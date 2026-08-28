# Stations

## Overview

### Available Operations

* [create](#create) - Create station
* [list](#list) - List and filter stations
* [get_current](#get_current) - Get current station
* [get](#get) - Get station
* [update](#update) - Update station
* [remove](#remove) - Remove station

## create

Create a station to register production equipment and link it to procedures.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.stations().create()
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
| `name` | `std::string` | :heavy_check_mark: | Name of the station |
| `procedure_id` | `std::optional<std::string>` | :heavy_minus_sign: | Optional procedure ID to link the station to |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to attach to the station (max 50 keys per station). Plain object of key/value pairs; values can be string, number, or boolean. Type is detected from the value. Use it for descriptive fields such as location or asset tag — not for procedure configuration, which belongs to station config. |

### Response

**[`StationCreateResponse`](../../models/stationcreateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `ForbiddenError` | 403 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## list

List stations. Search by name and filter by status. Cursor-paginated.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.stations().list()
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
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Number of stations to return per page |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Filter stations by custom metadata. Supports up to 5 keys per request. Per-key operators: string `{in: [...]}`/`{contains: "..."}`, number `{gte, lte, gt, lt, eq}`, bool `{eq: true|false}`. |
| `include_metadata` | `std::optional<bool>` | :heavy_minus_sign: | When true, includes the custom metadata object on each station in the response. Defaults to false to keep payloads small. |

### Response

**[`StationListResponse`](../../models/stationlistresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get_current

Get the station the request is authenticated as, with its linked procedures.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.stations().get_current()
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

### Response

**[`StationGetCurrentResponse`](../../models/stationgetcurrentresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `ForbiddenError` | 403 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get

Get a station by ID, with its linked procedures and recent activity.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.stations().get()
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
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the station to retrieve |

### Response

**[`StationGetResponse`](../../models/stationgetresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## update

Update a station name and/or image. Pass an empty string for image_id to remove the image.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.stations().update()
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
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the station to update |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | New name for the station |
| `image_id` | `std::optional<std::string>` | :heavy_minus_sign: | Upload ID for the station image, or empty string to remove image |
| `team_id` | `NullableField<std::string>` | :heavy_minus_sign: | Team ID to assign this station to, or null to unassign |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to upsert on the station. Plain object of key/value pairs. PATCH semantics: keys not present here are preserved. Pass `null` as a value to delete a key. |

### Response

**[`StationUpdateResponse`](../../models/stationupdateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## remove

Remove a station. Deleted if unused; archived (history preserved) if runs reference it.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.stations().remove()
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
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the station to remove |

### Response

**[`StationRemoveResponse`](../../models/stationremoveresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

