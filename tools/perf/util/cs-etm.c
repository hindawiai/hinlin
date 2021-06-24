<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015-2018 Linaro Limited.
 *
 * Author: Tor Jeremiassen <tor@ti.com>
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/types.h>
#समावेश <linux/zभाग.स>

#समावेश <खोलोcsd/ocsd_अगर_types.h>
#समावेश <मानककोष.स>

#समावेश "auxtrace.h"
#समावेश "color.h"
#समावेश "cs-etm.h"
#समावेश "cs-etm-decoder/cs-etm-decoder.h"
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "evlist.h"
#समावेश "intlist.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "perf.h"
#समावेश "session.h"
#समावेश "map_symbol.h"
#समावेश "branch.h"
#समावेश "symbol.h"
#समावेश "tool.h"
#समावेश "thread.h"
#समावेश "thread-stack.h"
#समावेश <tools/libc_compat.h>
#समावेश "util/synthetic-events.h"

#घोषणा MAX_TIMESTAMP (~0ULL)

काष्ठा cs_eपंचांग_auxtrace अणु
	काष्ठा auxtrace auxtrace;
	काष्ठा auxtrace_queues queues;
	काष्ठा auxtrace_heap heap;
	काष्ठा itrace_synth_opts synth_opts;
	काष्ठा perf_session *session;
	काष्ठा machine *machine;
	काष्ठा thपढ़ो *unknown_thपढ़ो;

	u8 समयless_decoding;
	u8 snapshot_mode;
	u8 data_queued;
	u8 sample_branches;
	u8 sample_inकाष्ठाions;

	पूर्णांक num_cpu;
	u32 auxtrace_type;
	u64 branches_sample_type;
	u64 branches_id;
	u64 inकाष्ठाions_sample_type;
	u64 inकाष्ठाions_sample_period;
	u64 inकाष्ठाions_id;
	u64 **metadata;
	u64 kernel_start;
	अचिन्हित पूर्णांक pmu_type;
पूर्ण;

काष्ठा cs_eपंचांग_traceid_queue अणु
	u8 trace_chan_id;
	pid_t pid, tid;
	u64 period_inकाष्ठाions;
	माप_प्रकार last_branch_pos;
	जोड़ perf_event *event_buf;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा branch_stack *last_branch;
	काष्ठा branch_stack *last_branch_rb;
	काष्ठा cs_eपंचांग_packet *prev_packet;
	काष्ठा cs_eपंचांग_packet *packet;
	काष्ठा cs_eपंचांग_packet_queue packet_queue;
पूर्ण;

काष्ठा cs_eपंचांग_queue अणु
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग;
	काष्ठा cs_eपंचांग_decoder *decoder;
	काष्ठा auxtrace_buffer *buffer;
	अचिन्हित पूर्णांक queue_nr;
	u8 pending_बारtamp;
	u64 offset;
	स्थिर अचिन्हित अक्षर *buf;
	माप_प्रकार buf_len, buf_used;
	/* Conversion between traceID and index in traceid_queues array */
	काष्ठा पूर्णांकlist *traceid_queues_list;
	काष्ठा cs_eपंचांग_traceid_queue **traceid_queues;
पूर्ण;

/* RB tree क्रम quick conversion between traceID and metadata poपूर्णांकers */
अटल काष्ठा पूर्णांकlist *traceid_list;

अटल पूर्णांक cs_eपंचांग__update_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग);
अटल पूर्णांक cs_eपंचांग__process_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग);
अटल पूर्णांक cs_eपंचांग__process_समयless_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
					   pid_t tid);
अटल पूर्णांक cs_eपंचांग__get_data_block(काष्ठा cs_eपंचांग_queue *eपंचांगq);
अटल पूर्णांक cs_eपंचांग__decode_data_block(काष्ठा cs_eपंचांग_queue *eपंचांगq);

/* PTMs ETMIDR [11:8] set to b0011 */
#घोषणा ETMIDR_PTM_VERSION 0x00000300

/*
 * A काष्ठा auxtrace_heap_item only has a queue_nr and a बारtamp to
 * work with.  One option is to modअगरy to auxtrace_heap_XYZ() API or simply
 * encode the eपंचांग queue number as the upper 16 bit and the channel as
 * the lower 16 bit.
 */
#घोषणा TO_CS_QUEUE_NR(queue_nr, trace_chan_id)	\
		      (queue_nr << 16 | trace_chan_id)
#घोषणा TO_QUEUE_NR(cs_queue_nr) (cs_queue_nr >> 16)
#घोषणा TO_TRACE_CHAN_ID(cs_queue_nr) (cs_queue_nr & 0x0000ffff)

अटल u32 cs_eपंचांग__get_v7_protocol_version(u32 eपंचांगidr)
अणु
	eपंचांगidr &= ETMIDR_PTM_VERSION;

	अगर (eपंचांगidr == ETMIDR_PTM_VERSION)
		वापस CS_ETM_PROTO_PTM;

	वापस CS_ETM_PROTO_ETMV3;
पूर्ण

अटल पूर्णांक cs_eपंचांग__get_magic(u8 trace_chan_id, u64 *magic)
अणु
	काष्ठा पूर्णांक_node *inode;
	u64 *metadata;

	inode = पूर्णांकlist__find(traceid_list, trace_chan_id);
	अगर (!inode)
		वापस -EINVAL;

	metadata = inode->priv;
	*magic = metadata[CS_ETM_MAGIC];
	वापस 0;
पूर्ण

पूर्णांक cs_eपंचांग__get_cpu(u8 trace_chan_id, पूर्णांक *cpu)
अणु
	काष्ठा पूर्णांक_node *inode;
	u64 *metadata;

	inode = पूर्णांकlist__find(traceid_list, trace_chan_id);
	अगर (!inode)
		वापस -EINVAL;

	metadata = inode->priv;
	*cpu = (पूर्णांक)metadata[CS_ETM_CPU];
	वापस 0;
पूर्ण

/*
 * The वापसed PID क्रमmat is presented by two bits:
 *
 *   Bit ETM_OPT_CTXTID: CONTEXTIDR or CONTEXTIDR_EL1 is traced;
 *   Bit ETM_OPT_CTXTID2: CONTEXTIDR_EL2 is traced.
 *
 * It's possible that the two bits ETM_OPT_CTXTID and ETM_OPT_CTXTID2
 * are enabled at the same समय when the session runs on an EL2 kernel.
 * This means the CONTEXTIDR_EL1 and CONTEXTIDR_EL2 both will be
 * recorded in the trace data, the tool will selectively use
 * CONTEXTIDR_EL2 as PID.
 */
पूर्णांक cs_eपंचांग__get_pid_fmt(u8 trace_chan_id, u64 *pid_fmt)
अणु
	काष्ठा पूर्णांक_node *inode;
	u64 *metadata, val;

	inode = पूर्णांकlist__find(traceid_list, trace_chan_id);
	अगर (!inode)
		वापस -EINVAL;

	metadata = inode->priv;

	अगर (metadata[CS_ETM_MAGIC] == __perf_cs_eपंचांगv3_magic) अणु
		val = metadata[CS_ETM_ETMCR];
		/* CONTEXTIDR is traced */
		अगर (val & BIT(ETM_OPT_CTXTID))
			*pid_fmt = BIT(ETM_OPT_CTXTID);
	पूर्ण अन्यथा अणु
		val = metadata[CS_ETMV4_TRCCONFIGR];
		/* CONTEXTIDR_EL2 is traced */
		अगर (val & (BIT(ETM4_CFG_BIT_VMID) | BIT(ETM4_CFG_BIT_VMID_OPT)))
			*pid_fmt = BIT(ETM_OPT_CTXTID2);
		/* CONTEXTIDR_EL1 is traced */
		अन्यथा अगर (val & BIT(ETM4_CFG_BIT_CTXTID))
			*pid_fmt = BIT(ETM_OPT_CTXTID);
	पूर्ण

	वापस 0;
पूर्ण

व्योम cs_eपंचांग__eपंचांगq_set_traceid_queue_बारtamp(काष्ठा cs_eपंचांग_queue *eपंचांगq,
					      u8 trace_chan_id)
अणु
	/*
	 * When a बारtamp packet is encountered the backend code
	 * is stopped so that the front end has समय to process packets
	 * that were accumulated in the traceID queue.  Since there can
	 * be more than one channel per cs_eपंचांग_queue, we need to specअगरy
	 * what traceID queue needs servicing.
	 */
	eपंचांगq->pending_बारtamp = trace_chan_id;
पूर्ण

अटल u64 cs_eपंचांग__eपंचांगq_get_बारtamp(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				      u8 *trace_chan_id)
अणु
	काष्ठा cs_eपंचांग_packet_queue *packet_queue;

	अगर (!eपंचांगq->pending_बारtamp)
		वापस 0;

	अगर (trace_chan_id)
		*trace_chan_id = eपंचांगq->pending_बारtamp;

	packet_queue = cs_eपंचांग__eपंचांगq_get_packet_queue(eपंचांगq,
						     eपंचांगq->pending_बारtamp);
	अगर (!packet_queue)
		वापस 0;

	/* Acknowledge pending status */
	eपंचांगq->pending_बारtamp = 0;

	/* See function cs_eपंचांग_decoder__करो_अणुhard|softपूर्ण_बारtamp() */
	वापस packet_queue->बारtamp;
पूर्ण

अटल व्योम cs_eपंचांग__clear_packet_queue(काष्ठा cs_eपंचांग_packet_queue *queue)
अणु
	पूर्णांक i;

	queue->head = 0;
	queue->tail = 0;
	queue->packet_count = 0;
	क्रम (i = 0; i < CS_ETM_PACKET_MAX_BUFFER; i++) अणु
		queue->packet_buffer[i].isa = CS_ETM_ISA_UNKNOWN;
		queue->packet_buffer[i].start_addr = CS_ETM_INVAL_ADDR;
		queue->packet_buffer[i].end_addr = CS_ETM_INVAL_ADDR;
		queue->packet_buffer[i].instr_count = 0;
		queue->packet_buffer[i].last_instr_taken_branch = false;
		queue->packet_buffer[i].last_instr_size = 0;
		queue->packet_buffer[i].last_instr_type = 0;
		queue->packet_buffer[i].last_instr_subtype = 0;
		queue->packet_buffer[i].last_instr_cond = 0;
		queue->packet_buffer[i].flags = 0;
		queue->packet_buffer[i].exception_number = UINT32_MAX;
		queue->packet_buffer[i].trace_chan_id = UINT8_MAX;
		queue->packet_buffer[i].cpu = पूर्णांक_न्यून;
	पूर्ण
पूर्ण

