<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/dmi.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/pm_qos.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "core.h"
#समावेश "mac.h"
#समावेश "htc.h"
#समावेश "hif.h"
#समावेश "wmi.h"
#समावेश "bmi.h"
#समावेश "debug.h"
#समावेश "htt.h"
#समावेश "testmode.h"
#समावेश "wmi-ops.h"
#समावेश "coredump.h"

अचिन्हित पूर्णांक ath10k_debug_mask;
EXPORT_SYMBOL(ath10k_debug_mask);

अटल अचिन्हित पूर्णांक ath10k_crypपंचांगode_param;
अटल bool uart_prपूर्णांक;
अटल bool skip_otp;
अटल bool rawmode;
अटल bool fw_diag_log;

अचिन्हित दीर्घ ath10k_coredump_mask = BIT(ATH10K_FW_CRASH_DUMP_REGISTERS) |
				     BIT(ATH10K_FW_CRASH_DUMP_CE_DATA);

/* FIXME: most of these should be पढ़ोonly */
module_param_named(debug_mask, ath10k_debug_mask, uपूर्णांक, 0644);
module_param_named(crypपंचांगode, ath10k_crypपंचांगode_param, uपूर्णांक, 0644);
module_param(uart_prपूर्णांक, bool, 0644);
module_param(skip_otp, bool, 0644);
module_param(rawmode, bool, 0644);
module_param(fw_diag_log, bool, 0644);
module_param_named(coredump_mask, ath10k_coredump_mask, uदीर्घ, 0444);

MODULE_PARM_DESC(debug_mask, "Debugging mask");
MODULE_PARM_DESC(uart_prपूर्णांक, "Uart target debugging");
MODULE_PARM_DESC(skip_otp, "Skip otp failure for calibration in testmode");
MODULE_PARM_DESC(crypपंचांगode, "Crypto mode: 0-hardware, 1-software");
MODULE_PARM_DESC(rawmode, "Use raw 802.11 frame datapath");
MODULE_PARM_DESC(coredump_mask, "Bitfield of what to include in firmware crash file");
MODULE_PARM_DESC(fw_diag_log, "Diag based fw log debugging");

अटल स्थिर काष्ठा ath10k_hw_params ath10k_hw_params_list[] = अणु
	अणु
		.id = QCA988X_HW_2_0_VERSION,
		.dev_id = QCA988X_2_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca988x hw2.0",
		.patch_load_addr = QCA988X_HW_2_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.cc_wraparound_type = ATH10K_HW_CC_WRAP_SHIFTED_ALL,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 2116,
		.fw = अणु
			.dir = QCA988X_HW_2_0_FW_सूची,
			.board = QCA988X_HW_2_0_BOARD_DATA_खाता,
			.board_size = QCA988X_BOARD_DATA_SZ,
			.board_ext_size = QCA988X_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = true,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA988X_HW_2_0_VERSION,
		.dev_id = QCA988X_2_0_DEVICE_ID_UBNT,
		.name = "qca988x hw2.0 ubiquiti",
		.patch_load_addr = QCA988X_HW_2_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.cc_wraparound_type = ATH10K_HW_CC_WRAP_SHIFTED_ALL,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 2116,
		.fw = अणु
			.dir = QCA988X_HW_2_0_FW_सूची,
			.board = QCA988X_HW_2_0_BOARD_DATA_खाता,
			.board_size = QCA988X_BOARD_DATA_SZ,
			.board_ext_size = QCA988X_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = true,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA9887_HW_1_0_VERSION,
		.dev_id = QCA9887_1_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca9887 hw1.0",
		.patch_load_addr = QCA9887_HW_1_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.cc_wraparound_type = ATH10K_HW_CC_WRAP_SHIFTED_ALL,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 2116,
		.fw = अणु
			.dir = QCA9887_HW_1_0_FW_सूची,
			.board = QCA9887_HW_1_0_BOARD_DATA_खाता,
			.board_size = QCA9887_BOARD_DATA_SZ,
			.board_ext_size = QCA9887_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA6174_HW_3_2_VERSION,
		.dev_id = QCA6174_3_2_DEVICE_ID,
		.bus = ATH10K_BUS_SDIO,
		.name = "qca6174 hw3.2 sdio",
		.patch_load_addr = QCA6174_HW_3_0_PATCH_LOAD_ADDR,
		.uart_pin = 19,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 0,
		.fw = अणु
			.dir = QCA6174_HW_3_0_FW_सूची,
			.board = QCA6174_HW_3_0_BOARD_DATA_खाता,
			.board_size = QCA6174_BOARD_DATA_SZ,
			.board_ext_size = QCA6174_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca6174_sdio_ops,
		.hw_clk = qca6174_clk,
		.target_cpu_freq = 176000000,
		.decap_align_bytes = 4,
		.n_cipher_suites = 8,
		.num_peers = 10,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.uart_pin_workaround = true,
		.tx_stats_over_pktlog = false,
		.bmi_large_size_करोwnload = true,
		.supports_peer_stats_info = true,
		.dynamic_sar_support = true,
	पूर्ण,
	अणु
		.id = QCA6174_HW_2_1_VERSION,
		.dev_id = QCA6164_2_1_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca6164 hw2.1",
		.patch_load_addr = QCA6174_HW_2_1_PATCH_LOAD_ADDR,
		.uart_pin = 6,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			.dir = QCA6174_HW_2_1_FW_सूची,
			.board = QCA6174_HW_2_1_BOARD_DATA_खाता,
			.board_size = QCA6174_BOARD_DATA_SZ,
			.board_ext_size = QCA6174_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA6174_HW_2_1_VERSION,
		.dev_id = QCA6174_2_1_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca6174 hw2.1",
		.patch_load_addr = QCA6174_HW_2_1_PATCH_LOAD_ADDR,
		.uart_pin = 6,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			.dir = QCA6174_HW_2_1_FW_सूची,
			.board = QCA6174_HW_2_1_BOARD_DATA_खाता,
			.board_size = QCA6174_BOARD_DATA_SZ,
			.board_ext_size = QCA6174_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA6174_HW_3_0_VERSION,
		.dev_id = QCA6174_2_1_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca6174 hw3.0",
		.patch_load_addr = QCA6174_HW_3_0_PATCH_LOAD_ADDR,
		.uart_pin = 6,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			.dir = QCA6174_HW_3_0_FW_सूची,
			.board = QCA6174_HW_3_0_BOARD_DATA_खाता,
			.board_size = QCA6174_BOARD_DATA_SZ,
			.board_ext_size = QCA6174_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA6174_HW_3_2_VERSION,
		.dev_id = QCA6174_2_1_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca6174 hw3.2",
		.patch_load_addr = QCA6174_HW_3_0_PATCH_LOAD_ADDR,
		.uart_pin = 6,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			/* uses same binaries as hw3.0 */
			.dir = QCA6174_HW_3_0_FW_सूची,
			.board = QCA6174_HW_3_0_BOARD_DATA_खाता,
			.board_size = QCA6174_BOARD_DATA_SZ,
			.board_ext_size = QCA6174_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca6174_ops,
		.hw_clk = qca6174_clk,
		.target_cpu_freq = 176000000,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = true,
		.tx_stats_over_pktlog = false,
		.supports_peer_stats_info = true,
		.dynamic_sar_support = true,
	पूर्ण,
	अणु
		.id = QCA99X0_HW_2_0_DEV_VERSION,
		.dev_id = QCA99X0_2_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca99x0 hw2.0",
		.patch_load_addr = QCA99X0_HW_2_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.otp_exe_param = 0x00000700,
		.continuous_frag_desc = true,
		.cck_rate_map_rev2 = true,
		.channel_counters_freq_hz = 150000,
		.max_probe_resp_desc_thres = 24,
		.tx_chain_mask = 0xf,
		.rx_chain_mask = 0xf,
		.max_spatial_stream = 4,
		.cal_data_len = 12064,
		.fw = अणु
			.dir = QCA99X0_HW_2_0_FW_सूची,
			.board = QCA99X0_HW_2_0_BOARD_DATA_खाता,
			.board_size = QCA99X0_BOARD_DATA_SZ,
			.board_ext_size = QCA99X0_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.sw_decrypt_mcast_mgmt = true,
		.hw_ops = &qca99x0_ops,
		.decap_align_bytes = 1,
		.spectral_bin_discard = 4,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 11,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA9984_HW_1_0_DEV_VERSION,
		.dev_id = QCA9984_1_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca9984/qca9994 hw1.0",
		.patch_load_addr = QCA9984_HW_1_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.cc_wraparound_type = ATH10K_HW_CC_WRAP_SHIFTED_EACH,
		.otp_exe_param = 0x00000700,
		.continuous_frag_desc = true,
		.cck_rate_map_rev2 = true,
		.channel_counters_freq_hz = 150000,
		.max_probe_resp_desc_thres = 24,
		.tx_chain_mask = 0xf,
		.rx_chain_mask = 0xf,
		.max_spatial_stream = 4,
		.cal_data_len = 12064,
		.fw = अणु
			.dir = QCA9984_HW_1_0_FW_सूची,
			.board = QCA9984_HW_1_0_BOARD_DATA_खाता,
			.eboard = QCA9984_HW_1_0_EBOARD_DATA_खाता,
			.board_size = QCA99X0_BOARD_DATA_SZ,
			.board_ext_size = QCA99X0_BOARD_EXT_DATA_SZ,
			.ext_board_size = QCA99X0_EXT_BOARD_DATA_SZ,
		पूर्ण,
		.sw_decrypt_mcast_mgmt = true,
		.hw_ops = &qca99x0_ops,
		.decap_align_bytes = 1,
		.spectral_bin_discard = 12,
		.spectral_bin_offset = 8,

		/* Can करो only 2x2 VHT160 or 80+80. 1560Mbps is 4x4 80Mhz
		 * or 2x2 160Mhz, दीर्घ-guard-पूर्णांकerval.
		 */
		.vht160_mcs_rx_highest = 1560,
		.vht160_mcs_tx_highest = 1560,
		.n_cipher_suites = 11,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA9888_HW_2_0_DEV_VERSION,
		.dev_id = QCA9888_2_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca9888 hw2.0",
		.patch_load_addr = QCA9888_HW_2_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.cc_wraparound_type = ATH10K_HW_CC_WRAP_SHIFTED_EACH,
		.otp_exe_param = 0x00000700,
		.continuous_frag_desc = true,
		.channel_counters_freq_hz = 150000,
		.max_probe_resp_desc_thres = 24,
		.tx_chain_mask = 3,
		.rx_chain_mask = 3,
		.max_spatial_stream = 2,
		.cal_data_len = 12064,
		.fw = अणु
			.dir = QCA9888_HW_2_0_FW_सूची,
			.board = QCA9888_HW_2_0_BOARD_DATA_खाता,
			.board_size = QCA99X0_BOARD_DATA_SZ,
			.board_ext_size = QCA99X0_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.sw_decrypt_mcast_mgmt = true,
		.hw_ops = &qca99x0_ops,
		.decap_align_bytes = 1,
		.spectral_bin_discard = 12,
		.spectral_bin_offset = 8,

		/* Can करो only 1x1 VHT160 or 80+80. 780Mbps is 2x2 80Mhz or
		 * 1x1 160Mhz, दीर्घ-guard-पूर्णांकerval.
		 */
		.vht160_mcs_rx_highest = 780,
		.vht160_mcs_tx_highest = 780,
		.n_cipher_suites = 11,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA9377_HW_1_0_DEV_VERSION,
		.dev_id = QCA9377_1_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca9377 hw1.0",
		.patch_load_addr = QCA9377_HW_1_0_PATCH_LOAD_ADDR,
		.uart_pin = 6,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			.dir = QCA9377_HW_1_0_FW_सूची,
			.board = QCA9377_HW_1_0_BOARD_DATA_खाता,
			.board_size = QCA9377_BOARD_DATA_SZ,
			.board_ext_size = QCA9377_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca988x_ops,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA9377_HW_1_1_DEV_VERSION,
		.dev_id = QCA9377_1_0_DEVICE_ID,
		.bus = ATH10K_BUS_PCI,
		.name = "qca9377 hw1.1",
		.patch_load_addr = QCA9377_HW_1_0_PATCH_LOAD_ADDR,
		.uart_pin = 6,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			.dir = QCA9377_HW_1_0_FW_सूची,
			.board = QCA9377_HW_1_0_BOARD_DATA_खाता,
			.board_size = QCA9377_BOARD_DATA_SZ,
			.board_ext_size = QCA9377_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca6174_ops,
		.hw_clk = qca6174_clk,
		.target_cpu_freq = 176000000,
		.decap_align_bytes = 4,
		.spectral_bin_discard = 0,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 8,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = true,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA9377_HW_1_1_DEV_VERSION,
		.dev_id = QCA9377_1_0_DEVICE_ID,
		.bus = ATH10K_BUS_SDIO,
		.name = "qca9377 hw1.1 sdio",
		.patch_load_addr = QCA9377_HW_1_0_PATCH_LOAD_ADDR,
		.uart_pin = 19,
		.otp_exe_param = 0,
		.channel_counters_freq_hz = 88000,
		.max_probe_resp_desc_thres = 0,
		.cal_data_len = 8124,
		.fw = अणु
			.dir = QCA9377_HW_1_0_FW_सूची,
			.board = QCA9377_HW_1_0_BOARD_DATA_खाता,
			.board_size = QCA9377_BOARD_DATA_SZ,
			.board_ext_size = QCA9377_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.hw_ops = &qca6174_ops,
		.hw_clk = qca6174_clk,
		.target_cpu_freq = 176000000,
		.decap_align_bytes = 4,
		.n_cipher_suites = 8,
		.num_peers = TARGET_QCA9377_HL_NUM_PEERS,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.uart_pin_workaround = true,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = QCA4019_HW_1_0_DEV_VERSION,
		.dev_id = 0,
		.bus = ATH10K_BUS_AHB,
		.name = "qca4019 hw1.0",
		.patch_load_addr = QCA4019_HW_1_0_PATCH_LOAD_ADDR,
		.uart_pin = 7,
		.cc_wraparound_type = ATH10K_HW_CC_WRAP_SHIFTED_EACH,
		.otp_exe_param = 0x0010000,
		.continuous_frag_desc = true,
		.cck_rate_map_rev2 = true,
		.channel_counters_freq_hz = 125000,
		.max_probe_resp_desc_thres = 24,
		.tx_chain_mask = 0x3,
		.rx_chain_mask = 0x3,
		.max_spatial_stream = 2,
		.cal_data_len = 12064,
		.fw = अणु
			.dir = QCA4019_HW_1_0_FW_सूची,
			.board = QCA4019_HW_1_0_BOARD_DATA_खाता,
			.board_size = QCA4019_BOARD_DATA_SZ,
			.board_ext_size = QCA4019_BOARD_EXT_DATA_SZ,
		पूर्ण,
		.sw_decrypt_mcast_mgmt = true,
		.hw_ops = &qca99x0_ops,
		.decap_align_bytes = 1,
		.spectral_bin_discard = 4,
		.spectral_bin_offset = 0,
		.vht160_mcs_rx_highest = 0,
		.vht160_mcs_tx_highest = 0,
		.n_cipher_suites = 11,
		.ast_skid_limit = 0x10,
		.num_wds_entries = 0x20,
		.target_64bit = false,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL,
		.shaकरोw_reg_support = false,
		.rri_on_ddr = false,
		.hw_filter_reset_required = true,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = false,
	पूर्ण,
	अणु
		.id = WCN3990_HW_1_0_DEV_VERSION,
		.dev_id = 0,
		.bus = ATH10K_BUS_SNOC,
		.name = "wcn3990 hw1.0",
		.continuous_frag_desc = true,
		.tx_chain_mask = 0x7,
		.rx_chain_mask = 0x7,
		.max_spatial_stream = 4,
		.fw = अणु
			.dir = WCN3990_HW_1_0_FW_सूची,
		पूर्ण,
		.sw_decrypt_mcast_mgmt = true,
		.hw_ops = &wcn3990_ops,
		.decap_align_bytes = 1,
		.num_peers = TARGET_HL_TLV_NUM_PEERS,
		.n_cipher_suites = 11,
		.ast_skid_limit = TARGET_HL_TLV_AST_SKID_LIMIT,
		.num_wds_entries = TARGET_HL_TLV_NUM_WDS_ENTRIES,
		.target_64bit = true,
		.rx_ring_fill_level = HTT_RX_RING_FILL_LEVEL_DUAL_MAC,
		.shaकरोw_reg_support = true,
		.rri_on_ddr = true,
		.hw_filter_reset_required = false,
		.fw_diag_ce_करोwnload = false,
		.tx_stats_over_pktlog = false,
		.dynamic_sar_support = true,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ath10k_core_fw_feature_str[] = अणु
	[ATH10K_FW_FEATURE_EXT_WMI_MGMT_RX] = "wmi-mgmt-rx",
	[ATH10K_FW_FEATURE_WMI_10X] = "wmi-10.x",
	[ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX] = "has-wmi-mgmt-tx",
	[ATH10K_FW_FEATURE_NO_P2P] = "no-p2p",
	[ATH10K_FW_FEATURE_WMI_10_2] = "wmi-10.2",
	[ATH10K_FW_FEATURE_MULTI_VIF_PS_SUPPORT] = "multi-vif-ps",
	[ATH10K_FW_FEATURE_WOWLAN_SUPPORT] = "wowlan",
	[ATH10K_FW_FEATURE_IGNORE_OTP_RESULT] = "ignore-otp",
	[ATH10K_FW_FEATURE_NO_NWIFI_DECAP_4ADDR_PADDING] = "no-4addr-pad",
	[ATH10K_FW_FEATURE_SUPPORTS_SKIP_CLOCK_INIT] = "skip-clock-init",
	[ATH10K_FW_FEATURE_RAW_MODE_SUPPORT] = "raw-mode",
	[ATH10K_FW_FEATURE_SUPPORTS_ADAPTIVE_CCA] = "adaptive-cca",
	[ATH10K_FW_FEATURE_MFP_SUPPORT] = "mfp",
	[ATH10K_FW_FEATURE_PEER_FLOW_CONTROL] = "peer-flow-ctrl",
	[ATH10K_FW_FEATURE_BTCOEX_PARAM] = "btcoex-param",
	[ATH10K_FW_FEATURE_SKIP_शून्य_FUNC_WAR] = "skip-null-func-war",
	[ATH10K_FW_FEATURE_ALLOWS_MESH_BCAST] = "allows-mesh-bcast",
	[ATH10K_FW_FEATURE_NO_PS] = "no-ps",
	[ATH10K_FW_FEATURE_MGMT_TX_BY_REF] = "mgmt-tx-by-reference",
	[ATH10K_FW_FEATURE_NON_BMI] = "non-bmi",
	[ATH10K_FW_FEATURE_SINGLE_CHAN_INFO_PER_CHANNEL] = "single-chan-info-per-channel",
	[ATH10K_FW_FEATURE_PEER_FIXED_RATE] = "peer-fixed-rate",
	[ATH10K_FW_FEATURE_IRAM_RECOVERY] = "iram-recovery",
