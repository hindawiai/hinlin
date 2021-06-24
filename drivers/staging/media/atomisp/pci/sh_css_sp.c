<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
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

#समावेश "sh_css_sp.h"

#अगर !defined(ISP2401)
#समावेश "input_formatter.h"
#पूर्ण_अगर

#समावेश "dma.h"	/* N_DMA_CHANNEL_ID */

#समावेश "ia_css_buffer.h"
#समावेश "ia_css_binary.h"
#समावेश "sh_css_hrt.h"
#समावेश "sh_css_defs.h"
#समावेश "sh_css_internal.h"
#समावेश "ia_css_control.h"
#समावेश "ia_css_debug.h"
#समावेश "ia_css_debug_pipe.h"
#समावेश "ia_css_event_public.h"
#समावेश "ia_css_mmu.h"
#समावेश "ia_css_stream.h"
#समावेश "ia_css_isp_param.h"
#समावेश "sh_css_params.h"
#समावेश "sh_css_legacy.h"
#समावेश "ia_css_frame_comm.h"
#समावेश "ia_css_isys.h"

#समावेश "gdc_device.h"				/* HRT_GDC_N */

/*#समावेश "sp.h"*/	/* host2sp_enqueue_frame_data() */


#समावेश "assert_support.h"

#समावेश "sw_event_global.h"			/* Event IDs.*/
#समावेश "ia_css_event.h"
#समावेश "mmu_device.h"
#समावेश "ia_css_spctrl.h"

#अगर_अघोषित दुरत्व
#घोषणा दुरत्व(T, x) ((अचिन्हित पूर्णांक)&(((T *)0)->x))
#पूर्ण_अगर

#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#घोषणा IA_CSS_INCLUDE_STATES
#समावेश "ia_css_isp_states.h"

#समावेश "isp/kernels/ipu2_io_ls/bayer_io_ls/ia_css_bayer_io.host.h"

काष्ठा sh_css_sp_group		sh_css_sp_group;
काष्ठा sh_css_sp_stage		sh_css_sp_stage;
काष्ठा sh_css_isp_stage		sh_css_isp_stage;
अटल काष्ठा sh_css_sp_output		sh_css_sp_output;
अटल काष्ठा sh_css_sp_per_frame_data per_frame_data;

/* true अगर SP supports frame loop and host2sp_commands */
/* For the moment there is only code that sets this bool to true */
/* TODO: add code that sets this bool to false */
अटल bool sp_running;

अटल पूर्णांक
set_output_frame_buffer(स्थिर काष्ठा ia_css_frame *frame,
			अचिन्हित पूर्णांक idx);

अटल व्योम
sh_css_copy_buffer_attr_to_spbuffer(काष्ठा ia_css_buffer_sp *dest_buf,
				    स्थिर क्रमागत sh_css_queue_id queue_id,
				    स्थिर ia_css_ptr xmem_addr,
				    स्थिर क्रमागत ia_css_buffer_type buf_type);

अटल व्योम
initialize_frame_buffer_attribute(काष्ठा ia_css_buffer_sp *buf_attr);

अटल व्योम
initialize_stage_frames(काष्ठा ia_css_frames_sp *frames);

/* This data is stored every frame */
व्योम
store_sp_group_data(व्योम)
अणु
	per_frame_data.sp_group_addr = sh_css_store_sp_group_to_ddr();
पूर्ण

अटल व्योम
copy_isp_stage_to_sp_stage(व्योम)
अणु
	/* [WW07.5]type casting will cause potential issues */
	sh_css_sp_stage.num_stripes = (uपूर्णांक8_t)
				      sh_css_isp_stage.binary_info.iterator.num_stripes;
	sh_css_sp_stage.row_stripes_height = (uपूर्णांक16_t)
					     sh_css_isp_stage.binary_info.iterator.row_stripes_height;
	sh_css_sp_stage.row_stripes_overlap_lines = (uपूर्णांक16_t)
		sh_css_isp_stage.binary_info.iterator.row_stripes_overlap_lines;
	sh_css_sp_stage.top_cropping = (uपूर्णांक16_t)
				       sh_css_isp_stage.binary_info.pipeline.top_cropping;
	/* moved to sh_css_sp_init_stage
	   sh_css_sp_stage.enable.vf_output =
	   sh_css_isp_stage.binary_info.enable.vf_veceven ||
	   sh_css_isp_stage.binary_info.num_output_pins > 1;
	*/
	sh_css_sp_stage.enable.sdis = sh_css_isp_stage.binary_info.enable.dis;
	sh_css_sp_stage.enable.s3a = sh_css_isp_stage.binary_info.enable.s3a;
पूर्ण

व्योम
store_sp_stage_data(क्रमागत ia_css_pipe_id id, अचिन्हित पूर्णांक pipe_num,
		    अचिन्हित पूर्णांक stage)
अणु
	अचिन्हित पूर्णांक thपढ़ो_id;

	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	copy_isp_stage_to_sp_stage();
	अगर (id != IA_CSS_PIPE_ID_COPY)
		sh_css_sp_stage.isp_stage_addr =
		    sh_css_store_isp_stage_to_ddr(pipe_num, stage);
	sh_css_sp_group.pipe[thपढ़ो_id].sp_stage_addr[stage] =
	    sh_css_store_sp_stage_to_ddr(pipe_num, stage);

	/* Clear क्रम next frame */
	sh_css_sp_stage.program_input_circuit = false;
पूर्ण

अटल व्योम
store_sp_per_frame_data(स्थिर काष्ठा ia_css_fw_info *fw)
अणु
	अचिन्हित पूर्णांक HIVE_ADDR_sp_per_frame_data = 0;

	निश्चित(fw);

	चयन (fw->type) अणु
	हाल ia_css_sp_firmware:
		HIVE_ADDR_sp_per_frame_data = fw->info.sp.per_frame_data;
		अवरोध;
	हाल ia_css_acc_firmware:
		HIVE_ADDR_sp_per_frame_data = fw->info.acc.per_frame_data;
		अवरोध;
	हाल ia_css_isp_firmware:
		वापस;
	पूर्ण

	sp_dmem_store(SP0_ID,
		      (अचिन्हित पूर्णांक)sp_address_of(sp_per_frame_data),
		      &per_frame_data,
		      माप(per_frame_data));
पूर्ण

अटल व्योम
sh_css_store_sp_per_frame_data(क्रमागत ia_css_pipe_id pipe_id,
			       अचिन्हित पूर्णांक pipe_num,
			       स्थिर काष्ठा ia_css_fw_info *sp_fw)
अणु
	अगर (!sp_fw)
		sp_fw = &sh_css_sp_fw;

	store_sp_stage_data(pipe_id, pipe_num, 0);
	store_sp_group_data();
	store_sp_per_frame_data(sp_fw);
पूर्ण

#अगर SP_DEBUG != SP_DEBUG_NONE

व्योम
sh_css_sp_get_debug_state(काष्ठा sh_css_sp_debug_state *state)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw = &sh_css_sp_fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_output = fw->info.sp.output;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा sh_css_sp_output,
			      debug) / माप(पूर्णांक);

	निश्चित(state);

	(व्योम)HIVE_ADDR_sp_output; /* To get rid of warning in CRUN */
	क्रम (i = 0; i < माप(*state) / माप(पूर्णांक); i++)
		((अचिन्हित *)state)[i] = load_sp_array_uपूर्णांक(sp_output, i + offset);
पूर्ण

#पूर्ण_अगर

व्योम
sh_css_sp_start_binary_copy(अचिन्हित पूर्णांक pipe_num,
			    काष्ठा ia_css_frame *out_frame,
			    अचिन्हित पूर्णांक two_ppc)
