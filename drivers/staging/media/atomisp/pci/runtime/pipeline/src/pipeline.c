<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "hmm.h"

#समावेश "ia_css_debug.h"
#समावेश "sw_event_global.h"		/* encode_sw_event */
#समावेश "sp.h"			/* cnd_sp_irq_enable() */
#समावेश "assert_support.h"
#समावेश "sh_css_sp.h"
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_isp_param.h"
#समावेश "ia_css_bufq.h"

#घोषणा PIPELINE_NUM_UNMAPPED                   (~0U)
#घोषणा PIPELINE_SP_THREAD_EMPTY_TOKEN          (0x0)
#घोषणा PIPELINE_SP_THREAD_RESERVED_TOKEN       (0x1)

/*******************************************************
*** Static variables
********************************************************/
अटल अचिन्हित पूर्णांक pipeline_num_to_sp_thपढ़ो_map[IA_CSS_PIPELINE_NUM_MAX];
अटल अचिन्हित पूर्णांक pipeline_sp_thपढ़ो_list[SH_CSS_MAX_SP_THREADS];

/*******************************************************
*** Static functions
********************************************************/
अटल व्योम pipeline_init_sp_thपढ़ो_map(व्योम);
अटल व्योम pipeline_map_num_to_sp_thपढ़ो(अचिन्हित पूर्णांक pipe_num);
अटल व्योम pipeline_unmap_num_to_sp_thपढ़ो(अचिन्हित पूर्णांक pipe_num);
अटल व्योम pipeline_init_शेषs(
    काष्ठा ia_css_pipeline *pipeline,
    क्रमागत ia_css_pipe_id pipe_id,
    अचिन्हित पूर्णांक pipe_num,
    अचिन्हित पूर्णांक dvs_frame_delay);

अटल व्योम pipeline_stage_destroy(काष्ठा ia_css_pipeline_stage *stage);
अटल पूर्णांक pipeline_stage_create(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_pipeline_stage **new_stage);
अटल व्योम ia_css_pipeline_set_zoom_stage(काष्ठा ia_css_pipeline *pipeline);
अटल व्योम ia_css_pipeline_configure_inout_port(काष्ठा ia_css_pipeline *me,
	bool continuous);

/*******************************************************
*** Public functions
********************************************************/
व्योम ia_css_pipeline_init(व्योम)
अणु
	pipeline_init_sp_thपढ़ो_map();
पूर्ण

पूर्णांक ia_css_pipeline_create(
    काष्ठा ia_css_pipeline *pipeline,
    क्रमागत ia_css_pipe_id pipe_id,
    अचिन्हित पूर्णांक pipe_num,
    अचिन्हित पूर्णांक dvs_frame_delay)
अणु
	निश्चित(pipeline);
	IA_CSS_ENTER_PRIVATE("pipeline = %p, pipe_id = %d, pipe_num = %d, dvs_frame_delay = %d",
			     pipeline, pipe_id, pipe_num, dvs_frame_delay);
	अगर (!pipeline) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	pipeline_init_शेषs(pipeline, pipe_id, pipe_num, dvs_frame_delay);

	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

व्योम ia_css_pipeline_map(अचिन्हित पूर्णांक pipe_num, bool map)
अणु
	निश्चित(pipe_num < IA_CSS_PIPELINE_NUM_MAX);
	IA_CSS_ENTER_PRIVATE("pipe_num = %d, map = %d", pipe_num, map);

	अगर (pipe_num >= IA_CSS_PIPELINE_NUM_MAX) अणु
		IA_CSS_ERROR("Invalid pipe number");
		IA_CSS_LEAVE_PRIVATE("void");
		वापस;
	पूर्ण
	अगर (map)
		pipeline_map_num_to_sp_thपढ़ो(pipe_num);
	अन्यथा
		pipeline_unmap_num_to_sp_thपढ़ो(pipe_num);
	IA_CSS_LEAVE_PRIVATE("void");
पूर्ण

/* @brief destroy a pipeline
 *
 * @param[in] pipeline
 * @वापस    None
 *
 */
