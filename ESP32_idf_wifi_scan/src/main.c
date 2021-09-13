
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"

const uint8_t MAX_AP_RECORDS = 30;

void scan_wifi() {
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true
    };
    printf("scanning started\n");
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    printf("scanning completed\n");
    uint16_t ap_number = 0;
    esp_wifi_scan_get_ap_num(&ap_number);
    printf("AP number %d\n", ap_number);
    wifi_ap_record_t *list = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * ap_number);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_number, list));
    printf("got records\n");

    printf(" ----- SSID------RSSI-----------\n");
    for (int i=0; i < ap_number; i++ ){
        printf("%32s |  %4d |  %7d\n", list[i].ssid, list[i].rssi, list[i].primary);
    }
    free(list);
}

void app_main() {
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    while(1){
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        scan_wifi();
    }
}