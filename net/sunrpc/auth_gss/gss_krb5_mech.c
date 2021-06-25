<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 *  linux/net/sunrpc/gss_krb5_mech.c
 *
 *  Copyright (c) 2001-2008 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson <andros@umich.edu>
 *  J. Bruce Fields <bfields@umich.edu>
 */

#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/gss_krb5.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/gss_krb5_enctypes.h>

#समावेश "auth_gss_internal.h"

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_AUTH
#पूर्ण_अगर

अटल काष्ठा gss_api_mech gss_kerberos_mech;	/* क्रमward declaration */

अटल स्थिर काष्ठा gss_krb5_enctype supported_gss_krb5_enctypes[] = अणु
#अगर_अघोषित CONFIG_SUNRPC_DISABLE_INSECURE_ENCTYPES
	/*
	 * DES (All DES enctypes are mapped to the same gss functionality)
	 */
	अणु
	  .etype = ENCTYPE_DES_CBC_RAW,
	  .ctype = CKSUMTYPE_RSA_MD5,
	  .name = "des-cbc-crc",
	  .encrypt_name = "cbc(des)",
	  .cksum_name = "md5",
	  .encrypt = krb5_encrypt,
	  .decrypt = krb5_decrypt,
	  .mk_key = शून्य,
	  .संकेतg = SGN_ALG_DES_MAC_MD5,
	  .sealalg = SEAL_ALG_DES,
	  .keybytes = 7,
	  .keylength = 8,
	  .blocksize = 8,
	  .conflen = 8,
	  .cksumlength = 8,
	  .keyed_cksum = 0,
	पूर्ण,
#पूर्ण_अगर	/* CONFIG_SUNRPC_DISABLE_INSECURE_ENCTYPES */
	/*
	 * 3DES
	 */
	अणु
	  .etype = ENCTYPE_DES3_CBC_RAW,
	  .ctype = CKSUMTYPE_HMAC_SHA1_DES3,
	  .name = "des3-hmac-sha1",
	  .encrypt_name = "cbc(des3_ede)",
	  .cksum_name = "hmac(sha1)",
	  .encrypt = krb5_encrypt,
	  .decrypt = krb5_decrypt,
	  .mk_key = gss_krb5_des3_make_key,
	  .संकेतg = SGN_ALG_HMAC_SHA1_DES3_KD,
	  .sealalg = SEAL_ALG_DES3KD,
	  .keybytes = 21,
	  .keylength = 24,
	  .blocksize = 8,
	  .conflen = 8,
	  .cksumlength = 20,
	  .keyed_cksum = 1,
	पूर्ण,
	/*
	 * AES128
	 */
	अणु
	  .etype = ENCTYPE_AES128_CTS_HMAC_SHA1_96,
	  .ctype = CKSUMTYPE_HMAC_SHA1_96_AES128,
	  .name = "aes128-cts",
	  .encrypt_name = "cts(cbc(aes))",
	  .cksum_name = "hmac(sha1)",
	  .encrypt = krb5_encrypt,
	  .decrypt = krb5_decrypt,
	  .mk_key = gss_krb5_aes_make_key,
	  .encrypt_v2 = gss_krb5_aes_encrypt,
	  .decrypt_v2 = gss_krb5_aes_decrypt,
	  .संकेतg = -1,
	  .sealalg = -1,
	  .keybytes = 16,
	  .keylength = 16,
	  .blocksize = 16,
	  .conflen = 16,
	  .cksumlength = 12,
	  .keyed_cksum = 1,
	पूर्ण,
	/*
	 * AES256
	 */
	अणु
	  .etype = ENCTYPE_AES256_CTS_HMAC_SHA1_96,
	  .ctype = CKSUMTYPE_HMAC_SHA1_96_AES256,
	  .name = "aes256-cts",
	  .encrypt_name = "cts(cbc(aes))",
	  .cksum_name = "hmac(sha1)",
	  .encrypt = krb5_encrypt,
	  .decrypt = krb5_decrypt,
	  .mk_key = gss_krb5_aes_make_key,
	  .encrypt_v2 = gss_krb5_aes_encrypt,
	  .decrypt_v2 = gss_krb5_aes_decrypt,
	  .संकेतg = -1,
	  .sealalg = -1,
	  .keybytes = 32,
	  .keylength = 32,
	  .blocksize = 16,
	  .conflen = 16,
	  .cksumlength = 12,
	  .keyed_cksum = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक num_supported_enctypes =
	ARRAY_SIZE(supported_gss_krb5_enctypes);

