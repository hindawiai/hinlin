<शैली गुरु>
/*
 * cxgb4i.c: Chelsio T4 iSCSI driver.
 *
 * Copyright (c) 2010-2015 Chelsio Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by:	Karen Xie (kxie@chelsio.com)
 *		Rakesh Ranjan (rranjan@chelsio.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <scsi/scsi_host.h>
#समावेश <net/tcp.h>
#समावेश <net/dst.h>
#समावेश <linux/netdevice.h>
#समावेश <net/addrconf.h>

#समावेश "t4_regs.h"
#समावेश "t4_msg.h"
#समावेश "cxgb4.h"
#समावेश "cxgb4_uld.h"
#समावेश "t4fw_api.h"
#समावेश "l2t.h"
#समावेश "cxgb4i.h"
#समावेश "clip_tbl.h"

अटल अचिन्हित पूर्णांक dbg_level;

#समावेश "../libcxgbi.h"

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
#समावेश <net/dcbevent.h>
#समावेश "cxgb4_dcb.h"
#पूर्ण_अगर

#घोषणा	DRV_MODULE_NAME		"cxgb4i"
#घोषणा DRV_MODULE_DESC		"Chelsio T4-T6 iSCSI Driver"
#घोषणा	DRV_MODULE_VERSION	"0.9.5-ko"
#घोषणा DRV_MODULE_RELDATE	"Apr. 2015"

अटल अक्षर version[] =
	DRV_MODULE_DESC " " DRV_MODULE_NAME
	" v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

MODULE_AUTHOR("Chelsio Communications, Inc.");
MODULE_DESCRIPTION(DRV_MODULE_DESC);
MODULE_VERSION(DRV_MODULE_VERSION);
MODULE_LICENSE("GPL");

module_param(dbg_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(dbg_level, "Debug flag (default=0)");

#घोषणा CXGB4I_DEFAULT_10G_RCV_WIN (256 * 1024)
अटल पूर्णांक cxgb4i_rcv_win = -1;
module_param(cxgb4i_rcv_win, पूर्णांक, 0644);
MODULE_PARM_DESC(cxgb4i_rcv_win, "TCP receive window in bytes");

#घोषणा CXGB4I_DEFAULT_10G_SND_WIN (128 * 1024)
अटल पूर्णांक cxgb4i_snd_win = -1;
module_param(cxgb4i_snd_win, पूर्णांक, 0644);
MODULE_PARM_DESC(cxgb4i_snd_win, "TCP send window in bytes");

अटल पूर्णांक cxgb4i_rx_credit_thres = 10 * 1024;
module_param(cxgb4i_rx_credit_thres, पूर्णांक, 0644);
MODULE_PARM_DESC(cxgb4i_rx_credit_thres,
		"RX credits return threshold in bytes (default=10KB)");

अटल अचिन्हित पूर्णांक cxgb4i_max_connect = (8 * 1024);
module_param(cxgb4i_max_connect, uपूर्णांक, 0644);
MODULE_PARM_DESC(cxgb4i_max_connect, "Maximum number of connections");

अटल अचिन्हित लघु cxgb4i_sport_base = 20000;
module_param(cxgb4i_sport_base, uलघु, 0644);
MODULE_PARM_DESC(cxgb4i_sport_base, "Starting port number (default 20000)");

प्रकार व्योम (*cxgb4i_cplhandler_func)(काष्ठा cxgbi_device *, काष्ठा sk_buff *);

अटल व्योम *t4_uld_add(स्थिर काष्ठा cxgb4_lld_info *);
अटल पूर्णांक t4_uld_rx_handler(व्योम *, स्थिर __be64 *, स्थिर काष्ठा pkt_gl *);
अटल पूर्णांक t4_uld_state_change(व्योम *, क्रमागत cxgb4_state state);
अटल अंतरभूत पूर्णांक send_tx_flowc_wr(काष्ठा cxgbi_sock *);

अटल स्थिर काष्ठा cxgb4_uld_info cxgb4i_uld_info = अणु
	.name = DRV_MODULE_NAME,
	.nrxq = MAX_ULD_QSETS,
	.ntxq = MAX_ULD_QSETS,
	.rxq_size = 1024,
	.lro = false,
	.add = t4_uld_add,
	.rx_handler = t4_uld_rx_handler,
	.state_change = t4_uld_state_change,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा cxgb4i_host_ढाँचा = अणु
	.module		= THIS_MODULE,
	.name		= DRV_MODULE_NAME,
	.proc_name	= DRV_MODULE_NAME,
	.can_queue	= CXGB4I_SCSI_HOST_QDEPTH,
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

अटल काष्ठा iscsi_transport cxgb4i_iscsi_transport = अणु
	.owner		= THIS_MODULE,
	.name		= DRV_MODULE_NAME,
	.caps		= CAP_RECOVERY_L0 | CAP_MULTI_R2T | CAP_HDRDGST |
				CAP_DATADGST | CAP_DIGEST_OFFLOAD |
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
	.bind_conn		= cxgbi_bind_conn,
	.destroy_conn	= iscsi_tcp_conn_tearकरोwn,
	.start_conn		= iscsi_conn_start,
	.stop_conn		= iscsi_conn_stop,
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

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
अटल पूर्णांक
cxgb4_dcb_change_notअगरy(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

अटल काष्ठा notअगरier_block cxgb4_dcb_change = अणु
	.notअगरier_call = cxgb4_dcb_change_notअगरy,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा scsi_transport_ढाँचा *cxgb4i_stt;

/*
 * CPL (Chelsio Protocol Language) defines a message passing पूर्णांकerface between
 * the host driver and Chelsio asic.
 * The section below implments CPLs that related to iscsi tcp connection
 * खोलो/बंद/पात and data send/receive.
 */

#घोषणा RCV_बफ_मान_MASK		0x3FFU
#घोषणा MAX_IMM_TX_PKT_LEN	256

अटल पूर्णांक push_tx_frames(काष्ठा cxgbi_sock *, पूर्णांक);

/*
 * is_ofld_imm - check whether a packet can be sent as immediate data
 * @skb: the packet
 *
 * Returns true अगर a packet can be sent as an offload WR with immediate
 * data.  We currently use the same limit as क्रम Ethernet packets.
 */
अटल अंतरभूत bool is_ofld_imm(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = skb->len;

	अगर (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_NEED_HDR)))
		len += माप(काष्ठा fw_ofld_tx_data_wr);

	अगर  (likely(cxgbi_skcb_test_flag((काष्ठा sk_buff *)skb, SKCBF_TX_ISO)))
		len += माप(काष्ठा cpl_tx_data_iso);

	वापस (len <= MAX_IMM_OFLD_TX_DATA_WR_LEN);
पूर्ण

अटल व्योम send_act_खोलो_req(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb,
				काष्ठा l2t_entry *e)
अणु
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(csk->cdev);
	पूर्णांक wscale = cxgbi_sock_compute_wscale(csk->mss_idx);
	अचिन्हित दीर्घ दीर्घ opt0;
	अचिन्हित पूर्णांक opt2;
	अचिन्हित पूर्णांक qid_atid = ((अचिन्हित पूर्णांक)csk->atid) |
				 (((अचिन्हित पूर्णांक)csk->rss_qid) << 14);

	opt0 = KEEP_ALIVE_F |
		WND_SCALE_V(wscale) |
		MSS_IDX_V(csk->mss_idx) |
		L2T_IDX_V(((काष्ठा l2t_entry *)csk->l2t)->idx) |
		TX_CHAN_V(csk->tx_chan) |
		SMAC_SEL_V(csk->smac_idx) |
		ULP_MODE_V(ULP_MODE_ISCSI) |
		RCV_बफ_मान_V(csk->rcv_win >> 10);

	opt2 = RX_CHANNEL_V(0) |
		RSS_QUEUE_VALID_F |
		RSS_QUEUE_V(csk->rss_qid);

	अगर (is_t4(lldi->adapter_type)) अणु
		काष्ठा cpl_act_खोलो_req *req =
				(काष्ठा cpl_act_खोलो_req *)skb->head;

		INIT_TP_WR(req, 0);
		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ,
					qid_atid));
		req->local_port = csk->saddr.sin_port;
		req->peer_port = csk->daddr.sin_port;
		req->local_ip = csk->saddr.sin_addr.s_addr;
		req->peer_ip = csk->daddr.sin_addr.s_addr;
		req->opt0 = cpu_to_be64(opt0);
		req->params = cpu_to_be32(cxgb4_select_ntuple(
					csk->cdev->ports[csk->port_id],
					csk->l2t));
		opt2 |= RX_FC_VALID_F;
		req->opt2 = cpu_to_be32(opt2);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk t4 0x%p, %pI4:%u-%pI4:%u, atid %d, qid %u.\n",
			csk, &req->local_ip, ntohs(req->local_port),
			&req->peer_ip, ntohs(req->peer_port),
			csk->atid, csk->rss_qid);
	पूर्ण अन्यथा अगर (is_t5(lldi->adapter_type)) अणु
		काष्ठा cpl_t5_act_खोलो_req *req =
				(काष्ठा cpl_t5_act_खोलो_req *)skb->head;
		u32 isn = (pअक्रमom_u32() & ~7UL) - 1;

		INIT_TP_WR(req, 0);
		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ,
					qid_atid));
		req->local_port = csk->saddr.sin_port;
		req->peer_port = csk->daddr.sin_port;
		req->local_ip = csk->saddr.sin_addr.s_addr;
		req->peer_ip = csk->daddr.sin_addr.s_addr;
		req->opt0 = cpu_to_be64(opt0);
		req->params = cpu_to_be64(FILTER_TUPLE_V(
				cxgb4_select_ntuple(
					csk->cdev->ports[csk->port_id],
					csk->l2t)));
		req->rsvd = cpu_to_be32(isn);
		opt2 |= T5_ISS_VALID;
		opt2 |= T5_OPT_2_VALID_F;

		req->opt2 = cpu_to_be32(opt2);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk t5 0x%p, %pI4:%u-%pI4:%u, atid %d, qid %u.\n",
			csk, &req->local_ip, ntohs(req->local_port),
			&req->peer_ip, ntohs(req->peer_port),
			csk->atid, csk->rss_qid);
	पूर्ण अन्यथा अणु
		काष्ठा cpl_t6_act_खोलो_req *req =
				(काष्ठा cpl_t6_act_खोलो_req *)skb->head;
		u32 isn = (pअक्रमom_u32() & ~7UL) - 1;

		INIT_TP_WR(req, 0);
		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ,
							    qid_atid));
		req->local_port = csk->saddr.sin_port;
		req->peer_port = csk->daddr.sin_port;
		req->local_ip = csk->saddr.sin_addr.s_addr;
		req->peer_ip = csk->daddr.sin_addr.s_addr;
		req->opt0 = cpu_to_be64(opt0);
		req->params = cpu_to_be64(FILTER_TUPLE_V(
				cxgb4_select_ntuple(
					csk->cdev->ports[csk->port_id],
					csk->l2t)));
		req->rsvd = cpu_to_be32(isn);

		opt2 |= T5_ISS_VALID;
		opt2 |= RX_FC_DISABLE_F;
		opt2 |= T5_OPT_2_VALID_F;

		req->opt2 = cpu_to_be32(opt2);
		req->rsvd2 = cpu_to_be32(0);
		req->opt3 = cpu_to_be32(0);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			  "csk t6 0x%p, %pI4:%u-%pI4:%u, atid %d, qid %u.\n",
			  csk, &req->local_ip, ntohs(req->local_port),
			  &req->peer_ip, ntohs(req->peer_port),
			  csk->atid, csk->rss_qid);
	पूर्ण

	set_wr_txq(skb, CPL_PRIORITY_SETUP, csk->port_id);

	pr_info_ipaddr("t%d csk 0x%p,%u,0x%lx,%u, rss_qid %u.\n",
		       (&csk->saddr), (&csk->daddr),
		       CHELSIO_CHIP_VERSION(lldi->adapter_type), csk,
		       csk->state, csk->flags, csk->atid, csk->rss_qid);

	cxgb4_l2t_send(csk->cdev->ports[csk->port_id], skb, csk->l2t);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम send_act_खोलो_req6(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb,
			       काष्ठा l2t_entry *e)
