<शैली गुरु>
/*
 * Copyright (c) 2016-2017, Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016-2017, Dave Watson <davejwatson@fb.com>. All rights reserved.
 * Copyright (c) 2016-2017, Lance Chao <lancerchao@fb.com>. All rights reserved.
 * Copyright (c) 2016, Friकरोlin Pokorny <friकरोlin.pokorny@gmail.com>. All rights reserved.
 * Copyright (c) 2016, Nikos Mavrogiannopoulos <nmav@gnutls.org>. All rights reserved.
 * Copyright (c) 2018, Covalent IO, Inc. http://covalent.io
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/splice.h>
#समावेश <crypto/aead.h>

#समावेश <net/strparser.h>
#समावेश <net/tls.h>

अटल पूर्णांक __skb_nsg(काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len,
                     अचिन्हित पूर्णांक recursion_level)
अणु
        पूर्णांक start = skb_headlen(skb);
        पूर्णांक i, chunk = start - offset;
        काष्ठा sk_buff *frag_iter;
        पूर्णांक elt = 0;

        अगर (unlikely(recursion_level >= 24))
                वापस -EMSGSIZE;

        अगर (chunk > 0) अणु
                अगर (chunk > len)
                        chunk = len;
                elt++;
                len -= chunk;
                अगर (len == 0)
                        वापस elt;
                offset += chunk;
        पूर्ण

        क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
                पूर्णांक end;

                WARN_ON(start > offset + len);

                end = start + skb_frag_size(&skb_shinfo(skb)->frags[i]);
                chunk = end - offset;
                अगर (chunk > 0) अणु
                        अगर (chunk > len)
                                chunk = len;
                        elt++;
                        len -= chunk;
                        अगर (len == 0)
                                वापस elt;
                        offset += chunk;
                पूर्ण
                start = end;
        पूर्ण

        अगर (unlikely(skb_has_frag_list(skb))) अणु
                skb_walk_frags(skb, frag_iter) अणु
                        पूर्णांक end, ret;

                        WARN_ON(start > offset + len);

                        end = start + frag_iter->len;
                        chunk = end - offset;
                        अगर (chunk > 0) अणु
                                अगर (chunk > len)
                                        chunk = len;
                                ret = __skb_nsg(frag_iter, offset - start, chunk,
                                                recursion_level + 1);
                                अगर (unlikely(ret < 0))
                                        वापस ret;
                                elt += ret;
                                len -= chunk;
                                अगर (len == 0)
                                        वापस elt;
                                offset += chunk;
                        पूर्ण
                        start = end;
                पूर्ण
        पूर्ण
        BUG_ON(len);
        वापस elt;
पूर्ण

/* Return the number of scatterlist elements required to completely map the
 * skb, or -EMSGSIZE अगर the recursion depth is exceeded.
 */
अटल पूर्णांक skb_nsg(काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len)
अणु
        वापस __skb_nsg(skb, offset, len, 0);
पूर्ण

अटल पूर्णांक padding_length(काष्ठा tls_sw_context_rx *ctx,
			  काष्ठा tls_prot_info *prot, काष्ठा sk_buff *skb)
अणु
	काष्ठा strp_msg *rxm = strp_msg(skb);
	पूर्णांक sub = 0;

	/* Determine zero-padding length */
	अगर (prot->version == TLS_1_3_VERSION) अणु
		अक्षर content_type = 0;
		पूर्णांक err;
		पूर्णांक back = 17;

		जबतक (content_type == 0) अणु
			अगर (back > rxm->full_len - prot->prepend_size)
				वापस -EBADMSG;
			err = skb_copy_bits(skb,
					    rxm->offset + rxm->full_len - back,
					    &content_type, 1);
			अगर (err)
				वापस err;
			अगर (content_type)
				अवरोध;
			sub++;
			back++;
		पूर्ण
		ctx->control = content_type;
	पूर्ण
	वापस sub;
पूर्ण

