<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pt.c: Intel Processor Trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/zभाग.स>

#समावेश "session.h"
#समावेश "machine.h"
#समावेश "memswap.h"
#समावेश "sort.h"
#समावेश "tool.h"
#समावेश "event.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "map.h"
#समावेश "color.h"
#समावेश "thread.h"
#समावेश "thread-stack.h"
#समावेश "symbol.h"
#समावेश "callchain.h"
#समावेश "dso.h"
#समावेश "debug.h"
#समावेश "auxtrace.h"
#समावेश "tsc.h"
#समावेश "intel-pt.h"
#समावेश "config.h"
#समावेश "util/perf_api_probe.h"
#समावेश "util/synthetic-events.h"
#समावेश "time-utils.h"

#समावेश "../arch/x86/include/uapi/asm/perf_regs.h"

#समावेश "intel-pt-decoder/intel-pt-log.h"
#समावेश "intel-pt-decoder/intel-pt-decoder.h"
#समावेश "intel-pt-decoder/intel-pt-insn-decoder.h"
#समावेश "intel-pt-decoder/intel-pt-pkt-decoder.h"

#घोषणा MAX_TIMESTAMP (~0ULL)

काष्ठा range अणु
	u64 start;
	u64 end;
पूर्ण;

काष्ठा पूर्णांकel_pt अणु
	काष्ठा auxtrace auxtrace;
	काष्ठा auxtrace_queues queues;
	काष्ठा auxtrace_heap heap;
	u32 auxtrace_type;
	काष्ठा perf_session *session;
	काष्ठा machine *machine;
	काष्ठा evsel *चयन_evsel;
	काष्ठा thपढ़ो *unknown_thपढ़ो;
	bool समयless_decoding;
	bool sampling_mode;
	bool snapshot_mode;
	bool per_cpu_mmaps;
	bool have_tsc;
	bool data_queued;
	bool est_tsc;
	bool sync_चयन;
	bool mispred_all;
	bool use_thपढ़ो_stack;
	bool callstack;
	अचिन्हित पूर्णांक br_stack_sz;
	अचिन्हित पूर्णांक br_stack_sz_plus;
	पूर्णांक have_sched_चयन;
	u32 pmu_type;
	u64 kernel_start;
	u64 चयन_ip;
	u64 ptss_ip;

	काष्ठा perf_tsc_conversion tc;
	bool cap_user_समय_zero;

	काष्ठा itrace_synth_opts synth_opts;

	bool sample_inकाष्ठाions;
	u64 inकाष्ठाions_sample_type;
	u64 inकाष्ठाions_id;

	bool sample_branches;
	u32 branches_filter;
	u64 branches_sample_type;
	u64 branches_id;

	bool sample_transactions;
	u64 transactions_sample_type;
	u64 transactions_id;

	bool sample_ptग_लिखोs;
	u64 ptग_लिखोs_sample_type;
	u64 ptग_लिखोs_id;

	bool sample_pwr_events;
	u64 pwr_events_sample_type;
	u64 mरुको_id;
	u64 pwre_id;
	u64 exstop_id;
	u64 pwrx_id;
	u64 cbr_id;
	u64 psb_id;

	bool sample_pebs;
	काष्ठा evsel *pebs_evsel;

	u64 tsc_bit;
	u64 mtc_bit;
	u64 mtc_freq_bits;
	u32 tsc_ctc_ratio_n;
	u32 tsc_ctc_ratio_d;
	u64 cyc_bit;
	u64 noretcomp_bit;
	अचिन्हित max_non_turbo_ratio;
	अचिन्हित cbr2khz;

	अचिन्हित दीर्घ num_events;

	अक्षर *filter;
	काष्ठा addr_filters filts;

	काष्ठा range *समय_ranges;
	अचिन्हित पूर्णांक range_cnt;

	काष्ठा ip_callchain *chain;
	काष्ठा branch_stack *br_stack;
पूर्ण;

क्रमागत चयन_state अणु
	INTEL_PT_SS_NOT_TRACING,
	INTEL_PT_SS_UNKNOWN,
	INTEL_PT_SS_TRACING,
	INTEL_PT_SS_EXPECTING_SWITCH_EVENT,
	INTEL_PT_SS_EXPECTING_SWITCH_IP,
पूर्ण;

काष्ठा पूर्णांकel_pt_queue अणु
	काष्ठा पूर्णांकel_pt *pt;
	अचिन्हित पूर्णांक queue_nr;
	काष्ठा auxtrace_buffer *buffer;
	काष्ठा auxtrace_buffer *old_buffer;
	व्योम *decoder;
	स्थिर काष्ठा पूर्णांकel_pt_state *state;
	काष्ठा ip_callchain *chain;
	काष्ठा branch_stack *last_branch;
	जोड़ perf_event *event_buf;
	bool on_heap;
	bool stop;
	bool step_through_buffers;
	bool use_buffer_pid_tid;
	bool sync_चयन;
	pid_t pid, tid;
	पूर्णांक cpu;
	पूर्णांक चयन_state;
	pid_t next_tid;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा machine *guest_machine;
	काष्ठा thपढ़ो *unknown_guest_thपढ़ो;
	pid_t guest_machine_pid;
	bool exclude_kernel;
	bool have_sample;
	u64 समय;
	u64 बारtamp;
	u64 sel_बारtamp;
	bool sel_start;
	अचिन्हित पूर्णांक sel_idx;
	u32 flags;
	u16 insn_len;
	u64 last_insn_cnt;
	u64 ipc_insn_cnt;
	u64 ipc_cyc_cnt;
	u64 last_in_insn_cnt;
	u64 last_in_cyc_cnt;
	u64 last_br_insn_cnt;
	u64 last_br_cyc_cnt;
	अचिन्हित पूर्णांक cbr_seen;
	अक्षर insn[INTEL_PT_INSN_BUF_SZ];
पूर्ण;

अटल व्योम पूर्णांकel_pt_dump(काष्ठा पूर्णांकel_pt *pt __maybe_unused,
			  अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा पूर्णांकel_pt_pkt packet;
	माप_प्रकार pos = 0;
	पूर्णांक ret, pkt_len, i;
	अक्षर desc[INTEL_PT_PKT_DESC_MAX];
	स्थिर अक्षर *color = PERF_COLOR_BLUE;
	क्रमागत पूर्णांकel_pt_pkt_ctx ctx = INTEL_PT_NO_CTX;

	color_ख_लिखो(मानक_निकास, color,
		      ". ... Intel Processor Trace data: size %zu bytes\n",
		      len);

	जबतक (len) अणु
		ret = पूर्णांकel_pt_get_packet(buf, len, &packet, &ctx);
		अगर (ret > 0)
			pkt_len = ret;
		अन्यथा
			pkt_len = 1;
		म_लिखो(".");
		color_ख_लिखो(मानक_निकास, color, "  %08x: ", pos);
		क्रम (i = 0; i < pkt_len; i++)
			color_ख_लिखो(मानक_निकास, color, " %02x", buf[i]);
		क्रम (; i < 16; i++)
			color_ख_लिखो(मानक_निकास, color, "   ");
		अगर (ret > 0) अणु
			ret = पूर्णांकel_pt_pkt_desc(&packet, desc,
						INTEL_PT_PKT_DESC_MAX);
			अगर (ret > 0)
				color_ख_लिखो(मानक_निकास, color, " %s\n", desc);
		पूर्ण अन्यथा अणु
			color_ख_लिखो(मानक_निकास, color, " Bad packet!\n");
		पूर्ण
		pos += pkt_len;
		buf += pkt_len;
		len -= pkt_len;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pt_dump_event(काष्ठा पूर्णांकel_pt *pt, अचिन्हित अक्षर *buf,
				माप_प्रकार len)
अणु
	म_लिखो(".\n");
	पूर्णांकel_pt_dump(pt, buf, len);
पूर्ण

अटल व्योम पूर्णांकel_pt_log_event(जोड़ perf_event *event)
अणु
	खाता *f = पूर्णांकel_pt_log_fp();

	अगर (!पूर्णांकel_pt_enable_logging || !f)
		वापस;

	perf_event__ख_लिखो(event, शून्य, f);
पूर्ण

अटल व्योम पूर्णांकel_pt_dump_sample(काष्ठा perf_session *session,
				 काष्ठा perf_sample *sample)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);

	म_लिखो("\n");
	पूर्णांकel_pt_dump(pt, sample->aux_sample.data, sample->aux_sample.size);
पूर्ण

अटल bool पूर्णांकel_pt_log_events(काष्ठा पूर्णांकel_pt *pt, u64 पंचांग)
अणु
	काष्ठा perf_समय_पूर्णांकerval *range = pt->synth_opts.pसमय_range;
	पूर्णांक n = pt->synth_opts.range_num;

	अगर (pt->synth_opts.log_plus_flags & AUXTRACE_LOG_FLG_ALL_PERF_EVTS)
		वापस true;

	अगर (pt->synth_opts.log_minus_flags & AUXTRACE_LOG_FLG_ALL_PERF_EVTS)
		वापस false;

	/* perf_समय__ranges_skip_sample करोes not work अगर समय is zero */
	अगर (!पंचांग)
		पंचांग = 1;

	वापस !n || !perf_समय__ranges_skip_sample(range, n, पंचांग);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_करो_fix_overlap(काष्ठा पूर्णांकel_pt *pt, काष्ठा auxtrace_buffer *a,
				   काष्ठा auxtrace_buffer *b)
अणु
	bool consecutive = false;
	व्योम *start;

	start = पूर्णांकel_pt_find_overlap(a->data, a->size, b->data, b->size,
				      pt->have_tsc, &consecutive);
	अगर (!start)
		वापस -EINVAL;
	b->use_size = b->data + b->size - start;
	b->use_data = start;
	अगर (b->use_size && consecutive)
		b->consecutive = true;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_buffer(काष्ठा पूर्णांकel_pt_queue *ptq,
			       काष्ठा auxtrace_buffer *buffer,
			       काष्ठा auxtrace_buffer *old_buffer,
			       काष्ठा पूर्णांकel_pt_buffer *b)
अणु
	bool might_overlap;

	अगर (!buffer->data) अणु
		पूर्णांक fd = perf_data__fd(ptq->pt->session->data);

		buffer->data = auxtrace_buffer__get_data(buffer, fd);
		अगर (!buffer->data)
			वापस -ENOMEM;
	पूर्ण

	might_overlap = ptq->pt->snapshot_mode || ptq->pt->sampling_mode;
	अगर (might_overlap && !buffer->consecutive && old_buffer &&
	    पूर्णांकel_pt_करो_fix_overlap(ptq->pt, old_buffer, buffer))
		वापस -ENOMEM;

	अगर (buffer->use_data) अणु
		b->len = buffer->use_size;
		b->buf = buffer->use_data;
	पूर्ण अन्यथा अणु
		b->len = buffer->size;
		b->buf = buffer->data;
	पूर्ण
	b->ref_बारtamp = buffer->reference;

	अगर (!old_buffer || (might_overlap && !buffer->consecutive)) अणु
		b->consecutive = false;
		b->trace_nr = buffer->buffer_nr + 1;
	पूर्ण अन्यथा अणु
		b->consecutive = true;
	पूर्ण

	वापस 0;
पूर्ण

/* Do not drop buffers with references - refer पूर्णांकel_pt_get_trace() */
अटल व्योम पूर्णांकel_pt_lookahead_drop_buffer(काष्ठा पूर्णांकel_pt_queue *ptq,
					   काष्ठा auxtrace_buffer *buffer)
अणु
	अगर (!buffer || buffer == ptq->buffer || buffer == ptq->old_buffer)
		वापस;

	auxtrace_buffer__drop_data(buffer);
पूर्ण

/* Must be serialized with respect to पूर्णांकel_pt_get_trace() */
अटल पूर्णांक पूर्णांकel_pt_lookahead(व्योम *data, पूर्णांकel_pt_lookahead_cb_t cb,
			      व्योम *cb_data)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = data;
	काष्ठा auxtrace_buffer *buffer = ptq->buffer;
	काष्ठा auxtrace_buffer *old_buffer = ptq->old_buffer;
	काष्ठा auxtrace_queue *queue;
	पूर्णांक err = 0;

	queue = &ptq->pt->queues.queue_array[ptq->queue_nr];

	जबतक (1) अणु
		काष्ठा पूर्णांकel_pt_buffer b = अणु .len = 0 पूर्ण;

		buffer = auxtrace_buffer__next(queue, buffer);
		अगर (!buffer)
			अवरोध;

		err = पूर्णांकel_pt_get_buffer(ptq, buffer, old_buffer, &b);
		अगर (err)
			अवरोध;

		अगर (b.len) अणु
			पूर्णांकel_pt_lookahead_drop_buffer(ptq, old_buffer);
			old_buffer = buffer;
		पूर्ण अन्यथा अणु
			पूर्णांकel_pt_lookahead_drop_buffer(ptq, buffer);
			जारी;
		पूर्ण

		err = cb(&b, cb_data);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (buffer != old_buffer)
		पूर्णांकel_pt_lookahead_drop_buffer(ptq, buffer);
	पूर्णांकel_pt_lookahead_drop_buffer(ptq, old_buffer);

	वापस err;
पूर्ण

/*
 * This function assumes data is processed sequentially only.
 * Must be serialized with respect to पूर्णांकel_pt_lookahead()
 */