अणु
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(csk->cdev);
	पूर्णांक wscale = cxgbi_sock_compute_wscale(csk->mss_idx);
	अचिन्हित दीर्घ दीर्घ opt0;
	अचिन्हित पूर्णांक opt2;
	अचिन्हित पूर्णांक qid_atid = ((अचिन्हित पूर्णांक)csk->atid) |
				 (((अचिन्हित पूर्णांक)csk->rss_qid) << 14);

	opt0 = KEEP_ALIVE_F |
		WND_SCALE_V(wscale) |
		MSS_IDX_V(csk->mss_idx) |
		L2T_IDX_V(((काष्ठा l2t_entry *)csk->l2t)->idx) |
		TX_CHAN_V(csk->tx_chan) |
		SMAC_SEL_V(csk->smac_idx) |
		ULP_MODE_V(ULP_MODE_ISCSI) |
		RCV_बफ_मान_V(csk->rcv_win >> 10);

	opt2 = RX_CHANNEL_V(0) |
		RSS_QUEUE_VALID_F |
		RSS_QUEUE_V(csk->rss_qid);

	अगर (is_t4(lldi->adapter_type)) अणु
		काष्ठा cpl_act_खोलो_req6 *req =
			    (काष्ठा cpl_act_खोलो_req6 *)skb->head;

		INIT_TP_WR(req, 0);
		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ6,
							    qid_atid));
		req->local_port = csk->saddr6.sin6_port;
		req->peer_port = csk->daddr6.sin6_port;

		req->local_ip_hi = *(__be64 *)(csk->saddr6.sin6_addr.s6_addr);
		req->local_ip_lo = *(__be64 *)(csk->saddr6.sin6_addr.s6_addr +
								    8);
		req->peer_ip_hi = *(__be64 *)(csk->daddr6.sin6_addr.s6_addr);
		req->peer_ip_lo = *(__be64 *)(csk->daddr6.sin6_addr.s6_addr +
								    8);

		req->opt0 = cpu_to_be64(opt0);

		opt2 |= RX_FC_VALID_F;
		req->opt2 = cpu_to_be32(opt2);

		req->params = cpu_to_be32(cxgb4_select_ntuple(
					  csk->cdev->ports[csk->port_id],
					  csk->l2t));
	पूर्ण अन्यथा अगर (is_t5(lldi->adapter_type)) अणु
		काष्ठा cpl_t5_act_खोलो_req6 *req =
				(काष्ठा cpl_t5_act_खोलो_req6 *)skb->head;

		INIT_TP_WR(req, 0);
		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ6,
							    qid_atid));
		req->local_port = csk->saddr6.sin6_port;
		req->peer_port = csk->daddr6.sin6_port;
		req->local_ip_hi = *(__be64 *)(csk->saddr6.sin6_addr.s6_addr);
		req->local_ip_lo = *(__be64 *)(csk->saddr6.sin6_addr.s6_addr +
									8);
		req->peer_ip_hi = *(__be64 *)(csk->daddr6.sin6_addr.s6_addr);
		req->peer_ip_lo = *(__be64 *)(csk->daddr6.sin6_addr.s6_addr +
									8);
		req->opt0 = cpu_to_be64(opt0);

		opt2 |= T5_OPT_2_VALID_F;
		req->opt2 = cpu_to_be32(opt2);

		req->params = cpu_to_be64(FILTER_TUPLE_V(cxgb4_select_ntuple(
					  csk->cdev->ports[csk->port_id],
					  csk->l2t)));
	पूर्ण अन्यथा अणु
		काष्ठा cpl_t6_act_खोलो_req6 *req =
				(काष्ठा cpl_t6_act_खोलो_req6 *)skb->head;

		INIT_TP_WR(req, 0);
		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ6,
							    qid_atid));
		req->local_port = csk->saddr6.sin6_port;
		req->peer_port = csk->daddr6.sin6_port;
		req->local_ip_hi = *(__be64 *)(csk->saddr6.sin6_addr.s6_addr);
		req->local_ip_lo = *(__be64 *)(csk->saddr6.sin6_addr.s6_addr +
									8);
		req->peer_ip_hi = *(__be64 *)(csk->daddr6.sin6_addr.s6_addr);
		req->peer_ip_lo = *(__be64 *)(csk->daddr6.sin6_addr.s6_addr +
									8);
		req->opt0 = cpu_to_be64(opt0);

		opt2 |= RX_FC_DISABLE_F;
		opt2 |= T5_OPT_2_VALID_F;

		req->opt2 = cpu_to_be32(opt2);

		req->params = cpu_to_be64(FILTER_TUPLE_V(cxgb4_select_ntuple(
					  csk->cdev->ports[csk->port_id],
					  csk->l2t)));

		req->rsvd2 = cpu_to_be32(0);
		req->opt3 = cpu_to_be32(0);
	पूर्ण

	set_wr_txq(skb, CPL_PRIORITY_SETUP, csk->port_id);

	pr_info("t%d csk 0x%p,%u,0x%lx,%u, [%pI6]:%u-[%pI6]:%u, rss_qid %u.\n",
		CHELSIO_CHIP_VERSION(lldi->adapter_type), csk, csk->state,
		csk->flags, csk->atid,
		&csk->saddr6.sin6_addr, ntohs(csk->saddr.sin_port),
		&csk->daddr6.sin6_addr, ntohs(csk->daddr.sin_port),
		csk->rss_qid);

	cxgb4_l2t_send(csk->cdev->ports[csk->port_id], skb, csk->l2t);
पूर्ण
#पूर्ण_अगर

अटल व्योम send_बंद_req(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb = csk->cpl_बंद;
	काष्ठा cpl_बंद_con_req *req = (काष्ठा cpl_बंद_con_req *)skb->head;
	अचिन्हित पूर्णांक tid = csk->tid;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, tid %u.\n",
		csk, csk->state, csk->flags, csk->tid);
	csk->cpl_बंद = शून्य;
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);
	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_CLOSE_CON_REQ, tid));
	req->rsvd = 0;

	cxgbi_sock_skb_entail(csk, skb);
	अगर (csk->state >= CTP_ESTABLISHED)
		push_tx_frames(csk, 1);
पूर्ण

अटल व्योम पात_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk = (काष्ठा cxgbi_sock *)handle;
	काष्ठा cpl_पात_req *req;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, tid %u, abort.\n",
		csk, csk->state, csk->flags, csk->tid);
	req = (काष्ठा cpl_पात_req *)skb->data;
	req->cmd = CPL_ABORT_NO_RST;
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
पूर्ण

अटल व्योम send_पात_req(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cpl_पात_req *req;
	काष्ठा sk_buff *skb = csk->cpl_पात_req;

	अगर (unlikely(csk->state == CTP_ABORTING) || !skb || !csk->cdev)
		वापस;

	अगर (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT)) अणु
		send_tx_flowc_wr(csk);
		cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
	पूर्ण

	cxgbi_sock_set_state(csk, CTP_ABORTING);
	cxgbi_sock_set_flag(csk, CTPF_ABORT_RPL_PENDING);
	cxgbi_sock_purge_ग_लिखो_queue(csk);

	csk->cpl_पात_req = शून्य;
	req = (काष्ठा cpl_पात_req *)skb->head;
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);
	req->cmd = CPL_ABORT_SEND_RST;
	t4_set_arp_err_handler(skb, csk, पात_arp_failure);
	INIT_TP_WR(req, csk->tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ABORT_REQ, csk->tid));
	req->rsvd0 = htonl(csk->snd_nxt);
	req->rsvd1 = !cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u, snd_nxt %u, 0x%x.\n",
		csk, csk->state, csk->flags, csk->tid, csk->snd_nxt,
		req->rsvd1);

	cxgb4_l2t_send(csk->cdev->ports[csk->port_id], skb, csk->l2t);
पूर्ण

अटल व्योम send_पात_rpl(काष्ठा cxgbi_sock *csk, पूर्णांक rst_status)
अणु
	काष्ठा sk_buff *skb = csk->cpl_पात_rpl;
	काष्ठा cpl_पात_rpl *rpl = (काष्ठा cpl_पात_rpl *)skb->head;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u, status %d.\n",
		csk, csk->state, csk->flags, csk->tid, rst_status);

	csk->cpl_पात_rpl = शून्य;
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);
	INIT_TP_WR(rpl, csk->tid);
	OPCODE_TID(rpl) = cpu_to_be32(MK_OPCODE_TID(CPL_ABORT_RPL, csk->tid));
	rpl->cmd = rst_status;
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
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

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, credit %u.\n",
		csk, csk->state, csk->flags, csk->tid, credits);

	skb = alloc_wr(माप(*req), 0, GFP_ATOMIC);
	अगर (!skb) अणु
		pr_info("csk 0x%p, credit %u, OOM.\n", csk, credits);
		वापस 0;
	पूर्ण
	req = (काष्ठा cpl_rx_data_ack *)skb->head;

	set_wr_txq(skb, CPL_PRIORITY_ACK, csk->port_id);
	INIT_TP_WR(req, csk->tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_RX_DATA_ACK,
				      csk->tid));
	req->credit_dack = cpu_to_be32(RX_CREDITS_V(credits)
				       | RX_FORCE_ACK_F);
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
	वापस credits;
पूर्ण

/*
 * sgl_len - calculates the size of an SGL of the given capacity
 * @n: the number of SGL entries
 * Calculates the number of flits needed क्रम a scatter/gather list that
 * can hold the given number of entries.
 */
अटल अंतरभूत अचिन्हित पूर्णांक sgl_len(अचिन्हित पूर्णांक n)
अणु
	n--;
	वापस (3 * n) / 2 + (n & 1) + 2;
पूर्ण

/*
 * calc_tx_flits_ofld - calculate # of flits क्रम an offload packet
 * @skb: the packet
 *
 * Returns the number of flits needed क्रम the given offload packet.
 * These packets are alपढ़ोy fully स्थिरructed and no additional headers
 * will be added.
 */
