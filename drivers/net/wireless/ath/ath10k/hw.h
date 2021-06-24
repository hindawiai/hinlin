<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _HW_H_
#घोषणा _HW_H_

#समावेश "targaddrs.h"

क्रमागत ath10k_bus अणु
	ATH10K_BUS_PCI,
	ATH10K_BUS_AHB,
	ATH10K_BUS_SDIO,
	ATH10K_BUS_USB,
	ATH10K_BUS_SNOC,
पूर्ण;

#घोषणा ATH10K_FW_सूची			"ath10k"

#घोषणा QCA988X_2_0_DEVICE_ID_UBNT   (0x11ac)
#घोषणा QCA988X_2_0_DEVICE_ID   (0x003c)
#घोषणा QCA6164_2_1_DEVICE_ID   (0x0041)
#घोषणा QCA6174_2_1_DEVICE_ID   (0x003e)
#घोषणा QCA6174_3_2_DEVICE_ID   (0x0042)
#घोषणा QCA99X0_2_0_DEVICE_ID   (0x0040)
#घोषणा QCA9888_2_0_DEVICE_ID	(0x0056)
#घोषणा QCA9984_1_0_DEVICE_ID	(0x0046)
#घोषणा QCA9377_1_0_DEVICE_ID   (0x0042)
#घोषणा QCA9887_1_0_DEVICE_ID   (0x0050)

/* QCA988X 1.0 definitions (unsupported) */
#घोषणा QCA988X_HW_1_0_CHIP_ID_REV	0x0

/* QCA988X 2.0 definitions */
#घोषणा QCA988X_HW_2_0_VERSION		0x4100016c
#घोषणा QCA988X_HW_2_0_CHIP_ID_REV	0x2
#घोषणा QCA988X_HW_2_0_FW_सूची		ATH10K_FW_सूची "/QCA988X/hw2.0"
#घोषणा QCA988X_HW_2_0_BOARD_DATA_खाता	"board.bin"
#घोषणा QCA988X_HW_2_0_PATCH_LOAD_ADDR	0x1234

/* QCA9887 1.0 definitions */
#घोषणा QCA9887_HW_1_0_VERSION		0x4100016d
#घोषणा QCA9887_HW_1_0_CHIP_ID_REV	0
#घोषणा QCA9887_HW_1_0_FW_सूची		ATH10K_FW_सूची "/QCA9887/hw1.0"
#घोषणा QCA9887_HW_1_0_BOARD_DATA_खाता	"board.bin"
#घोषणा QCA9887_HW_1_0_PATCH_LOAD_ADDR	0x1234

/* QCA6174 target BMI version signatures */
#घोषणा QCA6174_HW_1_0_VERSION		0x05000000
#घोषणा QCA6174_HW_1_1_VERSION		0x05000001
#घोषणा QCA6174_HW_1_3_VERSION		0x05000003
#घोषणा QCA6174_HW_2_1_VERSION		0x05010000
#घोषणा QCA6174_HW_3_0_VERSION		0x05020000
#घोषणा QCA6174_HW_3_2_VERSION		0x05030000

/* QCA9377 target BMI version signatures */
#घोषणा QCA9377_HW_1_0_DEV_VERSION	0x05020000
#घोषणा QCA9377_HW_1_1_DEV_VERSION	0x05020001

क्रमागत qca6174_pci_rev अणु
	QCA6174_PCI_REV_1_1 = 0x11,
	QCA6174_PCI_REV_1_3 = 0x13,
	QCA6174_PCI_REV_2_0 = 0x20,
	QCA6174_PCI_REV_3_0 = 0x30,
पूर्ण;

क्रमागत qca6174_chip_id_rev अणु
	QCA6174_HW_1_0_CHIP_ID_REV = 0,
	QCA6174_HW_1_1_CHIP_ID_REV = 1,
	QCA6174_HW_1_3_CHIP_ID_REV = 2,
	QCA6174_HW_2_1_CHIP_ID_REV = 4,
	QCA6174_HW_2_2_CHIP_ID_REV = 5,
	QCA6174_HW_3_0_CHIP_ID_REV = 8,
	QCA6174_HW_3_1_CHIP_ID_REV = 9,
	QCA6174_HW_3_2_CHIP_ID_REV = 10,
पूर्ण;

क्रमागत qca9377_chip_id_rev अणु
	QCA9377_HW_1_0_CHIP_ID_REV = 0x0,
	QCA9377_HW_1_1_CHIP_ID_REV = 0x1,
पूर्ण;

#घोषणा QCA6174_HW_2_1_FW_सूची		ATH10K_FW_सूची "/QCA6174/hw2.1"
#घोषणा QCA6174_HW_2_1_BOARD_DATA_खाता	"board.bin"
#घोषणा QCA6174_HW_2_1_PATCH_LOAD_ADDR	0x1234

#घोषणा QCA6174_HW_3_0_FW_सूची		ATH10K_FW_सूची "/QCA6174/hw3.0"
#घोषणा QCA6174_HW_3_0_BOARD_DATA_खाता	"board.bin"
#घोषणा QCA6174_HW_3_0_PATCH_LOAD_ADDR	0x1234

/* QCA99X0 1.0 definitions (unsupported) */
#घोषणा QCA99X0_HW_1_0_CHIP_ID_REV     0x0

/* QCA99X0 2.0 definitions */
#घोषणा QCA99X0_HW_2_0_DEV_VERSION     0x01000000
#घोषणा QCA99X0_HW_2_0_CHIP_ID_REV     0x1
#घोषणा QCA99X0_HW_2_0_FW_सूची          ATH10K_FW_सूची "/QCA99X0/hw2.0"
#घोषणा QCA99X0_HW_2_0_BOARD_DATA_खाता "board.bin"
#घोषणा QCA99X0_HW_2_0_PATCH_LOAD_ADDR	0x1234

/* QCA9984 1.0 defines */
#घोषणा QCA9984_HW_1_0_DEV_VERSION	0x1000000
#घोषणा QCA9984_HW_DEV_TYPE		0xa
#घोषणा QCA9984_HW_1_0_CHIP_ID_REV	0x0
#घोषणा QCA9984_HW_1_0_FW_सूची		ATH10K_FW_सूची "/QCA9984/hw1.0"
#घोषणा QCA9984_HW_1_0_BOARD_DATA_खाता "board.bin"
#घोषणा QCA9984_HW_1_0_EBOARD_DATA_खाता "eboard.bin"
#घोषणा QCA9984_HW_1_0_PATCH_LOAD_ADDR	0x1234

/* QCA9888 2.0 defines */
#घोषणा QCA9888_HW_2_0_DEV_VERSION	0x1000000
#घोषणा QCA9888_HW_DEV_TYPE		0xc
#घोषणा QCA9888_HW_2_0_CHIP_ID_REV	0x0
#घोषणा QCA9888_HW_2_0_FW_सूची		ATH10K_FW_सूची "/QCA9888/hw2.0"
#घोषणा QCA9888_HW_2_0_BOARD_DATA_खाता "board.bin"
#घोषणा QCA9888_HW_2_0_PATCH_LOAD_ADDR	0x1234

/* QCA9377 1.0 definitions */
#घोषणा QCA9377_HW_1_0_FW_सूची          ATH10K_FW_सूची "/QCA9377/hw1.0"
#घोषणा QCA9377_HW_1_0_BOARD_DATA_खाता "board.bin"
#घोषणा QCA9377_HW_1_0_PATCH_LOAD_ADDR	0x1234

/* QCA4019 1.0 definitions */
#घोषणा QCA4019_HW_1_0_DEV_VERSION     0x01000000
#घोषणा QCA4019_HW_1_0_FW_सूची          ATH10K_FW_सूची "/QCA4019/hw1.0"
#घोषणा QCA4019_HW_1_0_BOARD_DATA_खाता "board.bin"
#घोषणा QCA4019_HW_1_0_PATCH_LOAD_ADDR  0x1234

/* WCN3990 1.0 definitions */
#घोषणा WCN3990_HW_1_0_DEV_VERSION	ATH10K_HW_WCN3990
#घोषणा WCN3990_HW_1_0_FW_सूची		ATH10K_FW_सूची "/WCN3990/hw1.0"

#घोषणा ATH10K_FW_खाता_BASE		"firmware"
#घोषणा ATH10K_FW_API_MAX		6
#घोषणा ATH10K_FW_API_MIN		2

#घोषणा ATH10K_FW_API2_खाता		"firmware-2.bin"
#घोषणा ATH10K_FW_API3_खाता		"firmware-3.bin"

/* added support क्रम ATH10K_FW_IE_WMI_OP_VERSION */
#घोषणा ATH10K_FW_API4_खाता		"firmware-4.bin"

/* HTT id conflict fix क्रम management frames over HTT */
#घोषणा ATH10K_FW_API5_खाता		"firmware-5.bin"

/* the firmware-6.bin blob */
#घोषणा ATH10K_FW_API6_खाता		"firmware-6.bin"

