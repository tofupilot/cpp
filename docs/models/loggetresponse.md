# LogGetResponse

Log retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | N/A |
| `level` | `Level` | :heavy_check_mark: | N/A |
| `message` | `std::string` | :heavy_check_mark: | N/A |
| `created_at` | `std::string` | :heavy_check_mark: | N/A |
| `source_file` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `line_number` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `run` | `LogGetRun` | :heavy_check_mark: | N/A |
| `unit` | `LogGetUnit` | :heavy_check_mark: | N/A |
| `procedure` | `LogGetProcedure` | :heavy_check_mark: | N/A |
| `created_by_user` | `std::optional<LogGetCreatedByUser>` | :heavy_minus_sign: | N/A |
| `created_by_station` | `std::optional<LogGetCreatedByStation>` | :heavy_minus_sign: | N/A |
