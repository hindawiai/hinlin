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
#समावेश <linux/etherdevice.h>
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
#समावेश <linux/qed/qed_iscsi_अगर.h>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_int.h"
#समावेश "qed_iscsi.h"
#समावेश "qed_ll2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश "qed_reg_addr.h"

काष्ठा qed_iscsi_conn अणु
	काष्ठा list_head list_entry;
	bool मुक्त_on_delete;

	u16 conn_id;
	u32 icid;
	u32 fw_cid;

	u8 layer_code;
	u8 offl_flags;
	u8 connect_mode;
	u32 initial_ack;
	dma_addr_t sq_pbl_addr;
	काष्ठा qed_chain r2tq;
	काष्ठा qed_chain xhq;
	काष्ठा qed_chain uhq;

	काष्ठा tcp_upload_params *tcp_upload_params_virt_addr;
	dma_addr_t tcp_upload_params_phys_addr;
	काष्ठा scsi_terminate_extra_params *queue_cnts_virt_addr;
	dma_addr_t queue_cnts_phys_addr;
	dma_addr_t syn_phy_addr;

	u16 syn_ip_payload_length;
	u8 local_mac[6];
	u8 remote_mac[6];
	u16 vlan_id;
	u16 tcp_flags;
	u8 ip_version;
	u32 remote_ip[4];
	u32 local_ip[4];
	u8 ka_max_probe_cnt;
	u8 dup_ack_theshold;
	u32 rcv_next;
	u32 snd_una;
	u32 snd_next;
	u32 snd_max;
	u32 snd_wnd;
	u32 rcv_wnd;
	u32 snd_wl1;
	u32 cwnd;
	u32 ss_thresh;
	u16 srtt;
	u16 rtt_var;
	u32 ts_recent;
	u32 ts_recent_age;
	u32 total_rt;
	u32 ka_समयout_delta;
	u32 rt_समयout_delta;
	u8 dup_ack_cnt;
	u8 snd_wnd_probe_cnt;
	u8 ka_probe_cnt;
	u8 rt_cnt;
	u32 flow_label;
	u32 ka_समयout;
	u32 ka_पूर्णांकerval;
	u32 max_rt_समय;
	u32 initial_rcv_wnd;
	u8 ttl;
	u8 tos_or_tc;
	u16 remote_port;
	u16 local_port;
	u16 mss;
	u8 snd_wnd_scale;
	u8 rcv_wnd_scale;
	u16 da_समयout_value;
	u8 ack_frequency;

	u8 update_flag;
	u8 शेष_cq;
	u32 max_seq_size;
	u32 max_recv_pdu_length;
	u32 max_send_pdu_length;
	u32 first_seq_length;
	u32 exp_stat_sn;
	u32 stat_sn;
	u16 physical_q0;
	u16 physical_q1;
	u8 पातive_dsconnect;
पूर्ण;

अटल पूर्णांक qed_iscsi_async_event(काष्ठा qed_hwfn *p_hwfn, u8 fw_event_code,
				 __le16 echo, जोड़ event_ring_data *data,
				 u8 fw_वापस_code)
अणु
	अगर (p_hwfn->p_iscsi_info->event_cb) अणु
		काष्ठा qed_iscsi_info *p_iscsi = p_hwfn->p_iscsi_info;

		वापस p_iscsi->event_cb(p_iscsi->event_context,
					 fw_event_code, data);
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "iSCSI async completion is not set\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
qed_sp_iscsi_func_start(काष्ठा qed_hwfn *p_hwfn,
			क्रमागत spq_mode comp_mode,
			काष्ठा qed_spq_comp_cb *p_comp_addr,
			व्योम *event_context, iscsi_event_cb_t async_event_cb)
