<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_int.h"
#समावेश "qed_iscsi.h"
#समावेश "qed_mcp.h"
#समावेश "qed_ooo.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश "qed_rdma.h"

/***************************************************************************
* Structures & Definitions
***************************************************************************/

#घोषणा SPQ_HIGH_PRI_RESERVE_DEFAULT    (1)

#घोषणा SPQ_BLOCK_DELAY_MAX_ITER        (10)
#घोषणा SPQ_BLOCK_DELAY_US              (10)
#घोषणा SPQ_BLOCK_SLEEP_MAX_ITER        (1000)
#घोषणा SPQ_BLOCK_SLEEP_MS              (5)

/***************************************************************************
* Blocking Imp. (BLOCK/EBLOCK mode)
***************************************************************************/
अटल व्योम qed_spq_blocking_cb(काष्ठा qed_hwfn *p_hwfn,
				व्योम *cookie,
				जोड़ event_ring_data *data, u8 fw_वापस_code)
अणु
	काष्ठा qed_spq_comp_करोne *comp_करोne;

	comp_करोne = (काष्ठा qed_spq_comp_करोne *)cookie;

	comp_करोne->fw_वापस_code = fw_वापस_code;

	/* Make sure completion करोne is visible on रुकोing thपढ़ो */
	smp_store_release(&comp_करोne->करोne, 0x1);
पूर्ण

अटल पूर्णांक __qed_spq_block(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_spq_entry *p_ent,
			   u8 *p_fw_ret, bool sleep_between_iter)
अणु
	काष्ठा qed_spq_comp_करोne *comp_करोne;
	u32 iter_cnt;

	comp_करोne = (काष्ठा qed_spq_comp_करोne *)p_ent->comp_cb.cookie;
	iter_cnt = sleep_between_iter ? SPQ_BLOCK_SLEEP_MAX_ITER
				      : SPQ_BLOCK_DELAY_MAX_ITER;

	जबतक (iter_cnt--) अणु
		/* Validate we receive completion update */
		अगर (smp_load_acquire(&comp_करोne->करोne) == 1) अणु /* ^^^ */
			अगर (p_fw_ret)
				*p_fw_ret = comp_करोne->fw_वापस_code;
			वापस 0;
		पूर्ण

		अगर (sleep_between_iter)
			msleep(SPQ_BLOCK_SLEEP_MS);
		अन्यथा
			udelay(SPQ_BLOCK_DELAY_US);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक qed_spq_block(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_spq_entry *p_ent,
			 u8 *p_fw_ret, bool skip_quick_poll)
अणु
	काष्ठा qed_spq_comp_करोne *comp_करोne;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc;

	/* A relatively लघु polling period w/o sleeping, to allow the FW to
	 * complete the ramrod and thus possibly to aव्योम the following sleeps.
	 */
	अगर (!skip_quick_poll) अणु
		rc = __qed_spq_block(p_hwfn, p_ent, p_fw_ret, false);
		अगर (!rc)
			वापस 0;
	पूर्ण

	/* Move to polling with a sleeping period between iterations */
	rc = __qed_spq_block(p_hwfn, p_ent, p_fw_ret, true);
	अगर (!rc)
		वापस 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_NOTICE(p_hwfn, "ptt, failed to acquire\n");
		वापस -EAGAIN;
	पूर्ण

	DP_INFO(p_hwfn, "Ramrod is stuck, requesting MCP drain\n");
	rc = qed_mcp_drain(p_hwfn, p_ptt);
	qed_ptt_release(p_hwfn, p_ptt);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "MCP drain failed\n");
		जाओ err;
	पूर्ण

	/* Retry after drain */
	rc = __qed_spq_block(p_hwfn, p_ent, p_fw_ret, true);
	अगर (!rc)
		वापस 0;

	comp_करोne = (काष्ठा qed_spq_comp_करोne *)p_ent->comp_cb.cookie;
	अगर (comp_करोne->करोne == 1) अणु
		अगर (p_fw_ret)
			*p_fw_ret = comp_करोne->fw_वापस_code;
		वापस 0;
	पूर्ण
err:
	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EBUSY;
	qed_hw_err_notअगरy(p_hwfn, p_ptt, QED_HW_ERR_RAMROD_FAIL,
			  "Ramrod is stuck [CID %08x cmd %02x protocol %02x echo %04x]\n",
			  le32_to_cpu(p_ent->elem.hdr.cid),
			  p_ent->elem.hdr.cmd_id,
			  p_ent->elem.hdr.protocol_id,
			  le16_to_cpu(p_ent->elem.hdr.echo));
	qed_ptt_release(p_hwfn, p_ptt);

	वापस -EBUSY;
