# AuditListMeta


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `has_more` | `bool` | :heavy_check_mark: | Whether more events are available. |
| `next_cursor` | `std::optional<std::string>` | :heavy_minus_sign: | Pass as cursor to fetch the next page. Null when there are no more events. |
