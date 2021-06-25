<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/param.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#घोषणा __PREVENT_DUMP_MEM_ARR__
#घोषणा __PREVENT_PXP_GLOBAL_WIN__
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_fcoe.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_int.h"
#समावेश "qed_ll2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश <linux/qed/qed_fcoe_अगर.h>

काष्ठा qed_fcoe_conn अणु
	काष्ठा list_head list_entry;
	bool मुक्त_on_delete;

	u16 conn_id;
	u32 icid;
	u32 fw_cid;
	u8 layer_code;

	dma_addr_t sq_pbl_addr;
	dma_addr_t sq_curr_page_addr;
	dma_addr_t sq_next_page_addr;
	dma_addr_t xferq_pbl_addr;
	व्योम *xferq_pbl_addr_virt_addr;
	dma_addr_t xferq_addr[4];
	व्योम *xferq_addr_virt_addr[4];
	dma_addr_t confq_pbl_addr;
	व्योम *confq_pbl_addr_virt_addr;
	dma_addr_t confq_addr[2];
	व्योम *confq_addr_virt_addr[2];

	dma_addr_t terminate_params;

	u16 dst_mac_addr_lo;
	u16 dst_mac_addr_mid;
	u16 dst_mac_addr_hi;
	u16 src_mac_addr_lo;
	u16 src_mac_addr_mid;
	u16 src_mac_addr_hi;

	u16 tx_max_fc_pay_len;
	u16 e_d_tov_समयr_val;
	u16 rec_tov_समयr_val;
	u16 rx_max_fc_pay_len;
	u16 vlan_tag;
	u16 physical_q0;

	काष्ठा fc_addr_nw s_id;
	u8 max_conc_seqs_c3;
	काष्ठा fc_addr_nw d_id;
	u8 flags;
	u8 def_q_idx;
पूर्ण;

