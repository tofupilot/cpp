# LogListCreatedByUser

User who created this log. Null if created by a station or system.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the user. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Display name of the user who created this log. |
| `email` | `std::optional<std::string>` | :heavy_minus_sign: | Email of the user. |