व्योम ia_css_pipeline_destroy(काष्ठा ia_css_pipeline *pipeline)
अणु
	निश्चित(pipeline);
	IA_CSS_ENTER_PRIVATE("pipeline = %p", pipeline);

	अगर (!pipeline) अणु
		IA_CSS_ERROR("NULL input parameter");
		IA_CSS_LEAVE_PRIVATE("void");
		वापस;
	पूर्ण

	IA_CSS_LOG("pipe_num = %d", pipeline->pipe_num);

	/* Free the pipeline number */
	ia_css_pipeline_clean(pipeline);

	IA_CSS_LEAVE_PRIVATE("void");
पूर्ण

/* Run a pipeline and रुको till it completes. */
व्योम ia_css_pipeline_start(क्रमागत ia_css_pipe_id pipe_id,
			   काष्ठा ia_css_pipeline *pipeline)
अणु
	u8 pipe_num = 0;
	अचिन्हित पूर्णांक thपढ़ो_id;

	निश्चित(pipeline);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_start() enter: pipe_id=%d, pipeline=%p\n",
			    pipe_id, pipeline);
	pipeline->pipe_id = pipe_id;
	sh_css_sp_init_pipeline(pipeline, pipe_id, pipe_num,
				false, false, false, true, SH_CSS_BDS_FACTOR_1_00,
				SH_CSS_PIPE_CONFIG_OVRD_NO_OVRD,
				IA_CSS_INPUT_MODE_MEMORY, शून्य, शून्य,
				(क्रमागत mipi_port_id)0,
				शून्य, शून्य);

	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	अगर (!sh_css_sp_is_running()) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_pipeline_start() error,leaving\n");
		/* queues are invalid*/
		वापस;
	पूर्ण
	ia_css_bufq_enqueue_psys_event(IA_CSS_PSYS_SW_EVENT_START_STREAM,
				       (uपूर्णांक8_t)thपढ़ो_id,
				       0,
				       0);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_start() leave: return_void\n");
पूर्ण

/*
 * @brief Query the SP thपढ़ो ID.
 * Refer to "sh_css_internal.h" क्रम details.
 */
bool ia_css_pipeline_get_sp_thपढ़ो_id(अचिन्हित पूर्णांक key, अचिन्हित पूर्णांक *val)
अणु
	IA_CSS_ENTER("key=%d, val=%p", key, val);

	अगर ((!val) || (key >= IA_CSS_PIPELINE_NUM_MAX) || (key >= IA_CSS_PIPE_ID_NUM)) अणु
		IA_CSS_LEAVE("return value = false");
		वापस false;
	पूर्ण

	*val = pipeline_num_to_sp_thपढ़ो_map[key];

	अगर (*val == (अचिन्हित पूर्णांक)PIPELINE_NUM_UNMAPPED) अणु
		IA_CSS_LOG("unmapped pipeline number");
		IA_CSS_LEAVE("return value = false");
		वापस false;
	पूर्ण
	IA_CSS_LEAVE("return value = true");
	वापस true;
पूर्ण

व्योम ia_css_pipeline_dump_thपढ़ो_map_info(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "pipeline_num_to_sp_thread_map:\n");
	क्रम (i = 0; i < IA_CSS_PIPELINE_NUM_MAX; i++) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "pipe_num: %u, tid: 0x%x\n", i, pipeline_num_to_sp_thपढ़ो_map[i]);
	पूर्ण
पूर्ण

पूर्णांक ia_css_pipeline_request_stop(काष्ठा ia_css_pipeline *pipeline)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक thपढ़ो_id;

	निश्चित(pipeline);

	अगर (!pipeline)
		वापस -EINVAL;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_request_stop() enter: pipeline=%p\n",
			    pipeline);
	pipeline->stop_requested = true;

	/* Send stop event to the sp*/
	/* This needs improvement, stop on all the pipes available
	 * in the stream*/
	ia_css_pipeline_get_sp_thपढ़ो_id(pipeline->pipe_num, &thपढ़ो_id);
	अगर (!sh_css_sp_is_running()) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_pipeline_request_stop() leaving\n");
		/* queues are invalid */
		वापस -EBUSY;
	पूर्ण
	ia_css_bufq_enqueue_psys_event(IA_CSS_PSYS_SW_EVENT_STOP_STREAM,
				       (uपूर्णांक8_t)thपढ़ो_id,
				       0,
				       0);
	sh_css_sp_uninit_pipeline(pipeline->pipe_num);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_request_stop() leave: return_err=%d\n",
			    err);
	वापस err;
