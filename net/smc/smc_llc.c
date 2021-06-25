<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Link Layer Control (LLC)
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Klaus Wacker <Klaus.Wacker@de.ibm.com>
 *              Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <net/tcp.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "smc.h"
#समावेश "smc_core.h"
#समावेश "smc_clc.h"
#समावेश "smc_llc.h"
#समावेश "smc_pnet.h"

#घोषणा SMC_LLC_DATA_LEN		40

काष्ठा smc_llc_hdr अणु
	काष्ठा smc_wr_rx_hdr common;
	u8 length;	/* 44 */
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 reserved:4,
	   add_link_rej_rsn:4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 add_link_rej_rsn:4,
	   reserved:4;
#पूर्ण_अगर
	u8 flags;
पूर्ण;

#घोषणा SMC_LLC_FLAG_NO_RMBE_EYEC	0x03

काष्ठा smc_llc_msg_confirm_link अणु	/* type 0x01 */
	काष्ठा smc_llc_hdr hd;
	u8 sender_mac[ETH_ALEN];
	u8 sender_gid[SMC_GID_SIZE];
	u8 sender_qp_num[3];
	u8 link_num;
	u8 link_uid[SMC_LGR_ID_SIZE];
	u8 max_links;
	u8 reserved[9];
पूर्ण;

#घोषणा SMC_LLC_FLAG_ADD_LNK_REJ	0x40
#घोषणा SMC_LLC_REJ_RSN_NO_ALT_PATH	1

#घोषणा SMC_LLC_ADD_LNK_MAX_LINKS	2

काष्ठा smc_llc_msg_add_link अणु		/* type 0x02 */
	काष्ठा smc_llc_hdr hd;
	u8 sender_mac[ETH_ALEN];
	u8 reserved2[2];
	u8 sender_gid[SMC_GID_SIZE];
	u8 sender_qp_num[3];
	u8 link_num;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 reserved3 : 4,
	   qp_mtu   : 4;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 qp_mtu   : 4,
	   reserved3 : 4;
#पूर्ण_अगर
	u8 initial_psn[3];
	u8 reserved[8];
पूर्ण;

काष्ठा smc_llc_msg_add_link_cont_rt अणु
	__be32 rmb_key;
	__be32 rmb_key_new;
	__be64 rmb_vaddr_new;
पूर्ण;

#घोषणा SMC_LLC_RKEYS_PER_CONT_MSG	2

काष्ठा smc_llc_msg_add_link_cont अणु	/* type 0x03 */
	काष्ठा smc_llc_hdr hd;
	u8 link_num;
	u8 num_rkeys;
	u8 reserved2[2];
	काष्ठा smc_llc_msg_add_link_cont_rt rt[SMC_LLC_RKEYS_PER_CONT_MSG];
	u8 reserved[4];
पूर्ण __packed;			/* क्रमmat defined in RFC7609 */

#घोषणा SMC_LLC_FLAG_DEL_LINK_ALL	0x40
#घोषणा SMC_LLC_FLAG_DEL_LINK_ORDERLY	0x20

काष्ठा smc_llc_msg_del_link अणु		/* type 0x04 */
	काष्ठा smc_llc_hdr hd;
	u8 link_num;
	__be32 reason;
	u8 reserved[35];
पूर्ण __packed;			/* क्रमmat defined in RFC7609 */

काष्ठा smc_llc_msg_test_link अणु		/* type 0x07 */
	काष्ठा smc_llc_hdr hd;
	u8 user_data[16];
	u8 reserved[24];
पूर्ण;

काष्ठा smc_rmb_rtoken अणु
	जोड़ अणु
		u8 num_rkeys;	/* first rtoken byte of CONFIRM LINK msg */
				/* is actually the num of rtokens, first */
				/* rtoken is always क्रम the current link */
		u8 link_id;	/* link id of the rtoken */
	पूर्ण;
	__be32 rmb_key;
	__be64 rmb_vaddr;
पूर्ण __packed;			/* क्रमmat defined in RFC7609 */

#घोषणा SMC_LLC_RKEYS_PER_MSG	3

काष्ठा smc_llc_msg_confirm_rkey अणु	/* type 0x06 */
	काष्ठा smc_llc_hdr hd;
	काष्ठा smc_rmb_rtoken rtoken[SMC_LLC_RKEYS_PER_MSG];
	u8 reserved;
पूर्ण;

#घोषणा SMC_LLC_DEL_RKEY_MAX	8
#घोषणा SMC_LLC_FLAG_RKEY_RETRY	0x10
#घोषणा SMC_LLC_FLAG_RKEY_NEG	0x20

काष्ठा smc_llc_msg_delete_rkey अणु	/* type 0x09 */
	काष्ठा smc_llc_hdr hd;
	u8 num_rkeys;
	u8 err_mask;
	u8 reserved[2];
	__be32 rkey[8];
	u8 reserved2[4];
पूर्ण;

जोड़ smc_llc_msg अणु
	काष्ठा smc_llc_msg_confirm_link confirm_link;
	काष्ठा smc_llc_msg_add_link add_link;
	काष्ठा smc_llc_msg_add_link_cont add_link_cont;
	काष्ठा smc_llc_msg_del_link delete_link;

	काष्ठा smc_llc_msg_confirm_rkey confirm_rkey;
	काष्ठा smc_llc_msg_delete_rkey delete_rkey;

	काष्ठा smc_llc_msg_test_link test_link;
	काष्ठा अणु
		काष्ठा smc_llc_hdr hdr;
		u8 data[SMC_LLC_DATA_LEN];
	पूर्ण raw;
पूर्ण;

#घोषणा SMC_LLC_FLAG_RESP		0x80

काष्ठा smc_llc_qentry अणु
	काष्ठा list_head list;
	काष्ठा smc_link *link;
	जोड़ smc_llc_msg msg;
पूर्ण;

अटल व्योम smc_llc_enqueue(काष्ठा smc_link *link, जोड़ smc_llc_msg *llc);

काष्ठा smc_llc_qentry *smc_llc_flow_qentry_clr(काष्ठा smc_llc_flow *flow)
अणु
	काष्ठा smc_llc_qentry *qentry = flow->qentry;

	flow->qentry = शून्य;
	वापस qentry;
पूर्ण

व्योम smc_llc_flow_qentry_del(काष्ठा smc_llc_flow *flow)
अणु
	काष्ठा smc_llc_qentry *qentry;

	अगर (flow->qentry) अणु
		qentry = flow->qentry;
		flow->qentry = शून्य;
		kमुक्त(qentry);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम smc_llc_flow_qentry_set(काष्ठा smc_llc_flow *flow,
					   काष्ठा smc_llc_qentry *qentry)
अणु
	flow->qentry = qentry;
पूर्ण

अटल व्योम smc_llc_flow_parallel(काष्ठा smc_link_group *lgr, u8 flow_type,
				  काष्ठा smc_llc_qentry *qentry)
अणु
	u8 msg_type = qentry->msg.raw.hdr.common.type;

	अगर ((msg_type == SMC_LLC_ADD_LINK || msg_type == SMC_LLC_DELETE_LINK) &&
	    flow_type != msg_type && !lgr->delayed_event) अणु
		lgr->delayed_event = qentry;
		वापस;
	पूर्ण
	/* drop parallel or alपढ़ोy-in-progress llc requests */
	अगर (flow_type != msg_type)
		pr_warn_once("smc: SMC-R lg %*phN dropped parallel "
			     "LLC msg: msg %d flow %d role %d\n",
			     SMC_LGR_ID_SIZE, &lgr->id,
			     qentry->msg.raw.hdr.common.type,
			     flow_type, lgr->role);
	kमुक्त(qentry);
पूर्ण

/* try to start a new llc flow, initiated by an incoming llc msg */
अटल bool smc_llc_flow_start(काष्ठा smc_llc_flow *flow,
			       काष्ठा smc_llc_qentry *qentry)
अणु
	काष्ठा smc_link_group *lgr = qentry->link->lgr;

	spin_lock_bh(&lgr->llc_flow_lock);
	अगर (flow->type) अणु
		/* a flow is alपढ़ोy active */
		smc_llc_flow_parallel(lgr, flow->type, qentry);
		spin_unlock_bh(&lgr->llc_flow_lock);
		वापस false;
	पूर्ण
	चयन (qentry->msg.raw.hdr.common.type) अणु
	हाल SMC_LLC_ADD_LINK:
		flow->type = SMC_LLC_FLOW_ADD_LINK;
		अवरोध;
	हाल SMC_LLC_DELETE_LINK:
		flow->type = SMC_LLC_FLOW_DEL_LINK;
		अवरोध;
	हाल SMC_LLC_CONFIRM_RKEY:
	हाल SMC_LLC_DELETE_RKEY:
		flow->type = SMC_LLC_FLOW_RKEY;
		अवरोध;
	शेष:
		flow->type = SMC_LLC_FLOW_NONE;
	पूर्ण
	smc_llc_flow_qentry_set(flow, qentry);
	spin_unlock_bh(&lgr->llc_flow_lock);
	वापस true;
पूर्ण

/* start a new local llc flow, रुको till current flow finished */
पूर्णांक smc_llc_flow_initiate(काष्ठा smc_link_group *lgr,
			  क्रमागत smc_llc_flowtype type)
अणु
	क्रमागत smc_llc_flowtype allowed_remote = SMC_LLC_FLOW_NONE;
	पूर्णांक rc;

	/* all flows except confirm_rkey and delete_rkey are exclusive,
	 * confirm/delete rkey flows can run concurrently (local and remote)
	 */
	अगर (type == SMC_LLC_FLOW_RKEY)
		allowed_remote = SMC_LLC_FLOW_RKEY;
again:
	अगर (list_empty(&lgr->list))
		वापस -ENODEV;
	spin_lock_bh(&lgr->llc_flow_lock);
	अगर (lgr->llc_flow_lcl.type == SMC_LLC_FLOW_NONE &&
	    (lgr->llc_flow_rmt.type == SMC_LLC_FLOW_NONE ||
	     lgr->llc_flow_rmt.type == allowed_remote)) अणु
		lgr->llc_flow_lcl.type = type;
		spin_unlock_bh(&lgr->llc_flow_lock);
		वापस 0;
	पूर्ण
	spin_unlock_bh(&lgr->llc_flow_lock);
	rc = रुको_event_समयout(lgr->llc_flow_रुकोer, (list_empty(&lgr->list) ||
				(lgr->llc_flow_lcl.type == SMC_LLC_FLOW_NONE &&
				 (lgr->llc_flow_rmt.type == SMC_LLC_FLOW_NONE ||
				  lgr->llc_flow_rmt.type == allowed_remote))),
				SMC_LLC_WAIT_TIME * 10);
	अगर (!rc)
		वापस -ETIMEDOUT;
	जाओ again;
