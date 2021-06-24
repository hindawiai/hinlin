<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea_qmr.h
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *       Christoph Raisch <raisch@de.ibm.com>
 *       Jan-Bernd Themann <themann@de.ibm.com>
 *       Thomas Klein <tklein@de.ibm.com>
 */

#अगर_अघोषित __EHEA_QMR_H__
#घोषणा __EHEA_QMR_H__

#समावेश <linux/prefetch.h>
#समावेश "ehea.h"
#समावेश "ehea_hw.h"

/*
 * page size of ehea hardware queues
 */

#घोषणा EHEA_PAGESHIFT         12
#घोषणा EHEA_PAGESIZE          (1UL << EHEA_PAGESHIFT)
#घोषणा EHEA_SECTSIZE          (1UL << 24)
#घोषणा EHEA_PAGES_PER_SECTION (EHEA_SECTSIZE >> EHEA_PAGESHIFT)
#घोषणा EHEA_HUGEPAGESHIFT     34
#घोषणा EHEA_HUGEPAGE_SIZE     (1UL << EHEA_HUGEPAGESHIFT)
#घोषणा EHEA_HUGEPAGE_PFN_MASK ((EHEA_HUGEPAGE_SIZE - 1) >> PAGE_SHIFT)

#अगर ((1UL << SECTION_SIZE_BITS) < EHEA_SECTSIZE)
#त्रुटि eHEA module cannot work अगर kernel sectionsize < ehea sectionsize
#पूर्ण_अगर

/* Some abbreviations used here:
 *
 * WQE  - Work Queue Entry
 * SWQE - Send Work Queue Entry
 * RWQE - Receive Work Queue Entry
 * CQE  - Completion Queue Entry
 * EQE  - Event Queue Entry
 * MR   - Memory Region
 */

/* Use of WR_ID field क्रम EHEA */
#घोषणा EHEA_WR_ID_COUNT   EHEA_BMASK_IBM(0, 19)
#घोषणा EHEA_WR_ID_TYPE    EHEA_BMASK_IBM(20, 23)
#घोषणा EHEA_SWQE2_TYPE    0x1
#घोषणा EHEA_SWQE3_TYPE    0x2
#घोषणा EHEA_RWQE2_TYPE    0x3
#घोषणा EHEA_RWQE3_TYPE    0x4
#घोषणा EHEA_WR_ID_INDEX   EHEA_BMASK_IBM(24, 47)
#घोषणा EHEA_WR_ID_REFILL  EHEA_BMASK_IBM(48, 63)

काष्ठा ehea_vsgentry अणु
	u64 vaddr;
	u32 l_key;
	u32 len;
पूर्ण;

/* maximum number of sg entries allowed in a WQE */
#घोषणा EHEA_MAX_WQE_SG_ENTRIES  	252
#घोषणा SWQE2_MAX_IMM            	(0xD0 - 0x30)
#घोषणा SWQE3_MAX_IMM            	224

/* tx control flags क्रम swqe */
#घोषणा EHEA_SWQE_CRC                   0x8000
#घोषणा EHEA_SWQE_IP_CHECKSUM           0x4000
#घोषणा EHEA_SWQE_TCP_CHECKSUM          0x2000
#घोषणा EHEA_SWQE_TSO                   0x1000
#घोषणा EHEA_SWQE_SIGNALLED_COMPLETION  0x0800
#घोषणा EHEA_SWQE_VLAN_INSERT           0x0400
#घोषणा EHEA_SWQE_IMM_DATA_PRESENT      0x0200
#घोषणा EHEA_SWQE_DESCRIPTORS_PRESENT   0x0100
#घोषणा EHEA_SWQE_WRAP_CTL_REC          0x0080
#घोषणा EHEA_SWQE_WRAP_CTL_FORCE        0x0040
#घोषणा EHEA_SWQE_BIND                  0x0020
#घोषणा EHEA_SWQE_PURGE                 0x0010

/* माप(काष्ठा ehea_swqe) less the जोड़ */
#घोषणा SWQE_HEADER_SIZE		32