अणु
	काष्ठा iscsi_init_ramrod_params *p_ramrod = शून्य;
	काष्ठा scsi_init_func_queues *p_queue = शून्य;
	काष्ठा qed_iscsi_pf_params *p_params = शून्य;
	काष्ठा iscsi_spe_func_init *p_init = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = 0;
	u32 dval;
	u16 val;
	u8 i;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_INIT_FUNC,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.iscsi_init;
	p_init = &p_ramrod->iscsi_init_spe;
	p_params = &p_hwfn->pf_params.iscsi_pf_params;
	p_queue = &p_init->q_params;

	/* Sanity */
	अगर (p_params->num_queues > p_hwfn->hw_info.feat_num[QED_ISCSI_CQ]) अणु
		DP_ERR(p_hwfn,
		       "Cannot satisfy CQ amount. Queues requested %d, CQs available %d. Aborting function start\n",
		       p_params->num_queues,
		       p_hwfn->hw_info.feat_num[QED_ISCSI_CQ]);
		qed_sp_destroy_request(p_hwfn, p_ent);
		वापस -EINVAL;
	पूर्ण

	val = p_params->half_way_बंद_समयout;
	p_init->half_way_बंद_समयout = cpu_to_le16(val);
	p_init->num_sq_pages_in_ring = p_params->num_sq_pages_in_ring;
	p_init->num_r2tq_pages_in_ring = p_params->num_r2tq_pages_in_ring;
	p_init->num_uhq_pages_in_ring = p_params->num_uhq_pages_in_ring;
	p_init->ll2_rx_queue_id =
	    p_hwfn->hw_info.resc_start[QED_LL2_RAM_QUEUE] +
	    p_params->ll2_ooo_queue_id;

	p_init->func_params.log_page_size = p_params->log_page_size;
	val = p_params->num_tasks;
	p_init->func_params.num_tasks = cpu_to_le16(val);
	p_init->debug_mode.flags = p_params->debug_mode;

	DMA_REGPAIR_LE(p_queue->glbl_q_params_addr,
		       p_params->glbl_q_params_addr);

	val = p_params->cq_num_entries;
	p_queue->cq_num_entries = cpu_to_le16(val);
	val = p_params->cmdq_num_entries;
	p_queue->cmdq_num_entries = cpu_to_le16(val);
	p_queue->num_queues = p_params->num_queues;
	dval = (u8)p_hwfn->hw_info.resc_start[QED_CMDQS_CQS];
	p_queue->queue_relative_offset = (u8)dval;
	p_queue->cq_sb_pi = p_params->gl_rq_pi;
	p_queue->cmdq_sb_pi = p_params->gl_cmd_pi;

	क्रम (i = 0; i < p_params->num_queues; i++) अणु
		val = qed_get_igu_sb_id(p_hwfn, i);
		p_queue->cq_cmdq_sb_num_arr[i] = cpu_to_le16(val);
	पूर्ण

	p_queue->bdq_resource_id = (u8)RESC_START(p_hwfn, QED_BDQ);

	DMA_REGPAIR_LE(p_queue->bdq_pbl_base_address[BDQ_ID_RQ],
		       p_params->bdq_pbl_base_addr[BDQ_ID_RQ]);
	p_queue->bdq_pbl_num_entries[BDQ_ID_RQ] =
	    p_params->bdq_pbl_num_entries[BDQ_ID_RQ];
	val = p_params->bdq_xoff_threshold[BDQ_ID_RQ];
	p_queue->bdq_xoff_threshold[BDQ_ID_RQ] = cpu_to_le16(val);
	val = p_params->bdq_xon_threshold[BDQ_ID_RQ];
	p_queue->bdq_xon_threshold[BDQ_ID_RQ] = cpu_to_le16(val);

	DMA_REGPAIR_LE(p_queue->bdq_pbl_base_address[BDQ_ID_IMM_DATA],
		       p_params->bdq_pbl_base_addr[BDQ_ID_IMM_DATA]);
	p_queue->bdq_pbl_num_entries[BDQ_ID_IMM_DATA] =
	    p_params->bdq_pbl_num_entries[BDQ_ID_IMM_DATA];
	val = p_params->bdq_xoff_threshold[BDQ_ID_IMM_DATA];
	p_queue->bdq_xoff_threshold[BDQ_ID_IMM_DATA] = cpu_to_le16(val);
	val = p_params->bdq_xon_threshold[BDQ_ID_IMM_DATA];
	p_queue->bdq_xon_threshold[BDQ_ID_IMM_DATA] = cpu_to_le16(val);
	val = p_params->rq_buffer_size;
	p_queue->rq_buffer_size = cpu_to_le16(val);
	अगर (p_params->is_target) अणु
		SET_FIELD(p_queue->q_validity,
			  SCSI_INIT_FUNC_QUEUES_RQ_VALID, 1);
		अगर (p_queue->bdq_pbl_num_entries[BDQ_ID_IMM_DATA])
			SET_FIELD(p_queue->q_validity,
				  SCSI_INIT_FUNC_QUEUES_IMM_DATA_VALID, 1);
		SET_FIELD(p_queue->q_validity,
			  SCSI_INIT_FUNC_QUEUES_CMD_VALID, 1);
	पूर्ण अन्यथा अणु
		SET_FIELD(p_queue->q_validity,
			  SCSI_INIT_FUNC_QUEUES_RQ_VALID, 1);
	पूर्ण
	p_ramrod->tcp_init.two_msl_समयr = cpu_to_le32(p_params->two_msl_समयr);
	val = p_params->tx_sws_समयr;
	p_ramrod->tcp_init.tx_sws_समयr = cpu_to_le16(val);
	p_ramrod->tcp_init.max_fin_rt = p_params->max_fin_rt;

	p_hwfn->p_iscsi_info->event_context = event_context;
	p_hwfn->p_iscsi_info->event_cb = async_event_cb;

	qed_spq_रेजिस्टर_async_cb(p_hwfn, PROTOCOLID_ISCSI,
				  qed_iscsi_async_event);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_iscsi_conn_offload(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_iscsi_conn *p_conn,
				     क्रमागत spq_mode comp_mode,
				     काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा iscsi_spe_conn_offload *p_ramrod = शून्य;
	काष्ठा tcp_offload_params_opt2 *p_tcp2 = शून्य;
	काष्ठा tcp_offload_params *p_tcp = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	dma_addr_t r2tq_pbl_addr;
	dma_addr_t xhq_pbl_addr;
	dma_addr_t uhq_pbl_addr;
	u16 physical_q;
	__le16 पंचांगp;
	पूर्णांक rc = 0;
	u32 dval;
	u16 wval;
	u16 *p;
	u8 i;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_OFFLOAD_CONN,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.iscsi_conn_offload;

	/* Transmission PQ is the first of the PF */
	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_conn->physical_q0 = physical_q;
	p_ramrod->iscsi.physical_q0 = cpu_to_le16(physical_q);

	/* iSCSI Pure-ACK PQ */
	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_ACK);
	p_conn->physical_q1 = physical_q;
	p_ramrod->iscsi.physical_q1 = cpu_to_le16(physical_q);

	p_ramrod->conn_id = cpu_to_le16(p_conn->conn_id);

	DMA_REGPAIR_LE(p_ramrod->iscsi.sq_pbl_addr, p_conn->sq_pbl_addr);

	r2tq_pbl_addr = qed_chain_get_pbl_phys(&p_conn->r2tq);
	DMA_REGPAIR_LE(p_ramrod->iscsi.r2tq_pbl_addr, r2tq_pbl_addr);

	xhq_pbl_addr = qed_chain_get_pbl_phys(&p_conn->xhq);
	DMA_REGPAIR_LE(p_ramrod->iscsi.xhq_pbl_addr, xhq_pbl_addr);

	uhq_pbl_addr = qed_chain_get_pbl_phys(&p_conn->uhq);
	DMA_REGPAIR_LE(p_ramrod->iscsi.uhq_pbl_addr, uhq_pbl_addr);

	p_ramrod->iscsi.initial_ack = cpu_to_le32(p_conn->initial_ack);
	p_ramrod->iscsi.flags = p_conn->offl_flags;
	p_ramrod->iscsi.शेष_cq = p_conn->शेष_cq;
	p_ramrod->iscsi.stat_sn = cpu_to_le32(p_conn->stat_sn);

	अगर (!GET_FIELD(p_ramrod->iscsi.flags,
		       ISCSI_CONN_OFFLOAD_PARAMS_TCP_ON_CHIP_1B)) अणु
		p_tcp = &p_ramrod->tcp;

		p = (u16 *)p_conn->local_mac;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p));
		p_tcp->local_mac_addr_hi = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 1));
		p_tcp->local_mac_addr_mid = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 2));
		p_tcp->local_mac_addr_lo = पंचांगp;

		p = (u16 *)p_conn->remote_mac;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p));
		p_tcp->remote_mac_addr_hi = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 1));
		p_tcp->remote_mac_addr_mid = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 2));
		p_tcp->remote_mac_addr_lo = पंचांगp;

		p_tcp->vlan_id = cpu_to_le16(p_conn->vlan_id);

		p_tcp->flags = cpu_to_le16(p_conn->tcp_flags);
		p_tcp->ip_version = p_conn->ip_version;
		क्रम (i = 0; i < 4; i++) अणु
			dval = p_conn->remote_ip[i];
			p_tcp->remote_ip[i] = cpu_to_le32(dval);
			dval = p_conn->local_ip[i];
			p_tcp->local_ip[i] = cpu_to_le32(dval);
		पूर्ण
		p_tcp->ka_max_probe_cnt = p_conn->ka_max_probe_cnt;
		p_tcp->dup_ack_theshold = p_conn->dup_ack_theshold;

		p_tcp->rcv_next = cpu_to_le32(p_conn->rcv_next);
		p_tcp->snd_una = cpu_to_le32(p_conn->snd_una);
		p_tcp->snd_next = cpu_to_le32(p_conn->snd_next);
		p_tcp->snd_max = cpu_to_le32(p_conn->snd_max);
		p_tcp->snd_wnd = cpu_to_le32(p_conn->snd_wnd);
		p_tcp->rcv_wnd = cpu_to_le32(p_conn->rcv_wnd);
		p_tcp->snd_wl1 = cpu_to_le32(p_conn->snd_wl1);
		p_tcp->cwnd = cpu_to_le32(p_conn->cwnd);
		p_tcp->ss_thresh = cpu_to_le32(p_conn->ss_thresh);
		p_tcp->srtt = cpu_to_le16(p_conn->srtt);
		p_tcp->rtt_var = cpu_to_le16(p_conn->rtt_var);
		p_tcp->ts_recent = cpu_to_le32(p_conn->ts_recent);
		p_tcp->ts_recent_age = cpu_to_le32(p_conn->ts_recent_age);
		p_tcp->total_rt = cpu_to_le32(p_conn->total_rt);
		dval = p_conn->ka_समयout_delta;
		p_tcp->ka_समयout_delta = cpu_to_le32(dval);
		dval = p_conn->rt_समयout_delta;
		p_tcp->rt_समयout_delta = cpu_to_le32(dval);
		p_tcp->dup_ack_cnt = p_conn->dup_ack_cnt;
		p_tcp->snd_wnd_probe_cnt = p_conn->snd_wnd_probe_cnt;
		p_tcp->ka_probe_cnt = p_conn->ka_probe_cnt;
		p_tcp->rt_cnt = p_conn->rt_cnt;
		p_tcp->flow_label = cpu_to_le32(p_conn->flow_label);
		p_tcp->ka_समयout = cpu_to_le32(p_conn->ka_समयout);
		p_tcp->ka_पूर्णांकerval = cpu_to_le32(p_conn->ka_पूर्णांकerval);
		p_tcp->max_rt_समय = cpu_to_le32(p_conn->max_rt_समय);
		dval = p_conn->initial_rcv_wnd;
		p_tcp->initial_rcv_wnd = cpu_to_le32(dval);
		p_tcp->ttl = p_conn->ttl;
		p_tcp->tos_or_tc = p_conn->tos_or_tc;
		p_tcp->remote_port = cpu_to_le16(p_conn->remote_port);
		p_tcp->local_port = cpu_to_le16(p_conn->local_port);
		p_tcp->mss = cpu_to_le16(p_conn->mss);
		p_tcp->snd_wnd_scale = p_conn->snd_wnd_scale;
		p_tcp->rcv_wnd_scale = p_conn->rcv_wnd_scale;
		wval = p_conn->da_समयout_value;
		p_tcp->da_समयout_value = cpu_to_le16(wval);
		p_tcp->ack_frequency = p_conn->ack_frequency;
		p_tcp->connect_mode = p_conn->connect_mode;
	पूर्ण अन्यथा अणु
		p_tcp2 =
		    &((काष्ठा iscsi_spe_conn_offload_option2 *)p_ramrod)->tcp;

		p = (u16 *)p_conn->local_mac;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p));
		p_tcp2->local_mac_addr_hi = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 1));
		p_tcp2->local_mac_addr_mid = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 2));
		p_tcp2->local_mac_addr_lo = पंचांगp;

		p = (u16 *)p_conn->remote_mac;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p));
		p_tcp2->remote_mac_addr_hi = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 1));
		p_tcp2->remote_mac_addr_mid = पंचांगp;
		पंचांगp = cpu_to_le16(get_unaligned_be16(p + 2));
		p_tcp2->remote_mac_addr_lo = पंचांगp;

		p_tcp2->vlan_id = cpu_to_le16(p_conn->vlan_id);
		p_tcp2->flags = cpu_to_le16(p_conn->tcp_flags);

		p_tcp2->ip_version = p_conn->ip_version;
		क्रम (i = 0; i < 4; i++) अणु
			dval = p_conn->remote_ip[i];
			p_tcp2->remote_ip[i] = cpu_to_le32(dval);
			dval = p_conn->local_ip[i];
			p_tcp2->local_ip[i] = cpu_to_le32(dval);
		पूर्ण

		p_tcp2->flow_label = cpu_to_le32(p_conn->flow_label);
		p_tcp2->ttl = p_conn->ttl;
		p_tcp2->tos_or_tc = p_conn->tos_or_tc;
		p_tcp2->remote_port = cpu_to_le16(p_conn->remote_port);
		p_tcp2->local_port = cpu_to_le16(p_conn->local_port);
		p_tcp2->mss = cpu_to_le16(p_conn->mss);
		p_tcp2->rcv_wnd_scale = p_conn->rcv_wnd_scale;
		p_tcp2->connect_mode = p_conn->connect_mode;
		wval = p_conn->syn_ip_payload_length;
		p_tcp2->syn_ip_payload_length = cpu_to_le16(wval);
		p_tcp2->syn_phy_addr_lo = DMA_LO_LE(p_conn->syn_phy_addr);
		p_tcp2->syn_phy_addr_hi = DMA_HI_LE(p_conn->syn_phy_addr);
		p_tcp2->cwnd = cpu_to_le32(p_conn->cwnd);
		p_tcp2->ka_max_probe_cnt = p_conn->ka_probe_cnt;
		p_tcp2->ka_समयout = cpu_to_le32(p_conn->ka_समयout);
		p_tcp2->max_rt_समय = cpu_to_le32(p_conn->max_rt_समय);
		p_tcp2->ka_पूर्णांकerval = cpu_to_le32(p_conn->ka_पूर्णांकerval);
	पूर्ण

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_iscsi_conn_update(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_iscsi_conn *p_conn,
				    क्रमागत spq_mode comp_mode,
				    काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा iscsi_conn_update_ramrod_params *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;
	u32 dval;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_UPDATE_CONN,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.iscsi_conn_update;

	p_ramrod->conn_id = cpu_to_le16(p_conn->conn_id);
	p_ramrod->flags = p_conn->update_flag;
	p_ramrod->max_seq_size = cpu_to_le32(p_conn->max_seq_size);
	dval = p_conn->max_recv_pdu_length;
	p_ramrod->max_recv_pdu_length = cpu_to_le32(dval);
	dval = p_conn->max_send_pdu_length;
	p_ramrod->max_send_pdu_length = cpu_to_le32(dval);
	dval = p_conn->first_seq_length;
	p_ramrod->first_seq_length = cpu_to_le32(dval);
	p_ramrod->exp_stat_sn = cpu_to_le32(p_conn->exp_stat_sn);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक
qed_sp_iscsi_mac_update(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_iscsi_conn *p_conn,
			क्रमागत spq_mode comp_mode,
			काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा iscsi_spe_conn_mac_update *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;
	u8 ucval;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_MAC_UPDATE,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.iscsi_conn_mac_update;

	p_ramrod->conn_id = cpu_to_le16(p_conn->conn_id);
	ucval = p_conn->remote_mac[1];
	((u8 *)(&p_ramrod->remote_mac_addr_hi))[0] = ucval;
	ucval = p_conn->remote_mac[0];
	((u8 *)(&p_ramrod->remote_mac_addr_hi))[1] = ucval;
	ucval = p_conn->remote_mac[3];
	((u8 *)(&p_ramrod->remote_mac_addr_mid))[0] = ucval;
	ucval = p_conn->remote_mac[2];
	((u8 *)(&p_ramrod->remote_mac_addr_mid))[1] = ucval;
	ucval = p_conn->remote_mac[5];
	((u8 *)(&p_ramrod->remote_mac_addr_lo))[0] = ucval;
	ucval = p_conn->remote_mac[4];
	((u8 *)(&p_ramrod->remote_mac_addr_lo))[1] = ucval;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_iscsi_conn_terminate(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_iscsi_conn *p_conn,
				       क्रमागत spq_mode comp_mode,
				       काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा iscsi_spe_conn_termination *p_ramrod = शून्य;
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_TERMINATION_CONN,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.iscsi_conn_terminate;

	p_ramrod->conn_id = cpu_to_le16(p_conn->conn_id);
	p_ramrod->पातive = p_conn->पातive_dsconnect;

	DMA_REGPAIR_LE(p_ramrod->query_params_addr,
		       p_conn->tcp_upload_params_phys_addr);
	DMA_REGPAIR_LE(p_ramrod->queue_cnts_addr, p_conn->queue_cnts_phys_addr);

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_iscsi_conn_clear_sq(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_iscsi_conn *p_conn,
				      क्रमागत spq_mode comp_mode,
				      काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = -EINVAL;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_CLEAR_SQ,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_sp_iscsi_func_stop(काष्ठा qed_hwfn *p_hwfn,
				  क्रमागत spq_mode comp_mode,
				  काष्ठा qed_spq_comp_cb *p_comp_addr)
अणु
	काष्ठा qed_spq_entry *p_ent = शून्य;
	काष्ठा qed_sp_init_data init_data;
	पूर्णांक rc = 0;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_DESTROY_FUNC,
				 PROTOCOLID_ISCSI, &init_data);
	अगर (rc)
		वापस rc;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

	qed_spq_unरेजिस्टर_async_cb(p_hwfn, PROTOCOLID_ISCSI);
	वापस rc;
पूर्ण

अटल व्योम __iomem *qed_iscsi_get_db_addr(काष्ठा qed_hwfn *p_hwfn, u32 cid)
अणु
	वापस (u8 __iomem *)p_hwfn->करोorbells +
			     qed_db_addr(cid, DQ_DEMS_LEGACY);
पूर्ण

अटल व्योम __iomem *qed_iscsi_get_primary_bdq_prod(काष्ठा qed_hwfn *p_hwfn,
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

अटल व्योम __iomem *qed_iscsi_get_secondary_bdq_prod(काष्ठा qed_hwfn *p_hwfn,
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

अटल पूर्णांक qed_iscsi_setup_connection(काष्ठा qed_iscsi_conn *p_conn)
अणु
	अगर (!p_conn->queue_cnts_virt_addr)
		जाओ nomem;
	स_रखो(p_conn->queue_cnts_virt_addr, 0,
	       माप(*p_conn->queue_cnts_virt_addr));

	अगर (!p_conn->tcp_upload_params_virt_addr)
		जाओ nomem;
	स_रखो(p_conn->tcp_upload_params_virt_addr, 0,
	       माप(*p_conn->tcp_upload_params_virt_addr));

	अगर (!p_conn->r2tq.p_virt_addr)
		जाओ nomem;
	qed_chain_pbl_zero_mem(&p_conn->r2tq);

	अगर (!p_conn->uhq.p_virt_addr)
		जाओ nomem;
	qed_chain_pbl_zero_mem(&p_conn->uhq);

	अगर (!p_conn->xhq.p_virt_addr)
		जाओ nomem;
	qed_chain_pbl_zero_mem(&p_conn->xhq);

	वापस 0;
nomem:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qed_iscsi_allocate_connection(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_iscsi_conn **p_out_conn)
अणु
	काष्ठा scsi_terminate_extra_params *p_q_cnts = शून्य;
	काष्ठा qed_iscsi_pf_params *p_params = शून्य;
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
	पूर्ण;
	काष्ठा tcp_upload_params *p_tcp = शून्य;
	काष्ठा qed_iscsi_conn *p_conn = शून्य;
	पूर्णांक rc = 0;

	/* Try finding a मुक्त connection that can be used */
	spin_lock_bh(&p_hwfn->p_iscsi_info->lock);
	अगर (!list_empty(&p_hwfn->p_iscsi_info->मुक्त_list))
		p_conn = list_first_entry(&p_hwfn->p_iscsi_info->मुक्त_list,
					  काष्ठा qed_iscsi_conn, list_entry);
	अगर (p_conn) अणु
		list_del(&p_conn->list_entry);
		spin_unlock_bh(&p_hwfn->p_iscsi_info->lock);
		*p_out_conn = p_conn;
		वापस 0;
	पूर्ण
	spin_unlock_bh(&p_hwfn->p_iscsi_info->lock);

	/* Need to allocate a new connection */
	p_params = &p_hwfn->pf_params.iscsi_pf_params;

	p_conn = kzalloc(माप(*p_conn), GFP_KERNEL);
	अगर (!p_conn)
		वापस -ENOMEM;

	p_q_cnts = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				      माप(*p_q_cnts),
				      &p_conn->queue_cnts_phys_addr,
				      GFP_KERNEL);
	अगर (!p_q_cnts)
		जाओ nomem_queue_cnts_param;
	p_conn->queue_cnts_virt_addr = p_q_cnts;

	p_tcp = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				   माप(*p_tcp),
				   &p_conn->tcp_upload_params_phys_addr,
				   GFP_KERNEL);
	अगर (!p_tcp)
		जाओ nomem_upload_param;
	p_conn->tcp_upload_params_virt_addr = p_tcp;

	params.num_elems = p_params->num_r2tq_pages_in_ring *
			   QED_CHAIN_PAGE_SIZE / माप(काष्ठा iscsi_wqe);
	params.elem_size = माप(काष्ठा iscsi_wqe);

	rc = qed_chain_alloc(p_hwfn->cdev, &p_conn->r2tq, &params);
	अगर (rc)
		जाओ nomem_r2tq;

	params.num_elems = p_params->num_uhq_pages_in_ring *
			   QED_CHAIN_PAGE_SIZE / माप(काष्ठा iscsi_uhqe);
	params.elem_size = माप(काष्ठा iscsi_uhqe);

	rc = qed_chain_alloc(p_hwfn->cdev, &p_conn->uhq, &params);
	अगर (rc)
		जाओ nomem_uhq;

	params.elem_size = माप(काष्ठा iscsi_xhqe);

	rc = qed_chain_alloc(p_hwfn->cdev, &p_conn->xhq, &params);
	अगर (rc)
		जाओ nomem;

	p_conn->मुक्त_on_delete = true;
	*p_out_conn = p_conn;
	वापस 0;

nomem:
	qed_chain_मुक्त(p_hwfn->cdev, &p_conn->uhq);
nomem_uhq:
	qed_chain_मुक्त(p_hwfn->cdev, &p_conn->r2tq);
nomem_r2tq:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा tcp_upload_params),
			  p_conn->tcp_upload_params_virt_addr,
			  p_conn->tcp_upload_params_phys_addr);
nomem_upload_param:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा scsi_terminate_extra_params),
			  p_conn->queue_cnts_virt_addr,
			  p_conn->queue_cnts_phys_addr);
