<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015 Intel Deutschland GmbH
 */
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश "iwl-config.h"

/* Highest firmware API version supported */
#घोषणा IWL7260_UCODE_API_MAX	17
#घोषणा IWL7265_UCODE_API_MAX	17
#घोषणा IWL7265D_UCODE_API_MAX	29
#घोषणा IWL3168_UCODE_API_MAX	29

/* Lowest firmware API version supported */
#घोषणा IWL7260_UCODE_API_MIN	17
#घोषणा IWL7265_UCODE_API_MIN	17
#घोषणा IWL7265D_UCODE_API_MIN	22
#घोषणा IWL3168_UCODE_API_MIN	22

/* NVM versions */
#घोषणा IWL7260_NVM_VERSION		0x0a1d
#घोषणा IWL3160_NVM_VERSION		0x709
#घोषणा IWL3165_NVM_VERSION		0x709
#घोषणा IWL3168_NVM_VERSION		0xd01
#घोषणा IWL7265_NVM_VERSION		0x0a1d
#घोषणा IWL7265D_NVM_VERSION		0x0c11

/* DCCM offsets and lengths */
#घोषणा IWL7000_DCCM_OFFSET		0x800000
#घोषणा IWL7260_DCCM_LEN		0x14000
#घोषणा IWL3160_DCCM_LEN		0x10000
#घोषणा IWL7265_DCCM_LEN		0x17A00

#घोषणा IWL7260_FW_PRE "iwlwifi-7260-"
#घोषणा IWL7260_MODULE_FIRMWARE(api) IWL7260_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL3160_FW_PRE "iwlwifi-3160-"
#घोषणा IWL3160_MODULE_FIRMWARE(api) IWL3160_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL3168_FW_PRE "iwlwifi-3168-"
#घोषणा IWL3168_MODULE_FIRMWARE(api) IWL3168_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL7265_FW_PRE "iwlwifi-7265-"
#घोषणा IWL7265_MODULE_FIRMWARE(api) IWL7265_FW_PRE __stringअगरy(api) ".ucode"

#घोषणा IWL7265D_FW_PRE "iwlwifi-7265D-"
#घोषणा IWL7265D_MODULE_FIRMWARE(api) IWL7265D_FW_PRE __stringअगरy(api) ".ucode"

अटल स्थिर काष्ठा iwl_base_params iwl7000_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_16K,
	.num_of_queues = 31,
	.max_tfd_queue_size = 256,
	.shaकरोw_ram_support = true,
	.led_compensation = 57,
	.wd_समयout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = true,
	.pcie_l1_allowed = true,
	.apmg_wake_up_wa = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_tt_params iwl7000_high_temp_tt_params = अणु
	.ct_समाप्त_entry = 118,
	.ct_समाप्त_निकास = 96,
	.ct_समाप्त_duration = 5,
	.dynamic_smps_entry = 114,
	.dynamic_smps_निकास = 110,
	.tx_protection_entry = 114,
	.tx_protection_निकास = 108,
	.tx_backoff = अणु
		अणु.temperature = 112, .backoff = 300पूर्ण,
		अणु.temperature = 113, .backoff = 800पूर्ण,
		अणु.temperature = 114, .backoff = 1500पूर्ण,
		अणु.temperature = 115, .backoff = 3000पूर्ण,
		अणु.temperature = 116, .backoff = 5000पूर्ण,
		अणु.temperature = 117, .backoff = 10000पूर्ण,
	पूर्ण,
	.support_ct_समाप्त = true,
	.support_dynamic_smps = true,
	.support_tx_protection = true,
	.support_tx_backoff = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl7000_ht_params = अणु
	.stbc = true,
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ),
पूर्ण;

#घोषणा IWL_DEVICE_7000_COMMON					\
	.trans.device_family = IWL_DEVICE_FAMILY_7000,		\
	.trans.base_params = &iwl7000_base_params,		\
	.led_mode = IWL_LED_RF_STATE,				\
	.nvm_hw_section_num = 0,				\
	.non_shared_ant = ANT_A,				\
	.dccm_offset = IWL7000_DCCM_OFFSET

#घोषणा IWL_DEVICE_7000						\
	IWL_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWL7260_UCODE_API_MAX,			\
	.ucode_api_min = IWL7260_UCODE_API_MIN

#घोषणा IWL_DEVICE_7005						\
	IWL_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWL7265_UCODE_API_MAX,			\
	.ucode_api_min = IWL7265_UCODE_API_MIN

#घोषणा IWL_DEVICE_3008						\
	IWL_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWL3168_UCODE_API_MAX,			\
	.ucode_api_min = IWL3168_UCODE_API_MIN

#घोषणा IWL_DEVICE_7005D					\
	IWL_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWL7265D_UCODE_API_MAX,		\
	.ucode_api_min = IWL7265D_UCODE_API_MIN

