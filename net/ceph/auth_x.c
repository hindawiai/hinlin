<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/messenger.h>

#समावेश "crypto.h"
#समावेश "auth_x.h"
#समावेश "auth_x_protocol.h"

अटल व्योम ceph_x_validate_tickets(काष्ठा ceph_auth_client *ac, पूर्णांक *pneed);

अटल पूर्णांक ceph_x_is_authenticated(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	पूर्णांक missing;
	पूर्णांक need;  /* missing + need renewal */

	ceph_x_validate_tickets(ac, &need);
	missing = ac->want_keys & ~xi->have_keys;
	WARN_ON((need & missing) != missing);
	करोut("%s want 0x%x have 0x%x missing 0x%x -> %d\n", __func__,
	     ac->want_keys, xi->have_keys, missing, !missing);
	वापस !missing;
पूर्ण

अटल पूर्णांक ceph_x_should_authenticate(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	पूर्णांक need;

	ceph_x_validate_tickets(ac, &need);
	करोut("%s want 0x%x have 0x%x need 0x%x -> %d\n", __func__,
	     ac->want_keys, xi->have_keys, need, !!need);
	वापस !!need;
पूर्ण

अटल पूर्णांक ceph_x_encrypt_offset(व्योम)
अणु
	वापस माप(u32) + माप(काष्ठा ceph_x_encrypt_header);
पूर्ण

अटल पूर्णांक ceph_x_encrypt_buflen(पूर्णांक ilen)
अणु
	वापस ceph_x_encrypt_offset() + ilen + 16;
पूर्ण

अटल पूर्णांक ceph_x_encrypt(काष्ठा ceph_crypto_key *secret, व्योम *buf,
			  पूर्णांक buf_len, पूर्णांक plaपूर्णांकext_len)
अणु
	काष्ठा ceph_x_encrypt_header *hdr = buf + माप(u32);
	पूर्णांक ciphertext_len;
	पूर्णांक ret;

	hdr->काष्ठा_v = 1;
	hdr->magic = cpu_to_le64(CEPHX_ENC_MAGIC);

	ret = ceph_crypt(secret, true, buf + माप(u32), buf_len - माप(u32),
			 plaपूर्णांकext_len + माप(काष्ठा ceph_x_encrypt_header),
			 &ciphertext_len);
	अगर (ret)
		वापस ret;

	ceph_encode_32(&buf, ciphertext_len);
	वापस माप(u32) + ciphertext_len;
पूर्ण

अटल पूर्णांक __ceph_x_decrypt(काष्ठा ceph_crypto_key *secret, व्योम *p,
			    पूर्णांक ciphertext_len)
अणु
	काष्ठा ceph_x_encrypt_header *hdr = p;
	पूर्णांक plaपूर्णांकext_len;
	पूर्णांक ret;

	ret = ceph_crypt(secret, false, p, ciphertext_len, ciphertext_len,
			 &plaपूर्णांकext_len);
	अगर (ret)
		वापस ret;

	अगर (le64_to_cpu(hdr->magic) != CEPHX_ENC_MAGIC) अणु
		pr_err("%s bad magic\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस plaपूर्णांकext_len - माप(*hdr);
पूर्ण

अटल पूर्णांक ceph_x_decrypt(काष्ठा ceph_crypto_key *secret, व्योम **p, व्योम *end)
अणु
	पूर्णांक ciphertext_len;
	पूर्णांक ret;

	ceph_decode_32_safe(p, end, ciphertext_len, e_inval);
	ceph_decode_need(p, end, ciphertext_len, e_inval);

	ret = __ceph_x_decrypt(secret, *p, ciphertext_len);
	अगर (ret < 0)
		वापस ret;

	*p += ciphertext_len;
	वापस ret;

e_inval:
	वापस -EINVAL;
पूर्ण

/*
 * get existing (or insert new) ticket handler
 */
अटल काष्ठा ceph_x_ticket_handler *
get_ticket_handler(काष्ठा ceph_auth_client *ac, पूर्णांक service)
अणु
	काष्ठा ceph_x_ticket_handler *th;
	काष्ठा ceph_x_info *xi = ac->निजी;
	काष्ठा rb_node *parent = शून्य, **p = &xi->ticket_handlers.rb_node;

	जबतक (*p) अणु
		parent = *p;
		th = rb_entry(parent, काष्ठा ceph_x_ticket_handler, node);
		अगर (service < th->service)
			p = &(*p)->rb_left;
		अन्यथा अगर (service > th->service)
			p = &(*p)->rb_right;
		अन्यथा
			वापस th;
	पूर्ण

	/* add it */
	th = kzalloc(माप(*th), GFP_NOFS);
	अगर (!th)
		वापस ERR_PTR(-ENOMEM);
	th->service = service;
	rb_link_node(&th->node, parent, p);
	rb_insert_color(&th->node, &xi->ticket_handlers);
	वापस th;
पूर्ण

अटल व्योम हटाओ_ticket_handler(काष्ठा ceph_auth_client *ac,
				  काष्ठा ceph_x_ticket_handler *th)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;

	करोut("remove_ticket_handler %p %d\n", th, th->service);
	rb_erase(&th->node, &xi->ticket_handlers);
	ceph_crypto_key_destroy(&th->session_key);
	अगर (th->ticket_blob)
		ceph_buffer_put(th->ticket_blob);
	kमुक्त(th);
पूर्ण

अटल पूर्णांक process_one_ticket(काष्ठा ceph_auth_client *ac,
			      काष्ठा ceph_crypto_key *secret,
			      व्योम **p, व्योम *end)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	पूर्णांक type;
	u8 tkt_काष्ठा_v, blob_काष्ठा_v;
	काष्ठा ceph_x_ticket_handler *th;
	व्योम *dp, *dend;
	पूर्णांक dlen;
	अक्षर is_enc;
	काष्ठा बारpec64 validity;
	व्योम *tp, *tpend;
	व्योम **ptp;
	काष्ठा ceph_crypto_key new_session_key = अणु 0 पूर्ण;
	काष्ठा ceph_buffer *new_ticket_blob;
	समय64_t new_expires, new_renew_after;
	u64 new_secret_id;
	पूर्णांक ret;

	ceph_decode_need(p, end, माप(u32) + 1, bad);

	type = ceph_decode_32(p);
	करोut(" ticket type %d %s\n", type, ceph_entity_type_name(type));

	tkt_काष्ठा_v = ceph_decode_8(p);
	अगर (tkt_काष्ठा_v != 1)
		जाओ bad;

	th = get_ticket_handler(ac, type);
	अगर (IS_ERR(th)) अणु
		ret = PTR_ERR(th);
		जाओ out;
	पूर्ण

	/* blob क्रम me */
	dp = *p + ceph_x_encrypt_offset();
	ret = ceph_x_decrypt(secret, p, end);
	अगर (ret < 0)
		जाओ out;
	करोut(" decrypted %d bytes\n", ret);
	dend = dp + ret;

	ceph_decode_8_safe(&dp, dend, tkt_काष्ठा_v, bad);
	अगर (tkt_काष्ठा_v != 1)
		जाओ bad;

	ret = ceph_crypto_key_decode(&new_session_key, &dp, dend);
	अगर (ret)
		जाओ out;

	ceph_decode_need(&dp, dend, माप(काष्ठा ceph_बारpec), bad);
	ceph_decode_बारpec64(&validity, dp);
	dp += माप(काष्ठा ceph_बारpec);
	new_expires = kसमय_get_real_seconds() + validity.tv_sec;
	new_renew_after = new_expires - (validity.tv_sec / 4);
	करोut(" expires=%llu renew_after=%llu\n", new_expires,
	     new_renew_after);

	/* ticket blob क्रम service */
	ceph_decode_8_safe(p, end, is_enc, bad);
	अगर (is_enc) अणु
		/* encrypted */
		tp = *p + ceph_x_encrypt_offset();
		ret = ceph_x_decrypt(&th->session_key, p, end);
		अगर (ret < 0)
			जाओ out;
		करोut(" encrypted ticket, decrypted %d bytes\n", ret);
		ptp = &tp;
		tpend = tp + ret;
	पूर्ण अन्यथा अणु
		/* unencrypted */
		ptp = p;
		tpend = end;
	पूर्ण
	ceph_decode_32_safe(ptp, tpend, dlen, bad);
	करोut(" ticket blob is %d bytes\n", dlen);
	ceph_decode_need(ptp, tpend, 1 + माप(u64), bad);
	blob_काष्ठा_v = ceph_decode_8(ptp);
	अगर (blob_काष्ठा_v != 1)
		जाओ bad;

	new_secret_id = ceph_decode_64(ptp);
	ret = ceph_decode_buffer(&new_ticket_blob, ptp, tpend);
	अगर (ret)
		जाओ out;

	/* all is well, update our ticket */
	ceph_crypto_key_destroy(&th->session_key);
	अगर (th->ticket_blob)
		ceph_buffer_put(th->ticket_blob);
	th->session_key = new_session_key;
	th->ticket_blob = new_ticket_blob;
	th->secret_id = new_secret_id;
	th->expires = new_expires;
	th->renew_after = new_renew_after;
	th->have_key = true;
	करोut(" got ticket service %d (%s) secret_id %lld len %d\n",
	     type, ceph_entity_type_name(type), th->secret_id,
	     (पूर्णांक)th->ticket_blob->vec.iov_len);
	xi->have_keys |= th->service;
	वापस 0;

bad:
	ret = -EINVAL;
out:
	ceph_crypto_key_destroy(&new_session_key);
	वापस ret;
पूर्ण

अटल पूर्णांक ceph_x_proc_ticket_reply(काष्ठा ceph_auth_client *ac,
				    काष्ठा ceph_crypto_key *secret,
				    व्योम **p, व्योम *end)
अणु
	u8 reply_काष्ठा_v;
	u32 num;
	पूर्णांक ret;

	ceph_decode_8_safe(p, end, reply_काष्ठा_v, bad);
	अगर (reply_काष्ठा_v != 1)
		वापस -EINVAL;

	ceph_decode_32_safe(p, end, num, bad);
	करोut("%d tickets\n", num);

	जबतक (num--) अणु
		ret = process_one_ticket(ac, secret, p, end);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

bad:
	वापस -EINVAL;
पूर्ण

/*
 * Encode and encrypt the second part (ceph_x_authorize_b) of the
 * authorizer.  The first part (ceph_x_authorize_a) should alपढ़ोy be
 * encoded.
 */
अटल पूर्णांक encrypt_authorizer(काष्ठा ceph_x_authorizer *au,
			      u64 *server_challenge)
अणु
	काष्ठा ceph_x_authorize_a *msg_a;
	काष्ठा ceph_x_authorize_b *msg_b;
	व्योम *p, *end;
	पूर्णांक ret;

	msg_a = au->buf->vec.iov_base;
	WARN_ON(msg_a->ticket_blob.secret_id != cpu_to_le64(au->secret_id));
	p = (व्योम *)(msg_a + 1) + le32_to_cpu(msg_a->ticket_blob.blob_len);
	end = au->buf->vec.iov_base + au->buf->vec.iov_len;

	msg_b = p + ceph_x_encrypt_offset();
	msg_b->काष्ठा_v = 2;
	msg_b->nonce = cpu_to_le64(au->nonce);
	अगर (server_challenge) अणु
		msg_b->have_challenge = 1;
		msg_b->server_challenge_plus_one =
		    cpu_to_le64(*server_challenge + 1);
	पूर्ण अन्यथा अणु
		msg_b->have_challenge = 0;
		msg_b->server_challenge_plus_one = 0;
	पूर्ण

	ret = ceph_x_encrypt(&au->session_key, p, end - p, माप(*msg_b));
	अगर (ret < 0)
		वापस ret;

	p += ret;
	अगर (server_challenge) अणु
		WARN_ON(p != end);
	पूर्ण अन्यथा अणु
		WARN_ON(p > end);
		au->buf->vec.iov_len = p - au->buf->vec.iov_base;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ceph_x_authorizer_cleanup(काष्ठा ceph_x_authorizer *au)
अणु
	ceph_crypto_key_destroy(&au->session_key);
	अगर (au->buf) अणु
		ceph_buffer_put(au->buf);
		au->buf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ceph_x_build_authorizer(काष्ठा ceph_auth_client *ac,
				   काष्ठा ceph_x_ticket_handler *th,
				   काष्ठा ceph_x_authorizer *au)
अणु
	पूर्णांक maxlen;
	काष्ठा ceph_x_authorize_a *msg_a;
	काष्ठा ceph_x_authorize_b *msg_b;
	पूर्णांक ret;
	पूर्णांक ticket_blob_len =
		(th->ticket_blob ? th->ticket_blob->vec.iov_len : 0);

	करोut("build_authorizer for %s %p\n",
	     ceph_entity_type_name(th->service), au);

	ceph_crypto_key_destroy(&au->session_key);
	ret = ceph_crypto_key_clone(&au->session_key, &th->session_key);
	अगर (ret)
		जाओ out_au;

	maxlen = माप(*msg_a) + ticket_blob_len +
		ceph_x_encrypt_buflen(माप(*msg_b));
	करोut("  need len %d\n", maxlen);
	अगर (au->buf && au->buf->alloc_len < maxlen) अणु
		ceph_buffer_put(au->buf);
		au->buf = शून्य;
	पूर्ण
	अगर (!au->buf) अणु
		au->buf = ceph_buffer_new(maxlen, GFP_NOFS);
		अगर (!au->buf) अणु
			ret = -ENOMEM;
			जाओ out_au;
		पूर्ण
	पूर्ण
	au->service = th->service;
	WARN_ON(!th->secret_id);
	au->secret_id = th->secret_id;

	msg_a = au->buf->vec.iov_base;
	msg_a->काष्ठा_v = 1;
	msg_a->global_id = cpu_to_le64(ac->global_id);
	msg_a->service_id = cpu_to_le32(th->service);
	msg_a->ticket_blob.काष्ठा_v = 1;
	msg_a->ticket_blob.secret_id = cpu_to_le64(th->secret_id);
	msg_a->ticket_blob.blob_len = cpu_to_le32(ticket_blob_len);
	अगर (ticket_blob_len) अणु
		स_नकल(msg_a->ticket_blob.blob, th->ticket_blob->vec.iov_base,
		       th->ticket_blob->vec.iov_len);
	पूर्ण
	करोut(" th %p secret_id %lld %lld\n", th, th->secret_id,
	     le64_to_cpu(msg_a->ticket_blob.secret_id));

	get_अक्रमom_bytes(&au->nonce, माप(au->nonce));
	ret = encrypt_authorizer(au, शून्य);
	अगर (ret) अणु
		pr_err("failed to encrypt authorizer: %d", ret);
		जाओ out_au;
	पूर्ण

	करोut(" built authorizer nonce %llx len %d\n", au->nonce,
	     (पूर्णांक)au->buf->vec.iov_len);
	वापस 0;

out_au:
	ceph_x_authorizer_cleanup(au);
	वापस ret;
पूर्ण

अटल पूर्णांक ceph_x_encode_ticket(काष्ठा ceph_x_ticket_handler *th,
				व्योम **p, व्योम *end)
अणु
	ceph_decode_need(p, end, 1 + माप(u64), bad);
	ceph_encode_8(p, 1);
	ceph_encode_64(p, th->secret_id);
	अगर (th->ticket_blob) अणु
		स्थिर अक्षर *buf = th->ticket_blob->vec.iov_base;
		u32 len = th->ticket_blob->vec.iov_len;

		ceph_encode_32_safe(p, end, len, bad);
		ceph_encode_copy_safe(p, end, buf, len, bad);
	पूर्ण अन्यथा अणु
		ceph_encode_32_safe(p, end, 0, bad);
	पूर्ण

	वापस 0;
bad:
	वापस -दुस्फल;
पूर्ण

अटल bool need_key(काष्ठा ceph_x_ticket_handler *th)
अणु
	अगर (!th->have_key)
		वापस true;

	वापस kसमय_get_real_seconds() >= th->renew_after;
पूर्ण

अटल bool have_key(काष्ठा ceph_x_ticket_handler *th)
अणु
	अगर (th->have_key && kसमय_get_real_seconds() >= th->expires) अणु
		करोut("ticket %d (%s) secret_id %llu expired\n", th->service,
		     ceph_entity_type_name(th->service), th->secret_id);
		th->have_key = false;
	पूर्ण

	वापस th->have_key;
पूर्ण

अटल व्योम ceph_x_validate_tickets(काष्ठा ceph_auth_client *ac, पूर्णांक *pneed)
अणु
	पूर्णांक want = ac->want_keys;
	काष्ठा ceph_x_info *xi = ac->निजी;
	पूर्णांक service;

	*pneed = ac->want_keys & ~(xi->have_keys);

	क्रम (service = 1; service <= want; service <<= 1) अणु
		काष्ठा ceph_x_ticket_handler *th;

		अगर (!(ac->want_keys & service))
			जारी;

		अगर (*pneed & service)
			जारी;

		th = get_ticket_handler(ac, service);
		अगर (IS_ERR(th)) अणु
			*pneed |= service;
			जारी;
		पूर्ण

		अगर (need_key(th))
			*pneed |= service;
		अगर (!have_key(th))
			xi->have_keys &= ~service;
	पूर्ण
पूर्ण

अटल पूर्णांक ceph_x_build_request(काष्ठा ceph_auth_client *ac,
				व्योम *buf, व्योम *end)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	पूर्णांक need;
	काष्ठा ceph_x_request_header *head = buf;
	व्योम *p;
	पूर्णांक ret;
	काष्ठा ceph_x_ticket_handler *th =
		get_ticket_handler(ac, CEPH_ENTITY_TYPE_AUTH);

	अगर (IS_ERR(th))
		वापस PTR_ERR(th);

	ceph_x_validate_tickets(ac, &need);
	करोut("%s want 0x%x have 0x%x need 0x%x\n", __func__, ac->want_keys,
	     xi->have_keys, need);

	अगर (need & CEPH_ENTITY_TYPE_AUTH) अणु
		काष्ठा ceph_x_authenticate *auth = (व्योम *)(head + 1);
		व्योम *enc_buf = xi->auth_authorizer.enc_buf;
		काष्ठा ceph_x_challenge_blob *blob = enc_buf +
							ceph_x_encrypt_offset();
		u64 *u;

		p = auth + 1;
		अगर (p > end)
			वापस -दुस्फल;

		करोut(" get_auth_session_key\n");
		head->op = cpu_to_le16(CEPHX_GET_AUTH_SESSION_KEY);

		/* encrypt and hash */
		get_अक्रमom_bytes(&auth->client_challenge, माप(u64));
		blob->client_challenge = auth->client_challenge;
		blob->server_challenge = cpu_to_le64(xi->server_challenge);
		ret = ceph_x_encrypt(&xi->secret, enc_buf, CEPHX_AU_ENC_BUF_LEN,
				     माप(*blob));
		अगर (ret < 0)
			वापस ret;

		auth->काष्ठा_v = 3;  /* nautilus+ */
		auth->key = 0;
		क्रम (u = (u64 *)enc_buf; u + 1 <= (u64 *)(enc_buf + ret); u++)
			auth->key ^= *(__le64 *)u;
		करोut(" server_challenge %llx client_challenge %llx key %llx\n",
		     xi->server_challenge, le64_to_cpu(auth->client_challenge),
		     le64_to_cpu(auth->key));

		/* now encode the old ticket अगर exists */
		ret = ceph_x_encode_ticket(th, &p, end);
		अगर (ret < 0)
			वापस ret;

		/* nautilus+: request service tickets at the same समय */
		need = ac->want_keys & ~CEPH_ENTITY_TYPE_AUTH;
		WARN_ON(!need);
		ceph_encode_32_safe(&p, end, need, e_range);
		वापस p - buf;
	पूर्ण

	अगर (need) अणु
		करोut(" get_principal_session_key\n");
		ret = ceph_x_build_authorizer(ac, th, &xi->auth_authorizer);
		अगर (ret)
			वापस ret;

		p = buf;
		ceph_encode_16_safe(&p, end, CEPHX_GET_PRINCIPAL_SESSION_KEY,
				    e_range);
		ceph_encode_copy_safe(&p, end,
			xi->auth_authorizer.buf->vec.iov_base,
			xi->auth_authorizer.buf->vec.iov_len, e_range);
		ceph_encode_8_safe(&p, end, 1, e_range);
		ceph_encode_32_safe(&p, end, need, e_range);
		वापस p - buf;
	पूर्ण

	वापस 0;

e_range:
	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक decode_con_secret(व्योम **p, व्योम *end, u8 *con_secret,
			     पूर्णांक *con_secret_len)
अणु
	पूर्णांक len;

	ceph_decode_32_safe(p, end, len, bad);
	ceph_decode_need(p, end, len, bad);

	करोut("%s len %d\n", __func__, len);
	अगर (con_secret) अणु
		अगर (len > CEPH_MAX_CON_SECRET_LEN) अणु
			pr_err("connection secret too big %d\n", len);
			जाओ bad_memzero;
		पूर्ण
		स_नकल(con_secret, *p, len);
		*con_secret_len = len;
	पूर्ण
	memzero_explicit(*p, len);
	*p += len;
	वापस 0;

bad_memzero:
	memzero_explicit(*p, len);
bad:
	pr_err("failed to decode connection secret\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक handle_auth_session_key(काष्ठा ceph_auth_client *ac,
				   व्योम **p, व्योम *end,
				   u8 *session_key, पूर्णांक *session_key_len,
				   u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	काष्ठा ceph_x_ticket_handler *th;
	व्योम *dp, *dend;
	पूर्णांक len;
	पूर्णांक ret;

	/* AUTH ticket */
	ret = ceph_x_proc_ticket_reply(ac, &xi->secret, p, end);
	अगर (ret)
		वापस ret;

	अगर (*p == end) अणु
		/* pre-nautilus (or didn't request service tickets!) */
		WARN_ON(session_key || con_secret);
		वापस 0;
	पूर्ण

	th = get_ticket_handler(ac, CEPH_ENTITY_TYPE_AUTH);
	अगर (IS_ERR(th))
		वापस PTR_ERR(th);

	अगर (session_key) अणु
		स_नकल(session_key, th->session_key.key, th->session_key.len);
		*session_key_len = th->session_key.len;
	पूर्ण

	/* connection secret */
	ceph_decode_32_safe(p, end, len, e_inval);
	करोut("%s connection secret blob len %d\n", __func__, len);
	अगर (len > 0) अणु
		dp = *p + ceph_x_encrypt_offset();
		ret = ceph_x_decrypt(&th->session_key, p, *p + len);
		अगर (ret < 0)
			वापस ret;

		करोut("%s decrypted %d bytes\n", __func__, ret);
		dend = dp + ret;

		ret = decode_con_secret(&dp, dend, con_secret, con_secret_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* service tickets */
	ceph_decode_32_safe(p, end, len, e_inval);
	करोut("%s service tickets blob len %d\n", __func__, len);
	अगर (len > 0) अणु
		ret = ceph_x_proc_ticket_reply(ac, &th->session_key,
					       p, *p + len);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ceph_x_handle_reply(काष्ठा ceph_auth_client *ac, पूर्णांक result,
			       व्योम *buf, व्योम *end,
			       u8 *session_key, पूर्णांक *session_key_len,
			       u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	काष्ठा ceph_x_ticket_handler *th;
	पूर्णांक len = end - buf;
	व्योम *p;
	पूर्णांक op;
	पूर्णांक ret;

	अगर (result)
		वापस result;  /* XXX hmm? */

	अगर (xi->starting) अणु
		/* it's a hello */
		काष्ठा ceph_x_server_challenge *sc = buf;

		अगर (len != माप(*sc))
			वापस -EINVAL;
		xi->server_challenge = le64_to_cpu(sc->server_challenge);
		करोut("handle_reply got server challenge %llx\n",
		     xi->server_challenge);
		xi->starting = false;
		xi->have_keys &= ~CEPH_ENTITY_TYPE_AUTH;
		वापस -EAGAIN;
	पूर्ण

	p = buf;
	ceph_decode_16_safe(&p, end, op, e_inval);
	ceph_decode_32_safe(&p, end, result, e_inval);
	करोut("handle_reply op %d result %d\n", op, result);
	चयन (op) अणु
	हाल CEPHX_GET_AUTH_SESSION_KEY:
		/* AUTH ticket + [connection secret] + service tickets */
		ret = handle_auth_session_key(ac, &p, end, session_key,
					      session_key_len, con_secret,
					      con_secret_len);
		अवरोध;

	हाल CEPHX_GET_PRINCIPAL_SESSION_KEY:
		th = get_ticket_handler(ac, CEPH_ENTITY_TYPE_AUTH);
		अगर (IS_ERR(th))
			वापस PTR_ERR(th);

		/* service tickets */
		ret = ceph_x_proc_ticket_reply(ac, &th->session_key, &p, end);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (ret)
		वापस ret;
	अगर (ac->want_keys == xi->have_keys)
		वापस 0;
	वापस -EAGAIN;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल व्योम ceph_x_destroy_authorizer(काष्ठा ceph_authorizer *a)
अणु
	काष्ठा ceph_x_authorizer *au = (व्योम *)a;

	ceph_x_authorizer_cleanup(au);
	kमुक्त(au);
पूर्ण

अटल पूर्णांक ceph_x_create_authorizer(
	काष्ठा ceph_auth_client *ac, पूर्णांक peer_type,
	काष्ठा ceph_auth_handshake *auth)
अणु
	काष्ठा ceph_x_authorizer *au;
	काष्ठा ceph_x_ticket_handler *th;
	पूर्णांक ret;

	th = get_ticket_handler(ac, peer_type);
	अगर (IS_ERR(th))
		वापस PTR_ERR(th);

	au = kzalloc(माप(*au), GFP_NOFS);
	अगर (!au)
		वापस -ENOMEM;

	au->base.destroy = ceph_x_destroy_authorizer;

	ret = ceph_x_build_authorizer(ac, th, au);
	अगर (ret) अणु
		kमुक्त(au);
		वापस ret;
	पूर्ण

	auth->authorizer = (काष्ठा ceph_authorizer *) au;
	auth->authorizer_buf = au->buf->vec.iov_base;
	auth->authorizer_buf_len = au->buf->vec.iov_len;
	auth->authorizer_reply_buf = au->enc_buf;
	auth->authorizer_reply_buf_len = CEPHX_AU_ENC_BUF_LEN;
	auth->sign_message = ac->ops->sign_message;
	auth->check_message_signature = ac->ops->check_message_signature;

	वापस 0;
पूर्ण

अटल पूर्णांक ceph_x_update_authorizer(
	काष्ठा ceph_auth_client *ac, पूर्णांक peer_type,
	काष्ठा ceph_auth_handshake *auth)
अणु
	काष्ठा ceph_x_authorizer *au;
	काष्ठा ceph_x_ticket_handler *th;

	th = get_ticket_handler(ac, peer_type);
	अगर (IS_ERR(th))
		वापस PTR_ERR(th);

	au = (काष्ठा ceph_x_authorizer *)auth->authorizer;
	अगर (au->secret_id < th->secret_id) अणु
		करोut("ceph_x_update_authorizer service %u secret %llu < %llu\n",
		     au->service, au->secret_id, th->secret_id);
		वापस ceph_x_build_authorizer(ac, th, au);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * CephXAuthorizeChallenge
 */
अटल पूर्णांक decrypt_authorizer_challenge(काष्ठा ceph_crypto_key *secret,
					व्योम *challenge, पूर्णांक challenge_len,
					u64 *server_challenge)
अणु
	व्योम *dp, *dend;
	पूर्णांक ret;

	/* no leading len */
	ret = __ceph_x_decrypt(secret, challenge, challenge_len);
	अगर (ret < 0)
		वापस ret;

	करोut("%s decrypted %d bytes\n", __func__, ret);
	dp = challenge + माप(काष्ठा ceph_x_encrypt_header);
	dend = dp + ret;

	ceph_decode_skip_8(&dp, dend, e_inval);  /* काष्ठा_v */
	ceph_decode_64_safe(&dp, dend, *server_challenge, e_inval);
	करोut("%s server_challenge %llu\n", __func__, *server_challenge);
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ceph_x_add_authorizer_challenge(काष्ठा ceph_auth_client *ac,
					   काष्ठा ceph_authorizer *a,
					   व्योम *challenge, पूर्णांक challenge_len)
अणु
	काष्ठा ceph_x_authorizer *au = (व्योम *)a;
	u64 server_challenge;
	पूर्णांक ret;

	ret = decrypt_authorizer_challenge(&au->session_key, challenge,
					   challenge_len, &server_challenge);
	अगर (ret) अणु
		pr_err("failed to decrypt authorize challenge: %d", ret);
		वापस ret;
	पूर्ण

	ret = encrypt_authorizer(au, &server_challenge);
	अगर (ret) अणु
		pr_err("failed to encrypt authorizer w/ challenge: %d", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * CephXAuthorizeReply
 */
अटल पूर्णांक decrypt_authorizer_reply(काष्ठा ceph_crypto_key *secret,
				    व्योम **p, व्योम *end, u64 *nonce_plus_one,
				    u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	व्योम *dp, *dend;
	u8 काष्ठा_v;
	पूर्णांक ret;

	dp = *p + ceph_x_encrypt_offset();
	ret = ceph_x_decrypt(secret, p, end);
	अगर (ret < 0)
		वापस ret;

	करोut("%s decrypted %d bytes\n", __func__, ret);
	dend = dp + ret;

	ceph_decode_8_safe(&dp, dend, काष्ठा_v, e_inval);
	ceph_decode_64_safe(&dp, dend, *nonce_plus_one, e_inval);
	करोut("%s nonce_plus_one %llu\n", __func__, *nonce_plus_one);
	अगर (काष्ठा_v >= 2) अणु
		ret = decode_con_secret(&dp, dend, con_secret, con_secret_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ceph_x_verअगरy_authorizer_reply(काष्ठा ceph_auth_client *ac,
					  काष्ठा ceph_authorizer *a,
					  व्योम *reply, पूर्णांक reply_len,
					  u8 *session_key, पूर्णांक *session_key_len,
					  u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_x_authorizer *au = (व्योम *)a;
	u64 nonce_plus_one;
	पूर्णांक ret;

	अगर (session_key) अणु
		स_नकल(session_key, au->session_key.key, au->session_key.len);
		*session_key_len = au->session_key.len;
	पूर्ण

	ret = decrypt_authorizer_reply(&au->session_key, &reply,
				       reply + reply_len, &nonce_plus_one,
				       con_secret, con_secret_len);
	अगर (ret)
		वापस ret;

	अगर (nonce_plus_one != au->nonce + 1) अणु
		pr_err("failed to authenticate server\n");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ceph_x_reset(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;

	करोut("reset\n");
	xi->starting = true;
	xi->server_challenge = 0;
पूर्ण

अटल व्योम ceph_x_destroy(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_x_info *xi = ac->निजी;
	काष्ठा rb_node *p;

	करोut("ceph_x_destroy %p\n", ac);
	ceph_crypto_key_destroy(&xi->secret);

	जबतक ((p = rb_first(&xi->ticket_handlers)) != शून्य) अणु
		काष्ठा ceph_x_ticket_handler *th =
			rb_entry(p, काष्ठा ceph_x_ticket_handler, node);
		हटाओ_ticket_handler(ac, th);
	पूर्ण

	ceph_x_authorizer_cleanup(&xi->auth_authorizer);

	kमुक्त(ac->निजी);
	ac->निजी = शून्य;
पूर्ण

अटल व्योम invalidate_ticket(काष्ठा ceph_auth_client *ac, पूर्णांक peer_type)
अणु
	काष्ठा ceph_x_ticket_handler *th;

	th = get_ticket_handler(ac, peer_type);
	अगर (IS_ERR(th))
		वापस;

	अगर (th->have_key) अणु
		करोut("ticket %d (%s) secret_id %llu invalidated\n",
		     th->service, ceph_entity_type_name(th->service),
		     th->secret_id);
		th->have_key = false;
	पूर्ण
पूर्ण

अटल व्योम ceph_x_invalidate_authorizer(काष्ठा ceph_auth_client *ac,
					 पूर्णांक peer_type)
अणु
	/*
	 * We are to invalidate a service ticket in the hopes of
	 * getting a new, hopefully more valid, one.  But, we won't get
	 * it unless our AUTH ticket is good, so invalidate AUTH ticket
	 * as well, just in हाल.
	 */
	invalidate_ticket(ac, peer_type);
	invalidate_ticket(ac, CEPH_ENTITY_TYPE_AUTH);
पूर्ण

अटल पूर्णांक calc_signature(काष्ठा ceph_x_authorizer *au, काष्ठा ceph_msg *msg,
			  __le64 *psig)
अणु
	व्योम *enc_buf = au->enc_buf;
	पूर्णांक ret;

	अगर (!CEPH_HAVE_FEATURE(msg->con->peer_features, CEPHX_V2)) अणु
		काष्ठा अणु
			__le32 len;
			__le32 header_crc;
			__le32 front_crc;
			__le32 middle_crc;
			__le32 data_crc;
		पूर्ण __packed *sigblock = enc_buf + ceph_x_encrypt_offset();

		sigblock->len = cpu_to_le32(4*माप(u32));
		sigblock->header_crc = msg->hdr.crc;
		sigblock->front_crc = msg->footer.front_crc;
		sigblock->middle_crc = msg->footer.middle_crc;
		sigblock->data_crc =  msg->footer.data_crc;

		ret = ceph_x_encrypt(&au->session_key, enc_buf,
				     CEPHX_AU_ENC_BUF_LEN, माप(*sigblock));
		अगर (ret < 0)
			वापस ret;

		*psig = *(__le64 *)(enc_buf + माप(u32));
	पूर्ण अन्यथा अणु
		काष्ठा अणु
			__le32 header_crc;
			__le32 front_crc;
			__le32 front_len;
			__le32 middle_crc;
			__le32 middle_len;
			__le32 data_crc;
			__le32 data_len;
			__le32 seq_lower_word;
		पूर्ण __packed *sigblock = enc_buf;
		काष्ठा अणु
			__le64 a, b, c, d;
		पूर्ण __packed *penc = enc_buf;
		पूर्णांक ciphertext_len;

		sigblock->header_crc = msg->hdr.crc;
		sigblock->front_crc = msg->footer.front_crc;
		sigblock->front_len = msg->hdr.front_len;
		sigblock->middle_crc = msg->footer.middle_crc;
		sigblock->middle_len = msg->hdr.middle_len;
		sigblock->data_crc =  msg->footer.data_crc;
		sigblock->data_len = msg->hdr.data_len;
		sigblock->seq_lower_word = *(__le32 *)&msg->hdr.seq;

		/* no leading len, no ceph_x_encrypt_header */
		ret = ceph_crypt(&au->session_key, true, enc_buf,
				 CEPHX_AU_ENC_BUF_LEN, माप(*sigblock),
				 &ciphertext_len);
		अगर (ret)
			वापस ret;

		*psig = penc->a ^ penc->b ^ penc->c ^ penc->d;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ceph_x_sign_message(काष्ठा ceph_auth_handshake *auth,
			       काष्ठा ceph_msg *msg)
अणु
	__le64 sig;
	पूर्णांक ret;

	अगर (ceph_test_opt(from_msgr(msg->con->msgr), NOMSGSIGN))
		वापस 0;

	ret = calc_signature((काष्ठा ceph_x_authorizer *)auth->authorizer,
			     msg, &sig);
	अगर (ret)
		वापस ret;

	msg->footer.sig = sig;
	msg->footer.flags |= CEPH_MSG_FOOTER_SIGNED;
	वापस 0;
पूर्ण

अटल पूर्णांक ceph_x_check_message_signature(काष्ठा ceph_auth_handshake *auth,
					  काष्ठा ceph_msg *msg)
अणु
	__le64 sig_check;
	पूर्णांक ret;

	अगर (ceph_test_opt(from_msgr(msg->con->msgr), NOMSGSIGN))
		वापस 0;

	ret = calc_signature((काष्ठा ceph_x_authorizer *)auth->authorizer,
			     msg, &sig_check);
	अगर (ret)
		वापस ret;
	अगर (sig_check == msg->footer.sig)
		वापस 0;
	अगर (msg->footer.flags & CEPH_MSG_FOOTER_SIGNED)
		करोut("ceph_x_check_message_signature %p has signature %llx "
		     "expect %llx\n", msg, msg->footer.sig, sig_check);
	अन्यथा
		करोut("ceph_x_check_message_signature %p sender did not set "
		     "CEPH_MSG_FOOTER_SIGNED\n", msg);
	वापस -EBADMSG;
पूर्ण

अटल स्थिर काष्ठा ceph_auth_client_ops ceph_x_ops = अणु
	.is_authenticated = ceph_x_is_authenticated,
	.should_authenticate = ceph_x_should_authenticate,
	.build_request = ceph_x_build_request,
	.handle_reply = ceph_x_handle_reply,
	.create_authorizer = ceph_x_create_authorizer,
	.update_authorizer = ceph_x_update_authorizer,
	.add_authorizer_challenge = ceph_x_add_authorizer_challenge,
	.verअगरy_authorizer_reply = ceph_x_verअगरy_authorizer_reply,
	.invalidate_authorizer = ceph_x_invalidate_authorizer,
	.reset =  ceph_x_reset,
	.destroy = ceph_x_destroy,
	.sign_message = ceph_x_sign_message,
	.check_message_signature = ceph_x_check_message_signature,
पूर्ण;


पूर्णांक ceph_x_init(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_x_info *xi;
	पूर्णांक ret;

	करोut("ceph_x_init %p\n", ac);
	ret = -ENOMEM;
	xi = kzalloc(माप(*xi), GFP_NOFS);
	अगर (!xi)
		जाओ out;

	ret = -EINVAL;
	अगर (!ac->key) अणु
		pr_err("no secret set (for auth_x protocol)\n");
		जाओ out_nomem;
	पूर्ण

	ret = ceph_crypto_key_clone(&xi->secret, ac->key);
	अगर (ret < 0) अणु
		pr_err("cannot clone key: %d\n", ret);
		जाओ out_nomem;
	पूर्ण

	xi->starting = true;
	xi->ticket_handlers = RB_ROOT;

	ac->protocol = CEPH_AUTH_CEPHX;
	ac->निजी = xi;
	ac->ops = &ceph_x_ops;
	वापस 0;

out_nomem:
	kमुक्त(xi);
out:
	वापस ret;
पूर्ण