पूर्ण

/* finish the current llc flow */
व्योम smc_llc_flow_stop(काष्ठा smc_link_group *lgr, काष्ठा smc_llc_flow *flow)
अणु
	spin_lock_bh(&lgr->llc_flow_lock);
	स_रखो(flow, 0, माप(*flow));
	flow->type = SMC_LLC_FLOW_NONE;
	spin_unlock_bh(&lgr->llc_flow_lock);
	अगर (!list_empty(&lgr->list) && lgr->delayed_event &&
	    flow == &lgr->llc_flow_lcl)
		schedule_work(&lgr->llc_event_work);
	अन्यथा
		wake_up(&lgr->llc_flow_रुकोer);
पूर्ण

/* lnk is optional and used क्रम early wakeup when link goes करोwn, useful in
 * हालs where we रुको क्रम a response on the link after we sent a request
 */
काष्ठा smc_llc_qentry *smc_llc_रुको(काष्ठा smc_link_group *lgr,
				    काष्ठा smc_link *lnk,
				    पूर्णांक समय_out, u8 exp_msg)
अणु
	काष्ठा smc_llc_flow *flow = &lgr->llc_flow_lcl;
	u8 rcv_msg;

	रुको_event_समयout(lgr->llc_msg_रुकोer,
			   (flow->qentry ||
			    (lnk && !smc_link_usable(lnk)) ||
			    list_empty(&lgr->list)),
			   समय_out);
	अगर (!flow->qentry ||
	    (lnk && !smc_link_usable(lnk)) || list_empty(&lgr->list)) अणु
		smc_llc_flow_qentry_del(flow);
		जाओ out;
	पूर्ण
	rcv_msg = flow->qentry->msg.raw.hdr.common.type;
	अगर (exp_msg && rcv_msg != exp_msg) अणु
		अगर (exp_msg == SMC_LLC_ADD_LINK &&
		    rcv_msg == SMC_LLC_DELETE_LINK) अणु
			/* flow_start will delay the unexpected msg */
			smc_llc_flow_start(&lgr->llc_flow_lcl,
					   smc_llc_flow_qentry_clr(flow));
			वापस शून्य;
		पूर्ण
		pr_warn_once("smc: SMC-R lg %*phN dropped unexpected LLC msg: "
			     "msg %d exp %d flow %d role %d flags %x\n",
			     SMC_LGR_ID_SIZE, &lgr->id, rcv_msg, exp_msg,
			     flow->type, lgr->role,
			     flow->qentry->msg.raw.hdr.flags);
		smc_llc_flow_qentry_del(flow);
	पूर्ण
out:
	वापस flow->qentry;
पूर्ण

/********************************** send *************************************/

काष्ठा smc_llc_tx_pend अणु
पूर्ण;

/* handler क्रम send/transmission completion of an LLC msg */
अटल व्योम smc_llc_tx_handler(काष्ठा smc_wr_tx_pend_priv *pend,
			       काष्ठा smc_link *link,
			       क्रमागत ib_wc_status wc_status)
अणु
	/* future work: handle wc_status error क्रम recovery and failover */
पूर्ण

/**
 * smc_llc_add_pending_send() - add LLC control message to pending WQE transmits
 * @link: Poपूर्णांकer to SMC link used क्रम sending LLC control message.
 * @wr_buf: Out variable वापसing poपूर्णांकer to work request payload buffer.
 * @pend: Out variable वापसing poपूर्णांकer to निजी pending WR tracking.
 *	  It's the context the transmit complete handler will get.
 *
 * Reserves and pre-fills an entry क्रम a pending work request send/tx.
 * Used by mid-level smc_llc_send_msg() to prepare क्रम later actual send/tx.
 * Can sleep due to smc_get_ctrl_buf (अगर not in softirq context).
 *
 * Return: 0 on success, otherwise an error value.
 */
अटल पूर्णांक smc_llc_add_pending_send(काष्ठा smc_link *link,
				    काष्ठा smc_wr_buf **wr_buf,
				    काष्ठा smc_wr_tx_pend_priv **pend)
अणु
	पूर्णांक rc;

	rc = smc_wr_tx_get_मुक्त_slot(link, smc_llc_tx_handler, wr_buf, शून्य,
				     pend);
	अगर (rc < 0)
		वापस rc;
	BUILD_BUG_ON_MSG(
		माप(जोड़ smc_llc_msg) > SMC_WR_BUF_SIZE,
		"must increase SMC_WR_BUF_SIZE to at least sizeof(struct smc_llc_msg)");
	BUILD_BUG_ON_MSG(
		माप(जोड़ smc_llc_msg) != SMC_WR_TX_SIZE,
		"must adapt SMC_WR_TX_SIZE to sizeof(struct smc_llc_msg); if not all smc_wr upper layer protocols use the same message size any more, must start to set link->wr_tx_sges[i].length on each individual smc_wr_tx_send()");
	BUILD_BUG_ON_MSG(
		माप(काष्ठा smc_llc_tx_pend) > SMC_WR_TX_PEND_PRIV_SIZE,
		"must increase SMC_WR_TX_PEND_PRIV_SIZE to at least sizeof(struct smc_llc_tx_pend)");
	वापस 0;
पूर्ण

/* high-level API to send LLC confirm link */
पूर्णांक smc_llc_send_confirm_link(काष्ठा smc_link *link,
			      क्रमागत smc_llc_reqresp reqresp)
अणु
	काष्ठा smc_llc_msg_confirm_link *confllc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	confllc = (काष्ठा smc_llc_msg_confirm_link *)wr_buf;
	स_रखो(confllc, 0, माप(*confllc));
	confllc->hd.common.type = SMC_LLC_CONFIRM_LINK;
	confllc->hd.length = माप(काष्ठा smc_llc_msg_confirm_link);
	confllc->hd.flags |= SMC_LLC_FLAG_NO_RMBE_EYEC;
	अगर (reqresp == SMC_LLC_RESP)
		confllc->hd.flags |= SMC_LLC_FLAG_RESP;
	स_नकल(confllc->sender_mac, link->smcibdev->mac[link->ibport - 1],
	       ETH_ALEN);
	स_नकल(confllc->sender_gid, link->gid, SMC_GID_SIZE);
	hton24(confllc->sender_qp_num, link->roce_qp->qp_num);
	confllc->link_num = link->link_id;
	स_नकल(confllc->link_uid, link->link_uid, SMC_LGR_ID_SIZE);
	confllc->max_links = SMC_LLC_ADD_LNK_MAX_LINKS;
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	वापस rc;
पूर्ण

/* send LLC confirm rkey request */
अटल पूर्णांक smc_llc_send_confirm_rkey(काष्ठा smc_link *send_link,
				     काष्ठा smc_buf_desc *rmb_desc)
