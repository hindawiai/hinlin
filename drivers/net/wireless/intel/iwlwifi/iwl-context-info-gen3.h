<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2018, 2020 Intel Corporation
 */
#अगर_अघोषित __iwl_context_info_file_gen3_h__
#घोषणा __iwl_context_info_file_gen3_h__

#समावेश "iwl-context-info.h"

#घोषणा CSR_CTXT_INFO_BOOT_CTRL         0x0
#घोषणा CSR_CTXT_INFO_ADDR              0x118
#घोषणा CSR_IML_DATA_ADDR               0x120
#घोषणा CSR_IML_SIZE_ADDR               0x128
#घोषणा CSR_IML_RESP_ADDR               0x12c

/* Set bit क्रम enabling स्वतःmatic function boot */
#घोषणा CSR_AUTO_FUNC_BOOT_ENA          BIT(1)
/* Set bit क्रम initiating function boot */
#घोषणा CSR_AUTO_FUNC_INIT              BIT(7)

/**
 * क्रमागत iwl_prph_scratch_mtr_क्रमmat - tfd size configuration
 * @IWL_PRPH_MTR_FORMAT_16B: 16 bit tfd
 * @IWL_PRPH_MTR_FORMAT_32B: 32 bit tfd
 * @IWL_PRPH_MTR_FORMAT_64B: 64 bit tfd
 * @IWL_PRPH_MTR_FORMAT_256B: 256 bit tfd
 */
क्रमागत iwl_prph_scratch_mtr_क्रमmat अणु
	IWL_PRPH_MTR_FORMAT_16B = 0x0,
	IWL_PRPH_MTR_FORMAT_32B = 0x40000,
	IWL_PRPH_MTR_FORMAT_64B = 0x80000,
	IWL_PRPH_MTR_FORMAT_256B = 0xC0000,
पूर्ण;

/**
 * क्रमागत iwl_prph_scratch_flags - PRPH scratch control flags
 * @IWL_PRPH_SCRATCH_EARLY_DEBUG_EN: enable early debug conf
 * @IWL_PRPH_SCRATCH_EDBG_DEST_DRAM: use DRAM, with size allocated
 *	in hwm config.
 * @IWL_PRPH_SCRATCH_EDBG_DEST_INTERNAL: use buffer on SRAM
 * @IWL_PRPH_SCRATCH_EDBG_DEST_ST_ARBITER: use st arbiter, मुख्यly क्रम
 *	multicomm.
 * @IWL_PRPH_SCRATCH_EDBG_DEST_TB22DTF: route debug data to SoC HW
 * @IWL_PRPH_SCTATCH_RB_SIZE_4K: Use 4K RB size (the शेष is 2K)
 * @IWL_PRPH_SCRATCH_MTR_MODE: क्रमmat used क्रम completion - 0: क्रम
 *	completion descriptor, 1 क्रम responses (legacy)
 * @IWL_PRPH_SCRATCH_MTR_FORMAT: a mask क्रम the size of the tfd.
 *	There are 4 optional values: 0: 16 bit, 1: 32 bit, 2: 64 bit,
 *	3: 256 bit.
 * @IWL_PRPH_SCRATCH_RB_SIZE_EXT_MASK: RB size full inक्रमmation, ignored
 *	by older firmware versions, so set IWL_PRPH_SCRATCH_RB_SIZE_4K
 *	appropriately; use the below values क्रम this.
 * @IWL_PRPH_SCRATCH_RB_SIZE_EXT_8K: 8kB RB size
 * @IWL_PRPH_SCRATCH_RB_SIZE_EXT_12K: 12kB RB size
 * @IWL_PRPH_SCRATCH_RB_SIZE_EXT_16K: 16kB RB size
 */
क्रमागत iwl_prph_scratch_flags अणु
	IWL_PRPH_SCRATCH_EARLY_DEBUG_EN		= BIT(4),
	IWL_PRPH_SCRATCH_EDBG_DEST_DRAM		= BIT(8),
	IWL_PRPH_SCRATCH_EDBG_DEST_INTERNAL	= BIT(9),
	IWL_PRPH_SCRATCH_EDBG_DEST_ST_ARBITER	= BIT(10),
	IWL_PRPH_SCRATCH_EDBG_DEST_TB22DTF	= BIT(11),
	IWL_PRPH_SCRATCH_RB_SIZE_4K		= BIT(16),
	IWL_PRPH_SCRATCH_MTR_MODE		= BIT(17),
	IWL_PRPH_SCRATCH_MTR_FORMAT		= BIT(18) | BIT(19),
	IWL_PRPH_SCRATCH_RB_SIZE_EXT_MASK	= 0xf << 20,
	IWL_PRPH_SCRATCH_RB_SIZE_EXT_8K		= 8 << 20,
	IWL_PRPH_SCRATCH_RB_SIZE_EXT_12K	= 9 << 20,
	IWL_PRPH_SCRATCH_RB_SIZE_EXT_16K	= 10 << 20,
