# UnitListLastRun


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the run. |
| `outcome` | `Outcome` | :heavy_check_mark: | Final result of the test run execution. |
| `started_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the run execution started. |
| `ended_at` | `std::optional<std::string>` | :heavy_minus_sign: | ISO 8601 timestamp when the run execution completed. Null if still running. |
| `procedure` | `std::optional<UnitListProcedure>` | :heavy_minus_sign: | Test procedure that was executed. Null if run had no associated procedure. |