अटल अंतरभूत अचिन्हित पूर्णांक calc_tx_flits_ofld(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits, cnt;

	अगर (is_ofld_imm(skb))
		वापस DIV_ROUND_UP(skb->len, 8);
	flits = skb_transport_offset(skb) / 8;
	cnt = skb_shinfo(skb)->nr_frags;
	अगर (skb_tail_poपूर्णांकer(skb) != skb_transport_header(skb))
		cnt++;
	वापस flits + sgl_len(cnt);
पूर्ण

#घोषणा FLOWC_WR_NPARAMS_MIN	9
अटल अंतरभूत पूर्णांक tx_flowc_wr_credits(पूर्णांक *nparamsp, पूर्णांक *flowclenp)
अणु
	पूर्णांक nparams, flowclen16, flowclen;

	nparams = FLOWC_WR_NPARAMS_MIN;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	nparams++;
#पूर्ण_अगर
	flowclen = दुरत्व(काष्ठा fw_flowc_wr, mnemval[nparams]);
	flowclen16 = DIV_ROUND_UP(flowclen, 16);
	flowclen = flowclen16 * 16;
	/*
	 * Return the number of 16-byte credits used by the FlowC request.
	 * Pass back the nparams and actual FlowC length अगर requested.
	 */
	अगर (nparamsp)
		*nparamsp = nparams;
	अगर (flowclenp)
		*flowclenp = flowclen;

	वापस flowclen16;
पूर्ण

अटल अंतरभूत पूर्णांक send_tx_flowc_wr(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fw_flowc_wr *flowc;
	पूर्णांक nparams, flowclen16, flowclen;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u16 vlan = ((काष्ठा l2t_entry *)csk->l2t)->vlan;
#पूर्ण_अगर
	flowclen16 = tx_flowc_wr_credits(&nparams, &flowclen);
	skb = alloc_wr(flowclen, 0, GFP_ATOMIC);
	flowc = (काष्ठा fw_flowc_wr *)skb->head;
	flowc->op_to_nparams =
		htonl(FW_WR_OP_V(FW_FLOWC_WR) | FW_FLOWC_WR_NPARAMS_V(nparams));
	flowc->flowid_len16 =
		htonl(FW_WR_LEN16_V(flowclen16) | FW_WR_FLOWID_V(csk->tid));
	flowc->mnemval[0].mnemonic = FW_FLOWC_MNEM_PFNVFN;
	flowc->mnemval[0].val = htonl(csk->cdev->pfvf);
	flowc->mnemval[1].mnemonic = FW_FLOWC_MNEM_CH;
	flowc->mnemval[1].val = htonl(csk->tx_chan);
	flowc->mnemval[2].mnemonic = FW_FLOWC_MNEM_PORT;
	flowc->mnemval[2].val = htonl(csk->tx_chan);
	flowc->mnemval[3].mnemonic = FW_FLOWC_MNEM_IQID;
	flowc->mnemval[3].val = htonl(csk->rss_qid);
	flowc->mnemval[4].mnemonic = FW_FLOWC_MNEM_SNDNXT;
	flowc->mnemval[4].val = htonl(csk->snd_nxt);
	flowc->mnemval[5].mnemonic = FW_FLOWC_MNEM_RCVNXT;
	flowc->mnemval[5].val = htonl(csk->rcv_nxt);
	flowc->mnemval[6].mnemonic = FW_FLOWC_MNEM_SNDBUF;
	flowc->mnemval[6].val = htonl(csk->snd_win);
	flowc->mnemval[7].mnemonic = FW_FLOWC_MNEM_MSS;
	flowc->mnemval[7].val = htonl(csk->advmss);
	flowc->mnemval[8].mnemonic = 0;
	flowc->mnemval[8].val = 0;
	flowc->mnemval[8].mnemonic = FW_FLOWC_MNEM_TXDATAPLEN_MAX;
	अगर (csk->cdev->skb_iso_txhdr)
		flowc->mnemval[8].val = cpu_to_be32(CXGBI_MAX_ISO_DATA_IN_SKB);
	अन्यथा
		flowc->mnemval[8].val = cpu_to_be32(16128);
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	flowc->mnemval[9].mnemonic = FW_FLOWC_MNEM_DCBPRIO;
	अगर (vlan == CPL_L2T_VLAN_NONE) अणु
		pr_warn_ratelimited("csk %u without VLAN Tag on DCB Link\n",
				    csk->tid);
		flowc->mnemval[9].val = cpu_to_be32(0);
	पूर्ण अन्यथा अणु
		flowc->mnemval[9].val = cpu_to_be32((vlan & VLAN_PRIO_MASK) >>
					VLAN_PRIO_SHIFT);
	पूर्ण
#पूर्ण_अगर

	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, tid 0x%x, %u,%u,%u,%u,%u,%u,%u.\n",
		csk, csk->tid, 0, csk->tx_chan, csk->rss_qid,
		csk->snd_nxt, csk->rcv_nxt, csk->snd_win,
		csk->advmss);

	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);

	वापस flowclen16;
पूर्ण

अटल व्योम
cxgb4i_make_tx_iso_cpl(काष्ठा sk_buff *skb, काष्ठा cpl_tx_data_iso *cpl)
अणु
	काष्ठा cxgbi_iso_info *info = (काष्ठा cxgbi_iso_info *)skb->head;
	u32 imm_en = !!(info->flags & CXGBI_ISO_INFO_IMM_ENABLE);
	u32 fslice = !!(info->flags & CXGBI_ISO_INFO_FSLICE);
	u32 lslice = !!(info->flags & CXGBI_ISO_INFO_LSLICE);
	u32 pdu_type = (info->op == ISCSI_OP_SCSI_CMD) ? 0 : 1;
	u32 submode = cxgbi_skcb_tx_ulp_mode(skb) & 0x3;

	cpl->op_to_scsi = cpu_to_be32(CPL_TX_DATA_ISO_OP_V(CPL_TX_DATA_ISO) |
				CPL_TX_DATA_ISO_FIRST_V(fslice) |
				CPL_TX_DATA_ISO_LAST_V(lslice) |
				CPL_TX_DATA_ISO_CPLHDRLEN_V(0) |
				CPL_TX_DATA_ISO_HDRCRC_V(submode & 1) |
				CPL_TX_DATA_ISO_PLDCRC_V(((submode >> 1) & 1)) |
				CPL_TX_DATA_ISO_IMMEDIATE_V(imm_en) |
				CPL_TX_DATA_ISO_SCSI_V(pdu_type));

	cpl->ahs_len = info->ahs;
	cpl->mpdu = cpu_to_be16(DIV_ROUND_UP(info->mpdu, 4));
	cpl->burst_size = cpu_to_be32(info->burst_size);
	cpl->len = cpu_to_be32(info->len);
	cpl->reserved2_seglen_offset =
	     cpu_to_be32(CPL_TX_DATA_ISO_SEGLEN_OFFSET_V(info->segment_offset));
	cpl->datasn_offset = cpu_to_be32(info->datasn_offset);
	cpl->buffer_offset = cpu_to_be32(info->buffer_offset);
	cpl->reserved3 = cpu_to_be32(0);
	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "iso: flags 0x%x, op %u, ahs %u, num_pdu %u, mpdu %u, "
		  "burst_size %u, iso_len %u\n",
		  info->flags, info->op, info->ahs, info->num_pdu,
		  info->mpdu, info->burst_size << 2, info->len);
पूर्ण

अटल व्योम
cxgb4i_make_tx_data_wr(काष्ठा cxgbi_sock *csk, काष्ठा sk_buff *skb, पूर्णांक dlen,
		       पूर्णांक len, u32 credits, पूर्णांक compl)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा fw_ofld_tx_data_wr *req;
	काष्ठा cpl_tx_data_iso *cpl;
	u32 submode = cxgbi_skcb_tx_ulp_mode(skb) & 0x3;
	u32 wr_ulp_mode = 0;
	u32 hdr_size = माप(*req);
	u32 opcode = FW_OFLD_TX_DATA_WR;
	u32 immlen = 0;
	u32 क्रमce = is_t5(lldi->adapter_type) ? TX_FORCE_V(!submode) :
						T6_TX_FORCE_F;

	अगर (cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO)) अणु
		hdr_size += माप(काष्ठा cpl_tx_data_iso);
		opcode = FW_ISCSI_TX_DATA_WR;
		immlen += माप(काष्ठा cpl_tx_data_iso);
		submode |= 8;
	पूर्ण

	अगर (is_ofld_imm(skb))
		immlen += dlen;

	req = (काष्ठा fw_ofld_tx_data_wr *)__skb_push(skb, hdr_size);
	req->op_to_immdlen = cpu_to_be32(FW_WR_OP_V(opcode) |
					 FW_WR_COMPL_V(compl) |
					 FW_WR_IMMDLEN_V(immlen));
	req->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(csk->tid) |
					FW_WR_LEN16_V(credits));
	req->plen = cpu_to_be32(len);
	cpl =  (काष्ठा cpl_tx_data_iso *)(req + 1);

	अगर (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO)))
		cxgb4i_make_tx_iso_cpl(skb, cpl);

	अगर (submode)
		wr_ulp_mode = FW_OFLD_TX_DATA_WR_ULPMODE_V(ULP2_MODE_ISCSI) |
			      FW_OFLD_TX_DATA_WR_ULPSUBMODE_V(submode);

	req->tunnel_to_proxy = cpu_to_be32(wr_ulp_mode | क्रमce |
					   FW_OFLD_TX_DATA_WR_SHOVE_V(1U));

	अगर (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT))
		cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
पूर्ण

अटल व्योम arp_failure_skb_discard(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक push_tx_frames(काष्ठा cxgbi_sock *csk, पूर्णांक req_completion)
अणु
	पूर्णांक total_size = 0;
	काष्ठा sk_buff *skb;

	अगर (unlikely(csk->state < CTP_ESTABLISHED ||
		csk->state == CTP_CLOSE_WAIT_1 || csk->state >= CTP_ABORTING)) अणु
		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK |
			  1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%lx,%u, in closing state.\n",
			  csk, csk->state, csk->flags, csk->tid);
		वापस 0;
	पूर्ण

	जबतक (csk->wr_cred && ((skb = skb_peek(&csk->ग_लिखो_queue)) != शून्य)) अणु
		काष्ठा cxgbi_iso_info *iso_cpl;
		u32 dlen = skb->len;
		u32 len = skb->len;
		u32 iso_cpl_len = 0;
		u32 flowclen16 = 0;
		u32 credits_needed;
		u32 num_pdu = 1, hdr_len;

		अगर (cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO))
			iso_cpl_len = माप(काष्ठा cpl_tx_data_iso);

		अगर (is_ofld_imm(skb))
			credits_needed = DIV_ROUND_UP(dlen + iso_cpl_len, 16);
		अन्यथा
			credits_needed =
				DIV_ROUND_UP((8 * calc_tx_flits_ofld(skb)) +
					     iso_cpl_len, 16);

		अगर (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_NEED_HDR)))
			credits_needed +=
			   DIV_ROUND_UP(माप(काष्ठा fw_ofld_tx_data_wr), 16);

		/*
		 * Assumes the initial credits is large enough to support
		 * fw_flowc_wr plus largest possible first payload
		 */
		अगर (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT)) अणु
			flowclen16 = send_tx_flowc_wr(csk);
			csk->wr_cred -= flowclen16;
			csk->wr_una_cred += flowclen16;
			cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
		पूर्ण

		अगर (csk->wr_cred < credits_needed) अणु
			log_debug(1 << CXGBI_DBG_PDU_TX,
				  "csk 0x%p, skb %u/%u, wr %d < %u.\n",
				  csk, skb->len, skb->data_len,
				  credits_needed, csk->wr_cred);

			csk->no_tx_credits++;
			अवरोध;
		पूर्ण

		csk->no_tx_credits = 0;

		__skb_unlink(skb, &csk->ग_लिखो_queue);
		set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);
		skb->csum = (__क्रमce __wsum)(credits_needed + flowclen16);
		csk->wr_cred -= credits_needed;
		csk->wr_una_cred += credits_needed;
		cxgbi_sock_enqueue_wr(csk, skb);

		log_debug(1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, skb %u/%u, wr %d, left %u, unack %u.\n",
			csk, skb->len, skb->data_len, credits_needed,
			csk->wr_cred, csk->wr_una_cred);

		अगर (!req_completion &&
		    ((csk->wr_una_cred >= (csk->wr_max_cred / 2)) ||
		     after(csk->ग_लिखो_seq, (csk->snd_una + csk->snd_win / 2))))
			req_completion = 1;

		अगर (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_NEED_HDR))) अणु
			u32 ulp_mode = cxgbi_skcb_tx_ulp_mode(skb);

			अगर (cxgbi_skcb_test_flag(skb, SKCBF_TX_ISO)) अणु
				iso_cpl = (काष्ठा cxgbi_iso_info *)skb->head;
				num_pdu = iso_cpl->num_pdu;
				hdr_len = cxgbi_skcb_tx_iscsi_hdrlen(skb);
				len += (cxgbi_ulp_extra_len(ulp_mode) * num_pdu) +
				       (hdr_len * (num_pdu - 1));
			पूर्ण अन्यथा अणु
				len += cxgbi_ulp_extra_len(ulp_mode);
			पूर्ण

			cxgb4i_make_tx_data_wr(csk, skb, dlen, len,
					       credits_needed, req_completion);
			csk->snd_nxt += len;
			cxgbi_skcb_clear_flag(skb, SKCBF_TX_NEED_HDR);
		पूर्ण अन्यथा अगर (cxgbi_skcb_test_flag(skb, SKCBF_TX_FLAG_COMPL) &&
			   (csk->wr_una_cred >= (csk->wr_max_cred / 2))) अणु
			काष्ठा cpl_बंद_con_req *req =
				(काष्ठा cpl_बंद_con_req *)skb->data;

			req->wr.wr_hi |= cpu_to_be32(FW_WR_COMPL_F);
		पूर्ण

		total_size += skb->truesize;
		t4_set_arp_err_handler(skb, csk, arp_failure_skb_discard);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%lx,%u, skb 0x%p, %u.\n",
			  csk, csk->state, csk->flags, csk->tid, skb, len);
		cxgb4_l2t_send(csk->cdev->ports[csk->port_id], skb, csk->l2t);
	पूर्ण
	वापस total_size;