अटल पूर्णांक पूर्णांकel_pt_get_trace(काष्ठा पूर्णांकel_pt_buffer *b, व्योम *data)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = data;
	काष्ठा auxtrace_buffer *buffer = ptq->buffer;
	काष्ठा auxtrace_buffer *old_buffer = ptq->old_buffer;
	काष्ठा auxtrace_queue *queue;
	पूर्णांक err;

	अगर (ptq->stop) अणु
		b->len = 0;
		वापस 0;
	पूर्ण

	queue = &ptq->pt->queues.queue_array[ptq->queue_nr];

	buffer = auxtrace_buffer__next(queue, buffer);
	अगर (!buffer) अणु
		अगर (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		b->len = 0;
		वापस 0;
	पूर्ण

	ptq->buffer = buffer;

	err = पूर्णांकel_pt_get_buffer(ptq, buffer, old_buffer, b);
	अगर (err)
		वापस err;

	अगर (ptq->step_through_buffers)
		ptq->stop = true;

	अगर (b->len) अणु
		अगर (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		ptq->old_buffer = buffer;
	पूर्ण अन्यथा अणु
		auxtrace_buffer__drop_data(buffer);
		वापस पूर्णांकel_pt_get_trace(b, data);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा पूर्णांकel_pt_cache_entry अणु
	काष्ठा auxtrace_cache_entry	entry;
	u64				insn_cnt;
	u64				byte_cnt;
	क्रमागत पूर्णांकel_pt_insn_op		op;
	क्रमागत पूर्णांकel_pt_insn_branch	branch;
	पूर्णांक				length;
	पूर्णांक32_t				rel;
	अक्षर				insn[INTEL_PT_INSN_BUF_SZ];
पूर्ण;

अटल पूर्णांक पूर्णांकel_pt_config_भाग(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data)
अणु
	पूर्णांक *d = data;
	दीर्घ val;

	अगर (!म_भेद(var, "intel-pt.cache-divisor")) अणु
		val = म_से_दीर्घ(value, शून्य, 0);
		अगर (val > 0 && val <= पूर्णांक_उच्च)
			*d = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_cache_भागisor(व्योम)
अणु
	अटल पूर्णांक d;

	अगर (d)
		वापस d;

	perf_config(पूर्णांकel_pt_config_भाग, &d);

	अगर (!d)
		d = 64;

	वापस d;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_pt_cache_size(काष्ठा dso *dso,
					काष्ठा machine *machine)
अणु
	off_t size;

	size = dso__data_size(dso, machine);
	size /= पूर्णांकel_pt_cache_भागisor();
	अगर (size < 1000)
		वापस 10;
	अगर (size > (1 << 21))
		वापस 21;
	वापस 32 - __builtin_clz(size);
पूर्ण

अटल काष्ठा auxtrace_cache *पूर्णांकel_pt_cache(काष्ठा dso *dso,
					     काष्ठा machine *machine)
अणु
	काष्ठा auxtrace_cache *c;
	अचिन्हित पूर्णांक bits;

	अगर (dso->auxtrace_cache)
		वापस dso->auxtrace_cache;

	bits = पूर्णांकel_pt_cache_size(dso, machine);

	/* Ignoring cache creation failure */
	c = auxtrace_cache__new(bits, माप(काष्ठा पूर्णांकel_pt_cache_entry), 200);

	dso->auxtrace_cache = c;

	वापस c;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_cache_add(काष्ठा dso *dso, काष्ठा machine *machine,
			      u64 offset, u64 insn_cnt, u64 byte_cnt,
			      काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn)
अणु
	काष्ठा auxtrace_cache *c = पूर्णांकel_pt_cache(dso, machine);
	काष्ठा पूर्णांकel_pt_cache_entry *e;
	पूर्णांक err;

	अगर (!c)
		वापस -ENOMEM;

	e = auxtrace_cache__alloc_entry(c);
	अगर (!e)
		वापस -ENOMEM;

	e->insn_cnt = insn_cnt;
	e->byte_cnt = byte_cnt;
	e->op = पूर्णांकel_pt_insn->op;
	e->branch = पूर्णांकel_pt_insn->branch;
	e->length = पूर्णांकel_pt_insn->length;
	e->rel = पूर्णांकel_pt_insn->rel;
	स_नकल(e->insn, पूर्णांकel_pt_insn->buf, INTEL_PT_INSN_BUF_SZ);

	err = auxtrace_cache__add(c, offset, &e->entry);
	अगर (err)
		auxtrace_cache__मुक्त_entry(c, e);

	वापस err;
पूर्ण

अटल काष्ठा पूर्णांकel_pt_cache_entry *
पूर्णांकel_pt_cache_lookup(काष्ठा dso *dso, काष्ठा machine *machine, u64 offset)
अणु
	काष्ठा auxtrace_cache *c = पूर्णांकel_pt_cache(dso, machine);

	अगर (!c)
		वापस शून्य;

	वापस auxtrace_cache__lookup(dso->auxtrace_cache, offset);
पूर्ण

अटल व्योम पूर्णांकel_pt_cache_invalidate(काष्ठा dso *dso, काष्ठा machine *machine,
				      u64 offset)
अणु
	काष्ठा auxtrace_cache *c = पूर्णांकel_pt_cache(dso, machine);

	अगर (!c)
		वापस;

	auxtrace_cache__हटाओ(dso->auxtrace_cache, offset);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pt_guest_kernel_ip(uपूर्णांक64_t ip)
अणु
	/* Assumes 64-bit kernel */
	वापस ip & (1ULL << 63);
पूर्ण

अटल अंतरभूत u8 पूर्णांकel_pt_nr_cpumode(काष्ठा पूर्णांकel_pt_queue *ptq, uपूर्णांक64_t ip, bool nr)
अणु
	अगर (nr) अणु
		वापस पूर्णांकel_pt_guest_kernel_ip(ip) ?
		       PERF_RECORD_MISC_GUEST_KERNEL :
		       PERF_RECORD_MISC_GUEST_USER;
	पूर्ण

	वापस ip >= ptq->pt->kernel_start ?
	       PERF_RECORD_MISC_KERNEL :
	       PERF_RECORD_MISC_USER;
पूर्ण

अटल अंतरभूत u8 पूर्णांकel_pt_cpumode(काष्ठा पूर्णांकel_pt_queue *ptq, uपूर्णांक64_t from_ip, uपूर्णांक64_t to_ip)
अणु
	/* No support क्रम non-zero CS base */
	अगर (from_ip)
		वापस पूर्णांकel_pt_nr_cpumode(ptq, from_ip, ptq->state->from_nr);
	वापस पूर्णांकel_pt_nr_cpumode(ptq, to_ip, ptq->state->to_nr);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_guest(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा machines *machines = &ptq->pt->session->machines;
	काष्ठा machine *machine;
	pid_t pid = ptq->pid <= 0 ? DEFAULT_GUEST_KERNEL_ID : ptq->pid;

	अगर (ptq->guest_machine && pid == ptq->guest_machine_pid)
		वापस 0;

	ptq->guest_machine = शून्य;
	thपढ़ो__zput(ptq->unknown_guest_thपढ़ो);

	machine = machines__find_guest(machines, pid);
	अगर (!machine)
		वापस -1;

	ptq->unknown_guest_thपढ़ो = machine__idle_thपढ़ो(machine);
	अगर (!ptq->unknown_guest_thपढ़ो)
		वापस -1;

	ptq->guest_machine = machine;
	ptq->guest_machine_pid = pid;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_next_insn(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn,
				   uपूर्णांक64_t *insn_cnt_ptr, uपूर्णांक64_t *ip,
				   uपूर्णांक64_t to_ip, uपूर्णांक64_t max_insn_cnt,
				   व्योम *data)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = data;
	काष्ठा machine *machine = ptq->pt->machine;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा addr_location al;
	अचिन्हित अक्षर buf[INTEL_PT_INSN_BUF_SZ];
	sमाप_प्रकार len;
	पूर्णांक x86_64;
	u8 cpumode;
	u64 offset, start_offset, start_ip;
	u64 insn_cnt = 0;
	bool one_map = true;
	bool nr;

	पूर्णांकel_pt_insn->length = 0;

	अगर (to_ip && *ip == to_ip)
		जाओ out_no_cache;

	nr = ptq->state->to_nr;
	cpumode = पूर्णांकel_pt_nr_cpumode(ptq, *ip, nr);

	अगर (nr) अणु
		अगर (cpumode != PERF_RECORD_MISC_GUEST_KERNEL ||
		    पूर्णांकel_pt_get_guest(ptq))
			वापस -EINVAL;
		machine = ptq->guest_machine;
		thपढ़ो = ptq->unknown_guest_thपढ़ो;
	पूर्ण अन्यथा अणु
		thपढ़ो = ptq->thपढ़ो;
		अगर (!thपढ़ो) अणु
			अगर (cpumode != PERF_RECORD_MISC_KERNEL)
				वापस -EINVAL;
			thपढ़ो = ptq->pt->unknown_thपढ़ो;
		पूर्ण
	पूर्ण

	जबतक (1) अणु
		अगर (!thपढ़ो__find_map(thपढ़ो, cpumode, *ip, &al) || !al.map->dso)
			वापस -EINVAL;

		अगर (al.map->dso->data.status == DSO_DATA_STATUS_ERROR &&
		    dso__data_status_seen(al.map->dso,
					  DSO_DATA_STATUS_SEEN_ITRACE))
			वापस -ENOENT;

		offset = al.map->map_ip(al.map, *ip);

		अगर (!to_ip && one_map) अणु
			काष्ठा पूर्णांकel_pt_cache_entry *e;

			e = पूर्णांकel_pt_cache_lookup(al.map->dso, machine, offset);
			अगर (e &&
			    (!max_insn_cnt || e->insn_cnt <= max_insn_cnt)) अणु
				*insn_cnt_ptr = e->insn_cnt;
				*ip += e->byte_cnt;
				पूर्णांकel_pt_insn->op = e->op;
				पूर्णांकel_pt_insn->branch = e->branch;
				पूर्णांकel_pt_insn->length = e->length;
				पूर्णांकel_pt_insn->rel = e->rel;
				स_नकल(पूर्णांकel_pt_insn->buf, e->insn,
				       INTEL_PT_INSN_BUF_SZ);
				पूर्णांकel_pt_log_insn_no_data(पूर्णांकel_pt_insn, *ip);
				वापस 0;
			पूर्ण
		पूर्ण

		start_offset = offset;
		start_ip = *ip;

		/* Load maps to ensure dso->is_64_bit has been updated */
		map__load(al.map);

		x86_64 = al.map->dso->is_64_bit;

		जबतक (1) अणु
			len = dso__data_पढ़ो_offset(al.map->dso, machine,
						    offset, buf,
						    INTEL_PT_INSN_BUF_SZ);
			अगर (len <= 0)
				वापस -EINVAL;

			अगर (पूर्णांकel_pt_get_insn(buf, len, x86_64, पूर्णांकel_pt_insn))
				वापस -EINVAL;

			पूर्णांकel_pt_log_insn(पूर्णांकel_pt_insn, *ip);

			insn_cnt += 1;

			अगर (पूर्णांकel_pt_insn->branch != INTEL_PT_BR_NO_BRANCH)
				जाओ out;

			अगर (max_insn_cnt && insn_cnt >= max_insn_cnt)
				जाओ out_no_cache;

			*ip += पूर्णांकel_pt_insn->length;

			अगर (to_ip && *ip == to_ip) अणु
				पूर्णांकel_pt_insn->length = 0;
				जाओ out_no_cache;
			पूर्ण

			अगर (*ip >= al.map->end)
				अवरोध;

			offset += पूर्णांकel_pt_insn->length;
		पूर्ण
		one_map = false;
	पूर्ण
out:
	*insn_cnt_ptr = insn_cnt;

	अगर (!one_map)
		जाओ out_no_cache;

	/*
	 * Didn't lookup in the 'to_ip' हाल, so करो it now to prevent duplicate
	 * entries.
	 */
	अगर (to_ip) अणु
		काष्ठा पूर्णांकel_pt_cache_entry *e;

		e = पूर्णांकel_pt_cache_lookup(al.map->dso, machine, start_offset);
		अगर (e)
			वापस 0;
	पूर्ण

	/* Ignore cache errors */
	पूर्णांकel_pt_cache_add(al.map->dso, machine, start_offset, insn_cnt,
			   *ip - start_ip, पूर्णांकel_pt_insn);

	वापस 0;

out_no_cache:
	*insn_cnt_ptr = insn_cnt;
	वापस 0;
पूर्ण

अटल bool पूर्णांकel_pt_match_pgd_ip(काष्ठा पूर्णांकel_pt *pt, uपूर्णांक64_t ip,
				  uपूर्णांक64_t offset, स्थिर अक्षर *filename)
अणु
	काष्ठा addr_filter *filt;
	bool have_filter   = false;
	bool hit_tracestop = false;
	bool hit_filter    = false;

	list_क्रम_each_entry(filt, &pt->filts.head, list) अणु
		अगर (filt->start)
			have_filter = true;

		अगर ((filename && !filt->filename) ||
		    (!filename && filt->filename) ||
		    (filename && म_भेद(filename, filt->filename)))
			जारी;

		अगर (!(offset >= filt->addr && offset < filt->addr + filt->size))
			जारी;

		पूर्णांकel_pt_log("TIP.PGD ip %#"PRIx64" offset %#"PRIx64" in %s hit filter: %s offset %#"PRIx64" size %#"PRIx64"\n",
			     ip, offset, filename ? filename : "[kernel]",
			     filt->start ? "filter" : "stop",
			     filt->addr, filt->size);

		अगर (filt->start)
			hit_filter = true;
		अन्यथा
			hit_tracestop = true;
	पूर्ण

	अगर (!hit_tracestop && !hit_filter)
		पूर्णांकel_pt_log("TIP.PGD ip %#"PRIx64" offset %#"PRIx64" in %s is not in a filter region\n",
			     ip, offset, filename ? filename : "[kernel]");

	वापस hit_tracestop || (have_filter && !hit_filter);
पूर्ण

अटल पूर्णांक __पूर्णांकel_pt_pgd_ip(uपूर्णांक64_t ip, व्योम *data)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = data;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा addr_location al;
	u8 cpumode;
	u64 offset;

	अगर (ptq->state->to_nr) अणु
		अगर (पूर्णांकel_pt_guest_kernel_ip(ip))
			वापस पूर्णांकel_pt_match_pgd_ip(ptq->pt, ip, ip, शून्य);
		/* No support क्रम decoding guest user space */
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ip >= ptq->pt->kernel_start) अणु
		वापस पूर्णांकel_pt_match_pgd_ip(ptq->pt, ip, ip, शून्य);
	पूर्ण

	cpumode = PERF_RECORD_MISC_USER;

	thपढ़ो = ptq->thपढ़ो;
	अगर (!thपढ़ो)
		वापस -EINVAL;

	अगर (!thपढ़ो__find_map(thपढ़ो, cpumode, ip, &al) || !al.map->dso)
		वापस -EINVAL;

	offset = al.map->map_ip(al.map, ip);

	वापस पूर्णांकel_pt_match_pgd_ip(ptq->pt, ip, offset,
				     al.map->dso->दीर्घ_name);
पूर्ण

अटल bool पूर्णांकel_pt_pgd_ip(uपूर्णांक64_t ip, व्योम *data)
अणु
	वापस __पूर्णांकel_pt_pgd_ip(ip, data) > 0;
पूर्ण

अटल bool पूर्णांकel_pt_get_config(काष्ठा पूर्णांकel_pt *pt,
				काष्ठा perf_event_attr *attr, u64 *config)
अणु
	अगर (attr->type == pt->pmu_type) अणु
		अगर (config)
			*config = attr->config;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool पूर्णांकel_pt_exclude_kernel(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, शून्य) &&
		    !evsel->core.attr.exclude_kernel)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool पूर्णांकel_pt_वापस_compression(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;
	u64 config;

	अगर (!pt->noretcomp_bit)
		वापस true;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, &config) &&
		    (config & pt->noretcomp_bit))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool पूर्णांकel_pt_branch_enable(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;
	u64 config;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, &config) &&
		    (config & 1) && !(config & 0x2000))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_pt_mtc_period(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;
	अचिन्हित पूर्णांक shअगरt;
	u64 config;

	अगर (!pt->mtc_freq_bits)
		वापस 0;

	क्रम (shअगरt = 0, config = pt->mtc_freq_bits; !(config & 1); shअगरt++)
		config >>= 1;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, &config))
			वापस (config & pt->mtc_freq_bits) >> shअगरt;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool पूर्णांकel_pt_समयless_decoding(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;
	bool समयless_decoding = true;
	u64 config;

	अगर (!pt->tsc_bit || !pt->cap_user_समय_zero)
		वापस true;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (!(evsel->core.attr.sample_type & PERF_SAMPLE_TIME))
			वापस true;
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, &config)) अणु
			अगर (config & pt->tsc_bit)
				समयless_decoding = false;
			अन्यथा
				वापस true;
		पूर्ण
	पूर्ण
	वापस समयless_decoding;
पूर्ण

अटल bool पूर्णांकel_pt_tracing_kernel(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, शून्य) &&
		    !evsel->core.attr.exclude_kernel)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool पूर्णांकel_pt_have_tsc(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;
	bool have_tsc = false;
	u64 config;

	अगर (!pt->tsc_bit)
		वापस false;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, &config)) अणु
			अगर (config & pt->tsc_bit)
				have_tsc = true;
			अन्यथा
				वापस false;
		पूर्ण
	पूर्ण
	वापस have_tsc;
पूर्ण