पूर्ण;

/*
 * काष्ठा iwl_prph_scratch_version - version काष्ठाure
 * @mac_id: SKU and revision id
 * @version: prph scratch inक्रमmation version id
 * @size: the size of the context inक्रमmation in DWs
 * @reserved: reserved
 */
काष्ठा iwl_prph_scratch_version अणु
	__le16 mac_id;
	__le16 version;
	__le16 size;
	__le16 reserved;
पूर्ण __packed; /* PERIPH_SCRATCH_VERSION_S */

/*
 * काष्ठा iwl_prph_scratch_control - control काष्ठाure
 * @control_flags: context inक्रमmation flags see &क्रमागत iwl_prph_scratch_flags
 * @reserved: reserved
 */
काष्ठा iwl_prph_scratch_control अणु
	__le32 control_flags;
	__le32 reserved;
पूर्ण __packed; /* PERIPH_SCRATCH_CONTROL_S */

/*
 * काष्ठा iwl_prph_scratch_pnvm_cfg - ror config
 * @pnvm_base_addr: PNVM start address
 * @pnvm_size: PNVM size in DWs
 * @reserved: reserved
 */
काष्ठा iwl_prph_scratch_pnvm_cfg अणु
	__le64 pnvm_base_addr;
	__le32 pnvm_size;
	__le32 reserved;
पूर्ण __packed; /* PERIPH_SCRATCH_PNVM_CFG_S */

/*
 * काष्ठा iwl_prph_scratch_hwm_cfg - hwm config
 * @hwm_base_addr: hwm start address
 * @hwm_size: hwm size in DWs
 * @reserved: reserved
 */
काष्ठा iwl_prph_scratch_hwm_cfg अणु
	__le64 hwm_base_addr;
	__le32 hwm_size;
	__le32 reserved;
पूर्ण __packed; /* PERIPH_SCRATCH_HWM_CFG_S */

/*
 * काष्ठा iwl_prph_scratch_rbd_cfg - RBDs configuration
 * @मुक्त_rbd_addr: शेष queue मुक्त RB CB base address
 * @reserved: reserved
 */
काष्ठा iwl_prph_scratch_rbd_cfg अणु
	__le64 मुक्त_rbd_addr;
	__le32 reserved;
पूर्ण __packed; /* PERIPH_SCRATCH_RBD_CFG_S */

/*
 * काष्ठा iwl_prph_scratch_ctrl_cfg - prph scratch ctrl and config
 * @version: version inक्रमmation of context info and HW
 * @control: control flags of FH configurations
 * @pnvm_cfg: ror configuration
 * @hwm_cfg: hwm configuration
 * @rbd_cfg: शेष RX queue configuration
 */
काष्ठा iwl_prph_scratch_ctrl_cfg अणु
	काष्ठा iwl_prph_scratch_version version;
	काष्ठा iwl_prph_scratch_control control;
	काष्ठा iwl_prph_scratch_pnvm_cfg pnvm_cfg;
	काष्ठा iwl_prph_scratch_hwm_cfg hwm_cfg;
	काष्ठा iwl_prph_scratch_rbd_cfg rbd_cfg;
पूर्ण __packed; /* PERIPH_SCRATCH_CTRL_CFG_S */

/*
 * काष्ठा iwl_prph_scratch - peripheral scratch mapping
 * @ctrl_cfg: control and configuration of prph scratch
 * @dram: firmware images addresses in DRAM
 * @reserved: reserved
 */
काष्ठा iwl_prph_scratch अणु
	काष्ठा iwl_prph_scratch_ctrl_cfg ctrl_cfg;
	__le32 reserved[16];
	काष्ठा iwl_context_info_dram dram;
पूर्ण __packed; /* PERIPH_SCRATCH_S */

/*
 * काष्ठा iwl_prph_info - peripheral inक्रमmation
 * @boot_stage_mirror: reflects the value in the Boot Stage CSR रेजिस्टर
 * @ipc_status_mirror: reflects the value in the IPC Status CSR रेजिस्टर
 * @sleep_notअगर: indicates the peripheral sleep status
 * @reserved: reserved
 */