पूर्ण

/***************************************************************************
* SPQ entries inner API
***************************************************************************/
अटल पूर्णांक qed_spq_fill_entry(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_spq_entry *p_ent)
अणु
	p_ent->flags = 0;

	चयन (p_ent->comp_mode) अणु
	हाल QED_SPQ_MODE_EBLOCK:
	हाल QED_SPQ_MODE_BLOCK:
		p_ent->comp_cb.function = qed_spq_blocking_cb;
		अवरोध;
	हाल QED_SPQ_MODE_CB:
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown SPQE completion mode %d\n",
			  p_ent->comp_mode);
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Ramrod header: [CID 0x%08x CMD 0x%02x protocol 0x%02x] Data pointer: [%08x:%08x] Completion Mode: %s\n",
		   p_ent->elem.hdr.cid,
		   p_ent->elem.hdr.cmd_id,
		   p_ent->elem.hdr.protocol_id,
		   p_ent->elem.data_ptr.hi,
		   p_ent->elem.data_ptr.lo,
		   D_TRINE(p_ent->comp_mode, QED_SPQ_MODE_EBLOCK,
			   QED_SPQ_MODE_BLOCK, "MODE_EBLOCK", "MODE_BLOCK",
			   "MODE_CB"));

	वापस 0;
पूर्ण

/***************************************************************************
* HSI access
***************************************************************************/
अटल व्योम qed_spq_hw_initialize(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_spq *p_spq)
अणु
	काष्ठा e4_core_conn_context *p_cxt;
	काष्ठा qed_cxt_info cxt_info;
	u16 physical_q;
	पूर्णांक rc;

	cxt_info.iid = p_spq->cid;

	rc = qed_cxt_get_cid_info(p_hwfn, &cxt_info);

	अगर (rc < 0) अणु
		DP_NOTICE(p_hwfn, "Cannot find context info for cid=%d\n",
			  p_spq->cid);
		वापस;
	पूर्ण

	p_cxt = cxt_info.p_cxt;

	SET_FIELD(p_cxt->xstorm_ag_context.flags10,
		  E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_EN, 1);
	SET_FIELD(p_cxt->xstorm_ag_context.flags1,
		  E4_XSTORM_CORE_CONN_AG_CTX_DQ_CF_ACTIVE, 1);
	SET_FIELD(p_cxt->xstorm_ag_context.flags9,
		  E4_XSTORM_CORE_CONN_AG_CTX_CONSOLID_PROD_CF_EN, 1);

	/* QM physical queue */
	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LB);
	p_cxt->xstorm_ag_context.physical_q0 = cpu_to_le16(physical_q);

	p_cxt->xstorm_st_context.spq_base_lo =
		DMA_LO_LE(p_spq->chain.p_phys_addr);
	p_cxt->xstorm_st_context.spq_base_hi =
		DMA_HI_LE(p_spq->chain.p_phys_addr);

	DMA_REGPAIR_LE(p_cxt->xstorm_st_context.consolid_base_addr,
		       p_hwfn->p_consq->chain.p_phys_addr);
पूर्ण

अटल पूर्णांक qed_spq_hw_post(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_spq *p_spq, काष्ठा qed_spq_entry *p_ent)
अणु
	काष्ठा qed_chain *p_chain = &p_hwfn->p_spq->chain;
	काष्ठा core_db_data *p_db_data = &p_spq->db_data;
	u16 echo = qed_chain_get_prod_idx(p_chain);
	काष्ठा slow_path_element	*elem;

	p_ent->elem.hdr.echo	= cpu_to_le16(echo);
	elem = qed_chain_produce(p_chain);
	अगर (!elem) अणु
		DP_NOTICE(p_hwfn, "Failed to produce from SPQ chain\n");
		वापस -EINVAL;
	पूर्ण

	*elem = p_ent->elem; /* काष्ठा assignment */

	/* send a करोorbell on the slow hwfn session */
	p_db_data->spq_prod = cpu_to_le16(qed_chain_get_prod_idx(p_chain));

	/* make sure the SPQE is updated beक्रमe the करोorbell */
	wmb();

	DOORBELL(p_hwfn, p_spq->db_addr_offset, *(u32 *)p_db_data);

	/* make sure करोorbell is rang */
	wmb();

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Doorbelled [0x%08x, CID 0x%08x] with Flags: %02x agg_params: %02x, prod: %04x\n",
		   p_spq->db_addr_offset,
		   p_spq->cid,
		   p_db_data->params,
		   p_db_data->agg_flags, qed_chain_get_prod_idx(p_chain));

	वापस 0;
