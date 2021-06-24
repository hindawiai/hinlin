<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kernel/sched/loadavg.c
 *
 * This file contains the magic bits required to compute the global loadavg
 * figure. Its a silly number but people think its important. We go through
 * great pains to make it work on big machines and tickless kernels.
 */
#समावेश "sched.h"

/*
 * Global load-average calculations
 *
 * We take a distributed and async approach to calculating the global load-avg
 * in order to minimize overhead.
 *
 * The global load average is an exponentially decaying average of nr_running +
 * nr_unपूर्णांकerruptible.
 *
 * Once every LOAD_FREQ:
 *
 *   nr_active = 0;
 *   क्रम_each_possible_cpu(cpu)
 *	nr_active += cpu_of(cpu)->nr_running + cpu_of(cpu)->nr_unपूर्णांकerruptible;
 *
 *   avenrun[n] = avenrun[0] * exp_n + nr_active * (1 - exp_n)
 *
 * Due to a number of reasons the above turns in the mess below:
 *
 *  - क्रम_each_possible_cpu() is prohibitively expensive on machines with
 *    serious number of CPUs, thereक्रमe we need to take a distributed approach
 *    to calculating nr_active.
 *
 *        \Sum_i x_i(t) = \Sum_i x_i(t) - x_i(t_0) | x_i(t_0) := 0
 *                      = \Sum_i अणु \Sum_j=1 x_i(t_j) - x_i(t_j-1) पूर्ण
 *
 *    So assuming nr_active := 0 when we start out -- true per definition, we
 *    can simply take per-CPU deltas and fold those पूर्णांकo a global accumulate
 *    to obtain the same result. See calc_load_fold_active().
 *
 *    Furthermore, in order to aव्योम synchronizing all per-CPU delta folding
 *    across the machine, we assume 10 ticks is sufficient समय क्रम every
 *    CPU to have completed this task.
 *
 *    This places an upper-bound on the IRQ-off latency of the machine. Then
 *    again, being late करोesn't loose the delta, just wrecks the sample.
 *
 *  - cpu_rq()->nr_unपूर्णांकerruptible isn't accurately tracked per-CPU because
 *    this would add another cross-CPU cacheline miss and atomic operation
 *    to the wakeup path. Instead we increment on whatever CPU the task ran
 *    when it went पूर्णांकo unपूर्णांकerruptible state and decrement on whatever CPU
 *    did the wakeup. This means that only the sum of nr_unपूर्णांकerruptible over
 *    all CPUs yields the correct result.
 *
 *  This covers the NO_HZ=n code, क्रम extra head-aches, see the comment below.
 */

/* Variables and functions क्रम calc_load */
atomic_दीर्घ_t calc_load_tasks;
अचिन्हित दीर्घ calc_load_update;
अचिन्हित दीर्घ avenrun[3];
EXPORT_SYMBOL(avenrun); /* should be हटाओd */

/**
 * get_avenrun - get the load average array
 * @loads:	poपूर्णांकer to dest load array
 * @offset:	offset to add
 * @shअगरt:	shअगरt count to shअगरt the result left
 *
 * These values are estimates at best, so no need क्रम locking.
 */
व्योम get_avenrun(अचिन्हित दीर्घ *loads, अचिन्हित दीर्घ offset, पूर्णांक shअगरt)
अणु
	loads[0] = (avenrun[0] + offset) << shअगरt;
	loads[1] = (avenrun[1] + offset) << shअगरt;
	loads[2] = (avenrun[2] + offset) << shअगरt;
पूर्ण

दीर्घ calc_load_fold_active(काष्ठा rq *this_rq, दीर्घ adjust)
अणु
	दीर्घ nr_active, delta = 0;

	nr_active = this_rq->nr_running - adjust;
	nr_active += (दीर्घ)this_rq->nr_unपूर्णांकerruptible;

	अगर (nr_active != this_rq->calc_load_active) अणु
		delta = nr_active - this_rq->calc_load_active;
		this_rq->calc_load_active = nr_active;
	पूर्ण

	वापस delta;
