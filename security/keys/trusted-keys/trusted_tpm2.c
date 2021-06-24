<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 IBM Corporation
 * Copyright (C) 2014 Intel Corporation
 */

#समावेश <linux/asn1_encoder.h>
#समावेश <linux/oid_registry.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <linux/tpm.h>
#समावेश <linux/tpm_command.h>

#समावेश <keys/trusted-type.h>
#समावेश <keys/trusted_tpm.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "tpm2key.asn1.h"

अटल काष्ठा tpm2_hash tpm2_hash_map[] = अणु
	अणुHASH_ALGO_SHA1, TPM_ALG_SHA1पूर्ण,
	अणुHASH_ALGO_SHA256, TPM_ALG_SHA256पूर्ण,
	अणुHASH_ALGO_SHA384, TPM_ALG_SHA384पूर्ण,
	अणुHASH_ALGO_SHA512, TPM_ALG_SHA512पूर्ण,
	अणुHASH_ALGO_SM3_256, TPM_ALG_SM3_256पूर्ण,
पूर्ण;

अटल u32 tpm2key_oid[] = अणु 2, 23, 133, 10, 1, 5 पूर्ण;

अटल पूर्णांक tpm2_key_encode(काष्ठा trusted_key_payload *payload,
			   काष्ठा trusted_key_options *options,
			   u8 *src, u32 len)
अणु
	स्थिर पूर्णांक SCRATCH_SIZE = PAGE_SIZE;
	u8 *scratch = kदो_स्मृति(SCRATCH_SIZE, GFP_KERNEL);
	u8 *work = scratch, *work1;
	u8 *end_work = scratch + SCRATCH_SIZE;
	u8 *priv, *pub;
	u16 priv_len, pub_len;

	priv_len = get_unaligned_be16(src) + 2;
	priv = src;

	src += priv_len;

	pub_len = get_unaligned_be16(src) + 2;
	pub = src;

	अगर (!scratch)
		वापस -ENOMEM;

	work = asn1_encode_oid(work, end_work, tpm2key_oid,
			       asn1_oid_len(tpm2key_oid));

	अगर (options->blobauth_len == 0) अणु
		अचिन्हित अक्षर bool[3], *w = bool;
		/* tag 0 is emptyAuth */
		w = asn1_encode_boolean(w, w + माप(bool), true);
		अगर (WARN(IS_ERR(w), "BUG: Boolean failed to encode"))
			वापस PTR_ERR(w);
		work = asn1_encode_tag(work, end_work, 0, bool, w - bool);
	पूर्ण

	/*
	 * Assume both octet strings will encode to a 2 byte definite length
	 *
	 * Note: For a well behaved TPM, this warning should never
	 * trigger, so अगर it करोes there's something nefarious going on
	 */
	अगर (WARN(work - scratch + pub_len + priv_len + 14 > SCRATCH_SIZE,
		 "BUG: scratch buffer is too small"))
		वापस -EINVAL;

	work = asn1_encode_पूर्णांकeger(work, end_work, options->keyhandle);
	work = asn1_encode_octet_string(work, end_work, pub, pub_len);
	work = asn1_encode_octet_string(work, end_work, priv, priv_len);

	work1 = payload->blob;
	work1 = asn1_encode_sequence(work1, work1 + माप(payload->blob),
				     scratch, work - scratch);
	अगर (WARN(IS_ERR(work1), "BUG: ASN.1 encoder failed"))
		वापस PTR_ERR(work1);

	वापस work1 - payload->blob;
पूर्ण

काष्ठा tpm2_key_context अणु
	u32 parent;
	स्थिर u8 *pub;
	u32 pub_len;
	स्थिर u8 *priv;
	u32 priv_len;
पूर्ण;

अटल पूर्णांक tpm2_key_decode(काष्ठा trusted_key_payload *payload,
			   काष्ठा trusted_key_options *options,
			   u8 **buf)
अणु
	पूर्णांक ret;
	काष्ठा tpm2_key_context ctx;
	u8 *blob;

	स_रखो(&ctx, 0, माप(ctx));

	ret = asn1_ber_decoder(&tpm2key_decoder, &ctx, payload->blob,
			       payload->blob_len);
	अगर (ret < 0)
		वापस ret;

	अगर (ctx.priv_len + ctx.pub_len > MAX_BLOB_SIZE)
		वापस -EINVAL;

	blob = kदो_स्मृति(ctx.priv_len + ctx.pub_len + 4, GFP_KERNEL);
	अगर (!blob)
		वापस -ENOMEM;

	*buf = blob;
	options->keyhandle = ctx.parent;

	स_नकल(blob, ctx.priv, ctx.priv_len);
	blob += ctx.priv_len;

	स_नकल(blob, ctx.pub, ctx.pub_len);

	वापस 0;
