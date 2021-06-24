<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RSA key extract helper
 *
 * Copyright (c) 2015, Intel Corporation
 * Authors: Tadeusz Struk <tadeusz.struk@पूर्णांकel.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/fips.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>
#समावेश "rsapubkey.asn1.h"
#समावेश "rsaprivkey.asn1.h"

पूर्णांक rsa_get_n(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;
	स्थिर u8 *ptr = value;
	माप_प्रकार n_sz = vlen;

	/* invalid key provided */
	अगर (!value || !vlen)
		वापस -EINVAL;

	अगर (fips_enabled) अणु
		जबतक (n_sz && !*ptr) अणु
			ptr++;
			n_sz--;
		पूर्ण

		/* In FIPS mode only allow key size 2K and higher */
		अगर (n_sz < 256) अणु
			pr_err("RSA: key size not allowed in FIPS mode\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	key->n = value;
	key->n_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_e(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !key->n_sz || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->e = value;
	key->e_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_d(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !key->n_sz || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->d = value;
	key->d_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_p(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->p = value;
	key->p_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_q(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->q = value;
	key->q_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_dp(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->dp = value;
	key->dp_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_dq(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
	       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->dq = value;
	key->dq_sz = vlen;

	वापस 0;
पूर्ण

पूर्णांक rsa_get_qinv(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
		 स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा rsa_key *key = context;

	/* invalid key provided */
	अगर (!value || !vlen || vlen > key->n_sz)
		वापस -EINVAL;

	key->qinv = value;
	key->qinv_sz = vlen;

	वापस 0;
पूर्ण

/**
 * rsa_parse_pub_key() - decodes the BER encoded buffer and stores in the
 *                       provided काष्ठा rsa_key, poपूर्णांकers to the raw key as is,
 *                       so that the caller can copy it or MPI parse it, etc.
 *
 * @rsa_key:	काष्ठा rsa_key key representation
 * @key:	key in BER क्रमmat
 * @key_len:	length of key
 *
 * Return:	0 on success or error code in हाल of error
 */
पूर्णांक rsa_parse_pub_key(काष्ठा rsa_key *rsa_key, स्थिर व्योम *key,
		      अचिन्हित पूर्णांक key_len)
अणु
	वापस asn1_ber_decoder(&rsapubkey_decoder, rsa_key, key, key_len);
पूर्ण
EXPORT_SYMBOL_GPL(rsa_parse_pub_key);

/**
 * rsa_parse_priv_key() - decodes the BER encoded buffer and stores in the
 *                        provided काष्ठा rsa_key, poपूर्णांकers to the raw key
 *                        as is, so that the caller can copy it or MPI parse it,
 *                        etc.
 *
 * @rsa_key:	काष्ठा rsa_key key representation
 * @key:	key in BER क्रमmat
 * @key_len:	length of key
 *
 * Return:	0 on success or error code in हाल of error
 */
पूर्णांक rsa_parse_priv_key(काष्ठा rsa_key *rsa_key, स्थिर व्योम *key,
		       अचिन्हित पूर्णांक key_len)
अणु
	वापस asn1_ber_decoder(&rsaprivkey_decoder, rsa_key, key, key_len);
पूर्ण
EXPORT_SYMBOL_GPL(rsa_parse_priv_key);