#घोषणा ATH10K_FW_UTF_खाता		"utf.bin"
#घोषणा ATH10K_FW_UTF_API2_खाता		"utf-2.bin"

#घोषणा ATH10K_FW_UTF_खाता_BASE		"utf"

/* includes also the null byte */
#घोषणा ATH10K_FIRMWARE_MAGIC               "QCA-ATH10K"
#घोषणा ATH10K_BOARD_MAGIC                  "QCA-ATH10K-BOARD"

#घोषणा ATH10K_BOARD_API2_खाता         "board-2.bin"

#घोषणा REG_DUMP_COUNT_QCA988X 60

काष्ठा ath10k_fw_ie अणु
	__le32 id;
	__le32 len;
	u8 data[];
पूर्ण;

क्रमागत ath10k_fw_ie_type अणु
	ATH10K_FW_IE_FW_VERSION = 0,
	ATH10K_FW_IE_TIMESTAMP = 1,
	ATH10K_FW_IE_FEATURES = 2,
	ATH10K_FW_IE_FW_IMAGE = 3,
	ATH10K_FW_IE_OTP_IMAGE = 4,

	/* WMI "operations" पूर्णांकerface version, 32 bit value. Supported from
	 * FW API 4 and above.
	 */
	ATH10K_FW_IE_WMI_OP_VERSION = 5,

	/* HTT "operations" पूर्णांकerface version, 32 bit value. Supported from
	 * FW API 5 and above.
	 */
	ATH10K_FW_IE_HTT_OP_VERSION = 6,

	/* Code swap image क्रम firmware binary */
	ATH10K_FW_IE_FW_CODE_SWAP_IMAGE = 7,
पूर्ण;

क्रमागत ath10k_fw_wmi_op_version अणु
	ATH10K_FW_WMI_OP_VERSION_UNSET = 0,

	ATH10K_FW_WMI_OP_VERSION_MAIN = 1,
	ATH10K_FW_WMI_OP_VERSION_10_1 = 2,
	ATH10K_FW_WMI_OP_VERSION_10_2 = 3,
	ATH10K_FW_WMI_OP_VERSION_TLV = 4,
	ATH10K_FW_WMI_OP_VERSION_10_2_4 = 5,
	ATH10K_FW_WMI_OP_VERSION_10_4 = 6,

	/* keep last */
	ATH10K_FW_WMI_OP_VERSION_MAX,
पूर्ण;

क्रमागत ath10k_fw_htt_op_version अणु
	ATH10K_FW_HTT_OP_VERSION_UNSET = 0,

	ATH10K_FW_HTT_OP_VERSION_MAIN = 1,

	/* also used in 10.2 and 10.2.4 branches */
	ATH10K_FW_HTT_OP_VERSION_10_1 = 2,

	ATH10K_FW_HTT_OP_VERSION_TLV = 3,

	ATH10K_FW_HTT_OP_VERSION_10_4 = 4,

	/* keep last */
	ATH10K_FW_HTT_OP_VERSION_MAX,
पूर्ण;

क्रमागत ath10k_bd_ie_type अणु
	/* contains sub IEs of क्रमागत ath10k_bd_ie_board_type */
	ATH10K_BD_IE_BOARD = 0,
	ATH10K_BD_IE_BOARD_EXT = 1,
पूर्ण;

क्रमागत ath10k_bd_ie_board_type अणु
	ATH10K_BD_IE_BOARD_NAME = 0,
	ATH10K_BD_IE_BOARD_DATA = 1,
पूर्ण;

क्रमागत ath10k_hw_rev अणु
	ATH10K_HW_QCA988X,
	ATH10K_HW_QCA6174,
	ATH10K_HW_QCA99X0,
	ATH10K_HW_QCA9888,
	ATH10K_HW_QCA9984,
	ATH10K_HW_QCA9377,
	ATH10K_HW_QCA4019,
	ATH10K_HW_QCA9887,
	ATH10K_HW_WCN3990,
पूर्ण;

काष्ठा ath10k_hw_regs अणु
	u32 rtc_soc_base_address;
	u32 rtc_wmac_base_address;
	u32 soc_core_base_address;
	u32 wlan_mac_base_address;
	u32 ce_wrapper_base_address;
	u32 ce0_base_address;
	u32 ce1_base_address;
	u32 ce2_base_address;
	u32 ce3_base_address;
	u32 ce4_base_address;
	u32 ce5_base_address;
	u32 ce6_base_address;
	u32 ce7_base_address;
	u32 ce8_base_address;
	u32 ce9_base_address;
	u32 ce10_base_address;
	u32 ce11_base_address;
	u32 soc_reset_control_si0_rst_mask;
	u32 soc_reset_control_ce_rst_mask;
	u32 soc_chip_id_address;
	u32 scratch_3_address;
	u32 fw_indicator_address;
	u32 pcie_local_base_address;
	u32 ce_wrap_पूर्णांकr_sum_host_msi_lsb;
	u32 ce_wrap_पूर्णांकr_sum_host_msi_mask;
	u32 pcie_पूर्णांकr_fw_mask;
	u32 pcie_पूर्णांकr_ce_mask_all;
	u32 pcie_पूर्णांकr_clr_address;
	u32 cpu_pll_init_address;
	u32 cpu_speed_address;
	u32 core_clk_भाग_address;
पूर्ण;

बाह्य स्थिर काष्ठा ath10k_hw_regs qca988x_regs;
बाह्य स्थिर काष्ठा ath10k_hw_regs qca6174_regs;
बाह्य स्थिर काष्ठा ath10k_hw_regs qca99x0_regs;
बाह्य स्थिर काष्ठा ath10k_hw_regs qca4019_regs;
बाह्य स्थिर काष्ठा ath10k_hw_regs wcn3990_regs;

काष्ठा ath10k_hw_ce_regs_addr_map अणु
	u32 msb;
	u32 lsb;
	u32 mask;
पूर्ण;

काष्ठा ath10k_hw_ce_ctrl1 अणु
	u32 addr;
	u32 hw_mask;
	u32 sw_mask;
	u32 hw_wr_mask;
	u32 sw_wr_mask;
	u32 reset_mask;
	u32 reset;
	काष्ठा ath10k_hw_ce_regs_addr_map *src_ring;
	काष्ठा ath10k_hw_ce_regs_addr_map *dst_ring;
	काष्ठा ath10k_hw_ce_regs_addr_map *dmax; पूर्ण;

काष्ठा ath10k_hw_ce_cmd_halt अणु
	u32 status_reset;
	u32 msb;
	u32 mask;
	काष्ठा ath10k_hw_ce_regs_addr_map *status; पूर्ण;

काष्ठा ath10k_hw_ce_host_ie अणु
	u32 copy_complete_reset;
	काष्ठा ath10k_hw_ce_regs_addr_map *copy_complete; पूर्ण;

काष्ठा ath10k_hw_ce_host_wm_regs अणु
	u32 dstr_lmask;
	u32 dstr_hmask;
	u32 srcr_lmask;
	u32 srcr_hmask;
	u32 cc_mask;
	u32 wm_mask;
	u32 addr;
पूर्ण;

काष्ठा ath10k_hw_ce_misc_regs अणु
	u32 axi_err;
	u32 dstr_add_err;
	u32 srcr_len_err;
	u32 dstr_mlen_vio;
	u32 dstr_overflow;
	u32 srcr_overflow;
	u32 err_mask;
	u32 addr;
पूर्ण;

काष्ठा ath10k_hw_ce_dst_src_wm_regs अणु
	u32 addr;
	u32 low_rst;
	u32 high_rst;
	काष्ठा ath10k_hw_ce_regs_addr_map *wm_low;
	काष्ठा ath10k_hw_ce_regs_addr_map *wm_high; पूर्ण;

काष्ठा ath10k_hw_ce_ctrl1_upd अणु
	u32 shअगरt;
	u32 mask;
	u32 enable;
पूर्ण;

काष्ठा ath10k_hw_ce_regs अणु
	u32 sr_base_addr_lo;
	u32 sr_base_addr_hi;
	u32 sr_size_addr;
	u32 dr_base_addr_lo;
	u32 dr_base_addr_hi;
	u32 dr_size_addr;
	u32 ce_cmd_addr;
	u32 misc_ie_addr;
	u32 sr_wr_index_addr;
	u32 dst_wr_index_addr;
	u32 current_srri_addr;
	u32 current_drri_addr;
	u32 ddr_addr_क्रम_rri_low;
	u32 ddr_addr_क्रम_rri_high;
	u32 ce_rri_low;
	u32 ce_rri_high;
	u32 host_ie_addr;
	काष्ठा ath10k_hw_ce_host_wm_regs *wm_regs;
	काष्ठा ath10k_hw_ce_misc_regs *misc_regs;
	काष्ठा ath10k_hw_ce_ctrl1 *ctrl1_regs;
	काष्ठा ath10k_hw_ce_cmd_halt *cmd_halt;
	काष्ठा ath10k_hw_ce_host_ie *host_ie;
	काष्ठा ath10k_hw_ce_dst_src_wm_regs *wm_srcr;
	काष्ठा ath10k_hw_ce_dst_src_wm_regs *wm_dstr;
	काष्ठा ath10k_hw_ce_ctrl1_upd *upd;
