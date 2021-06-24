<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Kerberos-based RxRPC security
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <crypto/skcipher.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/udp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/key-type.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "ar-internal.h"

#घोषणा RXKAD_VERSION			2
#घोषणा MAXKRB5TICKETLEN		1024
#घोषणा RXKAD_TKT_TYPE_KERBEROS_V5	256
#घोषणा ANAME_SZ			40	/* size of authentication name */
#घोषणा INST_SZ				40	/* size of principal's instance */
#घोषणा REALM_SZ			40	/* size of principal's auth करोमुख्य */
#घोषणा SNAME_SZ			40	/* size of service name */
#घोषणा RXKAD_ALIGN			8

काष्ठा rxkad_level1_hdr अणु
	__be32	data_size;	/* true data size (excluding padding) */
पूर्ण;

काष्ठा rxkad_level2_hdr अणु
	__be32	data_size;	/* true data size (excluding padding) */
	__be32	checksum;	/* decrypted data checksum */
पूर्ण;

अटल पूर्णांक rxkad_prime_packet_security(काष्ठा rxrpc_connection *conn,
				       काष्ठा crypto_sync_skcipher *ci);

/*
 * this holds a pinned cipher so that keventd करोesn't get called by the cipher
 * alloc routine, but since we have it to hand, we use it to decrypt RESPONSE
 * packets
 */
अटल काष्ठा crypto_sync_skcipher *rxkad_ci;
अटल काष्ठा skcipher_request *rxkad_ci_req;
अटल DEFINE_MUTEX(rxkad_ci_mutex);

/*
 * Parse the inक्रमmation from a server key
 *
 * The data should be the 8-byte secret key.
 */