पूर्ण;

अटल अचिन्हित पूर्णांक ath10k_core_get_fw_feature_str(अक्षर *buf,
						   माप_प्रकार buf_len,
						   क्रमागत ath10k_fw_features feat)
अणु
	/* make sure that ath10k_core_fw_feature_str[] माला_लो updated */
	BUILD_BUG_ON(ARRAY_SIZE(ath10k_core_fw_feature_str) !=
		     ATH10K_FW_FEATURE_COUNT);

	अगर (feat >= ARRAY_SIZE(ath10k_core_fw_feature_str) ||
	    WARN_ON(!ath10k_core_fw_feature_str[feat])) अणु
		वापस scnम_लिखो(buf, buf_len, "bit%d", feat);
	पूर्ण

	वापस scnम_लिखो(buf, buf_len, "%s", ath10k_core_fw_feature_str[feat]);
पूर्ण

व्योम ath10k_core_get_fw_features_str(काष्ठा ath10k *ar,
				     अक्षर *buf,
				     माप_प्रकार buf_len)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ATH10K_FW_FEATURE_COUNT; i++) अणु
		अगर (test_bit(i, ar->normal_mode_fw.fw_file.fw_features)) अणु
			अगर (len > 0)
				len += scnम_लिखो(buf + len, buf_len - len, ",");

			len += ath10k_core_get_fw_feature_str(buf + len,
							      buf_len - len,
							      i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath10k_send_suspend_complete(काष्ठा ath10k *ar)
अणु
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot suspend complete\n");

	complete(&ar->target_suspend);
पूर्ण

अटल पूर्णांक ath10k_init_sdio(काष्ठा ath10k *ar, क्रमागत ath10k_firmware_mode mode)
अणु
	पूर्णांक ret;
	u32 param = 0;

	ret = ath10k_bmi_ग_लिखो32(ar, hi_mbox_io_block_sz, 256);
	अगर (ret)
		वापस ret;

	ret = ath10k_bmi_ग_लिखो32(ar, hi_mbox_isr_yield_limit, 99);
	अगर (ret)
		वापस ret;

	ret = ath10k_bmi_पढ़ो32(ar, hi_acs_flags, &param);
	अगर (ret)
		वापस ret;

	param |= HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_SET;

	अगर (mode == ATH10K_FIRMWARE_MODE_NORMAL)
		param |= HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE;
	अन्यथा
		param &= ~HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE;

	अगर (mode == ATH10K_FIRMWARE_MODE_UTF)
		param &= ~HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET;
	अन्यथा
		param |= HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET;

	ret = ath10k_bmi_ग_लिखो32(ar, hi_acs_flags, param);
	अगर (ret)
		वापस ret;

	ret = ath10k_bmi_पढ़ो32(ar, hi_option_flag2, &param);
	अगर (ret)
		वापस ret;

	param |= HI_OPTION_SDIO_CRASH_DUMP_ENHANCEMENT_HOST;

	ret = ath10k_bmi_ग_लिखो32(ar, hi_option_flag2, param);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_init_configure_target(काष्ठा ath10k *ar)
अणु
	u32 param_host;
	पूर्णांक ret;

	/* tell target which HTC version it is used*/
	ret = ath10k_bmi_ग_लिखो32(ar, hi_app_host_पूर्णांकerest,
				 HTC_PROTOCOL_VERSION);
	अगर (ret) अणु
		ath10k_err(ar, "settings HTC version failed\n");
		वापस ret;
	पूर्ण

	/* set the firmware mode to STA/IBSS/AP */
	ret = ath10k_bmi_पढ़ो32(ar, hi_option_flag, &param_host);
	अगर (ret) अणु
		ath10k_err(ar, "setting firmware mode (1/2) failed\n");
		वापस ret;
	पूर्ण

	/* TODO following parameters need to be re-visited. */
	/* num_device */
	param_host |= (1 << HI_OPTION_NUM_DEV_SHIFT);
	/* Firmware mode */
	/* FIXME: Why FW_MODE_AP ??.*/
	param_host |= (HI_OPTION_FW_MODE_AP << HI_OPTION_FW_MODE_SHIFT);
	/* mac_addr_method */
	param_host |= (1 << HI_OPTION_MAC_ADDR_METHOD_SHIFT);
	/* firmware_bridge */
	param_host |= (0 << HI_OPTION_FW_BRIDGE_SHIFT);
	/* fwsubmode */
	param_host |= (0 << HI_OPTION_FW_SUBMODE_SHIFT);

	ret = ath10k_bmi_ग_लिखो32(ar, hi_option_flag, param_host);
	अगर (ret) अणु
		ath10k_err(ar, "setting firmware mode (2/2) failed\n");
		वापस ret;
	पूर्ण

	/* We करो all byte-swapping on the host */
	ret = ath10k_bmi_ग_लिखो32(ar, hi_be, 0);
	अगर (ret) अणु
		ath10k_err(ar, "setting host CPU BE mode failed\n");
		वापस ret;
	पूर्ण

	/* FW descriptor/Data swap flags */
	ret = ath10k_bmi_ग_लिखो32(ar, hi_fw_swap, 0);

	अगर (ret) अणु
		ath10k_err(ar, "setting FW data/desc swap flags failed\n");
		वापस ret;
	पूर्ण

	/* Some devices have a special sanity check that verअगरies the PCI
	 * Device ID is written to this host पूर्णांकerest var. It is known to be
	 * required to boot QCA6164.
	 */
	ret = ath10k_bmi_ग_लिखो32(ar, hi_hci_uart_pwr_mgmt_params_ext,
				 ar->dev_id);
	अगर (ret) अणु
		ath10k_err(ar, "failed to set pwr_mgmt_params: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा firmware *ath10k_fetch_fw_file(काष्ठा ath10k *ar,
						   स्थिर अक्षर *dir,
						   स्थिर अक्षर *file)
अणु
	अक्षर filename[100];
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	अगर (file == शून्य)
		वापस ERR_PTR(-ENOENT);

	अगर (dir == शून्य)
		dir = ".";

	snम_लिखो(filename, माप(filename), "%s/%s", dir, file);
	ret = firmware_request_nowarn(&fw, filename, ar->dev);
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot fw request '%s': %d\n",
		   filename, ret);

	अगर (ret)
		वापस ERR_PTR(ret);

	वापस fw;
पूर्ण

अटल पूर्णांक ath10k_push_board_ext_data(काष्ठा ath10k *ar, स्थिर व्योम *data,
				      माप_प्रकार data_len)
अणु
	u32 board_data_size = ar->hw_params.fw.board_size;
	u32 board_ext_data_size = ar->hw_params.fw.board_ext_size;
	u32 board_ext_data_addr;
	पूर्णांक ret;

	ret = ath10k_bmi_पढ़ो32(ar, hi_board_ext_data, &board_ext_data_addr);
	अगर (ret) अणु
		ath10k_err(ar, "could not read board ext data addr (%d)\n",
			   ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot push board extended data addr 0x%x\n",
		   board_ext_data_addr);

	अगर (board_ext_data_addr == 0)
		वापस 0;

	अगर (data_len != (board_data_size + board_ext_data_size)) अणु
		ath10k_err(ar, "invalid board (ext) data sizes %zu != %d+%d\n",
			   data_len, board_data_size, board_ext_data_size);
		वापस -EINVAL;
	पूर्ण

	ret = ath10k_bmi_ग_लिखो_memory(ar, board_ext_data_addr,
				      data + board_data_size,
				      board_ext_data_size);
	अगर (ret) अणु
		ath10k_err(ar, "could not write board ext data (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_bmi_ग_लिखो32(ar, hi_board_ext_data_config,
				 (board_ext_data_size << 16) | 1);
	अगर (ret) अणु
		ath10k_err(ar, "could not write board ext data bit (%d)\n",
			   ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_get_board_id_from_otp(काष्ठा ath10k *ar)
अणु
	u32 result, address;
	u8 board_id, chip_id;
	bool ext_bid_support;
	पूर्णांक ret, bmi_board_id_param;

	address = ar->hw_params.patch_load_addr;

	अगर (!ar->normal_mode_fw.fw_file.otp_data ||
	    !ar->normal_mode_fw.fw_file.otp_len) अणु
		ath10k_warn(ar,
			    "failed to retrieve board id because of invalid otp\n");
		वापस -ENODATA;
	पूर्ण

	अगर (ar->id.bmi_ids_valid) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "boot already acquired valid otp board id,skip download, board_id %d chip_id %d\n",
			   ar->id.bmi_board_id, ar->id.bmi_chip_id);
		जाओ skip_otp_करोwnload;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot upload otp to 0x%x len %zd for board id\n",
		   address, ar->normal_mode_fw.fw_file.otp_len);

	ret = ath10k_bmi_fast_करोwnload(ar, address,
				       ar->normal_mode_fw.fw_file.otp_data,
				       ar->normal_mode_fw.fw_file.otp_len);
	अगर (ret) अणु
		ath10k_err(ar, "could not write otp for board id check: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	अगर (ar->cal_mode == ATH10K_PRE_CAL_MODE_DT ||
	    ar->cal_mode == ATH10K_PRE_CAL_MODE_खाता)
		bmi_board_id_param = BMI_PARAM_GET_FLASH_BOARD_ID;
	अन्यथा
		bmi_board_id_param = BMI_PARAM_GET_EEPROM_BOARD_ID;

	ret = ath10k_bmi_execute(ar, address, bmi_board_id_param, &result);
	अगर (ret) अणु
		ath10k_err(ar, "could not execute otp for board id check: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	board_id = MS(result, ATH10K_BMI_BOARD_ID_FROM_OTP);
	chip_id = MS(result, ATH10K_BMI_CHIP_ID_FROM_OTP);
	ext_bid_support = (result & ATH10K_BMI_EXT_BOARD_ID_SUPPORT);

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot get otp board id result 0x%08x board_id %d chip_id %d ext_bid_support %d\n",
		   result, board_id, chip_id, ext_bid_support);

	ar->id.ext_bid_supported = ext_bid_support;

	अगर ((result & ATH10K_BMI_BOARD_ID_STATUS_MASK) != 0 ||
	    (board_id == 0)) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "board id does not exist in otp, ignore it\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ar->id.bmi_ids_valid = true;
	ar->id.bmi_board_id = board_id;
	ar->id.bmi_chip_id = chip_id;

skip_otp_करोwnload:

	वापस 0;
पूर्ण