अटल व्योम cs_eपंचांग__clear_all_packet_queues(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	पूर्णांक idx;
	काष्ठा पूर्णांक_node *inode;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;
	काष्ठा पूर्णांकlist *traceid_queues_list = eपंचांगq->traceid_queues_list;

	पूर्णांकlist__क्रम_each_entry(inode, traceid_queues_list) अणु
		idx = (पूर्णांक)(पूर्णांकptr_t)inode->priv;
		tidq = eपंचांगq->traceid_queues[idx];
		cs_eपंचांग__clear_packet_queue(&tidq->packet_queue);
	पूर्ण
पूर्ण

अटल पूर्णांक cs_eपंचांग__init_traceid_queue(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				      काष्ठा cs_eपंचांग_traceid_queue *tidq,
				      u8 trace_chan_id)
अणु
	पूर्णांक rc = -ENOMEM;
	काष्ठा auxtrace_queue *queue;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;

	cs_eपंचांग__clear_packet_queue(&tidq->packet_queue);

	queue = &eपंचांगq->eपंचांग->queues.queue_array[eपंचांगq->queue_nr];
	tidq->tid = queue->tid;
	tidq->pid = -1;
	tidq->trace_chan_id = trace_chan_id;

	tidq->packet = zalloc(माप(काष्ठा cs_eपंचांग_packet));
	अगर (!tidq->packet)
		जाओ out;

	tidq->prev_packet = zalloc(माप(काष्ठा cs_eपंचांग_packet));
	अगर (!tidq->prev_packet)
		जाओ out_मुक्त;

	अगर (eपंचांग->synth_opts.last_branch) अणु
		माप_प्रकार sz = माप(काष्ठा branch_stack);

		sz += eपंचांग->synth_opts.last_branch_sz *
		      माप(काष्ठा branch_entry);
		tidq->last_branch = zalloc(sz);
		अगर (!tidq->last_branch)
			जाओ out_मुक्त;
		tidq->last_branch_rb = zalloc(sz);
		अगर (!tidq->last_branch_rb)
			जाओ out_मुक्त;
	पूर्ण

	tidq->event_buf = दो_स्मृति(PERF_SAMPLE_MAX_SIZE);
	अगर (!tidq->event_buf)
		जाओ out_मुक्त;

	वापस 0;

out_मुक्त:
	zमुक्त(&tidq->last_branch_rb);
	zमुक्त(&tidq->last_branch);
	zमुक्त(&tidq->prev_packet);
	zमुक्त(&tidq->packet);
out:
	वापस rc;
पूर्ण

अटल काष्ठा cs_eपंचांग_traceid_queue
*cs_eपंचांग__eपंचांगq_get_traceid_queue(काष्ठा cs_eपंचांग_queue *eपंचांगq, u8 trace_chan_id)
अणु
	पूर्णांक idx;
	काष्ठा पूर्णांक_node *inode;
	काष्ठा पूर्णांकlist *traceid_queues_list;
	काष्ठा cs_eपंचांग_traceid_queue *tidq, **traceid_queues;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;

	अगर (eपंचांग->समयless_decoding)
		trace_chan_id = CS_ETM_PER_THREAD_TRACEID;

	traceid_queues_list = eपंचांगq->traceid_queues_list;

	/*
	 * Check अगर the traceid_queue exist क्रम this traceID by looking
	 * in the queue list.
	 */
	inode = पूर्णांकlist__find(traceid_queues_list, trace_chan_id);
	अगर (inode) अणु
		idx = (पूर्णांक)(पूर्णांकptr_t)inode->priv;
		वापस eपंचांगq->traceid_queues[idx];
	पूर्ण

	/* We couldn't find a traceid_queue क्रम this traceID, allocate one */
	tidq = दो_स्मृति(माप(*tidq));
	अगर (!tidq)
		वापस शून्य;

	स_रखो(tidq, 0, माप(*tidq));

	/* Get a valid index क्रम the new traceid_queue */
	idx = पूर्णांकlist__nr_entries(traceid_queues_list);
	/* Memory क्रम the inode is मुक्त'ed in cs_eपंचांग_मुक्त_traceid_queues () */
	inode = पूर्णांकlist__findnew(traceid_queues_list, trace_chan_id);
	अगर (!inode)
		जाओ out_मुक्त;

	/* Associate this traceID with this index */
	inode->priv = (व्योम *)(पूर्णांकptr_t)idx;

	अगर (cs_eपंचांग__init_traceid_queue(eपंचांगq, tidq, trace_chan_id))
		जाओ out_मुक्त;

	/* Grow the traceid_queues array by one unit */
	traceid_queues = eपंचांगq->traceid_queues;
	traceid_queues = पुनः_स्मृतिarray(traceid_queues,
				      idx + 1,
				      माप(*traceid_queues));

	/*
	 * On failure पुनः_स्मृतिarray() वापसs शून्य and the original block of
	 * memory is left untouched.
	 */
	अगर (!traceid_queues)
		जाओ out_मुक्त;

	traceid_queues[idx] = tidq;
	eपंचांगq->traceid_queues = traceid_queues;

	वापस eपंचांगq->traceid_queues[idx];

out_मुक्त:
	/*
	 * Function पूर्णांकlist__हटाओ() हटाओs the inode from the list
	 * and delete the memory associated to it.
	 */
	पूर्णांकlist__हटाओ(traceid_queues_list, inode);
	मुक्त(tidq);

	वापस शून्य;
पूर्ण

काष्ठा cs_eपंचांग_packet_queue
*cs_eपंचांग__eपंचांगq_get_packet_queue(काष्ठा cs_eपंचांग_queue *eपंचांगq, u8 trace_chan_id)
अणु
	काष्ठा cs_eपंचांग_traceid_queue *tidq;

	tidq = cs_eपंचांग__eपंचांगq_get_traceid_queue(eपंचांगq, trace_chan_id);
	अगर (tidq)
		वापस &tidq->packet_queue;

	वापस शून्य;
पूर्ण

अटल व्योम cs_eपंचांग__packet_swap(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
				काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	काष्ठा cs_eपंचांग_packet *पंचांगp;

	अगर (eपंचांग->sample_branches || eपंचांग->synth_opts.last_branch ||
	    eपंचांग->sample_inकाष्ठाions) अणु
		/*
		 * Swap PACKET with PREV_PACKET: PACKET becomes PREV_PACKET क्रम
		 * the next incoming packet.
		 */
		पंचांगp = tidq->packet;
		tidq->packet = tidq->prev_packet;
		tidq->prev_packet = पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम cs_eपंचांग__packet_dump(स्थिर अक्षर *pkt_string)
अणु
	स्थिर अक्षर *color = PERF_COLOR_BLUE;
	पूर्णांक len = म_माप(pkt_string);

	अगर (len && (pkt_string[len-1] == '\n'))
		color_ख_लिखो(मानक_निकास, color, "	%s", pkt_string);
	अन्यथा
		color_ख_लिखो(मानक_निकास, color, "	%s\n", pkt_string);

	ख_साफ(मानक_निकास);
पूर्ण

अटल व्योम cs_eपंचांग__set_trace_param_eपंचांगv3(काष्ठा cs_eपंचांग_trace_params *t_params,
					  काष्ठा cs_eपंचांग_auxtrace *eपंचांग, पूर्णांक idx,
					  u32 eपंचांगidr)
अणु
	u64 **metadata = eपंचांग->metadata;

	t_params[idx].protocol = cs_eपंचांग__get_v7_protocol_version(eपंचांगidr);
	t_params[idx].eपंचांगv3.reg_ctrl = metadata[idx][CS_ETM_ETMCR];
	t_params[idx].eपंचांगv3.reg_trc_id = metadata[idx][CS_ETM_ETMTRACEIDR];
पूर्ण

अटल व्योम cs_eपंचांग__set_trace_param_eपंचांगv4(काष्ठा cs_eपंचांग_trace_params *t_params,
					  काष्ठा cs_eपंचांग_auxtrace *eपंचांग, पूर्णांक idx)
अणु
	u64 **metadata = eपंचांग->metadata;

	t_params[idx].protocol = CS_ETM_PROTO_ETMV4i;
	t_params[idx].eपंचांगv4.reg_idr0 = metadata[idx][CS_ETMV4_TRCIDR0];
	t_params[idx].eपंचांगv4.reg_idr1 = metadata[idx][CS_ETMV4_TRCIDR1];
	t_params[idx].eपंचांगv4.reg_idr2 = metadata[idx][CS_ETMV4_TRCIDR2];
	t_params[idx].eपंचांगv4.reg_idr8 = metadata[idx][CS_ETMV4_TRCIDR8];
	t_params[idx].eपंचांगv4.reg_configr = metadata[idx][CS_ETMV4_TRCCONFIGR];
	t_params[idx].eपंचांगv4.reg_traceidr = metadata[idx][CS_ETMV4_TRCTRACEIDR];
पूर्ण

अटल पूर्णांक cs_eपंचांग__init_trace_params(काष्ठा cs_eपंचांग_trace_params *t_params,
				     काष्ठा cs_eपंचांग_auxtrace *eपंचांग)
अणु
	पूर्णांक i;
	u32 eपंचांगidr;
	u64 architecture;

	क्रम (i = 0; i < eपंचांग->num_cpu; i++) अणु
		architecture = eपंचांग->metadata[i][CS_ETM_MAGIC];

		चयन (architecture) अणु
		हाल __perf_cs_eपंचांगv3_magic:
			eपंचांगidr = eपंचांग->metadata[i][CS_ETM_ETMIDR];
			cs_eपंचांग__set_trace_param_eपंचांगv3(t_params, eपंचांग, i, eपंचांगidr);
			अवरोध;
		हाल __perf_cs_eपंचांगv4_magic:
			cs_eपंचांग__set_trace_param_eपंचांगv4(t_params, eपंचांग, i);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__init_decoder_params(काष्ठा cs_eपंचांग_decoder_params *d_params,
				       काष्ठा cs_eपंचांग_queue *eपंचांगq,
				       क्रमागत cs_eपंचांग_decoder_operation mode)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!(mode < CS_ETM_OPERATION_MAX))
		जाओ out;

	d_params->packet_prपूर्णांकer = cs_eपंचांग__packet_dump;
	d_params->operation = mode;
	d_params->data = eपंचांगq;
	d_params->क्रमmatted = true;
	d_params->fsyncs = false;
	d_params->hsyncs = false;
	d_params->frame_aligned = true;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम cs_eपंचांग__dump_event(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
			       काष्ठा auxtrace_buffer *buffer)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *color = PERF_COLOR_BLUE;
	काष्ठा cs_eपंचांग_decoder_params d_params;
	काष्ठा cs_eपंचांग_trace_params *t_params;
	काष्ठा cs_eपंचांग_decoder *decoder;
	माप_प्रकार buffer_used = 0;

	ख_लिखो(मानक_निकास, "\n");
	color_ख_लिखो(मानक_निकास, color,
		     ". ... CoreSight ETM Trace data: size %zu bytes\n",
		     buffer->size);

	/* Use metadata to fill in trace parameters क्रम trace decoder */
	t_params = zalloc(माप(*t_params) * eपंचांग->num_cpu);

	अगर (!t_params)
		वापस;

	अगर (cs_eपंचांग__init_trace_params(t_params, eपंचांग))
		जाओ out_मुक्त;

	/* Set decoder parameters to simply prपूर्णांक the trace packets */
	अगर (cs_eपंचांग__init_decoder_params(&d_params, शून्य,
					CS_ETM_OPERATION_PRINT))
		जाओ out_मुक्त;

	decoder = cs_eपंचांग_decoder__new(eपंचांग->num_cpu, &d_params, t_params);

	अगर (!decoder)
		जाओ out_मुक्त;
	करो अणु
		माप_प्रकार consumed;

		ret = cs_eपंचांग_decoder__process_data_block(
				decoder, buffer->offset,
				&((u8 *)buffer->data)[buffer_used],
				buffer->size - buffer_used, &consumed);
		अगर (ret)
			अवरोध;

		buffer_used += consumed;
	पूर्ण जबतक (buffer_used < buffer->size);

	cs_eपंचांग_decoder__मुक्त(decoder);

out_मुक्त:
	zमुक्त(&t_params);
पूर्ण

अटल पूर्णांक cs_eपंचांग__flush_events(काष्ठा perf_session *session,
				काष्ठा perf_tool *tool)
अणु
	पूर्णांक ret;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = container_of(session->auxtrace,
						   काष्ठा cs_eपंचांग_auxtrace,
						   auxtrace);
	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events)
		वापस -EINVAL;

	ret = cs_eपंचांग__update_queues(eपंचांग);

	अगर (ret < 0)
		वापस ret;

	अगर (eपंचांग->समयless_decoding)
		वापस cs_eपंचांग__process_समयless_queues(eपंचांग, -1);

	वापस cs_eपंचांग__process_queues(eपंचांग);
पूर्ण

