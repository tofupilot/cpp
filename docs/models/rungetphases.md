# RunGetPhases


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Phase ID. |
| `name` | `std::string` | :heavy_check_mark: | Phase name. |
| `outcome` | `PhasesOutcome` | :heavy_check_mark: | Phase execution result. |
| `started_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the phase started. |
| `ended_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the phase ended. |
| `duration` | `std::string` | :heavy_check_mark: | ISO 8601 duration of the phase (computed from started_at and ended_at). |
| `retry_count` | `int64_t` | :heavy_check_mark: | Zero-based retry attempt index. 0 = first attempt, 1 = first retry, etc. |
| `docstring` | `NullableField<std::string>` | :heavy_minus_sign: | Phase documentation string. |
| `measurements` | `std::vector<RunGetMeasurements>` | :heavy_check_mark: | Array of measurements taken during this phase. |
