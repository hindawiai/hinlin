<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API
 *
 * ARC4 Cipher Algorithm
 *
 * Jon Oberheide <jon@oberheide.org>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/arc4.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>

अटल पूर्णांक crypto_arc4_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			      अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा arc4_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस arc4_setkey(ctx, in_key, key_len);
पूर्ण

अटल पूर्णांक crypto_arc4_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा arc4_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes > 0) अणु
		arc4_crypt(ctx, walk.dst.virt.addr, walk.src.virt.addr,
			   walk.nbytes);
		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_arc4_init(काष्ठा crypto_skcipher *tfm)
अणु
	pr_warn_ratelimited("\"%s\" (%ld) uses obsolete ecb(arc4) skcipher\n",
			    current->comm, (अचिन्हित दीर्घ)current->pid);

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_alg arc4_alg = अणु
	/*
	 * For legacy reasons, this is named "ecb(arc4)", not "arc4".
	 * Nevertheless it's actually a stream cipher, not a block cipher.
	 */
	.base.cra_name		=	"ecb(arc4)",
	.base.cra_driver_name	=	"ecb(arc4)-generic",
	.base.cra_priority	=	100,
	.base.cra_blocksize	=	ARC4_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा arc4_ctx),
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	ARC4_MIN_KEY_SIZE,
	.max_keysize		=	ARC4_MAX_KEY_SIZE,
	.setkey			=	crypto_arc4_setkey,
	.encrypt		=	crypto_arc4_crypt,
	.decrypt		=	crypto_arc4_crypt,
	.init			=	crypto_arc4_init,
पूर्ण;

अटल पूर्णांक __init arc4_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_skcipher(&arc4_alg);
पूर्ण

अटल व्योम __निकास arc4_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_skcipher(&arc4_alg);
पूर्ण

subsys_initcall(arc4_init);
module_निकास(arc4_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ARC4 Cipher Algorithm");
MODULE_AUTHOR("Jon Oberheide <jon@oberheide.org>");
MODULE_ALIAS_CRYPTO("ecb(arc4)");
