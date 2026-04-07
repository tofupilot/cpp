# RunGetAttachments


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `id` | `std::string` | :heavy_check_mark: | Attachment ID. |
| `name` | `std::string` | :heavy_check_mark: | File name. |
| `size` | `std::optional<double>` | :heavy_minus_sign: | File size in bytes. |
| `content_type` | `std::optional<std::string>` | :heavy_minus_sign: | MIME type of the file. |
| `is_report` | `bool` | :heavy_check_mark: | Whether this attachment is a test report (from file import) or a regular attachment. |
| `download_url` | `NullableField<std::string>` | :heavy_minus_sign: | Presigned URL for downloading the file. This URL is temporary and will expire. |