अणु
	क्रमागत ia_css_pipe_id pipe_id;
	अचिन्हित पूर्णांक thपढ़ो_id;
	काष्ठा sh_css_sp_pipeline *pipe;
	u8 stage_num = 0;

	निश्चित(out_frame);
	pipe_id = IA_CSS_PIPE_ID_CAPTURE;
	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	pipe = &sh_css_sp_group.pipe[thपढ़ो_id];

	pipe->copy.bin.bytes_available = out_frame->data_bytes;
	pipe->num_stages = 1;
	pipe->pipe_id = pipe_id;
	pipe->pipe_num = pipe_num;
	pipe->thपढ़ो_id = thपढ़ो_id;
	pipe->pipe_config = 0x0; /* No parameters */
	pipe->pipe_qos_config = QOS_INVALID;

	अगर (pipe->inout_port_config == 0) अणु
		SH_CSS_PIPE_PORT_CONFIG_SET(pipe->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		SH_CSS_PIPE_PORT_CONFIG_SET(pipe->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
	पूर्ण
	IA_CSS_LOG("pipe_id %d port_config %08x",
		   pipe->pipe_id, pipe->inout_port_config);

#अगर !defined(ISP2401)
	sh_css_sp_group.config.input_क्रमmatter.isp_2ppc = (uपूर्णांक8_t)two_ppc;
#अन्यथा
	(व्योम)two_ppc;
#पूर्ण_अगर

	sh_css_sp_stage.num = stage_num;
	sh_css_sp_stage.stage_type = SH_CSS_SP_STAGE_TYPE;
	sh_css_sp_stage.func =
	    (अचिन्हित पूर्णांक)IA_CSS_PIPELINE_BIN_COPY;

	set_output_frame_buffer(out_frame, 0);

	/* sp_bin_copy_init on the SP करोes not deal with dynamica/अटल yet */
	/* For now always update the dynamic data from out frames. */
	sh_css_store_sp_per_frame_data(pipe_id, pipe_num, &sh_css_sp_fw);
पूर्ण

अटल व्योम
sh_css_sp_start_raw_copy(काष्ठा ia_css_frame *out_frame,
			 अचिन्हित पूर्णांक pipe_num,
			 अचिन्हित पूर्णांक two_ppc,
			 अचिन्हित पूर्णांक max_input_width,
			 क्रमागत sh_css_pipe_config_override pipe_conf_override,
			 अचिन्हित पूर्णांक अगर_config_index)
अणु
	क्रमागत ia_css_pipe_id pipe_id;
	अचिन्हित पूर्णांक thपढ़ो_id;
	u8 stage_num = 0;
	काष्ठा sh_css_sp_pipeline *pipe;

	निश्चित(out_frame);

	अणु
		/*
		 * Clear sh_css_sp_stage क्रम easy debugging.
		 * program_input_circuit must be saved as it is set outside
		 * this function.
		 */
		u8 program_input_circuit;

		program_input_circuit = sh_css_sp_stage.program_input_circuit;
		स_रखो(&sh_css_sp_stage, 0, माप(sh_css_sp_stage));
		sh_css_sp_stage.program_input_circuit = program_input_circuit;
	पूर्ण

	pipe_id = IA_CSS_PIPE_ID_COPY;
	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	pipe = &sh_css_sp_group.pipe[thपढ़ो_id];

	pipe->copy.raw.height	    = out_frame->info.res.height;
	pipe->copy.raw.width	    = out_frame->info.res.width;
	pipe->copy.raw.padded_width  = out_frame->info.padded_width;
	pipe->copy.raw.raw_bit_depth = out_frame->info.raw_bit_depth;
	pipe->copy.raw.max_input_width = max_input_width;
	pipe->num_stages = 1;
	pipe->pipe_id = pipe_id;
	/* TODO: next indicates from which queues parameters need to be
		 sampled, needs checking/improvement */
	अगर (pipe_conf_override == SH_CSS_PIPE_CONFIG_OVRD_NO_OVRD)
		pipe->pipe_config =
		    (SH_CSS_PIPE_CONFIG_SAMPLE_PARAMS << thपढ़ो_id);
	अन्यथा
		pipe->pipe_config = pipe_conf_override;

	pipe->pipe_qos_config = QOS_INVALID;

	अगर (pipe->inout_port_config == 0) अणु
		SH_CSS_PIPE_PORT_CONFIG_SET(pipe->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_INPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
		SH_CSS_PIPE_PORT_CONFIG_SET(pipe->inout_port_config,
					    (uपूर्णांक8_t)SH_CSS_PORT_OUTPUT,
					    (uपूर्णांक8_t)SH_CSS_HOST_TYPE, 1);
	पूर्ण
	IA_CSS_LOG("pipe_id %d port_config %08x",
		   pipe->pipe_id, pipe->inout_port_config);

#अगर !defined(ISP2401)
	sh_css_sp_group.config.input_क्रमmatter.isp_2ppc = (uपूर्णांक8_t)two_ppc;
#अन्यथा
	(व्योम)two_ppc;
#पूर्ण_अगर

	sh_css_sp_stage.num = stage_num;
	sh_css_sp_stage.xmem_bin_addr = 0x0;
	sh_css_sp_stage.stage_type = SH_CSS_SP_STAGE_TYPE;
	sh_css_sp_stage.func = (अचिन्हित पूर्णांक)IA_CSS_PIPELINE_RAW_COPY;
	sh_css_sp_stage.अगर_config_index = (uपूर्णांक8_t)अगर_config_index;
	set_output_frame_buffer(out_frame, 0);

	ia_css_debug_pipe_graph_dump_sp_raw_copy(out_frame);
पूर्ण

अटल व्योम
sh_css_sp_start_isys_copy(काष्ठा ia_css_frame *out_frame,
			  अचिन्हित पूर्णांक pipe_num, अचिन्हित पूर्णांक max_input_width,
			  अचिन्हित पूर्णांक अगर_config_index)
अणु
	क्रमागत ia_css_pipe_id pipe_id;
	अचिन्हित पूर्णांक thपढ़ो_id;
	u8 stage_num = 0;
	काष्ठा sh_css_sp_pipeline *pipe;
#अगर defined SH_CSS_ENABLE_METADATA
	क्रमागत sh_css_queue_id queue_id;
#पूर्ण_अगर

	निश्चित(out_frame);

	अणु
		/*
		 * Clear sh_css_sp_stage क्रम easy debugging.
		 * program_input_circuit must be saved as it is set outside
		 * this function.
		 */
		u8 program_input_circuit;

		program_input_circuit = sh_css_sp_stage.program_input_circuit;
		स_रखो(&sh_css_sp_stage, 0, माप(sh_css_sp_stage));
		sh_css_sp_stage.program_input_circuit = program_input_circuit;
	पूर्ण

	pipe_id = IA_CSS_PIPE_ID_COPY;
	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	pipe = &sh_css_sp_group.pipe[thपढ़ो_id];

	pipe->copy.raw.height		= out_frame->info.res.height;
	pipe->copy.raw.width		= out_frame->info.res.width;
	pipe->copy.raw.padded_width	= out_frame->info.padded_width;
	pipe->copy.raw.raw_bit_depth	= out_frame->info.raw_bit_depth;
	pipe->copy.raw.max_input_width	= max_input_width;
	pipe->num_stages		= 1;
	pipe->pipe_id			= pipe_id;
	pipe->pipe_config		= 0x0;	/* No parameters */
	pipe->pipe_qos_config		= QOS_INVALID;

	initialize_stage_frames(&sh_css_sp_stage.frames);
	sh_css_sp_stage.num = stage_num;
	sh_css_sp_stage.xmem_bin_addr = 0x0;
	sh_css_sp_stage.stage_type = SH_CSS_SP_STAGE_TYPE;
	sh_css_sp_stage.func = (अचिन्हित पूर्णांक)IA_CSS_PIPELINE_ISYS_COPY;
	sh_css_sp_stage.अगर_config_index = (uपूर्णांक8_t)अगर_config_index;

	set_output_frame_buffer(out_frame, 0);

#अगर defined SH_CSS_ENABLE_METADATA
	अगर (pipe->metadata.height > 0) अणु
		ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_METADATA, thपढ़ो_id,
					       &queue_id);
		sh_css_copy_buffer_attr_to_spbuffer(&sh_css_sp_stage.frames.metadata_buf,
						    queue_id, mmgr_EXCEPTION,
						    IA_CSS_BUFFER_TYPE_METADATA);
	पूर्ण
#पूर्ण_अगर

	ia_css_debug_pipe_graph_dump_sp_raw_copy(out_frame);
पूर्ण

अचिन्हित पूर्णांक
sh_css_sp_get_binary_copy_size(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw = &sh_css_sp_fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_output = fw->info.sp.output;
	अचिन्हित पूर्णांक offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा sh_css_sp_output,
			      bin_copy_bytes_copied) / माप(पूर्णांक);
	(व्योम)HIVE_ADDR_sp_output; /* To get rid of warning in CRUN */
	वापस load_sp_array_uपूर्णांक(sp_output, offset);
पूर्ण

अचिन्हित पूर्णांक
sh_css_sp_get_sw_पूर्णांकerrupt_value(अचिन्हित पूर्णांक irq)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw = &sh_css_sp_fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_output = fw->info.sp.output;
	अचिन्हित पूर्णांक offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा sh_css_sp_output,
			      sw_पूर्णांकerrupt_value)
			      / माप(पूर्णांक);
	(व्योम)HIVE_ADDR_sp_output; /* To get rid of warning in CRUN */
	वापस load_sp_array_uपूर्णांक(sp_output, offset + irq);
पूर्ण

अटल व्योम
sh_css_copy_buffer_attr_to_spbuffer(काष्ठा ia_css_buffer_sp *dest_buf,
				    स्थिर क्रमागत sh_css_queue_id queue_id,
				    स्थिर ia_css_ptr xmem_addr,
				    स्थिर क्रमागत ia_css_buffer_type buf_type)
अणु
	निश्चित(buf_type < IA_CSS_NUM_BUFFER_TYPE);
	अगर (queue_id > SH_CSS_INVALID_QUEUE_ID) अणु
		/*
		 * value >=0 indicates that function init_frame_poपूर्णांकers()
		 * should use the dynamic data address
		 */
		निश्चित(queue_id < SH_CSS_MAX_NUM_QUEUES);

		/* Klocwork assumes निश्चित can be disabled;
		   Since we can get there with any type, and it करोes not
		   know that frame_in->dynamic_data_index can only be set
		   क्रम one of the types in the निश्चित) it has to assume we
		   can get here क्रम any type. however this could lead to an
		   out of bounds reference when indexing buf_type about 10
		   lines below. In order to satisfy KW an additional अगर
		   has been added. This one will always yield true.
		 */
		अगर ((queue_id < SH_CSS_MAX_NUM_QUEUES)) अणु
			dest_buf->buf_src.queue_id = queue_id;
		पूर्ण
	पूर्ण अन्यथा अणु
		निश्चित(xmem_addr != mmgr_EXCEPTION);
		dest_buf->buf_src.xmem_addr = xmem_addr;
	पूर्ण
	dest_buf->buf_type = buf_type;
पूर्ण

अटल व्योम
sh_css_copy_frame_to_spframe(काष्ठा ia_css_frame_sp *sp_frame_out,
			     स्थिर काष्ठा ia_css_frame *frame_in)
अणु
	निश्चित(frame_in);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_copy_frame_to_spframe():\n");

	sh_css_copy_buffer_attr_to_spbuffer(&sp_frame_out->buf_attr,
					    frame_in->dynamic_queue_id,
					    frame_in->data,
					    frame_in->buf_type);

	ia_css_frame_info_to_frame_sp_info(&sp_frame_out->info, &frame_in->info);

	चयन (frame_in->info.क्रमmat) अणु
	हाल IA_CSS_FRAME_FORMAT_RAW_PACKED:
	हाल IA_CSS_FRAME_FORMAT_RAW:
		sp_frame_out->planes.raw.offset = frame_in->planes.raw.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RGB565:
	हाल IA_CSS_FRAME_FORMAT_RGBA888:
		sp_frame_out->planes.rgb.offset = frame_in->planes.rgb.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_PLANAR_RGB888:
		sp_frame_out->planes.planar_rgb.r.offset =
		    frame_in->planes.planar_rgb.r.offset;
		sp_frame_out->planes.planar_rgb.g.offset =
		    frame_in->planes.planar_rgb.g.offset;
		sp_frame_out->planes.planar_rgb.b.offset =
		    frame_in->planes.planar_rgb.b.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_UYVY:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
		sp_frame_out->planes.yuyv.offset = frame_in->planes.yuyv.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_NV11:
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV12_16:
	हाल IA_CSS_FRAME_FORMAT_NV12_TILEY:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_NV16:
	हाल IA_CSS_FRAME_FORMAT_NV61:
		sp_frame_out->planes.nv.y.offset =
		    frame_in->planes.nv.y.offset;
		sp_frame_out->planes.nv.uv.offset =
		    frame_in->planes.nv.uv.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_YUV422:
	हाल IA_CSS_FRAME_FORMAT_YUV444:
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
	हाल IA_CSS_FRAME_FORMAT_YUV422_16:
	हाल IA_CSS_FRAME_FORMAT_YV12:
	हाल IA_CSS_FRAME_FORMAT_YV16:
		sp_frame_out->planes.yuv.y.offset =
		    frame_in->planes.yuv.y.offset;
		sp_frame_out->planes.yuv.u.offset =
		    frame_in->planes.yuv.u.offset;
		sp_frame_out->planes.yuv.v.offset =
		    frame_in->planes.yuv.v.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
		sp_frame_out->planes.plane6.r.offset =
		    frame_in->planes.plane6.r.offset;
		sp_frame_out->planes.plane6.r_at_b.offset =
		    frame_in->planes.plane6.r_at_b.offset;
		sp_frame_out->planes.plane6.gr.offset =
		    frame_in->planes.plane6.gr.offset;
		sp_frame_out->planes.plane6.gb.offset =
		    frame_in->planes.plane6.gb.offset;
		sp_frame_out->planes.plane6.b.offset =
		    frame_in->planes.plane6.b.offset;
		sp_frame_out->planes.plane6.b_at_r.offset =
		    frame_in->planes.plane6.b_at_r.offset;
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_BINARY_8:
		sp_frame_out->planes.binary.data.offset =
		    frame_in->planes.binary.data.offset;
		अवरोध;
	शेष:
		/* This should not happen, but in हाल it करोes,
		 * nullअगरy the planes
		 */
		स_रखो(&sp_frame_out->planes, 0, माप(sp_frame_out->planes));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
set_input_frame_buffer(स्थिर काष्ठा ia_css_frame *frame) अणु
	अगर (!frame)
		वापस -EINVAL;

	चयन (frame->info.क्रमmat)
	अणु
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
	हाल IA_CSS_FRAME_FORMAT_RAW_PACKED:
	हाल IA_CSS_FRAME_FORMAT_RAW:
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV12_16:
	हाल IA_CSS_FRAME_FORMAT_NV12_TILEY:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_10:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	sh_css_copy_frame_to_spframe(&sh_css_sp_stage.frames.in, frame);

	वापस 0;
पूर्ण

अटल पूर्णांक
set_output_frame_buffer(स्थिर काष्ठा ia_css_frame *frame,
			अचिन्हित पूर्णांक idx) अणु
	अगर (!frame)
		वापस -EINVAL;

	चयन (frame->info.क्रमmat)
	अणु
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_YUV422:
	हाल IA_CSS_FRAME_FORMAT_YUV444:
	हाल IA_CSS_FRAME_FORMAT_YV12:
	हाल IA_CSS_FRAME_FORMAT_YV16:
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
	हाल IA_CSS_FRAME_FORMAT_YUV422_16:
	हाल IA_CSS_FRAME_FORMAT_NV11:
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV12_16:
	हाल IA_CSS_FRAME_FORMAT_NV12_TILEY:
	हाल IA_CSS_FRAME_FORMAT_NV16:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_NV61:
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_UYVY:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
	हाल IA_CSS_FRAME_FORMAT_RGB565:
	हाल IA_CSS_FRAME_FORMAT_RGBA888:
	हाल IA_CSS_FRAME_FORMAT_PLANAR_RGB888:
	हाल IA_CSS_FRAME_FORMAT_RAW:
	हाल IA_CSS_FRAME_FORMAT_RAW_PACKED:
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
	हाल IA_CSS_FRAME_FORMAT_BINARY_8:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	sh_css_copy_frame_to_spframe(&sh_css_sp_stage.frames.out[idx], frame);
	वापस 0;
पूर्ण

अटल पूर्णांक
set_view_finder_buffer(स्थिर काष्ठा ia_css_frame *frame) अणु
	अगर (!frame)
		वापस -EINVAL;

	चयन (frame->info.क्रमmat)
	अणु
	/* the dual output pin */
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV12_16:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_UYVY:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_YV12:
	हाल IA_CSS_FRAME_FORMAT_NV12_TILEY:

	/* क्रम vf_veceven */
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sh_css_copy_frame_to_spframe(&sh_css_sp_stage.frames.out_vf, frame);
	वापस 0;
पूर्ण

#अगर !defined(ISP2401)
व्योम sh_css_sp_set_अगर_configs(
    स्थिर input_क्रमmatter_cfg_t	*config_a,
    स्थिर input_क्रमmatter_cfg_t	*config_b,
    स्थिर uपूर्णांक8_t		अगर_config_index
)
अणु
	निश्चित(अगर_config_index < SH_CSS_MAX_IF_CONFIGS);
	निश्चित(config_a);

	sh_css_sp_group.config.input_क्रमmatter.set[अगर_config_index].config_a =
	    *config_a;
	sh_css_sp_group.config.input_क्रमmatter.a_changed = true;

	अगर (config_b) अणु
		sh_css_sp_group.config.input_क्रमmatter.set[अगर_config_index].config_b =
		    *config_b;
		sh_css_sp_group.config.input_क्रमmatter.b_changed = true;
	पूर्ण

	वापस;
पूर्ण
#पूर्ण_अगर

#अगर !defined(ISP2401)
व्योम
sh_css_sp_program_input_circuit(पूर्णांक fmt_type,
				पूर्णांक ch_id,
				क्रमागत ia_css_input_mode input_mode)
अणु
	sh_css_sp_group.config.input_circuit.no_side_band = false;
	sh_css_sp_group.config.input_circuit.fmt_type     = fmt_type;
	sh_css_sp_group.config.input_circuit.ch_id	      = ch_id;
	sh_css_sp_group.config.input_circuit.input_mode   = input_mode;
	/*
	 * The SP group is only loaded at SP boot समय and is पढ़ो once
	 * change flags as "input_circuit_cfg_changed" must be reset on the SP
	 */
	sh_css_sp_group.config.input_circuit_cfg_changed = true;
	sh_css_sp_stage.program_input_circuit = true;
पूर्ण
#पूर्ण_अगर

#अगर !defined(ISP2401)
व्योम
sh_css_sp_configure_sync_gen(पूर्णांक width, पूर्णांक height,
			     पूर्णांक hblank_cycles,
			     पूर्णांक vblank_cycles)
अणु
	sh_css_sp_group.config.sync_gen.width	       = width;
	sh_css_sp_group.config.sync_gen.height	       = height;
	sh_css_sp_group.config.sync_gen.hblank_cycles = hblank_cycles;
	sh_css_sp_group.config.sync_gen.vblank_cycles = vblank_cycles;
पूर्ण

व्योम
sh_css_sp_configure_tpg(पूर्णांक x_mask,
			पूर्णांक y_mask,
			पूर्णांक x_delta,
			पूर्णांक y_delta,
			पूर्णांक xy_mask)
अणु
	sh_css_sp_group.config.tpg.x_mask  = x_mask;
	sh_css_sp_group.config.tpg.y_mask  = y_mask;
	sh_css_sp_group.config.tpg.x_delta = x_delta;
	sh_css_sp_group.config.tpg.y_delta = y_delta;
	sh_css_sp_group.config.tpg.xy_mask = xy_mask;
पूर्ण

व्योम
sh_css_sp_configure_prbs(पूर्णांक seed)
अणु
	sh_css_sp_group.config.prbs.seed = seed;
पूर्ण
#पूर्ण_अगर

व्योम
sh_css_sp_configure_enable_raw_pool_locking(bool lock_all)
अणु
	sh_css_sp_group.config.enable_raw_pool_locking = true;
	sh_css_sp_group.config.lock_all = lock_all;
पूर्ण

व्योम
sh_css_sp_enable_isys_event_queue(bool enable)
अणु
	sh_css_sp_group.config.enable_isys_event_queue = enable;
पूर्ण

व्योम
sh_css_sp_set_disable_continuous_viewfinder(bool flag)
अणु
	sh_css_sp_group.config.disable_cont_vf = flag;
पूर्ण

अटल पूर्णांक
sh_css_sp_ग_लिखो_frame_poपूर्णांकers(स्थिर काष्ठा sh_css_binary_args *args) अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	निश्चित(args);

	अगर (args->in_frame)
		err = set_input_frame_buffer(args->in_frame);
	अगर (!err && args->out_vf_frame)
		err = set_view_finder_buffer(args->out_vf_frame);
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
	अणु
		अगर (!err && args->out_frame[i])
			err = set_output_frame_buffer(args->out_frame[i], i);
	पूर्ण

	/* we करोn't pass this error back to the upper layer, so we add a निश्चित here
	   because we actually hit the error here but it still works by accident... */
	अगर (err) निश्चित(false);
	वापस err;
पूर्ण

अटल व्योम
sh_css_sp_init_group(bool two_ppc,
		     क्रमागत atomisp_input_क्रमmat input_क्रमmat,
		     bool no_isp_sync,
		     uपूर्णांक8_t अगर_config_index)
अणु
#अगर !defined(ISP2401)
	sh_css_sp_group.config.input_क्रमmatter.isp_2ppc = two_ppc;
#अन्यथा
	(व्योम)two_ppc;
#पूर्ण_अगर

	sh_css_sp_group.config.no_isp_sync = (uपूर्णांक8_t)no_isp_sync;
	/* decide whether the frame is processed online or offline */
	अगर (अगर_config_index == SH_CSS_IF_CONFIG_NOT_NEEDED) वापस;
#अगर !defined(ISP2401)
	निश्चित(अगर_config_index < SH_CSS_MAX_IF_CONFIGS);
	sh_css_sp_group.config.input_क्रमmatter.set[अगर_config_index].stream_क्रमmat =
	    input_क्रमmat;
#अन्यथा
	(व्योम)input_क्रमmat;
#पूर्ण_अगर
पूर्ण

व्योम
sh_css_stage_ग_लिखो_binary_info(काष्ठा ia_css_binary_info *info)
अणु
	निश्चित(info);
	sh_css_isp_stage.binary_info = *info;
पूर्ण

अटल पूर्णांक
copy_isp_mem_अगर_to_ddr(काष्ठा ia_css_binary *binary) अणु
	पूर्णांक err;

	err = ia_css_isp_param_copy_isp_mem_अगर_to_ddr(
	    &binary->css_params,
	    &binary->mem_params,
	    IA_CSS_PARAM_CLASS_CONFIG);
	अगर (err)
		वापस err;
	err = ia_css_isp_param_copy_isp_mem_अगर_to_ddr(
	    &binary->css_params,
	    &binary->mem_params,
	    IA_CSS_PARAM_CLASS_STATE);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

अटल bool
is_sp_stage(काष्ठा ia_css_pipeline_stage *stage)
अणु
	निश्चित(stage);
	वापस stage->sp_func != IA_CSS_PIPELINE_NO_FUNC;
पूर्ण

अटल पूर्णांक
configure_isp_from_args(
    स्थिर काष्ठा sh_css_sp_pipeline *pipeline,
    स्थिर काष्ठा ia_css_binary      *binary,
    स्थिर काष्ठा sh_css_binary_args *args,
    bool two_ppc,
    bool deपूर्णांकerleaved) अणु
	ia_css_fpn_configure(binary,  &binary->in_frame_info);
	ia_css_crop_configure(binary, &args->delay_frames[0]->info);
	ia_css_qplane_configure(pipeline, binary, &binary->in_frame_info);
	ia_css_output0_configure(binary, &args->out_frame[0]->info);
	ia_css_output1_configure(binary, &args->out_vf_frame->info);
	ia_css_copy_output_configure(binary, args->copy_output);
	ia_css_output0_configure(binary, &args->out_frame[0]->info);
#अगर_घोषित ISP2401
	ia_css_sc_configure(binary, pipeline->shading.पूर्णांकernal_frame_origin_x_bqs_on_sctbl,
			    pipeline->shading.पूर्णांकernal_frame_origin_y_bqs_on_sctbl);
#पूर्ण_अगर
	ia_css_iterator_configure(binary, &args->in_frame->info);
	ia_css_dvs_configure(binary, &args->out_frame[0]->info);
	ia_css_output_configure(binary, &args->out_frame[0]->info);
	ia_css_raw_configure(pipeline, binary, &args->in_frame->info, &binary->in_frame_info, two_ppc, deपूर्णांकerleaved);

	/*
	 * FIXME: args->delay_frames can be शून्य here
	 *
	 * Somehow, the driver at the Intel Atom Yocto tree करोesn't seem to
	 * suffer from the same issue.
	 *
	 * Anyway, the function below should now handle a शून्य delay_frames
	 * without crashing, but the pipeline should likely be built without
	 * adding it at the first place (or there are a hidden bug somewhere)
	 */
	ia_css_ref_configure(binary, args->delay_frames, pipeline->dvs_frame_delay);
	ia_css_tnr_configure(binary, args->tnr_frames);
	ia_css_bayer_io_config(binary, args);
	वापस 0;
पूर्ण

अटल व्योम
initialize_isp_states(स्थिर काष्ठा ia_css_binary *binary)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!binary->info->mem_offsets.offsets.state)
		वापस;
	क्रम (i = 0; i < IA_CSS_NUM_STATE_IDS; i++) अणु
		ia_css_kernel_init_state[i](binary);
	पूर्ण
