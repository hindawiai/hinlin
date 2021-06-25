<शैली गुरु>
/*
 * Copyright (C) 2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * Broadcom FlexRM Mailbox Driver
 *
 * Each Broadcom FlexSparx4 offload engine is implemented as an
 * extension to Broadcom FlexRM ring manager. The FlexRM ring
 * manager provides a set of rings which can be used to submit
 * work to a FlexSparx4 offload engine.
 *
 * This driver creates a mailbox controller using a set of FlexRM
 * rings where each mailbox channel represents a separate FlexRM ring.
 */

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mailbox/brcm-message.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

/* ====== FlexRM रेजिस्टर defines ===== */

/* FlexRM configuration */
#घोषणा RING_REGS_SIZE					0x10000
#घोषणा RING_DESC_SIZE					8
#घोषणा RING_DESC_INDEX(offset)				\
			((offset) / RING_DESC_SIZE)
#घोषणा RING_DESC_OFFSET(index)				\
			((index) * RING_DESC_SIZE)
#घोषणा RING_MAX_REQ_COUNT				1024
#घोषणा RING_BD_ALIGN_ORDER				12
#घोषणा RING_BD_ALIGN_CHECK(addr)			\
			(!((addr) & ((0x1 << RING_BD_ALIGN_ORDER) - 1)))
#घोषणा RING_BD_TOGGLE_INVALID(offset)			\
			(((offset) >> RING_BD_ALIGN_ORDER) & 0x1)
#घोषणा RING_BD_TOGGLE_VALID(offset)			\
			(!RING_BD_TOGGLE_INVALID(offset))
#घोषणा RING_BD_DESC_PER_REQ				32
#घोषणा RING_BD_DESC_COUNT				\
			(RING_MAX_REQ_COUNT * RING_BD_DESC_PER_REQ)
#घोषणा RING_BD_SIZE					\
			(RING_BD_DESC_COUNT * RING_DESC_SIZE)
#घोषणा RING_CMPL_ALIGN_ORDER				13
#घोषणा RING_CMPL_DESC_COUNT				RING_MAX_REQ_COUNT
#घोषणा RING_CMPL_SIZE					\
			(RING_CMPL_DESC_COUNT * RING_DESC_SIZE)
#घोषणा RING_VER_MAGIC					0x76303031

/* Per-Ring रेजिस्टर offsets */
#घोषणा RING_VER					0x000
#घोषणा RING_BD_START_ADDR				0x004
#घोषणा RING_BD_READ_PTR				0x008
#घोषणा RING_BD_WRITE_PTR				0x00c
#घोषणा RING_BD_READ_PTR_DDR_LS				0x010
#घोषणा RING_BD_READ_PTR_DDR_MS				0x014
#घोषणा RING_CMPL_START_ADDR				0x018
#घोषणा RING_CMPL_WRITE_PTR				0x01c
#घोषणा RING_NUM_REQ_RECV_LS				0x020
#घोषणा RING_NUM_REQ_RECV_MS				0x024
#घोषणा RING_NUM_REQ_TRANS_LS				0x028
#घोषणा RING_NUM_REQ_TRANS_MS				0x02c
#घोषणा RING_NUM_REQ_OUTSTAND				0x030
#घोषणा RING_CONTROL					0x034
#घोषणा RING_FLUSH_DONE					0x038
#घोषणा RING_MSI_ADDR_LS				0x03c
#घोषणा RING_MSI_ADDR_MS				0x040
#घोषणा RING_MSI_CONTROL				0x048
#घोषणा RING_BD_READ_PTR_DDR_CONTROL			0x04c
#घोषणा RING_MSI_DATA_VALUE				0x064

/* Register RING_BD_START_ADDR fields */
#घोषणा BD_LAST_UPDATE_HW_SHIFT				28
#घोषणा BD_LAST_UPDATE_HW_MASK				0x1
#घोषणा BD_START_ADDR_VALUE(pa)				\
	((u32)((((dma_addr_t)(pa)) >> RING_BD_ALIGN_ORDER) & 0x0fffffff))
#घोषणा BD_START_ADDR_DECODE(val)			\
	((dma_addr_t)((val) & 0x0fffffff) << RING_BD_ALIGN_ORDER)

/* Register RING_CMPL_START_ADDR fields */
#घोषणा CMPL_START_ADDR_VALUE(pa)			\
	((u32)((((u64)(pa)) >> RING_CMPL_ALIGN_ORDER) & 0x07ffffff))

/* Register RING_CONTROL fields */
#घोषणा CONTROL_MASK_DISABLE_CONTROL			12
#घोषणा CONTROL_FLUSH_SHIFT				5
#घोषणा CONTROL_ACTIVE_SHIFT				4
#घोषणा CONTROL_RATE_ADAPT_MASK				0xf
#घोषणा CONTROL_RATE_DYNAMIC				0x0
#घोषणा CONTROL_RATE_FAST				0x8
#घोषणा CONTROL_RATE_MEDIUM				0x9
#घोषणा CONTROL_RATE_SLOW				0xa
#घोषणा CONTROL_RATE_IDLE				0xb

/* Register RING_FLUSH_DONE fields */
#घोषणा FLUSH_DONE_MASK					0x1

/* Register RING_MSI_CONTROL fields */
#घोषणा MSI_TIMER_VAL_SHIFT				16
#घोषणा MSI_TIMER_VAL_MASK				0xffff
#घोषणा MSI_ENABLE_SHIFT				15
#घोषणा MSI_ENABLE_MASK					0x1
#घोषणा MSI_COUNT_SHIFT					0
#घोषणा MSI_COUNT_MASK					0x3ff

/* Register RING_BD_READ_PTR_DDR_CONTROL fields */
#घोषणा BD_READ_PTR_DDR_TIMER_VAL_SHIFT			16
#घोषणा BD_READ_PTR_DDR_TIMER_VAL_MASK			0xffff
#घोषणा BD_READ_PTR_DDR_ENABLE_SHIFT			15
#घोषणा BD_READ_PTR_DDR_ENABLE_MASK			0x1

/* ====== FlexRM ring descriptor defines ===== */

/* Completion descriptor क्रमmat */
#घोषणा CMPL_OPAQUE_SHIFT			0
#घोषणा CMPL_OPAQUE_MASK			0xffff
#घोषणा CMPL_ENGINE_STATUS_SHIFT		16
#घोषणा CMPL_ENGINE_STATUS_MASK			0xffff
#घोषणा CMPL_DME_STATUS_SHIFT			32
#घोषणा CMPL_DME_STATUS_MASK			0xffff
#घोषणा CMPL_RM_STATUS_SHIFT			48
#घोषणा CMPL_RM_STATUS_MASK			0xffff

/* Completion DME status code */
#घोषणा DME_STATUS_MEM_COR_ERR			BIT(0)
#घोषणा DME_STATUS_MEM_UCOR_ERR			BIT(1)
#घोषणा DME_STATUS_FIFO_UNDERFLOW		BIT(2)
#घोषणा DME_STATUS_FIFO_OVERFLOW		BIT(3)
#घोषणा DME_STATUS_RRESP_ERR			BIT(4)
#घोषणा DME_STATUS_BRESP_ERR			BIT(5)
#घोषणा DME_STATUS_ERROR_MASK			(DME_STATUS_MEM_COR_ERR | \
						 DME_STATUS_MEM_UCOR_ERR | \
						 DME_STATUS_FIFO_UNDERFLOW | \
						 DME_STATUS_FIFO_OVERFLOW | \
						 DME_STATUS_RRESP_ERR | \
						 DME_STATUS_BRESP_ERR)

/* Completion RM status code */
#घोषणा RM_STATUS_CODE_SHIFT			0
#घोषणा RM_STATUS_CODE_MASK			0x3ff
#घोषणा RM_STATUS_CODE_GOOD			0x0
#घोषणा RM_STATUS_CODE_AE_TIMEOUT		0x3ff

/* General descriptor क्रमmat */
#घोषणा DESC_TYPE_SHIFT				60
#घोषणा DESC_TYPE_MASK				0xf
#घोषणा DESC_PAYLOAD_SHIFT			0
#घोषणा DESC_PAYLOAD_MASK			0x0fffffffffffffff

/* Null descriptor क्रमmat  */
#घोषणा शून्य_TYPE				0
#घोषणा शून्य_TOGGLE_SHIFT			58
#घोषणा शून्य_TOGGLE_MASK			0x1

