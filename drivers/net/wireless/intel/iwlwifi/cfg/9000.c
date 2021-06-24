<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश "iwl-config.h"
#समावेश "fw/file.h"
#समावेश "iwl-prph.h"

/* Highest firmware API version supported */
#घोषणा IWL9000_UCODE_API_MAX	46

/* Lowest firmware API version supported */
#घोषणा IWL9000_UCODE_API_MIN	30

/* NVM versions */
#घोषणा IWL9000_NVM_VERSION		0x0a1d

/* Memory offsets and lengths */
#घोषणा IWL9000_DCCM_OFFSET		0x800000
#घोषणा IWL9000_DCCM_LEN		0x18000
#घोषणा IWL9000_DCCM2_OFFSET		0x880000
#घोषणा IWL9000_DCCM2_LEN		0x8000
#घोषणा IWL9000_SMEM_OFFSET		0x400000
#घोषणा IWL9000_SMEM_LEN		0x68000

#घोषणा  IWL9000_FW_PRE "iwlwifi-9000-pu-b0-jf-b0-"
#घोषणा  IWL9260_FW_PRE "iwlwifi-9260-th-b0-jf-b0-"
#घोषणा IWL9000_MODULE_FIRMWARE(api) \
	IWL9000_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL9260_MODULE_FIRMWARE(api) \
	IWL9260_FW_PRE __stringअगरy(api) ".ucode"

अटल स्थिर काष्ठा iwl_base_params iwl9000_base_params = अणु
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

अटल स्थिर काष्ठा iwl_ht_params iwl9000_ht_params = अणु
	.stbc = true,
	.ldpc = true,
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ),
पूर्ण;

अटल स्थिर काष्ठा iwl_tt_params iwl9000_tt_params = अणु
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

#घोषणा IWL_DEVICE_9000							\
	.ucode_api_max = IWL9000_UCODE_API_MAX,				\
	.ucode_api_min = IWL9000_UCODE_API_MIN,				\
	.led_mode = IWL_LED_RF_STATE,					\
	.nvm_hw_section_num = 10,					\
	.non_shared_ant = ANT_B,					\
	.dccm_offset = IWL9000_DCCM_OFFSET,				\
	.dccm_len = IWL9000_DCCM_LEN,					\
	.dccm2_offset = IWL9000_DCCM2_OFFSET,				\
	.dccm2_len = IWL9000_DCCM2_LEN,					\
	.smem_offset = IWL9000_SMEM_OFFSET,				\
	.smem_len = IWL9000_SMEM_LEN,					\
	.features = IWL_TX_CSUM_NETIF_FLAGS | NETIF_F_RXCSUM,		\
	.thermal_params = &iwl9000_tt_params,				\
	.apmg_not_supported = true,					\
	.num_rbds = 512,						\
	.vht_mu_mimo_supported = true,					\
	.mac_addr_from_csr = true,					\
	.nvm_type = IWL_NVM_EXT,					\
	.dbgc_supported = true,						\
	.min_umac_error_event_table = 0x800000,				\
	.d3_debug_data_base_addr = 0x401000,				\
	.d3_debug_data_length = 92 * 1024,				\
	.ht_params = &iwl9000_ht_params,				\
	.nvm_ver = IWL9000_NVM_VERSION,					\
	.mon_smem_regs = अणु						\
		.ग_लिखो_ptr = अणु						\
			.addr = LDBG_M2S_BUF_WPTR,			\
			.mask = LDBG_M2S_BUF_WPTR_VAL_MSK,		\
		पूर्ण,							\
		.cycle_cnt = अणु						\
			.addr = LDBG_M2S_BUF_WRAP_CNT,			\
			.mask = LDBG_M2S_BUF_WRAP_CNT_VAL_MSK,		\
		पूर्ण,							\
	पूर्ण,								\
	.mon_dram_regs = अणु						\
		.ग_लिखो_ptr = अणु						\
			.addr = MON_BUFF_WRPTR_VER2,			\
			.mask = 0xffffffff,				\
		पूर्ण,							\
		.cycle_cnt = अणु						\
			.addr = MON_BUFF_CYCLE_CNT_VER2,		\
			.mask = 0xffffffff,				\
		पूर्ण,							\
	पूर्ण

स्थिर काष्ठा iwl_cfg_trans_params iwl9000_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_9000,
	.base_params = &iwl9000_base_params,
	.mq_rx_supported = true,
	.rf_id = true,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl9560_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_9000,
	.base_params = &iwl9000_base_params,
	.mq_rx_supported = true,
	.rf_id = true,
	.पूर्णांकegrated = true,
	.xtal_latency = 650,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl9560_दीर्घ_latency_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_9000,
	.base_params = &iwl9000_base_params,
	.mq_rx_supported = true,
	.rf_id = true,
	.पूर्णांकegrated = true,
	.xtal_latency = 2820,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl9560_shared_clk_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_9000,
	.base_params = &iwl9000_base_params,
	.mq_rx_supported = true,
	.rf_id = true,
	.पूर्णांकegrated = true,
	.xtal_latency = 670,
	.extra_phy_cfg_flags = FW_PHY_CFG_SHARED_CLK
पूर्ण;

स्थिर अक्षर iwl9162_name[] = "Intel(R) Wireless-AC 9162";
स्थिर अक्षर iwl9260_name[] = "Intel(R) Wireless-AC 9260";
स्थिर अक्षर iwl9260_1_name[] = "Intel(R) Wireless-AC 9260-1";
स्थिर अक्षर iwl9270_name[] = "Intel(R) Wireless-AC 9270";
स्थिर अक्षर iwl9461_name[] = "Intel(R) Wireless-AC 9461";
स्थिर अक्षर iwl9462_name[] = "Intel(R) Wireless-AC 9462";
स्थिर अक्षर iwl9560_name[] = "Intel(R) Wireless-AC 9560";
स्थिर अक्षर iwl9162_160_name[] = "Intel(R) Wireless-AC 9162 160MHz";
स्थिर अक्षर iwl9260_160_name[] = "Intel(R) Wireless-AC 9260 160MHz";
स्थिर अक्षर iwl9270_160_name[] = "Intel(R) Wireless-AC 9270 160MHz";
स्थिर अक्षर iwl9461_160_name[] = "Intel(R) Wireless-AC 9461 160MHz";
स्थिर अक्षर iwl9462_160_name[] = "Intel(R) Wireless-AC 9462 160MHz";
स्थिर अक्षर iwl9560_160_name[] = "Intel(R) Wireless-AC 9560 160MHz";

स्थिर अक्षर iwl9260_समाप्तer_1550_name[] =
	"Killer (R) Wireless-AC 1550 Wireless Network Adapter (9260NGW) 160MHz";
स्थिर अक्षर iwl9560_समाप्तer_1550i_name[] =
	"Killer (R) Wireless-AC 1550i Wireless Network Adapter (9560NGW)";
स्थिर अक्षर iwl9560_समाप्तer_1550s_name[] =
	"Killer (R) Wireless-AC 1550s Wireless Network Adapter (9560NGW)";

स्थिर काष्ठा iwl_cfg iwl9260_2ac_cfg = अणु
	.fw_name_pre = IWL9260_FW_PRE,
	IWL_DEVICE_9000,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl9560_2ac_cfg_soc = अणु
	.fw_name_pre = IWL9000_FW_PRE,
	IWL_DEVICE_9000,
पूर्ण;

MODULE_FIRMWARE(IWL9000_MODULE_FIRMWARE(IWL9000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL9260_MODULE_FIRMWARE(IWL9000_UCODE_API_MAX));