nomem_queue_cnts_param:
	kमुक्त(p_conn);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qed_iscsi_acquire_connection(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_iscsi_conn *p_in_conn,
					काष्ठा qed_iscsi_conn **p_out_conn)
अणु
	काष्ठा qed_iscsi_conn *p_conn = शून्य;
	पूर्णांक rc = 0;
	u32 icid;

	spin_lock_bh(&p_hwfn->p_iscsi_info->lock);
	rc = qed_cxt_acquire_cid(p_hwfn, PROTOCOLID_ISCSI, &icid);
	spin_unlock_bh(&p_hwfn->p_iscsi_info->lock);
	अगर (rc)
		वापस rc;

	/* Use input connection or allocate a new one */
	अगर (p_in_conn)
		p_conn = p_in_conn;
	अन्यथा
		rc = qed_iscsi_allocate_connection(p_hwfn, &p_conn);

	अगर (!rc)
		rc = qed_iscsi_setup_connection(p_conn);

	अगर (rc) अणु
		spin_lock_bh(&p_hwfn->p_iscsi_info->lock);
		qed_cxt_release_cid(p_hwfn, icid);
		spin_unlock_bh(&p_hwfn->p_iscsi_info->lock);
		वापस rc;
	पूर्ण

	p_conn->icid = icid;
	p_conn->conn_id = (u16)icid;
	p_conn->fw_cid = (p_hwfn->hw_info.opaque_fid << 16) | icid;

	*p_out_conn = p_conn;

	वापस rc;
