# RunCreateYAxis

Data series with numeric data, unit, and optional validators/aggregations.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `data` | `std::vector<double>` | :heavy_check_mark: | Array of numeric data points for this axis. |
| `units` | `NullableField<std::string>` | :heavy_minus_sign: | Unit for this axis. |
| `description` | `NullableField<std::string>` | :heavy_minus_sign: | Description of this data series. |
| `validators` | `NullableField<std::vector<RunCreateYAxisValidators>>` | :heavy_minus_sign: | Validators for this specific axis/series. |
| `aggregations` | `NullableField<std::vector<RunCreateYAxisAggregations>>` | :heavy_minus_sign: | Aggregations computed over this axis data (min, max, avg, etc.). |
