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
#समावेश <linux/tls.h>
#समावेश <net/tls.h>

#समावेश "chtls.h"
#समावेश "chtls_cm.h"

अटल व्योम __set_tcb_field_direct(काष्ठा chtls_sock *csk,
				   काष्ठा cpl_set_tcb_field *req, u16 word,
				   u64 mask, u64 val, u8 cookie, पूर्णांक no_reply)
अणु
	काष्ठा ulptx_idata *sc;

	INIT_TP_WR_CPL(req, CPL_SET_TCB_FIELD, csk->tid);
	req->wr.wr_mid |= htonl(FW_WR_FLOWID_V(csk->tid));
	req->reply_ctrl = htons(NO_REPLY_V(no_reply) |
				QUEUENO_V(csk->rss_qid));
	req->word_cookie = htons(TCB_WORD_V(word) | TCB_COOKIE_V(cookie));
	req->mask = cpu_to_be64(mask);
	req->val = cpu_to_be64(val);
	sc = (काष्ठा ulptx_idata *)(req + 1);
	sc->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_NOOP));
	sc->len = htonl(0);
पूर्ण

अटल व्योम __set_tcb_field(काष्ठा sock *sk, काष्ठा sk_buff *skb, u16 word,
			    u64 mask, u64 val, u8 cookie, पूर्णांक no_reply)
अणु
	काष्ठा cpl_set_tcb_field *req;
	काष्ठा chtls_sock *csk;
	काष्ठा ulptx_idata *sc;
	अचिन्हित पूर्णांक wrlen;

	wrlen = roundup(माप(*req) + माप(*sc), 16);
	csk = rcu_dereference_sk_user_data(sk);

	req = (काष्ठा cpl_set_tcb_field *)__skb_put(skb, wrlen);
	__set_tcb_field_direct(csk, req, word, mask, val, cookie, no_reply);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->port_id);
पूर्ण

/*
 * Send control message to HW, message go as immediate data and packet
 * is मुक्तd immediately.
 */
अटल पूर्णांक chtls_set_tcb_field(काष्ठा sock *sk, u16 word, u64 mask, u64 val)
अणु
	काष्ठा cpl_set_tcb_field *req;
	अचिन्हित पूर्णांक credits_needed;
	काष्ठा chtls_sock *csk;
	काष्ठा ulptx_idata *sc;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक wrlen;
	पूर्णांक ret;

	wrlen = roundup(माप(*req) + माप(*sc), 16);

	skb = alloc_skb(wrlen, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	credits_needed = DIV_ROUND_UP(wrlen, 16);
	csk = rcu_dereference_sk_user_data(sk);

	__set_tcb_field(sk, skb, word, mask, val, 0, 1);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPL_PRIORITY_DATA);
	csk->wr_credits -= credits_needed;
	csk->wr_unacked += credits_needed;
	enqueue_wr(csk, skb);
	ret = cxgb4_ofld_send(csk->egress_dev, skb);
	अगर (ret < 0)
		kमुक्त_skb(skb);
	वापस ret < 0 ? ret : 0;
पूर्ण

व्योम chtls_set_tcb_field_rpl_skb(काष्ठा sock *sk, u16 word,
				 u64 mask, u64 val, u8 cookie,
				 पूर्णांक through_l2t)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक wrlen;

	wrlen = माप(काष्ठा cpl_set_tcb_field) + माप(काष्ठा ulptx_idata);
	wrlen = roundup(wrlen, 16);

	skb = alloc_skb(wrlen, GFP_KERNEL | __GFP_NOFAIL);
	अगर (!skb)
		वापस;

	__set_tcb_field(sk, skb, word, mask, val, cookie, 0);
	send_or_defer(sk, tcp_sk(sk), skb, through_l2t);
पूर्ण

/*
 * Set one of the t_flags bits in the TCB.
 */
पूर्णांक chtls_set_tcb_tflag(काष्ठा sock *sk, अचिन्हित पूर्णांक bit_pos, पूर्णांक val)
अणु
	वापस chtls_set_tcb_field(sk, 1, 1ULL << bit_pos,
				   (u64)val << bit_pos);
पूर्ण

अटल पूर्णांक chtls_set_tcb_keyid(काष्ठा sock *sk, पूर्णांक keyid)
अणु
	वापस chtls_set_tcb_field(sk, 31, 0xFFFFFFFFULL, keyid);
पूर्ण

अटल पूर्णांक chtls_set_tcb_seqno(काष्ठा sock *sk)
अणु
	वापस chtls_set_tcb_field(sk, 28, ~0ULL, 0);
पूर्ण

