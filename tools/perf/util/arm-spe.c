<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arm Statistical Profiling Extensions (SPE) support
 * Copyright (c) 2017-2018, Arm Ltd.
 */

#समावेश <byteswap.h>
#समावेश <endian.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/types.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश "auxtrace.h"
#समावेश "color.h"
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "machine.h"
#समावेश "session.h"
#समावेश "symbol.h"
#समावेश "thread.h"
#समावेश "thread-stack.h"
#समावेश "tool.h"
#समावेश "util/synthetic-events.h"

#समावेश "arm-spe.h"
#समावेश "arm-spe-decoder/arm-spe-decoder.h"
#समावेश "arm-spe-decoder/arm-spe-pkt-decoder.h"

#घोषणा MAX_TIMESTAMP (~0ULL)

काष्ठा arm_spe अणु
	काष्ठा auxtrace			auxtrace;
	काष्ठा auxtrace_queues		queues;
	काष्ठा auxtrace_heap		heap;
	काष्ठा itrace_synth_opts        synth_opts;
	u32				auxtrace_type;
	काष्ठा perf_session		*session;
	काष्ठा machine			*machine;
	u32				pmu_type;

	u8				समयless_decoding;
	u8				data_queued;

	u8				sample_flc;
	u8				sample_llc;
	u8				sample_tlb;
	u8				sample_branch;
	u8				sample_remote_access;
	u8				sample_memory;

	u64				l1d_miss_id;
	u64				l1d_access_id;
	u64				llc_miss_id;
	u64				llc_access_id;
	u64				tlb_miss_id;
	u64				tlb_access_id;
	u64				branch_miss_id;
	u64				remote_access_id;
	u64				memory_id;

	u64				kernel_start;

	अचिन्हित दीर्घ			num_events;
पूर्ण;

काष्ठा arm_spe_queue अणु
	काष्ठा arm_spe			*spe;
	अचिन्हित पूर्णांक			queue_nr;
	काष्ठा auxtrace_buffer		*buffer;
	काष्ठा auxtrace_buffer		*old_buffer;
	जोड़ perf_event		*event_buf;
	bool				on_heap;
	bool				करोne;
	pid_t				pid;
	pid_t				tid;
	पूर्णांक				cpu;
	काष्ठा arm_spe_decoder		*decoder;
	u64				समय;
	u64				बारtamp;
	काष्ठा thपढ़ो			*thपढ़ो;
पूर्ण;

