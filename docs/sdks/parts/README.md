# Parts

## Overview

### Available Operations

* [create](#create) - Create part
* [list](#list) - List and filter parts
* [get](#get) - Get part
* [update](#update) - Update part
* [delete_](#delete_) - Delete part

## create

Create a part, optionally with an initial revision. Part numbers match case-insensitively ("PART-001" == "part-001").

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.parts().create()
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
| `number` | `std::string` | :heavy_check_mark: | Unique identifier number for the part. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Human-readable name for the part. If not provided, a default name will be used. |
| `revision_number` | `std::optional<std::string>` | :heavy_minus_sign: | Revision identifier for the part version. If not provided, default revision identifier will be used. |

### Response

**[`PartCreateResponse`](../../models/partcreateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## list

List parts. Filter and search by name, number, or revision number. Cursor-paginated.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.parts().list()
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
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of parts to return in a single page. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `sort_by` | `std::optional<PartListSortBy>` | :heavy_minus_sign: | Field to sort results by. |
| `sort_order` | `std::optional<ListSortOrder>` | :heavy_minus_sign: | Sort order direction. |

### Response

**[`PartListResponse`](../../models/partlistresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## get

Get a part by number, with its revisions, metadata, and linked units. Numbers match case-insensitively.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.parts().get()
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
| `number` | `std::string` | :heavy_check_mark: | Part number of the part to retrieve. |

### Response

**[`PartGetResponse`](../../models/partgetresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## update

Update a part's number or name. Numbers match case-insensitively.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.parts().update()
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
| `number` | `std::string` | :heavy_check_mark: | Part number of the part to update. |
| `new_number` | `std::optional<std::string>` | :heavy_minus_sign: | New unique identifier number for the part. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | New human-readable name for the part. |

### Response

**[`PartUpdateResponse`](../../models/partupdateresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `ConflictError` | 409 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## delete_

Delete a part and all its revisions. Irreversible.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.parts().delete_()
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
| `number` | `std::string` | :heavy_check_mark: | Part number to delete. |

### Response

**[`PartDeleteResponse`](../../models/partdeleteresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

