<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * s390 arch अक्रमom implementation.
 *
 * Copyright IBM Corp. 2017, 2020
 * Author(s): Harald Freudenberger
 *
 * The s390_arch_अक्रमom_generate() function may be called from अक्रमom.c
 * in पूर्णांकerrupt context. So this implementation करोes the best to be very
 * fast. There is a buffer of अक्रमom data which is asynchronously checked
 * and filled by a workqueue thपढ़ो.
 * If there are enough bytes in the buffer the s390_arch_अक्रमom_generate()
 * just delivers these bytes. Otherwise false is वापसed until the
 * worker thपढ़ो refills the buffer.
 * The worker fills the rng buffer by pulling fresh entropy from the
 * high quality (but slow) true hardware अक्रमom generator. This entropy
 * is then spपढ़ो over the buffer with an pseuकरो अक्रमom generator PRNG.
 * As the arch_get_अक्रमom_seed_दीर्घ() fetches 8 bytes and the calling
 * function add_पूर्णांकerrupt_अक्रमomness() counts this as 1 bit entropy the
 * distribution needs to make sure there is in fact 1 bit entropy contained
 * in 8 bytes of the buffer. The current values pull 32 byte entropy
 * and scatter this पूर्णांकo a 2048 byte buffer. So 8 byte in the buffer
 * will contain 1 bit of entropy.
 * The worker thपढ़ो is rescheduled based on the अक्षरge level of the
 * buffer but at least with 500 ms delay to aव्योम too much CPU consumption.
 * So the max. amount of rng data delivered via arch_get_अक्रमom_seed is
 * limited to 4k bytes per second.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/moduleparam.h>
#समावेश <यंत्र/cpacf.h>

DEFINE_STATIC_KEY_FALSE(s390_arch_अक्रमom_available);

atomic64_t s390_arch_अक्रमom_counter = ATOMIC64_INIT(0);
EXPORT_SYMBOL(s390_arch_अक्रमom_counter);

#घोषणा ARCH_REFILL_TICKS (HZ/2)
#घोषणा ARCH_PRNG_SEED_SIZE 32
#घोषणा ARCH_RNG_BUF_SIZE 2048

अटल DEFINE_SPINLOCK(arch_rng_lock);
अटल u8 *arch_rng_buf;
अटल अचिन्हित पूर्णांक arch_rng_buf_idx;

अटल व्योम arch_rng_refill_buffer(काष्ठा work_काष्ठा *);
अटल DECLARE_DELAYED_WORK(arch_rng_work, arch_rng_refill_buffer);

bool s390_arch_अक्रमom_generate(u8 *buf, अचिन्हित पूर्णांक nbytes)
अणु
	/* max hunk is ARCH_RNG_BUF_SIZE */
	अगर (nbytes > ARCH_RNG_BUF_SIZE)
		वापस false;

	/* lock rng buffer */
	अगर (!spin_trylock(&arch_rng_lock))
		वापस false;

	/* try to resolve the requested amount of bytes from the buffer */
	arch_rng_buf_idx -= nbytes;
	अगर (arch_rng_buf_idx < ARCH_RNG_BUF_SIZE) अणु
		स_नकल(buf, arch_rng_buf + arch_rng_buf_idx, nbytes);
		atomic64_add(nbytes, &s390_arch_अक्रमom_counter);
		spin_unlock(&arch_rng_lock);
		वापस true;
	पूर्ण

	/* not enough bytes in rng buffer, refill is करोne asynchronously */
	spin_unlock(&arch_rng_lock);

	वापस false;
पूर्ण
EXPORT_SYMBOL(s390_arch_अक्रमom_generate);

अटल व्योम arch_rng_refill_buffer(काष्ठा work_काष्ठा *unused)
अणु
	अचिन्हित पूर्णांक delay = ARCH_REFILL_TICKS;

	spin_lock(&arch_rng_lock);
	अगर (arch_rng_buf_idx > ARCH_RNG_BUF_SIZE) अणु
		/* buffer is exhausted and needs refill */
		u8 seed[ARCH_PRNG_SEED_SIZE];
		u8 prng_wa[240];
		/* fetch ARCH_PRNG_SEED_SIZE bytes of entropy */
		cpacf_trng(शून्य, 0, seed, माप(seed));
		/* blow this entropy up to ARCH_RNG_BUF_SIZE with PRNG */
		स_रखो(prng_wa, 0, माप(prng_wa));
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED,
			   &prng_wa, शून्य, 0, seed, माप(seed));
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN,
			   &prng_wa, arch_rng_buf, ARCH_RNG_BUF_SIZE, शून्य, 0);
		arch_rng_buf_idx = ARCH_RNG_BUF_SIZE;
	पूर्ण
	delay += (ARCH_REFILL_TICKS * arch_rng_buf_idx) / ARCH_RNG_BUF_SIZE;
	spin_unlock(&arch_rng_lock);

	/* kick next check */
	queue_delayed_work(प्रणाली_दीर्घ_wq, &arch_rng_work, delay);
पूर्ण

