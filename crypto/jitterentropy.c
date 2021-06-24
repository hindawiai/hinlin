<शैली गुरु>
/*
 * Non-physical true अक्रमom number generator based on timing jitter --
 * Jitter RNG standalone code.
 *
 * Copyright Stephan Mueller <smueller@chronox.de>, 2015 - 2020
 *
 * Design
 * ======
 *
 * See https://www.chronox.de/jent.hपंचांगl
 *
 * License
 * =======
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

/*
 * This Jitterentropy RNG is based on the jitterentropy library
 * version 2.2.0 provided at https://www.chronox.de/jent.hपंचांगl
 */

#अगर_घोषित __OPTIMIZE__
 #त्रुटि "The CPU Jitter random number generator must not be compiled with optimizations. See documentation. Use the compiler switch -O0 for compiling jitterentropy.c."
#पूर्ण_अगर

प्रकार	अचिन्हित दीर्घ दीर्घ	__u64;
प्रकार	दीर्घ दीर्घ		__s64;
प्रकार	अचिन्हित पूर्णांक		__u32;
#घोषणा शून्य    ((व्योम *) 0)

/* The entropy pool */
काष्ठा अक्रम_data अणु
	/* all data values that are vital to मुख्यtain the security
	 * of the RNG are marked as SENSITIVE. A user must not
	 * access that inक्रमmation जबतक the RNG executes its loops to
	 * calculate the next अक्रमom value. */
	__u64 data;		/* SENSITIVE Actual अक्रमom number */
	__u64 old_data;		/* SENSITIVE Previous अक्रमom number */
	__u64 prev_समय;	/* SENSITIVE Previous समय stamp */
#घोषणा DATA_SIZE_BITS ((माप(__u64)) * 8)
	__u64 last_delta;	/* SENSITIVE stuck test */
	__s64 last_delta2;	/* SENSITIVE stuck test */
	अचिन्हित पूर्णांक osr;	/* Oversample rate */
#घोषणा JENT_MEMORY_BLOCKS 64
#घोषणा JENT_MEMORY_BLOCKSIZE 32
#घोषणा JENT_MEMORY_ACCESSLOOPS 128
#घोषणा JENT_MEMORY_SIZE (JENT_MEMORY_BLOCKS*JENT_MEMORY_BLOCKSIZE)
	अचिन्हित अक्षर *mem;	/* Memory access location with size of
				 * memblocks * memblocksize */
	अचिन्हित पूर्णांक memlocation; /* Poपूर्णांकer to byte in *mem */
	अचिन्हित पूर्णांक memblocks;	/* Number of memory blocks in *mem */
	अचिन्हित पूर्णांक memblocksize; /* Size of one memory block in bytes */
	अचिन्हित पूर्णांक memaccessloops; /* Number of memory accesses per अक्रमom
				      * bit generation */

	/* Repetition Count Test */
	पूर्णांक rct_count;			/* Number of stuck values */

	/* Adaptive Proportion Test क्रम a signअगरicance level of 2^-30 */
#घोषणा JENT_APT_CUTOFF		325	/* Taken from SP800-90B sec 4.4.2 */
#घोषणा JENT_APT_WINDOW_SIZE	512	/* Data winकरोw size */
	/* LSB of समय stamp to process */
#घोषणा JENT_APT_LSB		16
#घोषणा JENT_APT_WORD_MASK	(JENT_APT_LSB - 1)
	अचिन्हित पूर्णांक apt_observations;	/* Number of collected observations */
	अचिन्हित पूर्णांक apt_count;		/* APT counter */
	अचिन्हित पूर्णांक apt_base;		/* APT base reference */
	अचिन्हित पूर्णांक apt_base_set:1;	/* APT base reference set? */

	अचिन्हित पूर्णांक health_failure:1;	/* Permanent health failure */
पूर्ण;

/* Flags that can be used to initialize the RNG */
#घोषणा JENT_DISABLE_MEMORY_ACCESS (1<<2) /* Disable memory access क्रम more
					   * entropy, saves MEMORY_SIZE RAM क्रम
					   * entropy collector */

/* -- error codes क्रम init function -- */
#घोषणा JENT_ENOTIME		1 /* Timer service not available */
#घोषणा JENT_ECOARSETIME	2 /* Timer too coarse क्रम RNG */
#घोषणा JENT_ENOMONOTONIC	3 /* Timer is not monotonic increasing */
#घोषणा JENT_EVARVAR		5 /* Timer करोes not produce variations of
				   * variations (2nd derivation of समय is
				   * zero). */