पूर्ण

अटल व्योम
initialize_frame_buffer_attribute(काष्ठा ia_css_buffer_sp *buf_attr)
अणु
	buf_attr->buf_src.queue_id = SH_CSS_INVALID_QUEUE_ID;
	buf_attr->buf_type = IA_CSS_BUFFER_TYPE_INVALID;
पूर्ण

अटल व्योम
initialize_stage_frames(काष्ठा ia_css_frames_sp *frames)
अणु
	अचिन्हित पूर्णांक i;

	initialize_frame_buffer_attribute(&frames->in.buf_attr);
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		initialize_frame_buffer_attribute(&frames->out[i].buf_attr);
	पूर्ण
	initialize_frame_buffer_attribute(&frames->out_vf.buf_attr);
	initialize_frame_buffer_attribute(&frames->s3a_buf);
	initialize_frame_buffer_attribute(&frames->dvs_buf);
#अगर defined SH_CSS_ENABLE_METADATA
	initialize_frame_buffer_attribute(&frames->metadata_buf);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
sh_css_sp_init_stage(काष्ठा ia_css_binary *binary,
		     स्थिर अक्षर *binary_name,
		     स्थिर काष्ठा ia_css_blob_info *blob_info,
		     स्थिर काष्ठा sh_css_binary_args *args,
		     अचिन्हित पूर्णांक pipe_num,
		     अचिन्हित पूर्णांक stage,
		     bool xnr,
		     स्थिर काष्ठा ia_css_isp_param_css_segments *isp_mem_अगर,
		     अचिन्हित पूर्णांक अगर_config_index,
		     bool two_ppc) अणु
	स्थिर काष्ठा ia_css_binary_xinfo *xinfo;
	स्थिर काष्ठा ia_css_binary_info  *info;
	पूर्णांक err = 0;
	पूर्णांक i;
	काष्ठा ia_css_pipe *pipe = शून्य;
	अचिन्हित पूर्णांक thपढ़ो_id;
	क्रमागत sh_css_queue_id queue_id;
	bool continuous = sh_css_continuous_is_enabled((uपूर्णांक8_t)pipe_num);

	निश्चित(binary);
	निश्चित(blob_info);
	निश्चित(args);
	निश्चित(isp_mem_अगर);

	xinfo = binary->info;
	info  = &xinfo->sp;
	अणु
		/*
		 * Clear sh_css_sp_stage क्रम easy debugging.
		 * program_input_circuit must be saved as it is set outside
		 * this function.
		 */
		u8 program_input_circuit;

		program_input_circuit = sh_css_sp_stage.program_input_circuit;
		स_रखो(&sh_css_sp_stage, 0, माप(sh_css_sp_stage));
		sh_css_sp_stage.program_input_circuit = (uपूर्णांक8_t)program_input_circuit;
	पूर्ण

	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);

	अगर (!info)
	अणु
		sh_css_sp_group.pipe[thपढ़ो_id].sp_stage_addr[stage] = mmgr_शून्य;
		वापस 0;
	पूर्ण

