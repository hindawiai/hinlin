<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <crypto/curve25519.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/kpp.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>

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

	curve25519_generic(buf, secret, bp);

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
	.base.cra_driver_name	= "curve25519-generic",
	.base.cra_priority	= 100,
	.base.cra_module	= THIS_MODULE,
	.base.cra_ctxsize	= CURVE25519_KEY_SIZE,

	.set_secret		= curve25519_set_secret,
	.generate_खुला_key	= curve25519_compute_value,
	.compute_shared_secret	= curve25519_compute_value,
	.max_size		= curve25519_max_size,
पूर्ण;

अटल पूर्णांक curve25519_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_kpp(&curve25519_alg);
पूर्ण

अटल व्योम curve25519_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_kpp(&curve25519_alg);
पूर्ण

subsys_initcall(curve25519_init);
module_निकास(curve25519_निकास);

MODULE_ALIAS_CRYPTO("curve25519");
MODULE_ALIAS_CRYPTO("curve25519-generic");
MODULE_LICENSE("GPL");
