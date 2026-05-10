# Procedures

## Overview

### Available Operations

* [list](#list) - List and filter procedures
* [create](#create) - Create procedure
* [get](#get) - Get procedure
* [delete_](#delete_) - Delete procedure
* [update](#update) - Update procedure

## list

Retrieve procedures with optional filtering and search. Returns procedure data including creator and linked repository.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.procedures().list()
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
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of procedures to return per page. |
| `cursor` | `std::optional<double>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |

### Response

**[`ProcedureListResponse`](../../models/procedurelistresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## create

Create a new test procedure that can be used to organize and track test runs. The procedure serves as a template or framework for organizing test execution.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.procedures().create()
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
| `name` | `std::string` | :heavy_check_mark: | Name of the procedure. Must be unique within the organization. |

### Response

**[`ProcedureCreateResponse`](../../models/procedurecreateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get

Retrieve a single procedure by ID, including recent test runs, linked stations, and version history.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.procedures().get()
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
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the procedure to retrieve. |

### Response

**[`ProcedureGetResponse`](../../models/proceduregetresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## delete_

Permanently delete a procedure, removing all associated runs, phases, measurements, and attachments.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.procedures().delete_()
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
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the procedure to delete. |

### Response

**[`ProcedureDeleteResponse`](../../models/proceduredeleteresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## update

Update a test procedure's name or configuration. The procedure is identified by its unique ID in the URL path. Only provided fields are modified.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.procedures().update()
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
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the procedure to update. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | New name for the procedure. |
| `production_branch` | `NullableField<std::string>` | :heavy_minus_sign: | Branch treated as production. Pushes to this branch deploy as production; every other branch deploys as preview. Null = no branch promoted to production. |
| `auto_push_enabled` | `std::optional<bool>` | :heavy_minus_sign: | Master switch for auto-pushing builds to linked stations. Build artifacts are always recorded; this only gates the station fan-out. |
| `excluded_branch_patterns` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Branches matching any of these patterns (exact name or minimatch glob, e.g. "renovate/*") skip preview deployments. Empty array = no exclusions. |
| `root_directory` | `NullableField<std::string>` | :heavy_minus_sign: | Path within the linked repo to the directory holding this procedure's `pyproject.toml` (and `procedure.yaml` for framework procedures). Empty/null = repo root. |
| `entry_point` | `NullableField<std::string>` | :heavy_minus_sign: | Entry-point path inside the procedure's package dir, relative to it. Forwarded to the CLI through the deployment manifest. Empty/null = use the framework default (openhtf/plain → main.py, pytest → ".", yaml → procedure.yaml auto-discovery). |

### Response

**[`ProcedureUpdateResponse`](../../models/procedureupdateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

