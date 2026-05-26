# RunListCreatedByUser

User whose API key was used to create this run. Only returned if `all` or `created_by` is included.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | User ID. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | User display name. |
| `email` | `std::optional<std::string>` | :heavy_minus_sign: | User email address. |
