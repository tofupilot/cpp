# UnitGetResponse

Units retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the unit. |
| `serial_number` | `std::string` | :heavy_check_mark: | Unit serial number. |
| `created_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the unit was created. |
| `created_by_user` | `NullableField<UnitGetCreatedByUser>` | :heavy_minus_sign: | User who created this unit. |
| `created_by_station` | `NullableField<UnitGetCreatedByStation>` | :heavy_minus_sign: | Station that created this unit. |
| `part` | `UnitGetPart` | :heavy_check_mark: | Part information with revision details for this unit. Every unit must have a part and revision. |
| `batch` | `NullableField<UnitGetBatch>` | :heavy_minus_sign: | Batch information for this unit. |
| `parent` | `std::optional<UnitGetParent>` | :heavy_minus_sign: | Parent unit information with part details and processed images. |
| `children` | `std::optional<std::vector<UnitGetChildren>>` | :heavy_minus_sign: | Child units with part details. |
| `created_during` | `NullableField<UnitGetCreatedDuring>` | :heavy_minus_sign: | Run that created this unit. |
| `attachments` | `std::optional<std::vector<UnitGetAttachments>>` | :heavy_minus_sign: | Files attached to this unit. |
