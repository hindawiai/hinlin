<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <linux/membarrier.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <stdatomic.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <unistd.h>
#समावेश <poll.h>
#समावेश <sys/types.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>

अटल अंतरभूत pid_t rseq_gettid(व्योम)
अणु
	वापस syscall(__NR_gettid);
पूर्ण

#घोषणा NR_INJECT	9
अटल पूर्णांक loop_cnt[NR_INJECT + 1];

अटल पूर्णांक loop_cnt_1 यंत्र("asm_loop_cnt_1") __attribute__((used));
अटल पूर्णांक loop_cnt_2 यंत्र("asm_loop_cnt_2") __attribute__((used));
अटल पूर्णांक loop_cnt_3 यंत्र("asm_loop_cnt_3") __attribute__((used));
अटल पूर्णांक loop_cnt_4 यंत्र("asm_loop_cnt_4") __attribute__((used));
अटल पूर्णांक loop_cnt_5 यंत्र("asm_loop_cnt_5") __attribute__((used));
अटल पूर्णांक loop_cnt_6 यंत्र("asm_loop_cnt_6") __attribute__((used));

अटल पूर्णांक opt_modulo, verbose;

अटल पूर्णांक opt_yield, opt_संकेत, opt_sleep,
		opt_disable_rseq, opt_thपढ़ोs = 200,
		opt_disable_mod = 0, opt_test = 's', opt_mb = 0;

#अगर_अघोषित RSEQ_SKIP_FASTPATH
अटल दीर्घ दीर्घ opt_reps = 5000;
#अन्यथा
अटल दीर्घ दीर्घ opt_reps = 100;
#पूर्ण_अगर

अटल __thपढ़ो __attribute__((tls_model("initial-exec")))
अचिन्हित पूर्णांक संकेतs_delivered;

#अगर_अघोषित BENCHMARK

अटल __thपढ़ो __attribute__((tls_model("initial-exec"), unused))
अचिन्हित पूर्णांक yield_mod_cnt, nr_पात;

