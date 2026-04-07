# UnitGetAttachments


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Attachment ID. |
| `name` | `std::string` | :heavy_check_mark: | File name. |
| `size` | `std::optional<double>` | :heavy_minus_sign: | File size in bytes. |
| `content_type` | `std::optional<std::string>` | :heavy_minus_sign: | MIME type of the file. |
| `download_url` | `std::optional<std::string>` | :heavy_minus_sign: | Presigned URL for downloading the file. This URL is temporary and will expire. |
