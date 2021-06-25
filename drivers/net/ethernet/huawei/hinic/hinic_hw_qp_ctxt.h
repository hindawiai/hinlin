<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_QP_CTXT_H
#घोषणा HINIC_HW_QP_CTXT_H

#समावेश <linux/types.h>

#समावेश "hinic_hw_cmdq.h"

#घोषणा HINIC_SQ_CTXT_CEQ_ATTR_GLOBAL_SQ_ID_SHIFT       13
#घोषणा HINIC_SQ_CTXT_CEQ_ATTR_EN_SHIFT                 23

#घोषणा HINIC_SQ_CTXT_CEQ_ATTR_GLOBAL_SQ_ID_MASK        0x3FF
#घोषणा HINIC_SQ_CTXT_CEQ_ATTR_EN_MASK                  0x1

#घोषणा HINIC_SQ_CTXT_CEQ_ATTR_SET(val, member)         \
	(((u32)(val) & HINIC_SQ_CTXT_CEQ_ATTR_##member##_MASK) \
	 << HINIC_SQ_CTXT_CEQ_ATTR_##member##_SHIFT)

#घोषणा HINIC_SQ_CTXT_CI_IDX_SHIFT                      11
#घोषणा HINIC_SQ_CTXT_CI_WRAPPED_SHIFT                  23

#घोषणा HINIC_SQ_CTXT_CI_IDX_MASK                       0xFFF
#घोषणा HINIC_SQ_CTXT_CI_WRAPPED_MASK                   0x1

#घोषणा HINIC_SQ_CTXT_CI_SET(val, member)               \
	(((u32)(val) & HINIC_SQ_CTXT_CI_##member##_MASK) \
	 << HINIC_SQ_CTXT_CI_##member##_SHIFT)

#घोषणा HINIC_SQ_CTXT_WQ_PAGE_HI_PFN_SHIFT              0
#घोषणा HINIC_SQ_CTXT_WQ_PAGE_PI_SHIFT                  20

#घोषणा HINIC_SQ_CTXT_WQ_PAGE_HI_PFN_MASK               0xFFFFF
#घोषणा HINIC_SQ_CTXT_WQ_PAGE_PI_MASK                   0xFFF

#घोषणा HINIC_SQ_CTXT_WQ_PAGE_SET(val, member)          \
	(((u32)(val) & HINIC_SQ_CTXT_WQ_PAGE_##member##_MASK) \
	 << HINIC_SQ_CTXT_WQ_PAGE_##member##_SHIFT)

#घोषणा HINIC_SQ_CTXT_PREF_CACHE_THRESHOLD_SHIFT        0
#घोषणा HINIC_SQ_CTXT_PREF_CACHE_MAX_SHIFT              14
#घोषणा HINIC_SQ_CTXT_PREF_CACHE_MIN_SHIFT              25

#घोषणा HINIC_SQ_CTXT_PREF_CACHE_THRESHOLD_MASK         0x3FFF
#घोषणा HINIC_SQ_CTXT_PREF_CACHE_MAX_MASK               0x7FF
#घोषणा HINIC_SQ_CTXT_PREF_CACHE_MIN_MASK               0x7F

#घोषणा HINIC_SQ_CTXT_PREF_WQ_HI_PFN_SHIFT              0
#घोषणा HINIC_SQ_CTXT_PREF_CI_SHIFT                     20

#घोषणा HINIC_SQ_CTXT_PREF_WQ_HI_PFN_MASK               0xFFFFF
#घोषणा HINIC_SQ_CTXT_PREF_CI_MASK                      0xFFF

#घोषणा HINIC_SQ_CTXT_PREF_SET(val, member)             \
	(((u32)(val) & HINIC_SQ_CTXT_PREF_##member##_MASK) \
	 << HINIC_SQ_CTXT_PREF_##member##_SHIFT)

#घोषणा HINIC_SQ_CTXT_WQ_BLOCK_HI_PFN_SHIFT             0

#घोषणा HINIC_SQ_CTXT_WQ_BLOCK_HI_PFN_MASK              0x7FFFFF

#घोषणा HINIC_SQ_CTXT_WQ_BLOCK_SET(val, member)         \
	(((u32)(val) & HINIC_SQ_CTXT_WQ_BLOCK_##member##_MASK) \
	 << HINIC_SQ_CTXT_WQ_BLOCK_##member##_SHIFT)

#घोषणा HINIC_RQ_CTXT_CEQ_ATTR_EN_SHIFT                 0
#घोषणा HINIC_RQ_CTXT_CEQ_ATTR_WRAPPED_SHIFT            1

#घोषणा HINIC_RQ_CTXT_CEQ_ATTR_EN_MASK                  0x1
#घोषणा HINIC_RQ_CTXT_CEQ_ATTR_WRAPPED_MASK             0x1

#घोषणा HINIC_RQ_CTXT_CEQ_ATTR_SET(val, member)         \
	(((u32)(val) & HINIC_RQ_CTXT_CEQ_ATTR_##member##_MASK) \
	 << HINIC_RQ_CTXT_CEQ_ATTR_##member##_SHIFT)

#घोषणा HINIC_RQ_CTXT_PI_IDX_SHIFT                      0
#घोषणा HINIC_RQ_CTXT_PI_INTR_SHIFT                     22

#घोषणा HINIC_RQ_CTXT_PI_IDX_MASK                       0xFFF
#घोषणा HINIC_RQ_CTXT_PI_INTR_MASK                      0x3FF

#घोषणा HINIC_RQ_CTXT_PI_SET(val, member)               \
	(((u32)(val) & HINIC_RQ_CTXT_PI_##member##_MASK) << \
	 HINIC_RQ_CTXT_PI_##member##_SHIFT)

#घोषणा HINIC_RQ_CTXT_WQ_PAGE_HI_PFN_SHIFT              0
#घोषणा HINIC_RQ_CTXT_WQ_PAGE_CI_SHIFT                  20

#घोषणा HINIC_RQ_CTXT_WQ_PAGE_HI_PFN_MASK               0xFFFFF
#घोषणा HINIC_RQ_CTXT_WQ_PAGE_CI_MASK                   0xFFF

#घोषणा HINIC_RQ_CTXT_WQ_PAGE_SET(val, member)          \
	(((u32)(val) & HINIC_RQ_CTXT_WQ_PAGE_##member##_MASK) << \
	 HINIC_RQ_CTXT_WQ_PAGE_##member##_SHIFT)

#घोषणा HINIC_RQ_CTXT_PREF_CACHE_THRESHOLD_SHIFT        0
#घोषणा HINIC_RQ_CTXT_PREF_CACHE_MAX_SHIFT              14
#घोषणा HINIC_RQ_CTXT_PREF_CACHE_MIN_SHIFT              25

#घोषणा HINIC_RQ_CTXT_PREF_CACHE_THRESHOLD_MASK         0x3FFF
#घोषणा HINIC_RQ_CTXT_PREF_CACHE_MAX_MASK               0x7FF
#घोषणा HINIC_RQ_CTXT_PREF_CACHE_MIN_MASK               0x7F

#घोषणा HINIC_RQ_CTXT_PREF_WQ_HI_PFN_SHIFT              0
#घोषणा HINIC_RQ_CTXT_PREF_CI_SHIFT                     20

#घोषणा HINIC_RQ_CTXT_PREF_WQ_HI_PFN_MASK               0xFFFFF
#घोषणा HINIC_RQ_CTXT_PREF_CI_MASK                      0xFFF

#घोषणा HINIC_RQ_CTXT_PREF_SET(val, member)             \
	(((u32)(val) & HINIC_RQ_CTXT_PREF_##member##_MASK) << \
	 HINIC_RQ_CTXT_PREF_##member##_SHIFT)

#घोषणा HINIC_RQ_CTXT_WQ_BLOCK_HI_PFN_SHIFT             0

#घोषणा HINIC_RQ_CTXT_WQ_BLOCK_HI_PFN_MASK              0x7FFFFF

#घोषणा HINIC_RQ_CTXT_WQ_BLOCK_SET(val, member)         \
	(((u32)(val) & HINIC_RQ_CTXT_WQ_BLOCK_##member##_MASK) << \
	 HINIC_RQ_CTXT_WQ_BLOCK_##member##_SHIFT)

#घोषणा HINIC_SQ_CTXT_SIZE(num_sqs) (माप(काष्ठा hinic_qp_ctxt_header) \
				     + (num_sqs) * माप(काष्ठा hinic_sq_ctxt))

#घोषणा HINIC_RQ_CTXT_SIZE(num_rqs) (माप(काष्ठा hinic_qp_ctxt_header) \
				     + (num_rqs) * माप(काष्ठा hinic_rq_ctxt))

#घोषणा HINIC_WQ_PAGE_PFN_SHIFT         12
#घोषणा HINIC_WQ_BLOCK_PFN_SHIFT        9

#घोषणा HINIC_WQ_PAGE_PFN(page_addr)    ((page_addr) >> HINIC_WQ_PAGE_PFN_SHIFT)
#घोषणा HINIC_WQ_BLOCK_PFN(page_addr)   ((page_addr) >> \
					 HINIC_WQ_BLOCK_PFN_SHIFT)

#घोषणा HINIC_Q_CTXT_MAX                \
		((HINIC_CMDQ_BUF_SIZE - माप(काष्ठा hinic_qp_ctxt_header)) \
		 / माप(काष्ठा hinic_sq_ctxt))

क्रमागत hinic_qp_ctxt_type अणु
	HINIC_QP_CTXT_TYPE_SQ,
	HINIC_QP_CTXT_TYPE_RQ
पूर्ण;

काष्ठा hinic_qp_ctxt_header अणु
	u16     num_queues;
	u16     queue_type;
	u32     addr_offset;
पूर्ण;

काष्ठा hinic_sq_ctxt अणु
	u32     ceq_attr;

	u32     ci_wrapped;

	u32     wq_hi_pfn_pi;
	u32     wq_lo_pfn;

	u32     pref_cache;
	u32     pref_wrapped;
	u32     pref_wq_hi_pfn_ci;
	u32     pref_wq_lo_pfn;

	u32     rsvd0;
	u32     rsvd1;

	u32     wq_block_hi_pfn;
	u32     wq_block_lo_pfn;
पूर्ण;

काष्ठा hinic_rq_ctxt अणु
	u32     ceq_attr;

	u32     pi_पूर्णांकr_attr;

	u32     wq_hi_pfn_ci;
	u32     wq_lo_pfn;

	u32     pref_cache;
	u32     pref_wrapped;

	u32     pref_wq_hi_pfn_ci;
	u32     pref_wq_lo_pfn;

	u32     pi_paddr_hi;
	u32     pi_paddr_lo;

	u32     wq_block_hi_pfn;
	u32     wq_block_lo_pfn;
पूर्ण;

काष्ठा hinic_clean_queue_ctxt अणु
	काष्ठा hinic_qp_ctxt_header	cmdq_hdr;
	u32				ctxt_size;
पूर्ण;

काष्ठा hinic_sq_ctxt_block अणु
	काष्ठा hinic_qp_ctxt_header hdr;
	काष्ठा hinic_sq_ctxt sq_ctxt[HINIC_Q_CTXT_MAX];
पूर्ण;

काष्ठा hinic_rq_ctxt_block अणु
	काष्ठा hinic_qp_ctxt_header hdr;
	काष्ठा hinic_rq_ctxt rq_ctxt[HINIC_Q_CTXT_MAX];
पूर्ण;

#पूर्ण_अगर
