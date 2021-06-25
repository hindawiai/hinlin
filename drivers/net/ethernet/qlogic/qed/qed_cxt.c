<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_rdma.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sriov.h"

/* QM स्थिरants */
#घोषणा QM_PQ_ELEMENT_SIZE	4 /* in bytes */

/* Doorbell-Queue स्थिरants */
#घोषणा DQ_RANGE_SHIFT		4
#घोषणा DQ_RANGE_ALIGN		BIT(DQ_RANGE_SHIFT)

/* Searcher स्थिरants */
#घोषणा SRC_MIN_NUM_ELEMS 256

/* Timers स्थिरants */
#घोषणा TM_SHIFT        7
#घोषणा TM_ALIGN        BIT(TM_SHIFT)
#घोषणा TM_ELEM_SIZE    4

#घोषणा ILT_DEFAULT_HW_P_SIZE	4

#घोषणा ILT_PAGE_IN_BYTES(hw_p_size)	(1U << ((hw_p_size) + 12))
#घोषणा ILT_CFG_REG(cli, reg)	PSWRQ2_REG_ ## cli ## _ ## reg ## _RT_OFFSET

/* ILT entry काष्ठाure */
#घोषणा ILT_ENTRY_PHY_ADDR_MASK		(~0ULL >> 12)
#घोषणा ILT_ENTRY_PHY_ADDR_SHIFT	0
#घोषणा ILT_ENTRY_VALID_MASK		0x1ULL
#घोषणा ILT_ENTRY_VALID_SHIFT		52
#घोषणा ILT_ENTRY_IN_REGS		2
#घोषणा ILT_REG_SIZE_IN_BYTES		4

/* connection context जोड़ */
जोड़ conn_context अणु
	काष्ठा e4_core_conn_context core_ctx;
	काष्ठा e4_eth_conn_context eth_ctx;
	काष्ठा e4_iscsi_conn_context iscsi_ctx;
	काष्ठा e4_fcoe_conn_context fcoe_ctx;
	काष्ठा e4_roce_conn_context roce_ctx;
पूर्ण;

/* TYPE-0 task context - iSCSI, FCOE */
जोड़ type0_task_context अणु
	काष्ठा e4_iscsi_task_context iscsi_ctx;
	काष्ठा e4_fcoe_task_context fcoe_ctx;
पूर्ण;

/* TYPE-1 task context - ROCE */
जोड़ type1_task_context अणु
	काष्ठा e4_rdma_task_context roce_ctx;
पूर्ण;

काष्ठा src_ent अणु
	__u8				opaque[56];
	__be64				next;
पूर्ण;

#घोषणा CDUT_SEG_ALIGNMET		3 /* in 4k chunks */
#घोषणा CDUT_SEG_ALIGNMET_IN_BYTES	BIT(CDUT_SEG_ALIGNMET + 12)

#घोषणा CONN_CXT_SIZE(p_hwfn) \
	ALIGNED_TYPE_SIZE(जोड़ conn_context, p_hwfn)

#घोषणा SRQ_CXT_SIZE (माप(काष्ठा rdma_srq_context))
#घोषणा XRC_SRQ_CXT_SIZE (माप(काष्ठा rdma_xrc_srq_context))

#घोषणा TYPE0_TASK_CXT_SIZE(p_hwfn) \
	ALIGNED_TYPE_SIZE(जोड़ type0_task_context, p_hwfn)

/* Alignment is inherent to the type1_task_context काष्ठाure */
#घोषणा TYPE1_TASK_CXT_SIZE(p_hwfn) माप(जोड़ type1_task_context)

अटल bool src_proto(क्रमागत protocol_type type)
अणु
	वापस type == PROTOCOLID_ISCSI ||
	       type == PROTOCOLID_FCOE ||
	       type == PROTOCOLID_IWARP;
पूर्ण

अटल bool पंचांग_cid_proto(क्रमागत protocol_type type)
अणु
	वापस type == PROTOCOLID_ISCSI ||
	       type == PROTOCOLID_FCOE ||
	       type == PROTOCOLID_ROCE ||
	       type == PROTOCOLID_IWARP;
पूर्ण

अटल bool पंचांग_tid_proto(क्रमागत protocol_type type)
अणु
	वापस type == PROTOCOLID_FCOE;
पूर्ण

/* counts the iids क्रम the CDU/CDUC ILT client configuration */
काष्ठा qed_cdu_iids अणु
	u32 pf_cids;
	u32 per_vf_cids;
पूर्ण;

अटल व्योम qed_cxt_cdu_iids(काष्ठा qed_cxt_mngr *p_mngr,
			     काष्ठा qed_cdu_iids *iids)
अणु
	u32 type;

	क्रम (type = 0; type < MAX_CONN_TYPES; type++) अणु
		iids->pf_cids += p_mngr->conn_cfg[type].cid_count;
		iids->per_vf_cids += p_mngr->conn_cfg[type].cids_per_vf;
	पूर्ण
पूर्ण

/* counts the iids क्रम the Searcher block configuration */
काष्ठा qed_src_iids अणु
	u32 pf_cids;
	u32 per_vf_cids;
पूर्ण;

अटल व्योम qed_cxt_src_iids(काष्ठा qed_cxt_mngr *p_mngr,
			     काष्ठा qed_src_iids *iids)
अणु
	u32 i;

	क्रम (i = 0; i < MAX_CONN_TYPES; i++) अणु
		अगर (!src_proto(i))
			जारी;

		iids->pf_cids += p_mngr->conn_cfg[i].cid_count;
		iids->per_vf_cids += p_mngr->conn_cfg[i].cids_per_vf;
	पूर्ण

	/* Add L2 filtering filters in addition */
	iids->pf_cids += p_mngr->arfs_count;
पूर्ण

/* counts the iids क्रम the Timers block configuration */
काष्ठा qed_पंचांग_iids अणु
	u32 pf_cids;
	u32 pf_tids[NUM_TASK_PF_SEGMENTS];	/* per segment */
	u32 pf_tids_total;
	u32 per_vf_cids;
	u32 per_vf_tids;
पूर्ण;

अटल व्योम qed_cxt_पंचांग_iids(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_cxt_mngr *p_mngr,
			    काष्ठा qed_पंचांग_iids *iids)
अणु
	bool पंचांग_vf_required = false;
	bool पंचांग_required = false;
	पूर्णांक i, j;

	/* Timers is a special हाल -> we करोn't count how many cids require
	 * समयrs but what's the max cid that will be used by the समयr block.
	 * thereक्रमe we traverse in reverse order, and once we hit a protocol
	 * that requires the समयrs memory, we'll sum all the protocols up
	 * to that one.
	 */
	क्रम (i = MAX_CONN_TYPES - 1; i >= 0; i--) अणु
		काष्ठा qed_conn_type_cfg *p_cfg = &p_mngr->conn_cfg[i];

		अगर (पंचांग_cid_proto(i) || पंचांग_required) अणु
			अगर (p_cfg->cid_count)
				पंचांग_required = true;

			iids->pf_cids += p_cfg->cid_count;
		पूर्ण

		अगर (पंचांग_cid_proto(i) || पंचांग_vf_required) अणु
			अगर (p_cfg->cids_per_vf)
				पंचांग_vf_required = true;

			iids->per_vf_cids += p_cfg->cids_per_vf;
		पूर्ण

		अगर (पंचांग_tid_proto(i)) अणु
			काष्ठा qed_tid_seg *segs = p_cfg->tid_seg;

			/* क्रम each segment there is at most one
			 * protocol क्रम which count is not 0.
			 */
			क्रम (j = 0; j < NUM_TASK_PF_SEGMENTS; j++)
				iids->pf_tids[j] += segs[j].count;

			/* The last array elelment is क्रम the VFs. As क्रम PF
			 * segments there can be only one protocol क्रम
			 * which this value is not 0.
			 */
			iids->per_vf_tids += segs[NUM_TASK_PF_SEGMENTS].count;
		पूर्ण
	पूर्ण

	iids->pf_cids = roundup(iids->pf_cids, TM_ALIGN);
	iids->per_vf_cids = roundup(iids->per_vf_cids, TM_ALIGN);
	iids->per_vf_tids = roundup(iids->per_vf_tids, TM_ALIGN);

	क्रम (iids->pf_tids_total = 0, j = 0; j < NUM_TASK_PF_SEGMENTS; j++) अणु
		iids->pf_tids[j] = roundup(iids->pf_tids[j], TM_ALIGN);
		iids->pf_tids_total += iids->pf_tids[j];
	पूर्ण
पूर्ण

अटल व्योम qed_cxt_qm_iids(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_qm_iids *iids)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_tid_seg *segs;
	u32 vf_cids = 0, type, j;
	u32 vf_tids = 0;

	क्रम (type = 0; type < MAX_CONN_TYPES; type++) अणु
		iids->cids += p_mngr->conn_cfg[type].cid_count;
		vf_cids += p_mngr->conn_cfg[type].cids_per_vf;

		segs = p_mngr->conn_cfg[type].tid_seg;
		/* क्रम each segment there is at most one
		 * protocol क्रम which count is not 0.
		 */
		क्रम (j = 0; j < NUM_TASK_PF_SEGMENTS; j++)
			iids->tids += segs[j].count;

		/* The last array elelment is क्रम the VFs. As क्रम PF
		 * segments there can be only one protocol क्रम
		 * which this value is not 0.
		 */
		vf_tids += segs[NUM_TASK_PF_SEGMENTS].count;
	पूर्ण

	iids->vf_cids = vf_cids;
	iids->tids += vf_tids * p_mngr->vf_count;

	DP_VERBOSE(p_hwfn, QED_MSG_ILT,
		   "iids: CIDS %08x vf_cids %08x tids %08x vf_tids %08x\n",
		   iids->cids, iids->vf_cids, iids->tids, vf_tids);
पूर्ण

अटल काष्ठा qed_tid_seg *qed_cxt_tid_seg_info(काष्ठा qed_hwfn *p_hwfn,
						u32 seg)
अणु
	काष्ठा qed_cxt_mngr *p_cfg = p_hwfn->p_cxt_mngr;
	u32 i;

	/* Find the protocol with tid count > 0 क्रम this segment.
	 * Note: there can only be one and this is alपढ़ोy validated.
	 */
	क्रम (i = 0; i < MAX_CONN_TYPES; i++)
		अगर (p_cfg->conn_cfg[i].tid_seg[seg].count)
			वापस &p_cfg->conn_cfg[i].tid_seg[seg];
	वापस शून्य;
पूर्ण

अटल व्योम qed_cxt_set_srq_count(काष्ठा qed_hwfn *p_hwfn,
				  u32 num_srqs, u32 num_xrc_srqs)
अणु
	काष्ठा qed_cxt_mngr *p_mgr = p_hwfn->p_cxt_mngr;

	p_mgr->srq_count = num_srqs;
	p_mgr->xrc_srq_count = num_xrc_srqs;
पूर्ण

u32 qed_cxt_get_ilt_page_size(काष्ठा qed_hwfn *p_hwfn,
			      क्रमागत ilt_clients ilt_client)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_ilt_client_cfg *p_cli = &p_mngr->clients[ilt_client];

	वापस ILT_PAGE_IN_BYTES(p_cli->p_size.val);
पूर्ण

