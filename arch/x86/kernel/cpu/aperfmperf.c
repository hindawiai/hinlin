<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * x86 APERF/MPERF KHz calculation क्रम
 * /sys/.../cpufreq/scaling_cur_freq
 *
 * Copyright (C) 2017 Intel Corp.
 * Author: Len Brown <len.brown@पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/math64.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/rcupdate.h>

#समावेश "cpu.h"

काष्ठा aperfmperf_sample अणु
	अचिन्हित पूर्णांक	khz;
	atomic_t	scfpending;
	kसमय_प्रकार	समय;
	u64	aperf;
	u64	mperf;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा aperfmperf_sample, samples);

#घोषणा APERFMPERF_CACHE_THRESHOLD_MS	10
#घोषणा APERFMPERF_REFRESH_DELAY_MS	10
#घोषणा APERFMPERF_STALE_THRESHOLD_MS	1000

/*
 * aperfmperf_snapshot_khz()
 * On the current CPU, snapshot APERF, MPERF, and jअगरfies
 * unless we alपढ़ोy did it within 10ms
 * calculate kHz, save snapshot
 */
अटल व्योम aperfmperf_snapshot_khz(व्योम *dummy)
अणु
	u64 aperf, aperf_delta;
	u64 mperf, mperf_delta;
	काष्ठा aperfmperf_sample *s = this_cpu_ptr(&samples);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);
	local_irq_restore(flags);

	aperf_delta = aperf - s->aperf;
	mperf_delta = mperf - s->mperf;

	/*
	 * There is no architectural guarantee that MPERF
	 * increments faster than we can पढ़ो it.
	 */
	अगर (mperf_delta == 0)
		वापस;

	s->समय = kसमय_get();
	s->aperf = aperf;
	s->mperf = mperf;
	s->khz = भाग64_u64((cpu_khz * aperf_delta), mperf_delta);
	atomic_set_release(&s->scfpending, 0);
पूर्ण

अटल bool aperfmperf_snapshot_cpu(पूर्णांक cpu, kसमय_प्रकार now, bool रुको)
अणु
	s64 समय_delta = kसमय_ms_delta(now, per_cpu(samples.समय, cpu));
	काष्ठा aperfmperf_sample *s = per_cpu_ptr(&samples, cpu);

	/* Don't bother re-computing within the cache threshold समय. */
	अगर (समय_delta < APERFMPERF_CACHE_THRESHOLD_MS)
		वापस true;

	अगर (!atomic_xchg(&s->scfpending, 1) || रुको)
		smp_call_function_single(cpu, aperfmperf_snapshot_khz, शून्य, रुको);

	/* Return false अगर the previous iteration was too दीर्घ ago. */
	वापस समय_delta <= APERFMPERF_STALE_THRESHOLD_MS;
पूर्ण

अचिन्हित पूर्णांक aperfmperf_get_khz(पूर्णांक cpu)
अणु
	अगर (!cpu_khz)
		वापस 0;

	अगर (!boot_cpu_has(X86_FEATURE_APERFMPERF))
		वापस 0;

	अगर (!housekeeping_cpu(cpu, HK_FLAG_MISC))
		वापस 0;

	अगर (rcu_is_idle_cpu(cpu))
		वापस 0; /* Idle CPUs are completely unपूर्णांकeresting. */

	aperfmperf_snapshot_cpu(cpu, kसमय_get(), true);
	वापस per_cpu(samples.khz, cpu);
पूर्ण

व्योम arch_freq_prepare_all(व्योम)
अणु
	kसमय_प्रकार now = kसमय_get();
	bool रुको = false;
	पूर्णांक cpu;

	अगर (!cpu_khz)
		वापस;

	अगर (!boot_cpu_has(X86_FEATURE_APERFMPERF))
		वापस;

	क्रम_each_online_cpu(cpu) अणु
		अगर (!housekeeping_cpu(cpu, HK_FLAG_MISC))
			जारी;
		अगर (rcu_is_idle_cpu(cpu))
			जारी; /* Idle CPUs are completely unपूर्णांकeresting. */
		अगर (!aperfmperf_snapshot_cpu(cpu, now, false))
			रुको = true;
	पूर्ण

	अगर (रुको)
		msleep(APERFMPERF_REFRESH_DELAY_MS);
पूर्ण

अचिन्हित पूर्णांक arch_freq_get_on_cpu(पूर्णांक cpu)
अणु
	काष्ठा aperfmperf_sample *s = per_cpu_ptr(&samples, cpu);

	अगर (!cpu_khz)
		वापस 0;

	अगर (!boot_cpu_has(X86_FEATURE_APERFMPERF))
		वापस 0;

	अगर (!housekeeping_cpu(cpu, HK_FLAG_MISC))
		वापस 0;

	अगर (aperfmperf_snapshot_cpu(cpu, kसमय_get(), true))
		वापस per_cpu(samples.khz, cpu);

	msleep(APERFMPERF_REFRESH_DELAY_MS);
	atomic_set(&s->scfpending, 1);
	smp_mb(); /* ->scfpending beक्रमe smp_call_function_single(). */
	smp_call_function_single(cpu, aperfmperf_snapshot_khz, शून्य, 1);

	वापस per_cpu(samples.khz, cpu);
पूर्ण
