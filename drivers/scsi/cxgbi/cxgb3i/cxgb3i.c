<शैली गुरु>
/*
 * cxgb3i_offload.c: Chelsio S3xx iscsi offloaded tcp connection management
 *
 * Copyright (C) 2003-2015 Chelsio Communications.  All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the LICENSE file included in this
 * release क्रम licensing terms and conditions.
 *
 * Written by:	Dimitris Michailidis (dm@chelsio.com)
 *		Karen Xie (kxie@chelsio.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <scsi/scsi_host.h>

#समावेश "common.h"
#समावेश "t3_cpl.h"
#समावेश "t3cdev.h"
#समावेश "cxgb3_defs.h"
#समावेश "cxgb3_ctl_defs.h"
#समावेश "cxgb3_offload.h"
#समावेश "firmware_exports.h"
#समावेश "cxgb3i.h"

अटल अचिन्हित पूर्णांक dbg_level;
#समावेश "../libcxgbi.h"

#घोषणा DRV_MODULE_NAME         "cxgb3i"
#घोषणा DRV_MODULE_DESC         "Chelsio T3 iSCSI Driver"
#घोषणा DRV_MODULE_VERSION	"2.0.1-ko"
#घोषणा DRV_MODULE_RELDATE	"Apr. 2015"

अटल अक्षर version[] =
	DRV_MODULE_DESC " " DRV_MODULE_NAME
	" v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

MODULE_AUTHOR("Chelsio Communications, Inc.");
MODULE_DESCRIPTION(DRV_MODULE_DESC);
MODULE_VERSION(DRV_MODULE_VERSION);
MODULE_LICENSE("GPL");

module_param(dbg_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(dbg_level, "debug flag (default=0)");

अटल पूर्णांक cxgb3i_rcv_win = 256 * 1024;
module_param(cxgb3i_rcv_win, पूर्णांक, 0644);
MODULE_PARM_DESC(cxgb3i_rcv_win, "TCP receive window in bytes (default=256KB)");

अटल पूर्णांक cxgb3i_snd_win = 128 * 1024;
module_param(cxgb3i_snd_win, पूर्णांक, 0644);
MODULE_PARM_DESC(cxgb3i_snd_win, "TCP send window in bytes (default=128KB)");

अटल पूर्णांक cxgb3i_rx_credit_thres = 10 * 1024;
module_param(cxgb3i_rx_credit_thres, पूर्णांक, 0644);
MODULE_PARM_DESC(cxgb3i_rx_credit_thres,
		 "RX credits return threshold in bytes (default=10KB)");

अटल अचिन्हित पूर्णांक cxgb3i_max_connect = 8 * 1024;
module_param(cxgb3i_max_connect, uपूर्णांक, 0644);
MODULE_PARM_DESC(cxgb3i_max_connect, "Max. # of connections (default=8092)");

अटल अचिन्हित पूर्णांक cxgb3i_sport_base = 20000;
module_param(cxgb3i_sport_base, uपूर्णांक, 0644);
MODULE_PARM_DESC(cxgb3i_sport_base, "starting port number (default=20000)");

अटल व्योम cxgb3i_dev_खोलो(काष्ठा t3cdev *);
अटल व्योम cxgb3i_dev_बंद(काष्ठा t3cdev *);
अटल व्योम cxgb3i_dev_event_handler(काष्ठा t3cdev *, u32, u32);

अटल काष्ठा cxgb3_client t3_client = अणु
	.name = DRV_MODULE_NAME,
	.handlers = cxgb3i_cpl_handlers,
	.add = cxgb3i_dev_खोलो,
	.हटाओ = cxgb3i_dev_बंद,
	.event_handler = cxgb3i_dev_event_handler,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा cxgb3i_host_ढाँचा = अणु
	.module		= THIS_MODULE,
	.name		= DRV_MODULE_NAME,
	.proc_name	= DRV_MODULE_NAME,
	.can_queue	= CXGB3I_SCSI_HOST_QDEPTH,
	.queuecommand	= iscsi_queuecommand,
	.change_queue_depth = scsi_change_queue_depth,
	.sg_tablesize	= SG_ALL,
	.max_sectors	= 0xFFFF,
	.cmd_per_lun	= ISCSI_DEF_CMD_PER_LUN,
	.eh_समयd_out	= iscsi_eh_cmd_समयd_out,
	.eh_पात_handler = iscsi_eh_पात,
	.eh_device_reset_handler = iscsi_eh_device_reset,
	.eh_target_reset_handler = iscsi_eh_recover_target,
	.target_alloc	= iscsi_target_alloc,
	.dma_boundary	= PAGE_SIZE - 1,
	.this_id	= -1,
	.track_queue_depth = 1,
पूर्ण;

अटल काष्ठा iscsi_transport cxgb3i_iscsi_transport = अणु
	.owner		= THIS_MODULE,
	.name		= DRV_MODULE_NAME,
	/* owner and name should be set alपढ़ोy */
	.caps		= CAP_RECOVERY_L0 | CAP_MULTI_R2T | CAP_HDRDGST
				| CAP_DATADGST | CAP_DIGEST_OFFLOAD |
				CAP_PADDING_OFFLOAD | CAP_TEXT_NEGO,
	.attr_is_visible	= cxgbi_attr_is_visible,
	.get_host_param	= cxgbi_get_host_param,
	.set_host_param	= cxgbi_set_host_param,
	/* session management */
	.create_session	= cxgbi_create_session,
	.destroy_session	= cxgbi_destroy_session,
	.get_session_param = iscsi_session_get_param,
	/* connection management */
	.create_conn	= cxgbi_create_conn,
	.bind_conn	= cxgbi_bind_conn,
	.destroy_conn	= iscsi_tcp_conn_tearकरोwn,
	.start_conn	= iscsi_conn_start,
	.stop_conn	= iscsi_conn_stop,
	.get_conn_param	= iscsi_conn_get_param,
	.set_param	= cxgbi_set_conn_param,
	.get_stats	= cxgbi_get_conn_stats,
	/* pdu xmit req from user space */
	.send_pdu	= iscsi_conn_send_pdu,
	/* task */
	.init_task	= iscsi_tcp_task_init,
	.xmit_task	= iscsi_tcp_task_xmit,
	.cleanup_task	= cxgbi_cleanup_task,
	/* pdu */
	.alloc_pdu	= cxgbi_conn_alloc_pdu,
	.init_pdu	= cxgbi_conn_init_pdu,
	.xmit_pdu	= cxgbi_conn_xmit_pdu,
	.parse_pdu_itt	= cxgbi_parse_pdu_itt,
	/* TCP connect/disconnect */
	.get_ep_param	= cxgbi_get_ep_param,
	.ep_connect	= cxgbi_ep_connect,
	.ep_poll	= cxgbi_ep_poll,
	.ep_disconnect	= cxgbi_ep_disconnect,
	/* Error recovery समयout call */
	.session_recovery_समयकरोut = iscsi_session_recovery_समयकरोut,
पूर्ण;

अटल काष्ठा scsi_transport_ढाँचा *cxgb3i_stt;

/*
 * CPL (Chelsio Protocol Language) defines a message passing पूर्णांकerface between
 * the host driver and Chelsio asic.
 * The section below implments CPLs that related to iscsi tcp connection
 * खोलो/बंद/पात and data send/receive.
 */

अटल पूर्णांक push_tx_frames(काष्ठा cxgbi_sock *csk, पूर्णांक req_completion);

अटल व्योम send_act_खोलो_req(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb,
			      स्थिर काष्ठा l2t_entry *e)