अटल पूर्णांक rxkad_preparse_server_key(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा crypto_skcipher *ci;

	अगर (prep->datalen != 8)
		वापस -EINVAL;

	स_नकल(&prep->payload.data[2], prep->data, 8);

	ci = crypto_alloc_skcipher("pcbc(des)", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(ci)) अणु
		_leave(" = %ld", PTR_ERR(ci));
		वापस PTR_ERR(ci);
	पूर्ण

	अगर (crypto_skcipher_setkey(ci, prep->data, 8) < 0)
		BUG();

	prep->payload.data[0] = ci;
	_leave(" = 0");
	वापस 0;
पूर्ण

अटल व्योम rxkad_मुक्त_preparse_server_key(काष्ठा key_preparsed_payload *prep)
अणु

	अगर (prep->payload.data[0])
		crypto_मुक्त_skcipher(prep->payload.data[0]);
पूर्ण

अटल व्योम rxkad_destroy_server_key(काष्ठा key *key)
अणु
	अगर (key->payload.data[0]) अणु
		crypto_मुक्त_skcipher(key->payload.data[0]);
		key->payload.data[0] = शून्य;
	पूर्ण
पूर्ण

/*
 * initialise connection security
 */
अटल पूर्णांक rxkad_init_connection_security(काष्ठा rxrpc_connection *conn,
					  काष्ठा rxrpc_key_token *token)
अणु
	काष्ठा crypto_sync_skcipher *ci;
	पूर्णांक ret;

	_enter("{%d},{%x}", conn->debug_id, key_serial(conn->params.key));

	conn->security_ix = token->security_index;

	ci = crypto_alloc_sync_skcipher("pcbc(fcrypt)", 0, 0);
	अगर (IS_ERR(ci)) अणु
		_debug("no cipher");
		ret = PTR_ERR(ci);
		जाओ error;
	पूर्ण

	अगर (crypto_sync_skcipher_setkey(ci, token->kad->session_key,
				   माप(token->kad->session_key)) < 0)
		BUG();

	चयन (conn->params.security_level) अणु
	हाल RXRPC_SECURITY_PLAIN:
	हाल RXRPC_SECURITY_AUTH:
	हाल RXRPC_SECURITY_ENCRYPT:
		अवरोध;
	शेष:
		ret = -EKEYREJECTED;
		जाओ error;
	पूर्ण

	ret = rxkad_prime_packet_security(conn, ci);
	अगर (ret < 0)
		जाओ error_ci;

	conn->rxkad.cipher = ci;
	वापस 0;

error_ci:
	crypto_मुक्त_sync_skcipher(ci);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Work out how much data we can put in a packet.
 */
अटल पूर्णांक rxkad_how_much_data(काष्ठा rxrpc_call *call, माप_प्रकार reमुख्य,
			       माप_प्रकार *_buf_size, माप_प्रकार *_data_size, माप_प्रकार *_offset)
अणु
	माप_प्रकार shdr, buf_size, chunk;

	चयन (call->conn->params.security_level) अणु
	शेष:
		buf_size = chunk = min_t(माप_प्रकार, reमुख्य, RXRPC_JUMBO_DATALEN);
		shdr = 0;
		जाओ out;
	हाल RXRPC_SECURITY_AUTH:
		shdr = माप(काष्ठा rxkad_level1_hdr);
		अवरोध;
	हाल RXRPC_SECURITY_ENCRYPT:
		shdr = माप(काष्ठा rxkad_level2_hdr);
		अवरोध;
	पूर्ण

	buf_size = round_करोwn(RXRPC_JUMBO_DATALEN, RXKAD_ALIGN);

	chunk = buf_size - shdr;
	अगर (reमुख्य < chunk)
		buf_size = round_up(shdr + reमुख्य, RXKAD_ALIGN);

out:
	*_buf_size = buf_size;
	*_data_size = chunk;
	*_offset = shdr;
	वापस 0;
पूर्ण

/*
 * prime the encryption state with the invariant parts of a connection's
 * description
 */
अटल पूर्णांक rxkad_prime_packet_security(काष्ठा rxrpc_connection *conn,
				       काष्ठा crypto_sync_skcipher *ci)
अणु
	काष्ठा skcipher_request *req;
	काष्ठा rxrpc_key_token *token;
	काष्ठा scatterlist sg;
	काष्ठा rxrpc_crypt iv;
	__be32 *पंचांगpbuf;
	माप_प्रकार पंचांगpsize = 4 * माप(__be32);

	_enter("");

	अगर (!conn->params.key)
		वापस 0;

	पंचांगpbuf = kदो_स्मृति(पंचांगpsize, GFP_KERNEL);
	अगर (!पंचांगpbuf)
		वापस -ENOMEM;

	req = skcipher_request_alloc(&ci->base, GFP_NOFS);
	अगर (!req) अणु
		kमुक्त(पंचांगpbuf);
		वापस -ENOMEM;
	पूर्ण

	token = conn->params.key->payload.data[0];
	स_नकल(&iv, token->kad->session_key, माप(iv));

	पंचांगpbuf[0] = htonl(conn->proto.epoch);
	पंचांगpbuf[1] = htonl(conn->proto.cid);
	पंचांगpbuf[2] = 0;
	पंचांगpbuf[3] = htonl(conn->security_ix);

	sg_init_one(&sg, पंचांगpbuf, पंचांगpsize);
	skcipher_request_set_sync_tfm(req, ci);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &sg, &sg, पंचांगpsize, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_मुक्त(req);

	स_नकल(&conn->rxkad.csum_iv, पंचांगpbuf + 2, माप(conn->rxkad.csum_iv));
	kमुक्त(पंचांगpbuf);
	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * Allocate and prepare the crypto request on a call.  For any particular call,
 * this is called serially क्रम the packets, so no lock should be necessary.
 */
अटल काष्ठा skcipher_request *rxkad_get_call_crypto(काष्ठा rxrpc_call *call)
अणु
	काष्ठा crypto_skcipher *tfm = &call->conn->rxkad.cipher->base;
	काष्ठा skcipher_request	*cipher_req = call->cipher_req;

	अगर (!cipher_req) अणु
		cipher_req = skcipher_request_alloc(tfm, GFP_NOFS);
		अगर (!cipher_req)
			वापस शून्य;
		call->cipher_req = cipher_req;
	पूर्ण

	वापस cipher_req;
पूर्ण

/*
 * Clean up the crypto on a call.
 */
अटल व्योम rxkad_मुक्त_call_crypto(काष्ठा rxrpc_call *call)
अणु
	अगर (call->cipher_req)
		skcipher_request_मुक्त(call->cipher_req);
	call->cipher_req = शून्य;
पूर्ण

/*
 * partially encrypt a packet (level 1 security)
 */
अटल पूर्णांक rxkad_secure_packet_auth(स्थिर काष्ठा rxrpc_call *call,
				    काष्ठा sk_buff *skb, u32 data_size,
				    काष्ठा skcipher_request *req)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा rxkad_level1_hdr hdr;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist sg;
	माप_प्रकार pad;
	u16 check;

	_enter("");

	check = sp->hdr.seq ^ call->call_id;
	data_size |= (u32)check << 16;

	hdr.data_size = htonl(data_size);
	स_नकल(skb->head, &hdr, माप(hdr));

	pad = माप(काष्ठा rxkad_level1_hdr) + data_size;
	pad = RXKAD_ALIGN - pad;
	pad &= RXKAD_ALIGN - 1;
	अगर (pad)
		skb_put_zero(skb, pad);

	/* start the encryption afresh */
	स_रखो(&iv, 0, माप(iv));

	sg_init_one(&sg, skb->head, 8);
	skcipher_request_set_sync_tfm(req, call->conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &sg, &sg, 8, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * wholly encrypt a packet (level 2 security)
 */
अटल पूर्णांक rxkad_secure_packet_encrypt(स्थिर काष्ठा rxrpc_call *call,
				       काष्ठा sk_buff *skb,
				       u32 data_size,
				       काष्ठा skcipher_request *req)
अणु
	स्थिर काष्ठा rxrpc_key_token *token;
	काष्ठा rxkad_level2_hdr rxkhdr;
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist sg[16];
	अचिन्हित पूर्णांक len;
	माप_प्रकार pad;
	u16 check;
	पूर्णांक err;

	sp = rxrpc_skb(skb);

	_enter("");

	check = sp->hdr.seq ^ call->call_id;

	rxkhdr.data_size = htonl(data_size | (u32)check << 16);
	rxkhdr.checksum = 0;
	स_नकल(skb->head, &rxkhdr, माप(rxkhdr));

	pad = माप(काष्ठा rxkad_level2_hdr) + data_size;
	pad = RXKAD_ALIGN - pad;
	pad &= RXKAD_ALIGN - 1;
	अगर (pad)
		skb_put_zero(skb, pad);

	/* encrypt from the session key */
	token = call->conn->params.key->payload.data[0];
	स_नकल(&iv, token->kad->session_key, माप(iv));

	sg_init_one(&sg[0], skb->head, माप(rxkhdr));
	skcipher_request_set_sync_tfm(req, call->conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &sg[0], &sg[0], माप(rxkhdr), iv.x);
	crypto_skcipher_encrypt(req);

	/* we want to encrypt the skbuff in-place */
	err = -EMSGSIZE;
	अगर (skb_shinfo(skb)->nr_frags > 16)
		जाओ out;

	len = round_up(data_size, RXKAD_ALIGN);

	sg_init_table(sg, ARRAY_SIZE(sg));
	err = skb_to_sgvec(skb, sg, 8, len);
	अगर (unlikely(err < 0))
		जाओ out;
	skcipher_request_set_crypt(req, sg, sg, len, iv.x);
	crypto_skcipher_encrypt(req);

	_leave(" = 0");
	err = 0;

out:
	skcipher_request_zero(req);
	वापस err;
पूर्ण

/*
 * checksum an RxRPC packet header
 */
अटल पूर्णांक rxkad_secure_packet(काष्ठा rxrpc_call *call,
			       काष्ठा sk_buff *skb,
			       माप_प्रकार data_size)
अणु
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा skcipher_request	*req;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist sg;
	u32 x, y;
	पूर्णांक ret;

	sp = rxrpc_skb(skb);

	_enter("{%d{%x}},{#%u},%zu,",
	       call->debug_id, key_serial(call->conn->params.key),
	       sp->hdr.seq, data_size);

	अगर (!call->conn->rxkad.cipher)
		वापस 0;

	ret = key_validate(call->conn->params.key);
	अगर (ret < 0)
		वापस ret;

	req = rxkad_get_call_crypto(call);
	अगर (!req)
		वापस -ENOMEM;

	/* जारी encrypting from where we left off */
	स_नकल(&iv, call->conn->rxkad.csum_iv.x, माप(iv));

	/* calculate the security checksum */
	x = (call->cid & RXRPC_CHANNELMASK) << (32 - RXRPC_CIDSHIFT);
	x |= sp->hdr.seq & 0x3fffffff;
	call->crypto_buf[0] = htonl(call->call_id);
	call->crypto_buf[1] = htonl(x);

	sg_init_one(&sg, call->crypto_buf, 8);
	skcipher_request_set_sync_tfm(req, call->conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &sg, &sg, 8, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);

	y = ntohl(call->crypto_buf[1]);
	y = (y >> 16) & 0xffff;
	अगर (y == 0)
		y = 1; /* zero checksums are not permitted */
	sp->hdr.cksum = y;

	चयन (call->conn->params.security_level) अणु
	हाल RXRPC_SECURITY_PLAIN:
		ret = 0;
		अवरोध;
	हाल RXRPC_SECURITY_AUTH:
		ret = rxkad_secure_packet_auth(call, skb, data_size, req);
		अवरोध;
	हाल RXRPC_SECURITY_ENCRYPT:
		ret = rxkad_secure_packet_encrypt(call, skb, data_size, req);
		अवरोध;
	शेष:
		ret = -EPERM;
		अवरोध;
	पूर्ण

	_leave(" = %d [set %hx]", ret, y);
	वापस ret;
पूर्ण

/*
 * decrypt partial encryption on a packet (level 1 security)
 */
अटल पूर्णांक rxkad_verअगरy_packet_1(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
				 rxrpc_seq_t seq,
				 काष्ठा skcipher_request *req)
अणु
	काष्ठा rxkad_level1_hdr sechdr;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist sg[16];
	bool पातed;
	u32 data_size, buf;
	u16 check;
	पूर्णांक ret;

	_enter("");

	अगर (len < 8) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_1_hdr", "V1H",
					   RXKADSEALEDINCON);
		जाओ protocol_error;
	पूर्ण

	/* Decrypt the skbuff in-place.  TODO: We really want to decrypt
	 * directly पूर्णांकo the target buffer.
	 */
	sg_init_table(sg, ARRAY_SIZE(sg));
	ret = skb_to_sgvec(skb, sg, offset, 8);
	अगर (unlikely(ret < 0))
		वापस ret;

	/* start the decryption afresh */
	स_रखो(&iv, 0, माप(iv));

	skcipher_request_set_sync_tfm(req, call->conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, 8, iv.x);
	crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);

	/* Extract the decrypted packet length */
	अगर (skb_copy_bits(skb, offset, &sechdr, माप(sechdr)) < 0) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_1_len", "XV1",
					     RXKADDATALEN);
		जाओ protocol_error;
	पूर्ण
	len -= माप(sechdr);

	buf = ntohl(sechdr.data_size);
	data_size = buf & 0xffff;

	check = buf >> 16;
	check ^= seq ^ call->call_id;
	check &= 0xffff;
	अगर (check != 0) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_1_check", "V1C",
					     RXKADSEALEDINCON);
		जाओ protocol_error;
	पूर्ण

	अगर (data_size > len) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_1_datalen", "V1L",
					     RXKADDATALEN);
		जाओ protocol_error;
	पूर्ण

	_leave(" = 0 [dlen=%x]", data_size);
	वापस 0;

