<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Chelsio Communications.  All rights reserved. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <crypto/aes.h>
#समावेश "chcr_ktls.h"

अटल LIST_HEAD(uld_ctx_list);
अटल DEFINE_MUTEX(dev_mutex);

/* chcr_get_nfrags_to_send: get the reमुख्यing nfrags after start offset
 * @skb: skb
 * @start: start offset.
 * @len: how much data to send after @start
 */
अटल पूर्णांक chcr_get_nfrags_to_send(काष्ठा sk_buff *skb, u32 start, u32 len)
अणु
	काष्ठा skb_shared_info *si = skb_shinfo(skb);
	u32 frag_size, skb_linear_data_len = skb_headlen(skb);
	u8 nfrags = 0, frag_idx = 0;
	skb_frag_t *frag;

	/* अगर its a linear skb then वापस 1 */
	अगर (!skb_is_nonlinear(skb))
		वापस 1;

	अगर (unlikely(start < skb_linear_data_len)) अणु
		frag_size = min(len, skb_linear_data_len - start);
	पूर्ण अन्यथा अणु
		start -= skb_linear_data_len;

		frag = &si->frags[frag_idx];
		frag_size = skb_frag_size(frag);
		जबतक (start >= frag_size) अणु
			start -= frag_size;
			frag_idx++;
			frag = &si->frags[frag_idx];
			frag_size = skb_frag_size(frag);
		पूर्ण
		frag_size = min(len, skb_frag_size(frag) - start);
	पूर्ण
	len -= frag_size;
	nfrags++;

	जबतक (len) अणु
		frag_size = min(len, skb_frag_size(&si->frags[frag_idx]));
		len -= frag_size;
		nfrags++;
		frag_idx++;
	पूर्ण
	वापस nfrags;
पूर्ण

अटल पूर्णांक chcr_init_tcb_fields(काष्ठा chcr_ktls_info *tx_info);
अटल व्योम clear_conn_resources(काष्ठा chcr_ktls_info *tx_info);
/*
 * chcr_ktls_save_keys: calculate and save crypto keys.
 * @tx_info - driver specअगरic tls info.
 * @crypto_info - tls crypto inक्रमmation.
 * @direction - TX/RX direction.
 * वापस - SUCCESS/FAILURE.
 */
अटल पूर्णांक chcr_ktls_save_keys(काष्ठा chcr_ktls_info *tx_info,
			       काष्ठा tls_crypto_info *crypto_info,
			       क्रमागत tls_offload_ctx_dir direction)
अणु
	पूर्णांक ck_size, key_ctx_size, mac_key_size, keylen, ghash_size, ret;
	अचिन्हित अक्षर ghash_h[TLS_CIPHER_AES_GCM_256_TAG_SIZE];
	काष्ठा tls12_crypto_info_aes_gcm_128 *info_128_gcm;
	काष्ठा ktls_key_ctx *kctx = &tx_info->key_ctx;
	काष्ठा crypto_aes_ctx aes_ctx;
	अचिन्हित अक्षर *key, *salt;

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128:
		info_128_gcm =
			(काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info;
		keylen = TLS_CIPHER_AES_GCM_128_KEY_SIZE;
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
		tx_info->salt_size = TLS_CIPHER_AES_GCM_128_SALT_SIZE;
		mac_key_size = CHCR_KEYCTX_MAC_KEY_SIZE_128;
		tx_info->iv_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		tx_info->iv = be64_to_cpu(*(__be64 *)info_128_gcm->iv);

		ghash_size = TLS_CIPHER_AES_GCM_128_TAG_SIZE;
		key = info_128_gcm->key;
		salt = info_128_gcm->salt;
		tx_info->record_no = *(u64 *)info_128_gcm->rec_seq;

		/* The SCMD fields used when encrypting a full TLS
		 * record. Its a one समय calculation till the
		 * connection exists.
		 */
		tx_info->scmd0_seqno_numivs =
			SCMD_SEQ_NO_CTRL_V(CHCR_SCMD_SEQ_NO_CTRL_64BIT) |
			SCMD_CIPH_AUTH_SEQ_CTRL_F |
			SCMD_PROTO_VERSION_V(CHCR_SCMD_PROTO_VERSION_TLS) |
			SCMD_CIPH_MODE_V(CHCR_SCMD_CIPHER_MODE_AES_GCM) |
			SCMD_AUTH_MODE_V(CHCR_SCMD_AUTH_MODE_GHASH) |
			SCMD_IV_SIZE_V(TLS_CIPHER_AES_GCM_128_IV_SIZE >> 1) |
			SCMD_NUM_IVS_V(1);

		/* keys will be sent अंतरभूत. */
		tx_info->scmd0_ivgen_hdrlen = SCMD_KEY_CTX_INLINE_F;

		/* The SCMD fields used when encrypting a partial TLS
		 * record (no trailer and possibly a truncated payload).
		 */
		tx_info->scmd0_लघु_seqno_numivs =
			SCMD_CIPH_AUTH_SEQ_CTRL_F |
			SCMD_PROTO_VERSION_V(CHCR_SCMD_PROTO_VERSION_GENERIC) |
			SCMD_CIPH_MODE_V(CHCR_SCMD_CIPHER_MODE_AES_CTR) |
			SCMD_IV_SIZE_V(AES_BLOCK_LEN >> 1);

		tx_info->scmd0_लघु_ivgen_hdrlen =
			tx_info->scmd0_ivgen_hdrlen | SCMD_AADIVDROP_F;

		अवरोध;

	शेष:
		pr_err("GCM: cipher type 0x%x not supported\n",
		       crypto_info->cipher_type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	key_ctx_size = CHCR_KTLS_KEY_CTX_LEN +
		       roundup(keylen, 16) + ghash_size;
	/* Calculate the H = CIPH(K, 0 repeated 16 बार).
	 * It will go in key context
	 */

	ret = aes_expandkey(&aes_ctx, key, keylen);
	अगर (ret)
		जाओ out;

	स_रखो(ghash_h, 0, ghash_size);
	aes_encrypt(&aes_ctx, ghash_h, ghash_h);
	memzero_explicit(&aes_ctx, माप(aes_ctx));

	/* fill the Key context */
	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		kctx->ctx_hdr = FILL_KEY_CTX_HDR(ck_size,
						 mac_key_size,
						 key_ctx_size >> 4);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(kctx->salt, salt, tx_info->salt_size);
	स_नकल(kctx->key, key, keylen);
	स_नकल(kctx->key + keylen, ghash_h, ghash_size);
	tx_info->key_ctx_len = key_ctx_size;

out:
	वापस ret;
पूर्ण

/*
 * chcr_ktls_act_खोलो_req: creates TCB entry क्रम ipv4 connection.
 * @sk - tcp socket.
 * @tx_info - driver specअगरic tls info.
 * @atid - connection active tid.
 * वापस - send success/failure.
 */
अटल पूर्णांक chcr_ktls_act_खोलो_req(काष्ठा sock *sk,
				  काष्ठा chcr_ktls_info *tx_info,
				  पूर्णांक atid)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा cpl_t6_act_खोलो_req *cpl6;
	काष्ठा cpl_act_खोलो_req *cpl;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;
	पूर्णांक qid_atid;
	u64 options;

	len = माप(*cpl6);
	skb = alloc_skb(len, GFP_KERNEL);
	अगर (unlikely(!skb))
		वापस -ENOMEM;
	/* mark it a control pkt */
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, tx_info->port_id);

	cpl6 = __skb_put_zero(skb, len);
	cpl = (काष्ठा cpl_act_खोलो_req *)cpl6;
	INIT_TP_WR(cpl6, 0);
	qid_atid = TID_QID_V(tx_info->rx_qid) |
		   TID_TID_V(atid);
	OPCODE_TID(cpl) = htonl(MK_OPCODE_TID(CPL_ACT_OPEN_REQ, qid_atid));
	cpl->local_port = inet->inet_sport;
	cpl->peer_port = inet->inet_dport;
	cpl->local_ip = inet->inet_rcv_saddr;
	cpl->peer_ip = inet->inet_daddr;

	/* fill first 64 bit option field. */
	options = TCAM_BYPASS_F | ULP_MODE_V(ULP_MODE_NONE) | NON_OFFLOAD_F |
		  SMAC_SEL_V(tx_info->smt_idx) | TX_CHAN_V(tx_info->tx_chan);
	cpl->opt0 = cpu_to_be64(options);

	/* next 64 bit option field. */
	options =
		TX_QUEUE_V(tx_info->adap->params.tp.tx_modq[tx_info->tx_chan]);
	cpl->opt2 = htonl(options);

	वापस cxgb4_l2t_send(tx_info->netdev, skb, tx_info->l2te);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/*
 * chcr_ktls_act_खोलो_req6: creates TCB entry क्रम ipv6 connection.
 * @sk - tcp socket.
 * @tx_info - driver specअगरic tls info.
 * @atid - connection active tid.
 * वापस - send success/failure.
 */
अटल पूर्णांक chcr_ktls_act_खोलो_req6(काष्ठा sock *sk,
				   काष्ठा chcr_ktls_info *tx_info,
				   पूर्णांक atid)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा cpl_t6_act_खोलो_req6 *cpl6;
	काष्ठा cpl_act_खोलो_req6 *cpl;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;
	पूर्णांक qid_atid;
	u64 options;

	len = माप(*cpl6);
	skb = alloc_skb(len, GFP_KERNEL);
	अगर (unlikely(!skb))
		वापस -ENOMEM;
	/* mark it a control pkt */
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, tx_info->port_id);

	cpl6 = __skb_put_zero(skb, len);
	cpl = (काष्ठा cpl_act_खोलो_req6 *)cpl6;
	INIT_TP_WR(cpl6, 0);
	qid_atid = TID_QID_V(tx_info->rx_qid) | TID_TID_V(atid);
	OPCODE_TID(cpl) = htonl(MK_OPCODE_TID(CPL_ACT_OPEN_REQ6, qid_atid));
	cpl->local_port = inet->inet_sport;
	cpl->peer_port = inet->inet_dport;
	cpl->local_ip_hi = *(__be64 *)&sk->sk_v6_rcv_saddr.in6_u.u6_addr8[0];
	cpl->local_ip_lo = *(__be64 *)&sk->sk_v6_rcv_saddr.in6_u.u6_addr8[8];
	cpl->peer_ip_hi = *(__be64 *)&sk->sk_v6_daddr.in6_u.u6_addr8[0];
	cpl->peer_ip_lo = *(__be64 *)&sk->sk_v6_daddr.in6_u.u6_addr8[8];

	/* first 64 bit option field. */
	options = TCAM_BYPASS_F | ULP_MODE_V(ULP_MODE_NONE) | NON_OFFLOAD_F |
		  SMAC_SEL_V(tx_info->smt_idx) | TX_CHAN_V(tx_info->tx_chan);
	cpl->opt0 = cpu_to_be64(options);
	/* next 64 bit option field. */
	options =
		TX_QUEUE_V(tx_info->adap->params.tp.tx_modq[tx_info->tx_chan]);
	cpl->opt2 = htonl(options);

	वापस cxgb4_l2t_send(tx_info->netdev, skb, tx_info->l2te);
पूर्ण
#पूर्ण_अगर /* #अगर IS_ENABLED(CONFIG_IPV6) */

/*
 * chcr_setup_connection:  create a TCB entry so that TP will क्रमm tcp packets.
 * @sk - tcp socket.
 * @tx_info - driver specअगरic tls info.
 * वापस: NET_TX_OK/NET_XMIT_DROP
 */
