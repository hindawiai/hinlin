<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Siano core API module
 *
 *  This file contains implementation क्रम the पूर्णांकerface to sms core component
 *
 *  author: Uri Shkolnik
 *
 *  Copyright (c), 2005-2008 Siano Mobile Silicon, Inc.
 */

#समावेश "smscoreapi.h"

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <linux/firmware.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "sms-cards.h"
#समावेश "smsir.h"

काष्ठा smscore_device_notअगरyee_t अणु
	काष्ठा list_head entry;
	hotplug_t hotplug;
पूर्ण;

काष्ठा smscore_idlist_t अणु
	काष्ठा list_head entry;
	पूर्णांक		id;
	पूर्णांक		data_type;
पूर्ण;

काष्ठा smscore_client_t अणु
	काष्ठा list_head entry;
	काष्ठा smscore_device_t *coredev;
	व्योम			*context;
	काष्ठा list_head	idlist;
	onresponse_t		onresponse_handler;
	onहटाओ_t		onहटाओ_handler;
पूर्ण;

अटल अक्षर *siano_msgs[] = अणु
	[MSG_TYPE_BASE_VAL                           - MSG_TYPE_BASE_VAL] = "MSG_TYPE_BASE_VAL",
	[MSG_SMS_GET_VERSION_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_VERSION_REQ",
	[MSG_SMS_GET_VERSION_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_VERSION_RES",
	[MSG_SMS_MULTI_BRIDGE_CFG                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_MULTI_BRIDGE_CFG",
	[MSG_SMS_GPIO_CONFIG_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_CONFIG_REQ",
	[MSG_SMS_GPIO_CONFIG_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_CONFIG_RES",
	[MSG_SMS_GPIO_SET_LEVEL_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_SET_LEVEL_REQ",
	[MSG_SMS_GPIO_SET_LEVEL_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_SET_LEVEL_RES",
	[MSG_SMS_GPIO_GET_LEVEL_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_GET_LEVEL_REQ",
	[MSG_SMS_GPIO_GET_LEVEL_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_GET_LEVEL_RES",
	[MSG_SMS_EEPROM_BURN_IND                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_EEPROM_BURN_IND",
	[MSG_SMS_LOG_ENABLE_CHANGE_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_LOG_ENABLE_CHANGE_REQ",
	[MSG_SMS_LOG_ENABLE_CHANGE_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_LOG_ENABLE_CHANGE_RES",
	[MSG_SMS_SET_MAX_TX_MSG_LEN_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_MAX_TX_MSG_LEN_REQ",
	[MSG_SMS_SET_MAX_TX_MSG_LEN_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_MAX_TX_MSG_LEN_RES",
	[MSG_SMS_SPI_HALFDUPLEX_TOKEN_HOST_TO_DEVICE - MSG_TYPE_BASE_VAL] = "MSG_SMS_SPI_HALFDUPLEX_TOKEN_HOST_TO_DEVICE",
	[MSG_SMS_SPI_HALFDUPLEX_TOKEN_DEVICE_TO_HOST - MSG_TYPE_BASE_VAL] = "MSG_SMS_SPI_HALFDUPLEX_TOKEN_DEVICE_TO_HOST",
	[MSG_SMS_BACKGROUND_SCAN_FLAG_CHANGE_REQ     - MSG_TYPE_BASE_VAL] = "MSG_SMS_BACKGROUND_SCAN_FLAG_CHANGE_REQ",
	[MSG_SMS_BACKGROUND_SCAN_FLAG_CHANGE_RES     - MSG_TYPE_BASE_VAL] = "MSG_SMS_BACKGROUND_SCAN_FLAG_CHANGE_RES",
	[MSG_SMS_BACKGROUND_SCAN_SIGNAL_DETECTED_IND - MSG_TYPE_BASE_VAL] = "MSG_SMS_BACKGROUND_SCAN_SIGNAL_DETECTED_IND",
	[MSG_SMS_BACKGROUND_SCAN_NO_SIGNAL_IND       - MSG_TYPE_BASE_VAL] = "MSG_SMS_BACKGROUND_SCAN_NO_SIGNAL_IND",
	[MSG_SMS_CONFIGURE_RF_SWITCH_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_CONFIGURE_RF_SWITCH_REQ",
	[MSG_SMS_CONFIGURE_RF_SWITCH_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_CONFIGURE_RF_SWITCH_RES",
	[MSG_SMS_MRC_PATH_DISCONNECT_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_PATH_DISCONNECT_REQ",
	[MSG_SMS_MRC_PATH_DISCONNECT_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_PATH_DISCONNECT_RES",
	[MSG_SMS_RECEIVE_1SEG_THROUGH_FULLSEG_REQ    - MSG_TYPE_BASE_VAL] = "MSG_SMS_RECEIVE_1SEG_THROUGH_FULLSEG_REQ",
	[MSG_SMS_RECEIVE_1SEG_THROUGH_FULLSEG_RES    - MSG_TYPE_BASE_VAL] = "MSG_SMS_RECEIVE_1SEG_THROUGH_FULLSEG_RES",
	[MSG_SMS_RECEIVE_VHF_VIA_VHF_INPUT_REQ       - MSG_TYPE_BASE_VAL] = "MSG_SMS_RECEIVE_VHF_VIA_VHF_INPUT_REQ",
	[MSG_SMS_RECEIVE_VHF_VIA_VHF_INPUT_RES       - MSG_TYPE_BASE_VAL] = "MSG_SMS_RECEIVE_VHF_VIA_VHF_INPUT_RES",
	[MSG_WR_REG_RFT_REQ                          - MSG_TYPE_BASE_VAL] = "MSG_WR_REG_RFT_REQ",
	[MSG_WR_REG_RFT_RES                          - MSG_TYPE_BASE_VAL] = "MSG_WR_REG_RFT_RES",
	[MSG_RD_REG_RFT_REQ                          - MSG_TYPE_BASE_VAL] = "MSG_RD_REG_RFT_REQ",
	[MSG_RD_REG_RFT_RES                          - MSG_TYPE_BASE_VAL] = "MSG_RD_REG_RFT_RES",
	[MSG_RD_REG_ALL_RFT_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_RD_REG_ALL_RFT_REQ",
	[MSG_RD_REG_ALL_RFT_RES                      - MSG_TYPE_BASE_VAL] = "MSG_RD_REG_ALL_RFT_RES",
	[MSG_HELP_INT                                - MSG_TYPE_BASE_VAL] = "MSG_HELP_INT",
	[MSG_RUN_SCRIPT_INT                          - MSG_TYPE_BASE_VAL] = "MSG_RUN_SCRIPT_INT",
	[MSG_SMS_EWS_INBAND_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_EWS_INBAND_REQ",
	[MSG_SMS_EWS_INBAND_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_EWS_INBAND_RES",
	[MSG_SMS_RFS_SELECT_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_RFS_SELECT_REQ",
	[MSG_SMS_RFS_SELECT_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_RFS_SELECT_RES",
	[MSG_SMS_MB_GET_VER_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_GET_VER_REQ",
	[MSG_SMS_MB_GET_VER_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_GET_VER_RES",
	[MSG_SMS_MB_WRITE_CFGखाता_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_WRITE_CFGFILE_REQ",
	[MSG_SMS_MB_WRITE_CFGखाता_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_WRITE_CFGFILE_RES",
	[MSG_SMS_MB_READ_CFGखाता_REQ                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_READ_CFGFILE_REQ",
	[MSG_SMS_MB_READ_CFGखाता_RES                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_READ_CFGFILE_RES",
	[MSG_SMS_RD_MEM_REQ                          - MSG_TYPE_BASE_VAL] = "MSG_SMS_RD_MEM_REQ",
	[MSG_SMS_RD_MEM_RES                          - MSG_TYPE_BASE_VAL] = "MSG_SMS_RD_MEM_RES",
	[MSG_SMS_WR_MEM_REQ                          - MSG_TYPE_BASE_VAL] = "MSG_SMS_WR_MEM_REQ",
	[MSG_SMS_WR_MEM_RES                          - MSG_TYPE_BASE_VAL] = "MSG_SMS_WR_MEM_RES",
	[MSG_SMS_UPDATE_MEM_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_UPDATE_MEM_REQ",
	[MSG_SMS_UPDATE_MEM_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_UPDATE_MEM_RES",
	[MSG_SMS_ISDBT_ENABLE_FULL_PARAMS_SET_REQ    - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_ENABLE_FULL_PARAMS_SET_REQ",
	[MSG_SMS_ISDBT_ENABLE_FULL_PARAMS_SET_RES    - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_ENABLE_FULL_PARAMS_SET_RES",
	[MSG_SMS_RF_TUNE_REQ                         - MSG_TYPE_BASE_VAL] = "MSG_SMS_RF_TUNE_REQ",
	[MSG_SMS_RF_TUNE_RES                         - MSG_TYPE_BASE_VAL] = "MSG_SMS_RF_TUNE_RES",
	[MSG_SMS_ISDBT_ENABLE_HIGH_MOBILITY_REQ      - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_ENABLE_HIGH_MOBILITY_REQ",
	[MSG_SMS_ISDBT_ENABLE_HIGH_MOBILITY_RES      - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_ENABLE_HIGH_MOBILITY_RES",
	[MSG_SMS_ISDBT_SB_RECEPTION_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_SB_RECEPTION_REQ",
	[MSG_SMS_ISDBT_SB_RECEPTION_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_SB_RECEPTION_RES",
	[MSG_SMS_GENERIC_EPROM_WRITE_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_GENERIC_EPROM_WRITE_REQ",
	[MSG_SMS_GENERIC_EPROM_WRITE_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_GENERIC_EPROM_WRITE_RES",
	[MSG_SMS_GENERIC_EPROM_READ_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_GENERIC_EPROM_READ_REQ",
	[MSG_SMS_GENERIC_EPROM_READ_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_GENERIC_EPROM_READ_RES",
	[MSG_SMS_EEPROM_WRITE_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_EEPROM_WRITE_REQ",
	[MSG_SMS_EEPROM_WRITE_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_EEPROM_WRITE_RES",
	[MSG_SMS_CUSTOM_READ_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_CUSTOM_READ_REQ",
	[MSG_SMS_CUSTOM_READ_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_CUSTOM_READ_RES",
	[MSG_SMS_CUSTOM_WRITE_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_CUSTOM_WRITE_REQ",
	[MSG_SMS_CUSTOM_WRITE_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_CUSTOM_WRITE_RES",
	[MSG_SMS_INIT_DEVICE_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_INIT_DEVICE_REQ",
	[MSG_SMS_INIT_DEVICE_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_INIT_DEVICE_RES",
	[MSG_SMS_ATSC_SET_ALL_IP_REQ                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_SET_ALL_IP_REQ",
	[MSG_SMS_ATSC_SET_ALL_IP_RES                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_SET_ALL_IP_RES",
	[MSG_SMS_ATSC_START_ENSEMBLE_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_START_ENSEMBLE_REQ",
	[MSG_SMS_ATSC_START_ENSEMBLE_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_START_ENSEMBLE_RES",
	[MSG_SMS_SET_OUTPUT_MODE_REQ                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_OUTPUT_MODE_REQ",
	[MSG_SMS_SET_OUTPUT_MODE_RES                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_OUTPUT_MODE_RES",
	[MSG_SMS_ATSC_IP_FILTER_GET_LIST_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_GET_LIST_REQ",
	[MSG_SMS_ATSC_IP_FILTER_GET_LIST_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_GET_LIST_RES",
	[MSG_SMS_SUB_CHANNEL_START_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_SUB_CHANNEL_START_REQ",
	[MSG_SMS_SUB_CHANNEL_START_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_SUB_CHANNEL_START_RES",
	[MSG_SMS_SUB_CHANNEL_STOP_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_SUB_CHANNEL_STOP_REQ",
	[MSG_SMS_SUB_CHANNEL_STOP_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_SUB_CHANNEL_STOP_RES",
	[MSG_SMS_ATSC_IP_FILTER_ADD_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_ADD_REQ",
	[MSG_SMS_ATSC_IP_FILTER_ADD_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_ADD_RES",
	[MSG_SMS_ATSC_IP_FILTER_REMOVE_REQ           - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_REMOVE_REQ",
	[MSG_SMS_ATSC_IP_FILTER_REMOVE_RES           - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_REMOVE_RES",
	[MSG_SMS_ATSC_IP_FILTER_REMOVE_ALL_REQ       - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_REMOVE_ALL_REQ",
	[MSG_SMS_ATSC_IP_FILTER_REMOVE_ALL_RES       - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_IP_FILTER_REMOVE_ALL_RES",
	[MSG_SMS_WAIT_CMD                            - MSG_TYPE_BASE_VAL] = "MSG_SMS_WAIT_CMD",
	[MSG_SMS_ADD_PID_FILTER_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_ADD_PID_FILTER_REQ",
	[MSG_SMS_ADD_PID_FILTER_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_ADD_PID_FILTER_RES",
	[MSG_SMS_REMOVE_PID_FILTER_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_REMOVE_PID_FILTER_REQ",
	[MSG_SMS_REMOVE_PID_FILTER_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_REMOVE_PID_FILTER_RES",
	[MSG_SMS_FAST_INFORMATION_CHANNEL_REQ        - MSG_TYPE_BASE_VAL] = "MSG_SMS_FAST_INFORMATION_CHANNEL_REQ",
	[MSG_SMS_FAST_INFORMATION_CHANNEL_RES        - MSG_TYPE_BASE_VAL] = "MSG_SMS_FAST_INFORMATION_CHANNEL_RES",
	[MSG_SMS_DAB_CHANNEL                         - MSG_TYPE_BASE_VAL] = "MSG_SMS_DAB_CHANNEL",
	[MSG_SMS_GET_PID_FILTER_LIST_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_PID_FILTER_LIST_REQ",
	[MSG_SMS_GET_PID_FILTER_LIST_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_PID_FILTER_LIST_RES",
	[MSG_SMS_POWER_DOWN_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_DOWN_REQ",
	[MSG_SMS_POWER_DOWN_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_DOWN_RES",
	[MSG_SMS_ATSC_SLT_EXIST_IND                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_SLT_EXIST_IND",
	[MSG_SMS_ATSC_NO_SLT_IND                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_ATSC_NO_SLT_IND",
	[MSG_SMS_GET_STATISTICS_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_STATISTICS_REQ",
	[MSG_SMS_GET_STATISTICS_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_STATISTICS_RES",
	[MSG_SMS_SEND_DUMP                           - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_DUMP",
	[MSG_SMS_SCAN_START_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_SCAN_START_REQ",
	[MSG_SMS_SCAN_START_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_SCAN_START_RES",
	[MSG_SMS_SCAN_STOP_REQ                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_SCAN_STOP_REQ",
	[MSG_SMS_SCAN_STOP_RES                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_SCAN_STOP_RES",
	[MSG_SMS_SCAN_PROGRESS_IND                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_SCAN_PROGRESS_IND",
	[MSG_SMS_SCAN_COMPLETE_IND                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_SCAN_COMPLETE_IND",
	[MSG_SMS_LOG_ITEM                            - MSG_TYPE_BASE_VAL] = "MSG_SMS_LOG_ITEM",
	[MSG_SMS_DAB_SUBCHANNEL_RECONFIG_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_DAB_SUBCHANNEL_RECONFIG_REQ",
	[MSG_SMS_DAB_SUBCHANNEL_RECONFIG_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_DAB_SUBCHANNEL_RECONFIG_RES",
	[MSG_SMS_HO_PER_SLICES_IND                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_PER_SLICES_IND",
	[MSG_SMS_HO_INBAND_POWER_IND                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_INBAND_POWER_IND",
	[MSG_SMS_MANUAL_DEMOD_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_MANUAL_DEMOD_REQ",
	[MSG_SMS_HO_TUNE_ON_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_TUNE_ON_REQ",
	[MSG_SMS_HO_TUNE_ON_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_TUNE_ON_RES",
	[MSG_SMS_HO_TUNE_OFF_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_TUNE_OFF_REQ",
	[MSG_SMS_HO_TUNE_OFF_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_TUNE_OFF_RES",
	[MSG_SMS_HO_PEEK_FREQ_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_PEEK_FREQ_REQ",
	[MSG_SMS_HO_PEEK_FREQ_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_PEEK_FREQ_RES",
	[MSG_SMS_HO_PEEK_FREQ_IND                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_HO_PEEK_FREQ_IND",
	[MSG_SMS_MB_ATTEN_SET_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_ATTEN_SET_REQ",
	[MSG_SMS_MB_ATTEN_SET_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_MB_ATTEN_SET_RES",
	[MSG_SMS_ENABLE_STAT_IN_I2C_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_ENABLE_STAT_IN_I2C_REQ",
	[MSG_SMS_ENABLE_STAT_IN_I2C_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_ENABLE_STAT_IN_I2C_RES",
	[MSG_SMS_SET_ANTENNA_CONFIG_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_ANTENNA_CONFIG_REQ",
	[MSG_SMS_SET_ANTENNA_CONFIG_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_ANTENNA_CONFIG_RES",
	[MSG_SMS_GET_STATISTICS_EX_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_STATISTICS_EX_REQ",
	[MSG_SMS_GET_STATISTICS_EX_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_STATISTICS_EX_RES",
	[MSG_SMS_SLEEP_RESUME_COMP_IND               - MSG_TYPE_BASE_VAL] = "MSG_SMS_SLEEP_RESUME_COMP_IND",
	[MSG_SMS_SWITCH_HOST_INTERFACE_REQ           - MSG_TYPE_BASE_VAL] = "MSG_SMS_SWITCH_HOST_INTERFACE_REQ",
	[MSG_SMS_SWITCH_HOST_INTERFACE_RES           - MSG_TYPE_BASE_VAL] = "MSG_SMS_SWITCH_HOST_INTERFACE_RES",
	[MSG_SMS_DATA_DOWNLOAD_REQ                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_DOWNLOAD_REQ",
	[MSG_SMS_DATA_DOWNLOAD_RES                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_DOWNLOAD_RES",
	[MSG_SMS_DATA_VALIDITY_REQ                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_VALIDITY_REQ",
	[MSG_SMS_DATA_VALIDITY_RES                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_VALIDITY_RES",
	[MSG_SMS_SWDOWNLOAD_TRIGGER_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_SWDOWNLOAD_TRIGGER_REQ",
	[MSG_SMS_SWDOWNLOAD_TRIGGER_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_SWDOWNLOAD_TRIGGER_RES",
	[MSG_SMS_SWDOWNLOAD_BACKDOOR_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_SWDOWNLOAD_BACKDOOR_REQ",
	[MSG_SMS_SWDOWNLOAD_BACKDOOR_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_SWDOWNLOAD_BACKDOOR_RES",
	[MSG_SMS_GET_VERSION_EX_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_VERSION_EX_REQ",
	[MSG_SMS_GET_VERSION_EX_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_VERSION_EX_RES",
	[MSG_SMS_CLOCK_OUTPUT_CONFIG_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_CLOCK_OUTPUT_CONFIG_REQ",
	[MSG_SMS_CLOCK_OUTPUT_CONFIG_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_CLOCK_OUTPUT_CONFIG_RES",
	[MSG_SMS_I2C_SET_FREQ_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_I2C_SET_FREQ_REQ",
	[MSG_SMS_I2C_SET_FREQ_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_I2C_SET_FREQ_RES",
	[MSG_SMS_GENERIC_I2C_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_GENERIC_I2C_REQ",
	[MSG_SMS_GENERIC_I2C_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_GENERIC_I2C_RES",
	[MSG_SMS_DVBT_BDA_DATA                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_DVBT_BDA_DATA",
	[MSG_SW_RELOAD_REQ                           - MSG_TYPE_BASE_VAL] = "MSG_SW_RELOAD_REQ",
	[MSG_SMS_DATA_MSG                            - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_MSG",
	[MSG_TABLE_UPLOAD_REQ                        - MSG_TYPE_BASE_VAL] = "MSG_TABLE_UPLOAD_REQ",
	[MSG_TABLE_UPLOAD_RES                        - MSG_TYPE_BASE_VAL] = "MSG_TABLE_UPLOAD_RES",
	[MSG_SW_RELOAD_START_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SW_RELOAD_START_REQ",
	[MSG_SW_RELOAD_START_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SW_RELOAD_START_RES",
	[MSG_SW_RELOAD_EXEC_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SW_RELOAD_EXEC_REQ",
	[MSG_SW_RELOAD_EXEC_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SW_RELOAD_EXEC_RES",
	[MSG_SMS_SPI_INT_LINE_SET_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_SPI_INT_LINE_SET_REQ",
	[MSG_SMS_SPI_INT_LINE_SET_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_SPI_INT_LINE_SET_RES",
	[MSG_SMS_GPIO_CONFIG_EX_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_CONFIG_EX_REQ",
	[MSG_SMS_GPIO_CONFIG_EX_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_GPIO_CONFIG_EX_RES",
	[MSG_SMS_WATCHDOG_ACT_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_WATCHDOG_ACT_REQ",
	[MSG_SMS_WATCHDOG_ACT_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_WATCHDOG_ACT_RES",
	[MSG_SMS_LOOPBACK_REQ                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_LOOPBACK_REQ",
	[MSG_SMS_LOOPBACK_RES                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_LOOPBACK_RES",
	[MSG_SMS_RAW_CAPTURE_START_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_RAW_CAPTURE_START_REQ",
	[MSG_SMS_RAW_CAPTURE_START_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_RAW_CAPTURE_START_RES",
	[MSG_SMS_RAW_CAPTURE_ABORT_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_RAW_CAPTURE_ABORT_REQ",
	[MSG_SMS_RAW_CAPTURE_ABORT_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_RAW_CAPTURE_ABORT_RES",
	[MSG_SMS_RAW_CAPTURE_COMPLETE_IND            - MSG_TYPE_BASE_VAL] = "MSG_SMS_RAW_CAPTURE_COMPLETE_IND",
	[MSG_SMS_DATA_PUMP_IND                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_PUMP_IND",
	[MSG_SMS_DATA_PUMP_REQ                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_PUMP_REQ",
	[MSG_SMS_DATA_PUMP_RES                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_DATA_PUMP_RES",
	[MSG_SMS_FLASH_DL_REQ                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_FLASH_DL_REQ",
	[MSG_SMS_EXEC_TEST_1_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_EXEC_TEST_1_REQ",
	[MSG_SMS_EXEC_TEST_1_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_EXEC_TEST_1_RES",
	[MSG_SMS_ENABLE_TS_INTERFACE_REQ             - MSG_TYPE_BASE_VAL] = "MSG_SMS_ENABLE_TS_INTERFACE_REQ",
	[MSG_SMS_ENABLE_TS_INTERFACE_RES             - MSG_TYPE_BASE_VAL] = "MSG_SMS_ENABLE_TS_INTERFACE_RES",
	[MSG_SMS_SPI_SET_BUS_WIDTH_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_SPI_SET_BUS_WIDTH_REQ",
	[MSG_SMS_SPI_SET_BUS_WIDTH_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_SPI_SET_BUS_WIDTH_RES",
	[MSG_SMS_SEND_EMM_REQ                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_EMM_REQ",
	[MSG_SMS_SEND_EMM_RES                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_EMM_RES",
	[MSG_SMS_DISABLE_TS_INTERFACE_REQ            - MSG_TYPE_BASE_VAL] = "MSG_SMS_DISABLE_TS_INTERFACE_REQ",
	[MSG_SMS_DISABLE_TS_INTERFACE_RES            - MSG_TYPE_BASE_VAL] = "MSG_SMS_DISABLE_TS_INTERFACE_RES",
	[MSG_SMS_IS_BUF_FREE_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_IS_BUF_FREE_REQ",
	[MSG_SMS_IS_BUF_FREE_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_IS_BUF_FREE_RES",
	[MSG_SMS_EXT_ANTENNA_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_EXT_ANTENNA_REQ",
	[MSG_SMS_EXT_ANTENNA_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_EXT_ANTENNA_RES",
	[MSG_SMS_CMMB_GET_NET_OF_FREQ_REQ_OBSOLETE   - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_NET_OF_FREQ_REQ_OBSOLETE",
	[MSG_SMS_CMMB_GET_NET_OF_FREQ_RES_OBSOLETE   - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_NET_OF_FREQ_RES_OBSOLETE",
	[MSG_SMS_BATTERY_LEVEL_REQ                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_BATTERY_LEVEL_REQ",
	[MSG_SMS_BATTERY_LEVEL_RES                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_BATTERY_LEVEL_RES",
	[MSG_SMS_CMMB_INJECT_TABLE_REQ_OBSOLETE      - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_INJECT_TABLE_REQ_OBSOLETE",
	[MSG_SMS_CMMB_INJECT_TABLE_RES_OBSOLETE      - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_INJECT_TABLE_RES_OBSOLETE",
	[MSG_SMS_FM_RADIO_BLOCK_IND                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_FM_RADIO_BLOCK_IND",
	[MSG_SMS_HOST_NOTIFICATION_IND               - MSG_TYPE_BASE_VAL] = "MSG_SMS_HOST_NOTIFICATION_IND",
	[MSG_SMS_CMMB_GET_CONTROL_TABLE_REQ_OBSOLETE - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_CONTROL_TABLE_REQ_OBSOLETE",
	[MSG_SMS_CMMB_GET_CONTROL_TABLE_RES_OBSOLETE - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_CONTROL_TABLE_RES_OBSOLETE",
	[MSG_SMS_CMMB_GET_NETWORKS_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_NETWORKS_REQ",
	[MSG_SMS_CMMB_GET_NETWORKS_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_NETWORKS_RES",
	[MSG_SMS_CMMB_START_SERVICE_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_START_SERVICE_REQ",
	[MSG_SMS_CMMB_START_SERVICE_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_START_SERVICE_RES",
	[MSG_SMS_CMMB_STOP_SERVICE_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_STOP_SERVICE_REQ",
	[MSG_SMS_CMMB_STOP_SERVICE_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_STOP_SERVICE_RES",
	[MSG_SMS_CMMB_ADD_CHANNEL_FILTER_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_ADD_CHANNEL_FILTER_REQ",
	[MSG_SMS_CMMB_ADD_CHANNEL_FILTER_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_ADD_CHANNEL_FILTER_RES",
	[MSG_SMS_CMMB_REMOVE_CHANNEL_FILTER_REQ      - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_REMOVE_CHANNEL_FILTER_REQ",
	[MSG_SMS_CMMB_REMOVE_CHANNEL_FILTER_RES      - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_REMOVE_CHANNEL_FILTER_RES",
	[MSG_SMS_CMMB_START_CONTROL_INFO_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_START_CONTROL_INFO_REQ",
	[MSG_SMS_CMMB_START_CONTROL_INFO_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_START_CONTROL_INFO_RES",
	[MSG_SMS_CMMB_STOP_CONTROL_INFO_REQ          - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_STOP_CONTROL_INFO_REQ",
	[MSG_SMS_CMMB_STOP_CONTROL_INFO_RES          - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_STOP_CONTROL_INFO_RES",
	[MSG_SMS_ISDBT_TUNE_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_TUNE_REQ",
	[MSG_SMS_ISDBT_TUNE_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_ISDBT_TUNE_RES",
	[MSG_SMS_TRANSMISSION_IND                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_TRANSMISSION_IND",
	[MSG_SMS_PID_STATISTICS_IND                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_PID_STATISTICS_IND",
	[MSG_SMS_POWER_DOWN_IND                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_DOWN_IND",
	[MSG_SMS_POWER_DOWN_CONF                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_DOWN_CONF",
	[MSG_SMS_POWER_UP_IND                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_UP_IND",
	[MSG_SMS_POWER_UP_CONF                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_UP_CONF",
	[MSG_SMS_POWER_MODE_SET_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_MODE_SET_REQ",
	[MSG_SMS_POWER_MODE_SET_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_POWER_MODE_SET_RES",
	[MSG_SMS_DEBUG_HOST_EVENT_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_DEBUG_HOST_EVENT_REQ",
	[MSG_SMS_DEBUG_HOST_EVENT_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_DEBUG_HOST_EVENT_RES",
	[MSG_SMS_NEW_CRYSTAL_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_NEW_CRYSTAL_REQ",
	[MSG_SMS_NEW_CRYSTAL_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_NEW_CRYSTAL_RES",
	[MSG_SMS_CONFIG_SPI_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_CONFIG_SPI_REQ",
	[MSG_SMS_CONFIG_SPI_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_CONFIG_SPI_RES",
	[MSG_SMS_I2C_SHORT_STAT_IND                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_I2C_SHORT_STAT_IND",
	[MSG_SMS_START_IR_REQ                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_START_IR_REQ",
	[MSG_SMS_START_IR_RES                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_START_IR_RES",
	[MSG_SMS_IR_SAMPLES_IND                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_IR_SAMPLES_IND",
	[MSG_SMS_CMMB_CA_SERVICE_IND                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_CA_SERVICE_IND",
	[MSG_SMS_SLAVE_DEVICE_DETECTED               - MSG_TYPE_BASE_VAL] = "MSG_SMS_SLAVE_DEVICE_DETECTED",
	[MSG_SMS_INTERFACE_LOCK_IND                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_INTERFACE_LOCK_IND",
	[MSG_SMS_INTERFACE_UNLOCK_IND                - MSG_TYPE_BASE_VAL] = "MSG_SMS_INTERFACE_UNLOCK_IND",
	[MSG_SMS_SEND_ROSUM_BUFF_REQ                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_ROSUM_BUFF_REQ",
	[MSG_SMS_SEND_ROSUM_BUFF_RES                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_ROSUM_BUFF_RES",
	[MSG_SMS_ROSUM_BUFF                          - MSG_TYPE_BASE_VAL] = "MSG_SMS_ROSUM_BUFF",
	[MSG_SMS_SET_AES128_KEY_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_AES128_KEY_REQ",
	[MSG_SMS_SET_AES128_KEY_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_AES128_KEY_RES",
	[MSG_SMS_MBBMS_WRITE_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_MBBMS_WRITE_REQ",
	[MSG_SMS_MBBMS_WRITE_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_MBBMS_WRITE_RES",
	[MSG_SMS_MBBMS_READ_IND                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_MBBMS_READ_IND",
	[MSG_SMS_IQ_STREAM_START_REQ                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_IQ_STREAM_START_REQ",
	[MSG_SMS_IQ_STREAM_START_RES                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_IQ_STREAM_START_RES",
	[MSG_SMS_IQ_STREAM_STOP_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_IQ_STREAM_STOP_REQ",
	[MSG_SMS_IQ_STREAM_STOP_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_IQ_STREAM_STOP_RES",
	[MSG_SMS_IQ_STREAM_DATA_BLOCK                - MSG_TYPE_BASE_VAL] = "MSG_SMS_IQ_STREAM_DATA_BLOCK",
	[MSG_SMS_GET_EEPROM_VERSION_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_EEPROM_VERSION_REQ",
	[MSG_SMS_GET_EEPROM_VERSION_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_GET_EEPROM_VERSION_RES",
	[MSG_SMS_SIGNAL_DETECTED_IND                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SIGNAL_DETECTED_IND",
	[MSG_SMS_NO_SIGNAL_IND                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_NO_SIGNAL_IND",
	[MSG_SMS_MRC_SHUTDOWN_SLAVE_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_SHUTDOWN_SLAVE_REQ",
	[MSG_SMS_MRC_SHUTDOWN_SLAVE_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_SHUTDOWN_SLAVE_RES",
	[MSG_SMS_MRC_BRINGUP_SLAVE_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_BRINGUP_SLAVE_REQ",
	[MSG_SMS_MRC_BRINGUP_SLAVE_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_BRINGUP_SLAVE_RES",
	[MSG_SMS_EXTERNAL_LNA_CTRL_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_EXTERNAL_LNA_CTRL_REQ",
	[MSG_SMS_EXTERNAL_LNA_CTRL_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_EXTERNAL_LNA_CTRL_RES",
	[MSG_SMS_SET_PERIODIC_STATISTICS_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_PERIODIC_STATISTICS_REQ",
	[MSG_SMS_SET_PERIODIC_STATISTICS_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_SET_PERIODIC_STATISTICS_RES",
	[MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_REQ        - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_REQ",
	[MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_RES        - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_RES",
	[LOCAL_TUNE                                  - MSG_TYPE_BASE_VAL] = "LOCAL_TUNE",
	[LOCAL_IFFT_H_ICI                            - MSG_TYPE_BASE_VAL] = "LOCAL_IFFT_H_ICI",
	[MSG_RESYNC_REQ                              - MSG_TYPE_BASE_VAL] = "MSG_RESYNC_REQ",
	[MSG_SMS_CMMB_GET_MRC_STATISTICS_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_MRC_STATISTICS_REQ",
	[MSG_SMS_CMMB_GET_MRC_STATISTICS_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_MRC_STATISTICS_RES",
	[MSG_SMS_LOG_EX_ITEM                         - MSG_TYPE_BASE_VAL] = "MSG_SMS_LOG_EX_ITEM",
	[MSG_SMS_DEVICE_DATA_LOSS_IND                - MSG_TYPE_BASE_VAL] = "MSG_SMS_DEVICE_DATA_LOSS_IND",
	[MSG_SMS_MRC_WATCHDOG_TRIGGERED_IND          - MSG_TYPE_BASE_VAL] = "MSG_SMS_MRC_WATCHDOG_TRIGGERED_IND",
	[MSG_SMS_USER_MSG_REQ                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_USER_MSG_REQ",
	[MSG_SMS_USER_MSG_RES                        - MSG_TYPE_BASE_VAL] = "MSG_SMS_USER_MSG_RES",
	[MSG_SMS_SMART_CARD_INIT_REQ                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SMART_CARD_INIT_REQ",
	[MSG_SMS_SMART_CARD_INIT_RES                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SMART_CARD_INIT_RES",
	[MSG_SMS_SMART_CARD_WRITE_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_SMART_CARD_WRITE_REQ",
	[MSG_SMS_SMART_CARD_WRITE_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_SMART_CARD_WRITE_RES",
	[MSG_SMS_SMART_CARD_READ_IND                 - MSG_TYPE_BASE_VAL] = "MSG_SMS_SMART_CARD_READ_IND",
	[MSG_SMS_TSE_ENABLE_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_TSE_ENABLE_REQ",
	[MSG_SMS_TSE_ENABLE_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_TSE_ENABLE_RES",
	[MSG_SMS_CMMB_GET_SHORT_STATISTICS_REQ       - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_SHORT_STATISTICS_REQ",
	[MSG_SMS_CMMB_GET_SHORT_STATISTICS_RES       - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_GET_SHORT_STATISTICS_RES",
	[MSG_SMS_LED_CONFIG_REQ                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_LED_CONFIG_REQ",
	[MSG_SMS_LED_CONFIG_RES                      - MSG_TYPE_BASE_VAL] = "MSG_SMS_LED_CONFIG_RES",
	[MSG_PWM_ANTENNA_REQ                         - MSG_TYPE_BASE_VAL] = "MSG_PWM_ANTENNA_REQ",
	[MSG_PWM_ANTENNA_RES                         - MSG_TYPE_BASE_VAL] = "MSG_PWM_ANTENNA_RES",
	[MSG_SMS_CMMB_SMD_SN_REQ                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SMD_SN_REQ",
	[MSG_SMS_CMMB_SMD_SN_RES                     - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SMD_SN_RES",
	[MSG_SMS_CMMB_SET_CA_CW_REQ                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SET_CA_CW_REQ",
	[MSG_SMS_CMMB_SET_CA_CW_RES                  - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SET_CA_CW_RES",
	[MSG_SMS_CMMB_SET_CA_SALT_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SET_CA_SALT_REQ",
	[MSG_SMS_CMMB_SET_CA_SALT_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_CMMB_SET_CA_SALT_RES",
	[MSG_SMS_NSCD_INIT_REQ                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_NSCD_INIT_REQ",
	[MSG_SMS_NSCD_INIT_RES                       - MSG_TYPE_BASE_VAL] = "MSG_SMS_NSCD_INIT_RES",
	[MSG_SMS_NSCD_PROCESS_SECTION_REQ            - MSG_TYPE_BASE_VAL] = "MSG_SMS_NSCD_PROCESS_SECTION_REQ",
	[MSG_SMS_NSCD_PROCESS_SECTION_RES            - MSG_TYPE_BASE_VAL] = "MSG_SMS_NSCD_PROCESS_SECTION_RES",
	[MSG_SMS_DBD_CREATE_OBJECT_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_CREATE_OBJECT_REQ",
	[MSG_SMS_DBD_CREATE_OBJECT_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_CREATE_OBJECT_RES",
	[MSG_SMS_DBD_CONFIGURE_REQ                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_CONFIGURE_REQ",
	[MSG_SMS_DBD_CONFIGURE_RES                   - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_CONFIGURE_RES",
	[MSG_SMS_DBD_SET_KEYS_REQ                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_SET_KEYS_REQ",
	[MSG_SMS_DBD_SET_KEYS_RES                    - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_SET_KEYS_RES",
	[MSG_SMS_DBD_PROCESS_HEADER_REQ              - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_PROCESS_HEADER_REQ",
	[MSG_SMS_DBD_PROCESS_HEADER_RES              - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_PROCESS_HEADER_RES",
	[MSG_SMS_DBD_PROCESS_DATA_REQ                - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_PROCESS_DATA_REQ",
	[MSG_SMS_DBD_PROCESS_DATA_RES                - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_PROCESS_DATA_RES",
	[MSG_SMS_DBD_PROCESS_GET_DATA_REQ            - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_PROCESS_GET_DATA_REQ",
	[MSG_SMS_DBD_PROCESS_GET_DATA_RES            - MSG_TYPE_BASE_VAL] = "MSG_SMS_DBD_PROCESS_GET_DATA_RES",
	[MSG_SMS_NSCD_OPEN_SESSION_REQ               - MSG_TYPE_BASE_VAL] = "MSG_SMS_NSCD_OPEN_SESSION_REQ",
	[MSG_SMS_NSCD_OPEN_SESSION_RES               - MSG_TYPE_BASE_VAL] = "MSG_SMS_NSCD_OPEN_SESSION_RES",
	[MSG_SMS_SEND_HOST_DATA_TO_DEMUX_REQ         - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_HOST_DATA_TO_DEMUX_REQ",
	[MSG_SMS_SEND_HOST_DATA_TO_DEMUX_RES         - MSG_TYPE_BASE_VAL] = "MSG_SMS_SEND_HOST_DATA_TO_DEMUX_RES",
	[MSG_LAST_MSG_TYPE                           - MSG_TYPE_BASE_VAL] = "MSG_LAST_MSG_TYPE",
पूर्ण;

अक्षर *smscore_translate_msg(क्रमागत msg_types msgtype)
अणु
	पूर्णांक i = msgtype - MSG_TYPE_BASE_VAL;
	अक्षर *msg;

	अगर (i < 0 || i >= ARRAY_SIZE(siano_msgs))
		वापस "Unknown msg type";

	msg = siano_msgs[i];

	अगर (!*msg)
		वापस "Unknown msg type";

	वापस msg;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_translate_msg);

व्योम smscore_set_board_id(काष्ठा smscore_device_t *core, पूर्णांक id)
अणु
	core->board_id = id;
पूर्ण

पूर्णांक smscore_led_state(काष्ठा smscore_device_t *core, पूर्णांक led)
अणु
	अगर (led >= 0)
		core->led_state = led;
	वापस core->led_state;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_set_board_id);

पूर्णांक smscore_get_board_id(काष्ठा smscore_device_t *core)
अणु
	वापस core->board_id;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_get_board_id);

काष्ठा smscore_registry_entry_t अणु
	काष्ठा list_head entry;
	अक्षर devpath[32];
	पूर्णांक mode;
	क्रमागत sms_device_type_st	type;
पूर्ण;

अटल काष्ठा list_head g_smscore_notअगरyees;
अटल काष्ठा list_head g_smscore_devices;
अटल काष्ठा mutex g_smscore_deviceslock;

अटल काष्ठा list_head g_smscore_registry;
अटल काष्ठा mutex g_smscore_registrylock;

अटल पूर्णांक शेष_mode = DEVICE_MODE_NONE;

module_param(शेष_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(शेष_mode, "default firmware id (device mode)");

अटल काष्ठा smscore_registry_entry_t *smscore_find_registry(अक्षर *devpath)
अणु
	काष्ठा smscore_registry_entry_t *entry;
	काष्ठा list_head *next;

	mutex_lock(&g_smscore_registrylock);
	क्रम (next = g_smscore_registry.next;
	     next != &g_smscore_registry;
	     next = next->next) अणु
		entry = (काष्ठा smscore_registry_entry_t *) next;
		अगर (!म_भेदन(entry->devpath, devpath, माप(entry->devpath))) अणु
			mutex_unlock(&g_smscore_registrylock);
			वापस entry;
		पूर्ण
	पूर्ण
	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (entry) अणु
		entry->mode = शेष_mode;
		strscpy(entry->devpath, devpath, माप(entry->devpath));
		list_add(&entry->entry, &g_smscore_registry);
	पूर्ण अन्यथा
		pr_err("failed to create smscore_registry.\n");
	mutex_unlock(&g_smscore_registrylock);
	वापस entry;
पूर्ण

पूर्णांक smscore_registry_geपंचांगode(अक्षर *devpath)
अणु
	काष्ठा smscore_registry_entry_t *entry;

	entry = smscore_find_registry(devpath);
	अगर (entry)
		वापस entry->mode;
	अन्यथा
		pr_err("No registry found.\n");

	वापस शेष_mode;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_registry_geपंचांगode);

अटल क्रमागत sms_device_type_st smscore_registry_gettype(अक्षर *devpath)
अणु
	काष्ठा smscore_registry_entry_t *entry;

	entry = smscore_find_registry(devpath);
	अगर (entry)
		वापस entry->type;
	अन्यथा
		pr_err("No registry found.\n");

	वापस -EINVAL;
पूर्ण

अटल व्योम smscore_registry_seपंचांगode(अक्षर *devpath, पूर्णांक mode)
अणु
	काष्ठा smscore_registry_entry_t *entry;

	entry = smscore_find_registry(devpath);
	अगर (entry)
		entry->mode = mode;
	अन्यथा
		pr_err("No registry found.\n");
पूर्ण

अटल व्योम smscore_registry_settype(अक्षर *devpath,
				     क्रमागत sms_device_type_st type)
अणु
	काष्ठा smscore_registry_entry_t *entry;

	entry = smscore_find_registry(devpath);
	अगर (entry)
		entry->type = type;
	अन्यथा
		pr_err("No registry found.\n");
पूर्ण


अटल व्योम list_add_locked(काष्ठा list_head *new, काष्ठा list_head *head,
			    spinlock_t *lock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);

	list_add(new, head);

	spin_unlock_irqrestore(lock, flags);
पूर्ण

/*
 * रेजिस्टर a client callback that called when device plugged in/unplugged
 * NOTE: अगर devices exist callback is called immediately क्रम each device
 *
 * @param hotplug callback
 *
 * वापस: 0 on success, <0 on error.
 */
पूर्णांक smscore_रेजिस्टर_hotplug(hotplug_t hotplug)
अणु
	काष्ठा smscore_device_notअगरyee_t *notअगरyee;
	काष्ठा list_head *next, *first;
	पूर्णांक rc = 0;

	mutex_lock(&g_smscore_deviceslock);
	notअगरyee = kदो_स्मृति(माप(*notअगरyee), GFP_KERNEL);
	अगर (notअगरyee) अणु
		/* now notअगरy callback about existing devices */
		first = &g_smscore_devices;
		क्रम (next = first->next;
		     next != first && !rc;
		     next = next->next) अणु
			काष्ठा smscore_device_t *coredev =
				(काष्ठा smscore_device_t *) next;
			rc = hotplug(coredev, coredev->device, 1);
		पूर्ण

		अगर (rc >= 0) अणु
			notअगरyee->hotplug = hotplug;
			list_add(&notअगरyee->entry, &g_smscore_notअगरyees);
		पूर्ण अन्यथा
			kमुक्त(notअगरyee);
	पूर्ण अन्यथा
		rc = -ENOMEM;

	mutex_unlock(&g_smscore_deviceslock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_रेजिस्टर_hotplug);

/*
 * unरेजिस्टर a client callback that called when device plugged in/unplugged
 *
 * @param hotplug callback
 *
 */
व्योम smscore_unरेजिस्टर_hotplug(hotplug_t hotplug)
अणु
	काष्ठा list_head *next, *first;

	mutex_lock(&g_smscore_deviceslock);

	first = &g_smscore_notअगरyees;

	क्रम (next = first->next; next != first;) अणु
		काष्ठा smscore_device_notअगरyee_t *notअगरyee =
			(काष्ठा smscore_device_notअगरyee_t *) next;
		next = next->next;

		अगर (notअगरyee->hotplug == hotplug) अणु
			list_del(&notअगरyee->entry);
			kमुक्त(notअगरyee);
		पूर्ण
	पूर्ण

	mutex_unlock(&g_smscore_deviceslock);
पूर्ण
EXPORT_SYMBOL_GPL(smscore_unरेजिस्टर_hotplug);

अटल व्योम smscore_notअगरy_clients(काष्ठा smscore_device_t *coredev)
अणु
	काष्ठा smscore_client_t *client;

	/* the client must call smscore_unरेजिस्टर_client from हटाओ handler */
	जबतक (!list_empty(&coredev->clients)) अणु
		client = (काष्ठा smscore_client_t *) coredev->clients.next;
		client->onहटाओ_handler(client->context);
	पूर्ण
पूर्ण

अटल पूर्णांक smscore_notअगरy_callbacks(काष्ठा smscore_device_t *coredev,
				    काष्ठा device *device, पूर्णांक arrival)
अणु
	काष्ठा smscore_device_notअगरyee_t *elem;
	पूर्णांक rc = 0;

	/* note: must be called under g_deviceslock */

	list_क्रम_each_entry(elem, &g_smscore_notअगरyees, entry) अणु
		rc = elem->hotplug(coredev, device, arrival);
		अगर (rc < 0)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा
smscore_buffer_t *smscore_createbuffer(u8 *buffer, व्योम *common_buffer,
				       dma_addr_t common_buffer_phys)
अणु
	काष्ठा smscore_buffer_t *cb;

	cb = kzalloc(माप(*cb), GFP_KERNEL);
	अगर (!cb)
		वापस शून्य;

	cb->p = buffer;
	cb->offset_in_common = buffer - (u8 *) common_buffer;
	अगर (common_buffer_phys)
		cb->phys = common_buffer_phys + cb->offset_in_common;

	वापस cb;
पूर्ण

/*
 * creates coredev object क्रम a device, prepares buffers,
 * creates buffer mappings, notअगरies रेजिस्टरed hotplugs about new device.
 *
 * @param params device poपूर्णांकer to काष्ठा with device specअगरic parameters
 *               and handlers
 * @param coredev poपूर्णांकer to a value that receives created coredev object
 *
 * वापस: 0 on success, <0 on error.
 */
पूर्णांक smscore_रेजिस्टर_device(काष्ठा smsdevice_params_t *params,
			    काष्ठा smscore_device_t **coredev,
			    gfp_t gfp_buf_flags,
			    व्योम *mdev)
अणु
	काष्ठा smscore_device_t *dev;
	u8 *buffer;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	dev->media_dev = mdev;
#पूर्ण_अगर
	dev->gfp_buf_flags = gfp_buf_flags;

	/* init list entry so it could be safe in smscore_unरेजिस्टर_device */
	INIT_LIST_HEAD(&dev->entry);

	/* init queues */
	INIT_LIST_HEAD(&dev->clients);
	INIT_LIST_HEAD(&dev->buffers);

	/* init locks */
	spin_lock_init(&dev->clientslock);
	spin_lock_init(&dev->bufferslock);

	/* init completion events */
	init_completion(&dev->version_ex_करोne);
	init_completion(&dev->data_करोwnload_करोne);
	init_completion(&dev->data_validity_करोne);
	init_completion(&dev->trigger_करोne);
	init_completion(&dev->init_device_करोne);
	init_completion(&dev->reload_start_करोne);
	init_completion(&dev->resume_करोne);
	init_completion(&dev->gpio_configuration_करोne);
	init_completion(&dev->gpio_set_level_करोne);
	init_completion(&dev->gpio_get_level_करोne);
	init_completion(&dev->ir_init_करोne);

	/* Buffer management */
	init_रुकोqueue_head(&dev->buffer_mng_रुकोq);

	/* alloc common buffer */
	dev->common_buffer_size = params->buffer_size * params->num_buffers;
	अगर (params->usb_device)
		buffer = kzalloc(dev->common_buffer_size, GFP_KERNEL);
	अन्यथा
		buffer = dma_alloc_coherent(params->device,
					    dev->common_buffer_size,
					    &dev->common_buffer_phys,
					    GFP_KERNEL | dev->gfp_buf_flags);
	अगर (!buffer) अणु
		smscore_unरेजिस्टर_device(dev);
		वापस -ENOMEM;
	पूर्ण
	dev->common_buffer = buffer;

	/* prepare dma buffers */
	क्रम (; dev->num_buffers < params->num_buffers;
	     dev->num_buffers++, buffer += params->buffer_size) अणु
		काष्ठा smscore_buffer_t *cb;

		cb = smscore_createbuffer(buffer, dev->common_buffer,
					  dev->common_buffer_phys);
		अगर (!cb) अणु
			smscore_unरेजिस्टर_device(dev);
			वापस -ENOMEM;
		पूर्ण

		smscore_putbuffer(dev, cb);
	पूर्ण

	pr_debug("allocated %d buffers\n", dev->num_buffers);

	dev->mode = DEVICE_MODE_NONE;
	dev->board_id = SMS_BOARD_UNKNOWN;
	dev->context = params->context;
	dev->device = params->device;
	dev->usb_device = params->usb_device;
	dev->seपंचांगode_handler = params->seपंचांगode_handler;
	dev->detecपंचांगode_handler = params->detecपंचांगode_handler;
	dev->sendrequest_handler = params->sendrequest_handler;
	dev->preload_handler = params->preload_handler;
	dev->postload_handler = params->postload_handler;

	dev->device_flags = params->flags;
	strscpy(dev->devpath, params->devpath, माप(dev->devpath));

	smscore_registry_settype(dev->devpath, params->device_type);

	/* add device to devices list */
	mutex_lock(&g_smscore_deviceslock);
	list_add(&dev->entry, &g_smscore_devices);
	mutex_unlock(&g_smscore_deviceslock);

	*coredev = dev;

	pr_debug("device %p created\n", dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_रेजिस्टर_device);


अटल पूर्णांक smscore_sendrequest_and_रुको(काष्ठा smscore_device_t *coredev,
		व्योम *buffer, माप_प्रकार size, काष्ठा completion *completion) अणु
	पूर्णांक rc;

	अगर (!completion)
		वापस -EINVAL;
	init_completion(completion);

	rc = coredev->sendrequest_handler(coredev->context, buffer, size);
	अगर (rc < 0) अणु
		pr_info("sendrequest returned error %d\n", rc);
		वापस rc;
	पूर्ण

	वापस रुको_क्रम_completion_समयout(completion,
			msecs_to_jअगरfies(SMS_PROTOCOL_MAX_RAOUNDTRIP_MS)) ?
			0 : -ETIME;
पूर्ण

/*
 * Starts & enables IR operations
 *
 * वापस: 0 on success, < 0 on error.
 */
अटल पूर्णांक smscore_init_ir(काष्ठा smscore_device_t *coredev)
अणु
	पूर्णांक ir_io;
	पूर्णांक rc;
	व्योम *buffer;

	coredev->ir.dev = शून्य;
	ir_io = sms_get_board(smscore_get_board_id(coredev))->board_cfg.ir;
	अगर (ir_io) अणु/* only अगर IR port exist we use IR sub-module */
		pr_debug("IR loading\n");
		rc = sms_ir_init(coredev);

		अगर	(rc != 0)
			pr_err("Error initialization DTV IR sub-module\n");
		अन्यथा अणु
			buffer = kदो_स्मृति(माप(काष्ठा sms_msg_data2) +
						SMS_DMA_ALIGNMENT,
						GFP_KERNEL | coredev->gfp_buf_flags);
			अगर (buffer) अणु
				काष्ठा sms_msg_data2 *msg =
				(काष्ठा sms_msg_data2 *)
				SMS_ALIGN_ADDRESS(buffer);

				SMS_INIT_MSG(&msg->x_msg_header,
						MSG_SMS_START_IR_REQ,
						माप(काष्ठा sms_msg_data2));
				msg->msg_data[0] = coredev->ir.controller;
				msg->msg_data[1] = coredev->ir.समयout;

				rc = smscore_sendrequest_and_रुको(coredev, msg,
						msg->x_msg_header. msg_length,
						&coredev->ir_init_करोne);

				kमुक्त(buffer);
			पूर्ण अन्यथा
				pr_err("Sending IR initialization message failed\n");
		पूर्ण
	पूर्ण अन्यथा
		pr_info("IR port has not been detected\n");

	वापस 0;
पूर्ण

/*
 * configures device features according to board configuration काष्ठाure.
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 *
 * वापस: 0 on success, <0 on error.
 */
अटल पूर्णांक smscore_configure_board(काष्ठा smscore_device_t *coredev)
अणु
	काष्ठा sms_board *board;

	board = sms_get_board(coredev->board_id);
	अगर (!board) अणु
		pr_err("no board configuration exist.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (board->mtu) अणु
		काष्ठा sms_msg_data mtu_msg;
		pr_debug("set max transmit unit %d\n", board->mtu);

		mtu_msg.x_msg_header.msg_src_id = 0;
		mtu_msg.x_msg_header.msg_dst_id = HIF_TASK;
		mtu_msg.x_msg_header.msg_flags = 0;
		mtu_msg.x_msg_header.msg_type = MSG_SMS_SET_MAX_TX_MSG_LEN_REQ;
		mtu_msg.x_msg_header.msg_length = माप(mtu_msg);
		mtu_msg.msg_data[0] = board->mtu;

		coredev->sendrequest_handler(coredev->context, &mtu_msg,
					     माप(mtu_msg));
	पूर्ण

	अगर (board->crystal) अणु
		काष्ठा sms_msg_data crys_msg;
		pr_debug("set crystal value %d\n", board->crystal);

		SMS_INIT_MSG(&crys_msg.x_msg_header,
				MSG_SMS_NEW_CRYSTAL_REQ,
				माप(crys_msg));
		crys_msg.msg_data[0] = board->crystal;

		coredev->sendrequest_handler(coredev->context, &crys_msg,
					     माप(crys_msg));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * sets initial device mode and notअगरies client hotplugs that device is पढ़ोy
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *		  smscore_रेजिस्टर_device
 *
 * वापस: 0 on success, <0 on error.
 */
पूर्णांक smscore_start_device(काष्ठा smscore_device_t *coredev)
अणु
	पूर्णांक rc;
	पूर्णांक board_id = smscore_get_board_id(coredev);
	पूर्णांक mode = smscore_registry_geपंचांगode(coredev->devpath);

	/* Device is initialized as DEVICE_MODE_NONE */
	अगर (board_id != SMS_BOARD_UNKNOWN && mode == DEVICE_MODE_NONE)
		mode = sms_get_board(board_id)->शेष_mode;

	rc = smscore_set_device_mode(coredev, mode);
	अगर (rc < 0) अणु
		pr_info("set device mode failed , rc %d\n", rc);
		वापस rc;
	पूर्ण
	rc = smscore_configure_board(coredev);
	अगर (rc < 0) अणु
		pr_info("configure board failed , rc %d\n", rc);
		वापस rc;
	पूर्ण

	mutex_lock(&g_smscore_deviceslock);

	rc = smscore_notअगरy_callbacks(coredev, coredev->device, 1);
	smscore_init_ir(coredev);

	pr_debug("device %p started, rc %d\n", coredev, rc);

	mutex_unlock(&g_smscore_deviceslock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_start_device);


अटल पूर्णांक smscore_load_firmware_family2(काष्ठा smscore_device_t *coredev,
					 व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा sms_firmware *firmware = (काष्ठा sms_firmware *) buffer;
	काष्ठा sms_msg_data4 *msg;
	u32 mem_address,  calc_checksum = 0;
	u32 i, *ptr;
	u8 *payload = firmware->payload;
	पूर्णांक rc = 0;
	firmware->start_address = le32_to_cpup((__le32 *)&firmware->start_address);
	firmware->length = le32_to_cpup((__le32 *)&firmware->length);

	mem_address = firmware->start_address;

	pr_debug("loading FW to addr 0x%x size %d\n",
		 mem_address, firmware->length);
	अगर (coredev->preload_handler) अणु
		rc = coredev->preload_handler(coredev->context);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	/* PAGE_SIZE buffer shall be enough and dma aligned */
	msg = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL | coredev->gfp_buf_flags);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (coredev->mode != DEVICE_MODE_NONE) अणु
		pr_debug("sending reload command.\n");
		SMS_INIT_MSG(&msg->x_msg_header, MSG_SW_RELOAD_START_REQ,
			     माप(काष्ठा sms_msg_hdr));
		rc = smscore_sendrequest_and_रुको(coredev, msg,
						  msg->x_msg_header.msg_length,
						  &coredev->reload_start_करोne);
		अगर (rc < 0) अणु
			pr_err("device reload failed, rc %d\n", rc);
			जाओ निकास_fw_करोwnload;
		पूर्ण
		mem_address = *(u32 *) &payload[20];
	पूर्ण

	क्रम (i = 0, ptr = (u32 *)firmware->payload; i < firmware->length/4 ;
	     i++, ptr++)
		calc_checksum += *ptr;

	जबतक (size && rc >= 0) अणु
		काष्ठा sms_data_करोwnload *data_msg =
			(काष्ठा sms_data_करोwnload *) msg;
		पूर्णांक payload_size = min_t(पूर्णांक, size, SMS_MAX_PAYLOAD_SIZE);

		SMS_INIT_MSG(&msg->x_msg_header, MSG_SMS_DATA_DOWNLOAD_REQ,
			     (u16)(माप(काष्ठा sms_msg_hdr) +
				      माप(u32) + payload_size));

		data_msg->mem_addr = mem_address;
		स_नकल(data_msg->payload, payload, payload_size);

		rc = smscore_sendrequest_and_रुको(coredev, data_msg,
				data_msg->x_msg_header.msg_length,
				&coredev->data_करोwnload_करोne);

		payload += payload_size;
		size -= payload_size;
		mem_address += payload_size;
	पूर्ण

	अगर (rc < 0)
		जाओ निकास_fw_करोwnload;

	pr_debug("sending MSG_SMS_DATA_VALIDITY_REQ expecting 0x%x\n",
		calc_checksum);
	SMS_INIT_MSG(&msg->x_msg_header, MSG_SMS_DATA_VALIDITY_REQ,
			माप(msg->x_msg_header) +
			माप(u32) * 3);
	msg->msg_data[0] = firmware->start_address;
		/* Entry poपूर्णांक */
	msg->msg_data[1] = firmware->length;
	msg->msg_data[2] = 0; /* Regular checksum*/
	rc = smscore_sendrequest_and_रुको(coredev, msg,
					  msg->x_msg_header.msg_length,
					  &coredev->data_validity_करोne);
	अगर (rc < 0)
		जाओ निकास_fw_करोwnload;

	अगर (coredev->mode == DEVICE_MODE_NONE) अणु
		काष्ठा sms_msg_data *trigger_msg =
			(काष्ठा sms_msg_data *) msg;

		pr_debug("sending MSG_SMS_SWDOWNLOAD_TRIGGER_REQ\n");
		SMS_INIT_MSG(&msg->x_msg_header,
				MSG_SMS_SWDOWNLOAD_TRIGGER_REQ,
				माप(काष्ठा sms_msg_hdr) +
				माप(u32) * 5);

		trigger_msg->msg_data[0] = firmware->start_address;
					/* Entry poपूर्णांक */
		trigger_msg->msg_data[1] = 6; /* Priority */
		trigger_msg->msg_data[2] = 0x200; /* Stack size */
		trigger_msg->msg_data[3] = 0; /* Parameter */
		trigger_msg->msg_data[4] = 4; /* Task ID */

		rc = smscore_sendrequest_and_रुको(coredev, trigger_msg,
					trigger_msg->x_msg_header.msg_length,
					&coredev->trigger_करोne);
	पूर्ण अन्यथा अणु
		SMS_INIT_MSG(&msg->x_msg_header, MSG_SW_RELOAD_EXEC_REQ,
				माप(काष्ठा sms_msg_hdr));
		rc = coredev->sendrequest_handler(coredev->context, msg,
				msg->x_msg_header.msg_length);
	पूर्ण

	अगर (rc < 0)
		जाओ निकास_fw_करोwnload;

	/*
	 * backward compatibility - रुको to device_पढ़ोy_करोne क्रम
	 * not more than 400 ms
	 */
	msleep(400);

निकास_fw_करोwnload:
	kमुक्त(msg);

	अगर (coredev->postload_handler) अणु
		pr_debug("rc=%d, postload=0x%p\n",
			 rc, coredev->postload_handler);
		अगर (rc >= 0)
			वापस coredev->postload_handler(coredev->context);
	पूर्ण

	pr_debug("rc=%d\n", rc);
	वापस rc;
पूर्ण

अटल अक्षर *smscore_fw_lkup[][DEVICE_MODE_MAX] = अणु
	[SMS_NOVA_A0] = अणु
		[DEVICE_MODE_DVBT]		= SMS_FW_DVB_NOVA_12MHZ,
		[DEVICE_MODE_DVBH]		= SMS_FW_DVB_NOVA_12MHZ,
		[DEVICE_MODE_DAB_TDMB]		= SMS_FW_TDMB_NOVA_12MHZ,
		[DEVICE_MODE_DVBT_BDA]		= SMS_FW_DVB_NOVA_12MHZ,
		[DEVICE_MODE_ISDBT]		= SMS_FW_ISDBT_NOVA_12MHZ,
		[DEVICE_MODE_ISDBT_BDA]		= SMS_FW_ISDBT_NOVA_12MHZ,
	पूर्ण,
	[SMS_NOVA_B0] = अणु
		[DEVICE_MODE_DVBT]		= SMS_FW_DVB_NOVA_12MHZ_B0,
		[DEVICE_MODE_DVBH]		= SMS_FW_DVB_NOVA_12MHZ_B0,
		[DEVICE_MODE_DAB_TDMB]		= SMS_FW_TDMB_NOVA_12MHZ_B0,
		[DEVICE_MODE_DVBT_BDA]		= SMS_FW_DVB_NOVA_12MHZ_B0,
		[DEVICE_MODE_ISDBT]		= SMS_FW_ISDBT_NOVA_12MHZ_B0,
		[DEVICE_MODE_ISDBT_BDA]		= SMS_FW_ISDBT_NOVA_12MHZ_B0,
		[DEVICE_MODE_FM_RADIO]		= SMS_FW_FM_RADIO,
		[DEVICE_MODE_FM_RADIO_BDA]	= SMS_FW_FM_RADIO,
	पूर्ण,
	[SMS_VEGA] = अणु
		[DEVICE_MODE_CMMB]		= SMS_FW_CMMB_VEGA_12MHZ,
	पूर्ण,
	[SMS_VENICE] = अणु
		[DEVICE_MODE_CMMB]		= SMS_FW_CMMB_VENICE_12MHZ,
	पूर्ण,
	[SMS_MING] = अणु
		[DEVICE_MODE_CMMB]		= SMS_FW_CMMB_MING_APP,
	पूर्ण,
	[SMS_PELE] = अणु
		[DEVICE_MODE_ISDBT]		= SMS_FW_ISDBT_PELE,
		[DEVICE_MODE_ISDBT_BDA]		= SMS_FW_ISDBT_PELE,
	पूर्ण,
	[SMS_RIO] = अणु
		[DEVICE_MODE_DVBT]		= SMS_FW_DVB_RIO,
		[DEVICE_MODE_DVBH]		= SMS_FW_DVBH_RIO,
		[DEVICE_MODE_DVBT_BDA]		= SMS_FW_DVB_RIO,
		[DEVICE_MODE_ISDBT]		= SMS_FW_ISDBT_RIO,
		[DEVICE_MODE_ISDBT_BDA]		= SMS_FW_ISDBT_RIO,
		[DEVICE_MODE_FM_RADIO]		= SMS_FW_FM_RADIO_RIO,
		[DEVICE_MODE_FM_RADIO_BDA]	= SMS_FW_FM_RADIO_RIO,
	पूर्ण,
	[SMS_DENVER_1530] = अणु
		[DEVICE_MODE_ATSC]		= SMS_FW_ATSC_DENVER,
	पूर्ण,
	[SMS_DENVER_2160] = अणु
		[DEVICE_MODE_DAB_TDMB]		= SMS_FW_TDMB_DENVER,
	पूर्ण,
पूर्ण;

/*
 * get firmware file name from one of the two mechanisms : sms_boards or
 * smscore_fw_lkup.
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *		  smscore_रेजिस्टर_device
 * @param mode requested mode of operation
 * @param lookup अगर 1, always get the fw filename from smscore_fw_lkup
 *	 table. अगर 0, try first to get from sms_boards
 *
 * वापस: 0 on success, <0 on error.
 */
अटल अक्षर *smscore_get_fw_filename(काष्ठा smscore_device_t *coredev,
			      पूर्णांक mode)
अणु
	अक्षर **fw;
	पूर्णांक board_id = smscore_get_board_id(coredev);
	क्रमागत sms_device_type_st type;

	type = smscore_registry_gettype(coredev->devpath);

	/* Prevent looking outside the smscore_fw_lkup table */
	अगर (type <= SMS_UNKNOWN_TYPE || type >= SMS_NUM_OF_DEVICE_TYPES)
		वापस शून्य;
	अगर (mode <= DEVICE_MODE_NONE || mode >= DEVICE_MODE_MAX)
		वापस शून्य;

	pr_debug("trying to get fw name from sms_boards board_id %d mode %d\n",
		  board_id, mode);
	fw = sms_get_board(board_id)->fw;
	अगर (!fw || !fw[mode]) अणु
		pr_debug("cannot find fw name in sms_boards, getting from lookup table mode %d type %d\n",
			  mode, type);
		वापस smscore_fw_lkup[type][mode];
	पूर्ण

	वापस fw[mode];
पूर्ण

/*
 * loads specअगरied firmware पूर्णांकo a buffer and calls device loadfirmware_handler
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 * @param filename null-terminated string specअगरies firmware file name
 * @param loadfirmware_handler device handler that loads firmware
 *
 * वापस: 0 on success, <0 on error.
 */
अटल पूर्णांक smscore_load_firmware_from_file(काष्ठा smscore_device_t *coredev,
					   पूर्णांक mode,
					   loadfirmware_t loadfirmware_handler)
अणु
	पूर्णांक rc = -ENOENT;
	u8 *fw_buf;
	u32 fw_buf_size;
	स्थिर काष्ठा firmware *fw;

	अक्षर *fw_filename = smscore_get_fw_filename(coredev, mode);
	अगर (!fw_filename) अणु
		pr_err("mode %d not supported on this device\n", mode);
		वापस -ENOENT;
	पूर्ण
	pr_debug("Firmware name: %s\n", fw_filename);

	अगर (!loadfirmware_handler &&
	    !(coredev->device_flags & SMS_DEVICE_FAMILY2))
		वापस -EINVAL;

	rc = request_firmware(&fw, fw_filename, coredev->device);
	अगर (rc < 0) अणु
		pr_err("failed to open firmware file '%s'\n", fw_filename);
		वापस rc;
	पूर्ण
	pr_debug("read fw %s, buffer size=0x%zx\n", fw_filename, fw->size);
	fw_buf = kदो_स्मृति(ALIGN(fw->size + माप(काष्ठा sms_firmware),
			 SMS_ALLOC_ALIGNMENT), GFP_KERNEL | coredev->gfp_buf_flags);
	अगर (!fw_buf) अणु
		pr_err("failed to allocate firmware buffer\n");
		rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		स_नकल(fw_buf, fw->data, fw->size);
		fw_buf_size = fw->size;

		rc = (coredev->device_flags & SMS_DEVICE_FAMILY2) ?
			smscore_load_firmware_family2(coredev, fw_buf, fw_buf_size)
			: loadfirmware_handler(coredev->context, fw_buf,
			fw_buf_size);
	पूर्ण

	kमुक्त(fw_buf);
	release_firmware(fw);

	वापस rc;
पूर्ण

/*
 * notअगरies all clients रेजिस्टरed with the device, notअगरies hotplugs,
 * मुक्तs all buffers and coredev object
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 *
 * वापस: 0 on success, <0 on error.
 */
व्योम smscore_unरेजिस्टर_device(काष्ठा smscore_device_t *coredev)
अणु
	काष्ठा smscore_buffer_t *cb;
	पूर्णांक num_buffers = 0;
	पूर्णांक retry = 0;

	mutex_lock(&g_smscore_deviceslock);

	/* Release input device (IR) resources */
	sms_ir_निकास(coredev);

	smscore_notअगरy_clients(coredev);
	smscore_notअगरy_callbacks(coredev, शून्य, 0);

	/* at this poपूर्णांक all buffers should be back
	 * onresponse must no दीर्घer be called */

	जबतक (1) अणु
		जबतक (!list_empty(&coredev->buffers)) अणु
			cb = (काष्ठा smscore_buffer_t *) coredev->buffers.next;
			list_del(&cb->entry);
			kमुक्त(cb);
			num_buffers++;
		पूर्ण
		अगर (num_buffers == coredev->num_buffers)
			अवरोध;
		अगर (++retry > 10) अणु
			pr_info("exiting although not all buffers released.\n");
			अवरोध;
		पूर्ण

		pr_debug("waiting for %d buffer(s)\n",
			 coredev->num_buffers - num_buffers);
		mutex_unlock(&g_smscore_deviceslock);
		msleep(100);
		mutex_lock(&g_smscore_deviceslock);
	पूर्ण

	pr_debug("freed %d buffers\n", num_buffers);

	अगर (coredev->common_buffer) अणु
		अगर (coredev->usb_device)
			kमुक्त(coredev->common_buffer);
		अन्यथा
			dma_मुक्त_coherent(coredev->device,
					  coredev->common_buffer_size,
					  coredev->common_buffer,
					  coredev->common_buffer_phys);
	पूर्ण
	kमुक्त(coredev->fw_buf);

	list_del(&coredev->entry);
	kमुक्त(coredev);

	mutex_unlock(&g_smscore_deviceslock);

	pr_debug("device %p destroyed\n", coredev);
पूर्ण
EXPORT_SYMBOL_GPL(smscore_unरेजिस्टर_device);

अटल पूर्णांक smscore_detect_mode(काष्ठा smscore_device_t *coredev)
अणु
	व्योम *buffer = kदो_स्मृति(माप(काष्ठा sms_msg_hdr) + SMS_DMA_ALIGNMENT,
			       GFP_KERNEL | coredev->gfp_buf_flags);
	काष्ठा sms_msg_hdr *msg =
		(काष्ठा sms_msg_hdr *) SMS_ALIGN_ADDRESS(buffer);
	पूर्णांक rc;

	अगर (!buffer)
		वापस -ENOMEM;

	SMS_INIT_MSG(msg, MSG_SMS_GET_VERSION_EX_REQ,
		     माप(काष्ठा sms_msg_hdr));

	rc = smscore_sendrequest_and_रुको(coredev, msg, msg->msg_length,
					  &coredev->version_ex_करोne);
	अगर (rc == -ETIME) अणु
		pr_err("MSG_SMS_GET_VERSION_EX_REQ failed first try\n");

		अगर (रुको_क्रम_completion_समयout(&coredev->resume_करोne,
						msecs_to_jअगरfies(5000))) अणु
			rc = smscore_sendrequest_and_रुको(
				coredev, msg, msg->msg_length,
				&coredev->version_ex_करोne);
			अगर (rc < 0)
				pr_err("MSG_SMS_GET_VERSION_EX_REQ failed second try, rc %d\n",
					rc);
		पूर्ण अन्यथा
			rc = -ETIME;
	पूर्ण

	kमुक्त(buffer);

	वापस rc;
पूर्ण

/*
 * send init device request and रुको क्रम response
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 * @param mode requested mode of operation
 *
 * वापस: 0 on success, <0 on error.
 */
अटल पूर्णांक smscore_init_device(काष्ठा smscore_device_t *coredev, पूर्णांक mode)
अणु
	व्योम *buffer;
	काष्ठा sms_msg_data *msg;
	पूर्णांक rc = 0;

	buffer = kदो_स्मृति(माप(काष्ठा sms_msg_data) +
			SMS_DMA_ALIGNMENT, GFP_KERNEL | coredev->gfp_buf_flags);
	अगर (!buffer)
		वापस -ENOMEM;

	msg = (काष्ठा sms_msg_data *)SMS_ALIGN_ADDRESS(buffer);
	SMS_INIT_MSG(&msg->x_msg_header, MSG_SMS_INIT_DEVICE_REQ,
			माप(काष्ठा sms_msg_data));
	msg->msg_data[0] = mode;

	rc = smscore_sendrequest_and_रुको(coredev, msg,
			msg->x_msg_header. msg_length,
			&coredev->init_device_करोne);

	kमुक्त(buffer);
	वापस rc;
पूर्ण

/*
 * calls device handler to change mode of operation
 * NOTE: stellar/usb may disconnect when changing mode
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 * @param mode requested mode of operation
 *
 * वापस: 0 on success, <0 on error.
 */
पूर्णांक smscore_set_device_mode(काष्ठा smscore_device_t *coredev, पूर्णांक mode)
अणु
	पूर्णांक rc = 0;

	pr_debug("set device mode to %d\n", mode);
	अगर (coredev->device_flags & SMS_DEVICE_FAMILY2) अणु
		अगर (mode <= DEVICE_MODE_NONE || mode >= DEVICE_MODE_MAX) अणु
			pr_err("invalid mode specified %d\n", mode);
			वापस -EINVAL;
		पूर्ण

		smscore_registry_seपंचांगode(coredev->devpath, mode);

		अगर (!(coredev->device_flags & SMS_DEVICE_NOT_READY)) अणु
			rc = smscore_detect_mode(coredev);
			अगर (rc < 0) अणु
				pr_err("mode detect failed %d\n", rc);
				वापस rc;
			पूर्ण
		पूर्ण

		अगर (coredev->mode == mode) अणु
			pr_debug("device mode %d already set\n", mode);
			वापस 0;
		पूर्ण

		अगर (!(coredev->modes_supported & (1 << mode))) अणु
			rc = smscore_load_firmware_from_file(coredev,
							     mode, शून्य);
			अगर (rc >= 0)
				pr_debug("firmware download success\n");
		पूर्ण अन्यथा अणु
			pr_debug("mode %d is already supported by running firmware\n",
				 mode);
		पूर्ण
		अगर (coredev->fw_version >= 0x800) अणु
			rc = smscore_init_device(coredev, mode);
			अगर (rc < 0)
				pr_err("device init failed, rc %d.\n", rc);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mode <= DEVICE_MODE_NONE || mode >= DEVICE_MODE_MAX) अणु
			pr_err("invalid mode specified %d\n", mode);
			वापस -EINVAL;
		पूर्ण

		smscore_registry_seपंचांगode(coredev->devpath, mode);

		अगर (coredev->detecपंचांगode_handler)
			coredev->detecपंचांगode_handler(coredev->context,
						    &coredev->mode);

		अगर (coredev->mode != mode && coredev->seपंचांगode_handler)
			rc = coredev->seपंचांगode_handler(coredev->context, mode);
	पूर्ण

	अगर (rc >= 0) अणु
		अक्षर *buffer;
		coredev->mode = mode;
		coredev->device_flags &= ~SMS_DEVICE_NOT_READY;

		buffer = kदो_स्मृति(माप(काष्ठा sms_msg_data) +
				 SMS_DMA_ALIGNMENT, GFP_KERNEL | coredev->gfp_buf_flags);
		अगर (buffer) अणु
			काष्ठा sms_msg_data *msg = (काष्ठा sms_msg_data *) SMS_ALIGN_ADDRESS(buffer);

			SMS_INIT_MSG(&msg->x_msg_header, MSG_SMS_INIT_DEVICE_REQ,
				     माप(काष्ठा sms_msg_data));
			msg->msg_data[0] = mode;

			rc = smscore_sendrequest_and_रुको(
				coredev, msg, msg->x_msg_header.msg_length,
				&coredev->init_device_करोne);

			kमुक्त(buffer);
		पूर्ण
	पूर्ण

	अगर (rc < 0)
		pr_err("return error code %d.\n", rc);
	अन्यथा
		pr_debug("Success setting device mode.\n");

	वापस rc;
पूर्ण

/*
 * calls device handler to get current mode of operation
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 *
 * वापस: current mode
 */
पूर्णांक smscore_get_device_mode(काष्ठा smscore_device_t *coredev)
अणु
	वापस coredev->mode;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_get_device_mode);

/*
 * find client by response id & type within the clients list.
 * वापस client handle or शून्य.
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 * @param data_type client data type (SMS_DONT_CARE क्रम all types)
 * @param id client id (SMS_DONT_CARE क्रम all id)
 *
 */
अटल काष्ठा
smscore_client_t *smscore_find_client(काष्ठा smscore_device_t *coredev,
				      पूर्णांक data_type, पूर्णांक id)
अणु
	काष्ठा list_head *first;
	काष्ठा smscore_client_t *client;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *firstid;
	काष्ठा smscore_idlist_t *client_id;

	spin_lock_irqsave(&coredev->clientslock, flags);
	first = &coredev->clients;
	list_क्रम_each_entry(client, first, entry) अणु
		firstid = &client->idlist;
		list_क्रम_each_entry(client_id, firstid, entry) अणु
			अगर ((client_id->id == id) &&
			    (client_id->data_type == data_type ||
			    (client_id->data_type == 0)))
				जाओ found;
		पूर्ण
	पूर्ण
	client = शून्य;
found:
	spin_unlock_irqrestore(&coredev->clientslock, flags);
	वापस client;
पूर्ण

/*
 * find client by response id/type, call clients onresponse handler
 * वापस buffer to pool on error
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 * @param cb poपूर्णांकer to response buffer descriptor
 *
 */
व्योम smscore_onresponse(काष्ठा smscore_device_t *coredev,
		काष्ठा smscore_buffer_t *cb) अणु
	काष्ठा sms_msg_hdr *phdr = (काष्ठा sms_msg_hdr *) ((u8 *) cb->p
			+ cb->offset);
	काष्ठा smscore_client_t *client;
	पूर्णांक rc = -EBUSY;
	अटल अचिन्हित दीर्घ last_sample_समय; /* = 0; */
	अटल पूर्णांक data_total; /* = 0; */
	अचिन्हित दीर्घ समय_now = jअगरfies_to_msecs(jअगरfies);

	अगर (!last_sample_समय)
		last_sample_समय = समय_now;

	अगर (समय_now - last_sample_समय > 10000) अणु
		pr_debug("data rate %d bytes/secs\n",
			  (पूर्णांक)((data_total * 1000) /
				(समय_now - last_sample_समय)));

		last_sample_समय = समय_now;
		data_total = 0;
	पूर्ण

	data_total += cb->size;
	/* Do we need to re-route? */
	अगर ((phdr->msg_type == MSG_SMS_HO_PER_SLICES_IND) ||
			(phdr->msg_type == MSG_SMS_TRANSMISSION_IND)) अणु
		अगर (coredev->mode == DEVICE_MODE_DVBT_BDA)
			phdr->msg_dst_id = DVBT_BDA_CONTROL_MSG_ID;
	पूर्ण


	client = smscore_find_client(coredev, phdr->msg_type, phdr->msg_dst_id);

	/* If no client रेजिस्टरed क्रम type & id,
	 * check क्रम control client where type is not रेजिस्टरed */
	अगर (client)
		rc = client->onresponse_handler(client->context, cb);

	अगर (rc < 0) अणु
		चयन (phdr->msg_type) अणु
		हाल MSG_SMS_ISDBT_TUNE_RES:
			अवरोध;
		हाल MSG_SMS_RF_TUNE_RES:
			अवरोध;
		हाल MSG_SMS_SIGNAL_DETECTED_IND:
			अवरोध;
		हाल MSG_SMS_NO_SIGNAL_IND:
			अवरोध;
		हाल MSG_SMS_SPI_INT_LINE_SET_RES:
			अवरोध;
		हाल MSG_SMS_INTERFACE_LOCK_IND:
			अवरोध;
		हाल MSG_SMS_INTERFACE_UNLOCK_IND:
			अवरोध;
		हाल MSG_SMS_GET_VERSION_EX_RES:
		अणु
			काष्ठा sms_version_res *ver =
				(काष्ठा sms_version_res *) phdr;
			pr_debug("Firmware id %d prots 0x%x ver %d.%d\n",
				  ver->firmware_id, ver->supported_protocols,
				  ver->rom_ver_major, ver->rom_ver_minor);

			coredev->mode = ver->firmware_id == 255 ?
				DEVICE_MODE_NONE : ver->firmware_id;
			coredev->modes_supported = ver->supported_protocols;
			coredev->fw_version = ver->rom_ver_major << 8 |
					      ver->rom_ver_minor;

			complete(&coredev->version_ex_करोne);
			अवरोध;
		पूर्ण
		हाल MSG_SMS_INIT_DEVICE_RES:
			complete(&coredev->init_device_करोne);
			अवरोध;
		हाल MSG_SW_RELOAD_START_RES:
			complete(&coredev->reload_start_करोne);
			अवरोध;
		हाल MSG_SMS_DATA_VALIDITY_RES:
		अणु
			काष्ठा sms_msg_data *validity = (काष्ठा sms_msg_data *) phdr;

			pr_debug("MSG_SMS_DATA_VALIDITY_RES, checksum = 0x%x\n",
				validity->msg_data[0]);
			complete(&coredev->data_validity_करोne);
			अवरोध;
		पूर्ण
		हाल MSG_SMS_DATA_DOWNLOAD_RES:
			complete(&coredev->data_करोwnload_करोne);
			अवरोध;
		हाल MSG_SW_RELOAD_EXEC_RES:
			अवरोध;
		हाल MSG_SMS_SWDOWNLOAD_TRIGGER_RES:
			complete(&coredev->trigger_करोne);
			अवरोध;
		हाल MSG_SMS_SLEEP_RESUME_COMP_IND:
			complete(&coredev->resume_करोne);
			अवरोध;
		हाल MSG_SMS_GPIO_CONFIG_EX_RES:
			complete(&coredev->gpio_configuration_करोne);
			अवरोध;
		हाल MSG_SMS_GPIO_SET_LEVEL_RES:
			complete(&coredev->gpio_set_level_करोne);
			अवरोध;
		हाल MSG_SMS_GPIO_GET_LEVEL_RES:
		अणु
			u32 *msgdata = (u32 *) phdr;
			coredev->gpio_get_res = msgdata[1];
			pr_debug("gpio level %d\n",
					coredev->gpio_get_res);
			complete(&coredev->gpio_get_level_करोne);
			अवरोध;
		पूर्ण
		हाल MSG_SMS_START_IR_RES:
			complete(&coredev->ir_init_करोne);
			अवरोध;
		हाल MSG_SMS_IR_SAMPLES_IND:
			sms_ir_event(coredev,
				(स्थिर अक्षर *)
				((अक्षर *)phdr
				+ माप(काष्ठा sms_msg_hdr)),
				(पूर्णांक)phdr->msg_length
				- माप(काष्ठा sms_msg_hdr));
			अवरोध;

		हाल MSG_SMS_DVBT_BDA_DATA:
			/*
			 * It can be received here, अगर the frontend is
			 * tuned पूर्णांकo a valid channel and the proper firmware
			 * is loaded. That happens when the module got हटाओd
			 * and re-inserted, without घातering the device off
			 */
			अवरोध;

		शेष:
			pr_debug("message %s(%d) not handled.\n",
				  smscore_translate_msg(phdr->msg_type),
				  phdr->msg_type);
			अवरोध;
		पूर्ण
		smscore_putbuffer(coredev, cb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(smscore_onresponse);

/*
 * वापस poपूर्णांकer to next मुक्त buffer descriptor from core pool
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 *
 * वापस: poपूर्णांकer to descriptor on success, शून्य on error.
 */

अटल काष्ठा smscore_buffer_t *get_entry(काष्ठा smscore_device_t *coredev)
अणु
	काष्ठा smscore_buffer_t *cb = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&coredev->bufferslock, flags);
	अगर (!list_empty(&coredev->buffers)) अणु
		cb = (काष्ठा smscore_buffer_t *) coredev->buffers.next;
		list_del(&cb->entry);
	पूर्ण
	spin_unlock_irqrestore(&coredev->bufferslock, flags);
	वापस cb;
पूर्ण

काष्ठा smscore_buffer_t *smscore_getbuffer(काष्ठा smscore_device_t *coredev)
अणु
	काष्ठा smscore_buffer_t *cb = शून्य;

	रुको_event(coredev->buffer_mng_रुकोq, (cb = get_entry(coredev)));

	वापस cb;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_getbuffer);

/*
 * वापस buffer descriptor to a pool
 *
 * @param coredev poपूर्णांकer to a coredev object वापसed by
 *                smscore_रेजिस्टर_device
 * @param cb poपूर्णांकer buffer descriptor
 *
 */
व्योम smscore_putbuffer(काष्ठा smscore_device_t *coredev,
		काष्ठा smscore_buffer_t *cb) अणु
	wake_up_पूर्णांकerruptible(&coredev->buffer_mng_रुकोq);
	list_add_locked(&cb->entry, &coredev->buffers, &coredev->bufferslock);
पूर्ण
EXPORT_SYMBOL_GPL(smscore_putbuffer);

अटल पूर्णांक smscore_validate_client(काष्ठा smscore_device_t *coredev,
				   काष्ठा smscore_client_t *client,
				   पूर्णांक data_type, पूर्णांक id)
अणु
	काष्ठा smscore_idlist_t *listentry;
	काष्ठा smscore_client_t *रेजिस्टरed_client;

	अगर (!client) अणु
		pr_err("bad parameter.\n");
		वापस -EINVAL;
	पूर्ण
	रेजिस्टरed_client = smscore_find_client(coredev, data_type, id);
	अगर (रेजिस्टरed_client == client)
		वापस 0;

	अगर (रेजिस्टरed_client) अणु
		pr_err("The msg ID already registered to another client.\n");
		वापस -EEXIST;
	पूर्ण
	listentry = kzalloc(माप(*listentry), GFP_KERNEL);
	अगर (!listentry)
		वापस -ENOMEM;

	listentry->id = id;
	listentry->data_type = data_type;
	list_add_locked(&listentry->entry, &client->idlist,
			&coredev->clientslock);
	वापस 0;
पूर्ण

/*
 * creates smsclient object, check that id is taken by another client
 *
 * @param coredev poपूर्णांकer to a coredev object from clients hotplug
 * @param initial_id all messages with this id would be sent to this client
 * @param data_type all messages of this type would be sent to this client
 * @param onresponse_handler client handler that is called to
 *                           process incoming messages
 * @param onहटाओ_handler client handler that is called when device is हटाओd
 * @param context client-specअगरic context
 * @param client poपूर्णांकer to a value that receives created smsclient object
 *
 * वापस: 0 on success, <0 on error.
 */
पूर्णांक smscore_रेजिस्टर_client(काष्ठा smscore_device_t *coredev,
			    काष्ठा smsclient_params_t *params,
			    काष्ठा smscore_client_t **client)
अणु
	काष्ठा smscore_client_t *newclient;
	/* check that no other channel with same parameters exists */
	अगर (smscore_find_client(coredev, params->data_type,
				params->initial_id)) अणु
		pr_err("Client already exist.\n");
		वापस -EEXIST;
	पूर्ण

	newclient = kzalloc(माप(*newclient), GFP_KERNEL);
	अगर (!newclient)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&newclient->idlist);
	newclient->coredev = coredev;
	newclient->onresponse_handler = params->onresponse_handler;
	newclient->onहटाओ_handler = params->onहटाओ_handler;
	newclient->context = params->context;
	list_add_locked(&newclient->entry, &coredev->clients,
			&coredev->clientslock);
	smscore_validate_client(coredev, newclient, params->data_type,
				params->initial_id);
	*client = newclient;
	pr_debug("%p %d %d\n", params->context, params->data_type,
		  params->initial_id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(smscore_रेजिस्टर_client);

/*
 * मुक्तs smsclient object and all subclients associated with it
 *
 * @param client poपूर्णांकer to smsclient object वापसed by
 *               smscore_रेजिस्टर_client
 *
 */
व्योम smscore_unरेजिस्टर_client(काष्ठा smscore_client_t *client)
अणु
	काष्ठा smscore_device_t *coredev = client->coredev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&coredev->clientslock, flags);


	जबतक (!list_empty(&client->idlist)) अणु
		काष्ठा smscore_idlist_t *identry =
			(काष्ठा smscore_idlist_t *) client->idlist.next;
		list_del(&identry->entry);
		kमुक्त(identry);
	पूर्ण

	pr_debug("%p\n", client->context);

	list_del(&client->entry);
	kमुक्त(client);

	spin_unlock_irqrestore(&coredev->clientslock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(smscore_unरेजिस्टर_client);

/*
 * verअगरies that source id is not taken by another client,
 * calls device handler to send requests to the device
 *
 * @param client poपूर्णांकer to smsclient object वापसed by
 *               smscore_रेजिस्टर_client
 * @param buffer poपूर्णांकer to a request buffer
 * @param size size (in bytes) of request buffer
 *
 * वापस: 0 on success, <0 on error.
 */
पूर्णांक smsclient_sendrequest(काष्ठा smscore_client_t *client,
			  व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा smscore_device_t *coredev;
	काष्ठा sms_msg_hdr *phdr = (काष्ठा sms_msg_hdr *) buffer;
	पूर्णांक rc;

	अगर (!client) अणु
		pr_err("Got NULL client\n");
		वापस -EINVAL;
	पूर्ण

	coredev = client->coredev;

	/* check that no other channel with same id exists */
	अगर (!coredev) अणु
		pr_err("Got NULL coredev\n");
		वापस -EINVAL;
	पूर्ण

	rc = smscore_validate_client(client->coredev, client, 0,
				     phdr->msg_src_id);
	अगर (rc < 0)
		वापस rc;

	वापस coredev->sendrequest_handler(coredev->context, buffer, size);
पूर्ण
EXPORT_SYMBOL_GPL(smsclient_sendrequest);


/* old GPIO managements implementation */
पूर्णांक smscore_configure_gpio(काष्ठा smscore_device_t *coredev, u32 pin,
			   काष्ठा smscore_config_gpio *pinconfig)
अणु
	काष्ठा अणु
		काष्ठा sms_msg_hdr hdr;
		u32 data[6];
	पूर्ण msg;

	अगर (coredev->device_flags & SMS_DEVICE_FAMILY2) अणु
		msg.hdr.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
		msg.hdr.msg_dst_id = HIF_TASK;
		msg.hdr.msg_flags = 0;
		msg.hdr.msg_type  = MSG_SMS_GPIO_CONFIG_EX_REQ;
		msg.hdr.msg_length = माप(msg);

		msg.data[0] = pin;
		msg.data[1] = pinconfig->pullupकरोwn;

		/* Convert slew rate क्रम Nova: Fast(0) = 3 / Slow(1) = 0; */
		msg.data[2] = pinconfig->outमाला_दोlewrate == 0 ? 3 : 0;

		चयन (pinconfig->outputdriving) अणु
		हाल SMS_GPIO_OUTPUTDRIVING_S_16mA:
			msg.data[3] = 7; /* Nova - 16mA */
			अवरोध;
		हाल SMS_GPIO_OUTPUTDRIVING_S_12mA:
			msg.data[3] = 5; /* Nova - 11mA */
			अवरोध;
		हाल SMS_GPIO_OUTPUTDRIVING_S_8mA:
			msg.data[3] = 3; /* Nova - 7mA */
			अवरोध;
		हाल SMS_GPIO_OUTPUTDRIVING_S_4mA:
		शेष:
			msg.data[3] = 2; /* Nova - 4mA */
			अवरोध;
		पूर्ण

		msg.data[4] = pinconfig->direction;
		msg.data[5] = 0;
	पूर्ण अन्यथा /* TODO: SMS_DEVICE_FAMILY1 */
		वापस -EINVAL;

	वापस coredev->sendrequest_handler(coredev->context,
					    &msg, माप(msg));
पूर्ण

पूर्णांक smscore_set_gpio(काष्ठा smscore_device_t *coredev, u32 pin, पूर्णांक level)
अणु
	काष्ठा अणु
		काष्ठा sms_msg_hdr hdr;
		u32 data[3];
	पूर्ण msg;

	अगर (pin > MAX_GPIO_PIN_NUMBER)
		वापस -EINVAL;

	msg.hdr.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	msg.hdr.msg_dst_id = HIF_TASK;
	msg.hdr.msg_flags = 0;
	msg.hdr.msg_type  = MSG_SMS_GPIO_SET_LEVEL_REQ;
	msg.hdr.msg_length = माप(msg);

	msg.data[0] = pin;
	msg.data[1] = level ? 1 : 0;
	msg.data[2] = 0;

	वापस coredev->sendrequest_handler(coredev->context,
					    &msg, माप(msg));
पूर्ण

/* new GPIO management implementation */
अटल पूर्णांक get_gpio_pin_params(u32 pin_num, u32 *p_translatedpin_num,
		u32 *p_group_num, u32 *p_group_cfg) अणु

	*p_group_cfg = 1;

	अगर (pin_num <= 1)	अणु
		*p_translatedpin_num = 0;
		*p_group_num = 9;
		*p_group_cfg = 2;
	पूर्ण अन्यथा अगर (pin_num >= 2 && pin_num <= 6) अणु
		*p_translatedpin_num = 2;
		*p_group_num = 0;
		*p_group_cfg = 2;
	पूर्ण अन्यथा अगर (pin_num >= 7 && pin_num <= 11) अणु
		*p_translatedpin_num = 7;
		*p_group_num = 1;
	पूर्ण अन्यथा अगर (pin_num >= 12 && pin_num <= 15) अणु
		*p_translatedpin_num = 12;
		*p_group_num = 2;
		*p_group_cfg = 3;
	पूर्ण अन्यथा अगर (pin_num == 16) अणु
		*p_translatedpin_num = 16;
		*p_group_num = 23;
	पूर्ण अन्यथा अगर (pin_num >= 17 && pin_num <= 24) अणु
		*p_translatedpin_num = 17;
		*p_group_num = 3;
	पूर्ण अन्यथा अगर (pin_num == 25) अणु
		*p_translatedpin_num = 25;
		*p_group_num = 6;
	पूर्ण अन्यथा अगर (pin_num >= 26 && pin_num <= 28) अणु
		*p_translatedpin_num = 26;
		*p_group_num = 4;
	पूर्ण अन्यथा अगर (pin_num == 29) अणु
		*p_translatedpin_num = 29;
		*p_group_num = 5;
		*p_group_cfg = 2;
	पूर्ण अन्यथा अगर (pin_num == 30) अणु
		*p_translatedpin_num = 30;
		*p_group_num = 8;
	पूर्ण अन्यथा अगर (pin_num == 31) अणु
		*p_translatedpin_num = 31;
		*p_group_num = 17;
	पूर्ण अन्यथा
		वापस -1;

	*p_group_cfg <<= 24;

	वापस 0;
पूर्ण

पूर्णांक smscore_gpio_configure(काष्ठा smscore_device_t *coredev, u8 pin_num,
		काष्ठा smscore_config_gpio *p_gpio_config) अणु

	u32 total_len;
	u32 translatedpin_num = 0;
	u32 group_num = 0;
	u32 electric_अक्षर;
	u32 group_cfg;
	व्योम *buffer;
	पूर्णांक rc;

	काष्ठा set_gpio_msg अणु
		काष्ठा sms_msg_hdr x_msg_header;
		u32 msg_data[6];
	पूर्ण *p_msg;


	अगर (pin_num > MAX_GPIO_PIN_NUMBER)
		वापस -EINVAL;

	अगर (!p_gpio_config)
		वापस -EINVAL;

	total_len = माप(काष्ठा sms_msg_hdr) + (माप(u32) * 6);

	buffer = kदो_स्मृति(total_len + SMS_DMA_ALIGNMENT,
			GFP_KERNEL | coredev->gfp_buf_flags);
	अगर (!buffer)
		वापस -ENOMEM;

	p_msg = (काष्ठा set_gpio_msg *) SMS_ALIGN_ADDRESS(buffer);

	p_msg->x_msg_header.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	p_msg->x_msg_header.msg_dst_id = HIF_TASK;
	p_msg->x_msg_header.msg_flags = 0;
	p_msg->x_msg_header.msg_length = (u16) total_len;
	p_msg->msg_data[0] = pin_num;

	अगर (!(coredev->device_flags & SMS_DEVICE_FAMILY2)) अणु
		p_msg->x_msg_header.msg_type = MSG_SMS_GPIO_CONFIG_REQ;
		अगर (get_gpio_pin_params(pin_num, &translatedpin_num, &group_num,
				&group_cfg) != 0) अणु
			rc = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		p_msg->msg_data[1] = translatedpin_num;
		p_msg->msg_data[2] = group_num;
		electric_अक्षर = (p_gpio_config->pullupकरोwn)
				| (p_gpio_config->inअक्षर_दोacteristics << 2)
				| (p_gpio_config->outमाला_दोlewrate << 3)
				| (p_gpio_config->outputdriving << 4);
		p_msg->msg_data[3] = electric_अक्षर;
		p_msg->msg_data[4] = p_gpio_config->direction;
		p_msg->msg_data[5] = group_cfg;
	पूर्ण अन्यथा अणु
		p_msg->x_msg_header.msg_type = MSG_SMS_GPIO_CONFIG_EX_REQ;
		p_msg->msg_data[1] = p_gpio_config->pullupकरोwn;
		p_msg->msg_data[2] = p_gpio_config->outमाला_दोlewrate;
		p_msg->msg_data[3] = p_gpio_config->outputdriving;
		p_msg->msg_data[4] = p_gpio_config->direction;
		p_msg->msg_data[5] = 0;
	पूर्ण

	rc = smscore_sendrequest_and_रुको(coredev, p_msg, total_len,
			&coredev->gpio_configuration_करोne);

	अगर (rc != 0) अणु
		अगर (rc == -ETIME)
			pr_err("smscore_gpio_configure timeout\n");
		अन्यथा
			pr_err("smscore_gpio_configure error\n");
	पूर्ण
मुक्त:
	kमुक्त(buffer);

	वापस rc;
पूर्ण

पूर्णांक smscore_gpio_set_level(काष्ठा smscore_device_t *coredev, u8 pin_num,
		u8 new_level) अणु

	u32 total_len;
	पूर्णांक rc;
	व्योम *buffer;

	काष्ठा set_gpio_msg अणु
		काष्ठा sms_msg_hdr x_msg_header;
		u32 msg_data[3]; /* keep it 3 ! */
	पूर्ण *p_msg;

	अगर ((new_level > 1) || (pin_num > MAX_GPIO_PIN_NUMBER))
		वापस -EINVAL;

	total_len = माप(काष्ठा sms_msg_hdr) +
			(3 * माप(u32)); /* keep it 3 ! */

	buffer = kदो_स्मृति(total_len + SMS_DMA_ALIGNMENT,
			GFP_KERNEL | coredev->gfp_buf_flags);
	अगर (!buffer)
		वापस -ENOMEM;

	p_msg = (काष्ठा set_gpio_msg *) SMS_ALIGN_ADDRESS(buffer);

	p_msg->x_msg_header.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	p_msg->x_msg_header.msg_dst_id = HIF_TASK;
	p_msg->x_msg_header.msg_flags = 0;
	p_msg->x_msg_header.msg_type = MSG_SMS_GPIO_SET_LEVEL_REQ;
	p_msg->x_msg_header.msg_length = (u16) total_len;
	p_msg->msg_data[0] = pin_num;
	p_msg->msg_data[1] = new_level;

	/* Send message to SMS */
	rc = smscore_sendrequest_and_रुको(coredev, p_msg, total_len,
			&coredev->gpio_set_level_करोne);

	अगर (rc != 0) अणु
		अगर (rc == -ETIME)
			pr_err("smscore_gpio_set_level timeout\n");
		अन्यथा
			pr_err("smscore_gpio_set_level error\n");
	पूर्ण
	kमुक्त(buffer);

	वापस rc;
पूर्ण

पूर्णांक smscore_gpio_get_level(काष्ठा smscore_device_t *coredev, u8 pin_num,
		u8 *level) अणु

	u32 total_len;
	पूर्णांक rc;
	व्योम *buffer;

	काष्ठा set_gpio_msg अणु
		काष्ठा sms_msg_hdr x_msg_header;
		u32 msg_data[2];
	पूर्ण *p_msg;


	अगर (pin_num > MAX_GPIO_PIN_NUMBER)
		वापस -EINVAL;

	total_len = माप(काष्ठा sms_msg_hdr) + (2 * माप(u32));

	buffer = kदो_स्मृति(total_len + SMS_DMA_ALIGNMENT,
			GFP_KERNEL | coredev->gfp_buf_flags);
	अगर (!buffer)
		वापस -ENOMEM;

	p_msg = (काष्ठा set_gpio_msg *) SMS_ALIGN_ADDRESS(buffer);

	p_msg->x_msg_header.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	p_msg->x_msg_header.msg_dst_id = HIF_TASK;
	p_msg->x_msg_header.msg_flags = 0;
	p_msg->x_msg_header.msg_type = MSG_SMS_GPIO_GET_LEVEL_REQ;
	p_msg->x_msg_header.msg_length = (u16) total_len;
	p_msg->msg_data[0] = pin_num;
	p_msg->msg_data[1] = 0;

	/* Send message to SMS */
	rc = smscore_sendrequest_and_रुको(coredev, p_msg, total_len,
			&coredev->gpio_get_level_करोne);

	अगर (rc != 0) अणु
		अगर (rc == -ETIME)
			pr_err("smscore_gpio_get_level timeout\n");
		अन्यथा
			pr_err("smscore_gpio_get_level error\n");
	पूर्ण
	kमुक्त(buffer);

	/* Its a race between other gpio_get_level() and the copy of the single
	 * global 'coredev->gpio_get_res' to  the function's variable 'level'
	 */
	*level = coredev->gpio_get_res;

	वापस rc;
पूर्ण

अटल पूर्णांक __init smscore_module_init(व्योम)
अणु
	INIT_LIST_HEAD(&g_smscore_notअगरyees);
	INIT_LIST_HEAD(&g_smscore_devices);
	mutex_init(&g_smscore_deviceslock);

	INIT_LIST_HEAD(&g_smscore_registry);
	mutex_init(&g_smscore_registrylock);

	वापस 0;
पूर्ण

अटल व्योम __निकास smscore_module_निकास(व्योम)
अणु
	mutex_lock(&g_smscore_deviceslock);
	जबतक (!list_empty(&g_smscore_notअगरyees)) अणु
		काष्ठा smscore_device_notअगरyee_t *notअगरyee =
			(काष्ठा smscore_device_notअगरyee_t *)
				g_smscore_notअगरyees.next;

		list_del(&notअगरyee->entry);
		kमुक्त(notअगरyee);
	पूर्ण
	mutex_unlock(&g_smscore_deviceslock);

	mutex_lock(&g_smscore_registrylock);
	जबतक (!list_empty(&g_smscore_registry)) अणु
		काष्ठा smscore_registry_entry_t *entry =
			(काष्ठा smscore_registry_entry_t *)
				g_smscore_registry.next;

		list_del(&entry->entry);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&g_smscore_registrylock);

	pr_debug("\n");
पूर्ण

module_init(smscore_module_init);
module_निकास(smscore_module_निकास);

MODULE_DESCRIPTION("Siano MDTV Core module");
MODULE_AUTHOR("Siano Mobile Silicon, Inc. (uris@siano-ms.com)");
MODULE_LICENSE("GPL");

/* This should match what's defined at smscoreapi.h */
MODULE_FIRMWARE(SMS_FW_ATSC_DENVER);
MODULE_FIRMWARE(SMS_FW_CMMB_MING_APP);
MODULE_FIRMWARE(SMS_FW_CMMB_VEGA_12MHZ);
MODULE_FIRMWARE(SMS_FW_CMMB_VENICE_12MHZ);
MODULE_FIRMWARE(SMS_FW_DVBH_RIO);
MODULE_FIRMWARE(SMS_FW_DVB_NOVA_12MHZ_B0);
MODULE_FIRMWARE(SMS_FW_DVB_NOVA_12MHZ);
MODULE_FIRMWARE(SMS_FW_DVB_RIO);
MODULE_FIRMWARE(SMS_FW_FM_RADIO);
MODULE_FIRMWARE(SMS_FW_FM_RADIO_RIO);
MODULE_FIRMWARE(SMS_FW_DVBT_HCW_55XXX);
MODULE_FIRMWARE(SMS_FW_ISDBT_HCW_55XXX);
MODULE_FIRMWARE(SMS_FW_ISDBT_NOVA_12MHZ_B0);
MODULE_FIRMWARE(SMS_FW_ISDBT_NOVA_12MHZ);
MODULE_FIRMWARE(SMS_FW_ISDBT_PELE);
MODULE_FIRMWARE(SMS_FW_ISDBT_RIO);
MODULE_FIRMWARE(SMS_FW_DVBT_NOVA_A);
MODULE_FIRMWARE(SMS_FW_DVBT_NOVA_B);
MODULE_FIRMWARE(SMS_FW_DVBT_STELLAR);
MODULE_FIRMWARE(SMS_FW_TDMB_DENVER);
MODULE_FIRMWARE(SMS_FW_TDMB_NOVA_12MHZ_B0);
MODULE_FIRMWARE(SMS_FW_TDMB_NOVA_12MHZ);
