# PartCreateRequest


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `number` | `std::string` | :heavy_check_mark: | Unique identifier number for the part. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Human-readable name for the part. If not provided, a default name will be used. |
| `revision_number` | `std::optional<std::string>` | :heavy_minus_sign: | Revision identifier for the part version. If not provided, default revision identifier will be used. |