अटल पूर्णांक chcr_setup_connection(काष्ठा sock *sk,
				 काष्ठा chcr_ktls_info *tx_info)
अणु
	काष्ठा tid_info *t = &tx_info->adap->tids;
	पूर्णांक atid, ret = 0;

	atid = cxgb4_alloc_atid(t, tx_info);
	अगर (atid == -1)
		वापस -EINVAL;

	tx_info->atid = atid;

	अगर (tx_info->ip_family == AF_INET) अणु
		ret = chcr_ktls_act_खोलो_req(sk, tx_info, atid);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		ret = cxgb4_clip_get(tx_info->netdev, (स्थिर u32 *)
				     &sk->sk_v6_rcv_saddr,
				     1);
		अगर (ret)
			वापस ret;
		ret = chcr_ktls_act_खोलो_req6(sk, tx_info, atid);
#पूर्ण_अगर
	पूर्ण

	/* अगर वापस type is NET_XMIT_CN, msg will be sent but delayed, mark ret
	 * success, अगर any other वापस type clear atid and वापस that failure.
	 */
	अगर (ret) अणु
		अगर (ret == NET_XMIT_CN) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
#अगर IS_ENABLED(CONFIG_IPV6)
			/* clear clip entry */
			अगर (tx_info->ip_family == AF_INET6)
				cxgb4_clip_release(tx_info->netdev,
						   (स्थिर u32 *)
						   &sk->sk_v6_rcv_saddr,
						   1);
#पूर्ण_अगर
			cxgb4_मुक्त_atid(t, atid);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * chcr_set_tcb_field: update tcb fields.
 * @tx_info - driver specअगरic tls info.
 * @word - TCB word.
 * @mask - TCB word related mask.
 * @val - TCB word related value.
 * @no_reply - set 1 अगर not looking क्रम TP response.
 */
अटल पूर्णांक chcr_set_tcb_field(काष्ठा chcr_ktls_info *tx_info, u16 word,
			      u64 mask, u64 val, पूर्णांक no_reply)
अणु
	काष्ठा cpl_set_tcb_field *req;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(माप(काष्ठा cpl_set_tcb_field), GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	req = (काष्ठा cpl_set_tcb_field *)__skb_put_zero(skb, माप(*req));
	INIT_TP_WR_CPL(req, CPL_SET_TCB_FIELD, tx_info->tid);
	req->reply_ctrl = htons(QUEUENO_V(tx_info->rx_qid) |
				NO_REPLY_V(no_reply));
	req->word_cookie = htons(TCB_WORD_V(word));
	req->mask = cpu_to_be64(mask);
	req->val = cpu_to_be64(val);

	set_wr_txq(skb, CPL_PRIORITY_CONTROL, tx_info->port_id);
	वापस cxgb4_ofld_send(tx_info->netdev, skb);
पूर्ण

/*
 * chcr_ktls_dev_del:  call back क्रम tls_dev_del.
 * Remove the tid and l2t entry and बंद the connection.
 * it per connection basis.
 * @netdev - net device.
 * @tls_cts - tls context.
 * @direction - TX/RX crypto direction
 */
अटल व्योम chcr_ktls_dev_del(काष्ठा net_device *netdev,
			      काष्ठा tls_context *tls_ctx,
			      क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा chcr_ktls_ofld_ctx_tx *tx_ctx =
				chcr_get_ktls_tx_context(tls_ctx);
	काष्ठा chcr_ktls_info *tx_info = tx_ctx->chcr_info;
	काष्ठा ch_ktls_port_stats_debug *port_stats;
	काष्ठा chcr_ktls_uld_ctx *u_ctx;

	अगर (!tx_info)
		वापस;

	u_ctx = tx_info->adap->uld[CXGB4_ULD_KTLS].handle;
	अगर (u_ctx && u_ctx->detach)
		वापस;
	/* clear l2t entry */
	अगर (tx_info->l2te)
		cxgb4_l2t_release(tx_info->l2te);

#अगर IS_ENABLED(CONFIG_IPV6)
	/* clear clip entry */
	अगर (tx_info->ip_family == AF_INET6)
		cxgb4_clip_release(netdev, (स्थिर u32 *)
				   &tx_info->sk->sk_v6_rcv_saddr,
				   1);
#पूर्ण_अगर

	/* clear tid */
	अगर (tx_info->tid != -1) अणु
		cxgb4_हटाओ_tid(&tx_info->adap->tids, tx_info->tx_chan,
				 tx_info->tid, tx_info->ip_family);

		xa_erase(&u_ctx->tid_list, tx_info->tid);
	पूर्ण

	port_stats = &tx_info->adap->ch_ktls_stats.ktls_port[tx_info->port_id];
	atomic64_inc(&port_stats->ktls_tx_connection_बंद);
	kvमुक्त(tx_info);
	tx_ctx->chcr_info = शून्य;
	/* release module refcount */
	module_put(THIS_MODULE);
पूर्ण

/*
 * chcr_ktls_dev_add:  call back क्रम tls_dev_add.
 * Create a tcb entry क्रम TP. Also add l2t entry क्रम the connection. And
 * generate keys & save those keys locally.
 * @netdev - net device.
 * @tls_cts - tls context.
 * @direction - TX/RX crypto direction
 * वापस: SUCCESS/FAILURE.
 */
अटल पूर्णांक chcr_ktls_dev_add(काष्ठा net_device *netdev, काष्ठा sock *sk,
			     क्रमागत tls_offload_ctx_dir direction,
			     काष्ठा tls_crypto_info *crypto_info,
			     u32 start_offload_tcp_sn)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा ch_ktls_port_stats_debug *port_stats;
	काष्ठा chcr_ktls_ofld_ctx_tx *tx_ctx;
	काष्ठा chcr_ktls_uld_ctx *u_ctx;
	काष्ठा chcr_ktls_info *tx_info;
	काष्ठा dst_entry *dst;
	काष्ठा adapter *adap;
	काष्ठा port_info *pi;
	काष्ठा neighbour *n;
	u8 daaddr[16];
	पूर्णांक ret = -1;

	tx_ctx = chcr_get_ktls_tx_context(tls_ctx);

	pi = netdev_priv(netdev);
	adap = pi->adapter;
	port_stats = &adap->ch_ktls_stats.ktls_port[pi->port_id];
	atomic64_inc(&port_stats->ktls_tx_connection_खोलो);
	u_ctx = adap->uld[CXGB4_ULD_KTLS].handle;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_RX) अणु
		pr_err("not expecting for RX direction\n");
		जाओ out;
	पूर्ण

	अगर (tx_ctx->chcr_info)
		जाओ out;

	अगर (u_ctx && u_ctx->detach)
		जाओ out;

	tx_info = kvzalloc(माप(*tx_info), GFP_KERNEL);
	अगर (!tx_info)
		जाओ out;

	tx_info->sk = sk;
	spin_lock_init(&tx_info->lock);
	/* initialize tid and atid to -1, 0 is a also a valid id. */
	tx_info->tid = -1;
	tx_info->atid = -1;

	tx_info->adap = adap;
	tx_info->netdev = netdev;
	tx_info->first_qset = pi->first_qset;
	tx_info->tx_chan = pi->tx_chan;
	tx_info->smt_idx = pi->smt_idx;
	tx_info->port_id = pi->port_id;
	tx_info->prev_ack = 0;
	tx_info->prev_win = 0;

	tx_info->rx_qid = chcr_get_first_rx_qid(adap);
	अगर (unlikely(tx_info->rx_qid < 0))
		जाओ मुक्त_tx_info;

	tx_info->prev_seq = start_offload_tcp_sn;
	tx_info->tcp_start_seq_number = start_offload_tcp_sn;

	/* save crypto keys */
	ret = chcr_ktls_save_keys(tx_info, crypto_info, direction);
	अगर (ret < 0)
		जाओ मुक्त_tx_info;

	/* get peer ip */
	अगर (sk->sk_family == AF_INET) अणु
		स_नकल(daaddr, &sk->sk_daddr, 4);
		tx_info->ip_family = AF_INET;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		अगर (!sk->sk_ipv6only &&
		    ipv6_addr_type(&sk->sk_v6_daddr) == IPV6_ADDR_MAPPED) अणु
			स_नकल(daaddr, &sk->sk_daddr, 4);
			tx_info->ip_family = AF_INET;
		पूर्ण अन्यथा अणु
			स_नकल(daaddr, sk->sk_v6_daddr.in6_u.u6_addr8, 16);
			tx_info->ip_family = AF_INET6;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* get the l2t index */
	dst = sk_dst_get(sk);
	अगर (!dst) अणु
		pr_err("DST entry not found\n");
		जाओ मुक्त_tx_info;
	पूर्ण
	n = dst_neigh_lookup(dst, daaddr);
	अगर (!n || !n->dev) अणु
		pr_err("neighbour not found\n");
		dst_release(dst);
		जाओ मुक्त_tx_info;
	पूर्ण
	tx_info->l2te  = cxgb4_l2t_get(adap->l2t, n, n->dev, 0);

	neigh_release(n);
	dst_release(dst);

	अगर (!tx_info->l2te) अणु
		pr_err("l2t entry not found\n");
		जाओ मुक्त_tx_info;
	पूर्ण

	/* Driver shouldn't be हटाओd until any single connection exists */
	अगर (!try_module_get(THIS_MODULE))
		जाओ मुक्त_l2t;

	init_completion(&tx_info->completion);
	/* create a filter and call cxgb4_l2t_send to send the packet out, which
	 * will take care of updating l2t entry in hw अगर not alपढ़ोy करोne.
	 */
	tx_info->खोलो_state = CH_KTLS_OPEN_PENDING;

	अगर (chcr_setup_connection(sk, tx_info))
		जाओ put_module;

	/* Wait क्रम reply */
	रुको_क्रम_completion_समयout(&tx_info->completion, 30 * HZ);
	spin_lock_bh(&tx_info->lock);
	अगर (tx_info->खोलो_state) अणु
		/* need to रुको क्रम hw response, can't मुक्त tx_info yet. */
		अगर (tx_info->खोलो_state == CH_KTLS_OPEN_PENDING)
			tx_info->pending_बंद = true;
		अन्यथा
			spin_unlock_bh(&tx_info->lock);
		/* अगर in pending बंद, मुक्त the lock after the cleanup */
		जाओ put_module;
	पूर्ण
	spin_unlock_bh(&tx_info->lock);

	/* initialize tcb */
	reinit_completion(&tx_info->completion);
	/* mark it pending क्रम hw response */
	tx_info->खोलो_state = CH_KTLS_OPEN_PENDING;

	अगर (chcr_init_tcb_fields(tx_info))
		जाओ मुक्त_tid;

	/* Wait क्रम reply */
	रुको_क्रम_completion_समयout(&tx_info->completion, 30 * HZ);
	spin_lock_bh(&tx_info->lock);
	अगर (tx_info->खोलो_state) अणु
		/* need to रुको क्रम hw response, can't मुक्त tx_info yet. */
		tx_info->pending_बंद = true;
		/* मुक्त the lock after cleanup */
		जाओ मुक्त_tid;
	पूर्ण
	spin_unlock_bh(&tx_info->lock);

	अगर (!cxgb4_check_l2t_valid(tx_info->l2te))
		जाओ मुक्त_tid;

	atomic64_inc(&port_stats->ktls_tx_ctx);
	tx_ctx->chcr_info = tx_info;

	वापस 0;

मुक्त_tid:
#अगर IS_ENABLED(CONFIG_IPV6)
	/* clear clip entry */
	अगर (tx_info->ip_family == AF_INET6)
		cxgb4_clip_release(netdev, (स्थिर u32 *)
				   &sk->sk_v6_rcv_saddr,
				   1);
#पूर्ण_अगर
	cxgb4_हटाओ_tid(&tx_info->adap->tids, tx_info->tx_chan,
			 tx_info->tid, tx_info->ip_family);

	xa_erase(&u_ctx->tid_list, tx_info->tid);

put_module:
	/* release module refcount */
	module_put(THIS_MODULE);
मुक्त_l2t:
	cxgb4_l2t_release(tx_info->l2te);
मुक्त_tx_info:
	अगर (tx_info->pending_बंद)
		spin_unlock_bh(&tx_info->lock);
	अन्यथा
		kvमुक्त(tx_info);
out:
	atomic64_inc(&port_stats->ktls_tx_connection_fail);
	वापस -1;
पूर्ण

/*
 * chcr_init_tcb_fields:  Initialize tcb fields to handle TCP seq number
 *			  handling.
 * @tx_info - driver specअगरic tls info.
 * वापस: NET_TX_OK/NET_XMIT_DROP
 */
अटल पूर्णांक chcr_init_tcb_fields(काष्ठा chcr_ktls_info *tx_info)
अणु
	पूर्णांक  ret = 0;

	/* set tcb in offload and bypass */
	ret =
	chcr_set_tcb_field(tx_info, TCB_T_FLAGS_W,
			   TCB_T_FLAGS_V(TF_CORE_BYPASS_F | TF_NON_OFFLOAD_F),
			   TCB_T_FLAGS_V(TF_CORE_BYPASS_F), 1);
	अगर (ret)
		वापस ret;
	/* reset snd_una and snd_next fields in tcb */
	ret = chcr_set_tcb_field(tx_info, TCB_SND_UNA_RAW_W,
				 TCB_SND_NXT_RAW_V(TCB_SND_NXT_RAW_M) |
				 TCB_SND_UNA_RAW_V(TCB_SND_UNA_RAW_M),
				 0, 1);
	अगर (ret)
		वापस ret;

	/* reset send max */
	ret = chcr_set_tcb_field(tx_info, TCB_SND_MAX_RAW_W,
				 TCB_SND_MAX_RAW_V(TCB_SND_MAX_RAW_M),
				 0, 1);
	अगर (ret)
		वापस ret;

	/* update l2t index and request क्रम tp reply to confirm tcb is
	 * initialised to handle tx traffic.
	 */
	ret = chcr_set_tcb_field(tx_info, TCB_L2T_IX_W,
				 TCB_L2T_IX_V(TCB_L2T_IX_M),
				 TCB_L2T_IX_V(tx_info->l2te->idx), 0);
	वापस ret;
पूर्ण

/*
 * chcr_ktls_cpl_act_खोलो_rpl: connection reply received from TP.
 */
अटल पूर्णांक chcr_ktls_cpl_act_खोलो_rpl(काष्ठा adapter *adap,
				      अचिन्हित अक्षर *input)
अणु
	स्थिर काष्ठा cpl_act_खोलो_rpl *p = (व्योम *)input;
	काष्ठा chcr_ktls_info *tx_info = शून्य;
	काष्ठा chcr_ktls_ofld_ctx_tx *tx_ctx;
	काष्ठा chcr_ktls_uld_ctx *u_ctx;
	अचिन्हित पूर्णांक atid, tid, status;
	काष्ठा tls_context *tls_ctx;
	काष्ठा tid_info *t;
	पूर्णांक ret = 0;

	tid = GET_TID(p);
	status = AOPEN_STATUS_G(ntohl(p->atid_status));
	atid = TID_TID_G(AOPEN_ATID_G(ntohl(p->atid_status)));

	t = &adap->tids;
	tx_info = lookup_atid(t, atid);

	अगर (!tx_info || tx_info->atid != atid) अणु
		pr_err("%s: incorrect tx_info or atid\n", __func__);
		वापस -1;
	पूर्ण

	cxgb4_मुक्त_atid(t, atid);
	tx_info->atid = -1;

	spin_lock(&tx_info->lock);
	/* HW response is very बंद, finish pending cleanup */
	अगर (tx_info->pending_बंद) अणु
		spin_unlock(&tx_info->lock);
		अगर (!status) अणु
			cxgb4_हटाओ_tid(&tx_info->adap->tids, tx_info->tx_chan,
					 tid, tx_info->ip_family);
		पूर्ण
		kvमुक्त(tx_info);
		वापस 0;
	पूर्ण

	अगर (!status) अणु
		tx_info->tid = tid;
		cxgb4_insert_tid(t, tx_info, tx_info->tid, tx_info->ip_family);
		/* Adding tid */
		tls_ctx = tls_get_ctx(tx_info->sk);
		tx_ctx = chcr_get_ktls_tx_context(tls_ctx);
		u_ctx = adap->uld[CXGB4_ULD_KTLS].handle;
		अगर (u_ctx) अणु
			ret = xa_insert_bh(&u_ctx->tid_list, tid, tx_ctx,
					   GFP_NOWAIT);
			अगर (ret < 0) अणु
				pr_err("%s: Failed to allocate tid XA entry = %d\n",
				       __func__, tx_info->tid);
				tx_info->खोलो_state = CH_KTLS_OPEN_FAILURE;
				जाओ out;
			पूर्ण
		पूर्ण
		tx_info->खोलो_state = CH_KTLS_OPEN_SUCCESS;
	पूर्ण अन्यथा अणु
		tx_info->खोलो_state = CH_KTLS_OPEN_FAILURE;
	पूर्ण
out:
	spin_unlock(&tx_info->lock);

	complete(&tx_info->completion);
	वापस ret;
पूर्ण

/*
 * chcr_ktls_cpl_set_tcb_rpl: TCB reply received from TP.
 */
अटल पूर्णांक chcr_ktls_cpl_set_tcb_rpl(काष्ठा adapter *adap, अचिन्हित अक्षर *input)
अणु
	स्थिर काष्ठा cpl_set_tcb_rpl *p = (व्योम *)input;
	काष्ठा chcr_ktls_info *tx_info = शून्य;
	काष्ठा tid_info *t;
	u32 tid;

	tid = GET_TID(p);

	t = &adap->tids;
	tx_info = lookup_tid(t, tid);

	अगर (!tx_info || tx_info->tid != tid) अणु
		pr_err("%s: incorrect tx_info or tid\n", __func__);
		वापस -1;
	पूर्ण

	spin_lock(&tx_info->lock);
	अगर (tx_info->pending_बंद) अणु
		spin_unlock(&tx_info->lock);
		kvमुक्त(tx_info);
		वापस 0;
	पूर्ण
	tx_info->खोलो_state = CH_KTLS_OPEN_SUCCESS;
	spin_unlock(&tx_info->lock);

	complete(&tx_info->completion);
	वापस 0;
पूर्ण

अटल व्योम *__chcr_ग_लिखो_cpl_set_tcb_ulp(काष्ठा chcr_ktls_info *tx_info,
					u32 tid, व्योम *pos, u16 word,
					काष्ठा sge_eth_txq *q, u64 mask,
					u64 val, u32 reply)
अणु
	काष्ठा cpl_set_tcb_field_core *cpl;
	काष्ठा ulptx_idata *idata;
	काष्ठा ulp_txpkt *txpkt;

	/* ULP_TXPKT */
	txpkt = pos;
	txpkt->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) |
				ULP_TXPKT_CHANNELID_V(tx_info->port_id) |
				ULP_TXPKT_FID_V(q->q.cntxt_id) |
				ULP_TXPKT_RO_F);
	txpkt->len = htonl(DIV_ROUND_UP(CHCR_SET_TCB_FIELD_LEN, 16));

	/* ULPTX_IDATA sub-command */
	idata = (काष्ठा ulptx_idata *)(txpkt + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	idata->len = htonl(माप(*cpl));
	pos = idata + 1;

	cpl = pos;
	/* CPL_SET_TCB_FIELD */
	OPCODE_TID(cpl) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, tid));
	cpl->reply_ctrl = htons(QUEUENO_V(tx_info->rx_qid) |
			NO_REPLY_V(!reply));
	cpl->word_cookie = htons(TCB_WORD_V(word));
	cpl->mask = cpu_to_be64(mask);
	cpl->val = cpu_to_be64(val);

	/* ULPTX_NOOP */
	idata = (काष्ठा ulptx_idata *)(cpl + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_NOOP));
	idata->len = htonl(0);
	pos = idata + 1;

	वापस pos;
