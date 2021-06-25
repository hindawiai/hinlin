<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * DES & Triple DES EDE Cipher Algorithms.
 *
 * Copyright (c) 2005 Dag Arne Osvik <da@osvik.no>
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crypto.h>

#समावेश <crypto/पूर्णांकernal/des.h>

अटल पूर्णांक des_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा des_ctx *dctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	err = des_expand_key(dctx, key, keylen);
	अगर (err == -ENOKEY) अणु
		अगर (crypto_tfm_get_flags(tfm) & CRYPTO_TFM_REQ_FORBID_WEAK_KEYS)
			err = -EINVAL;
		अन्यथा
			err = 0;
	पूर्ण
	अगर (err)
		स_रखो(dctx, 0, माप(*dctx));
	वापस err;
पूर्ण

अटल व्योम crypto_des_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	स्थिर काष्ठा des_ctx *dctx = crypto_tfm_ctx(tfm);

	des_encrypt(dctx, dst, src);
पूर्ण

अटल व्योम crypto_des_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	स्थिर काष्ठा des_ctx *dctx = crypto_tfm_ctx(tfm);

	des_decrypt(dctx, dst, src);
पूर्ण

अटल पूर्णांक des3_ede_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा des3_ede_ctx *dctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	err = des3_ede_expand_key(dctx, key, keylen);
	अगर (err == -ENOKEY) अणु
		अगर (crypto_tfm_get_flags(tfm) & CRYPTO_TFM_REQ_FORBID_WEAK_KEYS)
			err = -EINVAL;
		अन्यथा
			err = 0;
	पूर्ण
	अगर (err)
		स_रखो(dctx, 0, माप(*dctx));
	वापस err;
पूर्ण

अटल व्योम crypto_des3_ede_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst,
				    स्थिर u8 *src)
अणु
	स्थिर काष्ठा des3_ede_ctx *dctx = crypto_tfm_ctx(tfm);

	des3_ede_encrypt(dctx, dst, src);
पूर्ण

अटल व्योम crypto_des3_ede_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst,
				    स्थिर u8 *src)
अणु
	स्थिर काष्ठा des3_ede_ctx *dctx = crypto_tfm_ctx(tfm);

	des3_ede_decrypt(dctx, dst, src);
पूर्ण

अटल काष्ठा crypto_alg des_algs[2] = अणु अणु
	.cra_name		=	"des",
	.cra_driver_name	=	"des-generic",
	.cra_priority		=	100,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा des_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	DES_KEY_SIZE,
	.cia_max_keysize	=	DES_KEY_SIZE,
	.cia_setkey		=	des_setkey,
	.cia_encrypt		=	crypto_des_encrypt,
	.cia_decrypt		=	crypto_des_decrypt पूर्ण पूर्ण
पूर्ण, अणु
	.cra_name		=	"des3_ede",
	.cra_driver_name	=	"des3_ede-generic",
	.cra_priority		=	100,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES3_EDE_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा des3_ede_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	DES3_EDE_KEY_SIZE,
	.cia_max_keysize	=	DES3_EDE_KEY_SIZE,
	.cia_setkey		=	des3_ede_setkey,
	.cia_encrypt		=	crypto_des3_ede_encrypt,
	.cia_decrypt		=	crypto_des3_ede_decrypt पूर्ण पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init des_generic_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_algs(des_algs, ARRAY_SIZE(des_algs));
पूर्ण

अटल व्योम __निकास des_generic_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_algs(des_algs, ARRAY_SIZE(des_algs));
पूर्ण

subsys_initcall(des_generic_mod_init);
module_निकास(des_generic_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DES & Triple DES EDE Cipher Algorithms");
MODULE_AUTHOR("Dag Arne Osvik <da@osvik.no>");
MODULE_ALIAS_CRYPTO("des");
MODULE_ALIAS_CRYPTO("des-generic");
MODULE_ALIAS_CRYPTO("des3_ede");
MODULE_ALIAS_CRYPTO("des3_ede-generic");