पूर्ण

/***************************************************************************
* Asynchronous events
***************************************************************************/
अटल पूर्णांक
qed_async_event_completion(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा event_ring_entry *p_eqe)
अणु
	qed_spq_async_comp_cb cb;

	अगर (!p_hwfn->p_spq || (p_eqe->protocol_id >= MAX_PROTOCOL_TYPE))
		वापस -EINVAL;

	cb = p_hwfn->p_spq->async_comp_cb[p_eqe->protocol_id];
	अगर (cb) अणु
		वापस cb(p_hwfn, p_eqe->opcode, p_eqe->echo,
			  &p_eqe->data, p_eqe->fw_वापस_code);
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn,
			  "Unknown Async completion for protocol: %d\n",
			  p_eqe->protocol_id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक
qed_spq_रेजिस्टर_async_cb(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत protocol_type protocol_id,
			  qed_spq_async_comp_cb cb)
अणु
	अगर (!p_hwfn->p_spq || (protocol_id >= MAX_PROTOCOL_TYPE))
		वापस -EINVAL;

	p_hwfn->p_spq->async_comp_cb[protocol_id] = cb;
	वापस 0;
पूर्ण

व्योम
qed_spq_unरेजिस्टर_async_cb(काष्ठा qed_hwfn *p_hwfn,
			    क्रमागत protocol_type protocol_id)
अणु
	अगर (!p_hwfn->p_spq || (protocol_id >= MAX_PROTOCOL_TYPE))
		वापस;

	p_hwfn->p_spq->async_comp_cb[protocol_id] = शून्य;
पूर्ण

/***************************************************************************
* EQ API
***************************************************************************/
व्योम qed_eq_prod_update(काष्ठा qed_hwfn *p_hwfn, u16 prod)
अणु
	u32 addr = GTT_BAR0_MAP_REG_USDM_RAM +
		   USTORM_EQE_CONS_OFFSET(p_hwfn->rel_pf_id);

	REG_WR16(p_hwfn, addr, prod);
पूर्ण

पूर्णांक qed_eq_completion(काष्ठा qed_hwfn *p_hwfn, व्योम *cookie)
अणु
	काष्ठा qed_eq *p_eq = cookie;
	काष्ठा qed_chain *p_chain = &p_eq->chain;
	पूर्णांक rc = 0;

	/* take a snapshot of the FW consumer */
	u16 fw_cons_idx = le16_to_cpu(*p_eq->p_fw_cons);

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ, "fw_cons_idx %x\n", fw_cons_idx);

	/* Need to guarantee the fw_cons index we use poपूर्णांकs to a usuable
	 * element (to comply with our chain), so our macros would comply
	 */
	अगर ((fw_cons_idx & qed_chain_get_usable_per_page(p_chain)) ==
	    qed_chain_get_usable_per_page(p_chain))
		fw_cons_idx += qed_chain_get_unusable_per_page(p_chain);

	/* Complete current segment of eq entries */
	जबतक (fw_cons_idx != qed_chain_get_cons_idx(p_chain)) अणु
		काष्ठा event_ring_entry *p_eqe = qed_chain_consume(p_chain);

		अगर (!p_eqe) अणु
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
			   "op %x prot %x res0 %x echo %x fwret %x flags %x\n",
			   p_eqe->opcode,
			   p_eqe->protocol_id,
			   p_eqe->reserved0,
			   le16_to_cpu(p_eqe->echo),
			   p_eqe->fw_वापस_code,
			   p_eqe->flags);

		अगर (GET_FIELD(p_eqe->flags, EVENT_RING_ENTRY_ASYNC)) अणु
			अगर (qed_async_event_completion(p_hwfn, p_eqe))
				rc = -EINVAL;
		पूर्ण अन्यथा अगर (qed_spq_completion(p_hwfn,
					      p_eqe->echo,
					      p_eqe->fw_वापस_code,
					      &p_eqe->data)) अणु
			rc = -EINVAL;
		पूर्ण

		qed_chain_recycle_consumed(p_chain);
	पूर्ण

	qed_eq_prod_update(p_hwfn, qed_chain_get_prod_idx(p_chain));

	/* Attempt to post pending requests */
	spin_lock_bh(&p_hwfn->p_spq->lock);
	rc = qed_spq_pend_post(p_hwfn);
	spin_unlock_bh(&p_hwfn->p_spq->lock);

	वापस rc;
पूर्ण

