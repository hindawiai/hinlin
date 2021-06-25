<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Routines supporting VMX inकाष्ठाions on the Power 8
 *
 * Copyright (C) 2015 International Business Machines Inc.
 *
 * Author: Marcelo Henrique Cerri <mhcerri@br.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/cputable.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "aesp8-ppc.h"

अटल पूर्णांक __init p8_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_shash(&p8_ghash_alg);
	अगर (ret)
		जाओ err;

	ret = crypto_रेजिस्टर_alg(&p8_aes_alg);
	अगर (ret)
		जाओ err_unरेजिस्टर_ghash;

	ret = crypto_रेजिस्टर_skcipher(&p8_aes_cbc_alg);
	अगर (ret)
		जाओ err_unरेजिस्टर_aes;

	ret = crypto_रेजिस्टर_skcipher(&p8_aes_ctr_alg);
	अगर (ret)
		जाओ err_unरेजिस्टर_aes_cbc;

	ret = crypto_रेजिस्टर_skcipher(&p8_aes_xts_alg);
	अगर (ret)
		जाओ err_unरेजिस्टर_aes_ctr;

	वापस 0;

err_unरेजिस्टर_aes_ctr:
	crypto_unरेजिस्टर_skcipher(&p8_aes_ctr_alg);
err_unरेजिस्टर_aes_cbc:
	crypto_unरेजिस्टर_skcipher(&p8_aes_cbc_alg);
err_unरेजिस्टर_aes:
	crypto_unरेजिस्टर_alg(&p8_aes_alg);
err_unरेजिस्टर_ghash:
	crypto_unरेजिस्टर_shash(&p8_ghash_alg);
err:
	वापस ret;
पूर्ण

अटल व्योम __निकास p8_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_skcipher(&p8_aes_xts_alg);
	crypto_unरेजिस्टर_skcipher(&p8_aes_ctr_alg);
	crypto_unरेजिस्टर_skcipher(&p8_aes_cbc_alg);
	crypto_unरेजिस्टर_alg(&p8_aes_alg);
	crypto_unरेजिस्टर_shash(&p8_ghash_alg);
पूर्ण

module_cpu_feature_match(PPC_MODULE_FEATURE_VEC_CRYPTO, p8_init);
module_निकास(p8_निकास);

MODULE_AUTHOR("Marcelo Cerri<mhcerri@br.ibm.com>");
MODULE_DESCRIPTION("IBM VMX cryptographic acceleration instructions "
		   "support on Power 8");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
