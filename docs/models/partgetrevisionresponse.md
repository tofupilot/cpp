# PartGetRevisionResponse

Revision retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the revision. |
| `number` | `std::string` | :heavy_check_mark: | Revision number. |
| `created_at` | `std::optional<std::string>` | :heavy_minus_sign: | ISO 8601 timestamp when the revision was created. |
| `created_by_user` | `std::optional<PartGetRevisionCreatedByUser>` | :heavy_minus_sign: | User who created the revision. |
| `created_by_station` | `std::optional<PartGetRevisionCreatedByStation>` | :heavy_minus_sign: | Station that created the revision. |
| `part` | `PartGetRevisionPart` | :heavy_check_mark: | Part associated with this revision. |
| `units` | `std::vector<PartGetRevisionUnits>` | :heavy_check_mark: | List of units created with this revision. |
