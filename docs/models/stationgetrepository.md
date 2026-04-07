# StationGetRepository


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `owner` | `std::string` | :heavy_check_mark: | Repository owner |
| `name` | `std::string` | :heavy_check_mark: | Repository name |
| `provider` | `Provider` | :heavy_check_mark: | Git provider |
| `gitlab_project_id` | `std::optional<double>` | :heavy_minus_sign: | GitLab project ID (only for GitLab repos) |
