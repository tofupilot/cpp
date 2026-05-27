# ImportStructuredResults


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `upload_id` | `std::string` | :heavy_check_mark: | Upload ID this result corresponds to. |
| `success` | `bool` | :heavy_check_mark: | Whether the file was imported successfully. |
| `id` | `std::optional<std::string>` | :heavy_minus_sign: | ID of the created run (present when success is true). For a multi-run file this is the first run; see `ids`. |
| `ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | All run ids created from the file. Present when the file produced more than one run. |
| `error` | `std::optional<std::string>` | :heavy_minus_sign: | Error message (present when success is false). |