पूर्णांक qed_eq_alloc(काष्ठा qed_hwfn *p_hwfn, u16 num_elem)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.num_elems	= num_elem,
		.elem_size	= माप(जोड़ event_ring_element),
	पूर्ण;
	काष्ठा qed_eq *p_eq;
	पूर्णांक ret;

	/* Allocate EQ काष्ठा */
	p_eq = kzalloc(माप(*p_eq), GFP_KERNEL);
	अगर (!p_eq)
		वापस -ENOMEM;

	ret = qed_chain_alloc(p_hwfn->cdev, &p_eq->chain, &params);
	अगर (ret) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate EQ chain\n");
		जाओ eq_allocate_fail;
	पूर्ण

	/* रेजिस्टर EQ completion on the SP SB */
	qed_पूर्णांक_रेजिस्टर_cb(p_hwfn, qed_eq_completion,
			    p_eq, &p_eq->eq_sb_index, &p_eq->p_fw_cons);

	p_hwfn->p_eq = p_eq;
	वापस 0;

eq_allocate_fail:
	kमुक्त(p_eq);

	वापस ret;
पूर्ण

व्योम qed_eq_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_chain_reset(&p_hwfn->p_eq->chain);
पूर्ण

व्योम qed_eq_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn->p_eq)
		वापस;

	qed_chain_मुक्त(p_hwfn->cdev, &p_hwfn->p_eq->chain);

	kमुक्त(p_hwfn->p_eq);
	p_hwfn->p_eq = शून्य;
पूर्ण

/***************************************************************************
* CQE API - manipulate EQ functionality
***************************************************************************/
अटल पूर्णांक qed_cqe_completion(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा eth_slow_path_rx_cqe *cqe,
			      क्रमागत protocol_type protocol)
अणु
	अगर (IS_VF(p_hwfn->cdev))
		वापस 0;

	/* @@@पंचांगp - it's possible we'll eventually want to handle some
	 * actual commands that can arrive here, but क्रम now this is only
	 * used to complete the ramrod using the echo value on the cqe
	 */
	वापस qed_spq_completion(p_hwfn, cqe->echo, 0, शून्य);
पूर्ण

पूर्णांक qed_eth_cqe_completion(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा eth_slow_path_rx_cqe *cqe)
अणु
	पूर्णांक rc;

	rc = qed_cqe_completion(p_hwfn, cqe, PROTOCOLID_ETH);
	अगर (rc)
		DP_NOTICE(p_hwfn,
			  "Failed to handle RXQ CQE [cmd 0x%02x]\n",
			  cqe->ramrod_cmd_id);

	वापस rc;
पूर्ण

/***************************************************************************
* Slow hwfn Queue (spq)
***************************************************************************/
व्योम qed_spq_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;
	काष्ठा qed_spq_entry *p_virt = शून्य;
	काष्ठा core_db_data *p_db_data;
	व्योम __iomem *db_addr;
	dma_addr_t p_phys = 0;
	u32 i, capacity;
	पूर्णांक rc;

	INIT_LIST_HEAD(&p_spq->pending);
	INIT_LIST_HEAD(&p_spq->completion_pending);
	INIT_LIST_HEAD(&p_spq->मुक्त_pool);
	INIT_LIST_HEAD(&p_spq->unlimited_pending);
	spin_lock_init(&p_spq->lock);

	/* SPQ empty pool */
	p_phys	= p_spq->p_phys + दुरत्व(काष्ठा qed_spq_entry, ramrod);
	p_virt	= p_spq->p_virt;

	capacity = qed_chain_get_capacity(&p_spq->chain);
	क्रम (i = 0; i < capacity; i++) अणु
		DMA_REGPAIR_LE(p_virt->elem.data_ptr, p_phys);

		list_add_tail(&p_virt->list, &p_spq->मुक्त_pool);

		p_virt++;
		p_phys += माप(काष्ठा qed_spq_entry);
	पूर्ण

	/* Statistics */
	p_spq->normal_count		= 0;
	p_spq->comp_count		= 0;
	p_spq->comp_sent_count		= 0;
	p_spq->unlimited_pending_count	= 0;

	biपंचांगap_zero(p_spq->p_comp_biपंचांगap, SPQ_RING_SIZE);
	p_spq->comp_biपंचांगap_idx = 0;

	/* SPQ cid, cannot fail */
	qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_CORE, &p_spq->cid);
	qed_spq_hw_initialize(p_hwfn, p_spq);

	/* reset the chain itself */
	qed_chain_reset(&p_spq->chain);

	/* Initialize the address/data of the SPQ करोorbell */
	p_spq->db_addr_offset = qed_db_addr(p_spq->cid, DQ_DEMS_LEGACY);
	p_db_data = &p_spq->db_data;
	स_रखो(p_db_data, 0, माप(*p_db_data));
	SET_FIELD(p_db_data->params, CORE_DB_DATA_DEST, DB_DEST_XCM);
	SET_FIELD(p_db_data->params, CORE_DB_DATA_AGG_CMD, DB_AGG_CMD_MAX);
	SET_FIELD(p_db_data->params, CORE_DB_DATA_AGG_VAL_SEL,
		  DQ_XCM_CORE_SPQ_PROD_CMD);
	p_db_data->agg_flags = DQ_XCM_CORE_DQ_CF_CMD;

	/* Register the SPQ करोorbell with the करोorbell recovery mechanism */
	db_addr = (व्योम __iomem *)((u8 __iomem *)p_hwfn->करोorbells +
				   p_spq->db_addr_offset);
	rc = qed_db_recovery_add(p_hwfn->cdev, db_addr, &p_spq->db_data,
				 DB_REC_WIDTH_32B, DB_REC_KERNEL);
	अगर (rc)
		DP_INFO(p_hwfn,
			"Failed to register the SPQ doorbell with the doorbell recovery mechanism\n");