#घोषणा म_लिखो_verbose(fmt, ...)			\
	करो अणु						\
		अगर (verbose)				\
			म_लिखो(fmt, ## __VA_ARGS__);	\
	पूर्ण जबतक (0)

#अगर_घोषित __i386__

#घोषणा INJECT_ASM_REG	"eax"

#घोषणा RSEQ_INJECT_CLOBBER \
	, INJECT_ASM_REG

#घोषणा RSEQ_INJECT_ASM(n) \
	"mov asm_loop_cnt_" #n ", %%" INJECT_ASM_REG "\n\t" \
	"test %%" INJECT_ASM_REG ",%%" INJECT_ASM_REG "\n\t" \
	"jz 333f\n\t" \
	"222:\n\t" \
	"dec %%" INJECT_ASM_REG "\n\t" \
	"jnz 222b\n\t" \
	"333:\n\t"

#या_अगर defined(__x86_64__)

#घोषणा INJECT_ASM_REG_P	"rax"
#घोषणा INJECT_ASM_REG		"eax"

#घोषणा RSEQ_INJECT_CLOBBER \
	, INJECT_ASM_REG_P \
	, INJECT_ASM_REG

#घोषणा RSEQ_INJECT_ASM(n) \
	"lea asm_loop_cnt_" #n "(%%rip), %%" INJECT_ASM_REG_P "\n\t" \
	"mov (%%" INJECT_ASM_REG_P "), %%" INJECT_ASM_REG "\n\t" \
	"test %%" INJECT_ASM_REG ",%%" INJECT_ASM_REG "\n\t" \
	"jz 333f\n\t" \
	"222:\n\t" \
	"dec %%" INJECT_ASM_REG "\n\t" \
	"jnz 222b\n\t" \
	"333:\n\t"

#या_अगर defined(__s390__)

#घोषणा RSEQ_INJECT_INPUT \
	, [loop_cnt_1]"m"(loop_cnt[1]) \
	, [loop_cnt_2]"m"(loop_cnt[2]) \
	, [loop_cnt_3]"m"(loop_cnt[3]) \
	, [loop_cnt_4]"m"(loop_cnt[4]) \
	, [loop_cnt_5]"m"(loop_cnt[5]) \
	, [loop_cnt_6]"m"(loop_cnt[6])

#घोषणा INJECT_ASM_REG	"r12"

#घोषणा RSEQ_INJECT_CLOBBER \
	, INJECT_ASM_REG

#घोषणा RSEQ_INJECT_ASM(n) \
	"l %%" INJECT_ASM_REG ", %[loop_cnt_" #n "]\n\t" \
	"ltr %%" INJECT_ASM_REG ", %%" INJECT_ASM_REG "\n\t" \
	"je 333f\n\t" \
	"222:\n\t" \
	"ahi %%" INJECT_ASM_REG ", -1\n\t" \
	"jnz 222b\n\t" \
	"333:\n\t"

#या_अगर defined(__ARMEL__)

#घोषणा RSEQ_INJECT_INPUT \
	, [loop_cnt_1]"m"(loop_cnt[1]) \
	, [loop_cnt_2]"m"(loop_cnt[2]) \
	, [loop_cnt_3]"m"(loop_cnt[3]) \
	, [loop_cnt_4]"m"(loop_cnt[4]) \
	, [loop_cnt_5]"m"(loop_cnt[5]) \
	, [loop_cnt_6]"m"(loop_cnt[6])

#घोषणा INJECT_ASM_REG	"r4"

#घोषणा RSEQ_INJECT_CLOBBER \
	, INJECT_ASM_REG

#घोषणा RSEQ_INJECT_ASM(n) \
	"ldr " INJECT_ASM_REG ", %[loop_cnt_" #n "]\n\t" \
	"cmp " INJECT_ASM_REG ", #0\n\t" \
	"beq 333f\n\t" \
	"222:\n\t" \
	"subs " INJECT_ASM_REG ", #1\n\t" \
	"bne 222b\n\t" \
	"333:\n\t"

#या_अगर defined(__AARCH64EL__)

#घोषणा RSEQ_INJECT_INPUT \
	, [loop_cnt_1] "Qo" (loop_cnt[1]) \
	, [loop_cnt_2] "Qo" (loop_cnt[2]) \
	, [loop_cnt_3] "Qo" (loop_cnt[3]) \
	, [loop_cnt_4] "Qo" (loop_cnt[4]) \
	, [loop_cnt_5] "Qo" (loop_cnt[5]) \
	, [loop_cnt_6] "Qo" (loop_cnt[6])

#घोषणा INJECT_ASM_REG	RSEQ_ASM_TMP_REG32

#घोषणा RSEQ_INJECT_ASM(n) \
	"	ldr	" INJECT_ASM_REG ", %[loop_cnt_" #n "]\n"	\
	"	cbz	" INJECT_ASM_REG ", 333f\n"			\
	"222:\n"							\
	"	sub	" INJECT_ASM_REG ", " INJECT_ASM_REG ", #1\n"	\
	"	cbnz	" INJECT_ASM_REG ", 222b\n"			\
	"333:\n"

#या_अगर __PPC__

#घोषणा RSEQ_INJECT_INPUT \
	, [loop_cnt_1]"m"(loop_cnt[1]) \
	, [loop_cnt_2]"m"(loop_cnt[2]) \
	, [loop_cnt_3]"m"(loop_cnt[3]) \
	, [loop_cnt_4]"m"(loop_cnt[4]) \
	, [loop_cnt_5]"m"(loop_cnt[5]) \
	, [loop_cnt_6]"m"(loop_cnt[6])

#घोषणा INJECT_ASM_REG	"r18"

#घोषणा RSEQ_INJECT_CLOBBER \
	, INJECT_ASM_REG

#घोषणा RSEQ_INJECT_ASM(n) \
	"lwz %%" INJECT_ASM_REG ", %[loop_cnt_" #n "]\n\t" \
	"cmpwi %%" INJECT_ASM_REG ", 0\n\t" \
	"beq 333f\n\t" \
	"222:\n\t" \
	"subic. %%" INJECT_ASM_REG ", %%" INJECT_ASM_REG ", 1\n\t" \
	"bne 222b\n\t" \
	"333:\n\t"

#या_अगर defined(__mips__)

#घोषणा RSEQ_INJECT_INPUT \
	, [loop_cnt_1]"m"(loop_cnt[1]) \
	, [loop_cnt_2]"m"(loop_cnt[2]) \
	, [loop_cnt_3]"m"(loop_cnt[3]) \
	, [loop_cnt_4]"m"(loop_cnt[4]) \
	, [loop_cnt_5]"m"(loop_cnt[5]) \
	, [loop_cnt_6]"m"(loop_cnt[6])

#घोषणा INJECT_ASM_REG	"$5"

#घोषणा RSEQ_INJECT_CLOBBER \
	, INJECT_ASM_REG

#घोषणा RSEQ_INJECT_ASM(n) \
	"lw " INJECT_ASM_REG ", %[loop_cnt_" #n "]\n\t" \
	"beqz " INJECT_ASM_REG ", 333f\n\t" \
	"222:\n\t" \
	"addiu " INJECT_ASM_REG ", -1\n\t" \
	"bnez " INJECT_ASM_REG ", 222b\n\t" \
	"333:\n\t"

#अन्यथा
#त्रुटि unsupported target
#पूर्ण_अगर

#घोषणा RSEQ_INJECT_FAILED \
	nr_पात++;

#घोषणा RSEQ_INJECT_C(n) \
अणु \
	पूर्णांक loc_i, loc_nr_loops = loop_cnt[n]; \
	\
	क्रम (loc_i = 0; loc_i < loc_nr_loops; loc_i++) अणु \
		rseq_barrier(); \
	पूर्ण \
	अगर (loc_nr_loops == -1 && opt_modulo) अणु \
		अगर (yield_mod_cnt == opt_modulo - 1) अणु \
			अगर (opt_sleep > 0) \
				poll(शून्य, 0, opt_sleep); \
			अगर (opt_yield) \
				sched_yield(); \
			अगर (opt_संकेत) \
				उठाओ(SIGUSR1); \
			yield_mod_cnt = 0; \
		पूर्ण अन्यथा अणु \
			yield_mod_cnt++; \
		पूर्ण \
	पूर्ण \
पूर्ण

#अन्यथा

#घोषणा म_लिखो_verbose(fmt, ...)

#पूर्ण_अगर /* BENCHMARK */

#समावेश "rseq.h"

काष्ठा percpu_lock_entry अणु
	पूर्णांकptr_t v;
पूर्ण __attribute__((aligned(128)));

काष्ठा percpu_lock अणु
	काष्ठा percpu_lock_entry c[CPU_SETSIZE];
पूर्ण;

काष्ठा test_data_entry अणु
	पूर्णांकptr_t count;
पूर्ण __attribute__((aligned(128)));

काष्ठा spinlock_test_data अणु
	काष्ठा percpu_lock lock;
	काष्ठा test_data_entry c[CPU_SETSIZE];
पूर्ण;

काष्ठा spinlock_thपढ़ो_test_data अणु
	काष्ठा spinlock_test_data *data;
	दीर्घ दीर्घ reps;
	पूर्णांक reg;
पूर्ण;

काष्ठा inc_test_data अणु
	काष्ठा test_data_entry c[CPU_SETSIZE];
पूर्ण;

काष्ठा inc_thपढ़ो_test_data अणु
	काष्ठा inc_test_data *data;
	दीर्घ दीर्घ reps;
	पूर्णांक reg;
पूर्ण;

काष्ठा percpu_list_node अणु
	पूर्णांकptr_t data;
	काष्ठा percpu_list_node *next;
पूर्ण;

काष्ठा percpu_list_entry अणु
	काष्ठा percpu_list_node *head;
पूर्ण __attribute__((aligned(128)));

काष्ठा percpu_list अणु
	काष्ठा percpu_list_entry c[CPU_SETSIZE];
पूर्ण;

#घोषणा BUFFER_ITEM_PER_CPU	100

काष्ठा percpu_buffer_node अणु
	पूर्णांकptr_t data;
पूर्ण;

काष्ठा percpu_buffer_entry अणु
	पूर्णांकptr_t offset;
	पूर्णांकptr_t buflen;
	काष्ठा percpu_buffer_node **array;
पूर्ण __attribute__((aligned(128)));

काष्ठा percpu_buffer अणु
	काष्ठा percpu_buffer_entry c[CPU_SETSIZE];
पूर्ण;

#घोषणा MEMCPY_BUFFER_ITEM_PER_CPU	100

काष्ठा percpu_स_नकल_buffer_node अणु
	पूर्णांकptr_t data1;
	uपूर्णांक64_t data2;
पूर्ण;

काष्ठा percpu_स_नकल_buffer_entry अणु
	पूर्णांकptr_t offset;
	पूर्णांकptr_t buflen;
	काष्ठा percpu_स_नकल_buffer_node *array;
पूर्ण __attribute__((aligned(128)));

काष्ठा percpu_स_नकल_buffer अणु
	काष्ठा percpu_स_नकल_buffer_entry c[CPU_SETSIZE];
पूर्ण;

/* A simple percpu spinlock. Grअसल lock on current cpu. */
अटल पूर्णांक rseq_this_cpu_lock(काष्ठा percpu_lock *lock)
अणु
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		ret = rseq_cmpeqv_storev(&lock->c[cpu].v,
					 0, 1, cpu);
		अगर (rseq_likely(!ret))
			अवरोध;
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	/*
	 * Acquire semantic when taking lock after control dependency.
	 * Matches rseq_smp_store_release().
	 */
	rseq_smp_acquire__after_ctrl_dep();
	वापस cpu;
पूर्ण

अटल व्योम rseq_percpu_unlock(काष्ठा percpu_lock *lock, पूर्णांक cpu)
अणु
	निश्चित(lock->c[cpu].v == 1);
	/*
	 * Release lock, with release semantic. Matches
	 * rseq_smp_acquire__after_ctrl_dep().
	 */
	rseq_smp_store_release(&lock->c[cpu].v, 0);
पूर्ण

व्योम *test_percpu_spinlock_thपढ़ो(व्योम *arg)
अणु
	काष्ठा spinlock_thपढ़ो_test_data *thपढ़ो_data = arg;
	काष्ठा spinlock_test_data *data = thपढ़ो_data->data;
	दीर्घ दीर्घ i, reps;

	अगर (!opt_disable_rseq && thपढ़ो_data->reg &&
	    rseq_रेजिस्टर_current_thपढ़ो())
		पात();
	reps = thपढ़ो_data->reps;
	क्रम (i = 0; i < reps; i++) अणु
		पूर्णांक cpu = rseq_cpu_start();

		cpu = rseq_this_cpu_lock(&data->lock);
		data->c[cpu].count++;
		rseq_percpu_unlock(&data->lock, cpu);
#अगर_अघोषित BENCHMARK
		अगर (i != 0 && !(i % (reps / 10)))
			म_लिखो_verbose("tid %d: count %lld\n",
				       (पूर्णांक) rseq_gettid(), i);
#पूर्ण_अगर
	पूर्ण
	म_लिखो_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (पूर्णांक) rseq_gettid(), nr_पात, संकेतs_delivered);
	अगर (!opt_disable_rseq && thपढ़ो_data->reg &&
	    rseq_unरेजिस्टर_current_thपढ़ो())
		पात();
	वापस शून्य;