काष्ठा ehea_swqe अणु
	u64 wr_id;
	u16 tx_control;
	u16 vlan_tag;
	u8 reserved1;
	u8 ip_start;
	u8 ip_end;
	u8 immediate_data_length;
	u8 tcp_offset;
	u8 reserved2;
	u16 reserved2b;
	u8 wrap_tag;
	u8 descriptors;		/* number of valid descriptors in WQE */
	u16 reserved3;
	u16 reserved4;
	u16 mss;
	u32 reserved5;
	जोड़ अणु
		/*  Send WQE Format 1 */
		काष्ठा अणु
			काष्ठा ehea_vsgentry sg_list[EHEA_MAX_WQE_SG_ENTRIES];
		पूर्ण no_immediate_data;

		/*  Send WQE Format 2 */
		काष्ठा अणु
			काष्ठा ehea_vsgentry sg_entry;
			/* 0x30 */
			u8 immediate_data[SWQE2_MAX_IMM];
			/* 0xd0 */
			काष्ठा ehea_vsgentry sg_list[EHEA_MAX_WQE_SG_ENTRIES-1];
		पूर्ण immdata_desc __packed;

		/*  Send WQE Format 3 */
		काष्ठा अणु
			u8 immediate_data[SWQE3_MAX_IMM];
		पूर्ण immdata_nodesc;
	पूर्ण u;
पूर्ण;

काष्ठा ehea_rwqe अणु
	u64 wr_id;		/* work request ID */
	u8 reserved1[5];
	u8 data_segments;
	u16 reserved2;
	u64 reserved3;
	u64 reserved4;
	काष्ठा ehea_vsgentry sg_list[EHEA_MAX_WQE_SG_ENTRIES];
पूर्ण;

#घोषणा EHEA_CQE_VLAN_TAG_XTRACT   0x0400

#घोषणा EHEA_CQE_TYPE_RQ           0x60
#घोषणा EHEA_CQE_STAT_ERR_MASK     0x700F
#घोषणा EHEA_CQE_STAT_FAT_ERR_MASK 0xF
#घोषणा EHEA_CQE_BLIND_CKSUM       0x8000
#घोषणा EHEA_CQE_STAT_ERR_TCP      0x4000
#घोषणा EHEA_CQE_STAT_ERR_IP       0x2000
#घोषणा EHEA_CQE_STAT_ERR_CRC      0x1000

/* Defines which bad send cqe stati lead to a port reset */
#घोषणा EHEA_CQE_STAT_RESET_MASK   0x0002

काष्ठा ehea_cqe अणु
	u64 wr_id;		/* work request ID from WQE */
	u8 type;
	u8 valid;
	u16 status;
	u16 reserved1;
	u16 num_bytes_transfered;
	u16 vlan_tag;
	u16 inet_checksum_value;
	u8 reserved2;
	u8 header_length;
	u16 reserved3;
	u16 page_offset;
	u16 wqe_count;
	u32 qp_token;
	u32 बारtamp;
	u32 reserved4;
	u64 reserved5[3];
पूर्ण;

#घोषणा EHEA_EQE_VALID           EHEA_BMASK_IBM(0, 0)
#घोषणा EHEA_EQE_IS_CQE          EHEA_BMASK_IBM(1, 1)
#घोषणा EHEA_EQE_IDENTIFIER      EHEA_BMASK_IBM(2, 7)
#घोषणा EHEA_EQE_QP_CQ_NUMBER    EHEA_BMASK_IBM(8, 31)
#घोषणा EHEA_EQE_QP_TOKEN        EHEA_BMASK_IBM(32, 63)
#घोषणा EHEA_EQE_CQ_TOKEN        EHEA_BMASK_IBM(32, 63)
#घोषणा EHEA_EQE_KEY             EHEA_BMASK_IBM(32, 63)
#घोषणा EHEA_EQE_PORT_NUMBER     EHEA_BMASK_IBM(56, 63)
#घोषणा EHEA_EQE_EQ_NUMBER       EHEA_BMASK_IBM(48, 63)
#घोषणा EHEA_EQE_SM_ID           EHEA_BMASK_IBM(48, 63)
#घोषणा EHEA_EQE_SM_MECH_NUMBER  EHEA_BMASK_IBM(48, 55)
#घोषणा EHEA_EQE_SM_PORT_NUMBER  EHEA_BMASK_IBM(56, 63)

#घोषणा EHEA_AER_RESTYPE_QP  0x8
#घोषणा EHEA_AER_RESTYPE_CQ  0x4
#घोषणा EHEA_AER_RESTYPE_EQ  0x3