protocol_error:
	अगर (पातed)
		rxrpc_send_पात_packet(call);
	वापस -EPROTO;
पूर्ण

/*
 * wholly decrypt a packet (level 2 security)
 */
अटल पूर्णांक rxkad_verअगरy_packet_2(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
				 rxrpc_seq_t seq,
				 काष्ठा skcipher_request *req)
अणु
	स्थिर काष्ठा rxrpc_key_token *token;
	काष्ठा rxkad_level2_hdr sechdr;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist _sg[4], *sg;
	bool पातed;
	u32 data_size, buf;
	u16 check;
	पूर्णांक nsg, ret;

	_enter(",{%d}", skb->len);

	अगर (len < 8) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_2_hdr", "V2H",
					     RXKADSEALEDINCON);
		जाओ protocol_error;
	पूर्ण

	/* Decrypt the skbuff in-place.  TODO: We really want to decrypt
	 * directly पूर्णांकo the target buffer.
	 */
	sg = _sg;
	nsg = skb_shinfo(skb)->nr_frags;
	अगर (nsg <= 4) अणु
		nsg = 4;
	पूर्ण अन्यथा अणु
		sg = kदो_स्मृति_array(nsg, माप(*sg), GFP_NOIO);
		अगर (!sg)
			जाओ nomem;
	पूर्ण

	sg_init_table(sg, nsg);
	ret = skb_to_sgvec(skb, sg, offset, len);
	अगर (unlikely(ret < 0)) अणु
		अगर (sg != _sg)
			kमुक्त(sg);
		वापस ret;
	पूर्ण

	/* decrypt from the session key */
	token = call->conn->params.key->payload.data[0];
	स_नकल(&iv, token->kad->session_key, माप(iv));

	skcipher_request_set_sync_tfm(req, call->conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, len, iv.x);
	crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);
	अगर (sg != _sg)
		kमुक्त(sg);

	/* Extract the decrypted packet length */
	अगर (skb_copy_bits(skb, offset, &sechdr, माप(sechdr)) < 0) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_2_len", "XV2",
					     RXKADDATALEN);
		जाओ protocol_error;
	पूर्ण
	len -= माप(sechdr);

	buf = ntohl(sechdr.data_size);
	data_size = buf & 0xffff;

	check = buf >> 16;
	check ^= seq ^ call->call_id;
	check &= 0xffff;
	अगर (check != 0) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_2_check", "V2C",
					     RXKADSEALEDINCON);
		जाओ protocol_error;
	पूर्ण

	अगर (data_size > len) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_2_datalen", "V2L",
					     RXKADDATALEN);
		जाओ protocol_error;
	पूर्ण

	_leave(" = 0 [dlen=%x]", data_size);
	वापस 0;

