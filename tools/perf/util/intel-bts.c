<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel-bts.c: Intel Processor Trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#समावेश <endian.h>
#समावेश <त्रुटिसं.स>
#समावेश <byteswap.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>

#समावेश "color.h"
#समावेश "evsel.h"
#समावेश "evlist.h"
#समावेश "machine.h"
#समावेश "symbol.h"
#समावेश "session.h"
#समावेश "tool.h"
#समावेश "thread.h"
#समावेश "thread-stack.h"
#समावेश "debug.h"
#समावेश "tsc.h"
#समावेश "auxtrace.h"
#समावेश "intel-pt-decoder/intel-pt-insn-decoder.h"
#समावेश "intel-bts.h"
#समावेश "util/synthetic-events.h"

#घोषणा MAX_TIMESTAMP (~0ULL)

#घोषणा INTEL_BTS_ERR_NOINSN  5
#घोषणा INTEL_BTS_ERR_LOST    9

#अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा le64_to_cpu bswap_64
#अन्यथा
#घोषणा le64_to_cpu
#पूर्ण_अगर

काष्ठा पूर्णांकel_bts अणु
	काष्ठा auxtrace			auxtrace;
	काष्ठा auxtrace_queues		queues;
	काष्ठा auxtrace_heap		heap;
	u32				auxtrace_type;
	काष्ठा perf_session		*session;
	काष्ठा machine			*machine;
	bool				sampling_mode;
	bool				snapshot_mode;
	bool				data_queued;
	u32				pmu_type;
	काष्ठा perf_tsc_conversion	tc;
	bool				cap_user_समय_zero;
	काष्ठा itrace_synth_opts	synth_opts;
	bool				sample_branches;
	u32				branches_filter;
	u64				branches_sample_type;
	u64				branches_id;
	माप_प्रकार				branches_event_size;
	अचिन्हित दीर्घ			num_events;
पूर्ण;

काष्ठा पूर्णांकel_bts_queue अणु
	काष्ठा पूर्णांकel_bts	*bts;
	अचिन्हित पूर्णांक		queue_nr;
	काष्ठा auxtrace_buffer	*buffer;
	bool			on_heap;
	bool			करोne;
	pid_t			pid;
	pid_t			tid;
	पूर्णांक			cpu;
	u64			समय;
	काष्ठा पूर्णांकel_pt_insn	पूर्णांकel_pt_insn;
	u32			sample_flags;
पूर्ण;

काष्ठा branch अणु
	u64 from;
	u64 to;
	u64 misc;
पूर्ण;