अटल u32 qed_cxt_xrc_srqs_per_page(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 page_size;

	page_size = qed_cxt_get_ilt_page_size(p_hwfn, ILT_CLI_TSDM);
	वापस page_size / XRC_SRQ_CXT_SIZE;
पूर्ण

u32 qed_cxt_get_total_srq_count(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mgr = p_hwfn->p_cxt_mngr;
	u32 total_srqs;

	total_srqs = p_mgr->srq_count + p_mgr->xrc_srq_count;

	वापस total_srqs;
पूर्ण

/* set the iids count per protocol */
अटल व्योम qed_cxt_set_proto_cid_count(काष्ठा qed_hwfn *p_hwfn,
					क्रमागत protocol_type type,
					u32 cid_count, u32 vf_cid_cnt)
अणु
	काष्ठा qed_cxt_mngr *p_mgr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_conn_type_cfg *p_conn = &p_mgr->conn_cfg[type];

	p_conn->cid_count = roundup(cid_count, DQ_RANGE_ALIGN);
	p_conn->cids_per_vf = roundup(vf_cid_cnt, DQ_RANGE_ALIGN);

	अगर (type == PROTOCOLID_ROCE) अणु
		u32 page_sz = p_mgr->clients[ILT_CLI_CDUC].p_size.val;
		u32 cxt_size = CONN_CXT_SIZE(p_hwfn);
		u32 elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
		u32 align = elems_per_page * DQ_RANGE_ALIGN;

		p_conn->cid_count = roundup(p_conn->cid_count, align);
	पूर्ण
पूर्ण

u32 qed_cxt_get_proto_cid_count(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत protocol_type type, u32 *vf_cid)
अणु
	अगर (vf_cid)
		*vf_cid = p_hwfn->p_cxt_mngr->conn_cfg[type].cids_per_vf;

	वापस p_hwfn->p_cxt_mngr->conn_cfg[type].cid_count;
पूर्ण

u32 qed_cxt_get_proto_cid_start(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत protocol_type type)
अणु
	वापस p_hwfn->p_cxt_mngr->acquired[type].start_cid;
पूर्ण

u32 qed_cxt_get_proto_tid_count(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत protocol_type type)
अणु
	u32 cnt = 0;
	पूर्णांक i;

	क्रम (i = 0; i < TASK_SEGMENTS; i++)
		cnt += p_hwfn->p_cxt_mngr->conn_cfg[type].tid_seg[i].count;

	वापस cnt;
पूर्ण

अटल व्योम qed_cxt_set_proto_tid_count(काष्ठा qed_hwfn *p_hwfn,
					क्रमागत protocol_type proto,
					u8 seg,
					u8 seg_type, u32 count, bool has_fl)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_tid_seg *p_seg = &p_mngr->conn_cfg[proto].tid_seg[seg];

	p_seg->count = count;
	p_seg->has_fl_mem = has_fl;
	p_seg->type = seg_type;
पूर्ण

अटल व्योम qed_ilt_cli_blk_fill(काष्ठा qed_ilt_client_cfg *p_cli,
				 काष्ठा qed_ilt_cli_blk *p_blk,
				 u32 start_line, u32 total_size, u32 elem_size)
अणु
	u32 ilt_size = ILT_PAGE_IN_BYTES(p_cli->p_size.val);

	/* verअगरy thatits called only once क्रम each block */
	अगर (p_blk->total_size)
		वापस;

	p_blk->total_size = total_size;
	p_blk->real_size_in_page = 0;
	अगर (elem_size)
		p_blk->real_size_in_page = (ilt_size / elem_size) * elem_size;
	p_blk->start_line = start_line;
पूर्ण

अटल व्योम qed_ilt_cli_adv_line(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ilt_client_cfg *p_cli,
				 काष्ठा qed_ilt_cli_blk *p_blk,
				 u32 *p_line, क्रमागत ilt_clients client_id)
अणु
	अगर (!p_blk->total_size)
		वापस;

	अगर (!p_cli->active)
		p_cli->first.val = *p_line;

	p_cli->active = true;
	*p_line += DIV_ROUND_UP(p_blk->total_size, p_blk->real_size_in_page);
	p_cli->last.val = *p_line - 1;

	DP_VERBOSE(p_hwfn, QED_MSG_ILT,
		   "ILT[Client %d] - Lines: [%08x - %08x]. Block - Size %08x [Real %08x] Start line %d\n",
		   client_id, p_cli->first.val,
		   p_cli->last.val, p_blk->total_size,
		   p_blk->real_size_in_page, p_blk->start_line);
पूर्ण

अटल u32 qed_ilt_get_dynamic_line_cnt(काष्ठा qed_hwfn *p_hwfn,
					क्रमागत ilt_clients ilt_client)
अणु
	u32 cid_count = p_hwfn->p_cxt_mngr->conn_cfg[PROTOCOLID_ROCE].cid_count;
	काष्ठा qed_ilt_client_cfg *p_cli;
	u32 lines_to_skip = 0;
	u32 cxts_per_p;

	अगर (ilt_client == ILT_CLI_CDUC) अणु
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];

		cxts_per_p = ILT_PAGE_IN_BYTES(p_cli->p_size.val) /
		    (u32) CONN_CXT_SIZE(p_hwfn);

		lines_to_skip = cid_count / cxts_per_p;
	पूर्ण

	वापस lines_to_skip;
पूर्ण

अटल काष्ठा qed_ilt_client_cfg *qed_cxt_set_cli(काष्ठा qed_ilt_client_cfg
						  *p_cli)
अणु
	p_cli->active = false;
	p_cli->first.val = 0;
	p_cli->last.val = 0;
	वापस p_cli;
पूर्ण

अटल काष्ठा qed_ilt_cli_blk *qed_cxt_set_blk(काष्ठा qed_ilt_cli_blk *p_blk)
अणु
	p_blk->total_size = 0;
	वापस p_blk;
पूर्ण

अटल व्योम qed_cxt_ilt_blk_reset(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *clients = p_hwfn->p_cxt_mngr->clients;
	u32 cli_idx, blk_idx;

	क्रम (cli_idx = 0; cli_idx < MAX_ILT_CLIENTS; cli_idx++) अणु
		क्रम (blk_idx = 0; blk_idx < ILT_CLI_PF_BLOCKS; blk_idx++)
			clients[cli_idx].pf_blks[blk_idx].total_size = 0;

		क्रम (blk_idx = 0; blk_idx < ILT_CLI_VF_BLOCKS; blk_idx++)
			clients[cli_idx].vf_blks[blk_idx].total_size = 0;
	पूर्ण
पूर्ण

पूर्णांक qed_cxt_cfg_ilt_compute(काष्ठा qed_hwfn *p_hwfn, u32 *line_count)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 curr_line, total, i, task_size, line;
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	काष्ठा qed_cdu_iids cdu_iids;
	काष्ठा qed_src_iids src_iids;
	काष्ठा qed_qm_iids qm_iids;
	काष्ठा qed_पंचांग_iids पंचांग_iids;
	काष्ठा qed_tid_seg *p_seg;

	स_रखो(&qm_iids, 0, माप(qm_iids));
	स_रखो(&cdu_iids, 0, माप(cdu_iids));
	स_रखो(&src_iids, 0, माप(src_iids));
	स_रखो(&पंचांग_iids, 0, माप(पंचांग_iids));

	p_mngr->pf_start_line = RESC_START(p_hwfn, QED_ILT);

	/* Reset all ILT blocks at the beginning of ILT computing in order
	 * to prevent memory allocation क्रम irrelevant blocks afterwards.
	 */
	qed_cxt_ilt_blk_reset(p_hwfn);

	DP_VERBOSE(p_hwfn, QED_MSG_ILT,
		   "hwfn [%d] - Set context manager starting line to be 0x%08x\n",
		   p_hwfn->my_id, p_hwfn->p_cxt_mngr->pf_start_line);

	/* CDUC */
	p_cli = qed_cxt_set_cli(&p_mngr->clients[ILT_CLI_CDUC]);

	curr_line = p_mngr->pf_start_line;

	/* CDUC PF */
	p_cli->pf_total_lines = 0;

	/* get the counters क्रम the CDUC and QM clients  */
	qed_cxt_cdu_iids(p_mngr, &cdu_iids);

	p_blk = qed_cxt_set_blk(&p_cli->pf_blks[CDUC_BLK]);

	total = cdu_iids.pf_cids * CONN_CXT_SIZE(p_hwfn);

	qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line,
			     total, CONN_CXT_SIZE(p_hwfn));

	qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line, ILT_CLI_CDUC);
	p_cli->pf_total_lines = curr_line - p_blk->start_line;

	p_blk->dynamic_line_cnt = qed_ilt_get_dynamic_line_cnt(p_hwfn,
							       ILT_CLI_CDUC);

	/* CDUC VF */
	p_blk = qed_cxt_set_blk(&p_cli->vf_blks[CDUC_BLK]);
	total = cdu_iids.per_vf_cids * CONN_CXT_SIZE(p_hwfn);

	qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line,
			     total, CONN_CXT_SIZE(p_hwfn));

	qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line, ILT_CLI_CDUC);
	p_cli->vf_total_lines = curr_line - p_blk->start_line;

	क्रम (i = 1; i < p_mngr->vf_count; i++)
		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_CDUC);

	/* CDUT PF */
	p_cli = qed_cxt_set_cli(&p_mngr->clients[ILT_CLI_CDUT]);
	p_cli->first.val = curr_line;

	/* first the 'working' task memory */
	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		p_seg = qed_cxt_tid_seg_info(p_hwfn, i);
		अगर (!p_seg || p_seg->count == 0)
			जारी;

		p_blk = qed_cxt_set_blk(&p_cli->pf_blks[CDUT_SEG_BLK(i)]);
		total = p_seg->count * p_mngr->task_type_size[p_seg->type];
		qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line, total,
				     p_mngr->task_type_size[p_seg->type]);

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_CDUT);
	पूर्ण

	/* next the 'init' task memory (क्रमced load memory) */
	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		p_seg = qed_cxt_tid_seg_info(p_hwfn, i);
		अगर (!p_seg || p_seg->count == 0)
			जारी;

		p_blk =
		    qed_cxt_set_blk(&p_cli->pf_blks[CDUT_FL_SEG_BLK(i, PF)]);

		अगर (!p_seg->has_fl_mem) अणु
			/* The segment is active (total size pf 'working'
			 * memory is > 0) but has no FL (क्रमced-load, Init)
			 * memory. Thus:
			 *
			 * 1.   The total-size in the corrsponding FL block of
			 *      the ILT client is set to 0 - No ILT line are
			 *      provisioned and no ILT memory allocated.
			 *
			 * 2.   The start-line of said block is set to the
			 *      start line of the matching working memory
			 *      block in the ILT client. This is later used to
			 *      configure the CDU segment offset रेजिस्टरs and
			 *      results in an FL command क्रम TIDs of this
			 *      segement behaves as regular load commands
			 *      (loading TIDs from the working memory).
			 */
			line = p_cli->pf_blks[CDUT_SEG_BLK(i)].start_line;

			qed_ilt_cli_blk_fill(p_cli, p_blk, line, 0, 0);
			जारी;
		पूर्ण
		total = p_seg->count * p_mngr->task_type_size[p_seg->type];

		qed_ilt_cli_blk_fill(p_cli, p_blk,
				     curr_line, total,
				     p_mngr->task_type_size[p_seg->type]);

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_CDUT);
	पूर्ण
	p_cli->pf_total_lines = curr_line - p_cli->pf_blks[0].start_line;

	/* CDUT VF */
	p_seg = qed_cxt_tid_seg_info(p_hwfn, TASK_SEGMENT_VF);
	अगर (p_seg && p_seg->count) अणु
		/* Stricly speaking we need to iterate over all VF
		 * task segment types, but a VF has only 1 segment
		 */

		/* 'working' memory */
		total = p_seg->count * p_mngr->task_type_size[p_seg->type];

		p_blk = qed_cxt_set_blk(&p_cli->vf_blks[CDUT_SEG_BLK(0)]);
		qed_ilt_cli_blk_fill(p_cli, p_blk,
				     curr_line, total,
				     p_mngr->task_type_size[p_seg->type]);

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_CDUT);

		/* 'init' memory */
		p_blk =
		    qed_cxt_set_blk(&p_cli->vf_blks[CDUT_FL_SEG_BLK(0, VF)]);
		अगर (!p_seg->has_fl_mem) अणु
			/* see comment above */
			line = p_cli->vf_blks[CDUT_SEG_BLK(0)].start_line;
			qed_ilt_cli_blk_fill(p_cli, p_blk, line, 0, 0);
		पूर्ण अन्यथा अणु
			task_size = p_mngr->task_type_size[p_seg->type];
			qed_ilt_cli_blk_fill(p_cli, p_blk,
					     curr_line, total, task_size);
			qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
					     ILT_CLI_CDUT);
		पूर्ण
		p_cli->vf_total_lines = curr_line -
		    p_cli->vf_blks[0].start_line;

		/* Now क्रम the rest of the VFs */
		क्रम (i = 1; i < p_mngr->vf_count; i++) अणु
			p_blk = &p_cli->vf_blks[CDUT_SEG_BLK(0)];
			qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
					     ILT_CLI_CDUT);

			p_blk = &p_cli->vf_blks[CDUT_FL_SEG_BLK(0, VF)];
			qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
					     ILT_CLI_CDUT);
		पूर्ण
	पूर्ण

	/* QM */
	p_cli = qed_cxt_set_cli(&p_mngr->clients[ILT_CLI_QM]);
	p_blk = qed_cxt_set_blk(&p_cli->pf_blks[0]);

	qed_cxt_qm_iids(p_hwfn, &qm_iids);
	total = qed_qm_pf_mem_size(qm_iids.cids,
				   qm_iids.vf_cids, qm_iids.tids,
				   p_hwfn->qm_info.num_pqs,
				   p_hwfn->qm_info.num_vf_pqs);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_ILT,
		   "QM ILT Info, (cids=%d, vf_cids=%d, tids=%d, num_pqs=%d, num_vf_pqs=%d, memory_size=%d)\n",
		   qm_iids.cids,
		   qm_iids.vf_cids,
		   qm_iids.tids,
		   p_hwfn->qm_info.num_pqs, p_hwfn->qm_info.num_vf_pqs, total);

	qed_ilt_cli_blk_fill(p_cli, p_blk,
			     curr_line, total * 0x1000,
			     QM_PQ_ELEMENT_SIZE);

	qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line, ILT_CLI_QM);
	p_cli->pf_total_lines = curr_line - p_blk->start_line;

	/* SRC */
	p_cli = qed_cxt_set_cli(&p_mngr->clients[ILT_CLI_SRC]);
	qed_cxt_src_iids(p_mngr, &src_iids);

	/* Both the PF and VFs searcher connections are stored in the per PF
	 * database. Thus sum the PF searcher cids and all the VFs searcher
	 * cids.
	 */
	total = src_iids.pf_cids + src_iids.per_vf_cids * p_mngr->vf_count;
	अगर (total) अणु
		u32 local_max = max_t(u32, total,
				      SRC_MIN_NUM_ELEMS);

		total = roundup_घात_of_two(local_max);

		p_blk = qed_cxt_set_blk(&p_cli->pf_blks[0]);
		qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line,
				     total * माप(काष्ठा src_ent),
				     माप(काष्ठा src_ent));

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_SRC);
		p_cli->pf_total_lines = curr_line - p_blk->start_line;
	पूर्ण

	/* TM PF */
	p_cli = qed_cxt_set_cli(&p_mngr->clients[ILT_CLI_TM]);
	qed_cxt_पंचांग_iids(p_hwfn, p_mngr, &पंचांग_iids);
	total = पंचांग_iids.pf_cids + पंचांग_iids.pf_tids_total;
	अगर (total) अणु
		p_blk = qed_cxt_set_blk(&p_cli->pf_blks[0]);
		qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line,
				     total * TM_ELEM_SIZE, TM_ELEM_SIZE);

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_TM);
		p_cli->pf_total_lines = curr_line - p_blk->start_line;
	पूर्ण

	/* TM VF */
	total = पंचांग_iids.per_vf_cids + पंचांग_iids.per_vf_tids;
	अगर (total) अणु
		p_blk = qed_cxt_set_blk(&p_cli->vf_blks[0]);
		qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line,
				     total * TM_ELEM_SIZE, TM_ELEM_SIZE);

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_TM);

		p_cli->vf_total_lines = curr_line - p_blk->start_line;
		क्रम (i = 1; i < p_mngr->vf_count; i++)
			qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
					     ILT_CLI_TM);
	पूर्ण

	/* TSDM (SRQ CONTEXT) */
	total = qed_cxt_get_total_srq_count(p_hwfn);

	अगर (total) अणु
		p_cli = qed_cxt_set_cli(&p_mngr->clients[ILT_CLI_TSDM]);
		p_blk = qed_cxt_set_blk(&p_cli->pf_blks[SRQ_BLK]);
		qed_ilt_cli_blk_fill(p_cli, p_blk, curr_line,
				     total * SRQ_CXT_SIZE, SRQ_CXT_SIZE);

		qed_ilt_cli_adv_line(p_hwfn, p_cli, p_blk, &curr_line,
				     ILT_CLI_TSDM);
		p_cli->pf_total_lines = curr_line - p_blk->start_line;
	पूर्ण

	*line_count = curr_line - p_hwfn->p_cxt_mngr->pf_start_line;

	अगर (curr_line - p_hwfn->p_cxt_mngr->pf_start_line >
	    RESC_NUM(p_hwfn, QED_ILT))
		वापस -EINVAL;

	वापस 0;
