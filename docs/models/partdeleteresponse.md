# PartDeleteResponse

Part deleted successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the deleted part. |
| `deleted_revision_ids` | `std::vector<std::string>` | :heavy_check_mark: | IDs of all revisions that were deleted with the part. |