पूर्ण

/*
 * A simple test which implements a sharded counter using a per-cpu
 * lock.  Obviously real applications might prefer to simply use a
 * per-cpu increment; however, this is reasonable क्रम a test and the
 * lock can be extended to synchronize more complicated operations.
 */
व्योम test_percpu_spinlock(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = opt_thपढ़ोs;
	पूर्णांक i, ret;
	uपूर्णांक64_t sum;
	pthपढ़ो_t test_thपढ़ोs[num_thपढ़ोs];
	काष्ठा spinlock_test_data data;
	काष्ठा spinlock_thपढ़ो_test_data thपढ़ो_data[num_thपढ़ोs];

	स_रखो(&data, 0, माप(data));
	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		thपढ़ो_data[i].reps = opt_reps;
		अगर (opt_disable_mod <= 0 || (i % opt_disable_mod))
			thपढ़ो_data[i].reg = 1;
		अन्यथा
			thपढ़ो_data[i].reg = 0;
		thपढ़ो_data[i].data = &data;
		ret = pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
				     test_percpu_spinlock_thपढ़ो,
				     &thपढ़ो_data[i]);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_create");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(test_thपढ़ोs[i], शून्य);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_join");
			पात();
		पूर्ण
	पूर्ण

	sum = 0;
	क्रम (i = 0; i < CPU_SETSIZE; i++)
		sum += data.c[i].count;

	निश्चित(sum == (uपूर्णांक64_t)opt_reps * num_thपढ़ोs);
पूर्ण

व्योम *test_percpu_inc_thपढ़ो(व्योम *arg)
अणु
	काष्ठा inc_thपढ़ो_test_data *thपढ़ो_data = arg;
	काष्ठा inc_test_data *data = thपढ़ो_data->data;
	दीर्घ दीर्घ i, reps;

	अगर (!opt_disable_rseq && thपढ़ो_data->reg &&
	    rseq_रेजिस्टर_current_thपढ़ो())
		पात();
	reps = thपढ़ो_data->reps;
	क्रम (i = 0; i < reps; i++) अणु
		पूर्णांक ret;

		करो अणु
			पूर्णांक cpu;

			cpu = rseq_cpu_start();
			ret = rseq_addv(&data->c[cpu].count, 1, cpu);
		पूर्ण जबतक (rseq_unlikely(ret));
#अगर_अघोषित BENCHMARK
		अगर (i != 0 && !(i % (reps / 10)))
			म_लिखो_verbose("tid %d: count %lld\n",
				       (पूर्णांक) rseq_gettid(), i);
#पूर्ण_अगर
	पूर्ण
	म_लिखो_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (पूर्णांक) rseq_gettid(), nr_पात, संकेतs_delivered);
	अगर (!opt_disable_rseq && thपढ़ो_data->reg &&
	    rseq_unरेजिस्टर_current_thपढ़ो())
		पात();
	वापस शून्य;
पूर्ण

व्योम test_percpu_inc(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = opt_thपढ़ोs;
	पूर्णांक i, ret;
	uपूर्णांक64_t sum;
	pthपढ़ो_t test_thपढ़ोs[num_thपढ़ोs];
	काष्ठा inc_test_data data;
	काष्ठा inc_thपढ़ो_test_data thपढ़ो_data[num_thपढ़ोs];

	स_रखो(&data, 0, माप(data));
	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		thपढ़ो_data[i].reps = opt_reps;
		अगर (opt_disable_mod <= 0 || (i % opt_disable_mod))
			thपढ़ो_data[i].reg = 1;
		अन्यथा
			thपढ़ो_data[i].reg = 0;
		thपढ़ो_data[i].data = &data;
		ret = pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
				     test_percpu_inc_thपढ़ो,
				     &thपढ़ो_data[i]);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_create");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(test_thपढ़ोs[i], शून्य);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_join");
			पात();
		पूर्ण
	पूर्ण

	sum = 0;
	क्रम (i = 0; i < CPU_SETSIZE; i++)
		sum += data.c[i].count;

	निश्चित(sum == (uपूर्णांक64_t)opt_reps * num_thपढ़ोs);
