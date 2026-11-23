# ImportTabularResponse

Run imported successfully

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | ID of the created run. With a mapping that makes several runs, the first one, see `ids`. |
| `file_import_id` | `std::string` | :heavy_check_mark: | ID of the file import record that links the runs to the uploaded file. |
| `ids` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Present with a mapping that makes several runs (`runsPer` `row` or `serial`): every run id created by this request, in file order, rows that failed or were skipped left out. When `already_imported` is true, the existing runs. |
| `already_imported` | `std::optional<bool>` | :heavy_minus_sign: | Present with a mapping that makes several runs. True when every run of this request already existed (see `skipped_rows`): `id` and `ids` are those runs and nothing was created. |
| `row_errors` | `std::optional<std::vector<ImportTabularRowErrors>>` | :heavy_minus_sign: | Present with a mapping that makes several runs: the rows of this request that created no run and why, at most 1000 (see `failed_row_count`). The other rows are imported. |
| `failed_row_count` | `std::optional<int64_t>` | :heavy_minus_sign: | Present with a mapping that makes several runs: how many runs of this request failed, including any not listed in `row_errors`. |
| `skipped_rows` | `std::optional<std::vector<ImportTabularSkippedRows>>` | :heavy_minus_sign: | Present with a mapping that makes several runs: the rows of this request an earlier import already created, at most 1000 (see `skipped_row_count`). They create no run. |
| `skipped_row_count` | `std::optional<int64_t>` | :heavy_minus_sign: | Present with a mapping that makes several runs: how many runs of this request were skipped because an earlier import created them. |
| `total_runs` | `std::optional<int64_t>` | :heavy_minus_sign: | Present with a mapping that makes several runs: how many runs the whole file makes (rows for `runsPer: row`, distinct serials for `runsPer: serial`), failed ones included. |
| `next_run_offset` | `std::optional<int64_t>` | :heavy_minus_sign: | Present when runs of the file remain after this request: send the same request with `run_offset` set to this value to import the next ones. |
| `warnings` | `std::optional<std::vector<std::string>>` | :heavy_minus_sign: | Non-fatal notes about the import, present when there are any. |
