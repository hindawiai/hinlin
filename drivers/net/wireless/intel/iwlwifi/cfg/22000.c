<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश "iwl-config.h"
#समावेश "iwl-prph.h"

/* Highest firmware API version supported */
#घोषणा IWL_22000_UCODE_API_MAX	63

/* Lowest firmware API version supported */
#घोषणा IWL_22000_UCODE_API_MIN	39

/* NVM versions */
#घोषणा IWL_22000_NVM_VERSION		0x0a1d

/* Memory offsets and lengths */
#घोषणा IWL_22000_DCCM_OFFSET		0x800000 /* LMAC1 */
#घोषणा IWL_22000_DCCM_LEN		0x10000 /* LMAC1 */
#घोषणा IWL_22000_DCCM2_OFFSET		0x880000
#घोषणा IWL_22000_DCCM2_LEN		0x8000
#घोषणा IWL_22000_SMEM_OFFSET		0x400000
#घोषणा IWL_22000_SMEM_LEN		0xD0000

#घोषणा IWL_QU_B_HR_B_FW_PRE		"iwlwifi-Qu-b0-hr-b0-"
#घोषणा IWL_QNJ_B_HR_B_FW_PRE		"iwlwifi-QuQnj-b0-hr-b0-"
#घोषणा IWL_QU_C_HR_B_FW_PRE		"iwlwifi-Qu-c0-hr-b0-"
#घोषणा IWL_QU_B_JF_B_FW_PRE		"iwlwifi-Qu-b0-jf-b0-"
#घोषणा IWL_QU_C_JF_B_FW_PRE		"iwlwifi-Qu-c0-jf-b0-"
#घोषणा IWL_QUZ_A_HR_B_FW_PRE		"iwlwifi-QuZ-a0-hr-b0-"
#घोषणा IWL_QUZ_A_JF_B_FW_PRE		"iwlwifi-QuZ-a0-jf-b0-"
#घोषणा IWL_QNJ_B_JF_B_FW_PRE		"iwlwifi-QuQnj-b0-jf-b0-"
#घोषणा IWL_CC_A_FW_PRE			"iwlwifi-cc-a0-"
#घोषणा IWL_SO_A_JF_B_FW_PRE		"iwlwifi-so-a0-jf-b0-"
#घोषणा IWL_SO_A_HR_B_FW_PRE		"iwlwifi-so-a0-hr-b0-"
#घोषणा IWL_SO_A_GF_A_FW_PRE		"iwlwifi-so-a0-gf-a0-"
#घोषणा IWL_TY_A_GF_A_FW_PRE		"iwlwifi-ty-a0-gf-a0-"
#घोषणा IWL_SO_A_GF4_A_FW_PRE		"iwlwifi-so-a0-gf4-a0-"
#घोषणा IWL_SNJ_A_GF4_A_FW_PRE		"iwlwifi-SoSnj-a0-gf4-a0-"
#घोषणा IWL_SNJ_A_GF_A_FW_PRE		"iwlwifi-SoSnj-a0-gf-a0-"
#घोषणा IWL_SNJ_A_HR_B_FW_PRE		"iwlwifi-SoSnj-a0-hr-b0-"
#घोषणा IWL_SNJ_A_JF_B_FW_PRE		"iwlwifi-SoSnj-a0-jf-b0-"
#घोषणा IWL_MA_A_HR_B_FW_PRE		"iwlwifi-ma-a0-hr-b0-"
#घोषणा IWL_MA_A_GF_A_FW_PRE		"iwlwifi-ma-a0-gf-a0-"
#घोषणा IWL_MA_A_GF4_A_FW_PRE		"iwlwifi-ma-a0-gf4-a0-"
#घोषणा IWL_MA_A_MR_A_FW_PRE		"iwlwifi-ma-a0-mr-a0-"
#घोषणा IWL_SNJ_A_MR_A_FW_PRE		"iwlwifi-SoSnj-a0-mr-a0-"
#घोषणा IWL_BZ_A_HR_B_FW_PRE		"iwlwifi-bz-a0-hr-b0-"
#घोषणा IWL_BZ_A_GF_A_FW_PRE		"iwlwifi-bz-a0-gf-a0-"
#घोषणा IWL_BZ_A_GF4_A_FW_PRE		"iwlwifi-bz-a0-gf4-a0-"
#घोषणा IWL_BZ_A_MR_A_FW_PRE		"iwlwifi-bz-a0-mr-a0-"

