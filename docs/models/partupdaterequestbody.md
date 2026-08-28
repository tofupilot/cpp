# PartUpdateRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `new_number` | `std::optional<std::string>` | :heavy_minus_sign: | New unique identifier number for the part. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | New human-readable name for the part. |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to upsert on the part. Plain object of key/value pairs. PATCH semantics: keys not present here are preserved. Pass `null` as a value to delete a key. |