पूर्ण

u32 qed_cxt_cfg_ilt_compute_excess(काष्ठा qed_hwfn *p_hwfn, u32 used_lines)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	u32 excess_lines, available_lines;
	काष्ठा qed_cxt_mngr *p_mngr;
	u32 ilt_page_size, elem_size;
	काष्ठा qed_tid_seg *p_seg;
	पूर्णांक i;

	available_lines = RESC_NUM(p_hwfn, QED_ILT);
	excess_lines = used_lines - available_lines;

	अगर (!excess_lines)
		वापस 0;

	अगर (!QED_IS_RDMA_PERSONALITY(p_hwfn))
		वापस 0;

	p_mngr = p_hwfn->p_cxt_mngr;
	p_cli = &p_mngr->clients[ILT_CLI_CDUT];
	ilt_page_size = ILT_PAGE_IN_BYTES(p_cli->p_size.val);

	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		p_seg = qed_cxt_tid_seg_info(p_hwfn, i);
		अगर (!p_seg || p_seg->count == 0)
			जारी;

		elem_size = p_mngr->task_type_size[p_seg->type];
		अगर (!elem_size)
			जारी;

		वापस (ilt_page_size / elem_size) * excess_lines;
	पूर्ण

	DP_NOTICE(p_hwfn, "failed computing excess ILT lines\n");
	वापस 0;
पूर्ण

अटल व्योम qed_cxt_src_t2_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_src_t2 *p_t2 = &p_hwfn->p_cxt_mngr->src_t2;
	u32 i;

	अगर (!p_t2 || !p_t2->dma_mem)
		वापस;

	क्रम (i = 0; i < p_t2->num_pages; i++)
		अगर (p_t2->dma_mem[i].virt_addr)
			dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
					  p_t2->dma_mem[i].size,
					  p_t2->dma_mem[i].virt_addr,
					  p_t2->dma_mem[i].phys_addr);

	kमुक्त(p_t2->dma_mem);
	p_t2->dma_mem = शून्य;
पूर्ण

अटल पूर्णांक
qed_cxt_t2_alloc_pages(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_src_t2 *p_t2, u32 total_size, u32 page_size)
अणु
	व्योम **p_virt;
	u32 size, i;

	अगर (!p_t2 || !p_t2->dma_mem)
		वापस -EINVAL;

	क्रम (i = 0; i < p_t2->num_pages; i++) अणु
		size = min_t(u32, total_size, page_size);
		p_virt = &p_t2->dma_mem[i].virt_addr;

		*p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					     size,
					     &p_t2->dma_mem[i].phys_addr,
					     GFP_KERNEL);
		अगर (!p_t2->dma_mem[i].virt_addr)
			वापस -ENOMEM;

		स_रखो(*p_virt, 0, size);
		p_t2->dma_mem[i].size = size;
		total_size -= size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_cxt_src_t2_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 conn_num, total_size, ent_per_page, psz, i;
	काष्ठा phys_mem_desc *p_t2_last_page;
	काष्ठा qed_ilt_client_cfg *p_src;
	काष्ठा qed_src_iids src_iids;
	काष्ठा qed_src_t2 *p_t2;
	पूर्णांक rc;

	स_रखो(&src_iids, 0, माप(src_iids));

	/* अगर the SRC ILT client is inactive - there are no connection
	 * requiring the searcer, leave.
	 */
	p_src = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_SRC];
	अगर (!p_src->active)
		वापस 0;

	qed_cxt_src_iids(p_mngr, &src_iids);
	conn_num = src_iids.pf_cids + src_iids.per_vf_cids * p_mngr->vf_count;
	total_size = conn_num * माप(काष्ठा src_ent);

	/* use the same page size as the SRC ILT client */
	psz = ILT_PAGE_IN_BYTES(p_src->p_size.val);
	p_t2 = &p_mngr->src_t2;
	p_t2->num_pages = DIV_ROUND_UP(total_size, psz);

	/* allocate t2 */
	p_t2->dma_mem = kसुस्मृति(p_t2->num_pages, माप(काष्ठा phys_mem_desc),
				GFP_KERNEL);
	अगर (!p_t2->dma_mem) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate t2 table\n");
		rc = -ENOMEM;
		जाओ t2_fail;
	पूर्ण

	rc = qed_cxt_t2_alloc_pages(p_hwfn, p_t2, total_size, psz);
	अगर (rc)
		जाओ t2_fail;

	/* Set the t2 poपूर्णांकers */

	/* entries per page - must be a घातer of two */
	ent_per_page = psz / माप(काष्ठा src_ent);

	p_t2->first_मुक्त = (u64)p_t2->dma_mem[0].phys_addr;

	p_t2_last_page = &p_t2->dma_mem[(conn_num - 1) / ent_per_page];
	p_t2->last_मुक्त = (u64)p_t2_last_page->phys_addr +
	    ((conn_num - 1) & (ent_per_page - 1)) * माप(काष्ठा src_ent);

	क्रम (i = 0; i < p_t2->num_pages; i++) अणु
		u32 ent_num = min_t(u32,
				    ent_per_page,
				    conn_num);
		काष्ठा src_ent *entries = p_t2->dma_mem[i].virt_addr;
		u64 p_ent_phys = (u64)p_t2->dma_mem[i].phys_addr, val;
		u32 j;

		क्रम (j = 0; j < ent_num - 1; j++) अणु
			val = p_ent_phys + (j + 1) * माप(काष्ठा src_ent);
			entries[j].next = cpu_to_be64(val);
		पूर्ण

		अगर (i < p_t2->num_pages - 1)
			val = (u64)p_t2->dma_mem[i + 1].phys_addr;
		अन्यथा
			val = 0;
		entries[j].next = cpu_to_be64(val);

		conn_num -= ent_num;
	पूर्ण

	वापस 0;

t2_fail:
	qed_cxt_src_t2_मुक्त(p_hwfn);
	वापस rc;
पूर्ण

#घोषणा क्रम_each_ilt_valid_client(pos, clients)	\
	क्रम (pos = 0; pos < MAX_ILT_CLIENTS; pos++)	\
		अगर (!clients[pos].active) अणु	\
			जारी;		\
		पूर्ण अन्यथा				\

/* Total number of ILT lines used by this PF */
अटल u32 qed_cxt_ilt_shaकरोw_size(काष्ठा qed_ilt_client_cfg *ilt_clients)
अणु
	u32 size = 0;
	u32 i;

	क्रम_each_ilt_valid_client(i, ilt_clients)
	    size += (ilt_clients[i].last.val - ilt_clients[i].first.val + 1);

	वापस size;
पूर्ण

अटल व्योम qed_ilt_shaकरोw_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli = p_hwfn->p_cxt_mngr->clients;
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 ilt_size, i;

	ilt_size = qed_cxt_ilt_shaकरोw_size(p_cli);

	क्रम (i = 0; p_mngr->ilt_shaकरोw && i < ilt_size; i++) अणु
		काष्ठा phys_mem_desc *p_dma = &p_mngr->ilt_shaकरोw[i];

		अगर (p_dma->virt_addr)
			dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
					  p_dma->size, p_dma->virt_addr,
					  p_dma->phys_addr);
		p_dma->virt_addr = शून्य;
	पूर्ण
	kमुक्त(p_mngr->ilt_shaकरोw);
पूर्ण

अटल पूर्णांक qed_ilt_blk_alloc(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ilt_cli_blk *p_blk,
			     क्रमागत ilt_clients ilt_client,
			     u32 start_line_offset)
अणु
	काष्ठा phys_mem_desc *ilt_shaकरोw = p_hwfn->p_cxt_mngr->ilt_shaकरोw;
	u32 lines, line, sz_left, lines_to_skip = 0;

	/* Special handling क्रम RoCE that supports dynamic allocation */
	अगर (QED_IS_RDMA_PERSONALITY(p_hwfn) &&
	    ((ilt_client == ILT_CLI_CDUT) || ilt_client == ILT_CLI_TSDM))
		वापस 0;

	lines_to_skip = p_blk->dynamic_line_cnt;

	अगर (!p_blk->total_size)
		वापस 0;

	sz_left = p_blk->total_size;
	lines = DIV_ROUND_UP(sz_left, p_blk->real_size_in_page) - lines_to_skip;
	line = p_blk->start_line + start_line_offset -
	    p_hwfn->p_cxt_mngr->pf_start_line + lines_to_skip;

	क्रम (; lines; lines--) अणु
		dma_addr_t p_phys;
		व्योम *p_virt;
		u32 size;

		size = min_t(u32, sz_left, p_blk->real_size_in_page);
		p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev, size,
					    &p_phys, GFP_KERNEL);
		अगर (!p_virt)
			वापस -ENOMEM;

		ilt_shaकरोw[line].phys_addr = p_phys;
		ilt_shaकरोw[line].virt_addr = p_virt;
		ilt_shaकरोw[line].size = size;

		DP_VERBOSE(p_hwfn, QED_MSG_ILT,
			   "ILT shadow: Line [%d] Physical 0x%llx Virtual %p Size %d\n",
			    line, (u64)p_phys, p_virt, size);

		sz_left -= size;
		line++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_ilt_shaकरोw_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_ilt_client_cfg *clients = p_mngr->clients;
	काष्ठा qed_ilt_cli_blk *p_blk;
	u32 size, i, j, k;
	पूर्णांक rc;

	size = qed_cxt_ilt_shaकरोw_size(clients);
	p_mngr->ilt_shaकरोw = kसुस्मृति(size, माप(काष्ठा phys_mem_desc),
				     GFP_KERNEL);
	अगर (!p_mngr->ilt_shaकरोw) अणु
		rc = -ENOMEM;
		जाओ ilt_shaकरोw_fail;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_ILT,
		   "Allocated 0x%x bytes for ilt shadow\n",
		   (u32)(size * माप(काष्ठा phys_mem_desc)));

	क्रम_each_ilt_valid_client(i, clients) अणु
		क्रम (j = 0; j < ILT_CLI_PF_BLOCKS; j++) अणु
			p_blk = &clients[i].pf_blks[j];
			rc = qed_ilt_blk_alloc(p_hwfn, p_blk, i, 0);
			अगर (rc)
				जाओ ilt_shaकरोw_fail;
		पूर्ण
		क्रम (k = 0; k < p_mngr->vf_count; k++) अणु
			क्रम (j = 0; j < ILT_CLI_VF_BLOCKS; j++) अणु
				u32 lines = clients[i].vf_total_lines * k;

				p_blk = &clients[i].vf_blks[j];
				rc = qed_ilt_blk_alloc(p_hwfn, p_blk, i, lines);
				अगर (rc)
					जाओ ilt_shaकरोw_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