पूर्ण

पूर्णांक tpm2_key_parent(व्योम *context, माप_प्रकार hdrlen,
		  अचिन्हित अक्षर tag,
		  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा tpm2_key_context *ctx = context;
	स्थिर u8 *v = value;
	पूर्णांक i;

	ctx->parent = 0;
	क्रम (i = 0; i < vlen; i++) अणु
		ctx->parent <<= 8;
		ctx->parent |= v[i];
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tpm2_key_type(व्योम *context, माप_प्रकार hdrlen,
		अचिन्हित अक्षर tag,
		स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	क्रमागत OID oid = look_up_OID(value, vlen);

	अगर (oid != OID_TPMSealedData) अणु
		अक्षर buffer[50];

		sprपूर्णांक_oid(value, vlen, buffer, माप(buffer));
		pr_debug("OID is \"%s\" which is not TPMSealedData\n",
			 buffer);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tpm2_key_pub(व्योम *context, माप_प्रकार hdrlen,
	       अचिन्हित अक्षर tag,
	       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा tpm2_key_context *ctx = context;

	ctx->pub = value;
	ctx->pub_len = vlen;

	वापस 0;
पूर्ण

पूर्णांक tpm2_key_priv(व्योम *context, माप_प्रकार hdrlen,
		अचिन्हित अक्षर tag,
		स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा tpm2_key_context *ctx = context;

	ctx->priv = value;
	ctx->priv_len = vlen;

	वापस 0;
पूर्ण

/**
 * tpm_buf_append_auth() - append TPMS_AUTH_COMMAND to the buffer.
 *
 * @buf: an allocated tpm_buf instance
 * @session_handle: session handle
 * @nonce: the session nonce, may be शून्य अगर not used
 * @nonce_len: the session nonce length, may be 0 अगर not used
 * @attributes: the session attributes
 * @hmac: the session HMAC or password, may be शून्य अगर not used
 * @hmac_len: the session HMAC or password length, maybe 0 अगर not used
 */
अटल व्योम tpm2_buf_append_auth(काष्ठा tpm_buf *buf, u32 session_handle,
				 स्थिर u8 *nonce, u16 nonce_len,
				 u8 attributes,
				 स्थिर u8 *hmac, u16 hmac_len)
अणु
	tpm_buf_append_u32(buf, 9 + nonce_len + hmac_len);
	tpm_buf_append_u32(buf, session_handle);
	tpm_buf_append_u16(buf, nonce_len);

	अगर (nonce && nonce_len)
		tpm_buf_append(buf, nonce, nonce_len);

	tpm_buf_append_u8(buf, attributes);
	tpm_buf_append_u16(buf, hmac_len);

	अगर (hmac && hmac_len)
		tpm_buf_append(buf, hmac, hmac_len);
पूर्ण

/**
 * tpm2_seal_trusted() - seal the payload of a trusted key
 *
 * @chip: TPM chip to use
 * @payload: the key data in clear and encrypted क्रमm
 * @options: authentication values and other options
 *
 * Return: < 0 on error and 0 on success.
 */
पूर्णांक tpm2_seal_trusted(काष्ठा tpm_chip *chip,
		      काष्ठा trusted_key_payload *payload,
		      काष्ठा trusted_key_options *options)
अणु
	पूर्णांक blob_len = 0;
	काष्ठा tpm_buf buf;
	u32 hash;
	u32 flags;
	पूर्णांक i;
	पूर्णांक rc;

	क्रम (i = 0; i < ARRAY_SIZE(tpm2_hash_map); i++) अणु
		अगर (options->hash == tpm2_hash_map[i].crypto_id) अणु
			hash = tpm2_hash_map[i].tpm_id;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(tpm2_hash_map))
		वापस -EINVAL;

	अगर (!options->keyhandle)
		वापस -EINVAL;

	rc = tpm_try_get_ops(chip);
	अगर (rc)
		वापस rc;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_CREATE);
	अगर (rc) अणु
		tpm_put_ops(chip);
		वापस rc;
	पूर्ण

	tpm_buf_append_u32(&buf, options->keyhandle);
	tpm2_buf_append_auth(&buf, TPM2_RS_PW,
			     शून्य /* nonce */, 0,
			     0 /* session_attributes */,
			     options->keyauth /* hmac */,
			     TPM_DIGEST_SIZE);

	/* sensitive */
	tpm_buf_append_u16(&buf, 4 + options->blobauth_len + payload->key_len);

	tpm_buf_append_u16(&buf, options->blobauth_len);
	अगर (options->blobauth_len)
		tpm_buf_append(&buf, options->blobauth, options->blobauth_len);

	tpm_buf_append_u16(&buf, payload->key_len);
	tpm_buf_append(&buf, payload->key, payload->key_len);

	/* खुला */
	tpm_buf_append_u16(&buf, 14 + options->policydigest_len);
	tpm_buf_append_u16(&buf, TPM_ALG_KEYEDHASH);
	tpm_buf_append_u16(&buf, hash);

	/* key properties */
	flags = 0;
	flags |= options->policydigest_len ? 0 : TPM2_OA_USER_WITH_AUTH;
	flags |= payload->migratable ? (TPM2_OA_FIXED_TPM |
					TPM2_OA_FIXED_PARENT) : 0;
	tpm_buf_append_u32(&buf, flags);

	/* policy */
	tpm_buf_append_u16(&buf, options->policydigest_len);
	अगर (options->policydigest_len)
		tpm_buf_append(&buf, options->policydigest,
			       options->policydigest_len);

	/* खुला parameters */
	tpm_buf_append_u16(&buf, TPM_ALG_शून्य);
	tpm_buf_append_u16(&buf, 0);

	/* outside info */
	tpm_buf_append_u16(&buf, 0);

	/* creation PCR */
	tpm_buf_append_u32(&buf, 0);

	अगर (buf.flags & TPM_BUF_OVERFLOW) अणु
		rc = -E2BIG;
		जाओ out;
	पूर्ण

	rc = tpm_transmit_cmd(chip, &buf, 4, "sealing data");
	अगर (rc)
		जाओ out;

	blob_len = be32_to_cpup((__be32 *) &buf.data[TPM_HEADER_SIZE]);
	अगर (blob_len > MAX_BLOB_SIZE) अणु
		rc = -E2BIG;
		जाओ out;
	पूर्ण
	अगर (tpm_buf_length(&buf) < TPM_HEADER_SIZE + 4 + blob_len) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	blob_len = tpm2_key_encode(payload, options,
				   &buf.data[TPM_HEADER_SIZE + 4],
				   blob_len);

out:
	tpm_buf_destroy(&buf);

	अगर (rc > 0) अणु
		अगर (tpm2_rc_value(rc) == TPM2_RC_HASH)
			rc = -EINVAL;
		अन्यथा
			rc = -EPERM;
	पूर्ण
	अगर (blob_len < 0)
		rc = blob_len;
	अन्यथा
		payload->blob_len = blob_len;

	tpm_put_ops(chip);
	वापस rc;
पूर्ण

/**
 * tpm2_load_cmd() - execute a TPM2_Load command
 *
 * @chip: TPM chip to use
 * @payload: the key data in clear and encrypted क्रमm
 * @options: authentication values and other options
 * @blob_handle: वापसed blob handle
 *
 * Return: 0 on success.
 *        -E2BIG on wrong payload size.
 *        -EPERM on tpm error status.
 *        < 0 error from tpm_send.
 */
अटल पूर्णांक tpm2_load_cmd(काष्ठा tpm_chip *chip,
			 काष्ठा trusted_key_payload *payload,
			 काष्ठा trusted_key_options *options,
			 u32 *blob_handle)
अणु
	काष्ठा tpm_buf buf;
	अचिन्हित पूर्णांक निजी_len;
	अचिन्हित पूर्णांक खुला_len;
	अचिन्हित पूर्णांक blob_len;
	u8 *blob, *pub;
	पूर्णांक rc;
	u32 attrs;

	rc = tpm2_key_decode(payload, options, &blob);
	अगर (rc) अणु
		/* old क्रमm */
		blob = payload->blob;
		payload->old_क्रमmat = 1;
	पूर्ण

	/* new क्रमmat carries keyhandle but old क्रमmat करोesn't */
	अगर (!options->keyhandle)
		वापस -EINVAL;

	/* must be big enough क्रम at least the two be16 size counts */
	अगर (payload->blob_len < 4)
		वापस -EINVAL;

	निजी_len = get_unaligned_be16(blob);

	/* must be big enough क्रम following खुला_len */
	अगर (निजी_len + 2 + 2 > (payload->blob_len))
		वापस -E2BIG;

	खुला_len = get_unaligned_be16(blob + 2 + निजी_len);
	अगर (निजी_len + 2 + खुला_len + 2 > payload->blob_len)
		वापस -E2BIG;

	pub = blob + 2 + निजी_len + 2;
	/* key attributes are always at offset 4 */
	attrs = get_unaligned_be32(pub + 4);

	अगर ((attrs & (TPM2_OA_FIXED_TPM | TPM2_OA_FIXED_PARENT)) ==
	    (TPM2_OA_FIXED_TPM | TPM2_OA_FIXED_PARENT))
		payload->migratable = 0;
	अन्यथा
		payload->migratable = 1;

	blob_len = निजी_len + खुला_len + 4;
	अगर (blob_len > payload->blob_len)
		वापस -E2BIG;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_LOAD);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&buf, options->keyhandle);
	tpm2_buf_append_auth(&buf, TPM2_RS_PW,
			     शून्य /* nonce */, 0,
			     0 /* session_attributes */,
			     options->keyauth /* hmac */,
			     TPM_DIGEST_SIZE);

	tpm_buf_append(&buf, blob, blob_len);

	अगर (buf.flags & TPM_BUF_OVERFLOW) अणु
		rc = -E2BIG;
		जाओ out;
	पूर्ण

	rc = tpm_transmit_cmd(chip, &buf, 4, "loading blob");
	अगर (!rc)
		*blob_handle = be32_to_cpup(
			(__be32 *) &buf.data[TPM_HEADER_SIZE]);