#घोषणा IWL_QU_B_HR_B_MODULE_FIRMWARE(api) \
	IWL_QU_B_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_QNJ_B_HR_B_MODULE_FIRMWARE(api)	\
	IWL_QNJ_B_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_QUZ_A_HR_B_MODULE_FIRMWARE(api) \
	IWL_QUZ_A_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_QUZ_A_JF_B_MODULE_FIRMWARE(api) \
	IWL_QUZ_A_JF_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_QU_C_HR_B_MODULE_FIRMWARE(api) \
	IWL_QU_C_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_QU_B_JF_B_MODULE_FIRMWARE(api) \
	IWL_QU_B_JF_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_QNJ_B_JF_B_MODULE_FIRMWARE(api)		\
	IWL_QNJ_B_JF_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_CC_A_MODULE_FIRMWARE(api)			\
	IWL_CC_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SO_A_JF_B_MODULE_FIRMWARE(api) \
	IWL_SO_A_JF_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SO_A_HR_B_MODULE_FIRMWARE(api) \
	IWL_SO_A_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SO_A_GF_A_MODULE_FIRMWARE(api) \
	IWL_SO_A_GF_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_TY_A_GF_A_MODULE_FIRMWARE(api) \
	IWL_TY_A_GF_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SNJ_A_GF4_A_MODULE_FIRMWARE(api) \
	IWL_SNJ_A_GF4_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SNJ_A_GF_A_MODULE_FIRMWARE(api) \
	IWL_SNJ_A_GF_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SNJ_A_HR_B_MODULE_FIRMWARE(api) \
	IWL_SNJ_A_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SNJ_A_JF_B_MODULE_FIRMWARE(api) \
	IWL_SNJ_A_JF_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_MA_A_HR_B_FW_MODULE_FIRMWARE(api)		\
	IWL_MA_A_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_MA_A_GF_A_FW_MODULE_FIRMWARE(api)		\
	IWL_MA_A_GF_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_MA_A_GF4_A_FW_MODULE_FIRMWARE(api)		\
	IWL_MA_A_GF4_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_MA_A_MR_A_FW_MODULE_FIRMWARE(api) \
	IWL_MA_A_MR_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_SNJ_A_MR_A_MODULE_FIRMWARE(api) \
	IWL_SNJ_A_MR_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_BZ_A_HR_B_MODULE_FIRMWARE(api) \
	IWL_BZ_A_HR_B_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_BZ_A_GF_A_MODULE_FIRMWARE(api) \
	IWL_BZ_A_GF_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_BZ_A_GF4_A_MODULE_FIRMWARE(api) \
	IWL_BZ_A_GF4_A_FW_PRE __stringअगरy(api) ".ucode"
#घोषणा IWL_BZ_A_MR_A_MODULE_FIRMWARE(api) \
	IWL_BZ_A_MR_A_FW_PRE __stringअगरy(api) ".ucode"

अटल स्थिर काष्ठा iwl_base_params iwl_22000_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_32K,
	.num_of_queues = 512,
	.max_tfd_queue_size = 256,
	.shaकरोw_ram_support = true,
	.led_compensation = 57,
	.wd_समयout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = true,
	.pcie_l1_allowed = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_base_params iwl_ax210_base_params = अणु
	.eeprom_size = OTP_LOW_IMAGE_SIZE_32K,
	.num_of_queues = 512,
	.max_tfd_queue_size = 65536,
	.shaकरोw_ram_support = true,
	.led_compensation = 57,
	.wd_समयout = IWL_LONG_WD_TIMEOUT,
	.max_event_log_size = 512,
	.shaकरोw_reg_enable = true,
	.pcie_l1_allowed = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_ht_params iwl_22000_ht_params = अणु
	.stbc = true,
	.ldpc = true,
	.ht40_bands = BIT(NL80211_BAND_2GHZ) | BIT(NL80211_BAND_5GHZ) |
		      BIT(NL80211_BAND_6GHZ),
पूर्ण;