अटल व्योम ath10k_core_check_bdfext(स्थिर काष्ठा dmi_header *hdr, व्योम *data)
अणु
	काष्ठा ath10k *ar = data;
	स्थिर अक्षर *bdf_ext;
	स्थिर अक्षर *magic = ATH10K_SMBIOS_BDF_EXT_MAGIC;
	u8 bdf_enabled;
	पूर्णांक i;

	अगर (hdr->type != ATH10K_SMBIOS_BDF_EXT_TYPE)
		वापस;

	अगर (hdr->length != ATH10K_SMBIOS_BDF_EXT_LENGTH) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "wrong smbios bdf ext type length (%d).\n",
			   hdr->length);
		वापस;
	पूर्ण

	bdf_enabled = *((u8 *)hdr + ATH10K_SMBIOS_BDF_EXT_OFFSET);
	अगर (!bdf_enabled) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT, "bdf variant name not found.\n");
		वापस;
	पूर्ण

	/* Only one string exists (per spec) */
	bdf_ext = (अक्षर *)hdr + hdr->length;

	अगर (स_भेद(bdf_ext, magic, म_माप(magic)) != 0) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "bdf variant magic does not match.\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < म_माप(bdf_ext); i++) अणु
		अगर (!isascii(bdf_ext[i]) || !है_छाप(bdf_ext[i])) अणु
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "bdf variant name contains non ascii chars.\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Copy extension name without magic suffix */
	अगर (strscpy(ar->id.bdf_ext, bdf_ext + म_माप(magic),
		    माप(ar->id.bdf_ext)) < 0) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "bdf variant string is longer than the buffer can accommodate (variant: %s)\n",
			    bdf_ext);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "found and validated bdf variant smbios_type 0x%x bdf %s\n",
		   ATH10K_SMBIOS_BDF_EXT_TYPE, bdf_ext);
पूर्ण

अटल पूर्णांक ath10k_core_check_smbios(काष्ठा ath10k *ar)
अणु
	ar->id.bdf_ext[0] = '\0';
	dmi_walk(ath10k_core_check_bdfext, ar);

	अगर (ar->id.bdf_ext[0] == '\0')
		वापस -ENODATA;

	वापस 0;
पूर्ण

पूर्णांक ath10k_core_check_dt(काष्ठा ath10k *ar)
अणु
	काष्ठा device_node *node;
	स्थिर अक्षर *variant = शून्य;

	node = ar->dev->of_node;
	अगर (!node)
		वापस -ENOENT;

	of_property_पढ़ो_string(node, "qcom,ath10k-calibration-variant",
				&variant);
	अगर (!variant)
		वापस -ENODATA;

	अगर (strscpy(ar->id.bdf_ext, variant, माप(ar->id.bdf_ext)) < 0)
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "bdf variant string is longer than the buffer can accommodate (variant: %s)\n",
			    variant);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath10k_core_check_dt);

अटल पूर्णांक ath10k_करोwnload_fw(काष्ठा ath10k *ar)
अणु
	u32 address, data_len;
	स्थिर व्योम *data;
	पूर्णांक ret;
	काष्ठा pm_qos_request latency_qos;

	address = ar->hw_params.patch_load_addr;

	data = ar->running_fw->fw_file.firmware_data;
	data_len = ar->running_fw->fw_file.firmware_len;

	ret = ath10k_swap_code_seg_configure(ar, &ar->running_fw->fw_file);
	अगर (ret) अणु
		ath10k_err(ar, "failed to configure fw code swap: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot uploading firmware image %pK len %d\n",
		   data, data_len);

	/* Check अगर device supports to करोwnload firmware via
	 * diag copy engine. Downloading firmware via diag CE
	 * greatly reduces the समय to करोwnload firmware.
	 */
	अगर (ar->hw_params.fw_diag_ce_करोwnload) अणु
		ret = ath10k_hw_diag_fast_करोwnload(ar, address,
						   data, data_len);
		अगर (ret == 0)
			/* firmware upload via diag ce was successful */
			वापस 0;

		ath10k_warn(ar,
			    "failed to upload firmware via diag ce, trying BMI: %d",
			    ret);
	पूर्ण

	स_रखो(&latency_qos, 0, माप(latency_qos));
	cpu_latency_qos_add_request(&latency_qos, 0);

	ret = ath10k_bmi_fast_करोwnload(ar, address, data, data_len);

	cpu_latency_qos_हटाओ_request(&latency_qos);

	वापस ret;
पूर्ण

व्योम ath10k_core_मुक्त_board_files(काष्ठा ath10k *ar)
अणु
	अगर (!IS_ERR(ar->normal_mode_fw.board))
		release_firmware(ar->normal_mode_fw.board);

	अगर (!IS_ERR(ar->normal_mode_fw.ext_board))
		release_firmware(ar->normal_mode_fw.ext_board);

	ar->normal_mode_fw.board = शून्य;
	ar->normal_mode_fw.board_data = शून्य;
	ar->normal_mode_fw.board_len = 0;
	ar->normal_mode_fw.ext_board = शून्य;
	ar->normal_mode_fw.ext_board_data = शून्य;
	ar->normal_mode_fw.ext_board_len = 0;
पूर्ण
EXPORT_SYMBOL(ath10k_core_मुक्त_board_files);

अटल व्योम ath10k_core_मुक्त_firmware_files(काष्ठा ath10k *ar)
अणु
	अगर (!IS_ERR(ar->normal_mode_fw.fw_file.firmware))
		release_firmware(ar->normal_mode_fw.fw_file.firmware);

	अगर (!IS_ERR(ar->cal_file))
		release_firmware(ar->cal_file);

	अगर (!IS_ERR(ar->pre_cal_file))
		release_firmware(ar->pre_cal_file);

	ath10k_swap_code_seg_release(ar, &ar->normal_mode_fw.fw_file);

	ar->normal_mode_fw.fw_file.otp_data = शून्य;
	ar->normal_mode_fw.fw_file.otp_len = 0;

	ar->normal_mode_fw.fw_file.firmware = शून्य;
	ar->normal_mode_fw.fw_file.firmware_data = शून्य;
	ar->normal_mode_fw.fw_file.firmware_len = 0;

	ar->cal_file = शून्य;
	ar->pre_cal_file = शून्य;
पूर्ण

अटल पूर्णांक ath10k_fetch_cal_file(काष्ठा ath10k *ar)
अणु
	अक्षर filename[100];

	/* pre-cal-<bus>-<id>.bin */
	scnम_लिखो(filename, माप(filename), "pre-cal-%s-%s.bin",
		  ath10k_bus_str(ar->hअगर.bus), dev_name(ar->dev));

	ar->pre_cal_file = ath10k_fetch_fw_file(ar, ATH10K_FW_सूची, filename);
	अगर (!IS_ERR(ar->pre_cal_file))
		जाओ success;

	/* cal-<bus>-<id>.bin */
	scnम_लिखो(filename, माप(filename), "cal-%s-%s.bin",
		  ath10k_bus_str(ar->hअगर.bus), dev_name(ar->dev));

	ar->cal_file = ath10k_fetch_fw_file(ar, ATH10K_FW_सूची, filename);
	अगर (IS_ERR(ar->cal_file))
		/* calibration file is optional, करोn't prपूर्णांक any warnings */
		वापस PTR_ERR(ar->cal_file);
success:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "found calibration file %s/%s\n",
		   ATH10K_FW_सूची, filename);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_fetch_board_data_api_1(काष्ठा ath10k *ar, पूर्णांक bd_ie_type)
अणु
	स्थिर काष्ठा firmware *fw;

	अगर (bd_ie_type == ATH10K_BD_IE_BOARD) अणु
		अगर (!ar->hw_params.fw.board) अणु
			ath10k_err(ar, "failed to find board file fw entry\n");
			वापस -EINVAL;
		पूर्ण

		ar->normal_mode_fw.board = ath10k_fetch_fw_file(ar,
								ar->hw_params.fw.dir,
								ar->hw_params.fw.board);
		अगर (IS_ERR(ar->normal_mode_fw.board))
			वापस PTR_ERR(ar->normal_mode_fw.board);

		ar->normal_mode_fw.board_data = ar->normal_mode_fw.board->data;
		ar->normal_mode_fw.board_len = ar->normal_mode_fw.board->size;
	पूर्ण अन्यथा अगर (bd_ie_type == ATH10K_BD_IE_BOARD_EXT) अणु
		अगर (!ar->hw_params.fw.eboard) अणु
			ath10k_err(ar, "failed to find eboard file fw entry\n");
			वापस -EINVAL;
		पूर्ण

		fw = ath10k_fetch_fw_file(ar, ar->hw_params.fw.dir,
					  ar->hw_params.fw.eboard);
		ar->normal_mode_fw.ext_board = fw;
		अगर (IS_ERR(ar->normal_mode_fw.ext_board))
			वापस PTR_ERR(ar->normal_mode_fw.ext_board);

		ar->normal_mode_fw.ext_board_data = ar->normal_mode_fw.ext_board->data;
		ar->normal_mode_fw.ext_board_len = ar->normal_mode_fw.ext_board->size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_parse_bd_ie_board(काष्ठा ath10k *ar,
					 स्थिर व्योम *buf, माप_प्रकार buf_len,
					 स्थिर अक्षर *boardname,
					 पूर्णांक bd_ie_type)
अणु
	स्थिर काष्ठा ath10k_fw_ie *hdr;
	bool name_match_found;
	पूर्णांक ret, board_ie_id;
	माप_प्रकार board_ie_len;
	स्थिर व्योम *board_ie_data;

	name_match_found = false;

	/* go through ATH10K_BD_IE_BOARD_ elements */
	जबतक (buf_len > माप(काष्ठा ath10k_fw_ie)) अणु
		hdr = buf;
		board_ie_id = le32_to_cpu(hdr->id);
		board_ie_len = le32_to_cpu(hdr->len);
		board_ie_data = hdr->data;

		buf_len -= माप(*hdr);
		buf += माप(*hdr);

		अगर (buf_len < ALIGN(board_ie_len, 4)) अणु
			ath10k_err(ar, "invalid ATH10K_BD_IE_BOARD length: %zu < %zu\n",
				   buf_len, ALIGN(board_ie_len, 4));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (board_ie_id) अणु
		हाल ATH10K_BD_IE_BOARD_NAME:
			ath10k_dbg_dump(ar, ATH10K_DBG_BOOT, "board name", "",
					board_ie_data, board_ie_len);

			अगर (board_ie_len != म_माप(boardname))
				अवरोध;

			ret = स_भेद(board_ie_data, boardname, म_माप(boardname));
			अगर (ret)
				अवरोध;

			name_match_found = true;
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "boot found match for name '%s'",
				   boardname);
			अवरोध;
		हाल ATH10K_BD_IE_BOARD_DATA:
			अगर (!name_match_found)
				/* no match found */
				अवरोध;

			अगर (bd_ie_type == ATH10K_BD_IE_BOARD) अणु
				ath10k_dbg(ar, ATH10K_DBG_BOOT,
					   "boot found board data for '%s'",
						boardname);

				ar->normal_mode_fw.board_data = board_ie_data;
				ar->normal_mode_fw.board_len = board_ie_len;
			पूर्ण अन्यथा अगर (bd_ie_type == ATH10K_BD_IE_BOARD_EXT) अणु
				ath10k_dbg(ar, ATH10K_DBG_BOOT,
					   "boot found eboard data for '%s'",
						boardname);

				ar->normal_mode_fw.ext_board_data = board_ie_data;
				ar->normal_mode_fw.ext_board_len = board_ie_len;
			पूर्ण

			ret = 0;
			जाओ out;
		शेष:
			ath10k_warn(ar, "unknown ATH10K_BD_IE_BOARD found: %d\n",
				    board_ie_id);
			अवरोध;
		पूर्ण

		/* jump over the padding */
		board_ie_len = ALIGN(board_ie_len, 4);

		buf_len -= board_ie_len;
		buf += board_ie_len;
	पूर्ण

	/* no match found */
	ret = -ENOENT;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_core_search_bd(काष्ठा ath10k *ar,
				 स्थिर अक्षर *boardname,
				 स्थिर u8 *data,
				 माप_प्रकार len)
अणु
	माप_प्रकार ie_len;
	काष्ठा ath10k_fw_ie *hdr;
	पूर्णांक ret = -ENOENT, ie_id;

	जबतक (len > माप(काष्ठा ath10k_fw_ie)) अणु
		hdr = (काष्ठा ath10k_fw_ie *)data;
		ie_id = le32_to_cpu(hdr->id);
		ie_len = le32_to_cpu(hdr->len);

		len -= माप(*hdr);
		data = hdr->data;

		अगर (len < ALIGN(ie_len, 4)) अणु
			ath10k_err(ar, "invalid length for board ie_id %d ie_len %zu len %zu\n",
				   ie_id, ie_len, len);
			वापस -EINVAL;
		पूर्ण

		चयन (ie_id) अणु
		हाल ATH10K_BD_IE_BOARD:
			ret = ath10k_core_parse_bd_ie_board(ar, data, ie_len,
							    boardname,
							    ATH10K_BD_IE_BOARD);
			अगर (ret == -ENOENT)
				/* no match found, जारी */
				अवरोध;

			/* either found or error, so stop searching */
			जाओ out;
		हाल ATH10K_BD_IE_BOARD_EXT:
			ret = ath10k_core_parse_bd_ie_board(ar, data, ie_len,
							    boardname,
							    ATH10K_BD_IE_BOARD_EXT);
			अगर (ret == -ENOENT)
				/* no match found, जारी */
				अवरोध;

			/* either found or error, so stop searching */
			जाओ out;
		पूर्ण

		/* jump over the padding */
		ie_len = ALIGN(ie_len, 4);

		len -= ie_len;
		data += ie_len;
	पूर्ण

out:
	/* वापस result of parse_bd_ie_board() or -ENOENT */
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_core_fetch_board_data_api_n(काष्ठा ath10k *ar,
					      स्थिर अक्षर *boardname,
					      स्थिर अक्षर *fallback_boardname1,
					      स्थिर अक्षर *fallback_boardname2,
					      स्थिर अक्षर *filename)
