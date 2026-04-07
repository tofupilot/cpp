# RunGetMeasurements


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Measurement ID. |
| `name` | `std::string` | :heavy_check_mark: | Measurement name. |
| `outcome` | `ValidatorsOutcome` | :heavy_check_mark: | Measurement validation result. |
| `units` | `std::optional<std::string>` | :heavy_minus_sign: | Units of measurement. |
| `validators` | `std::optional<std::vector<RunGetValidators>>` | :heavy_minus_sign: | Structured validation rules with outcome and expected values. |
| `aggregations` | `NullableField<std::vector<RunGetAggregations>>` | :heavy_minus_sign: | Aggregations computed over this measurement. |
| `measured_value` | `std::optional<nlohmann::json>` | :heavy_minus_sign: | The actual measured value. |
| `data_series` | `std::optional<std::vector<RunGetDataSeries>>` | :heavy_minus_sign: | Multi-dimensional measurement data series. |