अटल bool पूर्णांकel_pt_sampling_mode(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर ((evsel->core.attr.sample_type & PERF_SAMPLE_AUX) &&
		    evsel->core.attr.aux_sample_size)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल u64 पूर्णांकel_pt_ctl(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;
	u64 config;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (पूर्णांकel_pt_get_config(pt, &evsel->core.attr, &config))
			वापस config;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 पूर्णांकel_pt_ns_to_ticks(स्थिर काष्ठा पूर्णांकel_pt *pt, u64 ns)
अणु
	u64 quot, rem;

	quot = ns / pt->tc.समय_mult;
	rem  = ns % pt->tc.समय_mult;
	वापस (quot << pt->tc.समय_shअगरt) + (rem << pt->tc.समय_shअगरt) /
		pt->tc.समय_mult;
पूर्ण

अटल काष्ठा ip_callchain *पूर्णांकel_pt_alloc_chain(काष्ठा पूर्णांकel_pt *pt)
अणु
	माप_प्रकार sz = माप(काष्ठा ip_callchain);

	/* Add 1 to callchain_sz क्रम callchain context */
	sz += (pt->synth_opts.callchain_sz + 1) * माप(u64);
	वापस zalloc(sz);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_callchain_init(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (!(evsel->core.attr.sample_type & PERF_SAMPLE_CALLCHAIN))
			evsel->synth_sample_type |= PERF_SAMPLE_CALLCHAIN;
	पूर्ण

	pt->chain = पूर्णांकel_pt_alloc_chain(pt);
	अगर (!pt->chain)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_add_callchain(काष्ठा पूर्णांकel_pt *pt,
				   काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(pt->machine,
							sample->pid,
							sample->tid);

	thपढ़ो_stack__sample_late(thपढ़ो, sample->cpu, pt->chain,
				  pt->synth_opts.callchain_sz + 1, sample->ip,
				  pt->kernel_start);

	sample->callchain = pt->chain;
पूर्ण

अटल काष्ठा branch_stack *पूर्णांकel_pt_alloc_br_stack(अचिन्हित पूर्णांक entry_cnt)
अणु
	माप_प्रकार sz = माप(काष्ठा branch_stack);

	sz += entry_cnt * माप(काष्ठा branch_entry);
	वापस zalloc(sz);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_br_stack_init(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (!(evsel->core.attr.sample_type & PERF_SAMPLE_BRANCH_STACK))
			evsel->synth_sample_type |= PERF_SAMPLE_BRANCH_STACK;
	पूर्ण

	pt->br_stack = पूर्णांकel_pt_alloc_br_stack(pt->br_stack_sz);
	अगर (!pt->br_stack)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_add_br_stack(काष्ठा पूर्णांकel_pt *pt,
				  काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(pt->machine,
							sample->pid,
							sample->tid);

	thपढ़ो_stack__br_sample_late(thपढ़ो, sample->cpu, pt->br_stack,
				     pt->br_stack_sz, sample->ip,
				     pt->kernel_start);

	sample->branch_stack = pt->br_stack;
पूर्ण

/* INTEL_PT_LBR_0, INTEL_PT_LBR_1 and INTEL_PT_LBR_2 */
#घोषणा LBRS_MAX (INTEL_PT_BLK_ITEM_ID_CNT * 3U)

अटल काष्ठा पूर्णांकel_pt_queue *पूर्णांकel_pt_alloc_queue(काष्ठा पूर्णांकel_pt *pt,
						   अचिन्हित पूर्णांक queue_nr)
अणु
	काष्ठा पूर्णांकel_pt_params params = अणु .get_trace = 0, पूर्ण;
	काष्ठा perf_env *env = pt->machine->env;
	काष्ठा पूर्णांकel_pt_queue *ptq;

	ptq = zalloc(माप(काष्ठा पूर्णांकel_pt_queue));
	अगर (!ptq)
		वापस शून्य;

	अगर (pt->synth_opts.callchain) अणु
		ptq->chain = पूर्णांकel_pt_alloc_chain(pt);
		अगर (!ptq->chain)
			जाओ out_मुक्त;
	पूर्ण

	अगर (pt->synth_opts.last_branch || pt->synth_opts.other_events) अणु
		अचिन्हित पूर्णांक entry_cnt = max(LBRS_MAX, pt->br_stack_sz);

		ptq->last_branch = पूर्णांकel_pt_alloc_br_stack(entry_cnt);
		अगर (!ptq->last_branch)
			जाओ out_मुक्त;
	पूर्ण

	ptq->event_buf = दो_स्मृति(PERF_SAMPLE_MAX_SIZE);
	अगर (!ptq->event_buf)
		जाओ out_मुक्त;

	ptq->pt = pt;
	ptq->queue_nr = queue_nr;
	ptq->exclude_kernel = पूर्णांकel_pt_exclude_kernel(pt);
	ptq->pid = -1;
	ptq->tid = -1;
	ptq->cpu = -1;
	ptq->next_tid = -1;

	params.get_trace = पूर्णांकel_pt_get_trace;
	params.walk_insn = पूर्णांकel_pt_walk_next_insn;
	params.lookahead = पूर्णांकel_pt_lookahead;
	params.data = ptq;
	params.वापस_compression = पूर्णांकel_pt_वापस_compression(pt);
	params.branch_enable = पूर्णांकel_pt_branch_enable(pt);
	params.ctl = पूर्णांकel_pt_ctl(pt);
	params.max_non_turbo_ratio = pt->max_non_turbo_ratio;
	params.mtc_period = पूर्णांकel_pt_mtc_period(pt);
	params.tsc_ctc_ratio_n = pt->tsc_ctc_ratio_n;
	params.tsc_ctc_ratio_d = pt->tsc_ctc_ratio_d;
	params.quick = pt->synth_opts.quick;

	अगर (pt->filts.cnt > 0)
		params.pgd_ip = पूर्णांकel_pt_pgd_ip;

	अगर (pt->synth_opts.inकाष्ठाions) अणु
		अगर (pt->synth_opts.period) अणु
			चयन (pt->synth_opts.period_type) अणु
			हाल PERF_ITRACE_PERIOD_INSTRUCTIONS:
				params.period_type =
						INTEL_PT_PERIOD_INSTRUCTIONS;
				params.period = pt->synth_opts.period;
				अवरोध;
			हाल PERF_ITRACE_PERIOD_TICKS:
				params.period_type = INTEL_PT_PERIOD_TICKS;
				params.period = pt->synth_opts.period;
				अवरोध;
			हाल PERF_ITRACE_PERIOD_न_अंकOSECS:
				params.period_type = INTEL_PT_PERIOD_TICKS;
				params.period = पूर्णांकel_pt_ns_to_ticks(pt,
							pt->synth_opts.period);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!params.period) अणु
			params.period_type = INTEL_PT_PERIOD_INSTRUCTIONS;
			params.period = 1;
		पूर्ण
	पूर्ण

	अगर (env->cpuid && !म_भेदन(env->cpuid, "GenuineIntel,6,92,", 18))
		params.flags |= INTEL_PT_FUP_WITH_NLIP;

	ptq->decoder = पूर्णांकel_pt_decoder_new(&params);
	अगर (!ptq->decoder)
		जाओ out_मुक्त;

	वापस ptq;

out_मुक्त:
	zमुक्त(&ptq->event_buf);
	zमुक्त(&ptq->last_branch);
	zमुक्त(&ptq->chain);
	मुक्त(ptq);
	वापस शून्य;
पूर्ण

अटल व्योम पूर्णांकel_pt_मुक्त_queue(व्योम *priv)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = priv;

	अगर (!ptq)
		वापस;
	thपढ़ो__zput(ptq->thपढ़ो);
	thपढ़ो__zput(ptq->unknown_guest_thपढ़ो);
	पूर्णांकel_pt_decoder_मुक्त(ptq->decoder);
	zमुक्त(&ptq->event_buf);
	zमुक्त(&ptq->last_branch);
	zमुक्त(&ptq->chain);
	मुक्त(ptq);
पूर्ण

अटल व्योम पूर्णांकel_pt_set_pid_tid_cpu(काष्ठा पूर्णांकel_pt *pt,
				     काष्ठा auxtrace_queue *queue)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = queue->priv;

	अगर (queue->tid == -1 || pt->have_sched_चयन) अणु
		ptq->tid = machine__get_current_tid(pt->machine, ptq->cpu);
		अगर (ptq->tid == -1)
			ptq->pid = -1;
		thपढ़ो__zput(ptq->thपढ़ो);
	पूर्ण

	अगर (!ptq->thपढ़ो && ptq->tid != -1)
		ptq->thपढ़ो = machine__find_thपढ़ो(pt->machine, -1, ptq->tid);

	अगर (ptq->thपढ़ो) अणु
		ptq->pid = ptq->thपढ़ो->pid_;
		अगर (queue->cpu == -1)
			ptq->cpu = ptq->thपढ़ो->cpu;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pt_sample_flags(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	ptq->insn_len = 0;
	अगर (ptq->state->flags & INTEL_PT_ABORT_TX) अणु
		ptq->flags = PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TX_ABORT;
	पूर्ण अन्यथा अगर (ptq->state->flags & INTEL_PT_ASYNC) अणु
		अगर (!ptq->state->to_ip)
			ptq->flags = PERF_IP_FLAG_BRANCH |
				     PERF_IP_FLAG_TRACE_END;
		अन्यथा अगर (ptq->state->from_nr && !ptq->state->to_nr)
			ptq->flags = PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
				     PERF_IP_FLAG_VMEXIT;
		अन्यथा
			ptq->flags = PERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL |
				     PERF_IP_FLAG_ASYNC |
				     PERF_IP_FLAG_INTERRUPT;
	पूर्ण अन्यथा अणु
		अगर (ptq->state->from_ip)
			ptq->flags = पूर्णांकel_pt_insn_type(ptq->state->insn_op);
		अन्यथा
			ptq->flags = PERF_IP_FLAG_BRANCH |
				     PERF_IP_FLAG_TRACE_BEGIN;
		अगर (ptq->state->flags & INTEL_PT_IN_TX)
			ptq->flags |= PERF_IP_FLAG_IN_TX;
		ptq->insn_len = ptq->state->insn_len;
		स_नकल(ptq->insn, ptq->state->insn, INTEL_PT_INSN_BUF_SZ);
	पूर्ण

	अगर (ptq->state->type & INTEL_PT_TRACE_BEGIN)
		ptq->flags |= PERF_IP_FLAG_TRACE_BEGIN;
	अगर (ptq->state->type & INTEL_PT_TRACE_END)
		ptq->flags |= PERF_IP_FLAG_TRACE_END;
पूर्ण

अटल व्योम पूर्णांकel_pt_setup_समय_range(काष्ठा पूर्णांकel_pt *pt,
				      काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	अगर (!pt->range_cnt)
		वापस;

	ptq->sel_बारtamp = pt->समय_ranges[0].start;
	ptq->sel_idx = 0;

	अगर (ptq->sel_बारtamp) अणु
		ptq->sel_start = true;
	पूर्ण अन्यथा अणु
		ptq->sel_बारtamp = pt->समय_ranges[0].end;
		ptq->sel_start = false;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_setup_queue(काष्ठा पूर्णांकel_pt *pt,
				काष्ठा auxtrace_queue *queue,
				अचिन्हित पूर्णांक queue_nr)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq = queue->priv;

	अगर (list_empty(&queue->head))
		वापस 0;

	अगर (!ptq) अणु
		ptq = पूर्णांकel_pt_alloc_queue(pt, queue_nr);
		अगर (!ptq)
			वापस -ENOMEM;
		queue->priv = ptq;

		अगर (queue->cpu != -1)
			ptq->cpu = queue->cpu;
		ptq->tid = queue->tid;

		ptq->cbr_seen = अच_पूर्णांक_उच्च;

		अगर (pt->sampling_mode && !pt->snapshot_mode &&
		    pt->समयless_decoding)
			ptq->step_through_buffers = true;

		ptq->sync_चयन = pt->sync_चयन;

		पूर्णांकel_pt_setup_समय_range(pt, ptq);
	पूर्ण

	अगर (!ptq->on_heap &&
	    (!ptq->sync_चयन ||
	     ptq->चयन_state != INTEL_PT_SS_EXPECTING_SWITCH_EVENT)) अणु
		स्थिर काष्ठा पूर्णांकel_pt_state *state;
		पूर्णांक ret;

		अगर (pt->समयless_decoding)
			वापस 0;

		पूर्णांकel_pt_log("queue %u getting timestamp\n", queue_nr);
		पूर्णांकel_pt_log("queue %u decoding cpu %d pid %d tid %d\n",
			     queue_nr, ptq->cpu, ptq->pid, ptq->tid);

		अगर (ptq->sel_start && ptq->sel_बारtamp) अणु
			ret = पूर्णांकel_pt_fast_क्रमward(ptq->decoder,
						    ptq->sel_बारtamp);
			अगर (ret)
				वापस ret;
		पूर्ण

		जबतक (1) अणु
			state = पूर्णांकel_pt_decode(ptq->decoder);
			अगर (state->err) अणु
				अगर (state->err == INTEL_PT_ERR_NODATA) अणु
					पूर्णांकel_pt_log("queue %u has no timestamp\n",
						     queue_nr);
					वापस 0;
				पूर्ण
				जारी;
			पूर्ण
			अगर (state->बारtamp)
				अवरोध;
		पूर्ण

		ptq->बारtamp = state->बारtamp;
		पूर्णांकel_pt_log("queue %u timestamp 0x%" PRIx64 "\n",
			     queue_nr, ptq->बारtamp);
		ptq->state = state;
		ptq->have_sample = true;
		अगर (ptq->sel_start && ptq->sel_बारtamp &&
		    ptq->बारtamp < ptq->sel_बारtamp)
			ptq->have_sample = false;
		पूर्णांकel_pt_sample_flags(ptq);
		ret = auxtrace_heap__add(&pt->heap, queue_nr, ptq->बारtamp);
		अगर (ret)
			वापस ret;
		ptq->on_heap = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_setup_queues(काष्ठा पूर्णांकel_pt *pt)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < pt->queues.nr_queues; i++) अणु
		ret = पूर्णांकel_pt_setup_queue(pt, &pt->queues.queue_array[i], i);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pt_skip_event(काष्ठा पूर्णांकel_pt *pt)
अणु
	वापस pt->synth_opts.initial_skip &&
	       pt->num_events++ < pt->synth_opts.initial_skip;
पूर्ण

/*
 * Cannot count CBR as skipped because it won't go away until cbr == cbr_seen.
 * Also ensure CBR is first non-skipped event by allowing क्रम 4 more samples
 * from this decoder state.
 */
अटल अंतरभूत bool पूर्णांकel_pt_skip_cbr_event(काष्ठा पूर्णांकel_pt *pt)
अणु
	वापस pt->synth_opts.initial_skip &&
	       pt->num_events + 4 < pt->synth_opts.initial_skip;
पूर्ण

अटल व्योम पूर्णांकel_pt_prep_a_sample(काष्ठा पूर्णांकel_pt_queue *ptq,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample)
अणु
	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.size = माप(काष्ठा perf_event_header);

	sample->pid = ptq->pid;
	sample->tid = ptq->tid;
	sample->cpu = ptq->cpu;
	sample->insn_len = ptq->insn_len;
	स_नकल(sample->insn, ptq->insn, INTEL_PT_INSN_BUF_SZ);
पूर्ण

अटल व्योम पूर्णांकel_pt_prep_b_sample(काष्ठा पूर्णांकel_pt *pt,
				   काष्ठा पूर्णांकel_pt_queue *ptq,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample)
अणु
	पूर्णांकel_pt_prep_a_sample(ptq, event, sample);

	अगर (!pt->समयless_decoding)
		sample->समय = tsc_to_perf_समय(ptq->बारtamp, &pt->tc);

	sample->ip = ptq->state->from_ip;
	sample->addr = ptq->state->to_ip;
	sample->cpumode = पूर्णांकel_pt_cpumode(ptq, sample->ip, sample->addr);
	sample->period = 1;
	sample->flags = ptq->flags;

	event->sample.header.misc = sample->cpumode;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_inject_event(जोड़ perf_event *event,
				 काष्ठा perf_sample *sample, u64 type)
अणु
	event->header.size = perf_event__sample_event_size(sample, type, 0);
	वापस perf_event__synthesize_sample(event, type, 0, sample);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_pt_opt_inject(काष्ठा पूर्णांकel_pt *pt,
				      जोड़ perf_event *event,
				      काष्ठा perf_sample *sample, u64 type)
अणु
	अगर (!pt->synth_opts.inject)
		वापस 0;

	वापस पूर्णांकel_pt_inject_event(event, sample, type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_deliver_synth_event(काष्ठा पूर्णांकel_pt *pt,
					जोड़ perf_event *event,
					काष्ठा perf_sample *sample, u64 type)
अणु
	पूर्णांक ret;

	ret = पूर्णांकel_pt_opt_inject(pt, event, sample, type);
	अगर (ret)
		वापस ret;

	ret = perf_session__deliver_synth_event(pt->session, event, sample);
	अगर (ret)
		pr_err("Intel PT: failed to deliver event, error %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_branch_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा dummy_branch_stack अणु
		u64			nr;
		u64			hw_idx;
		काष्ठा branch_entry	entries;
	पूर्ण dummy_bs;

	अगर (pt->branches_filter && !(pt->branches_filter & ptq->flags))
		वापस 0;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_b_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->branches_id;
	sample.stream_id = ptq->pt->branches_id;

	/*
	 * perf report cannot handle events without a branch stack when using
	 * SORT_MODE__BRANCH so make a dummy one.
	 */
	अगर (pt->synth_opts.last_branch && sort__mode == SORT_MODE__BRANCH) अणु
		dummy_bs = (काष्ठा dummy_branch_stack)अणु
			.nr = 1,
			.hw_idx = -1ULL,
			.entries = अणु
				.from = sample.ip,
				.to = sample.addr,
			पूर्ण,
		पूर्ण;
		sample.branch_stack = (काष्ठा branch_stack *)&dummy_bs;
	पूर्ण

	अगर (ptq->state->flags & INTEL_PT_SAMPLE_IPC)
		sample.cyc_cnt = ptq->ipc_cyc_cnt - ptq->last_br_cyc_cnt;
	अगर (sample.cyc_cnt) अणु
		sample.insn_cnt = ptq->ipc_insn_cnt - ptq->last_br_insn_cnt;
		ptq->last_br_insn_cnt = ptq->ipc_insn_cnt;
		ptq->last_br_cyc_cnt = ptq->ipc_cyc_cnt;
	पूर्ण

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->branches_sample_type);
पूर्ण

अटल व्योम पूर्णांकel_pt_prep_sample(काष्ठा पूर्णांकel_pt *pt,
				 काष्ठा पूर्णांकel_pt_queue *ptq,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample)
अणु
	पूर्णांकel_pt_prep_b_sample(pt, ptq, event, sample);

	अगर (pt->synth_opts.callchain) अणु
		thपढ़ो_stack__sample(ptq->thपढ़ो, ptq->cpu, ptq->chain,
				     pt->synth_opts.callchain_sz + 1,
				     sample->ip, pt->kernel_start);
		sample->callchain = ptq->chain;
	पूर्ण

	अगर (pt->synth_opts.last_branch) अणु
		thपढ़ो_stack__br_sample(ptq->thपढ़ो, ptq->cpu, ptq->last_branch,
					pt->br_stack_sz);
		sample->branch_stack = ptq->last_branch;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_inकाष्ठाion_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->inकाष्ठाions_id;
	sample.stream_id = ptq->pt->inकाष्ठाions_id;
	अगर (pt->synth_opts.quick)
		sample.period = 1;
	अन्यथा
		sample.period = ptq->state->tot_insn_cnt - ptq->last_insn_cnt;

	अगर (ptq->state->flags & INTEL_PT_SAMPLE_IPC)
		sample.cyc_cnt = ptq->ipc_cyc_cnt - ptq->last_in_cyc_cnt;
	अगर (sample.cyc_cnt) अणु
		sample.insn_cnt = ptq->ipc_insn_cnt - ptq->last_in_insn_cnt;
		ptq->last_in_insn_cnt = ptq->ipc_insn_cnt;
		ptq->last_in_cyc_cnt = ptq->ipc_cyc_cnt;
	पूर्ण

	ptq->last_insn_cnt = ptq->state->tot_insn_cnt;

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->inकाष्ठाions_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_transaction_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->transactions_id;
	sample.stream_id = ptq->pt->transactions_id;

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->transactions_sample_type);
पूर्ण

अटल व्योम पूर्णांकel_pt_prep_p_sample(काष्ठा पूर्णांकel_pt *pt,
				   काष्ठा पूर्णांकel_pt_queue *ptq,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample)
अणु
	पूर्णांकel_pt_prep_sample(pt, ptq, event, sample);

	/*
	 * Zero IP is used to mean "trace start" but that is not the हाल क्रम
	 * घातer or PTWRITE events with no IP, so clear the flags.
	 */
	अगर (!sample->ip)
		sample->flags = 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_ptग_लिखो_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_ptग_लिखो raw;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->ptग_लिखोs_id;
	sample.stream_id = ptq->pt->ptग_लिखोs_id;

	raw.flags = 0;
	raw.ip = !!(ptq->state->flags & INTEL_PT_FUP_IP);
	raw.payload = cpu_to_le64(ptq->state->ptw_payload);

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->ptग_लिखोs_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_cbr_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_cbr raw;
	u32 flags;

	अगर (पूर्णांकel_pt_skip_cbr_event(pt))
		वापस 0;

	ptq->cbr_seen = ptq->state->cbr;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->cbr_id;
	sample.stream_id = ptq->pt->cbr_id;

	flags = (u16)ptq->state->cbr_payload | (pt->max_non_turbo_ratio << 16);
	raw.flags = cpu_to_le32(flags);
	raw.freq = cpu_to_le32(raw.cbr * pt->cbr2khz);
	raw.reserved3 = 0;

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->pwr_events_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_psb_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_psb raw;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->psb_id;
	sample.stream_id = ptq->pt->psb_id;
	sample.flags = 0;

	raw.reserved = 0;
	raw.offset = ptq->state->psb_offset;

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->pwr_events_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_mरुको_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_mरुको raw;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->mरुको_id;
	sample.stream_id = ptq->pt->mरुको_id;

	raw.reserved = 0;
	raw.payload = cpu_to_le64(ptq->state->mरुको_payload);

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->pwr_events_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_pwre_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_pwre raw;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->pwre_id;
	sample.stream_id = ptq->pt->pwre_id;

	raw.reserved = 0;
	raw.payload = cpu_to_le64(ptq->state->pwre_payload);

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->pwr_events_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_exstop_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_exstop raw;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->exstop_id;
	sample.stream_id = ptq->pt->exstop_id;

	raw.flags = 0;
	raw.ip = !!(ptq->state->flags & INTEL_PT_FUP_IP);

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->pwr_events_sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_pwrx_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	काष्ठा perf_synth_पूर्णांकel_pwrx raw;

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->pwrx_id;
	sample.stream_id = ptq->pt->pwrx_id;

	raw.reserved = 0;
	raw.payload = cpu_to_le64(ptq->state->pwrx_payload);

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample,
					    pt->pwr_events_sample_type);
पूर्ण

/*
 * PEBS gp_regs array indexes plus 1 so that 0 means not present. Refer
 * पूर्णांकel_pt_add_gp_regs().
 */
अटल स्थिर पूर्णांक pebs_gp_regs[] = अणु
	[PERF_REG_X86_FLAGS]	= 1,
	[PERF_REG_X86_IP]	= 2,
	[PERF_REG_X86_AX]	= 3,
	[PERF_REG_X86_CX]	= 4,
	[PERF_REG_X86_DX]	= 5,
	[PERF_REG_X86_BX]	= 6,
	[PERF_REG_X86_SP]	= 7,
	[PERF_REG_X86_BP]	= 8,
	[PERF_REG_X86_SI]	= 9,
	[PERF_REG_X86_DI]	= 10,
	[PERF_REG_X86_R8]	= 11,
	[PERF_REG_X86_R9]	= 12,
	[PERF_REG_X86_R10]	= 13,
	[PERF_REG_X86_R11]	= 14,
	[PERF_REG_X86_R12]	= 15,
	[PERF_REG_X86_R13]	= 16,
	[PERF_REG_X86_R14]	= 17,
	[PERF_REG_X86_R15]	= 18,
पूर्ण;

अटल u64 *पूर्णांकel_pt_add_gp_regs(काष्ठा regs_dump *पूर्णांकr_regs, u64 *pos,
				 स्थिर काष्ठा पूर्णांकel_pt_blk_items *items,
				 u64 regs_mask)
अणु
	स्थिर u64 *gp_regs = items->val[INTEL_PT_GP_REGS_POS];
	u32 mask = items->mask[INTEL_PT_GP_REGS_POS];
	u32 bit;
	पूर्णांक i;

	क्रम (i = 0, bit = 1; i < PERF_REG_X86_64_MAX; i++, bit <<= 1) अणु
		/* Get the PEBS gp_regs array index */
		पूर्णांक n = pebs_gp_regs[i] - 1;

		अगर (n < 0)
			जारी;
		/*
		 * Add only रेजिस्टरs that were requested (i.e. 'regs_mask') and
		 * that were provided (i.e. 'mask'), and update the resulting
		 * mask (i.e. 'intr_regs->mask') accordingly.
		 */
		अगर (mask & 1 << n && regs_mask & bit) अणु
			पूर्णांकr_regs->mask |= bit;
			*pos++ = gp_regs[n];
		पूर्ण
	पूर्ण

	वापस pos;
पूर्ण

#अगर_अघोषित PERF_REG_X86_XMM0
#घोषणा PERF_REG_X86_XMM0 32
#पूर्ण_अगर

अटल व्योम पूर्णांकel_pt_add_xmm(काष्ठा regs_dump *पूर्णांकr_regs, u64 *pos,
			     स्थिर काष्ठा पूर्णांकel_pt_blk_items *items,
			     u64 regs_mask)
अणु
	u32 mask = items->has_xmm & (regs_mask >> PERF_REG_X86_XMM0);
	स्थिर u64 *xmm = items->xmm;

	/*
	 * If there are any XMM रेजिस्टरs, then there should be all of them.
	 * Nevertheless, follow the logic to add only रेजिस्टरs that were
	 * requested (i.e. 'regs_mask') and that were provided (i.e. 'mask'),
	 * and update the resulting mask (i.e. 'intr_regs->mask') accordingly.
	 */
	पूर्णांकr_regs->mask |= (u64)mask << PERF_REG_X86_XMM0;

	क्रम (; mask; mask >>= 1, xmm++) अणु
		अगर (mask & 1)
			*pos++ = *xmm;
	पूर्ण
पूर्ण

#घोषणा LBR_INFO_MISPRED	(1ULL << 63)
#घोषणा LBR_INFO_IN_TX		(1ULL << 62)
#घोषणा LBR_INFO_ABORT		(1ULL << 61)
#घोषणा LBR_INFO_CYCLES		0xffff

/* Refer kernel's पूर्णांकel_pmu_store_pebs_lbrs() */
अटल u64 पूर्णांकel_pt_lbr_flags(u64 info)
अणु
	जोड़ अणु
		काष्ठा branch_flags flags;
		u64 result;
	पूर्ण u;

	u.result	  = 0;
	u.flags.mispred	  = !!(info & LBR_INFO_MISPRED);
	u.flags.predicted = !(info & LBR_INFO_MISPRED);
	u.flags.in_tx	  = !!(info & LBR_INFO_IN_TX);
	u.flags.पात	  = !!(info & LBR_INFO_ABORT);
	u.flags.cycles	  = info & LBR_INFO_CYCLES;

	वापस u.result;
पूर्ण

अटल व्योम पूर्णांकel_pt_add_lbrs(काष्ठा branch_stack *br_stack,
			      स्थिर काष्ठा पूर्णांकel_pt_blk_items *items)
अणु
	u64 *to;
	पूर्णांक i;

	br_stack->nr = 0;

	to = &br_stack->entries[0].from;

	क्रम (i = INTEL_PT_LBR_0_POS; i <= INTEL_PT_LBR_2_POS; i++) अणु
		u32 mask = items->mask[i];
		स्थिर u64 *from = items->val[i];

		क्रम (; mask; mask >>= 3, from += 3) अणु
			अगर ((mask & 7) == 7) अणु
				*to++ = from[0];
				*to++ = from[1];
				*to++ = पूर्णांकel_pt_lbr_flags(from[2]);
				br_stack->nr += 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_pebs_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	स्थिर काष्ठा पूर्णांकel_pt_blk_items *items = &ptq->state->items;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;
	जोड़ perf_event *event = ptq->event_buf;
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	काष्ठा evsel *evsel = pt->pebs_evsel;
	u64 sample_type = evsel->core.attr.sample_type;
	u64 id = evsel->core.id[0];
	u8 cpumode;
	u64 regs[8 * माप(sample.पूर्णांकr_regs.mask)];

	अगर (पूर्णांकel_pt_skip_event(pt))
		वापस 0;

	पूर्णांकel_pt_prep_a_sample(ptq, event, &sample);

	sample.id = id;
	sample.stream_id = id;

	अगर (!evsel->core.attr.freq)
		sample.period = evsel->core.attr.sample_period;

	/* No support क्रम non-zero CS base */
	अगर (items->has_ip)
		sample.ip = items->ip;
	अन्यथा अगर (items->has_rip)
		sample.ip = items->rip;
	अन्यथा
		sample.ip = ptq->state->from_ip;

	cpumode = पूर्णांकel_pt_cpumode(ptq, sample.ip, 0);

	event->sample.header.misc = cpumode | PERF_RECORD_MISC_EXACT_IP;

	sample.cpumode = cpumode;

	अगर (sample_type & PERF_SAMPLE_TIME) अणु
		u64 बारtamp = 0;

		अगर (items->has_बारtamp)
			बारtamp = items->बारtamp;
		अन्यथा अगर (!pt->समयless_decoding)
			बारtamp = ptq->बारtamp;
		अगर (बारtamp)
			sample.समय = tsc_to_perf_समय(बारtamp, &pt->tc);
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_CALLCHAIN &&
	    pt->synth_opts.callchain) अणु
		thपढ़ो_stack__sample(ptq->thपढ़ो, ptq->cpu, ptq->chain,
				     pt->synth_opts.callchain_sz, sample.ip,
				     pt->kernel_start);
		sample.callchain = ptq->chain;
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_REGS_INTR &&
	    (items->mask[INTEL_PT_GP_REGS_POS] ||
	     items->mask[INTEL_PT_XMM_POS])) अणु
		u64 regs_mask = evsel->core.attr.sample_regs_पूर्णांकr;
		u64 *pos;

		sample.पूर्णांकr_regs.abi = items->is_32_bit ?
				       PERF_SAMPLE_REGS_ABI_32 :
				       PERF_SAMPLE_REGS_ABI_64;
		sample.पूर्णांकr_regs.regs = regs;

		pos = पूर्णांकel_pt_add_gp_regs(&sample.पूर्णांकr_regs, regs, items, regs_mask);

		पूर्णांकel_pt_add_xmm(&sample.पूर्णांकr_regs, pos, items, regs_mask);
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_BRANCH_STACK) अणु
		अगर (items->mask[INTEL_PT_LBR_0_POS] ||
		    items->mask[INTEL_PT_LBR_1_POS] ||
		    items->mask[INTEL_PT_LBR_2_POS]) अणु
			पूर्णांकel_pt_add_lbrs(ptq->last_branch, items);
		पूर्ण अन्यथा अगर (pt->synth_opts.last_branch) अणु
			thपढ़ो_stack__br_sample(ptq->thपढ़ो, ptq->cpu,
						ptq->last_branch,
						pt->br_stack_sz);
		पूर्ण अन्यथा अणु
			ptq->last_branch->nr = 0;
		पूर्ण
		sample.branch_stack = ptq->last_branch;
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_ADDR && items->has_mem_access_address)
		sample.addr = items->mem_access_address;

	अगर (sample_type & PERF_SAMPLE_WEIGHT_TYPE) अणु
		/*
		 * Refer kernel's setup_pebs_adaptive_sample_data() and
		 * पूर्णांकel_hsw_weight().
		 */
		अगर (items->has_mem_access_latency) अणु
			u64 weight = items->mem_access_latency >> 32;

			/*
			 * Starts from SPR, the mem access latency field
			 * contains both cache latency [47:32] and inकाष्ठाion
			 * latency [15:0]. The cache latency is the same as the
			 * mem access latency on previous platक्रमms.
			 *
			 * In practice, no memory access could last than 4G
			 * cycles. Use latency >> 32 to distinguish the
			 * dअगरferent क्रमmat of the mem access latency field.
			 */
			अगर (weight > 0) अणु
				sample.weight = weight & 0xffff;
				sample.ins_lat = items->mem_access_latency & 0xffff;
			पूर्ण अन्यथा
				sample.weight = items->mem_access_latency;
		पूर्ण
		अगर (!sample.weight && items->has_tsx_aux_info) अणु
			/* Cycles last block */
			sample.weight = (u32)items->tsx_aux_info;
		पूर्ण
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_TRANSACTION && items->has_tsx_aux_info) अणु
		u64 ax = items->has_rax ? items->rax : 0;
		/* Refer kernel's पूर्णांकel_hsw_transaction() */
		u64 txn = (u8)(items->tsx_aux_info >> 32);

		/* For RTM XABORTs also log the पात code from AX */
		अगर (txn & PERF_TXN_TRANSACTION && ax & 1)
			txn |= ((ax >> 24) & 0xff) << PERF_TXN_ABORT_SHIFT;
		sample.transaction = txn;
	पूर्ण

	वापस पूर्णांकel_pt_deliver_synth_event(pt, event, &sample, sample_type);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_error(काष्ठा पूर्णांकel_pt *pt, पूर्णांक code, पूर्णांक cpu,
				pid_t pid, pid_t tid, u64 ip, u64 बारtamp)