अटल पूर्णांक
supported_gss_krb5_enctype(पूर्णांक etype)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < num_supported_enctypes; i++)
		अगर (supported_gss_krb5_enctypes[i].etype == etype)
			वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gss_krb5_enctype *
get_gss_krb5_enctype(पूर्णांक etype)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < num_supported_enctypes; i++)
		अगर (supported_gss_krb5_enctypes[i].etype == etype)
			वापस &supported_gss_krb5_enctypes[i];
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर व्योम *
get_key(स्थिर व्योम *p, स्थिर व्योम *end,
	काष्ठा krb5_ctx *ctx, काष्ठा crypto_sync_skcipher **res)
अणु
	काष्ठा xdr_netobj	key;
	पूर्णांक			alg;

	p = simple_get_bytes(p, end, &alg, माप(alg));
	अगर (IS_ERR(p))
		जाओ out_err;

	चयन (alg) अणु
	हाल ENCTYPE_DES_CBC_CRC:
	हाल ENCTYPE_DES_CBC_MD4:
	हाल ENCTYPE_DES_CBC_MD5:
		/* Map all these key types to ENCTYPE_DES_CBC_RAW */
		alg = ENCTYPE_DES_CBC_RAW;
		अवरोध;
	पूर्ण

	अगर (!supported_gss_krb5_enctype(alg)) अणु
		prपूर्णांकk(KERN_WARNING "gss_kerberos_mech: unsupported "
			"encryption key algorithm %d\n", alg);
		p = ERR_PTR(-EINVAL);
		जाओ out_err;
	पूर्ण
	p = simple_get_netobj(p, end, &key);
	अगर (IS_ERR(p))
		जाओ out_err;

	*res = crypto_alloc_sync_skcipher(ctx->gk5e->encrypt_name, 0, 0);
	अगर (IS_ERR(*res)) अणु
		prपूर्णांकk(KERN_WARNING "gss_kerberos_mech: unable to initialize "
			"crypto algorithm %s\n", ctx->gk5e->encrypt_name);
		*res = शून्य;
		जाओ out_err_मुक्त_key;
	पूर्ण
	अगर (crypto_sync_skcipher_setkey(*res, key.data, key.len)) अणु
		prपूर्णांकk(KERN_WARNING "gss_kerberos_mech: error setting key for "
			"crypto algorithm %s\n", ctx->gk5e->encrypt_name);
		जाओ out_err_मुक्त_tfm;
	पूर्ण

	kमुक्त(key.data);
	वापस p;

out_err_मुक्त_tfm:
	crypto_मुक्त_sync_skcipher(*res);
out_err_मुक्त_key:
	kमुक्त(key.data);
	p = ERR_PTR(-EINVAL);
out_err:
	वापस p;
पूर्ण

