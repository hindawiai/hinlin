<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CCM: Counter with CBC-MAC
 *
 * (C) Copyright IBM Corp. 2007 - Joy Latten <latten@us.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

काष्ठा ccm_instance_ctx अणु
	काष्ठा crypto_skcipher_spawn ctr;
	काष्ठा crypto_ahash_spawn mac;
पूर्ण;

काष्ठा crypto_ccm_ctx अणु
	काष्ठा crypto_ahash *mac;
	काष्ठा crypto_skcipher *ctr;
पूर्ण;

काष्ठा crypto_rfc4309_ctx अणु
	काष्ठा crypto_aead *child;
	u8 nonce[3];
पूर्ण;

काष्ठा crypto_rfc4309_req_ctx अणु
	काष्ठा scatterlist src[3];
	काष्ठा scatterlist dst[3];
	काष्ठा aead_request subreq;
पूर्ण;

काष्ठा crypto_ccm_req_priv_ctx अणु
	u8 odata[16];
	u8 idata[16];
	u8 auth_tag[16];
	u32 flags;
	काष्ठा scatterlist src[3];
	काष्ठा scatterlist dst[3];
	जोड़ अणु
		काष्ठा ahash_request ahreq;
		काष्ठा skcipher_request skreq;
	पूर्ण;
पूर्ण;

काष्ठा cbcmac_tfm_ctx अणु
	काष्ठा crypto_cipher *child;
पूर्ण;

काष्ठा cbcmac_desc_ctx अणु
	अचिन्हित पूर्णांक len;
पूर्ण;

अटल अंतरभूत काष्ठा crypto_ccm_req_priv_ctx *crypto_ccm_reqctx(
	काष्ठा aead_request *req)
अणु
	अचिन्हित दीर्घ align = crypto_aead_alignmask(crypto_aead_reqtfm(req));

	वापस (व्योम *)PTR_ALIGN((u8 *)aead_request_ctx(req), align + 1);
पूर्ण

