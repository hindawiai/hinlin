<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) "ASYM-TPM: "fmt
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/tpm.h>
#समावेश <linux/tpm_command.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <keys/asymmetric-subtype.h>
#समावेश <keys/trusted_tpm.h>
#समावेश <crypto/asym_tpm_subtype.h>
#समावेश <crypto/खुला_key.h>

#घोषणा TPM_ORD_FLUSHSPECIFIC	186
#घोषणा TPM_ORD_LOADKEY2	65
#घोषणा TPM_ORD_UNBIND		30
#घोषणा TPM_ORD_SIGN		60

#घोषणा TPM_RT_KEY                      0x00000001

/*
 * Load a TPM key from the blob provided by userspace
 */
अटल पूर्णांक tpm_loadkey2(काष्ठा tpm_buf *tb,
			uपूर्णांक32_t keyhandle, अचिन्हित अक्षर *keyauth,
			स्थिर अचिन्हित अक्षर *keyblob, पूर्णांक keybloblen,
			uपूर्णांक32_t *newhandle)
अणु
	अचिन्हित अक्षर nonceodd[TPM_NONCE_SIZE];
	अचिन्हित अक्षर enonce[TPM_NONCE_SIZE];
	अचिन्हित अक्षर authdata[SHA1_DIGEST_SIZE];
	uपूर्णांक32_t authhandle = 0;
	अचिन्हित अक्षर cont = 0;
	uपूर्णांक32_t ordinal;
	पूर्णांक ret;

	ordinal = htonl(TPM_ORD_LOADKEY2);

	/* session क्रम loading the key */
	ret = oiap(tb, &authhandle, enonce);
	अगर (ret < 0) अणु
		pr_info("oiap failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* generate odd nonce */
	ret = tpm_get_अक्रमom(शून्य, nonceodd, TPM_NONCE_SIZE);
	अगर (ret < 0) अणु
		pr_info("tpm_get_random failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* calculate authorization HMAC value */
	ret = TSS_authhmac(authdata, keyauth, SHA1_DIGEST_SIZE, enonce,
			   nonceodd, cont, माप(uपूर्णांक32_t), &ordinal,
			   keybloblen, keyblob, 0, 0);
	अगर (ret < 0)
		वापस ret;

	/* build the request buffer */
	tpm_buf_reset(tb, TPM_TAG_RQU_AUTH1_COMMAND, TPM_ORD_LOADKEY2);
	tpm_buf_append_u32(tb, keyhandle);
	tpm_buf_append(tb, keyblob, keybloblen);
	tpm_buf_append_u32(tb, authhandle);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0) अणु
		pr_info("authhmac failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = TSS_checkhmac1(tb->data, ordinal, nonceodd, keyauth,
			     SHA1_DIGEST_SIZE, 0, 0);
	अगर (ret < 0) अणु
		pr_info("TSS_checkhmac1 failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	*newhandle = LOAD32(tb->data, TPM_DATA_OFFSET);
	वापस 0;
पूर्ण

/*
 * Execute the FlushSpecअगरic TPM command
 */
अटल पूर्णांक tpm_flushspecअगरic(काष्ठा tpm_buf *tb, uपूर्णांक32_t handle)
अणु
	tpm_buf_reset(tb, TPM_TAG_RQU_COMMAND, TPM_ORD_FLUSHSPECIFIC);
	tpm_buf_append_u32(tb, handle);
	tpm_buf_append_u32(tb, TPM_RT_KEY);

	वापस trusted_tpm_send(tb->data, MAX_BUF_SIZE);
पूर्ण

/*
 * Decrypt a blob provided by userspace using a specअगरic key handle.
 * The handle is a well known handle or previously loaded by e.g. LoadKey2
 */
अटल पूर्णांक tpm_unbind(काष्ठा tpm_buf *tb,
			uपूर्णांक32_t keyhandle, अचिन्हित अक्षर *keyauth,
			स्थिर अचिन्हित अक्षर *blob, uपूर्णांक32_t bloblen,
			व्योम *out, uपूर्णांक32_t outlen)
अणु
	अचिन्हित अक्षर nonceodd[TPM_NONCE_SIZE];
	अचिन्हित अक्षर enonce[TPM_NONCE_SIZE];
	अचिन्हित अक्षर authdata[SHA1_DIGEST_SIZE];
	uपूर्णांक32_t authhandle = 0;
	अचिन्हित अक्षर cont = 0;
	uपूर्णांक32_t ordinal;
	uपूर्णांक32_t datalen;
	पूर्णांक ret;

	ordinal = htonl(TPM_ORD_UNBIND);
	datalen = htonl(bloblen);

	/* session क्रम loading the key */
	ret = oiap(tb, &authhandle, enonce);
	अगर (ret < 0) अणु
		pr_info("oiap failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* generate odd nonce */
	ret = tpm_get_अक्रमom(शून्य, nonceodd, TPM_NONCE_SIZE);
	अगर (ret < 0) अणु
		pr_info("tpm_get_random failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* calculate authorization HMAC value */
	ret = TSS_authhmac(authdata, keyauth, SHA1_DIGEST_SIZE, enonce,
			   nonceodd, cont, माप(uपूर्णांक32_t), &ordinal,
			   माप(uपूर्णांक32_t), &datalen,
			   bloblen, blob, 0, 0);
	अगर (ret < 0)
		वापस ret;

	/* build the request buffer */
	tpm_buf_reset(tb, TPM_TAG_RQU_AUTH1_COMMAND, TPM_ORD_UNBIND);
	tpm_buf_append_u32(tb, keyhandle);
	tpm_buf_append_u32(tb, bloblen);
	tpm_buf_append(tb, blob, bloblen);
	tpm_buf_append_u32(tb, authhandle);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0) अणु
		pr_info("authhmac failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	datalen = LOAD32(tb->data, TPM_DATA_OFFSET);

	ret = TSS_checkhmac1(tb->data, ordinal, nonceodd,
			     keyauth, SHA1_DIGEST_SIZE,
			     माप(uपूर्णांक32_t), TPM_DATA_OFFSET,
			     datalen, TPM_DATA_OFFSET + माप(uपूर्णांक32_t),
			     0, 0);
	अगर (ret < 0) अणु
		pr_info("TSS_checkhmac1 failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(out, tb->data + TPM_DATA_OFFSET + माप(uपूर्णांक32_t),
	       min(outlen, datalen));

	वापस datalen;
पूर्ण

/*
 * Sign a blob provided by userspace (that has had the hash function applied)
 * using a specअगरic key handle.  The handle is assumed to have been previously
 * loaded by e.g. LoadKey2.
 *
 * Note that the key signature scheme of the used key should be set to
 * TPM_SS_RSASSAPKCS1v15_DER.  This allows the hashed input to be of any size
 * up to key_length_in_bytes - 11 and not be limited to size 20 like the
 * TPM_SS_RSASSAPKCS1v15_SHA1 signature scheme.
 */
अटल पूर्णांक tpm_sign(काष्ठा tpm_buf *tb,
		    uपूर्णांक32_t keyhandle, अचिन्हित अक्षर *keyauth,
		    स्थिर अचिन्हित अक्षर *blob, uपूर्णांक32_t bloblen,
		    व्योम *out, uपूर्णांक32_t outlen)
अणु
	अचिन्हित अक्षर nonceodd[TPM_NONCE_SIZE];
	अचिन्हित अक्षर enonce[TPM_NONCE_SIZE];
	अचिन्हित अक्षर authdata[SHA1_DIGEST_SIZE];
	uपूर्णांक32_t authhandle = 0;
	अचिन्हित अक्षर cont = 0;
	uपूर्णांक32_t ordinal;
	uपूर्णांक32_t datalen;
	पूर्णांक ret;

	ordinal = htonl(TPM_ORD_SIGN);
	datalen = htonl(bloblen);

	/* session क्रम loading the key */
	ret = oiap(tb, &authhandle, enonce);
	अगर (ret < 0) अणु
		pr_info("oiap failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* generate odd nonce */
	ret = tpm_get_अक्रमom(शून्य, nonceodd, TPM_NONCE_SIZE);
	अगर (ret < 0) अणु
		pr_info("tpm_get_random failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* calculate authorization HMAC value */
	ret = TSS_authhmac(authdata, keyauth, SHA1_DIGEST_SIZE, enonce,
			   nonceodd, cont, माप(uपूर्णांक32_t), &ordinal,
			   माप(uपूर्णांक32_t), &datalen,
			   bloblen, blob, 0, 0);
	अगर (ret < 0)
		वापस ret;

	/* build the request buffer */
	tpm_buf_reset(tb, TPM_TAG_RQU_AUTH1_COMMAND, TPM_ORD_SIGN);
	tpm_buf_append_u32(tb, keyhandle);
	tpm_buf_append_u32(tb, bloblen);
	tpm_buf_append(tb, blob, bloblen);
	tpm_buf_append_u32(tb, authhandle);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0) अणु
		pr_info("authhmac failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	datalen = LOAD32(tb->data, TPM_DATA_OFFSET);

	ret = TSS_checkhmac1(tb->data, ordinal, nonceodd,
			     keyauth, SHA1_DIGEST_SIZE,
			     माप(uपूर्णांक32_t), TPM_DATA_OFFSET,
			     datalen, TPM_DATA_OFFSET + माप(uपूर्णांक32_t),
			     0, 0);
	अगर (ret < 0) अणु
		pr_info("TSS_checkhmac1 failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(out, tb->data + TPM_DATA_OFFSET + माप(uपूर्णांक32_t),
	       min(datalen, outlen));

	वापस datalen;
पूर्ण

/* Room to fit two u32 zeros क्रम algo id and parameters length. */
#घोषणा SETKEY_PARAMS_SIZE (माप(u32) * 2)

/*
 * Maximum buffer size क्रम the BER/DER encoded खुला key.  The खुला key
 * is of the क्रमm SEQUENCE अणु INTEGER n, INTEGER e पूर्ण where n is a maximum 2048
 * bit key and e is usually 65537
 * The encoding overhead is:
 * - max 4 bytes क्रम SEQUENCE
 *   - max 4 bytes क्रम INTEGER n type/length
 *     - 257 bytes of n
 *   - max 2 bytes क्रम INTEGER e type/length
 *     - 3 bytes of e
 * - 4+4 of zeros क्रम set_pub_key parameters (SETKEY_PARAMS_SIZE)
 */
#घोषणा PUB_KEY_BUF_SIZE (4 + 4 + 257 + 2 + 3 + SETKEY_PARAMS_SIZE)

/*
 * Provide a part of a description of the key क्रम /proc/keys.
 */
अटल व्योम asym_tpm_describe(स्थिर काष्ठा key *asymmetric_key,
			      काष्ठा seq_file *m)
अणु
	काष्ठा tpm_key *tk = asymmetric_key->payload.data[asym_crypto];

	अगर (!tk)
		वापस;

	seq_म_लिखो(m, "TPM1.2/Blob");
पूर्ण

अटल व्योम asym_tpm_destroy(व्योम *payload0, व्योम *payload3)
अणु
	काष्ठा tpm_key *tk = payload0;

	अगर (!tk)
		वापस;

	kमुक्त(tk->blob);
	tk->blob_len = 0;

	kमुक्त(tk);
पूर्ण

/* How many bytes will it take to encode the length */
अटल अंतरभूत uपूर्णांक32_t definite_length(uपूर्णांक32_t len)
अणु
	अगर (len <= 127)
		वापस 1;
	अगर (len <= 255)
		वापस 2;
	वापस 3;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t *encode_tag_length(uपूर्णांक8_t *buf, uपूर्णांक8_t tag,
					 uपूर्णांक32_t len)
अणु
	*buf++ = tag;

	अगर (len <= 127) अणु
		buf[0] = len;
		वापस buf + 1;
	पूर्ण

	अगर (len <= 255) अणु
		buf[0] = 0x81;
		buf[1] = len;
		वापस buf + 2;
	पूर्ण

	buf[0] = 0x82;
	put_unaligned_be16(len, buf + 1);
	वापस buf + 3;
पूर्ण

अटल uपूर्णांक32_t derive_pub_key(स्थिर व्योम *pub_key, uपूर्णांक32_t len, uपूर्णांक8_t *buf)
अणु
	uपूर्णांक8_t *cur = buf;
	uपूर्णांक32_t n_len = definite_length(len) + 1 + len + 1;
	uपूर्णांक32_t e_len = definite_length(3) + 1 + 3;
	uपूर्णांक8_t e[3] = अणु 0x01, 0x00, 0x01 पूर्ण;

	/* SEQUENCE */
	cur = encode_tag_length(cur, 0x30, n_len + e_len);
	/* INTEGER n */
	cur = encode_tag_length(cur, 0x02, len + 1);
	cur[0] = 0x00;
	स_नकल(cur + 1, pub_key, len);
	cur += len + 1;
	cur = encode_tag_length(cur, 0x02, माप(e));
	स_नकल(cur, e, माप(e));
	cur += माप(e);
	/* Zero parameters to satisfy set_pub_key ABI. */
	memzero_explicit(cur, SETKEY_PARAMS_SIZE);

	वापस cur - buf;
पूर्ण

/*
 * Determine the crypto algorithm name.
 */
अटल पूर्णांक determine_akcipher(स्थिर अक्षर *encoding, स्थिर अक्षर *hash_algo,
			      अक्षर alg_name[CRYPTO_MAX_ALG_NAME])
अणु
	अगर (म_भेद(encoding, "pkcs1") == 0) अणु
		अगर (!hash_algo) अणु
			म_नकल(alg_name, "pkcs1pad(rsa)");
			वापस 0;
		पूर्ण

		अगर (snम_लिखो(alg_name, CRYPTO_MAX_ALG_NAME, "pkcs1pad(rsa,%s)",
			     hash_algo) >= CRYPTO_MAX_ALG_NAME)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	अगर (म_भेद(encoding, "raw") == 0) अणु
		म_नकल(alg_name, "rsa");
		वापस 0;
	पूर्ण

	वापस -ENOPKG;
पूर्ण

/*
 * Query inक्रमmation about a key.
 */
अटल पूर्णांक tpm_key_query(स्थिर काष्ठा kernel_pkey_params *params,
			 काष्ठा kernel_pkey_query *info)
अणु
	काष्ठा tpm_key *tk = params->key->payload.data[asym_crypto];
	पूर्णांक ret;
	अक्षर alg_name[CRYPTO_MAX_ALG_NAME];
	काष्ठा crypto_akcipher *tfm;
	uपूर्णांक8_t der_pub_key[PUB_KEY_BUF_SIZE];
	uपूर्णांक32_t der_pub_key_len;
	पूर्णांक len;

	/* TPM only works on निजी keys, खुला keys still करोne in software */
	ret = determine_akcipher(params->encoding, params->hash_algo, alg_name);
	अगर (ret < 0)
		वापस ret;

	tfm = crypto_alloc_akcipher(alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	der_pub_key_len = derive_pub_key(tk->pub_key, tk->pub_key_len,
					 der_pub_key);

	ret = crypto_akcipher_set_pub_key(tfm, der_pub_key, der_pub_key_len);
	अगर (ret < 0)
		जाओ error_मुक्त_tfm;

	len = crypto_akcipher_maxsize(tfm);

	info->key_size = tk->key_len;
	info->max_data_size = tk->key_len / 8;
	info->max_sig_size = len;
	info->max_enc_size = len;
	info->max_dec_size = tk->key_len / 8;

	info->supported_ops = KEYCTL_SUPPORTS_ENCRYPT |
			      KEYCTL_SUPPORTS_DECRYPT |
			      KEYCTL_SUPPORTS_VERIFY |
			      KEYCTL_SUPPORTS_SIGN;

	ret = 0;
error_मुक्त_tfm:
	crypto_मुक्त_akcipher(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Encryption operation is perक्रमmed with the खुला key.  Hence it is करोne
 * in software
 */
अटल पूर्णांक tpm_key_encrypt(काष्ठा tpm_key *tk,
			   काष्ठा kernel_pkey_params *params,
			   स्थिर व्योम *in, व्योम *out)
अणु
	अक्षर alg_name[CRYPTO_MAX_ALG_NAME];
	काष्ठा crypto_akcipher *tfm;
	काष्ठा akcipher_request *req;
	काष्ठा crypto_रुको cरुको;
	काष्ठा scatterlist in_sg, out_sg;
	uपूर्णांक8_t der_pub_key[PUB_KEY_BUF_SIZE];
	uपूर्णांक32_t der_pub_key_len;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	ret = determine_akcipher(params->encoding, params->hash_algo, alg_name);
	अगर (ret < 0)
		वापस ret;

	tfm = crypto_alloc_akcipher(alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	der_pub_key_len = derive_pub_key(tk->pub_key, tk->pub_key_len,
					 der_pub_key);

	ret = crypto_akcipher_set_pub_key(tfm, der_pub_key, der_pub_key_len);
	अगर (ret < 0)
		जाओ error_मुक्त_tfm;

	ret = -ENOMEM;
	req = akcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		जाओ error_मुक्त_tfm;

	sg_init_one(&in_sg, in, params->in_len);
	sg_init_one(&out_sg, out, params->out_len);
	akcipher_request_set_crypt(req, &in_sg, &out_sg, params->in_len,
				   params->out_len);
	crypto_init_रुको(&cरुको);
	akcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
				      CRYPTO_TFM_REQ_MAY_SLEEP,
				      crypto_req_करोne, &cरुको);

	ret = crypto_akcipher_encrypt(req);
	ret = crypto_रुको_req(ret, &cरुको);

	अगर (ret == 0)
		ret = req->dst_len;

	akcipher_request_मुक्त(req);
error_मुक्त_tfm:
	crypto_मुक्त_akcipher(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Decryption operation is perक्रमmed with the निजी key in the TPM.
 */
अटल पूर्णांक tpm_key_decrypt(काष्ठा tpm_key *tk,
			   काष्ठा kernel_pkey_params *params,
			   स्थिर व्योम *in, व्योम *out)
अणु
	काष्ठा tpm_buf tb;
	uपूर्णांक32_t keyhandle;
	uपूर्णांक8_t srkauth[SHA1_DIGEST_SIZE];
	uपूर्णांक8_t keyauth[SHA1_DIGEST_SIZE];
	पूर्णांक r;

	pr_devel("==>%s()\n", __func__);

	अगर (params->hash_algo)
		वापस -ENOPKG;

	अगर (म_भेद(params->encoding, "pkcs1"))
		वापस -ENOPKG;

	r = tpm_buf_init(&tb, 0, 0);
	अगर (r)
		वापस r;

	/* TODO: Handle a non-all zero SRK authorization */
	स_रखो(srkauth, 0, माप(srkauth));

	r = tpm_loadkey2(&tb, SRKHANDLE, srkauth,
				tk->blob, tk->blob_len, &keyhandle);
	अगर (r < 0) अणु
		pr_devel("loadkey2 failed (%d)\n", r);
		जाओ error;
	पूर्ण

	/* TODO: Handle a non-all zero key authorization */
	स_रखो(keyauth, 0, माप(keyauth));

	r = tpm_unbind(&tb, keyhandle, keyauth,
		       in, params->in_len, out, params->out_len);
	अगर (r < 0)
		pr_devel("tpm_unbind failed (%d)\n", r);

	अगर (tpm_flushspecअगरic(&tb, keyhandle) < 0)
		pr_devel("flushspecific failed (%d)\n", r);

error:
	tpm_buf_destroy(&tb);
	pr_devel("<==%s() = %d\n", __func__, r);
	वापस r;
पूर्ण

/*
 * Hash algorithm OIDs plus ASN.1 DER wrappings [RFC4880 sec 5.2.2].
 */
अटल स्थिर u8 digest_info_md5[] = अणु
	0x30, 0x20, 0x30, 0x0c, 0x06, 0x08,
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05, /* OID */
	0x05, 0x00, 0x04, 0x10
पूर्ण;

अटल स्थिर u8 digest_info_sha1[] = अणु
	0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
	0x2b, 0x0e, 0x03, 0x02, 0x1a,
	0x05, 0x00, 0x04, 0x14
पूर्ण;

अटल स्थिर u8 digest_info_rmd160[] = अणु
	0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
	0x2b, 0x24, 0x03, 0x02, 0x01,
	0x05, 0x00, 0x04, 0x14
पूर्ण;

अटल स्थिर u8 digest_info_sha224[] = अणु
	0x30, 0x2d, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x04,
	0x05, 0x00, 0x04, 0x1c
पूर्ण;

अटल स्थिर u8 digest_info_sha256[] = अणु
	0x30, 0x31, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01,
	0x05, 0x00, 0x04, 0x20
पूर्ण;

अटल स्थिर u8 digest_info_sha384[] = अणु
	0x30, 0x41, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02,
	0x05, 0x00, 0x04, 0x30
पूर्ण;

अटल स्थिर u8 digest_info_sha512[] = अणु
	0x30, 0x51, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03,
	0x05, 0x00, 0x04, 0x40
पूर्ण;

अटल स्थिर काष्ठा asn1_ढाँचा अणु
	स्थिर अक्षर	*name;
	स्थिर u8	*data;
	माप_प्रकार		size;
पूर्ण asn1_ढाँचाs[] = अणु
#घोषणा _(X) अणु #X, digest_info_##X, माप(digest_info_##X) पूर्ण
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

अटल स्थिर काष्ठा asn1_ढाँचा *lookup_asn1(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा asn1_ढाँचा *p;

	क्रम (p = asn1_ढाँचाs; p->name; p++)
		अगर (म_भेद(name, p->name) == 0)
			वापस p;
	वापस शून्य;
पूर्ण

/*
 * Sign operation is perक्रमmed with the निजी key in the TPM.
 */
अटल पूर्णांक tpm_key_sign(काष्ठा tpm_key *tk,
			काष्ठा kernel_pkey_params *params,
			स्थिर व्योम *in, व्योम *out)
अणु
	काष्ठा tpm_buf tb;
	uपूर्णांक32_t keyhandle;
	uपूर्णांक8_t srkauth[SHA1_DIGEST_SIZE];
	uपूर्णांक8_t keyauth[SHA1_DIGEST_SIZE];
	व्योम *asn1_wrapped = शून्य;
	uपूर्णांक32_t in_len = params->in_len;
	पूर्णांक r;

	pr_devel("==>%s()\n", __func__);

	अगर (म_भेद(params->encoding, "pkcs1"))
		वापस -ENOPKG;

	अगर (params->hash_algo) अणु
		स्थिर काष्ठा asn1_ढाँचा *asn1 =
						lookup_asn1(params->hash_algo);

		अगर (!asn1)
			वापस -ENOPKG;

		/* request enough space क्रम the ASN.1 ढाँचा + input hash */
		asn1_wrapped = kzalloc(in_len + asn1->size, GFP_KERNEL);
		अगर (!asn1_wrapped)
			वापस -ENOMEM;

		/* Copy ASN.1 ढाँचा, then the input */
		स_नकल(asn1_wrapped, asn1->data, asn1->size);
		स_नकल(asn1_wrapped + asn1->size, in, in_len);

		in = asn1_wrapped;
		in_len += asn1->size;
	पूर्ण

	अगर (in_len > tk->key_len / 8 - 11) अणु
		r = -EOVERFLOW;
		जाओ error_मुक्त_asn1_wrapped;
	पूर्ण

	r = tpm_buf_init(&tb, 0, 0);
	अगर (r)
		जाओ error_मुक्त_asn1_wrapped;

	/* TODO: Handle a non-all zero SRK authorization */
	स_रखो(srkauth, 0, माप(srkauth));

	r = tpm_loadkey2(&tb, SRKHANDLE, srkauth,
			 tk->blob, tk->blob_len, &keyhandle);
	अगर (r < 0) अणु
		pr_devel("loadkey2 failed (%d)\n", r);
		जाओ error_मुक्त_tb;
	पूर्ण

	/* TODO: Handle a non-all zero key authorization */
	स_रखो(keyauth, 0, माप(keyauth));

	r = tpm_sign(&tb, keyhandle, keyauth, in, in_len, out, params->out_len);
	अगर (r < 0)
		pr_devel("tpm_sign failed (%d)\n", r);

	अगर (tpm_flushspecअगरic(&tb, keyhandle) < 0)
		pr_devel("flushspecific failed (%d)\n", r);

error_मुक्त_tb:
	tpm_buf_destroy(&tb);
error_मुक्त_asn1_wrapped:
	kमुक्त(asn1_wrapped);
	pr_devel("<==%s() = %d\n", __func__, r);
	वापस r;
पूर्ण

/*
 * Do encryption, decryption and signing ops.
 */
अटल पूर्णांक tpm_key_eds_op(काष्ठा kernel_pkey_params *params,
			  स्थिर व्योम *in, व्योम *out)
अणु
	काष्ठा tpm_key *tk = params->key->payload.data[asym_crypto];
	पूर्णांक ret = -EOPNOTSUPP;

	/* Perक्रमm the encryption calculation. */
	चयन (params->op) अणु
	हाल kernel_pkey_encrypt:
		ret = tpm_key_encrypt(tk, params, in, out);
		अवरोध;
	हाल kernel_pkey_decrypt:
		ret = tpm_key_decrypt(tk, params, in, out);
		अवरोध;
	हाल kernel_pkey_sign:
		ret = tpm_key_sign(tk, params, in, out);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Verअगरy a signature using a खुला key.
 */
अटल पूर्णांक tpm_key_verअगरy_signature(स्थिर काष्ठा key *key,
				    स्थिर काष्ठा खुला_key_signature *sig)
अणु
	स्थिर काष्ठा tpm_key *tk = key->payload.data[asym_crypto];
	काष्ठा crypto_रुको cरुको;
	काष्ठा crypto_akcipher *tfm;
	काष्ठा akcipher_request *req;
	काष्ठा scatterlist src_sg[2];
	अक्षर alg_name[CRYPTO_MAX_ALG_NAME];
	uपूर्णांक8_t der_pub_key[PUB_KEY_BUF_SIZE];
	uपूर्णांक32_t der_pub_key_len;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	BUG_ON(!tk);
	BUG_ON(!sig);
	BUG_ON(!sig->s);

	अगर (!sig->digest)
		वापस -ENOPKG;

	ret = determine_akcipher(sig->encoding, sig->hash_algo, alg_name);
	अगर (ret < 0)
		वापस ret;

	tfm = crypto_alloc_akcipher(alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	der_pub_key_len = derive_pub_key(tk->pub_key, tk->pub_key_len,
					 der_pub_key);

	ret = crypto_akcipher_set_pub_key(tfm, der_pub_key, der_pub_key_len);
	अगर (ret < 0)
		जाओ error_मुक्त_tfm;

	ret = -ENOMEM;
	req = akcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		जाओ error_मुक्त_tfm;

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

	akcipher_request_मुक्त(req);
error_मुक्त_tfm:
	crypto_मुक्त_akcipher(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	अगर (WARN_ON_ONCE(ret > 0))
		ret = -EINVAL;
	वापस ret;
पूर्ण

/*
 * Parse enough inक्रमmation out of TPM_KEY काष्ठाure:
 * TPM_STRUCT_VER -> 4 bytes
 * TPM_KEY_USAGE -> 2 bytes
 * TPM_KEY_FLAGS -> 4 bytes
 * TPM_AUTH_DATA_USAGE -> 1 byte
 * TPM_KEY_PARMS -> variable
 * UINT32 PCRInfoSize -> 4 bytes
 * BYTE* -> PCRInfoSize bytes
 * TPM_STORE_PUBKEY
 * UINT32 encDataSize;
 * BYTE* -> encDataSize;
 *
 * TPM_KEY_PARMS:
 * TPM_ALGORITHM_ID -> 4 bytes
 * TPM_ENC_SCHEME -> 2 bytes
 * TPM_SIG_SCHEME -> 2 bytes
 * UINT32 parmSize -> 4 bytes
 * BYTE* -> variable
 */
अटल पूर्णांक extract_key_parameters(काष्ठा tpm_key *tk)
अणु
	स्थिर व्योम *cur = tk->blob;
	uपूर्णांक32_t len = tk->blob_len;
	स्थिर व्योम *pub_key;
	uपूर्णांक32_t sz;
	uपूर्णांक32_t key_len;

	अगर (len < 11)
		वापस -EBADMSG;

	/* Ensure this is a legacy key */
	अगर (get_unaligned_be16(cur + 4) != 0x0015)
		वापस -EBADMSG;

	/* Skip to TPM_KEY_PARMS */
	cur += 11;
	len -= 11;

	अगर (len < 12)
		वापस -EBADMSG;

	/* Make sure this is an RSA key */
	अगर (get_unaligned_be32(cur) != 0x00000001)
		वापस -EBADMSG;

	/* Make sure this is TPM_ES_RSAESPKCSv15 encoding scheme */
	अगर (get_unaligned_be16(cur + 4) != 0x0002)
		वापस -EBADMSG;

	/* Make sure this is TPM_SS_RSASSAPKCS1v15_DER signature scheme */
	अगर (get_unaligned_be16(cur + 6) != 0x0003)
		वापस -EBADMSG;

	sz = get_unaligned_be32(cur + 8);
	अगर (len < sz + 12)
		वापस -EBADMSG;

	/* Move to TPM_RSA_KEY_PARMS */
	len -= 12;
	cur += 12;

	/* Grab the RSA key length */
	key_len = get_unaligned_be32(cur);

	चयन (key_len) अणु
	हाल 512:
	हाल 1024:
	हाल 1536:
	हाल 2048:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Move just past TPM_KEY_PARMS */
	cur += sz;
	len -= sz;

	अगर (len < 4)
		वापस -EBADMSG;

	sz = get_unaligned_be32(cur);
	अगर (len < 4 + sz)
		वापस -EBADMSG;

	/* Move to TPM_STORE_PUBKEY */
	cur += 4 + sz;
	len -= 4 + sz;

	/* Grab the size of the खुला key, it should jive with the key size */
	sz = get_unaligned_be32(cur);
	अगर (sz > 256)
		वापस -EINVAL;

	pub_key = cur + 4;

	tk->key_len = key_len;
	tk->pub_key = pub_key;
	tk->pub_key_len = sz;

	वापस 0;
पूर्ण

/* Given the blob, parse it and load it पूर्णांकo the TPM */
काष्ठा tpm_key *tpm_key_create(स्थिर व्योम *blob, uपूर्णांक32_t blob_len)
अणु
	पूर्णांक r;
	काष्ठा tpm_key *tk;

	r = tpm_is_tpm2(शून्य);
	अगर (r < 0)
		जाओ error;

	/* We करोn't support TPM2 yet */
	अगर (r > 0) अणु
		r = -ENODEV;
		जाओ error;
	पूर्ण

	r = -ENOMEM;
	tk = kzalloc(माप(काष्ठा tpm_key), GFP_KERNEL);
	अगर (!tk)
		जाओ error;

	tk->blob = kmemdup(blob, blob_len, GFP_KERNEL);
	अगर (!tk->blob)
		जाओ error_memdup;

	tk->blob_len = blob_len;

	r = extract_key_parameters(tk);
	अगर (r < 0)
		जाओ error_extract;

	वापस tk;

error_extract:
	kमुक्त(tk->blob);
	tk->blob_len = 0;
error_memdup:
	kमुक्त(tk);
error:
	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_key_create);

/*
 * TPM-based asymmetric key subtype
 */
काष्ठा asymmetric_key_subtype asym_tpm_subtype = अणु
	.owner			= THIS_MODULE,
	.name			= "asym_tpm",
	.name_len		= माप("asym_tpm") - 1,
	.describe		= asym_tpm_describe,
	.destroy		= asym_tpm_destroy,
	.query			= tpm_key_query,
	.eds_op			= tpm_key_eds_op,
	.verअगरy_signature	= tpm_key_verअगरy_signature,
पूर्ण;
EXPORT_SYMBOL_GPL(asym_tpm_subtype);

MODULE_DESCRIPTION("TPM based asymmetric key subtype");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
