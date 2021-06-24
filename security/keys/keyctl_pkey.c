<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Public-key operation keyctls
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/key.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/parser.h>
#समावेश <linux/uaccess.h>
#समावेश <keys/user-type.h>
#समावेश "internal.h"

अटल व्योम keyctl_pkey_params_मुक्त(काष्ठा kernel_pkey_params *params)
अणु
	kमुक्त(params->info);
	key_put(params->key);
पूर्ण

क्रमागत अणु
	Opt_err,
	Opt_enc,		/* "enc=<encoding>" eg. "enc=oaep" */
	Opt_hash,		/* "hash=<digest-name>" eg. "hash=sha1" */
पूर्ण;

अटल स्थिर match_table_t param_keys = अणु
	अणु Opt_enc,	"enc=%s" पूर्ण,
	अणु Opt_hash,	"hash=%s" पूर्ण,
	अणु Opt_err,	शून्य पूर्ण
पूर्ण;

/*
 * Parse the inक्रमmation string which consists of key=val pairs.
 */
अटल पूर्णांक keyctl_pkey_params_parse(काष्ठा kernel_pkey_params *params)
अणु
	अचिन्हित दीर्घ token_mask = 0;
	substring_t args[MAX_OPT_ARGS];
	अक्षर *c = params->info, *p, *q;
	पूर्णांक token;

	जबतक ((p = strsep(&c, " \t"))) अणु
		अगर (*p == '\0' || *p == ' ' || *p == '\t')
			जारी;
		token = match_token(p, param_keys, args);
		अगर (token == Opt_err)
			वापस -EINVAL;
		अगर (__test_and_set_bit(token, &token_mask))
			वापस -EINVAL;
		q = args[0].from;
		अगर (!q[0])
			वापस -EINVAL;

		चयन (token) अणु
		हाल Opt_enc:
			params->encoding = q;
			अवरोध;

		हाल Opt_hash:
			params->hash_algo = q;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Interpret parameters.  Callers must always call the मुक्त function
 * on params, even अगर an error is वापसed.
 */
अटल पूर्णांक keyctl_pkey_params_get(key_serial_t id,
				  स्थिर अक्षर __user *_info,
				  काष्ठा kernel_pkey_params *params)
अणु
	key_ref_t key_ref;
	व्योम *p;
	पूर्णांक ret;

	स_रखो(params, 0, माप(*params));
	params->encoding = "raw";

	p = strndup_user(_info, PAGE_SIZE);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);
	params->info = p;

	ret = keyctl_pkey_params_parse(params);
	अगर (ret < 0)
		वापस ret;

	key_ref = lookup_user_key(id, 0, KEY_NEED_SEARCH);
	अगर (IS_ERR(key_ref))
		वापस PTR_ERR(key_ref);
	params->key = key_ref_to_ptr(key_ref);

	अगर (!params->key->type->asym_query)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

/*
 * Get parameters from userspace.  Callers must always call the मुक्त function
 * on params, even अगर an error is वापसed.
 */
अटल पूर्णांक keyctl_pkey_params_get_2(स्थिर काष्ठा keyctl_pkey_params __user *_params,
				    स्थिर अक्षर __user *_info,
				    पूर्णांक op,
				    काष्ठा kernel_pkey_params *params)
अणु
	काष्ठा keyctl_pkey_params uparams;
	काष्ठा kernel_pkey_query info;
	पूर्णांक ret;

	स_रखो(params, 0, माप(*params));
	params->encoding = "raw";

	अगर (copy_from_user(&uparams, _params, माप(uparams)) != 0)
		वापस -EFAULT;

	ret = keyctl_pkey_params_get(uparams.key_id, _info, params);
	अगर (ret < 0)
		वापस ret;

	ret = params->key->type->asym_query(params, &info);
	अगर (ret < 0)
		वापस ret;

	चयन (op) अणु
	हाल KEYCTL_PKEY_ENCRYPT:
	हाल KEYCTL_PKEY_DECRYPT:
		अगर (uparams.in_len  > info.max_enc_size ||
		    uparams.out_len > info.max_dec_size)
			वापस -EINVAL;
		अवरोध;
	हाल KEYCTL_PKEY_SIGN:
	हाल KEYCTL_PKEY_VERIFY:
		अगर (uparams.in_len  > info.max_sig_size ||
		    uparams.out_len > info.max_data_size)
			वापस -EINVAL;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	params->in_len  = uparams.in_len;
	params->out_len = uparams.out_len;
	वापस 0;
पूर्ण

/*
 * Query inक्रमmation about an asymmetric key.
 */
दीर्घ keyctl_pkey_query(key_serial_t id,
		       स्थिर अक्षर __user *_info,
		       काष्ठा keyctl_pkey_query __user *_res)
