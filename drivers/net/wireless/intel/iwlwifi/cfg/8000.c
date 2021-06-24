<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2014, 2018-2020 Intel Corporation
 * Copyright (C) 2014-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश "iwl-config.h"

/* Highest firmware API version supported */
#घोषणा IWL8000_UCODE_API_MAX	36
#घोषणा IWL8265_UCODE_API_MAX	36

/* Lowest firmware API version supported */
#घोषणा IWL8000_UCODE_API_MIN	22
#घोषणा IWL8265_UCODE_API_MIN	22

/* NVM versions */
#घोषणा IWL8000_NVM_VERSION		0x0a1d

/* Memory offsets and lengths */
#घोषणा IWL8260_DCCM_OFFSET		0x800000
#घोषणा IWL8260_DCCM_LEN		0x18000
#घोषणा IWL8260_DCCM2_OFFSET		0x880000
#घोषणा IWL8260_DCCM2_LEN		0x8000
#घोषणा IWL8260_SMEM_OFFSET		0x400000
#घोषणा IWL8260_SMEM_LEN		0x68000

#घोषणा IWL8000_FW_PRE "iwlwifi-8000C-"
#घोषणा IWL8000_MODULE_FIRMWARE(api) \
	IWL8000_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL8265_FW_PRE "iwlwifi-8265-"
#घोषणा IWL8265_MODULE_FIRMWARE(api) \
	IWL8265_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा DEFAULT_NVM_खाता_FAMILY_8000C		"nvmData-8000C"

अटल स्थिर काष्ठा iwl_base_params iwl8000_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_32K,
	.num_of_queues = 31,
	.max_tfd_queue_size = 256,
	.shaकरोw_ram_support = true,
	.led_compensation = 57,
	.wd_समयout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = true,
	.pcie_l1_allowed = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl8000_ht_params = अणु
	.stbc = true,
	.ldpc = true,
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ),
पूर्ण;

अटल स्थिर काष्ठा iwl_tt_params iwl8000_tt_params = अणु
	.ct_समाप्त_entry = 115,
	.ct_समाप्त_निकास = 93,
	.ct_समाप्त_duration = 5,
	.dynamic_smps_entry = 111,
	.dynamic_smps_निकास = 107,
	.tx_protection_entry = 112,
	.tx_protection_निकास = 105,
	.tx_backoff = अणु
		अणु.temperature = 110, .backoff = 200पूर्ण,
		अणु.temperature = 111, .backoff = 600पूर्ण,
		अणु.temperature = 112, .backoff = 1200पूर्ण,
		अणु.temperature = 113, .backoff = 2000पूर्ण,
		अणु.temperature = 114, .backoff = 4000पूर्ण,
	पूर्ण,
	.support_ct_समाप्त = true,
	.support_dynamic_smps = true,
	.support_tx_protection = true,
	.support_tx_backoff = true,
पूर्ण;

#घोषणा IWL_DEVICE_8000_COMMON						\
	.trans.device_family = IWL_DEVICE_FAMILY_8000,			\
	.trans.base_params = &iwl8000_base_params,			\
	.led_mode = IWL_LED_RF_STATE,					\
	.nvm_hw_section_num = 10,					\
	.features = NETIF_F_RXCSUM,					\
	.non_shared_ant = ANT_A,					\
	.dccm_offset = IWL8260_DCCM_OFFSET,				\
	.dccm_len = IWL8260_DCCM_LEN,					\
	.dccm2_offset = IWL8260_DCCM2_OFFSET,				\
	.dccm2_len = IWL8260_DCCM2_LEN,					\
	.smem_offset = IWL8260_SMEM_OFFSET,				\
	.smem_len = IWL8260_SMEM_LEN,					\
	.शेष_nvm_file_C_step = DEFAULT_NVM_खाता_FAMILY_8000C,	\
	.thermal_params = &iwl8000_tt_params,				\
	.apmg_not_supported = true,					\
	.nvm_type = IWL_NVM_EXT,					\
	.dbgc_supported = true,						\
	.min_umac_error_event_table = 0x800000

#घोषणा IWL_DEVICE_8000							\
	IWL_DEVICE_8000_COMMON,						\
	.ucode_api_max = IWL8000_UCODE_API_MAX,				\
	.ucode_api_min = IWL8000_UCODE_API_MIN				\

#घोषणा IWL_DEVICE_8260							\
	IWL_DEVICE_8000_COMMON,						\
	.ucode_api_max = IWL8000_UCODE_API_MAX,				\
	.ucode_api_min = IWL8000_UCODE_API_MIN				\

#घोषणा IWL_DEVICE_8265							\
	IWL_DEVICE_8000_COMMON,						\
	.ucode_api_max = IWL8265_UCODE_API_MAX,				\
	.ucode_api_min = IWL8265_UCODE_API_MIN				\

स्थिर काष्ठा iwl_cfg iwl8260_2n_cfg = अणु
	.name = "Intel(R) Dual Band Wireless N 8260",
	.fw_name_pre = IWL8000_FW_PRE,
	IWL_DEVICE_8260,
	.ht_params = &iwl8000_ht_params,
	.nvm_ver = IWL8000_NVM_VERSION,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl8260_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 8260",
	.fw_name_pre = IWL8000_FW_PRE,
	IWL_DEVICE_8260,
	.ht_params = &iwl8000_ht_params,
	.nvm_ver = IWL8000_NVM_VERSION,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl8265_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 8265",
	.fw_name_pre = IWL8265_FW_PRE,
	IWL_DEVICE_8265,
	.ht_params = &iwl8000_ht_params,
	.nvm_ver = IWL8000_NVM_VERSION,
	.vht_mu_mimo_supported = true,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl8275_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 8275",
	.fw_name_pre = IWL8265_FW_PRE,
	IWL_DEVICE_8265,
	.ht_params = &iwl8000_ht_params,
	.nvm_ver = IWL8000_NVM_VERSION,
	.vht_mu_mimo_supported = true,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl4165_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 4165",
	.fw_name_pre = IWL8000_FW_PRE,
	IWL_DEVICE_8000,
	.ht_params = &iwl8000_ht_params,
	.nvm_ver = IWL8000_NVM_VERSION,
पूर्ण;

MODULE_FIRMWARE(IWL8000_MODULE_FIRMWARE(IWL8000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL8265_MODULE_FIRMWARE(IWL8265_UCODE_API_MAX));
