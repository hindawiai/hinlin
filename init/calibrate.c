<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* calibrate.c: शेष delay calibration
 *
 * Excised from init/मुख्य.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/समयx.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>

अचिन्हित दीर्घ lpj_fine;
अचिन्हित दीर्घ preset_lpj;
अटल पूर्णांक __init lpj_setup(अक्षर *str)
अणु
	preset_lpj = simple_म_से_अदीर्घ(str,शून्य,0);
	वापस 1;
पूर्ण

__setup("lpj=", lpj_setup);

#अगर_घोषित ARCH_HAS_READ_CURRENT_TIMER

/* This routine uses the पढ़ो_current_समयr() routine and माला_लो the
 * loops per jअगरfy directly, instead of guessing it using delay().
 * Also, this code tries to handle non-maskable asynchronous events
 * (like SMIs)
 */
#घोषणा DELAY_CALIBRATION_TICKS			((HZ < 100) ? 1 : (HZ/100))
#घोषणा MAX_सूचीECT_CALIBRATION_RETRIES		5

अटल अचिन्हित दीर्घ calibrate_delay_direct(व्योम)
अणु
	अचिन्हित दीर्घ pre_start, start, post_start;
	अचिन्हित दीर्घ pre_end, end, post_end;
	अचिन्हित दीर्घ start_jअगरfies;
	अचिन्हित दीर्घ समयr_rate_min, समयr_rate_max;
	अचिन्हित दीर्घ good_समयr_sum = 0;
	अचिन्हित दीर्घ good_समयr_count = 0;
	अचिन्हित दीर्घ measured_बार[MAX_सूचीECT_CALIBRATION_RETRIES];
	पूर्णांक max = -1; /* index of measured_बार with max/min values or not set */
	पूर्णांक min = -1;
	पूर्णांक i;

	अगर (पढ़ो_current_समयr(&pre_start) < 0 )
		वापस 0;

	/*
	 * A simple loop like
	 *	जबतक ( jअगरfies < start_jअगरfies+1)
	 *		start = पढ़ो_current_समयr();
	 * will not करो. As we करोn't really know whether jअगरfy चयन
	 * happened first or समयr_value was पढ़ो first. And some asynchronous
	 * event can happen between these two events पूर्णांकroducing errors in lpj.
	 *
	 * So, we करो
	 * 1. pre_start <- When we are sure that jअगरfy चयन hasn't happened
	 * 2. check jअगरfy चयन
	 * 3. start <- समयr value beक्रमe or after jअगरfy चयन
	 * 4. post_start <- When we are sure that jअगरfy चयन has happened
	 *
	 * Note, we करोn't know anything about order of 2 and 3.
	 * Now, by looking at post_start and pre_start dअगरference, we can
	 * check whether any asynchronous event happened or not
	 */

	क्रम (i = 0; i < MAX_सूचीECT_CALIBRATION_RETRIES; i++) अणु
		pre_start = 0;
		पढ़ो_current_समयr(&start);
		start_jअगरfies = jअगरfies;
		जबतक (समय_beक्रमe_eq(jअगरfies, start_jअगरfies + 1)) अणु
			pre_start = start;
			पढ़ो_current_समयr(&start);
		पूर्ण
		पढ़ो_current_समयr(&post_start);

		pre_end = 0;
		end = post_start;
		जबतक (समय_beक्रमe_eq(jअगरfies, start_jअगरfies + 1 +
					       DELAY_CALIBRATION_TICKS)) अणु
			pre_end = end;
			पढ़ो_current_समयr(&end);
		पूर्ण
		पढ़ो_current_समयr(&post_end);

		समयr_rate_max = (post_end - pre_start) /
					DELAY_CALIBRATION_TICKS;
		समयr_rate_min = (pre_end - post_start) /
					DELAY_CALIBRATION_TICKS;

		/*
		 * If the upper limit and lower limit of the समयr_rate is
		 * >= 12.5% apart, reकरो calibration.
		 */
		अगर (start >= post_end)
			prपूर्णांकk(KERN_NOTICE "calibrate_delay_direct() ignoring "
					"timer_rate as we had a TSC wrap around"
					" start=%lu >=post_end=%lu\n",
				start, post_end);
		अगर (start < post_end && pre_start != 0 && pre_end != 0 &&
		    (समयr_rate_max - समयr_rate_min) < (समयr_rate_max >> 3)) अणु
			good_समयr_count++;
			good_समयr_sum += समयr_rate_max;
			measured_बार[i] = समयr_rate_max;
			अगर (max < 0 || समयr_rate_max > measured_बार[max])
				max = i;
			अगर (min < 0 || समयr_rate_max < measured_बार[min])
				min = i;
		पूर्ण अन्यथा
			measured_बार[i] = 0;

	पूर्ण

	/*
	 * Find the maximum & minimum - अगर they dअगरfer too much throw out the
	 * one with the largest dअगरference from the mean and try again...
	 */
	जबतक (good_समयr_count > 1) अणु
		अचिन्हित दीर्घ estimate;
		अचिन्हित दीर्घ maxdअगरf;

		/* compute the estimate */
		estimate = (good_समयr_sum/good_समयr_count);
		maxdअगरf = estimate >> 3;

		/* अगर range is within 12% let's take it */
		अगर ((measured_बार[max] - measured_बार[min]) < maxdअगरf)
			वापस estimate;

		/* ok - drop the worse value and try again... */
		good_समयr_sum = 0;
		good_समयr_count = 0;
		अगर ((measured_बार[max] - estimate) <
				(estimate - measured_बार[min])) अणु
			prपूर्णांकk(KERN_NOTICE "calibrate_delay_direct() dropping "
					"min bogoMips estimate %d = %lu\n",
				min, measured_बार[min]);
			measured_बार[min] = 0;
			min = max;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_NOTICE "calibrate_delay_direct() dropping "
					"max bogoMips estimate %d = %lu\n",
				max, measured_बार[max]);
			measured_बार[max] = 0;
			max = min;
		पूर्ण

		क्रम (i = 0; i < MAX_सूचीECT_CALIBRATION_RETRIES; i++) अणु
			अगर (measured_बार[i] == 0)
				जारी;
			good_समयr_count++;
			good_समयr_sum += measured_बार[i];
			अगर (measured_बार[i] < measured_बार[min])
				min = i;
			अगर (measured_बार[i] > measured_बार[max])
				max = i;
		पूर्ण

	पूर्ण

	prपूर्णांकk(KERN_NOTICE "calibrate_delay_direct() failed to get a good "
	       "estimate for loops_per_jiffy.\nProbably due to long platform "
		"interrupts. Consider using \"lpj=\" boot option.\n");
	वापस 0;
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ calibrate_delay_direct(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * This is the number of bits of precision क्रम the loops_per_jअगरfy.  Each
 * समय we refine our estimate after the first takes 1.5/HZ seconds, so try
 * to start with a good estimate.
 * For the boot cpu we can skip the delay calibration and assign it a value
 * calculated based on the समयr frequency.
 * For the rest of the CPUs we cannot assume that the समयr frequency is same as
 * the cpu frequency, hence करो the calibration क्रम those.
 */
#घोषणा LPS_PREC 8

अटल अचिन्हित दीर्घ calibrate_delay_converge(व्योम)
अणु
	/* First stage - slowly accelerate to find initial bounds */
	अचिन्हित दीर्घ lpj, lpj_base, ticks, loopadd, loopadd_base, chop_limit;
	पूर्णांक trials = 0, band = 0, trial_in_band = 0;

	lpj = (1<<12);

	/* रुको क्रम "start of" घड़ी tick */
	ticks = jअगरfies;
	जबतक (ticks == jअगरfies)
		; /* nothing */
	/* Go .. */
	ticks = jअगरfies;
	करो अणु
		अगर (++trial_in_band == (1<<band)) अणु
			++band;
			trial_in_band = 0;
		पूर्ण
		__delay(lpj * band);
		trials += band;
	पूर्ण जबतक (ticks == jअगरfies);
	/*
	 * We overshot, so retreat to a clear underestimate. Then estimate
	 * the largest likely undershoot. This defines our chop bounds.
	 */
	trials -= band;
	loopadd_base = lpj * band;
	lpj_base = lpj * trials;

recalibrate:
	lpj = lpj_base;
	loopadd = loopadd_base;

	/*
	 * Do a binary approximation to get lpj set to
	 * equal one घड़ी (up to LPS_PREC bits)
	 */
	chop_limit = lpj >> LPS_PREC;
	जबतक (loopadd > chop_limit) अणु
		lpj += loopadd;
		ticks = jअगरfies;
		जबतक (ticks == jअगरfies)
			; /* nothing */
		ticks = jअगरfies;
		__delay(lpj);
		अगर (jअगरfies != ticks)	/* दीर्घer than 1 tick */
			lpj -= loopadd;
		loopadd >>= 1;
	पूर्ण
	/*
	 * If we incremented every single समय possible, presume we've
	 * massively underestimated initially, and retry with a higher
	 * start, and larger range. (Only seen on x86_64, due to SMIs)
	 */
	अगर (lpj + loopadd * 2 == lpj_base + loopadd_base * 2) अणु
		lpj_base = lpj;
		loopadd_base <<= 2;
		जाओ recalibrate;
	पूर्ण

	वापस lpj;
पूर्ण

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_loops_per_jअगरfy) = अणु 0 पूर्ण;