काष्ठा iwl_prph_info अणु
	__le32 boot_stage_mirror;
	__le32 ipc_status_mirror;
	__le32 sleep_notअगर;
	__le32 reserved;
पूर्ण __packed; /* PERIPH_INFO_S */

/*
 * काष्ठा iwl_context_info_gen3 - device INIT configuration
 * @version: version of the context inक्रमmation
 * @size: size of context inक्रमmation in DWs
 * @config: context in which the peripheral would execute - a subset of
 *	capability csr रेजिस्टर published by the peripheral
 * @prph_info_base_addr: the peripheral inक्रमmation काष्ठाure start address
 * @cr_head_idx_arr_base_addr: the completion ring head index array
 *	start address
 * @tr_tail_idx_arr_base_addr: the transfer ring tail index array
 *	start address
 * @cr_tail_idx_arr_base_addr: the completion ring tail index array
 *	start address
 * @tr_head_idx_arr_base_addr: the transfer ring head index array
 *	start address
 * @cr_idx_arr_size: number of entries in the completion ring index array
 * @tr_idx_arr_size: number of entries in the transfer ring index array
 * @mtr_base_addr: the message transfer ring start address
 * @mcr_base_addr: the message completion ring start address
 * @mtr_size: number of entries which the message transfer ring can hold
 * @mcr_size: number of entries which the message completion ring can hold
 * @mtr_करोorbell_vec: the करोorbell vector associated with the message
 *	transfer ring
 * @mcr_करोorbell_vec: the करोorbell vector associated with the message
 *	completion ring
 * @mtr_msi_vec: the MSI which shall be generated by the peripheral after
 *	completing a transfer descriptor in the message transfer ring
 * @mcr_msi_vec: the MSI which shall be generated by the peripheral after
 *	completing a completion descriptor in the message completion ring
 * @mtr_opt_header_size: the size of the optional header in the transfer
 *	descriptor associated with the message transfer ring in DWs
 * @mtr_opt_footer_size: the size of the optional footer in the transfer
 *	descriptor associated with the message transfer ring in DWs
 * @mcr_opt_header_size: the size of the optional header in the completion
 *	descriptor associated with the message completion ring in DWs
 * @mcr_opt_footer_size: the size of the optional footer in the completion
 *	descriptor associated with the message completion ring in DWs
 * @msg_rings_ctrl_flags: message rings control flags
 * @prph_info_msi_vec: the MSI which shall be generated by the peripheral
 *	after updating the Peripheral Inक्रमmation काष्ठाure
 * @prph_scratch_base_addr: the peripheral scratch काष्ठाure start address
 * @prph_scratch_size: the size of the peripheral scratch काष्ठाure in DWs
 * @reserved: reserved
 */
काष्ठा iwl_context_info_gen3 अणु
	__le16 version;
	__le16 size;
	__le32 config;
	__le64 prph_info_base_addr;
	__le64 cr_head_idx_arr_base_addr;
	__le64 tr_tail_idx_arr_base_addr;
	__le64 cr_tail_idx_arr_base_addr;
	__le64 tr_head_idx_arr_base_addr;
	__le16 cr_idx_arr_size;
	__le16 tr_idx_arr_size;
	__le64 mtr_base_addr;
	__le64 mcr_base_addr;
	__le16 mtr_size;
	__le16 mcr_size;
	__le16 mtr_करोorbell_vec;
	__le16 mcr_करोorbell_vec;
	__le16 mtr_msi_vec;
	__le16 mcr_msi_vec;
	u8 mtr_opt_header_size;
	u8 mtr_opt_footer_size;
	u8 mcr_opt_header_size;
	u8 mcr_opt_footer_size;
	__le16 msg_rings_ctrl_flags;
	__le16 prph_info_msi_vec;
	__le64 prph_scratch_base_addr;
	__le32 prph_scratch_size;
	__le32 reserved;
पूर्ण __packed; /* IPC_CONTEXT_INFO_S */

पूर्णांक iwl_pcie_ctxt_info_gen3_init(काष्ठा iwl_trans *trans,
				 स्थिर काष्ठा fw_img *fw);
व्योम iwl_pcie_ctxt_info_gen3_मुक्त(काष्ठा iwl_trans *trans);

पूर्णांक iwl_trans_pcie_ctx_info_gen3_set_pnvm(काष्ठा iwl_trans *trans,
					  स्थिर व्योम *data, u32 len);

#पूर्ण_अगर /* __iwl_context_info_file_gen3_h__ */