स्थिर काष्ठा iwl_cfg iwl7260_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 7260",
	.fw_name_pre = IWL7260_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL7260_NVM_VERSION,
	.host_पूर्णांकerrupt_operation_mode = true,
	.lp_xtal_workaround = true,
	.dccm_len = IWL7260_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7260_2ac_cfg_high_temp = अणु
	.name = "Intel(R) Dual Band Wireless AC 7260",
	.fw_name_pre = IWL7260_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL7260_NVM_VERSION,
	.high_temp = true,
	.host_पूर्णांकerrupt_operation_mode = true,
	.lp_xtal_workaround = true,
	.dccm_len = IWL7260_DCCM_LEN,
	.thermal_params = &iwl7000_high_temp_tt_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7260_2n_cfg = अणु
	.name = "Intel(R) Dual Band Wireless N 7260",
	.fw_name_pre = IWL7260_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL7260_NVM_VERSION,
	.host_पूर्णांकerrupt_operation_mode = true,
	.lp_xtal_workaround = true,
	.dccm_len = IWL7260_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7260_n_cfg = अणु
	.name = "Intel(R) Wireless N 7260",
	.fw_name_pre = IWL7260_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL7260_NVM_VERSION,
	.host_पूर्णांकerrupt_operation_mode = true,
	.lp_xtal_workaround = true,
	.dccm_len = IWL7260_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl3160_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 3160",
	.fw_name_pre = IWL3160_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL3160_NVM_VERSION,
	.host_पूर्णांकerrupt_operation_mode = true,
	.dccm_len = IWL3160_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl3160_2n_cfg = अणु
	.name = "Intel(R) Dual Band Wireless N 3160",
	.fw_name_pre = IWL3160_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL3160_NVM_VERSION,
	.host_पूर्णांकerrupt_operation_mode = true,
	.dccm_len = IWL3160_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl3160_n_cfg = अणु
	.name = "Intel(R) Wireless N 3160",
	.fw_name_pre = IWL3160_FW_PRE,
	IWL_DEVICE_7000,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL3160_NVM_VERSION,
	.host_पूर्णांकerrupt_operation_mode = true,
	.dccm_len = IWL3160_DCCM_LEN,
पूर्ण;

अटल स्थिर काष्ठा iwl_pwr_tx_backoff iwl7265_pwr_tx_backoffs[] = अणु
	अणु.pwr = 1600, .backoff = 0पूर्ण,
	अणु.pwr = 1300, .backoff = 467पूर्ण,
	अणु.pwr = 900,  .backoff = 1900पूर्ण,
	अणु.pwr = 800, .backoff = 2630पूर्ण,
	अणु.pwr = 700, .backoff = 3720पूर्ण,
	अणु.pwr = 600, .backoff = 5550पूर्ण,
	अणु.pwr = 500, .backoff = 9350पूर्ण,
	अणु0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl7265_ht_params = अणु
	.stbc = true,
	.ldpc = true,
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ),
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl3165_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 3165",
	.fw_name_pre = IWL7265D_FW_PRE,
	IWL_DEVICE_7005D,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL3165_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl3168_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 3168",
	.fw_name_pre = IWL3168_FW_PRE,
	IWL_DEVICE_3008,
	.ht_params = &iwl7000_ht_params,
	.nvm_ver = IWL3168_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
	.nvm_type = IWL_NVM_SDP,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7265_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 7265",
	.fw_name_pre = IWL7265_FW_PRE,
	IWL_DEVICE_7005,
	.ht_params = &iwl7265_ht_params,
	.nvm_ver = IWL7265_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7265_2n_cfg = अणु
	.name = "Intel(R) Dual Band Wireless N 7265",
	.fw_name_pre = IWL7265_FW_PRE,
	IWL_DEVICE_7005,
	.ht_params = &iwl7265_ht_params,
	.nvm_ver = IWL7265_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7265_n_cfg = अणु
	.name = "Intel(R) Wireless N 7265",
	.fw_name_pre = IWL7265_FW_PRE,
	IWL_DEVICE_7005,
	.ht_params = &iwl7265_ht_params,
	.nvm_ver = IWL7265_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7265d_2ac_cfg = अणु
	.name = "Intel(R) Dual Band Wireless AC 7265",
	.fw_name_pre = IWL7265D_FW_PRE,
	IWL_DEVICE_7005D,
	.ht_params = &iwl7265_ht_params,
	.nvm_ver = IWL7265D_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7265d_2n_cfg = अणु
	.name = "Intel(R) Dual Band Wireless N 7265",
	.fw_name_pre = IWL7265D_FW_PRE,
	IWL_DEVICE_7005D,
	.ht_params = &iwl7265_ht_params,
	.nvm_ver = IWL7265D_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl7265d_n_cfg = अणु
	.name = "Intel(R) Wireless N 7265",
	.fw_name_pre = IWL7265D_FW_PRE,
	IWL_DEVICE_7005D,
	.ht_params = &iwl7265_ht_params,
	.nvm_ver = IWL7265D_NVM_VERSION,
	.pwr_tx_backoffs = iwl7265_pwr_tx_backoffs,
	.dccm_len = IWL7265_DCCM_LEN,
पूर्ण;

MODULE_FIRMWARE(IWL7260_MODULE_FIRMWARE(IWL7260_UCODE_API_MAX));
MODULE_FIRMWARE(IWL3160_MODULE_FIRMWARE(IWL7260_UCODE_API_MAX));
MODULE_FIRMWARE(IWL3168_MODULE_FIRMWARE(IWL3168_UCODE_API_MAX));
MODULE_FIRMWARE(IWL7265_MODULE_FIRMWARE(IWL7265_UCODE_API_MAX));
MODULE_FIRMWARE(IWL7265D_MODULE_FIRMWARE(IWL7265D_UCODE_API_MAX));
