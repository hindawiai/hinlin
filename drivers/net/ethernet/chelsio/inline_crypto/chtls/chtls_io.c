<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2018 Chelsio Communications, Inc.
 *
 * Written by: Atul Gupta (atul.gupta@chelsio.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <net/tcp.h>
#समावेश <net/busy_poll.h>
#समावेश <crypto/aes.h>

#समावेश "chtls.h"
#समावेश "chtls_cm.h"

अटल bool is_tls_tx(काष्ठा chtls_sock *csk)
अणु
	वापस csk->tlshws.txkey >= 0;
पूर्ण

अटल bool is_tls_rx(काष्ठा chtls_sock *csk)
अणु
	वापस csk->tlshws.rxkey >= 0;
पूर्ण

अटल पूर्णांक data_sgl_len(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक cnt;

	cnt = skb_shinfo(skb)->nr_frags;
	वापस sgl_len(cnt) * 8;
पूर्ण

अटल पूर्णांक nos_ivs(काष्ठा sock *sk, अचिन्हित पूर्णांक size)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	वापस DIV_ROUND_UP(size, csk->tlshws.mfs);
पूर्ण

अटल पूर्णांक set_ivs_imm(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक ivs_size = nos_ivs(sk, skb->len) * CIPHER_BLOCK_SIZE;
	पूर्णांक hlen = TLS_WR_CPL_LEN + data_sgl_len(skb);

	अगर ((hlen + KEY_ON_MEM_SZ + ivs_size) <
	    MAX_IMM_OFLD_TX_DATA_WR_LEN) अणु
		ULP_SKB_CB(skb)->ulp.tls.iv = 1;
		वापस 1;
	पूर्ण
	ULP_SKB_CB(skb)->ulp.tls.iv = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक max_ivs_size(काष्ठा sock *sk, पूर्णांक size)
अणु
	वापस nos_ivs(sk, size) * CIPHER_BLOCK_SIZE;
पूर्ण

अटल पूर्णांक ivs_size(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	वापस set_ivs_imm(sk, skb) ? (nos_ivs(sk, skb->len) *
		 CIPHER_BLOCK_SIZE) : 0;
पूर्ण

अटल पूर्णांक flowc_wr_credits(पूर्णांक nparams, पूर्णांक *flowclenp)
अणु
	पूर्णांक flowclen16, flowclen;

	flowclen = दुरत्व(काष्ठा fw_flowc_wr, mnemval[nparams]);
	flowclen16 = DIV_ROUND_UP(flowclen, 16);
	flowclen = flowclen16 * 16;

	अगर (flowclenp)
		*flowclenp = flowclen;

	वापस flowclen16;
पूर्ण

अटल काष्ठा sk_buff *create_flowc_wr_skb(काष्ठा sock *sk,
					   काष्ठा fw_flowc_wr *flowc,
					   पूर्णांक flowclen)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा sk_buff *skb;

	skb = alloc_skb(flowclen, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	__skb_put_data(skb, flowc, flowclen);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPL_PRIORITY_DATA);

	वापस skb;
पूर्ण

अटल पूर्णांक send_flowc_wr(काष्ठा sock *sk, काष्ठा fw_flowc_wr *flowc,
			 पूर्णांक flowclen)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक flowclen16;
	पूर्णांक ret;

	flowclen16 = flowclen / 16;

	अगर (csk_flag(sk, CSK_TX_DATA_SENT)) अणु
		skb = create_flowc_wr_skb(sk, flowc, flowclen);
		अगर (!skb)
			वापस -ENOMEM;

		skb_entail(sk, skb,
			   ULPCB_FLAG_NO_HDR | ULPCB_FLAG_NO_APPEND);
		वापस 0;
	पूर्ण

	ret = cxgb4_immdata_send(csk->egress_dev,
				 csk->txq_idx,
				 flowc, flowclen);
	अगर (!ret)
		वापस flowclen16;
	skb = create_flowc_wr_skb(sk, flowc, flowclen);
	अगर (!skb)
		वापस -ENOMEM;
	send_or_defer(sk, tp, skb, 0);
	वापस flowclen16;
पूर्ण

अटल u8 tcp_state_to_flowc_state(u8 state)
अणु
	चयन (state) अणु
	हाल TCP_ESTABLISHED:
		वापस FW_FLOWC_MNEM_TCPSTATE_ESTABLISHED;
	हाल TCP_CLOSE_WAIT:
		वापस FW_FLOWC_MNEM_TCPSTATE_CLOSEWAIT;
	हाल TCP_FIN_WAIT1:
		वापस FW_FLOWC_MNEM_TCPSTATE_FINWAIT1;
	हाल TCP_CLOSING:
		वापस FW_FLOWC_MNEM_TCPSTATE_CLOSING;
	हाल TCP_LAST_ACK:
		वापस FW_FLOWC_MNEM_TCPSTATE_LASTACK;
	हाल TCP_FIN_WAIT2:
		वापस FW_FLOWC_MNEM_TCPSTATE_FINWAIT2;
	पूर्ण

	वापस FW_FLOWC_MNEM_TCPSTATE_ESTABLISHED;
पूर्ण

पूर्णांक send_tx_flowc_wr(काष्ठा sock *sk, पूर्णांक compl,
		     u32 snd_nxt, u32 rcv_nxt)
अणु
	काष्ठा flowc_packed अणु
		काष्ठा fw_flowc_wr fc;
		काष्ठा fw_flowc_mnemval mnemval[FW_FLOWC_MNEM_MAX];
	पूर्ण __packed sflowc;
	पूर्णांक nparams, paramidx, flowclen16, flowclen;
	काष्ठा fw_flowc_wr *flowc;
	काष्ठा chtls_sock *csk;
	काष्ठा tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tp = tcp_sk(sk);
	स_रखो(&sflowc, 0, माप(sflowc));
	flowc = &sflowc.fc;

#घोषणा FLOWC_PARAM(__m, __v) \
	करो अणु \
		flowc->mnemval[paramidx].mnemonic = FW_FLOWC_MNEM_##__m; \
		flowc->mnemval[paramidx].val = cpu_to_be32(__v); \
		paramidx++; \
	पूर्ण जबतक (0)

	paramidx = 0;

	FLOWC_PARAM(PFNVFN, FW_PFVF_CMD_PFN_V(csk->cdev->lldi->pf));
	FLOWC_PARAM(CH, csk->tx_chan);
	FLOWC_PARAM(PORT, csk->tx_chan);
	FLOWC_PARAM(IQID, csk->rss_qid);
	FLOWC_PARAM(SNDNXT, tp->snd_nxt);
	FLOWC_PARAM(RCVNXT, tp->rcv_nxt);
	FLOWC_PARAM(SNDBUF, csk->sndbuf);
	FLOWC_PARAM(MSS, tp->mss_cache);
	FLOWC_PARAM(TCPSTATE, tcp_state_to_flowc_state(sk->sk_state));

	अगर (SND_WSCALE(tp))
		FLOWC_PARAM(RCV_SCALE, SND_WSCALE(tp));

	अगर (csk->ulp_mode == ULP_MODE_TLS)
		FLOWC_PARAM(ULD_MODE, ULP_MODE_TLS);

	अगर (csk->tlshws.fcplenmax)
		FLOWC_PARAM(TXDATAPLEN_MAX, csk->tlshws.fcplenmax);

	nparams = paramidx;
#अघोषित FLOWC_PARAM

	flowclen16 = flowc_wr_credits(nparams, &flowclen);
	flowc->op_to_nparams =
		cpu_to_be32(FW_WR_OP_V(FW_FLOWC_WR) |
			    FW_WR_COMPL_V(compl) |
			    FW_FLOWC_WR_NPARAMS_V(nparams));
	flowc->flowid_len16 = cpu_to_be32(FW_WR_LEN16_V(flowclen16) |
					  FW_WR_FLOWID_V(csk->tid));

	वापस send_flowc_wr(sk, flowc, flowclen);
पूर्ण

/* Copy IVs to WR */
अटल पूर्णांक tls_copy_ivs(काष्ठा sock *sk, काष्ठा sk_buff *skb)

अणु
	काष्ठा chtls_sock *csk;
	अचिन्हित अक्षर *iv_loc;
	काष्ठा chtls_hws *hws;
	अचिन्हित अक्षर *ivs;
	u16 number_of_ivs;
	काष्ठा page *page;
	पूर्णांक err = 0;

	csk = rcu_dereference_sk_user_data(sk);
	hws = &csk->tlshws;
	number_of_ivs = nos_ivs(sk, skb->len);

	अगर (number_of_ivs > MAX_IVS_PAGE) अणु
		pr_warn("MAX IVs in PAGE exceeded %d\n", number_of_ivs);
		वापस -ENOMEM;
	पूर्ण

	/* generate the  IVs */
	ivs = kदो_स्मृति_array(CIPHER_BLOCK_SIZE, number_of_ivs, GFP_ATOMIC);
	अगर (!ivs)
		वापस -ENOMEM;
	get_अक्रमom_bytes(ivs, number_of_ivs * CIPHER_BLOCK_SIZE);

	अगर (skb_ulp_tls_iv_imm(skb)) अणु
		/* send the IVs as immediate data in the WR */
		iv_loc = (अचिन्हित अक्षर *)__skb_push(skb, number_of_ivs *
						CIPHER_BLOCK_SIZE);
		अगर (iv_loc)
			स_नकल(iv_loc, ivs, number_of_ivs * CIPHER_BLOCK_SIZE);

		hws->ivsize = number_of_ivs * CIPHER_BLOCK_SIZE;
	पूर्ण अन्यथा अणु
		/* Send the IVs as sgls */
		/* Alपढ़ोy accounted IV DSGL क्रम credits */
		skb_shinfo(skb)->nr_frags--;
		page = alloc_pages(sk->sk_allocation | __GFP_COMP, 0);
		अगर (!page) अणु
			pr_info("%s : Page allocation for IVs failed\n",
				__func__);
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		स_नकल(page_address(page), ivs, number_of_ivs *
		       CIPHER_BLOCK_SIZE);
		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags, page, 0,
				   number_of_ivs * CIPHER_BLOCK_SIZE);
		hws->ivsize = 0;
	पूर्ण
out:
	kमुक्त(ivs);
	वापस err;
पूर्ण

/* Copy Key to WR */
अटल व्योम tls_copy_tx_key(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ulptx_sc_memrd *sc_memrd;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_dev *cdev;
	काष्ठा ulptx_idata *sc;
	काष्ठा chtls_hws *hws;
	u32 immdlen;
	पूर्णांक kaddr;

	csk = rcu_dereference_sk_user_data(sk);
	hws = &csk->tlshws;
	cdev = csk->cdev;

	immdlen = माप(*sc) + माप(*sc_memrd);
	kaddr = keyid_to_addr(cdev->kmap.start, hws->txkey);
	sc = (काष्ठा ulptx_idata *)__skb_push(skb, immdlen);
	अगर (sc) अणु
		sc->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_NOOP));
		sc->len = htonl(0);
		sc_memrd = (काष्ठा ulptx_sc_memrd *)(sc + 1);
		sc_memrd->cmd_to_len =
				htonl(ULPTX_CMD_V(ULP_TX_SC_MEMRD) |
				ULP_TX_SC_MORE_V(1) |
				ULPTX_LEN16_V(hws->keylen >> 4));
		sc_memrd->addr = htonl(kaddr);
	पूर्ण
पूर्ण

अटल u64 tlstx_incr_seqnum(काष्ठा chtls_hws *hws)
अणु
	वापस hws->tx_seq_no++;
पूर्ण

अटल bool is_sg_request(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->peeked ||
		(skb->len > MAX_IMM_ULPTX_WR_LEN);
पूर्ण

/*
 * Returns true अगर an sk_buff carries urgent data.
 */
अटल bool skb_urgent(काष्ठा sk_buff *skb)
अणु
	वापस ULP_SKB_CB(skb)->flags & ULPCB_FLAG_URG;
पूर्ण

/* TLS content type क्रम CPL SFO */
अटल अचिन्हित अक्षर tls_content_type(अचिन्हित अक्षर content_type)
अणु
	चयन (content_type) अणु
	हाल TLS_HDR_TYPE_CCS:
		वापस CPL_TX_TLS_SFO_TYPE_CCS;
	हाल TLS_HDR_TYPE_ALERT:
		वापस CPL_TX_TLS_SFO_TYPE_ALERT;
	हाल TLS_HDR_TYPE_HANDSHAKE:
		वापस CPL_TX_TLS_SFO_TYPE_HANDSHAKE;
	हाल TLS_HDR_TYPE_HEARTBEAT:
		वापस CPL_TX_TLS_SFO_TYPE_HEARTBEAT;
	पूर्ण
	वापस CPL_TX_TLS_SFO_TYPE_DATA;
पूर्ण

अटल व्योम tls_tx_data_wr(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   पूर्णांक dlen, पूर्णांक tls_immd, u32 credits,
			   पूर्णांक expn, पूर्णांक pdus)
अणु
	काष्ठा fw_tlstx_data_wr *req_wr;
	काष्ठा cpl_tx_tls_sfo *req_cpl;
	अचिन्हित पूर्णांक wr_ulp_mode_क्रमce;
	काष्ठा tls_scmd *updated_scmd;
	अचिन्हित अक्षर data_type;
	काष्ठा chtls_sock *csk;
	काष्ठा net_device *dev;
	काष्ठा chtls_hws *hws;
	काष्ठा tls_scmd *scmd;
	काष्ठा adapter *adap;
	अचिन्हित अक्षर *req;
	पूर्णांक immd_len;
	पूर्णांक iv_imm;
	पूर्णांक len;

	csk = rcu_dereference_sk_user_data(sk);
	iv_imm = skb_ulp_tls_iv_imm(skb);
	dev = csk->egress_dev;
	adap = netdev2adap(dev);
	hws = &csk->tlshws;
	scmd = &hws->scmd;
	len = dlen + expn;

	dlen = (dlen < hws->mfs) ? dlen : hws->mfs;
	atomic_inc(&adap->chcr_stats.tls_pdu_tx);

	updated_scmd = scmd;
	updated_scmd->seqno_numivs &= 0xffffff80;
	updated_scmd->seqno_numivs |= SCMD_NUM_IVS_V(pdus);
	hws->scmd = *updated_scmd;

	req = (अचिन्हित अक्षर *)__skb_push(skb, माप(काष्ठा cpl_tx_tls_sfo));
	req_cpl = (काष्ठा cpl_tx_tls_sfo *)req;
	req = (अचिन्हित अक्षर *)__skb_push(skb, (माप(काष्ठा
				fw_tlstx_data_wr)));

	req_wr = (काष्ठा fw_tlstx_data_wr *)req;
	immd_len = (tls_immd ? dlen : 0);
	req_wr->op_to_immdlen =
		htonl(FW_WR_OP_V(FW_TLSTX_DATA_WR) |
		FW_TLSTX_DATA_WR_COMPL_V(1) |
		FW_TLSTX_DATA_WR_IMMDLEN_V(immd_len));
	req_wr->flowid_len16 = htonl(FW_TLSTX_DATA_WR_FLOWID_V(csk->tid) |
				     FW_TLSTX_DATA_WR_LEN16_V(credits));
	wr_ulp_mode_क्रमce = TX_ULP_MODE_V(ULP_MODE_TLS);

	अगर (is_sg_request(skb))
		wr_ulp_mode_क्रमce |= FW_OFLD_TX_DATA_WR_ALIGNPLD_F |
			((tcp_sk(sk)->nonagle & TCP_NAGLE_OFF) ? 0 :
			FW_OFLD_TX_DATA_WR_SHOVE_F);

	req_wr->lsodisable_to_flags =
			htonl(TX_ULP_MODE_V(ULP_MODE_TLS) |
			      TX_URG_V(skb_urgent(skb)) |
			      T6_TX_FORCE_F | wr_ulp_mode_क्रमce |
			      TX_SHOVE_V((!csk_flag(sk, CSK_TX_MORE_DATA)) &&
					 skb_queue_empty(&csk->txq)));

	req_wr->ctxloc_to_exp =
			htonl(FW_TLSTX_DATA_WR_NUMIVS_V(pdus) |
			      FW_TLSTX_DATA_WR_EXP_V(expn) |
			      FW_TLSTX_DATA_WR_CTXLOC_V(CHTLS_KEY_CONTEXT_DDR) |
			      FW_TLSTX_DATA_WR_IVDSGL_V(!iv_imm) |
			      FW_TLSTX_DATA_WR_KEYSIZE_V(hws->keylen >> 4));

	/* Fill in the length */
	req_wr->plen = htonl(len);
	req_wr->mfs = htons(hws->mfs);
	req_wr->adjustedplen_pkd =
		htons(FW_TLSTX_DATA_WR_ADJUSTEDPLEN_V(hws->adjustlen));
	req_wr->expinplenmax_pkd =
		htons(FW_TLSTX_DATA_WR_EXPINPLENMAX_V(hws->expansion));
	req_wr->pdusinplenmax_pkd =
		FW_TLSTX_DATA_WR_PDUSINPLENMAX_V(hws->pdus);
	req_wr->r10 = 0;

	data_type = tls_content_type(ULP_SKB_CB(skb)->ulp.tls.type);
	req_cpl->op_to_seg_len = htonl(CPL_TX_TLS_SFO_OPCODE_V(CPL_TX_TLS_SFO) |
				       CPL_TX_TLS_SFO_DATA_TYPE_V(data_type) |
				       CPL_TX_TLS_SFO_CPL_LEN_V(2) |
				       CPL_TX_TLS_SFO_SEG_LEN_V(dlen));
	req_cpl->pld_len = htonl(len - expn);

	req_cpl->type_protover = htonl(CPL_TX_TLS_SFO_TYPE_V
		((data_type == CPL_TX_TLS_SFO_TYPE_HEARTBEAT) ?
		TLS_HDR_TYPE_HEARTBEAT : 0) |
		CPL_TX_TLS_SFO_PROTOVER_V(0));

	/* create the s-command */
	req_cpl->r1_lo = 0;
	req_cpl->seqno_numivs  = cpu_to_be32(hws->scmd.seqno_numivs);
	req_cpl->ivgen_hdrlen = cpu_to_be32(hws->scmd.ivgen_hdrlen);
	req_cpl->scmd1 = cpu_to_be64(tlstx_incr_seqnum(hws));
पूर्ण

/*
 * Calculate the TLS data expansion size
 */
अटल पूर्णांक chtls_expansion_size(काष्ठा sock *sk, पूर्णांक data_len,
				पूर्णांक fullpdu,
				अचिन्हित लघु *pducnt)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा chtls_hws *hws = &csk->tlshws;
	काष्ठा tls_scmd *scmd = &hws->scmd;
	पूर्णांक fragsize = hws->mfs;
	पूर्णांक expnsize = 0;
	पूर्णांक fragleft;
	पूर्णांक fragcnt;
	पूर्णांक expppdu;

	अगर (SCMD_CIPH_MODE_G(scmd->seqno_numivs) ==
	    SCMD_CIPH_MODE_AES_GCM) अणु
		expppdu = GCM_TAG_SIZE + AEAD_EXPLICIT_DATA_SIZE +
			  TLS_HEADER_LENGTH;

		अगर (fullpdu) अणु
			*pducnt = data_len / (expppdu + fragsize);
			अगर (*pducnt > 32)
				*pducnt = 32;
			अन्यथा अगर (!*pducnt)
				*pducnt = 1;
			expnsize = (*pducnt) * expppdu;
			वापस expnsize;
		पूर्ण
		fragcnt = (data_len / fragsize);
		expnsize =  fragcnt * expppdu;
		fragleft = data_len % fragsize;
		अगर (fragleft > 0)
			expnsize += expppdu;
	पूर्ण
	वापस expnsize;
पूर्ण

/* WR with IV, KEY and CPL SFO added */
अटल व्योम make_tlstx_data_wr(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       पूर्णांक tls_tx_imm, पूर्णांक tls_len, u32 credits)
अणु
	अचिन्हित लघु pdus_per_ulp = 0;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_hws *hws;
	पूर्णांक expn_sz;
	पूर्णांक pdus;

	csk = rcu_dereference_sk_user_data(sk);
	hws = &csk->tlshws;
	pdus = DIV_ROUND_UP(tls_len, hws->mfs);
	expn_sz = chtls_expansion_size(sk, tls_len, 0, शून्य);
	अगर (!hws->compute) अणु
		hws->expansion = chtls_expansion_size(sk,
						      hws->fcplenmax,
						      1, &pdus_per_ulp);
		hws->pdus = pdus_per_ulp;
		hws->adjustlen = hws->pdus *
			((hws->expansion / hws->pdus) + hws->mfs);
		hws->compute = 1;
	पूर्ण
	अगर (tls_copy_ivs(sk, skb))
		वापस;
	tls_copy_tx_key(sk, skb);
	tls_tx_data_wr(sk, skb, tls_len, tls_tx_imm, credits, expn_sz, pdus);
	hws->tx_seq_no += (pdus - 1);
पूर्ण

अटल व्योम make_tx_data_wr(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक immdlen, पूर्णांक len,
			    u32 credits, u32 compl)
अणु
	काष्ठा fw_ofld_tx_data_wr *req;
	अचिन्हित पूर्णांक wr_ulp_mode_क्रमce;
	काष्ठा chtls_sock *csk;
	अचिन्हित पूर्णांक opcode;

	csk = rcu_dereference_sk_user_data(sk);
	opcode = FW_OFLD_TX_DATA_WR;

	req = (काष्ठा fw_ofld_tx_data_wr *)__skb_push(skb, माप(*req));
	req->op_to_immdlen = htonl(WR_OP_V(opcode) |
				FW_WR_COMPL_V(compl) |
				FW_WR_IMMDLEN_V(immdlen));
	req->flowid_len16 = htonl(FW_WR_FLOWID_V(csk->tid) |
				FW_WR_LEN16_V(credits));

	wr_ulp_mode_क्रमce = TX_ULP_MODE_V(csk->ulp_mode);
	अगर (is_sg_request(skb))
		wr_ulp_mode_क्रमce |= FW_OFLD_TX_DATA_WR_ALIGNPLD_F |
			((tcp_sk(sk)->nonagle & TCP_NAGLE_OFF) ? 0 :
				FW_OFLD_TX_DATA_WR_SHOVE_F);

	req->tunnel_to_proxy = htonl(wr_ulp_mode_क्रमce |
			TX_URG_V(skb_urgent(skb)) |
			TX_SHOVE_V((!csk_flag(sk, CSK_TX_MORE_DATA)) &&
				   skb_queue_empty(&csk->txq)));
	req->plen = htonl(len);
पूर्ण

अटल पूर्णांक chtls_wr_size(काष्ठा chtls_sock *csk, स्थिर काष्ठा sk_buff *skb,
			 bool size)
अणु
	पूर्णांक wr_size;

	wr_size = TLS_WR_CPL_LEN;
	wr_size += KEY_ON_MEM_SZ;
	wr_size += ivs_size(csk->sk, skb);

	अगर (size)
		वापस wr_size;

	/* frags counted क्रम IV dsgl */
	अगर (!skb_ulp_tls_iv_imm(skb))
		skb_shinfo(skb)->nr_frags++;

	वापस wr_size;
पूर्ण

अटल bool is_ofld_imm(काष्ठा chtls_sock *csk, स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक length = skb->len;

	अगर (skb->peeked || skb->len > MAX_IMM_ULPTX_WR_LEN)
		वापस false;

	अगर (likely(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NEED_HDR)) अणु
		/* Check TLS header len क्रम Immediate */
		अगर (csk->ulp_mode == ULP_MODE_TLS &&
		    skb_ulp_tls_अंतरभूत(skb))
			length += chtls_wr_size(csk, skb, true);
		अन्यथा
			length += माप(काष्ठा fw_ofld_tx_data_wr);

		वापस length <= MAX_IMM_OFLD_TX_DATA_WR_LEN;
	पूर्ण
	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक calc_tx_flits(स्थिर काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक immdlen)
अणु
	अचिन्हित पूर्णांक flits, cnt;

	flits = immdlen / 8;   /* headers */
	cnt = skb_shinfo(skb)->nr_frags;
	अगर (skb_tail_poपूर्णांकer(skb) != skb_transport_header(skb))
		cnt++;
	वापस flits + sgl_len(cnt);
पूर्ण

अटल व्योम arp_failure_discard(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

पूर्णांक chtls_push_frames(काष्ठा chtls_sock *csk, पूर्णांक comp)
अणु
	काष्ठा chtls_hws *hws = &csk->tlshws;
	काष्ठा tcp_sock *tp;
	काष्ठा sk_buff *skb;
	पूर्णांक total_size = 0;
	काष्ठा sock *sk;
	पूर्णांक wr_size;

	wr_size = माप(काष्ठा fw_ofld_tx_data_wr);
	sk = csk->sk;
	tp = tcp_sk(sk);

	अगर (unlikely(sk_in_state(sk, TCPF_SYN_SENT | TCPF_CLOSE)))
		वापस 0;

	अगर (unlikely(csk_flag(sk, CSK_ABORT_SHUTDOWN)))
		वापस 0;

	जबतक (csk->wr_credits && (skb = skb_peek(&csk->txq)) &&
	       (!(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_HOLD) ||
		skb_queue_len(&csk->txq) > 1)) अणु
		अचिन्हित पूर्णांक credit_len = skb->len;
		अचिन्हित पूर्णांक credits_needed;
		अचिन्हित पूर्णांक completion = 0;
		पूर्णांक tls_len = skb->len;/* TLS data len beक्रमe IV/key */
		अचिन्हित पूर्णांक immdlen;
		पूर्णांक len = skb->len;    /* length [ulp bytes] inserted by hw */
		पूर्णांक flowclen16 = 0;
		पूर्णांक tls_tx_imm = 0;

		immdlen = skb->len;
		अगर (!is_ofld_imm(csk, skb)) अणु
			immdlen = skb_transport_offset(skb);
			अगर (skb_ulp_tls_अंतरभूत(skb))
				wr_size = chtls_wr_size(csk, skb, false);
			credit_len = 8 * calc_tx_flits(skb, immdlen);
		पूर्ण अन्यथा अणु
			अगर (skb_ulp_tls_अंतरभूत(skb)) अणु
				wr_size = chtls_wr_size(csk, skb, false);
				tls_tx_imm = 1;
			पूर्ण
		पूर्ण
		अगर (likely(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NEED_HDR))
			credit_len += wr_size;
		credits_needed = DIV_ROUND_UP(credit_len, 16);
		अगर (!csk_flag_nochk(csk, CSK_TX_DATA_SENT)) अणु
			flowclen16 = send_tx_flowc_wr(sk, 1, tp->snd_nxt,
						      tp->rcv_nxt);
			अगर (flowclen16 <= 0)
				अवरोध;
			csk->wr_credits -= flowclen16;
			csk->wr_unacked += flowclen16;
			csk->wr_nondata += flowclen16;
			csk_set_flag(csk, CSK_TX_DATA_SENT);
		पूर्ण

		अगर (csk->wr_credits < credits_needed) अणु
			अगर (skb_ulp_tls_अंतरभूत(skb) &&
			    !skb_ulp_tls_iv_imm(skb))
				skb_shinfo(skb)->nr_frags--;
			अवरोध;
		पूर्ण

		__skb_unlink(skb, &csk->txq);
		skb_set_queue_mapping(skb, (csk->txq_idx << 1) |
				      CPL_PRIORITY_DATA);
		अगर (hws->ofld)
			hws->txqid = (skb->queue_mapping >> 1);
		skb->csum = (__क्रमce __wsum)(credits_needed + csk->wr_nondata);
		csk->wr_credits -= credits_needed;
		csk->wr_unacked += credits_needed;
		csk->wr_nondata = 0;
		enqueue_wr(csk, skb);

		अगर (likely(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NEED_HDR)) अणु
			अगर ((comp && csk->wr_unacked == credits_needed) ||
			    (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_COMPL) ||
			    csk->wr_unacked >= csk->wr_max_credits / 2) अणु
				completion = 1;
				csk->wr_unacked = 0;
			पूर्ण
			अगर (skb_ulp_tls_अंतरभूत(skb))
				make_tlstx_data_wr(sk, skb, tls_tx_imm,
						   tls_len, credits_needed);
			अन्यथा
				make_tx_data_wr(sk, skb, immdlen, len,
						credits_needed, completion);
			tp->snd_nxt += len;
			tp->lsndसमय = tcp_jअगरfies32;
			अगर (completion)
				ULP_SKB_CB(skb)->flags &= ~ULPCB_FLAG_NEED_HDR;
		पूर्ण अन्यथा अणु
			काष्ठा cpl_बंद_con_req *req = cplhdr(skb);
			अचिन्हित पूर्णांक cmd  = CPL_OPCODE_G(ntohl
					     (OPCODE_TID(req)));

			अगर (cmd == CPL_CLOSE_CON_REQ)
				csk_set_flag(csk,
					     CSK_CLOSE_CON_REQUESTED);

			अगर ((ULP_SKB_CB(skb)->flags & ULPCB_FLAG_COMPL) &&
			    (csk->wr_unacked >= csk->wr_max_credits / 2)) अणु
				req->wr.wr_hi |= htonl(FW_WR_COMPL_F);
				csk->wr_unacked = 0;
			पूर्ण
		पूर्ण
		total_size += skb->truesize;
		अगर (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_BARRIER)
			csk_set_flag(csk, CSK_TX_WAIT_IDLE);
		t4_set_arp_err_handler(skb, शून्य, arp_failure_discard);
		cxgb4_l2t_send(csk->egress_dev, skb, csk->l2t_entry);
	पूर्ण
	sk->sk_wmem_queued -= total_size;
	वापस total_size;
पूर्ण

अटल व्योम mark_urg(काष्ठा tcp_sock *tp, पूर्णांक flags,
		     काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(flags & MSG_OOB)) अणु
		tp->snd_up = tp->ग_लिखो_seq;
		ULP_SKB_CB(skb)->flags = ULPCB_FLAG_URG |
					 ULPCB_FLAG_BARRIER |
					 ULPCB_FLAG_NO_APPEND |
					 ULPCB_FLAG_NEED_HDR;
	पूर्ण
पूर्ण

/*
 * Returns true अगर a connection should send more data to TCP engine
 */
अटल bool should_push(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा chtls_dev *cdev = csk->cdev;
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/*
	 * If we've released our offload resources there's nothing to करो ...
	 */
	अगर (!cdev)
		वापस false;

	/*
	 * If there aren't any work requests in flight, or there isn't enough
	 * data in flight, or Nagle is off then send the current TX_DATA
	 * otherwise hold it and रुको to accumulate more data.
	 */
	वापस csk->wr_credits == csk->wr_max_credits ||
		(tp->nonagle & TCP_NAGLE_OFF);
पूर्ण

/*
 * Returns true अगर a TCP socket is corked.
 */
अटल bool corked(स्थिर काष्ठा tcp_sock *tp, पूर्णांक flags)
अणु
	वापस (flags & MSG_MORE) || (tp->nonagle & TCP_NAGLE_CORK);
पूर्ण

/*
 * Returns true अगर a send should try to push new data.
 */
अटल bool send_should_push(काष्ठा sock *sk, पूर्णांक flags)
अणु
	वापस should_push(sk) && !corked(tcp_sk(sk), flags);
पूर्ण

व्योम chtls_tcp_push(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	पूर्णांक qlen = skb_queue_len(&csk->txq);

	अगर (likely(qlen)) अणु
		काष्ठा sk_buff *skb = skb_peek_tail(&csk->txq);
		काष्ठा tcp_sock *tp = tcp_sk(sk);

		mark_urg(tp, flags, skb);

		अगर (!(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) &&
		    corked(tp, flags)) अणु
			ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_HOLD;
			वापस;
		पूर्ण

		ULP_SKB_CB(skb)->flags &= ~ULPCB_FLAG_HOLD;
		अगर (qlen == 1 &&
		    ((ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) ||
		     should_push(sk)))
			chtls_push_frames(csk, 1);
	पूर्ण
पूर्ण

/*
 * Calculate the size क्रम a new send sk_buff.  It's maximum size so we can
 * pack lots of data पूर्णांकo it, unless we plan to send it immediately, in which
 * हाल we size it more tightly.
 *
 * Note: we करोn't bother compensating for MSS < PAGE_SIZE because it doesn't
 * arise in normal हालs and when it करोes we are just wasting memory.
 */
अटल पूर्णांक select_size(काष्ठा sock *sk, पूर्णांक io_len, पूर्णांक flags, पूर्णांक len)
अणु
	स्थिर पूर्णांक pgअवरोध = SKB_MAX_HEAD(len);

	/*
	 * If the data wouldn't fit in the मुख्य body anyway, put only the
	 * header in the मुख्य body so it can use immediate data and place all
	 * the payload in page fragments.
	 */
	अगर (io_len > pgअवरोध)
		वापस 0;

	/*
	 * If we will be accumulating payload get a large मुख्य body.
	 */
	अगर (!send_should_push(sk, flags))
		वापस pgअवरोध;

	वापस io_len;
पूर्ण

व्योम skb_entail(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक flags)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ULP_SKB_CB(skb)->seq = tp->ग_लिखो_seq;
	ULP_SKB_CB(skb)->flags = flags;
	__skb_queue_tail(&csk->txq, skb);
	sk->sk_wmem_queued += skb->truesize;

	अगर (TCP_PAGE(sk) && TCP_OFF(sk)) अणु
		put_page(TCP_PAGE(sk));
		TCP_PAGE(sk) = शून्य;
		TCP_OFF(sk) = 0;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *get_tx_skb(काष्ठा sock *sk, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(size + TX_HEADER_LEN, sk->sk_allocation);
	अगर (likely(skb)) अणु
		skb_reserve(skb, TX_HEADER_LEN);
		skb_entail(sk, skb, ULPCB_FLAG_NEED_HDR);
		skb_reset_transport_header(skb);
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *get_record_skb(काष्ठा sock *sk, पूर्णांक size, bool zcopy)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा sk_buff *skb;

	skb = alloc_skb(((zcopy ? 0 : size) + TX_TLSHDR_LEN +
			KEY_ON_MEM_SZ + max_ivs_size(sk, size)),
			sk->sk_allocation);
	अगर (likely(skb)) अणु
		skb_reserve(skb, (TX_TLSHDR_LEN +
			    KEY_ON_MEM_SZ + max_ivs_size(sk, size)));
		skb_entail(sk, skb, ULPCB_FLAG_NEED_HDR);
		skb_reset_transport_header(skb);
		ULP_SKB_CB(skb)->ulp.tls.ofld = 1;
		ULP_SKB_CB(skb)->ulp.tls.type = csk->tlshws.type;
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम tx_skb_finalize(काष्ठा sk_buff *skb)
अणु
	काष्ठा ulp_skb_cb *cb = ULP_SKB_CB(skb);

	अगर (!(cb->flags & ULPCB_FLAG_NO_HDR))
		cb->flags = ULPCB_FLAG_NEED_HDR;
	cb->flags |= ULPCB_FLAG_NO_APPEND;
पूर्ण

अटल व्योम push_frames_अगर_head(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	अगर (skb_queue_len(&csk->txq) == 1)
		chtls_push_frames(csk, 1);
पूर्ण

अटल पूर्णांक chtls_skb_copy_to_page_nocache(काष्ठा sock *sk,
					  काष्ठा iov_iter *from,
					  काष्ठा sk_buff *skb,
					  काष्ठा page *page,
					  पूर्णांक off, पूर्णांक copy)
अणु
	पूर्णांक err;

	err = skb_करो_copy_data_nocache(sk, skb, from, page_address(page) +
				       off, copy, skb->len);
	अगर (err)
		वापस err;

	skb->len             += copy;
	skb->data_len        += copy;
	skb->truesize        += copy;
	sk->sk_wmem_queued   += copy;
	वापस 0;
पूर्ण

अटल bool csk_mem_मुक्त(काष्ठा chtls_dev *cdev, काष्ठा sock *sk)
अणु
	वापस (cdev->max_host_sndbuf - sk->sk_wmem_queued > 0);
पूर्ण

अटल पूर्णांक csk_रुको_memory(काष्ठा chtls_dev *cdev,
			   काष्ठा sock *sk, दीर्घ *समयo_p)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक err = 0;
	दीर्घ current_समयo;
	दीर्घ vm_रुको = 0;
	bool noblock;

	current_समयo = *समयo_p;
	noblock = (*समयo_p ? false : true);
	अगर (csk_mem_मुक्त(cdev, sk)) अणु
		current_समयo = (pअक्रमom_u32() % (HZ / 5)) + 2;
		vm_रुको = (pअक्रमom_u32() % (HZ / 5)) + 2;
	पूर्ण

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

		अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN))
			जाओ करो_error;
		अगर (!*समयo_p) अणु
			अगर (noblock)
				set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			जाओ करो_nonblock;
		पूर्ण
		अगर (संकेत_pending(current))
			जाओ करो_पूर्णांकerrupted;
		sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		अगर (csk_mem_मुक्त(cdev, sk) && !vm_रुको)
			अवरोध;

		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		sk->sk_ग_लिखो_pending++;
		sk_रुको_event(sk, &current_समयo, sk->sk_err ||
			      (sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
			      (csk_mem_मुक्त(cdev, sk) && !vm_रुको), &रुको);
		sk->sk_ग_लिखो_pending--;

		अगर (vm_रुको) अणु
			vm_रुको -= current_समयo;
			current_समयo = *समयo_p;
			अगर (current_समयo != MAX_SCHEDULE_TIMEOUT) अणु
				current_समयo -= vm_रुको;
				अगर (current_समयo < 0)
					current_समयo = 0;
			पूर्ण
			vm_रुको = 0;
		पूर्ण
		*समयo_p = current_समयo;
	पूर्ण
करो_rm_wq:
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस err;
करो_error:
	err = -EPIPE;
	जाओ करो_rm_wq;
करो_nonblock:
	err = -EAGAIN;
	जाओ करो_rm_wq;
करो_पूर्णांकerrupted:
	err = sock_पूर्णांकr_त्रुटि_सं(*समयo_p);
	जाओ करो_rm_wq;
पूर्ण

अटल पूर्णांक chtls_proccess_cmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
			       अचिन्हित अक्षर *record_type)
अणु
	काष्ठा cmsghdr *cmsg;
	पूर्णांक rc = -EINVAL;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;
		अगर (cmsg->cmsg_level != SOL_TLS)
			जारी;

		चयन (cmsg->cmsg_type) अणु
		हाल TLS_SET_RECORD_TYPE:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(*record_type)))
				वापस -EINVAL;

			अगर (msg->msg_flags & MSG_MORE)
				वापस -EINVAL;

			*record_type = *(अचिन्हित अक्षर *)CMSG_DATA(cmsg);
			rc = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक chtls_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा chtls_dev *cdev = csk->cdev;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक mss, flags, err;
	पूर्णांक recordsz = 0;
	पूर्णांक copied = 0;
	दीर्घ समयo;

	lock_sock(sk);
	flags = msg->msg_flags;
	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);

	अगर (!sk_in_state(sk, TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) अणु
		err = sk_stream_रुको_connect(sk, &समयo);
		अगर (err)
			जाओ out_err;
	पूर्ण

	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
	err = -EPIPE;
	अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN))
		जाओ out_err;

	mss = csk->mss;
	csk_set_flag(csk, CSK_TX_MORE_DATA);

	जबतक (msg_data_left(msg)) अणु
		पूर्णांक copy = 0;

		skb = skb_peek_tail(&csk->txq);
		अगर (skb) अणु
			copy = mss - skb->len;
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण
		अगर (!csk_mem_मुक्त(cdev, sk))
			जाओ रुको_क्रम_sndbuf;

		अगर (is_tls_tx(csk) && !csk->tlshws.txleft) अणु
			अचिन्हित अक्षर record_type = TLS_RECORD_TYPE_DATA;

			अगर (unlikely(msg->msg_controllen)) अणु
				err = chtls_proccess_cmsg(sk, msg,
							  &record_type);
				अगर (err)
					जाओ out_err;

				/* Aव्योम appending tls handshake, alert to tls data */
				अगर (skb)
					tx_skb_finalize(skb);
			पूर्ण

			recordsz = size;
			csk->tlshws.txleft = recordsz;
			csk->tlshws.type = record_type;
		पूर्ण

		अगर (!skb || (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) ||
		    copy <= 0) अणु
new_buf:
			अगर (skb) अणु
				tx_skb_finalize(skb);
				push_frames_अगर_head(sk);
			पूर्ण

			अगर (is_tls_tx(csk)) अणु
				skb = get_record_skb(sk,
						     select_size(sk,
								 recordsz,
								 flags,
								 TX_TLSHDR_LEN),
								 false);
			पूर्ण अन्यथा अणु
				skb = get_tx_skb(sk,
						 select_size(sk, size, flags,
							     TX_HEADER_LEN));
			पूर्ण
			अगर (unlikely(!skb))
				जाओ रुको_क्रम_memory;

			skb->ip_summed = CHECKSUM_UNNECESSARY;
			copy = mss;
		पूर्ण
		अगर (copy > size)
			copy = size;

		अगर (skb_tailroom(skb) > 0) अणु
			copy = min(copy, skb_tailroom(skb));
			अगर (is_tls_tx(csk))
				copy = min_t(पूर्णांक, copy, csk->tlshws.txleft);
			err = skb_add_data_nocache(sk, skb,
						   &msg->msg_iter, copy);
			अगर (err)
				जाओ करो_fault;
		पूर्ण अन्यथा अणु
			पूर्णांक i = skb_shinfo(skb)->nr_frags;
			काष्ठा page *page = TCP_PAGE(sk);
			पूर्णांक pg_size = PAGE_SIZE;
			पूर्णांक off = TCP_OFF(sk);
			bool merge;

			अगर (page)
				pg_size = page_size(page);
			अगर (off < pg_size &&
			    skb_can_coalesce(skb, i, page, off)) अणु
				merge = true;
				जाओ copy;
			पूर्ण
			merge = false;
			अगर (i == (is_tls_tx(csk) ? (MAX_SKB_FRAGS - 1) :
			    MAX_SKB_FRAGS))
				जाओ new_buf;

			अगर (page && off == pg_size) अणु
				put_page(page);
				TCP_PAGE(sk) = page = शून्य;
				pg_size = PAGE_SIZE;
			पूर्ण

			अगर (!page) अणु
				gfp_t gfp = sk->sk_allocation;
				पूर्णांक order = cdev->send_page_order;

				अगर (order) अणु
					page = alloc_pages(gfp | __GFP_COMP |
							   __GFP_NOWARN |
							   __GFP_NORETRY,
							   order);
					अगर (page)
						pg_size <<= order;
				पूर्ण
				अगर (!page) अणु
					page = alloc_page(gfp);
					pg_size = PAGE_SIZE;
				पूर्ण
				अगर (!page)
					जाओ रुको_क्रम_memory;
				off = 0;
			पूर्ण
copy:
			अगर (copy > pg_size - off)
				copy = pg_size - off;
			अगर (is_tls_tx(csk))
				copy = min_t(पूर्णांक, copy, csk->tlshws.txleft);

			err = chtls_skb_copy_to_page_nocache(sk, &msg->msg_iter,
							     skb, page,
							     off, copy);
			अगर (unlikely(err)) अणु
				अगर (!TCP_PAGE(sk)) अणु
					TCP_PAGE(sk) = page;
					TCP_OFF(sk) = 0;
				पूर्ण
				जाओ करो_fault;
			पूर्ण
			/* Update the skb. */
			अगर (merge) अणु
				skb_frag_size_add(
						&skb_shinfo(skb)->frags[i - 1],
						copy);
			पूर्ण अन्यथा अणु
				skb_fill_page_desc(skb, i, page, off, copy);
				अगर (off + copy < pg_size) अणु
					/* space left keep page */
					get_page(page);
					TCP_PAGE(sk) = page;
				पूर्ण अन्यथा अणु
					TCP_PAGE(sk) = शून्य;
				पूर्ण
			पूर्ण
			TCP_OFF(sk) = off + copy;
		पूर्ण
		अगर (unlikely(skb->len == mss))
			tx_skb_finalize(skb);
		tp->ग_लिखो_seq += copy;
		copied += copy;
		size -= copy;

		अगर (is_tls_tx(csk))
			csk->tlshws.txleft -= copy;

		अगर (corked(tp, flags) &&
		    (sk_stream_wspace(sk) < sk_stream_min_wspace(sk)))
			ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_NO_APPEND;

		अगर (size == 0)
			जाओ out;

		अगर (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND)
			push_frames_अगर_head(sk);
		जारी;
रुको_क्रम_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
रुको_क्रम_memory:
		err = csk_रुको_memory(cdev, sk, &समयo);
		अगर (err)
			जाओ करो_error;
	पूर्ण
out:
	csk_reset_flag(csk, CSK_TX_MORE_DATA);
	अगर (copied)
		chtls_tcp_push(sk, flags);
करोne:
	release_sock(sk);
	वापस copied;
करो_fault:
	अगर (!skb->len) अणु
		__skb_unlink(skb, &csk->txq);
		sk->sk_wmem_queued -= skb->truesize;
		__kमुक्त_skb(skb);
	पूर्ण
करो_error:
	अगर (copied)
		जाओ out;
out_err:
	अगर (csk_conn_अंतरभूत(csk))
		csk_reset_flag(csk, CSK_TX_MORE_DATA);
	copied = sk_stream_error(sk, flags, err);
	जाओ करोne;
पूर्ण

पूर्णांक chtls_sendpage(काष्ठा sock *sk, काष्ठा page *page,
		   पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_dev *cdev;
	पूर्णांक mss, err, copied;
	काष्ठा tcp_sock *tp;
	दीर्घ समयo;

	tp = tcp_sk(sk);
	copied = 0;
	csk = rcu_dereference_sk_user_data(sk);
	cdev = csk->cdev;
	lock_sock(sk);
	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);

	err = sk_stream_रुको_connect(sk, &समयo);
	अगर (!sk_in_state(sk, TCPF_ESTABLISHED | TCPF_CLOSE_WAIT) &&
	    err != 0)
		जाओ out_err;

	mss = csk->mss;
	csk_set_flag(csk, CSK_TX_MORE_DATA);

	जबतक (size > 0) अणु
		काष्ठा sk_buff *skb = skb_peek_tail(&csk->txq);
		पूर्णांक copy, i;

		अगर (!skb || (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) ||
		    (copy = mss - skb->len) <= 0) अणु
new_buf:
			अगर (!csk_mem_मुक्त(cdev, sk))
				जाओ रुको_क्रम_sndbuf;

			अगर (is_tls_tx(csk)) अणु
				skb = get_record_skb(sk,
						     select_size(sk, size,
								 flags,
								 TX_TLSHDR_LEN),
						     true);
			पूर्ण अन्यथा अणु
				skb = get_tx_skb(sk, 0);
			पूर्ण
			अगर (!skb)
				जाओ रुको_क्रम_memory;
			copy = mss;
		पूर्ण
		अगर (copy > size)
			copy = size;

		i = skb_shinfo(skb)->nr_frags;
		अगर (skb_can_coalesce(skb, i, page, offset)) अणु
			skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
		पूर्ण अन्यथा अगर (i < MAX_SKB_FRAGS) अणु
			get_page(page);
			skb_fill_page_desc(skb, i, page, offset, copy);
		पूर्ण अन्यथा अणु
			tx_skb_finalize(skb);
			push_frames_अगर_head(sk);
			जाओ new_buf;
		पूर्ण

		skb->len += copy;
		अगर (skb->len == mss)
			tx_skb_finalize(skb);
		skb->data_len += copy;
		skb->truesize += copy;
		sk->sk_wmem_queued += copy;
		tp->ग_लिखो_seq += copy;
		copied += copy;
		offset += copy;
		size -= copy;

		अगर (corked(tp, flags) &&
		    (sk_stream_wspace(sk) < sk_stream_min_wspace(sk)))
			ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_NO_APPEND;

		अगर (!size)
			अवरोध;

		अगर (unlikely(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND))
			push_frames_अगर_head(sk);
		जारी;
रुको_क्रम_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
रुको_क्रम_memory:
		err = csk_रुको_memory(cdev, sk, &समयo);
		अगर (err)
			जाओ करो_error;
	पूर्ण
out:
	csk_reset_flag(csk, CSK_TX_MORE_DATA);
	अगर (copied)
		chtls_tcp_push(sk, flags);
करोne:
	release_sock(sk);
	वापस copied;

करो_error:
	अगर (copied)
		जाओ out;

out_err:
	अगर (csk_conn_अंतरभूत(csk))
		csk_reset_flag(csk, CSK_TX_MORE_DATA);
	copied = sk_stream_error(sk, flags, err);
	जाओ करोne;
पूर्ण

अटल व्योम chtls_select_winकरोw(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित पूर्णांक wnd = tp->rcv_wnd;

	wnd = max_t(अचिन्हित पूर्णांक, wnd, tcp_full_space(sk));
	wnd = max_t(अचिन्हित पूर्णांक, MIN_RCV_WND, wnd);

	अगर (wnd > MAX_RCV_WND)
		wnd = MAX_RCV_WND;

/*
 * Check अगर we need to grow the receive winकरोw in response to an increase in
 * the socket's receive buffer size.  Some applications increase the buffer
 * size dynamically and rely on the winकरोw to grow accordingly.
 */

	अगर (wnd > tp->rcv_wnd) अणु
		tp->rcv_wup -= wnd - tp->rcv_wnd;
		tp->rcv_wnd = wnd;
		/* Mark the receive winकरोw as updated */
		csk_reset_flag(csk, CSK_UPDATE_RCV_WND);
	पूर्ण
पूर्ण

/*
 * Send RX credits through an RX_DATA_ACK CPL message.  We are permitted
 * to वापस without sending the message in हाल we cannot allocate
 * an sk_buff.  Returns the number of credits sent.
 */
अटल u32 send_rx_credits(काष्ठा chtls_sock *csk, u32 credits)
अणु
	काष्ठा cpl_rx_data_ack *req;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(माप(*req), GFP_ATOMIC);
	अगर (!skb)
		वापस 0;
	__skb_put(skb, माप(*req));
	req = (काष्ठा cpl_rx_data_ack *)skb->head;

	set_wr_txq(skb, CPL_PRIORITY_ACK, csk->port_id);
	INIT_TP_WR(req, csk->tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_RX_DATA_ACK,
						    csk->tid));
	req->credit_dack = cpu_to_be32(RX_CREDITS_V(credits) |
				       RX_FORCE_ACK_F);
	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
	वापस credits;
पूर्ण

#घोषणा CREDIT_RETURN_STATE (TCPF_ESTABLISHED | \
			     TCPF_FIN_WAIT1 | \
			     TCPF_FIN_WAIT2)

/*
 * Called after some received data has been पढ़ो.  It वापसs RX credits
 * to the HW क्रम the amount of data processed.
 */
अटल व्योम chtls_cleanup_rbuf(काष्ठा sock *sk, पूर्णांक copied)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा tcp_sock *tp;
	पूर्णांक must_send;
	u32 credits;
	u32 thres;

	thres = 15 * 1024;

	अगर (!sk_in_state(sk, CREDIT_RETURN_STATE))
		वापस;

	chtls_select_winकरोw(sk);
	tp = tcp_sk(sk);
	credits = tp->copied_seq - tp->rcv_wup;
	अगर (unlikely(!credits))
		वापस;

/*
 * For coalescing to work effectively ensure the receive winकरोw has
 * at least 16KB left.
 */
	must_send = credits + 16384 >= tp->rcv_wnd;

	अगर (must_send || credits >= thres)
		tp->rcv_wup += send_rx_credits(csk, credits);
पूर्ण

अटल पूर्णांक chtls_pt_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			    पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा chtls_hws *hws = &csk->tlshws;
	काष्ठा net_device *dev = csk->egress_dev;
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	अचिन्हित दीर्घ avail;
	पूर्णांक buffers_मुक्तd;
	पूर्णांक copied = 0;
	पूर्णांक target;
	दीर्घ समयo;

	buffers_मुक्तd = 0;

	समयo = sock_rcvसमयo(sk, nonblock);
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);

	अगर (unlikely(csk_flag(sk, CSK_UPDATE_RCV_WND)))
		chtls_cleanup_rbuf(sk, copied);

	करो अणु
		काष्ठा sk_buff *skb;
		u32 offset = 0;

		अगर (unlikely(tp->urg_data &&
			     tp->urg_seq == tp->copied_seq)) अणु
			अगर (copied)
				अवरोध;
			अगर (संकेत_pending(current)) अणु
				copied = समयo ? sock_पूर्णांकr_त्रुटि_सं(समयo) :
					-EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण
		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb)
			जाओ found_ok_skb;
		अगर (csk->wr_credits &&
		    skb_queue_len(&csk->txq) &&
		    chtls_push_frames(csk, csk->wr_credits ==
				      csk->wr_max_credits))
			sk->sk_ग_लिखो_space(sk);

		अगर (copied >= target && !READ_ONCE(sk->sk_backlog.tail))
			अवरोध;

		अगर (copied) अणु
			अगर (sk->sk_err || sk->sk_state == TCP_CLOSE ||
			    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			    संकेत_pending(current))
				अवरोध;

			अगर (!समयo)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (sock_flag(sk, SOCK_DONE))
				अवरोध;
			अगर (sk->sk_err) अणु
				copied = sock_error(sk);
				अवरोध;
			पूर्ण
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				अवरोध;
			अगर (sk->sk_state == TCP_CLOSE) अणु
				copied = -ENOTCONN;
				अवरोध;
			पूर्ण
			अगर (!समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण
			अगर (संकेत_pending(current)) अणु
				copied = sock_पूर्णांकr_त्रुटि_सं(समयo);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (READ_ONCE(sk->sk_backlog.tail)) अणु
			release_sock(sk);
			lock_sock(sk);
			chtls_cleanup_rbuf(sk, copied);
			जारी;
		पूर्ण

		अगर (copied >= target)
			अवरोध;
		chtls_cleanup_rbuf(sk, copied);
		sk_रुको_data(sk, &समयo, शून्य);
		जारी;
found_ok_skb:
		अगर (!skb->len) अणु
			skb_dst_set(skb, शून्य);
			__skb_unlink(skb, &sk->sk_receive_queue);
			kमुक्त_skb(skb);

			अगर (!copied && !समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण

			अगर (copied < target) अणु
				release_sock(sk);
				lock_sock(sk);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
		offset = hws->copied_seq;
		avail = skb->len - offset;
		अगर (len < avail)
			avail = len;

		अगर (unlikely(tp->urg_data)) अणु
			u32 urg_offset = tp->urg_seq - tp->copied_seq;

			अगर (urg_offset < avail) अणु
				अगर (urg_offset) अणु
					avail = urg_offset;
				पूर्ण अन्यथा अगर (!sock_flag(sk, SOCK_URGINLINE)) अणु
					/* First byte is urgent, skip */
					tp->copied_seq++;
					offset++;
					avail--;
					अगर (!avail)
						जाओ skip_copy;
				पूर्ण
			पूर्ण
		पूर्ण
		/* Set record type अगर not alपढ़ोy करोne. For a non-data record,
		 * करो not proceed अगर record type could not be copied.
		 */
		अगर (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_TLS_HDR) अणु
			काष्ठा tls_hdr *thdr = (काष्ठा tls_hdr *)skb->data;
			पूर्णांक cerr = 0;

			cerr = put_cmsg(msg, SOL_TLS, TLS_GET_RECORD_TYPE,
					माप(thdr->type), &thdr->type);

			अगर (cerr && thdr->type != TLS_RECORD_TYPE_DATA) अणु
				copied = -EIO;
				अवरोध;
			पूर्ण
			/*  करोn't send tls header, skip copy */
			जाओ skip_copy;
		पूर्ण

		अगर (skb_copy_datagram_msg(skb, offset, msg, avail)) अणु
			अगर (!copied) अणु
				copied = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण

		copied += avail;
		len -= avail;
		hws->copied_seq += avail;
skip_copy:
		अगर (tp->urg_data && after(tp->copied_seq, tp->urg_seq))
			tp->urg_data = 0;

		अगर ((avail + offset) >= skb->len) अणु
			काष्ठा sk_buff *next_skb;
			अगर (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_TLS_HDR) अणु
				tp->copied_seq += skb->len;
				hws->rcvpld = skb->hdr_len;
			पूर्ण अन्यथा अणु
				atomic_inc(&adap->chcr_stats.tls_pdu_rx);
				tp->copied_seq += hws->rcvpld;
			पूर्ण
			chtls_मुक्त_skb(sk, skb);
			buffers_मुक्तd++;
			hws->copied_seq = 0;
			next_skb = skb_peek(&sk->sk_receive_queue);
			अगर (copied >= target && !next_skb)
				अवरोध;
			अगर (ULP_SKB_CB(next_skb)->flags & ULPCB_FLAG_TLS_HDR)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (len > 0);

	अगर (buffers_मुक्तd)
		chtls_cleanup_rbuf(sk, copied);
	release_sock(sk);
	वापस copied;
पूर्ण

/*
 * Peek at data in a socket's receive buffer.
 */
अटल पूर्णांक peekmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
		   माप_प्रकार len, पूर्णांक nonblock, पूर्णांक flags)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 peek_seq, offset;
	काष्ठा sk_buff *skb;
	पूर्णांक copied = 0;
	माप_प्रकार avail;          /* amount of available data in current skb */
	दीर्घ समयo;

	lock_sock(sk);
	समयo = sock_rcvसमयo(sk, nonblock);
	peek_seq = tp->copied_seq;

	करो अणु
		अगर (unlikely(tp->urg_data && tp->urg_seq == peek_seq)) अणु
			अगर (copied)
				अवरोध;
			अगर (संकेत_pending(current)) अणु
				copied = समयo ? sock_पूर्णांकr_त्रुटि_सं(समयo) :
				-EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण

		skb_queue_walk(&sk->sk_receive_queue, skb) अणु
			offset = peek_seq - ULP_SKB_CB(skb)->seq;
			अगर (offset < skb->len)
				जाओ found_ok_skb;
		पूर्ण

		/* empty receive queue */
		अगर (copied)
			अवरोध;
		अगर (sock_flag(sk, SOCK_DONE))
			अवरोध;
		अगर (sk->sk_err) अणु
			copied = sock_error(sk);
			अवरोध;
		पूर्ण
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			अवरोध;
		अगर (sk->sk_state == TCP_CLOSE) अणु
			copied = -ENOTCONN;
			अवरोध;
		पूर्ण
		अगर (!समयo) अणु
			copied = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			copied = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण

		अगर (READ_ONCE(sk->sk_backlog.tail)) अणु
			/* Do not sleep, just process backlog. */
			release_sock(sk);
			lock_sock(sk);
		पूर्ण अन्यथा अणु
			sk_रुको_data(sk, &समयo, शून्य);
		पूर्ण

		अगर (unlikely(peek_seq != tp->copied_seq)) अणु
			अगर (net_ratelimit())
				pr_info("TCP(%s:%d), race in MSG_PEEK.\n",
					current->comm, current->pid);
			peek_seq = tp->copied_seq;
		पूर्ण
		जारी;

found_ok_skb:
		avail = skb->len - offset;
		अगर (len < avail)
			avail = len;
		/*
		 * Do we have urgent data here?  We need to skip over the
		 * urgent byte.
		 */
		अगर (unlikely(tp->urg_data)) अणु
			u32 urg_offset = tp->urg_seq - peek_seq;

			अगर (urg_offset < avail) अणु
				/*
				 * The amount of data we are preparing to copy
				 * contains urgent data.
				 */
				अगर (!urg_offset) अणु /* First byte is urgent */
					अगर (!sock_flag(sk, SOCK_URGINLINE)) अणु
						peek_seq++;
						offset++;
						avail--;
					पूर्ण
					अगर (!avail)
						जारी;
				पूर्ण अन्यथा अणु
					/* stop लघु of the urgent data */
					avail = urg_offset;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * If MSG_TRUNC is specअगरied the data is discarded.
		 */
		अगर (likely(!(flags & MSG_TRUNC)))
			अगर (skb_copy_datagram_msg(skb, offset, msg, len)) अणु
				अगर (!copied) अणु
					copied = -EFAULT;
					अवरोध;
				पूर्ण
			पूर्ण
		peek_seq += avail;
		copied += avail;
		len -= avail;
	पूर्ण जबतक (len > 0);

	release_sock(sk);
	वापस copied;
पूर्ण

पूर्णांक chtls_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		  पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा chtls_sock *csk;
	अचिन्हित दीर्घ avail;    /* amount of available data in current skb */
	पूर्णांक buffers_मुक्तd;
	पूर्णांक copied = 0;
	दीर्घ समयo;
	पूर्णांक target;             /* Read at least this many bytes */

	buffers_मुक्तd = 0;

	अगर (unlikely(flags & MSG_OOB))
		वापस tcp_prot.recvmsg(sk, msg, len, nonblock, flags,
					addr_len);

	अगर (unlikely(flags & MSG_PEEK))
		वापस peekmsg(sk, msg, len, nonblock, flags);

	अगर (sk_can_busy_loop(sk) &&
	    skb_queue_empty_lockless(&sk->sk_receive_queue) &&
	    sk->sk_state == TCP_ESTABLISHED)
		sk_busy_loop(sk, nonblock);

	lock_sock(sk);
	csk = rcu_dereference_sk_user_data(sk);

	अगर (is_tls_rx(csk))
		वापस chtls_pt_recvmsg(sk, msg, len, nonblock,
					flags, addr_len);

	समयo = sock_rcvसमयo(sk, nonblock);
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);

	अगर (unlikely(csk_flag(sk, CSK_UPDATE_RCV_WND)))
		chtls_cleanup_rbuf(sk, copied);

	करो अणु
		काष्ठा sk_buff *skb;
		u32 offset;

		अगर (unlikely(tp->urg_data && tp->urg_seq == tp->copied_seq)) अणु
			अगर (copied)
				अवरोध;
			अगर (संकेत_pending(current)) अणु
				copied = समयo ? sock_पूर्णांकr_त्रुटि_सं(समयo) :
					-EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण

		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb)
			जाओ found_ok_skb;

		अगर (csk->wr_credits &&
		    skb_queue_len(&csk->txq) &&
		    chtls_push_frames(csk, csk->wr_credits ==
				      csk->wr_max_credits))
			sk->sk_ग_लिखो_space(sk);

		अगर (copied >= target && !READ_ONCE(sk->sk_backlog.tail))
			अवरोध;

		अगर (copied) अणु
			अगर (sk->sk_err || sk->sk_state == TCP_CLOSE ||
			    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			    संकेत_pending(current))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (sock_flag(sk, SOCK_DONE))
				अवरोध;
			अगर (sk->sk_err) अणु
				copied = sock_error(sk);
				अवरोध;
			पूर्ण
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				अवरोध;
			अगर (sk->sk_state == TCP_CLOSE) अणु
				copied = -ENOTCONN;
				अवरोध;
			पूर्ण
			अगर (!समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण
			अगर (संकेत_pending(current)) अणु
				copied = sock_पूर्णांकr_त्रुटि_सं(समयo);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (READ_ONCE(sk->sk_backlog.tail)) अणु
			release_sock(sk);
			lock_sock(sk);
			chtls_cleanup_rbuf(sk, copied);
			जारी;
		पूर्ण

		अगर (copied >= target)
			अवरोध;
		chtls_cleanup_rbuf(sk, copied);
		sk_रुको_data(sk, &समयo, शून्य);
		जारी;

found_ok_skb:
		अगर (!skb->len) अणु
			chtls_kमुक्त_skb(sk, skb);
			अगर (!copied && !समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण

			अगर (copied < target)
				जारी;

			अवरोध;
		पूर्ण

		offset = tp->copied_seq - ULP_SKB_CB(skb)->seq;
		avail = skb->len - offset;
		अगर (len < avail)
			avail = len;

		अगर (unlikely(tp->urg_data)) अणु
			u32 urg_offset = tp->urg_seq - tp->copied_seq;

			अगर (urg_offset < avail) अणु
				अगर (urg_offset) अणु
					avail = urg_offset;
				पूर्ण अन्यथा अगर (!sock_flag(sk, SOCK_URGINLINE)) अणु
					tp->copied_seq++;
					offset++;
					avail--;
					अगर (!avail)
						जाओ skip_copy;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (likely(!(flags & MSG_TRUNC))) अणु
			अगर (skb_copy_datagram_msg(skb, offset,
						  msg, avail)) अणु
				अगर (!copied) अणु
					copied = -EFAULT;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		tp->copied_seq += avail;
		copied += avail;
		len -= avail;

skip_copy:
		अगर (tp->urg_data && after(tp->copied_seq, tp->urg_seq))
			tp->urg_data = 0;

		अगर (avail + offset >= skb->len) अणु
			chtls_मुक्त_skb(sk, skb);
			buffers_मुक्तd++;

			अगर  (copied >= target &&
			     !skb_peek(&sk->sk_receive_queue))
				अवरोध;
		पूर्ण
	पूर्ण जबतक (len > 0);

	अगर (buffers_मुक्तd)
		chtls_cleanup_rbuf(sk, copied);

	release_sock(sk);
	वापस copied;
पूर्ण
