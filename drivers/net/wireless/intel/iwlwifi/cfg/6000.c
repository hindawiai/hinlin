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
#घोषणा IWL6000_UCODE_API_MAX 6
#घोषणा IWL6050_UCODE_API_MAX 5
#घोषणा IWL6000G2_UCODE_API_MAX 6
#घोषणा IWL6035_UCODE_API_MAX 6

/* Lowest firmware API version supported */
#घोषणा IWL6000_UCODE_API_MIN 4
#घोषणा IWL6050_UCODE_API_MIN 4
#घोषणा IWL6000G2_UCODE_API_MIN 5
#घोषणा IWL6035_UCODE_API_MIN 6

/* EEPROM versions */
#घोषणा EEPROM_6000_TX_POWER_VERSION	(4)
#घोषणा EEPROM_6000_EEPROM_VERSION	(0x423)
#घोषणा EEPROM_6050_TX_POWER_VERSION	(4)
#घोषणा EEPROM_6050_EEPROM_VERSION	(0x532)
#घोषणा EEPROM_6150_TX_POWER_VERSION	(6)
#घोषणा EEPROM_6150_EEPROM_VERSION	(0x553)
#घोषणा EEPROM_6005_TX_POWER_VERSION	(6)
#घोषणा EEPROM_6005_EEPROM_VERSION	(0x709)
#घोषणा EEPROM_6030_TX_POWER_VERSION	(6)
#घोषणा EEPROM_6030_EEPROM_VERSION	(0x709)
#घोषणा EEPROM_6035_TX_POWER_VERSION	(6)
#घोषणा EEPROM_6035_EEPROM_VERSION	(0x753)

#घोषणा IWL6000_FW_PRE "iwlwifi-6000-"
#घोषणा IWL6000_MODULE_FIRMWARE(api) IWL6000_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL6050_FW_PRE "iwlwifi-6050-"
#घोषणा IWL6050_MODULE_FIRMWARE(api) IWL6050_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL6005_FW_PRE "iwlwifi-6000g2a-"
#घोषणा IWL6005_MODULE_FIRMWARE(api) IWL6005_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL6030_FW_PRE "iwlwifi-6000g2b-"
#घोषणा IWL6030_MODULE_FIRMWARE(api) IWL6030_FW_PRE __stringअगरy(api) ".ucode"

अटल स्थिर काष्ठा iwl_base_params iwl6000_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_2K,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ll_items = OTP_MAX_LL_ITEMS_6x00,
	.shaकरोw_ram_support = true,
	.led_compensation = 51,
	.wd_समयout = IWL_DEF_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = false, /* TODO: fix bugs using this feature */
	.scd_chain_ext_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_base_params iwl6050_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_2K,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ll_items = OTP_MAX_LL_ITEMS_6x50,
	.shaकरोw_ram_support = true,
	.led_compensation = 51,
	.wd_समयout = IWL_DEF_WD_TIMEOUT,
	.max_event_log_size = 1024,
	.shaकरोw_reg_enable = false, /* TODO: fix bugs using this feature */
	.scd_chain_ext_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_base_params iwl6000_g2_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_2K,
	.num_of_queues = IWLAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ll_items = OTP_MAX_LL_ITEMS_6x00,
	.shaकरोw_ram_support = true,
	.led_compensation = 57,
	.wd_समयout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = false, /* TODO: fix bugs using this feature */
	.scd_chain_ext_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl6000_ht_params = अणु
	.ht_greenfield_support = true,
	.use_rts_क्रम_aggregation = true, /* use rts/cts protection */
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ),
पूर्ण;

अटल स्थिर काष्ठा iwl_eeprom_params iwl6000_eeprom_params = अणु
	.regulatory_bands = अणु
		EEPROM_REG_BAND_1_CHANNELS,
		EEPROM_REG_BAND_2_CHANNELS,
		EEPROM_REG_BAND_3_CHANNELS,
		EEPROM_REG_BAND_4_CHANNELS,
		EEPROM_REG_BAND_5_CHANNELS,
		EEPROM_6000_REG_BAND_24_HT40_CHANNELS,
		EEPROM_REG_BAND_52_HT40_CHANNELS
	पूर्ण,
	.enhanced_txघातer = true,