protocol_error:
	अगर (पातed)
		rxrpc_send_पात_packet(call);
	वापस -EPROTO;

nomem:
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण

/*
 * Verअगरy the security on a received packet or subpacket (अगर part of a
 * jumbo packet).
 */
अटल पूर्णांक rxkad_verअगरy_packet(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
			       rxrpc_seq_t seq, u16 expected_cksum)
अणु
	काष्ठा skcipher_request	*req;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist sg;
	bool पातed;
	u16 cksum;
	u32 x, y;

	_enter("{%d{%x}},{#%u}",
	       call->debug_id, key_serial(call->conn->params.key), seq);

	अगर (!call->conn->rxkad.cipher)
		वापस 0;

	req = rxkad_get_call_crypto(call);
	अगर (!req)
		वापस -ENOMEM;

	/* जारी encrypting from where we left off */
	स_नकल(&iv, call->conn->rxkad.csum_iv.x, माप(iv));

	/* validate the security checksum */
	x = (call->cid & RXRPC_CHANNELMASK) << (32 - RXRPC_CIDSHIFT);
	x |= seq & 0x3fffffff;
	call->crypto_buf[0] = htonl(call->call_id);
	call->crypto_buf[1] = htonl(x);

	sg_init_one(&sg, call->crypto_buf, 8);
	skcipher_request_set_sync_tfm(req, call->conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &sg, &sg, 8, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);

	y = ntohl(call->crypto_buf[1]);
	cksum = (y >> 16) & 0xffff;
	अगर (cksum == 0)
		cksum = 1; /* zero checksums are not permitted */

	अगर (cksum != expected_cksum) अणु
		पातed = rxrpc_पात_eproto(call, skb, "rxkad_csum", "VCK",
					     RXKADSEALEDINCON);
		जाओ protocol_error;
	पूर्ण

	चयन (call->conn->params.security_level) अणु
	हाल RXRPC_SECURITY_PLAIN:
		वापस 0;
	हाल RXRPC_SECURITY_AUTH:
		वापस rxkad_verअगरy_packet_1(call, skb, offset, len, seq, req);
	हाल RXRPC_SECURITY_ENCRYPT:
		वापस rxkad_verअगरy_packet_2(call, skb, offset, len, seq, req);
	शेष:
		वापस -ENOANO;
	पूर्ण

protocol_error:
	अगर (पातed)
		rxrpc_send_पात_packet(call);
	वापस -EPROTO;
पूर्ण

/*
 * Locate the data contained in a packet that was partially encrypted.
 */
अटल व्योम rxkad_locate_data_1(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक *_offset, अचिन्हित पूर्णांक *_len)
अणु
	काष्ठा rxkad_level1_hdr sechdr;

	अगर (skb_copy_bits(skb, *_offset, &sechdr, माप(sechdr)) < 0)
		BUG();
	*_offset += माप(sechdr);
	*_len = ntohl(sechdr.data_size) & 0xffff;
पूर्ण

/*
 * Locate the data contained in a packet that was completely encrypted.
 */
अटल व्योम rxkad_locate_data_2(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक *_offset, अचिन्हित पूर्णांक *_len)
अणु
	काष्ठा rxkad_level2_hdr sechdr;

	अगर (skb_copy_bits(skb, *_offset, &sechdr, माप(sechdr)) < 0)
		BUG();
	*_offset += माप(sechdr);
	*_len = ntohl(sechdr.data_size) & 0xffff;
पूर्ण

/*
 * Locate the data contained in an alपढ़ोy decrypted packet.
 */
अटल व्योम rxkad_locate_data(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक *_offset, अचिन्हित पूर्णांक *_len)
अणु
	चयन (call->conn->params.security_level) अणु
	हाल RXRPC_SECURITY_AUTH:
		rxkad_locate_data_1(call, skb, _offset, _len);
		वापस;
	हाल RXRPC_SECURITY_ENCRYPT:
		rxkad_locate_data_2(call, skb, _offset, _len);
		वापस;
	शेष:
		वापस;
	पूर्ण
पूर्ण

/*
 * issue a challenge
 */
