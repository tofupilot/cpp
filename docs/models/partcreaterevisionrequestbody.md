# PartCreateRevisionRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `number` | `std::string` | :heavy_check_mark: | Revision number (e.g., version number or code). |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata to attach to the revision (max 50 keys per revision). Plain object of key/value pairs; values can be string, number, or boolean. Type is detected from the value. |
