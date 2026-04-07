# Versions

## Overview

### Available Operations

* [get](#get) - Get procedure version
* [delete_](#delete_) - Delete procedure version
* [create](#create) - Create procedure version

## get

Retrieve a single procedure version by its tag, including version metadata and configuration details.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.versions().get()
            .procedure_id("550e8400-e29b-41d4-a716-446655440000")
            .tag("value")
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
| `procedure_id` | `std::string` | :heavy_check_mark: | ID of the procedure that owns this version. |
| `tag` | `std::string` | :heavy_check_mark: | Version tag to retrieve. |

### Response

**[`ProcedureGetVersionResponse`](../../models/proceduregetversionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## delete_

Permanently delete a procedure version by its tag. This removes the version record and all associated configuration data and cannot be undone.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.versions().delete_()
            .procedure_id("550e8400-e29b-41d4-a716-446655440000")
            .tag("value")
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
| `procedure_id` | `std::string` | :heavy_check_mark: | ID of the procedure that owns this version |
| `tag` | `std::string` | :heavy_check_mark: | Version tag to delete |

### Response

**[`ProcedureDeleteVersionResponse`](../../models/proceduredeleteversionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## create

Create a new version for an existing test procedure. Versions let you track procedure changes over time and maintain a history of test configurations.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.versions().create()
            .procedure_id("550e8400-e29b-41d4-a716-446655440000")
            .tag("value")
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
| `procedure_id` | `std::string` | :heavy_check_mark: | The ID of the procedure this version belongs to |
| `tag` | `std::string` | :heavy_check_mark: | The version tag |

### Response

**[`ProcedureCreateVersionResponse`](../../models/procedurecreateversionresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