पूर्ण

पूर्णांक qed_spq_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_SINGLE,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.elem_size	= माप(काष्ठा slow_path_element),
	पूर्ण;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	काष्ठा qed_spq_entry *p_virt = शून्य;
	काष्ठा qed_spq *p_spq = शून्य;
	dma_addr_t p_phys = 0;
	u32 capacity;
	पूर्णांक ret;

	/* SPQ काष्ठा */
	p_spq = kzalloc(माप(काष्ठा qed_spq), GFP_KERNEL);
	अगर (!p_spq)
		वापस -ENOMEM;

	/* SPQ ring */
	ret = qed_chain_alloc(cdev, &p_spq->chain, &params);
	अगर (ret) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate SPQ chain\n");
		जाओ spq_chain_alloc_fail;
	पूर्ण

	/* allocate and fill the SPQ elements (incl. ramrod data list) */
	capacity = qed_chain_get_capacity(&p_spq->chain);
	ret = -ENOMEM;

	p_virt = dma_alloc_coherent(&cdev->pdev->dev,
				    capacity * माप(काष्ठा qed_spq_entry),
				    &p_phys, GFP_KERNEL);
	अगर (!p_virt)
		जाओ spq_alloc_fail;

	p_spq->p_virt = p_virt;
	p_spq->p_phys = p_phys;
	p_hwfn->p_spq = p_spq;

	वापस 0;

spq_alloc_fail:
	qed_chain_मुक्त(cdev, &p_spq->chain);
spq_chain_alloc_fail:
	kमुक्त(p_spq);

	वापस ret;
पूर्ण

व्योम qed_spq_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;
	व्योम __iomem *db_addr;
	u32 capacity;

	अगर (!p_spq)
		वापस;

	/* Delete the SPQ करोorbell from the करोorbell recovery mechanism */
	db_addr = (व्योम __iomem *)((u8 __iomem *)p_hwfn->करोorbells +
				   p_spq->db_addr_offset);
	qed_db_recovery_del(p_hwfn->cdev, db_addr, &p_spq->db_data);

	अगर (p_spq->p_virt) अणु
		capacity = qed_chain_get_capacity(&p_spq->chain);
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  capacity *
				  माप(काष्ठा qed_spq_entry),
				  p_spq->p_virt, p_spq->p_phys);
	पूर्ण

	qed_chain_मुक्त(p_hwfn->cdev, &p_spq->chain);
	kमुक्त(p_spq);
	p_hwfn->p_spq = शून्य;
पूर्ण

पूर्णांक qed_spq_get_entry(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_spq_entry **pp_ent)
अणु
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	पूर्णांक rc = 0;

	spin_lock_bh(&p_spq->lock);

	अगर (list_empty(&p_spq->मुक्त_pool)) अणु
		p_ent = kzalloc(माप(*p_ent), GFP_ATOMIC);
		अगर (!p_ent) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to allocate an SPQ entry for a pending ramrod\n");
			rc = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		p_ent->queue = &p_spq->unlimited_pending;
	पूर्ण अन्यथा अणु
		p_ent = list_first_entry(&p_spq->मुक्त_pool,
					 काष्ठा qed_spq_entry, list);
		list_del(&p_ent->list);
		p_ent->queue = &p_spq->pending;
	पूर्ण

	*pp_ent = p_ent;

