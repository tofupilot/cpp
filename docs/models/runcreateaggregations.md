# RunCreateAggregations

Aggregation specification with computed value and optional validators.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `type` | `std::string` | :heavy_check_mark: | Aggregation function: "min", "max", "avg", "sum", "count", "std", "median", "percentile_95", etc. |
| `outcome` | `NullableField<std::string>` | :heavy_minus_sign: | Computed result of aggregation validation. Server stores as-is. |
| `value` | `NullableField<nlohmann::json>` | :heavy_minus_sign: | Computed aggregation value. |
| `unit` | `NullableField<std::string>` | :heavy_minus_sign: | Unit for the aggregated value. |
| `validators` | `NullableField<std::vector<RunCreateAggregationsValidators>>` | :heavy_minus_sign: | Validators applied to the aggregated value. |
