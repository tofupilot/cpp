# Revisions

## Overview

### Available Operations

* [get](#get) - Get part revision
* [delete_](#delete_) - Delete part revision
* [update](#update) - Update part revision
* [create](#create) - Create part revision

## get

Retrieve a single part revision by its part number and revision number, including revision metadata, configuration details, and linked units.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.revisions().get()
            .part_number("PCB-V1.2")
            .revision_number("REV-A")
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
| `part_number` | `std::string` | :heavy_check_mark: | Part number that the revision belongs to. |
| `revision_number` | `std::string` | :heavy_check_mark: | Revision number to retrieve. |

### Response

**[`PartGetRevisionResponse`](../../models/partgetrevisionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## delete_

Permanently delete a part revision by its part number and revision number. This action removes the revision and all associated data and cannot be undone.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.revisions().delete_()
            .part_number("PCB-V1.2")
            .revision_number("REV-A")
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
| `part_number` | `std::string` | :heavy_check_mark: | Part number that the revision belongs to. |
| `revision_number` | `std::string` | :heavy_check_mark: | Revision number to delete. |

### Response

**[`PartDeleteRevisionResponse`](../../models/partdeleterevisionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## update

Update a part revision's number or image. Identifies the revision by part number and revision number in the URL.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.revisions().update()
            .part_number("PCB-V1.2")
            .revision_number("REV-A")
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
| `part_number` | `std::string` | :heavy_check_mark: | Part number that the revision belongs to. |
| `revision_number` | `std::string` | :heavy_check_mark: | Current revision number to update. |
| `number` | `std::optional<std::string>` | :heavy_minus_sign: | New revision number to set. |
| `image_id` | `std::optional<std::string>` | :heavy_minus_sign: | Upload ID for the revision image, or empty string to remove image |

### Response

**[`PartUpdateRevisionResponse`](../../models/partupdaterevisionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## create

Create a new part revision for an existing part. Revision numbers are matched case-insensitively (e.g., "REV-A" and "rev-a" are considered the same).

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.revisions().create()
            .part_number("PCB-V1.2")
            .number("PART-001")
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
| `part_number` | `std::string` | :heavy_check_mark: | Part number to create a revision for. |
| `number` | `std::string` | :heavy_check_mark: | Revision number (e.g., version number or code). |

### Response

**[`PartCreateRevisionResponse`](../../models/partcreaterevisionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

