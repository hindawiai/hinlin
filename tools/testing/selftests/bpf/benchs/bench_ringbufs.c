<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <यंत्र/barrier.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ring_buffer.h>
#समावेश <sys/epoll.h>
#समावेश <sys/mman.h>
#समावेश <argp.h>
#समावेश <मानककोष.स>
#समावेश "bench.h"
#समावेश "ringbuf_bench.skel.h"
#समावेश "perfbuf_bench.skel.h"

अटल काष्ठा अणु
	bool back2back;
	पूर्णांक batch_cnt;
	bool sampled;
	पूर्णांक sample_rate;
	पूर्णांक ringbuf_sz; /* per-ringbuf, in bytes */
	bool ringbuf_use_output; /* use slower output API */
	पूर्णांक perfbuf_sz; /* per-CPU size, in pages */
पूर्ण args = अणु
	.back2back = false,
	.batch_cnt = 500,
	.sampled = false,
	.sample_rate = 500,
	.ringbuf_sz = 512 * 1024,
	.ringbuf_use_output = false,
	.perfbuf_sz = 128,
पूर्ण;

क्रमागत अणु
	ARG_RB_BACK2BACK = 2000,
	ARG_RB_USE_OUTPUT = 2001,
	ARG_RB_BATCH_CNT = 2002,
	ARG_RB_SAMPLED = 2003,
	ARG_RB_SAMPLE_RATE = 2004,
पूर्ण;

अटल स्थिर काष्ठा argp_option opts[] = अणु
	अणु "rb-b2b", ARG_RB_BACK2BACK, शून्य, 0, "Back-to-back mode"पूर्ण,
	अणु "rb-use-output", ARG_RB_USE_OUTPUT, शून्य, 0, "Use bpf_ringbuf_output() instead of bpf_ringbuf_reserve()"पूर्ण,
	अणु "rb-batch-cnt", ARG_RB_BATCH_CNT, "CNT", 0, "Set BPF-side record batch count"पूर्ण,
	अणु "rb-sampled", ARG_RB_SAMPLED, शून्य, 0, "Notification sampling"पूर्ण,
	अणु "rb-sample-rate", ARG_RB_SAMPLE_RATE, "RATE", 0, "Notification sample rate"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल error_t parse_arg(पूर्णांक key, अक्षर *arg, काष्ठा argp_state *state)
