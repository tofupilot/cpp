# IdentityWhoamiUser

The user the request is authenticated as; null for a station key.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the user. |
| `email` | `std::string` | :heavy_check_mark: | Email address of the user. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Display name of the user. |