#घोषणा IWL_DEVICE_22000_COMMON						\
	.ucode_api_max = IWL_22000_UCODE_API_MAX,			\
	.ucode_api_min = IWL_22000_UCODE_API_MIN,			\
	.led_mode = IWL_LED_RF_STATE,					\
	.nvm_hw_section_num = 10,					\
	.non_shared_ant = ANT_B,					\
	.dccm_offset = IWL_22000_DCCM_OFFSET,				\
	.dccm_len = IWL_22000_DCCM_LEN,					\
	.dccm2_offset = IWL_22000_DCCM2_OFFSET,				\
	.dccm2_len = IWL_22000_DCCM2_LEN,				\
	.smem_offset = IWL_22000_SMEM_OFFSET,				\
	.smem_len = IWL_22000_SMEM_LEN,					\
	.features = IWL_TX_CSUM_NETIF_FLAGS | NETIF_F_RXCSUM,		\
	.apmg_not_supported = true,					\
	.trans.mq_rx_supported = true,					\
	.vht_mu_mimo_supported = true,					\
	.mac_addr_from_csr = true,					\
	.ht_params = &iwl_22000_ht_params,				\
	.nvm_ver = IWL_22000_NVM_VERSION,				\
	.trans.use_tfh = true,						\
	.trans.rf_id = true,						\
	.trans.gen2 = true,						\
	.nvm_type = IWL_NVM_EXT,					\
	.dbgc_supported = true,						\
	.min_umac_error_event_table = 0x400000,				\
	.d3_debug_data_base_addr = 0x401000,				\
	.d3_debug_data_length = 60 * 1024,				\
	.mon_smem_regs = अणु						\
		.ग_लिखो_ptr = अणु						\
			.addr = LDBG_M2S_BUF_WPTR,			\
			.mask = LDBG_M2S_BUF_WPTR_VAL_MSK,		\
	पूर्ण,								\
		.cycle_cnt = अणु						\
			.addr = LDBG_M2S_BUF_WRAP_CNT,			\
			.mask = LDBG_M2S_BUF_WRAP_CNT_VAL_MSK,		\
		पूर्ण,							\
	पूर्ण

#घोषणा IWL_DEVICE_22500						\
	IWL_DEVICE_22000_COMMON,					\
	.trans.device_family = IWL_DEVICE_FAMILY_22000,			\
	.trans.base_params = &iwl_22000_base_params,			\
	.gp2_reg_addr = 0xa02c68,					\
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

#घोषणा IWL_DEVICE_AX210						\
	IWL_DEVICE_22000_COMMON,					\
	.trans.umac_prph_offset = 0x300000,				\
	.trans.device_family = IWL_DEVICE_FAMILY_AX210,			\
	.trans.base_params = &iwl_ax210_base_params,			\
	.min_txq_size = 128,						\
	.gp2_reg_addr = 0xd02c68,					\
	.min_256_ba_txq_size = 1024,					\
	.mon_dram_regs = अणु						\
		.ग_लिखो_ptr = अणु						\
			.addr = DBGC_CUR_DBGBUF_STATUS,			\
			.mask = DBGC_CUR_DBGBUF_STATUS_OFFSET_MSK,	\
		पूर्ण,							\
		.cycle_cnt = अणु						\
			.addr = DBGC_DBGBUF_WRAP_AROUND,		\
			.mask = 0xffffffff,				\
		पूर्ण,							\
		.cur_frag = अणु						\
			.addr = DBGC_CUR_DBGBUF_STATUS,			\
			.mask = DBGC_CUR_DBGBUF_STATUS_IDX_MSK,		\
		पूर्ण,							\
	पूर्ण

स्थिर काष्ठा iwl_cfg_trans_params iwl_qnj_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_22000,
	.base_params = &iwl_22000_base_params,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_qu_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_22000,
	.base_params = &iwl_22000_base_params,
	.पूर्णांकegrated = true,
	.xtal_latency = 500,
	.ltr_delay = IWL_CFG_TRANS_LTR_DELAY_200US,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_qu_medium_latency_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_22000,
	.base_params = &iwl_22000_base_params,
	.पूर्णांकegrated = true,
	.xtal_latency = 1820,
	.ltr_delay = IWL_CFG_TRANS_LTR_DELAY_1820US,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_qu_दीर्घ_latency_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_22000,
	.base_params = &iwl_22000_base_params,
	.पूर्णांकegrated = true,
	.xtal_latency = 12000,
	.low_latency_xtal = true,
	.ltr_delay = IWL_CFG_TRANS_LTR_DELAY_2500US,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_snj_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_AX210,
	.base_params = &iwl_ax210_base_params,
	.umac_prph_offset = 0x300000,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_so_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_AX210,
	.base_params = &iwl_ax210_base_params,
	.umac_prph_offset = 0x300000,
	.पूर्णांकegrated = true,
	/* TODO: the following values need to be checked */
	.xtal_latency = 500,
	.ltr_delay = IWL_CFG_TRANS_LTR_DELAY_200US,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_so_दीर्घ_latency_trans_cfg = अणु
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.device_family = IWL_DEVICE_FAMILY_AX210,
	.base_params = &iwl_ax210_base_params,
	.umac_prph_offset = 0x300000,
	.पूर्णांकegrated = true,
	/* TODO: the following values need to be checked */
	.xtal_latency = 12000,
	.ltr_delay = IWL_CFG_TRANS_LTR_DELAY_2500US,