ilt_shaकरोw_fail:
	qed_ilt_shaकरोw_मुक्त(p_hwfn);
	वापस rc;
पूर्ण

अटल व्योम qed_cid_map_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 type, vf;

	क्रम (type = 0; type < MAX_CONN_TYPES; type++) अणु
		kमुक्त(p_mngr->acquired[type].cid_map);
		p_mngr->acquired[type].max_count = 0;
		p_mngr->acquired[type].start_cid = 0;

		क्रम (vf = 0; vf < MAX_NUM_VFS; vf++) अणु
			kमुक्त(p_mngr->acquired_vf[type][vf].cid_map);
			p_mngr->acquired_vf[type][vf].max_count = 0;
			p_mngr->acquired_vf[type][vf].start_cid = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
qed_cid_map_alloc_single(काष्ठा qed_hwfn *p_hwfn,
			 u32 type,
			 u32 cid_start,
			 u32 cid_count, काष्ठा qed_cid_acquired_map *p_map)
अणु
	u32 size;

	अगर (!cid_count)
		वापस 0;

	size = DIV_ROUND_UP(cid_count,
			    माप(अचिन्हित दीर्घ) * BITS_PER_BYTE) *
	       माप(अचिन्हित दीर्घ);
	p_map->cid_map = kzalloc(size, GFP_KERNEL);
	अगर (!p_map->cid_map)
		वापस -ENOMEM;

	p_map->max_count = cid_count;
	p_map->start_cid = cid_start;

	DP_VERBOSE(p_hwfn, QED_MSG_CXT,
		   "Type %08x start: %08x count %08x\n",
		   type, p_map->start_cid, p_map->max_count);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_cid_map_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 start_cid = 0, vf_start_cid = 0;
	u32 type, vf;

	क्रम (type = 0; type < MAX_CONN_TYPES; type++) अणु
		काष्ठा qed_conn_type_cfg *p_cfg = &p_mngr->conn_cfg[type];
		काष्ठा qed_cid_acquired_map *p_map;

		/* Handle PF maps */
		p_map = &p_mngr->acquired[type];
		अगर (qed_cid_map_alloc_single(p_hwfn, type, start_cid,
					     p_cfg->cid_count, p_map))
			जाओ cid_map_fail;

		/* Handle VF maps */
		क्रम (vf = 0; vf < MAX_NUM_VFS; vf++) अणु
			p_map = &p_mngr->acquired_vf[type][vf];
			अगर (qed_cid_map_alloc_single(p_hwfn, type,
						     vf_start_cid,
						     p_cfg->cids_per_vf, p_map))
				जाओ cid_map_fail;
		पूर्ण

		start_cid += p_cfg->cid_count;
		vf_start_cid += p_cfg->cids_per_vf;
	पूर्ण

	वापस 0;

cid_map_fail:
	qed_cid_map_मुक्त(p_hwfn);
	वापस -ENOMEM;
पूर्ण

पूर्णांक qed_cxt_mngr_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *clients;
	काष्ठा qed_cxt_mngr *p_mngr;
	u32 i;

	p_mngr = kzalloc(माप(*p_mngr), GFP_KERNEL);
	अगर (!p_mngr)
		वापस -ENOMEM;

	/* Initialize ILT client रेजिस्टरs */
	clients = p_mngr->clients;
	clients[ILT_CLI_CDUC].first.reg = ILT_CFG_REG(CDUC, FIRST_ILT);
	clients[ILT_CLI_CDUC].last.reg = ILT_CFG_REG(CDUC, LAST_ILT);
	clients[ILT_CLI_CDUC].p_size.reg = ILT_CFG_REG(CDUC, P_SIZE);

	clients[ILT_CLI_QM].first.reg = ILT_CFG_REG(QM, FIRST_ILT);
	clients[ILT_CLI_QM].last.reg = ILT_CFG_REG(QM, LAST_ILT);
	clients[ILT_CLI_QM].p_size.reg = ILT_CFG_REG(QM, P_SIZE);

	clients[ILT_CLI_TM].first.reg = ILT_CFG_REG(TM, FIRST_ILT);
	clients[ILT_CLI_TM].last.reg = ILT_CFG_REG(TM, LAST_ILT);
	clients[ILT_CLI_TM].p_size.reg = ILT_CFG_REG(TM, P_SIZE);

	clients[ILT_CLI_SRC].first.reg = ILT_CFG_REG(SRC, FIRST_ILT);
	clients[ILT_CLI_SRC].last.reg = ILT_CFG_REG(SRC, LAST_ILT);
	clients[ILT_CLI_SRC].p_size.reg = ILT_CFG_REG(SRC, P_SIZE);

	clients[ILT_CLI_CDUT].first.reg = ILT_CFG_REG(CDUT, FIRST_ILT);
	clients[ILT_CLI_CDUT].last.reg = ILT_CFG_REG(CDUT, LAST_ILT);
	clients[ILT_CLI_CDUT].p_size.reg = ILT_CFG_REG(CDUT, P_SIZE);

	clients[ILT_CLI_TSDM].first.reg = ILT_CFG_REG(TSDM, FIRST_ILT);
	clients[ILT_CLI_TSDM].last.reg = ILT_CFG_REG(TSDM, LAST_ILT);
	clients[ILT_CLI_TSDM].p_size.reg = ILT_CFG_REG(TSDM, P_SIZE);
	/* शेष ILT page size क्रम all clients is 64K */
	क्रम (i = 0; i < MAX_ILT_CLIENTS; i++)
		p_mngr->clients[i].p_size.val = ILT_DEFAULT_HW_P_SIZE;

	p_mngr->conn_ctx_size = CONN_CXT_SIZE(p_hwfn);

	/* Initialize task sizes */
	p_mngr->task_type_size[0] = TYPE0_TASK_CXT_SIZE(p_hwfn);
	p_mngr->task_type_size[1] = TYPE1_TASK_CXT_SIZE(p_hwfn);

	अगर (p_hwfn->cdev->p_iov_info) अणु
		p_mngr->vf_count = p_hwfn->cdev->p_iov_info->total_vfs;
		p_mngr->first_vf_in_pf =
			p_hwfn->cdev->p_iov_info->first_vf_in_pf;
	पूर्ण
	/* Initialize the dynamic ILT allocation mutex */
	mutex_init(&p_mngr->mutex);

	/* Set the cxt mangr poपूर्णांकer priori to further allocations */
	p_hwfn->p_cxt_mngr = p_mngr;

	वापस 0;
पूर्ण

पूर्णांक qed_cxt_tables_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक rc;

	/* Allocate the ILT shaकरोw table */
	rc = qed_ilt_shaकरोw_alloc(p_hwfn);
	अगर (rc)
		जाओ tables_alloc_fail;

	/* Allocate the T2  table */
	rc = qed_cxt_src_t2_alloc(p_hwfn);
	अगर (rc)
		जाओ tables_alloc_fail;

	/* Allocate and initialize the acquired cids biपंचांगaps */
	rc = qed_cid_map_alloc(p_hwfn);
	अगर (rc)
		जाओ tables_alloc_fail;

	वापस 0;

tables_alloc_fail:
	qed_cxt_mngr_मुक्त(p_hwfn);
	वापस rc;
पूर्ण

व्योम qed_cxt_mngr_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn->p_cxt_mngr)
		वापस;

	qed_cid_map_मुक्त(p_hwfn);
	qed_cxt_src_t2_मुक्त(p_hwfn);
	qed_ilt_shaकरोw_मुक्त(p_hwfn);
	kमुक्त(p_hwfn->p_cxt_mngr);

	p_hwfn->p_cxt_mngr = शून्य;
पूर्ण

व्योम qed_cxt_mngr_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_cid_acquired_map *p_map;
	काष्ठा qed_conn_type_cfg *p_cfg;
	पूर्णांक type;
	u32 len;

	/* Reset acquired cids */
	क्रम (type = 0; type < MAX_CONN_TYPES; type++) अणु
		u32 vf;

		p_cfg = &p_mngr->conn_cfg[type];
		अगर (p_cfg->cid_count) अणु
			p_map = &p_mngr->acquired[type];
			len = DIV_ROUND_UP(p_map->max_count,
					   माप(अचिन्हित दीर्घ) *
					   BITS_PER_BYTE) *
			      माप(अचिन्हित दीर्घ);
			स_रखो(p_map->cid_map, 0, len);
		पूर्ण

		अगर (!p_cfg->cids_per_vf)
			जारी;

		क्रम (vf = 0; vf < MAX_NUM_VFS; vf++) अणु
			p_map = &p_mngr->acquired_vf[type][vf];
			len = DIV_ROUND_UP(p_map->max_count,
					   माप(अचिन्हित दीर्घ) *
					   BITS_PER_BYTE) *
			      माप(अचिन्हित दीर्घ);
			स_रखो(p_map->cid_map, 0, len);
		पूर्ण
	पूर्ण
पूर्ण

/* CDU Common */
#घोषणा CDUC_CXT_SIZE_SHIFT \
	CDU_REG_CID_ADDR_PARAMS_CONTEXT_SIZE_SHIFT

#घोषणा CDUC_CXT_SIZE_MASK \
	(CDU_REG_CID_ADDR_PARAMS_CONTEXT_SIZE >> CDUC_CXT_SIZE_SHIFT)

#घोषणा CDUC_BLOCK_WASTE_SHIFT \
	CDU_REG_CID_ADDR_PARAMS_BLOCK_WASTE_SHIFT

#घोषणा CDUC_BLOCK_WASTE_MASK \
	(CDU_REG_CID_ADDR_PARAMS_BLOCK_WASTE >> CDUC_BLOCK_WASTE_SHIFT)

#घोषणा CDUC_NCIB_SHIFT	\
	CDU_REG_CID_ADDR_PARAMS_NCIB_SHIFT

#घोषणा CDUC_NCIB_MASK \
	(CDU_REG_CID_ADDR_PARAMS_NCIB >> CDUC_NCIB_SHIFT)

#घोषणा CDUT_TYPE0_CXT_SIZE_SHIFT \
	CDU_REG_SEGMENT0_PARAMS_T0_TID_SIZE_SHIFT

#घोषणा CDUT_TYPE0_CXT_SIZE_MASK		\
	(CDU_REG_SEGMENT0_PARAMS_T0_TID_SIZE >>	\
	 CDUT_TYPE0_CXT_SIZE_SHIFT)

#घोषणा CDUT_TYPE0_BLOCK_WASTE_SHIFT \
	CDU_REG_SEGMENT0_PARAMS_T0_TID_BLOCK_WASTE_SHIFT

#घोषणा CDUT_TYPE0_BLOCK_WASTE_MASK		       \
	(CDU_REG_SEGMENT0_PARAMS_T0_TID_BLOCK_WASTE >> \
	 CDUT_TYPE0_BLOCK_WASTE_SHIFT)

#घोषणा CDUT_TYPE0_NCIB_SHIFT \
	CDU_REG_SEGMENT0_PARAMS_T0_NUM_TIDS_IN_BLOCK_SHIFT

