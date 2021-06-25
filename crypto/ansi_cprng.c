<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PRNG: Pseuकरो Ranकरोm Number Generator
 *       Based on NIST Recommended PRNG From ANSI X9.31 Appendix A.2.4 using
 *       AES 128 cipher
 *
 *  (C) Neil Horman <nhorman@tuxdriver.com>
 */

#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>

#घोषणा DEFAULT_PRNG_KEY "0123456789abcdef"
#घोषणा DEFAULT_PRNG_KSZ 16
#घोषणा DEFAULT_BLK_SZ 16
#घोषणा DEFAULT_V_SEED "zaybxcwdveuftgsh"

/*
 * Flags क्रम the prng_context flags field
 */

#घोषणा PRNG_FIXED_SIZE 0x1
#घोषणा PRNG_NEED_RESET 0x2

/*
 * Note: DT is our counter value
 *	 I is our पूर्णांकermediate value
 *	 V is our seed vector
 * See http://csrc.nist.gov/groups/STM/cavp/करोcuments/rng/931rngext.pdf
 * क्रम implementation details
 */


काष्ठा prng_context अणु
	spinlock_t prng_lock;
	अचिन्हित अक्षर अक्रम_data[DEFAULT_BLK_SZ];
	अचिन्हित अक्षर last_अक्रम_data[DEFAULT_BLK_SZ];
	अचिन्हित अक्षर DT[DEFAULT_BLK_SZ];
	अचिन्हित अक्षर I[DEFAULT_BLK_SZ];
	अचिन्हित अक्षर V[DEFAULT_BLK_SZ];
	u32 अक्रम_data_valid;
	काष्ठा crypto_cipher *tfm;
	u32 flags;
पूर्ण;

अटल पूर्णांक dbg;

अटल व्योम hexdump(अक्षर *note, अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	अगर (dbg) अणु
		prपूर्णांकk(KERN_CRIT "%s", note);
		prपूर्णांक_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET,
				16, 1,
				buf, len, false);
	पूर्ण
पूर्ण

