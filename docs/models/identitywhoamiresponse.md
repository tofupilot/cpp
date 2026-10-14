# IdentityWhoamiResponse

Identity retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `type` | `IdentityWhoamiType` | :heavy_check_mark: | What the API key identifies: a station or a user. The matching object below is set, the other is null. |
| `station` | `std::optional<IdentityWhoamiStation>` | :heavy_minus_sign: | The station the request is authenticated as; null for a user key. |
| `user` | `std::optional<IdentityWhoamiUser>` | :heavy_minus_sign: | The user the request is authenticated as; null for a station key. |
| `organization` | `IdentityWhoamiOrganization` | :heavy_check_mark: | The organization the key belongs to. |