#अगर defined(ISP2401)
	(व्योम)continuous;
	sh_css_sp_stage.deपूर्णांकerleaved = 0;
#अन्यथा
	sh_css_sp_stage.deपूर्णांकerleaved = ((stage == 0) && continuous);
#पूर्ण_अगर

	initialize_stage_frames(&sh_css_sp_stage.frames);
	/*
	 * TODO: Make the Host dynamically determine
	 * the stage type.
	 */
	sh_css_sp_stage.stage_type = SH_CSS_ISP_STAGE_TYPE;
	sh_css_sp_stage.num		= (uपूर्णांक8_t)stage;
	sh_css_sp_stage.isp_online	= (uपूर्णांक8_t)binary->online;
	sh_css_sp_stage.isp_copy_vf     = (uपूर्णांक8_t)args->copy_vf;
	sh_css_sp_stage.isp_copy_output = (uपूर्णांक8_t)args->copy_output;
	sh_css_sp_stage.enable.vf_output = (args->out_vf_frame != शून्य);

	/* Copy the frame infos first, to be overwritten by the frames,
	   अगर these are present.
	*/
	sh_css_sp_stage.frames.effective_in_res.width = binary->effective_in_frame_res.width;
	sh_css_sp_stage.frames.effective_in_res.height = binary->effective_in_frame_res.height;

	ia_css_frame_info_to_frame_sp_info(&sh_css_sp_stage.frames.in.info,
					   &binary->in_frame_info);
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
	अणु
		ia_css_frame_info_to_frame_sp_info(&sh_css_sp_stage.frames.out[i].info,
						   &binary->out_frame_info[i]);
	पूर्ण
	ia_css_frame_info_to_frame_sp_info(&sh_css_sp_stage.frames.पूर्णांकernal_frame_info,
					   &binary->पूर्णांकernal_frame_info);
	sh_css_sp_stage.dvs_envelope.width    = binary->dvs_envelope.width;
	sh_css_sp_stage.dvs_envelope.height   = binary->dvs_envelope.height;
	sh_css_sp_stage.isp_pipe_version      = (uपूर्णांक8_t)info->pipeline.isp_pipe_version;
	sh_css_sp_stage.isp_deci_log_factor   = (uपूर्णांक8_t)binary->deci_factor_log2;
	sh_css_sp_stage.isp_vf_करोwnscale_bits = (uपूर्णांक8_t)binary->vf_करोwnscale_log2;

	sh_css_sp_stage.अगर_config_index = (uपूर्णांक8_t)अगर_config_index;

	sh_css_sp_stage.sp_enable_xnr = (uपूर्णांक8_t)xnr;
	sh_css_sp_stage.xmem_bin_addr = xinfo->xmem_addr;
	sh_css_sp_stage.xmem_map_addr = sh_css_params_ddr_address_map();
	sh_css_isp_stage.blob_info = *blob_info;
	sh_css_stage_ग_लिखो_binary_info((काष्ठा ia_css_binary_info *)info);

	/* Make sure binary name is smaller than allowed string size */
	निश्चित(म_माप(binary_name) < SH_CSS_MAX_BINARY_NAME - 1);
	strscpy(sh_css_isp_stage.binary_name, binary_name, SH_CSS_MAX_BINARY_NAME);
	sh_css_isp_stage.mem_initializers = *isp_mem_अगर;

	/*
	 * Even when a stage करोes not need uds and करोes not params,
	 * ia_css_uds_sp_scale_params() seems to be called (needs
	 * further investigation). This function can not deal with
	 * dx, dy = अणु0, 0पूर्ण
	 */

	err = sh_css_sp_ग_लिखो_frame_poपूर्णांकers(args);
	/* TODO: move it to a better place */
	अगर (binary->info->sp.enable.s3a)
	अणु
		ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_3A_STATISTICS, thपढ़ो_id,
					       &queue_id);
		sh_css_copy_buffer_attr_to_spbuffer(&sh_css_sp_stage.frames.s3a_buf, queue_id,
						    mmgr_EXCEPTION,
						    IA_CSS_BUFFER_TYPE_3A_STATISTICS);
	पूर्ण
	अगर (binary->info->sp.enable.dis)
	अणु
		ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_DIS_STATISTICS, thपढ़ो_id,
					       &queue_id);
		sh_css_copy_buffer_attr_to_spbuffer(&sh_css_sp_stage.frames.dvs_buf, queue_id,
						    mmgr_EXCEPTION,
						    IA_CSS_BUFFER_TYPE_DIS_STATISTICS);
	पूर्ण