अणु
	अचिन्हित पूर्णांक wscale = cxgbi_sock_compute_wscale(csk->rcv_win);
	काष्ठा cpl_act_खोलो_req *req = (काष्ठा cpl_act_खोलो_req *)skb->head;

	skb->priority = CPL_PRIORITY_SETUP;

	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_ACT_OPEN_REQ, csk->atid));
	req->local_port = csk->saddr.sin_port;
	req->peer_port = csk->daddr.sin_port;
	req->local_ip = csk->saddr.sin_addr.s_addr;
	req->peer_ip = csk->daddr.sin_addr.s_addr;

	req->opt0h = htonl(V_KEEP_ALIVE(1) | F_TCAM_BYPASS |
			V_WND_SCALE(wscale) | V_MSS_IDX(csk->mss_idx) |
			V_L2T_IDX(e->idx) | V_TX_CHANNEL(e->smt_idx));
	req->opt0l = htonl(V_ULP_MODE(ULP2_MODE_ISCSI) |
			V_RCV_बफ_मान(csk->rcv_win >> 10));

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u, %pI4:%u-%pI4:%u, %u,%u,%u.\n",
		csk, csk->state, csk->flags, csk->atid,
		&req->local_ip, ntohs(req->local_port),
		&req->peer_ip, ntohs(req->peer_port),
		csk->mss_idx, e->idx, e->smt_idx);

	l2t_send(csk->cdev->lldev, skb, csk->l2t);
पूर्ण

अटल अंतरभूत व्योम act_खोलो_arp_failure(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	cxgbi_sock_act_खोलो_req_arp_failure(शून्य, skb);
पूर्ण

/*
 * CPL connection बंद request: host ->
 *
 * Close a connection by sending a CPL_CLOSE_CON_REQ message and queue it to
 * the ग_लिखो queue (i.e., after any unsent txt data).
 */
अटल व्योम send_बंद_req(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb = csk->cpl_बंद;
	काष्ठा cpl_बंद_con_req *req = (काष्ठा cpl_बंद_con_req *)skb->head;
	अचिन्हित पूर्णांक tid = csk->tid;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	csk->cpl_बंद = शून्य;
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_CLOSE_CON));
	req->wr.wr_lo = htonl(V_WR_TID(tid));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_CLOSE_CON_REQ, tid));
	req->rsvd = htonl(csk->ग_लिखो_seq);

	cxgbi_sock_skb_entail(csk, skb);
	अगर (csk->state >= CTP_ESTABLISHED)
		push_tx_frames(csk, 1);
पूर्ण

/*
 * CPL connection पात request: host ->
 *
 * Send an ABORT_REQ message. Makes sure we करो not send multiple ABORT_REQs
 * क्रम the same connection and also that we करो not try to send a message
 * after the connection has बंदd.
 */
अटल व्योम पात_arp_failure(काष्ठा t3cdev *tdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req *req = cplhdr(skb);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"t3dev 0x%p, tid %u, skb 0x%p.\n",
		tdev, GET_TID(req), skb);
	req->cmd = CPL_ABORT_NO_RST;
	cxgb3_ofld_send(tdev, skb);
पूर्ण

अटल व्योम send_पात_req(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb = csk->cpl_पात_req;
	काष्ठा cpl_पात_req *req;

	अगर (unlikely(csk->state == CTP_ABORTING || !skb))
		वापस;
	cxgbi_sock_set_state(csk, CTP_ABORTING);
	cxgbi_sock_set_flag(csk, CTPF_ABORT_RPL_PENDING);
	/* Purge the send queue so we करोn't send anything after an पात. */
	cxgbi_sock_purge_ग_लिखो_queue(csk);

	csk->cpl_पात_req = शून्य;
	req = (काष्ठा cpl_पात_req *)skb->head;
	skb->priority = CPL_PRIORITY_DATA;
	set_arp_failure_handler(skb, पात_arp_failure);
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_HOST_ABORT_CON_REQ));
	req->wr.wr_lo = htonl(V_WR_TID(csk->tid));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_ABORT_REQ, csk->tid));
	req->rsvd0 = htonl(csk->snd_nxt);
	req->rsvd1 = !cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT);
	req->cmd = CPL_ABORT_SEND_RST;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u, snd_nxt %u, 0x%x.\n",
		csk, csk->state, csk->flags, csk->tid, csk->snd_nxt,
		req->rsvd1);

	l2t_send(csk->cdev->lldev, skb, csk->l2t);
पूर्ण

/*
 * CPL connection पात reply: host ->
 *
 * Send an ABORT_RPL message in response of the ABORT_REQ received.
 */
अटल व्योम send_पात_rpl(काष्ठा cxgbi_sock *csk, पूर्णांक rst_status)
अणु
	काष्ठा sk_buff *skb = csk->cpl_पात_rpl;
	काष्ठा cpl_पात_rpl *rpl = (काष्ठा cpl_पात_rpl *)skb->head;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u, status %d.\n",
		csk, csk->state, csk->flags, csk->tid, rst_status);

	csk->cpl_पात_rpl = शून्य;
	skb->priority = CPL_PRIORITY_DATA;
	rpl->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_HOST_ABORT_CON_RPL));
	rpl->wr.wr_lo = htonl(V_WR_TID(csk->tid));
	OPCODE_TID(rpl) = htonl(MK_OPCODE_TID(CPL_ABORT_RPL, csk->tid));
	rpl->cmd = rst_status;
	cxgb3_ofld_send(csk->cdev->lldev, skb);
पूर्ण

/*
 * CPL connection rx data ack: host ->
 * Send RX credits through an RX_DATA_ACK CPL message. Returns the number of
 * credits sent.
 */
अटल u32 send_rx_credits(काष्ठा cxgbi_sock *csk, u32 credits)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_rx_data_ack *req;
	u32 dack = F_RX_DACK_CHANGE | V_RX_DACK_MODE(1);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, credit %u, dack %u.\n",
		csk, csk->state, csk->flags, csk->tid, credits, dack);

	skb = alloc_wr(माप(*req), 0, GFP_ATOMIC);
	अगर (!skb) अणु
		pr_info("csk 0x%p, credit %u, OOM.\n", csk, credits);
		वापस 0;
	पूर्ण
	req = (काष्ठा cpl_rx_data_ack *)skb->head;
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_RX_DATA_ACK, csk->tid));
	req->credit_dack = htonl(F_RX_DACK_CHANGE | V_RX_DACK_MODE(1) |
				V_RX_CREDITS(credits));
	skb->priority = CPL_PRIORITY_ACK;
	cxgb3_ofld_send(csk->cdev->lldev, skb);
	वापस credits;
पूर्ण

/*
 * CPL connection tx data: host ->
 *
 * Send iscsi PDU via TX_DATA CPL message. Returns the number of
 * credits sent.
 * Each TX_DATA consumes work request credit (wrs), so we need to keep track of
 * how many we've used so far and how many are pending (i.e., yet ack'ed by T3).
 */

अटल अचिन्हित पूर्णांक wrlen __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक skb_wrs[SKB_WR_LIST_SIZE] __पढ़ो_mostly;

अटल व्योम init_wr_tab(अचिन्हित पूर्णांक wr_len)
अणु
	पूर्णांक i;

	अगर (skb_wrs[1])		/* alपढ़ोy initialized */
		वापस;
	क्रम (i = 1; i < SKB_WR_LIST_SIZE; i++) अणु
		पूर्णांक sgl_len = (3 * i) / 2 + (i & 1);

		sgl_len += 3;
		skb_wrs[i] = (sgl_len <= wr_len
			      ? 1 : 1 + (sgl_len - 2) / (wr_len - 1));
	पूर्ण
	wrlen = wr_len * 8;
