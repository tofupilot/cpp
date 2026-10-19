# RunGetSequences


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | N/A |
| `path` | `std::string` | :heavy_check_mark: | Instance keys of the call and of the calls it is nested in, joined by `/`. Unique within the run. |
| `key` | `std::string` | :heavy_check_mark: | The call's own instance key (last segment of `path`). |
| `parent_path` | `std::optional<std::string>` | :heavy_minus_sign: | Path of the enclosing call, null for a call made in the procedure itself. |
| `name` | `std::string` | :heavy_check_mark: | N/A |
| `source` | `std::optional<std::string>` | :heavy_minus_sign: | The sequence reference as written in the procedure (`uses:`). |
| `outcome` | `SequencesOutcome` | :heavy_check_mark: | Outcome of the call, aggregated over its phases like a run outcome. SKIP when none of them ran. |
| `started_at` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `ended_at` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `duration` | `std::optional<std::string>` | :heavy_minus_sign: | ISO 8601 duration, null for a skipped call. |
