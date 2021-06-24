<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RSA पूर्णांकernal helpers
 *
 * Copyright (c) 2015, Intel Corporation
 * Authors: Tadeusz Struk <tadeusz.struk@पूर्णांकel.com>
 */
#अगर_अघोषित _RSA_HELPER_
#घोषणा _RSA_HELPER_
#समावेश <linux/types.h>

/**
 * rsa_key - RSA key काष्ठाure
 * @n           : RSA modulus raw byte stream
 * @e           : RSA खुला exponent raw byte stream
 * @d           : RSA निजी exponent raw byte stream
 * @p           : RSA prime factor p of n raw byte stream
 * @q           : RSA prime factor q of n raw byte stream
 * @dp          : RSA exponent d mod (p - 1) raw byte stream
 * @dq          : RSA exponent d mod (q - 1) raw byte stream
 * @qinv        : RSA CRT coefficient q^(-1) mod p raw byte stream
 * @n_sz        : length in bytes of RSA modulus n
 * @e_sz        : length in bytes of RSA खुला exponent
 * @d_sz        : length in bytes of RSA निजी exponent
 * @p_sz        : length in bytes of p field
 * @q_sz        : length in bytes of q field
 * @dp_sz       : length in bytes of dp field
 * @dq_sz       : length in bytes of dq field
 * @qinv_sz     : length in bytes of qinv field
 */
काष्ठा rsa_key अणु
	स्थिर u8 *n;
	स्थिर u8 *e;
	स्थिर u8 *d;
	स्थिर u8 *p;
	स्थिर u8 *q;
	स्थिर u8 *dp;
	स्थिर u8 *dq;
	स्थिर u8 *qinv;
	माप_प्रकार n_sz;
	माप_प्रकार e_sz;
	माप_प्रकार d_sz;
	माप_प्रकार p_sz;
	माप_प्रकार q_sz;
	माप_प्रकार dp_sz;
	माप_प्रकार dq_sz;
	माप_प्रकार qinv_sz;
पूर्ण;

पूर्णांक rsa_parse_pub_key(काष्ठा rsa_key *rsa_key, स्थिर व्योम *key,
		      अचिन्हित पूर्णांक key_len);

पूर्णांक rsa_parse_priv_key(काष्ठा rsa_key *rsa_key, स्थिर व्योम *key,
		       अचिन्हित पूर्णांक key_len);

बाह्य काष्ठा crypto_ढाँचा rsa_pkcs1pad_पंचांगpl;
#पूर्ण_अगर