पूर्ण

अटल अंतरभूत व्योम make_tx_data_wr(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb,
				   पूर्णांक len, पूर्णांक req_completion)
अणु
	काष्ठा tx_data_wr *req;
	काष्ठा l2t_entry *l2t = csk->l2t;

	skb_reset_transport_header(skb);
	req = __skb_push(skb, माप(*req));
	req->wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_TX_DATA) |
			(req_completion ? F_WR_COMPL : 0));
	req->wr_lo = htonl(V_WR_TID(csk->tid));
	/* len includes the length of any HW ULP additions */
	req->len = htonl(len);
	/* V_TX_ULP_SUBMODE sets both the mode and submode */
	req->flags = htonl(V_TX_ULP_SUBMODE(cxgbi_skcb_tx_ulp_mode(skb)) |
			   V_TX_SHOVE((skb_peek(&csk->ग_लिखो_queue) ? 0 : 1)));
	req->sndseq = htonl(csk->snd_nxt);
	req->param = htonl(V_TX_PORT(l2t->smt_idx));

	अगर (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT)) अणु
		req->flags |= htonl(V_TX_ACK_PAGES(2) | F_TX_INIT |
				    V_TX_CPU_IDX(csk->rss_qid));
		/* sendbuffer is in units of 32KB. */
		req->param |= htonl(V_TX_SNDBUF(csk->snd_win >> 15));
		cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
	पूर्ण
पूर्ण

/*
 * push_tx_frames -- start transmit
 *
 * Prepends TX_DATA_WR or CPL_CLOSE_CON_REQ headers to buffers रुकोing in a
 * connection's send queue and sends them on to T3.  Must be called with the
 * connection's lock held.  Returns the amount of send buffer space that was
 * मुक्तd as a result of sending queued data to T3.
 */

अटल व्योम arp_failure_skb_discard(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक push_tx_frames(काष्ठा cxgbi_sock *csk, पूर्णांक req_completion)
अणु
	पूर्णांक total_size = 0;
	काष्ठा sk_buff *skb;

	अगर (unlikely(csk->state < CTP_ESTABLISHED ||
		csk->state == CTP_CLOSE_WAIT_1 || csk->state >= CTP_ABORTING)) अणु
			log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
				"csk 0x%p,%u,0x%lx,%u, in closing state.\n",
				csk, csk->state, csk->flags, csk->tid);
		वापस 0;
	पूर्ण

	जबतक (csk->wr_cred && (skb = skb_peek(&csk->ग_लिखो_queue)) != शून्य) अणु
		पूर्णांक len = skb->len;	/* length beक्रमe skb_push */
		पूर्णांक frags = skb_shinfo(skb)->nr_frags + (len != skb->data_len);
		पूर्णांक wrs_needed = skb_wrs[frags];

		अगर (wrs_needed > 1 && len + माप(काष्ठा tx_data_wr) <= wrlen)
			wrs_needed = 1;

		WARN_ON(frags >= SKB_WR_LIST_SIZE || wrs_needed < 1);

		अगर (csk->wr_cred < wrs_needed) अणु
			log_debug(1 << CXGBI_DBG_PDU_TX,
				"csk 0x%p, skb len %u/%u, frag %u, wr %d<%u.\n",
				csk, skb->len, skb->data_len, frags,
				wrs_needed, csk->wr_cred);
			अवरोध;
		पूर्ण

		__skb_unlink(skb, &csk->ग_लिखो_queue);
		skb->priority = CPL_PRIORITY_DATA;
		skb->csum = wrs_needed;	/* remember this until the WR_ACK */
		csk->wr_cred -= wrs_needed;
		csk->wr_una_cred += wrs_needed;
		cxgbi_sock_enqueue_wr(csk, skb);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, enqueue, skb len %u/%u, frag %u, wr %d, "
			"left %u, unack %u.\n",
			csk, skb->len, skb->data_len, frags, skb->csum,
			csk->wr_cred, csk->wr_una_cred);

		अगर (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_NEED_HDR))) अणु
			अगर ((req_completion &&
				csk->wr_una_cred == wrs_needed) ||
			     csk->wr_una_cred >= csk->wr_max_cred / 2) अणु
				req_completion = 1;
				csk->wr_una_cred = 0;
			पूर्ण
			len += cxgbi_ulp_extra_len(cxgbi_skcb_tx_ulp_mode(skb));
			make_tx_data_wr(csk, skb, len, req_completion);
			csk->snd_nxt += len;
			cxgbi_skcb_clear_flag(skb, SKCBF_TX_NEED_HDR);
		पूर्ण
		total_size += skb->truesize;
		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, tid 0x%x, send skb 0x%p.\n",
			csk, csk->tid, skb);
		set_arp_failure_handler(skb, arp_failure_skb_discard);
		l2t_send(csk->cdev->lldev, skb, csk->l2t);
	पूर्ण
	वापस total_size;
पूर्ण

/*
 * Process a CPL_ACT_ESTABLISH message: -> host
 * Updates connection state from an active establish CPL message.  Runs with
 * the connection lock held.
 */

अटल अंतरभूत व्योम मुक्त_atid(काष्ठा cxgbi_sock *csk)
अणु
	अगर (cxgbi_sock_flag(csk, CTPF_HAS_ATID)) अणु
		cxgb3_मुक्त_atid(csk->cdev->lldev, csk->atid);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_ATID);
		cxgbi_sock_put(csk);
	पूर्ण
पूर्ण

अटल पूर्णांक करो_act_establish(काष्ठा t3cdev *tdev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा cxgbi_sock *csk = ctx;
	काष्ठा cpl_act_establish *req = cplhdr(skb);
	अचिन्हित पूर्णांक tid = GET_TID(req);
	अचिन्हित पूर्णांक atid = G_PASS_OPEN_TID(ntohl(req->tos_tid));
	u32 rcv_isn = ntohl(req->rcv_isn);	/* real RCV_ISN + 1 */

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"atid 0x%x,tid 0x%x, csk 0x%p,%u,0x%lx, isn %u.\n",
		atid, atid, csk, csk->state, csk->flags, rcv_isn);

	cxgbi_sock_get(csk);
	cxgbi_sock_set_flag(csk, CTPF_HAS_TID);
	csk->tid = tid;
	cxgb3_insert_tid(csk->cdev->lldev, &t3_client, csk, tid);

	मुक्त_atid(csk);

	csk->rss_qid = G_QNUM(ntohs(skb->csum));

	spin_lock_bh(&csk->lock);
	अगर (csk->retry_समयr.function) अणु
		del_समयr(&csk->retry_समयr);
		csk->retry_समयr.function = शून्य;
	पूर्ण

	अगर (unlikely(csk->state != CTP_ACTIVE_OPEN))
		pr_info("csk 0x%p,%u,0x%lx,%u, got EST.\n",
			csk, csk->state, csk->flags, csk->tid);

	csk->copied_seq = csk->rcv_wup = csk->rcv_nxt = rcv_isn;
	अगर (csk->rcv_win > (M_RCV_बफ_मान << 10))
		csk->rcv_wup -= csk->rcv_win - (M_RCV_बफ_मान << 10);

	cxgbi_sock_established(csk, ntohl(req->snd_isn), ntohs(req->tcp_opt));

	अगर (unlikely(cxgbi_sock_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED)))
		/* upper layer has requested closing */
		send_पात_req(csk);
	अन्यथा अणु
		अगर (skb_queue_len(&csk->ग_लिखो_queue))
			push_tx_frames(csk, 1);
		cxgbi_conn_tx_खोलो(csk);
	पूर्ण

	spin_unlock_bh(&csk->lock);
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process a CPL_ACT_OPEN_RPL message: -> host
 * Handle active खोलो failures.
 */
