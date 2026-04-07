# User

## Overview

### Available Operations

* [list](#list) - List users

## list

Retrieve a list of users in your organization. Use the current parameter to get only the authenticated user profile and permissions.

### Example Usage

```cpp
#include <tofupilot/tofupilot.hpp>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    try {
        auto result = client.user().list()
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
| `current` | `std::optional<bool>` | :heavy_minus_sign: | If true, returns only the current authenticated user |

### Response

**`std::vector<UserListResponse>`**

### Errors

| Error Type | Status Code | Content Type |
| --- | --- | --- |
| `UnauthorizedError` | 401 | application/json |
| `InternalServerError` | 500 | application/json |
| `ApiException` | 4XX, 5XX | \*/\* |

