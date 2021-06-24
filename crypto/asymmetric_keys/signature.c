<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Signature verअगरication with an asymmetric key
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "SIG: "fmt
#समावेश <keys/asymmetric-subtype.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/keyctl.h>
#समावेश <crypto/खुला_key.h>
#समावेश <keys/user-type.h>
#समावेश "asymmetric_keys.h"

/*
 * Destroy a खुला key signature.
 */
व्योम खुला_key_signature_मुक्त(काष्ठा खुला_key_signature *sig)
अणु
	पूर्णांक i;

	अगर (sig) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sig->auth_ids); i++)
			kमुक्त(sig->auth_ids[i]);
		kमुक्त(sig->s);
		kमुक्त(sig->digest);
		kमुक्त(sig);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(खुला_key_signature_मुक्त);

/**
 * query_asymmetric_key - Get inक्रमmation about an aymmetric key.
 * @params: Various parameters.
 * @info: Where to put the inक्रमmation.
 */
पूर्णांक query_asymmetric_key(स्थिर काष्ठा kernel_pkey_params *params,
			 काष्ठा kernel_pkey_query *info)
अणु
	स्थिर काष्ठा asymmetric_key_subtype *subtype;
	काष्ठा key *key = params->key;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	अगर (key->type != &key_type_asymmetric)
		वापस -EINVAL;
	subtype = asymmetric_key_subtype(key);
	अगर (!subtype ||
	    !key->payload.data[0])
		वापस -EINVAL;
	अगर (!subtype->query)
		वापस -ENOTSUPP;

	ret = subtype->query(params, info);

	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(query_asymmetric_key);

/**
 * encrypt_blob - Encrypt data using an asymmetric key
 * @params: Various parameters
 * @data: Data blob to be encrypted, length params->data_len
 * @enc: Encrypted data buffer, length params->enc_len
 *
 * Encrypt the specअगरied data blob using the निजी key specअगरied by
 * params->key.  The encrypted data is wrapped in an encoding अगर
 * params->encoding is specअगरied (eg. "pkcs1").
 *
 * Returns the length of the data placed in the encrypted data buffer or an
 * error.
 */
पूर्णांक encrypt_blob(काष्ठा kernel_pkey_params *params,
		 स्थिर व्योम *data, व्योम *enc)
अणु
	params->op = kernel_pkey_encrypt;
	वापस asymmetric_key_eds_op(params, data, enc);
पूर्ण
EXPORT_SYMBOL_GPL(encrypt_blob);

/**
 * decrypt_blob - Decrypt data using an asymmetric key
 * @params: Various parameters
 * @enc: Encrypted data to be decrypted, length params->enc_len
 * @data: Decrypted data buffer, length params->data_len
 *
 * Decrypt the specअगरied data blob using the निजी key specअगरied by
 * params->key.  The decrypted data is wrapped in an encoding अगर
 * params->encoding is specअगरied (eg. "pkcs1").
 *
 * Returns the length of the data placed in the decrypted data buffer or an
 * error.
 */
पूर्णांक decrypt_blob(काष्ठा kernel_pkey_params *params,
		 स्थिर व्योम *enc, व्योम *data)
अणु
	params->op = kernel_pkey_decrypt;
	वापस asymmetric_key_eds_op(params, enc, data);
पूर्ण
EXPORT_SYMBOL_GPL(decrypt_blob);

/**
 * create_signature - Sign some data using an asymmetric key
 * @params: Various parameters
 * @data: Data blob to be चिन्हित, length params->data_len
 * @enc: Signature buffer, length params->enc_len
 *
 * Sign the specअगरied data blob using the निजी key specअगरied by params->key.
 * The signature is wrapped in an encoding अगर params->encoding is specअगरied
 * (eg. "pkcs1").  If the encoding needs to know the digest type, this can be
 * passed through params->hash_algo (eg. "sha1").
 *
 * Returns the length of the data placed in the signature buffer or an error.
 */
पूर्णांक create_signature(काष्ठा kernel_pkey_params *params,
		     स्थिर व्योम *data, व्योम *enc)
अणु
	params->op = kernel_pkey_sign;
	वापस asymmetric_key_eds_op(params, data, enc);
पूर्ण
EXPORT_SYMBOL_GPL(create_signature);

/**
 * verअगरy_signature - Initiate the use of an asymmetric key to verअगरy a signature
 * @key: The asymmetric key to verअगरy against
 * @sig: The signature to check
 *
 * Returns 0 अगर successful or अन्यथा an error.
 */
पूर्णांक verअगरy_signature(स्थिर काष्ठा key *key,
		     स्थिर काष्ठा खुला_key_signature *sig)
अणु
	स्थिर काष्ठा asymmetric_key_subtype *subtype;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	अगर (key->type != &key_type_asymmetric)
		वापस -EINVAL;
	subtype = asymmetric_key_subtype(key);
	अगर (!subtype ||
	    !key->payload.data[0])
		वापस -EINVAL;
	अगर (!subtype->verअगरy_signature)
		वापस -ENOTSUPP;

	ret = subtype->verअगरy_signature(key, sig);

	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(verअगरy_signature);
