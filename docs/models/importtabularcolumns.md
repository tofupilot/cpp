# ImportTabularColumns


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `column` | `std::string` | :heavy_check_mark: | N/A |
| `name` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `units` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `lower_limit` | `std::optional<double>` | :heavy_minus_sign: | N/A |
| `upper_limit` | `std::optional<double>` | :heavy_minus_sign: | N/A |
| `phase` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `outcome_map` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Turns the column into a step result: each cell value maps to the measurement outcome (`PASS`, `FAIL`, `UNSET`), or to `null` to leave that cell out, such as `NOT_RUN`. A failed measurement fails its phase. A value with no entry fails the row. |
