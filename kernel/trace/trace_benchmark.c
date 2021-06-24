<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/trace_घड़ी.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_benchmark.h"

अटल काष्ठा task_काष्ठा *bm_event_thपढ़ो;

अटल अक्षर bm_str[BENCHMARK_EVENT_STRLEN] = "START";

अटल u64 bm_total;
अटल u64 bm_totalsq;
अटल u64 bm_last;
अटल u64 bm_max;
अटल u64 bm_min;
अटल u64 bm_first;
अटल u64 bm_cnt;
अटल u64 bm_stddev;
अटल अचिन्हित पूर्णांक bm_avg;
अटल अचिन्हित पूर्णांक bm_std;

अटल bool ok_to_run;

/*
 * This माला_लो called in a loop recording the समय it took to ग_लिखो
 * the tracepoपूर्णांक. What it ग_लिखोs is the समय statistics of the last
 * tracepoपूर्णांक ग_लिखो. As there is nothing to ग_लिखो the first समय
 * it simply ग_लिखोs "START". As the first ग_लिखो is cold cache and
 * the rest is hot, we save off that समय in bm_first and it is
 * reported as "first", which is shown in the second ग_लिखो to the
 * tracepoपूर्णांक. The "first" field is written within the अटलs from
 * then on but never changes.
 */
अटल व्योम trace_करो_benchmark(व्योम)
अणु
	u64 start;
	u64 stop;
	u64 delta;
	u64 stddev;
	u64 seed;
	u64 last_seed;
	अचिन्हित पूर्णांक avg;
	अचिन्हित पूर्णांक std = 0;

	/* Only run अगर the tracepoपूर्णांक is actually active */
	अगर (!trace_benchmark_event_enabled() || !tracing_is_on())
		वापस;

	local_irq_disable();
	start = trace_घड़ी_local();
	trace_benchmark_event(bm_str);
	stop = trace_घड़ी_local();
	local_irq_enable();

	bm_cnt++;

	delta = stop - start;

	/*
	 * The first पढ़ो is cold cached, keep it separate from the
	 * other calculations.
	 */
	अगर (bm_cnt == 1) अणु
		bm_first = delta;
		scnम_लिखो(bm_str, BENCHMARK_EVENT_STRLEN,
			  "first=%llu [COLD CACHED]", bm_first);
		वापस;
	पूर्ण

	bm_last = delta;

	अगर (delta > bm_max)
		bm_max = delta;
	अगर (!bm_min || delta < bm_min)
		bm_min = delta;

	/*
	 * When bm_cnt is greater than अच_पूर्णांक_उच्च, it अवरोधs the statistics
	 * accounting. Freeze the statistics when that happens.
	 * We should have enough data क्रम the avg and stddev anyway.
	 */
	अगर (bm_cnt > अच_पूर्णांक_उच्च) अणु
		scnम_लिखो(bm_str, BENCHMARK_EVENT_STRLEN,
		    "last=%llu first=%llu max=%llu min=%llu ** avg=%u std=%d std^2=%lld",
			  bm_last, bm_first, bm_max, bm_min, bm_avg, bm_std, bm_stddev);
		वापस;
	पूर्ण

	bm_total += delta;
	bm_totalsq += delta * delta;


	अगर (bm_cnt > 1) अणु
		/*
		 * Apply Welक्रमd's method to calculate standard deviation:
		 * s^2 = 1 / (n * (n-1)) * (n * \Sum (x_i)^2 - (\Sum x_i)^2)
		 */
		stddev = (u64)bm_cnt * bm_totalsq - bm_total * bm_total;
		करो_भाग(stddev, (u32)bm_cnt);
		करो_भाग(stddev, (u32)bm_cnt - 1);
	पूर्ण अन्यथा
		stddev = 0;

	delta = bm_total;
	करो_भाग(delta, bm_cnt);
	avg = delta;

	अगर (stddev > 0) अणु
		पूर्णांक i = 0;
		/*
		 * stddev is the square of standard deviation but
		 * we want the actually number. Use the average
		 * as our seed to find the std.
		 *
		 * The next try is:
		 *  x = (x + N/x) / 2
		 *
		 * Where N is the squared number to find the square
		 * root of.
		 */
		seed = avg;
		करो अणु
			last_seed = seed;
			seed = stddev;
			अगर (!last_seed)
				अवरोध;
			करो_भाग(seed, last_seed);
			seed += last_seed;
			करो_भाग(seed, 2);
		पूर्ण जबतक (i++ < 10 && last_seed != seed);

		std = seed;
	पूर्ण

	scnम_लिखो(bm_str, BENCHMARK_EVENT_STRLEN,
		  "last=%llu first=%llu max=%llu min=%llu avg=%u std=%d std^2=%lld",
		  bm_last, bm_first, bm_max, bm_min, avg, std, stddev);

	bm_std = std;
	bm_avg = avg;
	bm_stddev = stddev;
पूर्ण

अटल पूर्णांक benchmark_event_kthपढ़ो(व्योम *arg)
अणु
	/* sleep a bit to make sure the tracepoपूर्णांक माला_लो activated */
	msleep(100);

	जबतक (!kthपढ़ो_should_stop()) अणु

		trace_करो_benchmark();

		/*
		 * We करोn't go to sleep, but let others run as well.
		 * This is basically a "yield()" to let any task that
		 * wants to run, schedule in, but अगर the CPU is idle,
		 * we'll keep burning cycles.
		 *
		 * Note the tasks_rcu_qs() version of cond_resched() will
		 * notअगरy synchronize_rcu_tasks() that this thपढ़ो has
		 * passed a quiescent state क्रम rcu_tasks. Otherwise
		 * this thपढ़ो will never voluntarily schedule which would
		 * block synchronize_rcu_tasks() indefinitely.
		 */
		cond_resched_tasks_rcu_qs();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * When the benchmark tracepoपूर्णांक is enabled, it calls this
 * function and the thपढ़ो that calls the tracepoपूर्णांक is created.
 */
पूर्णांक trace_benchmark_reg(व्योम)
अणु
	अगर (!ok_to_run) अणु
		pr_warn("trace benchmark cannot be started via kernel command line\n");
		वापस -EBUSY;
	पूर्ण

	bm_event_thपढ़ो = kthपढ़ो_run(benchmark_event_kthपढ़ो,
				      शून्य, "event_benchmark");
	अगर (IS_ERR(bm_event_thपढ़ो)) अणु
		pr_warn("trace benchmark failed to create kernel thread\n");
		वापस PTR_ERR(bm_event_thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * When the benchmark tracepoपूर्णांक is disabled, it calls this
 * function and the thपढ़ो that calls the tracepoपूर्णांक is deleted
 * and all the numbers are reset.
 */
व्योम trace_benchmark_unreg(व्योम)
अणु
	अगर (!bm_event_thपढ़ो)
		वापस;

	kthपढ़ो_stop(bm_event_thपढ़ो);
	bm_event_thपढ़ो = शून्य;

	म_नकल(bm_str, "START");
	bm_total = 0;
	bm_totalsq = 0;
	bm_last = 0;
	bm_max = 0;
	bm_min = 0;
	bm_cnt = 0;
	/* These करोn't need to be reset but reset them anyway */
	bm_first = 0;
	bm_std = 0;
	bm_avg = 0;
	bm_stddev = 0;
पूर्ण

अटल __init पूर्णांक ok_to_run_trace_benchmark(व्योम)
अणु
	ok_to_run = true;

	वापस 0;
पूर्ण

early_initcall(ok_to_run_trace_benchmark);