अटल पूर्णांक rxkad_issue_challenge(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा rxkad_challenge challenge;
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	माप_प्रकार len;
	u32 serial;
	पूर्णांक ret;

	_enter("{%d}", conn->debug_id);

	get_अक्रमom_bytes(&conn->rxkad.nonce, माप(conn->rxkad.nonce));

	challenge.version	= htonl(2);
	challenge.nonce		= htonl(conn->rxkad.nonce);
	challenge.min_level	= htonl(0);
	challenge.__padding	= 0;

	msg.msg_name	= &conn->params.peer->srx.transport;
	msg.msg_namelen	= conn->params.peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	whdr.epoch	= htonl(conn->proto.epoch);
	whdr.cid	= htonl(conn->proto.cid);
	whdr.callNumber	= 0;
	whdr.seq	= 0;
	whdr.type	= RXRPC_PACKET_TYPE_CHALLENGE;
	whdr.flags	= conn->out_clientflag;
	whdr.userStatus	= 0;
	whdr.securityIndex = conn->security_ix;
	whdr._rsvd	= 0;
	whdr.serviceId	= htons(conn->service_id);

	iov[0].iov_base	= &whdr;
	iov[0].iov_len	= माप(whdr);
	iov[1].iov_base	= &challenge;
	iov[1].iov_len	= माप(challenge);

	len = iov[0].iov_len + iov[1].iov_len;

	serial = atomic_inc_वापस(&conn->serial);
	whdr.serial = htonl(serial);
	_proto("Tx CHALLENGE %%%u", serial);

	ret = kernel_sendmsg(conn->params.local->socket, &msg, iov, 2, len);
	अगर (ret < 0) अणु
		trace_rxrpc_tx_fail(conn->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_rxkad_challenge);
		वापस -EAGAIN;
	पूर्ण

	conn->params.peer->last_tx_at = kसमय_get_seconds();
	trace_rxrpc_tx_packet(conn->debug_id, &whdr,
			      rxrpc_tx_poपूर्णांक_rxkad_challenge);
	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * send a Kerberos security response
 */
अटल पूर्णांक rxkad_send_response(काष्ठा rxrpc_connection *conn,
			       काष्ठा rxrpc_host_header *hdr,
			       काष्ठा rxkad_response *resp,
			       स्थिर काष्ठा rxkad_key *s2)
अणु
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[3];
	माप_प्रकार len;
	u32 serial;
	पूर्णांक ret;

	_enter("");

	msg.msg_name	= &conn->params.peer->srx.transport;
	msg.msg_namelen	= conn->params.peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	स_रखो(&whdr, 0, माप(whdr));
	whdr.epoch	= htonl(hdr->epoch);
	whdr.cid	= htonl(hdr->cid);
	whdr.type	= RXRPC_PACKET_TYPE_RESPONSE;
	whdr.flags	= conn->out_clientflag;
	whdr.securityIndex = hdr->securityIndex;
	whdr.serviceId	= htons(hdr->serviceId);

	iov[0].iov_base	= &whdr;
	iov[0].iov_len	= माप(whdr);
	iov[1].iov_base	= resp;
	iov[1].iov_len	= माप(*resp);
	iov[2].iov_base	= (व्योम *)s2->ticket;
	iov[2].iov_len	= s2->ticket_len;

	len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;

	serial = atomic_inc_वापस(&conn->serial);
	whdr.serial = htonl(serial);
	_proto("Tx RESPONSE %%%u", serial);

	ret = kernel_sendmsg(conn->params.local->socket, &msg, iov, 3, len);
	अगर (ret < 0) अणु
		trace_rxrpc_tx_fail(conn->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_rxkad_response);
		वापस -EAGAIN;
	पूर्ण

	conn->params.peer->last_tx_at = kसमय_get_seconds();
	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * calculate the response checksum
 */
अटल व्योम rxkad_calc_response_checksum(काष्ठा rxkad_response *response)
अणु
	u32 csum = 1000003;
	पूर्णांक loop;
	u8 *p = (u8 *) response;

	क्रम (loop = माप(*response); loop > 0; loop--)
		csum = csum * 0x10204081 + *p++;

	response->encrypted.checksum = htonl(csum);
पूर्ण

/*
 * encrypt the response packet
 */
अटल पूर्णांक rxkad_encrypt_response(काष्ठा rxrpc_connection *conn,
				  काष्ठा rxkad_response *resp,
				  स्थिर काष्ठा rxkad_key *s2)
अणु
	काष्ठा skcipher_request *req;
	काष्ठा rxrpc_crypt iv;
	काष्ठा scatterlist sg[1];

	req = skcipher_request_alloc(&conn->rxkad.cipher->base, GFP_NOFS);
	अगर (!req)
		वापस -ENOMEM;

	/* जारी encrypting from where we left off */
	स_नकल(&iv, s2->session_key, माप(iv));

	sg_init_table(sg, 1);
	sg_set_buf(sg, &resp->encrypted, माप(resp->encrypted));
	skcipher_request_set_sync_tfm(req, conn->rxkad.cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, माप(resp->encrypted), iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_मुक्त(req);
	वापस 0;
पूर्ण

/*
 * respond to a challenge packet
 */
अटल पूर्णांक rxkad_respond_to_challenge(काष्ठा rxrpc_connection *conn,
				      काष्ठा sk_buff *skb,
				      u32 *_पात_code)
अणु
	स्थिर काष्ठा rxrpc_key_token *token;
	काष्ठा rxkad_challenge challenge;
	काष्ठा rxkad_response *resp;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	स्थिर अक्षर *eproto;
	u32 version, nonce, min_level, पात_code;
	पूर्णांक ret;

	_enter("{%d,%x}", conn->debug_id, key_serial(conn->params.key));

	eproto = tracepoपूर्णांक_string("chall_no_key");
	पात_code = RX_PROTOCOL_ERROR;
	अगर (!conn->params.key)
		जाओ protocol_error;

	पात_code = RXKADEXPIRED;
	ret = key_validate(conn->params.key);
	अगर (ret < 0)
		जाओ other_error;

	eproto = tracepoपूर्णांक_string("chall_short");
	पात_code = RXKADPACKETSHORT;
	अगर (skb_copy_bits(skb, माप(काष्ठा rxrpc_wire_header),
			  &challenge, माप(challenge)) < 0)
		जाओ protocol_error;

	version = ntohl(challenge.version);
	nonce = ntohl(challenge.nonce);
	min_level = ntohl(challenge.min_level);

	_proto("Rx CHALLENGE %%%u { v=%u n=%u ml=%u }",
	       sp->hdr.serial, version, nonce, min_level);

	eproto = tracepoपूर्णांक_string("chall_ver");
	पात_code = RXKADINCONSISTENCY;
	अगर (version != RXKAD_VERSION)
		जाओ protocol_error;

	पात_code = RXKADLEVELFAIL;
	ret = -EACCES;
	अगर (conn->params.security_level < min_level)
		जाओ other_error;

	token = conn->params.key->payload.data[0];

	/* build the response packet */
	resp = kzalloc(माप(काष्ठा rxkad_response), GFP_NOFS);
	अगर (!resp)
		वापस -ENOMEM;

	resp->version			= htonl(RXKAD_VERSION);
	resp->encrypted.epoch		= htonl(conn->proto.epoch);
	resp->encrypted.cid		= htonl(conn->proto.cid);
	resp->encrypted.securityIndex	= htonl(conn->security_ix);
	resp->encrypted.inc_nonce	= htonl(nonce + 1);
	resp->encrypted.level		= htonl(conn->params.security_level);
	resp->kvno			= htonl(token->kad->kvno);
	resp->ticket_len		= htonl(token->kad->ticket_len);
	resp->encrypted.call_id[0]	= htonl(conn->channels[0].call_counter);
	resp->encrypted.call_id[1]	= htonl(conn->channels[1].call_counter);
	resp->encrypted.call_id[2]	= htonl(conn->channels[2].call_counter);
	resp->encrypted.call_id[3]	= htonl(conn->channels[3].call_counter);

	/* calculate the response checksum and then करो the encryption */
	rxkad_calc_response_checksum(resp);
	ret = rxkad_encrypt_response(conn, resp, token->kad);
	अगर (ret == 0)
		ret = rxkad_send_response(conn, &sp->hdr, resp, token->kad);
	kमुक्त(resp);
	वापस ret;

protocol_error:
	trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial, eproto);
	ret = -EPROTO;
other_error:
	*_पात_code = पात_code;
	वापस ret;
पूर्ण

/*
 * decrypt the kerberos IV ticket in the response
 */
अटल पूर्णांक rxkad_decrypt_ticket(काष्ठा rxrpc_connection *conn,
				काष्ठा key *server_key,
				काष्ठा sk_buff *skb,
				व्योम *ticket, माप_प्रकार ticket_len,
				काष्ठा rxrpc_crypt *_session_key,
				समय64_t *_expiry,
				u32 *_पात_code)
अणु
	काष्ठा skcipher_request *req;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा rxrpc_crypt iv, key;
	काष्ठा scatterlist sg[1];
	काष्ठा in_addr addr;
	अचिन्हित पूर्णांक lअगरe;
	स्थिर अक्षर *eproto;
	समय64_t issue, now;
	bool little_endian;
	पूर्णांक ret;
	u32 पात_code;
	u8 *p, *q, *name, *end;

	_enter("{%d},{%x}", conn->debug_id, key_serial(server_key));

	*_expiry = 0;

	ASSERT(server_key->payload.data[0] != शून्य);
	ASSERTCMP((अचिन्हित दीर्घ) ticket & 7UL, ==, 0);

	स_नकल(&iv, &server_key->payload.data[2], माप(iv));

	ret = -ENOMEM;
	req = skcipher_request_alloc(server_key->payload.data[0], GFP_NOFS);
	अगर (!req)
		जाओ temporary_error;

	sg_init_one(&sg[0], ticket, ticket_len);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, ticket_len, iv.x);
	crypto_skcipher_decrypt(req);
	skcipher_request_मुक्त(req);

	p = ticket;
	end = p + ticket_len;

