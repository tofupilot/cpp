# RunCreateMeasurements


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `name` | `std::string` | :heavy_check_mark: | Name identifier for the measurement. Each measurement should have a descriptive name that identifies the specific data point being captured. Analytics at measurement level are computed using this name as unique identifier. |
| `outcome` | `ValidatorsOutcome` | :heavy_check_mark: | Result of the measurement validation. Use PASS when measurement meets all criteria, FAIL when measurement is outside acceptable limits or validation fails, UNSET when no validation was performed. |
| `x_axis` | `NullableField<RunCreateXAxis>` | :heavy_minus_sign: | X-axis data series for multi-dimensional measurements. Use with y_axis for structured multi-dimensional data with per-axis validators/aggregations. |
| `y_axis` | `NullableField<std::vector<RunCreateYAxis>>` | :heavy_minus_sign: | Y-axis data series (one or more) for multi-dimensional measurements. Each series can have its own validators and aggregations. |
| `measured_value` | `NullableField<nlohmann::json>` | :heavy_minus_sign: | N/A |
| `units` | `NullableField<nlohmann::json>` | :heavy_minus_sign: | [LEGACY for multi-dim] Units of measurement. For structured multi-dimensional, use units within x_axis/y_axis instead. |
| `lower_limit` | `std::optional<double>` | :heavy_minus_sign: | Use validators with operator ">=" instead. Will be converted to a validator automatically. |
| `upper_limit` | `std::optional<double>` | :heavy_minus_sign: | Use validators with operator "<=" instead. Will be converted to a validator automatically. |
| `validators` | `NullableField<std::vector<RunCreateMeasurementsValidators>>` | :heavy_minus_sign: | N/A |
| `aggregations` | `NullableField<std::vector<RunCreateMeasurementsAggregations>>` | :heavy_minus_sign: | N/A |
| `docstring` | `NullableField<std::string>` | :heavy_minus_sign: | N/A |