पूर्ण;

काष्ठा ath10k_hw_values अणु
	u32 rtc_state_val_on;
	u8 ce_count;
	u8 msi_assign_ce_max;
	u8 num_target_ce_config_wlan;
	u16 ce_desc_meta_data_mask;
	u8 ce_desc_meta_data_lsb;
	u32 rfसमाप्त_pin;
	u32 rfसमाप्त_cfg;
	bool rfसमाप्त_on_level;
पूर्ण;

बाह्य स्थिर काष्ठा ath10k_hw_values qca988x_values;
बाह्य स्थिर काष्ठा ath10k_hw_values qca6174_values;
बाह्य स्थिर काष्ठा ath10k_hw_values qca99x0_values;
बाह्य स्थिर काष्ठा ath10k_hw_values qca9888_values;
बाह्य स्थिर काष्ठा ath10k_hw_values qca4019_values;
बाह्य स्थिर काष्ठा ath10k_hw_values wcn3990_values;
बाह्य स्थिर काष्ठा ath10k_hw_ce_regs wcn3990_ce_regs;
बाह्य स्थिर काष्ठा ath10k_hw_ce_regs qcax_ce_regs;

व्योम ath10k_hw_fill_survey_समय(काष्ठा ath10k *ar, काष्ठा survey_info *survey,
				u32 cc, u32 rcc, u32 cc_prev, u32 rcc_prev);

पूर्णांक ath10k_hw_diag_fast_करोwnload(काष्ठा ath10k *ar,
				 u32 address,
				 स्थिर व्योम *buffer,
				 u32 length);

#घोषणा QCA_REV_988X(ar) ((ar)->hw_rev == ATH10K_HW_QCA988X)
#घोषणा QCA_REV_9887(ar) ((ar)->hw_rev == ATH10K_HW_QCA9887)
#घोषणा QCA_REV_6174(ar) ((ar)->hw_rev == ATH10K_HW_QCA6174)
#घोषणा QCA_REV_99X0(ar) ((ar)->hw_rev == ATH10K_HW_QCA99X0)
#घोषणा QCA_REV_9888(ar) ((ar)->hw_rev == ATH10K_HW_QCA9888)
#घोषणा QCA_REV_9984(ar) ((ar)->hw_rev == ATH10K_HW_QCA9984)
#घोषणा QCA_REV_9377(ar) ((ar)->hw_rev == ATH10K_HW_QCA9377)
#घोषणा QCA_REV_40XX(ar) ((ar)->hw_rev == ATH10K_HW_QCA4019)
#घोषणा QCA_REV_WCN3990(ar) ((ar)->hw_rev == ATH10K_HW_WCN3990)

/* Known peculiarities:
 *  - raw appears in nwअगरi decap, raw and nwअगरi appear in ethernet decap
 *  - raw have FCS, nwअगरi करोesn't
 *  - ethernet frames have 802.11 header decapped and parts (base hdr, cipher
 *    param, llc/snap) are aligned to 4byte boundaries each
 */
क्रमागत ath10k_hw_txrx_mode अणु
	ATH10K_HW_TXRX_RAW = 0,

	/* Native Wअगरi decap mode is used to align IP frames to 4-byte
	 * boundaries and aव्योम a very expensive re-alignment in mac80211.
	 */
	ATH10K_HW_TXRX_NATIVE_WIFI = 1,
	ATH10K_HW_TXRX_ETHERNET = 2,

	/* Valid क्रम HTT >= 3.0. Used क्रम management frames in TX_FRM. */
	ATH10K_HW_TXRX_MGMT = 3,
पूर्ण;

क्रमागत ath10k_mcast2ucast_mode अणु
	ATH10K_MCAST2UCAST_DISABLED = 0,
	ATH10K_MCAST2UCAST_ENABLED = 1,
पूर्ण;

क्रमागत ath10k_hw_rate_ofdm अणु
	ATH10K_HW_RATE_OFDM_48M = 0,
	ATH10K_HW_RATE_OFDM_24M,
	ATH10K_HW_RATE_OFDM_12M,
	ATH10K_HW_RATE_OFDM_6M,
	ATH10K_HW_RATE_OFDM_54M,
	ATH10K_HW_RATE_OFDM_36M,
	ATH10K_HW_RATE_OFDM_18M,
	ATH10K_HW_RATE_OFDM_9M,
पूर्ण;

क्रमागत ath10k_hw_rate_cck अणु
	ATH10K_HW_RATE_CCK_LP_11M = 0,
	ATH10K_HW_RATE_CCK_LP_5_5M,
	ATH10K_HW_RATE_CCK_LP_2M,
	ATH10K_HW_RATE_CCK_LP_1M,
	ATH10K_HW_RATE_CCK_SP_11M,
	ATH10K_HW_RATE_CCK_SP_5_5M,
	ATH10K_HW_RATE_CCK_SP_2M,
पूर्ण;

क्रमागत ath10k_hw_rate_rev2_cck अणु
	ATH10K_HW_RATE_REV2_CCK_LP_1M = 1,
	ATH10K_HW_RATE_REV2_CCK_LP_2M,
	ATH10K_HW_RATE_REV2_CCK_LP_5_5M,
	ATH10K_HW_RATE_REV2_CCK_LP_11M,
	ATH10K_HW_RATE_REV2_CCK_SP_2M,
	ATH10K_HW_RATE_REV2_CCK_SP_5_5M,
	ATH10K_HW_RATE_REV2_CCK_SP_11M,
पूर्ण;

क्रमागत ath10k_hw_cc_wraparound_type अणु
	ATH10K_HW_CC_WRAP_DISABLED = 0,

	/* This type is when the HW chip has a quirky Cycle Counter
	 * wraparound which resets to 0x7fffffff instead of 0. All
	 * other CC related counters (e.g. Rx Clear Count) are भागided
	 * by 2 so they never wraparound themselves.
	 */
	ATH10K_HW_CC_WRAP_SHIFTED_ALL = 1,

	/* Each hw counter wrapsaround independently. When the
	 * counter overflows the repestive counter is right shअगरted
	 * by 1, i.e reset to 0x7fffffff, and other counters will be
	 * running unaffected. In this type of wraparound, it should
	 * be possible to report accurate Rx busy समय unlike the
	 * first type.
	 */
	ATH10K_HW_CC_WRAP_SHIFTED_EACH = 2,
पूर्ण;

क्रमागत ath10k_hw_refclk_speed अणु
	ATH10K_HW_REFCLK_UNKNOWN = -1,
	ATH10K_HW_REFCLK_48_MHZ = 0,
	ATH10K_HW_REFCLK_19_2_MHZ = 1,
	ATH10K_HW_REFCLK_24_MHZ = 2,
	ATH10K_HW_REFCLK_26_MHZ = 3,
	ATH10K_HW_REFCLK_37_4_MHZ = 4,
	ATH10K_HW_REFCLK_38_4_MHZ = 5,
	ATH10K_HW_REFCLK_40_MHZ = 6,
	ATH10K_HW_REFCLK_52_MHZ = 7,

	/* must be the last one */
	ATH10K_HW_REFCLK_COUNT,
पूर्ण;

काष्ठा ath10k_hw_clk_params अणु
	u32 refclk;
	u32 भाग;
	u32 rnfrac;
	u32 settle_समय;
	u32 refभाग;
	u32 outभाग;
पूर्ण;