पूर्ण

अटल अंतरभूत व्योम मुक्त_atid(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(csk->cdev);

	अगर (cxgbi_sock_flag(csk, CTPF_HAS_ATID)) अणु
		cxgb4_मुक्त_atid(lldi->tids, csk->atid);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_ATID);
		cxgbi_sock_put(csk);
	पूर्ण
पूर्ण

अटल व्योम करो_act_establish(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_act_establish *req = (काष्ठा cpl_act_establish *)skb->data;
	अचिन्हित लघु tcp_opt = ntohs(req->tcp_opt);
	अचिन्हित पूर्णांक tid = GET_TID(req);
	अचिन्हित पूर्णांक atid = TID_TID_G(ntohl(req->tos_atid));
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;
	u32 rcv_isn = be32_to_cpu(req->rcv_isn);

	csk = lookup_atid(t, atid);
	अगर (unlikely(!csk)) अणु
		pr_err("NO conn. for atid %u, cdev 0x%p.\n", atid, cdev);
		जाओ rel_skb;
	पूर्ण

	अगर (csk->atid != atid) अणु
		pr_err("bad conn atid %u, csk 0x%p,%u,0x%lx,tid %u, atid %u.\n",
			atid, csk, csk->state, csk->flags, csk->tid, csk->atid);
		जाओ rel_skb;
	पूर्ण

	pr_info_ipaddr("atid 0x%x, tid 0x%x, csk 0x%p,%u,0x%lx, isn %u.\n",
		       (&csk->saddr), (&csk->daddr),
		       atid, tid, csk, csk->state, csk->flags, rcv_isn);

	module_put(cdev->owner);

	cxgbi_sock_get(csk);
	csk->tid = tid;
	cxgb4_insert_tid(lldi->tids, csk, tid, csk->csk_family);
	cxgbi_sock_set_flag(csk, CTPF_HAS_TID);

	मुक्त_atid(csk);

	spin_lock_bh(&csk->lock);
	अगर (unlikely(csk->state != CTP_ACTIVE_OPEN))
		pr_info("csk 0x%p,%u,0x%lx,%u, got EST.\n",
			csk, csk->state, csk->flags, csk->tid);

	अगर (csk->retry_समयr.function) अणु
		del_समयr(&csk->retry_समयr);
		csk->retry_समयr.function = शून्य;
	पूर्ण

	csk->copied_seq = csk->rcv_wup = csk->rcv_nxt = rcv_isn;
	/*
	 * Causes the first RX_DATA_ACK to supply any Rx credits we couldn't
	 * pass through opt0.
	 */
	अगर (csk->rcv_win > (RCV_बफ_मान_MASK << 10))
		csk->rcv_wup -= csk->rcv_win - (RCV_बफ_मान_MASK << 10);

	csk->advmss = lldi->mtus[TCPOPT_MSS_G(tcp_opt)] - 40;
	अगर (TCPOPT_TSTAMP_G(tcp_opt))
		csk->advmss -= 12;
	अगर (csk->advmss < 128)
		csk->advmss = 128;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, mss_idx %u, advmss %u.\n",
			csk, TCPOPT_MSS_G(tcp_opt), csk->advmss);

	cxgbi_sock_established(csk, ntohl(req->snd_isn), ntohs(req->tcp_opt));

	अगर (unlikely(cxgbi_sock_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED)))
		send_पात_req(csk);
	अन्यथा अणु
		अगर (skb_queue_len(&csk->ग_लिखो_queue))
			push_tx_frames(csk, 0);
		cxgbi_conn_tx_खोलो(csk);
	पूर्ण
	spin_unlock_bh(&csk->lock);

rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

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

अटल व्योम csk_act_खोलो_retry_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा cxgbi_sock *csk = from_समयr(csk, t, retry_समयr);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(csk->cdev);
	व्योम (*send_act_खोलो_func)(काष्ठा cxgbi_sock *, काष्ठा sk_buff *,
				   काष्ठा l2t_entry *);
	पूर्णांक t4 = is_t4(lldi->adapter_type), size, size6;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	अगर (t4) अणु
		size = माप(काष्ठा cpl_act_खोलो_req);
		size6 = माप(काष्ठा cpl_act_खोलो_req6);
	पूर्ण अन्यथा अणु
		size = माप(काष्ठा cpl_t5_act_खोलो_req);
		size6 = माप(काष्ठा cpl_t5_act_खोलो_req6);
	पूर्ण

	अगर (csk->csk_family == AF_INET) अणु
		send_act_खोलो_func = send_act_खोलो_req;
		skb = alloc_wr(size, 0, GFP_ATOMIC);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		send_act_खोलो_func = send_act_खोलो_req6;
		skb = alloc_wr(size6, 0, GFP_ATOMIC);
#पूर्ण_अगर
	पूर्ण

	अगर (!skb)
		cxgbi_sock_fail_act_खोलो(csk, -ENOMEM);
	अन्यथा अणु
		skb->sk = (काष्ठा sock *)csk;
		t4_set_arp_err_handler(skb, csk,
				       cxgbi_sock_act_खोलो_req_arp_failure);
		send_act_खोलो_func(csk, skb, csk->l2t);
	पूर्ण

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);

पूर्ण

अटल अंतरभूत bool is_neg_adv(अचिन्हित पूर्णांक status)
अणु
	वापस status == CPL_ERR_RTX_NEG_ADVICE ||
		status == CPL_ERR_KEEPALV_NEG_ADVICE ||
		status == CPL_ERR_PERSIST_NEG_ADVICE;
पूर्ण