अणु
	जोड़ perf_event event;
	अक्षर msg[MAX_AUXTRACE_ERROR_MSG];
	पूर्णांक err;

	अगर (pt->synth_opts.error_minus_flags) अणु
		अगर (code == INTEL_PT_ERR_OVR &&
		    pt->synth_opts.error_minus_flags & AUXTRACE_ERR_FLG_OVERFLOW)
			वापस 0;
		अगर (code == INTEL_PT_ERR_LOST &&
		    pt->synth_opts.error_minus_flags & AUXTRACE_ERR_FLG_DATA_LOST)
			वापस 0;
	पूर्ण

	पूर्णांकel_pt__म_त्रुटि(code, msg, MAX_AUXTRACE_ERROR_MSG);

	auxtrace_synth_error(&event.auxtrace_error, PERF_AUXTRACE_ERROR_ITRACE,
			     code, cpu, pid, tid, ip, msg, बारtamp);

	err = perf_session__deliver_synth_event(pt->session, &event, शून्य);
	अगर (err)
		pr_err("Intel Processor Trace: failed to deliver error event, error %d\n",
		       err);

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_ptq_synth_error(काष्ठा पूर्णांकel_pt_queue *ptq,
				 स्थिर काष्ठा पूर्णांकel_pt_state *state)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	u64 पंचांग = ptq->बारtamp;

	पंचांग = pt->समयless_decoding ? 0 : tsc_to_perf_समय(पंचांग, &pt->tc);

	वापस पूर्णांकel_pt_synth_error(pt, state->err, ptq->cpu, ptq->pid,
				    ptq->tid, state->from_ip, पंचांग);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_next_tid(काष्ठा पूर्णांकel_pt *pt, काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा auxtrace_queue *queue;
	pid_t tid = ptq->next_tid;
	पूर्णांक err;

	अगर (tid == -1)
		वापस 0;

	पूर्णांकel_pt_log("switch: cpu %d tid %d\n", ptq->cpu, tid);

	err = machine__set_current_tid(pt->machine, ptq->cpu, -1, tid);

	queue = &pt->queues.queue_array[ptq->queue_nr];
	पूर्णांकel_pt_set_pid_tid_cpu(pt, queue);

	ptq->next_tid = -1;

	वापस err;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pt_is_चयन_ip(काष्ठा पूर्णांकel_pt_queue *ptq, u64 ip)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;

	वापस ip == pt->चयन_ip &&
	       (ptq->flags & PERF_IP_FLAG_BRANCH) &&
	       !(ptq->flags & (PERF_IP_FLAG_CONDITIONAL | PERF_IP_FLAG_ASYNC |
			       PERF_IP_FLAG_INTERRUPT | PERF_IP_FLAG_TX_ABORT));
पूर्ण

#घोषणा INTEL_PT_PWR_EVT (INTEL_PT_MWAIT_OP | INTEL_PT_PWR_ENTRY | \
			  INTEL_PT_EX_STOP | INTEL_PT_PWR_EXIT)

