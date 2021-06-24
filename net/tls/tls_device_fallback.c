<शैली गुरु>
/* Copyright (c) 2018, Mellanox Technologies All rights reserved.
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

#समावेश <net/tls.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <net/ip6_checksum.h>

अटल व्योम chain_to_walk(काष्ठा scatterlist *sg, काष्ठा scatter_walk *walk)
अणु
	काष्ठा scatterlist *src = walk->sg;
	पूर्णांक dअगरf = walk->offset - src->offset;

	sg_set_page(sg, sg_page(src),
		    src->length - dअगरf, walk->offset);

	scatterwalk_crypto_chain(sg, sg_next(src), 2);
पूर्ण

अटल पूर्णांक tls_enc_record(काष्ठा aead_request *aead_req,
			  काष्ठा crypto_aead *aead, अक्षर *aad,
			  अक्षर *iv, __be64 rcd_sn,
			  काष्ठा scatter_walk *in,
			  काष्ठा scatter_walk *out, पूर्णांक *in_len,
			  काष्ठा tls_prot_info *prot)
अणु
	अचिन्हित अक्षर buf[TLS_HEADER_SIZE + TLS_CIPHER_AES_GCM_128_IV_SIZE];
	काष्ठा scatterlist sg_in[3];
	काष्ठा scatterlist sg_out[3];
	u16 len;
	पूर्णांक rc;

	len = min_t(पूर्णांक, *in_len, ARRAY_SIZE(buf));

	scatterwalk_copychunks(buf, in, len, 0);
	scatterwalk_copychunks(buf, out, len, 1);

	*in_len -= len;
	अगर (!*in_len)
		वापस 0;

	scatterwalk_pageकरोne(in, 0, 1);
	scatterwalk_pageकरोne(out, 1, 1);

	len = buf[4] | (buf[3] << 8);
	len -= TLS_CIPHER_AES_GCM_128_IV_SIZE;

	tls_make_aad(aad, len - TLS_CIPHER_AES_GCM_128_TAG_SIZE,
		(अक्षर *)&rcd_sn, buf[0], prot);

	स_नकल(iv + TLS_CIPHER_AES_GCM_128_SALT_SIZE, buf + TLS_HEADER_SIZE,
	       TLS_CIPHER_AES_GCM_128_IV_SIZE);

	sg_init_table(sg_in, ARRAY_SIZE(sg_in));
	sg_init_table(sg_out, ARRAY_SIZE(sg_out));
	sg_set_buf(sg_in, aad, TLS_AAD_SPACE_SIZE);
	sg_set_buf(sg_out, aad, TLS_AAD_SPACE_SIZE);
	chain_to_walk(sg_in + 1, in);
	chain_to_walk(sg_out + 1, out);

	*in_len -= len;
	अगर (*in_len < 0) अणु
		*in_len += TLS_CIPHER_AES_GCM_128_TAG_SIZE;
		/* the input buffer करोesn't contain the entire record.
		 * trim len accordingly. The resulting authentication tag
		 * will contain garbage, but we करोn't care, so we won't
		 * include any of it in the output skb
		 * Note that we assume the output buffer length
		 * is larger then input buffer length + tag size
		 */
		अगर (*in_len < 0)
			len += *in_len;

		*in_len = 0;
	पूर्ण

	अगर (*in_len) अणु
		scatterwalk_copychunks(शून्य, in, len, 2);
		scatterwalk_pageकरोne(in, 0, 1);
		scatterwalk_copychunks(शून्य, out, len, 2);
		scatterwalk_pageकरोne(out, 1, 1);
	पूर्ण

	len -= TLS_CIPHER_AES_GCM_128_TAG_SIZE;
	aead_request_set_crypt(aead_req, sg_in, sg_out, len, iv);

	rc = crypto_aead_encrypt(aead_req);

	वापस rc;
पूर्ण

अटल व्योम tls_init_aead_request(काष्ठा aead_request *aead_req,
				  काष्ठा crypto_aead *aead)
अणु
	aead_request_set_tfm(aead_req, aead);
	aead_request_set_ad(aead_req, TLS_AAD_SPACE_SIZE);
पूर्ण

अटल काष्ठा aead_request *tls_alloc_aead_request(काष्ठा crypto_aead *aead,
						   gfp_t flags)
अणु
	अचिन्हित पूर्णांक req_size = माप(काष्ठा aead_request) +
		crypto_aead_reqsize(aead);
	काष्ठा aead_request *aead_req;

	aead_req = kzalloc(req_size, flags);
	अगर (aead_req)
		tls_init_aead_request(aead_req, aead);
	वापस aead_req;
पूर्ण