पूर्ण

अटल व्योम qed_iscsi_release_connection(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_iscsi_conn *p_conn)
अणु
	spin_lock_bh(&p_hwfn->p_iscsi_info->lock);
	list_add_tail(&p_conn->list_entry, &p_hwfn->p_iscsi_info->मुक्त_list);
	qed_cxt_release_cid(p_hwfn, p_conn->icid);
	spin_unlock_bh(&p_hwfn->p_iscsi_info->lock);
पूर्ण

अटल व्योम qed_iscsi_मुक्त_connection(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_iscsi_conn *p_conn)
अणु
	qed_chain_मुक्त(p_hwfn->cdev, &p_conn->xhq);
	qed_chain_मुक्त(p_hwfn->cdev, &p_conn->uhq);
	qed_chain_मुक्त(p_hwfn->cdev, &p_conn->r2tq);
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा tcp_upload_params),
			  p_conn->tcp_upload_params_virt_addr,
			  p_conn->tcp_upload_params_phys_addr);
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा scsi_terminate_extra_params),
			  p_conn->queue_cnts_virt_addr,
			  p_conn->queue_cnts_phys_addr);
	kमुक्त(p_conn);
पूर्ण

पूर्णांक qed_iscsi_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iscsi_info *p_iscsi_info;

	p_iscsi_info = kzalloc(माप(*p_iscsi_info), GFP_KERNEL);
	अगर (!p_iscsi_info)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&p_iscsi_info->मुक्त_list);

	p_hwfn->p_iscsi_info = p_iscsi_info;
	वापस 0;