पूर्ण


/*
 * chcr_ग_लिखो_cpl_set_tcb_ulp: update tcb values.
 * TCB is responsible to create tcp headers, so all the related values
 * should be correctly updated.
 * @tx_info - driver specअगरic tls info.
 * @q - tx queue on which packet is going out.
 * @tid - TCB identअगरier.
 * @pos - current index where should we start writing.
 * @word - TCB word.
 * @mask - TCB word related mask.
 * @val - TCB word related value.
 * @reply - set 1 अगर looking क्रम TP response.
 * वापस - next position to ग_लिखो.
 */
अटल व्योम *chcr_ग_लिखो_cpl_set_tcb_ulp(काष्ठा chcr_ktls_info *tx_info,
					काष्ठा sge_eth_txq *q, u32 tid,
					व्योम *pos, u16 word, u64 mask,
					u64 val, u32 reply)
अणु
	पूर्णांक left = (व्योम *)q->q.stat - pos;

	अगर (unlikely(left < CHCR_SET_TCB_FIELD_LEN)) अणु
		अगर (!left) अणु
			pos = q->q.desc;
		पूर्ण अन्यथा अणु
			u8 buf[48] = अणु0पूर्ण;

			__chcr_ग_लिखो_cpl_set_tcb_ulp(tx_info, tid, buf, word, q,
						     mask, val, reply);

			वापस chcr_copy_to_txd(buf, &q->q, pos,
						CHCR_SET_TCB_FIELD_LEN);
		पूर्ण
	पूर्ण

	pos = __chcr_ग_लिखो_cpl_set_tcb_ulp(tx_info, tid, pos, word, q,
					   mask, val, reply);

	/* check again अगर we are at the end of the queue */
	अगर (left == CHCR_SET_TCB_FIELD_LEN)
		pos = q->q.desc;

	वापस pos;
पूर्ण

/*
 * chcr_ktls_xmit_tcb_cpls: update tcb entry so that TP will create the header
 * with updated values like tcp seq, ack, winकरोw etc.
 * @tx_info - driver specअगरic tls info.
 * @q - TX queue.
 * @tcp_seq
 * @tcp_ack
 * @tcp_win
 * वापस: NETDEV_TX_BUSY/NET_TX_OK.
 */
अटल पूर्णांक chcr_ktls_xmit_tcb_cpls(काष्ठा chcr_ktls_info *tx_info,
				   काष्ठा sge_eth_txq *q, u64 tcp_seq,
				   u64 tcp_ack, u64 tcp_win, bool offset)
