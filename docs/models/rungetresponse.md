# RunGetResponse

Single test run details.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the run. |
| `created_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the run was created. |
| `started_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the run execution started. |
| `ended_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the run execution ended. |
| `duration` | `std::string` | :heavy_check_mark: | ISO 8601 duration of the run (computed from started_at and ended_at). |
| `outcome` | `LogGetOutcome` | :heavy_check_mark: | Final result of the run execution. |
| `docstring` | `NullableField<std::string>` | :heavy_minus_sign: | Additional notes or documentation about this test run. |
| `execution_id` | `std::optional<std::string>` | :heavy_minus_sign: | Groups the runs produced by one multi-slot execution, one run per slot. Null for single-slot runs. |
| `slot_key` | `std::optional<std::string>` | :heavy_minus_sign: | Key of the fixture slot that produced this run. Null for single-slot runs. |
| `slot_name` | `std::optional<std::string>` | :heavy_minus_sign: | Display name of the slot as declared at run time. Null when absent. |
| `created_by_user` | `NullableField<RunGetCreatedByUser>` | :heavy_minus_sign: | User whose API key was used to create this run. Only returned if `all` or `created_by` is included. |
| `created_by_station` | `NullableField<RunGetCreatedByStation>` | :heavy_minus_sign: | Station whose API key was used to create this run. Only returned if `all` or `created_by` is included. |
| `operated_by` | `NullableField<RunGetOperatedBy>` | :heavy_minus_sign: | Operator of this run: a linked organization member (id/email set) or a declared free-text name (id/email null). Only returned if `all` or `operated_by` is included. |
| `procedure` | `RunGetProcedure` | :heavy_check_mark: | Test procedure associated with this run. |
| `unit` | `RunGetUnit` | :heavy_check_mark: | Unit under test information. |
| `phases` | `std::optional<std::vector<RunGetPhases>>` | :heavy_minus_sign: | Array of execution phases in this run, ordered by start time, then by name and retry attempt for phases that share one. Retry attempts of a phase therefore always appear in attempt order. Only returned if `all` or `phases` is included. |
| `attachments` | `std::optional<std::vector<RunGetAttachments>>` | :heavy_minus_sign: | Files attached to this run, including both regular attachments and test reports. Only returned if `all` or `attachments` is included. |
| `logs` | `std::optional<std::vector<RunGetLogs>>` | :heavy_minus_sign: | N/A |
| `sub_units` | `std::optional<std::vector<RunGetSubUnits>>` | :heavy_minus_sign: | Array of sub-units that had parent changes during this run. Only returned if `all` or `sub_units` is included. |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata key/value pairs on the run. |
