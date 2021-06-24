<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश "core.h"
#समावेश "hw.h"
#समावेश "hif.h"
#समावेश "wmi-ops.h"
#समावेश "bmi.h"

स्थिर काष्ठा ath10k_hw_regs qca988x_regs = अणु
	.rtc_soc_base_address		= 0x00004000,
	.rtc_wmac_base_address		= 0x00005000,
	.soc_core_base_address		= 0x00009000,
	.wlan_mac_base_address		= 0x00020000,
	.ce_wrapper_base_address	= 0x00057000,
	.ce0_base_address		= 0x00057400,
	.ce1_base_address		= 0x00057800,
	.ce2_base_address		= 0x00057c00,
	.ce3_base_address		= 0x00058000,
	.ce4_base_address		= 0x00058400,
	.ce5_base_address		= 0x00058800,
	.ce6_base_address		= 0x00058c00,
	.ce7_base_address		= 0x00059000,
	.soc_reset_control_si0_rst_mask	= 0x00000001,
	.soc_reset_control_ce_rst_mask	= 0x00040000,
	.soc_chip_id_address		= 0x000000ec,
	.scratch_3_address		= 0x00000030,
	.fw_indicator_address		= 0x00009030,
	.pcie_local_base_address	= 0x00080000,
	.ce_wrap_पूर्णांकr_sum_host_msi_lsb	= 0x00000008,
	.ce_wrap_पूर्णांकr_sum_host_msi_mask	= 0x0000ff00,
	.pcie_पूर्णांकr_fw_mask		= 0x00000400,
	.pcie_पूर्णांकr_ce_mask_all		= 0x0007f800,
	.pcie_पूर्णांकr_clr_address		= 0x00000014,
पूर्ण;

स्थिर काष्ठा ath10k_hw_regs qca6174_regs = अणु
	.rtc_soc_base_address			= 0x00000800,
	.rtc_wmac_base_address			= 0x00001000,
	.soc_core_base_address			= 0x0003a000,
	.wlan_mac_base_address			= 0x00010000,
	.ce_wrapper_base_address		= 0x00034000,
	.ce0_base_address			= 0x00034400,
	.ce1_base_address			= 0x00034800,
	.ce2_base_address			= 0x00034c00,
	.ce3_base_address			= 0x00035000,
	.ce4_base_address			= 0x00035400,
	.ce5_base_address			= 0x00035800,
	.ce6_base_address			= 0x00035c00,
	.ce7_base_address			= 0x00036000,
	.soc_reset_control_si0_rst_mask		= 0x00000000,
	.soc_reset_control_ce_rst_mask		= 0x00000001,
	.soc_chip_id_address			= 0x000000f0,
	.scratch_3_address			= 0x00000028,
	.fw_indicator_address			= 0x0003a028,
	.pcie_local_base_address		= 0x00080000,
	.ce_wrap_पूर्णांकr_sum_host_msi_lsb		= 0x00000008,
	.ce_wrap_पूर्णांकr_sum_host_msi_mask		= 0x0000ff00,
	.pcie_पूर्णांकr_fw_mask			= 0x00000400,
	.pcie_पूर्णांकr_ce_mask_all			= 0x0007f800,
	.pcie_पूर्णांकr_clr_address			= 0x00000014,
	.cpu_pll_init_address			= 0x00404020,
	.cpu_speed_address			= 0x00404024,
	.core_clk_भाग_address			= 0x00404028,
पूर्ण;

स्थिर काष्ठा ath10k_hw_regs qca99x0_regs = अणु
	.rtc_soc_base_address			= 0x00080000,
	.rtc_wmac_base_address			= 0x00000000,
	.soc_core_base_address			= 0x00082000,
	.wlan_mac_base_address			= 0x00030000,
	.ce_wrapper_base_address		= 0x0004d000,
	.ce0_base_address			= 0x0004a000,
	.ce1_base_address			= 0x0004a400,
	.ce2_base_address			= 0x0004a800,
	.ce3_base_address			= 0x0004ac00,
	.ce4_base_address			= 0x0004b000,
	.ce5_base_address			= 0x0004b400,
	.ce6_base_address			= 0x0004b800,
	.ce7_base_address			= 0x0004bc00,
	/* Note: qca99x0 supports upto 12 Copy Engines. Other than address of
	 * CE0 and CE1 no other copy engine is directly referred in the code.
	 * It is not really necessary to assign address क्रम newly supported
	 * CEs in this address table.
	 *	Copy Engine		Address
	 *	CE8			0x0004c000
	 *	CE9			0x0004c400
	 *	CE10			0x0004c800
	 *	CE11			0x0004cc00
	 */
	.soc_reset_control_si0_rst_mask		= 0x00000001,
	.soc_reset_control_ce_rst_mask		= 0x00000100,
	.soc_chip_id_address			= 0x000000ec,
	.scratch_3_address			= 0x00040050,
	.fw_indicator_address			= 0x00040050,
	.pcie_local_base_address		= 0x00000000,
	.ce_wrap_पूर्णांकr_sum_host_msi_lsb		= 0x0000000c,
	.ce_wrap_पूर्णांकr_sum_host_msi_mask		= 0x00fff000,
	.pcie_पूर्णांकr_fw_mask			= 0x00100000,
	.pcie_पूर्णांकr_ce_mask_all			= 0x000fff00,
	.pcie_पूर्णांकr_clr_address			= 0x00000010,
पूर्ण;