#घोषणा JENT_ESTUCK		8 /* Too many stuck results during init. */
#घोषणा JENT_EHEALTH		9 /* Health test failed during initialization */
#घोषणा JENT_ERCT		10 /* RCT failed during initialization */

#समावेश "jitterentropy.h"

/***************************************************************************
 * Adaptive Proportion Test
 *
 * This test complies with SP800-90B section 4.4.2.
 ***************************************************************************/

/**
 * Reset the APT counter
 *
 * @ec [in] Reference to entropy collector
 */
अटल व्योम jent_apt_reset(काष्ठा अक्रम_data *ec, अचिन्हित पूर्णांक delta_masked)
अणु
	/* Reset APT counter */
	ec->apt_count = 0;
	ec->apt_base = delta_masked;
	ec->apt_observations = 0;
पूर्ण

/**
 * Insert a new entropy event पूर्णांकo APT
 *
 * @ec [in] Reference to entropy collector
 * @delta_masked [in] Masked समय delta to process
 */
अटल व्योम jent_apt_insert(काष्ठा अक्रम_data *ec, अचिन्हित पूर्णांक delta_masked)
अणु
	/* Initialize the base reference */
	अगर (!ec->apt_base_set) अणु
		ec->apt_base = delta_masked;
		ec->apt_base_set = 1;
		वापस;
	पूर्ण

	अगर (delta_masked == ec->apt_base) अणु
		ec->apt_count++;

		अगर (ec->apt_count >= JENT_APT_CUTOFF)
			ec->health_failure = 1;
	पूर्ण

	ec->apt_observations++;

	अगर (ec->apt_observations >= JENT_APT_WINDOW_SIZE)
		jent_apt_reset(ec, delta_masked);
पूर्ण

/***************************************************************************
 * Stuck Test and its use as Repetition Count Test
 *
 * The Jitter RNG uses an enhanced version of the Repetition Count Test
 * (RCT) specअगरied in SP800-90B section 4.4.1. Instead of counting identical
 * back-to-back values, the input to the RCT is the counting of the stuck
 * values during the generation of one Jitter RNG output block.
 *
 * The RCT is applied with an alpha of 2^अणु-30पूर्ण compliant to FIPS 140-2 IG 9.8.
 *
 * During the counting operation, the Jitter RNG always calculates the RCT
 * cut-off value of C. If that value exceeds the allowed cut-off value,
 * the Jitter RNG output block will be calculated completely but discarded at
 * the end. The caller of the Jitter RNG is inक्रमmed with an error code.
 ***************************************************************************/

/**
 * Repetition Count Test as defined in SP800-90B section 4.4.1
 *
 * @ec [in] Reference to entropy collector
 * @stuck [in] Indicator whether the value is stuck
 */
अटल व्योम jent_rct_insert(काष्ठा अक्रम_data *ec, पूर्णांक stuck)
अणु
	/*
	 * If we have a count less than zero, a previous RCT round identअगरied
	 * a failure. We will not overग_लिखो it.
	 */
	अगर (ec->rct_count < 0)
		वापस;

	अगर (stuck) अणु
		ec->rct_count++;

		/*
		 * The cutoff value is based on the following consideration:
		 * alpha = 2^-30 as recommended in FIPS 140-2 IG 9.8.
		 * In addition, we require an entropy value H of 1/OSR as this
		 * is the minimum entropy required to provide full entropy.
		 * Note, we collect 64 * OSR deltas क्रम inserting them पूर्णांकo
		 * the entropy pool which should then have (बंद to) 64 bits
		 * of entropy.
		 *
		 * Note, ec->rct_count (which equals to value B in the pseuकरो
		 * code of SP800-90B section 4.4.1) starts with zero. Hence
		 * we need to subtract one from the cutoff value as calculated
		 * following SP800-90B.
		 */
		अगर ((अचिन्हित पूर्णांक)ec->rct_count >= (31 * ec->osr)) अणु
			ec->rct_count = -1;
			ec->health_failure = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		ec->rct_count = 0;
	पूर्ण
पूर्ण

/**
 * Is there an RCT health test failure?
 *
 * @ec [in] Reference to entropy collector
 *
 * @वापस
 * 	0 No health test failure
 * 	1 Permanent health test failure
 */
