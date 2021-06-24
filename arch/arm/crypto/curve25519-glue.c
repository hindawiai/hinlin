<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * Based on खुला करोमुख्य code from Daniel J. Bernstein and Peter Schwabe. This
 * began from SUPERCOP's curve25519/neon2/scalarmult.s, but has subsequently been
 * manually reworked क्रम use in kernel space.
 */

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/curve25519.h>

यंत्रlinkage व्योम curve25519_neon(u8 myखुला[CURVE25519_KEY_SIZE],
				स्थिर u8 secret[CURVE25519_KEY_SIZE],
				स्थिर u8 basepoपूर्णांक[CURVE25519_KEY_SIZE]);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(have_neon);

व्योम curve25519_arch(u8 out[CURVE25519_KEY_SIZE],
		     स्थिर u8 scalar[CURVE25519_KEY_SIZE],
		     स्थिर u8 poपूर्णांक[CURVE25519_KEY_SIZE])
अणु
	अगर (अटल_branch_likely(&have_neon) && crypto_simd_usable()) अणु
		kernel_neon_begin();
		curve25519_neon(out, scalar, poपूर्णांक);
		kernel_neon_end();
	पूर्ण अन्यथा अणु
		curve25519_generic(out, scalar, poपूर्णांक);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(curve25519_arch);

व्योम curve25519_base_arch(u8 pub[CURVE25519_KEY_SIZE],
			  स्थिर u8 secret[CURVE25519_KEY_SIZE])
अणु
	वापस curve25519_arch(pub, secret, curve25519_base_poपूर्णांक);
पूर्ण
EXPORT_SYMBOL(curve25519_base_arch);

अटल पूर्णांक curve25519_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
				 अचिन्हित पूर्णांक len)
अणु
	u8 *secret = kpp_tfm_ctx(tfm);

	अगर (!len)
		curve25519_generate_secret(secret);
	अन्यथा अगर (len == CURVE25519_KEY_SIZE &&
		 crypto_memneq(buf, curve25519_null_poपूर्णांक, CURVE25519_KEY_SIZE))
		स_नकल(secret, buf, CURVE25519_KEY_SIZE);
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक curve25519_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	स्थिर u8 *secret = kpp_tfm_ctx(tfm);
	u8 खुला_key[CURVE25519_KEY_SIZE];
	u8 buf[CURVE25519_KEY_SIZE];
	पूर्णांक copied, nbytes;
	u8 स्थिर *bp;

	अगर (req->src) अणु
		copied = sg_copy_to_buffer(req->src,
					   sg_nents_क्रम_len(req->src,
							    CURVE25519_KEY_SIZE),
					   खुला_key, CURVE25519_KEY_SIZE);
		अगर (copied != CURVE25519_KEY_SIZE)
			वापस -EINVAL;
		bp = खुला_key;
	पूर्ण अन्यथा अणु
		bp = curve25519_base_poपूर्णांक;
	पूर्ण

	curve25519_arch(buf, secret, bp);

	/* might want less than we've got */
	nbytes = min_t(माप_प्रकार, CURVE25519_KEY_SIZE, req->dst_len);
	copied = sg_copy_from_buffer(req->dst, sg_nents_क्रम_len(req->dst,
								nbytes),
				     buf, nbytes);
	अगर (copied != nbytes)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक curve25519_max_size(काष्ठा crypto_kpp *tfm)
अणु
	वापस CURVE25519_KEY_SIZE;
पूर्ण

अटल काष्ठा kpp_alg curve25519_alg = अणु
	.base.cra_name		= "curve25519",
	.base.cra_driver_name	= "curve25519-neon",
	.base.cra_priority	= 200,
	.base.cra_module	= THIS_MODULE,
	.base.cra_ctxsize	= CURVE25519_KEY_SIZE,

	.set_secret		= curve25519_set_secret,
	.generate_खुला_key	= curve25519_compute_value,
	.compute_shared_secret	= curve25519_compute_value,
	.max_size		= curve25519_max_size,
पूर्ण;

अटल पूर्णांक __init mod_init(व्योम)
अणु
	अगर (elf_hwcap & HWCAP_NEON) अणु
		अटल_branch_enable(&have_neon);
		वापस IS_REACHABLE(CONFIG_CRYPTO_KPP) ?
			crypto_रेजिस्टर_kpp(&curve25519_alg) : 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_KPP) && elf_hwcap & HWCAP_NEON)
		crypto_unरेजिस्टर_kpp(&curve25519_alg);
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);

MODULE_ALIAS_CRYPTO("curve25519");
MODULE_ALIAS_CRYPTO("curve25519-neon");
MODULE_LICENSE("GPL v2");