#घोषणा Z(field)					\
	(अणु						\
		u8 *__str = p;				\
		eproto = tracepoपूर्णांक_string("rxkad_bad_"#field); \
		q = स_प्रथम(p, 0, end - p);		\
		अगर (!q || q - p > (field##_SZ))		\
			जाओ bad_ticket;		\
		क्रम (; p < q; p++)			\
			अगर (!है_छाप(*p))		\
				जाओ bad_ticket;	\
		p++;					\
		__str;					\
	पूर्ण)

	/* extract the ticket flags */
	_debug("KIV FLAGS: %x", *p);
	little_endian = *p & 1;
	p++;

	/* extract the authentication name */
	name = Z(ANAME);
	_debug("KIV ANAME: %s", name);

	/* extract the principal's instance */
	name = Z(INST);
	_debug("KIV INST : %s", name);

	/* extract the principal's authentication करोमुख्य */
	name = Z(REALM);
	_debug("KIV REALM: %s", name);

	eproto = tracepoपूर्णांक_string("rxkad_bad_len");
	अगर (end - p < 4 + 8 + 4 + 2)
		जाओ bad_ticket;

	/* get the IPv4 address of the entity that requested the ticket */
	स_नकल(&addr, p, माप(addr));
	p += 4;
	_debug("KIV ADDR : %pI4", &addr);

	/* get the session key from the ticket */
	स_नकल(&key, p, माप(key));
	p += 8;
	_debug("KIV KEY  : %08x %08x", ntohl(key.n[0]), ntohl(key.n[1]));
	स_नकल(_session_key, &key, माप(key));

	/* get the ticket's lअगरeसमय */
	lअगरe = *p++ * 5 * 60;
	_debug("KIV LIFE : %u", lअगरe);

	/* get the issue समय of the ticket */
	अगर (little_endian) अणु
		__le32 stamp;
		स_नकल(&stamp, p, 4);
		issue = rxrpc_u32_to_समय64(le32_to_cpu(stamp));
	पूर्ण अन्यथा अणु
		__be32 stamp;
		स_नकल(&stamp, p, 4);
		issue = rxrpc_u32_to_समय64(be32_to_cpu(stamp));
	पूर्ण
	p += 4;
	now = kसमय_get_real_seconds();
	_debug("KIV ISSUE: %llx [%llx]", issue, now);

	/* check the ticket is in date */
	अगर (issue > now) अणु
		पात_code = RXKADNOAUTH;
		ret = -EKEYREJECTED;
		जाओ other_error;
	पूर्ण

	अगर (issue < now - lअगरe) अणु
		पात_code = RXKADEXPIRED;
		ret = -EKEYEXPIRED;
		जाओ other_error;
	पूर्ण

	*_expiry = issue + lअगरe;

	/* get the service name */
	name = Z(SNAME);
	_debug("KIV SNAME: %s", name);

	/* get the service instance name */
	name = Z(INST);
	_debug("KIV SINST: %s", name);
	वापस 0;

bad_ticket:
	trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial, eproto);
	पात_code = RXKADBADTICKET;
	ret = -EPROTO;
other_error:
	*_पात_code = पात_code;
	वापस ret;
temporary_error:
	वापस ret;
पूर्ण

/*
 * decrypt the response packet
 */
अटल व्योम rxkad_decrypt_response(काष्ठा rxrpc_connection *conn,
				   काष्ठा rxkad_response *resp,
				   स्थिर काष्ठा rxrpc_crypt *session_key)
अणु
	काष्ठा skcipher_request *req = rxkad_ci_req;
	काष्ठा scatterlist sg[1];
	काष्ठा rxrpc_crypt iv;

	_enter(",,%08x%08x",
	       ntohl(session_key->n[0]), ntohl(session_key->n[1]));

	mutex_lock(&rxkad_ci_mutex);
	अगर (crypto_sync_skcipher_setkey(rxkad_ci, session_key->x,
					माप(*session_key)) < 0)
		BUG();

	स_नकल(&iv, session_key, माप(iv));

	sg_init_table(sg, 1);
	sg_set_buf(sg, &resp->encrypted, माप(resp->encrypted));
	skcipher_request_set_sync_tfm(req, rxkad_ci);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, माप(resp->encrypted), iv.x);
	crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);

	mutex_unlock(&rxkad_ci_mutex);

	_leave("");
