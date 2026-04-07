# BatchListMeta

Pagination metadata.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `has_more` | `bool` | :heavy_check_mark: | Whether there are more results available. |
| `next_cursor` | `std::optional<int64_t>` | :heavy_minus_sign: | Cursor for fetching the next page of results. |
