<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* In-software asymmetric खुला-key crypto subtype
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "PKEY: "fmt
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/asn1.h>
#समावेश <keys/asymmetric-subtype.h>
#समावेश <crypto/खुला_key.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/sm2.h>
#समावेश <crypto/sm3_base.h>

MODULE_DESCRIPTION("In-software asymmetric public-key subtype");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

/*
 * Provide a part of a description of the key क्रम /proc/keys.
 */
अटल व्योम खुला_key_describe(स्थिर काष्ठा key *asymmetric_key,
				काष्ठा seq_file *m)
अणु
	काष्ठा खुला_key *key = asymmetric_key->payload.data[asym_crypto];

	अगर (key)
		seq_म_लिखो(m, "%s.%s", key->id_type, key->pkey_algo);
पूर्ण

/*
 * Destroy a खुला key algorithm key.
 */
व्योम खुला_key_मुक्त(काष्ठा खुला_key *key)
अणु
	अगर (key) अणु
		kमुक्त(key->key);
		kमुक्त(key->params);
		kमुक्त(key);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(खुला_key_मुक्त);

/*
 * Destroy a खुला key algorithm key.
 */
अटल व्योम खुला_key_destroy(व्योम *payload0, व्योम *payload3)
अणु
	खुला_key_मुक्त(payload0);
	खुला_key_signature_मुक्त(payload3);
पूर्ण

/*
 * Determine the crypto algorithm name.
 */
अटल
पूर्णांक software_key_determine_akcipher(स्थिर अक्षर *encoding,
				    स्थिर अक्षर *hash_algo,
				    स्थिर काष्ठा खुला_key *pkey,
				    अक्षर alg_name[CRYPTO_MAX_ALG_NAME])
अणु
	पूर्णांक n;

	अगर (म_भेद(encoding, "pkcs1") == 0) अणु
		/* The data wangled by the RSA algorithm is typically padded
		 * and encoded in some manner, such as EMSA-PKCS1-1_5 [RFC3447
		 * sec 8.2].
		 */
		अगर (!hash_algo)
			n = snम_लिखो(alg_name, CRYPTO_MAX_ALG_NAME,
				     "pkcs1pad(%s)",
				     pkey->pkey_algo);
		अन्यथा
			n = snम_लिखो(alg_name, CRYPTO_MAX_ALG_NAME,
				     "pkcs1pad(%s,%s)",
				     pkey->pkey_algo, hash_algo);
		वापस n >= CRYPTO_MAX_ALG_NAME ? -EINVAL : 0;
	पूर्ण

	अगर (म_भेद(encoding, "raw") == 0 ||
	    म_भेद(encoding, "x962") == 0) अणु
		म_नकल(alg_name, pkey->pkey_algo);
		वापस 0;
	पूर्ण

	वापस -ENOPKG;
पूर्ण

अटल u8 *pkey_pack_u32(u8 *dst, u32 val)
अणु
	स_नकल(dst, &val, माप(val));
	वापस dst + माप(val);
पूर्ण

/*
 * Query inक्रमmation about a key.
 */
अटल पूर्णांक software_key_query(स्थिर काष्ठा kernel_pkey_params *params,
			      काष्ठा kernel_pkey_query *info)