out_unlock:
	spin_unlock_bh(&p_spq->lock);
	वापस rc;
पूर्ण

/* Locked variant; Should be called जबतक the SPQ lock is taken */
अटल व्योम __qed_spq_वापस_entry(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_spq_entry *p_ent)
अणु
	list_add_tail(&p_ent->list, &p_hwfn->p_spq->मुक्त_pool);
पूर्ण

व्योम qed_spq_वापस_entry(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_spq_entry *p_ent)
अणु
	spin_lock_bh(&p_hwfn->p_spq->lock);
	__qed_spq_वापस_entry(p_hwfn, p_ent);
	spin_unlock_bh(&p_hwfn->p_spq->lock);
पूर्ण

/**
 * qed_spq_add_entry() - Add a new entry to the pending list.
 *                       Should be used जबतक lock is being held.
 *
 * @p_hwfn: HW device data.
 * @p_ent: An entry to add.
 * @priority: Desired priority.
 *
 * Adds an entry to the pending list is there is room (an empty
 * element is available in the मुक्त_pool), or अन्यथा places the
 * entry in the unlimited_pending pool.
 *
 * Return: zero on success, -EINVAL on invalid @priority.
 */
अटल पूर्णांक qed_spq_add_entry(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_spq_entry *p_ent,
			     क्रमागत spq_priority priority)
अणु
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;

	अगर (p_ent->queue == &p_spq->unlimited_pending) अणु

		अगर (list_empty(&p_spq->मुक्त_pool)) अणु
			list_add_tail(&p_ent->list, &p_spq->unlimited_pending);
			p_spq->unlimited_pending_count++;

			वापस 0;
		पूर्ण अन्यथा अणु
			काष्ठा qed_spq_entry *p_en2;

			p_en2 = list_first_entry(&p_spq->मुक्त_pool,
						 काष्ठा qed_spq_entry, list);
			list_del(&p_en2->list);

			/* Copy the ring element physical poपूर्णांकer to the new
			 * entry, since we are about to override the entire ring
			 * entry and करोn't want to lose the poपूर्णांकer.
			 */
			p_ent->elem.data_ptr = p_en2->elem.data_ptr;

			*p_en2 = *p_ent;

			/* EBLOCK responsible to मुक्त the allocated p_ent */
			अगर (p_ent->comp_mode != QED_SPQ_MODE_EBLOCK)
				kमुक्त(p_ent);
			अन्यथा
				p_ent->post_ent = p_en2;

			p_ent = p_en2;
		पूर्ण
	पूर्ण

	/* entry is to be placed in 'pending' queue */
	चयन (priority) अणु
	हाल QED_SPQ_PRIORITY_NORMAL:
		list_add_tail(&p_ent->list, &p_spq->pending);
		p_spq->normal_count++;
		अवरोध;
	हाल QED_SPQ_PRIORITY_HIGH:
		list_add(&p_ent->list, &p_spq->pending);
		p_spq->high_count++;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/***************************************************************************
* Accessor
***************************************************************************/
u32 qed_spq_get_cid(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn->p_spq)
		वापस 0xffffffff;      /* illegal */
	वापस p_hwfn->p_spq->cid;
पूर्ण