अटल पूर्णांक
gss_import_v1_context(स्थिर व्योम *p, स्थिर व्योम *end, काष्ठा krb5_ctx *ctx)
अणु
	u32 seq_send;
	पूर्णांक पंचांगp;
	u32 समय32;

	p = simple_get_bytes(p, end, &ctx->initiate, माप(ctx->initiate));
	अगर (IS_ERR(p))
		जाओ out_err;

	/* Old क्रमmat supports only DES!  Any other enctype uses new क्रमmat */
	ctx->enctype = ENCTYPE_DES_CBC_RAW;

	ctx->gk5e = get_gss_krb5_enctype(ctx->enctype);
	अगर (ctx->gk5e == शून्य) अणु
		p = ERR_PTR(-EINVAL);
		जाओ out_err;
	पूर्ण

	/* The करोwncall क्रमmat was deचिन्हित beक्रमe we completely understood
	 * the uses of the context fields; so it includes some stuff we
	 * just give some minimal sanity-checking, and some we ignore
	 * completely (like the next twenty bytes): */
	अगर (unlikely(p + 20 > end || p + 20 < p)) अणु
		p = ERR_PTR(-EFAULT);
		जाओ out_err;
	पूर्ण
	p += 20;
	p = simple_get_bytes(p, end, &पंचांगp, माप(पंचांगp));
	अगर (IS_ERR(p))
		जाओ out_err;
	अगर (पंचांगp != SGN_ALG_DES_MAC_MD5) अणु
		p = ERR_PTR(-ENOSYS);
		जाओ out_err;
	पूर्ण
	p = simple_get_bytes(p, end, &पंचांगp, माप(पंचांगp));
	अगर (IS_ERR(p))
		जाओ out_err;
	अगर (पंचांगp != SEAL_ALG_DES) अणु
		p = ERR_PTR(-ENOSYS);
		जाओ out_err;
	पूर्ण
	p = simple_get_bytes(p, end, &समय32, माप(समय32));
	अगर (IS_ERR(p))
		जाओ out_err;
	/* अचिन्हित 32-bit समय overflows in year 2106 */
	ctx->endसमय = (समय64_t)समय32;
	p = simple_get_bytes(p, end, &seq_send, माप(seq_send));
	अगर (IS_ERR(p))
		जाओ out_err;
	atomic_set(&ctx->seq_send, seq_send);
	p = simple_get_netobj(p, end, &ctx->mech_used);
	अगर (IS_ERR(p))
		जाओ out_err;
	p = get_key(p, end, ctx, &ctx->enc);
	अगर (IS_ERR(p))
		जाओ out_err_मुक्त_mech;
	p = get_key(p, end, ctx, &ctx->seq);
	अगर (IS_ERR(p))
		जाओ out_err_मुक्त_key1;
	अगर (p != end) अणु
		p = ERR_PTR(-EFAULT);
		जाओ out_err_मुक्त_key2;
	पूर्ण

	वापस 0;

out_err_मुक्त_key2:
	crypto_मुक्त_sync_skcipher(ctx->seq);
out_err_मुक्त_key1:
	crypto_मुक्त_sync_skcipher(ctx->enc);
out_err_मुक्त_mech:
	kमुक्त(ctx->mech_used.data);
out_err:
	वापस PTR_ERR(p);
पूर्ण

अटल काष्ठा crypto_sync_skcipher *
context_v2_alloc_cipher(काष्ठा krb5_ctx *ctx, स्थिर अक्षर *cname, u8 *key)
अणु
	काष्ठा crypto_sync_skcipher *cp;

	cp = crypto_alloc_sync_skcipher(cname, 0, 0);
	अगर (IS_ERR(cp)) अणु
		dprपूर्णांकk("gss_kerberos_mech: unable to initialize "
			"crypto algorithm %s\n", cname);
		वापस शून्य;
	पूर्ण
	अगर (crypto_sync_skcipher_setkey(cp, key, ctx->gk5e->keylength)) अणु
		dprपूर्णांकk("gss_kerberos_mech: error setting key for "
			"crypto algorithm %s\n", cname);
		crypto_मुक्त_sync_skcipher(cp);
		वापस शून्य;
	पूर्ण
	वापस cp;
पूर्ण

अटल अंतरभूत व्योम
set_cdata(u8 cdata[GSS_KRB5_K5CLENGTH], u32 usage, u8 seed)
अणु
	cdata[0] = (usage>>24)&0xff;
	cdata[1] = (usage>>16)&0xff;
	cdata[2] = (usage>>8)&0xff;
	cdata[3] = usage&0xff;
	cdata[4] = seed;
पूर्ण

अटल पूर्णांक
context_derive_keys_des3(काष्ठा krb5_ctx *ctx, gfp_t gfp_mask)
अणु
	काष्ठा xdr_netobj c, keyin, keyout;
	u8 cdata[GSS_KRB5_K5CLENGTH];
	u32 err;

	c.len = GSS_KRB5_K5CLENGTH;
	c.data = cdata;

	keyin.data = ctx->Ksess;
	keyin.len = ctx->gk5e->keylength;
	keyout.len = ctx->gk5e->keylength;

	/* seq uses the raw key */
	ctx->seq = context_v2_alloc_cipher(ctx, ctx->gk5e->encrypt_name,
					   ctx->Ksess);
	अगर (ctx->seq == शून्य)
		जाओ out_err;

	ctx->enc = context_v2_alloc_cipher(ctx, ctx->gk5e->encrypt_name,
					   ctx->Ksess);
	अगर (ctx->enc == शून्य)
		जाओ out_मुक्त_seq;

	/* derive cksum */
	set_cdata(cdata, KG_USAGE_SIGN, KEY_USAGE_SEED_CHECKSUM);
	keyout.data = ctx->cksum;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving cksum key\n",
			__func__, err);
		जाओ out_मुक्त_enc;
	पूर्ण

	वापस 0;