अणु
	bool first_wr = ((tx_info->prev_ack == 0) && (tx_info->prev_win == 0));
	काष्ठा ch_ktls_port_stats_debug *port_stats;
	u32 len, cpl = 0, ndesc, wr_len, wr_mid = 0;
	काष्ठा fw_ulptx_wr *wr;
	पूर्णांक credits;
	व्योम *pos;

	wr_len = माप(*wr);
	/* there can be max 4 cpls, check अगर we have enough credits */
	len = wr_len + 4 * roundup(CHCR_SET_TCB_FIELD_LEN, 16);
	ndesc = DIV_ROUND_UP(len, 64);

	credits = chcr_txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		chcr_eth_txq_stop(q);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		chcr_eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	pos = &q->q.desc[q->q.pidx];
	/* make space क्रम WR, we'll fill it later when we know all the cpls
	 * being sent out and have complete length.
	 */
	wr = pos;
	pos += wr_len;
	/* update tx_max अगर its a re-transmit or the first wr */
	अगर (first_wr || tcp_seq != tx_info->prev_seq) अणु
		pos = chcr_ग_लिखो_cpl_set_tcb_ulp(tx_info, q, tx_info->tid, pos,
						 TCB_TX_MAX_W,
						 TCB_TX_MAX_V(TCB_TX_MAX_M),
						 TCB_TX_MAX_V(tcp_seq), 0);
		cpl++;
	पूर्ण
	/* reset snd una अगर it's a re-transmit pkt */
	अगर (tcp_seq != tx_info->prev_seq || offset) अणु
		/* reset snd_una */
		port_stats =
			&tx_info->adap->ch_ktls_stats.ktls_port[tx_info->port_id];
		pos = chcr_ग_लिखो_cpl_set_tcb_ulp(tx_info, q, tx_info->tid, pos,
						 TCB_SND_UNA_RAW_W,
						 TCB_SND_UNA_RAW_V
						 (TCB_SND_UNA_RAW_M),
						 TCB_SND_UNA_RAW_V(0), 0);
		अगर (tcp_seq != tx_info->prev_seq)
			atomic64_inc(&port_stats->ktls_tx_ooo);
		cpl++;
	पूर्ण
	/* update ack */
	अगर (first_wr || tx_info->prev_ack != tcp_ack) अणु
		pos = chcr_ग_लिखो_cpl_set_tcb_ulp(tx_info, q, tx_info->tid, pos,
						 TCB_RCV_NXT_W,
						 TCB_RCV_NXT_V(TCB_RCV_NXT_M),
						 TCB_RCV_NXT_V(tcp_ack), 0);
		tx_info->prev_ack = tcp_ack;
		cpl++;
	पूर्ण
	/* update receive winकरोw */
	अगर (first_wr || tx_info->prev_win != tcp_win) अणु
		chcr_ग_लिखो_cpl_set_tcb_ulp(tx_info, q, tx_info->tid, pos,
					   TCB_RCV_WND_W,
					   TCB_RCV_WND_V(TCB_RCV_WND_M),
					   TCB_RCV_WND_V(tcp_win), 0);
		tx_info->prev_win = tcp_win;
		cpl++;
	पूर्ण

	अगर (cpl) अणु
		/* get the actual length */
		len = wr_len + cpl * roundup(CHCR_SET_TCB_FIELD_LEN, 16);
		/* ULPTX wr */
		wr->op_to_compl = htonl(FW_WR_OP_V(FW_ULPTX_WR));
		wr->cookie = 0;
		/* fill len in wr field */
		wr->flowid_len16 = htonl(wr_mid |
					 FW_WR_LEN16_V(DIV_ROUND_UP(len, 16)));

		ndesc = DIV_ROUND_UP(len, 64);
		chcr_txq_advance(&q->q, ndesc);
		cxgb4_ring_tx_db(tx_info->adap, &q->q, ndesc);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * chcr_ktls_get_tx_flits
 * वापसs number of flits to be sent out, it includes key context length, WR
 * size and skb fragments.
 */
अटल अचिन्हित पूर्णांक
chcr_ktls_get_tx_flits(u32 nr_frags, अचिन्हित पूर्णांक key_ctx_len)
अणु
	वापस chcr_sgl_len(nr_frags) +
	       DIV_ROUND_UP(key_ctx_len + CHCR_KTLS_WR_SIZE, 8);
पूर्ण

/*
 * chcr_ktls_check_tcp_options: To check अगर there is any TCP option available
 * other than बारtamp.
 * @skb - skb contains partial record..
 * वापस: 1 / 0
 */
अटल पूर्णांक
chcr_ktls_check_tcp_options(काष्ठा tcphdr *tcp)
अणु
	पूर्णांक cnt, opt, optlen;
	u_अक्षर *cp;

	cp = (u_अक्षर *)(tcp + 1);
	cnt = (tcp->करोff << 2) - माप(काष्ठा tcphdr);
	क्रम (; cnt > 0; cnt -= optlen, cp += optlen) अणु
		opt = cp[0];
		अगर (opt == TCPOPT_EOL)
			अवरोध;
		अगर (opt == TCPOPT_NOP) अणु
			optlen = 1;
		पूर्ण अन्यथा अणु
			अगर (cnt < 2)
				अवरोध;
			optlen = cp[1];
			अगर (optlen < 2 || optlen > cnt)
				अवरोध;
		पूर्ण
		चयन (opt) अणु
		हाल TCPOPT_NOP:
			अवरोध;
		शेष:
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * chcr_ktls_ग_लिखो_tcp_options : TP can't send out all the options, we need to
 * send out separately.
 * @tx_info - driver specअगरic tls info.
 * @skb - skb contains partial record..
 * @q - TX queue.
 * @tx_chan - channel number.
 * वापस: NETDEV_TX_OK/NETDEV_TX_BUSY.
 */
अटल पूर्णांक
chcr_ktls_ग_लिखो_tcp_options(काष्ठा chcr_ktls_info *tx_info, काष्ठा sk_buff *skb,
			    काष्ठा sge_eth_txq *q, uपूर्णांक32_t tx_chan)
अणु
	काष्ठा fw_eth_tx_pkt_wr *wr;
	काष्ठा cpl_tx_pkt_core *cpl;
	u32 ctrl, iplen, maclen;
	काष्ठा ipv6hdr *ip6;
	अचिन्हित पूर्णांक ndesc;
	काष्ठा tcphdr *tcp;
	पूर्णांक len16, pktlen;
	काष्ठा iphdr *ip;
	u32 wr_mid = 0;
	पूर्णांक credits;
	u8 buf[150];
	u64 cntrl1;
	व्योम *pos;

	iplen = skb_network_header_len(skb);
	maclen = skb_mac_header_len(skb);

	/* packet length = eth hdr len + ip hdr len + tcp hdr len
	 * (including options).
	 */
	pktlen = skb_transport_offset(skb) + tcp_hdrlen(skb);

	ctrl = माप(*cpl) + pktlen;
	len16 = DIV_ROUND_UP(माप(*wr) + ctrl, 16);
	/* check how many descriptors needed */
	ndesc = DIV_ROUND_UP(len16, 4);

	credits = chcr_txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		chcr_eth_txq_stop(q);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		chcr_eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	pos = &q->q.desc[q->q.pidx];
	wr = pos;

	/* Firmware work request header */
	wr->op_immdlen = htonl(FW_WR_OP_V(FW_ETH_TX_PKT_WR) |
			       FW_WR_IMMDLEN_V(ctrl));

	wr->equiq_to_len16 = htonl(wr_mid | FW_WR_LEN16_V(len16));
	wr->r3 = 0;

	cpl = (व्योम *)(wr + 1);

	/* CPL header */
	cpl->ctrl0 = htonl(TXPKT_OPCODE_V(CPL_TX_PKT) | TXPKT_INTF_V(tx_chan) |
			   TXPKT_PF_V(tx_info->adap->pf));
	cpl->pack = 0;
	cpl->len = htons(pktlen);

	स_नकल(buf, skb->data, pktlen);
	अगर (!IS_ENABLED(CONFIG_IPV6) || tx_info->ip_family == AF_INET) अणु
		/* we need to correct ip header len */
		ip = (काष्ठा iphdr *)(buf + maclen);
		ip->tot_len = htons(pktlen - maclen);
		cntrl1 = TXPKT_CSUM_TYPE_V(TX_CSUM_TCPIP);
	पूर्ण अन्यथा अणु
		ip6 = (काष्ठा ipv6hdr *)(buf + maclen);
		ip6->payload_len = htons(pktlen - maclen - iplen);
		cntrl1 = TXPKT_CSUM_TYPE_V(TX_CSUM_TCPIP6);
	पूर्ण

	cntrl1 |= T6_TXPKT_ETHHDR_LEN_V(maclen - ETH_HLEN) |
		  TXPKT_IPHDR_LEN_V(iplen);
	/* checksum offload */
	cpl->ctrl1 = cpu_to_be64(cntrl1);

	pos = cpl + 1;

	/* now take care of the tcp header, अगर fin is not set then clear push
	 * bit as well, and अगर fin is set, it will be sent at the last so we
	 * need to update the tcp sequence number as per the last packet.
	 */
	tcp = (काष्ठा tcphdr *)(buf + maclen + iplen);

	अगर (!tcp->fin)
		tcp->psh = 0;
	अन्यथा
		tcp->seq = htonl(tx_info->prev_seq);

	chcr_copy_to_txd(buf, &q->q, pos, pktlen);

	chcr_txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(tx_info->adap, &q->q, ndesc);
	वापस 0;
पूर्ण

/*
 * chcr_ktls_xmit_wr_complete: This sends out the complete record. If an skb
 * received has partial end part of the record, send out the complete record, so
 * that crypto block will be able to generate TAG/HASH.
 * @skb - segment which has complete or partial end part.
 * @tx_info - driver specअगरic tls info.
 * @q - TX queue.
 * @tcp_seq
 * @tcp_push - tcp push bit.
 * @mss - segment size.
 * वापस: NETDEV_TX_BUSY/NET_TX_OK.
 */
अटल पूर्णांक chcr_ktls_xmit_wr_complete(काष्ठा sk_buff *skb,
				      काष्ठा chcr_ktls_info *tx_info,
				      काष्ठा sge_eth_txq *q, u32 tcp_seq,
				      bool is_last_wr, u32 data_len,
				      u32 skb_offset, u32 nfrags,
				      bool tcp_push, u32 mss)
