# Override In-Game System Language

Plugin filename: `system_language_override.prx`

Authors:

* jocover
* Kendek

Override System Language detected by applications.

**Note:** This plugin is incompatible with `button_swap.prx` !

## How To Use

* Load [latest GoldHEN](https://github.com/GoldHEN/GoldHEN/releases) on your PS4.
* Check `Enable Plugins Loader` option in `Plugin Settings` menu.
* Place `system_language_override.prx` in the `/data/GoldHEN/plugins/`.
* Add `/data/GoldHEN/plugins/system_language_override.prx` into `/data/GoldHEN/plugins.ini`.  
**Note:** End of Line must be UNIX format!
* Add a Language Code to each `/data/GoldHEN/plugins/system_language_override.prx` line as a comment.

## Supported Language Codes

| Language | Code |
| - | :-: |
| Arabic | `ar` |
| Chinese (Simplified) | `zh_CN` |
| Chinese (Traditional) | `zh_TW` |
| Czech | `cs` |
| Danish | `da` |
| Dutch | `nl` |
| English (United Kingdom) | `en_GB` |
| English (United States) | `en_US` |
| Finnish| `fi` |
| French (Canada) | `fr_CA` |
| French (France) | `fr_FR` |
| German | `de` |
| Greek | `el` |
| Hungarian | `hu` |
| Indonesian | `in` |
| Italian | `it` |
| Japanese | `ja` |
| Korean | `ko` |
| Norwegian | `no` |
| Polish | `pl` |
| Portuguese (Brazil) | `pt_BR` |
| Portuguese (Portugal) | `pt_PT` |
| Romanian | `ro` |
| Russian | `ru` |
| Spanish (Latin America) | `es_LA` |
| Spanish (Spain) | `es_ES` |
| Swedish | `sv` |
| Thai | `th` |
| Turkish | `tr` |
| Ukrainian | `uk` |
| Vietnamese | `vi` |

## Example

```
[CUSA12345]
/data/GoldHEN/plugins/system_language_override.prx ; en_US

[CUSA12346]
/data/GoldHEN/plugins/system_language_override.prx ; hu
```
