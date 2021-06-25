<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RSA padding ढाँचाs.
 *
 * Copyright (c) 2015  Intel Corporation
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/scatterlist.h>

/*
 * Hash algorithm OIDs plus ASN.1 DER wrappings [RFC4880 sec 5.2.2].
 */
अटल स्थिर u8 rsa_digest_info_md5[] = अणु
	0x30, 0x20, 0x30, 0x0c, 0x06, 0x08,
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05, /* OID */
	0x05, 0x00, 0x04, 0x10
पूर्ण;

अटल स्थिर u8 rsa_digest_info_sha1[] = अणु
	0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
	0x2b, 0x0e, 0x03, 0x02, 0x1a,
	0x05, 0x00, 0x04, 0x14
पूर्ण;

अटल स्थिर u8 rsa_digest_info_rmd160[] = अणु
	0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
	0x2b, 0x24, 0x03, 0x02, 0x01,
	0x05, 0x00, 0x04, 0x14
पूर्ण;

अटल स्थिर u8 rsa_digest_info_sha224[] = अणु
	0x30, 0x2d, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x04,
	0x05, 0x00, 0x04, 0x1c
पूर्ण;

अटल स्थिर u8 rsa_digest_info_sha256[] = अणु
	0x30, 0x31, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01,
	0x05, 0x00, 0x04, 0x20
पूर्ण;

अटल स्थिर u8 rsa_digest_info_sha384[] = अणु
	0x30, 0x41, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02,
	0x05, 0x00, 0x04, 0x30
पूर्ण;

अटल स्थिर u8 rsa_digest_info_sha512[] = अणु
	0x30, 0x51, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03,
	0x05, 0x00, 0x04, 0x40
पूर्ण;

अटल स्थिर काष्ठा rsa_asn1_ढाँचा अणु
	स्थिर अक्षर	*name;
	स्थिर u8	*data;
	माप_प्रकार		size;
पूर्ण rsa_asn1_ढाँचाs[] = अणु
#घोषणा _(X) अणु #X, rsa_digest_info_##X, माप(rsa_digest_info_##X) पूर्ण
	_(md5),
	_(sha1),
	_(rmd160),
	_(sha256),
	_(sha384),
	_(sha512),
	_(sha224),
	अणु शून्य पूर्ण
#अघोषित _
पूर्ण;

अटल स्थिर काष्ठा rsa_asn1_ढाँचा *rsa_lookup_asn1(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा rsa_asn1_ढाँचा *p;

	क्रम (p = rsa_asn1_ढाँचाs; p->name; p++)
		अगर (म_भेद(name, p->name) == 0)
			वापस p;
	वापस शून्य;
पूर्ण

काष्ठा pkcs1pad_ctx अणु
	काष्ठा crypto_akcipher *child;
	अचिन्हित पूर्णांक key_size;
पूर्ण;

काष्ठा pkcs1pad_inst_ctx अणु
	काष्ठा crypto_akcipher_spawn spawn;
	स्थिर काष्ठा rsa_asn1_ढाँचा *digest_info;
पूर्ण;

काष्ठा pkcs1pad_request अणु
	काष्ठा scatterlist in_sg[2], out_sg[1];
	uपूर्णांक8_t *in_buf, *out_buf;
	काष्ठा akcipher_request child_req;
पूर्ण;

अटल पूर्णांक pkcs1pad_set_pub_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
		अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	पूर्णांक err;

	ctx->key_size = 0;

	err = crypto_akcipher_set_pub_key(ctx->child, key, keylen);
	अगर (err)
		वापस err;

	/* Find out new modulus size from rsa implementation */
	err = crypto_akcipher_maxsize(ctx->child);
	अगर (err > PAGE_SIZE)
		वापस -ENOTSUPP;

	ctx->key_size = err;
	वापस 0;
पूर्ण

अटल पूर्णांक pkcs1pad_set_priv_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
		अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	पूर्णांक err;

	ctx->key_size = 0;

	err = crypto_akcipher_set_priv_key(ctx->child, key, keylen);
	अगर (err)
		वापस err;

	/* Find out new modulus size from rsa implementation */
	err = crypto_akcipher_maxsize(ctx->child);
	अगर (err > PAGE_SIZE)
		वापस -ENOTSUPP;

	ctx->key_size = err;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pkcs1pad_get_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);

	/*
	 * The maximum destination buffer size क्रम the encrypt/sign operations
	 * will be the same as क्रम RSA, even though it's smaller क्रम
	 * decrypt/verअगरy.
	 */

	वापस ctx->key_size;