अटल व्योम tls_decrypt_करोne(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा aead_request *aead_req = (काष्ठा aead_request *)req;
	काष्ठा scatterlist *sgout = aead_req->dst;
	काष्ठा scatterlist *sgin = aead_req->src;
	काष्ठा tls_sw_context_rx *ctx;
	काष्ठा tls_context *tls_ctx;
	काष्ठा tls_prot_info *prot;
	काष्ठा scatterlist *sg;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक pages;
	पूर्णांक pending;

	skb = (काष्ठा sk_buff *)req->data;
	tls_ctx = tls_get_ctx(skb->sk);
	ctx = tls_sw_ctx_rx(tls_ctx);
	prot = &tls_ctx->prot_info;

	/* Propagate अगर there was an err */
	अगर (err) अणु
		अगर (err == -EBADMSG)
			TLS_INC_STATS(sock_net(skb->sk),
				      LINUX_MIB_TLSDECRYPTERROR);
		ctx->async_रुको.err = err;
		tls_err_पात(skb->sk, err);
	पूर्ण अन्यथा अणु
		काष्ठा strp_msg *rxm = strp_msg(skb);
		पूर्णांक pad;

		pad = padding_length(ctx, prot, skb);
		अगर (pad < 0) अणु
			ctx->async_रुको.err = pad;
			tls_err_पात(skb->sk, pad);
		पूर्ण अन्यथा अणु
			rxm->full_len -= pad;
			rxm->offset += prot->prepend_size;
			rxm->full_len -= prot->overhead_size;
		पूर्ण
	पूर्ण

	/* After using skb->sk to propagate sk through crypto async callback
	 * we need to शून्य it again.
	 */
	skb->sk = शून्य;


	/* Free the destination pages अगर skb was not decrypted inplace */
	अगर (sgout != sgin) अणु
		/* Skip the first S/G entry as it poपूर्णांकs to AAD */
		क्रम_each_sg(sg_next(sgout), sg, अच_पूर्णांक_उच्च, pages) अणु
			अगर (!sg)
				अवरोध;
			put_page(sg_page(sg));
		पूर्ण
	पूर्ण

	kमुक्त(aead_req);

	spin_lock_bh(&ctx->decrypt_compl_lock);
	pending = atomic_dec_वापस(&ctx->decrypt_pending);

	अगर (!pending && ctx->async_notअगरy)
		complete(&ctx->async_रुको.completion);
	spin_unlock_bh(&ctx->decrypt_compl_lock);
पूर्ण

अटल पूर्णांक tls_करो_decryption(काष्ठा sock *sk,
			     काष्ठा sk_buff *skb,
			     काष्ठा scatterlist *sgin,
			     काष्ठा scatterlist *sgout,
			     अक्षर *iv_recv,
			     माप_प्रकार data_len,
			     काष्ठा aead_request *aead_req,
			     bool async)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	पूर्णांक ret;

	aead_request_set_tfm(aead_req, ctx->aead_recv);
	aead_request_set_ad(aead_req, prot->aad_size);
	aead_request_set_crypt(aead_req, sgin, sgout,
			       data_len + prot->tag_size,
			       (u8 *)iv_recv);

	अगर (async) अणु
		/* Using skb->sk to push sk through to crypto async callback
		 * handler. This allows propagating errors up to the socket
		 * अगर needed. It _must_ be cleared in the async handler
		 * beक्रमe consume_skb is called. We _know_ skb->sk is शून्य
		 * because it is a clone from strparser.
		 */
		skb->sk = sk;
		aead_request_set_callback(aead_req,
					  CRYPTO_TFM_REQ_MAY_BACKLOG,
					  tls_decrypt_करोne, skb);
		atomic_inc(&ctx->decrypt_pending);
	पूर्ण अन्यथा अणु
		aead_request_set_callback(aead_req,
					  CRYPTO_TFM_REQ_MAY_BACKLOG,
					  crypto_req_करोne, &ctx->async_रुको);
	पूर्ण

	ret = crypto_aead_decrypt(aead_req);
	अगर (ret == -EINPROGRESS) अणु
		अगर (async)
			वापस ret;

		ret = crypto_रुको_req(ret, &ctx->async_रुको);
	पूर्ण

	अगर (async)
		atomic_dec(&ctx->decrypt_pending);

	वापस ret;
पूर्ण

अटल व्योम tls_trim_both_msgs(काष्ठा sock *sk, पूर्णांक target_size)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec = ctx->खोलो_rec;

	sk_msg_trim(sk, &rec->msg_plaपूर्णांकext, target_size);
	अगर (target_size > 0)
		target_size += prot->overhead_size;
	sk_msg_trim(sk, &rec->msg_encrypted, target_size);
पूर्ण

अटल पूर्णांक tls_alloc_encrypted_msg(काष्ठा sock *sk, पूर्णांक len)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec = ctx->खोलो_rec;
	काष्ठा sk_msg *msg_en = &rec->msg_encrypted;

	वापस sk_msg_alloc(sk, msg_en, len, 0);
पूर्ण

अटल पूर्णांक tls_clone_plaपूर्णांकext_msg(काष्ठा sock *sk, पूर्णांक required)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec = ctx->खोलो_rec;
	काष्ठा sk_msg *msg_pl = &rec->msg_plaपूर्णांकext;
	काष्ठा sk_msg *msg_en = &rec->msg_encrypted;
	पूर्णांक skip, len;

	/* We add page references worth len bytes from encrypted sg
	 * at the end of plaपूर्णांकext sg. It is guaranteed that msg_en
	 * has enough required room (ensured by caller).
	 */
	len = required - msg_pl->sg.size;

	/* Skip initial bytes in msg_en's data to be able to use
	 * same offset of both plain and encrypted data.
	 */
	skip = prot->prepend_size + msg_pl->sg.size;

	वापस sk_msg_clone(sk, msg_pl, msg_en, skip, len);
पूर्ण

अटल काष्ठा tls_rec *tls_get_rec(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा sk_msg *msg_pl, *msg_en;
	काष्ठा tls_rec *rec;
	पूर्णांक mem_size;

	mem_size = माप(काष्ठा tls_rec) + crypto_aead_reqsize(ctx->aead_send);

	rec = kzalloc(mem_size, sk->sk_allocation);
	अगर (!rec)
		वापस शून्य;

	msg_pl = &rec->msg_plaपूर्णांकext;
	msg_en = &rec->msg_encrypted;

	sk_msg_init(msg_pl);
	sk_msg_init(msg_en);

	sg_init_table(rec->sg_aead_in, 2);
	sg_set_buf(&rec->sg_aead_in[0], rec->aad_space, prot->aad_size);
	sg_unmark_end(&rec->sg_aead_in[1]);

	sg_init_table(rec->sg_aead_out, 2);
	sg_set_buf(&rec->sg_aead_out[0], rec->aad_space, prot->aad_size);
	sg_unmark_end(&rec->sg_aead_out[1]);

	वापस rec;
पूर्ण

अटल व्योम tls_मुक्त_rec(काष्ठा sock *sk, काष्ठा tls_rec *rec)
अणु
	sk_msg_मुक्त(sk, &rec->msg_encrypted);
	sk_msg_मुक्त(sk, &rec->msg_plaपूर्णांकext);
	kमुक्त(rec);
पूर्ण

अटल व्योम tls_मुक्त_खोलो_rec(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec = ctx->खोलो_rec;

	अगर (rec) अणु
		tls_मुक्त_rec(sk, rec);
		ctx->खोलो_rec = शून्य;
	पूर्ण
पूर्ण

पूर्णांक tls_tx_records(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec, *पंचांगp;
	काष्ठा sk_msg *msg_en;
	पूर्णांक tx_flags, rc = 0;

	अगर (tls_is_partially_sent_record(tls_ctx)) अणु
		rec = list_first_entry(&ctx->tx_list,
				       काष्ठा tls_rec, list);

		अगर (flags == -1)
			tx_flags = rec->tx_flags;
		अन्यथा
			tx_flags = flags;

		rc = tls_push_partial_record(sk, tls_ctx, tx_flags);
		अगर (rc)
			जाओ tx_err;

		/* Full record has been transmitted.
		 * Remove the head of tx_list
		 */
		list_del(&rec->list);
		sk_msg_मुक्त(sk, &rec->msg_plaपूर्णांकext);
		kमुक्त(rec);
	पूर्ण

	/* Tx all पढ़ोy records */
	list_क्रम_each_entry_safe(rec, पंचांगp, &ctx->tx_list, list) अणु
		अगर (READ_ONCE(rec->tx_पढ़ोy)) अणु
			अगर (flags == -1)
				tx_flags = rec->tx_flags;
			अन्यथा
				tx_flags = flags;

			msg_en = &rec->msg_encrypted;
			rc = tls_push_sg(sk, tls_ctx,
					 &msg_en->sg.data[msg_en->sg.curr],
					 0, tx_flags);
			अगर (rc)
				जाओ tx_err;

			list_del(&rec->list);
			sk_msg_मुक्त(sk, &rec->msg_plaपूर्णांकext);
			kमुक्त(rec);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

tx_err:
	अगर (rc < 0 && rc != -EAGAIN)
		tls_err_पात(sk, EBADMSG);

	वापस rc;
पूर्ण

अटल व्योम tls_encrypt_करोne(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा aead_request *aead_req = (काष्ठा aead_request *)req;
	काष्ठा sock *sk = req->data;
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा scatterlist *sge;
	काष्ठा sk_msg *msg_en;
	काष्ठा tls_rec *rec;
	bool पढ़ोy = false;
	पूर्णांक pending;

	rec = container_of(aead_req, काष्ठा tls_rec, aead_req);
	msg_en = &rec->msg_encrypted;

	sge = sk_msg_elem(msg_en, msg_en->sg.curr);
	sge->offset -= prot->prepend_size;
	sge->length += prot->prepend_size;

	/* Check अगर error is previously set on socket */
	अगर (err || sk->sk_err) अणु
		rec = शून्य;

		/* If err is alपढ़ोy set on socket, वापस the same code */
		अगर (sk->sk_err) अणु
			ctx->async_रुको.err = sk->sk_err;
		पूर्ण अन्यथा अणु
			ctx->async_रुको.err = err;
			tls_err_पात(sk, err);
		पूर्ण
	पूर्ण

	अगर (rec) अणु
		काष्ठा tls_rec *first_rec;

		/* Mark the record as पढ़ोy क्रम transmission */
		smp_store_mb(rec->tx_पढ़ोy, true);

		/* If received record is at head of tx_list, schedule tx */
		first_rec = list_first_entry(&ctx->tx_list,
					     काष्ठा tls_rec, list);
		अगर (rec == first_rec)
			पढ़ोy = true;
	पूर्ण

	spin_lock_bh(&ctx->encrypt_compl_lock);
	pending = atomic_dec_वापस(&ctx->encrypt_pending);

	अगर (!pending && ctx->async_notअगरy)
		complete(&ctx->async_रुको.completion);
	spin_unlock_bh(&ctx->encrypt_compl_lock);

	अगर (!पढ़ोy)
		वापस;

	/* Schedule the transmission */
	अगर (!test_and_set_bit(BIT_TX_SCHEDULED, &ctx->tx_biपंचांगask))
		schedule_delayed_work(&ctx->tx_work.work, 1);
पूर्ण

अटल पूर्णांक tls_करो_encryption(काष्ठा sock *sk,
			     काष्ठा tls_context *tls_ctx,
			     काष्ठा tls_sw_context_tx *ctx,
			     काष्ठा aead_request *aead_req,
			     माप_प्रकार data_len, u32 start)
अणु
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_rec *rec = ctx->खोलो_rec;
	काष्ठा sk_msg *msg_en = &rec->msg_encrypted;
	काष्ठा scatterlist *sge = sk_msg_elem(msg_en, start);
	पूर्णांक rc, iv_offset = 0;

	/* For CCM based ciphers, first byte of IV is a स्थिरant */
	अगर (prot->cipher_type == TLS_CIPHER_AES_CCM_128) अणु
		rec->iv_data[0] = TLS_AES_CCM_IV_B0_BYTE;
		iv_offset = 1;
	पूर्ण

	स_नकल(&rec->iv_data[iv_offset], tls_ctx->tx.iv,
	       prot->iv_size + prot->salt_size);

	xor_iv_with_seq(prot, rec->iv_data, tls_ctx->tx.rec_seq);

	sge->offset += prot->prepend_size;
	sge->length -= prot->prepend_size;

	msg_en->sg.curr = start;

	aead_request_set_tfm(aead_req, ctx->aead_send);
	aead_request_set_ad(aead_req, prot->aad_size);
	aead_request_set_crypt(aead_req, rec->sg_aead_in,
			       rec->sg_aead_out,
			       data_len, rec->iv_data);

	aead_request_set_callback(aead_req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  tls_encrypt_करोne, sk);

	/* Add the record in tx_list */
	list_add_tail((काष्ठा list_head *)&rec->list, &ctx->tx_list);
	atomic_inc(&ctx->encrypt_pending);

	rc = crypto_aead_encrypt(aead_req);
	अगर (!rc || rc != -EINPROGRESS) अणु
		atomic_dec(&ctx->encrypt_pending);
		sge->offset -= prot->prepend_size;
		sge->length += prot->prepend_size;
	पूर्ण

	अगर (!rc) अणु
		WRITE_ONCE(rec->tx_पढ़ोy, true);
	पूर्ण अन्यथा अगर (rc != -EINPROGRESS) अणु
		list_del(&rec->list);
		वापस rc;
	पूर्ण

	/* Unhook the record from context अगर encryption is not failure */
	ctx->खोलो_rec = शून्य;
	tls_advance_record_sn(sk, prot, &tls_ctx->tx);
	वापस rc;
पूर्ण

अटल पूर्णांक tls_split_खोलो_record(काष्ठा sock *sk, काष्ठा tls_rec *from,
				 काष्ठा tls_rec **to, काष्ठा sk_msg *msg_opl,
				 काष्ठा sk_msg *msg_oen, u32 split_poपूर्णांक,
				 u32 tx_overhead_size, u32 *orig_end)
अणु
	u32 i, j, bytes = 0, apply = msg_opl->apply_bytes;
	काष्ठा scatterlist *sge, *osge, *nsge;
	u32 orig_size = msg_opl->sg.size;
	काष्ठा scatterlist पंचांगp = अणु पूर्ण;
	काष्ठा sk_msg *msg_npl;
	काष्ठा tls_rec *new;
	पूर्णांक ret;

	new = tls_get_rec(sk);
	अगर (!new)
		वापस -ENOMEM;
	ret = sk_msg_alloc(sk, &new->msg_encrypted, msg_opl->sg.size +
			   tx_overhead_size, 0);
	अगर (ret < 0) अणु
		tls_मुक्त_rec(sk, new);
		वापस ret;
	पूर्ण

	*orig_end = msg_opl->sg.end;
	i = msg_opl->sg.start;
	sge = sk_msg_elem(msg_opl, i);
	जबतक (apply && sge->length) अणु
		अगर (sge->length > apply) अणु
			u32 len = sge->length - apply;

			get_page(sg_page(sge));
			sg_set_page(&पंचांगp, sg_page(sge), len,
				    sge->offset + apply);
			sge->length = apply;
			bytes += apply;
			apply = 0;
		पूर्ण अन्यथा अणु
			apply -= sge->length;
			bytes += sge->length;
		पूर्ण

		sk_msg_iter_var_next(i);
		अगर (i == msg_opl->sg.end)
			अवरोध;
		sge = sk_msg_elem(msg_opl, i);
	पूर्ण

	msg_opl->sg.end = i;
	msg_opl->sg.curr = i;
	msg_opl->sg.copyअवरोध = 0;
	msg_opl->apply_bytes = 0;
	msg_opl->sg.size = bytes;

	msg_npl = &new->msg_plaपूर्णांकext;
	msg_npl->apply_bytes = apply;
	msg_npl->sg.size = orig_size - bytes;

	j = msg_npl->sg.start;
	nsge = sk_msg_elem(msg_npl, j);
	अगर (पंचांगp.length) अणु
		स_नकल(nsge, &पंचांगp, माप(*nsge));
		sk_msg_iter_var_next(j);
		nsge = sk_msg_elem(msg_npl, j);
	पूर्ण

	osge = sk_msg_elem(msg_opl, i);
	जबतक (osge->length) अणु
		स_नकल(nsge, osge, माप(*nsge));
		sg_unmark_end(nsge);
		sk_msg_iter_var_next(i);
		sk_msg_iter_var_next(j);
		अगर (i == *orig_end)
			अवरोध;
		osge = sk_msg_elem(msg_opl, i);
		nsge = sk_msg_elem(msg_npl, j);
	पूर्ण

	msg_npl->sg.end = j;
	msg_npl->sg.curr = j;
	msg_npl->sg.copyअवरोध = 0;

	*to = new;
	वापस 0;
पूर्ण

अटल व्योम tls_merge_खोलो_record(काष्ठा sock *sk, काष्ठा tls_rec *to,
				  काष्ठा tls_rec *from, u32 orig_end)
अणु
	काष्ठा sk_msg *msg_npl = &from->msg_plaपूर्णांकext;
	काष्ठा sk_msg *msg_opl = &to->msg_plaपूर्णांकext;
	काष्ठा scatterlist *osge, *nsge;
	u32 i, j;

	i = msg_opl->sg.end;
	sk_msg_iter_var_prev(i);
	j = msg_npl->sg.start;

	osge = sk_msg_elem(msg_opl, i);
	nsge = sk_msg_elem(msg_npl, j);

	अगर (sg_page(osge) == sg_page(nsge) &&
	    osge->offset + osge->length == nsge->offset) अणु
		osge->length += nsge->length;
		put_page(sg_page(nsge));
	पूर्ण

	msg_opl->sg.end = orig_end;
	msg_opl->sg.curr = orig_end;
	msg_opl->sg.copyअवरोध = 0;
	msg_opl->apply_bytes = msg_opl->sg.size + msg_npl->sg.size;
	msg_opl->sg.size += msg_npl->sg.size;

	sk_msg_मुक्त(sk, &to->msg_encrypted);
	sk_msg_xfer_full(&to->msg_encrypted, &from->msg_encrypted);

	kमुक्त(from);
पूर्ण

अटल पूर्णांक tls_push_record(काष्ठा sock *sk, पूर्णांक flags,
			   अचिन्हित अक्षर record_type)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec = ctx->खोलो_rec, *पंचांगp = शून्य;
	u32 i, split_poपूर्णांक, orig_end;
	काष्ठा sk_msg *msg_pl, *msg_en;
	काष्ठा aead_request *req;
	bool split;
	पूर्णांक rc;

	अगर (!rec)
		वापस 0;

	msg_pl = &rec->msg_plaपूर्णांकext;
	msg_en = &rec->msg_encrypted;

	split_poपूर्णांक = msg_pl->apply_bytes;
	split = split_poपूर्णांक && split_poपूर्णांक < msg_pl->sg.size;
	अगर (unlikely((!split &&
		      msg_pl->sg.size +
		      prot->overhead_size > msg_en->sg.size) ||
		     (split &&
		      split_poपूर्णांक +
		      prot->overhead_size > msg_en->sg.size))) अणु
		split = true;
		split_poपूर्णांक = msg_en->sg.size;
	पूर्ण
	अगर (split) अणु
		rc = tls_split_खोलो_record(sk, rec, &पंचांगp, msg_pl, msg_en,
					   split_poपूर्णांक, prot->overhead_size,
					   &orig_end);
		अगर (rc < 0)
			वापस rc;
		/* This can happen अगर above tls_split_खोलो_record allocates
		 * a single large encryption buffer instead of two smaller
		 * ones. In this हाल adjust poपूर्णांकers and जारी without
		 * split.
		 */
		अगर (!msg_pl->sg.size) अणु
			tls_merge_खोलो_record(sk, rec, पंचांगp, orig_end);
			msg_pl = &rec->msg_plaपूर्णांकext;
			msg_en = &rec->msg_encrypted;
			split = false;
		पूर्ण
		sk_msg_trim(sk, msg_en, msg_pl->sg.size +
			    prot->overhead_size);
	पूर्ण

	rec->tx_flags = flags;
	req = &rec->aead_req;

	i = msg_pl->sg.end;
	sk_msg_iter_var_prev(i);

	rec->content_type = record_type;
	अगर (prot->version == TLS_1_3_VERSION) अणु
		/* Add content type to end of message.  No padding added */
		sg_set_buf(&rec->sg_content_type, &rec->content_type, 1);
		sg_mark_end(&rec->sg_content_type);
		sg_chain(msg_pl->sg.data, msg_pl->sg.end + 1,
			 &rec->sg_content_type);
	पूर्ण अन्यथा अणु
		sg_mark_end(sk_msg_elem(msg_pl, i));
	पूर्ण

	अगर (msg_pl->sg.end < msg_pl->sg.start) अणु
		sg_chain(&msg_pl->sg.data[msg_pl->sg.start],
			 MAX_SKB_FRAGS - msg_pl->sg.start + 1,
			 msg_pl->sg.data);
	पूर्ण

	i = msg_pl->sg.start;
	sg_chain(rec->sg_aead_in, 2, &msg_pl->sg.data[i]);

	i = msg_en->sg.end;
	sk_msg_iter_var_prev(i);
	sg_mark_end(sk_msg_elem(msg_en, i));

	i = msg_en->sg.start;
	sg_chain(rec->sg_aead_out, 2, &msg_en->sg.data[i]);

	tls_make_aad(rec->aad_space, msg_pl->sg.size + prot->tail_size,
		     tls_ctx->tx.rec_seq, record_type, prot);

	tls_fill_prepend(tls_ctx,
			 page_address(sg_page(&msg_en->sg.data[i])) +
			 msg_en->sg.data[i].offset,
			 msg_pl->sg.size + prot->tail_size,
			 record_type);

	tls_ctx->pending_खोलो_record_frags = false;

	rc = tls_करो_encryption(sk, tls_ctx, ctx, req,
			       msg_pl->sg.size + prot->tail_size, i);
	अगर (rc < 0) अणु
		अगर (rc != -EINPROGRESS) अणु
			tls_err_पात(sk, EBADMSG);
			अगर (split) अणु
				tls_ctx->pending_खोलो_record_frags = true;
				tls_merge_खोलो_record(sk, rec, पंचांगp, orig_end);
			पूर्ण
		पूर्ण
		ctx->async_capable = 1;
		वापस rc;
	पूर्ण अन्यथा अगर (split) अणु
		msg_pl = &पंचांगp->msg_plaपूर्णांकext;
		msg_en = &पंचांगp->msg_encrypted;
		sk_msg_trim(sk, msg_en, msg_pl->sg.size + prot->overhead_size);
		tls_ctx->pending_खोलो_record_frags = true;
		ctx->खोलो_rec = पंचांगp;
	पूर्ण

	वापस tls_tx_records(sk, flags);
पूर्ण

अटल पूर्णांक bpf_exec_tx_verdict(काष्ठा sk_msg *msg, काष्ठा sock *sk,
			       bool full_record, u8 record_type,
			       sमाप_प्रकार *copied, पूर्णांक flags)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा sk_msg msg_redir = अणु पूर्ण;
	काष्ठा sk_psock *psock;
	काष्ठा sock *sk_redir;
	काष्ठा tls_rec *rec;
	bool enospc, policy;
	पूर्णांक err = 0, send;
	u32 delta = 0;

	policy = !(flags & MSG_SENDPAGE_NOPOLICY);
	psock = sk_psock_get(sk);
	अगर (!psock || !policy) अणु
		err = tls_push_record(sk, flags, record_type);
		अगर (err && sk->sk_err == EBADMSG) अणु
			*copied -= sk_msg_मुक्त(sk, msg);
			tls_मुक्त_खोलो_rec(sk);
			err = -sk->sk_err;
		पूर्ण
		अगर (psock)
			sk_psock_put(sk, psock);
		वापस err;
	पूर्ण
more_data:
	enospc = sk_msg_full(msg);
	अगर (psock->eval == __SK_NONE) अणु
		delta = msg->sg.size;
		psock->eval = sk_psock_msg_verdict(sk, psock, msg);
		delta -= msg->sg.size;
	पूर्ण
	अगर (msg->cork_bytes && msg->cork_bytes > msg->sg.size &&
	    !enospc && !full_record) अणु
		err = -ENOSPC;
		जाओ out_err;
	पूर्ण
	msg->cork_bytes = 0;
	send = msg->sg.size;
	अगर (msg->apply_bytes && msg->apply_bytes < send)
		send = msg->apply_bytes;

	चयन (psock->eval) अणु
	हाल __SK_PASS:
		err = tls_push_record(sk, flags, record_type);
		अगर (err && sk->sk_err == EBADMSG) अणु
			*copied -= sk_msg_मुक्त(sk, msg);
			tls_मुक्त_खोलो_rec(sk);
			err = -sk->sk_err;
			जाओ out_err;
		पूर्ण
		अवरोध;
	हाल __SK_REसूचीECT:
		sk_redir = psock->sk_redir;
		स_नकल(&msg_redir, msg, माप(*msg));
		अगर (msg->apply_bytes < send)
			msg->apply_bytes = 0;
		अन्यथा
			msg->apply_bytes -= send;
		sk_msg_वापस_zero(sk, msg, send);
		msg->sg.size -= send;
		release_sock(sk);
		err = tcp_bpf_sendmsg_redir(sk_redir, &msg_redir, send, flags);
		lock_sock(sk);
		अगर (err < 0) अणु
			*copied -= sk_msg_मुक्त_noअक्षरge(sk, &msg_redir);
			msg->sg.size = 0;
		पूर्ण
		अगर (msg->sg.size == 0)
			tls_मुक्त_खोलो_rec(sk);
		अवरोध;
	हाल __SK_DROP:
	शेष:
		sk_msg_मुक्त_partial(sk, msg, send);
		अगर (msg->apply_bytes < send)
			msg->apply_bytes = 0;
		अन्यथा
			msg->apply_bytes -= send;
		अगर (msg->sg.size == 0)
			tls_मुक्त_खोलो_rec(sk);
		*copied -= (send + delta);
		err = -EACCES;
	पूर्ण

	अगर (likely(!err)) अणु
		bool reset_eval = !ctx->खोलो_rec;

		rec = ctx->खोलो_rec;
		अगर (rec) अणु
			msg = &rec->msg_plaपूर्णांकext;
			अगर (!msg->apply_bytes)
				reset_eval = true;
		पूर्ण
		अगर (reset_eval) अणु
			psock->eval = __SK_NONE;
			अगर (psock->sk_redir) अणु
				sock_put(psock->sk_redir);
				psock->sk_redir = शून्य;
			पूर्ण
		पूर्ण
		अगर (rec)
			जाओ more_data;
	पूर्ण
 out_err:
	sk_psock_put(sk, psock);
	वापस err;
पूर्ण

अटल पूर्णांक tls_sw_push_pending_record(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec = ctx->खोलो_rec;
	काष्ठा sk_msg *msg_pl;
	माप_प्रकार copied;

	अगर (!rec)
		वापस 0;

	msg_pl = &rec->msg_plaपूर्णांकext;
	copied = msg_pl->sg.size;
	अगर (!copied)
		वापस 0;

	वापस bpf_exec_tx_verdict(msg_pl, sk, true, TLS_RECORD_TYPE_DATA,
				   &copied, flags);
पूर्ण

पूर्णांक tls_sw_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	दीर्घ समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	bool async_capable = ctx->async_capable;
	अचिन्हित अक्षर record_type = TLS_RECORD_TYPE_DATA;
	bool is_kvec = iov_iter_is_kvec(&msg->msg_iter);
	bool eor = !(msg->msg_flags & MSG_MORE);
	माप_प्रकार try_to_copy;
	sमाप_प्रकार copied = 0;
	काष्ठा sk_msg *msg_pl, *msg_en;
	काष्ठा tls_rec *rec;
	पूर्णांक required_size;
	पूर्णांक num_async = 0;
	bool full_record;
	पूर्णांक record_room;
	पूर्णांक num_zc = 0;
	पूर्णांक orig_size;
	पूर्णांक ret = 0;
	पूर्णांक pending;

	अगर (msg->msg_flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL |
			       MSG_CMSG_COMPAT))
		वापस -EOPNOTSUPP;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);

	अगर (unlikely(msg->msg_controllen)) अणु
		ret = tls_proccess_cmsg(sk, msg, &record_type);
		अगर (ret) अणु
			अगर (ret == -EINPROGRESS)
				num_async++;
			अन्यथा अगर (ret != -EAGAIN)
				जाओ send_end;
		पूर्ण
	पूर्ण

	जबतक (msg_data_left(msg)) अणु
		अगर (sk->sk_err) अणु
			ret = -sk->sk_err;
			जाओ send_end;
		पूर्ण

		अगर (ctx->खोलो_rec)
			rec = ctx->खोलो_rec;
		अन्यथा
			rec = ctx->खोलो_rec = tls_get_rec(sk);
		अगर (!rec) अणु
			ret = -ENOMEM;
			जाओ send_end;
		पूर्ण

		msg_pl = &rec->msg_plaपूर्णांकext;
		msg_en = &rec->msg_encrypted;

		orig_size = msg_pl->sg.size;
		full_record = false;
		try_to_copy = msg_data_left(msg);
		record_room = TLS_MAX_PAYLOAD_SIZE - msg_pl->sg.size;
		अगर (try_to_copy >= record_room) अणु
			try_to_copy = record_room;
			full_record = true;
		पूर्ण

		required_size = msg_pl->sg.size + try_to_copy +
				prot->overhead_size;

		अगर (!sk_stream_memory_मुक्त(sk))
			जाओ रुको_क्रम_sndbuf;

alloc_encrypted:
		ret = tls_alloc_encrypted_msg(sk, required_size);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				जाओ रुको_क्रम_memory;

			/* Adjust try_to_copy according to the amount that was
			 * actually allocated. The dअगरference is due
			 * to max sg elements limit
			 */
			try_to_copy -= required_size - msg_en->sg.size;
			full_record = true;
		पूर्ण

		अगर (!is_kvec && (full_record || eor) && !async_capable) अणु
			u32 first = msg_pl->sg.end;

			ret = sk_msg_zerocopy_from_iter(sk, &msg->msg_iter,
							msg_pl, try_to_copy);
			अगर (ret)
				जाओ fallback_to_reg_send;

			num_zc++;
			copied += try_to_copy;

			sk_msg_sg_copy_set(msg_pl, first);
			ret = bpf_exec_tx_verdict(msg_pl, sk, full_record,
						  record_type, &copied,
						  msg->msg_flags);
			अगर (ret) अणु
				अगर (ret == -EINPROGRESS)
					num_async++;
				अन्यथा अगर (ret == -ENOMEM)
					जाओ रुको_क्रम_memory;
				अन्यथा अगर (ctx->खोलो_rec && ret == -ENOSPC)
					जाओ rollback_iter;
				अन्यथा अगर (ret != -EAGAIN)
					जाओ send_end;
			पूर्ण
			जारी;
rollback_iter:
			copied -= try_to_copy;
			sk_msg_sg_copy_clear(msg_pl, first);
			iov_iter_revert(&msg->msg_iter,
					msg_pl->sg.size - orig_size);
fallback_to_reg_send:
			sk_msg_trim(sk, msg_pl, orig_size);
		पूर्ण

		required_size = msg_pl->sg.size + try_to_copy;

		ret = tls_clone_plaपूर्णांकext_msg(sk, required_size);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				जाओ send_end;

			/* Adjust try_to_copy according to the amount that was
			 * actually allocated. The dअगरference is due
			 * to max sg elements limit
			 */
			try_to_copy -= required_size - msg_pl->sg.size;
			full_record = true;
			sk_msg_trim(sk, msg_en,
				    msg_pl->sg.size + prot->overhead_size);
		पूर्ण

		अगर (try_to_copy) अणु
			ret = sk_msg_memcopy_from_iter(sk, &msg->msg_iter,
						       msg_pl, try_to_copy);
			अगर (ret < 0)
				जाओ trim_sgl;
		पूर्ण

		/* Open records defined only अगर successfully copied, otherwise
		 * we would trim the sg but not reset the खोलो record frags.
		 */
		tls_ctx->pending_खोलो_record_frags = true;
		copied += try_to_copy;
		अगर (full_record || eor) अणु
			ret = bpf_exec_tx_verdict(msg_pl, sk, full_record,
						  record_type, &copied,
						  msg->msg_flags);
			अगर (ret) अणु
				अगर (ret == -EINPROGRESS)
					num_async++;
				अन्यथा अगर (ret == -ENOMEM)
					जाओ रुको_क्रम_memory;
				अन्यथा अगर (ret != -EAGAIN) अणु
					अगर (ret == -ENOSPC)
						ret = 0;
					जाओ send_end;
				पूर्ण
			पूर्ण
		पूर्ण

		जारी;

रुको_क्रम_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
रुको_क्रम_memory:
		ret = sk_stream_रुको_memory(sk, &समयo);
		अगर (ret) अणु
trim_sgl:
			अगर (ctx->खोलो_rec)
				tls_trim_both_msgs(sk, orig_size);
			जाओ send_end;
		पूर्ण

		अगर (ctx->खोलो_rec && msg_en->sg.size < required_size)
			जाओ alloc_encrypted;
	पूर्ण

	अगर (!num_async) अणु
		जाओ send_end;
	पूर्ण अन्यथा अगर (num_zc) अणु
		/* Wait क्रम pending encryptions to get completed */
		spin_lock_bh(&ctx->encrypt_compl_lock);
		ctx->async_notअगरy = true;

		pending = atomic_पढ़ो(&ctx->encrypt_pending);
		spin_unlock_bh(&ctx->encrypt_compl_lock);
		अगर (pending)
			crypto_रुको_req(-EINPROGRESS, &ctx->async_रुको);
		अन्यथा
			reinit_completion(&ctx->async_रुको.completion);

		/* There can be no concurrent accesses, since we have no
		 * pending encrypt operations
		 */
		WRITE_ONCE(ctx->async_notअगरy, false);

		अगर (ctx->async_रुको.err) अणु
			ret = ctx->async_रुको.err;
			copied = 0;
		पूर्ण
	पूर्ण

	/* Transmit अगर any encryptions have completed */
	अगर (test_and_clear_bit(BIT_TX_SCHEDULED, &ctx->tx_biपंचांगask)) अणु
		cancel_delayed_work(&ctx->tx_work.work);
		tls_tx_records(sk, msg->msg_flags);
	पूर्ण

send_end:
	ret = sk_stream_error(sk, msg->msg_flags, ret);

	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	वापस copied > 0 ? copied : ret;
पूर्ण

अटल पूर्णांक tls_sw_करो_sendpage(काष्ठा sock *sk, काष्ठा page *page,
			      पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	दीर्घ समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	अचिन्हित अक्षर record_type = TLS_RECORD_TYPE_DATA;
	काष्ठा sk_msg *msg_pl;
	काष्ठा tls_rec *rec;
	पूर्णांक num_async = 0;
	sमाप_प्रकार copied = 0;
	bool full_record;
	पूर्णांक record_room;
	पूर्णांक ret = 0;
	bool eor;

	eor = !(flags & (MSG_MORE | MSG_SENDPAGE_NOTLAST));
	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	/* Call the sk_stream functions to manage the sndbuf mem. */
	जबतक (size > 0) अणु
		माप_प्रकार copy, required_size;

		अगर (sk->sk_err) अणु
			ret = -sk->sk_err;
			जाओ sendpage_end;
		पूर्ण

		अगर (ctx->खोलो_rec)
			rec = ctx->खोलो_rec;
		अन्यथा
			rec = ctx->खोलो_rec = tls_get_rec(sk);
		अगर (!rec) अणु
			ret = -ENOMEM;
			जाओ sendpage_end;
		पूर्ण

		msg_pl = &rec->msg_plaपूर्णांकext;

		full_record = false;
		record_room = TLS_MAX_PAYLOAD_SIZE - msg_pl->sg.size;
		copy = size;
		अगर (copy >= record_room) अणु
			copy = record_room;
			full_record = true;
		पूर्ण

		required_size = msg_pl->sg.size + copy + prot->overhead_size;

		अगर (!sk_stream_memory_मुक्त(sk))
			जाओ रुको_क्रम_sndbuf;
alloc_payload:
		ret = tls_alloc_encrypted_msg(sk, required_size);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				जाओ रुको_क्रम_memory;

			/* Adjust copy according to the amount that was
			 * actually allocated. The dअगरference is due
			 * to max sg elements limit
			 */
			copy -= required_size - msg_pl->sg.size;
			full_record = true;
		पूर्ण

		sk_msg_page_add(msg_pl, page, copy, offset);
		sk_mem_अक्षरge(sk, copy);

		offset += copy;
		size -= copy;
		copied += copy;

		tls_ctx->pending_खोलो_record_frags = true;
		अगर (full_record || eor || sk_msg_full(msg_pl)) अणु
			ret = bpf_exec_tx_verdict(msg_pl, sk, full_record,
						  record_type, &copied, flags);
			अगर (ret) अणु
				अगर (ret == -EINPROGRESS)
					num_async++;
				अन्यथा अगर (ret == -ENOMEM)
					जाओ रुको_क्रम_memory;
				अन्यथा अगर (ret != -EAGAIN) अणु
					अगर (ret == -ENOSPC)
						ret = 0;
					जाओ sendpage_end;
				पूर्ण
			पूर्ण
		पूर्ण
		जारी;
रुको_क्रम_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
रुको_क्रम_memory:
		ret = sk_stream_रुको_memory(sk, &समयo);
		अगर (ret) अणु
			अगर (ctx->खोलो_rec)
				tls_trim_both_msgs(sk, msg_pl->sg.size);
			जाओ sendpage_end;
		पूर्ण

		अगर (ctx->खोलो_rec)
			जाओ alloc_payload;
	पूर्ण

	अगर (num_async) अणु
		/* Transmit अगर any encryptions have completed */
		अगर (test_and_clear_bit(BIT_TX_SCHEDULED, &ctx->tx_biपंचांगask)) अणु
			cancel_delayed_work(&ctx->tx_work.work);
			tls_tx_records(sk, flags);
		पूर्ण
	पूर्ण
sendpage_end:
	ret = sk_stream_error(sk, flags, ret);
	वापस copied > 0 ? copied : ret;
पूर्ण

पूर्णांक tls_sw_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page,
			   पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL |
		      MSG_SENDPAGE_NOTLAST | MSG_SENDPAGE_NOPOLICY |
		      MSG_NO_SHARED_FRAGS))
		वापस -EOPNOTSUPP;

	वापस tls_sw_करो_sendpage(sk, page, offset, size, flags);
पूर्ण

पूर्णांक tls_sw_sendpage(काष्ठा sock *sk, काष्ठा page *page,
		    पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	पूर्णांक ret;

	अगर (flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL |
		      MSG_SENDPAGE_NOTLAST | MSG_SENDPAGE_NOPOLICY))
		वापस -EOPNOTSUPP;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);
	ret = tls_sw_करो_sendpage(sk, page, offset, size, flags);
	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *tls_रुको_data(काष्ठा sock *sk, काष्ठा sk_psock *psock,
				     bool nonblock, दीर्घ समयo, पूर्णांक *err)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा sk_buff *skb;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	जबतक (!(skb = ctx->recv_pkt) && sk_psock_queue_empty(psock)) अणु
		अगर (sk->sk_err) अणु
			*err = sock_error(sk);
			वापस शून्य;
		पूर्ण

		अगर (!skb_queue_empty(&sk->sk_receive_queue)) अणु
			__strp_unछोड़ो(&ctx->strp);
			अगर (ctx->recv_pkt)
				वापस ctx->recv_pkt;
		पूर्ण

		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			वापस शून्य;

		अगर (sock_flag(sk, SOCK_DONE))
			वापस शून्य;

		अगर (nonblock || !समयo) अणु
			*err = -EAGAIN;
			वापस शून्य;
		पूर्ण

		add_रुको_queue(sk_sleep(sk), &रुको);
		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		sk_रुको_event(sk, &समयo,
			      ctx->recv_pkt != skb ||
			      !sk_psock_queue_empty(psock),
			      &रुको);
		sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		हटाओ_रुको_queue(sk_sleep(sk), &रुको);

		/* Handle संकेतs */
		अगर (संकेत_pending(current)) अणु
			*err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक tls_setup_from_iter(काष्ठा sock *sk, काष्ठा iov_iter *from,
			       पूर्णांक length, पूर्णांक *pages_used,
			       अचिन्हित पूर्णांक *size_used,
			       काष्ठा scatterlist *to,
			       पूर्णांक to_max_pages)
अणु
	पूर्णांक rc = 0, i = 0, num_elem = *pages_used, maxpages;
	काष्ठा page *pages[MAX_SKB_FRAGS];
	अचिन्हित पूर्णांक size = *size_used;
	sमाप_प्रकार copied, use;
	माप_प्रकार offset;

	जबतक (length > 0) अणु
		i = 0;
		maxpages = to_max_pages - num_elem;
		अगर (maxpages == 0) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण
		copied = iov_iter_get_pages(from, pages,
					    length,
					    maxpages, &offset);
		अगर (copied <= 0) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		iov_iter_advance(from, copied);

		length -= copied;
		size += copied;
		जबतक (copied) अणु
			use = min_t(पूर्णांक, copied, PAGE_SIZE - offset);

			sg_set_page(&to[num_elem],
				    pages[i], use, offset);
			sg_unmark_end(&to[num_elem]);
			/* We करो not unअक्षरge memory from this API */

			offset = 0;
			copied -= use;

			i++;
			num_elem++;
		पूर्ण
	पूर्ण
	/* Mark the end in the last sg entry अगर newly added */
	अगर (num_elem > *pages_used)
		sg_mark_end(&to[num_elem - 1]);
out:
	अगर (rc)
		iov_iter_revert(from, size - *size_used);
	*size_used = size;
	*pages_used = num_elem;

	वापस rc;
पूर्ण

/* This function decrypts the input skb पूर्णांकo either out_iov or in out_sg
 * or in skb buffers itself. The input parameter 'zc' indicates अगर
 * zero-copy mode needs to be tried or not. With zero-copy mode, either
 * out_iov or out_sg must be non-शून्य. In हाल both out_iov and out_sg are
 * शून्य, then the decryption happens inside skb buffers itself, i.e.
 * zero-copy माला_लो disabled and 'zc' is updated.
 */

अटल पूर्णांक decrypt_पूर्णांकernal(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा iov_iter *out_iov,
			    काष्ठा scatterlist *out_sg,
			    पूर्णांक *chunk, bool *zc, bool async)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा strp_msg *rxm = strp_msg(skb);
	पूर्णांक n_sgin, n_sgout, nsg, mem_size, aead_size, err, pages = 0;
	काष्ठा aead_request *aead_req;
	काष्ठा sk_buff *unused;
	u8 *aad, *iv, *mem = शून्य;
	काष्ठा scatterlist *sgin = शून्य;
	काष्ठा scatterlist *sgout = शून्य;
	स्थिर पूर्णांक data_len = rxm->full_len - prot->overhead_size +
			     prot->tail_size;
	पूर्णांक iv_offset = 0;

	अगर (*zc && (out_iov || out_sg)) अणु
		अगर (out_iov)
			n_sgout = iov_iter_npages(out_iov, पूर्णांक_उच्च) + 1;
		अन्यथा
			n_sgout = sg_nents(out_sg);
		n_sgin = skb_nsg(skb, rxm->offset + prot->prepend_size,
				 rxm->full_len - prot->prepend_size);
	पूर्ण अन्यथा अणु
		n_sgout = 0;
		*zc = false;
		n_sgin = skb_cow_data(skb, 0, &unused);
	पूर्ण

	अगर (n_sgin < 1)
		वापस -EBADMSG;

	/* Increment to accommodate AAD */
	n_sgin = n_sgin + 1;

	nsg = n_sgin + n_sgout;

	aead_size = माप(*aead_req) + crypto_aead_reqsize(ctx->aead_recv);
	mem_size = aead_size + (nsg * माप(काष्ठा scatterlist));
	mem_size = mem_size + prot->aad_size;
	mem_size = mem_size + crypto_aead_ivsize(ctx->aead_recv);

	/* Allocate a single block of memory which contains
	 * aead_req || sgin[] || sgout[] || aad || iv.
	 * This order achieves correct alignment क्रम aead_req, sgin, sgout.
	 */
	mem = kदो_स्मृति(mem_size, sk->sk_allocation);
	अगर (!mem)
		वापस -ENOMEM;

	/* Segment the allocated memory */
	aead_req = (काष्ठा aead_request *)mem;
	sgin = (काष्ठा scatterlist *)(mem + aead_size);
	sgout = sgin + n_sgin;
	aad = (u8 *)(sgout + n_sgout);
	iv = aad + prot->aad_size;

	/* For CCM based ciphers, first byte of nonce+iv is always '2' */
	अगर (prot->cipher_type == TLS_CIPHER_AES_CCM_128) अणु
		iv[0] = 2;
		iv_offset = 1;
	पूर्ण

	/* Prepare IV */
	err = skb_copy_bits(skb, rxm->offset + TLS_HEADER_SIZE,
			    iv + iv_offset + prot->salt_size,
			    prot->iv_size);
	अगर (err < 0) अणु
		kमुक्त(mem);
		वापस err;
	पूर्ण
	अगर (prot->version == TLS_1_3_VERSION ||
	    prot->cipher_type == TLS_CIPHER_CHACHA20_POLY1305)
		स_नकल(iv + iv_offset, tls_ctx->rx.iv,
		       crypto_aead_ivsize(ctx->aead_recv));
	अन्यथा
		स_नकल(iv + iv_offset, tls_ctx->rx.iv, prot->salt_size);

	xor_iv_with_seq(prot, iv, tls_ctx->rx.rec_seq);

	/* Prepare AAD */
	tls_make_aad(aad, rxm->full_len - prot->overhead_size +
		     prot->tail_size,
		     tls_ctx->rx.rec_seq, ctx->control, prot);

	/* Prepare sgin */
	sg_init_table(sgin, n_sgin);
	sg_set_buf(&sgin[0], aad, prot->aad_size);
	err = skb_to_sgvec(skb, &sgin[1],
			   rxm->offset + prot->prepend_size,
			   rxm->full_len - prot->prepend_size);
	अगर (err < 0) अणु
		kमुक्त(mem);
		वापस err;
	पूर्ण

	अगर (n_sgout) अणु
		अगर (out_iov) अणु
			sg_init_table(sgout, n_sgout);
			sg_set_buf(&sgout[0], aad, prot->aad_size);

			*chunk = 0;
			err = tls_setup_from_iter(sk, out_iov, data_len,
						  &pages, chunk, &sgout[1],
						  (n_sgout - 1));
			अगर (err < 0)
				जाओ fallback_to_reg_recv;
		पूर्ण अन्यथा अगर (out_sg) अणु
			स_नकल(sgout, out_sg, n_sgout * माप(*sgout));
		पूर्ण अन्यथा अणु
			जाओ fallback_to_reg_recv;
		पूर्ण
	पूर्ण अन्यथा अणु
fallback_to_reg_recv:
		sgout = sgin;
		pages = 0;
		*chunk = data_len;
		*zc = false;
	पूर्ण

	/* Prepare and submit AEAD request */
	err = tls_करो_decryption(sk, skb, sgin, sgout, iv,
				data_len, aead_req, async);
	अगर (err == -EINPROGRESS)
		वापस err;

	/* Release the pages in हाल iov was mapped to pages */
	क्रम (; pages > 0; pages--)
		put_page(sg_page(&sgout[pages]));

	kमुक्त(mem);
	वापस err;
पूर्ण

अटल पूर्णांक decrypt_skb_update(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			      काष्ठा iov_iter *dest, पूर्णांक *chunk, bool *zc,
			      bool async)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा strp_msg *rxm = strp_msg(skb);
	पूर्णांक pad, err = 0;

	अगर (!ctx->decrypted) अणु
		अगर (tls_ctx->rx_conf == TLS_HW) अणु
			err = tls_device_decrypted(sk, tls_ctx, skb, rxm);
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* Still not decrypted after tls_device */
		अगर (!ctx->decrypted) अणु
			err = decrypt_पूर्णांकernal(sk, skb, dest, शून्य, chunk, zc,
					       async);
			अगर (err < 0) अणु
				अगर (err == -EINPROGRESS)
					tls_advance_record_sn(sk, prot,
							      &tls_ctx->rx);
				अन्यथा अगर (err == -EBADMSG)
					TLS_INC_STATS(sock_net(sk),
						      LINUX_MIB_TLSDECRYPTERROR);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अणु
			*zc = false;
		पूर्ण

		pad = padding_length(ctx, prot, skb);
		अगर (pad < 0)
			वापस pad;

		rxm->full_len -= pad;
		rxm->offset += prot->prepend_size;
		rxm->full_len -= prot->overhead_size;
		tls_advance_record_sn(sk, prot, &tls_ctx->rx);
		ctx->decrypted = 1;
		ctx->saved_data_पढ़ोy(sk);
	पूर्ण अन्यथा अणु
		*zc = false;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक decrypt_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		काष्ठा scatterlist *sgout)
अणु
	bool zc = true;
	पूर्णांक chunk;

	वापस decrypt_पूर्णांकernal(sk, skb, शून्य, sgout, &chunk, &zc, false);
पूर्ण

अटल bool tls_sw_advance_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	अगर (skb) अणु
		काष्ठा strp_msg *rxm = strp_msg(skb);

		अगर (len < rxm->full_len) अणु
			rxm->offset += len;
			rxm->full_len -= len;
			वापस false;
		पूर्ण
		consume_skb(skb);
	पूर्ण

	/* Finished with message */
	ctx->recv_pkt = शून्य;
	__strp_unछोड़ो(&ctx->strp);

	वापस true;
पूर्ण

/* This function traverses the rx_list in tls receive context to copies the
 * decrypted records पूर्णांकo the buffer provided by caller zero copy is not
 * true. Further, the records are हटाओd from the rx_list अगर it is not a peek
 * हाल and the record has been consumed completely.
 */
अटल पूर्णांक process_rx_list(काष्ठा tls_sw_context_rx *ctx,
			   काष्ठा msghdr *msg,
			   u8 *control,
			   bool *cmsg,
			   माप_प्रकार skip,
			   माप_प्रकार len,
			   bool zc,
			   bool is_peek)
अणु
	काष्ठा sk_buff *skb = skb_peek(&ctx->rx_list);
	u8 ctrl = *control;
	u8 msgc = *cmsg;
	काष्ठा tls_msg *tlm;
	sमाप_प्रकार copied = 0;

	/* Set the record type in 'control' if caller didn't pass it */
	अगर (!ctrl && skb) अणु
		tlm = tls_msg(skb);
		ctrl = tlm->control;
	पूर्ण

	जबतक (skip && skb) अणु
		काष्ठा strp_msg *rxm = strp_msg(skb);
		tlm = tls_msg(skb);

		/* Cannot process a record of dअगरferent type */
		अगर (ctrl != tlm->control)
			वापस 0;

		अगर (skip < rxm->full_len)
			अवरोध;

		skip = skip - rxm->full_len;
		skb = skb_peek_next(skb, &ctx->rx_list);
	पूर्ण

	जबतक (len && skb) अणु
		काष्ठा sk_buff *next_skb;
		काष्ठा strp_msg *rxm = strp_msg(skb);
		पूर्णांक chunk = min_t(अचिन्हित पूर्णांक, rxm->full_len - skip, len);

		tlm = tls_msg(skb);

		/* Cannot process a record of dअगरferent type */
		अगर (ctrl != tlm->control)
			वापस 0;

		/* Set record type अगर not alपढ़ोy करोne. For a non-data record,
		 * करो not proceed अगर record type could not be copied.
		 */
		अगर (!msgc) अणु
			पूर्णांक cerr = put_cmsg(msg, SOL_TLS, TLS_GET_RECORD_TYPE,
					    माप(ctrl), &ctrl);
			msgc = true;
			अगर (ctrl != TLS_RECORD_TYPE_DATA) अणु
				अगर (cerr || msg->msg_flags & MSG_CTRUNC)
					वापस -EIO;

				*cmsg = msgc;
			पूर्ण
		पूर्ण

		अगर (!zc || (rxm->full_len - skip) > len) अणु
			पूर्णांक err = skb_copy_datagram_msg(skb, rxm->offset + skip,
						    msg, chunk);
			अगर (err < 0)
				वापस err;
		पूर्ण

		len = len - chunk;
		copied = copied + chunk;

		/* Consume the data from record अगर it is non-peek हाल*/
		अगर (!is_peek) अणु
			rxm->offset = rxm->offset + chunk;
			rxm->full_len = rxm->full_len - chunk;

			/* Return अगर there is unconsumed data in the record */
			अगर (rxm->full_len - skip)
				अवरोध;
		पूर्ण

		/* The reमुख्यing skip-bytes must lie in 1st record in rx_list.
		 * So from the 2nd record, 'skip' should be 0.
		 */
		skip = 0;

		अगर (msg)
			msg->msg_flags |= MSG_EOR;

		next_skb = skb_peek_next(skb, &ctx->rx_list);

		अगर (!is_peek) अणु
			skb_unlink(skb, &ctx->rx_list);
			consume_skb(skb);
		पूर्ण

		skb = next_skb;
	पूर्ण

	*control = ctrl;
	वापस copied;
पूर्ण

पूर्णांक tls_sw_recvmsg(काष्ठा sock *sk,
		   काष्ठा msghdr *msg,
		   माप_प्रकार len,
		   पूर्णांक nonblock,
		   पूर्णांक flags,
		   पूर्णांक *addr_len)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा sk_psock *psock;
	अचिन्हित अक्षर control = 0;
	sमाप_प्रकार decrypted = 0;
	काष्ठा strp_msg *rxm;
	काष्ठा tls_msg *tlm;
	काष्ठा sk_buff *skb;
	sमाप_प्रकार copied = 0;
	bool cmsg = false;
	पूर्णांक target, err = 0;
	दीर्घ समयo;
	bool is_kvec = iov_iter_is_kvec(&msg->msg_iter);
	bool is_peek = flags & MSG_PEEK;
	bool bpf_strp_enabled;
	पूर्णांक num_async = 0;
	पूर्णांक pending;

	flags |= nonblock;

	अगर (unlikely(flags & MSG_ERRQUEUE))
		वापस sock_recv_errqueue(sk, msg, len, SOL_IP, IP_RECVERR);

	psock = sk_psock_get(sk);
	lock_sock(sk);
	bpf_strp_enabled = sk_psock_strp_enabled(psock);

	/* Process pending decrypted records. It must be non-zero-copy */
	err = process_rx_list(ctx, msg, &control, &cmsg, 0, len, false,
			      is_peek);
	अगर (err < 0) अणु
		tls_err_पात(sk, err);
		जाओ end;
	पूर्ण अन्यथा अणु
		copied = err;
	पूर्ण

	अगर (len <= copied)
		जाओ recv_end;

	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);
	len = len - copied;
	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	जबतक (len && (decrypted + copied < target || ctx->recv_pkt)) अणु
		bool retain_skb = false;
		bool zc = false;
		पूर्णांक to_decrypt;
		पूर्णांक chunk = 0;
		bool async_capable;
		bool async = false;

		skb = tls_रुको_data(sk, psock, flags & MSG_DONTWAIT, समयo, &err);
		अगर (!skb) अणु
			अगर (psock) अणु
				पूर्णांक ret = sk_msg_recvmsg(sk, psock, msg, len,
							 flags);

				अगर (ret > 0) अणु
					decrypted += ret;
					len -= ret;
					जारी;
				पूर्ण
			पूर्ण
			जाओ recv_end;
		पूर्ण अन्यथा अणु
			tlm = tls_msg(skb);
			अगर (prot->version == TLS_1_3_VERSION)
				tlm->control = 0;
			अन्यथा
				tlm->control = ctx->control;
		पूर्ण

		rxm = strp_msg(skb);

		to_decrypt = rxm->full_len - prot->overhead_size;

		अगर (to_decrypt <= len && !is_kvec && !is_peek &&
		    ctx->control == TLS_RECORD_TYPE_DATA &&
		    prot->version != TLS_1_3_VERSION &&
		    !bpf_strp_enabled)
			zc = true;

		/* Do not use async mode अगर record is non-data */
		अगर (ctx->control == TLS_RECORD_TYPE_DATA && !bpf_strp_enabled)
			async_capable = ctx->async_capable;
		अन्यथा
			async_capable = false;

		err = decrypt_skb_update(sk, skb, &msg->msg_iter,
					 &chunk, &zc, async_capable);
		अगर (err < 0 && err != -EINPROGRESS) अणु
			tls_err_पात(sk, EBADMSG);
			जाओ recv_end;
		पूर्ण

		अगर (err == -EINPROGRESS) अणु
			async = true;
			num_async++;
		पूर्ण अन्यथा अगर (prot->version == TLS_1_3_VERSION) अणु
			tlm->control = ctx->control;
		पूर्ण

		/* If the type of records being processed is not known yet,
		 * set it to record type just dequeued. If it is alपढ़ोy known,
		 * but करोes not match the record type just dequeued, go to end.
		 * We always get record type here since क्रम tls1.2, record type
		 * is known just after record is dequeued from stream parser.
		 * For tls1.3, we disable async.
		 */

		अगर (!control)
			control = tlm->control;
		अन्यथा अगर (control != tlm->control)
			जाओ recv_end;

		अगर (!cmsg) अणु
			पूर्णांक cerr;

			cerr = put_cmsg(msg, SOL_TLS, TLS_GET_RECORD_TYPE,
					माप(control), &control);
			cmsg = true;
			अगर (control != TLS_RECORD_TYPE_DATA) अणु
				अगर (cerr || msg->msg_flags & MSG_CTRUNC) अणु
					err = -EIO;
					जाओ recv_end;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (async)
			जाओ pick_next_record;

		अगर (!zc) अणु
			अगर (bpf_strp_enabled) अणु
				err = sk_psock_tls_strp_पढ़ो(psock, skb);
				अगर (err != __SK_PASS) अणु
					rxm->offset = rxm->offset + rxm->full_len;
					rxm->full_len = 0;
					अगर (err == __SK_DROP)
						consume_skb(skb);
					ctx->recv_pkt = शून्य;
					__strp_unछोड़ो(&ctx->strp);
					जारी;
				पूर्ण
			पूर्ण

			अगर (rxm->full_len > len) अणु
				retain_skb = true;
				chunk = len;
			पूर्ण अन्यथा अणु
				chunk = rxm->full_len;
			पूर्ण

			err = skb_copy_datagram_msg(skb, rxm->offset,
						    msg, chunk);
			अगर (err < 0)
				जाओ recv_end;

			अगर (!is_peek) अणु
				rxm->offset = rxm->offset + chunk;
				rxm->full_len = rxm->full_len - chunk;
			पूर्ण
		पूर्ण