स्थिर काष्ठा ath10k_hw_regs qca4019_regs = अणु
	.rtc_soc_base_address                   = 0x00080000,
	.soc_core_base_address                  = 0x00082000,
	.wlan_mac_base_address                  = 0x00030000,
	.ce_wrapper_base_address                = 0x0004d000,
	.ce0_base_address                       = 0x0004a000,
	.ce1_base_address                       = 0x0004a400,
	.ce2_base_address                       = 0x0004a800,
	.ce3_base_address                       = 0x0004ac00,
	.ce4_base_address                       = 0x0004b000,
	.ce5_base_address                       = 0x0004b400,
	.ce6_base_address                       = 0x0004b800,
	.ce7_base_address                       = 0x0004bc00,
	/* qca4019 supports upto 12 copy engines. Since base address
	 * of ce8 to ce11 are not directly referred in the code,
	 * no need have them in separate members in this table.
	 *      Copy Engine             Address
	 *      CE8                     0x0004c000
	 *      CE9                     0x0004c400
	 *      CE10                    0x0004c800
	 *      CE11                    0x0004cc00
	 */
	.soc_reset_control_si0_rst_mask         = 0x00000001,
	.soc_reset_control_ce_rst_mask          = 0x00000100,
	.soc_chip_id_address                    = 0x000000ec,
	.fw_indicator_address                   = 0x0004f00c,
	.ce_wrap_पूर्णांकr_sum_host_msi_lsb          = 0x0000000c,
	.ce_wrap_पूर्णांकr_sum_host_msi_mask         = 0x00fff000,
	.pcie_पूर्णांकr_fw_mask                      = 0x00100000,
	.pcie_पूर्णांकr_ce_mask_all                  = 0x000fff00,
	.pcie_पूर्णांकr_clr_address                  = 0x00000010,
पूर्ण;

स्थिर काष्ठा ath10k_hw_values qca988x_values = अणु
	.rtc_state_val_on		= 3,
	.ce_count			= 8,
	.msi_assign_ce_max		= 7,
	.num_target_ce_config_wlan	= 7,
	.ce_desc_meta_data_mask		= 0xFFFC,
	.ce_desc_meta_data_lsb		= 2,
पूर्ण;

स्थिर काष्ठा ath10k_hw_values qca6174_values = अणु
	.rtc_state_val_on		= 3,
	.ce_count			= 8,
	.msi_assign_ce_max		= 7,
	.num_target_ce_config_wlan	= 7,
	.ce_desc_meta_data_mask		= 0xFFFC,
	.ce_desc_meta_data_lsb		= 2,
	.rfसमाप्त_pin			= 16,
	.rfसमाप्त_cfg			= 0,
	.rfसमाप्त_on_level		= 1,
पूर्ण;

स्थिर काष्ठा ath10k_hw_values qca99x0_values = अणु
	.rtc_state_val_on		= 7,
	.ce_count			= 12,
	.msi_assign_ce_max		= 12,
	.num_target_ce_config_wlan	= 10,
	.ce_desc_meta_data_mask		= 0xFFF0,
	.ce_desc_meta_data_lsb		= 4,
पूर्ण;

स्थिर काष्ठा ath10k_hw_values qca9888_values = अणु
	.rtc_state_val_on		= 3,
	.ce_count			= 12,
	.msi_assign_ce_max		= 12,
	.num_target_ce_config_wlan	= 10,
	.ce_desc_meta_data_mask		= 0xFFF0,
	.ce_desc_meta_data_lsb		= 4,
पूर्ण;

स्थिर काष्ठा ath10k_hw_values qca4019_values = अणु
	.ce_count                       = 12,
	.num_target_ce_config_wlan      = 10,
	.ce_desc_meta_data_mask         = 0xFFF0,
	.ce_desc_meta_data_lsb          = 4,
पूर्ण;

