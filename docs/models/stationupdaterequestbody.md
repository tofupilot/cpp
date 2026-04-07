# StationUpdateRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | New name for the station |
| `image_id` | `std::optional<std::string>` | :heavy_minus_sign: | Upload ID for the station image, or empty string to remove image |
| `team_id` | `NullableField<std::string>` | :heavy_minus_sign: | Team ID to assign this station to, or null to unassign |
