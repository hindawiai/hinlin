<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित __ICP_QAT_FW_LOADER_HANDLE_H__
#घोषणा __ICP_QAT_FW_LOADER_HANDLE_H__
#समावेश "icp_qat_uclo.h"

काष्ठा icp_qat_fw_loader_ae_data अणु
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक ustore_size;
	अचिन्हित पूर्णांक मुक्त_addr;
	अचिन्हित पूर्णांक मुक्त_size;
	अचिन्हित पूर्णांक live_ctx_mask;
पूर्ण;

काष्ठा icp_qat_fw_loader_hal_handle अणु
	काष्ठा icp_qat_fw_loader_ae_data aes[ICP_QAT_UCLO_MAX_AE];
	अचिन्हित पूर्णांक ae_mask;
	अचिन्हित पूर्णांक admin_ae_mask;
	अचिन्हित पूर्णांक slice_mask;
	अचिन्हित पूर्णांक revision_id;
	अचिन्हित पूर्णांक ae_max_num;
	अचिन्हित पूर्णांक upc_mask;
	अचिन्हित पूर्णांक max_ustore;
पूर्ण;

काष्ठा icp_qat_fw_loader_chip_info अणु
	bool sram_visible;
	bool nn;
	bool lm2lm3;
	u32 lm_size;
	u32 icp_rst_csr;
	u32 icp_rst_mask;
	u32 glb_clk_enable_csr;
	u32 misc_ctl_csr;
	u32 wakeup_event_val;
	bool fw_auth;
	bool css_3k;
	bool tgroup_share_ustore;
	u32 fcu_ctl_csr;
	u32 fcu_sts_csr;
	u32 fcu_dram_addr_hi;
	u32 fcu_dram_addr_lo;
	u32 fcu_loaded_ae_csr;
	u8 fcu_loaded_ae_pos;
पूर्ण;

काष्ठा icp_qat_fw_loader_handle अणु
	काष्ठा icp_qat_fw_loader_hal_handle *hal_handle;
	काष्ठा icp_qat_fw_loader_chip_info *chip_info;
	काष्ठा pci_dev *pci_dev;
	व्योम *obj_handle;
	व्योम *sobj_handle;
	व्योम *mobj_handle;
	अचिन्हित पूर्णांक cfg_ae_mask;
	व्योम __iomem *hal_sram_addr_v;
	व्योम __iomem *hal_cap_g_ctl_csr_addr_v;
	व्योम __iomem *hal_cap_ae_xfer_csr_addr_v;
	व्योम __iomem *hal_cap_ae_local_csr_addr_v;
	व्योम __iomem *hal_ep_csr_addr_v;
पूर्ण;

काष्ठा icp_firml_dram_desc अणु
	व्योम __iomem *dram_base_addr;
	व्योम *dram_base_addr_v;
	dma_addr_t dram_bus_addr;
	u64 dram_size;
पूर्ण;
#पूर्ण_अगर