पूर्ण

अटल व्योम pkcs1pad_sg_set_buf(काष्ठा scatterlist *sg, व्योम *buf, माप_प्रकार len,
		काष्ठा scatterlist *next)
अणु
	पूर्णांक nsegs = next ? 2 : 1;

	sg_init_table(sg, nsegs);
	sg_set_buf(sg, buf, len);

	अगर (next)
		sg_chain(sg, nsegs, next);
पूर्ण

अटल पूर्णांक pkcs1pad_encrypt_sign_complete(काष्ठा akcipher_request *req, पूर्णांक err)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	अचिन्हित पूर्णांक pad_len;
	अचिन्हित पूर्णांक len;
	u8 *out_buf;

	अगर (err)
		जाओ out;

	len = req_ctx->child_req.dst_len;
	pad_len = ctx->key_size - len;

	/* Four billion to one */
	अगर (likely(!pad_len))
		जाओ out;

	out_buf = kzalloc(ctx->key_size, GFP_KERNEL);
	err = -ENOMEM;
	अगर (!out_buf)
		जाओ out;

	sg_copy_to_buffer(req->dst, sg_nents_क्रम_len(req->dst, len),
			  out_buf + pad_len, len);
	sg_copy_from_buffer(req->dst,
			    sg_nents_क्रम_len(req->dst, ctx->key_size),
			    out_buf, ctx->key_size);
	kमुक्त_sensitive(out_buf);

out:
	req->dst_len = ctx->key_size;

	kमुक्त(req_ctx->in_buf);

	वापस err;
पूर्ण

अटल व्योम pkcs1pad_encrypt_sign_complete_cb(
		काष्ठा crypto_async_request *child_async_req, पूर्णांक err)
अणु
	काष्ठा akcipher_request *req = child_async_req->data;
	काष्ठा crypto_async_request async_req;

	अगर (err == -EINPROGRESS)
		वापस;

	async_req.data = req->base.data;
	async_req.tfm = crypto_akcipher_tfm(crypto_akcipher_reqtfm(req));
	async_req.flags = child_async_req->flags;
	req->base.complete(&async_req,
			pkcs1pad_encrypt_sign_complete(req, err));
पूर्ण

