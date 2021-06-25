<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Torture test क्रम smp_call_function() and मित्रs.
//
// Copyright (C) Facebook, 2020.
//
// Author: Paul E. McKenney <paulmck@kernel.org>

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rcupdate_trace.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/srcu.h>
#समावेश <linux/slab.h>
#समावेश <linux/torture.h>
#समावेश <linux/types.h>

#घोषणा SCFTORT_STRING "scftorture"
#घोषणा SCFTORT_FLAG SCFTORT_STRING ": "

#घोषणा SCFTORTOUT(s, x...) \
	pr_alert(SCFTORT_FLAG s, ## x)

#घोषणा VERBOSE_SCFTORTOUT(s, x...) \
	करो अणु अगर (verbose) pr_alert(SCFTORT_FLAG s, ## x); पूर्ण जबतक (0)

#घोषणा VERBOSE_SCFTORTOUT_ERRSTRING(s, x...) \
	करो अणु अगर (verbose) pr_alert(SCFTORT_FLAG "!!! " s, ## x); पूर्ण जबतक (0)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul E. McKenney <paulmck@kernel.org>");

// Wait until there are multiple CPUs beक्रमe starting test.
torture_param(पूर्णांक, holकरोff, IS_BUILTIN(CONFIG_SCF_TORTURE_TEST) ? 10 : 0,
	      "Holdoff time before test start (s)");
torture_param(पूर्णांक, दीर्घरुको, 0, "Include ridiculously long waits? (seconds)");
torture_param(पूर्णांक, nthपढ़ोs, -1, "# threads, defaults to -1 for all CPUs.");
torture_param(पूर्णांक, onoff_holकरोff, 0, "Time after boot before CPU hotplugs (s)");
torture_param(पूर्णांक, onoff_पूर्णांकerval, 0, "Time between CPU hotplugs (s), 0=disable");
torture_param(पूर्णांक, shutकरोwn_secs, 0, "Shutdown time (ms), <= zero to disable.");
torture_param(पूर्णांक, stat_पूर्णांकerval, 60, "Number of seconds between stats printk()s.");
torture_param(पूर्णांक, stutter, 5, "Number of jiffies to run/halt test, 0=disable");
torture_param(bool, use_cpus_पढ़ो_lock, 0, "Use cpus_read_lock() to exclude CPU hotplug.");
torture_param(पूर्णांक, verbose, 0, "Enable verbose debugging printk()s");
torture_param(पूर्णांक, weight_resched, -1, "Testing weight for resched_cpu() operations.");
torture_param(पूर्णांक, weight_single, -1, "Testing weight for single-CPU no-wait operations.");
torture_param(पूर्णांक, weight_single_रुको, -1, "Testing weight for single-CPU operations.");
torture_param(पूर्णांक, weight_many, -1, "Testing weight for multi-CPU no-wait operations.");
torture_param(पूर्णांक, weight_many_रुको, -1, "Testing weight for multi-CPU operations.");
torture_param(पूर्णांक, weight_all, -1, "Testing weight for all-CPU no-wait operations.");
torture_param(पूर्णांक, weight_all_रुको, -1, "Testing weight for all-CPU operations.");

अक्षर *torture_type = "";

#अगर_घोषित MODULE
# define SCFTORT_SHUTDOWN 0
#अन्यथा
# define SCFTORT_SHUTDOWN 1
#पूर्ण_अगर

torture_param(bool, shutकरोwn, SCFTORT_SHUTDOWN, "Shutdown at end of torture test.");

काष्ठा scf_statistics अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक cpu;
	दीर्घ दीर्घ n_resched;
	दीर्घ दीर्घ n_single;
	दीर्घ दीर्घ n_single_ofl;
	दीर्घ दीर्घ n_single_रुको;
	दीर्घ दीर्घ n_single_रुको_ofl;
	दीर्घ दीर्घ n_many;
	दीर्घ दीर्घ n_many_रुको;
	दीर्घ दीर्घ n_all;
	दीर्घ दीर्घ n_all_रुको;
पूर्ण;

अटल काष्ठा scf_statistics *scf_stats_p;
अटल काष्ठा task_काष्ठा *scf_torture_stats_task;
अटल DEFINE_PER_CPU(दीर्घ दीर्घ, scf_invoked_count);

// Data क्रम अक्रमom primitive selection
#घोषणा SCF_PRIM_RESCHED	0
#घोषणा SCF_PRIM_SINGLE		1
#घोषणा SCF_PRIM_MANY		2
#घोषणा SCF_PRIM_ALL		3
#घोषणा SCF_NPRIMS		7 // Need रुको and no-रुको versions of each,
				  //  except क्रम SCF_PRIM_RESCHED.

अटल अक्षर *scf_prim_name[] = अणु
	"resched_cpu",
	"smp_call_function_single",
	"smp_call_function_many",
	"smp_call_function",
पूर्ण;

काष्ठा scf_selector अणु
	अचिन्हित दीर्घ scfs_weight;
	पूर्णांक scfs_prim;
	bool scfs_रुको;
पूर्ण;
अटल काष्ठा scf_selector scf_sel_array[SCF_NPRIMS];
अटल पूर्णांक scf_sel_array_len;
अटल अचिन्हित दीर्घ scf_sel_totweight;

// Communicate between caller and handler.
काष्ठा scf_check अणु
	bool scfc_in;
	bool scfc_out;
	पूर्णांक scfc_cpu; // -1 क्रम not _single().
	bool scfc_रुको;
पूर्ण;

// Use to रुको क्रम all thपढ़ोs to start.
अटल atomic_t n_started;
अटल atomic_t n_errs;
अटल atomic_t n_mb_in_errs;
अटल atomic_t n_mb_out_errs;
अटल atomic_t n_alloc_errs;
अटल bool scfकरोne;
अटल अक्षर *bangstr = "";

अटल DEFINE_TORTURE_RANDOM_PERCPU(scf_torture_अक्रम);

बाह्य व्योम resched_cpu(पूर्णांक cpu); // An alternative IPI vector.

// Prपूर्णांक torture statistics.  Caller must ensure serialization.
अटल व्योम scf_torture_stats_prपूर्णांक(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक i;
	दीर्घ दीर्घ invoked_count = 0;
	bool isकरोne = READ_ONCE(scfकरोne);
	काष्ठा scf_statistics scfs = अणुपूर्ण;

	क्रम_each_possible_cpu(cpu)
		invoked_count += data_race(per_cpu(scf_invoked_count, cpu));
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		scfs.n_resched += scf_stats_p[i].n_resched;
		scfs.n_single += scf_stats_p[i].n_single;
		scfs.n_single_ofl += scf_stats_p[i].n_single_ofl;
		scfs.n_single_रुको += scf_stats_p[i].n_single_रुको;
		scfs.n_single_रुको_ofl += scf_stats_p[i].n_single_रुको_ofl;
		scfs.n_many += scf_stats_p[i].n_many;
		scfs.n_many_रुको += scf_stats_p[i].n_many_रुको;
		scfs.n_all += scf_stats_p[i].n_all;
		scfs.n_all_रुको += scf_stats_p[i].n_all_रुको;
	पूर्ण
	अगर (atomic_पढ़ो(&n_errs) || atomic_पढ़ो(&n_mb_in_errs) ||
	    atomic_पढ़ो(&n_mb_out_errs) || atomic_पढ़ो(&n_alloc_errs))
		bangstr = "!!! ";
	pr_alert("%s %sscf_invoked_count %s: %lld resched: %lld single: %lld/%lld single_ofl: %lld/%lld many: %lld/%lld all: %lld/%lld ",
		 SCFTORT_FLAG, bangstr, isकरोne ? "VER" : "ver", invoked_count, scfs.n_resched,
		 scfs.n_single, scfs.n_single_रुको, scfs.n_single_ofl, scfs.n_single_रुको_ofl,
		 scfs.n_many, scfs.n_many_रुको, scfs.n_all, scfs.n_all_रुको);
	torture_onoff_stats();
	pr_cont("ste: %d stnmie: %d stnmoe: %d staf: %d\n", atomic_पढ़ो(&n_errs),
		atomic_पढ़ो(&n_mb_in_errs), atomic_पढ़ो(&n_mb_out_errs),
		atomic_पढ़ो(&n_alloc_errs));
पूर्ण

// Periodically prपूर्णांकs torture statistics, अगर periodic statistics prपूर्णांकing
// was specअगरied via the stat_पूर्णांकerval module parameter.
अटल पूर्णांक
scf_torture_stats(व्योम *arg)
अणु
	VERBOSE_TOROUT_STRING("scf_torture_stats task started");
	करो अणु
		schedule_समयout_पूर्णांकerruptible(stat_पूर्णांकerval * HZ);
		scf_torture_stats_prपूर्णांक();
		torture_shutकरोwn_असलorb("scf_torture_stats");
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("scf_torture_stats");
	वापस 0;
पूर्ण

// Add a primitive to the scf_sel_array[].
अटल व्योम scf_sel_add(अचिन्हित दीर्घ weight, पूर्णांक prim, bool रुको)
अणु
	काष्ठा scf_selector *scfsp = &scf_sel_array[scf_sel_array_len];

	// If no weight, अगर array would overflow, अगर computing three-place
	// percentages would overflow, or अगर the scf_prim_name[] array would
	// overflow, करोn't bother.  In the last three two हालs, complain.
	अगर (!weight ||
	    WARN_ON_ONCE(scf_sel_array_len >= ARRAY_SIZE(scf_sel_array)) ||
	    WARN_ON_ONCE(0 - 100000 * weight <= 100000 * scf_sel_totweight) ||
	    WARN_ON_ONCE(prim >= ARRAY_SIZE(scf_prim_name)))
		वापस;
	scf_sel_totweight += weight;
	scfsp->scfs_weight = scf_sel_totweight;
	scfsp->scfs_prim = prim;
	scfsp->scfs_रुको = रुको;
	scf_sel_array_len++;
पूर्ण

// Dump out weighting percentages क्रम scf_prim_name[] array.
अटल व्योम scf_sel_dump(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ oldw = 0;
	काष्ठा scf_selector *scfsp;
	अचिन्हित दीर्घ w;

	क्रम (i = 0; i < scf_sel_array_len; i++) अणु
		scfsp = &scf_sel_array[i];
		w = (scfsp->scfs_weight - oldw) * 100000 / scf_sel_totweight;
		pr_info("%s: %3lu.%03lu %s(%s)\n", __func__, w / 1000, w % 1000,
			scf_prim_name[scfsp->scfs_prim],
			scfsp->scfs_रुको ? "wait" : "nowait");
		oldw = scfsp->scfs_weight;
	पूर्ण
पूर्ण

// Ranकरोmly pick a primitive and रुको/noरुको, based on weightings.
अटल काष्ठा scf_selector *scf_sel_अक्रम(काष्ठा torture_अक्रमom_state *trsp)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ w = torture_अक्रमom(trsp) % (scf_sel_totweight + 1);

	क्रम (i = 0; i < scf_sel_array_len; i++)
		अगर (scf_sel_array[i].scfs_weight >= w)
			वापस &scf_sel_array[i];
	WARN_ON_ONCE(1);
	वापस &scf_sel_array[0];
पूर्ण

// Update statistics and occasionally burn up mass quantities of CPU समय,
// अगर told to करो so via scftorture.दीर्घरुको.  Otherwise, occasionally burn
// a little bit.
अटल व्योम scf_handler(व्योम *scfc_in)
अणु
	पूर्णांक i;
	पूर्णांक j;
	अचिन्हित दीर्घ r = torture_अक्रमom(this_cpu_ptr(&scf_torture_अक्रम));
	काष्ठा scf_check *scfcp = scfc_in;

	अगर (likely(scfcp)) अणु
		WRITE_ONCE(scfcp->scfc_out, false); // For multiple receivers.
		अगर (WARN_ON_ONCE(unlikely(!READ_ONCE(scfcp->scfc_in))))
			atomic_inc(&n_mb_in_errs);
	पूर्ण
	this_cpu_inc(scf_invoked_count);
	अगर (दीर्घरुको <= 0) अणु
		अगर (!(r & 0xffc0))
			udelay(r & 0x3f);
		जाओ out;
	पूर्ण
	अगर (r & 0xfff)
		जाओ out;
	r = (r >> 12);
	अगर (दीर्घरुको <= 0) अणु
		udelay((r & 0xff) + 1);
		जाओ out;
	पूर्ण
	r = r % दीर्घरुको + 1;
	क्रम (i = 0; i < r; i++) अणु
		क्रम (j = 0; j < 1000; j++) अणु
			udelay(1000);
			cpu_relax();
		पूर्ण
	पूर्ण
out:
	अगर (unlikely(!scfcp))
		वापस;
	अगर (scfcp->scfc_रुको)
		WRITE_ONCE(scfcp->scfc_out, true);
	अन्यथा
		kमुक्त(scfcp);
पूर्ण

// As above, but check क्रम correct CPU.
अटल व्योम scf_handler_1(व्योम *scfc_in)
अणु
	काष्ठा scf_check *scfcp = scfc_in;

	अगर (likely(scfcp) && WARN_ONCE(smp_processor_id() != scfcp->scfc_cpu, "%s: Wanted CPU %d got CPU %d\n", __func__, scfcp->scfc_cpu, smp_processor_id())) अणु
		atomic_inc(&n_errs);
	पूर्ण
	scf_handler(scfcp);
पूर्ण

// Ranकरोmly करो an smp_call_function*() invocation.
अटल व्योम scftorture_invoke_one(काष्ठा scf_statistics *scfp, काष्ठा torture_अक्रमom_state *trsp)
अणु
	uपूर्णांकptr_t cpu;
	पूर्णांक ret = 0;
	काष्ठा scf_check *scfcp = शून्य;
	काष्ठा scf_selector *scfsp = scf_sel_अक्रम(trsp);

	अगर (use_cpus_पढ़ो_lock)
		cpus_पढ़ो_lock();
	अन्यथा
		preempt_disable();
	अगर (scfsp->scfs_prim == SCF_PRIM_SINGLE || scfsp->scfs_रुको) अणु
		scfcp = kदो_स्मृति(माप(*scfcp), GFP_ATOMIC);
		अगर (WARN_ON_ONCE(!scfcp)) अणु
			atomic_inc(&n_alloc_errs);
		पूर्ण अन्यथा अणु
			scfcp->scfc_cpu = -1;
			scfcp->scfc_रुको = scfsp->scfs_रुको;
			scfcp->scfc_out = false;
		पूर्ण
	पूर्ण
	चयन (scfsp->scfs_prim) अणु
	हाल SCF_PRIM_RESCHED:
		अगर (IS_BUILTIN(CONFIG_SCF_TORTURE_TEST)) अणु
			cpu = torture_अक्रमom(trsp) % nr_cpu_ids;
			scfp->n_resched++;
			resched_cpu(cpu);
		पूर्ण
		अवरोध;
	हाल SCF_PRIM_SINGLE:
		cpu = torture_अक्रमom(trsp) % nr_cpu_ids;
		अगर (scfsp->scfs_रुको)
			scfp->n_single_रुको++;
		अन्यथा
			scfp->n_single++;
		अगर (scfcp) अणु
			scfcp->scfc_cpu = cpu;
			barrier(); // Prevent race-reduction compiler optimizations.
			scfcp->scfc_in = true;
		पूर्ण
		ret = smp_call_function_single(cpu, scf_handler_1, (व्योम *)scfcp, scfsp->scfs_रुको);
		अगर (ret) अणु
			अगर (scfsp->scfs_रुको)
				scfp->n_single_रुको_ofl++;
			अन्यथा
				scfp->n_single_ofl++;
			kमुक्त(scfcp);
			scfcp = शून्य;
		पूर्ण
		अवरोध;
	हाल SCF_PRIM_MANY:
		अगर (scfsp->scfs_रुको)
			scfp->n_many_रुको++;
		अन्यथा
			scfp->n_many++;
		अगर (scfcp) अणु
			barrier(); // Prevent race-reduction compiler optimizations.
			scfcp->scfc_in = true;
		पूर्ण
		smp_call_function_many(cpu_online_mask, scf_handler, scfcp, scfsp->scfs_रुको);
		अवरोध;
	हाल SCF_PRIM_ALL:
		अगर (scfsp->scfs_रुको)
			scfp->n_all_रुको++;
		अन्यथा
			scfp->n_all++;
		अगर (scfcp) अणु
			barrier(); // Prevent race-reduction compiler optimizations.
			scfcp->scfc_in = true;
		पूर्ण
		smp_call_function(scf_handler, scfcp, scfsp->scfs_रुको);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अगर (scfcp)
			scfcp->scfc_out = true;
	पूर्ण
	अगर (scfcp && scfsp->scfs_रुको) अणु
		अगर (WARN_ON_ONCE((num_online_cpus() > 1 || scfsp->scfs_prim == SCF_PRIM_SINGLE) &&
				 !scfcp->scfc_out))
			atomic_inc(&n_mb_out_errs); // Leak rather than trash!
		अन्यथा
			kमुक्त(scfcp);
		barrier(); // Prevent race-reduction compiler optimizations.
	पूर्ण
	अगर (use_cpus_पढ़ो_lock)
		cpus_पढ़ो_unlock();
	अन्यथा
		preempt_enable();
	अगर (!(torture_अक्रमom(trsp) & 0xfff))
		schedule_समयout_unपूर्णांकerruptible(1);
पूर्ण

// SCF test kthपढ़ो.  Repeatedly करोes calls to members of the
// smp_call_function() family of functions.
अटल पूर्णांक scftorture_invoker(व्योम *arg)
अणु
	पूर्णांक cpu;
	पूर्णांक curcpu;
	DEFINE_TORTURE_RANDOM(अक्रम);
	काष्ठा scf_statistics *scfp = (काष्ठा scf_statistics *)arg;
	bool was_offline = false;

	VERBOSE_SCFTORTOUT("scftorture_invoker %d: task started", scfp->cpu);
	cpu = scfp->cpu % nr_cpu_ids;
	set_cpus_allowed_ptr(current, cpumask_of(cpu));
	set_user_nice(current, MAX_NICE);
	अगर (holकरोff)
		schedule_समयout_पूर्णांकerruptible(holकरोff * HZ);

	VERBOSE_SCFTORTOUT("scftorture_invoker %d: Waiting for all SCF torturers from cpu %d", scfp->cpu, smp_processor_id());

	// Make sure that the CPU is affinitized appropriately during testing.
	curcpu = smp_processor_id();
	WARN_ONCE(curcpu != scfp->cpu % nr_cpu_ids,
		  "%s: Wanted CPU %d, running on %d, nr_cpu_ids = %d\n",
		  __func__, scfp->cpu, curcpu, nr_cpu_ids);

	अगर (!atomic_dec_वापस(&n_started))
		जबतक (atomic_पढ़ो_acquire(&n_started)) अणु
			अगर (torture_must_stop()) अणु
				VERBOSE_SCFTORTOUT("scftorture_invoker %d ended before starting", scfp->cpu);
				जाओ end;
			पूर्ण
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण

	VERBOSE_SCFTORTOUT("scftorture_invoker %d started", scfp->cpu);

	करो अणु
		scftorture_invoke_one(scfp, &अक्रम);
		जबतक (cpu_is_offline(cpu) && !torture_must_stop()) अणु
			schedule_समयout_पूर्णांकerruptible(HZ / 5);
			was_offline = true;
		पूर्ण
		अगर (was_offline) अणु
			set_cpus_allowed_ptr(current, cpumask_of(cpu));
			was_offline = false;
		पूर्ण
		cond_resched();
		stutter_रुको("scftorture_invoker");
	पूर्ण जबतक (!torture_must_stop());

	VERBOSE_SCFTORTOUT("scftorture_invoker %d ended", scfp->cpu);
end:
	torture_kthपढ़ो_stopping("scftorture_invoker");
	वापस 0;
पूर्ण

अटल व्योम
scftorture_prपूर्णांक_module_parms(स्थिर अक्षर *tag)
अणु
	pr_alert(SCFTORT_FLAG
		 "--- %s:  verbose=%d holdoff=%d longwait=%d nthreads=%d onoff_holdoff=%d onoff_interval=%d shutdown_secs=%d stat_interval=%d stutter=%d use_cpus_read_lock=%d, weight_resched=%d, weight_single=%d, weight_single_wait=%d, weight_many=%d, weight_many_wait=%d, weight_all=%d, weight_all_wait=%d\n", tag,
		 verbose, holकरोff, दीर्घरुको, nthपढ़ोs, onoff_holकरोff, onoff_पूर्णांकerval, shutकरोwn, stat_पूर्णांकerval, stutter, use_cpus_पढ़ो_lock, weight_resched, weight_single, weight_single_रुको, weight_many, weight_many_रुको, weight_all, weight_all_रुको);
पूर्ण

अटल व्योम scf_cleanup_handler(व्योम *unused)
अणु
पूर्ण

अटल व्योम scf_torture_cleanup(व्योम)
अणु
	पूर्णांक i;

	अगर (torture_cleanup_begin())
		वापस;

	WRITE_ONCE(scfकरोne, true);
	अगर (nthपढ़ोs)
		क्रम (i = 0; i < nthपढ़ोs; i++)
			torture_stop_kthपढ़ो("scftorture_invoker", scf_stats_p[i].task);
	अन्यथा
		जाओ end;
	smp_call_function(scf_cleanup_handler, शून्य, 0);
	torture_stop_kthपढ़ो(scf_torture_stats, scf_torture_stats_task);
	scf_torture_stats_prपूर्णांक();  // -After- the stats thपढ़ो is stopped!
	kमुक्त(scf_stats_p);  // -After- the last stats prपूर्णांक has completed!
	scf_stats_p = शून्य;

	अगर (atomic_पढ़ो(&n_errs) || atomic_पढ़ो(&n_mb_in_errs) || atomic_पढ़ो(&n_mb_out_errs))
		scftorture_prपूर्णांक_module_parms("End of test: FAILURE");
	अन्यथा अगर (torture_onoff_failures())
		scftorture_prपूर्णांक_module_parms("End of test: LOCK_HOTPLUG");
	अन्यथा
		scftorture_prपूर्णांक_module_parms("End of test: SUCCESS");

end:
	torture_cleanup_end();
पूर्ण

अटल पूर्णांक __init scf_torture_init(व्योम)
अणु
	दीर्घ i;
	पूर्णांक firsterr = 0;
	अचिन्हित दीर्घ weight_resched1 = weight_resched;
	अचिन्हित दीर्घ weight_single1 = weight_single;
	अचिन्हित दीर्घ weight_single_रुको1 = weight_single_रुको;
	अचिन्हित दीर्घ weight_many1 = weight_many;
	अचिन्हित दीर्घ weight_many_रुको1 = weight_many_रुको;
	अचिन्हित दीर्घ weight_all1 = weight_all;
	अचिन्हित दीर्घ weight_all_रुको1 = weight_all_रुको;

	अगर (!torture_init_begin(SCFTORT_STRING, verbose))
		वापस -EBUSY;

	scftorture_prपूर्णांक_module_parms("Start of test");

	अगर (weight_resched == -1 && weight_single == -1 && weight_single_रुको == -1 &&
	    weight_many == -1 && weight_many_रुको == -1 &&
	    weight_all == -1 && weight_all_रुको == -1) अणु
		weight_resched1 = 2 * nr_cpu_ids;
		weight_single1 = 2 * nr_cpu_ids;
		weight_single_रुको1 = 2 * nr_cpu_ids;
		weight_many1 = 2;
		weight_many_रुको1 = 2;
		weight_all1 = 1;
		weight_all_रुको1 = 1;
	पूर्ण अन्यथा अणु
		अगर (weight_resched == -1)
			weight_resched1 = 0;
		अगर (weight_single == -1)
			weight_single1 = 0;
		अगर (weight_single_रुको == -1)
			weight_single_रुको1 = 0;
		अगर (weight_many == -1)
			weight_many1 = 0;
		अगर (weight_many_रुको == -1)
			weight_many_रुको1 = 0;
		अगर (weight_all == -1)
			weight_all1 = 0;
		अगर (weight_all_रुको == -1)
			weight_all_रुको1 = 0;
	पूर्ण
	अगर (weight_single1 == 0 && weight_single_रुको1 == 0 &&
	    weight_many1 == 0 && weight_many_रुको1 == 0 &&
	    weight_all1 == 0 && weight_all_रुको1 == 0) अणु
		VERBOSE_SCFTORTOUT_ERRSTRING("all zero weights makes no sense");
		firsterr = -EINVAL;
		जाओ unwind;
	पूर्ण
	अगर (IS_BUILTIN(CONFIG_SCF_TORTURE_TEST))
		scf_sel_add(weight_resched1, SCF_PRIM_RESCHED, false);
	अन्यथा अगर (weight_resched1)
		VERBOSE_SCFTORTOUT_ERRSTRING("built as module, weight_resched ignored");
	scf_sel_add(weight_single1, SCF_PRIM_SINGLE, false);
	scf_sel_add(weight_single_रुको1, SCF_PRIM_SINGLE, true);
	scf_sel_add(weight_many1, SCF_PRIM_MANY, false);
	scf_sel_add(weight_many_रुको1, SCF_PRIM_MANY, true);
	scf_sel_add(weight_all1, SCF_PRIM_ALL, false);
	scf_sel_add(weight_all_रुको1, SCF_PRIM_ALL, true);
	scf_sel_dump();

	अगर (onoff_पूर्णांकerval > 0) अणु
		firsterr = torture_onoff_init(onoff_holकरोff * HZ, onoff_पूर्णांकerval, शून्य);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (shutकरोwn_secs > 0) अणु
		firsterr = torture_shutकरोwn_init(shutकरोwn_secs, scf_torture_cleanup);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (stutter > 0) अणु
		firsterr = torture_stutter_init(stutter, stutter);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण

	// Worker tasks invoking smp_call_function().
	अगर (nthपढ़ोs < 0)
		nthपढ़ोs = num_online_cpus();
	scf_stats_p = kसुस्मृति(nthपढ़ोs, माप(scf_stats_p[0]), GFP_KERNEL);
	अगर (!scf_stats_p) अणु
		VERBOSE_SCFTORTOUT_ERRSTRING("out of memory");
		firsterr = -ENOMEM;
		जाओ unwind;
	पूर्ण

	VERBOSE_SCFTORTOUT("Starting %d smp_call_function() threads\n", nthपढ़ोs);

	atomic_set(&n_started, nthपढ़ोs);
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		scf_stats_p[i].cpu = i;
		firsterr = torture_create_kthपढ़ो(scftorture_invoker, (व्योम *)&scf_stats_p[i],
						  scf_stats_p[i].task);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (stat_पूर्णांकerval > 0) अणु
		firsterr = torture_create_kthपढ़ो(scf_torture_stats, शून्य, scf_torture_stats_task);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण

	torture_init_end();
	वापस 0;

unwind:
	torture_init_end();
	scf_torture_cleanup();
	वापस firsterr;
पूर्ण

module_init(scf_torture_init);
module_निकास(scf_torture_cleanup);