पूर्ण

/**
 * fixed_घातer_पूर्णांक - compute: x^n, in O(log n) समय
 *
 * @x:         base of the घातer
 * @frac_bits: fractional bits of @x
 * @n:         घातer to उठाओ @x to.
 *
 * By exploiting the relation between the definition of the natural घातer
 * function: x^n := x*x*...*x (x multiplied by itself क्रम n बार), and
 * the binary encoding of numbers used by computers: n := \Sum n_i * 2^i,
 * (where: n_i \elem अणु0, 1पूर्ण, the binary vector representing n),
 * we find: x^n := x^(\Sum n_i * 2^i) := \Prod x^(n_i * 2^i), which is
 * of course trivially computable in O(log_2 n), the length of our binary
 * vector.
 */
अटल अचिन्हित दीर्घ
fixed_घातer_पूर्णांक(अचिन्हित दीर्घ x, अचिन्हित पूर्णांक frac_bits, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ result = 1UL << frac_bits;

	अगर (n) अणु
		क्रम (;;) अणु
			अगर (n & 1) अणु
				result *= x;
				result += 1UL << (frac_bits - 1);
				result >>= frac_bits;
			पूर्ण
			n >>= 1;
			अगर (!n)
				अवरोध;
			x *= x;
			x += 1UL << (frac_bits - 1);
			x >>= frac_bits;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

/*
 * a1 = a0 * e + a * (1 - e)
 *
 * a2 = a1 * e + a * (1 - e)
 *    = (a0 * e + a * (1 - e)) * e + a * (1 - e)
 *    = a0 * e^2 + a * (1 - e) * (1 + e)
 *
 * a3 = a2 * e + a * (1 - e)
 *    = (a0 * e^2 + a * (1 - e) * (1 + e)) * e + a * (1 - e)
 *    = a0 * e^3 + a * (1 - e) * (1 + e + e^2)
 *
 *  ...
 *
 * an = a0 * e^n + a * (1 - e) * (1 + e + ... + e^n-1) [1]
 *    = a0 * e^n + a * (1 - e) * (1 - e^n)/(1 - e)
 *    = a0 * e^n + a * (1 - e^n)
 *
 * [1] application of the geometric series:
 *
 *              n         1 - x^(n+1)
 *     S_n := \Sum x^i = -------------
 *             i=0          1 - x
 */
अचिन्हित दीर्घ
calc_load_n(अचिन्हित दीर्घ load, अचिन्हित दीर्घ exp,
	    अचिन्हित दीर्घ active, अचिन्हित पूर्णांक n)
अणु
	वापस calc_load(load, fixed_घातer_पूर्णांक(exp, FSHIFT, n), active);
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_COMMON
/*
 * Handle NO_HZ क्रम the global load-average.
 *
 * Since the above described distributed algorithm to compute the global
 * load-average relies on per-CPU sampling from the tick, it is affected by
 * NO_HZ.
 *
 * The basic idea is to fold the nr_active delta पूर्णांकo a global NO_HZ-delta upon
 * entering NO_HZ state such that we can include this as an 'extra' CPU delta
 * when we पढ़ो the global state.
 *
 * Obviously reality has to ruin such a delightfully simple scheme:
 *
 *  - When we go NO_HZ idle during the winकरोw, we can negate our sample
 *    contribution, causing under-accounting.
 *
 *    We aव्योम this by keeping two NO_HZ-delta counters and flipping them
 *    when the winकरोw starts, thus separating old and new NO_HZ load.
 *
 *    The only trick is the slight shअगरt in index flip क्रम पढ़ो vs ग_लिखो.
 *
 *        0s            5s            10s           15s
 *          +10           +10           +10           +10
 *        |-|-----------|-|-----------|-|-----------|-|
 *    r:0 0 1           1 0           0 1           1 0
 *    w:0 1 1           0 0           1 1           0 0
 *
 *    This ensures we'll fold the old NO_HZ contribution in this winकरोw जबतक
 *    accumulating the new one.
 *
 *  - When we wake up from NO_HZ during the winकरोw, we push up our
 *    contribution, since we effectively move our sample poपूर्णांक to a known
 *    busy state.
 *
 *    This is solved by pushing the winकरोw क्रमward, and thus skipping the
 *    sample, क्रम this CPU (effectively using the NO_HZ-delta क्रम this CPU which
 *    was in effect at the समय the winकरोw खोलोed). This also solves the issue
 *    of having to deal with a CPU having been in NO_HZ क्रम multiple LOAD_FREQ
 *    पूर्णांकervals.
 *
 * When making the ILB scale, we should try to pull this in as well.
 */
अटल atomic_दीर्घ_t calc_load_nohz[2];
अटल पूर्णांक calc_load_idx;

अटल अंतरभूत पूर्णांक calc_load_ग_लिखो_idx(व्योम)
अणु
	पूर्णांक idx = calc_load_idx;

	/*
	 * See calc_global_nohz(), अगर we observe the new index, we also
	 * need to observe the new update समय.
	 */
	smp_rmb();

	/*
	 * If the folding winकरोw started, make sure we start writing in the
	 * next NO_HZ-delta.
	 */
	अगर (!समय_beक्रमe(jअगरfies, READ_ONCE(calc_load_update)))
		idx++;

	वापस idx & 1;
पूर्ण

अटल अंतरभूत पूर्णांक calc_load_पढ़ो_idx(व्योम)
अणु
	वापस calc_load_idx & 1;
पूर्ण

अटल व्योम calc_load_nohz_fold(काष्ठा rq *rq)
अणु
	दीर्घ delta;

	delta = calc_load_fold_active(rq, 0);
	अगर (delta) अणु
		पूर्णांक idx = calc_load_ग_लिखो_idx();

		atomic_दीर्घ_add(delta, &calc_load_nohz[idx]);
	पूर्ण
पूर्ण

व्योम calc_load_nohz_start(व्योम)
अणु
	/*
	 * We're going into NO_HZ mode, if there's any pending delta, fold it
	 * पूर्णांकo the pending NO_HZ delta.
	 */
	calc_load_nohz_fold(this_rq());
पूर्ण

/*
 * Keep track of the load क्रम NOHZ_FULL, must be called between
 * calc_load_nohz_अणुstart,stopपूर्ण().
 */
व्योम calc_load_nohz_remote(काष्ठा rq *rq)
अणु
	calc_load_nohz_fold(rq);
पूर्ण

व्योम calc_load_nohz_stop(व्योम)
अणु
	काष्ठा rq *this_rq = this_rq();

	/*
	 * If we're still before the pending sample window, we're करोne.
	 */
	this_rq->calc_load_update = READ_ONCE(calc_load_update);
	अगर (समय_beक्रमe(jअगरfies, this_rq->calc_load_update))
		वापस;

	/*
	 * We woke inside or after the sample winकरोw, this means we're alपढ़ोy
	 * accounted through the nohz accounting, so skip the entire deal and
	 * sync up क्रम the next winकरोw.
	 */
	अगर (समय_beक्रमe(jअगरfies, this_rq->calc_load_update + 10))
		this_rq->calc_load_update += LOAD_FREQ;
पूर्ण

अटल दीर्घ calc_load_nohz_पढ़ो(व्योम)
अणु
	पूर्णांक idx = calc_load_पढ़ो_idx();
	दीर्घ delta = 0;

	अगर (atomic_दीर्घ_पढ़ो(&calc_load_nohz[idx]))
		delta = atomic_दीर्घ_xchg(&calc_load_nohz[idx], 0);

	वापस delta;
पूर्ण

/*
 * NO_HZ can leave us missing all per-CPU ticks calling
 * calc_load_fold_active(), but since a NO_HZ CPU folds its delta पूर्णांकo
 * calc_load_nohz per calc_load_nohz_start(), all we need to करो is fold
 * in the pending NO_HZ delta अगर our NO_HZ period crossed a load cycle boundary.
 *
 * Once we've updated the global active value, we need to apply the exponential
 * weights adjusted to the number of cycles missed.
 */
अटल व्योम calc_global_nohz(व्योम)
अणु
	अचिन्हित दीर्घ sample_winकरोw;
	दीर्घ delta, active, n;

	sample_winकरोw = READ_ONCE(calc_load_update);
	अगर (!समय_beक्रमe(jअगरfies, sample_winकरोw + 10)) अणु
		/*
		 * Catch-up, fold however many we are behind still
		 */
		delta = jअगरfies - sample_winकरोw - 10;
		n = 1 + (delta / LOAD_FREQ);

		active = atomic_दीर्घ_पढ़ो(&calc_load_tasks);
		active = active > 0 ? active * FIXED_1 : 0;

		avenrun[0] = calc_load_n(avenrun[0], EXP_1, active, n);
		avenrun[1] = calc_load_n(avenrun[1], EXP_5, active, n);
		avenrun[2] = calc_load_n(avenrun[2], EXP_15, active, n);

		WRITE_ONCE(calc_load_update, sample_winकरोw + n * LOAD_FREQ);
	पूर्ण

	/*
	 * Flip the NO_HZ index...
	 *
	 * Make sure we first ग_लिखो the new समय then flip the index, so that
	 * calc_load_ग_लिखो_idx() will see the new समय when it पढ़ोs the new
	 * index, this aव्योमs a द्विगुन flip messing things up.
	 */
	smp_wmb();
	calc_load_idx++;
पूर्ण
#अन्यथा /* !CONFIG_NO_HZ_COMMON */

अटल अंतरभूत दीर्घ calc_load_nohz_पढ़ो(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम calc_global_nohz(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

/*
 * calc_load - update the avenrun load estimates 10 ticks after the
 * CPUs have updated calc_load_tasks.
 *
 * Called from the global समयr code.
 */
व्योम calc_global_load(व्योम)
अणु
	अचिन्हित दीर्घ sample_winकरोw;
	दीर्घ active, delta;

	sample_winकरोw = READ_ONCE(calc_load_update);
	अगर (समय_beक्रमe(jअगरfies, sample_winकरोw + 10))
		वापस;

	/*
	 * Fold the 'old' NO_HZ-delta to include all NO_HZ CPUs.
	 */
	delta = calc_load_nohz_पढ़ो();
	अगर (delta)
		atomic_दीर्घ_add(delta, &calc_load_tasks);

	active = atomic_दीर्घ_पढ़ो(&calc_load_tasks);
	active = active > 0 ? active * FIXED_1 : 0;

	avenrun[0] = calc_load(avenrun[0], EXP_1, active);
	avenrun[1] = calc_load(avenrun[1], EXP_5, active);
	avenrun[2] = calc_load(avenrun[2], EXP_15, active);

	WRITE_ONCE(calc_load_update, sample_winकरोw + LOAD_FREQ);

	/*
	 * In हाल we went to NO_HZ क्रम multiple LOAD_FREQ पूर्णांकervals
	 * catch up in bulk.
	 */
	calc_global_nohz();
पूर्ण

/*
 * Called from scheduler_tick() to periodically update this CPU's
 * active count.
 */
व्योम calc_global_load_tick(काष्ठा rq *this_rq)
अणु
	दीर्घ delta;

	अगर (समय_beक्रमe(jअगरfies, this_rq->calc_load_update))
		वापस;

	delta  = calc_load_fold_active(this_rq, 0);
	अगर (delta)
		atomic_दीर्घ_add(delta, &calc_load_tasks);

	this_rq->calc_load_update += LOAD_FREQ;
पूर्ण
