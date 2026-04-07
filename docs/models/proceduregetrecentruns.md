# ProcedureGetRecentRuns


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Run ID. |
| `started_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the run started. |
| `outcome` | `Outcome` | :heavy_check_mark: | Run outcome. |
| `unit` | `std::optional<ProcedureGetUnit>` | :heavy_minus_sign: | Unit information. |