अटल पूर्णांक set_msg_len(u8 *block, अचिन्हित पूर्णांक msglen, पूर्णांक csize)
अणु
	__be32 data;

	स_रखो(block, 0, csize);
	block += csize;

	अगर (csize >= 4)
		csize = 4;
	अन्यथा अगर (msglen > (1 << (8 * csize)))
		वापस -EOVERFLOW;

	data = cpu_to_be32(msglen);
	स_नकल(block - csize, (u8 *)&data + 4 - csize, csize);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_ccm_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_skcipher *ctr = ctx->ctr;
	काष्ठा crypto_ahash *mac = ctx->mac;
	पूर्णांक err;

	crypto_skcipher_clear_flags(ctr, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ctr, crypto_aead_get_flags(aead) &
				       CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(ctr, key, keylen);
	अगर (err)
		वापस err;

	crypto_ahash_clear_flags(mac, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(mac, crypto_aead_get_flags(aead) &
				    CRYPTO_TFM_REQ_MASK);
	वापस crypto_ahash_setkey(mac, key, keylen);
पूर्ण

अटल पूर्णांक crypto_ccm_setauthsize(काष्ठा crypto_aead *tfm,
				  अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 6:
	हाल 8:
	हाल 10:
	हाल 12:
	हाल 14:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक क्रमmat_input(u8 *info, काष्ठा aead_request *req,
			अचिन्हित पूर्णांक cryptlen)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक lp = req->iv[0];
	अचिन्हित पूर्णांक l = lp + 1;
	अचिन्हित पूर्णांक m;

	m = crypto_aead_authsize(aead);

	स_नकल(info, req->iv, 16);

	/* क्रमmat control info per RFC 3610 and
	 * NIST Special Publication 800-38C
	 */
	*info |= (8 * ((m - 2) / 2));
	अगर (req->assoclen)
		*info |= 64;

	वापस set_msg_len(info + 16 - l, cryptlen, l);
पूर्ण

अटल पूर्णांक क्रमmat_adata(u8 *adata, अचिन्हित पूर्णांक a)
अणु
	पूर्णांक len = 0;

	/* add control info क्रम associated data
	 * RFC 3610 and NIST Special Publication 800-38C
	 */
	अगर (a < 65280) अणु
		*(__be16 *)adata = cpu_to_be16(a);
		len = 2;
	पूर्ण अन्यथा  अणु
		*(__be16 *)adata = cpu_to_be16(0xfffe);
		*(__be32 *)&adata[2] = cpu_to_be32(a);
		len = 6;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक crypto_ccm_auth(काष्ठा aead_request *req, काष्ठा scatterlist *plain,
			   अचिन्हित पूर्णांक cryptlen)
अणु
	काष्ठा crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा ahash_request *ahreq = &pctx->ahreq;
	अचिन्हित पूर्णांक assoclen = req->assoclen;
	काष्ठा scatterlist sg[3];
	u8 *odata = pctx->odata;
	u8 *idata = pctx->idata;
	पूर्णांक ilen, err;

	/* क्रमmat control data क्रम input */
	err = क्रमmat_input(odata, req, cryptlen);
	अगर (err)
		जाओ out;

	sg_init_table(sg, 3);
	sg_set_buf(&sg[0], odata, 16);

	/* क्रमmat associated data and compute पूर्णांकo mac */
	अगर (assoclen) अणु
		ilen = क्रमmat_adata(idata, assoclen);
		sg_set_buf(&sg[1], idata, ilen);
		sg_chain(sg, 3, req->src);
	पूर्ण अन्यथा अणु
		ilen = 0;
		sg_chain(sg, 2, req->src);
	पूर्ण

	ahash_request_set_tfm(ahreq, ctx->mac);
	ahash_request_set_callback(ahreq, pctx->flags, शून्य, शून्य);
	ahash_request_set_crypt(ahreq, sg, शून्य, assoclen + ilen + 16);
	err = crypto_ahash_init(ahreq);
	अगर (err)
		जाओ out;
	err = crypto_ahash_update(ahreq);
	अगर (err)
		जाओ out;

	/* we need to pad the MAC input to a round multiple of the block size */
	ilen = 16 - (assoclen + ilen) % 16;
	अगर (ilen < 16) अणु
		स_रखो(idata, 0, ilen);
		sg_init_table(sg, 2);
		sg_set_buf(&sg[0], idata, ilen);
		अगर (plain)
			sg_chain(sg, 2, plain);
		plain = sg;
		cryptlen += ilen;
	पूर्ण

	ahash_request_set_crypt(ahreq, plain, pctx->odata, cryptlen);
	err = crypto_ahash_finup(ahreq);
out:
	वापस err;
पूर्ण

अटल व्योम crypto_ccm_encrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	u8 *odata = pctx->odata;

	अगर (!err)
		scatterwalk_map_and_copy(odata, req->dst,
					 req->assoclen + req->cryptlen,
					 crypto_aead_authsize(aead), 1);
	aead_request_complete(req, err);
पूर्ण

अटल अंतरभूत पूर्णांक crypto_ccm_check_iv(स्थिर u8 *iv)
अणु
	/* 2 <= L <= 8, so 1 <= L' <= 7. */
	अगर (1 > iv[0] || iv[0] > 7)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_ccm_init_crypt(काष्ठा aead_request *req, u8 *tag)
अणु
	काष्ठा crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	काष्ठा scatterlist *sg;
	u8 *iv = req->iv;
	पूर्णांक err;

	err = crypto_ccm_check_iv(iv);
	अगर (err)
		वापस err;

	pctx->flags = aead_request_flags(req);

	 /* Note: rfc 3610 and NIST 800-38C require counter of
	 * zero to encrypt auth tag.
	 */
	स_रखो(iv + 15 - iv[0], 0, iv[0] + 1);

	sg_init_table(pctx->src, 3);
	sg_set_buf(pctx->src, tag, 16);
	sg = scatterwalk_ffwd(pctx->src + 1, req->src, req->assoclen);
	अगर (sg != pctx->src + 1)
		sg_chain(pctx->src, 2, sg);

	अगर (req->src != req->dst) अणु
		sg_init_table(pctx->dst, 3);
		sg_set_buf(pctx->dst, tag, 16);
		sg = scatterwalk_ffwd(pctx->dst + 1, req->dst, req->assoclen);
		अगर (sg != pctx->dst + 1)
			sg_chain(pctx->dst, 2, sg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_ccm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	काष्ठा skcipher_request *skreq = &pctx->skreq;
	काष्ठा scatterlist *dst;
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	u8 *odata = pctx->odata;
	u8 *iv = req->iv;
	पूर्णांक err;

	err = crypto_ccm_init_crypt(req, odata);
	अगर (err)
		वापस err;

	err = crypto_ccm_auth(req, sg_next(pctx->src), cryptlen);
	अगर (err)
		वापस err;

	dst = pctx->src;
	अगर (req->src != req->dst)
		dst = pctx->dst;

	skcipher_request_set_tfm(skreq, ctx->ctr);
	skcipher_request_set_callback(skreq, pctx->flags,
				      crypto_ccm_encrypt_करोne, req);
	skcipher_request_set_crypt(skreq, pctx->src, dst, cryptlen + 16, iv);
	err = crypto_skcipher_encrypt(skreq);
	अगर (err)
		वापस err;

	/* copy authtag to end of dst */
	scatterwalk_map_and_copy(odata, sg_next(dst), cryptlen,
				 crypto_aead_authsize(aead), 1);
	वापस err;
पूर्ण

अटल व्योम crypto_ccm_decrypt_करोne(काष्ठा crypto_async_request *areq,
				   पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;
	काष्ठा crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen - authsize;
	काष्ठा scatterlist *dst;

	pctx->flags = 0;

	dst = sg_next(req->src == req->dst ? pctx->src : pctx->dst);

	अगर (!err) अणु
		err = crypto_ccm_auth(req, dst, cryptlen);
		अगर (!err && crypto_memneq(pctx->auth_tag, pctx->odata, authsize))
			err = -EBADMSG;
	पूर्ण
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक crypto_ccm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	काष्ठा skcipher_request *skreq = &pctx->skreq;
	काष्ठा scatterlist *dst;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	u8 *authtag = pctx->auth_tag;
	u8 *odata = pctx->odata;
	u8 *iv = pctx->idata;
	पूर्णांक err;

	cryptlen -= authsize;

	err = crypto_ccm_init_crypt(req, authtag);
	अगर (err)
		वापस err;

	scatterwalk_map_and_copy(authtag, sg_next(pctx->src), cryptlen,
				 authsize, 0);

	dst = pctx->src;
	अगर (req->src != req->dst)
		dst = pctx->dst;

	स_नकल(iv, req->iv, 16);

	skcipher_request_set_tfm(skreq, ctx->ctr);
	skcipher_request_set_callback(skreq, pctx->flags,
				      crypto_ccm_decrypt_करोne, req);
	skcipher_request_set_crypt(skreq, pctx->src, dst, cryptlen + 16, iv);
	err = crypto_skcipher_decrypt(skreq);
	अगर (err)
		वापस err;

	err = crypto_ccm_auth(req, sg_next(dst), cryptlen);
	अगर (err)
		वापस err;

	/* verअगरy */
	अगर (crypto_memneq(authtag, odata, authsize))
		वापस -EBADMSG;

	वापस err;
पूर्ण

अटल पूर्णांक crypto_ccm_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा ccm_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_ccm_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_ahash *mac;
	काष्ठा crypto_skcipher *ctr;
	अचिन्हित दीर्घ align;
	पूर्णांक err;

	mac = crypto_spawn_ahash(&ictx->mac);
	अगर (IS_ERR(mac))
		वापस PTR_ERR(mac);

	ctr = crypto_spawn_skcipher(&ictx->ctr);
	err = PTR_ERR(ctr);
	अगर (IS_ERR(ctr))
		जाओ err_मुक्त_mac;

	ctx->mac = mac;
	ctx->ctr = ctr;

	align = crypto_aead_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		align + माप(काष्ठा crypto_ccm_req_priv_ctx) +
		max(crypto_ahash_reqsize(mac), crypto_skcipher_reqsize(ctr)));

	वापस 0;

err_मुक्त_mac:
	crypto_मुक्त_ahash(mac);
	वापस err;
पूर्ण

अटल व्योम crypto_ccm_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto_ccm_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_ahash(ctx->mac);
	crypto_मुक्त_skcipher(ctx->ctr);
पूर्ण

अटल व्योम crypto_ccm_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा ccm_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_ahash(&ctx->mac);
	crypto_drop_skcipher(&ctx->ctr);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_ccm_create_common(काष्ठा crypto_ढाँचा *पंचांगpl,
				    काष्ठा rtattr **tb,
				    स्थिर अक्षर *ctr_name,
				    स्थिर अक्षर *mac_name)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा ccm_instance_ctx *ictx;
	काष्ठा skcipher_alg *ctr;
	काष्ठा hash_alg_common *mac;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ictx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	ictx = aead_instance_ctx(inst);

	err = crypto_grab_ahash(&ictx->mac, aead_crypto_instance(inst),
				mac_name, 0, mask | CRYPTO_ALG_ASYNC);
	अगर (err)
		जाओ err_मुक्त_inst;
	mac = crypto_spawn_ahash_alg(&ictx->mac);

	err = -EINVAL;
	अगर (म_भेदन(mac->base.cra_name, "cbcmac(", 7) != 0 ||
	    mac->digestsize != 16)
		जाओ err_मुक्त_inst;

	err = crypto_grab_skcipher(&ictx->ctr, aead_crypto_instance(inst),
				   ctr_name, 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	ctr = crypto_spawn_skcipher_alg(&ictx->ctr);

	/* The skcipher algorithm must be CTR mode, using 16-byte blocks. */
	err = -EINVAL;
	अगर (म_भेदन(ctr->base.cra_name, "ctr(", 4) != 0 ||
	    crypto_skcipher_alg_ivsize(ctr) != 16 ||
	    ctr->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	/* ctr and cbcmac must use the same underlying block cipher. */
	अगर (म_भेद(ctr->base.cra_name + 4, mac->base.cra_name + 7) != 0)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "ccm(%s", ctr->base.cra_name + 4) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "ccm_base(%s,%s)", ctr->base.cra_driver_name,
		     mac->base.cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = (mac->base.cra_priority +
				       ctr->base.cra_priority) / 2;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = mac->base.cra_alignmask |
				       ctr->base.cra_alignmask;
	inst->alg.ivsize = 16;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(ctr);
	inst->alg.maxauthsize = 16;
	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_ccm_ctx);
	inst->alg.init = crypto_ccm_init_tfm;
	inst->alg.निकास = crypto_ccm_निकास_tfm;
	inst->alg.setkey = crypto_ccm_setkey;
	inst->alg.setauthsize = crypto_ccm_setauthsize;
	inst->alg.encrypt = crypto_ccm_encrypt;
	inst->alg.decrypt = crypto_ccm_decrypt;

	inst->मुक्त = crypto_ccm_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_ccm_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक crypto_ccm_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	स्थिर अक्षर *cipher_name;
	अक्षर ctr_name[CRYPTO_MAX_ALG_NAME];
	अक्षर mac_name[CRYPTO_MAX_ALG_NAME];

	cipher_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(cipher_name))
		वापस PTR_ERR(cipher_name);

	अगर (snम_लिखो(ctr_name, CRYPTO_MAX_ALG_NAME, "ctr(%s)",
		     cipher_name) >= CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	अगर (snम_लिखो(mac_name, CRYPTO_MAX_ALG_NAME, "cbcmac(%s)",
		     cipher_name) >= CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	वापस crypto_ccm_create_common(पंचांगpl, tb, ctr_name, mac_name);
पूर्ण

अटल पूर्णांक crypto_ccm_base_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				  काष्ठा rtattr **tb)
अणु
	स्थिर अक्षर *ctr_name;
	स्थिर अक्षर *mac_name;

	ctr_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(ctr_name))
		वापस PTR_ERR(ctr_name);

	mac_name = crypto_attr_alg_name(tb[2]);
	अगर (IS_ERR(mac_name))
		वापस PTR_ERR(mac_name);

	वापस crypto_ccm_create_common(पंचांगpl, tb, ctr_name, mac_name);
पूर्ण

अटल पूर्णांक crypto_rfc4309_setkey(काष्ठा crypto_aead *parent, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_rfc4309_ctx *ctx = crypto_aead_ctx(parent);
	काष्ठा crypto_aead *child = ctx->child;

	अगर (keylen < 3)
		वापस -EINVAL;

	keylen -= 3;
	स_नकल(ctx->nonce, key + keylen, 3);

	crypto_aead_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(child, crypto_aead_get_flags(parent) &
				     CRYPTO_TFM_REQ_MASK);
	वापस crypto_aead_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक crypto_rfc4309_setauthsize(काष्ठा crypto_aead *parent,
				      अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा crypto_rfc4309_ctx *ctx = crypto_aead_ctx(parent);

	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस crypto_aead_setauthsize(ctx->child, authsize);
पूर्ण

अटल काष्ठा aead_request *crypto_rfc4309_crypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_rfc4309_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा aead_request *subreq = &rctx->subreq;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_rfc4309_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_aead *child = ctx->child;
	काष्ठा scatterlist *sg;
	u8 *iv = PTR_ALIGN((u8 *)(subreq + 1) + crypto_aead_reqsize(child),
			   crypto_aead_alignmask(child) + 1);

	/* L' */
	iv[0] = 3;

	स_नकल(iv + 1, ctx->nonce, 3);
	स_नकल(iv + 4, req->iv, 8);

	scatterwalk_map_and_copy(iv + 16, req->src, 0, req->assoclen - 8, 0);

	sg_init_table(rctx->src, 3);
	sg_set_buf(rctx->src, iv + 16, req->assoclen - 8);
	sg = scatterwalk_ffwd(rctx->src + 1, req->src, req->assoclen);
	अगर (sg != rctx->src + 1)
		sg_chain(rctx->src, 2, sg);

	अगर (req->src != req->dst) अणु
		sg_init_table(rctx->dst, 3);
		sg_set_buf(rctx->dst, iv + 16, req->assoclen - 8);
		sg = scatterwalk_ffwd(rctx->dst + 1, req->dst, req->assoclen);
		अगर (sg != rctx->dst + 1)
			sg_chain(rctx->dst, 2, sg);
	पूर्ण

	aead_request_set_tfm(subreq, child);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, rctx->src,
			       req->src == req->dst ? rctx->src : rctx->dst,
			       req->cryptlen, iv);
	aead_request_set_ad(subreq, req->assoclen - 8);

	वापस subreq;
पूर्ण

अटल पूर्णांक crypto_rfc4309_encrypt(काष्ठा aead_request *req)
अणु
	अगर (req->assoclen != 16 && req->assoclen != 20)
		वापस -EINVAL;

	req = crypto_rfc4309_crypt(req);

	वापस crypto_aead_encrypt(req);
पूर्ण

अटल पूर्णांक crypto_rfc4309_decrypt(काष्ठा aead_request *req)
अणु
	अगर (req->assoclen != 16 && req->assoclen != 20)
		वापस -EINVAL;

	req = crypto_rfc4309_crypt(req);

	वापस crypto_aead_decrypt(req);
पूर्ण

अटल पूर्णांक crypto_rfc4309_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा crypto_aead_spawn *spawn = aead_instance_ctx(inst);
	काष्ठा crypto_rfc4309_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *aead;
	अचिन्हित दीर्घ align;

	aead = crypto_spawn_aead(spawn);
	अगर (IS_ERR(aead))
		वापस PTR_ERR(aead);

	ctx->child = aead;

	align = crypto_aead_alignmask(aead);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		माप(काष्ठा crypto_rfc4309_req_ctx) +
		ALIGN(crypto_aead_reqsize(aead), crypto_tfm_ctx_alignment()) +
		align + 32);

	वापस 0;
पूर्ण

अटल व्योम crypto_rfc4309_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto_rfc4309_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_aead(ctx->child);
पूर्ण

अटल व्योम crypto_rfc4309_मुक्त(काष्ठा aead_instance *inst)
अणु
	crypto_drop_aead(aead_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_rfc4309_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				 काष्ठा rtattr **tb)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा crypto_aead_spawn *spawn;
	काष्ठा aead_alg *alg;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	spawn = aead_instance_ctx(inst);
	err = crypto_grab_aead(spawn, aead_crypto_instance(inst),
			       crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_aead_alg(spawn);

	err = -EINVAL;

	/* We only support 16-byte blocks. */
	अगर (crypto_aead_alg_ivsize(alg) != 16)
		जाओ err_मुक्त_inst;

	/* Not a stream cipher? */
	अगर (alg->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "rfc4309(%s)", alg->base.cra_name) >=
	    CRYPTO_MAX_ALG_NAME ||
	    snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "rfc4309(%s)", alg->base.cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask;

	inst->alg.ivsize = 8;
	inst->alg.chunksize = crypto_aead_alg_chunksize(alg);
	inst->alg.maxauthsize = 16;

	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_rfc4309_ctx);

	inst->alg.init = crypto_rfc4309_init_tfm;
	inst->alg.निकास = crypto_rfc4309_निकास_tfm;

	inst->alg.setkey = crypto_rfc4309_setkey;
	inst->alg.setauthsize = crypto_rfc4309_setauthsize;
	inst->alg.encrypt = crypto_rfc4309_encrypt;
	inst->alg.decrypt = crypto_rfc4309_decrypt;

	inst->मुक्त = crypto_rfc4309_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_rfc4309_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक crypto_cbcmac_digest_setkey(काष्ठा crypto_shash *parent,
				     स्थिर u8 *inkey, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cbcmac_tfm_ctx *ctx = crypto_shash_ctx(parent);

	वापस crypto_cipher_setkey(ctx->child, inkey, keylen);
पूर्ण

अटल पूर्णांक crypto_cbcmac_digest_init(काष्ठा shash_desc *pdesc)
अणु
	काष्ठा cbcmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	पूर्णांक bs = crypto_shash_digestsize(pdesc->tfm);
	u8 *dg = (u8 *)ctx + crypto_shash_descsize(pdesc->tfm) - bs;

	ctx->len = 0;
	स_रखो(dg, 0, bs);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_cbcmac_digest_update(काष्ठा shash_desc *pdesc, स्थिर u8 *p,
				       अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	काष्ठा cbcmac_tfm_ctx *tctx = crypto_shash_ctx(parent);
	काष्ठा cbcmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	काष्ठा crypto_cipher *tfm = tctx->child;
	पूर्णांक bs = crypto_shash_digestsize(parent);
	u8 *dg = (u8 *)ctx + crypto_shash_descsize(parent) - bs;

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक l = min(len, bs - ctx->len);

		crypto_xor(dg + ctx->len, p, l);
		ctx->len +=l;
		len -= l;
		p += l;

		अगर (ctx->len == bs) अणु
			crypto_cipher_encrypt_one(tfm, dg, dg);
			ctx->len = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_cbcmac_digest_final(काष्ठा shash_desc *pdesc, u8 *out)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	काष्ठा cbcmac_tfm_ctx *tctx = crypto_shash_ctx(parent);
	काष्ठा cbcmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	काष्ठा crypto_cipher *tfm = tctx->child;
	पूर्णांक bs = crypto_shash_digestsize(parent);
	u8 *dg = (u8 *)ctx + crypto_shash_descsize(parent) - bs;

	अगर (ctx->len)
		crypto_cipher_encrypt_one(tfm, dg, dg);

	स_नकल(out, dg, bs);
	वापस 0;
पूर्ण

अटल पूर्णांक cbcmac_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_instance *inst = (व्योम *)tfm->__crt_alg;
	काष्ठा crypto_cipher_spawn *spawn = crypto_instance_ctx(inst);
	काष्ठा cbcmac_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	cipher = crypto_spawn_cipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;

	वापस 0;
पूर्ण;

अटल व्योम cbcmac_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cbcmac_tfm_ctx *ctx = crypto_tfm_ctx(tfm);
	crypto_मुक्त_cipher(ctx->child);
पूर्ण

अटल पूर्णांक cbcmac_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा shash_instance *inst;
	काष्ठा crypto_cipher_spawn *spawn;
	काष्ठा crypto_alg *alg;
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	spawn = shash_instance_ctx(inst);

	err = crypto_grab_cipher(spawn, shash_crypto_instance(inst),
				 crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	alg = crypto_spawn_cipher_alg(spawn);

	err = crypto_inst_setname(shash_crypto_instance(inst), पंचांगpl->name, alg);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = 1;

	inst->alg.digestsize = alg->cra_blocksize;
	inst->alg.descsize = ALIGN(माप(काष्ठा cbcmac_desc_ctx),
				   alg->cra_alignmask + 1) +
			     alg->cra_blocksize;

	inst->alg.base.cra_ctxsize = माप(काष्ठा cbcmac_tfm_ctx);
	inst->alg.base.cra_init = cbcmac_init_tfm;
	inst->alg.base.cra_निकास = cbcmac_निकास_tfm;

	inst->alg.init = crypto_cbcmac_digest_init;
	inst->alg.update = crypto_cbcmac_digest_update;
	inst->alg.final = crypto_cbcmac_digest_final;
	inst->alg.setkey = crypto_cbcmac_digest_setkey;

	inst->मुक्त = shash_मुक्त_singlespawn_instance;

	err = shash_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		shash_मुक्त_singlespawn_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_ccm_पंचांगpls[] = अणु
	अणु
		.name = "cbcmac",
		.create = cbcmac_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "ccm_base",
		.create = crypto_ccm_base_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "ccm",
		.create = crypto_ccm_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "rfc4309",
		.create = crypto_rfc4309_create,
		.module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init crypto_ccm_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचाs(crypto_ccm_पंचांगpls,
					 ARRAY_SIZE(crypto_ccm_पंचांगpls));
पूर्ण

अटल व्योम __निकास crypto_ccm_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचाs(crypto_ccm_पंचांगpls,
				    ARRAY_SIZE(crypto_ccm_पंचांगpls));
पूर्ण

subsys_initcall(crypto_ccm_module_init);
module_निकास(crypto_ccm_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Counter with CBC MAC");
MODULE_ALIAS_CRYPTO("ccm_base");
MODULE_ALIAS_CRYPTO("rfc4309");
MODULE_ALIAS_CRYPTO("ccm");
MODULE_ALIAS_CRYPTO("cbcmac");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
