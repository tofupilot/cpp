# RunUpdateMetadataRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to upsert on the run. Plain object of key/value pairs. PATCH semantics: keys not present here are preserved. Pass `null` as a value to delete a key. |
