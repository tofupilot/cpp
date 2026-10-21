# RunCreateConfig


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `key` | `std::string` | :heavy_check_mark: | Key as declared under `config:` or `secrets:` in procedure.yaml. |
| `value` | `nlohmann::json` | :heavy_check_mark: | Value the run used, in its declared type. |
| `variable_id` | `NullableField<std::string>` | :heavy_minus_sign: | ID of the stored value the station received, when it came from TofuPilot. |
| `version` | `NullableField<int64_t>` | :heavy_minus_sign: | Version of the stored value the station received. |
| `source` | `NullableField<Source>` | :heavy_minus_sign: | Where the value came from: the YAML `default:`, the shell environment, a `.env` file, the station process environment, or a value stored on the station, the procedure or the organization. |