अणु
	माप_प्रकार len, magic_len;
	स्थिर u8 *data;
	पूर्णांक ret;

	/* Skip अगर alपढ़ोy fetched during board data करोwnload */
	अगर (!ar->normal_mode_fw.board)
		ar->normal_mode_fw.board = ath10k_fetch_fw_file(ar,
								ar->hw_params.fw.dir,
								filename);
	अगर (IS_ERR(ar->normal_mode_fw.board))
		वापस PTR_ERR(ar->normal_mode_fw.board);

	data = ar->normal_mode_fw.board->data;
	len = ar->normal_mode_fw.board->size;

	/* magic has extra null byte padded */
	magic_len = म_माप(ATH10K_BOARD_MAGIC) + 1;
	अगर (len < magic_len) अणु
		ath10k_err(ar, "failed to find magic value in %s/%s, file too short: %zu\n",
			   ar->hw_params.fw.dir, filename, len);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (स_भेद(data, ATH10K_BOARD_MAGIC, magic_len)) अणु
		ath10k_err(ar, "found invalid board magic\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* magic is padded to 4 bytes */
	magic_len = ALIGN(magic_len, 4);
	अगर (len < magic_len) अणु
		ath10k_err(ar, "failed: %s/%s too small to contain board data, len: %zu\n",
			   ar->hw_params.fw.dir, filename, len);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	data += magic_len;
	len -= magic_len;

	/* attempt to find boardname in the IE list */
	ret = ath10k_core_search_bd(ar, boardname, data, len);

	/* अगर we didn't find it and have a fallback name, try that */
	अगर (ret == -ENOENT && fallback_boardname1)
		ret = ath10k_core_search_bd(ar, fallback_boardname1, data, len);

	अगर (ret == -ENOENT && fallback_boardname2)
		ret = ath10k_core_search_bd(ar, fallback_boardname2, data, len);

	अगर (ret == -ENOENT) अणु
		ath10k_err(ar,
			   "failed to fetch board data for %s from %s/%s\n",
			   boardname, ar->hw_params.fw.dir, filename);
		ret = -ENODATA;
	पूर्ण

	अगर (ret)
		जाओ err;

	वापस 0;

err:
	ath10k_core_मुक्त_board_files(ar);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_core_create_board_name(काष्ठा ath10k *ar, अक्षर *name,
					 माप_प्रकार name_len, bool with_variant,
					 bool with_chip_id)
अणु
	/* म_माप(',variant=') + म_माप(ar->id.bdf_ext) */
	अक्षर variant[9 + ATH10K_SMBIOS_BDF_EXT_STR_LENGTH] = अणु 0 पूर्ण;

	अगर (with_variant && ar->id.bdf_ext[0] != '\0')
		scnम_लिखो(variant, माप(variant), ",variant=%s",
			  ar->id.bdf_ext);

	अगर (ar->id.bmi_ids_valid) अणु
		scnम_लिखो(name, name_len,
			  "bus=%s,bmi-chip-id=%d,bmi-board-id=%d%s",
			  ath10k_bus_str(ar->hअगर.bus),
			  ar->id.bmi_chip_id,
			  ar->id.bmi_board_id, variant);
		जाओ out;
	पूर्ण

	अगर (ar->id.qmi_ids_valid) अणु
		अगर (with_chip_id)
			scnम_लिखो(name, name_len,
				  "bus=%s,qmi-board-id=%x,qmi-chip-id=%x%s",
				  ath10k_bus_str(ar->hअगर.bus),
				  ar->id.qmi_board_id, ar->id.qmi_chip_id,
				  variant);
		अन्यथा
			scnम_लिखो(name, name_len,
				  "bus=%s,qmi-board-id=%x",
				  ath10k_bus_str(ar->hअगर.bus),
				  ar->id.qmi_board_id);
		जाओ out;
	पूर्ण

	scnम_लिखो(name, name_len,
		  "bus=%s,vendor=%04x,device=%04x,subsystem-vendor=%04x,subsystem-device=%04x%s",
		  ath10k_bus_str(ar->hअगर.bus),
		  ar->id.venकरोr, ar->id.device,
		  ar->id.subप्रणाली_venकरोr, ar->id.subप्रणाली_device, variant);
out:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot using board name '%s'\n", name);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_create_eboard_name(काष्ठा ath10k *ar, अक्षर *name,
					  माप_प्रकार name_len)
अणु
	अगर (ar->id.bmi_ids_valid) अणु
		scnम_लिखो(name, name_len,
			  "bus=%s,bmi-chip-id=%d,bmi-eboard-id=%d",
			  ath10k_bus_str(ar->hअगर.bus),
			  ar->id.bmi_chip_id,
			  ar->id.bmi_eboard_id);

		ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot using eboard name '%s'\n", name);
		वापस 0;
	पूर्ण
	/* Fallback अगर वापसed board id is zero */
	वापस -1;
पूर्ण

पूर्णांक ath10k_core_fetch_board_file(काष्ठा ath10k *ar, पूर्णांक bd_ie_type)
अणु
	अक्षर boardname[100], fallback_boardname1[100], fallback_boardname2[100];
	पूर्णांक ret;

	अगर (bd_ie_type == ATH10K_BD_IE_BOARD) अणु
		/* With variant and chip id */
		ret = ath10k_core_create_board_name(ar, boardname,
						    माप(boardname), true,
						    true);
		अगर (ret) अणु
			ath10k_err(ar, "failed to create board name: %d", ret);
			वापस ret;
		पूर्ण

		/* Without variant and only chip-id */
		ret = ath10k_core_create_board_name(ar, fallback_boardname1,
						    माप(boardname), false,
						    true);
		अगर (ret) अणु
			ath10k_err(ar, "failed to create 1st fallback board name: %d",
				   ret);
			वापस ret;
		पूर्ण

		/* Without variant and without chip-id */
		ret = ath10k_core_create_board_name(ar, fallback_boardname2,
						    माप(boardname), false,
						    false);
		अगर (ret) अणु
			ath10k_err(ar, "failed to create 2nd fallback board name: %d",
				   ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (bd_ie_type == ATH10K_BD_IE_BOARD_EXT) अणु
		ret = ath10k_core_create_eboard_name(ar, boardname,
						     माप(boardname));
		अगर (ret) अणु
			ath10k_err(ar, "fallback to eboard.bin since board id 0");
			जाओ fallback;
		पूर्ण
	पूर्ण

	ar->bd_api = 2;
	ret = ath10k_core_fetch_board_data_api_n(ar, boardname,
						 fallback_boardname1,
						 fallback_boardname2,
						 ATH10K_BOARD_API2_खाता);
	अगर (!ret)
		जाओ success;

fallback:
	ar->bd_api = 1;
	ret = ath10k_core_fetch_board_data_api_1(ar, bd_ie_type);
	अगर (ret) अणु
		ath10k_err(ar, "failed to fetch board-2.bin or board.bin from %s\n",
			   ar->hw_params.fw.dir);
		वापस ret;
	पूर्ण

success:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "using board api %d\n", ar->bd_api);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath10k_core_fetch_board_file);

अटल पूर्णांक ath10k_core_get_ext_board_id_from_otp(काष्ठा ath10k *ar)
अणु
	u32 result, address;
	u8 ext_board_id;
	पूर्णांक ret;

	address = ar->hw_params.patch_load_addr;

	अगर (!ar->normal_mode_fw.fw_file.otp_data ||
	    !ar->normal_mode_fw.fw_file.otp_len) अणु
		ath10k_warn(ar,
			    "failed to retrieve extended board id due to otp binary missing\n");
		वापस -ENODATA;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot upload otp to 0x%x len %zd for ext board id\n",
		   address, ar->normal_mode_fw.fw_file.otp_len);

	ret = ath10k_bmi_fast_करोwnload(ar, address,
				       ar->normal_mode_fw.fw_file.otp_data,
				       ar->normal_mode_fw.fw_file.otp_len);
	अगर (ret) अणु
		ath10k_err(ar, "could not write otp for ext board id check: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	ret = ath10k_bmi_execute(ar, address, BMI_PARAM_GET_EXT_BOARD_ID, &result);
	अगर (ret) अणु
		ath10k_err(ar, "could not execute otp for ext board id check: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	अगर (!result) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "ext board id does not exist in otp, ignore it\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ext_board_id = result & ATH10K_BMI_EBOARD_ID_STATUS_MASK;

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot get otp ext board id result 0x%08x ext_board_id %d\n",
		   result, ext_board_id);

	ar->id.bmi_eboard_id = ext_board_id;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_करोwnload_board_data(काष्ठा ath10k *ar, स्थिर व्योम *data,
				      माप_प्रकार data_len)
अणु
	u32 board_data_size = ar->hw_params.fw.board_size;
	u32 eboard_data_size = ar->hw_params.fw.ext_board_size;
	u32 board_address;
	u32 ext_board_address;
	पूर्णांक ret;

	ret = ath10k_push_board_ext_data(ar, data, data_len);
	अगर (ret) अणु
		ath10k_err(ar, "could not push board ext data (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath10k_bmi_पढ़ो32(ar, hi_board_data, &board_address);
	अगर (ret) अणु
		ath10k_err(ar, "could not read board data addr (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath10k_bmi_ग_लिखो_memory(ar, board_address, data,
				      min_t(u32, board_data_size,
					    data_len));
	अगर (ret) अणु
		ath10k_err(ar, "could not write board data (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath10k_bmi_ग_लिखो32(ar, hi_board_data_initialized, 1);
	अगर (ret) अणु
		ath10k_err(ar, "could not write board data bit (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (!ar->id.ext_bid_supported)
		जाओ निकास;

	/* Extended board data करोwnload */
	ret = ath10k_core_get_ext_board_id_from_otp(ar);
	अगर (ret == -EOPNOTSUPP) अणु
		/* Not fetching ext_board_data अगर ext board id is 0 */
		ath10k_dbg(ar, ATH10K_DBG_BOOT, "otp returned ext board id 0\n");
		वापस 0;
	पूर्ण अन्यथा अगर (ret) अणु
		ath10k_err(ar, "failed to get extended board id: %d\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath10k_core_fetch_board_file(ar, ATH10K_BD_IE_BOARD_EXT);
	अगर (ret)
		जाओ निकास;

	अगर (ar->normal_mode_fw.ext_board_data) अणु
		ext_board_address = board_address + EXT_BOARD_ADDRESS_OFFSET;
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "boot writing ext board data to addr 0x%x",
			   ext_board_address);
		ret = ath10k_bmi_ग_लिखो_memory(ar, ext_board_address,
					      ar->normal_mode_fw.ext_board_data,
					      min_t(u32, eboard_data_size, data_len));
		अगर (ret)
			ath10k_err(ar, "failed to write ext board data: %d\n", ret);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_करोwnload_and_run_otp(काष्ठा ath10k *ar)
अणु
	u32 result, address = ar->hw_params.patch_load_addr;
	u32 bmi_otp_exe_param = ar->hw_params.otp_exe_param;
	पूर्णांक ret;

	ret = ath10k_करोwnload_board_data(ar,
					 ar->running_fw->board_data,
					 ar->running_fw->board_len);
	अगर (ret) अणु
		ath10k_err(ar, "failed to download board data: %d\n", ret);
		वापस ret;
	पूर्ण

	/* OTP is optional */

	अगर (!ar->running_fw->fw_file.otp_data ||
	    !ar->running_fw->fw_file.otp_len) अणु
		ath10k_warn(ar, "Not running otp, calibration will be incorrect (otp-data %pK otp_len %zd)!\n",
			    ar->running_fw->fw_file.otp_data,
			    ar->running_fw->fw_file.otp_len);
		वापस 0;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot upload otp to 0x%x len %zd\n",
		   address, ar->running_fw->fw_file.otp_len);

	ret = ath10k_bmi_fast_करोwnload(ar, address,
				       ar->running_fw->fw_file.otp_data,
				       ar->running_fw->fw_file.otp_len);
	अगर (ret) अणु
		ath10k_err(ar, "could not write otp (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* As of now pre-cal is valid क्रम 10_4 variants */
	अगर (ar->cal_mode == ATH10K_PRE_CAL_MODE_DT ||
	    ar->cal_mode == ATH10K_PRE_CAL_MODE_खाता)
		bmi_otp_exe_param = BMI_PARAM_FLASH_SECTION_ALL;

	ret = ath10k_bmi_execute(ar, address, bmi_otp_exe_param, &result);
	अगर (ret) अणु
		ath10k_err(ar, "could not execute otp (%d)\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot otp execute result %d\n", result);

	अगर (!(skip_otp || test_bit(ATH10K_FW_FEATURE_IGNORE_OTP_RESULT,
				   ar->running_fw->fw_file.fw_features)) &&
	    result != 0) अणु
		ath10k_err(ar, "otp calibration failed: %d", result);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_करोwnload_cal_file(काष्ठा ath10k *ar,
				    स्थिर काष्ठा firmware *file)
अणु
	पूर्णांक ret;

	अगर (!file)
		वापस -ENOENT;

	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ret = ath10k_करोwnload_board_data(ar, file->data, file->size);
	अगर (ret) अणु
		ath10k_err(ar, "failed to download cal_file data: %d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot cal file downloaded\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_करोwnload_cal_dt(काष्ठा ath10k *ar, स्थिर अक्षर *dt_name)
अणु
	काष्ठा device_node *node;
	पूर्णांक data_len;
	व्योम *data;
	पूर्णांक ret;

	node = ar->dev->of_node;
	अगर (!node)
		/* Device Tree is optional, करोn't prपूर्णांक any warnings अगर
		 * there's no node क्रम ath10k.
		 */
		वापस -ENOENT;

	अगर (!of_get_property(node, dt_name, &data_len)) अणु
		/* The calibration data node is optional */
		वापस -ENOENT;
	पूर्ण

	अगर (data_len != ar->hw_params.cal_data_len) अणु
		ath10k_warn(ar, "invalid calibration data length in DT: %d\n",
			    data_len);
		ret = -EMSGSIZE;
		जाओ out;
	पूर्ण

	data = kदो_स्मृति(data_len, GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = of_property_पढ़ो_u8_array(node, dt_name, data, data_len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read calibration data from DT: %d\n",
			    ret);
		जाओ out_मुक्त;
	पूर्ण

	ret = ath10k_करोwnload_board_data(ar, data, data_len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to download calibration data from Device Tree: %d\n",
			    ret);
		जाओ out_मुक्त;
	पूर्ण

	ret = 0;

out_मुक्त:
	kमुक्त(data);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_करोwnload_cal_eeprom(काष्ठा ath10k *ar)
अणु
	माप_प्रकार data_len;
	व्योम *data = शून्य;
	पूर्णांक ret;

	ret = ath10k_hअगर_fetch_cal_eeprom(ar, &data, &data_len);
	अगर (ret) अणु
		अगर (ret != -EOPNOTSUPP)
			ath10k_warn(ar, "failed to read calibration data from EEPROM: %d\n",
				    ret);
		जाओ out_मुक्त;
	पूर्ण

	ret = ath10k_करोwnload_board_data(ar, data, data_len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to download calibration data from EEPROM: %d\n",
			    ret);
		जाओ out_मुक्त;
	पूर्ण

	ret = 0;

out_मुक्त:
	kमुक्त(data);

	वापस ret;
पूर्ण

पूर्णांक ath10k_core_fetch_firmware_api_n(काष्ठा ath10k *ar, स्थिर अक्षर *name,
				     काष्ठा ath10k_fw_file *fw_file)
अणु
	माप_प्रकार magic_len, len, ie_len;
	पूर्णांक ie_id, i, index, bit, ret;
	काष्ठा ath10k_fw_ie *hdr;
	स्थिर u8 *data;
	__le32 *बारtamp, *version;

	/* first fetch the firmware file (firmware-*.bin) */
	fw_file->firmware = ath10k_fetch_fw_file(ar, ar->hw_params.fw.dir,
						 name);
	अगर (IS_ERR(fw_file->firmware))
		वापस PTR_ERR(fw_file->firmware);

	data = fw_file->firmware->data;
	len = fw_file->firmware->size;

	/* magic also includes the null byte, check that as well */
	magic_len = म_माप(ATH10K_FIRMWARE_MAGIC) + 1;

	अगर (len < magic_len) अणु
		ath10k_err(ar, "firmware file '%s/%s' too small to contain magic: %zu\n",
			   ar->hw_params.fw.dir, name, len);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (स_भेद(data, ATH10K_FIRMWARE_MAGIC, magic_len) != 0) अणु
		ath10k_err(ar, "invalid firmware magic\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* jump over the padding */
	magic_len = ALIGN(magic_len, 4);

	len -= magic_len;
	data += magic_len;

	/* loop elements */
	जबतक (len > माप(काष्ठा ath10k_fw_ie)) अणु
		hdr = (काष्ठा ath10k_fw_ie *)data;

		ie_id = le32_to_cpu(hdr->id);
		ie_len = le32_to_cpu(hdr->len);

		len -= माप(*hdr);
		data += माप(*hdr);

		अगर (len < ie_len) अणु
			ath10k_err(ar, "invalid length for FW IE %d (%zu < %zu)\n",
				   ie_id, len, ie_len);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		चयन (ie_id) अणु
		हाल ATH10K_FW_IE_FW_VERSION:
			अगर (ie_len > माप(fw_file->fw_version) - 1)
				अवरोध;

			स_नकल(fw_file->fw_version, data, ie_len);
			fw_file->fw_version[ie_len] = '\0';

			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "found fw version %s\n",
				    fw_file->fw_version);
			अवरोध;
		हाल ATH10K_FW_IE_TIMESTAMP:
			अगर (ie_len != माप(u32))
				अवरोध;

			बारtamp = (__le32 *)data;

			ath10k_dbg(ar, ATH10K_DBG_BOOT, "found fw timestamp %d\n",
				   le32_to_cpup(बारtamp));
			अवरोध;
		हाल ATH10K_FW_IE_FEATURES:
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "found firmware features ie (%zd B)\n",
				   ie_len);

			क्रम (i = 0; i < ATH10K_FW_FEATURE_COUNT; i++) अणु
				index = i / 8;
				bit = i % 8;

				अगर (index == ie_len)
					अवरोध;

				अगर (data[index] & (1 << bit)) अणु
					ath10k_dbg(ar, ATH10K_DBG_BOOT,
						   "Enabling feature bit: %i\n",
						   i);
					__set_bit(i, fw_file->fw_features);
				पूर्ण
			पूर्ण

			ath10k_dbg_dump(ar, ATH10K_DBG_BOOT, "features", "",
					fw_file->fw_features,
					माप(fw_file->fw_features));
			अवरोध;
		हाल ATH10K_FW_IE_FW_IMAGE:
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "found fw image ie (%zd B)\n",
				   ie_len);

			fw_file->firmware_data = data;
			fw_file->firmware_len = ie_len;

			अवरोध;
		हाल ATH10K_FW_IE_OTP_IMAGE:
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "found otp image ie (%zd B)\n",
				   ie_len);

			fw_file->otp_data = data;
			fw_file->otp_len = ie_len;

			अवरोध;
		हाल ATH10K_FW_IE_WMI_OP_VERSION:
			अगर (ie_len != माप(u32))
				अवरोध;

			version = (__le32 *)data;

			fw_file->wmi_op_version = le32_to_cpup(version);

			ath10k_dbg(ar, ATH10K_DBG_BOOT, "found fw ie wmi op version %d\n",
				   fw_file->wmi_op_version);
			अवरोध;
		हाल ATH10K_FW_IE_HTT_OP_VERSION:
			अगर (ie_len != माप(u32))
				अवरोध;

			version = (__le32 *)data;

			fw_file->htt_op_version = le32_to_cpup(version);

			ath10k_dbg(ar, ATH10K_DBG_BOOT, "found fw ie htt op version %d\n",
				   fw_file->htt_op_version);
			अवरोध;
		हाल ATH10K_FW_IE_FW_CODE_SWAP_IMAGE:
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "found fw code swap image ie (%zd B)\n",
				   ie_len);
			fw_file->codeswap_data = data;
			fw_file->codeswap_len = ie_len;
			अवरोध;
		शेष:
			ath10k_warn(ar, "Unknown FW IE: %u\n",
				    le32_to_cpu(hdr->id));
			अवरोध;
		पूर्ण

		/* jump over the padding */
		ie_len = ALIGN(ie_len, 4);

		len -= ie_len;
		data += ie_len;
	पूर्ण

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI, fw_file->fw_features) &&
	    (!fw_file->firmware_data || !fw_file->firmware_len)) अणु
		ath10k_warn(ar, "No ATH10K_FW_IE_FW_IMAGE found from '%s/%s', skipping\n",
			    ar->hw_params.fw.dir, name);
		ret = -ENOMEDIUM;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	ath10k_core_मुक्त_firmware_files(ar);
	वापस ret;
