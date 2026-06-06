# DeploymentListRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `environments` | `std::optional<std::vector<Environment>>` | :heavy_minus_sign: | N/A |
| `build_statuses` | `std::optional<std::vector<DeploymentGetStatus>>` | :heavy_minus_sign: | N/A |
| `pushed` | `std::optional<bool>` | :heavy_minus_sign: | N/A |
| `branch_names` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `author_usernames` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `deployed_after` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `deployed_before` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of deployments to return. |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | Cursor for pagination. Use next_cursor from the previous response to fetch the next page. |