/* Header descriptor क्रमmat */
#घोषणा HEADER_TYPE				1
#घोषणा HEADER_TOGGLE_SHIFT			58
#घोषणा HEADER_TOGGLE_MASK			0x1
#घोषणा HEADER_ENDPKT_SHIFT			57
#घोषणा HEADER_ENDPKT_MASK			0x1
#घोषणा HEADER_STARTPKT_SHIFT			56
#घोषणा HEADER_STARTPKT_MASK			0x1
#घोषणा HEADER_BDCOUNT_SHIFT			36
#घोषणा HEADER_BDCOUNT_MASK			0x1f
#घोषणा HEADER_BDCOUNT_MAX			HEADER_BDCOUNT_MASK
#घोषणा HEADER_FLAGS_SHIFT			16
#घोषणा HEADER_FLAGS_MASK			0xffff
#घोषणा HEADER_OPAQUE_SHIFT			0
#घोषणा HEADER_OPAQUE_MASK			0xffff

/* Source (SRC) descriptor क्रमmat */
#घोषणा SRC_TYPE				2
#घोषणा SRC_LENGTH_SHIFT			44
#घोषणा SRC_LENGTH_MASK				0xffff
#घोषणा SRC_ADDR_SHIFT				0
#घोषणा SRC_ADDR_MASK				0x00000fffffffffff

/* Destination (DST) descriptor क्रमmat */
#घोषणा DST_TYPE				3
#घोषणा DST_LENGTH_SHIFT			44
#घोषणा DST_LENGTH_MASK				0xffff
#घोषणा DST_ADDR_SHIFT				0
#घोषणा DST_ADDR_MASK				0x00000fffffffffff

/* Immediate (IMM) descriptor क्रमmat */
#घोषणा IMM_TYPE				4
#घोषणा IMM_DATA_SHIFT				0
#घोषणा IMM_DATA_MASK				0x0fffffffffffffff

/* Next poपूर्णांकer (NPTR) descriptor क्रमmat */
#घोषणा NPTR_TYPE				5
#घोषणा NPTR_TOGGLE_SHIFT			58
#घोषणा NPTR_TOGGLE_MASK			0x1
#घोषणा NPTR_ADDR_SHIFT				0
#घोषणा NPTR_ADDR_MASK				0x00000fffffffffff

/* Mega source (MSRC) descriptor क्रमmat */
#घोषणा MSRC_TYPE				6
#घोषणा MSRC_LENGTH_SHIFT			44
#घोषणा MSRC_LENGTH_MASK			0xffff
#घोषणा MSRC_ADDR_SHIFT				0
#घोषणा MSRC_ADDR_MASK				0x00000fffffffffff

/* Mega destination (MDST) descriptor क्रमmat */
#घोषणा MDST_TYPE				7
#घोषणा MDST_LENGTH_SHIFT			44
#घोषणा MDST_LENGTH_MASK			0xffff
#घोषणा MDST_ADDR_SHIFT				0
#घोषणा MDST_ADDR_MASK				0x00000fffffffffff

/* Source with tlast (SRCT) descriptor क्रमmat */
#घोषणा SRCT_TYPE				8
#घोषणा SRCT_LENGTH_SHIFT			44
#घोषणा SRCT_LENGTH_MASK			0xffff
#घोषणा SRCT_ADDR_SHIFT				0
#घोषणा SRCT_ADDR_MASK				0x00000fffffffffff

/* Destination with tlast (DSTT) descriptor क्रमmat */
#घोषणा DSTT_TYPE				9
#घोषणा DSTT_LENGTH_SHIFT			44
#घोषणा DSTT_LENGTH_MASK			0xffff
#घोषणा DSTT_ADDR_SHIFT				0
#घोषणा DSTT_ADDR_MASK				0x00000fffffffffff

/* Immediate with tlast (IMMT) descriptor क्रमmat */
#घोषणा IMMT_TYPE				10
#घोषणा IMMT_DATA_SHIFT				0
#घोषणा IMMT_DATA_MASK				0x0fffffffffffffff

/* Descriptor helper macros */
#घोषणा DESC_DEC(_d, _s, _m)			(((_d) >> (_s)) & (_m))
#घोषणा DESC_ENC(_d, _v, _s, _m)		\
			करो अणु \
				(_d) &= ~((u64)(_m) << (_s)); \
				(_d) |= (((u64)(_v) & (_m)) << (_s)); \
			पूर्ण जबतक (0)

/* ====== FlexRM data काष्ठाures ===== */

काष्ठा flexrm_ring अणु
	/* Unरक्षित members */
	पूर्णांक num;
	काष्ठा flexrm_mbox *mbox;
	व्योम __iomem *regs;
	bool irq_requested;
	अचिन्हित पूर्णांक irq;
	cpumask_t irq_aff_hपूर्णांक;
	अचिन्हित पूर्णांक msi_समयr_val;
	अचिन्हित पूर्णांक msi_count_threshold;
	काष्ठा brcm_message *requests[RING_MAX_REQ_COUNT];
	व्योम *bd_base;
	dma_addr_t bd_dma_base;
	u32 bd_ग_लिखो_offset;
	व्योम *cmpl_base;
	dma_addr_t cmpl_dma_base;
	/* Atomic stats */
	atomic_t msg_send_count;
	atomic_t msg_cmpl_count;
	/* Protected members */
	spinlock_t lock;
	DECLARE_BITMAP(requests_bmap, RING_MAX_REQ_COUNT);
	u32 cmpl_पढ़ो_offset;
पूर्ण;

काष्ठा flexrm_mbox अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	u32 num_rings;
	काष्ठा flexrm_ring *rings;
	काष्ठा dma_pool *bd_pool;
	काष्ठा dma_pool *cmpl_pool;
	काष्ठा dentry *root;
	काष्ठा mbox_controller controller;
पूर्ण;

/* ====== FlexRM ring descriptor helper routines ===== */

अटल u64 flexrm_पढ़ो_desc(व्योम *desc_ptr)
अणु
	वापस le64_to_cpu(*((u64 *)desc_ptr));
पूर्ण

अटल व्योम flexrm_ग_लिखो_desc(व्योम *desc_ptr, u64 desc)
अणु
	*((u64 *)desc_ptr) = cpu_to_le64(desc);
पूर्ण

अटल u32 flexrm_cmpl_desc_to_reqid(u64 cmpl_desc)
अणु
	वापस (u32)(cmpl_desc & CMPL_OPAQUE_MASK);
पूर्ण

अटल पूर्णांक flexrm_cmpl_desc_to_error(u64 cmpl_desc)
अणु
	u32 status;

	status = DESC_DEC(cmpl_desc, CMPL_DME_STATUS_SHIFT,
			  CMPL_DME_STATUS_MASK);
	अगर (status & DME_STATUS_ERROR_MASK)
		वापस -EIO;

	status = DESC_DEC(cmpl_desc, CMPL_RM_STATUS_SHIFT,
			  CMPL_RM_STATUS_MASK);
	status &= RM_STATUS_CODE_MASK;
	अगर (status == RM_STATUS_CODE_AE_TIMEOUT)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल bool flexrm_is_next_table_desc(व्योम *desc_ptr)
अणु
	u64 desc = flexrm_पढ़ो_desc(desc_ptr);
	u32 type = DESC_DEC(desc, DESC_TYPE_SHIFT, DESC_TYPE_MASK);

	वापस (type == NPTR_TYPE) ? true : false;
पूर्ण

