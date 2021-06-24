<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RNG: Ranकरोm Number Generator  algorithms under the crypto API
 *
 * Copyright (c) 2008 Neil Horman <nhorman@tuxdriver.com>
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_RNG_H
#घोषणा _CRYPTO_RNG_H

#समावेश <linux/crypto.h>

काष्ठा crypto_rng;

/**
 * काष्ठा rng_alg - अक्रमom number generator definition
 *
 * @generate:	The function defined by this variable obtains a
 *		अक्रमom number. The अक्रमom number generator transक्रमm
 *		must generate the अक्रमom number out of the context
 *		provided with this call, plus any additional data
 *		अगर provided to the call.
 * @seed:	Seed or reseed the अक्रमom number generator.  With the
 *		invocation of this function call, the अक्रमom number
 *		generator shall become पढ़ोy क्रम generation.  If the
 *		अक्रमom number generator requires a seed क्रम setting
 *		up a new state, the seed must be provided by the
 *		consumer जबतक invoking this function. The required
 *		size of the seed is defined with @seedsize .
 * @set_ent:	Set entropy that would otherwise be obtained from
 *		entropy source.  Internal use only.
 * @seedsize:	The seed size required क्रम a अक्रमom number generator
 *		initialization defined with this variable. Some
 *		अक्रमom number generators करोes not require a seed
 *		as the seeding is implemented पूर्णांकernally without
 *		the need of support by the consumer. In this हाल,
 *		the seed size is set to zero.
 * @base:	Common crypto API algorithm data काष्ठाure.
 */
काष्ठा rng_alg अणु
	पूर्णांक (*generate)(काष्ठा crypto_rng *tfm,
			स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			u8 *dst, अचिन्हित पूर्णांक dlen);
	पूर्णांक (*seed)(काष्ठा crypto_rng *tfm, स्थिर u8 *seed, अचिन्हित पूर्णांक slen);
	व्योम (*set_ent)(काष्ठा crypto_rng *tfm, स्थिर u8 *data,
			अचिन्हित पूर्णांक len);

	अचिन्हित पूर्णांक seedsize;

	काष्ठा crypto_alg base;
पूर्ण;

काष्ठा crypto_rng अणु
	काष्ठा crypto_tfm base;
पूर्ण;

बाह्य काष्ठा crypto_rng *crypto_शेष_rng;

पूर्णांक crypto_get_शेष_rng(व्योम);
व्योम crypto_put_शेष_rng(व्योम);

/**
 * DOC: Ranकरोm number generator API
 *
 * The अक्रमom number generator API is used with the ciphers of type
 * CRYPTO_ALG_TYPE_RNG (listed as type "rng" in /proc/crypto)
 */

/**
 * crypto_alloc_rng() -- allocate RNG handle
 * @alg_name: is the cra_name / name or cra_driver_name / driver name of the
 *	      message digest cipher
 * @type: specअगरies the type of the cipher
 * @mask: specअगरies the mask क्रम the cipher
 *
 * Allocate a cipher handle क्रम a अक्रमom number generator. The वापसed काष्ठा
 * crypto_rng is the cipher handle that is required क्रम any subsequent
 * API invocation क्रम that अक्रमom number generator.
 *
 * For all अक्रमom number generators, this call creates a new निजी copy of
 * the अक्रमom number generator that करोes not share a state with other
 * instances. The only exception is the "krng" अक्रमom number generator which
 * is a kernel crypto API use हाल क्रम the get_अक्रमom_bytes() function of the
 * /dev/अक्रमom driver.
 *
 * Return: allocated cipher handle in हाल of success; IS_ERR() is true in हाल
 *	   of an error, PTR_ERR() वापसs the error code.
 */
काष्ठा crypto_rng *crypto_alloc_rng(स्थिर अक्षर *alg_name, u32 type, u32 mask);

अटल अंतरभूत काष्ठा crypto_tfm *crypto_rng_tfm(काष्ठा crypto_rng *tfm)
अणु
	वापस &tfm->base;
पूर्ण