पूर्ण;

/*
 * If the device करोesn't support HE, no need to have that many buffers.
 * 22000 devices can split multiple frames पूर्णांकo a single RB, so fewer are
 * needed; AX210 cannot (but use smaller RBs by शेष) - these sizes
 * were picked according to 8 MSDUs inside 256 A-MSDUs in an A-MPDU, with
 * additional overhead to account क्रम processing समय.
 */
#घोषणा IWL_NUM_RBDS_NON_HE		512
#घोषणा IWL_NUM_RBDS_22000_HE		2048
#घोषणा IWL_NUM_RBDS_AX210_HE		4096

/*
 * All JF radio modules are part of the 9000 series, but the MAC part
 * looks more like 22000.  That's why this device is here, but called
 * 9560 nevertheless.
 */
स्थिर काष्ठा iwl_cfg iwl9560_qu_b0_jf_b0_cfg = अणु
	.fw_name_pre = IWL_QU_B_JF_B_FW_PRE,
	IWL_DEVICE_22500,
	.num_rbds = IWL_NUM_RBDS_NON_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl9560_qu_c0_jf_b0_cfg = अणु
	.fw_name_pre = IWL_QU_C_JF_B_FW_PRE,
	IWL_DEVICE_22500,
	.num_rbds = IWL_NUM_RBDS_NON_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl9560_quz_a0_jf_b0_cfg = अणु
	.fw_name_pre = IWL_QUZ_A_JF_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_NON_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl9560_qnj_b0_jf_b0_cfg = अणु
	.fw_name_pre = IWL_QNJ_B_JF_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_NON_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_ax200_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_22000,
	.base_params = &iwl_22000_base_params,
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.bisr_workaround = 1,
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_ma_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_AX210,
	.base_params = &iwl_ax210_base_params,
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.पूर्णांकegrated = true,
	.umac_prph_offset = 0x300000
पूर्ण;

स्थिर काष्ठा iwl_cfg_trans_params iwl_bz_trans_cfg = अणु
	.device_family = IWL_DEVICE_FAMILY_AX210,
	.base_params = &iwl_ax210_base_params,
	.mq_rx_supported = true,
	.use_tfh = true,
	.rf_id = true,
	.gen2 = true,
	.पूर्णांकegrated = true,
	.umac_prph_offset = 0x300000,
	.xtal_latency = 12000,
	.low_latency_xtal = true,
	.ltr_delay = IWL_CFG_TRANS_LTR_DELAY_2500US,
पूर्ण;

स्थिर अक्षर iwl_ax101_name[] = "Intel(R) Wi-Fi 6 AX101";
स्थिर अक्षर iwl_ax200_name[] = "Intel(R) Wi-Fi 6 AX200 160MHz";
स्थिर अक्षर iwl_ax201_name[] = "Intel(R) Wi-Fi 6 AX201 160MHz";
स्थिर अक्षर iwl_ax203_name[] = "Intel(R) Wi-Fi 6 AX203";
स्थिर अक्षर iwl_ax211_name[] = "Intel(R) Wi-Fi 6E AX211 160MHz";
स्थिर अक्षर iwl_ax221_name[] = "Intel(R) Wi-Fi 6E AX221 160MHz";
स्थिर अक्षर iwl_ax411_name[] = "Intel(R) Wi-Fi 6E AX411 160MHz";

स्थिर अक्षर iwl_ax200_समाप्तer_1650w_name[] =
	"Killer(R) Wi-Fi 6 AX1650w 160MHz Wireless Network Adapter (200D2W)";