अटल पूर्णांक pkcs1pad_encrypt(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	पूर्णांक err;
	अचिन्हित पूर्णांक i, ps_end;

	अगर (!ctx->key_size)
		वापस -EINVAL;

	अगर (req->src_len > ctx->key_size - 11)
		वापस -EOVERFLOW;

	अगर (req->dst_len < ctx->key_size) अणु
		req->dst_len = ctx->key_size;
		वापस -EOVERFLOW;
	पूर्ण

	req_ctx->in_buf = kदो_स्मृति(ctx->key_size - 1 - req->src_len,
				  GFP_KERNEL);
	अगर (!req_ctx->in_buf)
		वापस -ENOMEM;

	ps_end = ctx->key_size - req->src_len - 2;
	req_ctx->in_buf[0] = 0x02;
	क्रम (i = 1; i < ps_end; i++)
		req_ctx->in_buf[i] = 1 + pअक्रमom_u32_max(255);
	req_ctx->in_buf[ps_end] = 0x00;

	pkcs1pad_sg_set_buf(req_ctx->in_sg, req_ctx->in_buf,
			ctx->key_size - 1 - req->src_len, req->src);

	akcipher_request_set_tfm(&req_ctx->child_req, ctx->child);
	akcipher_request_set_callback(&req_ctx->child_req, req->base.flags,
			pkcs1pad_encrypt_sign_complete_cb, req);

	/* Reuse output buffer */
	akcipher_request_set_crypt(&req_ctx->child_req, req_ctx->in_sg,
				   req->dst, ctx->key_size - 1, req->dst_len);

	err = crypto_akcipher_encrypt(&req_ctx->child_req);
	अगर (err != -EINPROGRESS && err != -EBUSY)
		वापस pkcs1pad_encrypt_sign_complete(req, err);

	वापस err;
पूर्ण

अटल पूर्णांक pkcs1pad_decrypt_complete(काष्ठा akcipher_request *req, पूर्णांक err)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	अचिन्हित पूर्णांक dst_len;
	अचिन्हित पूर्णांक pos;
	u8 *out_buf;

	अगर (err)
		जाओ करोne;

	err = -EINVAL;
	dst_len = req_ctx->child_req.dst_len;
	अगर (dst_len < ctx->key_size - 1)
		जाओ करोne;

	out_buf = req_ctx->out_buf;
	अगर (dst_len == ctx->key_size) अणु
		अगर (out_buf[0] != 0x00)
			/* Decrypted value had no leading 0 byte */
			जाओ करोne;

		dst_len--;
		out_buf++;
	पूर्ण

	अगर (out_buf[0] != 0x02)
		जाओ करोne;

	क्रम (pos = 1; pos < dst_len; pos++)
		अगर (out_buf[pos] == 0x00)
			अवरोध;
	अगर (pos < 9 || pos == dst_len)
		जाओ करोne;
	pos++;

	err = 0;

	अगर (req->dst_len < dst_len - pos)
		err = -EOVERFLOW;
	req->dst_len = dst_len - pos;

	अगर (!err)
		sg_copy_from_buffer(req->dst,
				sg_nents_क्रम_len(req->dst, req->dst_len),
				out_buf + pos, req->dst_len);

करोne:
	kमुक्त_sensitive(req_ctx->out_buf);

	वापस err;
पूर्ण

अटल व्योम pkcs1pad_decrypt_complete_cb(
		काष्ठा crypto_async_request *child_async_req, पूर्णांक err)
अणु
	काष्ठा akcipher_request *req = child_async_req->data;
	काष्ठा crypto_async_request async_req;

	अगर (err == -EINPROGRESS)
		वापस;

	async_req.data = req->base.data;
	async_req.tfm = crypto_akcipher_tfm(crypto_akcipher_reqtfm(req));
	async_req.flags = child_async_req->flags;
	req->base.complete(&async_req, pkcs1pad_decrypt_complete(req, err));
पूर्ण

अटल पूर्णांक pkcs1pad_decrypt(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	पूर्णांक err;

	अगर (!ctx->key_size || req->src_len != ctx->key_size)
		वापस -EINVAL;

	req_ctx->out_buf = kदो_स्मृति(ctx->key_size, GFP_KERNEL);
	अगर (!req_ctx->out_buf)
		वापस -ENOMEM;

	pkcs1pad_sg_set_buf(req_ctx->out_sg, req_ctx->out_buf,
			    ctx->key_size, शून्य);

	akcipher_request_set_tfm(&req_ctx->child_req, ctx->child);
	akcipher_request_set_callback(&req_ctx->child_req, req->base.flags,
			pkcs1pad_decrypt_complete_cb, req);

	/* Reuse input buffer, output to a new buffer */
	akcipher_request_set_crypt(&req_ctx->child_req, req->src,
				   req_ctx->out_sg, req->src_len,
				   ctx->key_size);

	err = crypto_akcipher_decrypt(&req_ctx->child_req);
	अगर (err != -EINPROGRESS && err != -EBUSY)
		वापस pkcs1pad_decrypt_complete(req, err);

	वापस err;
पूर्ण

अटल पूर्णांक pkcs1pad_sign(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	काष्ठा akcipher_instance *inst = akcipher_alg_instance(tfm);
	काष्ठा pkcs1pad_inst_ctx *ictx = akcipher_instance_ctx(inst);
	स्थिर काष्ठा rsa_asn1_ढाँचा *digest_info = ictx->digest_info;
	पूर्णांक err;
	अचिन्हित पूर्णांक ps_end, digest_size = 0;

	अगर (!ctx->key_size)
		वापस -EINVAL;

	अगर (digest_info)
		digest_size = digest_info->size;

	अगर (req->src_len + digest_size > ctx->key_size - 11)
		वापस -EOVERFLOW;

	अगर (req->dst_len < ctx->key_size) अणु
		req->dst_len = ctx->key_size;
		वापस -EOVERFLOW;
	पूर्ण

	req_ctx->in_buf = kदो_स्मृति(ctx->key_size - 1 - req->src_len,
				  GFP_KERNEL);
	अगर (!req_ctx->in_buf)
		वापस -ENOMEM;

	ps_end = ctx->key_size - digest_size - req->src_len - 2;
	req_ctx->in_buf[0] = 0x01;
	स_रखो(req_ctx->in_buf + 1, 0xff, ps_end - 1);
	req_ctx->in_buf[ps_end] = 0x00;

	अगर (digest_info)
		स_नकल(req_ctx->in_buf + ps_end + 1, digest_info->data,
		       digest_info->size);

	pkcs1pad_sg_set_buf(req_ctx->in_sg, req_ctx->in_buf,
			ctx->key_size - 1 - req->src_len, req->src);

	akcipher_request_set_tfm(&req_ctx->child_req, ctx->child);
	akcipher_request_set_callback(&req_ctx->child_req, req->base.flags,
			pkcs1pad_encrypt_sign_complete_cb, req);

	/* Reuse output buffer */
	akcipher_request_set_crypt(&req_ctx->child_req, req_ctx->in_sg,
				   req->dst, ctx->key_size - 1, req->dst_len);

	err = crypto_akcipher_decrypt(&req_ctx->child_req);
	अगर (err != -EINPROGRESS && err != -EBUSY)
		वापस pkcs1pad_encrypt_sign_complete(req, err);

	वापस err;
पूर्ण

अटल पूर्णांक pkcs1pad_verअगरy_complete(काष्ठा akcipher_request *req, पूर्णांक err)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	काष्ठा akcipher_instance *inst = akcipher_alg_instance(tfm);
	काष्ठा pkcs1pad_inst_ctx *ictx = akcipher_instance_ctx(inst);
	स्थिर काष्ठा rsa_asn1_ढाँचा *digest_info = ictx->digest_info;
	अचिन्हित पूर्णांक dst_len;
	अचिन्हित पूर्णांक pos;
	u8 *out_buf;

	अगर (err)
		जाओ करोne;

	err = -EINVAL;
	dst_len = req_ctx->child_req.dst_len;
	अगर (dst_len < ctx->key_size - 1)
		जाओ करोne;

	out_buf = req_ctx->out_buf;
	अगर (dst_len == ctx->key_size) अणु
		अगर (out_buf[0] != 0x00)
			/* Decrypted value had no leading 0 byte */
			जाओ करोne;

		dst_len--;
		out_buf++;
	पूर्ण

	err = -EBADMSG;
	अगर (out_buf[0] != 0x01)
		जाओ करोne;

	क्रम (pos = 1; pos < dst_len; pos++)
		अगर (out_buf[pos] != 0xff)
			अवरोध;

	अगर (pos < 9 || pos == dst_len || out_buf[pos] != 0x00)
		जाओ करोne;
	pos++;

	अगर (digest_info) अणु
		अगर (crypto_memneq(out_buf + pos, digest_info->data,
				  digest_info->size))
			जाओ करोne;

		pos += digest_info->size;
	पूर्ण

	err = 0;

	अगर (req->dst_len != dst_len - pos) अणु
		err = -EKEYREJECTED;
		req->dst_len = dst_len - pos;
		जाओ करोne;
	पूर्ण
	/* Extract appended digest. */
	sg_pcopy_to_buffer(req->src,
			   sg_nents_क्रम_len(req->src,
					    req->src_len + req->dst_len),
			   req_ctx->out_buf + ctx->key_size,
			   req->dst_len, ctx->key_size);
	/* Do the actual verअगरication step. */
	अगर (स_भेद(req_ctx->out_buf + ctx->key_size, out_buf + pos,
		   req->dst_len) != 0)
		err = -EKEYREJECTED;
करोne:
	kमुक्त_sensitive(req_ctx->out_buf);

	वापस err;
पूर्ण

अटल व्योम pkcs1pad_verअगरy_complete_cb(
		काष्ठा crypto_async_request *child_async_req, पूर्णांक err)
अणु
	काष्ठा akcipher_request *req = child_async_req->data;
	काष्ठा crypto_async_request async_req;

	अगर (err == -EINPROGRESS)
		वापस;

	async_req.data = req->base.data;
	async_req.tfm = crypto_akcipher_tfm(crypto_akcipher_reqtfm(req));
	async_req.flags = child_async_req->flags;
	req->base.complete(&async_req, pkcs1pad_verअगरy_complete(req, err));
पूर्ण

/*
 * The verअगरy operation is here क्रम completeness similar to the verअगरication
 * defined in RFC2313 section 10.2 except that block type 0 is not accepted,
 * as in RFC2437.  RFC2437 section 9.2 करोesn't define any operation to
 * retrieve the DigestInfo from a signature, instead the user is expected
 * to call the sign operation to generate the expected signature and compare
 * signatures instead of the message-digests.
 */
अटल पूर्णांक pkcs1pad_verअगरy(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	पूर्णांक err;

	अगर (WARN_ON(req->dst) ||
	    WARN_ON(!req->dst_len) ||
	    !ctx->key_size || req->src_len < ctx->key_size)
		वापस -EINVAL;

	req_ctx->out_buf = kदो_स्मृति(ctx->key_size + req->dst_len, GFP_KERNEL);
	अगर (!req_ctx->out_buf)
		वापस -ENOMEM;

	pkcs1pad_sg_set_buf(req_ctx->out_sg, req_ctx->out_buf,
			    ctx->key_size, शून्य);

	akcipher_request_set_tfm(&req_ctx->child_req, ctx->child);
	akcipher_request_set_callback(&req_ctx->child_req, req->base.flags,
			pkcs1pad_verअगरy_complete_cb, req);

	/* Reuse input buffer, output to a new buffer */
	akcipher_request_set_crypt(&req_ctx->child_req, req->src,
				   req_ctx->out_sg, req->src_len,
				   ctx->key_size);

	err = crypto_akcipher_encrypt(&req_ctx->child_req);
	अगर (err != -EINPROGRESS && err != -EBUSY)
		वापस pkcs1pad_verअगरy_complete(req, err);

	वापस err;
पूर्ण

अटल पूर्णांक pkcs1pad_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा akcipher_instance *inst = akcipher_alg_instance(tfm);
	काष्ठा pkcs1pad_inst_ctx *ictx = akcipher_instance_ctx(inst);
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा crypto_akcipher *child_tfm;

	child_tfm = crypto_spawn_akcipher(&ictx->spawn);
	अगर (IS_ERR(child_tfm))
		वापस PTR_ERR(child_tfm);

	ctx->child = child_tfm;
	वापस 0;
पूर्ण

अटल व्योम pkcs1pad_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);

	crypto_मुक्त_akcipher(ctx->child);
पूर्ण

अटल व्योम pkcs1pad_मुक्त(काष्ठा akcipher_instance *inst)
अणु
	काष्ठा pkcs1pad_inst_ctx *ctx = akcipher_instance_ctx(inst);
	काष्ठा crypto_akcipher_spawn *spawn = &ctx->spawn;

	crypto_drop_akcipher(spawn);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक pkcs1pad_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	u32 mask;
	काष्ठा akcipher_instance *inst;
	काष्ठा pkcs1pad_inst_ctx *ctx;
	काष्ठा akcipher_alg *rsa_alg;
	स्थिर अक्षर *hash_name;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AKCIPHER, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	ctx = akcipher_instance_ctx(inst);

	err = crypto_grab_akcipher(&ctx->spawn, akcipher_crypto_instance(inst),
				   crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	rsa_alg = crypto_spawn_akcipher_alg(&ctx->spawn);

	err = -ENAMETOOLONG;
	hash_name = crypto_attr_alg_name(tb[2]);
	अगर (IS_ERR(hash_name)) अणु
		अगर (snम_लिखो(inst->alg.base.cra_name,
			     CRYPTO_MAX_ALG_NAME, "pkcs1pad(%s)",
			     rsa_alg->base.cra_name) >= CRYPTO_MAX_ALG_NAME)
			जाओ err_मुक्त_inst;

		अगर (snम_लिखो(inst->alg.base.cra_driver_name,
			     CRYPTO_MAX_ALG_NAME, "pkcs1pad(%s)",
			     rsa_alg->base.cra_driver_name) >=
			     CRYPTO_MAX_ALG_NAME)
			जाओ err_मुक्त_inst;
	पूर्ण अन्यथा अणु
		ctx->digest_info = rsa_lookup_asn1(hash_name);
		अगर (!ctx->digest_info) अणु
			err = -EINVAL;
			जाओ err_मुक्त_inst;
		पूर्ण

		अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
			     "pkcs1pad(%s,%s)", rsa_alg->base.cra_name,
			     hash_name) >= CRYPTO_MAX_ALG_NAME)
			जाओ err_मुक्त_inst;

		अगर (snम_लिखो(inst->alg.base.cra_driver_name,
			     CRYPTO_MAX_ALG_NAME, "pkcs1pad(%s,%s)",
			     rsa_alg->base.cra_driver_name,
			     hash_name) >= CRYPTO_MAX_ALG_NAME)
			जाओ err_मुक्त_inst;
	पूर्ण

	inst->alg.base.cra_priority = rsa_alg->base.cra_priority;
	inst->alg.base.cra_ctxsize = माप(काष्ठा pkcs1pad_ctx);

	inst->alg.init = pkcs1pad_init_tfm;
	inst->alg.निकास = pkcs1pad_निकास_tfm;

	inst->alg.encrypt = pkcs1pad_encrypt;
	inst->alg.decrypt = pkcs1pad_decrypt;
	inst->alg.sign = pkcs1pad_sign;
	inst->alg.verअगरy = pkcs1pad_verअगरy;
	inst->alg.set_pub_key = pkcs1pad_set_pub_key;
	inst->alg.set_priv_key = pkcs1pad_set_priv_key;
	inst->alg.max_size = pkcs1pad_get_max_size;
	inst->alg.reqsize = माप(काष्ठा pkcs1pad_request) + rsa_alg->reqsize;

	inst->मुक्त = pkcs1pad_मुक्त;

	err = akcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		pkcs1pad_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

काष्ठा crypto_ढाँचा rsa_pkcs1pad_पंचांगpl = अणु
	.name = "pkcs1pad",
	.create = pkcs1pad_create,
	.module = THIS_MODULE,
पूर्ण;