अणु
	काष्ठा smc_llc_msg_confirm_rkey *rkeyllc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	काष्ठा smc_link *link;
	पूर्णांक i, rc, rtok_ix;

	rc = smc_llc_add_pending_send(send_link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	rkeyllc = (काष्ठा smc_llc_msg_confirm_rkey *)wr_buf;
	स_रखो(rkeyllc, 0, माप(*rkeyllc));
	rkeyllc->hd.common.type = SMC_LLC_CONFIRM_RKEY;
	rkeyllc->hd.length = माप(काष्ठा smc_llc_msg_confirm_rkey);

	rtok_ix = 1;
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		link = &send_link->lgr->lnk[i];
		अगर (smc_link_active(link) && link != send_link) अणु
			rkeyllc->rtoken[rtok_ix].link_id = link->link_id;
			rkeyllc->rtoken[rtok_ix].rmb_key =
				htonl(rmb_desc->mr_rx[link->link_idx]->rkey);
			rkeyllc->rtoken[rtok_ix].rmb_vaddr = cpu_to_be64(
				(u64)sg_dma_address(
					rmb_desc->sgt[link->link_idx].sgl));
			rtok_ix++;
		पूर्ण
	पूर्ण
	/* rkey of send_link is in rtoken[0] */
	rkeyllc->rtoken[0].num_rkeys = rtok_ix - 1;
	rkeyllc->rtoken[0].rmb_key =
		htonl(rmb_desc->mr_rx[send_link->link_idx]->rkey);
	rkeyllc->rtoken[0].rmb_vaddr = cpu_to_be64(
		(u64)sg_dma_address(rmb_desc->sgt[send_link->link_idx].sgl));
	/* send llc message */
	rc = smc_wr_tx_send(send_link, pend);
	वापस rc;
पूर्ण

/* send LLC delete rkey request */
अटल पूर्णांक smc_llc_send_delete_rkey(काष्ठा smc_link *link,
				    काष्ठा smc_buf_desc *rmb_desc)
अणु
	काष्ठा smc_llc_msg_delete_rkey *rkeyllc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	rkeyllc = (काष्ठा smc_llc_msg_delete_rkey *)wr_buf;
	स_रखो(rkeyllc, 0, माप(*rkeyllc));
	rkeyllc->hd.common.type = SMC_LLC_DELETE_RKEY;
	rkeyllc->hd.length = माप(काष्ठा smc_llc_msg_delete_rkey);
	rkeyllc->num_rkeys = 1;
	rkeyllc->rkey[0] = htonl(rmb_desc->mr_rx[link->link_idx]->rkey);
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	वापस rc;
पूर्ण

/* send ADD LINK request or response */
पूर्णांक smc_llc_send_add_link(काष्ठा smc_link *link, u8 mac[], u8 gid[],
			  काष्ठा smc_link *link_new,
			  क्रमागत smc_llc_reqresp reqresp)
अणु
	काष्ठा smc_llc_msg_add_link *addllc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	addllc = (काष्ठा smc_llc_msg_add_link *)wr_buf;

	स_रखो(addllc, 0, माप(*addllc));
	addllc->hd.common.type = SMC_LLC_ADD_LINK;
	addllc->hd.length = माप(काष्ठा smc_llc_msg_add_link);
	अगर (reqresp == SMC_LLC_RESP)
		addllc->hd.flags |= SMC_LLC_FLAG_RESP;
	स_नकल(addllc->sender_mac, mac, ETH_ALEN);
	स_नकल(addllc->sender_gid, gid, SMC_GID_SIZE);
	अगर (link_new) अणु
		addllc->link_num = link_new->link_id;
		hton24(addllc->sender_qp_num, link_new->roce_qp->qp_num);
		hton24(addllc->initial_psn, link_new->psn_initial);
		अगर (reqresp == SMC_LLC_REQ)
			addllc->qp_mtu = link_new->path_mtu;
		अन्यथा
			addllc->qp_mtu = min(link_new->path_mtu,
					     link_new->peer_mtu);
	पूर्ण
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	वापस rc;
पूर्ण

/* send DELETE LINK request or response */
पूर्णांक smc_llc_send_delete_link(काष्ठा smc_link *link, u8 link_del_id,
			     क्रमागत smc_llc_reqresp reqresp, bool orderly,
			     u32 reason)
अणु
	काष्ठा smc_llc_msg_del_link *delllc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	delllc = (काष्ठा smc_llc_msg_del_link *)wr_buf;

	स_रखो(delllc, 0, माप(*delllc));
	delllc->hd.common.type = SMC_LLC_DELETE_LINK;
	delllc->hd.length = माप(काष्ठा smc_llc_msg_del_link);
	अगर (reqresp == SMC_LLC_RESP)
		delllc->hd.flags |= SMC_LLC_FLAG_RESP;
	अगर (orderly)
		delllc->hd.flags |= SMC_LLC_FLAG_DEL_LINK_ORDERLY;
	अगर (link_del_id)
		delllc->link_num = link_del_id;
	अन्यथा
		delllc->hd.flags |= SMC_LLC_FLAG_DEL_LINK_ALL;
	delllc->reason = htonl(reason);
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	वापस rc;
पूर्ण

/* send LLC test link request */
अटल पूर्णांक smc_llc_send_test_link(काष्ठा smc_link *link, u8 user_data[16])
अणु
	काष्ठा smc_llc_msg_test_link *testllc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	testllc = (काष्ठा smc_llc_msg_test_link *)wr_buf;
	स_रखो(testllc, 0, माप(*testllc));
	testllc->hd.common.type = SMC_LLC_TEST_LINK;
	testllc->hd.length = माप(काष्ठा smc_llc_msg_test_link);
	स_नकल(testllc->user_data, user_data, माप(testllc->user_data));
	/* send llc message */
	rc = smc_wr_tx_send(link, pend);
	वापस rc;
पूर्ण

/* schedule an llc send on link, may रुको क्रम buffers */
अटल पूर्णांक smc_llc_send_message(काष्ठा smc_link *link, व्योम *llcbuf)
अणु
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	अगर (!smc_link_usable(link))
		वापस -ENOLINK;
	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	स_नकल(wr_buf, llcbuf, माप(जोड़ smc_llc_msg));
	वापस smc_wr_tx_send(link, pend);
पूर्ण

/* schedule an llc send on link, may रुको क्रम buffers,
 * and रुको क्रम send completion notअगरication.
 * @वापस 0 on success
 */
अटल पूर्णांक smc_llc_send_message_रुको(काष्ठा smc_link *link, व्योम *llcbuf)
अणु
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	अगर (!smc_link_usable(link))
		वापस -ENOLINK;
	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	स_नकल(wr_buf, llcbuf, माप(जोड़ smc_llc_msg));
	वापस smc_wr_tx_send_रुको(link, pend, SMC_LLC_WAIT_TIME);
पूर्ण

/********************************* receive ***********************************/

अटल पूर्णांक smc_llc_alloc_alt_link(काष्ठा smc_link_group *lgr,
				  क्रमागत smc_lgr_type lgr_new_t)
अणु
	पूर्णांक i;

	अगर (lgr->type == SMC_LGR_SYMMETRIC ||
	    (lgr->type != SMC_LGR_SINGLE &&
	     (lgr_new_t == SMC_LGR_ASYMMETRIC_LOCAL ||
	      lgr_new_t == SMC_LGR_ASYMMETRIC_PEER)))
		वापस -EMLINK;

	अगर (lgr_new_t == SMC_LGR_ASYMMETRIC_LOCAL ||
	    lgr_new_t == SMC_LGR_ASYMMETRIC_PEER) अणु
		क्रम (i = SMC_LINKS_PER_LGR_MAX - 1; i >= 0; i--)
			अगर (lgr->lnk[i].state == SMC_LNK_UNUSED)
				वापस i;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++)
			अगर (lgr->lnk[i].state == SMC_LNK_UNUSED)
				वापस i;
	पूर्ण
	वापस -EMLINK;
पूर्ण

/* वापस first buffer from any of the next buf lists */
अटल काष्ठा smc_buf_desc *_smc_llc_get_next_rmb(काष्ठा smc_link_group *lgr,
						  पूर्णांक *buf_lst)
अणु
	काष्ठा smc_buf_desc *buf_pos;

	जबतक (*buf_lst < SMC_RMBE_SIZES) अणु
		buf_pos = list_first_entry_or_null(&lgr->rmbs[*buf_lst],
						   काष्ठा smc_buf_desc, list);
		अगर (buf_pos)
			वापस buf_pos;
		(*buf_lst)++;
	पूर्ण
	वापस शून्य;
पूर्ण

/* वापस next rmb from buffer lists */
अटल काष्ठा smc_buf_desc *smc_llc_get_next_rmb(काष्ठा smc_link_group *lgr,
						 पूर्णांक *buf_lst,
						 काष्ठा smc_buf_desc *buf_pos)
अणु
	काष्ठा smc_buf_desc *buf_next;

	अगर (!buf_pos || list_is_last(&buf_pos->list, &lgr->rmbs[*buf_lst])) अणु
		(*buf_lst)++;
		वापस _smc_llc_get_next_rmb(lgr, buf_lst);
	पूर्ण
	buf_next = list_next_entry(buf_pos, list);
	वापस buf_next;
पूर्ण

अटल काष्ठा smc_buf_desc *smc_llc_get_first_rmb(काष्ठा smc_link_group *lgr,
						  पूर्णांक *buf_lst)
अणु
	*buf_lst = 0;
	वापस smc_llc_get_next_rmb(lgr, buf_lst, शून्य);
पूर्ण

/* send one add_link_जारी msg */
अटल पूर्णांक smc_llc_add_link_cont(काष्ठा smc_link *link,
				 काष्ठा smc_link *link_new, u8 *num_rkeys_toकरो,
				 पूर्णांक *buf_lst, काष्ठा smc_buf_desc **buf_pos)
अणु
	काष्ठा smc_llc_msg_add_link_cont *addc_llc;
	काष्ठा smc_link_group *lgr = link->lgr;
	पूर्णांक prim_lnk_idx, lnk_idx, i, rc;
	काष्ठा smc_wr_tx_pend_priv *pend;
	काष्ठा smc_wr_buf *wr_buf;
	काष्ठा smc_buf_desc *rmb;
	u8 n;

	rc = smc_llc_add_pending_send(link, &wr_buf, &pend);
	अगर (rc)
		वापस rc;
	addc_llc = (काष्ठा smc_llc_msg_add_link_cont *)wr_buf;
	स_रखो(addc_llc, 0, माप(*addc_llc));

	prim_lnk_idx = link->link_idx;
	lnk_idx = link_new->link_idx;
	addc_llc->link_num = link_new->link_id;
	addc_llc->num_rkeys = *num_rkeys_toकरो;
	n = *num_rkeys_toकरो;
	क्रम (i = 0; i < min_t(u8, n, SMC_LLC_RKEYS_PER_CONT_MSG); i++) अणु
		अगर (!*buf_pos) अणु
			addc_llc->num_rkeys = addc_llc->num_rkeys -
					      *num_rkeys_toकरो;
			*num_rkeys_toकरो = 0;
			अवरोध;
		पूर्ण
		rmb = *buf_pos;

		addc_llc->rt[i].rmb_key = htonl(rmb->mr_rx[prim_lnk_idx]->rkey);
		addc_llc->rt[i].rmb_key_new = htonl(rmb->mr_rx[lnk_idx]->rkey);
		addc_llc->rt[i].rmb_vaddr_new =
			cpu_to_be64((u64)sg_dma_address(rmb->sgt[lnk_idx].sgl));

		(*num_rkeys_toकरो)--;
		*buf_pos = smc_llc_get_next_rmb(lgr, buf_lst, *buf_pos);
		जबतक (*buf_pos && !(*buf_pos)->used)
			*buf_pos = smc_llc_get_next_rmb(lgr, buf_lst, *buf_pos);
	पूर्ण
	addc_llc->hd.common.type = SMC_LLC_ADD_LINK_CONT;
	addc_llc->hd.length = माप(काष्ठा smc_llc_msg_add_link_cont);
	अगर (lgr->role == SMC_CLNT)
		addc_llc->hd.flags |= SMC_LLC_FLAG_RESP;
	वापस smc_wr_tx_send(link, pend);
पूर्ण

अटल पूर्णांक smc_llc_cli_rkey_exchange(काष्ठा smc_link *link,
				     काष्ठा smc_link *link_new)
