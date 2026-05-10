# UnitUpdateRequestBody


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `new_serial_number` | `std::optional<std::string>` | :heavy_minus_sign: | New serial number for the unit. |
| `part_number` | `std::optional<std::string>` | :heavy_minus_sign: | New part number for the unit. |
| `revision_number` | `std::optional<std::string>` | :heavy_minus_sign: | New revision number for the unit. |
| `batch_number` | `NullableField<std::string>` | :heavy_minus_sign: | New batch number for the unit. Set to null to remove batch. |
| `attachments` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Array of upload IDs to attach to the unit. |
| `sample` | `NullableField<std::string>` | :heavy_minus_sign: | Reference-sample classification. 'golden' marks a known-good reference unit; 'failing' marks a known-faulty reference unit. Both are excluded from production analytics by default. Set to null to clear and treat as a production unit. |