पूर्ण

व्योम this_cpu_list_push(काष्ठा percpu_list *list,
			काष्ठा percpu_list_node *node,
			पूर्णांक *_cpu)
अणु
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांकptr_t *targetptr, newval, expect;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		/* Load list->c[cpu].head with single-copy atomicity. */
		expect = (पूर्णांकptr_t)RSEQ_READ_ONCE(list->c[cpu].head);
		newval = (पूर्णांकptr_t)node;
		targetptr = (पूर्णांकptr_t *)&list->c[cpu].head;
		node->next = (काष्ठा percpu_list_node *)expect;
		ret = rseq_cmpeqv_storev(targetptr, expect, newval, cpu);
		अगर (rseq_likely(!ret))
			अवरोध;
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
पूर्ण

/*
 * Unlike a traditional lock-less linked list; the availability of a
 * rseq primitive allows us to implement pop without concerns over
 * ABA-type races.
 */
काष्ठा percpu_list_node *this_cpu_list_pop(काष्ठा percpu_list *list,
					   पूर्णांक *_cpu)
अणु
	काष्ठा percpu_list_node *node = शून्य;
	पूर्णांक cpu;

	क्रम (;;) अणु
		काष्ठा percpu_list_node *head;
		पूर्णांकptr_t *targetptr, expectnot, *load;
		off_t offset;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		targetptr = (पूर्णांकptr_t *)&list->c[cpu].head;
		expectnot = (पूर्णांकptr_t)शून्य;
		offset = दुरत्व(काष्ठा percpu_list_node, next);
		load = (पूर्णांकptr_t *)&head;
		ret = rseq_cmpnev_storeoffp_load(targetptr, expectnot,
						   offset, load, cpu);
		अगर (rseq_likely(!ret)) अणु
			node = head;
			अवरोध;
		पूर्ण
		अगर (ret > 0)
			अवरोध;
		/* Retry अगर rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
	वापस node;
पूर्ण

/*
 * __percpu_list_pop is not safe against concurrent accesses. Should
 * only be used on lists that are not concurrently modअगरied.
 */
काष्ठा percpu_list_node *__percpu_list_pop(काष्ठा percpu_list *list, पूर्णांक cpu)
अणु
	काष्ठा percpu_list_node *node;

	node = list->c[cpu].head;
	अगर (!node)
		वापस शून्य;
	list->c[cpu].head = node->next;
	वापस node;
पूर्ण

व्योम *test_percpu_list_thपढ़ो(व्योम *arg)
अणु
	दीर्घ दीर्घ i, reps;
	काष्ठा percpu_list *list = (काष्ठा percpu_list *)arg;

	अगर (!opt_disable_rseq && rseq_रेजिस्टर_current_thपढ़ो())
		पात();

	reps = opt_reps;
	क्रम (i = 0; i < reps; i++) अणु
		काष्ठा percpu_list_node *node;

		node = this_cpu_list_pop(list, शून्य);
		अगर (opt_yield)
			sched_yield();  /* encourage shuffling */
		अगर (node)
			this_cpu_list_push(list, node, शून्य);
	पूर्ण

	म_लिखो_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (पूर्णांक) rseq_gettid(), nr_पात, संकेतs_delivered);
	अगर (!opt_disable_rseq && rseq_unरेजिस्टर_current_thपढ़ो())
		पात();

	वापस शून्य;
पूर्ण

/* Simultaneous modअगरication to a per-cpu linked list from many thपढ़ोs.  */
व्योम test_percpu_list(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = opt_thपढ़ोs;
	पूर्णांक i, j, ret;
	uपूर्णांक64_t sum = 0, expected_sum = 0;
	काष्ठा percpu_list list;
	pthपढ़ो_t test_thपढ़ोs[num_thपढ़ोs];
	cpu_set_t allowed_cpus;

	स_रखो(&list, 0, माप(list));

	/* Generate list entries क्रम every usable cpu. */
	sched_getaffinity(0, माप(allowed_cpus), &allowed_cpus);
	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;
		क्रम (j = 1; j <= 100; j++) अणु
			काष्ठा percpu_list_node *node;

			expected_sum += j;

			node = दो_स्मृति(माप(*node));
			निश्चित(node);
			node->data = j;
			node->next = list.c[i].head;
			list.c[i].head = node;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
				     test_percpu_list_thपढ़ो, &list);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_create");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(test_thपढ़ोs[i], शून्य);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_join");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		काष्ठा percpu_list_node *node;

		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;

		जबतक ((node = __percpu_list_pop(&list, i))) अणु
			sum += node->data;
			मुक्त(node);
		पूर्ण
	पूर्ण

	/*
	 * All entries should now be accounted क्रम (unless some बाह्यal
	 * actor is पूर्णांकerfering with our allowed affinity जबतक this
	 * test is running).
	 */
	निश्चित(sum == expected_sum);
पूर्ण

bool this_cpu_buffer_push(काष्ठा percpu_buffer *buffer,
			  काष्ठा percpu_buffer_node *node,
			  पूर्णांक *_cpu)
अणु
	bool result = false;
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांकptr_t *targetptr_spec, newval_spec;
		पूर्णांकptr_t *targetptr_final, newval_final;
		पूर्णांकptr_t offset;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		offset = RSEQ_READ_ONCE(buffer->c[cpu].offset);
		अगर (offset == buffer->c[cpu].buflen)
			अवरोध;
		newval_spec = (पूर्णांकptr_t)node;
		targetptr_spec = (पूर्णांकptr_t *)&buffer->c[cpu].array[offset];
		newval_final = offset + 1;
		targetptr_final = &buffer->c[cpu].offset;
		अगर (opt_mb)
			ret = rseq_cmpeqv_trystorev_storev_release(
				targetptr_final, offset, targetptr_spec,
				newval_spec, newval_final, cpu);
		अन्यथा
			ret = rseq_cmpeqv_trystorev_storev(targetptr_final,
				offset, targetptr_spec, newval_spec,
				newval_final, cpu);
		अगर (rseq_likely(!ret)) अणु
			result = true;
			अवरोध;
		पूर्ण
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
	वापस result;
