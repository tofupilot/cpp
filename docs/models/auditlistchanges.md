# AuditListChanges


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `field` | `std::string` | :heavy_check_mark: | N/A |
| `previous` | `std::optional<nlohmann::json>` | :heavy_minus_sign: | Value before the action. |
| `next` | `std::optional<nlohmann::json>` | :heavy_minus_sign: | Value after the action. |