/***************************************************************************
* Posting new Ramrods
***************************************************************************/
अटल पूर्णांक qed_spq_post_list(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा list_head *head, u32 keep_reserve)
अणु
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;
	पूर्णांक rc;

	जबतक (qed_chain_get_elem_left(&p_spq->chain) > keep_reserve &&
	       !list_empty(head)) अणु
		काष्ठा qed_spq_entry *p_ent =
			list_first_entry(head, काष्ठा qed_spq_entry, list);
		list_move_tail(&p_ent->list, &p_spq->completion_pending);
		p_spq->comp_sent_count++;

		rc = qed_spq_hw_post(p_hwfn, p_spq, p_ent);
		अगर (rc) अणु
			list_del(&p_ent->list);
			__qed_spq_वापस_entry(p_hwfn, p_ent);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_spq_pend_post(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;
	काष्ठा qed_spq_entry *p_ent = शून्य;

	जबतक (!list_empty(&p_spq->मुक्त_pool)) अणु
		अगर (list_empty(&p_spq->unlimited_pending))
			अवरोध;

		p_ent = list_first_entry(&p_spq->unlimited_pending,
					 काष्ठा qed_spq_entry, list);
		अगर (!p_ent)
			वापस -EINVAL;

		list_del(&p_ent->list);

		qed_spq_add_entry(p_hwfn, p_ent, p_ent->priority);
	पूर्ण

	वापस qed_spq_post_list(p_hwfn, &p_spq->pending,
				 SPQ_HIGH_PRI_RESERVE_DEFAULT);
पूर्ण

अटल व्योम qed_spq_recov_set_ret_code(काष्ठा qed_spq_entry *p_ent,
				       u8 *fw_वापस_code)
अणु
	अगर (!fw_वापस_code)
		वापस;

	अगर (p_ent->elem.hdr.protocol_id == PROTOCOLID_ROCE ||
	    p_ent->elem.hdr.protocol_id == PROTOCOLID_IWARP)
		*fw_वापस_code = RDMA_RETURN_OK;
पूर्ण

/* Aव्योम overriding of SPQ entries when getting out-of-order completions, by
 * marking the completions in a biपंचांगap and increasing the chain consumer only
 * क्रम the first successive completed entries.
 */
अटल व्योम qed_spq_comp_bmap_update(काष्ठा qed_hwfn *p_hwfn, __le16 echo)
अणु
	u16 pos = le16_to_cpu(echo) % SPQ_RING_SIZE;
	काष्ठा qed_spq *p_spq = p_hwfn->p_spq;

	__set_bit(pos, p_spq->p_comp_biपंचांगap);
	जबतक (test_bit(p_spq->comp_biपंचांगap_idx,
			p_spq->p_comp_biपंचांगap)) अणु
		__clear_bit(p_spq->comp_biपंचांगap_idx,
			    p_spq->p_comp_biपंचांगap);
		p_spq->comp_biपंचांगap_idx++;
		qed_chain_वापस_produced(&p_spq->chain);
	पूर्ण
पूर्ण

पूर्णांक qed_spq_post(काष्ठा qed_hwfn *p_hwfn,
		 काष्ठा qed_spq_entry *p_ent, u8 *fw_वापस_code)
अणु
	पूर्णांक rc = 0;
	काष्ठा qed_spq *p_spq = p_hwfn ? p_hwfn->p_spq : शून्य;
	bool b_ret_ent = true;
	bool eblock;

	अगर (!p_hwfn)
		वापस -EINVAL;

	अगर (!p_ent) अणु
		DP_NOTICE(p_hwfn, "Got a NULL pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (p_hwfn->cdev->recov_in_prog) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SPQ,
			   "Recovery is in progress. Skip spq post [cmd %02x protocol %02x]\n",
			   p_ent->elem.hdr.cmd_id, p_ent->elem.hdr.protocol_id);

		/* Let the flow complete w/o any error handling */
		qed_spq_recov_set_ret_code(p_ent, fw_वापस_code);
		वापस 0;
	पूर्ण

	/* Complete the entry */
	rc = qed_spq_fill_entry(p_hwfn, p_ent);

	spin_lock_bh(&p_spq->lock);

	/* Check वापस value after LOCK is taken क्रम cleaner error flow */
	अगर (rc)
		जाओ spq_post_fail;

	/* Check अगर entry is in block mode beक्रमe qed_spq_add_entry,
	 * which might kमुक्त p_ent.
	 */
	eblock = (p_ent->comp_mode == QED_SPQ_MODE_EBLOCK);

	/* Add the request to the pending queue */
	rc = qed_spq_add_entry(p_hwfn, p_ent, p_ent->priority);
	अगर (rc)
		जाओ spq_post_fail;

	rc = qed_spq_pend_post(p_hwfn);
	अगर (rc) अणु
		/* Since it's possible that pending failed क्रम a dअगरferent
		 * entry [although unlikely], the failed entry was alपढ़ोy
		 * dealt with; No need to वापस it here.
		 */
		b_ret_ent = false;
		जाओ spq_post_fail;
	पूर्ण

	spin_unlock_bh(&p_spq->lock);

	अगर (eblock) अणु
		/* For entries in QED BLOCK mode, the completion code cannot
		 * perक्रमm the necessary cleanup - अगर it did, we couldn't
		 * access p_ent here to see whether it's successful or not.
		 * Thus, after gaining the answer perक्रमm the cleanup here.
		 */
		rc = qed_spq_block(p_hwfn, p_ent, fw_वापस_code,
				   p_ent->queue == &p_spq->unlimited_pending);

		अगर (p_ent->queue == &p_spq->unlimited_pending) अणु
			काष्ठा qed_spq_entry *p_post_ent = p_ent->post_ent;

			kमुक्त(p_ent);

			/* Return the entry which was actually posted */
			p_ent = p_post_ent;
		पूर्ण

		अगर (rc)
			जाओ spq_post_fail2;

		/* वापस to pool */
		qed_spq_वापस_entry(p_hwfn, p_ent);
	पूर्ण
	वापस rc;

spq_post_fail2:
	spin_lock_bh(&p_spq->lock);
	list_del(&p_ent->list);
	qed_spq_comp_bmap_update(p_hwfn, p_ent->elem.hdr.echo);

spq_post_fail:
	/* वापस to the मुक्त pool */
	अगर (b_ret_ent)
		__qed_spq_वापस_entry(p_hwfn, p_ent);
	spin_unlock_bh(&p_spq->lock);

	वापस rc;
पूर्ण

पूर्णांक qed_spq_completion(काष्ठा qed_hwfn *p_hwfn,
		       __le16 echo,
		       u8 fw_वापस_code,
		       जोड़ event_ring_data *p_data)
अणु
	काष्ठा qed_spq		*p_spq;
	काष्ठा qed_spq_entry	*p_ent = शून्य;
	काष्ठा qed_spq_entry	*पंचांगp;
	काष्ठा qed_spq_entry	*found = शून्य;

	अगर (!p_hwfn)
		वापस -EINVAL;

	p_spq = p_hwfn->p_spq;
	अगर (!p_spq)
		वापस -EINVAL;

	spin_lock_bh(&p_spq->lock);
	list_क्रम_each_entry_safe(p_ent, पंचांगp, &p_spq->completion_pending, list) अणु
		अगर (p_ent->elem.hdr.echo == echo) अणु
			list_del(&p_ent->list);
			qed_spq_comp_bmap_update(p_hwfn, echo);
			p_spq->comp_count++;
			found = p_ent;
			अवरोध;
		पूर्ण

		/* This is relatively uncommon - depends on scenarios
		 * which have mutliple per-PF sent ramrods.
		 */
		DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
			   "Got completion for echo %04x - doesn't match echo %04x in completion pending list\n",
			   le16_to_cpu(echo),
			   le16_to_cpu(p_ent->elem.hdr.echo));
	पूर्ण

	/* Release lock beक्रमe callback, as callback may post
	 * an additional ramrod.
	 */
	spin_unlock_bh(&p_spq->lock);

	अगर (!found) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to find an entry this EQE [echo %04x] completes\n",
			  le16_to_cpu(echo));
		वापस -EEXIST;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Complete EQE [echo %04x]: func %p cookie %p)\n",
		   le16_to_cpu(echo),
		   p_ent->comp_cb.function, p_ent->comp_cb.cookie);
	अगर (found->comp_cb.function)
		found->comp_cb.function(p_hwfn, found->comp_cb.cookie, p_data,
					fw_वापस_code);
	अन्यथा
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SPQ,
			   "Got a completion without a callback function\n");

	अगर (found->comp_mode != QED_SPQ_MODE_EBLOCK)
		/* EBLOCK  is responsible क्रम वापसing its own entry पूर्णांकo the
		 * मुक्त list.
		 */
		qed_spq_वापस_entry(p_hwfn, found);

	वापस 0;
