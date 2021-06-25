<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <crypto/dh.h>
#समावेश <crypto/kpp.h>

#घोषणा DH_KPP_SECRET_MIN_SIZE (माप(काष्ठा kpp_secret) + 4 * माप(पूर्णांक))

अटल अंतरभूत u8 *dh_pack_data(u8 *dst, u8 *end, स्थिर व्योम *src, माप_प्रकार size)
अणु
	अगर (!dst || size > end - dst)
		वापस शून्य;
	स_नकल(dst, src, size);
	वापस dst + size;
पूर्ण

अटल अंतरभूत स्थिर u8 *dh_unpack_data(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	स_नकल(dst, src, size);
	वापस src + size;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dh_data_size(स्थिर काष्ठा dh *p)
अणु
	वापस p->key_size + p->p_size + p->q_size + p->g_size;
पूर्ण

अचिन्हित पूर्णांक crypto_dh_key_len(स्थिर काष्ठा dh *p)
अणु
	वापस DH_KPP_SECRET_MIN_SIZE + dh_data_size(p);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_dh_key_len);

पूर्णांक crypto_dh_encode_key(अक्षर *buf, अचिन्हित पूर्णांक len, स्थिर काष्ठा dh *params)
अणु
	u8 *ptr = buf;
	u8 * स्थिर end = ptr + len;
	काष्ठा kpp_secret secret = अणु
		.type = CRYPTO_KPP_SECRET_TYPE_DH,
		.len = len
	पूर्ण;

	अगर (unlikely(!len))
		वापस -EINVAL;

	ptr = dh_pack_data(ptr, end, &secret, माप(secret));
	ptr = dh_pack_data(ptr, end, &params->key_size,
			   माप(params->key_size));
	ptr = dh_pack_data(ptr, end, &params->p_size, माप(params->p_size));
	ptr = dh_pack_data(ptr, end, &params->q_size, माप(params->q_size));
	ptr = dh_pack_data(ptr, end, &params->g_size, माप(params->g_size));
	ptr = dh_pack_data(ptr, end, params->key, params->key_size);
	ptr = dh_pack_data(ptr, end, params->p, params->p_size);
	ptr = dh_pack_data(ptr, end, params->q, params->q_size);
	ptr = dh_pack_data(ptr, end, params->g, params->g_size);
	अगर (ptr != end)
		वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_dh_encode_key);

पूर्णांक crypto_dh_decode_key(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len, काष्ठा dh *params)
अणु
	स्थिर u8 *ptr = buf;
	काष्ठा kpp_secret secret;

	अगर (unlikely(!buf || len < DH_KPP_SECRET_MIN_SIZE))
		वापस -EINVAL;

	ptr = dh_unpack_data(&secret, ptr, माप(secret));
	अगर (secret.type != CRYPTO_KPP_SECRET_TYPE_DH)
		वापस -EINVAL;

	ptr = dh_unpack_data(&params->key_size, ptr, माप(params->key_size));
	ptr = dh_unpack_data(&params->p_size, ptr, माप(params->p_size));
	ptr = dh_unpack_data(&params->q_size, ptr, माप(params->q_size));
	ptr = dh_unpack_data(&params->g_size, ptr, माप(params->g_size));
	अगर (secret.len != crypto_dh_key_len(params))
		वापस -EINVAL;

	/*
	 * Don't permit the buffer for 'key' or 'g' to be larger than 'p', since
	 * some drivers assume otherwise.
	 */
	अगर (params->key_size > params->p_size ||
	    params->g_size > params->p_size || params->q_size > params->p_size)
		वापस -EINVAL;

	/* Don't allocate memory. Set poपूर्णांकers to data within
	 * the given buffer
	 */
	params->key = (व्योम *)ptr;
	params->p = (व्योम *)(ptr + params->key_size);
	params->q = (व्योम *)(ptr + params->key_size + params->p_size);
	params->g = (व्योम *)(ptr + params->key_size + params->p_size +
			     params->q_size);

	/*
	 * Don't permit 'p' to be 0.  It's not a prime number, and it's subject
	 * to corner हालs such as 'mod 0' being undefined or
	 * crypto_kpp_maxsize() वापसing 0.
	 */
	अगर (स_प्रथम_inv(params->p, 0, params->p_size) == शून्य)
		वापस -EINVAL;

	/* It is permissible to not provide Q. */
	अगर (params->q_size == 0)
		params->q = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_dh_decode_key);