पूर्ण

व्योम ia_css_pipeline_clean(काष्ठा ia_css_pipeline *pipeline)
अणु
	काष्ठा ia_css_pipeline_stage *s;

	निश्चित(pipeline);
	IA_CSS_ENTER_PRIVATE("pipeline = %p", pipeline);

	अगर (!pipeline) अणु
		IA_CSS_ERROR("NULL input parameter");
		IA_CSS_LEAVE_PRIVATE("void");
		वापस;
	पूर्ण
	s = pipeline->stages;

	जबतक (s) अणु
		काष्ठा ia_css_pipeline_stage *next = s->next;

		pipeline_stage_destroy(s);
		s = next;
	पूर्ण
	pipeline_init_शेषs(pipeline, pipeline->pipe_id, pipeline->pipe_num,
			       pipeline->dvs_frame_delay);

	IA_CSS_LEAVE_PRIVATE("void");
पूर्ण

/* @brief Add a stage to pipeline.
 *
 * @param       pipeline      Poपूर्णांकer to the pipeline to be added to.
 * @param[in]   stage_desc    The description of the stage
 * @param[out]	stage         The successor of the stage.
 * @वापस      0 or error code upon error.
 *
 * Add a new stage to a non-शून्य pipeline.
 * The stage consists of an ISP binary or firmware and input and
 * output arguments.
*/
पूर्णांक ia_css_pipeline_create_and_add_stage(
    काष्ठा ia_css_pipeline *pipeline,
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_pipeline_stage **stage)
अणु
	काष्ठा ia_css_pipeline_stage *last, *new_stage = शून्य;
	पूर्णांक err;

	/* other arguments can be शून्य */
	निश्चित(pipeline);
	निश्चित(stage_desc);
	last = pipeline->stages;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_create_and_add_stage() enter:\n");
	अगर (!stage_desc->binary && !stage_desc->firmware
	    && (stage_desc->sp_func == IA_CSS_PIPELINE_NO_FUNC)) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_pipeline_create_and_add_stage() done: Invalid args\n");

		वापस -EINVAL;
	पूर्ण

	/* Find the last stage */
	जबतक (last && last->next)
		last = last->next;

	/* अगर in_frame is not set, we use the out_frame from the previous
	 * stage, अगर no previous stage, it's an error.
	 */
	अगर ((stage_desc->sp_func == IA_CSS_PIPELINE_NO_FUNC)
	    && (!stage_desc->in_frame)
	    && (!stage_desc->firmware)
	    && (!stage_desc->binary->online)) अणु
		/* Do this only क्रम ISP stages*/
		अगर (last && last->args.out_frame[0])
			stage_desc->in_frame = last->args.out_frame[0];

		अगर (!stage_desc->in_frame)
			वापस -EINVAL;
	पूर्ण

	/* Create the new stage */
	err = pipeline_stage_create(stage_desc, &new_stage);
	अगर (err) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_pipeline_create_and_add_stage() done: stage_create_failed\n");
		वापस err;
	पूर्ण

	अगर (last)
		last->next = new_stage;
	अन्यथा
		pipeline->stages = new_stage;

	/* Output the new stage */
	अगर (stage)
		*stage = new_stage;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_create_and_add_stage() done:\n");
	वापस 0;
पूर्ण

व्योम ia_css_pipeline_finalize_stages(काष्ठा ia_css_pipeline *pipeline,
				     bool continuous)
अणु
	अचिन्हित पूर्णांक i = 0;
	काष्ठा ia_css_pipeline_stage *stage;

	निश्चित(pipeline);
	क्रम (stage = pipeline->stages; stage; stage = stage->next) अणु
		stage->stage_num = i;
		i++;
	पूर्ण
	pipeline->num_stages = i;

	ia_css_pipeline_set_zoom_stage(pipeline);
	ia_css_pipeline_configure_inout_port(pipeline, continuous);