अटल पूर्णांक पूर्णांकel_pt_sample(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	स्थिर काष्ठा पूर्णांकel_pt_state *state = ptq->state;
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	पूर्णांक err;

	अगर (!ptq->have_sample)
		वापस 0;

	ptq->have_sample = false;

	ptq->ipc_insn_cnt = ptq->state->tot_insn_cnt;
	ptq->ipc_cyc_cnt = ptq->state->tot_cyc_cnt;

	/*
	 * Do PEBS first to allow क्रम the possibility that the PEBS बारtamp
	 * precedes the current बारtamp.
	 */
	अगर (pt->sample_pebs && state->type & INTEL_PT_BLK_ITEMS) अणु
		err = पूर्णांकel_pt_synth_pebs_sample(ptq);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pt->sample_pwr_events) अणु
		अगर (state->type & INTEL_PT_PSB_EVT) अणु
			err = पूर्णांकel_pt_synth_psb_sample(ptq);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (ptq->state->cbr != ptq->cbr_seen) अणु
			err = पूर्णांकel_pt_synth_cbr_sample(ptq);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (state->type & INTEL_PT_PWR_EVT) अणु
			अगर (state->type & INTEL_PT_MWAIT_OP) अणु
				err = पूर्णांकel_pt_synth_mरुको_sample(ptq);
				अगर (err)
					वापस err;
			पूर्ण
			अगर (state->type & INTEL_PT_PWR_ENTRY) अणु
				err = पूर्णांकel_pt_synth_pwre_sample(ptq);
				अगर (err)
					वापस err;
			पूर्ण
			अगर (state->type & INTEL_PT_EX_STOP) अणु
				err = पूर्णांकel_pt_synth_exstop_sample(ptq);
				अगर (err)
					वापस err;
			पूर्ण
			अगर (state->type & INTEL_PT_PWR_EXIT) अणु
				err = पूर्णांकel_pt_synth_pwrx_sample(ptq);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pt->sample_inकाष्ठाions && (state->type & INTEL_PT_INSTRUCTION)) अणु
		err = पूर्णांकel_pt_synth_inकाष्ठाion_sample(ptq);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pt->sample_transactions && (state->type & INTEL_PT_TRANSACTION)) अणु
		err = पूर्णांकel_pt_synth_transaction_sample(ptq);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pt->sample_ptग_लिखोs && (state->type & INTEL_PT_PTW)) अणु
		err = पूर्णांकel_pt_synth_ptग_लिखो_sample(ptq);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!(state->type & INTEL_PT_BRANCH))
		वापस 0;

	अगर (pt->use_thपढ़ो_stack) अणु
		thपढ़ो_stack__event(ptq->thपढ़ो, ptq->cpu, ptq->flags,
				    state->from_ip, state->to_ip, ptq->insn_len,
				    state->trace_nr, pt->callstack,
				    pt->br_stack_sz_plus,
				    pt->mispred_all);
	पूर्ण अन्यथा अणु
		thपढ़ो_stack__set_trace_nr(ptq->thपढ़ो, ptq->cpu, state->trace_nr);
	पूर्ण

	अगर (pt->sample_branches) अणु
		अगर (state->from_nr != state->to_nr &&
		    state->from_ip && state->to_ip) अणु
			काष्ठा पूर्णांकel_pt_state *st = (काष्ठा पूर्णांकel_pt_state *)state;
			u64 to_ip = st->to_ip;
			u64 from_ip = st->from_ip;

			/*
			 * perf cannot handle having dअगरferent machines क्रम ip
			 * and addr, so create 2 branches.
			 */
			st->to_ip = 0;
			err = पूर्णांकel_pt_synth_branch_sample(ptq);
			अगर (err)
				वापस err;
			st->from_ip = 0;
			st->to_ip = to_ip;
			err = पूर्णांकel_pt_synth_branch_sample(ptq);
			st->from_ip = from_ip;
		पूर्ण अन्यथा अणु
			err = पूर्णांकel_pt_synth_branch_sample(ptq);
		पूर्ण
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!ptq->sync_चयन)
		वापस 0;

	अगर (पूर्णांकel_pt_is_चयन_ip(ptq, state->to_ip)) अणु
		चयन (ptq->चयन_state) अणु
		हाल INTEL_PT_SS_NOT_TRACING:
		हाल INTEL_PT_SS_UNKNOWN:
		हाल INTEL_PT_SS_EXPECTING_SWITCH_IP:
			err = पूर्णांकel_pt_next_tid(pt, ptq);
			अगर (err)
				वापस err;
			ptq->चयन_state = INTEL_PT_SS_TRACING;
			अवरोध;
		शेष:
			ptq->चयन_state = INTEL_PT_SS_EXPECTING_SWITCH_EVENT;
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (!state->to_ip) अणु
		ptq->चयन_state = INTEL_PT_SS_NOT_TRACING;
	पूर्ण अन्यथा अगर (ptq->चयन_state == INTEL_PT_SS_NOT_TRACING) अणु
		ptq->चयन_state = INTEL_PT_SS_UNKNOWN;
	पूर्ण अन्यथा अगर (ptq->चयन_state == INTEL_PT_SS_UNKNOWN &&
		   state->to_ip == pt->ptss_ip &&
		   (ptq->flags & PERF_IP_FLAG_CALL)) अणु
		ptq->चयन_state = INTEL_PT_SS_TRACING;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 पूर्णांकel_pt_चयन_ip(काष्ठा पूर्णांकel_pt *pt, u64 *ptss_ip)
अणु
	काष्ठा machine *machine = pt->machine;
	काष्ठा map *map;
	काष्ठा symbol *sym, *start;
	u64 ip, चयन_ip = 0;
	स्थिर अक्षर *ptss;

	अगर (ptss_ip)
		*ptss_ip = 0;

	map = machine__kernel_map(machine);
	अगर (!map)
		वापस 0;

	अगर (map__load(map))
		वापस 0;

	start = dso__first_symbol(map->dso);

	क्रम (sym = start; sym; sym = dso__next_symbol(sym)) अणु
		अगर (sym->binding == STB_GLOBAL &&
		    !म_भेद(sym->name, "__switch_to")) अणु
			ip = map->unmap_ip(map, sym->start);
			अगर (ip >= map->start && ip < map->end) अणु
				चयन_ip = ip;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!चयन_ip || !ptss_ip)
		वापस 0;

	अगर (pt->have_sched_चयन == 1)
		ptss = "perf_trace_sched_switch";
	अन्यथा
		ptss = "__perf_event_task_sched_out";

	क्रम (sym = start; sym; sym = dso__next_symbol(sym)) अणु
		अगर (!म_भेद(sym->name, ptss)) अणु
			ip = map->unmap_ip(map, sym->start);
			अगर (ip >= map->start && ip < map->end) अणु
				*ptss_ip = ip;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस चयन_ip;
पूर्ण

अटल व्योम पूर्णांकel_pt_enable_sync_चयन(काष्ठा पूर्णांकel_pt *pt)
अणु
	अचिन्हित पूर्णांक i;

	pt->sync_चयन = true;

	क्रम (i = 0; i < pt->queues.nr_queues; i++) अणु
		काष्ठा auxtrace_queue *queue = &pt->queues.queue_array[i];
		काष्ठा पूर्णांकel_pt_queue *ptq = queue->priv;

		अगर (ptq)
			ptq->sync_चयन = true;
	पूर्ण
पूर्ण

/*
 * To filter against समय ranges, it is only necessary to look at the next start
 * or end समय.
 */
अटल bool पूर्णांकel_pt_next_समय(काष्ठा पूर्णांकel_pt_queue *ptq)
अणु
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;

	अगर (ptq->sel_start) अणु
		/* Next समय is an end समय */
		ptq->sel_start = false;
		ptq->sel_बारtamp = pt->समय_ranges[ptq->sel_idx].end;
		वापस true;
	पूर्ण अन्यथा अगर (ptq->sel_idx + 1 < pt->range_cnt) अणु
		/* Next समय is a start समय */
		ptq->sel_start = true;
		ptq->sel_idx += 1;
		ptq->sel_बारtamp = pt->समय_ranges[ptq->sel_idx].start;
		वापस true;
	पूर्ण

	/* No next समय */
	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_समय_filter(काष्ठा पूर्णांकel_pt_queue *ptq, u64 *ff_बारtamp)
अणु
	पूर्णांक err;

	जबतक (1) अणु
		अगर (ptq->sel_start) अणु
			अगर (ptq->बारtamp >= ptq->sel_बारtamp) अणु
				/* After start समय, so consider next समय */
				पूर्णांकel_pt_next_समय(ptq);
				अगर (!ptq->sel_बारtamp) अणु
					/* No end समय */
					वापस 0;
				पूर्ण
				/* Check against end समय */
				जारी;
			पूर्ण
			/* Beक्रमe start समय, so fast क्रमward */
			ptq->have_sample = false;
			अगर (ptq->sel_बारtamp > *ff_बारtamp) अणु
				अगर (ptq->sync_चयन) अणु
					पूर्णांकel_pt_next_tid(ptq->pt, ptq);
					ptq->चयन_state = INTEL_PT_SS_UNKNOWN;
				पूर्ण
				*ff_बारtamp = ptq->sel_बारtamp;
				err = पूर्णांकel_pt_fast_क्रमward(ptq->decoder,
							    ptq->sel_बारtamp);
				अगर (err)
					वापस err;
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अगर (ptq->बारtamp > ptq->sel_बारtamp) अणु
			/* After end समय, so consider next समय */
			अगर (!पूर्णांकel_pt_next_समय(ptq)) अणु
				/* No next समय range, so stop decoding */
				ptq->have_sample = false;
				ptq->चयन_state = INTEL_PT_SS_NOT_TRACING;
				वापस 1;
			पूर्ण
			/* Check against next start समय */
			जारी;
		पूर्ण अन्यथा अणु
			/* Beक्रमe end समय */
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_run_decoder(काष्ठा पूर्णांकel_pt_queue *ptq, u64 *बारtamp)
अणु
	स्थिर काष्ठा पूर्णांकel_pt_state *state = ptq->state;
	काष्ठा पूर्णांकel_pt *pt = ptq->pt;
	u64 ff_बारtamp = 0;
	पूर्णांक err;

	अगर (!pt->kernel_start) अणु
		pt->kernel_start = machine__kernel_start(pt->machine);
		अगर (pt->per_cpu_mmaps &&
		    (pt->have_sched_चयन == 1 || pt->have_sched_चयन == 3) &&
		    !pt->समयless_decoding && पूर्णांकel_pt_tracing_kernel(pt) &&
		    !pt->sampling_mode) अणु
			pt->चयन_ip = पूर्णांकel_pt_चयन_ip(pt, &pt->ptss_ip);
			अगर (pt->चयन_ip) अणु
				पूर्णांकel_pt_log("switch_ip: %"PRIx64" ptss_ip: %"PRIx64"\n",
					     pt->चयन_ip, pt->ptss_ip);
				पूर्णांकel_pt_enable_sync_चयन(pt);
			पूर्ण
		पूर्ण
	पूर्ण

	पूर्णांकel_pt_log("queue %u decoding cpu %d pid %d tid %d\n",
		     ptq->queue_nr, ptq->cpu, ptq->pid, ptq->tid);
	जबतक (1) अणु
		err = पूर्णांकel_pt_sample(ptq);
		अगर (err)
			वापस err;

		state = पूर्णांकel_pt_decode(ptq->decoder);
		अगर (state->err) अणु
			अगर (state->err == INTEL_PT_ERR_NODATA)
				वापस 1;
			अगर (ptq->sync_चयन &&
			    state->from_ip >= pt->kernel_start) अणु
				ptq->sync_चयन = false;
				पूर्णांकel_pt_next_tid(pt, ptq);
			पूर्ण
			अगर (pt->synth_opts.errors) अणु
				err = पूर्णांकel_ptq_synth_error(ptq, state);
				अगर (err)
					वापस err;
			पूर्ण
			जारी;
		पूर्ण

		ptq->state = state;
		ptq->have_sample = true;
		पूर्णांकel_pt_sample_flags(ptq);

		/* Use estimated TSC upon वापस to user space */
		अगर (pt->est_tsc &&
		    (state->from_ip >= pt->kernel_start || !state->from_ip) &&
		    state->to_ip && state->to_ip < pt->kernel_start) अणु
			पूर्णांकel_pt_log("TSC %"PRIx64" est. TSC %"PRIx64"\n",
				     state->बारtamp, state->est_बारtamp);
			ptq->बारtamp = state->est_बारtamp;
		/* Use estimated TSC in unknown चयन state */
		पूर्ण अन्यथा अगर (ptq->sync_चयन &&
			   ptq->चयन_state == INTEL_PT_SS_UNKNOWN &&
			   पूर्णांकel_pt_is_चयन_ip(ptq, state->to_ip) &&
			   ptq->next_tid == -1) अणु
			पूर्णांकel_pt_log("TSC %"PRIx64" est. TSC %"PRIx64"\n",
				     state->बारtamp, state->est_बारtamp);
			ptq->बारtamp = state->est_बारtamp;
		पूर्ण अन्यथा अगर (state->बारtamp > ptq->बारtamp) अणु
			ptq->बारtamp = state->बारtamp;
		पूर्ण

		अगर (ptq->sel_बारtamp) अणु
			err = पूर्णांकel_pt_समय_filter(ptq, &ff_बारtamp);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (!pt->समयless_decoding && ptq->बारtamp >= *बारtamp) अणु
			*बारtamp = ptq->बारtamp;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_pt_update_queues(काष्ठा पूर्णांकel_pt *pt)
