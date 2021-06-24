<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *  Copyright(c) 2017-2018 Jesper Dangaard Brouer, Red Hat Inc.
 *
 * XDP monitor tool, based on tracepoपूर्णांकs
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, 2);
	/* TODO: have entries क्रम all possible त्रुटि_सं's */
पूर्ण redirect_err_cnt SEC(".maps");

#घोषणा XDP_UNKNOWN	XDP_REसूचीECT + 1
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, XDP_UNKNOWN + 1);
पूर्ण exception_cnt SEC(".maps");

/* Tracepoपूर्णांक क्रमmat: /sys/kernel/debug/tracing/events/xdp/xdp_redirect/क्रमmat
 * Code in:                kernel/include/trace/events/xdp.h
 */
काष्ठा xdp_redirect_ctx अणु
	u64 __pad;		// First 8 bytes are not accessible by bpf code
	पूर्णांक prog_id;		//	offset:8;  size:4; चिन्हित:1;
	u32 act;		//	offset:12  size:4; चिन्हित:0;
	पूर्णांक अगरindex;		//	offset:16  size:4; चिन्हित:1;
	पूर्णांक err;		//	offset:20  size:4; चिन्हित:1;
	पूर्णांक to_अगरindex;		//	offset:24  size:4; चिन्हित:1;
	u32 map_id;		//	offset:28  size:4; चिन्हित:0;
	पूर्णांक map_index;		//	offset:32  size:4; चिन्हित:1;
पूर्ण;				//	offset:36

क्रमागत अणु
	XDP_REसूचीECT_SUCCESS = 0,
	XDP_REसूचीECT_ERROR = 1
पूर्ण;

अटल __always_अंतरभूत
पूर्णांक xdp_redirect_collect_stat(काष्ठा xdp_redirect_ctx *ctx)
अणु
	u32 key = XDP_REसूचीECT_ERROR;
	पूर्णांक err = ctx->err;
	u64 *cnt;

	अगर (!err)
		key = XDP_REसूचीECT_SUCCESS;

	cnt  = bpf_map_lookup_elem(&redirect_err_cnt, &key);
	अगर (!cnt)
		वापस 1;
	*cnt += 1;

	वापस 0; /* Indicate event was filtered (no further processing)*/
	/*
	 * Returning 1 here would allow e.g. a perf-record tracepoपूर्णांक
	 * to see and record these events, but it करोesn't work well
	 * in-practice as stopping perf-record also unload this
	 * bpf_prog.  Plus, there is additional overhead of करोing so.
	 */
पूर्ण

SEC("tracepoint/xdp/xdp_redirect_err")
पूर्णांक trace_xdp_redirect_err(काष्ठा xdp_redirect_ctx *ctx)
अणु
	वापस xdp_redirect_collect_stat(ctx);
पूर्ण


SEC("tracepoint/xdp/xdp_redirect_map_err")
पूर्णांक trace_xdp_redirect_map_err(काष्ठा xdp_redirect_ctx *ctx)
अणु
	वापस xdp_redirect_collect_stat(ctx);
पूर्ण

/* Likely unloaded when prog starts */
SEC("tracepoint/xdp/xdp_redirect")
पूर्णांक trace_xdp_redirect(काष्ठा xdp_redirect_ctx *ctx)
अणु
	वापस xdp_redirect_collect_stat(ctx);
पूर्ण

/* Likely unloaded when prog starts */
SEC("tracepoint/xdp/xdp_redirect_map")
पूर्णांक trace_xdp_redirect_map(काष्ठा xdp_redirect_ctx *ctx)
अणु
	वापस xdp_redirect_collect_stat(ctx);
पूर्ण

/* Tracepoपूर्णांक क्रमmat: /sys/kernel/debug/tracing/events/xdp/xdp_exception/क्रमmat
 * Code in:                kernel/include/trace/events/xdp.h
 */
काष्ठा xdp_exception_ctx अणु
	u64 __pad;	// First 8 bytes are not accessible by bpf code
	पूर्णांक prog_id;	//	offset:8;  size:4; चिन्हित:1;
	u32 act;	//	offset:12; size:4; चिन्हित:0;
	पूर्णांक अगरindex;	//	offset:16; size:4; चिन्हित:1;
पूर्ण;

SEC("tracepoint/xdp/xdp_exception")
पूर्णांक trace_xdp_exception(काष्ठा xdp_exception_ctx *ctx)
अणु
	u64 *cnt;
	u32 key;

	key = ctx->act;
	अगर (key > XDP_REसूचीECT)
		key = XDP_UNKNOWN;

	cnt = bpf_map_lookup_elem(&exception_cnt, &key);
	अगर (!cnt)
		वापस 1;
	*cnt += 1;

	वापस 0;
पूर्ण

/* Common stats data record shared with _user.c */
काष्ठा datarec अणु
	u64 processed;
	u64 dropped;
	u64 info;
	u64 err;
पूर्ण;
#घोषणा MAX_CPUS 64

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, MAX_CPUS);
पूर्ण cpumap_enqueue_cnt SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 1);
पूर्ण cpumap_kthपढ़ो_cnt SEC(".maps");

