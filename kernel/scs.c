<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shaकरोw Call Stack support.
 *
 * Copyright (C) 2019 Google LLC
 */

#समावेश <linux/cpuhotplug.h>
#समावेश <linux/kasan.h>
#समावेश <linux/mm.h>
#समावेश <linux/scs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/vmस्थिति.स>

अटल व्योम __scs_account(व्योम *s, पूर्णांक account)
अणु
	काष्ठा page *scs_page = vदो_स्मृति_to_page(s);

	mod_node_page_state(page_pgdat(scs_page), NR_KERNEL_SCS_KB,
			    account * (SCS_SIZE / SZ_1K));
पूर्ण

/* Matches NR_CACHED_STACKS क्रम VMAP_STACK */
#घोषणा NR_CACHED_SCS 2
अटल DEFINE_PER_CPU(व्योम *, scs_cache[NR_CACHED_SCS]);

अटल व्योम *__scs_alloc(पूर्णांक node)
अणु
	पूर्णांक i;
	व्योम *s;

	क्रम (i = 0; i < NR_CACHED_SCS; i++) अणु
		s = this_cpu_xchg(scs_cache[i], शून्य);
		अगर (s) अणु
			kasan_unpoison_vदो_स्मृति(s, SCS_SIZE);
			स_रखो(s, 0, SCS_SIZE);
			वापस s;
		पूर्ण
	पूर्ण

	वापस __vदो_स्मृति_node_range(SCS_SIZE, 1, VMALLOC_START, VMALLOC_END,
				    GFP_SCS, PAGE_KERNEL, 0, node,
				    __builtin_वापस_address(0));
पूर्ण

व्योम *scs_alloc(पूर्णांक node)
अणु
	व्योम *s;

	s = __scs_alloc(node);
	अगर (!s)
		वापस शून्य;

	*__scs_magic(s) = SCS_END_MAGIC;

	/*
	 * Poison the allocation to catch unपूर्णांकentional accesses to
	 * the shaकरोw stack when KASAN is enabled.
	 */
	kasan_poison_vदो_स्मृति(s, SCS_SIZE);
	__scs_account(s, 1);
	वापस s;
पूर्ण

व्योम scs_मुक्त(व्योम *s)
अणु
	पूर्णांक i;

	__scs_account(s, -1);

	/*
	 * We cannot sleep as this can be called in पूर्णांकerrupt context,
	 * so use this_cpu_cmpxchg to update the cache, and vमुक्त_atomic
	 * to मुक्त the stack.
	 */

	क्रम (i = 0; i < NR_CACHED_SCS; i++)
		अगर (this_cpu_cmpxchg(scs_cache[i], 0, s) == शून्य)
			वापस;

	vमुक्त_atomic(s);
पूर्ण

अटल पूर्णांक scs_cleanup(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;
	व्योम **cache = per_cpu_ptr(scs_cache, cpu);

	क्रम (i = 0; i < NR_CACHED_SCS; i++) अणु
		vमुक्त(cache[i]);
		cache[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __init scs_init(व्योम)
अणु
	cpuhp_setup_state(CPUHP_BP_PREPARE_DYN, "scs:scs_cache", शून्य,
			  scs_cleanup);
पूर्ण

पूर्णांक scs_prepare(काष्ठा task_काष्ठा *tsk, पूर्णांक node)
अणु
	व्योम *s = scs_alloc(node);

	अगर (!s)
		वापस -ENOMEM;

	task_scs(tsk) = task_scs_sp(tsk) = s;
	वापस 0;
पूर्ण

अटल व्योम scs_check_usage(काष्ठा task_काष्ठा *tsk)
अणु
	अटल अचिन्हित दीर्घ highest;

	अचिन्हित दीर्घ *p, prev, curr = highest, used = 0;

	अगर (!IS_ENABLED(CONFIG_DEBUG_STACK_USAGE))
		वापस;

	क्रम (p = task_scs(tsk); p < __scs_magic(tsk); ++p) अणु
		अगर (!READ_ONCE_NOCHECK(*p))
			अवरोध;
		used += माप(*p);
	पूर्ण

	जबतक (used > curr) अणु
		prev = cmpxchg_relaxed(&highest, curr, used);

		अगर (prev == curr) अणु
			pr_info("%s (%d): highest shadow stack usage: %lu bytes\n",
				tsk->comm, task_pid_nr(tsk), used);
			अवरोध;
		पूर्ण

		curr = prev;
	पूर्ण
पूर्ण

व्योम scs_release(काष्ठा task_काष्ठा *tsk)
अणु
	व्योम *s = task_scs(tsk);

	अगर (!s)
		वापस;

	WARN(task_scs_end_corrupted(tsk),
	     "corrupted shadow stack detected when freeing task\n");
	scs_check_usage(tsk);
	scs_मुक्त(s);
पूर्ण