अणु
	अगर (pt->queues.new_data) अणु
		pt->queues.new_data = false;
		वापस पूर्णांकel_pt_setup_queues(pt);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_queues(काष्ठा पूर्णांकel_pt *pt, u64 बारtamp)
अणु
	अचिन्हित पूर्णांक queue_nr;
	u64 ts;
	पूर्णांक ret;

	जबतक (1) अणु
		काष्ठा auxtrace_queue *queue;
		काष्ठा पूर्णांकel_pt_queue *ptq;

		अगर (!pt->heap.heap_cnt)
			वापस 0;

		अगर (pt->heap.heap_array[0].ordinal >= बारtamp)
			वापस 0;

		queue_nr = pt->heap.heap_array[0].queue_nr;
		queue = &pt->queues.queue_array[queue_nr];
		ptq = queue->priv;

		पूर्णांकel_pt_log("queue %u processing 0x%" PRIx64 " to 0x%" PRIx64 "\n",
			     queue_nr, pt->heap.heap_array[0].ordinal,
			     बारtamp);

		auxtrace_heap__pop(&pt->heap);

		अगर (pt->heap.heap_cnt) अणु
			ts = pt->heap.heap_array[0].ordinal + 1;
			अगर (ts > बारtamp)
				ts = बारtamp;
		पूर्ण अन्यथा अणु
			ts = बारtamp;
		पूर्ण

		पूर्णांकel_pt_set_pid_tid_cpu(pt, queue);

		ret = पूर्णांकel_pt_run_decoder(ptq, &ts);

		अगर (ret < 0) अणु
			auxtrace_heap__add(&pt->heap, queue_nr, ts);
			वापस ret;
		पूर्ण

		अगर (!ret) अणु
			ret = auxtrace_heap__add(&pt->heap, queue_nr, ts);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			ptq->on_heap = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_समयless_queues(काष्ठा पूर्णांकel_pt *pt, pid_t tid,
					    u64 समय_)
अणु
	काष्ठा auxtrace_queues *queues = &pt->queues;
	अचिन्हित पूर्णांक i;
	u64 ts = 0;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		काष्ठा auxtrace_queue *queue = &pt->queues.queue_array[i];
		काष्ठा पूर्णांकel_pt_queue *ptq = queue->priv;

		अगर (ptq && (tid == -1 || ptq->tid == tid)) अणु
			ptq->समय = समय_;
			पूर्णांकel_pt_set_pid_tid_cpu(pt, queue);
			पूर्णांकel_pt_run_decoder(ptq, &ts);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_sample_set_pid_tid_cpu(काष्ठा पूर्णांकel_pt_queue *ptq,
					    काष्ठा auxtrace_queue *queue,
					    काष्ठा perf_sample *sample)
अणु
	काष्ठा machine *m = ptq->pt->machine;

	ptq->pid = sample->pid;
	ptq->tid = sample->tid;
	ptq->cpu = queue->cpu;

	पूर्णांकel_pt_log("queue %u cpu %d pid %d tid %d\n",
		     ptq->queue_nr, ptq->cpu, ptq->pid, ptq->tid);

	thपढ़ो__zput(ptq->thपढ़ो);

	अगर (ptq->tid == -1)
		वापस;

	अगर (ptq->pid == -1) अणु
		ptq->thपढ़ो = machine__find_thपढ़ो(m, -1, ptq->tid);
		अगर (ptq->thपढ़ो)
			ptq->pid = ptq->thपढ़ो->pid_;
		वापस;
	पूर्ण

	ptq->thपढ़ो = machine__findnew_thपढ़ो(m, ptq->pid, ptq->tid);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_समयless_sample(काष्ठा पूर्णांकel_pt *pt,
					    काष्ठा perf_sample *sample)
अणु
	काष्ठा auxtrace_queue *queue;
	काष्ठा पूर्णांकel_pt_queue *ptq;
	u64 ts = 0;

	queue = auxtrace_queues__sample_queue(&pt->queues, sample, pt->session);
	अगर (!queue)
		वापस -EINVAL;

	ptq = queue->priv;
	अगर (!ptq)
		वापस 0;

	ptq->stop = false;
	ptq->समय = sample->समय;
	पूर्णांकel_pt_sample_set_pid_tid_cpu(ptq, queue, sample);
	पूर्णांकel_pt_run_decoder(ptq, &ts);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_lost(काष्ठा पूर्णांकel_pt *pt, काष्ठा perf_sample *sample)
अणु
	वापस पूर्णांकel_pt_synth_error(pt, INTEL_PT_ERR_LOST, sample->cpu,
				    sample->pid, sample->tid, 0, sample->समय);
पूर्ण

अटल काष्ठा पूर्णांकel_pt_queue *पूर्णांकel_pt_cpu_to_ptq(काष्ठा पूर्णांकel_pt *pt, पूर्णांक cpu)
अणु
	अचिन्हित i, j;

	अगर (cpu < 0 || !pt->queues.nr_queues)
		वापस शून्य;

	अगर ((अचिन्हित)cpu >= pt->queues.nr_queues)
		i = pt->queues.nr_queues - 1;
	अन्यथा
		i = cpu;

	अगर (pt->queues.queue_array[i].cpu == cpu)
		वापस pt->queues.queue_array[i].priv;

	क्रम (j = 0; i > 0; j++) अणु
		अगर (pt->queues.queue_array[--i].cpu == cpu)
			वापस pt->queues.queue_array[i].priv;
	पूर्ण

	क्रम (; j < pt->queues.nr_queues; j++) अणु
		अगर (pt->queues.queue_array[j].cpu == cpu)
			वापस pt->queues.queue_array[j].priv;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_sync_चयन(काष्ठा पूर्णांकel_pt *pt, पूर्णांक cpu, pid_t tid,
				u64 बारtamp)
अणु
	काष्ठा पूर्णांकel_pt_queue *ptq;
	पूर्णांक err;

	अगर (!pt->sync_चयन)
		वापस 1;

	ptq = पूर्णांकel_pt_cpu_to_ptq(pt, cpu);
	अगर (!ptq || !ptq->sync_चयन)
		वापस 1;

	चयन (ptq->चयन_state) अणु
	हाल INTEL_PT_SS_NOT_TRACING:
		अवरोध;
	हाल INTEL_PT_SS_UNKNOWN:
	हाल INTEL_PT_SS_TRACING:
		ptq->next_tid = tid;
		ptq->चयन_state = INTEL_PT_SS_EXPECTING_SWITCH_IP;
		वापस 0;
	हाल INTEL_PT_SS_EXPECTING_SWITCH_EVENT:
		अगर (!ptq->on_heap) अणु
			ptq->बारtamp = perf_समय_प्रकारo_tsc(बारtamp,
							  &pt->tc);
			err = auxtrace_heap__add(&pt->heap, ptq->queue_nr,
						 ptq->बारtamp);
			अगर (err)
				वापस err;
			ptq->on_heap = true;
		पूर्ण
		ptq->चयन_state = INTEL_PT_SS_TRACING;
		अवरोध;
	हाल INTEL_PT_SS_EXPECTING_SWITCH_IP:
		पूर्णांकel_pt_log("ERROR: cpu %d expecting switch ip\n", cpu);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ptq->next_tid = -1;

	वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_चयन(काष्ठा पूर्णांकel_pt *pt,
				   काष्ठा perf_sample *sample)
अणु
	pid_t tid;
	पूर्णांक cpu, ret;
	काष्ठा evsel *evsel = evlist__id2evsel(pt->session->evlist, sample->id);

	अगर (evsel != pt->चयन_evsel)
		वापस 0;

	tid = evsel__पूर्णांकval(evsel, sample, "next_pid");
	cpu = sample->cpu;

	पूर्णांकel_pt_log("sched_switch: cpu %d tid %d time %"PRIu64" tsc %#"PRIx64"\n",
		     cpu, tid, sample->समय, perf_समय_प्रकारo_tsc(sample->समय,
		     &pt->tc));

	ret = पूर्णांकel_pt_sync_चयन(pt, cpu, tid, sample->समय);
	अगर (ret <= 0)
		वापस ret;

	वापस machine__set_current_tid(pt->machine, cpu, -1, tid);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_context_चयन_in(काष्ठा पूर्णांकel_pt *pt,
				      काष्ठा perf_sample *sample)
अणु
	pid_t pid = sample->pid;
	pid_t tid = sample->tid;
	पूर्णांक cpu = sample->cpu;

	अगर (pt->sync_चयन) अणु
		काष्ठा पूर्णांकel_pt_queue *ptq;

		ptq = पूर्णांकel_pt_cpu_to_ptq(pt, cpu);
		अगर (ptq && ptq->sync_चयन) अणु
			ptq->next_tid = -1;
			चयन (ptq->चयन_state) अणु
			हाल INTEL_PT_SS_NOT_TRACING:
			हाल INTEL_PT_SS_UNKNOWN:
			हाल INTEL_PT_SS_TRACING:
				अवरोध;
			हाल INTEL_PT_SS_EXPECTING_SWITCH_EVENT:
			हाल INTEL_PT_SS_EXPECTING_SWITCH_IP:
				ptq->चयन_state = INTEL_PT_SS_TRACING;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If the current tid has not been updated yet, ensure it is now that
	 * a "switch in" event has occurred.
	 */
	अगर (machine__get_current_tid(pt->machine, cpu) == tid)
		वापस 0;

	वापस machine__set_current_tid(pt->machine, cpu, pid, tid);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_context_चयन(काष्ठा पूर्णांकel_pt *pt, जोड़ perf_event *event,
				   काष्ठा perf_sample *sample)
अणु
	bool out = event->header.misc & PERF_RECORD_MISC_SWITCH_OUT;
	pid_t pid, tid;
	पूर्णांक cpu, ret;

	cpu = sample->cpu;

	अगर (pt->have_sched_चयन == 3) अणु
		अगर (!out)
			वापस पूर्णांकel_pt_context_चयन_in(pt, sample);
		अगर (event->header.type != PERF_RECORD_SWITCH_CPU_WIDE) अणु
			pr_err("Expecting CPU-wide context switch event\n");
			वापस -EINVAL;
		पूर्ण
		pid = event->context_चयन.next_prev_pid;
		tid = event->context_चयन.next_prev_tid;
	पूर्ण अन्यथा अणु
		अगर (out)
			वापस 0;
		pid = sample->pid;
		tid = sample->tid;
	पूर्ण

	अगर (tid == -1)
		पूर्णांकel_pt_log("context_switch event has no tid\n");

	ret = पूर्णांकel_pt_sync_चयन(pt, cpu, tid, sample->समय);
	अगर (ret <= 0)
		वापस ret;

	वापस machine__set_current_tid(pt->machine, cpu, pid, tid);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_itrace_start(काष्ठा पूर्णांकel_pt *pt,
					 जोड़ perf_event *event,
					 काष्ठा perf_sample *sample)
अणु
	अगर (!pt->per_cpu_mmaps)
		वापस 0;

	पूर्णांकel_pt_log("itrace_start: cpu %d pid %d tid %d time %"PRIu64" tsc %#"PRIx64"\n",
		     sample->cpu, event->itrace_start.pid,
		     event->itrace_start.tid, sample->समय,
		     perf_समय_प्रकारo_tsc(sample->समय, &pt->tc));

	वापस machine__set_current_tid(pt->machine, sample->cpu,
					event->itrace_start.pid,
					event->itrace_start.tid);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_find_map(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode, u64 addr,
			     काष्ठा addr_location *al)
अणु
	अगर (!al->map || addr < al->map->start || addr >= al->map->end) अणु
		अगर (!thपढ़ो__find_map(thपढ़ो, cpumode, addr, al))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* Invalidate all inकाष्ठाion cache entries that overlap the text poke */
अटल पूर्णांक पूर्णांकel_pt_text_poke(काष्ठा पूर्णांकel_pt *pt, जोड़ perf_event *event)
अणु
	u8 cpumode = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;
	u64 addr = event->text_poke.addr + event->text_poke.new_len - 1;
	/* Assume text poke begins in a basic block no more than 4096 bytes */
	पूर्णांक cnt = 4096 + event->text_poke.new_len;
	काष्ठा thपढ़ो *thपढ़ो = pt->unknown_thपढ़ो;
	काष्ठा addr_location al = अणु .map = शून्य पूर्ण;
	काष्ठा machine *machine = pt->machine;
	काष्ठा पूर्णांकel_pt_cache_entry *e;
	u64 offset;

	अगर (!event->text_poke.new_len)
		वापस 0;

	क्रम (; cnt; cnt--, addr--) अणु
		अगर (पूर्णांकel_pt_find_map(thपढ़ो, cpumode, addr, &al)) अणु
			अगर (addr < event->text_poke.addr)
				वापस 0;
			जारी;
		पूर्ण

		अगर (!al.map->dso || !al.map->dso->auxtrace_cache)
			जारी;

		offset = al.map->map_ip(al.map, addr);

		e = पूर्णांकel_pt_cache_lookup(al.map->dso, machine, offset);
		अगर (!e)
			जारी;

		अगर (addr + e->byte_cnt + e->length <= event->text_poke.addr) अणु
			/*
			 * No overlap. Working backwards there cannot be another
			 * basic block that overlaps the text poke अगर there is a
			 * branch inकाष्ठाion beक्रमe the text poke address.
			 */
			अगर (e->branch != INTEL_PT_BR_NO_BRANCH)
				वापस 0;
		पूर्ण अन्यथा अणु
			पूर्णांकel_pt_cache_invalidate(al.map->dso, machine, offset);
			पूर्णांकel_pt_log("Invalidated instruction cache for %s at %#"PRIx64"\n",
				     al.map->dso->दीर्घ_name, addr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_event(काष्ठा perf_session *session,
				  जोड़ perf_event *event,
				  काष्ठा perf_sample *sample,
				  काष्ठा perf_tool *tool)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);
	u64 बारtamp;
	पूर्णांक err = 0;

	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events) अणु
		pr_err("Intel Processor Trace requires ordered events\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sample->समय && sample->समय != (u64)-1)
		बारtamp = perf_समय_प्रकारo_tsc(sample->समय, &pt->tc);
	अन्यथा
		बारtamp = 0;

	अगर (बारtamp || pt->समयless_decoding) अणु
		err = पूर्णांकel_pt_update_queues(pt);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pt->समयless_decoding) अणु
		अगर (pt->sampling_mode) अणु
			अगर (sample->aux_sample.size)
				err = पूर्णांकel_pt_process_समयless_sample(pt,
								       sample);
		पूर्ण अन्यथा अगर (event->header.type == PERF_RECORD_EXIT) अणु
			err = पूर्णांकel_pt_process_समयless_queues(pt,
							       event->विभाजन.tid,
							       sample->समय);
		पूर्ण
	पूर्ण अन्यथा अगर (बारtamp) अणु
		err = पूर्णांकel_pt_process_queues(pt, बारtamp);
	पूर्ण
	अगर (err)
		वापस err;

	अगर (event->header.type == PERF_RECORD_SAMPLE) अणु
		अगर (pt->synth_opts.add_callchain && !sample->callchain)
			पूर्णांकel_pt_add_callchain(pt, sample);
		अगर (pt->synth_opts.add_last_branch && !sample->branch_stack)
			पूर्णांकel_pt_add_br_stack(pt, sample);
	पूर्ण

	अगर (event->header.type == PERF_RECORD_AUX &&
	    (event->aux.flags & PERF_AUX_FLAG_TRUNCATED) &&
	    pt->synth_opts.errors) अणु
		err = पूर्णांकel_pt_lost(pt, sample);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pt->चयन_evsel && event->header.type == PERF_RECORD_SAMPLE)
		err = पूर्णांकel_pt_process_चयन(pt, sample);
	अन्यथा अगर (event->header.type == PERF_RECORD_ITRACE_START)
		err = पूर्णांकel_pt_process_itrace_start(pt, event, sample);
	अन्यथा अगर (event->header.type == PERF_RECORD_SWITCH ||
		 event->header.type == PERF_RECORD_SWITCH_CPU_WIDE)
		err = पूर्णांकel_pt_context_चयन(pt, event, sample);

	अगर (!err && event->header.type == PERF_RECORD_TEXT_POKE)
		err = पूर्णांकel_pt_text_poke(pt, event);

	अगर (पूर्णांकel_pt_enable_logging && पूर्णांकel_pt_log_events(pt, sample->समय)) अणु
		पूर्णांकel_pt_log("event %u: cpu %d time %"PRIu64" tsc %#"PRIx64" ",
			     event->header.type, sample->cpu, sample->समय, बारtamp);
		पूर्णांकel_pt_log_event(event);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_flush(काष्ठा perf_session *session, काष्ठा perf_tool *tool)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);
	पूर्णांक ret;

	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events)
		वापस -EINVAL;

	ret = पूर्णांकel_pt_update_queues(pt);
	अगर (ret < 0)
		वापस ret;

	अगर (pt->समयless_decoding)
		वापस पूर्णांकel_pt_process_समयless_queues(pt, -1,
							MAX_TIMESTAMP - 1);

	वापस पूर्णांकel_pt_process_queues(pt, MAX_TIMESTAMP);