पूर्ण

काष्ठा percpu_buffer_node *this_cpu_buffer_pop(काष्ठा percpu_buffer *buffer,
					       पूर्णांक *_cpu)
अणु
	काष्ठा percpu_buffer_node *head;
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांकptr_t *targetptr, newval;
		पूर्णांकptr_t offset;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		/* Load offset with single-copy atomicity. */
		offset = RSEQ_READ_ONCE(buffer->c[cpu].offset);
		अगर (offset == 0) अणु
			head = शून्य;
			अवरोध;
		पूर्ण
		head = RSEQ_READ_ONCE(buffer->c[cpu].array[offset - 1]);
		newval = offset - 1;
		targetptr = (पूर्णांकptr_t *)&buffer->c[cpu].offset;
		ret = rseq_cmpeqv_cmpeqv_storev(targetptr, offset,
			(पूर्णांकptr_t *)&buffer->c[cpu].array[offset - 1],
			(पूर्णांकptr_t)head, newval, cpu);
		अगर (rseq_likely(!ret))
			अवरोध;
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
	वापस head;
पूर्ण

/*
 * __percpu_buffer_pop is not safe against concurrent accesses. Should
 * only be used on buffers that are not concurrently modअगरied.
 */
काष्ठा percpu_buffer_node *__percpu_buffer_pop(काष्ठा percpu_buffer *buffer,
					       पूर्णांक cpu)
अणु
	काष्ठा percpu_buffer_node *head;
	पूर्णांकptr_t offset;

	offset = buffer->c[cpu].offset;
	अगर (offset == 0)
		वापस शून्य;
	head = buffer->c[cpu].array[offset - 1];
	buffer->c[cpu].offset = offset - 1;
	वापस head;
पूर्ण

व्योम *test_percpu_buffer_thपढ़ो(व्योम *arg)
अणु
	दीर्घ दीर्घ i, reps;
	काष्ठा percpu_buffer *buffer = (काष्ठा percpu_buffer *)arg;

	अगर (!opt_disable_rseq && rseq_रेजिस्टर_current_thपढ़ो())
		पात();

	reps = opt_reps;
	क्रम (i = 0; i < reps; i++) अणु
		काष्ठा percpu_buffer_node *node;

		node = this_cpu_buffer_pop(buffer, शून्य);
		अगर (opt_yield)
			sched_yield();  /* encourage shuffling */
		अगर (node) अणु
			अगर (!this_cpu_buffer_push(buffer, node, शून्य)) अणु
				/* Should increase buffer size. */
				पात();
			पूर्ण
		पूर्ण
	पूर्ण

	म_लिखो_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (पूर्णांक) rseq_gettid(), nr_पात, संकेतs_delivered);
	अगर (!opt_disable_rseq && rseq_unरेजिस्टर_current_thपढ़ो())
		पात();

	वापस शून्य;
पूर्ण

/* Simultaneous modअगरication to a per-cpu buffer from many thपढ़ोs.  */
व्योम test_percpu_buffer(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = opt_thपढ़ोs;
	पूर्णांक i, j, ret;
	uपूर्णांक64_t sum = 0, expected_sum = 0;
	काष्ठा percpu_buffer buffer;
	pthपढ़ो_t test_thपढ़ोs[num_thपढ़ोs];
	cpu_set_t allowed_cpus;

	स_रखो(&buffer, 0, माप(buffer));

	/* Generate list entries क्रम every usable cpu. */
	sched_getaffinity(0, माप(allowed_cpus), &allowed_cpus);
	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;
		/* Worse-हाल is every item in same CPU. */
		buffer.c[i].array =
			दो_स्मृति(माप(*buffer.c[i].array) * CPU_SETSIZE *
			       BUFFER_ITEM_PER_CPU);
		निश्चित(buffer.c[i].array);
		buffer.c[i].buflen = CPU_SETSIZE * BUFFER_ITEM_PER_CPU;
		क्रम (j = 1; j <= BUFFER_ITEM_PER_CPU; j++) अणु
			काष्ठा percpu_buffer_node *node;

			expected_sum += j;

			/*
			 * We could theoretically put the word-sized
			 * "data" directly in the buffer. However, we
			 * want to model objects that would not fit
			 * within a single word, so allocate an object
			 * क्रम each node.
			 */
			node = दो_स्मृति(माप(*node));
			निश्चित(node);
			node->data = j;
			buffer.c[i].array[j - 1] = node;
			buffer.c[i].offset++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
				     test_percpu_buffer_thपढ़ो, &buffer);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_create");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(test_thपढ़ोs[i], शून्य);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_join");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		काष्ठा percpu_buffer_node *node;

		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;

		जबतक ((node = __percpu_buffer_pop(&buffer, i))) अणु
			sum += node->data;
			मुक्त(node);
		पूर्ण
		मुक्त(buffer.c[i].array);
	पूर्ण

	/*
	 * All entries should now be accounted क्रम (unless some बाह्यal
	 * actor is पूर्णांकerfering with our allowed affinity जबतक this
	 * test is running).
	 */
	निश्चित(sum == expected_sum);
पूर्ण

bool this_cpu_स_नकल_buffer_push(काष्ठा percpu_स_नकल_buffer *buffer,
				 काष्ठा percpu_स_नकल_buffer_node item,
				 पूर्णांक *_cpu)
अणु
	bool result = false;
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांकptr_t *targetptr_final, newval_final, offset;
		अक्षर *destptr, *srcptr;
		माप_प्रकार copylen;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		/* Load offset with single-copy atomicity. */
		offset = RSEQ_READ_ONCE(buffer->c[cpu].offset);
		अगर (offset == buffer->c[cpu].buflen)
			अवरोध;
		destptr = (अक्षर *)&buffer->c[cpu].array[offset];
		srcptr = (अक्षर *)&item;
		/* copylen must be <= 4kB. */
		copylen = माप(item);
		newval_final = offset + 1;
		targetptr_final = &buffer->c[cpu].offset;
		अगर (opt_mb)
			ret = rseq_cmpeqv_tryस_नकल_storev_release(
				targetptr_final, offset,
				destptr, srcptr, copylen,
				newval_final, cpu);
		अन्यथा
			ret = rseq_cmpeqv_tryस_नकल_storev(targetptr_final,
				offset, destptr, srcptr, copylen,
				newval_final, cpu);
		अगर (rseq_likely(!ret)) अणु
			result = true;
			अवरोध;
		पूर्ण
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
	वापस result;