पूर्ण

अटल व्योम ath10k_core_get_fw_name(काष्ठा ath10k *ar, अक्षर *fw_name,
				    माप_प्रकार fw_name_len, पूर्णांक fw_api)
अणु
	चयन (ar->hअगर.bus) अणु
	हाल ATH10K_BUS_SDIO:
	हाल ATH10K_BUS_USB:
		scnम_लिखो(fw_name, fw_name_len, "%s-%s-%d.bin",
			  ATH10K_FW_खाता_BASE, ath10k_bus_str(ar->hअगर.bus),
			  fw_api);
		अवरोध;
	हाल ATH10K_BUS_PCI:
	हाल ATH10K_BUS_AHB:
	हाल ATH10K_BUS_SNOC:
		scnम_लिखो(fw_name, fw_name_len, "%s-%d.bin",
			  ATH10K_FW_खाता_BASE, fw_api);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_core_fetch_firmware_files(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret, i;
	अक्षर fw_name[100];

	/* calibration file is optional, करोn't check क्रम any errors */
	ath10k_fetch_cal_file(ar);

	क्रम (i = ATH10K_FW_API_MAX; i >= ATH10K_FW_API_MIN; i--) अणु
		ar->fw_api = i;
		ath10k_dbg(ar, ATH10K_DBG_BOOT, "trying fw api %d\n",
			   ar->fw_api);

		ath10k_core_get_fw_name(ar, fw_name, माप(fw_name), ar->fw_api);
		ret = ath10k_core_fetch_firmware_api_n(ar, fw_name,
						       &ar->normal_mode_fw.fw_file);
		अगर (!ret)
			जाओ success;
	पूर्ण

	/* we end up here अगर we couldn't fetch any firmware */

	ath10k_err(ar, "Failed to find firmware-N.bin (N between %d and %d) from %s: %d",
		   ATH10K_FW_API_MIN, ATH10K_FW_API_MAX, ar->hw_params.fw.dir,
		   ret);

	वापस ret;

success:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "using fw api %d\n", ar->fw_api);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_pre_cal_करोwnload(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ret = ath10k_करोwnload_cal_file(ar, ar->pre_cal_file);
	अगर (ret == 0) अणु
		ar->cal_mode = ATH10K_PRE_CAL_MODE_खाता;
		जाओ success;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot did not find a pre calibration file, try DT next: %d\n",
		   ret);

	ret = ath10k_करोwnload_cal_dt(ar, "qcom,ath10k-pre-calibration-data");
	अगर (ret) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "unable to load pre cal data from DT: %d\n", ret);
		वापस ret;
	पूर्ण
	ar->cal_mode = ATH10K_PRE_CAL_MODE_DT;

success:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot using calibration mode %s\n",
		   ath10k_cal_mode_str(ar->cal_mode));

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_pre_cal_config(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ret = ath10k_core_pre_cal_करोwnload(ar);
	अगर (ret) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "failed to load pre cal data: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_core_get_board_id_from_otp(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to get board id: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_करोwnload_and_run_otp(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to run otp: %d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "pre cal configuration done successfully\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_करोwnload_cal_data(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ret = ath10k_core_pre_cal_config(ar);
	अगर (ret == 0)
		वापस 0;

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "pre cal download procedure failed, try cal file: %d\n",
		   ret);

	ret = ath10k_करोwnload_cal_file(ar, ar->cal_file);
	अगर (ret == 0) अणु
		ar->cal_mode = ATH10K_CAL_MODE_खाता;
		जाओ करोne;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot did not find a calibration file, try DT next: %d\n",
		   ret);

	ret = ath10k_करोwnload_cal_dt(ar, "qcom,ath10k-calibration-data");
	अगर (ret == 0) अणु
		ar->cal_mode = ATH10K_CAL_MODE_DT;
		जाओ करोne;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot did not find DT entry, try target EEPROM next: %d\n",
		   ret);

	ret = ath10k_करोwnload_cal_eeprom(ar);
	अगर (ret == 0) अणु
		ar->cal_mode = ATH10K_CAL_MODE_EEPROM;
		जाओ करोne;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot did not find target EEPROM entry, try OTP next: %d\n",
		   ret);

	ret = ath10k_करोwnload_and_run_otp(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to run otp: %d\n", ret);
		वापस ret;
	पूर्ण

	ar->cal_mode = ATH10K_CAL_MODE_OTP;

करोne:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot using calibration mode %s\n",
		   ath10k_cal_mode_str(ar->cal_mode));
	वापस 0;
पूर्ण

अटल व्योम ath10k_core_fetch_btcoex_dt(काष्ठा ath10k *ar)
अणु
	काष्ठा device_node *node;
	u8 coex_support = 0;
	पूर्णांक ret;

	node = ar->dev->of_node;
	अगर (!node)
		जाओ out;

	ret = of_property_पढ़ो_u8(node, "qcom,coexist-support", &coex_support);
	अगर (ret) अणु
		ar->coex_support = true;
		जाओ out;
	पूर्ण

	अगर (coex_support) अणु
		ar->coex_support = true;
	पूर्ण अन्यथा अणु
		ar->coex_support = false;
		ar->coex_gpio_pin = -1;
		जाओ out;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,coexist-gpio-pin",
				   &ar->coex_gpio_pin);
	अगर (ret)
		ar->coex_gpio_pin = -1;

out:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot coex_support %d coex_gpio_pin %d\n",
		   ar->coex_support, ar->coex_gpio_pin);
पूर्ण

अटल पूर्णांक ath10k_init_uart(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	/*
	 * Explicitly setting UART prपूर्णांकs to zero as target turns it on
	 * based on scratch रेजिस्टरs.
	 */
	ret = ath10k_bmi_ग_लिखो32(ar, hi_serial_enable, 0);
	अगर (ret) अणु
		ath10k_warn(ar, "could not disable UART prints (%d)\n", ret);
		वापस ret;
	पूर्ण

	अगर (!uart_prपूर्णांक) अणु
		अगर (ar->hw_params.uart_pin_workaround) अणु
			ret = ath10k_bmi_ग_लिखो32(ar, hi_dbg_uart_txpin,
						 ar->hw_params.uart_pin);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to set UART TX pin: %d",
					    ret);
				वापस ret;
			पूर्ण
		पूर्ण

		वापस 0;
	पूर्ण

	ret = ath10k_bmi_ग_लिखो32(ar, hi_dbg_uart_txpin, ar->hw_params.uart_pin);
	अगर (ret) अणु
		ath10k_warn(ar, "could not enable UART prints (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_bmi_ग_लिखो32(ar, hi_serial_enable, 1);
	अगर (ret) अणु
		ath10k_warn(ar, "could not enable UART prints (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Set the UART baud rate to 19200. */
	ret = ath10k_bmi_ग_लिखो32(ar, hi_desired_baud_rate, 19200);
	अगर (ret) अणु
		ath10k_warn(ar, "could not set the baud rate (%d)\n", ret);
		वापस ret;
	पूर्ण

	ath10k_info(ar, "UART prints enabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_init_hw_params(काष्ठा ath10k *ar)
अणु
	स्थिर काष्ठा ath10k_hw_params *hw_params;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ath10k_hw_params_list); i++) अणु
		hw_params = &ath10k_hw_params_list[i];

		अगर (hw_params->bus == ar->hअगर.bus &&
		    hw_params->id == ar->target_version &&
		    hw_params->dev_id == ar->dev_id)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ath10k_hw_params_list)) अणु
		ath10k_err(ar, "Unsupported hardware version: 0x%x\n",
			   ar->target_version);
		वापस -EINVAL;
	पूर्ण

	ar->hw_params = *hw_params;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "Hardware name %s version 0x%x\n",
		   ar->hw_params.name, ar->target_version);

	वापस 0;
पूर्ण

व्योम ath10k_core_start_recovery(काष्ठा ath10k *ar)
अणु
	अगर (test_and_set_bit(ATH10K_FLAG_RESTARTING, &ar->dev_flags)) अणु
		ath10k_warn(ar, "already restarting\n");
		वापस;
	पूर्ण

	queue_work(ar->workqueue, &ar->restart_work);
पूर्ण
EXPORT_SYMBOL(ath10k_core_start_recovery);