अटल पूर्णांक
qed_sp_fcoe_func_start(काष्ठा qed_hwfn *p_hwfn,
		       क्रमागत spq_mode comp_mode,
		       काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा qed_fcoe_pf_params *fcoe_pf_params = शून्य;
	काष्ठा fcoe_init_ramrod_params *p_ramrod = शून्य;
	काष्ठा fcoe_init_func_ramrod_data *p_data;
	काष्ठा e4_fcoe_conn_context *p_cxt = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_cxt_info cxt_info;
	u32 dummy_cid;
	पूर्णांक rc = 0;
	__le16 पंचांगp;
	u8 i;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_INIT_FUNC,
				 PROTOCOLID_FCOE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.fcoe_init;
	p_data = &p_ramrod->init_ramrod_data;
	fcoe_pf_params = &p_hwfn->pf_params.fcoe_pf_params;

	/* Sanity */
	अगर (fcoe_pf_params->num_cqs > p_hwfn->hw_info.feat_num[QED_FCOE_CQ]) अणु
		DP_ERR(p_hwfn,
		       "Cannot satisfy CQ amount. CQs requested %d, CQs available %d. Aborting function start\n",
		       fcoe_pf_params->num_cqs,
		       p_hwfn->hw_info.feat_num[QED_FCOE_CQ]);
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	p_data->mtu = cpu_to_le16(fcoe_pf_params->mtu);
	पंचांगp = cpu_to_le16(fcoe_pf_params->sq_num_pbl_pages);
	p_data->sq_num_pages_in_pbl = पंचांगp;

	rc = qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_FCOE, &dummy_cid);
	अगर (rc)
		जाओ err;

	cxt_info.iid = dummy_cid;
	rc = qed_cxt_get_cid_info(p_hwfn, &cxt_info);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Cannot find context info for dummy cid=%d\n",
			  dummy_cid);
		जाओ err;
	पूर्ण
	p_cxt = cxt_info.p_cxt;
	स_रखो(p_cxt, 0, माप(*p_cxt));

	SET_FIELD(p_cxt->tstorm_ag_context.flags3,
		  E4_TSTORM_FCOE_CONN_AG_CTX_DUMMY_TIMER_CF_EN, 1);

	fcoe_pf_params->dummy_icid = (u16)dummy_cid;

	पंचांगp = cpu_to_le16(fcoe_pf_params->num_tasks);
	p_data->func_params.num_tasks = पंचांगp;
	p_data->func_params.log_page_size = fcoe_pf_params->log_page_size;
	p_data->func_params.debug_mode = fcoe_pf_params->debug_mode;

	DMA_REGPAIR_LE(p_data->q_params.glbl_q_params_addr,
		       fcoe_pf_params->glbl_q_params_addr);

	पंचांगp = cpu_to_le16(fcoe_pf_params->cq_num_entries);
	p_data->q_params.cq_num_entries = पंचांगp;

	पंचांगp = cpu_to_le16(fcoe_pf_params->cmdq_num_entries);
	p_data->q_params.cmdq_num_entries = पंचांगp;

	p_data->q_params.num_queues = fcoe_pf_params->num_cqs;

	पंचांगp = (__क्रमce __le16)p_hwfn->hw_info.resc_start[QED_CMDQS_CQS];
	p_data->q_params.queue_relative_offset = (__क्रमce u8)पंचांगp;

	क्रम (i = 0; i < fcoe_pf_params->num_cqs; i++) अणु
		पंचांगp = cpu_to_le16(qed_get_igu_sb_id(p_hwfn, i));
		p_data->q_params.cq_cmdq_sb_num_arr[i] = पंचांगp;
	पूर्ण

	p_data->q_params.cq_sb_pi = fcoe_pf_params->gl_rq_pi;
	p_data->q_params.cmdq_sb_pi = fcoe_pf_params->gl_cmd_pi;

	p_data->q_params.bdq_resource_id = (u8)RESC_START(p_hwfn, QED_BDQ);

	DMA_REGPAIR_LE(p_data->q_params.bdq_pbl_base_address[BDQ_ID_RQ],
		       fcoe_pf_params->bdq_pbl_base_addr[BDQ_ID_RQ]);
	p_data->q_params.bdq_pbl_num_entries[BDQ_ID_RQ] =
	    fcoe_pf_params->bdq_pbl_num_entries[BDQ_ID_RQ];
	पंचांगp = cpu_to_le16(fcoe_pf_params->bdq_xoff_threshold[BDQ_ID_RQ]);
	p_data->q_params.bdq_xoff_threshold[BDQ_ID_RQ] = पंचांगp;
	पंचांगp = cpu_to_le16(fcoe_pf_params->bdq_xon_threshold[BDQ_ID_RQ]);
	p_data->q_params.bdq_xon_threshold[BDQ_ID_RQ] = पंचांगp;

	DMA_REGPAIR_LE(p_data->q_params.bdq_pbl_base_address[BDQ_ID_IMM_DATA],
		       fcoe_pf_params->bdq_pbl_base_addr[BDQ_ID_IMM_DATA]);
	p_data->q_params.bdq_pbl_num_entries[BDQ_ID_IMM_DATA] =
	    fcoe_pf_params->bdq_pbl_num_entries[BDQ_ID_IMM_DATA];
	पंचांगp = cpu_to_le16(fcoe_pf_params->bdq_xoff_threshold[BDQ_ID_IMM_DATA]);
	p_data->q_params.bdq_xoff_threshold[BDQ_ID_IMM_DATA] = पंचांगp;
	पंचांगp = cpu_to_le16(fcoe_pf_params->bdq_xon_threshold[BDQ_ID_IMM_DATA]);
	p_data->q_params.bdq_xon_threshold[BDQ_ID_IMM_DATA] = पंचांगp;
	पंचांगp = cpu_to_le16(fcoe_pf_params->rq_buffer_size);
	p_data->q_params.rq_buffer_size = पंचांगp;

	अगर (fcoe_pf_params->is_target) अणु
		SET_FIELD(p_data->q_params.q_validity,
			  SCSI_INIT_FUNC_QUEUES_RQ_VALID, 1);
		अगर (p_data->q_params.bdq_pbl_num_entries[BDQ_ID_IMM_DATA])
			SET_FIELD(p_data->q_params.q_validity,
				  SCSI_INIT_FUNC_QUEUES_IMM_DATA_VALID, 1);
		SET_FIELD(p_data->q_params.q_validity,
			  SCSI_INIT_FUNC_QUEUES_CMD_VALID, 1);
	पूर्ण अन्यथा अणु
		SET_FIELD(p_data->q_params.q_validity,
			  SCSI_INIT_FUNC_QUEUES_RQ_VALID, 1);
	पूर्ण

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	वापस rc;

err:
	qed_sp_destroy_request(p_hwfn, p_ent);
	वापस rc;
पूर्ण

