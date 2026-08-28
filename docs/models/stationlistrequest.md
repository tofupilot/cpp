# StationListRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Number of stations to return per page |
| `cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | N/A |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `procedure_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | N/A |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Filter stations by custom metadata. Supports up to 5 keys per request. Per-key operators: string `{in: [...]}`/`{contains: "..."}`, number `{gte, lte, gt, lt, eq}`, bool `{eq: true|false}`. |
| `include_metadata` | `std::optional<bool>` | :heavy_minus_sign: | When true, includes the custom metadata object on each station in the response. Defaults to false to keep payloads small. |