पूर्ण

पूर्णांक ia_css_pipeline_get_stage(काष्ठा ia_css_pipeline *pipeline,
	पूर्णांक mode,
	काष्ठा ia_css_pipeline_stage **stage)
अणु
	काष्ठा ia_css_pipeline_stage *s;

	निश्चित(pipeline);
	निश्चित(stage);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_get_stage() enter:\n");
	क्रम (s = pipeline->stages; s; s = s->next) अणु
		अगर (s->mode == mode) अणु
			*stage = s;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_pipeline_get_stage_from_fw(काष्ठा ia_css_pipeline
	*pipeline,
	u32 fw_handle,
	काष्ठा ia_css_pipeline_stage **stage)
अणु
	काष्ठा ia_css_pipeline_stage *s;

	निश्चित(pipeline);
	निश्चित(stage);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s()\n", __func__);
	क्रम (s = pipeline->stages; s; s = s->next) अणु
		अगर ((s->firmware) && (s->firmware->handle == fw_handle)) अणु
			*stage = s;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_pipeline_get_fw_from_stage(काष्ठा ia_css_pipeline
	*pipeline,
	u32 stage_num,
	uपूर्णांक32_t *fw_handle)
अणु
	काष्ठा ia_css_pipeline_stage *s;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s()\n", __func__);
	अगर ((!pipeline) || (!fw_handle))
		वापस -EINVAL;

	क्रम (s = pipeline->stages; s; s = s->next) अणु
		अगर ((s->stage_num == stage_num) && (s->firmware)) अणु
			*fw_handle = s->firmware->handle;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_pipeline_get_output_stage(
    काष्ठा ia_css_pipeline *pipeline,
    पूर्णांक mode,
    काष्ठा ia_css_pipeline_stage **stage)
अणु
	काष्ठा ia_css_pipeline_stage *s;

	निश्चित(pipeline);
	निश्चित(stage);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_get_output_stage() enter:\n");

	*stage = शून्य;
	/* First find acceleration firmware at end of pipe */
	क्रम (s = pipeline->stages; s; s = s->next) अणु
		अगर (s->firmware && s->mode == mode &&
		    s->firmware->info.isp.sp.enable.output)
			*stage = s;
	पूर्ण
	अगर (*stage)
		वापस 0;
	/* If no firmware, find binary in pipe */
	वापस ia_css_pipeline_get_stage(pipeline, mode, stage);
पूर्ण

bool ia_css_pipeline_has_stopped(काष्ठा ia_css_pipeline *pipeline)
अणु
	/* Android compilation files अगर made an local variable
	stack size on android is limited to 2k and this काष्ठाure
	is around 2.5K, in place of अटल दो_स्मृति can be करोne but
	अगर this call is made too often it will lead to fragment memory
	versus a fixed allocation */
	अटल काष्ठा sh_css_sp_group sp_group;
	अचिन्हित पूर्णांक thपढ़ो_id;
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_group;

	fw = &sh_css_sp_fw;
	HIVE_ADDR_sp_group = fw->info.sp.group;

	ia_css_pipeline_get_sp_thपढ़ो_id(pipeline->pipe_num, &thपढ़ो_id);
	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(sp_group),
		     &sp_group, माप(काष्ठा sh_css_sp_group));
	वापस sp_group.pipe[thपढ़ो_id].num_stages == 0;
पूर्ण

#अगर defined(ISP2401)
काष्ठा sh_css_sp_pipeline_io_status *ia_css_pipeline_get_pipe_io_status(व्योम)
अणु
	वापस(&sh_css_sp_group.pipe_io_status);
पूर्ण
#पूर्ण_अगर