/*
 * Here follows the implementation of s390_arch_get_अक्रमom_दीर्घ().
 *
 * The अक्रमom दीर्घs to be pulled by arch_get_अक्रमom_दीर्घ() are
 * prepared in an 4K buffer which is filled from the NIST 800-90
 * compliant s390 drbg. By शेष the अक्रमom दीर्घ buffer is refilled
 * 256 बार beक्रमe the drbg itself needs a reseed. The reseed of the
 * drbg is करोne with 32 bytes fetched from the high quality (but slow)
 * trng which is assumed to deliver 100% entropy. So the 32 * 8 = 256
 * bits of entropy are spपढ़ो over 256 * 4KB = 1MB serving 131072
 * arch_get_अक्रमom_दीर्घ() invocations beक्रमe reseeded.
 *
 * How often the 4K अक्रमom दीर्घ buffer is refilled with the drbg
 * beक्रमe the drbg is reseeded can be adjusted. There is a module
 * parameter 's390_arch_rnd_long_drbg_reseed' accessible via
 *   /sys/module/arch_अक्रमom/parameters/rndदीर्घ_drbg_reseed
 * or as kernel command line parameter
 *   arch_अक्रमom.rndदीर्घ_drbg_reseed=<value>
 * This parameter tells how often the drbg fills the 4K buffer beक्रमe
 * it is re-seeded by fresh entropy from the trng.
 * A value of 16 results in reseeding the drbg at every 16 * 4 KB = 64
 * KB with 32 bytes of fresh entropy pulled from the trng. So a value
 * of 16 would result in 256 bits entropy per 64 KB.
 * A value of 256 results in 1MB of drbg output beक्रमe a reseed of the
 * drbg is करोne. So this would spपढ़ो the 256 bits of entropy among 1MB.
 * Setting this parameter to 0 क्रमces the reseed to take place every
 * समय the 4K buffer is depleted, so the entropy rises to 256 bits
 * entropy per 4K or 0.5 bit entropy per arch_get_अक्रमom_दीर्घ().  With
 * setting this parameter to negative values all this efक्रमt is
 * disabled, arch_get_अक्रमom दीर्घ() वापसs false and thus indicating
 * that the arch_get_अक्रमom_दीर्घ() feature is disabled at all.
 */

अटल अचिन्हित दीर्घ rndदीर्घ_buf[512];
अटल DEFINE_SPINLOCK(rndदीर्घ_lock);
अटल पूर्णांक rndदीर्घ_buf_index;

अटल पूर्णांक rndदीर्घ_drbg_reseed = 256;
module_param_named(rndदीर्घ_drbg_reseed, rndदीर्घ_drbg_reseed, पूर्णांक, 0600);
MODULE_PARM_DESC(rndदीर्घ_drbg_reseed, "s390 arch_get_random_long() drbg reseed");

अटल अंतरभूत व्योम refill_rndदीर्घ_buf(व्योम)
अणु
	अटल u8 prng_ws[240];
	अटल पूर्णांक drbg_counter;

	अगर (--drbg_counter < 0) अणु
		/* need to re-seed the drbg */
		u8 seed[32];

		/* fetch seed from trng */
		cpacf_trng(शून्य, 0, seed, माप(seed));
		/* seed drbg */
		स_रखो(prng_ws, 0, माप(prng_ws));
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED,
			   &prng_ws, शून्य, 0, seed, माप(seed));
		/* re-init counter क्रम drbg */
		drbg_counter = rndदीर्घ_drbg_reseed;
	पूर्ण

	/* fill the arch_get_अक्रमom_दीर्घ buffer from drbg */
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN, &prng_ws,
		   (u8 *) rndदीर्घ_buf, माप(rndदीर्घ_buf),
		   शून्य, 0);
पूर्ण

bool s390_arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	bool rc = false;
	अचिन्हित दीर्घ flags;

	/* arch_get_अक्रमom_दीर्घ() disabled ? */
	अगर (rndदीर्घ_drbg_reseed < 0)
		वापस false;

	/* try to lock the अक्रमom दीर्घ lock */
	अगर (!spin_trylock_irqsave(&rndदीर्घ_lock, flags))
		वापस false;

	अगर (--rndदीर्घ_buf_index >= 0) अणु
		/* deliver next दीर्घ value from the buffer */
		*v = rndदीर्घ_buf[rndदीर्घ_buf_index];
		rc = true;
		जाओ out;
	पूर्ण

	/* buffer is depleted and needs refill */
	अगर (in_पूर्णांकerrupt()) अणु
		/* delay refill in पूर्णांकerrupt context to next caller */
		rndदीर्घ_buf_index = 0;
		जाओ out;
	पूर्ण

	/* refill अक्रमom दीर्घ buffer */
	refill_rndदीर्घ_buf();
	rndदीर्घ_buf_index = ARRAY_SIZE(rndदीर्घ_buf);

	/* and provide one अक्रमom दीर्घ */
	*v = rndदीर्घ_buf[--rndदीर्घ_buf_index];
	rc = true;

out:
	spin_unlock_irqrestore(&rndदीर्घ_lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(s390_arch_get_अक्रमom_दीर्घ);

अटल पूर्णांक __init s390_arch_अक्रमom_init(व्योम)
अणु
	/* all the needed PRNO subfunctions available ? */
	अगर (cpacf_query_func(CPACF_PRNO, CPACF_PRNO_TRNG) &&
	    cpacf_query_func(CPACF_PRNO, CPACF_PRNO_SHA512_DRNG_GEN)) अणु

		/* alloc arch अक्रमom working buffer */
		arch_rng_buf = kदो_स्मृति(ARCH_RNG_BUF_SIZE, GFP_KERNEL);
		अगर (!arch_rng_buf)
			वापस -ENOMEM;

		/* kick worker queue job to fill the अक्रमom buffer */
		queue_delayed_work(प्रणाली_दीर्घ_wq,
				   &arch_rng_work, ARCH_REFILL_TICKS);

		/* enable arch अक्रमom to the outside world */
		अटल_branch_enable(&s390_arch_अक्रमom_available);
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(s390_arch_अक्रमom_init);
