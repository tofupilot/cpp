# LogListRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `levels` | `std::optional<std::vector<Level>>` | :heavy_minus_sign: | N/A |
| `timestamp_after` | `std::optional<std::string>` | :heavy_minus_sign: | Filter logs with timestamp after this date (inclusive). |
| `timestamp_before` | `std::optional<std::string>` | :heavy_minus_sign: | Filter logs with timestamp before this date (inclusive). |
| `source_files` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `run_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `run_outcomes` | `std::optional<std::vector<LogGetOutcome>>` | :heavy_minus_sign: | N/A |
| `procedure_versions` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `deployment_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `environments` | `std::optional<std::vector<Environment>>` | :heavy_minus_sign: | N/A |
| `serial_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `part_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `revision_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `batch_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `samples` | `std::optional<std::vector<Sample>>` | :heavy_minus_sign: | N/A |
| `created_by_station_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_user_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `sort_by` | `std::optional<LogListSortBy>` | :heavy_minus_sign: | Field to sort results by. |
| `sort_order` | `std::optional<ListSortOrder>` | :heavy_minus_sign: | Sort order direction. |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of logs to return. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
