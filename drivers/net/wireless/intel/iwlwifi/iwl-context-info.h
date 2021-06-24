<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_context_info_file_h__
#घोषणा __iwl_context_info_file_h__

/* maximmum number of DRAM map entries supported by FW */
#घोषणा IWL_MAX_DRAM_ENTRY	64
#घोषणा CSR_CTXT_INFO_BA	0x40

/**
 * क्रमागत iwl_context_info_flags - Context inक्रमmation control flags
 * @IWL_CTXT_INFO_AUTO_FUNC_INIT: If set, FW will not रुको beक्रमe पूर्णांकerrupting
 *	the init करोne क्रम driver command that configures several प्रणाली modes
 * @IWL_CTXT_INFO_EARLY_DEBUG: enable early debug
 * @IWL_CTXT_INFO_ENABLE_CDMP: enable core dump
 * @IWL_CTXT_INFO_RB_CB_SIZE: mask of the RBD Cyclic Buffer Size
 *	exponent, the actual size is 2**value, valid sizes are 8-2048.
 *	The value is four bits दीर्घ. Maximum valid exponent is 12
 * @IWL_CTXT_INFO_TFD_FORMAT_LONG: use दीर्घ TFD Format (the
 *	शेष is लघु क्रमmat - not supported by the driver)
 * @IWL_CTXT_INFO_RB_SIZE: RB size mask
 *	(values are IWL_CTXT_INFO_RB_SIZE_*K)
 * @IWL_CTXT_INFO_RB_SIZE_1K: Value क्रम 1K RB size
 * @IWL_CTXT_INFO_RB_SIZE_2K: Value क्रम 2K RB size
 * @IWL_CTXT_INFO_RB_SIZE_4K: Value क्रम 4K RB size
 * @IWL_CTXT_INFO_RB_SIZE_8K: Value क्रम 8K RB size
 * @IWL_CTXT_INFO_RB_SIZE_12K: Value क्रम 12K RB size
 * @IWL_CTXT_INFO_RB_SIZE_16K: Value क्रम 16K RB size
 * @IWL_CTXT_INFO_RB_SIZE_20K: Value क्रम 20K RB size
 * @IWL_CTXT_INFO_RB_SIZE_24K: Value क्रम 24K RB size
 * @IWL_CTXT_INFO_RB_SIZE_28K: Value क्रम 28K RB size
 * @IWL_CTXT_INFO_RB_SIZE_32K: Value क्रम 32K RB size
 */
क्रमागत iwl_context_info_flags अणु
	IWL_CTXT_INFO_AUTO_FUNC_INIT	= 0x0001,
	IWL_CTXT_INFO_EARLY_DEBUG	= 0x0002,
	IWL_CTXT_INFO_ENABLE_CDMP	= 0x0004,
	IWL_CTXT_INFO_RB_CB_SIZE	= 0x00f0,
	IWL_CTXT_INFO_TFD_FORMAT_LONG	= 0x0100,
	IWL_CTXT_INFO_RB_SIZE		= 0x1e00,
	IWL_CTXT_INFO_RB_SIZE_1K	= 0x1,
	IWL_CTXT_INFO_RB_SIZE_2K	= 0x2,
	IWL_CTXT_INFO_RB_SIZE_4K	= 0x4,
	IWL_CTXT_INFO_RB_SIZE_8K	= 0x8,
	IWL_CTXT_INFO_RB_SIZE_12K	= 0x9,
	IWL_CTXT_INFO_RB_SIZE_16K	= 0xa,
	IWL_CTXT_INFO_RB_SIZE_20K	= 0xb,
	IWL_CTXT_INFO_RB_SIZE_24K	= 0xc,
	IWL_CTXT_INFO_RB_SIZE_28K	= 0xd,
	IWL_CTXT_INFO_RB_SIZE_32K	= 0xe,
पूर्ण;

/*
 * काष्ठा iwl_context_info_version - version काष्ठाure
 * @mac_id: SKU and revision id
 * @version: context inक्रमmation version id
 * @size: the size of the context inक्रमmation in DWs
 */
काष्ठा iwl_context_info_version अणु
	__le16 mac_id;
	__le16 version;
	__le16 size;
	__le16 reserved;
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_control - version काष्ठाure
 * @control_flags: context inक्रमmation flags see &क्रमागत iwl_context_info_flags
 */