अटल व्योम cs_eपंचांग__मुक्त_traceid_queues(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	पूर्णांक idx;
	uपूर्णांकptr_t priv;
	काष्ठा पूर्णांक_node *inode, *पंचांगp;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;
	काष्ठा पूर्णांकlist *traceid_queues_list = eपंचांगq->traceid_queues_list;

	पूर्णांकlist__क्रम_each_entry_safe(inode, पंचांगp, traceid_queues_list) अणु
		priv = (uपूर्णांकptr_t)inode->priv;
		idx = priv;

		/* Free this traceid_queue from the array */
		tidq = eपंचांगq->traceid_queues[idx];
		thपढ़ो__zput(tidq->thपढ़ो);
		zमुक्त(&tidq->event_buf);
		zमुक्त(&tidq->last_branch);
		zमुक्त(&tidq->last_branch_rb);
		zमुक्त(&tidq->prev_packet);
		zमुक्त(&tidq->packet);
		zमुक्त(&tidq);

		/*
		 * Function पूर्णांकlist__हटाओ() हटाओs the inode from the list
		 * and delete the memory associated to it.
		 */
		पूर्णांकlist__हटाओ(traceid_queues_list, inode);
	पूर्ण

	/* Then the RB tree itself */
	पूर्णांकlist__delete(traceid_queues_list);
	eपंचांगq->traceid_queues_list = शून्य;

	/* finally मुक्त the traceid_queues array */
	zमुक्त(&eपंचांगq->traceid_queues);
पूर्ण

अटल व्योम cs_eपंचांग__मुक्त_queue(व्योम *priv)
अणु
	काष्ठा cs_eपंचांग_queue *eपंचांगq = priv;

	अगर (!eपंचांगq)
		वापस;

	cs_eपंचांग_decoder__मुक्त(eपंचांगq->decoder);
	cs_eपंचांग__मुक्त_traceid_queues(eपंचांगq);
	मुक्त(eपंचांगq);
पूर्ण

अटल व्योम cs_eपंचांग__मुक्त_events(काष्ठा perf_session *session)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा cs_eपंचांग_auxtrace *aux = container_of(session->auxtrace,
						   काष्ठा cs_eपंचांग_auxtrace,
						   auxtrace);
	काष्ठा auxtrace_queues *queues = &aux->queues;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		cs_eपंचांग__मुक्त_queue(queues->queue_array[i].priv);
		queues->queue_array[i].priv = शून्य;
	पूर्ण

	auxtrace_queues__मुक्त(queues);
पूर्ण

अटल व्योम cs_eपंचांग__मुक्त(काष्ठा perf_session *session)
अणु
	पूर्णांक i;
	काष्ठा पूर्णांक_node *inode, *पंचांगp;
	काष्ठा cs_eपंचांग_auxtrace *aux = container_of(session->auxtrace,
						   काष्ठा cs_eपंचांग_auxtrace,
						   auxtrace);
	cs_eपंचांग__मुक्त_events(session);
	session->auxtrace = शून्य;

	/* First हटाओ all traceID/metadata nodes क्रम the RB tree */
	पूर्णांकlist__क्रम_each_entry_safe(inode, पंचांगp, traceid_list)
		पूर्णांकlist__हटाओ(traceid_list, inode);
	/* Then the RB tree itself */
	पूर्णांकlist__delete(traceid_list);

	क्रम (i = 0; i < aux->num_cpu; i++)
		zमुक्त(&aux->metadata[i]);

	thपढ़ो__zput(aux->unknown_thपढ़ो);
	zमुक्त(&aux->metadata);
	zमुक्त(&aux);
पूर्ण

अटल bool cs_eपंचांग__evsel_is_auxtrace(काष्ठा perf_session *session,
				      काष्ठा evsel *evsel)
अणु
	काष्ठा cs_eपंचांग_auxtrace *aux = container_of(session->auxtrace,
						   काष्ठा cs_eपंचांग_auxtrace,
						   auxtrace);

	वापस evsel->core.attr.type == aux->pmu_type;
पूर्ण

अटल u8 cs_eपंचांग__cpu_mode(काष्ठा cs_eपंचांग_queue *eपंचांगq, u64 address)
अणु
	काष्ठा machine *machine;

	machine = eपंचांगq->eपंचांग->machine;

	अगर (address >= eपंचांगq->eपंचांग->kernel_start) अणु
		अगर (machine__is_host(machine))
			वापस PERF_RECORD_MISC_KERNEL;
		अन्यथा
			वापस PERF_RECORD_MISC_GUEST_KERNEL;
	पूर्ण अन्यथा अणु
		अगर (machine__is_host(machine))
			वापस PERF_RECORD_MISC_USER;
		अन्यथा अगर (perf_guest)
			वापस PERF_RECORD_MISC_GUEST_USER;
		अन्यथा
			वापस PERF_RECORD_MISC_HYPERVISOR;
	पूर्ण
पूर्ण

अटल u32 cs_eपंचांग__mem_access(काष्ठा cs_eपंचांग_queue *eपंचांगq, u8 trace_chan_id,
			      u64 address, माप_प्रकार size, u8 *buffer)
अणु
	u8  cpumode;
	u64 offset;
	पूर्णांक len;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा machine *machine;
	काष्ठा addr_location al;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;

	अगर (!eपंचांगq)
		वापस 0;

	machine = eपंचांगq->eपंचांग->machine;
	cpumode = cs_eपंचांग__cpu_mode(eपंचांगq, address);
	tidq = cs_eपंचांग__eपंचांगq_get_traceid_queue(eपंचांगq, trace_chan_id);
	अगर (!tidq)
		वापस 0;

	thपढ़ो = tidq->thपढ़ो;
	अगर (!thपढ़ो) अणु
		अगर (cpumode != PERF_RECORD_MISC_KERNEL)
			वापस 0;
		thपढ़ो = eपंचांगq->eपंचांग->unknown_thपढ़ो;
	पूर्ण

	अगर (!thपढ़ो__find_map(thपढ़ो, cpumode, address, &al) || !al.map->dso)
		वापस 0;

	अगर (al.map->dso->data.status == DSO_DATA_STATUS_ERROR &&
	    dso__data_status_seen(al.map->dso, DSO_DATA_STATUS_SEEN_ITRACE))
		वापस 0;

	offset = al.map->map_ip(al.map, address);

	map__load(al.map);

	len = dso__data_पढ़ो_offset(al.map->dso, machine, offset, buffer, size);

	अगर (len <= 0)
		वापस 0;

	वापस len;
पूर्ण

अटल काष्ठा cs_eपंचांग_queue *cs_eपंचांग__alloc_queue(काष्ठा cs_eपंचांग_auxtrace *eपंचांग)
अणु
	काष्ठा cs_eपंचांग_decoder_params d_params;
	काष्ठा cs_eपंचांग_trace_params  *t_params = शून्य;
	काष्ठा cs_eपंचांग_queue *eपंचांगq;

	eपंचांगq = zalloc(माप(*eपंचांगq));
	अगर (!eपंचांगq)
		वापस शून्य;

	eपंचांगq->traceid_queues_list = पूर्णांकlist__new(शून्य);
	अगर (!eपंचांगq->traceid_queues_list)
		जाओ out_मुक्त;

	/* Use metadata to fill in trace parameters क्रम trace decoder */
	t_params = zalloc(माप(*t_params) * eपंचांग->num_cpu);

	अगर (!t_params)
		जाओ out_मुक्त;

	अगर (cs_eपंचांग__init_trace_params(t_params, eपंचांग))
		जाओ out_मुक्त;

	/* Set decoder parameters to decode trace packets */
	अगर (cs_eपंचांग__init_decoder_params(&d_params, eपंचांगq,
					CS_ETM_OPERATION_DECODE))
		जाओ out_मुक्त;

	eपंचांगq->decoder = cs_eपंचांग_decoder__new(eपंचांग->num_cpu, &d_params, t_params);

	अगर (!eपंचांगq->decoder)
		जाओ out_मुक्त;

	/*
	 * Register a function to handle all memory accesses required by
	 * the trace decoder library.
	 */
	अगर (cs_eपंचांग_decoder__add_mem_access_cb(eपंचांगq->decoder,
					      0x0L, ((u64) -1L),
					      cs_eपंचांग__mem_access))
		जाओ out_मुक्त_decoder;

	zमुक्त(&t_params);
	वापस eपंचांगq;

out_मुक्त_decoder:
	cs_eपंचांग_decoder__मुक्त(eपंचांगq->decoder);
out_मुक्त:
	पूर्णांकlist__delete(eपंचांगq->traceid_queues_list);
	मुक्त(eपंचांगq);

	वापस शून्य;
पूर्ण

अटल पूर्णांक cs_eपंचांग__setup_queue(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
			       काष्ठा auxtrace_queue *queue,
			       अचिन्हित पूर्णांक queue_nr)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cs_queue_nr;
	u8 trace_chan_id;
	u64 बारtamp;
	काष्ठा cs_eपंचांग_queue *eपंचांगq = queue->priv;

	अगर (list_empty(&queue->head) || eपंचांगq)
		जाओ out;

	eपंचांगq = cs_eपंचांग__alloc_queue(eपंचांग);

	अगर (!eपंचांगq) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	queue->priv = eपंचांगq;
	eपंचांगq->eपंचांग = eपंचांग;
	eपंचांगq->queue_nr = queue_nr;
	eपंचांगq->offset = 0;

	अगर (eपंचांग->समयless_decoding)
		जाओ out;

	/*
	 * We are under a CPU-wide trace scenario.  As such we need to know
	 * when the code that generated the traces started to execute so that
	 * it can be correlated with execution on other CPUs.  So we get a
	 * handle on the beginning of traces and decode until we find a
	 * बारtamp.  The बारtamp is then added to the auxtrace min heap
	 * in order to know what nibble (of all the eपंचांगqs) to decode first.
	 */
	जबतक (1) अणु
		/*
		 * Fetch an aux_buffer from this eपंचांगq.  Bail अगर no more
		 * blocks or an error has been encountered.
		 */
		ret = cs_eपंचांग__get_data_block(eपंचांगq);
		अगर (ret <= 0)
			जाओ out;

		/*
		 * Run decoder on the trace block.  The decoder will stop when
		 * encountering a बारtamp, a full packet queue or the end of
		 * trace क्रम that block.
		 */
		ret = cs_eपंचांग__decode_data_block(eपंचांगq);
		अगर (ret)
			जाओ out;

		/*
		 * Function cs_eपंचांग_decoder__करो_अणुhard|softपूर्ण_बारtamp() करोes all
		 * the बारtamp calculation क्रम us.
		 */
		बारtamp = cs_eपंचांग__eपंचांगq_get_बारtamp(eपंचांगq, &trace_chan_id);

		/* We found a बारtamp, no need to जारी. */
		अगर (बारtamp)
			अवरोध;

		/*
		 * We didn't find a बारtamp so empty all the traceid packet
		 * queues beक्रमe looking क्रम another बारtamp packet, either
		 * in the current data block or a new one.  Packets that were
		 * just decoded are useless since no बारtamp has been
		 * associated with them.  As such simply discard them.
		 */
		cs_eपंचांग__clear_all_packet_queues(eपंचांगq);
	पूर्ण

	/*
	 * We have a बारtamp.  Add it to the min heap to reflect when
	 * inकाष्ठाions conveyed by the range packets of this traceID queue
	 * started to execute.  Once the same has been करोne क्रम all the traceID
	 * queues of each eपंचांगq, redenring and decoding can start in
	 * chronological order.
	 *
	 * Note that packets decoded above are still in the traceID's packet
	 * queue and will be processed in cs_eपंचांग__process_queues().
	 */
	cs_queue_nr = TO_CS_QUEUE_NR(queue_nr, trace_chan_id);
	ret = auxtrace_heap__add(&eपंचांग->heap, cs_queue_nr, बारtamp);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक cs_eपंचांग__setup_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!eपंचांग->kernel_start)
		eपंचांग->kernel_start = machine__kernel_start(eपंचांग->machine);

	क्रम (i = 0; i < eपंचांग->queues.nr_queues; i++) अणु
		ret = cs_eपंचांग__setup_queue(eपंचांग, &eपंचांग->queues.queue_array[i], i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__update_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग)
