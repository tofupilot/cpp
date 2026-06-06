# DeploymentGetBuildLogs


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `seq` | `int64_t` | :heavy_check_mark: | Sequence number ordering the log line within the build. |
| `level` | `Level` | :heavy_check_mark: | Severity of the build log line. |
| `message` | `std::string` | :heavy_check_mark: | Build log line content. |
| `created_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the log line was emitted. |
