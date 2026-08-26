# Measurements

## Overview

### Available Operations

* [list](#list) - List and filter measurements
* [get](#get) - Get measurement

## list

List measurements for a procedure with filtering by phase, measurement, value, outcome, date range, unit, and run details. Cursor-paginated.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.measurements().list()
            .procedure_id("550e8400-e29b-41d4-a716-446655440000")
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
| `procedure_id` | `std::string` | :heavy_check_mark: | Procedure to list measurements for. Required: measurements are scoped to a single procedure. |
| `phase_name` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `measurement_name` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `phase_names` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `outcomes` | `std::optional<std::vector<LogGetOutcome>>` | :heavy_minus_sign: | N/A |
| `ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `duration_min` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `duration_max` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `deployment_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `procedure_versions` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `environments` | `std::optional<std::vector<Environment>>` | :heavy_minus_sign: | N/A |
| `serial_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `part_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `revision_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `batch_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `operated_by_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `operated_by_names` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_station_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_user_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `started_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `started_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `exclude_retries` | `std::optional<bool>` | :heavy_minus_sign: | Exclude retried phase attempts, keeping only the final attempt. |
| `value_min` | `std::optional<double>` | :heavy_minus_sign: | N/A |
| `value_max` | `std::optional<double>` | :heavy_minus_sign: | N/A |
| `value_bool` | `std::optional<bool>` | :heavy_minus_sign: | N/A |
| `value_strings` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `measurement_outcomes` | `std::optional<std::vector<Outcome>>` | :heavy_minus_sign: | N/A |
| `measurement_types` | `std::optional<std::vector<MeasurementType>>` | :heavy_minus_sign: | N/A |
| `sort_by` | `std::optional<MeasurementListSortBy>` | :heavy_minus_sign: | Field to sort results by. |
| `sort_order` | `std::optional<ListSortOrder>` | :heavy_minus_sign: | Sort order direction. |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of measurements to return. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | Cursor for pagination. Use next_cursor from the previous response to fetch the next page. |

### Response

**[`MeasurementListResponse`](../../models/measurementlistresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get

Get a single measurement by ID, with its value, validators, and run context.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.measurements().get()
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
| `id` | `std::string` | :heavy_check_mark: | ID of the measurement to retrieve. |

### Response

**[`MeasurementGetResponse`](../../models/measurementgetresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