अणु
	u32 len16, wr_mid = 0, flits = 0, ndesc, cipher_start;
	काष्ठा adapter *adap = tx_info->adap;
	पूर्णांक credits, left, last_desc;
	काष्ठा tx_sw_desc *sgl_sdesc;
	काष्ठा cpl_tx_data *tx_data;
	काष्ठा cpl_tx_sec_pdu *cpl;
	काष्ठा ulptx_idata *idata;
	काष्ठा ulp_txpkt *ulptx;
	काष्ठा fw_ulptx_wr *wr;
	व्योम *pos;
	u64 *end;

	/* get the number of flits required */
	flits = chcr_ktls_get_tx_flits(nfrags, tx_info->key_ctx_len);
	/* number of descriptors */
	ndesc = chcr_flits_to_desc(flits);
	/* check अगर enough credits available */
	credits = chcr_txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		chcr_eth_txq_stop(q);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		/* Credits are below the threshold values, stop the queue after
		 * injecting the Work Request क्रम this packet.
		 */
		chcr_eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	last_desc = q->q.pidx + ndesc - 1;
	अगर (last_desc >= q->q.size)
		last_desc -= q->q.size;
	sgl_sdesc = &q->q.sdesc[last_desc];

	अगर (unlikely(cxgb4_map_skb(adap->pdev_dev, skb, sgl_sdesc->addr) < 0)) अणु
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		q->mapping_err++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (!is_last_wr)
		skb_get(skb);

	pos = &q->q.desc[q->q.pidx];
	end = (u64 *)pos + flits;
	/* FW_ULPTX_WR */
	wr = pos;
	/* WR will need len16 */
	len16 = DIV_ROUND_UP(flits, 2);
	wr->op_to_compl = htonl(FW_WR_OP_V(FW_ULPTX_WR));
	wr->flowid_len16 = htonl(wr_mid | FW_WR_LEN16_V(len16));
	wr->cookie = 0;
	pos += माप(*wr);
	/* ULP_TXPKT */
	ulptx = pos;
	ulptx->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) |
				ULP_TXPKT_CHANNELID_V(tx_info->port_id) |
				ULP_TXPKT_FID_V(q->q.cntxt_id) |
				ULP_TXPKT_RO_F);
	ulptx->len = htonl(len16 - 1);
	/* ULPTX_IDATA sub-command */
	idata = (काष्ठा ulptx_idata *)(ulptx + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM) | ULP_TX_SC_MORE_F);
	/* idata length will include cpl_tx_sec_pdu + key context size +
	 * cpl_tx_data header.
	 */
	idata->len = htonl(माप(*cpl) + tx_info->key_ctx_len +
			   माप(*tx_data));
	/* SEC CPL */
	cpl = (काष्ठा cpl_tx_sec_pdu *)(idata + 1);
	cpl->op_ivinsrtofst =
		htonl(CPL_TX_SEC_PDU_OPCODE_V(CPL_TX_SEC_PDU) |
		      CPL_TX_SEC_PDU_CPLLEN_V(CHCR_CPL_TX_SEC_PDU_LEN_64BIT) |
		      CPL_TX_SEC_PDU_PLACEHOLDER_V(1) |
		      CPL_TX_SEC_PDU_IVINSRTOFST_V(TLS_HEADER_SIZE + 1));
	cpl->pldlen = htonl(data_len);

	/* encryption should start after tls header size + iv size */
	cipher_start = TLS_HEADER_SIZE + tx_info->iv_size + 1;

	cpl->aadstart_cipherstop_hi =
		htonl(CPL_TX_SEC_PDU_AADSTART_V(1) |
		      CPL_TX_SEC_PDU_AADSTOP_V(TLS_HEADER_SIZE) |
		      CPL_TX_SEC_PDU_CIPHERSTART_V(cipher_start));

	/* authentication will also start after tls header + iv size */
	cpl->cipherstop_lo_authinsert =
	htonl(CPL_TX_SEC_PDU_AUTHSTART_V(cipher_start) |
	      CPL_TX_SEC_PDU_AUTHSTOP_V(TLS_CIPHER_AES_GCM_128_TAG_SIZE) |
	      CPL_TX_SEC_PDU_AUTHINSERT_V(TLS_CIPHER_AES_GCM_128_TAG_SIZE));

	/* These two flits are actually a CPL_TLS_TX_SCMD_FMT. */
	cpl->seqno_numivs = htonl(tx_info->scmd0_seqno_numivs);
	cpl->ivgen_hdrlen = htonl(tx_info->scmd0_ivgen_hdrlen);
	cpl->scmd1 = cpu_to_be64(tx_info->record_no);

	pos = cpl + 1;
	/* check अगर space left to fill the keys */
	left = (व्योम *)q->q.stat - pos;
	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण

	pos = chcr_copy_to_txd(&tx_info->key_ctx, &q->q, pos,
			       tx_info->key_ctx_len);
	left = (व्योम *)q->q.stat - pos;

	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण
	/* CPL_TX_DATA */
	tx_data = (व्योम *)pos;
	OPCODE_TID(tx_data) = htonl(MK_OPCODE_TID(CPL_TX_DATA, tx_info->tid));
	tx_data->len = htonl(TX_DATA_MSS_V(mss) | TX_LENGTH_V(data_len));

	tx_data->rsvd = htonl(tcp_seq);

	tx_data->flags = htonl(TX_BYPASS_F);
	अगर (tcp_push)
		tx_data->flags |= htonl(TX_PUSH_F | TX_SHOVE_F);

	/* check left again, it might go beyond queue limit */
	pos = tx_data + 1;
	left = (व्योम *)q->q.stat - pos;

	/* check the position again */
	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण

	/* send the complete packet except the header */
	cxgb4_ग_लिखो_partial_sgl(skb, &q->q, pos, end, sgl_sdesc->addr,
				skb_offset, data_len);
	sgl_sdesc->skb = skb;

	chcr_txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(adap, &q->q, ndesc);
	atomic64_inc(&adap->ch_ktls_stats.ktls_tx_send_records);

	वापस 0;
पूर्ण

/*
 * chcr_ktls_xmit_wr_लघु: This is to send out partial records. If its
 * a middle part of a record, fetch the prior data to make it 16 byte aligned
 * and then only send it out.
 *
 * @skb - skb contains partial record..
 * @tx_info - driver specअगरic tls info.
 * @q - TX queue.
 * @tcp_seq
 * @tcp_push - tcp push bit.
 * @mss - segment size.
 * @tls_rec_offset - offset from start of the tls record.
 * @perior_data - data beक्रमe the current segment, required to make this record
 *		  16 byte aligned.
 * @prior_data_len - prior_data length (less than 16)
 * वापस: NETDEV_TX_BUSY/NET_TX_OK.
 */
अटल पूर्णांक chcr_ktls_xmit_wr_लघु(काष्ठा sk_buff *skb,
				   काष्ठा chcr_ktls_info *tx_info,
				   काष्ठा sge_eth_txq *q,
				   u32 tcp_seq, bool tcp_push, u32 mss,
				   u32 tls_rec_offset, u8 *prior_data,
				   u32 prior_data_len, u32 data_len,
				   u32 skb_offset)
अणु
	u32 len16, wr_mid = 0, cipher_start, nfrags;
	काष्ठा adapter *adap = tx_info->adap;
	अचिन्हित पूर्णांक flits = 0, ndesc;
	पूर्णांक credits, left, last_desc;
	काष्ठा tx_sw_desc *sgl_sdesc;
	काष्ठा cpl_tx_data *tx_data;
	काष्ठा cpl_tx_sec_pdu *cpl;
	काष्ठा ulptx_idata *idata;
	काष्ठा ulp_txpkt *ulptx;
	काष्ठा fw_ulptx_wr *wr;
	__be64 iv_record;
	व्योम *pos;
	u64 *end;

	nfrags = chcr_get_nfrags_to_send(skb, skb_offset, data_len);
	/* get the number of flits required, it's a partial record so 2 flits
	 * (AES_BLOCK_SIZE) will be added.
	 */
	flits = chcr_ktls_get_tx_flits(nfrags, tx_info->key_ctx_len) + 2;
	/* get the correct 8 byte IV of this record */
	iv_record = cpu_to_be64(tx_info->iv + tx_info->record_no);
	/* If it's a middle record and not 16 byte aligned to run AES CTR, need
	 * to make it 16 byte aligned. So atleadt 2 extra flits of immediate
	 * data will be added.
	 */
	अगर (prior_data_len)
		flits += 2;
	/* number of descriptors */
	ndesc = chcr_flits_to_desc(flits);
	/* check अगर enough credits available */
	credits = chcr_txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		chcr_eth_txq_stop(q);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		chcr_eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	last_desc = q->q.pidx + ndesc - 1;
	अगर (last_desc >= q->q.size)
		last_desc -= q->q.size;
	sgl_sdesc = &q->q.sdesc[last_desc];

	अगर (unlikely(cxgb4_map_skb(adap->pdev_dev, skb, sgl_sdesc->addr) < 0)) अणु
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		q->mapping_err++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	pos = &q->q.desc[q->q.pidx];
	end = (u64 *)pos + flits;
	/* FW_ULPTX_WR */
	wr = pos;
	/* WR will need len16 */
	len16 = DIV_ROUND_UP(flits, 2);
	wr->op_to_compl = htonl(FW_WR_OP_V(FW_ULPTX_WR));
	wr->flowid_len16 = htonl(wr_mid | FW_WR_LEN16_V(len16));
	wr->cookie = 0;
	pos += माप(*wr);
	/* ULP_TXPKT */
	ulptx = pos;
	ulptx->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) |
				ULP_TXPKT_CHANNELID_V(tx_info->port_id) |
				ULP_TXPKT_FID_V(q->q.cntxt_id) |
				ULP_TXPKT_RO_F);
	ulptx->len = htonl(len16 - 1);
	/* ULPTX_IDATA sub-command */
	idata = (काष्ठा ulptx_idata *)(ulptx + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM) | ULP_TX_SC_MORE_F);
	/* idata length will include cpl_tx_sec_pdu + key context size +
	 * cpl_tx_data header.
	 */
	idata->len = htonl(माप(*cpl) + tx_info->key_ctx_len +
			   माप(*tx_data) + AES_BLOCK_LEN + prior_data_len);
	/* SEC CPL */
	cpl = (काष्ठा cpl_tx_sec_pdu *)(idata + 1);
	/* cipher start will have tls header + iv size extra अगर its a header
	 * part of tls record. अन्यथा only 16 byte IV will be added.
	 */
	cipher_start =
		AES_BLOCK_LEN + 1 +
		(!tls_rec_offset ? TLS_HEADER_SIZE + tx_info->iv_size : 0);

	cpl->op_ivinsrtofst =
		htonl(CPL_TX_SEC_PDU_OPCODE_V(CPL_TX_SEC_PDU) |
		      CPL_TX_SEC_PDU_CPLLEN_V(CHCR_CPL_TX_SEC_PDU_LEN_64BIT) |
		      CPL_TX_SEC_PDU_IVINSRTOFST_V(1));
	cpl->pldlen = htonl(data_len + AES_BLOCK_LEN + prior_data_len);
	cpl->aadstart_cipherstop_hi =
		htonl(CPL_TX_SEC_PDU_CIPHERSTART_V(cipher_start));
	cpl->cipherstop_lo_authinsert = 0;
	/* These two flits are actually a CPL_TLS_TX_SCMD_FMT. */
	cpl->seqno_numivs = htonl(tx_info->scmd0_लघु_seqno_numivs);
	cpl->ivgen_hdrlen = htonl(tx_info->scmd0_लघु_ivgen_hdrlen);
	cpl->scmd1 = 0;

	pos = cpl + 1;
	/* check अगर space left to fill the keys */
	left = (व्योम *)q->q.stat - pos;
	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण

	pos = chcr_copy_to_txd(&tx_info->key_ctx, &q->q, pos,
			       tx_info->key_ctx_len);
	left = (व्योम *)q->q.stat - pos;

	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण
	/* CPL_TX_DATA */
	tx_data = (व्योम *)pos;
	OPCODE_TID(tx_data) = htonl(MK_OPCODE_TID(CPL_TX_DATA, tx_info->tid));
	tx_data->len = htonl(TX_DATA_MSS_V(mss) |
			     TX_LENGTH_V(data_len + prior_data_len));
	tx_data->rsvd = htonl(tcp_seq);
	tx_data->flags = htonl(TX_BYPASS_F);
	अगर (tcp_push)
		tx_data->flags |= htonl(TX_PUSH_F | TX_SHOVE_F);

	/* check left again, it might go beyond queue limit */
	pos = tx_data + 1;
	left = (व्योम *)q->q.stat - pos;

	/* check the position again */
	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण
	/* copy the 16 byte IV क्रम AES-CTR, which includes 4 bytes of salt, 8
	 * bytes of actual IV and 4 bytes of 16 byte-sequence.
	 */
	स_नकल(pos, tx_info->key_ctx.salt, tx_info->salt_size);
	स_नकल(pos + tx_info->salt_size, &iv_record, tx_info->iv_size);
	*(__be32 *)(pos + tx_info->salt_size + tx_info->iv_size) =
		htonl(2 + (tls_rec_offset ? ((tls_rec_offset -
		(TLS_HEADER_SIZE + tx_info->iv_size)) / AES_BLOCK_LEN) : 0));

	pos += 16;
	/* Prior_data_len will always be less than 16 bytes, fill the
	 * prio_data_len after AES_CTRL_BLOCK and clear the reमुख्यing length
	 * to 0.
	 */
	अगर (prior_data_len)
		pos = chcr_copy_to_txd(prior_data, &q->q, pos, 16);
	/* send the complete packet except the header */
	cxgb4_ग_लिखो_partial_sgl(skb, &q->q, pos, end, sgl_sdesc->addr,
				skb_offset, data_len);
	sgl_sdesc->skb = skb;

	chcr_txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(adap, &q->q, ndesc);

	वापस 0;