पूर्ण

bool this_cpu_स_नकल_buffer_pop(काष्ठा percpu_स_नकल_buffer *buffer,
				काष्ठा percpu_स_नकल_buffer_node *item,
				पूर्णांक *_cpu)
अणु
	bool result = false;
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांकptr_t *targetptr_final, newval_final, offset;
		अक्षर *destptr, *srcptr;
		माप_प्रकार copylen;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		/* Load offset with single-copy atomicity. */
		offset = RSEQ_READ_ONCE(buffer->c[cpu].offset);
		अगर (offset == 0)
			अवरोध;
		destptr = (अक्षर *)item;
		srcptr = (अक्षर *)&buffer->c[cpu].array[offset - 1];
		/* copylen must be <= 4kB. */
		copylen = माप(*item);
		newval_final = offset - 1;
		targetptr_final = &buffer->c[cpu].offset;
		ret = rseq_cmpeqv_tryस_नकल_storev(targetptr_final,
			offset, destptr, srcptr, copylen,
			newval_final, cpu);
		अगर (rseq_likely(!ret)) अणु
			result = true;
			अवरोध;
		पूर्ण
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
	वापस result;
पूर्ण

/*
 * __percpu_स_नकल_buffer_pop is not safe against concurrent accesses. Should
 * only be used on buffers that are not concurrently modअगरied.
 */
bool __percpu_स_नकल_buffer_pop(काष्ठा percpu_स_नकल_buffer *buffer,
				काष्ठा percpu_स_नकल_buffer_node *item,
				पूर्णांक cpu)
अणु
	पूर्णांकptr_t offset;

	offset = buffer->c[cpu].offset;
	अगर (offset == 0)
		वापस false;
	स_नकल(item, &buffer->c[cpu].array[offset - 1], माप(*item));
	buffer->c[cpu].offset = offset - 1;
	वापस true;
पूर्ण

व्योम *test_percpu_स_नकल_buffer_thपढ़ो(व्योम *arg)
अणु
	दीर्घ दीर्घ i, reps;
	काष्ठा percpu_स_नकल_buffer *buffer = (काष्ठा percpu_स_नकल_buffer *)arg;

	अगर (!opt_disable_rseq && rseq_रेजिस्टर_current_thपढ़ो())
		पात();

	reps = opt_reps;
	क्रम (i = 0; i < reps; i++) अणु
		काष्ठा percpu_स_नकल_buffer_node item;
		bool result;

		result = this_cpu_स_नकल_buffer_pop(buffer, &item, शून्य);
		अगर (opt_yield)
			sched_yield();  /* encourage shuffling */
		अगर (result) अणु
			अगर (!this_cpu_स_नकल_buffer_push(buffer, item, शून्य)) अणु
				/* Should increase buffer size. */
				पात();
			पूर्ण
		पूर्ण
	पूर्ण

	म_लिखो_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (पूर्णांक) rseq_gettid(), nr_पात, संकेतs_delivered);
	अगर (!opt_disable_rseq && rseq_unरेजिस्टर_current_thपढ़ो())
		पात();

	वापस शून्य;
पूर्ण

/* Simultaneous modअगरication to a per-cpu buffer from many thपढ़ोs.  */
व्योम test_percpu_स_नकल_buffer(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = opt_thपढ़ोs;
	पूर्णांक i, j, ret;
	uपूर्णांक64_t sum = 0, expected_sum = 0;
	काष्ठा percpu_स_नकल_buffer buffer;
	pthपढ़ो_t test_thपढ़ोs[num_thपढ़ोs];
	cpu_set_t allowed_cpus;

	स_रखो(&buffer, 0, माप(buffer));

	/* Generate list entries क्रम every usable cpu. */
	sched_getaffinity(0, माप(allowed_cpus), &allowed_cpus);
	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;
		/* Worse-हाल is every item in same CPU. */
		buffer.c[i].array =
			दो_स्मृति(माप(*buffer.c[i].array) * CPU_SETSIZE *
			       MEMCPY_BUFFER_ITEM_PER_CPU);
		निश्चित(buffer.c[i].array);
		buffer.c[i].buflen = CPU_SETSIZE * MEMCPY_BUFFER_ITEM_PER_CPU;
		क्रम (j = 1; j <= MEMCPY_BUFFER_ITEM_PER_CPU; j++) अणु
			expected_sum += 2 * j + 1;

			/*
			 * We could theoretically put the word-sized
			 * "data" directly in the buffer. However, we
			 * want to model objects that would not fit
			 * within a single word, so allocate an object
			 * क्रम each node.
			 */
			buffer.c[i].array[j - 1].data1 = j;
			buffer.c[i].array[j - 1].data2 = j + 1;
			buffer.c[i].offset++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
				     test_percpu_स_नकल_buffer_thपढ़ो,
				     &buffer);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_create");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(test_thपढ़ोs[i], शून्य);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_join");
			पात();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		काष्ठा percpu_स_नकल_buffer_node item;

		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;

		जबतक (__percpu_स_नकल_buffer_pop(&buffer, &item, i)) अणु
			sum += item.data1;
			sum += item.data2;
		पूर्ण
		मुक्त(buffer.c[i].array);
	पूर्ण

	/*
	 * All entries should now be accounted क्रम (unless some बाह्यal
	 * actor is पूर्णांकerfering with our allowed affinity जबतक this
	 * test is running).
	 */
	निश्चित(sum == expected_sum);
पूर्ण

अटल व्योम test_संकेत_पूर्णांकerrupt_handler(पूर्णांक signo)
अणु
	संकेतs_delivered++;
पूर्ण

