# AuditListData


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique ID of the event. Stable: use it to de-duplicate. |
| `occurred_at` | `std::string` | :heavy_check_mark: | When the event occurred, in UTC, from the database clock. |
| `action` | `std::string` | :heavy_check_mark: | What was done, written resource.verb. |
| `outcome` | `DataOutcome` | :heavy_check_mark: | Whether the action succeeded. |
| `actor` | `AuditListActor` | :heavy_check_mark: | N/A |
| `on_behalf_of` | `std::optional<AuditListOnBehalfOf>` | :heavy_minus_sign: | The member a TofuPilot staff member acted as, when the actor was impersonating them. Null otherwise. |
| `via` | `Via` | :heavy_check_mark: | Surface the action came through. |
| `client` | `std::optional<std::string>` | :heavy_minus_sign: | SDK, CLI or MCP client that made the request, when known. |
| `api_key_id` | `std::optional<std::string>` | :heavy_minus_sign: | ID of the API key used, when the request used one. |
| `target` | `std::optional<AuditListTarget>` | :heavy_minus_sign: | N/A |
| `changes` | `std::vector<AuditListChanges>` | :heavy_check_mark: | Values the action replaced, and the columns of deleted records. Empty when not recorded. |
| `input` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Request input, with credentials replaced by [redacted]. Large inputs keep their top-level fields only. |
| `error` | `std::optional<std::string>` | :heavy_minus_sign: | Error message of a failed action. |
| `request_id` | `std::optional<std::string>` | :heavy_minus_sign: | ID of the request that produced the event. |
| `ip_address` | `std::optional<std::string>` | :heavy_minus_sign: | IP address the request came from. |
| `user_agent` | `std::optional<std::string>` | :heavy_minus_sign: | User agent of the request. |
