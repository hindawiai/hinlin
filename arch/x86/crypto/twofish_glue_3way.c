<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम 3-way parallel assembler optimized version of Twofish
 *
 * Copyright (c) 2011 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/twofish.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश "twofish.h"
#समावेश "ecb_cbc_helpers.h"

EXPORT_SYMBOL_GPL(__twofish_enc_blk_3way);
EXPORT_SYMBOL_GPL(twofish_dec_blk_3way);

अटल पूर्णांक twofish_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस twofish_setkey(&tfm->base, key, keylen);
पूर्ण

अटल अंतरभूत व्योम twofish_enc_blk_3way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__twofish_enc_blk_3way(ctx, dst, src, false);
पूर्ण

व्योम twofish_dec_blk_cbc_3way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	u8 buf[2][TF_BLOCK_SIZE];
	स्थिर u8 *s = src;

	अगर (dst == src)
		s = स_नकल(buf, src, माप(buf));
	twofish_dec_blk_3way(ctx, dst, src);
	crypto_xor(dst + TF_BLOCK_SIZE, s, माप(buf));

पूर्ण
EXPORT_SYMBOL_GPL(twofish_dec_blk_cbc_3way);

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, TF_BLOCK_SIZE, -1);
	ECB_BLOCK(3, twofish_enc_blk_3way);
	ECB_BLOCK(1, twofish_enc_blk);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, TF_BLOCK_SIZE, -1);
	ECB_BLOCK(3, twofish_dec_blk_3way);
	ECB_BLOCK(1, twofish_dec_blk);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, TF_BLOCK_SIZE, -1);
	CBC_ENC_BLOCK(twofish_enc_blk);
	CBC_WALK_END();
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, TF_BLOCK_SIZE, -1);
	CBC_DEC_BLOCK(3, twofish_dec_blk_cbc_3way);
	CBC_DEC_BLOCK(1, twofish_dec_blk);
	CBC_WALK_END();
पूर्ण

अटल काष्ठा skcipher_alg tf_skciphers[] = अणु
	अणु
		.base.cra_name		= "ecb(twofish)",
		.base.cra_driver_name	= "ecb-twofish-3way",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= TF_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा twofish_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.setkey			= twofish_setkey_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "cbc(twofish)",
		.base.cra_driver_name	= "cbc-twofish-3way",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= TF_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा twofish_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.ivsize			= TF_BLOCK_SIZE,
		.setkey			= twofish_setkey_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण,
पूर्ण;

अटल bool is_blacklisted_cpu(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस false;

	अगर (boot_cpu_data.x86 == 0x06 &&
		(boot_cpu_data.x86_model == 0x1c ||
		 boot_cpu_data.x86_model == 0x26 ||
		 boot_cpu_data.x86_model == 0x36)) अणु
		/*
		 * On Atom, twofish-3way is slower than original assembler
		 * implementation. Twofish-3way trades off some perक्रमmance in
		 * storing blocks in 64bit रेजिस्टरs to allow three blocks to
		 * be processed parallel. Parallel operation then allows gaining
		 * more perक्रमmance than was trade off, on out-of-order CPUs.
		 * However Atom करोes not benefit from this parallelism and
		 * should be blacklisted.
		 */
		वापस true;
	पूर्ण

	अगर (boot_cpu_data.x86 == 0x0f) अणु
		/*
		 * On Pentium 4, twofish-3way is slower than original assembler
		 * implementation because excessive uses of 64bit rotate and
		 * left-shअगरts (which are really slow on P4) needed to store and
		 * handle 128bit block in two 64bit रेजिस्टरs.
		 */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक क्रमce;
module_param(क्रमce, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमce, "Force module load, ignore CPU blacklist");

अटल पूर्णांक __init init(व्योम)
अणु
	अगर (!क्रमce && is_blacklisted_cpu()) अणु
		prपूर्णांकk(KERN_INFO
			"twofish-x86_64-3way: performance on this CPU "
			"would be suboptimal: disabling "
			"twofish-x86_64-3way.\n");
		वापस -ENODEV;
	पूर्ण

	वापस crypto_रेजिस्टर_skciphers(tf_skciphers,
					 ARRAY_SIZE(tf_skciphers));
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	crypto_unरेजिस्टर_skciphers(tf_skciphers, ARRAY_SIZE(tf_skciphers));
पूर्ण

module_init(init);
module_निकास(fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Twofish Cipher Algorithm, 3-way parallel asm optimized");
MODULE_ALIAS_CRYPTO("twofish");
MODULE_ALIAS_CRYPTO("twofish-asm");