#अगर defined SH_CSS_ENABLE_METADATA
	ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_METADATA, thपढ़ो_id, &queue_id);
	sh_css_copy_buffer_attr_to_spbuffer(&sh_css_sp_stage.frames.metadata_buf, queue_id, mmgr_EXCEPTION, IA_CSS_BUFFER_TYPE_METADATA);
#पूर्ण_अगर
	अगर (err)
		वापस err;

#अगर_घोषित ISP2401
	अगर (stage == 0) अणु
		pipe = find_pipe_by_num(sh_css_sp_group.pipe[thपढ़ो_id].pipe_num);
		अगर (!pipe)
			वापस -EINVAL;

		अगर (args->in_frame)
			ia_css_get_crop_offsets(pipe, &args->in_frame->info);
		अन्यथा
			ia_css_get_crop_offsets(pipe, &binary->in_frame_info);
	पूर्ण
#अन्यथा
	(व्योम)pipe; /*aव्योम build warning*/
#पूर्ण_अगर

	err = configure_isp_from_args(&sh_css_sp_group.pipe[thपढ़ो_id],
				      binary, args, two_ppc, sh_css_sp_stage.deपूर्णांकerleaved);
	अगर (err)
		वापस err;

	initialize_isp_states(binary);

	/* we करो this only क्रम preview pipe because in fill_binary_info function
	 * we assign vf_out res to out res, but क्रम ISP पूर्णांकernal processing, we need
	 * the original out res. क्रम video pipe, it has two output pins --- out and
	 * vf_out, so it can keep these two resolutions alपढ़ोy. */
	अगर (binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_PREVIEW &&
	    (binary->vf_करोwnscale_log2 > 0))
	अणु
		/* TODO: Remove this after preview output decimation is fixed
		 * by configuring out&vf info fiels properly */
		sh_css_sp_stage.frames.out[0].info.padded_width
		<<= binary->vf_करोwnscale_log2;
		sh_css_sp_stage.frames.out[0].info.res.width
		<<= binary->vf_करोwnscale_log2;
		sh_css_sp_stage.frames.out[0].info.res.height
		<<= binary->vf_करोwnscale_log2;
	पूर्ण
	err = copy_isp_mem_अगर_to_ddr(binary);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
sp_init_stage(काष्ठा ia_css_pipeline_stage *stage,
	      अचिन्हित पूर्णांक pipe_num,
	      bool xnr,
	      अचिन्हित पूर्णांक अगर_config_index,
	      bool two_ppc) अणु
	काष्ठा ia_css_binary *binary;
	स्थिर काष्ठा ia_css_fw_info *firmware;
	स्थिर काष्ठा sh_css_binary_args *args;
	अचिन्हित पूर्णांक stage_num;
	/*
	 * Initialiser required because of the "else" path below.
	 * Is this a valid path ?
	 */
	स्थिर अक्षर *binary_name = "";
	स्थिर काष्ठा ia_css_binary_xinfo *info = शून्य;
	/* note: the var below is made अटल as it is quite large;
	   अगर it is not अटल it ends up on the stack which could
	   cause issues क्रम drivers
	*/
	अटल काष्ठा ia_css_binary पंचांगp_binary;
	स्थिर काष्ठा ia_css_blob_info *blob_info = शून्य;
	काष्ठा ia_css_isp_param_css_segments isp_mem_अगर;
	/* LA: should be ia_css_data, should not contain host poपूर्णांकer.
	   However, CSS/DDR poपूर्णांकer is not available yet.
	   Hack is to store it in params->ddr_ptrs and then copy it late in the SP just beक्रमe vmem init.
	   TODO: Call this after CSS/DDR allocation and store that poपूर्णांकer.
	   Best is to allocate it at stage creation समय together with host poपूर्णांकer.
	   Remove vmem from params.
	*/
	काष्ठा ia_css_isp_param_css_segments *mem_अगर = &isp_mem_अगर;

	पूर्णांक err = 0;

	निश्चित(stage);

	binary = stage->binary;
	firmware = stage->firmware;
	args = &stage->args;
	stage_num = stage->stage_num;

	अगर (binary)
	अणु
		info = binary->info;
		binary_name = (स्थिर अक्षर *)(info->blob->name);
		blob_info = &info->blob->header.blob;
		ia_css_init_memory_पूर्णांकerface(mem_अगर, &binary->mem_params, &binary->css_params);
	पूर्ण अन्यथा अगर (firmware)
	अणु
		स्थिर काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS] = अणुशून्यपूर्ण;

		अगर (args->out_frame[0])
			out_infos[0] = &args->out_frame[0]->info;
		info = &firmware->info.isp;
		ia_css_binary_fill_info(info, false, false,
					ATOMISP_INPUT_FORMAT_RAW_10,
					args->in_frame  ? &args->in_frame->info  : शून्य,
					शून्य,
					out_infos,
					args->out_vf_frame ? &args->out_vf_frame->info
					: शून्य,
					&पंचांगp_binary,
					शून्य,
					-1, true);
		binary = &पंचांगp_binary;
		binary->info = info;
		binary_name = IA_CSS_EXT_ISP_PROG_NAME(firmware);
		blob_info = &firmware->blob;
		mem_अगर = (काष्ठा ia_css_isp_param_css_segments *)&firmware->mem_initializers;
	पूर्ण अन्यथा
	अणु
		/* SP stage */
		निश्चित(stage->sp_func != IA_CSS_PIPELINE_NO_FUNC);
		/* binary and blob_info are now शून्य.
		   These will be passed to sh_css_sp_init_stage
		   and dereferenced there, so passing a शून्य
		   poपूर्णांकer is no good. वापस an error */
		वापस -EINVAL;
	पूर्ण

	err = sh_css_sp_init_stage(binary,
				   (स्थिर अक्षर *)binary_name,
				   blob_info,
				   args,
				   pipe_num,
				   stage_num,
				   xnr,
				   mem_अगर,
				   अगर_config_index,
				   two_ppc);
	वापस err;