अटल पूर्णांक tls_enc_records(काष्ठा aead_request *aead_req,
			   काष्ठा crypto_aead *aead, काष्ठा scatterlist *sg_in,
			   काष्ठा scatterlist *sg_out, अक्षर *aad, अक्षर *iv,
			   u64 rcd_sn, पूर्णांक len, काष्ठा tls_prot_info *prot)
अणु
	काष्ठा scatter_walk out, in;
	पूर्णांक rc;

	scatterwalk_start(&in, sg_in);
	scatterwalk_start(&out, sg_out);

	करो अणु
		rc = tls_enc_record(aead_req, aead, aad, iv,
				    cpu_to_be64(rcd_sn), &in, &out, &len, prot);
		rcd_sn++;

	पूर्ण जबतक (rc == 0 && len);

	scatterwalk_करोne(&in, 0, 0);
	scatterwalk_करोne(&out, 1, 0);

	वापस rc;
पूर्ण

/* Can't use icsk->icsk_af_ops->send_check here because the ip addresses
 * might have been changed by NAT.
 */
अटल व्योम update_chksum(काष्ठा sk_buff *skb, पूर्णांक headln)
अणु
	काष्ठा tcphdr *th = tcp_hdr(skb);
	पूर्णांक datalen = skb->len - headln;
	स्थिर काष्ठा ipv6hdr *ipv6h;
	स्थिर काष्ठा iphdr *iph;

	/* We only changed the payload so अगर we are using partial we करोn't
	 * need to update anything.
	 */
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL))
		वापस;

	skb->ip_summed = CHECKSUM_PARTIAL;
	skb->csum_start = skb_transport_header(skb) - skb->head;
	skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);

	अगर (skb->sk->sk_family == AF_INET6) अणु
		ipv6h = ipv6_hdr(skb);
		th->check = ~csum_ipv6_magic(&ipv6h->saddr, &ipv6h->daddr,
					     datalen, IPPROTO_TCP, 0);
	पूर्ण अन्यथा अणु
		iph = ip_hdr(skb);
		th->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr, datalen,
					       IPPROTO_TCP, 0);
	पूर्ण
पूर्ण

अटल व्योम complete_skb(काष्ठा sk_buff *nskb, काष्ठा sk_buff *skb, पूर्णांक headln)
अणु
	काष्ठा sock *sk = skb->sk;
	पूर्णांक delta;

	skb_copy_header(nskb, skb);

	skb_put(nskb, skb->len);
	स_नकल(nskb->data, skb->data, headln);

	nskb->deकाष्ठाor = skb->deकाष्ठाor;
	nskb->sk = sk;
	skb->deकाष्ठाor = शून्य;
	skb->sk = शून्य;

	update_chksum(nskb, headln);

	/* sock_eमुक्त means skb must gone through skb_orphan_partial() */
	अगर (nskb->deकाष्ठाor == sock_eमुक्त)
		वापस;

	delta = nskb->truesize - skb->truesize;
	अगर (likely(delta < 0))
		WARN_ON_ONCE(refcount_sub_and_test(-delta, &sk->sk_wmem_alloc));
	अन्यथा अगर (delta)
		refcount_add(delta, &sk->sk_wmem_alloc);
पूर्ण

/* This function may be called after the user socket is alपढ़ोy
 * बंदd so make sure we करोn't use anything मुक्तd during
 * tls_sk_proto_बंद here
 */

अटल पूर्णांक fill_sg_in(काष्ठा scatterlist *sg_in,
		      काष्ठा sk_buff *skb,
		      काष्ठा tls_offload_context_tx *ctx,
		      u64 *rcd_sn,
		      s32 *sync_size,
		      पूर्णांक *resync_sgs)
