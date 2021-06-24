<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BENCH_H
#घोषणा BENCH_H

#समावेश <sys/समय.स>

बाह्य काष्ठा समयval bench__start, bench__end, bench__runसमय;

/*
 * The madvise transparent hugepage स्थिरants were added in glibc
 * 2.13. For compatibility with older versions of glibc, define these
 * tokens अगर they are not alपढ़ोy defined.
 *
 * PA-RISC uses dअगरferent madvise values from other architectures and
 * needs to be special-हालd.
 */
#अगर_घोषित __hppa__
# अगरndef MADV_HUGEPAGE
#  define MADV_HUGEPAGE		67
# endअगर
# अगरndef MADV_NOHUGEPAGE
#  define MADV_NOHUGEPAGE	68
# endअगर
#अन्यथा
# अगरndef MADV_HUGEPAGE
#  define MADV_HUGEPAGE		14
# endअगर
# अगरndef MADV_NOHUGEPAGE
#  define MADV_NOHUGEPAGE	15
# endअगर
#पूर्ण_अगर

पूर्णांक bench_numa(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_sched_messaging(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_sched_pipe(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_syscall_basic(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_mem_स_नकल(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_mem_स_रखो(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_mem_find_bit(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_futex_hash(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_futex_wake(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_futex_wake_parallel(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_futex_requeue(पूर्णांक argc, स्थिर अक्षर **argv);
/* pi futexes */
पूर्णांक bench_futex_lock_pi(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_epoll_रुको(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_epoll_ctl(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_synthesize(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_kallsyms_parse(पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक bench_inject_build_id(पूर्णांक argc, स्थिर अक्षर **argv);

#घोषणा BENCH_FORMAT_DEFAULT_STR	"default"
#घोषणा BENCH_FORMAT_DEFAULT		0
#घोषणा BENCH_FORMAT_SIMPLE_STR		"simple"
#घोषणा BENCH_FORMAT_SIMPLE		1

#घोषणा BENCH_FORMAT_UNKNOWN		-1

बाह्य पूर्णांक bench_क्रमmat;
बाह्य अचिन्हित पूर्णांक bench_repeat;

#अगर_अघोषित HAVE_PTHREAD_ATTR_SETAFFINITY_NP
#समावेश <pthपढ़ो.h>
#समावेश <linux/compiler.h>
अटल अंतरभूत पूर्णांक pthपढ़ो_attr_setaffinity_np(pthपढ़ो_attr_t *attr __maybe_unused,
					      माप_प्रकार cpusetsize __maybe_unused,
					      cpu_set_t *cpuset __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