पूर्ण

अटल व्योम
sp_init_sp_stage(काष्ठा ia_css_pipeline_stage *stage,
		 अचिन्हित पूर्णांक pipe_num,
		 bool two_ppc,
		 क्रमागत sh_css_pipe_config_override copy_ovrd,
		 अचिन्हित पूर्णांक अगर_config_index)
अणु
	स्थिर काष्ठा sh_css_binary_args *args = &stage->args;

	निश्चित(stage);
	चयन (stage->sp_func) अणु
	हाल IA_CSS_PIPELINE_RAW_COPY:
		sh_css_sp_start_raw_copy(args->out_frame[0],
					 pipe_num, two_ppc,
					 stage->max_input_width,
					 copy_ovrd, अगर_config_index);
		अवरोध;
	हाल IA_CSS_PIPELINE_BIN_COPY:
		निश्चित(false); /* TBI */
		अवरोध;
	हाल IA_CSS_PIPELINE_ISYS_COPY:
		sh_css_sp_start_isys_copy(args->out_frame[0],
					  pipe_num, stage->max_input_width, अगर_config_index);
		अवरोध;
	हाल IA_CSS_PIPELINE_NO_FUNC:
		निश्चित(false);
		अवरोध;
	पूर्ण
पूर्ण

व्योम
sh_css_sp_init_pipeline(काष्ठा ia_css_pipeline *me,
			क्रमागत ia_css_pipe_id id,
			u8 pipe_num,
			bool xnr,
			bool two_ppc,
			bool continuous,
			bool offline,
			अचिन्हित पूर्णांक required_bds_factor,
			क्रमागत sh_css_pipe_config_override copy_ovrd,
			क्रमागत ia_css_input_mode input_mode,
			स्थिर काष्ठा ia_css_metadata_config *md_config,
			स्थिर काष्ठा ia_css_metadata_info *md_info,
			स्थिर क्रमागत mipi_port_id port_id,
			स्थिर काष्ठा ia_css_coordinate
			*पूर्णांकernal_frame_origin_bqs_on_sctbl, /* Origin of पूर्णांकernal frame
							positioned on shading table at shading correction in ISP. */
			स्थिर काष्ठा ia_css_isp_parameters *params
		       ) अणु
	/* Get first stage */
	काष्ठा ia_css_pipeline_stage *stage        = शून्य;
	काष्ठा ia_css_binary	     *first_binary = शून्य;
	काष्ठा ia_css_pipe *pipe = शून्य;
	अचिन्हित पूर्णांक num;

	क्रमागत ia_css_pipe_id pipe_id = id;
	अचिन्हित पूर्णांक thपढ़ो_id;
	u8 अगर_config_index, पंचांगp_अगर_config_index;

	निश्चित(me);

	निश्चित(me->stages);

	first_binary = me->stages->binary;

	अगर (input_mode == IA_CSS_INPUT_MODE_SENSOR ||
	    input_mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
	अणु
		निश्चित(port_id < N_MIPI_PORT_ID);
		अगर (port_id >= N_MIPI_PORT_ID) /* should not happen but KW करोes not know */
			वापस; /* we should be able to वापस an error */
		अगर_config_index  = (uपूर्णांक8_t)(port_id - MIPI_PORT0_ID);
	पूर्ण अन्यथा अगर (input_mode == IA_CSS_INPUT_MODE_MEMORY)
	अणु
		अगर_config_index = SH_CSS_IF_CONFIG_NOT_NEEDED;
	पूर्ण अन्यथा
	अणु
		अगर_config_index = 0x0;
	पूर्ण

	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	स_रखो(&sh_css_sp_group.pipe[thपढ़ो_id], 0, माप(काष्ठा sh_css_sp_pipeline));

	/* Count stages */
	क्रम (stage = me->stages, num = 0; stage; stage = stage->next, num++)
	अणु
		stage->stage_num = num;
		ia_css_debug_pipe_graph_dump_stage(stage, id);
	पूर्ण
	me->num_stages = num;

	अगर (first_binary)
	अणु
		/* Init pipeline data */
		sh_css_sp_init_group(two_ppc, first_binary->input_क्रमmat,
				     offline, अगर_config_index);
	पूर्ण /* अगर (first_binary != शून्य) */

	/* Signal the host immediately after start क्रम SP_ISYS_COPY only */
	अगर ((me->num_stages == 1) && me->stages &&
	    (me->stages->sp_func == IA_CSS_PIPELINE_ISYS_COPY))
		sh_css_sp_group.config.no_isp_sync = true;

	/* Init stage data */
	sh_css_init_host2sp_frame_data();

	sh_css_sp_group.pipe[thपढ़ो_id].num_stages = 0;
	sh_css_sp_group.pipe[thपढ़ो_id].pipe_id = pipe_id;
	sh_css_sp_group.pipe[thपढ़ो_id].thपढ़ो_id = thपढ़ो_id;
	sh_css_sp_group.pipe[thपढ़ो_id].pipe_num = pipe_num;
	sh_css_sp_group.pipe[thपढ़ो_id].num_execs = me->num_execs;
	sh_css_sp_group.pipe[thपढ़ो_id].pipe_qos_config = me->pipe_qos_config;
	sh_css_sp_group.pipe[thपढ़ो_id].required_bds_factor = required_bds_factor;
	sh_css_sp_group.pipe[thपढ़ो_id].input_प्रणाली_mode
	= (uपूर्णांक32_t)input_mode;
	sh_css_sp_group.pipe[thपढ़ो_id].port_id = port_id;
	sh_css_sp_group.pipe[thपढ़ो_id].dvs_frame_delay = (uपूर्णांक32_t)me->dvs_frame_delay;

	/* TODO: next indicates from which queues parameters need to be
		 sampled, needs checking/improvement */
	अगर (ia_css_pipeline_uses_params(me))
	अणु
		sh_css_sp_group.pipe[thपढ़ो_id].pipe_config =
		SH_CSS_PIPE_CONFIG_SAMPLE_PARAMS << thपढ़ो_id;
	पूर्ण

	/* For continuous use-हालs, SP copy is responsible क्रम sampling the
	 * parameters */
	अगर (continuous)
		sh_css_sp_group.pipe[thपढ़ो_id].pipe_config = 0;

	sh_css_sp_group.pipe[thपढ़ो_id].inout_port_config = me->inout_port_config;

	pipe = find_pipe_by_num(pipe_num);
	निश्चित(pipe);
	अगर (!pipe)
	अणु
		वापस;
	पूर्ण
	sh_css_sp_group.pipe[thपढ़ो_id].scaler_pp_lut = sh_css_pipe_get_pp_gdc_lut(pipe);

#अगर defined(SH_CSS_ENABLE_METADATA)
	अगर (md_info && md_info->size > 0)
	अणु
		sh_css_sp_group.pipe[thपढ़ो_id].metadata.width  = md_info->resolution.width;
		sh_css_sp_group.pipe[thपढ़ो_id].metadata.height = md_info->resolution.height;
		sh_css_sp_group.pipe[thपढ़ो_id].metadata.stride = md_info->stride;
		sh_css_sp_group.pipe[thपढ़ो_id].metadata.size   = md_info->size;
		ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(
		    md_config->data_type, MIPI_PREDICTOR_NONE,
		    &sh_css_sp_group.pipe[thपढ़ो_id].metadata.क्रमmat);
	पूर्ण
#अन्यथा
	(व्योम)md_config;
	(व्योम)md_info;
#पूर्ण_अगर

#अगर defined(SH_CSS_ENABLE_PER_FRAME_PARAMS)
	sh_css_sp_group.pipe[thपढ़ो_id].output_frame_queue_id = (uपूर्णांक32_t)SH_CSS_INVALID_QUEUE_ID;
	अगर (pipe_id != IA_CSS_PIPE_ID_COPY)
	अणु
		ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, thपढ़ो_id,
					       (क्रमागत sh_css_queue_id *)(
						   &sh_css_sp_group.pipe[thपढ़ो_id].output_frame_queue_id));
	पूर्ण