#घोषणा CDUT_TYPE0_NCIB_MASK				 \
	(CDU_REG_SEGMENT0_PARAMS_T0_NUM_TIDS_IN_BLOCK >> \
	 CDUT_TYPE0_NCIB_SHIFT)

#घोषणा CDUT_TYPE1_CXT_SIZE_SHIFT \
	CDU_REG_SEGMENT1_PARAMS_T1_TID_SIZE_SHIFT

#घोषणा CDUT_TYPE1_CXT_SIZE_MASK		\
	(CDU_REG_SEGMENT1_PARAMS_T1_TID_SIZE >>	\
	 CDUT_TYPE1_CXT_SIZE_SHIFT)

#घोषणा CDUT_TYPE1_BLOCK_WASTE_SHIFT \
	CDU_REG_SEGMENT1_PARAMS_T1_TID_BLOCK_WASTE_SHIFT

#घोषणा CDUT_TYPE1_BLOCK_WASTE_MASK		       \
	(CDU_REG_SEGMENT1_PARAMS_T1_TID_BLOCK_WASTE >> \
	 CDUT_TYPE1_BLOCK_WASTE_SHIFT)

#घोषणा CDUT_TYPE1_NCIB_SHIFT \
	CDU_REG_SEGMENT1_PARAMS_T1_NUM_TIDS_IN_BLOCK_SHIFT

#घोषणा CDUT_TYPE1_NCIB_MASK				 \
	(CDU_REG_SEGMENT1_PARAMS_T1_NUM_TIDS_IN_BLOCK >> \
	 CDUT_TYPE1_NCIB_SHIFT)

अटल व्योम qed_cdu_init_common(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 page_sz, elems_per_page, block_waste, cxt_size, cdu_params = 0;

	/* CDUC - connection configuration */
	page_sz = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC].p_size.val;
	cxt_size = CONN_CXT_SIZE(p_hwfn);
	elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
	block_waste = ILT_PAGE_IN_BYTES(page_sz) - elems_per_page * cxt_size;

	SET_FIELD(cdu_params, CDUC_CXT_SIZE, cxt_size);
	SET_FIELD(cdu_params, CDUC_BLOCK_WASTE, block_waste);
	SET_FIELD(cdu_params, CDUC_NCIB, elems_per_page);
	STORE_RT_REG(p_hwfn, CDU_REG_CID_ADDR_PARAMS_RT_OFFSET, cdu_params);

	/* CDUT - type-0 tasks configuration */
	page_sz = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT].p_size.val;
	cxt_size = p_hwfn->p_cxt_mngr->task_type_size[0];
	elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
	block_waste = ILT_PAGE_IN_BYTES(page_sz) - elems_per_page * cxt_size;

	/* cxt size and block-waste are multipes of 8 */
	cdu_params = 0;
	SET_FIELD(cdu_params, CDUT_TYPE0_CXT_SIZE, (cxt_size >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE0_BLOCK_WASTE, (block_waste >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE0_NCIB, elems_per_page);
	STORE_RT_REG(p_hwfn, CDU_REG_SEGMENT0_PARAMS_RT_OFFSET, cdu_params);

	/* CDUT - type-1 tasks configuration */
	cxt_size = p_hwfn->p_cxt_mngr->task_type_size[1];
	elems_per_page = ILT_PAGE_IN_BYTES(page_sz) / cxt_size;
	block_waste = ILT_PAGE_IN_BYTES(page_sz) - elems_per_page * cxt_size;

	/* cxt size and block-waste are multipes of 8 */
	cdu_params = 0;
	SET_FIELD(cdu_params, CDUT_TYPE1_CXT_SIZE, (cxt_size >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE1_BLOCK_WASTE, (block_waste >> 3));
	SET_FIELD(cdu_params, CDUT_TYPE1_NCIB, elems_per_page);
	STORE_RT_REG(p_hwfn, CDU_REG_SEGMENT1_PARAMS_RT_OFFSET, cdu_params);
पूर्ण

/* CDU PF */
#घोषणा CDU_SEG_REG_TYPE_SHIFT          CDU_SEG_TYPE_OFFSET_REG_TYPE_SHIFT
#घोषणा CDU_SEG_REG_TYPE_MASK           0x1
#घोषणा CDU_SEG_REG_OFFSET_SHIFT        0
#घोषणा CDU_SEG_REG_OFFSET_MASK         CDU_SEG_TYPE_OFFSET_REG_OFFSET_MASK

अटल व्योम qed_cdu_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_tid_seg *p_seg;
	u32 cdu_seg_params, offset;
	पूर्णांक i;

	अटल स्थिर u32 rt_type_offset_arr[] = अणु
		CDU_REG_PF_SEG0_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_SEG1_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_SEG2_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_SEG3_TYPE_OFFSET_RT_OFFSET
	पूर्ण;

	अटल स्थिर u32 rt_type_offset_fl_arr[] = अणु
		CDU_REG_PF_FL_SEG0_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_FL_SEG1_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_FL_SEG2_TYPE_OFFSET_RT_OFFSET,
		CDU_REG_PF_FL_SEG3_TYPE_OFFSET_RT_OFFSET
	पूर्ण;

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];

	/* There are initializations only क्रम CDUT during pf Phase */
	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		/* Segment 0 */
		p_seg = qed_cxt_tid_seg_info(p_hwfn, i);
		अगर (!p_seg)
			जारी;

		/* Note: start_line is alपढ़ोy adjusted क्रम the CDU
		 * segment रेजिस्टर granularity, so we just need to
		 * भागide. Adjusपंचांगent is implicit as we assume ILT
		 * Page size is larger than 32K!
		 */
		offset = (ILT_PAGE_IN_BYTES(p_cli->p_size.val) *
			  (p_cli->pf_blks[CDUT_SEG_BLK(i)].start_line -
			   p_cli->first.val)) / CDUT_SEG_ALIGNMET_IN_BYTES;

		cdu_seg_params = 0;
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_TYPE, p_seg->type);
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_OFFSET, offset);
		STORE_RT_REG(p_hwfn, rt_type_offset_arr[i], cdu_seg_params);

		offset = (ILT_PAGE_IN_BYTES(p_cli->p_size.val) *
			  (p_cli->pf_blks[CDUT_FL_SEG_BLK(i, PF)].start_line -
			   p_cli->first.val)) / CDUT_SEG_ALIGNMET_IN_BYTES;

		cdu_seg_params = 0;
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_TYPE, p_seg->type);
		SET_FIELD(cdu_seg_params, CDU_SEG_REG_OFFSET, offset);
		STORE_RT_REG(p_hwfn, rt_type_offset_fl_arr[i], cdu_seg_params);
	पूर्ण
पूर्ण

व्योम qed_qm_init_pf(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, bool is_pf_loading)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	काष्ठा qed_qm_pf_rt_init_params params;
	काष्ठा qed_qm_iids iids;

	स_रखो(&iids, 0, माप(iids));
	qed_cxt_qm_iids(p_hwfn, &iids);

	स_रखो(&params, 0, माप(params));
	params.port_id = p_hwfn->port_id;
	params.pf_id = p_hwfn->rel_pf_id;
	params.max_phys_tcs_per_port = qm_info->max_phys_tcs_per_port;
	params.is_pf_loading = is_pf_loading;
	params.num_pf_cids = iids.cids;
	params.num_vf_cids = iids.vf_cids;
	params.num_tids = iids.tids;
	params.start_pq = qm_info->start_pq;
	params.num_pf_pqs = qm_info->num_pqs - qm_info->num_vf_pqs;
	params.num_vf_pqs = qm_info->num_vf_pqs;
	params.start_vport = qm_info->start_vport;
	params.num_vports = qm_info->num_vports;
	params.pf_wfq = qm_info->pf_wfq;
	params.pf_rl = qm_info->pf_rl;
	params.pq_params = qm_info->qm_pq_params;
	params.vport_params = qm_info->qm_vport_params;

	qed_qm_pf_rt_init(p_hwfn, p_ptt, &params);
पूर्ण

/* CM PF */
अटल व्योम qed_cm_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* XCM pure-LB queue */
	STORE_RT_REG(p_hwfn, XCM_REG_CON_PHY_Q3_RT_OFFSET,
		     qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LB));
पूर्ण

/* DQ PF */
अटल व्योम qed_dq_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 dq_pf_max_cid = 0, dq_vf_max_cid = 0;

	dq_pf_max_cid += (p_mngr->conn_cfg[0].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_0_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[0].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_0_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[1].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_1_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[1].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_1_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[2].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_2_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[2].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_2_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[3].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_3_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[3].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_3_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[4].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_4_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[4].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_4_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[5].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_5_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[5].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_5_RT_OFFSET, dq_vf_max_cid);

	/* Connection types 6 & 7 are not in use, yet they must be configured
	 * as the highest possible connection. Not configuring them means the
	 * शेषs will be  used, and with a large number of cids a bug may
	 * occur, अगर the शेषs will be smaller than dq_pf_max_cid /
	 * dq_vf_max_cid.
	 */
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_6_RT_OFFSET, dq_pf_max_cid);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_6_RT_OFFSET, dq_vf_max_cid);

	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_7_RT_OFFSET, dq_pf_max_cid);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_7_RT_OFFSET, dq_vf_max_cid);
पूर्ण

अटल व्योम qed_ilt_bounds_init(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *ilt_clients;
	पूर्णांक i;

	ilt_clients = p_hwfn->p_cxt_mngr->clients;
	क्रम_each_ilt_valid_client(i, ilt_clients) अणु
		STORE_RT_REG(p_hwfn,
			     ilt_clients[i].first.reg,
			     ilt_clients[i].first.val);
		STORE_RT_REG(p_hwfn,
			     ilt_clients[i].last.reg, ilt_clients[i].last.val);
		STORE_RT_REG(p_hwfn,
			     ilt_clients[i].p_size.reg,
			     ilt_clients[i].p_size.val);
	पूर्ण
पूर्ण

अटल व्योम qed_ilt_vf_bounds_init(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	u32 blk_factor;

	/* For simplicty  we set the 'block' to be an ILT page */
	अगर (p_hwfn->cdev->p_iov_info) अणु
		काष्ठा qed_hw_sriov_info *p_iov = p_hwfn->cdev->p_iov_info;

		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_VF_BASE_RT_OFFSET,
			     p_iov->first_vf_in_pf);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_VF_LAST_ILT_RT_OFFSET,
			     p_iov->first_vf_in_pf + p_iov->total_vfs);
	पूर्ण

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];
	blk_factor = ilog2(ILT_PAGE_IN_BYTES(p_cli->p_size.val) >> 10);
	अगर (p_cli->active) अणु
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_CDUC_BLOCKS_FACTOR_RT_OFFSET,
			     blk_factor);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_CDUC_NUMBER_OF_PF_BLOCKS_RT_OFFSET,
			     p_cli->pf_total_lines);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_CDUC_VF_BLOCKS_RT_OFFSET,
			     p_cli->vf_total_lines);
	पूर्ण

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
	blk_factor = ilog2(ILT_PAGE_IN_BYTES(p_cli->p_size.val) >> 10);
	अगर (p_cli->active) अणु
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_CDUT_BLOCKS_FACTOR_RT_OFFSET,
			     blk_factor);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_CDUT_NUMBER_OF_PF_BLOCKS_RT_OFFSET,
			     p_cli->pf_total_lines);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_CDUT_VF_BLOCKS_RT_OFFSET,
			     p_cli->vf_total_lines);
	पूर्ण

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TM];
	blk_factor = ilog2(ILT_PAGE_IN_BYTES(p_cli->p_size.val) >> 10);
	अगर (p_cli->active) अणु
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_TM_BLOCKS_FACTOR_RT_OFFSET, blk_factor);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_TM_NUMBER_OF_PF_BLOCKS_RT_OFFSET,
			     p_cli->pf_total_lines);
		STORE_RT_REG(p_hwfn,
			     PSWRQ2_REG_TM_VF_BLOCKS_RT_OFFSET,
			     p_cli->vf_total_lines);
	पूर्ण
पूर्ण

