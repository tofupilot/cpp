# StationGetResponse

Station retrieved successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the station |
| `name` | `std::string` | :heavy_check_mark: | Name of the station |
| `api_key` | `std::optional<std::string>` | :heavy_minus_sign: | API key prefix for the station (full key only shown on creation) |
| `procedures` | `std::vector<StationGetProcedures>` | :heavy_check_mark: | Procedures linked to this station with recent run counts |
| `organization_slug` | `std::string` | :heavy_check_mark: | Slug of the organization this station belongs to |
| `connection_status` | `std::optional<std::string>` | :heavy_minus_sign: | Current connection status of the station |
| `team` | `std::optional<StationGetTeam>` | :heavy_minus_sign: | Team this station is assigned to |