पूर्ण

व्योम qed_iscsi_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	spin_lock_init(&p_hwfn->p_iscsi_info->lock);
पूर्ण

व्योम qed_iscsi_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_iscsi_conn *p_conn = शून्य;

	अगर (!p_hwfn->p_iscsi_info)
		वापस;

	जबतक (!list_empty(&p_hwfn->p_iscsi_info->मुक्त_list)) अणु
		p_conn = list_first_entry(&p_hwfn->p_iscsi_info->मुक्त_list,
					  काष्ठा qed_iscsi_conn, list_entry);
		अगर (p_conn) अणु
			list_del(&p_conn->list_entry);
			qed_iscsi_मुक्त_connection(p_hwfn, p_conn);
		पूर्ण
	पूर्ण

	kमुक्त(p_hwfn->p_iscsi_info);
	p_hwfn->p_iscsi_info = शून्य;
पूर्ण

अटल व्योम _qed_iscsi_get_tstats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iscsi_stats *p_stats)
अणु
	काष्ठा tstorm_iscsi_stats_drv tstats;
	u32 tstats_addr;

	स_रखो(&tstats, 0, माप(tstats));
	tstats_addr = BAR0_MAP_REG_TSDM_RAM +
		      TSTORM_ISCSI_RX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &tstats, tstats_addr, माप(tstats));

	p_stats->iscsi_rx_bytes_cnt =
	    HILO_64_REGPAIR(tstats.iscsi_rx_bytes_cnt);
	p_stats->iscsi_rx_packet_cnt =
	    HILO_64_REGPAIR(tstats.iscsi_rx_packet_cnt);
	p_stats->iscsi_rx_new_ooo_isle_events_cnt =
	    HILO_64_REGPAIR(tstats.iscsi_rx_new_ooo_isle_events_cnt);
	p_stats->iscsi_cmdq_threshold_cnt =
	    le32_to_cpu(tstats.iscsi_cmdq_threshold_cnt);
	p_stats->iscsi_rq_threshold_cnt =
	    le32_to_cpu(tstats.iscsi_rq_threshold_cnt);
	p_stats->iscsi_immq_threshold_cnt =
	    le32_to_cpu(tstats.iscsi_immq_threshold_cnt);