स्थिर काष्ठा ath10k_hw_regs wcn3990_regs = अणु
	.rtc_soc_base_address			= 0x00000000,
	.rtc_wmac_base_address			= 0x00000000,
	.soc_core_base_address			= 0x00000000,
	.ce_wrapper_base_address		= 0x0024C000,
	.ce0_base_address			= 0x00240000,
	.ce1_base_address			= 0x00241000,
	.ce2_base_address			= 0x00242000,
	.ce3_base_address			= 0x00243000,
	.ce4_base_address			= 0x00244000,
	.ce5_base_address			= 0x00245000,
	.ce6_base_address			= 0x00246000,
	.ce7_base_address			= 0x00247000,
	.ce8_base_address			= 0x00248000,
	.ce9_base_address			= 0x00249000,
	.ce10_base_address			= 0x0024A000,
	.ce11_base_address			= 0x0024B000,
	.soc_chip_id_address			= 0x000000f0,
	.soc_reset_control_si0_rst_mask		= 0x00000001,
	.soc_reset_control_ce_rst_mask		= 0x00000100,
	.ce_wrap_पूर्णांकr_sum_host_msi_lsb		= 0x0000000c,
	.ce_wrap_पूर्णांकr_sum_host_msi_mask		= 0x00fff000,
	.pcie_पूर्णांकr_fw_mask			= 0x00100000,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_src_ring = अणु
	.msb	= 0x00000010,
	.lsb	= 0x00000010,
	.mask	= GENMASK(17, 17),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_dst_ring = अणु
	.msb	= 0x00000012,
	.lsb	= 0x00000012,
	.mask	= GENMASK(18, 18),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_dmax = अणु
	.msb	= 0x00000000,
	.lsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_ctrl1 wcn3990_ctrl1 = अणु
	.addr		= 0x00000018,
	.src_ring	= &wcn3990_src_ring,
	.dst_ring	= &wcn3990_dst_ring,
	.dmax		= &wcn3990_dmax,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_host_ie_cc = अणु
	.mask	= GENMASK(0, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_host_ie wcn3990_host_ie = अणु
	.copy_complete	= &wcn3990_host_ie_cc,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_host_wm_regs wcn3990_wm_reg = अणु
	.dstr_lmask	= 0x00000010,
	.dstr_hmask	= 0x00000008,
	.srcr_lmask	= 0x00000004,
	.srcr_hmask	= 0x00000002,
	.cc_mask	= 0x00000001,
	.wm_mask	= 0x0000001E,
	.addr		= 0x00000030,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_misc_regs wcn3990_misc_reg = अणु
	.axi_err	= 0x00000100,
	.dstr_add_err	= 0x00000200,
	.srcr_len_err	= 0x00000100,
	.dstr_mlen_vio	= 0x00000080,
	.dstr_overflow	= 0x00000040,
	.srcr_overflow	= 0x00000020,
	.err_mask	= 0x000003E0,
	.addr		= 0x00000038,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_src_wm_low = अणु
	.msb	= 0x00000000,
	.lsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_src_wm_high = अणु
	.msb	= 0x0000000f,
	.lsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_dst_src_wm_regs wcn3990_wm_src_ring = अणु
	.addr		= 0x0000004c,
	.low_rst	= 0x00000000,
	.high_rst	= 0x00000000,
	.wm_low		= &wcn3990_src_wm_low,
	.wm_high	= &wcn3990_src_wm_high,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_dst_wm_low = अणु
	.lsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map wcn3990_dst_wm_high = अणु
	.msb	= 0x0000000f,
	.lsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_dst_src_wm_regs wcn3990_wm_dst_ring = अणु
	.addr		= 0x00000050,
	.low_rst	= 0x00000000,
	.high_rst	= 0x00000000,
	.wm_low		= &wcn3990_dst_wm_low,
	.wm_high	= &wcn3990_dst_wm_high,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_ctrl1_upd wcn3990_ctrl1_upd = अणु
	.shअगरt = 19,
	.mask = 0x00080000,
	.enable = 0x00000000,
पूर्ण;

स्थिर काष्ठा ath10k_hw_ce_regs wcn3990_ce_regs = अणु
	.sr_base_addr_lo	= 0x00000000,
	.sr_base_addr_hi	= 0x00000004,
	.sr_size_addr		= 0x00000008,
	.dr_base_addr_lo	= 0x0000000c,
	.dr_base_addr_hi	= 0x00000010,
	.dr_size_addr		= 0x00000014,
	.misc_ie_addr		= 0x00000034,
	.sr_wr_index_addr	= 0x0000003c,
	.dst_wr_index_addr	= 0x00000040,
	.current_srri_addr	= 0x00000044,
	.current_drri_addr	= 0x00000048,
	.ce_rri_low		= 0x0024C004,
	.ce_rri_high		= 0x0024C008,
	.host_ie_addr		= 0x0000002c,
	.ctrl1_regs		= &wcn3990_ctrl1,
	.host_ie		= &wcn3990_host_ie,
	.wm_regs		= &wcn3990_wm_reg,
	.misc_regs		= &wcn3990_misc_reg,
	.wm_srcr		= &wcn3990_wm_src_ring,
	.wm_dstr		= &wcn3990_wm_dst_ring,
	.upd			= &wcn3990_ctrl1_upd,
पूर्ण;

स्थिर काष्ठा ath10k_hw_values wcn3990_values = अणु
	.rtc_state_val_on		= 5,
	.ce_count			= 12,
	.msi_assign_ce_max		= 12,
	.num_target_ce_config_wlan	= 12,
	.ce_desc_meta_data_mask		= 0xFFF0,
	.ce_desc_meta_data_lsb		= 4,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_src_ring = अणु
	.msb	= 0x00000010,
	.lsb	= 0x00000010,
	.mask	= GENMASK(16, 16),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_dst_ring = अणु
	.msb	= 0x00000011,
	.lsb	= 0x00000011,
	.mask	= GENMASK(17, 17),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_dmax = अणु
	.msb	= 0x0000000f,
	.lsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_ctrl1 qcax_ctrl1 = अणु
	.addr		= 0x00000010,
	.hw_mask	= 0x0007ffff,
	.sw_mask	= 0x0007ffff,
	.hw_wr_mask	= 0x00000000,
	.sw_wr_mask	= 0x0007ffff,
	.reset_mask	= 0xffffffff,
	.reset		= 0x00000080,
	.src_ring	= &qcax_src_ring,
	.dst_ring	= &qcax_dst_ring,
	.dmax		= &qcax_dmax,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_cmd_halt_status = अणु
	.msb	= 0x00000003,
	.lsb	= 0x00000003,
	.mask	= GENMASK(3, 3),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_cmd_halt qcax_cmd_halt = अणु
	.msb		= 0x00000000,
	.mask		= GENMASK(0, 0),
	.status_reset	= 0x00000000,
	.status		= &qcax_cmd_halt_status,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_host_ie_cc = अणु
	.msb	= 0x00000000,
	.lsb	= 0x00000000,
	.mask	= GENMASK(0, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_host_ie qcax_host_ie = अणु
	.copy_complete_reset	= 0x00000000,
	.copy_complete		= &qcax_host_ie_cc,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_host_wm_regs qcax_wm_reg = अणु
	.dstr_lmask	= 0x00000010,
	.dstr_hmask	= 0x00000008,
	.srcr_lmask	= 0x00000004,
	.srcr_hmask	= 0x00000002,
	.cc_mask	= 0x00000001,
	.wm_mask	= 0x0000001E,
	.addr		= 0x00000030,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_misc_regs qcax_misc_reg = अणु
	.axi_err	= 0x00000400,
	.dstr_add_err	= 0x00000200,
	.srcr_len_err	= 0x00000100,
	.dstr_mlen_vio	= 0x00000080,
	.dstr_overflow	= 0x00000040,
	.srcr_overflow	= 0x00000020,
	.err_mask	= 0x000007E0,
	.addr		= 0x00000038,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_src_wm_low = अणु
	.msb    = 0x0000001f,
	.lsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_src_wm_high = अणु
	.msb	= 0x0000000f,
	.lsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_dst_src_wm_regs qcax_wm_src_ring = अणु
	.addr		= 0x0000004c,
	.low_rst	= 0x00000000,
	.high_rst	= 0x00000000,
	.wm_low		= &qcax_src_wm_low,
	.wm_high        = &qcax_src_wm_high,
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_dst_wm_low = अणु
	.lsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_regs_addr_map qcax_dst_wm_high = अणु
	.msb	= 0x0000000f,
	.lsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
पूर्ण;

अटल काष्ठा ath10k_hw_ce_dst_src_wm_regs qcax_wm_dst_ring = अणु
	.addr		= 0x00000050,
	.low_rst	= 0x00000000,
	.high_rst	= 0x00000000,
	.wm_low		= &qcax_dst_wm_low,
	.wm_high	= &qcax_dst_wm_high,
पूर्ण;

स्थिर काष्ठा ath10k_hw_ce_regs qcax_ce_regs = अणु
	.sr_base_addr_lo	= 0x00000000,
	.sr_size_addr		= 0x00000004,
	.dr_base_addr_lo	= 0x00000008,
	.dr_size_addr		= 0x0000000c,
	.ce_cmd_addr		= 0x00000018,
	.misc_ie_addr		= 0x00000034,
	.sr_wr_index_addr	= 0x0000003c,
	.dst_wr_index_addr	= 0x00000040,
	.current_srri_addr	= 0x00000044,
	.current_drri_addr	= 0x00000048,
	.host_ie_addr		= 0x0000002c,
	.ctrl1_regs		= &qcax_ctrl1,
	.cmd_halt		= &qcax_cmd_halt,
	.host_ie		= &qcax_host_ie,
	.wm_regs		= &qcax_wm_reg,
	.misc_regs		= &qcax_misc_reg,
	.wm_srcr		= &qcax_wm_src_ring,
	.wm_dstr                = &qcax_wm_dst_ring,
पूर्ण;

स्थिर काष्ठा ath10k_hw_clk_params qca6174_clk[ATH10K_HW_REFCLK_COUNT] = अणु
	अणु
		.refclk = 48000000,
		.भाग = 0xe,
		.rnfrac = 0x2aaa8,
		.settle_समय = 2400,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 19200000,
		.भाग = 0x24,
		.rnfrac = 0x2aaa8,
		.settle_समय = 960,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 24000000,
		.भाग = 0x1d,
		.rnfrac = 0x15551,
		.settle_समय = 1200,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 26000000,
		.भाग = 0x1b,
		.rnfrac = 0x4ec4,
		.settle_समय = 1300,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 37400000,
		.भाग = 0x12,
		.rnfrac = 0x34b49,
		.settle_समय = 1870,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 38400000,
		.भाग = 0x12,
		.rnfrac = 0x15551,
		.settle_समय = 1920,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 40000000,
		.भाग = 0x12,
		.rnfrac = 0x26665,
		.settle_समय = 2000,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
	अणु
		.refclk = 52000000,
		.भाग = 0x1b,
		.rnfrac = 0x4ec4,
		.settle_समय = 2600,
		.refभाग = 0,
		.outभाग = 1,
	पूर्ण,
पूर्ण;

व्योम ath10k_hw_fill_survey_समय(काष्ठा ath10k *ar, काष्ठा survey_info *survey,
				u32 cc, u32 rcc, u32 cc_prev, u32 rcc_prev)
अणु
	u32 cc_fix = 0;
	u32 rcc_fix = 0;
	क्रमागत ath10k_hw_cc_wraparound_type wraparound_type;

	survey->filled |= SURVEY_INFO_TIME |
			  SURVEY_INFO_TIME_BUSY;

	wraparound_type = ar->hw_params.cc_wraparound_type;

	अगर (cc < cc_prev || rcc < rcc_prev) अणु
		चयन (wraparound_type) अणु
		हाल ATH10K_HW_CC_WRAP_SHIFTED_ALL:
			अगर (cc < cc_prev) अणु
				cc_fix = 0x7fffffff;
				survey->filled &= ~SURVEY_INFO_TIME_BUSY;
			पूर्ण
			अवरोध;
		हाल ATH10K_HW_CC_WRAP_SHIFTED_EACH:
			अगर (cc < cc_prev)
				cc_fix = 0x7fffffff;

			अगर (rcc < rcc_prev)
				rcc_fix = 0x7fffffff;
			अवरोध;
		हाल ATH10K_HW_CC_WRAP_DISABLED:
			अवरोध;
		पूर्ण
	पूर्ण

	cc -= cc_prev - cc_fix;
	rcc -= rcc_prev - rcc_fix;

	survey->समय = CCNT_TO_MSEC(ar, cc);
	survey->समय_busy = CCNT_TO_MSEC(ar, rcc);
पूर्ण

/* The firmware करोes not support setting the coverage class. Instead this
 * function monitors and modअगरies the corresponding MAC रेजिस्टरs.
 */
अटल व्योम ath10k_hw_qca988x_set_coverage_class(काष्ठा ath10k *ar,
						 s16 value)
अणु
	u32 slotसमय_reg;
	u32 slotसमय;
	u32 समयout_reg;
	u32 ack_समयout;
	u32 cts_समयout;
	u32 phyclk_reg;
	u32 phyclk;
	u64 fw_dbglog_mask;
	u32 fw_dbglog_level;

	mutex_lock(&ar->conf_mutex);

	/* Only modअगरy रेजिस्टरs अगर the core is started. */
	अगर ((ar->state != ATH10K_STATE_ON) &&
	    (ar->state != ATH10K_STATE_RESTARTED)) अणु
		spin_lock_bh(&ar->data_lock);
		/* Store config value क्रम when radio boots up */
		ar->fw_coverage.coverage_class = value;
		spin_unlock_bh(&ar->data_lock);
		जाओ unlock;
	पूर्ण

	/* Retrieve the current values of the two रेजिस्टरs that need to be
	 * adjusted.
	 */
	slotसमय_reg = ath10k_hअगर_पढ़ो32(ar, WLAN_MAC_BASE_ADDRESS +
					     WAVE1_PCU_GBL_IFS_SLOT);
	समयout_reg = ath10k_hअगर_पढ़ो32(ar, WLAN_MAC_BASE_ADDRESS +
					    WAVE1_PCU_ACK_CTS_TIMEOUT);
	phyclk_reg = ath10k_hअगर_पढ़ो32(ar, WLAN_MAC_BASE_ADDRESS +
					   WAVE1_PHYCLK);
	phyclk = MS(phyclk_reg, WAVE1_PHYCLK_USEC) + 1;

	अगर (value < 0)
		value = ar->fw_coverage.coverage_class;

	/* Break out अगर the coverage class and रेजिस्टरs have the expected
	 * value.
	 */
	अगर (value == ar->fw_coverage.coverage_class &&
	    slotसमय_reg == ar->fw_coverage.reg_slotसमय_conf &&
	    समयout_reg == ar->fw_coverage.reg_ack_cts_समयout_conf &&
	    phyclk_reg == ar->fw_coverage.reg_phyclk)
		जाओ unlock;

	/* Store new initial रेजिस्टर values from the firmware. */
	अगर (slotसमय_reg != ar->fw_coverage.reg_slotसमय_conf)
		ar->fw_coverage.reg_slotसमय_orig = slotसमय_reg;
	अगर (समयout_reg != ar->fw_coverage.reg_ack_cts_समयout_conf)
		ar->fw_coverage.reg_ack_cts_समयout_orig = समयout_reg;
	ar->fw_coverage.reg_phyclk = phyclk_reg;

	/* Calculate new value based on the (original) firmware calculation. */
	slotसमय_reg = ar->fw_coverage.reg_slotसमय_orig;
	समयout_reg = ar->fw_coverage.reg_ack_cts_समयout_orig;

	/* Do some sanity checks on the slotसमय रेजिस्टर. */
	अगर (slotसमय_reg % phyclk) अणु
		ath10k_warn(ar,
			    "failed to set coverage class: expected integer microsecond value in register\n");

		जाओ store_regs;
	पूर्ण

	slotसमय = MS(slotसमय_reg, WAVE1_PCU_GBL_IFS_SLOT);
	slotसमय = slotसमय / phyclk;
	अगर (slotसमय != 9 && slotसमय != 20) अणु
		ath10k_warn(ar,
			    "failed to set coverage class: expected slot time of 9 or 20us in HW register. It is %uus.\n",
			    slotसमय);

		जाओ store_regs;
	पूर्ण

	/* Recalculate the रेजिस्टर values by adding the additional propagation
	 * delay (3us per coverage class).
	 */

	slotसमय = MS(slotसमय_reg, WAVE1_PCU_GBL_IFS_SLOT);
	slotसमय += value * 3 * phyclk;
	slotसमय = min_t(u32, slotसमय, WAVE1_PCU_GBL_IFS_SLOT_MAX);
	slotसमय = SM(slotसमय, WAVE1_PCU_GBL_IFS_SLOT);
	slotसमय_reg = (slotसमय_reg & ~WAVE1_PCU_GBL_IFS_SLOT_MASK) | slotसमय;

	/* Update ack समयout (lower halfword). */
	ack_समयout = MS(समयout_reg, WAVE1_PCU_ACK_CTS_TIMEOUT_ACK);
	ack_समयout += 3 * value * phyclk;
	ack_समयout = min_t(u32, ack_समयout, WAVE1_PCU_ACK_CTS_TIMEOUT_MAX);
	ack_समयout = SM(ack_समयout, WAVE1_PCU_ACK_CTS_TIMEOUT_ACK);

	/* Update cts समयout (upper halfword). */
	cts_समयout = MS(समयout_reg, WAVE1_PCU_ACK_CTS_TIMEOUT_CTS);
	cts_समयout += 3 * value * phyclk;
	cts_समयout = min_t(u32, cts_समयout, WAVE1_PCU_ACK_CTS_TIMEOUT_MAX);
	cts_समयout = SM(cts_समयout, WAVE1_PCU_ACK_CTS_TIMEOUT_CTS);

	समयout_reg = ack_समयout | cts_समयout;

	ath10k_hअगर_ग_लिखो32(ar,
			   WLAN_MAC_BASE_ADDRESS + WAVE1_PCU_GBL_IFS_SLOT,
			   slotसमय_reg);
	ath10k_hअगर_ग_लिखो32(ar,
			   WLAN_MAC_BASE_ADDRESS + WAVE1_PCU_ACK_CTS_TIMEOUT,
			   समयout_reg);

	/* Ensure we have a debug level of WARN set क्रम the हाल that the
	 * coverage class is larger than 0. This is important as we need to
	 * set the रेजिस्टरs again अगर the firmware करोes an पूर्णांकernal reset and
	 * this way we will be notअगरied of the event.
	 */
	fw_dbglog_mask = ath10k_debug_get_fw_dbglog_mask(ar);
	fw_dbglog_level = ath10k_debug_get_fw_dbglog_level(ar);

	अगर (value > 0) अणु
		अगर (fw_dbglog_level > ATH10K_DBGLOG_LEVEL_WARN)
			fw_dbglog_level = ATH10K_DBGLOG_LEVEL_WARN;
		fw_dbglog_mask = ~0;
	पूर्ण

	ath10k_wmi_dbglog_cfg(ar, fw_dbglog_mask, fw_dbglog_level);

store_regs:
	/* After an error we will not retry setting the coverage class. */
	spin_lock_bh(&ar->data_lock);
	ar->fw_coverage.coverage_class = value;
	spin_unlock_bh(&ar->data_lock);

	ar->fw_coverage.reg_slotसमय_conf = slotसमय_reg;
	ar->fw_coverage.reg_ack_cts_समयout_conf = समयout_reg;

unlock:
	mutex_unlock(&ar->conf_mutex);
पूर्ण

/**
 * ath10k_hw_qca6174_enable_pll_घड़ी() - enable the qca6174 hw pll घड़ी
 * @ar: the ath10k blob
 *
 * This function is very hardware specअगरic, the घड़ी initialization
 * steps is very sensitive and could lead to unknown crash, so they
 * should be करोne in sequence.
 *
 * *** Be aware अगर you planned to refactor them. ***
 *
 * Return: 0 अगर successfully enable the pll, otherwise EINVAL
 */
अटल पूर्णांक ath10k_hw_qca6174_enable_pll_घड़ी(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret, रुको_limit;
	u32 clk_भाग_addr, pll_init_addr, speed_addr;
	u32 addr, reg_val, mem_val;
	काष्ठा ath10k_hw_params *hw;
	स्थिर काष्ठा ath10k_hw_clk_params *hw_clk;

	hw = &ar->hw_params;

	अगर (ar->regs->core_clk_भाग_address == 0 ||
	    ar->regs->cpu_pll_init_address == 0 ||
	    ar->regs->cpu_speed_address == 0)
		वापस -EINVAL;

	clk_भाग_addr = ar->regs->core_clk_भाग_address;
	pll_init_addr = ar->regs->cpu_pll_init_address;
	speed_addr = ar->regs->cpu_speed_address;

	/* Read efuse रेजिस्टर to find out the right hw घड़ी configuration */
	addr = (RTC_SOC_BASE_ADDRESS | EFUSE_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* sanitize अगर the hw refclk index is out of the boundary */
	अगर (MS(reg_val, EFUSE_XTAL_SEL) > ATH10K_HW_REFCLK_COUNT)
		वापस -EINVAL;

	hw_clk = &hw->hw_clk[MS(reg_val, EFUSE_XTAL_SEL)];

	/* Set the rnfrac and outभाग params to bb_pll रेजिस्टर */
	addr = (RTC_SOC_BASE_ADDRESS | BB_PLL_CONFIG_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val &= ~(BB_PLL_CONFIG_FRAC_MASK | BB_PLL_CONFIG_OUTDIV_MASK);
	reg_val |= (SM(hw_clk->rnfrac, BB_PLL_CONFIG_FRAC) |
		    SM(hw_clk->outभाग, BB_PLL_CONFIG_OUTDIV));
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* Set the correct settle समय value to pll_settle रेजिस्टर */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_SETTLE_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val &= ~WLAN_PLL_SETTLE_TIME_MASK;
	reg_val |= SM(hw_clk->settle_समय, WLAN_PLL_SETTLE_TIME);
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* Set the घड़ी_ctrl भाग to core_clk_ctrl रेजिस्टर */
	addr = (RTC_SOC_BASE_ADDRESS | SOC_CORE_CLK_CTRL_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val &= ~SOC_CORE_CLK_CTRL_DIV_MASK;
	reg_val |= SM(1, SOC_CORE_CLK_CTRL_DIV);
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* Set the घड़ी_भाग रेजिस्टर */
	mem_val = 1;
	ret = ath10k_bmi_ग_लिखो_memory(ar, clk_भाग_addr, &mem_val,
				      माप(mem_val));
	अगर (ret)
		वापस -EINVAL;

	/* Configure the pll_control रेजिस्टर */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_CONTROL_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val |= (SM(hw_clk->refभाग, WLAN_PLL_CONTROL_REFDIV) |
		    SM(hw_clk->भाग, WLAN_PLL_CONTROL_DIV) |
		    SM(1, WLAN_PLL_CONTROL_NOPWD));
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* busy रुको (max 1s) the rtc_sync status रेजिस्टर indicate पढ़ोy */
	रुको_limit = 100000;
	addr = (RTC_WMAC_BASE_ADDRESS | RTC_SYNC_STATUS_OFFSET);
	करो अणु
		ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
		अगर (ret)
			वापस -EINVAL;

		अगर (!MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
			अवरोध;

		रुको_limit--;
		udelay(10);

	पूर्ण जबतक (रुको_limit > 0);

	अगर (MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
		वापस -EINVAL;

	/* Unset the pll_bypass in pll_control रेजिस्टर */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_CONTROL_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val &= ~WLAN_PLL_CONTROL_BYPASS_MASK;
	reg_val |= SM(0, WLAN_PLL_CONTROL_BYPASS);
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* busy रुको (max 1s) the rtc_sync status रेजिस्टर indicate पढ़ोy */
	रुको_limit = 100000;
	addr = (RTC_WMAC_BASE_ADDRESS | RTC_SYNC_STATUS_OFFSET);
	करो अणु
		ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
		अगर (ret)
			वापस -EINVAL;

		अगर (!MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
			अवरोध;

		रुको_limit--;
		udelay(10);

	पूर्ण जबतक (रुको_limit > 0);

	अगर (MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
		वापस -EINVAL;

	/* Enable the hardware cpu घड़ी रेजिस्टर */
	addr = (RTC_SOC_BASE_ADDRESS | SOC_CPU_CLOCK_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val &= ~SOC_CPU_CLOCK_STANDARD_MASK;
	reg_val |= SM(1, SOC_CPU_CLOCK_STANDARD);
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* unset the nopwd from pll_control रेजिस्टर */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_CONTROL_OFFSET);
	ret = ath10k_bmi_पढ़ो_soc_reg(ar, addr, &reg_val);
	अगर (ret)
		वापस -EINVAL;

	reg_val &= ~WLAN_PLL_CONTROL_NOPWD_MASK;
	ret = ath10k_bmi_ग_लिखो_soc_reg(ar, addr, reg_val);
	अगर (ret)
		वापस -EINVAL;

	/* enable the pll_init रेजिस्टर */
	mem_val = 1;
	ret = ath10k_bmi_ग_लिखो_memory(ar, pll_init_addr, &mem_val,
				      माप(mem_val));
	अगर (ret)
		वापस -EINVAL;

	/* set the target घड़ी frequency to speed रेजिस्टर */
	ret = ath10k_bmi_ग_लिखो_memory(ar, speed_addr, &hw->target_cpu_freq,
				      माप(hw->target_cpu_freq));
	अगर (ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Program CPU_ADDR_MSB to allow dअगरferent memory
 * region access.
 */
अटल व्योम ath10k_hw_map_target_mem(काष्ठा ath10k *ar, u32 msb)
अणु
	u32 address = SOC_CORE_BASE_ADDRESS + FW_RAM_CONFIG_ADDRESS;

	ath10k_hअगर_ग_लिखो32(ar, address, msb);
पूर्ण

/* 1. Write to memory region of target, such as IRAM adn DRAM.
 * 2. Target address( 0 ~ 00100000 & 0x00400000~0x00500000)
 *    can be written directly. See ath10k_pci_targ_cpu_to_ce_addr() too.
 * 3. In order to access the region other than the above,
 *    we need to set the value of रेजिस्टर CPU_ADDR_MSB.
 * 4. Target memory access space is limited to 1M size. If the size is larger
 *    than 1M, need to split it and program CPU_ADDR_MSB accordingly.
 */
अटल पूर्णांक ath10k_hw_diag_segment_msb_करोwnload(काष्ठा ath10k *ar,
					       स्थिर व्योम *buffer,
					       u32 address,
					       u32 length)
अणु
	u32 addr = address & REGION_ACCESS_SIZE_MASK;
	पूर्णांक ret, reमुख्य_size, size;
	स्थिर u8 *buf;

	ath10k_hw_map_target_mem(ar, CPU_ADDR_MSB_REGION_VAL(address));

	अगर (addr + length > REGION_ACCESS_SIZE_LIMIT) अणु
		size = REGION_ACCESS_SIZE_LIMIT - addr;
		reमुख्य_size = length - size;

		ret = ath10k_hअगर_diag_ग_लिखो(ar, address, buffer, size);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to download the first %d bytes segment to address:0x%x: %d\n",
				    size, address, ret);
			जाओ करोne;
		पूर्ण

		/* Change msb to the next memory region*/
		ath10k_hw_map_target_mem(ar,
					 CPU_ADDR_MSB_REGION_VAL(address) + 1);
		buf = buffer +  size;
		ret = ath10k_hअगर_diag_ग_लिखो(ar,
					    address & ~REGION_ACCESS_SIZE_MASK,
					    buf, reमुख्य_size);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to download the second %d bytes segment to address:0x%x: %d\n",
				    reमुख्य_size,
				    address & ~REGION_ACCESS_SIZE_MASK,
				    ret);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ath10k_hअगर_diag_ग_लिखो(ar, address, buffer, length);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to download the only %d bytes segment to address:0x%x: %d\n",
				    length, address, ret);
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	/* Change msb to DRAM */
	ath10k_hw_map_target_mem(ar,
				 CPU_ADDR_MSB_REGION_VAL(DRAM_BASE_ADDRESS));
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_hw_diag_segment_करोwnload(काष्ठा ath10k *ar,
					   स्थिर व्योम *buffer,
					   u32 address,
					   u32 length)
अणु
	अगर (address >= DRAM_BASE_ADDRESS + REGION_ACCESS_SIZE_LIMIT)
		/* Needs to change MSB क्रम memory ग_लिखो */
		वापस ath10k_hw_diag_segment_msb_करोwnload(ar, buffer,
							   address, length);
	अन्यथा
		वापस ath10k_hअगर_diag_ग_लिखो(ar, address, buffer, length);
पूर्ण

पूर्णांक ath10k_hw_diag_fast_करोwnload(काष्ठा ath10k *ar,
				 u32 address,
				 स्थिर व्योम *buffer,
				 u32 length)
अणु
	स्थिर u8 *buf = buffer;
	bool sgmt_end = false;
	u32 base_addr = 0;
	u32 base_len = 0;
	u32 left = 0;
	काष्ठा bmi_segmented_file_header *hdr;
	काष्ठा bmi_segmented_metadata *metadata;
	पूर्णांक ret = 0;

	अगर (length < माप(*hdr))
		वापस -EINVAL;

	/* check firmware header. If it has no correct magic number
	 * or it's compressed, वापसs error.
	 */
	hdr = (काष्ठा bmi_segmented_file_header *)buf;
	अगर (__le32_to_cpu(hdr->magic_num) != BMI_SGMTखाता_MAGIC_NUM) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "Not a supported firmware, magic_num:0x%x\n",
			   hdr->magic_num);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->file_flags != 0) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "Not a supported firmware, file_flags:0x%x\n",
			   hdr->file_flags);
		वापस -EINVAL;
	पूर्ण

	metadata = (काष्ठा bmi_segmented_metadata *)hdr->data;
	left = length - माप(*hdr);

	जबतक (left > 0) अणु
		अगर (left < माप(*metadata)) अणु
			ath10k_warn(ar, "firmware segment is truncated: %d\n",
				    left);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		base_addr = __le32_to_cpu(metadata->addr);
		base_len = __le32_to_cpu(metadata->length);
		buf = metadata->data;
		left -= माप(*metadata);

		चयन (base_len) अणु
		हाल BMI_SGMTखाता_BEGINADDR:
			/* base_addr is the start address to run */
			ret = ath10k_bmi_set_start(ar, base_addr);
			base_len = 0;
			अवरोध;
		हाल BMI_SGMTखाता_DONE:
			/* no more segment */
			base_len = 0;
			sgmt_end = true;
			ret = 0;
			अवरोध;
		हाल BMI_SGMTखाता_BDDATA:
		हाल BMI_SGMTखाता_EXEC:
			ath10k_warn(ar,
				    "firmware has unsupported segment:%d\n",
				    base_len);
			ret = -EINVAL;
			अवरोध;
		शेष:
			अगर (base_len > left) अणु
				/* sanity check */
				ath10k_warn(ar,
					    "firmware has invalid segment length, %d > %d\n",
					    base_len, left);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			ret = ath10k_hw_diag_segment_करोwnload(ar,
							      buf,
							      base_addr,
							      base_len);

			अगर (ret)
				ath10k_warn(ar,
					    "failed to download firmware via diag interface:%d\n",
					    ret);
			अवरोध;
		पूर्ण

		अगर (ret || sgmt_end)
			अवरोध;

		metadata = (काष्ठा bmi_segmented_metadata *)(buf + base_len);
		left -= base_len;
	पूर्ण

	अगर (ret == 0)
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "boot firmware fast diag download successfully.\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_rssi_enable(काष्ठा htt_resp *resp)
अणु
	वापस (resp->data_tx_completion.flags2 & HTT_TX_CMPL_FLAG_DATA_RSSI);
पूर्ण

अटल पूर्णांक ath10k_htt_tx_rssi_enable_wcn3990(काष्ठा htt_resp *resp)
अणु
	वापस (resp->data_tx_completion.flags2 &
		HTT_TX_DATA_RSSI_ENABLE_WCN3990);
पूर्ण

अटल पूर्णांक ath10k_get_htt_tx_data_rssi_pad(काष्ठा htt_resp *resp)
अणु
	काष्ठा htt_data_tx_completion_ext extd;
	पूर्णांक pad_bytes = 0;

	अगर (resp->data_tx_completion.flags2 & HTT_TX_DATA_APPEND_RETRIES)
		pad_bytes += माप(extd.a_retries) /
			     माप(extd.msdus_rssi[0]);

	अगर (resp->data_tx_completion.flags2 & HTT_TX_DATA_APPEND_TIMESTAMP)
		pad_bytes += माप(extd.t_stamp) / माप(extd.msdus_rssi[0]);

	वापस pad_bytes;
पूर्ण

स्थिर काष्ठा ath10k_hw_ops qca988x_ops = अणु
	.set_coverage_class = ath10k_hw_qca988x_set_coverage_class,
	.is_rssi_enable = ath10k_htt_tx_rssi_enable,
पूर्ण;

अटल पूर्णांक ath10k_qca99x0_rx_desc_get_l3_pad_bytes(काष्ठा htt_rx_desc *rxd)
अणु
	वापस MS(__le32_to_cpu(rxd->msdu_end.qca99x0.info1),
		  RX_MSDU_END_INFO1_L3_HDR_PAD);
पूर्ण

अटल bool ath10k_qca99x0_rx_desc_msdu_limit_error(काष्ठा htt_rx_desc *rxd)
अणु
	वापस !!(rxd->msdu_end.common.info0 &
		  __cpu_to_le32(RX_MSDU_END_INFO0_MSDU_LIMIT_ERR));
पूर्ण

स्थिर काष्ठा ath10k_hw_ops qca99x0_ops = अणु
	.rx_desc_get_l3_pad_bytes = ath10k_qca99x0_rx_desc_get_l3_pad_bytes,
	.rx_desc_get_msdu_limit_error = ath10k_qca99x0_rx_desc_msdu_limit_error,
	.is_rssi_enable = ath10k_htt_tx_rssi_enable,
पूर्ण;

स्थिर काष्ठा ath10k_hw_ops qca6174_ops = अणु
	.set_coverage_class = ath10k_hw_qca988x_set_coverage_class,
	.enable_pll_clk = ath10k_hw_qca6174_enable_pll_घड़ी,
	.is_rssi_enable = ath10k_htt_tx_rssi_enable,
पूर्ण;

स्थिर काष्ठा ath10k_hw_ops qca6174_sdio_ops = अणु
	.enable_pll_clk = ath10k_hw_qca6174_enable_pll_घड़ी,
पूर्ण;

स्थिर काष्ठा ath10k_hw_ops wcn3990_ops = अणु
	.tx_data_rssi_pad_bytes = ath10k_get_htt_tx_data_rssi_pad,
	.is_rssi_enable = ath10k_htt_tx_rssi_enable_wcn3990,
पूर्ण;