अटल पूर्णांक chtls_set_tcb_quiesce(काष्ठा sock *sk, पूर्णांक val)
अणु
	वापस chtls_set_tcb_field(sk, 1, (1ULL << TF_RX_QUIESCE_S),
				   TF_RX_QUIESCE_V(val));
पूर्ण

व्योम chtls_set_quiesce_ctrl(काष्ठा sock *sk, पूर्णांक val)
अणु
	काष्ठा chtls_sock *csk;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक wrlen;
	पूर्णांक ret;

	wrlen = माप(काष्ठा cpl_set_tcb_field) + माप(काष्ठा ulptx_idata);
	wrlen = roundup(wrlen, 16);

	skb = alloc_skb(wrlen, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	csk = rcu_dereference_sk_user_data(sk);

	__set_tcb_field(sk, skb, 1, TF_RX_QUIESCE_V(1), 0, 0, 1);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->port_id);
	ret = cxgb4_ofld_send(csk->egress_dev, skb);
	अगर (ret < 0)
		kमुक्त_skb(skb);
पूर्ण

/* TLS Key biपंचांगap processing */
पूर्णांक chtls_init_kmap(काष्ठा chtls_dev *cdev, काष्ठा cxgb4_lld_info *lldi)
अणु
	अचिन्हित पूर्णांक num_key_ctx, bsize;
	पूर्णांक ksize;

	num_key_ctx = (lldi->vr->key.size / TLS_KEY_CONTEXT_SZ);
	bsize = BITS_TO_LONGS(num_key_ctx);

	cdev->kmap.size = num_key_ctx;
	cdev->kmap.available = bsize;
	ksize = माप(*cdev->kmap.addr) * bsize;
	cdev->kmap.addr = kvzalloc(ksize, GFP_KERNEL);
	अगर (!cdev->kmap.addr)
		वापस -ENOMEM;

	cdev->kmap.start = lldi->vr->key.start;
	spin_lock_init(&cdev->kmap.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक get_new_keyid(काष्ठा chtls_sock *csk, u32 optname)
अणु
	काष्ठा net_device *dev = csk->egress_dev;
	काष्ठा chtls_dev *cdev = csk->cdev;
	काष्ठा chtls_hws *hws;
	काष्ठा adapter *adap;
	पूर्णांक keyid;

	adap = netdev2adap(dev);
	hws = &csk->tlshws;

	spin_lock_bh(&cdev->kmap.lock);
	keyid = find_first_zero_bit(cdev->kmap.addr, cdev->kmap.size);
	अगर (keyid < cdev->kmap.size) अणु
		__set_bit(keyid, cdev->kmap.addr);
		अगर (optname == TLS_RX)
			hws->rxkey = keyid;
		अन्यथा
			hws->txkey = keyid;
		atomic_inc(&adap->chcr_stats.tls_key);
	पूर्ण अन्यथा अणु
		keyid = -1;
	पूर्ण
	spin_unlock_bh(&cdev->kmap.lock);
	वापस keyid;
पूर्ण

व्योम मुक्त_tls_keyid(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा net_device *dev = csk->egress_dev;
	काष्ठा chtls_dev *cdev = csk->cdev;
	काष्ठा chtls_hws *hws;
	काष्ठा adapter *adap;

	अगर (!cdev->kmap.addr)
		वापस;

	adap = netdev2adap(dev);
	hws = &csk->tlshws;

	spin_lock_bh(&cdev->kmap.lock);
	अगर (hws->rxkey >= 0) अणु
		__clear_bit(hws->rxkey, cdev->kmap.addr);
		atomic_dec(&adap->chcr_stats.tls_key);
		hws->rxkey = -1;
	पूर्ण
	अगर (hws->txkey >= 0) अणु
		__clear_bit(hws->txkey, cdev->kmap.addr);
		atomic_dec(&adap->chcr_stats.tls_key);
		hws->txkey = -1;
	पूर्ण
	spin_unlock_bh(&cdev->kmap.lock);
पूर्ण

अचिन्हित पूर्णांक keyid_to_addr(पूर्णांक start_addr, पूर्णांक keyid)
अणु
	वापस (start_addr + (keyid * TLS_KEY_CONTEXT_SZ)) >> 5;
पूर्ण

अटल व्योम chtls_rxkey_ivauth(काष्ठा _key_ctx *kctx)
अणु
	kctx->iv_to_auth = cpu_to_be64(KEYCTX_TX_WR_IV_V(6ULL) |
				  KEYCTX_TX_WR_AAD_V(1ULL) |
				  KEYCTX_TX_WR_AADST_V(5ULL) |
				  KEYCTX_TX_WR_CIPHER_V(14ULL) |
				  KEYCTX_TX_WR_CIPHERST_V(0ULL) |
				  KEYCTX_TX_WR_AUTH_V(14ULL) |
				  KEYCTX_TX_WR_AUTHST_V(16ULL) |
				  KEYCTX_TX_WR_AUTHIN_V(16ULL));
पूर्ण

अटल पूर्णांक chtls_key_info(काष्ठा chtls_sock *csk,
			  काष्ठा _key_ctx *kctx,
			  u32 keylen, u32 optname,
			  पूर्णांक cipher_type)
अणु
	अचिन्हित अक्षर key[AES_MAX_KEY_SIZE];
	अचिन्हित अक्षर *key_p, *salt;
	अचिन्हित अक्षर ghash_h[AEAD_H_SIZE];
	पूर्णांक ck_size, key_ctx_size, kctx_mackey_size, salt_size;
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret;

	key_ctx_size = माप(काष्ठा _key_ctx) +
		       roundup(keylen, 16) + AEAD_H_SIZE;

	/* GCM mode of AES supports 128 and 256 bit encryption, so
	 * prepare key context base on GCM cipher type
	 */
	चयन (cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128: अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 *gcm_ctx_128 =
			(काष्ठा tls12_crypto_info_aes_gcm_128 *)
					&csk->tlshws.crypto_info;
		स_नकल(key, gcm_ctx_128->key, keylen);

		key_p            = gcm_ctx_128->key;
		salt             = gcm_ctx_128->salt;
		ck_size          = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
		salt_size        = TLS_CIPHER_AES_GCM_128_SALT_SIZE;
		kctx_mackey_size = CHCR_KEYCTX_MAC_KEY_SIZE_128;
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_GCM_256: अणु
		काष्ठा tls12_crypto_info_aes_gcm_256 *gcm_ctx_256 =
			(काष्ठा tls12_crypto_info_aes_gcm_256 *)
					&csk->tlshws.crypto_info;
		स_नकल(key, gcm_ctx_256->key, keylen);

		key_p            = gcm_ctx_256->key;
		salt             = gcm_ctx_256->salt;
		ck_size          = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
		salt_size        = TLS_CIPHER_AES_GCM_256_SALT_SIZE;
		kctx_mackey_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
		अवरोध;
	पूर्ण
	शेष:
		pr_err("GCM: Invalid key length %d\n", keylen);
		वापस -EINVAL;
	पूर्ण

	/* Calculate the H = CIPH(K, 0 repeated 16 बार).
	 * It will go in key context
	 */
	ret = aes_expandkey(&aes, key, keylen);
	अगर (ret)
		वापस ret;

	स_रखो(ghash_h, 0, AEAD_H_SIZE);
	aes_encrypt(&aes, ghash_h, ghash_h);
	memzero_explicit(&aes, माप(aes));
	csk->tlshws.keylen = key_ctx_size;

	/* Copy the Key context */
	अगर (optname == TLS_RX) अणु
		पूर्णांक key_ctx;

		key_ctx = ((key_ctx_size >> 4) << 3);
		kctx->ctx_hdr = FILL_KEY_CRX_HDR(ck_size,
						 kctx_mackey_size,
						 0, 0, key_ctx);
		chtls_rxkey_ivauth(kctx);
	पूर्ण अन्यथा अणु
		kctx->ctx_hdr = FILL_KEY_CTX_HDR(ck_size,
						 kctx_mackey_size,
						 0, 0, key_ctx_size >> 4);
	पूर्ण

	स_नकल(kctx->salt, salt, salt_size);
	स_नकल(kctx->key, key_p, keylen);
	स_नकल(kctx->key + keylen, ghash_h, AEAD_H_SIZE);
	/* erase key info from driver */
	स_रखो(key_p, 0, keylen);

	वापस 0;
पूर्ण

अटल व्योम chtls_set_scmd(काष्ठा chtls_sock *csk)
अणु
	काष्ठा chtls_hws *hws = &csk->tlshws;

	hws->scmd.seqno_numivs =
		SCMD_SEQ_NO_CTRL_V(3) |
		SCMD_PROTO_VERSION_V(0) |
		SCMD_ENC_DEC_CTRL_V(0) |
		SCMD_CIPH_AUTH_SEQ_CTRL_V(1) |
		SCMD_CIPH_MODE_V(2) |
		SCMD_AUTH_MODE_V(4) |
		SCMD_HMAC_CTRL_V(0) |
		SCMD_IV_SIZE_V(4) |
		SCMD_NUM_IVS_V(1);

	hws->scmd.ivgen_hdrlen =
		SCMD_IV_GEN_CTRL_V(1) |
		SCMD_KEY_CTX_INLINE_V(0) |
		SCMD_TLS_FRAG_ENABLE_V(1);
पूर्ण

पूर्णांक chtls_setkey(काष्ठा chtls_sock *csk, u32 keylen,
		 u32 optname, पूर्णांक cipher_type)
अणु
	काष्ठा tls_key_req *kwr;
	काष्ठा chtls_dev *cdev;
	काष्ठा _key_ctx *kctx;
	पूर्णांक wrlen, klen, len;
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	पूर्णांक keyid;
	पूर्णांक kaddr;
	पूर्णांक ret;

	cdev = csk->cdev;
	sk = csk->sk;

	klen = roundup((keylen + AEAD_H_SIZE) + माप(*kctx), 32);
	wrlen = roundup(माप(*kwr), 16);
	len = klen + wrlen;

	/* Flush out-standing data beक्रमe new key takes effect */
	अगर (optname == TLS_TX) अणु
		lock_sock(sk);
		अगर (skb_queue_len(&csk->txq))
			chtls_push_frames(csk, 0);
		release_sock(sk);
	पूर्ण

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	keyid = get_new_keyid(csk, optname);
	अगर (keyid < 0) अणु
		ret = -ENOSPC;
		जाओ out_nokey;
	पूर्ण

	kaddr = keyid_to_addr(cdev->kmap.start, keyid);
	kwr = (काष्ठा tls_key_req *)__skb_put_zero(skb, len);
	kwr->wr.op_to_compl =
		cpu_to_be32(FW_WR_OP_V(FW_ULPTX_WR) | FW_WR_COMPL_F |
		      FW_WR_ATOMIC_V(1U));
	kwr->wr.flowid_len16 =
		cpu_to_be32(FW_WR_LEN16_V(DIV_ROUND_UP(len, 16) |
			    FW_WR_FLOWID_V(csk->tid)));
	kwr->wr.protocol = 0;
	kwr->wr.mfs = htons(TLS_MFS);
	kwr->wr.reneg_to_ग_लिखो_rx = optname;

	/* ulptx command */
	kwr->req.cmd = cpu_to_be32(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
			    T5_ULP_MEMIO_ORDER_V(1) |
			    T5_ULP_MEMIO_IMM_V(1));
	kwr->req.len16 = cpu_to_be32((csk->tid << 8) |
			      DIV_ROUND_UP(len - माप(kwr->wr), 16));
	kwr->req.dlen = cpu_to_be32(ULP_MEMIO_DATA_LEN_V(klen >> 5));
	kwr->req.lock_addr = cpu_to_be32(ULP_MEMIO_ADDR_V(kaddr));

	/* sub command */
	kwr->sc_imm.cmd_more = cpu_to_be32(ULPTX_CMD_V(ULP_TX_SC_IMM));
	kwr->sc_imm.len = cpu_to_be32(klen);

	lock_sock(sk);
	/* key info */
	kctx = (काष्ठा _key_ctx *)(kwr + 1);
	ret = chtls_key_info(csk, kctx, keylen, optname, cipher_type);
	अगर (ret)
		जाओ out_notcb;

	अगर (unlikely(csk_flag(sk, CSK_ABORT_SHUTDOWN)))
		जाओ out_notcb;

	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->tlshws.txqid);
	csk->wr_credits -= DIV_ROUND_UP(len, 16);
	csk->wr_unacked += DIV_ROUND_UP(len, 16);
	enqueue_wr(csk, skb);
	cxgb4_ofld_send(csk->egress_dev, skb);
	skb = शून्य;

	chtls_set_scmd(csk);
	/* Clear quiesce क्रम Rx key */
	अगर (optname == TLS_RX) अणु
		ret = chtls_set_tcb_keyid(sk, keyid);
		अगर (ret)
			जाओ out_notcb;
		ret = chtls_set_tcb_field(sk, 0,
					  TCB_ULP_RAW_V(TCB_ULP_RAW_M),
					  TCB_ULP_RAW_V((TF_TLS_KEY_SIZE_V(1) |
					  TF_TLS_CONTROL_V(1) |
					  TF_TLS_ACTIVE_V(1) |
					  TF_TLS_ENABLE_V(1))));
		अगर (ret)
			जाओ out_notcb;
		ret = chtls_set_tcb_seqno(sk);
		अगर (ret)
			जाओ out_notcb;
		ret = chtls_set_tcb_quiesce(sk, 0);
		अगर (ret)
			जाओ out_notcb;
		csk->tlshws.rxkey = keyid;
	पूर्ण अन्यथा अणु
		csk->tlshws.tx_seq_no = 0;
		csk->tlshws.txkey = keyid;
	पूर्ण

	release_sock(sk);
	वापस ret;
out_notcb:
	release_sock(sk);
	मुक्त_tls_keyid(sk);
out_nokey:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण
