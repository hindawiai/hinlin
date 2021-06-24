<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित CURVE25519_H
#घोषणा CURVE25519_H

#समावेश <crypto/algapi.h> // For crypto_memneq.
#समावेश <linux/types.h>
#समावेश <linux/अक्रमom.h>

क्रमागत curve25519_lengths अणु
	CURVE25519_KEY_SIZE = 32
पूर्ण;

बाह्य स्थिर u8 curve25519_null_poपूर्णांक[];
बाह्य स्थिर u8 curve25519_base_poपूर्णांक[];

व्योम curve25519_generic(u8 out[CURVE25519_KEY_SIZE],
			स्थिर u8 scalar[CURVE25519_KEY_SIZE],
			स्थिर u8 poपूर्णांक[CURVE25519_KEY_SIZE]);

व्योम curve25519_arch(u8 out[CURVE25519_KEY_SIZE],
		     स्थिर u8 scalar[CURVE25519_KEY_SIZE],
		     स्थिर u8 poपूर्णांक[CURVE25519_KEY_SIZE]);

व्योम curve25519_base_arch(u8 pub[CURVE25519_KEY_SIZE],
			  स्थिर u8 secret[CURVE25519_KEY_SIZE]);

bool curve25519_selftest(व्योम);

अटल अंतरभूत
bool __must_check curve25519(u8 myखुला[CURVE25519_KEY_SIZE],
			     स्थिर u8 secret[CURVE25519_KEY_SIZE],
			     स्थिर u8 basepoपूर्णांक[CURVE25519_KEY_SIZE])
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_CURVE25519))
		curve25519_arch(myखुला, secret, basepoपूर्णांक);
	अन्यथा
		curve25519_generic(myखुला, secret, basepoपूर्णांक);
	वापस crypto_memneq(myखुला, curve25519_null_poपूर्णांक,
			     CURVE25519_KEY_SIZE);
पूर्ण

अटल अंतरभूत bool
__must_check curve25519_generate_खुला(u8 pub[CURVE25519_KEY_SIZE],
					स्थिर u8 secret[CURVE25519_KEY_SIZE])
अणु
	अगर (unlikely(!crypto_memneq(secret, curve25519_null_poपूर्णांक,
				    CURVE25519_KEY_SIZE)))
		वापस false;

	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_CURVE25519))
		curve25519_base_arch(pub, secret);
	अन्यथा
		curve25519_generic(pub, secret, curve25519_base_poपूर्णांक);
	वापस crypto_memneq(pub, curve25519_null_poपूर्णांक, CURVE25519_KEY_SIZE);
पूर्ण

अटल अंतरभूत व्योम curve25519_clamp_secret(u8 secret[CURVE25519_KEY_SIZE])
अणु
	secret[0] &= 248;
	secret[31] = (secret[31] & 127) | 64;
पूर्ण

अटल अंतरभूत व्योम curve25519_generate_secret(u8 secret[CURVE25519_KEY_SIZE])
अणु
	get_अक्रमom_bytes_रुको(secret, CURVE25519_KEY_SIZE);
	curve25519_clamp_secret(secret);
पूर्ण

#पूर्ण_अगर /* CURVE25519_H */
