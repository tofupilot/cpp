# BatchListData


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the batch. |
| `number` | `std::string` | :heavy_check_mark: | Batch number. |
| `created_at` | `std::string` | :heavy_check_mark: | ISO timestamp when the batch was created. |
| `created_by_user` | `NullableField<BatchListCreatedByUser>` | :heavy_minus_sign: | User who created this batch. |
| `created_by_station` | `NullableField<BatchListCreatedByStation>` | :heavy_minus_sign: | Station that created this batch. |
| `unit_count` | `int64_t` | :heavy_check_mark: | Total number of units in this batch. |
