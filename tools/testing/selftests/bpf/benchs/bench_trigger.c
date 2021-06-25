<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bench.h"
#समावेश "trigger_bench.skel.h"

/* BPF triggering benchmarks */
अटल काष्ठा trigger_ctx अणु
	काष्ठा trigger_bench *skel;
पूर्ण ctx;

अटल काष्ठा counter base_hits;

अटल व्योम trigger_validate()
अणु
	अगर (env.consumer_cnt != 1) अणु
		ख_लिखो(मानक_त्रुटि, "benchmark doesn't support multi-consumer!\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम *trigger_base_producer(व्योम *input)
अणु
	जबतक (true) अणु
		(व्योम)syscall(__NR_getpgid);
		atomic_inc(&base_hits.value);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम trigger_base_measure(काष्ठा bench_res *res)
अणु
	res->hits = atomic_swap(&base_hits.value, 0);
पूर्ण

अटल व्योम *trigger_producer(व्योम *input)
अणु
	जबतक (true)
		(व्योम)syscall(__NR_getpgid);
	वापस शून्य;
पूर्ण

अटल व्योम trigger_measure(काष्ठा bench_res *res)
अणु
	res->hits = atomic_swap(&ctx.skel->bss->hits, 0);
पूर्ण

अटल व्योम setup_ctx()
अणु
	setup_libbpf();

	ctx.skel = trigger_bench__खोलो_and_load();
	अगर (!ctx.skel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open skeleton\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम attach_bpf(काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_link *link;

	link = bpf_program__attach(prog);
	अगर (IS_ERR(link)) अणु
		ख_लिखो(मानक_त्रुटि, "failed to attach program!\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम trigger_tp_setup()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.bench_trigger_tp);
पूर्ण

अटल व्योम trigger_rawtp_setup()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.bench_trigger_raw_tp);
पूर्ण

अटल व्योम trigger_kprobe_setup()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.bench_trigger_kprobe);
पूर्ण

अटल व्योम trigger_fentry_setup()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.bench_trigger_fentry);
पूर्ण

अटल व्योम trigger_fentry_sleep_setup()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.bench_trigger_fentry_sleep);
पूर्ण

अटल व्योम trigger_भ_शेषret_setup()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.bench_trigger_भ_शेषret);
पूर्ण

अटल व्योम *trigger_consumer(व्योम *input)
अणु
	वापस शून्य;
पूर्ण

स्थिर काष्ठा bench bench_trig_base = अणु
	.name = "trig-base",
	.validate = trigger_validate,
	.producer_thपढ़ो = trigger_base_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_base_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_trig_tp = अणु
	.name = "trig-tp",
	.validate = trigger_validate,
	.setup = trigger_tp_setup,
	.producer_thपढ़ो = trigger_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_trig_rawtp = अणु
	.name = "trig-rawtp",
	.validate = trigger_validate,
	.setup = trigger_rawtp_setup,
	.producer_thपढ़ो = trigger_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_trig_kprobe = अणु
	.name = "trig-kprobe",
	.validate = trigger_validate,
	.setup = trigger_kprobe_setup,
	.producer_thपढ़ो = trigger_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_trig_fentry = अणु
	.name = "trig-fentry",
	.validate = trigger_validate,
	.setup = trigger_fentry_setup,
	.producer_thपढ़ो = trigger_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_trig_fentry_sleep = अणु
	.name = "trig-fentry-sleep",
	.validate = trigger_validate,
	.setup = trigger_fentry_sleep_setup,
	.producer_thपढ़ो = trigger_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_trig_भ_शेषret = अणु
	.name = "trig-fmodret",
	.validate = trigger_validate,
	.setup = trigger_भ_शेषret_setup,
	.producer_thपढ़ो = trigger_producer,
	.consumer_thपढ़ो = trigger_consumer,
	.measure = trigger_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;
