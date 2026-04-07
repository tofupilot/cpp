# RunListRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `outcomes` | `std::optional<std::vector<Outcome>>` | :heavy_minus_sign: | N/A |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `procedure_versions` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `serial_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `part_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `revision_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `batch_numbers` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `duration_min` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `duration_max` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `started_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `started_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `ended_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `ended_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `created_by_user_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `created_by_station_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `operated_by_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of runs to return per page. |
| `cursor` | `std::optional<double>` | :heavy_minus_sign: | N/A |
| `sort_by` | `std::optional<RunListSortBy>` | :heavy_minus_sign: | Field to sort results by. |
| `sort_order` | `std::optional<ListSortOrder>` | :heavy_minus_sign: | Sort order direction. |