पूर्ण

अटल व्योम _qed_iscsi_get_mstats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iscsi_stats *p_stats)
अणु
	काष्ठा mstorm_iscsi_stats_drv mstats;
	u32 mstats_addr;

	स_रखो(&mstats, 0, माप(mstats));
	mstats_addr = BAR0_MAP_REG_MSDM_RAM +
		      MSTORM_ISCSI_RX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &mstats, mstats_addr, माप(mstats));

	p_stats->iscsi_rx_dropped_pdus_task_not_valid =
	    HILO_64_REGPAIR(mstats.iscsi_rx_dropped_pdus_task_not_valid);
पूर्ण

अटल व्योम _qed_iscsi_get_ustats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iscsi_stats *p_stats)
अणु
	काष्ठा ustorm_iscsi_stats_drv ustats;
	u32 ustats_addr;

	स_रखो(&ustats, 0, माप(ustats));
	ustats_addr = BAR0_MAP_REG_USDM_RAM +
		      USTORM_ISCSI_RX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &ustats, ustats_addr, माप(ustats));

	p_stats->iscsi_rx_data_pdu_cnt =
	    HILO_64_REGPAIR(ustats.iscsi_rx_data_pdu_cnt);
	p_stats->iscsi_rx_r2t_pdu_cnt =
	    HILO_64_REGPAIR(ustats.iscsi_rx_r2t_pdu_cnt);
	p_stats->iscsi_rx_total_pdu_cnt =
	    HILO_64_REGPAIR(ustats.iscsi_rx_total_pdu_cnt);
पूर्ण

अटल व्योम _qed_iscsi_get_xstats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iscsi_stats *p_stats)
अणु
	काष्ठा xstorm_iscsi_stats_drv xstats;
	u32 xstats_addr;

	स_रखो(&xstats, 0, माप(xstats));
	xstats_addr = BAR0_MAP_REG_XSDM_RAM +
		      XSTORM_ISCSI_TX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &xstats, xstats_addr, माप(xstats));

	p_stats->iscsi_tx_go_to_slow_start_event_cnt =
	    HILO_64_REGPAIR(xstats.iscsi_tx_go_to_slow_start_event_cnt);
	p_stats->iscsi_tx_fast_retransmit_event_cnt =
	    HILO_64_REGPAIR(xstats.iscsi_tx_fast_retransmit_event_cnt);
पूर्ण

अटल व्योम _qed_iscsi_get_ystats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iscsi_stats *p_stats)
अणु
	काष्ठा ystorm_iscsi_stats_drv ystats;
	u32 ystats_addr;

	स_रखो(&ystats, 0, माप(ystats));
	ystats_addr = BAR0_MAP_REG_YSDM_RAM +
		      YSTORM_ISCSI_TX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &ystats, ystats_addr, माप(ystats));

	p_stats->iscsi_tx_data_pdu_cnt =
	    HILO_64_REGPAIR(ystats.iscsi_tx_data_pdu_cnt);
	p_stats->iscsi_tx_r2t_pdu_cnt =
	    HILO_64_REGPAIR(ystats.iscsi_tx_r2t_pdu_cnt);
	p_stats->iscsi_tx_total_pdu_cnt =
	    HILO_64_REGPAIR(ystats.iscsi_tx_total_pdu_cnt);
पूर्ण

अटल व्योम _qed_iscsi_get_pstats(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_iscsi_stats *p_stats)
अणु
	काष्ठा pstorm_iscsi_stats_drv pstats;
	u32 pstats_addr;

	स_रखो(&pstats, 0, माप(pstats));
	pstats_addr = BAR0_MAP_REG_PSDM_RAM +
		      PSTORM_ISCSI_TX_STATS_OFFSET(p_hwfn->rel_pf_id);
	qed_स_नकल_from(p_hwfn, p_ptt, &pstats, pstats_addr, माप(pstats));

	p_stats->iscsi_tx_bytes_cnt =
	    HILO_64_REGPAIR(pstats.iscsi_tx_bytes_cnt);
	p_stats->iscsi_tx_packet_cnt =
	    HILO_64_REGPAIR(pstats.iscsi_tx_packet_cnt);
पूर्ण

अटल पूर्णांक qed_iscsi_get_stats(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_iscsi_stats *stats)
अणु
	काष्ठा qed_ptt *p_ptt;

	स_रखो(stats, 0, माप(*stats));

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_ERR(p_hwfn, "Failed to acquire ptt\n");
		वापस -EAGAIN;
	पूर्ण

	_qed_iscsi_get_tstats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_mstats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_ustats(p_hwfn, p_ptt, stats);

	_qed_iscsi_get_xstats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_ystats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_pstats(p_hwfn, p_ptt, stats);

	qed_ptt_release(p_hwfn, p_ptt);

	वापस 0;