pick_next_record:
		अगर (chunk > len)
			chunk = len;

		decrypted += chunk;
		len -= chunk;

		/* For async or peek हाल, queue the current skb */
		अगर (async || is_peek || retain_skb) अणु
			skb_queue_tail(&ctx->rx_list, skb);
			skb = शून्य;
		पूर्ण

		अगर (tls_sw_advance_skb(sk, skb, chunk)) अणु
			/* Return full control message to
			 * userspace beक्रमe trying to parse
			 * another message type
			 */
			msg->msg_flags |= MSG_EOR;
			अगर (control != TLS_RECORD_TYPE_DATA)
				जाओ recv_end;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

recv_end:
	अगर (num_async) अणु
		/* Wait क्रम all previously submitted records to be decrypted */
		spin_lock_bh(&ctx->decrypt_compl_lock);
		ctx->async_notअगरy = true;
		pending = atomic_पढ़ो(&ctx->decrypt_pending);
		spin_unlock_bh(&ctx->decrypt_compl_lock);
		अगर (pending) अणु
			err = crypto_रुको_req(-EINPROGRESS, &ctx->async_रुको);
			अगर (err) अणु
				/* one of async decrypt failed */
				tls_err_पात(sk, err);
				copied = 0;
				decrypted = 0;
				जाओ end;
			पूर्ण
		पूर्ण अन्यथा अणु
			reinit_completion(&ctx->async_रुको.completion);
		पूर्ण

		/* There can be no concurrent accesses, since we have no
		 * pending decrypt operations
		 */
		WRITE_ONCE(ctx->async_notअगरy, false);

		/* Drain records from the rx_list & copy अगर required */
		अगर (is_peek || is_kvec)
			err = process_rx_list(ctx, msg, &control, &cmsg, copied,
					      decrypted, false, is_peek);
		अन्यथा
			err = process_rx_list(ctx, msg, &control, &cmsg, 0,
					      decrypted, true, is_peek);
		अगर (err < 0) अणु
			tls_err_पात(sk, err);
			copied = 0;
			जाओ end;
		पूर्ण
	पूर्ण

	copied += decrypted;