काष्ठा ath10k_hw_params अणु
	u32 id;
	u16 dev_id;
	क्रमागत ath10k_bus bus;
	स्थिर अक्षर *name;
	u32 patch_load_addr;
	पूर्णांक uart_pin;
	u32 otp_exe_param;

	/* Type of hw cycle counter wraparound logic, क्रम more info
	 * refer क्रमागत ath10k_hw_cc_wraparound_type.
	 */
	क्रमागत ath10k_hw_cc_wraparound_type cc_wraparound_type;

	/* Some of chip expects fragment descriptor to be continuous
	 * memory क्रम any TX operation. Set continuous_frag_desc flag
	 * क्रम the hardware which have such requirement.
	 */
	bool continuous_frag_desc;

	/* CCK hardware rate table mapping क्रम the newer chipsets
	 * like QCA99X0, QCA4019 got revised. The CCK h/w rate values
	 * are in a proper order with respect to the rate/preamble
	 */
	bool cck_rate_map_rev2;

	u32 channel_counters_freq_hz;

	/* Mgmt tx descriptors threshold क्रम limiting probe response
	 * frames.
	 */
	u32 max_probe_resp_desc_thres;

	u32 tx_chain_mask;
	u32 rx_chain_mask;
	u32 max_spatial_stream;
	u32 cal_data_len;

	काष्ठा ath10k_hw_params_fw अणु
		स्थिर अक्षर *dir;
		स्थिर अक्षर *board;
		माप_प्रकार board_size;
		स्थिर अक्षर *eboard;
		माप_प्रकार ext_board_size;
		माप_प्रकार board_ext_size;
	पूर्ण fw;

	/* qca99x0 family chips deliver broadcast/multicast management
	 * frames encrypted and expect software करो decryption.
	 */
	bool sw_decrypt_mcast_mgmt;

	स्थिर काष्ठा ath10k_hw_ops *hw_ops;

	/* Number of bytes used क्रम alignment in rx_hdr_status of rx desc. */
	पूर्णांक decap_align_bytes;

	/* hw specअगरic घड़ी control parameters */
	स्थिर काष्ठा ath10k_hw_clk_params *hw_clk;
	पूर्णांक target_cpu_freq;

	/* Number of bytes to be discarded क्रम each FFT sample */
	पूर्णांक spectral_bin_discard;

	/* The board may have a restricted NSS क्रम 160 or 80+80 vs what it
	 * can करो क्रम 80Mhz.
	 */
	पूर्णांक vht160_mcs_rx_highest;
	पूर्णांक vht160_mcs_tx_highest;

	/* Number of ciphers supported (i.e First N) in cipher_suites array */
	पूर्णांक n_cipher_suites;

	u32 num_peers;
	u32 ast_skid_limit;
	u32 num_wds_entries;

	/* Tarमाला_लो supporting physical addressing capability above 32-bits */
	bool target_64bit;

	/* Target rx ring fill level */
	u32 rx_ring_fill_level;

	/* target supporting shaकरोw रेजिस्टर क्रम ce ग_लिखो */
	bool shaकरोw_reg_support;

	/* target supporting retention restore on ddr */
	bool rri_on_ddr;

	/* Number of bytes to be the offset क्रम each FFT sample */
	पूर्णांक spectral_bin_offset;

	/* tarमाला_लो which require hw filter reset during boot up,
	 * to aव्योम it sending spurious acks.
	 */
	bool hw_filter_reset_required;

	/* target supporting fw करोwnload via diag ce */
	bool fw_diag_ce_करोwnload;

	/* target supporting fw करोwnload via large size BMI */
	bool bmi_large_size_करोwnload;

	/* need to set uart pin अगर disable uart prपूर्णांक, workaround क्रम a
	 * firmware bug
	 */
	bool uart_pin_workaround;

	/* tx stats support over pktlog */
	bool tx_stats_over_pktlog;

	/* provides bitrates क्रम sta_statistics using WMI_TLV_PEER_STATS_INFO_EVENTID */
	bool supports_peer_stats_info;

	bool dynamic_sar_support;
पूर्ण;

काष्ठा htt_rx_desc;
काष्ठा htt_resp;
काष्ठा htt_data_tx_completion_ext;

/* Defines needed क्रम Rx descriptor असलtraction */
काष्ठा ath10k_hw_ops अणु
	पूर्णांक (*rx_desc_get_l3_pad_bytes)(काष्ठा htt_rx_desc *rxd);
	व्योम (*set_coverage_class)(काष्ठा ath10k *ar, s16 value);
	पूर्णांक (*enable_pll_clk)(काष्ठा ath10k *ar);
	bool (*rx_desc_get_msdu_limit_error)(काष्ठा htt_rx_desc *rxd);
	पूर्णांक (*tx_data_rssi_pad_bytes)(काष्ठा htt_resp *htt);
	पूर्णांक (*is_rssi_enable)(काष्ठा htt_resp *resp);
पूर्ण;

बाह्य स्थिर काष्ठा ath10k_hw_ops qca988x_ops;
बाह्य स्थिर काष्ठा ath10k_hw_ops qca99x0_ops;
बाह्य स्थिर काष्ठा ath10k_hw_ops qca6174_ops;
बाह्य स्थिर काष्ठा ath10k_hw_ops qca6174_sdio_ops;
बाह्य स्थिर काष्ठा ath10k_hw_ops wcn3990_ops;

बाह्य स्थिर काष्ठा ath10k_hw_clk_params qca6174_clk[];

अटल अंतरभूत पूर्णांक
ath10k_rx_desc_get_l3_pad_bytes(काष्ठा ath10k_hw_params *hw,
				काष्ठा htt_rx_desc *rxd)
अणु
	अगर (hw->hw_ops->rx_desc_get_l3_pad_bytes)
		वापस hw->hw_ops->rx_desc_get_l3_pad_bytes(rxd);
	वापस 0;
पूर्ण

अटल अंतरभूत bool
ath10k_rx_desc_msdu_limit_error(काष्ठा ath10k_hw_params *hw,
				काष्ठा htt_rx_desc *rxd)
अणु
	अगर (hw->hw_ops->rx_desc_get_msdu_limit_error)
		वापस hw->hw_ops->rx_desc_get_msdu_limit_error(rxd);
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_tx_data_rssi_get_pad_bytes(काष्ठा ath10k_hw_params *hw,
				  काष्ठा htt_resp *htt)
अणु
	अगर (hw->hw_ops->tx_data_rssi_pad_bytes)
		वापस hw->hw_ops->tx_data_rssi_pad_bytes(htt);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_is_rssi_enable(काष्ठा ath10k_hw_params *hw,
		      काष्ठा htt_resp *resp)
अणु
	अगर (hw->hw_ops->is_rssi_enable)
		वापस hw->hw_ops->is_rssi_enable(resp);
	वापस 0;
पूर्ण

/* Target specअगरic defines क्रम MAIN firmware */
#घोषणा TARGET_NUM_VDEVS			8
#घोषणा TARGET_NUM_PEER_AST			2
#घोषणा TARGET_NUM_WDS_ENTRIES			32
#घोषणा TARGET_DMA_BURST_SIZE			0
#घोषणा TARGET_MAC_AGGR_DELIM			0
#घोषणा TARGET_AST_SKID_LIMIT			16
#घोषणा TARGET_NUM_STATIONS			16
#घोषणा TARGET_NUM_PEERS			((TARGET_NUM_STATIONS) + \
						 (TARGET_NUM_VDEVS))
#घोषणा TARGET_NUM_OFFLOAD_PEERS		0
#घोषणा TARGET_NUM_OFFLOAD_REORDER_BUFS         0
#घोषणा TARGET_NUM_PEER_KEYS			2
#घोषणा TARGET_NUM_TIDS				((TARGET_NUM_PEERS) * 2)
#घोषणा TARGET_TX_CHAIN_MASK			(BIT(0) | BIT(1) | BIT(2))
#घोषणा TARGET_RX_CHAIN_MASK			(BIT(0) | BIT(1) | BIT(2))
#घोषणा TARGET_RX_TIMEOUT_LO_PRI		100
#घोषणा TARGET_RX_TIMEOUT_HI_PRI		40

#घोषणा TARGET_SCAN_MAX_PENDING_REQS		4
#घोषणा TARGET_BMISS_OFFLOAD_MAX_VDEV		3
#घोषणा TARGET_ROAM_OFFLOAD_MAX_VDEV		3
#घोषणा TARGET_ROAM_OFFLOAD_MAX_AP_PROखाताS	8
#घोषणा TARGET_GTK_OFFLOAD_MAX_VDEV		3
#घोषणा TARGET_NUM_MCAST_GROUPS			0
#घोषणा TARGET_NUM_MCAST_TABLE_ELEMS		0
#घोषणा TARGET_MCAST2UCAST_MODE			ATH10K_MCAST2UCAST_DISABLED
#घोषणा TARGET_TX_DBG_LOG_SIZE			1024
#घोषणा TARGET_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK 0
#घोषणा TARGET_VOW_CONFIG			0
#घोषणा TARGET_NUM_MSDU_DESC			(1024 + 400)
#घोषणा TARGET_MAX_FRAG_ENTRIES			0

/* Target specअगरic defines क्रम 10.X firmware */
#घोषणा TARGET_10X_NUM_VDEVS			16
#घोषणा TARGET_10X_NUM_PEER_AST			2
#घोषणा TARGET_10X_NUM_WDS_ENTRIES		32
#घोषणा TARGET_10X_DMA_BURST_SIZE		0
#घोषणा TARGET_10X_MAC_AGGR_DELIM		0
#घोषणा TARGET_10X_AST_SKID_LIMIT		128
#घोषणा TARGET_10X_NUM_STATIONS			128
#घोषणा TARGET_10X_TX_STATS_NUM_STATIONS	118
#घोषणा TARGET_10X_NUM_PEERS			((TARGET_10X_NUM_STATIONS) + \
						 (TARGET_10X_NUM_VDEVS))
#घोषणा TARGET_10X_TX_STATS_NUM_PEERS		((TARGET_10X_TX_STATS_NUM_STATIONS) + \
						 (TARGET_10X_NUM_VDEVS))
#घोषणा TARGET_10X_NUM_OFFLOAD_PEERS		0
#घोषणा TARGET_10X_NUM_OFFLOAD_REORDER_BUFS	0
#घोषणा TARGET_10X_NUM_PEER_KEYS		2
#घोषणा TARGET_10X_NUM_TIDS_MAX			256
#घोषणा TARGET_10X_NUM_TIDS			min((TARGET_10X_NUM_TIDS_MAX), \
						    (TARGET_10X_NUM_PEERS) * 2)