out_मुक्त_enc:
	crypto_मुक्त_sync_skcipher(ctx->enc);
out_मुक्त_seq:
	crypto_मुक्त_sync_skcipher(ctx->seq);
out_err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
context_derive_keys_new(काष्ठा krb5_ctx *ctx, gfp_t gfp_mask)
अणु
	काष्ठा xdr_netobj c, keyin, keyout;
	u8 cdata[GSS_KRB5_K5CLENGTH];
	u32 err;

	c.len = GSS_KRB5_K5CLENGTH;
	c.data = cdata;

	keyin.data = ctx->Ksess;
	keyin.len = ctx->gk5e->keylength;
	keyout.len = ctx->gk5e->keylength;

	/* initiator seal encryption */
	set_cdata(cdata, KG_USAGE_INITIATOR_SEAL, KEY_USAGE_SEED_ENCRYPTION);
	keyout.data = ctx->initiator_seal;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving initiator_seal key\n",
			__func__, err);
		जाओ out_err;
	पूर्ण
	ctx->initiator_enc = context_v2_alloc_cipher(ctx,
						     ctx->gk5e->encrypt_name,
						     ctx->initiator_seal);
	अगर (ctx->initiator_enc == शून्य)
		जाओ out_err;

	/* acceptor seal encryption */
	set_cdata(cdata, KG_USAGE_ACCEPTOR_SEAL, KEY_USAGE_SEED_ENCRYPTION);
	keyout.data = ctx->acceptor_seal;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving acceptor_seal key\n",
			__func__, err);
		जाओ out_मुक्त_initiator_enc;
	पूर्ण
	ctx->acceptor_enc = context_v2_alloc_cipher(ctx,
						    ctx->gk5e->encrypt_name,
						    ctx->acceptor_seal);
	अगर (ctx->acceptor_enc == शून्य)
		जाओ out_मुक्त_initiator_enc;

	/* initiator sign checksum */
	set_cdata(cdata, KG_USAGE_INITIATOR_SIGN, KEY_USAGE_SEED_CHECKSUM);
	keyout.data = ctx->initiator_sign;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving initiator_sign key\n",
			__func__, err);
		जाओ out_मुक्त_acceptor_enc;
	पूर्ण

	/* acceptor sign checksum */
	set_cdata(cdata, KG_USAGE_ACCEPTOR_SIGN, KEY_USAGE_SEED_CHECKSUM);
	keyout.data = ctx->acceptor_sign;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving acceptor_sign key\n",
			__func__, err);
		जाओ out_मुक्त_acceptor_enc;
	पूर्ण

	/* initiator seal पूर्णांकegrity */
	set_cdata(cdata, KG_USAGE_INITIATOR_SEAL, KEY_USAGE_SEED_INTEGRITY);
	keyout.data = ctx->initiator_पूर्णांकeg;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving initiator_integ key\n",
			__func__, err);
		जाओ out_मुक्त_acceptor_enc;
	पूर्ण

	/* acceptor seal पूर्णांकegrity */
	set_cdata(cdata, KG_USAGE_ACCEPTOR_SEAL, KEY_USAGE_SEED_INTEGRITY);
	keyout.data = ctx->acceptor_पूर्णांकeg;
	err = krb5_derive_key(ctx->gk5e, &keyin, &keyout, &c, gfp_mask);
	अगर (err) अणु
		dprपूर्णांकk("%s: Error %d deriving acceptor_integ key\n",
			__func__, err);
		जाओ out_मुक्त_acceptor_enc;
	पूर्ण

	चयन (ctx->enctype) अणु
	हाल ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	हाल ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		ctx->initiator_enc_aux =
			context_v2_alloc_cipher(ctx, "cbc(aes)",
						ctx->initiator_seal);
		अगर (ctx->initiator_enc_aux == शून्य)
			जाओ out_मुक्त_acceptor_enc;
		ctx->acceptor_enc_aux =
			context_v2_alloc_cipher(ctx, "cbc(aes)",
						ctx->acceptor_seal);
		अगर (ctx->acceptor_enc_aux == शून्य) अणु
			crypto_मुक्त_sync_skcipher(ctx->initiator_enc_aux);
			जाओ out_मुक्त_acceptor_enc;
		पूर्ण
	पूर्ण

	वापस 0;

