# MeasurementListData


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the measurement. |
| `phase_name` | `std::string` | :heavy_check_mark: | Name of the phase this measurement belongs to. |
| `measurement_name` | `std::string` | :heavy_check_mark: | Name of the measurement. |
| `started_at` | `std::optional<std::string>` | :heavy_minus_sign: | ISO 8601 timestamp when the measurement's phase started. |
| `value` | `std::optional<double>` | :heavy_minus_sign: | Numeric value, when the measurement is numeric. Null otherwise. |
| `bool_value` | `std::optional<bool>` | :heavy_minus_sign: | Boolean value, when the measurement is boolean. Null otherwise. |
| `string_value` | `std::optional<std::string>` | :heavy_minus_sign: | String value, when the measurement is a string. Null otherwise. |
| `units` | `std::optional<std::string>` | :heavy_minus_sign: | Measurement units, when applicable. |
| `measurement_outcome` | `Outcome` | :heavy_check_mark: | Outcome of the measurement. |
| `run_id` | `std::string` | :heavy_check_mark: | ID of the run this measurement belongs to. |
| `serial_number` | `std::optional<std::string>` | :heavy_minus_sign: | Serial number of the unit tested. |
| `sample` | `std::optional<Sample>` | :heavy_minus_sign: | Sample class of the unit (golden or failing). Null for regular units. |
| `measurement_type` | `MeasurementType` | :heavy_check_mark: | Value type of the measurement. |
| `retry_count` | `int64_t` | :heavy_check_mark: | Retry attempt number of the phase this measurement belongs to (0 for the first attempt). |
| `is_final_attempt` | `bool` | :heavy_check_mark: | True when this measurement comes from the final attempt of its phase. |
| `validators` | `std::optional<std::vector<MeasurementListValidators>>` | :heavy_minus_sign: | Validators applied to this measurement. Null when none. |