पूर्ण

/*
 * chcr_ktls_tx_plaपूर्णांकxt: This handler will take care of the records which has
 * only plain text (only tls header and iv)
 * @tx_info - driver specअगरic tls info.
 * @skb - skb contains partial record..
 * @tcp_seq
 * @mss - segment size.
 * @tcp_push - tcp push bit.
 * @q - TX queue.
 * @port_id : port number
 * @perior_data - data beक्रमe the current segment, required to make this record
 *		 16 byte aligned.
 * @prior_data_len - prior_data length (less than 16)
 * वापस: NETDEV_TX_BUSY/NET_TX_OK.
 */
अटल पूर्णांक chcr_ktls_tx_plaपूर्णांकxt(काष्ठा chcr_ktls_info *tx_info,
				 काष्ठा sk_buff *skb, u32 tcp_seq, u32 mss,
				 bool tcp_push, काष्ठा sge_eth_txq *q,
				 u32 port_id, u8 *prior_data,
				 u32 data_len, u32 skb_offset,
				 u32 prior_data_len)
अणु
	पूर्णांक credits, left, len16, last_desc;
	अचिन्हित पूर्णांक flits = 0, ndesc;
	काष्ठा tx_sw_desc *sgl_sdesc;
	काष्ठा cpl_tx_data *tx_data;
	काष्ठा ulptx_idata *idata;
	काष्ठा ulp_txpkt *ulptx;
	काष्ठा fw_ulptx_wr *wr;
	u32 wr_mid = 0, nfrags;
	व्योम *pos;
	u64 *end;

	flits = DIV_ROUND_UP(CHCR_PLAIN_TX_DATA_LEN, 8);
	nfrags = chcr_get_nfrags_to_send(skb, skb_offset, data_len);
	flits += chcr_sgl_len(nfrags);
	अगर (prior_data_len)
		flits += 2;

	/* WR will need len16 */
	len16 = DIV_ROUND_UP(flits, 2);
	/* check how many descriptors needed */
	ndesc = DIV_ROUND_UP(flits, 8);

	credits = chcr_txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		chcr_eth_txq_stop(q);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		chcr_eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	last_desc = q->q.pidx + ndesc - 1;
	अगर (last_desc >= q->q.size)
		last_desc -= q->q.size;
	sgl_sdesc = &q->q.sdesc[last_desc];

	अगर (unlikely(cxgb4_map_skb(tx_info->adap->pdev_dev, skb,
				   sgl_sdesc->addr) < 0)) अणु
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		q->mapping_err++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	pos = &q->q.desc[q->q.pidx];
	end = (u64 *)pos + flits;
	/* FW_ULPTX_WR */
	wr = pos;
	wr->op_to_compl = htonl(FW_WR_OP_V(FW_ULPTX_WR));
	wr->flowid_len16 = htonl(wr_mid | FW_WR_LEN16_V(len16));
	wr->cookie = 0;
	/* ULP_TXPKT */
	ulptx = (काष्ठा ulp_txpkt *)(wr + 1);
	ulptx->cmd_dest = htonl(ULPTX_CMD_V(ULP_TX_PKT) |
			ULP_TXPKT_DATAMODIFY_V(0) |
			ULP_TXPKT_CHANNELID_V(tx_info->port_id) |
			ULP_TXPKT_DEST_V(0) |
			ULP_TXPKT_FID_V(q->q.cntxt_id) | ULP_TXPKT_RO_V(1));
	ulptx->len = htonl(len16 - 1);
	/* ULPTX_IDATA sub-command */
	idata = (काष्ठा ulptx_idata *)(ulptx + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM) | ULP_TX_SC_MORE_F);
	idata->len = htonl(माप(*tx_data) + prior_data_len);
	/* CPL_TX_DATA */
	tx_data = (काष्ठा cpl_tx_data *)(idata + 1);
	OPCODE_TID(tx_data) = htonl(MK_OPCODE_TID(CPL_TX_DATA, tx_info->tid));
	tx_data->len = htonl(TX_DATA_MSS_V(mss) |
			     TX_LENGTH_V(data_len + prior_data_len));
	/* set tcp seq number */
	tx_data->rsvd = htonl(tcp_seq);
	tx_data->flags = htonl(TX_BYPASS_F);
	अगर (tcp_push)
		tx_data->flags |= htonl(TX_PUSH_F | TX_SHOVE_F);

	pos = tx_data + 1;
	/* apart from prior_data_len, we should set reमुख्यing part of 16 bytes
	 * to be zero.
	 */
	अगर (prior_data_len)
		pos = chcr_copy_to_txd(prior_data, &q->q, pos, 16);

	/* check left again, it might go beyond queue limit */
	left = (व्योम *)q->q.stat - pos;

	/* check the position again */
	अगर (!left) अणु
		left = (व्योम *)end - (व्योम *)q->q.stat;
		pos = q->q.desc;
		end = pos + left;
	पूर्ण
	/* send the complete packet including the header */
	cxgb4_ग_लिखो_partial_sgl(skb, &q->q, pos, end, sgl_sdesc->addr,
				skb_offset, data_len);
	sgl_sdesc->skb = skb;

	chcr_txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(tx_info->adap, &q->q, ndesc);
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_ktls_tunnel_pkt(काष्ठा chcr_ktls_info *tx_info,
				काष्ठा sk_buff *skb,
				काष्ठा sge_eth_txq *q)
अणु
	u32 ctrl, iplen, maclen, wr_mid = 0, len16;
	काष्ठा tx_sw_desc *sgl_sdesc;
	काष्ठा fw_eth_tx_pkt_wr *wr;
	काष्ठा cpl_tx_pkt_core *cpl;
	अचिन्हित पूर्णांक flits, ndesc;
	पूर्णांक credits, last_desc;
	u64 cntrl1, *end;
	व्योम *pos;

	ctrl = माप(*cpl);
	flits = DIV_ROUND_UP(माप(*wr) + ctrl, 8);

	flits += chcr_sgl_len(skb_shinfo(skb)->nr_frags + 1);
	len16 = DIV_ROUND_UP(flits, 2);
	/* check how many descriptors needed */
	ndesc = DIV_ROUND_UP(flits, 8);

	credits = chcr_txq_avail(&q->q) - ndesc;
	अगर (unlikely(credits < 0)) अणु
		chcr_eth_txq_stop(q);
		वापस -ENOMEM;
	पूर्ण

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		chcr_eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण

	last_desc = q->q.pidx + ndesc - 1;
	अगर (last_desc >= q->q.size)
		last_desc -= q->q.size;
	sgl_sdesc = &q->q.sdesc[last_desc];

	अगर (unlikely(cxgb4_map_skb(tx_info->adap->pdev_dev, skb,
				   sgl_sdesc->addr) < 0)) अणु
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		q->mapping_err++;
		वापस -ENOMEM;
	पूर्ण

	iplen = skb_network_header_len(skb);
	maclen = skb_mac_header_len(skb);

	pos = &q->q.desc[q->q.pidx];
	end = (u64 *)pos + flits;
	wr = pos;

	/* Firmware work request header */
	wr->op_immdlen = htonl(FW_WR_OP_V(FW_ETH_TX_PKT_WR) |
			       FW_WR_IMMDLEN_V(ctrl));

	wr->equiq_to_len16 = htonl(wr_mid | FW_WR_LEN16_V(len16));
	wr->r3 = 0;

	cpl = (व्योम *)(wr + 1);

	/* CPL header */
	cpl->ctrl0 = htonl(TXPKT_OPCODE_V(CPL_TX_PKT) |
			   TXPKT_INTF_V(tx_info->tx_chan) |
			   TXPKT_PF_V(tx_info->adap->pf));
	cpl->pack = 0;
	cntrl1 = TXPKT_CSUM_TYPE_V(tx_info->ip_family == AF_INET ?
				   TX_CSUM_TCPIP : TX_CSUM_TCPIP6);
	cntrl1 |= T6_TXPKT_ETHHDR_LEN_V(maclen - ETH_HLEN) |
		  TXPKT_IPHDR_LEN_V(iplen);
	/* checksum offload */
	cpl->ctrl1 = cpu_to_be64(cntrl1);
	cpl->len = htons(skb->len);

	pos = cpl + 1;

	cxgb4_ग_लिखो_sgl(skb, &q->q, pos, end, 0, sgl_sdesc->addr);
	sgl_sdesc->skb = skb;
	chcr_txq_advance(&q->q, ndesc);
	cxgb4_ring_tx_db(tx_info->adap, &q->q, ndesc);
	वापस 0;
पूर्ण

/*
 * chcr_ktls_copy_record_in_skb
 * @nskb - new skb where the frags to be added.
 * @skb - old skb, to copy socket and deकाष्ठाor details.
 * @record - specअगरic record which has complete 16k record in frags.
 */
अटल व्योम chcr_ktls_copy_record_in_skb(काष्ठा sk_buff *nskb,
					 काष्ठा sk_buff *skb,
					 काष्ठा tls_record_info *record)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < record->num_frags; i++) अणु
		skb_shinfo(nskb)->frags[i] = record->frags[i];
		/* increase the frag ref count */
		__skb_frag_ref(&skb_shinfo(nskb)->frags[i]);
	पूर्ण

	skb_shinfo(nskb)->nr_frags = record->num_frags;
	nskb->data_len = record->len;
	nskb->len += record->len;
	nskb->truesize += record->len;
	nskb->sk = skb->sk;
	nskb->deकाष्ठाor = skb->deकाष्ठाor;
	refcount_add(nskb->truesize, &nskb->sk->sk_wmem_alloc);
पूर्ण

/*
 * chcr_end_part_handler: This handler will handle the record which
 * is complete or अगर record's end part is received. T6 adapter has a issue that
 * it can't send out TAG with partial record so अगर its an end part then we have
 * to send TAG as well and क्रम which we need to fetch the complete record and
 * send it to crypto module.
 * @tx_info - driver specअगरic tls info.
 * @skb - skb contains partial record.
 * @record - complete record of 16K size.
 * @tcp_seq
 * @mss - segment size in which TP needs to chop a packet.
 * @tcp_push_no_fin - tcp push अगर fin is not set.
 * @q - TX queue.
 * @tls_end_offset - offset from end of the record.
 * @last wr : check अगर this is the last part of the skb going out.
 * वापस: NETDEV_TX_OK/NETDEV_TX_BUSY.
 */
