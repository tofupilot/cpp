# StationGetProcedures


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Procedure ID |
| `identifier` | `std::optional<std::string>` | :heavy_minus_sign: | Procedure identifier |
| `name` | `std::string` | :heavy_check_mark: | Procedure name |
| `runs_count` | `double` | :heavy_check_mark: | Number of runs created by this station in the last 7 days |
| `deployment` | `NullableField<StationGetDeployment>` | :heavy_minus_sign: | Deployment information for this procedure on this station |
