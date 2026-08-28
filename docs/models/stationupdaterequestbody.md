# StationUpdateRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | New name for the station |
| `image_id` | `std::optional<std::string>` | :heavy_minus_sign: | Upload ID for the station image, or empty string to remove image |
| `team_id` | `NullableField<std::string>` | :heavy_minus_sign: | Team ID to assign this station to, or null to unassign |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to upsert on the station. Plain object of key/value pairs. PATCH semantics: keys not present here are preserved. Pass `null` as a value to delete a key. |