अणु
	पूर्णांक tcp_payload_offset = skb_transport_offset(skb) + tcp_hdrlen(skb);
	पूर्णांक payload_len = skb->len - tcp_payload_offset;
	u32 tcp_seq = ntohl(tcp_hdr(skb)->seq);
	काष्ठा tls_record_info *record;
	अचिन्हित दीर्घ flags;
	पूर्णांक reमुख्यing;
	पूर्णांक i;

	spin_lock_irqsave(&ctx->lock, flags);
	record = tls_get_record(ctx, tcp_seq, rcd_sn);
	अगर (!record) अणु
		spin_unlock_irqrestore(&ctx->lock, flags);
		वापस -EINVAL;
	पूर्ण

	*sync_size = tcp_seq - tls_record_start_seq(record);
	अगर (*sync_size < 0) अणु
		पूर्णांक is_start_marker = tls_record_is_start_marker(record);

		spin_unlock_irqrestore(&ctx->lock, flags);
		/* This should only occur अगर the relevant record was
		 * alपढ़ोy acked. In that हाल it should be ok
		 * to drop the packet and aव्योम retransmission.
		 *
		 * There is a corner हाल where the packet contains
		 * both an acked and a non-acked record.
		 * We currently करोn't handle that हाल and rely
		 * on TCP to retranmit a packet that करोesn't contain
		 * alपढ़ोy acked payload.
		 */
		अगर (!is_start_marker)
			*sync_size = 0;
		वापस -EINVAL;
	पूर्ण

	reमुख्यing = *sync_size;
	क्रम (i = 0; reमुख्यing > 0; i++) अणु
		skb_frag_t *frag = &record->frags[i];

		__skb_frag_ref(frag);
		sg_set_page(sg_in + i, skb_frag_page(frag),
			    skb_frag_size(frag), skb_frag_off(frag));

		reमुख्यing -= skb_frag_size(frag);

		अगर (reमुख्यing < 0)
			sg_in[i].length += reमुख्यing;
	पूर्ण
	*resync_sgs = i;

	spin_unlock_irqrestore(&ctx->lock, flags);
	अगर (skb_to_sgvec(skb, &sg_in[i], tcp_payload_offset, payload_len) < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम fill_sg_out(काष्ठा scatterlist sg_out[3], व्योम *buf,
			काष्ठा tls_context *tls_ctx,
			काष्ठा sk_buff *nskb,
			पूर्णांक tcp_payload_offset,
			पूर्णांक payload_len,
			पूर्णांक sync_size,
			व्योम *dummy_buf)
अणु
	sg_set_buf(&sg_out[0], dummy_buf, sync_size);
	sg_set_buf(&sg_out[1], nskb->data + tcp_payload_offset, payload_len);
	/* Add room क्रम authentication tag produced by crypto */
	dummy_buf += sync_size;
	sg_set_buf(&sg_out[2], dummy_buf, TLS_CIPHER_AES_GCM_128_TAG_SIZE);
पूर्ण

अटल काष्ठा sk_buff *tls_enc_skb(काष्ठा tls_context *tls_ctx,
				   काष्ठा scatterlist sg_out[3],
				   काष्ठा scatterlist *sg_in,
				   काष्ठा sk_buff *skb,
				   s32 sync_size, u64 rcd_sn)
अणु
	पूर्णांक tcp_payload_offset = skb_transport_offset(skb) + tcp_hdrlen(skb);
	काष्ठा tls_offload_context_tx *ctx = tls_offload_ctx_tx(tls_ctx);
	पूर्णांक payload_len = skb->len - tcp_payload_offset;
	व्योम *buf, *iv, *aad, *dummy_buf;
	काष्ठा aead_request *aead_req;
	काष्ठा sk_buff *nskb = शून्य;
	पूर्णांक buf_len;

	aead_req = tls_alloc_aead_request(ctx->aead_send, GFP_ATOMIC);
	अगर (!aead_req)
		वापस शून्य;

	buf_len = TLS_CIPHER_AES_GCM_128_SALT_SIZE +
		  TLS_CIPHER_AES_GCM_128_IV_SIZE +
		  TLS_AAD_SPACE_SIZE +
		  sync_size +
		  TLS_CIPHER_AES_GCM_128_TAG_SIZE;
	buf = kदो_स्मृति(buf_len, GFP_ATOMIC);
	अगर (!buf)
		जाओ मुक्त_req;

	iv = buf;
	स_नकल(iv, tls_ctx->crypto_send.aes_gcm_128.salt,
	       TLS_CIPHER_AES_GCM_128_SALT_SIZE);
	aad = buf + TLS_CIPHER_AES_GCM_128_SALT_SIZE +
	      TLS_CIPHER_AES_GCM_128_IV_SIZE;
	dummy_buf = aad + TLS_AAD_SPACE_SIZE;

	nskb = alloc_skb(skb_headroom(skb) + skb->len, GFP_ATOMIC);
	अगर (!nskb)
		जाओ मुक्त_buf;

	skb_reserve(nskb, skb_headroom(skb));

	fill_sg_out(sg_out, buf, tls_ctx, nskb, tcp_payload_offset,
		    payload_len, sync_size, dummy_buf);

	अगर (tls_enc_records(aead_req, ctx->aead_send, sg_in, sg_out, aad, iv,
			    rcd_sn, sync_size + payload_len,
			    &tls_ctx->prot_info) < 0)
		जाओ मुक्त_nskb;

	complete_skb(nskb, skb, tcp_payload_offset);

	/* validate_xmit_skb_list assumes that अगर the skb wasn't segmented
	 * nskb->prev will poपूर्णांक to the skb itself
	 */
	nskb->prev = nskb;

मुक्त_buf:
	kमुक्त(buf);
मुक्त_req:
	kमुक्त(aead_req);
	वापस nskb;
मुक्त_nskb:
	kमुक्त_skb(nskb);
	nskb = शून्य;
	जाओ मुक्त_buf;
पूर्ण

अटल काष्ठा sk_buff *tls_sw_fallback(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक tcp_payload_offset = skb_transport_offset(skb) + tcp_hdrlen(skb);
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_offload_context_tx *ctx = tls_offload_ctx_tx(tls_ctx);
	पूर्णांक payload_len = skb->len - tcp_payload_offset;
	काष्ठा scatterlist *sg_in, sg_out[3];
	काष्ठा sk_buff *nskb = शून्य;
	पूर्णांक sg_in_max_elements;
	पूर्णांक resync_sgs = 0;
	s32 sync_size = 0;
	u64 rcd_sn;

	/* worst हाल is:
	 * MAX_SKB_FRAGS in tls_record_info
	 * MAX_SKB_FRAGS + 1 in SKB head and frags.
	 */
	sg_in_max_elements = 2 * MAX_SKB_FRAGS + 1;

	अगर (!payload_len)
		वापस skb;

	sg_in = kदो_स्मृति_array(sg_in_max_elements, माप(*sg_in), GFP_ATOMIC);
	अगर (!sg_in)
		जाओ मुक्त_orig;

	sg_init_table(sg_in, sg_in_max_elements);
	sg_init_table(sg_out, ARRAY_SIZE(sg_out));

	अगर (fill_sg_in(sg_in, skb, ctx, &rcd_sn, &sync_size, &resync_sgs)) अणु
		/* bypass packets beक्रमe kernel TLS socket option was set */
		अगर (sync_size < 0 && payload_len <= -sync_size)
			nskb = skb_get(skb);
		जाओ put_sg;
	पूर्ण

	nskb = tls_enc_skb(tls_ctx, sg_out, sg_in, skb, sync_size, rcd_sn);

put_sg:
	जबतक (resync_sgs)
		put_page(sg_page(&sg_in[--resync_sgs]));
	kमुक्त(sg_in);
मुक्त_orig:
	अगर (nskb)
		consume_skb(skb);
	अन्यथा
		kमुक्त_skb(skb);
	वापस nskb;
पूर्ण

काष्ठा sk_buff *tls_validate_xmit_skb(काष्ठा sock *sk,
				      काष्ठा net_device *dev,
				      काष्ठा sk_buff *skb)
अणु
	अगर (dev == tls_get_ctx(sk)->netdev || netअगर_is_bond_master(dev))
		वापस skb;

	वापस tls_sw_fallback(sk, skb);
पूर्ण
EXPORT_SYMBOL_GPL(tls_validate_xmit_skb);

काष्ठा sk_buff *tls_validate_xmit_skb_sw(काष्ठा sock *sk,
					 काष्ठा net_device *dev,
					 काष्ठा sk_buff *skb)
अणु
	वापस tls_sw_fallback(sk, skb);
पूर्ण

काष्ठा sk_buff *tls_encrypt_skb(काष्ठा sk_buff *skb)
अणु
	वापस tls_sw_fallback(skb->sk, skb);
पूर्ण
EXPORT_SYMBOL_GPL(tls_encrypt_skb);

पूर्णांक tls_sw_fallback_init(काष्ठा sock *sk,
			 काष्ठा tls_offload_context_tx *offload_ctx,
			 काष्ठा tls_crypto_info *crypto_info)
अणु
	स्थिर u8 *key;
	पूर्णांक rc;

	offload_ctx->aead_send =
	    crypto_alloc_aead("gcm(aes)", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(offload_ctx->aead_send)) अणु
		rc = PTR_ERR(offload_ctx->aead_send);
		pr_err_ratelimited("crypto_alloc_aead failed rc=%d\n", rc);
		offload_ctx->aead_send = शून्य;
		जाओ err_out;
	पूर्ण

	key = ((काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info)->key;

	rc = crypto_aead_setkey(offload_ctx->aead_send, key,
				TLS_CIPHER_AES_GCM_128_KEY_SIZE);
	अगर (rc)
		जाओ मुक्त_aead;

	rc = crypto_aead_setauthsize(offload_ctx->aead_send,
				     TLS_CIPHER_AES_GCM_128_TAG_SIZE);
	अगर (rc)
		जाओ मुक्त_aead;

	वापस 0;
मुक्त_aead:
	crypto_मुक्त_aead(offload_ctx->aead_send);
err_out:
	वापस rc;
पूर्ण