/* ILT (PSWRQ2) PF */
अटल व्योम qed_ilt_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *clients;
	काष्ठा qed_cxt_mngr *p_mngr;
	काष्ठा phys_mem_desc *p_shdw;
	u32 line, rt_offst, i;

	qed_ilt_bounds_init(p_hwfn);
	qed_ilt_vf_bounds_init(p_hwfn);

	p_mngr = p_hwfn->p_cxt_mngr;
	p_shdw = p_mngr->ilt_shaकरोw;
	clients = p_hwfn->p_cxt_mngr->clients;

	क्रम_each_ilt_valid_client(i, clients) अणु
		/** Client's 1st val and RT array are absolute, ILT shadows'
		 *  lines are relative.
		 */
		line = clients[i].first.val - p_mngr->pf_start_line;
		rt_offst = PSWRQ2_REG_ILT_MEMORY_RT_OFFSET +
			   clients[i].first.val * ILT_ENTRY_IN_REGS;

		क्रम (; line <= clients[i].last.val - p_mngr->pf_start_line;
		     line++, rt_offst += ILT_ENTRY_IN_REGS) अणु
			u64 ilt_hw_entry = 0;

			/** p_virt could be शून्य inहाल of dynamic
			 *  allocation
			 */
			अगर (p_shdw[line].virt_addr) अणु
				SET_FIELD(ilt_hw_entry, ILT_ENTRY_VALID, 1ULL);
				SET_FIELD(ilt_hw_entry, ILT_ENTRY_PHY_ADDR,
					  (p_shdw[line].phys_addr >> 12));

				DP_VERBOSE(p_hwfn, QED_MSG_ILT,
					   "Setting RT[0x%08x] from ILT[0x%08x] [Client is %d] to Physical addr: 0x%llx\n",
					   rt_offst, line, i,
					   (u64)(p_shdw[line].phys_addr >> 12));
			पूर्ण

			STORE_RT_REG_AGG(p_hwfn, rt_offst, ilt_hw_entry);
		पूर्ण
	पूर्ण
पूर्ण

/* SRC (Searcher) PF */
अटल व्योम qed_src_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 rounded_conn_num, conn_num, conn_max;
	काष्ठा qed_src_iids src_iids;

	स_रखो(&src_iids, 0, माप(src_iids));
	qed_cxt_src_iids(p_mngr, &src_iids);
	conn_num = src_iids.pf_cids + src_iids.per_vf_cids * p_mngr->vf_count;
	अगर (!conn_num)
		वापस;

	conn_max = max_t(u32, conn_num, SRC_MIN_NUM_ELEMS);
	rounded_conn_num = roundup_घात_of_two(conn_max);

	STORE_RT_REG(p_hwfn, SRC_REG_COUNTFREE_RT_OFFSET, conn_num);
	STORE_RT_REG(p_hwfn, SRC_REG_NUMBER_HASH_BITS_RT_OFFSET,
		     ilog2(rounded_conn_num));

	STORE_RT_REG_AGG(p_hwfn, SRC_REG_FIRSTFREE_RT_OFFSET,
			 p_hwfn->p_cxt_mngr->src_t2.first_मुक्त);
	STORE_RT_REG_AGG(p_hwfn, SRC_REG_LASTFREE_RT_OFFSET,
			 p_hwfn->p_cxt_mngr->src_t2.last_मुक्त);
पूर्ण

/* Timers PF */
#घोषणा TM_CFG_NUM_IDS_SHIFT            0
#घोषणा TM_CFG_NUM_IDS_MASK             0xFFFFULL
#घोषणा TM_CFG_PRE_SCAN_OFFSET_SHIFT    16
#घोषणा TM_CFG_PRE_SCAN_OFFSET_MASK     0x1FFULL
#घोषणा TM_CFG_PARENT_PF_SHIFT          25
#घोषणा TM_CFG_PARENT_PF_MASK           0x7ULL

#घोषणा TM_CFG_CID_PRE_SCAN_ROWS_SHIFT  30
#घोषणा TM_CFG_CID_PRE_SCAN_ROWS_MASK   0x1FFULL

#घोषणा TM_CFG_TID_OFFSET_SHIFT         30
#घोषणा TM_CFG_TID_OFFSET_MASK          0x7FFFFULL
#घोषणा TM_CFG_TID_PRE_SCAN_ROWS_SHIFT  49
#घोषणा TM_CFG_TID_PRE_SCAN_ROWS_MASK   0x1FFULL

अटल व्योम qed_पंचांग_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 active_seg_mask = 0, पंचांग_offset, rt_reg;
	काष्ठा qed_पंचांग_iids पंचांग_iids;
	u64 cfg_word;
	u8 i;

	स_रखो(&पंचांग_iids, 0, माप(पंचांग_iids));
	qed_cxt_पंचांग_iids(p_hwfn, p_mngr, &पंचांग_iids);

	/* @@@TBD No pre-scan क्रम now */

	/* Note: We assume consecutive VFs क्रम a PF */
	क्रम (i = 0; i < p_mngr->vf_count; i++) अणु
		cfg_word = 0;
		SET_FIELD(cfg_word, TM_CFG_NUM_IDS, पंचांग_iids.per_vf_cids);
		SET_FIELD(cfg_word, TM_CFG_PRE_SCAN_OFFSET, 0);
		SET_FIELD(cfg_word, TM_CFG_PARENT_PF, p_hwfn->rel_pf_id);
		SET_FIELD(cfg_word, TM_CFG_CID_PRE_SCAN_ROWS, 0);
		rt_reg = TM_REG_CONFIG_CONN_MEM_RT_OFFSET +
		    (माप(cfg_word) / माप(u32)) *
		    (p_hwfn->cdev->p_iov_info->first_vf_in_pf + i);
		STORE_RT_REG_AGG(p_hwfn, rt_reg, cfg_word);
	पूर्ण

	cfg_word = 0;
	SET_FIELD(cfg_word, TM_CFG_NUM_IDS, पंचांग_iids.pf_cids);
	SET_FIELD(cfg_word, TM_CFG_PRE_SCAN_OFFSET, 0);
	SET_FIELD(cfg_word, TM_CFG_PARENT_PF, 0);	/* n/a क्रम PF */
	SET_FIELD(cfg_word, TM_CFG_CID_PRE_SCAN_ROWS, 0);	/* scan all   */

	rt_reg = TM_REG_CONFIG_CONN_MEM_RT_OFFSET +
	    (माप(cfg_word) / माप(u32)) *
	    (NUM_OF_VFS(p_hwfn->cdev) + p_hwfn->rel_pf_id);
	STORE_RT_REG_AGG(p_hwfn, rt_reg, cfg_word);

	/* enale scan */
	STORE_RT_REG(p_hwfn, TM_REG_PF_ENABLE_CONN_RT_OFFSET,
		     पंचांग_iids.pf_cids ? 0x1 : 0x0);

	/* @@@TBD how to enable the scan क्रम the VFs */

	पंचांग_offset = पंचांग_iids.per_vf_cids;

	/* Note: We assume consecutive VFs क्रम a PF */
	क्रम (i = 0; i < p_mngr->vf_count; i++) अणु
		cfg_word = 0;
		SET_FIELD(cfg_word, TM_CFG_NUM_IDS, पंचांग_iids.per_vf_tids);
		SET_FIELD(cfg_word, TM_CFG_PRE_SCAN_OFFSET, 0);
		SET_FIELD(cfg_word, TM_CFG_PARENT_PF, p_hwfn->rel_pf_id);
		SET_FIELD(cfg_word, TM_CFG_TID_OFFSET, पंचांग_offset);
		SET_FIELD(cfg_word, TM_CFG_TID_PRE_SCAN_ROWS, (u64) 0);

		rt_reg = TM_REG_CONFIG_TASK_MEM_RT_OFFSET +
		    (माप(cfg_word) / माप(u32)) *
		    (p_hwfn->cdev->p_iov_info->first_vf_in_pf + i);

		STORE_RT_REG_AGG(p_hwfn, rt_reg, cfg_word);
	पूर्ण

	पंचांग_offset = पंचांग_iids.pf_cids;
	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		cfg_word = 0;
		SET_FIELD(cfg_word, TM_CFG_NUM_IDS, पंचांग_iids.pf_tids[i]);
		SET_FIELD(cfg_word, TM_CFG_PRE_SCAN_OFFSET, 0);
		SET_FIELD(cfg_word, TM_CFG_PARENT_PF, 0);
		SET_FIELD(cfg_word, TM_CFG_TID_OFFSET, पंचांग_offset);
		SET_FIELD(cfg_word, TM_CFG_TID_PRE_SCAN_ROWS, (u64) 0);

		rt_reg = TM_REG_CONFIG_TASK_MEM_RT_OFFSET +
		    (माप(cfg_word) / माप(u32)) *
		    (NUM_OF_VFS(p_hwfn->cdev) +
		     p_hwfn->rel_pf_id * NUM_TASK_PF_SEGMENTS + i);

		STORE_RT_REG_AGG(p_hwfn, rt_reg, cfg_word);
		active_seg_mask |= (पंचांग_iids.pf_tids[i] ? BIT(i) : 0);

		पंचांग_offset += पंचांग_iids.pf_tids[i];
	पूर्ण

	अगर (QED_IS_RDMA_PERSONALITY(p_hwfn))
		active_seg_mask = 0;

	STORE_RT_REG(p_hwfn, TM_REG_PF_ENABLE_TASK_RT_OFFSET, active_seg_mask);

	/* @@@TBD how to enable the scan क्रम the VFs */
पूर्ण

