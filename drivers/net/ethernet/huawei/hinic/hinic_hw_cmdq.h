<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_CMDQ_H
#घोषणा HINIC_CMDQ_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/pci.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wq.h"

#घोषणा HINIC_CMDQ_CTXT_CURR_WQE_PAGE_PFN_SHIFT         0
#घोषणा HINIC_CMDQ_CTXT_EQ_ID_SHIFT                     56
#घोषणा HINIC_CMDQ_CTXT_CEQ_ARM_SHIFT                   61
#घोषणा HINIC_CMDQ_CTXT_CEQ_EN_SHIFT                    62
#घोषणा HINIC_CMDQ_CTXT_WRAPPED_SHIFT                   63

#घोषणा HINIC_CMDQ_CTXT_CURR_WQE_PAGE_PFN_MASK          0xFFFFFFFFFFFFF
#घोषणा HINIC_CMDQ_CTXT_EQ_ID_MASK                      0x1F
#घोषणा HINIC_CMDQ_CTXT_CEQ_ARM_MASK                    0x1
#घोषणा HINIC_CMDQ_CTXT_CEQ_EN_MASK                     0x1
#घोषणा HINIC_CMDQ_CTXT_WRAPPED_MASK                    0x1

#घोषणा HINIC_CMDQ_CTXT_PAGE_INFO_SET(val, member)      \
			(((u64)(val) & HINIC_CMDQ_CTXT_##member##_MASK) \
			 << HINIC_CMDQ_CTXT_##member##_SHIFT)

#घोषणा HINIC_CMDQ_CTXT_PAGE_INFO_GET(val, member)	\
			(((u64)(val) >> HINIC_CMDQ_CTXT_##member##_SHIFT) \
			 & HINIC_CMDQ_CTXT_##member##_MASK)

#घोषणा HINIC_CMDQ_CTXT_PAGE_INFO_CLEAR(val, member)    \
			((val) & (~((u64)HINIC_CMDQ_CTXT_##member##_MASK \
			 << HINIC_CMDQ_CTXT_##member##_SHIFT)))

#घोषणा HINIC_CMDQ_CTXT_WQ_BLOCK_PFN_SHIFT              0
#घोषणा HINIC_CMDQ_CTXT_CI_SHIFT                        52

#घोषणा HINIC_CMDQ_CTXT_WQ_BLOCK_PFN_MASK               0xFFFFFFFFFFFFF
#घोषणा HINIC_CMDQ_CTXT_CI_MASK                         0xFFF

#घोषणा HINIC_CMDQ_CTXT_BLOCK_INFO_SET(val, member)     \
			(((u64)(val) & HINIC_CMDQ_CTXT_##member##_MASK) \
			 << HINIC_CMDQ_CTXT_##member##_SHIFT)

#घोषणा HINIC_CMDQ_CTXT_BLOCK_INFO_GET(val, member)	\
			(((u64)(val) >> HINIC_CMDQ_CTXT_##member##_SHIFT) \
			& HINIC_CMDQ_CTXT_##member##_MASK)

#घोषणा HINIC_CMDQ_CTXT_BLOCK_INFO_CLEAR(val, member)   \
			((val) & (~((u64)HINIC_CMDQ_CTXT_##member##_MASK \
			 << HINIC_CMDQ_CTXT_##member##_SHIFT)))

#घोषणा HINIC_SAVED_DATA_ARM_SHIFT                      31

#घोषणा HINIC_SAVED_DATA_ARM_MASK                       0x1

#घोषणा HINIC_SAVED_DATA_SET(val, member)               \
			(((u32)(val) & HINIC_SAVED_DATA_##member##_MASK) \
			 << HINIC_SAVED_DATA_##member##_SHIFT)

#घोषणा HINIC_SAVED_DATA_GET(val, member)               \
			(((val) >> HINIC_SAVED_DATA_##member##_SHIFT) \
			 & HINIC_SAVED_DATA_##member##_MASK)

#घोषणा HINIC_SAVED_DATA_CLEAR(val, member)             \
			((val) & (~(HINIC_SAVED_DATA_##member##_MASK \
			 << HINIC_SAVED_DATA_##member##_SHIFT)))

#घोषणा HINIC_CMDQ_DB_INFO_HI_PROD_IDX_SHIFT            0
#घोषणा HINIC_CMDQ_DB_INFO_PATH_SHIFT                   23
#घोषणा HINIC_CMDQ_DB_INFO_CMDQ_TYPE_SHIFT              24
#घोषणा HINIC_CMDQ_DB_INFO_DB_TYPE_SHIFT                27

#घोषणा HINIC_CMDQ_DB_INFO_HI_PROD_IDX_MASK             0xFF
#घोषणा HINIC_CMDQ_DB_INFO_PATH_MASK                    0x1
#घोषणा HINIC_CMDQ_DB_INFO_CMDQ_TYPE_MASK               0x7
#घोषणा HINIC_CMDQ_DB_INFO_DB_TYPE_MASK                 0x1F

#घोषणा HINIC_CMDQ_DB_INFO_SET(val, member)             \
			(((u32)(val) & HINIC_CMDQ_DB_INFO_##member##_MASK) \
			 << HINIC_CMDQ_DB_INFO_##member##_SHIFT)

#घोषणा HINIC_CMDQ_BUF_SIZE             2048

#घोषणा HINIC_CMDQ_BUF_HW_RSVD          8
#घोषणा HINIC_CMDQ_MAX_DATA_SIZE        (HINIC_CMDQ_BUF_SIZE - \
					 HINIC_CMDQ_BUF_HW_RSVD)

क्रमागत hinic_cmdq_type अणु
	HINIC_CMDQ_SYNC,

	HINIC_MAX_CMDQ_TYPES,
पूर्ण;

क्रमागत hinic_set_arm_qtype अणु
	HINIC_SET_ARM_CMDQ,
पूर्ण;

क्रमागत hinic_cmd_ack_type अणु
	HINIC_CMD_ACK_TYPE_CMDQ,
पूर्ण;

काष्ठा hinic_cmdq_buf अणु
	व्योम            *buf;
	dma_addr_t      dma_addr;
	माप_प्रकार          size;
पूर्ण;

काष्ठा hinic_cmdq_arm_bit अणु
	u32     q_type;
	u32     q_id;
पूर्ण;

काष्ठा hinic_cmdq_ctxt_info अणु
	u64     curr_wqe_page_pfn;
	u64     wq_block_pfn;
पूर्ण;

काष्ठा hinic_cmdq_ctxt अणु
	u8      status;
	u8      version;
	u8      rsvd0[6];

	u16     func_idx;
	u8      cmdq_type;
	u8      ppf_idx;

	u8      rsvd2[4];

	काष्ठा hinic_cmdq_ctxt_info ctxt_info;
पूर्ण;

काष्ठा hinic_cmdq अणु
	काष्ठा hinic_hwdev      *hwdev;

	काष्ठा hinic_wq         *wq;

	क्रमागत hinic_cmdq_type    cmdq_type;
	पूर्णांक                     wrapped;

	/* Lock क्रम keeping the करोorbell order */
	spinlock_t              cmdq_lock;

	काष्ठा completion       **करोne;
	पूर्णांक                     **errcode;

	/* करोorbell area */
	व्योम __iomem            *db_base;
पूर्ण;

काष्ठा hinic_cmdqs अणु
	काष्ठा hinic_hwअगर       *hwअगर;

	काष्ठा dma_pool         *cmdq_buf_pool;

	काष्ठा hinic_wq         *saved_wqs;

	काष्ठा hinic_cmdq_pages cmdq_pages;

	काष्ठा hinic_cmdq       cmdq[HINIC_MAX_CMDQ_TYPES];
पूर्ण;

पूर्णांक hinic_alloc_cmdq_buf(काष्ठा hinic_cmdqs *cmdqs,
			 काष्ठा hinic_cmdq_buf *cmdq_buf);

व्योम hinic_मुक्त_cmdq_buf(काष्ठा hinic_cmdqs *cmdqs,
			 काष्ठा hinic_cmdq_buf *cmdq_buf);

पूर्णांक hinic_cmdq_direct_resp(काष्ठा hinic_cmdqs *cmdqs,
			   क्रमागत hinic_mod_type mod, u8 cmd,
			   काष्ठा hinic_cmdq_buf *buf_in, u64 *out_param);

पूर्णांक hinic_set_arm_bit(काष्ठा hinic_cmdqs *cmdqs,
		      क्रमागत hinic_set_arm_qtype q_type, u32 q_id);

पूर्णांक hinic_init_cmdqs(काष्ठा hinic_cmdqs *cmdqs, काष्ठा hinic_hwअगर *hwअगर,
		     व्योम __iomem **db_area);

व्योम hinic_मुक्त_cmdqs(काष्ठा hinic_cmdqs *cmdqs);

#पूर्ण_अगर
