# PhaseGetResponse

Phase retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | N/A |
| `name` | `std::string` | :heavy_check_mark: | N/A |
| `outcome` | `PhaseGetOutcome` | :heavy_check_mark: | N/A |
| `started_at` | `std::string` | :heavy_check_mark: | N/A |
| `ended_at` | `std::string` | :heavy_check_mark: | N/A |
| `duration` | `std::string` | :heavy_check_mark: | N/A |
| `retry_count` | `int64_t` | :heavy_check_mark: | N/A |
| `sequence_path` | `std::optional<std::string>` | :heavy_minus_sign: | Path of the sequence call the phase ran in. Null for a phase written in the procedure itself. |
| `docstring` | `NullableField<std::string>` | :heavy_minus_sign: | N/A |
| `measurements` | `std::vector<PhaseGetMeasurements>` | :heavy_check_mark: | N/A |
| `run` | `PhaseGetRun` | :heavy_check_mark: | N/A |
| `procedure` | `PhaseGetProcedure` | :heavy_check_mark: | N/A |