अणु
	अगर (eपंचांग->queues.new_data) अणु
		eपंचांग->queues.new_data = false;
		वापस cs_eपंचांग__setup_queues(eपंचांग);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम cs_eपंचांग__copy_last_branch_rb(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				 काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	काष्ठा branch_stack *bs_src = tidq->last_branch_rb;
	काष्ठा branch_stack *bs_dst = tidq->last_branch;
	माप_प्रकार nr = 0;

	/*
	 * Set the number of records beक्रमe early निकास: ->nr is used to
	 * determine how many branches to copy from ->entries.
	 */
	bs_dst->nr = bs_src->nr;

	/*
	 * Early निकास when there is nothing to copy.
	 */
	अगर (!bs_src->nr)
		वापस;

	/*
	 * As bs_src->entries is a circular buffer, we need to copy from it in
	 * two steps.  First, copy the branches from the most recently inserted
	 * branch ->last_branch_pos until the end of bs_src->entries buffer.
	 */
	nr = eपंचांगq->eपंचांग->synth_opts.last_branch_sz - tidq->last_branch_pos;
	स_नकल(&bs_dst->entries[0],
	       &bs_src->entries[tidq->last_branch_pos],
	       माप(काष्ठा branch_entry) * nr);

	/*
	 * If we wrapped around at least once, the branches from the beginning
	 * of the bs_src->entries buffer and until the ->last_branch_pos element
	 * are older valid branches: copy them over.  The total number of
	 * branches copied over will be equal to the number of branches asked by
	 * the user in last_branch_sz.
	 */
	अगर (bs_src->nr >= eपंचांगq->eपंचांग->synth_opts.last_branch_sz) अणु
		स_नकल(&bs_dst->entries[nr],
		       &bs_src->entries[0],
		       माप(काष्ठा branch_entry) * tidq->last_branch_pos);
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम cs_eपंचांग__reset_last_branch_rb(काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	tidq->last_branch_pos = 0;
	tidq->last_branch_rb->nr = 0;
पूर्ण

अटल अंतरभूत पूर्णांक cs_eपंचांग__t32_instr_size(काष्ठा cs_eपंचांग_queue *eपंचांगq,
					 u8 trace_chan_id, u64 addr)
अणु
	u8 instrBytes[2];

	cs_eपंचांग__mem_access(eपंचांगq, trace_chan_id, addr,
			   ARRAY_SIZE(instrBytes), instrBytes);
	/*
	 * T32 inकाष्ठाion size is indicated by bits[15:11] of the first
	 * 16-bit word of the inकाष्ठाion: 0b11101, 0b11110 and 0b11111
	 * denote a 32-bit inकाष्ठाion.
	 */
	वापस ((instrBytes[1] & 0xF8) >= 0xE8) ? 4 : 2;
पूर्ण

अटल अंतरभूत u64 cs_eपंचांग__first_executed_instr(काष्ठा cs_eपंचांग_packet *packet)
अणु
	/* Returns 0 क्रम the CS_ETM_DISCONTINUITY packet */
	अगर (packet->sample_type == CS_ETM_DISCONTINUITY)
		वापस 0;

	वापस packet->start_addr;
पूर्ण

अटल अंतरभूत
u64 cs_eपंचांग__last_executed_instr(स्थिर काष्ठा cs_eपंचांग_packet *packet)
अणु
	/* Returns 0 क्रम the CS_ETM_DISCONTINUITY packet */
	अगर (packet->sample_type == CS_ETM_DISCONTINUITY)
		वापस 0;

	वापस packet->end_addr - packet->last_instr_size;
पूर्ण

अटल अंतरभूत u64 cs_eपंचांग__instr_addr(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				     u64 trace_chan_id,
				     स्थिर काष्ठा cs_eपंचांग_packet *packet,
				     u64 offset)
अणु
	अगर (packet->isa == CS_ETM_ISA_T32) अणु
		u64 addr = packet->start_addr;

		जबतक (offset) अणु
			addr += cs_eपंचांग__t32_instr_size(eपंचांगq,
						       trace_chan_id, addr);
			offset--;
		पूर्ण
		वापस addr;
	पूर्ण

	/* Assume a 4 byte inकाष्ठाion size (A32/A64) */
	वापस packet->start_addr + offset * 4;
पूर्ण

अटल व्योम cs_eपंचांग__update_last_branch_rb(काष्ठा cs_eपंचांग_queue *eपंचांगq,
					  काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	काष्ठा branch_stack *bs = tidq->last_branch_rb;
	काष्ठा branch_entry *be;

	/*
	 * The branches are recorded in a circular buffer in reverse
	 * chronological order: we start recording from the last element of the
	 * buffer करोwn.  After writing the first element of the stack, move the
	 * insert position back to the end of the buffer.
	 */
	अगर (!tidq->last_branch_pos)
		tidq->last_branch_pos = eपंचांगq->eपंचांग->synth_opts.last_branch_sz;

	tidq->last_branch_pos -= 1;

	be       = &bs->entries[tidq->last_branch_pos];
	be->from = cs_eपंचांग__last_executed_instr(tidq->prev_packet);
	be->to	 = cs_eपंचांग__first_executed_instr(tidq->packet);
	/* No support क्रम mispredict */
	be->flags.mispred = 0;
	be->flags.predicted = 1;

	/*
	 * Increment bs->nr until reaching the number of last branches asked by
	 * the user on the command line.
	 */
	अगर (bs->nr < eपंचांगq->eपंचांग->synth_opts.last_branch_sz)
		bs->nr += 1;
पूर्ण

अटल पूर्णांक cs_eपंचांग__inject_event(जोड़ perf_event *event,
			       काष्ठा perf_sample *sample, u64 type)
अणु
	event->header.size = perf_event__sample_event_size(sample, type, 0);
	वापस perf_event__synthesize_sample(event, type, 0, sample);
पूर्ण


अटल पूर्णांक
cs_eपंचांग__get_trace(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	काष्ठा auxtrace_buffer *aux_buffer = eपंचांगq->buffer;
	काष्ठा auxtrace_buffer *old_buffer = aux_buffer;
	काष्ठा auxtrace_queue *queue;

	queue = &eपंचांगq->eपंचांग->queues.queue_array[eपंचांगq->queue_nr];

	aux_buffer = auxtrace_buffer__next(queue, aux_buffer);

	/* If no more data, drop the previous auxtrace_buffer and वापस */
	अगर (!aux_buffer) अणु
		अगर (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		eपंचांगq->buf_len = 0;
		वापस 0;
	पूर्ण

	eपंचांगq->buffer = aux_buffer;

	/* If the aux_buffer करोesn't have data associated, try to load it */
	अगर (!aux_buffer->data) अणु
		/* get the file desc associated with the perf data file */
		पूर्णांक fd = perf_data__fd(eपंचांगq->eपंचांग->session->data);

		aux_buffer->data = auxtrace_buffer__get_data(aux_buffer, fd);
		अगर (!aux_buffer->data)
			वापस -ENOMEM;
	पूर्ण

	/* If valid, drop the previous buffer */
	अगर (old_buffer)
		auxtrace_buffer__drop_data(old_buffer);

	eपंचांगq->buf_used = 0;
	eपंचांगq->buf_len = aux_buffer->size;
	eपंचांगq->buf = aux_buffer->data;

	वापस eपंचांगq->buf_len;
पूर्ण

अटल व्योम cs_eपंचांग__set_pid_tid_cpu(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
				    काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	अगर ((!tidq->thपढ़ो) && (tidq->tid != -1))
		tidq->thपढ़ो = machine__find_thपढ़ो(eपंचांग->machine, -1,
						    tidq->tid);

	अगर (tidq->thपढ़ो)
		tidq->pid = tidq->thपढ़ो->pid_;
पूर्ण

पूर्णांक cs_eपंचांग__eपंचांगq_set_tid(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			 pid_t tid, u8 trace_chan_id)
अणु
	पूर्णांक cpu, err = -EINVAL;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;

	tidq = cs_eपंचांग__eपंचांगq_get_traceid_queue(eपंचांगq, trace_chan_id);
	अगर (!tidq)
		वापस err;

	अगर (cs_eपंचांग__get_cpu(trace_chan_id, &cpu) < 0)
		वापस err;

	err = machine__set_current_tid(eपंचांग->machine, cpu, tid, tid);
	अगर (err)
		वापस err;

	tidq->tid = tid;
	thपढ़ो__zput(tidq->thपढ़ो);

	cs_eपंचांग__set_pid_tid_cpu(eपंचांग, tidq);
	वापस 0;
पूर्ण

bool cs_eपंचांग__eपंचांगq_is_समयless(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	वापस !!eपंचांगq->eपंचांग->समयless_decoding;
पूर्ण

अटल व्योम cs_eपंचांग__copy_insn(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			      u64 trace_chan_id,
			      स्थिर काष्ठा cs_eपंचांग_packet *packet,
			      काष्ठा perf_sample *sample)
अणु
	/*
	 * It's poपूर्णांकless to पढ़ो inकाष्ठाions क्रम the CS_ETM_DISCONTINUITY
	 * packet, so directly bail out with 'insn_len' = 0.
	 */
	अगर (packet->sample_type == CS_ETM_DISCONTINUITY) अणु
		sample->insn_len = 0;
		वापस;
	पूर्ण

	/*
	 * T32 inकाष्ठाion size might be 32-bit or 16-bit, decide by calling
	 * cs_eपंचांग__t32_instr_size().
	 */
	अगर (packet->isa == CS_ETM_ISA_T32)
		sample->insn_len = cs_eपंचांग__t32_instr_size(eपंचांगq, trace_chan_id,
							  sample->ip);
	/* Otherwise, A64 and A32 inकाष्ठाion size are always 32-bit. */
	अन्यथा
		sample->insn_len = 4;

	cs_eपंचांग__mem_access(eपंचांगq, trace_chan_id, sample->ip,
			   sample->insn_len, (व्योम *)sample->insn);
पूर्ण

अटल पूर्णांक cs_eपंचांग__synth_inकाष्ठाion_sample(काष्ठा cs_eपंचांग_queue *eपंचांगq,
					    काष्ठा cs_eपंचांग_traceid_queue *tidq,
					    u64 addr, u64 period)
अणु
	पूर्णांक ret = 0;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;
	जोड़ perf_event *event = tidq->event_buf;
	काष्ठा perf_sample sample = अणु.ip = 0,पूर्ण;

	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.misc = cs_eपंचांग__cpu_mode(eपंचांगq, addr);
	event->sample.header.size = माप(काष्ठा perf_event_header);

	sample.ip = addr;
	sample.pid = tidq->pid;
	sample.tid = tidq->tid;
	sample.id = eपंचांगq->eपंचांग->inकाष्ठाions_id;
	sample.stream_id = eपंचांगq->eपंचांग->inकाष्ठाions_id;
	sample.period = period;
	sample.cpu = tidq->packet->cpu;
	sample.flags = tidq->prev_packet->flags;
	sample.cpumode = event->sample.header.misc;

	cs_eपंचांग__copy_insn(eपंचांगq, tidq->trace_chan_id, tidq->packet, &sample);

	अगर (eपंचांग->synth_opts.last_branch)
		sample.branch_stack = tidq->last_branch;

	अगर (eपंचांग->synth_opts.inject) अणु
		ret = cs_eपंचांग__inject_event(event, &sample,
					   eपंचांग->inकाष्ठाions_sample_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = perf_session__deliver_synth_event(eपंचांग->session, event, &sample);

	अगर (ret)
		pr_err(
			"CS ETM Trace: failed to deliver instruction event, error %d\n",
			ret);

	वापस ret;
पूर्ण

/*
 * The cs eपंचांग packet encodes an inकाष्ठाion range between a branch target
 * and the next taken branch. Generate sample accordingly.
 */
अटल पूर्णांक cs_eपंचांग__synth_branch_sample(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				       काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	पूर्णांक ret = 0;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;
	काष्ठा perf_sample sample = अणु.ip = 0,पूर्ण;
	जोड़ perf_event *event = tidq->event_buf;
	काष्ठा dummy_branch_stack अणु
		u64			nr;
		u64			hw_idx;
		काष्ठा branch_entry	entries;
	पूर्ण dummy_bs;
	u64 ip;

	ip = cs_eपंचांग__last_executed_instr(tidq->prev_packet);

	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.misc = cs_eपंचांग__cpu_mode(eपंचांगq, ip);
	event->sample.header.size = माप(काष्ठा perf_event_header);

	sample.ip = ip;
	sample.pid = tidq->pid;
	sample.tid = tidq->tid;
	sample.addr = cs_eपंचांग__first_executed_instr(tidq->packet);
	sample.id = eपंचांगq->eपंचांग->branches_id;
	sample.stream_id = eपंचांगq->eपंचांग->branches_id;
	sample.period = 1;
	sample.cpu = tidq->packet->cpu;
	sample.flags = tidq->prev_packet->flags;
	sample.cpumode = event->sample.header.misc;

	cs_eपंचांग__copy_insn(eपंचांगq, tidq->trace_chan_id, tidq->prev_packet,
			  &sample);

	/*
	 * perf report cannot handle events without a branch stack
	 */
	अगर (eपंचांग->synth_opts.last_branch) अणु
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

	अगर (eपंचांग->synth_opts.inject) अणु
		ret = cs_eपंचांग__inject_event(event, &sample,
					   eपंचांग->branches_sample_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = perf_session__deliver_synth_event(eपंचांग->session, event, &sample);

	अगर (ret)
		pr_err(
		"CS ETM Trace: failed to deliver instruction event, error %d\n",
		ret);

	वापस ret;
पूर्ण

काष्ठा cs_eपंचांग_synth अणु
	काष्ठा perf_tool dummy_tool;
	काष्ठा perf_session *session;
पूर्ण;

अटल पूर्णांक cs_eपंचांग__event_synth(काष्ठा perf_tool *tool,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample __maybe_unused,
			       काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा cs_eपंचांग_synth *cs_eपंचांग_synth =
		      container_of(tool, काष्ठा cs_eपंचांग_synth, dummy_tool);

	वापस perf_session__deliver_synth_event(cs_eपंचांग_synth->session,
						 event, शून्य);
पूर्ण

अटल पूर्णांक cs_eपंचांग__synth_event(काष्ठा perf_session *session,
			       काष्ठा perf_event_attr *attr, u64 id)
अणु
	काष्ठा cs_eपंचांग_synth cs_eपंचांग_synth;

	स_रखो(&cs_eपंचांग_synth, 0, माप(काष्ठा cs_eपंचांग_synth));
	cs_eपंचांग_synth.session = session;

	वापस perf_event__synthesize_attr(&cs_eपंचांग_synth.dummy_tool, attr, 1,
					   &id, cs_eपंचांग__event_synth);
पूर्ण

अटल पूर्णांक cs_eपंचांग__synth_events(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
				काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel;
	काष्ठा perf_event_attr attr;
	bool found = false;
	u64 id;
	पूर्णांक err;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type == eपंचांग->pmu_type) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_debug("No selected events with CoreSight Trace data\n");
		वापस 0;
	पूर्ण

	स_रखो(&attr, 0, माप(काष्ठा perf_event_attr));
	attr.size = माप(काष्ठा perf_event_attr);
	attr.type = PERF_TYPE_HARDWARE;
	attr.sample_type = evsel->core.attr.sample_type & PERF_SAMPLE_MASK;
	attr.sample_type |= PERF_SAMPLE_IP | PERF_SAMPLE_TID |
			    PERF_SAMPLE_PERIOD;
	अगर (eपंचांग->समयless_decoding)
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

	अगर (eपंचांग->synth_opts.branches) अणु
		attr.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
		attr.sample_period = 1;
		attr.sample_type |= PERF_SAMPLE_ADDR;
		err = cs_eपंचांग__synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		eपंचांग->sample_branches = true;
		eपंचांग->branches_sample_type = attr.sample_type;
		eपंचांग->branches_id = id;
		id += 1;
		attr.sample_type &= ~(u64)PERF_SAMPLE_ADDR;
	पूर्ण

	अगर (eपंचांग->synth_opts.last_branch) अणु
		attr.sample_type |= PERF_SAMPLE_BRANCH_STACK;
		/*
		 * We करोn't use the hardware index, but the sample generation
		 * code uses the new क्रमmat branch_stack with this field,
		 * so the event attributes must indicate that it's present.
		 */
		attr.branch_sample_type |= PERF_SAMPLE_BRANCH_HW_INDEX;
	पूर्ण

	अगर (eपंचांग->synth_opts.inकाष्ठाions) अणु
		attr.config = PERF_COUNT_HW_INSTRUCTIONS;
		attr.sample_period = eपंचांग->synth_opts.period;
		eपंचांग->inकाष्ठाions_sample_period = attr.sample_period;
		err = cs_eपंचांग__synth_event(session, &attr, id);
		अगर (err)
			वापस err;
		eपंचांग->sample_inकाष्ठाions = true;
		eपंचांग->inकाष्ठाions_sample_type = attr.sample_type;
		eपंचांग->inकाष्ठाions_id = id;
		id += 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__sample(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			  काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;
	पूर्णांक ret;
	u8 trace_chan_id = tidq->trace_chan_id;
	u64 instrs_prev;

	/* Get inकाष्ठाions reमुख्यder from previous packet */
	instrs_prev = tidq->period_inकाष्ठाions;

	tidq->period_inकाष्ठाions += tidq->packet->instr_count;

	/*
	 * Record a branch when the last inकाष्ठाion in
	 * PREV_PACKET is a branch.
	 */
	अगर (eपंचांग->synth_opts.last_branch &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE &&
	    tidq->prev_packet->last_instr_taken_branch)
		cs_eपंचांग__update_last_branch_rb(eपंचांगq, tidq);

	अगर (eपंचांग->sample_inकाष्ठाions &&
	    tidq->period_inकाष्ठाions >= eपंचांग->inकाष्ठाions_sample_period) अणु
		/*
		 * Emit inकाष्ठाion sample periodically
		 * TODO: allow period to be defined in cycles and घड़ी समय
		 */

		/*
		 * Below diagram demonstrates the inकाष्ठाion samples
		 * generation flows:
		 *
		 *    Instrs     Instrs       Instrs       Instrs
		 *   Sample(n)  Sample(n+1)  Sample(n+2)  Sample(n+3)
		 *    |            |            |            |
		 *    V            V            V            V
		 *   --------------------------------------------------
		 *            ^                                  ^
		 *            |                                  |
		 *         Period                             Period
		 *    inकाष्ठाions(Pi)                   inकाष्ठाions(Pi')
		 *
		 *            |                                  |
		 *            \---------------- -----------------/
		 *                             V
		 *                 tidq->packet->instr_count
		 *
		 * Instrs Sample(n...) are the synthesised samples occurring
		 * every eपंचांग->inकाष्ठाions_sample_period inकाष्ठाions - as
		 * defined on the perf command line.  Sample(n) is being the
		 * last sample beक्रमe the current eपंचांग packet, n+1 to n+3
		 * samples are generated from the current eपंचांग packet.
		 *
		 * tidq->packet->instr_count represents the number of
		 * inकाष्ठाions in the current eपंचांग packet.
		 *
		 * Period inकाष्ठाions (Pi) contains the the number of
		 * inकाष्ठाions executed after the sample poपूर्णांक(n) from the
		 * previous eपंचांग packet.  This will always be less than
		 * eपंचांग->inकाष्ठाions_sample_period.
		 *
		 * When generate new samples, it combines with two parts
		 * inकाष्ठाions, one is the tail of the old packet and another
		 * is the head of the new coming packet, to generate
		 * sample(n+1); sample(n+2) and sample(n+3) consume the
		 * inकाष्ठाions with sample period.  After sample(n+3), the rest
		 * inकाष्ठाions will be used by later packet and it is asचिन्हित
		 * to tidq->period_inकाष्ठाions क्रम next round calculation.
		 */

		/*
		 * Get the initial offset पूर्णांकo the current packet inकाष्ठाions;
		 * entry conditions ensure that instrs_prev is less than
		 * eपंचांग->inकाष्ठाions_sample_period.
		 */
		u64 offset = eपंचांग->inकाष्ठाions_sample_period - instrs_prev;
		u64 addr;

		/* Prepare last branches क्रम inकाष्ठाion sample */
		अगर (eपंचांग->synth_opts.last_branch)
			cs_eपंचांग__copy_last_branch_rb(eपंचांगq, tidq);

		जबतक (tidq->period_inकाष्ठाions >=
				eपंचांग->inकाष्ठाions_sample_period) अणु
			/*
			 * Calculate the address of the sampled inकाष्ठाion (-1
			 * as sample is reported as though inकाष्ठाion has just
			 * been executed, but PC has not advanced to next
			 * inकाष्ठाion)
			 */
			addr = cs_eपंचांग__instr_addr(eपंचांगq, trace_chan_id,
						  tidq->packet, offset - 1);
			ret = cs_eपंचांग__synth_inकाष्ठाion_sample(
				eपंचांगq, tidq, addr,
				eपंचांग->inकाष्ठाions_sample_period);
			अगर (ret)
				वापस ret;

			offset += eपंचांग->inकाष्ठाions_sample_period;
			tidq->period_inकाष्ठाions -=
				eपंचांग->inकाष्ठाions_sample_period;
		पूर्ण
	पूर्ण

	अगर (eपंचांग->sample_branches) अणु
		bool generate_sample = false;

		/* Generate sample क्रम tracing on packet */
		अगर (tidq->prev_packet->sample_type == CS_ETM_DISCONTINUITY)
			generate_sample = true;

		/* Generate sample क्रम branch taken packet */
		अगर (tidq->prev_packet->sample_type == CS_ETM_RANGE &&
		    tidq->prev_packet->last_instr_taken_branch)
			generate_sample = true;

		अगर (generate_sample) अणु
			ret = cs_eपंचांग__synth_branch_sample(eपंचांगq, tidq);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	cs_eपंचांग__packet_swap(eपंचांग, tidq);

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__exception(काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	/*
	 * When the exception packet is inserted, whether the last inकाष्ठाion
	 * in previous range packet is taken branch or not, we need to क्रमce
	 * to set 'prev_packet->last_instr_taken_branch' to true.  This ensures
	 * to generate branch sample क्रम the inकाष्ठाion range beक्रमe the
	 * exception is trapped to kernel or beक्रमe the exception वापसing.
	 *
	 * The exception packet includes the dummy address values, so करोn't
	 * swap PACKET with PREV_PACKET.  This keeps PREV_PACKET to be useful
	 * क्रम generating inकाष्ठाion and branch samples.
	 */
	अगर (tidq->prev_packet->sample_type == CS_ETM_RANGE)
		tidq->prev_packet->last_instr_taken_branch = true;

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__flush(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			 काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	पूर्णांक err = 0;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = eपंचांगq->eपंचांग;

	/* Handle start tracing packet */
	अगर (tidq->prev_packet->sample_type == CS_ETM_EMPTY)
		जाओ swap_packet;

	अगर (eपंचांगq->eपंचांग->synth_opts.last_branch &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE) अणु
		u64 addr;

		/* Prepare last branches क्रम inकाष्ठाion sample */
		cs_eपंचांग__copy_last_branch_rb(eपंचांगq, tidq);

		/*
		 * Generate a last branch event क्रम the branches left in the
		 * circular buffer at the end of the trace.
		 *
		 * Use the address of the end of the last reported execution
		 * range
		 */
		addr = cs_eपंचांग__last_executed_instr(tidq->prev_packet);

		err = cs_eपंचांग__synth_inकाष्ठाion_sample(
			eपंचांगq, tidq, addr,
			tidq->period_inकाष्ठाions);
		अगर (err)
			वापस err;

		tidq->period_inकाष्ठाions = 0;

	पूर्ण

	अगर (eपंचांग->sample_branches &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE) अणु
		err = cs_eपंचांग__synth_branch_sample(eपंचांगq, tidq);
		अगर (err)
			वापस err;
	पूर्ण

swap_packet:
	cs_eपंचांग__packet_swap(eपंचांग, tidq);

	/* Reset last branches after flush the trace */
	अगर (eपंचांग->synth_opts.last_branch)
		cs_eपंचांग__reset_last_branch_rb(tidq);

	वापस err;
पूर्ण

अटल पूर्णांक cs_eपंचांग__end_block(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			     काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	पूर्णांक err;

	/*
	 * It has no new packet coming and 'etmq->packet' contains the stale
	 * packet which was set at the previous समय with packets swapping;
	 * so skip to generate branch sample to aव्योम stale packet.
	 *
	 * For this हाल only flush branch stack and generate a last branch
	 * event क्रम the branches left in the circular buffer at the end of
	 * the trace.
	 */
	अगर (eपंचांगq->eपंचांग->synth_opts.last_branch &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE) अणु
		u64 addr;

		/* Prepare last branches क्रम inकाष्ठाion sample */
		cs_eपंचांग__copy_last_branch_rb(eपंचांगq, tidq);

		/*
		 * Use the address of the end of the last reported execution
		 * range.
		 */
		addr = cs_eपंचांग__last_executed_instr(tidq->prev_packet);

		err = cs_eपंचांग__synth_inकाष्ठाion_sample(
			eपंचांगq, tidq, addr,
			tidq->period_inकाष्ठाions);
		अगर (err)
			वापस err;

		tidq->period_inकाष्ठाions = 0;
	पूर्ण

	वापस 0;
पूर्ण
/*
 * cs_eपंचांग__get_data_block: Fetch a block from the auxtrace_buffer queue
 *			   अगर need be.
 * Returns:	< 0	अगर error
 *		= 0	अगर no more auxtrace_buffer to पढ़ो
 *		> 0	अगर the current buffer isn't empty yet
 */
अटल पूर्णांक cs_eपंचांग__get_data_block(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	पूर्णांक ret;

	अगर (!eपंचांगq->buf_len) अणु
		ret = cs_eपंचांग__get_trace(eपंचांगq);
		अगर (ret <= 0)
			वापस ret;
		/*
		 * We cannot assume consecutive blocks in the data file
		 * are contiguous, reset the decoder to क्रमce re-sync.
		 */
		ret = cs_eपंचांग_decoder__reset(eपंचांगq->decoder);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस eपंचांगq->buf_len;
पूर्ण

अटल bool cs_eपंचांग__is_svc_instr(काष्ठा cs_eपंचांग_queue *eपंचांगq, u8 trace_chan_id,
				 काष्ठा cs_eपंचांग_packet *packet,
				 u64 end_addr)
अणु
	/* Initialise to keep compiler happy */
	u16 instr16 = 0;
	u32 instr32 = 0;
	u64 addr;

	चयन (packet->isa) अणु
	हाल CS_ETM_ISA_T32:
		/*
		 * The SVC of T32 is defined in ARM DDI 0487D.a, F5.1.247:
		 *
		 *  b'15         b'8
		 * +-----------------+--------+
		 * | 1 1 0 1 1 1 1 1 |  imm8  |
		 * +-----------------+--------+
		 *
		 * According to the specअगरication, it only defines SVC क्रम T32
		 * with 16 bits inकाष्ठाion and has no definition क्रम 32bits;
		 * so below only पढ़ो 2 bytes as inकाष्ठाion size क्रम T32.
		 */
		addr = end_addr - 2;
		cs_eपंचांग__mem_access(eपंचांगq, trace_chan_id, addr,
				   माप(instr16), (u8 *)&instr16);
		अगर ((instr16 & 0xFF00) == 0xDF00)
			वापस true;

		अवरोध;
	हाल CS_ETM_ISA_A32:
		/*
		 * The SVC of A32 is defined in ARM DDI 0487D.a, F5.1.247:
		 *
		 *  b'31 b'28 b'27 b'24
		 * +---------+---------+-------------------------+
		 * |  !1111  | 1 1 1 1 |        imm24            |
		 * +---------+---------+-------------------------+
		 */
		addr = end_addr - 4;
		cs_eपंचांग__mem_access(eपंचांगq, trace_chan_id, addr,
				   माप(instr32), (u8 *)&instr32);
		अगर ((instr32 & 0x0F000000) == 0x0F000000 &&
		    (instr32 & 0xF0000000) != 0xF0000000)
			वापस true;

		अवरोध;
	हाल CS_ETM_ISA_A64:
		/*
		 * The SVC of A64 is defined in ARM DDI 0487D.a, C6.2.294:
		 *
		 *  b'31               b'21           b'4     b'0
		 * +-----------------------+---------+-----------+
		 * | 1 1 0 1 0 1 0 0 0 0 0 |  imm16  | 0 0 0 0 1 |
		 * +-----------------------+---------+-----------+
		 */
		addr = end_addr - 4;
		cs_eपंचांग__mem_access(eपंचांगq, trace_chan_id, addr,
				   माप(instr32), (u8 *)&instr32);
		अगर ((instr32 & 0xFFE0001F) == 0xd4000001)
			वापस true;

		अवरोध;
	हाल CS_ETM_ISA_UNKNOWN:
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool cs_eपंचांग__is_syscall(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			       काष्ठा cs_eपंचांग_traceid_queue *tidq, u64 magic)
अणु
	u8 trace_chan_id = tidq->trace_chan_id;
	काष्ठा cs_eपंचांग_packet *packet = tidq->packet;
	काष्ठा cs_eपंचांग_packet *prev_packet = tidq->prev_packet;

	अगर (magic == __perf_cs_eपंचांगv3_magic)
		अगर (packet->exception_number == CS_ETMV3_EXC_SVC)
			वापस true;

	/*
	 * ETMv4 exception type CS_ETMV4_EXC_CALL covers SVC, SMC and
	 * HVC हालs; need to check अगर it's SVC inकाष्ठाion based on
	 * packet address.
	 */
	अगर (magic == __perf_cs_eपंचांगv4_magic) अणु
		अगर (packet->exception_number == CS_ETMV4_EXC_CALL &&
		    cs_eपंचांग__is_svc_instr(eपंचांगq, trace_chan_id, prev_packet,
					 prev_packet->end_addr))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool cs_eपंचांग__is_async_exception(काष्ठा cs_eपंचांग_traceid_queue *tidq,
				       u64 magic)
अणु
	काष्ठा cs_eपंचांग_packet *packet = tidq->packet;

	अगर (magic == __perf_cs_eपंचांगv3_magic)
		अगर (packet->exception_number == CS_ETMV3_EXC_DEBUG_HALT ||
		    packet->exception_number == CS_ETMV3_EXC_ASYNC_DATA_ABORT ||
		    packet->exception_number == CS_ETMV3_EXC_PE_RESET ||
		    packet->exception_number == CS_ETMV3_EXC_IRQ ||
		    packet->exception_number == CS_ETMV3_EXC_FIQ)
			वापस true;

	अगर (magic == __perf_cs_eपंचांगv4_magic)
		अगर (packet->exception_number == CS_ETMV4_EXC_RESET ||
		    packet->exception_number == CS_ETMV4_EXC_DEBUG_HALT ||
		    packet->exception_number == CS_ETMV4_EXC_SYSTEM_ERROR ||
		    packet->exception_number == CS_ETMV4_EXC_INST_DEBUG ||
		    packet->exception_number == CS_ETMV4_EXC_DATA_DEBUG ||
		    packet->exception_number == CS_ETMV4_EXC_IRQ ||
		    packet->exception_number == CS_ETMV4_EXC_FIQ)
			वापस true;

	वापस false;
पूर्ण

अटल bool cs_eपंचांग__is_sync_exception(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				      काष्ठा cs_eपंचांग_traceid_queue *tidq,
				      u64 magic)
अणु
	u8 trace_chan_id = tidq->trace_chan_id;
	काष्ठा cs_eपंचांग_packet *packet = tidq->packet;
	काष्ठा cs_eपंचांग_packet *prev_packet = tidq->prev_packet;

	अगर (magic == __perf_cs_eपंचांगv3_magic)
		अगर (packet->exception_number == CS_ETMV3_EXC_SMC ||
		    packet->exception_number == CS_ETMV3_EXC_HYP ||
		    packet->exception_number == CS_ETMV3_EXC_JAZELLE_THUMBEE ||
		    packet->exception_number == CS_ETMV3_EXC_UNDEFINED_INSTR ||
		    packet->exception_number == CS_ETMV3_EXC_PREFETCH_ABORT ||
		    packet->exception_number == CS_ETMV3_EXC_DATA_FAULT ||
		    packet->exception_number == CS_ETMV3_EXC_GENERIC)
			वापस true;

	अगर (magic == __perf_cs_eपंचांगv4_magic) अणु
		अगर (packet->exception_number == CS_ETMV4_EXC_TRAP ||
		    packet->exception_number == CS_ETMV4_EXC_ALIGNMENT ||
		    packet->exception_number == CS_ETMV4_EXC_INST_FAULT ||
		    packet->exception_number == CS_ETMV4_EXC_DATA_FAULT)
			वापस true;

		/*
		 * For CS_ETMV4_EXC_CALL, except SVC other inकाष्ठाions
		 * (SMC, HVC) are taken as sync exceptions.
		 */
		अगर (packet->exception_number == CS_ETMV4_EXC_CALL &&
		    !cs_eपंचांग__is_svc_instr(eपंचांगq, trace_chan_id, prev_packet,
					  prev_packet->end_addr))
			वापस true;

		/*
		 * ETMv4 has 5 bits क्रम exception number; अगर the numbers
		 * are in the range ( CS_ETMV4_EXC_FIQ, CS_ETMV4_EXC_END ]
		 * they are implementation defined exceptions.
		 *
		 * For this हाल, simply take it as sync exception.
		 */
		अगर (packet->exception_number > CS_ETMV4_EXC_FIQ &&
		    packet->exception_number <= CS_ETMV4_EXC_END)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक cs_eपंचांग__set_sample_flags(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				    काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	काष्ठा cs_eपंचांग_packet *packet = tidq->packet;
	काष्ठा cs_eपंचांग_packet *prev_packet = tidq->prev_packet;
	u8 trace_chan_id = tidq->trace_chan_id;
	u64 magic;
	पूर्णांक ret;

	चयन (packet->sample_type) अणु
	हाल CS_ETM_RANGE:
		/*
		 * Immediate branch inकाष्ठाion without neither link nor
		 * वापस flag, it's normal branch inकाष्ठाion within
		 * the function.
		 */
		अगर (packet->last_instr_type == OCSD_INSTR_BR &&
		    packet->last_instr_subtype == OCSD_S_INSTR_NONE) अणु
			packet->flags = PERF_IP_FLAG_BRANCH;

			अगर (packet->last_instr_cond)
				packet->flags |= PERF_IP_FLAG_CONDITIONAL;
		पूर्ण

		/*
		 * Immediate branch inकाष्ठाion with link (e.g. BL), this is
		 * branch inकाष्ठाion क्रम function call.
		 */
		अगर (packet->last_instr_type == OCSD_INSTR_BR &&
		    packet->last_instr_subtype == OCSD_S_INSTR_BR_LINK)
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_CALL;

		/*
		 * Indirect branch inकाष्ठाion with link (e.g. BLR), this is
		 * branch inकाष्ठाion क्रम function call.
		 */
		अगर (packet->last_instr_type == OCSD_INSTR_BR_INसूचीECT &&
		    packet->last_instr_subtype == OCSD_S_INSTR_BR_LINK)
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_CALL;

		/*
		 * Indirect branch inकाष्ठाion with subtype of
		 * OCSD_S_INSTR_V7_IMPLIED_RET, this is explicit hपूर्णांक क्रम
		 * function वापस क्रम A32/T32.
		 */
		अगर (packet->last_instr_type == OCSD_INSTR_BR_INसूचीECT &&
		    packet->last_instr_subtype == OCSD_S_INSTR_V7_IMPLIED_RET)
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_RETURN;

		/*
		 * Indirect branch inकाष्ठाion without link (e.g. BR), usually
		 * this is used क्रम function वापस, especially क्रम functions
		 * within dynamic link lib.
		 */
		अगर (packet->last_instr_type == OCSD_INSTR_BR_INसूचीECT &&
		    packet->last_instr_subtype == OCSD_S_INSTR_NONE)
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_RETURN;

		/* Return inकाष्ठाion क्रम function वापस. */
		अगर (packet->last_instr_type == OCSD_INSTR_BR_INसूचीECT &&
		    packet->last_instr_subtype == OCSD_S_INSTR_V8_RET)
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_RETURN;

		/*
		 * Decoder might insert a discontinuity in the middle of
		 * inकाष्ठाion packets, fixup prev_packet with flag
		 * PERF_IP_FLAG_TRACE_BEGIN to indicate restarting trace.
		 */
		अगर (prev_packet->sample_type == CS_ETM_DISCONTINUITY)
			prev_packet->flags |= PERF_IP_FLAG_BRANCH |
					      PERF_IP_FLAG_TRACE_BEGIN;

		/*
		 * If the previous packet is an exception वापस packet
		 * and the वापस address just follows SVC inकाष्ठाion,
		 * it needs to calibrate the previous packet sample flags
		 * as PERF_IP_FLAG_SYSCALLRET.
		 */
		अगर (prev_packet->flags == (PERF_IP_FLAG_BRANCH |
					   PERF_IP_FLAG_RETURN |
					   PERF_IP_FLAG_INTERRUPT) &&
		    cs_eपंचांग__is_svc_instr(eपंचांगq, trace_chan_id,
					 packet, packet->start_addr))
			prev_packet->flags = PERF_IP_FLAG_BRANCH |
					     PERF_IP_FLAG_RETURN |
					     PERF_IP_FLAG_SYSCALLRET;
		अवरोध;
	हाल CS_ETM_DISCONTINUITY:
		/*
		 * The trace is discontinuous, अगर the previous packet is
		 * inकाष्ठाion packet, set flag PERF_IP_FLAG_TRACE_END
		 * क्रम previous packet.
		 */
		अगर (prev_packet->sample_type == CS_ETM_RANGE)
			prev_packet->flags |= PERF_IP_FLAG_BRANCH |
					      PERF_IP_FLAG_TRACE_END;
		अवरोध;
	हाल CS_ETM_EXCEPTION:
		ret = cs_eपंचांग__get_magic(packet->trace_chan_id, &magic);
		अगर (ret)
			वापस ret;

		/* The exception is क्रम प्रणाली call. */
		अगर (cs_eपंचांग__is_syscall(eपंचांगq, tidq, magic))
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_CALL |
					PERF_IP_FLAG_SYSCALLRET;
		/*
		 * The exceptions are triggered by बाह्यal संकेतs from bus,
		 * पूर्णांकerrupt controller, debug module, PE reset or halt.
		 */
		अन्यथा अगर (cs_eपंचांग__is_async_exception(tidq, magic))
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_CALL |
					PERF_IP_FLAG_ASYNC |
					PERF_IP_FLAG_INTERRUPT;
		/*
		 * Otherwise, exception is caused by trap, inकाष्ठाion &
		 * data fault, or alignment errors.
		 */
		अन्यथा अगर (cs_eपंचांग__is_sync_exception(eपंचांगq, tidq, magic))
			packet->flags = PERF_IP_FLAG_BRANCH |
					PERF_IP_FLAG_CALL |
					PERF_IP_FLAG_INTERRUPT;

		/*
		 * When the exception packet is inserted, since exception
		 * packet is not used standalone क्रम generating samples
		 * and it's affiliation to the previous inकाष्ठाion range
		 * packet; so set previous range packet flags to tell perf
		 * it is an exception taken branch.
		 */
		अगर (prev_packet->sample_type == CS_ETM_RANGE)
			prev_packet->flags = packet->flags;
		अवरोध;
	हाल CS_ETM_EXCEPTION_RET:
		/*
		 * When the exception वापस packet is inserted, since
		 * exception वापस packet is not used standalone क्रम
		 * generating samples and it's affiliation to the previous
		 * inकाष्ठाion range packet; so set previous range packet
		 * flags to tell perf it is an exception वापस branch.
		 *
		 * The exception वापस can be क्रम either प्रणाली call or
		 * other exception types; unक्रमtunately the packet करोesn't
		 * contain exception type related info so we cannot decide
		 * the exception type purely based on exception वापस packet.
		 * If we record the exception number from exception packet and
		 * reuse it क्रम exception वापस packet, this is not reliable
		 * due the trace can be discontinuity or the पूर्णांकerrupt can
		 * be nested, thus the recorded exception number cannot be
		 * used क्रम exception वापस packet क्रम these two हालs.
		 *
		 * For exception वापस packet, we only need to distinguish the
		 * packet is क्रम प्रणाली call or क्रम other types.  Thus the
		 * decision can be deferred when receive the next packet which
		 * contains the वापस address, based on the वापस address we
		 * can पढ़ो out the previous inकाष्ठाion and check अगर it's a
		 * प्रणाली call inकाष्ठाion and then calibrate the sample flag
		 * as needed.
		 */
		अगर (prev_packet->sample_type == CS_ETM_RANGE)
			prev_packet->flags = PERF_IP_FLAG_BRANCH |
					     PERF_IP_FLAG_RETURN |
					     PERF_IP_FLAG_INTERRUPT;
		अवरोध;
	हाल CS_ETM_EMPTY:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__decode_data_block(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार processed = 0;

	/*
	 * Packets are decoded and added to the decoder's packet queue
	 * until the decoder packet processing callback has requested that
	 * processing stops or there is nothing left in the buffer.  Normal
	 * operations that stop processing are a बारtamp packet or a full
	 * decoder buffer queue.
	 */
	ret = cs_eपंचांग_decoder__process_data_block(eपंचांगq->decoder,
						 eपंचांगq->offset,
						 &eपंचांगq->buf[eपंचांगq->buf_used],
						 eपंचांगq->buf_len,
						 &processed);
	अगर (ret)
		जाओ out;

	eपंचांगq->offset += processed;
	eपंचांगq->buf_used += processed;
	eपंचांगq->buf_len -= processed;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_traceid_queue(काष्ठा cs_eपंचांग_queue *eपंचांगq,
					 काष्ठा cs_eपंचांग_traceid_queue *tidq)
अणु
	पूर्णांक ret;
	काष्ठा cs_eपंचांग_packet_queue *packet_queue;

	packet_queue = &tidq->packet_queue;

	/* Process each packet in this chunk */
	जबतक (1) अणु
		ret = cs_eपंचांग_decoder__get_packet(packet_queue,
						 tidq->packet);
		अगर (ret <= 0)
			/*
			 * Stop processing this chunk on
			 * end of data or error
			 */
			अवरोध;

		/*
		 * Since packet addresses are swapped in packet
		 * handling within below चयन() statements,
		 * thus setting sample flags must be called
		 * prior to चयन() statement to use address
		 * inक्रमmation beक्रमe packets swapping.
		 */
		ret = cs_eपंचांग__set_sample_flags(eपंचांगq, tidq);
		अगर (ret < 0)
			अवरोध;

		चयन (tidq->packet->sample_type) अणु
		हाल CS_ETM_RANGE:
			/*
			 * If the packet contains an inकाष्ठाion
			 * range, generate inकाष्ठाion sequence
			 * events.
			 */
			cs_eपंचांग__sample(eपंचांगq, tidq);
			अवरोध;
		हाल CS_ETM_EXCEPTION:
		हाल CS_ETM_EXCEPTION_RET:
			/*
			 * If the exception packet is coming,
			 * make sure the previous inकाष्ठाion
			 * range packet to be handled properly.
			 */
			cs_eपंचांग__exception(tidq);
			अवरोध;
		हाल CS_ETM_DISCONTINUITY:
			/*
			 * Discontinuity in trace, flush
			 * previous branch stack
			 */
			cs_eपंचांग__flush(eपंचांगq, tidq);
			अवरोध;
		हाल CS_ETM_EMPTY:
			/*
			 * Should not receive empty packet,
			 * report error.
			 */
			pr_err("CS ETM Trace: empty packet\n");
			वापस -EINVAL;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cs_eपंचांग__clear_all_traceid_queues(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	पूर्णांक idx;
	काष्ठा पूर्णांक_node *inode;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;
	काष्ठा पूर्णांकlist *traceid_queues_list = eपंचांगq->traceid_queues_list;

	पूर्णांकlist__क्रम_each_entry(inode, traceid_queues_list) अणु
		idx = (पूर्णांक)(पूर्णांकptr_t)inode->priv;
		tidq = eपंचांगq->traceid_queues[idx];

		/* Ignore वापस value */
		cs_eपंचांग__process_traceid_queue(eपंचांगq, tidq);

		/*
		 * Generate an inकाष्ठाion sample with the reमुख्यing
		 * branchstack entries.
		 */
		cs_eपंचांग__flush(eपंचांगq, tidq);
	पूर्ण
पूर्ण

अटल पूर्णांक cs_eपंचांग__run_decoder(काष्ठा cs_eपंचांग_queue *eपंचांगq)
अणु
	पूर्णांक err = 0;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;

	tidq = cs_eपंचांग__eपंचांगq_get_traceid_queue(eपंचांगq, CS_ETM_PER_THREAD_TRACEID);
	अगर (!tidq)
		वापस -EINVAL;

	/* Go through each buffer in the queue and decode them one by one */
	जबतक (1) अणु
		err = cs_eपंचांग__get_data_block(eपंचांगq);
		अगर (err <= 0)
			वापस err;

		/* Run trace decoder until buffer consumed or end of trace */
		करो अणु
			err = cs_eपंचांग__decode_data_block(eपंचांगq);
			अगर (err)
				वापस err;

			/*
			 * Process each packet in this chunk, nothing to करो अगर
			 * an error occurs other than hoping the next one will
			 * be better.
			 */
			err = cs_eपंचांग__process_traceid_queue(eपंचांगq, tidq);

		पूर्ण जबतक (eपंचांगq->buf_len);

		अगर (err == 0)
			/* Flush any reमुख्यing branch stack entries */
			err = cs_eपंचांग__end_block(eपंचांगq, tidq);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_समयless_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
					   pid_t tid)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा auxtrace_queues *queues = &eपंचांग->queues;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		काष्ठा auxtrace_queue *queue = &eपंचांग->queues.queue_array[i];
		काष्ठा cs_eपंचांग_queue *eपंचांगq = queue->priv;
		काष्ठा cs_eपंचांग_traceid_queue *tidq;

		अगर (!eपंचांगq)
			जारी;

		tidq = cs_eपंचांग__eपंचांगq_get_traceid_queue(eपंचांगq,
						CS_ETM_PER_THREAD_TRACEID);

		अगर (!tidq)
			जारी;

		अगर ((tid == -1) || (tidq->tid == tid)) अणु
			cs_eपंचांग__set_pid_tid_cpu(eपंचांग, tidq);
			cs_eपंचांग__run_decoder(eपंचांगq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_queues(काष्ठा cs_eपंचांग_auxtrace *eपंचांग)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cs_queue_nr, queue_nr;
	u8 trace_chan_id;
	u64 बारtamp;
	काष्ठा auxtrace_queue *queue;
	काष्ठा cs_eपंचांग_queue *eपंचांगq;
	काष्ठा cs_eपंचांग_traceid_queue *tidq;

	जबतक (1) अणु
		अगर (!eपंचांग->heap.heap_cnt)
			जाओ out;

		/* Take the entry at the top of the min heap */
		cs_queue_nr = eपंचांग->heap.heap_array[0].queue_nr;
		queue_nr = TO_QUEUE_NR(cs_queue_nr);
		trace_chan_id = TO_TRACE_CHAN_ID(cs_queue_nr);
		queue = &eपंचांग->queues.queue_array[queue_nr];
		eपंचांगq = queue->priv;

		/*
		 * Remove the top entry from the heap since we are about
		 * to process it.
		 */
		auxtrace_heap__pop(&eपंचांग->heap);

		tidq  = cs_eपंचांग__eपंचांगq_get_traceid_queue(eपंचांगq, trace_chan_id);
		अगर (!tidq) अणु
			/*
			 * No traceID queue has been allocated क्रम this traceID,
			 * which means something somewhere went very wrong.  No
			 * other choice than simply निकास.
			 */
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * Packets associated with this बारtamp are alपढ़ोy in
		 * the eपंचांगq's traceID queue, so process them.
		 */
		ret = cs_eपंचांग__process_traceid_queue(eपंचांगq, tidq);
		अगर (ret < 0)
			जाओ out;

		/*
		 * Packets क्रम this बारtamp have been processed, समय to
		 * move on to the next बारtamp, fetching a new auxtrace_buffer
		 * अगर need be.
		 */
refetch:
		ret = cs_eपंचांग__get_data_block(eपंचांगq);
		अगर (ret < 0)
			जाओ out;

		/*
		 * No more auxtrace_buffers to process in this eपंचांगq, simply
		 * move on to another entry in the auxtrace_heap.
		 */
		अगर (!ret)
			जारी;

		ret = cs_eपंचांग__decode_data_block(eपंचांगq);
		अगर (ret)
			जाओ out;

		बारtamp = cs_eपंचांग__eपंचांगq_get_बारtamp(eपंचांगq, &trace_chan_id);

		अगर (!बारtamp) अणु
			/*
			 * Function cs_eपंचांग__decode_data_block() वापसs when
			 * there is no more traces to decode in the current
			 * auxtrace_buffer OR when a बारtamp has been
			 * encountered on any of the traceID queues.  Since we
			 * did not get a बारtamp, there is no more traces to
			 * process in this auxtrace_buffer.  As such empty and
			 * flush all traceID queues.
			 */
			cs_eपंचांग__clear_all_traceid_queues(eपंचांगq);

			/* Fetch another auxtrace_buffer क्रम this eपंचांगq */
			जाओ refetch;
		पूर्ण

		/*
		 * Add to the min heap the बारtamp क्रम packets that have
		 * just been decoded.  They will be processed and synthesized
		 * during the next call to cs_eपंचांग__process_traceid_queue() क्रम
		 * this queue/traceID.
		 */
		cs_queue_nr = TO_CS_QUEUE_NR(queue_nr, trace_chan_id);
		ret = auxtrace_heap__add(&eपंचांग->heap, cs_queue_nr, बारtamp);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_itrace_start(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
					जोड़ perf_event *event)
अणु
	काष्ठा thपढ़ो *th;

	अगर (eपंचांग->समयless_decoding)
		वापस 0;

	/*
	 * Add the tid/pid to the log so that we can get a match when
	 * we get a contextID from the decoder.
	 */
	th = machine__findnew_thपढ़ो(eपंचांग->machine,
				     event->itrace_start.pid,
				     event->itrace_start.tid);
	अगर (!th)
		वापस -ENOMEM;

	thपढ़ो__put(th);

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_चयन_cpu_wide(काष्ठा cs_eपंचांग_auxtrace *eपंचांग,
					   जोड़ perf_event *event)
अणु
	काष्ठा thपढ़ो *th;
	bool out = event->header.misc & PERF_RECORD_MISC_SWITCH_OUT;

	/*
	 * Context चयन in per-thपढ़ो mode are irrelevant since perf
	 * will start/stop tracing as the process is scheduled.
	 */
	अगर (eपंचांग->समयless_decoding)
		वापस 0;

	/*
	 * SWITCH_IN events carry the next process to be चयनed out जबतक
	 * SWITCH_OUT events carry the process to be चयनed in.  As such
	 * we करोn't care about IN events.
	 */
	अगर (!out)
		वापस 0;

	/*
	 * Add the tid/pid to the log so that we can get a match when
	 * we get a contextID from the decoder.
	 */
	th = machine__findnew_thपढ़ो(eपंचांग->machine,
				     event->context_चयन.next_prev_pid,
				     event->context_चयन.next_prev_tid);
	अगर (!th)
		वापस -ENOMEM;

	thपढ़ो__put(th);

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_event(काष्ठा perf_session *session,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample,
				 काष्ठा perf_tool *tool)
अणु
	पूर्णांक err = 0;
	u64 बारtamp;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = container_of(session->auxtrace,
						   काष्ठा cs_eपंचांग_auxtrace,
						   auxtrace);

	अगर (dump_trace)
		वापस 0;

	अगर (!tool->ordered_events) अणु
		pr_err("CoreSight ETM Trace requires ordered events\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sample->समय && (sample->समय != (u64) -1))
		बारtamp = sample->समय;
	अन्यथा
		बारtamp = 0;

	अगर (बारtamp || eपंचांग->समयless_decoding) अणु
		err = cs_eपंचांग__update_queues(eपंचांग);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (eपंचांग->समयless_decoding &&
	    event->header.type == PERF_RECORD_EXIT)
		वापस cs_eपंचांग__process_समयless_queues(eपंचांग,
						       event->विभाजन.tid);

	अगर (event->header.type == PERF_RECORD_ITRACE_START)
		वापस cs_eपंचांग__process_itrace_start(eपंचांग, event);
	अन्यथा अगर (event->header.type == PERF_RECORD_SWITCH_CPU_WIDE)
		वापस cs_eपंचांग__process_चयन_cpu_wide(eपंचांग, event);

	अगर (!eपंचांग->समयless_decoding &&
	    event->header.type == PERF_RECORD_AUX)
		वापस cs_eपंचांग__process_queues(eपंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__process_auxtrace_event(काष्ठा perf_session *session,
					  जोड़ perf_event *event,
					  काष्ठा perf_tool *tool __maybe_unused)
अणु
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = container_of(session->auxtrace,
						   काष्ठा cs_eपंचांग_auxtrace,
						   auxtrace);
	अगर (!eपंचांग->data_queued) अणु
		काष्ठा auxtrace_buffer *buffer;
		off_t  data_offset;
		पूर्णांक fd = perf_data__fd(session->data);
		bool is_pipe = perf_data__is_pipe(session->data);
		पूर्णांक err;

		अगर (is_pipe)
			data_offset = 0;
		अन्यथा अणु
			data_offset = lseek(fd, 0, प्रस्तुत_से);
			अगर (data_offset == -1)
				वापस -त्रुटि_सं;
		पूर्ण

		err = auxtrace_queues__add_event(&eपंचांग->queues, session,
						 event, data_offset, &buffer);
		अगर (err)
			वापस err;

		अगर (dump_trace)
			अगर (auxtrace_buffer__get_data(buffer, fd)) अणु
				cs_eपंचांग__dump_event(eपंचांग, buffer);
				auxtrace_buffer__put_data(buffer);
			पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool cs_eपंचांग__is_समयless_decoding(काष्ठा cs_eपंचांग_auxtrace *eपंचांग)
अणु
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = eपंचांग->session->evlist;
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

अटल स्थिर अक्षर * स्थिर cs_eपंचांग_global_header_fmts[] = अणु
	[CS_HEADER_VERSION]	= "	Header version		       %llx\n",
	[CS_PMU_TYPE_CPUS]	= "	PMU type/num cpus	       %llx\n",
	[CS_ETM_SNAPSHOT]	= "	Snapshot		       %llx\n",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs_eपंचांग_priv_fmts[] = अणु
	[CS_ETM_MAGIC]		= "	Magic number		       %llx\n",
	[CS_ETM_CPU]		= "	CPU			       %lld\n",
	[CS_ETM_NR_TRC_PARAMS]	= "	NR_TRC_PARAMS		       %llx\n",
	[CS_ETM_ETMCR]		= "	ETMCR			       %llx\n",
	[CS_ETM_ETMTRACEIDR]	= "	ETMTRACEIDR		       %llx\n",
	[CS_ETM_ETMCCER]	= "	ETMCCER			       %llx\n",
	[CS_ETM_ETMIDR]		= "	ETMIDR			       %llx\n",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs_eपंचांगv4_priv_fmts[] = अणु
	[CS_ETM_MAGIC]		= "	Magic number		       %llx\n",
	[CS_ETM_CPU]		= "	CPU			       %lld\n",
	[CS_ETM_NR_TRC_PARAMS]	= "	NR_TRC_PARAMS		       %llx\n",
	[CS_ETMV4_TRCCONFIGR]	= "	TRCCONFIGR		       %llx\n",
	[CS_ETMV4_TRCTRACEIDR]	= "	TRCTRACEIDR		       %llx\n",
	[CS_ETMV4_TRCIDR0]	= "	TRCIDR0			       %llx\n",
	[CS_ETMV4_TRCIDR1]	= "	TRCIDR1			       %llx\n",
	[CS_ETMV4_TRCIDR2]	= "	TRCIDR2			       %llx\n",
	[CS_ETMV4_TRCIDR8]	= "	TRCIDR8			       %llx\n",
	[CS_ETMV4_TRCAUTHSTATUS] = "	TRCAUTHSTATUS		       %llx\n",
पूर्ण;

अटल स्थिर अक्षर * स्थिर param_unk_fmt =
	"	Unknown parameter [%d]	       %llx\n";
अटल स्थिर अक्षर * स्थिर magic_unk_fmt =
	"	Magic number Unknown	       %llx\n";

अटल पूर्णांक cs_eपंचांग__prपूर्णांक_cpu_metadata_v0(__u64 *val, पूर्णांक *offset)
अणु
	पूर्णांक i = *offset, j, nr_params = 0, fmt_offset;
	__u64 magic;

	/* check magic value */
	magic = val[i + CS_ETM_MAGIC];
	अगर ((magic != __perf_cs_eपंचांगv3_magic) &&
	    (magic != __perf_cs_eपंचांगv4_magic)) अणु
		/* failure - note bad magic value */
		ख_लिखो(मानक_निकास, magic_unk_fmt, magic);
		वापस -EINVAL;
	पूर्ण

	/* prपूर्णांक common header block */
	ख_लिखो(मानक_निकास, cs_eपंचांग_priv_fmts[CS_ETM_MAGIC], val[i++]);
	ख_लिखो(मानक_निकास, cs_eपंचांग_priv_fmts[CS_ETM_CPU], val[i++]);

	अगर (magic == __perf_cs_eपंचांगv3_magic) अणु
		nr_params = CS_ETM_NR_TRC_PARAMS_V0;
		fmt_offset = CS_ETM_ETMCR;
		/* after common block, offset क्रमmat index past NR_PARAMS */
		क्रम (j = fmt_offset; j < nr_params + fmt_offset; j++, i++)
			ख_लिखो(मानक_निकास, cs_eपंचांग_priv_fmts[j], val[i]);
	पूर्ण अन्यथा अगर (magic == __perf_cs_eपंचांगv4_magic) अणु
		nr_params = CS_ETMV4_NR_TRC_PARAMS_V0;
		fmt_offset = CS_ETMV4_TRCCONFIGR;
		/* after common block, offset क्रमmat index past NR_PARAMS */
		क्रम (j = fmt_offset; j < nr_params + fmt_offset; j++, i++)
			ख_लिखो(मानक_निकास, cs_eपंचांगv4_priv_fmts[j], val[i]);
	पूर्ण
	*offset = i;
	वापस 0;
पूर्ण

अटल पूर्णांक cs_eपंचांग__prपूर्णांक_cpu_metadata_v1(__u64 *val, पूर्णांक *offset)
अणु
	पूर्णांक i = *offset, j, total_params = 0;
	__u64 magic;

	magic = val[i + CS_ETM_MAGIC];
	/* total params to prपूर्णांक is NR_PARAMS + common block size क्रम v1 */
	total_params = val[i + CS_ETM_NR_TRC_PARAMS] + CS_ETM_COMMON_BLK_MAX_V1;

	अगर (magic == __perf_cs_eपंचांगv3_magic) अणु
		क्रम (j = 0; j < total_params; j++, i++) अणु
			/* अगर newer record - could be excess params */
			अगर (j >= CS_ETM_PRIV_MAX)
				ख_लिखो(मानक_निकास, param_unk_fmt, j, val[i]);
			अन्यथा
				ख_लिखो(मानक_निकास, cs_eपंचांग_priv_fmts[j], val[i]);
		पूर्ण
	पूर्ण अन्यथा अगर (magic == __perf_cs_eपंचांगv4_magic) अणु
		क्रम (j = 0; j < total_params; j++, i++) अणु
			/* अगर newer record - could be excess params */
			अगर (j >= CS_ETMV4_PRIV_MAX)
				ख_लिखो(मानक_निकास, param_unk_fmt, j, val[i]);
			अन्यथा
				ख_लिखो(मानक_निकास, cs_eपंचांगv4_priv_fmts[j], val[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* failure - note bad magic value and error out */
		ख_लिखो(मानक_निकास, magic_unk_fmt, magic);
		वापस -EINVAL;
	पूर्ण
	*offset = i;
	वापस 0;
पूर्ण

अटल व्योम cs_eपंचांग__prपूर्णांक_auxtrace_info(__u64 *val, पूर्णांक num)
अणु
	पूर्णांक i, cpu = 0, version, err;

	/* bail out early on bad header version */
	version = val[0];
	अगर (version > CS_HEADER_CURRENT_VERSION) अणु
		/* failure.. वापस */
		ख_लिखो(मानक_निकास, "	Unknown Header Version = %x, ", version);
		ख_लिखो(मानक_निकास, "Version supported <= %x\n", CS_HEADER_CURRENT_VERSION);
		वापस;
	पूर्ण

	क्रम (i = 0; i < CS_HEADER_VERSION_MAX; i++)
		ख_लिखो(मानक_निकास, cs_eपंचांग_global_header_fmts[i], val[i]);

	क्रम (i = CS_HEADER_VERSION_MAX; cpu < num; cpu++) अणु
		अगर (version == 0)
			err = cs_eपंचांग__prपूर्णांक_cpu_metadata_v0(val, &i);
		अन्यथा अगर (version == 1)
			err = cs_eपंचांग__prपूर्णांक_cpu_metadata_v1(val, &i);
		अगर (err)
			वापस;
	पूर्ण
पूर्ण

/*
 * Read a single cpu parameter block from the auxtrace_info priv block.
 *
 * For version 1 there is a per cpu nr_params entry. If we are handling
 * version 1 file, then there may be less, the same, or more params
 * indicated by this value than the compile समय number we understand.
 *
 * For a version 0 info block, there are a fixed number, and we need to
 * fill out the nr_param value in the metadata we create.
 */
अटल u64 *cs_eपंचांग__create_meta_blk(u64 *buff_in, पूर्णांक *buff_in_offset,
				    पूर्णांक out_blk_size, पूर्णांक nr_params_v0)
अणु
	u64 *metadata = शून्य;
	पूर्णांक hdr_version;
	पूर्णांक nr_in_params, nr_out_params, nr_cmn_params;
	पूर्णांक i, k;

	metadata = zalloc(माप(*metadata) * out_blk_size);
	अगर (!metadata)
		वापस शून्य;

	/* पढ़ो block current index & version */
	i = *buff_in_offset;
	hdr_version = buff_in[CS_HEADER_VERSION];

	अगर (!hdr_version) अणु
	/* पढ़ो version 0 info block पूर्णांकo a version 1 metadata block  */
		nr_in_params = nr_params_v0;
		metadata[CS_ETM_MAGIC] = buff_in[i + CS_ETM_MAGIC];
		metadata[CS_ETM_CPU] = buff_in[i + CS_ETM_CPU];
		metadata[CS_ETM_NR_TRC_PARAMS] = nr_in_params;
		/* reमुख्यing block params at offset +1 from source */
		क्रम (k = CS_ETM_COMMON_BLK_MAX_V1 - 1; k < nr_in_params; k++)
			metadata[k + 1] = buff_in[i + k];
		/* version 0 has 2 common params */
		nr_cmn_params = 2;
	पूर्ण अन्यथा अणु
	/* पढ़ो version 1 info block - input and output nr_params may dअगरfer */
		/* version 1 has 3 common params */
		nr_cmn_params = 3;
		nr_in_params = buff_in[i + CS_ETM_NR_TRC_PARAMS];

		/* अगर input has more params than output - skip excess */
		nr_out_params = nr_in_params + nr_cmn_params;
		अगर (nr_out_params > out_blk_size)
			nr_out_params = out_blk_size;

		क्रम (k = CS_ETM_MAGIC; k < nr_out_params; k++)
			metadata[k] = buff_in[i + k];

		/* record the actual nr params we copied */
		metadata[CS_ETM_NR_TRC_PARAMS] = nr_out_params - nr_cmn_params;
	पूर्ण

	/* adjust in offset by number of in params used */
	i += nr_in_params + nr_cmn_params;
	*buff_in_offset = i;
	वापस metadata;
पूर्ण

पूर्णांक cs_eपंचांग__process_auxtrace_info(जोड़ perf_event *event,
				  काष्ठा perf_session *session)
अणु
	काष्ठा perf_record_auxtrace_info *auxtrace_info = &event->auxtrace_info;
	काष्ठा cs_eपंचांग_auxtrace *eपंचांग = शून्य;
	काष्ठा पूर्णांक_node *inode;
	अचिन्हित पूर्णांक pmu_type;
	पूर्णांक event_header_size = माप(काष्ठा perf_event_header);
	पूर्णांक info_header_size;
	पूर्णांक total_size = auxtrace_info->header.size;
	पूर्णांक priv_size = 0;
	पूर्णांक num_cpu, trcidr_idx;
	पूर्णांक err = 0;
	पूर्णांक i, j;
	u64 *ptr, *hdr = शून्य;
	u64 **metadata = शून्य;
	u64 hdr_version;

	/*
	 * माप(auxtrace_info_event::type) +
	 * माप(auxtrace_info_event::reserved) == 8
	 */
	info_header_size = 8;

	अगर (total_size < (event_header_size + info_header_size))
		वापस -EINVAL;

	priv_size = total_size - event_header_size - info_header_size;

	/* First the global part */
	ptr = (u64 *) auxtrace_info->priv;

	/* Look क्रम version of the header */
	hdr_version = ptr[0];
	अगर (hdr_version > CS_HEADER_CURRENT_VERSION) अणु
		/* prपूर्णांक routine will prपूर्णांक an error on bad version */
		अगर (dump_trace)
			cs_eपंचांग__prपूर्णांक_auxtrace_info(auxtrace_info->priv, 0);
		वापस -EINVAL;
	पूर्ण

	hdr = zalloc(माप(*hdr) * CS_HEADER_VERSION_MAX);
	अगर (!hdr)
		वापस -ENOMEM;

	/* Extract header inक्रमmation - see cs-eपंचांग.h क्रम क्रमmat */
	क्रम (i = 0; i < CS_HEADER_VERSION_MAX; i++)
		hdr[i] = ptr[i];
	num_cpu = hdr[CS_PMU_TYPE_CPUS] & 0xffffffff;
	pmu_type = (अचिन्हित पूर्णांक) ((hdr[CS_PMU_TYPE_CPUS] >> 32) &
				    0xffffffff);

	/*
	 * Create an RB tree क्रम traceID-metadata tuple.  Since the conversion
	 * has to be made क्रम each packet that माला_लो decoded, optimizing access
	 * in anything other than a sequential array is worth करोing.
	 */
	traceid_list = पूर्णांकlist__new(शून्य);
	अगर (!traceid_list) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_hdr;
	पूर्ण

	metadata = zalloc(माप(*metadata) * num_cpu);
	अगर (!metadata) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_traceid_list;
	पूर्ण

	/*
	 * The metadata is stored in the auxtrace_info section and encodes
	 * the configuration of the ARM embedded trace macrocell which is
	 * required by the trace decoder to properly decode the trace due
	 * to its highly compressed nature.
	 */
	क्रम (j = 0; j < num_cpu; j++) अणु
		अगर (ptr[i] == __perf_cs_eपंचांगv3_magic) अणु
			metadata[j] =
				cs_eपंचांग__create_meta_blk(ptr, &i,
							CS_ETM_PRIV_MAX,
							CS_ETM_NR_TRC_PARAMS_V0);

			/* The traceID is our handle */
			trcidr_idx = CS_ETM_ETMTRACEIDR;

		पूर्ण अन्यथा अगर (ptr[i] == __perf_cs_eपंचांगv4_magic) अणु
			metadata[j] =
				cs_eपंचांग__create_meta_blk(ptr, &i,
							CS_ETMV4_PRIV_MAX,
							CS_ETMV4_NR_TRC_PARAMS_V0);

			/* The traceID is our handle */
			trcidr_idx = CS_ETMV4_TRCTRACEIDR;
		पूर्ण

		अगर (!metadata[j]) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_metadata;
		पूर्ण

		/* Get an RB node क्रम this CPU */
		inode = पूर्णांकlist__findnew(traceid_list, metadata[j][trcidr_idx]);

		/* Something went wrong, no need to जारी */
		अगर (!inode) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_metadata;
		पूर्ण

		/*
		 * The node क्रम that CPU should not be taken.
		 * Back out अगर that's the हाल.
		 */
		अगर (inode->priv) अणु
			err = -EINVAL;
			जाओ err_मुक्त_metadata;
		पूर्ण
		/* All good, associate the traceID with the metadata poपूर्णांकer */
		inode->priv = metadata[j];
	पूर्ण

	/*
	 * Each of CS_HEADER_VERSION_MAX, CS_ETM_PRIV_MAX and
	 * CS_ETMV4_PRIV_MAX mark how many द्विगुन words are in the
	 * global metadata, and each cpu's metadata respectively.
	 * The following tests अगर the correct number of द्विगुन words was
	 * present in the auxtrace info section.
	 */
	अगर (i * 8 != priv_size) अणु
		err = -EINVAL;
		जाओ err_मुक्त_metadata;
	पूर्ण

	eपंचांग = zalloc(माप(*eपंचांग));

	अगर (!eपंचांग) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_metadata;
	पूर्ण

	err = auxtrace_queues__init(&eपंचांग->queues);
	अगर (err)
		जाओ err_मुक्त_eपंचांग;

	eपंचांग->session = session;
	eपंचांग->machine = &session->machines.host;

	eपंचांग->num_cpu = num_cpu;
	eपंचांग->pmu_type = pmu_type;
	eपंचांग->snapshot_mode = (hdr[CS_ETM_SNAPSHOT] != 0);
	eपंचांग->metadata = metadata;
	eपंचांग->auxtrace_type = auxtrace_info->type;
	eपंचांग->समयless_decoding = cs_eपंचांग__is_समयless_decoding(eपंचांग);

	eपंचांग->auxtrace.process_event = cs_eपंचांग__process_event;
	eपंचांग->auxtrace.process_auxtrace_event = cs_eपंचांग__process_auxtrace_event;
	eपंचांग->auxtrace.flush_events = cs_eपंचांग__flush_events;
	eपंचांग->auxtrace.मुक्त_events = cs_eपंचांग__मुक्त_events;
	eपंचांग->auxtrace.मुक्त = cs_eपंचांग__मुक्त;
	eपंचांग->auxtrace.evsel_is_auxtrace = cs_eपंचांग__evsel_is_auxtrace;
	session->auxtrace = &eपंचांग->auxtrace;

	eपंचांग->unknown_thपढ़ो = thपढ़ो__new(999999999, 999999999);
	अगर (!eपंचांग->unknown_thपढ़ो) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_queues;
	पूर्ण

	/*
	 * Initialize list node so that at thपढ़ो__zput() we can aव्योम
	 * segmentation fault at list_del_init().
	 */
	INIT_LIST_HEAD(&eपंचांग->unknown_thपढ़ो->node);

	err = thपढ़ो__set_comm(eपंचांग->unknown_thपढ़ो, "unknown", 0);
	अगर (err)
		जाओ err_delete_thपढ़ो;

	अगर (thपढ़ो__init_maps(eपंचांग->unknown_thपढ़ो, eपंचांग->machine)) अणु
		err = -ENOMEM;
		जाओ err_delete_thपढ़ो;
	पूर्ण

	अगर (dump_trace) अणु
		cs_eपंचांग__prपूर्णांक_auxtrace_info(auxtrace_info->priv, num_cpu);
		वापस 0;
	पूर्ण

	अगर (session->itrace_synth_opts->set) अणु
		eपंचांग->synth_opts = *session->itrace_synth_opts;
	पूर्ण अन्यथा अणु
		itrace_synth_opts__set_शेष(&eपंचांग->synth_opts,
				session->itrace_synth_opts->शेष_no_sample);
		eपंचांग->synth_opts.callchain = false;
	पूर्ण

	err = cs_eपंचांग__synth_events(eपंचांग, session);
	अगर (err)
		जाओ err_delete_thपढ़ो;

	err = auxtrace_queues__process_index(&eपंचांग->queues, session);
	अगर (err)
		जाओ err_delete_thपढ़ो;

	eपंचांग->data_queued = eपंचांग->queues.populated;

	वापस 0;

err_delete_thपढ़ो:
	thपढ़ो__zput(eपंचांग->unknown_thपढ़ो);
err_मुक्त_queues:
	auxtrace_queues__मुक्त(&eपंचांग->queues);
	session->auxtrace = शून्य;
err_मुक्त_eपंचांग:
	zमुक्त(&eपंचांग);
err_मुक्त_metadata:
	/* No need to check @metadata[j], मुक्त(शून्य) is supported */
	क्रम (j = 0; j < num_cpu; j++)
		zमुक्त(&metadata[j]);
	zमुक्त(&metadata);
err_मुक्त_traceid_list:
	पूर्णांकlist__delete(traceid_list);
err_मुक्त_hdr:
	zमुक्त(&hdr);
	/*
	 * At this poपूर्णांक, as a minimum we have valid header. Dump the rest of
	 * the info section - the prपूर्णांक routines will error out on काष्ठाural
	 * issues.
	 */
	अगर (dump_trace)
		cs_eपंचांग__prपूर्णांक_auxtrace_info(auxtrace_info->priv, num_cpu);
	वापस err;
पूर्ण