out:
	अगर (blob != payload->blob)
		kमुक्त(blob);
	tpm_buf_destroy(&buf);

	अगर (rc > 0)
		rc = -EPERM;

	वापस rc;
पूर्ण

/**
 * tpm2_unseal_cmd() - execute a TPM2_Unload command
 *
 * @chip: TPM chip to use
 * @payload: the key data in clear and encrypted क्रमm
 * @options: authentication values and other options
 * @blob_handle: blob handle
 *
 * Return: 0 on success
 *         -EPERM on tpm error status
 *         < 0 error from tpm_send
 */
अटल पूर्णांक tpm2_unseal_cmd(काष्ठा tpm_chip *chip,
			   काष्ठा trusted_key_payload *payload,
			   काष्ठा trusted_key_options *options,
			   u32 blob_handle)
अणु
	काष्ठा tpm_buf buf;
	u16 data_len;
	u8 *data;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_UNSEAL);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&buf, blob_handle);
	tpm2_buf_append_auth(&buf,
			     options->policyhandle ?
			     options->policyhandle : TPM2_RS_PW,
			     शून्य /* nonce */, 0,
			     TPM2_SA_CONTINUE_SESSION,
			     options->blobauth /* hmac */,
			     options->blobauth_len);

	rc = tpm_transmit_cmd(chip, &buf, 6, "unsealing");
	अगर (rc > 0)
		rc = -EPERM;

	अगर (!rc) अणु
		data_len = be16_to_cpup(
			(__be16 *) &buf.data[TPM_HEADER_SIZE + 4]);
		अगर (data_len < MIN_KEY_SIZE ||  data_len > MAX_KEY_SIZE) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (tpm_buf_length(&buf) < TPM_HEADER_SIZE + 6 + data_len) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण
		data = &buf.data[TPM_HEADER_SIZE + 6];

		अगर (payload->old_क्रमmat) अणु
			/* migratable flag is at the end of the key */
			स_नकल(payload->key, data, data_len - 1);
			payload->key_len = data_len - 1;
			payload->migratable = data[data_len - 1];
		पूर्ण अन्यथा अणु
			/*
			 * migratable flag alपढ़ोy collected from key
			 * attributes
			 */
			स_नकल(payload->key, data, data_len);
			payload->key_len = data_len;
		पूर्ण
	पूर्ण

out:
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

/**
 * tpm2_unseal_trusted() - unseal the payload of a trusted key
 *
 * @chip: TPM chip to use
 * @payload: the key data in clear and encrypted क्रमm
 * @options: authentication values and other options
 *
 * Return: Same as with tpm_send.
 */
पूर्णांक tpm2_unseal_trusted(काष्ठा tpm_chip *chip,
			काष्ठा trusted_key_payload *payload,
			काष्ठा trusted_key_options *options)
अणु
	u32 blob_handle;
	पूर्णांक rc;

	rc = tpm_try_get_ops(chip);
	अगर (rc)
		वापस rc;

	rc = tpm2_load_cmd(chip, payload, options, &blob_handle);
	अगर (rc)
		जाओ out;

	rc = tpm2_unseal_cmd(chip, payload, options, blob_handle);
	tpm2_flush_context(chip, blob_handle);

out:
	tpm_put_ops(chip);

	वापस rc;
पूर्ण
