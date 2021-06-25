<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <fcntl.h>
#समावेश "bench.h"
#समावेश "test_overhead.skel.h"

/* BPF triggering benchmarks */
अटल काष्ठा ctx अणु
	काष्ठा test_overhead *skel;
	काष्ठा counter hits;
	पूर्णांक fd;
पूर्ण ctx;

अटल व्योम validate()
अणु
	अगर (env.producer_cnt != 1) अणु
		ख_लिखो(मानक_त्रुटि, "benchmark doesn't support multi-producer!\n");
		निकास(1);
	पूर्ण
	अगर (env.consumer_cnt != 1) अणु
		ख_लिखो(मानक_त्रुटि, "benchmark doesn't support multi-consumer!\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम *producer(व्योम *input)
अणु
	अक्षर buf[] = "test_overhead";
	पूर्णांक err;

	जबतक (true) अणु
		err = ग_लिखो(ctx.fd, buf, माप(buf));
		अगर (err < 0) अणु
			ख_लिखो(मानक_त्रुटि, "write failed\n");
			निकास(1);
		पूर्ण
		atomic_inc(&ctx.hits.value);
	पूर्ण
पूर्ण

अटल व्योम measure(काष्ठा bench_res *res)
अणु
	res->hits = atomic_swap(&ctx.hits.value, 0);
पूर्ण

अटल व्योम setup_ctx()
अणु
	setup_libbpf();

	ctx.skel = test_overhead__खोलो_and_load();
	अगर (!ctx.skel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open skeleton\n");
		निकास(1);
	पूर्ण

	ctx.fd = खोलो("/proc/self/comm", O_WRONLY|O_TRUNC);
	अगर (ctx.fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open /proc/self/comm: %d\n", -त्रुटि_सं);
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

अटल व्योम setup_base()
अणु
	setup_ctx();
पूर्ण

अटल व्योम setup_kprobe()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.prog1);
पूर्ण

अटल व्योम setup_kretprobe()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.prog2);
पूर्ण

अटल व्योम setup_rawtp()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.prog3);
पूर्ण

अटल व्योम setup_fentry()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.prog4);
पूर्ण

अटल व्योम setup_fनिकास()
अणु
	setup_ctx();
	attach_bpf(ctx.skel->progs.prog5);
पूर्ण

अटल व्योम *consumer(व्योम *input)
अणु
	वापस शून्य;
पूर्ण

स्थिर काष्ठा bench bench_नाम_base = अणु
	.name = "rename-base",
	.validate = validate,
	.setup = setup_base,
	.producer_thपढ़ो = producer,
	.consumer_thपढ़ो = consumer,
	.measure = measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_नाम_kprobe = अणु
	.name = "rename-kprobe",
	.validate = validate,
	.setup = setup_kprobe,
	.producer_thपढ़ो = producer,
	.consumer_thपढ़ो = consumer,
	.measure = measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_नाम_kretprobe = अणु
	.name = "rename-kretprobe",
	.validate = validate,
	.setup = setup_kretprobe,
	.producer_thपढ़ो = producer,
	.consumer_thपढ़ो = consumer,
	.measure = measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_नाम_rawtp = अणु
	.name = "rename-rawtp",
	.validate = validate,
	.setup = setup_rawtp,
	.producer_thपढ़ो = producer,
	.consumer_thपढ़ो = consumer,
	.measure = measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_नाम_fentry = अणु
	.name = "rename-fentry",
	.validate = validate,
	.setup = setup_fentry,
	.producer_thपढ़ो = producer,
	.consumer_thपढ़ो = consumer,
	.measure = measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_नाम_fनिकास = अणु
	.name = "rename-fexit",
	.validate = validate,
	.setup = setup_fनिकास,
	.producer_thपढ़ो = producer,
	.consumer_thपढ़ो = consumer,
	.measure = measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;
