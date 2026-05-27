# Imports

## Overview

### Available Operations

* [structured](#structured) - Import runs from structured files
* [tabular](#tabular) - Import a run from a tabular file

## structured

Import one or more previously uploaded structured files (OpenHTF, WATS WSJF/WSXF, ATML, NI TestStand, STDF, or ATDF) in a single call. Each file is parsed independently and its result returned per-item, so one bad file does not fail the others. A file that contains several units (a multi-part STDF/ATDF datalog or a multi-report WSXF/TestStand document) creates one run per unit; all run ids are returned in the item’s `ids`.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.imports().structured()
            .items({})
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
| `items` | `std::vector<ImportStructuredItems>` | :heavy_check_mark: | Files to import (1–100). Pass a single-item list to import one file. Each item is parsed independently; one failure does not abort the others. |

### Response

**[`ImportStructuredResponse`](../../models/importstructuredresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

## tabular

Import a previously uploaded tabular file (CSV or Excel) by mapping its columns to TofuPilot fields. Provide exactly one of `mapping` (an inline column mapping) or `template_id` (a mapping template saved in the dashboard). The `procedure_id` is required and overrides any procedure referenced in the file.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.imports().tabular()
            .upload_id("550e8400-e29b-41d4-a716-446655440000")
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
| `upload_id` | `std::string` | :heavy_check_mark: | ID of a previously uploaded tabular file. |
| `procedure_id` | `std::string` | :heavy_check_mark: | Procedure to attach the imported run to. Always overrides any procedure referenced in the file. Create the procedure in the app first, then find the auto-generated ID on the procedure page. |
| `mapping` | `std::optional<ImportTabularMapping>` | :heavy_minus_sign: | Inline column mapping describing how source columns feed TofuPilot fields. Provide this OR template_id, not both. |
| `template_id` | `std::optional<std::string>` | :heavy_minus_sign: | ID of a saved mapping template to apply. Provide this OR mapping, not both. |

### Response

**[`ImportTabularResponse`](../../models/importtabularresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `BadRequestError` | 400 | application/json |
| `UnauthorizedError` | 401 | application/json |
| `NotFoundError` | 404 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