पूर्ण

अटल व्योम पूर्णांकel_pt_मुक्त_events(काष्ठा perf_session *session)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);
	काष्ठा auxtrace_queues *queues = &pt->queues;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		पूर्णांकel_pt_मुक्त_queue(queues->queue_array[i].priv);
		queues->queue_array[i].priv = शून्य;
	पूर्ण
	पूर्णांकel_pt_log_disable();
	auxtrace_queues__मुक्त(queues);
पूर्ण

अटल व्योम पूर्णांकel_pt_मुक्त(काष्ठा perf_session *session)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);

	auxtrace_heap__मुक्त(&pt->heap);
	पूर्णांकel_pt_मुक्त_events(session);
	session->auxtrace = शून्य;
	thपढ़ो__put(pt->unknown_thपढ़ो);
	addr_filters__निकास(&pt->filts);
	zमुक्त(&pt->chain);
	zमुक्त(&pt->filter);
	zमुक्त(&pt->समय_ranges);
	मुक्त(pt);
पूर्ण

अटल bool पूर्णांकel_pt_evsel_is_auxtrace(काष्ठा perf_session *session,
				       काष्ठा evsel *evsel)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);

	वापस evsel->core.attr.type == pt->pmu_type;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_process_auxtrace_event(काष्ठा perf_session *session,
					   जोड़ perf_event *event,
					   काष्ठा perf_tool *tool __maybe_unused)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);

	अगर (!pt->data_queued) अणु
		काष्ठा auxtrace_buffer *buffer;
		off_t data_offset;
		पूर्णांक fd = perf_data__fd(session->data);
		पूर्णांक err;

		अगर (perf_data__is_pipe(session->data)) अणु
			data_offset = 0;
		पूर्ण अन्यथा अणु
			data_offset = lseek(fd, 0, प्रस्तुत_से);
			अगर (data_offset == -1)
				वापस -त्रुटि_सं;
		पूर्ण

		err = auxtrace_queues__add_event(&pt->queues, session, event,
						 data_offset, &buffer);
		अगर (err)
			वापस err;

		/* Dump here now we have copied a piped trace out of the pipe */
		अगर (dump_trace) अणु
			अगर (auxtrace_buffer__get_data(buffer, fd)) अणु
				पूर्णांकel_pt_dump_event(pt, buffer->data,
						    buffer->size);
				auxtrace_buffer__put_data(buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_queue_data(काष्ठा perf_session *session,
			       काष्ठा perf_sample *sample,
			       जोड़ perf_event *event, u64 data_offset)
अणु
	काष्ठा पूर्णांकel_pt *pt = container_of(session->auxtrace, काष्ठा पूर्णांकel_pt,
					   auxtrace);
	u64 बारtamp;

	अगर (event) अणु
		वापस auxtrace_queues__add_event(&pt->queues, session, event,
						  data_offset, शून्य);
	पूर्ण

	अगर (sample->समय && sample->समय != (u64)-1)
		बारtamp = perf_समय_प्रकारo_tsc(sample->समय, &pt->tc);
	अन्यथा
		बारtamp = 0;

	वापस auxtrace_queues__add_sample(&pt->queues, session, sample,
					   data_offset, बारtamp);
पूर्ण

काष्ठा पूर्णांकel_pt_synth अणु
	काष्ठा perf_tool dummy_tool;
	काष्ठा perf_session *session;
पूर्ण;

अटल पूर्णांक पूर्णांकel_pt_event_synth(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample __maybe_unused,
				काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा पूर्णांकel_pt_synth *पूर्णांकel_pt_synth =
			container_of(tool, काष्ठा पूर्णांकel_pt_synth, dummy_tool);

	वापस perf_session__deliver_synth_event(पूर्णांकel_pt_synth->session, event,
						 शून्य);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_event(काष्ठा perf_session *session, स्थिर अक्षर *name,
				काष्ठा perf_event_attr *attr, u64 id)
अणु
	काष्ठा पूर्णांकel_pt_synth पूर्णांकel_pt_synth;
	पूर्णांक err;

	pr_debug("Synthesizing '%s' event with id %" PRIu64 " sample type %#" PRIx64 "\n",
		 name, id, (u64)attr->sample_type);

	स_रखो(&पूर्णांकel_pt_synth, 0, माप(काष्ठा पूर्णांकel_pt_synth));
	पूर्णांकel_pt_synth.session = session;

	err = perf_event__synthesize_attr(&पूर्णांकel_pt_synth.dummy_tool, attr, 1,
					  &id, पूर्णांकel_pt_event_synth);
	अगर (err)
		pr_err("%s: failed to synthesize '%s' event type\n",
		       __func__, name);

	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_pt_set_event_name(काष्ठा evlist *evlist, u64 id,
				    स्थिर अक्षर *name)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.id && evsel->core.id[0] == id) अणु
			अगर (evsel->name)
				zमुक्त(&evsel->name);
			evsel->name = strdup(name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा evsel *पूर्णांकel_pt_evsel(काष्ठा पूर्णांकel_pt *pt,
					 काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == pt->pmu_type && evsel->core.ids)
			वापस evsel;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_synth_events(काष्ठा पूर्णांकel_pt *pt,
				 काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel = पूर्णांकel_pt_evsel(pt, evlist);
	काष्ठा perf_event_attr attr;
	u64 id;
	पूर्णांक err;

	अगर (!evsel) अणु
		pr_debug("There are no selected events with Intel Processor Trace data\n");
		वापस 0;
	पूर्ण

	स_रखो(&attr, 0, माप(काष्ठा perf_event_attr));
	attr.size = माप(काष्ठा perf_event_attr);
	attr.type = PERF_TYPE_HARDWARE;
	attr.sample_type = evsel->core.attr.sample_type & PERF_SAMPLE_MASK;
	attr.sample_type |= PERF_SAMPLE_IP | PERF_SAMPLE_TID |
			    PERF_SAMPLE_PERIOD;
	अगर (pt->समयless_decoding)
		attr.sample_type &= ~(u64)PERF_SAMPLE_TIME;
	अन्यथा
		attr.sample_type |= PERF_SAMPLE_TIME;
	अगर (!pt->per_cpu_mmaps)
		attr.sample_type &= ~(u64)PERF_SAMPLE_CPU;
	attr.exclude_user = evsel->core.attr.exclude_user;
	attr.exclude_kernel = evsel->core.attr.exclude_kernel;
	attr.exclude_hv = evsel->core.attr.exclude_hv;
	attr.exclude_host = evsel->core.attr.exclude_host;
	attr.exclude_guest = evsel->core.attr.exclude_guest;
	attr.sample_id_all = evsel->core.attr.sample_id_all;
	attr.पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;

	id = evsel->core.id[0] + 1000000000;
	अगर (!id)
		id = 1;

	अगर (pt->synth_opts.branches) अणु
		attr.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
		attr.sample_period = 1;
		attr.sample_type |= PERF_SAMPLE_ADDR;
		err = पूर्णांकel_pt_synth_event(session, "branches", &attr, id);
		अगर (err)
			वापस err;
		pt->sample_branches = true;
		pt->branches_sample_type = attr.sample_type;
		pt->branches_id = id;
		id += 1;
		attr.sample_type &= ~(u64)PERF_SAMPLE_ADDR;
	पूर्ण

	अगर (pt->synth_opts.callchain)
		attr.sample_type |= PERF_SAMPLE_CALLCHAIN;
	अगर (pt->synth_opts.last_branch) अणु
		attr.sample_type |= PERF_SAMPLE_BRANCH_STACK;
		/*
		 * We करोn't use the hardware index, but the sample generation
		 * code uses the new क्रमmat branch_stack with this field,
		 * so the event attributes must indicate that it's present.
		 */
		attr.branch_sample_type |= PERF_SAMPLE_BRANCH_HW_INDEX;
	पूर्ण

	अगर (pt->synth_opts.inकाष्ठाions) अणु
		attr.config = PERF_COUNT_HW_INSTRUCTIONS;
		अगर (pt->synth_opts.period_type == PERF_ITRACE_PERIOD_न_अंकOSECS)
			attr.sample_period =
				पूर्णांकel_pt_ns_to_ticks(pt, pt->synth_opts.period);
		अन्यथा
			attr.sample_period = pt->synth_opts.period;
		err = पूर्णांकel_pt_synth_event(session, "instructions", &attr, id);
		अगर (err)
			वापस err;
		pt->sample_inकाष्ठाions = true;
		pt->inकाष्ठाions_sample_type = attr.sample_type;
		pt->inकाष्ठाions_id = id;
		id += 1;
	पूर्ण

	attr.sample_type &= ~(u64)PERF_SAMPLE_PERIOD;
	attr.sample_period = 1;

	अगर (pt->synth_opts.transactions) अणु
		attr.config = PERF_COUNT_HW_INSTRUCTIONS;
		err = पूर्णांकel_pt_synth_event(session, "transactions", &attr, id);
		अगर (err)
			वापस err;
		pt->sample_transactions = true;
		pt->transactions_sample_type = attr.sample_type;
		pt->transactions_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "transactions");
		id += 1;
	पूर्ण

	attr.type = PERF_TYPE_SYNTH;
	attr.sample_type |= PERF_SAMPLE_RAW;

	अगर (pt->synth_opts.ptग_लिखोs) अणु
		attr.config = PERF_SYNTH_INTEL_PTWRITE;
		err = पूर्णांकel_pt_synth_event(session, "ptwrite", &attr, id);
		अगर (err)
			वापस err;
		pt->sample_ptग_लिखोs = true;
		pt->ptग_लिखोs_sample_type = attr.sample_type;
		pt->ptग_लिखोs_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "ptwrite");
		id += 1;
	पूर्ण

	अगर (pt->synth_opts.pwr_events) अणु
		pt->sample_pwr_events = true;
		pt->pwr_events_sample_type = attr.sample_type;

		attr.config = PERF_SYNTH_INTEL_CBR;
		err = पूर्णांकel_pt_synth_event(session, "cbr", &attr, id);
		अगर (err)
			वापस err;
		pt->cbr_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "cbr");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_PSB;
		err = पूर्णांकel_pt_synth_event(session, "psb", &attr, id);
		अगर (err)
			वापस err;
		pt->psb_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "psb");
		id += 1;
	पूर्ण

	अगर (pt->synth_opts.pwr_events && (evsel->core.attr.config & 0x10)) अणु
		attr.config = PERF_SYNTH_INTEL_MWAIT;
		err = पूर्णांकel_pt_synth_event(session, "mwait", &attr, id);
		अगर (err)
			वापस err;
		pt->mरुको_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "mwait");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_PWRE;
		err = पूर्णांकel_pt_synth_event(session, "pwre", &attr, id);
		अगर (err)
			वापस err;
		pt->pwre_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "pwre");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_EXSTOP;
		err = पूर्णांकel_pt_synth_event(session, "exstop", &attr, id);
		अगर (err)
			वापस err;
		pt->exstop_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "exstop");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_PWRX;
		err = पूर्णांकel_pt_synth_event(session, "pwrx", &attr, id);
		अगर (err)
			वापस err;
		pt->pwrx_id = id;
		पूर्णांकel_pt_set_event_name(evlist, id, "pwrx");
		id += 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_setup_pebs_events(काष्ठा पूर्णांकel_pt *pt)
अणु
	काष्ठा evsel *evsel;

	अगर (!pt->synth_opts.other_events)
		वापस;

	evlist__क्रम_each_entry(pt->session->evlist, evsel) अणु
		अगर (evsel->core.attr.aux_output && evsel->core.id) अणु
			pt->sample_pebs = true;
			pt->pebs_evsel = evsel;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा evsel *पूर्णांकel_pt_find_sched_चयन(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry_reverse(evlist, evsel) अणु
		स्थिर अक्षर *name = evsel__name(evsel);

		अगर (!म_भेद(name, "sched:sched_switch"))
			वापस evsel;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool पूर्णांकel_pt_find_चयन(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.context_चयन)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_perf_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data)
अणु
	काष्ठा पूर्णांकel_pt *pt = data;

	अगर (!म_भेद(var, "intel-pt.mispred-all"))
		pt->mispred_all = perf_config_bool(var, value);

	वापस 0;
पूर्ण

/* Find least TSC which converts to ns or later */
अटल u64 पूर्णांकel_pt_tsc_start(u64 ns, काष्ठा पूर्णांकel_pt *pt)
अणु
	u64 tsc, पंचांग;

	tsc = perf_समय_प्रकारo_tsc(ns, &pt->tc);

	जबतक (1) अणु
		पंचांग = tsc_to_perf_समय(tsc, &pt->tc);
		अगर (पंचांग < ns)
			अवरोध;
		tsc -= 1;
	पूर्ण

	जबतक (पंचांग < ns)
		पंचांग = tsc_to_perf_समय(++tsc, &pt->tc);

	वापस tsc;
पूर्ण

/* Find greatest TSC which converts to ns or earlier */
अटल u64 पूर्णांकel_pt_tsc_end(u64 ns, काष्ठा पूर्णांकel_pt *pt)
अणु
	u64 tsc, पंचांग;

	tsc = perf_समय_प्रकारo_tsc(ns, &pt->tc);

	जबतक (1) अणु
		पंचांग = tsc_to_perf_समय(tsc, &pt->tc);
		अगर (पंचांग > ns)
			अवरोध;
		tsc += 1;
	पूर्ण

	जबतक (पंचांग > ns)
		पंचांग = tsc_to_perf_समय(--tsc, &pt->tc);

	वापस tsc;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_setup_समय_ranges(काष्ठा पूर्णांकel_pt *pt,
				      काष्ठा itrace_synth_opts *opts)
अणु
	काष्ठा perf_समय_पूर्णांकerval *p = opts->pसमय_range;
	पूर्णांक n = opts->range_num;
	पूर्णांक i;

	अगर (!n || !p || pt->समयless_decoding)
		वापस 0;

	pt->समय_ranges = सुस्मृति(n, माप(काष्ठा range));
	अगर (!pt->समय_ranges)
		वापस -ENOMEM;

	pt->range_cnt = n;

	पूर्णांकel_pt_log("%s: %u range(s)\n", __func__, n);

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा range *r = &pt->समय_ranges[i];
		u64 ts = p[i].start;
		u64 te = p[i].end;

		/*
		 * Take care to ensure the TSC range matches the perf-समय range
		 * when converted back to perf-समय.
		 */
		r->start = ts ? पूर्णांकel_pt_tsc_start(ts, pt) : 0;
		r->end   = te ? पूर्णांकel_pt_tsc_end(te, pt) : 0;

		पूर्णांकel_pt_log("range %d: perf time interval: %"PRIu64" to %"PRIu64"\n",
			     i, ts, te);
		पूर्णांकel_pt_log("range %d: TSC time interval: %#"PRIx64" to %#"PRIx64"\n",
			     i, r->start, r->end);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर पूर्णांकel_pt_info_fmts[] = अणु
	[INTEL_PT_PMU_TYPE]		= "  PMU Type            %"PRId64"\n",
	[INTEL_PT_TIME_SHIFT]		= "  Time Shift          %"PRIu64"\n",
	[INTEL_PT_TIME_MULT]		= "  Time Muliplier      %"PRIu64"\n",
	[INTEL_PT_TIME_ZERO]		= "  Time Zero           %"PRIu64"\n",
	[INTEL_PT_CAP_USER_TIME_ZERO]	= "  Cap Time Zero       %"PRId64"\n",
	[INTEL_PT_TSC_BIT]		= "  TSC bit             %#"PRIx64"\n",
	[INTEL_PT_NORETCOMP_BIT]	= "  NoRETComp bit       %#"PRIx64"\n",
	[INTEL_PT_HAVE_SCHED_SWITCH]	= "  Have sched_switch   %"PRId64"\n",
	[INTEL_PT_SNAPSHOT_MODE]	= "  Snapshot mode       %"PRId64"\n",
	[INTEL_PT_PER_CPU_MMAPS]	= "  Per-cpu maps        %"PRId64"\n",
	[INTEL_PT_MTC_BIT]		= "  MTC bit             %#"PRIx64"\n",
	[INTEL_PT_TSC_CTC_N]		= "  TSC:CTC numerator   %"PRIu64"\n",
	[INTEL_PT_TSC_CTC_D]		= "  TSC:CTC denominator %"PRIu64"\n",
	[INTEL_PT_CYC_BIT]		= "  CYC bit             %#"PRIx64"\n",
	[INTEL_PT_MAX_NONTURBO_RATIO]	= "  Max non-turbo ratio %"PRIu64"\n",
	[INTEL_PT_FILTER_STR_LEN]	= "  Filter string len.  %"PRIu64"\n",