अटल पूर्णांक act_खोलो_rpl_status_to_त्रुटि_सं(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल CPL_ERR_CONN_RESET:
		वापस -ECONNREFUSED;
	हाल CPL_ERR_ARP_MISS:
		वापस -EHOSTUNREACH;
	हाल CPL_ERR_CONN_TIMEDOUT:
		वापस -ETIMEDOUT;
	हाल CPL_ERR_TCAM_FULL:
		वापस -ENOMEM;
	हाल CPL_ERR_CONN_EXIST:
		वापस -EADDRINUSE;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम act_खोलो_retry_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा cxgbi_sock *csk = from_समयr(csk, t, retry_समयr);
	काष्ठा sk_buff *skb;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);
	skb = alloc_wr(माप(काष्ठा cpl_act_खोलो_req), 0, GFP_ATOMIC);
	अगर (!skb)
		cxgbi_sock_fail_act_खोलो(csk, -ENOMEM);
	अन्यथा अणु
		skb->sk = (काष्ठा sock *)csk;
		set_arp_failure_handler(skb, act_खोलो_arp_failure);
		send_act_खोलो_req(csk, skb, csk->l2t);
	पूर्ण
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
पूर्ण

अटल पूर्णांक करो_act_खोलो_rpl(काष्ठा t3cdev *tdev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा cxgbi_sock *csk = ctx;
	काष्ठा cpl_act_खोलो_rpl *rpl = cplhdr(skb);

	pr_info("csk 0x%p,%u,0x%lx,%u, status %u, %pI4:%u-%pI4:%u.\n",
		csk, csk->state, csk->flags, csk->atid, rpl->status,
		&csk->saddr.sin_addr.s_addr, ntohs(csk->saddr.sin_port),
		&csk->daddr.sin_addr.s_addr, ntohs(csk->daddr.sin_port));

	अगर (rpl->status != CPL_ERR_TCAM_FULL &&
	    rpl->status != CPL_ERR_CONN_EXIST &&
	    rpl->status != CPL_ERR_ARP_MISS)
		cxgb3_queue_tid_release(tdev, GET_TID(rpl));

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);
	अगर (rpl->status == CPL_ERR_CONN_EXIST &&
	    csk->retry_समयr.function != act_खोलो_retry_समयr) अणु
		csk->retry_समयr.function = act_खोलो_retry_समयr;
		mod_समयr(&csk->retry_समयr, jअगरfies + HZ / 2);
	पूर्ण अन्यथा
		cxgbi_sock_fail_act_खोलो(csk,
				act_खोलो_rpl_status_to_त्रुटि_सं(rpl->status));

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process PEER_CLOSE CPL messages: -> host
 * Handle peer FIN.
 */
अटल पूर्णांक करो_peer_बंद(काष्ठा t3cdev *cdev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा cxgbi_sock *csk = ctx;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	cxgbi_sock_rcv_peer_बंद(csk);
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process CLOSE_CONN_RPL CPL message: -> host
 * Process a peer ACK to our FIN.
 */
अटल पूर्णांक करो_बंद_con_rpl(काष्ठा t3cdev *cdev, काष्ठा sk_buff *skb,
			    व्योम *ctx)
अणु
	काष्ठा cxgbi_sock *csk = ctx;
	काष्ठा cpl_बंद_con_rpl *rpl = cplhdr(skb);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u, snxt %u.\n",
		csk, csk->state, csk->flags, csk->tid, ntohl(rpl->snd_nxt));

	cxgbi_sock_rcv_बंद_conn_rpl(csk, ntohl(rpl->snd_nxt));
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process ABORT_REQ_RSS CPL message: -> host
 * Process पात requests.  If we are रुकोing क्रम an ABORT_RPL we ignore this
 * request except that we need to reply to it.
 */

अटल पूर्णांक पात_status_to_त्रुटि_सं(काष्ठा cxgbi_sock *csk, पूर्णांक पात_reason,
				 पूर्णांक *need_rst)
अणु
	चयन (पात_reason) अणु
	हाल CPL_ERR_BAD_SYN:
	हाल CPL_ERR_CONN_RESET:
		वापस csk->state > CTP_ESTABLISHED ? -EPIPE : -ECONNRESET;
	हाल CPL_ERR_XMIT_TIMEDOUT:
	हाल CPL_ERR_PERSIST_TIMEDOUT:
	हाल CPL_ERR_FINWAIT2_TIMEDOUT:
	हाल CPL_ERR_KEEPALIVE_TIMEDOUT:
		वापस -ETIMEDOUT;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_पात_req(काष्ठा t3cdev *cdev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	स्थिर काष्ठा cpl_पात_req_rss *req = cplhdr(skb);
	काष्ठा cxgbi_sock *csk = ctx;
	पूर्णांक rst_status = CPL_ABORT_NO_RST;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	अगर (req->status == CPL_ERR_RTX_NEG_ADVICE ||
	    req->status == CPL_ERR_PERSIST_NEG_ADVICE) अणु
		जाओ करोne;
	पूर्ण

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	अगर (!cxgbi_sock_flag(csk, CTPF_ABORT_REQ_RCVD)) अणु
		cxgbi_sock_set_flag(csk, CTPF_ABORT_REQ_RCVD);
		cxgbi_sock_set_state(csk, CTP_ABORTING);
		जाओ out;
	पूर्ण

	cxgbi_sock_clear_flag(csk, CTPF_ABORT_REQ_RCVD);
	send_पात_rpl(csk, rst_status);

	अगर (!cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING)) अणु
		csk->err = पात_status_to_त्रुटि_सं(csk, req->status, &rst_status);
		cxgbi_sock_बंदd(csk);
	पूर्ण

out:
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
करोne:
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process ABORT_RPL_RSS CPL message: -> host
 * Process पात replies.  We only process these messages अगर we anticipate
 * them as the coordination between SW and HW in this area is somewhat lacking
 * and someबार we get ABORT_RPLs after we are करोne with the connection that
 * originated the ABORT_REQ.
 */
अटल पूर्णांक करो_पात_rpl(काष्ठा t3cdev *cdev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा cpl_पात_rpl_rss *rpl = cplhdr(skb);
	काष्ठा cxgbi_sock *csk = ctx;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"status 0x%x, csk 0x%p, s %u, 0x%lx.\n",
		rpl->status, csk, csk ? csk->state : 0,
		csk ? csk->flags : 0UL);
	/*
	 * Ignore replies to post-बंद पातs indicating that the पात was
	 * requested too late.  These connections are terminated when we get
	 * PEER_CLOSE or CLOSE_CON_RPL and by the समय the पात_rpl_rss
	 * arrives the TID is either no दीर्घer used or it has been recycled.
	 */
	अगर (rpl->status == CPL_ERR_ABORT_FAILED)
		जाओ rel_skb;
	/*
	 * Someबार we've alपढ़ोy बंदd the connection, e.g., a post-बंद
	 * पात races with ABORT_REQ_RSS, the latter मुक्तs the connection
	 * expecting the ABORT_REQ will fail with CPL_ERR_ABORT_FAILED,
	 * but FW turns the ABORT_REQ पूर्णांकo a regular one and so we get
	 * ABORT_RPL_RSS with status 0 and no connection.
	 */
	अगर (csk)
		cxgbi_sock_rcv_पात_rpl(csk);
