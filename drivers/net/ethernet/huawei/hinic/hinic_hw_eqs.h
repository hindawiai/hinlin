<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_EQS_H
#घोषणा HINIC_HW_EQS_H

#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/sizes.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "hinic_hw_if.h"

#घोषणा HINIC_AEQ_CTRL_0_INT_IDX_SHIFT          0
#घोषणा HINIC_AEQ_CTRL_0_DMA_ATTR_SHIFT         12
#घोषणा HINIC_AEQ_CTRL_0_PCI_INTF_IDX_SHIFT     20
#घोषणा HINIC_AEQ_CTRL_0_INT_MODE_SHIFT         31

#घोषणा HINIC_AEQ_CTRL_0_INT_IDX_MASK           0x3FF
#घोषणा HINIC_AEQ_CTRL_0_DMA_ATTR_MASK          0x3F
#घोषणा HINIC_AEQ_CTRL_0_PCI_INTF_IDX_MASK      0x3
#घोषणा HINIC_AEQ_CTRL_0_INT_MODE_MASK          0x1

#घोषणा HINIC_AEQ_CTRL_0_SET(val, member)       \
			(((u32)(val) & HINIC_AEQ_CTRL_0_##member##_MASK) << \
			 HINIC_AEQ_CTRL_0_##member##_SHIFT)

#घोषणा HINIC_AEQ_CTRL_0_CLEAR(val, member)     \
			((val) & (~(HINIC_AEQ_CTRL_0_##member##_MASK \
			 << HINIC_AEQ_CTRL_0_##member##_SHIFT)))

#घोषणा HINIC_AEQ_CTRL_1_LEN_SHIFT              0
#घोषणा HINIC_AEQ_CTRL_1_ELEM_SIZE_SHIFT        24
#घोषणा HINIC_AEQ_CTRL_1_PAGE_SIZE_SHIFT        28

#घोषणा HINIC_AEQ_CTRL_1_LEN_MASK               0x1FFFFF
#घोषणा HINIC_AEQ_CTRL_1_ELEM_SIZE_MASK         0x3
#घोषणा HINIC_AEQ_CTRL_1_PAGE_SIZE_MASK         0xF

#घोषणा HINIC_AEQ_CTRL_1_SET(val, member)       \
			(((u32)(val) & HINIC_AEQ_CTRL_1_##member##_MASK) << \
			 HINIC_AEQ_CTRL_1_##member##_SHIFT)

#घोषणा HINIC_AEQ_CTRL_1_CLEAR(val, member)     \
			((val) & (~(HINIC_AEQ_CTRL_1_##member##_MASK \
			 << HINIC_AEQ_CTRL_1_##member##_SHIFT)))

#घोषणा HINIC_CEQ_CTRL_0_INTR_IDX_SHIFT         0
#घोषणा HINIC_CEQ_CTRL_0_DMA_ATTR_SHIFT         12
#घोषणा HINIC_CEQ_CTRL_0_KICK_THRESH_SHIFT      20
#घोषणा HINIC_CEQ_CTRL_0_PCI_INTF_IDX_SHIFT     24
#घोषणा HINIC_CEQ_CTRL_0_INTR_MODE_SHIFT        31

#घोषणा HINIC_CEQ_CTRL_0_INTR_IDX_MASK          0x3FF
#घोषणा HINIC_CEQ_CTRL_0_DMA_ATTR_MASK          0x3F
#घोषणा HINIC_CEQ_CTRL_0_KICK_THRESH_MASK       0xF
#घोषणा HINIC_CEQ_CTRL_0_PCI_INTF_IDX_MASK      0x3
#घोषणा HINIC_CEQ_CTRL_0_INTR_MODE_MASK         0x1

#घोषणा HINIC_CEQ_CTRL_0_SET(val, member)       \
			(((u32)(val) & HINIC_CEQ_CTRL_0_##member##_MASK) << \
			 HINIC_CEQ_CTRL_0_##member##_SHIFT)

#घोषणा HINIC_CEQ_CTRL_0_CLEAR(val, member)     \
			((val) & (~(HINIC_CEQ_CTRL_0_##member##_MASK \
			 << HINIC_CEQ_CTRL_0_##member##_SHIFT)))

#घोषणा HINIC_CEQ_CTRL_1_LEN_SHIFT              0
#घोषणा HINIC_CEQ_CTRL_1_PAGE_SIZE_SHIFT        28

#घोषणा HINIC_CEQ_CTRL_1_LEN_MASK               0x1FFFFF
#घोषणा HINIC_CEQ_CTRL_1_PAGE_SIZE_MASK         0xF

#घोषणा HINIC_CEQ_CTRL_1_SET(val, member)       \
			(((u32)(val) & HINIC_CEQ_CTRL_1_##member##_MASK) << \
			 HINIC_CEQ_CTRL_1_##member##_SHIFT)

#घोषणा HINIC_CEQ_CTRL_1_CLEAR(val, member)     \
			((val) & (~(HINIC_CEQ_CTRL_1_##member##_MASK \
			 << HINIC_CEQ_CTRL_1_##member##_SHIFT)))

#घोषणा HINIC_EQ_ELEM_DESC_TYPE_SHIFT           0
#घोषणा HINIC_EQ_ELEM_DESC_SRC_SHIFT            7
#घोषणा HINIC_EQ_ELEM_DESC_SIZE_SHIFT           8
#घोषणा HINIC_EQ_ELEM_DESC_WRAPPED_SHIFT        31

#घोषणा HINIC_EQ_ELEM_DESC_TYPE_MASK            0x7F
#घोषणा HINIC_EQ_ELEM_DESC_SRC_MASK             0x1
#घोषणा HINIC_EQ_ELEM_DESC_SIZE_MASK            0xFF
#घोषणा HINIC_EQ_ELEM_DESC_WRAPPED_MASK         0x1

#घोषणा HINIC_EQ_ELEM_DESC_SET(val, member)     \
			(((u32)(val) & HINIC_EQ_ELEM_DESC_##member##_MASK) << \
			 HINIC_EQ_ELEM_DESC_##member##_SHIFT)

#घोषणा HINIC_EQ_ELEM_DESC_GET(val, member)     \
			(((val) >> HINIC_EQ_ELEM_DESC_##member##_SHIFT) & \
			 HINIC_EQ_ELEM_DESC_##member##_MASK)

#घोषणा HINIC_EQ_CI_IDX_SHIFT                   0
#घोषणा HINIC_EQ_CI_WRAPPED_SHIFT               20
#घोषणा HINIC_EQ_CI_XOR_CHKSUM_SHIFT            24
#घोषणा HINIC_EQ_CI_INT_ARMED_SHIFT             31

#घोषणा HINIC_EQ_CI_IDX_MASK                    0xFFFFF
#घोषणा HINIC_EQ_CI_WRAPPED_MASK                0x1
#घोषणा HINIC_EQ_CI_XOR_CHKSUM_MASK             0xF
#घोषणा HINIC_EQ_CI_INT_ARMED_MASK              0x1

#घोषणा HINIC_EQ_CI_SET(val, member)            \
			(((u32)(val) & HINIC_EQ_CI_##member##_MASK) << \
			 HINIC_EQ_CI_##member##_SHIFT)

#घोषणा HINIC_EQ_CI_CLEAR(val, member)          \
			((val) & (~(HINIC_EQ_CI_##member##_MASK \
			 << HINIC_EQ_CI_##member##_SHIFT)))

#घोषणा HINIC_MAX_AEQS                  4
#घोषणा HINIC_MAX_CEQS                  32

#घोषणा HINIC_AEQE_SIZE                 64
#घोषणा HINIC_CEQE_SIZE                 4

#घोषणा HINIC_AEQE_DESC_SIZE            4
#घोषणा HINIC_AEQE_DATA_SIZE            \
			(HINIC_AEQE_SIZE - HINIC_AEQE_DESC_SIZE)

#घोषणा HINIC_DEFAULT_AEQ_LEN           64
#घोषणा HINIC_DEFAULT_CEQ_LEN           1024

#घोषणा HINIC_EQ_PAGE_SIZE              SZ_4K

#घोषणा HINIC_CEQ_ID_CMDQ               0

क्रमागत hinic_eq_type अणु
	HINIC_AEQ,
	HINIC_CEQ,
पूर्ण;

क्रमागत hinic_aeq_type अणु
	HINIC_MBX_FROM_FUNC = 1,
	HINIC_MSG_FROM_MGMT_CPU = 2,
	HINIC_MBX_SEND_RSLT = 5,
	HINIC_MAX_AEQ_EVENTS,
पूर्ण;

क्रमागत hinic_ceq_type अणु
	HINIC_CEQ_CMDQ = 3,

	HINIC_MAX_CEQ_EVENTS,
पूर्ण;

क्रमागत hinic_eqe_state अणु
	HINIC_EQE_ENABLED = BIT(0),
	HINIC_EQE_RUNNING = BIT(1),
पूर्ण;

काष्ठा hinic_aeq_elem अणु
	u8      data[HINIC_AEQE_DATA_SIZE];
	__be32  desc;
पूर्ण;

काष्ठा hinic_eq_work अणु
	काष्ठा work_काष्ठा      work;
	व्योम                    *data;
पूर्ण;

काष्ठा hinic_eq अणु
	काष्ठा hinic_hwअगर       *hwअगर;
	काष्ठा hinic_hwdev      *hwdev;
	क्रमागत hinic_eq_type      type;
	पूर्णांक                     q_id;
	u32                     q_len;
	u32                     page_size;

	u32                     cons_idx;
	पूर्णांक                     wrapped;

	माप_प्रकार                  elem_size;
	पूर्णांक                     num_pages;
	पूर्णांक                     num_elem_in_pg;

	काष्ठा msix_entry       msix_entry;
	अक्षर			irq_name[64];

	dma_addr_t              *dma_addr;
	व्योम                    **virt_addr;

	काष्ठा hinic_eq_work    aeq_work;

	काष्ठा tasklet_काष्ठा   ceq_tasklet;
पूर्ण;

काष्ठा hinic_hw_event_cb अणु
	व्योम    (*hwe_handler)(व्योम *handle, व्योम *data, u8 size);
	व्योम                    *handle;
	अचिन्हित दीर्घ           hwe_state;
पूर्ण;

काष्ठा hinic_aeqs अणु
	काष्ठा hinic_hwअगर       *hwअगर;

	काष्ठा hinic_eq         aeq[HINIC_MAX_AEQS];
	पूर्णांक                     num_aeqs;

	काष्ठा hinic_hw_event_cb hwe_cb[HINIC_MAX_AEQ_EVENTS];

	काष्ठा workqueue_काष्ठा *workq;
पूर्ण;

काष्ठा hinic_ceq_cb अणु
	व्योम    (*handler)(व्योम *handle, u32 ceqe_data);
	व्योम                    *handle;
	क्रमागत hinic_eqe_state    ceqe_state;
पूर्ण;

काष्ठा hinic_ceqs अणु
	काष्ठा hinic_hwअगर       *hwअगर;
	काष्ठा hinic_hwdev		*hwdev;
	काष्ठा hinic_eq         ceq[HINIC_MAX_CEQS];
	पूर्णांक                     num_ceqs;

	काष्ठा hinic_ceq_cb     ceq_cb[HINIC_MAX_CEQ_EVENTS];
पूर्ण;

व्योम hinic_aeq_रेजिस्टर_hw_cb(काष्ठा hinic_aeqs *aeqs,
			      क्रमागत hinic_aeq_type event, व्योम *handle,
			      व्योम (*hwe_handler)(व्योम *handle, व्योम *data,
						  u8 size));

व्योम hinic_aeq_unरेजिस्टर_hw_cb(काष्ठा hinic_aeqs *aeqs,
				क्रमागत hinic_aeq_type event);

व्योम hinic_ceq_रेजिस्टर_cb(काष्ठा hinic_ceqs *ceqs,
			   क्रमागत hinic_ceq_type event, व्योम *handle,
			   व्योम (*ceq_cb)(व्योम *handle, u32 ceqe_data));

व्योम hinic_ceq_unरेजिस्टर_cb(काष्ठा hinic_ceqs *ceqs,
			     क्रमागत hinic_ceq_type event);

पूर्णांक hinic_aeqs_init(काष्ठा hinic_aeqs *aeqs, काष्ठा hinic_hwअगर *hwअगर,
		    पूर्णांक num_aeqs, u32 q_len, u32 page_size,
		    काष्ठा msix_entry *msix_entries);

व्योम hinic_aeqs_मुक्त(काष्ठा hinic_aeqs *aeqs);

पूर्णांक hinic_ceqs_init(काष्ठा hinic_ceqs *ceqs, काष्ठा hinic_hwअगर *hwअगर,
		    पूर्णांक num_ceqs, u32 q_len, u32 page_size,
		    काष्ठा msix_entry *msix_entries);

व्योम hinic_ceqs_मुक्त(काष्ठा hinic_ceqs *ceqs);

व्योम hinic_dump_ceq_info(काष्ठा hinic_hwdev *hwdev);

व्योम hinic_dump_aeq_info(काष्ठा hinic_hwdev *hwdev);

#पूर्ण_अगर
