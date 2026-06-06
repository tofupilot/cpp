# DeploymentGetResponse

Deployment retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier for the deployment. |
| `environment` | `Environment` | :heavy_check_mark: | Deployment environment. |
| `trigger` | `Trigger` | :heavy_check_mark: | How the deployment was triggered. |
| `status` | `DeploymentGetStatus` | :heavy_check_mark: | Build status of the deployment. |
| `deployed_at` | `std::string` | :heavy_check_mark: | ISO 8601 timestamp when the deployment was created. |
| `started_at` | `std::optional<std::string>` | :heavy_minus_sign: | ISO 8601 timestamp when the build started. Null if not started. |
| `ended_at` | `std::optional<std::string>` | :heavy_minus_sign: | ISO 8601 timestamp when the build ended. Null if not ended. |
| `artifact_url` | `std::optional<std::string>` | :heavy_minus_sign: | URL of the built artifact. Null if not built. |
| `artifact_sha256` | `std::optional<std::string>` | :heavy_minus_sign: | SHA-256 checksum of the artifact. Null if not built. |
| `artifact_size_bytes` | `std::optional<double>` | :heavy_minus_sign: | Size of the artifact in bytes. Null if not built. |
| `deployment_mode` | `DeploymentGetDeploymentMode` | :heavy_check_mark: | Deployment mode. |
| `platform` | `std::optional<std::string>` | :heavy_minus_sign: | Target platform. Null if unspecified. |
| `language` | `std::optional<std::string>` | :heavy_minus_sign: | Procedure language. Null if unspecified. |
| `runtime_version` | `std::optional<std::string>` | :heavy_minus_sign: | Runtime version. Null if unspecified. |
| `procedure` | `std::optional<DeploymentGetProcedure>` | :heavy_minus_sign: | Procedure this deployment targets. |
| `created_by_user` | `std::optional<DeploymentGetCreatedByUser>` | :heavy_minus_sign: | User who created the deployment. Null for system-created deployments. |
| `commit` | `std::optional<DeploymentGetCommit>` | :heavy_minus_sign: | Git commit the deployment was built from. Null for non-git deployments. |
| `stations` | `std::vector<DeploymentGetStations>` | :heavy_check_mark: | Stations linked to the procedure, with per-station push state. pushed_at is null when this deployment has not been pushed to that station. |
| `build_logs` | `std::vector<DeploymentGetBuildLogs>` | :heavy_check_mark: | Build log lines for this deployment, ordered by sequence. Empty if the build has not produced logs. |