अणु
	काष्ठा smc_llc_msg_add_link_cont *addc_llc;
	काष्ठा smc_link_group *lgr = link->lgr;
	u8 max, num_rkeys_send, num_rkeys_recv;
	काष्ठा smc_llc_qentry *qentry;
	काष्ठा smc_buf_desc *buf_pos;
	पूर्णांक buf_lst;
	पूर्णांक rc = 0;
	पूर्णांक i;

	mutex_lock(&lgr->rmbs_lock);
	num_rkeys_send = lgr->conns_num;
	buf_pos = smc_llc_get_first_rmb(lgr, &buf_lst);
	करो अणु
		qentry = smc_llc_रुको(lgr, शून्य, SMC_LLC_WAIT_TIME,
				      SMC_LLC_ADD_LINK_CONT);
		अगर (!qentry) अणु
			rc = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		addc_llc = &qentry->msg.add_link_cont;
		num_rkeys_recv = addc_llc->num_rkeys;
		max = min_t(u8, num_rkeys_recv, SMC_LLC_RKEYS_PER_CONT_MSG);
		क्रम (i = 0; i < max; i++) अणु
			smc_rtoken_set(lgr, link->link_idx, link_new->link_idx,
				       addc_llc->rt[i].rmb_key,
				       addc_llc->rt[i].rmb_vaddr_new,
				       addc_llc->rt[i].rmb_key_new);
			num_rkeys_recv--;
		पूर्ण
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		rc = smc_llc_add_link_cont(link, link_new, &num_rkeys_send,
					   &buf_lst, &buf_pos);
		अगर (rc)
			अवरोध;
	पूर्ण जबतक (num_rkeys_send || num_rkeys_recv);

	mutex_unlock(&lgr->rmbs_lock);
	वापस rc;
पूर्ण

/* prepare and send an add link reject response */
अटल पूर्णांक smc_llc_cli_add_link_reject(काष्ठा smc_llc_qentry *qentry)
अणु
	qentry->msg.raw.hdr.flags |= SMC_LLC_FLAG_RESP;
	qentry->msg.raw.hdr.flags |= SMC_LLC_FLAG_ADD_LNK_REJ;
	qentry->msg.raw.hdr.add_link_rej_rsn = SMC_LLC_REJ_RSN_NO_ALT_PATH;
	वापस smc_llc_send_message(qentry->link, &qentry->msg);
पूर्ण

अटल पूर्णांक smc_llc_cli_conf_link(काष्ठा smc_link *link,
				 काष्ठा smc_init_info *ini,
				 काष्ठा smc_link *link_new,
				 क्रमागत smc_lgr_type lgr_new_t)
अणु
	काष्ठा smc_link_group *lgr = link->lgr;
	काष्ठा smc_llc_qentry *qentry = शून्य;
	पूर्णांक rc = 0;

	/* receive CONFIRM LINK request over RoCE fabric */
	qentry = smc_llc_रुको(lgr, शून्य, SMC_LLC_WAIT_FIRST_TIME, 0);
	अगर (!qentry) अणु
		rc = smc_llc_send_delete_link(link, link_new->link_id,
					      SMC_LLC_REQ, false,
					      SMC_LLC_DEL_LOST_PATH);
		वापस -ENOLINK;
	पूर्ण
	अगर (qentry->msg.raw.hdr.common.type != SMC_LLC_CONFIRM_LINK) अणु
		/* received DELETE_LINK instead */
		qentry->msg.raw.hdr.flags |= SMC_LLC_FLAG_RESP;
		smc_llc_send_message(link, &qentry->msg);
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		वापस -ENOLINK;
	पूर्ण
	smc_llc_save_peer_uid(qentry);
	smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);

	rc = smc_ib_modअगरy_qp_rts(link_new);
	अगर (rc) अणु
		smc_llc_send_delete_link(link, link_new->link_id, SMC_LLC_REQ,
					 false, SMC_LLC_DEL_LOST_PATH);
		वापस -ENOLINK;
	पूर्ण
	smc_wr_remember_qp_attr(link_new);

	rc = smcr_buf_reg_lgr(link_new);
	अगर (rc) अणु
		smc_llc_send_delete_link(link, link_new->link_id, SMC_LLC_REQ,
					 false, SMC_LLC_DEL_LOST_PATH);
		वापस -ENOLINK;
	पूर्ण

	/* send CONFIRM LINK response over RoCE fabric */
	rc = smc_llc_send_confirm_link(link_new, SMC_LLC_RESP);
	अगर (rc) अणु
		smc_llc_send_delete_link(link, link_new->link_id, SMC_LLC_REQ,
					 false, SMC_LLC_DEL_LOST_PATH);
		वापस -ENOLINK;
	पूर्ण
	smc_llc_link_active(link_new);
	अगर (lgr_new_t == SMC_LGR_ASYMMETRIC_LOCAL ||
	    lgr_new_t == SMC_LGR_ASYMMETRIC_PEER)
		smcr_lgr_set_type_asym(lgr, lgr_new_t, link_new->link_idx);
	अन्यथा
		smcr_lgr_set_type(lgr, lgr_new_t);
	वापस 0;
पूर्ण

अटल व्योम smc_llc_save_add_link_info(काष्ठा smc_link *link,
				       काष्ठा smc_llc_msg_add_link *add_llc)
अणु
	link->peer_qpn = ntoh24(add_llc->sender_qp_num);
	स_नकल(link->peer_gid, add_llc->sender_gid, SMC_GID_SIZE);
	स_नकल(link->peer_mac, add_llc->sender_mac, ETH_ALEN);
	link->peer_psn = ntoh24(add_llc->initial_psn);
	link->peer_mtu = add_llc->qp_mtu;
पूर्ण

/* as an SMC client, process an add link request */
पूर्णांक smc_llc_cli_add_link(काष्ठा smc_link *link, काष्ठा smc_llc_qentry *qentry)
अणु
	काष्ठा smc_llc_msg_add_link *llc = &qentry->msg.add_link;
	क्रमागत smc_lgr_type lgr_new_t = SMC_LGR_SYMMETRIC;
	काष्ठा smc_link_group *lgr = smc_get_lgr(link);
	काष्ठा smc_link *lnk_new = शून्य;
	काष्ठा smc_init_info ini;
	पूर्णांक lnk_idx, rc = 0;

	अगर (!llc->qp_mtu)
		जाओ out_reject;

	ini.vlan_id = lgr->vlan_id;
	smc_pnet_find_alt_roce(lgr, &ini, link->smcibdev);
	अगर (!स_भेद(llc->sender_gid, link->peer_gid, SMC_GID_SIZE) &&
	    !स_भेद(llc->sender_mac, link->peer_mac, ETH_ALEN)) अणु
		अगर (!ini.ib_dev)
			जाओ out_reject;
		lgr_new_t = SMC_LGR_ASYMMETRIC_PEER;
	पूर्ण
	अगर (!ini.ib_dev) अणु
		lgr_new_t = SMC_LGR_ASYMMETRIC_LOCAL;
		ini.ib_dev = link->smcibdev;
		ini.ib_port = link->ibport;
	पूर्ण
	lnk_idx = smc_llc_alloc_alt_link(lgr, lgr_new_t);
	अगर (lnk_idx < 0)
		जाओ out_reject;
	lnk_new = &lgr->lnk[lnk_idx];
	rc = smcr_link_init(lgr, lnk_new, lnk_idx, &ini);
	अगर (rc)
		जाओ out_reject;
	smc_llc_save_add_link_info(lnk_new, llc);
	lnk_new->link_id = llc->link_num;	/* SMC server assigns link id */
	smc_llc_link_set_uid(lnk_new);

	rc = smc_ib_पढ़ोy_link(lnk_new);
	अगर (rc)
		जाओ out_clear_lnk;

	rc = smcr_buf_map_lgr(lnk_new);
	अगर (rc)
		जाओ out_clear_lnk;

	rc = smc_llc_send_add_link(link,
				   lnk_new->smcibdev->mac[ini.ib_port - 1],
				   lnk_new->gid, lnk_new, SMC_LLC_RESP);
	अगर (rc)
		जाओ out_clear_lnk;
	rc = smc_llc_cli_rkey_exchange(link, lnk_new);
	अगर (rc) अणु
		rc = 0;
		जाओ out_clear_lnk;
	पूर्ण
	rc = smc_llc_cli_conf_link(link, &ini, lnk_new, lgr_new_t);
	अगर (!rc)
		जाओ out;
out_clear_lnk:
	smcr_link_clear(lnk_new, false);
out_reject:
	smc_llc_cli_add_link_reject(qentry);
out:
	kमुक्त(qentry);
	वापस rc;
पूर्ण

/* as an SMC client, invite server to start the add_link processing */
अटल व्योम smc_llc_cli_add_link_invite(काष्ठा smc_link *link,
					काष्ठा smc_llc_qentry *qentry)
अणु
	काष्ठा smc_link_group *lgr = smc_get_lgr(link);
	काष्ठा smc_init_info ini;

	अगर (lgr->type == SMC_LGR_SYMMETRIC ||
	    lgr->type == SMC_LGR_ASYMMETRIC_PEER)
		जाओ out;

	ini.vlan_id = lgr->vlan_id;
	smc_pnet_find_alt_roce(lgr, &ini, link->smcibdev);
	अगर (!ini.ib_dev)
		जाओ out;

	smc_llc_send_add_link(link, ini.ib_dev->mac[ini.ib_port - 1],
			      ini.ib_gid, शून्य, SMC_LLC_REQ);
out:
	kमुक्त(qentry);
पूर्ण

अटल bool smc_llc_is_empty_llc_message(जोड़ smc_llc_msg *llc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(llc->raw.data); i++)
		अगर (llc->raw.data[i])
			वापस false;
	वापस true;
पूर्ण

अटल bool smc_llc_is_local_add_link(जोड़ smc_llc_msg *llc)
अणु
	अगर (llc->raw.hdr.common.type == SMC_LLC_ADD_LINK &&
	    smc_llc_is_empty_llc_message(llc))
		वापस true;
	वापस false;
पूर्ण