rel_skb:
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process RX_ISCSI_HDR CPL message: -> host
 * Handle received PDUs, the payload could be DDP'ed. If not, the payload
 * follow after the bhs.
 */
अटल पूर्णांक करो_iscsi_hdr(काष्ठा t3cdev *t3dev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा cxgbi_sock *csk = ctx;
	काष्ठा cpl_iscsi_hdr *hdr_cpl = cplhdr(skb);
	काष्ठा cpl_iscsi_hdr_norss data_cpl;
	काष्ठा cpl_rx_data_ddp_norss ddp_cpl;
	अचिन्हित पूर्णांक hdr_len, data_len, status;
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, skb 0x%p,%u.\n",
		csk, csk->state, csk->flags, csk->tid, skb, skb->len);

	spin_lock_bh(&csk->lock);

	अगर (unlikely(csk->state >= CTP_PASSIVE_CLOSE)) अणु
		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk 0x%p,%u,0x%lx,%u, bad state.\n",
			csk, csk->state, csk->flags, csk->tid);
		अगर (csk->state != CTP_ABORTING)
			जाओ पात_conn;
		अन्यथा
			जाओ discard;
	पूर्ण

	cxgbi_skcb_tcp_seq(skb) = ntohl(hdr_cpl->seq);
	cxgbi_skcb_flags(skb) = 0;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(काष्ठा cpl_iscsi_hdr));

	len = hdr_len = ntohs(hdr_cpl->len);
	/* msg coalesce is off or not enough data received */
	अगर (skb->len <= hdr_len) अणु
		pr_err("%s: tid %u, CPL_ISCSI_HDR, skb len %u < %u.\n",
			csk->cdev->ports[csk->port_id]->name, csk->tid,
			skb->len, hdr_len);
		जाओ पात_conn;
	पूर्ण
	cxgbi_skcb_set_flag(skb, SKCBF_RX_COALESCED);

	err = skb_copy_bits(skb, skb->len - माप(ddp_cpl), &ddp_cpl,
			    माप(ddp_cpl));
	अगर (err < 0) अणु
		pr_err("%s: tid %u, copy cpl_ddp %u-%zu failed %d.\n",
			csk->cdev->ports[csk->port_id]->name, csk->tid,
			skb->len, माप(ddp_cpl), err);
		जाओ पात_conn;
	पूर्ण

	cxgbi_skcb_set_flag(skb, SKCBF_RX_STATUS);
	cxgbi_skcb_rx_pdulen(skb) = ntohs(ddp_cpl.len);
	cxgbi_skcb_rx_ddigest(skb) = ntohl(ddp_cpl.ulp_crc);
	status = ntohl(ddp_cpl.ddp_status);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p, skb 0x%p,%u, pdulen %u, status 0x%x.\n",
		csk, skb, skb->len, cxgbi_skcb_rx_pdulen(skb), status);

	अगर (status & (1 << CPL_RX_DDP_STATUS_HCRC_SHIFT))
		cxgbi_skcb_set_flag(skb, SKCBF_RX_HCRC_ERR);
	अगर (status & (1 << CPL_RX_DDP_STATUS_DCRC_SHIFT))
		cxgbi_skcb_set_flag(skb, SKCBF_RX_DCRC_ERR);
	अगर (status & (1 << CPL_RX_DDP_STATUS_PAD_SHIFT))
		cxgbi_skcb_set_flag(skb, SKCBF_RX_PAD_ERR);

	अगर (skb->len > (hdr_len + माप(ddp_cpl))) अणु
		err = skb_copy_bits(skb, hdr_len, &data_cpl, माप(data_cpl));
		अगर (err < 0) अणु
			pr_err("%s: tid %u, cp %zu/%u failed %d.\n",
				csk->cdev->ports[csk->port_id]->name,
				csk->tid, माप(data_cpl), skb->len, err);
			जाओ पात_conn;
		पूर्ण
		data_len = ntohs(data_cpl.len);
		log_debug(1 << CXGBI_DBG_DDP | 1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, pdu not ddp'ed %u/%u, status 0x%x.\n",
			skb, data_len, cxgbi_skcb_rx_pdulen(skb), status);
		len += माप(data_cpl) + data_len;
	पूर्ण अन्यथा अगर (status & (1 << CPL_RX_DDP_STATUS_DDP_SHIFT))
		cxgbi_skcb_set_flag(skb, SKCBF_RX_DATA_DDPD);

	csk->rcv_nxt = ntohl(ddp_cpl.seq) + cxgbi_skcb_rx_pdulen(skb);
	__pskb_trim(skb, len);
	__skb_queue_tail(&csk->receive_queue, skb);
	cxgbi_conn_pdu_पढ़ोy(csk);

	spin_unlock_bh(&csk->lock);
	वापस 0;

पात_conn:
	send_पात_req(csk);
discard:
	spin_unlock_bh(&csk->lock);
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Process TX_DATA_ACK CPL messages: -> host
 * Process an acknowledgment of WR completion.  Advance snd_una and send the
 * next batch of work requests from the ग_लिखो queue.
 */
अटल पूर्णांक करो_wr_ack(काष्ठा t3cdev *cdev, काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा cxgbi_sock *csk = ctx;
	काष्ठा cpl_wr_ack *hdr = cplhdr(skb);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, cr %u.\n",
		csk, csk->state, csk->flags, csk->tid, ntohs(hdr->credits));

	cxgbi_sock_rcv_wr_ack(csk, ntohs(hdr->credits), ntohl(hdr->snd_una), 1);
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * क्रम each connection, pre-allocate skbs needed क्रम बंद/पात requests. So
 * that we can service the request right away.
 */
अटल पूर्णांक alloc_cpls(काष्ठा cxgbi_sock *csk)
अणु
	csk->cpl_बंद = alloc_wr(माप(काष्ठा cpl_बंद_con_req), 0,
					GFP_KERNEL);
	अगर (!csk->cpl_बंद)
		वापस -ENOMEM;
	csk->cpl_पात_req = alloc_wr(माप(काष्ठा cpl_पात_req), 0,
					GFP_KERNEL);
	अगर (!csk->cpl_पात_req)
		जाओ मुक्त_cpl_skbs;

	csk->cpl_पात_rpl = alloc_wr(माप(काष्ठा cpl_पात_rpl), 0,
					GFP_KERNEL);
	अगर (!csk->cpl_पात_rpl)
		जाओ मुक्त_cpl_skbs;

	वापस 0;

मुक्त_cpl_skbs:
	cxgbi_sock_मुक्त_cpl_skbs(csk);
	वापस -ENOMEM;
पूर्ण