पूर्ण

#घोषणा QED_SPQ_CONSQ_ELEM_SIZE		0x80

पूर्णांक qed_consq_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.num_elems	= QED_CHAIN_PAGE_SIZE / QED_SPQ_CONSQ_ELEM_SIZE,
		.elem_size	= QED_SPQ_CONSQ_ELEM_SIZE,
	पूर्ण;
	काष्ठा qed_consq *p_consq;
	पूर्णांक ret;

	/* Allocate ConsQ काष्ठा */
	p_consq = kzalloc(माप(*p_consq), GFP_KERNEL);
	अगर (!p_consq)
		वापस -ENOMEM;

	/* Allocate and initialize ConsQ chain */
	ret = qed_chain_alloc(p_hwfn->cdev, &p_consq->chain, &params);
	अगर (ret) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate ConsQ chain");
		जाओ consq_alloc_fail;
	पूर्ण

	p_hwfn->p_consq = p_consq;

	वापस 0;

consq_alloc_fail:
	kमुक्त(p_consq);

	वापस ret;
पूर्ण

व्योम qed_consq_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_chain_reset(&p_hwfn->p_consq->chain);
पूर्ण

व्योम qed_consq_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn->p_consq)
		वापस;

	qed_chain_मुक्त(p_hwfn->cdev, &p_hwfn->p_consq->chain);

	kमुक्त(p_hwfn->p_consq);
	p_hwfn->p_consq = शून्य;
पूर्ण
