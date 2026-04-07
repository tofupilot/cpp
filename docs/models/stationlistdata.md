# StationListData


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Unique identifier of the station |
| `name` | `std::string` | :heavy_check_mark: | Name of the station |
| `procedures` | `std::vector<StationListProcedures>` | :heavy_check_mark: | Procedures linked to this station |
| `procedures_count` | `double` | :heavy_check_mark: | Total number of procedures linked to this station |
| `team` | `std::optional<StationListTeam>` | :heavy_minus_sign: | Team this station belongs to |