पूर्ण

/*
 * verअगरy a response
 */
अटल पूर्णांक rxkad_verअगरy_response(काष्ठा rxrpc_connection *conn,
				 काष्ठा sk_buff *skb,
				 u32 *_पात_code)
अणु
	काष्ठा rxkad_response *response;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा rxrpc_crypt session_key;
	काष्ठा key *server_key;
	स्थिर अक्षर *eproto;
	समय64_t expiry;
	व्योम *ticket;
	u32 पात_code, version, kvno, ticket_len, level;
	__be32 csum;
	पूर्णांक ret, i;

	_enter("{%d}", conn->debug_id);

	server_key = rxrpc_look_up_server_security(conn, skb, 0, 0);
	अगर (IS_ERR(server_key)) अणु
		चयन (PTR_ERR(server_key)) अणु
		हाल -ENOKEY:
			पात_code = RXKADUNKNOWNKEY;
			अवरोध;
		हाल -EKEYEXPIRED:
			पात_code = RXKADEXPIRED;
			अवरोध;
		शेष:
			पात_code = RXKADNOAUTH;
			अवरोध;
		पूर्ण
		trace_rxrpc_पात(0, "SVK",
				  sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
				  पात_code, PTR_ERR(server_key));
		*_पात_code = पात_code;
		वापस -EPROTO;
	पूर्ण

	ret = -ENOMEM;
	response = kzalloc(माप(काष्ठा rxkad_response), GFP_NOFS);
	अगर (!response)
		जाओ temporary_error;

	eproto = tracepoपूर्णांक_string("rxkad_rsp_short");
	पात_code = RXKADPACKETSHORT;
	अगर (skb_copy_bits(skb, माप(काष्ठा rxrpc_wire_header),
			  response, माप(*response)) < 0)
		जाओ protocol_error;

	version = ntohl(response->version);
	ticket_len = ntohl(response->ticket_len);
	kvno = ntohl(response->kvno);
	_proto("Rx RESPONSE %%%u { v=%u kv=%u tl=%u }",
	       sp->hdr.serial, version, kvno, ticket_len);

	eproto = tracepoपूर्णांक_string("rxkad_rsp_ver");
	पात_code = RXKADINCONSISTENCY;
	अगर (version != RXKAD_VERSION)
		जाओ protocol_error;

	eproto = tracepoपूर्णांक_string("rxkad_rsp_tktlen");
	पात_code = RXKADTICKETLEN;
	अगर (ticket_len < 4 || ticket_len > MAXKRB5TICKETLEN)
		जाओ protocol_error;

	eproto = tracepoपूर्णांक_string("rxkad_rsp_unkkey");
	पात_code = RXKADUNKNOWNKEY;
	अगर (kvno >= RXKAD_TKT_TYPE_KERBEROS_V5)
		जाओ protocol_error;

	/* extract the kerberos ticket and decrypt and decode it */
	ret = -ENOMEM;
	ticket = kदो_स्मृति(ticket_len, GFP_NOFS);
	अगर (!ticket)
		जाओ temporary_error_मुक्त_resp;

	eproto = tracepoपूर्णांक_string("rxkad_tkt_short");
	पात_code = RXKADPACKETSHORT;
	अगर (skb_copy_bits(skb, माप(काष्ठा rxrpc_wire_header) + माप(*response),
			  ticket, ticket_len) < 0)
		जाओ protocol_error_मुक्त;

	ret = rxkad_decrypt_ticket(conn, server_key, skb, ticket, ticket_len,
				   &session_key, &expiry, _पात_code);
	अगर (ret < 0)
		जाओ temporary_error_मुक्त_ticket;

	/* use the session key from inside the ticket to decrypt the
	 * response */
	rxkad_decrypt_response(conn, response, &session_key);

	eproto = tracepoपूर्णांक_string("rxkad_rsp_param");
	पात_code = RXKADSEALEDINCON;
	अगर (ntohl(response->encrypted.epoch) != conn->proto.epoch)
		जाओ protocol_error_मुक्त;
	अगर (ntohl(response->encrypted.cid) != conn->proto.cid)
		जाओ protocol_error_मुक्त;
	अगर (ntohl(response->encrypted.securityIndex) != conn->security_ix)
		जाओ protocol_error_मुक्त;
	csum = response->encrypted.checksum;
	response->encrypted.checksum = 0;
	rxkad_calc_response_checksum(response);
	eproto = tracepoपूर्णांक_string("rxkad_rsp_csum");
	अगर (response->encrypted.checksum != csum)
		जाओ protocol_error_मुक्त;

	spin_lock(&conn->bundle->channel_lock);
	क्रम (i = 0; i < RXRPC_MAXCALLS; i++) अणु
		काष्ठा rxrpc_call *call;
		u32 call_id = ntohl(response->encrypted.call_id[i]);

		eproto = tracepoपूर्णांक_string("rxkad_rsp_callid");
		अगर (call_id > पूर्णांक_उच्च)
			जाओ protocol_error_unlock;

		eproto = tracepoपूर्णांक_string("rxkad_rsp_callctr");
		अगर (call_id < conn->channels[i].call_counter)
			जाओ protocol_error_unlock;

		eproto = tracepoपूर्णांक_string("rxkad_rsp_callst");
		अगर (call_id > conn->channels[i].call_counter) अणु
			call = rcu_dereference_रक्षित(
				conn->channels[i].call,
				lockdep_is_held(&conn->bundle->channel_lock));
			अगर (call && call->state < RXRPC_CALL_COMPLETE)
				जाओ protocol_error_unlock;
			conn->channels[i].call_counter = call_id;
		पूर्ण
	पूर्ण
	spin_unlock(&conn->bundle->channel_lock);

	eproto = tracepoपूर्णांक_string("rxkad_rsp_seq");
	पात_code = RXKADOUTOFSEQUENCE;
	अगर (ntohl(response->encrypted.inc_nonce) != conn->rxkad.nonce + 1)
		जाओ protocol_error_मुक्त;

	eproto = tracepoपूर्णांक_string("rxkad_rsp_level");
	पात_code = RXKADLEVELFAIL;
	level = ntohl(response->encrypted.level);
	अगर (level > RXRPC_SECURITY_ENCRYPT)
		जाओ protocol_error_मुक्त;
	conn->params.security_level = level;

	/* create a key to hold the security data and expiration समय - after
	 * this the connection security can be handled in exactly the same way
	 * as क्रम a client connection */
	ret = rxrpc_get_server_data_key(conn, &session_key, expiry, kvno);
	अगर (ret < 0)
		जाओ temporary_error_मुक्त_ticket;

	kमुक्त(ticket);
	kमुक्त(response);
	_leave(" = 0");
	वापस 0;