#घोषणा TARGET_10X_TX_STATS_NUM_TIDS		min((TARGET_10X_NUM_TIDS_MAX), \
						    (TARGET_10X_TX_STATS_NUM_PEERS) * 2)
#घोषणा TARGET_10X_TX_CHAIN_MASK		(BIT(0) | BIT(1) | BIT(2))
#घोषणा TARGET_10X_RX_CHAIN_MASK		(BIT(0) | BIT(1) | BIT(2))
#घोषणा TARGET_10X_RX_TIMEOUT_LO_PRI		100
#घोषणा TARGET_10X_RX_TIMEOUT_HI_PRI		40
#घोषणा TARGET_10X_SCAN_MAX_PENDING_REQS	4
#घोषणा TARGET_10X_BMISS_OFFLOAD_MAX_VDEV	2
#घोषणा TARGET_10X_ROAM_OFFLOAD_MAX_VDEV	2
#घोषणा TARGET_10X_ROAM_OFFLOAD_MAX_AP_PROखाताS	8
#घोषणा TARGET_10X_GTK_OFFLOAD_MAX_VDEV		3
#घोषणा TARGET_10X_NUM_MCAST_GROUPS		0
#घोषणा TARGET_10X_NUM_MCAST_TABLE_ELEMS	0
#घोषणा TARGET_10X_MCAST2UCAST_MODE		ATH10K_MCAST2UCAST_DISABLED
#घोषणा TARGET_10X_TX_DBG_LOG_SIZE		1024
#घोषणा TARGET_10X_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK 1
#घोषणा TARGET_10X_VOW_CONFIG			0
#घोषणा TARGET_10X_NUM_MSDU_DESC		(1024 + 400)
#घोषणा TARGET_10X_MAX_FRAG_ENTRIES		0

/* 10.2 parameters */
#घोषणा TARGET_10_2_DMA_BURST_SIZE		0

/* Target specअगरic defines क्रम WMI-TLV firmware */
#घोषणा TARGET_TLV_NUM_VDEVS			4
#घोषणा TARGET_TLV_NUM_STATIONS			32
#घोषणा TARGET_TLV_NUM_PEERS			33
#घोषणा TARGET_TLV_NUM_TDLS_VDEVS		1
#घोषणा TARGET_TLV_NUM_TIDS			((TARGET_TLV_NUM_PEERS) * 2)
#घोषणा TARGET_TLV_NUM_MSDU_DESC		(1024 + 32)
#घोषणा TARGET_TLV_NUM_MSDU_DESC_HL		1024
#घोषणा TARGET_TLV_NUM_WOW_PATTERNS		22
#घोषणा TARGET_TLV_MGMT_NUM_MSDU_DESC		(50)

/* Target specअगरic defines क्रम WMI-HL-1.0 firmware */
#घोषणा TARGET_HL_TLV_NUM_PEERS			33
#घोषणा TARGET_HL_TLV_AST_SKID_LIMIT		16
#घोषणा TARGET_HL_TLV_NUM_WDS_ENTRIES		2

/* Target specअगरic defines क्रम QCA9377 high latency firmware */
#घोषणा TARGET_QCA9377_HL_NUM_PEERS		15

/* Diagnostic Winकरोw */
#घोषणा CE_DIAG_PIPE	7

#घोषणा NUM_TARGET_CE_CONFIG_WLAN ar->hw_values->num_target_ce_config_wlan

/* Target specअगरic defines क्रम 10.4 firmware */
#घोषणा TARGET_10_4_NUM_VDEVS			16
#घोषणा TARGET_10_4_NUM_STATIONS		32
#घोषणा TARGET_10_4_NUM_PEERS			((TARGET_10_4_NUM_STATIONS) + \
						 (TARGET_10_4_NUM_VDEVS))
#घोषणा TARGET_10_4_ACTIVE_PEERS		0

#घोषणा TARGET_10_4_NUM_QCACHE_PEERS_MAX	512
#घोषणा TARGET_10_4_QCACHE_ACTIVE_PEERS		50
#घोषणा TARGET_10_4_QCACHE_ACTIVE_PEERS_PFC	35
#घोषणा TARGET_10_4_NUM_OFFLOAD_PEERS		0
#घोषणा TARGET_10_4_NUM_OFFLOAD_REORDER_BUFFS	0
#घोषणा TARGET_10_4_NUM_PEER_KEYS		2
#घोषणा TARGET_10_4_TGT_NUM_TIDS		((TARGET_10_4_NUM_PEERS) * 2)
#घोषणा TARGET_10_4_NUM_MSDU_DESC		(1024 + 400)
#घोषणा TARGET_10_4_NUM_MSDU_DESC_PFC		2500
#घोषणा TARGET_10_4_AST_SKID_LIMIT		32

/* 100 ms क्रम video, best-efक्रमt, and background */
#घोषणा TARGET_10_4_RX_TIMEOUT_LO_PRI		100

/* 40 ms क्रम voice */
#घोषणा TARGET_10_4_RX_TIMEOUT_HI_PRI		40

#घोषणा TARGET_10_4_RX_DECAP_MODE		ATH10K_HW_TXRX_NATIVE_WIFI
#घोषणा TARGET_10_4_SCAN_MAX_REQS		4
#घोषणा TARGET_10_4_BMISS_OFFLOAD_MAX_VDEV	3
#घोषणा TARGET_10_4_ROAM_OFFLOAD_MAX_VDEV	3
#घोषणा TARGET_10_4_ROAM_OFFLOAD_MAX_PROखाताS   8

/* Note: mcast to ucast is disabled by शेष */
#घोषणा TARGET_10_4_NUM_MCAST_GROUPS		0
#घोषणा TARGET_10_4_NUM_MCAST_TABLE_ELEMS	0
#घोषणा TARGET_10_4_MCAST2UCAST_MODE		0

#घोषणा TARGET_10_4_TX_DBG_LOG_SIZE		1024
#घोषणा TARGET_10_4_NUM_WDS_ENTRIES		32
#घोषणा TARGET_10_4_DMA_BURST_SIZE		1
#घोषणा TARGET_10_4_MAC_AGGR_DELIM		0
#घोषणा TARGET_10_4_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK 1
#घोषणा TARGET_10_4_VOW_CONFIG			0
#घोषणा TARGET_10_4_GTK_OFFLOAD_MAX_VDEV	3
#घोषणा TARGET_10_4_11AC_TX_MAX_FRAGS		2
#घोषणा TARGET_10_4_MAX_PEER_EXT_STATS		16
#घोषणा TARGET_10_4_SMART_ANT_CAP		0
#घोषणा TARGET_10_4_BK_MIN_FREE			0
#घोषणा TARGET_10_4_BE_MIN_FREE			0
#घोषणा TARGET_10_4_VI_MIN_FREE			0
#घोषणा TARGET_10_4_VO_MIN_FREE			0
#घोषणा TARGET_10_4_RX_BATCH_MODE		1
#घोषणा TARGET_10_4_THERMAL_THROTTLING_CONFIG	0
#घोषणा TARGET_10_4_ATF_CONFIG			0
#घोषणा TARGET_10_4_IPHDR_PAD_CONFIG		1
#घोषणा TARGET_10_4_QWRAP_CONFIG		0

/* TDLS config */
#घोषणा TARGET_10_4_NUM_TDLS_VDEVS		1
#घोषणा TARGET_10_4_NUM_TDLS_BUFFER_STA		1
#घोषणा TARGET_10_4_NUM_TDLS_SLEEP_STA		1

/* Maximum number of Copy Engine's supported */
#घोषणा CE_COUNT_MAX 12

/* Number of Copy Engines supported */
#घोषणा CE_COUNT ar->hw_values->ce_count

/*
 * Granted MSIs are asचिन्हित as follows:
 * Firmware uses the first
 * Reमुख्यing MSIs, अगर any, are used by Copy Engines
 * This mapping is known to both Target firmware and Host software.
 * It may be changed as दीर्घ as Host and Target are kept in sync.
 */
/* MSI क्रम firmware (errors, etc.) */
#घोषणा MSI_ASSIGN_FW		0

/* MSIs क्रम Copy Engines */
#घोषणा MSI_ASSIGN_CE_INITIAL	1
#घोषणा MSI_ASSIGN_CE_MAX	ar->hw_values->msi_assign_ce_max

/* as of IP3.7.1 */
#घोषणा RTC_STATE_V_ON				ar->hw_values->rtc_state_val_on

#घोषणा RTC_STATE_V_LSB				0
#घोषणा RTC_STATE_V_MASK			0x00000007
#घोषणा RTC_STATE_ADDRESS			0x0000
#घोषणा PCIE_SOC_WAKE_V_MASK			0x00000001
#घोषणा PCIE_SOC_WAKE_ADDRESS			0x0004
#घोषणा PCIE_SOC_WAKE_RESET			0x00000000
#घोषणा SOC_GLOBAL_RESET_ADDRESS		0x0008