अटल व्योम l2t_put(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा t3cdev *t3dev = (काष्ठा t3cdev *)csk->cdev->lldev;

	अगर (csk->l2t) अणु
		l2t_release(t3dev, csk->l2t);
		csk->l2t = शून्य;
		cxgbi_sock_put(csk);
	पूर्ण
पूर्ण

/*
 * release_offload_resources - release offload resource
 * Release resources held by an offload connection (TID, L2T entry, etc.)
 */
अटल व्योम release_offload_resources(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा t3cdev *t3dev = (काष्ठा t3cdev *)csk->cdev->lldev;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	csk->rss_qid = 0;
	cxgbi_sock_मुक्त_cpl_skbs(csk);

	अगर (csk->wr_cred != csk->wr_max_cred) अणु
		cxgbi_sock_purge_wr_queue(csk);
		cxgbi_sock_reset_wr_list(csk);
	पूर्ण
	l2t_put(csk);
	अगर (cxgbi_sock_flag(csk, CTPF_HAS_ATID))
		मुक्त_atid(csk);
	अन्यथा अगर (cxgbi_sock_flag(csk, CTPF_HAS_TID)) अणु
		cxgb3_हटाओ_tid(t3dev, (व्योम *)csk, csk->tid);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_TID);
		cxgbi_sock_put(csk);
	पूर्ण
	csk->dst = शून्य;
	csk->cdev = शून्य;
पूर्ण

अटल व्योम update_address(काष्ठा cxgbi_hba *chba)
अणु
	अगर (chba->ipv4addr) अणु
		अगर (chba->vdev &&
		    chba->ipv4addr != cxgb3i_get_निजी_ipv4addr(chba->vdev)) अणु
			cxgb3i_set_निजी_ipv4addr(chba->vdev, chba->ipv4addr);
			cxgb3i_set_निजी_ipv4addr(chba->ndev, 0);
			pr_info("%s set %pI4.\n",
				chba->vdev->name, &chba->ipv4addr);
		पूर्ण अन्यथा अगर (chba->ipv4addr !=
				cxgb3i_get_निजी_ipv4addr(chba->ndev)) अणु
			cxgb3i_set_निजी_ipv4addr(chba->ndev, chba->ipv4addr);
			pr_info("%s set %pI4.\n",
				chba->ndev->name, &chba->ipv4addr);
		पूर्ण
	पूर्ण अन्यथा अगर (cxgb3i_get_निजी_ipv4addr(chba->ndev)) अणु
		अगर (chba->vdev)
			cxgb3i_set_निजी_ipv4addr(chba->vdev, 0);
		cxgb3i_set_निजी_ipv4addr(chba->ndev, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक init_act_खोलो(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा dst_entry *dst = csk->dst;
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा t3cdev *t3dev = (काष्ठा t3cdev *)cdev->lldev;
	काष्ठा net_device *ndev = cdev->ports[csk->port_id];
	काष्ठा cxgbi_hba *chba = cdev->hbas[csk->port_id];
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx.\n", csk, csk->state, csk->flags);

	update_address(chba);
	अगर (chba->ipv4addr)
		csk->saddr.sin_addr.s_addr = chba->ipv4addr;

	csk->rss_qid = 0;
	csk->l2t = t3_l2t_get(t3dev, dst, ndev,
			      &csk->daddr.sin_addr.s_addr);
	अगर (!csk->l2t) अणु
		pr_err("NO l2t available.\n");
		वापस -EINVAL;
	पूर्ण
	cxgbi_sock_get(csk);

	csk->atid = cxgb3_alloc_atid(t3dev, &t3_client, csk);
	अगर (csk->atid < 0) अणु
		pr_err("NO atid available.\n");
		ret = -EINVAL;
		जाओ put_sock;
	पूर्ण
	cxgbi_sock_set_flag(csk, CTPF_HAS_ATID);
	cxgbi_sock_get(csk);

	skb = alloc_wr(माप(काष्ठा cpl_act_खोलो_req), 0, GFP_KERNEL);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ मुक्त_atid;
	पूर्ण
	skb->sk = (काष्ठा sock *)csk;
	set_arp_failure_handler(skb, act_खोलो_arp_failure);
	csk->snd_win = cxgb3i_snd_win;
	csk->rcv_win = cxgb3i_rcv_win;

	csk->wr_max_cred = csk->wr_cred = T3C_DATA(t3dev)->max_wrs - 1;
	csk->wr_una_cred = 0;
	csk->mss_idx = cxgbi_sock_select_mss(csk, dst_mtu(dst));
	cxgbi_sock_reset_wr_list(csk);
	csk->err = 0;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, %pI4:%u-%pI4:%u.\n",
		csk, csk->state, csk->flags,
		&csk->saddr.sin_addr.s_addr, ntohs(csk->saddr.sin_port),
		&csk->daddr.sin_addr.s_addr, ntohs(csk->daddr.sin_port));

	cxgbi_sock_set_state(csk, CTP_ACTIVE_OPEN);
	send_act_खोलो_req(csk, skb, csk->l2t);
	वापस 0;

मुक्त_atid:
	cxgb3_मुक्त_atid(t3dev, csk->atid);
put_sock:
	cxgbi_sock_put(csk);
	l2t_release(t3dev, csk->l2t);
	csk->l2t = शून्य;

	वापस ret;
पूर्ण

cxgb3_cpl_handler_func cxgb3i_cpl_handlers[NUM_CPL_CMDS] = अणु
	[CPL_ACT_ESTABLISH] = करो_act_establish,
	[CPL_ACT_OPEN_RPL] = करो_act_खोलो_rpl,
	[CPL_PEER_CLOSE] = करो_peer_बंद,
	[CPL_ABORT_REQ_RSS] = करो_पात_req,
	[CPL_ABORT_RPL_RSS] = करो_पात_rpl,
	[CPL_CLOSE_CON_RPL] = करो_बंद_con_rpl,
	[CPL_TX_DMA_ACK] = करो_wr_ack,
	[CPL_ISCSI_HDR] = करो_iscsi_hdr,
पूर्ण;

/**
 * cxgb3i_ofld_init - allocate and initialize resources क्रम each adapter found
 * @cdev:	cxgbi adapter
 */
अटल पूर्णांक cxgb3i_ofld_init(काष्ठा cxgbi_device *cdev)
अणु
	काष्ठा t3cdev *t3dev = (काष्ठा t3cdev *)cdev->lldev;
	काष्ठा adap_ports port;
	काष्ठा ofld_page_info rx_page_info;
	अचिन्हित पूर्णांक wr_len;
	पूर्णांक rc;

	अगर (t3dev->ctl(t3dev, GET_WR_LEN, &wr_len) < 0 ||
	    t3dev->ctl(t3dev, GET_PORTS, &port) < 0 ||
	    t3dev->ctl(t3dev, GET_RX_PAGE_INFO, &rx_page_info) < 0) अणु
		pr_warn("t3 0x%p, offload up, ioctl failed.\n", t3dev);
		वापस -EINVAL;
	पूर्ण

	अगर (cxgb3i_max_connect > CXGBI_MAX_CONN)
		cxgb3i_max_connect = CXGBI_MAX_CONN;

	rc = cxgbi_device_porपंचांगap_create(cdev, cxgb3i_sport_base,
					cxgb3i_max_connect);
	अगर (rc < 0)
		वापस rc;

	init_wr_tab(wr_len);
	cdev->csk_release_offload_resources = release_offload_resources;
	cdev->csk_push_tx_frames = push_tx_frames;
	cdev->csk_send_पात_req = send_पात_req;
	cdev->csk_send_बंद_req = send_बंद_req;
	cdev->csk_send_rx_credits = send_rx_credits;
	cdev->csk_alloc_cpls = alloc_cpls;
	cdev->csk_init_act_खोलो = init_act_खोलो;

	pr_info("cdev 0x%p, offload up, added.\n", cdev);
	वापस 0;
पूर्ण

/*
 * functions to program the pagepod in h/w
 */
अटल अंतरभूत व्योम ulp_mem_io_set_hdr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा ulp_mem_io *req = (काष्ठा ulp_mem_io *)skb->head;

	स_रखो(req, 0, माप(*req));

	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_BYPASS));
	req->cmd_lock_addr = htonl(V_ULP_MEMIO_ADDR(addr >> 5) |
				   V_ULPTX_CMD(ULP_MEM_WRITE));
	req->len = htonl(V_ULP_MEMIO_DATA_LEN(IPPOD_SIZE >> 5) |
			 V_ULPTX_NFLITS((IPPOD_SIZE >> 3) + 1));
