# PartListData


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique database identifier of the part. |
| `number` | `std::string` | :heavy_check_mark: | Unique part number identifier. |
| `name` | `std::string` | :heavy_check_mark: | Human-readable name of the part. |
| `created_at` | `std::string` | :heavy_check_mark: | Time at which the part was created. |
| `revisions` | `std::vector<PartListRevisions>` | :heavy_check_mark: | List of revisions for this part. |
| `metadata` | `std::optional<std::map<std::string, nlohmann::json>>` | :heavy_minus_sign: | Custom metadata key/value pairs on the part. Only present when the request sets `include_metadata=true`. |