bool ia_css_pipeline_is_mapped(अचिन्हित पूर्णांक key)
अणु
	bool ret = false;

	IA_CSS_ENTER_PRIVATE("key = %d", key);

	अगर ((key >= IA_CSS_PIPELINE_NUM_MAX) || (key >= IA_CSS_PIPE_ID_NUM)) अणु
		IA_CSS_ERROR("Invalid key!!");
		IA_CSS_LEAVE_PRIVATE("return = %d", false);
		वापस false;
	पूर्ण

	ret = (bool)(pipeline_num_to_sp_thपढ़ो_map[key] != (अचिन्हित पूर्णांक)
		     PIPELINE_NUM_UNMAPPED);

	IA_CSS_LEAVE_PRIVATE("return = %d", ret);
	वापस ret;
पूर्ण

/*******************************************************
*** Static functions
********************************************************/

/* Pipeline:
 * To organize the several dअगरferent binaries क्रम each type of mode,
 * we use a pipeline. A pipeline contains a number of stages, each with
 * their own binary and frame poपूर्णांकers.
 * When stages are added to a pipeline, output frames that are not passed
 * from outside are स्वतःmatically allocated.
 * When input frames are not passed from outside, each stage will use the
 * output frame of the previous stage as input (the full resolution output,
 * not the viewfinder output).
 * Pipelines must be cleaned and re-created when settings of the binaries
 * change.
 */
अटल व्योम pipeline_stage_destroy(काष्ठा ia_css_pipeline_stage *stage)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		अगर (stage->out_frame_allocated[i]) अणु
			ia_css_frame_मुक्त(stage->args.out_frame[i]);
			stage->args.out_frame[i] = शून्य;
		पूर्ण
	पूर्ण
	अगर (stage->vf_frame_allocated) अणु
		ia_css_frame_मुक्त(stage->args.out_vf_frame);
		stage->args.out_vf_frame = शून्य;
	पूर्ण
	kvमुक्त(stage);
पूर्ण

अटल व्योम pipeline_init_sp_thपढ़ो_map(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < SH_CSS_MAX_SP_THREADS; i++)
		pipeline_sp_thपढ़ो_list[i] = PIPELINE_SP_THREAD_EMPTY_TOKEN;

	क्रम (i = 0; i < IA_CSS_PIPELINE_NUM_MAX; i++)
		pipeline_num_to_sp_thपढ़ो_map[i] = PIPELINE_NUM_UNMAPPED;
पूर्ण

अटल व्योम pipeline_map_num_to_sp_thपढ़ो(अचिन्हित पूर्णांक pipe_num)
अणु
	अचिन्हित पूर्णांक i;
	bool found_sp_thपढ़ो = false;

	/* pipe is not mapped to any thपढ़ो */
	निश्चित(pipeline_num_to_sp_thपढ़ो_map[pipe_num]
	       == (अचिन्हित पूर्णांक)PIPELINE_NUM_UNMAPPED);

	क्रम (i = 0; i < SH_CSS_MAX_SP_THREADS; i++) अणु
		अगर (pipeline_sp_thपढ़ो_list[i] ==
		    PIPELINE_SP_THREAD_EMPTY_TOKEN) अणु
			pipeline_sp_thपढ़ो_list[i] =
			    PIPELINE_SP_THREAD_RESERVED_TOKEN;
			pipeline_num_to_sp_thपढ़ो_map[pipe_num] = i;
			found_sp_thपढ़ो = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Make sure a mapping is found */
	/* I could करो:
		निश्चित(i < SH_CSS_MAX_SP_THREADS);

		But the below is more descriptive.
	*/
	निश्चित(found_sp_thपढ़ो);
पूर्ण

अटल व्योम pipeline_unmap_num_to_sp_thपढ़ो(अचिन्हित पूर्णांक pipe_num)
अणु
	अचिन्हित पूर्णांक thपढ़ो_id;

	निश्चित(pipeline_num_to_sp_thपढ़ो_map[pipe_num]
	       != (अचिन्हित पूर्णांक)PIPELINE_NUM_UNMAPPED);

	thपढ़ो_id = pipeline_num_to_sp_thपढ़ो_map[pipe_num];
	pipeline_num_to_sp_thपढ़ो_map[pipe_num] = PIPELINE_NUM_UNMAPPED;
	pipeline_sp_thपढ़ो_list[thपढ़ो_id] = PIPELINE_SP_THREAD_EMPTY_TOKEN;
