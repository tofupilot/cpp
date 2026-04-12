# TofuPilot C++ Client

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)

The official C++ client for [TofuPilot](https://tofupilot.com). Integrate your hardware test runs into one app with just a few lines of C++.

## Installation

Add to your `CMakeLists.txt`:

```cmake
include(FetchContent)
FetchContent_Declare(tofupilot GIT_REPOSITORY https://github.com/tofupilot/cpp.git GIT_TAG v2.0.2 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(tofupilot)
target_link_libraries(your_target PRIVATE tofupilot)
```

**Requires:** C++17, OpenSSL

## Quick Start

```cpp
#include <tofupilot/tofupilot.hpp>
#include <iostream>

int main() {
    auto client = tofupilot::TofuPilot("your-api-key");

    auto run = client.runs().create()
        .procedure_id("your-procedure-id")
        .serial_number("SN-001234")
        .part_number("PCB-V1.2")
        .outcome(tofupilot::Outcome::Pass)
        .started_at("2025-01-01T00:00:00Z")
        .ended_at("2025-01-01T00:05:00Z")
        .send();

    std::cout << "Run created: " << run.id << std::endl;
}
```

## Authentication

Set your API key as an environment variable:

```bash
export TOFUPILOT_API_KEY="your-api-key"
```

```cpp
auto client = tofupilot::TofuPilot(std::getenv("TOFUPILOT_API_KEY"));
```

Or pass it directly:

```cpp
auto client = tofupilot::TofuPilot("your-api-key");
```

To point to a different server (e.g. self-hosted):

```cpp
auto client = tofupilot::TofuPilot(
    tofupilot::ClientConfig::with_api_key("your-api-key")
        .set_base_url("https://your-instance.example.com")
);
```

## Available Resources

| Resource | Operations |
|----------|-----------|
| `client.procedures()` | list, create, get, delete_, update |
| `client.versions()` | get, delete_, create |
| `client.runs()` | list, create, delete_, get, update, create_attachment |
| `client.attachments()` | initialize, finalize |
| `client.units()` | list, create, delete_, get, update, add_child, remove_child, create_attachment, delete_attachment |
| `client.parts()` | list, create, get, delete_, update |
| `client.revisions()` | get, delete_, update, create |
| `client.batches()` | get, delete_, update, list, create |
| `client.stations()` | list, create, get_current, get, remove, update |
| `client.user()` | list |

## Usage Examples

### Create a run with measurements

```cpp
tofupilot::RunCreateMeasurements m;
m.name = "Output Voltage";
m.outcome = tofupilot::ValidatorsOutcome::Pass;
m.measured_value = nlohmann::json(3.3);

tofupilot::RunCreatePhases phase;
phase.name = "Voltage Test";
phase.outcome = tofupilot::PhasesOutcome::Pass;
phase.started_at = "2025-01-01T00:00:00Z";
phase.ended_at = "2025-01-01T00:05:00Z";
phase.measurements = {m};

auto run = client.runs().create()
    .procedure_id("your-procedure-id")
    .serial_number("SN-001")
    .part_number("PCB-V1")
    .outcome(tofupilot::Outcome::Pass)
    .started_at("2025-01-01T00:00:00Z")
    .ended_at("2025-01-01T00:05:00Z")
    .phases({phase})
    .send();
```

### List and filter runs

```cpp
auto result = client.runs().list()
    .part_numbers({"PCB-V1"})
    .outcomes({tofupilot::Outcome::Pass})
    .limit(10)
    .send();

for (const auto& run : result.data) {
    std::cout << run.id << " — " << run.unit.serial_number << std::endl;
}
```

### Upload and download attachments

```cpp
// Upload a file
auto upload = tofupilot::upload_file(client, "report.pdf");

// Link to a run
client.runs().update().id(run.id).attachments({upload.id}).send();

// Download
tofupilot::download_file(upload.url, "local-copy.pdf");
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

| Exception | Status Code |
|-----------|------------|
| `BadRequestError` | 400 |
| `UnauthorizedError` | 401 |
| `ForbiddenError` | 403 |
| `NotFoundError` | 404 |
| `ConflictError` | 409 |
| `UnprocessableContentError` | 422 |
| `InternalServerError` | 500 |

## Thread Safety

`TofuPilot` is **not** thread-safe. Use one client per thread or synchronize externally.

## Documentation

- [Getting Started](https://tofupilot.com/docs/dashboard)
- [API Reference](https://tofupilot.com/docs/dashboard/api/v2)
- [Changelog](https://tofupilot.com/changelog)

## License

MIT
