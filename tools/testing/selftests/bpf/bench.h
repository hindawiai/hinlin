<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#आशय once
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <linux/err.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <गणित.स>
#समावेश <समय.स>
#समावेश <sys/syscall.h>

काष्ठा cpu_set अणु
	bool *cpus;
	पूर्णांक cpus_len;
	पूर्णांक next_cpu;
पूर्ण;

काष्ठा env अणु
	अक्षर *bench_name;
	पूर्णांक duration_sec;
	पूर्णांक warmup_sec;
	bool verbose;
	bool list;
	bool affinity;
	पूर्णांक consumer_cnt;
	पूर्णांक producer_cnt;
	काष्ठा cpu_set prod_cpus;
	काष्ठा cpu_set cons_cpus;
पूर्ण;

काष्ठा bench_res अणु
	दीर्घ hits;
	दीर्घ drops;
पूर्ण;

काष्ठा bench अणु
	स्थिर अक्षर *name;
	व्योम (*validate)();
	व्योम (*setup)();
	व्योम *(*producer_thपढ़ो)(व्योम *ctx);
	व्योम *(*consumer_thपढ़ो)(व्योम *ctx);
	व्योम (*measure)(काष्ठा bench_res* res);
	व्योम (*report_progress)(पूर्णांक iter, काष्ठा bench_res* res, दीर्घ delta_ns);
	व्योम (*report_final)(काष्ठा bench_res res[], पूर्णांक res_cnt);
पूर्ण;

काष्ठा counter अणु
	दीर्घ value;
पूर्ण __attribute__((aligned(128)));

बाह्य काष्ठा env env;
बाह्य स्थिर काष्ठा bench *bench;

व्योम setup_libbpf();
व्योम hits_drops_report_progress(पूर्णांक iter, काष्ठा bench_res *res, दीर्घ delta_ns);
व्योम hits_drops_report_final(काष्ठा bench_res res[], पूर्णांक res_cnt);

अटल अंतरभूत __u64 get_समय_ns() अणु
	काष्ठा बारpec t;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &t);

	वापस (u64)t.tv_sec * 1000000000 + t.tv_nsec;
पूर्ण

अटल अंतरभूत व्योम atomic_inc(दीर्घ *value)
अणु
	(व्योम)__atomic_add_fetch(value, 1, __ATOMIC_RELAXED);
पूर्ण

अटल अंतरभूत व्योम atomic_add(दीर्घ *value, दीर्घ n)
अणु
	(व्योम)__atomic_add_fetch(value, n, __ATOMIC_RELAXED);
पूर्ण

अटल अंतरभूत दीर्घ atomic_swap(दीर्घ *value, दीर्घ n)
अणु
	वापस __atomic_exchange_n(value, n, __ATOMIC_RELAXED);
पूर्ण