अटल व्योम smc_llc_process_cli_add_link(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_llc_qentry *qentry;

	qentry = smc_llc_flow_qentry_clr(&lgr->llc_flow_lcl);

	mutex_lock(&lgr->llc_conf_mutex);
	अगर (smc_llc_is_local_add_link(&qentry->msg))
		smc_llc_cli_add_link_invite(qentry->link, qentry);
	अन्यथा
		smc_llc_cli_add_link(qentry->link, qentry);
	mutex_unlock(&lgr->llc_conf_mutex);
पूर्ण

अटल पूर्णांक smc_llc_active_link_count(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक i, link_count = 0;

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_active(&lgr->lnk[i]))
			जारी;
		link_count++;
	पूर्ण
	वापस link_count;
पूर्ण

/* find the asymmetric link when 3 links are established  */
अटल काष्ठा smc_link *smc_llc_find_asym_link(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक asym_idx = -ENOENT;
	पूर्णांक i, j, k;
	bool found;

	/* determine asymmetric link */
	found = false;
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		क्रम (j = i + 1; j < SMC_LINKS_PER_LGR_MAX; j++) अणु
			अगर (!smc_link_usable(&lgr->lnk[i]) ||
			    !smc_link_usable(&lgr->lnk[j]))
				जारी;
			अगर (!स_भेद(lgr->lnk[i].gid, lgr->lnk[j].gid,
				    SMC_GID_SIZE)) अणु
				found = true;	/* asym_lnk is i or j */
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (found)
			अवरोध;
	पूर्ण
	अगर (!found)
		जाओ out; /* no asymmetric link */
	क्रम (k = 0; k < SMC_LINKS_PER_LGR_MAX; k++) अणु
		अगर (!smc_link_usable(&lgr->lnk[k]))
			जारी;
		अगर (k != i &&
		    !स_भेद(lgr->lnk[i].peer_gid, lgr->lnk[k].peer_gid,
			    SMC_GID_SIZE)) अणु
			asym_idx = i;
			अवरोध;
		पूर्ण
		अगर (k != j &&
		    !स_भेद(lgr->lnk[j].peer_gid, lgr->lnk[k].peer_gid,
			    SMC_GID_SIZE)) अणु
			asym_idx = j;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस (asym_idx < 0) ? शून्य : &lgr->lnk[asym_idx];
पूर्ण

अटल व्योम smc_llc_delete_asym_link(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_link *lnk_new = शून्य, *lnk_asym;
	काष्ठा smc_llc_qentry *qentry;
	पूर्णांक rc;

	lnk_asym = smc_llc_find_asym_link(lgr);
	अगर (!lnk_asym)
		वापस; /* no asymmetric link */
	अगर (!smc_link_करोwning(&lnk_asym->state))
		वापस;
	lnk_new = smc_चयन_conns(lgr, lnk_asym, false);
	smc_wr_tx_रुको_no_pending_sends(lnk_asym);
	अगर (!lnk_new)
		जाओ out_मुक्त;
	/* change flow type from ADD_LINK पूर्णांकo DEL_LINK */
	lgr->llc_flow_lcl.type = SMC_LLC_FLOW_DEL_LINK;
	rc = smc_llc_send_delete_link(lnk_new, lnk_asym->link_id, SMC_LLC_REQ,
				      true, SMC_LLC_DEL_NO_ASYM_NEEDED);
	अगर (rc) अणु
		smcr_link_करोwn_cond(lnk_new);
		जाओ out_मुक्त;
	पूर्ण
	qentry = smc_llc_रुको(lgr, lnk_new, SMC_LLC_WAIT_TIME,
			      SMC_LLC_DELETE_LINK);
	अगर (!qentry) अणु
		smcr_link_करोwn_cond(lnk_new);
		जाओ out_मुक्त;
	पूर्ण
	smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
out_मुक्त:
	smcr_link_clear(lnk_asym, true);
पूर्ण

अटल पूर्णांक smc_llc_srv_rkey_exchange(काष्ठा smc_link *link,
				     काष्ठा smc_link *link_new)
अणु
	काष्ठा smc_llc_msg_add_link_cont *addc_llc;
	काष्ठा smc_link_group *lgr = link->lgr;
	u8 max, num_rkeys_send, num_rkeys_recv;
	काष्ठा smc_llc_qentry *qentry = शून्य;
	काष्ठा smc_buf_desc *buf_pos;
	पूर्णांक buf_lst;
	पूर्णांक rc = 0;
	पूर्णांक i;

	mutex_lock(&lgr->rmbs_lock);
	num_rkeys_send = lgr->conns_num;
	buf_pos = smc_llc_get_first_rmb(lgr, &buf_lst);
	करो अणु
		smc_llc_add_link_cont(link, link_new, &num_rkeys_send,
				      &buf_lst, &buf_pos);
		qentry = smc_llc_रुको(lgr, link, SMC_LLC_WAIT_TIME,
				      SMC_LLC_ADD_LINK_CONT);
		अगर (!qentry) अणु
			rc = -ETIMEDOUT;
			जाओ out;
		पूर्ण
		addc_llc = &qentry->msg.add_link_cont;
		num_rkeys_recv = addc_llc->num_rkeys;
		max = min_t(u8, num_rkeys_recv, SMC_LLC_RKEYS_PER_CONT_MSG);
		क्रम (i = 0; i < max; i++) अणु
			smc_rtoken_set(lgr, link->link_idx, link_new->link_idx,
				       addc_llc->rt[i].rmb_key,
				       addc_llc->rt[i].rmb_vaddr_new,
				       addc_llc->rt[i].rmb_key_new);
			num_rkeys_recv--;
		पूर्ण
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
	पूर्ण जबतक (num_rkeys_send || num_rkeys_recv);
out:
	mutex_unlock(&lgr->rmbs_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_llc_srv_conf_link(काष्ठा smc_link *link,
				 काष्ठा smc_link *link_new,
				 क्रमागत smc_lgr_type lgr_new_t)
अणु
	काष्ठा smc_link_group *lgr = link->lgr;
	काष्ठा smc_llc_qentry *qentry = शून्य;
	पूर्णांक rc;

	/* send CONFIRM LINK request over the RoCE fabric */
	rc = smc_llc_send_confirm_link(link_new, SMC_LLC_REQ);
	अगर (rc)
		वापस -ENOLINK;
	/* receive CONFIRM LINK response over the RoCE fabric */
	qentry = smc_llc_रुको(lgr, link, SMC_LLC_WAIT_FIRST_TIME, 0);
	अगर (!qentry ||
	    qentry->msg.raw.hdr.common.type != SMC_LLC_CONFIRM_LINK) अणु
		/* send DELETE LINK */
		smc_llc_send_delete_link(link, link_new->link_id, SMC_LLC_REQ,
					 false, SMC_LLC_DEL_LOST_PATH);
		अगर (qentry)
			smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		वापस -ENOLINK;
	पूर्ण
	smc_llc_save_peer_uid(qentry);
	smc_llc_link_active(link_new);
	अगर (lgr_new_t == SMC_LGR_ASYMMETRIC_LOCAL ||
	    lgr_new_t == SMC_LGR_ASYMMETRIC_PEER)
		smcr_lgr_set_type_asym(lgr, lgr_new_t, link_new->link_idx);
	अन्यथा
		smcr_lgr_set_type(lgr, lgr_new_t);
	smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
	वापस 0;
पूर्ण

पूर्णांक smc_llc_srv_add_link(काष्ठा smc_link *link)
अणु
	क्रमागत smc_lgr_type lgr_new_t = SMC_LGR_SYMMETRIC;
	काष्ठा smc_link_group *lgr = link->lgr;
	काष्ठा smc_llc_msg_add_link *add_llc;
	काष्ठा smc_llc_qentry *qentry = शून्य;
	काष्ठा smc_link *link_new;
	काष्ठा smc_init_info ini;
	पूर्णांक lnk_idx, rc = 0;

	/* ignore client add link recommendation, start new flow */
	ini.vlan_id = lgr->vlan_id;
	smc_pnet_find_alt_roce(lgr, &ini, link->smcibdev);
	अगर (!ini.ib_dev) अणु
		lgr_new_t = SMC_LGR_ASYMMETRIC_LOCAL;
		ini.ib_dev = link->smcibdev;
		ini.ib_port = link->ibport;
	पूर्ण
	lnk_idx = smc_llc_alloc_alt_link(lgr, lgr_new_t);
	अगर (lnk_idx < 0)
		वापस 0;

	rc = smcr_link_init(lgr, &lgr->lnk[lnk_idx], lnk_idx, &ini);
	अगर (rc)
		वापस rc;
	link_new = &lgr->lnk[lnk_idx];
	rc = smc_llc_send_add_link(link,
				   link_new->smcibdev->mac[ini.ib_port - 1],
				   link_new->gid, link_new, SMC_LLC_REQ);
	अगर (rc)
		जाओ out_err;
	/* receive ADD LINK response over the RoCE fabric */
	qentry = smc_llc_रुको(lgr, link, SMC_LLC_WAIT_TIME, SMC_LLC_ADD_LINK);
	अगर (!qentry) अणु
		rc = -ETIMEDOUT;
		जाओ out_err;
	पूर्ण
	add_llc = &qentry->msg.add_link;
	अगर (add_llc->hd.flags & SMC_LLC_FLAG_ADD_LNK_REJ) अणु
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		rc = -ENOLINK;
		जाओ out_err;
	पूर्ण
	अगर (lgr->type == SMC_LGR_SINGLE &&
	    (!स_भेद(add_llc->sender_gid, link->peer_gid, SMC_GID_SIZE) &&
	     !स_भेद(add_llc->sender_mac, link->peer_mac, ETH_ALEN))) अणु
		lgr_new_t = SMC_LGR_ASYMMETRIC_PEER;
	पूर्ण
	smc_llc_save_add_link_info(link_new, add_llc);
	smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);

	rc = smc_ib_पढ़ोy_link(link_new);
	अगर (rc)
		जाओ out_err;
	rc = smcr_buf_map_lgr(link_new);
	अगर (rc)
		जाओ out_err;
	rc = smcr_buf_reg_lgr(link_new);
	अगर (rc)
		जाओ out_err;
	rc = smc_llc_srv_rkey_exchange(link, link_new);
	अगर (rc)
		जाओ out_err;
	rc = smc_llc_srv_conf_link(link, link_new, lgr_new_t);
	अगर (rc)
		जाओ out_err;
	वापस 0;
out_err:
	smcr_link_clear(link_new, false);
	वापस rc;
पूर्ण

अटल व्योम smc_llc_process_srv_add_link(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_link *link = lgr->llc_flow_lcl.qentry->link;
	पूर्णांक rc;

	smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);

	mutex_lock(&lgr->llc_conf_mutex);
	rc = smc_llc_srv_add_link(link);
	अगर (!rc && lgr->type == SMC_LGR_SYMMETRIC) अणु
		/* delete any asymmetric link */
		smc_llc_delete_asym_link(lgr);
	पूर्ण
	mutex_unlock(&lgr->llc_conf_mutex);
पूर्ण

/* enqueue a local add_link req to trigger a new add_link flow */
व्योम smc_llc_add_link_local(काष्ठा smc_link *link)
अणु
	काष्ठा smc_llc_msg_add_link add_llc = अणुपूर्ण;

	add_llc.hd.length = माप(add_llc);
	add_llc.hd.common.type = SMC_LLC_ADD_LINK;
	/* no dev and port needed */
	smc_llc_enqueue(link, (जोड़ smc_llc_msg *)&add_llc);
पूर्ण

/* worker to process an add link message */
अटल व्योम smc_llc_add_link_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link_group *lgr = container_of(work, काष्ठा smc_link_group,
						  llc_add_link_work);

	अगर (list_empty(&lgr->list)) अणु
		/* link group is terminating */
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		जाओ out;
	पूर्ण

	अगर (lgr->role == SMC_CLNT)
		smc_llc_process_cli_add_link(lgr);
	अन्यथा
		smc_llc_process_srv_add_link(lgr);
out:
	smc_llc_flow_stop(lgr, &lgr->llc_flow_lcl);
पूर्ण

/* enqueue a local del_link msg to trigger a new del_link flow,
 * called only क्रम role SMC_SERV
 */
व्योम smc_llc_srv_delete_link_local(काष्ठा smc_link *link, u8 del_link_id)
अणु
	काष्ठा smc_llc_msg_del_link del_llc = अणुपूर्ण;

	del_llc.hd.length = माप(del_llc);
	del_llc.hd.common.type = SMC_LLC_DELETE_LINK;
	del_llc.link_num = del_link_id;
	del_llc.reason = htonl(SMC_LLC_DEL_LOST_PATH);
	del_llc.hd.flags |= SMC_LLC_FLAG_DEL_LINK_ORDERLY;
	smc_llc_enqueue(link, (जोड़ smc_llc_msg *)&del_llc);
पूर्ण

अटल व्योम smc_llc_process_cli_delete_link(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_link *lnk_del = शून्य, *lnk_asym, *lnk;
	काष्ठा smc_llc_msg_del_link *del_llc;
	काष्ठा smc_llc_qentry *qentry;
	पूर्णांक active_links;
	पूर्णांक lnk_idx;

	qentry = smc_llc_flow_qentry_clr(&lgr->llc_flow_lcl);
	lnk = qentry->link;
	del_llc = &qentry->msg.delete_link;

	अगर (del_llc->hd.flags & SMC_LLC_FLAG_DEL_LINK_ALL) अणु
		smc_lgr_terminate_sched(lgr);
		जाओ out;
	पूर्ण
	mutex_lock(&lgr->llc_conf_mutex);
	/* delete single link */
	क्रम (lnk_idx = 0; lnk_idx < SMC_LINKS_PER_LGR_MAX; lnk_idx++) अणु
		अगर (lgr->lnk[lnk_idx].link_id != del_llc->link_num)
			जारी;
		lnk_del = &lgr->lnk[lnk_idx];
		अवरोध;
	पूर्ण
	del_llc->hd.flags |= SMC_LLC_FLAG_RESP;
	अगर (!lnk_del) अणु
		/* link was not found */
		del_llc->reason = htonl(SMC_LLC_DEL_NOLNK);
		smc_llc_send_message(lnk, &qentry->msg);
		जाओ out_unlock;
	पूर्ण
	lnk_asym = smc_llc_find_asym_link(lgr);

	del_llc->reason = 0;
	smc_llc_send_message(lnk, &qentry->msg); /* response */

	अगर (smc_link_करोwning(&lnk_del->state)) अणु
		अगर (smc_चयन_conns(lgr, lnk_del, false))
			smc_wr_tx_रुको_no_pending_sends(lnk_del);
	पूर्ण
	smcr_link_clear(lnk_del, true);

	active_links = smc_llc_active_link_count(lgr);
	अगर (lnk_del == lnk_asym) अणु
		/* expected deletion of asym link, करोn't change lgr state */
	पूर्ण अन्यथा अगर (active_links == 1) अणु
		smcr_lgr_set_type(lgr, SMC_LGR_SINGLE);
	पूर्ण अन्यथा अगर (!active_links) अणु
		smcr_lgr_set_type(lgr, SMC_LGR_NONE);
		smc_lgr_terminate_sched(lgr);
	पूर्ण
out_unlock:
	mutex_unlock(&lgr->llc_conf_mutex);
out:
	kमुक्त(qentry);
पूर्ण

/* try to send a DELETE LINK ALL request on any active link,
 * रुकोing क्रम send completion
 */
व्योम smc_llc_send_link_delete_all(काष्ठा smc_link_group *lgr, bool ord, u32 rsn)
अणु
	काष्ठा smc_llc_msg_del_link delllc = अणुपूर्ण;
	पूर्णांक i;

	delllc.hd.common.type = SMC_LLC_DELETE_LINK;
	delllc.hd.length = माप(delllc);
	अगर (ord)
		delllc.hd.flags |= SMC_LLC_FLAG_DEL_LINK_ORDERLY;
	delllc.hd.flags |= SMC_LLC_FLAG_DEL_LINK_ALL;
	delllc.reason = htonl(rsn);

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_usable(&lgr->lnk[i]))
			जारी;
		अगर (!smc_llc_send_message_रुको(&lgr->lnk[i], &delllc))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम smc_llc_process_srv_delete_link(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_llc_msg_del_link *del_llc;
	काष्ठा smc_link *lnk, *lnk_del;
	काष्ठा smc_llc_qentry *qentry;
	पूर्णांक active_links;
	पूर्णांक i;

	mutex_lock(&lgr->llc_conf_mutex);
	qentry = smc_llc_flow_qentry_clr(&lgr->llc_flow_lcl);
	lnk = qentry->link;
	del_llc = &qentry->msg.delete_link;

	अगर (qentry->msg.delete_link.hd.flags & SMC_LLC_FLAG_DEL_LINK_ALL) अणु
		/* delete entire lgr */
		smc_llc_send_link_delete_all(lgr, true, ntohl(
					      qentry->msg.delete_link.reason));
		smc_lgr_terminate_sched(lgr);
		जाओ out;
	पूर्ण
	/* delete single link */
	lnk_del = शून्य;
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (lgr->lnk[i].link_id == del_llc->link_num) अणु
			lnk_del = &lgr->lnk[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!lnk_del)
		जाओ out; /* asymmetric link alपढ़ोy deleted */

	अगर (smc_link_करोwning(&lnk_del->state)) अणु
		अगर (smc_चयन_conns(lgr, lnk_del, false))
			smc_wr_tx_रुको_no_pending_sends(lnk_del);
	पूर्ण
	अगर (!list_empty(&lgr->list)) अणु
		/* qentry is either a request from peer (send it back to
		 * initiate the DELETE_LINK processing), or a locally
		 * enqueued DELETE_LINK request (क्रमward it)
		 */
		अगर (!smc_llc_send_message(lnk, &qentry->msg)) अणु
			काष्ठा smc_llc_qentry *qentry2;

			qentry2 = smc_llc_रुको(lgr, lnk, SMC_LLC_WAIT_TIME,
					       SMC_LLC_DELETE_LINK);
			अगर (qentry2)
				smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		पूर्ण
	पूर्ण
	smcr_link_clear(lnk_del, true);

	active_links = smc_llc_active_link_count(lgr);
	अगर (active_links == 1) अणु
		smcr_lgr_set_type(lgr, SMC_LGR_SINGLE);
	पूर्ण अन्यथा अगर (!active_links) अणु
		smcr_lgr_set_type(lgr, SMC_LGR_NONE);
		smc_lgr_terminate_sched(lgr);
	पूर्ण

	अगर (lgr->type == SMC_LGR_SINGLE && !list_empty(&lgr->list)) अणु
		/* trigger setup of asymm alt link */
		smc_llc_add_link_local(lnk);
	पूर्ण
out:
	mutex_unlock(&lgr->llc_conf_mutex);
	kमुक्त(qentry);
पूर्ण

अटल व्योम smc_llc_delete_link_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link_group *lgr = container_of(work, काष्ठा smc_link_group,
						  llc_del_link_work);

	अगर (list_empty(&lgr->list)) अणु
		/* link group is terminating */
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
		जाओ out;
	पूर्ण

	अगर (lgr->role == SMC_CLNT)
		smc_llc_process_cli_delete_link(lgr);
	अन्यथा
		smc_llc_process_srv_delete_link(lgr);
out:
	smc_llc_flow_stop(lgr, &lgr->llc_flow_lcl);
पूर्ण

/* process a confirm_rkey request from peer, remote flow */
अटल व्योम smc_llc_rmt_conf_rkey(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_llc_msg_confirm_rkey *llc;
	काष्ठा smc_llc_qentry *qentry;
	काष्ठा smc_link *link;
	पूर्णांक num_entries;
	पूर्णांक rk_idx;
	पूर्णांक i;

	qentry = lgr->llc_flow_rmt.qentry;
	llc = &qentry->msg.confirm_rkey;
	link = qentry->link;

	num_entries = llc->rtoken[0].num_rkeys;
	/* first rkey entry is क्रम receiving link */
	rk_idx = smc_rtoken_add(link,
				llc->rtoken[0].rmb_vaddr,
				llc->rtoken[0].rmb_key);
	अगर (rk_idx < 0)
		जाओ out_err;

	क्रम (i = 1; i <= min_t(u8, num_entries, SMC_LLC_RKEYS_PER_MSG - 1); i++)
		smc_rtoken_set2(lgr, rk_idx, llc->rtoken[i].link_id,
				llc->rtoken[i].rmb_vaddr,
				llc->rtoken[i].rmb_key);
	/* max links is 3 so there is no need to support conf_rkey_cont msgs */
	जाओ out;
out_err:
	llc->hd.flags |= SMC_LLC_FLAG_RKEY_NEG;
	llc->hd.flags |= SMC_LLC_FLAG_RKEY_RETRY;
out:
	llc->hd.flags |= SMC_LLC_FLAG_RESP;
	smc_llc_send_message(link, &qentry->msg);
	smc_llc_flow_qentry_del(&lgr->llc_flow_rmt);
पूर्ण

/* process a delete_rkey request from peer, remote flow */
अटल व्योम smc_llc_rmt_delete_rkey(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_llc_msg_delete_rkey *llc;
	काष्ठा smc_llc_qentry *qentry;
	काष्ठा smc_link *link;
	u8 err_mask = 0;
	पूर्णांक i, max;

	qentry = lgr->llc_flow_rmt.qentry;
	llc = &qentry->msg.delete_rkey;
	link = qentry->link;

	max = min_t(u8, llc->num_rkeys, SMC_LLC_DEL_RKEY_MAX);
	क्रम (i = 0; i < max; i++) अणु
		अगर (smc_rtoken_delete(link, llc->rkey[i]))
			err_mask |= 1 << (SMC_LLC_DEL_RKEY_MAX - 1 - i);
	पूर्ण
	अगर (err_mask) अणु
		llc->hd.flags |= SMC_LLC_FLAG_RKEY_NEG;
		llc->err_mask = err_mask;
	पूर्ण
	llc->hd.flags |= SMC_LLC_FLAG_RESP;
	smc_llc_send_message(link, &qentry->msg);
	smc_llc_flow_qentry_del(&lgr->llc_flow_rmt);
पूर्ण

अटल व्योम smc_llc_protocol_violation(काष्ठा smc_link_group *lgr, u8 type)
अणु
	pr_warn_ratelimited("smc: SMC-R lg %*phN LLC protocol violation: "
			    "llc_type %d\n", SMC_LGR_ID_SIZE, &lgr->id, type);
	smc_llc_set_termination_rsn(lgr, SMC_LLC_DEL_PROT_VIOL);
	smc_lgr_terminate_sched(lgr);
पूर्ण

/* flush the llc event queue */
अटल व्योम smc_llc_event_flush(काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_llc_qentry *qentry, *q;

	spin_lock_bh(&lgr->llc_event_q_lock);
	list_क्रम_each_entry_safe(qentry, q, &lgr->llc_event_q, list) अणु
		list_del_init(&qentry->list);
		kमुक्त(qentry);
	पूर्ण
	spin_unlock_bh(&lgr->llc_event_q_lock);
पूर्ण

अटल व्योम smc_llc_event_handler(काष्ठा smc_llc_qentry *qentry)
अणु
	जोड़ smc_llc_msg *llc = &qentry->msg;
	काष्ठा smc_link *link = qentry->link;
	काष्ठा smc_link_group *lgr = link->lgr;

	अगर (!smc_link_usable(link))
		जाओ out;

	चयन (llc->raw.hdr.common.type) अणु
	हाल SMC_LLC_TEST_LINK:
		llc->test_link.hd.flags |= SMC_LLC_FLAG_RESP;
		smc_llc_send_message(link, llc);
		अवरोध;
	हाल SMC_LLC_ADD_LINK:
		अगर (list_empty(&lgr->list))
			जाओ out;	/* lgr is terminating */
		अगर (lgr->role == SMC_CLNT) अणु
			अगर (smc_llc_is_local_add_link(llc)) अणु
				अगर (lgr->llc_flow_lcl.type ==
				    SMC_LLC_FLOW_ADD_LINK)
					अवरोध;	/* add_link in progress */
				अगर (smc_llc_flow_start(&lgr->llc_flow_lcl,
						       qentry)) अणु
					schedule_work(&lgr->llc_add_link_work);
				पूर्ण
				वापस;
			पूर्ण
			अगर (lgr->llc_flow_lcl.type == SMC_LLC_FLOW_ADD_LINK &&
			    !lgr->llc_flow_lcl.qentry) अणु
				/* a flow is रुकोing क्रम this message */
				smc_llc_flow_qentry_set(&lgr->llc_flow_lcl,
							qentry);
				wake_up(&lgr->llc_msg_रुकोer);
			पूर्ण अन्यथा अगर (smc_llc_flow_start(&lgr->llc_flow_lcl,
						      qentry)) अणु
				schedule_work(&lgr->llc_add_link_work);
			पूर्ण
		पूर्ण अन्यथा अगर (smc_llc_flow_start(&lgr->llc_flow_lcl, qentry)) अणु
			/* as smc server, handle client suggestion */
			schedule_work(&lgr->llc_add_link_work);
		पूर्ण
		वापस;
	हाल SMC_LLC_CONFIRM_LINK:
	हाल SMC_LLC_ADD_LINK_CONT:
		अगर (lgr->llc_flow_lcl.type != SMC_LLC_FLOW_NONE) अणु
			/* a flow is रुकोing क्रम this message */
			smc_llc_flow_qentry_set(&lgr->llc_flow_lcl, qentry);
			wake_up(&lgr->llc_msg_रुकोer);
			वापस;
		पूर्ण
		अवरोध;
	हाल SMC_LLC_DELETE_LINK:
		अगर (lgr->llc_flow_lcl.type == SMC_LLC_FLOW_ADD_LINK &&
		    !lgr->llc_flow_lcl.qentry) अणु
			/* DEL LINK REQ during ADD LINK SEQ */
			smc_llc_flow_qentry_set(&lgr->llc_flow_lcl, qentry);
			wake_up(&lgr->llc_msg_रुकोer);
		पूर्ण अन्यथा अगर (smc_llc_flow_start(&lgr->llc_flow_lcl, qentry)) अणु
			schedule_work(&lgr->llc_del_link_work);
		पूर्ण
		वापस;
	हाल SMC_LLC_CONFIRM_RKEY:
		/* new request from remote, assign to remote flow */
		अगर (smc_llc_flow_start(&lgr->llc_flow_rmt, qentry)) अणु
			/* process here, करोes not रुको क्रम more llc msgs */
			smc_llc_rmt_conf_rkey(lgr);
			smc_llc_flow_stop(lgr, &lgr->llc_flow_rmt);
		पूर्ण
		वापस;
	हाल SMC_LLC_CONFIRM_RKEY_CONT:
		/* not used because max links is 3, and 3 rkeys fit पूर्णांकo
		 * one CONFIRM_RKEY message
		 */
		अवरोध;
	हाल SMC_LLC_DELETE_RKEY:
		/* new request from remote, assign to remote flow */
		अगर (smc_llc_flow_start(&lgr->llc_flow_rmt, qentry)) अणु
			/* process here, करोes not रुको क्रम more llc msgs */
			smc_llc_rmt_delete_rkey(lgr);
			smc_llc_flow_stop(lgr, &lgr->llc_flow_rmt);
		पूर्ण
		वापस;
	शेष:
		smc_llc_protocol_violation(lgr, llc->raw.hdr.common.type);
		अवरोध;
	पूर्ण
out:
	kमुक्त(qentry);
पूर्ण

/* worker to process llc messages on the event queue */
अटल व्योम smc_llc_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link_group *lgr = container_of(work, काष्ठा smc_link_group,
						  llc_event_work);
	काष्ठा smc_llc_qentry *qentry;

	अगर (!lgr->llc_flow_lcl.type && lgr->delayed_event) अणु
		qentry = lgr->delayed_event;
		lgr->delayed_event = शून्य;
		अगर (smc_link_usable(qentry->link))
			smc_llc_event_handler(qentry);
		अन्यथा
			kमुक्त(qentry);
	पूर्ण

again:
	spin_lock_bh(&lgr->llc_event_q_lock);
	अगर (!list_empty(&lgr->llc_event_q)) अणु
		qentry = list_first_entry(&lgr->llc_event_q,
					  काष्ठा smc_llc_qentry, list);
		list_del_init(&qentry->list);
		spin_unlock_bh(&lgr->llc_event_q_lock);
		smc_llc_event_handler(qentry);
		जाओ again;
	पूर्ण
	spin_unlock_bh(&lgr->llc_event_q_lock);
पूर्ण

/* process llc responses in tasklet context */
अटल व्योम smc_llc_rx_response(काष्ठा smc_link *link,
				काष्ठा smc_llc_qentry *qentry)
अणु
	क्रमागत smc_llc_flowtype flowtype = link->lgr->llc_flow_lcl.type;
	काष्ठा smc_llc_flow *flow = &link->lgr->llc_flow_lcl;
	u8 llc_type = qentry->msg.raw.hdr.common.type;

	चयन (llc_type) अणु
	हाल SMC_LLC_TEST_LINK:
		अगर (smc_link_active(link))
			complete(&link->llc_testlink_resp);
		अवरोध;
	हाल SMC_LLC_ADD_LINK:
	हाल SMC_LLC_ADD_LINK_CONT:
	हाल SMC_LLC_CONFIRM_LINK:
		अगर (flowtype != SMC_LLC_FLOW_ADD_LINK || flow->qentry)
			अवरोध;	/* drop out-of-flow response */
		जाओ assign;
	हाल SMC_LLC_DELETE_LINK:
		अगर (flowtype != SMC_LLC_FLOW_DEL_LINK || flow->qentry)
			अवरोध;	/* drop out-of-flow response */
		जाओ assign;
	हाल SMC_LLC_CONFIRM_RKEY:
	हाल SMC_LLC_DELETE_RKEY:
		अगर (flowtype != SMC_LLC_FLOW_RKEY || flow->qentry)
			अवरोध;	/* drop out-of-flow response */
		जाओ assign;
	हाल SMC_LLC_CONFIRM_RKEY_CONT:
		/* not used because max links is 3 */
		अवरोध;
	शेष:
		smc_llc_protocol_violation(link->lgr, llc_type);
		अवरोध;
	पूर्ण
	kमुक्त(qentry);
	वापस;
assign:
	/* assign responses to the local flow, we requested them */
	smc_llc_flow_qentry_set(&link->lgr->llc_flow_lcl, qentry);
	wake_up(&link->lgr->llc_msg_रुकोer);
पूर्ण

अटल व्योम smc_llc_enqueue(काष्ठा smc_link *link, जोड़ smc_llc_msg *llc)
अणु
	काष्ठा smc_link_group *lgr = link->lgr;
	काष्ठा smc_llc_qentry *qentry;
	अचिन्हित दीर्घ flags;

	qentry = kदो_स्मृति(माप(*qentry), GFP_ATOMIC);
	अगर (!qentry)
		वापस;
	qentry->link = link;
	INIT_LIST_HEAD(&qentry->list);
	स_नकल(&qentry->msg, llc, माप(जोड़ smc_llc_msg));

	/* process responses immediately */
	अगर (llc->raw.hdr.flags & SMC_LLC_FLAG_RESP) अणु
		smc_llc_rx_response(link, qentry);
		वापस;
	पूर्ण

	/* add requests to event queue */
	spin_lock_irqsave(&lgr->llc_event_q_lock, flags);
	list_add_tail(&qentry->list, &lgr->llc_event_q);
	spin_unlock_irqrestore(&lgr->llc_event_q_lock, flags);
	queue_work(प्रणाली_highpri_wq, &lgr->llc_event_work);
पूर्ण

/* copy received msg and add it to the event queue */
अटल व्योम smc_llc_rx_handler(काष्ठा ib_wc *wc, व्योम *buf)
अणु
	काष्ठा smc_link *link = (काष्ठा smc_link *)wc->qp->qp_context;
	जोड़ smc_llc_msg *llc = buf;

	अगर (wc->byte_len < माप(*llc))
		वापस; /* लघु message */
	अगर (llc->raw.hdr.length != माप(*llc))
		वापस; /* invalid message */

	smc_llc_enqueue(link, llc);
पूर्ण

/***************************** worker, utils *********************************/

अटल व्योम smc_llc_testlink_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link *link = container_of(to_delayed_work(work),
					     काष्ठा smc_link, llc_testlink_wrk);
	अचिन्हित दीर्घ next_पूर्णांकerval;
	अचिन्हित दीर्घ expire_समय;
	u8 user_data[16] = अणु 0 पूर्ण;
	पूर्णांक rc;

	अगर (!smc_link_active(link))
		वापस;		/* करोn't reschedule worker */
	expire_समय = link->wr_rx_tstamp + link->llc_testlink_समय;
	अगर (समय_is_after_jअगरfies(expire_समय)) अणु
		next_पूर्णांकerval = expire_समय - jअगरfies;
		जाओ out;
	पूर्ण
	reinit_completion(&link->llc_testlink_resp);
	smc_llc_send_test_link(link, user_data);
	/* receive TEST LINK response over RoCE fabric */
	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&link->llc_testlink_resp,
						       SMC_LLC_WAIT_TIME);
	अगर (!smc_link_active(link))
		वापस;		/* link state changed */
	अगर (rc <= 0) अणु
		smcr_link_करोwn_cond_sched(link);
		वापस;
	पूर्ण
	next_पूर्णांकerval = link->llc_testlink_समय;
out:
	schedule_delayed_work(&link->llc_testlink_wrk, next_पूर्णांकerval);
पूर्ण

व्योम smc_llc_lgr_init(काष्ठा smc_link_group *lgr, काष्ठा smc_sock *smc)
अणु
	काष्ठा net *net = sock_net(smc->clcsock->sk);

	INIT_WORK(&lgr->llc_event_work, smc_llc_event_work);
	INIT_WORK(&lgr->llc_add_link_work, smc_llc_add_link_work);
	INIT_WORK(&lgr->llc_del_link_work, smc_llc_delete_link_work);
	INIT_LIST_HEAD(&lgr->llc_event_q);
	spin_lock_init(&lgr->llc_event_q_lock);
	spin_lock_init(&lgr->llc_flow_lock);
	init_रुकोqueue_head(&lgr->llc_flow_रुकोer);
	init_रुकोqueue_head(&lgr->llc_msg_रुकोer);
	mutex_init(&lgr->llc_conf_mutex);
	lgr->llc_testlink_समय = net->ipv4.sysctl_tcp_keepalive_समय;
पूर्ण

/* called after lgr was हटाओd from lgr_list */
व्योम smc_llc_lgr_clear(काष्ठा smc_link_group *lgr)
अणु
	smc_llc_event_flush(lgr);
	wake_up_all(&lgr->llc_flow_रुकोer);
	wake_up_all(&lgr->llc_msg_रुकोer);
	cancel_work_sync(&lgr->llc_event_work);
	cancel_work_sync(&lgr->llc_add_link_work);
	cancel_work_sync(&lgr->llc_del_link_work);
	अगर (lgr->delayed_event) अणु
		kमुक्त(lgr->delayed_event);
		lgr->delayed_event = शून्य;
	पूर्ण
पूर्ण

पूर्णांक smc_llc_link_init(काष्ठा smc_link *link)
अणु
	init_completion(&link->llc_testlink_resp);
	INIT_DELAYED_WORK(&link->llc_testlink_wrk, smc_llc_testlink_work);
	वापस 0;
पूर्ण

व्योम smc_llc_link_active(काष्ठा smc_link *link)
अणु
	pr_warn_ratelimited("smc: SMC-R lg %*phN link added: id %*phN, "
			    "peerid %*phN, ibdev %s, ibport %d\n",
			    SMC_LGR_ID_SIZE, &link->lgr->id,
			    SMC_LGR_ID_SIZE, &link->link_uid,
			    SMC_LGR_ID_SIZE, &link->peer_link_uid,
			    link->smcibdev->ibdev->name, link->ibport);
	link->state = SMC_LNK_ACTIVE;
	अगर (link->lgr->llc_testlink_समय) अणु
		link->llc_testlink_समय = link->lgr->llc_testlink_समय * HZ;
		schedule_delayed_work(&link->llc_testlink_wrk,
				      link->llc_testlink_समय);
	पूर्ण
पूर्ण

/* called in worker context */
व्योम smc_llc_link_clear(काष्ठा smc_link *link, bool log)
अणु
	अगर (log)
		pr_warn_ratelimited("smc: SMC-R lg %*phN link removed: id %*phN"
				    ", peerid %*phN, ibdev %s, ibport %d\n",
				    SMC_LGR_ID_SIZE, &link->lgr->id,
				    SMC_LGR_ID_SIZE, &link->link_uid,
				    SMC_LGR_ID_SIZE, &link->peer_link_uid,
				    link->smcibdev->ibdev->name, link->ibport);
	complete(&link->llc_testlink_resp);
	cancel_delayed_work_sync(&link->llc_testlink_wrk);
	smc_wr_wakeup_reg_रुको(link);
	smc_wr_wakeup_tx_रुको(link);
पूर्ण

/* रेजिस्टर a new rtoken at the remote peer (क्रम all links) */
पूर्णांक smc_llc_करो_confirm_rkey(काष्ठा smc_link *send_link,
			    काष्ठा smc_buf_desc *rmb_desc)
अणु
	काष्ठा smc_link_group *lgr = send_link->lgr;
	काष्ठा smc_llc_qentry *qentry = शून्य;
	पूर्णांक rc = 0;

	rc = smc_llc_send_confirm_rkey(send_link, rmb_desc);
	अगर (rc)
		जाओ out;
	/* receive CONFIRM RKEY response from server over RoCE fabric */
	qentry = smc_llc_रुको(lgr, send_link, SMC_LLC_WAIT_TIME,
			      SMC_LLC_CONFIRM_RKEY);
	अगर (!qentry || (qentry->msg.raw.hdr.flags & SMC_LLC_FLAG_RKEY_NEG))
		rc = -EFAULT;
out:
	अगर (qentry)
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
	वापस rc;
पूर्ण

/* unरेजिस्टर an rtoken at the remote peer */
पूर्णांक smc_llc_करो_delete_rkey(काष्ठा smc_link_group *lgr,
			   काष्ठा smc_buf_desc *rmb_desc)
अणु
	काष्ठा smc_llc_qentry *qentry = शून्य;
	काष्ठा smc_link *send_link;
	पूर्णांक rc = 0;

	send_link = smc_llc_usable_link(lgr);
	अगर (!send_link)
		वापस -ENOLINK;

	/* रक्षित by llc_flow control */
	rc = smc_llc_send_delete_rkey(send_link, rmb_desc);
	अगर (rc)
		जाओ out;
	/* receive DELETE RKEY response from server over RoCE fabric */
	qentry = smc_llc_रुको(lgr, send_link, SMC_LLC_WAIT_TIME,
			      SMC_LLC_DELETE_RKEY);
	अगर (!qentry || (qentry->msg.raw.hdr.flags & SMC_LLC_FLAG_RKEY_NEG))
		rc = -EFAULT;
out:
	अगर (qentry)
		smc_llc_flow_qentry_del(&lgr->llc_flow_lcl);
	वापस rc;
पूर्ण

व्योम smc_llc_link_set_uid(काष्ठा smc_link *link)
अणु
	__be32 link_uid;

	link_uid = htonl(*((u32 *)link->lgr->id) + link->link_id);
	स_नकल(link->link_uid, &link_uid, SMC_LGR_ID_SIZE);
पूर्ण

/* save peers link user id, used क्रम debug purposes */
व्योम smc_llc_save_peer_uid(काष्ठा smc_llc_qentry *qentry)
अणु
	स_नकल(qentry->link->peer_link_uid, qentry->msg.confirm_link.link_uid,
	       SMC_LGR_ID_SIZE);
पूर्ण

/* evaluate confirm link request or response */
पूर्णांक smc_llc_eval_conf_link(काष्ठा smc_llc_qentry *qentry,
			   क्रमागत smc_llc_reqresp type)
अणु
	अगर (type == SMC_LLC_REQ) अणु	/* SMC server assigns link_id */
		qentry->link->link_id = qentry->msg.confirm_link.link_num;
		smc_llc_link_set_uid(qentry->link);
	पूर्ण
	अगर (!(qentry->msg.raw.hdr.flags & SMC_LLC_FLAG_NO_RMBE_EYEC))
		वापस -ENOTSUPP;
	वापस 0;
पूर्ण

/***************************** init, निकास, misc ******************************/

अटल काष्ठा smc_wr_rx_handler smc_llc_rx_handlers[] = अणु
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_CONFIRM_LINK
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_TEST_LINK
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_ADD_LINK
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_ADD_LINK_CONT
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_DELETE_LINK
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_CONFIRM_RKEY
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_CONFIRM_RKEY_CONT
	पूर्ण,
	अणु
		.handler	= smc_llc_rx_handler,
		.type		= SMC_LLC_DELETE_RKEY
	पूर्ण,
	अणु
		.handler	= शून्य,
	पूर्ण
पूर्ण;

पूर्णांक __init smc_llc_init(व्योम)
अणु
	काष्ठा smc_wr_rx_handler *handler;
	पूर्णांक rc = 0;

	क्रम (handler = smc_llc_rx_handlers; handler->handler; handler++) अणु
		INIT_HLIST_NODE(&handler->list);
		rc = smc_wr_rx_रेजिस्टर_handler(handler);
		अगर (rc)
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