पूर्ण

अटल काष्ठा cxgbi_ppm *cdev2ppm(काष्ठा cxgbi_device *cdev)
अणु
	वापस ((काष्ठा t3cdev *)cdev->lldev)->ulp_iscsi;
पूर्ण

अटल पूर्णांक ddp_set_map(काष्ठा cxgbi_ppm *ppm, काष्ठा cxgbi_sock *csk,
		       काष्ठा cxgbi_task_tag_info *ttinfo)
अणु
	अचिन्हित पूर्णांक idx = ttinfo->idx;
	अचिन्हित पूर्णांक npods = ttinfo->npods;
	काष्ठा scatterlist *sg = ttinfo->sgl;
	काष्ठा cxgbi_pagepod *ppod;
	काष्ठा ulp_mem_io *req;
	अचिन्हित पूर्णांक sg_off;
	अचिन्हित पूर्णांक pm_addr = (idx << PPOD_SIZE_SHIFT) + ppm->llimit;
	पूर्णांक i;

	क्रम (i = 0; i < npods; i++, idx++, pm_addr += IPPOD_SIZE) अणु
		काष्ठा sk_buff *skb = alloc_wr(माप(काष्ठा ulp_mem_io) +
					       IPPOD_SIZE, 0, GFP_ATOMIC);

		अगर (!skb)
			वापस -ENOMEM;
		ulp_mem_io_set_hdr(skb, pm_addr);
		req = (काष्ठा ulp_mem_io *)skb->head;
		ppod = (काष्ठा cxgbi_pagepod *)(req + 1);
		sg_off = i * PPOD_PAGES_MAX;
		cxgbi_ddp_set_one_ppod(ppod, ttinfo, &sg,
				       &sg_off);
		skb->priority = CPL_PRIORITY_CONTROL;
		cxgb3_ofld_send(ppm->lldev, skb);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ddp_clear_map(काष्ठा cxgbi_device *cdev, काष्ठा cxgbi_ppm *ppm,
			  काष्ठा cxgbi_task_tag_info *ttinfo)
अणु
	अचिन्हित पूर्णांक idx = ttinfo->idx;
	अचिन्हित पूर्णांक pm_addr = (idx << PPOD_SIZE_SHIFT) + ppm->llimit;
	अचिन्हित पूर्णांक npods = ttinfo->npods;
	पूर्णांक i;

	log_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, clear idx %u, npods %u.\n",
		  cdev, idx, npods);

	क्रम (i = 0; i < npods; i++, idx++, pm_addr += IPPOD_SIZE) अणु
		काष्ठा sk_buff *skb = alloc_wr(माप(काष्ठा ulp_mem_io) +
					       IPPOD_SIZE, 0, GFP_ATOMIC);

		अगर (!skb) अणु
			pr_err("cdev 0x%p, clear ddp, %u,%d/%u, skb OOM.\n",
			       cdev, idx, i, npods);
			जारी;
		पूर्ण
		ulp_mem_io_set_hdr(skb, pm_addr);
		skb->priority = CPL_PRIORITY_CONTROL;
		cxgb3_ofld_send(ppm->lldev, skb);
	पूर्ण
पूर्ण

अटल पूर्णांक ddp_setup_conn_pgidx(काष्ठा cxgbi_sock *csk,
				अचिन्हित पूर्णांक tid, पूर्णांक pg_idx)
अणु
	काष्ठा sk_buff *skb = alloc_wr(माप(काष्ठा cpl_set_tcb_field), 0,
					GFP_KERNEL);
	काष्ठा cpl_set_tcb_field *req;
	u64 val = pg_idx < DDP_PGIDX_MAX ? pg_idx : 0;

	log_debug(1 << CXGBI_DBG_DDP,
		"csk 0x%p, tid %u, pg_idx %d.\n", csk, tid, pg_idx);
	अगर (!skb)
		वापस -ENOMEM;

	/* set up ulp submode and page size */
	req = (काष्ठा cpl_set_tcb_field *)skb->head;
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, tid));
	req->reply = V_NO_REPLY(1);
	req->cpu_idx = 0;
	req->word = htons(31);
	req->mask = cpu_to_be64(0xF0000000);
	req->val = cpu_to_be64(val << 28);
	skb->priority = CPL_PRIORITY_CONTROL;

	cxgb3_ofld_send(csk->cdev->lldev, skb);
	वापस 0;
पूर्ण

/**
 * ddp_setup_conn_digest - setup conn. digest setting
 * @csk: cxgb tcp socket
 * @tid: connection id
 * @hcrc: header digest enabled
 * @dcrc: data digest enabled
 * set up the iscsi digest settings क्रम a connection identअगरied by tid
 */
अटल पूर्णांक ddp_setup_conn_digest(काष्ठा cxgbi_sock *csk, अचिन्हित पूर्णांक tid,
				 पूर्णांक hcrc, पूर्णांक dcrc)
अणु
	काष्ठा sk_buff *skb = alloc_wr(माप(काष्ठा cpl_set_tcb_field), 0,
					GFP_KERNEL);
	काष्ठा cpl_set_tcb_field *req;
	u64 val = (hcrc ? 1 : 0) | (dcrc ? 2 : 0);

	log_debug(1 << CXGBI_DBG_DDP,
		"csk 0x%p, tid %u, crc %d,%d.\n", csk, tid, hcrc, dcrc);
	अगर (!skb)
		वापस -ENOMEM;

	/* set up ulp submode and page size */
	req = (काष्ठा cpl_set_tcb_field *)skb->head;
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, tid));
	req->reply = V_NO_REPLY(1);
	req->cpu_idx = 0;
	req->word = htons(31);
	req->mask = cpu_to_be64(0x0F000000);
	req->val = cpu_to_be64(val << 24);
	skb->priority = CPL_PRIORITY_CONTROL;

	cxgb3_ofld_send(csk->cdev->lldev, skb);
	वापस 0;
पूर्ण

/**
 * cxgb3i_ddp_init - initialize the cxgb3 adapter's ddp resource
 * @cdev: cxgb3i adapter
 * initialize the ddp pagepod manager क्रम a given adapter
 */
