# RunListOperatedBy

User who operated this run. Only returned if `all` or `operated_by` is included.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Operator ID. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Operator display name. |
| `email` | `std::optional<std::string>` | :heavy_minus_sign: | Operator email address. |
