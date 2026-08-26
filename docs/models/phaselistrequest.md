# PhaseListRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `procedure_id` | `std::string` | :heavy_check_mark: | Procedure to list phases for. Required: phases are scoped to a single procedure. |
| `names` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `outcomes` | `std::optional<std::vector<PhaseGetOutcome>>` | :heavy_minus_sign: | N/A |
| `started_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `started_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `exclude_retries` | `std::optional<bool>` | :heavy_minus_sign: | N/A |
| `run_outcomes` | `std::optional<std::vector<LogGetOutcome>>` | :heavy_minus_sign: | N/A |
| `ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `duration_min` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `duration_max` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `deployment_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `procedure_versions` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `environments` | `std::optional<std::vector<Environment>>` | :heavy_minus_sign: | N/A |
| `operated_by_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `operated_by_names` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_station_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_user_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `serial_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `part_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `revision_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `batch_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `samples` | `std::optional<std::vector<PhaseListQueryParamSample>>` | :heavy_minus_sign: | N/A |
| `sort_by` | `std::optional<PhaseListSortBy>` | :heavy_minus_sign: | Field to sort results by. |
| `sort_order` | `std::optional<ListSortOrder>` | :heavy_minus_sign: | Sort order direction. |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of phases to return. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | Cursor for pagination. Use next_cursor from the previous response to fetch the next page. |
