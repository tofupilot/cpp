# Attachments

## Overview

### Available Operations

* [initialize](#initialize) - Initialize upload
* [delete_](#delete_) - Delete attachments
* [finalize](#finalize) - Finalize upload

## initialize

Get a temporary pre-signed URL to upload a file. Returns the upload ID and URL. Upload the file to the URL with a PUT request, then call Finalize upload.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.attachments().initialize()
            .name("My Test Procedure")
            .send();
    } catch (const tofupilot::ApiException& e) {
        // Handle error
    }

    return 0;
}
```

### Parameters

| Parameter | Type | Required | Description |
| --- | --- | --- | --- |
| `name` | `std::string` | :heavy_check_mark: | File name including extension (e.g. "report.pdf") |

### Response

**[`AttachmentInitializeResponse`](../../models/attachmentinitializeresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `ForbiddenError` | 403 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `BadGatewayError` | 502 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## delete_

Permanently delete attachments by their IDs and unlink them from any associated runs or units. Removes files from storage and clears all references.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.attachments().delete_()
            .ids({"550e8400-e29b-41d4-a716-446655440000"})
            .send();
    } catch (const tofupilot::ApiException& e) {
        // Handle error
    }

    return 0;
}
```

### Parameters

| Parameter | Type | Required | Description |
| --- | --- | --- | --- |
| `ids` | `std::vector<std::string>` | :heavy_check_mark: | Upload IDs to delete |

### Response

**[`AttachmentDeleteResponse`](../../models/attachmentdeleteresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## finalize

Finalize a file upload after uploading to the pre-signed URL. Validates the file and records its metadata.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.attachments().finalize()
            .id("550e8400-e29b-41d4-a716-446655440000")
            .send();
    } catch (const tofupilot::ApiException& e) {
        // Handle error
    }

    return 0;
}
```

### Parameters

| Parameter | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | ID of the upload to finalize |

### Response

**[`AttachmentFinalizeResponse`](../../models/attachmentfinalizeresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

