# AuditListActor


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `type` | `AuditListType` | :heavy_check_mark: | Who acted. |
| `id` | `std::optional<std::string>` | :heavy_minus_sign: | ID of the user or station. Null for the system. |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | Name of the actor at the time of the event. |
| `email` | `std::optional<std::string>` | :heavy_minus_sign: | Email of the user at the time of the event. |
