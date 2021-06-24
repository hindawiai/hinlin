<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_IF_H
#घोषणा HINIC_HW_IF_H

#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा HINIC_PCIE_LINK_DOWN					0xFFFFFFFF

#घोषणा HINIC_DMA_ATTR_ST_SHIFT                                 0
#घोषणा HINIC_DMA_ATTR_AT_SHIFT                                 8
#घोषणा HINIC_DMA_ATTR_PH_SHIFT                                 10
#घोषणा HINIC_DMA_ATTR_NO_SNOOPING_SHIFT                        12
#घोषणा HINIC_DMA_ATTR_TPH_EN_SHIFT                             13

#घोषणा HINIC_DMA_ATTR_ST_MASK                                  0xFF
#घोषणा HINIC_DMA_ATTR_AT_MASK                                  0x3
#घोषणा HINIC_DMA_ATTR_PH_MASK                                  0x3
#घोषणा HINIC_DMA_ATTR_NO_SNOOPING_MASK                         0x1
#घोषणा HINIC_DMA_ATTR_TPH_EN_MASK                              0x1

#घोषणा HINIC_DMA_ATTR_SET(val, member)                         \
	(((u32)(val) & HINIC_DMA_ATTR_##member##_MASK) <<       \
	 HINIC_DMA_ATTR_##member##_SHIFT)

#घोषणा HINIC_DMA_ATTR_CLEAR(val, member)                       \
	((val) & (~(HINIC_DMA_ATTR_##member##_MASK              \
	 << HINIC_DMA_ATTR_##member##_SHIFT)))

#घोषणा HINIC_FA0_FUNC_IDX_SHIFT                                0
#घोषणा HINIC_FA0_PF_IDX_SHIFT                                  10
#घोषणा HINIC_FA0_PCI_INTF_IDX_SHIFT                            14
#घोषणा HINIC_FA0_VF_IN_PF_SHIFT				16
/* reserved members - off 16 */
#घोषणा HINIC_FA0_FUNC_TYPE_SHIFT                               24

#घोषणा HINIC_FA0_FUNC_IDX_MASK                                 0x3FF
#घोषणा HINIC_FA0_PF_IDX_MASK                                   0xF
#घोषणा HINIC_FA0_PCI_INTF_IDX_MASK                             0x3
#घोषणा HINIC_FA0_FUNC_TYPE_MASK                                0x1
#घोषणा HINIC_FA0_VF_IN_PF_MASK					0xFF

#घोषणा HINIC_FA0_GET(val, member)                              \
	(((val) >> HINIC_FA0_##member##_SHIFT) & HINIC_FA0_##member##_MASK)

#घोषणा HINIC_FA1_AEQS_PER_FUNC_SHIFT                           8
/* reserved members - off 10 */
#घोषणा HINIC_FA1_CEQS_PER_FUNC_SHIFT                           12
/* reserved members - off 15 */
#घोषणा HINIC_FA1_IRQS_PER_FUNC_SHIFT                           20
#घोषणा HINIC_FA1_DMA_ATTR_PER_FUNC_SHIFT                       24
/* reserved members - off 27 */
#घोषणा HINIC_FA1_MGMT_INIT_STATUS_SHIFT			30
#घोषणा HINIC_FA1_PF_INIT_STATUS_SHIFT				31

#घोषणा HINIC_FA1_AEQS_PER_FUNC_MASK                            0x3
#घोषणा HINIC_FA1_CEQS_PER_FUNC_MASK                            0x7
#घोषणा HINIC_FA1_IRQS_PER_FUNC_MASK                            0xF
#घोषणा HINIC_FA1_DMA_ATTR_PER_FUNC_MASK                        0x7
#घोषणा HINIC_FA1_MGMT_INIT_STATUS_MASK                         0x1
#घोषणा HINIC_FA1_PF_INIT_STATUS_MASK				0x1

#घोषणा HINIC_FA1_GET(val, member)                              \
	(((val) >> HINIC_FA1_##member##_SHIFT) & HINIC_FA1_##member##_MASK)

#घोषणा HINIC_FA2_GLOBAL_VF_ID_OF_PF_SHIFT	16
#घोषणा HINIC_FA2_GLOBAL_VF_ID_OF_PF_MASK	0x3FF

#घोषणा HINIC_FA2_GET(val, member)				\
	(((val) >> HINIC_FA2_##member##_SHIFT) & HINIC_FA2_##member##_MASK)

#घोषणा HINIC_FA4_OUTBOUND_STATE_SHIFT                          0
#घोषणा HINIC_FA4_DB_STATE_SHIFT                                1

#घोषणा HINIC_FA4_OUTBOUND_STATE_MASK                           0x1
#घोषणा HINIC_FA4_DB_STATE_MASK                                 0x1

#घोषणा HINIC_FA4_GET(val, member)                              \
	(((val) >> HINIC_FA4_##member##_SHIFT) & HINIC_FA4_##member##_MASK)

#घोषणा HINIC_FA4_SET(val, member)                              \
	((((u32)val) & HINIC_FA4_##member##_MASK) << HINIC_FA4_##member##_SHIFT)

#घोषणा HINIC_FA4_CLEAR(val, member)                            \
	((val) & (~(HINIC_FA4_##member##_MASK << HINIC_FA4_##member##_SHIFT)))

#घोषणा HINIC_FA5_PF_ACTION_SHIFT                               0
#घोषणा HINIC_FA5_PF_ACTION_MASK                                0xFFFF

#घोषणा HINIC_FA5_SET(val, member)                              \
	(((u32)(val) & HINIC_FA5_##member##_MASK) << HINIC_FA5_##member##_SHIFT)

#घोषणा HINIC_FA5_CLEAR(val, member)                            \
	((val) & (~(HINIC_FA5_##member##_MASK << HINIC_FA5_##member##_SHIFT)))

#घोषणा HINIC_PPF_ELECTION_IDX_SHIFT                            0
#घोषणा HINIC_PPF_ELECTION_IDX_MASK                             0x1F

#घोषणा HINIC_PPF_ELECTION_SET(val, member)                     \
	(((u32)(val) & HINIC_PPF_ELECTION_##member##_MASK) <<   \
	 HINIC_PPF_ELECTION_##member##_SHIFT)

#घोषणा HINIC_PPF_ELECTION_GET(val, member)                     \
	(((val) >> HINIC_PPF_ELECTION_##member##_SHIFT) &       \
	 HINIC_PPF_ELECTION_##member##_MASK)

#घोषणा HINIC_PPF_ELECTION_CLEAR(val, member)                   \
	((val) & (~(HINIC_PPF_ELECTION_##member##_MASK          \
	 << HINIC_PPF_ELECTION_##member##_SHIFT)))

#घोषणा HINIC_MSIX_PENDING_LIMIT_SHIFT                          0
#घोषणा HINIC_MSIX_COALESC_TIMER_SHIFT                          8
#घोषणा HINIC_MSIX_LLI_TIMER_SHIFT                              16
#घोषणा HINIC_MSIX_LLI_CREDIT_SHIFT                             24
#घोषणा HINIC_MSIX_RESEND_TIMER_SHIFT                           29

#घोषणा HINIC_MSIX_PENDING_LIMIT_MASK                           0xFF
#घोषणा HINIC_MSIX_COALESC_TIMER_MASK                           0xFF
#घोषणा HINIC_MSIX_LLI_TIMER_MASK                               0xFF
#घोषणा HINIC_MSIX_LLI_CREDIT_MASK                              0x1F
#घोषणा HINIC_MSIX_RESEND_TIMER_MASK                            0x7

#घोषणा HINIC_MSIX_ATTR_SET(val, member)                        \
	(((u32)(val) & HINIC_MSIX_##member##_MASK) <<           \
	 HINIC_MSIX_##member##_SHIFT)

#घोषणा HINIC_MSIX_ATTR_GET(val, member)                        \
	(((val) >> HINIC_MSIX_##member##_SHIFT) &               \
	 HINIC_MSIX_##member##_MASK)

#घोषणा HINIC_MSIX_CNT_RESEND_TIMER_SHIFT                       29

#घोषणा HINIC_MSIX_CNT_RESEND_TIMER_MASK                        0x1

#घोषणा HINIC_MSIX_CNT_SET(val, member)                         \
	(((u32)(val) & HINIC_MSIX_CNT_##member##_MASK) <<       \
	 HINIC_MSIX_CNT_##member##_SHIFT)

#घोषणा HINIC_HWIF_NUM_AEQS(hwअगर)       ((hwअगर)->attr.num_aeqs)
#घोषणा HINIC_HWIF_NUM_CEQS(hwअगर)       ((hwअगर)->attr.num_ceqs)
#घोषणा HINIC_HWIF_NUM_IRQS(hwअगर)       ((hwअगर)->attr.num_irqs)
#घोषणा HINIC_HWIF_FUNC_IDX(hwअगर)       ((hwअगर)->attr.func_idx)
#घोषणा HINIC_HWIF_PCI_INTF(hwअगर)       ((hwअगर)->attr.pci_पूर्णांकf_idx)
#घोषणा HINIC_HWIF_PF_IDX(hwअगर)         ((hwअगर)->attr.pf_idx)
#घोषणा HINIC_HWIF_PPF_IDX(hwअगर)        ((hwअगर)->attr.ppf_idx)

#घोषणा HINIC_FUNC_TYPE(hwअगर)           ((hwअगर)->attr.func_type)
#घोषणा HINIC_IS_VF(hwअगर)               (HINIC_FUNC_TYPE(hwअगर) == HINIC_VF)
#घोषणा HINIC_IS_PF(hwअगर)               (HINIC_FUNC_TYPE(hwअगर) == HINIC_PF)
#घोषणा HINIC_IS_PPF(hwअगर)              (HINIC_FUNC_TYPE(hwअगर) == HINIC_PPF)

#घोषणा HINIC_PCI_CFG_REGS_BAR          0
#घोषणा HINIC_PCI_INTR_REGS_BAR         2
#घोषणा HINIC_PCI_DB_BAR                4

#घोषणा HINIC_PCIE_ST_DISABLE           0
#घोषणा HINIC_PCIE_AT_DISABLE           0
#घोषणा HINIC_PCIE_PH_DISABLE           0

#घोषणा HINIC_EQ_MSIX_PENDING_LIMIT_DEFAULT     0       /* Disabled */
#घोषणा HINIC_EQ_MSIX_COALESC_TIMER_DEFAULT     0xFF    /* max */
#घोषणा HINIC_EQ_MSIX_LLI_TIMER_DEFAULT         0       /* Disabled */
#घोषणा HINIC_EQ_MSIX_LLI_CREDIT_LIMIT_DEFAULT  0       /* Disabled */
#घोषणा HINIC_EQ_MSIX_RESEND_TIMER_DEFAULT      7       /* max */

#घोषणा HINIC_PCI_MSIX_ENTRY_SIZE               16
#घोषणा HINIC_PCI_MSIX_ENTRY_VECTOR_CTRL        12
#घोषणा HINIC_PCI_MSIX_ENTRY_CTRL_MASKBIT       1

क्रमागत hinic_pcie_nosnoop अणु
	HINIC_PCIE_SNOOP        = 0,
	HINIC_PCIE_NO_SNOOP     = 1,
पूर्ण;

क्रमागत hinic_pcie_tph अणु
	HINIC_PCIE_TPH_DISABLE  = 0,
	HINIC_PCIE_TPH_ENABLE   = 1,
पूर्ण;

क्रमागत hinic_func_type अणु
	HINIC_PF        = 0,
	HINIC_VF	    = 1,
	HINIC_PPF       = 2,
पूर्ण;

क्रमागत hinic_mod_type अणु
	HINIC_MOD_COMM  = 0,    /* HW communication module */
	HINIC_MOD_L2NIC = 1,    /* L2NIC module */
	HINIC_MOD_CFGM  = 7,    /* Configuration module */
	HINIC_MOD_HILINK = 14,  /* Hilink module */
	HINIC_MOD_MAX   = 15
पूर्ण;

क्रमागत hinic_node_id अणु
	HINIC_NODE_ID_MGMT = 21,
पूर्ण;

क्रमागत hinic_pf_action अणु
	HINIC_PF_MGMT_INIT = 0x0,

	HINIC_PF_MGMT_ACTIVE = 0x11,
पूर्ण;

क्रमागत hinic_outbound_state अणु
	HINIC_OUTBOUND_ENABLE  = 0,
	HINIC_OUTBOUND_DISABLE = 1,
पूर्ण;

क्रमागत hinic_db_state अणु
	HINIC_DB_ENABLE  = 0,
	HINIC_DB_DISABLE = 1,
पूर्ण;

क्रमागत hinic_msix_state अणु
	HINIC_MSIX_ENABLE,
	HINIC_MSIX_DISABLE,
पूर्ण;

काष्ठा hinic_func_attr अणु
	u16                     func_idx;
	u8                      pf_idx;
	u8                      pci_पूर्णांकf_idx;

	क्रमागत hinic_func_type    func_type;

	u8                      ppf_idx;

	u16                     num_irqs;
	u8                      num_aeqs;
	u8                      num_ceqs;

	u8                      num_dma_attr;

	u16						global_vf_id_of_pf;
पूर्ण;

काष्ठा hinic_hwअगर अणु
	काष्ठा pci_dev          *pdev;
	व्योम __iomem            *cfg_regs_bar;
	व्योम __iomem		*पूर्णांकr_regs_base;

	काष्ठा hinic_func_attr  attr;
पूर्ण;

अटल अंतरभूत u32 hinic_hwअगर_पढ़ो_reg(काष्ठा hinic_hwअगर *hwअगर, u32 reg)
अणु
	u32 out = पढ़ोl(hwअगर->cfg_regs_bar + reg);

	वापस be32_to_cpu(*(__be32 *)&out);
पूर्ण

अटल अंतरभूत व्योम hinic_hwअगर_ग_लिखो_reg(काष्ठा hinic_hwअगर *hwअगर, u32 reg,
					u32 val)
अणु
	__be32 in = cpu_to_be32(val);

	ग_लिखोl(*(u32 *)&in, hwअगर->cfg_regs_bar + reg);
पूर्ण

पूर्णांक hinic_msix_attr_set(काष्ठा hinic_hwअगर *hwअगर, u16 msix_index,
			u8 pending_limit, u8 coalesc_समयr,
			u8 lli_समयr_cfg, u8 lli_credit_limit,
			u8 resend_समयr);

पूर्णांक hinic_msix_attr_get(काष्ठा hinic_hwअगर *hwअगर, u16 msix_index,
			u8 *pending_limit, u8 *coalesc_समयr_cfg,
			u8 *lli_समयr, u8 *lli_credit_limit,
			u8 *resend_समयr);

व्योम hinic_set_msix_state(काष्ठा hinic_hwअगर *hwअगर, u16 msix_idx,
			  क्रमागत hinic_msix_state flag);

पूर्णांक hinic_msix_attr_cnt_clear(काष्ठा hinic_hwअगर *hwअगर, u16 msix_index);

व्योम hinic_set_pf_action(काष्ठा hinic_hwअगर *hwअगर, क्रमागत hinic_pf_action action);

क्रमागत hinic_outbound_state hinic_outbound_state_get(काष्ठा hinic_hwअगर *hwअगर);

व्योम hinic_outbound_state_set(काष्ठा hinic_hwअगर *hwअगर,
			      क्रमागत hinic_outbound_state outbound_state);

क्रमागत hinic_db_state hinic_db_state_get(काष्ठा hinic_hwअगर *hwअगर);

व्योम hinic_db_state_set(काष्ठा hinic_hwअगर *hwअगर,
			क्रमागत hinic_db_state db_state);

u16 hinic_glb_pf_vf_offset(काष्ठा hinic_hwअगर *hwअगर);

u16 hinic_global_func_id_hw(काष्ठा hinic_hwअगर *hwअगर);

u16 hinic_pf_id_of_vf_hw(काष्ठा hinic_hwअगर *hwअगर);

पूर्णांक hinic_init_hwअगर(काष्ठा hinic_hwअगर *hwअगर, काष्ठा pci_dev *pdev);

व्योम hinic_मुक्त_hwअगर(काष्ठा hinic_hwअगर *hwअगर);

#पूर्ण_अगर
