<शैली गुरु>
/*
 * Non-physical true अक्रमom number generator based on timing jitter --
 * Linux Kernel Crypto API specअगरic code
 *
 * Copyright Stephan Mueller <smueller@chronox.de>, 2015
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU General Public License, in which हाल the provisions of the GPL2 are
 * required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fips.h>
#समावेश <linux/समय.स>
#समावेश <crypto/पूर्णांकernal/rng.h>

#समावेश "jitterentropy.h"

/***************************************************************************
 * Helper function
 ***************************************************************************/

व्योम *jent_zalloc(अचिन्हित पूर्णांक len)
अणु
	वापस kzalloc(len, GFP_KERNEL);
पूर्ण

व्योम jent_zमुक्त(व्योम *ptr)
अणु
	kमुक्त_sensitive(ptr);
पूर्ण

पूर्णांक jent_fips_enabled(व्योम)
अणु
	वापस fips_enabled;
पूर्ण

व्योम jent_panic(अक्षर *s)
अणु
	panic("%s", s);
पूर्ण

व्योम jent_स_नकल(व्योम *dest, स्थिर व्योम *src, अचिन्हित पूर्णांक n)
अणु
	स_नकल(dest, src, n);
पूर्ण

/*
 * Obtain a high-resolution समय stamp value. The समय stamp is used to measure
 * the execution समय of a given code path and its variations. Hence, the समय
 * stamp must have a sufficiently high resolution.
 *
 * Note, अगर the function वापसs zero because a given architecture करोes not
 * implement a high-resolution समय stamp, the RNG code's runसमय test
 * will detect it and will not produce output.
 */
व्योम jent_get_nsसमय(__u64 *out)
अणु
	__u64 पंचांगp = 0;

	पंचांगp = अक्रमom_get_entropy();

	/*
	 * If अक्रमom_get_entropy करोes not वापस a value, i.e. it is not
	 * implemented क्रम a given architecture, use a घड़ी source.
	 * hoping that there are समयrs we can work with.
	 */
	अगर (पंचांगp == 0)
		पंचांगp = kसमय_get_ns();

	*out = पंचांगp;
पूर्ण

/***************************************************************************
 * Kernel crypto API पूर्णांकerface
 ***************************************************************************/

काष्ठा jitterentropy अणु
	spinlock_t jent_lock;
	काष्ठा अक्रम_data *entropy_collector;
	अचिन्हित पूर्णांक reset_cnt;
पूर्ण;

अटल पूर्णांक jent_kcapi_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा jitterentropy *rng = crypto_tfm_ctx(tfm);
	पूर्णांक ret = 0;

	rng->entropy_collector = jent_entropy_collector_alloc(1, 0);
	अगर (!rng->entropy_collector)
		ret = -ENOMEM;

	spin_lock_init(&rng->jent_lock);
	वापस ret;
पूर्ण

अटल व्योम jent_kcapi_cleanup(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा jitterentropy *rng = crypto_tfm_ctx(tfm);

	spin_lock(&rng->jent_lock);
	अगर (rng->entropy_collector)
		jent_entropy_collector_मुक्त(rng->entropy_collector);
	rng->entropy_collector = शून्य;
	spin_unlock(&rng->jent_lock);
पूर्ण

अटल पूर्णांक jent_kcapi_अक्रमom(काष्ठा crypto_rng *tfm,
			     स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			     u8 *rdata, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा jitterentropy *rng = crypto_rng_ctx(tfm);
	पूर्णांक ret = 0;

	spin_lock(&rng->jent_lock);

	/* Return a permanent error in हाल we had too many resets in a row. */
	अगर (rng->reset_cnt > (1<<10)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = jent_पढ़ो_entropy(rng->entropy_collector, rdata, dlen);

	/* Reset RNG in हाल of health failures */
	अगर (ret < -1) अणु
		pr_warn_ratelimited("Reset Jitter RNG due to health test failure: %s failure\n",
				    (ret == -2) ? "Repetition Count Test" :
						  "Adaptive Proportion Test");

		rng->reset_cnt++;

		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		rng->reset_cnt = 0;

		/* Convert the Jitter RNG error पूर्णांकo a usable error code */
		अगर (ret == -1)
			ret = -EINVAL;
	पूर्ण

out:
	spin_unlock(&rng->jent_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक jent_kcapi_reset(काष्ठा crypto_rng *tfm,
			    स्थिर u8 *seed, अचिन्हित पूर्णांक slen)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा rng_alg jent_alg = अणु
	.generate		= jent_kcapi_अक्रमom,
	.seed			= jent_kcapi_reset,
	.seedsize		= 0,
	.base			= अणु
		.cra_name               = "jitterentropy_rng",
		.cra_driver_name        = "jitterentropy_rng",
		.cra_priority           = 100,
		.cra_ctxsize            = माप(काष्ठा jitterentropy),
		.cra_module             = THIS_MODULE,
		.cra_init               = jent_kcapi_init,
		.cra_निकास               = jent_kcapi_cleanup,

	पूर्ण
पूर्ण;

अटल पूर्णांक __init jent_mod_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = jent_entropy_init();
	अगर (ret) अणु
		pr_info("jitterentropy: Initialization failed with host not compliant with requirements: %d\n", ret);
		वापस -EFAULT;
	पूर्ण
	वापस crypto_रेजिस्टर_rng(&jent_alg);
पूर्ण

अटल व्योम __निकास jent_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_rng(&jent_alg);
पूर्ण

module_init(jent_mod_init);
module_निकास(jent_mod_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Stephan Mueller <smueller@chronox.de>");
MODULE_DESCRIPTION("Non-physical True Random Number Generator based on CPU Jitter");
MODULE_ALIAS_CRYPTO("jitterentropy_rng");