अटल पूर्णांक
qed_sp_fcoe_conn_offload(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_fcoe_conn *p_conn,
			 क्रमागत spq_mode comp_mode,
			 काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा fcoe_conn_offload_ramrod_params *p_ramrod = शून्य;
	काष्ठा fcoe_conn_offload_ramrod_data *p_data;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u16 physical_q0;
	__le16 पंचांगp;
	पूर्णांक rc;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_OFFLOAD_CONN,
				 PROTOCOLID_FCOE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.fcoe_conn_ofld;
	p_data = &p_ramrod->offload_ramrod_data;

	/* Transmission PQ is the first of the PF */
	physical_q0 = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_conn->physical_q0 = physical_q0;
	p_data->physical_q0 = cpu_to_le16(physical_q0);

	p_data->conn_id = cpu_to_le16(p_conn->conn_id);
	DMA_REGPAIR_LE(p_data->sq_pbl_addr, p_conn->sq_pbl_addr);
	DMA_REGPAIR_LE(p_data->sq_curr_page_addr, p_conn->sq_curr_page_addr);
	DMA_REGPAIR_LE(p_data->sq_next_page_addr, p_conn->sq_next_page_addr);
	DMA_REGPAIR_LE(p_data->xferq_pbl_addr, p_conn->xferq_pbl_addr);
	DMA_REGPAIR_LE(p_data->xferq_curr_page_addr, p_conn->xferq_addr[0]);
	DMA_REGPAIR_LE(p_data->xferq_next_page_addr, p_conn->xferq_addr[1]);

	DMA_REGPAIR_LE(p_data->respq_pbl_addr, p_conn->confq_pbl_addr);
	DMA_REGPAIR_LE(p_data->respq_curr_page_addr, p_conn->confq_addr[0]);
	DMA_REGPAIR_LE(p_data->respq_next_page_addr, p_conn->confq_addr[1]);

	p_data->dst_mac_addr_lo = cpu_to_le16(p_conn->dst_mac_addr_lo);
	p_data->dst_mac_addr_mid = cpu_to_le16(p_conn->dst_mac_addr_mid);
	p_data->dst_mac_addr_hi = cpu_to_le16(p_conn->dst_mac_addr_hi);
	p_data->src_mac_addr_lo = cpu_to_le16(p_conn->src_mac_addr_lo);
	p_data->src_mac_addr_mid = cpu_to_le16(p_conn->src_mac_addr_mid);
	p_data->src_mac_addr_hi = cpu_to_le16(p_conn->src_mac_addr_hi);

	पंचांगp = cpu_to_le16(p_conn->tx_max_fc_pay_len);
	p_data->tx_max_fc_pay_len = पंचांगp;
	पंचांगp = cpu_to_le16(p_conn->e_d_tov_समयr_val);
	p_data->e_d_tov_समयr_val = पंचांगp;
	पंचांगp = cpu_to_le16(p_conn->rec_tov_समयr_val);
	p_data->rec_rr_tov_समयr_val = पंचांगp;
	पंचांगp = cpu_to_le16(p_conn->rx_max_fc_pay_len);
	p_data->rx_max_fc_pay_len = पंचांगp;

	p_data->vlan_tag = cpu_to_le16(p_conn->vlan_tag);
	p_data->s_id.addr_hi = p_conn->s_id.addr_hi;
	p_data->s_id.addr_mid = p_conn->s_id.addr_mid;
	p_data->s_id.addr_lo = p_conn->s_id.addr_lo;
	p_data->max_conc_seqs_c3 = p_conn->max_conc_seqs_c3;
	p_data->d_id.addr_hi = p_conn->d_id.addr_hi;
	p_data->d_id.addr_mid = p_conn->d_id.addr_mid;
	p_data->d_id.addr_lo = p_conn->d_id.addr_lo;
	p_data->flags = p_conn->flags;
	अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
		SET_FIELD(p_data->flags,
			  FCOE_CONN_OFFLOAD_RAMROD_DATA_B_SINGLE_VLAN, 1);
	p_data->def_q_idx = p_conn->def_q_idx;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_sp_fcoe_conn_destroy(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_fcoe_conn *p_conn,
			 क्रमागत spq_mode comp_mode,
			 काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा fcoe_conn_terminate_ramrod_params *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = 0;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_TERMINATE_CONN,
				 PROTOCOLID_FCOE, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.fcoe_conn_terminate;
	DMA_REGPAIR_LE(p_ramrod->terminate_ramrod_data.terminate_params_addr,
		       p_conn->terminate_params);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_sp_fcoe_func_stop(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      क्रमागत spq_mode comp_mode,
		      काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	u32 active_segs = 0;
	पूर्णांक rc = 0;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_hwfn->pf_params.fcoe_pf_params.dummy_icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_DESTROY_FUNC,
				 PROTOCOLID_FCOE, &init_data);
	अगर (rc)
		वापस rc;

	active_segs = qed_rd(p_hwfn, p_ptt, TM_REG_PF_ENABLE_TASK);
	active_segs &= ~BIT(QED_CXT_FCOE_TID_SEG);
	qed_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_TASK, active_segs);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_fcoe_allocate_connection(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_fcoe_conn **p_out_conn)
अणु
	काष्ठा qed_fcoe_conn *p_conn = शून्य;
	व्योम *p_addr;
	u32 i;

	spin_lock_bh(&p_hwfn->p_fcoe_info->lock);
	अगर (!list_empty(&p_hwfn->p_fcoe_info->मुक्त_list))
		p_conn =
		    list_first_entry(&p_hwfn->p_fcoe_info->मुक्त_list,
				     काष्ठा qed_fcoe_conn, list_entry);
	अगर (p_conn) अणु
		list_del(&p_conn->list_entry);
		spin_unlock_bh(&p_hwfn->p_fcoe_info->lock);
		*p_out_conn = p_conn;
		वापस 0;
	पूर्ण
	spin_unlock_bh(&p_hwfn->p_fcoe_info->lock);

	p_conn = kzalloc(माप(*p_conn), GFP_KERNEL);
	अगर (!p_conn)
		वापस -ENOMEM;

	p_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    QED_CHAIN_PAGE_SIZE,
				    &p_conn->xferq_pbl_addr, GFP_KERNEL);
	अगर (!p_addr)
		जाओ nomem_pbl_xferq;
	p_conn->xferq_pbl_addr_virt_addr = p_addr;

	क्रम (i = 0; i < ARRAY_SIZE(p_conn->xferq_addr); i++) अणु
		p_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					    QED_CHAIN_PAGE_SIZE,
					    &p_conn->xferq_addr[i], GFP_KERNEL);
		अगर (!p_addr)
			जाओ nomem_xferq;
		p_conn->xferq_addr_virt_addr[i] = p_addr;

		p_addr = p_conn->xferq_pbl_addr_virt_addr;
		((dma_addr_t *)p_addr)[i] = p_conn->xferq_addr[i];
	पूर्ण

	p_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    QED_CHAIN_PAGE_SIZE,
				    &p_conn->confq_pbl_addr, GFP_KERNEL);
	अगर (!p_addr)
		जाओ nomem_xferq;
	p_conn->confq_pbl_addr_virt_addr = p_addr;

	क्रम (i = 0; i < ARRAY_SIZE(p_conn->confq_addr); i++) अणु
		p_addr = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					    QED_CHAIN_PAGE_SIZE,
					    &p_conn->confq_addr[i], GFP_KERNEL);
		अगर (!p_addr)
			जाओ nomem_confq;
		p_conn->confq_addr_virt_addr[i] = p_addr;

		p_addr = p_conn->confq_pbl_addr_virt_addr;
		((dma_addr_t *)p_addr)[i] = p_conn->confq_addr[i];
	पूर्ण

	p_conn->मुक्त_on_delete = true;
	*p_out_conn = p_conn;
	वापस 0;

