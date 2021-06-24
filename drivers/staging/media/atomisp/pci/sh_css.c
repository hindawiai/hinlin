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

/*! \पile */
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "hmm.h"

#समावेश "ia_css.h"
#समावेश "sh_css_hrt.h"		/* only क्रम file 2 MIPI */
#समावेश "ia_css_buffer.h"
#समावेश "ia_css_binary.h"
#समावेश "sh_css_internal.h"
#समावेश "sh_css_mipi.h"
#समावेश "sh_css_sp.h"		/* sh_css_sp_group */
#समावेश "ia_css_isys.h"
#समावेश "ia_css_frame.h"
#समावेश "sh_css_defs.h"
#समावेश "sh_css_firmware.h"
#समावेश "sh_css_params.h"
#समावेश "sh_css_params_internal.h"
#समावेश "sh_css_param_shading.h"
#समावेश "ia_css_refcount.h"
#समावेश "ia_css_rmgr.h"
#समावेश "ia_css_debug.h"
#समावेश "ia_css_debug_pipe.h"
#समावेश "ia_css_device_access.h"
#समावेश "device_access.h"
#समावेश "sh_css_legacy.h"
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_stream.h"
#समावेश "sh_css_stream_format.h"
#समावेश "ia_css_pipe.h"
#समावेश "ia_css_util.h"
#समावेश "ia_css_pipe_util.h"
#समावेश "ia_css_pipe_binarydesc.h"
#समावेश "ia_css_pipe_stagedesc.h"

#समावेश "tag.h"
#समावेश "assert_support.h"
#समावेश "math_support.h"
#समावेश "sw_event_global.h"			/* Event IDs.*/
#अगर !defined(ISP2401)
#समावेश "ia_css_ifmtr.h"
#पूर्ण_अगर
#समावेश "input_system.h"
#समावेश "mmu_device.h"		/* mmu_set_page_table_base_index(), ... */
#समावेश "ia_css_mmu_private.h" /* sh_css_mmu_set_page_table_base_index() */
#समावेश "gdc_device.h"		/* HRT_GDC_N */
#समावेश "dma.h"		/* dma_set_max_burst_size() */
#समावेश "irq.h"			/* virq */
#समावेश "sp.h"				/* cnd_sp_irq_enable() */
#समावेश "isp.h"			/* cnd_isp_irq_enable, ISP_VEC_NELEMS */
#समावेश "gp_device.h"		/* gp_device_reg_store() */
#घोषणा __INLINE_GPIO__
#समावेश "gpio.h"
#समावेश "timed_ctrl.h"
#समावेश "ia_css_inputfifo.h"
#घोषणा WITH_PC_MONITORING  0

#घोषणा SH_CSS_VIDEO_BUFFER_ALIGNMENT 0

#अगर WITH_PC_MONITORING
#घोषणा MULTIPLE_SAMPLES 1
#घोषणा NOF_SAMPLES      60
#समावेश "linux/kthread.h"
#समावेश "linux/sched.h"
#समावेश "linux/delay.h"
#समावेश "sh_css_metrics.h"
अटल पूर्णांक thपढ़ो_alive;
#पूर्ण_अगर /* WITH_PC_MONITORING */

#समावेश "ia_css_spctrl.h"
#समावेश "ia_css_version_data.h"
#समावेश "sh_css_struct.h"
#समावेश "ia_css_bufq.h"
#समावेश "ia_css_timer.h" /* घड़ी_value_t */

#समावेश "isp/modes/interface/input_buf.isp.h"

/* Name of the sp program: should not be built-in */
#घोषणा SP_PROG_NAME "sp"
/* Size of Refcount List */
#घोषणा REFCOUNT_SIZE 1000

/* क्रम JPEG, we करोn't know the length of the image upfront,
 * but since we support sensor upto 16MP, we take this as
 * upper limit.
 */
#घोषणा JPEG_BYTES (16 * 1024 * 1024)

#घोषणा STATS_ENABLED(stage) (stage && stage->binary && stage->binary->info && \
	(stage->binary->info->sp.enable.s3a || stage->binary->info->sp.enable.dis))

काष्ठा sh_css my_css;

पूर्णांक  __म_लिखो(1, 0) (*sh_css_म_लिखो)(स्थिर अक्षर *fmt, बहु_सूची args) = शून्य;

/* modes of work: stream_create and stream_destroy will update the save/restore data
   only when in working mode, not suspend/resume
*/
क्रमागत ia_sh_css_modes अणु
	sh_css_mode_none = 0,
	sh_css_mode_working,
	sh_css_mode_suspend,
	sh_css_mode_resume
पूर्ण;

/* a stream seed, to save and restore the stream data.
   the stream seed contains all the data required to "grow" the seed again after it was बंदd.
*/
काष्ठा sh_css_stream_seed अणु
	काष्ठा ia_css_stream
		**orig_stream;                /* poपूर्णांकer to restore the original handle */
	काष्ठा ia_css_stream		*stream;                      /* handle, used as ID too.*/
	काष्ठा ia_css_stream_config	stream_config;				/* stream config काष्ठा */
	पूर्णांक				num_pipes;
	काष्ठा ia_css_pipe		*pipes[IA_CSS_PIPE_ID_NUM];			/* pipe handles */
	काष्ठा ia_css_pipe
		**orig_pipes[IA_CSS_PIPE_ID_NUM];	/* poपूर्णांकer to restore original handle */
	काष्ठा ia_css_pipe_config
		pipe_config[IA_CSS_PIPE_ID_NUM];	/* pipe config काष्ठाs */
पूर्ण;

#घोषणा MAX_ACTIVE_STREAMS	5
/* A global काष्ठा क्रम save/restore to hold all the data that should sustain घातer-करोwn:
   MMU base, IRQ type, env क्रम routines, binary loaded FW and the stream seeds.
*/
काष्ठा sh_css_save अणु
	क्रमागत ia_sh_css_modes		mode;
	u32		       mmu_base;				/* the last mmu_base */
	क्रमागत ia_css_irq_type           irq_type;
	काष्ठा sh_css_stream_seed      stream_seeds[MAX_ACTIVE_STREAMS];
	काष्ठा ia_css_fw	       *loaded_fw;				/* fw काष्ठा previously loaded */
	काष्ठा ia_css_env	       driver_env;				/* driver-supplied env copy */
पूर्ण;

अटल bool my_css_save_initialized;	/* अगर my_css_save was initialized */
अटल काष्ठा sh_css_save my_css_save;

/* pqiao NOTICE: this is क्रम css पूर्णांकernal buffer recycling when stopping pipeline,
   this array is temporary and will be replaced by resource manager*/
/* Taking the biggest Size क्रम number of Elements */
#घोषणा MAX_HMM_BUFFER_NUM	\
	(SH_CSS_MAX_NUM_QUEUES * (IA_CSS_NUM_ELEMS_SP2HOST_BUFFER_QUEUE + 2))

काष्ठा sh_css_hmm_buffer_record अणु
	bool in_use;
	क्रमागत ia_css_buffer_type type;
	काष्ठा ia_css_rmgr_vbuf_handle *h_vbuf;
	hrt_address kernel_ptr;
पूर्ण;

अटल काष्ठा sh_css_hmm_buffer_record hmm_buffer_record[MAX_HMM_BUFFER_NUM];

#घोषणा GPIO_FLASH_PIN_MASK BIT(HIVE_GPIO_STROBE_TRIGGER_PIN)

अटल bool fw_explicitly_loaded;

/*
 * Local prototypes
 */

अटल पूर्णांक
allocate_delay_frames(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
sh_css_pipe_start(काष्ठा ia_css_stream *stream);

/* ISP 2401 */
/*
 * @brief Stop all "ia_css_pipe" instances in the target
 * "ia_css_stream" instance.
 *
 * @param[in] stream	Poपूर्णांक to the target "ia_css_stream" instance.
 *
 * @वापस
 * - 0, अगर the "stop" requests have been successfully sent out.
 * - CSS error code, otherwise.
 *
 *
 * NOTE
 * This API sends the "stop" requests to the "ia_css_pipe"
 * instances in the same "ia_css_stream" instance. It will
 * वापस without रुकोing क्रम all "ia_css_pipe" instatnces
 * being stopped.
 */
अटल पूर्णांक
sh_css_pipes_stop(काष्ठा ia_css_stream *stream);

/*
 * @brief Check अगर all "ia_css_pipe" instances in the target
 * "ia_css_stream" instance have stopped.
 *
 * @param[in] stream	Poपूर्णांक to the target "ia_css_stream" instance.
 *
 * @वापस
 * - true, अगर all "ia_css_pipe" instances in the target "ia_css_stream"
 *   instance have ben stopped.
 * - false, otherwise.
 */
/* ISP 2401 */
अटल bool
sh_css_pipes_have_stopped(काष्ठा ia_css_stream *stream);

/* ISP 2401 */
अटल पूर्णांक
ia_css_pipe_check_क्रमmat(काष्ठा ia_css_pipe *pipe,
			 क्रमागत ia_css_frame_क्रमmat क्रमmat);

/* ISP 2401 */
अटल पूर्णांक
check_pipe_resolutions(स्थिर काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
ia_css_pipe_load_extension(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_fw_info *firmware);

अटल व्योम
ia_css_pipe_unload_extension(काष्ठा ia_css_pipe *pipe,
			     काष्ठा ia_css_fw_info *firmware);
अटल व्योम
ia_css_reset_शेषs(काष्ठा sh_css *css);

अटल व्योम
sh_css_init_host_sp_control_vars(व्योम);

अटल पूर्णांक set_num_primary_stages(अचिन्हित पूर्णांक *num,
	क्रमागत ia_css_pipe_version version);

अटल bool
need_capture_pp(स्थिर काष्ठा ia_css_pipe *pipe);

अटल bool
need_yuv_scaler_stage(स्थिर काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक ia_css_pipe_create_cas_scaler_desc_single_output(
    काष्ठा ia_css_frame_info *cas_scaler_in_info,
    काष्ठा ia_css_frame_info *cas_scaler_out_info,
    काष्ठा ia_css_frame_info *cas_scaler_vf_info,
    काष्ठा ia_css_cas_binary_descr *descr);

अटल व्योम ia_css_pipe_destroy_cas_scaler_desc(काष्ठा ia_css_cas_binary_descr
	*descr);

अटल bool
need_करोwnscaling(स्थिर काष्ठा ia_css_resolution in_res,
		 स्थिर काष्ठा ia_css_resolution out_res);

अटल bool need_capt_ldc(स्थिर काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
sh_css_pipe_load_binaries(काष्ठा ia_css_pipe *pipe);

अटल
पूर्णांक sh_css_pipe_get_viewfinder_frame_info(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_frame_info *info,
    अचिन्हित पूर्णांक idx);

अटल पूर्णांक
sh_css_pipe_get_output_frame_info(काष्ठा ia_css_pipe *pipe,
				  काष्ठा ia_css_frame_info *info,
				  अचिन्हित पूर्णांक idx);

अटल पूर्णांक
capture_start(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
video_start(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
preview_start(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
yuvpp_start(काष्ठा ia_css_pipe *pipe);

अटल bool copy_on_sp(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
init_vf_frameinfo_शेषs(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_frame *vf_frame, अचिन्हित पूर्णांक idx);

अटल पूर्णांक
init_in_frameinfo_memory_शेषs(काष्ठा ia_css_pipe *pipe,
				  काष्ठा ia_css_frame *frame, क्रमागत ia_css_frame_क्रमmat क्रमmat);

अटल पूर्णांक
init_out_frameinfo_शेषs(काष्ठा ia_css_pipe *pipe,
			    काष्ठा ia_css_frame *out_frame, अचिन्हित पूर्णांक idx);

अटल पूर्णांक
sh_css_pipeline_add_acc_stage(काष्ठा ia_css_pipeline *pipeline,
			      स्थिर व्योम *acc_fw);

अटल पूर्णांक
alloc_continuous_frames(
    काष्ठा ia_css_pipe *pipe, bool init_समय);

अटल व्योम
pipe_global_init(व्योम);

अटल पूर्णांक
pipe_generate_pipe_num(स्थिर काष्ठा ia_css_pipe *pipe,
		       अचिन्हित पूर्णांक *pipe_number);

अटल व्योम
pipe_release_pipe_num(अचिन्हित पूर्णांक pipe_num);

अटल पूर्णांक
create_host_pipeline_काष्ठाure(काष्ठा ia_css_stream *stream);

अटल पूर्णांक
create_host_pipeline(काष्ठा ia_css_stream *stream);

अटल पूर्णांक
create_host_preview_pipeline(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
create_host_video_pipeline(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
create_host_copy_pipeline(काष्ठा ia_css_pipe *pipe,
			  अचिन्हित पूर्णांक max_input_width,
			  काष्ठा ia_css_frame *out_frame);

अटल पूर्णांक
create_host_isyscopy_capture_pipeline(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
create_host_capture_pipeline(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
create_host_yuvpp_pipeline(काष्ठा ia_css_pipe *pipe);

अटल पूर्णांक
create_host_acc_pipeline(काष्ठा ia_css_pipe *pipe);

अटल अचिन्हित पूर्णांक
sh_css_get_sw_पूर्णांकerrupt_value(अचिन्हित पूर्णांक irq);

अटल काष्ठा ia_css_binary *ia_css_pipe_get_shading_correction_binary(
    स्थिर काष्ठा ia_css_pipe *pipe);

अटल काष्ठा ia_css_binary *
ia_css_pipe_get_s3a_binary(स्थिर काष्ठा ia_css_pipe *pipe);

अटल काष्ठा ia_css_binary *
ia_css_pipe_get_sdis_binary(स्थिर काष्ठा ia_css_pipe *pipe);

अटल व्योम
sh_css_hmm_buffer_record_init(व्योम);

अटल व्योम
sh_css_hmm_buffer_record_uninit(व्योम);

अटल व्योम
sh_css_hmm_buffer_record_reset(काष्ठा sh_css_hmm_buffer_record *buffer_record);

अटल काष्ठा sh_css_hmm_buffer_record
*sh_css_hmm_buffer_record_acquire(काष्ठा ia_css_rmgr_vbuf_handle *h_vbuf,
				  क्रमागत ia_css_buffer_type type,
				  hrt_address kernel_ptr);

अटल काष्ठा sh_css_hmm_buffer_record
*sh_css_hmm_buffer_record_validate(ia_css_ptr ddr_buffer_addr,
				   क्रमागत ia_css_buffer_type type);

व्योम
ia_css_get_acc_configs(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_isp_config *config);

#अगर CONFIG_ON_FRAME_ENQUEUE()
अटल पूर्णांक set_config_on_frame_enqueue(काष्ठा ia_css_frame_info
	*info, काष्ठा frame_data_wrapper *frame);
#पूर्ण_अगर

#अगर_घोषित ISP2401
अटल अचिन्हित पूर्णांक get_crop_lines_क्रम_bayer_order(स्थिर काष्ठा
	ia_css_stream_config *config);
अटल अचिन्हित पूर्णांक get_crop_columns_क्रम_bayer_order(स्थिर काष्ठा
	ia_css_stream_config *config);
अटल व्योम get_pipe_extra_pixel(काष्ठा ia_css_pipe *pipe,
				 अचिन्हित पूर्णांक *extra_row, अचिन्हित पूर्णांक *extra_column);
अटल पूर्णांक
aspect_ratio_crop_init(काष्ठा ia_css_stream *curr_stream,
		       काष्ठा ia_css_pipe *pipes[],
		       bool *करो_crop_status);

अटल bool
aspect_ratio_crop_check(bool enabled, काष्ठा ia_css_pipe *curr_pipe);

अटल पूर्णांक
aspect_ratio_crop(काष्ठा ia_css_pipe *curr_pipe,
		  काष्ठा ia_css_resolution *effective_res);
#पूर्ण_अगर

अटल व्योम
sh_css_pipe_मुक्त_shading_table(काष्ठा ia_css_pipe *pipe)
अणु
	निश्चित(pipe);
	अगर (!pipe) अणु
		IA_CSS_ERROR("NULL input parameter");
		वापस;
	पूर्ण

	अगर (pipe->shading_table)
		ia_css_shading_table_मुक्त(pipe->shading_table);
	pipe->shading_table = शून्य;
पूर्ण

अटल क्रमागत ia_css_frame_क्रमmat yuv420_copy_क्रमmats[] = अणु
	IA_CSS_FRAME_FORMAT_NV12,
	IA_CSS_FRAME_FORMAT_NV21,
	IA_CSS_FRAME_FORMAT_YV12,
	IA_CSS_FRAME_FORMAT_YUV420,
	IA_CSS_FRAME_FORMAT_YUV420_16,
	IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8,
	IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8
पूर्ण;

अटल क्रमागत ia_css_frame_क्रमmat yuv422_copy_क्रमmats[] = अणु
	IA_CSS_FRAME_FORMAT_NV12,
	IA_CSS_FRAME_FORMAT_NV16,
	IA_CSS_FRAME_FORMAT_NV21,
	IA_CSS_FRAME_FORMAT_NV61,
	IA_CSS_FRAME_FORMAT_YV12,
	IA_CSS_FRAME_FORMAT_YV16,
	IA_CSS_FRAME_FORMAT_YUV420,
	IA_CSS_FRAME_FORMAT_YUV420_16,
	IA_CSS_FRAME_FORMAT_YUV422,
	IA_CSS_FRAME_FORMAT_YUV422_16,
	IA_CSS_FRAME_FORMAT_UYVY,
	IA_CSS_FRAME_FORMAT_YUYV
पूर्ण;

/* Verअगरy whether the selected output क्रमmat is can be produced
 * by the copy binary given the stream क्रमmat.
 * */
अटल पूर्णांक
verअगरy_copy_out_frame_क्रमmat(काष्ठा ia_css_pipe *pipe) अणु
	क्रमागत ia_css_frame_क्रमmat out_fmt = pipe->output_info[0].क्रमmat;
	अचिन्हित पूर्णांक i, found = 0;

	निश्चित(pipe);
	निश्चित(pipe->stream);

	चयन (pipe->stream->config.input_config.क्रमmat)
	अणु
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
		क्रम (i = 0; i < ARRAY_SIZE(yuv420_copy_क्रमmats) && !found; i++)
			found = (out_fmt == yuv420_copy_क्रमmats[i]);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
		found = (out_fmt == IA_CSS_FRAME_FORMAT_YUV420_16);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
		क्रम (i = 0; i < ARRAY_SIZE(yuv422_copy_क्रमmats) && !found; i++)
			found = (out_fmt == yuv422_copy_क्रमmats[i]);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		found = (out_fmt == IA_CSS_FRAME_FORMAT_YUV422_16 ||
			 out_fmt == IA_CSS_FRAME_FORMAT_YUV420_16);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
		found = (out_fmt == IA_CSS_FRAME_FORMAT_RGBA888 ||
			 out_fmt == IA_CSS_FRAME_FORMAT_RGB565);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
		found = (out_fmt == IA_CSS_FRAME_FORMAT_RGBA888 ||
			 out_fmt == IA_CSS_FRAME_FORMAT_YUV420);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
		found = (out_fmt == IA_CSS_FRAME_FORMAT_RAW) ||
		(out_fmt == IA_CSS_FRAME_FORMAT_RAW_PACKED);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
		found = (out_fmt == IA_CSS_FRAME_FORMAT_BINARY_8);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (!found)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक
ia_css_stream_input_क्रमmat_bits_per_pixel(काष्ठा ia_css_stream *stream)
अणु
	पूर्णांक bpp = 0;

	अगर (stream)
		bpp = ia_css_util_input_क्रमmat_bpp(stream->config.input_config.क्रमmat,
						   stream->config.pixels_per_घड़ी == 2);

	वापस bpp;
पूर्ण

#घोषणा GP_ISEL_TPG_MODE 0x90058

#अगर !defined(ISP2401)
अटल पूर्णांक
sh_css_config_input_network(काष्ठा ia_css_stream *stream) अणु
	अचिन्हित पूर्णांक fmt_type;
	काष्ठा ia_css_pipe *pipe = stream->last_pipe;
	काष्ठा ia_css_binary *binary = शून्य;
	पूर्णांक err = 0;

	निश्चित(stream);
	निश्चित(pipe);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_config_input_network() enter:\n");

	अगर (pipe->pipeline.stages)
		binary = pipe->pipeline.stages->binary;

	err = ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(
	    stream->config.input_config.क्रमmat,
	    stream->csi_rx_config.comp,
	    &fmt_type);
	अगर (err)
		वापस err;
	sh_css_sp_program_input_circuit(fmt_type,
					stream->config.channel_id,
					stream->config.mode);

	अगर ((binary && (binary->online || stream->config.continuous)) ||
	    pipe->config.mode == IA_CSS_PIPE_MODE_COPY)
	अणु
		err = ia_css_अगरmtr_configure(&stream->config,
					     binary);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (stream->config.mode == IA_CSS_INPUT_MODE_TPG ||
	    stream->config.mode == IA_CSS_INPUT_MODE_PRBS)
	अणु
		अचिन्हित पूर्णांक hblank_cycles = 100,
		vblank_lines = 6,
		width,
		height,
		vblank_cycles;
		width  = (stream->config.input_config.input_res.width) / (1 +
			(stream->config.pixels_per_घड़ी == 2));
		height = stream->config.input_config.input_res.height;
		vblank_cycles = vblank_lines * (width + hblank_cycles);
		sh_css_sp_configure_sync_gen(width, height, hblank_cycles,
					     vblank_cycles);
		अगर (!IS_ISP2401) अणु
			अगर (pipe->stream->config.mode == IA_CSS_INPUT_MODE_TPG) अणु
				/* TODO: move define to proper file in tools */
				ia_css_device_store_uपूर्णांक32(GP_ISEL_TPG_MODE, 0);
			पूर्ण
		पूर्ण
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_config_input_network() leave:\n");
	वापस 0;
पूर्ण
#या_अगर defined(ISP2401)
अटल अचिन्हित पूर्णांक csi2_protocol_calculate_max_subpixels_per_line(
    क्रमागत atomisp_input_क्रमmat	क्रमmat,
    अचिन्हित पूर्णांक			pixels_per_line)
अणु
	अचिन्हित पूर्णांक rval;

	चयन (क्रमmat) अणु
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
		/*
		 * The frame क्रमmat layout is shown below.
		 *
		 *		Line	0:	UYY0 UYY0 ... UYY0
		 *		Line	1:	VYY0 VYY0 ... VYY0
		 *		Line	2:	UYY0 UYY0 ... UYY0
		 *		Line	3:	VYY0 VYY0 ... VYY0
		 *		...
		 *		Line (n-2):	UYY0 UYY0 ... UYY0
		 *		Line (n-1):	VYY0 VYY0 ... VYY0
		 *
		 *	In this frame क्रमmat, the even-line is
		 *	as wide as the odd-line.
		 *	The 0 is पूर्णांकroduced by the input प्रणाली
		 *	(mipi backend).
		 */
		rval = pixels_per_line * 2;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
		/*
		 * The frame क्रमmat layout is shown below.
		 *
		 *		Line	0:	YYYY YYYY ... YYYY
		 *		Line	1:	UYVY UYVY ... UYVY UYVY
		 *		Line	2:	YYYY YYYY ... YYYY
		 *		Line	3:	UYVY UYVY ... UYVY UYVY
		 *		...
		 *		Line (n-2):	YYYY YYYY ... YYYY
		 *		Line (n-1):	UYVY UYVY ... UYVY UYVY
		 *
		 * In this frame क्रमmat, the odd-line is twice
		 * wider than the even-line.
		 */
		rval = pixels_per_line * 2;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		/*
		 * The frame क्रमmat layout is shown below.
		 *
		 *		Line	0:	UYVY UYVY ... UYVY
		 *		Line	1:	UYVY UYVY ... UYVY
		 *		Line	2:	UYVY UYVY ... UYVY
		 *		Line	3:	UYVY UYVY ... UYVY
		 *		...
		 *		Line (n-2):	UYVY UYVY ... UYVY
		 *		Line (n-1):	UYVY UYVY ... UYVY
		 *
		 * In this frame क्रमmat, the even-line is
		 * as wide as the odd-line.
		 */
		rval = pixels_per_line * 2;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
		/*
		 * The frame क्रमmat layout is shown below.
		 *
		 *		Line	0:	ABGR ABGR ... ABGR
		 *		Line	1:	ABGR ABGR ... ABGR
		 *		Line	2:	ABGR ABGR ... ABGR
		 *		Line	3:	ABGR ABGR ... ABGR
		 *		...
		 *		Line (n-2):	ABGR ABGR ... ABGR
		 *		Line (n-1):	ABGR ABGR ... ABGR
		 *
		 * In this frame क्रमmat, the even-line is
		 * as wide as the odd-line.
		 */
		rval = pixels_per_line * 4;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF1:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF2:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF3:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF4:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF5:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF6:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF7:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF8:
		/*
		 * The frame क्रमmat layout is shown below.
		 *
		 *		Line	0:	Pixel Pixel ... Pixel
		 *		Line	1:	Pixel Pixel ... Pixel
		 *		Line	2:	Pixel Pixel ... Pixel
		 *		Line	3:	Pixel Pixel ... Pixel
		 *		...
		 *		Line (n-2):	Pixel Pixel ... Pixel
		 *		Line (n-1):	Pixel Pixel ... Pixel
		 *
		 * In this frame क्रमmat, the even-line is
		 * as wide as the odd-line.
		 */
		rval = pixels_per_line;
		अवरोध;
	शेष:
		rval = 0;
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण

अटल bool sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_id(
    काष्ठा ia_css_stream_config *stream_cfg,
    ia_css_isys_descr_t	*isys_stream_descr)
अणु
	bool rc;

	rc = true;
	चयन (stream_cfg->mode) अणु
	हाल IA_CSS_INPUT_MODE_TPG:

		अगर (stream_cfg->source.tpg.id == IA_CSS_TPG_ID0) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_PIXELGEN_PORT0_ID;
		पूर्ण अन्यथा अगर (stream_cfg->source.tpg.id == IA_CSS_TPG_ID1) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_PIXELGEN_PORT1_ID;
		पूर्ण अन्यथा अगर (stream_cfg->source.tpg.id == IA_CSS_TPG_ID2) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_PIXELGEN_PORT2_ID;
		पूर्ण

		अवरोध;
	हाल IA_CSS_INPUT_MODE_PRBS:

		अगर (stream_cfg->source.prbs.id == IA_CSS_PRBS_ID0) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_PIXELGEN_PORT0_ID;
		पूर्ण अन्यथा अगर (stream_cfg->source.prbs.id == IA_CSS_PRBS_ID1) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_PIXELGEN_PORT1_ID;
		पूर्ण अन्यथा अगर (stream_cfg->source.prbs.id == IA_CSS_PRBS_ID2) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_PIXELGEN_PORT2_ID;
		पूर्ण

		अवरोध;
	हाल IA_CSS_INPUT_MODE_BUFFERED_SENSOR:

		अगर (stream_cfg->source.port.port == MIPI_PORT0_ID) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_CSI_PORT0_ID;
		पूर्ण अन्यथा अगर (stream_cfg->source.port.port == MIPI_PORT1_ID) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_CSI_PORT1_ID;
		पूर्ण अन्यथा अगर (stream_cfg->source.port.port == MIPI_PORT2_ID) अणु
			isys_stream_descr->input_port_id = INPUT_SYSTEM_CSI_PORT2_ID;
		पूर्ण

		अवरोध;
	शेष:
		rc = false;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_type(
    काष्ठा ia_css_stream_config *stream_cfg,
    ia_css_isys_descr_t	*isys_stream_descr)
अणु
	bool rc;

	rc = true;
	चयन (stream_cfg->mode) अणु
	हाल IA_CSS_INPUT_MODE_TPG:

		isys_stream_descr->mode = INPUT_SYSTEM_SOURCE_TYPE_TPG;

		अवरोध;
	हाल IA_CSS_INPUT_MODE_PRBS:

		isys_stream_descr->mode = INPUT_SYSTEM_SOURCE_TYPE_PRBS;

		अवरोध;
	हाल IA_CSS_INPUT_MODE_SENSOR:
	हाल IA_CSS_INPUT_MODE_BUFFERED_SENSOR:

		isys_stream_descr->mode = INPUT_SYSTEM_SOURCE_TYPE_SENSOR;
		अवरोध;

	शेष:
		rc = false;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_attr(
    काष्ठा ia_css_stream_config *stream_cfg,
    ia_css_isys_descr_t	*isys_stream_descr,
    पूर्णांक isys_stream_idx)
अणु
	bool rc;

	rc = true;
	चयन (stream_cfg->mode) अणु
	हाल IA_CSS_INPUT_MODE_TPG:
		अगर (stream_cfg->source.tpg.mode == IA_CSS_TPG_MODE_RAMP) अणु
			isys_stream_descr->tpg_port_attr.mode = PIXELGEN_TPG_MODE_RAMP;
		पूर्ण अन्यथा अगर (stream_cfg->source.tpg.mode == IA_CSS_TPG_MODE_CHECKERBOARD) अणु
			isys_stream_descr->tpg_port_attr.mode = PIXELGEN_TPG_MODE_CHBO;
		पूर्ण अन्यथा अगर (stream_cfg->source.tpg.mode == IA_CSS_TPG_MODE_MONO) अणु
			isys_stream_descr->tpg_port_attr.mode = PIXELGEN_TPG_MODE_MONO;
		पूर्ण अन्यथा अणु
			rc = false;
		पूर्ण

		/*
		 * TODO
		 * - Make "color_cfg" as part of "ia_css_tpg_config".
		 */
		isys_stream_descr->tpg_port_attr.color_cfg.R1 = 51;
		isys_stream_descr->tpg_port_attr.color_cfg.G1 = 102;
		isys_stream_descr->tpg_port_attr.color_cfg.B1 = 255;
		isys_stream_descr->tpg_port_attr.color_cfg.R2 = 0;
		isys_stream_descr->tpg_port_attr.color_cfg.G2 = 100;
		isys_stream_descr->tpg_port_attr.color_cfg.B2 = 160;

		isys_stream_descr->tpg_port_attr.mask_cfg.h_mask =
		    stream_cfg->source.tpg.x_mask;
		isys_stream_descr->tpg_port_attr.mask_cfg.v_mask =
		    stream_cfg->source.tpg.y_mask;
		isys_stream_descr->tpg_port_attr.mask_cfg.hv_mask =
		    stream_cfg->source.tpg.xy_mask;

		isys_stream_descr->tpg_port_attr.delta_cfg.h_delta =
		    stream_cfg->source.tpg.x_delta;
		isys_stream_descr->tpg_port_attr.delta_cfg.v_delta =
		    stream_cfg->source.tpg.y_delta;

		/*
		 * TODO
		 * - Make "sync_gen_cfg" as part of "ia_css_tpg_config".
		 */
		isys_stream_descr->tpg_port_attr.sync_gen_cfg.hblank_cycles = 100;
		isys_stream_descr->tpg_port_attr.sync_gen_cfg.vblank_cycles = 100;
		isys_stream_descr->tpg_port_attr.sync_gen_cfg.pixels_per_घड़ी =
		    stream_cfg->pixels_per_घड़ी;
		isys_stream_descr->tpg_port_attr.sync_gen_cfg.nr_of_frames = (uपूर्णांक32_t)~(0x0);
		isys_stream_descr->tpg_port_attr.sync_gen_cfg.pixels_per_line =
		    stream_cfg->isys_config[IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX].input_res.width;
		isys_stream_descr->tpg_port_attr.sync_gen_cfg.lines_per_frame =
		    stream_cfg->isys_config[IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX].input_res.height;

		अवरोध;
	हाल IA_CSS_INPUT_MODE_PRBS:

		isys_stream_descr->prbs_port_attr.seed0 = stream_cfg->source.prbs.seed;
		isys_stream_descr->prbs_port_attr.seed1 = stream_cfg->source.prbs.seed1;

		/*
		 * TODO
		 * - Make "sync_gen_cfg" as part of "ia_css_prbs_config".
		 */
		isys_stream_descr->prbs_port_attr.sync_gen_cfg.hblank_cycles = 100;
		isys_stream_descr->prbs_port_attr.sync_gen_cfg.vblank_cycles = 100;
		isys_stream_descr->prbs_port_attr.sync_gen_cfg.pixels_per_घड़ी =
		    stream_cfg->pixels_per_घड़ी;
		isys_stream_descr->prbs_port_attr.sync_gen_cfg.nr_of_frames = (uपूर्णांक32_t)~(0x0);
		isys_stream_descr->prbs_port_attr.sync_gen_cfg.pixels_per_line =
		    stream_cfg->isys_config[IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX].input_res.width;
		isys_stream_descr->prbs_port_attr.sync_gen_cfg.lines_per_frame =
		    stream_cfg->isys_config[IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX].input_res.height;

		अवरोध;
	हाल IA_CSS_INPUT_MODE_BUFFERED_SENSOR: अणु
		पूर्णांक err;
		अचिन्हित पूर्णांक fmt_type;

		err = ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(
			  stream_cfg->isys_config[isys_stream_idx].क्रमmat,
			  MIPI_PREDICTOR_NONE,
			  &fmt_type);
		अगर (err)
			rc = false;

		isys_stream_descr->csi_port_attr.active_lanes =
		    stream_cfg->source.port.num_lanes;
		isys_stream_descr->csi_port_attr.fmt_type = fmt_type;
		isys_stream_descr->csi_port_attr.ch_id = stream_cfg->channel_id;
#अगर_घोषित ISP2401
		isys_stream_descr->online = stream_cfg->online;
#पूर्ण_अगर
		err |= ia_css_isys_convert_compressed_क्रमmat(
			   &stream_cfg->source.port.compression,
			   isys_stream_descr);
		अगर (err)
			rc = false;

		/* metadata */
		isys_stream_descr->metadata.enable = false;
		अगर (stream_cfg->metadata_config.resolution.height > 0) अणु
			err = ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(
				  stream_cfg->metadata_config.data_type,
				  MIPI_PREDICTOR_NONE,
				  &fmt_type);
			अगर (err)
				rc = false;
			isys_stream_descr->metadata.fmt_type = fmt_type;
			isys_stream_descr->metadata.bits_per_pixel =
			    ia_css_util_input_क्रमmat_bpp(stream_cfg->metadata_config.data_type, true);
			isys_stream_descr->metadata.pixels_per_line =
			    stream_cfg->metadata_config.resolution.width;
			isys_stream_descr->metadata.lines_per_frame =
			    stream_cfg->metadata_config.resolution.height;
#अगर_घोषित ISP2401
			/* For new input प्रणाली, number of str2mmio requests must be even.
			 * So we round up number of metadata lines to be even. */
			अगर (isys_stream_descr->metadata.lines_per_frame > 0)
				isys_stream_descr->metadata.lines_per_frame +=
				    (isys_stream_descr->metadata.lines_per_frame & 1);
#पूर्ण_अगर
			isys_stream_descr->metadata.align_req_in_bytes =
			    ia_css_csi2_calculate_input_प्रणाली_alignment(
				stream_cfg->metadata_config.data_type);
			isys_stream_descr->metadata.enable = true;
		पूर्ण

		अवरोध;
	पूर्ण
	शेष:
		rc = false;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_resolution(
    काष्ठा ia_css_stream_config *stream_cfg,
    ia_css_isys_descr_t	*isys_stream_descr,
    पूर्णांक isys_stream_idx)
अणु
	अचिन्हित पूर्णांक bits_per_subpixel;
	अचिन्हित पूर्णांक max_subpixels_per_line;
	अचिन्हित पूर्णांक lines_per_frame;
	अचिन्हित पूर्णांक align_req_in_bytes;
	क्रमागत atomisp_input_क्रमmat fmt_type;

	fmt_type = stream_cfg->isys_config[isys_stream_idx].क्रमmat;
	अगर ((stream_cfg->mode == IA_CSS_INPUT_MODE_SENSOR ||
	     stream_cfg->mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR) &&
	    stream_cfg->source.port.compression.type != IA_CSS_CSI2_COMPRESSION_TYPE_NONE) अणु
		अगर (stream_cfg->source.port.compression.uncompressed_bits_per_pixel ==
		    UNCOMPRESSED_BITS_PER_PIXEL_10) अणु
			fmt_type = ATOMISP_INPUT_FORMAT_RAW_10;
		पूर्ण अन्यथा अगर (stream_cfg->source.port.compression.uncompressed_bits_per_pixel ==
			   UNCOMPRESSED_BITS_PER_PIXEL_12) अणु
			fmt_type = ATOMISP_INPUT_FORMAT_RAW_12;
		पूर्ण अन्यथा
			वापस false;
	पूर्ण

	bits_per_subpixel =
	    sh_css_stream_क्रमmat_2_bits_per_subpixel(fmt_type);
	अगर (bits_per_subpixel == 0)
		वापस false;

	max_subpixels_per_line =
	    csi2_protocol_calculate_max_subpixels_per_line(fmt_type,
		    stream_cfg->isys_config[isys_stream_idx].input_res.width);
	अगर (max_subpixels_per_line == 0)
		वापस false;

	lines_per_frame = stream_cfg->isys_config[isys_stream_idx].input_res.height;
	अगर (lines_per_frame == 0)
		वापस false;

	align_req_in_bytes = ia_css_csi2_calculate_input_प्रणाली_alignment(fmt_type);

	/* HW needs subpixel info क्रम their settings */
	isys_stream_descr->input_port_resolution.bits_per_pixel = bits_per_subpixel;
	isys_stream_descr->input_port_resolution.pixels_per_line =
	    max_subpixels_per_line;
	isys_stream_descr->input_port_resolution.lines_per_frame = lines_per_frame;
	isys_stream_descr->input_port_resolution.align_req_in_bytes =
	    align_req_in_bytes;

	वापस true;
पूर्ण

अटल bool sh_css_translate_stream_cfg_to_isys_stream_descr(
    काष्ठा ia_css_stream_config *stream_cfg,
    bool early_polling,
    ia_css_isys_descr_t	*isys_stream_descr,
    पूर्णांक isys_stream_idx)
अणु
	bool rc;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_translate_stream_cfg_to_isys_stream_descr() enter:\n");
	rc  = sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_id(stream_cfg,
		isys_stream_descr);
	rc &= sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_type(stream_cfg,
		isys_stream_descr);
	rc &= sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_attr(stream_cfg,
		isys_stream_descr, isys_stream_idx);
	rc &= sh_css_translate_stream_cfg_to_input_प्रणाली_input_port_resolution(
		  stream_cfg, isys_stream_descr, isys_stream_idx);

	isys_stream_descr->raw_packed = stream_cfg->pack_raw_pixels;
	isys_stream_descr->linked_isys_stream_id = (पूर्णांक8_t)
		stream_cfg->isys_config[isys_stream_idx].linked_isys_stream_id;
	/*
	 * Early polling is required क्रम बारtamp accuracy in certain हाल.
	 * The ISYS HW polling is started on
	 * ia_css_isys_stream_capture_indication() instead of
	 * ia_css_pipeline_sp_रुको_क्रम_isys_stream_N() as isp processing of
	 * capture takes दीर्घer than getting an ISYS frame
	 *
	 * Only 2401 relevant ??
	 */
#अगर 0 // FIXME: NOT USED on Yocto Aero
	isys_stream_descr->polling_mode
	    = early_polling ? INPUT_SYSTEM_POLL_ON_CAPTURE_REQUEST
	      : INPUT_SYSTEM_POLL_ON_WAIT_FOR_FRAME;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_translate_stream_cfg_to_isys_stream_descr() leave:\n");
#पूर्ण_अगर

	वापस rc;
पूर्ण

अटल bool sh_css_translate_binary_info_to_input_प्रणाली_output_port_attr(
    काष्ठा ia_css_binary *binary,
    ia_css_isys_descr_t     *isys_stream_descr)
अणु
	अगर (!binary)
		वापस false;

	isys_stream_descr->output_port_attr.left_padding = binary->left_padding;
	isys_stream_descr->output_port_attr.max_isp_input_width =
	    binary->info->sp.input.max_width;

	वापस true;
पूर्ण

अटल पूर्णांक
sh_css_config_input_network(काष्ठा ia_css_stream *stream) अणु
	bool					rc;
	ia_css_isys_descr_t			isys_stream_descr;
	अचिन्हित पूर्णांक				sp_thपढ़ो_id;
	काष्ठा sh_css_sp_pipeline_terminal	*sp_pipeline_input_terminal;
	काष्ठा ia_css_pipe *pipe = शून्य;
	काष्ठा ia_css_binary *binary = शून्य;
	पूर्णांक i;
	u32 isys_stream_id;
	bool early_polling = false;

	निश्चित(stream);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_config_input_network() enter 0x%p:\n", stream);

	अगर (stream->config.continuous)
	अणु
		अगर (stream->last_pipe->config.mode == IA_CSS_PIPE_MODE_CAPTURE) अणु
			pipe = stream->last_pipe;
		पूर्ण अन्यथा अगर (stream->last_pipe->config.mode == IA_CSS_PIPE_MODE_YUVPP) अणु
			pipe = stream->last_pipe;
		पूर्ण अन्यथा अगर (stream->last_pipe->config.mode == IA_CSS_PIPE_MODE_PREVIEW) अणु
			pipe = stream->last_pipe->pipe_settings.preview.copy_pipe;
		पूर्ण अन्यथा अगर (stream->last_pipe->config.mode == IA_CSS_PIPE_MODE_VIDEO) अणु
			pipe = stream->last_pipe->pipe_settings.video.copy_pipe;
		पूर्ण
	पूर्ण अन्यथा
	अणु
		pipe = stream->last_pipe;
		अगर (stream->last_pipe->config.mode == IA_CSS_PIPE_MODE_CAPTURE) अणु
			/*
			 * We need to poll the ISYS HW in capture_indication itself
			 * क्रम "non-continuous" capture useहाल क्रम getting accurate
			 * isys frame capture बारtamps.
			 * This is because the capturepipe propcessing takes दीर्घer
			 * to execute than the input प्रणाली frame capture.
			 * 2401 specअगरic
			 */
			early_polling = true;
		पूर्ण
	पूर्ण

	निश्चित(pipe);
	अगर (!pipe)
		वापस -EINVAL;

	अगर (pipe->pipeline.stages)
		अगर (pipe->pipeline.stages->binary)
			binary = pipe->pipeline.stages->binary;

	अगर (binary)
	अणु
		/* this was being करोne in अगरmtr in 2400.
		 * online and cont bypass the init_in_frameinfo_memory_शेषs
		 * so need to करो it here
		 */
		ia_css_get_crop_offsets(pipe, &binary->in_frame_info);
	पूर्ण

	/* get the SP thपढ़ो id */
	rc = ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &sp_thपढ़ो_id);
	अगर (!rc)
		वापस -EINVAL;
	/* get the target input terminal */
	sp_pipeline_input_terminal = &sh_css_sp_group.pipe_io[sp_thपढ़ो_id].input;

	क्रम (i = 0; i < IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH; i++)
	अणु
		/* initialization */
		स_रखो((व्योम *)(&isys_stream_descr), 0, माप(ia_css_isys_descr_t));
		sp_pipeline_input_terminal->context.भव_input_प्रणाली_stream[i].valid = 0;
		sp_pipeline_input_terminal->ctrl.भव_input_प्रणाली_stream_cfg[i].valid = 0;

		अगर (!stream->config.isys_config[i].valid)
			जारी;

		/* translate the stream configuration to the Input System (2401) configuration */
		rc = sh_css_translate_stream_cfg_to_isys_stream_descr(
			 &stream->config,
			 early_polling,
			 &(isys_stream_descr), i);

		अगर (stream->config.online) अणु
			rc &= sh_css_translate_binary_info_to_input_प्रणाली_output_port_attr(
				  binary,
				  &(isys_stream_descr));
		पूर्ण

		अगर (!rc)
			वापस -EINVAL;

		isys_stream_id = ia_css_isys_generate_stream_id(sp_thपढ़ो_id, i);

		/* create the भव Input System (2401) */
		rc =  ia_css_isys_stream_create(
			  &(isys_stream_descr),
			  &sp_pipeline_input_terminal->context.भव_input_प्रणाली_stream[i],
			  isys_stream_id);
		अगर (!rc)
			वापस -EINVAL;

		/* calculate the configuration of the भव Input System (2401) */
		rc = ia_css_isys_stream_calculate_cfg(
			 &sp_pipeline_input_terminal->context.भव_input_प्रणाली_stream[i],
			 &(isys_stream_descr),
			 &sp_pipeline_input_terminal->ctrl.भव_input_प्रणाली_stream_cfg[i]);
		अगर (!rc) अणु
			ia_css_isys_stream_destroy(
			    &sp_pipeline_input_terminal->context.भव_input_प्रणाली_stream[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_config_input_network() leave:\n");

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ia_css_pipe *stream_get_last_pipe(
    काष्ठा ia_css_stream *stream)
अणु
	काष्ठा ia_css_pipe *last_pipe = शून्य;

	अगर (stream)
		last_pipe = stream->last_pipe;

	वापस last_pipe;
पूर्ण

अटल अंतरभूत काष्ठा ia_css_pipe *stream_get_copy_pipe(
    काष्ठा ia_css_stream *stream)
अणु
	काष्ठा ia_css_pipe *copy_pipe = शून्य;
	काष्ठा ia_css_pipe *last_pipe = शून्य;
	क्रमागत ia_css_pipe_id pipe_id;

	last_pipe = stream_get_last_pipe(stream);

	अगर ((stream) &&
	    (last_pipe) &&
	    (stream->config.continuous)) अणु
		pipe_id = last_pipe->mode;
		चयन (pipe_id) अणु
		हाल IA_CSS_PIPE_ID_PREVIEW:
			copy_pipe = last_pipe->pipe_settings.preview.copy_pipe;
			अवरोध;
		हाल IA_CSS_PIPE_ID_VIDEO:
			copy_pipe = last_pipe->pipe_settings.video.copy_pipe;
			अवरोध;
		शेष:
			copy_pipe = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस copy_pipe;
पूर्ण

अटल अंतरभूत काष्ठा ia_css_pipe *stream_get_target_pipe(
    काष्ठा ia_css_stream *stream)
अणु
	काष्ठा ia_css_pipe *target_pipe;

	/* get the pipe that consumes the stream */
	अगर (stream->config.continuous) अणु
		target_pipe = stream_get_copy_pipe(stream);
	पूर्ण अन्यथा अणु
		target_pipe = stream_get_last_pipe(stream);
	पूर्ण

	वापस target_pipe;
पूर्ण

अटल पूर्णांक stream_csi_rx_helper(
    काष्ठा ia_css_stream *stream,
    पूर्णांक (*func)(क्रमागत mipi_port_id, uपूर्णांक32_t))
अणु
	पूर्णांक retval = -EINVAL;
	u32 sp_thपढ़ो_id, stream_id;
	bool rc;
	काष्ठा ia_css_pipe *target_pipe = शून्य;

	अगर ((!stream) || (stream->config.mode != IA_CSS_INPUT_MODE_BUFFERED_SENSOR))
		जाओ निकास;

	target_pipe = stream_get_target_pipe(stream);

	अगर (!target_pipe)
		जाओ निकास;

	rc = ia_css_pipeline_get_sp_thपढ़ो_id(
		 ia_css_pipe_get_pipe_num(target_pipe),
		 &sp_thपढ़ो_id);

	अगर (!rc)
		जाओ निकास;

	/* (un)रेजिस्टर all valid "virtual isys streams" within the ia_css_stream */
	stream_id = 0;
	करो अणु
		अगर (stream->config.isys_config[stream_id].valid) अणु
			u32 isys_stream_id = ia_css_isys_generate_stream_id(sp_thपढ़ो_id, stream_id);

			retval = func(stream->config.source.port.port, isys_stream_id);
		पूर्ण
		stream_id++;
	पूर्ण जबतक ((retval == 0) &&
		 (stream_id < IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH));

निकास:
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक stream_रेजिस्टर_with_csi_rx(
    काष्ठा ia_css_stream *stream)
अणु
	वापस stream_csi_rx_helper(stream, ia_css_isys_csi_rx_रेजिस्टर_stream);
पूर्ण

अटल अंतरभूत पूर्णांक stream_unरेजिस्टर_with_csi_rx(
    काष्ठा ia_css_stream *stream)
अणु
	वापस stream_csi_rx_helper(stream, ia_css_isys_csi_rx_unरेजिस्टर_stream);
पूर्ण
#पूर्ण_अगर

#अगर WITH_PC_MONITORING
अटल काष्ठा task_काष्ठा *my_kthपढ़ो;    /* Handle क्रम the monitoring thपढ़ो */
अटल पूर्णांक sh_binary_running;         /* Enable sampling in the thपढ़ो */

अटल व्योम prपूर्णांक_pc_histo(अक्षर *core_name, काष्ठा sh_css_pc_histogram *hist)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक cnt_run = 0;
	अचिन्हित पूर्णांक cnt_stall = 0;

	अगर (!hist)
		वापस;

	sh_css_prपूर्णांक("%s histogram length = %d\n", core_name, hist->length);
	sh_css_prपूर्णांक("%s PC\turn\tstall\n", core_name);

	क्रम (i = 0; i < hist->length; i++) अणु
		अगर ((hist->run[i] == 0) && (hist->run[i] == hist->stall[i]))
			जारी;
		sh_css_prपूर्णांक("%s %d\t%d\t%d\n",
			     core_name, i, hist->run[i], hist->stall[i]);
		cnt_run += hist->run[i];
		cnt_stall += hist->stall[i];
	पूर्ण

	sh_css_prपूर्णांक(" Statistics for %s, cnt_run = %d, cnt_stall = %d, hist->length = %d\n",
		     core_name, cnt_run, cnt_stall, hist->length);
पूर्ण

अटल व्योम prपूर्णांक_pc_histogram(व्योम)
अणु
	काष्ठा ia_css_binary_metrics *metrics;

	क्रम (metrics = sh_css_metrics.binary_metrics;
	     metrics;
	     metrics = metrics->next) अणु
		अगर (metrics->mode == IA_CSS_BINARY_MODE_PREVIEW ||
		    metrics->mode == IA_CSS_BINARY_MODE_VF_PP) अणु
			sh_css_prपूर्णांक("pc_histogram for binary %d is SKIPPED\n",
				     metrics->id);
			जारी;
		पूर्ण

		sh_css_prपूर्णांक(" pc_histogram for binary %d\n", metrics->id);
		prपूर्णांक_pc_histo("  ISP", &metrics->isp_histogram);
		prपूर्णांक_pc_histo("  SP",   &metrics->sp_histogram);
		sh_css_prपूर्णांक("print_pc_histogram() done for binary->id = %d, done.\n",
			     metrics->id);
	पूर्ण

	sh_css_prपूर्णांक("PC_MONITORING:print_pc_histogram() -- DONE\n");
पूर्ण

अटल पूर्णांक pc_monitoring(व्योम *data)
अणु
	पूर्णांक i = 0;

	(व्योम)data;
	जबतक (true) अणु
		अगर (sh_binary_running) अणु
			sh_css_metrics_sample_pcs();
#अगर MULTIPLE_SAMPLES
			क्रम (i = 0; i < NOF_SAMPLES; i++)
				sh_css_metrics_sample_pcs();
#पूर्ण_अगर
		पूर्ण
		usleep_range(10, 50);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम spying_thपढ़ो_create(व्योम)
अणु
	my_kthपढ़ो = kthपढ़ो_run(pc_monitoring, शून्य, "sh_pc_monitor");
	sh_css_metrics_enable_pc_histogram(1);
पूर्ण

अटल व्योम input_frame_info(काष्ठा ia_css_frame_info frame_info)
अणु
	sh_css_prपूर्णांक("SH_CSS:input_frame_info() -- frame->info.res.width = %d, frame->info.res.height = %d, format = %d\n",
		     frame_info.res.width, frame_info.res.height, frame_info.क्रमmat);
पूर्ण
#पूर्ण_अगर /* WITH_PC_MONITORING */

अटल व्योम
start_binary(काष्ठा ia_css_pipe *pipe,
	     काष्ठा ia_css_binary *binary)
अणु
	निश्चित(pipe);
	/* Acceleration uses firmware, the binary thus can be शून्य */

	अगर (binary)
		sh_css_metrics_start_binary(&binary->metrics);

#अगर WITH_PC_MONITORING
	sh_css_prपूर्णांक("PC_MONITORING: %s() -- binary id = %d , enable_dvs_envelope = %d\n",
		     __func__, binary->info->sp.id,
		     binary->info->sp.enable.dvs_envelope);
	input_frame_info(binary->in_frame_info);

	अगर (binary && binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_VIDEO)
		sh_binary_running = true;
#पूर्ण_अगर

#अगर !defined(ISP2401)
	अगर (pipe->stream->reconfigure_css_rx) अणु
		ia_css_isys_rx_configure(&pipe->stream->csi_rx_config,
					 pipe->stream->config.mode);
		pipe->stream->reconfigure_css_rx = false;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* start the copy function on the SP */
अटल पूर्णांक
start_copy_on_sp(काष्ठा ia_css_pipe *pipe,
		 काष्ठा ia_css_frame *out_frame) अणु
	(व्योम)out_frame;
	निश्चित(pipe);
	निश्चित(pipe->stream);

	अगर ((!pipe) || (!pipe->stream))
		वापस -EINVAL;

#अगर !defined(ISP2401)
	अगर (pipe->stream->reconfigure_css_rx)
		ia_css_isys_rx_disable();
#पूर्ण_अगर

	अगर (pipe->stream->config.input_config.क्रमmat != ATOMISP_INPUT_FORMAT_BINARY_8)
		वापस -EINVAL;
	sh_css_sp_start_binary_copy(ia_css_pipe_get_pipe_num(pipe), out_frame, pipe->stream->config.pixels_per_घड़ी == 2);

#अगर !defined(ISP2401)
	अगर (pipe->stream->reconfigure_css_rx)
	अणु
		ia_css_isys_rx_configure(&pipe->stream->csi_rx_config,
					 pipe->stream->config.mode);
		pipe->stream->reconfigure_css_rx = false;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम sh_css_binary_args_reset(काष्ठा sh_css_binary_args *args)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_TNR_FRAMES; i++)
		args->tnr_frames[i] = शून्य;
	क्रम (i = 0; i < MAX_NUM_VIDEO_DELAY_FRAMES; i++)
		args->delay_frames[i] = शून्य;
	args->in_frame      = शून्य;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		args->out_frame[i] = शून्य;
	args->out_vf_frame  = शून्य;
	args->copy_vf       = false;
	args->copy_output   = true;
	args->vf_करोwnscale_log2 = 0;
पूर्ण

अटल व्योम start_pipe(
    काष्ठा ia_css_pipe *me,
    क्रमागत sh_css_pipe_config_override copy_ovrd,
    क्रमागत ia_css_input_mode input_mode)
अणु
	स्थिर काष्ठा ia_css_coordinate *coord = शून्य;
	स्थिर काष्ठा ia_css_isp_parameters *params = शून्य;


	IA_CSS_ENTER_PRIVATE("me = %p, copy_ovrd = %d, input_mode = %d",
			     me, copy_ovrd, input_mode);

	निश्चित(me); /* all callers are in this file and call with non null argument */

	अगर (!IS_ISP2401) अणु
		coord = &me->config.पूर्णांकernal_frame_origin_bqs_on_sctbl;
		params = me->stream->isp_params_configs;
	पूर्ण

	sh_css_sp_init_pipeline(&me->pipeline,
				me->mode,
				(uपूर्णांक8_t)ia_css_pipe_get_pipe_num(me),
				me->config.शेष_capture_config.enable_xnr != 0,
				me->stream->config.pixels_per_घड़ी == 2,
				me->stream->config.continuous,
				false,
				me->required_bds_factor,
				copy_ovrd,
				input_mode,
				&me->stream->config.metadata_config,
				&me->stream->info.metadata_info
				, (input_mode == IA_CSS_INPUT_MODE_MEMORY) ?
				(क्रमागत mipi_port_id)0 :
				me->stream->config.source.port.port,
				coord,
				params);

	अगर (me->config.mode != IA_CSS_PIPE_MODE_COPY) अणु
		काष्ठा ia_css_pipeline_stage *stage;

		stage = me->pipeline.stages;
		अगर (stage) अणु
			me->pipeline.current_stage = stage;
			start_binary(me, stage->binary);
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE_PRIVATE("void");
पूर्ण

व्योम
sh_css_invalidate_shading_tables(काष्ठा ia_css_stream *stream)
अणु
	पूर्णांक i;

	निश्चित(stream);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_invalidate_shading_tables() enter:\n");

	क्रम (i = 0; i < stream->num_pipes; i++) अणु
		निश्चित(stream->pipes[i]);
		sh_css_pipe_मुक्त_shading_table(stream->pipes[i]);
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_invalidate_shading_tables() leave: return_void\n");
पूर्ण

अटल व्योम
enable_पूर्णांकerrupts(क्रमागत ia_css_irq_type irq_type)
अणु
#अगर_अघोषित ISP2401
	क्रमागत mipi_port_id port;
#पूर्ण_अगर
	bool enable_pulse = irq_type != IA_CSS_IRQ_TYPE_EDGE;

	IA_CSS_ENTER_PRIVATE("");
	/* Enable IRQ on the SP which संकेतs that SP goes to idle
	 * (aka पढ़ोy state) */
	cnd_sp_irq_enable(SP0_ID, true);
	/* Set the IRQ device 0 to either level or pulse */
	irq_enable_pulse(IRQ0_ID, enable_pulse);

	cnd_virq_enable_channel(virq_sp, true);

	/* Enable SW पूर्णांकerrupt 0, this is used to संकेत ISYS events */
	cnd_virq_enable_channel(
	    (क्रमागत virq_id)(IRQ_SW_CHANNEL0_ID + IRQ_SW_CHANNEL_OFFSET),
	    true);
	/* Enable SW पूर्णांकerrupt 1, this is used to संकेत PSYS events */
	cnd_virq_enable_channel(
	    (क्रमागत virq_id)(IRQ_SW_CHANNEL1_ID + IRQ_SW_CHANNEL_OFFSET),
	    true);

#अगर_अघोषित ISP2401
	क्रम (port = 0; port < N_MIPI_PORT_ID; port++)
		ia_css_isys_rx_enable_all_पूर्णांकerrupts(port);
#पूर्ण_अगर

	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

अटल bool sh_css_setup_spctrl_config(स्थिर काष्ठा ia_css_fw_info *fw,
				       स्थिर अक्षर *program,
				       ia_css_spctrl_cfg  *spctrl_cfg)
अणु
	अगर ((!fw) || (!spctrl_cfg))
		वापस false;
	spctrl_cfg->sp_entry = 0;
	spctrl_cfg->program_name = (अक्षर *)(program);

	spctrl_cfg->ddr_data_offset =  fw->blob.data_source;
	spctrl_cfg->dmem_data_addr = fw->blob.data_target;
	spctrl_cfg->dmem_bss_addr = fw->blob.bss_target;
	spctrl_cfg->data_size = fw->blob.data_size;
	spctrl_cfg->bss_size = fw->blob.bss_size;

	spctrl_cfg->spctrl_config_dmem_addr = fw->info.sp.init_dmem_data;
	spctrl_cfg->spctrl_state_dmem_addr = fw->info.sp.sw_state;

	spctrl_cfg->code_size = fw->blob.size;
	spctrl_cfg->code      = fw->blob.code;
	spctrl_cfg->sp_entry  = fw->info.sp.sp_entry; /* entry function ptr on SP */

	वापस true;
पूर्ण

व्योम
ia_css_unload_firmware(व्योम)
अणु
	अगर (sh_css_num_binaries) अणु
		/* we have alपढ़ोy loaded beक्रमe so get rid of the old stuff */
		ia_css_binary_uninit();
		sh_css_unload_firmware();
	पूर्ण
	fw_explicitly_loaded = false;
पूर्ण

अटल व्योम
ia_css_reset_शेषs(काष्ठा sh_css *css)
अणु
	काष्ठा sh_css शेष_css;

	/* Reset everything to zero */
	स_रखो(&शेष_css, 0, माप(शेष_css));

	/* Initialize the non zero values*/
	शेष_css.check_प्रणाली_idle = true;
	शेष_css.num_cont_raw_frames = NUM_CONTINUOUS_FRAMES;

	/* All should be 0: but स_रखो करोes it alपढ़ोy.
	 * शेष_css.num_mipi_frames[N_CSI_PORTS] = 0;
	 */

	शेष_css.irq_type = IA_CSS_IRQ_TYPE_EDGE;

	/*Set the शेषs to the output */
	*css = शेष_css;
पूर्ण

पूर्णांक
ia_css_load_firmware(काष्ठा device *dev, स्थिर काष्ठा ia_css_env *env,
		     स्थिर काष्ठा ia_css_fw  *fw) अणु
	पूर्णांक err;

	अगर (!env)
		वापस -EINVAL;
	अगर (!fw)
		वापस -EINVAL;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_load_firmware() enter\n");

	/* make sure we initialize my_css */
	अगर (my_css.flush != env->cpu_mem_env.flush)
	अणु
		ia_css_reset_शेषs(&my_css);
		my_css.flush = env->cpu_mem_env.flush;
	पूर्ण

	ia_css_unload_firmware(); /* in हाल we are called twice */
	err = sh_css_load_firmware(dev, fw->data, fw->bytes);
	अगर (!err)
	अणु
		err = ia_css_binary_init_infos();
		अगर (!err)
			fw_explicitly_loaded = true;
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_load_firmware() leave\n");
	वापस err;
पूर्ण

पूर्णांक
ia_css_init(काष्ठा device *dev, स्थिर काष्ठा ia_css_env *env,
	    स्थिर काष्ठा ia_css_fw  *fw,
	    u32                 mmu_l1_base,
	    क्रमागत ia_css_irq_type     irq_type) अणु
	पूर्णांक err;
	ia_css_spctrl_cfg spctrl_cfg;

	व्योम (*flush_func)(काष्ठा ia_css_acc_fw *fw);
	hrt_data select, enable;

	/*
	 * The C99 standard करोes not specअगरy the exact object representation of काष्ठाs;
	 * the representation is compiler dependent.
	 *
	 * The काष्ठाs that are communicated between host and SP/ISP should have the
	 * exact same object representation. The compiler that is used to compile the
	 * firmware is hivecc.
	 *
	 * To check अगर a dअगरferent compiler, used to compile a host application, uses
	 * another object representation, macros are defined specअगरying the size of
	 * the काष्ठाs as expected by the firmware.
	 *
	 * A host application shall verअगरy that a माप( ) of the काष्ठा is equal to
	 * the SIZE_OF_XXX macro of the corresponding काष्ठा. If they are not
	 * equal, functionality will अवरोध.
	 */
	/* Check काष्ठा sh_css_ddr_address_map */
	COMPILATION_ERROR_IF(माप(काष्ठा sh_css_ddr_address_map)		!= SIZE_OF_SH_CSS_DDR_ADDRESS_MAP_STRUCT);
	/* Check काष्ठा host_sp_queues */
	COMPILATION_ERROR_IF(माप(काष्ठा host_sp_queues)			!= SIZE_OF_HOST_SP_QUEUES_STRUCT);
	COMPILATION_ERROR_IF(माप(काष्ठा ia_css_circbuf_desc_s)		!= SIZE_OF_IA_CSS_CIRCBUF_DESC_S_STRUCT);
	COMPILATION_ERROR_IF(माप(काष्ठा ia_css_circbuf_elem_s)		!= SIZE_OF_IA_CSS_CIRCBUF_ELEM_S_STRUCT);

	/* Check काष्ठा host_sp_communication */
	COMPILATION_ERROR_IF(माप(काष्ठा host_sp_communication)		!= SIZE_OF_HOST_SP_COMMUNICATION_STRUCT);
	COMPILATION_ERROR_IF(माप(काष्ठा sh_css_event_irq_mask)		!= SIZE_OF_SH_CSS_EVENT_IRQ_MASK_STRUCT);

	/* Check काष्ठा sh_css_hmm_buffer */
	COMPILATION_ERROR_IF(माप(काष्ठा sh_css_hmm_buffer)			!= SIZE_OF_SH_CSS_HMM_BUFFER_STRUCT);
	COMPILATION_ERROR_IF(माप(काष्ठा ia_css_isp_3a_statistics)		!= SIZE_OF_IA_CSS_ISP_3A_STATISTICS_STRUCT);
	COMPILATION_ERROR_IF(माप(काष्ठा ia_css_isp_dvs_statistics)		!= SIZE_OF_IA_CSS_ISP_DVS_STATISTICS_STRUCT);
	COMPILATION_ERROR_IF(माप(काष्ठा ia_css_metadata)			!= SIZE_OF_IA_CSS_METADATA_STRUCT);

	/* Check काष्ठा ia_css_init_dmem_cfg */
	COMPILATION_ERROR_IF(माप(काष्ठा ia_css_sp_init_dmem_cfg)		!= SIZE_OF_IA_CSS_SP_INIT_DMEM_CFG_STRUCT);

	अगर (!fw && !fw_explicitly_loaded)
		वापस -EINVAL;
	अगर (!env)
		वापस -EINVAL;

	sh_css_म_लिखो = env->prपूर्णांक_env.debug_prपूर्णांक;

	IA_CSS_ENTER("void");

	flush_func     = env->cpu_mem_env.flush;

	pipe_global_init();
	ia_css_pipeline_init();
	ia_css_queue_map_init();

	ia_css_device_access_init(&env->hw_access_env);

	select = gpio_reg_load(GPIO0_ID, _gpio_block_reg_करो_select)
	& (~GPIO_FLASH_PIN_MASK);
	enable = gpio_reg_load(GPIO0_ID, _gpio_block_reg_करो_e)
	| GPIO_FLASH_PIN_MASK;
	sh_css_mmu_set_page_table_base_index(mmu_l1_base);

	my_css_save.mmu_base = mmu_l1_base;

	ia_css_reset_शेषs(&my_css);

	my_css_save.driver_env = *env;
	my_css.flush     = flush_func;

	err = ia_css_rmgr_init();
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

	IA_CSS_LOG("init: %d", my_css_save_initialized);

	अगर (!my_css_save_initialized)
	अणु
		my_css_save_initialized = true;
		my_css_save.mode = sh_css_mode_working;
		स_रखो(my_css_save.stream_seeds, 0,
		       माप(काष्ठा sh_css_stream_seed) * MAX_ACTIVE_STREAMS);
		IA_CSS_LOG("init: %d mode=%d", my_css_save_initialized, my_css_save.mode);
	पूर्ण

	mipi_init();

#अगर_अघोषित ISP2401
	/* In हाल this has been programmed alपढ़ोy, update पूर्णांकernal
	   data काष्ठाure ... DEPRECATED */
	my_css.page_table_base_index = mmu_get_page_table_base_index(MMU0_ID);

#पूर्ण_अगर
	my_css.irq_type = irq_type;

	my_css_save.irq_type = irq_type;

	enable_पूर्णांकerrupts(my_css.irq_type);

	/* configure GPIO to output mode */
	gpio_reg_store(GPIO0_ID, _gpio_block_reg_करो_select, select);
	gpio_reg_store(GPIO0_ID, _gpio_block_reg_करो_e, enable);
	gpio_reg_store(GPIO0_ID, _gpio_block_reg_करो_0, 0);

	err = ia_css_refcount_init(REFCOUNT_SIZE);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण
	err = sh_css_params_init();
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण
	अगर (fw)
	अणु
		ia_css_unload_firmware(); /* in हाल we alपढ़ोy had firmware loaded */
		err = sh_css_load_firmware(dev, fw->data, fw->bytes);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR(err);
			वापस err;
		पूर्ण
		err = ia_css_binary_init_infos();
		अगर (err) अणु
			IA_CSS_LEAVE_ERR(err);
			वापस err;
		पूर्ण
		fw_explicitly_loaded = false;
#अगर_अघोषित ISP2401
		my_css_save.loaded_fw = (काष्ठा ia_css_fw *)fw;
#पूर्ण_अगर
	पूर्ण
	अगर (!sh_css_setup_spctrl_config(&sh_css_sp_fw, SP_PROG_NAME, &spctrl_cfg))
		वापस -EINVAL;

	err = ia_css_spctrl_load_fw(SP0_ID, &spctrl_cfg);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

#अगर WITH_PC_MONITORING
	अगर (!thपढ़ो_alive)
	अणु
		thपढ़ो_alive++;
		sh_css_prपूर्णांक("PC_MONITORING: %s() -- create thread DISABLED\n",
			     __func__);
		spying_thपढ़ो_create();
	पूर्ण
#पूर्ण_अगर
	अगर (!sh_css_hrt_प्रणाली_is_idle())
	अणु
		IA_CSS_LEAVE_ERR(-EBUSY);
		वापस -EBUSY;
	पूर्ण
	/* can be called here, queuing works, but:
	   - when sp is started later, it will wipe queued items
	   so क्रम now we leave it क्रम later and make sure
	   updates are not called to frequently.
	sh_css_init_buffer_queues();
	*/

#अगर defined(ISP2401)
	gp_device_reg_store(GP_DEVICE0_ID, _REG_GP_SWITCH_ISYS2401_ADDR, 1);
#पूर्ण_अगर


	अगर (!IS_ISP2401)
		dma_set_max_burst_size(DMA0_ID, HIVE_DMA_BUS_DDR_CONN,
				       ISP2400_DMA_MAX_BURST_LENGTH);
	अन्यथा
		dma_set_max_burst_size(DMA0_ID, HIVE_DMA_BUS_DDR_CONN,
				       ISP2401_DMA_MAX_BURST_LENGTH);

	अगर (ia_css_isys_init() != INPUT_SYSTEM_ERR_NO_ERROR)
		err = -EINVAL;

	sh_css_params_map_and_store_शेष_gdc_lut();

	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

पूर्णांक
ia_css_enable_isys_event_queue(bool enable) अणु
	अगर (sh_css_sp_is_running())
		वापस -EBUSY;
	sh_css_sp_enable_isys_event_queue(enable);
	वापस 0;
पूर्ण

/* For Acceleration API: Flush FW (shared buffer poपूर्णांकer) arguments */
व्योम
sh_css_flush(काष्ठा ia_css_acc_fw *fw)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "sh_css_flush() enter:\n");
	अगर ((fw) && (my_css.flush))
		my_css.flush(fw);
पूर्ण

/* Mapping sp thपढ़ोs. Currently, this is करोne when a stream is created and
 * pipelines are पढ़ोy to be converted to sp pipelines. Be careful अगर you are
 * करोing it from stream_create since we could run out of sp thपढ़ोs due to
 * allocation on inactive pipelines. */
अटल पूर्णांक
map_sp_thपढ़ोs(काष्ठा ia_css_stream *stream, bool map) अणु
	काष्ठा ia_css_pipe *मुख्य_pipe = शून्य;
	काष्ठा ia_css_pipe *copy_pipe = शून्य;
	काष्ठा ia_css_pipe *capture_pipe = शून्य;
	काष्ठा ia_css_pipe *acc_pipe = शून्य;
	पूर्णांक err = 0;
	क्रमागत ia_css_pipe_id pipe_id;

	निश्चित(stream);
	IA_CSS_ENTER_PRIVATE("stream = %p, map = %s",
			     stream, map ? "true" : "false");

	अगर (!stream)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	मुख्य_pipe = stream->last_pipe;
	pipe_id	= मुख्य_pipe->mode;

	ia_css_pipeline_map(मुख्य_pipe->pipe_num, map);

	चयन (pipe_id)
	अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		copy_pipe    = मुख्य_pipe->pipe_settings.preview.copy_pipe;
		capture_pipe = मुख्य_pipe->pipe_settings.preview.capture_pipe;
		acc_pipe     = मुख्य_pipe->pipe_settings.preview.acc_pipe;
		अवरोध;

	हाल IA_CSS_PIPE_ID_VIDEO:
		copy_pipe    = मुख्य_pipe->pipe_settings.video.copy_pipe;
		capture_pipe = मुख्य_pipe->pipe_settings.video.capture_pipe;
		अवरोध;

	हाल IA_CSS_PIPE_ID_CAPTURE:
	हाल IA_CSS_PIPE_ID_ACC:
	शेष:
		अवरोध;
	पूर्ण

	अगर (acc_pipe)
	अणु
		ia_css_pipeline_map(acc_pipe->pipe_num, map);
	पूर्ण

	अगर (capture_pipe)
	अणु
		ia_css_pipeline_map(capture_pipe->pipe_num, map);
	पूर्ण

	/* Firmware expects copy pipe to be the last pipe mapped. (अगर needed) */
	अगर (copy_pipe)
	अणु
		ia_css_pipeline_map(copy_pipe->pipe_num, map);
	पूर्ण
	/* DH regular multi pipe - not continuous mode: map the next pipes too */
	अगर (!stream->config.continuous)
	अणु
		पूर्णांक i;

		क्रम (i = 1; i < stream->num_pipes; i++)
			ia_css_pipeline_map(stream->pipes[i]->pipe_num, map);
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* creates a host pipeline skeleton क्रम all pipes in a stream. Called during
 * stream_create. */
अटल पूर्णांक
create_host_pipeline_काष्ठाure(काष्ठा ia_css_stream *stream) अणु
	काष्ठा ia_css_pipe *copy_pipe = शून्य, *capture_pipe = शून्य;
	काष्ठा ia_css_pipe *acc_pipe = शून्य;
	क्रमागत ia_css_pipe_id pipe_id;
	काष्ठा ia_css_pipe *मुख्य_pipe = शून्य;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक copy_pipe_delay = 0,
	capture_pipe_delay = 0;

	निश्चित(stream);
	IA_CSS_ENTER_PRIVATE("stream = %p", stream);

	अगर (!stream)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	मुख्य_pipe	= stream->last_pipe;
	निश्चित(मुख्य_pipe);
	अगर (!मुख्य_pipe)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	pipe_id	= मुख्य_pipe->mode;

	चयन (pipe_id)
	अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		copy_pipe    = मुख्य_pipe->pipe_settings.preview.copy_pipe;
		copy_pipe_delay = मुख्य_pipe->dvs_frame_delay;
		capture_pipe = मुख्य_pipe->pipe_settings.preview.capture_pipe;
		capture_pipe_delay = IA_CSS_FRAME_DELAY_0;
		acc_pipe     = मुख्य_pipe->pipe_settings.preview.acc_pipe;
		err = ia_css_pipeline_create(&मुख्य_pipe->pipeline, मुख्य_pipe->mode,
					     मुख्य_pipe->pipe_num, मुख्य_pipe->dvs_frame_delay);
		अवरोध;

	हाल IA_CSS_PIPE_ID_VIDEO:
		copy_pipe    = मुख्य_pipe->pipe_settings.video.copy_pipe;
		copy_pipe_delay = मुख्य_pipe->dvs_frame_delay;
		capture_pipe = मुख्य_pipe->pipe_settings.video.capture_pipe;
		capture_pipe_delay = IA_CSS_FRAME_DELAY_0;
		err = ia_css_pipeline_create(&मुख्य_pipe->pipeline, मुख्य_pipe->mode,
					     मुख्य_pipe->pipe_num, मुख्य_pipe->dvs_frame_delay);
		अवरोध;

	हाल IA_CSS_PIPE_ID_CAPTURE:
		capture_pipe = मुख्य_pipe;
		capture_pipe_delay = मुख्य_pipe->dvs_frame_delay;
		अवरोध;

	हाल IA_CSS_PIPE_ID_YUVPP:
		err = ia_css_pipeline_create(&मुख्य_pipe->pipeline, मुख्य_pipe->mode,
					     मुख्य_pipe->pipe_num, मुख्य_pipe->dvs_frame_delay);
		अवरोध;

	हाल IA_CSS_PIPE_ID_ACC:
		err = ia_css_pipeline_create(&मुख्य_pipe->pipeline, मुख्य_pipe->mode,
					     मुख्य_pipe->pipe_num, मुख्य_pipe->dvs_frame_delay);
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

	अगर (!(err) && copy_pipe)
	अणु
		err = ia_css_pipeline_create(&copy_pipe->pipeline,
					     copy_pipe->mode,
					     copy_pipe->pipe_num,
					     copy_pipe_delay);
	पूर्ण

	अगर (!(err) && capture_pipe)
	अणु
		err = ia_css_pipeline_create(&capture_pipe->pipeline,
					     capture_pipe->mode,
					     capture_pipe->pipe_num,
					     capture_pipe_delay);
	पूर्ण

	अगर (!(err) && acc_pipe)
	अणु
		err = ia_css_pipeline_create(&acc_pipe->pipeline, acc_pipe->mode,
					     acc_pipe->pipe_num, मुख्य_pipe->dvs_frame_delay);
	पूर्ण

	/* DH regular multi pipe - not continuous mode: create the next pipelines too */
	अगर (!stream->config.continuous)
	अणु
		पूर्णांक i;

		क्रम (i = 1; i < stream->num_pipes && 0 == err; i++) अणु
			मुख्य_pipe = stream->pipes[i];
			err = ia_css_pipeline_create(&मुख्य_pipe->pipeline,
						     मुख्य_pipe->mode,
						     मुख्य_pipe->pipe_num,
						     मुख्य_pipe->dvs_frame_delay);
		पूर्ण
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* creates a host pipeline क्रम all pipes in a stream. Called during
 * stream_start. */
अटल पूर्णांक
create_host_pipeline(काष्ठा ia_css_stream *stream) अणु
	काष्ठा ia_css_pipe *copy_pipe = शून्य, *capture_pipe = शून्य;
	काष्ठा ia_css_pipe *acc_pipe = शून्य;
	क्रमागत ia_css_pipe_id pipe_id;
	काष्ठा ia_css_pipe *मुख्य_pipe = शून्य;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक max_input_width = 0;

	IA_CSS_ENTER_PRIVATE("stream = %p", stream);
	अगर (!stream)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	मुख्य_pipe	= stream->last_pipe;
	pipe_id	= मुख्य_pipe->mode;

	/* No continuous frame allocation क्रम capture pipe. It uses the
	 * "main" pipe's frames. */
	अगर ((pipe_id == IA_CSS_PIPE_ID_PREVIEW) ||
	    (pipe_id == IA_CSS_PIPE_ID_VIDEO))
	अणु
		/* About pipe_id == IA_CSS_PIPE_ID_PREVIEW && stream->config.mode != IA_CSS_INPUT_MODE_MEMORY:
		 * The original condition pipe_id == IA_CSS_PIPE_ID_PREVIEW is too strong. E.g. in SkyCam (with memory
		 * based input frames) there is no continuous mode and thus no need क्रम allocated continuous frames
		 * This is not only क्रम SkyCam but क्रम all preview हालs that use DDR based input frames. For this
		 * reason the stream->config.mode != IA_CSS_INPUT_MODE_MEMORY has beed added.
		 */
		अगर (stream->config.continuous ||
		    (pipe_id == IA_CSS_PIPE_ID_PREVIEW &&
		     stream->config.mode != IA_CSS_INPUT_MODE_MEMORY)) अणु
			err = alloc_continuous_frames(मुख्य_pipe, true);
			अगर (err)
				जाओ ERR;
		पूर्ण
	पूर्ण

#अगर !defined(ISP2401)
	/* old isys: need to allocate_mipi_frames() even in IA_CSS_PIPE_MODE_COPY */
	अगर (pipe_id != IA_CSS_PIPE_ID_ACC)
	अणु
		err = allocate_mipi_frames(मुख्य_pipe, &stream->info);
		अगर (err)
			जाओ ERR;
	पूर्ण
#या_अगर defined(ISP2401)
	अगर ((pipe_id != IA_CSS_PIPE_ID_ACC) &&
	    (मुख्य_pipe->config.mode != IA_CSS_PIPE_MODE_COPY))
	अणु
		err = allocate_mipi_frames(मुख्य_pipe, &stream->info);
		अगर (err)
			जाओ ERR;
	पूर्ण
#पूर्ण_अगर

	चयन (pipe_id)
	अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		copy_pipe    = मुख्य_pipe->pipe_settings.preview.copy_pipe;
		capture_pipe = मुख्य_pipe->pipe_settings.preview.capture_pipe;
		acc_pipe     = मुख्य_pipe->pipe_settings.preview.acc_pipe;
		max_input_width =
		    मुख्य_pipe->pipe_settings.preview.preview_binary.info->sp.input.max_width;

		err = create_host_preview_pipeline(मुख्य_pipe);
		अगर (err)
			जाओ ERR;

		अवरोध;

	हाल IA_CSS_PIPE_ID_VIDEO:
		copy_pipe    = मुख्य_pipe->pipe_settings.video.copy_pipe;
		capture_pipe = मुख्य_pipe->pipe_settings.video.capture_pipe;
		max_input_width =
		    मुख्य_pipe->pipe_settings.video.video_binary.info->sp.input.max_width;

		err = create_host_video_pipeline(मुख्य_pipe);
		अगर (err)
			जाओ ERR;

		अवरोध;

	हाल IA_CSS_PIPE_ID_CAPTURE:
		capture_pipe = मुख्य_pipe;

		अवरोध;

	हाल IA_CSS_PIPE_ID_YUVPP:
		err = create_host_yuvpp_pipeline(मुख्य_pipe);
		अगर (err)
			जाओ ERR;

		अवरोध;

	हाल IA_CSS_PIPE_ID_ACC:
		err = create_host_acc_pipeline(मुख्य_pipe);
		अगर (err)
			जाओ ERR;

		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	अगर (err)
		जाओ ERR;

	अगर (copy_pipe)
	अणु
		err = create_host_copy_pipeline(copy_pipe, max_input_width,
						मुख्य_pipe->continuous_frames[0]);
		अगर (err)
			जाओ ERR;
	पूर्ण

	अगर (capture_pipe)
	अणु
		err = create_host_capture_pipeline(capture_pipe);
		अगर (err)
			जाओ ERR;
	पूर्ण

	अगर (acc_pipe)
	अणु
		err = create_host_acc_pipeline(acc_pipe);
		अगर (err)
			जाओ ERR;
	पूर्ण

	/* DH regular multi pipe - not continuous mode: create the next pipelines too */
	अगर (!stream->config.continuous)
	अणु
		पूर्णांक i;

		क्रम (i = 1; i < stream->num_pipes && 0 == err; i++) अणु
			चयन (stream->pipes[i]->mode) अणु
			हाल IA_CSS_PIPE_ID_PREVIEW:
				err = create_host_preview_pipeline(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_VIDEO:
				err = create_host_video_pipeline(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_CAPTURE:
				err = create_host_capture_pipeline(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_YUVPP:
				err = create_host_yuvpp_pipeline(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_ACC:
				err = create_host_acc_pipeline(stream->pipes[i]);
				अवरोध;
			शेष:
				err = -EINVAL;
			पूर्ण
			अगर (err)
				जाओ ERR;
		पूर्ण
	पूर्ण

ERR:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा ia_css_pipe शेष_pipe = IA_CSS_DEFAULT_PIPE;
अटल स्थिर काष्ठा ia_css_preview_settings preview = IA_CSS_DEFAULT_PREVIEW_SETTINGS;
अटल स्थिर काष्ठा ia_css_capture_settings capture = IA_CSS_DEFAULT_CAPTURE_SETTINGS;
अटल स्थिर काष्ठा ia_css_video_settings video = IA_CSS_DEFAULT_VIDEO_SETTINGS;
अटल स्थिर काष्ठा ia_css_yuvpp_settings yuvpp = IA_CSS_DEFAULT_YUVPP_SETTINGS;

अटल पूर्णांक
init_pipe_शेषs(क्रमागत ia_css_pipe_mode mode,
		   काष्ठा ia_css_pipe *pipe,
		   bool copy_pipe) अणु

	अगर (!pipe)
	अणु
		IA_CSS_ERROR("NULL pipe parameter");
		वापस -EINVAL;
	पूर्ण

	/* Initialize pipe to pre-defined शेषs */
	स_नकल(pipe, &शेष_pipe, माप(शेष_pipe));

	/* TODO: JB should not be needed, but temporary backward reference */
	चयन (mode)
	अणु
	हाल IA_CSS_PIPE_MODE_PREVIEW:
		pipe->mode = IA_CSS_PIPE_ID_PREVIEW;
		स_नकल(&pipe->pipe_settings.preview, &preview, माप(preview));
		अवरोध;
	हाल IA_CSS_PIPE_MODE_CAPTURE:
		अगर (copy_pipe) अणु
			pipe->mode = IA_CSS_PIPE_ID_COPY;
		पूर्ण अन्यथा अणु
			pipe->mode = IA_CSS_PIPE_ID_CAPTURE;
		पूर्ण
		स_नकल(&pipe->pipe_settings.capture, &capture, माप(capture));
		अवरोध;
	हाल IA_CSS_PIPE_MODE_VIDEO:
		pipe->mode = IA_CSS_PIPE_ID_VIDEO;
		स_नकल(&pipe->pipe_settings.video, &video, माप(video));
		अवरोध;
	हाल IA_CSS_PIPE_MODE_ACC:
		pipe->mode = IA_CSS_PIPE_ID_ACC;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_COPY:
		pipe->mode = IA_CSS_PIPE_ID_CAPTURE;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_YUVPP:
		pipe->mode = IA_CSS_PIPE_ID_YUVPP;
		स_नकल(&pipe->pipe_settings.yuvpp, &yuvpp, माप(yuvpp));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
pipe_global_init(व्योम)
अणु
	u8 i;

	my_css.pipe_counter = 0;
	क्रम (i = 0; i < IA_CSS_PIPELINE_NUM_MAX; i++) अणु
		my_css.all_pipes[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
pipe_generate_pipe_num(स्थिर काष्ठा ia_css_pipe *pipe,
		       अचिन्हित पूर्णांक *pipe_number) अणु
	स्थिर u8 INVALID_PIPE_NUM = (uपूर्णांक8_t)~(0);
	u8 pipe_num = INVALID_PIPE_NUM;
	u8 i;

	अगर (!pipe)
	अणु
		IA_CSS_ERROR("NULL pipe parameter");
		वापस -EINVAL;
	पूर्ण

	/* Assign a new pipe_num .... search क्रम empty place */
	क्रम (i = 0; i < IA_CSS_PIPELINE_NUM_MAX; i++)
	अणु
		अगर (!my_css.all_pipes[i]) अणु
			/*position is reserved */
			my_css.all_pipes[i] = (काष्ठा ia_css_pipe *)pipe;
			pipe_num = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pipe_num == INVALID_PIPE_NUM)
	अणु
		/* Max number of pipes alपढ़ोy allocated */
		IA_CSS_ERROR("Max number of pipes already created");
		वापस -ENOSPC;
	पूर्ण

	my_css.pipe_counter++;

	IA_CSS_LOG("pipe_num (%d)", pipe_num);

	*pipe_number = pipe_num;
	वापस 0;
पूर्ण

अटल व्योम
pipe_release_pipe_num(अचिन्हित पूर्णांक pipe_num)
अणु
	my_css.all_pipes[pipe_num] = शून्य;
	my_css.pipe_counter--;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "pipe_release_pipe_num (%d)\n", pipe_num);
पूर्ण

अटल पूर्णांक
create_pipe(क्रमागत ia_css_pipe_mode mode,
	    काष्ठा ia_css_pipe **pipe,
	    bool copy_pipe) अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_pipe *me;

	अगर (!pipe)
	अणु
		IA_CSS_ERROR("NULL pipe parameter");
		वापस -EINVAL;
	पूर्ण

	me = kदो_स्मृति(माप(*me), GFP_KERNEL);
	अगर (!me)
		वापस -ENOMEM;

	err = init_pipe_शेषs(mode, me, copy_pipe);
	अगर (err)
	अणु
		kमुक्त(me);
		वापस err;
	पूर्ण

	err = pipe_generate_pipe_num(me, &me->pipe_num);
	अगर (err)
	अणु
		kमुक्त(me);
		वापस err;
	पूर्ण

	*pipe = me;
	वापस 0;
पूर्ण

काष्ठा ia_css_pipe *
find_pipe_by_num(uपूर्णांक32_t pipe_num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IA_CSS_PIPELINE_NUM_MAX; i++) अणु
		अगर (my_css.all_pipes[i] &&
		    ia_css_pipe_get_pipe_num(my_css.all_pipes[i]) == pipe_num) अणु
			वापस my_css.all_pipes[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम sh_css_pipe_मुक्त_acc_binaries(
    काष्ठा ia_css_pipe *pipe)
अणु
	काष्ठा ia_css_pipeline *pipeline;
	काष्ठा ia_css_pipeline_stage *stage;

	निश्चित(pipe);
	अगर (!pipe) अणु
		IA_CSS_ERROR("NULL input pointer");
		वापस;
	पूर्ण
	pipeline = &pipe->pipeline;

	/* loop through the stages and unload them */
	क्रम (stage = pipeline->stages; stage; stage = stage->next) अणु
		काष्ठा ia_css_fw_info *firmware = (काष्ठा ia_css_fw_info *)
						  stage->firmware;
		अगर (firmware)
			ia_css_pipe_unload_extension(pipe, firmware);
	पूर्ण
पूर्ण

पूर्णांक
ia_css_pipe_destroy(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER("pipe = %p", pipe);

	अगर (!pipe)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर (pipe->stream)
	अणु
		IA_CSS_LOG("ia_css_stream_destroy not called!");
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	चयन (pipe->config.mode)
	अणु
	हाल IA_CSS_PIPE_MODE_PREVIEW:
		/* need to take पूर्णांकo account that this function is also called
		   on the पूर्णांकernal copy pipe */
		अगर (pipe->mode == IA_CSS_PIPE_ID_PREVIEW) अणु
			ia_css_frame_मुक्त_multiple(NUM_CONTINUOUS_FRAMES,
						   pipe->continuous_frames);
			ia_css_metadata_मुक्त_multiple(NUM_CONTINUOUS_FRAMES,
						      pipe->cont_md_buffers);
			अगर (pipe->pipe_settings.preview.copy_pipe) अणु
				err = ia_css_pipe_destroy(pipe->pipe_settings.preview.copy_pipe);
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_pipe_destroy(): destroyed internal copy pipe err=%d\n",
						    err);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IA_CSS_PIPE_MODE_VIDEO:
		अगर (pipe->mode == IA_CSS_PIPE_ID_VIDEO) अणु
			ia_css_frame_मुक्त_multiple(NUM_CONTINUOUS_FRAMES,
						   pipe->continuous_frames);
			ia_css_metadata_मुक्त_multiple(NUM_CONTINUOUS_FRAMES,
						      pipe->cont_md_buffers);
			अगर (pipe->pipe_settings.video.copy_pipe) अणु
				err = ia_css_pipe_destroy(pipe->pipe_settings.video.copy_pipe);
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_pipe_destroy(): destroyed internal copy pipe err=%d\n",
						    err);
			पूर्ण
		पूर्ण
#अगर_अघोषित ISP2401
		ia_css_frame_मुक्त_multiple(NUM_TNR_FRAMES,
					   pipe->pipe_settings.video.tnr_frames);
#अन्यथा
		ia_css_frame_मुक्त_multiple(NUM_TNR_FRAMES,
					   pipe->pipe_settings.video.tnr_frames);
#पूर्ण_अगर
		ia_css_frame_मुक्त_multiple(MAX_NUM_VIDEO_DELAY_FRAMES,
					   pipe->pipe_settings.video.delay_frames);
		अवरोध;
	हाल IA_CSS_PIPE_MODE_CAPTURE:
		ia_css_frame_मुक्त_multiple(MAX_NUM_VIDEO_DELAY_FRAMES,
					   pipe->pipe_settings.capture.delay_frames);
		अवरोध;
	हाल IA_CSS_PIPE_MODE_ACC:
		sh_css_pipe_मुक्त_acc_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_MODE_COPY:
		अवरोध;
	हाल IA_CSS_PIPE_MODE_YUVPP:
		अवरोध;
	पूर्ण

	sh_css_params_मुक्त_gdc_lut(pipe->scaler_pp_lut);
	pipe->scaler_pp_lut = mmgr_शून्य;

	my_css.active_pipes[ia_css_pipe_get_pipe_num(pipe)] = शून्य;
	sh_css_pipe_मुक्त_shading_table(pipe);

	ia_css_pipeline_destroy(&pipe->pipeline);
	pipe_release_pipe_num(ia_css_pipe_get_pipe_num(pipe));

	/* Temporarily, not every sh_css_pipe has an acc_extension. */
	अगर (pipe->config.acc_extension)
	अणु
		ia_css_pipe_unload_extension(pipe, pipe->config.acc_extension);
	पूर्ण
	kमुक्त(pipe);
	IA_CSS_LEAVE("err = %d", err);
	वापस err;
पूर्ण

व्योम
ia_css_uninit(व्योम)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_uninit() enter: void\n");
#अगर WITH_PC_MONITORING
	sh_css_prपूर्णांक("PC_MONITORING: %s() -- started\n", __func__);
	prपूर्णांक_pc_histogram();
#पूर्ण_अगर

	sh_css_params_मुक्त_शेष_gdc_lut();

	/* TODO: JB: implement decent check and handling of मुक्तing mipi frames */
	//निश्चित(ref_count_mipi_allocation == 0); //mipi frames are not मुक्तd
	/* cleanup generic data */
	sh_css_params_uninit();
	ia_css_refcount_uninit();

	ia_css_rmgr_uninit();

#अगर !defined(ISP2401)
	/* needed क्रम reprogramming the inputक्रमmatter after घातer cycle of css */
	अगरmtr_set_अगर_blocking_mode_reset = true;
#पूर्ण_अगर

	अगर (!fw_explicitly_loaded) अणु
		ia_css_unload_firmware();
	पूर्ण
	ia_css_spctrl_unload_fw(SP0_ID);
	sh_css_sp_set_sp_running(false);
	/* check and मुक्त any reमुख्यing mipi frames */
	मुक्त_mipi_frames(शून्य);

	sh_css_sp_reset_global_vars();

	ia_css_isys_uninit();

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_uninit() leave: return_void\n");
पूर्ण

पूर्णांक ia_css_irq_translate(
    अचिन्हित पूर्णांक *irq_infos)
अणु
	क्रमागत virq_id	irq;
	क्रमागत hrt_isp_css_irq_status status = hrt_isp_css_irq_status_more_irqs;
	अचिन्हित पूर्णांक infos = 0;

	/* irq_infos can be शून्य, but that would make the function useless */
	/* निश्चित(irq_infos != शून्य); */
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_irq_translate() enter: irq_infos=%p\n", irq_infos);

	जबतक (status == hrt_isp_css_irq_status_more_irqs) अणु
		status = virq_get_channel_id(&irq);
		अगर (status == hrt_isp_css_irq_status_error)
			वापस -EINVAL;

#अगर WITH_PC_MONITORING
		sh_css_prपूर्णांक("PC_MONITORING: %s() irq = %d, sh_binary_running set to 0\n",
			     __func__, irq);
		sh_binary_running = 0;
#पूर्ण_अगर

		चयन (irq) अणु
		हाल virq_sp:
			/* When SP goes to idle, info is available in the
			 * event queue. */
			infos |= IA_CSS_IRQ_INFO_EVENTS_READY;
			अवरोध;
		हाल virq_isp:
			अवरोध;
		हाल virq_isys_sof:
			infos |= IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF;
			अवरोध;
		हाल virq_isys_eof:
			infos |= IA_CSS_IRQ_INFO_CSS_RECEIVER_खातापूर्ण;
			अवरोध;
		हाल virq_isys_csi:
			infos |= IA_CSS_IRQ_INFO_INPUT_SYSTEM_ERROR;
			अवरोध;
#अगर !defined(ISP2401)
		हाल virq_अगरmt0_id:
			infos |= IA_CSS_IRQ_INFO_IF_ERROR;
			अवरोध;
#पूर्ण_अगर
		हाल virq_dma:
			infos |= IA_CSS_IRQ_INFO_DMA_ERROR;
			अवरोध;
		हाल virq_sw_pin_0:
			infos |= sh_css_get_sw_पूर्णांकerrupt_value(0);
			अवरोध;
		हाल virq_sw_pin_1:
			infos |= sh_css_get_sw_पूर्णांकerrupt_value(1);
			/* pqiao TODO: also assumption here */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (irq_infos)
		*irq_infos = infos;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_irq_translate() leave: irq_infos=%u\n",
			    infos);

	वापस 0;
पूर्ण

पूर्णांक ia_css_irq_enable(
    क्रमागत ia_css_irq_info info,
    bool enable)
अणु
	क्रमागत virq_id	irq = N_virq_id;

	IA_CSS_ENTER("info=%d, enable=%d", info, enable);

	चयन (info) अणु
#अगर !defined(ISP2401)
	हाल IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF:
		irq = virq_isys_sof;
		अवरोध;
	हाल IA_CSS_IRQ_INFO_CSS_RECEIVER_खातापूर्ण:
		irq = virq_isys_eof;
		अवरोध;
	हाल IA_CSS_IRQ_INFO_INPUT_SYSTEM_ERROR:
		irq = virq_isys_csi;
		अवरोध;
	हाल IA_CSS_IRQ_INFO_IF_ERROR:
		irq = virq_अगरmt0_id;
		अवरोध;
#अन्यथा
	हाल IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF:
	हाल IA_CSS_IRQ_INFO_CSS_RECEIVER_खातापूर्ण:
	हाल IA_CSS_IRQ_INFO_INPUT_SYSTEM_ERROR:
	हाल IA_CSS_IRQ_INFO_IF_ERROR:
		/* Just ignore those unused IRQs without prपूर्णांकing errors */
		वापस 0;
#पूर्ण_अगर
	हाल IA_CSS_IRQ_INFO_DMA_ERROR:
		irq = virq_dma;
		अवरोध;
	हाल IA_CSS_IRQ_INFO_SW_0:
		irq = virq_sw_pin_0;
		अवरोध;
	हाल IA_CSS_IRQ_INFO_SW_1:
		irq = virq_sw_pin_1;
		अवरोध;
	शेष:
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	cnd_virq_enable_channel(irq, enable);

	IA_CSS_LEAVE_ERR(0);
	वापस 0;
पूर्ण


अटल अचिन्हित पूर्णांक
sh_css_get_sw_पूर्णांकerrupt_value(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक irq_value;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_get_sw_interrupt_value() enter: irq=%d\n", irq);
	irq_value = sh_css_sp_get_sw_पूर्णांकerrupt_value(irq);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_get_sw_interrupt_value() leave: irq_value=%d\n", irq_value);
	वापस irq_value;
पूर्ण

/* configure and load the copy binary, the next binary is used to
   determine whether the copy binary needs to करो left padding. */
अटल पूर्णांक load_copy_binary(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_binary *copy_binary,
    काष्ठा ia_css_binary *next_binary)
अणु
	काष्ठा ia_css_frame_info copy_out_info, copy_in_info, copy_vf_info;
	अचिन्हित पूर्णांक left_padding;
	पूर्णांक err;
	काष्ठा ia_css_binary_descr copy_descr;

	/* next_binary can be शून्य */
	निश्चित(pipe);
	निश्चित(copy_binary);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "load_copy_binary() enter:\n");

	अगर (next_binary) अणु
		copy_out_info = next_binary->in_frame_info;
		left_padding = next_binary->left_padding;
	पूर्ण अन्यथा अणु
		copy_out_info = pipe->output_info[0];
		copy_vf_info = pipe->vf_output_info[0];
		ia_css_frame_info_set_क्रमmat(&copy_vf_info, IA_CSS_FRAME_FORMAT_YUV_LINE);
		left_padding = 0;
	पूर्ण

	ia_css_pipe_get_copy_binarydesc(pipe, &copy_descr,
					&copy_in_info, &copy_out_info,
					(next_binary) ? शून्य : शून्य/*TODO: &copy_vf_info*/);
	err = ia_css_binary_find(&copy_descr, copy_binary);
	अगर (err)
		वापस err;
	copy_binary->left_padding = left_padding;
	वापस 0;
पूर्ण

अटल पूर्णांक
alloc_continuous_frames(
    काष्ठा ia_css_pipe *pipe, bool init_समय) अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_frame_info ref_info;
	क्रमागत ia_css_pipe_id pipe_id;
	bool continuous;
	अचिन्हित पूर्णांक i, idx;
	अचिन्हित पूर्णांक num_frames;

	IA_CSS_ENTER_PRIVATE("pipe = %p, init_time = %d", pipe, init_समय);

	अगर ((!pipe) || (!pipe->stream))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	pipe_id = pipe->mode;
	continuous = pipe->stream->config.continuous;

	अगर (continuous)
	अणु
		अगर (init_समय) अणु
			num_frames = pipe->stream->config.init_num_cont_raw_buf;
			pipe->stream->continuous_pipe = pipe;
		पूर्ण अन्यथा
			num_frames = pipe->stream->config.target_num_cont_raw_buf;
	पूर्ण अन्यथा
	अणु
		num_frames = NUM_ONLINE_INIT_CONTINUOUS_FRAMES;
	पूर्ण

	अगर (pipe_id == IA_CSS_PIPE_ID_PREVIEW)
	अणु
		ref_info = pipe->pipe_settings.preview.preview_binary.in_frame_info;
	पूर्ण अन्यथा अगर (pipe_id == IA_CSS_PIPE_ID_VIDEO)
	अणु
		ref_info = pipe->pipe_settings.video.video_binary.in_frame_info;
	पूर्ण अन्यथा
	अणु
		/* should not happen */
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

#अगर defined(ISP2401)
	/* For CSI2+, the continuous frame will hold the full input frame */
	ref_info.res.width = pipe->stream->config.input_config.input_res.width;
	ref_info.res.height = pipe->stream->config.input_config.input_res.height;

	/* Ensure padded width is aligned क्रम 2401 */
	ref_info.padded_width = CEIL_MUL(ref_info.res.width, 2 * ISP_VEC_NELEMS);
#पूर्ण_अगर

#अगर !defined(HAS_NO_PACKED_RAW_PIXELS)
	अगर (pipe->stream->config.pack_raw_pixels)
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "alloc_continuous_frames() IA_CSS_FRAME_FORMAT_RAW_PACKED\n");
		ref_info.क्रमmat = IA_CSS_FRAME_FORMAT_RAW_PACKED;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "alloc_continuous_frames() IA_CSS_FRAME_FORMAT_RAW\n");
		ref_info.क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	पूर्ण

	/* Write क्रमmat back to binary */
	अगर (pipe_id == IA_CSS_PIPE_ID_PREVIEW) अणु
		pipe->pipe_settings.preview.preview_binary.in_frame_info.क्रमmat =
		    ref_info.क्रमmat;
	पूर्ण अन्यथा अगर (pipe_id == IA_CSS_PIPE_ID_VIDEO) अणु
		pipe->pipe_settings.video.video_binary.in_frame_info.क्रमmat = ref_info.क्रमmat;
	पूर्ण अन्यथा अणु
		/* should not happen */
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर (init_समय)
		idx = 0;
	अन्यथा
		idx = pipe->stream->config.init_num_cont_raw_buf;

	क्रम (i = idx; i < NUM_CONTINUOUS_FRAMES; i++)
	अणु
		/* मुक्त previous frame */
		अगर (pipe->continuous_frames[i]) अणु
			ia_css_frame_मुक्त(pipe->continuous_frames[i]);
			pipe->continuous_frames[i] = शून्य;
		पूर्ण
		/* मुक्त previous metadata buffer */
		ia_css_metadata_मुक्त(pipe->cont_md_buffers[i]);
		pipe->cont_md_buffers[i] = शून्य;

		/* check अगर new frame needed */
		अगर (i < num_frames) अणु
			/* allocate new frame */
			err = ia_css_frame_allocate_from_info(
				  &pipe->continuous_frames[i],
				  &ref_info);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
			/* allocate metadata buffer */
			pipe->cont_md_buffers[i] = ia_css_metadata_allocate(
						       &pipe->stream->info.metadata_info);
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

पूर्णांक
ia_css_alloc_continuous_frame_reमुख्य(काष्ठा ia_css_stream *stream) अणु
	अगर (!stream)
		वापस -EINVAL;
	वापस alloc_continuous_frames(stream->continuous_pipe, false);
पूर्ण

अटल पूर्णांक
load_preview_binaries(काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_frame_info prev_in_info,
		prev_bds_out_info,
		prev_out_info,
		prev_vf_info;
	काष्ठा ia_css_binary_descr preview_descr;
	bool online;
	पूर्णांक err = 0;
	bool need_vf_pp = false;
	bool need_isp_copy_binary = false;
#अगर_घोषित ISP2401
	bool sensor = false;
#अन्यथा
	bool continuous;
#पूर्ण_अगर
	/* preview only have 1 output pin now */
	काष्ठा ia_css_frame_info *pipe_out_info = &pipe->output_info[0];
	काष्ठा ia_css_preview_settings *mycs  = &pipe->pipe_settings.preview;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->stream);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_PREVIEW);

	online = pipe->stream->config.online;
#अगर_घोषित ISP2401
	sensor = pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR;
#अन्यथा
	continuous = pipe->stream->config.continuous;
#पूर्ण_अगर

	अगर (mycs->preview_binary.info)
		वापस 0;

	err = ia_css_util_check_input(&pipe->stream->config, false, false);
	अगर (err)
		वापस err;
	err = ia_css_frame_check_info(pipe_out_info);
	अगर (err)
		वापस err;

	/* Note: the current selection of vf_pp binary and
	 * parameterization of the preview binary contains a few pieces
	 * of hardcoded knowledge. This needs to be cleaned up such that
	 * the binary selection becomes more generic.
	 * The vf_pp binary is needed अगर one or more of the following features
	 * are required:
	 * 1. YUV करोwnscaling.
	 * 2. Digital zoom.
	 * 3. An output क्रमmat that is not supported by the preview binary.
	 *    In practice this means something other than yuv_line or nv12.
	 * The decision अगर the vf_pp binary is needed क्रम YUV करोwnscaling is
	 * made after the preview binary selection, since some preview binaries
	 * can perक्रमm the requested YUV करोwnscaling.
	 * */
	need_vf_pp = pipe->config.enable_dz;
	need_vf_pp |= pipe_out_info->क्रमmat != IA_CSS_FRAME_FORMAT_YUV_LINE &&
	!(pipe_out_info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12 ||
	  pipe_out_info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12_16 ||
	  pipe_out_info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12_TILEY);

	/* Preview step 1 */
	अगर (pipe->vf_yuv_ds_input_info.res.width)
		prev_vf_info = pipe->vf_yuv_ds_input_info;
	अन्यथा
		prev_vf_info = *pipe_out_info;
	/* If vf_pp is needed, then preview must output yuv_line.
	 * The exception is when vf_pp is manually disabled, that is only
	 * used in combination with a pipeline extension that requires
	 * yuv_line as input.
	 * */
	अगर (need_vf_pp)
		ia_css_frame_info_set_क्रमmat(&prev_vf_info,
					     IA_CSS_FRAME_FORMAT_YUV_LINE);

	err = ia_css_pipe_get_preview_binarydesc(
	    pipe,
	    &preview_descr,
	    &prev_in_info,
	    &prev_bds_out_info,
	    &prev_out_info,
	    &prev_vf_info);
	अगर (err)
		वापस err;
	err = ia_css_binary_find(&preview_descr, &mycs->preview_binary);
	अगर (err)
		वापस err;

	अगर (IS_ISP2401) अणु
		/* The delay latency determines the number of invalid frames after
		* a stream is started. */
		pipe->num_invalid_frames = pipe->dvs_frame_delay;
		pipe->info.num_invalid_frames = pipe->num_invalid_frames;

		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "load_preview_binaries() num_invalid_frames=%d dvs_frame_delay=%d\n",
				    pipe->num_invalid_frames, pipe->dvs_frame_delay);
	पूर्ण

	/* The vf_pp binary is needed when (further) YUV करोwnscaling is required */
	need_vf_pp |= mycs->preview_binary.out_frame_info[0].res.width != pipe_out_info->res.width;
	need_vf_pp |= mycs->preview_binary.out_frame_info[0].res.height != pipe_out_info->res.height;

	/* When vf_pp is needed, then the output क्रमmat of the selected
	 * preview binary must be yuv_line. If this is not the हाल,
	 * then the preview binary selection is करोne again.
	 */
	अगर (need_vf_pp &&
	    (mycs->preview_binary.out_frame_info[0].क्रमmat != IA_CSS_FRAME_FORMAT_YUV_LINE))
	अणु
		/* Preview step 2 */
		अगर (pipe->vf_yuv_ds_input_info.res.width)
			prev_vf_info = pipe->vf_yuv_ds_input_info;
		अन्यथा
			prev_vf_info = *pipe_out_info;

		ia_css_frame_info_set_क्रमmat(&prev_vf_info,
					     IA_CSS_FRAME_FORMAT_YUV_LINE);

		err = ia_css_pipe_get_preview_binarydesc(
		    pipe,
		    &preview_descr,
		    &prev_in_info,
		    &prev_bds_out_info,
		    &prev_out_info,
		    &prev_vf_info);
		अगर (err)
			वापस err;
		err = ia_css_binary_find(&preview_descr,
					 &mycs->preview_binary);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (need_vf_pp)
	अणु
		काष्ठा ia_css_binary_descr vf_pp_descr;

		/* Viewfinder post-processing */
		ia_css_pipe_get_vfpp_binarydesc(pipe, &vf_pp_descr,
						&mycs->preview_binary.out_frame_info[0],
						pipe_out_info);
		err = ia_css_binary_find(&vf_pp_descr,
					 &mycs->vf_pp_binary);
		अगर (err)
			वापस err;
	पूर्ण

#अगर_घोषित ISP2401
	/* When the input प्रणाली is 2401, only the Direct Sensor Mode
	 * Offline Preview uses the ISP copy binary.
	 */
	need_isp_copy_binary = !online && sensor;
#अन्यथा
	/* About pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY:
	 * This is typical the हाल with SkyCam (which has no input प्रणाली) but it also applies to all हालs
	 * where the driver chooses क्रम memory based input frames. In these हालs, a copy binary (which typical
	 * copies sensor data to DDR) करोes not have much use.
	 */
	अगर (!IS_ISP2401)
		need_isp_copy_binary = !online && !continuous;
	अन्यथा
		need_isp_copy_binary = !online && !continuous && !(pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY);
#पूर्ण_अगर

	/* Copy */
	अगर (need_isp_copy_binary)
	अणु
		err = load_copy_binary(pipe,
				       &mycs->copy_binary,
				       &mycs->preview_binary);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pipe->shading_table)
	अणु
		ia_css_shading_table_मुक्त(pipe->shading_table);
		pipe->shading_table = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
ia_css_binary_unload(काष्ठा ia_css_binary *binary)
अणु
	ia_css_binary_destroy_isp_parameters(binary);
पूर्ण

अटल पूर्णांक
unload_preview_binaries(काष्ठा ia_css_pipe *pipe) अणु
	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);

	अगर ((!pipe) || (pipe->mode != IA_CSS_PIPE_ID_PREVIEW))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	ia_css_binary_unload(&pipe->pipe_settings.preview.copy_binary);
	ia_css_binary_unload(&pipe->pipe_settings.preview.preview_binary);
	ia_css_binary_unload(&pipe->pipe_settings.preview.vf_pp_binary);

	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ia_css_fw_info *last_output_firmware(
    स्थिर काष्ठा ia_css_fw_info *fw)
अणु
	स्थिर काष्ठा ia_css_fw_info *last_fw = शून्य;
	/* fw can be शून्य */
	IA_CSS_ENTER_LEAVE_PRIVATE("");

	क्रम (; fw; fw = fw->next) अणु
		स्थिर काष्ठा ia_css_fw_info *info = fw;

		अगर (info->info.isp.sp.enable.output)
			last_fw = fw;
	पूर्ण
	वापस last_fw;
पूर्ण

अटल पूर्णांक add_firmwares(
    काष्ठा ia_css_pipeline *me,
    काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_fw_info *fw,
    स्थिर काष्ठा ia_css_fw_info *last_fw,
    अचिन्हित पूर्णांक binary_mode,
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *out_frame,
    काष्ठा ia_css_frame *vf_frame,
    काष्ठा ia_css_pipeline_stage **my_stage,
    काष्ठा ia_css_pipeline_stage **vf_stage)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_pipeline_stage *extra_stage = शून्य;
	काष्ठा ia_css_pipeline_stage_desc stage_desc;

	/* all args can be शून्य ??? */
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "add_firmwares() enter:\n");

	क्रम (; fw; fw = fw->next) अणु
		काष्ठा ia_css_frame *out[IA_CSS_BINARY_MAX_OUTPUT_PORTS] = अणुशून्यपूर्ण;
		काष्ठा ia_css_frame *in = शून्य;
		काष्ठा ia_css_frame *vf = शून्य;

		अगर ((fw == last_fw) && (fw->info.isp.sp.enable.out_frame  != 0)) अणु
			out[0] = out_frame;
		पूर्ण
		अगर (fw->info.isp.sp.enable.in_frame != 0) अणु
			in = in_frame;
		पूर्ण
		अगर (fw->info.isp.sp.enable.out_frame != 0) अणु
			vf = vf_frame;
		पूर्ण
		ia_css_pipe_get_firmwares_stage_desc(&stage_desc, binary,
						     out, in, vf, fw, binary_mode);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			&extra_stage);
		अगर (err)
			वापस err;
		अगर (fw->info.isp.sp.enable.output != 0)
			in_frame = extra_stage->args.out_frame[0];
		अगर (my_stage && !*my_stage && extra_stage)
			*my_stage = extra_stage;
		अगर (vf_stage && !*vf_stage && extra_stage &&
		    fw->info.isp.sp.enable.vf_veceven)
			*vf_stage = extra_stage;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक add_vf_pp_stage(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *out_frame,
    काष्ठा ia_css_binary *vf_pp_binary,
    काष्ठा ia_css_pipeline_stage **vf_pp_stage)
अणु
	काष्ठा ia_css_pipeline *me = शून्य;
	स्थिर काष्ठा ia_css_fw_info *last_fw = शून्य;
	पूर्णांक err = 0;
	काष्ठा ia_css_frame *out_frames[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_pipeline_stage_desc stage_desc;

	/* out_frame can be शून्य ??? */

	अगर (!pipe)
		वापस -EINVAL;
	अगर (!in_frame)
		वापस -EINVAL;
	अगर (!vf_pp_binary)
		वापस -EINVAL;
	अगर (!vf_pp_stage)
		वापस -EINVAL;

	ia_css_pipe_util_create_output_frames(out_frames);
	me = &pipe->pipeline;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "add_vf_pp_stage() enter:\n");

	*vf_pp_stage = शून्य;

	last_fw = last_output_firmware(pipe->vf_stage);
	अगर (!pipe->extra_config.disable_vf_pp) अणु
		अगर (last_fw) अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, vf_pp_binary,
							   out_frames, in_frame, शून्य);
		पूर्ण अन्यथा अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, vf_pp_binary,
							   out_frames, in_frame, शून्य);
		पूर्ण
		err = ia_css_pipeline_create_and_add_stage(me, &stage_desc, vf_pp_stage);
		अगर (err)
			वापस err;
		in_frame = (*vf_pp_stage)->args.out_frame[0];
	पूर्ण
	err = add_firmwares(me, vf_pp_binary, pipe->vf_stage, last_fw,
			    IA_CSS_BINARY_MODE_VF_PP,
			    in_frame, out_frame, शून्य,
			    vf_pp_stage, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक add_yuv_scaler_stage(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_pipeline *me,
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *out_frame,
    काष्ठा ia_css_frame *पूर्णांकernal_out_frame,
    काष्ठा ia_css_binary *yuv_scaler_binary,
    काष्ठा ia_css_pipeline_stage **pre_vf_pp_stage)
अणु
	स्थिर काष्ठा ia_css_fw_info *last_fw;
	पूर्णांक err = 0;
	काष्ठा ia_css_frame *vf_frame = शून्य;
	काष्ठा ia_css_frame *out_frames[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_pipeline_stage_desc stage_desc;

	/* out_frame can be शून्य ??? */
	निश्चित(in_frame);
	निश्चित(pipe);
	निश्चित(me);
	निश्चित(yuv_scaler_binary);
	निश्चित(pre_vf_pp_stage);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "add_yuv_scaler_stage() enter:\n");

	*pre_vf_pp_stage = शून्य;
	ia_css_pipe_util_create_output_frames(out_frames);

	last_fw = last_output_firmware(pipe->output_stage);

	अगर (last_fw) अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc,
						   yuv_scaler_binary, out_frames, in_frame, vf_frame);
	पूर्ण अन्यथा अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
		ia_css_pipe_util_set_output_frames(out_frames, 1, पूर्णांकernal_out_frame);
		ia_css_pipe_get_generic_stage_desc(&stage_desc,
						   yuv_scaler_binary, out_frames, in_frame, vf_frame);
	पूर्ण
	err = ia_css_pipeline_create_and_add_stage(me,
		&stage_desc,
		pre_vf_pp_stage);
	अगर (err)
		वापस err;
	in_frame = (*pre_vf_pp_stage)->args.out_frame[0];

	err = add_firmwares(me, yuv_scaler_binary, pipe->output_stage, last_fw,
			    IA_CSS_BINARY_MODE_CAPTURE_PP,
			    in_frame, out_frame, vf_frame,
			    शून्य, pre_vf_pp_stage);
	/* If a firmware produce vf_pp output, we set that as vf_pp input */
	(*pre_vf_pp_stage)->args.vf_करोwnscale_log2 =
	    yuv_scaler_binary->vf_करोwnscale_log2;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "add_yuv_scaler_stage() leave:\n");
	वापस err;
पूर्ण

अटल पूर्णांक add_capture_pp_stage(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_pipeline *me,
    काष्ठा ia_css_frame *in_frame,
    काष्ठा ia_css_frame *out_frame,
    काष्ठा ia_css_binary *capture_pp_binary,
    काष्ठा ia_css_pipeline_stage **capture_pp_stage)
अणु
	स्थिर काष्ठा ia_css_fw_info *last_fw = शून्य;
	पूर्णांक err = 0;
	काष्ठा ia_css_frame *vf_frame = शून्य;
	काष्ठा ia_css_frame *out_frames[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_pipeline_stage_desc stage_desc;

	/* out_frame can be शून्य ??? */
	निश्चित(in_frame);
	निश्चित(pipe);
	निश्चित(me);
	निश्चित(capture_pp_binary);
	निश्चित(capture_pp_stage);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "add_capture_pp_stage() enter:\n");

	*capture_pp_stage = शून्य;
	ia_css_pipe_util_create_output_frames(out_frames);

	last_fw = last_output_firmware(pipe->output_stage);
	err = ia_css_frame_allocate_from_info(&vf_frame,
					      &capture_pp_binary->vf_frame_info);
	अगर (err)
		वापस err;
	अगर (last_fw)	अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc,
						   capture_pp_binary, out_frames, शून्य, vf_frame);
	पूर्ण अन्यथा अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
		ia_css_pipe_get_generic_stage_desc(&stage_desc,
						   capture_pp_binary, out_frames, शून्य, vf_frame);
	पूर्ण
	err = ia_css_pipeline_create_and_add_stage(me,
		&stage_desc,
		capture_pp_stage);
	अगर (err)
		वापस err;
	err = add_firmwares(me, capture_pp_binary, pipe->output_stage, last_fw,
			    IA_CSS_BINARY_MODE_CAPTURE_PP,
			    in_frame, out_frame, vf_frame,
			    शून्य, capture_pp_stage);
	/* If a firmware produce vf_pp output, we set that as vf_pp input */
	अगर (*capture_pp_stage) अणु
		(*capture_pp_stage)->args.vf_करोwnscale_log2 =
		    capture_pp_binary->vf_करोwnscale_log2;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम sh_css_setup_queues(व्योम)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_queues_initialized;

	sh_css_hmm_buffer_record_init();

	sh_css_event_init_irq_mask();

	fw = &sh_css_sp_fw;
	HIVE_ADDR_host_sp_queues_initialized =
	    fw->info.sp.host_sp_queues_initialized;

	ia_css_bufq_init();

	/* set "host_sp_queues_initialized" to "true" */
	sp_dmem_store_uपूर्णांक32(SP0_ID,
			     (अचिन्हित पूर्णांक)sp_address_of(host_sp_queues_initialized),
			     (uपूर्णांक32_t)(1));
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "sh_css_setup_queues() leave:\n");
पूर्ण

अटल पूर्णांक
init_vf_frameinfo_शेषs(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_frame *vf_frame, अचिन्हित पूर्णांक idx) अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक thपढ़ो_id;
	क्रमागत sh_css_queue_id queue_id;

	निश्चित(vf_frame);

	sh_css_pipe_get_viewfinder_frame_info(pipe, &vf_frame->info, idx);
	vf_frame->contiguous = false;
	vf_frame->flash_state = IA_CSS_FRAME_FLASH_STATE_NONE;
	ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
	ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME + idx, thपढ़ो_id, &queue_id);
	vf_frame->dynamic_queue_id = queue_id;
	vf_frame->buf_type = IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME + idx;

	err = ia_css_frame_init_planes(vf_frame);
	वापस err;
पूर्ण

#अगर_घोषित ISP2401
अटल अचिन्हित पूर्णांक
get_crop_lines_क्रम_bayer_order(
    स्थिर काष्ठा ia_css_stream_config *config)
अणु
	निश्चित(config);
	अगर ((config->input_config.bayer_order == IA_CSS_BAYER_ORDER_BGGR)
	    || (config->input_config.bayer_order == IA_CSS_BAYER_ORDER_GBRG))
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
get_crop_columns_क्रम_bayer_order(
    स्थिर काष्ठा ia_css_stream_config *config)
अणु
	निश्चित(config);
	अगर ((config->input_config.bayer_order == IA_CSS_BAYER_ORDER_RGGB)
	    || (config->input_config.bayer_order == IA_CSS_BAYER_ORDER_GBRG))
		वापस 1;

	वापस 0;
पूर्ण

/* This function is to get the sum of all extra pixels in addition to the effective
 * input, it includes dvs envelop and filter run-in */
अटल व्योम get_pipe_extra_pixel(काष्ठा ia_css_pipe *pipe,
				 अचिन्हित पूर्णांक *extra_row, अचिन्हित पूर्णांक *extra_column)
अणु
	क्रमागत ia_css_pipe_id pipe_id = pipe->mode;
	अचिन्हित पूर्णांक left_cropping = 0, top_cropping = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_resolution dvs_env = pipe->config.dvs_envelope;

	/* The dvs envelope info may not be correctly sent करोwn via pipe config
	 * The check is made and the correct value is populated in the binary info
	 * Use this value when computing crop, अन्यथा excess lines may get trimmed
	 */
	चयन (pipe_id) अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		अगर (pipe->pipe_settings.preview.preview_binary.info) अणु
			left_cropping =
			    pipe->pipe_settings.preview.preview_binary.info->sp.pipeline.left_cropping;
			top_cropping =
			    pipe->pipe_settings.preview.preview_binary.info->sp.pipeline.top_cropping;
		पूर्ण
		dvs_env = pipe->pipe_settings.preview.preview_binary.dvs_envelope;
		अवरोध;
	हाल IA_CSS_PIPE_ID_VIDEO:
		अगर (pipe->pipe_settings.video.video_binary.info) अणु
			left_cropping =
			    pipe->pipe_settings.video.video_binary.info->sp.pipeline.left_cropping;
			top_cropping =
			    pipe->pipe_settings.video.video_binary.info->sp.pipeline.top_cropping;
		पूर्ण
		dvs_env = pipe->pipe_settings.video.video_binary.dvs_envelope;
		अवरोध;
	हाल IA_CSS_PIPE_ID_CAPTURE:
		क्रम (i = 0; i < pipe->pipe_settings.capture.num_primary_stage; i++) अणु
			अगर (pipe->pipe_settings.capture.primary_binary[i].info) अणु
				left_cropping +=
				    pipe->pipe_settings.capture.primary_binary[i].info->sp.pipeline.left_cropping;
				top_cropping +=
				    pipe->pipe_settings.capture.primary_binary[i].info->sp.pipeline.top_cropping;
			पूर्ण
			dvs_env.width +=
			    pipe->pipe_settings.capture.primary_binary[i].dvs_envelope.width;
			dvs_env.height +=
			    pipe->pipe_settings.capture.primary_binary[i].dvs_envelope.height;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	*extra_row = top_cropping + dvs_env.height;
	*extra_column = left_cropping + dvs_env.width;
पूर्ण

व्योम
ia_css_get_crop_offsets(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_frame_info *in_frame)
अणु
	अचिन्हित पूर्णांक row = 0;
	अचिन्हित पूर्णांक column = 0;
	काष्ठा ia_css_resolution *input_res;
	काष्ठा ia_css_resolution *effective_res;
	अचिन्हित पूर्णांक extra_row = 0, extra_col = 0;
	अचिन्हित पूर्णांक min_reqd_height, min_reqd_width;

	निश्चित(pipe);
	निश्चित(pipe->stream);
	निश्चित(in_frame);

	IA_CSS_ENTER_PRIVATE("pipe = %p effective_wd = %u effective_ht = %u",
			     pipe, pipe->config.input_effective_res.width,
			     pipe->config.input_effective_res.height);

	input_res = &pipe->stream->config.input_config.input_res;
#अगर_अघोषित ISP2401
	effective_res = &pipe->stream->config.input_config.effective_res;
#अन्यथा
	effective_res = &pipe->config.input_effective_res;
#पूर्ण_अगर

	get_pipe_extra_pixel(pipe, &extra_row, &extra_col);

	in_frame->raw_bayer_order = pipe->stream->config.input_config.bayer_order;

	min_reqd_height = effective_res->height + extra_row;
	min_reqd_width = effective_res->width + extra_col;

	अगर (input_res->height > min_reqd_height) अणु
		row = (input_res->height - min_reqd_height) / 2;
		row &= ~0x1;
	पूर्ण
	अगर (input_res->width > min_reqd_width) अणु
		column = (input_res->width - min_reqd_width) / 2;
		column &= ~0x1;
	पूर्ण

	/*
	 * TODO:
	 * 1. Require the special support क्रम RAW10 packed mode.
	 * 2. Require the special support क्रम the online use हालs.
	 */

	/* ISP expects GRBG bayer order, we skip one line and/or one row
	 * to correct in हाल the input bayer order is dअगरferent.
	 */
	column += get_crop_columns_क्रम_bayer_order(&pipe->stream->config);
	row += get_crop_lines_क्रम_bayer_order(&pipe->stream->config);

	in_frame->crop_info.start_column = column;
	in_frame->crop_info.start_line = row;

	IA_CSS_LEAVE_PRIVATE("void start_col: %u start_row: %u", column, row);

	वापस;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
init_in_frameinfo_memory_शेषs(काष्ठा ia_css_pipe *pipe,
				  काष्ठा ia_css_frame *frame, क्रमागत ia_css_frame_क्रमmat क्रमmat) अणु
	काष्ठा ia_css_frame *in_frame;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक thपढ़ो_id;
	क्रमागत sh_css_queue_id queue_id;

	निश्चित(frame);
	in_frame = frame;

	in_frame->info.क्रमmat = क्रमmat;

#अगर_घोषित ISP2401
	अगर (क्रमmat == IA_CSS_FRAME_FORMAT_RAW)
		in_frame->info.क्रमmat = (pipe->stream->config.pack_raw_pixels) ?
		IA_CSS_FRAME_FORMAT_RAW_PACKED : IA_CSS_FRAME_FORMAT_RAW;
#पूर्ण_अगर

	in_frame->info.res.width = pipe->stream->config.input_config.input_res.width;
	in_frame->info.res.height = pipe->stream->config.input_config.input_res.height;
	in_frame->info.raw_bit_depth =
	ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	ia_css_frame_info_set_width(&in_frame->info, pipe->stream->config.input_config.input_res.width, 0);
	in_frame->contiguous = false;
	in_frame->flash_state = IA_CSS_FRAME_FLASH_STATE_NONE;
	ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
	ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_INPUT_FRAME, thपढ़ो_id, &queue_id);
	in_frame->dynamic_queue_id = queue_id;
	in_frame->buf_type = IA_CSS_BUFFER_TYPE_INPUT_FRAME;
#अगर_घोषित ISP2401
	ia_css_get_crop_offsets(pipe, &in_frame->info);
#पूर्ण_अगर
	err = ia_css_frame_init_planes(in_frame);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "init_in_frameinfo_memory_defaults() bayer_order = %d:\n", in_frame->info.raw_bayer_order);

	वापस err;
पूर्ण

अटल पूर्णांक
init_out_frameinfo_शेषs(काष्ठा ia_css_pipe *pipe,
			    काष्ठा ia_css_frame *out_frame, अचिन्हित पूर्णांक idx) अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक thपढ़ो_id;
	क्रमागत sh_css_queue_id queue_id;

	निश्चित(out_frame);

	sh_css_pipe_get_output_frame_info(pipe, &out_frame->info, idx);
	out_frame->contiguous = false;
	out_frame->flash_state = IA_CSS_FRAME_FLASH_STATE_NONE;
	ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
	ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_OUTPUT_FRAME + idx, thपढ़ो_id, &queue_id);
	out_frame->dynamic_queue_id = queue_id;
	out_frame->buf_type = IA_CSS_BUFFER_TYPE_OUTPUT_FRAME + idx;
	err = ia_css_frame_init_planes(out_frame);

	वापस err;
पूर्ण

/* Create stages क्रम video pipe */
अटल पूर्णांक create_host_video_pipeline(काष्ठा ia_css_pipe *pipe)
अणु
	काष्ठा ia_css_pipeline_stage_desc stage_desc;
	काष्ठा ia_css_binary *copy_binary, *video_binary,
		       *yuv_scaler_binary, *vf_pp_binary;
	काष्ठा ia_css_pipeline_stage *copy_stage  = शून्य;
	काष्ठा ia_css_pipeline_stage *video_stage = शून्य;
	काष्ठा ia_css_pipeline_stage *yuv_scaler_stage  = शून्य;
	काष्ठा ia_css_pipeline_stage *vf_pp_stage = शून्य;
	काष्ठा ia_css_pipeline *me;
	काष्ठा ia_css_frame *in_frame = शून्य;
	काष्ठा ia_css_frame *out_frame;
	काष्ठा ia_css_frame *out_frames[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_frame *vf_frame = शून्य;
	पूर्णांक err = 0;
	bool need_copy   = false;
	bool need_vf_pp  = false;
	bool need_yuv_pp = false;
	bool need_in_frameinfo_memory = false;

	अचिन्हित पूर्णांक i, num_yuv_scaler;
	bool *is_output_stage = शून्य;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (!pipe->stream) || (pipe->mode != IA_CSS_PIPE_ID_VIDEO)) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	ia_css_pipe_util_create_output_frames(out_frames);
	out_frame = &pipe->out_frame_काष्ठा;

	/* pipeline alपढ़ोy created as part of create_host_pipeline_काष्ठाure */
	me = &pipe->pipeline;
	ia_css_pipeline_clean(me);

	me->dvs_frame_delay = pipe->dvs_frame_delay;

#अगर_घोषित ISP2401
	/* When the input प्रणाली is 2401, always enable 'in_frameinfo_memory'
	 * except क्रम the following: online or continuous
	 */
	need_in_frameinfo_memory = !(pipe->stream->config.online ||
				     pipe->stream->config.continuous);
#अन्यथा
	/* Conकाष्ठा in_frame info (only in हाल we have dynamic input */
	need_in_frameinfo_memory = pipe->stream->config.mode ==
				   IA_CSS_INPUT_MODE_MEMORY;
#पूर्ण_अगर

	/* Conकाष्ठा in_frame info (only in हाल we have dynamic input */
	अगर (need_in_frameinfo_memory) अणु
		in_frame = &pipe->in_frame_काष्ठा;
		err = init_in_frameinfo_memory_शेषs(pipe, in_frame,
							IA_CSS_FRAME_FORMAT_RAW);
		अगर (err)
			जाओ ERR;
	पूर्ण

	out_frame->data = 0;
	err = init_out_frameinfo_शेषs(pipe, out_frame, 0);
	अगर (err)
		जाओ ERR;

	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0]) अणु
		vf_frame = &pipe->vf_frame_काष्ठा;
		vf_frame->data = 0;
		err = init_vf_frameinfo_शेषs(pipe, vf_frame, 0);
		अगर (err)
			जाओ ERR;
	पूर्ण

	copy_binary  = &pipe->pipe_settings.video.copy_binary;
	video_binary = &pipe->pipe_settings.video.video_binary;
	vf_pp_binary = &pipe->pipe_settings.video.vf_pp_binary;

	yuv_scaler_binary = pipe->pipe_settings.video.yuv_scaler_binary;
	num_yuv_scaler  = pipe->pipe_settings.video.num_yuv_scaler;
	is_output_stage = pipe->pipe_settings.video.is_output_stage;

	need_copy   = (copy_binary && copy_binary->info);
	need_vf_pp  = (vf_pp_binary && vf_pp_binary->info);
	need_yuv_pp = (yuv_scaler_binary && yuv_scaler_binary->info);

	अगर (need_copy) अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
						   out_frames, शून्य, शून्य);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			&copy_stage);
		अगर (err)
			जाओ ERR;
		in_frame = me->stages->args.out_frame[0];
	पूर्ण अन्यथा अगर (pipe->stream->config.continuous) अणु
#अगर_घोषित ISP2401
		/* When continuous is enabled, configure in_frame with the
		 * last pipe, which is the copy pipe.
		 */
		in_frame = pipe->stream->last_pipe->continuous_frames[0];
#अन्यथा
		in_frame = pipe->continuous_frames[0];
#पूर्ण_अगर
	पूर्ण

	ia_css_pipe_util_set_output_frames(out_frames, 0,
					   need_yuv_pp ? शून्य : out_frame);

	/* when the video binary supports a second output pin,
	   it can directly produce the vf_frame.  */
	अगर (need_vf_pp) अणु
		ia_css_pipe_get_generic_stage_desc(&stage_desc, video_binary,
						   out_frames, in_frame, शून्य);
	पूर्ण अन्यथा अणु
		ia_css_pipe_get_generic_stage_desc(&stage_desc, video_binary,
						   out_frames, in_frame, vf_frame);
	पूर्ण
	err = ia_css_pipeline_create_and_add_stage(me,
		&stage_desc,
		&video_stage);
	अगर (err)
		जाओ ERR;

	/* If we use copy iso video, the input must be yuv iso raw */
	अगर (video_stage) अणु
		video_stage->args.copy_vf =
		    video_binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_COPY;
		video_stage->args.copy_output = video_stage->args.copy_vf;
	पूर्ण

	/* when the video binary supports only 1 output pin, vf_pp is needed to
	produce the vf_frame.*/
	अगर (need_vf_pp && video_stage) अणु
		in_frame = video_stage->args.out_vf_frame;
		err = add_vf_pp_stage(pipe, in_frame, vf_frame, vf_pp_binary,
				      &vf_pp_stage);
		अगर (err)
			जाओ ERR;
	पूर्ण
	अगर (video_stage) अणु
		पूर्णांक frm;

		क्रम (frm = 0; frm < NUM_TNR_FRAMES; frm++) अणु
			video_stage->args.tnr_frames[frm] =
			    pipe->pipe_settings.video.tnr_frames[frm];
		पूर्ण
		क्रम (frm = 0; frm < MAX_NUM_VIDEO_DELAY_FRAMES; frm++) अणु
			video_stage->args.delay_frames[frm] =
			    pipe->pipe_settings.video.delay_frames[frm];
		पूर्ण
	पूर्ण

	/* Append Extension on Video out, अगर enabled */
	अगर (!need_vf_pp && video_stage && pipe->config.acc_extension &&
	    (pipe->config.acc_extension->info.isp.type == IA_CSS_ACC_OUTPUT)) अणु
		काष्ठा ia_css_frame *out = शून्य;
		काष्ठा ia_css_frame *in = शून्य;

		अगर ((pipe->config.acc_extension->info.isp.sp.enable.output) &&
		    (pipe->config.acc_extension->info.isp.sp.enable.in_frame) &&
		    (pipe->config.acc_extension->info.isp.sp.enable.out_frame)) अणु
			/* In/Out Frame mapping to support output frame extension.*/
			out = video_stage->args.out_frame[0];
			err = ia_css_frame_allocate_from_info(&in, &pipe->output_info[0]);
			अगर (err)
				जाओ ERR;
			video_stage->args.out_frame[0] = in;
		पूर्ण

		err = add_firmwares(me, video_binary, pipe->output_stage,
				    last_output_firmware(pipe->output_stage),
				    IA_CSS_BINARY_MODE_VIDEO,
				    in, out, शून्य, &video_stage, शून्य);
		अगर (err)
			जाओ ERR;
	पूर्ण

	अगर (need_yuv_pp && video_stage) अणु
		काष्ठा ia_css_frame *पंचांगp_in_frame = video_stage->args.out_frame[0];
		काष्ठा ia_css_frame *पंचांगp_out_frame = शून्य;

		क्रम (i = 0; i < num_yuv_scaler; i++) अणु
			अगर (is_output_stage[i]) अणु
				पंचांगp_out_frame = out_frame;
			पूर्ण अन्यथा अणु
				पंचांगp_out_frame = शून्य;
			पूर्ण
			err = add_yuv_scaler_stage(pipe, me, पंचांगp_in_frame, पंचांगp_out_frame,
						   शून्य,
						   &yuv_scaler_binary[i],
						   &yuv_scaler_stage);

			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
			/* we use output port 1 as पूर्णांकernal output port */
			अगर (yuv_scaler_stage)
				पंचांगp_in_frame = yuv_scaler_stage->args.out_frame[1];
		पूर्ण
	पूर्ण

	pipe->pipeline.acquire_isp_each_stage = false;
	ia_css_pipeline_finalize_stages(&pipe->pipeline,
					pipe->stream->config.continuous);

ERR:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल पूर्णांक
create_host_acc_pipeline(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (!pipe->stream))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	pipe->pipeline.num_execs = pipe->config.acc_num_execs;
	/* Reset pipe_qos_config to शेष disable all QOS extension stages */
	अगर (pipe->config.acc_extension)
		pipe->pipeline.pipe_qos_config = 0;

	fw = pipe->vf_stage;
	क्रम (i = 0; fw; fw = fw->next)
	अणु
		err = sh_css_pipeline_add_acc_stage(&pipe->pipeline, fw);
		अगर (err)
			जाओ ERR;
	पूर्ण

	क्रम (i = 0; i < pipe->config.num_acc_stages; i++)
	अणु
		काष्ठा ia_css_fw_info *fw = pipe->config.acc_stages[i];

		err = sh_css_pipeline_add_acc_stage(&pipe->pipeline, fw);
		अगर (err)
			जाओ ERR;
	पूर्ण

	ia_css_pipeline_finalize_stages(&pipe->pipeline, pipe->stream->config.continuous);

ERR:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* Create stages क्रम preview */
अटल पूर्णांक
create_host_preview_pipeline(काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_pipeline_stage *copy_stage = शून्य;
	काष्ठा ia_css_pipeline_stage *preview_stage = शून्य;
	काष्ठा ia_css_pipeline_stage *vf_pp_stage = शून्य;
	काष्ठा ia_css_pipeline_stage_desc stage_desc;
	काष्ठा ia_css_pipeline *me = शून्य;
	काष्ठा ia_css_binary *copy_binary, *preview_binary, *vf_pp_binary = शून्य;
	काष्ठा ia_css_frame *in_frame = शून्य;
	पूर्णांक err = 0;
	काष्ठा ia_css_frame *out_frame;
	काष्ठा ia_css_frame *out_frames[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	bool need_in_frameinfo_memory = false;
#अगर_घोषित ISP2401
	bool sensor = false;
	bool buffered_sensor = false;
	bool online = false;
	bool continuous = false;
#पूर्ण_अगर

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (!pipe->stream) || (pipe->mode != IA_CSS_PIPE_ID_PREVIEW))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	ia_css_pipe_util_create_output_frames(out_frames);
	/* pipeline alपढ़ोy created as part of create_host_pipeline_काष्ठाure */
	me = &pipe->pipeline;
	ia_css_pipeline_clean(me);

#अगर_घोषित ISP2401
	/* When the input प्रणाली is 2401, always enable 'in_frameinfo_memory'
	 * except क्रम the following:
	 * - Direct Sensor Mode Online Preview
	 * - Buffered Sensor Mode Online Preview
	 * - Direct Sensor Mode Continuous Preview
	 * - Buffered Sensor Mode Continuous Preview
	 */
	sensor = (pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR);
	buffered_sensor = (pipe->stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR);
	online = pipe->stream->config.online;
	continuous = pipe->stream->config.continuous;
	need_in_frameinfo_memory =
	!((sensor && (online || continuous)) || (buffered_sensor && (online || continuous)));
#अन्यथा
	/* Conकाष्ठा in_frame info (only in हाल we have dynamic input */
	need_in_frameinfo_memory = pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY;
#पूर्ण_अगर
	अगर (need_in_frameinfo_memory)
	अणु
		err = init_in_frameinfo_memory_शेषs(pipe, &me->in_frame,
							IA_CSS_FRAME_FORMAT_RAW);
		अगर (err)
			जाओ ERR;

		in_frame = &me->in_frame;
	पूर्ण अन्यथा
	अणु
		in_frame = शून्य;
	पूर्ण

	err = init_out_frameinfo_शेषs(pipe, &me->out_frame[0], 0);
	अगर (err)
		जाओ ERR;
	out_frame = &me->out_frame[0];

	copy_binary    = &pipe->pipe_settings.preview.copy_binary;
	preview_binary = &pipe->pipe_settings.preview.preview_binary;
	अगर (pipe->pipe_settings.preview.vf_pp_binary.info)
		vf_pp_binary = &pipe->pipe_settings.preview.vf_pp_binary;

	अगर (pipe->pipe_settings.preview.copy_binary.info)
	अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
						   out_frames, शून्य, शून्य);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			&copy_stage);
		अगर (err)
			जाओ ERR;
		in_frame = me->stages->args.out_frame[0];
	पूर्ण अन्यथा अगर (pipe->stream->config.continuous) अणु
#अगर_घोषित ISP2401
		/* When continuous is enabled, configure in_frame with the
		 * last pipe, which is the copy pipe.
		 */
		अगर (continuous || !online) अणु
			in_frame = pipe->stream->last_pipe->continuous_frames[0];
		पूर्ण
#अन्यथा
		in_frame = pipe->continuous_frames[0];
#पूर्ण_अगर
	पूर्ण

	अगर (vf_pp_binary)
	अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, preview_binary,
						   out_frames, in_frame, शून्य);
	पूर्ण अन्यथा
	अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, preview_binary,
						   out_frames, in_frame, शून्य);
	पूर्ण
	err = ia_css_pipeline_create_and_add_stage(me,
		&stage_desc,
		&preview_stage);
	अगर (err)
		जाओ ERR;
	/* If we use copy iso preview, the input must be yuv iso raw */
	preview_stage->args.copy_vf =
	    preview_binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_COPY;
	preview_stage->args.copy_output = !preview_stage->args.copy_vf;
	अगर (preview_stage->args.copy_vf && !preview_stage->args.out_vf_frame)
	अणु
		/* in हाल of copy, use the vf frame as output frame */
		preview_stage->args.out_vf_frame =
		    preview_stage->args.out_frame[0];
	पूर्ण
	अगर (vf_pp_binary)
	अणु
		अगर (preview_binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_COPY)
			in_frame = preview_stage->args.out_vf_frame;
		अन्यथा
			in_frame = preview_stage->args.out_frame[0];
		err = add_vf_pp_stage(pipe, in_frame, out_frame, vf_pp_binary,
				      &vf_pp_stage);
		अगर (err)
			जाओ ERR;
	पूर्ण

	pipe->pipeline.acquire_isp_each_stage = false;
	ia_css_pipeline_finalize_stages(&pipe->pipeline, pipe->stream->config.continuous);

ERR:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल व्योम send_raw_frames(काष्ठा ia_css_pipe *pipe)
अणु
	अगर (pipe->stream->config.continuous) अणु
		अचिन्हित पूर्णांक i;

		sh_css_update_host2sp_cont_num_raw_frames
		(pipe->stream->config.init_num_cont_raw_buf, true);
		sh_css_update_host2sp_cont_num_raw_frames
		(pipe->stream->config.target_num_cont_raw_buf, false);

		/* Hand-over all the SP-पूर्णांकernal buffers */
		क्रम (i = 0; i < pipe->stream->config.init_num_cont_raw_buf; i++) अणु
			sh_css_update_host2sp_offline_frame(i,
							    pipe->continuous_frames[i], pipe->cont_md_buffers[i]);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक
preview_start(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_pipe *copy_pipe, *capture_pipe;
	काष्ठा ia_css_pipe *acc_pipe;
	क्रमागत sh_css_pipe_config_override copy_ovrd;
	क्रमागत ia_css_input_mode preview_pipe_input_mode;
	स्थिर काष्ठा ia_css_coordinate *coord = शून्य;
	स्थिर काष्ठा ia_css_isp_parameters *params = शून्य;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (!pipe->stream) || (pipe->mode != IA_CSS_PIPE_ID_PREVIEW))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	preview_pipe_input_mode = pipe->stream->config.mode;

	copy_pipe    = pipe->pipe_settings.preview.copy_pipe;
	capture_pipe = pipe->pipe_settings.preview.capture_pipe;
	acc_pipe     = pipe->pipe_settings.preview.acc_pipe;

	sh_css_metrics_start_frame();

	/* multi stream video needs mipi buffers */
	err = send_mipi_frames(pipe);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	send_raw_frames(pipe);

	अणु
		अचिन्हित पूर्णांक thपढ़ो_id;

		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		copy_ovrd = 1 << thपढ़ो_id;

		अगर (pipe->stream->cont_capt)
		अणु
			ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(capture_pipe),
							 &thपढ़ो_id);
			copy_ovrd |= 1 << thपढ़ो_id;
		पूर्ण
	पूर्ण

	अगर (IS_ISP2401) अणु
		coord = &pipe->config.पूर्णांकernal_frame_origin_bqs_on_sctbl;
		params = pipe->stream->isp_params_configs;
	पूर्ण

	/* Conकाष्ठा and load the copy pipe */
	अगर (pipe->stream->config.continuous)
	अणु
		sh_css_sp_init_pipeline(&copy_pipe->pipeline,
					IA_CSS_PIPE_ID_COPY,
					(uपूर्णांक8_t)ia_css_pipe_get_pipe_num(copy_pipe),
					false,
					pipe->stream->config.pixels_per_घड़ी == 2, false,
					false, pipe->required_bds_factor,
					copy_ovrd,
					pipe->stream->config.mode,
					&pipe->stream->config.metadata_config,
					&pipe->stream->info.metadata_info,
					pipe->stream->config.source.port.port,
					coord,
					params);

		/* make the preview pipe start with mem mode input, copy handles
		   the actual mode */
		preview_pipe_input_mode = IA_CSS_INPUT_MODE_MEMORY;
	पूर्ण

	/* Conकाष्ठा and load the capture pipe */
	अगर (pipe->stream->cont_capt)
	अणु
		sh_css_sp_init_pipeline(&capture_pipe->pipeline,
					IA_CSS_PIPE_ID_CAPTURE,
					(uपूर्णांक8_t)ia_css_pipe_get_pipe_num(capture_pipe),
					capture_pipe->config.शेष_capture_config.enable_xnr != 0,
					capture_pipe->stream->config.pixels_per_घड़ी == 2,
					true, /* continuous */
					false, /* offline */
					capture_pipe->required_bds_factor,
					0,
					IA_CSS_INPUT_MODE_MEMORY,
					&pipe->stream->config.metadata_config,
					&pipe->stream->info.metadata_info,
					(क्रमागत mipi_port_id)0,
					coord,
					params);
	पूर्ण

	अगर (acc_pipe)
	अणु
		sh_css_sp_init_pipeline(&acc_pipe->pipeline,
					IA_CSS_PIPE_ID_ACC,
					(uपूर्णांक8_t)ia_css_pipe_get_pipe_num(acc_pipe),
					false,
					pipe->stream->config.pixels_per_घड़ी == 2,
					false, /* continuous */
					false, /* offline */
					pipe->required_bds_factor,
					0,
					IA_CSS_INPUT_MODE_MEMORY,
					शून्य,
					शून्य,
					(क्रमागत mipi_port_id)0,
					coord,
					params);
	पूर्ण

	start_pipe(pipe, copy_ovrd, preview_pipe_input_mode);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

पूर्णांक
ia_css_pipe_enqueue_buffer(काष्ठा ia_css_pipe *pipe,
			   स्थिर काष्ठा ia_css_buffer *buffer) अणु
	पूर्णांक वापस_err = 0;
	अचिन्हित पूर्णांक thपढ़ो_id;
	क्रमागत sh_css_queue_id queue_id;
	काष्ठा ia_css_pipeline *pipeline;
	काष्ठा ia_css_pipeline_stage *stage;
	काष्ठा ia_css_rmgr_vbuf_handle p_vbuf;
	काष्ठा ia_css_rmgr_vbuf_handle *h_vbuf;
	काष्ठा sh_css_hmm_buffer ddr_buffer;
	क्रमागत ia_css_buffer_type buf_type;
	क्रमागत ia_css_pipe_id pipe_id;
	bool ret_err;

	IA_CSS_ENTER("pipe=%p, buffer=%p", pipe, buffer);

	अगर ((!pipe) || (!buffer))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	buf_type = buffer->type;
	/* following code will be enabled when IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME
	   is हटाओd */
#अगर 0
	अगर (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
	अणु
		bool found_pipe = false;

		क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
			अगर ((buffer->data.frame->info.res.width == pipe->output_info[i].res.width) &&
			    (buffer->data.frame->info.res.height == pipe->output_info[i].res.height)) अणु
				buf_type += i;
				found_pipe = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found_pipe)
			वापस -EINVAL;
	पूर्ण
	अगर (buf_type == IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME)
	अणु
		bool found_pipe = false;

		क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
			अगर ((buffer->data.frame->info.res.width == pipe->vf_output_info[i].res.width) &&
			    (buffer->data.frame->info.res.height == pipe->vf_output_info[i].res.height)) अणु
				buf_type += i;
				found_pipe = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found_pipe)
			वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	pipe_id = pipe->mode;

	IA_CSS_LOG("pipe_id=%d, buf_type=%d", pipe_id, buf_type);

	निश्चित(pipe_id < IA_CSS_PIPE_ID_NUM);
	निश्चित(buf_type < IA_CSS_NUM_DYNAMIC_BUFFER_TYPE);
	अगर ((buf_type == IA_CSS_BUFFER_TYPE_INVALID) ||
	    (buf_type >= IA_CSS_NUM_DYNAMIC_BUFFER_TYPE) ||
	    (pipe_id >= IA_CSS_PIPE_ID_NUM))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	ret_err = ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
	अगर (!ret_err)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	ret_err = ia_css_query_पूर्णांकernal_queue_id(buf_type, thपढ़ो_id, &queue_id);
	अगर (!ret_err)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर ((queue_id <= SH_CSS_INVALID_QUEUE_ID) || (queue_id >= SH_CSS_MAX_NUM_QUEUES))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर (!sh_css_sp_is_running())
	अणु
		IA_CSS_LOG("SP is not running!");
		IA_CSS_LEAVE_ERR(-EBUSY);
		/* SP is not running. The queues are not valid */
		वापस -EBUSY;
	पूर्ण

	pipeline = &pipe->pipeline;

	निश्चित(pipeline ||
	       pipe_id == IA_CSS_PIPE_ID_COPY ||
	       pipe_id == IA_CSS_PIPE_ID_ACC);

	निश्चित(माप(शून्य) <= माप(ddr_buffer.kernel_ptr));
	ddr_buffer.kernel_ptr = HOST_ADDRESS(शून्य);
	ddr_buffer.cookie_ptr = buffer->driver_cookie;
	ddr_buffer.timing_data = buffer->timing_data;

	अगर (buf_type == IA_CSS_BUFFER_TYPE_3A_STATISTICS)
	अणु
		अगर (!buffer->data.stats_3a) अणु
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण
		ddr_buffer.kernel_ptr = HOST_ADDRESS(buffer->data.stats_3a);
		ddr_buffer.payload.s3a = *buffer->data.stats_3a;
	पूर्ण अन्यथा अगर (buf_type == IA_CSS_BUFFER_TYPE_DIS_STATISTICS)
	अणु
		अगर (!buffer->data.stats_dvs) अणु
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण
		ddr_buffer.kernel_ptr = HOST_ADDRESS(buffer->data.stats_dvs);
		ddr_buffer.payload.dis = *buffer->data.stats_dvs;
	पूर्ण अन्यथा अगर (buf_type == IA_CSS_BUFFER_TYPE_METADATA)
	अणु
		अगर (!buffer->data.metadata) अणु
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण
		ddr_buffer.kernel_ptr = HOST_ADDRESS(buffer->data.metadata);
		ddr_buffer.payload.metadata = *buffer->data.metadata;
	पूर्ण अन्यथा अगर ((buf_type == IA_CSS_BUFFER_TYPE_INPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME))
	अणु
		अगर (!buffer->data.frame) अणु
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण
		ddr_buffer.kernel_ptr = HOST_ADDRESS(buffer->data.frame);
		ddr_buffer.payload.frame.frame_data = buffer->data.frame->data;
		ddr_buffer.payload.frame.flashed = 0;

		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_pipe_enqueue_buffer() buf_type=%d, data(DDR address)=0x%x\n",
				    buf_type, buffer->data.frame->data);

#अगर CONFIG_ON_FRAME_ENQUEUE()
		वापस_err = set_config_on_frame_enqueue(
				 &buffer->data.frame->info,
				 &ddr_buffer.payload.frame);
		अगर (वापस_err) अणु
			IA_CSS_LEAVE_ERR(वापस_err);
			वापस वापस_err;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* start of test क्रम using rmgr क्रम acq/rel memory */
	p_vbuf.vptr = 0;
	p_vbuf.count = 0;
	p_vbuf.size = माप(काष्ठा sh_css_hmm_buffer);
	h_vbuf = &p_vbuf;
	/* TODO: change next to correct pool क्रम optimization */
	ia_css_rmgr_acq_vbuf(hmm_buffer_pool, &h_vbuf);

	निश्चित(h_vbuf);
	निश्चित(h_vbuf->vptr != 0x0);

	अगर ((!h_vbuf) || (h_vbuf->vptr == 0x0))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	hmm_store(h_vbuf->vptr,
		   (व्योम *)(&ddr_buffer),
		   माप(काष्ठा sh_css_hmm_buffer));
	अगर ((buf_type == IA_CSS_BUFFER_TYPE_3A_STATISTICS)
	    || (buf_type == IA_CSS_BUFFER_TYPE_DIS_STATISTICS)
	    || (buf_type == IA_CSS_BUFFER_TYPE_LACE_STATISTICS))
	अणु
		अगर (!pipeline) अणु
			ia_css_rmgr_rel_vbuf(hmm_buffer_pool, &h_vbuf);
			IA_CSS_LOG("pipeline is empty!");
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण

		क्रम (stage = pipeline->stages; stage; stage = stage->next) अणु
			/* The SP will पढ़ो the params
				after it got empty 3a and dis */
			अगर (STATS_ENABLED(stage)) अणु
				/* there is a stage that needs it */
				वापस_err = ia_css_bufq_enqueue_buffer(thपढ़ो_id,
									queue_id,
									(uपूर्णांक32_t)h_vbuf->vptr);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर ((buf_type == IA_CSS_BUFFER_TYPE_INPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME)
		   || (buf_type == IA_CSS_BUFFER_TYPE_METADATA))
	अणु
		वापस_err = ia_css_bufq_enqueue_buffer(thपढ़ो_id,
							queue_id,
							(uपूर्णांक32_t)h_vbuf->vptr);
#अगर defined(SH_CSS_ENABLE_PER_FRAME_PARAMS)
		अगर (!(वापस_err) &&
		    (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)) अणु
			IA_CSS_LOG("pfp: enqueued OF %d to q %d thread %d",
				   ddr_buffer.payload.frame.frame_data,
				   queue_id, thपढ़ो_id);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (!वापस_err)
	अणु
		अगर (sh_css_hmm_buffer_record_acquire(
			h_vbuf, buf_type,
			HOST_ADDRESS(ddr_buffer.kernel_ptr))) अणु
			IA_CSS_LOG("send vbuf=%p", h_vbuf);
		पूर्ण अन्यथा अणु
			वापस_err = -EINVAL;
			IA_CSS_ERROR("hmm_buffer_record[]: no available slots\n");
		पूर्ण
	पूर्ण

	/*
	 * Tell the SP which queues are not empty,
	 * by sending the software event.
	 */
	अगर (!वापस_err)
	अणु
		अगर (!sh_css_sp_is_running()) अणु
			/* SP is not running. The queues are not valid */
			IA_CSS_LOG("SP is not running!");
			IA_CSS_LEAVE_ERR(-EBUSY);
			वापस -EBUSY;
		पूर्ण
		वापस_err = ia_css_bufq_enqueue_psys_event(
				 IA_CSS_PSYS_SW_EVENT_BUFFER_ENQUEUED,
				 (uपूर्णांक8_t)thपढ़ो_id,
				 queue_id,
				 0);
	पूर्ण अन्यथा
	अणु
		ia_css_rmgr_rel_vbuf(hmm_buffer_pool, &h_vbuf);
		IA_CSS_ERROR("buffer not enqueued");
	पूर्ण

	IA_CSS_LEAVE("return value = %d", वापस_err);

	वापस वापस_err;
पूर्ण

/*
 * TODO: Free up the hmm memory space.
	 */
पूर्णांक
ia_css_pipe_dequeue_buffer(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_buffer *buffer) अणु
	पूर्णांक वापस_err;
	क्रमागत sh_css_queue_id queue_id;
	ia_css_ptr ddr_buffer_addr = (ia_css_ptr)0;
	काष्ठा sh_css_hmm_buffer ddr_buffer;
	क्रमागत ia_css_buffer_type buf_type;
	क्रमागत ia_css_pipe_id pipe_id;
	अचिन्हित पूर्णांक thपढ़ो_id;
	hrt_address kernel_ptr = 0;
	bool ret_err;

	IA_CSS_ENTER("pipe=%p, buffer=%p", pipe, buffer);

	अगर ((!pipe) || (!buffer))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	pipe_id = pipe->mode;

	buf_type = buffer->type;

	IA_CSS_LOG("pipe_id=%d, buf_type=%d", pipe_id, buf_type);

	ddr_buffer.kernel_ptr = 0;

	ret_err = ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
	अगर (!ret_err)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	ret_err = ia_css_query_पूर्णांकernal_queue_id(buf_type, thपढ़ो_id, &queue_id);
	अगर (!ret_err)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर ((queue_id <= SH_CSS_INVALID_QUEUE_ID) || (queue_id >= SH_CSS_MAX_NUM_QUEUES))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर (!sh_css_sp_is_running())
	अणु
		IA_CSS_LOG("SP is not running!");
		IA_CSS_LEAVE_ERR(-EBUSY);
		/* SP is not running. The queues are not valid */
		वापस -EBUSY;
	पूर्ण

	वापस_err = ia_css_bufq_dequeue_buffer(queue_id,
						(uपूर्णांक32_t *)&ddr_buffer_addr);

	अगर (!वापस_err)
	अणु
		काष्ठा ia_css_frame *frame;
		काष्ठा sh_css_hmm_buffer_record *hmm_buffer_record = शून्य;

		IA_CSS_LOG("receive vbuf=%x", (पूर्णांक)ddr_buffer_addr);

		/* Validate the ddr_buffer_addr and buf_type */
		hmm_buffer_record = sh_css_hmm_buffer_record_validate(
		    ddr_buffer_addr, buf_type);
		अगर (hmm_buffer_record) अणु
			/* valid hmm_buffer_record found. Save the kernel_ptr
			 * क्रम validation after perक्रमming hmm_load.  The
			 * vbuf handle and buffer_record can be released.
			 */
			kernel_ptr = hmm_buffer_record->kernel_ptr;
			ia_css_rmgr_rel_vbuf(hmm_buffer_pool, &hmm_buffer_record->h_vbuf);
			sh_css_hmm_buffer_record_reset(hmm_buffer_record);
		पूर्ण अन्यथा अणु
			IA_CSS_ERROR("hmm_buffer_record not found (0x%x) buf_type(%d)",
				     ddr_buffer_addr, buf_type);
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण

		hmm_load(ddr_buffer_addr,
			  &ddr_buffer,
			  माप(काष्ठा sh_css_hmm_buffer));

		/* अगर the kernel_ptr is 0 or an invalid, वापस an error.
		 * करो not access the buffer via the kernal_ptr.
		 */
		अगर ((ddr_buffer.kernel_ptr == 0) ||
		    (kernel_ptr != HOST_ADDRESS(ddr_buffer.kernel_ptr))) अणु
			IA_CSS_ERROR("kernel_ptr invalid");
			IA_CSS_ERROR("expected: (0x%llx)", (u64)kernel_ptr);
			IA_CSS_ERROR("actual: (0x%llx)", (u64)HOST_ADDRESS(ddr_buffer.kernel_ptr));
			IA_CSS_ERROR("buf_type: %d\n", buf_type);
			IA_CSS_LEAVE_ERR(-EINVAL);
			वापस -EINVAL;
		पूर्ण

		अगर (ddr_buffer.kernel_ptr != 0) अणु
			/* buffer->exp_id : all instances to be हटाओd later once the driver change
			 * is completed. See patch #5758 क्रम reference */
			buffer->exp_id = 0;
			buffer->driver_cookie = ddr_buffer.cookie_ptr;
			buffer->timing_data = ddr_buffer.timing_data;

			अगर ((buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME) ||
			    (buf_type == IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME)) अणु
				buffer->isys_eof_घड़ी_प्रकारick.ticks = ddr_buffer.isys_eof_घड़ी_प्रकारick;
			पूर्ण

			चयन (buf_type) अणु
			हाल IA_CSS_BUFFER_TYPE_INPUT_FRAME:
			हाल IA_CSS_BUFFER_TYPE_OUTPUT_FRAME:
			हाल IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME:
				अगर (pipe && pipe->stop_requested) अणु
#अगर !defined(ISP2401)
					/* मुक्त mipi frames only क्रम old input प्रणाली
					 * क्रम 2401 it is करोne in ia_css_stream_destroy call
					 */
					वापस_err = मुक्त_mipi_frames(pipe);
					अगर (वापस_err) अणु
						IA_CSS_LOG("free_mipi_frames() failed");
						IA_CSS_LEAVE_ERR(वापस_err);
						वापस वापस_err;
					पूर्ण
#पूर्ण_अगर
					pipe->stop_requested = false;
				पूर्ण
				fallthrough;
			हाल IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME:
			हाल IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME:
				frame = (काष्ठा ia_css_frame *)HOST_ADDRESS(ddr_buffer.kernel_ptr);
				buffer->data.frame = frame;
				buffer->exp_id = ddr_buffer.payload.frame.exp_id;
				frame->exp_id = ddr_buffer.payload.frame.exp_id;
				frame->isp_config_id = ddr_buffer.payload.frame.isp_parameters_id;
				अगर (ddr_buffer.payload.frame.flashed == 1)
					frame->flash_state =
					    IA_CSS_FRAME_FLASH_STATE_PARTIAL;
				अगर (ddr_buffer.payload.frame.flashed == 2)
					frame->flash_state =
					    IA_CSS_FRAME_FLASH_STATE_FULL;
				frame->valid = pipe->num_invalid_frames == 0;
				अगर (!frame->valid)
					pipe->num_invalid_frames--;

				अगर (frame->info.क्रमmat == IA_CSS_FRAME_FORMAT_BINARY_8) अणु
#अगर_घोषित ISP2401
					frame->planes.binary.size = frame->data_bytes;
#अन्यथा
					frame->planes.binary.size =
					    sh_css_sp_get_binary_copy_size();
#पूर्ण_अगर
				पूर्ण
#अगर defined(SH_CSS_ENABLE_PER_FRAME_PARAMS)
				अगर (buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME) अणु
					IA_CSS_LOG("pfp: dequeued OF %d with config id %d thread %d",
						   frame->data, frame->isp_config_id, thपढ़ो_id);
				पूर्ण
#पूर्ण_अगर

				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_pipe_dequeue_buffer() buf_type=%d, data(DDR address)=0x%x\n",
						    buf_type, buffer->data.frame->data);

				अवरोध;
			हाल IA_CSS_BUFFER_TYPE_3A_STATISTICS:
				buffer->data.stats_3a =
				    (काष्ठा ia_css_isp_3a_statistics *)HOST_ADDRESS(ddr_buffer.kernel_ptr);
				buffer->exp_id = ddr_buffer.payload.s3a.exp_id;
				buffer->data.stats_3a->exp_id = ddr_buffer.payload.s3a.exp_id;
				buffer->data.stats_3a->isp_config_id = ddr_buffer.payload.s3a.isp_config_id;
				अवरोध;
			हाल IA_CSS_BUFFER_TYPE_DIS_STATISTICS:
				buffer->data.stats_dvs =
				    (काष्ठा ia_css_isp_dvs_statistics *)
				    HOST_ADDRESS(ddr_buffer.kernel_ptr);
				buffer->exp_id = ddr_buffer.payload.dis.exp_id;
				buffer->data.stats_dvs->exp_id = ddr_buffer.payload.dis.exp_id;
				अवरोध;
			हाल IA_CSS_BUFFER_TYPE_LACE_STATISTICS:
				अवरोध;
			हाल IA_CSS_BUFFER_TYPE_METADATA:
				buffer->data.metadata =
				    (काष्ठा ia_css_metadata *)HOST_ADDRESS(ddr_buffer.kernel_ptr);
				buffer->exp_id = ddr_buffer.payload.metadata.exp_id;
				buffer->data.metadata->exp_id = ddr_buffer.payload.metadata.exp_id;
				अवरोध;
			शेष:
				वापस_err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Tell the SP which queues are not full,
	 * by sending the software event.
	 */
	अगर (!वापस_err)
	अणु
		अगर (!sh_css_sp_is_running()) अणु
			IA_CSS_LOG("SP is not running!");
			IA_CSS_LEAVE_ERR(-EBUSY);
			/* SP is not running. The queues are not valid */
			वापस -EBUSY;
		पूर्ण
		ia_css_bufq_enqueue_psys_event(
		    IA_CSS_PSYS_SW_EVENT_BUFFER_DEQUEUED,
		    0,
		    queue_id,
		    0);
	पूर्ण
	IA_CSS_LEAVE("buffer=%p", buffer);

	वापस वापस_err;
पूर्ण

/*
 * Cannot Move this to event module as it is of ia_css_event_type which is declared in ia_css.h
 * TODO: modअगरy and move it अगर possible.
 *
 * !!!IMPORTANT!!! KEEP THE FOLLOWING IN SYNC:
 * 1) "enum ia_css_event_type"					(ia_css_event_खुला.h)
 * 2) "enum sh_css_sp_event_type"				(sh_css_पूर्णांकernal.h)
 * 3) "enum ia_css_event_type event_id_2_event_mask"		(event_handler.sp.c)
 * 4) "enum ia_css_event_type convert_event_sp_to_host_domain"	(sh_css.c)
 */
अटल क्रमागत ia_css_event_type convert_event_sp_to_host_करोमुख्य[] = अणु
	IA_CSS_EVENT_TYPE_OUTPUT_FRAME_DONE,	/** Output frame पढ़ोy. */
	IA_CSS_EVENT_TYPE_SECOND_OUTPUT_FRAME_DONE,	/** Second output frame पढ़ोy. */
	IA_CSS_EVENT_TYPE_VF_OUTPUT_FRAME_DONE,	/** Viewfinder Output frame पढ़ोy. */
	IA_CSS_EVENT_TYPE_SECOND_VF_OUTPUT_FRAME_DONE,	/** Second viewfinder Output frame पढ़ोy. */
	IA_CSS_EVENT_TYPE_3A_STATISTICS_DONE,	/** Indication that 3A statistics are available. */
	IA_CSS_EVENT_TYPE_DIS_STATISTICS_DONE,	/** Indication that DIS statistics are available. */
	IA_CSS_EVENT_TYPE_PIPELINE_DONE,	/** Pipeline Done event, sent after last pipeline stage. */
	IA_CSS_EVENT_TYPE_FRAME_TAGGED,		/** Frame tagged. */
	IA_CSS_EVENT_TYPE_INPUT_FRAME_DONE,	/** Input frame पढ़ोy. */
	IA_CSS_EVENT_TYPE_METADATA_DONE,	/** Metadata पढ़ोy. */
	IA_CSS_EVENT_TYPE_LACE_STATISTICS_DONE,	/** Indication that LACE statistics are available. */
	IA_CSS_EVENT_TYPE_ACC_STAGE_COMPLETE,	/** Extension stage executed. */
	IA_CSS_EVENT_TYPE_TIMER,		/** Timing measurement data. */
	IA_CSS_EVENT_TYPE_PORT_खातापूर्ण,		/** End Of Frame event, sent when in buffered sensor mode. */
	IA_CSS_EVENT_TYPE_FW_WARNING,		/** Perक्रमmance warning encountered by FW */
	IA_CSS_EVENT_TYPE_FW_ASSERT,		/** Assertion hit by FW */
	0,					/* error अगर sp passes  SH_CSS_SP_EVENT_NR_OF_TYPES as a valid event. */
पूर्ण;

पूर्णांक
ia_css_dequeue_event(काष्ठा ia_css_event *event) अणु
	वापस ia_css_dequeue_psys_event(event);
पूर्ण

पूर्णांक
ia_css_dequeue_psys_event(काष्ठा ia_css_event *event) अणु
	क्रमागत ia_css_pipe_id pipe_id = 0;
	u8 payload[4] = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक ret_err;

	/*TODO:
	 * a) use generic decoding function , same as the one used by sp.
	 * b) group decode and dequeue पूर्णांकo eventQueue module
	 *
	 * We skip the IA_CSS_ENTER logging call
	 * to aव्योम flooding the logs when the host application
	 * uses polling. */
	अगर (!event)
		वापस -EINVAL;

	अगर (!sh_css_sp_is_running())
	अणु
		/* SP is not running. The queues are not valid */
		वापस -EBUSY;
	पूर्ण

	/* dequeue the event (अगर any) from the psys event queue */
	ret_err = ia_css_bufq_dequeue_psys_event(payload);
	अगर (ret_err)
		वापस ret_err;

	IA_CSS_LOG("event dequeued from psys event queue");

	/* Tell the SP that we dequeued an event from the event queue. */
	ia_css_bufq_enqueue_psys_event(
	    IA_CSS_PSYS_SW_EVENT_EVENT_DEQUEUED, 0, 0, 0);

	/* Events are decoded पूर्णांकo 4 bytes of payload, the first byte
	 * contains the sp event type. This is converted to a host क्रमागत.
	 * TODO: can this क्रमागत conversion be eliminated */
	event->type = convert_event_sp_to_host_करोमुख्य[payload[0]];
	/* Some sane शेष values since not all events use all fields. */
	event->pipe = शून्य;
	event->port = MIPI_PORT0_ID;
	event->exp_id = 0;
	event->fw_warning = IA_CSS_FW_WARNING_NONE;
	event->fw_handle = 0;
	event->समयr_data = 0;
	event->समयr_code = 0;
	event->समयr_subcode = 0;

	अगर (event->type == IA_CSS_EVENT_TYPE_TIMER)
	अणु
		/* समयr event ??? get the 2nd event and decode the data पूर्णांकo the event काष्ठा */
		u32 पंचांगp_data;
		/* 1st event: LSB 16-bit समयr data and code */
		event->समयr_data = ((payload[1] & 0xFF) | ((payload[3] & 0xFF) << 8));
		event->समयr_code = payload[2];
		payload[0] = payload[1] = payload[2] = payload[3] = 0;
		ret_err = ia_css_bufq_dequeue_psys_event(payload);
		अगर (ret_err) अणु
			/* no 2nd event ??? an error */
			/* Putting IA_CSS_ERROR is resulting in failures in
			 * Merrअगरield smoke testing  */
			IA_CSS_WARNING("Timer: Error de-queuing the 2nd TIMER event!!!\n");
			वापस ret_err;
		पूर्ण
		ia_css_bufq_enqueue_psys_event(
		    IA_CSS_PSYS_SW_EVENT_EVENT_DEQUEUED, 0, 0, 0);
		event->type = convert_event_sp_to_host_करोमुख्य[payload[0]];
		/* It's a समयr */
		अगर (event->type == IA_CSS_EVENT_TYPE_TIMER) अणु
			/* 2nd event data: MSB 16-bit समयr and subcode */
			पंचांगp_data = ((payload[1] & 0xFF) | ((payload[3] & 0xFF) << 8));
			event->समयr_data |= (पंचांगp_data << 16);
			event->समयr_subcode = payload[2];
		पूर्ण
		/* It's a non समयr event. So clear first half of the समयr event data.
		* If the second part of the TIMER event is not received, we discard
		* the first half of the समयr data and process the non समयr event without
		* affecting the flow. So the non समयr event falls through
		* the code. */
		अन्यथा अणु
			event->समयr_data = 0;
			event->समयr_code = 0;
			event->समयr_subcode = 0;
			IA_CSS_ERROR("Missing 2nd timer event. Timer event discarded");
		पूर्ण
	पूर्ण
	अगर (event->type == IA_CSS_EVENT_TYPE_PORT_खातापूर्ण)
	अणु
		event->port = (क्रमागत mipi_port_id)payload[1];
		event->exp_id = payload[3];
	पूर्ण अन्यथा अगर (event->type == IA_CSS_EVENT_TYPE_FW_WARNING)
	अणु
		event->fw_warning = (क्रमागत ia_css_fw_warning)payload[1];
		/* exp_id is only available in these warning types */
		अगर (event->fw_warning == IA_CSS_FW_WARNING_EXP_ID_LOCKED ||
		    event->fw_warning == IA_CSS_FW_WARNING_TAG_EXP_ID_FAILED)
			event->exp_id = payload[3];
	पूर्ण अन्यथा अगर (event->type == IA_CSS_EVENT_TYPE_FW_ASSERT)
	अणु
		event->fw_निश्चित_module_id = payload[1]; /* module */
		event->fw_निश्चित_line_no = (payload[2] << 8) + payload[3];
		/* payload[2] is line_no>>8, payload[3] is line_no&0xff */
	पूर्ण अन्यथा अगर (event->type != IA_CSS_EVENT_TYPE_TIMER)
	अणु
		/* pipe related events.
		 * payload[1] contains the pipe_num,
		 * payload[2] contains the pipe_id. These are dअगरferent. */
		event->pipe = find_pipe_by_num(payload[1]);
		pipe_id = (क्रमागत ia_css_pipe_id)payload[2];
		/* Check to see अगर pipe still exists */
		अगर (!event->pipe)
			वापस -EBUSY;

		अगर (event->type == IA_CSS_EVENT_TYPE_FRAME_TAGGED) अणु
			/* find the capture pipe that goes with this */
			पूर्णांक i, n;

			n = event->pipe->stream->num_pipes;
			क्रम (i = 0; i < n; i++) अणु
				काष्ठा ia_css_pipe *p =
					    event->pipe->stream->pipes[i];
				अगर (p->config.mode == IA_CSS_PIPE_MODE_CAPTURE) अणु
					event->pipe = p;
					अवरोध;
				पूर्ण
			पूर्ण
			event->exp_id = payload[3];
		पूर्ण
		अगर (event->type == IA_CSS_EVENT_TYPE_ACC_STAGE_COMPLETE) अणु
			/* payload[3] contains the acc fw handle. */
			u32 stage_num = (uपूर्णांक32_t)payload[3];

			ret_err = ia_css_pipeline_get_fw_from_stage(
				      &event->pipe->pipeline,
				      stage_num,
				      &event->fw_handle);
			अगर (ret_err) अणु
				IA_CSS_ERROR("Invalid stage num received for ACC event. stage_num:%u",
					     stage_num);
				वापस ret_err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (event->pipe)
		IA_CSS_LEAVE("event_id=%d, pipe_id=%d", event->type, pipe_id);
	अन्यथा
		IA_CSS_LEAVE("event_id=%d", event->type);

	वापस 0;
पूर्ण

पूर्णांक
ia_css_dequeue_isys_event(काष्ठा ia_css_event *event) अणु
	u8 payload[4] = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक err = 0;

	/* We skip the IA_CSS_ENTER logging call
	 * to aव्योम flooding the logs when the host application
	 * uses polling. */
	अगर (!event)
		वापस -EINVAL;

	अगर (!sh_css_sp_is_running())
	अणु
		/* SP is not running. The queues are not valid */
		वापस -EBUSY;
	पूर्ण

	err = ia_css_bufq_dequeue_isys_event(payload);
	अगर (err)
		वापस err;

	IA_CSS_LOG("event dequeued from isys event queue");

	/* Update SP state to indicate that element was dequeued. */
	ia_css_bufq_enqueue_isys_event(IA_CSS_ISYS_SW_EVENT_EVENT_DEQUEUED);

	/* Fill वापस काष्ठा with appropriate info */
	event->type = IA_CSS_EVENT_TYPE_PORT_खातापूर्ण;
	/* खातापूर्ण events are associated with a CSI port, not with a pipe */
	event->pipe = शून्य;
	event->port = payload[1];
	event->exp_id = payload[3];

	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

अटल व्योम
acc_start(काष्ठा ia_css_pipe *pipe)
अणु
	निश्चित(pipe);
	निश्चित(pipe->stream);

	start_pipe(pipe, SH_CSS_PIPE_CONFIG_OVRD_NO_OVRD,
		   pipe->stream->config.mode);
पूर्ण

अटल पूर्णांक
sh_css_pipe_start(काष्ठा ia_css_stream *stream) अणु
	पूर्णांक err = 0;

	काष्ठा ia_css_pipe *pipe;
	क्रमागत ia_css_pipe_id pipe_id;
	अचिन्हित पूर्णांक thपढ़ो_id;

	IA_CSS_ENTER_PRIVATE("stream = %p", stream);

	अगर (!stream)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	pipe = stream->last_pipe;
	अगर (!pipe)
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	pipe_id = pipe->mode;

	अगर (stream->started)
	अणु
		IA_CSS_WARNING("Cannot start stream that is already started");
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

	pipe->stop_requested = false;

	चयन (pipe_id)
	अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		err = preview_start(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_VIDEO:
		err = video_start(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_CAPTURE:
		err = capture_start(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_YUVPP:
		err = yuvpp_start(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_ACC:
		acc_start(pipe);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	/* DH regular multi pipe - not continuous mode: start the next pipes too */
	अगर (!stream->config.continuous)
	अणु
		पूर्णांक i;

		क्रम (i = 1; i < stream->num_pipes && 0 == err ; i++) अणु
			चयन (stream->pipes[i]->mode) अणु
			हाल IA_CSS_PIPE_ID_PREVIEW:
				stream->pipes[i]->stop_requested = false;
				err = preview_start(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_VIDEO:
				stream->pipes[i]->stop_requested = false;
				err = video_start(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_CAPTURE:
				stream->pipes[i]->stop_requested = false;
				err = capture_start(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_YUVPP:
				stream->pipes[i]->stop_requested = false;
				err = yuvpp_start(stream->pipes[i]);
				अवरोध;
			हाल IA_CSS_PIPE_ID_ACC:
				stream->pipes[i]->stop_requested = false;
				acc_start(stream->pipes[i]);
				अवरोध;
			शेष:
				err = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	/* Force ISP parameter calculation after a mode change
	 * Acceleration API examples pass शून्य क्रम stream but they
	 * करोn't use ISP parameters anyway. So this should be okay.
	 * The SP binary (jpeg) copy करोes not use any parameters.
	 */
	अगर (!copy_on_sp(pipe))
	अणु
		sh_css_invalidate_params(stream);
		err = sh_css_param_update_isp_params(pipe,
						     stream->isp_params_configs, true, शून्य);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

	ia_css_debug_pipe_graph_dump_epilogue();

	ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);

	अगर (!sh_css_sp_is_running())
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EBUSY);
		/* SP is not running. The queues are not valid */
		वापस -EBUSY;
	पूर्ण
	ia_css_bufq_enqueue_psys_event(IA_CSS_PSYS_SW_EVENT_START_STREAM,
				       (uपूर्णांक8_t)thपढ़ो_id, 0, 0);

	/* DH regular multi pipe - not continuous mode: enqueue event to the next pipes too */
	अगर (!stream->config.continuous)
	अणु
		पूर्णांक i;

		क्रम (i = 1; i < stream->num_pipes; i++) अणु
			ia_css_pipeline_get_sp_thपढ़ो_id(
			    ia_css_pipe_get_pipe_num(stream->pipes[i]),
			    &thपढ़ो_id);
			ia_css_bufq_enqueue_psys_event(
			    IA_CSS_PSYS_SW_EVENT_START_STREAM,
			    (uपूर्णांक8_t)thपढ़ो_id, 0, 0);
		पूर्ण
	पूर्ण

	/* in हाल of continuous capture mode, we also start capture thपढ़ो and copy thपढ़ो*/
	अगर (pipe->stream->config.continuous)
	अणु
		काष्ठा ia_css_pipe *copy_pipe = शून्य;

		अगर (pipe_id == IA_CSS_PIPE_ID_PREVIEW)
			copy_pipe = pipe->pipe_settings.preview.copy_pipe;
		अन्यथा अगर (pipe_id == IA_CSS_PIPE_ID_VIDEO)
			copy_pipe = pipe->pipe_settings.video.copy_pipe;

		अगर (!copy_pipe) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
			वापस -EINVAL;
		पूर्ण
		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(copy_pipe),
						 &thपढ़ो_id);
		/* by the समय we reach here q is initialized and handle is available.*/
		ia_css_bufq_enqueue_psys_event(
		    IA_CSS_PSYS_SW_EVENT_START_STREAM,
		    (uपूर्णांक8_t)thपढ़ो_id, 0,  0);
	पूर्ण
	अगर (pipe->stream->cont_capt)
	अणु
		काष्ठा ia_css_pipe *capture_pipe = शून्य;

		अगर (pipe_id == IA_CSS_PIPE_ID_PREVIEW)
			capture_pipe = pipe->pipe_settings.preview.capture_pipe;
		अन्यथा अगर (pipe_id == IA_CSS_PIPE_ID_VIDEO)
			capture_pipe = pipe->pipe_settings.video.capture_pipe;

		अगर (!capture_pipe) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
			वापस -EINVAL;
		पूर्ण
		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(capture_pipe),
						 &thपढ़ो_id);
		/* by the समय we reach here q is initialized and handle is available.*/
		ia_css_bufq_enqueue_psys_event(
		    IA_CSS_PSYS_SW_EVENT_START_STREAM,
		    (uपूर्णांक8_t)thपढ़ो_id, 0,  0);
	पूर्ण

	/* in हाल of PREVIEW mode, check whether QOS acc_pipe is available, then start the qos pipe */
	अगर (pipe_id == IA_CSS_PIPE_ID_PREVIEW)
	अणु
		काष्ठा ia_css_pipe *acc_pipe = शून्य;

		acc_pipe = pipe->pipe_settings.preview.acc_pipe;

		अगर (acc_pipe) अणु
			ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(acc_pipe),
							 &thपढ़ो_id);
			/* by the समय we reach here q is initialized and handle is available.*/
			ia_css_bufq_enqueue_psys_event(
			    IA_CSS_PSYS_SW_EVENT_START_STREAM,
			    (uपूर्णांक8_t)thपढ़ो_id, 0, 0);
		पूर्ण
	पूर्ण

	stream->started = true;

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* ISP2400 */
व्योम
sh_css_enable_cont_capt(bool enable, bool stop_copy_preview)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_enable_cont_capt() enter: enable=%d\n", enable);
//my_css.cont_capt = enable;
	my_css.stop_copy_preview = stop_copy_preview;
पूर्ण

bool
sh_css_continuous_is_enabled(uपूर्णांक8_t pipe_num)
अणु
	काष्ठा ia_css_pipe *pipe;
	bool continuous;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_continuous_is_enabled() enter: pipe_num=%d\n", pipe_num);

	pipe = find_pipe_by_num(pipe_num);
	continuous = pipe && pipe->stream->config.continuous;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_continuous_is_enabled() leave: enable=%d\n",
			    continuous);
	वापस continuous;
पूर्ण

/* ISP2400 */
पूर्णांक
ia_css_stream_get_max_buffer_depth(काष्ठा ia_css_stream *stream,
				   पूर्णांक *buffer_depth) अणु
	अगर (!buffer_depth)
		वापस -EINVAL;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_get_max_buffer_depth() enter: void\n");
	(व्योम)stream;
	*buffer_depth = NUM_CONTINUOUS_FRAMES;
	वापस 0;
पूर्ण

पूर्णांक
ia_css_stream_set_buffer_depth(काष्ठा ia_css_stream *stream, पूर्णांक buffer_depth) अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_set_buffer_depth() enter: num_frames=%d\n", buffer_depth);
	(व्योम)stream;
	अगर (buffer_depth > NUM_CONTINUOUS_FRAMES || buffer_depth < 1)
		वापस -EINVAL;
	/* ok, value allowed */
	stream->config.target_num_cont_raw_buf = buffer_depth;
	/* TODO: check what to regarding initialization */
	वापस 0;
पूर्ण

/* ISP2401 */
पूर्णांक
ia_css_stream_get_buffer_depth(काष्ठा ia_css_stream *stream,
			       पूर्णांक *buffer_depth) अणु
	अगर (!buffer_depth)
		वापस -EINVAL;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_get_buffer_depth() enter: void\n");
	(व्योम)stream;
	*buffer_depth = stream->config.target_num_cont_raw_buf;
	वापस 0;
पूर्ण

/*
 * @brief Stop all "ia_css_pipe" instances in the target
 * "ia_css_stream" instance.
 *
 * Refer to "Local prototypes" क्रम more info.
 */
/* ISP2401 */
अटल पूर्णांक
sh_css_pipes_stop(काष्ठा ia_css_stream *stream)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_pipe *मुख्य_pipe;
	क्रमागत ia_css_pipe_id मुख्य_pipe_id;
	पूर्णांक i;

	निश्चित(stream);
	अगर (!stream)
	अणु
		IA_CSS_LOG("stream does NOT exist!");
		err = -EINVAL;
		जाओ ERR;
	पूर्ण

	मुख्य_pipe = stream->last_pipe;
	निश्चित(मुख्य_pipe);
	अगर (!मुख्य_pipe)
	अणु
		IA_CSS_LOG("main_pipe does NOT exist!");
		err = -EINVAL;
		जाओ ERR;
	पूर्ण

	मुख्य_pipe_id = मुख्य_pipe->mode;
	IA_CSS_ENTER_PRIVATE("main_pipe_id=%d", मुख्य_pipe_id);

	/*
	 * Stop all "ia_css_pipe" instances in this target
	 * "ia_css_stream" instance.
	 */
	क्रम (i = 0; i < stream->num_pipes; i++)
	अणु
		/* send the "stop" request to the "ia_css_pipe" instance */
		IA_CSS_LOG("Send the stop-request to the pipe: pipe_id=%d",
			stream->pipes[i]->pipeline.pipe_id);
		err = ia_css_pipeline_request_stop(&stream->pipes[i]->pipeline);

		/*
		* Exit this loop अगर "ia_css_pipeline_request_stop()"
		* वापसs the error code.
		*
		* The error code would be generated in the following
		* two हालs:
		* (1) The Scalar Processor has alपढ़ोy been stopped.
		* (2) The "Host->SP" event queue is full.
		*
		* As the convention of using CSS API 2.0/2.1, such CSS
		* error code would be propogated from the CSS-पूर्णांकernal
		* API वापसed value to the CSS API वापसed value. Then
		* the CSS driver should capture these error code and
		* handle it in the driver exception handling mechanism.
		*/
		अगर (err)
			जाओ ERR;
	पूर्ण

	/*
	 * In the CSS firmware use scenario "Continuous Preview"
	 * as well as "Continuous Video", the "ia_css_pipe" instance
	 * "Copy Pipe" is activated. This "Copy Pipe" is निजी to
	 * the CSS firmware so that it is not listed in the target
	 * "ia_css_stream" instance.
	 *
	 * We need to stop this "Copy Pipe", as well.
	 */
	अगर (मुख्य_pipe->stream->config.continuous)
	अणु
		काष्ठा ia_css_pipe *copy_pipe = शून्य;

		/* get the reference to "Copy Pipe" */
		अगर (मुख्य_pipe_id == IA_CSS_PIPE_ID_PREVIEW)
			copy_pipe = मुख्य_pipe->pipe_settings.preview.copy_pipe;
		अन्यथा अगर (मुख्य_pipe_id == IA_CSS_PIPE_ID_VIDEO)
			copy_pipe = मुख्य_pipe->pipe_settings.video.copy_pipe;

		/* वापस the error code अगर "Copy Pipe" करोes NOT exist */
		निश्चित(copy_pipe);
		अगर (!copy_pipe) अणु
			IA_CSS_LOG("Copy Pipe does NOT exist!");
			err = -EINVAL;
			जाओ ERR;
		पूर्ण

		/* send the "stop" request to "Copy Pipe" */
		IA_CSS_LOG("Send the stop-request to the pipe: pipe_id=%d",
			copy_pipe->pipeline.pipe_id);
		err = ia_css_pipeline_request_stop(&copy_pipe->pipeline);
	पूर्ण

ERR:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/*
 * @brief Check अगर all "ia_css_pipe" instances in the target
 * "ia_css_stream" instance have stopped.
 *
 * Refer to "Local prototypes" क्रम more info.
 */
/* ISP2401 */
अटल bool
sh_css_pipes_have_stopped(काष्ठा ia_css_stream *stream)
अणु
	bool rval = true;

	काष्ठा ia_css_pipe *मुख्य_pipe;
	क्रमागत ia_css_pipe_id मुख्य_pipe_id;

	पूर्णांक i;

	निश्चित(stream);
	अगर (!stream) अणु
		IA_CSS_LOG("stream does NOT exist!");
		rval = false;
		जाओ RET;
	पूर्ण

	मुख्य_pipe = stream->last_pipe;
	निश्चित(मुख्य_pipe);

	अगर (!मुख्य_pipe) अणु
		IA_CSS_LOG("main_pipe does NOT exist!");
		rval = false;
		जाओ RET;
	पूर्ण

	मुख्य_pipe_id = मुख्य_pipe->mode;
	IA_CSS_ENTER_PRIVATE("main_pipe_id=%d", मुख्य_pipe_id);

	/*
	 * Check अगर every "ia_css_pipe" instance in this target
	 * "ia_css_stream" instance has stopped.
	 */
	क्रम (i = 0; i < stream->num_pipes; i++) अणु
		rval = rval && ia_css_pipeline_has_stopped(&stream->pipes[i]->pipeline);
		IA_CSS_LOG("Pipe has stopped: pipe_id=%d, stopped=%d",
			   stream->pipes[i]->pipeline.pipe_id,
			   rval);
	पूर्ण

	/*
	 * In the CSS firmware use scenario "Continuous Preview"
	 * as well as "Continuous Video", the "ia_css_pipe" instance
	 * "Copy Pipe" is activated. This "Copy Pipe" is निजी to
	 * the CSS firmware so that it is not listed in the target
	 * "ia_css_stream" instance.
	 *
	 * We need to check अगर this "Copy Pipe" has stopped, as well.
	 */
	अगर (मुख्य_pipe->stream->config.continuous) अणु
		काष्ठा ia_css_pipe *copy_pipe = शून्य;

		/* get the reference to "Copy Pipe" */
		अगर (मुख्य_pipe_id == IA_CSS_PIPE_ID_PREVIEW)
			copy_pipe = मुख्य_pipe->pipe_settings.preview.copy_pipe;
		अन्यथा अगर (मुख्य_pipe_id == IA_CSS_PIPE_ID_VIDEO)
			copy_pipe = मुख्य_pipe->pipe_settings.video.copy_pipe;

		/* वापस अगर "Copy Pipe" करोes NOT exist */
		निश्चित(copy_pipe);
		अगर (!copy_pipe) अणु
			IA_CSS_LOG("Copy Pipe does NOT exist!");

			rval = false;
			जाओ RET;
		पूर्ण

		/* check अगर "Copy Pipe" has stopped or not */
		rval = rval && ia_css_pipeline_has_stopped(&copy_pipe->pipeline);
		IA_CSS_LOG("Pipe has stopped: pipe_id=%d, stopped=%d",
			   copy_pipe->pipeline.pipe_id,
			   rval);
	पूर्ण

RET:
	IA_CSS_LEAVE_PRIVATE("rval=%d", rval);
	वापस rval;
पूर्ण

#अगर !defined(ISP2401)
अचिन्हित पूर्णांक
sh_css_get_mipi_sizes_क्रम_check(स्थिर अचिन्हित पूर्णांक port, स्थिर अचिन्हित पूर्णांक idx)
अणु
	OP___निश्चित(port < N_CSI_PORTS);
	OP___निश्चित(idx  < IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES_PER_PORT);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_get_mipi_sizes_for_check(port %d, idx %d): %d\n",
			    port, idx, my_css.mipi_sizes_क्रम_check[port][idx]);
	वापस my_css.mipi_sizes_क्रम_check[port][idx];
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sh_css_pipe_configure_output(
    काष्ठा ia_css_pipe *pipe,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक padded_width,
    क्रमागत ia_css_frame_क्रमmat क्रमmat,
    अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("pipe = %p, width = %d, height = %d, padded width = %d, format = %d, idx = %d",
			     pipe, width, height, padded_width, क्रमmat, idx);
	अगर (!pipe) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	err = ia_css_util_check_res(width, height);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	अगर (pipe->output_info[idx].res.width != width ||
	    pipe->output_info[idx].res.height != height ||
	    pipe->output_info[idx].क्रमmat != क्रमmat) अणु
		ia_css_frame_info_init(
		    &pipe->output_info[idx],
		    width,
		    height,
		    क्रमmat,
		    padded_width);
	पूर्ण
	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

अटल पूर्णांक
sh_css_pipe_get_shading_info(काष्ठा ia_css_pipe *pipe,
			     काष्ठा ia_css_shading_info *shading_info,
			     काष्ठा ia_css_pipe_config *pipe_config)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_binary *binary = शून्य;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_pipe_get_shading_info() enter:\n");

	binary = ia_css_pipe_get_shading_correction_binary(pipe);

	अगर (binary)
	अणु
		err = ia_css_binary_get_shading_info(binary,
						     IA_CSS_SHADING_CORRECTION_TYPE_1,
						     pipe->required_bds_factor,
						     (स्थिर काष्ठा ia_css_stream_config *)&pipe->stream->config,
						     shading_info, pipe_config);

		/* Other function calls can be added here when other shading correction types will be added
		 * in the future.
		 */
	पूर्ण अन्यथा
	अणु
		/* When the pipe करोes not have a binary which has the shading
		 * correction, this function करोes not need to fill the shading
		 * inक्रमmation. It is not a error हाल, and then
		 * this function should वापस 0.
		 */
		स_रखो(shading_info, 0, माप(*shading_info));
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
sh_css_pipe_get_grid_info(काष्ठा ia_css_pipe *pipe,
			  काष्ठा ia_css_grid_info *info) अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_binary *binary = शून्य;

	निश्चित(pipe);
	निश्चित(info);

	IA_CSS_ENTER_PRIVATE("");

	binary = ia_css_pipe_get_s3a_binary(pipe);

	अगर (binary)
	अणु
		err = ia_css_binary_3a_grid_info(binary, info, pipe);
		अगर (err)
			जाओ ERR;
	पूर्ण अन्यथा
		स_रखो(&info->s3a_grid, 0, माप(info->s3a_grid));

	binary = ia_css_pipe_get_sdis_binary(pipe);

	अगर (binary)
	अणु
		ia_css_binary_dvs_grid_info(binary, info, pipe);
		ia_css_binary_dvs_stat_grid_info(binary, info, pipe);
	पूर्ण अन्यथा
	अणु
		स_रखो(&info->dvs_grid.dvs_grid_info, 0,
		       माप(info->dvs_grid.dvs_grid_info));
		स_रखो(&info->dvs_grid.dvs_stat_grid_info, 0,
		       माप(info->dvs_grid.dvs_stat_grid_info));
	पूर्ण

	अगर (binary)
	अणु
		/* copy pipe करोes not have ISP binary*/
		info->isp_in_width = binary->पूर्णांकernal_frame_info.res.width;
		info->isp_in_height = binary->पूर्णांकernal_frame_info.res.height;
	पूर्ण

	info->vamem_type = IA_CSS_VAMEM_TYPE_2;

ERR :
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* ISP2401 */
/*
 * @brief Check अगर a क्रमmat is supported by the pipe.
 *
 */
अटल पूर्णांक
ia_css_pipe_check_क्रमmat(काष्ठा ia_css_pipe *pipe,
			 क्रमागत ia_css_frame_क्रमmat क्रमmat) अणु
	स्थिर क्रमागत ia_css_frame_क्रमmat *supported_क्रमmats;
	पूर्णांक number_of_क्रमmats;
	पूर्णांक found = 0;
	पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("");

	अगर (शून्य == pipe || शून्य == pipe->pipe_settings.video.video_binary.info)
	अणु
		IA_CSS_ERROR("Pipe or binary info is not set");
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	supported_क्रमmats = pipe->pipe_settings.video.video_binary.info->output_क्रमmats;
	number_of_क्रमmats = माप(pipe->pipe_settings.video.video_binary.info->output_क्रमmats) / माप(क्रमागत ia_css_frame_क्रमmat);

	क्रम (i = 0; i < number_of_क्रमmats && !found; i++)
	अणु
		अगर (supported_क्रमmats[i] == क्रमmat) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
	अणु
		IA_CSS_ERROR("Requested format is not supported by binary");
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण अन्यथा
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(0);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक load_video_binaries(काष्ठा ia_css_pipe *pipe)
अणु
	काष्ठा ia_css_frame_info video_in_info, tnr_info,
		       *video_vf_info, video_bds_out_info, *pipe_out_info, *pipe_vf_out_info;
	bool online;
	पूर्णांक err = 0;
	bool continuous = pipe->stream->config.continuous;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_output_pins;
	काष्ठा ia_css_frame_info video_bin_out_info;
	bool need_scaler = false;
	bool vf_res_dअगरferent_than_output = false;
	bool need_vf_pp = false;
	पूर्णांक vf_ds_log2;
	काष्ठा ia_css_video_settings *mycs  = &pipe->pipe_settings.video;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_VIDEO);
	/* we only test the video_binary because offline video करोesn't need a
	 * vf_pp binary and online करोes not (always use) the copy_binary.
	 * All are always reset at the same समय anyway.
	 */
	अगर (mycs->video_binary.info)
		वापस 0;

	online = pipe->stream->config.online;
	pipe_out_info = &pipe->output_info[0];
	pipe_vf_out_info = &pipe->vf_output_info[0];

	निश्चित(pipe_out_info);

	/*
	 * There is no explicit input क्रमmat requirement क्रम raw or yuv
	 * What matters is that there is a binary that supports the stream क्रमmat.
	 * This is checked in the binary_find(), so no need to check it here
	 */
	err = ia_css_util_check_input(&pipe->stream->config, false, false);
	अगर (err)
		वापस err;
	/* cannot have online video and input_mode memory */
	अगर (online && pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY)
		वापस -EINVAL;
	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0]) अणु
		err = ia_css_util_check_vf_out_info(pipe_out_info,
						    pipe_vf_out_info);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = ia_css_frame_check_info(pipe_out_info);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pipe->out_yuv_ds_input_info.res.width)
		video_bin_out_info = pipe->out_yuv_ds_input_info;
	अन्यथा
		video_bin_out_info = *pipe_out_info;

	/* Video */
	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0]) अणु
		video_vf_info = pipe_vf_out_info;
		vf_res_dअगरferent_than_output = (video_vf_info->res.width !=
						video_bin_out_info.res.width) ||
					       (video_vf_info->res.height != video_bin_out_info.res.height);
	पूर्ण अन्यथा अणु
		video_vf_info = शून्य;
	पूर्ण

	need_scaler = need_करोwnscaling(video_bin_out_info.res, pipe_out_info->res);

	/* we build up the pipeline starting at the end */
	/* YUV post-processing अगर needed */
	अगर (need_scaler) अणु
		काष्ठा ia_css_cas_binary_descr cas_scaler_descr = अणु पूर्ण;

		/* NV12 is the common क्रमmat that is supported by both */
		/* yuv_scaler and the video_xx_isp2_min binaries. */
		video_bin_out_info.क्रमmat = IA_CSS_FRAME_FORMAT_NV12;

		err = ia_css_pipe_create_cas_scaler_desc_single_output(
			  &video_bin_out_info,
			  pipe_out_info,
			  शून्य,
			  &cas_scaler_descr);
		अगर (err)
			वापस err;
		mycs->num_yuv_scaler = cas_scaler_descr.num_stage;
		mycs->yuv_scaler_binary = kzalloc(cas_scaler_descr.num_stage *
						  माप(काष्ठा ia_css_binary), GFP_KERNEL);
		अगर (!mycs->yuv_scaler_binary) अणु
			err = -ENOMEM;
			वापस err;
		पूर्ण
		mycs->is_output_stage = kzalloc(cas_scaler_descr.num_stage
						* माप(bool), GFP_KERNEL);
		अगर (!mycs->is_output_stage) अणु
			err = -ENOMEM;
			वापस err;
		पूर्ण
		क्रम (i = 0; i < cas_scaler_descr.num_stage; i++) अणु
			काष्ठा ia_css_binary_descr yuv_scaler_descr;

			mycs->is_output_stage[i] = cas_scaler_descr.is_output_stage[i];
			ia_css_pipe_get_yuvscaler_binarydesc(pipe,
							     &yuv_scaler_descr, &cas_scaler_descr.in_info[i],
							     &cas_scaler_descr.out_info[i],
							     &cas_scaler_descr.पूर्णांकernal_out_info[i],
							     &cas_scaler_descr.vf_info[i]);
			err = ia_css_binary_find(&yuv_scaler_descr,
						 &mycs->yuv_scaler_binary[i]);
			अगर (err) अणु
				kमुक्त(mycs->is_output_stage);
				mycs->is_output_stage = शून्य;
				वापस err;
			पूर्ण
		पूर्ण
		ia_css_pipe_destroy_cas_scaler_desc(&cas_scaler_descr);
	पूर्ण

	अणु
		काष्ठा ia_css_binary_descr video_descr;
		क्रमागत ia_css_frame_क्रमmat vf_info_क्रमmat;

		err = ia_css_pipe_get_video_binarydesc(pipe,
						       &video_descr, &video_in_info, &video_bds_out_info, &video_bin_out_info,
						       video_vf_info,
						       pipe->stream->config.left_padding);
		अगर (err)
			वापस err;

		/* In the हाल where video_vf_info is not शून्य, this allows
		 * us to find a potential video library with desired vf क्रमmat.
		 * If success, no vf_pp binary is needed.
		 * If failed, we will look up video binary with YUV_LINE vf क्रमmat
		 */
		err = ia_css_binary_find(&video_descr,
					 &mycs->video_binary);

		अगर (err) अणु
			अगर (video_vf_info) अणु
				/* This will करो another video binary lookup later क्रम YUV_LINE क्रमmat*/
				need_vf_pp = true;
			पूर्ण अन्यथा
				वापस err;
		पूर्ण अन्यथा अगर (video_vf_info) अणु
			/* The first video binary lookup is successful, but we may
			 * still need vf_pp binary based on additiona check */
			num_output_pins = mycs->video_binary.info->num_output_pins;
			vf_ds_log2 = mycs->video_binary.vf_करोwnscale_log2;

			/* If the binary has dual output pins, we need vf_pp अगर the resolution
			* is dअगरferent. */
			need_vf_pp |= ((num_output_pins == 2) && vf_res_dअगरferent_than_output);

			/* If the binary has single output pin, we need vf_pp अगर additional
			* scaling is needed क्रम vf */
			need_vf_pp |= ((num_output_pins == 1) &&
				       ((video_vf_info->res.width << vf_ds_log2 != pipe_out_info->res.width) ||
					(video_vf_info->res.height << vf_ds_log2 != pipe_out_info->res.height)));
		पूर्ण

		अगर (need_vf_pp) अणु
			/* save the current vf_info क्रमmat क्रम restoration later */
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "load_video_binaries() need_vf_pp; find video binary with YUV_LINE again\n");

			vf_info_क्रमmat = video_vf_info->क्रमmat;

			अगर (!pipe->config.enable_vfpp_bci)
				ia_css_frame_info_set_क्रमmat(video_vf_info,
							     IA_CSS_FRAME_FORMAT_YUV_LINE);

			ia_css_binary_destroy_isp_parameters(&mycs->video_binary);

			err = ia_css_binary_find(&video_descr,
						 &mycs->video_binary);

			/* restore original vf_info क्रमmat */
			ia_css_frame_info_set_क्रमmat(video_vf_info,
						     vf_info_क्रमmat);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	/* If a video binary करोes not use a ref_frame, we set the frame delay
	 * to 0. This is the हाल क्रम the 1-stage low-घातer video binary. */
	अगर (!mycs->video_binary.info->sp.enable.ref_frame)
		pipe->dvs_frame_delay = 0;

	/* The delay latency determines the number of invalid frames after
	 * a stream is started. */
	pipe->num_invalid_frames = pipe->dvs_frame_delay;
	pipe->info.num_invalid_frames = pipe->num_invalid_frames;

	/* Viewfinder frames also decrement num_invalid_frames. If the pipe
	 * outमाला_दो a viewfinder output, then we need द्विगुन the number of
	 * invalid frames */
	अगर (video_vf_info)
		pipe->num_invalid_frames *= 2;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "load_video_binaries() num_invalid_frames=%d dvs_frame_delay=%d\n",
			    pipe->num_invalid_frames, pipe->dvs_frame_delay);

	/* pqiao TODO: temp hack क्रम PO, should be हटाओd after offline YUVPP is enabled */
#अगर !defined(ISP2401)
	/* Copy */
	अगर (!online && !continuous) अणु
		/* TODO: what exactly needs करोing, prepend the copy binary to
		 *	 video base this only on !online?
		 */
		err = load_copy_binary(pipe,
				       &mycs->copy_binary,
				       &mycs->video_binary);
		अगर (err)
			वापस err;
	पूर्ण
#अन्यथा
	(व्योम)continuous;
#पूर्ण_अगर

#अगर !defined(HAS_OUTPUT_SYSTEM)
	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0] && need_vf_pp) अणु
		काष्ठा ia_css_binary_descr vf_pp_descr;

		अगर (mycs->video_binary.vf_frame_info.क्रमmat
		    == IA_CSS_FRAME_FORMAT_YUV_LINE) अणु
			ia_css_pipe_get_vfpp_binarydesc(pipe, &vf_pp_descr,
							&mycs->video_binary.vf_frame_info,
							pipe_vf_out_info);
		पूर्ण अन्यथा अणु
			/* output from मुख्य binary is not yuv line. currently this is
			 * possible only when bci is enabled on vfpp output */
			निश्चित(pipe->config.enable_vfpp_bci);
			ia_css_pipe_get_yuvscaler_binarydesc(pipe, &vf_pp_descr,
							     &mycs->video_binary.vf_frame_info,
							     pipe_vf_out_info, शून्य, शून्य);
		पूर्ण

		err = ia_css_binary_find(&vf_pp_descr,
					 &mycs->vf_pp_binary);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	err = allocate_delay_frames(pipe);

	अगर (err)
		वापस err;

	अगर (mycs->video_binary.info->sp.enable.block_output) अणु
		अचिन्हित पूर्णांक tnr_width;
		अचिन्हित पूर्णांक tnr_height;

		tnr_info = mycs->video_binary.out_frame_info[0];

		अगर (IS_ISP2401) अणु
			/* Select resolution क्रम TNR. If
			* output_प्रणाली_in_resolution(GDC_out_resolution) is
			* being used, then select that as it will also be in resolution क्रम
			* TNR. At present, it only make sense क्रम Skycam */
			अगर (pipe->config.output_प्रणाली_in_res.width &&
			    pipe->config.output_प्रणाली_in_res.height) अणु
				tnr_width = pipe->config.output_प्रणाली_in_res.width;
				tnr_height = pipe->config.output_प्रणाली_in_res.height;
			पूर्ण अन्यथा अणु
				tnr_width = tnr_info.res.width;
				tnr_height = tnr_info.res.height;
			पूर्ण

			/* Make tnr reference buffers output block width(in pix) align */
			tnr_info.res.width  = CEIL_MUL(tnr_width,
						       (mycs->video_binary.info->sp.block.block_width * ISP_NWAY));
			tnr_info.padded_width = tnr_info.res.width;
		पूर्ण अन्यथा अणु
			tnr_height = tnr_info.res.height;
		पूर्ण

		/* Make tnr reference buffers output block height align */
		tnr_info.res.height = CEIL_MUL(tnr_height,
					       mycs->video_binary.info->sp.block.output_block_height);
	पूर्ण अन्यथा अणु
		tnr_info = mycs->video_binary.पूर्णांकernal_frame_info;
	पूर्ण
	tnr_info.क्रमmat = IA_CSS_FRAME_FORMAT_YUV_LINE;
	tnr_info.raw_bit_depth = SH_CSS_TNR_BIT_DEPTH;

	क्रम (i = 0; i < NUM_TNR_FRAMES; i++) अणु
		अगर (mycs->tnr_frames[i]) अणु
			ia_css_frame_मुक्त(mycs->tnr_frames[i]);
			mycs->tnr_frames[i] = शून्य;
		पूर्ण
		err = ia_css_frame_allocate_from_info(
			  &mycs->tnr_frames[i],
			  &tnr_info);
		अगर (err)
			वापस err;
	पूर्ण
	IA_CSS_LEAVE_PRIVATE("");
	वापस 0;
पूर्ण

अटल पूर्णांक
unload_video_binaries(काष्ठा ia_css_pipe *pipe) अणु
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);

	अगर ((!pipe) || (pipe->mode != IA_CSS_PIPE_ID_VIDEO))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	ia_css_binary_unload(&pipe->pipe_settings.video.copy_binary);
	ia_css_binary_unload(&pipe->pipe_settings.video.video_binary);
	ia_css_binary_unload(&pipe->pipe_settings.video.vf_pp_binary);

	क्रम (i = 0; i < pipe->pipe_settings.video.num_yuv_scaler; i++)
		ia_css_binary_unload(&pipe->pipe_settings.video.yuv_scaler_binary[i]);

	kमुक्त(pipe->pipe_settings.video.is_output_stage);
	pipe->pipe_settings.video.is_output_stage = शून्य;
	kमुक्त(pipe->pipe_settings.video.yuv_scaler_binary);
	pipe->pipe_settings.video.yuv_scaler_binary = शून्य;

	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

अटल पूर्णांक video_start(काष्ठा ia_css_pipe *pipe)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_pipe *copy_pipe, *capture_pipe;
	क्रमागत sh_css_pipe_config_override copy_ovrd;
	क्रमागत ia_css_input_mode video_pipe_input_mode;

	स्थिर काष्ठा ia_css_coordinate *coord = शून्य;
	स्थिर काष्ठा ia_css_isp_parameters *params = शून्य;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (pipe->mode != IA_CSS_PIPE_ID_VIDEO)) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	video_pipe_input_mode = pipe->stream->config.mode;

	copy_pipe    = pipe->pipe_settings.video.copy_pipe;
	capture_pipe = pipe->pipe_settings.video.capture_pipe;

	sh_css_metrics_start_frame();

	/* multi stream video needs mipi buffers */

	err = send_mipi_frames(pipe);
	अगर (err)
		वापस err;

	send_raw_frames(pipe);
	अणु
		अचिन्हित पूर्णांक thपढ़ो_id;

		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		copy_ovrd = 1 << thपढ़ो_id;

		अगर (pipe->stream->cont_capt) अणु
			ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(capture_pipe),
							 &thपढ़ो_id);
			copy_ovrd |= 1 << thपढ़ो_id;
		पूर्ण
	पूर्ण

	अगर (IS_ISP2401) अणु
		coord = &pipe->config.पूर्णांकernal_frame_origin_bqs_on_sctbl;
		params = pipe->stream->isp_params_configs;
	पूर्ण

	/* Conकाष्ठा and load the copy pipe */
	अगर (pipe->stream->config.continuous) अणु
		sh_css_sp_init_pipeline(&copy_pipe->pipeline,
					IA_CSS_PIPE_ID_COPY,
					(uपूर्णांक8_t)ia_css_pipe_get_pipe_num(copy_pipe),
					false,
					pipe->stream->config.pixels_per_घड़ी == 2, false,
					false, pipe->required_bds_factor,
					copy_ovrd,
					pipe->stream->config.mode,
					&pipe->stream->config.metadata_config,
					&pipe->stream->info.metadata_info,
					pipe->stream->config.source.port.port,
					coord,
					params);

		/* make the video pipe start with mem mode input, copy handles
		   the actual mode */
		video_pipe_input_mode = IA_CSS_INPUT_MODE_MEMORY;
	पूर्ण

	/* Conकाष्ठा and load the capture pipe */
	अगर (pipe->stream->cont_capt) अणु
		sh_css_sp_init_pipeline(&capture_pipe->pipeline,
					IA_CSS_PIPE_ID_CAPTURE,
					(uपूर्णांक8_t)ia_css_pipe_get_pipe_num(capture_pipe),
					capture_pipe->config.शेष_capture_config.enable_xnr != 0,
					capture_pipe->stream->config.pixels_per_घड़ी == 2,
					true, /* continuous */
					false, /* offline */
					capture_pipe->required_bds_factor,
					0,
					IA_CSS_INPUT_MODE_MEMORY,
					&pipe->stream->config.metadata_config,
					&pipe->stream->info.metadata_info,
					(क्रमागत mipi_port_id)0,
					coord,
					params);
	पूर्ण

	start_pipe(pipe, copy_ovrd, video_pipe_input_mode);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल
पूर्णांक sh_css_pipe_get_viewfinder_frame_info(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_frame_info *info,
    अचिन्हित पूर्णांक idx)
अणु
	निश्चित(pipe);
	निश्चित(info);

	/* We could prपूर्णांक the poपूर्णांकer as input arg, and the values as output */
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_pipe_get_viewfinder_frame_info() enter: void\n");

	अगर (pipe->mode == IA_CSS_PIPE_ID_CAPTURE &&
	    (pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_RAW ||
	     pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_BAYER))
		वापस -EINVAL;
	/* offline video करोes not generate viewfinder output */
	*info = pipe->vf_output_info[idx];

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_pipe_get_viewfinder_frame_info() leave: \
		info.res.width=%d, info.res.height=%d, \
		info.padded_width=%d, info.क्रमmat=%d, \
		info.raw_bit_depth=%d, info.raw_bayer_order=%d\न",
			    info->res.width, info->res.height,
			    info->padded_width, info->क्रमmat,
			    info->raw_bit_depth, info->raw_bayer_order);

	वापस 0;
पूर्ण

अटल पूर्णांक
sh_css_pipe_configure_viewfinder(काष्ठा ia_css_pipe *pipe, अचिन्हित पूर्णांक width,
				 अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक min_width,
				 क्रमागत ia_css_frame_क्रमmat क्रमmat,
				 अचिन्हित पूर्णांक idx) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("pipe = %p, width = %d, height = %d, min_width = %d, format = %d, idx = %d\n",
			     pipe, width, height, min_width, क्रमmat, idx);

	अगर (!pipe)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	err = ia_css_util_check_res(width, height);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	अगर (pipe->vf_output_info[idx].res.width != width ||
	    pipe->vf_output_info[idx].res.height != height ||
	    pipe->vf_output_info[idx].क्रमmat != क्रमmat)
	अणु
		ia_css_frame_info_init(&pipe->vf_output_info[idx], width, height,
				       क्रमmat, min_width);
	पूर्ण
	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

अटल पूर्णांक load_copy_binaries(काष्ठा ia_css_pipe *pipe)
अणु
	पूर्णांक err = 0;

	निश्चित(pipe);
	IA_CSS_ENTER_PRIVATE("");

	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE ||
	       pipe->mode == IA_CSS_PIPE_ID_COPY);
	अगर (pipe->pipe_settings.capture.copy_binary.info)
		वापस 0;

	err = ia_css_frame_check_info(&pipe->output_info[0]);
	अगर (err)
		जाओ ERR;

	err = verअगरy_copy_out_frame_क्रमmat(pipe);
	अगर (err)
		जाओ ERR;

	err = load_copy_binary(pipe,
			       &pipe->pipe_settings.capture.copy_binary,
			       शून्य);

ERR:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल bool need_capture_pp(
    स्थिर काष्ठा ia_css_pipe *pipe)
अणु
	स्थिर काष्ठा ia_css_frame_info *out_info = &pipe->output_info[0];

	IA_CSS_ENTER_LEAVE_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE);

	अगर (IS_ISP2401) अणु
		/* ldc and capture_pp are not supported in the same pipeline */
		अगर (need_capt_ldc(pipe))
			वापस false;
	पूर्ण

	/* determine whether we need to use the capture_pp binary.
	 * This is needed क्रम:
	 *   1. XNR or
	 *   2. Digital Zoom or
	 *   3. YUV करोwnscaling
	 */
	अगर (pipe->out_yuv_ds_input_info.res.width &&
	    ((pipe->out_yuv_ds_input_info.res.width != out_info->res.width) ||
	     (pipe->out_yuv_ds_input_info.res.height != out_info->res.height)))
		वापस true;

	अगर (pipe->config.शेष_capture_config.enable_xnr != 0)
		वापस true;

	अगर ((pipe->stream->isp_params_configs->dz_config.dx < HRT_GDC_N) ||
	    (pipe->stream->isp_params_configs->dz_config.dy < HRT_GDC_N) ||
	    pipe->config.enable_dz)
		वापस true;

	वापस false;
पूर्ण

अटल bool need_capt_ldc(
    स्थिर काष्ठा ia_css_pipe *pipe)
अणु
	IA_CSS_ENTER_LEAVE_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE);
	वापस (pipe->extra_config.enable_dvs_6axis) ? true : false;
पूर्ण

अटल पूर्णांक set_num_primary_stages(अचिन्हित पूर्णांक *num,
	क्रमागत ia_css_pipe_version version)
अणु
	पूर्णांक err = 0;

	अगर (!num)
		वापस -EINVAL;

	चयन (version) अणु
	हाल IA_CSS_PIPE_VERSION_2_6_1:
		*num = NUM_PRIMARY_HQ_STAGES;
		अवरोध;
	हाल IA_CSS_PIPE_VERSION_2_2:
	हाल IA_CSS_PIPE_VERSION_1:
		*num = NUM_PRIMARY_STAGES;
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक load_primary_binaries(
    काष्ठा ia_css_pipe *pipe)
अणु
	bool online = false;
	bool need_pp = false;
	bool need_isp_copy_binary = false;
	bool need_ldc = false;
#अगर_घोषित ISP2401
	bool sensor = false;
#अन्यथा
	bool memory, continuous;
#पूर्ण_अगर
	काष्ठा ia_css_frame_info prim_in_info,
		       prim_out_info,
		       capt_pp_out_info, vf_info,
		       *vf_pp_in_info, *pipe_out_info,
		       *pipe_vf_out_info, *capt_pp_in_info,
		       capt_ldc_out_info;
	पूर्णांक err = 0;
	काष्ठा ia_css_capture_settings *mycs;
	अचिन्हित पूर्णांक i;
	bool need_extra_yuv_scaler = false;
	काष्ठा ia_css_binary_descr prim_descr[MAX_NUM_PRIMARY_STAGES];

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->stream);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE ||
	       pipe->mode == IA_CSS_PIPE_ID_COPY);

	online = pipe->stream->config.online;
#अगर_घोषित ISP2401
	sensor = (pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR);
#अन्यथा
	memory = pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY;
	continuous = pipe->stream->config.continuous;
#पूर्ण_अगर

	mycs = &pipe->pipe_settings.capture;
	pipe_out_info = &pipe->output_info[0];
	pipe_vf_out_info = &pipe->vf_output_info[0];

	अगर (mycs->primary_binary[0].info)
		वापस 0;

	err = set_num_primary_stages(&mycs->num_primary_stage,
				     pipe->config.isp_pipe_version);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0]) अणु
		err = ia_css_util_check_vf_out_info(pipe_out_info, pipe_vf_out_info);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = ia_css_frame_check_info(pipe_out_info);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण
	need_pp = need_capture_pp(pipe);

	/* we use the vf output info to get the primary/capture_pp binary
	   configured क्रम vf_veceven. It will select the बंदst करोwnscaling
	   factor. */
	vf_info = *pipe_vf_out_info;

	/*
	 * WARNING: The #अगर def flag has been added below as a
	 * temporary solution to solve the problem of enabling the
	 * view finder in a single binary in a capture flow. The
	 * vf-pp stage has been हटाओd क्रम Skycam in the solution
	 * provided. The vf-pp stage should be re-पूर्णांकroduced when
	 * required. This should not be considered as a clean solution.
	 * Proper investigation should be करोne to come up with the clean
	 * solution.
	 * */
	ia_css_frame_info_set_क्रमmat(&vf_info, IA_CSS_FRAME_FORMAT_YUV_LINE);

	/* TODO: All this yuv_scaler and capturepp calculation logic
	 * can be shared later. Capture_pp is also a yuv_scale binary
	 * with extra XNR funcionality. Thereक्रमe, it can be made as the
	 * first step of the cascade. */
	capt_pp_out_info = pipe->out_yuv_ds_input_info;
	capt_pp_out_info.क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
	capt_pp_out_info.res.width  /= MAX_PREFERRED_YUV_DS_PER_STEP;
	capt_pp_out_info.res.height /= MAX_PREFERRED_YUV_DS_PER_STEP;
	ia_css_frame_info_set_width(&capt_pp_out_info, capt_pp_out_info.res.width, 0);

	need_extra_yuv_scaler = need_करोwnscaling(capt_pp_out_info.res,
						 pipe_out_info->res);

	अगर (need_extra_yuv_scaler) अणु
		काष्ठा ia_css_cas_binary_descr cas_scaler_descr = अणु पूर्ण;

		err = ia_css_pipe_create_cas_scaler_desc_single_output(
			  &capt_pp_out_info,
			  pipe_out_info,
			  शून्य,
			  &cas_scaler_descr);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
		mycs->num_yuv_scaler = cas_scaler_descr.num_stage;
		mycs->yuv_scaler_binary = kzalloc(cas_scaler_descr.num_stage *
						  माप(काष्ठा ia_css_binary), GFP_KERNEL);
		अगर (!mycs->yuv_scaler_binary) अणु
			err = -ENOMEM;
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
		mycs->is_output_stage = kzalloc(cas_scaler_descr.num_stage *
						माप(bool), GFP_KERNEL);
		अगर (!mycs->is_output_stage) अणु
			err = -ENOMEM;
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
		क्रम (i = 0; i < cas_scaler_descr.num_stage; i++) अणु
			काष्ठा ia_css_binary_descr yuv_scaler_descr;

			mycs->is_output_stage[i] = cas_scaler_descr.is_output_stage[i];
			ia_css_pipe_get_yuvscaler_binarydesc(pipe,
							     &yuv_scaler_descr, &cas_scaler_descr.in_info[i],
							     &cas_scaler_descr.out_info[i],
							     &cas_scaler_descr.पूर्णांकernal_out_info[i],
							     &cas_scaler_descr.vf_info[i]);
			err = ia_css_binary_find(&yuv_scaler_descr,
						 &mycs->yuv_scaler_binary[i]);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
		पूर्ण
		ia_css_pipe_destroy_cas_scaler_desc(&cas_scaler_descr);

	पूर्ण अन्यथा अणु
		capt_pp_out_info = pipe->output_info[0];
	पूर्ण

	/* TODO Do we disable ldc क्रम skycam */
	need_ldc = need_capt_ldc(pipe);
	अगर (IS_ISP2401 && need_ldc) अणु
		/* ldc and capt_pp are not supported in the same pipeline */
		काष्ठा ia_css_binary_descr capt_ldc_descr;

		ia_css_pipe_get_ldc_binarydesc(pipe,
					       &capt_ldc_descr, &prim_out_info,
					       &capt_pp_out_info);

		err = ia_css_binary_find(&capt_ldc_descr,
					 &mycs->capture_ldc_binary);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
		need_pp = false;
		need_ldc = false;
	पूर्ण

	/* we build up the pipeline starting at the end */
	/* Capture post-processing */
	अगर (need_pp) अणु
		काष्ठा ia_css_binary_descr capture_pp_descr;

		अगर (!IS_ISP2401)
			capt_pp_in_info = need_ldc ? &capt_ldc_out_info : &prim_out_info;
		अन्यथा
			capt_pp_in_info = &prim_out_info;

		ia_css_pipe_get_capturepp_binarydesc(pipe,
							&capture_pp_descr, capt_pp_in_info,
							&capt_pp_out_info, &vf_info);
		err = ia_css_binary_find(&capture_pp_descr,
					    &mycs->capture_pp_binary);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण

		अगर (need_ldc) अणु
			काष्ठा ia_css_binary_descr capt_ldc_descr;

			ia_css_pipe_get_ldc_binarydesc(pipe,
							&capt_ldc_descr, &prim_out_info,
							&capt_ldc_out_info);

			err = ia_css_binary_find(&capt_ldc_descr,
						    &mycs->capture_ldc_binary);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		prim_out_info = *pipe_out_info;
	पूर्ण

	/* Primary */
	क्रम (i = 0; i < mycs->num_primary_stage; i++) अणु
		काष्ठा ia_css_frame_info *local_vf_info = शून्य;

		अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0] &&
		    (i == mycs->num_primary_stage - 1))
			local_vf_info = &vf_info;
		ia_css_pipe_get_primary_binarydesc(pipe, &prim_descr[i], &prim_in_info,
						    &prim_out_info, local_vf_info, i);
		err = ia_css_binary_find(&prim_descr[i], &mycs->primary_binary[i]);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Viewfinder post-processing */
	अगर (need_pp)
		vf_pp_in_info = &mycs->capture_pp_binary.vf_frame_info;
	अन्यथा
		vf_pp_in_info = &mycs->primary_binary[mycs->num_primary_stage - 1].vf_frame_info;

	/*
	    * WARNING: The #अगर def flag has been added below as a
	    * temporary solution to solve the problem of enabling the
	    * view finder in a single binary in a capture flow. The
	    * vf-pp stage has been हटाओd क्रम Skycam in the solution
	    * provided. The vf-pp stage should be re-पूर्णांकroduced when
	    * required. Thisshould not be considered as a clean solution.
	    * Proper  * investigation should be करोne to come up with the clean
	    * solution.
	    * */
	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0]) अणु
		काष्ठा ia_css_binary_descr vf_pp_descr;

		ia_css_pipe_get_vfpp_binarydesc(pipe,
						&vf_pp_descr, vf_pp_in_info, pipe_vf_out_info);
		err = ia_css_binary_find(&vf_pp_descr, &mycs->vf_pp_binary);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण
	err = allocate_delay_frames(pipe);

	अगर (err)
		वापस err;

#अगर_घोषित ISP2401
	/* When the input प्रणाली is 2401, only the Direct Sensor Mode
	    * Offline Capture uses the ISP copy binary.
	    */
	need_isp_copy_binary = !online && sensor;
#अन्यथा
	need_isp_copy_binary = !online && !continuous && !memory;
#पूर्ण_अगर

	/* ISP Copy */
	अगर (need_isp_copy_binary) अणु
		err = load_copy_binary(pipe,
					&mycs->copy_binary,
					&mycs->primary_binary[0]);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
allocate_delay_frames(काष्ठा ia_css_pipe *pipe) अणु
	अचिन्हित पूर्णांक num_delay_frames = 0, i = 0;
	अचिन्हित पूर्णांक dvs_frame_delay = 0;
	काष्ठा ia_css_frame_info ref_info;
	पूर्णांक err = 0;
	क्रमागत ia_css_pipe_id mode = IA_CSS_PIPE_ID_VIDEO;
	काष्ठा ia_css_frame **delay_frames = शून्य;

	IA_CSS_ENTER_PRIVATE("");

	अगर (!pipe)
	अणु
		IA_CSS_ERROR("Invalid args - pipe %p", pipe);
		वापस -EINVAL;
	पूर्ण

	mode = pipe->mode;
	dvs_frame_delay = pipe->dvs_frame_delay;

	अगर (dvs_frame_delay > 0)
		num_delay_frames = dvs_frame_delay + 1;

	चयन (mode)
	अणु
	हाल IA_CSS_PIPE_ID_CAPTURE: अणु
		काष्ठा ia_css_capture_settings *mycs_capture = &pipe->pipe_settings.capture;
		(व्योम)mycs_capture;
		वापस err;
	पूर्ण
	अवरोध;
	हाल IA_CSS_PIPE_ID_VIDEO: अणु
		काष्ठा ia_css_video_settings *mycs_video = &pipe->pipe_settings.video;

		ref_info = mycs_video->video_binary.पूर्णांकernal_frame_info;
		/*The ref frame expects
		    *	1. Y plane
		    *	2. UV plane with line पूर्णांकerleaving, like below
		    *		UUUUUU(width/2 बार) VVVVVVVV..(width/2 बार)
		    *
		    *	This क्रमmat is not YUV420(which has Y, U and V planes).
		    *	Its बंदr to NV12, except that the UV plane has UV
		    *	पूर्णांकerleaving, like UVUVUVUVUVUVUVUVU...
		    *
		    *	TODO: make this ref_frame क्रमmat as a separate frame क्रमmat
		    */
		ref_info.क्रमmat        = IA_CSS_FRAME_FORMAT_NV12;
		delay_frames = mycs_video->delay_frames;
	पूर्ण
	अवरोध;
	हाल IA_CSS_PIPE_ID_PREVIEW: अणु
		काष्ठा ia_css_preview_settings *mycs_preview = &pipe->pipe_settings.preview;

		ref_info = mycs_preview->preview_binary.पूर्णांकernal_frame_info;
		/*The ref frame expects
		    *	1. Y plane
		    *	2. UV plane with line पूर्णांकerleaving, like below
		    *		UUUUUU(width/2 बार) VVVVVVVV..(width/2 बार)
		    *
		    *	This क्रमmat is not YUV420(which has Y, U and V planes).
		    *	Its बंदr to NV12, except that the UV plane has UV
		    *	पूर्णांकerleaving, like UVUVUVUVUVUVUVUVU...
		    *
		    *	TODO: make this ref_frame क्रमmat as a separate frame क्रमmat
		    */
		ref_info.क्रमmat        = IA_CSS_FRAME_FORMAT_NV12;
		delay_frames = mycs_preview->delay_frames;
	पूर्ण
	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ref_info.raw_bit_depth = SH_CSS_REF_BIT_DEPTH;

	निश्चित(num_delay_frames <= MAX_NUM_VIDEO_DELAY_FRAMES);
	क्रम (i = 0; i < num_delay_frames; i++)
	अणु
		err = ia_css_frame_allocate_from_info(&delay_frames[i],	&ref_info);
		अगर (err)
			वापस err;
	पूर्ण
	IA_CSS_LEAVE_PRIVATE("");
	वापस 0;
पूर्ण

अटल पूर्णांक load_advanced_binaries(
    काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_frame_info pre_in_info, gdc_in_info,
			post_in_info, post_out_info,
			vf_info, *vf_pp_in_info, *pipe_out_info,
			*pipe_vf_out_info;
	bool need_pp;
	bool need_isp_copy = true;
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("");

	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE ||
		pipe->mode == IA_CSS_PIPE_ID_COPY);
	अगर (pipe->pipe_settings.capture.pre_isp_binary.info)
		वापस 0;
	pipe_out_info = &pipe->output_info[0];
	pipe_vf_out_info = &pipe->vf_output_info[0];

	vf_info = *pipe_vf_out_info;
	err = ia_css_util_check_vf_out_info(pipe_out_info, &vf_info);
	अगर (err)
		वापस err;
	need_pp = need_capture_pp(pipe);

	ia_css_frame_info_set_क्रमmat(&vf_info,
					IA_CSS_FRAME_FORMAT_YUV_LINE);

	/* we build up the pipeline starting at the end */
	/* Capture post-processing */
	अगर (need_pp) अणु
		काष्ठा ia_css_binary_descr capture_pp_descr;

		ia_css_pipe_get_capturepp_binarydesc(pipe,
							&capture_pp_descr, &post_out_info, pipe_out_info, &vf_info);
		err = ia_css_binary_find(&capture_pp_descr,
					    &pipe->pipe_settings.capture.capture_pp_binary);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		post_out_info = *pipe_out_info;
	पूर्ण

	/* Post-gdc */
	अणु
		काष्ठा ia_css_binary_descr post_gdc_descr;

		ia_css_pipe_get_post_gdc_binarydesc(pipe,
						    &post_gdc_descr, &post_in_info, &post_out_info, &vf_info);
		err = ia_css_binary_find(&post_gdc_descr,
					    &pipe->pipe_settings.capture.post_isp_binary);
		अगर (err)
			वापस err;
	पूर्ण

	/* Gdc */
	अणु
		काष्ठा ia_css_binary_descr gdc_descr;

		ia_css_pipe_get_gdc_binarydesc(pipe, &gdc_descr, &gdc_in_info,
						&pipe->pipe_settings.capture.post_isp_binary.in_frame_info);
		err = ia_css_binary_find(&gdc_descr,
					    &pipe->pipe_settings.capture.anr_gdc_binary);
		अगर (err)
			वापस err;
	पूर्ण
	pipe->pipe_settings.capture.anr_gdc_binary.left_padding =
	    pipe->pipe_settings.capture.post_isp_binary.left_padding;

	/* Pre-gdc */
	अणु
		काष्ठा ia_css_binary_descr pre_gdc_descr;

		ia_css_pipe_get_pre_gdc_binarydesc(pipe, &pre_gdc_descr, &pre_in_info,
						    &pipe->pipe_settings.capture.anr_gdc_binary.in_frame_info);
		err = ia_css_binary_find(&pre_gdc_descr,
					    &pipe->pipe_settings.capture.pre_isp_binary);
		अगर (err)
			वापस err;
	पूर्ण
	pipe->pipe_settings.capture.pre_isp_binary.left_padding =
	    pipe->pipe_settings.capture.anr_gdc_binary.left_padding;

	/* Viewfinder post-processing */
	अगर (need_pp) अणु
		vf_pp_in_info =
		    &pipe->pipe_settings.capture.capture_pp_binary.vf_frame_info;
	पूर्ण अन्यथा अणु
		vf_pp_in_info =
		    &pipe->pipe_settings.capture.post_isp_binary.vf_frame_info;
	पूर्ण

	अणु
		काष्ठा ia_css_binary_descr vf_pp_descr;

		ia_css_pipe_get_vfpp_binarydesc(pipe,
						&vf_pp_descr, vf_pp_in_info, pipe_vf_out_info);
		err = ia_css_binary_find(&vf_pp_descr,
					    &pipe->pipe_settings.capture.vf_pp_binary);
		अगर (err)
			वापस err;
	पूर्ण

	/* Copy */
#अगर_घोषित ISP2401
	/* For CSI2+, only the direct sensor mode/online requires ISP copy */
	need_isp_copy = pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR;
#पूर्ण_अगर
	अगर (need_isp_copy)
		load_copy_binary(pipe,
				    &pipe->pipe_settings.capture.copy_binary,
				    &pipe->pipe_settings.capture.pre_isp_binary);

	वापस err;
पूर्ण

अटल पूर्णांक load_bayer_isp_binaries(
    काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_frame_info pre_isp_in_info, *pipe_out_info;
	पूर्णांक err = 0;
	काष्ठा ia_css_binary_descr pre_de_descr;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE ||
		pipe->mode == IA_CSS_PIPE_ID_COPY);
	pipe_out_info = &pipe->output_info[0];

	अगर (pipe->pipe_settings.capture.pre_isp_binary.info)
		वापस 0;

	err = ia_css_frame_check_info(pipe_out_info);
	अगर (err)
		वापस err;

	ia_css_pipe_get_pre_de_binarydesc(pipe, &pre_de_descr,
					    &pre_isp_in_info,
					    pipe_out_info);

	err = ia_css_binary_find(&pre_de_descr,
				    &pipe->pipe_settings.capture.pre_isp_binary);

	वापस err;
पूर्ण

अटल पूर्णांक load_low_light_binaries(
    काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_frame_info pre_in_info, anr_in_info,
			post_in_info, post_out_info,
			vf_info, *pipe_vf_out_info, *pipe_out_info,
			*vf_pp_in_info;
	bool need_pp;
	bool need_isp_copy = true;
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE ||
		pipe->mode == IA_CSS_PIPE_ID_COPY);

	अगर (pipe->pipe_settings.capture.pre_isp_binary.info)
		वापस 0;
	pipe_vf_out_info = &pipe->vf_output_info[0];
	pipe_out_info = &pipe->output_info[0];

	vf_info = *pipe_vf_out_info;
	err = ia_css_util_check_vf_out_info(pipe_out_info,
					    &vf_info);
	अगर (err)
		वापस err;
	need_pp = need_capture_pp(pipe);

	ia_css_frame_info_set_क्रमmat(&vf_info,
					IA_CSS_FRAME_FORMAT_YUV_LINE);

	/* we build up the pipeline starting at the end */
	/* Capture post-processing */
	अगर (need_pp) अणु
		काष्ठा ia_css_binary_descr capture_pp_descr;

		ia_css_pipe_get_capturepp_binarydesc(pipe,
							&capture_pp_descr, &post_out_info, pipe_out_info, &vf_info);
		err = ia_css_binary_find(&capture_pp_descr,
					    &pipe->pipe_settings.capture.capture_pp_binary);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		post_out_info = *pipe_out_info;
	पूर्ण

	/* Post-anr */
	अणु
		काष्ठा ia_css_binary_descr post_anr_descr;

		ia_css_pipe_get_post_anr_binarydesc(pipe,
						    &post_anr_descr, &post_in_info, &post_out_info, &vf_info);
		err = ia_css_binary_find(&post_anr_descr,
					    &pipe->pipe_settings.capture.post_isp_binary);
		अगर (err)
			वापस err;
	पूर्ण

	/* Anr */
	अणु
		काष्ठा ia_css_binary_descr anr_descr;

		ia_css_pipe_get_anr_binarydesc(pipe, &anr_descr, &anr_in_info,
						&pipe->pipe_settings.capture.post_isp_binary.in_frame_info);
		err = ia_css_binary_find(&anr_descr,
					    &pipe->pipe_settings.capture.anr_gdc_binary);
		अगर (err)
			वापस err;
	पूर्ण
	pipe->pipe_settings.capture.anr_gdc_binary.left_padding =
	    pipe->pipe_settings.capture.post_isp_binary.left_padding;

	/* Pre-anr */
	अणु
		काष्ठा ia_css_binary_descr pre_anr_descr;

		ia_css_pipe_get_pre_anr_binarydesc(pipe, &pre_anr_descr, &pre_in_info,
						    &pipe->pipe_settings.capture.anr_gdc_binary.in_frame_info);
		err = ia_css_binary_find(&pre_anr_descr,
					    &pipe->pipe_settings.capture.pre_isp_binary);
		अगर (err)
			वापस err;
	पूर्ण
	pipe->pipe_settings.capture.pre_isp_binary.left_padding =
	    pipe->pipe_settings.capture.anr_gdc_binary.left_padding;

	/* Viewfinder post-processing */
	अगर (need_pp) अणु
		vf_pp_in_info =
		    &pipe->pipe_settings.capture.capture_pp_binary.vf_frame_info;
	पूर्ण अन्यथा अणु
		vf_pp_in_info =
		    &pipe->pipe_settings.capture.post_isp_binary.vf_frame_info;
	पूर्ण

	अणु
		काष्ठा ia_css_binary_descr vf_pp_descr;

		ia_css_pipe_get_vfpp_binarydesc(pipe,
						&vf_pp_descr, vf_pp_in_info, pipe_vf_out_info);
		err = ia_css_binary_find(&vf_pp_descr,
					    &pipe->pipe_settings.capture.vf_pp_binary);
		अगर (err)
			वापस err;
	पूर्ण

	/* Copy */
#अगर_घोषित ISP2401
	/* For CSI2+, only the direct sensor mode/online requires ISP copy */
	need_isp_copy = pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR;
#पूर्ण_अगर
	अगर (need_isp_copy)
		err = load_copy_binary(pipe,
					&pipe->pipe_settings.capture.copy_binary,
					&pipe->pipe_settings.capture.pre_isp_binary);

	वापस err;
पूर्ण

अटल bool copy_on_sp(काष्ठा ia_css_pipe *pipe)
अणु
	bool rval;

	निश्चित(pipe);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "copy_on_sp() enter:\n");

	rval = true;

	rval &=	(pipe->mode == IA_CSS_PIPE_ID_CAPTURE);

	rval &= (pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_RAW);

	rval &= ((pipe->stream->config.input_config.क्रमmat ==
		    ATOMISP_INPUT_FORMAT_BINARY_8) ||
		    (pipe->config.mode == IA_CSS_PIPE_MODE_COPY));

	वापस rval;
पूर्ण

अटल पूर्णांक load_capture_binaries(
    काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;
	bool must_be_raw;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE ||
		pipe->mode == IA_CSS_PIPE_ID_COPY);

	अगर (pipe->pipe_settings.capture.primary_binary[0].info) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(0);
		वापस 0;
	पूर्ण

	/* in primary, advanced,low light or bayer,
						the input क्रमmat must be raw */
	must_be_raw =
	    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_ADVANCED ||
	    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_BAYER ||
	    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_LOW_LIGHT;
	err = ia_css_util_check_input(&pipe->stream->config, must_be_raw, false);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	अगर (copy_on_sp(pipe) &&
	    pipe->stream->config.input_config.क्रमmat == ATOMISP_INPUT_FORMAT_BINARY_8) अणु
		ia_css_frame_info_init(
		    &pipe->output_info[0],
		    JPEG_BYTES,
		    1,
		    IA_CSS_FRAME_FORMAT_BINARY_8,
		    0);
		IA_CSS_LEAVE_ERR_PRIVATE(0);
		वापस 0;
	पूर्ण

	चयन (pipe->config.शेष_capture_config.mode) अणु
	हाल IA_CSS_CAPTURE_MODE_RAW:
		err = load_copy_binaries(pipe);
#अगर defined(ISP2401)
		अगर (!err)
			pipe->pipe_settings.capture.copy_binary.online = pipe->stream->config.online;
#पूर्ण_अगर
		अवरोध;
	हाल IA_CSS_CAPTURE_MODE_BAYER:
		err = load_bayer_isp_binaries(pipe);
		अवरोध;
	हाल IA_CSS_CAPTURE_MODE_PRIMARY:
		err = load_primary_binaries(pipe);
		अवरोध;
	हाल IA_CSS_CAPTURE_MODE_ADVANCED:
		err = load_advanced_binaries(pipe);
		अवरोध;
	हाल IA_CSS_CAPTURE_MODE_LOW_LIGHT:
		err = load_low_light_binaries(pipe);
		अवरोध;
	पूर्ण
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल पूर्णांक
unload_capture_binaries(काष्ठा ia_css_pipe *pipe) अणु
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);

	अगर ((!pipe) || ((pipe->mode != IA_CSS_PIPE_ID_CAPTURE) && (pipe->mode != IA_CSS_PIPE_ID_COPY)))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	ia_css_binary_unload(&pipe->pipe_settings.capture.copy_binary);
	क्रम (i = 0; i < MAX_NUM_PRIMARY_STAGES; i++)
		ia_css_binary_unload(&pipe->pipe_settings.capture.primary_binary[i]);
	ia_css_binary_unload(&pipe->pipe_settings.capture.pre_isp_binary);
	ia_css_binary_unload(&pipe->pipe_settings.capture.anr_gdc_binary);
	ia_css_binary_unload(&pipe->pipe_settings.capture.post_isp_binary);
	ia_css_binary_unload(&pipe->pipe_settings.capture.capture_pp_binary);
	ia_css_binary_unload(&pipe->pipe_settings.capture.capture_ldc_binary);
	ia_css_binary_unload(&pipe->pipe_settings.capture.vf_pp_binary);

	क्रम (i = 0; i < pipe->pipe_settings.capture.num_yuv_scaler; i++)
		ia_css_binary_unload(&pipe->pipe_settings.capture.yuv_scaler_binary[i]);

	kमुक्त(pipe->pipe_settings.capture.is_output_stage);
	pipe->pipe_settings.capture.is_output_stage = शून्य;
	kमुक्त(pipe->pipe_settings.capture.yuv_scaler_binary);
	pipe->pipe_settings.capture.yuv_scaler_binary = शून्य;

	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

अटल bool
need_करोwnscaling(स्थिर काष्ठा ia_css_resolution in_res,
		    स्थिर काष्ठा ia_css_resolution out_res) अणु
	अगर (in_res.width > out_res.width || in_res.height > out_res.height)
		वापस true;

	वापस false;
पूर्ण

अटल bool
need_yuv_scaler_stage(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_resolution in_res, out_res;

	bool need_क्रमmat_conversion = false;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_YUVPP);

	/* TODO: make generic function */
	need_क्रमmat_conversion =
	    ((pipe->stream->config.input_config.क्रमmat ==
		ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY) &&
		(pipe->output_info[0].क्रमmat != IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8));

	in_res = pipe->config.input_effective_res;

	अगर (pipe->config.enable_dz)
		वापस true;

	अगर ((pipe->output_info[0].res.width != 0) && need_क्रमmat_conversion)
		वापस true;

	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
		out_res = pipe->output_info[i].res;

		/* A non-zero width means it is a valid output port */
		अगर ((out_res.width != 0) && need_करोwnscaling(in_res, out_res))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* TODO: it is temporarily created from ia_css_pipe_create_cas_scaler_desc */
/* which has some hard-coded knowledge which prevents reuse of the function. */
/* Later, merge this with ia_css_pipe_create_cas_scaler_desc */
अटल पूर्णांक ia_css_pipe_create_cas_scaler_desc_single_output(
    काष्ठा ia_css_frame_info *cas_scaler_in_info,
    काष्ठा ia_css_frame_info *cas_scaler_out_info,
    काष्ठा ia_css_frame_info *cas_scaler_vf_info,
    काष्ठा ia_css_cas_binary_descr *descr) अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक hor_ds_factor = 0, ver_ds_factor = 0;
	पूर्णांक err = 0;
	काष्ठा ia_css_frame_info पंचांगp_in_info;

	अचिन्हित पूर्णांक max_scale_factor_per_stage = MAX_PREFERRED_YUV_DS_PER_STEP;

	निश्चित(cas_scaler_in_info);
	निश्चित(cas_scaler_out_info);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_create_cas_scaler_desc() enter:\n");

	/* We assume that this function is used only क्रम single output port हाल. */
	descr->num_output_stage = 1;

	hor_ds_factor = CEIL_DIV(cas_scaler_in_info->res.width,
				    cas_scaler_out_info->res.width);
	ver_ds_factor = CEIL_DIV(cas_scaler_in_info->res.height,
				    cas_scaler_out_info->res.height);
	/* use the same horizontal and vertical करोwnscaling factor क्रम simplicity */
	निश्चित(hor_ds_factor == ver_ds_factor);

	i = 1;
	जबतक (i < hor_ds_factor) अणु
		descr->num_stage++;
		i *= max_scale_factor_per_stage;
	पूर्ण

	descr->in_info = kदो_स्मृति(descr->num_stage * माप(काष्ठा ia_css_frame_info),
				    GFP_KERNEL);
	अगर (!descr->in_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->पूर्णांकernal_out_info = kदो_स्मृति(descr->num_stage * माप(
						काष्ठा ia_css_frame_info), GFP_KERNEL);
	अगर (!descr->पूर्णांकernal_out_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->out_info = kदो_स्मृति(descr->num_stage * माप(काष्ठा ia_css_frame_info),
				    GFP_KERNEL);
	अगर (!descr->out_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->vf_info = kदो_स्मृति(descr->num_stage * माप(काष्ठा ia_css_frame_info),
				    GFP_KERNEL);
	अगर (!descr->vf_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->is_output_stage = kदो_स्मृति(descr->num_stage * माप(bool), GFP_KERNEL);
	अगर (!descr->is_output_stage) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण

	पंचांगp_in_info = *cas_scaler_in_info;
	क्रम (i = 0; i < descr->num_stage; i++) अणु
		descr->in_info[i] = पंचांगp_in_info;
		अगर ((पंचांगp_in_info.res.width / max_scale_factor_per_stage) <=
		    cas_scaler_out_info->res.width) अणु
			descr->is_output_stage[i] = true;
			अगर ((descr->num_output_stage > 1) && (i != (descr->num_stage - 1))) अणु
				descr->पूर्णांकernal_out_info[i].res.width = cas_scaler_out_info->res.width;
				descr->पूर्णांकernal_out_info[i].res.height = cas_scaler_out_info->res.height;
				descr->पूर्णांकernal_out_info[i].padded_width = cas_scaler_out_info->padded_width;
				descr->पूर्णांकernal_out_info[i].क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
			पूर्ण अन्यथा अणु
				निश्चित(i == (descr->num_stage - 1));
				descr->पूर्णांकernal_out_info[i].res.width = 0;
				descr->पूर्णांकernal_out_info[i].res.height = 0;
			पूर्ण
			descr->out_info[i].res.width = cas_scaler_out_info->res.width;
			descr->out_info[i].res.height = cas_scaler_out_info->res.height;
			descr->out_info[i].padded_width = cas_scaler_out_info->padded_width;
			descr->out_info[i].क्रमmat = cas_scaler_out_info->क्रमmat;
			अगर (cas_scaler_vf_info) अणु
				descr->vf_info[i].res.width = cas_scaler_vf_info->res.width;
				descr->vf_info[i].res.height = cas_scaler_vf_info->res.height;
				descr->vf_info[i].padded_width = cas_scaler_vf_info->padded_width;
				ia_css_frame_info_set_क्रमmat(&descr->vf_info[i], IA_CSS_FRAME_FORMAT_YUV_LINE);
			पूर्ण अन्यथा अणु
				descr->vf_info[i].res.width = 0;
				descr->vf_info[i].res.height = 0;
				descr->vf_info[i].padded_width = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			descr->is_output_stage[i] = false;
			descr->पूर्णांकernal_out_info[i].res.width = पंचांगp_in_info.res.width /
								max_scale_factor_per_stage;
			descr->पूर्णांकernal_out_info[i].res.height = पंचांगp_in_info.res.height /
				max_scale_factor_per_stage;
			descr->पूर्णांकernal_out_info[i].क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
			ia_css_frame_info_init(&descr->पूर्णांकernal_out_info[i],
						पंचांगp_in_info.res.width / max_scale_factor_per_stage,
						पंचांगp_in_info.res.height / max_scale_factor_per_stage,
						IA_CSS_FRAME_FORMAT_YUV420, 0);
			descr->out_info[i].res.width = 0;
			descr->out_info[i].res.height = 0;
			descr->vf_info[i].res.width = 0;
			descr->vf_info[i].res.height = 0;
		पूर्ण
		पंचांगp_in_info = descr->पूर्णांकernal_out_info[i];
	पूर्ण
ERR:
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_create_cas_scaler_desc() leave, err=%d\n",
			    err);
	वापस err;
पूर्ण

/* FIXME: merge most of this and single output version */
अटल पूर्णांक ia_css_pipe_create_cas_scaler_desc(
    काष्ठा ia_css_pipe *pipe,
    काष्ठा ia_css_cas_binary_descr *descr) अणु
	काष्ठा ia_css_frame_info in_info = IA_CSS_BINARY_DEFAULT_FRAME_INFO;
	काष्ठा ia_css_frame_info *out_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_frame_info *vf_out_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_frame_info पंचांगp_in_info = IA_CSS_BINARY_DEFAULT_FRAME_INFO;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित पूर्णांक hor_scale_factor[IA_CSS_PIPE_MAX_OUTPUT_STAGE],
		    ver_scale_factor[IA_CSS_PIPE_MAX_OUTPUT_STAGE],
		    scale_factor = 0;
	अचिन्हित पूर्णांक num_stages = 0;
	पूर्णांक err = 0;

	अचिन्हित पूर्णांक max_scale_factor_per_stage = MAX_PREFERRED_YUV_DS_PER_STEP;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_create_cas_scaler_desc() enter:\n");

	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
		out_info[i] = शून्य;
		vf_out_info[i] = शून्य;
		hor_scale_factor[i] = 0;
		ver_scale_factor[i] = 0;
	पूर्ण

	in_info.res = pipe->config.input_effective_res;
	in_info.padded_width = in_info.res.width;
	descr->num_output_stage = 0;
	/* Find out how much scaling we need क्रम each output */
	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
		अगर (pipe->output_info[i].res.width != 0) अणु
			out_info[i] = &pipe->output_info[i];
			अगर (pipe->vf_output_info[i].res.width != 0)
				vf_out_info[i] = &pipe->vf_output_info[i];
			descr->num_output_stage += 1;
		पूर्ण

		अगर (out_info[i]) अणु
			hor_scale_factor[i] = CEIL_DIV(in_info.res.width, out_info[i]->res.width);
			ver_scale_factor[i] = CEIL_DIV(in_info.res.height, out_info[i]->res.height);
			/* use the same horizontal and vertical scaling factor क्रम simplicity */
			निश्चित(hor_scale_factor[i] == ver_scale_factor[i]);
			scale_factor = 1;
			करो अणु
				num_stages++;
				scale_factor *= max_scale_factor_per_stage;
			पूर्ण जबतक (scale_factor < hor_scale_factor[i]);

			in_info.res = out_info[i]->res;
		पूर्ण
	पूर्ण

	अगर (need_yuv_scaler_stage(pipe) && (num_stages == 0))
		num_stages = 1;

	descr->num_stage = num_stages;

	descr->in_info = kदो_स्मृति_array(descr->num_stage,
					माप(काष्ठा ia_css_frame_info), GFP_KERNEL);
	अगर (!descr->in_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->पूर्णांकernal_out_info = kदो_स्मृति(descr->num_stage * माप(
						काष्ठा ia_css_frame_info), GFP_KERNEL);
	अगर (!descr->पूर्णांकernal_out_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->out_info = kदो_स्मृति(descr->num_stage * माप(काष्ठा ia_css_frame_info),
				    GFP_KERNEL);
	अगर (!descr->out_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->vf_info = kदो_स्मृति(descr->num_stage * माप(काष्ठा ia_css_frame_info),
				    GFP_KERNEL);
	अगर (!descr->vf_info) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण
	descr->is_output_stage = kदो_स्मृति(descr->num_stage * माप(bool), GFP_KERNEL);
	अगर (!descr->is_output_stage) अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण

	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
		अगर (out_info[i]) अणु
			अगर (i > 0) अणु
				निश्चित((out_info[i - 1]->res.width >= out_info[i]->res.width) &&
					(out_info[i - 1]->res.height >= out_info[i]->res.height));
			पूर्ण
		पूर्ण
	पूर्ण

	पंचांगp_in_info.res = pipe->config.input_effective_res;
	पंचांगp_in_info.क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
	क्रम (i = 0, j = 0; i < descr->num_stage; i++) अणु
		निश्चित(j < 2);
		निश्चित(out_info[j]);

		descr->in_info[i] = पंचांगp_in_info;
		अगर ((पंचांगp_in_info.res.width / max_scale_factor_per_stage) <=
		    out_info[j]->res.width) अणु
			descr->is_output_stage[i] = true;
			अगर ((descr->num_output_stage > 1) && (i != (descr->num_stage - 1))) अणु
				descr->पूर्णांकernal_out_info[i].res.width = out_info[j]->res.width;
				descr->पूर्णांकernal_out_info[i].res.height = out_info[j]->res.height;
				descr->पूर्णांकernal_out_info[i].padded_width = out_info[j]->padded_width;
				descr->पूर्णांकernal_out_info[i].क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
			पूर्ण अन्यथा अणु
				निश्चित(i == (descr->num_stage - 1));
				descr->पूर्णांकernal_out_info[i].res.width = 0;
				descr->पूर्णांकernal_out_info[i].res.height = 0;
			पूर्ण
			descr->out_info[i].res.width = out_info[j]->res.width;
			descr->out_info[i].res.height = out_info[j]->res.height;
			descr->out_info[i].padded_width = out_info[j]->padded_width;
			descr->out_info[i].क्रमmat = out_info[j]->क्रमmat;
			अगर (vf_out_info[j]) अणु
				descr->vf_info[i].res.width = vf_out_info[j]->res.width;
				descr->vf_info[i].res.height = vf_out_info[j]->res.height;
				descr->vf_info[i].padded_width = vf_out_info[j]->padded_width;
				ia_css_frame_info_set_क्रमmat(&descr->vf_info[i], IA_CSS_FRAME_FORMAT_YUV_LINE);
			पूर्ण अन्यथा अणु
				descr->vf_info[i].res.width = 0;
				descr->vf_info[i].res.height = 0;
				descr->vf_info[i].padded_width = 0;
			पूर्ण
			j++;
		पूर्ण अन्यथा अणु
			descr->is_output_stage[i] = false;
			descr->पूर्णांकernal_out_info[i].res.width = पंचांगp_in_info.res.width /
								max_scale_factor_per_stage;
			descr->पूर्णांकernal_out_info[i].res.height = पंचांगp_in_info.res.height /
				max_scale_factor_per_stage;
			descr->पूर्णांकernal_out_info[i].क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
			ia_css_frame_info_init(&descr->पूर्णांकernal_out_info[i],
						पंचांगp_in_info.res.width / max_scale_factor_per_stage,
						पंचांगp_in_info.res.height / max_scale_factor_per_stage,
						IA_CSS_FRAME_FORMAT_YUV420, 0);
			descr->out_info[i].res.width = 0;
			descr->out_info[i].res.height = 0;
			descr->vf_info[i].res.width = 0;
			descr->vf_info[i].res.height = 0;
		पूर्ण
		पंचांगp_in_info = descr->पूर्णांकernal_out_info[i];
	पूर्ण
ERR:
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_create_cas_scaler_desc() leave, err=%d\n",
			    err);
	वापस err;
पूर्ण

अटल व्योम ia_css_pipe_destroy_cas_scaler_desc(काष्ठा ia_css_cas_binary_descr
	*descr) अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_destroy_cas_scaler_desc() enter:\n");
	kमुक्त(descr->in_info);
	descr->in_info = शून्य;
	kमुक्त(descr->पूर्णांकernal_out_info);
	descr->पूर्णांकernal_out_info = शून्य;
	kमुक्त(descr->out_info);
	descr->out_info = शून्य;
	kमुक्त(descr->vf_info);
	descr->vf_info = शून्य;
	kमुक्त(descr->is_output_stage);
	descr->is_output_stage = शून्य;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_pipe_destroy_cas_scaler_desc() leave\n");
पूर्ण

अटल पूर्णांक
load_yuvpp_binaries(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;
	bool need_scaler = false;
	काष्ठा ia_css_frame_info *vf_pp_in_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_yuvpp_settings *mycs;
	काष्ठा ia_css_binary *next_binary;
	काष्ठा ia_css_cas_binary_descr cas_scaler_descr = अणु पूर्ण;
	अचिन्हित पूर्णांक i, j;
	bool need_isp_copy_binary = false;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->stream);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_YUVPP);

	अगर (pipe->pipe_settings.yuvpp.copy_binary.info)
		जाओ ERR;

	/* Set both must_be_raw and must_be_yuv to false then yuvpp can take rgb inमाला_दो */
	err = ia_css_util_check_input(&pipe->stream->config, false, false);
	अगर (err)
		जाओ ERR;

	mycs = &pipe->pipe_settings.yuvpp;

	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++)
	अणु
		अगर (pipe->vf_output_info[i].res.width != 0) अणु
			err = ia_css_util_check_vf_out_info(&pipe->output_info[i],
							    &pipe->vf_output_info[i]);
			अगर (err)
				जाओ ERR;
		पूर्ण
		vf_pp_in_info[i] = शून्य;
	पूर्ण

	need_scaler = need_yuv_scaler_stage(pipe);

	/* we build up the pipeline starting at the end */
	/* Capture post-processing */
	अगर (need_scaler)
	अणु
		काष्ठा ia_css_binary_descr yuv_scaler_descr;

		err = ia_css_pipe_create_cas_scaler_desc(pipe,
			&cas_scaler_descr);
		अगर (err)
			जाओ ERR;
		mycs->num_output = cas_scaler_descr.num_output_stage;
		mycs->num_yuv_scaler = cas_scaler_descr.num_stage;
		mycs->yuv_scaler_binary = kzalloc(cas_scaler_descr.num_stage *
						    माप(काष्ठा ia_css_binary), GFP_KERNEL);
		अगर (!mycs->yuv_scaler_binary) अणु
			err = -ENOMEM;
			जाओ ERR;
		पूर्ण
		mycs->is_output_stage = kzalloc(cas_scaler_descr.num_stage *
						माप(bool), GFP_KERNEL);
		अगर (!mycs->is_output_stage) अणु
			err = -ENOMEM;
			जाओ ERR;
		पूर्ण
		क्रम (i = 0; i < cas_scaler_descr.num_stage; i++) अणु
			mycs->is_output_stage[i] = cas_scaler_descr.is_output_stage[i];
			ia_css_pipe_get_yuvscaler_binarydesc(pipe,
								&yuv_scaler_descr, &cas_scaler_descr.in_info[i],
								&cas_scaler_descr.out_info[i],
								&cas_scaler_descr.पूर्णांकernal_out_info[i],
								&cas_scaler_descr.vf_info[i]);
			err = ia_css_binary_find(&yuv_scaler_descr,
						    &mycs->yuv_scaler_binary[i]);
			अगर (err)
				जाओ ERR;
		पूर्ण
		ia_css_pipe_destroy_cas_scaler_desc(&cas_scaler_descr);
	पूर्ण अन्यथा
	अणु
		mycs->num_output = 1;
	पूर्ण

	अगर (need_scaler)
	अणु
		next_binary = &mycs->yuv_scaler_binary[0];
	पूर्ण अन्यथा
	अणु
		next_binary = शून्य;
	पूर्ण

#अगर defined(ISP2401)
	/*
	    * NOTES
	    * - Why करोes the "yuvpp" pipe needs "isp_copy_binary" (i.e. ISP Copy) when
	    *   its input is "ATOMISP_INPUT_FORMAT_YUV422_8"?
	    *
	    *   In most use हालs, the first stage in the "yuvpp" pipe is the "yuv_scale_
	    *   binary". However, the "yuv_scale_binary" करोes NOT support the input-frame
	    *   क्रमmat as "IA_CSS_STREAM _FORMAT_YUV422_8".
	    *
	    *   Hence, the "isp_copy_binary" is required to be present in front of the "yuv
	    *   _scale_binary". It would translate the input-frame to the frame क्रमmats that
	    *   are supported by the "yuv_scale_binary".
	    *
	    *   Please refer to "FrameWork/css/isp/pipes/capture_pp/capture_pp_1.0/capture_
	    *   pp_defs.h" क्रम the list of input-frame क्रमmats that are supported by the
	    *   "yuv_scale_binary".
	    */
	need_isp_copy_binary =
	    (pipe->stream->config.input_config.क्रमmat == ATOMISP_INPUT_FORMAT_YUV422_8);
#अन्यथा  /* !ISP2401 */
	need_isp_copy_binary = true;
#पूर्ण_अगर /*  ISP2401 */

	अगर (need_isp_copy_binary)
	अणु
		err = load_copy_binary(pipe,
					&mycs->copy_binary,
					next_binary);

		अगर (err)
			जाओ ERR;

		/*
		    * NOTES
		    * - Why is "pipe->pipe_settings.capture.copy_binary.online" specअगरied?
		    *
		    *   In some use हालs, the first stage in the "yuvpp" pipe is the
		    *   "isp_copy_binary". The "isp_copy_binary" is deचिन्हित to process
		    *   the input from either the प्रणाली DDR or from the IPU पूर्णांकernal VMEM.
		    *   So it provides the flag "online" to specअगरy where its input is from,
		    *   i.e.:
		    *
		    *      (1) "online <= true", the input is from the IPU पूर्णांकernal VMEM.
		    *      (2) "online <= false", the input is from the प्रणाली DDR.
		    *
		    *   In other use हालs, the first stage in the "yuvpp" pipe is the
		    *   "yuv_scale_binary". "The "yuv_scale_binary" is deचिन्हित to process the
		    *   input ONLY from the प्रणाली DDR. So it करोes not provide the flag "online"
		    *   to specअगरy where its input is from.
		    */
		pipe->pipe_settings.capture.copy_binary.online = pipe->stream->config.online;
	पूर्ण

	/* Viewfinder post-processing */
	अगर (need_scaler)
	अणु
		क्रम (i = 0, j = 0; i < mycs->num_yuv_scaler; i++) अणु
			अगर (mycs->is_output_stage[i]) अणु
				निश्चित(j < 2);
				vf_pp_in_info[j] =
				    &mycs->yuv_scaler_binary[i].vf_frame_info;
				j++;
			पूर्ण
		पूर्ण
		mycs->num_vf_pp = j;
	पूर्ण अन्यथा
	अणु
		vf_pp_in_info[0] =
		    &mycs->copy_binary.vf_frame_info;
		क्रम (i = 1; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++) अणु
			vf_pp_in_info[i] = शून्य;
		पूर्ण
		mycs->num_vf_pp = 1;
	पूर्ण
	mycs->vf_pp_binary = kzalloc(mycs->num_vf_pp * माप(काष्ठा ia_css_binary),
					GFP_KERNEL);
	अगर (!mycs->vf_pp_binary)
	अणु
		err = -ENOMEM;
		जाओ ERR;
	पूर्ण

	अणु
		काष्ठा ia_css_binary_descr vf_pp_descr;

		क्रम (i = 0; i < mycs->num_vf_pp; i++)
		अणु
			अगर (pipe->vf_output_info[i].res.width != 0) अणु
				ia_css_pipe_get_vfpp_binarydesc(pipe,
								&vf_pp_descr, vf_pp_in_info[i], &pipe->vf_output_info[i]);
				err = ia_css_binary_find(&vf_pp_descr, &mycs->vf_pp_binary[i]);
				अगर (err)
					जाओ ERR;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (err)
		जाओ ERR;

ERR:
	अगर (need_scaler)
	अणु
		ia_css_pipe_destroy_cas_scaler_desc(&cas_scaler_descr);
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "load_yuvpp_binaries() leave, err=%d\n",
			    err);
	वापस err;
पूर्ण

अटल पूर्णांक
unload_yuvpp_binaries(काष्ठा ia_css_pipe *pipe) अणु
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);

	अगर ((!pipe) || (pipe->mode != IA_CSS_PIPE_ID_YUVPP))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	ia_css_binary_unload(&pipe->pipe_settings.yuvpp.copy_binary);
	क्रम (i = 0; i < pipe->pipe_settings.yuvpp.num_yuv_scaler; i++)
	अणु
		ia_css_binary_unload(&pipe->pipe_settings.yuvpp.yuv_scaler_binary[i]);
	पूर्ण
	क्रम (i = 0; i < pipe->pipe_settings.yuvpp.num_vf_pp; i++)
	अणु
		ia_css_binary_unload(&pipe->pipe_settings.yuvpp.vf_pp_binary[i]);
	पूर्ण
	kमुक्त(pipe->pipe_settings.yuvpp.is_output_stage);
	pipe->pipe_settings.yuvpp.is_output_stage = शून्य;
	kमुक्त(pipe->pipe_settings.yuvpp.yuv_scaler_binary);
	pipe->pipe_settings.yuvpp.yuv_scaler_binary = शून्य;
	kमुक्त(pipe->pipe_settings.yuvpp.vf_pp_binary);
	pipe->pipe_settings.yuvpp.vf_pp_binary = शून्य;

	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

अटल पूर्णांक yuvpp_start(काष्ठा ia_css_pipe *pipe)
अणु
	पूर्णांक err = 0;
	क्रमागत sh_css_pipe_config_override copy_ovrd;
	क्रमागत ia_css_input_mode yuvpp_pipe_input_mode;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (pipe->mode != IA_CSS_PIPE_ID_YUVPP)) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	yuvpp_pipe_input_mode = pipe->stream->config.mode;

	sh_css_metrics_start_frame();

	/* multi stream video needs mipi buffers */

	err = send_mipi_frames(pipe);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	अणु
		अचिन्हित पूर्णांक thपढ़ो_id;

		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		copy_ovrd = 1 << thपढ़ो_id;
	पूर्ण

	start_pipe(pipe, copy_ovrd, yuvpp_pipe_input_mode);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल पूर्णांक
sh_css_pipe_unload_binaries(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);

	अगर (!pipe)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	/* PIPE_MODE_COPY has no binaries, but has output frames to outside*/
	अगर (pipe->config.mode == IA_CSS_PIPE_MODE_COPY)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(0);
		वापस 0;
	पूर्ण

	चयन (pipe->mode)
	अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		err = unload_preview_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_VIDEO:
		err = unload_video_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_CAPTURE:
		err = unload_capture_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_YUVPP:
		err = unload_yuvpp_binaries(pipe);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल पूर्णांक
sh_css_pipe_load_binaries(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;

	निश्चित(pipe);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "sh_css_pipe_load_binaries() enter:\n");

	/* PIPE_MODE_COPY has no binaries, but has output frames to outside*/
	अगर (pipe->config.mode == IA_CSS_PIPE_MODE_COPY)
		वापस err;

	चयन (pipe->mode)
	अणु
	हाल IA_CSS_PIPE_ID_PREVIEW:
		err = load_preview_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_VIDEO:
		err = load_video_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_CAPTURE:
		err = load_capture_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_YUVPP:
		err = load_yuvpp_binaries(pipe);
		अवरोध;
	हाल IA_CSS_PIPE_ID_ACC:
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (err)
	अणु
		अगर (sh_css_pipe_unload_binaries(pipe)) अणु
			/* currently css करोes not support multiple error वापसs in a single function,
			    * using -EINVAL in this हाल */
			err = -EINVAL;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
create_host_yuvpp_pipeline(काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_pipeline *me;
	पूर्णांक err = 0;
	काष्ठा ia_css_pipeline_stage *vf_pp_stage = शून्य,
		*copy_stage = शून्य,
		*yuv_scaler_stage = शून्य;
	काष्ठा ia_css_binary *copy_binary,
		*vf_pp_binary,
		*yuv_scaler_binary;
	bool need_scaler = false;
	अचिन्हित पूर्णांक num_stage, num_output_stage;
	अचिन्हित पूर्णांक i, j;

	काष्ठा ia_css_frame *in_frame = शून्य;
	काष्ठा ia_css_frame *out_frame[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_frame *bin_out_frame[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_frame *vf_frame[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_pipeline_stage_desc stage_desc;
	bool need_in_frameinfo_memory = false;
#अगर_घोषित ISP2401
	bool sensor = false;
	bool buffered_sensor = false;
	bool online = false;
	bool continuous = false;
#पूर्ण_अगर

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर ((!pipe) || (!pipe->stream) || (pipe->mode != IA_CSS_PIPE_ID_YUVPP))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	me = &pipe->pipeline;
	ia_css_pipeline_clean(me);
	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++)
	अणु
		out_frame[i] = शून्य;
		vf_frame[i] = शून्य;
	पूर्ण
	ia_css_pipe_util_create_output_frames(bin_out_frame);
	num_stage  = pipe->pipe_settings.yuvpp.num_yuv_scaler;
	num_output_stage   = pipe->pipe_settings.yuvpp.num_output;

#अगर_घोषित ISP2401
	/* When the input प्रणाली is 2401, always enable 'in_frameinfo_memory'
	    * except क्रम the following:
	    * - Direct Sensor Mode Online Capture
	    * - Direct Sensor Mode Continuous Capture
	    * - Buffered Sensor Mode Continuous Capture
	    */
	sensor = pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR;
	buffered_sensor = pipe->stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR;
	online = pipe->stream->config.online;
	continuous = pipe->stream->config.continuous;
	need_in_frameinfo_memory =
	!((sensor && (online || continuous)) || (buffered_sensor && continuous));
#अन्यथा
	/* Conकाष्ठा in_frame info (only in हाल we have dynamic input */
	need_in_frameinfo_memory = pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY;
#पूर्ण_अगर
	/* the input frame can come from:
	    *  a) memory: connect yuvscaler to me->in_frame
	    *  b) sensor, via copy binary: connect yuvscaler to copy binary later on */
	अगर (need_in_frameinfo_memory)
	अणु
		/* TODO: improve क्रम dअगरferent input क्रमmats. */

		/*
		    * "pipe->stream->config.input_config.format" represents the sensor output
		    * frame क्रमmat, e.g. YUV422 8-bit.
		    *
		    * "in_frame_format" represents the imaging pipe's input frame क्रमmat, e.g.
		    * Bayer-Quad RAW.
		    */
		पूर्णांक in_frame_क्रमmat;

		अगर (pipe->stream->config.input_config.क्रमmat ==
		    ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY) अणु
			in_frame_क्रमmat = IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8;
		पूर्ण अन्यथा अगर (pipe->stream->config.input_config.क्रमmat ==
			    ATOMISP_INPUT_FORMAT_YUV422_8) अणु
			/*
			    * When the sensor output frame क्रमmat is "ATOMISP_INPUT_FORMAT_YUV422_8",
			    * the "isp_copy_var" binary is selected as the first stage in the yuvpp
			    * pipe.
			    *
			    * For the "isp_copy_var" binary, it पढ़ोs the YUV422-8 pixels from
			    * the frame buffer (at DDR) to the frame-line buffer (at VMEM).
			    *
			    * By now, the "isp_copy_var" binary करोes NOT provide a separated
			    * frame-line buffer to store the YUV422-8 pixels. Instead, it stores
			    * the YUV422-8 pixels in the frame-line buffer which is deचिन्हित to
			    * store the Bayer-Quad RAW pixels.
			    *
			    * To direct the "isp_copy_var" binary पढ़ोing from the RAW frame-line
			    * buffer, its input frame क्रमmat must be specअगरied as "IA_CSS_FRAME_
			    * FORMAT_RAW".
			    */
			in_frame_क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
		पूर्ण अन्यथा अणु
			in_frame_क्रमmat = IA_CSS_FRAME_FORMAT_NV12;
		पूर्ण

		err = init_in_frameinfo_memory_शेषs(pipe,
							&me->in_frame,
							in_frame_क्रमmat);

		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण

		in_frame = &me->in_frame;
	पूर्ण अन्यथा
	अणु
		in_frame = शून्य;
	पूर्ण

	क्रम (i = 0; i < num_output_stage; i++)
	अणु
		निश्चित(i < IA_CSS_PIPE_MAX_OUTPUT_STAGE);
		अगर (pipe->output_info[i].res.width != 0) अणु
			err = init_out_frameinfo_शेषs(pipe, &me->out_frame[i], i);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
			out_frame[i] = &me->out_frame[i];
		पूर्ण

		/* Conकाष्ठा vf_frame info (only in हाल we have VF) */
		अगर (pipe->vf_output_info[i].res.width != 0) अणु
			err = init_vf_frameinfo_शेषs(pipe, &me->vf_frame[i], i);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
			vf_frame[i] = &me->vf_frame[i];
		पूर्ण
	पूर्ण

	copy_binary       = &pipe->pipe_settings.yuvpp.copy_binary;
	vf_pp_binary      = pipe->pipe_settings.yuvpp.vf_pp_binary;
	yuv_scaler_binary = pipe->pipe_settings.yuvpp.yuv_scaler_binary;
	need_scaler = need_yuv_scaler_stage(pipe);

	अगर (pipe->pipe_settings.yuvpp.copy_binary.info)
	अणु
		काष्ठा ia_css_frame *in_frame_local = शून्य;

#अगर_घोषित ISP2401
		/* After isp copy is enabled in_frame needs to be passed. */
		अगर (!online)
			in_frame_local = in_frame;
#पूर्ण_अगर

		अगर (need_scaler) अणु
			ia_css_pipe_util_set_output_frames(bin_out_frame, 0, शून्य);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
							    bin_out_frame, in_frame_local, शून्य);
		पूर्ण अन्यथा अणु
			ia_css_pipe_util_set_output_frames(bin_out_frame, 0, out_frame[0]);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
							    bin_out_frame, in_frame_local, शून्य);
		पूर्ण

		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			&copy_stage);

		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण

		अगर (copy_stage) अणु
			/* अगर we use yuv scaler binary, vf output should be from there */
			copy_stage->args.copy_vf = !need_scaler;
			/* क्रम yuvpp pipe, it should always be enabled */
			copy_stage->args.copy_output = true;
			/* connect output of copy binary to input of yuv scaler */
			in_frame = copy_stage->args.out_frame[0];
		पूर्ण
	पूर्ण

	अगर (need_scaler)
	अणु
		काष्ठा ia_css_frame *पंचांगp_out_frame = शून्य;
		काष्ठा ia_css_frame *पंचांगp_vf_frame = शून्य;
		काष्ठा ia_css_frame *पंचांगp_in_frame = in_frame;

		क्रम (i = 0, j = 0; i < num_stage; i++) अणु
			निश्चित(j < num_output_stage);
			अगर (pipe->pipe_settings.yuvpp.is_output_stage[i]) अणु
				पंचांगp_out_frame = out_frame[j];
				पंचांगp_vf_frame = vf_frame[j];
			पूर्ण अन्यथा अणु
				पंचांगp_out_frame = शून्य;
				पंचांगp_vf_frame = शून्य;
			पूर्ण

			err = add_yuv_scaler_stage(pipe, me, पंचांगp_in_frame, पंचांगp_out_frame,
						    शून्य,
						    &yuv_scaler_binary[i],
						    &yuv_scaler_stage);

			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
			/* we use output port 1 as पूर्णांकernal output port */
			पंचांगp_in_frame = yuv_scaler_stage->args.out_frame[1];
			अगर (pipe->pipe_settings.yuvpp.is_output_stage[i]) अणु
				अगर (पंचांगp_vf_frame && (पंचांगp_vf_frame->info.res.width != 0)) अणु
					in_frame = yuv_scaler_stage->args.out_vf_frame;
					err = add_vf_pp_stage(pipe, in_frame, पंचांगp_vf_frame, &vf_pp_binary[j],
								&vf_pp_stage);

					अगर (err) अणु
						IA_CSS_LEAVE_ERR_PRIVATE(err);
						वापस err;
					पूर्ण
				पूर्ण
				j++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (copy_stage)
	अणु
		अगर (vf_frame[0] && vf_frame[0]->info.res.width != 0) अणु
			in_frame = copy_stage->args.out_vf_frame;
			err = add_vf_pp_stage(pipe, in_frame, vf_frame[0], &vf_pp_binary[0],
						&vf_pp_stage);
		पूर्ण
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

	ia_css_pipeline_finalize_stages(&pipe->pipeline, pipe->stream->config.continuous);

	IA_CSS_LEAVE_ERR_PRIVATE(0);

	वापस 0;
पूर्ण

अटल पूर्णांक
create_host_copy_pipeline(काष्ठा ia_css_pipe *pipe,
			    अचिन्हित पूर्णांक max_input_width,
			    काष्ठा ia_css_frame *out_frame) अणु
	काष्ठा ia_css_pipeline *me;
	पूर्णांक err = 0;
	काष्ठा ia_css_pipeline_stage_desc stage_desc;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "create_host_copy_pipeline() enter:\n");

	/* pipeline alपढ़ोy created as part of create_host_pipeline_काष्ठाure */
	me = &pipe->pipeline;
	ia_css_pipeline_clean(me);

	/* Conकाष्ठा out_frame info */
	out_frame->contiguous = false;
	out_frame->flash_state = IA_CSS_FRAME_FLASH_STATE_NONE;

	अगर (copy_on_sp(pipe) &&
	    pipe->stream->config.input_config.क्रमmat == ATOMISP_INPUT_FORMAT_BINARY_8)
	अणु
		ia_css_frame_info_init(
		    &out_frame->info,
		    JPEG_BYTES,
		    1,
		    IA_CSS_FRAME_FORMAT_BINARY_8,
		    0);
	पूर्ण अन्यथा अगर (out_frame->info.क्रमmat == IA_CSS_FRAME_FORMAT_RAW)
	अणु
		out_frame->info.raw_bit_depth =
		ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	पूर्ण

	me->num_stages = 1;
	me->pipe_id = IA_CSS_PIPE_ID_COPY;
	pipe->mode  = IA_CSS_PIPE_ID_COPY;

	ia_css_pipe_get_sp_func_stage_desc(&stage_desc, out_frame,
					    IA_CSS_PIPELINE_RAW_COPY, max_input_width);
	err = ia_css_pipeline_create_and_add_stage(me,
		&stage_desc,
		शून्य);

	ia_css_pipeline_finalize_stages(&pipe->pipeline, pipe->stream->config.continuous);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "create_host_copy_pipeline() leave:\n");

	वापस err;
पूर्ण

अटल पूर्णांक
create_host_isyscopy_capture_pipeline(काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_pipeline *me = &pipe->pipeline;
	पूर्णांक err = 0;
	काष्ठा ia_css_pipeline_stage_desc stage_desc;
	काष्ठा ia_css_frame *out_frame = &me->out_frame[0];
	काष्ठा ia_css_pipeline_stage *out_stage = शून्य;
	अचिन्हित पूर्णांक thपढ़ो_id;
	क्रमागत sh_css_queue_id queue_id;
	अचिन्हित पूर्णांक max_input_width = MAX_VECTORS_PER_INPUT_LINE_CONT * ISP_VEC_NELEMS;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "create_host_isyscopy_capture_pipeline() enter:\n");
	ia_css_pipeline_clean(me);

	/* Conकाष्ठा out_frame info */
	err = sh_css_pipe_get_output_frame_info(pipe, &out_frame->info, 0);
	अगर (err)
		वापस err;
	out_frame->contiguous = false;
	out_frame->flash_state = IA_CSS_FRAME_FLASH_STATE_NONE;
	ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
	ia_css_query_पूर्णांकernal_queue_id(IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, thपढ़ो_id, &queue_id);
	out_frame->dynamic_queue_id = queue_id;
	out_frame->buf_type = IA_CSS_BUFFER_TYPE_OUTPUT_FRAME;

	me->num_stages = 1;
	me->pipe_id = IA_CSS_PIPE_ID_CAPTURE;
	pipe->mode  = IA_CSS_PIPE_ID_CAPTURE;
	ia_css_pipe_get_sp_func_stage_desc(&stage_desc, out_frame,
					    IA_CSS_PIPELINE_ISYS_COPY, max_input_width);
	err = ia_css_pipeline_create_and_add_stage(me,
		&stage_desc, &out_stage);
	अगर (err)
		वापस err;

	ia_css_pipeline_finalize_stages(me, pipe->stream->config.continuous);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "create_host_isyscopy_capture_pipeline() leave:\n");

	वापस err;
पूर्ण

अटल पूर्णांक
create_host_regular_capture_pipeline(काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_pipeline *me;
	पूर्णांक err = 0;
	क्रमागत ia_css_capture_mode mode;
	काष्ठा ia_css_pipeline_stage *current_stage = शून्य;
	काष्ठा ia_css_pipeline_stage *yuv_scaler_stage = शून्य;
	काष्ठा ia_css_binary *copy_binary,
		*primary_binary[MAX_NUM_PRIMARY_STAGES],
		*vf_pp_binary,
		*pre_isp_binary,
		*anr_gdc_binary,
		*post_isp_binary,
		*yuv_scaler_binary,
		*capture_pp_binary,
		*capture_ldc_binary;
	bool need_pp = false;
	bool raw;

	काष्ठा ia_css_frame *in_frame;
	काष्ठा ia_css_frame *out_frame;
	काष्ठा ia_css_frame *out_frames[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_frame *vf_frame;
	काष्ठा ia_css_pipeline_stage_desc stage_desc;
	bool need_in_frameinfo_memory = false;
#अगर_घोषित ISP2401
	bool sensor = false;
	bool buffered_sensor = false;
	bool online = false;
	bool continuous = false;
#पूर्ण_अगर
	अचिन्हित पूर्णांक i, num_yuv_scaler, num_primary_stage;
	bool need_yuv_pp = false;
	bool *is_output_stage = शून्य;
	bool need_ldc = false;

	IA_CSS_ENTER_PRIVATE("");
	निश्चित(pipe);
	निश्चित(pipe->stream);
	निश्चित(pipe->mode == IA_CSS_PIPE_ID_CAPTURE || pipe->mode == IA_CSS_PIPE_ID_COPY);

	me = &pipe->pipeline;
	mode = pipe->config.शेष_capture_config.mode;
	raw = (mode == IA_CSS_CAPTURE_MODE_RAW);
	ia_css_pipeline_clean(me);
	ia_css_pipe_util_create_output_frames(out_frames);

#अगर_घोषित ISP2401
	/* When the input प्रणाली is 2401, always enable 'in_frameinfo_memory'
	    * except क्रम the following:
	    * - Direct Sensor Mode Online Capture
	    * - Direct Sensor Mode Online Capture
	    * - Direct Sensor Mode Continuous Capture
	    * - Buffered Sensor Mode Continuous Capture
	    */
	sensor = (pipe->stream->config.mode == IA_CSS_INPUT_MODE_SENSOR);
	buffered_sensor = (pipe->stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR);
	online = pipe->stream->config.online;
	continuous = pipe->stream->config.continuous;
	need_in_frameinfo_memory =
	!((sensor && (online || continuous)) || (buffered_sensor && (online || continuous)));
#अन्यथा
	/* Conकाष्ठा in_frame info (only in हाल we have dynamic input */
	need_in_frameinfo_memory = pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY;
#पूर्ण_अगर
	अगर (need_in_frameinfo_memory)
	अणु
		err = init_in_frameinfo_memory_शेषs(pipe, &me->in_frame,
							IA_CSS_FRAME_FORMAT_RAW);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण

		in_frame = &me->in_frame;
	पूर्ण अन्यथा
	अणु
		in_frame = शून्य;
	पूर्ण

	err = init_out_frameinfo_शेषs(pipe, &me->out_frame[0], 0);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	out_frame = &me->out_frame[0];

	/* Conकाष्ठा vf_frame info (only in हाल we have VF) */
	अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0])
	अणु
		अगर (mode == IA_CSS_CAPTURE_MODE_RAW || mode == IA_CSS_CAPTURE_MODE_BAYER) अणु
			/* These modes करोn't support viewfinder output */
			vf_frame = शून्य;
		पूर्ण अन्यथा अणु
			init_vf_frameinfo_शेषs(pipe, &me->vf_frame[0], 0);
			vf_frame = &me->vf_frame[0];
		पूर्ण
	पूर्ण अन्यथा
	अणु
		vf_frame = शून्य;
	पूर्ण

	copy_binary       = &pipe->pipe_settings.capture.copy_binary;
	num_primary_stage = pipe->pipe_settings.capture.num_primary_stage;
	अगर ((num_primary_stage == 0) && (mode == IA_CSS_CAPTURE_MODE_PRIMARY))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < num_primary_stage; i++)
	अणु
		primary_binary[i] = &pipe->pipe_settings.capture.primary_binary[i];
	पूर्ण
	vf_pp_binary      = &pipe->pipe_settings.capture.vf_pp_binary;
	pre_isp_binary    = &pipe->pipe_settings.capture.pre_isp_binary;
	anr_gdc_binary    = &pipe->pipe_settings.capture.anr_gdc_binary;
	post_isp_binary   = &pipe->pipe_settings.capture.post_isp_binary;
	capture_pp_binary = &pipe->pipe_settings.capture.capture_pp_binary;
	yuv_scaler_binary = pipe->pipe_settings.capture.yuv_scaler_binary;
	num_yuv_scaler	  = pipe->pipe_settings.capture.num_yuv_scaler;
	is_output_stage   = pipe->pipe_settings.capture.is_output_stage;
	capture_ldc_binary = &pipe->pipe_settings.capture.capture_ldc_binary;

	need_pp = (need_capture_pp(pipe) || pipe->output_stage) &&
		    mode != IA_CSS_CAPTURE_MODE_RAW &&
		    mode != IA_CSS_CAPTURE_MODE_BAYER;
	need_yuv_pp = (yuv_scaler_binary && yuv_scaler_binary->info);
	need_ldc = (capture_ldc_binary && capture_ldc_binary->info);

	अगर (pipe->pipe_settings.capture.copy_binary.info)
	अणु
		अगर (raw) अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
#अगर defined(ISP2401)
			अगर (!continuous) अणु
				ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
								    out_frames, in_frame, शून्य);
			पूर्ण अन्यथा अणु
				in_frame = pipe->stream->last_pipe->continuous_frames[0];
				ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
								    out_frames, in_frame, शून्य);
			पूर्ण
#अन्यथा
			ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
							    out_frames, शून्य, शून्य);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, in_frame);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, copy_binary,
							    out_frames, शून्य, शून्य);
		पूर्ण

		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			&current_stage);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (pipe->stream->config.continuous)
	अणु
		in_frame = pipe->stream->last_pipe->continuous_frames[0];
	पूर्ण

	अगर (mode == IA_CSS_CAPTURE_MODE_PRIMARY)
	अणु
		काष्ठा ia_css_frame *local_in_frame = शून्य;
		काष्ठा ia_css_frame *local_out_frame = शून्य;

		क्रम (i = 0; i < num_primary_stage; i++) अणु
			अगर (i == 0)
				local_in_frame = in_frame;
			अन्यथा
				local_in_frame = शून्य;
#अगर_अघोषित ISP2401
			अगर (!need_pp && (i == num_primary_stage - 1))
#अन्यथा
			अगर (!need_pp && (i == num_primary_stage - 1) && !need_ldc)
#पूर्ण_अगर
				local_out_frame = out_frame;
			अन्यथा
				local_out_frame = शून्य;
			ia_css_pipe_util_set_output_frames(out_frames, 0, local_out_frame);
			/*
			    * WARNING: The #अगर def flag has been added below as a
			    * temporary solution to solve the problem of enabling the
			    * view finder in a single binary in a capture flow. The
			    * vf-pp stage has been हटाओd from Skycam in the solution
			    * provided. The vf-pp stage should be re-पूर्णांकroduced when
			    * required. This  * should not be considered as a clean solution.
			    * Proper investigation should be करोne to come up with the clean
			    * solution.
			    * */
			ia_css_pipe_get_generic_stage_desc(&stage_desc, primary_binary[i],
							    out_frames, local_in_frame, शून्य);
			err = ia_css_pipeline_create_and_add_stage(me,
				&stage_desc,
				&current_stage);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
		पूर्ण
		/* If we use copy iso primary,
		    the input must be yuv iso raw */
		current_stage->args.copy_vf =
		    primary_binary[0]->info->sp.pipeline.mode ==
		    IA_CSS_BINARY_MODE_COPY;
		current_stage->args.copy_output = current_stage->args.copy_vf;
	पूर्ण अन्यथा अगर (mode == IA_CSS_CAPTURE_MODE_ADVANCED ||
		    mode == IA_CSS_CAPTURE_MODE_LOW_LIGHT)
	अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, pre_isp_binary,
						    out_frames, in_frame, शून्य);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc, शून्य);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
		ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, anr_gdc_binary,
						    out_frames, शून्य, शून्य);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc, शून्य);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण

		अगर (need_pp) अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, post_isp_binary,
							    out_frames, शून्य, शून्य);
		पूर्ण अन्यथा अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, post_isp_binary,
							    out_frames, शून्य, शून्य);
		पूर्ण

		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc, &current_stage);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (mode == IA_CSS_CAPTURE_MODE_BAYER)
	अणु
		ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, pre_isp_binary,
						    out_frames, in_frame, शून्य);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			शून्य);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

#अगर_अघोषित ISP2401
	अगर (need_pp && current_stage)
	अणु
		काष्ठा ia_css_frame *local_in_frame = शून्य;

		local_in_frame = current_stage->args.out_frame[0];

		अगर (need_ldc) अणु
			ia_css_pipe_util_set_output_frames(out_frames, 0, शून्य);
			ia_css_pipe_get_generic_stage_desc(&stage_desc, capture_ldc_binary,
							    out_frames, local_in_frame, शून्य);
			err = ia_css_pipeline_create_and_add_stage(me,
				&stage_desc,
				&current_stage);
			local_in_frame = current_stage->args.out_frame[0];
		पूर्ण
		err = add_capture_pp_stage(pipe, me, local_in_frame,
					    need_yuv_pp ? शून्य : out_frame,
#अन्यथा
	/* ldc and capture_pp not supported in same pipeline */
	अगर (need_ldc && current_stage)
	अणु
		in_frame = current_stage->args.out_frame[0];
		ia_css_pipe_util_set_output_frames(out_frames, 0, out_frame);
		ia_css_pipe_get_generic_stage_desc(&stage_desc, capture_ldc_binary,
						    out_frames, in_frame, शून्य);
		err = ia_css_pipeline_create_and_add_stage(me,
			&stage_desc,
			शून्य);
	पूर्ण अन्यथा अगर (need_pp && current_stage)
	अणु
		in_frame = current_stage->args.out_frame[0];
		err = add_capture_pp_stage(pipe, me, in_frame, need_yuv_pp ? शून्य : out_frame,
#पूर्ण_अगर
					    capture_pp_binary,
					    &current_stage);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (need_yuv_pp && current_stage)
	अणु
		काष्ठा ia_css_frame *पंचांगp_in_frame = current_stage->args.out_frame[0];
		काष्ठा ia_css_frame *पंचांगp_out_frame = शून्य;

		क्रम (i = 0; i < num_yuv_scaler; i++) अणु
			अगर (is_output_stage[i])
				पंचांगp_out_frame = out_frame;
			अन्यथा
				पंचांगp_out_frame = शून्य;

			err = add_yuv_scaler_stage(pipe, me, पंचांगp_in_frame, पंचांगp_out_frame,
						    शून्य,
						    &yuv_scaler_binary[i],
						    &yuv_scaler_stage);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				वापस err;
			पूर्ण
			/* we use output port 1 as पूर्णांकernal output port */
			पंचांगp_in_frame = yuv_scaler_stage->args.out_frame[1];
		पूर्ण
	पूर्ण

	/*
	    * WARNING: The #अगर def flag has been added below as a
	    * temporary solution to solve the problem of enabling the
	    * view finder in a single binary in a capture flow. The vf-pp
	    * stage has been हटाओd from Skycam in the solution provided.
	    * The vf-pp stage should be re-पूर्णांकroduced when required. This
	    * should not be considered as a clean solution. Proper
	    * investigation should be करोne to come up with the clean solution.
	    * */
	अगर (mode != IA_CSS_CAPTURE_MODE_RAW && mode != IA_CSS_CAPTURE_MODE_BAYER && current_stage && vf_frame)
	अणु
		in_frame = current_stage->args.out_vf_frame;
		err = add_vf_pp_stage(pipe, in_frame, vf_frame, vf_pp_binary,
					&current_stage);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण
	ia_css_pipeline_finalize_stages(&pipe->pipeline, pipe->stream->config.continuous);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "create_host_regular_capture_pipeline() leave:\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
create_host_capture_pipeline(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);

	अगर (pipe->config.mode == IA_CSS_PIPE_MODE_COPY)
		err = create_host_isyscopy_capture_pipeline(pipe);
	अन्यथा
		err = create_host_regular_capture_pipeline(pipe);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(err);

	वापस err;
पूर्ण

अटल पूर्णांक capture_start(
    काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_pipeline *me;

	पूर्णांक err = 0;
	क्रमागत sh_css_pipe_config_override copy_ovrd;

	IA_CSS_ENTER_PRIVATE("pipe = %p", pipe);
	अगर (!pipe) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	me = &pipe->pipeline;

	अगर ((pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_RAW   ||
		pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_BAYER) &&
	    (pipe->config.mode != IA_CSS_PIPE_MODE_COPY)) अणु
		अगर (copy_on_sp(pipe)) अणु
			err = start_copy_on_sp(pipe, &me->out_frame[0]);
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

#अगर !defined(ISP2401)
	/* old isys: need to send_mipi_frames() in all pipe modes */
	err = send_mipi_frames(pipe);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
#या_अगर defined(ISP2401)
	अगर (pipe->config.mode != IA_CSS_PIPE_MODE_COPY) अणु
		err = send_mipi_frames(pipe);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

#पूर्ण_अगर

	अणु
		अचिन्हित पूर्णांक thपढ़ो_id;

		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		copy_ovrd = 1 << thपढ़ो_id;
	पूर्ण
	start_pipe(pipe, copy_ovrd, pipe->stream->config.mode);

#अगर !defined(ISP2401)
	/*
	    * old isys: क्रम IA_CSS_PIPE_MODE_COPY pipe, isys rx has to be configured,
	    * which is currently करोne in start_binary(); but COPY pipe contains no binary,
	    * and करोes not call start_binary(); so we need to configure the rx here.
	    */
	अगर (pipe->config.mode == IA_CSS_PIPE_MODE_COPY &&
	    pipe->stream->reconfigure_css_rx) अणु
		ia_css_isys_rx_configure(&pipe->stream->csi_rx_config,
					    pipe->stream->config.mode);
		pipe->stream->reconfigure_css_rx = false;
	पूर्ण
#पूर्ण_अगर

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल पूर्णांक
sh_css_pipe_get_output_frame_info(काष्ठा ia_css_pipe *pipe,
				    काष्ठा ia_css_frame_info *info,
				    अचिन्हित पूर्णांक idx) अणु
	निश्चित(pipe);
	निश्चित(info);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_pipe_get_output_frame_info() enter:\n");

	*info = pipe->output_info[idx];
	अगर (copy_on_sp(pipe) &&
	    pipe->stream->config.input_config.क्रमmat == ATOMISP_INPUT_FORMAT_BINARY_8)
	अणु
		ia_css_frame_info_init(
		    info,
		    JPEG_BYTES,
		    1,
		    IA_CSS_FRAME_FORMAT_BINARY_8,
		    0);
	पूर्ण अन्यथा अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW ||
		    info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW_PACKED)
	अणु
		info->raw_bit_depth =
		ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_pipe_get_output_frame_info() leave:\n");
	वापस 0;
पूर्ण

व्योम
ia_css_stream_send_input_frame(स्थिर काष्ठा ia_css_stream *stream,
				स्थिर अचिन्हित लघु *data,
				अचिन्हित पूर्णांक width,
				अचिन्हित पूर्णांक height) अणु
	निश्चित(stream);

	ia_css_inputfअगरo_send_input_frame(
	    data, width, height,
	    stream->config.channel_id,
	    stream->config.input_config.क्रमmat,
	    stream->config.pixels_per_घड़ी == 2);
पूर्ण

व्योम
ia_css_stream_start_input_frame(स्थिर काष्ठा ia_css_stream *stream) अणु
	निश्चित(stream);

	ia_css_inputfअगरo_start_frame(
	    stream->config.channel_id,
	    stream->config.input_config.क्रमmat,
	    stream->config.pixels_per_घड़ी == 2);
पूर्ण

व्योम
ia_css_stream_send_input_line(स्थिर काष्ठा ia_css_stream *stream,
				स्थिर अचिन्हित लघु *data,
				अचिन्हित पूर्णांक width,
				स्थिर अचिन्हित लघु *data2,
				अचिन्हित पूर्णांक width2) अणु
	निश्चित(stream);

	ia_css_inputfअगरo_send_line(stream->config.channel_id,
				    data, width, data2, width2);
पूर्ण

व्योम
ia_css_stream_send_input_embedded_line(स्थिर काष्ठा ia_css_stream *stream,
					क्रमागत atomisp_input_क्रमmat क्रमmat,
					स्थिर अचिन्हित लघु *data,
					अचिन्हित पूर्णांक width) अणु
	निश्चित(stream);
	अगर (!data || width == 0)
		वापस;
	ia_css_inputfअगरo_send_embedded_line(stream->config.channel_id,
					    क्रमmat, data, width);
पूर्ण

व्योम
ia_css_stream_end_input_frame(स्थिर काष्ठा ia_css_stream *stream) अणु
	निश्चित(stream);

	ia_css_inputfअगरo_end_frame(stream->config.channel_id);
पूर्ण

अटल व्योम
append_firmware(काष्ठा ia_css_fw_info **l, काष्ठा ia_css_fw_info *firmware) अणु
	IA_CSS_ENTER_PRIVATE("l = %p, firmware = %p", l, firmware);
	अगर (!l) अणु
		IA_CSS_ERROR("NULL fw_info");
		IA_CSS_LEAVE_PRIVATE("");
		वापस;
	पूर्ण
	जबतक (*l)
		l = &(*l)->next;
	*l = firmware;
	/*firmware->next = शून्य;*/ /* when multiple acc extensions are loaded, 'next' can be not शून्य */
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

अटल व्योम
हटाओ_firmware(काष्ठा ia_css_fw_info **l, काष्ठा ia_css_fw_info *firmware) अणु
	निश्चित(*l);
	निश्चित(firmware);
	(व्योम)l;
	(व्योम)firmware;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "remove_firmware() enter:\n");

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE, "remove_firmware() leave:\n");
	वापस; /* removing single and multiple firmware is handled in acc_unload_extension() */
पूर्ण

अटल पूर्णांक upload_isp_code(काष्ठा ia_css_fw_info *firmware)
अणु
	ia_css_ptr binary;

	अगर (!firmware) अणु
		IA_CSS_ERROR("NULL input parameter");
		वापस -EINVAL;
	पूर्ण
	binary = firmware->info.isp.xmem_addr;

	अगर (!binary) अणु
		अचिन्हित पूर्णांक size = firmware->blob.size;
		स्थिर अचिन्हित अक्षर *blob;
		स्थिर अचिन्हित अक्षर *binary_name;

		binary_name =
		    (स्थिर अचिन्हित अक्षर *)(IA_CSS_EXT_ISP_PROG_NAME(
						firmware));
		blob = binary_name +
			म_माप((स्थिर अक्षर *)binary_name) +
			1;
		binary = sh_css_load_blob(blob, size);
		firmware->info.isp.xmem_addr = binary;
	पूर्ण

	अगर (!binary)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक
acc_load_extension(काष्ठा ia_css_fw_info *firmware) अणु
	पूर्णांक err;
	काष्ठा ia_css_fw_info *hd = firmware;

	जबतक (hd)
	अणु
		err = upload_isp_code(hd);
		अगर (err)
			वापस err;
		hd = hd->next;
	पूर्ण

	अगर (!firmware)
		वापस -EINVAL;
	firmware->loaded = true;
	वापस 0;
पूर्ण

अटल व्योम
acc_unload_extension(काष्ठा ia_css_fw_info *firmware) अणु
	काष्ठा ia_css_fw_info *hd = firmware;
	काष्ठा ia_css_fw_info *hdn = शून्य;

	अगर (!firmware) /* should not happen */
		वापस;
	/* unload and हटाओ multiple firmwares */
	जबतक (hd) अणु
		hdn = (hd->next) ? &(*hd->next) : शून्य;
		अगर (hd->info.isp.xmem_addr) अणु
			hmm_मुक्त(hd->info.isp.xmem_addr);
			hd->info.isp.xmem_addr = mmgr_शून्य;
		पूर्ण
		hd->isp_code = शून्य;
		hd->next = शून्य;
		hd = hdn;
	पूर्ण

	firmware->loaded = false;
पूर्ण

/* Load firmware क्रम extension */
अटल पूर्णांक
ia_css_pipe_load_extension(काष्ठा ia_css_pipe *pipe,
			    काष्ठा ia_css_fw_info *firmware) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("fw = %p pipe = %p", firmware, pipe);

	अगर ((!firmware) || (!pipe))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर (firmware->info.isp.type == IA_CSS_ACC_OUTPUT)
		append_firmware(&pipe->output_stage, firmware);
	अन्यथा अगर (firmware->info.isp.type == IA_CSS_ACC_VIEWFINDER)
		append_firmware(&pipe->vf_stage, firmware);
	err = acc_load_extension(firmware);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* Unload firmware क्रम extension */
अटल व्योम
ia_css_pipe_unload_extension(काष्ठा ia_css_pipe *pipe,
				काष्ठा ia_css_fw_info *firmware) अणु
	IA_CSS_ENTER_PRIVATE("fw = %p pipe = %p", firmware, pipe);

	अगर ((!firmware) || (!pipe)) अणु
		IA_CSS_ERROR("NULL input parameters");
		IA_CSS_LEAVE_PRIVATE("");
		वापस;
	पूर्ण

	अगर (firmware->info.isp.type == IA_CSS_ACC_OUTPUT)
		हटाओ_firmware(&pipe->output_stage, firmware);
	अन्यथा अगर (firmware->info.isp.type == IA_CSS_ACC_VIEWFINDER)
		हटाओ_firmware(&pipe->vf_stage, firmware);
	acc_unload_extension(firmware);

	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

bool
ia_css_pipeline_uses_params(काष्ठा ia_css_pipeline *me) अणु
	काष्ठा ia_css_pipeline_stage *stage;

	निश्चित(me);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_uses_params() enter: me=%p\n", me);

	क्रम (stage = me->stages; stage; stage = stage->next)
		अगर (stage->binary_info && stage->binary_info->enable.params) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_pipeline_uses_params() leave: return_bool=true\n");
			वापस true;
		पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipeline_uses_params() leave: return_bool=false\n");
	वापस false;
पूर्ण

अटल पूर्णांक
sh_css_pipeline_add_acc_stage(काष्ठा ia_css_pipeline *pipeline,
				स्थिर व्योम *acc_fw) अणु
	काष्ठा ia_css_fw_info *fw = (काष्ठा ia_css_fw_info *)acc_fw;
	/* In QoS हाल, load_extension alपढ़ोy called, so skipping */
	पूर्णांक	err = 0;

	अगर (!fw->loaded)
		err = acc_load_extension(fw);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_pipeline_add_acc_stage() enter: pipeline=%p, acc_fw=%p\n",
			    pipeline, acc_fw);

	अगर (!err)
	अणु
		काष्ठा ia_css_pipeline_stage_desc stage_desc;

		ia_css_pipe_get_acc_stage_desc(&stage_desc, शून्य, fw);
		err = ia_css_pipeline_create_and_add_stage(pipeline,
			&stage_desc,
			शून्य);
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "sh_css_pipeline_add_acc_stage() leave: return_err=%d\n", err);
	वापस err;
पूर्ण

/*
    * @brief Tag a specअगरic frame in continuous capture.
    * Refer to "sh_css_internal.h" क्रम details.
    */
पूर्णांक ia_css_stream_capture_frame(काष्ठा ia_css_stream *stream,
	अचिन्हित पूर्णांक exp_id) अणु
	काष्ठा sh_css_tag_descr tag_descr;
	u32 encoded_tag_descr;
	पूर्णांक err;

	निश्चित(stream);
	IA_CSS_ENTER("exp_id=%d", exp_id);

	/* Only continuous streams have a tagger */
	अगर (exp_id == 0 || !stream->config.continuous) अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	अगर (!sh_css_sp_is_running()) अणु
		/* SP is not running. The queues are not valid */
		IA_CSS_LEAVE_ERR(-EBUSY);
		वापस -EBUSY;
	पूर्ण

	/* Create the tag descriptor from the parameters */
	sh_css_create_tag_descr(0, 0, 0, exp_id, &tag_descr);
	/* Encode the tag descriptor पूर्णांकo a 32-bit value */
	encoded_tag_descr = sh_css_encode_tag_descr(&tag_descr);
	/* Enqueue the encoded tag to the host2sp queue.
	    * Note: The pipe and stage IDs क्रम tag_cmd queue are hard-coded to 0
	    * on both host and the SP side.
	    * It is मुख्यly because it is enough to have only one tag_cmd queue */
	err = ia_css_bufq_enqueue_tag_cmd(encoded_tag_descr);

	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

/*
    * @brief Configure the continuous capture.
    * Refer to "sh_css_internal.h" क्रम details.
    */
पूर्णांक ia_css_stream_capture(
    काष्ठा ia_css_stream *stream,
    पूर्णांक num_captures,
    अचिन्हित पूर्णांक skip,
    पूर्णांक offset) अणु
	काष्ठा sh_css_tag_descr tag_descr;
	अचिन्हित पूर्णांक encoded_tag_descr;
	पूर्णांक वापस_err;

	अगर (!stream)
		वापस -EINVAL;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_stream_capture() enter: num_captures=%d, skip=%d, offset=%d\n",
			    num_captures, skip, offset);

	/* Check अगर the tag descriptor is valid */
	अगर (num_captures < SH_CSS_MINIMUM_TAG_ID) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_stream_capture() leave: return_err=%d\n",
				    -EINVAL);
		वापस -EINVAL;
	पूर्ण

	/* Create the tag descriptor from the parameters */
	sh_css_create_tag_descr(num_captures, skip, offset, 0, &tag_descr);

	/* Encode the tag descriptor पूर्णांकo a 32-bit value */
	encoded_tag_descr = sh_css_encode_tag_descr(&tag_descr);

	अगर (!sh_css_sp_is_running()) अणु
		/* SP is not running. The queues are not valid */
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_stream_capture() leaving:queues unavailable\n");
		वापस -EBUSY;
	पूर्ण

	/* Enqueue the encoded tag to the host2sp queue.
	    * Note: The pipe and stage IDs क्रम tag_cmd queue are hard-coded to 0
	    * on both host and the SP side.
	    * It is मुख्यly because it is enough to have only one tag_cmd queue */
	वापस_err = ia_css_bufq_enqueue_tag_cmd((uपूर्णांक32_t)encoded_tag_descr);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_stream_capture() leave: return_err=%d\n",
			    वापस_err);

	वापस वापस_err;
पूर्ण

व्योम ia_css_stream_request_flash(काष्ठा ia_css_stream *stream)
अणु
	(व्योम)stream;

	निश्चित(stream);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_stream_request_flash() enter: void\n");

#अगर_अघोषित ISP2401
	sh_css_ग_लिखो_host2sp_command(host2sp_cmd_start_flash);
#अन्यथा
	अगर (sh_css_sp_is_running()) अणु
		अगर (!sh_css_ग_लिखो_host2sp_command(host2sp_cmd_start_flash)) अणु
			IA_CSS_ERROR("Call to 'sh-css_write_host2sp_command()' failed");
			ia_css_debug_dump_sp_sw_debug_info();
			ia_css_debug_dump_debug_info(शून्य);
		पूर्ण
	पूर्ण अन्यथा
		IA_CSS_LOG("SP is not running!");

#पूर्ण_अगर
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_stream_request_flash() leave: return_void\n");
पूर्ण

अटल व्योम
sh_css_init_host_sp_control_vars(व्योम) अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक HIVE_ADDR_ia_css_ispctrl_sp_isp_started;

	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_queues_initialized;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_sleep_mode;
	अचिन्हित पूर्णांक HIVE_ADDR_ia_css_dmaproxy_sp_invalidate_tlb;
#अगर_अघोषित ISP2401
	अचिन्हित पूर्णांक HIVE_ADDR_sp_stop_copy_preview;
#पूर्ण_अगर
	अचिन्हित पूर्णांक HIVE_ADDR_host_sp_com;
	अचिन्हित पूर्णांक o = दुरत्व(काष्ठा host_sp_communication, host2sp_command)
			    / माप(पूर्णांक);

	अचिन्हित पूर्णांक i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_init_host_sp_control_vars() enter: void\n");

	fw = &sh_css_sp_fw;
	HIVE_ADDR_ia_css_ispctrl_sp_isp_started = fw->info.sp.isp_started;

	HIVE_ADDR_host_sp_queues_initialized =
	    fw->info.sp.host_sp_queues_initialized;
	HIVE_ADDR_sp_sleep_mode = fw->info.sp.sleep_mode;
	HIVE_ADDR_ia_css_dmaproxy_sp_invalidate_tlb = fw->info.sp.invalidate_tlb;
#अगर_अघोषित ISP2401
	HIVE_ADDR_sp_stop_copy_preview = fw->info.sp.stop_copy_preview;
#पूर्ण_अगर
	HIVE_ADDR_host_sp_com = fw->info.sp.host_sp_com;

	(व्योम)HIVE_ADDR_ia_css_ispctrl_sp_isp_started; /* Suppres warnings in CRUN */

	(व्योम)HIVE_ADDR_sp_sleep_mode;
	(व्योम)HIVE_ADDR_ia_css_dmaproxy_sp_invalidate_tlb;
#अगर_अघोषित ISP2401
	(व्योम)HIVE_ADDR_sp_stop_copy_preview;
#पूर्ण_अगर
	(व्योम)HIVE_ADDR_host_sp_com;

	sp_dmem_store_uपूर्णांक32(SP0_ID,
				(अचिन्हित पूर्णांक)sp_address_of(ia_css_ispctrl_sp_isp_started),
				(uपूर्णांक32_t)(0));

	sp_dmem_store_uपूर्णांक32(SP0_ID,
				(अचिन्हित पूर्णांक)sp_address_of(host_sp_queues_initialized),
				(uपूर्णांक32_t)(0));
	sp_dmem_store_uपूर्णांक32(SP0_ID,
				(अचिन्हित पूर्णांक)sp_address_of(sp_sleep_mode),
				(uपूर्णांक32_t)(0));
	sp_dmem_store_uपूर्णांक32(SP0_ID,
				(अचिन्हित पूर्णांक)sp_address_of(ia_css_dmaproxy_sp_invalidate_tlb),
				(uपूर्णांक32_t)(false));
#अगर_अघोषित ISP2401
	sp_dmem_store_uपूर्णांक32(SP0_ID,
				(अचिन्हित पूर्णांक)sp_address_of(sp_stop_copy_preview),
				my_css.stop_copy_preview ? (uपूर्णांक32_t)(1) : (uपूर्णांक32_t)(0));
#पूर्ण_अगर
	store_sp_array_uपूर्णांक(host_sp_com, o, host2sp_cmd_पढ़ोy);

	क्रम (i = 0; i < N_CSI_PORTS; i++) अणु
		sh_css_update_host2sp_num_mipi_frames
		(my_css.num_mipi_frames[i]);
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "sh_css_init_host_sp_control_vars() leave: return_void\n");
पूर्ण

/*
 * create the पूर्णांकernal काष्ठाures and fill in the configuration data
 */

अटल स्थिर काष्ठा
ia_css_pipe_config ia_css_pipe_शेष_config = DEFAULT_PIPE_CONFIG;

व्योम ia_css_pipe_config_शेषs(काष्ठा ia_css_pipe_config *pipe_config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_pipe_config_defaults()\n");
	स_नकल(pipe_config, &ia_css_pipe_शेष_config, माप(*pipe_config));
पूर्ण

व्योम
ia_css_pipe_extra_config_शेषs(काष्ठा ia_css_pipe_extra_config
				    *extra_config) अणु
	अगर (!extra_config) अणु
		IA_CSS_ERROR("NULL input parameter");
		वापस;
	पूर्ण

	extra_config->enable_raw_binning = false;
	extra_config->enable_yuv_ds = false;
	extra_config->enable_high_speed = false;
	extra_config->enable_dvs_6axis = false;
	extra_config->enable_reduced_pipe = false;
	extra_config->disable_vf_pp = false;
	extra_config->enable_fractional_ds = false;
पूर्ण

व्योम ia_css_stream_config_शेषs(काष्ठा ia_css_stream_config *stream_config)
अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_config_defaults()\n");
	निश्चित(stream_config);
	स_रखो(stream_config, 0, माप(*stream_config));
	stream_config->online = true;
	stream_config->left_padding = -1;
	stream_config->pixels_per_घड़ी = 1;
	/* temporary शेष value क्रम backwards compatibility.
	    * This field used to be hardcoded within CSS but this has now
	    * been moved to the stream_config काष्ठा. */
	stream_config->source.port.rxcount = 0x04040404;
पूर्ण

अटल पूर्णांक
ia_css_acc_pipe_create(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = 0;

	अगर (!pipe)
	अणु
		IA_CSS_ERROR("NULL input parameter");
		वापस -EINVAL;
	पूर्ण

	/* There is not meaning क्रम num_execs = 0 semantically. Run atleast once. */
	अगर (pipe->config.acc_num_execs == 0)
		pipe->config.acc_num_execs = 1;

	अगर (pipe->config.acc_extension)
	अणु
		err = ia_css_pipe_load_extension(pipe, pipe->config.acc_extension);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ia_css_pipe_create(स्थिर काष्ठा ia_css_pipe_config *config,
		       काष्ठा ia_css_pipe **pipe)
अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("config = %p, pipe = %p", config, pipe);

	अगर (!config || !pipe) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	err = ia_css_pipe_create_extra(config, शून्य, pipe);

	अगर (err == 0) अणु
		IA_CSS_LOG("pipe created successfully = %p", *pipe);
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(err);

	वापस err;
पूर्ण

पूर्णांक
ia_css_pipe_create_extra(स्थिर काष्ठा ia_css_pipe_config *config,
			    स्थिर काष्ठा ia_css_pipe_extra_config *extra_config,
			    काष्ठा ia_css_pipe **pipe) अणु
	पूर्णांक err = -EINVAL;
	काष्ठा ia_css_pipe *पूर्णांकernal_pipe = शून्य;
	अचिन्हित पूर्णांक i;

	IA_CSS_ENTER_PRIVATE("config = %p, extra_config = %p and pipe = %p", config, extra_config, pipe);

	/* करो not allow to create more than the maximum limit */
	अगर (my_css.pipe_counter >= IA_CSS_PIPELINE_NUM_MAX)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-ENOSPC);
		वापस -EINVAL;
	पूर्ण

	अगर ((!pipe) || (!config))
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	ia_css_debug_dump_pipe_config(config);
	ia_css_debug_dump_pipe_extra_config(extra_config);

	err = create_pipe(config->mode, &पूर्णांकernal_pipe, false);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	/* now we have a pipe काष्ठाure to fill */
	पूर्णांकernal_pipe->config = *config;
	अगर (extra_config)
		पूर्णांकernal_pipe->extra_config = *extra_config;
	अन्यथा
		ia_css_pipe_extra_config_शेषs(&पूर्णांकernal_pipe->extra_config);

	अगर (config->mode == IA_CSS_PIPE_MODE_ACC)
	अणु
		/* Temporary hack to migrate acceleration to CSS 2.0.
		    * In the future the code क्रम all pipe types should be
		    * unअगरied. */
		*pipe = पूर्णांकernal_pipe;
		अगर (!पूर्णांकernal_pipe->config.acc_extension &&
		    पूर्णांकernal_pipe->config.num_acc_stages ==
		    0) अणु /* अगर no acc binary and no standalone stage */
			*pipe = शून्य;
			IA_CSS_LEAVE_ERR_PRIVATE(0);
			वापस 0;
		पूर्ण
		वापस ia_css_acc_pipe_create(पूर्णांकernal_pipe);
	पूर्ण

	/* Use config value when dvs_frame_delay setting equal to 2, otherwise always 1 by शेष */
	अगर (पूर्णांकernal_pipe->config.dvs_frame_delay == IA_CSS_FRAME_DELAY_2)
		पूर्णांकernal_pipe->dvs_frame_delay = 2;
	अन्यथा
		पूर्णांकernal_pipe->dvs_frame_delay = 1;

	/* we still keep enable_raw_binning क्रम backward compatibility, क्रम any new
	    fractional bayer करोwnscaling, we should use bayer_ds_out_res. अगर both are
	    specअगरied, bayer_ds_out_res will take precedence.अगर none is specअगरied, we
	    set bayer_ds_out_res equal to IF output resolution(IF may करो cropping on
	    sensor output) or use शेष decimation factor 1. */
	अगर (पूर्णांकernal_pipe->extra_config.enable_raw_binning &&
	    पूर्णांकernal_pipe->config.bayer_ds_out_res.width)
	अणु
		/* fill some code here, अगर no code is needed, please हटाओ it during पूर्णांकegration */
	पूर्ण

	/* YUV करोwnscaling */
	अगर ((पूर्णांकernal_pipe->config.vf_pp_in_res.width ||
		पूर्णांकernal_pipe->config.capt_pp_in_res.width))
	अणु
		क्रमागत ia_css_frame_क्रमmat क्रमmat;

		अगर (पूर्णांकernal_pipe->config.vf_pp_in_res.width) अणु
			क्रमmat = IA_CSS_FRAME_FORMAT_YUV_LINE;
			ia_css_frame_info_init(
			    &पूर्णांकernal_pipe->vf_yuv_ds_input_info,
			    पूर्णांकernal_pipe->config.vf_pp_in_res.width,
			    पूर्णांकernal_pipe->config.vf_pp_in_res.height,
			    क्रमmat, 0);
		पूर्ण
		अगर (पूर्णांकernal_pipe->config.capt_pp_in_res.width) अणु
			क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
			ia_css_frame_info_init(
			    &पूर्णांकernal_pipe->out_yuv_ds_input_info,
			    पूर्णांकernal_pipe->config.capt_pp_in_res.width,
			    पूर्णांकernal_pipe->config.capt_pp_in_res.height,
			    क्रमmat, 0);
		पूर्ण
	पूर्ण
	अगर (पूर्णांकernal_pipe->config.vf_pp_in_res.width &&
	    पूर्णांकernal_pipe->config.mode == IA_CSS_PIPE_MODE_PREVIEW)
	अणु
		ia_css_frame_info_init(
		    &पूर्णांकernal_pipe->vf_yuv_ds_input_info,
		    पूर्णांकernal_pipe->config.vf_pp_in_res.width,
		    पूर्णांकernal_pipe->config.vf_pp_in_res.height,
		    IA_CSS_FRAME_FORMAT_YUV_LINE, 0);
	पूर्ण
	/* handle bayer करोwnscaling output info */
	अगर (पूर्णांकernal_pipe->config.bayer_ds_out_res.width)
	अणु
		ia_css_frame_info_init(
		    &पूर्णांकernal_pipe->bds_output_info,
		    पूर्णांकernal_pipe->config.bayer_ds_out_res.width,
		    पूर्णांकernal_pipe->config.bayer_ds_out_res.height,
		    IA_CSS_FRAME_FORMAT_RAW, 0);
	पूर्ण

	/* handle output info, assume always needed */
	क्रम (i = 0; i < IA_CSS_PIPE_MAX_OUTPUT_STAGE; i++)
	अणु
		अगर (पूर्णांकernal_pipe->config.output_info[i].res.width) अणु
			err = sh_css_pipe_configure_output(
				    पूर्णांकernal_pipe,
				    पूर्णांकernal_pipe->config.output_info[i].res.width,
				    पूर्णांकernal_pipe->config.output_info[i].res.height,
				    पूर्णांकernal_pipe->config.output_info[i].padded_width,
				    पूर्णांकernal_pipe->config.output_info[i].क्रमmat,
				    i);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				kvमुक्त(पूर्णांकernal_pipe);
				पूर्णांकernal_pipe = शून्य;
				वापस err;
			पूर्ण
		पूर्ण

		/* handle vf output info, when configured */
		पूर्णांकernal_pipe->enable_viewfinder[i] =
		    (पूर्णांकernal_pipe->config.vf_output_info[i].res.width != 0);
		अगर (पूर्णांकernal_pipe->config.vf_output_info[i].res.width) अणु
			err = sh_css_pipe_configure_viewfinder(
				    पूर्णांकernal_pipe,
				    पूर्णांकernal_pipe->config.vf_output_info[i].res.width,
				    पूर्णांकernal_pipe->config.vf_output_info[i].res.height,
				    पूर्णांकernal_pipe->config.vf_output_info[i].padded_width,
				    पूर्णांकernal_pipe->config.vf_output_info[i].क्रमmat,
				    i);
			अगर (err) अणु
				IA_CSS_LEAVE_ERR_PRIVATE(err);
				kvमुक्त(पूर्णांकernal_pipe);
				पूर्णांकernal_pipe = शून्य;
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (पूर्णांकernal_pipe->config.acc_extension)
	अणु
		err = ia_css_pipe_load_extension(पूर्णांकernal_pipe,
						    पूर्णांकernal_pipe->config.acc_extension);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			kvमुक्त(पूर्णांकernal_pipe);
			वापस err;
		पूर्ण
	पूर्ण
	/* set all info to zeroes first */
	स_रखो(&पूर्णांकernal_pipe->info, 0, माप(पूर्णांकernal_pipe->info));

	/* all went well, वापस the pipe */
	*pipe = पूर्णांकernal_pipe;
	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

पूर्णांक
ia_css_pipe_get_info(स्थिर काष्ठा ia_css_pipe *pipe,
			काष्ठा ia_css_pipe_info *pipe_info) अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_pipe_get_info()\n");
	निश्चित(pipe_info);
	अगर (!pipe_info)
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
				    "ia_css_pipe_get_info: pipe_info cannot be NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!pipe || !pipe->stream)
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
				    "ia_css_pipe_get_info: ia_css_stream_create needs to be called before ia_css_[stream/pipe]_get_info\n");
		वापस -EINVAL;
	पूर्ण
	/* we succeeded वापस the info */
	*pipe_info = pipe->info;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_pipe_get_info() leave\n");
	वापस 0;
पूर्ण

bool ia_css_pipe_has_dvs_stats(काष्ठा ia_css_pipe_info *pipe_info)
अणु
	अचिन्हित पूर्णांक i;

	अगर (pipe_info) अणु
		क्रम (i = 0; i < IA_CSS_DVS_STAT_NUM_OF_LEVELS; i++) अणु
			अगर (pipe_info->grid_info.dvs_grid.dvs_stat_grid_info.grd_cfg[i].grd_start.enable)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक
ia_css_pipe_override_frame_क्रमmat(काष्ठा ia_css_pipe *pipe,
				    पूर्णांक pin_index,
				    क्रमागत ia_css_frame_क्रमmat new_क्रमmat) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("pipe = %p, pin_index = %d, new_formats = %d", pipe, pin_index, new_क्रमmat);

	अगर (!pipe)
	अणु
		IA_CSS_ERROR("pipe is not set");
		err = -EINVAL;
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	अगर (0 != pin_index && 1 != pin_index)
	अणु
		IA_CSS_ERROR("pin index is not valid");
		err = -EINVAL;
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण
	अगर (new_क्रमmat != IA_CSS_FRAME_FORMAT_NV12_TILEY)
	अणु
		IA_CSS_ERROR("new format is not valid");
		err = -EINVAL;
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण अन्यथा
	अणु
		err = ia_css_pipe_check_क्रमmat(pipe, new_क्रमmat);
		अगर (!err) अणु
			अगर (pin_index == 0) अणु
				pipe->output_info[0].क्रमmat = new_क्रमmat;
			पूर्ण अन्यथा अणु
				pipe->vf_output_info[0].क्रमmat = new_क्रमmat;
			पूर्ण
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

#अगर !defined(ISP2401)
/* Configuration of INPUT_SYSTEM_VERSION_2401 is करोne on SP */
अटल पूर्णांक
ia_css_stream_configure_rx(काष्ठा ia_css_stream *stream) अणु
	काष्ठा ia_css_input_port *config;

	निश्चित(stream);

	config = &stream->config.source.port;
	/* AM: this code is not reliable, especially क्रम 2400 */
	अगर (config->num_lanes == 1)
		stream->csi_rx_config.mode = MONO_1L_1L_0L;
	अन्यथा अगर (config->num_lanes == 2)
		stream->csi_rx_config.mode = MONO_2L_1L_0L;
	अन्यथा अगर (config->num_lanes == 3)
		stream->csi_rx_config.mode = MONO_3L_1L_0L;
	अन्यथा अगर (config->num_lanes == 4)
		stream->csi_rx_config.mode = MONO_4L_1L_0L;
	अन्यथा अगर (config->num_lanes != 0)
		वापस -EINVAL;

	अगर (config->port > MIPI_PORT2_ID)
		वापस -EINVAL;
	stream->csi_rx_config.port =
	ia_css_isys_port_to_mipi_port(config->port);
	stream->csi_rx_config.समयout    = config->समयout;
	stream->csi_rx_config.initcount  = 0;
	stream->csi_rx_config.synccount  = 0x28282828;
	stream->csi_rx_config.rxcount    = config->rxcount;
	अगर (config->compression.type == IA_CSS_CSI2_COMPRESSION_TYPE_NONE)
		stream->csi_rx_config.comp = MIPI_PREDICTOR_NONE;
	अन्यथा
	अणु
		/* not implemented yet, requires extension of the rx_cfg_t
		    * काष्ठा */
		वापस -EINVAL;
	पूर्ण
	stream->csi_rx_config.is_two_ppc = (stream->config.pixels_per_घड़ी == 2);
	stream->reconfigure_css_rx = true;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा ia_css_pipe *
find_pipe(काष्ठा ia_css_pipe *pipes[],
	    अचिन्हित पूर्णांक num_pipes,
	    क्रमागत ia_css_pipe_mode mode,
	    bool copy_pipe) अणु
	अचिन्हित पूर्णांक i;

	निश्चित(pipes);
	क्रम (i = 0; i < num_pipes; i++) अणु
		निश्चित(pipes[i]);
		अगर (pipes[i]->config.mode != mode)
			जारी;
		अगर (copy_pipe && pipes[i]->mode != IA_CSS_PIPE_ID_COPY)
			जारी;
		वापस pipes[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
ia_css_acc_stream_create(काष्ठा ia_css_stream *stream) अणु
	पूर्णांक i;
	पूर्णांक err = 0;

	निश्चित(stream);
	IA_CSS_ENTER_PRIVATE("stream = %p", stream);

	अगर (!stream)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0;  i < stream->num_pipes; i++)
	अणु
		काष्ठा ia_css_pipe *pipe = stream->pipes[i];

		निश्चित(pipe);
		अगर (!pipe) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
			वापस -EINVAL;
		पूर्ण

		pipe->stream = stream;
	पूर्ण

	/* Map SP thपढ़ोs beक्रमe करोing anything. */
	err = map_sp_thपढ़ोs(stream, true);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	क्रम (i = 0;  i < stream->num_pipes; i++)
	अणु
		काष्ठा ia_css_pipe *pipe = stream->pipes[i];

		निश्चित(pipe);
		ia_css_pipe_map_queue(pipe, true);
	पूर्ण

	err = create_host_pipeline_काष्ठाure(stream);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	stream->started = false;

	IA_CSS_LEAVE_ERR_PRIVATE(0);

	वापस 0;
पूर्ण

अटल पूर्णांक
metadata_info_init(स्थिर काष्ठा ia_css_metadata_config *mdc,
		    काष्ठा ia_css_metadata_info *md) अणु
	/* Either both width and height should be set or neither */
	अगर ((mdc->resolution.height > 0) ^ (mdc->resolution.width > 0))
		वापस -EINVAL;

	md->resolution = mdc->resolution;
	/* We round up the stride to a multiple of the width
	    * of the port going to DDR, this is a HW requirements (DMA). */
	md->stride = CEIL_MUL(mdc->resolution.width, HIVE_ISP_DDR_WORD_BYTES);
	md->size = mdc->resolution.height * md->stride;
	वापस 0;
पूर्ण

/* ISP2401 */
अटल पूर्णांक check_pipe_resolutions(स्थिर काष्ठा ia_css_pipe *pipe)
अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("");

	अगर (!pipe || !pipe->stream) अणु
		IA_CSS_ERROR("null arguments");
		err = -EINVAL;
		जाओ EXIT;
	पूर्ण

	अगर (ia_css_util_check_res(pipe->config.input_effective_res.width,
				    pipe->config.input_effective_res.height) != 0) अणु
		IA_CSS_ERROR("effective resolution not supported");
		err = -EINVAL;
		जाओ EXIT;
	पूर्ण
	अगर (!ia_css_util_resolution_is_zero(
		pipe->stream->config.input_config.input_res)) अणु
		अगर (!ia_css_util_res_leq(pipe->config.input_effective_res,
					    pipe->stream->config.input_config.input_res)) अणु
			IA_CSS_ERROR("effective resolution is larger than input resolution");
			err = -EINVAL;
			जाओ EXIT;
		पूर्ण
	पूर्ण
	अगर (!ia_css_util_resolution_is_even(pipe->config.output_info[0].res)) अणु
		IA_CSS_ERROR("output resolution must be even");
		err = -EINVAL;
		जाओ EXIT;
	पूर्ण
	अगर (!ia_css_util_resolution_is_even(pipe->config.vf_output_info[0].res)) अणु
		IA_CSS_ERROR("VF resolution must be even");
		err = -EINVAL;
		जाओ EXIT;
	पूर्ण
EXIT:
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

पूर्णांक
ia_css_stream_create(स्थिर काष्ठा ia_css_stream_config *stream_config,
			पूर्णांक num_pipes,
			काष्ठा ia_css_pipe *pipes[],
			काष्ठा ia_css_stream **stream) अणु
	काष्ठा ia_css_pipe *curr_pipe;
	काष्ठा ia_css_stream *curr_stream = शून्य;
	bool spcopyonly;
	bool sensor_binning_changed;
	पूर्णांक i, j;
	पूर्णांक err = -EINVAL;
	काष्ठा ia_css_metadata_info md_info;
	काष्ठा ia_css_resolution effective_res;
#अगर_घोषित ISP2401
	bool aspect_ratio_crop_enabled = false;
#पूर्ण_अगर

	IA_CSS_ENTER("num_pipes=%d", num_pipes);
	ia_css_debug_dump_stream_config(stream_config, num_pipes);

	/* some checks */
	अगर (num_pipes == 0 ||
	    !stream ||
	    !pipes)
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

#अगर !defined(ISP2401)
	/* We करोn't support metadata क्रम JPEG stream, since they both use str2mem */
	अगर (stream_config->input_config.क्रमmat == ATOMISP_INPUT_FORMAT_BINARY_8 &&
	    stream_config->metadata_config.resolution.height > 0)
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित ISP2401
	अगर (stream_config->online && stream_config->pack_raw_pixels)
	अणु
		IA_CSS_LOG("online and pack raw is invalid on input system 2401");
		err = -EINVAL;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण
#पूर्ण_अगर

	ia_css_debug_pipe_graph_dump_stream_config(stream_config);

	/* check अगर mipi size specअगरied */
	अगर (stream_config->mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
#अगर_घोषित ISP2401
		अगर (!stream_config->online)
#पूर्ण_अगर
		अणु
			अचिन्हित पूर्णांक port = (अचिन्हित पूर्णांक)stream_config->source.port.port;

			अगर (port >= N_MIPI_PORT_ID) अणु
				err = -EINVAL;
				IA_CSS_LEAVE_ERR(err);
				वापस err;
			पूर्ण

			अगर (my_css.size_mem_words != 0) अणु
				my_css.mipi_frame_size[port] = my_css.size_mem_words;
			पूर्ण अन्यथा अगर (stream_config->mipi_buffer_config.size_mem_words != 0) अणु
				my_css.mipi_frame_size[port] = stream_config->mipi_buffer_config.size_mem_words;
			पूर्ण अन्यथा अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_stream_create() exit: error, need to set mipi frame size.\n");
				निश्चित(stream_config->mipi_buffer_config.size_mem_words != 0);
				err = -EINVAL;
				IA_CSS_LEAVE_ERR(err);
				वापस err;
			पूर्ण

			अगर (my_css.size_mem_words != 0) अणु
				my_css.num_mipi_frames[port] =
				    2; /* Temp change: Default क्रम backwards compatibility. */
			पूर्ण अन्यथा अगर (stream_config->mipi_buffer_config.nof_mipi_buffers != 0) अणु
				my_css.num_mipi_frames[port] =
				    stream_config->mipi_buffer_config.nof_mipi_buffers;
			पूर्ण अन्यथा अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_stream_create() exit: error, need to set number of mipi frames.\n");
				निश्चित(stream_config->mipi_buffer_config.nof_mipi_buffers != 0);
				err = -EINVAL;
				IA_CSS_LEAVE_ERR(err);
				वापस err;
			पूर्ण
		पूर्ण

	/* Currently we only supported metadata up to a certain size. */
	err = metadata_info_init(&stream_config->metadata_config, &md_info);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

	/* allocate the stream instance */
	curr_stream = kzalloc(माप(काष्ठा ia_css_stream), GFP_KERNEL);
	अगर (!curr_stream)
	अणु
		err = -ENOMEM;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण
	/* शेष all to 0 */
	curr_stream->info.metadata_info = md_info;

	/* allocate pipes */
	curr_stream->num_pipes = num_pipes;
	curr_stream->pipes = kसुस्मृति(num_pipes, माप(काष्ठा ia_css_pipe *), GFP_KERNEL);
	अगर (!curr_stream->pipes)
	अणु
		curr_stream->num_pipes = 0;
		kमुक्त(curr_stream);
		curr_stream = शून्य;
		err = -ENOMEM;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण
	/* store pipes */
	spcopyonly = (num_pipes == 1) && (pipes[0]->config.mode == IA_CSS_PIPE_MODE_COPY);
	क्रम (i = 0; i < num_pipes; i++)
		curr_stream->pipes[i] = pipes[i];
	curr_stream->last_pipe = curr_stream->pipes[0];
	/* take over stream config */
	curr_stream->config = *stream_config;

#अगर defined(ISP2401)
	अगर (stream_config->mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR &&
	    stream_config->online)
		curr_stream->config.online = false;
#पूर्ण_अगर

#अगर_घोषित ISP2401
	अगर (curr_stream->config.online)
	अणु
		curr_stream->config.source.port.num_lanes =
		    stream_config->source.port.num_lanes;
		curr_stream->config.mode =  IA_CSS_INPUT_MODE_BUFFERED_SENSOR;
	पूर्ण
#पूर्ण_अगर
	/* in हाल driver करोesn't configure init number of raw buffers, configure it here */
	अगर (curr_stream->config.target_num_cont_raw_buf == 0)
		curr_stream->config.target_num_cont_raw_buf = NUM_CONTINUOUS_FRAMES;
	अगर (curr_stream->config.init_num_cont_raw_buf == 0)
		curr_stream->config.init_num_cont_raw_buf = curr_stream->config.target_num_cont_raw_buf;

	/* Enable locking & unlocking of buffers in RAW buffer pool */
	अगर (curr_stream->config.ia_css_enable_raw_buffer_locking)
		sh_css_sp_configure_enable_raw_pool_locking(
		    curr_stream->config.lock_all);

	/* copy mode specअगरic stuff */
	चयन (curr_stream->config.mode)
	अणु
	हाल IA_CSS_INPUT_MODE_SENSOR:
	हाल IA_CSS_INPUT_MODE_BUFFERED_SENSOR:
#अगर !defined(ISP2401)
		ia_css_stream_configure_rx(curr_stream);
#पूर्ण_अगर
		अवरोध;
	हाल IA_CSS_INPUT_MODE_TPG:
#अगर !defined(ISP2401)
		IA_CSS_LOG("tpg_configuration: x_mask=%d, y_mask=%d, x_delta=%d, y_delta=%d, xy_mask=%d",
			    curr_stream->config.source.tpg.x_mask,
			    curr_stream->config.source.tpg.y_mask,
			    curr_stream->config.source.tpg.x_delta,
			    curr_stream->config.source.tpg.y_delta,
			    curr_stream->config.source.tpg.xy_mask);

		sh_css_sp_configure_tpg(
		    curr_stream->config.source.tpg.x_mask,
		    curr_stream->config.source.tpg.y_mask,
		    curr_stream->config.source.tpg.x_delta,
		    curr_stream->config.source.tpg.y_delta,
		    curr_stream->config.source.tpg.xy_mask);
#पूर्ण_अगर
		अवरोध;
	हाल IA_CSS_INPUT_MODE_PRBS:
#अगर !defined(ISP2401)
		IA_CSS_LOG("mode prbs");
		sh_css_sp_configure_prbs(curr_stream->config.source.prbs.seed);
#पूर्ण_अगर
		अवरोध;
	हाल IA_CSS_INPUT_MODE_MEMORY:
		IA_CSS_LOG("mode memory");
		curr_stream->reconfigure_css_rx = false;
		अवरोध;
	शेष:
		IA_CSS_LOG("mode sensor/default");
	पूर्ण

#अगर_घोषित ISP2401
	err = aspect_ratio_crop_init(curr_stream,
					pipes,
					&aspect_ratio_crop_enabled);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		जाओ ERR;
	पूर्ण
#पूर्ण_अगर
	क्रम (i = 0; i < num_pipes; i++)
	अणु
		काष्ठा ia_css_resolution effective_res;

		curr_pipe = pipes[i];
		/* set current stream */
		curr_pipe->stream = curr_stream;
		/* take over effective info */

		effective_res = curr_pipe->config.input_effective_res;
		अगर (effective_res.height == 0 || effective_res.width == 0) अणु
			effective_res = curr_pipe->stream->config.input_config.effective_res;

#अगर defined(ISP2401)
			/* The aspect ratio cropping is currently only
			    * supported on the new input प्रणाली. */
			अगर (aspect_ratio_crop_check(aspect_ratio_crop_enabled, curr_pipe)) अणु
				काष्ठा ia_css_resolution crop_res;

				err = aspect_ratio_crop(curr_pipe, &crop_res);
				अगर (!err) अणु
					effective_res = crop_res;
				पूर्ण अन्यथा अणु
					/* in हाल of error fallback to शेष
					    * effective resolution from driver. */
					IA_CSS_LOG("aspect_ratio_crop() failed with err(%d)", err);
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			curr_pipe->config.input_effective_res = effective_res;
		पूर्ण
		IA_CSS_LOG("effective_res=%dx%d",
			    effective_res.width,
			    effective_res.height);
	पूर्ण

	अगर (IS_ISP2401) अणु
		क्रम (i = 0; i < num_pipes; i++) अणु
			अगर (pipes[i]->config.mode != IA_CSS_PIPE_MODE_ACC &&
			    pipes[i]->config.mode != IA_CSS_PIPE_MODE_COPY) अणु
				err = check_pipe_resolutions(pipes[i]);
				अगर (err) अणु
					जाओ ERR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	err = ia_css_stream_isp_parameters_init(curr_stream);
	अगर (err)
		जाओ ERR;
	IA_CSS_LOG("isp_params_configs: %p", curr_stream->isp_params_configs);

	अगर (num_pipes == 1 && pipes[0]->config.mode == IA_CSS_PIPE_MODE_ACC)
	अणु
		*stream = curr_stream;
		err = ia_css_acc_stream_create(curr_stream);
		जाओ ERR;
	पूर्ण
	/* sensor binning */
	अगर (!spcopyonly)
	अणु
		sensor_binning_changed =
		    sh_css_params_set_binning_factor(curr_stream,
							curr_stream->config.sensor_binning_factor);
	पूर्ण अन्यथा
	अणु
		sensor_binning_changed = false;
	पूर्ण

	IA_CSS_LOG("sensor_binning=%d, changed=%d",
		    curr_stream->config.sensor_binning_factor, sensor_binning_changed);
	/* loop over pipes */
	IA_CSS_LOG("num_pipes=%d", num_pipes);
	curr_stream->cont_capt = false;
	/* Temporary hack: we give the preview pipe a reference to the capture
	    * pipe in continuous capture mode. */
	अगर (curr_stream->config.continuous)
	अणु
		/* Search क्रम the preview pipe and create the copy pipe */
		काष्ठा ia_css_pipe *preview_pipe;
		काष्ठा ia_css_pipe *video_pipe;
		काष्ठा ia_css_pipe *acc_pipe;
		काष्ठा ia_css_pipe *capture_pipe = शून्य;
		काष्ठा ia_css_pipe *copy_pipe = शून्य;

		अगर (num_pipes >= 2) अणु
			curr_stream->cont_capt = true;
			curr_stream->disable_cont_vf = curr_stream->config.disable_cont_viewfinder;

			अगर (!IS_ISP2401)
				curr_stream->stop_copy_preview = my_css.stop_copy_preview;
		पूर्ण

		/* Create copy pipe here, since it may not be exposed to the driver */
		preview_pipe = find_pipe(pipes, num_pipes,
					    IA_CSS_PIPE_MODE_PREVIEW, false);
		video_pipe = find_pipe(pipes, num_pipes,
					IA_CSS_PIPE_MODE_VIDEO, false);
		acc_pipe = find_pipe(pipes, num_pipes,
					IA_CSS_PIPE_MODE_ACC, false);
		अगर (acc_pipe && num_pipes == 2 && curr_stream->cont_capt)
			curr_stream->cont_capt =
			    false; /* preview + QoS हाल will not need cont_capt चयन */
		अगर (curr_stream->cont_capt) अणु
			capture_pipe = find_pipe(pipes, num_pipes,
						    IA_CSS_PIPE_MODE_CAPTURE, false);
			अगर (!capture_pipe) अणु
				err = -EINVAL;
				जाओ ERR;
			पूर्ण
		पूर्ण
		/* We करो not support preview and video pipe at the same समय */
		अगर (preview_pipe && video_pipe) अणु
			err = -EINVAL;
			जाओ ERR;
		पूर्ण

		अगर (preview_pipe && !preview_pipe->pipe_settings.preview.copy_pipe) अणु
			err = create_pipe(IA_CSS_PIPE_MODE_CAPTURE, &copy_pipe, true);
			अगर (err)
				जाओ ERR;
			ia_css_pipe_config_शेषs(&copy_pipe->config);
			preview_pipe->pipe_settings.preview.copy_pipe = copy_pipe;
			copy_pipe->stream = curr_stream;
		पूर्ण
		अगर (preview_pipe && curr_stream->cont_capt) अणु
			preview_pipe->pipe_settings.preview.capture_pipe = capture_pipe;
		पूर्ण
		अगर (video_pipe && !video_pipe->pipe_settings.video.copy_pipe) अणु
			err = create_pipe(IA_CSS_PIPE_MODE_CAPTURE, &copy_pipe, true);
			अगर (err)
				जाओ ERR;
			ia_css_pipe_config_शेषs(&copy_pipe->config);
			video_pipe->pipe_settings.video.copy_pipe = copy_pipe;
			copy_pipe->stream = curr_stream;
		पूर्ण
		अगर (video_pipe && curr_stream->cont_capt) अणु
			video_pipe->pipe_settings.video.capture_pipe = capture_pipe;
		पूर्ण
		अगर (preview_pipe && acc_pipe) अणु
			preview_pipe->pipe_settings.preview.acc_pipe = acc_pipe;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < num_pipes; i++)
	अणु
		curr_pipe = pipes[i];
		/* set current stream */
		curr_pipe->stream = curr_stream;

		अगर (!IS_ISP2401) अणु
			/* take over effective info */

			effective_res = curr_pipe->config.input_effective_res;
			err = ia_css_util_check_res(
				effective_res.width,
				effective_res.height);
			अगर (err)
				जाओ ERR;
		पूर्ण
		/* sensor binning per pipe */
		अगर (sensor_binning_changed)
			sh_css_pipe_मुक्त_shading_table(curr_pipe);
	पूर्ण

	/* now pipes have been configured, info should be available */
	क्रम (i = 0; i < num_pipes; i++)
	अणु
		काष्ठा ia_css_pipe_info *pipe_info = शून्य;

		curr_pipe = pipes[i];

		err = sh_css_pipe_load_binaries(curr_pipe);
		अगर (err)
			जाओ ERR;

		/* handle each pipe */
		pipe_info = &curr_pipe->info;
		क्रम (j = 0; j < IA_CSS_PIPE_MAX_OUTPUT_STAGE; j++) अणु
			err = sh_css_pipe_get_output_frame_info(curr_pipe,
								&pipe_info->output_info[j], j);
			अगर (err)
				जाओ ERR;
		पूर्ण

		अगर (IS_ISP2401)
			pipe_info->output_प्रणाली_in_res_info = curr_pipe->config.output_प्रणाली_in_res;

		अगर (!spcopyonly) अणु
			अगर (!IS_ISP2401)
				err = sh_css_pipe_get_shading_info(curr_pipe,
								    &pipe_info->shading_info, शून्य);
			अन्यथा
				err = sh_css_pipe_get_shading_info(curr_pipe,
								    &pipe_info->shading_info, &curr_pipe->config);

			अगर (err)
				जाओ ERR;
			err = sh_css_pipe_get_grid_info(curr_pipe,
							&pipe_info->grid_info);
			अगर (err)
				जाओ ERR;
			क्रम (j = 0; j < IA_CSS_PIPE_MAX_OUTPUT_STAGE; j++) अणु
				sh_css_pipe_get_viewfinder_frame_info(curr_pipe,
									&pipe_info->vf_output_info[j], j);
				अगर (err)
					जाओ ERR;
			पूर्ण
		पूर्ण

		my_css.active_pipes[ia_css_pipe_get_pipe_num(curr_pipe)] = curr_pipe;
	पूर्ण

	curr_stream->started = false;

	/* Map SP thपढ़ोs beक्रमe करोing anything. */
	err = map_sp_thपढ़ोs(curr_stream, true);
	अगर (err)
	अणु
		IA_CSS_LOG("map_sp_threads: return_err=%d", err);
		जाओ ERR;
	पूर्ण

	क्रम (i = 0; i < num_pipes; i++)
	अणु
		curr_pipe = pipes[i];
		ia_css_pipe_map_queue(curr_pipe, true);
	पूर्ण

	/* Create host side pipeline objects without stages */
	err = create_host_pipeline_काष्ठाure(curr_stream);
	अगर (err)
	अणु
		IA_CSS_LOG("create_host_pipeline_structure: return_err=%d", err);
		जाओ ERR;
	पूर्ण

	/* assign curr_stream */
	*stream = curr_stream;

ERR:
	अगर (!err) अणु
		/* working mode: enter पूर्णांकo the seed list */
		अगर (my_css_save.mode == sh_css_mode_working) अणु
			क्रम (i = 0; i < MAX_ACTIVE_STREAMS; i++) अणु
				अगर (!my_css_save.stream_seeds[i].stream) अणु
					IA_CSS_LOG("entered stream into loc=%d", i);
					my_css_save.stream_seeds[i].orig_stream = stream;
					my_css_save.stream_seeds[i].stream = curr_stream;
					my_css_save.stream_seeds[i].num_pipes = num_pipes;
					my_css_save.stream_seeds[i].stream_config = *stream_config;
					क्रम (j = 0; j < num_pipes; j++) अणु
						my_css_save.stream_seeds[i].pipe_config[j] = pipes[j]->config;
						my_css_save.stream_seeds[i].pipes[j] = pipes[j];
						my_css_save.stream_seeds[i].orig_pipes[j] = &pipes[j];
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			ia_css_stream_destroy(curr_stream);
		पूर्ण
	पूर्ण अन्यथा अणु
		ia_css_stream_destroy(curr_stream);
	पूर्ण
	IA_CSS_LEAVE("return_err=%d mode=%d", err, my_css_save.mode);
	वापस err;
पूर्ण

पूर्णांक
ia_css_stream_destroy(काष्ठा ia_css_stream *stream) अणु
	पूर्णांक i;
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("stream = %p", stream);
	अगर (!stream)
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	ia_css_stream_isp_parameters_uninit(stream);

	अगर ((stream->last_pipe) &&
	    ia_css_pipeline_is_mapped(stream->last_pipe->pipe_num))
	अणु
#अगर defined(ISP2401)
		bool मुक्त_mpi;

		क्रम (i = 0; i < stream->num_pipes; i++) अणु
			काष्ठा ia_css_pipe *entry = stream->pipes[i];
			अचिन्हित पूर्णांक sp_thपढ़ो_id;
			काष्ठा sh_css_sp_pipeline_terminal *sp_pipeline_input_terminal;

			निश्चित(entry);
			अगर (entry) अणु
				/* get the SP thपढ़ो id */
				अगर (!ia_css_pipeline_get_sp_thपढ़ो_id(
					ia_css_pipe_get_pipe_num(entry), &sp_thपढ़ो_id))
					वापस -EINVAL;
				/* get the target input terminal */
				sp_pipeline_input_terminal =
				&sh_css_sp_group.pipe_io[sp_thपढ़ो_id].input;

				क्रम (i = 0; i < IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH; i++) अणु
					ia_css_isys_stream_h isys_stream =
					&sp_pipeline_input_terminal->context.भव_input_प्रणाली_stream[i];
					अगर (stream->config.isys_config[i].valid && isys_stream->valid)
						ia_css_isys_stream_destroy(isys_stream);
				पूर्ण
			पूर्ण
		पूर्ण
		मुक्त_mpi = stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR;
		अगर (IS_ISP2401) अणु
			मुक्त_mpi |= stream->config.mode == IA_CSS_INPUT_MODE_TPG;
			मुक्त_mpi |= stream->config.mode == IA_CSS_INPUT_MODE_PRBS;
		पूर्ण

		अगर (मुक्त_mpi) अणु
			क्रम (i = 0; i < stream->num_pipes; i++) अणु
				काष्ठा ia_css_pipe *entry = stream->pipes[i];
				/* मुक्त any mipi frames that are reमुख्यing:
				    * some test stream create-destroy cycles करो not generate output frames
				    * and the mipi buffer is not मुक्तd in the deque function
				    */
				अगर (entry)
					मुक्त_mipi_frames(entry);
			पूर्ण
		पूर्ण
		stream_unरेजिस्टर_with_csi_rx(stream);
#पूर्ण_अगर

		क्रम (i = 0; i < stream->num_pipes; i++) अणु
			काष्ठा ia_css_pipe *curr_pipe = stream->pipes[i];

			निश्चित(curr_pipe);
			ia_css_pipe_map_queue(curr_pipe, false);
		पूर्ण

		err = map_sp_thपढ़ोs(stream, false);
		अगर (err) अणु
			IA_CSS_LEAVE_ERR_PRIVATE(err);
			वापस err;
		पूर्ण
	पूर्ण

	/* हटाओ references from pipes to stream */
	क्रम (i = 0; i < stream->num_pipes; i++)
	अणु
		काष्ठा ia_css_pipe *entry = stream->pipes[i];

		निश्चित(entry);
		अगर (entry) अणु
			/* clear reference to stream */
			entry->stream = शून्य;
			/* check पूर्णांकernal copy pipe */
			अगर (entry->mode == IA_CSS_PIPE_ID_PREVIEW &&
			    entry->pipe_settings.preview.copy_pipe) अणु
				IA_CSS_LOG("clearing stream on internal preview copy pipe");
				entry->pipe_settings.preview.copy_pipe->stream = शून्य;
			पूर्ण
			अगर (entry->mode == IA_CSS_PIPE_ID_VIDEO &&
			    entry->pipe_settings.video.copy_pipe) अणु
				IA_CSS_LOG("clearing stream on internal video copy pipe");
				entry->pipe_settings.video.copy_pipe->stream = शून्य;
			पूर्ण
			err = sh_css_pipe_unload_binaries(entry);
		पूर्ण
	पूर्ण
	/* मुक्त associated memory of stream काष्ठा */
	kमुक्त(stream->pipes);
	stream->pipes = शून्य;
	stream->num_pipes = 0;

	/* working mode: take out of the seed list */
	अगर (my_css_save.mode == sh_css_mode_working) अणु
		क्रम (i = 0; i < MAX_ACTIVE_STREAMS; i++) अणु
			अगर (my_css_save.stream_seeds[i].stream == stream)
			अणु
				IA_CSS_LOG("took out stream %d", i);
				my_css_save.stream_seeds[i].stream = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	kमुक्त(stream);
	IA_CSS_LEAVE_ERR(err);

	वापस err;
पूर्ण

पूर्णांक
ia_css_stream_get_info(स्थिर काष्ठा ia_css_stream *stream,
			काष्ठा ia_css_stream_info *stream_info) अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_get_info: enter/exit\n");
	निश्चित(stream);
	निश्चित(stream_info);

	*stream_info = stream->info;
	वापस 0;
पूर्ण

/*
    * Rebuild a stream, including allocating काष्ठाs, setting configuration and
    * building the required pipes.
    * The data is taken from the css_save काष्ठा updated upon stream creation.
    * The stream handle is used to identअगरy the correct entry in the css_save काष्ठा
    */
पूर्णांक
ia_css_stream_load(काष्ठा ia_css_stream *stream) अणु
	अगर (!IS_ISP2401) अणु
		पूर्णांक i;
		पूर्णांक err;

		निश्चित(stream);
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,	"ia_css_stream_load() enter,\n");
		क्रम (i = 0; i < MAX_ACTIVE_STREAMS; i++)
		अणु
			अगर (my_css_save.stream_seeds[i].stream == stream) अणु
				पूर्णांक j;

				क्रम (j = 0; j < my_css_save.stream_seeds[i].num_pipes; j++) अणु
					अगर ((err = ia_css_pipe_create(&my_css_save.stream_seeds[i].pipe_config[j],
								    &my_css_save.stream_seeds[i].pipes[j])) != 0) अणु
						अगर (j) अणु
							पूर्णांक k;

							क्रम (k = 0; k < j; k++)
								ia_css_pipe_destroy(my_css_save.stream_seeds[i].pipes[k]);
						पूर्ण
						वापस err;
					पूर्ण
				पूर्ण
				err = ia_css_stream_create(&my_css_save.stream_seeds[i].stream_config,
							my_css_save.stream_seeds[i].num_pipes,
							my_css_save.stream_seeds[i].pipes,
							&my_css_save.stream_seeds[i].stream);
				अगर (err) अणु
					ia_css_stream_destroy(stream);
					क्रम (j = 0; j < my_css_save.stream_seeds[i].num_pipes; j++)
						ia_css_pipe_destroy(my_css_save.stream_seeds[i].pipes[j]);
					वापस err;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,	"ia_css_stream_load() exit,\n");
		वापस 0;
	पूर्ण अन्यथा अणु
		/* TODO हटाओ function - DEPRECATED */
		(व्योम)stream;
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक
ia_css_stream_start(काष्ठा ia_css_stream *stream) अणु
	पूर्णांक err = 0;

	IA_CSS_ENTER("stream = %p", stream);
	अगर ((!stream) || (!stream->last_pipe))
	अणु
		IA_CSS_LEAVE_ERR(-EINVAL);
		वापस -EINVAL;
	पूर्ण
	IA_CSS_LOG("starting %d", stream->last_pipe->mode);

	sh_css_sp_set_disable_continuous_viewfinder(stream->disable_cont_vf);

	/* Create host side pipeline. */
	err = create_host_pipeline(stream);
	अगर (err)
	अणु
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

#अगर defined(ISP2401)
	अगर ((stream->config.mode == IA_CSS_INPUT_MODE_SENSOR) ||
	    (stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR))
		stream_रेजिस्टर_with_csi_rx(stream);
#पूर्ण_अगर

#अगर !defined(ISP2401)
	/* Initialize mipi size checks */
	अगर (stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
	अणु
		अचिन्हित पूर्णांक idx;
		अचिन्हित पूर्णांक port = (अचिन्हित पूर्णांक)(stream->config.source.port.port);

		क्रम (idx = 0; idx < IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES_PER_PORT; idx++) अणु
			sh_css_sp_group.config.mipi_sizes_क्रम_check[port][idx] =
			sh_css_get_mipi_sizes_क्रम_check(port, idx);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (stream->config.mode != IA_CSS_INPUT_MODE_MEMORY)
	अणु
		err = sh_css_config_input_network(stream);
		अगर (err)
			वापस err;
	पूर्ण

	err = sh_css_pipe_start(stream);
	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

पूर्णांक
ia_css_stream_stop(काष्ठा ia_css_stream *stream) अणु
	पूर्णांक err = 0;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_stop() enter/exit\n");
	निश्चित(stream);
	निश्चित(stream->last_pipe);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_stream_stop: stopping %d\n",
			    stream->last_pipe->mode);

#अगर !defined(ISP2401)
	/* De-initialize mipi size checks */
	अगर (stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
	अणु
		अचिन्हित पूर्णांक idx;
		अचिन्हित पूर्णांक port = (अचिन्हित पूर्णांक)(stream->config.source.port.port);

		क्रम (idx = 0; idx < IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES_PER_PORT; idx++) अणु
			sh_css_sp_group.config.mipi_sizes_क्रम_check[port][idx] = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (!IS_ISP2401) अणु
		err = ia_css_pipeline_request_stop(&stream->last_pipe->pipeline);
	पूर्ण अन्यथा अणु
		err = sh_css_pipes_stop(stream);
	पूर्ण

	अगर (err)
		वापस err;

	/* Ideally, unmapping should happen after pipeline_stop, but current
	    * semantics करो not allow that. */
	/* err = map_sp_thपढ़ोs(stream, false); */

	वापस err;
पूर्ण

bool
ia_css_stream_has_stopped(काष्ठा ia_css_stream *stream) अणु
	bool stopped;

	निश्चित(stream);

	अगर (!IS_ISP2401) अणु
		stopped = ia_css_pipeline_has_stopped(&stream->last_pipe->pipeline);
	पूर्ण अन्यथा अणु
		stopped = sh_css_pipes_have_stopped(stream);
	पूर्ण

	वापस stopped;
पूर्ण

/* ISP2400 */
/*
    * Destroy the stream and all the pipes related to it.
    * The stream handle is used to identअगरy the correct entry in the css_save काष्ठा
    */
पूर्णांक
ia_css_stream_unload(काष्ठा ia_css_stream *stream) अणु
	पूर्णांक i;

	निश्चित(stream);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,	"ia_css_stream_unload() enter,\n");
	/* some checks */
	निश्चित(stream);
	क्रम (i = 0; i < MAX_ACTIVE_STREAMS; i++)
		अगर (my_css_save.stream_seeds[i].stream == stream)
		अणु
			पूर्णांक j;

			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_stream_unload(): unloading %d (%p)\n", i,
					    my_css_save.stream_seeds[i].stream);
			ia_css_stream_destroy(stream);
			क्रम (j = 0; j < my_css_save.stream_seeds[i].num_pipes; j++)
				ia_css_pipe_destroy(my_css_save.stream_seeds[i].pipes[j]);
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_stream_unload(): after unloading %d (%p)\n", i,
					    my_css_save.stream_seeds[i].stream);
			अवरोध;
		पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,	"ia_css_stream_unload() exit,\n");
	वापस 0;
पूर्ण

पूर्णांक
ia_css_temp_pipe_to_pipe_id(स्थिर काष्ठा ia_css_pipe *pipe,
			    क्रमागत ia_css_pipe_id *pipe_id) अणु
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_temp_pipe_to_pipe_id() enter/exit\n");
	अगर (pipe)
		*pipe_id = pipe->mode;
	अन्यथा
		*pipe_id = IA_CSS_PIPE_ID_COPY;

	वापस 0;
पूर्ण

क्रमागत atomisp_input_क्रमmat
ia_css_stream_get_क्रमmat(स्थिर काष्ठा ia_css_stream *stream) अणु
	वापस stream->config.input_config.क्रमmat;
पूर्ण

bool
ia_css_stream_get_two_pixels_per_घड़ी(स्थिर काष्ठा ia_css_stream *stream) अणु
	वापस (stream->config.pixels_per_घड़ी == 2);
पूर्ण

काष्ठा ia_css_binary *
ia_css_stream_get_shading_correction_binary(स्थिर काष्ठा ia_css_stream
	*stream) अणु
	काष्ठा ia_css_pipe *pipe;

	निश्चित(stream);

	pipe = stream->pipes[0];

	अगर (stream->num_pipes == 2) अणु
		निश्चित(stream->pipes[1]);
		अगर (stream->pipes[1]->config.mode == IA_CSS_PIPE_MODE_VIDEO ||
		    stream->pipes[1]->config.mode == IA_CSS_PIPE_MODE_PREVIEW)
			pipe = stream->pipes[1];
	पूर्ण

	वापस ia_css_pipe_get_shading_correction_binary(pipe);
पूर्ण

काष्ठा ia_css_binary *
ia_css_stream_get_dvs_binary(स्थिर काष्ठा ia_css_stream *stream) अणु
	पूर्णांक i;
	काष्ठा ia_css_pipe *video_pipe = शून्य;

	/* First we find the video pipe */
	क्रम (i = 0; i < stream->num_pipes; i++) अणु
		काष्ठा ia_css_pipe *pipe = stream->pipes[i];

		अगर (pipe->config.mode == IA_CSS_PIPE_MODE_VIDEO) अणु
			video_pipe = pipe;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (video_pipe)
		वापस &video_pipe->pipe_settings.video.video_binary;
	वापस शून्य;
पूर्ण

काष्ठा ia_css_binary *
ia_css_stream_get_3a_binary(स्थिर काष्ठा ia_css_stream *stream) अणु
	काष्ठा ia_css_pipe *pipe;
	काष्ठा ia_css_binary *s3a_binary = शून्य;

	निश्चित(stream);

	pipe = stream->pipes[0];

	अगर (stream->num_pipes == 2) अणु
		निश्चित(stream->pipes[1]);
		अगर (stream->pipes[1]->config.mode == IA_CSS_PIPE_MODE_VIDEO ||
		    stream->pipes[1]->config.mode == IA_CSS_PIPE_MODE_PREVIEW)
			pipe = stream->pipes[1];
	पूर्ण

	s3a_binary = ia_css_pipe_get_s3a_binary(pipe);

	वापस s3a_binary;
पूर्ण

पूर्णांक
ia_css_stream_set_output_padded_width(काष्ठा ia_css_stream *stream,
					अचिन्हित पूर्णांक output_padded_width) अणु
	काष्ठा ia_css_pipe *pipe;

	निश्चित(stream);

	pipe = stream->last_pipe;

	निश्चित(pipe);

	/* set the config also just in हाल (redundant info? why करो we save config in pipe?) */
	pipe->config.output_info[IA_CSS_PIPE_OUTPUT_STAGE_0].padded_width = output_padded_width;
	pipe->output_info[IA_CSS_PIPE_OUTPUT_STAGE_0].padded_width = output_padded_width;

	वापस 0;
पूर्ण

अटल काष्ठा ia_css_binary *
ia_css_pipe_get_shading_correction_binary(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_binary *binary = शून्य;

	निश्चित(pipe);

	चयन (pipe->config.mode) अणु
	हाल IA_CSS_PIPE_MODE_PREVIEW:
		binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.preview.preview_binary;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_VIDEO:
		binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.video.video_binary;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_CAPTURE:
		अगर (pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_PRIMARY) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < pipe->pipe_settings.capture.num_primary_stage; i++) अणु
				अगर (pipe->pipe_settings.capture.primary_binary[i].info->sp.enable.sc) अणु
					binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.primary_binary[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (pipe->config.शेष_capture_config.mode ==
			    IA_CSS_CAPTURE_MODE_BAYER)
			binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.pre_isp_binary;
		अन्यथा अगर (pipe->config.शेष_capture_config.mode ==
			    IA_CSS_CAPTURE_MODE_ADVANCED ||
			    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_LOW_LIGHT) अणु
			अगर (pipe->config.isp_pipe_version == IA_CSS_PIPE_VERSION_1)
				binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.pre_isp_binary;
			अन्यथा अगर (pipe->config.isp_pipe_version == IA_CSS_PIPE_VERSION_2_2)
				binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.post_isp_binary;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (binary && binary->info->sp.enable.sc)
		वापस binary;

	वापस शून्य;
पूर्ण

अटल काष्ठा ia_css_binary *
ia_css_pipe_get_s3a_binary(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_binary *binary = शून्य;

	निश्चित(pipe);

	चयन (pipe->config.mode) अणु
	हाल IA_CSS_PIPE_MODE_PREVIEW:
		binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.preview.preview_binary;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_VIDEO:
		binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.video.video_binary;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_CAPTURE:
		अगर (pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_PRIMARY) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < pipe->pipe_settings.capture.num_primary_stage; i++) अणु
				अगर (pipe->pipe_settings.capture.primary_binary[i].info->sp.enable.s3a) अणु
					binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.primary_binary[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (pipe->config.शेष_capture_config.mode ==
			    IA_CSS_CAPTURE_MODE_BAYER)
			binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.pre_isp_binary;
		अन्यथा अगर (pipe->config.शेष_capture_config.mode ==
			    IA_CSS_CAPTURE_MODE_ADVANCED ||
			    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_LOW_LIGHT) अणु
			अगर (pipe->config.isp_pipe_version == IA_CSS_PIPE_VERSION_1)
				binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.pre_isp_binary;
			अन्यथा अगर (pipe->config.isp_pipe_version == IA_CSS_PIPE_VERSION_2_2)
				binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.capture.post_isp_binary;
			अन्यथा
				निश्चित(0);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (binary && !binary->info->sp.enable.s3a)
		binary = शून्य;

	वापस binary;
पूर्ण

अटल काष्ठा ia_css_binary *
ia_css_pipe_get_sdis_binary(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_binary *binary = शून्य;

	निश्चित(pipe);

	चयन (pipe->config.mode) अणु
	हाल IA_CSS_PIPE_MODE_VIDEO:
		binary = (काष्ठा ia_css_binary *)&pipe->pipe_settings.video.video_binary;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (binary && !binary->info->sp.enable.dis)
		binary = शून्य;

	वापस binary;
पूर्ण

काष्ठा ia_css_pipeline *
ia_css_pipe_get_pipeline(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	निश्चित(pipe);

	वापस (काष्ठा ia_css_pipeline *)&pipe->pipeline;
पूर्ण

अचिन्हित पूर्णांक
ia_css_pipe_get_pipe_num(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	निश्चित(pipe);

	/* KW was not sure this function was not वापसing a value
	    that was out of range; so added an निश्चित, and, क्रम the
	    हाल when निश्चितs are not enabled, clip to the largest
	    value; pipe_num is अचिन्हित so the value cannot be too small
	*/
	निश्चित(pipe->pipe_num < IA_CSS_PIPELINE_NUM_MAX);

	अगर (pipe->pipe_num >= IA_CSS_PIPELINE_NUM_MAX)
		वापस (IA_CSS_PIPELINE_NUM_MAX - 1);

	वापस pipe->pipe_num;
पूर्ण

अचिन्हित पूर्णांक
ia_css_pipe_get_isp_pipe_version(स्थिर काष्ठा ia_css_pipe *pipe) अणु
	निश्चित(pipe);

	वापस (अचिन्हित पूर्णांक)pipe->config.isp_pipe_version;
पूर्ण

#घोषणा SP_START_TIMEOUT_US 30000000

पूर्णांक
ia_css_start_sp(व्योम) अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = 0;

	IA_CSS_ENTER("");
	sh_css_sp_start_isp();

	/* रुकोing क्रम the SP is completely started */
	समयout = SP_START_TIMEOUT_US;
	जबतक ((ia_css_spctrl_get_state(SP0_ID) != IA_CSS_SP_SW_INITIALIZED) && समयout)
	अणु
		समयout--;
		udelay(1);
	पूर्ण
	अगर (समयout == 0)
	अणु
		IA_CSS_ERROR("timeout during SP initialization");
		वापस -EINVAL;
	पूर्ण

	/* Workaround, in order to run two streams in parallel. See TASK 4271*/
	/* TODO: Fix this. */

	sh_css_init_host_sp_control_vars();

	/* buffers should be initialized only when sp is started */
	/* AM: At the moment it will be करोne only when there is no stream active. */

	sh_css_setup_queues();
	ia_css_bufq_dump_queue_info();

	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

/*
    *	Time to रुको SP क्रम termincate. Only condition when this can happen
    *	is a fatal hw failure, but we must be able to detect this and emit
    *	a proper error trace.
    */
#घोषणा SP_SHUTDOWN_TIMEOUT_US 200000

पूर्णांक
ia_css_stop_sp(व्योम) अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = 0;

	IA_CSS_ENTER("void");

	अगर (!sh_css_sp_is_running())
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE("SP already stopped : return_err=%d", err);

		/* Return an error - stop SP should not have been called by driver */
		वापस err;
	पूर्ण

	/* For now, stop whole SP */
	अगर (!IS_ISP2401) अणु
		sh_css_ग_लिखो_host2sp_command(host2sp_cmd_terminate);
	पूर्ण अन्यथा अणु
		अगर (!sh_css_ग_लिखो_host2sp_command(host2sp_cmd_terminate))
		अणु
			IA_CSS_ERROR("Call to 'sh-css_write_host2sp_command()' failed");
			ia_css_debug_dump_sp_sw_debug_info();
			ia_css_debug_dump_debug_info(शून्य);
		पूर्ण
	पूर्ण

	sh_css_sp_set_sp_running(false);

	समयout = SP_SHUTDOWN_TIMEOUT_US;
	जबतक (!ia_css_spctrl_is_idle(SP0_ID) && समयout)
	अणु
		समयout--;
		udelay(1);
	पूर्ण
	अगर ((ia_css_spctrl_get_state(SP0_ID) != IA_CSS_SP_SW_TERMINATED))
		IA_CSS_WARNING("SP has not terminated (SW)");

	अगर (समयout == 0)
	अणु
		IA_CSS_WARNING("SP is not idle");
		ia_css_debug_dump_sp_sw_debug_info();
	पूर्ण
	समयout = SP_SHUTDOWN_TIMEOUT_US;
	जबतक (!isp_ctrl_getbit(ISP0_ID, ISP_SC_REG, ISP_IDLE_BIT) && समयout)
	अणु
		समयout--;
		udelay(1);
	पूर्ण
	अगर (समयout == 0)
	अणु
		IA_CSS_WARNING("ISP is not idle");
		ia_css_debug_dump_sp_sw_debug_info();
	पूर्ण

	sh_css_hmm_buffer_record_uninit();

	/* clear pending param sets from refcount */
	sh_css_param_clear_param_sets();

	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

पूर्णांक
ia_css_update_continuous_frames(काष्ठा ia_css_stream *stream) अणु
	काष्ठा ia_css_pipe *pipe;
	अचिन्हित पूर्णांक i;

	ia_css_debug_dtrace(
	    IA_CSS_DEBUG_TRACE,
	    "sh_css_update_continuous_frames() enter:\n");

	अगर (!stream)
	अणु
		ia_css_debug_dtrace(
		    IA_CSS_DEBUG_TRACE,
		    "sh_css_update_continuous_frames() leave: invalid stream, return_void\n");
		वापस -EINVAL;
	पूर्ण

	pipe = stream->continuous_pipe;

	क्रम (i = stream->config.init_num_cont_raw_buf;
		i < stream->config.target_num_cont_raw_buf; i++)
	अणु
		sh_css_update_host2sp_offline_frame(i,
						    pipe->continuous_frames[i], pipe->cont_md_buffers[i]);
	पूर्ण
	sh_css_update_host2sp_cont_num_raw_frames
	(stream->config.target_num_cont_raw_buf, true);
	ia_css_debug_dtrace(
	    IA_CSS_DEBUG_TRACE,
	    "sh_css_update_continuous_frames() leave: return_void\n");

	वापस 0;
पूर्ण

व्योम ia_css_pipe_map_queue(काष्ठा ia_css_pipe *pipe, bool map)
अणु
	अचिन्हित पूर्णांक thपढ़ो_id;
	अचिन्हित पूर्णांक pipe_num;
	bool need_input_queue;

	IA_CSS_ENTER("");
	निश्चित(pipe);

	pipe_num = pipe->pipe_num;

	ia_css_pipeline_get_sp_thपढ़ो_id(pipe_num, &thपढ़ो_id);

#अगर defined(ISP2401)
	need_input_queue = true;
#अन्यथा
	need_input_queue = pipe->stream->config.mode == IA_CSS_INPUT_MODE_MEMORY;
#पूर्ण_अगर

	/* map required buffer queues to resources */
	/* TODO: to be improved */
	अगर (pipe->mode == IA_CSS_PIPE_ID_PREVIEW) अणु
		अगर (need_input_queue)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_INPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PARAMETER_SET, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PER_FRAME_PARAMETER_SET, map);
#अगर defined SH_CSS_ENABLE_METADATA
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_METADATA, map);
#पूर्ण_अगर
		अगर (pipe->pipe_settings.preview.preview_binary.info &&
		    pipe->pipe_settings.preview.preview_binary.info->sp.enable.s3a)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_3A_STATISTICS, map);
	पूर्ण अन्यथा अगर (pipe->mode == IA_CSS_PIPE_ID_CAPTURE) अणु
		अचिन्हित पूर्णांक i;

		अगर (need_input_queue)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_INPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PARAMETER_SET, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PER_FRAME_PARAMETER_SET, map);
#अगर defined SH_CSS_ENABLE_METADATA
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_METADATA, map);
#पूर्ण_अगर
		अगर (pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_PRIMARY) अणु
			क्रम (i = 0; i < pipe->pipe_settings.capture.num_primary_stage; i++) अणु
				अगर (pipe->pipe_settings.capture.primary_binary[i].info &&
				    pipe->pipe_settings.capture.primary_binary[i].info->sp.enable.s3a) अणु
					ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_3A_STATISTICS, map);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (pipe->config.शेष_capture_config.mode ==
			    IA_CSS_CAPTURE_MODE_ADVANCED ||
			    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_LOW_LIGHT ||
			    pipe->config.शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_BAYER) अणु
			अगर (pipe->pipe_settings.capture.pre_isp_binary.info &&
			    pipe->pipe_settings.capture.pre_isp_binary.info->sp.enable.s3a)
				ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_3A_STATISTICS, map);
		पूर्ण
	पूर्ण अन्यथा अगर (pipe->mode == IA_CSS_PIPE_ID_VIDEO) अणु
		अगर (need_input_queue)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_INPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, map);
		अगर (pipe->enable_viewfinder[IA_CSS_PIPE_OUTPUT_STAGE_0])
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PARAMETER_SET, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PER_FRAME_PARAMETER_SET, map);
#अगर defined SH_CSS_ENABLE_METADATA
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_METADATA, map);
#पूर्ण_अगर
		अगर (pipe->pipe_settings.video.video_binary.info &&
		    pipe->pipe_settings.video.video_binary.info->sp.enable.s3a)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_3A_STATISTICS, map);
		अगर (pipe->pipe_settings.video.video_binary.info &&
		    (pipe->pipe_settings.video.video_binary.info->sp.enable.dis
		    ))
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_DIS_STATISTICS, map);
	पूर्ण अन्यथा अगर (pipe->mode == IA_CSS_PIPE_ID_COPY) अणु
		अगर (need_input_queue)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_INPUT_FRAME, map);
		अगर (!pipe->stream->config.continuous)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, map);
#अगर defined SH_CSS_ENABLE_METADATA
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_METADATA, map);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (pipe->mode == IA_CSS_PIPE_ID_ACC) अणु
		अगर (need_input_queue)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_INPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PARAMETER_SET, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PER_FRAME_PARAMETER_SET, map);
#अगर defined SH_CSS_ENABLE_METADATA
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_METADATA, map);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (pipe->mode == IA_CSS_PIPE_ID_YUVPP) अणु
		अचिन्हित पूर्णांक idx;

		क्रम (idx = 0; idx < IA_CSS_PIPE_MAX_OUTPUT_STAGE; idx++) अणु
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME + idx, map);
			अगर (pipe->enable_viewfinder[idx])
				ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME + idx, map);
		पूर्ण
		अगर (need_input_queue)
			ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_INPUT_FRAME, map);
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_PARAMETER_SET, map);
#अगर defined SH_CSS_ENABLE_METADATA
		ia_css_queue_map(thपढ़ो_id, IA_CSS_BUFFER_TYPE_METADATA, map);
#पूर्ण_अगर
	पूर्ण
	IA_CSS_LEAVE("");
पूर्ण

#अगर CONFIG_ON_FRAME_ENQUEUE()
अटल पूर्णांक set_config_on_frame_enqueue(काष्ठा ia_css_frame_info
	*info, काष्ठा frame_data_wrapper *frame) अणु
	frame->config_on_frame_enqueue.padded_width = 0;

	/* currently we support configuration on frame enqueue only on YUV क्रमmats */
	/* on other क्रमmats the padded_width is zeroed क्रम no configuration override */
	चयन (info->क्रमmat) अणु
	हाल IA_CSS_FRAME_FORMAT_YUV420:
	हाल IA_CSS_FRAME_FORMAT_NV12:
		अगर (info->padded_width > info->res.width) अणु
			frame->config_on_frame_enqueue.padded_width = info->padded_width;
		पूर्ण अन्यथा अगर ((info->padded_width < info->res.width) && (info->padded_width > 0)) अणु
			वापस -EINVAL;
		पूर्ण
		/* nothing to करो अगर width == padded width or padded width is zeroed (the same) */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक
ia_css_unlock_raw_frame(काष्ठा ia_css_stream *stream, uपूर्णांक32_t exp_id) अणु
	पूर्णांक ret;

	IA_CSS_ENTER("");

	/* Only continuous streams have a tagger to which we can send the
	    * unlock message. */
	अगर (!stream || !stream->config.continuous)
	अणु
		IA_CSS_ERROR("invalid stream pointer");
		वापस -EINVAL;
	पूर्ण

	अगर (exp_id > IA_CSS_ISYS_MAX_EXPOSURE_ID ||
	    exp_id < IA_CSS_ISYS_MIN_EXPOSURE_ID)
	अणु
		IA_CSS_ERROR("invalid exposure ID: %d\n", exp_id);
		वापस -EINVAL;
	पूर्ण

	/* Send the event. Since we verअगरied that the exp_id is valid,
	    * we can safely assign it to an 8-bit argument here. */
	ret = ia_css_bufq_enqueue_psys_event(
	    IA_CSS_PSYS_SW_EVENT_UNLOCK_RAW_BUFFER, exp_id, 0, 0);

	IA_CSS_LEAVE_ERR(ret);
	वापस ret;
पूर्ण

/* @brief	Set the state (Enable or Disable) of the Extension stage in the
    *		given pipe.
    */
पूर्णांक
ia_css_pipe_set_qos_ext_state(काष्ठा ia_css_pipe *pipe, uपूर्णांक32_t fw_handle,
				bool enable) अणु
	अचिन्हित पूर्णांक thपढ़ो_id;
	काष्ठा ia_css_pipeline_stage *stage;
	पूर्णांक err = 0;

	IA_CSS_ENTER("");

	/* Parameter Check */
	अगर (!pipe || !pipe->stream)
	अणु
		IA_CSS_ERROR("Invalid Pipe.");
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!(pipe->config.acc_extension))
	अणु
		IA_CSS_ERROR("Invalid Pipe(No Extension Firmware)");
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!sh_css_sp_is_running())
	अणु
		IA_CSS_ERROR("Leaving: queue unavailable.");
		err = -EBUSY;
	पूर्ण अन्यथा
	अणु
		/* Query the thपढ़ोid and stage_num क्रम the Extension firmware*/
		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		err = ia_css_pipeline_get_stage_from_fw(&pipe->pipeline, fw_handle, &stage);
		अगर (!err) अणु
			/* Set the Extension State;. TODO: Add check क्रम stage firmware.type (QOS)*/
			err = ia_css_bufq_enqueue_psys_event(
			    (uपूर्णांक8_t)IA_CSS_PSYS_SW_EVENT_STAGE_ENABLE_DISABLE,
			    (uपूर्णांक8_t)thपढ़ो_id,
			    (uपूर्णांक8_t)stage->stage_num,
			    enable ? 1 : 0);
			अगर (!err) अणु
				अगर (enable)
					SH_CSS_QOS_STAGE_ENABLE(&sh_css_sp_group.pipe[thपढ़ो_id], stage->stage_num);
				अन्यथा
					SH_CSS_QOS_STAGE_DISABLE(&sh_css_sp_group.pipe[thपढ़ो_id], stage->stage_num);
			पूर्ण
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE("err:%d handle:%u enable:%d", err, fw_handle, enable);
	वापस err;
पूर्ण

/*	@brief	Get the state (Enable or Disable) of the Extension stage in the
    *	given pipe.
    */
पूर्णांक
ia_css_pipe_get_qos_ext_state(काष्ठा ia_css_pipe *pipe, uपूर्णांक32_t fw_handle,
				bool *enable) अणु
	काष्ठा ia_css_pipeline_stage *stage;
	अचिन्हित पूर्णांक thपढ़ो_id;
	पूर्णांक err = 0;

	IA_CSS_ENTER("");

	/* Parameter Check */
	अगर (!pipe || !pipe->stream)
	अणु
		IA_CSS_ERROR("Invalid Pipe.");
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!(pipe->config.acc_extension))
	अणु
		IA_CSS_ERROR("Invalid Pipe (No Extension Firmware).");
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!sh_css_sp_is_running())
	अणु
		IA_CSS_ERROR("Leaving: queue unavailable.");
		err = -EBUSY;
	पूर्ण अन्यथा
	अणु
		/* Query the thपढ़ोid and stage_num corresponding to the Extension firmware*/
		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		err = ia_css_pipeline_get_stage_from_fw(&pipe->pipeline, fw_handle, &stage);

		अगर (!err) अणु
			/* Get the Extension State */
			*enable = (SH_CSS_QOS_STAGE_IS_ENABLED(&sh_css_sp_group.pipe[thपढ़ो_id],
								stage->stage_num)) ? true : false;
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE("err:%d handle:%u enable:%d", err, fw_handle, *enable);
	वापस err;
पूर्ण

/* ISP2401 */
पूर्णांक
ia_css_pipe_update_qos_ext_mapped_arg(काष्ठा ia_css_pipe *pipe,
					u32 fw_handle,
					काष्ठा ia_css_isp_param_css_segments *css_seg,
					काष्ठा ia_css_isp_param_isp_segments *isp_seg) अणु
	अचिन्हित पूर्णांक HIVE_ADDR_sp_group;
	अटल काष्ठा sh_css_sp_group sp_group;
	अटल काष्ठा sh_css_sp_stage sp_stage;
	अटल काष्ठा sh_css_isp_stage isp_stage;
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक thपढ़ो_id;
	काष्ठा ia_css_pipeline_stage *stage;
	पूर्णांक err = 0;
	पूर्णांक stage_num = 0;
	क्रमागत ia_css_isp_memories mem;
	bool enabled;

	IA_CSS_ENTER("");

	fw = &sh_css_sp_fw;

	/* Parameter Check */
	अगर (!pipe || !pipe->stream)
	अणु
		IA_CSS_ERROR("Invalid Pipe.");
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!(pipe->config.acc_extension))
	अणु
		IA_CSS_ERROR("Invalid Pipe (No Extension Firmware).");
		err = -EINVAL;
	पूर्ण अन्यथा अगर (!sh_css_sp_is_running())
	अणु
		IA_CSS_ERROR("Leaving: queue unavailable.");
		err = -EBUSY;
	पूर्ण अन्यथा
	अणु
		/* Query the thपढ़ो_id and stage_num corresponding to the Extension firmware */
		ia_css_pipeline_get_sp_thपढ़ो_id(ia_css_pipe_get_pipe_num(pipe), &thपढ़ो_id);
		err = ia_css_pipeline_get_stage_from_fw(&pipe->pipeline, fw_handle, &stage);
		अगर (!err) अणु
			/* Get the Extension State */
			enabled = (SH_CSS_QOS_STAGE_IS_ENABLED(&sh_css_sp_group.pipe[thपढ़ो_id],
								stage->stage_num)) ? true : false;
			/* Update mapped arg only when extension stage is not enabled */
			अगर (enabled) अणु
				IA_CSS_ERROR("Leaving: cannot update when stage is enabled.");
				err = -EBUSY;
			पूर्ण अन्यथा अणु
				stage_num = stage->stage_num;

				HIVE_ADDR_sp_group = fw->info.sp.group;
				sp_dmem_load(SP0_ID,
						(अचिन्हित पूर्णांक)sp_address_of(sp_group),
						&sp_group, माप(काष्ठा sh_css_sp_group));
				hmm_load(sp_group.pipe[thपढ़ो_id].sp_stage_addr[stage_num],
					    &sp_stage, माप(काष्ठा sh_css_sp_stage));

				hmm_load(sp_stage.isp_stage_addr,
					    &isp_stage, माप(काष्ठा sh_css_isp_stage));

				क्रम (mem = 0; mem < N_IA_CSS_ISP_MEMORIES; mem++) अणु
					isp_stage.mem_initializers.params[IA_CSS_PARAM_CLASS_PARAM][mem].address =
					    css_seg->params[IA_CSS_PARAM_CLASS_PARAM][mem].address;
					isp_stage.mem_initializers.params[IA_CSS_PARAM_CLASS_PARAM][mem].size =
					    css_seg->params[IA_CSS_PARAM_CLASS_PARAM][mem].size;
					isp_stage.binary_info.mem_initializers.params[IA_CSS_PARAM_CLASS_PARAM][mem].address
					    =
						isp_seg->params[IA_CSS_PARAM_CLASS_PARAM][mem].address;
					isp_stage.binary_info.mem_initializers.params[IA_CSS_PARAM_CLASS_PARAM][mem].size
					    =
						isp_seg->params[IA_CSS_PARAM_CLASS_PARAM][mem].size;
				पूर्ण

				hmm_store(sp_stage.isp_stage_addr,
					    &isp_stage, माप(काष्ठा sh_css_isp_stage));
			पूर्ण
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE("err:%d handle:%u", err, fw_handle);
	वापस err;
पूर्ण

#अगर_घोषित ISP2401
अटल पूर्णांक
aspect_ratio_crop_init(काष्ठा ia_css_stream *curr_stream,
			काष्ठा ia_css_pipe *pipes[],
			bool *करो_crop_status) अणु
	पूर्णांक err = 0;
	पूर्णांक i;
	काष्ठा ia_css_pipe *curr_pipe;
	u32 pipe_mask = 0;

	अगर ((!curr_stream) ||
	    (curr_stream->num_pipes == 0) ||
	    (!pipes) ||
	    (!करो_crop_status))
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < curr_stream->num_pipes; i++)
	अणु
		curr_pipe = pipes[i];
		pipe_mask |= (1 << curr_pipe->config.mode);
	पूर्ण

	*करो_crop_status =
	(((pipe_mask & (1 << IA_CSS_PIPE_MODE_PREVIEW)) ||
	    (pipe_mask & (1 << IA_CSS_PIPE_MODE_VIDEO))) &&
	    (pipe_mask & (1 << IA_CSS_PIPE_MODE_CAPTURE)) &&
	    curr_stream->config.continuous);
	वापस 0;
पूर्ण

अटल bool
aspect_ratio_crop_check(bool enabled, काष्ठा ia_css_pipe *curr_pipe) अणु
	bool status = false;

	अगर ((curr_pipe) && enabled) अणु
		अगर ((curr_pipe->config.mode == IA_CSS_PIPE_MODE_PREVIEW) ||
		    (curr_pipe->config.mode == IA_CSS_PIPE_MODE_VIDEO) ||
		    (curr_pipe->config.mode == IA_CSS_PIPE_MODE_CAPTURE))
			status = true;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक
aspect_ratio_crop(काष्ठा ia_css_pipe *curr_pipe,
		    काष्ठा ia_css_resolution *effective_res) अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_resolution crop_res;
	काष्ठा ia_css_resolution *in_res = शून्य;
	काष्ठा ia_css_resolution *out_res = शून्य;
	bool use_bds_output_info = false;
	bool use_vf_pp_in_res = false;
	bool use_capt_pp_in_res = false;

	अगर ((!curr_pipe) ||
	    (!effective_res))
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

	अगर ((curr_pipe->config.mode != IA_CSS_PIPE_MODE_PREVIEW) &&
	    (curr_pipe->config.mode != IA_CSS_PIPE_MODE_VIDEO) &&
	    (curr_pipe->config.mode != IA_CSS_PIPE_MODE_CAPTURE))
	अणु
		err = -EINVAL;
		IA_CSS_LEAVE_ERR(err);
		वापस err;
	पूर्ण

	use_bds_output_info =
	((curr_pipe->bds_output_info.res.width != 0) &&
	    (curr_pipe->bds_output_info.res.height != 0));

	use_vf_pp_in_res =
	((curr_pipe->config.vf_pp_in_res.width != 0) &&
	    (curr_pipe->config.vf_pp_in_res.height != 0));

	use_capt_pp_in_res =
	((curr_pipe->config.capt_pp_in_res.width != 0) &&
	    (curr_pipe->config.capt_pp_in_res.height != 0));

	in_res = &curr_pipe->stream->config.input_config.effective_res;
	out_res = &curr_pipe->output_info[0].res;

	चयन (curr_pipe->config.mode)
	अणु
	हाल IA_CSS_PIPE_MODE_PREVIEW:
		अगर (use_bds_output_info)
			out_res = &curr_pipe->bds_output_info.res;
		अन्यथा अगर (use_vf_pp_in_res)
			out_res = &curr_pipe->config.vf_pp_in_res;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_VIDEO:
		अगर (use_bds_output_info)
			out_res = &curr_pipe->bds_output_info.res;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_CAPTURE:
		अगर (use_capt_pp_in_res)
			out_res = &curr_pipe->config.capt_pp_in_res;
		अवरोध;
	हाल IA_CSS_PIPE_MODE_ACC:
	हाल IA_CSS_PIPE_MODE_COPY:
	हाल IA_CSS_PIPE_MODE_YUVPP:
	शेष:
		IA_CSS_ERROR("aspect ratio cropping invalid args: mode[%d]\n",
				curr_pipe->config.mode);
		निश्चित(0);
		अवरोध;
	पूर्ण

	err = ia_css_frame_find_crop_resolution(in_res, out_res, &crop_res);
	अगर (!err)
	अणु
		*effective_res = crop_res;
	पूर्ण अन्यथा
	अणु
		/* in हाल of error fallback to शेष
		    * effective resolution from driver. */
		IA_CSS_LOG("ia_css_frame_find_crop_resolution() failed with err(%d)", err);
	पूर्ण
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल व्योम
sh_css_hmm_buffer_record_init(व्योम) अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_HMM_BUFFER_NUM; i++)
		sh_css_hmm_buffer_record_reset(&hmm_buffer_record[i]);
पूर्ण

अटल व्योम
sh_css_hmm_buffer_record_uninit(व्योम) अणु
	पूर्णांक i;
	काष्ठा sh_css_hmm_buffer_record *buffer_record = शून्य;

	buffer_record = &hmm_buffer_record[0];
	क्रम (i = 0; i < MAX_HMM_BUFFER_NUM; i++) अणु
		अगर (buffer_record->in_use) अणु
			अगर (buffer_record->h_vbuf)
				ia_css_rmgr_rel_vbuf(hmm_buffer_pool, &buffer_record->h_vbuf);
			sh_css_hmm_buffer_record_reset(buffer_record);
		पूर्ण
		buffer_record++;
	पूर्ण
पूर्ण

अटल व्योम
sh_css_hmm_buffer_record_reset(काष्ठा sh_css_hmm_buffer_record *buffer_record) अणु
	निश्चित(buffer_record);
	buffer_record->in_use = false;
	buffer_record->type = IA_CSS_BUFFER_TYPE_INVALID;
	buffer_record->h_vbuf = शून्य;
	buffer_record->kernel_ptr = 0;
पूर्ण

अटल काष्ठा sh_css_hmm_buffer_record
*sh_css_hmm_buffer_record_acquire(काष्ठा ia_css_rmgr_vbuf_handle *h_vbuf,
				    क्रमागत ia_css_buffer_type type,
				    hrt_address kernel_ptr) अणु
	पूर्णांक i;
	काष्ठा sh_css_hmm_buffer_record *buffer_record = शून्य;
	काष्ठा sh_css_hmm_buffer_record *out_buffer_record = शून्य;

	निश्चित(h_vbuf);
	निश्चित((type > IA_CSS_BUFFER_TYPE_INVALID) &&
		(type < IA_CSS_NUM_DYNAMIC_BUFFER_TYPE));
	निश्चित(kernel_ptr != 0);

	buffer_record = &hmm_buffer_record[0];
	क्रम (i = 0; i < MAX_HMM_BUFFER_NUM; i++) अणु
		अगर (!buffer_record->in_use) अणु
			buffer_record->in_use = true;
			buffer_record->type = type;
			buffer_record->h_vbuf = h_vbuf;
			buffer_record->kernel_ptr = kernel_ptr;
			out_buffer_record = buffer_record;
			अवरोध;
		पूर्ण
		buffer_record++;
	पूर्ण

	वापस out_buffer_record;
पूर्ण

अटल काष्ठा sh_css_hmm_buffer_record
*sh_css_hmm_buffer_record_validate(ia_css_ptr ddr_buffer_addr,
				    क्रमागत ia_css_buffer_type type) अणु
	पूर्णांक i;
	काष्ठा sh_css_hmm_buffer_record *buffer_record = शून्य;
	bool found_record = false;

	buffer_record = &hmm_buffer_record[0];
	क्रम (i = 0; i < MAX_HMM_BUFFER_NUM; i++) अणु
		अगर ((buffer_record->in_use) &&
		    (buffer_record->type == type) &&
		    (buffer_record->h_vbuf) &&
		    (buffer_record->h_vbuf->vptr == ddr_buffer_addr)) अणु
			found_record = true;
			अवरोध;
		पूर्ण
		buffer_record++;
	पूर्ण

	अगर (found_record)
		वापस buffer_record;
	अन्यथा
		वापस शून्य;
पूर्ण
