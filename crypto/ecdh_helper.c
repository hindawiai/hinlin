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
#समावेश <crypto/ecdh.h>
#समावेश <crypto/kpp.h>

#घोषणा ECDH_KPP_SECRET_MIN_SIZE (माप(काष्ठा kpp_secret) + माप(लघु))

अटल अंतरभूत u8 *ecdh_pack_data(व्योम *dst, स्थिर व्योम *src, माप_प्रकार sz)
अणु
	स_नकल(dst, src, sz);
	वापस dst + sz;
पूर्ण

अटल अंतरभूत स्थिर u8 *ecdh_unpack_data(व्योम *dst, स्थिर व्योम *src, माप_प्रकार sz)
अणु
	स_नकल(dst, src, sz);
	वापस src + sz;
पूर्ण

अचिन्हित पूर्णांक crypto_ecdh_key_len(स्थिर काष्ठा ecdh *params)
अणु
	वापस ECDH_KPP_SECRET_MIN_SIZE + params->key_size;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ecdh_key_len);

पूर्णांक crypto_ecdh_encode_key(अक्षर *buf, अचिन्हित पूर्णांक len,
			   स्थिर काष्ठा ecdh *params)
अणु
	u8 *ptr = buf;
	काष्ठा kpp_secret secret = अणु
		.type = CRYPTO_KPP_SECRET_TYPE_ECDH,
		.len = len
	पूर्ण;

	अगर (unlikely(!buf))
		वापस -EINVAL;

	अगर (len != crypto_ecdh_key_len(params))
		वापस -EINVAL;

	ptr = ecdh_pack_data(ptr, &secret, माप(secret));
	ptr = ecdh_pack_data(ptr, &params->key_size, माप(params->key_size));
	ecdh_pack_data(ptr, params->key, params->key_size);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ecdh_encode_key);

पूर्णांक crypto_ecdh_decode_key(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len,
			   काष्ठा ecdh *params)
अणु
	स्थिर u8 *ptr = buf;
	काष्ठा kpp_secret secret;

	अगर (unlikely(!buf || len < ECDH_KPP_SECRET_MIN_SIZE))
		वापस -EINVAL;

	ptr = ecdh_unpack_data(&secret, ptr, माप(secret));
	अगर (secret.type != CRYPTO_KPP_SECRET_TYPE_ECDH)
		वापस -EINVAL;

	अगर (unlikely(len < secret.len))
		वापस -EINVAL;

	ptr = ecdh_unpack_data(&params->key_size, ptr, माप(params->key_size));
	अगर (secret.len != crypto_ecdh_key_len(params))
		वापस -EINVAL;

	/* Don't allocate memory. Set poपूर्णांकer to data
	 * within the given buffer
	 */
	params->key = (व्योम *)ptr;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ecdh_decode_key);
