/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
*
* The information contained herein is confidential property of Nordic Semiconductor. The use,
* copying, transfer or disclosure of such information is prohibited except by express written
* agreement with Nordic Semiconductor.
*
*/
/** @file
*
* @brief Type definitions and API calls for SoftDevice RPC module.
*
*/

#ifndef SD_RPC_H__
#define SD_RPC_H__

#include "sd_rpc_types.h"
#include "adapter.h"

#include "config/platform.h"
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

SD_RPC_API physical_layer_t *sd_rpc_physical_layer_create_uart(const char * port_name, uint32_t baud_rate, sd_rpc_flow_control_t flow_control, sd_rpc_parity_t parity);
SD_RPC_API data_link_layer_t *sd_rpc_data_link_layer_create_bt_three_wire(physical_layer_t *physical_layer, uint32_t retransmission_interval);
SD_RPC_API transport_layer_t *sd_rpc_transport_layer_create(data_link_layer_t *data_link_layer, uint32_t response_timeout);
SD_RPC_API adapter_t *sd_rpc_adapter_create(transport_layer_t* transport_layer);
SD_RPC_API void sd_rpc_adapter_delete(adapter_t *adapter);

/**@brief Initialize the SoftDevice RPC module.
*
* @note This function must be called prior to the sd_ble_* API commands.
*       The serial port will be attempted opened with the configured serial port settings.
*
* @retval NRF_SUCCESS  The module was opened successfully.
* @retval NRF_ERROR    There was an error opening the module.
*/
SD_RPC_API uint32_t sd_rpc_open(adapter_t *adapter, sd_rpc_status_handler_t status_handler, sd_rpc_evt_handler_t event_handler, sd_rpc_log_handler_t log_handler);


/**@brief Close the SoftDevice RPC module.
*
* @note This function will close the serial port and release allocated resources.
*
* @retval NRF_SUCCESS  The module was closed successfully.
* @retval NRF_ERROR    There was an error closing the module.
*/
SD_RPC_API uint32_t sd_rpc_close(adapter_t *adapter);

/**@brief Set the lowest log level for messages to be logged to handler.
*        Default log handler severity filter is LOG_INFO.
*
* @param[in]  severity_filter  The lowest severity level messages should be logged.
*
* @retval NRF_SUCCESS              severity_filter is valid.
* @retval NRF_ERROR_INVALID_PARAM  severity_filter is not one of the valid enum values
*                                  in app_log_severity_t
*/
SD_RPC_API uint32_t sd_rpc_log_handler_severity_filter_set(adapter_t *adapter, sd_rpc_log_severity_t severity_filter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SD_RPC_H__