अणु
	काष्ठा crypto_akcipher *tfm;
	काष्ठा खुला_key *pkey = params->key->payload.data[asym_crypto];
	अक्षर alg_name[CRYPTO_MAX_ALG_NAME];
	u8 *key, *ptr;
	पूर्णांक ret, len;

	ret = software_key_determine_akcipher(params->encoding,
					      params->hash_algo,
					      pkey, alg_name);
	अगर (ret < 0)
		वापस ret;

	tfm = crypto_alloc_akcipher(alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	ret = -ENOMEM;
	key = kदो_स्मृति(pkey->keylen + माप(u32) * 2 + pkey->paramlen,
		      GFP_KERNEL);
	अगर (!key)
		जाओ error_मुक्त_tfm;
	स_नकल(key, pkey->key, pkey->keylen);
	ptr = key + pkey->keylen;
	ptr = pkey_pack_u32(ptr, pkey->algo);
	ptr = pkey_pack_u32(ptr, pkey->paramlen);
	स_नकल(ptr, pkey->params, pkey->paramlen);

	अगर (pkey->key_is_निजी)
		ret = crypto_akcipher_set_priv_key(tfm, key, pkey->keylen);
	अन्यथा
		ret = crypto_akcipher_set_pub_key(tfm, key, pkey->keylen);
	अगर (ret < 0)
		जाओ error_मुक्त_key;

	len = crypto_akcipher_maxsize(tfm);
	info->key_size = len * 8;
	info->max_data_size = len;
	info->max_sig_size = len;
	info->max_enc_size = len;
	info->max_dec_size = len;
	info->supported_ops = (KEYCTL_SUPPORTS_ENCRYPT |
			       KEYCTL_SUPPORTS_VERIFY);
	अगर (pkey->key_is_निजी)
		info->supported_ops |= (KEYCTL_SUPPORTS_DECRYPT |
					KEYCTL_SUPPORTS_SIGN);
	ret = 0;

error_मुक्त_key:
	kमुक्त(key);
error_मुक्त_tfm:
	crypto_मुक्त_akcipher(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Do encryption, decryption and signing ops.
 */
अटल पूर्णांक software_key_eds_op(काष्ठा kernel_pkey_params *params,
			       स्थिर व्योम *in, व्योम *out)
अणु
	स्थिर काष्ठा खुला_key *pkey = params->key->payload.data[asym_crypto];
	काष्ठा akcipher_request *req;
	काष्ठा crypto_akcipher *tfm;
	काष्ठा crypto_रुको cरुको;
	काष्ठा scatterlist in_sg, out_sg;
	अक्षर alg_name[CRYPTO_MAX_ALG_NAME];
	अक्षर *key, *ptr;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	ret = software_key_determine_akcipher(params->encoding,
					      params->hash_algo,
					      pkey, alg_name);
	अगर (ret < 0)
		वापस ret;

	tfm = crypto_alloc_akcipher(alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	ret = -ENOMEM;
	req = akcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		जाओ error_मुक्त_tfm;

	key = kदो_स्मृति(pkey->keylen + माप(u32) * 2 + pkey->paramlen,
		      GFP_KERNEL);
	अगर (!key)
		जाओ error_मुक्त_req;

	स_नकल(key, pkey->key, pkey->keylen);
	ptr = key + pkey->keylen;
	ptr = pkey_pack_u32(ptr, pkey->algo);
	ptr = pkey_pack_u32(ptr, pkey->paramlen);
	स_नकल(ptr, pkey->params, pkey->paramlen);

	अगर (pkey->key_is_निजी)
		ret = crypto_akcipher_set_priv_key(tfm, key, pkey->keylen);
	अन्यथा
		ret = crypto_akcipher_set_pub_key(tfm, key, pkey->keylen);
	अगर (ret)
		जाओ error_मुक्त_key;

	sg_init_one(&in_sg, in, params->in_len);
	sg_init_one(&out_sg, out, params->out_len);
	akcipher_request_set_crypt(req, &in_sg, &out_sg, params->in_len,
				   params->out_len);
	crypto_init_रुको(&cरुको);
	akcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
				      CRYPTO_TFM_REQ_MAY_SLEEP,
				      crypto_req_करोne, &cरुको);

	/* Perक्रमm the encryption calculation. */
	चयन (params->op) अणु
	हाल kernel_pkey_encrypt:
		ret = crypto_akcipher_encrypt(req);
		अवरोध;
	हाल kernel_pkey_decrypt:
		ret = crypto_akcipher_decrypt(req);
		अवरोध;
	हाल kernel_pkey_sign:
		ret = crypto_akcipher_sign(req);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	ret = crypto_रुको_req(ret, &cरुको);
	अगर (ret == 0)
		ret = req->dst_len;

error_मुक्त_key:
	kमुक्त(key);
error_मुक्त_req:
	akcipher_request_मुक्त(req);
error_मुक्त_tfm:
	crypto_मुक्त_akcipher(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

#अगर IS_REACHABLE(CONFIG_CRYPTO_SM2)
अटल पूर्णांक cert_sig_digest_update(स्थिर काष्ठा खुला_key_signature *sig,
				  काष्ठा crypto_akcipher *tfm_pkey)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *desc;
	माप_प्रकार desc_size;
	अचिन्हित अक्षर dgst[SM3_DIGEST_SIZE];
	पूर्णांक ret;

	BUG_ON(!sig->data);

	ret = sm2_compute_z_digest(tfm_pkey, SM2_DEFAULT_USERID,
					SM2_DEFAULT_USERID_LEN, dgst);
	अगर (ret)
		वापस ret;

	tfm = crypto_alloc_shash(sig->hash_algo, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	desc_size = crypto_shash_descsize(tfm) + माप(*desc);
	desc = kzalloc(desc_size, GFP_KERNEL);
	अगर (!desc) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_tfm;
	पूर्ण

	desc->tfm = tfm;

	ret = crypto_shash_init(desc);
	अगर (ret < 0)
		जाओ error_मुक्त_desc;

	ret = crypto_shash_update(desc, dgst, SM3_DIGEST_SIZE);
	अगर (ret < 0)
		जाओ error_मुक्त_desc;

	ret = crypto_shash_finup(desc, sig->data, sig->data_size, sig->digest);

error_मुक्त_desc:
	kमुक्त(desc);
error_मुक्त_tfm:
	crypto_मुक्त_shash(tfm);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cert_sig_digest_update(
	स्थिर काष्ठा खुला_key_signature *sig,
	काष्ठा crypto_akcipher *tfm_pkey)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर /* ! IS_REACHABLE(CONFIG_CRYPTO_SM2) */

/*
 * Verअगरy a signature using a खुला key.
 */
पूर्णांक खुला_key_verअगरy_signature(स्थिर काष्ठा खुला_key *pkey,
				स्थिर काष्ठा खुला_key_signature *sig)
अणु
	काष्ठा crypto_रुको cरुको;
	काष्ठा crypto_akcipher *tfm;
	काष्ठा akcipher_request *req;
	काष्ठा scatterlist src_sg[2];
	अक्षर alg_name[CRYPTO_MAX_ALG_NAME];
	अक्षर *key, *ptr;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	BUG_ON(!pkey);
	BUG_ON(!sig);
	BUG_ON(!sig->s);

	ret = software_key_determine_akcipher(sig->encoding,
					      sig->hash_algo,
					      pkey, alg_name);
	अगर (ret < 0)
		वापस ret;

	tfm = crypto_alloc_akcipher(alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	ret = -ENOMEM;
	req = akcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		जाओ error_मुक्त_tfm;

	key = kदो_स्मृति(pkey->keylen + माप(u32) * 2 + pkey->paramlen,
		      GFP_KERNEL);
	अगर (!key)
		जाओ error_मुक्त_req;

	स_नकल(key, pkey->key, pkey->keylen);
	ptr = key + pkey->keylen;
	ptr = pkey_pack_u32(ptr, pkey->algo);
	ptr = pkey_pack_u32(ptr, pkey->paramlen);
	स_नकल(ptr, pkey->params, pkey->paramlen);

	अगर (pkey->key_is_निजी)
		ret = crypto_akcipher_set_priv_key(tfm, key, pkey->keylen);
	अन्यथा
		ret = crypto_akcipher_set_pub_key(tfm, key, pkey->keylen);
	अगर (ret)
		जाओ error_मुक्त_key;

	अगर (sig->pkey_algo && म_भेद(sig->pkey_algo, "sm2") == 0 &&
	    sig->data_size) अणु
		ret = cert_sig_digest_update(sig, tfm);
		अगर (ret)
			जाओ error_मुक्त_key;
	पूर्ण

	sg_init_table(src_sg, 2);
	sg_set_buf(&src_sg[0], sig->s, sig->s_size);
	sg_set_buf(&src_sg[1], sig->digest, sig->digest_size);
	akcipher_request_set_crypt(req, src_sg, शून्य, sig->s_size,
				   sig->digest_size);
	crypto_init_रुको(&cरुको);
	akcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
				      CRYPTO_TFM_REQ_MAY_SLEEP,
				      crypto_req_करोne, &cरुको);
	ret = crypto_रुको_req(crypto_akcipher_verअगरy(req), &cरुको);

error_मुक्त_key:
	kमुक्त(key);
error_मुक्त_req:
	akcipher_request_मुक्त(req);
error_मुक्त_tfm:
	crypto_मुक्त_akcipher(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	अगर (WARN_ON_ONCE(ret > 0))
		ret = -EINVAL;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(खुला_key_verअगरy_signature);

अटल पूर्णांक खुला_key_verअगरy_signature_2(स्थिर काष्ठा key *key,
					 स्थिर काष्ठा खुला_key_signature *sig)
अणु
	स्थिर काष्ठा खुला_key *pk = key->payload.data[asym_crypto];
	वापस खुला_key_verअगरy_signature(pk, sig);
पूर्ण

/*
 * Public key algorithm asymmetric key subtype
 */
काष्ठा asymmetric_key_subtype खुला_key_subtype = अणु
	.owner			= THIS_MODULE,
	.name			= "public_key",
	.name_len		= माप("public_key") - 1,
	.describe		= खुला_key_describe,
	.destroy		= खुला_key_destroy,
	.query			= software_key_query,
	.eds_op			= software_key_eds_op,
	.verअगरy_signature	= खुला_key_verअगरy_signature_2,
पूर्ण;
EXPORT_SYMBOL_GPL(खुला_key_subtype);
