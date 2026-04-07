# RunGetDataSeriesAggregations

Aggregation result with computed value and optional validators.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the aggregation. |
| `type` | `std::string` | :heavy_check_mark: | Aggregation type (e.g., MIN, MAX, MEAN, RANGE, STD_DEV). |
| `outcome` | `std::optional<std::string>` | :heavy_minus_sign: | Aggregation validation result: PASS, FAIL, UNSET, or null if no validators. |
| `value` | `std::optional<nlohmann::json>` | :heavy_minus_sign: | Computed aggregation value. Type depends on aggregation type. |
| `unit` | `NullableField<std::string>` | :heavy_minus_sign: | Unit of measurement for the aggregated value. |
| `validators` | `NullableField<std::vector<RunGetDataSeriesAggregationsValidators>>` | :heavy_minus_sign: | Validators applied to the aggregated value. |