nomem_confq:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  QED_CHAIN_PAGE_SIZE,
			  p_conn->confq_pbl_addr_virt_addr,
			  p_conn->confq_pbl_addr);
	क्रम (i = 0; i < ARRAY_SIZE(p_conn->confq_addr); i++)
		अगर (p_conn->confq_addr_virt_addr[i])
			dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
					  QED_CHAIN_PAGE_SIZE,
					  p_conn->confq_addr_virt_addr[i],
					  p_conn->confq_addr[i]);
nomem_xferq:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  QED_CHAIN_PAGE_SIZE,
			  p_conn->xferq_pbl_addr_virt_addr,
			  p_conn->xferq_pbl_addr);
	क्रम (i = 0; i < ARRAY_SIZE(p_conn->xferq_addr); i++)
		अगर (p_conn->xferq_addr_virt_addr[i])
			dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
					  QED_CHAIN_PAGE_SIZE,
					  p_conn->xferq_addr_virt_addr[i],
					  p_conn->xferq_addr[i]);
nomem_pbl_xferq:
	kमुक्त(p_conn);
	वापस -ENOMEM;
पूर्ण

अटल व्योम qed_fcoe_मुक्त_connection(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_fcoe_conn *p_conn)
अणु
	u32 i;

	अगर (!p_conn)
		वापस;

	अगर (p_conn->confq_pbl_addr_virt_addr)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->confq_pbl_addr_virt_addr,
				  p_conn->confq_pbl_addr);

	क्रम (i = 0; i < ARRAY_SIZE(p_conn->confq_addr); i++) अणु
		अगर (!p_conn->confq_addr_virt_addr[i])
			जारी;
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->confq_addr_virt_addr[i],
				  p_conn->confq_addr[i]);
	पूर्ण

	अगर (p_conn->xferq_pbl_addr_virt_addr)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->xferq_pbl_addr_virt_addr,
				  p_conn->xferq_pbl_addr);

	क्रम (i = 0; i < ARRAY_SIZE(p_conn->xferq_addr); i++) अणु
		अगर (!p_conn->xferq_addr_virt_addr[i])
			जारी;
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->xferq_addr_virt_addr[i],
				  p_conn->xferq_addr[i]);
	पूर्ण
	kमुक्त(p_conn);
पूर्ण

अटल व्योम __iomem *qed_fcoe_get_db_addr(काष्ठा qed_hwfn *p_hwfn, u32 cid)
अणु
	वापस (u8 __iomem *)p_hwfn->करोorbells +
	       qed_db_addr(cid, DQ_DEMS_LEGACY);
पूर्ण

अटल व्योम __iomem *qed_fcoe_get_primary_bdq_prod(काष्ठा qed_hwfn *p_hwfn,
						   u8 bdq_id)
अणु
	अगर (RESC_NUM(p_hwfn, QED_BDQ)) अणु
		वापस (u8 __iomem *)p_hwfn->regview +
		       GTT_BAR0_MAP_REG_MSDM_RAM +
		       MSTORM_SCSI_BDQ_EXT_PROD_OFFSET(RESC_START(p_hwfn,
								  QED_BDQ),
						       bdq_id);
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "BDQ is not allocated!\n");
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम __iomem *qed_fcoe_get_secondary_bdq_prod(काष्ठा qed_hwfn *p_hwfn,
						     u8 bdq_id)
अणु
	अगर (RESC_NUM(p_hwfn, QED_BDQ)) अणु
		वापस (u8 __iomem *)p_hwfn->regview +
		       GTT_BAR0_MAP_REG_TSDM_RAM +
		       TSTORM_SCSI_BDQ_EXT_PROD_OFFSET(RESC_START(p_hwfn,
								  QED_BDQ),
						       bdq_id);
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "BDQ is not allocated!\n");
		वापस शून्य;
	पूर्ण