/**
 * crypto_rng_alg - obtain name of RNG
 * @tfm: cipher handle
 *
 * Return the generic name (cra_name) of the initialized अक्रमom number generator
 *
 * Return: generic name string
 */
अटल अंतरभूत काष्ठा rng_alg *crypto_rng_alg(काष्ठा crypto_rng *tfm)
अणु
	वापस container_of(crypto_rng_tfm(tfm)->__crt_alg,
			    काष्ठा rng_alg, base);
पूर्ण

/**
 * crypto_मुक्त_rng() - zeroize and मुक्त RNG handle
 * @tfm: cipher handle to be मुक्तd
 *
 * If @tfm is a शून्य or error poपूर्णांकer, this function करोes nothing.
 */
अटल अंतरभूत व्योम crypto_मुक्त_rng(काष्ठा crypto_rng *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_rng_tfm(tfm));
पूर्ण

/**
 * crypto_rng_generate() - get अक्रमom number
 * @tfm: cipher handle
 * @src: Input buffer holding additional data, may be शून्य
 * @slen: Length of additional data
 * @dst: output buffer holding the अक्रमom numbers
 * @dlen: length of the output buffer
 *
 * This function fills the caller-allocated buffer with अक्रमom
 * numbers using the अक्रमom number generator referenced by the
 * cipher handle.
 *
 * Return: 0 function was successful; < 0 अगर an error occurred
 */
अटल अंतरभूत पूर्णांक crypto_rng_generate(काष्ठा crypto_rng *tfm,
				      स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				      u8 *dst, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	पूर्णांक ret;

	crypto_stats_get(alg);
	ret = crypto_rng_alg(tfm)->generate(tfm, src, slen, dst, dlen);
	crypto_stats_rng_generate(alg, dlen, ret);
	वापस ret;
पूर्ण

/**
 * crypto_rng_get_bytes() - get अक्रमom number
 * @tfm: cipher handle
 * @rdata: output buffer holding the अक्रमom numbers
 * @dlen: length of the output buffer
 *
 * This function fills the caller-allocated buffer with अक्रमom numbers using the
 * अक्रमom number generator referenced by the cipher handle.
 *
 * Return: 0 function was successful; < 0 अगर an error occurred
 */
अटल अंतरभूत पूर्णांक crypto_rng_get_bytes(काष्ठा crypto_rng *tfm,
				       u8 *rdata, अचिन्हित पूर्णांक dlen)
अणु
	वापस crypto_rng_generate(tfm, शून्य, 0, rdata, dlen);
पूर्ण

/**
 * crypto_rng_reset() - re-initialize the RNG
 * @tfm: cipher handle
 * @seed: seed input data
 * @slen: length of the seed input data
 *
 * The reset function completely re-initializes the अक्रमom number generator
 * referenced by the cipher handle by clearing the current state. The new state
 * is initialized with the caller provided seed or स्वतःmatically, depending
 * on the अक्रमom number generator type (the ANSI X9.31 RNG requires
 * caller-provided seed, the SP800-90A DRBGs perक्रमm an स्वतःmatic seeding).
 * The seed is provided as a parameter to this function call. The provided seed
 * should have the length of the seed size defined क्रम the अक्रमom number
 * generator as defined by crypto_rng_seedsize.
 *
 * Return: 0 अगर the setting of the key was successful; < 0 अगर an error occurred
 */
पूर्णांक crypto_rng_reset(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
		     अचिन्हित पूर्णांक slen);

/**
 * crypto_rng_seedsize() - obtain seed size of RNG
 * @tfm: cipher handle
 *
 * The function वापसs the seed size क्रम the अक्रमom number generator
 * referenced by the cipher handle. This value may be zero अगर the अक्रमom
 * number generator करोes not implement or require a reseeding. For example,
 * the SP800-90A DRBGs implement an स्वतःmated reseeding after reaching a
 * pre-defined threshold.
 *
 * Return: seed size क्रम the अक्रमom number generator
 */
अटल अंतरभूत पूर्णांक crypto_rng_seedsize(काष्ठा crypto_rng *tfm)
अणु
	वापस crypto_rng_alg(tfm)->seedsize;
पूर्ण

#पूर्ण_अगर
