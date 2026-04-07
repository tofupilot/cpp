# ProcedureGetResponse

Procedure retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the procedure. |
| `identifier` | `std::optional<std::string>` | :heavy_minus_sign: | Optional unique identifier for the procedure. |
| `name` | `std::string` | :heavy_check_mark: | Procedure name. |
| `created_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the procedure was created. |
| `created_by_user` | `std::optional<ProcedureGetCreatedByUser>` | :heavy_minus_sign: | User who created this procedure. |
| `runs_count` | `double` | :heavy_check_mark: | Total number of runs for this procedure. |
| `recent_runs` | `std::vector<ProcedureGetRecentRuns>` | :heavy_check_mark: | List of recent runs for this procedure. |
| `stations` | `std::vector<ProcedureGetStations>` | :heavy_check_mark: | Stations linked to this procedure. |