अटल व्योम qed_prs_init_common(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर ((p_hwfn->hw_info.personality == QED_PCI_FCOE) &&
	    p_hwfn->pf_params.fcoe_pf_params.is_target)
		STORE_RT_REG(p_hwfn,
			     PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET, 0);
पूर्ण

अटल व्योम qed_prs_init_pf(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_conn_type_cfg *p_fcoe;
	काष्ठा qed_tid_seg *p_tid;

	p_fcoe = &p_mngr->conn_cfg[PROTOCOLID_FCOE];

	/* If FCoE is active set the MAX OX_ID (tid) in the Parser */
	अगर (!p_fcoe->cid_count)
		वापस;

	p_tid = &p_fcoe->tid_seg[QED_CXT_FCOE_TID_SEG];
	अगर (p_hwfn->pf_params.fcoe_pf_params.is_target) अणु
		STORE_RT_REG_AGG(p_hwfn,
				 PRS_REG_TASK_ID_MAX_TARGET_PF_RT_OFFSET,
				 p_tid->count);
	पूर्ण अन्यथा अणु
		STORE_RT_REG_AGG(p_hwfn,
				 PRS_REG_TASK_ID_MAX_INITIATOR_PF_RT_OFFSET,
				 p_tid->count);
	पूर्ण
पूर्ण

व्योम qed_cxt_hw_init_common(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_cdu_init_common(p_hwfn);
	qed_prs_init_common(p_hwfn);
पूर्ण

व्योम qed_cxt_hw_init_pf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	qed_qm_init_pf(p_hwfn, p_ptt, true);
	qed_cm_init_pf(p_hwfn);
	qed_dq_init_pf(p_hwfn);
	qed_cdu_init_pf(p_hwfn);
	qed_ilt_init_pf(p_hwfn);
	qed_src_init_pf(p_hwfn);
	qed_पंचांग_init_pf(p_hwfn);
	qed_prs_init_pf(p_hwfn);
पूर्ण

पूर्णांक _qed_cxt_acquire_cid(काष्ठा qed_hwfn *p_hwfn,
			 क्रमागत protocol_type type, u32 *p_cid, u8 vfid)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_cid_acquired_map *p_map;
	u32 rel_cid;

	अगर (type >= MAX_CONN_TYPES) अणु
		DP_NOTICE(p_hwfn, "Invalid protocol type %d", type);
		वापस -EINVAL;
	पूर्ण

	अगर (vfid >= MAX_NUM_VFS && vfid != QED_CXT_PF_CID) अणु
		DP_NOTICE(p_hwfn, "VF [%02x] is out of range\n", vfid);
		वापस -EINVAL;
	पूर्ण

	/* Determine the right map to take this CID from */
	अगर (vfid == QED_CXT_PF_CID)
		p_map = &p_mngr->acquired[type];
	अन्यथा
		p_map = &p_mngr->acquired_vf[type][vfid];

	अगर (!p_map->cid_map) अणु
		DP_NOTICE(p_hwfn, "Invalid protocol type %d", type);
		वापस -EINVAL;
	पूर्ण

	rel_cid = find_first_zero_bit(p_map->cid_map, p_map->max_count);

	अगर (rel_cid >= p_map->max_count) अणु
		DP_NOTICE(p_hwfn, "no CID available for protocol %d\n", type);
		वापस -EINVAL;
	पूर्ण

	__set_bit(rel_cid, p_map->cid_map);

	*p_cid = rel_cid + p_map->start_cid;

	DP_VERBOSE(p_hwfn, QED_MSG_CXT,
		   "Acquired cid 0x%08x [rel. %08x] vfid %02x type %d\n",
		   *p_cid, rel_cid, vfid, type);

	वापस 0;
पूर्ण

पूर्णांक qed_cxt_acquire_cid(काष्ठा qed_hwfn *p_hwfn,
			क्रमागत protocol_type type, u32 *p_cid)
अणु
	वापस _qed_cxt_acquire_cid(p_hwfn, type, p_cid, QED_CXT_PF_CID);
पूर्ण

अटल bool qed_cxt_test_cid_acquired(काष्ठा qed_hwfn *p_hwfn,
				      u32 cid,
				      u8 vfid,
				      क्रमागत protocol_type *p_type,
				      काष्ठा qed_cid_acquired_map **pp_map)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 rel_cid;

	/* Iterate over protocols and find matching cid range */
	क्रम (*p_type = 0; *p_type < MAX_CONN_TYPES; (*p_type)++) अणु
		अगर (vfid == QED_CXT_PF_CID)
			*pp_map = &p_mngr->acquired[*p_type];
		अन्यथा
			*pp_map = &p_mngr->acquired_vf[*p_type][vfid];

		अगर (!((*pp_map)->cid_map))
			जारी;
		अगर (cid >= (*pp_map)->start_cid &&
		    cid < (*pp_map)->start_cid + (*pp_map)->max_count)
			अवरोध;
	पूर्ण

	अगर (*p_type == MAX_CONN_TYPES) अणु
		DP_NOTICE(p_hwfn, "Invalid CID %d vfid %02x", cid, vfid);
		जाओ fail;
	पूर्ण

	rel_cid = cid - (*pp_map)->start_cid;
	अगर (!test_bit(rel_cid, (*pp_map)->cid_map)) अणु
		DP_NOTICE(p_hwfn, "CID %d [vifd %02x] not acquired",
			  cid, vfid);
		जाओ fail;
	पूर्ण

	वापस true;
fail:
	*p_type = MAX_CONN_TYPES;
	*pp_map = शून्य;
	वापस false;
पूर्ण

व्योम _qed_cxt_release_cid(काष्ठा qed_hwfn *p_hwfn, u32 cid, u8 vfid)
अणु
	काष्ठा qed_cid_acquired_map *p_map = शून्य;
	क्रमागत protocol_type type;
	bool b_acquired;
	u32 rel_cid;

	अगर (vfid != QED_CXT_PF_CID && vfid > MAX_NUM_VFS) अणु
		DP_NOTICE(p_hwfn,
			  "Trying to return incorrect CID belonging to VF %02x\n",
			  vfid);
		वापस;
	पूर्ण

	/* Test acquired and find matching per-protocol map */
	b_acquired = qed_cxt_test_cid_acquired(p_hwfn, cid, vfid,
					       &type, &p_map);

	अगर (!b_acquired)
		वापस;

	rel_cid = cid - p_map->start_cid;
	clear_bit(rel_cid, p_map->cid_map);

	DP_VERBOSE(p_hwfn, QED_MSG_CXT,
		   "Released CID 0x%08x [rel. %08x] vfid %02x type %d\n",
		   cid, rel_cid, vfid, type);
पूर्ण

व्योम qed_cxt_release_cid(काष्ठा qed_hwfn *p_hwfn, u32 cid)
अणु
	_qed_cxt_release_cid(p_hwfn, cid, QED_CXT_PF_CID);
पूर्ण

पूर्णांक qed_cxt_get_cid_info(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_cxt_info *p_info)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_cid_acquired_map *p_map = शून्य;
	u32 conn_cxt_size, hw_p_size, cxts_per_p, line;
	क्रमागत protocol_type type;
	bool b_acquired;

	/* Test acquired and find matching per-protocol map */
	b_acquired = qed_cxt_test_cid_acquired(p_hwfn, p_info->iid,
					       QED_CXT_PF_CID, &type, &p_map);

	अगर (!b_acquired)
		वापस -EINVAL;

	/* set the protocl type */
	p_info->type = type;

	/* compute context भव poपूर्णांकer */
	hw_p_size = p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC].p_size.val;

	conn_cxt_size = CONN_CXT_SIZE(p_hwfn);
	cxts_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / conn_cxt_size;
	line = p_info->iid / cxts_per_p;

	/* Make sure context is allocated (dynamic allocation) */
	अगर (!p_mngr->ilt_shaकरोw[line].virt_addr)
		वापस -EINVAL;

	p_info->p_cxt = p_mngr->ilt_shaकरोw[line].virt_addr +
			p_info->iid % cxts_per_p * conn_cxt_size;

	DP_VERBOSE(p_hwfn, (QED_MSG_ILT | QED_MSG_CXT),
		   "Accessing ILT shadow[%d]: CXT pointer is at %p (for iid %d)\n",
		   p_info->iid / cxts_per_p, p_info->p_cxt, p_info->iid);

	वापस 0;
पूर्ण

अटल व्योम qed_rdma_set_pf_params(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_rdma_pf_params *p_params,
				   u32 num_tasks)
अणु
	u32 num_cons, num_qps;
	क्रमागत protocol_type proto;

	अगर (p_hwfn->mcp_info->func_info.protocol == QED_PCI_ETH_RDMA) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Current day drivers don't support RoCE & iWARP simultaneously on the same PF. Default to RoCE-only\n");
		p_hwfn->hw_info.personality = QED_PCI_ETH_ROCE;
	पूर्ण

	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_ETH_IWARP:
		/* Each QP requires one connection */
		num_cons = min_t(u32, IWARP_MAX_QPS, p_params->num_qps);
		proto = PROTOCOLID_IWARP;
		अवरोध;
	हाल QED_PCI_ETH_ROCE:
		num_qps = min_t(u32, ROCE_MAX_QPS, p_params->num_qps);
		num_cons = num_qps * 2;	/* each QP requires two connections */
		proto = PROTOCOLID_ROCE;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (num_cons && num_tasks) अणु
		u32 num_srqs, num_xrc_srqs;

		qed_cxt_set_proto_cid_count(p_hwfn, proto, num_cons, 0);

		/* Deliberatly passing ROCE क्रम tasks id. This is because
		 * iWARP / RoCE share the task id.
		 */
		qed_cxt_set_proto_tid_count(p_hwfn, PROTOCOLID_ROCE,
					    QED_CXT_ROCE_TID_SEG, 1,
					    num_tasks, false);

		num_srqs = min_t(u32, QED_RDMA_MAX_SRQS, p_params->num_srqs);

		/* XRC SRQs populate a single ILT page */
		num_xrc_srqs = qed_cxt_xrc_srqs_per_page(p_hwfn);

		qed_cxt_set_srq_count(p_hwfn, num_srqs, num_xrc_srqs);
	पूर्ण अन्यथा अणु
		DP_INFO(p_hwfn->cdev,
			"RDMA personality used without setting params!\n");
	पूर्ण
पूर्ण

पूर्णांक qed_cxt_set_pf_params(काष्ठा qed_hwfn *p_hwfn, u32 rdma_tasks)
अणु
	/* Set the number of required CORE connections */
	u32 core_cids = 1; /* SPQ */

	अगर (p_hwfn->using_ll2)
		core_cids += 4;
	qed_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_CORE, core_cids, 0);

	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_ETH_RDMA:
	हाल QED_PCI_ETH_IWARP:
	हाल QED_PCI_ETH_ROCE:
	अणु
			qed_rdma_set_pf_params(p_hwfn,
					       &p_hwfn->
					       pf_params.rdma_pf_params,
					       rdma_tasks);
		/* no need क्रम अवरोध since RoCE coexist with Ethernet */
	पूर्ण
		fallthrough;
	हाल QED_PCI_ETH:
	अणु
		काष्ठा qed_eth_pf_params *p_params =
		    &p_hwfn->pf_params.eth_pf_params;

		अगर (!p_params->num_vf_cons)
			p_params->num_vf_cons =
			    ETH_PF_PARAMS_VF_CONS_DEFAULT;
		qed_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_ETH,
					    p_params->num_cons,
					    p_params->num_vf_cons);
		p_hwfn->p_cxt_mngr->arfs_count = p_params->num_arfs_filters;
		अवरोध;
	पूर्ण
	हाल QED_PCI_FCOE:
	अणु
		काष्ठा qed_fcoe_pf_params *p_params;

		p_params = &p_hwfn->pf_params.fcoe_pf_params;

		अगर (p_params->num_cons && p_params->num_tasks) अणु
			qed_cxt_set_proto_cid_count(p_hwfn,
						    PROTOCOLID_FCOE,
						    p_params->num_cons,
						    0);

			qed_cxt_set_proto_tid_count(p_hwfn, PROTOCOLID_FCOE,
						    QED_CXT_FCOE_TID_SEG, 0,
						    p_params->num_tasks, true);
		पूर्ण अन्यथा अणु
			DP_INFO(p_hwfn->cdev,
				"Fcoe personality used without setting params!\n");
		पूर्ण
		अवरोध;
	पूर्ण
	हाल QED_PCI_ISCSI:
	अणु
		काष्ठा qed_iscsi_pf_params *p_params;

		p_params = &p_hwfn->pf_params.iscsi_pf_params;

		अगर (p_params->num_cons && p_params->num_tasks) अणु
			qed_cxt_set_proto_cid_count(p_hwfn,
						    PROTOCOLID_ISCSI,
						    p_params->num_cons,
						    0);

			qed_cxt_set_proto_tid_count(p_hwfn,
						    PROTOCOLID_ISCSI,
						    QED_CXT_ISCSI_TID_SEG,
						    0,
						    p_params->num_tasks,
						    true);
		पूर्ण अन्यथा अणु
			DP_INFO(p_hwfn->cdev,
				"Iscsi personality used without setting params!\n");
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_cxt_get_tid_mem_info(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_tid_mem *p_info)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 proto, seg, total_lines, i, shaकरोw_line;
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_fl_seg;
	काष्ठा qed_tid_seg *p_seg_info;

	/* Verअगरy the personality */
	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_FCOE:
		proto = PROTOCOLID_FCOE;
		seg = QED_CXT_FCOE_TID_SEG;
		अवरोध;
	हाल QED_PCI_ISCSI:
		proto = PROTOCOLID_ISCSI;
		seg = QED_CXT_ISCSI_TID_SEG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	p_cli = &p_mngr->clients[ILT_CLI_CDUT];
	अगर (!p_cli->active)
		वापस -EINVAL;

	p_seg_info = &p_mngr->conn_cfg[proto].tid_seg[seg];
	अगर (!p_seg_info->has_fl_mem)
		वापस -EINVAL;

	p_fl_seg = &p_cli->pf_blks[CDUT_FL_SEG_BLK(seg, PF)];
	total_lines = DIV_ROUND_UP(p_fl_seg->total_size,
				   p_fl_seg->real_size_in_page);

	क्रम (i = 0; i < total_lines; i++) अणु
		shaकरोw_line = i + p_fl_seg->start_line -
		    p_hwfn->p_cxt_mngr->pf_start_line;
		p_info->blocks[i] = p_mngr->ilt_shaकरोw[shaकरोw_line].virt_addr;
	पूर्ण
	p_info->waste = ILT_PAGE_IN_BYTES(p_cli->p_size.val) -
	    p_fl_seg->real_size_in_page;
	p_info->tid_size = p_mngr->task_type_size[p_seg_info->type];
	p_info->num_tids_per_block = p_fl_seg->real_size_in_page /
	    p_info->tid_size;

	वापस 0;
पूर्ण

/* This function is very RoCE oriented, अगर another protocol in the future
 * will want this feature we'll need to modअगरy the function to be more generic
 */