पूर्ण;

#घोषणा IWL_DEVICE_6005						\
	.fw_name_pre = IWL6005_FW_PRE,				\
	.ucode_api_max = IWL6000G2_UCODE_API_MAX,		\
	.ucode_api_min = IWL6000G2_UCODE_API_MIN,		\
	.trans.device_family = IWL_DEVICE_FAMILY_6005,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_6005_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_6005_TX_POWER_VERSION,	\
	.trans.base_params = &iwl6000_g2_base_params,		\
	.eeprom_params = &iwl6000_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE

स्थिर काष्ठा iwl_cfg iwl6005_2agn_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6205 AGN",
	IWL_DEVICE_6005,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6005_2abg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6205 ABG",
	IWL_DEVICE_6005,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6005_2bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6205 BG",
	IWL_DEVICE_6005,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6005_2agn_sff_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6205S AGN",
	IWL_DEVICE_6005,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6005_2agn_d_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6205D AGN",
	IWL_DEVICE_6005,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6005_2agn_mow1_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6206 AGN",
	IWL_DEVICE_6005,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6005_2agn_mow2_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6207 AGN",
	IWL_DEVICE_6005,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

#घोषणा IWL_DEVICE_6030						\
	.fw_name_pre = IWL6030_FW_PRE,				\
	.ucode_api_max = IWL6000G2_UCODE_API_MAX,		\
	.ucode_api_min = IWL6000G2_UCODE_API_MIN,		\
	.trans.device_family = IWL_DEVICE_FAMILY_6030,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_6030_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_6030_TX_POWER_VERSION,	\
	.trans.base_params = &iwl6000_g2_base_params,		\
	.eeprom_params = &iwl6000_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE

स्थिर काष्ठा iwl_cfg iwl6030_2agn_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6230 AGN",
	IWL_DEVICE_6030,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6030_2abg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6230 ABG",
	IWL_DEVICE_6030,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6030_2bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6230 BGN",
	IWL_DEVICE_6030,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6030_2bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6230 BG",
	IWL_DEVICE_6030,
पूर्ण;

#घोषणा IWL_DEVICE_6035						\
	.fw_name_pre = IWL6030_FW_PRE,				\
	.ucode_api_max = IWL6035_UCODE_API_MAX,			\
	.ucode_api_min = IWL6035_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_6030,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_6030_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_6030_TX_POWER_VERSION,	\
	.trans.base_params = &iwl6000_g2_base_params,		\
	.eeprom_params = &iwl6000_eeprom_params,		\
	.led_mode = IWL_LED_RF_STATE

स्थिर काष्ठा iwl_cfg iwl6035_2agn_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6235 AGN",
	IWL_DEVICE_6035,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6035_2agn_sff_cfg = अणु
	.name = "Intel(R) Centrino(R) Ultimate-N 6235 AGN",
	IWL_DEVICE_6035,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl1030_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 1030 BGN",
	IWL_DEVICE_6030,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl1030_bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 1030 BG",
	IWL_DEVICE_6030,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl130_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 130 BGN",
	IWL_DEVICE_6030,
	.ht_params = &iwl6000_ht_params,
	.rx_with_siso_भागersity = true,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl130_bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N 130 BG",
	IWL_DEVICE_6030,
	.rx_with_siso_भागersity = true,
पूर्ण;

/*
 * "i": Internal configuration, use पूर्णांकernal Power Amplअगरier
 */
#घोषणा IWL_DEVICE_6000i					\
	.fw_name_pre = IWL6000_FW_PRE,				\
	.ucode_api_max = IWL6000_UCODE_API_MAX,			\
	.ucode_api_min = IWL6000_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_6000i,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.valid_tx_ant = ANT_BC,		/* .cfg overग_लिखो */	\
	.valid_rx_ant = ANT_BC,		/* .cfg overग_लिखो */	\
	.nvm_ver = EEPROM_6000_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_6000_TX_POWER_VERSION,	\
	.trans.base_params = &iwl6000_base_params,		\
	.eeprom_params = &iwl6000_eeprom_params,		\
	.led_mode = IWL_LED_BLINK

