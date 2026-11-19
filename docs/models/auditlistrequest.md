# AuditListRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `occurred_after` | `std::optional<std::string>` | :heavy_minus_sign: | Only events that occurred at or after this time (ISO 8601). |
| `occurred_before` | `std::optional<std::string>` | :heavy_minus_sign: | Only events that occurred at or before this time (ISO 8601). |
| `actions` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Filter by action, written resource.verb. |
| `actor_ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Filter by the user or station that acted. |
| `vias` | `std::optional<std::vector<Via>>` | :heavy_minus_sign: | N/A |
| `outcomes` | `std::optional<std::vector<DataOutcome>>` | :heavy_minus_sign: | N/A |
| `target_type` | `std::optional<std::string>` | :heavy_minus_sign: | Filter by the type of record acted on. |
| `target_id` | `std::optional<std::string>` | :heavy_minus_sign: | Filter by the ID of the record acted on. |
| `request_id` | `std::optional<std::string>` | :heavy_minus_sign: | Filter by request ID, to find the events one API request produced. |
| `search_query` | `std::optional<std::string>` | :heavy_minus_sign: | Match the actor name or email, the record name, or the action. |
| `limit` | `std::optional<int64_t>` | :heavy_minus_sign: | Maximum number of events to return. |
| `cursor` | `NullableField<nlohmann::json>` | :heavy_minus_sign: | Opaque cursor of the next page: pass next_cursor from the previous response unchanged. A keyset cursor rather than an offset: paging is stable while new events arrive. An event is timestamped when its request starts and appears when it commits, so a poller re-reads the last 10 minutes and de-duplicates by id. |