व्योम ath10k_core_napi_enable(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (test_bit(ATH10K_FLAG_NAPI_ENABLED, &ar->dev_flags))
		वापस;

	napi_enable(&ar->napi);
	set_bit(ATH10K_FLAG_NAPI_ENABLED, &ar->dev_flags);
पूर्ण
EXPORT_SYMBOL(ath10k_core_napi_enable);

व्योम ath10k_core_napi_sync_disable(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!test_bit(ATH10K_FLAG_NAPI_ENABLED, &ar->dev_flags))
		वापस;

	napi_synchronize(&ar->napi);
	napi_disable(&ar->napi);
	clear_bit(ATH10K_FLAG_NAPI_ENABLED, &ar->dev_flags);
पूर्ण
EXPORT_SYMBOL(ath10k_core_napi_sync_disable);

अटल व्योम ath10k_core_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, restart_work);
	पूर्णांक ret;

	set_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags);

	/* Place a barrier to make sure the compiler करोesn't reorder
	 * CRASH_FLUSH and calling other functions.
	 */
	barrier();

	ieee80211_stop_queues(ar->hw);
	ath10k_drain_tx(ar);
	complete(&ar->scan.started);
	complete(&ar->scan.completed);
	complete(&ar->scan.on_channel);
	complete(&ar->offchan_tx_completed);
	complete(&ar->install_key_करोne);
	complete(&ar->vdev_setup_करोne);
	complete(&ar->vdev_delete_करोne);
	complete(&ar->thermal.wmi_sync);
	complete(&ar->bss_survey_करोne);
	wake_up(&ar->htt.empty_tx_wq);
	wake_up(&ar->wmi.tx_credits_wq);
	wake_up(&ar->peer_mapping_wq);

	/* TODO: We can have one instance of cancelling coverage_class_work by
	 * moving it to ath10k_halt(), so that both stop() and restart() would
	 * call that but it takes conf_mutex() and अगर we call cancel_work_sync()
	 * with conf_mutex it will deadlock.
	 */
	cancel_work_sync(&ar->set_coverage_class_work);

	mutex_lock(&ar->conf_mutex);

	चयन (ar->state) अणु
	हाल ATH10K_STATE_ON:
		ar->state = ATH10K_STATE_RESTARTING;
		ath10k_halt(ar);
		ath10k_scan_finish(ar);
		ieee80211_restart_hw(ar->hw);
		अवरोध;
	हाल ATH10K_STATE_OFF:
		/* this can happen अगर driver is being unloaded
		 * or अगर the crash happens during FW probing
		 */
		ath10k_warn(ar, "cannot restart a device that hasn't been started\n");
		अवरोध;
	हाल ATH10K_STATE_RESTARTING:
		/* hw restart might be requested from multiple places */
		अवरोध;
	हाल ATH10K_STATE_RESTARTED:
		ar->state = ATH10K_STATE_WEDGED;
		fallthrough;
	हाल ATH10K_STATE_WEDGED:
		ath10k_warn(ar, "device is wedged, will not restart\n");
		अवरोध;
	हाल ATH10K_STATE_UTF:
		ath10k_warn(ar, "firmware restart in UTF mode not supported\n");
		अवरोध;
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	ret = ath10k_coredump_submit(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to send firmware crash dump via devcoredump: %d",
			    ret);

	complete(&ar->driver_recovery);
पूर्ण

अटल व्योम ath10k_core_set_coverage_class_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k,
					 set_coverage_class_work);

	अगर (ar->hw_params.hw_ops->set_coverage_class)
		ar->hw_params.hw_ops->set_coverage_class(ar, -1);
पूर्ण

अटल पूर्णांक ath10k_core_init_firmware_features(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_fw_file *fw_file = &ar->normal_mode_fw.fw_file;
	पूर्णांक max_num_peers;

	अगर (test_bit(ATH10K_FW_FEATURE_WMI_10_2, fw_file->fw_features) &&
	    !test_bit(ATH10K_FW_FEATURE_WMI_10X, fw_file->fw_features)) अणु
		ath10k_err(ar, "feature bits corrupted: 10.2 feature requires 10.x feature to be set as well");
		वापस -EINVAL;
	पूर्ण

	अगर (fw_file->wmi_op_version >= ATH10K_FW_WMI_OP_VERSION_MAX) अणु
		ath10k_err(ar, "unsupported WMI OP version (max %d): %d\n",
			   ATH10K_FW_WMI_OP_VERSION_MAX, fw_file->wmi_op_version);
		वापस -EINVAL;
	पूर्ण

	ar->wmi.rx_decap_mode = ATH10K_HW_TXRX_NATIVE_WIFI;
	चयन (ath10k_crypपंचांगode_param) अणु
	हाल ATH10K_CRYPT_MODE_HW:
		clear_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags);
		clear_bit(ATH10K_FLAG_HW_CRYPTO_DISABLED, &ar->dev_flags);
		अवरोध;
	हाल ATH10K_CRYPT_MODE_SW:
		अगर (!test_bit(ATH10K_FW_FEATURE_RAW_MODE_SUPPORT,
			      fw_file->fw_features)) अणु
			ath10k_err(ar, "cryptmode > 0 requires raw mode support from firmware");
			वापस -EINVAL;
		पूर्ण

		set_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags);
		set_bit(ATH10K_FLAG_HW_CRYPTO_DISABLED, &ar->dev_flags);
		अवरोध;
	शेष:
		ath10k_info(ar, "invalid cryptmode: %d\n",
			    ath10k_crypपंचांगode_param);
		वापस -EINVAL;
	पूर्ण

	ar->htt.max_num_amsdu = ATH10K_HTT_MAX_NUM_AMSDU_DEFAULT;
	ar->htt.max_num_ampdu = ATH10K_HTT_MAX_NUM_AMPDU_DEFAULT;

	अगर (rawmode) अणु
		अगर (!test_bit(ATH10K_FW_FEATURE_RAW_MODE_SUPPORT,
			      fw_file->fw_features)) अणु
			ath10k_err(ar, "rawmode = 1 requires support from firmware");
			वापस -EINVAL;
		पूर्ण
		set_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags);
	पूर्ण

	अगर (test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) अणु
		ar->wmi.rx_decap_mode = ATH10K_HW_TXRX_RAW;

		/* Workaround:
		 *
		 * Firmware A-MSDU aggregation अवरोधs with RAW Tx encap mode
		 * and causes enormous perक्रमmance issues (malक्रमmed frames,
		 * etc).
		 *
		 * Disabling A-MSDU makes RAW mode stable with heavy traffic
		 * albeit a bit slower compared to regular operation.
		 */
		ar->htt.max_num_amsdu = 1;
	पूर्ण

	/* Backwards compatibility क्रम firmwares without
	 * ATH10K_FW_IE_WMI_OP_VERSION.
	 */
	अगर (fw_file->wmi_op_version == ATH10K_FW_WMI_OP_VERSION_UNSET) अणु
		अगर (test_bit(ATH10K_FW_FEATURE_WMI_10X, fw_file->fw_features)) अणु
			अगर (test_bit(ATH10K_FW_FEATURE_WMI_10_2,
				     fw_file->fw_features))
				fw_file->wmi_op_version = ATH10K_FW_WMI_OP_VERSION_10_2;
			अन्यथा
				fw_file->wmi_op_version = ATH10K_FW_WMI_OP_VERSION_10_1;
		पूर्ण अन्यथा अणु
			fw_file->wmi_op_version = ATH10K_FW_WMI_OP_VERSION_MAIN;
		पूर्ण
	पूर्ण

	चयन (fw_file->wmi_op_version) अणु
	हाल ATH10K_FW_WMI_OP_VERSION_MAIN:
		max_num_peers = TARGET_NUM_PEERS;
		ar->max_num_stations = TARGET_NUM_STATIONS;
		ar->max_num_vdevs = TARGET_NUM_VDEVS;
		ar->htt.max_num_pending_tx = TARGET_NUM_MSDU_DESC;
		ar->fw_stats_req_mask = WMI_STAT_PDEV | WMI_STAT_VDEV |
			WMI_STAT_PEER;
		ar->max_spatial_stream = WMI_MAX_SPATIAL_STREAM;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_1:
	हाल ATH10K_FW_WMI_OP_VERSION_10_2:
	हाल ATH10K_FW_WMI_OP_VERSION_10_2_4:
		अगर (ath10k_peer_stats_enabled(ar)) अणु
			max_num_peers = TARGET_10X_TX_STATS_NUM_PEERS;
			ar->max_num_stations = TARGET_10X_TX_STATS_NUM_STATIONS;
		पूर्ण अन्यथा अणु
			max_num_peers = TARGET_10X_NUM_PEERS;
			ar->max_num_stations = TARGET_10X_NUM_STATIONS;
		पूर्ण
		ar->max_num_vdevs = TARGET_10X_NUM_VDEVS;
		ar->htt.max_num_pending_tx = TARGET_10X_NUM_MSDU_DESC;
		ar->fw_stats_req_mask = WMI_STAT_PEER;
		ar->max_spatial_stream = WMI_MAX_SPATIAL_STREAM;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_TLV:
		max_num_peers = TARGET_TLV_NUM_PEERS;
		ar->max_num_stations = TARGET_TLV_NUM_STATIONS;
		ar->max_num_vdevs = TARGET_TLV_NUM_VDEVS;
		ar->max_num_tdls_vdevs = TARGET_TLV_NUM_TDLS_VDEVS;
		अगर (ar->hअगर.bus == ATH10K_BUS_SDIO)
			ar->htt.max_num_pending_tx =
				TARGET_TLV_NUM_MSDU_DESC_HL;
		अन्यथा
			ar->htt.max_num_pending_tx = TARGET_TLV_NUM_MSDU_DESC;
		ar->wow.max_num_patterns = TARGET_TLV_NUM_WOW_PATTERNS;
		ar->fw_stats_req_mask = WMI_TLV_STAT_PDEV | WMI_TLV_STAT_VDEV |
			WMI_TLV_STAT_PEER | WMI_TLV_STAT_PEER_EXTD;
		ar->max_spatial_stream = WMI_MAX_SPATIAL_STREAM;
		ar->wmi.mgmt_max_num_pending_tx = TARGET_TLV_MGMT_NUM_MSDU_DESC;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_4:
		max_num_peers = TARGET_10_4_NUM_PEERS;
		ar->max_num_stations = TARGET_10_4_NUM_STATIONS;
		ar->num_active_peers = TARGET_10_4_ACTIVE_PEERS;
		ar->max_num_vdevs = TARGET_10_4_NUM_VDEVS;
		ar->num_tids = TARGET_10_4_TGT_NUM_TIDS;
		ar->fw_stats_req_mask = WMI_10_4_STAT_PEER |
					WMI_10_4_STAT_PEER_EXTD |
					WMI_10_4_STAT_VDEV_EXTD;
		ar->max_spatial_stream = ar->hw_params.max_spatial_stream;
		ar->max_num_tdls_vdevs = TARGET_10_4_NUM_TDLS_VDEVS;

		अगर (test_bit(ATH10K_FW_FEATURE_PEER_FLOW_CONTROL,
			     fw_file->fw_features))
			ar->htt.max_num_pending_tx = TARGET_10_4_NUM_MSDU_DESC_PFC;
		अन्यथा
			ar->htt.max_num_pending_tx = TARGET_10_4_NUM_MSDU_DESC;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_UNSET:
	हाल ATH10K_FW_WMI_OP_VERSION_MAX:
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (ar->hw_params.num_peers)
		ar->max_num_peers = ar->hw_params.num_peers;
	अन्यथा
		ar->max_num_peers = max_num_peers;

	/* Backwards compatibility क्रम firmwares without
	 * ATH10K_FW_IE_HTT_OP_VERSION.
	 */
	अगर (fw_file->htt_op_version == ATH10K_FW_HTT_OP_VERSION_UNSET) अणु
		चयन (fw_file->wmi_op_version) अणु
		हाल ATH10K_FW_WMI_OP_VERSION_MAIN:
			fw_file->htt_op_version = ATH10K_FW_HTT_OP_VERSION_MAIN;
			अवरोध;
		हाल ATH10K_FW_WMI_OP_VERSION_10_1:
		हाल ATH10K_FW_WMI_OP_VERSION_10_2:
		हाल ATH10K_FW_WMI_OP_VERSION_10_2_4:
			fw_file->htt_op_version = ATH10K_FW_HTT_OP_VERSION_10_1;
			अवरोध;
		हाल ATH10K_FW_WMI_OP_VERSION_TLV:
			fw_file->htt_op_version = ATH10K_FW_HTT_OP_VERSION_TLV;
			अवरोध;
		हाल ATH10K_FW_WMI_OP_VERSION_10_4:
		हाल ATH10K_FW_WMI_OP_VERSION_UNSET:
		हाल ATH10K_FW_WMI_OP_VERSION_MAX:
			ath10k_err(ar, "htt op version not found from fw meta data");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_reset_rx_filter(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;
	पूर्णांक vdev_id;
	पूर्णांक vdev_type;
	पूर्णांक vdev_subtype;
	स्थिर u8 *vdev_addr;

	vdev_id = 0;
	vdev_type = WMI_VDEV_TYPE_STA;
	vdev_subtype = ath10k_wmi_get_vdev_subtype(ar, WMI_VDEV_SUBTYPE_NONE);
	vdev_addr = ar->mac_addr;

	ret = ath10k_wmi_vdev_create(ar, vdev_id, vdev_type, vdev_subtype,
				     vdev_addr);
	अगर (ret) अणु
		ath10k_err(ar, "failed to create dummy vdev: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_wmi_vdev_delete(ar, vdev_id);
	अगर (ret) अणु
		ath10k_err(ar, "failed to delete dummy vdev: %d\n", ret);
		वापस ret;
	पूर्ण

	/* WMI and HTT may use separate HIF pipes and are not guaranteed to be
	 * serialized properly implicitly.
	 *
	 * Moreover (most) WMI commands have no explicit acknowledges. It is
	 * possible to infer it implicitly by poking firmware with echo
	 * command - getting a reply means all preceding comments have been
	 * (mostly) processed.
	 *
	 * In हाल of vdev create/delete this is sufficient.
	 *
	 * Without this it's possible to end up with a race when HTT Rx ring is
	 * started beक्रमe vdev create/delete hack is complete allowing a लघु
	 * winकरोw of opportunity to receive (and Tx ACK) a bunch of frames.
	 */
	ret = ath10k_wmi_barrier(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to ping firmware: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_core_compat_services(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_fw_file *fw_file = &ar->normal_mode_fw.fw_file;

	/* all 10.x firmware versions support thermal throttling but करोn't
	 * advertise the support via service flags so we have to hardcode
	 * it here
	 */
	चयन (fw_file->wmi_op_version) अणु
	हाल ATH10K_FW_WMI_OP_VERSION_10_1:
	हाल ATH10K_FW_WMI_OP_VERSION_10_2:
	हाल ATH10K_FW_WMI_OP_VERSION_10_2_4:
	हाल ATH10K_FW_WMI_OP_VERSION_10_4:
		set_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा TGT_IRAM_READ_PER_ITR (8 * 1024)

अटल पूर्णांक ath10k_core_copy_target_iram(काष्ठा ath10k *ar)
अणु
	स्थिर काष्ठा ath10k_hw_mem_layout *hw_mem;
	स्थिर काष्ठा ath10k_mem_region *पंचांगp, *mem_region = शून्य;
	dma_addr_t paddr;
	व्योम *vaddr = शून्य;
	u8 num_पढ़ो_itr;
	पूर्णांक i, ret;
	u32 len, reमुख्यing_len;

	hw_mem = ath10k_coredump_get_mem_layout(ar);
	अगर (!hw_mem)
		वापस -ENOMEM;

	क्रम (i = 0; i < hw_mem->region_table.size; i++) अणु
		पंचांगp = &hw_mem->region_table.regions[i];
		अगर (पंचांगp->type == ATH10K_MEM_REGION_TYPE_REG) अणु
			mem_region = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mem_region)
		वापस -ENOMEM;

	क्रम (i = 0; i < ar->wmi.num_mem_chunks; i++) अणु
		अगर (ar->wmi.mem_chunks[i].req_id ==
		    WMI_IRAM_RECOVERY_HOST_MEM_REQ_ID) अणु
			vaddr = ar->wmi.mem_chunks[i].vaddr;
			len = ar->wmi.mem_chunks[i].len;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!vaddr || !len) अणु
		ath10k_warn(ar, "No allocated memory for IRAM back up");
		वापस -ENOMEM;
	पूर्ण

	len = (len < mem_region->len) ? len : mem_region->len;
	paddr = mem_region->start;
	num_पढ़ो_itr = len / TGT_IRAM_READ_PER_ITR;
	reमुख्यing_len = len % TGT_IRAM_READ_PER_ITR;
	क्रम (i = 0; i < num_पढ़ो_itr; i++) अणु
		ret = ath10k_hअगर_diag_पढ़ो(ar, paddr, vaddr,
					   TGT_IRAM_READ_PER_ITR);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to copy firmware IRAM contents: %d",
				    ret);
			वापस ret;
		पूर्ण

		paddr += TGT_IRAM_READ_PER_ITR;
		vaddr += TGT_IRAM_READ_PER_ITR;
	पूर्ण

	अगर (reमुख्यing_len) अणु
		ret = ath10k_hअगर_diag_पढ़ो(ar, paddr, vaddr, reमुख्यing_len);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to copy firmware IRAM contents: %d",
				    ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "target IRAM back up completed\n");

	वापस 0;
