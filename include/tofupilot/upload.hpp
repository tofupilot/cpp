// Hand-written attachment sub-resources for runs and units.

#pragma once

#include <chrono>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <httplib.h>

#include "client.hpp"
#include "error.hpp"
#include "types.hpp"

namespace tofupilot {

namespace detail {

inline const char* content_type_for(const std::string& filename) {
    auto dot = filename.rfind('.');
    if (dot == std::string::npos) return "application/octet-stream";
    std::string ext = filename.substr(dot + 1);
    for (auto& c : ext) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (ext == "pdf")                  return "application/pdf";
    if (ext == "png")                  return "image/png";
    if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
    if (ext == "gif")                  return "image/gif";
    if (ext == "csv")                  return "text/csv";
    if (ext == "json")                 return "application/json";
    if (ext == "xml")                  return "application/xml";
    if (ext == "zip")                  return "application/zip";
    if (ext == "txt" || ext == "log")  return "text/plain";
    if (ext == "html" || ext == "htm") return "text/html";
    return "application/octet-stream";
}

inline std::string extract_filename(const std::string& path) {
    auto sep = path.find_last_of("/\\");
    return (sep == std::string::npos) ? path : path.substr(sep + 1);
}

inline void put_to_presigned_url(const std::string& upload_url, const char* data, size_t size, const char* mime) {
    auto scheme_end = upload_url.find("://");
    if (scheme_end == std::string::npos) throw HttpError("Invalid upload URL: " + upload_url);
    auto path_start = upload_url.find('/', scheme_end + 3);
    if (path_start == std::string::npos) throw HttpError("Invalid upload URL (no path): " + upload_url);
    httplib::Client cli(upload_url.substr(0, path_start));
    cli.set_connection_timeout(std::chrono::seconds(60));
    cli.set_read_timeout(std::chrono::seconds(300));
    cli.set_write_timeout(std::chrono::seconds(300));
    auto result = cli.Put(upload_url.substr(path_start), data, size, mime);
    if (!result) throw HttpError("PUT to pre-signed URL failed: " + httplib::to_string(result.error()));
    if (result->status < 200 || result->status >= 300)
        throw HttpError("PUT to pre-signed URL returned HTTP " + std::to_string(result->status) + ": " + result->body);
}

inline std::vector<char> read_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw HttpError("Failed to open file: " + path);
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

inline void download_to_file(const std::string& url, const std::string& local_path) {
    if (url.empty()) throw ValidationError("Download URL cannot be empty");
    auto scheme_end = url.find("://");
    if (scheme_end == std::string::npos) throw HttpError("Invalid download URL: " + url);
    auto path_start = url.find('/', scheme_end + 3);
    if (path_start == std::string::npos) throw HttpError("Invalid download URL (no path): " + url);
    httplib::Client cli(url.substr(0, path_start));
    cli.set_read_timeout(std::chrono::seconds(300));
    auto result = cli.Get(url.substr(path_start));
    if (!result) throw HttpError("Download failed: " + httplib::to_string(result.error()));
    if (result->status < 200 || result->status >= 300)
        throw HttpError("Download returned HTTP " + std::to_string(result->status) + ": " + result->body);
    std::ofstream out(local_path, std::ios::binary);
    if (!out) throw HttpError("Failed to create file: " + local_path);
    out.write(result->body.data(), static_cast<std::streamsize>(result->body.size()));
}

} // namespace detail

/// Sub-resource: client.runs().attachments().create() / .download()
class RunAttachments {
public:
    explicit RunAttachments(TofuPilot& client) noexcept : client_(client) {}

    /// Upload a file and attach it to a run. Returns the attachment ID.
    std::string upload(const std::string& run_id, const std::string& path) {
        auto name = detail::extract_filename(path);
        if (name.empty()) throw ValidationError("Could not extract file name from path: " + path);
        auto bytes = detail::read_file(path);
        auto result = client_.runs().create_attachment().id(run_id).name(name).send();
        detail::put_to_presigned_url(result.upload_url, bytes.data(), bytes.size(), detail::content_type_for(name));
        return result.id;
    }

    /// Download an attachment to a local file.
    void download(const std::string& url, const std::string& local_path) {
        detail::download_to_file(url, local_path);
    }

private:
    TofuPilot& client_;
};

/// Sub-resource: client.units().attachments().upload() / .download() / .delete_()
class UnitAttachments {
public:
    explicit UnitAttachments(TofuPilot& client) noexcept : client_(client) {}

    /// Upload a file and attach it to a unit. Returns the attachment ID.
    std::string upload(const std::string& serial_number, const std::string& path) {
        auto name = detail::extract_filename(path);
        if (name.empty()) throw ValidationError("Could not extract file name from path: " + path);
        auto bytes = detail::read_file(path);
        auto result = client_.units().create_attachment().serial_number(serial_number).name(name).send();
        detail::put_to_presigned_url(result.upload_url, bytes.data(), bytes.size(), detail::content_type_for(name));
        return result.id;
    }

    /// Download an attachment to a local file.
    void download(const std::string& url, const std::string& local_path) {
        detail::download_to_file(url, local_path);
    }

    /// Delete attachments from a unit by their IDs.
    UnitDeleteAttachmentResponse delete_(const std::string& serial_number, std::vector<std::string> ids) {
        return client_.units().delete_attachment().serial_number(serial_number).ids(std::move(ids)).send();
    }

private:
    TofuPilot& client_;
};

// Add attachments() accessors to generated client classes
inline RunAttachments RunsClient::attachments() { return RunAttachments(client_); }
inline UnitAttachments UnitsClient::attachments() { return UnitAttachments(client_); }

} // namespace tofupilot