पूर्ण

काष्ठा qed_hash_iscsi_con अणु
	काष्ठा hlist_node node;
	काष्ठा qed_iscsi_conn *con;
पूर्ण;

अटल पूर्णांक qed_fill_iscsi_dev_info(काष्ठा qed_dev *cdev,
				   काष्ठा qed_dev_iscsi_info *info)
अणु
	काष्ठा qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);

	पूर्णांक rc;

	स_रखो(info, 0, माप(*info));
	rc = qed_fill_dev_info(cdev, &info->common);

	info->primary_dbq_rq_addr =
	    qed_iscsi_get_primary_bdq_prod(hwfn, BDQ_ID_RQ);
	info->secondary_bdq_rq_addr =
	    qed_iscsi_get_secondary_bdq_prod(hwfn, BDQ_ID_RQ);

	info->num_cqs = FEAT_NUM(hwfn, QED_ISCSI_CQ);

	वापस rc;
पूर्ण

अटल व्योम qed_रेजिस्टर_iscsi_ops(काष्ठा qed_dev *cdev,
				   काष्ठा qed_iscsi_cb_ops *ops, व्योम *cookie)
अणु
	cdev->protocol_ops.iscsi = ops;
	cdev->ops_cookie = cookie;
पूर्ण

अटल काष्ठा qed_hash_iscsi_con *qed_iscsi_get_hash(काष्ठा qed_dev *cdev,
						     u32 handle)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con = शून्य;

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

