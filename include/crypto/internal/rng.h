<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RNG: Ranकरोm Number Generator  algorithms under the crypto API
 *
 * Copyright (c) 2008 Neil Horman <nhorman@tuxdriver.com>
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_INTERNAL_RNG_H
#घोषणा _CRYPTO_INTERNAL_RNG_H

#समावेश <crypto/algapi.h>
#समावेश <crypto/rng.h>

पूर्णांक crypto_रेजिस्टर_rng(काष्ठा rng_alg *alg);
व्योम crypto_unरेजिस्टर_rng(काष्ठा rng_alg *alg);
पूर्णांक crypto_रेजिस्टर_rngs(काष्ठा rng_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_rngs(काष्ठा rng_alg *algs, पूर्णांक count);

#अगर defined(CONFIG_CRYPTO_RNG) || defined(CONFIG_CRYPTO_RNG_MODULE)
पूर्णांक crypto_del_शेष_rng(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक crypto_del_शेष_rng(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम *crypto_rng_ctx(काष्ठा crypto_rng *tfm)
अणु
	वापस crypto_tfm_ctx(&tfm->base);
पूर्ण

अटल अंतरभूत व्योम crypto_rng_set_entropy(काष्ठा crypto_rng *tfm,
					  स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	crypto_rng_alg(tfm)->set_ent(tfm, data, len);
पूर्ण

#पूर्ण_अगर
