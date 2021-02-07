/**
 * Program allow control ESP32 module GPIO pins via html page.
 * Module has been configured as an access point and an http server.
 * 
 * Based on https://github.com/espressif/esp-idf/blob/v4.2/examples/wifi/getting_started/softAP
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include "mdns.h"

#include "driver/gpio.h"

#include "html.h"
#include <OmniWheelPlatform.h>

/**
 *  HTTP headers and web pages.
 */ 
const static char http_html_hdr[] = "HTTP/1.1 200 OK\nContent-type: text/html\n\n";

/**
 *  Access point configuration.
*/
#define EXAMPLE_ESP_WIFI_SSID      "CONFIG_ESP_WIFI_SSID"
#define EXAMPLE_ESP_WIFI_PASS      "CONFIG_ESP_WIFI_PASSWORD"
#define EXAMPLE_ESP_WIFI_CHANNEL   1
#define EXAMPLE_MAX_STA_CONN       1

static const char *TAG = "wifi softAP"; ///< debug tag

/**
 * Handling http GET requests - motor control.
 */
static void http_server_netconn_serve(struct netconn *conn)
{
  struct netbuf *inbuf;
  char *buf;
  u16_t buflen;
  err_t err;
  err = netconn_recv(conn, &inbuf);

  if (err == ERR_OK) {
    netbuf_data(inbuf, (void**)&buf, &buflen);
 		char *request_line = strtok(buf, "\n");
		if(request_line) {
			if(strstr(request_line, "GET / ")) {				
                printf("ASKED FOR INDEX.HTML \n\n");
			} else if (strstr(request_line, "GET /right ")) {
                move(MOVE_DIRECTION_RIGHT, 100);
            } else if (strstr(request_line, "GET /left ")) {
                move(MOVE_DIRECTION_LEFT, 100);
            } else if (strstr(request_line, "GET /forward ")) {
                move(MOVE_DIRECTION_FORWARD, 100);
            } else if (strstr(request_line, "GET /backward ")) {
                move(MOVE_DIRECTION_BACKWARD, 100);
            } else if (strstr(request_line, "GET /stop ")) {
                stop();
            }
        /* Send our default HTML page */
        netconn_write(conn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
        netconn_write(conn, htmlExample, sizeof(htmlExample) - 1, NETCONN_NOCOPY);			   
    }
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);

  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}

/**
 * Create new TCP connection and bind to default http port.
 */   
static void http_server(void *pvParameters)
{
  struct netconn *conn, *newconn;
  err_t err;
  conn = netconn_new(NETCONN_TCP);
  netconn_bind(conn, NULL, 80);
  netconn_listen(conn);
  do {
     err = netconn_accept(conn, &newconn);
     if (err == ERR_OK) {
       http_server_netconn_serve(newconn);
       netconn_delete(newconn);
     }
   } while(err == ERR_OK);
   netconn_close(conn);
   netconn_delete(conn);
}

/**
 * Handling wi-fi state events.
 */
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_START) {
        ESP_LOGI(TAG, "Server starting...");
        // start the HTTP server task
		xTaskCreate(&http_server, "http_server", 2048, NULL, 5, NULL);
		printf("- HTTP server started\n");

    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

/**
 * Configuration mDNS service.
 */ 
void start_mdns_service()
{ 
    esp_err_t err = mdns_init();
    if (err) {
        printf("MDNS Init failed: %d\n", err);
        return;
    }
    mdns_hostname_set("my-esp32");
    mdns_instance_name_set("My ESP32 AP");
}

/**
 * Configuration and initialisation module in Access Point mode 
 * with parameters defined above. 
 */ 
void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    start_mdns_service();
	ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS, EXAMPLE_ESP_WIFI_CHANNEL);
}

/**
 * Main function.
 */ 
void app_main(void)
{
    gpioConfig(&motorDriver1);
    gpioConfig(&motorDriver2);

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
}