स्थिर काष्ठा iwl_cfg iwl6000i_2agn_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6200 AGN",
	IWL_DEVICE_6000i,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6000i_2abg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6200 ABG",
	IWL_DEVICE_6000i,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6000i_2bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N 6200 BG",
	IWL_DEVICE_6000i,
पूर्ण;

#घोषणा IWL_DEVICE_6050						\
	.fw_name_pre = IWL6050_FW_PRE,				\
	.ucode_api_max = IWL6050_UCODE_API_MAX,			\
	.ucode_api_min = IWL6050_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_6050,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.valid_tx_ant = ANT_AB,		/* .cfg overग_लिखो */	\
	.valid_rx_ant = ANT_AB,		/* .cfg overग_लिखो */	\
	.nvm_ver = EEPROM_6050_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_6050_TX_POWER_VERSION,	\
	.trans.base_params = &iwl6050_base_params,		\
	.eeprom_params = &iwl6000_eeprom_params,		\
	.led_mode = IWL_LED_BLINK,				\
	.पूर्णांकernal_wimax_coex = true

स्थिर काष्ठा iwl_cfg iwl6050_2agn_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N + WiMAX 6250 AGN",
	IWL_DEVICE_6050,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6050_2abg_cfg = अणु
	.name = "Intel(R) Centrino(R) Advanced-N + WiMAX 6250 ABG",
	IWL_DEVICE_6050,
पूर्ण;

#घोषणा IWL_DEVICE_6150						\
	.fw_name_pre = IWL6050_FW_PRE,				\
	.ucode_api_max = IWL6050_UCODE_API_MAX,			\
	.ucode_api_min = IWL6050_UCODE_API_MIN,			\
	.trans.device_family = IWL_DEVICE_FAMILY_6150,		\
	.max_inst_size = IWL60_RTC_INST_SIZE,			\
	.max_data_size = IWL60_RTC_DATA_SIZE,			\
	.nvm_ver = EEPROM_6150_EEPROM_VERSION,		\
	.nvm_calib_ver = EEPROM_6150_TX_POWER_VERSION,	\
	.trans.base_params = &iwl6050_base_params,		\
	.eeprom_params = &iwl6000_eeprom_params,		\
	.led_mode = IWL_LED_BLINK,				\
	.पूर्णांकernal_wimax_coex = true

स्थिर काष्ठा iwl_cfg iwl6150_bgn_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N + WiMAX 6150 BGN",
	IWL_DEVICE_6150,
	.ht_params = &iwl6000_ht_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6150_bg_cfg = अणु
	.name = "Intel(R) Centrino(R) Wireless-N + WiMAX 6150 BG",
	IWL_DEVICE_6150,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl6000_3agn_cfg = अणु
	.name = "Intel(R) Centrino(R) Ultimate-N 6300 AGN",
	.fw_name_pre = IWL6000_FW_PRE,
	.ucode_api_max = IWL6000_UCODE_API_MAX,
	.ucode_api_min = IWL6000_UCODE_API_MIN,
	.trans.device_family = IWL_DEVICE_FAMILY_6000,
	.max_inst_size = IWL60_RTC_INST_SIZE,
	.max_data_size = IWL60_RTC_DATA_SIZE,
	.nvm_ver = EEPROM_6000_EEPROM_VERSION,
	.nvm_calib_ver = EEPROM_6000_TX_POWER_VERSION,
	.trans.base_params = &iwl6000_base_params,
	.eeprom_params = &iwl6000_eeprom_params,
	.ht_params = &iwl6000_ht_params,
	.led_mode = IWL_LED_BLINK,
पूर्ण;

MODULE_FIRMWARE(IWL6000_MODULE_FIRMWARE(IWL6000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL6050_MODULE_FIRMWARE(IWL6050_UCODE_API_MAX));
MODULE_FIRMWARE(IWL6005_MODULE_FIRMWARE(IWL6000G2_UCODE_API_MAX));
MODULE_FIRMWARE(IWL6030_MODULE_FIRMWARE(IWL6000G2_UCODE_API_MAX));