अटल u64 flexrm_next_table_desc(u32 toggle, dma_addr_t next_addr)
अणु
	u64 desc = 0;

	DESC_ENC(desc, NPTR_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggle, NPTR_TOGGLE_SHIFT, NPTR_TOGGLE_MASK);
	DESC_ENC(desc, next_addr, NPTR_ADDR_SHIFT, NPTR_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_null_desc(u32 toggle)
अणु
	u64 desc = 0;

	DESC_ENC(desc, शून्य_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggle, शून्य_TOGGLE_SHIFT, शून्य_TOGGLE_MASK);

	वापस desc;
पूर्ण

अटल u32 flexrm_estimate_header_desc_count(u32 nhcnt)
अणु
	u32 hcnt = nhcnt / HEADER_BDCOUNT_MAX;

	अगर (!(nhcnt % HEADER_BDCOUNT_MAX))
		hcnt += 1;

	वापस hcnt;
पूर्ण

अटल व्योम flexrm_flip_header_toggle(व्योम *desc_ptr)
अणु
	u64 desc = flexrm_पढ़ो_desc(desc_ptr);

	अगर (desc & ((u64)0x1 << HEADER_TOGGLE_SHIFT))
		desc &= ~((u64)0x1 << HEADER_TOGGLE_SHIFT);
	अन्यथा
		desc |= ((u64)0x1 << HEADER_TOGGLE_SHIFT);

	flexrm_ग_लिखो_desc(desc_ptr, desc);
पूर्ण

अटल u64 flexrm_header_desc(u32 toggle, u32 startpkt, u32 endpkt,
			       u32 bdcount, u32 flags, u32 opaque)
अणु
	u64 desc = 0;

	DESC_ENC(desc, HEADER_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggle, HEADER_TOGGLE_SHIFT, HEADER_TOGGLE_MASK);
	DESC_ENC(desc, startpkt, HEADER_STARTPKT_SHIFT, HEADER_STARTPKT_MASK);
	DESC_ENC(desc, endpkt, HEADER_ENDPKT_SHIFT, HEADER_ENDPKT_MASK);
	DESC_ENC(desc, bdcount, HEADER_BDCOUNT_SHIFT, HEADER_BDCOUNT_MASK);
	DESC_ENC(desc, flags, HEADER_FLAGS_SHIFT, HEADER_FLAGS_MASK);
	DESC_ENC(desc, opaque, HEADER_OPAQUE_SHIFT, HEADER_OPAQUE_MASK);

	वापस desc;
पूर्ण

अटल व्योम flexrm_enqueue_desc(u32 nhpos, u32 nhcnt, u32 reqid,
				 u64 desc, व्योम **desc_ptr, u32 *toggle,
				 व्योम *start_desc, व्योम *end_desc)
अणु
	u64 d;
	u32 nhavail, _toggle, _startpkt, _endpkt, _bdcount;

	/* Sanity check */
	अगर (nhcnt <= nhpos)
		वापस;

	/*
	 * Each request or packet start with a HEADER descriptor followed
	 * by one or more non-HEADER descriptors (SRC, SRCT, MSRC, DST,
	 * DSTT, MDST, IMM, and IMMT). The number of non-HEADER descriptors
	 * following a HEADER descriptor is represented by BDCOUNT field
	 * of HEADER descriptor. The max value of BDCOUNT field is 31 which
	 * means we can only have 31 non-HEADER descriptors following one
	 * HEADER descriptor.
	 *
	 * In general use, number of non-HEADER descriptors can easily go
	 * beyond 31. To tackle this situation, we have packet (or request)
	 * extension bits (STARTPKT and ENDPKT) in the HEADER descriptor.
	 *
	 * To use packet extension, the first HEADER descriptor of request
	 * (or packet) will have STARTPKT=1 and ENDPKT=0. The पूर्णांकermediate
	 * HEADER descriptors will have STARTPKT=0 and ENDPKT=0. The last
	 * HEADER descriptor will have STARTPKT=0 and ENDPKT=1. Also, the
	 * TOGGLE bit of the first HEADER will be set to invalid state to
	 * ensure that FlexRM करोes not start fetching descriptors till all
	 * descriptors are enqueued. The user of this function will flip
	 * the TOGGLE bit of first HEADER after all descriptors are
	 * enqueued.
	 */

	अगर ((nhpos % HEADER_BDCOUNT_MAX == 0) && (nhcnt - nhpos)) अणु
		/* Prepare the header descriptor */
		nhavail = (nhcnt - nhpos);
		_toggle = (nhpos == 0) ? !(*toggle) : (*toggle);
		_startpkt = (nhpos == 0) ? 0x1 : 0x0;
		_endpkt = (nhavail <= HEADER_BDCOUNT_MAX) ? 0x1 : 0x0;
		_bdcount = (nhavail <= HEADER_BDCOUNT_MAX) ?
				nhavail : HEADER_BDCOUNT_MAX;
		अगर (nhavail <= HEADER_BDCOUNT_MAX)
			_bdcount = nhavail;
		अन्यथा
			_bdcount = HEADER_BDCOUNT_MAX;
		d = flexrm_header_desc(_toggle, _startpkt, _endpkt,
					_bdcount, 0x0, reqid);

		/* Write header descriptor */
		flexrm_ग_लिखो_desc(*desc_ptr, d);

		/* Poपूर्णांक to next descriptor */
		*desc_ptr += माप(desc);
		अगर (*desc_ptr == end_desc)
			*desc_ptr = start_desc;

		/* Skip next poपूर्णांकer descriptors */
		जबतक (flexrm_is_next_table_desc(*desc_ptr)) अणु
			*toggle = (*toggle) ? 0 : 1;
			*desc_ptr += माप(desc);
			अगर (*desc_ptr == end_desc)
				*desc_ptr = start_desc;
		पूर्ण
	पूर्ण

	/* Write desired descriptor */
	flexrm_ग_लिखो_desc(*desc_ptr, desc);

	/* Poपूर्णांक to next descriptor */
	*desc_ptr += माप(desc);
	अगर (*desc_ptr == end_desc)
		*desc_ptr = start_desc;

	/* Skip next poपूर्णांकer descriptors */
	जबतक (flexrm_is_next_table_desc(*desc_ptr)) अणु
		*toggle = (*toggle) ? 0 : 1;
		*desc_ptr += माप(desc);
		अगर (*desc_ptr == end_desc)
			*desc_ptr = start_desc;
	पूर्ण
पूर्ण

अटल u64 flexrm_src_desc(dma_addr_t addr, अचिन्हित पूर्णांक length)
अणु
	u64 desc = 0;

	DESC_ENC(desc, SRC_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length, SRC_LENGTH_SHIFT, SRC_LENGTH_MASK);
	DESC_ENC(desc, addr, SRC_ADDR_SHIFT, SRC_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_msrc_desc(dma_addr_t addr, अचिन्हित पूर्णांक length_भाग_16)
अणु
	u64 desc = 0;

	DESC_ENC(desc, MSRC_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length_भाग_16, MSRC_LENGTH_SHIFT, MSRC_LENGTH_MASK);
	DESC_ENC(desc, addr, MSRC_ADDR_SHIFT, MSRC_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_dst_desc(dma_addr_t addr, अचिन्हित पूर्णांक length)
अणु
	u64 desc = 0;

	DESC_ENC(desc, DST_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length, DST_LENGTH_SHIFT, DST_LENGTH_MASK);
	DESC_ENC(desc, addr, DST_ADDR_SHIFT, DST_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_mdst_desc(dma_addr_t addr, अचिन्हित पूर्णांक length_भाग_16)
अणु
	u64 desc = 0;

	DESC_ENC(desc, MDST_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length_भाग_16, MDST_LENGTH_SHIFT, MDST_LENGTH_MASK);
	DESC_ENC(desc, addr, MDST_ADDR_SHIFT, MDST_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_imm_desc(u64 data)
अणु
	u64 desc = 0;

	DESC_ENC(desc, IMM_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, data, IMM_DATA_SHIFT, IMM_DATA_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_srct_desc(dma_addr_t addr, अचिन्हित पूर्णांक length)
अणु
	u64 desc = 0;

	DESC_ENC(desc, SRCT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length, SRCT_LENGTH_SHIFT, SRCT_LENGTH_MASK);
	DESC_ENC(desc, addr, SRCT_ADDR_SHIFT, SRCT_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_dstt_desc(dma_addr_t addr, अचिन्हित पूर्णांक length)
अणु
	u64 desc = 0;

	DESC_ENC(desc, DSTT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length, DSTT_LENGTH_SHIFT, DSTT_LENGTH_MASK);
	DESC_ENC(desc, addr, DSTT_ADDR_SHIFT, DSTT_ADDR_MASK);

	वापस desc;
पूर्ण

अटल u64 flexrm_immt_desc(u64 data)
अणु
	u64 desc = 0;

	DESC_ENC(desc, IMMT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, data, IMMT_DATA_SHIFT, IMMT_DATA_MASK);

	वापस desc;
पूर्ण

अटल bool flexrm_spu_sanity_check(काष्ठा brcm_message *msg)
अणु
	काष्ठा scatterlist *sg;

	अगर (!msg->spu.src || !msg->spu.dst)
		वापस false;
	क्रम (sg = msg->spu.src; sg; sg = sg_next(sg)) अणु
		अगर (sg->length & 0xf) अणु
			अगर (sg->length > SRC_LENGTH_MASK)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (sg->length > (MSRC_LENGTH_MASK * 16))
				वापस false;
		पूर्ण
	पूर्ण
	क्रम (sg = msg->spu.dst; sg; sg = sg_next(sg)) अणु
		अगर (sg->length & 0xf) अणु
			अगर (sg->length > DST_LENGTH_MASK)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (sg->length > (MDST_LENGTH_MASK * 16))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल u32 flexrm_spu_estimate_nonheader_desc_count(काष्ठा brcm_message *msg)
अणु
	u32 cnt = 0;
	अचिन्हित पूर्णांक dst_target = 0;
	काष्ठा scatterlist *src_sg = msg->spu.src, *dst_sg = msg->spu.dst;

	जबतक (src_sg || dst_sg) अणु
		अगर (src_sg) अणु
			cnt++;
			dst_target = src_sg->length;
			src_sg = sg_next(src_sg);
		पूर्ण अन्यथा
			dst_target = अच_पूर्णांक_उच्च;

		जबतक (dst_target && dst_sg) अणु
			cnt++;
			अगर (dst_sg->length < dst_target)
				dst_target -= dst_sg->length;
			अन्यथा
				dst_target = 0;
			dst_sg = sg_next(dst_sg);
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक flexrm_spu_dma_map(काष्ठा device *dev, काष्ठा brcm_message *msg)
अणु
	पूर्णांक rc;

	rc = dma_map_sg(dev, msg->spu.src, sg_nents(msg->spu.src),
			DMA_TO_DEVICE);
	अगर (rc < 0)
		वापस rc;

	rc = dma_map_sg(dev, msg->spu.dst, sg_nents(msg->spu.dst),
			DMA_FROM_DEVICE);
	अगर (rc < 0) अणु
		dma_unmap_sg(dev, msg->spu.src, sg_nents(msg->spu.src),
			     DMA_TO_DEVICE);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम flexrm_spu_dma_unmap(काष्ठा device *dev, काष्ठा brcm_message *msg)
अणु
	dma_unmap_sg(dev, msg->spu.dst, sg_nents(msg->spu.dst),
		     DMA_FROM_DEVICE);
	dma_unmap_sg(dev, msg->spu.src, sg_nents(msg->spu.src),
		     DMA_TO_DEVICE);
पूर्ण

अटल व्योम *flexrm_spu_ग_लिखो_descs(काष्ठा brcm_message *msg, u32 nhcnt,
				     u32 reqid, व्योम *desc_ptr, u32 toggle,
				     व्योम *start_desc, व्योम *end_desc)
अणु
	u64 d;
	u32 nhpos = 0;
	व्योम *orig_desc_ptr = desc_ptr;
	अचिन्हित पूर्णांक dst_target = 0;
	काष्ठा scatterlist *src_sg = msg->spu.src, *dst_sg = msg->spu.dst;

	जबतक (src_sg || dst_sg) अणु
		अगर (src_sg) अणु
			अगर (sg_dma_len(src_sg) & 0xf)
				d = flexrm_src_desc(sg_dma_address(src_sg),
						     sg_dma_len(src_sg));
			अन्यथा
				d = flexrm_msrc_desc(sg_dma_address(src_sg),
						      sg_dma_len(src_sg)/16);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
			dst_target = sg_dma_len(src_sg);
			src_sg = sg_next(src_sg);
		पूर्ण अन्यथा
			dst_target = अच_पूर्णांक_उच्च;

		जबतक (dst_target && dst_sg) अणु
			अगर (sg_dma_len(dst_sg) & 0xf)
				d = flexrm_dst_desc(sg_dma_address(dst_sg),
						     sg_dma_len(dst_sg));
			अन्यथा
				d = flexrm_mdst_desc(sg_dma_address(dst_sg),
						      sg_dma_len(dst_sg)/16);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
			अगर (sg_dma_len(dst_sg) < dst_target)
				dst_target -= sg_dma_len(dst_sg);
			अन्यथा
				dst_target = 0;
			dst_sg = sg_next(dst_sg);
		पूर्ण
	पूर्ण

	/* Null descriptor with invalid toggle bit */
	flexrm_ग_लिखो_desc(desc_ptr, flexrm_null_desc(!toggle));

	/* Ensure that descriptors have been written to memory */
	wmb();

	/* Flip toggle bit in header */
	flexrm_flip_header_toggle(orig_desc_ptr);

	वापस desc_ptr;
पूर्ण

अटल bool flexrm_sba_sanity_check(काष्ठा brcm_message *msg)
अणु
	u32 i;

	अगर (!msg->sba.cmds || !msg->sba.cmds_count)
		वापस false;

	क्रम (i = 0; i < msg->sba.cmds_count; i++) अणु
		अगर (((msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_B) ||
		     (msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_C)) &&
		    (msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_OUTPUT))
			वापस false;
		अगर ((msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_B) &&
		    (msg->sba.cmds[i].data_len > SRCT_LENGTH_MASK))
			वापस false;
		अगर ((msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_C) &&
		    (msg->sba.cmds[i].data_len > SRCT_LENGTH_MASK))
			वापस false;
		अगर ((msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_RESP) &&
		    (msg->sba.cmds[i].resp_len > DSTT_LENGTH_MASK))
			वापस false;
		अगर ((msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_OUTPUT) &&
		    (msg->sba.cmds[i].data_len > DSTT_LENGTH_MASK))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल u32 flexrm_sba_estimate_nonheader_desc_count(काष्ठा brcm_message *msg)
अणु
	u32 i, cnt;

	cnt = 0;
	क्रम (i = 0; i < msg->sba.cmds_count; i++) अणु
		cnt++;

		अगर ((msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_B) ||
		    (msg->sba.cmds[i].flags & BRCM_SBA_CMD_TYPE_C))
			cnt++;

		अगर (msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_RESP)
			cnt++;

		अगर (msg->sba.cmds[i].flags & BRCM_SBA_CMD_HAS_OUTPUT)
			cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम *flexrm_sba_ग_लिखो_descs(काष्ठा brcm_message *msg, u32 nhcnt,
				     u32 reqid, व्योम *desc_ptr, u32 toggle,
				     व्योम *start_desc, व्योम *end_desc)
अणु
	u64 d;
	u32 i, nhpos = 0;
	काष्ठा brcm_sba_command *c;
	व्योम *orig_desc_ptr = desc_ptr;

	/* Convert SBA commands पूर्णांकo descriptors */
	क्रम (i = 0; i < msg->sba.cmds_count; i++) अणु
		c = &msg->sba.cmds[i];

		अगर ((c->flags & BRCM_SBA_CMD_HAS_RESP) &&
		    (c->flags & BRCM_SBA_CMD_HAS_OUTPUT)) अणु
			/* Destination response descriptor */
			d = flexrm_dst_desc(c->resp, c->resp_len);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
		पूर्ण अन्यथा अगर (c->flags & BRCM_SBA_CMD_HAS_RESP) अणु
			/* Destination response with tlast descriptor */
			d = flexrm_dstt_desc(c->resp, c->resp_len);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
		पूर्ण

		अगर (c->flags & BRCM_SBA_CMD_HAS_OUTPUT) अणु
			/* Destination with tlast descriptor */
			d = flexrm_dstt_desc(c->data, c->data_len);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
		पूर्ण

		अगर (c->flags & BRCM_SBA_CMD_TYPE_B) अणु
			/* Command as immediate descriptor */
			d = flexrm_imm_desc(c->cmd);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
		पूर्ण अन्यथा अणु
			/* Command as immediate descriptor with tlast */
			d = flexrm_immt_desc(c->cmd);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
		पूर्ण

		अगर ((c->flags & BRCM_SBA_CMD_TYPE_B) ||
		    (c->flags & BRCM_SBA_CMD_TYPE_C)) अणु
			/* Source with tlast descriptor */
			d = flexrm_srct_desc(c->data, c->data_len);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
		पूर्ण
	पूर्ण

	/* Null descriptor with invalid toggle bit */
	flexrm_ग_लिखो_desc(desc_ptr, flexrm_null_desc(!toggle));

	/* Ensure that descriptors have been written to memory */
	wmb();

	/* Flip toggle bit in header */
	flexrm_flip_header_toggle(orig_desc_ptr);

	वापस desc_ptr;
पूर्ण

अटल bool flexrm_sanity_check(काष्ठा brcm_message *msg)
अणु
	अगर (!msg)
		वापस false;

	चयन (msg->type) अणु
	हाल BRCM_MESSAGE_SPU:
		वापस flexrm_spu_sanity_check(msg);
	हाल BRCM_MESSAGE_SBA:
		वापस flexrm_sba_sanity_check(msg);
	शेष:
		वापस false;
	पूर्ण;
पूर्ण

अटल u32 flexrm_estimate_nonheader_desc_count(काष्ठा brcm_message *msg)
अणु
	अगर (!msg)
		वापस 0;

	चयन (msg->type) अणु
	हाल BRCM_MESSAGE_SPU:
		वापस flexrm_spu_estimate_nonheader_desc_count(msg);
	हाल BRCM_MESSAGE_SBA:
		वापस flexrm_sba_estimate_nonheader_desc_count(msg);
	शेष:
		वापस 0;
	पूर्ण;
पूर्ण

अटल पूर्णांक flexrm_dma_map(काष्ठा device *dev, काष्ठा brcm_message *msg)
अणु
	अगर (!dev || !msg)
		वापस -EINVAL;

	चयन (msg->type) अणु
	हाल BRCM_MESSAGE_SPU:
		वापस flexrm_spu_dma_map(dev, msg);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम flexrm_dma_unmap(काष्ठा device *dev, काष्ठा brcm_message *msg)
अणु
	अगर (!dev || !msg)
		वापस;

	चयन (msg->type) अणु
	हाल BRCM_MESSAGE_SPU:
		flexrm_spu_dma_unmap(dev, msg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम *flexrm_ग_लिखो_descs(काष्ठा brcm_message *msg, u32 nhcnt,
				u32 reqid, व्योम *desc_ptr, u32 toggle,
				व्योम *start_desc, व्योम *end_desc)
अणु
	अगर (!msg || !desc_ptr || !start_desc || !end_desc)
		वापस ERR_PTR(-ENOTSUPP);

	अगर ((desc_ptr < start_desc) || (end_desc <= desc_ptr))
		वापस ERR_PTR(-दुस्फल);

	चयन (msg->type) अणु
	हाल BRCM_MESSAGE_SPU:
		वापस flexrm_spu_ग_लिखो_descs(msg, nhcnt, reqid,
					       desc_ptr, toggle,
					       start_desc, end_desc);
	हाल BRCM_MESSAGE_SBA:
		वापस flexrm_sba_ग_लिखो_descs(msg, nhcnt, reqid,
					       desc_ptr, toggle,
					       start_desc, end_desc);
	शेष:
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण;
पूर्ण

/* ====== FlexRM driver helper routines ===== */

अटल व्योम flexrm_ग_लिखो_config_in_seqfile(काष्ठा flexrm_mbox *mbox,
					   काष्ठा seq_file *file)
अणु
	पूर्णांक i;
	स्थिर अक्षर *state;
	काष्ठा flexrm_ring *ring;

	seq_म_लिखो(file, "%-5s %-9s %-18s %-10s %-18s %-10s\n",
		   "Ring#", "State", "BD_Addr", "BD_Size",
		   "Cmpl_Addr", "Cmpl_Size");

	क्रम (i = 0; i < mbox->num_rings; i++) अणु
		ring = &mbox->rings[i];
		अगर (पढ़ोl(ring->regs + RING_CONTROL) &
		    BIT(CONTROL_ACTIVE_SHIFT))
			state = "active";
		अन्यथा
			state = "inactive";
		seq_म_लिखो(file,
			   "%-5d %-9s 0x%016llx 0x%08x 0x%016llx 0x%08x\n",
			   ring->num, state,
			   (अचिन्हित दीर्घ दीर्घ)ring->bd_dma_base,
			   (u32)RING_BD_SIZE,
			   (अचिन्हित दीर्घ दीर्घ)ring->cmpl_dma_base,
			   (u32)RING_CMPL_SIZE);
	पूर्ण
पूर्ण

अटल व्योम flexrm_ग_लिखो_stats_in_seqfile(काष्ठा flexrm_mbox *mbox,
					  काष्ठा seq_file *file)
अणु
	पूर्णांक i;
	u32 val, bd_पढ़ो_offset;
	काष्ठा flexrm_ring *ring;

	seq_म_लिखो(file, "%-5s %-10s %-10s %-10s %-11s %-11s\n",
		   "Ring#", "BD_Read", "BD_Write",
		   "Cmpl_Read", "Submitted", "Completed");

	क्रम (i = 0; i < mbox->num_rings; i++) अणु
		ring = &mbox->rings[i];
		bd_पढ़ो_offset = पढ़ोl_relaxed(ring->regs + RING_BD_READ_PTR);
		val = पढ़ोl_relaxed(ring->regs + RING_BD_START_ADDR);
		bd_पढ़ो_offset *= RING_DESC_SIZE;
		bd_पढ़ो_offset += (u32)(BD_START_ADDR_DECODE(val) -
					ring->bd_dma_base);
		seq_म_लिखो(file, "%-5d 0x%08x 0x%08x 0x%08x %-11d %-11d\n",
			   ring->num,
			   (u32)bd_पढ़ो_offset,
			   (u32)ring->bd_ग_लिखो_offset,
			   (u32)ring->cmpl_पढ़ो_offset,
			   (u32)atomic_पढ़ो(&ring->msg_send_count),
			   (u32)atomic_पढ़ो(&ring->msg_cmpl_count));
	पूर्ण
पूर्ण

अटल पूर्णांक flexrm_new_request(काष्ठा flexrm_ring *ring,
				काष्ठा brcm_message *batch_msg,
				काष्ठा brcm_message *msg)
अणु
	व्योम *next;
	अचिन्हित दीर्घ flags;
	u32 val, count, nhcnt;
	u32 पढ़ो_offset, ग_लिखो_offset;
	bool निकास_cleanup = false;
	पूर्णांक ret = 0, reqid;

	/* Do sanity check on message */
	अगर (!flexrm_sanity_check(msg))
		वापस -EIO;
	msg->error = 0;

	/* If no requests possible then save data poपूर्णांकer and जाओ करोne. */
	spin_lock_irqsave(&ring->lock, flags);
	reqid = biपंचांगap_find_मुक्त_region(ring->requests_bmap,
					RING_MAX_REQ_COUNT, 0);
	spin_unlock_irqrestore(&ring->lock, flags);
	अगर (reqid < 0)
		वापस -ENOSPC;
	ring->requests[reqid] = msg;

	/* Do DMA mappings क्रम the message */
	ret = flexrm_dma_map(ring->mbox->dev, msg);
	अगर (ret < 0) अणु
		ring->requests[reqid] = शून्य;
		spin_lock_irqsave(&ring->lock, flags);
		biपंचांगap_release_region(ring->requests_bmap, reqid, 0);
		spin_unlock_irqrestore(&ring->lock, flags);
		वापस ret;
	पूर्ण

	/* Determine current HW BD पढ़ो offset */
	पढ़ो_offset = पढ़ोl_relaxed(ring->regs + RING_BD_READ_PTR);
	val = पढ़ोl_relaxed(ring->regs + RING_BD_START_ADDR);
	पढ़ो_offset *= RING_DESC_SIZE;
	पढ़ो_offset += (u32)(BD_START_ADDR_DECODE(val) - ring->bd_dma_base);

	/*
	 * Number required descriptors = number of non-header descriptors +
	 *				 number of header descriptors +
	 *				 1x null descriptor
	 */
	nhcnt = flexrm_estimate_nonheader_desc_count(msg);
	count = flexrm_estimate_header_desc_count(nhcnt) + nhcnt + 1;

	/* Check क्रम available descriptor space. */
	ग_लिखो_offset = ring->bd_ग_लिखो_offset;
	जबतक (count) अणु
		अगर (!flexrm_is_next_table_desc(ring->bd_base + ग_लिखो_offset))
			count--;
		ग_लिखो_offset += RING_DESC_SIZE;
		अगर (ग_लिखो_offset == RING_BD_SIZE)
			ग_लिखो_offset = 0x0;
		अगर (ग_लिखो_offset == पढ़ो_offset)
			अवरोध;
	पूर्ण
	अगर (count) अणु
		ret = -ENOSPC;
		निकास_cleanup = true;
		जाओ निकास;
	पूर्ण

	/* Write descriptors to ring */
	next = flexrm_ग_लिखो_descs(msg, nhcnt, reqid,
			ring->bd_base + ring->bd_ग_लिखो_offset,
			RING_BD_TOGGLE_VALID(ring->bd_ग_लिखो_offset),
			ring->bd_base, ring->bd_base + RING_BD_SIZE);
	अगर (IS_ERR(next)) अणु
		ret = PTR_ERR(next);
		निकास_cleanup = true;
		जाओ निकास;
	पूर्ण

	/* Save ring BD ग_लिखो offset */
	ring->bd_ग_लिखो_offset = (अचिन्हित दीर्घ)(next - ring->bd_base);

	/* Increment number of messages sent */
	atomic_inc_वापस(&ring->msg_send_count);

निकास:
	/* Update error status in message */
	msg->error = ret;

	/* Cleanup अगर we failed */
	अगर (निकास_cleanup) अणु
		flexrm_dma_unmap(ring->mbox->dev, msg);
		ring->requests[reqid] = शून्य;
		spin_lock_irqsave(&ring->lock, flags);
		biपंचांगap_release_region(ring->requests_bmap, reqid, 0);
		spin_unlock_irqrestore(&ring->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक flexrm_process_completions(काष्ठा flexrm_ring *ring)
अणु
	u64 desc;
	पूर्णांक err, count = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा brcm_message *msg = शून्य;
	u32 reqid, cmpl_पढ़ो_offset, cmpl_ग_लिखो_offset;
	काष्ठा mbox_chan *chan = &ring->mbox->controller.chans[ring->num];

	spin_lock_irqsave(&ring->lock, flags);

	/*
	 * Get current completion पढ़ो and ग_लिखो offset
	 *
	 * Note: We should पढ़ो completion ग_लिखो poपूर्णांकer at least once
	 * after we get a MSI पूर्णांकerrupt because HW मुख्यtains पूर्णांकernal
	 * MSI status which will allow next MSI पूर्णांकerrupt only after
	 * completion ग_लिखो poपूर्णांकer is पढ़ो.
	 */
	cmpl_ग_लिखो_offset = पढ़ोl_relaxed(ring->regs + RING_CMPL_WRITE_PTR);
	cmpl_ग_लिखो_offset *= RING_DESC_SIZE;
	cmpl_पढ़ो_offset = ring->cmpl_पढ़ो_offset;
	ring->cmpl_पढ़ो_offset = cmpl_ग_लिखो_offset;

	spin_unlock_irqrestore(&ring->lock, flags);

	/* For each completed request notअगरy mailbox clients */
	reqid = 0;
	जबतक (cmpl_पढ़ो_offset != cmpl_ग_लिखो_offset) अणु
		/* Dequeue next completion descriptor */
		desc = *((u64 *)(ring->cmpl_base + cmpl_पढ़ो_offset));

		/* Next पढ़ो offset */
		cmpl_पढ़ो_offset += RING_DESC_SIZE;
		अगर (cmpl_पढ़ो_offset == RING_CMPL_SIZE)
			cmpl_पढ़ो_offset = 0;

		/* Decode error from completion descriptor */
		err = flexrm_cmpl_desc_to_error(desc);
		अगर (err < 0) अणु
			dev_warn(ring->mbox->dev,
			"ring%d got completion desc=0x%lx with error %d\n",
			ring->num, (अचिन्हित दीर्घ)desc, err);
		पूर्ण

		/* Determine request id from completion descriptor */
		reqid = flexrm_cmpl_desc_to_reqid(desc);

		/* Determine message poपूर्णांकer based on reqid */
		msg = ring->requests[reqid];
		अगर (!msg) अणु
			dev_warn(ring->mbox->dev,
			"ring%d null msg pointer for completion desc=0x%lx\n",
			ring->num, (अचिन्हित दीर्घ)desc);
			जारी;
		पूर्ण

		/* Release reqid क्रम recycling */
		ring->requests[reqid] = शून्य;
		spin_lock_irqsave(&ring->lock, flags);
		biपंचांगap_release_region(ring->requests_bmap, reqid, 0);
		spin_unlock_irqrestore(&ring->lock, flags);

		/* Unmap DMA mappings */
		flexrm_dma_unmap(ring->mbox->dev, msg);

		/* Give-back message to mailbox client */
		msg->error = err;
		mbox_chan_received_data(chan, msg);

		/* Increment number of completions processed */
		atomic_inc_वापस(&ring->msg_cmpl_count);
		count++;
	पूर्ण

	वापस count;
पूर्ण

/* ====== FlexRM Debugfs callbacks ====== */

अटल पूर्णांक flexrm_debugfs_conf_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा flexrm_mbox *mbox = dev_get_drvdata(file->निजी);

	/* Write config in file */
	flexrm_ग_लिखो_config_in_seqfile(mbox, file);

	वापस 0;
पूर्ण

अटल पूर्णांक flexrm_debugfs_stats_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा flexrm_mbox *mbox = dev_get_drvdata(file->निजी);

	/* Write stats in file */
	flexrm_ग_लिखो_stats_in_seqfile(mbox, file);

	वापस 0;
पूर्ण

/* ====== FlexRM पूर्णांकerrupt handler ===== */

अटल irqवापस_t flexrm_irq_event(पूर्णांक irq, व्योम *dev_id)
अणु
	/* We only have MSI क्रम completions so just wakeup IRQ thपढ़ो */
	/* Ring related errors will be inक्रमmed via completion descriptors */

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t flexrm_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	flexrm_process_completions(dev_id);

	वापस IRQ_HANDLED;
पूर्ण

/* ====== FlexRM mailbox callbacks ===== */

अटल पूर्णांक flexrm_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	पूर्णांक i, rc;
	काष्ठा flexrm_ring *ring = chan->con_priv;
	काष्ठा brcm_message *msg = data;

	अगर (msg->type == BRCM_MESSAGE_BATCH) अणु
		क्रम (i = msg->batch.msgs_queued;
		     i < msg->batch.msgs_count; i++) अणु
			rc = flexrm_new_request(ring, msg,
						 &msg->batch.msgs[i]);
			अगर (rc) अणु
				msg->error = rc;
				वापस rc;
			पूर्ण
			msg->batch.msgs_queued++;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस flexrm_new_request(ring, शून्य, data);
पूर्ण

अटल bool flexrm_peek_data(काष्ठा mbox_chan *chan)
अणु
	पूर्णांक cnt = flexrm_process_completions(chan->con_priv);

	वापस (cnt > 0) ? true : false;
पूर्ण

अटल पूर्णांक flexrm_startup(काष्ठा mbox_chan *chan)
अणु
	u64 d;
	u32 val, off;
	पूर्णांक ret = 0;
	dma_addr_t next_addr;
	काष्ठा flexrm_ring *ring = chan->con_priv;

	/* Allocate BD memory */
	ring->bd_base = dma_pool_alloc(ring->mbox->bd_pool,
				       GFP_KERNEL, &ring->bd_dma_base);
	अगर (!ring->bd_base) अणु
		dev_err(ring->mbox->dev,
			"can't allocate BD memory for ring%d\n",
			ring->num);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* Configure next table poपूर्णांकer entries in BD memory */
	क्रम (off = 0; off < RING_BD_SIZE; off += RING_DESC_SIZE) अणु
		next_addr = off + RING_DESC_SIZE;
		अगर (next_addr == RING_BD_SIZE)
			next_addr = 0;
		next_addr += ring->bd_dma_base;
		अगर (RING_BD_ALIGN_CHECK(next_addr))
			d = flexrm_next_table_desc(RING_BD_TOGGLE_VALID(off),
						    next_addr);
		अन्यथा
			d = flexrm_null_desc(RING_BD_TOGGLE_INVALID(off));
		flexrm_ग_लिखो_desc(ring->bd_base + off, d);
	पूर्ण

	/* Allocate completion memory */
	ring->cmpl_base = dma_pool_zalloc(ring->mbox->cmpl_pool,
					 GFP_KERNEL, &ring->cmpl_dma_base);
	अगर (!ring->cmpl_base) अणु
		dev_err(ring->mbox->dev,
			"can't allocate completion memory for ring%d\n",
			ring->num);
		ret = -ENOMEM;
		जाओ fail_मुक्त_bd_memory;
	पूर्ण

	/* Request IRQ */
	अगर (ring->irq == अच_पूर्णांक_उच्च) अणु
		dev_err(ring->mbox->dev,
			"ring%d IRQ not available\n", ring->num);
		ret = -ENODEV;
		जाओ fail_मुक्त_cmpl_memory;
	पूर्ण
	ret = request_thपढ़ोed_irq(ring->irq,
				   flexrm_irq_event,
				   flexrm_irq_thपढ़ो,
				   0, dev_name(ring->mbox->dev), ring);
	अगर (ret) अणु
		dev_err(ring->mbox->dev,
			"failed to request ring%d IRQ\n", ring->num);
		जाओ fail_मुक्त_cmpl_memory;
	पूर्ण
	ring->irq_requested = true;

	/* Set IRQ affinity hपूर्णांक */
	ring->irq_aff_hपूर्णांक = CPU_MASK_NONE;
	val = ring->mbox->num_rings;
	val = (num_online_cpus() < val) ? val / num_online_cpus() : 1;
	cpumask_set_cpu((ring->num / val) % num_online_cpus(),
			&ring->irq_aff_hपूर्णांक);
	ret = irq_set_affinity_hपूर्णांक(ring->irq, &ring->irq_aff_hपूर्णांक);
	अगर (ret) अणु
		dev_err(ring->mbox->dev,
			"failed to set IRQ affinity hint for ring%d\n",
			ring->num);
		जाओ fail_मुक्त_irq;
	पूर्ण

	/* Disable/inactivate ring */
	ग_लिखोl_relaxed(0x0, ring->regs + RING_CONTROL);

	/* Program BD start address */
	val = BD_START_ADDR_VALUE(ring->bd_dma_base);
	ग_लिखोl_relaxed(val, ring->regs + RING_BD_START_ADDR);

	/* BD ग_लिखो poपूर्णांकer will be same as HW ग_लिखो poपूर्णांकer */
	ring->bd_ग_लिखो_offset =
			पढ़ोl_relaxed(ring->regs + RING_BD_WRITE_PTR);
	ring->bd_ग_लिखो_offset *= RING_DESC_SIZE;

	/* Program completion start address */
	val = CMPL_START_ADDR_VALUE(ring->cmpl_dma_base);
	ग_लिखोl_relaxed(val, ring->regs + RING_CMPL_START_ADDR);

	/* Completion पढ़ो poपूर्णांकer will be same as HW ग_लिखो poपूर्णांकer */
	ring->cmpl_पढ़ो_offset =
			पढ़ोl_relaxed(ring->regs + RING_CMPL_WRITE_PTR);
	ring->cmpl_पढ़ो_offset *= RING_DESC_SIZE;

	/* Read ring Tx, Rx, and Outstanding counts to clear */
	पढ़ोl_relaxed(ring->regs + RING_NUM_REQ_RECV_LS);
	पढ़ोl_relaxed(ring->regs + RING_NUM_REQ_RECV_MS);
	पढ़ोl_relaxed(ring->regs + RING_NUM_REQ_TRANS_LS);
	पढ़ोl_relaxed(ring->regs + RING_NUM_REQ_TRANS_MS);
	पढ़ोl_relaxed(ring->regs + RING_NUM_REQ_OUTSTAND);

	/* Configure RING_MSI_CONTROL */
	val = 0;
	val |= (ring->msi_समयr_val << MSI_TIMER_VAL_SHIFT);
	val |= BIT(MSI_ENABLE_SHIFT);
	val |= (ring->msi_count_threshold & MSI_COUNT_MASK) << MSI_COUNT_SHIFT;
	ग_लिखोl_relaxed(val, ring->regs + RING_MSI_CONTROL);

	/* Enable/activate ring */
	val = BIT(CONTROL_ACTIVE_SHIFT);
	ग_लिखोl_relaxed(val, ring->regs + RING_CONTROL);

	/* Reset stats to zero */
	atomic_set(&ring->msg_send_count, 0);
	atomic_set(&ring->msg_cmpl_count, 0);

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(ring->irq, ring);
	ring->irq_requested = false;
fail_मुक्त_cmpl_memory:
	dma_pool_मुक्त(ring->mbox->cmpl_pool,
		      ring->cmpl_base, ring->cmpl_dma_base);
	ring->cmpl_base = शून्य;
fail_मुक्त_bd_memory:
	dma_pool_मुक्त(ring->mbox->bd_pool,
		      ring->bd_base, ring->bd_dma_base);
	ring->bd_base = शून्य;
fail:
	वापस ret;
पूर्ण

अटल व्योम flexrm_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	u32 reqid;
	अचिन्हित पूर्णांक समयout;
	काष्ठा brcm_message *msg;
	काष्ठा flexrm_ring *ring = chan->con_priv;

	/* Disable/inactivate ring */
	ग_लिखोl_relaxed(0x0, ring->regs + RING_CONTROL);

	/* Set ring flush state */
	समयout = 1000; /* समयout of 1s */
	ग_लिखोl_relaxed(BIT(CONTROL_FLUSH_SHIFT),
			ring->regs + RING_CONTROL);
	करो अणु
		अगर (पढ़ोl_relaxed(ring->regs + RING_FLUSH_DONE) &
		    FLUSH_DONE_MASK)
			अवरोध;
		mdelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		dev_err(ring->mbox->dev,
			"setting ring%d flush state timedout\n", ring->num);

	/* Clear ring flush state */
	समयout = 1000; /* समयout of 1s */
	ग_लिखोl_relaxed(0x0, ring->regs + RING_CONTROL);
	करो अणु
		अगर (!(पढ़ोl_relaxed(ring->regs + RING_FLUSH_DONE) &
		      FLUSH_DONE_MASK))
			अवरोध;
		mdelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		dev_err(ring->mbox->dev,
			"clearing ring%d flush state timedout\n", ring->num);

	/* Abort all in-flight requests */
	क्रम (reqid = 0; reqid < RING_MAX_REQ_COUNT; reqid++) अणु
		msg = ring->requests[reqid];
		अगर (!msg)
			जारी;

		/* Release reqid क्रम recycling */
		ring->requests[reqid] = शून्य;

		/* Unmap DMA mappings */
		flexrm_dma_unmap(ring->mbox->dev, msg);

		/* Give-back message to mailbox client */
		msg->error = -EIO;
		mbox_chan_received_data(chan, msg);
	पूर्ण

	/* Clear requests biपंचांगap */
	biपंचांगap_zero(ring->requests_bmap, RING_MAX_REQ_COUNT);

	/* Release IRQ */
	अगर (ring->irq_requested) अणु
		irq_set_affinity_hपूर्णांक(ring->irq, शून्य);
		मुक्त_irq(ring->irq, ring);
		ring->irq_requested = false;
	पूर्ण

	/* Free-up completion descriptor ring */
	अगर (ring->cmpl_base) अणु
		dma_pool_मुक्त(ring->mbox->cmpl_pool,
			      ring->cmpl_base, ring->cmpl_dma_base);
		ring->cmpl_base = शून्य;
	पूर्ण

	/* Free-up BD descriptor ring */
	अगर (ring->bd_base) अणु
		dma_pool_मुक्त(ring->mbox->bd_pool,
			      ring->bd_base, ring->bd_dma_base);
		ring->bd_base = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops flexrm_mbox_chan_ops = अणु
	.send_data	= flexrm_send_data,
	.startup	= flexrm_startup,
	.shutकरोwn	= flexrm_shutकरोwn,
	.peek_data	= flexrm_peek_data,
पूर्ण;

अटल काष्ठा mbox_chan *flexrm_mbox_of_xlate(काष्ठा mbox_controller *cntlr,
					स्थिर काष्ठा of_phandle_args *pa)
अणु
	काष्ठा mbox_chan *chan;
	काष्ठा flexrm_ring *ring;

	अगर (pa->args_count < 3)
		वापस ERR_PTR(-EINVAL);

	अगर (pa->args[0] >= cntlr->num_chans)
		वापस ERR_PTR(-ENOENT);

	अगर (pa->args[1] > MSI_COUNT_MASK)
		वापस ERR_PTR(-EINVAL);

	अगर (pa->args[2] > MSI_TIMER_VAL_MASK)
		वापस ERR_PTR(-EINVAL);

	chan = &cntlr->chans[pa->args[0]];
	ring = chan->con_priv;
	ring->msi_count_threshold = pa->args[1];
	ring->msi_समयr_val = pa->args[2];

	वापस chan;
पूर्ण

/* ====== FlexRM platक्रमm driver ===== */

अटल व्योम flexrm_mbox_msi_ग_लिखो(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	काष्ठा device *dev = msi_desc_to_dev(desc);
	काष्ठा flexrm_mbox *mbox = dev_get_drvdata(dev);
	काष्ठा flexrm_ring *ring = &mbox->rings[desc->platक्रमm.msi_index];

	/* Configure per-Ring MSI रेजिस्टरs */
	ग_लिखोl_relaxed(msg->address_lo, ring->regs + RING_MSI_ADDR_LS);
	ग_लिखोl_relaxed(msg->address_hi, ring->regs + RING_MSI_ADDR_MS);
	ग_लिखोl_relaxed(msg->data, ring->regs + RING_MSI_DATA_VALUE);
पूर्ण

अटल पूर्णांक flexrm_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक index, ret = 0;
	व्योम __iomem *regs;
	व्योम __iomem *regs_end;
	काष्ठा msi_desc *desc;
	काष्ठा resource *iomem;
	काष्ठा flexrm_ring *ring;
	काष्ठा flexrm_mbox *mbox;
	काष्ठा device *dev = &pdev->dev;

	/* Allocate driver mailbox काष्ठा */
	mbox = devm_kzalloc(dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	mbox->dev = dev;
	platक्रमm_set_drvdata(pdev, mbox);

	/* Get resource क्रम रेजिस्टरs */
	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iomem || (resource_size(iomem) < RING_REGS_SIZE)) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	/* Map रेजिस्टरs of all rings */
	mbox->regs = devm_ioremap_resource(&pdev->dev, iomem);
	अगर (IS_ERR(mbox->regs)) अणु
		ret = PTR_ERR(mbox->regs);
		dev_err(&pdev->dev, "Failed to remap mailbox regs: %d\n", ret);
		जाओ fail;
	पूर्ण
	regs_end = mbox->regs + resource_size(iomem);

	/* Scan and count available rings */
	mbox->num_rings = 0;
	क्रम (regs = mbox->regs; regs < regs_end; regs += RING_REGS_SIZE) अणु
		अगर (पढ़ोl_relaxed(regs + RING_VER) == RING_VER_MAGIC)
			mbox->num_rings++;
	पूर्ण
	अगर (!mbox->num_rings) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	/* Allocate driver ring काष्ठाs */
	ring = devm_kसुस्मृति(dev, mbox->num_rings, माप(*ring), GFP_KERNEL);
	अगर (!ring) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	mbox->rings = ring;

	/* Initialize members of driver ring काष्ठाs */
	regs = mbox->regs;
	क्रम (index = 0; index < mbox->num_rings; index++) अणु
		ring = &mbox->rings[index];
		ring->num = index;
		ring->mbox = mbox;
		जबतक ((regs < regs_end) &&
		       (पढ़ोl_relaxed(regs + RING_VER) != RING_VER_MAGIC))
			regs += RING_REGS_SIZE;
		अगर (regs_end <= regs) अणु
			ret = -ENODEV;
			जाओ fail;
		पूर्ण
		ring->regs = regs;
		regs += RING_REGS_SIZE;
		ring->irq = अच_पूर्णांक_उच्च;
		ring->irq_requested = false;
		ring->msi_समयr_val = MSI_TIMER_VAL_MASK;
		ring->msi_count_threshold = 0x1;
		स_रखो(ring->requests, 0, माप(ring->requests));
		ring->bd_base = शून्य;
		ring->bd_dma_base = 0;
		ring->cmpl_base = शून्य;
		ring->cmpl_dma_base = 0;
		atomic_set(&ring->msg_send_count, 0);
		atomic_set(&ring->msg_cmpl_count, 0);
		spin_lock_init(&ring->lock);
		biपंचांगap_zero(ring->requests_bmap, RING_MAX_REQ_COUNT);
		ring->cmpl_पढ़ो_offset = 0;
	पूर्ण

	/* FlexRM is capable of 40-bit physical addresses only */
	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(40));
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret)
			जाओ fail;
	पूर्ण

	/* Create DMA pool क्रम ring BD memory */
	mbox->bd_pool = dma_pool_create("bd", dev, RING_BD_SIZE,
					1 << RING_BD_ALIGN_ORDER, 0);
	अगर (!mbox->bd_pool) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* Create DMA pool क्रम ring completion memory */
	mbox->cmpl_pool = dma_pool_create("cmpl", dev, RING_CMPL_SIZE,
					  1 << RING_CMPL_ALIGN_ORDER, 0);
	अगर (!mbox->cmpl_pool) अणु
		ret = -ENOMEM;
		जाओ fail_destroy_bd_pool;
	पूर्ण

	/* Allocate platक्रमm MSIs क्रम each ring */
	ret = platक्रमm_msi_करोमुख्य_alloc_irqs(dev, mbox->num_rings,
						flexrm_mbox_msi_ग_लिखो);
	अगर (ret)
		जाओ fail_destroy_cmpl_pool;

	/* Save alloced IRQ numbers क्रम each ring */
	क्रम_each_msi_entry(desc, dev) अणु
		ring = &mbox->rings[desc->platक्रमm.msi_index];
		ring->irq = desc->irq;
	पूर्ण

	/* Check availability of debugfs */
	अगर (!debugfs_initialized())
		जाओ skip_debugfs;

	/* Create debugfs root entry */
	mbox->root = debugfs_create_dir(dev_name(mbox->dev), शून्य);

	/* Create debugfs config entry */
	debugfs_create_devm_seqfile(mbox->dev, "config", mbox->root,
				    flexrm_debugfs_conf_show);

	/* Create debugfs stats entry */
	debugfs_create_devm_seqfile(mbox->dev, "stats", mbox->root,
				    flexrm_debugfs_stats_show);

skip_debugfs:

	/* Initialize mailbox controller */
	mbox->controller.txकरोne_irq = false;
	mbox->controller.txकरोne_poll = false;
	mbox->controller.ops = &flexrm_mbox_chan_ops;
	mbox->controller.dev = dev;
	mbox->controller.num_chans = mbox->num_rings;
	mbox->controller.of_xlate = flexrm_mbox_of_xlate;
	mbox->controller.chans = devm_kसुस्मृति(dev, mbox->num_rings,
				माप(*mbox->controller.chans), GFP_KERNEL);
	अगर (!mbox->controller.chans) अणु
		ret = -ENOMEM;
		जाओ fail_मुक्त_debugfs_root;
	पूर्ण
	क्रम (index = 0; index < mbox->num_rings; index++)
		mbox->controller.chans[index].con_priv = &mbox->rings[index];

	/* Register mailbox controller */
	ret = devm_mbox_controller_रेजिस्टर(dev, &mbox->controller);
	अगर (ret)
		जाओ fail_मुक्त_debugfs_root;

	dev_info(dev, "registered flexrm mailbox with %d channels\n",
			mbox->controller.num_chans);

	वापस 0;

fail_मुक्त_debugfs_root:
	debugfs_हटाओ_recursive(mbox->root);
	platक्रमm_msi_करोमुख्य_मुक्त_irqs(dev);
fail_destroy_cmpl_pool:
	dma_pool_destroy(mbox->cmpl_pool);
fail_destroy_bd_pool:
	dma_pool_destroy(mbox->bd_pool);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक flexrm_mbox_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा flexrm_mbox *mbox = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(mbox->root);

	platक्रमm_msi_करोमुख्य_मुक्त_irqs(dev);

	dma_pool_destroy(mbox->cmpl_pool);
	dma_pool_destroy(mbox->bd_pool);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id flexrm_mbox_of_match[] = अणु
	अणु .compatible = "brcm,iproc-flexrm-mbox", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, flexrm_mbox_of_match);

अटल काष्ठा platक्रमm_driver flexrm_mbox_driver = अणु
	.driver = अणु
		.name = "brcm-flexrm-mbox",
		.of_match_table = flexrm_mbox_of_match,
	पूर्ण,
	.probe		= flexrm_mbox_probe,
	.हटाओ		= flexrm_mbox_हटाओ,
पूर्ण;
module_platक्रमm_driver(flexrm_mbox_driver);

MODULE_AUTHOR("Anup Patel <anup.patel@broadcom.com>");
MODULE_DESCRIPTION("Broadcom FlexRM mailbox driver");
MODULE_LICENSE("GPL v2");
