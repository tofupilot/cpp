# RunGetDataSeries


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `data` | `std::vector<double>` | :heavy_check_mark: | Array of numeric data points for this series. |
| `units` | `std::optional<std::string>` | :heavy_minus_sign: | Unit for this data series. |
| `name` | `NullableField<std::string>` | :heavy_minus_sign: | Name of this data series. |
| `description` | `NullableField<std::string>` | :heavy_minus_sign: | Description of this data series. |
| `validators` | `NullableField<std::vector<RunGetDataSeriesValidators>>` | :heavy_minus_sign: | Validators for this data series. |
| `aggregations` | `NullableField<std::vector<RunGetDataSeriesAggregations>>` | :heavy_minus_sign: | Aggregations computed over this data series. |
