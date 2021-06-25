<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERCPU_H
#घोषणा PERCPU_H

#समावेश <मानकघोष.स>
#समावेश "bug_on.h"
#समावेश "preempt.h"

#घोषणा __percpu

/* Maximum size of any percpu data. */
#घोषणा PERCPU_OFFSET (4 * माप(दीर्घ))

/* Ignore alignment, as CBMC करोesn't care about false sharing. */
#घोषणा alloc_percpu(type) __alloc_percpu(माप(type), 1)

अटल अंतरभूत व्योम *__alloc_percpu(माप_प्रकार size, माप_प्रकार align)
अणु
	BUG();
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम मुक्त_percpu(व्योम *ptr)
अणु
	BUG();
पूर्ण

#घोषणा per_cpu_ptr(ptr, cpu) \
	((typeof(ptr)) ((अक्षर *) (ptr) + PERCPU_OFFSET * cpu))

#घोषणा __this_cpu_inc(pcp) __this_cpu_add(pcp, 1)
#घोषणा __this_cpu_dec(pcp) __this_cpu_sub(pcp, 1)
#घोषणा __this_cpu_sub(pcp, n) __this_cpu_add(pcp, -(typeof(pcp)) (n))

#घोषणा this_cpu_inc(pcp) this_cpu_add(pcp, 1)
#घोषणा this_cpu_dec(pcp) this_cpu_sub(pcp, 1)
#घोषणा this_cpu_sub(pcp, n) this_cpu_add(pcp, -(typeof(pcp)) (n))

/* Make CBMC use atomics to work around bug. */
#अगर_घोषित RUN
#घोषणा THIS_CPU_ADD_HELPER(ptr, x) (*(ptr) += (x))
#अन्यथा
/*
 * Split the atomic पूर्णांकo a पढ़ो and a ग_लिखो so that it has the least
 * possible ordering.
 */
#घोषणा THIS_CPU_ADD_HELPER(ptr, x) \
	करो अणु \
		typeof(ptr) this_cpu_add_helper_ptr = (ptr); \
		typeof(ptr) this_cpu_add_helper_x = (x); \
		typeof(*ptr) this_cpu_add_helper_temp; \
		__CPROVER_atomic_begin(); \
		this_cpu_add_helper_temp = *(this_cpu_add_helper_ptr); \
		__CPROVER_atomic_end(); \
		this_cpu_add_helper_temp += this_cpu_add_helper_x; \
		__CPROVER_atomic_begin(); \
		*(this_cpu_add_helper_ptr) = this_cpu_add_helper_temp; \
		__CPROVER_atomic_end(); \
	पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * For some reason CBMC needs an atomic operation even though this is percpu
 * data.
 */
#घोषणा __this_cpu_add(pcp, n) \
	करो अणु \
		BUG_ON(preemptible()); \
		THIS_CPU_ADD_HELPER(per_cpu_ptr(&(pcp), thपढ़ो_cpu_id), \
				    (typeof(pcp)) (n)); \
	पूर्ण जबतक (0)

#घोषणा this_cpu_add(pcp, n) \
	करो अणु \
		पूर्णांक this_cpu_add_impl_cpu = get_cpu(); \
		THIS_CPU_ADD_HELPER(per_cpu_ptr(&(pcp), this_cpu_add_impl_cpu), \
				    (typeof(pcp)) (n)); \
		put_cpu(); \
	पूर्ण जबतक (0)

/*
 * This will cause a compiler warning because of the cast from अक्षर[][] to
 * type*. This will cause a compile समय error अगर type is too big.
 */
#घोषणा DEFINE_PER_CPU(type, name) \
	अक्षर name[NR_CPUS][PERCPU_OFFSET]; \
	प्रकार अक्षर percpu_too_big_##name \
		[माप(type) > PERCPU_OFFSET ? -1 : 1]

#घोषणा क्रम_each_possible_cpu(cpu) \
	क्रम ((cpu) = 0; (cpu) < NR_CPUS; ++(cpu))

#पूर्ण_अगर