अटल पूर्णांक qed_iscsi_stop(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक rc;

	अगर (!(cdev->flags & QED_FLAG_STORAGE_STARTED)) अणु
		DP_NOTICE(cdev, "iscsi already stopped\n");
		वापस 0;
	पूर्ण

	अगर (!hash_empty(cdev->connections)) अणु
		DP_NOTICE(cdev,
			  "Can't stop iscsi - not all connections were returned\n");
		वापस -EINVAL;
	पूर्ण

	/* Stop the iscsi */
	rc = qed_sp_iscsi_func_stop(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBLOCK,
				    शून्य);
	cdev->flags &= ~QED_FLAG_STORAGE_STARTED;

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iscsi_start(काष्ठा qed_dev *cdev,
			   काष्ठा qed_iscsi_tid *tasks,
			   व्योम *event_context,
			   iscsi_event_cb_t async_event_cb)
अणु
	पूर्णांक rc;
	काष्ठा qed_tid_mem *tid_info;

	अगर (cdev->flags & QED_FLAG_STORAGE_STARTED) अणु
		DP_NOTICE(cdev, "iscsi already started;\n");
		वापस 0;
	पूर्ण

	rc = qed_sp_iscsi_func_start(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBLOCK,
				     शून्य, event_context, async_event_cb);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Failed to start iscsi\n");
		वापस rc;
	पूर्ण

	cdev->flags |= QED_FLAG_STORAGE_STARTED;
	hash_init(cdev->connections);

	अगर (!tasks)
		वापस 0;

	tid_info = kzalloc(माप(*tid_info), GFP_KERNEL);

	अगर (!tid_info) अणु
		qed_iscsi_stop(cdev);
		वापस -ENOMEM;
	पूर्ण

	rc = qed_cxt_get_tid_mem_info(QED_AFFIN_HWFN(cdev), tid_info);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Failed to gather task information\n");
		qed_iscsi_stop(cdev);
		kमुक्त(tid_info);
		वापस rc;
	पूर्ण

	/* Fill task inक्रमmation */
	tasks->size = tid_info->tid_size;
	tasks->num_tids_per_block = tid_info->num_tids_per_block;
	स_नकल(tasks->blocks, tid_info->blocks,
	       MAX_TID_BLOCKS_ISCSI * माप(u8 *));

	kमुक्त(tid_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iscsi_acquire_conn(काष्ठा qed_dev *cdev,
				  u32 *handle,
				  u32 *fw_cid, व्योम __iomem **p_करोorbell)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;
	पूर्णांक rc;

	/* Allocate a hashed connection */
	hash_con = kzalloc(माप(*hash_con), GFP_ATOMIC);
	अगर (!hash_con)
		वापस -ENOMEM;

	/* Acquire the connection */
	rc = qed_iscsi_acquire_connection(QED_AFFIN_HWFN(cdev), शून्य,
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
		*p_करोorbell = qed_iscsi_get_db_addr(QED_AFFIN_HWFN(cdev),
						    *handle);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iscsi_release_conn(काष्ठा qed_dev *cdev, u32 handle)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	hlist_del(&hash_con->node);
	qed_iscsi_release_connection(QED_AFFIN_HWFN(cdev), hash_con->con);
	kमुक्त(hash_con);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_iscsi_offload_conn(काष्ठा qed_dev *cdev,
				  u32 handle,
				  काष्ठा qed_iscsi_params_offload *conn_info)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;
	काष्ठा qed_iscsi_conn *con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	/* Update the connection with inक्रमmation from the params */
	con = hash_con->con;

	ether_addr_copy(con->local_mac, conn_info->src.mac);
	ether_addr_copy(con->remote_mac, conn_info->dst.mac);
	स_नकल(con->local_ip, conn_info->src.ip, माप(con->local_ip));
	स_नकल(con->remote_ip, conn_info->dst.ip, माप(con->remote_ip));
	con->local_port = conn_info->src.port;
	con->remote_port = conn_info->dst.port;

	con->layer_code = conn_info->layer_code;
	con->sq_pbl_addr = conn_info->sq_pbl_addr;
	con->initial_ack = conn_info->initial_ack;
	con->vlan_id = conn_info->vlan_id;
	con->tcp_flags = conn_info->tcp_flags;
	con->ip_version = conn_info->ip_version;
	con->शेष_cq = conn_info->शेष_cq;
	con->ka_max_probe_cnt = conn_info->ka_max_probe_cnt;
	con->dup_ack_theshold = conn_info->dup_ack_theshold;
	con->rcv_next = conn_info->rcv_next;
	con->snd_una = conn_info->snd_una;
	con->snd_next = conn_info->snd_next;
	con->snd_max = conn_info->snd_max;
	con->snd_wnd = conn_info->snd_wnd;
	con->rcv_wnd = conn_info->rcv_wnd;
	con->snd_wl1 = conn_info->snd_wl1;
	con->cwnd = conn_info->cwnd;
	con->ss_thresh = conn_info->ss_thresh;
	con->srtt = conn_info->srtt;
	con->rtt_var = conn_info->rtt_var;
	con->ts_recent = conn_info->ts_recent;
	con->ts_recent_age = conn_info->ts_recent_age;
	con->total_rt = conn_info->total_rt;
	con->ka_समयout_delta = conn_info->ka_समयout_delta;
	con->rt_समयout_delta = conn_info->rt_समयout_delta;
	con->dup_ack_cnt = conn_info->dup_ack_cnt;
	con->snd_wnd_probe_cnt = conn_info->snd_wnd_probe_cnt;
	con->ka_probe_cnt = conn_info->ka_probe_cnt;
	con->rt_cnt = conn_info->rt_cnt;
	con->flow_label = conn_info->flow_label;
	con->ka_समयout = conn_info->ka_समयout;
	con->ka_पूर्णांकerval = conn_info->ka_पूर्णांकerval;
	con->max_rt_समय = conn_info->max_rt_समय;
	con->initial_rcv_wnd = conn_info->initial_rcv_wnd;
	con->ttl = conn_info->ttl;
	con->tos_or_tc = conn_info->tos_or_tc;
	con->remote_port = conn_info->remote_port;
	con->local_port = conn_info->local_port;
	con->mss = conn_info->mss;
	con->snd_wnd_scale = conn_info->snd_wnd_scale;
	con->rcv_wnd_scale = conn_info->rcv_wnd_scale;
	con->da_समयout_value = conn_info->da_समयout_value;
	con->ack_frequency = conn_info->ack_frequency;

	/* Set शेष values on other connection fields */
	con->offl_flags = 0x1;

	वापस qed_sp_iscsi_conn_offload(QED_AFFIN_HWFN(cdev), con,
					 QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

अटल पूर्णांक qed_iscsi_update_conn(काष्ठा qed_dev *cdev,
				 u32 handle,
				 काष्ठा qed_iscsi_params_update *conn_info)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;
	काष्ठा qed_iscsi_conn *con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	/* Update the connection with inक्रमmation from the params */
	con = hash_con->con;
	con->update_flag = conn_info->update_flag;
	con->max_seq_size = conn_info->max_seq_size;
	con->max_recv_pdu_length = conn_info->max_recv_pdu_length;
	con->max_send_pdu_length = conn_info->max_send_pdu_length;
	con->first_seq_length = conn_info->first_seq_length;
	con->exp_stat_sn = conn_info->exp_stat_sn;

	वापस qed_sp_iscsi_conn_update(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

अटल पूर्णांक qed_iscsi_clear_conn_sq(काष्ठा qed_dev *cdev, u32 handle)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	वापस qed_sp_iscsi_conn_clear_sq(QED_AFFIN_HWFN(cdev), hash_con->con,
					  QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

अटल पूर्णांक qed_iscsi_destroy_conn(काष्ठा qed_dev *cdev,
				  u32 handle, u8 abrt_conn)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	hash_con->con->पातive_dsconnect = abrt_conn;

	वापस qed_sp_iscsi_conn_terminate(QED_AFFIN_HWFN(cdev), hash_con->con,
					   QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

अटल पूर्णांक qed_iscsi_stats(काष्ठा qed_dev *cdev, काष्ठा qed_iscsi_stats *stats)
अणु
	वापस qed_iscsi_get_stats(QED_AFFIN_HWFN(cdev), stats);
पूर्ण

अटल पूर्णांक qed_iscsi_change_mac(काष्ठा qed_dev *cdev,
				u32 handle, स्थिर u8 *mac)
अणु
	काष्ठा qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	अगर (!hash_con) अणु
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		वापस -EINVAL;
	पूर्ण

	वापस qed_sp_iscsi_mac_update(QED_AFFIN_HWFN(cdev), hash_con->con,
				       QED_SPQ_MODE_EBLOCK, शून्य);
पूर्ण

व्योम qed_get_protocol_stats_iscsi(काष्ठा qed_dev *cdev,
				  काष्ठा qed_mcp_iscsi_stats *stats)
अणु
	काष्ठा qed_iscsi_stats proto_stats;

	/* Retrieve FW statistics */
	स_रखो(&proto_stats, 0, माप(proto_stats));
	अगर (qed_iscsi_stats(cdev, &proto_stats)) अणु
		DP_VERBOSE(cdev, QED_MSG_STORAGE,
			   "Failed to collect ISCSI statistics\n");
		वापस;
	पूर्ण

	/* Translate FW statistics पूर्णांकo काष्ठा */
	stats->rx_pdus = proto_stats.iscsi_rx_total_pdu_cnt;
	stats->tx_pdus = proto_stats.iscsi_tx_total_pdu_cnt;
	stats->rx_bytes = proto_stats.iscsi_rx_bytes_cnt;
	stats->tx_bytes = proto_stats.iscsi_tx_bytes_cnt;
पूर्ण

अटल स्थिर काष्ठा qed_iscsi_ops qed_iscsi_ops_pass = अणु
	.common = &qed_common_ops_pass,
	.ll2 = &qed_ll2_ops_pass,
	.fill_dev_info = &qed_fill_iscsi_dev_info,
	.रेजिस्टर_ops = &qed_रेजिस्टर_iscsi_ops,
	.start = &qed_iscsi_start,
	.stop = &qed_iscsi_stop,
	.acquire_conn = &qed_iscsi_acquire_conn,
	.release_conn = &qed_iscsi_release_conn,
	.offload_conn = &qed_iscsi_offload_conn,
	.update_conn = &qed_iscsi_update_conn,
	.destroy_conn = &qed_iscsi_destroy_conn,
	.clear_sq = &qed_iscsi_clear_conn_sq,
	.get_stats = &qed_iscsi_stats,
	.change_mac = &qed_iscsi_change_mac,
पूर्ण;

स्थिर काष्ठा qed_iscsi_ops *qed_get_iscsi_ops(व्योम)
अणु
	वापस &qed_iscsi_ops_pass;
पूर्ण
EXPORT_SYMBOL(qed_get_iscsi_ops);

व्योम qed_put_iscsi_ops(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL(qed_put_iscsi_ops);