out_मुक्त_acceptor_enc:
	crypto_मुक्त_sync_skcipher(ctx->acceptor_enc);
out_मुक्त_initiator_enc:
	crypto_मुक्त_sync_skcipher(ctx->initiator_enc);
out_err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
gss_import_v2_context(स्थिर व्योम *p, स्थिर व्योम *end, काष्ठा krb5_ctx *ctx,
		gfp_t gfp_mask)
अणु
	u64 seq_send64;
	पूर्णांक keylen;
	u32 समय32;

	p = simple_get_bytes(p, end, &ctx->flags, माप(ctx->flags));
	अगर (IS_ERR(p))
		जाओ out_err;
	ctx->initiate = ctx->flags & KRB5_CTX_FLAG_INITIATOR;

	p = simple_get_bytes(p, end, &समय32, माप(समय32));
	अगर (IS_ERR(p))
		जाओ out_err;
	/* अचिन्हित 32-bit समय overflows in year 2106 */
	ctx->endसमय = (समय64_t)समय32;
	p = simple_get_bytes(p, end, &seq_send64, माप(seq_send64));
	अगर (IS_ERR(p))
		जाओ out_err;
	atomic64_set(&ctx->seq_send64, seq_send64);
	/* set seq_send क्रम use by "older" enctypes */
	atomic_set(&ctx->seq_send, seq_send64);
	अगर (seq_send64 != atomic_पढ़ो(&ctx->seq_send)) अणु
		dprपूर्णांकk("%s: seq_send64 %llx, seq_send %x overflow?\n", __func__,
			seq_send64, atomic_पढ़ो(&ctx->seq_send));
		p = ERR_PTR(-EINVAL);
		जाओ out_err;
	पूर्ण
	p = simple_get_bytes(p, end, &ctx->enctype, माप(ctx->enctype));
	अगर (IS_ERR(p))
		जाओ out_err;
	/* Map ENCTYPE_DES3_CBC_SHA1 to ENCTYPE_DES3_CBC_RAW */
	अगर (ctx->enctype == ENCTYPE_DES3_CBC_SHA1)
		ctx->enctype = ENCTYPE_DES3_CBC_RAW;
	ctx->gk5e = get_gss_krb5_enctype(ctx->enctype);
	अगर (ctx->gk5e == शून्य) अणु
		dprपूर्णांकk("gss_kerberos_mech: unsupported krb5 enctype %u\n",
			ctx->enctype);
		p = ERR_PTR(-EINVAL);
		जाओ out_err;
	पूर्ण
	keylen = ctx->gk5e->keylength;

	p = simple_get_bytes(p, end, ctx->Ksess, keylen);
	अगर (IS_ERR(p))
		जाओ out_err;

	अगर (p != end) अणु
		p = ERR_PTR(-EINVAL);
		जाओ out_err;
	पूर्ण

	ctx->mech_used.data = kmemdup(gss_kerberos_mech.gm_oid.data,
				      gss_kerberos_mech.gm_oid.len, gfp_mask);
	अगर (unlikely(ctx->mech_used.data == शून्य)) अणु
		p = ERR_PTR(-ENOMEM);
		जाओ out_err;
	पूर्ण
	ctx->mech_used.len = gss_kerberos_mech.gm_oid.len;

	चयन (ctx->enctype) अणु
	हाल ENCTYPE_DES3_CBC_RAW:
		वापस context_derive_keys_des3(ctx, gfp_mask);
	हाल ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	हाल ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		वापस context_derive_keys_new(ctx, gfp_mask);
	शेष:
		वापस -EINVAL;
	पूर्ण

out_err:
	वापस PTR_ERR(p);
पूर्ण

अटल पूर्णांक
gss_import_sec_context_kerberos(स्थिर व्योम *p, माप_प्रकार len,
				काष्ठा gss_ctx *ctx_id,
				समय64_t *endसमय,
				gfp_t gfp_mask)
