# DeploymentListCommit

Git commit the deployment was built from. Null for non-git deployments.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | N/A |
| `sha` | `std::string` | :heavy_check_mark: | N/A |
| `message` | `std::string` | :heavy_check_mark: | N/A |
| `author_username` | `std::string` | :heavy_check_mark: | N/A |
| `author_avatar_url` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `committed_at` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
| `branch` | `std::optional<std::string>` | :heavy_minus_sign: | N/A |