अटल पूर्णांक set_संकेत_handler(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा sigaction sa;
	sigset_t sigset;

	ret = sigemptyset(&sigset);
	अगर (ret < 0) अणु
		लिखो_त्रुटि("sigemptyset");
		वापस ret;
	पूर्ण

	sa.sa_handler = test_संकेत_पूर्णांकerrupt_handler;
	sa.sa_mask = sigset;
	sa.sa_flags = 0;
	ret = sigaction(SIGUSR1, &sa, शून्य);
	अगर (ret < 0) अणु
		लिखो_त्रुटि("sigaction");
		वापस ret;
	पूर्ण

	म_लिखो_verbose("Signal handler set for SIGUSR1\n");

	वापस ret;
पूर्ण

/* Test MEMBARRIER_CMD_PRIVATE_RESTART_RSEQ_ON_CPU membarrier command. */
#अगर_घोषित RSEQ_ARCH_HAS_OFFSET_DEREF_ADDV
काष्ठा test_membarrier_thपढ़ो_args अणु
	पूर्णांक stop;
	पूर्णांकptr_t percpu_list_ptr;
पूर्ण;

/* Worker thपढ़ोs modअगरy data in their "active" percpu lists. */
व्योम *test_membarrier_worker_thपढ़ो(व्योम *arg)
अणु
	काष्ठा test_membarrier_thपढ़ो_args *args =
		(काष्ठा test_membarrier_thपढ़ो_args *)arg;
	स्थिर पूर्णांक iters = opt_reps;
	पूर्णांक i;

	अगर (rseq_रेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण

	/* Wait क्रम initialization. */
	जबतक (!atomic_load(&args->percpu_list_ptr)) अणुपूर्ण

	क्रम (i = 0; i < iters; ++i) अणु
		पूर्णांक ret;

		करो अणु
			पूर्णांक cpu = rseq_cpu_start();

			ret = rseq_offset_deref_addv(&args->percpu_list_ptr,
				माप(काष्ठा percpu_list_entry) * cpu, 1, cpu);
		पूर्ण जबतक (rseq_unlikely(ret));
	पूर्ण

	अगर (rseq_unरेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम test_membarrier_init_percpu_list(काष्ठा percpu_list *list)
अणु
	पूर्णांक i;

	स_रखो(list, 0, माप(*list));
	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		काष्ठा percpu_list_node *node;

		node = दो_स्मृति(माप(*node));
		निश्चित(node);
		node->data = 0;
		node->next = शून्य;
		list->c[i].head = node;
	पूर्ण
पूर्ण

व्योम test_membarrier_मुक्त_percpu_list(काष्ठा percpu_list *list)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CPU_SETSIZE; i++)
		मुक्त(list->c[i].head);
पूर्ण

अटल पूर्णांक sys_membarrier(पूर्णांक cmd, पूर्णांक flags, पूर्णांक cpu_id)
अणु
	वापस syscall(__NR_membarrier, cmd, flags, cpu_id);
पूर्ण

/*
 * The manager thपढ़ो swaps per-cpu lists that worker thपढ़ोs see,
 * and validates that there are no unexpected modअगरications.
 */
व्योम *test_membarrier_manager_thपढ़ो(व्योम *arg)
अणु
	काष्ठा test_membarrier_thपढ़ो_args *args =
		(काष्ठा test_membarrier_thपढ़ो_args *)arg;
	काष्ठा percpu_list list_a, list_b;
	पूर्णांकptr_t expect_a = 0, expect_b = 0;
	पूर्णांक cpu_a = 0, cpu_b = 0;

	अगर (rseq_रेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण

	/* Init lists. */
	test_membarrier_init_percpu_list(&list_a);
	test_membarrier_init_percpu_list(&list_b);

	atomic_store(&args->percpu_list_ptr, (पूर्णांकptr_t)&list_a);

	जबतक (!atomic_load(&args->stop)) अणु
		/* list_a is "active". */
		cpu_a = अक्रम() % CPU_SETSIZE;
		/*
		 * As list_b is "inactive", we should never see changes
		 * to list_b.
		 */
		अगर (expect_b != atomic_load(&list_b.c[cpu_b].head->data)) अणु
			ख_लिखो(मानक_त्रुटि, "Membarrier test failed\n");
			पात();
		पूर्ण

		/* Make list_b "active". */
		atomic_store(&args->percpu_list_ptr, (पूर्णांकptr_t)&list_b);
		अगर (sys_membarrier(MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ,
					MEMBARRIER_CMD_FLAG_CPU, cpu_a) &&
				त्रुटि_सं != ENXIO /* missing CPU */) अणु
			लिखो_त्रुटि("sys_membarrier");
			पात();
		पूर्ण
		/*
		 * Cpu A should now only modअगरy list_b, so the values
		 * in list_a should be stable.
		 */
		expect_a = atomic_load(&list_a.c[cpu_a].head->data);

		cpu_b = अक्रम() % CPU_SETSIZE;
		/*
		 * As list_a is "inactive", we should never see changes
		 * to list_a.
		 */
		अगर (expect_a != atomic_load(&list_a.c[cpu_a].head->data)) अणु
			ख_लिखो(मानक_त्रुटि, "Membarrier test failed\n");
			पात();
		पूर्ण

		/* Make list_a "active". */
		atomic_store(&args->percpu_list_ptr, (पूर्णांकptr_t)&list_a);
		अगर (sys_membarrier(MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ,
					MEMBARRIER_CMD_FLAG_CPU, cpu_b) &&
				त्रुटि_सं != ENXIO /* missing CPU*/) अणु
			लिखो_त्रुटि("sys_membarrier");
			पात();
		पूर्ण
		/* Remember a value from list_b. */
		expect_b = atomic_load(&list_b.c[cpu_b].head->data);
	पूर्ण

	test_membarrier_मुक्त_percpu_list(&list_a);
	test_membarrier_मुक्त_percpu_list(&list_b);

	अगर (rseq_unरेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम test_membarrier(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = opt_thपढ़ोs;
	काष्ठा test_membarrier_thपढ़ो_args thपढ़ो_args;
	pthपढ़ो_t worker_thपढ़ोs[num_thपढ़ोs];
	pthपढ़ो_t manager_thपढ़ो;
	पूर्णांक i, ret;

	अगर (sys_membarrier(MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_RSEQ, 0, 0)) अणु
		लिखो_त्रुटि("sys_membarrier");
		पात();
	पूर्ण

	thपढ़ो_args.stop = 0;
	thपढ़ो_args.percpu_list_ptr = 0;
	ret = pthपढ़ो_create(&manager_thपढ़ो, शून्य,
			test_membarrier_manager_thपढ़ो, &thपढ़ो_args);
	अगर (ret) अणु
		त्रुटि_सं = ret;
		लिखो_त्रुटि("pthread_create");
		पात();
	पूर्ण

	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_create(&worker_thपढ़ोs[i], शून्य,
				test_membarrier_worker_thपढ़ो, &thपढ़ो_args);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_create");
			पात();
		पूर्ण
	पूर्ण


	क्रम (i = 0; i < num_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(worker_thपढ़ोs[i], शून्य);
		अगर (ret) अणु
			त्रुटि_सं = ret;
			लिखो_त्रुटि("pthread_join");
			पात();
		पूर्ण
	पूर्ण

	atomic_store(&thपढ़ो_args.stop, 1);
	ret = pthपढ़ो_join(manager_thपढ़ो, शून्य);
	अगर (ret) अणु
		त्रुटि_सं = ret;
		लिखो_त्रुटि("pthread_join");
		पात();
	पूर्ण
पूर्ण
#अन्यथा /* RSEQ_ARCH_HAS_OFFSET_DEREF_ADDV */
व्योम test_membarrier(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "rseq_offset_deref_addv is not implemented on this architecture. "
			"Skipping membarrier test.\n");
पूर्ण
#पूर्ण_अगर

अटल व्योम show_usage(पूर्णांक argc, अक्षर **argv)
अणु
	म_लिखो("Usage : %s <OPTIONS>\n",
		argv[0]);
	म_लिखो("OPTIONS:\n");
	म_लिखो("	[-1 loops] Number of loops for delay injection 1\n");
	म_लिखो("	[-2 loops] Number of loops for delay injection 2\n");
	म_लिखो("	[-3 loops] Number of loops for delay injection 3\n");
	म_लिखो("	[-4 loops] Number of loops for delay injection 4\n");
	म_लिखो("	[-5 loops] Number of loops for delay injection 5\n");
	म_लिखो("	[-6 loops] Number of loops for delay injection 6\n");
	म_लिखो("	[-7 loops] Number of loops for delay injection 7 (-1 to enable -m)\n");
	म_लिखो("	[-8 loops] Number of loops for delay injection 8 (-1 to enable -m)\n");
	म_लिखो("	[-9 loops] Number of loops for delay injection 9 (-1 to enable -m)\n");
	म_लिखो("	[-m N] Yield/sleep/kill every modulo N (default 0: disabled) (>= 0)\n");
	म_लिखो("	[-y] Yield\n");
	म_लिखो("	[-k] Kill thread with signal\n");
	म_लिखो("	[-s S] S: =0: disabled (default), >0: sleep time (ms)\n");
	म_लिखो("	[-t N] Number of threads (default 200)\n");
	म_लिखो("	[-r N] Number of repetitions per thread (default 5000)\n");
	म_लिखो("	[-d] Disable rseq system call (no initialization)\n");
	म_लिखो("	[-D M] Disable rseq for each M threads\n");
	म_लिखो("	[-T test] Choose test: (s)pinlock, (l)ist, (b)uffer, (m)emcpy, (i)ncrement, membarrie(r)\n");
	म_लिखो("	[-M] Push into buffer and memcpy buffer with memory barriers.\n");
	म_लिखो("	[-v] Verbose output.\n");
	म_लिखो("	[-h] Show this help.\n");
	म_लिखो("\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < argc; i++) अणु
		अगर (argv[i][0] != '-')
			जारी;
		चयन (argv[i][1]) अणु
		हाल '1':
		हाल '2':
		हाल '3':
		हाल '4':
		हाल '5':
		हाल '6':
		हाल '7':
		हाल '8':
		हाल '9':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			loop_cnt[argv[i][1] - '0'] = म_से_द(argv[i + 1]);
			i++;
			अवरोध;
		हाल 'm':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			opt_modulo = म_से_द(argv[i + 1]);
			अगर (opt_modulo < 0) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			i++;
			अवरोध;
		हाल 's':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			opt_sleep = म_से_द(argv[i + 1]);
			अगर (opt_sleep < 0) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			i++;
			अवरोध;
		हाल 'y':
			opt_yield = 1;
			अवरोध;
		हाल 'k':
			opt_संकेत = 1;
			अवरोध;
		हाल 'd':
			opt_disable_rseq = 1;
			अवरोध;
		हाल 'D':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			opt_disable_mod = म_से_द(argv[i + 1]);
			अगर (opt_disable_mod < 0) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			i++;
			अवरोध;
		हाल 't':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			opt_thपढ़ोs = म_से_द(argv[i + 1]);
			अगर (opt_thपढ़ोs < 0) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			i++;
			अवरोध;
		हाल 'r':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			opt_reps = म_से_दl(argv[i + 1]);
			अगर (opt_reps < 0) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			i++;
			अवरोध;
		हाल 'h':
			show_usage(argc, argv);
			जाओ end;
		हाल 'T':
			अगर (argc < i + 2) अणु
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			opt_test = *argv[i + 1];
			चयन (opt_test) अणु
			हाल 's':
			हाल 'l':
			हाल 'i':
			हाल 'b':
			हाल 'm':
			हाल 'r':
				अवरोध;
			शेष:
				show_usage(argc, argv);
				जाओ error;
			पूर्ण
			i++;
			अवरोध;
		हाल 'v':
			verbose = 1;
			अवरोध;
		हाल 'M':
			opt_mb = 1;
			अवरोध;
		शेष:
			show_usage(argc, argv);
			जाओ error;
		पूर्ण
	पूर्ण

	loop_cnt_1 = loop_cnt[1];
	loop_cnt_2 = loop_cnt[2];
	loop_cnt_3 = loop_cnt[3];
	loop_cnt_4 = loop_cnt[4];
	loop_cnt_5 = loop_cnt[5];
	loop_cnt_6 = loop_cnt[6];

	अगर (set_संकेत_handler())
		जाओ error;

	अगर (!opt_disable_rseq && rseq_रेजिस्टर_current_thपढ़ो())
		जाओ error;
	चयन (opt_test) अणु
	हाल 's':
		म_लिखो_verbose("spinlock\n");
		test_percpu_spinlock();
		अवरोध;
	हाल 'l':
		म_लिखो_verbose("linked list\n");
		test_percpu_list();
		अवरोध;
	हाल 'b':
		म_लिखो_verbose("buffer\n");
		test_percpu_buffer();
		अवरोध;
	हाल 'm':
		म_लिखो_verbose("memcpy buffer\n");
		test_percpu_स_नकल_buffer();
		अवरोध;
	हाल 'i':
		म_लिखो_verbose("counter increment\n");
		test_percpu_inc();
		अवरोध;
	हाल 'r':
		म_लिखो_verbose("membarrier\n");
		test_membarrier();
		अवरोध;
	पूर्ण
	अगर (!opt_disable_rseq && rseq_unरेजिस्टर_current_thपढ़ो())
		पात();
end:
	वापस 0;

error:
	वापस -1;
पूर्ण