protocol_error_unlock:
	spin_unlock(&conn->bundle->channel_lock);
protocol_error_मुक्त:
	kमुक्त(ticket);
protocol_error:
	kमुक्त(response);
	trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial, eproto);
	key_put(server_key);
	*_पात_code = पात_code;
	वापस -EPROTO;

temporary_error_मुक्त_ticket:
	kमुक्त(ticket);
temporary_error_मुक्त_resp:
	kमुक्त(response);
temporary_error:
	/* Ignore the response packet अगर we got a temporary error such as
	 * ENOMEM.  We just want to send the challenge again.  Note that we
	 * also come out this way अगर the ticket decryption fails.
	 */
	key_put(server_key);
	वापस ret;
पूर्ण

/*
 * clear the connection security
 */
अटल व्योम rxkad_clear(काष्ठा rxrpc_connection *conn)
अणु
	_enter("");

	अगर (conn->rxkad.cipher)
		crypto_मुक्त_sync_skcipher(conn->rxkad.cipher);
पूर्ण

/*
 * Initialise the rxkad security service.
 */
अटल पूर्णांक rxkad_init(व्योम)
अणु
	काष्ठा crypto_sync_skcipher *tfm;
	काष्ठा skcipher_request *req;

	/* pin the cipher we need so that the crypto layer करोesn't invoke
	 * keventd to go get it */
	tfm = crypto_alloc_sync_skcipher("pcbc(fcrypt)", 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	req = skcipher_request_alloc(&tfm->base, GFP_KERNEL);
	अगर (!req)
		जाओ nomem_tfm;

	rxkad_ci_req = req;
	rxkad_ci = tfm;
	वापस 0;

nomem_tfm:
	crypto_मुक्त_sync_skcipher(tfm);
	वापस -ENOMEM;
पूर्ण

/*
 * Clean up the rxkad security service.
 */
अटल व्योम rxkad_निकास(व्योम)
अणु
	crypto_मुक्त_sync_skcipher(rxkad_ci);
	skcipher_request_मुक्त(rxkad_ci_req);
पूर्ण

/*
 * RxRPC Kerberos-based security
 */
स्थिर काष्ठा rxrpc_security rxkad = अणु
	.name				= "rxkad",
	.security_index			= RXRPC_SECURITY_RXKAD,
	.no_key_पात			= RXKADUNKNOWNKEY,
	.init				= rxkad_init,
	.निकास				= rxkad_निकास,
	.preparse_server_key		= rxkad_preparse_server_key,
	.मुक्त_preparse_server_key	= rxkad_मुक्त_preparse_server_key,
	.destroy_server_key		= rxkad_destroy_server_key,
	.init_connection_security	= rxkad_init_connection_security,
	.how_much_data			= rxkad_how_much_data,
	.secure_packet			= rxkad_secure_packet,
	.verअगरy_packet			= rxkad_verअगरy_packet,
	.मुक्त_call_crypto		= rxkad_मुक्त_call_crypto,
	.locate_data			= rxkad_locate_data,
	.issue_challenge		= rxkad_issue_challenge,
	.respond_to_challenge		= rxkad_respond_to_challenge,
	.verअगरy_response		= rxkad_verअगरy_response,
	.clear				= rxkad_clear,
पूर्ण;