/* Defines which affiliated errors lead to a port reset */
#घोषणा EHEA_AER_RESET_MASK   0xFFFFFFFFFEFFFFFFULL
#घोषणा EHEA_AERR_RESET_MASK  0xFFFFFFFFFFFFFFFFULL

काष्ठा ehea_eqe अणु
	u64 entry;
पूर्ण;

#घोषणा ERROR_DATA_LENGTH  EHEA_BMASK_IBM(52, 63)
#घोषणा ERROR_DATA_TYPE    EHEA_BMASK_IBM(0, 7)

अटल अंतरभूत व्योम *hw_qeit_calc(काष्ठा hw_queue *queue, u64 q_offset)
अणु
	काष्ठा ehea_page *current_page;

	अगर (q_offset >= queue->queue_length)
		q_offset -= queue->queue_length;
	current_page = (queue->queue_pages)[q_offset >> EHEA_PAGESHIFT];
	वापस &current_page->entries[q_offset & (EHEA_PAGESIZE - 1)];
पूर्ण

अटल अंतरभूत व्योम *hw_qeit_get(काष्ठा hw_queue *queue)
अणु
	वापस hw_qeit_calc(queue, queue->current_q_offset);
पूर्ण

अटल अंतरभूत व्योम hw_qeit_inc(काष्ठा hw_queue *queue)
अणु
	queue->current_q_offset += queue->qe_size;
	अगर (queue->current_q_offset >= queue->queue_length) अणु
		queue->current_q_offset = 0;
		/* toggle the valid flag */
		queue->toggle_state = (~queue->toggle_state) & 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *hw_qeit_get_inc(काष्ठा hw_queue *queue)
अणु
	व्योम *retvalue = hw_qeit_get(queue);
	hw_qeit_inc(queue);
	वापस retvalue;
पूर्ण

अटल अंतरभूत व्योम *hw_qeit_get_inc_valid(काष्ठा hw_queue *queue)
अणु
	काष्ठा ehea_cqe *retvalue = hw_qeit_get(queue);
	u8 valid = retvalue->valid;
	व्योम *pref;

	अगर ((valid >> 7) == (queue->toggle_state & 1)) अणु
		/* this is a good one */
		hw_qeit_inc(queue);
		pref = hw_qeit_calc(queue, queue->current_q_offset);
		prefetch(pref);
		prefetch(pref + 128);
	पूर्ण अन्यथा
		retvalue = शून्य;
	वापस retvalue;
पूर्ण

अटल अंतरभूत व्योम *hw_qeit_get_valid(काष्ठा hw_queue *queue)
अणु
	काष्ठा ehea_cqe *retvalue = hw_qeit_get(queue);
	व्योम *pref;
	u8 valid;

	pref = hw_qeit_calc(queue, queue->current_q_offset);
	prefetch(pref);
	prefetch(pref + 128);
	prefetch(pref + 256);
	valid = retvalue->valid;
	अगर (!((valid >> 7) == (queue->toggle_state & 1)))
		retvalue = शून्य;
	वापस retvalue;
पूर्ण

अटल अंतरभूत व्योम *hw_qeit_reset(काष्ठा hw_queue *queue)
अणु
	queue->current_q_offset = 0;
	वापस hw_qeit_get(queue);
पूर्ण

अटल अंतरभूत व्योम *hw_qeit_eq_get_inc(काष्ठा hw_queue *queue)
अणु
	u64 last_entry_in_q = queue->queue_length - queue->qe_size;
	व्योम *retvalue;

	retvalue = hw_qeit_get(queue);
	queue->current_q_offset += queue->qe_size;
	अगर (queue->current_q_offset > last_entry_in_q) अणु
		queue->current_q_offset = 0;
		queue->toggle_state = (~queue->toggle_state) & 1;
	पूर्ण
	वापस retvalue;
पूर्ण

अटल अंतरभूत व्योम *hw_eqit_eq_get_inc_valid(काष्ठा hw_queue *queue)
अणु
	व्योम *retvalue = hw_qeit_get(queue);
	u32 qe = *(u8 *)retvalue;
	अगर ((qe >> 7) == (queue->toggle_state & 1))
		hw_qeit_eq_get_inc(queue);
	अन्यथा
		retvalue = शून्य;
	वापस retvalue;
पूर्ण

अटल अंतरभूत काष्ठा ehea_rwqe *ehea_get_next_rwqe(काष्ठा ehea_qp *qp,
						   पूर्णांक rq_nr)
