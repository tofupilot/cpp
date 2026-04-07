# RunGetDataSeriesAggregationsValidators

Validator result with outcome and comparison details.

## Fields

| Field | Type | Required | Description |
| --- | --- | --- | --- |
| `outcome` | `ValidatorsOutcome` | :heavy_check_mark: | Validation result: PASS, FAIL, or UNSET. |
| `operator_` | `std::optional<std::string>` | :heavy_minus_sign: | Comparison operator used for validation. |
| `expected_value` | `std::optional<nlohmann::json>` | :heavy_minus_sign: | Expected value for comparison. Type depends on measurement type. |
| `expression` | `std::string` | :heavy_check_mark: | Human-readable expression string for display. |
| `is_decisive` | `std::optional<bool>` | :heavy_minus_sign: | Whether this validator is decisive (if it fails, measurement fails). False for marginal/warning validators. |
| `is_expression_only` | `bool` | :heavy_check_mark: | True if validator only has expression (no structured operator/expected_value). |
| `analytics_expression` | `std::optional<std::string>` | :heavy_minus_sign: | Synthetic expression from operator+expected_value for analytics tooltip. Null if expression-only. |
| `has_custom_expression` | `bool` | :heavy_check_mark: | True if user provided a custom expression (shown in italic with analytics tooltip). |