#पूर्ण_अगर

	अगर (IS_ISP2401) अणु
		/* For the shading correction type 1 (the legacy shading table conversion in css is not used),
		* the parameters are passed to the isp क्रम the shading table centering.
		*/
		अगर (पूर्णांकernal_frame_origin_bqs_on_sctbl &&
		    params && params->shading_settings.enable_shading_table_conversion == 0)
		अणु
			sh_css_sp_group.pipe[thपढ़ो_id].shading.पूर्णांकernal_frame_origin_x_bqs_on_sctbl
			= (uपूर्णांक32_t)पूर्णांकernal_frame_origin_bqs_on_sctbl->x;
			sh_css_sp_group.pipe[thपढ़ो_id].shading.पूर्णांकernal_frame_origin_y_bqs_on_sctbl
			= (uपूर्णांक32_t)पूर्णांकernal_frame_origin_bqs_on_sctbl->y;
		पूर्ण अन्यथा
		अणु
			sh_css_sp_group.pipe[thपढ़ो_id].shading.पूर्णांकernal_frame_origin_x_bqs_on_sctbl =
			0;
			sh_css_sp_group.pipe[thपढ़ो_id].shading.पूर्णांकernal_frame_origin_y_bqs_on_sctbl =
			0;
		पूर्ण
	पूर्ण

	IA_CSS_LOG("pipe_id %d port_config %08x",
		   pipe_id, sh_css_sp_group.pipe[thपढ़ो_id].inout_port_config);

	क्रम (stage = me->stages, num = 0; stage; stage = stage->next, num++)
	अणु
		sh_css_sp_group.pipe[thपढ़ो_id].num_stages++;
		अगर (is_sp_stage(stage)) अणु
			sp_init_sp_stage(stage, pipe_num, two_ppc,
					 copy_ovrd, अगर_config_index);
		पूर्ण अन्यथा अणु
			अगर ((stage->stage_num != 0) ||
			    SH_CSS_PIPE_PORT_CONFIG_IS_CONTINUOUS(me->inout_port_config))
				पंचांगp_अगर_config_index = SH_CSS_IF_CONFIG_NOT_NEEDED;
			अन्यथा
				पंचांगp_अगर_config_index = अगर_config_index;
			sp_init_stage(stage, pipe_num,
				      xnr, पंचांगp_अगर_config_index, two_ppc);
		पूर्ण

		store_sp_stage_data(pipe_id, pipe_num, num);
	पूर्ण
	sh_css_sp_group.pipe[thपढ़ो_id].pipe_config |= (uपूर्णांक32_t)
		(me->acquire_isp_each_stage << IA_CSS_ACQUIRE_ISP_POS);
	store_sp_group_data();
पूर्ण

व्योम
sh_css_sp_uninit_pipeline(अचिन्हित पूर्णांक pipe_num)
अणु
	अचिन्हित पूर्णांक thपढ़ो_id;

	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);
	/*स_रखो(&sh_css_sp_group.pipe[thपढ़ो_id], 0, माप(काष्ठा sh_css_sp_pipeline));*/
	sh_css_sp_group.pipe[thपढ़ो_id].num_stages = 0;
पूर्ण

bool sh_css_ग_लिखो_host2sp_command(क्रमागत host2sp_commands host2sp_command)
अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	अचिन्हित पूर्णांक offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
			      host2sp_command)
			      / माप(पूर्णांक);
	क्रमागत host2sp_commands last_cmd = host2sp_cmd_error;
	(व्योम)HIVE_ADDR_host_sp_com; /* Suppres warnings in CRUN */

	/* Previous command must be handled by SP (by design) */
	last_cmd = load_sp_array_uपूर्णांक(host_sp_com, offset);
	अगर (last_cmd != host2sp_cmd_पढ़ोy)
		IA_CSS_ERROR("last host command not handled by SP(%d)", last_cmd);

	store_sp_array_uपूर्णांक(host_sp_com, offset, host2sp_command);

	वापस (last_cmd == host2sp_cmd_पढ़ोy);
पूर्ण

क्रमागत host2sp_commands
sh_css_पढ़ो_host2sp_command(व्योम) अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	अचिन्हित पूर्णांक offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication, host2sp_command)
	/ माप(पूर्णांक);
	(व्योम)HIVE_ADDR_host_sp_com; /* Suppres warnings in CRUN */
	वापस (क्रमागत host2sp_commands)load_sp_array_uपूर्णांक(host_sp_com, offset);
पूर्ण

/*
 * Frame data is no दीर्घer part of the sp_stage काष्ठाure but part of a
 * separate काष्ठाure. The aim is to make the sp_data काष्ठा अटल
 * (it defines a pipeline) and that the dynamic (per frame) data is stored
 * separetly.
 *
 * This function must be called first every where were you start स्थिरructing
 * a new pipeline by defining one or more stages with use of variable
 * sh_css_sp_stage. Even the special हालs like accelerator and copy_frame
 * These have a pipeline of just 1 stage.
 */
व्योम
sh_css_init_host2sp_frame_data(व्योम)
अणु
	/* Clean table */
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;

	(व्योम)HIVE_ADDR_host_sp_com; /* Suppres warnings in CRUN */
	/*
	 * rvanimme: करोn't clean it to save अटल frame info line ref_in
	 * ref_out, and tnr_frames. Once this अटल data is in a
	 * separate data काष्ठा, this may be enable (but still, there is
	 * no need क्रम it)
	 */
पूर्ण

/*
 * @brief Update the offline frame inक्रमmation in host_sp_communication.
 * Refer to "sh_css_sp.h" क्रम more details.
 */
व्योम
sh_css_update_host2sp_offline_frame(
    अचिन्हित पूर्णांक frame_num,
    काष्ठा ia_css_frame *frame,
    काष्ठा ia_css_metadata *metadata)
अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com;
	अचिन्हित पूर्णांक offset;

	निश्चित(frame_num < NUM_CONTINUOUS_FRAMES);

	/* Write new frame data पूर्णांकo SP DMEM */
	HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
					host2sp_offline_frames)
		 / माप(पूर्णांक);
	offset += frame_num;
	store_sp_array_uपूर्णांक(host_sp_com, offset, frame ? frame->data : 0);

	/* Write metadata buffer पूर्णांकo SP DMEM */
	offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
					host2sp_offline_metadata)
		 / माप(पूर्णांक);
	offset += frame_num;
	store_sp_array_uपूर्णांक(host_sp_com, offset, metadata ? metadata->address : 0);
पूर्ण

/*
 * @brief Update the mipi frame inक्रमmation in host_sp_communication.
 * Refer to "sh_css_sp.h" क्रम more details.
 */
व्योम
sh_css_update_host2sp_mipi_frame(
    अचिन्हित पूर्णांक frame_num,
    काष्ठा ia_css_frame *frame)
अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com;
	अचिन्हित पूर्णांक offset;

	/* MIPI buffers are dedicated to port, so now there are more of them. */
	निश्चित(frame_num < (N_CSI_PORTS * NUM_MIPI_FRAMES_PER_STREAM));

	/* Write new frame data पूर्णांकo SP DMEM */
	HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
					host2sp_mipi_frames)
		 / माप(पूर्णांक);
	offset += frame_num;

	store_sp_array_uपूर्णांक(host_sp_com, offset,
			    frame ? frame->data : 0);
पूर्ण

/*
 * @brief Update the mipi metadata inक्रमmation in host_sp_communication.
 * Refer to "sh_css_sp.h" क्रम more details.
 */
व्योम
sh_css_update_host2sp_mipi_metadata(
    अचिन्हित पूर्णांक frame_num,
    काष्ठा ia_css_metadata *metadata)
अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com;
	अचिन्हित पूर्णांक o;

	/* MIPI buffers are dedicated to port, so now there are more of them. */
	निश्चित(frame_num < (N_CSI_PORTS * NUM_MIPI_FRAMES_PER_STREAM));

	/* Write new frame data पूर्णांकo SP DMEM */
	HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	o = दुरत्व(काष्ठा host_sp_communication, host2sp_mipi_metadata)
	    / माप(पूर्णांक);
	o += frame_num;
	store_sp_array_uपूर्णांक(host_sp_com, o,
			    metadata ? metadata->address : 0);
पूर्ण

व्योम
sh_css_update_host2sp_num_mipi_frames(अचिन्हित पूर्णांक num_frames)
अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com;
	अचिन्हित पूर्णांक offset;

	/* Write new frame data पूर्णांकo SP DMEM */
	HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
					host2sp_num_mipi_frames)
		 / माप(पूर्णांक);

	store_sp_array_uपूर्णांक(host_sp_com, offset, num_frames);
पूर्ण

व्योम
sh_css_update_host2sp_cont_num_raw_frames(अचिन्हित पूर्णांक num_frames,
	bool set_avail)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com;
	अचिन्हित पूर्णांक extra_num_frames, avail_num_frames;
	अचिन्हित पूर्णांक offset, offset_extra;

	/* Write new frame data पूर्णांकo SP DMEM */
	fw = &sh_css_sp_fw;
	HIVE_ADDR_host_sp_com = fw->info.sp.host_sp_com;
	अगर (set_avail) अणु
		offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
						host2sp_cont_avail_num_raw_frames)
			 / माप(पूर्णांक);
		avail_num_frames = load_sp_array_uपूर्णांक(host_sp_com, offset);
		extra_num_frames = num_frames - avail_num_frames;
		offset_extra = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
						      host2sp_cont_extra_num_raw_frames)
			       / माप(पूर्णांक);
		store_sp_array_uपूर्णांक(host_sp_com, offset_extra, extra_num_frames);
	पूर्ण अन्यथा
		offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
						host2sp_cont_target_num_raw_frames)
			 / माप(पूर्णांक);

	store_sp_array_uपूर्णांक(host_sp_com, offset, num_frames);