पूर्ण

पूर्णांक ath10k_core_start(काष्ठा ath10k *ar, क्रमागत ath10k_firmware_mode mode,
		      स्थिर काष्ठा ath10k_fw_components *fw)
अणु
	पूर्णांक status;
	u32 val;

	lockdep_निश्चित_held(&ar->conf_mutex);

	clear_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags);

	ar->running_fw = fw;

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->running_fw->fw_file.fw_features)) अणु
		ath10k_bmi_start(ar);

		/* Enable hardware घड़ी to speed up firmware करोwnload */
		अगर (ar->hw_params.hw_ops->enable_pll_clk) अणु
			status = ar->hw_params.hw_ops->enable_pll_clk(ar);
			ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot enable pll ret %d\n",
				   status);
		पूर्ण

		अगर (ath10k_init_configure_target(ar)) अणु
			status = -EINVAL;
			जाओ err;
		पूर्ण

		status = ath10k_करोwnload_cal_data(ar);
		अगर (status)
			जाओ err;

		/* Some of qca988x solutions are having global reset issue
		 * during target initialization. Bypassing PLL setting beक्रमe
		 * करोwnloading firmware and letting the SoC run on REF_CLK is
		 * fixing the problem. Corresponding firmware change is also
		 * needed to set the घड़ी source once the target is
		 * initialized.
		 */
		अगर (test_bit(ATH10K_FW_FEATURE_SUPPORTS_SKIP_CLOCK_INIT,
			     ar->running_fw->fw_file.fw_features)) अणु
			status = ath10k_bmi_ग_लिखो32(ar, hi_skip_घड़ी_init, 1);
			अगर (status) अणु
				ath10k_err(ar, "could not write to skip_clock_init: %d\n",
					   status);
				जाओ err;
			पूर्ण
		पूर्ण

		status = ath10k_करोwnload_fw(ar);
		अगर (status)
			जाओ err;

		status = ath10k_init_uart(ar);
		अगर (status)
			जाओ err;

		अगर (ar->hअगर.bus == ATH10K_BUS_SDIO) अणु
			status = ath10k_init_sdio(ar, mode);
			अगर (status) अणु
				ath10k_err(ar, "failed to init SDIO: %d\n", status);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	ar->htc.htc_ops.target_send_suspend_complete =
		ath10k_send_suspend_complete;

	status = ath10k_htc_init(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not init HTC (%d)\n", status);
		जाओ err;
	पूर्ण

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->running_fw->fw_file.fw_features)) अणु
		status = ath10k_bmi_करोne(ar);
		अगर (status)
			जाओ err;
	पूर्ण

	status = ath10k_wmi_attach(ar);
	अगर (status) अणु
		ath10k_err(ar, "WMI attach failed: %d\n", status);
		जाओ err;
	पूर्ण

	status = ath10k_htt_init(ar);
	अगर (status) अणु
		ath10k_err(ar, "failed to init htt: %d\n", status);
		जाओ err_wmi_detach;
	पूर्ण

	status = ath10k_htt_tx_start(&ar->htt);
	अगर (status) अणु
		ath10k_err(ar, "failed to alloc htt tx: %d\n", status);
		जाओ err_wmi_detach;
	पूर्ण

	/* If firmware indicates Full Rx Reorder support it must be used in a
	 * slightly dअगरferent manner. Let HTT code know.
	 */
	ar->htt.rx_ring.in_ord_rx = !!(test_bit(WMI_SERVICE_RX_FULL_REORDER,
						ar->wmi.svc_map));

	status = ath10k_htt_rx_alloc(&ar->htt);
	अगर (status) अणु
		ath10k_err(ar, "failed to alloc htt rx: %d\n", status);
		जाओ err_htt_tx_detach;
	पूर्ण

	status = ath10k_hअगर_start(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not start HIF: %d\n", status);
		जाओ err_htt_rx_detach;
	पूर्ण

	status = ath10k_htc_रुको_target(&ar->htc);
	अगर (status) अणु
		ath10k_err(ar, "failed to connect to HTC: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	status = ath10k_hअगर_start_post(ar);
	अगर (status) अणु
		ath10k_err(ar, "failed to swap mailbox: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	अगर (mode == ATH10K_FIRMWARE_MODE_NORMAL) अणु
		status = ath10k_htt_connect(&ar->htt);
		अगर (status) अणु
			ath10k_err(ar, "failed to connect htt (%d)\n", status);
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	status = ath10k_wmi_connect(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not connect wmi: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	status = ath10k_htc_start(&ar->htc);
	अगर (status) अणु
		ath10k_err(ar, "failed to start htc: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	अगर (mode == ATH10K_FIRMWARE_MODE_NORMAL) अणु
		status = ath10k_wmi_रुको_क्रम_service_पढ़ोy(ar);
		अगर (status) अणु
			ath10k_warn(ar, "wmi service ready event not received");
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "firmware %s booted\n",
		   ar->hw->wiphy->fw_version);

	अगर (test_bit(ATH10K_FW_FEATURE_IRAM_RECOVERY,
		     ar->running_fw->fw_file.fw_features)) अणु
		status = ath10k_core_copy_target_iram(ar);
		अगर (status) अणु
			ath10k_warn(ar, "failed to copy target iram contents: %d",
				    status);
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	अगर (test_bit(WMI_SERVICE_EXT_RES_CFG_SUPPORT, ar->wmi.svc_map) &&
	    mode == ATH10K_FIRMWARE_MODE_NORMAL) अणु
		val = 0;
		अगर (ath10k_peer_stats_enabled(ar))
			val = WMI_10_4_PEER_STATS;

		/* Enable vdev stats by शेष */
		val |= WMI_10_4_VDEV_STATS;

		अगर (test_bit(WMI_SERVICE_BSS_CHANNEL_INFO_64, ar->wmi.svc_map))
			val |= WMI_10_4_BSS_CHANNEL_INFO_64;

		ath10k_core_fetch_btcoex_dt(ar);

		/* 10.4 firmware supports BT-Coex without reloading firmware
		 * via pdev param. To support Bluetooth coexistence pdev param,
		 * WMI_COEX_GPIO_SUPPORT of extended resource config should be
		 * enabled always.
		 *
		 * We can still enable BTCOEX अगर firmware has the support
		 * eventhough btceox_support value is
		 * ATH10K_DT_BTCOEX_NOT_FOUND
		 */

		अगर (test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map) &&
		    test_bit(ATH10K_FW_FEATURE_BTCOEX_PARAM,
			     ar->running_fw->fw_file.fw_features) &&
		    ar->coex_support)
			val |= WMI_10_4_COEX_GPIO_SUPPORT;

		अगर (test_bit(WMI_SERVICE_TDLS_EXPLICIT_MODE_ONLY,
			     ar->wmi.svc_map))
			val |= WMI_10_4_TDLS_EXPLICIT_MODE_ONLY;

		अगर (test_bit(WMI_SERVICE_TDLS_UAPSD_BUFFER_STA,
			     ar->wmi.svc_map))
			val |= WMI_10_4_TDLS_UAPSD_BUFFER_STA;

		अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI,
			     ar->wmi.svc_map))
			val |= WMI_10_4_TX_DATA_ACK_RSSI;

		अगर (test_bit(WMI_SERVICE_REPORT_AIRTIME, ar->wmi.svc_map))
			val |= WMI_10_4_REPORT_AIRTIME;

		अगर (test_bit(WMI_SERVICE_EXT_PEER_TID_CONFIGS_SUPPORT,
			     ar->wmi.svc_map))
			val |= WMI_10_4_EXT_PEER_TID_CONFIGS_SUPPORT;

		status = ath10k_mac_ext_resource_config(ar, val);
		अगर (status) अणु
			ath10k_err(ar,
				   "failed to send ext resource cfg command : %d\n",
				   status);
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	status = ath10k_wmi_cmd_init(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not send WMI init command (%d)\n",
			   status);
		जाओ err_hअगर_stop;
	पूर्ण

	status = ath10k_wmi_रुको_क्रम_unअगरied_पढ़ोy(ar);
	अगर (status) अणु
		ath10k_err(ar, "wmi unified ready event not received\n");
		जाओ err_hअगर_stop;
	पूर्ण

	status = ath10k_core_compat_services(ar);
	अगर (status) अणु
		ath10k_err(ar, "compat services failed: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	status = ath10k_wmi_pdev_set_base_macaddr(ar, ar->mac_addr);
	अगर (status && status != -EOPNOTSUPP) अणु
		ath10k_err(ar,
			   "failed to set base mac address: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	/* Some firmware revisions करो not properly set up hardware rx filter
	 * रेजिस्टरs.
	 *
	 * A known example from QCA9880 and 10.2.4 is that MAC_PCU_ADDR1_MASK
	 * is filled with 0s instead of 1s allowing HW to respond with ACKs to
	 * any frames that matches MAC_PCU_RX_FILTER which is also
	 * misconfigured to accept anything.
	 *
	 * The ADDR1 is programmed using पूर्णांकernal firmware काष्ठाure field and
	 * can't be (easily/sanely) reached from the driver explicitly. It is
	 * possible to implicitly make it correct by creating a dummy vdev and
	 * then deleting it.
	 */
	अगर (ar->hw_params.hw_filter_reset_required &&
	    mode == ATH10K_FIRMWARE_MODE_NORMAL) अणु
		status = ath10k_core_reset_rx_filter(ar);
		अगर (status) अणु
			ath10k_err(ar,
				   "failed to reset rx filter: %d\n", status);
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	status = ath10k_htt_rx_ring_refill(ar);
	अगर (status) अणु
		ath10k_err(ar, "failed to refill htt rx ring: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	अगर (ar->max_num_vdevs >= 64)
		ar->मुक्त_vdev_map = 0xFFFFFFFFFFFFFFFFLL;
	अन्यथा
		ar->मुक्त_vdev_map = (1LL << ar->max_num_vdevs) - 1;

	INIT_LIST_HEAD(&ar->arvअगरs);

	/* we करोn't care about HTT in UTF mode */
	अगर (mode == ATH10K_FIRMWARE_MODE_NORMAL) अणु
		status = ath10k_htt_setup(&ar->htt);
		अगर (status) अणु
			ath10k_err(ar, "failed to setup htt: %d\n", status);
			जाओ err_hअगर_stop;
		पूर्ण
	पूर्ण

	status = ath10k_debug_start(ar);
	अगर (status)
		जाओ err_hअगर_stop;

	status = ath10k_hअगर_set_target_log_mode(ar, fw_diag_log);
	अगर (status && status != -EOPNOTSUPP) अणु
		ath10k_warn(ar, "set target log mode failed: %d\n", status);
		जाओ err_hअगर_stop;
	पूर्ण

	वापस 0;

err_hअगर_stop:
	ath10k_hअगर_stop(ar);
err_htt_rx_detach:
	ath10k_htt_rx_मुक्त(&ar->htt);
err_htt_tx_detach:
	ath10k_htt_tx_मुक्त(&ar->htt);
err_wmi_detach:
	ath10k_wmi_detach(ar);
err:
	वापस status;
पूर्ण
EXPORT_SYMBOL(ath10k_core_start);

पूर्णांक ath10k_रुको_क्रम_suspend(काष्ठा ath10k *ar, u32 suspend_opt)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	reinit_completion(&ar->target_suspend);

	ret = ath10k_wmi_pdev_suspend_target(ar, suspend_opt);
	अगर (ret) अणु
		ath10k_warn(ar, "could not suspend target (%d)\n", ret);
		वापस ret;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->target_suspend, 1 * HZ);

	अगर (!समय_left) अणु
		ath10k_warn(ar, "suspend timed out - target pause event never came\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_core_stop(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);
	ath10k_debug_stop(ar);

	/* try to suspend target */
	अगर (ar->state != ATH10K_STATE_RESTARTING &&
	    ar->state != ATH10K_STATE_UTF)
		ath10k_रुको_क्रम_suspend(ar, WMI_PDEV_SUSPEND_AND_DISABLE_INTR);

	ath10k_hअगर_stop(ar);
	ath10k_htt_tx_stop(&ar->htt);
	ath10k_htt_rx_मुक्त(&ar->htt);
	ath10k_wmi_detach(ar);

	ar->id.bmi_ids_valid = false;
पूर्ण
EXPORT_SYMBOL(ath10k_core_stop);

/* mac80211 manages fw/hw initialization through start/stop hooks. However in
 * order to know what hw capabilities should be advertised to mac80211 it is
 * necessary to load the firmware (and tear it करोwn immediately since start
 * hook will try to init it again) beक्रमe रेजिस्टरing
 */
अटल पूर्णांक ath10k_core_probe_fw(काष्ठा ath10k *ar)
अणु
	काष्ठा bmi_target_info target_info;
	पूर्णांक ret = 0;

	ret = ath10k_hअगर_घातer_up(ar, ATH10K_FIRMWARE_MODE_NORMAL);
	अगर (ret) अणु
		ath10k_err(ar, "could not power on hif bus (%d)\n", ret);
		वापस ret;
	पूर्ण

	चयन (ar->hअगर.bus) अणु
	हाल ATH10K_BUS_SDIO:
		स_रखो(&target_info, 0, माप(target_info));
		ret = ath10k_bmi_get_target_info_sdio(ar, &target_info);
		अगर (ret) अणु
			ath10k_err(ar, "could not get target info (%d)\n", ret);
			जाओ err_घातer_करोwn;
		पूर्ण
		ar->target_version = target_info.version;
		ar->hw->wiphy->hw_version = target_info.version;
		अवरोध;
	हाल ATH10K_BUS_PCI:
	हाल ATH10K_BUS_AHB:
	हाल ATH10K_BUS_USB:
		स_रखो(&target_info, 0, माप(target_info));
		ret = ath10k_bmi_get_target_info(ar, &target_info);
		अगर (ret) अणु
			ath10k_err(ar, "could not get target info (%d)\n", ret);
			जाओ err_घातer_करोwn;
		पूर्ण
		ar->target_version = target_info.version;
		ar->hw->wiphy->hw_version = target_info.version;
		अवरोध;
	हाल ATH10K_BUS_SNOC:
		स_रखो(&target_info, 0, माप(target_info));
		ret = ath10k_hअगर_get_target_info(ar, &target_info);
		अगर (ret) अणु
			ath10k_err(ar, "could not get target info (%d)\n", ret);
			जाओ err_घातer_करोwn;
		पूर्ण
		ar->target_version = target_info.version;
		ar->hw->wiphy->hw_version = target_info.version;
		अवरोध;
	शेष:
		ath10k_err(ar, "incorrect hif bus type: %d\n", ar->hअगर.bus);
	पूर्ण

	ret = ath10k_init_hw_params(ar);
	अगर (ret) अणु
		ath10k_err(ar, "could not get hw params (%d)\n", ret);
		जाओ err_घातer_करोwn;
	पूर्ण

	ret = ath10k_core_fetch_firmware_files(ar);
	अगर (ret) अणु
		ath10k_err(ar, "could not fetch firmware files (%d)\n", ret);
		जाओ err_घातer_करोwn;
	पूर्ण

	BUILD_BUG_ON(माप(ar->hw->wiphy->fw_version) !=
		     माप(ar->normal_mode_fw.fw_file.fw_version));
	स_नकल(ar->hw->wiphy->fw_version, ar->normal_mode_fw.fw_file.fw_version,
	       माप(ar->hw->wiphy->fw_version));

	ath10k_debug_prपूर्णांक_hwfw_info(ar);

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->normal_mode_fw.fw_file.fw_features)) अणु
		ret = ath10k_core_pre_cal_करोwnload(ar);
		अगर (ret) अणु
			/* pre calibration data करोwnload is not necessary
			 * क्रम all the chipsets. Ignore failures and जारी.
			 */
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "could not load pre cal data: %d\n", ret);
		पूर्ण

		ret = ath10k_core_get_board_id_from_otp(ar);
		अगर (ret && ret != -EOPNOTSUPP) अणु
			ath10k_err(ar, "failed to get board id from otp: %d\n",
				   ret);
			जाओ err_मुक्त_firmware_files;
		पूर्ण

		ret = ath10k_core_check_smbios(ar);
		अगर (ret)
			ath10k_dbg(ar, ATH10K_DBG_BOOT, "SMBIOS bdf variant name not set.\n");

		ret = ath10k_core_check_dt(ar);
		अगर (ret)
			ath10k_dbg(ar, ATH10K_DBG_BOOT, "DT bdf variant name not set.\n");

		ret = ath10k_core_fetch_board_file(ar, ATH10K_BD_IE_BOARD);
		अगर (ret) अणु
			ath10k_err(ar, "failed to fetch board file: %d\n", ret);
			जाओ err_मुक्त_firmware_files;
		पूर्ण

		ath10k_debug_prपूर्णांक_board_info(ar);
	पूर्ण

	device_get_mac_address(ar->dev, ar->mac_addr, माप(ar->mac_addr));

	ret = ath10k_core_init_firmware_features(ar);
	अगर (ret) अणु
		ath10k_err(ar, "fatal problem with firmware features: %d\n",
			   ret);
		जाओ err_मुक्त_firmware_files;
	पूर्ण

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->normal_mode_fw.fw_file.fw_features)) अणु
		ret = ath10k_swap_code_seg_init(ar,
						&ar->normal_mode_fw.fw_file);
		अगर (ret) अणु
			ath10k_err(ar, "failed to initialize code swap segment: %d\n",
				   ret);
			जाओ err_मुक्त_firmware_files;
		पूर्ण
	पूर्ण

	mutex_lock(&ar->conf_mutex);

	ret = ath10k_core_start(ar, ATH10K_FIRMWARE_MODE_NORMAL,
				&ar->normal_mode_fw);
	अगर (ret) अणु
		ath10k_err(ar, "could not init core (%d)\n", ret);
		जाओ err_unlock;
	पूर्ण

	ath10k_debug_prपूर्णांक_boot_info(ar);
	ath10k_core_stop(ar);

	mutex_unlock(&ar->conf_mutex);

	ath10k_hअगर_घातer_करोwn(ar);
	वापस 0;