पूर्णांक
qed_cxt_dynamic_ilt_alloc(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत qed_cxt_elem_type elem_type, u32 iid)
अणु
	u32 reg_offset, shaकरोw_line, elem_size, hw_p_size, elems_per_p, line;
	काष्ठा tdअगर_task_context *tdअगर_context;
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	काष्ठा qed_ptt *p_ptt;
	dma_addr_t p_phys;
	u64 ilt_hw_entry;
	व्योम *p_virt;
	u32 flags1;
	पूर्णांक rc = 0;

	चयन (elem_type) अणु
	हाल QED_ELEM_CXT:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];
		elem_size = CONN_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUC_BLK];
		अवरोध;
	हाल QED_ELEM_SRQ:
		/* The first ILT page is not used क्रम regular SRQs. Skip it. */
		iid += p_hwfn->p_cxt_mngr->xrc_srq_count;
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		अवरोध;
	हाल QED_ELEM_XRC_SRQ:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = XRC_SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		अवरोध;
	हाल QED_ELEM_TASK:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
		elem_size = TYPE1_TASK_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUT_SEG_BLK(QED_CXT_ROCE_TID_SEG)];
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "-EINVALID elem type = %d", elem_type);
		वापस -EINVAL;
	पूर्ण

	/* Calculate line in ilt */
	hw_p_size = p_cli->p_size.val;
	elems_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / elem_size;
	line = p_blk->start_line + (iid / elems_per_p);
	shaकरोw_line = line - p_hwfn->p_cxt_mngr->pf_start_line;

	/* If line is alपढ़ोy allocated, करो nothing, otherwise allocate it and
	 * ग_लिखो it to the PSWRQ2 रेजिस्टरs.
	 * This section can be run in parallel from dअगरferent contexts and thus
	 * a mutex protection is needed.
	 */

	mutex_lock(&p_hwfn->p_cxt_mngr->mutex);

	अगर (p_hwfn->p_cxt_mngr->ilt_shaकरोw[shaकरोw_line].virt_addr)
		जाओ out0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_NOTICE(p_hwfn,
			  "QED_TIME_OUT on ptt acquire - dynamic allocation");
		rc = -EBUSY;
		जाओ out0;
	पूर्ण

	p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    p_blk->real_size_in_page, &p_phys,
				    GFP_KERNEL);
	अगर (!p_virt) अणु
		rc = -ENOMEM;
		जाओ out1;
	पूर्ण

	/* configuration of refTagMask to 0xF is required क्रम RoCE DIF MR only,
	 * to compensate क्रम a HW bug, but it is configured even अगर DIF is not
	 * enabled. This is harmless and allows us to aव्योम a dedicated API. We
	 * configure the field क्रम all of the contexts on the newly allocated
	 * page.
	 */
	अगर (elem_type == QED_ELEM_TASK) अणु
		u32 elem_i;
		u8 *elem_start = (u8 *)p_virt;
		जोड़ type1_task_context *elem;

		क्रम (elem_i = 0; elem_i < elems_per_p; elem_i++) अणु
			elem = (जोड़ type1_task_context *)elem_start;
			tdअगर_context = &elem->roce_ctx.tdअगर_context;

			flags1 = le32_to_cpu(tdअगर_context->flags1);
			SET_FIELD(flags1, TDIF_TASK_CONTEXT_REF_TAG_MASK, 0xf);
			tdअगर_context->flags1 = cpu_to_le32(flags1);

			elem_start += TYPE1_TASK_CXT_SIZE(p_hwfn);
		पूर्ण
	पूर्ण

	p_hwfn->p_cxt_mngr->ilt_shaकरोw[shaकरोw_line].virt_addr = p_virt;
	p_hwfn->p_cxt_mngr->ilt_shaकरोw[shaकरोw_line].phys_addr = p_phys;
	p_hwfn->p_cxt_mngr->ilt_shaकरोw[shaकरोw_line].size =
	    p_blk->real_size_in_page;

	/* compute असलolute offset */
	reg_offset = PSWRQ2_REG_ILT_MEMORY +
	    (line * ILT_REG_SIZE_IN_BYTES * ILT_ENTRY_IN_REGS);

	ilt_hw_entry = 0;
	SET_FIELD(ilt_hw_entry, ILT_ENTRY_VALID, 1ULL);
	SET_FIELD(ilt_hw_entry, ILT_ENTRY_PHY_ADDR,
		  (p_hwfn->p_cxt_mngr->ilt_shaकरोw[shaकरोw_line].phys_addr
		   >> 12));

	/* Write via DMAE since the PSWRQ2_REG_ILT_MEMORY line is a wide-bus */
	qed_dmae_host2grc(p_hwfn, p_ptt, (u64) (uपूर्णांकptr_t)&ilt_hw_entry,
			  reg_offset, माप(ilt_hw_entry) / माप(u32),
			  शून्य);

	अगर (elem_type == QED_ELEM_CXT) अणु
		u32 last_cid_allocated = (1 + (iid / elems_per_p)) *
		    elems_per_p;

		/* Update the relevant रेजिस्टर in the parser */
		qed_wr(p_hwfn, p_ptt, PRS_REG_ROCE_DEST_QP_MAX_PF,
		       last_cid_allocated - 1);

		अगर (!p_hwfn->b_rdma_enabled_in_prs) अणु
			/* Enable RDMA search */
			qed_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 1);
			p_hwfn->b_rdma_enabled_in_prs = true;
		पूर्ण
	पूर्ण

out1:
	qed_ptt_release(p_hwfn, p_ptt);
out0:
	mutex_unlock(&p_hwfn->p_cxt_mngr->mutex);

	वापस rc;
पूर्ण

/* This function is very RoCE oriented, अगर another protocol in the future
 * will want this feature we'll need to modअगरy the function to be more generic
 */
अटल पूर्णांक
qed_cxt_मुक्त_ilt_range(काष्ठा qed_hwfn *p_hwfn,
		       क्रमागत qed_cxt_elem_type elem_type,
		       u32 start_iid, u32 count)
अणु
	u32 start_line, end_line, shaकरोw_start_line, shaकरोw_end_line;
	u32 reg_offset, elem_size, hw_p_size, elems_per_p;
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	u32 end_iid = start_iid + count;
	काष्ठा qed_ptt *p_ptt;
	u64 ilt_hw_entry = 0;
	u32 i;

	चयन (elem_type) अणु
	हाल QED_ELEM_CXT:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];
		elem_size = CONN_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUC_BLK];
		अवरोध;
	हाल QED_ELEM_SRQ:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		अवरोध;
	हाल QED_ELEM_XRC_SRQ:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = XRC_SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		अवरोध;
	हाल QED_ELEM_TASK:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
		elem_size = TYPE1_TASK_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUT_SEG_BLK(QED_CXT_ROCE_TID_SEG)];
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "-EINVALID elem type = %d", elem_type);
		वापस -EINVAL;
	पूर्ण

	/* Calculate line in ilt */
	hw_p_size = p_cli->p_size.val;
	elems_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / elem_size;
	start_line = p_blk->start_line + (start_iid / elems_per_p);
	end_line = p_blk->start_line + (end_iid / elems_per_p);
	अगर (((end_iid + 1) / elems_per_p) != (end_iid / elems_per_p))
		end_line--;

	shaकरोw_start_line = start_line - p_hwfn->p_cxt_mngr->pf_start_line;
	shaकरोw_end_line = end_line - p_hwfn->p_cxt_mngr->pf_start_line;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_NOTICE(p_hwfn,
			  "QED_TIME_OUT on ptt acquire - dynamic allocation");
		वापस -EBUSY;
	पूर्ण

	क्रम (i = shaकरोw_start_line; i < shaकरोw_end_line; i++) अणु
		अगर (!p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].virt_addr)
			जारी;

		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].size,
				  p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].virt_addr,
				  p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].phys_addr);

		p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].virt_addr = शून्य;
		p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].phys_addr = 0;
		p_hwfn->p_cxt_mngr->ilt_shaकरोw[i].size = 0;

		/* compute असलolute offset */
		reg_offset = PSWRQ2_REG_ILT_MEMORY +
		    ((start_line++) * ILT_REG_SIZE_IN_BYTES *
		     ILT_ENTRY_IN_REGS);

		/* Write via DMAE since the PSWRQ2_REG_ILT_MEMORY line is a
		 * wide-bus.
		 */
		qed_dmae_host2grc(p_hwfn, p_ptt,
				  (u64) (uपूर्णांकptr_t) &ilt_hw_entry,
				  reg_offset,
				  माप(ilt_hw_entry) / माप(u32),
				  शून्य);
	पूर्ण

	qed_ptt_release(p_hwfn, p_ptt);

	वापस 0;
पूर्ण

पूर्णांक qed_cxt_मुक्त_proto_ilt(काष्ठा qed_hwfn *p_hwfn, क्रमागत protocol_type proto)
अणु
	पूर्णांक rc;
	u32 cid;

	/* Free Connection CXT */
	rc = qed_cxt_मुक्त_ilt_range(p_hwfn, QED_ELEM_CXT,
				    qed_cxt_get_proto_cid_start(p_hwfn,
								proto),
				    qed_cxt_get_proto_cid_count(p_hwfn,
								proto, &cid));

	अगर (rc)
		वापस rc;

	/* Free Task CXT ( Intentionally RoCE as task-id is shared between
	 * RoCE and iWARP )
	 */
	proto = PROTOCOLID_ROCE;
	rc = qed_cxt_मुक्त_ilt_range(p_hwfn, QED_ELEM_TASK, 0,
				    qed_cxt_get_proto_tid_count(p_hwfn, proto));
	अगर (rc)
		वापस rc;

	/* Free TSDM CXT */
	rc = qed_cxt_मुक्त_ilt_range(p_hwfn, QED_ELEM_XRC_SRQ, 0,
				    p_hwfn->p_cxt_mngr->xrc_srq_count);

	rc = qed_cxt_मुक्त_ilt_range(p_hwfn, QED_ELEM_SRQ,
				    p_hwfn->p_cxt_mngr->xrc_srq_count,
				    p_hwfn->p_cxt_mngr->srq_count);

	वापस rc;
पूर्ण

पूर्णांक qed_cxt_get_task_ctx(काष्ठा qed_hwfn *p_hwfn,
			 u32 tid, u8 ctx_type, व्योम **pp_task_ctx)
अणु
	काष्ठा qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_tid_seg *p_seg_info;
	काष्ठा qed_ilt_cli_blk *p_seg;
	u32 num_tids_per_block;
	u32 tid_size, ilt_idx;
	u32 total_lines;
	u32 proto, seg;

	/* Verअगरy the personality */
	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_FCOE:
		proto = PROTOCOLID_FCOE;
		seg = QED_CXT_FCOE_TID_SEG;
		अवरोध;
	हाल QED_PCI_ISCSI:
		proto = PROTOCOLID_ISCSI;
		seg = QED_CXT_ISCSI_TID_SEG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	p_cli = &p_mngr->clients[ILT_CLI_CDUT];
	अगर (!p_cli->active)
		वापस -EINVAL;

	p_seg_info = &p_mngr->conn_cfg[proto].tid_seg[seg];

	अगर (ctx_type == QED_CTX_WORKING_MEM) अणु
		p_seg = &p_cli->pf_blks[CDUT_SEG_BLK(seg)];
	पूर्ण अन्यथा अगर (ctx_type == QED_CTX_FL_MEM) अणु
		अगर (!p_seg_info->has_fl_mem)
			वापस -EINVAL;
		p_seg = &p_cli->pf_blks[CDUT_FL_SEG_BLK(seg, PF)];
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	total_lines = DIV_ROUND_UP(p_seg->total_size, p_seg->real_size_in_page);
	tid_size = p_mngr->task_type_size[p_seg_info->type];
	num_tids_per_block = p_seg->real_size_in_page / tid_size;

	अगर (total_lines < tid / num_tids_per_block)
		वापस -EINVAL;

	ilt_idx = tid / num_tids_per_block + p_seg->start_line -
		  p_mngr->pf_start_line;
	*pp_task_ctx = (u8 *)p_mngr->ilt_shaकरोw[ilt_idx].virt_addr +
		       (tid % num_tids_per_block) * tid_size;

	वापस 0;
पूर्ण

अटल u16 qed_blk_calculate_pages(काष्ठा qed_ilt_cli_blk *p_blk)
अणु
	अगर (p_blk->real_size_in_page == 0)
		वापस 0;

	वापस DIV_ROUND_UP(p_blk->total_size, p_blk->real_size_in_page);
पूर्ण

u16 qed_get_cdut_num_pf_init_pages(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	u16 i, pages = 0;

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		p_blk = &p_cli->pf_blks[CDUT_FL_SEG_BLK(i, PF)];
		pages += qed_blk_calculate_pages(p_blk);
	पूर्ण

	वापस pages;
पूर्ण

u16 qed_get_cdut_num_vf_init_pages(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	u16 i, pages = 0;

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
	क्रम (i = 0; i < NUM_TASK_VF_SEGMENTS; i++) अणु
		p_blk = &p_cli->vf_blks[CDUT_FL_SEG_BLK(i, VF)];
		pages += qed_blk_calculate_pages(p_blk);
	पूर्ण

	वापस pages;
पूर्ण

u16 qed_get_cdut_num_pf_work_pages(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	u16 i, pages = 0;

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
	क्रम (i = 0; i < NUM_TASK_PF_SEGMENTS; i++) अणु
		p_blk = &p_cli->pf_blks[CDUT_SEG_BLK(i)];
		pages += qed_blk_calculate_pages(p_blk);
	पूर्ण

	वापस pages;
पूर्ण

u16 qed_get_cdut_num_vf_work_pages(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ilt_client_cfg *p_cli;
	काष्ठा qed_ilt_cli_blk *p_blk;
	u16 pages = 0, i;

	p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
	क्रम (i = 0; i < NUM_TASK_VF_SEGMENTS; i++) अणु
		p_blk = &p_cli->vf_blks[CDUT_SEG_BLK(i)];
		pages += qed_blk_calculate_pages(p_blk);
	पूर्ण

	वापस pages;
पूर्ण