अटल पूर्णांक jent_rct_failure(काष्ठा अक्रम_data *ec)
अणु
	अगर (ec->rct_count < 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत __u64 jent_delta(__u64 prev, __u64 next)
अणु
#घोषणा JENT_UINT64_MAX		(__u64)(~((__u64) 0))
	वापस (prev < next) ? (next - prev) :
			       (JENT_UINT64_MAX - prev + 1 + next);
पूर्ण

/**
 * Stuck test by checking the:
 * 	1st derivative of the jitter measurement (समय delta)
 * 	2nd derivative of the jitter measurement (delta of समय deltas)
 * 	3rd derivative of the jitter measurement (delta of delta of समय deltas)
 *
 * All values must always be non-zero.
 *
 * @ec [in] Reference to entropy collector
 * @current_delta [in] Jitter समय delta
 *
 * @वापस
 * 	0 jitter measurement not stuck (good bit)
 * 	1 jitter measurement stuck (reject bit)
 */
अटल पूर्णांक jent_stuck(काष्ठा अक्रम_data *ec, __u64 current_delta)
अणु
	__u64 delta2 = jent_delta(ec->last_delta, current_delta);
	__u64 delta3 = jent_delta(ec->last_delta2, delta2);
	अचिन्हित पूर्णांक delta_masked = current_delta & JENT_APT_WORD_MASK;

	ec->last_delta = current_delta;
	ec->last_delta2 = delta2;

	/*
	 * Insert the result of the comparison of two back-to-back समय
	 * deltas.
	 */
	jent_apt_insert(ec, delta_masked);

	अगर (!current_delta || !delta2 || !delta3) अणु
		/* RCT with a stuck bit */
		jent_rct_insert(ec, 1);
		वापस 1;
	पूर्ण

	/* RCT with a non-stuck bit */
	jent_rct_insert(ec, 0);

	वापस 0;
पूर्ण

/**
 * Report any health test failures
 *
 * @ec [in] Reference to entropy collector
 *
 * @वापस
 * 	0 No health test failure
 * 	1 Permanent health test failure
 */
अटल पूर्णांक jent_health_failure(काष्ठा अक्रम_data *ec)
अणु
	/* Test is only enabled in FIPS mode */
	अगर (!jent_fips_enabled())
		वापस 0;

	वापस ec->health_failure;
पूर्ण

/***************************************************************************
 * Noise sources
 ***************************************************************************/

/**
 * Update of the loop count used क्रम the next round of
 * an entropy collection.
 *
 * Input:
 * @ec entropy collector काष्ठा -- may be शून्य
 * @bits is the number of low bits of the समयr to consider
 * @min is the number of bits we shअगरt the समयr value to the right at
 *	the end to make sure we have a guaranteed minimum value
 *
 * @वापस Newly calculated loop counter
 */
अटल __u64 jent_loop_shuffle(काष्ठा अक्रम_data *ec,
			       अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक min)
अणु
	__u64 समय = 0;
	__u64 shuffle = 0;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक mask = (1<<bits) - 1;

	jent_get_nsसमय(&समय);
	/*
	 * Mix the current state of the अक्रमom number पूर्णांकo the shuffle
	 * calculation to balance that shuffle a bit more.
	 */
	अगर (ec)
		समय ^= ec->data;
	/*
	 * We fold the समय value as much as possible to ensure that as many
	 * bits of the समय stamp are included as possible.
	 */
	क्रम (i = 0; ((DATA_SIZE_BITS + bits - 1) / bits) > i; i++) अणु
		shuffle ^= समय & mask;
		समय = समय >> bits;
	पूर्ण

	/*
	 * We add a lower boundary value to ensure we have a minimum
	 * RNG loop count.
	 */
	वापस (shuffle + (1<<min));
पूर्ण

/**
 * CPU Jitter noise source -- this is the noise source based on the CPU
 *			      execution समय jitter
 *
 * This function injects the inभागidual bits of the समय value पूर्णांकo the
 * entropy pool using an LFSR.
 *
 * The code is deliberately inefficient with respect to the bit shअगरting
 * and shall stay that way. This function is the root cause why the code
 * shall be compiled without optimization. This function not only acts as
 * folding operation, but this function's execution is used to measure
 * the CPU execution समय jitter. Any change to the loop in this function
 * implies that careful retesting must be करोne.
 *
 * @ec [in] entropy collector काष्ठा
 * @समय [in] समय stamp to be injected
 * @loop_cnt [in] अगर a value not equal to 0 is set, use the given value as
 *		  number of loops to perक्रमm the folding
 * @stuck [in] Is the समय stamp identअगरied as stuck?
 *
 * Output:
 * updated ec->data
 *
 * @वापस Number of loops the folding operation is perक्रमmed
 */
अटल व्योम jent_lfsr_समय(काष्ठा अक्रम_data *ec, __u64 समय, __u64 loop_cnt,
			   पूर्णांक stuck)
अणु
	अचिन्हित पूर्णांक i;
	__u64 j = 0;
	__u64 new = 0;
#घोषणा MAX_FOLD_LOOP_BIT 4
#घोषणा MIN_FOLD_LOOP_BIT 0
	__u64 fold_loop_cnt =
		jent_loop_shuffle(ec, MAX_FOLD_LOOP_BIT, MIN_FOLD_LOOP_BIT);

	/*
	 * testing purposes -- allow test app to set the counter, not
	 * needed during runसमय
	 */
	अगर (loop_cnt)
		fold_loop_cnt = loop_cnt;
	क्रम (j = 0; j < fold_loop_cnt; j++) अणु
		new = ec->data;
		क्रम (i = 1; (DATA_SIZE_BITS) >= i; i++) अणु
			__u64 पंचांगp = समय << (DATA_SIZE_BITS - i);

			पंचांगp = पंचांगp >> (DATA_SIZE_BITS - 1);

			/*
			* Fibonacci LSFR with polynomial of
			*  x^64 + x^61 + x^56 + x^31 + x^28 + x^23 + 1 which is
			*  primitive according to
			*   http://poincare.matf.bg.ac.rs/~ezivkovm/खुलाations/primpol1.pdf
			* (the shअगरt values are the polynomial values minus one
			* due to counting bits from 0 to 63). As the current
			* position is always the LSB, the polynomial only needs
			* to shअगरt data in from the left without wrap.
			*/
			पंचांगp ^= ((new >> 63) & 1);
			पंचांगp ^= ((new >> 60) & 1);
			पंचांगp ^= ((new >> 55) & 1);
			पंचांगp ^= ((new >> 30) & 1);
			पंचांगp ^= ((new >> 27) & 1);
			पंचांगp ^= ((new >> 22) & 1);
			new <<= 1;
			new ^= पंचांगp;
		पूर्ण
	पूर्ण

	/*
	 * If the समय stamp is stuck, करो not finally insert the value पूर्णांकo
	 * the entropy pool. Although this operation should not करो any harm
	 * even when the समय stamp has no entropy, SP800-90B requires that
	 * any conditioning operation (SP800-90B considers the LFSR to be a
	 * conditioning operation) to have an identical amount of input
	 * data according to section 3.1.5.
	 */
	अगर (!stuck)
		ec->data = new;
पूर्ण

/**
 * Memory Access noise source -- this is a noise source based on variations in
 *				 memory access बार
 *
 * This function perक्रमms memory accesses which will add to the timing
 * variations due to an unknown amount of CPU रुको states that need to be
 * added when accessing memory. The memory size should be larger than the L1
 * caches as outlined in the करोcumentation and the associated testing.
 *
 * The L1 cache has a very high bandwidth, albeit its access rate is  usually
 * slower than accessing CPU रेजिस्टरs. Thereक्रमe, L1 accesses only add minimal
 * variations as the CPU has hardly to रुको. Starting with L2, signअगरicant
 * variations are added because L2 typically करोes not beदीर्घ to the CPU any more
 * and thereक्रमe a wider range of CPU रुको states is necessary क्रम accesses.
 * L3 and real memory accesses have even a wider range of रुको states. However,
 * to reliably access either L3 or memory, the ec->mem memory must be quite
 * large which is usually not desirable.
 *
 * @ec [in] Reference to the entropy collector with the memory access data -- अगर
 *	    the reference to the memory block to be accessed is शून्य, this noise
 *	    source is disabled
 * @loop_cnt [in] अगर a value not equal to 0 is set, use the given value
 *		  number of loops to perक्रमm the LFSR
 */
अटल व्योम jent_memaccess(काष्ठा अक्रम_data *ec, __u64 loop_cnt)
अणु
	अचिन्हित पूर्णांक wrap = 0;
	__u64 i = 0;
#घोषणा MAX_ACC_LOOP_BIT 7
#घोषणा MIN_ACC_LOOP_BIT 0
	__u64 acc_loop_cnt =
		jent_loop_shuffle(ec, MAX_ACC_LOOP_BIT, MIN_ACC_LOOP_BIT);

	अगर (शून्य == ec || शून्य == ec->mem)
		वापस;
	wrap = ec->memblocksize * ec->memblocks;

	/*
	 * testing purposes -- allow test app to set the counter, not
	 * needed during runसमय
	 */
	अगर (loop_cnt)
		acc_loop_cnt = loop_cnt;

	क्रम (i = 0; i < (ec->memaccessloops + acc_loop_cnt); i++) अणु
		अचिन्हित अक्षर *पंचांगpval = ec->mem + ec->memlocation;
		/*
		 * memory access: just add 1 to one byte,
		 * wrap at 255 -- memory access implies पढ़ो
		 * from and ग_लिखो to memory location
		 */
		*पंचांगpval = (*पंचांगpval + 1) & 0xff;
		/*
		 * Addition of memblocksize - 1 to poपूर्णांकer
		 * with wrap around logic to ensure that every
		 * memory location is hit evenly
		 */
		ec->memlocation = ec->memlocation + ec->memblocksize - 1;
		ec->memlocation = ec->memlocation % wrap;
	पूर्ण
पूर्ण

/***************************************************************************
 * Start of entropy processing logic
 ***************************************************************************/
/**
 * This is the heart of the entropy generation: calculate समय deltas and
 * use the CPU jitter in the समय deltas. The jitter is injected पूर्णांकo the
 * entropy pool.
 *
 * WARNING: ensure that ->prev_समय is primed beक्रमe using the output
 *	    of this function! This can be करोne by calling this function
 *	    and not using its result.
 *
 * @ec [in] Reference to entropy collector
 *
 * @वापस result of stuck test
 */
अटल पूर्णांक jent_measure_jitter(काष्ठा अक्रम_data *ec)
अणु
	__u64 समय = 0;
	__u64 current_delta = 0;
	पूर्णांक stuck;

	/* Invoke one noise source beक्रमe समय measurement to add variations */
	jent_memaccess(ec, 0);

	/*
	 * Get समय stamp and calculate समय delta to previous
	 * invocation to measure the timing variations
	 */
	jent_get_nsसमय(&समय);
	current_delta = jent_delta(ec->prev_समय, समय);
	ec->prev_समय = समय;

	/* Check whether we have a stuck measurement. */
	stuck = jent_stuck(ec, current_delta);

	/* Now call the next noise sources which also injects the data */
	jent_lfsr_समय(ec, current_delta, 0, stuck);

	वापस stuck;
पूर्ण

/**
 * Generator of one 64 bit अक्रमom number
 * Function fills अक्रम_data->data
 *
 * @ec [in] Reference to entropy collector
 */
अटल व्योम jent_gen_entropy(काष्ठा अक्रम_data *ec)
अणु
	अचिन्हित पूर्णांक k = 0;

	/* priming of the ->prev_समय value */
	jent_measure_jitter(ec);

	जबतक (1) अणु
		/* If a stuck measurement is received, repeat measurement */
		अगर (jent_measure_jitter(ec))
			जारी;

		/*
		 * We multiply the loop value with ->osr to obtain the
		 * oversampling rate requested by the caller
		 */
		अगर (++k >= (DATA_SIZE_BITS * ec->osr))
			अवरोध;
	पूर्ण
पूर्ण

/**
 * Entry function: Obtain entropy क्रम the caller.
 *
 * This function invokes the entropy gathering logic as often to generate
 * as many bytes as requested by the caller. The entropy gathering logic
 * creates 64 bit per invocation.
 *
 * This function truncates the last 64 bit entropy value output to the exact
 * size specअगरied by the caller.
 *
 * @ec [in] Reference to entropy collector
 * @data [in] poपूर्णांकer to buffer क्रम storing अक्रमom data -- buffer must alपढ़ोy
 *	      exist
 * @len [in] size of the buffer, specअगरying also the requested number of अक्रमom
 *	     in bytes
 *
 * @वापस 0 when request is fulfilled or an error
 *
 * The following error codes can occur:
 *	-1	entropy_collector is शून्य
 *	-2	RCT failed
 *	-3	APT test failed
 */
पूर्णांक jent_पढ़ो_entropy(काष्ठा अक्रम_data *ec, अचिन्हित अक्षर *data,
		      अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *p = data;

	अगर (!ec)
		वापस -1;

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक tocopy;

		jent_gen_entropy(ec);

		अगर (jent_health_failure(ec)) अणु
			पूर्णांक ret;

			अगर (jent_rct_failure(ec))
				ret = -2;
			अन्यथा
				ret = -3;

			/*
			 * Re-initialize the noise source
			 *
			 * If the health test fails, the Jitter RNG reमुख्यs
			 * in failure state and will वापस a health failure
			 * during next invocation.
			 */
			अगर (jent_entropy_init())
				वापस ret;

			/* Set APT to initial state */
			jent_apt_reset(ec, 0);
			ec->apt_base_set = 0;

			/* Set RCT to initial state */
			ec->rct_count = 0;

			/* Re-enable Jitter RNG */
			ec->health_failure = 0;

			/*
			 * Return the health test failure status to the
			 * caller as the generated value is not appropriate.
			 */
			वापस ret;
		पूर्ण

		अगर ((DATA_SIZE_BITS / 8) < len)
			tocopy = (DATA_SIZE_BITS / 8);
		अन्यथा
			tocopy = len;
		jent_स_नकल(p, &ec->data, tocopy);

		len -= tocopy;
		p += tocopy;
	पूर्ण

	वापस 0;
पूर्ण

/***************************************************************************
 * Initialization logic
 ***************************************************************************/

काष्ठा अक्रम_data *jent_entropy_collector_alloc(अचिन्हित पूर्णांक osr,
					       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा अक्रम_data *entropy_collector;

	entropy_collector = jent_zalloc(माप(काष्ठा अक्रम_data));
	अगर (!entropy_collector)
		वापस शून्य;

	अगर (!(flags & JENT_DISABLE_MEMORY_ACCESS)) अणु
		/* Allocate memory क्रम adding variations based on memory
		 * access
		 */
		entropy_collector->mem = jent_zalloc(JENT_MEMORY_SIZE);
		अगर (!entropy_collector->mem) अणु
			jent_zमुक्त(entropy_collector);
			वापस शून्य;
		पूर्ण
		entropy_collector->memblocksize = JENT_MEMORY_BLOCKSIZE;
		entropy_collector->memblocks = JENT_MEMORY_BLOCKS;
		entropy_collector->memaccessloops = JENT_MEMORY_ACCESSLOOPS;
	पूर्ण

	/* verअगरy and set the oversampling rate */
	अगर (osr == 0)
		osr = 1; /* minimum sampling rate is 1 */
	entropy_collector->osr = osr;

	/* fill the data pad with non-zero values */
	jent_gen_entropy(entropy_collector);

	वापस entropy_collector;
पूर्ण

व्योम jent_entropy_collector_मुक्त(काष्ठा अक्रम_data *entropy_collector)
अणु
	jent_zमुक्त(entropy_collector->mem);
	entropy_collector->mem = शून्य;
	jent_zमुक्त(entropy_collector);
पूर्ण

पूर्णांक jent_entropy_init(व्योम)
अणु
	पूर्णांक i;
	__u64 delta_sum = 0;
	__u64 old_delta = 0;
	अचिन्हित पूर्णांक nonstuck = 0;
	पूर्णांक समय_backwards = 0;
	पूर्णांक count_mod = 0;
	पूर्णांक count_stuck = 0;
	काष्ठा अक्रम_data ec = अणु 0 पूर्ण;

	/* Required क्रम RCT */
	ec.osr = 1;

	/* We could perक्रमm statistical tests here, but the problem is
	 * that we only have a few loop counts to करो testing. These
	 * loop counts may show some slight skew and we produce
	 * false positives.
	 *
	 * Moreover, only old प्रणालीs show potentially problematic
	 * jitter entropy that could potentially be caught here. But
	 * the RNG is पूर्णांकended क्रम hardware that is available or widely
	 * used, but not old प्रणालीs that are दीर्घ out of favor. Thus,
	 * no statistical tests.
	 */

	/*
	 * We could add a check क्रम प्रणाली capabilities such as घड़ी_getres or
	 * check क्रम CONFIG_X86_TSC, but it करोes not make much sense as the
	 * following sanity checks verअगरy that we have a high-resolution
	 * समयr.
	 */
	/*
	 * TESTLOOPCOUNT needs some loops to identअगरy edge प्रणालीs. 100 is
	 * definitely too little.
	 *
	 * SP800-90B requires at least 1024 initial test cycles.
	 */
#घोषणा TESTLOOPCOUNT 1024
#घोषणा CLEARCACHE 100
	क्रम (i = 0; (TESTLOOPCOUNT + CLEARCACHE) > i; i++) अणु
		__u64 समय = 0;
		__u64 समय2 = 0;
		__u64 delta = 0;
		अचिन्हित पूर्णांक lowdelta = 0;
		पूर्णांक stuck;

		/* Invoke core entropy collection logic */
		jent_get_nsसमय(&समय);
		ec.prev_समय = समय;
		jent_lfsr_समय(&ec, समय, 0, 0);
		jent_get_nsसमय(&समय2);

		/* test whether समयr works */
		अगर (!समय || !समय2)
			वापस JENT_ENOTIME;
		delta = jent_delta(समय, समय2);
		/*
		 * test whether समयr is fine grained enough to provide
		 * delta even when called लघुly after each other -- this
		 * implies that we also have a high resolution समयr
		 */
		अगर (!delta)
			वापस JENT_ECOARSETIME;

		stuck = jent_stuck(&ec, delta);

		/*
		 * up to here we did not modअगरy any variable that will be
		 * evaluated later, but we alपढ़ोy perक्रमmed some work. Thus we
		 * alपढ़ोy have had an impact on the caches, branch prediction,
		 * etc. with the goal to clear it to get the worst हाल
		 * measurements.
		 */
		अगर (i < CLEARCACHE)
			जारी;

		अगर (stuck)
			count_stuck++;
		अन्यथा अणु
			nonstuck++;

			/*
			 * Ensure that the APT succeeded.
			 *
			 * With the check below that count_stuck must be less
			 * than 10% of the overall generated raw entropy values
			 * it is guaranteed that the APT is invoked at
			 * न्यूनमान((TESTLOOPCOUNT * 0.9) / 64) == 14 बार.
			 */
			अगर ((nonstuck % JENT_APT_WINDOW_SIZE) == 0) अणु
				jent_apt_reset(&ec,
					       delta & JENT_APT_WORD_MASK);
				अगर (jent_health_failure(&ec))
					वापस JENT_EHEALTH;
			पूर्ण
		पूर्ण

		/* Validate RCT */
		अगर (jent_rct_failure(&ec))
			वापस JENT_ERCT;

		/* test whether we have an increasing समयr */
		अगर (!(समय2 > समय))
			समय_backwards++;

		/* use 32 bit value to ensure compilation on 32 bit arches */
		lowdelta = समय2 - समय;
		अगर (!(lowdelta % 100))
			count_mod++;

		/*
		 * ensure that we have a varying delta समयr which is necessary
		 * क्रम the calculation of entropy -- perक्रमm this check
		 * only after the first loop is executed as we need to prime
		 * the old_data value
		 */
		अगर (delta > old_delta)
			delta_sum += (delta - old_delta);
		अन्यथा
			delta_sum += (old_delta - delta);
		old_delta = delta;
	पूर्ण

	/*
	 * we allow up to three बार the समय running backwards.
	 * CLOCK_REALTIME is affected by adjसमय and NTP operations. Thus,
	 * अगर such an operation just happens to पूर्णांकerfere with our test, it
	 * should not fail. The value of 3 should cover the NTP हाल being
	 * perक्रमmed during our test run.
	 */
	अगर (समय_backwards > 3)
		वापस JENT_ENOMONOTONIC;

	/*
	 * Variations of deltas of समय must on average be larger
	 * than 1 to ensure the entropy estimation
	 * implied with 1 is preserved
	 */
	अगर ((delta_sum) <= 1)
		वापस JENT_EVARVAR;

	/*
	 * Ensure that we have variations in the समय stamp below 10 क्रम at
	 * least 10% of all checks -- on some platक्रमms, the counter increments
	 * in multiples of 100, but not always
	 */
	अगर ((TESTLOOPCOUNT/10 * 9) < count_mod)
		वापस JENT_ECOARSETIME;

	/*
	 * If we have more than 90% stuck results, then this Jitter RNG is
	 * likely to not work well.
	 */
	अगर ((TESTLOOPCOUNT/10 * 9) < count_stuck)
		वापस JENT_ESTUCK;

	वापस 0;
पूर्ण
