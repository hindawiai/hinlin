<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
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
#घोषणा IWL1000_UCODE_API_MAX 5
#घोषणा IWL100_UCODE_API_MAX 5

/* Lowest firmware API version supported */
#घोषणा IWL1000_UCODE_API_MIN 1
#घोषणा IWL100_UCODE_API_MIN 5

/* EEPROM version */
#घोषणा EEPROM_1000_TX_POWER_VERSION	(4)
#घोषणा EEPROM_1000_EEPROM_VERSION	(0x15C)

#घोषणा IWL1000_FW_PRE "iwlwifi-1000-"
#घोषणा IWL1000_MODULE_FIRMWARE(api) IWL1000_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL100_FW_PRE "iwlwifi-100-"
#घोषणा IWL100_MODULE_FIRMWARE(api) IWL100_FW_PRE __stringअगरy(api) ".ucode"


अटल स्थिर काष्ठा iwl_base_params iwl1000_base_params = अणु
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.eeprom_size = OTP_LOW_IMAGE_SIZE_2K,
	.pll_cfg = true,
	.max_ll_items = OTP_MAX_LL_ITEMS_1000,
	.shaकरोw_ram_support = false,
	.led_compensation = 51,
	.wd_समयout = IWL_WATCHDOG_DISABLED,
	.max_event_log_size = 128,
	.scd_chain_ext_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl1000_ht_params = अणु
	.ht_greenfield_support = true,
	.use_rts_क्रम_aggregation = true, /* use rts/cts protection */
	.ht40_bands = BIT(NL80211_BAND_2GHZ),
पूर्ण;

अटल स्थिर काष्ठा iwl_eeprom_params iwl1000_eeprom_params = अणु
	.regulatory_bands = अणु
		EEPROM_REG_BAND_1_CHANNELS,
		EEPROM_REG_BAND_2_CHANNELS,
		EEPROM_REG_BAND_3_CHANNELS,
		EEPROM_REG_BAND_4_CHANNELS,
		EEPROM_REG_BAND_5_CHANNELS,
		EEPROM_REG_BAND_24_HT40_CHANNELS,
		EEPROM_REGULATORY_BAND_NO_HT40,
	पूर्ण
पूर्ण;

#घोषणा IWL_DEVICE_1000						\
	.fw_name_pre = IWL1000_FW_PRE,				\
	.ucode_api_max = IWL1000_UCODE_API_MAX,			\
	.ucode_api_min = IWL1000_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_1000,		\
	.max_inst_size = IWLAGN_RTC_INST_SIZE,			\
	.max_data_size = IWLAGN_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_1000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_1000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl1000_base_params,		\
	.eeprom_params = &iwl1000_eeprom_params,		\
	.led_mode = IWL_LED_BLINK

स्थिर काष्ठा iwl_cfg iwl1000_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 1000 BGN",
	IWL_DEVICE_1000,
	.ht_params = &iwl1000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl1000_bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 1000 BG",
	IWL_DEVICE_1000,
पूर्ण;

#घोषणा IWL_DEVICE_100						\
	.fw_name_pre = IWL100_FW_PRE,				\
	.ucode_api_max = IWL100_UCODE_API_MAX,			\
	.ucode_api_min = IWL100_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_100,		\
	.max_inst_size = IWLAGN_RTC_INST_SIZE,			\
	.max_data_size = IWLAGN_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_1000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_1000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl1000_base_params,		\
	.eeprom_params = &iwl1000_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE,				\
	.rx_with_siso_भागersity = true

स्थिर काष्ठा iwl_cfg iwl100_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 100 BGN",
	IWL_DEVICE_100,
	.ht_params = &iwl1000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl100_bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 100 BG",
	IWL_DEVICE_100,
पूर्ण;

MODULE_FIRMWARE(IWL1000_MODULE_FIRMWARE(IWL1000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL100_MODULE_FIRMWARE(IWL100_UCODE_API_MAX));