पूर्ण;

अटल व्योम पूर्णांकel_pt_prपूर्णांक_info(__u64 *arr, पूर्णांक start, पूर्णांक finish)
अणु
	पूर्णांक i;

	अगर (!dump_trace)
		वापस;

	क्रम (i = start; i <= finish; i++)
		ख_लिखो(मानक_निकास, पूर्णांकel_pt_info_fmts[i], arr[i]);
पूर्ण

अटल व्योम पूर्णांकel_pt_prपूर्णांक_info_str(स्थिर अक्षर *name, स्थिर अक्षर *str)
अणु
	अगर (!dump_trace)
		वापस;

	ख_लिखो(मानक_निकास, "  %-20s%s\n", name, str ? str : "");
पूर्ण

अटल bool पूर्णांकel_pt_has(काष्ठा perf_record_auxtrace_info *auxtrace_info, पूर्णांक pos)
अणु
	वापस auxtrace_info->header.size >=
		माप(काष्ठा perf_record_auxtrace_info) + (माप(u64) * (pos + 1));
पूर्ण

पूर्णांक पूर्णांकel_pt_process_auxtrace_info(जोड़ perf_event *event,
				   काष्ठा perf_session *session)
अणु
	काष्ठा perf_record_auxtrace_info *auxtrace_info = &event->auxtrace_info;
	माप_प्रकार min_sz = माप(u64) * INTEL_PT_PER_CPU_MMAPS;
	काष्ठा पूर्णांकel_pt *pt;
	व्योम *info_end;
	__u64 *info;
	पूर्णांक err;

	अगर (auxtrace_info->header.size < माप(काष्ठा perf_record_auxtrace_info) +
					min_sz)
		वापस -EINVAL;

	pt = zalloc(माप(काष्ठा पूर्णांकel_pt));
	अगर (!pt)
		वापस -ENOMEM;

	addr_filters__init(&pt->filts);

	err = perf_config(पूर्णांकel_pt_perf_config, pt);
	अगर (err)
		जाओ err_मुक्त;

	err = auxtrace_queues__init(&pt->queues);
	अगर (err)
		जाओ err_मुक्त;

	पूर्णांकel_pt_log_set_name(INTEL_PT_PMU_NAME);

	pt->session = session;
	pt->machine = &session->machines.host; /* No kvm support */
	pt->auxtrace_type = auxtrace_info->type;
	pt->pmu_type = auxtrace_info->priv[INTEL_PT_PMU_TYPE];
	pt->tc.समय_shअगरt = auxtrace_info->priv[INTEL_PT_TIME_SHIFT];
	pt->tc.समय_mult = auxtrace_info->priv[INTEL_PT_TIME_MULT];
	pt->tc.समय_zero = auxtrace_info->priv[INTEL_PT_TIME_ZERO];
	pt->cap_user_समय_zero = auxtrace_info->priv[INTEL_PT_CAP_USER_TIME_ZERO];
	pt->tsc_bit = auxtrace_info->priv[INTEL_PT_TSC_BIT];
	pt->noretcomp_bit = auxtrace_info->priv[INTEL_PT_NORETCOMP_BIT];
	pt->have_sched_चयन = auxtrace_info->priv[INTEL_PT_HAVE_SCHED_SWITCH];
	pt->snapshot_mode = auxtrace_info->priv[INTEL_PT_SNAPSHOT_MODE];
	pt->per_cpu_mmaps = auxtrace_info->priv[INTEL_PT_PER_CPU_MMAPS];
	पूर्णांकel_pt_prपूर्णांक_info(&auxtrace_info->priv[0], INTEL_PT_PMU_TYPE,
			    INTEL_PT_PER_CPU_MMAPS);

	अगर (पूर्णांकel_pt_has(auxtrace_info, INTEL_PT_CYC_BIT)) अणु
		pt->mtc_bit = auxtrace_info->priv[INTEL_PT_MTC_BIT];
		pt->mtc_freq_bits = auxtrace_info->priv[INTEL_PT_MTC_FREQ_BITS];
		pt->tsc_ctc_ratio_n = auxtrace_info->priv[INTEL_PT_TSC_CTC_N];
		pt->tsc_ctc_ratio_d = auxtrace_info->priv[INTEL_PT_TSC_CTC_D];
		pt->cyc_bit = auxtrace_info->priv[INTEL_PT_CYC_BIT];
		पूर्णांकel_pt_prपूर्णांक_info(&auxtrace_info->priv[0], INTEL_PT_MTC_BIT,
				    INTEL_PT_CYC_BIT);
	पूर्ण

	अगर (पूर्णांकel_pt_has(auxtrace_info, INTEL_PT_MAX_NONTURBO_RATIO)) अणु
		pt->max_non_turbo_ratio =
			auxtrace_info->priv[INTEL_PT_MAX_NONTURBO_RATIO];
		पूर्णांकel_pt_prपूर्णांक_info(&auxtrace_info->priv[0],
				    INTEL_PT_MAX_NONTURBO_RATIO,
				    INTEL_PT_MAX_NONTURBO_RATIO);
	पूर्ण

	info = &auxtrace_info->priv[INTEL_PT_FILTER_STR_LEN] + 1;
	info_end = (व्योम *)info + auxtrace_info->header.size;

	अगर (पूर्णांकel_pt_has(auxtrace_info, INTEL_PT_FILTER_STR_LEN)) अणु
		माप_प्रकार len;

		len = auxtrace_info->priv[INTEL_PT_FILTER_STR_LEN];
		पूर्णांकel_pt_prपूर्णांक_info(&auxtrace_info->priv[0],
				    INTEL_PT_FILTER_STR_LEN,
				    INTEL_PT_FILTER_STR_LEN);
		अगर (len) अणु
			स्थिर अक्षर *filter = (स्थिर अक्षर *)info;

			len = roundup(len + 1, 8);
			info += len >> 3;
			अगर ((व्योम *)info > info_end) अणु
				pr_err("%s: bad filter string length\n", __func__);
				err = -EINVAL;
				जाओ err_मुक्त_queues;
			पूर्ण
			pt->filter = memdup(filter, len);
			अगर (!pt->filter) अणु
				err = -ENOMEM;
				जाओ err_मुक्त_queues;
			पूर्ण
			अगर (session->header.needs_swap)
				mem_bswap_64(pt->filter, len);
			अगर (pt->filter[len - 1]) अणु
				pr_err("%s: filter string not null terminated\n", __func__);
				err = -EINVAL;
				जाओ err_मुक्त_queues;
			पूर्ण
			err = addr_filters__parse_bare_filter(&pt->filts,
							      filter);
			अगर (err)
				जाओ err_मुक्त_queues;
		पूर्ण
		पूर्णांकel_pt_prपूर्णांक_info_str("Filter string", pt->filter);
	पूर्ण

	pt->समयless_decoding = पूर्णांकel_pt_समयless_decoding(pt);
	अगर (pt->समयless_decoding && !pt->tc.समय_mult)
		pt->tc.समय_mult = 1;
	pt->have_tsc = पूर्णांकel_pt_have_tsc(pt);
	pt->sampling_mode = पूर्णांकel_pt_sampling_mode(pt);
	pt->est_tsc = !pt->समयless_decoding;

	pt->unknown_thपढ़ो = thपढ़ो__new(999999999, 999999999);
	अगर (!pt->unknown_thपढ़ो) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_queues;
	पूर्ण

	/*
	 * Since this thपढ़ो will not be kept in any rbtree not in a
	 * list, initialize its list node so that at thपढ़ो__put() the
	 * current thपढ़ो lअगरeसमय assumption is kept and we करोn't segfault
	 * at list_del_init().
	 */
	INIT_LIST_HEAD(&pt->unknown_thपढ़ो->node);

	err = thपढ़ो__set_comm(pt->unknown_thपढ़ो, "unknown", 0);
	अगर (err)
		जाओ err_delete_thपढ़ो;
	अगर (thपढ़ो__init_maps(pt->unknown_thपढ़ो, pt->machine)) अणु
		err = -ENOMEM;
		जाओ err_delete_thपढ़ो;
	पूर्ण

	pt->auxtrace.process_event = पूर्णांकel_pt_process_event;
	pt->auxtrace.process_auxtrace_event = पूर्णांकel_pt_process_auxtrace_event;
	pt->auxtrace.queue_data = पूर्णांकel_pt_queue_data;
	pt->auxtrace.dump_auxtrace_sample = पूर्णांकel_pt_dump_sample;
	pt->auxtrace.flush_events = पूर्णांकel_pt_flush;
	pt->auxtrace.मुक्त_events = पूर्णांकel_pt_मुक्त_events;
	pt->auxtrace.मुक्त = पूर्णांकel_pt_मुक्त;
	pt->auxtrace.evsel_is_auxtrace = पूर्णांकel_pt_evsel_is_auxtrace;
	session->auxtrace = &pt->auxtrace;

	अगर (dump_trace)
		वापस 0;

	अगर (pt->have_sched_चयन == 1) अणु
		pt->चयन_evsel = पूर्णांकel_pt_find_sched_चयन(session->evlist);
		अगर (!pt->चयन_evsel) अणु
			pr_err("%s: missing sched_switch event\n", __func__);
			err = -EINVAL;
			जाओ err_delete_thपढ़ो;
		पूर्ण
	पूर्ण अन्यथा अगर (pt->have_sched_चयन == 2 &&
		   !पूर्णांकel_pt_find_चयन(session->evlist)) अणु
		pr_err("%s: missing context_switch attribute flag\n", __func__);
		err = -EINVAL;
		जाओ err_delete_thपढ़ो;
	पूर्ण

	अगर (session->itrace_synth_opts->set) अणु
		pt->synth_opts = *session->itrace_synth_opts;
	पूर्ण अन्यथा अणु
		itrace_synth_opts__set_शेष(&pt->synth_opts,
				session->itrace_synth_opts->शेष_no_sample);
		अगर (!session->itrace_synth_opts->शेष_no_sample &&
		    !session->itrace_synth_opts->inject) अणु
			pt->synth_opts.branches = false;
			pt->synth_opts.callchain = true;
			pt->synth_opts.add_callchain = true;
		पूर्ण
		pt->synth_opts.thपढ़ो_stack =
				session->itrace_synth_opts->thपढ़ो_stack;
	पूर्ण

	अगर (pt->synth_opts.log)
		पूर्णांकel_pt_log_enable();

	/* Maximum non-turbo ratio is TSC freq / 100 MHz */
	अगर (pt->tc.समय_mult) अणु
		u64 tsc_freq = पूर्णांकel_pt_ns_to_ticks(pt, 1000000000);

		अगर (!pt->max_non_turbo_ratio)
			pt->max_non_turbo_ratio =
					(tsc_freq + 50000000) / 100000000;
		पूर्णांकel_pt_log("TSC frequency %"PRIu64"\n", tsc_freq);
		पूर्णांकel_pt_log("Maximum non-turbo ratio %u\n",
			     pt->max_non_turbo_ratio);
		pt->cbr2khz = tsc_freq / pt->max_non_turbo_ratio / 1000;
	पूर्ण

	err = पूर्णांकel_pt_setup_समय_ranges(pt, session->itrace_synth_opts);
	अगर (err)
		जाओ err_delete_thपढ़ो;

	अगर (pt->synth_opts.calls)
		pt->branches_filter |= PERF_IP_FLAG_CALL | PERF_IP_FLAG_ASYNC |
				       PERF_IP_FLAG_TRACE_END;
	अगर (pt->synth_opts.वापसs)
		pt->branches_filter |= PERF_IP_FLAG_RETURN |
				       PERF_IP_FLAG_TRACE_BEGIN;

	अगर ((pt->synth_opts.callchain || pt->synth_opts.add_callchain) &&
	    !symbol_conf.use_callchain) अणु
		symbol_conf.use_callchain = true;
		अगर (callchain_रेजिस्टर_param(&callchain_param) < 0) अणु
			symbol_conf.use_callchain = false;
			pt->synth_opts.callchain = false;
			pt->synth_opts.add_callchain = false;
		पूर्ण
	पूर्ण

	अगर (pt->synth_opts.add_callchain) अणु
		err = पूर्णांकel_pt_callchain_init(pt);
		अगर (err)
			जाओ err_delete_thपढ़ो;
	पूर्ण

	अगर (pt->synth_opts.last_branch || pt->synth_opts.add_last_branch) अणु
		pt->br_stack_sz = pt->synth_opts.last_branch_sz;
		pt->br_stack_sz_plus = pt->br_stack_sz;
	पूर्ण

	अगर (pt->synth_opts.add_last_branch) अणु
		err = पूर्णांकel_pt_br_stack_init(pt);
		अगर (err)
			जाओ err_delete_thपढ़ो;
		/*
		 * Additional branch stack size to cater क्रम tracing from the
		 * actual sample ip to where the sample समय is recorded.
		 * Measured at about 200 branches, but generously set to 1024.
		 * If kernel space is not being traced, then add just 1 क्रम the
		 * branch to kernel space.
		 */
		अगर (पूर्णांकel_pt_tracing_kernel(pt))
			pt->br_stack_sz_plus += 1024;
		अन्यथा
			pt->br_stack_sz_plus += 1;
	पूर्ण

	pt->use_thपढ़ो_stack = pt->synth_opts.callchain ||
			       pt->synth_opts.add_callchain ||
			       pt->synth_opts.thपढ़ो_stack ||
			       pt->synth_opts.last_branch ||
			       pt->synth_opts.add_last_branch;

	pt->callstack = pt->synth_opts.callchain ||
			pt->synth_opts.add_callchain ||
			pt->synth_opts.thपढ़ो_stack;

	err = पूर्णांकel_pt_synth_events(pt, session);
	अगर (err)
		जाओ err_delete_thपढ़ो;

	पूर्णांकel_pt_setup_pebs_events(pt);

	अगर (pt->sampling_mode || list_empty(&session->auxtrace_index))
		err = auxtrace_queue_data(session, true, true);
	अन्यथा
		err = auxtrace_queues__process_index(&pt->queues, session);
	अगर (err)
		जाओ err_delete_thपढ़ो;

	अगर (pt->queues.populated)
		pt->data_queued = true;

	अगर (pt->समयless_decoding)
		pr_debug2("Intel PT decoding without timestamps\n");

	वापस 0;

err_delete_thपढ़ो:
	zमुक्त(&pt->chain);
	thपढ़ो__zput(pt->unknown_thपढ़ो);
err_मुक्त_queues:
	पूर्णांकel_pt_log_disable();
	auxtrace_queues__मुक्त(&pt->queues);
	session->auxtrace = शून्य;
err_मुक्त:
	addr_filters__निकास(&pt->filts);
	zमुक्त(&pt->filter);
	zमुक्त(&pt->समय_ranges);
	मुक्त(pt);
	वापस err;
पूर्ण