अटल पूर्णांक chcr_end_part_handler(काष्ठा chcr_ktls_info *tx_info,
				 काष्ठा sk_buff *skb,
				 काष्ठा tls_record_info *record,
				 u32 tcp_seq, पूर्णांक mss, bool tcp_push_no_fin,
				 काष्ठा sge_eth_txq *q, u32 skb_offset,
				 u32 tls_end_offset, bool last_wr)
अणु
	bool मुक्त_skb_अगर_tx_fails = false;
	काष्ठा sk_buff *nskb = शून्य;

	/* check अगर it is a complete record */
	अगर (tls_end_offset == record->len) अणु
		nskb = skb;
		atomic64_inc(&tx_info->adap->ch_ktls_stats.ktls_tx_complete_pkts);
	पूर्ण अन्यथा अणु
		nskb = alloc_skb(0, GFP_ATOMIC);
		अगर (!nskb) अणु
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_BUSY;
		पूर्ण

		/* copy complete record in skb */
		chcr_ktls_copy_record_in_skb(nskb, skb, record);
		/* packet is being sent from the beginning, update the tcp_seq
		 * accordingly.
		 */
		tcp_seq = tls_record_start_seq(record);
		/* reset skb offset */
		skb_offset = 0;

		अगर (last_wr)
			dev_kमुक्त_skb_any(skb);
		अन्यथा
			मुक्त_skb_अगर_tx_fails = true;

		last_wr = true;

		atomic64_inc(&tx_info->adap->ch_ktls_stats.ktls_tx_end_pkts);
	पूर्ण

	अगर (chcr_ktls_xmit_wr_complete(nskb, tx_info, q, tcp_seq,
				       last_wr, record->len, skb_offset,
				       record->num_frags,
				       (last_wr && tcp_push_no_fin),
				       mss)) अणु
		अगर (मुक्त_skb_अगर_tx_fails)
			dev_kमुक्त_skb_any(skb);
		जाओ out;
	पूर्ण
	tx_info->prev_seq = record->end_seq;
	वापस 0;
out:
	dev_kमुक्त_skb_any(nskb);
	वापस NETDEV_TX_BUSY;
पूर्ण

/*
 * chcr_लघु_record_handler: This handler will take care of the records which
 * करोesn't have end part (1st part or the middle part(/s) of a record). In such
 * हालs, AES CTR will be used in place of AES GCM to send out partial packet.
 * This partial record might be the first part of the record, or the middle
 * part. In हाल of middle record we should fetch the prior data to make it 16
 * byte aligned. If it has a partial tls header or iv then get to the start of
 * tls header. And अगर it has partial TAG, then हटाओ the complete TAG and send
 * only the payload.
 * There is one more possibility that it माला_लो a partial header, send that
 * portion as a plaपूर्णांकext.
 * @tx_info - driver specअगरic tls info.
 * @skb - skb contains partial record..
 * @record - complete record of 16K size.
 * @tcp_seq
 * @mss - segment size in which TP needs to chop a packet.
 * @tcp_push_no_fin - tcp push अगर fin is not set.
 * @q - TX queue.
 * @tls_end_offset - offset from end of the record.
 * वापस: NETDEV_TX_OK/NETDEV_TX_BUSY.
 */
अटल पूर्णांक chcr_लघु_record_handler(काष्ठा chcr_ktls_info *tx_info,
				     काष्ठा sk_buff *skb,
				     काष्ठा tls_record_info *record,
				     u32 tcp_seq, पूर्णांक mss, bool tcp_push_no_fin,
				     u32 data_len, u32 skb_offset,
				     काष्ठा sge_eth_txq *q, u32 tls_end_offset)
अणु
	u32 tls_rec_offset = tcp_seq - tls_record_start_seq(record);
	u8 prior_data[16] = अणु0पूर्ण;
	u32 prior_data_len = 0;

	/* check अगर the skb is ending in middle of tag/HASH, its a big
	 * trouble, send the packet beक्रमe the HASH.
	 */
	पूर्णांक reमुख्यing_record = tls_end_offset - data_len;

	अगर (reमुख्यing_record > 0 &&
	    reमुख्यing_record < TLS_CIPHER_AES_GCM_128_TAG_SIZE) अणु
		पूर्णांक trimmed_len = 0;

		अगर (tls_end_offset > TLS_CIPHER_AES_GCM_128_TAG_SIZE)
			trimmed_len = data_len -
				      (TLS_CIPHER_AES_GCM_128_TAG_SIZE -
				       reमुख्यing_record);
		अगर (!trimmed_len)
			वापस FALLBACK;

		WARN_ON(trimmed_len > data_len);

		data_len = trimmed_len;
		atomic64_inc(&tx_info->adap->ch_ktls_stats.ktls_tx_trimmed_pkts);
	पूर्ण

	/* check अगर it is only the header part. */
	अगर (tls_rec_offset + data_len <= (TLS_HEADER_SIZE + tx_info->iv_size)) अणु
		अगर (chcr_ktls_tx_plaपूर्णांकxt(tx_info, skb, tcp_seq, mss,
					  tcp_push_no_fin, q,
					  tx_info->port_id, prior_data,
					  data_len, skb_offset, prior_data_len))
			जाओ out;

		tx_info->prev_seq = tcp_seq + data_len;
		वापस 0;
	पूर्ण

	/* check अगर the middle record's start poपूर्णांक is 16 byte aligned. CTR
	 * needs 16 byte aligned start poपूर्णांक to start encryption.
	 */
	अगर (tls_rec_offset) अणु
		/* there is an offset from start, means its a middle record */
		पूर्णांक reमुख्यing = 0;

		अगर (tls_rec_offset < (TLS_HEADER_SIZE + tx_info->iv_size)) अणु
			prior_data_len = tls_rec_offset;
			tls_rec_offset = 0;
			reमुख्यing = 0;
		पूर्ण अन्यथा अणु
			prior_data_len =
				(tls_rec_offset -
				(TLS_HEADER_SIZE + tx_info->iv_size))
				% AES_BLOCK_LEN;
			reमुख्यing = tls_rec_offset - prior_data_len;
		पूर्ण

		/* अगर prior_data_len is not zero, means we need to fetch prior
		 * data to make this record 16 byte aligned, or we need to reach
		 * to start offset.
		 */
		अगर (prior_data_len) अणु
			पूर्णांक i = 0;
			u8 *data = शून्य;
			skb_frag_t *f;
			u8 *vaddr;
			पूर्णांक frag_size = 0, frag_delta = 0;

			जबतक (reमुख्यing > 0) अणु
				frag_size = skb_frag_size(&record->frags[i]);
				अगर (reमुख्यing < frag_size)
					अवरोध;

				reमुख्यing -= frag_size;
				i++;
			पूर्ण
			f = &record->frags[i];
			vaddr = kmap_atomic(skb_frag_page(f));

			data = vaddr + skb_frag_off(f)  + reमुख्यing;
			frag_delta = skb_frag_size(f) - reमुख्यing;

			अगर (frag_delta >= prior_data_len) अणु
				स_नकल(prior_data, data, prior_data_len);
				kunmap_atomic(vaddr);
			पूर्ण अन्यथा अणु
				स_नकल(prior_data, data, frag_delta);
				kunmap_atomic(vaddr);
				/* get the next page */
				f = &record->frags[i + 1];
				vaddr = kmap_atomic(skb_frag_page(f));
				data = vaddr + skb_frag_off(f);
				स_नकल(prior_data + frag_delta,
				       data, (prior_data_len - frag_delta));
				kunmap_atomic(vaddr);
			पूर्ण
			/* reset tcp_seq as per the prior_data_required len */
			tcp_seq -= prior_data_len;
		पूर्ण
		atomic64_inc(&tx_info->adap->ch_ktls_stats.ktls_tx_middle_pkts);
	पूर्ण अन्यथा अणु
		atomic64_inc(&tx_info->adap->ch_ktls_stats.ktls_tx_start_pkts);
	पूर्ण

	अगर (chcr_ktls_xmit_wr_लघु(skb, tx_info, q, tcp_seq, tcp_push_no_fin,
				    mss, tls_rec_offset, prior_data,
				    prior_data_len, data_len, skb_offset)) अणु
		जाओ out;
	पूर्ण

	tx_info->prev_seq = tcp_seq + data_len + prior_data_len;
	वापस 0;
out:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल पूर्णांक chcr_ktls_sw_fallback(काष्ठा sk_buff *skb,
				 काष्ठा chcr_ktls_info *tx_info,
				 काष्ठा sge_eth_txq *q)
अणु
	u32 data_len, skb_offset;
	काष्ठा sk_buff *nskb;
	काष्ठा tcphdr *th;

	nskb = tls_encrypt_skb(skb);

	अगर (!nskb)
		वापस 0;

	th = tcp_hdr(nskb);
	skb_offset =  skb_transport_offset(nskb) + tcp_hdrlen(nskb);
	data_len = nskb->len - skb_offset;
	skb_tx_बारtamp(nskb);

	अगर (chcr_ktls_tunnel_pkt(tx_info, nskb, q))
		जाओ out;

	tx_info->prev_seq = ntohl(th->seq) + data_len;
	atomic64_inc(&tx_info->adap->ch_ktls_stats.ktls_tx_fallback);
	वापस 0;
out:
	dev_kमुक्त_skb_any(nskb);
	वापस 0;
