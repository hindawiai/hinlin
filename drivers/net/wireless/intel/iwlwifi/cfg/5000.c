<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2007 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2018 - 2020 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश "iwl-config.h"
#समावेश "iwl-agn-hw.h"

/* Highest firmware API version supported */
#घोषणा IWL5000_UCODE_API_MAX 5
#घोषणा IWL5150_UCODE_API_MAX 2

/* Lowest firmware API version supported */
#घोषणा IWL5000_UCODE_API_MIN 1
#घोषणा IWL5150_UCODE_API_MIN 1

/* EEPROM versions */
#घोषणा EEPROM_5000_TX_POWER_VERSION	(4)
#घोषणा EEPROM_5000_EEPROM_VERSION	(0x11A)
#घोषणा EEPROM_5050_TX_POWER_VERSION	(4)
#घोषणा EEPROM_5050_EEPROM_VERSION	(0x21E)

#घोषणा IWL5000_FW_PRE "iwlwifi-5000-"
#घोषणा IWL5000_MODULE_FIRMWARE(api) IWL5000_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL5150_FW_PRE "iwlwifi-5150-"
#घोषणा IWL5150_MODULE_FIRMWARE(api) IWL5150_FW_PRE __stringअगरy(api) ".ucode"

अटल स्थिर काष्ठा iwl_base_params iwl5000_base_params = अणु
	.eeprom_size = IWLAGN_EEPROM_IMG_SIZE,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.pll_cfg = true,
	.led_compensation = 51,
	.wd_समयout = IWL_WATCHDOG_DISABLED,
	.max_event_log_size = 512,
	.scd_chain_ext_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl5000_ht_params = अणु
	.ht_greenfield_support = true,
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ),
पूर्ण;

अटल स्थिर काष्ठा iwl_eeprom_params iwl5000_eeprom_params = अणु
	.regulatory_bands = अणु
		EEPROM_REG_BAND_1_CHANNELS,
		EEPROM_REG_BAND_2_CHANNELS,
		EEPROM_REG_BAND_3_CHANNELS,
		EEPROM_REG_BAND_4_CHANNELS,
		EEPROM_REG_BAND_5_CHANNELS,
		EEPROM_REG_BAND_24_HT40_CHANNELS,
		EEPROM_REG_BAND_52_HT40_CHANNELS
	पूर्ण,
पूर्ण;

#घोषणा IWL_DEVICE_5000						\
	.fw_name_pre = IWL5000_FW_PRE,				\
	.ucode_api_max = IWL5000_UCODE_API_MAX,			\
	.ucode_api_min = IWL5000_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_5000,		\
	.max_inst_size = IWLAGN_RTC_INST_SIZE,			\
	.max_data_size = IWLAGN_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_5000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_5000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl5000_base_params,		\
	.eeprom_params = &iwl5000_eeprom_params,		\
	.led_mode = IWL_LED_BLINK

स्थिर काष्ठा iwl_cfg iwl5300_agn_cfg = अणु
	.name = "Intel(R) Ultimate N WiFi Link 5300 AGN",
	IWL_DEVICE_5000,
	/* at least EEPROM 0x11A has wrong info */
	.valid_tx_ant = ANT_ABC,	/* .cfg overग_लिखो */
	.valid_rx_ant = ANT_ABC,	/* .cfg overग_लिखो */
	.ht_params = &iwl5000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl5100_bgn_cfg = अणु
	.name = "Intel(R) WiFi Link 5100 BGN",
	IWL_DEVICE_5000,
	.valid_tx_ant = ANT_B,		/* .cfg overग_लिखो */
	.valid_rx_ant = ANT_AB,		/* .cfg overग_लिखो */
	.ht_params = &iwl5000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl5100_abg_cfg = अणु
	.name = "Intel(R) WiFi Link 5100 ABG",
	IWL_DEVICE_5000,
	.valid_tx_ant = ANT_B,		/* .cfg overग_लिखो */
	.valid_rx_ant = ANT_AB,		/* .cfg overग_लिखो */
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl5100_agn_cfg = अणु
	.name = "Intel(R) WiFi Link 5100 AGN",
	IWL_DEVICE_5000,
	.valid_tx_ant = ANT_B,		/* .cfg overग_लिखो */
	.valid_rx_ant = ANT_AB,		/* .cfg overग_लिखो */
	.ht_params = &iwl5000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl5350_agn_cfg = अणु
	.name = "Intel(R) WiMAX/WiFi Link 5350 AGN",
	.fw_name_pre = IWL5000_FW_PRE,
	.ucode_api_max = IWL5000_UCODE_API_MAX,
	.ucode_api_min = IWL5000_UCODE_API_MIN,
	.trans.device_family = IWL_DEVICE_FAMILY_5000,
	.max_inst_size = IWLAGN_RTC_INST_SIZE,
	.max_data_size = IWLAGN_RTC_DATA_SIZE,
	.nvm_ver = EEPROM_5050_EEPROM_VERSION,
	.nvm_calib_ver = EEPROM_5050_TX_POWER_VERSION,
	.trans.base_params = &iwl5000_base_params,
	.eeprom_params = &iwl5000_eeprom_params,
	.ht_params = &iwl5000_ht_params,
	.led_mode = IWL_LED_BLINK,
	.पूर्णांकernal_wimax_coex = true,
पूर्ण;

#घोषणा IWL_DEVICE_5150						\
	.fw_name_pre = IWL5150_FW_PRE,				\
	.ucode_api_max = IWL5150_UCODE_API_MAX,			\
	.ucode_api_min = IWL5150_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_5150,		\
	.max_inst_size = IWLAGN_RTC_INST_SIZE,			\
	.max_data_size = IWLAGN_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_5050_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_5050_TX_POWER_VERSION,	\
	.trans.base_params = &iwl5000_base_params,		\
	.eeprom_params = &iwl5000_eeprom_params,		\
	.led_mode = IWL_LED_BLINK,				\
	.पूर्णांकernal_wimax_coex = true

स्थिर काष्ठा iwl_cfg iwl5150_agn_cfg = अणु
	.name = "Intel(R) WiMAX/WiFi Link 5150 AGN",
	IWL_DEVICE_5150,
	.ht_params = &iwl5000_ht_params,

पूर्ण;

स्थिर काष्ठा iwl_cfg iwl5150_abg_cfg = अणु
	.name = "Intel(R) WiMAX/WiFi Link 5150 ABG",
	IWL_DEVICE_5150,
पूर्ण;

MODULE_FIRMWARE(IWL5000_MODULE_FIRMWARE(IWL5000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL5150_MODULE_FIRMWARE(IWL5150_UCODE_API_MAX));
