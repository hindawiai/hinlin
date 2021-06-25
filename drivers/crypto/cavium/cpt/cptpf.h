<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#अगर_अघोषित __CPTPF_H
#घोषणा __CPTPF_H

#समावेश "cpt_common.h"

#घोषणा CSR_DELAY 30
#घोषणा CPT_MAX_CORE_GROUPS 8
#घोषणा CPT_MAX_SE_CORES 10
#घोषणा CPT_MAX_AE_CORES 6
#घोषणा CPT_MAX_TOTAL_CORES (CPT_MAX_SE_CORES + CPT_MAX_AE_CORES)
#घोषणा CPT_MAX_VF_NUM 16
#घोषणा	CPT_PF_MSIX_VECTORS 3
#घोषणा CPT_PF_INT_VEC_E_MBOXX(a) (0x02 + (a))
#घोषणा CPT_UCODE_VERSION_SZ 32
काष्ठा cpt_device;

काष्ठा microcode अणु
	u8 is_mc_valid;
	u8 is_ae;
	u8 group;
	u8 num_cores;
	u32 code_size;
	u64 core_mask;
	u8 version[CPT_UCODE_VERSION_SZ];
	/* Base info */
	dma_addr_t phys_base;
	व्योम *code;
पूर्ण;

काष्ठा cpt_vf_info अणु
	u8 state;
	u8 priority;
	u8 id;
	u32 qlen;
पूर्ण;

/**
 * cpt device काष्ठाure
 */
काष्ठा cpt_device अणु
	u16 flags;	/* Flags to hold device status bits */
	u8 num_vf_en; /* Number of VFs enabled (0...CPT_MAX_VF_NUM) */
	काष्ठा cpt_vf_info vfinfo[CPT_MAX_VF_NUM]; /* Per VF info */

	व्योम __iomem *reg_base; /* Register start address */
	काष्ठा pci_dev *pdev; /* pci device handle */

	काष्ठा microcode mcode[CPT_MAX_CORE_GROUPS];
	u8 next_mc_idx; /* next microcode index */
	u8 next_group;
	u8 max_se_cores;
	u8 max_ae_cores;
पूर्ण;

व्योम cpt_mbox_पूर्णांकr_handler(काष्ठा cpt_device *cpt, पूर्णांक mbx);
#पूर्ण_अगर /* __CPTPF_H */
