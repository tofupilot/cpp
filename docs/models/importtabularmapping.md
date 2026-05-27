# ImportTabularMapping

Inline column mapping describing how source columns feed TofuPilot fields. Provide this OR template_id, not both.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `fields` | `ImportTabularFields` | :heavy_check_mark: | N/A |
| `measurements` | `nlohmann::json` | :heavy_check_mark: | N/A |
| `phases` | `std::optional<ImportTabularPhases>` | :heavy_minus_sign: | N/A |
| `metadata` | `std::optional<std::vector<ImportTabularMetadata>>` | :heavy_minus_sign: | N/A |
| `unit_metadata` | `std::optional<std::vector<ImportTabularUnitMetadata>>` | :heavy_minus_sign: | N/A |