#घोषणा RTC_SOC_BASE_ADDRESS			ar->regs->rtc_soc_base_address
#घोषणा RTC_WMAC_BASE_ADDRESS			ar->regs->rtc_wmac_base_address
#घोषणा MAC_COEX_BASE_ADDRESS			0x00006000
#घोषणा BT_COEX_BASE_ADDRESS			0x00007000
#घोषणा SOC_PCIE_BASE_ADDRESS			0x00008000
#घोषणा SOC_CORE_BASE_ADDRESS			ar->regs->soc_core_base_address
#घोषणा WLAN_UART_BASE_ADDRESS			0x0000c000
#घोषणा WLAN_SI_BASE_ADDRESS			0x00010000
#घोषणा WLAN_GPIO_BASE_ADDRESS			0x00014000
#घोषणा WLAN_ANALOG_INTF_BASE_ADDRESS		0x0001c000
#घोषणा WLAN_MAC_BASE_ADDRESS			ar->regs->wlan_mac_base_address
#घोषणा EFUSE_BASE_ADDRESS			0x00030000
#घोषणा FPGA_REG_BASE_ADDRESS			0x00039000
#घोषणा WLAN_UART2_BASE_ADDRESS			0x00054c00
#घोषणा CE_WRAPPER_BASE_ADDRESS			ar->regs->ce_wrapper_base_address
#घोषणा CE0_BASE_ADDRESS			ar->regs->ce0_base_address
#घोषणा CE1_BASE_ADDRESS			ar->regs->ce1_base_address
#घोषणा CE2_BASE_ADDRESS			ar->regs->ce2_base_address
#घोषणा CE3_BASE_ADDRESS			ar->regs->ce3_base_address
#घोषणा CE4_BASE_ADDRESS			ar->regs->ce4_base_address
#घोषणा CE5_BASE_ADDRESS			ar->regs->ce5_base_address
#घोषणा CE6_BASE_ADDRESS			ar->regs->ce6_base_address
#घोषणा CE7_BASE_ADDRESS			ar->regs->ce7_base_address
#घोषणा DBI_BASE_ADDRESS			0x00060000
#घोषणा WLAN_ANALOG_INTF_PCIE_BASE_ADDRESS	0x0006c000
#घोषणा PCIE_LOCAL_BASE_ADDRESS		ar->regs->pcie_local_base_address

#घोषणा SOC_RESET_CONTROL_ADDRESS		0x00000000
#घोषणा SOC_RESET_CONTROL_OFFSET		0x00000000
#घोषणा SOC_RESET_CONTROL_SI0_RST_MASK		ar->regs->soc_reset_control_si0_rst_mask
#घोषणा SOC_RESET_CONTROL_CE_RST_MASK		ar->regs->soc_reset_control_ce_rst_mask
#घोषणा SOC_RESET_CONTROL_CPU_WARM_RST_MASK	0x00000040
#घोषणा SOC_CPU_CLOCK_OFFSET			0x00000020
#घोषणा SOC_CPU_CLOCK_STANDARD_LSB		0
#घोषणा SOC_CPU_CLOCK_STANDARD_MASK		0x00000003
#घोषणा SOC_CLOCK_CONTROL_OFFSET		0x00000028
#घोषणा SOC_CLOCK_CONTROL_SI0_CLK_MASK		0x00000001
#घोषणा SOC_SYSTEM_SLEEP_OFFSET			0x000000c4
#घोषणा SOC_LPO_CAL_OFFSET			0x000000e0
#घोषणा SOC_LPO_CAL_ENABLE_LSB			20
#घोषणा SOC_LPO_CAL_ENABLE_MASK			0x00100000
#घोषणा SOC_LF_TIMER_CONTROL0_ADDRESS		0x00000050
#घोषणा SOC_LF_TIMER_CONTROL0_ENABLE_MASK	0x00000004

#घोषणा SOC_CHIP_ID_ADDRESS			ar->regs->soc_chip_id_address
#घोषणा SOC_CHIP_ID_REV_LSB			8
#घोषणा SOC_CHIP_ID_REV_MASK			0x00000f00

#घोषणा WLAN_RESET_CONTROL_COLD_RST_MASK	0x00000008
#घोषणा WLAN_RESET_CONTROL_WARM_RST_MASK	0x00000004
#घोषणा WLAN_SYSTEM_SLEEP_DISABLE_LSB		0
#घोषणा WLAN_SYSTEM_SLEEP_DISABLE_MASK		0x00000001

#घोषणा WLAN_GPIO_PIN0_ADDRESS			0x00000028
#घोषणा WLAN_GPIO_PIN0_CONFIG_LSB		11
#घोषणा WLAN_GPIO_PIN0_CONFIG_MASK		0x00007800
#घोषणा WLAN_GPIO_PIN0_PAD_PULL_LSB		5
#घोषणा WLAN_GPIO_PIN0_PAD_PULL_MASK		0x00000060
#घोषणा WLAN_GPIO_PIN1_ADDRESS			0x0000002c
#घोषणा WLAN_GPIO_PIN1_CONFIG_MASK		0x00007800
#घोषणा WLAN_GPIO_PIN10_ADDRESS			0x00000050
#घोषणा WLAN_GPIO_PIN11_ADDRESS			0x00000054
#घोषणा WLAN_GPIO_PIN12_ADDRESS			0x00000058
#घोषणा WLAN_GPIO_PIN13_ADDRESS			0x0000005c

#घोषणा CLOCK_GPIO_OFFSET			0xffffffff
#घोषणा CLOCK_GPIO_BT_CLK_OUT_EN_LSB		0
#घोषणा CLOCK_GPIO_BT_CLK_OUT_EN_MASK		0

#घोषणा SI_CONFIG_OFFSET			0x00000000
#घोषणा SI_CONFIG_ERR_INT_LSB			19
#घोषणा SI_CONFIG_ERR_INT_MASK			0x00080000
#घोषणा SI_CONFIG_BIसूची_OD_DATA_LSB		18
#घोषणा SI_CONFIG_BIसूची_OD_DATA_MASK		0x00040000
#घोषणा SI_CONFIG_I2C_LSB			16
#घोषणा SI_CONFIG_I2C_MASK			0x00010000
#घोषणा SI_CONFIG_POS_SAMPLE_LSB		7
#घोषणा SI_CONFIG_POS_SAMPLE_MASK		0x00000080
#घोषणा SI_CONFIG_INACTIVE_DATA_LSB		5
#घोषणा SI_CONFIG_INACTIVE_DATA_MASK		0x00000020
#घोषणा SI_CONFIG_INACTIVE_CLK_LSB		4
#घोषणा SI_CONFIG_INACTIVE_CLK_MASK		0x00000010
#घोषणा SI_CONFIG_DIVIDER_LSB			0
#घोषणा SI_CONFIG_DIVIDER_MASK			0x0000000f
#घोषणा SI_CS_OFFSET				0x00000004
#घोषणा SI_CS_DONE_ERR_LSB			10
#घोषणा SI_CS_DONE_ERR_MASK			0x00000400
#घोषणा SI_CS_DONE_INT_LSB			9
#घोषणा SI_CS_DONE_INT_MASK			0x00000200
#घोषणा SI_CS_START_LSB				8
#घोषणा SI_CS_START_MASK			0x00000100
#घोषणा SI_CS_RX_CNT_LSB			4
#घोषणा SI_CS_RX_CNT_MASK			0x000000f0
#घोषणा SI_CS_TX_CNT_LSB			0
#घोषणा SI_CS_TX_CNT_MASK			0x0000000f

#घोषणा SI_TX_DATA0_OFFSET			0x00000008
#घोषणा SI_TX_DATA1_OFFSET			0x0000000c
#घोषणा SI_RX_DATA0_OFFSET			0x00000010
#घोषणा SI_RX_DATA1_OFFSET			0x00000014

#घोषणा CORE_CTRL_CPU_INTR_MASK			0x00002000
#घोषणा CORE_CTRL_PCIE_REG_31_MASK		0x00000800
#घोषणा CORE_CTRL_ADDRESS			0x0000
#घोषणा PCIE_INTR_ENABLE_ADDRESS		0x0008
#घोषणा PCIE_INTR_CAUSE_ADDRESS			0x000c
#घोषणा PCIE_INTR_CLR_ADDRESS			ar->regs->pcie_पूर्णांकr_clr_address
#घोषणा SCRATCH_3_ADDRESS			ar->regs->scratch_3_address
#घोषणा CPU_INTR_ADDRESS			0x0010
#घोषणा FW_RAM_CONFIG_ADDRESS			0x0018

#घोषणा CCNT_TO_MSEC(ar, x) ((x) / ar->hw_params.channel_counters_freq_hz)

/* Firmware indications to the Host via SCRATCH_3 रेजिस्टर. */
#घोषणा FW_INDICATOR_ADDRESS			ar->regs->fw_indicator_address
#घोषणा FW_IND_EVENT_PENDING			1
#घोषणा FW_IND_INITIALIZED			2
#घोषणा FW_IND_HOST_READY			0x80000000