#घोषणा dbgprपूर्णांक(क्रमmat, args...) करो अणु\
अगर (dbg)\
	prपूर्णांकk(क्रमmat, ##args);\
पूर्ण जबतक (0)

अटल व्योम xor_vectors(अचिन्हित अक्षर *in1, अचिन्हित अक्षर *in2,
			अचिन्हित अक्षर *out, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		out[i] = in1[i] ^ in2[i];

पूर्ण
/*
 * Returns DEFAULT_BLK_SZ bytes of अक्रमom data per call
 * वापसs 0 अगर generation succeeded, <0 अगर something went wrong
 */
अटल पूर्णांक _get_more_prng_bytes(काष्ठा prng_context *ctx, पूर्णांक cont_test)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर पंचांगp[DEFAULT_BLK_SZ];
	अचिन्हित अक्षर *output = शून्य;


	dbgprपूर्णांक(KERN_CRIT "Calling _get_more_prng_bytes for context %p\n",
		ctx);

	hexdump("Input DT: ", ctx->DT, DEFAULT_BLK_SZ);
	hexdump("Input I: ", ctx->I, DEFAULT_BLK_SZ);
	hexdump("Input V: ", ctx->V, DEFAULT_BLK_SZ);

	/*
	 * This algorithm is a 3 stage state machine
	 */
	क्रम (i = 0; i < 3; i++) अणु

		चयन (i) अणु
		हाल 0:
			/*
			 * Start by encrypting the counter value
			 * This gives us an पूर्णांकermediate value I
			 */
			स_नकल(पंचांगp, ctx->DT, DEFAULT_BLK_SZ);
			output = ctx->I;
			hexdump("tmp stage 0: ", पंचांगp, DEFAULT_BLK_SZ);
			अवरोध;
		हाल 1:

			/*
			 * Next xor I with our secret vector V
			 * encrypt that result to obtain our
			 * pseuकरो अक्रमom data which we output
			 */
			xor_vectors(ctx->I, ctx->V, पंचांगp, DEFAULT_BLK_SZ);
			hexdump("tmp stage 1: ", पंचांगp, DEFAULT_BLK_SZ);
			output = ctx->अक्रम_data;
			अवरोध;
		हाल 2:
			/*
			 * First check that we didn't produce the same
			 * अक्रमom data that we did last समय around through this
			 */
			अगर (!स_भेद(ctx->अक्रम_data, ctx->last_अक्रम_data,
					DEFAULT_BLK_SZ)) अणु
				अगर (cont_test) अणु
					panic("cprng %p Failed repetition check!\n",
						ctx);
				पूर्ण

				prपूर्णांकk(KERN_ERR
					"ctx %p Failed repetition check!\n",
					ctx);

				ctx->flags |= PRNG_NEED_RESET;
				वापस -EINVAL;
			पूर्ण
			स_नकल(ctx->last_अक्रम_data, ctx->अक्रम_data,
				DEFAULT_BLK_SZ);

			/*
			 * Lastly xor the अक्रमom data with I
			 * and encrypt that to obtain a new secret vector V
			 */
			xor_vectors(ctx->अक्रम_data, ctx->I, पंचांगp,
				DEFAULT_BLK_SZ);
			output = ctx->V;
			hexdump("tmp stage 2: ", पंचांगp, DEFAULT_BLK_SZ);
			अवरोध;
		पूर्ण


		/* करो the encryption */
		crypto_cipher_encrypt_one(ctx->tfm, output, पंचांगp);

	पूर्ण

	/*
	 * Now update our DT value
	 */
	क्रम (i = DEFAULT_BLK_SZ - 1; i >= 0; i--) अणु
		ctx->DT[i] += 1;
		अगर (ctx->DT[i] != 0)
			अवरोध;
	पूर्ण

	dbgprपूर्णांक("Returning new block for context %p\n", ctx);
	ctx->अक्रम_data_valid = 0;

	hexdump("Output DT: ", ctx->DT, DEFAULT_BLK_SZ);
	hexdump("Output I: ", ctx->I, DEFAULT_BLK_SZ);
	hexdump("Output V: ", ctx->V, DEFAULT_BLK_SZ);
	hexdump("New Random Data: ", ctx->अक्रम_data, DEFAULT_BLK_SZ);

	वापस 0;
पूर्ण

/* Our exported functions */
अटल पूर्णांक get_prng_bytes(अक्षर *buf, माप_प्रकार nbytes, काष्ठा prng_context *ctx,
				पूर्णांक करो_cont_test)
अणु
	अचिन्हित अक्षर *ptr = buf;
	अचिन्हित पूर्णांक byte_count = (अचिन्हित पूर्णांक)nbytes;
	पूर्णांक err;


	spin_lock_bh(&ctx->prng_lock);

	err = -EINVAL;
	अगर (ctx->flags & PRNG_NEED_RESET)
		जाओ करोne;

	/*
	 * If the FIXED_SIZE flag is on, only वापस whole blocks of
	 * pseuकरो अक्रमom data
	 */
	err = -EINVAL;
	अगर (ctx->flags & PRNG_FIXED_SIZE) अणु
		अगर (nbytes < DEFAULT_BLK_SZ)
			जाओ करोne;
		byte_count = DEFAULT_BLK_SZ;
	पूर्ण

	/*
	 * Return 0 in हाल of success as mandated by the kernel
	 * crypto API पूर्णांकerface definition.
	 */
	err = 0;

	dbgprपूर्णांक(KERN_CRIT "getting %d random bytes for context %p\n",
		byte_count, ctx);


reमुख्यder:
	अगर (ctx->अक्रम_data_valid == DEFAULT_BLK_SZ) अणु
		अगर (_get_more_prng_bytes(ctx, करो_cont_test) < 0) अणु
			स_रखो(buf, 0, nbytes);
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Copy any data less than an entire block
	 */
	अगर (byte_count < DEFAULT_BLK_SZ) अणु
empty_rbuf:
		जबतक (ctx->अक्रम_data_valid < DEFAULT_BLK_SZ) अणु
			*ptr = ctx->अक्रम_data[ctx->अक्रम_data_valid];
			ptr++;
			byte_count--;
			ctx->अक्रम_data_valid++;
			अगर (byte_count == 0)
				जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Now copy whole blocks
	 */
	क्रम (; byte_count >= DEFAULT_BLK_SZ; byte_count -= DEFAULT_BLK_SZ) अणु
		अगर (ctx->अक्रम_data_valid == DEFAULT_BLK_SZ) अणु
			अगर (_get_more_prng_bytes(ctx, करो_cont_test) < 0) अणु
				स_रखो(buf, 0, nbytes);
				err = -EINVAL;
				जाओ करोne;
			पूर्ण
		पूर्ण
		अगर (ctx->अक्रम_data_valid > 0)
			जाओ empty_rbuf;
		स_नकल(ptr, ctx->अक्रम_data, DEFAULT_BLK_SZ);
		ctx->अक्रम_data_valid += DEFAULT_BLK_SZ;
		ptr += DEFAULT_BLK_SZ;
	पूर्ण

	/*
	 * Now go back and get any reमुख्यing partial block
	 */
	अगर (byte_count)
		जाओ reमुख्यder;

करोne:
	spin_unlock_bh(&ctx->prng_lock);
	dbgprपूर्णांक(KERN_CRIT "returning %d from get_prng_bytes in context %p\n",
		err, ctx);
	वापस err;
पूर्ण

अटल व्योम मुक्त_prng_context(काष्ठा prng_context *ctx)
अणु
	crypto_मुक्त_cipher(ctx->tfm);
पूर्ण

अटल पूर्णांक reset_prng_context(काष्ठा prng_context *ctx,
			      स्थिर अचिन्हित अक्षर *key, माप_प्रकार klen,
			      स्थिर अचिन्हित अक्षर *V, स्थिर अचिन्हित अक्षर *DT)
अणु
	पूर्णांक ret;
	स्थिर अचिन्हित अक्षर *prng_key;

	spin_lock_bh(&ctx->prng_lock);
	ctx->flags |= PRNG_NEED_RESET;

	prng_key = (key != शून्य) ? key : (अचिन्हित अक्षर *)DEFAULT_PRNG_KEY;

	अगर (!key)
		klen = DEFAULT_PRNG_KSZ;

	अगर (V)
		स_नकल(ctx->V, V, DEFAULT_BLK_SZ);
	अन्यथा
		स_नकल(ctx->V, DEFAULT_V_SEED, DEFAULT_BLK_SZ);

	अगर (DT)
		स_नकल(ctx->DT, DT, DEFAULT_BLK_SZ);
	अन्यथा
		स_रखो(ctx->DT, 0, DEFAULT_BLK_SZ);

	स_रखो(ctx->अक्रम_data, 0, DEFAULT_BLK_SZ);
	स_रखो(ctx->last_अक्रम_data, 0, DEFAULT_BLK_SZ);

	ctx->अक्रम_data_valid = DEFAULT_BLK_SZ;

	ret = crypto_cipher_setkey(ctx->tfm, prng_key, klen);
	अगर (ret) अणु
		dbgprपूर्णांक(KERN_CRIT "PRNG: setkey() failed flags=%x\n",
			crypto_cipher_get_flags(ctx->tfm));
		जाओ out;
	पूर्ण

	ret = 0;
	ctx->flags &= ~PRNG_NEED_RESET;
out:
	spin_unlock_bh(&ctx->prng_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक cprng_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा prng_context *ctx = crypto_tfm_ctx(tfm);

	spin_lock_init(&ctx->prng_lock);
	ctx->tfm = crypto_alloc_cipher("aes", 0, 0);
	अगर (IS_ERR(ctx->tfm)) अणु
		dbgprपूर्णांक(KERN_CRIT "Failed to alloc tfm for context %p\n",
				ctx);
		वापस PTR_ERR(ctx->tfm);
	पूर्ण

	अगर (reset_prng_context(ctx, शून्य, DEFAULT_PRNG_KSZ, शून्य, शून्य) < 0)
		वापस -EINVAL;

	/*
	 * after allocation, we should always क्रमce the user to reset
	 * so they करोn't inadvertently use the insecure शेष values
	 * without specअगरying them पूर्णांकentially
	 */
	ctx->flags |= PRNG_NEED_RESET;
	वापस 0;
पूर्ण

अटल व्योम cprng_निकास(काष्ठा crypto_tfm *tfm)
अणु
	मुक्त_prng_context(crypto_tfm_ctx(tfm));
पूर्ण

अटल पूर्णांक cprng_get_अक्रमom(काष्ठा crypto_rng *tfm,
			    स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			    u8 *rdata, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा prng_context *prng = crypto_rng_ctx(tfm);

	वापस get_prng_bytes(rdata, dlen, prng, 0);
पूर्ण

/*
 *  This is the cprng_रेजिस्टरed reset method the seed value is
 *  पूर्णांकerpreted as the tuple अणु V KEY DTपूर्ण
 *  V and KEY are required during reset, and DT is optional, detected
 *  as being present by testing the length of the seed
 */
अटल पूर्णांक cprng_reset(काष्ठा crypto_rng *tfm,
		       स्थिर u8 *seed, अचिन्हित पूर्णांक slen)
अणु
	काष्ठा prng_context *prng = crypto_rng_ctx(tfm);
	स्थिर u8 *key = seed + DEFAULT_BLK_SZ;
	स्थिर u8 *dt = शून्य;

	अगर (slen < DEFAULT_PRNG_KSZ + DEFAULT_BLK_SZ)
		वापस -EINVAL;

	अगर (slen >= (2 * DEFAULT_BLK_SZ + DEFAULT_PRNG_KSZ))
		dt = key + DEFAULT_PRNG_KSZ;

	reset_prng_context(prng, key, DEFAULT_PRNG_KSZ, seed, dt);

	अगर (prng->flags & PRNG_NEED_RESET)
		वापस -EINVAL;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_FIPS
अटल पूर्णांक fips_cprng_get_अक्रमom(काष्ठा crypto_rng *tfm,
				 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				 u8 *rdata, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा prng_context *prng = crypto_rng_ctx(tfm);

	वापस get_prng_bytes(rdata, dlen, prng, 1);
पूर्ण

अटल पूर्णांक fips_cprng_reset(काष्ठा crypto_rng *tfm,
			    स्थिर u8 *seed, अचिन्हित पूर्णांक slen)
अणु
	u8 rdata[DEFAULT_BLK_SZ];
	स्थिर u8 *key = seed + DEFAULT_BLK_SZ;
	पूर्णांक rc;

	काष्ठा prng_context *prng = crypto_rng_ctx(tfm);

	अगर (slen < DEFAULT_PRNG_KSZ + DEFAULT_BLK_SZ)
		वापस -EINVAL;

	/* fips strictly requires seed != key */
	अगर (!स_भेद(seed, key, DEFAULT_PRNG_KSZ))
		वापस -EINVAL;

	rc = cprng_reset(tfm, seed, slen);

	अगर (!rc)
		जाओ out;

	/* this primes our continuity test */
	rc = get_prng_bytes(rdata, DEFAULT_BLK_SZ, prng, 0);
	prng->अक्रम_data_valid = DEFAULT_BLK_SZ;

out:
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा rng_alg rng_algs[] = अणु अणु
	.generate		= cprng_get_अक्रमom,
	.seed			= cprng_reset,
	.seedsize		= DEFAULT_PRNG_KSZ + 2 * DEFAULT_BLK_SZ,
	.base			=	अणु
		.cra_name		= "stdrng",
		.cra_driver_name	= "ansi_cprng",
		.cra_priority		= 100,
		.cra_ctxsize		= माप(काष्ठा prng_context),
		.cra_module		= THIS_MODULE,
		.cra_init		= cprng_init,
		.cra_निकास		= cprng_निकास,
	पूर्ण
#अगर_घोषित CONFIG_CRYPTO_FIPS
पूर्ण, अणु
	.generate		= fips_cprng_get_अक्रमom,
	.seed			= fips_cprng_reset,
	.seedsize		= DEFAULT_PRNG_KSZ + 2 * DEFAULT_BLK_SZ,
	.base			=	अणु
		.cra_name		= "fips(ansi_cprng)",
		.cra_driver_name	= "fips_ansi_cprng",
		.cra_priority		= 300,
		.cra_ctxsize		= माप(काष्ठा prng_context),
		.cra_module		= THIS_MODULE,
		.cra_init		= cprng_init,
		.cra_निकास		= cprng_निकास,
	पूर्ण
#पूर्ण_अगर
पूर्ण पूर्ण;

/* Module initalization */
अटल पूर्णांक __init prng_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_rngs(rng_algs, ARRAY_SIZE(rng_algs));
पूर्ण

अटल व्योम __निकास prng_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_rngs(rng_algs, ARRAY_SIZE(rng_algs));
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Software Pseudo Random Number Generator");
MODULE_AUTHOR("Neil Horman <nhorman@tuxdriver.com>");
module_param(dbg, पूर्णांक, 0);
MODULE_PARM_DESC(dbg, "Boolean to enable debugging (0/1 == off/on)");
subsys_initcall(prng_mod_init);
module_निकास(prng_mod_fini);
MODULE_ALIAS_CRYPTO("stdrng");
MODULE_ALIAS_CRYPTO("ansi_cprng");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
