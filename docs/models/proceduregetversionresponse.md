# ProcedureGetVersionResponse

Procedure version retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the procedure version. |
| `tag` | `std::string` | :heavy_check_mark: | Version tag. |
| `created_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the procedure version was created. |
| `created_by_user` | `NullableField<ProcedureGetVersionCreatedByUser>` | :heavy_minus_sign: | User who created this procedure version. |
| `created_by_station` | `NullableField<ProcedureGetVersionCreatedByStation>` | :heavy_minus_sign: | Station that created this procedure version. |
| `procedure` | `ProcedureGetVersionProcedure` | :heavy_check_mark: | Procedure this version belongs to. |
| `run_count` | `int64_t` | :heavy_check_mark: | Number of runs using this procedure version. |