पूर्ण

पूर्णांक qed_fcoe_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_fcoe_info *p_fcoe_info;

	/* Allocate LL2's set काष्ठा */
	p_fcoe_info = kzalloc(माप(*p_fcoe_info), GFP_KERNEL);
	अगर (!p_fcoe_info) अणु
		DP_NOTICE(p_hwfn, "Failed to allocate qed_fcoe_info'\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&p_fcoe_info->मुक्त_list);

	p_hwfn->p_fcoe_info = p_fcoe_info;
	वापस 0;
पूर्ण

व्योम qed_fcoe_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा e4_fcoe_task_context *p_task_ctx = शून्य;
	u32 i, lc;
	पूर्णांक rc;

	spin_lock_init(&p_hwfn->p_fcoe_info->lock);
	क्रम (i = 0; i < p_hwfn->pf_params.fcoe_pf_params.num_tasks; i++) अणु
		rc = qed_cxt_get_task_ctx(p_hwfn, i,
					  QED_CTX_WORKING_MEM,
					  (व्योम **)&p_task_ctx);
		अगर (rc)
			जारी;

		स_रखो(p_task_ctx, 0, माप(काष्ठा e4_fcoe_task_context));

		lc = 0;
		SET_FIELD(lc, TIMERS_CONTEXT_VALIDLC0, 1);
		p_task_ctx->समयr_context.logical_client_0 = cpu_to_le32(lc);

		lc = 0;
		SET_FIELD(lc, TIMERS_CONTEXT_VALIDLC1, 1);
		p_task_ctx->समयr_context.logical_client_1 = cpu_to_le32(lc);

		SET_FIELD(p_task_ctx->tstorm_ag_context.flags0,
			  E4_TSTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE, 1);
	पूर्ण
पूर्ण

व्योम qed_fcoe_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_fcoe_conn *p_conn = शून्य;

	अगर (!p_hwfn->p_fcoe_info)
		वापस;

	जबतक (!list_empty(&p_hwfn->p_fcoe_info->मुक्त_list)) अणु
		p_conn = list_first_entry(&p_hwfn->p_fcoe_info->मुक्त_list,
					  काष्ठा qed_fcoe_conn, list_entry);
		अगर (!p_conn)
			अवरोध;
		list_del(&p_conn->list_entry);
		qed_fcoe_मुक्त_connection(p_hwfn, p_conn);
	पूर्ण

	kमुक्त(p_hwfn->p_fcoe_info);
	p_hwfn->p_fcoe_info = शून्य;
पूर्ण

अटल पूर्णांक
qed_fcoe_acquire_connection(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_fcoe_conn *p_in_conn,
			    काष्ठा qed_fcoe_conn **p_out_conn)
अणु
	काष्ठा qed_fcoe_conn *p_conn = शून्य;
	पूर्णांक rc = 0;
	u32 icid;

	spin_lock_bh(&p_hwfn->p_fcoe_info->lock);
	rc = qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_FCOE, &icid);
	spin_unlock_bh(&p_hwfn->p_fcoe_info->lock);
	अगर (rc)
		वापस rc;

	/* Use input connection [अगर provided] or allocate a new one */
	अगर (p_in_conn) अणु
		p_conn = p_in_conn;
	पूर्ण अन्यथा अणु
		rc = qed_fcoe_allocate_connection(p_hwfn, &p_conn);
		अगर (rc) अणु
			spin_lock_bh(&p_hwfn->p_fcoe_info->lock);
			qed_cxt_release_cid(p_hwfn, icid);
			spin_unlock_bh(&p_hwfn->p_fcoe_info->lock);
			वापस rc;
		पूर्ण
	पूर्ण

	p_conn->icid = icid;
	p_conn->fw_cid = (p_hwfn->hw_info.opaque_fid << 16) | icid;
	*p_out_conn = p_conn;

	वापस rc;
पूर्ण

अटल व्योम qed_fcoe_release_connection(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_fcoe_conn *p_conn)
अणु
	spin_lock_bh(&p_hwfn->p_fcoe_info->lock);
	list_add_tail(&p_conn->list_entry, &p_hwfn->p_fcoe_info->मुक्त_list);
	qed_cxt_release_cid(p_hwfn, p_conn->icid);
	spin_unlock_bh(&p_hwfn->p_fcoe_info->lock);
पूर्ण

