<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015-2018 Linaro Limited.
 *
 * Author: Tor Jeremiassen <tor@ti.com>
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/coresight-pmu.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <खोलोcsd/c_api/खोलोcsd_c_api.h>
#समावेश <खोलोcsd/eपंचांगv4/trc_pkt_types_eपंचांगv4.h>
#समावेश <खोलोcsd/ocsd_अगर_types.h>

#समावेश "cs-etm.h"
#समावेश "cs-etm-decoder.h"
#समावेश "intlist.h"

/* use raw logging */
#अगर_घोषित CS_DEBUG_RAW
#घोषणा CS_LOG_RAW_FRAMES
#अगर_घोषित CS_RAW_PACKED
#घोषणा CS_RAW_DEBUG_FLAGS (OCSD_DFRMTR_UNPACKED_RAW_OUT | \
			    OCSD_DFRMTR_PACKED_RAW_OUT)
#अन्यथा
#घोषणा CS_RAW_DEBUG_FLAGS (OCSD_DFRMTR_UNPACKED_RAW_OUT)
#पूर्ण_अगर
#पूर्ण_अगर

काष्ठा cs_eपंचांग_decoder अणु
	व्योम *data;
	व्योम (*packet_prपूर्णांकer)(स्थिर अक्षर *msg);
	dcd_tree_handle_t dcd_tree;
	cs_eपंचांग_mem_cb_type mem_access;
	ocsd_datapath_resp_t prev_वापस;
पूर्ण;

अटल u32
cs_eपंचांग_decoder__mem_access(स्थिर व्योम *context,
			   स्थिर ocsd_vaddr_t address,
			   स्थिर ocsd_mem_space_acc_t mem_space __maybe_unused,
			   स्थिर u8 trace_chan_id,
			   स्थिर u32 req_size,
			   u8 *buffer)
अणु
	काष्ठा cs_eपंचांग_decoder *decoder = (काष्ठा cs_eपंचांग_decoder *) context;

	वापस decoder->mem_access(decoder->data, trace_chan_id,
				   address, req_size, buffer);
पूर्ण

पूर्णांक cs_eपंचांग_decoder__add_mem_access_cb(काष्ठा cs_eपंचांग_decoder *decoder,
				      u64 start, u64 end,
				      cs_eपंचांग_mem_cb_type cb_func)
