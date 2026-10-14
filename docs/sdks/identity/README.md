# Identity

## Overview

### Available Operations

* [whoami](#whoami) - Who am I

## whoami

The identity the request is authenticated as: the station or the user behind the API key, and its organization. Works with both kinds of key; `type` says which one. Use it before a call that only one kind may make, instead of catching that call's refusal.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.identity().whoami()
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

**[`IdentityWhoamiResponse`](../../models/identitywhoamiresponse.md)**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `ApiException(408)` | 408 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