स्थिर अक्षर iwl_ax200_समाप्तer_1650x_name[] =
	"Killer(R) Wi-Fi 6 AX1650x 160MHz Wireless Network Adapter (200NGW)";
स्थिर अक्षर iwl_ax201_समाप्तer_1650s_name[] =
	"Killer(R) Wi-Fi 6 AX1650s 160MHz Wireless Network Adapter (201D2W)";
स्थिर अक्षर iwl_ax201_समाप्तer_1650i_name[] =
	"Killer(R) Wi-Fi 6 AX1650i 160MHz Wireless Network Adapter (201NGW)";
स्थिर अक्षर iwl_ax210_समाप्तer_1675w_name[] =
	"Killer(R) Wi-Fi 6E AX1675w 160MHz Wireless Network Adapter (210D2W)";
स्थिर अक्षर iwl_ax210_समाप्तer_1675x_name[] =
	"Killer(R) Wi-Fi 6E AX1675x 160MHz Wireless Network Adapter (210NGW)";

स्थिर काष्ठा iwl_cfg iwl_qu_b0_hr1_b0 = अणु
	.fw_name_pre = IWL_QU_B_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.tx_with_siso_भागersity = true,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_qu_b0_hr_b0 = अणु
	.fw_name_pre = IWL_QU_B_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_qu_hr = अणु
	.name = "Intel(R) Wi-Fi 6 AX201 160MHz",
	.fw_name_pre = IWL_QU_B_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_qu_c0_hr1_b0 = अणु
	.fw_name_pre = IWL_QU_C_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.tx_with_siso_भागersity = true,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_qu_c0_hr_b0 = अणु
	.fw_name_pre = IWL_QU_C_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_qu_c0_hr_b0 = अणु
	.name = "Intel(R) Wi-Fi 6 AX201 160MHz",
	.fw_name_pre = IWL_QU_C_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_quz_a0_hr1_b0 = अणु
	.fw_name_pre = IWL_QUZ_A_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.tx_with_siso_भागersity = true,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_quz_hr = अणु
	.name = "Intel(R) Wi-Fi 6 AX201 160MHz",
	.fw_name_pre = IWL_QUZ_A_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
         * This device करोesn't support receiving BlockAck with a large biपंचांगap
         * so we need to restrict the size of transmitted aggregation to the
         * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
         */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_ax1650s_cfg_quz_hr = अणु
	.name = "Killer(R) Wi-Fi 6 AX1650s 160MHz Wireless Network Adapter (201D2W)",
	.fw_name_pre = IWL_QUZ_A_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
         * This device करोesn't support receiving BlockAck with a large biपंचांगap
         * so we need to restrict the size of transmitted aggregation to the
         * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
         */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_ax1650i_cfg_quz_hr = अणु
	.name = "Killer(R) Wi-Fi 6 AX1650i 160MHz Wireless Network Adapter (201NGW)",
	.fw_name_pre = IWL_QUZ_A_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
         * This device करोesn't support receiving BlockAck with a large biपंचांगap
         * so we need to restrict the size of transmitted aggregation to the
         * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
         */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_ax200_cfg_cc = अणु
	.fw_name_pre = IWL_CC_A_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg समाप्तer1650s_2ax_cfg_qu_b0_hr_b0 = अणु
	.name = "Killer(R) Wi-Fi 6 AX1650i 160MHz Wireless Network Adapter (201NGW)",
	.fw_name_pre = IWL_QU_B_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg समाप्तer1650i_2ax_cfg_qu_b0_hr_b0 = अणु
	.name = "Killer(R) Wi-Fi 6 AX1650s 160MHz Wireless Network Adapter (201D2W)",
	.fw_name_pre = IWL_QU_B_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg समाप्तer1650s_2ax_cfg_qu_c0_hr_b0 = अणु
	.name = "Killer(R) Wi-Fi 6 AX1650i 160MHz Wireless Network Adapter (201NGW)",
	.fw_name_pre = IWL_QU_C_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg समाप्तer1650i_2ax_cfg_qu_c0_hr_b0 = अणु
	.name = "Killer(R) Wi-Fi 6 AX1650s 160MHz Wireless Network Adapter (201D2W)",
	.fw_name_pre = IWL_QU_C_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_qnj_b0_hr_b0_cfg = अणु
	.fw_name_pre = IWL_QNJ_B_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax210_2ax_cfg_so_jf_b0 = अणु
	.name = "Intel(R) Wireless-AC 9560 160MHz",
	.fw_name_pre = IWL_SO_A_JF_B_FW_PRE,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_NON_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax210_2ax_cfg_so_hr_a0 = अणु
	.name = "Intel(R) Wi-Fi 6 AX210 160MHz",
	.fw_name_pre = IWL_SO_A_HR_B_FW_PRE,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax211_2ax_cfg_so_gf_a0 = अणु
	.name = iwl_ax211_name,
	.fw_name_pre = IWL_SO_A_GF_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax211_2ax_cfg_so_gf_a0_दीर्घ = अणु
	.name = iwl_ax211_name,
	.fw_name_pre = IWL_SO_A_GF_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
	.trans.xtal_latency = 12000,
	.trans.low_latency_xtal = true,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax210_2ax_cfg_ty_gf_a0 = अणु
	.name = "Intel(R) Wi-Fi 6 AX210 160MHz",
	.fw_name_pre = IWL_TY_A_GF_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax411_2ax_cfg_so_gf4_a0 = अणु
	.name = iwl_ax411_name,
	.fw_name_pre = IWL_SO_A_GF4_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax411_2ax_cfg_so_gf4_a0_दीर्घ = अणु
	.name = iwl_ax411_name,
	.fw_name_pre = IWL_SO_A_GF4_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
	.trans.xtal_latency = 12000,
	.trans.low_latency_xtal = true,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax411_2ax_cfg_sosnj_gf4_a0 = अणु
	.name = iwl_ax411_name,
	.fw_name_pre = IWL_SNJ_A_GF4_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwlax211_cfg_snj_gf_a0 = अणु
	.name = iwl_ax211_name,
	.fw_name_pre = IWL_SNJ_A_GF_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_snj_hr_b0 = अणु
	.fw_name_pre = IWL_SNJ_A_HR_B_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_snj_a0_jf_b0 = अणु
	.fw_name_pre = IWL_SNJ_A_JF_B_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_hr_b0 = अणु
	.fw_name_pre = IWL_MA_A_HR_B_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_gf_a0 = अणु
	.fw_name_pre = IWL_MA_A_GF_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_gf4_a0 = अणु
	.fw_name_pre = IWL_MA_A_GF4_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_mr_a0 = अणु
	.fw_name_pre = IWL_MA_A_MR_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_snj_a0_mr_a0 = अणु
	.fw_name_pre = IWL_SNJ_A_MR_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_so_a0_hr_a0 = अणु
	.fw_name_pre = IWL_SO_A_HR_B_FW_PRE,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_quz_a0_hr_b0 = अणु
	.fw_name_pre = IWL_QUZ_A_HR_B_FW_PRE,
	IWL_DEVICE_22500,
	/*
	 * This device करोesn't support receiving BlockAck with a large biपंचांगap
	 * so we need to restrict the size of transmitted aggregation to the
	 * HT size; mac80211 would otherwise pick the HE max (256) by शेष.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_rbds = IWL_NUM_RBDS_22000_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_hr_b0 = अणु
	.fw_name_pre = IWL_BZ_A_HR_B_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_gf_a0 = अणु
	.fw_name_pre = IWL_BZ_A_GF_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_gf4_a0 = अणु
	.fw_name_pre = IWL_BZ_A_GF4_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_mr_a0 = अणु
	.fw_name_pre = IWL_BZ_A_MR_A_FW_PRE,
	.uhb_supported = true,
	IWL_DEVICE_AX210,
	.num_rbds = IWL_NUM_RBDS_AX210_HE,
पूर्ण;

MODULE_FIRMWARE(IWL_QU_B_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_QNJ_B_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_QU_C_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_QU_B_JF_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_QUZ_A_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_QUZ_A_JF_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_QNJ_B_JF_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_CC_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SO_A_JF_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SO_A_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SO_A_GF_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_TY_A_GF_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SNJ_A_GF4_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SNJ_A_GF_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SNJ_A_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SNJ_A_JF_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_MA_A_HR_B_FW_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_MA_A_GF_A_FW_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_MA_A_GF4_A_FW_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_MA_A_MR_A_FW_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_SNJ_A_MR_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_BZ_A_HR_B_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_BZ_A_GF_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_BZ_A_GF4_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
MODULE_FIRMWARE(IWL_BZ_A_MR_A_MODULE_FIRMWARE(IWL_22000_UCODE_API_MAX));
