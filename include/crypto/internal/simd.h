<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared crypto simd helpers
 */

#अगर_अघोषित _CRYPTO_INTERNAL_SIMD_H
#घोषणा _CRYPTO_INTERNAL_SIMD_H

#समावेश <linux/percpu.h>
#समावेश <linux/types.h>

/* skcipher support */

काष्ठा simd_skcipher_alg;
काष्ठा skcipher_alg;

काष्ठा simd_skcipher_alg *simd_skcipher_create_compat(स्थिर अक्षर *algname,
						      स्थिर अक्षर *drvname,
						      स्थिर अक्षर *basename);
काष्ठा simd_skcipher_alg *simd_skcipher_create(स्थिर अक्षर *algname,
					       स्थिर अक्षर *basename);
व्योम simd_skcipher_मुक्त(काष्ठा simd_skcipher_alg *alg);

पूर्णांक simd_रेजिस्टर_skciphers_compat(काष्ठा skcipher_alg *algs, पूर्णांक count,
				   काष्ठा simd_skcipher_alg **simd_algs);

व्योम simd_unरेजिस्टर_skciphers(काष्ठा skcipher_alg *algs, पूर्णांक count,
			       काष्ठा simd_skcipher_alg **simd_algs);

/* AEAD support */

काष्ठा simd_aead_alg;
काष्ठा aead_alg;

काष्ठा simd_aead_alg *simd_aead_create_compat(स्थिर अक्षर *algname,
					      स्थिर अक्षर *drvname,
					      स्थिर अक्षर *basename);
काष्ठा simd_aead_alg *simd_aead_create(स्थिर अक्षर *algname,
				       स्थिर अक्षर *basename);
व्योम simd_aead_मुक्त(काष्ठा simd_aead_alg *alg);

पूर्णांक simd_रेजिस्टर_aeads_compat(काष्ठा aead_alg *algs, पूर्णांक count,
			       काष्ठा simd_aead_alg **simd_algs);

व्योम simd_unरेजिस्टर_aeads(काष्ठा aead_alg *algs, पूर्णांक count,
			   काष्ठा simd_aead_alg **simd_algs);

/*
 * crypto_simd_usable() - is it allowed at this समय to use SIMD inकाष्ठाions or
 *			  access the SIMD रेजिस्टर file?
 *
 * This delegates to may_use_simd(), except that this also वापसs false अगर SIMD
 * in crypto code has been temporarily disabled on this CPU by the crypto
 * self-tests, in order to test the no-SIMD fallback code.  This override is
 * currently limited to configurations where the extra self-tests are enabled,
 * because it might be a bit too invasive to be part of the regular self-tests.
 *
 * This is a macro so that <यंत्र/simd.h>, which some architectures करोn't have,
 * करोesn't have to be included directly here.
 */
#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
DECLARE_PER_CPU(bool, crypto_simd_disabled_क्रम_test);
#घोषणा crypto_simd_usable() \
	(may_use_simd() && !this_cpu_पढ़ो(crypto_simd_disabled_क्रम_test))
#अन्यथा
#घोषणा crypto_simd_usable() may_use_simd()
#पूर्ण_अगर

#पूर्ण_अगर /* _CRYPTO_INTERNAL_SIMD_H */