पूर्ण
/* nic tls TX handler */
अटल पूर्णांक chcr_ktls_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	u32 tls_end_offset, tcp_seq, skb_data_len, skb_offset;
	काष्ठा ch_ktls_port_stats_debug *port_stats;
	काष्ठा chcr_ktls_ofld_ctx_tx *tx_ctx;
	काष्ठा ch_ktls_stats_debug *stats;
	काष्ठा tcphdr *th = tcp_hdr(skb);
	पूर्णांक data_len, qidx, ret = 0, mss;
	काष्ठा tls_record_info *record;
	काष्ठा chcr_ktls_info *tx_info;
	काष्ठा tls_context *tls_ctx;
	काष्ठा sge_eth_txq *q;
	काष्ठा adapter *adap;
	अचिन्हित दीर्घ flags;

	tcp_seq = ntohl(th->seq);
	skb_offset = skb_transport_offset(skb) + tcp_hdrlen(skb);
	skb_data_len = skb->len - skb_offset;
	data_len = skb_data_len;

	mss = skb_is_gso(skb) ? skb_shinfo(skb)->gso_size : data_len;

	tls_ctx = tls_get_ctx(skb->sk);
	अगर (unlikely(tls_ctx->netdev != dev))
		जाओ out;

	tx_ctx = chcr_get_ktls_tx_context(tls_ctx);
	tx_info = tx_ctx->chcr_info;

	अगर (unlikely(!tx_info))
		जाओ out;

	adap = tx_info->adap;
	stats = &adap->ch_ktls_stats;
	port_stats = &stats->ktls_port[tx_info->port_id];

	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + tx_info->first_qset];
	cxgb4_reclaim_completed_tx(adap, &q->q, true);
	/* अगर tcp options are set but finish is not send the options first */
	अगर (!th->fin && chcr_ktls_check_tcp_options(th)) अणु
		ret = chcr_ktls_ग_लिखो_tcp_options(tx_info, skb, q,
						  tx_info->tx_chan);
		अगर (ret)
			वापस NETDEV_TX_BUSY;
	पूर्ण

	/* TCP segments can be in received either complete or partial.
	 * chcr_end_part_handler will handle हालs अगर complete record or end
	 * part of the record is received. In हाल of partial end part of record,
	 * we will send the complete record again.
	 */

	spin_lock_irqsave(&tx_ctx->base.lock, flags);

	करो अणु

		cxgb4_reclaim_completed_tx(adap, &q->q, true);
		/* fetch the tls record */
		record = tls_get_record(&tx_ctx->base, tcp_seq,
					&tx_info->record_no);
		/* By the समय packet reached to us, ACK is received, and record
		 * won't be found in that हाल, handle it gracefully.
		 */
		अगर (unlikely(!record)) अणु
			spin_unlock_irqrestore(&tx_ctx->base.lock, flags);
			atomic64_inc(&port_stats->ktls_tx_drop_no_sync_data);
			जाओ out;
		पूर्ण

		tls_end_offset = record->end_seq - tcp_seq;

		pr_debug("seq 0x%x, end_seq 0x%x prev_seq 0x%x, datalen 0x%x\n",
			 tcp_seq, record->end_seq, tx_info->prev_seq, data_len);
		/* update tcb क्रम the skb */
		अगर (skb_data_len == data_len) अणु
			u32 tx_max = tcp_seq;

			अगर (!tls_record_is_start_marker(record) &&
			    tls_end_offset < TLS_CIPHER_AES_GCM_128_TAG_SIZE)
				tx_max = record->end_seq -
					TLS_CIPHER_AES_GCM_128_TAG_SIZE;

			ret = chcr_ktls_xmit_tcb_cpls(tx_info, q, tx_max,
						      ntohl(th->ack_seq),
						      ntohs(th->winकरोw),
						      tls_end_offset !=
						      record->len);
			अगर (ret) अणु
				spin_unlock_irqrestore(&tx_ctx->base.lock,
						       flags);
				जाओ out;
			पूर्ण

			अगर (th->fin)
				skb_get(skb);
		पूर्ण

		अगर (unlikely(tls_record_is_start_marker(record))) अणु
			atomic64_inc(&port_stats->ktls_tx_skip_no_sync_data);
			/* If tls_end_offset < data_len, means there is some
			 * data after start marker, which needs encryption, send
			 * plaपूर्णांकext first and take skb refcount. अन्यथा send out
			 * complete pkt as plaपूर्णांकext.
			 */
			अगर (tls_end_offset < data_len)
				skb_get(skb);
			अन्यथा
				tls_end_offset = data_len;

			ret = chcr_ktls_tx_plaपूर्णांकxt(tx_info, skb, tcp_seq, mss,
						    (!th->fin && th->psh), q,
						    tx_info->port_id, शून्य,
						    tls_end_offset, skb_offset,
						    0);

			अगर (ret) अणु
				/* मुक्त the refcount taken earlier */
				अगर (tls_end_offset < data_len)
					dev_kमुक्त_skb_any(skb);
				spin_unlock_irqrestore(&tx_ctx->base.lock, flags);
				जाओ out;
			पूर्ण

			data_len -= tls_end_offset;
			tcp_seq = record->end_seq;
			skb_offset += tls_end_offset;
			जारी;
		पूर्ण

		/* अगर a tls record is finishing in this SKB */
		अगर (tls_end_offset <= data_len) अणु
			ret = chcr_end_part_handler(tx_info, skb, record,
						    tcp_seq, mss,
						    (!th->fin && th->psh), q,
						    skb_offset,
						    tls_end_offset,
						    skb_offset +
						    tls_end_offset == skb->len);

			data_len -= tls_end_offset;
			/* tcp_seq increment is required to handle next record.
			 */
			tcp_seq += tls_end_offset;
			skb_offset += tls_end_offset;
		पूर्ण अन्यथा अणु
			ret = chcr_लघु_record_handler(tx_info, skb,
							record, tcp_seq, mss,
							(!th->fin && th->psh),
							data_len, skb_offset,
							q, tls_end_offset);
			data_len = 0;
		पूर्ण

		/* अगर any failure, come out from the loop. */
		अगर (ret) अणु
			spin_unlock_irqrestore(&tx_ctx->base.lock, flags);
			अगर (th->fin)
				dev_kमुक्त_skb_any(skb);

			अगर (ret == FALLBACK)
				वापस chcr_ktls_sw_fallback(skb, tx_info, q);

			वापस NETDEV_TX_OK;
		पूर्ण

		/* length should never be less than 0 */
		WARN_ON(data_len < 0);

	पूर्ण जबतक (data_len > 0);

	spin_unlock_irqrestore(&tx_ctx->base.lock, flags);
	atomic64_inc(&port_stats->ktls_tx_encrypted_packets);
	atomic64_add(skb_data_len, &port_stats->ktls_tx_encrypted_bytes);

	/* tcp finish is set, send a separate tcp msg including all the options
	 * as well.
	 */
	अगर (th->fin) अणु
		chcr_ktls_ग_लिखो_tcp_options(tx_info, skb, q, tx_info->tx_chan);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	वापस NETDEV_TX_OK;
out:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम *chcr_ktls_uld_add(स्थिर काष्ठा cxgb4_lld_info *lldi)
अणु
	काष्ठा chcr_ktls_uld_ctx *u_ctx;

	pr_info_once("%s - version %s\n", CHCR_KTLS_DRV_DESC,
		     CHCR_KTLS_DRV_VERSION);
	u_ctx = kzalloc(माप(*u_ctx), GFP_KERNEL);
	अगर (!u_ctx) अणु
		u_ctx = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	u_ctx->lldi = *lldi;
	u_ctx->detach = false;
	xa_init_flags(&u_ctx->tid_list, XA_FLAGS_LOCK_BH);
out:
	वापस u_ctx;
पूर्ण

अटल स्थिर काष्ठा tlsdev_ops chcr_ktls_ops = अणु
	.tls_dev_add = chcr_ktls_dev_add,
	.tls_dev_del = chcr_ktls_dev_del,
पूर्ण;

अटल chcr_handler_func work_handlers[NUM_CPL_CMDS] = अणु
	[CPL_ACT_OPEN_RPL] = chcr_ktls_cpl_act_खोलो_rpl,
	[CPL_SET_TCB_RPL] = chcr_ktls_cpl_set_tcb_rpl,
पूर्ण;

अटल पूर्णांक chcr_ktls_uld_rx_handler(व्योम *handle, स्थिर __be64 *rsp,
				    स्थिर काष्ठा pkt_gl *pgl)
अणु
	स्थिर काष्ठा cpl_act_खोलो_rpl *rpl = (काष्ठा cpl_act_खोलो_rpl *)rsp;
	काष्ठा chcr_ktls_uld_ctx *u_ctx = handle;
	u8 opcode = rpl->ot.opcode;
	काष्ठा adapter *adap;

	adap = pci_get_drvdata(u_ctx->lldi.pdev);

	अगर (!work_handlers[opcode]) अणु
		pr_err("Unsupported opcode %d received\n", opcode);
		वापस 0;
	पूर्ण

	work_handlers[opcode](adap, (अचिन्हित अक्षर *)&rsp[1]);
	वापस 0;
पूर्ण

अटल व्योम clear_conn_resources(काष्ठा chcr_ktls_info *tx_info)
अणु
	/* clear l2t entry */
	अगर (tx_info->l2te)
		cxgb4_l2t_release(tx_info->l2te);

#अगर IS_ENABLED(CONFIG_IPV6)
	/* clear clip entry */
	अगर (tx_info->ip_family == AF_INET6)
		cxgb4_clip_release(tx_info->netdev, (स्थिर u32 *)
				   &tx_info->sk->sk_v6_rcv_saddr,
				   1);
#पूर्ण_अगर

	/* clear tid */
	अगर (tx_info->tid != -1)
		cxgb4_हटाओ_tid(&tx_info->adap->tids, tx_info->tx_chan,
				 tx_info->tid, tx_info->ip_family);
पूर्ण

अटल व्योम ch_ktls_reset_all_conn(काष्ठा chcr_ktls_uld_ctx *u_ctx)
अणु
	काष्ठा ch_ktls_port_stats_debug *port_stats;
	काष्ठा chcr_ktls_ofld_ctx_tx *tx_ctx;
	काष्ठा chcr_ktls_info *tx_info;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&u_ctx->tid_list, index, tx_ctx) अणु
		tx_info = tx_ctx->chcr_info;
		clear_conn_resources(tx_info);
		port_stats = &tx_info->adap->ch_ktls_stats.ktls_port[tx_info->port_id];
		atomic64_inc(&port_stats->ktls_tx_connection_बंद);
		kvमुक्त(tx_info);
		tx_ctx->chcr_info = शून्य;
		/* release module refcount */
		module_put(THIS_MODULE);
	पूर्ण
पूर्ण

अटल पूर्णांक chcr_ktls_uld_state_change(व्योम *handle, क्रमागत cxgb4_state new_state)
अणु
	काष्ठा chcr_ktls_uld_ctx *u_ctx = handle;

	चयन (new_state) अणु
	हाल CXGB4_STATE_UP:
		pr_info("%s: Up\n", pci_name(u_ctx->lldi.pdev));
		mutex_lock(&dev_mutex);
		list_add_tail(&u_ctx->entry, &uld_ctx_list);
		mutex_unlock(&dev_mutex);
		अवरोध;
	हाल CXGB4_STATE_START_RECOVERY:
	हाल CXGB4_STATE_DOWN:
	हाल CXGB4_STATE_DETACH:
		pr_info("%s: Down\n", pci_name(u_ctx->lldi.pdev));
		mutex_lock(&dev_mutex);
		u_ctx->detach = true;
		list_del(&u_ctx->entry);
		ch_ktls_reset_all_conn(u_ctx);
		xa_destroy(&u_ctx->tid_list);
		mutex_unlock(&dev_mutex);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cxgb4_uld_info chcr_ktls_uld_info = अणु
	.name = CHCR_KTLS_DRV_MODULE_NAME,
	.nrxq = 1,
	.rxq_size = 1024,
	.add = chcr_ktls_uld_add,
	.tx_handler = chcr_ktls_xmit,
	.rx_handler = chcr_ktls_uld_rx_handler,
	.state_change = chcr_ktls_uld_state_change,
	.tlsdev_ops = &chcr_ktls_ops,
पूर्ण;

अटल पूर्णांक __init chcr_ktls_init(व्योम)
अणु
	cxgb4_रेजिस्टर_uld(CXGB4_ULD_KTLS, &chcr_ktls_uld_info);
	वापस 0;
पूर्ण

अटल व्योम __निकास chcr_ktls_निकास(व्योम)
अणु
	काष्ठा chcr_ktls_uld_ctx *u_ctx, *पंचांगp;
	काष्ठा adapter *adap;

	pr_info("driver unloaded\n");

	mutex_lock(&dev_mutex);
	list_क्रम_each_entry_safe(u_ctx, पंचांगp, &uld_ctx_list, entry) अणु
		adap = pci_get_drvdata(u_ctx->lldi.pdev);
		स_रखो(&adap->ch_ktls_stats, 0, माप(adap->ch_ktls_stats));
		list_del(&u_ctx->entry);
		xa_destroy(&u_ctx->tid_list);
		kमुक्त(u_ctx);
	पूर्ण
	mutex_unlock(&dev_mutex);
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_KTLS);
पूर्ण

module_init(chcr_ktls_init);
module_निकास(chcr_ktls_निकास);

MODULE_DESCRIPTION("Chelsio NIC TLS ULD driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chelsio Communications");
MODULE_VERSION(CHCR_KTLS_DRV_VERSION);