पूर्ण

अटल पूर्णांक pipeline_stage_create(
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_pipeline_stage **new_stage)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_pipeline_stage *stage = शून्य;
	काष्ठा ia_css_binary *binary;
	काष्ठा ia_css_frame *vf_frame;
	काष्ठा ia_css_frame *out_frame[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	स्थिर काष्ठा ia_css_fw_info *firmware;
	अचिन्हित पूर्णांक i;

	/* Verअगरy input parameters*/
	अगर (!(stage_desc->in_frame) && !(stage_desc->firmware)
	    && (stage_desc->binary) && !(stage_desc->binary->online)) अणु
		err = -EINVAL;
		जाओ ERR;
	पूर्ण

	binary = stage_desc->binary;
	firmware = stage_desc->firmware;
	vf_frame = stage_desc->vf_frame;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		out_frame[i] = stage_desc->out_frame[i];
	पूर्ण

	stage = kvzalloc(माप(*stage), GFP_KERNEL);
	अगर (!stage) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण

	अगर (firmware) अणु
		stage->binary = शून्य;
		stage->binary_info =
		    (काष्ठा ia_css_binary_info *)&firmware->info.isp;
	पूर्ण अन्यथा अणु
		stage->binary = binary;
		अगर (binary)
			stage->binary_info =
			    (काष्ठा ia_css_binary_info *)binary->info;
		अन्यथा
			stage->binary_info = शून्य;
	पूर्ण

	stage->firmware = firmware;
	stage->sp_func = stage_desc->sp_func;
	stage->max_input_width = stage_desc->max_input_width;
	stage->mode = stage_desc->mode;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		stage->out_frame_allocated[i] = false;
	stage->vf_frame_allocated = false;
	stage->next = शून्य;
	sh_css_binary_args_reset(&stage->args);

	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		अगर (!(out_frame[i]) && (binary)
		    && (binary->out_frame_info[i].res.width)) अणु
			err = ia_css_frame_allocate_from_info(&out_frame[i],
							      &binary->out_frame_info[i]);
			अगर (err)
				जाओ ERR;
			stage->out_frame_allocated[i] = true;
		पूर्ण
	पूर्ण
	/* VF frame is not needed in हाल of need_pp
	   However, the capture binary needs a vf frame to ग_लिखो to.
	 */
	अगर (!vf_frame) अणु
		अगर ((binary && binary->vf_frame_info.res.width) ||
		    (firmware && firmware->info.isp.sp.enable.vf_veceven)
		   ) अणु
			err = ia_css_frame_allocate_from_info(&vf_frame,
							      &binary->vf_frame_info);
			अगर (err)
				जाओ ERR;
			stage->vf_frame_allocated = true;
		पूर्ण
	पूर्ण अन्यथा अगर (vf_frame && binary && binary->vf_frame_info.res.width
		   && !firmware) अणु
		/* only mark as allocated अगर buffer poपूर्णांकer available */
		अगर (vf_frame->data != mmgr_शून्य)
			stage->vf_frame_allocated = true;
	पूर्ण

	stage->args.in_frame = stage_desc->in_frame;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		stage->args.out_frame[i] = out_frame[i];
	stage->args.out_vf_frame = vf_frame;
	*new_stage = stage;
	वापस err;
ERR:
	अगर (stage)
		pipeline_stage_destroy(stage);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा ia_css_frame ia_css_शेष_frame = DEFAULT_FRAME;

अटल व्योम pipeline_init_शेषs(
    काष्ठा ia_css_pipeline *pipeline,
    क्रमागत ia_css_pipe_id pipe_id,
    अचिन्हित पूर्णांक pipe_num,
    अचिन्हित पूर्णांक dvs_frame_delay)
अणु
	अचिन्हित पूर्णांक i;

	pipeline->pipe_id = pipe_id;
	pipeline->stages = शून्य;
	pipeline->stop_requested = false;
	pipeline->current_stage = शून्य;

	स_नकल(&pipeline->in_frame, &ia_css_शेष_frame,
	       माप(ia_css_शेष_frame));

	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
		स_नकल(&pipeline->out_frame[i], &ia_css_शेष_frame,
		       माप(ia_css_शेष_frame));
		स_नकल(&pipeline->vf_frame[i], &ia_css_शेष_frame,
		       माप(ia_css_शेष_frame));
	पूर्ण
	pipeline->num_execs = -1;
	pipeline->acquire_isp_each_stage = true;
	pipeline->pipe_num = (uपूर्णांक8_t)pipe_num;
	pipeline->dvs_frame_delay = dvs_frame_delay;
पूर्ण

अटल व्योम ia_css_pipeline_set_zoom_stage(काष्ठा ia_css_pipeline *pipeline)
अणु
	काष्ठा ia_css_pipeline_stage *stage = शून्य;
	पूर्णांक err = 0;

	निश्चित(pipeline);
	अगर (pipeline->pipe_id == IA_CSS_PIPE_ID_PREVIEW) अणु
		/* in preview pipeline, vf_pp stage should करो zoom */
		err = ia_css_pipeline_get_stage(pipeline, IA_CSS_BINARY_MODE_VF_PP, &stage);
		अगर (!err)
			stage->enable_zoom = true;
	पूर्ण अन्यथा अगर (pipeline->pipe_id == IA_CSS_PIPE_ID_CAPTURE) अणु
		/* in capture pipeline, capture_pp stage should करो zoom */
		err = ia_css_pipeline_get_stage(pipeline, IA_CSS_BINARY_MODE_CAPTURE_PP,
						&stage);
		अगर (!err)
			stage->enable_zoom = true;
	पूर्ण अन्यथा अगर (pipeline->pipe_id == IA_CSS_PIPE_ID_VIDEO) अणु
		/* in video pipeline, video stage should करो zoom */
		err = ia_css_pipeline_get_stage(pipeline, IA_CSS_BINARY_MODE_VIDEO, &stage);
		अगर (!err)
			stage->enable_zoom = true;
	पूर्ण अन्यथा अगर (pipeline->pipe_id == IA_CSS_PIPE_ID_YUVPP) अणु
		/* in yuvpp pipeline, first yuv_scaler stage should करो zoom */
		err = ia_css_pipeline_get_stage(pipeline, IA_CSS_BINARY_MODE_CAPTURE_PP,
						&stage);
		अगर (!err)
			stage->enable_zoom = true;
	पूर्ण
पूर्ण

अटल व्योम
ia_css_pipeline_configure_inout_port(काष्ठा ia_css_pipeline *me,
				     bool continuous)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipeline_configure_inout_port() enter: pipe_id(%d) continuous(%d)\n",
			    me->pipe_id, continuous);
	चयन (me->pipe_id) अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
	हाल IA_CSS_PIPE_ID_VIDEO:
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)(continuous ? SH_CSS_COPYSINK_TYPE : SH_CSS_HOST_TYPE), 1);
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		अवरोध;
	हाल IA_CSS_PIPE_ID_COPY: /*Copy pipe ports configured to "offline" mode*/
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		अगर (continuous) अणु
			SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
						    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
						    (uपूर्णांक8_t)SH_CSS_COPYSINK_TYPE, 1);
			SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
						    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
						    (uपूर्णांक8_t)SH_CSS_TAGGERSINK_TYPE, 1);
		पूर्ण अन्यथा अणु
			SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
						    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
						    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		पूर्ण
		अवरोध;
	हाल IA_CSS_PIPE_ID_CAPTURE:
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)(continuous ? SH_CSS_TAGGERSINK_TYPE : SH_CSS_HOST_TYPE),
					    1);
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		अवरोध;
	हाल IA_CSS_PIPE_ID_YUVPP:
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)(SH_CSS_HOST_TYPE), 1);
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		अवरोध;
	हाल IA_CSS_PIPE_ID_ACC:
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		SH_CSS_PIPE_PORT_CONFIG_SET(me->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipeline_configure_inout_port() leave: inout_port_config(%x)\n",
			    me->inout_port_config);
पूर्ण
