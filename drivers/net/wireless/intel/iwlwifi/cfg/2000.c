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
#समावेश "dvm/commands.h" /* needed क्रम BT क्रम now */

/* Highest firmware API version supported */
#घोषणा IWL2030_UCODE_API_MAX 6
#घोषणा IWL2000_UCODE_API_MAX 6
#घोषणा IWL105_UCODE_API_MAX 6
#घोषणा IWL135_UCODE_API_MAX 6

/* Lowest firmware API version supported */
#घोषणा IWL2030_UCODE_API_MIN 5
#घोषणा IWL2000_UCODE_API_MIN 5
#घोषणा IWL105_UCODE_API_MIN 5
#घोषणा IWL135_UCODE_API_MIN 5

/* EEPROM version */
#घोषणा EEPROM_2000_TX_POWER_VERSION	(6)
#घोषणा EEPROM_2000_EEPROM_VERSION	(0x805)


#घोषणा IWL2030_FW_PRE "iwlwifi-2030-"
#घोषणा IWL2030_MODULE_FIRMWARE(api) IWL2030_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL2000_FW_PRE "iwlwifi-2000-"
#घोषणा IWL2000_MODULE_FIRMWARE(api) IWL2000_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL105_FW_PRE "iwlwifi-105-"
#घोषणा IWL105_MODULE_FIRMWARE(api) IWL105_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL135_FW_PRE "iwlwifi-135-"
#घोषणा IWL135_MODULE_FIRMWARE(api) IWL135_FW_PRE __stringअगरy(api) ".ucode"

अटल स्थिर काष्ठा iwl_base_params iwl2000_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_2K,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ll_items = OTP_MAX_LL_ITEMS_2x00,
	.shaकरोw_ram_support = true,
	.led_compensation = 51,
	.wd_समयout = IWL_DEF_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = false, /* TODO: fix bugs using this feature */
	.scd_chain_ext_wa = true,
पूर्ण;


अटल स्थिर काष्ठा iwl_base_params iwl2030_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_2K,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ll_items = OTP_MAX_LL_ITEMS_2x00,
	.shaकरोw_ram_support = true,
	.led_compensation = 57,
	.wd_समयout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = false, /* TODO: fix bugs using this feature */
	.scd_chain_ext_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl2000_ht_params = अणु
	.ht_greenfield_support = true,
	.use_rts_क्रम_aggregation = true, /* use rts/cts protection */
	.ht40_bands = BIT(NL80211_BAND_2GHZ),
पूर्ण;

अटल स्थिर काष्ठा iwl_eeprom_params iwl20x0_eeprom_params = अणु
	.regulatory_bands = अणु
		EEPROM_REG_BAND_1_CHANNELS,
		EEPROM_REG_BAND_2_CHANNELS,
		EEPROM_REG_BAND_3_CHANNELS,
		EEPROM_REG_BAND_4_CHANNELS,
		EEPROM_REG_BAND_5_CHANNELS,
		EEPROM_6000_REG_BAND_24_HT40_CHANNELS,
		EEPROM_REGULATORY_BAND_NO_HT40,
	पूर्ण,
	.enhanced_txघातer = true,
पूर्ण;

#घोषणा IWL_DEVICE_2000						\
	.fw_name_pre = IWL2000_FW_PRE,				\
	.ucode_api_max = IWL2000_UCODE_API_MAX,			\
	.ucode_api_min = IWL2000_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_2000,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_2000_EEPROM_VERSION,			\
	.nvm_calib_ver = EEPROM_2000_TX_POWER_VERSION,		\
	.trans.base_params = &iwl2000_base_params,		\
	.eeprom_params = &iwl20x0_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE


स्थिर काष्ठा iwl_cfg iwl2000_2bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 2200 BGN",
	IWL_DEVICE_2000,
	.ht_params = &iwl2000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl2000_2bgn_d_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 2200D BGN",
	IWL_DEVICE_2000,
	.ht_params = &iwl2000_ht_params,
पूर्ण;

#घोषणा IWL_DEVICE_2030						\
	.fw_name_pre = IWL2030_FW_PRE,				\
	.ucode_api_max = IWL2030_UCODE_API_MAX,			\
	.ucode_api_min = IWL2030_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_2030,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_2000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_2000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl2030_base_params,		\
	.eeprom_params = &iwl20x0_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE

स्थिर काष्ठा iwl_cfg iwl2030_2bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 2230 BGN",
	IWL_DEVICE_2030,
	.ht_params = &iwl2000_ht_params,
पूर्ण;

#घोषणा IWL_DEVICE_105						\
	.fw_name_pre = IWL105_FW_PRE,				\
	.ucode_api_max = IWL105_UCODE_API_MAX,			\
	.ucode_api_min = IWL105_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_105,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_2000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_2000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl2000_base_params,		\
	.eeprom_params = &iwl20x0_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE,				\
	.rx_with_siso_भागersity = true

स्थिर काष्ठा iwl_cfg iwl105_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 105 BGN",
	IWL_DEVICE_105,
	.ht_params = &iwl2000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl105_bgn_d_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 105D BGN",
	IWL_DEVICE_105,
	.ht_params = &iwl2000_ht_params,
पूर्ण;

#घोषणा IWL_DEVICE_135						\
	.fw_name_pre = IWL135_FW_PRE,				\
	.ucode_api_max = IWL135_UCODE_API_MAX,			\
	.ucode_api_min = IWL135_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_135,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_2000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_2000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl2030_base_params,		\
	.eeprom_params = &iwl20x0_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE,				\
	.rx_with_siso_भागersity = true

स्थिर काष्ठा iwl_cfg iwl135_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 135 BGN",
	IWL_DEVICE_135,
	.ht_params = &iwl2000_ht_params,
पूर्ण;

MODULE_FIRMWARE(IWL2000_MODULE_FIRMWARE(IWL2000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL2030_MODULE_FIRMWARE(IWL2030_UCODE_API_MAX));
MODULE_FIRMWARE(IWL105_MODULE_FIRMWARE(IWL105_UCODE_API_MAX));
MODULE_FIRMWARE(IWL135_MODULE_FIRMWARE(IWL135_UCODE_API_MAX));
