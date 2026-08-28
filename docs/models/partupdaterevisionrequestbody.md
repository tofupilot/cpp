# PartUpdateRevisionRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `number` | `std::optional<std::string>` | :heavy_minus_sign: | New revision number to set. |
| `image_id` | `std::optional<std::string>` | :heavy_minus_sign: | Upload ID for the revision image, or empty string to remove image |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to upsert on the revision. Plain object of key/value pairs. PATCH semantics: keys not present here are preserved. Pass `null` as a value to delete a key. |
