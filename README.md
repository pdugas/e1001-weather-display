# E1001 Weather Display

This is an ESPHome project to turn Seeed Studio's E1001 into a Weather Display managed by Home Assistant.

It includes a GitHub workflow that will automatically build the configuration(s) and then deploys a simple
website via GitHub pages that utilizes [ESP Web Tools](https://esphome.github.io/esp-web-tools/) for users to easily install onto their device.

## Quickstart (Home Assistant)

### 1) Install the Home Assistant template sensors (forecast + dawn/dusk)

ESPHome can’t directly consume the `weather.get_forecasts` service response, so you need a small Home Assistant Template that flattens the forecast into simple sensor attributes.

- **Template file in this repo**: [`home-assistant-e1001-templates.yaml`](https://raw.githubusercontent.com/pdugas/e1001-weather-display/main/home-assistant-e1001-templates.yaml)
- **What it creates**:
  - `sensor.e1001_daily_forecast` (attributes `day0..5`, `condition0..5`, `high0..5`, `low0..5`, `precip0..5`)
  - `sensor.e1001_hourly_forecast` (attributes `hour0..24`, `temp0..24`, `precip0..24`)
  - `sensor.e1001_sun_info` (attributes `dawn`, `dusk`)

To use it:

- Copy the YAML from the linked template file into Home Assistant’s **`template:`** configuration. You can do this either inline in `configuration.yml`/`configuration.yaml`, or by saving it as a separate `templates.yaml` file in your HA config directory (usually `/config/`) and including it.

Example (inline in `configuration.yaml`):

```yaml
template:
  # Paste the contents of `home-assistant-e1001-templates.yaml` here (it starts with `- trigger:`)
  - trigger:
      - platform: time_pattern
        minutes: "/30"
      - platform: homeassistant
        event: start
    # ... rest of the template ...
```

Example (separate `templates.yaml` file):

- Save the contents of `home-assistant-e1001-templates.yaml` as `/config/templates.yaml`
- Add this line to `configuration.yaml`:

```yaml
template: !include templates.yaml
```

- Set `e1001_weather_entity` to your weather entity (e.g. `weather.nws` or `weather.pirateweather`) and `e1001_sun_entity` to your sun entity (usually `sun.sun`)
- Restart Home Assistant (or reload Templates)

### 2) Create your ESPHome device YAML

Create (or edit) a file like `/config/esphome/epaper-display-1.yaml`:

```yaml
esphome:
  name: epaper-display-1
  friendly_name: ePaper Display 1
  # Recommended: avoid mDNS name changes across flashes.
  name_add_mac_suffix: false

substitutions:
  # If set (non-empty), this becomes the title. If empty, the display falls back to the weather entity name.
  location_name: "Chez Dugas"

  # Must match `e1001_weather_entity` in `templates.yaml`.
  weather_entity_id: "weather.pirateweather"

  # Optional integrations
  # Set to an entity id to enable, or leave empty to disable.
  allergy_index_entity_id: "sensor.allergy_index_today"
  pollution_level_entity_id: "sensor.u_s_air_pollution_level"

packages:
  # Pick the entrypoint that matches your board:
  # - e1001-weather-display-esp32.yaml
  # - e1001-weather-display-esp32-c3.yaml
  # - e1001-weather-display-esp32-c6.yaml
  # - e1001-weather-display-esp32-s3.yaml
  #
  # Tip: pin to a commit SHA for stability:
  #   e1001: github://pdugas/e1001-weather-display/e1001-weather-display-esp32-s3.yaml@<sha>
  #
  # Local development option (repo checked out under /config/esphome/):
  #   e1001: !include e1001-weather-display/e1001-weather-display-esp32-s3.yaml
  e1001: github://pdugas/e1001-weather-display/e1001-weather-display-esp32-s3.yaml@main

api:
  encryption:
    key: !secret esphome_api_key

ota:
  - platform: esphome
    password: !secret esphome_ota_password

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  ap:
    ssid: "E1001 Fallback Hotspot"
    password: !secret wifi_ap_password

captive_portal:
```

### 3) Flash the firmware

- **ESP Web Tools (browser “web flasher”)** installs the **factory** firmware from GitHub Pages. It’s great for first install, but it does **not** compile your HA ESPHome YAML.
- To run *your* substitutions/entities (and the exact git ref you pinned), install from **Home Assistant → ESPHome Device Builder**:
  - **Install → Plug into this computer** (USB) is the most reliable
  - OTA works too once the node is stable and awake long enough

## Troubleshooting

- **Forecast sensors show `unknown` / no attributes**
  - Confirm `templates.yaml` uses `service: weather.get_forecasts` (not `action:`) and includes a `homeassistant.start` trigger.
  - Reload Templates or restart Home Assistant.
  - Check the entities exist: `sensor.e1001_daily_forecast`, `sensor.e1001_hourly_forecast`, `sensor.e1001_sun_info`.
- **Display says “Missing Home Assistant templates”**
  - The node can’t read the expected HA entities. Verify the three `sensor.e1001_*` entities above exist and have attributes.
  - Ensure the device is running firmware compiled from your HA ESPHome YAML (see “Flash the firmware”).
- **No logs / device disappears**
  - Deep sleep run duration can be too short for Wi‑Fi + API + sensor reads. Increase `deep_sleep.run_duration` in your device YAML.