अटल व्योम पूर्णांकel_bts_dump(काष्ठा पूर्णांकel_bts *bts __maybe_unused,
			   अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा branch *branch;
	माप_प्रकार i, pos = 0, br_sz = माप(काष्ठा branch), sz;
	स्थिर अक्षर *color = PERF_COLOR_BLUE;

	color_ख_लिखो(मानक_निकास, color,
		      ". ... Intel BTS data: size %zu bytes\n",
		      len);

	जबतक (len) अणु
		अगर (len >= br_sz)
			sz = br_sz;
		अन्यथा
			sz = len;
		म_लिखो(".");
		color_ख_लिखो(मानक_निकास, color, "  %08x: ", pos);
		क्रम (i = 0; i < sz; i++)
			color_ख_लिखो(मानक_निकास, color, " %02x", buf[i]);
		क्रम (; i < br_sz; i++)
			color_ख_लिखो(मानक_निकास, color, "   ");
		अगर (len >= br_sz) अणु
			branch = (काष्ठा branch *)buf;
			color_ख_लिखो(मानक_निकास, color, " %"PRIx64" -> %"PRIx64" %s\n",
				      le64_to_cpu(branch->from),
				      le64_to_cpu(branch->to),
				      le64_to_cpu(branch->misc) & 0x10 ?
							"pred" : "miss");
		पूर्ण अन्यथा अणु
			color_ख_लिखो(मानक_निकास, color, " Bad record!\n");
		पूर्ण
		pos += sz;
		buf += sz;
		len -= sz;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_bts_dump_event(काष्ठा पूर्णांकel_bts *bts, अचिन्हित अक्षर *buf,
				 माप_प्रकार len)
अणु
	म_लिखो(".\n");
	पूर्णांकel_bts_dump(bts, buf, len);
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_lost(काष्ठा पूर्णांकel_bts *bts, काष्ठा perf_sample *sample)
अणु
	जोड़ perf_event event;
	पूर्णांक err;

	auxtrace_synth_error(&event.auxtrace_error, PERF_AUXTRACE_ERROR_ITRACE,
			     INTEL_BTS_ERR_LOST, sample->cpu, sample->pid,
			     sample->tid, 0, "Lost trace data", sample->समय);

	err = perf_session__deliver_synth_event(bts->session, &event, शून्य);
	अगर (err)
		pr_err("Intel BTS: failed to deliver error event, error %d\n",
		       err);

	वापस err;
पूर्ण

अटल काष्ठा पूर्णांकel_bts_queue *पूर्णांकel_bts_alloc_queue(काष्ठा पूर्णांकel_bts *bts,
						     अचिन्हित पूर्णांक queue_nr)
अणु
	काष्ठा पूर्णांकel_bts_queue *btsq;

	btsq = zalloc(माप(काष्ठा पूर्णांकel_bts_queue));
	अगर (!btsq)
		वापस शून्य;

	btsq->bts = bts;
	btsq->queue_nr = queue_nr;
	btsq->pid = -1;
	btsq->tid = -1;
	btsq->cpu = -1;

	वापस btsq;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_setup_queue(काष्ठा पूर्णांकel_bts *bts,
				 काष्ठा auxtrace_queue *queue,
				 अचिन्हित पूर्णांक queue_nr)
अणु
	काष्ठा पूर्णांकel_bts_queue *btsq = queue->priv;

	अगर (list_empty(&queue->head))
		वापस 0;

	अगर (!btsq) अणु
		btsq = पूर्णांकel_bts_alloc_queue(bts, queue_nr);
		अगर (!btsq)
			वापस -ENOMEM;
		queue->priv = btsq;

		अगर (queue->cpu != -1)
			btsq->cpu = queue->cpu;
		btsq->tid = queue->tid;
	पूर्ण

	अगर (bts->sampling_mode)
		वापस 0;

	अगर (!btsq->on_heap && !btsq->buffer) अणु
		पूर्णांक ret;

		btsq->buffer = auxtrace_buffer__next(queue, शून्य);
		अगर (!btsq->buffer)
			वापस 0;

		ret = auxtrace_heap__add(&bts->heap, queue_nr,
					 btsq->buffer->reference);
		अगर (ret)
			वापस ret;
		btsq->on_heap = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_setup_queues(काष्ठा पूर्णांकel_bts *bts)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < bts->queues.nr_queues; i++) अणु
		ret = पूर्णांकel_bts_setup_queue(bts, &bts->queues.queue_array[i],
					    i);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_bts_update_queues(काष्ठा पूर्णांकel_bts *bts)
अणु
	अगर (bts->queues.new_data) अणु
		bts->queues.new_data = false;
		वापस पूर्णांकel_bts_setup_queues(bts);
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर *पूर्णांकel_bts_find_overlap(अचिन्हित अक्षर *buf_a, माप_प्रकार len_a,
					     अचिन्हित अक्षर *buf_b, माप_प्रकार len_b)
अणु
	माप_प्रकार offs, len;

	अगर (len_a > len_b)
		offs = len_a - len_b;
	अन्यथा
		offs = 0;

	क्रम (; offs < len_a; offs += माप(काष्ठा branch)) अणु
		len = len_a - offs;
		अगर (!स_भेद(buf_a + offs, buf_b, len))
			वापस buf_b + len;
	पूर्ण

	वापस buf_b;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_करो_fix_overlap(काष्ठा auxtrace_queue *queue,
				    काष्ठा auxtrace_buffer *b)