अणु
	decoder->mem_access = cb_func;

	अगर (ocsd_dt_add_callback_trcid_mem_acc(decoder->dcd_tree, start, end,
					       OCSD_MEM_SPACE_ANY,
					       cs_eपंचांग_decoder__mem_access,
					       decoder))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक cs_eपंचांग_decoder__reset(काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	ocsd_datapath_resp_t dp_ret;

	decoder->prev_वापस = OCSD_RESP_CONT;

	dp_ret = ocsd_dt_process_data(decoder->dcd_tree, OCSD_OP_RESET,
				      0, 0, शून्य, शून्य);
	अगर (OCSD_DATA_RESP_IS_FATAL(dp_ret))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक cs_eपंचांग_decoder__get_packet(काष्ठा cs_eपंचांग_packet_queue *packet_queue,
			       काष्ठा cs_eपंचांग_packet *packet)
अणु
	अगर (!packet_queue || !packet)
		वापस -EINVAL;

	/* Nothing to करो, might as well just वापस */
	अगर (packet_queue->packet_count == 0)
		वापस 0;
	/*
	 * The queueing process in function cs_eपंचांग_decoder__buffer_packet()
	 * increments the tail *beक्रमe* using it.  This is somewhat counter
	 * पूर्णांकuitive but it has the advantage of centralizing tail management
	 * at a single location.  Because of that we need to follow the same
	 * heuristic with the head, i.e we increment it beक्रमe using its
	 * value.  Otherwise the first element of the packet queue is not
	 * used.
	 */
	packet_queue->head = (packet_queue->head + 1) &
			     (CS_ETM_PACKET_MAX_BUFFER - 1);

	*packet = packet_queue->packet_buffer[packet_queue->head];

	packet_queue->packet_count--;

	वापस 1;
पूर्ण

अटल पूर्णांक cs_eपंचांग_decoder__gen_eपंचांगv3_config(काष्ठा cs_eपंचांग_trace_params *params,
					    ocsd_eपंचांगv3_cfg *config)
अणु
	config->reg_idr = params->eपंचांगv3.reg_idr;
	config->reg_ctrl = params->eपंचांगv3.reg_ctrl;
	config->reg_ccer = params->eपंचांगv3.reg_ccer;
	config->reg_trc_id = params->eपंचांगv3.reg_trc_id;
	config->arch_ver = ARCH_V7;
	config->core_prof = profile_CortexA;

	वापस 0;
पूर्ण

अटल व्योम cs_eपंचांग_decoder__gen_eपंचांगv4_config(काष्ठा cs_eपंचांग_trace_params *params,
					     ocsd_eपंचांगv4_cfg *config)
अणु
	config->reg_configr = params->eपंचांगv4.reg_configr;
	config->reg_traceidr = params->eपंचांगv4.reg_traceidr;
	config->reg_idr0 = params->eपंचांगv4.reg_idr0;
	config->reg_idr1 = params->eपंचांगv4.reg_idr1;
	config->reg_idr2 = params->eपंचांगv4.reg_idr2;
	config->reg_idr8 = params->eपंचांगv4.reg_idr8;
	config->reg_idr9 = 0;
	config->reg_idr10 = 0;
	config->reg_idr11 = 0;
	config->reg_idr12 = 0;
	config->reg_idr13 = 0;
	config->arch_ver = ARCH_V8;
	config->core_prof = profile_CortexA;
पूर्ण

अटल व्योम cs_eपंचांग_decoder__prपूर्णांक_str_cb(स्थिर व्योम *p_context,
					 स्थिर अक्षर *msg,
					 स्थिर पूर्णांक str_len)
अणु
	अगर (p_context && str_len)
		((काष्ठा cs_eपंचांग_decoder *)p_context)->packet_prपूर्णांकer(msg);
पूर्ण

अटल पूर्णांक
cs_eपंचांग_decoder__init_def_logger_prपूर्णांकing(काष्ठा cs_eपंचांग_decoder_params *d_params,
					 काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	पूर्णांक ret = 0;

	अगर (d_params->packet_prपूर्णांकer == शून्य)
		वापस -1;

	decoder->packet_prपूर्णांकer = d_params->packet_prपूर्णांकer;

	/*
	 * Set up a library शेष logger to process any prपूर्णांकers
	 * (packet/raw frame) we add later.
	 */
	ret = ocsd_def_errlog_init(OCSD_ERR_SEV_ERROR, 1);
	अगर (ret != 0)
		वापस -1;

	/* no मानक_निकास / err / file output */
	ret = ocsd_def_errlog_config_output(C_API_MSGLOGOUT_FLG_NONE, शून्य);
	अगर (ret != 0)
		वापस -1;

	/*
	 * Set the string CB क्रम the शेष logger, passes strings to
	 * perf prपूर्णांक logger.
	 */
	ret = ocsd_def_errlog_set_strprपूर्णांक_cb(decoder->dcd_tree,
					      (व्योम *)decoder,
					      cs_eपंचांग_decoder__prपूर्णांक_str_cb);
	अगर (ret != 0)
		ret = -1;

	वापस 0;
पूर्ण

#अगर_घोषित CS_LOG_RAW_FRAMES
अटल व्योम
cs_eपंचांग_decoder__init_raw_frame_logging(काष्ठा cs_eपंचांग_decoder_params *d_params,
				       काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	/* Only log these during a --dump operation */
	अगर (d_params->operation == CS_ETM_OPERATION_PRINT) अणु
		/* set up a library शेष logger to process the
		 *  raw frame prपूर्णांकer we add later
		 */
		ocsd_def_errlog_init(OCSD_ERR_SEV_ERROR, 1);

		/* no मानक_निकास / err / file output */
		ocsd_def_errlog_config_output(C_API_MSGLOGOUT_FLG_NONE, शून्य);

		/* set the string CB क्रम the शेष logger,
		 * passes strings to perf prपूर्णांक logger.
		 */
		ocsd_def_errlog_set_strprपूर्णांक_cb(decoder->dcd_tree,
						(व्योम *)decoder,
						cs_eपंचांग_decoder__prपूर्णांक_str_cb);

		/* use the built in library prपूर्णांकer क्रम the raw frames */
		ocsd_dt_set_raw_frame_prपूर्णांकer(decoder->dcd_tree,
					      CS_RAW_DEBUG_FLAGS);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम
cs_eपंचांग_decoder__init_raw_frame_logging(
		काष्ठा cs_eपंचांग_decoder_params *d_params __maybe_unused,
		काष्ठा cs_eपंचांग_decoder *decoder __maybe_unused)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cs_eपंचांग_decoder__create_packet_prपूर्णांकer(काष्ठा cs_eपंचांग_decoder *decoder,
						 स्थिर अक्षर *decoder_name,
						 व्योम *trace_config)
अणु
	u8 csid;

	अगर (ocsd_dt_create_decoder(decoder->dcd_tree, decoder_name,
				   OCSD_CREATE_FLG_PACKET_PROC,
				   trace_config, &csid))
		वापस -1;

	अगर (ocsd_dt_set_pkt_protocol_prपूर्णांकer(decoder->dcd_tree, csid, 0))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
cs_eपंचांग_decoder__create_eपंचांग_packet_prपूर्णांकer(काष्ठा cs_eपंचांग_trace_params *t_params,
					  काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	स्थिर अक्षर *decoder_name;
	ocsd_eपंचांगv3_cfg config_eपंचांगv3;
	ocsd_eपंचांगv4_cfg trace_config_eपंचांगv4;
	व्योम *trace_config;

	चयन (t_params->protocol) अणु
	हाल CS_ETM_PROTO_ETMV3:
	हाल CS_ETM_PROTO_PTM:
		cs_eपंचांग_decoder__gen_eपंचांगv3_config(t_params, &config_eपंचांगv3);
		decoder_name = (t_params->protocol == CS_ETM_PROTO_ETMV3) ?
							OCSD_BUILTIN_DCD_ETMV3 :
							OCSD_BUILTIN_DCD_PTM;
		trace_config = &config_eपंचांगv3;
		अवरोध;
	हाल CS_ETM_PROTO_ETMV4i:
		cs_eपंचांग_decoder__gen_eपंचांगv4_config(t_params, &trace_config_eपंचांगv4);
		decoder_name = OCSD_BUILTIN_DCD_ETMV4I;
		trace_config = &trace_config_eपंचांगv4;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस cs_eपंचांग_decoder__create_packet_prपूर्णांकer(decoder,
						     decoder_name,
						     trace_config);
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__करो_soft_बारtamp(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				  काष्ठा cs_eपंचांग_packet_queue *packet_queue,
				  स्थिर uपूर्णांक8_t trace_chan_id)
अणु
	/* No बारtamp packet has been received, nothing to करो */
	अगर (!packet_queue->बारtamp)
		वापस OCSD_RESP_CONT;

	packet_queue->बारtamp = packet_queue->next_बारtamp;

	/* Estimate the बारtamp क्रम the next range packet */
	packet_queue->next_बारtamp += packet_queue->instr_count;
	packet_queue->instr_count = 0;

	/* Tell the front end which traceid_queue needs attention */
	cs_eपंचांग__eपंचांगq_set_traceid_queue_बारtamp(eपंचांगq, trace_chan_id);

	वापस OCSD_RESP_WAIT;
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__करो_hard_बारtamp(काष्ठा cs_eपंचांग_queue *eपंचांगq,
				  स्थिर ocsd_generic_trace_elem *elem,
				  स्थिर uपूर्णांक8_t trace_chan_id)
अणु
	काष्ठा cs_eपंचांग_packet_queue *packet_queue;

	/* First get the packet queue क्रम this traceID */
	packet_queue = cs_eपंचांग__eपंचांगq_get_packet_queue(eपंचांगq, trace_chan_id);
	अगर (!packet_queue)
		वापस OCSD_RESP_FATAL_SYS_ERR;

	/*
	 * We've seen a बारtamp packet beक्रमe - simply record the new value.
	 * Function करो_soft_बारtamp() will report the value to the front end,
	 * hence asking the decoder to keep decoding rather than stopping.
	 */
	अगर (packet_queue->बारtamp) अणु
		packet_queue->next_बारtamp = elem->बारtamp;
		वापस OCSD_RESP_CONT;
	पूर्ण

	/*
	 * This is the first बारtamp we've seen since the beginning of traces
	 * or a discontinuity.  Since बारtamps packets are generated *after*
	 * range packets have been generated, we need to estimate the समय at
	 * which inकाष्ठाions started by subtracting the number of inकाष्ठाions
	 * executed to the बारtamp.
	 */
	packet_queue->बारtamp = elem->बारtamp - packet_queue->instr_count;
	packet_queue->next_बारtamp = elem->बारtamp;
	packet_queue->instr_count = 0;

	/* Tell the front end which traceid_queue needs attention */
	cs_eपंचांग__eपंचांगq_set_traceid_queue_बारtamp(eपंचांगq, trace_chan_id);

	/* Halt processing until we are being told to proceed */
	वापस OCSD_RESP_WAIT;
पूर्ण

अटल व्योम
cs_eपंचांग_decoder__reset_बारtamp(काष्ठा cs_eपंचांग_packet_queue *packet_queue)
अणु
	packet_queue->बारtamp = 0;
	packet_queue->next_बारtamp = 0;
	packet_queue->instr_count = 0;
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__buffer_packet(काष्ठा cs_eपंचांग_packet_queue *packet_queue,
			      स्थिर u8 trace_chan_id,
			      क्रमागत cs_eपंचांग_sample_type sample_type)
अणु
	u32 et = 0;
	पूर्णांक cpu;

	अगर (packet_queue->packet_count >= CS_ETM_PACKET_MAX_BUFFER - 1)
		वापस OCSD_RESP_FATAL_SYS_ERR;

	अगर (cs_eपंचांग__get_cpu(trace_chan_id, &cpu) < 0)
		वापस OCSD_RESP_FATAL_SYS_ERR;

	et = packet_queue->tail;
	et = (et + 1) & (CS_ETM_PACKET_MAX_BUFFER - 1);
	packet_queue->tail = et;
	packet_queue->packet_count++;

	packet_queue->packet_buffer[et].sample_type = sample_type;
	packet_queue->packet_buffer[et].isa = CS_ETM_ISA_UNKNOWN;
	packet_queue->packet_buffer[et].cpu = cpu;
	packet_queue->packet_buffer[et].start_addr = CS_ETM_INVAL_ADDR;
	packet_queue->packet_buffer[et].end_addr = CS_ETM_INVAL_ADDR;
	packet_queue->packet_buffer[et].instr_count = 0;
	packet_queue->packet_buffer[et].last_instr_taken_branch = false;
	packet_queue->packet_buffer[et].last_instr_size = 0;
	packet_queue->packet_buffer[et].last_instr_type = 0;
	packet_queue->packet_buffer[et].last_instr_subtype = 0;
	packet_queue->packet_buffer[et].last_instr_cond = 0;
	packet_queue->packet_buffer[et].flags = 0;
	packet_queue->packet_buffer[et].exception_number = UINT32_MAX;
	packet_queue->packet_buffer[et].trace_chan_id = trace_chan_id;

	अगर (packet_queue->packet_count == CS_ETM_PACKET_MAX_BUFFER - 1)
		वापस OCSD_RESP_WAIT;

	वापस OCSD_RESP_CONT;
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__buffer_range(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			     काष्ठा cs_eपंचांग_packet_queue *packet_queue,
			     स्थिर ocsd_generic_trace_elem *elem,
			     स्थिर uपूर्णांक8_t trace_chan_id)
अणु
	पूर्णांक ret = 0;
	काष्ठा cs_eपंचांग_packet *packet;

	ret = cs_eपंचांग_decoder__buffer_packet(packet_queue, trace_chan_id,
					    CS_ETM_RANGE);
	अगर (ret != OCSD_RESP_CONT && ret != OCSD_RESP_WAIT)
		वापस ret;

	packet = &packet_queue->packet_buffer[packet_queue->tail];

	चयन (elem->isa) अणु
	हाल ocsd_isa_aarch64:
		packet->isa = CS_ETM_ISA_A64;
		अवरोध;
	हाल ocsd_isa_arm:
		packet->isa = CS_ETM_ISA_A32;
		अवरोध;
	हाल ocsd_isa_thumb2:
		packet->isa = CS_ETM_ISA_T32;
		अवरोध;
	हाल ocsd_isa_tee:
	हाल ocsd_isa_jazelle:
	हाल ocsd_isa_custom:
	हाल ocsd_isa_unknown:
	शेष:
		packet->isa = CS_ETM_ISA_UNKNOWN;
	पूर्ण

	packet->start_addr = elem->st_addr;
	packet->end_addr = elem->en_addr;
	packet->instr_count = elem->num_instr_range;
	packet->last_instr_type = elem->last_i_type;
	packet->last_instr_subtype = elem->last_i_subtype;
	packet->last_instr_cond = elem->last_instr_cond;

	अगर (elem->last_i_type == OCSD_INSTR_BR || elem->last_i_type == OCSD_INSTR_BR_INसूचीECT)
		packet->last_instr_taken_branch = elem->last_instr_exec;
	अन्यथा
		packet->last_instr_taken_branch = false;

	packet->last_instr_size = elem->last_instr_sz;

	/* per-thपढ़ो scenario, no need to generate a बारtamp */
	अगर (cs_eपंचांग__eपंचांगq_is_समयless(eपंचांगq))
		जाओ out;

	/*
	 * The packet queue is full and we haven't seen a बारtamp (had we
	 * seen one the packet queue wouldn't be full).  Let the front end
	 * deal with it.
	 */
	अगर (ret == OCSD_RESP_WAIT)
		जाओ out;

	packet_queue->instr_count += elem->num_instr_range;
	/* Tell the front end we have a new बारtamp to process */
	ret = cs_eपंचांग_decoder__करो_soft_बारtamp(eपंचांगq, packet_queue,
						trace_chan_id);
out:
	वापस ret;
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__buffer_discontinuity(काष्ठा cs_eपंचांग_packet_queue *queue,
				     स्थिर uपूर्णांक8_t trace_chan_id)
अणु
	/*
	 * Something happened and who knows when we'll get new traces so
	 * reset समय statistics.
	 */
	cs_eपंचांग_decoder__reset_बारtamp(queue);
	वापस cs_eपंचांग_decoder__buffer_packet(queue, trace_chan_id,
					     CS_ETM_DISCONTINUITY);
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__buffer_exception(काष्ठा cs_eपंचांग_packet_queue *queue,
				 स्थिर ocsd_generic_trace_elem *elem,
				 स्थिर uपूर्णांक8_t trace_chan_id)
अणु	पूर्णांक ret = 0;
	काष्ठा cs_eपंचांग_packet *packet;

	ret = cs_eपंचांग_decoder__buffer_packet(queue, trace_chan_id,
					    CS_ETM_EXCEPTION);
	अगर (ret != OCSD_RESP_CONT && ret != OCSD_RESP_WAIT)
		वापस ret;

	packet = &queue->packet_buffer[queue->tail];
	packet->exception_number = elem->exception_number;

	वापस ret;
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__buffer_exception_ret(काष्ठा cs_eपंचांग_packet_queue *queue,
				     स्थिर uपूर्णांक8_t trace_chan_id)
अणु
	वापस cs_eपंचांग_decoder__buffer_packet(queue, trace_chan_id,
					     CS_ETM_EXCEPTION_RET);
पूर्ण

अटल ocsd_datapath_resp_t
cs_eपंचांग_decoder__set_tid(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			काष्ठा cs_eपंचांग_packet_queue *packet_queue,
			स्थिर ocsd_generic_trace_elem *elem,
			स्थिर uपूर्णांक8_t trace_chan_id)
अणु
	pid_t tid = -1;
	अटल u64 pid_fmt;
	पूर्णांक ret;

	/*
	 * As all the ETMs run at the same exception level, the प्रणाली should
	 * have the same PID क्रमmat crossing CPUs.  So cache the PID क्रमmat
	 * and reuse it क्रम sequential decoding.
	 */
	अगर (!pid_fmt) अणु
		ret = cs_eपंचांग__get_pid_fmt(trace_chan_id, &pid_fmt);
		अगर (ret)
			वापस OCSD_RESP_FATAL_SYS_ERR;
	पूर्ण

	/*
	 * Process the PE_CONTEXT packets अगर we have a valid contextID or VMID.
	 * If the kernel is running at EL2, the PID is traced in CONTEXTIDR_EL2
	 * as VMID, Bit ETM_OPT_CTXTID2 is set in this हाल.
	 */
	चयन (pid_fmt) अणु
	हाल BIT(ETM_OPT_CTXTID):
		अगर (elem->context.ctxt_id_valid)
			tid = elem->context.context_id;
		अवरोध;
	हाल BIT(ETM_OPT_CTXTID2):
		अगर (elem->context.vmid_valid)
			tid = elem->context.vmid;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (tid == -1)
		वापस OCSD_RESP_CONT;

	अगर (cs_eपंचांग__eपंचांगq_set_tid(eपंचांगq, tid, trace_chan_id))
		वापस OCSD_RESP_FATAL_SYS_ERR;

	/*
	 * A बारtamp is generated after a PE_CONTEXT element so make sure
	 * to rely on that coming one.
	 */
	cs_eपंचांग_decoder__reset_बारtamp(packet_queue);

	वापस OCSD_RESP_CONT;
पूर्ण

अटल ocsd_datapath_resp_t cs_eपंचांग_decoder__gen_trace_elem_prपूर्णांकer(
				स्थिर व्योम *context,
				स्थिर ocsd_trc_index_t indx __maybe_unused,
				स्थिर u8 trace_chan_id __maybe_unused,
				स्थिर ocsd_generic_trace_elem *elem)
अणु
	ocsd_datapath_resp_t resp = OCSD_RESP_CONT;
	काष्ठा cs_eपंचांग_decoder *decoder = (काष्ठा cs_eपंचांग_decoder *) context;
	काष्ठा cs_eपंचांग_queue *eपंचांगq = decoder->data;
	काष्ठा cs_eपंचांग_packet_queue *packet_queue;

	/* First get the packet queue क्रम this traceID */
	packet_queue = cs_eपंचांग__eपंचांगq_get_packet_queue(eपंचांगq, trace_chan_id);
	अगर (!packet_queue)
		वापस OCSD_RESP_FATAL_SYS_ERR;

	चयन (elem->elem_type) अणु
	हाल OCSD_GEN_TRC_ELEM_UNKNOWN:
		अवरोध;
	हाल OCSD_GEN_TRC_ELEM_EO_TRACE:
	हाल OCSD_GEN_TRC_ELEM_NO_SYNC:
	हाल OCSD_GEN_TRC_ELEM_TRACE_ON:
		resp = cs_eपंचांग_decoder__buffer_discontinuity(packet_queue,
							    trace_chan_id);
		अवरोध;
	हाल OCSD_GEN_TRC_ELEM_INSTR_RANGE:
		resp = cs_eपंचांग_decoder__buffer_range(eपंचांगq, packet_queue, elem,
						    trace_chan_id);
		अवरोध;
	हाल OCSD_GEN_TRC_ELEM_EXCEPTION:
		resp = cs_eपंचांग_decoder__buffer_exception(packet_queue, elem,
							trace_chan_id);
		अवरोध;
	हाल OCSD_GEN_TRC_ELEM_EXCEPTION_RET:
		resp = cs_eपंचांग_decoder__buffer_exception_ret(packet_queue,
							    trace_chan_id);
		अवरोध;
	हाल OCSD_GEN_TRC_ELEM_TIMESTAMP:
		resp = cs_eपंचांग_decoder__करो_hard_बारtamp(eपंचांगq, elem,
							 trace_chan_id);
		अवरोध;
	हाल OCSD_GEN_TRC_ELEM_PE_CONTEXT:
		resp = cs_eपंचांग_decoder__set_tid(eपंचांगq, packet_queue,
					       elem, trace_chan_id);
		अवरोध;
	/* Unused packet types */
	हाल OCSD_GEN_TRC_ELEM_I_RANGE_NOPATH:
	हाल OCSD_GEN_TRC_ELEM_ADDR_NACC:
	हाल OCSD_GEN_TRC_ELEM_CYCLE_COUNT:
	हाल OCSD_GEN_TRC_ELEM_ADDR_UNKNOWN:
	हाल OCSD_GEN_TRC_ELEM_EVENT:
	हाल OCSD_GEN_TRC_ELEM_SWTRACE:
	हाल OCSD_GEN_TRC_ELEM_CUSTOM:
	हाल OCSD_GEN_TRC_ELEM_SYNC_MARKER:
	हाल OCSD_GEN_TRC_ELEM_MEMTRANS:
	शेष:
		अवरोध;
	पूर्ण

	वापस resp;
पूर्ण

अटल पूर्णांक cs_eपंचांग_decoder__create_eपंचांग_packet_decoder(
					काष्ठा cs_eपंचांग_trace_params *t_params,
					काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	स्थिर अक्षर *decoder_name;
	ocsd_eपंचांगv3_cfg config_eपंचांगv3;
	ocsd_eपंचांगv4_cfg trace_config_eपंचांगv4;
	व्योम *trace_config;
	u8 csid;

	चयन (t_params->protocol) अणु
	हाल CS_ETM_PROTO_ETMV3:
	हाल CS_ETM_PROTO_PTM:
		cs_eपंचांग_decoder__gen_eपंचांगv3_config(t_params, &config_eपंचांगv3);
		decoder_name = (t_params->protocol == CS_ETM_PROTO_ETMV3) ?
							OCSD_BUILTIN_DCD_ETMV3 :
							OCSD_BUILTIN_DCD_PTM;
		trace_config = &config_eपंचांगv3;
		अवरोध;
	हाल CS_ETM_PROTO_ETMV4i:
		cs_eपंचांग_decoder__gen_eपंचांगv4_config(t_params, &trace_config_eपंचांगv4);
		decoder_name = OCSD_BUILTIN_DCD_ETMV4I;
		trace_config = &trace_config_eपंचांगv4;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (ocsd_dt_create_decoder(decoder->dcd_tree,
				     decoder_name,
				     OCSD_CREATE_FLG_FULL_DECODER,
				     trace_config, &csid))
		वापस -1;

	अगर (ocsd_dt_set_gen_elem_outfn(decoder->dcd_tree,
				       cs_eपंचांग_decoder__gen_trace_elem_prपूर्णांकer,
				       decoder))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
cs_eपंचांग_decoder__create_eपंचांग_decoder(काष्ठा cs_eपंचांग_decoder_params *d_params,
				   काष्ठा cs_eपंचांग_trace_params *t_params,
				   काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	अगर (d_params->operation == CS_ETM_OPERATION_PRINT)
		वापस cs_eपंचांग_decoder__create_eपंचांग_packet_prपूर्णांकer(t_params,
								 decoder);
	अन्यथा अगर (d_params->operation == CS_ETM_OPERATION_DECODE)
		वापस cs_eपंचांग_decoder__create_eपंचांग_packet_decoder(t_params,
								 decoder);

	वापस -1;
पूर्ण

काष्ठा cs_eपंचांग_decoder *
cs_eपंचांग_decoder__new(पूर्णांक num_cpu, काष्ठा cs_eपंचांग_decoder_params *d_params,
		    काष्ठा cs_eपंचांग_trace_params t_params[])
अणु
	काष्ठा cs_eपंचांग_decoder *decoder;
	ocsd_dcd_tree_src_t क्रमmat;
	u32 flags;
	पूर्णांक i, ret;

	अगर ((!t_params) || (!d_params))
		वापस शून्य;

	decoder = zalloc(माप(*decoder));

	अगर (!decoder)
		वापस शून्य;

	decoder->data = d_params->data;
	decoder->prev_वापस = OCSD_RESP_CONT;
	क्रमmat = (d_params->क्रमmatted ? OCSD_TRC_SRC_FRAME_FORMATTED :
					 OCSD_TRC_SRC_SINGLE);
	flags = 0;
	flags |= (d_params->fsyncs ? OCSD_DFRMTR_HAS_FSYNCS : 0);
	flags |= (d_params->hsyncs ? OCSD_DFRMTR_HAS_HSYNCS : 0);
	flags |= (d_params->frame_aligned ? OCSD_DFRMTR_FRAME_MEM_ALIGN : 0);

	/*
	 * Drivers may add barrier frames when used with perf, set up to
	 * handle this. Barriers स्थिर of FSYNC packet repeated 4 बार.
	 */
	flags |= OCSD_DFRMTR_RESET_ON_4X_FSYNC;

	/* Create decode tree क्रम the data source */
	decoder->dcd_tree = ocsd_create_dcd_tree(क्रमmat, flags);

	अगर (decoder->dcd_tree == 0)
		जाओ err_मुक्त_decoder;

	/* init library prपूर्णांक logging support */
	ret = cs_eपंचांग_decoder__init_def_logger_prपूर्णांकing(d_params, decoder);
	अगर (ret != 0)
		जाओ err_मुक्त_decoder;

	/* init raw frame logging अगर required */
	cs_eपंचांग_decoder__init_raw_frame_logging(d_params, decoder);

	क्रम (i = 0; i < num_cpu; i++) अणु
		ret = cs_eपंचांग_decoder__create_eपंचांग_decoder(d_params,
							 &t_params[i],
							 decoder);
		अगर (ret != 0)
			जाओ err_मुक्त_decoder;
	पूर्ण

	वापस decoder;

err_मुक्त_decoder:
	cs_eपंचांग_decoder__मुक्त(decoder);
	वापस शून्य;
पूर्ण

पूर्णांक cs_eपंचांग_decoder__process_data_block(काष्ठा cs_eपंचांग_decoder *decoder,
				       u64 indx, स्थिर u8 *buf,
				       माप_प्रकार len, माप_प्रकार *consumed)
अणु
	पूर्णांक ret = 0;
	ocsd_datapath_resp_t cur = OCSD_RESP_CONT;
	ocsd_datapath_resp_t prev_वापस = decoder->prev_वापस;
	माप_प्रकार processed = 0;
	u32 count;

	जबतक (processed < len) अणु
		अगर (OCSD_DATA_RESP_IS_WAIT(prev_वापस)) अणु
			cur = ocsd_dt_process_data(decoder->dcd_tree,
						   OCSD_OP_FLUSH,
						   0,
						   0,
						   शून्य,
						   शून्य);
		पूर्ण अन्यथा अगर (OCSD_DATA_RESP_IS_CONT(prev_वापस)) अणु
			cur = ocsd_dt_process_data(decoder->dcd_tree,
						   OCSD_OP_DATA,
						   indx + processed,
						   len - processed,
						   &buf[processed],
						   &count);
			processed += count;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * Return to the input code अगर the packet buffer is full.
		 * Flushing will get करोne once the packet buffer has been
		 * processed.
		 */
		अगर (OCSD_DATA_RESP_IS_WAIT(cur))
			अवरोध;

		prev_वापस = cur;
	पूर्ण

	decoder->prev_वापस = cur;
	*consumed = processed;

	वापस ret;
पूर्ण

व्योम cs_eपंचांग_decoder__मुक्त(काष्ठा cs_eपंचांग_decoder *decoder)
अणु
	अगर (!decoder)
		वापस;

	ocsd_destroy_dcd_tree(decoder->dcd_tree);
	decoder->dcd_tree = शून्य;
	मुक्त(decoder);
पूर्ण