end:
	release_sock(sk);
	अगर (psock)
		sk_psock_put(sk, psock);
	वापस copied ? : err;
पूर्ण

sमाप_प्रकार tls_sw_splice_पढ़ो(काष्ठा socket *sock,  loff_t *ppos,
			   काष्ठा pipe_inode_info *pipe,
			   माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sock->sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा strp_msg *rxm = शून्य;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	sमाप_प्रकार copied = 0;
	पूर्णांक err = 0;
	दीर्घ समयo;
	पूर्णांक chunk;
	bool zc = false;

	lock_sock(sk);

	समयo = sock_rcvसमयo(sk, flags & SPLICE_F_NONBLOCK);

	skb = tls_रुको_data(sk, शून्य, flags & SPLICE_F_NONBLOCK, समयo, &err);
	अगर (!skb)
		जाओ splice_पढ़ो_end;

	अगर (!ctx->decrypted) अणु
		err = decrypt_skb_update(sk, skb, शून्य, &chunk, &zc, false);

		/* splice करोes not support पढ़ोing control messages */
		अगर (ctx->control != TLS_RECORD_TYPE_DATA) अणु
			err = -EINVAL;
			जाओ splice_पढ़ो_end;
		पूर्ण

		अगर (err < 0) अणु
			tls_err_पात(sk, EBADMSG);
			जाओ splice_पढ़ो_end;
		पूर्ण
		ctx->decrypted = 1;
	पूर्ण
	rxm = strp_msg(skb);

	chunk = min_t(अचिन्हित पूर्णांक, rxm->full_len, len);
	copied = skb_splice_bits(skb, sk, rxm->offset, pipe, chunk, flags);
	अगर (copied < 0)
		जाओ splice_पढ़ो_end;

	अगर (likely(!(flags & MSG_PEEK)))
		tls_sw_advance_skb(sk, skb, copied);

splice_पढ़ो_end:
	release_sock(sk);
	वापस copied ? : err;
पूर्ण

bool tls_sw_stream_पढ़ो(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	bool ingress_empty = true;
	काष्ठा sk_psock *psock;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (psock)
		ingress_empty = list_empty(&psock->ingress_msg);
	rcu_पढ़ो_unlock();

	वापस !ingress_empty || ctx->recv_pkt ||
		!skb_queue_empty(&ctx->rx_list);
पूर्ण

अटल पूर्णांक tls_पढ़ो_size(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(strp->sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	अक्षर header[TLS_HEADER_SIZE + MAX_IV_SIZE];
	काष्ठा strp_msg *rxm = strp_msg(skb);
	माप_प्रकार cipher_overhead;
	माप_प्रकार data_len = 0;
	पूर्णांक ret;

	/* Verअगरy that we have a full TLS header, or रुको क्रम more data */
	अगर (rxm->offset + prot->prepend_size > skb->len)
		वापस 0;

	/* Sanity-check size of on-stack buffer. */
	अगर (WARN_ON(prot->prepend_size > माप(header))) अणु
		ret = -EINVAL;
		जाओ पढ़ो_failure;
	पूर्ण

	/* Linearize header to local buffer */
	ret = skb_copy_bits(skb, rxm->offset, header, prot->prepend_size);

	अगर (ret < 0)
		जाओ पढ़ो_failure;

	ctx->control = header[0];

	data_len = ((header[4] & 0xFF) | (header[3] << 8));

	cipher_overhead = prot->tag_size;
	अगर (prot->version != TLS_1_3_VERSION &&
	    prot->cipher_type != TLS_CIPHER_CHACHA20_POLY1305)
		cipher_overhead += prot->iv_size;

	अगर (data_len > TLS_MAX_PAYLOAD_SIZE + cipher_overhead +
	    prot->tail_size) अणु
		ret = -EMSGSIZE;
		जाओ पढ़ो_failure;
	पूर्ण
	अगर (data_len < cipher_overhead) अणु
		ret = -EBADMSG;
		जाओ पढ़ो_failure;
	पूर्ण

	/* Note that both TLS1.3 and TLS1.2 use TLS_1_2 version here */
	अगर (header[1] != TLS_1_2_VERSION_MINOR ||
	    header[2] != TLS_1_2_VERSION_MAJOR) अणु
		ret = -EINVAL;
		जाओ पढ़ो_failure;
	पूर्ण

	tls_device_rx_resync_new_rec(strp->sk, data_len + TLS_HEADER_SIZE,
				     TCP_SKB_CB(skb)->seq + rxm->offset);
	वापस data_len + TLS_HEADER_SIZE;

पढ़ो_failure:
	tls_err_पात(strp->sk, ret);

	वापस ret;
पूर्ण

अटल व्योम tls_queue(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(strp->sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	ctx->decrypted = 0;

	ctx->recv_pkt = skb;
	strp_छोड़ो(strp);

	ctx->saved_data_पढ़ोy(strp->sk);
पूर्ण

अटल व्योम tls_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	काष्ठा sk_psock *psock;

	strp_data_पढ़ोy(&ctx->strp);

	psock = sk_psock_get(sk);
	अगर (psock) अणु
		अगर (!list_empty(&psock->ingress_msg))
			ctx->saved_data_पढ़ोy(sk);
		sk_psock_put(sk, psock);
	पूर्ण
पूर्ण

व्योम tls_sw_cancel_work_tx(काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);

	set_bit(BIT_TX_CLOSING, &ctx->tx_biपंचांगask);
	set_bit(BIT_TX_SCHEDULED, &ctx->tx_biपंचांगask);
	cancel_delayed_work_sync(&ctx->tx_work.work);
पूर्ण

व्योम tls_sw_release_resources_tx(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	काष्ठा tls_rec *rec, *पंचांगp;
	पूर्णांक pending;

	/* Wait क्रम any pending async encryptions to complete */
	spin_lock_bh(&ctx->encrypt_compl_lock);
	ctx->async_notअगरy = true;
	pending = atomic_पढ़ो(&ctx->encrypt_pending);
	spin_unlock_bh(&ctx->encrypt_compl_lock);

	अगर (pending)
		crypto_रुको_req(-EINPROGRESS, &ctx->async_रुको);

	tls_tx_records(sk, -1);

	/* Free up un-sent records in tx_list. First, मुक्त
	 * the partially sent record अगर any at head of tx_list.
	 */
	अगर (tls_ctx->partially_sent_record) अणु
		tls_मुक्त_partial_record(sk, tls_ctx);
		rec = list_first_entry(&ctx->tx_list,
				       काष्ठा tls_rec, list);
		list_del(&rec->list);
		sk_msg_मुक्त(sk, &rec->msg_plaपूर्णांकext);
		kमुक्त(rec);
	पूर्ण

	list_क्रम_each_entry_safe(rec, पंचांगp, &ctx->tx_list, list) अणु
		list_del(&rec->list);
		sk_msg_मुक्त(sk, &rec->msg_encrypted);
		sk_msg_मुक्त(sk, &rec->msg_plaपूर्णांकext);
		kमुक्त(rec);
	पूर्ण

	crypto_मुक्त_aead(ctx->aead_send);
	tls_मुक्त_खोलो_rec(sk);
पूर्ण

व्योम tls_sw_मुक्त_ctx_tx(काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);

	kमुक्त(ctx);
पूर्ण

व्योम tls_sw_release_resources_rx(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	kमुक्त(tls_ctx->rx.rec_seq);
	kमुक्त(tls_ctx->rx.iv);

	अगर (ctx->aead_recv) अणु
		kमुक्त_skb(ctx->recv_pkt);
		ctx->recv_pkt = शून्य;
		skb_queue_purge(&ctx->rx_list);
		crypto_मुक्त_aead(ctx->aead_recv);
		strp_stop(&ctx->strp);
		/* If tls_sw_strparser_arm() was not called (cleanup paths)
		 * we still want to strp_stop(), but sk->sk_data_पढ़ोy was
		 * never swapped.
		 */
		अगर (ctx->saved_data_पढ़ोy) अणु
			ग_लिखो_lock_bh(&sk->sk_callback_lock);
			sk->sk_data_पढ़ोy = ctx->saved_data_पढ़ोy;
			ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		पूर्ण
	पूर्ण
पूर्ण

व्योम tls_sw_strparser_करोne(काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	strp_करोne(&ctx->strp);
पूर्ण

व्योम tls_sw_मुक्त_ctx_rx(काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	kमुक्त(ctx);
पूर्ण

व्योम tls_sw_मुक्त_resources_rx(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);

	tls_sw_release_resources_rx(sk);
	tls_sw_मुक्त_ctx_rx(tls_ctx);
पूर्ण

/* The work handler to transmitt the encrypted records in tx_list */
अटल व्योम tx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा tx_work *tx_work = container_of(delayed_work,
					       काष्ठा tx_work, work);
	काष्ठा sock *sk = tx_work->sk;
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_sw_context_tx *ctx;

	अगर (unlikely(!tls_ctx))
		वापस;

	ctx = tls_sw_ctx_tx(tls_ctx);
	अगर (test_bit(BIT_TX_CLOSING, &ctx->tx_biपंचांगask))
		वापस;

	अगर (!test_and_clear_bit(BIT_TX_SCHEDULED, &ctx->tx_biपंचांगask))
		वापस;
	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);
	tls_tx_records(sk, -1);
	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
पूर्ण

व्योम tls_sw_ग_लिखो_space(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	काष्ठा tls_sw_context_tx *tx_ctx = tls_sw_ctx_tx(ctx);

	/* Schedule the transmission अगर tx list is पढ़ोy */
	अगर (is_tx_पढ़ोy(tx_ctx) &&
	    !test_and_set_bit(BIT_TX_SCHEDULED, &tx_ctx->tx_biपंचांगask))
		schedule_delayed_work(&tx_ctx->tx_work.work, 0);
पूर्ण

व्योम tls_sw_strparser_arm(काष्ठा sock *sk, काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा tls_sw_context_rx *rx_ctx = tls_sw_ctx_rx(tls_ctx);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	rx_ctx->saved_data_पढ़ोy = sk->sk_data_पढ़ोy;
	sk->sk_data_पढ़ोy = tls_data_पढ़ोy;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	strp_check_rcv(&rx_ctx->strp);
पूर्ण

पूर्णांक tls_set_sw_offload(काष्ठा sock *sk, काष्ठा tls_context *ctx, पूर्णांक tx)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_crypto_info *crypto_info;
	काष्ठा tls12_crypto_info_aes_gcm_128 *gcm_128_info;
	काष्ठा tls12_crypto_info_aes_gcm_256 *gcm_256_info;
	काष्ठा tls12_crypto_info_aes_ccm_128 *ccm_128_info;
	काष्ठा tls12_crypto_info_chacha20_poly1305 *chacha20_poly1305_info;
	काष्ठा tls_sw_context_tx *sw_ctx_tx = शून्य;
	काष्ठा tls_sw_context_rx *sw_ctx_rx = शून्य;
	काष्ठा cipher_context *cctx;
	काष्ठा crypto_aead **aead;
	काष्ठा strp_callbacks cb;
	u16 nonce_size, tag_size, iv_size, rec_seq_size, salt_size;
	काष्ठा crypto_tfm *tfm;
	अक्षर *iv, *rec_seq, *key, *salt, *cipher_name;
	माप_प्रकार keysize;
	पूर्णांक rc = 0;

	अगर (!ctx) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (tx) अणु
		अगर (!ctx->priv_ctx_tx) अणु
			sw_ctx_tx = kzalloc(माप(*sw_ctx_tx), GFP_KERNEL);
			अगर (!sw_ctx_tx) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			ctx->priv_ctx_tx = sw_ctx_tx;
		पूर्ण अन्यथा अणु
			sw_ctx_tx =
				(काष्ठा tls_sw_context_tx *)ctx->priv_ctx_tx;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!ctx->priv_ctx_rx) अणु
			sw_ctx_rx = kzalloc(माप(*sw_ctx_rx), GFP_KERNEL);
			अगर (!sw_ctx_rx) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			ctx->priv_ctx_rx = sw_ctx_rx;
		पूर्ण अन्यथा अणु
			sw_ctx_rx =
				(काष्ठा tls_sw_context_rx *)ctx->priv_ctx_rx;
		पूर्ण
	पूर्ण

	अगर (tx) अणु
		crypto_init_रुको(&sw_ctx_tx->async_रुको);
		spin_lock_init(&sw_ctx_tx->encrypt_compl_lock);
		crypto_info = &ctx->crypto_send.info;
		cctx = &ctx->tx;
		aead = &sw_ctx_tx->aead_send;
		INIT_LIST_HEAD(&sw_ctx_tx->tx_list);
		INIT_DELAYED_WORK(&sw_ctx_tx->tx_work.work, tx_work_handler);
		sw_ctx_tx->tx_work.sk = sk;
	पूर्ण अन्यथा अणु
		crypto_init_रुको(&sw_ctx_rx->async_रुको);
		spin_lock_init(&sw_ctx_rx->decrypt_compl_lock);
		crypto_info = &ctx->crypto_recv.info;
		cctx = &ctx->rx;
		skb_queue_head_init(&sw_ctx_rx->rx_list);
		aead = &sw_ctx_rx->aead_recv;
	पूर्ण

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128: अणु
		nonce_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		tag_size = TLS_CIPHER_AES_GCM_128_TAG_SIZE;
		iv_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		iv = ((काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info)->iv;
		rec_seq_size = TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE;
		rec_seq =
		 ((काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info)->rec_seq;
		gcm_128_info =
			(काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info;
		keysize = TLS_CIPHER_AES_GCM_128_KEY_SIZE;
		key = gcm_128_info->key;
		salt = gcm_128_info->salt;
		salt_size = TLS_CIPHER_AES_GCM_128_SALT_SIZE;
		cipher_name = "gcm(aes)";
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_GCM_256: अणु
		nonce_size = TLS_CIPHER_AES_GCM_256_IV_SIZE;
		tag_size = TLS_CIPHER_AES_GCM_256_TAG_SIZE;
		iv_size = TLS_CIPHER_AES_GCM_256_IV_SIZE;
		iv = ((काष्ठा tls12_crypto_info_aes_gcm_256 *)crypto_info)->iv;
		rec_seq_size = TLS_CIPHER_AES_GCM_256_REC_SEQ_SIZE;
		rec_seq =
		 ((काष्ठा tls12_crypto_info_aes_gcm_256 *)crypto_info)->rec_seq;
		gcm_256_info =
			(काष्ठा tls12_crypto_info_aes_gcm_256 *)crypto_info;
		keysize = TLS_CIPHER_AES_GCM_256_KEY_SIZE;
		key = gcm_256_info->key;
		salt = gcm_256_info->salt;
		salt_size = TLS_CIPHER_AES_GCM_256_SALT_SIZE;
		cipher_name = "gcm(aes)";
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_CCM_128: अणु
		nonce_size = TLS_CIPHER_AES_CCM_128_IV_SIZE;
		tag_size = TLS_CIPHER_AES_CCM_128_TAG_SIZE;
		iv_size = TLS_CIPHER_AES_CCM_128_IV_SIZE;
		iv = ((काष्ठा tls12_crypto_info_aes_ccm_128 *)crypto_info)->iv;
		rec_seq_size = TLS_CIPHER_AES_CCM_128_REC_SEQ_SIZE;
		rec_seq =
		((काष्ठा tls12_crypto_info_aes_ccm_128 *)crypto_info)->rec_seq;
		ccm_128_info =
		(काष्ठा tls12_crypto_info_aes_ccm_128 *)crypto_info;
		keysize = TLS_CIPHER_AES_CCM_128_KEY_SIZE;
		key = ccm_128_info->key;
		salt = ccm_128_info->salt;
		salt_size = TLS_CIPHER_AES_CCM_128_SALT_SIZE;
		cipher_name = "ccm(aes)";
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_CHACHA20_POLY1305: अणु
		chacha20_poly1305_info = (व्योम *)crypto_info;
		nonce_size = 0;
		tag_size = TLS_CIPHER_CHACHA20_POLY1305_TAG_SIZE;
		iv_size = TLS_CIPHER_CHACHA20_POLY1305_IV_SIZE;
		iv = chacha20_poly1305_info->iv;
		rec_seq_size = TLS_CIPHER_CHACHA20_POLY1305_REC_SEQ_SIZE;
		rec_seq = chacha20_poly1305_info->rec_seq;
		keysize = TLS_CIPHER_CHACHA20_POLY1305_KEY_SIZE;
		key = chacha20_poly1305_info->key;
		salt = chacha20_poly1305_info->salt;
		salt_size = TLS_CIPHER_CHACHA20_POLY1305_SALT_SIZE;
		cipher_name = "rfc7539(chacha20,poly1305)";
		अवरोध;
	पूर्ण
	शेष:
		rc = -EINVAL;
		जाओ मुक्त_priv;
	पूर्ण

	/* Sanity-check the sizes क्रम stack allocations. */
	अगर (iv_size > MAX_IV_SIZE || nonce_size > MAX_IV_SIZE ||
	    rec_seq_size > TLS_MAX_REC_SEQ_SIZE) अणु
		rc = -EINVAL;
		जाओ मुक्त_priv;
	पूर्ण

	अगर (crypto_info->version == TLS_1_3_VERSION) अणु
		nonce_size = 0;
		prot->aad_size = TLS_HEADER_SIZE;
		prot->tail_size = 1;
	पूर्ण अन्यथा अणु
		prot->aad_size = TLS_AAD_SPACE_SIZE;
		prot->tail_size = 0;
	पूर्ण

	prot->version = crypto_info->version;
	prot->cipher_type = crypto_info->cipher_type;
	prot->prepend_size = TLS_HEADER_SIZE + nonce_size;
	prot->tag_size = tag_size;
	prot->overhead_size = prot->prepend_size +
			      prot->tag_size + prot->tail_size;
	prot->iv_size = iv_size;
	prot->salt_size = salt_size;
	cctx->iv = kदो_स्मृति(iv_size + salt_size, GFP_KERNEL);
	अगर (!cctx->iv) अणु
		rc = -ENOMEM;
		जाओ मुक्त_priv;
	पूर्ण
	/* Note: 128 & 256 bit salt are the same size */
	prot->rec_seq_size = rec_seq_size;
	स_नकल(cctx->iv, salt, salt_size);
	स_नकल(cctx->iv + salt_size, iv, iv_size);
	cctx->rec_seq = kmemdup(rec_seq, rec_seq_size, GFP_KERNEL);
	अगर (!cctx->rec_seq) अणु
		rc = -ENOMEM;
		जाओ मुक्त_iv;
	पूर्ण

	अगर (!*aead) अणु
		*aead = crypto_alloc_aead(cipher_name, 0, 0);
		अगर (IS_ERR(*aead)) अणु
			rc = PTR_ERR(*aead);
			*aead = शून्य;
			जाओ मुक्त_rec_seq;
		पूर्ण
	पूर्ण

	ctx->push_pending_record = tls_sw_push_pending_record;

	rc = crypto_aead_setkey(*aead, key, keysize);

	अगर (rc)
		जाओ मुक्त_aead;

	rc = crypto_aead_setauthsize(*aead, prot->tag_size);
	अगर (rc)
		जाओ मुक्त_aead;

	अगर (sw_ctx_rx) अणु
		tfm = crypto_aead_tfm(sw_ctx_rx->aead_recv);

		अगर (crypto_info->version == TLS_1_3_VERSION)
			sw_ctx_rx->async_capable = 0;
		अन्यथा
			sw_ctx_rx->async_capable =
				!!(tfm->__crt_alg->cra_flags &
				   CRYPTO_ALG_ASYNC);

		/* Set up strparser */
		स_रखो(&cb, 0, माप(cb));
		cb.rcv_msg = tls_queue;
		cb.parse_msg = tls_पढ़ो_size;

		strp_init(&sw_ctx_rx->strp, sk, &cb);
	पूर्ण

	जाओ out;

मुक्त_aead:
	crypto_मुक्त_aead(*aead);
	*aead = शून्य;
मुक्त_rec_seq:
	kमुक्त(cctx->rec_seq);
	cctx->rec_seq = शून्य;
मुक्त_iv:
	kमुक्त(cctx->iv);
	cctx->iv = शून्य;
मुक्त_priv:
	अगर (tx) अणु
		kमुक्त(ctx->priv_ctx_tx);
		ctx->priv_ctx_tx = शून्य;
	पूर्ण अन्यथा अणु
		kमुक्त(ctx->priv_ctx_rx);
		ctx->priv_ctx_rx = शून्य;
	पूर्ण
out:
	वापस rc;
पूर्ण