अटल व्योम करो_act_खोलो_rpl(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_act_खोलो_rpl *rpl = (काष्ठा cpl_act_खोलो_rpl *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	अचिन्हित पूर्णांक atid =
		TID_TID_G(AOPEN_ATID_G(be32_to_cpu(rpl->atid_status)));
	अचिन्हित पूर्णांक status = AOPEN_STATUS_G(be32_to_cpu(rpl->atid_status));
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_atid(t, atid);
	अगर (unlikely(!csk)) अणु
		pr_err("NO matching conn. atid %u, tid %u.\n", atid, tid);
		जाओ rel_skb;
	पूर्ण

	pr_info_ipaddr("tid %u/%u, status %u.\n"
		       "csk 0x%p,%u,0x%lx. ", (&csk->saddr), (&csk->daddr),
		       atid, tid, status, csk, csk->state, csk->flags);

	अगर (is_neg_adv(status))
		जाओ rel_skb;

	module_put(cdev->owner);

	अगर (status && status != CPL_ERR_TCAM_FULL &&
	    status != CPL_ERR_CONN_EXIST &&
	    status != CPL_ERR_ARP_MISS)
		cxgb4_हटाओ_tid(lldi->tids, csk->port_id, GET_TID(rpl),
				 csk->csk_family);

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	अगर (status == CPL_ERR_CONN_EXIST &&
	    csk->retry_समयr.function != csk_act_खोलो_retry_समयr) अणु
		csk->retry_समयr.function = csk_act_खोलो_retry_समयr;
		mod_समयr(&csk->retry_समयr, jअगरfies + HZ / 2);
	पूर्ण अन्यथा
		cxgbi_sock_fail_act_खोलो(csk,
					act_खोलो_rpl_status_to_त्रुटि_सं(status));

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_peer_बंद(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_peer_बंद *req = (काष्ठा cpl_peer_बंद *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(req);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण
	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u.\n",
		       (&csk->saddr), (&csk->daddr),
		       csk, csk->state, csk->flags, csk->tid);
	cxgbi_sock_rcv_peer_बंद(csk);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_बंद_con_rpl(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_बंद_con_rpl *rpl = (काष्ठा cpl_बंद_con_rpl *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण
	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u.\n",
		       (&csk->saddr), (&csk->daddr),
		       csk, csk->state, csk->flags, csk->tid);
	cxgbi_sock_rcv_बंद_conn_rpl(csk, ntohl(rpl->snd_nxt));
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक पात_status_to_त्रुटि_सं(काष्ठा cxgbi_sock *csk, पूर्णांक पात_reason,
								पूर्णांक *need_rst)
अणु
	चयन (पात_reason) अणु
	हाल CPL_ERR_BAD_SYN:
	हाल CPL_ERR_CONN_RESET:
		वापस csk->state > CTP_ESTABLISHED ?
			-EPIPE : -ECONNRESET;
	हाल CPL_ERR_XMIT_TIMEDOUT:
	हाल CPL_ERR_PERSIST_TIMEDOUT:
	हाल CPL_ERR_FINWAIT2_TIMEDOUT:
	हाल CPL_ERR_KEEPALIVE_TIMEDOUT:
		वापस -ETIMEDOUT;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम करो_पात_req_rss(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_पात_req_rss *req = (काष्ठा cpl_पात_req_rss *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(req);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;
	पूर्णांक rst_status = CPL_ABORT_NO_RST;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u, status %u.\n",
		       (&csk->saddr), (&csk->daddr),
		       csk, csk->state, csk->flags, csk->tid, req->status);

	अगर (is_neg_adv(req->status))
		जाओ rel_skb;

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	cxgbi_sock_clear_flag(csk, CTPF_ABORT_REQ_RCVD);

	अगर (!cxgbi_sock_flag(csk, CTPF_TX_DATA_SENT)) अणु
		send_tx_flowc_wr(csk);
		cxgbi_sock_set_flag(csk, CTPF_TX_DATA_SENT);
	पूर्ण

	cxgbi_sock_set_flag(csk, CTPF_ABORT_REQ_RCVD);
	cxgbi_sock_set_state(csk, CTP_ABORTING);

	send_पात_rpl(csk, rst_status);

	अगर (!cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING)) अणु
		csk->err = पात_status_to_त्रुटि_सं(csk, req->status, &rst_status);
		cxgbi_sock_बंदd(csk);
	पूर्ण

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_पात_rpl_rss(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_पात_rpl_rss *rpl = (काष्ठा cpl_पात_rpl_rss *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (!csk)
		जाओ rel_skb;

	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u, status %u.\n",
		       (&csk->saddr), (&csk->daddr), csk,
		       csk->state, csk->flags, csk->tid, rpl->status);

	अगर (rpl->status == CPL_ERR_ABORT_FAILED)
		जाओ rel_skb;

	cxgbi_sock_rcv_पात_rpl(csk);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_rx_data(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_rx_data *cpl = (काष्ठा cpl_rx_data *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(cpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (!csk) अणु
		pr_err("can't find connection for tid %u.\n", tid);
	पूर्ण अन्यथा अणु
		/* not expecting this, reset the connection. */
		pr_err("csk 0x%p, tid %u, rcv cpl_rx_data.\n", csk, tid);
		spin_lock_bh(&csk->lock);
		send_पात_req(csk);
		spin_unlock_bh(&csk->lock);
	पूर्ण
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_rx_iscsi_hdr(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_iscsi_hdr *cpl = (काष्ठा cpl_iscsi_hdr *)skb->data;
	अचिन्हित लघु pdu_len_ddp = be16_to_cpu(cpl->pdu_len_ddp);
	अचिन्हित पूर्णांक tid = GET_TID(cpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find conn. for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx, tid %u, skb 0x%p,%u, 0x%x.\n",
		csk, csk->state, csk->flags, csk->tid, skb, skb->len,
		pdu_len_ddp);

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

	cxgbi_skcb_tcp_seq(skb) = ntohl(cpl->seq);
	cxgbi_skcb_flags(skb) = 0;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(*cpl));
	__pskb_trim(skb, ntohs(cpl->len));

	अगर (!csk->skb_ulp_lhdr) अणु
		अचिन्हित अक्षर *bhs;
		अचिन्हित पूर्णांक hlen, dlen, plen;

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p,%u,0x%lx, tid %u, skb 0x%p header.\n",
			csk, csk->state, csk->flags, csk->tid, skb);
		csk->skb_ulp_lhdr = skb;
		cxgbi_skcb_set_flag(skb, SKCBF_RX_HDR);

		अगर ((CHELSIO_CHIP_VERSION(lldi->adapter_type) <= CHELSIO_T5) &&
		    (cxgbi_skcb_tcp_seq(skb) != csk->rcv_nxt)) अणु
			pr_info("tid %u, CPL_ISCSI_HDR, bad seq, 0x%x/0x%x.\n",
				csk->tid, cxgbi_skcb_tcp_seq(skb),
				csk->rcv_nxt);
			जाओ पात_conn;
		पूर्ण

		bhs = skb->data;
		hlen = ntohs(cpl->len);
		dlen = ntohl(*(अचिन्हित पूर्णांक *)(bhs + 4)) & 0xFFFFFF;

		plen = ISCSI_PDU_LEN_G(pdu_len_ddp);
		अगर (is_t4(lldi->adapter_type))
			plen -= 40;

		अगर ((hlen + dlen) != plen) अणु
			pr_info("tid 0x%x, CPL_ISCSI_HDR, pdu len "
				"mismatch %u != %u + %u, seq 0x%x.\n",
				csk->tid, plen, hlen, dlen,
				cxgbi_skcb_tcp_seq(skb));
			जाओ पात_conn;
		पूर्ण

		cxgbi_skcb_rx_pdulen(skb) = (hlen + dlen + 3) & (~0x3);
		अगर (dlen)
			cxgbi_skcb_rx_pdulen(skb) += csk->dcrc_len;
		csk->rcv_nxt += cxgbi_skcb_rx_pdulen(skb);

		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p, skb 0x%p, 0x%x,%u+%u,0x%x,0x%x.\n",
			csk, skb, *bhs, hlen, dlen,
			ntohl(*((अचिन्हित पूर्णांक *)(bhs + 16))),
			ntohl(*((अचिन्हित पूर्णांक *)(bhs + 24))));

	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *lskb = csk->skb_ulp_lhdr;

		cxgbi_skcb_set_flag(lskb, SKCBF_RX_DATA);
		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p,%u,0x%lx, skb 0x%p data, 0x%p.\n",
			csk, csk->state, csk->flags, skb, lskb);
	पूर्ण

	__skb_queue_tail(&csk->receive_queue, skb);
	spin_unlock_bh(&csk->lock);
	वापस;

पात_conn:
	send_पात_req(csk);
discard:
	spin_unlock_bh(&csk->lock);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_rx_iscsi_data(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_iscsi_hdr *cpl = (काष्ठा cpl_iscsi_hdr *)skb->data;
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;
	काष्ठा sk_buff *lskb;
	u32 tid = GET_TID(cpl);
	u16 pdu_len_ddp = be16_to_cpu(cpl->pdu_len_ddp);

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find conn. for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		  "csk 0x%p,%u,0x%lx, tid %u, skb 0x%p,%u, 0x%x.\n",
		  csk, csk->state, csk->flags, csk->tid, skb,
		  skb->len, pdu_len_ddp);

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

	cxgbi_skcb_tcp_seq(skb) = be32_to_cpu(cpl->seq);
	cxgbi_skcb_flags(skb) = 0;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(*cpl));
	__pskb_trim(skb, ntohs(cpl->len));

	अगर (!csk->skb_ulp_lhdr)
		csk->skb_ulp_lhdr = skb;

	lskb = csk->skb_ulp_lhdr;
	cxgbi_skcb_set_flag(lskb, SKCBF_RX_DATA);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		  "csk 0x%p,%u,0x%lx, skb 0x%p data, 0x%p.\n",
		  csk, csk->state, csk->flags, skb, lskb);

	__skb_queue_tail(&csk->receive_queue, skb);
	spin_unlock_bh(&csk->lock);
	वापस;

पात_conn:
	send_पात_req(csk);
discard:
	spin_unlock_bh(&csk->lock);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम
cxgb4i_process_ddpvld(काष्ठा cxgbi_sock *csk,
		      काष्ठा sk_buff *skb, u32 ddpvld)
अणु
	अगर (ddpvld & (1 << CPL_RX_DDP_STATUS_HCRC_SHIFT)) अणु
		pr_info("csk 0x%p, lhdr 0x%p, status 0x%x, hcrc bad 0x%lx.\n",
			csk, skb, ddpvld, cxgbi_skcb_flags(skb));
		cxgbi_skcb_set_flag(skb, SKCBF_RX_HCRC_ERR);
	पूर्ण

	अगर (ddpvld & (1 << CPL_RX_DDP_STATUS_DCRC_SHIFT)) अणु
		pr_info("csk 0x%p, lhdr 0x%p, status 0x%x, dcrc bad 0x%lx.\n",
			csk, skb, ddpvld, cxgbi_skcb_flags(skb));
		cxgbi_skcb_set_flag(skb, SKCBF_RX_DCRC_ERR);
	पूर्ण

	अगर (ddpvld & (1 << CPL_RX_DDP_STATUS_PAD_SHIFT)) अणु
		log_debug(1 << CXGBI_DBG_PDU_RX,
			  "csk 0x%p, lhdr 0x%p, status 0x%x, pad bad.\n",
			  csk, skb, ddpvld);
		cxgbi_skcb_set_flag(skb, SKCBF_RX_PAD_ERR);
	पूर्ण

	अगर ((ddpvld & (1 << CPL_RX_DDP_STATUS_DDP_SHIFT)) &&
	    !cxgbi_skcb_test_flag(skb, SKCBF_RX_DATA)) अणु
		log_debug(1 << CXGBI_DBG_PDU_RX,
			  "csk 0x%p, lhdr 0x%p, 0x%x, data ddp'ed.\n",
			  csk, skb, ddpvld);
		cxgbi_skcb_set_flag(skb, SKCBF_RX_DATA_DDPD);
	पूर्ण
पूर्ण

अटल व्योम करो_rx_data_ddp(काष्ठा cxgbi_device *cdev,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा sk_buff *lskb;
	काष्ठा cpl_rx_data_ddp *rpl = (काष्ठा cpl_rx_data_ddp *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;
	u32 ddpvld = be32_to_cpu(rpl->ddpvld);

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx, skb 0x%p,0x%x, lhdr 0x%p.\n",
		csk, csk->state, csk->flags, skb, ddpvld, csk->skb_ulp_lhdr);

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

	अगर (!csk->skb_ulp_lhdr) अणु
		pr_err("tid 0x%x, rcv RX_DATA_DDP w/o pdu bhs.\n", csk->tid);
		जाओ पात_conn;
	पूर्ण

	lskb = csk->skb_ulp_lhdr;
	csk->skb_ulp_lhdr = शून्य;

	cxgbi_skcb_rx_ddigest(lskb) = ntohl(rpl->ulp_crc);

	अगर (ntohs(rpl->len) != cxgbi_skcb_rx_pdulen(lskb))
		pr_info("tid 0x%x, RX_DATA_DDP pdulen %u != %u.\n",
			csk->tid, ntohs(rpl->len), cxgbi_skcb_rx_pdulen(lskb));

	cxgb4i_process_ddpvld(csk, lskb, ddpvld);

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p, lskb 0x%p, f 0x%lx.\n",
		csk, lskb, cxgbi_skcb_flags(lskb));

	cxgbi_skcb_set_flag(lskb, SKCBF_RX_STATUS);
	cxgbi_conn_pdu_पढ़ोy(csk);
	spin_unlock_bh(&csk->lock);
	जाओ rel_skb;

पात_conn:
	send_पात_req(csk);
discard:
	spin_unlock_bh(&csk->lock);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम
करो_rx_iscsi_cmp(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_rx_iscsi_cmp *rpl = (काष्ठा cpl_rx_iscsi_cmp *)skb->data;
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;
	काष्ठा sk_buff *data_skb = शून्य;
	u32 tid = GET_TID(rpl);
	u32 ddpvld = be32_to_cpu(rpl->ddpvld);
	u32 seq = be32_to_cpu(rpl->seq);
	u16 pdu_len_ddp = be16_to_cpu(rpl->pdu_len_ddp);

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk)) अणु
		pr_err("can't find connection for tid %u.\n", tid);
		जाओ rel_skb;
	पूर्ण

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		  "csk 0x%p,%u,0x%lx, skb 0x%p,0x%x, lhdr 0x%p, len %u, "
		  "pdu_len_ddp %u, status %u.\n",
		  csk, csk->state, csk->flags, skb, ddpvld, csk->skb_ulp_lhdr,
		  ntohs(rpl->len), pdu_len_ddp,  rpl->status);

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

	cxgbi_skcb_tcp_seq(skb) = seq;
	cxgbi_skcb_flags(skb) = 0;
	cxgbi_skcb_rx_pdulen(skb) = 0;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(*rpl));
	__pskb_trim(skb, be16_to_cpu(rpl->len));

	csk->rcv_nxt = seq + pdu_len_ddp;

	अगर (csk->skb_ulp_lhdr) अणु
		data_skb = skb_peek(&csk->receive_queue);
		अगर (!data_skb ||
		    !cxgbi_skcb_test_flag(data_skb, SKCBF_RX_DATA)) अणु
			pr_err("Error! freelist data not found 0x%p, tid %u\n",
			       data_skb, tid);

			जाओ पात_conn;
		पूर्ण
		__skb_unlink(data_skb, &csk->receive_queue);

		cxgbi_skcb_set_flag(skb, SKCBF_RX_DATA);

		__skb_queue_tail(&csk->receive_queue, skb);
		__skb_queue_tail(&csk->receive_queue, data_skb);
	पूर्ण अन्यथा अणु
		 __skb_queue_tail(&csk->receive_queue, skb);
	पूर्ण

	csk->skb_ulp_lhdr = शून्य;

	cxgbi_skcb_set_flag(skb, SKCBF_RX_HDR);
	cxgbi_skcb_set_flag(skb, SKCBF_RX_STATUS);
	cxgbi_skcb_set_flag(skb, SKCBF_RX_ISCSI_COMPL);
	cxgbi_skcb_rx_ddigest(skb) = be32_to_cpu(rpl->ulp_crc);

	cxgb4i_process_ddpvld(csk, skb, ddpvld);

	log_debug(1 << CXGBI_DBG_PDU_RX, "csk 0x%p, skb 0x%p, f 0x%lx.\n",
		  csk, skb, cxgbi_skcb_flags(skb));

	cxgbi_conn_pdu_पढ़ोy(csk);
	spin_unlock_bh(&csk->lock);

	वापस;

पात_conn:
	send_पात_req(csk);
discard:
	spin_unlock_bh(&csk->lock);
rel_skb:
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_fw4_ack(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbi_sock *csk;
	काष्ठा cpl_fw4_ack *rpl = (काष्ठा cpl_fw4_ack *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	अगर (unlikely(!csk))
		pr_err("can't find connection for tid %u.\n", tid);
	अन्यथा अणु
		log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk 0x%p,%u,0x%lx,%u.\n",
			csk, csk->state, csk->flags, csk->tid);
		cxgbi_sock_rcv_wr_ack(csk, rpl->credits, ntohl(rpl->snd_una),
					rpl->seq_vld);
	पूर्ण
	__kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_set_tcb_rpl(काष्ठा cxgbi_device *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_set_tcb_rpl *rpl = (काष्ठा cpl_set_tcb_rpl *)skb->data;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा tid_info *t = lldi->tids;
	काष्ठा cxgbi_sock *csk;

	csk = lookup_tid(t, tid);
	अगर (!csk) अणु
		pr_err("can't find conn. for tid %u.\n", tid);
		वापस;
	पूर्ण

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,%lx,%u, status 0x%x.\n",
		csk, csk->state, csk->flags, csk->tid, rpl->status);

	अगर (rpl->status != CPL_ERR_NONE) अणु
		pr_err("csk 0x%p,%u, SET_TCB_RPL status %u.\n",
			csk, tid, rpl->status);
		csk->err = -EINVAL;
	पूर्ण

	complete(&csk->cmpl);

	__kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक alloc_cpls(काष्ठा cxgbi_sock *csk)
अणु
	csk->cpl_बंद = alloc_wr(माप(काष्ठा cpl_बंद_con_req),
					0, GFP_KERNEL);
	अगर (!csk->cpl_बंद)
		वापस -ENOMEM;

	csk->cpl_पात_req = alloc_wr(माप(काष्ठा cpl_पात_req),
					0, GFP_KERNEL);
	अगर (!csk->cpl_पात_req)
		जाओ मुक्त_cpls;

	csk->cpl_पात_rpl = alloc_wr(माप(काष्ठा cpl_पात_rpl),
					0, GFP_KERNEL);
	अगर (!csk->cpl_पात_rpl)
		जाओ मुक्त_cpls;
	वापस 0;

मुक्त_cpls:
	cxgbi_sock_मुक्त_cpl_skbs(csk);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम l2t_put(काष्ठा cxgbi_sock *csk)
अणु
	अगर (csk->l2t) अणु
		cxgb4_l2t_release(csk->l2t);
		csk->l2t = शून्य;
		cxgbi_sock_put(csk);
	पूर्ण
पूर्ण

अटल व्योम release_offload_resources(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cxgb4_lld_info *lldi;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा net_device *ndev = csk->cdev->ports[csk->port_id];
#पूर्ण_अगर

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	cxgbi_sock_मुक्त_cpl_skbs(csk);
	cxgbi_sock_purge_ग_लिखो_queue(csk);
	अगर (csk->wr_cred != csk->wr_max_cred) अणु
		cxgbi_sock_purge_wr_queue(csk);
		cxgbi_sock_reset_wr_list(csk);
	पूर्ण

	l2t_put(csk);
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (csk->csk_family == AF_INET6)
		cxgb4_clip_release(ndev,
				   (स्थिर u32 *)&csk->saddr6.sin6_addr, 1);
#पूर्ण_अगर

	अगर (cxgbi_sock_flag(csk, CTPF_HAS_ATID))
		मुक्त_atid(csk);
	अन्यथा अगर (cxgbi_sock_flag(csk, CTPF_HAS_TID)) अणु
		lldi = cxgbi_cdev_priv(csk->cdev);
		cxgb4_हटाओ_tid(lldi->tids, 0, csk->tid,
				 csk->csk_family);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_TID);
		cxgbi_sock_put(csk);
	पूर्ण
	csk->dst = शून्य;
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
अटल अंतरभूत u8 get_iscsi_dcb_state(काष्ठा net_device *ndev)
अणु
	वापस ndev->dcbnl_ops->माला_लोtate(ndev);
पूर्ण

अटल पूर्णांक select_priority(पूर्णांक pri_mask)
अणु
	अगर (!pri_mask)
		वापस 0;
	वापस (ffs(pri_mask) - 1);
पूर्ण

अटल u8 get_iscsi_dcb_priority(काष्ठा net_device *ndev)
अणु
	पूर्णांक rv;
	u8 caps;

	काष्ठा dcb_app iscsi_dcb_app = अणु
		.protocol = 3260
	पूर्ण;

	rv = (पूर्णांक)ndev->dcbnl_ops->अ_लोap(ndev, DCB_CAP_ATTR_DCBX, &caps);
	अगर (rv)
		वापस 0;

	अगर (caps & DCB_CAP_DCBX_VER_IEEE) अणु
		iscsi_dcb_app.selector = IEEE_8021QAZ_APP_SEL_STREAM;
		rv = dcb_ieee_getapp_mask(ndev, &iscsi_dcb_app);
		अगर (!rv) अणु
			iscsi_dcb_app.selector = IEEE_8021QAZ_APP_SEL_ANY;
			rv = dcb_ieee_getapp_mask(ndev, &iscsi_dcb_app);
		पूर्ण
	पूर्ण अन्यथा अगर (caps & DCB_CAP_DCBX_VER_CEE) अणु
		iscsi_dcb_app.selector = DCB_APP_IDTYPE_PORTNUM;
		rv = dcb_getapp(ndev, &iscsi_dcb_app);
	पूर्ण

	log_debug(1 << CXGBI_DBG_ISCSI,
		  "iSCSI priority is set to %u\n", select_priority(rv));
	वापस select_priority(rv);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक init_act_खोलो(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा net_device *ndev = cdev->ports[csk->port_id];
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा neighbour *n = शून्य;
	व्योम *daddr;
	अचिन्हित पूर्णांक step;
	अचिन्हित पूर्णांक rxq_idx;
	अचिन्हित पूर्णांक size, size6;
	अचिन्हित पूर्णांक linkspeed;
	अचिन्हित पूर्णांक rcv_winf, snd_winf;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u8 priority = 0;
#पूर्ण_अगर
	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	अगर (csk->csk_family == AF_INET)
		daddr = &csk->daddr.sin_addr.s_addr;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (csk->csk_family == AF_INET6)
		daddr = &csk->daddr6.sin6_addr;
#पूर्ण_अगर
	अन्यथा अणु
		pr_err("address family 0x%x not supported\n", csk->csk_family);
		जाओ rel_resource;
	पूर्ण

	n = dst_neigh_lookup(csk->dst, daddr);

	अगर (!n) अणु
		pr_err("%s, can't get neighbour of csk->dst.\n", ndev->name);
		जाओ rel_resource;
	पूर्ण

	अगर (!(n->nud_state & NUD_VALID))
		neigh_event_send(n, शून्य);

	csk->atid = cxgb4_alloc_atid(lldi->tids, csk);
	अगर (csk->atid < 0) अणु
		pr_err("%s, NO atid available.\n", ndev->name);
		जाओ rel_resource_without_clip;
	पूर्ण
	cxgbi_sock_set_flag(csk, CTPF_HAS_ATID);
	cxgbi_sock_get(csk);

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	अगर (get_iscsi_dcb_state(ndev))
		priority = get_iscsi_dcb_priority(ndev);

	csk->dcb_priority = priority;
	csk->l2t = cxgb4_l2t_get(lldi->l2t, n, ndev, priority);
#अन्यथा
	csk->l2t = cxgb4_l2t_get(lldi->l2t, n, ndev, 0);
#पूर्ण_अगर
	अगर (!csk->l2t) अणु
		pr_err("%s, cannot alloc l2t.\n", ndev->name);
		जाओ rel_resource_without_clip;
	पूर्ण
	cxgbi_sock_get(csk);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (csk->csk_family == AF_INET6)
		cxgb4_clip_get(ndev, (स्थिर u32 *)&csk->saddr6.sin6_addr, 1);
#पूर्ण_अगर

	अगर (is_t4(lldi->adapter_type)) अणु
		size = माप(काष्ठा cpl_act_खोलो_req);
		size6 = माप(काष्ठा cpl_act_खोलो_req6);
	पूर्ण अन्यथा अगर (is_t5(lldi->adapter_type)) अणु
		size = माप(काष्ठा cpl_t5_act_खोलो_req);
		size6 = माप(काष्ठा cpl_t5_act_खोलो_req6);
	पूर्ण अन्यथा अणु
		size = माप(काष्ठा cpl_t6_act_खोलो_req);
		size6 = माप(काष्ठा cpl_t6_act_खोलो_req6);
	पूर्ण

	अगर (csk->csk_family == AF_INET)
		skb = alloc_wr(size, 0, GFP_NOIO);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		skb = alloc_wr(size6, 0, GFP_NOIO);
#पूर्ण_अगर

	अगर (!skb)
		जाओ rel_resource;
	skb->sk = (काष्ठा sock *)csk;
	t4_set_arp_err_handler(skb, csk, cxgbi_sock_act_खोलो_req_arp_failure);

	अगर (!csk->mtu)
		csk->mtu = dst_mtu(csk->dst);
	cxgb4_best_mtu(lldi->mtus, csk->mtu, &csk->mss_idx);
	csk->tx_chan = cxgb4_port_chan(ndev);
	csk->smac_idx = ((काष्ठा port_info *)netdev_priv(ndev))->smt_idx;
	step = lldi->ntxq / lldi->nchan;
	csk->txq_idx = cxgb4_port_idx(ndev) * step;
	step = lldi->nrxq / lldi->nchan;
	rxq_idx = (cxgb4_port_idx(ndev) * step) + (cdev->rxq_idx_cntr % step);
	cdev->rxq_idx_cntr++;
	csk->rss_qid = lldi->rxq_ids[rxq_idx];
	linkspeed = ((काष्ठा port_info *)netdev_priv(ndev))->link_cfg.speed;
	csk->snd_win = cxgb4i_snd_win;
	csk->rcv_win = cxgb4i_rcv_win;
	अगर (cxgb4i_rcv_win <= 0) अणु
		csk->rcv_win = CXGB4I_DEFAULT_10G_RCV_WIN;
		rcv_winf = linkspeed / SPEED_10000;
		अगर (rcv_winf)
			csk->rcv_win *= rcv_winf;
	पूर्ण
	अगर (cxgb4i_snd_win <= 0) अणु
		csk->snd_win = CXGB4I_DEFAULT_10G_SND_WIN;
		snd_winf = linkspeed / SPEED_10000;
		अगर (snd_winf)
			csk->snd_win *= snd_winf;
	पूर्ण
	csk->wr_cred = lldi->wr_cred -
		       DIV_ROUND_UP(माप(काष्ठा cpl_पात_req), 16);
	csk->wr_max_cred = csk->wr_cred;
	csk->wr_una_cred = 0;
	cxgbi_sock_reset_wr_list(csk);
	csk->err = 0;

	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u,%u,%u, mtu %u,%u, smac %u.\n",
		       (&csk->saddr), (&csk->daddr), csk, csk->state,
		       csk->flags, csk->tx_chan, csk->txq_idx, csk->rss_qid,
		       csk->mtu, csk->mss_idx, csk->smac_idx);

	/* must रुको क्रम either a act_खोलो_rpl or act_खोलो_establish */
	अगर (!try_module_get(cdev->owner)) अणु
		pr_err("%s, try_module_get failed.\n", ndev->name);
		जाओ rel_resource;
	पूर्ण

	cxgbi_sock_set_state(csk, CTP_ACTIVE_OPEN);
	अगर (csk->csk_family == AF_INET)
		send_act_खोलो_req(csk, skb, csk->l2t);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		send_act_खोलो_req6(csk, skb, csk->l2t);
#पूर्ण_अगर
	neigh_release(n);

	वापस 0;

rel_resource:
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (csk->csk_family == AF_INET6)
		cxgb4_clip_release(ndev,
				   (स्थिर u32 *)&csk->saddr6.sin6_addr, 1);
#पूर्ण_अगर
rel_resource_without_clip:
	अगर (n)
		neigh_release(n);
	अगर (skb)
		__kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल cxgb4i_cplhandler_func cxgb4i_cplhandlers[NUM_CPL_CMDS] = अणु
	[CPL_ACT_ESTABLISH] = करो_act_establish,
	[CPL_ACT_OPEN_RPL] = करो_act_खोलो_rpl,
	[CPL_PEER_CLOSE] = करो_peer_बंद,
	[CPL_ABORT_REQ_RSS] = करो_पात_req_rss,
	[CPL_ABORT_RPL_RSS] = करो_पात_rpl_rss,
	[CPL_CLOSE_CON_RPL] = करो_बंद_con_rpl,
	[CPL_FW4_ACK] = करो_fw4_ack,
	[CPL_ISCSI_HDR] = करो_rx_iscsi_hdr,
	[CPL_ISCSI_DATA] = करो_rx_iscsi_data,
	[CPL_SET_TCB_RPL] = करो_set_tcb_rpl,
	[CPL_RX_DATA_DDP] = करो_rx_data_ddp,
	[CPL_RX_ISCSI_DDP] = करो_rx_data_ddp,
	[CPL_RX_ISCSI_CMP] = करो_rx_iscsi_cmp,
	[CPL_RX_DATA] = करो_rx_data,
पूर्ण;

अटल पूर्णांक cxgb4i_ofld_init(काष्ठा cxgbi_device *cdev)
अणु
	पूर्णांक rc;

	अगर (cxgb4i_max_connect > CXGB4I_MAX_CONN)
		cxgb4i_max_connect = CXGB4I_MAX_CONN;

	rc = cxgbi_device_porपंचांगap_create(cdev, cxgb4i_sport_base,
					cxgb4i_max_connect);
	अगर (rc < 0)
		वापस rc;

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

अटल अंतरभूत व्योम
ulp_mem_io_set_hdr(काष्ठा cxgbi_device *cdev,
		   काष्ठा ulp_mem_io *req,
		   अचिन्हित पूर्णांक wr_len, अचिन्हित पूर्णांक dlen,
		   अचिन्हित पूर्णांक pm_addr,
		   पूर्णांक tid)
अणु
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा ulptx_idata *idata = (काष्ठा ulptx_idata *)(req + 1);

	INIT_ULPTX_WR(req, wr_len, 0, tid);
	req->wr.wr_hi = htonl(FW_WR_OP_V(FW_ULPTX_WR) |
		FW_WR_ATOMIC_V(0));
	req->cmd = htonl(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
		ULP_MEMIO_ORDER_V(is_t4(lldi->adapter_type)) |
		T5_ULP_MEMIO_IMM_V(!is_t4(lldi->adapter_type)));
	req->dlen = htonl(ULP_MEMIO_DATA_LEN_V(dlen >> 5));
	req->lock_addr = htonl(ULP_MEMIO_ADDR_V(pm_addr >> 5));
	req->len16 = htonl(DIV_ROUND_UP(wr_len - माप(req->wr), 16));

	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	idata->len = htonl(dlen);
पूर्ण

अटल काष्ठा sk_buff *
ddp_ppod_init_idata(काष्ठा cxgbi_device *cdev,
		    काष्ठा cxgbi_ppm *ppm,
		    अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक npods,
		    अचिन्हित पूर्णांक tid)
अणु
	अचिन्हित पूर्णांक pm_addr = (idx << PPOD_SIZE_SHIFT) + ppm->llimit;
	अचिन्हित पूर्णांक dlen = npods << PPOD_SIZE_SHIFT;
	अचिन्हित पूर्णांक wr_len = roundup(माप(काष्ठा ulp_mem_io) +
				माप(काष्ठा ulptx_idata) + dlen, 16);
	काष्ठा sk_buff *skb = alloc_wr(wr_len, 0, GFP_ATOMIC);

	अगर (!skb) अणु
		pr_err("%s: %s idx %u, npods %u, OOM.\n",
		       __func__, ppm->ndev->name, idx, npods);
		वापस शून्य;
	पूर्ण

	ulp_mem_io_set_hdr(cdev, (काष्ठा ulp_mem_io *)skb->head, wr_len, dlen,
			   pm_addr, tid);

	वापस skb;
पूर्ण

अटल पूर्णांक ddp_ppod_ग_लिखो_idata(काष्ठा cxgbi_ppm *ppm, काष्ठा cxgbi_sock *csk,
				काष्ठा cxgbi_task_tag_info *ttinfo,
				अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक npods,
				काष्ठा scatterlist **sg_pp,
				अचिन्हित पूर्णांक *sg_off)
अणु
	काष्ठा cxgbi_device *cdev = csk->cdev;
	काष्ठा sk_buff *skb = ddp_ppod_init_idata(cdev, ppm, idx, npods,
						  csk->tid);
	काष्ठा ulp_mem_io *req;
	काष्ठा ulptx_idata *idata;
	काष्ठा cxgbi_pagepod *ppod;
	पूर्णांक i;

	अगर (!skb)
		वापस -ENOMEM;

	req = (काष्ठा ulp_mem_io *)skb->head;
	idata = (काष्ठा ulptx_idata *)(req + 1);
	ppod = (काष्ठा cxgbi_pagepod *)(idata + 1);

	क्रम (i = 0; i < npods; i++, ppod++)
		cxgbi_ddp_set_one_ppod(ppod, ttinfo, sg_pp, sg_off);

	cxgbi_skcb_set_flag(skb, SKCBF_TX_MEM_WRITE);
	cxgbi_skcb_set_flag(skb, SKCBF_TX_FLAG_COMPL);
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);

	spin_lock_bh(&csk->lock);
	cxgbi_sock_skb_entail(csk, skb);
	spin_unlock_bh(&csk->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ddp_set_map(काष्ठा cxgbi_ppm *ppm, काष्ठा cxgbi_sock *csk,
		       काष्ठा cxgbi_task_tag_info *ttinfo)
अणु
	अचिन्हित पूर्णांक pidx = ttinfo->idx;
	अचिन्हित पूर्णांक npods = ttinfo->npods;
	अचिन्हित पूर्णांक i, cnt;
	पूर्णांक err = 0;
	काष्ठा scatterlist *sg = ttinfo->sgl;
	अचिन्हित पूर्णांक offset = 0;

	ttinfo->cid = csk->port_id;

	क्रम (i = 0; i < npods; i += cnt, pidx += cnt) अणु
		cnt = npods - i;

		अगर (cnt > ULPMEM_IDATA_MAX_NPPODS)
			cnt = ULPMEM_IDATA_MAX_NPPODS;
		err = ddp_ppod_ग_लिखो_idata(ppm, csk, ttinfo, pidx, cnt,
					   &sg, &offset);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ddp_setup_conn_pgidx(काष्ठा cxgbi_sock *csk, अचिन्हित पूर्णांक tid,
				पूर्णांक pg_idx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_set_tcb_field *req;

	अगर (!pg_idx || pg_idx >= DDP_PGIDX_MAX)
		वापस 0;

	skb = alloc_wr(माप(*req), 0, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	/*  set up ulp page size */
	req = (काष्ठा cpl_set_tcb_field *)skb->head;
	INIT_TP_WR(req, csk->tid);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, csk->tid));
	req->reply_ctrl = htons(NO_REPLY_V(0) | QUEUENO_V(csk->rss_qid));
	req->word_cookie = htons(0);
	req->mask = cpu_to_be64(0x3 << 8);
	req->val = cpu_to_be64(pg_idx << 8);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->port_id);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, tid 0x%x, pg_idx %u.\n", csk, csk->tid, pg_idx);

	reinit_completion(&csk->cmpl);
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
	रुको_क्रम_completion(&csk->cmpl);

	वापस csk->err;
पूर्ण

अटल पूर्णांक ddp_setup_conn_digest(काष्ठा cxgbi_sock *csk, अचिन्हित पूर्णांक tid,
				 पूर्णांक hcrc, पूर्णांक dcrc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_set_tcb_field *req;

	अगर (!hcrc && !dcrc)
		वापस 0;

	skb = alloc_wr(माप(*req), 0, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	csk->hcrc_len = (hcrc ? 4 : 0);
	csk->dcrc_len = (dcrc ? 4 : 0);
	/*  set up ulp submode */
	req = (काष्ठा cpl_set_tcb_field *)skb->head;
	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, tid));
	req->reply_ctrl = htons(NO_REPLY_V(0) | QUEUENO_V(csk->rss_qid));
	req->word_cookie = htons(0);
	req->mask = cpu_to_be64(0x3 << 4);
	req->val = cpu_to_be64(((hcrc ? ULP_CRC_HEADER : 0) |
				(dcrc ? ULP_CRC_DATA : 0)) << 4);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->port_id);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, tid 0x%x, crc %d,%d.\n", csk, csk->tid, hcrc, dcrc);

	reinit_completion(&csk->cmpl);
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
	रुको_क्रम_completion(&csk->cmpl);

	वापस csk->err;
पूर्ण

अटल काष्ठा cxgbi_ppm *cdev2ppm(काष्ठा cxgbi_device *cdev)
अणु
	वापस (काष्ठा cxgbi_ppm *)(*((काष्ठा cxgb4_lld_info *)
				       (cxgbi_cdev_priv(cdev)))->iscsi_ppm);
पूर्ण

अटल पूर्णांक cxgb4i_ddp_init(काष्ठा cxgbi_device *cdev)
अणु
	काष्ठा cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	काष्ठा net_device *ndev = cdev->ports[0];
	काष्ठा cxgbi_tag_क्रमmat tक्रमmat;
	पूर्णांक i, err;

	अगर (!lldi->vr->iscsi.size) अणु
		pr_warn("%s, iscsi NOT enabled, check config!\n", ndev->name);
		वापस -EACCES;
	पूर्ण

	cdev->flags |= CXGBI_FLAG_USE_PPOD_OFLDQ;

	स_रखो(&tक्रमmat, 0, माप(काष्ठा cxgbi_tag_क्रमmat));
	क्रम (i = 0; i < 4; i++)
		tक्रमmat.pgsz_order[i] = (lldi->iscsi_pgsz_order >> (i << 3))
					 & 0xF;
	cxgbi_tagmask_check(lldi->iscsi_tagmask, &tक्रमmat);

	pr_info("iscsi_edram.start 0x%x iscsi_edram.size 0x%x",
		lldi->vr->ppod_edram.start, lldi->vr->ppod_edram.size);

	err = cxgbi_ddp_ppm_setup(lldi->iscsi_ppm, cdev, &tक्रमmat,
				  lldi->vr->iscsi.size, lldi->iscsi_llimit,
				  lldi->vr->iscsi.start, 2,
				  lldi->vr->ppod_edram.start,
				  lldi->vr->ppod_edram.size);

	अगर (err < 0)
		वापस err;

	cdev->csk_ddp_setup_digest = ddp_setup_conn_digest;
	cdev->csk_ddp_setup_pgidx = ddp_setup_conn_pgidx;
	cdev->csk_ddp_set_map = ddp_set_map;
	cdev->tx_max_size = min_t(अचिन्हित पूर्णांक, ULP2_MAX_PDU_PAYLOAD,
				  lldi->iscsi_iolen - ISCSI_PDU_NONPAYLOAD_LEN);
	cdev->rx_max_size = min_t(अचिन्हित पूर्णांक, ULP2_MAX_PDU_PAYLOAD,
				  lldi->iscsi_iolen - ISCSI_PDU_NONPAYLOAD_LEN);
	cdev->cdev2ppm = cdev2ppm;

	वापस 0;