अटल पूर्णांक cxgb3i_ddp_init(काष्ठा cxgbi_device *cdev)
अणु
	काष्ठा t3cdev *tdev = (काष्ठा t3cdev *)cdev->lldev;
	काष्ठा net_device *ndev = cdev->ports[0];
	काष्ठा cxgbi_tag_क्रमmat tक्रमmat;
	अचिन्हित पूर्णांक ppmax, tagmask = 0;
	काष्ठा ulp_iscsi_info uinfo;
	पूर्णांक i, err;

	err = tdev->ctl(tdev, ULP_ISCSI_GET_PARAMS, &uinfo);
	अगर (err < 0) अणु
		pr_err("%s, failed to get iscsi param %d.\n",
		       ndev->name, err);
		वापस err;
	पूर्ण
	अगर (uinfo.llimit >= uinfo.ulimit) अणु
		pr_warn("T3 %s, iscsi NOT enabled %u ~ %u!\n",
			ndev->name, uinfo.llimit, uinfo.ulimit);
		वापस -EACCES;
	पूर्ण

	ppmax = (uinfo.ulimit - uinfo.llimit + 1) >> PPOD_SIZE_SHIFT;
	tagmask = cxgbi_tagmask_set(ppmax);

	pr_info("T3 %s: 0x%x~0x%x, 0x%x, tagmask 0x%x -> 0x%x.\n",
		ndev->name, uinfo.llimit, uinfo.ulimit, ppmax, uinfo.tagmask,
		tagmask);

	स_रखो(&tक्रमmat, 0, माप(काष्ठा cxgbi_tag_क्रमmat));
	क्रम (i = 0; i < 4; i++)
		tक्रमmat.pgsz_order[i] = uinfo.pgsz_factor[i];
	cxgbi_tagmask_check(tagmask, &tक्रमmat);

	err = cxgbi_ddp_ppm_setup(&tdev->ulp_iscsi, cdev, &tक्रमmat,
				  (uinfo.ulimit - uinfo.llimit + 1),
				  uinfo.llimit, uinfo.llimit, 0, 0, 0);
	अगर (err)
		वापस err;

	अगर (!(cdev->flags & CXGBI_FLAG_DDP_OFF)) अणु
		uinfo.tagmask = tagmask;
		uinfo.ulimit = uinfo.llimit + (ppmax << PPOD_SIZE_SHIFT);

		err = tdev->ctl(tdev, ULP_ISCSI_SET_PARAMS, &uinfo);
		अगर (err < 0) अणु
			pr_err("T3 %s fail to set iscsi param %d.\n",
			       ndev->name, err);
			cdev->flags |= CXGBI_FLAG_DDP_OFF;
		पूर्ण
		err = 0;
	पूर्ण

	cdev->csk_ddp_setup_digest = ddp_setup_conn_digest;
	cdev->csk_ddp_setup_pgidx = ddp_setup_conn_pgidx;
	cdev->csk_ddp_set_map = ddp_set_map;
	cdev->csk_ddp_clear_map = ddp_clear_map;
	cdev->cdev2ppm = cdev2ppm;
	cdev->tx_max_size = min_t(अचिन्हित पूर्णांक, ULP2_MAX_PDU_PAYLOAD,
				  uinfo.max_txsz - ISCSI_PDU_NONPAYLOAD_LEN);
	cdev->rx_max_size = min_t(अचिन्हित पूर्णांक, ULP2_MAX_PDU_PAYLOAD,
				  uinfo.max_rxsz - ISCSI_PDU_NONPAYLOAD_LEN);

	वापस 0;
पूर्ण

अटल व्योम cxgb3i_dev_बंद(काष्ठा t3cdev *t3dev)
अणु
	काष्ठा cxgbi_device *cdev = cxgbi_device_find_by_lldev(t3dev);

	अगर (!cdev || cdev->flags & CXGBI_FLAG_ADAPTER_RESET) अणु
		pr_info("0x%p close, f 0x%x.\n", cdev, cdev ? cdev->flags : 0);
		वापस;
	पूर्ण

	cxgbi_device_unरेजिस्टर(cdev);
पूर्ण

/**
 * cxgb3i_dev_खोलो - init a t3 adapter काष्ठाure and any h/w settings
 * @t3dev: t3cdev adapter
 */
अटल व्योम cxgb3i_dev_खोलो(काष्ठा t3cdev *t3dev)
अणु
	काष्ठा cxgbi_device *cdev = cxgbi_device_find_by_lldev(t3dev);
	काष्ठा adapter *adapter = tdev2adap(t3dev);
	पूर्णांक i, err;

	अगर (cdev) अणु
		pr_info("0x%p, updating.\n", cdev);
		वापस;
	पूर्ण

	cdev = cxgbi_device_रेजिस्टर(0, adapter->params.nports);
	अगर (!cdev) अणु
		pr_warn("device 0x%p register failed.\n", t3dev);
		वापस;
	पूर्ण

	cdev->flags = CXGBI_FLAG_DEV_T3 | CXGBI_FLAG_IPV4_SET;
	cdev->lldev = t3dev;
	cdev->pdev = adapter->pdev;
	cdev->ports = adapter->port;
	cdev->nports = adapter->params.nports;
	cdev->mtus = adapter->params.mtus;
	cdev->nmtus = NMTUS;
	cdev->rx_credit_thres = cxgb3i_rx_credit_thres;
	cdev->skb_tx_rsvd = CXGB3I_TX_HEADER_LEN;
	cdev->skb_rx_extra = माप(काष्ठा cpl_iscsi_hdr_norss);
	cdev->itp = &cxgb3i_iscsi_transport;

	err = cxgb3i_ddp_init(cdev);
	अगर (err) अणु
		pr_info("0x%p ddp init failed %d\n", cdev, err);
		जाओ err_out;
	पूर्ण

	err = cxgb3i_ofld_init(cdev);
	अगर (err) अणु
		pr_info("0x%p offload init failed\n", cdev);
		जाओ err_out;
	पूर्ण

	err = cxgbi_hbas_add(cdev, CXGB3I_MAX_LUN, CXGBI_MAX_CONN,
				&cxgb3i_host_ढाँचा, cxgb3i_stt);
	अगर (err)
		जाओ err_out;

	क्रम (i = 0; i < cdev->nports; i++)
		cdev->hbas[i]->ipv4addr =
			cxgb3i_get_निजी_ipv4addr(cdev->ports[i]);

	pr_info("cdev 0x%p, f 0x%x, t3dev 0x%p open, err %d.\n",
		cdev, cdev ? cdev->flags : 0, t3dev, err);
	वापस;

err_out:
	cxgbi_device_unरेजिस्टर(cdev);
पूर्ण

अटल व्योम cxgb3i_dev_event_handler(काष्ठा t3cdev *t3dev, u32 event, u32 port)
अणु
	काष्ठा cxgbi_device *cdev = cxgbi_device_find_by_lldev(t3dev);

	log_debug(1 << CXGBI_DBG_TOE,
		"0x%p, cdev 0x%p, event 0x%x, port 0x%x.\n",
		t3dev, cdev, event, port);
	अगर (!cdev)
		वापस;

	चयन (event) अणु
	हाल OFFLOAD_STATUS_DOWN:
		cdev->flags |= CXGBI_FLAG_ADAPTER_RESET;
		अवरोध;
	हाल OFFLOAD_STATUS_UP:
		cdev->flags &= ~CXGBI_FLAG_ADAPTER_RESET;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * cxgb3i_init_module - module init entry poपूर्णांक
 *
 * initialize any driver wide global data काष्ठाures and रेजिस्टर itself
 *	with the cxgb3 module
 */
अटल पूर्णांक __init cxgb3i_init_module(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "%s", version);

	rc = cxgbi_iscsi_init(&cxgb3i_iscsi_transport, &cxgb3i_stt);
	अगर (rc < 0)
		वापस rc;

	cxgb3_रेजिस्टर_client(&t3_client);
	वापस 0;
पूर्ण

/**
 * cxgb3i_निकास_module - module cleanup/निकास entry poपूर्णांक
 *
 * go through the driver hba list and क्रम each hba, release any resource held.
 *	and unरेजिस्टरs iscsi transport and the cxgb3 module
 */
अटल व्योम __निकास cxgb3i_निकास_module(व्योम)
अणु
	cxgb3_unरेजिस्टर_client(&t3_client);
	cxgbi_device_unरेजिस्टर_all(CXGBI_FLAG_DEV_T3);
	cxgbi_iscsi_cleanup(&cxgb3i_iscsi_transport, &cxgb3i_stt);
पूर्ण

module_init(cxgb3i_init_module);
module_निकास(cxgb3i_निकास_module);
