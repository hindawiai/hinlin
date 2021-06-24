<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Manage affinity to optimize IPIs inside the kernel perf API. */
#घोषणा _GNU_SOURCE 1
#समावेश <sched.h>
#समावेश <मानककोष.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/zभाग.स>
#समावेश "perf.h"
#समावेश "cpumap.h"
#समावेश "affinity.h"

अटल पूर्णांक get_cpu_set_size(व्योम)
अणु
	पूर्णांक sz = cpu__max_cpu() + 8 - 1;
	/*
	 * sched_getaffinity करोesn't like masks smaller than the kernel.
	 * Hopefully that's big enough.
	 */
	अगर (sz < 4096)
		sz = 4096;
	वापस sz / 8;
पूर्ण

पूर्णांक affinity__setup(काष्ठा affinity *a)
अणु
	पूर्णांक cpu_set_size = get_cpu_set_size();

	a->orig_cpus = biपंचांगap_alloc(cpu_set_size * 8);
	अगर (!a->orig_cpus)
		वापस -1;
	sched_getaffinity(0, cpu_set_size, (cpu_set_t *)a->orig_cpus);
	a->sched_cpus = biपंचांगap_alloc(cpu_set_size * 8);
	अगर (!a->sched_cpus) अणु
		zमुक्त(&a->orig_cpus);
		वापस -1;
	पूर्ण
	biपंचांगap_zero((अचिन्हित दीर्घ *)a->sched_cpus, cpu_set_size);
	a->changed = false;
	वापस 0;
पूर्ण

/*
 * perf_event_खोलो करोes an IPI पूर्णांकernally to the target CPU.
 * It is more efficient to change perf's affinity to the target
 * CPU and then set up all events on that CPU, so we amortize
 * CPU communication.
 */
व्योम affinity__set(काष्ठा affinity *a, पूर्णांक cpu)
अणु
	पूर्णांक cpu_set_size = get_cpu_set_size();

	अगर (cpu == -1)
		वापस;
	a->changed = true;
	set_bit(cpu, a->sched_cpus);
	/*
	 * We ignore errors because affinity is just an optimization.
	 * This could happen क्रम example with isolated CPUs or cpusets.
	 * In this हाल the IPIs inside the kernel's perf API still work.
	 */
	sched_setaffinity(0, cpu_set_size, (cpu_set_t *)a->sched_cpus);
	clear_bit(cpu, a->sched_cpus);
पूर्ण

व्योम affinity__cleanup(काष्ठा affinity *a)
अणु
	पूर्णांक cpu_set_size = get_cpu_set_size();

	अगर (a->changed)
		sched_setaffinity(0, cpu_set_size, (cpu_set_t *)a->orig_cpus);
	zमुक्त(&a->sched_cpus);
	zमुक्त(&a->orig_cpus);
पूर्ण