अटल व्योम arm_spe_dump(काष्ठा arm_spe *spe __maybe_unused,
			 अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा arm_spe_pkt packet;
	माप_प्रकार pos = 0;
	पूर्णांक ret, pkt_len, i;
	अक्षर desc[ARM_SPE_PKT_DESC_MAX];
	स्थिर अक्षर *color = PERF_COLOR_BLUE;

	color_ख_लिखो(मानक_निकास, color,
		      ". ... ARM SPE data: size %zu bytes\n",
		      len);

	जबतक (len) अणु
		ret = arm_spe_get_packet(buf, len, &packet);
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
			ret = arm_spe_pkt_desc(&packet, desc,
					       ARM_SPE_PKT_DESC_MAX);
			अगर (!ret)
				color_ख_लिखो(मानक_निकास, color, " %s\n", desc);
		पूर्ण अन्यथा अणु
			color_ख_लिखो(मानक_निकास, color, " Bad packet!\n");
		पूर्ण
		pos += pkt_len;
		buf += pkt_len;
		len -= pkt_len;
	पूर्ण
पूर्ण

अटल व्योम arm_spe_dump_event(काष्ठा arm_spe *spe, अचिन्हित अक्षर *buf,
			       माप_प्रकार len)
अणु
	म_लिखो(".\n");
	arm_spe_dump(spe, buf, len);
पूर्ण

अटल पूर्णांक arm_spe_get_trace(काष्ठा arm_spe_buffer *b, व्योम *data)
अणु
	काष्ठा arm_spe_queue *speq = data;
	काष्ठा auxtrace_buffer *buffer = speq->buffer;
	काष्ठा auxtrace_buffer *old_buffer = speq->old_buffer;
	काष्ठा auxtrace_queue *queue;

	queue = &speq->spe->queues.queue_array[speq->queue_nr];

	buffer = auxtrace_buffer__next(queue, buffer);
	/* If no more data, drop the previous auxtrace_buffer and वापस */
	अगर (!buffer) अणु
		अगर (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		b->len = 0;
		वापस 0;
	पूर्ण

	speq->buffer = buffer;

	/* If the aux_buffer करोesn't have data associated, try to load it */
	अगर (!buffer->data) अणु
		/* get the file desc associated with the perf data file */
		पूर्णांक fd = perf_data__fd(speq->spe->session->data);

		buffer->data = auxtrace_buffer__get_data(buffer, fd);
		अगर (!buffer->data)
			वापस -ENOMEM;
	पूर्ण

	b->len = buffer->size;
	b->buf = buffer->data;

	अगर (b->len) अणु
		अगर (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		speq->old_buffer = buffer;
	पूर्ण अन्यथा अणु
		auxtrace_buffer__drop_data(buffer);
		वापस arm_spe_get_trace(b, data);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा arm_spe_queue *arm_spe__alloc_queue(काष्ठा arm_spe *spe,
		अचिन्हित पूर्णांक queue_nr)
अणु
	काष्ठा arm_spe_params params = अणु .get_trace = 0, पूर्ण;
	काष्ठा arm_spe_queue *speq;

	speq = zalloc(माप(*speq));
	अगर (!speq)
		वापस शून्य;

	speq->event_buf = दो_स्मृति(PERF_SAMPLE_MAX_SIZE);
	अगर (!speq->event_buf)
		जाओ out_मुक्त;

	speq->spe = spe;
	speq->queue_nr = queue_nr;
	speq->pid = -1;
	speq->tid = -1;
	speq->cpu = -1;

	/* params set */
	params.get_trace = arm_spe_get_trace;
	params.data = speq;

	/* create new decoder */
	speq->decoder = arm_spe_decoder_new(&params);
	अगर (!speq->decoder)
		जाओ out_मुक्त;

	वापस speq;

out_मुक्त:
	zमुक्त(&speq->event_buf);
	मुक्त(speq);

	वापस शून्य;
पूर्ण

अटल अंतरभूत u8 arm_spe_cpumode(काष्ठा arm_spe *spe, u64 ip)
अणु
	वापस ip >= spe->kernel_start ?
		PERF_RECORD_MISC_KERNEL :
		PERF_RECORD_MISC_USER;
पूर्ण

अटल व्योम arm_spe_prep_sample(काष्ठा arm_spe *spe,
				काष्ठा arm_spe_queue *speq,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample)
अणु
	काष्ठा arm_spe_record *record = &speq->decoder->record;

	अगर (!spe->समयless_decoding)
		sample->समय = speq->बारtamp;

	sample->ip = record->from_ip;
	sample->cpumode = arm_spe_cpumode(spe, sample->ip);
	sample->pid = speq->pid;
	sample->tid = speq->tid;
	sample->period = 1;
	sample->cpu = speq->cpu;

	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.misc = sample->cpumode;
	event->sample.header.size = माप(काष्ठा perf_event_header);
पूर्ण

अटल अंतरभूत पूर्णांक
arm_spe_deliver_synth_event(काष्ठा arm_spe *spe,
			    काष्ठा arm_spe_queue *speq __maybe_unused,
			    जोड़ perf_event *event,
			    काष्ठा perf_sample *sample)
अणु
	पूर्णांक ret;

	ret = perf_session__deliver_synth_event(spe->session, event, sample);
	अगर (ret)
		pr_err("ARM SPE: failed to deliver event, error %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक arm_spe__synth_mem_sample(काष्ठा arm_spe_queue *speq,
				     u64 spe_events_id, u64 data_src)
अणु
	काष्ठा arm_spe *spe = speq->spe;
	काष्ठा arm_spe_record *record = &speq->decoder->record;
	जोड़ perf_event *event = speq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;

	arm_spe_prep_sample(spe, speq, event, &sample);

	sample.id = spe_events_id;
	sample.stream_id = spe_events_id;
	sample.addr = record->virt_addr;
	sample.phys_addr = record->phys_addr;
	sample.data_src = data_src;

	वापस arm_spe_deliver_synth_event(spe, speq, event, &sample);
पूर्ण

अटल पूर्णांक arm_spe__synth_branch_sample(काष्ठा arm_spe_queue *speq,
					u64 spe_events_id)
अणु
	काष्ठा arm_spe *spe = speq->spe;
	काष्ठा arm_spe_record *record = &speq->decoder->record;
	जोड़ perf_event *event = speq->event_buf;
	काष्ठा perf_sample sample = अणु .ip = 0, पूर्ण;

	arm_spe_prep_sample(spe, speq, event, &sample);

	sample.id = spe_events_id;
	sample.stream_id = spe_events_id;
	sample.addr = record->to_ip;

	वापस arm_spe_deliver_synth_event(spe, speq, event, &sample);
पूर्ण

#घोषणा SPE_MEM_TYPE	(ARM_SPE_L1D_ACCESS | ARM_SPE_L1D_MISS | \
			 ARM_SPE_LLC_ACCESS | ARM_SPE_LLC_MISS | \
			 ARM_SPE_REMOTE_ACCESS)

अटल bool arm_spe__is_memory_event(क्रमागत arm_spe_sample_type type)
अणु
	अगर (type & SPE_MEM_TYPE)
		वापस true;

	वापस false;
पूर्ण

अटल u64 arm_spe__synth_data_source(स्थिर काष्ठा arm_spe_record *record)
अणु
	जोड़ perf_mem_data_src	data_src = अणु 0 पूर्ण;

	अगर (record->op == ARM_SPE_LD)
		data_src.mem_op = PERF_MEM_OP_LOAD;
	अन्यथा
		data_src.mem_op = PERF_MEM_OP_STORE;

	अगर (record->type & (ARM_SPE_LLC_ACCESS | ARM_SPE_LLC_MISS)) अणु
		data_src.mem_lvl = PERF_MEM_LVL_L3;

		अगर (record->type & ARM_SPE_LLC_MISS)
			data_src.mem_lvl |= PERF_MEM_LVL_MISS;
		अन्यथा
			data_src.mem_lvl |= PERF_MEM_LVL_HIT;
	पूर्ण अन्यथा अगर (record->type & (ARM_SPE_L1D_ACCESS | ARM_SPE_L1D_MISS)) अणु
		data_src.mem_lvl = PERF_MEM_LVL_L1;

		अगर (record->type & ARM_SPE_L1D_MISS)
			data_src.mem_lvl |= PERF_MEM_LVL_MISS;
		अन्यथा
			data_src.mem_lvl |= PERF_MEM_LVL_HIT;
	पूर्ण

	अगर (record->type & ARM_SPE_REMOTE_ACCESS)
		data_src.mem_lvl |= PERF_MEM_LVL_REM_CCE1;

	अगर (record->type & (ARM_SPE_TLB_ACCESS | ARM_SPE_TLB_MISS)) अणु
		data_src.mem_dtlb = PERF_MEM_TLB_WK;

		अगर (record->type & ARM_SPE_TLB_MISS)
			data_src.mem_dtlb |= PERF_MEM_TLB_MISS;
		अन्यथा
			data_src.mem_dtlb |= PERF_MEM_TLB_HIT;
	पूर्ण

	वापस data_src.val;
पूर्ण

अटल पूर्णांक arm_spe_sample(काष्ठा arm_spe_queue *speq)
अणु
	स्थिर काष्ठा arm_spe_record *record = &speq->decoder->record;
	काष्ठा arm_spe *spe = speq->spe;
	u64 data_src;
	पूर्णांक err;

	data_src = arm_spe__synth_data_source(record);

	अगर (spe->sample_flc) अणु
		अगर (record->type & ARM_SPE_L1D_MISS) अणु
			err = arm_spe__synth_mem_sample(speq, spe->l1d_miss_id,
							data_src);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (record->type & ARM_SPE_L1D_ACCESS) अणु
			err = arm_spe__synth_mem_sample(speq, spe->l1d_access_id,
							data_src);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (spe->sample_llc) अणु
		अगर (record->type & ARM_SPE_LLC_MISS) अणु
			err = arm_spe__synth_mem_sample(speq, spe->llc_miss_id,
							data_src);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (record->type & ARM_SPE_LLC_ACCESS) अणु
			err = arm_spe__synth_mem_sample(speq, spe->llc_access_id,
							data_src);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (spe->sample_tlb) अणु
		अगर (record->type & ARM_SPE_TLB_MISS) अणु
			err = arm_spe__synth_mem_sample(speq, spe->tlb_miss_id,
							data_src);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (record->type & ARM_SPE_TLB_ACCESS) अणु
			err = arm_spe__synth_mem_sample(speq, spe->tlb_access_id,
							data_src);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (spe->sample_branch && (record->type & ARM_SPE_BRANCH_MISS)) अणु
		err = arm_spe__synth_branch_sample(speq, spe->branch_miss_id);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (spe->sample_remote_access &&
	    (record->type & ARM_SPE_REMOTE_ACCESS)) अणु
		err = arm_spe__synth_mem_sample(speq, spe->remote_access_id,
						data_src);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (spe->sample_memory && arm_spe__is_memory_event(record->type)) अणु
		err = arm_spe__synth_mem_sample(speq, spe->memory_id, data_src);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_run_decoder(काष्ठा arm_spe_queue *speq, u64 *बारtamp)
अणु
	काष्ठा arm_spe *spe = speq->spe;
	पूर्णांक ret;

	अगर (!spe->kernel_start)
		spe->kernel_start = machine__kernel_start(spe->machine);

	जबतक (1) अणु
		ret = arm_spe_decode(speq->decoder);
		अगर (!ret) अणु
			pr_debug("No data or all data has been processed.\n");
			वापस 1;
		पूर्ण

		/*
		 * Error is detected when decode SPE trace data, जारी to
		 * the next trace data and find out more records.
		 */
		अगर (ret < 0)
			जारी;

		ret = arm_spe_sample(speq);
		अगर (ret)
			वापस ret;

		अगर (!spe->समयless_decoding && speq->बारtamp >= *बारtamp) अणु
			*बारtamp = speq->बारtamp;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe__setup_queue(काष्ठा arm_spe *spe,
			       काष्ठा auxtrace_queue *queue,
			       अचिन्हित पूर्णांक queue_nr)
अणु
	काष्ठा arm_spe_queue *speq = queue->priv;
	काष्ठा arm_spe_record *record;

	अगर (list_empty(&queue->head) || speq)
		वापस 0;

	speq = arm_spe__alloc_queue(spe, queue_nr);

	अगर (!speq)
		वापस -ENOMEM;

	queue->priv = speq;

	अगर (queue->cpu != -1)
		speq->cpu = queue->cpu;

	अगर (!speq->on_heap) अणु
		पूर्णांक ret;

		अगर (spe->समयless_decoding)
			वापस 0;

retry:
		ret = arm_spe_decode(speq->decoder);

		अगर (!ret)
			वापस 0;

		अगर (ret < 0)
			जाओ retry;

		record = &speq->decoder->record;

		speq->बारtamp = record->बारtamp;
		ret = auxtrace_heap__add(&spe->heap, queue_nr, speq->बारtamp);
		अगर (ret)
			वापस ret;
		speq->on_heap = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe__setup_queues(काष्ठा arm_spe *spe)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < spe->queues.nr_queues; i++) अणु
		ret = arm_spe__setup_queue(spe, &spe->queues.queue_array[i], i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe__update_queues(काष्ठा arm_spe *spe)
अणु
	अगर (spe->queues.new_data) अणु
		spe->queues.new_data = false;
		वापस arm_spe__setup_queues(spe);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool arm_spe__is_समयless_decoding(काष्ठा arm_spe *spe)
अणु
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = spe->session->evlist;
	bool समयless_decoding = true;

	/*
	 * Circle through the list of event and complain अगर we find one
	 * with the समय bit set.
	 */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर ((evsel->core.attr.sample_type & PERF_SAMPLE_TIME))
			समयless_decoding = false;
	पूर्ण

	वापस समयless_decoding;
पूर्ण

अटल व्योम arm_spe_set_pid_tid_cpu(काष्ठा arm_spe *spe,
				    काष्ठा auxtrace_queue *queue)
अणु
	काष्ठा arm_spe_queue *speq = queue->priv;
	pid_t tid;

	tid = machine__get_current_tid(spe->machine, speq->cpu);
	अगर (tid != -1) अणु
		speq->tid = tid;
		thपढ़ो__zput(speq->thपढ़ो);
	पूर्ण अन्यथा
		speq->tid = queue->tid;

	अगर ((!speq->thपढ़ो) && (speq->tid != -1)) अणु
		speq->thपढ़ो = machine__find_thपढ़ो(spe->machine, -1,
						    speq->tid);
	पूर्ण

	अगर (speq->thपढ़ो) अणु
		speq->pid = speq->thपढ़ो->pid_;
		अगर (queue->cpu == -1)
			speq->cpu = speq->thपढ़ो->cpu;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_spe_process_queues(काष्ठा arm_spe *spe, u64 बारtamp)
अणु
	अचिन्हित पूर्णांक queue_nr;
	u64 ts;
	पूर्णांक ret;

	जबतक (1) अणु
		काष्ठा auxtrace_queue *queue;
		काष्ठा arm_spe_queue *speq;

		अगर (!spe->heap.heap_cnt)
			वापस 0;

		अगर (spe->heap.heap_array[0].ordinal >= बारtamp)
			वापस 0;

		queue_nr = spe->heap.heap_array[0].queue_nr;
		queue = &spe->queues.queue_array[queue_nr];
		speq = queue->priv;

		auxtrace_heap__pop(&spe->heap);

		अगर (spe->heap.heap_cnt) अणु
			ts = spe->heap.heap_array[0].ordinal + 1;
			अगर (ts > बारtamp)
				ts = बारtamp;
		पूर्ण अन्यथा अणु
			ts = बारtamp;
		पूर्ण

		arm_spe_set_pid_tid_cpu(spe, queue);

		ret = arm_spe_run_decoder(speq, &ts);
		अगर (ret < 0) अणु
			auxtrace_heap__add(&spe->heap, queue_nr, ts);
			वापस ret;
		पूर्ण

		अगर (!ret) अणु
			ret = auxtrace_heap__add(&spe->heap, queue_nr, ts);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			speq->on_heap = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_process_समयless_queues(काष्ठा arm_spe *spe, pid_t tid,
					    u64 समय_)
अणु
	काष्ठा auxtrace_queues *queues = &spe->queues;
	अचिन्हित पूर्णांक i;
	u64 ts = 0;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		काष्ठा auxtrace_queue *queue = &spe->queues.queue_array[i];
		काष्ठा arm_spe_queue *speq = queue->priv;

		अगर (speq && (tid == -1 || speq->tid == tid)) अणु
			speq->समय = समय_;
			arm_spe_set_pid_tid_cpu(spe, queue);
			arm_spe_run_decoder(speq, &ts);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_process_event(काष्ठा perf_session *session,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample,
				 काष्ठा perf_tool *tool)
अणु
	पूर्णांक err = 0;
	u64 बारtamp;
	काष्ठा arm_spe *spe = container_of(session->auxtrace,
			काष्ठा arm_spe, auxtrace);

	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events) अणु
		pr_err("SPE trace requires ordered events\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sample->समय && (sample->समय != (u64) -1))
		बारtamp = sample->समय;
	अन्यथा
		बारtamp = 0;

	अगर (बारtamp || spe->समयless_decoding) अणु
		err = arm_spe__update_queues(spe);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (spe->समयless_decoding) अणु
		अगर (event->header.type == PERF_RECORD_EXIT) अणु
			err = arm_spe_process_समयless_queues(spe,
					event->विभाजन.tid,
					sample->समय);
		पूर्ण
	पूर्ण अन्यथा अगर (बारtamp) अणु
		अगर (event->header.type == PERF_RECORD_EXIT) अणु
			err = arm_spe_process_queues(spe, बारtamp);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक arm_spe_process_auxtrace_event(काष्ठा perf_session *session,
					  जोड़ perf_event *event,
					  काष्ठा perf_tool *tool __maybe_unused)
अणु
	काष्ठा arm_spe *spe = container_of(session->auxtrace, काष्ठा arm_spe,
					     auxtrace);

	अगर (!spe->data_queued) अणु
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

		err = auxtrace_queues__add_event(&spe->queues, session, event,
				data_offset, &buffer);
		अगर (err)
			वापस err;

		/* Dump here now we have copied a piped trace out of the pipe */
		अगर (dump_trace) अणु
			अगर (auxtrace_buffer__get_data(buffer, fd)) अणु
				arm_spe_dump_event(spe, buffer->data,
						buffer->size);
				auxtrace_buffer__put_data(buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_flush(काष्ठा perf_session *session __maybe_unused,
			 काष्ठा perf_tool *tool __maybe_unused)
अणु
	काष्ठा arm_spe *spe = container_of(session->auxtrace, काष्ठा arm_spe,
			auxtrace);
	पूर्णांक ret;

	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events)
		वापस -EINVAL;

	ret = arm_spe__update_queues(spe);
	अगर (ret < 0)
		वापस ret;

	अगर (spe->समयless_decoding)
		वापस arm_spe_process_समयless_queues(spe, -1,
				MAX_TIMESTAMP - 1);

	वापस arm_spe_process_queues(spe, MAX_TIMESTAMP);
पूर्ण

अटल व्योम arm_spe_मुक्त_queue(व्योम *priv)
अणु
	काष्ठा arm_spe_queue *speq = priv;

	अगर (!speq)
		वापस;
	thपढ़ो__zput(speq->thपढ़ो);
	arm_spe_decoder_मुक्त(speq->decoder);
	zमुक्त(&speq->event_buf);
	मुक्त(speq);
पूर्ण

अटल व्योम arm_spe_मुक्त_events(काष्ठा perf_session *session)
अणु
	काष्ठा arm_spe *spe = container_of(session->auxtrace, काष्ठा arm_spe,
					     auxtrace);
	काष्ठा auxtrace_queues *queues = &spe->queues;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		arm_spe_मुक्त_queue(queues->queue_array[i].priv);
		queues->queue_array[i].priv = शून्य;
	पूर्ण
	auxtrace_queues__मुक्त(queues);
पूर्ण

अटल व्योम arm_spe_मुक्त(काष्ठा perf_session *session)
अणु
	काष्ठा arm_spe *spe = container_of(session->auxtrace, काष्ठा arm_spe,
					     auxtrace);

	auxtrace_heap__मुक्त(&spe->heap);
	arm_spe_मुक्त_events(session);
	session->auxtrace = शून्य;
	मुक्त(spe);
पूर्ण

अटल bool arm_spe_evsel_is_auxtrace(काष्ठा perf_session *session,
				      काष्ठा evsel *evsel)
अणु
	काष्ठा arm_spe *spe = container_of(session->auxtrace, काष्ठा arm_spe, auxtrace);

	वापस evsel->core.attr.type == spe->pmu_type;
पूर्ण

अटल स्थिर अक्षर * स्थिर arm_spe_info_fmts[] = अणु
	[ARM_SPE_PMU_TYPE]		= "  PMU Type           %"PRId64"\n",
पूर्ण;

अटल व्योम arm_spe_prपूर्णांक_info(__u64 *arr)
अणु
	अगर (!dump_trace)
		वापस;

	ख_लिखो(मानक_निकास, arm_spe_info_fmts[ARM_SPE_PMU_TYPE], arr[ARM_SPE_PMU_TYPE]);
पूर्ण

काष्ठा arm_spe_synth अणु
	काष्ठा perf_tool dummy_tool;
	काष्ठा perf_session *session;
पूर्ण;

अटल पूर्णांक arm_spe_event_synth(काष्ठा perf_tool *tool,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample __maybe_unused,
			       काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा arm_spe_synth *arm_spe_synth =
		      container_of(tool, काष्ठा arm_spe_synth, dummy_tool);

	वापस perf_session__deliver_synth_event(arm_spe_synth->session,
						 event, शून्य);
पूर्ण

अटल पूर्णांक arm_spe_synth_event(काष्ठा perf_session *session,
			       काष्ठा perf_event_attr *attr, u64 id)
अणु
	काष्ठा arm_spe_synth arm_spe_synth;

	स_रखो(&arm_spe_synth, 0, माप(काष्ठा arm_spe_synth));
	arm_spe_synth.session = session;

	वापस perf_event__synthesize_attr(&arm_spe_synth.dummy_tool, attr, 1,
					   &id, arm_spe_event_synth);
पूर्ण

अटल व्योम arm_spe_set_event_name(काष्ठा evlist *evlist, u64 id,
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

अटल पूर्णांक
arm_spe_synth_events(काष्ठा arm_spe *spe, काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel;
	काष्ठा perf_event_attr attr;
	bool found = false;
	u64 id;
	पूर्णांक err;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == spe->pmu_type) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_debug("No selected events with SPE trace data\n");
		वापस 0;
	पूर्ण

	स_रखो(&attr, 0, माप(काष्ठा perf_event_attr));
	attr.size = माप(काष्ठा perf_event_attr);
	attr.type = PERF_TYPE_HARDWARE;
	attr.sample_type = evsel->core.attr.sample_type & PERF_SAMPLE_MASK;
	attr.sample_type |= PERF_SAMPLE_IP | PERF_SAMPLE_TID |
			    PERF_SAMPLE_PERIOD | PERF_SAMPLE_DATA_SRC;
	अगर (spe->समयless_decoding)
		attr.sample_type &= ~(u64)PERF_SAMPLE_TIME;
	अन्यथा
		attr.sample_type |= PERF_SAMPLE_TIME;

	attr.exclude_user = evsel->core.attr.exclude_user;
	attr.exclude_kernel = evsel->core.attr.exclude_kernel;
	attr.exclude_hv = evsel->core.attr.exclude_hv;
	attr.exclude_host = evsel->core.attr.exclude_host;
	attr.exclude_guest = evsel->core.attr.exclude_guest;
	attr.sample_id_all = evsel->core.attr.sample_id_all;
	attr.पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;

	/* create new id val to be a fixed offset from evsel id */
	id = evsel->core.id[0] + 1000000000;

	अगर (!id)
		id = 1;

	अगर (spe->synth_opts.flc) अणु
		spe->sample_flc = true;

		/* Level 1 data cache miss */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->l1d_miss_id = id;
		arm_spe_set_event_name(evlist, id, "l1d-miss");
		id += 1;

		/* Level 1 data cache access */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->l1d_access_id = id;
		arm_spe_set_event_name(evlist, id, "l1d-access");
		id += 1;
	पूर्ण

	अगर (spe->synth_opts.llc) अणु
		spe->sample_llc = true;

		/* Last level cache miss */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->llc_miss_id = id;
		arm_spe_set_event_name(evlist, id, "llc-miss");
		id += 1;

		/* Last level cache access */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->llc_access_id = id;
		arm_spe_set_event_name(evlist, id, "llc-access");
		id += 1;
	पूर्ण

	अगर (spe->synth_opts.tlb) अणु
		spe->sample_tlb = true;

		/* TLB miss */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->tlb_miss_id = id;
		arm_spe_set_event_name(evlist, id, "tlb-miss");
		id += 1;

		/* TLB access */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->tlb_access_id = id;
		arm_spe_set_event_name(evlist, id, "tlb-access");
		id += 1;
	पूर्ण

	अगर (spe->synth_opts.branches) अणु
		spe->sample_branch = true;

		/* Branch miss */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->branch_miss_id = id;
		arm_spe_set_event_name(evlist, id, "branch-miss");
		id += 1;
	पूर्ण

	अगर (spe->synth_opts.remote_access) अणु
		spe->sample_remote_access = true;

		/* Remote access */
		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->remote_access_id = id;
		arm_spe_set_event_name(evlist, id, "remote-access");
		id += 1;
	पूर्ण

	अगर (spe->synth_opts.mem) अणु
		spe->sample_memory = true;

		err = arm_spe_synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		spe->memory_id = id;
		arm_spe_set_event_name(evlist, id, "memory");
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arm_spe_process_auxtrace_info(जोड़ perf_event *event,
				  काष्ठा perf_session *session)
अणु
	काष्ठा perf_record_auxtrace_info *auxtrace_info = &event->auxtrace_info;
	माप_प्रकार min_sz = माप(u64) * ARM_SPE_AUXTRACE_PRIV_MAX;
	काष्ठा arm_spe *spe;
	पूर्णांक err;

	अगर (auxtrace_info->header.size < माप(काष्ठा perf_record_auxtrace_info) +
					min_sz)
		वापस -EINVAL;

	spe = zalloc(माप(काष्ठा arm_spe));
	अगर (!spe)
		वापस -ENOMEM;

	err = auxtrace_queues__init(&spe->queues);
	अगर (err)
		जाओ err_मुक्त;

	spe->session = session;
	spe->machine = &session->machines.host; /* No kvm support */
	spe->auxtrace_type = auxtrace_info->type;
	spe->pmu_type = auxtrace_info->priv[ARM_SPE_PMU_TYPE];

	spe->समयless_decoding = arm_spe__is_समयless_decoding(spe);
	spe->auxtrace.process_event = arm_spe_process_event;
	spe->auxtrace.process_auxtrace_event = arm_spe_process_auxtrace_event;
	spe->auxtrace.flush_events = arm_spe_flush;
	spe->auxtrace.मुक्त_events = arm_spe_मुक्त_events;
	spe->auxtrace.मुक्त = arm_spe_मुक्त;
	spe->auxtrace.evsel_is_auxtrace = arm_spe_evsel_is_auxtrace;
	session->auxtrace = &spe->auxtrace;

	arm_spe_prपूर्णांक_info(&auxtrace_info->priv[0]);

	अगर (dump_trace)
		वापस 0;

	अगर (session->itrace_synth_opts && session->itrace_synth_opts->set)
		spe->synth_opts = *session->itrace_synth_opts;
	अन्यथा
		itrace_synth_opts__set_शेष(&spe->synth_opts, false);

	err = arm_spe_synth_events(spe, session);
	अगर (err)
		जाओ err_मुक्त_queues;

	err = auxtrace_queues__process_index(&spe->queues, session);
	अगर (err)
		जाओ err_मुक्त_queues;

	अगर (spe->queues.populated)
		spe->data_queued = true;

	वापस 0;

err_मुक्त_queues:
	auxtrace_queues__मुक्त(&spe->queues);
	session->auxtrace = शून्य;
err_मुक्त:
	मुक्त(spe);
	वापस err;
पूर्ण
