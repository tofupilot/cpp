# MeasurementGetResponse

Measurement retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | N/A |
| `name` | `std::string` | :heavy_check_mark: | N/A |
| `outcome` | `Outcome` | :heavy_check_mark: | N/A |
| `units` | `NullableField<std::string>` | :heavy_minus_sign: | N/A |
| `validators` | `std::optional<std::vector<MeasurementGetValidators>>` | :heavy_minus_sign: | N/A |
| `aggregations` | `NullableField<std::vector<MeasurementGetAggregations>>` | :heavy_minus_sign: | N/A |
| `measured_value` | `std::optional<nlohmann::json>` | :heavy_minus_sign: | N/A |
| `data_series` | `std::optional<std::vector<MeasurementGetDataSeries>>` | :heavy_minus_sign: | N/A |
| `docstring` | `NullableField<std::string>` | :heavy_minus_sign: | N/A |
| `phase` | `MeasurementGetPhase` | :heavy_check_mark: | N/A |
| `run` | `MeasurementGetRun` | :heavy_check_mark: | N/A |
| `procedure` | `MeasurementGetProcedure` | :heavy_check_mark: | N/A |