अणु
	काष्ठा auxtrace_buffer *a;
	व्योम *start;

	अगर (b->list.prev == &queue->head)
		वापस 0;
	a = list_entry(b->list.prev, काष्ठा auxtrace_buffer, list);
	start = पूर्णांकel_bts_find_overlap(a->data, a->size, b->data, b->size);
	अगर (!start)
		वापस -EINVAL;
	b->use_size = b->data + b->size - start;
	b->use_data = start;
	वापस 0;
पूर्ण

अटल अंतरभूत u8 पूर्णांकel_bts_cpumode(काष्ठा पूर्णांकel_bts *bts, uपूर्णांक64_t ip)
अणु
	वापस machine__kernel_ip(bts->machine, ip) ?
	       PERF_RECORD_MISC_KERNEL :
	       PERF_RECORD_MISC_USER;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_synth_branch_sample(काष्ठा पूर्णांकel_bts_queue *btsq,
					 काष्ठा branch *branch)
अणु
	पूर्णांक ret;
	काष्ठा पूर्णांकel_bts *bts = btsq->bts;
	जोड़ perf_event event;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;

	अगर (bts->synth_opts.initial_skip &&
	    bts->num_events++ <= bts->synth_opts.initial_skip)
		वापस 0;

	sample.ip = le64_to_cpu(branch->from);
	sample.cpumode = पूर्णांकel_bts_cpumode(bts, sample.ip);
	sample.pid = btsq->pid;
	sample.tid = btsq->tid;
	sample.addr = le64_to_cpu(branch->to);
	sample.id = btsq->bts->branches_id;
	sample.stream_id = btsq->bts->branches_id;
	sample.period = 1;
	sample.cpu = btsq->cpu;
	sample.flags = btsq->sample_flags;
	sample.insn_len = btsq->पूर्णांकel_pt_insn.length;
	स_नकल(sample.insn, btsq->पूर्णांकel_pt_insn.buf, INTEL_PT_INSN_BUF_SZ);

	event.sample.header.type = PERF_RECORD_SAMPLE;
	event.sample.header.misc = sample.cpumode;
	event.sample.header.size = माप(काष्ठा perf_event_header);

	अगर (bts->synth_opts.inject) अणु
		event.sample.header.size = bts->branches_event_size;
		ret = perf_event__synthesize_sample(&event,
						    bts->branches_sample_type,
						    0, &sample);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = perf_session__deliver_synth_event(bts->session, &event, &sample);
	अगर (ret)
		pr_err("Intel BTS: failed to deliver branch event, error %d\n",
		       ret);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_get_next_insn(काष्ठा पूर्णांकel_bts_queue *btsq, u64 ip)
अणु
	काष्ठा machine *machine = btsq->bts->machine;
	काष्ठा thपढ़ो *thपढ़ो;
	अचिन्हित अक्षर buf[INTEL_PT_INSN_BUF_SZ];
	sमाप_प्रकार len;
	bool x86_64;
	पूर्णांक err = -1;

	thपढ़ो = machine__find_thपढ़ो(machine, -1, btsq->tid);
	अगर (!thपढ़ो)
		वापस -1;

	len = thपढ़ो__स_नकल(thपढ़ो, machine, buf, ip, INTEL_PT_INSN_BUF_SZ, &x86_64);
	अगर (len <= 0)
		जाओ out_put;

	अगर (पूर्णांकel_pt_get_insn(buf, len, x86_64, &btsq->पूर्णांकel_pt_insn))
		जाओ out_put;

	err = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_synth_error(काष्ठा पूर्णांकel_bts *bts, पूर्णांक cpu, pid_t pid,
				 pid_t tid, u64 ip)
अणु
	जोड़ perf_event event;
	पूर्णांक err;

	auxtrace_synth_error(&event.auxtrace_error, PERF_AUXTRACE_ERROR_ITRACE,
			     INTEL_BTS_ERR_NOINSN, cpu, pid, tid, ip,
			     "Failed to get instruction", 0);

	err = perf_session__deliver_synth_event(bts->session, &event, शून्य);
	अगर (err)
		pr_err("Intel BTS: failed to deliver error event, error %d\n",
		       err);

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_get_branch_type(काष्ठा पूर्णांकel_bts_queue *btsq,
				     काष्ठा branch *branch)
