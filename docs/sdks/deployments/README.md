# Deployments

## Overview

### Available Operations

* [list](#list) - List and filter deployments
* [get](#get) - Get deployment

## list

List deployments with filtering by procedure, environment, build status, branch, author, and date range. Cursor-paginated.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.deployments().list()
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
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `environments` | `std::optional<std::vector<Environment>>` | :heavy_minus_sign: | N/A |
| `build_statuses` | `std::optional<std::vector<DeploymentGetStatus>>` | :heavy_minus_sign: | N/A |
| `pushed` | `std::optional<bool>` | :heavy_minus_sign: | N/A |
| `branch_names` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `author_usernames` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `deployed_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `deployed_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of deployments to return. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | Cursor for pagination. Use next_cursor from the previous response to fetch the next page. |

### Response

**[`DeploymentListResponse`](../../models/deploymentlistresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get

Get a deployment by ID, with its artifact metadata, commit, creator, and per-station push state.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.deployments().get()
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
| `id` | `std::string` | :heavy_check_mark: | The deployment ID to retrieve. |

### Response

**[`DeploymentGetResponse`](../../models/deploymentgetresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