/* HOST_REG पूर्णांकerrupt from firmware */
#घोषणा PCIE_INTR_FIRMWARE_MASK			ar->regs->pcie_पूर्णांकr_fw_mask
#घोषणा PCIE_INTR_CE_MASK_ALL			ar->regs->pcie_पूर्णांकr_ce_mask_all

#घोषणा DRAM_BASE_ADDRESS			0x00400000

#घोषणा PCIE_BAR_REG_ADDRESS			0x40030

#घोषणा MISSING 0

#घोषणा SYSTEM_SLEEP_OFFSET			SOC_SYSTEM_SLEEP_OFFSET
#घोषणा WLAN_SYSTEM_SLEEP_OFFSET		SOC_SYSTEM_SLEEP_OFFSET
#घोषणा WLAN_RESET_CONTROL_OFFSET		SOC_RESET_CONTROL_OFFSET
#घोषणा CLOCK_CONTROL_OFFSET			SOC_CLOCK_CONTROL_OFFSET
#घोषणा CLOCK_CONTROL_SI0_CLK_MASK		SOC_CLOCK_CONTROL_SI0_CLK_MASK
#घोषणा RESET_CONTROL_MBOX_RST_MASK		MISSING
#घोषणा RESET_CONTROL_SI0_RST_MASK		SOC_RESET_CONTROL_SI0_RST_MASK
#घोषणा GPIO_BASE_ADDRESS			WLAN_GPIO_BASE_ADDRESS
#घोषणा GPIO_PIN0_OFFSET			WLAN_GPIO_PIN0_ADDRESS
#घोषणा GPIO_PIN1_OFFSET			WLAN_GPIO_PIN1_ADDRESS
#घोषणा GPIO_PIN0_CONFIG_LSB			WLAN_GPIO_PIN0_CONFIG_LSB
#घोषणा GPIO_PIN0_CONFIG_MASK			WLAN_GPIO_PIN0_CONFIG_MASK
#घोषणा GPIO_PIN0_PAD_PULL_LSB			WLAN_GPIO_PIN0_PAD_PULL_LSB
#घोषणा GPIO_PIN0_PAD_PULL_MASK			WLAN_GPIO_PIN0_PAD_PULL_MASK
#घोषणा GPIO_PIN1_CONFIG_MASK			WLAN_GPIO_PIN1_CONFIG_MASK
#घोषणा SI_BASE_ADDRESS				WLAN_SI_BASE_ADDRESS
#घोषणा SCRATCH_BASE_ADDRESS			SOC_CORE_BASE_ADDRESS
#घोषणा LOCAL_SCRATCH_OFFSET			0x18
#घोषणा CPU_CLOCK_OFFSET			SOC_CPU_CLOCK_OFFSET
#घोषणा LPO_CAL_OFFSET				SOC_LPO_CAL_OFFSET
#घोषणा GPIO_PIN10_OFFSET			WLAN_GPIO_PIN10_ADDRESS
#घोषणा GPIO_PIN11_OFFSET			WLAN_GPIO_PIN11_ADDRESS
#घोषणा GPIO_PIN12_OFFSET			WLAN_GPIO_PIN12_ADDRESS
#घोषणा GPIO_PIN13_OFFSET			WLAN_GPIO_PIN13_ADDRESS
#घोषणा CPU_CLOCK_STANDARD_LSB			SOC_CPU_CLOCK_STANDARD_LSB
#घोषणा CPU_CLOCK_STANDARD_MASK			SOC_CPU_CLOCK_STANDARD_MASK
#घोषणा LPO_CAL_ENABLE_LSB			SOC_LPO_CAL_ENABLE_LSB
#घोषणा LPO_CAL_ENABLE_MASK			SOC_LPO_CAL_ENABLE_MASK
#घोषणा ANALOG_INTF_BASE_ADDRESS		WLAN_ANALOG_INTF_BASE_ADDRESS
#घोषणा MBOX_BASE_ADDRESS			MISSING
#घोषणा INT_STATUS_ENABLE_ERROR_LSB		MISSING
#घोषणा INT_STATUS_ENABLE_ERROR_MASK		MISSING
#घोषणा INT_STATUS_ENABLE_CPU_LSB		MISSING
#घोषणा INT_STATUS_ENABLE_CPU_MASK		MISSING
#घोषणा INT_STATUS_ENABLE_COUNTER_LSB		MISSING
#घोषणा INT_STATUS_ENABLE_COUNTER_MASK		MISSING
#घोषणा INT_STATUS_ENABLE_MBOX_DATA_LSB		MISSING
#घोषणा INT_STATUS_ENABLE_MBOX_DATA_MASK	MISSING
#घोषणा ERROR_STATUS_ENABLE_RX_UNDERFLOW_LSB	MISSING
#घोषणा ERROR_STATUS_ENABLE_RX_UNDERFLOW_MASK	MISSING
#घोषणा ERROR_STATUS_ENABLE_TX_OVERFLOW_LSB	MISSING
#घोषणा ERROR_STATUS_ENABLE_TX_OVERFLOW_MASK	MISSING
#घोषणा COUNTER_INT_STATUS_ENABLE_BIT_LSB	MISSING
#घोषणा COUNTER_INT_STATUS_ENABLE_BIT_MASK	MISSING
#घोषणा INT_STATUS_ENABLE_ADDRESS		MISSING
#घोषणा CPU_INT_STATUS_ENABLE_BIT_LSB		MISSING
#घोषणा CPU_INT_STATUS_ENABLE_BIT_MASK		MISSING
#घोषणा HOST_INT_STATUS_ADDRESS			MISSING
#घोषणा CPU_INT_STATUS_ADDRESS			MISSING
#घोषणा ERROR_INT_STATUS_ADDRESS		MISSING
#घोषणा ERROR_INT_STATUS_WAKEUP_MASK		MISSING
#घोषणा ERROR_INT_STATUS_WAKEUP_LSB		MISSING
#घोषणा ERROR_INT_STATUS_RX_UNDERFLOW_MASK	MISSING
#घोषणा ERROR_INT_STATUS_RX_UNDERFLOW_LSB	MISSING
#घोषणा ERROR_INT_STATUS_TX_OVERFLOW_MASK	MISSING
#घोषणा ERROR_INT_STATUS_TX_OVERFLOW_LSB	MISSING
#घोषणा COUNT_DEC_ADDRESS			MISSING
#घोषणा HOST_INT_STATUS_CPU_MASK		MISSING
#घोषणा HOST_INT_STATUS_CPU_LSB			MISSING
#घोषणा HOST_INT_STATUS_ERROR_MASK		MISSING
#घोषणा HOST_INT_STATUS_ERROR_LSB		MISSING
#घोषणा HOST_INT_STATUS_COUNTER_MASK		MISSING
#घोषणा HOST_INT_STATUS_COUNTER_LSB		MISSING
#घोषणा RX_LOOKAHEAD_VALID_ADDRESS		MISSING
#घोषणा WINDOW_DATA_ADDRESS			MISSING
#घोषणा WINDOW_READ_ADDR_ADDRESS		MISSING
#घोषणा WINDOW_WRITE_ADDR_ADDRESS		MISSING

#घोषणा QCA9887_1_0_I2C_SDA_GPIO_PIN		5
#घोषणा QCA9887_1_0_I2C_SDA_PIN_CONFIG		3
#घोषणा QCA9887_1_0_SI_CLK_GPIO_PIN		17
#घोषणा QCA9887_1_0_SI_CLK_PIN_CONFIG		3
#घोषणा QCA9887_1_0_GPIO_ENABLE_W1TS_LOW_ADDRESS 0x00000010

#घोषणा QCA9887_EEPROM_SELECT_READ		0xa10000a0
#घोषणा QCA9887_EEPROM_ADDR_HI_MASK		0x0000ff00
#घोषणा QCA9887_EEPROM_ADDR_HI_LSB		8
#घोषणा QCA9887_EEPROM_ADDR_LO_MASK		0x00ff0000
#घोषणा QCA9887_EEPROM_ADDR_LO_LSB		16