/* Tracepoपूर्णांक: /sys/kernel/debug/tracing/events/xdp/xdp_cpumap_enqueue/क्रमmat
 * Code in:         kernel/include/trace/events/xdp.h
 */
काष्ठा cpumap_enqueue_ctx अणु
	u64 __pad;		// First 8 bytes are not accessible by bpf code
	पूर्णांक map_id;		//	offset:8;  size:4; चिन्हित:1;
	u32 act;		//	offset:12; size:4; चिन्हित:0;
	पूर्णांक cpu;		//	offset:16; size:4; चिन्हित:1;
	अचिन्हित पूर्णांक drops;	//	offset:20; size:4; चिन्हित:0;
	अचिन्हित पूर्णांक processed;	//	offset:24; size:4; चिन्हित:0;
	पूर्णांक to_cpu;		//	offset:28; size:4; चिन्हित:1;
पूर्ण;

SEC("tracepoint/xdp/xdp_cpumap_enqueue")
पूर्णांक trace_xdp_cpumap_enqueue(काष्ठा cpumap_enqueue_ctx *ctx)
अणु
	u32 to_cpu = ctx->to_cpu;
	काष्ठा datarec *rec;

	अगर (to_cpu >= MAX_CPUS)
		वापस 1;

	rec = bpf_map_lookup_elem(&cpumap_enqueue_cnt, &to_cpu);
	अगर (!rec)
		वापस 0;
	rec->processed += ctx->processed;
	rec->dropped   += ctx->drops;

	/* Record bulk events, then userspace can calc average bulk size */
	अगर (ctx->processed > 0)
		rec->info += 1;

	वापस 0;
पूर्ण

/* Tracepoपूर्णांक: /sys/kernel/debug/tracing/events/xdp/xdp_cpumap_kthपढ़ो/क्रमmat
 * Code in:         kernel/include/trace/events/xdp.h
 */
काष्ठा cpumap_kthपढ़ो_ctx अणु
	u64 __pad;		// First 8 bytes are not accessible by bpf code
	पूर्णांक map_id;		//	offset:8;  size:4; चिन्हित:1;
	u32 act;		//	offset:12; size:4; चिन्हित:0;
	पूर्णांक cpu;		//	offset:16; size:4; चिन्हित:1;
	अचिन्हित पूर्णांक drops;	//	offset:20; size:4; चिन्हित:0;
	अचिन्हित पूर्णांक processed;	//	offset:24; size:4; चिन्हित:0;
	पूर्णांक sched;		//	offset:28; size:4; चिन्हित:1;
पूर्ण;

SEC("tracepoint/xdp/xdp_cpumap_kthread")
पूर्णांक trace_xdp_cpumap_kthपढ़ो(काष्ठा cpumap_kthपढ़ो_ctx *ctx)
अणु
	काष्ठा datarec *rec;
	u32 key = 0;

	rec = bpf_map_lookup_elem(&cpumap_kthपढ़ो_cnt, &key);
	अगर (!rec)
		वापस 0;
	rec->processed += ctx->processed;
	rec->dropped   += ctx->drops;

	/* Count बार kthपढ़ो yielded CPU via schedule call */
	अगर (ctx->sched)
		rec->info++;

	वापस 0;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 1);
पूर्ण devmap_xmit_cnt SEC(".maps");

/* Tracepoपूर्णांक: /sys/kernel/debug/tracing/events/xdp/xdp_devmap_xmit/क्रमmat
 * Code in:         kernel/include/trace/events/xdp.h
 */
काष्ठा devmap_xmit_ctx अणु
	u64 __pad;		// First 8 bytes are not accessible by bpf code
	पूर्णांक from_अगरindex;	//	offset:8;  size:4; चिन्हित:1;
	u32 act;		//	offset:12; size:4; चिन्हित:0;
	पूर्णांक to_अगरindex; 	//	offset:16; size:4; चिन्हित:1;
	पूर्णांक drops;		//	offset:20; size:4; चिन्हित:1;
	पूर्णांक sent;		//	offset:24; size:4; चिन्हित:1;
	पूर्णांक err;		//	offset:28; size:4; चिन्हित:1;
पूर्ण;

SEC("tracepoint/xdp/xdp_devmap_xmit")
पूर्णांक trace_xdp_devmap_xmit(काष्ठा devmap_xmit_ctx *ctx)
अणु
	काष्ठा datarec *rec;
	u32 key = 0;

	rec = bpf_map_lookup_elem(&devmap_xmit_cnt, &key);
	अगर (!rec)
		वापस 0;
	rec->processed += ctx->sent;
	rec->dropped   += ctx->drops;

	/* Record bulk events, then userspace can calc average bulk size */
	rec->info += 1;

	/* Record error हालs, where no frame were sent */
	अगर (ctx->err)
		rec->err++;

	/* Catch API error of drv nकरो_xdp_xmit sent more than count */
	अगर (ctx->drops < 0)
		rec->err++;

	वापस 1;
पूर्ण