/*
 * Check अगर cpu calibration delay is alपढ़ोy known. For example,
 * some processors with multi-core sockets may have all cores
 * with the same calibration delay.
 *
 * Architectures should override this function अगर a faster calibration
 * method is available.
 */
अचिन्हित दीर्घ __attribute__((weak)) calibrate_delay_is_known(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Indicate the cpu delay calibration is करोne. This can be used by
 * architectures to stop accepting delay समयr registrations after this poपूर्णांक.
 */

व्योम __attribute__((weak)) calibration_delay_करोne(व्योम)
अणु
पूर्ण

व्योम calibrate_delay(व्योम)
अणु
	अचिन्हित दीर्घ lpj;
	अटल bool prपूर्णांकed;
	पूर्णांक this_cpu = smp_processor_id();

	अगर (per_cpu(cpu_loops_per_jअगरfy, this_cpu)) अणु
		lpj = per_cpu(cpu_loops_per_jअगरfy, this_cpu);
		अगर (!prपूर्णांकed)
			pr_info("Calibrating delay loop (skipped) "
				"already calibrated this CPU");
	पूर्ण अन्यथा अगर (preset_lpj) अणु
		lpj = preset_lpj;
		अगर (!prपूर्णांकed)
			pr_info("Calibrating delay loop (skipped) "
				"preset value.. ");
	पूर्ण अन्यथा अगर ((!prपूर्णांकed) && lpj_fine) अणु
		lpj = lpj_fine;
		pr_info("Calibrating delay loop (skipped), "
			"value calculated using timer frequency.. ");
	पूर्ण अन्यथा अगर ((lpj = calibrate_delay_is_known())) अणु
		;
	पूर्ण अन्यथा अगर ((lpj = calibrate_delay_direct()) != 0) अणु
		अगर (!prपूर्णांकed)
			pr_info("Calibrating delay using timer "
				"specific routine.. ");
	पूर्ण अन्यथा अणु
		अगर (!prपूर्णांकed)
			pr_info("Calibrating delay loop... ");
		lpj = calibrate_delay_converge();
	पूर्ण
	per_cpu(cpu_loops_per_jअगरfy, this_cpu) = lpj;
	अगर (!prपूर्णांकed)
		pr_cont("%lu.%02lu BogoMIPS (lpj=%lu)\n",
			lpj/(500000/HZ),
			(lpj/(5000/HZ)) % 100, lpj);

	loops_per_jअगरfy = lpj;
	prपूर्णांकed = true;

	calibration_delay_करोne();
पूर्ण