err_unlock:
	mutex_unlock(&ar->conf_mutex);

err_मुक्त_firmware_files:
	ath10k_core_मुक्त_firmware_files(ar);

err_घातer_करोwn:
	ath10k_hअगर_घातer_करोwn(ar);

	वापस ret;
पूर्ण

अटल व्योम ath10k_core_रेजिस्टर_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, रेजिस्टर_work);
	पूर्णांक status;

	/* peer stats are enabled by शेष */
	set_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags);

	status = ath10k_core_probe_fw(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not probe fw (%d)\n", status);
		जाओ err;
	पूर्ण

	status = ath10k_mac_रेजिस्टर(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not register to mac80211 (%d)\n", status);
		जाओ err_release_fw;
	पूर्ण

	status = ath10k_coredump_रेजिस्टर(ar);
	अगर (status) अणु
		ath10k_err(ar, "unable to register coredump\n");
		जाओ err_unरेजिस्टर_mac;
	पूर्ण

	status = ath10k_debug_रेजिस्टर(ar);
	अगर (status) अणु
		ath10k_err(ar, "unable to initialize debugfs\n");
		जाओ err_unरेजिस्टर_coredump;
	पूर्ण

	status = ath10k_spectral_create(ar);
	अगर (status) अणु
		ath10k_err(ar, "failed to initialize spectral\n");
		जाओ err_debug_destroy;
	पूर्ण

	status = ath10k_thermal_रेजिस्टर(ar);
	अगर (status) अणु
		ath10k_err(ar, "could not register thermal device: %d\n",
			   status);
		जाओ err_spectral_destroy;
	पूर्ण

	set_bit(ATH10K_FLAG_CORE_REGISTERED, &ar->dev_flags);
	वापस;

err_spectral_destroy:
	ath10k_spectral_destroy(ar);
err_debug_destroy:
	ath10k_debug_destroy(ar);
err_unरेजिस्टर_coredump:
	ath10k_coredump_unरेजिस्टर(ar);
err_unरेजिस्टर_mac:
	ath10k_mac_unरेजिस्टर(ar);
err_release_fw:
	ath10k_core_मुक्त_firmware_files(ar);
err:
	/* TODO: It's probably a good idea to release device from the driver
	 * but calling device_release_driver() here will cause a deadlock.
	 */
	वापस;
पूर्ण

पूर्णांक ath10k_core_रेजिस्टर(काष्ठा ath10k *ar,
			 स्थिर काष्ठा ath10k_bus_params *bus_params)
अणु
	ar->bus_param = *bus_params;

	queue_work(ar->workqueue, &ar->रेजिस्टर_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath10k_core_रेजिस्टर);

व्योम ath10k_core_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
	cancel_work_sync(&ar->रेजिस्टर_work);

	अगर (!test_bit(ATH10K_FLAG_CORE_REGISTERED, &ar->dev_flags))
		वापस;

	ath10k_thermal_unरेजिस्टर(ar);
	/* Stop spectral beक्रमe unरेजिस्टरing from mac80211 to हटाओ the
	 * relayfs debugfs file cleanly. Otherwise the parent debugfs tree
	 * would be alपढ़ोy be मुक्त'd recursively, leading to a द्विगुन मुक्त.
	 */
	ath10k_spectral_destroy(ar);

	/* We must unरेजिस्टर from mac80211 beक्रमe we stop HTC and HIF.
	 * Otherwise we will fail to submit commands to FW and mac80211 will be
	 * unhappy about callback failures.
	 */
	ath10k_mac_unरेजिस्टर(ar);

	ath10k_tesपंचांगode_destroy(ar);

	ath10k_core_मुक्त_firmware_files(ar);
	ath10k_core_मुक्त_board_files(ar);

	ath10k_debug_unरेजिस्टर(ar);
पूर्ण
EXPORT_SYMBOL(ath10k_core_unरेजिस्टर);

काष्ठा ath10k *ath10k_core_create(माप_प्रकार priv_size, काष्ठा device *dev,
				  क्रमागत ath10k_bus bus,
				  क्रमागत ath10k_hw_rev hw_rev,
				  स्थिर काष्ठा ath10k_hअगर_ops *hअगर_ops)
अणु
	काष्ठा ath10k *ar;
	पूर्णांक ret;

	ar = ath10k_mac_create(priv_size);
	अगर (!ar)
		वापस शून्य;

	ar->ath_common.priv = ar;
	ar->ath_common.hw = ar->hw;
	ar->dev = dev;
	ar->hw_rev = hw_rev;
	ar->hअगर.ops = hअगर_ops;
	ar->hअगर.bus = bus;

	चयन (hw_rev) अणु
	हाल ATH10K_HW_QCA988X:
	हाल ATH10K_HW_QCA9887:
		ar->regs = &qca988x_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca988x_values;
		अवरोध;
	हाल ATH10K_HW_QCA6174:
	हाल ATH10K_HW_QCA9377:
		ar->regs = &qca6174_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca6174_values;
		अवरोध;
	हाल ATH10K_HW_QCA99X0:
	हाल ATH10K_HW_QCA9984:
		ar->regs = &qca99x0_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca99x0_values;
		अवरोध;
	हाल ATH10K_HW_QCA9888:
		ar->regs = &qca99x0_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca9888_values;
		अवरोध;
	हाल ATH10K_HW_QCA4019:
		ar->regs = &qca4019_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca4019_values;
		अवरोध;
	हाल ATH10K_HW_WCN3990:
		ar->regs = &wcn3990_regs;
		ar->hw_ce_regs = &wcn3990_ce_regs;
		ar->hw_values = &wcn3990_values;
		अवरोध;
	शेष:
		ath10k_err(ar, "unsupported core hardware revision %d\n",
			   hw_rev);
		ret = -ENOTSUPP;
		जाओ err_मुक्त_mac;
	पूर्ण

	init_completion(&ar->scan.started);
	init_completion(&ar->scan.completed);
	init_completion(&ar->scan.on_channel);
	init_completion(&ar->target_suspend);
	init_completion(&ar->driver_recovery);
	init_completion(&ar->wow.wakeup_completed);

	init_completion(&ar->install_key_करोne);
	init_completion(&ar->vdev_setup_करोne);
	init_completion(&ar->vdev_delete_करोne);
	init_completion(&ar->thermal.wmi_sync);
	init_completion(&ar->bss_survey_करोne);
	init_completion(&ar->peer_delete_करोne);
	init_completion(&ar->peer_stats_info_complete);

	INIT_DELAYED_WORK(&ar->scan.समयout, ath10k_scan_समयout_work);

	ar->workqueue = create_singlethपढ़ो_workqueue("ath10k_wq");
	अगर (!ar->workqueue)
		जाओ err_मुक्त_mac;

	ar->workqueue_aux = create_singlethपढ़ो_workqueue("ath10k_aux_wq");
	अगर (!ar->workqueue_aux)
		जाओ err_मुक्त_wq;

	ar->workqueue_tx_complete =
		create_singlethपढ़ो_workqueue("ath10k_tx_complete_wq");
	अगर (!ar->workqueue_tx_complete)
		जाओ err_मुक्त_aux_wq;

	mutex_init(&ar->conf_mutex);
	mutex_init(&ar->dump_mutex);
	spin_lock_init(&ar->data_lock);

	INIT_LIST_HEAD(&ar->peers);
	init_रुकोqueue_head(&ar->peer_mapping_wq);
	init_रुकोqueue_head(&ar->htt.empty_tx_wq);
	init_रुकोqueue_head(&ar->wmi.tx_credits_wq);

	skb_queue_head_init(&ar->htt.rx_indication_head);

	init_completion(&ar->offchan_tx_completed);
	INIT_WORK(&ar->offchan_tx_work, ath10k_offchan_tx_work);
	skb_queue_head_init(&ar->offchan_tx_queue);

	INIT_WORK(&ar->wmi_mgmt_tx_work, ath10k_mgmt_over_wmi_tx_work);
	skb_queue_head_init(&ar->wmi_mgmt_tx_queue);

	INIT_WORK(&ar->रेजिस्टर_work, ath10k_core_रेजिस्टर_work);
	INIT_WORK(&ar->restart_work, ath10k_core_restart);
	INIT_WORK(&ar->set_coverage_class_work,
		  ath10k_core_set_coverage_class_work);

	init_dummy_netdev(&ar->napi_dev);

	ret = ath10k_coredump_create(ar);
	अगर (ret)
		जाओ err_मुक्त_tx_complete;

	ret = ath10k_debug_create(ar);
	अगर (ret)
		जाओ err_मुक्त_coredump;

	वापस ar;

err_मुक्त_coredump:
	ath10k_coredump_destroy(ar);
err_मुक्त_tx_complete:
	destroy_workqueue(ar->workqueue_tx_complete);
err_मुक्त_aux_wq:
	destroy_workqueue(ar->workqueue_aux);
err_मुक्त_wq:
	destroy_workqueue(ar->workqueue);
err_मुक्त_mac:
	ath10k_mac_destroy(ar);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ath10k_core_create);

व्योम ath10k_core_destroy(काष्ठा ath10k *ar)
अणु
	flush_workqueue(ar->workqueue);
	destroy_workqueue(ar->workqueue);

	flush_workqueue(ar->workqueue_aux);
	destroy_workqueue(ar->workqueue_aux);

	flush_workqueue(ar->workqueue_tx_complete);
	destroy_workqueue(ar->workqueue_tx_complete);

	ath10k_debug_destroy(ar);
	ath10k_coredump_destroy(ar);
	ath10k_htt_tx_destroy(&ar->htt);
	ath10k_wmi_मुक्त_host_mem(ar);
	ath10k_mac_destroy(ar);
पूर्ण
EXPORT_SYMBOL(ath10k_core_destroy);

MODULE_AUTHOR("Qualcomm Atheros");
MODULE_DESCRIPTION("Core module for Qualcomm Atheros 802.11ac wireless LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");