अणु
	पूर्णांक err;

	अगर (!branch->from) अणु
		अगर (branch->to)
			btsq->sample_flags = PERF_IP_FLAG_BRANCH |
					     PERF_IP_FLAG_TRACE_BEGIN;
		अन्यथा
			btsq->sample_flags = 0;
		btsq->पूर्णांकel_pt_insn.length = 0;
	पूर्ण अन्यथा अगर (!branch->to) अणु
		btsq->sample_flags = PERF_IP_FLAG_BRANCH |
				     PERF_IP_FLAG_TRACE_END;
		btsq->पूर्णांकel_pt_insn.length = 0;
	पूर्ण अन्यथा अणु
		err = पूर्णांकel_bts_get_next_insn(btsq, branch->from);
		अगर (err) अणु
			btsq->sample_flags = 0;
			btsq->पूर्णांकel_pt_insn.length = 0;
			अगर (!btsq->bts->synth_opts.errors)
				वापस 0;
			err = पूर्णांकel_bts_synth_error(btsq->bts, btsq->cpu,
						    btsq->pid, btsq->tid,
						    branch->from);
			वापस err;
		पूर्ण
		btsq->sample_flags = पूर्णांकel_pt_insn_type(btsq->पूर्णांकel_pt_insn.op);
		/* Check क्रम an async branch पूर्णांकo the kernel */
		अगर (!machine__kernel_ip(btsq->bts->machine, branch->from) &&
		    machine__kernel_ip(btsq->bts->machine, branch->to) &&
		    btsq->sample_flags != (PERF_IP_FLAG_BRANCH |
					   PERF_IP_FLAG_CALL |
					   PERF_IP_FLAG_SYSCALLRET))
			btsq->sample_flags = PERF_IP_FLAG_BRANCH |
					     PERF_IP_FLAG_CALL |
					     PERF_IP_FLAG_ASYNC |
					     PERF_IP_FLAG_INTERRUPT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_process_buffer(काष्ठा पूर्णांकel_bts_queue *btsq,
				    काष्ठा auxtrace_buffer *buffer,
				    काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा branch *branch;
	माप_प्रकार sz, bsz = माप(काष्ठा branch);
	u32 filter = btsq->bts->branches_filter;
	पूर्णांक err = 0;

	अगर (buffer->use_data) अणु
		sz = buffer->use_size;
		branch = buffer->use_data;
	पूर्ण अन्यथा अणु
		sz = buffer->size;
		branch = buffer->data;
	पूर्ण

	अगर (!btsq->bts->sample_branches)
		वापस 0;

	क्रम (; sz > bsz; branch += 1, sz -= bsz) अणु
		अगर (!branch->from && !branch->to)
			जारी;
		पूर्णांकel_bts_get_branch_type(btsq, branch);
		अगर (btsq->bts->synth_opts.thपढ़ो_stack)
			thपढ़ो_stack__event(thपढ़ो, btsq->cpu, btsq->sample_flags,
					    le64_to_cpu(branch->from),
					    le64_to_cpu(branch->to),
					    btsq->पूर्णांकel_pt_insn.length,
					    buffer->buffer_nr + 1, true, 0, 0);
		अगर (filter && !(filter & btsq->sample_flags))
			जारी;
		err = पूर्णांकel_bts_synth_branch_sample(btsq, branch);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_process_queue(काष्ठा पूर्णांकel_bts_queue *btsq, u64 *बारtamp)
अणु
	काष्ठा auxtrace_buffer *buffer = btsq->buffer, *old_buffer = buffer;
	काष्ठा auxtrace_queue *queue;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक err;

	अगर (btsq->करोne)
		वापस 1;

	अगर (btsq->pid == -1) अणु
		thपढ़ो = machine__find_thपढ़ो(btsq->bts->machine, -1,
					      btsq->tid);
		अगर (thपढ़ो)
			btsq->pid = thपढ़ो->pid_;
	पूर्ण अन्यथा अणु
		thपढ़ो = machine__findnew_thपढ़ो(btsq->bts->machine, btsq->pid,
						 btsq->tid);
	पूर्ण

	queue = &btsq->bts->queues.queue_array[btsq->queue_nr];

	अगर (!buffer)
		buffer = auxtrace_buffer__next(queue, शून्य);

	अगर (!buffer) अणु
		अगर (!btsq->bts->sampling_mode)
			btsq->करोne = 1;
		err = 1;
		जाओ out_put;
	पूर्ण

	/* Currently there is no support क्रम split buffers */
	अगर (buffer->consecutive) अणु
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	अगर (!buffer->data) अणु
		पूर्णांक fd = perf_data__fd(btsq->bts->session->data);

		buffer->data = auxtrace_buffer__get_data(buffer, fd);
		अगर (!buffer->data) अणु
			err = -ENOMEM;
			जाओ out_put;
		पूर्ण
	पूर्ण

	अगर (btsq->bts->snapshot_mode && !buffer->consecutive &&
	    पूर्णांकel_bts_करो_fix_overlap(queue, buffer)) अणु
		err = -ENOMEM;
		जाओ out_put;
	पूर्ण

	अगर (!btsq->bts->synth_opts.callchain &&
	    !btsq->bts->synth_opts.thपढ़ो_stack && thपढ़ो &&
	    (!old_buffer || btsq->bts->sampling_mode ||
	     (btsq->bts->snapshot_mode && !buffer->consecutive)))
		thपढ़ो_stack__set_trace_nr(thपढ़ो, btsq->cpu, buffer->buffer_nr + 1);

	err = पूर्णांकel_bts_process_buffer(btsq, buffer, thपढ़ो);

	auxtrace_buffer__drop_data(buffer);

	btsq->buffer = auxtrace_buffer__next(queue, buffer);
	अगर (btsq->buffer) अणु
		अगर (बारtamp)
			*बारtamp = btsq->buffer->reference;
	पूर्ण अन्यथा अणु
		अगर (!btsq->bts->sampling_mode)
			btsq->करोne = 1;
	पूर्ण
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_flush_queue(काष्ठा पूर्णांकel_bts_queue *btsq)
अणु
	u64 ts = 0;
	पूर्णांक ret;

	जबतक (1) अणु
		ret = पूर्णांकel_bts_process_queue(btsq, &ts);
		अगर (ret < 0)
			वापस ret;
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_process_tid_निकास(काष्ठा पूर्णांकel_bts *bts, pid_t tid)
अणु
	काष्ठा auxtrace_queues *queues = &bts->queues;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		काष्ठा auxtrace_queue *queue = &bts->queues.queue_array[i];
		काष्ठा पूर्णांकel_bts_queue *btsq = queue->priv;

		अगर (btsq && btsq->tid == tid)
			वापस पूर्णांकel_bts_flush_queue(btsq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_process_queues(काष्ठा पूर्णांकel_bts *bts, u64 बारtamp)
अणु
	जबतक (1) अणु
		अचिन्हित पूर्णांक queue_nr;
		काष्ठा auxtrace_queue *queue;
		काष्ठा पूर्णांकel_bts_queue *btsq;
		u64 ts = 0;
		पूर्णांक ret;

		अगर (!bts->heap.heap_cnt)
			वापस 0;

		अगर (bts->heap.heap_array[0].ordinal > बारtamp)
			वापस 0;

		queue_nr = bts->heap.heap_array[0].queue_nr;
		queue = &bts->queues.queue_array[queue_nr];
		btsq = queue->priv;

		auxtrace_heap__pop(&bts->heap);

		ret = पूर्णांकel_bts_process_queue(btsq, &ts);
		अगर (ret < 0) अणु
			auxtrace_heap__add(&bts->heap, queue_nr, ts);
			वापस ret;
		पूर्ण

		अगर (!ret) अणु
			ret = auxtrace_heap__add(&bts->heap, queue_nr, ts);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			btsq->on_heap = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_process_event(काष्ठा perf_session *session,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा perf_tool *tool)
अणु
	काष्ठा पूर्णांकel_bts *bts = container_of(session->auxtrace, काष्ठा पूर्णांकel_bts,
					     auxtrace);
	u64 बारtamp;
	पूर्णांक err;

	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events) अणु
		pr_err("Intel BTS requires ordered events\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sample->समय && sample->समय != (u64)-1)
		बारtamp = perf_समय_प्रकारo_tsc(sample->समय, &bts->tc);
	अन्यथा
		बारtamp = 0;

	err = पूर्णांकel_bts_update_queues(bts);
	अगर (err)
		वापस err;

	err = पूर्णांकel_bts_process_queues(bts, बारtamp);
	अगर (err)
		वापस err;
	अगर (event->header.type == PERF_RECORD_EXIT) अणु
		err = पूर्णांकel_bts_process_tid_निकास(bts, event->विभाजन.tid);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (event->header.type == PERF_RECORD_AUX &&
	    (event->aux.flags & PERF_AUX_FLAG_TRUNCATED) &&
	    bts->synth_opts.errors)
		err = पूर्णांकel_bts_lost(bts, sample);

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_process_auxtrace_event(काष्ठा perf_session *session,
					    जोड़ perf_event *event,
					    काष्ठा perf_tool *tool __maybe_unused)
अणु
	काष्ठा पूर्णांकel_bts *bts = container_of(session->auxtrace, काष्ठा पूर्णांकel_bts,
					     auxtrace);

	अगर (bts->sampling_mode)
		वापस 0;

	अगर (!bts->data_queued) अणु
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

		err = auxtrace_queues__add_event(&bts->queues, session, event,
						 data_offset, &buffer);
		अगर (err)
			वापस err;

		/* Dump here now we have copied a piped trace out of the pipe */
		अगर (dump_trace) अणु
			अगर (auxtrace_buffer__get_data(buffer, fd)) अणु
				पूर्णांकel_bts_dump_event(bts, buffer->data,
						     buffer->size);
				auxtrace_buffer__put_data(buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_flush(काष्ठा perf_session *session,
			   काष्ठा perf_tool *tool __maybe_unused)
अणु
	काष्ठा पूर्णांकel_bts *bts = container_of(session->auxtrace, काष्ठा पूर्णांकel_bts,
					     auxtrace);
	पूर्णांक ret;

	अगर (dump_trace || bts->sampling_mode)
		वापस 0;

	अगर (!tool->ordered_events)
		वापस -EINVAL;

	ret = पूर्णांकel_bts_update_queues(bts);
	अगर (ret < 0)
		वापस ret;

	वापस पूर्णांकel_bts_process_queues(bts, MAX_TIMESTAMP);
पूर्ण

अटल व्योम पूर्णांकel_bts_मुक्त_queue(व्योम *priv)
अणु
	काष्ठा पूर्णांकel_bts_queue *btsq = priv;

	अगर (!btsq)
		वापस;
	मुक्त(btsq);
पूर्ण

अटल व्योम पूर्णांकel_bts_मुक्त_events(काष्ठा perf_session *session)
अणु
	काष्ठा पूर्णांकel_bts *bts = container_of(session->auxtrace, काष्ठा पूर्णांकel_bts,
					     auxtrace);
	काष्ठा auxtrace_queues *queues = &bts->queues;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		पूर्णांकel_bts_मुक्त_queue(queues->queue_array[i].priv);
		queues->queue_array[i].priv = शून्य;
	पूर्ण
	auxtrace_queues__मुक्त(queues);
पूर्ण

अटल व्योम पूर्णांकel_bts_मुक्त(काष्ठा perf_session *session)
अणु
	काष्ठा पूर्णांकel_bts *bts = container_of(session->auxtrace, काष्ठा पूर्णांकel_bts,
					     auxtrace);

	auxtrace_heap__मुक्त(&bts->heap);
	पूर्णांकel_bts_मुक्त_events(session);
	session->auxtrace = शून्य;
	मुक्त(bts);
पूर्ण

अटल bool पूर्णांकel_bts_evsel_is_auxtrace(काष्ठा perf_session *session,
					काष्ठा evsel *evsel)
अणु
	काष्ठा पूर्णांकel_bts *bts = container_of(session->auxtrace, काष्ठा पूर्णांकel_bts,
					     auxtrace);

	वापस evsel->core.attr.type == bts->pmu_type;
पूर्ण

काष्ठा पूर्णांकel_bts_synth अणु
	काष्ठा perf_tool dummy_tool;
	काष्ठा perf_session *session;
पूर्ण;

अटल पूर्णांक पूर्णांकel_bts_event_synth(काष्ठा perf_tool *tool,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample __maybe_unused,
				 काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा पूर्णांकel_bts_synth *पूर्णांकel_bts_synth =
			container_of(tool, काष्ठा पूर्णांकel_bts_synth, dummy_tool);

	वापस perf_session__deliver_synth_event(पूर्णांकel_bts_synth->session,
						 event, शून्य);
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_synth_event(काष्ठा perf_session *session,
				 काष्ठा perf_event_attr *attr, u64 id)
अणु
	काष्ठा पूर्णांकel_bts_synth पूर्णांकel_bts_synth;

	स_रखो(&पूर्णांकel_bts_synth, 0, माप(काष्ठा पूर्णांकel_bts_synth));
	पूर्णांकel_bts_synth.session = session;

	वापस perf_event__synthesize_attr(&पूर्णांकel_bts_synth.dummy_tool, attr, 1,
					   &id, पूर्णांकel_bts_event_synth);
पूर्ण

अटल पूर्णांक पूर्णांकel_bts_synth_events(काष्ठा पूर्णांकel_bts *bts,
				  काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel;
	काष्ठा perf_event_attr attr;
	bool found = false;
	u64 id;
	पूर्णांक err;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == bts->pmu_type && evsel->core.ids) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_debug("There are no selected events with Intel BTS data\n");
		वापस 0;
	पूर्ण

	स_रखो(&attr, 0, माप(काष्ठा perf_event_attr));
	attr.size = माप(काष्ठा perf_event_attr);
	attr.type = PERF_TYPE_HARDWARE;
	attr.sample_type = evsel->core.attr.sample_type & PERF_SAMPLE_MASK;
	attr.sample_type |= PERF_SAMPLE_IP | PERF_SAMPLE_TID |
			    PERF_SAMPLE_PERIOD;
	attr.sample_type &= ~(u64)PERF_SAMPLE_TIME;
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

	अगर (bts->synth_opts.branches) अणु
		attr.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
		attr.sample_period = 1;
		attr.sample_type |= PERF_SAMPLE_ADDR;
		pr_debug("Synthesizing 'branches' event with id %" PRIu64 " sample type %#" PRIx64 "\n",
			 id, (u64)attr.sample_type);
		err = पूर्णांकel_bts_synth_event(session, &attr, id);
		अगर (err) अणु
			pr_err("%s: failed to synthesize 'branches' event type\n",
			       __func__);
			वापस err;
		पूर्ण
		bts->sample_branches = true;
		bts->branches_sample_type = attr.sample_type;
		bts->branches_id = id;
		/*
		 * We only use sample types from PERF_SAMPLE_MASK so we can use
		 * __evsel__sample_size() here.
		 */
		bts->branches_event_size = माप(काष्ठा perf_record_sample) +
					   __evsel__sample_size(attr.sample_type);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर पूर्णांकel_bts_info_fmts[] = अणु
	[INTEL_BTS_PMU_TYPE]		= "  PMU Type           %"PRId64"\n",
	[INTEL_BTS_TIME_SHIFT]		= "  Time Shift         %"PRIu64"\n",
	[INTEL_BTS_TIME_MULT]		= "  Time Muliplier     %"PRIu64"\n",
	[INTEL_BTS_TIME_ZERO]		= "  Time Zero          %"PRIu64"\n",
	[INTEL_BTS_CAP_USER_TIME_ZERO]	= "  Cap Time Zero      %"PRId64"\n",
	[INTEL_BTS_SNAPSHOT_MODE]	= "  Snapshot mode      %"PRId64"\n",
पूर्ण;

अटल व्योम पूर्णांकel_bts_prपूर्णांक_info(__u64 *arr, पूर्णांक start, पूर्णांक finish)
अणु
	पूर्णांक i;

	अगर (!dump_trace)
		वापस;

	क्रम (i = start; i <= finish; i++)
		ख_लिखो(मानक_निकास, पूर्णांकel_bts_info_fmts[i], arr[i]);
पूर्ण

पूर्णांक पूर्णांकel_bts_process_auxtrace_info(जोड़ perf_event *event,
				    काष्ठा perf_session *session)
अणु
	काष्ठा perf_record_auxtrace_info *auxtrace_info = &event->auxtrace_info;
	माप_प्रकार min_sz = माप(u64) * INTEL_BTS_SNAPSHOT_MODE;
	काष्ठा पूर्णांकel_bts *bts;
	पूर्णांक err;

	अगर (auxtrace_info->header.size < माप(काष्ठा perf_record_auxtrace_info) +
					min_sz)
		वापस -EINVAL;

	bts = zalloc(माप(काष्ठा पूर्णांकel_bts));
	अगर (!bts)
		वापस -ENOMEM;

	err = auxtrace_queues__init(&bts->queues);
	अगर (err)
		जाओ err_मुक्त;

	bts->session = session;
	bts->machine = &session->machines.host; /* No kvm support */
	bts->auxtrace_type = auxtrace_info->type;
	bts->pmu_type = auxtrace_info->priv[INTEL_BTS_PMU_TYPE];
	bts->tc.समय_shअगरt = auxtrace_info->priv[INTEL_BTS_TIME_SHIFT];
	bts->tc.समय_mult = auxtrace_info->priv[INTEL_BTS_TIME_MULT];
	bts->tc.समय_zero = auxtrace_info->priv[INTEL_BTS_TIME_ZERO];
	bts->cap_user_समय_zero =
			auxtrace_info->priv[INTEL_BTS_CAP_USER_TIME_ZERO];
	bts->snapshot_mode = auxtrace_info->priv[INTEL_BTS_SNAPSHOT_MODE];

	bts->sampling_mode = false;

	bts->auxtrace.process_event = पूर्णांकel_bts_process_event;
	bts->auxtrace.process_auxtrace_event = पूर्णांकel_bts_process_auxtrace_event;
	bts->auxtrace.flush_events = पूर्णांकel_bts_flush;
	bts->auxtrace.मुक्त_events = पूर्णांकel_bts_मुक्त_events;
	bts->auxtrace.मुक्त = पूर्णांकel_bts_मुक्त;
	bts->auxtrace.evsel_is_auxtrace = पूर्णांकel_bts_evsel_is_auxtrace;
	session->auxtrace = &bts->auxtrace;

	पूर्णांकel_bts_prपूर्णांक_info(&auxtrace_info->priv[0], INTEL_BTS_PMU_TYPE,
			     INTEL_BTS_SNAPSHOT_MODE);

	अगर (dump_trace)
		वापस 0;

	अगर (session->itrace_synth_opts->set) अणु
		bts->synth_opts = *session->itrace_synth_opts;
	पूर्ण अन्यथा अणु
		itrace_synth_opts__set_शेष(&bts->synth_opts,
				session->itrace_synth_opts->शेष_no_sample);
		bts->synth_opts.thपढ़ो_stack =
				session->itrace_synth_opts->thपढ़ो_stack;
	पूर्ण

	अगर (bts->synth_opts.calls)
		bts->branches_filter |= PERF_IP_FLAG_CALL | PERF_IP_FLAG_ASYNC |
					PERF_IP_FLAG_TRACE_END;
	अगर (bts->synth_opts.वापसs)
		bts->branches_filter |= PERF_IP_FLAG_RETURN |
					PERF_IP_FLAG_TRACE_BEGIN;

	err = पूर्णांकel_bts_synth_events(bts, session);
	अगर (err)
		जाओ err_मुक्त_queues;

	err = auxtrace_queues__process_index(&bts->queues, session);
	अगर (err)
		जाओ err_मुक्त_queues;

	अगर (bts->queues.populated)
		bts->data_queued = true;

	वापस 0;

err_मुक्त_queues:
	auxtrace_queues__मुक्त(&bts->queues);
	session->auxtrace = शून्य;
err_मुक्त:
	मुक्त(bts);
	वापस err;
पूर्ण