अणु
	काष्ठा kernel_pkey_params params;
	काष्ठा kernel_pkey_query res;
	दीर्घ ret;

	ret = keyctl_pkey_params_get(id, _info, &params);
	अगर (ret < 0)
		जाओ error;

	ret = params.key->type->asym_query(&params, &res);
	अगर (ret < 0)
		जाओ error;

	ret = -EFAULT;
	अगर (copy_to_user(_res, &res, माप(res)) == 0 &&
	    clear_user(_res->__spare, माप(_res->__spare)) == 0)
		ret = 0;

error:
	keyctl_pkey_params_मुक्त(&params);
	वापस ret;
पूर्ण

/*
 * Encrypt/decrypt/sign
 *
 * Encrypt data, decrypt data or sign data using a खुला key.
 *
 * _info is a string of supplementary inक्रमmation in key=val क्रमmat.  For
 * instance, it might contain:
 *
 *	"enc=pkcs1 hash=sha256"
 *
 * where enc= specअगरies the encoding and hash= selects the OID to go in that
 * particular encoding अगर required.  If enc= isn't supplied, it's assumed that
 * the caller is supplying raw values.
 *
 * If successful, the amount of data written पूर्णांकo the output buffer is
 * वापसed.
 */
दीर्घ keyctl_pkey_e_d_s(पूर्णांक op,
		       स्थिर काष्ठा keyctl_pkey_params __user *_params,
		       स्थिर अक्षर __user *_info,
		       स्थिर व्योम __user *_in,
		       व्योम __user *_out)
अणु
	काष्ठा kernel_pkey_params params;
	व्योम *in, *out;
	दीर्घ ret;

	ret = keyctl_pkey_params_get_2(_params, _info, op, &params);
	अगर (ret < 0)
		जाओ error_params;

	ret = -EOPNOTSUPP;
	अगर (!params.key->type->asym_eds_op)
		जाओ error_params;

	चयन (op) अणु
	हाल KEYCTL_PKEY_ENCRYPT:
		params.op = kernel_pkey_encrypt;
		अवरोध;
	हाल KEYCTL_PKEY_DECRYPT:
		params.op = kernel_pkey_decrypt;
		अवरोध;
	हाल KEYCTL_PKEY_SIGN:
		params.op = kernel_pkey_sign;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	in = memdup_user(_in, params.in_len);
	अगर (IS_ERR(in)) अणु
		ret = PTR_ERR(in);
		जाओ error_params;
	पूर्ण

	ret = -ENOMEM;
	out = kदो_स्मृति(params.out_len, GFP_KERNEL);
	अगर (!out)
		जाओ error_in;

	ret = params.key->type->asym_eds_op(&params, in, out);
	अगर (ret < 0)
		जाओ error_out;

	अगर (copy_to_user(_out, out, ret) != 0)
		ret = -EFAULT;

error_out:
	kमुक्त(out);
error_in:
	kमुक्त(in);
error_params:
	keyctl_pkey_params_मुक्त(&params);
	वापस ret;
पूर्ण

/*
 * Verअगरy a signature.
 *
 * Verअगरy a खुला key signature using the given key, or अगर not given, search
 * क्रम a matching key.
 *
 * _info is a string of supplementary inक्रमmation in key=val क्रमmat.  For
 * instance, it might contain:
 *
 *	"enc=pkcs1 hash=sha256"
 *
 * where enc= specअगरies the signature blob encoding and hash= selects the OID
 * to go in that particular encoding.  If enc= isn't supplied, it's assumed
 * that the caller is supplying raw values.
 *
 * If successful, 0 is वापसed.
 */
दीर्घ keyctl_pkey_verअगरy(स्थिर काष्ठा keyctl_pkey_params __user *_params,
			स्थिर अक्षर __user *_info,
			स्थिर व्योम __user *_in,
			स्थिर व्योम __user *_in2)
अणु
	काष्ठा kernel_pkey_params params;
	व्योम *in, *in2;
	दीर्घ ret;

	ret = keyctl_pkey_params_get_2(_params, _info, KEYCTL_PKEY_VERIFY,
				       &params);
	अगर (ret < 0)
		जाओ error_params;

	ret = -EOPNOTSUPP;
	अगर (!params.key->type->asym_verअगरy_signature)
		जाओ error_params;

	in = memdup_user(_in, params.in_len);
	अगर (IS_ERR(in)) अणु
		ret = PTR_ERR(in);
		जाओ error_params;
	पूर्ण

	in2 = memdup_user(_in2, params.in2_len);
	अगर (IS_ERR(in2)) अणु
		ret = PTR_ERR(in2);
		जाओ error_in;
	पूर्ण

	params.op = kernel_pkey_verअगरy;
	ret = params.key->type->asym_verअगरy_signature(&params, in, in2);

	kमुक्त(in2);
error_in:
	kमुक्त(in);
error_params:
	keyctl_pkey_params_मुक्त(&params);
	वापस ret;
पूर्ण