अटल व्योम _qed_fcoe_get_tstats(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 काष्ठा qed_fcoe_stats *p_stats)
अणु
	काष्ठा fcoe_rx_stat tstats;
	u32 tstats_addr;

	स_रखो(&tstats, 0, माप(tstats));
	tstats_addr = BAR0_MAP_REG_TSDM_RAM +
	    TSTORM_FCOE_RX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &tstats, tstats_addr, माप(tstats));

	p_stats->fcoe_rx_byte_cnt = HILO_64_REGPAIR(tstats.fcoe_rx_byte_cnt);
	p_stats->fcoe_rx_data_pkt_cnt =
	    HILO_64_REGPAIR(tstats.fcoe_rx_data_pkt_cnt);
	p_stats->fcoe_rx_xfer_pkt_cnt =
	    HILO_64_REGPAIR(tstats.fcoe_rx_xfer_pkt_cnt);
	p_stats->fcoe_rx_other_pkt_cnt =
	    HILO_64_REGPAIR(tstats.fcoe_rx_other_pkt_cnt);

	p_stats->fcoe_silent_drop_pkt_cmdq_full_cnt =
	    le32_to_cpu(tstats.fcoe_silent_drop_pkt_cmdq_full_cnt);
	p_stats->fcoe_silent_drop_pkt_rq_full_cnt =
	    le32_to_cpu(tstats.fcoe_silent_drop_pkt_rq_full_cnt);
	p_stats->fcoe_silent_drop_pkt_crc_error_cnt =
	    le32_to_cpu(tstats.fcoe_silent_drop_pkt_crc_error_cnt);
	p_stats->fcoe_silent_drop_pkt_task_invalid_cnt =
	    le32_to_cpu(tstats.fcoe_silent_drop_pkt_task_invalid_cnt);
	p_stats->fcoe_silent_drop_total_pkt_cnt =
	    le32_to_cpu(tstats.fcoe_silent_drop_total_pkt_cnt);
पूर्ण

अटल व्योम _qed_fcoe_get_pstats(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 काष्ठा qed_fcoe_stats *p_stats)
अणु
	काष्ठा fcoe_tx_stat pstats;
	u32 pstats_addr;

	स_रखो(&pstats, 0, माप(pstats));
	pstats_addr = BAR0_MAP_REG_PSDM_RAM +
	    PSTORM_FCOE_TX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &pstats, pstats_addr, माप(pstats));

	p_stats->fcoe_tx_byte_cnt = HILO_64_REGPAIR(pstats.fcoe_tx_byte_cnt);
	p_stats->fcoe_tx_data_pkt_cnt =
	    HILO_64_REGPAIR(pstats.fcoe_tx_data_pkt_cnt);
	p_stats->fcoe_tx_xfer_pkt_cnt =
	    HILO_64_REGPAIR(pstats.fcoe_tx_xfer_pkt_cnt);
	p_stats->fcoe_tx_other_pkt_cnt =
	    HILO_64_REGPAIR(pstats.fcoe_tx_other_pkt_cnt);
पूर्ण

अटल पूर्णांक qed_fcoe_get_stats(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_fcoe_stats *p_stats)
अणु
	काष्ठा qed_ptt *p_ptt;

	स_रखो(p_stats, 0, माप(*p_stats));

	p_ptt = qed_ptt_acquire(p_hwfn);

	अगर (!p_ptt) अणु
		DP_ERR(p_hwfn, "Failed to acquire ptt\n");
		वापस -EINVAL;
	पूर्ण

	_qed_fcoe_get_tstats(p_hwfn, p_ptt, p_stats);
	_qed_fcoe_get_pstats(p_hwfn, p_ptt, p_stats);

	qed_ptt_release(p_hwfn, p_ptt);

	वापस 0;
पूर्ण

काष्ठा qed_hash_fcoe_con अणु
	काष्ठा hlist_node node;
	काष्ठा qed_fcoe_conn *con;
पूर्ण;

अटल पूर्णांक qed_fill_fcoe_dev_info(काष्ठा qed_dev *cdev,
				  काष्ठा qed_dev_fcoe_info *info)
अणु
	काष्ठा qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);
	पूर्णांक rc;

	स_रखो(info, 0, माप(*info));
	rc = qed_fill_dev_info(cdev, &info->common);

	info->primary_dbq_rq_addr =
	    qed_fcoe_get_primary_bdq_prod(hwfn, BDQ_ID_RQ);
	info->secondary_bdq_rq_addr =
	    qed_fcoe_get_secondary_bdq_prod(hwfn, BDQ_ID_RQ);

	info->wwpn = hwfn->mcp_info->func_info.wwn_port;
	info->wwnn = hwfn->mcp_info->func_info.wwn_node;

	info->num_cqs = FEAT_NUM(hwfn, QED_FCOE_CQ);

	वापस rc;
पूर्ण

अटल व्योम qed_रेजिस्टर_fcoe_ops(काष्ठा qed_dev *cdev,
				  काष्ठा qed_fcoe_cb_ops *ops, व्योम *cookie)
अणु
	cdev->protocol_ops.fcoe = ops;
	cdev->ops_cookie = cookie;
पूर्ण

अटल काष्ठा qed_hash_fcoe_con *qed_fcoe_get_hash(काष्ठा qed_dev *cdev,
						   u32 handle)
अणु
	काष्ठा qed_hash_fcoe_con *hash_con = शून्य;

	अगर (!(cdev->flags & QED_FLAG_STORAGE_STARTED))
		वापस शून्य;

	hash_क्रम_each_possible(cdev->connections, hash_con, node, handle) अणु
		अगर (hash_con->con->icid == handle)
			अवरोध;
	पूर्ण

	अगर (!hash_con || (hash_con->con->icid != handle))
		वापस शून्य;

	वापस hash_con;
