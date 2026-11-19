# RunGetPlugs


## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `key` | `std::string` | :heavy_check_mark: | Key of the plug in the procedure. |
| `name` | `std::string` | :heavy_check_mark: | Display name of the plug. |
| `python` | `std::optional<std::string>` | :heavy_minus_sign: | Class reference of the plug as written in the procedure. |
| `scope` | `std::optional<Scope>` | :heavy_minus_sign: | Lifetime of the plug instance: slot, execution or station. |
| `manufacturer` | `std::optional<std::string>` | :heavy_minus_sign: | Maker of the instrument. |
| `model` | `std::optional<std::string>` | :heavy_minus_sign: | Model of the instrument. |
| `serial_number` | `std::optional<std::string>` | :heavy_minus_sign: | Serial number of the instrument. |
| `firmware` | `std::optional<std::string>` | :heavy_minus_sign: | Firmware version of the instrument. |