अणु
	स्थिर व्योम *end = (स्थिर व्योम *)((स्थिर अक्षर *)p + len);
	काष्ठा  krb5_ctx *ctx;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), gfp_mask);
	अगर (ctx == शून्य)
		वापस -ENOMEM;

	अगर (len == 85)
		ret = gss_import_v1_context(p, end, ctx);
	अन्यथा
		ret = gss_import_v2_context(p, end, ctx, gfp_mask);

	अगर (ret == 0) अणु
		ctx_id->पूर्णांकernal_ctx_id = ctx;
		अगर (endसमय)
			*endसमय = ctx->endसमय;
	पूर्ण अन्यथा
		kमुक्त(ctx);

	dprपूर्णांकk("RPC:       %s: returning %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम
gss_delete_sec_context_kerberos(व्योम *पूर्णांकernal_ctx) अणु
	काष्ठा krb5_ctx *kctx = पूर्णांकernal_ctx;

	crypto_मुक्त_sync_skcipher(kctx->seq);
	crypto_मुक्त_sync_skcipher(kctx->enc);
	crypto_मुक्त_sync_skcipher(kctx->acceptor_enc);
	crypto_मुक्त_sync_skcipher(kctx->initiator_enc);
	crypto_मुक्त_sync_skcipher(kctx->acceptor_enc_aux);
	crypto_मुक्त_sync_skcipher(kctx->initiator_enc_aux);
	kमुक्त(kctx->mech_used.data);
	kमुक्त(kctx);
पूर्ण

अटल स्थिर काष्ठा gss_api_ops gss_kerberos_ops = अणु
	.gss_import_sec_context	= gss_import_sec_context_kerberos,
	.gss_get_mic		= gss_get_mic_kerberos,
	.gss_verअगरy_mic		= gss_verअगरy_mic_kerberos,
	.gss_wrap		= gss_wrap_kerberos,
	.gss_unwrap		= gss_unwrap_kerberos,
	.gss_delete_sec_context	= gss_delete_sec_context_kerberos,
पूर्ण;

अटल काष्ठा pf_desc gss_kerberos_pfs[] = अणु
	[0] = अणु
		.pseuकरोflavor = RPC_AUTH_GSS_KRB5,
		.qop = GSS_C_QOP_DEFAULT,
		.service = RPC_GSS_SVC_NONE,
		.name = "krb5",
	पूर्ण,
	[1] = अणु
		.pseuकरोflavor = RPC_AUTH_GSS_KRB5I,
		.qop = GSS_C_QOP_DEFAULT,
		.service = RPC_GSS_SVC_INTEGRITY,
		.name = "krb5i",
		.datatouch = true,
	पूर्ण,
	[2] = अणु
		.pseuकरोflavor = RPC_AUTH_GSS_KRB5P,
		.qop = GSS_C_QOP_DEFAULT,
		.service = RPC_GSS_SVC_PRIVACY,
		.name = "krb5p",
		.datatouch = true,
	पूर्ण,
पूर्ण;

MODULE_ALIAS("rpc-auth-gss-krb5");
MODULE_ALIAS("rpc-auth-gss-krb5i");
MODULE_ALIAS("rpc-auth-gss-krb5p");
MODULE_ALIAS("rpc-auth-gss-390003");
MODULE_ALIAS("rpc-auth-gss-390004");
MODULE_ALIAS("rpc-auth-gss-390005");
MODULE_ALIAS("rpc-auth-gss-1.2.840.113554.1.2.2");

अटल काष्ठा gss_api_mech gss_kerberos_mech = अणु
	.gm_name	= "krb5",
	.gm_owner	= THIS_MODULE,
	.gm_oid		= अणु 9, "\x2a\x86\x48\x86\xf7\x12\x01\x02\x02" पूर्ण,
	.gm_ops		= &gss_kerberos_ops,
	.gm_pf_num	= ARRAY_SIZE(gss_kerberos_pfs),
	.gm_pfs		= gss_kerberos_pfs,
	.gm_upcall_enctypes = KRB5_SUPPORTED_ENCTYPES,
पूर्ण;

अटल पूर्णांक __init init_kerberos_module(व्योम)
अणु
	पूर्णांक status;

	status = gss_mech_रेजिस्टर(&gss_kerberos_mech);
	अगर (status)
		prपूर्णांकk("Failed to register kerberos gss mechanism!\n");
	वापस status;
पूर्ण

अटल व्योम __निकास cleanup_kerberos_module(व्योम)
अणु
	gss_mech_unरेजिस्टर(&gss_kerberos_mech);
पूर्ण

MODULE_LICENSE("GPL");
module_init(init_kerberos_module);
module_निकास(cleanup_kerberos_module);
