# E1001 Weather Display

> DRAFT/WIP

This is an ESPHome project for the E1001 Weather Display.

It includes a GitHub workflow that will automatically build the configuration(s) and then deploys a simple
website via GitHub pages that utilizes [ESP Web Tools](https://esphome.github.io/esp-web-tools/) for users to easily install onto their device.

## Using this repo from ESPHome

The “core” config lives in `e1001-weather-display.yaml` (display, sensors, data-source substitutions). It intentionally **does not** define Wi-Fi, API encryption, or OTA passwords — those should live in your device YAML.

The board-specific entrypoints include that core file:

- `e1001-weather-display-esp32.yaml`
- `e1001-weather-display-esp32-c3.yaml`
- `e1001-weather-display-esp32-c6.yaml`
- `e1001-weather-display-esp32-s3.yaml`

### Option A: Use your local git checkout (recommended for development)

- Put this repo somewhere ESPHome can read (for Home Assistant add-on, that typically means under `/config/esphome/`).
- Use the board entrypoint YAML directly, or create a small “wrapper” YAML that includes it as a package.

Example wrapper YAML (path is relative to the wrapper file):

```yaml
substitutions:
  name: e1001-weather-display
  friendly_name: E1001 Weather Display

packages:
  e1001: !include e1001-weather-display/e1001-weather-display-esp32-s3.yaml
```

### Option B: Use GitHub as the source (recommended for stable installs)

In an ESPHome device YAML, import the board entrypoint directly from GitHub:

```yaml
packages:
  e1001: github://pdugas/e1001-weather-display/e1001-weather-display-esp32-s3.yaml@main
```

This is also what the `*.factory.yaml` configurations use via `dashboard_import`.

## Configuring the location and data sources

The display title and Home Assistant entity IDs are configurable via `substitutions`. Put these in your device YAML (the one that imports this repo via `packages:`), and adjust as needed:

```yaml
substitutions:
  location_name: "Canton, Georgia"

  weather_entity_id: "weather.nws"
  daily_forecast_entity_id: "sensor.daily_forecast"
  hourly_forecast_entity_id: "sensor.hourly_forecast"
  sun_info_entity_id: "sensor.daily_sun_info"
  apparent_temp_entity_id: "sensor.apparent_temperature"
  allergy_index_entity_id: "sensor.allergy_index_today"
  pollution_level_entity_id: "sensor.u_s_air_pollution_level"
```

