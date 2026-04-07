# Units

## Overview

### Available Operations

* [list](#list) - List and filter units
* [create](#create) - Create unit
* [delete_](#delete_) - Delete units
* [get](#get) - Get unit
* [update](#update) - Update unit
* [add_child](#add_child) - Add sub-unit
* [remove_child](#remove_child) - Remove sub-unit

## list

Retrieve a paginated list of units with filtering by serial number, part number, and batch. Uses cursor-based pagination for efficient large dataset traversal.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().list()
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
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `serial_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `part_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `revision_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `batch_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `outcomes` | `std::optional<std::vector<Outcome>>` | :heavy_minus_sign: | N/A |
| `started_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `started_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `latest_only` | `std::optional<bool>` | :heavy_minus_sign: | N/A |
| `run_count_min` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `run_count_max` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `created_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_by_user_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_station_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `exclude_units_with_parent` | `std::optional<bool>` | :heavy_minus_sign: | N/A |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of units to return. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `sort_by` | `std::optional<UnitListSortBy>` | :heavy_minus_sign: | Field to sort results by. last_run_at sorts by most recent test run date. last_run_procedure sorts by procedure name of the last run. |
| `sort_order` | `std::optional<ListSortOrder>` | :heavy_minus_sign: | Sort order direction. |

### Response

**[`UnitListResponse`](../../models/unitlistresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## create

Create a new unit with a serial number and link it to a part revision. Units represent individual hardware items tracked for manufacturing traceability.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().create()
            .serial_number("SN-001234")
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
| `serial_number` | `std::string` | :heavy_check_mark: | Unique serial number identifier for the unit. Must be unique within the organization. |
| `part_number` | `std::string` | :heavy_check_mark: | Component part number that defines what type of unit this is. If the part does not exist, it will be created. |
| `revision_number` | `std::string` | :heavy_check_mark: | Hardware revision identifier for the specific version of the part. If the revision does not exist, it will be created. |

### Response

**[`UnitCreateResponse`](../../models/unitcreateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## delete_

Permanently delete units by serial number. This action will remove all nested elements and relationships associated with the units.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().delete_()
            .serial_numbers({"SN-001234"})
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
| `serial_numbers` | `std::vector<std::string>` | :heavy_check_mark: | Array of unit serial numbers to delete. |

### Response

**[`UnitDeleteResponse`](../../models/unitdeleteresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get

Retrieve a single unit by its serial number. Returns comprehensive unit data including part information, parent/child relationships, and test run history.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().get()
            .serial_number("SN-001234")
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
| `serial_number` | `std::string` | :heavy_check_mark: | Serial number of the unit to retrieve. |

### Response

**[`UnitGetResponse`](../../models/unitgetresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## update

Update unit properties including serial number, part revision, batch assignment, and file attachments with case-insensitive matching.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().update()
            .serial_number("SN-001234")
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
| `serial_number` | `std::string` | :heavy_check_mark: | Serial number of the unit to update. |
| `new_serial_number` | `std::optional<std::string>` | :heavy_minus_sign: | New serial number for the unit. |
| `part_number` | `std::optional<std::string>` | :heavy_minus_sign: | New part number for the unit. |
| `revision_number` | `std::optional<std::string>` | :heavy_minus_sign: | New revision number for the unit. |
| `batch_number` | `NullableField<std::string>` | :heavy_minus_sign: | New batch number for the unit. Set to null to remove batch. |
| `attachments` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Array of upload IDs to attach to the unit. |

### Response

**[`UnitUpdateResponse`](../../models/unitupdateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## add_child

Add a sub-unit to a parent unit to track component assemblies and multi-level hardware traceability.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().add_child()
            .serial_number("SN-001234")
            .child_serial_number("SN-001234")
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
| `serial_number` | `std::string` | :heavy_check_mark: | Serial number of the parent unit |
| `child_serial_number` | `std::string` | :heavy_check_mark: | Serial number of the sub-unit to add |

### Response

**[`UnitAddChildResponse`](../../models/unitaddchildresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## remove_child

Remove a sub-unit relationship from a parent unit by serial number. Only unlinks the parent-child relationship; neither unit is deleted from the system.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.units().remove_child()
            .serial_number("SN-001234")
            .child_serial_number("SN-001234")
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
| `serial_number` | `std::string` | :heavy_check_mark: | Serial number of the parent unit |
| `child_serial_number` | `std::string` | :heavy_check_mark: | Serial number of the sub-unit to remove |

### Response

**[`UnitRemoveChildResponse`](../../models/unitremovechildresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