काष्ठा iwl_context_info_control अणु
	__le32 control_flags;
	__le32 reserved;
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_dram - images DRAM map
 * each entry in the map represents a DRAM chunk of up to 32 KB
 * @umac_img: UMAC image DRAM map
 * @lmac_img: LMAC image DRAM map
 * @भव_img: paged image DRAM map
 */
काष्ठा iwl_context_info_dram अणु
	__le64 umac_img[IWL_MAX_DRAM_ENTRY];
	__le64 lmac_img[IWL_MAX_DRAM_ENTRY];
	__le64 भव_img[IWL_MAX_DRAM_ENTRY];
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_rbd_cfg - RBDs configuration
 * @मुक्त_rbd_addr: शेष queue मुक्त RB CB base address
 * @used_rbd_addr: शेष queue used RB CB base address
 * @status_wr_ptr: शेष queue used RB status ग_लिखो poपूर्णांकer
 */
काष्ठा iwl_context_info_rbd_cfg अणु
	__le64 मुक्त_rbd_addr;
	__le64 used_rbd_addr;
	__le64 status_wr_ptr;
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_hcmd_cfg  - command queue configuration
 * @cmd_queue_addr: address of command queue
 * @cmd_queue_size: number of entries
 */
काष्ठा iwl_context_info_hcmd_cfg अणु
	__le64 cmd_queue_addr;
	u8 cmd_queue_size;
	u8 reserved[7];
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_dump_cfg - Core Dump configuration
 * @core_dump_addr: core dump (debug DRAM address) start address
 * @core_dump_size: size, in DWs
 */
काष्ठा iwl_context_info_dump_cfg अणु
	__le64 core_dump_addr;
	__le32 core_dump_size;
	__le32 reserved;
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_pnvm_cfg - platक्रमm NVM data configuration
 * @platक्रमm_nvm_addr: Platक्रमm NVM data start address
 * @platक्रमm_nvm_size: size in DWs
 */
काष्ठा iwl_context_info_pnvm_cfg अणु
	__le64 platक्रमm_nvm_addr;
	__le32 platक्रमm_nvm_size;
	__le32 reserved;
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info_early_dbg_cfg - early debug configuration क्रम
 *	dumping DRAM addresses
 * @early_debug_addr: early debug start address
 * @early_debug_size: size in DWs
 */
काष्ठा iwl_context_info_early_dbg_cfg अणु
	__le64 early_debug_addr;
	__le32 early_debug_size;
	__le32 reserved;
पूर्ण __packed;

/*
 * काष्ठा iwl_context_info - device INIT configuration
 * @version: version inक्रमmation of context info and HW
 * @control: control flags of FH configurations
 * @rbd_cfg: शेष RX queue configuration
 * @hcmd_cfg: command queue configuration
 * @dump_cfg: core dump data
 * @edbg_cfg: early debug configuration
 * @pnvm_cfg: platक्रमm nvm configuration
 * @dram: firmware image addresses in DRAM
 */
काष्ठा iwl_context_info अणु
	काष्ठा iwl_context_info_version version;
	काष्ठा iwl_context_info_control control;
	__le64 reserved0;
	काष्ठा iwl_context_info_rbd_cfg rbd_cfg;
	काष्ठा iwl_context_info_hcmd_cfg hcmd_cfg;
	__le32 reserved1[4];
	काष्ठा iwl_context_info_dump_cfg dump_cfg;
	काष्ठा iwl_context_info_early_dbg_cfg edbg_cfg;
	काष्ठा iwl_context_info_pnvm_cfg pnvm_cfg;
	__le32 reserved2[16];
	काष्ठा iwl_context_info_dram dram;
	__le32 reserved3[16];
पूर्ण __packed;

पूर्णांक iwl_pcie_ctxt_info_init(काष्ठा iwl_trans *trans, स्थिर काष्ठा fw_img *fw);
व्योम iwl_pcie_ctxt_info_मुक्त(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_ctxt_info_मुक्त_paging(काष्ठा iwl_trans *trans);
पूर्णांक iwl_pcie_init_fw_sec(काष्ठा iwl_trans *trans,
			 स्थिर काष्ठा fw_img *fw,
			 काष्ठा iwl_context_info_dram *ctxt_dram);
पूर्णांक iwl_pcie_ctxt_info_alloc_dma(काष्ठा iwl_trans *trans,
				 स्थिर व्योम *data, u32 len,
				 काष्ठा iwl_dram_data *dram);

#पूर्ण_अगर /* __iwl_context_info_file_h__ */