अणु
	चयन (key) अणु
	हाल ARG_RB_BACK2BACK:
		args.back2back = true;
		अवरोध;
	हाल ARG_RB_USE_OUTPUT:
		args.ringbuf_use_output = true;
		अवरोध;
	हाल ARG_RB_BATCH_CNT:
		args.batch_cnt = म_से_दीर्घ(arg, शून्य, 10);
		अगर (args.batch_cnt < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid batch count.");
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल ARG_RB_SAMPLED:
		args.sampled = true;
		अवरोध;
	हाल ARG_RB_SAMPLE_RATE:
		args.sample_rate = म_से_दीर्घ(arg, शून्य, 10);
		अगर (args.sample_rate < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid perfbuf sample rate.");
			argp_usage(state);
		पूर्ण
		अवरोध;
	शेष:
		वापस ARGP_ERR_UNKNOWN;
	पूर्ण
	वापस 0;
पूर्ण

/* exported पूर्णांकo benchmark runner */
स्थिर काष्ठा argp bench_ringbufs_argp = अणु
	.options = opts,
	.parser = parse_arg,
पूर्ण;

/* RINGBUF-LIBBPF benchmark */

अटल काष्ठा counter buf_hits;

अटल अंतरभूत व्योम bufs_trigger_batch()
अणु
	(व्योम)syscall(__NR_getpgid);
पूर्ण

अटल व्योम bufs_validate()
अणु
	अगर (env.consumer_cnt != 1) अणु
		ख_लिखो(मानक_त्रुटि, "rb-libbpf benchmark doesn't support multi-consumer!\n");
		निकास(1);
	पूर्ण

	अगर (args.back2back && env.producer_cnt > 1) अणु
		ख_लिखो(मानक_त्रुटि, "back-to-back mode makes sense only for single-producer case!\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम *bufs_sample_producer(व्योम *input)
अणु
	अगर (args.back2back) अणु
		/* initial batch to get everything started */
		bufs_trigger_batch();
		वापस शून्य;
	पूर्ण

	जबतक (true)
		bufs_trigger_batch();
	वापस शून्य;
पूर्ण

अटल काष्ठा ringbuf_libbpf_ctx अणु
	काष्ठा ringbuf_bench *skel;
	काष्ठा ring_buffer *ringbuf;
पूर्ण ringbuf_libbpf_ctx;

अटल व्योम ringbuf_libbpf_measure(काष्ठा bench_res *res)
अणु
	काष्ठा ringbuf_libbpf_ctx *ctx = &ringbuf_libbpf_ctx;

	res->hits = atomic_swap(&buf_hits.value, 0);
	res->drops = atomic_swap(&ctx->skel->bss->dropped, 0);
पूर्ण

अटल काष्ठा ringbuf_bench *ringbuf_setup_skeleton()
अणु
	काष्ठा ringbuf_bench *skel;

	setup_libbpf();

	skel = ringbuf_bench__खोलो();
	अगर (!skel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open skeleton\n");
		निकास(1);
	पूर्ण

	skel->rodata->batch_cnt = args.batch_cnt;
	skel->rodata->use_output = args.ringbuf_use_output ? 1 : 0;

	अगर (args.sampled)
		/* record data + header take 16 bytes */
		skel->rodata->wakeup_data_size = args.sample_rate * 16;

	bpf_map__resize(skel->maps.ringbuf, args.ringbuf_sz);

	अगर (ringbuf_bench__load(skel)) अणु
		ख_लिखो(मानक_त्रुटि, "failed to load skeleton\n");
		निकास(1);
	पूर्ण

	वापस skel;
पूर्ण

अटल पूर्णांक buf_process_sample(व्योम *ctx, व्योम *data, माप_प्रकार len)
अणु
	atomic_inc(&buf_hits.value);
	वापस 0;
पूर्ण

अटल व्योम ringbuf_libbpf_setup()
अणु
	काष्ठा ringbuf_libbpf_ctx *ctx = &ringbuf_libbpf_ctx;
	काष्ठा bpf_link *link;

	ctx->skel = ringbuf_setup_skeleton();
	ctx->ringbuf = ring_buffer__new(bpf_map__fd(ctx->skel->maps.ringbuf),
					buf_process_sample, शून्य, शून्य);
	अगर (!ctx->ringbuf) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create ringbuf\n");
		निकास(1);
	पूर्ण

	link = bpf_program__attach(ctx->skel->progs.bench_ringbuf);
	अगर (IS_ERR(link)) अणु
		ख_लिखो(मानक_त्रुटि, "failed to attach program!\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम *ringbuf_libbpf_consumer(व्योम *input)
अणु
	काष्ठा ringbuf_libbpf_ctx *ctx = &ringbuf_libbpf_ctx;

	जबतक (ring_buffer__poll(ctx->ringbuf, -1) >= 0) अणु
		अगर (args.back2back)
			bufs_trigger_batch();
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "ringbuf polling failed!\n");
	वापस शून्य;
पूर्ण

/* RINGBUF-CUSTOM benchmark */
काष्ठा ringbuf_custom अणु
	__u64 *consumer_pos;
	__u64 *producer_pos;
	__u64 mask;
	व्योम *data;
	पूर्णांक map_fd;
पूर्ण;

अटल काष्ठा ringbuf_custom_ctx अणु
	काष्ठा ringbuf_bench *skel;
	काष्ठा ringbuf_custom ringbuf;
	पूर्णांक epoll_fd;
	काष्ठा epoll_event event;
पूर्ण ringbuf_custom_ctx;

अटल व्योम ringbuf_custom_measure(काष्ठा bench_res *res)
अणु
	काष्ठा ringbuf_custom_ctx *ctx = &ringbuf_custom_ctx;

	res->hits = atomic_swap(&buf_hits.value, 0);
	res->drops = atomic_swap(&ctx->skel->bss->dropped, 0);
पूर्ण

अटल व्योम ringbuf_custom_setup()
अणु
	काष्ठा ringbuf_custom_ctx *ctx = &ringbuf_custom_ctx;
	स्थिर माप_प्रकार page_size = getpagesize();
	काष्ठा bpf_link *link;
	काष्ठा ringbuf_custom *r;
	व्योम *पंचांगp;
	पूर्णांक err;

	ctx->skel = ringbuf_setup_skeleton();

	ctx->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	अगर (ctx->epoll_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create epoll fd: %d\n", -त्रुटि_सं);
		निकास(1);
	पूर्ण

	r = &ctx->ringbuf;
	r->map_fd = bpf_map__fd(ctx->skel->maps.ringbuf);
	r->mask = args.ringbuf_sz - 1;

	/* Map writable consumer page */
	पंचांगp = mmap(शून्य, page_size, PROT_READ | PROT_WRITE, MAP_SHARED,
		   r->map_fd, 0);
	अगर (पंचांगp == MAP_FAILED) अणु
		ख_लिखो(मानक_त्रुटि, "failed to mmap consumer page: %d\n", -त्रुटि_सं);
		निकास(1);
	पूर्ण
	r->consumer_pos = पंचांगp;

	/* Map पढ़ो-only producer page and data pages. */
	पंचांगp = mmap(शून्य, page_size + 2 * args.ringbuf_sz, PROT_READ, MAP_SHARED,
		   r->map_fd, page_size);
	अगर (पंचांगp == MAP_FAILED) अणु
		ख_लिखो(मानक_त्रुटि, "failed to mmap data pages: %d\n", -त्रुटि_सं);
		निकास(1);
	पूर्ण
	r->producer_pos = पंचांगp;
	r->data = पंचांगp + page_size;

	ctx->event.events = EPOLLIN;
	err = epoll_ctl(ctx->epoll_fd, EPOLL_CTL_ADD, r->map_fd, &ctx->event);
	अगर (err < 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed to epoll add ringbuf: %d\n", -त्रुटि_सं);
		निकास(1);
	पूर्ण

	link = bpf_program__attach(ctx->skel->progs.bench_ringbuf);
	अगर (IS_ERR(link)) अणु
		ख_लिखो(मानक_त्रुटि, "failed to attach program\n");
		निकास(1);
	पूर्ण
पूर्ण

#घोषणा RINGBUF_BUSY_BIT (1 << 31)
#घोषणा RINGBUF_DISCARD_BIT (1 << 30)
#घोषणा RINGBUF_META_LEN 8

अटल अंतरभूत पूर्णांक roundup_len(__u32 len)
अणु
	/* clear out top 2 bits */
	len <<= 2;
	len >>= 2;
	/* add length prefix */
	len += RINGBUF_META_LEN;
	/* round up to 8 byte alignment */
	वापस (len + 7) / 8 * 8;
पूर्ण

अटल व्योम ringbuf_custom_process_ring(काष्ठा ringbuf_custom *r)
अणु
	अचिन्हित दीर्घ cons_pos, prod_pos;
	पूर्णांक *len_ptr, len;
	bool got_new_data;

	cons_pos = smp_load_acquire(r->consumer_pos);
	जबतक (true) अणु
		got_new_data = false;
		prod_pos = smp_load_acquire(r->producer_pos);
		जबतक (cons_pos < prod_pos) अणु
			len_ptr = r->data + (cons_pos & r->mask);
			len = smp_load_acquire(len_ptr);

			/* sample not committed yet, bail out क्रम now */
			अगर (len & RINGBUF_BUSY_BIT)
				वापस;

			got_new_data = true;
			cons_pos += roundup_len(len);

			atomic_inc(&buf_hits.value);
		पूर्ण
		अगर (got_new_data)
			smp_store_release(r->consumer_pos, cons_pos);
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम *ringbuf_custom_consumer(व्योम *input)
अणु
	काष्ठा ringbuf_custom_ctx *ctx = &ringbuf_custom_ctx;
	पूर्णांक cnt;

	करो अणु
		अगर (args.back2back)
			bufs_trigger_batch();
		cnt = epoll_रुको(ctx->epoll_fd, &ctx->event, 1, -1);
		अगर (cnt > 0)
			ringbuf_custom_process_ring(&ctx->ringbuf);
	पूर्ण जबतक (cnt >= 0);
	ख_लिखो(मानक_त्रुटि, "ringbuf polling failed!\n");
	वापस 0;
पूर्ण

/* PERFBUF-LIBBPF benchmark */
अटल काष्ठा perfbuf_libbpf_ctx अणु
	काष्ठा perfbuf_bench *skel;
	काष्ठा perf_buffer *perfbuf;
पूर्ण perfbuf_libbpf_ctx;

अटल व्योम perfbuf_measure(काष्ठा bench_res *res)
अणु
	काष्ठा perfbuf_libbpf_ctx *ctx = &perfbuf_libbpf_ctx;

	res->hits = atomic_swap(&buf_hits.value, 0);
	res->drops = atomic_swap(&ctx->skel->bss->dropped, 0);
पूर्ण

अटल काष्ठा perfbuf_bench *perfbuf_setup_skeleton()
अणु
	काष्ठा perfbuf_bench *skel;

	setup_libbpf();

	skel = perfbuf_bench__खोलो();
	अगर (!skel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open skeleton\n");
		निकास(1);
	पूर्ण

	skel->rodata->batch_cnt = args.batch_cnt;

	अगर (perfbuf_bench__load(skel)) अणु
		ख_लिखो(मानक_त्रुटि, "failed to load skeleton\n");
		निकास(1);
	पूर्ण

	वापस skel;
पूर्ण

अटल क्रमागत bpf_perf_event_ret
perfbuf_process_sample_raw(व्योम *input_ctx, पूर्णांक cpu,
			   काष्ठा perf_event_header *e)
अणु
	चयन (e->type) अणु
	हाल PERF_RECORD_SAMPLE:
		atomic_inc(&buf_hits.value);
		अवरोध;
	हाल PERF_RECORD_LOST:
		अवरोध;
	शेष:
		वापस LIBBPF_PERF_EVENT_ERROR;
	पूर्ण
	वापस LIBBPF_PERF_EVENT_CONT;
पूर्ण

अटल व्योम perfbuf_libbpf_setup()
अणु
	काष्ठा perfbuf_libbpf_ctx *ctx = &perfbuf_libbpf_ctx;
	काष्ठा perf_event_attr attr;
	काष्ठा perf_buffer_raw_opts pb_opts = अणु
		.event_cb = perfbuf_process_sample_raw,
		.ctx = (व्योम *)(दीर्घ)0,
		.attr = &attr,
	पूर्ण;
	काष्ठा bpf_link *link;

	ctx->skel = perfbuf_setup_skeleton();

	स_रखो(&attr, 0, माप(attr));
	attr.config = PERF_COUNT_SW_BPF_OUTPUT,
	attr.type = PERF_TYPE_SOFTWARE;
	attr.sample_type = PERF_SAMPLE_RAW;
	/* notअगरy only every Nth sample */
	अगर (args.sampled) अणु
		attr.sample_period = args.sample_rate;
		attr.wakeup_events = args.sample_rate;
	पूर्ण अन्यथा अणु
		attr.sample_period = 1;
		attr.wakeup_events = 1;
	पूर्ण

	अगर (args.sample_rate > args.batch_cnt) अणु
		ख_लिखो(मानक_त्रुटि, "sample rate %d is too high for given batch count %d\n",
			args.sample_rate, args.batch_cnt);
		निकास(1);
	पूर्ण

	ctx->perfbuf = perf_buffer__new_raw(bpf_map__fd(ctx->skel->maps.perfbuf),
					    args.perfbuf_sz, &pb_opts);
	अगर (!ctx->perfbuf) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create perfbuf\n");
		निकास(1);
	पूर्ण

	link = bpf_program__attach(ctx->skel->progs.bench_perfbuf);
	अगर (IS_ERR(link)) अणु
		ख_लिखो(मानक_त्रुटि, "failed to attach program\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम *perfbuf_libbpf_consumer(व्योम *input)
अणु
	काष्ठा perfbuf_libbpf_ctx *ctx = &perfbuf_libbpf_ctx;

	जबतक (perf_buffer__poll(ctx->perfbuf, -1) >= 0) अणु
		अगर (args.back2back)
			bufs_trigger_batch();
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "perfbuf polling failed!\n");
	वापस शून्य;
पूर्ण

/* PERFBUF-CUSTOM benchmark */

/* copies of पूर्णांकernal libbpf definitions */
काष्ठा perf_cpu_buf अणु
	काष्ठा perf_buffer *pb;
	व्योम *base; /* mmap()'ed memory */
	व्योम *buf; /* क्रम reस्थिरructing segmented data */
	माप_प्रकार buf_size;
	पूर्णांक fd;
	पूर्णांक cpu;
	पूर्णांक map_key;
पूर्ण;

काष्ठा perf_buffer अणु
	perf_buffer_event_fn event_cb;
	perf_buffer_sample_fn sample_cb;
	perf_buffer_lost_fn lost_cb;
	व्योम *ctx; /* passed पूर्णांकo callbacks */

	माप_प्रकार page_size;
	माप_प्रकार mmap_size;
	काष्ठा perf_cpu_buf **cpu_bufs;
	काष्ठा epoll_event *events;
	पूर्णांक cpu_cnt; /* number of allocated CPU buffers */
	पूर्णांक epoll_fd; /* perf event FD */
	पूर्णांक map_fd; /* BPF_MAP_TYPE_PERF_EVENT_ARRAY BPF map FD */
पूर्ण;

अटल व्योम *perfbuf_custom_consumer(व्योम *input)
अणु
	काष्ठा perfbuf_libbpf_ctx *ctx = &perfbuf_libbpf_ctx;
	काष्ठा perf_buffer *pb = ctx->perfbuf;
	काष्ठा perf_cpu_buf *cpu_buf;
	काष्ठा perf_event_mmap_page *header;
	माप_प्रकार mmap_mask = pb->mmap_size - 1;
	काष्ठा perf_event_header *ehdr;
	__u64 data_head, data_tail;
	माप_प्रकार ehdr_size;
	व्योम *base;
	पूर्णांक i, cnt;

	जबतक (true) अणु
		अगर (args.back2back)
			bufs_trigger_batch();
		cnt = epoll_रुको(pb->epoll_fd, pb->events, pb->cpu_cnt, -1);
		अगर (cnt <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "perf epoll failed: %d\n", -त्रुटि_सं);
			निकास(1);
		पूर्ण

		क्रम (i = 0; i < cnt; ++i) अणु
			cpu_buf = pb->events[i].data.ptr;
			header = cpu_buf->base;
			base = ((व्योम *)header) + pb->page_size;

			data_head = ring_buffer_पढ़ो_head(header);
			data_tail = header->data_tail;
			जबतक (data_head != data_tail) अणु
				ehdr = base + (data_tail & mmap_mask);
				ehdr_size = ehdr->size;

				अगर (ehdr->type == PERF_RECORD_SAMPLE)
					atomic_inc(&buf_hits.value);

				data_tail += ehdr_size;
			पूर्ण
			ring_buffer_ग_लिखो_tail(header, data_tail);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

स्थिर काष्ठा bench bench_rb_libbpf = अणु
	.name = "rb-libbpf",
	.validate = bufs_validate,
	.setup = ringbuf_libbpf_setup,
	.producer_thपढ़ो = bufs_sample_producer,
	.consumer_thपढ़ो = ringbuf_libbpf_consumer,
	.measure = ringbuf_libbpf_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_rb_custom = अणु
	.name = "rb-custom",
	.validate = bufs_validate,
	.setup = ringbuf_custom_setup,
	.producer_thपढ़ो = bufs_sample_producer,
	.consumer_thपढ़ो = ringbuf_custom_consumer,
	.measure = ringbuf_custom_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_pb_libbpf = अणु
	.name = "pb-libbpf",
	.validate = bufs_validate,
	.setup = perfbuf_libbpf_setup,
	.producer_thपढ़ो = bufs_sample_producer,
	.consumer_thपढ़ो = perfbuf_libbpf_consumer,
	.measure = perfbuf_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_pb_custom = अणु
	.name = "pb-custom",
	.validate = bufs_validate,
	.setup = perfbuf_libbpf_setup,
	.producer_thपढ़ो = bufs_sample_producer,
	.consumer_thपढ़ो = perfbuf_custom_consumer,
	.measure = perfbuf_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

