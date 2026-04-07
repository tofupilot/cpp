# TofuPilot C++ Client

C++ client for the [TofuPilot](https://tofupilot.com) REST API. Synchronous, typed, with retries and builder-pattern operations.

**Requires:** C++17, OpenSSL

## Installation

### vcpkg

```bash
vcpkg install tofupilot
```

```cmake
find_package(tofupilot CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE tofupilot::tofupilot)
```

### CMake (FetchContent)

```cmake
include(FetchContent)
FetchContent_Declare(tofupilot GIT_REPOSITORY https://github.com/tofupilot/cpp.git GIT_TAG v2.0.0 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(tofupilot)
target_link_libraries(your_target PRIVATE tofupilot)
```

## Quick Start

```cpp
#include <tofupilot/tofupilot.hpp>
#include <iostream>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    auto run = client.runs().create()
        .procedure_id("550e8400-e29b-41d4-a716-446655440000")
        .serial_number("SN-001234")
        .part_number("PCB-V1.2")
        .outcome(tofupilot::Outcome::Pass)
        .send();

    std::cout << "Created run: " << run.id << std::endl;
}
```

## Available Resources

| Resource | Methods | Docs |
| --- | --- | --- |
| **Procedures** | list, create, get, delete_, update | [docs/sdks/procedures](docs/sdks/procedures/README.md) |
| **Versions** | get, delete_, create | [docs/sdks/versions](docs/sdks/versions/README.md) |
| **Runs** | list, create, delete_, get, update | [docs/sdks/runs](docs/sdks/runs/README.md) |
| **Attachments** | initialize, delete_, finalize | [docs/sdks/attachments](docs/sdks/attachments/README.md) |
| **Units** | list, create, delete_, get, update, add_child, remove_child | [docs/sdks/units](docs/sdks/units/README.md) |
| **Parts** | list, create, get, delete_, update | [docs/sdks/parts](docs/sdks/parts/README.md) |
| **Revisions** | get, delete_, update, create | [docs/sdks/revisions](docs/sdks/revisions/README.md) |
| **Batches** | get, delete_, update, list, create | [docs/sdks/batches](docs/sdks/batches/README.md) |
| **Stations** | list, create, get_current, get, remove, update | [docs/sdks/stations](docs/sdks/stations/README.md) |
| **User** | list | [docs/sdks/user](docs/sdks/user/README.md) |

All model types are documented in [docs/models/](docs/models).

## File Upload

```cpp
auto upload = tofupilot::upload_file(client, "report.pdf");
client.runs().update().id(run.id).attachments({upload.id}).send();
tofupilot::download_file(upload.url, "local-report.pdf");
```

## Error Handling

```cpp
try {
    auto run = client.runs().get().id("nonexistent").send();
} catch (const tofupilot::NotFoundError& e) {
    std::cerr << "Not found: " << e.error().message << std::endl;
} catch (const tofupilot::BadRequestError& e) {
    for (const auto& issue : e.error().issues)
        std::cerr << "  - " << issue.message << std::endl;
} catch (const tofupilot::ApiException& e) {
    std::cerr << "API error " << e.status_code() << ": " << e.what() << std::endl;
}
```

## Configuration

```cpp
auto client = tofupilot::TofuPilot(
    tofupilot::ClientConfig::with_api_key("your-api-key")
        .set_base_url("https://your-instance.example.com/api")
        .set_timeout(std::chrono::seconds(60))
        .set_max_retries(5)
);
```

## Thread Safety

`TofuPilot` is **not** thread-safe. Use one client per thread or synchronize externally.