पूर्ण

अटल bool is_memमुक्त(काष्ठा adapter *adap)
अणु
	u32 io;

	io = t4_पढ़ो_reg(adap, MA_TARGET_MEM_ENABLE_A);
	अगर (is_t5(adap->params.chip)) अणु
		अगर ((io & EXT_MEM0_ENABLE_F) || (io & EXT_MEM1_ENABLE_F))
			वापस false;
	पूर्ण अन्यथा अगर (io & EXT_MEM_ENABLE_F) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम *t4_uld_add(स्थिर काष्ठा cxgb4_lld_info *lldi)
अणु
	काष्ठा cxgbi_device *cdev;
	काष्ठा port_info *pi;
	काष्ठा net_device *ndev;
	काष्ठा adapter *adap;
	काष्ठा tid_info *t;
	u32 max_cmds = CXGB4I_SCSI_HOST_QDEPTH;
	u32 max_conn = CXGBI_MAX_CONN;
	पूर्णांक i, rc;

	cdev = cxgbi_device_रेजिस्टर(माप(*lldi), lldi->nports);
	अगर (!cdev) अणु
		pr_info("t4 device 0x%p, register failed.\n", lldi);
		वापस शून्य;
	पूर्ण
	pr_info("0x%p,0x%x, ports %u,%s, chan %u, q %u,%u, wr %u.\n",
		cdev, lldi->adapter_type, lldi->nports,
		lldi->ports[0]->name, lldi->nchan, lldi->ntxq,
		lldi->nrxq, lldi->wr_cred);
	क्रम (i = 0; i < lldi->nrxq; i++)
		log_debug(1 << CXGBI_DBG_DEV,
			"t4 0x%p, rxq id #%d: %u.\n",
			cdev, i, lldi->rxq_ids[i]);

	स_नकल(cxgbi_cdev_priv(cdev), lldi, माप(*lldi));
	cdev->flags = CXGBI_FLAG_DEV_T4;
	cdev->pdev = lldi->pdev;
	cdev->ports = lldi->ports;
	cdev->nports = lldi->nports;
	cdev->mtus = lldi->mtus;
	cdev->nmtus = NMTUS;
	cdev->rx_credit_thres = (CHELSIO_CHIP_VERSION(lldi->adapter_type) <=
				 CHELSIO_T5) ? cxgb4i_rx_credit_thres : 0;
	cdev->skb_tx_rsvd = CXGB4I_TX_HEADER_LEN;
	cdev->skb_rx_extra = माप(काष्ठा cpl_iscsi_hdr);
	cdev->itp = &cxgb4i_iscsi_transport;
	cdev->owner = THIS_MODULE;

	cdev->pfvf = FW_PFVF_CMD_PFN_V(lldi->pf);
	pr_info("cdev 0x%p,%s, pfvf %u.\n",
		cdev, lldi->ports[0]->name, cdev->pfvf);

	rc = cxgb4i_ddp_init(cdev);
	अगर (rc) अणु
		pr_info("t4 0x%p ddp init failed %d.\n", cdev, rc);
		जाओ err_out;
	पूर्ण

	ndev = cdev->ports[0];
	adap = netdev2adap(ndev);
	अगर (adap) अणु
		t = &adap->tids;
		अगर (t->ntids <= CXGBI_MAX_CONN)
			max_conn = t->ntids;

		अगर (is_memमुक्त(adap)) अणु
			cdev->flags |=	CXGBI_FLAG_DEV_ISO_OFF;
			max_cmds = CXGB4I_SCSI_HOST_QDEPTH >> 2;

			pr_info("%s: 0x%p, tid %u, SO adapter.\n",
				ndev->name, cdev, t->ntids);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("%s, 0x%p, NO adapter struct.\n", ndev->name, cdev);
	पूर्ण

	/* ISO is enabled in T5/T6 firmware version >= 1.13.43.0 */
	अगर (!is_t4(lldi->adapter_type) &&
	    (lldi->fw_vers >= 0x10d2b00) &&
	    !(cdev->flags & CXGBI_FLAG_DEV_ISO_OFF))
		cdev->skb_iso_txhdr = माप(काष्ठा cpl_tx_data_iso);

	rc = cxgb4i_ofld_init(cdev);
	अगर (rc) अणु
		pr_info("t4 0x%p ofld init failed.\n", cdev);
		जाओ err_out;
	पूर्ण

	cxgb4i_host_ढाँचा.can_queue = max_cmds;
	rc = cxgbi_hbas_add(cdev, CXGB4I_MAX_LUN, max_conn,
			    &cxgb4i_host_ढाँचा, cxgb4i_stt);
	अगर (rc)
		जाओ err_out;

	क्रम (i = 0; i < cdev->nports; i++) अणु
		pi = netdev_priv(lldi->ports[i]);
		cdev->hbas[i]->port_id = pi->port_id;
	पूर्ण
	वापस cdev;

err_out:
	cxgbi_device_unरेजिस्टर(cdev);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

#घोषणा RX_PULL_LEN	128
अटल पूर्णांक t4_uld_rx_handler(व्योम *handle, स्थिर __be64 *rsp,
				स्थिर काष्ठा pkt_gl *pgl)
अणु
	स्थिर काष्ठा cpl_act_establish *rpl;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक opc;
	काष्ठा cxgbi_device *cdev = handle;

	अगर (pgl == शून्य) अणु
		अचिन्हित पूर्णांक len = 64 - माप(काष्ठा rsp_ctrl) - 8;

		skb = alloc_wr(len, 0, GFP_ATOMIC);
		अगर (!skb)
			जाओ nomem;
		skb_copy_to_linear_data(skb, &rsp[1], len);
	पूर्ण अन्यथा अणु
		अगर (unlikely(*(u8 *)rsp != *(u8 *)pgl->va)) अणु
			pr_info("? FL 0x%p,RSS%#llx,FL %#llx,len %u.\n",
				pgl->va, be64_to_cpu(*rsp),
				be64_to_cpu(*(u64 *)pgl->va),
				pgl->tot_len);
			वापस 0;
		पूर्ण
		skb = cxgb4_pktgl_to_skb(pgl, RX_PULL_LEN, RX_PULL_LEN);
		अगर (unlikely(!skb))
			जाओ nomem;
	पूर्ण

	rpl = (काष्ठा cpl_act_establish *)skb->data;
	opc = rpl->ot.opcode;
	log_debug(1 << CXGBI_DBG_TOE,
		"cdev %p, opcode 0x%x(0x%x,0x%x), skb %p.\n",
		 cdev, opc, rpl->ot.opcode_tid, ntohl(rpl->ot.opcode_tid), skb);
	अगर (opc >= ARRAY_SIZE(cxgb4i_cplhandlers) || !cxgb4i_cplhandlers[opc]) अणु
		pr_err("No handler for opcode 0x%x.\n", opc);
		__kमुक्त_skb(skb);
	पूर्ण अन्यथा
		cxgb4i_cplhandlers[opc](cdev, skb);

	वापस 0;
nomem:
	log_debug(1 << CXGBI_DBG_TOE, "OOM bailing out.\n");
	वापस 1;
पूर्ण

अटल पूर्णांक t4_uld_state_change(व्योम *handle, क्रमागत cxgb4_state state)
अणु
	काष्ठा cxgbi_device *cdev = handle;

	चयन (state) अणु
	हाल CXGB4_STATE_UP:
		pr_info("cdev 0x%p, UP.\n", cdev);
		अवरोध;
	हाल CXGB4_STATE_START_RECOVERY:
		pr_info("cdev 0x%p, RECOVERY.\n", cdev);
		/* बंद all connections */
		अवरोध;
	हाल CXGB4_STATE_DOWN:
		pr_info("cdev 0x%p, DOWN.\n", cdev);
		अवरोध;
	हाल CXGB4_STATE_DETACH:
		pr_info("cdev 0x%p, DETACH.\n", cdev);
		cxgbi_device_unरेजिस्टर(cdev);
		अवरोध;
	शेष:
		pr_info("cdev 0x%p, unknown state %d.\n", cdev, state);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
अटल पूर्णांक
cxgb4_dcb_change_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val,
			व्योम *data)
अणु
	पूर्णांक i, port = 0xFF;
	काष्ठा net_device *ndev;
	काष्ठा cxgbi_device *cdev = शून्य;
	काष्ठा dcb_app_type *iscsi_app = data;
	काष्ठा cxgbi_ports_map *pmap;
	u8 priority;

	अगर (iscsi_app->dcbx & DCB_CAP_DCBX_VER_IEEE) अणु
		अगर ((iscsi_app->app.selector != IEEE_8021QAZ_APP_SEL_STREAM) &&
		    (iscsi_app->app.selector != IEEE_8021QAZ_APP_SEL_ANY))
			वापस NOTIFY_DONE;

		priority = iscsi_app->app.priority;
	पूर्ण अन्यथा अगर (iscsi_app->dcbx & DCB_CAP_DCBX_VER_CEE) अणु
		अगर (iscsi_app->app.selector != DCB_APP_IDTYPE_PORTNUM)
			वापस NOTIFY_DONE;

		अगर (!iscsi_app->app.priority)
			वापस NOTIFY_DONE;

		priority = ffs(iscsi_app->app.priority) - 1;
	पूर्ण अन्यथा अणु
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (iscsi_app->app.protocol != 3260)
		वापस NOTIFY_DONE;

	log_debug(1 << CXGBI_DBG_ISCSI, "iSCSI priority for ifid %d is %u\n",
		  iscsi_app->अगरindex, priority);

	ndev = dev_get_by_index(&init_net, iscsi_app->अगरindex);
	अगर (!ndev)
		वापस NOTIFY_DONE;

	cdev = cxgbi_device_find_by_netdev_rcu(ndev, &port);

	dev_put(ndev);
	अगर (!cdev)
		वापस NOTIFY_DONE;

	pmap = &cdev->pmap;

	क्रम (i = 0; i < pmap->used; i++) अणु
		अगर (pmap->port_csk[i]) अणु
			काष्ठा cxgbi_sock *csk = pmap->port_csk[i];

			अगर (csk->dcb_priority != priority) अणु
				iscsi_conn_failure(csk->user_data,
						   ISCSI_ERR_CONN_FAILED);
				pr_info("Restarting iSCSI connection %p with "
					"priority %u->%u.\n", csk,
					csk->dcb_priority, priority);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init cxgb4i_init_module(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "%s", version);

	rc = cxgbi_iscsi_init(&cxgb4i_iscsi_transport, &cxgb4i_stt);
	अगर (rc < 0)
		वापस rc;
	cxgb4_रेजिस्टर_uld(CXGB4_ULD_ISCSI, &cxgb4i_uld_info);

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	pr_info("%s dcb enabled.\n", DRV_MODULE_NAME);
	रेजिस्टर_dcbevent_notअगरier(&cxgb4_dcb_change);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास cxgb4i_निकास_module(व्योम)
अणु
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	unरेजिस्टर_dcbevent_notअगरier(&cxgb4_dcb_change);
#पूर्ण_अगर
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_ISCSI);
	cxgbi_device_unरेजिस्टर_all(CXGBI_FLAG_DEV_T4);
	cxgbi_iscsi_cleanup(&cxgb4i_iscsi_transport, &cxgb4i_stt);
पूर्ण

module_init(cxgb4i_init_module);
module_निकास(cxgb4i_निकास_module);