पूर्ण

अटल पूर्णांक qed_fcoe_stop(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc;

	अगर (!(cdev->flags & QED_FLAG_STORAGE_STARTED)) अणु
		DP_NOTICE(cdev, "fcoe already stopped\n");
		वापस 0;
	पूर्ण

	अगर (!hash_empty(cdev->connections)) अणु
		DP_NOTICE(cdev,
			  "Can't stop fcoe - not all connections were returned\n");
		वापस -EINVAL;
	पूर्ण

	p_ptt = qed_ptt_acquire(QED_AFFIN_HWFN(cdev));
	अगर (!p_ptt)
		वापस -EAGAIN;

	/* Stop the fcoe */
	rc = qed_sp_fcoe_func_stop(QED_AFFIN_HWFN(cdev), p_ptt,
				   QED_SPQ_MODE_EBLOCK, शून्य);
	cdev->flags &= ~QED_FLAG_STORAGE_STARTED;
	qed_ptt_release(QED_AFFIN_HWFN(cdev), p_ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_fcoe_start(काष्ठा qed_dev *cdev, काष्ठा qed_fcoe_tid *tasks)
अणु
	पूर्णांक rc;

	अगर (cdev->flags & QED_FLAG_STORAGE_STARTED) अणु
		DP_NOTICE(cdev, "fcoe already started;\n");
		वापस 0;
	पूर्ण

	rc = qed_sp_fcoe_func_start(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBLOCK,
				    शून्य);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Failed to start fcoe\n");
		वापस rc;
	पूर्ण

	cdev->flags |= QED_FLAG_STORAGE_STARTED;
	hash_init(cdev->connections);

	अगर (tasks) अणु
		काष्ठा qed_tid_mem *tid_info = kzalloc(माप(*tid_info),
						       GFP_ATOMIC);

		अगर (!tid_info) अणु
			DP_NOTICE(cdev,
				  "Failed to allocate tasks information\n");
			qed_fcoe_stop(cdev);
			वापस -ENOMEM;
		पूर्ण

		rc = qed_cxt_get_tid_mem_info(QED_AFFIN_HWFN(cdev), tid_info);
		अगर (rc) अणु
			DP_NOTICE(cdev, "Failed to gather task information\n");
			qed_fcoe_stop(cdev);
			kमुक्त(tid_info);
			वापस rc;
		पूर्ण

		/* Fill task inक्रमmation */
		tasks->size = tid_info->tid_size;
		tasks->num_tids_per_block = tid_info->num_tids_per_block;
		स_नकल(tasks->blocks, tid_info->blocks,
		       MAX_TID_BLOCKS_FCOE * माप(u8 *));

		kमुक्त(tid_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_fcoe_acquire_conn(काष्ठा qed_dev *cdev,
				 u32 *handle,
				 u32 *fw_cid, व्योम __iomem **p_करोorbell)
अणु
	काष्ठा qed_hash_fcoe_con *hash_con;
	पूर्णांक rc;

	/* Allocate a hashed connection */
	hash_con = kzalloc(माप(*hash_con), GFP_KERNEL);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to allocate hashed connection\n");
		वापस -ENOMEM;
	पूर्ण

	/* Acquire the connection */
	rc = qed_fcoe_acquire_connection(QED_AFFIN_HWFN(cdev), शून्य,
					 &hash_con->con);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Failed to acquire Connection\n");
		kमुक्त(hash_con);
		वापस rc;
	पूर्ण

	/* Added the connection to hash table */
	*handle = hash_con->con->icid;
	*fw_cid = hash_con->con->fw_cid;
	hash_add(cdev->connections, &hash_con->node, *handle);

	अगर (p_करोorbell)
		*p_करोorbell = qed_fcoe_get_db_addr(QED_AFFIN_HWFN(cdev),
						   *handle);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_fcoe_release_conn(काष्ठा qed_dev *cdev, u32 handle)
अणु
	काष्ठा qed_hash_fcoe_con *hash_con;

	hash_con = qed_fcoe_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	hlist_del(&hash_con->node);
	qed_fcoe_release_connection(QED_AFFIN_HWFN(cdev), hash_con->con);
	kमुक्त(hash_con);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_fcoe_offload_conn(काष्ठा qed_dev *cdev,
				 u32 handle,
				 काष्ठा qed_fcoe_params_offload *conn_info)
अणु
	काष्ठा qed_hash_fcoe_con *hash_con;
	काष्ठा qed_fcoe_conn *con;

	hash_con = qed_fcoe_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	/* Update the connection with inक्रमmation from the params */
	con = hash_con->con;

	con->sq_pbl_addr = conn_info->sq_pbl_addr;
	con->sq_curr_page_addr = conn_info->sq_curr_page_addr;
	con->sq_next_page_addr = conn_info->sq_next_page_addr;
	con->tx_max_fc_pay_len = conn_info->tx_max_fc_pay_len;
	con->e_d_tov_समयr_val = conn_info->e_d_tov_समयr_val;
	con->rec_tov_समयr_val = conn_info->rec_tov_समयr_val;
	con->rx_max_fc_pay_len = conn_info->rx_max_fc_pay_len;
	con->vlan_tag = conn_info->vlan_tag;
	con->max_conc_seqs_c3 = conn_info->max_conc_seqs_c3;
	con->flags = conn_info->flags;
	con->def_q_idx = conn_info->def_q_idx;

	con->src_mac_addr_hi = (conn_info->src_mac[5] << 8) |
	    conn_info->src_mac[4];
	con->src_mac_addr_mid = (conn_info->src_mac[3] << 8) |
	    conn_info->src_mac[2];
	con->src_mac_addr_lo = (conn_info->src_mac[1] << 8) |
	    conn_info->src_mac[0];
	con->dst_mac_addr_hi = (conn_info->dst_mac[5] << 8) |
	    conn_info->dst_mac[4];
	con->dst_mac_addr_mid = (conn_info->dst_mac[3] << 8) |
	    conn_info->dst_mac[2];
	con->dst_mac_addr_lo = (conn_info->dst_mac[1] << 8) |
	    conn_info->dst_mac[0];

	con->s_id.addr_hi = conn_info->s_id.addr_hi;
	con->s_id.addr_mid = conn_info->s_id.addr_mid;
	con->s_id.addr_lo = conn_info->s_id.addr_lo;
	con->d_id.addr_hi = conn_info->d_id.addr_hi;
	con->d_id.addr_mid = conn_info->d_id.addr_mid;
	con->d_id.addr_lo = conn_info->d_id.addr_lo;

	वापस qed_sp_fcoe_conn_offload(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

अटल पूर्णांक qed_fcoe_destroy_conn(काष्ठा qed_dev *cdev,
				 u32 handle, dma_addr_t terminate_params)
अणु
	काष्ठा qed_hash_fcoe_con *hash_con;
	काष्ठा qed_fcoe_conn *con;

	hash_con = qed_fcoe_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	/* Update the connection with inक्रमmation from the params */
	con = hash_con->con;
	con->terminate_params = terminate_params;

	वापस qed_sp_fcoe_conn_destroy(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

अटल पूर्णांक qed_fcoe_stats(काष्ठा qed_dev *cdev, काष्ठा qed_fcoe_stats *stats)
अणु
	वापस qed_fcoe_get_stats(QED_AFFIN_HWFN(cdev), stats);
पूर्ण

व्योम qed_get_protocol_stats_fcoe(काष्ठा qed_dev *cdev,
				 काष्ठा qed_mcp_fcoe_stats *stats)
अणु
	काष्ठा qed_fcoe_stats proto_stats;

	/* Retrieve FW statistics */
	स_रखो(&proto_stats, 0, माप(proto_stats));
	अगर (qed_fcoe_stats(cdev, &proto_stats)) अणु
		DP_VERBOSE(cdev, QED_MSG_STORAGE,
			   "Failed to collect FCoE statistics\n");
		वापस;
	पूर्ण

	/* Translate FW statistics पूर्णांकo काष्ठा */
	stats->rx_pkts = proto_stats.fcoe_rx_data_pkt_cnt +
			 proto_stats.fcoe_rx_xfer_pkt_cnt +
			 proto_stats.fcoe_rx_other_pkt_cnt;
	stats->tx_pkts = proto_stats.fcoe_tx_data_pkt_cnt +
			 proto_stats.fcoe_tx_xfer_pkt_cnt +
			 proto_stats.fcoe_tx_other_pkt_cnt;
	stats->fcs_err = proto_stats.fcoe_silent_drop_pkt_crc_error_cnt;

	/* Request protocol driver to fill-in the rest */
	अगर (cdev->protocol_ops.fcoe && cdev->ops_cookie) अणु
		काष्ठा qed_fcoe_cb_ops *ops = cdev->protocol_ops.fcoe;
		व्योम *cookie = cdev->ops_cookie;

		अगर (ops->get_login_failures)
			stats->login_failure = ops->get_login_failures(cookie);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा qed_fcoe_ops qed_fcoe_ops_pass = अणु
	.common = &qed_common_ops_pass,
	.ll2 = &qed_ll2_ops_pass,
	.fill_dev_info = &qed_fill_fcoe_dev_info,
	.start = &qed_fcoe_start,
	.stop = &qed_fcoe_stop,
	.रेजिस्टर_ops = &qed_रेजिस्टर_fcoe_ops,
	.acquire_conn = &qed_fcoe_acquire_conn,
	.release_conn = &qed_fcoe_release_conn,
	.offload_conn = &qed_fcoe_offload_conn,
	.destroy_conn = &qed_fcoe_destroy_conn,
	.get_stats = &qed_fcoe_stats,
पूर्ण;

स्थिर काष्ठा qed_fcoe_ops *qed_get_fcoe_ops(व्योम)
अणु
	वापस &qed_fcoe_ops_pass;
पूर्ण
EXPORT_SYMBOL(qed_get_fcoe_ops);

व्योम qed_put_fcoe_ops(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL(qed_put_fcoe_ops);