#घोषणा MBOX_RESET_CONTROL_ADDRESS		0x00000000
#घोषणा MBOX_HOST_INT_STATUS_ADDRESS		0x00000800
#घोषणा MBOX_HOST_INT_STATUS_ERROR_LSB		7
#घोषणा MBOX_HOST_INT_STATUS_ERROR_MASK		0x00000080
#घोषणा MBOX_HOST_INT_STATUS_CPU_LSB		6
#घोषणा MBOX_HOST_INT_STATUS_CPU_MASK		0x00000040
#घोषणा MBOX_HOST_INT_STATUS_COUNTER_LSB	4
#घोषणा MBOX_HOST_INT_STATUS_COUNTER_MASK	0x00000010
#घोषणा MBOX_CPU_INT_STATUS_ADDRESS		0x00000801
#घोषणा MBOX_ERROR_INT_STATUS_ADDRESS		0x00000802
#घोषणा MBOX_ERROR_INT_STATUS_WAKEUP_LSB	2
#घोषणा MBOX_ERROR_INT_STATUS_WAKEUP_MASK	0x00000004
#घोषणा MBOX_ERROR_INT_STATUS_RX_UNDERFLOW_LSB	1
#घोषणा MBOX_ERROR_INT_STATUS_RX_UNDERFLOW_MASK	0x00000002
#घोषणा MBOX_ERROR_INT_STATUS_TX_OVERFLOW_LSB	0
#घोषणा MBOX_ERROR_INT_STATUS_TX_OVERFLOW_MASK	0x00000001
#घोषणा MBOX_COUNTER_INT_STATUS_ADDRESS		0x00000803
#घोषणा MBOX_COUNTER_INT_STATUS_COUNTER_LSB	0
#घोषणा MBOX_COUNTER_INT_STATUS_COUNTER_MASK	0x000000ff
#घोषणा MBOX_RX_LOOKAHEAD_VALID_ADDRESS		0x00000805
#घोषणा MBOX_INT_STATUS_ENABLE_ADDRESS		0x00000828
#घोषणा MBOX_INT_STATUS_ENABLE_ERROR_LSB	7
#घोषणा MBOX_INT_STATUS_ENABLE_ERROR_MASK	0x00000080
#घोषणा MBOX_INT_STATUS_ENABLE_CPU_LSB		6
#घोषणा MBOX_INT_STATUS_ENABLE_CPU_MASK		0x00000040
#घोषणा MBOX_INT_STATUS_ENABLE_INT_LSB		5
#घोषणा MBOX_INT_STATUS_ENABLE_INT_MASK		0x00000020
#घोषणा MBOX_INT_STATUS_ENABLE_COUNTER_LSB	4
#घोषणा MBOX_INT_STATUS_ENABLE_COUNTER_MASK	0x00000010
#घोषणा MBOX_INT_STATUS_ENABLE_MBOX_DATA_LSB	0
#घोषणा MBOX_INT_STATUS_ENABLE_MBOX_DATA_MASK	0x0000000f
#घोषणा MBOX_CPU_INT_STATUS_ENABLE_ADDRESS	0x00000819
#घोषणा MBOX_CPU_INT_STATUS_ENABLE_BIT_LSB	0
#घोषणा MBOX_CPU_INT_STATUS_ENABLE_BIT_MASK	0x000000ff
#घोषणा MBOX_CPU_STATUS_ENABLE_ASSERT_MASK 0x00000001
#घोषणा MBOX_ERROR_STATUS_ENABLE_ADDRESS	0x0000081a
#घोषणा MBOX_ERROR_STATUS_ENABLE_RX_UNDERFLOW_LSB  1
#घोषणा MBOX_ERROR_STATUS_ENABLE_RX_UNDERFLOW_MASK 0x00000002
#घोषणा MBOX_ERROR_STATUS_ENABLE_TX_OVERFLOW_LSB   0
#घोषणा MBOX_ERROR_STATUS_ENABLE_TX_OVERFLOW_MASK  0x00000001
#घोषणा MBOX_COUNTER_INT_STATUS_ENABLE_ADDRESS	0x0000081b
#घोषणा MBOX_COUNTER_INT_STATUS_ENABLE_BIT_LSB	0
#घोषणा MBOX_COUNTER_INT_STATUS_ENABLE_BIT_MASK	0x000000ff
#घोषणा MBOX_COUNT_ADDRESS			0x00000820
#घोषणा MBOX_COUNT_DEC_ADDRESS			0x00000840
#घोषणा MBOX_WINDOW_DATA_ADDRESS		0x00000874
#घोषणा MBOX_WINDOW_WRITE_ADDR_ADDRESS		0x00000878
#घोषणा MBOX_WINDOW_READ_ADDR_ADDRESS		0x0000087c
#घोषणा MBOX_CPU_DBG_SEL_ADDRESS		0x00000883
#घोषणा MBOX_CPU_DBG_ADDRESS			0x00000884
#घोषणा MBOX_RTC_BASE_ADDRESS			0x00000000
#घोषणा MBOX_GPIO_BASE_ADDRESS			0x00005000
#घोषणा MBOX_MBOX_BASE_ADDRESS			0x00008000

#घोषणा RTC_STATE_V_GET(x) (((x) & RTC_STATE_V_MASK) >> RTC_STATE_V_LSB)

/* Register definitions क्रम first generation ath10k cards. These cards include
 * a mac thich has a रेजिस्टर allocation similar to ath9k and at least some
 * रेजिस्टरs including the ones relevant क्रम modअगरying the coverage class are
 * identical to the ath9k definitions.
 * These रेजिस्टरs are usually managed by the ath10k firmware. However by
 * overriding them it is possible to support coverage class modअगरications.
 */
#घोषणा WAVE1_PCU_ACK_CTS_TIMEOUT		0x8014
#घोषणा WAVE1_PCU_ACK_CTS_TIMEOUT_MAX		0x00003FFF
#घोषणा WAVE1_PCU_ACK_CTS_TIMEOUT_ACK_MASK	0x00003FFF
#घोषणा WAVE1_PCU_ACK_CTS_TIMEOUT_ACK_LSB	0
#घोषणा WAVE1_PCU_ACK_CTS_TIMEOUT_CTS_MASK	0x3FFF0000
#घोषणा WAVE1_PCU_ACK_CTS_TIMEOUT_CTS_LSB	16

#घोषणा WAVE1_PCU_GBL_IFS_SLOT			0x1070
#घोषणा WAVE1_PCU_GBL_IFS_SLOT_MASK		0x0000FFFF
#घोषणा WAVE1_PCU_GBL_IFS_SLOT_MAX		0x0000FFFF
#घोषणा WAVE1_PCU_GBL_IFS_SLOT_LSB		0
#घोषणा WAVE1_PCU_GBL_IFS_SLOT_RESV0		0xFFFF0000

#घोषणा WAVE1_PHYCLK				0x801C
#घोषणा WAVE1_PHYCLK_USEC_MASK			0x0000007F
#घोषणा WAVE1_PHYCLK_USEC_LSB			0

/* qca6174 PLL offset/mask */
#घोषणा SOC_CORE_CLK_CTRL_OFFSET		0x00000114
#घोषणा SOC_CORE_CLK_CTRL_DIV_LSB		0
#घोषणा SOC_CORE_CLK_CTRL_DIV_MASK		0x00000007

#घोषणा EFUSE_OFFSET				0x0000032c
#घोषणा EFUSE_XTAL_SEL_LSB			8
#घोषणा EFUSE_XTAL_SEL_MASK			0x00000700

#घोषणा BB_PLL_CONFIG_OFFSET			0x000002f4
#घोषणा BB_PLL_CONFIG_FRAC_LSB			0
#घोषणा BB_PLL_CONFIG_FRAC_MASK			0x0003ffff
#घोषणा BB_PLL_CONFIG_OUTDIV_LSB		18
#घोषणा BB_PLL_CONFIG_OUTDIV_MASK		0x001c0000

#घोषणा WLAN_PLL_SETTLE_OFFSET			0x0018
#घोषणा WLAN_PLL_SETTLE_TIME_LSB		0
#घोषणा WLAN_PLL_SETTLE_TIME_MASK		0x000007ff

#घोषणा WLAN_PLL_CONTROL_OFFSET			0x0014
#घोषणा WLAN_PLL_CONTROL_DIV_LSB		0
#घोषणा WLAN_PLL_CONTROL_DIV_MASK		0x000003ff
#घोषणा WLAN_PLL_CONTROL_REFDIV_LSB		10
#घोषणा WLAN_PLL_CONTROL_REFDIV_MASK		0x00003c00
#घोषणा WLAN_PLL_CONTROL_BYPASS_LSB		16
#घोषणा WLAN_PLL_CONTROL_BYPASS_MASK		0x00010000
#घोषणा WLAN_PLL_CONTROL_NOPWD_LSB		18
#घोषणा WLAN_PLL_CONTROL_NOPWD_MASK		0x00040000

#घोषणा RTC_SYNC_STATUS_OFFSET			0x0244
#घोषणा RTC_SYNC_STATUS_PLL_CHANGING_LSB	5
#घोषणा RTC_SYNC_STATUS_PLL_CHANGING_MASK	0x00000020
/* qca6174 PLL offset/mask end */

/* CPU_ADDR_MSB is a रेजिस्टर, bit[3:0] is to specअगरy which memory
 * region is accessed. The memory region size is 1M.
 * If host wants to access 0xX12345 at target, then CPU_ADDR_MSB[3:0]
 * is 0xX.
 * The following MACROs are defined to get the 0xX and the size limit.
 */
#घोषणा CPU_ADDR_MSB_REGION_MASK	GENMASK(23, 20)
#घोषणा CPU_ADDR_MSB_REGION_VAL(X)	FIELD_GET(CPU_ADDR_MSB_REGION_MASK, X)
#घोषणा REGION_ACCESS_SIZE_LIMIT	0x100000
#घोषणा REGION_ACCESS_SIZE_MASK		(REGION_ACCESS_SIZE_LIMIT - 1)

#पूर्ण_अगर /* _HW_H_ */