पूर्ण

व्योम
sh_css_event_init_irq_mask(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	अचिन्हित पूर्णांक offset;
	काष्ठा sh_css_event_irq_mask event_irq_mask_init;

	event_irq_mask_init.or_mask  = IA_CSS_EVENT_TYPE_ALL;
	event_irq_mask_init.and_mask = IA_CSS_EVENT_TYPE_NONE;
	(व्योम)HIVE_ADDR_host_sp_com; /* Suppress warnings in CRUN */

	निश्चित(माप(event_irq_mask_init) % HRT_BUS_BYTES == 0);
	क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++) अणु
		offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
						host2sp_event_irq_mask[i]);
		निश्चित(offset % HRT_BUS_BYTES == 0);
		sp_dmem_store(SP0_ID,
			      (अचिन्हित पूर्णांक)sp_address_of(host_sp_com) + offset,
			      &event_irq_mask_init, माप(event_irq_mask_init));
	पूर्ण
पूर्ण

पूर्णांक
ia_css_pipe_set_irq_mask(काष्ठा ia_css_pipe *pipe,
			 अचिन्हित पूर्णांक or_mask,
			 अचिन्हित पूर्णांक and_mask) अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	अचिन्हित पूर्णांक offset;
	काष्ठा sh_css_event_irq_mask event_irq_mask;
	अचिन्हित पूर्णांक pipe_num;

	निश्चित(pipe);

	निश्चित(IA_CSS_PIPE_ID_NUM == NR_OF_PIPELINES);
	/* Linux kernel करोes not have UINT16_MAX
	 * Thereक्रमe decided to comment out these 2 निश्चितs क्रम Linux
	 * Alternatives that were not chosen:
	 * - add a conditional #घोषणा क्रम UINT16_MAX
	 * - compare with (uपूर्णांक16_t)~0 or 0xffff
	 * - dअगरferent निश्चित क्रम Linux and Winकरोws
	 */

	(व्योम)HIVE_ADDR_host_sp_com; /* Suppres warnings in CRUN */

	IA_CSS_LOG("or_mask=%x, and_mask=%x", or_mask, and_mask);
	event_irq_mask.or_mask  = (uपूर्णांक16_t)or_mask;
	event_irq_mask.and_mask = (uपूर्णांक16_t)and_mask;

	pipe_num = ia_css_pipe_get_pipe_num(pipe);
	अगर (pipe_num >= IA_CSS_PIPE_ID_NUM)
		वापस -EINVAL;
	offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
					host2sp_event_irq_mask[pipe_num]);
	निश्चित(offset % HRT_BUS_BYTES == 0);
	sp_dmem_store(SP0_ID,
		      (अचिन्हित पूर्णांक)sp_address_of(host_sp_com) + offset,
		      &event_irq_mask, माप(event_irq_mask));

	वापस 0;
पूर्ण

पूर्णांक
ia_css_event_get_irq_mask(स्थिर काष्ठा ia_css_pipe *pipe,
			  अचिन्हित पूर्णांक *or_mask,
			  अचिन्हित पूर्णांक *and_mask) अणु
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	अचिन्हित पूर्णांक offset;
	काष्ठा sh_css_event_irq_mask event_irq_mask;
	अचिन्हित पूर्णांक pipe_num;

	(व्योम)HIVE_ADDR_host_sp_com; /* Suppres warnings in CRUN */

	IA_CSS_ENTER_LEAVE("");

	निश्चित(pipe);
	निश्चित(IA_CSS_PIPE_ID_NUM == NR_OF_PIPELINES);

	pipe_num = ia_css_pipe_get_pipe_num(pipe);
	अगर (pipe_num >= IA_CSS_PIPE_ID_NUM)
		वापस -EINVAL;
	offset = (अचिन्हित पूर्णांक)दुरत्व(काष्ठा host_sp_communication,
					host2sp_event_irq_mask[pipe_num]);
	निश्चित(offset % HRT_BUS_BYTES == 0);
	sp_dmem_load(SP0_ID,
		     (अचिन्हित पूर्णांक)sp_address_of(host_sp_com) + offset,
		     &event_irq_mask, माप(event_irq_mask));

	अगर (or_mask)
		*or_mask = event_irq_mask.or_mask;

	अगर (and_mask)
		*and_mask = event_irq_mask.and_mask;

	वापस 0;
पूर्ण

व्योम
sh_css_sp_set_sp_running(bool flag)
अणु
	sp_running = flag;
पूर्ण

bool
sh_css_sp_is_running(व्योम)
अणु
	वापस sp_running;
पूर्ण

व्योम
sh_css_sp_start_isp(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_sw_state;

	fw = &sh_css_sp_fw;
	HIVE_ADDR_sp_sw_state = fw->info.sp.sw_state;

	अगर (sp_running)
		वापस;

	(व्योम)HIVE_ADDR_sp_sw_state; /* Suppres warnings in CRUN */

	/* no दीर्घer here, sp started immediately */
	/*ia_css_debug_pipe_graph_dump_epilogue();*/

	store_sp_group_data();
	store_sp_per_frame_data(fw);

	sp_dmem_store_uपूर्णांक32(SP0_ID,
			     (अचिन्हित पूर्णांक)sp_address_of(sp_sw_state),
			     (uपूर्णांक32_t)(IA_CSS_SP_SW_TERMINATED));

	/* Note 1: The sp_start_isp function contains a रुको till
	 * the input network is configured by the SP.
	 * Note 2: Not all SP binaries supports host2sp_commands.
	 * In हाल a binary करोes support it, the host2sp_command
	 * will have status cmd_पढ़ोy after वापस of the function
	 * sh_css_hrt_sp_start_isp. There is no race-condition here
	 * because only after the process_frame command has been
	 * received, the SP starts configuring the input network.
	 */

	/* we need to set sp_running beक्रमe we call ia_css_mmu_invalidate_cache
	 * as ia_css_mmu_invalidate_cache checks on sp_running to
	 * aव्योम that it accesses dmem जबतक the SP is not घातered
	 */
	sp_running = true;
	ia_css_mmu_invalidate_cache();
	/* Invalidate all MMU caches */
	mmu_invalidate_cache_all();

	ia_css_spctrl_start(SP0_ID);
पूर्ण

bool
ia_css_isp_has_started(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw = &sh_css_sp_fw;
	अचिन्हित पूर्णांक HIVE_ADDR_ia_css_ispctrl_sp_isp_started = fw->info.sp.isp_started;
	(व्योम)HIVE_ADDR_ia_css_ispctrl_sp_isp_started; /* Suppres warnings in CRUN */

	वापस (bool)load_sp_uपूर्णांक(ia_css_ispctrl_sp_isp_started);
पूर्ण

/*
 * @brief Initialize the DMA software-mask in the debug mode.
 * Refer to "sh_css_sp.h" क्रम more details.
 */
bool
sh_css_sp_init_dma_sw_reg(पूर्णांक dma_id)
अणु
	पूर्णांक i;

	/* enable all the DMA channels */
	क्रम (i = 0; i < N_DMA_CHANNEL_ID; i++) अणु
		/* enable the writing request */
		sh_css_sp_set_dma_sw_reg(dma_id,
					 i,
					 0,
					 true);
		/* enable the पढ़ोing request */
		sh_css_sp_set_dma_sw_reg(dma_id,
					 i,
					 1,
					 true);
	पूर्ण

	वापस true;
पूर्ण

/*
 * @brief Set the DMA software-mask in the debug mode.
 * Refer to "sh_css_sp.h" क्रम more details.
 */
bool
sh_css_sp_set_dma_sw_reg(पूर्णांक dma_id,
			 पूर्णांक channel_id,
			 पूर्णांक request_type,
			 bool enable)
अणु
	u32 sw_reg;
	u32 bit_val;
	u32 bit_offset;
	u32 bit_mask;

	(व्योम)dma_id;

	निश्चित(channel_id >= 0 && channel_id < N_DMA_CHANNEL_ID);
	निश्चित(request_type >= 0);

	/* get the software-mask */
	sw_reg =
	    sh_css_sp_group.debug.dma_sw_reg;

	/* get the offest of the target bit */
	bit_offset = (8 * request_type) + channel_id;

	/* clear the value of the target bit */
	bit_mask = ~(1 << bit_offset);
	sw_reg &= bit_mask;

	/* set the value of the bit क्रम the DMA channel */
	bit_val = enable ? 1 : 0;
	bit_val <<= bit_offset;
	sw_reg |= bit_val;

	/* update the software status of DMA channels */
	sh_css_sp_group.debug.dma_sw_reg = sw_reg;

	वापस true;
पूर्ण

व्योम
sh_css_sp_reset_global_vars(व्योम)
अणु
	स_रखो(&sh_css_sp_group, 0, माप(काष्ठा sh_css_sp_group));
	स_रखो(&sh_css_sp_stage, 0, माप(काष्ठा sh_css_sp_stage));
	स_रखो(&sh_css_isp_stage, 0, माप(काष्ठा sh_css_isp_stage));
	स_रखो(&sh_css_sp_output, 0, माप(काष्ठा sh_css_sp_output));
	स_रखो(&per_frame_data, 0, माप(काष्ठा sh_css_sp_per_frame_data));
पूर्ण
