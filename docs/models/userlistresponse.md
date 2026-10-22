# UserListResponse


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the user. |
| `email` | `std::optional<std::string>` | :heavy_minus_sign: | Email address of the user. Null for another member when the key belongs to a viewer restricted to access groups. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Display name of the user. |
| `image` | `std::optional<std::string>` | :heavy_minus_sign: | Profile image URL for the user. |
| `banned` | `bool` | :heavy_check_mark: | Whether the user is banned. |