अणु
	काष्ठा hw_queue *queue;

	अगर (rq_nr == 1)
		queue = &qp->hw_rqueue1;
	अन्यथा अगर (rq_nr == 2)
		queue = &qp->hw_rqueue2;
	अन्यथा
		queue = &qp->hw_rqueue3;

	वापस hw_qeit_get_inc(queue);
पूर्ण

अटल अंतरभूत काष्ठा ehea_swqe *ehea_get_swqe(काष्ठा ehea_qp *my_qp,
					      पूर्णांक *wqe_index)
अणु
	काष्ठा hw_queue *queue = &my_qp->hw_squeue;
	काष्ठा ehea_swqe *wqe_p;

	*wqe_index = (queue->current_q_offset) >> (7 + EHEA_SG_SQ);
	wqe_p = hw_qeit_get_inc(&my_qp->hw_squeue);

	वापस wqe_p;
पूर्ण

अटल अंतरभूत व्योम ehea_post_swqe(काष्ठा ehea_qp *my_qp, काष्ठा ehea_swqe *swqe)
अणु
	iosync();
	ehea_update_sqa(my_qp, 1);
पूर्ण

अटल अंतरभूत काष्ठा ehea_cqe *ehea_poll_rq1(काष्ठा ehea_qp *qp, पूर्णांक *wqe_index)
अणु
	काष्ठा hw_queue *queue = &qp->hw_rqueue1;

	*wqe_index = (queue->current_q_offset) >> (7 + EHEA_SG_RQ1);
	वापस hw_qeit_get_valid(queue);
पूर्ण

अटल अंतरभूत व्योम ehea_inc_cq(काष्ठा ehea_cq *cq)
अणु
	hw_qeit_inc(&cq->hw_queue);
पूर्ण

अटल अंतरभूत व्योम ehea_inc_rq1(काष्ठा ehea_qp *qp)
अणु
	hw_qeit_inc(&qp->hw_rqueue1);
पूर्ण

अटल अंतरभूत काष्ठा ehea_cqe *ehea_poll_cq(काष्ठा ehea_cq *my_cq)
अणु
	वापस hw_qeit_get_valid(&my_cq->hw_queue);
पूर्ण

#घोषणा EHEA_CQ_REGISTER_ORIG 0
#घोषणा EHEA_EQ_REGISTER_ORIG 0

क्रमागत ehea_eq_type अणु
	EHEA_EQ = 0,		/* event queue              */
	EHEA_NEQ		/* notअगरication event queue */
पूर्ण;

काष्ठा ehea_eq *ehea_create_eq(काष्ठा ehea_adapter *adapter,
			       क्रमागत ehea_eq_type type,
			       स्थिर u32 length, स्थिर u8 eqe_gen);

पूर्णांक ehea_destroy_eq(काष्ठा ehea_eq *eq);

काष्ठा ehea_eqe *ehea_poll_eq(काष्ठा ehea_eq *eq);

काष्ठा ehea_cq *ehea_create_cq(काष्ठा ehea_adapter *adapter, पूर्णांक cqe,
			       u64 eq_handle, u32 cq_token);

पूर्णांक ehea_destroy_cq(काष्ठा ehea_cq *cq);

काष्ठा ehea_qp *ehea_create_qp(काष्ठा ehea_adapter *adapter, u32 pd,
			       काष्ठा ehea_qp_init_attr *init_attr);

पूर्णांक ehea_destroy_qp(काष्ठा ehea_qp *qp);

पूर्णांक ehea_reg_kernel_mr(काष्ठा ehea_adapter *adapter, काष्ठा ehea_mr *mr);

पूर्णांक ehea_gen_smr(काष्ठा ehea_adapter *adapter, काष्ठा ehea_mr *old_mr,
		 काष्ठा ehea_mr *shared_mr);

पूर्णांक ehea_rem_mr(काष्ठा ehea_mr *mr);

u64 ehea_error_data(काष्ठा ehea_adapter *adapter, u64 res_handle,
		    u64 *aer, u64 *aerr);

पूर्णांक ehea_add_sect_bmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages);
पूर्णांक ehea_rem_sect_bmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages);
पूर्णांक ehea_create_busmap(व्योम);
व्योम ehea_destroy_busmap(व्योम);
u64 ehea_map_vaddr(व्योम *caddr);

#पूर्ण_अगर	/* __EHEA_QMR_H__ */
