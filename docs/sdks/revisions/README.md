# Revisions

## Overview

### Available Operations

* [get](#get) - Get part revision
* [update](#update) - Update part revision
* [delete_](#delete_) - Delete part revision
* [create](#create) - Create part revision

## get

Get a part revision by part number and revision number, with its metadata, configuration, and linked units.

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

## update

Update a revision's number or image.

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
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to upsert on the revision. Plain object of key/value pairs. PATCH semantics: keys not present here are preserved. Pass `null` as a value to delete a key. |

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

## delete_

Delete a part revision. Irreversible.

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

## create

Create a revision of a part. Revision numbers match case-insensitively ("REV-A" == "rev-a").

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
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to attach to the revision (max 50 keys per revision). Plain object of key/value pairs; values can be string, number, or boolean. Type is detected from the value. |

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

