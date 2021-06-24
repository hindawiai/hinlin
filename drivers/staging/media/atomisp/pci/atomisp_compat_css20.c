<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Clovertrail PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#समावेश <media/videobuf-vदो_स्मृति.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-event.h>

#समावेश "mmu/isp_mmu.h"
#समावेश "mmu/sh_mmu_mrfld.h"
#समावेश "hmm/hmm_bo.h"
#समावेश "hmm/hmm.h"

#समावेश "atomisp_compat.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_cmd.h"
#समावेश "atomisp-regs.h"
#समावेश "atomisp_fops.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp_acc.h"

#समावेश "ia_css_debug.h"
#समावेश "ia_css_isp_param.h"
#समावेश "sh_css_hrt.h"
#समावेश "ia_css_isys.h"

#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>

/* Assume max number of ACC stages */
#घोषणा MAX_ACC_STAGES	20

/* Ideally, this should come from CSS headers */
#घोषणा NO_LINK -1

/*
 * to serialize MMIO access , this is due to ISP2400 silicon issue Sighting
 * #4684168, अगर concurrency access happened, प्रणाली may hard hang.
 */
अटल DEFINE_SPINLOCK(mmio_lock);

क्रमागत frame_info_type अणु
	ATOMISP_CSS_VF_FRAME,
	ATOMISP_CSS_SECOND_VF_FRAME,
	ATOMISP_CSS_OUTPUT_FRAME,
	ATOMISP_CSS_SECOND_OUTPUT_FRAME,
	ATOMISP_CSS_RAW_FRAME,
पूर्ण;

काष्ठा bayer_ds_factor अणु
	अचिन्हित पूर्णांक numerator;
	अचिन्हित पूर्णांक denominator;
पूर्ण;

अटल व्योम atomisp_css2_hw_store_8(hrt_address addr, uपूर्णांक8_t data)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmio_lock, flags);
	ग_लिखोb(data, isp->base + (addr & 0x003FFFFF));
	spin_unlock_irqrestore(&mmio_lock, flags);
पूर्ण

अटल व्योम atomisp_css2_hw_store_16(hrt_address addr, uपूर्णांक16_t data)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmio_lock, flags);
	ग_लिखोw(data, isp->base + (addr & 0x003FFFFF));
	spin_unlock_irqrestore(&mmio_lock, flags);
पूर्ण

व्योम atomisp_css2_hw_store_32(hrt_address addr, uपूर्णांक32_t data)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmio_lock, flags);
	ग_लिखोl(data, isp->base + (addr & 0x003FFFFF));
	spin_unlock_irqrestore(&mmio_lock, flags);
पूर्ण

अटल uपूर्णांक8_t atomisp_css2_hw_load_8(hrt_address addr)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;
	u8 ret;

	spin_lock_irqsave(&mmio_lock, flags);
	ret = पढ़ोb(isp->base + (addr & 0x003FFFFF));
	spin_unlock_irqrestore(&mmio_lock, flags);
	वापस ret;
पूर्ण

अटल uपूर्णांक16_t atomisp_css2_hw_load_16(hrt_address addr)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;
	u16 ret;

	spin_lock_irqsave(&mmio_lock, flags);
	ret = पढ़ोw(isp->base + (addr & 0x003FFFFF));
	spin_unlock_irqrestore(&mmio_lock, flags);
	वापस ret;
पूर्ण

अटल uपूर्णांक32_t atomisp_css2_hw_load_32(hrt_address addr)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;
	u32 ret;

	spin_lock_irqsave(&mmio_lock, flags);
	ret = पढ़ोl(isp->base + (addr & 0x003FFFFF));
	spin_unlock_irqrestore(&mmio_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम atomisp_css2_hw_store(hrt_address addr, स्थिर व्योम *from, uपूर्णांक32_t n)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	addr &= 0x003FFFFF;
	spin_lock_irqsave(&mmio_lock, flags);
	क्रम (i = 0; i < n; i++, from++)
		ग_लिखोb(*(s8 *)from, isp->base + addr + i);

	spin_unlock_irqrestore(&mmio_lock, flags);
पूर्ण

अटल व्योम atomisp_css2_hw_load(hrt_address addr, व्योम *to, uपूर्णांक32_t n)
अणु
	काष्ठा atomisp_device *isp = dev_get_drvdata(atomisp_dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	addr &= 0x003FFFFF;
	spin_lock_irqsave(&mmio_lock, flags);
	क्रम (i = 0; i < n; i++, to++)
		*(s8 *)to = पढ़ोb(isp->base + addr + i);
	spin_unlock_irqrestore(&mmio_lock, flags);
पूर्ण

अटल पूर्णांक  __म_लिखो(1, 0) atomisp_css2_dbg_ftrace_prपूर्णांक(स्थिर अक्षर *fmt,
							 बहु_सूची args)
अणु
	ftrace_vprपूर्णांकk(fmt, args);
	वापस 0;
पूर्ण

अटल पूर्णांक  __म_लिखो(1, 0) atomisp_vprपूर्णांकk(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	vprपूर्णांकk(fmt, args);
	वापस 0;
पूर्ण

व्योम atomisp_load_uपूर्णांक32(hrt_address addr, uपूर्णांक32_t *data)
अणु
	*data = atomisp_css2_hw_load_32(addr);
पूर्ण

अटल पूर्णांक hmm_get_mmu_base_addr(काष्ठा device *dev, अचिन्हित पूर्णांक *mmu_base_addr)
अणु
	अगर (!sh_mmu_mrfld.get_pd_base) अणु
		dev_err(dev, "get mmu base address failed.\n");
		वापस -EINVAL;
	पूर्ण

	*mmu_base_addr = sh_mmu_mrfld.get_pd_base(&bo_device.mmu,
			 bo_device.mmu.base_address);
	वापस 0;
पूर्ण

अटल व्योम __dump_pipe_config(काष्ठा atomisp_sub_device *asd,
			       काष्ठा atomisp_stream_env *stream_env,
			       अचिन्हित पूर्णांक pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (stream_env->pipes[pipe_id]) अणु
		काष्ठा ia_css_pipe_config *p_config;
		काष्ठा ia_css_pipe_extra_config *pe_config;

		p_config = &stream_env->pipe_configs[pipe_id];
		pe_config = &stream_env->pipe_extra_configs[pipe_id];
		dev_dbg(isp->dev, "dumping pipe[%d] config:\n", pipe_id);
		dev_dbg(isp->dev,
			"pipe_config.pipe_mode:%d.\n", p_config->mode);
		dev_dbg(isp->dev,
			"pipe_config.output_info[0] w=%d, h=%d.\n",
			p_config->output_info[0].res.width,
			p_config->output_info[0].res.height);
		dev_dbg(isp->dev,
			"pipe_config.vf_pp_in_res w=%d, h=%d.\n",
			p_config->vf_pp_in_res.width,
			p_config->vf_pp_in_res.height);
		dev_dbg(isp->dev,
			"pipe_config.capt_pp_in_res w=%d, h=%d.\n",
			p_config->capt_pp_in_res.width,
			p_config->capt_pp_in_res.height);
		dev_dbg(isp->dev,
			"pipe_config.output.padded w=%d.\n",
			p_config->output_info[0].padded_width);
		dev_dbg(isp->dev,
			"pipe_config.vf_output_info[0] w=%d, h=%d.\n",
			p_config->vf_output_info[0].res.width,
			p_config->vf_output_info[0].res.height);
		dev_dbg(isp->dev,
			"pipe_config.bayer_ds_out_res w=%d, h=%d.\n",
			p_config->bayer_ds_out_res.width,
			p_config->bayer_ds_out_res.height);
		dev_dbg(isp->dev,
			"pipe_config.envelope w=%d, h=%d.\n",
			p_config->dvs_envelope.width,
			p_config->dvs_envelope.height);
		dev_dbg(isp->dev,
			"pipe_config.dvs_frame_delay=%d.\n",
			p_config->dvs_frame_delay);
		dev_dbg(isp->dev,
			"pipe_config.isp_pipe_version:%d.\n",
			p_config->isp_pipe_version);
		dev_dbg(isp->dev,
			"pipe_config.acc_extension=%p.\n",
			p_config->acc_extension);
		dev_dbg(isp->dev,
			"pipe_config.acc_stages=%p.\n",
			p_config->acc_stages);
		dev_dbg(isp->dev,
			"pipe_config.num_acc_stages=%d.\n",
			p_config->num_acc_stages);
		dev_dbg(isp->dev,
			"pipe_config.acc_num_execs=%d.\n",
			p_config->acc_num_execs);
		dev_dbg(isp->dev,
			"pipe_config.default_capture_config.capture_mode=%d.\n",
			p_config->शेष_capture_config.mode);
		dev_dbg(isp->dev,
			"pipe_config.enable_dz=%d.\n",
			p_config->enable_dz);
		dev_dbg(isp->dev,
			"pipe_config.default_capture_config.enable_xnr=%d.\n",
			p_config->शेष_capture_config.enable_xnr);
		dev_dbg(isp->dev,
			"dumping pipe[%d] extra config:\n", pipe_id);
		dev_dbg(isp->dev,
			"pipe_extra_config.enable_raw_binning:%d.\n",
			pe_config->enable_raw_binning);
		dev_dbg(isp->dev,
			"pipe_extra_config.enable_yuv_ds:%d.\n",
			pe_config->enable_yuv_ds);
		dev_dbg(isp->dev,
			"pipe_extra_config.enable_high_speed:%d.\n",
			pe_config->enable_high_speed);
		dev_dbg(isp->dev,
			"pipe_extra_config.enable_dvs_6axis:%d.\n",
			pe_config->enable_dvs_6axis);
		dev_dbg(isp->dev,
			"pipe_extra_config.enable_reduced_pipe:%d.\n",
			pe_config->enable_reduced_pipe);
		dev_dbg(isp->dev,
			"pipe_(extra_)config.enable_dz:%d.\n",
			p_config->enable_dz);
		dev_dbg(isp->dev,
			"pipe_extra_config.disable_vf_pp:%d.\n",
			pe_config->disable_vf_pp);
	पूर्ण
पूर्ण

अटल व्योम __dump_stream_config(काष्ठा atomisp_sub_device *asd,
				 काष्ठा atomisp_stream_env *stream_env)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा ia_css_stream_config *s_config;
	पूर्णांक j;
	bool valid_stream = false;

	क्रम (j = 0; j < IA_CSS_PIPE_ID_NUM; j++) अणु
		अगर (stream_env->pipes[j]) अणु
			__dump_pipe_config(asd, stream_env, j);
			valid_stream = true;
		पूर्ण
	पूर्ण
	अगर (!valid_stream)
		वापस;
	s_config = &stream_env->stream_config;
	dev_dbg(isp->dev, "stream_config.mode=%d.\n", s_config->mode);

	अगर (s_config->mode == IA_CSS_INPUT_MODE_SENSOR ||
	    s_config->mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR) अणु
		dev_dbg(isp->dev, "stream_config.source.port.port=%d.\n",
			s_config->source.port.port);
		dev_dbg(isp->dev, "stream_config.source.port.num_lanes=%d.\n",
			s_config->source.port.num_lanes);
		dev_dbg(isp->dev, "stream_config.source.port.timeout=%d.\n",
			s_config->source.port.समयout);
		dev_dbg(isp->dev, "stream_config.source.port.rxcount=0x%x.\n",
			s_config->source.port.rxcount);
		dev_dbg(isp->dev, "stream_config.source.port.compression.type=%d.\n",
			s_config->source.port.compression.type);
		dev_dbg(isp->dev,
			"stream_config.source.port.compression.compressed_bits_per_pixel=%d.\n",
			s_config->source.port.compression.
			compressed_bits_per_pixel);
		dev_dbg(isp->dev,
			"stream_config.source.port.compression.uncompressed_bits_per_pixel=%d.\n",
			s_config->source.port.compression.
			uncompressed_bits_per_pixel);
	पूर्ण अन्यथा अगर (s_config->mode == IA_CSS_INPUT_MODE_TPG) अणु
		dev_dbg(isp->dev, "stream_config.source.tpg.id=%d.\n",
			s_config->source.tpg.id);
		dev_dbg(isp->dev, "stream_config.source.tpg.mode=%d.\n",
			s_config->source.tpg.mode);
		dev_dbg(isp->dev, "stream_config.source.tpg.x_mask=%d.\n",
			s_config->source.tpg.x_mask);
		dev_dbg(isp->dev, "stream_config.source.tpg.x_delta=%d.\n",
			s_config->source.tpg.x_delta);
		dev_dbg(isp->dev, "stream_config.source.tpg.y_mask=%d.\n",
			s_config->source.tpg.y_mask);
		dev_dbg(isp->dev, "stream_config.source.tpg.y_delta=%d.\n",
			s_config->source.tpg.y_delta);
		dev_dbg(isp->dev, "stream_config.source.tpg.xy_mask=%d.\n",
			s_config->source.tpg.xy_mask);
	पूर्ण अन्यथा अगर (s_config->mode == IA_CSS_INPUT_MODE_PRBS) अणु
		dev_dbg(isp->dev, "stream_config.source.prbs.id=%d.\n",
			s_config->source.prbs.id);
		dev_dbg(isp->dev, "stream_config.source.prbs.h_blank=%d.\n",
			s_config->source.prbs.h_blank);
		dev_dbg(isp->dev, "stream_config.source.prbs.v_blank=%d.\n",
			s_config->source.prbs.v_blank);
		dev_dbg(isp->dev, "stream_config.source.prbs.seed=%d.\n",
			s_config->source.prbs.seed);
		dev_dbg(isp->dev, "stream_config.source.prbs.seed1=%d.\n",
			s_config->source.prbs.seed1);
	पूर्ण

	क्रम (j = 0; j < IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH; j++) अणु
		dev_dbg(isp->dev, "stream_configisys_config[%d].input_res w=%d, h=%d.\n",
			j,
			s_config->isys_config[j].input_res.width,
			s_config->isys_config[j].input_res.height);

		dev_dbg(isp->dev, "stream_configisys_config[%d].linked_isys_stream_id=%d\n",
			j,
			s_config->isys_config[j].linked_isys_stream_id);

		dev_dbg(isp->dev, "stream_configisys_config[%d].format=%d\n",
			j,
			s_config->isys_config[j].क्रमmat);

		dev_dbg(isp->dev, "stream_configisys_config[%d].valid=%d.\n",
			j,
			s_config->isys_config[j].valid);
	पूर्ण

	dev_dbg(isp->dev, "stream_config.input_config.input_res w=%d, h=%d.\n",
		s_config->input_config.input_res.width,
		s_config->input_config.input_res.height);

	dev_dbg(isp->dev, "stream_config.input_config.effective_res w=%d, h=%d.\n",
		s_config->input_config.effective_res.width,
		s_config->input_config.effective_res.height);

	dev_dbg(isp->dev, "stream_config.input_config.format=%d\n",
		s_config->input_config.क्रमmat);

	dev_dbg(isp->dev, "stream_config.input_config.bayer_order=%d.\n",
		s_config->input_config.bayer_order);

	dev_dbg(isp->dev, "stream_config.pixels_per_clock=%d.\n",
		s_config->pixels_per_घड़ी);
	dev_dbg(isp->dev, "stream_config.online=%d.\n", s_config->online);
	dev_dbg(isp->dev, "stream_config.continuous=%d.\n",
		s_config->continuous);
	dev_dbg(isp->dev, "stream_config.disable_cont_viewfinder=%d.\n",
		s_config->disable_cont_viewfinder);
	dev_dbg(isp->dev, "stream_config.channel_id=%d.\n",
		s_config->channel_id);
	dev_dbg(isp->dev, "stream_config.init_num_cont_raw_buf=%d.\n",
		s_config->init_num_cont_raw_buf);
	dev_dbg(isp->dev, "stream_config.target_num_cont_raw_buf=%d.\n",
		s_config->target_num_cont_raw_buf);
	dev_dbg(isp->dev, "stream_config.left_padding=%d.\n",
		s_config->left_padding);
	dev_dbg(isp->dev, "stream_config.sensor_binning_factor=%d.\n",
		s_config->sensor_binning_factor);
	dev_dbg(isp->dev, "stream_config.pixels_per_clock=%d.\n",
		s_config->pixels_per_घड़ी);
	dev_dbg(isp->dev, "stream_config.pack_raw_pixels=%d.\n",
		s_config->pack_raw_pixels);
	dev_dbg(isp->dev, "stream_config.flash_gpio_pin=%d.\n",
		s_config->flash_gpio_pin);
	dev_dbg(isp->dev, "stream_config.mipi_buffer_config.size_mem_words=%d.\n",
		s_config->mipi_buffer_config.size_mem_words);
	dev_dbg(isp->dev, "stream_config.mipi_buffer_config.contiguous=%d.\n",
		s_config->mipi_buffer_config.contiguous);
	dev_dbg(isp->dev, "stream_config.metadata_config.data_type=%d.\n",
		s_config->metadata_config.data_type);
	dev_dbg(isp->dev, "stream_config.metadata_config.resolution w=%d, h=%d.\n",
		s_config->metadata_config.resolution.width,
		s_config->metadata_config.resolution.height);
पूर्ण

अटल पूर्णांक __destroy_stream(काष्ठा atomisp_sub_device *asd,
			    काष्ठा atomisp_stream_env *stream_env, bool क्रमce)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक i;
	अचिन्हित दीर्घ समयout;

	अगर (!stream_env->stream)
		वापस 0;

	अगर (!क्रमce) अणु
		क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
			अगर (stream_env->update_pipe[i])
				अवरोध;

		अगर (i == IA_CSS_PIPE_ID_NUM)
			वापस 0;
	पूर्ण

	अगर (stream_env->stream_state == CSS_STREAM_STARTED
	    && ia_css_stream_stop(stream_env->stream) != 0) अणु
		dev_err(isp->dev, "stop stream failed.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (stream_env->stream_state == CSS_STREAM_STARTED) अणु
		समयout = jअगरfies + msecs_to_jअगरfies(40);
		जबतक (1) अणु
			अगर (ia_css_stream_has_stopped(stream_env->stream))
				अवरोध;

			अगर (समय_after(jअगरfies, समयout)) अणु
				dev_warn(isp->dev, "stop stream timeout.\n");
				अवरोध;
			पूर्ण

			usleep_range(100, 200);
		पूर्ण
	पूर्ण

	stream_env->stream_state = CSS_STREAM_STOPPED;

	अगर (ia_css_stream_destroy(stream_env->stream)) अणु
		dev_err(isp->dev, "destroy stream failed.\n");
		वापस -EINVAL;
	पूर्ण
	stream_env->stream_state = CSS_STREAM_UNINIT;
	stream_env->stream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक __destroy_streams(काष्ठा atomisp_sub_device *asd, bool क्रमce)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		ret = __destroy_stream(asd, &asd->stream_env[i], क्रमce);
		अगर (ret)
			वापस ret;
	पूर्ण
	asd->stream_prepared = false;
	वापस 0;
पूर्ण

अटल पूर्णांक __create_stream(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_stream_env *stream_env)
अणु
	पूर्णांक pipe_index = 0, i;
	काष्ठा ia_css_pipe *multi_pipes[IA_CSS_PIPE_ID_NUM];

	क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++) अणु
		अगर (stream_env->pipes[i])
			multi_pipes[pipe_index++] = stream_env->pipes[i];
	पूर्ण
	अगर (pipe_index == 0)
		वापस 0;

	stream_env->stream_config.target_num_cont_raw_buf =
	    asd->continuous_raw_buffer_size->val;
	stream_env->stream_config.channel_id = stream_env->ch_id;
	stream_env->stream_config.ia_css_enable_raw_buffer_locking =
	    asd->enable_raw_buffer_lock->val;

	__dump_stream_config(asd, stream_env);
	अगर (ia_css_stream_create(&stream_env->stream_config,
				 pipe_index, multi_pipes, &stream_env->stream) != 0)
		वापस -EINVAL;
	अगर (ia_css_stream_get_info(stream_env->stream,
				   &stream_env->stream_info) != 0) अणु
		ia_css_stream_destroy(stream_env->stream);
		stream_env->stream = शून्य;
		वापस -EINVAL;
	पूर्ण

	stream_env->stream_state = CSS_STREAM_CREATED;
	वापस 0;
पूर्ण

अटल पूर्णांक __create_streams(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		ret = __create_stream(asd, &asd->stream_env[i]);
		अगर (ret)
			जाओ rollback;
	पूर्ण
	asd->stream_prepared = true;
	वापस 0;
rollback:
	क्रम (i--; i >= 0; i--)
		__destroy_stream(asd, &asd->stream_env[i], true);
	वापस ret;
पूर्ण

अटल पूर्णांक __destroy_stream_pipes(काष्ठा atomisp_sub_device *asd,
				  काष्ठा atomisp_stream_env *stream_env,
				  bool क्रमce)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++) अणु
		अगर (!stream_env->pipes[i] ||
		    !(क्रमce || stream_env->update_pipe[i]))
			जारी;
		अगर (ia_css_pipe_destroy(stream_env->pipes[i])
		    != 0) अणु
			dev_err(isp->dev,
				"destroy pipe[%d]failed.cannot recover.\n", i);
			ret = -EINVAL;
		पूर्ण
		stream_env->pipes[i] = शून्य;
		stream_env->update_pipe[i] = false;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __destroy_pipes(काष्ठा atomisp_sub_device *asd, bool क्रमce)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		अगर (asd->stream_env[i].stream) अणु
			dev_err(isp->dev,
				"cannot destroy css pipes for stream[%d].\n",
				i);
			जारी;
		पूर्ण

		ret = __destroy_stream_pipes(asd, &asd->stream_env[i], क्रमce);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_destroy_pipes_stream_क्रमce(काष्ठा atomisp_sub_device *asd)
अणु
	__destroy_streams(asd, true);
	__destroy_pipes(asd, true);
पूर्ण

अटल व्योम __apply_additional_pipe_config(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा atomisp_stream_env *stream_env,
    क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (pipe_id < 0 || pipe_id >= IA_CSS_PIPE_ID_NUM) अणु
		dev_err(isp->dev,
			"wrong pipe_id for additional pipe config.\n");
		वापस;
	पूर्ण

	/* apply शेष pipe config */
	stream_env->pipe_configs[pipe_id].isp_pipe_version = 2;
	stream_env->pipe_configs[pipe_id].enable_dz =
	    asd->disable_dz->val ? false : true;
	/* apply isp 2.2 specअगरic config क्रम baytrail*/
	चयन (pipe_id) अणु
	हाल IA_CSS_PIPE_ID_CAPTURE:
		/* enable capture pp/dz manually or digital zoom would
		 * fail*/
		अगर (stream_env->pipe_configs[pipe_id].
		    शेष_capture_config.mode == IA_CSS_CAPTURE_MODE_RAW)
			stream_env->pipe_configs[pipe_id].enable_dz = false;

		अगर (IS_ISP2401) अणु
			/* the isp शेष to use ISP2.2 and the camera hal will
			* control whether use isp2.7 */
			अगर (asd->select_isp_version->val == ATOMISP_CSS_ISP_PIPE_VERSION_2_7)
				stream_env->pipe_configs[pipe_id].isp_pipe_version =  SH_CSS_ISP_PIPE_VERSION_2_7;
			अन्यथा
				stream_env->pipe_configs[pipe_id].isp_pipe_version = SH_CSS_ISP_PIPE_VERSION_2_2;
		पूर्ण
		अवरोध;
	हाल IA_CSS_PIPE_ID_VIDEO:
		/* enable reduced pipe to have binary
		 * video_dz_2_min selected*/
		stream_env->pipe_extra_configs[pipe_id]
		.enable_reduced_pipe = true;
		stream_env->pipe_configs[pipe_id]
		.enable_dz = false;
		अगर (ATOMISP_SOC_CAMERA(asd))
			stream_env->pipe_configs[pipe_id].enable_dz = true;

		अगर (asd->params.video_dis_en) अणु
			stream_env->pipe_extra_configs[pipe_id]
			.enable_dvs_6axis = true;
			stream_env->pipe_configs[pipe_id]
			.dvs_frame_delay =
			    ATOMISP_CSS2_NUM_DVS_FRAME_DELAY;
		पूर्ण
		अवरोध;
	हाल IA_CSS_PIPE_ID_PREVIEW:
		अवरोध;
	हाल IA_CSS_PIPE_ID_YUVPP:
	हाल IA_CSS_PIPE_ID_COPY:
		अगर (ATOMISP_SOC_CAMERA(asd))
			stream_env->pipe_configs[pipe_id].enable_dz = true;
		अन्यथा
			stream_env->pipe_configs[pipe_id].enable_dz = false;
		अवरोध;
	हाल IA_CSS_PIPE_ID_ACC:
		stream_env->pipe_configs[pipe_id].mode = IA_CSS_PIPE_MODE_ACC;
		stream_env->pipe_configs[pipe_id].enable_dz = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool is_pipe_valid_to_current_run_mode(काष्ठा atomisp_sub_device *asd,
	क्रमागत ia_css_pipe_id pipe_id)
अणु
	अगर (!asd)
		वापस false;

	अगर (pipe_id == IA_CSS_PIPE_ID_ACC || pipe_id == IA_CSS_PIPE_ID_YUVPP)
		वापस true;

	अगर (asd->vfpp) अणु
		अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER) अणु
			अगर (pipe_id == IA_CSS_PIPE_ID_VIDEO)
				वापस true;
			अन्यथा
				वापस false;
		पूर्ण अन्यथा अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT) अणु
			अगर (pipe_id == IA_CSS_PIPE_ID_CAPTURE)
				वापस true;
			अन्यथा
				वापस false;
		पूर्ण
	पूर्ण

	अगर (!asd->run_mode)
		वापस false;

	अगर (asd->copy_mode && pipe_id == IA_CSS_PIPE_ID_COPY)
		वापस true;

	चयन (asd->run_mode->val) अणु
	हाल ATOMISP_RUN_MODE_STILL_CAPTURE:
		अगर (pipe_id == IA_CSS_PIPE_ID_CAPTURE)
			वापस true;

		वापस false;
	हाल ATOMISP_RUN_MODE_PREVIEW:
		अगर (!asd->continuous_mode->val) अणु
			अगर (pipe_id == IA_CSS_PIPE_ID_PREVIEW)
				वापस true;

			वापस false;
		पूर्ण
		fallthrough;
	हाल ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE:
		अगर (pipe_id == IA_CSS_PIPE_ID_CAPTURE ||
		    pipe_id == IA_CSS_PIPE_ID_PREVIEW)
			वापस true;

		वापस false;
	हाल ATOMISP_RUN_MODE_VIDEO:
		अगर (!asd->continuous_mode->val) अणु
			अगर (pipe_id == IA_CSS_PIPE_ID_VIDEO ||
			    pipe_id == IA_CSS_PIPE_ID_YUVPP)
				वापस true;
			अन्यथा
				वापस false;
		पूर्ण
		fallthrough;
	हाल ATOMISP_RUN_MODE_SDV:
		अगर (pipe_id == IA_CSS_PIPE_ID_CAPTURE ||
		    pipe_id == IA_CSS_PIPE_ID_VIDEO)
			वापस true;

		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __create_pipe(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_stream_env *stream_env,
			 क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा ia_css_pipe_extra_config extra_config;
	पूर्णांक ret;

	अगर (pipe_id >= IA_CSS_PIPE_ID_NUM)
		वापस -EINVAL;

	अगर (pipe_id != IA_CSS_PIPE_ID_ACC &&
	    !stream_env->pipe_configs[pipe_id].output_info[0].res.width)
		वापस 0;

	अगर (pipe_id == IA_CSS_PIPE_ID_ACC &&
	    !stream_env->pipe_configs[pipe_id].acc_extension)
		वापस 0;

	अगर (!is_pipe_valid_to_current_run_mode(asd, pipe_id))
		वापस 0;

	ia_css_pipe_extra_config_शेषs(&extra_config);

	__apply_additional_pipe_config(asd, stream_env, pipe_id);
	अगर (!स_भेद(&extra_config,
		    &stream_env->pipe_extra_configs[pipe_id],
		    माप(extra_config)))
		ret = ia_css_pipe_create(
			  &stream_env->pipe_configs[pipe_id],
			  &stream_env->pipes[pipe_id]);
	अन्यथा
		ret = ia_css_pipe_create_extra(
			  &stream_env->pipe_configs[pipe_id],
			  &stream_env->pipe_extra_configs[pipe_id],
			  &stream_env->pipes[pipe_id]);
	अगर (ret)
		dev_err(isp->dev, "create pipe[%d] error.\n", pipe_id);
	वापस ret;
पूर्ण

अटल पूर्णांक __create_pipes(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक ret;
	पूर्णांक i, j;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		क्रम (j = 0; j < IA_CSS_PIPE_ID_NUM; j++) अणु
			ret = __create_pipe(asd, &asd->stream_env[i], j);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (j < IA_CSS_PIPE_ID_NUM)
			जाओ pipe_err;
	पूर्ण
	वापस 0;
pipe_err:
	क्रम (; i >= 0; i--) अणु
		क्रम (j--; j >= 0; j--) अणु
			अगर (asd->stream_env[i].pipes[j]) अणु
				ia_css_pipe_destroy(asd->stream_env[i].pipes[j]);
				asd->stream_env[i].pipes[j] = शून्य;
			पूर्ण
		पूर्ण
		j = IA_CSS_PIPE_ID_NUM;
	पूर्ण
	वापस -EINVAL;
पूर्ण

व्योम atomisp_create_pipes_stream(काष्ठा atomisp_sub_device *asd)
अणु
	__create_pipes(asd);
	__create_streams(asd);
पूर्ण

पूर्णांक atomisp_css_update_stream(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक ret;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (__destroy_streams(asd, true))
		dev_warn(isp->dev, "destroy stream failed.\n");

	अगर (__destroy_pipes(asd, true))
		dev_warn(isp->dev, "destroy pipe failed.\n");

	ret = __create_pipes(asd);
	अगर (ret) अणु
		dev_err(isp->dev, "create pipe failed %d.\n", ret);
		वापस -EIO;
	पूर्ण

	ret = __create_streams(asd);
	अगर (ret) अणु
		dev_warn(isp->dev, "create stream failed %d.\n", ret);
		__destroy_pipes(asd, true);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_init(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक mmu_base_addr;
	पूर्णांक ret;
	पूर्णांक err;

	ret = hmm_get_mmu_base_addr(isp->dev, &mmu_base_addr);
	अगर (ret)
		वापस ret;

	/* Init ISP */
	err = ia_css_init(isp->dev, &isp->css_env.isp_css_env, शून्य,
			  (uपूर्णांक32_t)mmu_base_addr, IA_CSS_IRQ_TYPE_PULSE);
	अगर (err) अणु
		dev_err(isp->dev, "css init failed --- bad firmware?\n");
		वापस -EINVAL;
	पूर्ण
	ia_css_enable_isys_event_queue(true);

	isp->css_initialized = true;
	dev_dbg(isp->dev, "sh_css_init success\n");

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __set_css_prपूर्णांक_env(काष्ठा atomisp_device *isp, पूर्णांक opt)
अणु
	पूर्णांक ret = 0;

	अगर (opt == 0)
		isp->css_env.isp_css_env.prपूर्णांक_env.debug_prपूर्णांक = शून्य;
	अन्यथा अगर (opt == 1)
		isp->css_env.isp_css_env.prपूर्णांक_env.debug_prपूर्णांक =
		    atomisp_css2_dbg_ftrace_prपूर्णांक;
	अन्यथा अगर (opt == 2)
		isp->css_env.isp_css_env.prपूर्णांक_env.debug_prपूर्णांक = atomisp_vprपूर्णांकk;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

पूर्णांक atomisp_css_load_firmware(काष्ठा atomisp_device *isp)
अणु
	पूर्णांक err;

	/* set css env */
	isp->css_env.isp_css_fw.data = (व्योम *)isp->firmware->data;
	isp->css_env.isp_css_fw.bytes = isp->firmware->size;

	isp->css_env.isp_css_env.hw_access_env.store_8 =
	    atomisp_css2_hw_store_8;
	isp->css_env.isp_css_env.hw_access_env.store_16 =
	    atomisp_css2_hw_store_16;
	isp->css_env.isp_css_env.hw_access_env.store_32 =
	    atomisp_css2_hw_store_32;

	isp->css_env.isp_css_env.hw_access_env.load_8 = atomisp_css2_hw_load_8;
	isp->css_env.isp_css_env.hw_access_env.load_16 =
	    atomisp_css2_hw_load_16;
	isp->css_env.isp_css_env.hw_access_env.load_32 =
	    atomisp_css2_hw_load_32;

	isp->css_env.isp_css_env.hw_access_env.load = atomisp_css2_hw_load;
	isp->css_env.isp_css_env.hw_access_env.store = atomisp_css2_hw_store;

	__set_css_prपूर्णांक_env(isp, dbg_func);

	isp->css_env.isp_css_env.prपूर्णांक_env.error_prपूर्णांक = atomisp_vprपूर्णांकk;

	/* load isp fw पूर्णांकo ISP memory */
	err = ia_css_load_firmware(isp->dev, &isp->css_env.isp_css_env,
				   &isp->css_env.isp_css_fw);
	अगर (err) अणु
		dev_err(isp->dev, "css load fw failed.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_css_uninit(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_sub_device *asd;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		स_रखो(&asd->params.config, 0, माप(asd->params.config));
		asd->params.css_update_params_needed = false;
	पूर्ण

	isp->css_initialized = false;
	ia_css_uninit();
पूर्ण

व्योम atomisp_css_suspend(काष्ठा atomisp_device *isp)
अणु
	isp->css_initialized = false;
	ia_css_uninit();
पूर्ण

पूर्णांक atomisp_css_resume(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक mmu_base_addr;
	पूर्णांक ret;

	ret = hmm_get_mmu_base_addr(isp->dev, &mmu_base_addr);
	अगर (ret) अणु
		dev_err(isp->dev, "get base address error.\n");
		वापस -EINVAL;
	पूर्ण

	ret = ia_css_init(isp->dev, &isp->css_env.isp_css_env, शून्य,
			  mmu_base_addr, IA_CSS_IRQ_TYPE_PULSE);
	अगर (ret) अणु
		dev_err(isp->dev, "re-init css failed.\n");
		वापस -EINVAL;
	पूर्ण
	ia_css_enable_isys_event_queue(true);

	isp->css_initialized = true;
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_irq_translate(काष्ठा atomisp_device *isp,
			      अचिन्हित पूर्णांक *infos)
अणु
	पूर्णांक err;

	err = ia_css_irq_translate(infos);
	अगर (err) अणु
		dev_warn(isp->dev,
			 "%s:failed to translate irq (err = %d,infos = %d)\n",
			 __func__, err, *infos);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_css_rx_get_irq_info(क्रमागत mipi_port_id port,
				 अचिन्हित पूर्णांक *infos)
अणु
#अगर_अघोषित ISP2401_NEW_INPUT_SYSTEM
	ia_css_isys_rx_get_irq_info(port, infos);
#अन्यथा
	*infos = 0;
#पूर्ण_अगर
पूर्ण

व्योम atomisp_css_rx_clear_irq_info(क्रमागत mipi_port_id port,
				   अचिन्हित पूर्णांक infos)
अणु
#अगर_अघोषित ISP2401_NEW_INPUT_SYSTEM
	ia_css_isys_rx_clear_irq_info(port, infos);
#पूर्ण_अगर
पूर्ण

पूर्णांक atomisp_css_irq_enable(काष्ठा atomisp_device *isp,
			   क्रमागत ia_css_irq_info info, bool enable)
अणु
	dev_dbg(isp->dev, "%s: css irq info 0x%08x: %s (%d).\n",
		__func__, info,
		enable ? "enable" : "disable", enable);
	अगर (ia_css_irq_enable(info, enable)) अणु
		dev_warn(isp->dev, "%s:Invalid irq info: 0x%08x when %s.\n",
			 __func__, info,
			 enable ? "enabling" : "disabling");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_css_init_काष्ठा(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		asd->stream_env[i].stream = शून्य;
		क्रम (j = 0; j < IA_CSS_PIPE_MODE_NUM; j++) अणु
			asd->stream_env[i].pipes[j] = शून्य;
			asd->stream_env[i].update_pipe[j] = false;
			ia_css_pipe_config_शेषs(
			    &asd->stream_env[i].pipe_configs[j]);
			ia_css_pipe_extra_config_शेषs(
			    &asd->stream_env[i].pipe_extra_configs[j]);
		पूर्ण
		ia_css_stream_config_शेषs(&asd->stream_env[i].stream_config);
	पूर्ण
पूर्ण

पूर्णांक atomisp_q_video_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				  काष्ठा videobuf_vदो_स्मृति_memory *vm_mem,
				  क्रमागत atomisp_input_stream_id stream_id,
				  क्रमागत ia_css_buffer_type css_buf_type,
				  क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_stream_env *stream_env = &asd->stream_env[stream_id];
	काष्ठा ia_css_buffer css_buf = अणु0पूर्ण;
	पूर्णांक err;

	css_buf.type = css_buf_type;
	css_buf.data.frame = vm_mem->vaddr;

	err = ia_css_pipe_enqueue_buffer(
		  stream_env->pipes[css_pipe_id], &css_buf);
	अगर (err)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक atomisp_q_metadata_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				     काष्ठा atomisp_metadata_buf *metadata_buf,
				     क्रमागत atomisp_input_stream_id stream_id,
				     क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_stream_env *stream_env = &asd->stream_env[stream_id];
	काष्ठा ia_css_buffer buffer = अणु0पूर्ण;
	काष्ठा atomisp_device *isp = asd->isp;

	buffer.type = IA_CSS_BUFFER_TYPE_METADATA;
	buffer.data.metadata = metadata_buf->metadata;
	अगर (ia_css_pipe_enqueue_buffer(stream_env->pipes[css_pipe_id],
				       &buffer)) अणु
		dev_err(isp->dev, "failed to q meta data buffer\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_q_s3a_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_s3a_buf *s3a_buf,
				क्रमागत atomisp_input_stream_id stream_id,
				क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_stream_env *stream_env = &asd->stream_env[stream_id];
	काष्ठा ia_css_buffer buffer = अणु0पूर्ण;
	काष्ठा atomisp_device *isp = asd->isp;

	buffer.type = IA_CSS_BUFFER_TYPE_3A_STATISTICS;
	buffer.data.stats_3a = s3a_buf->s3a_data;
	अगर (ia_css_pipe_enqueue_buffer(
		stream_env->pipes[css_pipe_id],
		&buffer)) अणु
		dev_dbg(isp->dev, "failed to q s3a stat buffer\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_q_dis_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_dis_buf *dis_buf,
				क्रमागत atomisp_input_stream_id stream_id,
				क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_stream_env *stream_env = &asd->stream_env[stream_id];
	काष्ठा ia_css_buffer buffer = अणु0पूर्ण;
	काष्ठा atomisp_device *isp = asd->isp;

	buffer.type = IA_CSS_BUFFER_TYPE_DIS_STATISTICS;
	buffer.data.stats_dvs = dis_buf->dis_data;
	अगर (ia_css_pipe_enqueue_buffer(
		stream_env->pipes[css_pipe_id],
		&buffer)) अणु
		dev_dbg(isp->dev, "failed to q dvs stat buffer\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_start(काष्ठा atomisp_sub_device *asd,
		      क्रमागत ia_css_pipe_id pipe_id, bool in_reset)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	bool sp_is_started = false;
	पूर्णांक ret = 0, i = 0;

	अगर (in_reset) अणु
		अगर (__destroy_streams(asd, true))
			dev_warn(isp->dev, "destroy stream failed.\n");

		अगर (__destroy_pipes(asd, true))
			dev_warn(isp->dev, "destroy pipe failed.\n");

		अगर (__create_pipes(asd)) अणु
			dev_err(isp->dev, "create pipe error.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (__create_streams(asd)) अणु
			dev_err(isp->dev, "create stream error.\n");
			ret = -EINVAL;
			जाओ stream_err;
		पूर्ण
		/* in_reset == true, extension firmwares are reloaded after the recovery */
		atomisp_acc_load_extensions(asd);
	पूर्ण

	/*
	 * For dual steam हाल, it is possible that:
	 * 1: क्रम this stream, it is at the stage that:
	 * - after set_fmt is called
	 * - beक्रमe stream on is called
	 * 2: क्रम the other stream, the stream off is called which css reset
	 * has been करोne.
	 *
	 * Thus the stream created in set_fmt get destroyed and need to be
	 * recreated in the next stream on.
	 */
	अगर (!asd->stream_prepared) अणु
		अगर (__create_pipes(asd)) अणु
			dev_err(isp->dev, "create pipe error.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (__create_streams(asd)) अणु
			dev_err(isp->dev, "create stream error.\n");
			ret = -EINVAL;
			जाओ stream_err;
		पूर्ण
	पूर्ण
	/*
	 * SP can only be started one समय
	 * अगर atomisp_subdev_streaming_count() tell there alपढ़ोy has some
	 * subdev at streamming, then SP should alपढ़ोy be started previously,
	 * so need to skip start sp procedure
	 */
	अगर (atomisp_streaming_count(isp)) अणु
		dev_dbg(isp->dev, "skip start sp\n");
	पूर्ण अन्यथा अणु
		अगर (!sh_css_hrt_प्रणाली_is_idle())
			dev_err(isp->dev, "CSS HW not idle before starting SP\n");
		अगर (ia_css_start_sp()) अणु
			dev_err(isp->dev, "start sp error.\n");
			ret = -EINVAL;
			जाओ start_err;
		पूर्ण अन्यथा अणु
			sp_is_started = true;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		अगर (asd->stream_env[i].stream) अणु
			अगर (ia_css_stream_start(asd->stream_env[i]
						.stream) != 0) अणु
				dev_err(isp->dev, "stream[%d] start error.\n", i);
				ret = -EINVAL;
				जाओ start_err;
			पूर्ण अन्यथा अणु
				asd->stream_env[i].stream_state = CSS_STREAM_STARTED;
				dev_dbg(isp->dev, "stream[%d] started.\n", i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

start_err:
	__destroy_streams(asd, true);
stream_err:
	__destroy_pipes(asd, true);

	/* css 2.0 API limitation: ia_css_stop_sp() could be only called after
	 * destroy all pipes
	 */
	/*
	 * SP can not be stop अगर other streams are in use
	 */
	अगर ((atomisp_streaming_count(isp) == 0) && sp_is_started)
		ia_css_stop_sp();

	वापस ret;
पूर्ण

व्योम atomisp_css_update_isp_params(काष्ठा atomisp_sub_device *asd)
अणु
	/*
	 * FIXME!
	 * क्रम ISP2401 new input प्रणाली, this api is under development.
	 * Calling it would cause kernel panic.
	 *
	 * VIED BZ: 1458
	 *
	 * Check अगर it is Cherry Trail and also new input प्रणाली
	 */
	अगर (asd->copy_mode) अणु
		dev_warn(asd->isp->dev,
			 "%s: ia_css_stream_set_isp_config() not supported in copy mode!.\n",
			 __func__);
		वापस;
	पूर्ण

	ia_css_stream_set_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &asd->params.config);
	स_रखो(&asd->params.config, 0, माप(asd->params.config));
पूर्ण

व्योम atomisp_css_update_isp_params_on_pipe(काष्ठा atomisp_sub_device *asd,
	काष्ठा ia_css_pipe *pipe)
अणु
	पूर्णांक ret;

	अगर (!pipe) अणु
		atomisp_css_update_isp_params(asd);
		वापस;
	पूर्ण

	dev_dbg(asd->isp->dev,
		"%s: apply parameter for ia_css_frame %p with isp_config_id %d on pipe %p.\n",
		__func__, asd->params.config.output_frame,
		asd->params.config.isp_config_id, pipe);

	ret = ia_css_stream_set_isp_config_on_pipe(
		  asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
		  &asd->params.config, pipe);
	अगर (ret)
		dev_warn(asd->isp->dev, "%s: ia_css_stream_set_isp_config_on_pipe failed %d\n",
			 __func__, ret);
	स_रखो(&asd->params.config, 0, माप(asd->params.config));
पूर्ण

पूर्णांक atomisp_css_queue_buffer(काष्ठा atomisp_sub_device *asd,
			     क्रमागत atomisp_input_stream_id stream_id,
			     क्रमागत ia_css_pipe_id pipe_id,
			     क्रमागत ia_css_buffer_type buf_type,
			     काष्ठा atomisp_css_buffer *isp_css_buffer)
अणु
	अगर (ia_css_pipe_enqueue_buffer(
		asd->stream_env[stream_id].pipes[pipe_id],
		&isp_css_buffer->css_buffer)
	    != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_dequeue_buffer(काष्ठा atomisp_sub_device *asd,
			       क्रमागत atomisp_input_stream_id stream_id,
			       क्रमागत ia_css_pipe_id pipe_id,
			       क्रमागत ia_css_buffer_type buf_type,
			       काष्ठा atomisp_css_buffer *isp_css_buffer)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक err;

	err = ia_css_pipe_dequeue_buffer(
		  asd->stream_env[stream_id].pipes[pipe_id],
		  &isp_css_buffer->css_buffer);
	अगर (err) अणु
		dev_err(isp->dev,
			"ia_css_pipe_dequeue_buffer failed: 0x%x\n", err);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_allocate_stat_buffers(काष्ठा atomisp_sub_device   *asd,
				      u16 stream_id,
				      काष्ठा atomisp_s3a_buf      *s3a_buf,
				      काष्ठा atomisp_dis_buf      *dis_buf,
				      काष्ठा atomisp_metadata_buf *md_buf)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा ia_css_dvs_grid_info *dvs_grid_info =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);

	अगर (s3a_buf && asd->params.curr_grid_info.s3a_grid.enable) अणु
		व्योम *s3a_ptr;

		s3a_buf->s3a_data = ia_css_isp_3a_statistics_allocate(
					&asd->params.curr_grid_info.s3a_grid);
		अगर (!s3a_buf->s3a_data) अणु
			dev_err(isp->dev, "3a buf allocation failed.\n");
			वापस -EINVAL;
		पूर्ण

		s3a_ptr = hmm_vmap(s3a_buf->s3a_data->data_ptr, true);
		s3a_buf->s3a_map = ia_css_isp_3a_statistics_map_allocate(
				       s3a_buf->s3a_data, s3a_ptr);
	पूर्ण

	अगर (dis_buf && dvs_grid_info && dvs_grid_info->enable) अणु
		व्योम *dvs_ptr;

		dis_buf->dis_data = ia_css_isp_dvs2_statistics_allocate(
					dvs_grid_info);
		अगर (!dis_buf->dis_data) अणु
			dev_err(isp->dev, "dvs buf allocation failed.\n");
			अगर (s3a_buf)
				ia_css_isp_3a_statistics_मुक्त(s3a_buf->s3a_data);
			वापस -EINVAL;
		पूर्ण

		dvs_ptr = hmm_vmap(dis_buf->dis_data->data_ptr, true);
		dis_buf->dvs_map = ia_css_isp_dvs_statistics_map_allocate(
				       dis_buf->dis_data, dvs_ptr);
	पूर्ण

	अगर (asd->stream_env[stream_id].stream_info.
	    metadata_info.size && md_buf) अणु
		md_buf->metadata = ia_css_metadata_allocate(
				       &asd->stream_env[stream_id].stream_info.metadata_info);
		अगर (!md_buf->metadata) अणु
			अगर (s3a_buf)
				ia_css_isp_3a_statistics_मुक्त(s3a_buf->s3a_data);
			अगर (dis_buf)
				ia_css_isp_dvs2_statistics_मुक्त(dis_buf->dis_data);
			dev_err(isp->dev, "metadata buf allocation failed.\n");
			वापस -EINVAL;
		पूर्ण
		md_buf->md_vptr = hmm_vmap(md_buf->metadata->address, false);
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_css_मुक्त_3a_buffer(काष्ठा atomisp_s3a_buf *s3a_buf)
अणु
	अगर (s3a_buf->s3a_data)
		hmm_vunmap(s3a_buf->s3a_data->data_ptr);

	ia_css_isp_3a_statistics_map_मुक्त(s3a_buf->s3a_map);
	s3a_buf->s3a_map = शून्य;
	ia_css_isp_3a_statistics_मुक्त(s3a_buf->s3a_data);
पूर्ण

व्योम atomisp_css_मुक्त_dis_buffer(काष्ठा atomisp_dis_buf *dis_buf)
अणु
	अगर (dis_buf->dis_data)
		hmm_vunmap(dis_buf->dis_data->data_ptr);

	ia_css_isp_dvs_statistics_map_मुक्त(dis_buf->dvs_map);
	dis_buf->dvs_map = शून्य;
	ia_css_isp_dvs2_statistics_मुक्त(dis_buf->dis_data);
पूर्ण

व्योम atomisp_css_मुक्त_metadata_buffer(काष्ठा atomisp_metadata_buf *metadata_buf)
अणु
	अगर (metadata_buf->md_vptr) अणु
		hmm_vunmap(metadata_buf->metadata->address);
		metadata_buf->md_vptr = शून्य;
	पूर्ण
	ia_css_metadata_मुक्त(metadata_buf->metadata);
पूर्ण

व्योम atomisp_css_मुक्त_stat_buffers(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_s3a_buf *s3a_buf, *_s3a_buf;
	काष्ठा atomisp_dis_buf *dis_buf, *_dis_buf;
	काष्ठा atomisp_metadata_buf *md_buf, *_md_buf;
	काष्ठा ia_css_dvs_grid_info *dvs_grid_info =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);
	अचिन्हित पूर्णांक i;

	/* 3A statistics use vदो_स्मृति, DIS use kदो_स्मृति */
	अगर (dvs_grid_info && dvs_grid_info->enable) अणु
		ia_css_dvs2_coefficients_मुक्त(asd->params.css_param.dvs2_coeff);
		ia_css_dvs2_statistics_मुक्त(asd->params.dvs_stat);
		asd->params.css_param.dvs2_coeff = शून्य;
		asd->params.dvs_stat = शून्य;
		asd->params.dvs_hor_proj_bytes = 0;
		asd->params.dvs_ver_proj_bytes = 0;
		asd->params.dvs_hor_coef_bytes = 0;
		asd->params.dvs_ver_coef_bytes = 0;
		asd->params.dis_proj_data_valid = false;
		list_क्रम_each_entry_safe(dis_buf, _dis_buf,
					 &asd->dis_stats, list) अणु
			atomisp_css_मुक्त_dis_buffer(dis_buf);
			list_del(&dis_buf->list);
			kमुक्त(dis_buf);
		पूर्ण
		list_क्रम_each_entry_safe(dis_buf, _dis_buf,
					 &asd->dis_stats_in_css, list) अणु
			atomisp_css_मुक्त_dis_buffer(dis_buf);
			list_del(&dis_buf->list);
			kमुक्त(dis_buf);
		पूर्ण
	पूर्ण
	अगर (asd->params.curr_grid_info.s3a_grid.enable) अणु
		ia_css_3a_statistics_मुक्त(asd->params.s3a_user_stat);
		asd->params.s3a_user_stat = शून्य;
		asd->params.s3a_output_bytes = 0;
		list_क्रम_each_entry_safe(s3a_buf, _s3a_buf,
					 &asd->s3a_stats, list) अणु
			atomisp_css_मुक्त_3a_buffer(s3a_buf);
			list_del(&s3a_buf->list);
			kमुक्त(s3a_buf);
		पूर्ण
		list_क्रम_each_entry_safe(s3a_buf, _s3a_buf,
					 &asd->s3a_stats_in_css, list) अणु
			atomisp_css_मुक्त_3a_buffer(s3a_buf);
			list_del(&s3a_buf->list);
			kमुक्त(s3a_buf);
		पूर्ण
		list_क्रम_each_entry_safe(s3a_buf, _s3a_buf,
					 &asd->s3a_stats_पढ़ोy, list) अणु
			atomisp_css_मुक्त_3a_buffer(s3a_buf);
			list_del(&s3a_buf->list);
			kमुक्त(s3a_buf);
		पूर्ण
	पूर्ण

	अगर (asd->params.css_param.dvs_6axis) अणु
		ia_css_dvs2_6axis_config_मुक्त(asd->params.css_param.dvs_6axis);
		asd->params.css_param.dvs_6axis = शून्य;
	पूर्ण

	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		list_क्रम_each_entry_safe(md_buf, _md_buf,
					 &asd->metadata[i], list) अणु
			atomisp_css_मुक्त_metadata_buffer(md_buf);
			list_del(&md_buf->list);
			kमुक्त(md_buf);
		पूर्ण
		list_क्रम_each_entry_safe(md_buf, _md_buf,
					 &asd->metadata_in_css[i], list) अणु
			atomisp_css_मुक्त_metadata_buffer(md_buf);
			list_del(&md_buf->list);
			kमुक्त(md_buf);
		पूर्ण
		list_क्रम_each_entry_safe(md_buf, _md_buf,
					 &asd->metadata_पढ़ोy[i], list) अणु
			atomisp_css_मुक्त_metadata_buffer(md_buf);
			list_del(&md_buf->list);
			kमुक्त(md_buf);
		पूर्ण
	पूर्ण
	asd->params.metadata_width_size = 0;
	atomisp_मुक्त_metadata_output_buf(asd);
पूर्ण

पूर्णांक atomisp_css_get_grid_info(काष्ठा atomisp_sub_device *asd,
			      क्रमागत ia_css_pipe_id pipe_id,
			      पूर्णांक source_pad)
अणु
	काष्ठा ia_css_pipe_info p_info;
	काष्ठा ia_css_grid_info old_info;
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक stream_index = atomisp_source_pad_to_stream_id(asd, source_pad);
	पूर्णांक md_width = asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].
		       stream_config.metadata_config.resolution.width;

	स_रखो(&p_info, 0, माप(काष्ठा ia_css_pipe_info));
	स_रखो(&old_info, 0, माप(काष्ठा ia_css_grid_info));

	अगर (ia_css_pipe_get_info(
		asd->stream_env[stream_index].pipes[pipe_id],
		&p_info) != 0) अणु
		dev_err(isp->dev, "ia_css_pipe_get_info failed\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(&old_info, &asd->params.curr_grid_info,
	       माप(काष्ठा ia_css_grid_info));
	स_नकल(&asd->params.curr_grid_info, &p_info.grid_info,
	       माप(काष्ठा ia_css_grid_info));
	/*
	 * Record which css pipe enables s3a_grid.
	 * Currently would have one css pipe that need it
	 */
	अगर (asd->params.curr_grid_info.s3a_grid.enable) अणु
		अगर (asd->params.s3a_enabled_pipe != IA_CSS_PIPE_ID_NUM)
			dev_dbg(isp->dev, "css pipe %d enabled s3a grid replaced by: %d.\n",
				asd->params.s3a_enabled_pipe, pipe_id);
		asd->params.s3a_enabled_pipe = pipe_id;
	पूर्ण

	/* If the grid info has not changed and the buffers क्रम 3A and
	 * DIS statistics buffers are allocated or buffer size would be zero
	 * then no need to करो anything. */
	अगर (((!स_भेद(&old_info, &asd->params.curr_grid_info, माप(old_info))
	      && asd->params.s3a_user_stat && asd->params.dvs_stat)
	     || asd->params.curr_grid_info.s3a_grid.width == 0
	     || asd->params.curr_grid_info.s3a_grid.height == 0)
	    && asd->params.metadata_width_size == md_width) अणु
		dev_dbg(isp->dev,
			"grid info change escape. memcmp=%d, s3a_user_stat=%d,dvs_stat=%d, s3a.width=%d, s3a.height=%d, metadata width =%d\n",
			!स_भेद(&old_info, &asd->params.curr_grid_info,
				माप(old_info)),
			!!asd->params.s3a_user_stat, !!asd->params.dvs_stat,
			asd->params.curr_grid_info.s3a_grid.width,
			asd->params.curr_grid_info.s3a_grid.height,
			asd->params.metadata_width_size);
		वापस -EINVAL;
	पूर्ण
	asd->params.metadata_width_size = md_width;

	वापस 0;
पूर्ण

पूर्णांक atomisp_alloc_3a_output_buf(काष्ठा atomisp_sub_device *asd)
अणु
	अगर (!asd->params.curr_grid_info.s3a_grid.width ||
	    !asd->params.curr_grid_info.s3a_grid.height)
		वापस 0;

	asd->params.s3a_user_stat = ia_css_3a_statistics_allocate(
					&asd->params.curr_grid_info.s3a_grid);
	अगर (!asd->params.s3a_user_stat)
		वापस -ENOMEM;
	/* 3A statistics. These can be big, so we use vदो_स्मृति. */
	asd->params.s3a_output_bytes =
	    asd->params.curr_grid_info.s3a_grid.width *
	    asd->params.curr_grid_info.s3a_grid.height *
	    माप(*asd->params.s3a_user_stat->data);

	वापस 0;
पूर्ण

पूर्णांक atomisp_alloc_dis_coef_buf(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा ia_css_dvs_grid_info *dvs_grid =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);

	अगर (!dvs_grid)
		वापस 0;

	अगर (!dvs_grid->enable) अणु
		dev_dbg(asd->isp->dev, "%s: dvs_grid not enabled.\n", __func__);
		वापस 0;
	पूर्ण

	/* DIS coefficients. */
	asd->params.css_param.dvs2_coeff = ia_css_dvs2_coefficients_allocate(
					       dvs_grid);
	अगर (!asd->params.css_param.dvs2_coeff)
		वापस -ENOMEM;

	asd->params.dvs_hor_coef_bytes = dvs_grid->num_hor_coefs *
					 माप(*asd->params.css_param.dvs2_coeff->hor_coefs.odd_real);

	asd->params.dvs_ver_coef_bytes = dvs_grid->num_ver_coefs *
					 माप(*asd->params.css_param.dvs2_coeff->ver_coefs.odd_real);

	/* DIS projections. */
	asd->params.dis_proj_data_valid = false;
	asd->params.dvs_stat = ia_css_dvs2_statistics_allocate(dvs_grid);
	अगर (!asd->params.dvs_stat)
		वापस -ENOMEM;

	asd->params.dvs_hor_proj_bytes =
	    dvs_grid->aligned_height * dvs_grid->aligned_width *
	    माप(*asd->params.dvs_stat->hor_prod.odd_real);

	asd->params.dvs_ver_proj_bytes =
	    dvs_grid->aligned_height * dvs_grid->aligned_width *
	    माप(*asd->params.dvs_stat->ver_prod.odd_real);

	वापस 0;
पूर्ण

पूर्णांक atomisp_alloc_metadata_output_buf(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक i;

	/* We allocate the cpu-side buffer used क्रम communication with user
	 * space */
	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		asd->params.metadata_user[i] = kvदो_स्मृति(
						   asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].
						   stream_info.metadata_info.size, GFP_KERNEL);
		अगर (!asd->params.metadata_user[i]) अणु
			जबतक (--i >= 0) अणु
				kvमुक्त(asd->params.metadata_user[i]);
				asd->params.metadata_user[i] = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_मुक्त_metadata_output_buf(काष्ठा atomisp_sub_device *asd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		अगर (asd->params.metadata_user[i]) अणु
			kvमुक्त(asd->params.metadata_user[i]);
			asd->params.metadata_user[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम atomisp_css_get_dis_statistics(काष्ठा atomisp_sub_device *asd,
				    काष्ठा atomisp_css_buffer *isp_css_buffer,
				    काष्ठा ia_css_isp_dvs_statistics_map *dvs_map)
अणु
	अगर (asd->params.dvs_stat) अणु
		अगर (dvs_map)
			ia_css_translate_dvs2_statistics(
			    asd->params.dvs_stat, dvs_map);
		अन्यथा
			ia_css_get_dvs2_statistics(asd->params.dvs_stat,
						   isp_css_buffer->css_buffer.data.stats_dvs);
	पूर्ण
पूर्ण

पूर्णांक atomisp_css_dequeue_event(काष्ठा atomisp_css_event *current_event)
अणु
	अगर (ia_css_dequeue_event(&current_event->event))
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम atomisp_css_temp_pipe_to_pipe_id(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_css_event *current_event)
अणु
	/*
	 * FIXME!
	 * Pipe ID reported in CSS event is not correct क्रम new प्रणाली's
	 * copy pipe.
	 * VIED BZ: 1463
	 */
	ia_css_temp_pipe_to_pipe_id(current_event->event.pipe,
				    &current_event->pipe);
	अगर (asd && asd->copy_mode &&
	    current_event->pipe == IA_CSS_PIPE_ID_CAPTURE)
		current_event->pipe = IA_CSS_PIPE_ID_COPY;
पूर्ण

पूर्णांक atomisp_css_isys_set_resolution(काष्ठा atomisp_sub_device *asd,
				    क्रमागत atomisp_input_stream_id stream_id,
				    काष्ठा v4l2_mbus_framefmt *ffmt,
				    पूर्णांक isys_stream)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	अगर (isys_stream >= IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH)
		वापस -EINVAL;

	s_config->isys_config[isys_stream].input_res.width = ffmt->width;
	s_config->isys_config[isys_stream].input_res.height = ffmt->height;
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_input_set_resolution(काष्ठा atomisp_sub_device *asd,
				     क्रमागत atomisp_input_stream_id stream_id,
				     काष्ठा v4l2_mbus_framefmt *ffmt)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->input_config.input_res.width = ffmt->width;
	s_config->input_config.input_res.height = ffmt->height;
	वापस 0;
पूर्ण

व्योम atomisp_css_input_set_binning_factor(काष्ठा atomisp_sub_device *asd,
	क्रमागत atomisp_input_stream_id stream_id,
	अचिन्हित पूर्णांक bin_factor)
अणु
	asd->stream_env[stream_id]
	.stream_config.sensor_binning_factor = bin_factor;
पूर्ण

व्योम atomisp_css_input_set_bayer_order(काष्ठा atomisp_sub_device *asd,
				       क्रमागत atomisp_input_stream_id stream_id,
				       क्रमागत ia_css_bayer_order bayer_order)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;
	s_config->input_config.bayer_order = bayer_order;
पूर्ण

व्योम atomisp_css_isys_set_link(काष्ठा atomisp_sub_device *asd,
			       क्रमागत atomisp_input_stream_id stream_id,
			       पूर्णांक link,
			       पूर्णांक isys_stream)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->isys_config[isys_stream].linked_isys_stream_id = link;
पूर्ण

व्योम atomisp_css_isys_set_valid(काष्ठा atomisp_sub_device *asd,
				क्रमागत atomisp_input_stream_id stream_id,
				bool valid,
				पूर्णांक isys_stream)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->isys_config[isys_stream].valid = valid;
पूर्ण

व्योम atomisp_css_isys_set_क्रमmat(काष्ठा atomisp_sub_device *asd,
				 क्रमागत atomisp_input_stream_id stream_id,
				 क्रमागत atomisp_input_क्रमmat क्रमmat,
				 पूर्णांक isys_stream)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->isys_config[isys_stream].क्रमmat = क्रमmat;
पूर्ण

व्योम atomisp_css_input_set_क्रमmat(काष्ठा atomisp_sub_device *asd,
				  क्रमागत atomisp_input_stream_id stream_id,
				  क्रमागत atomisp_input_क्रमmat क्रमmat)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->input_config.क्रमmat = क्रमmat;
पूर्ण

पूर्णांक atomisp_css_set_शेष_isys_config(काष्ठा atomisp_sub_device *asd,
					क्रमागत atomisp_input_stream_id stream_id,
					काष्ठा v4l2_mbus_framefmt *ffmt)
अणु
	पूर्णांक i;
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;
	/*
	 * Set all isys configs to not valid.
	 * Currently we support only one stream per channel
	 */
	क्रम (i = IA_CSS_STREAM_ISYS_STREAM_0;
	     i < IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH; i++)
		s_config->isys_config[i].valid = false;

	atomisp_css_isys_set_resolution(asd, stream_id, ffmt,
					IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX);
	atomisp_css_isys_set_क्रमmat(asd, stream_id,
				    s_config->input_config.क्रमmat,
				    IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX);
	atomisp_css_isys_set_link(asd, stream_id, NO_LINK,
				  IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX);
	atomisp_css_isys_set_valid(asd, stream_id, true,
				   IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX);

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_isys_two_stream_cfg(काष्ठा atomisp_sub_device *asd,
				    क्रमागत atomisp_input_stream_id stream_id,
				    क्रमागत atomisp_input_क्रमmat input_क्रमmat)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].input_res.width =
	    s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].input_res.width;

	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].input_res.height =
	    s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].input_res.height / 2;

	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].linked_isys_stream_id
	    = IA_CSS_STREAM_ISYS_STREAM_0;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].क्रमmat =
	    ATOMISP_INPUT_FORMAT_USER_DEF1;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].क्रमmat =
	    ATOMISP_INPUT_FORMAT_USER_DEF2;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].valid = true;
	वापस 0;
पूर्ण

व्योम atomisp_css_isys_two_stream_cfg_update_stream1(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].input_res.width =
	    width;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].input_res.height =
	    height;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].क्रमmat =
	    input_क्रमmat;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_0].valid = true;
पूर्ण

व्योम atomisp_css_isys_two_stream_cfg_update_stream2(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;

	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].input_res.width =
	    width;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].input_res.height =
	    height;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].linked_isys_stream_id
	    = IA_CSS_STREAM_ISYS_STREAM_0;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].क्रमmat =
	    input_क्रमmat;
	s_config->isys_config[IA_CSS_STREAM_ISYS_STREAM_1].valid = true;
पूर्ण

पूर्णांक atomisp_css_input_set_effective_resolution(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा ia_css_stream_config *s_config =
		    &asd->stream_env[stream_id].stream_config;
	s_config->input_config.effective_res.width = width;
	s_config->input_config.effective_res.height = height;
	वापस 0;
पूर्ण

व्योम atomisp_css_video_set_dis_envelope(काष्ठा atomisp_sub_device *asd,
					अचिन्हित पूर्णांक dvs_w, अचिन्हित पूर्णांक dvs_h)
अणु
	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.pipe_configs[IA_CSS_PIPE_ID_VIDEO].dvs_envelope.width = dvs_w;
	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.pipe_configs[IA_CSS_PIPE_ID_VIDEO].dvs_envelope.height = dvs_h;
पूर्ण

व्योम atomisp_css_input_set_two_pixels_per_घड़ी(
    काष्ठा atomisp_sub_device *asd,
    bool two_ppc)
अणु
	पूर्णांक i;

	अगर (asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	    .stream_config.pixels_per_घड़ी == (two_ppc ? 2 : 1))
		वापस;

	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.stream_config.pixels_per_घड़ी = (two_ppc ? 2 : 1);
	क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
		asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		.update_pipe[i] = true;
पूर्ण

व्योम atomisp_css_enable_raw_binning(काष्ठा atomisp_sub_device *asd,
				    bool enable)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	अचिन्हित पूर्णांक pipe;

	अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
		pipe = IA_CSS_PIPE_ID_VIDEO;
	अन्यथा
		pipe = IA_CSS_PIPE_ID_PREVIEW;

	stream_env->pipe_extra_configs[pipe].enable_raw_binning = enable;
	stream_env->update_pipe[pipe] = true;
	अगर (enable)
		stream_env->pipe_configs[pipe].output_info[0].padded_width =
		    stream_env->stream_config.input_config.effective_res.width;
पूर्ण

व्योम atomisp_css_enable_dz(काष्ठा atomisp_sub_device *asd, bool enable)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
		asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		.pipe_configs[i].enable_dz = enable;
पूर्ण

व्योम atomisp_css_capture_set_mode(काष्ठा atomisp_sub_device *asd,
				  क्रमागत ia_css_capture_mode mode)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];

	अगर (stream_env->pipe_configs[IA_CSS_PIPE_ID_CAPTURE]
	    .शेष_capture_config.mode == mode)
		वापस;

	stream_env->pipe_configs[IA_CSS_PIPE_ID_CAPTURE].
	शेष_capture_config.mode = mode;
	stream_env->update_pipe[IA_CSS_PIPE_ID_CAPTURE] = true;
पूर्ण

व्योम atomisp_css_input_set_mode(काष्ठा atomisp_sub_device *asd,
				क्रमागत ia_css_input_mode mode)
अणु
	पूर्णांक i;
	काष्ठा atomisp_device *isp = asd->isp;
	अचिन्हित पूर्णांक size_mem_words;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++)
		asd->stream_env[i].stream_config.mode = mode;

	अगर (isp->inमाला_दो[asd->input_curr].type == TEST_PATTERN) अणु
		काष्ठा ia_css_stream_config *s_config =
			    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream_config;
		s_config->mode = IA_CSS_INPUT_MODE_TPG;
		s_config->source.tpg.mode = IA_CSS_TPG_MODE_CHECKERBOARD;
		s_config->source.tpg.x_mask = (1 << 4) - 1;
		s_config->source.tpg.x_delta = -2;
		s_config->source.tpg.y_mask = (1 << 4) - 1;
		s_config->source.tpg.y_delta = 3;
		s_config->source.tpg.xy_mask = (1 << 8) - 1;
		वापस;
	पूर्ण

	अगर (mode != IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
		वापस;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		/*
		 * TODO: sensor needs to export the embedded_data_size_words
		 * inक्रमmation to atomisp क्रम each setting.
		 * Here using a large safe value.
		 */
		काष्ठा ia_css_stream_config *s_config =
			    &asd->stream_env[i].stream_config;

		अगर (s_config->input_config.input_res.width == 0)
			जारी;

		अगर (ia_css_mipi_frame_calculate_size(
			s_config->input_config.input_res.width,
			s_config->input_config.input_res.height,
			s_config->input_config.क्रमmat,
			true,
			0x13000,
			&size_mem_words) != 0) अणु
			अगर (IS_MRFD)
				size_mem_words = CSS_MIPI_FRAME_BUFFER_SIZE_2;
			अन्यथा
				size_mem_words = CSS_MIPI_FRAME_BUFFER_SIZE_1;
			dev_warn(asd->isp->dev,
				 "ia_css_mipi_frame_calculate_size failed,applying pre-defined MIPI buffer size %u.\n",
				 size_mem_words);
		पूर्ण
		s_config->mipi_buffer_config.size_mem_words = size_mem_words;
		s_config->mipi_buffer_config.nof_mipi_buffers = 2;
	पूर्ण
पूर्ण

व्योम atomisp_css_capture_enable_online(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित लघु stream_index, bool enable)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[stream_index];

	अगर (stream_env->stream_config.online == !!enable)
		वापस;

	stream_env->stream_config.online = !!enable;
	stream_env->update_pipe[IA_CSS_PIPE_ID_CAPTURE] = true;
पूर्ण

व्योम atomisp_css_preview_enable_online(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित लघु stream_index, bool enable)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[stream_index];
	पूर्णांक i;

	अगर (stream_env->stream_config.online != !!enable) अणु
		stream_env->stream_config.online = !!enable;
		क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
			stream_env->update_pipe[i] = true;
	पूर्ण
पूर्ण

व्योम atomisp_css_video_enable_online(काष्ठा atomisp_sub_device *asd,
				     bool enable)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_VIDEO];
	पूर्णांक i;

	अगर (stream_env->stream_config.online != enable) अणु
		stream_env->stream_config.online = enable;
		क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
			stream_env->update_pipe[i] = true;
	पूर्ण
पूर्ण

व्योम atomisp_css_enable_continuous(काष्ठा atomisp_sub_device *asd,
				   bool enable)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	पूर्णांक i;

	/*
	 * To SOC camera, there is only one YUVPP pipe in any हाल
	 * including ZSL/SDV/continuous viewfinder, so always set
	 * stream_config.continuous to 0.
	 */
	अगर (ATOMISP_USE_YUVPP(asd)) अणु
		stream_env->stream_config.continuous = 0;
		stream_env->stream_config.online = 1;
		वापस;
	पूर्ण

	अगर (stream_env->stream_config.continuous != !!enable) अणु
		stream_env->stream_config.continuous = !!enable;
		stream_env->stream_config.pack_raw_pixels = true;
		क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
			stream_env->update_pipe[i] = true;
	पूर्ण
पूर्ण

व्योम atomisp_css_enable_cvf(काष्ठा atomisp_sub_device *asd,
			    bool enable)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	पूर्णांक i;

	अगर (stream_env->stream_config.disable_cont_viewfinder != !enable) अणु
		stream_env->stream_config.disable_cont_viewfinder = !enable;
		क्रम (i = 0; i < IA_CSS_PIPE_ID_NUM; i++)
			stream_env->update_pipe[i] = true;
	पूर्ण
पूर्ण

पूर्णांक atomisp_css_input_configure_port(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत mipi_port_id port,
    अचिन्हित पूर्णांक num_lanes,
    अचिन्हित पूर्णांक समयout,
    अचिन्हित पूर्णांक mipi_freq,
    क्रमागत atomisp_input_क्रमmat metadata_क्रमmat,
    अचिन्हित पूर्णांक metadata_width,
    अचिन्हित पूर्णांक metadata_height)
अणु
	पूर्णांक i;
	काष्ठा atomisp_stream_env *stream_env;
	/*
	 * Calculate rx_count as follows:
	 * Input: mipi_freq                 : CSI-2 bus frequency in Hz
	 * UI = 1 / (2 * mipi_freq)         : period of one bit on the bus
	 * min = 85e-9 + 6 * UI             : Limits क्रम rx_count in seconds
	 * max = 145e-9 + 10 * UI
	 * rxcount0 = min / (4 / mipi_freq) : convert seconds to byte घड़ीs
	 * rxcount = rxcount0 - 2           : adjust क्रम better results
	 * The क्रमmula below is simplअगरied version of the above with
	 * 10-bit fixed poपूर्णांकs क्रम improved accuracy.
	 */
	स्थिर अचिन्हित पूर्णांक rxcount =
	    min(((mipi_freq / 46000) - 1280) >> 10, 0xffU) * 0x01010101U;

	क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
		stream_env = &asd->stream_env[i];
		stream_env->stream_config.source.port.port = port;
		stream_env->stream_config.source.port.num_lanes = num_lanes;
		stream_env->stream_config.source.port.समयout = समयout;
		अगर (mipi_freq)
			stream_env->stream_config.source.port.rxcount = rxcount;
		stream_env->stream_config.
		metadata_config.data_type = metadata_क्रमmat;
		stream_env->stream_config.
		metadata_config.resolution.width = metadata_width;
		stream_env->stream_config.
		metadata_config.resolution.height = metadata_height;
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_css_stop(काष्ठा atomisp_sub_device *asd,
		      क्रमागत ia_css_pipe_id pipe_id, bool in_reset)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_s3a_buf *s3a_buf;
	काष्ठा atomisp_dis_buf *dis_buf;
	काष्ठा atomisp_metadata_buf *md_buf;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक i;

	/* अगर is called in atomisp_reset(), क्रमce destroy stream */
	अगर (__destroy_streams(asd, true))
		dev_err(isp->dev, "destroy stream failed.\n");

	/* अगर is called in atomisp_reset(), क्रमce destroy all pipes */
	अगर (__destroy_pipes(asd, true))
		dev_err(isp->dev, "destroy pipes failed.\n");

	atomisp_init_raw_buffer_biपंचांगap(asd);

	/*
	 * SP can not be stop अगर other streams are in use
	 */
	अगर (atomisp_streaming_count(isp) == 0)
		ia_css_stop_sp();

	अगर (!in_reset) अणु
		काष्ठा atomisp_stream_env *stream_env;
		पूर्णांक i, j;

		क्रम (i = 0; i < ATOMISP_INPUT_STREAM_NUM; i++) अणु
			stream_env = &asd->stream_env[i];
			क्रम (j = 0; j < IA_CSS_PIPE_ID_NUM; j++) अणु
				ia_css_pipe_config_शेषs(
				    &stream_env->pipe_configs[j]);
				ia_css_pipe_extra_config_शेषs(
				    &stream_env->pipe_extra_configs[j]);
			पूर्ण
			ia_css_stream_config_शेषs(
			    &stream_env->stream_config);
		पूर्ण
		स_रखो(&asd->params.config, 0, माप(asd->params.config));
		asd->params.css_update_params_needed = false;
	पूर्ण

	/* move stats buffers to मुक्त queue list */
	जबतक (!list_empty(&asd->s3a_stats_in_css)) अणु
		s3a_buf = list_entry(asd->s3a_stats_in_css.next,
				     काष्ठा atomisp_s3a_buf, list);
		list_del(&s3a_buf->list);
		list_add_tail(&s3a_buf->list, &asd->s3a_stats);
	पूर्ण
	जबतक (!list_empty(&asd->s3a_stats_पढ़ोy)) अणु
		s3a_buf = list_entry(asd->s3a_stats_पढ़ोy.next,
				     काष्ठा atomisp_s3a_buf, list);
		list_del(&s3a_buf->list);
		list_add_tail(&s3a_buf->list, &asd->s3a_stats);
	पूर्ण

	spin_lock_irqsave(&asd->dis_stats_lock, irqflags);
	जबतक (!list_empty(&asd->dis_stats_in_css)) अणु
		dis_buf = list_entry(asd->dis_stats_in_css.next,
				     काष्ठा atomisp_dis_buf, list);
		list_del(&dis_buf->list);
		list_add_tail(&dis_buf->list, &asd->dis_stats);
	पूर्ण
	asd->params.dis_proj_data_valid = false;
	spin_unlock_irqrestore(&asd->dis_stats_lock, irqflags);

	क्रम (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) अणु
		जबतक (!list_empty(&asd->metadata_in_css[i])) अणु
			md_buf = list_entry(asd->metadata_in_css[i].next,
					    काष्ठा atomisp_metadata_buf, list);
			list_del(&md_buf->list);
			list_add_tail(&md_buf->list, &asd->metadata[i]);
		पूर्ण
		जबतक (!list_empty(&asd->metadata_पढ़ोy[i])) अणु
			md_buf = list_entry(asd->metadata_पढ़ोy[i].next,
					    काष्ठा atomisp_metadata_buf, list);
			list_del(&md_buf->list);
			list_add_tail(&md_buf->list, &asd->metadata[i]);
		पूर्ण
	पूर्ण

	atomisp_flush_params_queue(&asd->video_out_capture);
	atomisp_flush_params_queue(&asd->video_out_vf);
	atomisp_flush_params_queue(&asd->video_out_preview);
	atomisp_flush_params_queue(&asd->video_out_video_capture);
	atomisp_मुक्त_css_parameters(&asd->params.css_param);
	स_रखो(&asd->params.css_param, 0, माप(asd->params.css_param));
पूर्ण

व्योम atomisp_css_continuous_set_num_raw_frames(
     काष्ठा atomisp_sub_device *asd,
     पूर्णांक num_frames)
अणु
	अगर (asd->enable_raw_buffer_lock->val) अणु
		asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		.stream_config.init_num_cont_raw_buf =
		    ATOMISP_CSS2_NUM_OFFLINE_INIT_CONTINUOUS_FRAMES_LOCK_EN;
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
		    asd->params.video_dis_en)
			asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
			.stream_config.init_num_cont_raw_buf +=
			    ATOMISP_CSS2_NUM_DVS_FRAME_DELAY;
	पूर्ण अन्यथा अणु
		asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		.stream_config.init_num_cont_raw_buf =
		    ATOMISP_CSS2_NUM_OFFLINE_INIT_CONTINUOUS_FRAMES;
	पूर्ण

	अगर (asd->params.video_dis_en)
		asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		.stream_config.init_num_cont_raw_buf +=
		    ATOMISP_CSS2_NUM_DVS_FRAME_DELAY;

	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.stream_config.target_num_cont_raw_buf = num_frames;
पूर्ण

अटल क्रमागत ia_css_pipe_mode __pipe_id_to_pipe_mode(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा camera_mipi_info *mipi_info = atomisp_to_sensor_mipi_info(
		isp->inमाला_दो[asd->input_curr].camera);

	चयन (pipe_id) अणु
	हाल IA_CSS_PIPE_ID_COPY:
		/* Currently only YUVPP mode supports YUV420_Legacy क्रमmat.
		 * Revert this when other pipe modes can support
		 * YUV420_Legacy क्रमmat.
		 */
		अगर (mipi_info && mipi_info->input_क्रमmat ==
		    ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY)
			वापस IA_CSS_PIPE_MODE_YUVPP;
		वापस IA_CSS_PIPE_MODE_COPY;
	हाल IA_CSS_PIPE_ID_PREVIEW:
		वापस IA_CSS_PIPE_MODE_PREVIEW;
	हाल IA_CSS_PIPE_ID_CAPTURE:
		वापस IA_CSS_PIPE_MODE_CAPTURE;
	हाल IA_CSS_PIPE_ID_VIDEO:
		वापस IA_CSS_PIPE_MODE_VIDEO;
	हाल IA_CSS_PIPE_ID_ACC:
		वापस IA_CSS_PIPE_MODE_ACC;
	हाल IA_CSS_PIPE_ID_YUVPP:
		वापस IA_CSS_PIPE_MODE_YUVPP;
	शेष:
		WARN_ON(1);
		वापस IA_CSS_PIPE_MODE_PREVIEW;
	पूर्ण
पूर्ण

अटल व्योम __configure_output(काष्ठा atomisp_sub_device *asd,
			       अचिन्हित पूर्णांक stream_index,
			       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
			       अचिन्हित पूर्णांक min_width,
			       क्रमागत ia_css_frame_क्रमmat क्रमmat,
			       क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[stream_index];
	काष्ठा ia_css_stream_config *s_config = &stream_env->stream_config;

	stream_env->pipe_configs[pipe_id].mode =
	    __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	stream_env->pipe_configs[pipe_id].output_info[0].res.width = width;
	stream_env->pipe_configs[pipe_id].output_info[0].res.height = height;
	stream_env->pipe_configs[pipe_id].output_info[0].क्रमmat = क्रमmat;
	stream_env->pipe_configs[pipe_id].output_info[0].padded_width = min_width;

	/* isp binary 2.2 specअगरic setting*/
	अगर (width > s_config->input_config.effective_res.width ||
	    height > s_config->input_config.effective_res.height) अणु
		s_config->input_config.effective_res.width = width;
		s_config->input_config.effective_res.height = height;
	पूर्ण

	dev_dbg(isp->dev, "configuring pipe[%d] output info w=%d.h=%d.f=%d.\n",
		pipe_id, width, height, क्रमmat);
पूर्ण

अटल व्योम __configure_video_preview_output(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक stream_index,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	अचिन्हित पूर्णांक min_width,
	क्रमागत ia_css_frame_क्रमmat क्रमmat,
	क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[stream_index];
	काष्ठा ia_css_frame_info *css_output_info;
	काष्ठा ia_css_stream_config *stream_config = &stream_env->stream_config;

	stream_env->pipe_configs[pipe_id].mode =
	    __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	/*
	 * second_output will be as video मुख्य output in SDV mode
	 * with SOC camera. output will be as video मुख्य output in
	 * normal video mode.
	 */
	अगर (asd->continuous_mode->val)
		css_output_info = &stream_env->pipe_configs[pipe_id].
				  output_info[ATOMISP_CSS_OUTPUT_SECOND_INDEX];
	अन्यथा
		css_output_info = &stream_env->pipe_configs[pipe_id].
				  output_info[ATOMISP_CSS_OUTPUT_DEFAULT_INDEX];

	css_output_info->res.width = width;
	css_output_info->res.height = height;
	css_output_info->क्रमmat = क्रमmat;
	css_output_info->padded_width = min_width;

	/* isp binary 2.2 specअगरic setting*/
	अगर (width > stream_config->input_config.effective_res.width ||
	    height > stream_config->input_config.effective_res.height) अणु
		stream_config->input_config.effective_res.width = width;
		stream_config->input_config.effective_res.height = height;
	पूर्ण

	dev_dbg(isp->dev, "configuring pipe[%d] output info w=%d.h=%d.f=%d.\n",
		pipe_id, width, height, क्रमmat);
पूर्ण

/*
 * For CSS2.1, capture pipe uses capture_pp_in_res to configure yuv
 * करोwnscaling input resolution.
 */
अटल व्योम __configure_capture_pp_input(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	काष्ठा ia_css_stream_config *stream_config = &stream_env->stream_config;
	काष्ठा ia_css_pipe_config *pipe_configs =
		    &stream_env->pipe_configs[pipe_id];
	काष्ठा ia_css_pipe_extra_config *pipe_extra_configs =
		    &stream_env->pipe_extra_configs[pipe_id];
	अचिन्हित पूर्णांक hor_ds_factor = 0, ver_ds_factor = 0;

	अगर (width == 0 && height == 0)
		वापस;

	अगर (width * 9 / 10 < pipe_configs->output_info[0].res.width ||
	    height * 9 / 10 < pipe_configs->output_info[0].res.height)
		वापस;
	/* here just copy the calculation in css */
	hor_ds_factor = CEIL_DIV(width >> 1,
				 pipe_configs->output_info[0].res.width);
	ver_ds_factor = CEIL_DIV(height >> 1,
				 pipe_configs->output_info[0].res.height);

	अगर ((asd->isp->media_dev.hw_revision <
	     (ATOMISP_HW_REVISION_ISP2401 << ATOMISP_HW_REVISION_SHIFT) ||
	     IS_CHT) && hor_ds_factor != ver_ds_factor) अणु
		dev_warn(asd->isp->dev,
			 "Cropping for capture due to FW limitation");
		वापस;
	पूर्ण

	pipe_configs->mode = __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	pipe_extra_configs->enable_yuv_ds = true;

	pipe_configs->capt_pp_in_res.width =
	    stream_config->input_config.effective_res.width;
	pipe_configs->capt_pp_in_res.height =
	    stream_config->input_config.effective_res.height;

	dev_dbg(isp->dev, "configuring pipe[%d]capture pp input w=%d.h=%d.\n",
		pipe_id, width, height);
पूर्ण

/*
 * For CSS2.1, preview pipe could support bayer करोwnscaling, yuv decimation and
 * yuv करोwnscaling, which needs addtional configurations.
 */
अटल व्योम __configure_preview_pp_input(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक out_width, out_height, yuv_ds_in_width, yuv_ds_in_height;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	काष्ठा ia_css_stream_config *stream_config = &stream_env->stream_config;
	काष्ठा ia_css_pipe_config *pipe_configs =
		    &stream_env->pipe_configs[pipe_id];
	काष्ठा ia_css_pipe_extra_config *pipe_extra_configs =
		    &stream_env->pipe_extra_configs[pipe_id];
	काष्ठा ia_css_resolution *bayer_ds_out_res =
		    &pipe_configs->bayer_ds_out_res;
	काष्ठा ia_css_resolution *vf_pp_in_res =
		    &pipe_configs->vf_pp_in_res;
	काष्ठा ia_css_resolution  *effective_res =
		    &stream_config->input_config.effective_res;

	अटल स्थिर काष्ठा bayer_ds_factor bds_fct[] = अणुअणु2, 1पूर्ण, अणु3, 2पूर्ण, अणु5, 4पूर्ण पूर्ण;
	/*
	 * BZ201033: YUV decimation factor of 4 causes couple of righपंचांगost
	 * columns to be shaded. Remove this factor to work around the CSS bug.
	 * स्थिर अचिन्हित पूर्णांक yuv_dec_fct[] = अणु4, 2पूर्ण;
	 */
	अटल स्थिर अचिन्हित पूर्णांक yuv_dec_fct[] = अणु 2 पूर्ण;
	अचिन्हित पूर्णांक i;

	अगर (width == 0 && height == 0)
		वापस;

	pipe_configs->mode = __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	out_width = pipe_configs->output_info[0].res.width;
	out_height = pipe_configs->output_info[0].res.height;

	/*
	 * The ISP could करो bayer करोwnscaling, yuv decimation and yuv
	 * करोwnscaling:
	 * 1: Bayer Downscaling: between effective resolution and
	 * bayer_ds_res_out;
	 * 2: YUV Decimation: between bayer_ds_res_out and vf_pp_in_res;
	 * 3: YUV Downscaling: between vf_pp_in_res and final vf output
	 *
	 * Rule क्रम Bayer Downscaling: support factor 2, 1.5 and 1.25
	 * Rule क्रम YUV Decimation: support factor 2, 4
	 * Rule क्रम YUV Downscaling: arbitrary value below 2
	 *
	 * General rule of factor distribution among these stages:
	 * 1: try to करो Bayer करोwnscaling first अगर not in online mode.
	 * 2: try to करो maximum of 2 क्रम YUV करोwnscaling
	 * 3: the reमुख्यling क्रम YUV decimation
	 *
	 * Note:
	 * Do not configure bayer_ds_out_res अगर:
	 * online == 1 or continuous == 0 or raw_binning = 0
	 */
	अगर (stream_config->online || !stream_config->continuous ||
	    !pipe_extra_configs->enable_raw_binning) अणु
		bayer_ds_out_res->width = 0;
		bayer_ds_out_res->height = 0;
	पूर्ण अन्यथा अणु
		bayer_ds_out_res->width = effective_res->width;
		bayer_ds_out_res->height = effective_res->height;

		क्रम (i = 0; i < ARRAY_SIZE(bds_fct); i++) अणु
			अगर (effective_res->width >= out_width *
			    bds_fct[i].numerator / bds_fct[i].denominator &&
			    effective_res->height >= out_height *
			    bds_fct[i].numerator / bds_fct[i].denominator) अणु
				bayer_ds_out_res->width =
				    effective_res->width *
				    bds_fct[i].denominator /
				    bds_fct[i].numerator;
				bayer_ds_out_res->height =
				    effective_res->height *
				    bds_fct[i].denominator /
				    bds_fct[i].numerator;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * calculate YUV Decimation, YUV करोwnscaling facor:
	 * YUV Downscaling factor must not exceed 2.
	 * YUV Decimation factor could be 2, 4.
	 */
	/* first decide the yuv_ds input resolution */
	अगर (bayer_ds_out_res->width == 0) अणु
		yuv_ds_in_width = effective_res->width;
		yuv_ds_in_height = effective_res->height;
	पूर्ण अन्यथा अणु
		yuv_ds_in_width = bayer_ds_out_res->width;
		yuv_ds_in_height = bayer_ds_out_res->height;
	पूर्ण

	vf_pp_in_res->width = yuv_ds_in_width;
	vf_pp_in_res->height = yuv_ds_in_height;

	/* find out the yuv decimation factor */
	क्रम (i = 0; i < ARRAY_SIZE(yuv_dec_fct); i++) अणु
		अगर (yuv_ds_in_width >= out_width * yuv_dec_fct[i] &&
		    yuv_ds_in_height >= out_height * yuv_dec_fct[i]) अणु
			vf_pp_in_res->width = yuv_ds_in_width / yuv_dec_fct[i];
			vf_pp_in_res->height = yuv_ds_in_height / yuv_dec_fct[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (vf_pp_in_res->width == out_width &&
	    vf_pp_in_res->height == out_height) अणु
		pipe_extra_configs->enable_yuv_ds = false;
		vf_pp_in_res->width = 0;
		vf_pp_in_res->height = 0;
	पूर्ण अन्यथा अणु
		pipe_extra_configs->enable_yuv_ds = true;
	पूर्ण

	dev_dbg(isp->dev, "configuring pipe[%d]preview pp input w=%d.h=%d.\n",
		pipe_id, width, height);
पूर्ण

/*
 * For CSS2.1, offline video pipe could support bayer decimation, and
 * yuv करोwnscaling, which needs addtional configurations.
 */
अटल व्योम __configure_video_pp_input(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक out_width, out_height;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	काष्ठा ia_css_stream_config *stream_config = &stream_env->stream_config;
	काष्ठा ia_css_pipe_config *pipe_configs =
		    &stream_env->pipe_configs[pipe_id];
	काष्ठा ia_css_pipe_extra_config *pipe_extra_configs =
		    &stream_env->pipe_extra_configs[pipe_id];
	काष्ठा ia_css_resolution *bayer_ds_out_res =
		    &pipe_configs->bayer_ds_out_res;
	काष्ठा ia_css_resolution  *effective_res =
		    &stream_config->input_config.effective_res;

	अटल स्थिर काष्ठा bayer_ds_factor bds_factors[] = अणु
		अणु8, 1पूर्ण, अणु6, 1पूर्ण, अणु4, 1पूर्ण, अणु3, 1पूर्ण, अणु2, 1पूर्ण, अणु3, 2पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक i;

	अगर (width == 0 && height == 0)
		वापस;

	pipe_configs->mode = __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	pipe_extra_configs->enable_yuv_ds = false;

	/*
	 * If DVS is enabled,  video binary will take care the dvs envelope
	 * and usually the bayer_ds_out_res should be larger than 120% of
	 * destination resolution, the extra 20% will be cropped as DVS
	 * envelope. But,  अगर the bayer_ds_out_res is less than 120% of the
	 * destination. The ISP can still work,  but DVS quality is not good.
	 */
	/* taking at least 10% as envelope */
	अगर (asd->params.video_dis_en) अणु
		out_width = pipe_configs->output_info[0].res.width * 110 / 100;
		out_height = pipe_configs->output_info[0].res.height * 110 / 100;
	पूर्ण अन्यथा अणु
		out_width = pipe_configs->output_info[0].res.width;
		out_height = pipe_configs->output_info[0].res.height;
	पूर्ण

	/*
	 * calculate bayer decimate factor:
	 * 1: only 1.5, 2, 4 and 8 get supported
	 * 2: Do not configure bayer_ds_out_res अगर:
	 *    online == 1 or continuous == 0 or raw_binning = 0
	 */
	अगर (stream_config->online || !stream_config->continuous) अणु
		bayer_ds_out_res->width = 0;
		bayer_ds_out_res->height = 0;
		जाओ करोne;
	पूर्ण

	pipe_extra_configs->enable_raw_binning = true;
	bayer_ds_out_res->width = effective_res->width;
	bayer_ds_out_res->height = effective_res->height;

	क्रम (i = 0; i < माप(bds_factors) / माप(काष्ठा bayer_ds_factor);
	     i++) अणु
		अगर (effective_res->width >= out_width *
		    bds_factors[i].numerator / bds_factors[i].denominator &&
		    effective_res->height >= out_height *
		    bds_factors[i].numerator / bds_factors[i].denominator) अणु
			bayer_ds_out_res->width = effective_res->width *
						  bds_factors[i].denominator /
						  bds_factors[i].numerator;
			bayer_ds_out_res->height = effective_res->height *
						   bds_factors[i].denominator /
						   bds_factors[i].numerator;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * DVS is cropped from BDS output, so we करो not really need to set the
	 * envelope to 20% of output resolution here. always set it to 12x12
	 * per firmware requirement.
	 */
	pipe_configs->dvs_envelope.width = 12;
	pipe_configs->dvs_envelope.height = 12;

करोne:
	अगर (pipe_id == IA_CSS_PIPE_ID_YUVPP)
		stream_config->left_padding = -1;
	अन्यथा
		stream_config->left_padding = 12;
	dev_dbg(isp->dev, "configuring pipe[%d]video pp input w=%d.h=%d.\n",
		pipe_id, width, height);
पूर्ण

अटल व्योम __configure_vf_output(काष्ठा atomisp_sub_device *asd,
				  अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				  अचिन्हित पूर्णांक min_width,
				  क्रमागत ia_css_frame_क्रमmat क्रमmat,
				  क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	stream_env->pipe_configs[pipe_id].mode =
	    __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	stream_env->pipe_configs[pipe_id].vf_output_info[0].res.width = width;
	stream_env->pipe_configs[pipe_id].vf_output_info[0].res.height = height;
	stream_env->pipe_configs[pipe_id].vf_output_info[0].क्रमmat = क्रमmat;
	stream_env->pipe_configs[pipe_id].vf_output_info[0].padded_width =
	    min_width;
	dev_dbg(isp->dev,
		"configuring pipe[%d] vf output info w=%d.h=%d.f=%d.\n",
		pipe_id, width, height, क्रमmat);
पूर्ण

अटल व्योम __configure_video_vf_output(काष्ठा atomisp_sub_device *asd,
					अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
					अचिन्हित पूर्णांक min_width,
					क्रमागत ia_css_frame_क्रमmat क्रमmat,
					क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	काष्ठा ia_css_frame_info *css_output_info;

	stream_env->pipe_configs[pipe_id].mode =
	    __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	/*
	 * second_vf_output will be as video viewfinder in SDV mode
	 * with SOC camera. vf_output will be as video viewfinder in
	 * normal video mode.
	 */
	अगर (asd->continuous_mode->val)
		css_output_info = &stream_env->pipe_configs[pipe_id].
				  vf_output_info[ATOMISP_CSS_OUTPUT_SECOND_INDEX];
	अन्यथा
		css_output_info = &stream_env->pipe_configs[pipe_id].
				  vf_output_info[ATOMISP_CSS_OUTPUT_DEFAULT_INDEX];

	css_output_info->res.width = width;
	css_output_info->res.height = height;
	css_output_info->क्रमmat = क्रमmat;
	css_output_info->padded_width = min_width;
	dev_dbg(isp->dev,
		"configuring pipe[%d] vf output info w=%d.h=%d.f=%d.\n",
		pipe_id, width, height, क्रमmat);
पूर्ण

अटल पूर्णांक __get_frame_info(काष्ठा atomisp_sub_device *asd,
			    अचिन्हित पूर्णांक stream_index,
			    काष्ठा ia_css_frame_info *info,
			    क्रमागत frame_info_type type,
			    क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक ret;
	काष्ठा ia_css_pipe_info p_info;

	/* FIXME! No need to destroy/recreate all streams */
	अगर (__destroy_streams(asd, true))
		dev_warn(isp->dev, "destroy stream failed.\n");

	अगर (__destroy_pipes(asd, true))
		dev_warn(isp->dev, "destroy pipe failed.\n");

	अगर (__create_pipes(asd))
		वापस -EINVAL;

	अगर (__create_streams(asd))
		जाओ stream_err;

	ret = ia_css_pipe_get_info(
		  asd->stream_env[stream_index]
		  .pipes[pipe_id], &p_info);
	अगर (!ret) अणु
		चयन (type) अणु
		हाल ATOMISP_CSS_VF_FRAME:
			*info = p_info.vf_output_info[0];
			dev_dbg(isp->dev, "getting vf frame info.\n");
			अवरोध;
		हाल ATOMISP_CSS_SECOND_VF_FRAME:
			*info = p_info.vf_output_info[1];
			dev_dbg(isp->dev, "getting second vf frame info.\n");
			अवरोध;
		हाल ATOMISP_CSS_OUTPUT_FRAME:
			*info = p_info.output_info[0];
			dev_dbg(isp->dev, "getting main frame info.\n");
			अवरोध;
		हाल ATOMISP_CSS_SECOND_OUTPUT_FRAME:
			*info = p_info.output_info[1];
			dev_dbg(isp->dev, "getting second main frame info.\n");
			अवरोध;
		हाल ATOMISP_CSS_RAW_FRAME:
			*info = p_info.raw_output_info;
			dev_dbg(isp->dev, "getting raw frame info.\n");
		पूर्ण
		dev_dbg(isp->dev, "get frame info: w=%d, h=%d, num_invalid_frames %d.\n",
			info->res.width, info->res.height, p_info.num_invalid_frames);
		वापस 0;
	पूर्ण

stream_err:
	__destroy_pipes(asd, true);
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक atomisp_get_pipe_index(काष्ठा atomisp_sub_device *asd,
	uपूर्णांक16_t source_pad)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	/*
	 * to SOC camera, use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		वापस IA_CSS_PIPE_ID_YUVPP;

	चयन (source_pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VIDEO:
		अगर (asd->yuvpp_mode)
			वापस IA_CSS_PIPE_ID_YUVPP;
		अगर (asd->copy_mode)
			वापस IA_CSS_PIPE_ID_COPY;
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO
		    || asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER)
			वापस IA_CSS_PIPE_ID_VIDEO;

		वापस IA_CSS_PIPE_ID_CAPTURE;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE:
		अगर (asd->copy_mode)
			वापस IA_CSS_PIPE_ID_COPY;

		वापस IA_CSS_PIPE_ID_CAPTURE;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VF:
		अगर (!atomisp_is_mbuscode_raw(asd->fmt[asd->capture_pad].fmt.code)) अणु
			वापस IA_CSS_PIPE_ID_CAPTURE;
		पूर्ण
		fallthrough;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW:
		अगर (asd->yuvpp_mode)
			वापस IA_CSS_PIPE_ID_YUVPP;
		अगर (asd->copy_mode)
			वापस IA_CSS_PIPE_ID_COPY;
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO)
			वापस IA_CSS_PIPE_ID_VIDEO;

		वापस IA_CSS_PIPE_ID_PREVIEW;
	पूर्ण
	dev_warn(isp->dev,
		 "invalid source pad:%d, return default preview pipe index.\n",
		 source_pad);
	वापस IA_CSS_PIPE_ID_PREVIEW;
पूर्ण

पूर्णांक atomisp_get_css_frame_info(काष्ठा atomisp_sub_device *asd,
			       u16 source_pad,
			       काष्ठा ia_css_frame_info *frame_info)
अणु
	काष्ठा ia_css_pipe_info info;
	पूर्णांक pipe_index = atomisp_get_pipe_index(asd, source_pad);
	पूर्णांक stream_index;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (ATOMISP_SOC_CAMERA(asd))
		stream_index = atomisp_source_pad_to_stream_id(asd, source_pad);
	अन्यथा अणु
		stream_index = (pipe_index == IA_CSS_PIPE_ID_YUVPP) ?
			       ATOMISP_INPUT_STREAM_VIDEO :
			       atomisp_source_pad_to_stream_id(asd, source_pad);
	पूर्ण

	अगर (0 != ia_css_pipe_get_info(asd->stream_env[stream_index]
		.pipes[pipe_index], &info)) अणु
		dev_err(isp->dev, "ia_css_pipe_get_info FAILED");
		वापस -EINVAL;
	पूर्ण

	चयन (source_pad) अणु
	हाल ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE:
		*frame_info = info.output_info[0];
		अवरोध;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VIDEO:
		अगर (ATOMISP_USE_YUVPP(asd) && asd->continuous_mode->val)
			*frame_info = info.
				      output_info[ATOMISP_CSS_OUTPUT_SECOND_INDEX];
		अन्यथा
			*frame_info = info.
				      output_info[ATOMISP_CSS_OUTPUT_DEFAULT_INDEX];
		अवरोध;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_VF:
		अगर (stream_index == ATOMISP_INPUT_STREAM_POSTVIEW)
			*frame_info = info.output_info[0];
		अन्यथा
			*frame_info = info.vf_output_info[0];
		अवरोध;
	हाल ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW:
		अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO &&
		    (pipe_index == IA_CSS_PIPE_ID_VIDEO ||
		     pipe_index == IA_CSS_PIPE_ID_YUVPP))
			अगर (ATOMISP_USE_YUVPP(asd) && asd->continuous_mode->val)
				*frame_info = info.
					      vf_output_info[ATOMISP_CSS_OUTPUT_SECOND_INDEX];
			अन्यथा
				*frame_info = info.
					      vf_output_info[ATOMISP_CSS_OUTPUT_DEFAULT_INDEX];
		अन्यथा अगर (ATOMISP_USE_YUVPP(asd) && asd->continuous_mode->val)
			*frame_info =
			    info.output_info[ATOMISP_CSS_OUTPUT_SECOND_INDEX];
		अन्यथा
			*frame_info =
			    info.output_info[ATOMISP_CSS_OUTPUT_DEFAULT_INDEX];

		अवरोध;
	शेष:
		frame_info = शून्य;
		अवरोध;
	पूर्ण
	वापस frame_info ? 0 : -EINVAL;
पूर्ण

पूर्णांक atomisp_css_copy_configure_output(काष्ठा atomisp_sub_device *asd,
				      अचिन्हित पूर्णांक stream_index,
				      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				      अचिन्हित पूर्णांक padded_width,
				      क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	asd->stream_env[stream_index].pipe_configs[IA_CSS_PIPE_ID_COPY].
	शेष_capture_config.mode =
	    IA_CSS_CAPTURE_MODE_RAW;

	__configure_output(asd, stream_index, width, height, padded_width,
			   क्रमmat, IA_CSS_PIPE_ID_COPY);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_yuvpp_configure_output(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित पूर्णांक stream_index,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       अचिन्हित पूर्णांक padded_width,
				       क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	asd->stream_env[stream_index].pipe_configs[IA_CSS_PIPE_ID_YUVPP].
	शेष_capture_config.mode =
	    IA_CSS_CAPTURE_MODE_RAW;

	__configure_output(asd, stream_index, width, height, padded_width,
			   क्रमmat, IA_CSS_PIPE_ID_YUVPP);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_yuvpp_configure_viewfinder(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक min_width,
    क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[stream_index];
	क्रमागत ia_css_pipe_id pipe_id = IA_CSS_PIPE_ID_YUVPP;

	stream_env->pipe_configs[pipe_id].mode =
	    __pipe_id_to_pipe_mode(asd, pipe_id);
	stream_env->update_pipe[pipe_id] = true;

	stream_env->pipe_configs[pipe_id].vf_output_info[0].res.width = width;
	stream_env->pipe_configs[pipe_id].vf_output_info[0].res.height = height;
	stream_env->pipe_configs[pipe_id].vf_output_info[0].क्रमmat = क्रमmat;
	stream_env->pipe_configs[pipe_id].vf_output_info[0].padded_width =
	    min_width;
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_yuvpp_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    काष्ठा ia_css_frame_info *info)
अणु
	वापस __get_frame_info(asd, stream_index, info,
				ATOMISP_CSS_OUTPUT_FRAME, IA_CSS_PIPE_ID_YUVPP);
पूर्ण

पूर्णांक atomisp_css_yuvpp_get_viewfinder_frame_info(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    काष्ठा ia_css_frame_info *info)
अणु
	वापस __get_frame_info(asd, stream_index, info,
				ATOMISP_CSS_VF_FRAME, IA_CSS_PIPE_ID_YUVPP);
पूर्ण

पूर्णांक atomisp_css_preview_configure_output(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	अचिन्हित पूर्णांक min_width,
	क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	/*
	 * to SOC camera, use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		__configure_video_preview_output(asd, ATOMISP_INPUT_STREAM_GENERAL, width,
						 height,
						 min_width, क्रमmat, IA_CSS_PIPE_ID_YUVPP);
	अन्यथा
		__configure_output(asd, ATOMISP_INPUT_STREAM_GENERAL, width, height,
				   min_width, क्रमmat, IA_CSS_PIPE_ID_PREVIEW);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_capture_configure_output(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	अचिन्हित पूर्णांक min_width,
	क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	क्रमागत ia_css_pipe_id pipe_id;

	/*
	 * to SOC camera, use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
	अन्यथा
		pipe_id = IA_CSS_PIPE_ID_CAPTURE;

	__configure_output(asd, ATOMISP_INPUT_STREAM_GENERAL, width, height,
			   min_width, क्रमmat, pipe_id);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_video_configure_output(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       अचिन्हित पूर्णांक min_width,
				       क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	/*
	 * to SOC camera, use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		__configure_video_preview_output(asd, ATOMISP_INPUT_STREAM_GENERAL, width,
						 height,
						 min_width, क्रमmat, IA_CSS_PIPE_ID_YUVPP);
	अन्यथा
		__configure_output(asd, ATOMISP_INPUT_STREAM_GENERAL, width, height,
				   min_width, क्रमmat, IA_CSS_PIPE_ID_VIDEO);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_video_configure_viewfinder(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक min_width,
    क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	/*
	 * to SOC camera, video will use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		__configure_video_vf_output(asd, width, height, min_width, क्रमmat,
					    IA_CSS_PIPE_ID_YUVPP);
	अन्यथा
		__configure_vf_output(asd, width, height, min_width, क्रमmat,
				      IA_CSS_PIPE_ID_VIDEO);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_capture_configure_viewfinder(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक min_width,
    क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	क्रमागत ia_css_pipe_id pipe_id;

	/*
	 * to SOC camera, video will use yuvpp pipe.
	 */
	अगर (ATOMISP_USE_YUVPP(asd))
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
	अन्यथा
		pipe_id = IA_CSS_PIPE_ID_CAPTURE;

	__configure_vf_output(asd, width, height, min_width, क्रमmat,
			      pipe_id);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_video_get_viewfinder_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info)
अणु
	क्रमागत ia_css_pipe_id pipe_id;
	क्रमागत frame_info_type frame_type = ATOMISP_CSS_VF_FRAME;

	अगर (ATOMISP_USE_YUVPP(asd)) अणु
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
		अगर (asd->continuous_mode->val)
			frame_type = ATOMISP_CSS_SECOND_VF_FRAME;
	पूर्ण अन्यथा अणु
		pipe_id = IA_CSS_PIPE_ID_VIDEO;
	पूर्ण

	वापस __get_frame_info(asd, ATOMISP_INPUT_STREAM_GENERAL, info,
				frame_type, pipe_id);
पूर्ण

पूर्णांक atomisp_css_capture_get_viewfinder_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info)
अणु
	क्रमागत ia_css_pipe_id pipe_id;

	अगर (ATOMISP_USE_YUVPP(asd))
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
	अन्यथा
		pipe_id = IA_CSS_PIPE_ID_CAPTURE;

	वापस __get_frame_info(asd, ATOMISP_INPUT_STREAM_GENERAL, info,
				ATOMISP_CSS_VF_FRAME, pipe_id);
पूर्ण

पूर्णांक atomisp_css_capture_get_output_raw_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info)
अणु
	अगर (ATOMISP_USE_YUVPP(asd))
		वापस 0;

	वापस __get_frame_info(asd, ATOMISP_INPUT_STREAM_GENERAL, info,
				ATOMISP_CSS_RAW_FRAME, IA_CSS_PIPE_ID_CAPTURE);
पूर्ण

पूर्णांक atomisp_css_copy_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    काष्ठा ia_css_frame_info *info)
अणु
	वापस __get_frame_info(asd, stream_index, info,
				ATOMISP_CSS_OUTPUT_FRAME, IA_CSS_PIPE_ID_COPY);
पूर्ण

पूर्णांक atomisp_css_preview_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info)
अणु
	क्रमागत ia_css_pipe_id pipe_id;
	क्रमागत frame_info_type frame_type = ATOMISP_CSS_OUTPUT_FRAME;

	अगर (ATOMISP_USE_YUVPP(asd)) अणु
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
		अगर (asd->continuous_mode->val)
			frame_type = ATOMISP_CSS_SECOND_OUTPUT_FRAME;
	पूर्ण अन्यथा अणु
		pipe_id = IA_CSS_PIPE_ID_PREVIEW;
	पूर्ण

	वापस __get_frame_info(asd, ATOMISP_INPUT_STREAM_GENERAL, info,
				frame_type, pipe_id);
पूर्ण

पूर्णांक atomisp_css_capture_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info)
अणु
	क्रमागत ia_css_pipe_id pipe_id;

	अगर (ATOMISP_USE_YUVPP(asd))
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
	अन्यथा
		pipe_id = IA_CSS_PIPE_ID_CAPTURE;

	वापस __get_frame_info(asd, ATOMISP_INPUT_STREAM_GENERAL, info,
				ATOMISP_CSS_OUTPUT_FRAME, pipe_id);
पूर्ण

पूर्णांक atomisp_css_video_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info)
अणु
	क्रमागत ia_css_pipe_id pipe_id;
	क्रमागत frame_info_type frame_type = ATOMISP_CSS_OUTPUT_FRAME;

	अगर (ATOMISP_USE_YUVPP(asd)) अणु
		pipe_id = IA_CSS_PIPE_ID_YUVPP;
		अगर (asd->continuous_mode->val)
			frame_type = ATOMISP_CSS_SECOND_OUTPUT_FRAME;
	पूर्ण अन्यथा अणु
		pipe_id = IA_CSS_PIPE_ID_VIDEO;
	पूर्ण

	वापस __get_frame_info(asd, ATOMISP_INPUT_STREAM_GENERAL, info,
				frame_type, pipe_id);
पूर्ण

पूर्णांक atomisp_css_preview_configure_pp_input(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	__configure_preview_pp_input(asd, width, height,
				     ATOMISP_USE_YUVPP(asd) ?
				     IA_CSS_PIPE_ID_YUVPP : IA_CSS_PIPE_ID_PREVIEW);

	अगर (width > stream_env->pipe_configs[IA_CSS_PIPE_ID_CAPTURE].
	    capt_pp_in_res.width)
		__configure_capture_pp_input(asd, width, height,
					     ATOMISP_USE_YUVPP(asd) ?
					     IA_CSS_PIPE_ID_YUVPP : IA_CSS_PIPE_ID_CAPTURE);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_capture_configure_pp_input(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	__configure_capture_pp_input(asd, width, height,
				     ATOMISP_USE_YUVPP(asd) ?
				     IA_CSS_PIPE_ID_YUVPP : IA_CSS_PIPE_ID_CAPTURE);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_video_configure_pp_input(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];

	__configure_video_pp_input(asd, width, height,
				   ATOMISP_USE_YUVPP(asd) ?
				   IA_CSS_PIPE_ID_YUVPP : IA_CSS_PIPE_ID_VIDEO);

	अगर (width > stream_env->pipe_configs[IA_CSS_PIPE_ID_CAPTURE].
	    capt_pp_in_res.width)
		__configure_capture_pp_input(asd, width, height,
					     ATOMISP_USE_YUVPP(asd) ?
					     IA_CSS_PIPE_ID_YUVPP : IA_CSS_PIPE_ID_CAPTURE);
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_offline_capture_configure(काष्ठा atomisp_sub_device *asd,
	पूर्णांक num_captures, अचिन्हित पूर्णांक skip, पूर्णांक offset)
अणु
	पूर्णांक ret;

	dev_dbg(asd->isp->dev, "%s num_capture:%d skip:%d offset:%d\n",
		__func__, num_captures, skip, offset);

	ret = ia_css_stream_capture(
		  asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
		  num_captures, skip, offset);
	अगर (ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_exp_id_capture(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id)
अणु
	पूर्णांक ret;

	ret = ia_css_stream_capture_frame(
		  asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
		  exp_id);
	अगर (ret == -ENOBUFS) अणु
		/* capture cmd queue is full */
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (ret) अणु
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_exp_id_unlock(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id)
अणु
	पूर्णांक ret;

	ret = ia_css_unlock_raw_frame(
		  asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
		  exp_id);
	अगर (ret == -ENOBUFS)
		वापस -EAGAIN;
	अन्यथा अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_capture_enable_xnr(काष्ठा atomisp_sub_device *asd,
				   bool enable)
अणु
	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.pipe_configs[IA_CSS_PIPE_ID_CAPTURE]
	.शेष_capture_config.enable_xnr = enable;
	asd->params.capture_config.enable_xnr = enable;
	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.update_pipe[IA_CSS_PIPE_ID_CAPTURE] = true;

	वापस 0;
पूर्ण

व्योम atomisp_css_set_ctc_table(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_ctc_table *ctc_table)
अणु
	पूर्णांक i;
	u16 *vamem_ptr = ctc_table->data.vamem_1;
	पूर्णांक data_size = IA_CSS_VAMEM_1_CTC_TABLE_SIZE;
	bool valid = false;

	/* workaround: अगर ctc_table is all 0, करो not apply it */
	अगर (ctc_table->vamem_type == IA_CSS_VAMEM_TYPE_2) अणु
		vamem_ptr = ctc_table->data.vamem_2;
		data_size = IA_CSS_VAMEM_2_CTC_TABLE_SIZE;
	पूर्ण

	क्रम (i = 0; i < data_size; i++) अणु
		अगर (*(vamem_ptr + i)) अणु
			valid = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (valid)
		asd->params.config.ctc_table = ctc_table;
	अन्यथा
		dev_warn(asd->isp->dev, "Bypass the invalid ctc_table.\n");
पूर्ण

व्योम atomisp_css_set_anr_thres(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_anr_thres *anr_thres)
अणु
	asd->params.config.anr_thres = anr_thres;
पूर्ण

व्योम atomisp_css_set_dvs_6axis(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_dvs_6axis_config *dvs_6axis)
अणु
	asd->params.config.dvs_6axis_config = dvs_6axis;
पूर्ण

व्योम atomisp_css_video_set_dis_vector(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_dis_vector *vector)
अणु
	अगर (!asd->params.config.motion_vector)
		asd->params.config.motion_vector = &asd->params.css_param.motion_vector;

	स_रखो(asd->params.config.motion_vector,
	       0, माप(काष्ठा ia_css_vector));
	asd->params.css_param.motion_vector.x = vector->x;
	asd->params.css_param.motion_vector.y = vector->y;
पूर्ण

अटल पूर्णांक atomisp_compare_dvs_grid(काष्ठा atomisp_sub_device *asd,
				    काष्ठा atomisp_dvs_grid_info *atomgrid)
अणु
	काष्ठा ia_css_dvs_grid_info *cur =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);

	अगर (!cur) अणु
		dev_err(asd->isp->dev, "dvs grid not available!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (माप(*cur) != माप(*atomgrid)) अणु
		dev_err(asd->isp->dev, "dvs grid mis-match!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cur->enable) अणु
		dev_err(asd->isp->dev, "dvs not enabled!\n");
		वापस -EINVAL;
	पूर्ण

	वापस स_भेद(atomgrid, cur, माप(*cur));
पूर्ण

व्योम  atomisp_css_set_dvs2_coefs(काष्ठा atomisp_sub_device *asd,
				 काष्ठा ia_css_dvs2_coefficients *coefs)
अणु
	asd->params.config.dvs2_coefs = coefs;
पूर्ण

पूर्णांक atomisp_css_set_dis_coefs(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_dis_coefficients *coefs)
अणु
	अगर (atomisp_compare_dvs_grid(asd, &coefs->grid_info) != 0)
		/* If the grid info in the argument dअगरfers from the current
		   grid info, we tell the caller to reset the grid size and
		   try again. */
		वापस -EAGAIN;

	अगर (!coefs->hor_coefs.odd_real ||
	    !coefs->hor_coefs.odd_imag ||
	    !coefs->hor_coefs.even_real ||
	    !coefs->hor_coefs.even_imag ||
	    !coefs->ver_coefs.odd_real ||
	    !coefs->ver_coefs.odd_imag ||
	    !coefs->ver_coefs.even_real ||
	    !coefs->ver_coefs.even_imag ||
	    !asd->params.css_param.dvs2_coeff->hor_coefs.odd_real ||
	    !asd->params.css_param.dvs2_coeff->hor_coefs.odd_imag ||
	    !asd->params.css_param.dvs2_coeff->hor_coefs.even_real ||
	    !asd->params.css_param.dvs2_coeff->hor_coefs.even_imag ||
	    !asd->params.css_param.dvs2_coeff->ver_coefs.odd_real ||
	    !asd->params.css_param.dvs2_coeff->ver_coefs.odd_imag ||
	    !asd->params.css_param.dvs2_coeff->ver_coefs.even_real ||
	    !asd->params.css_param.dvs2_coeff->ver_coefs.even_imag)
		वापस -EINVAL;

	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->hor_coefs.odd_real,
			   coefs->hor_coefs.odd_real, asd->params.dvs_hor_coef_bytes))
		वापस -EFAULT;
	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->hor_coefs.odd_imag,
			   coefs->hor_coefs.odd_imag, asd->params.dvs_hor_coef_bytes))
		वापस -EFAULT;
	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->hor_coefs.even_real,
			   coefs->hor_coefs.even_real, asd->params.dvs_hor_coef_bytes))
		वापस -EFAULT;
	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->hor_coefs.even_imag,
			   coefs->hor_coefs.even_imag, asd->params.dvs_hor_coef_bytes))
		वापस -EFAULT;

	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->ver_coefs.odd_real,
			   coefs->ver_coefs.odd_real, asd->params.dvs_ver_coef_bytes))
		वापस -EFAULT;
	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->ver_coefs.odd_imag,
			   coefs->ver_coefs.odd_imag, asd->params.dvs_ver_coef_bytes))
		वापस -EFAULT;
	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->ver_coefs.even_real,
			   coefs->ver_coefs.even_real, asd->params.dvs_ver_coef_bytes))
		वापस -EFAULT;
	अगर (copy_from_user(asd->params.css_param.dvs2_coeff->ver_coefs.even_imag,
			   coefs->ver_coefs.even_imag, asd->params.dvs_ver_coef_bytes))
		वापस -EFAULT;

	asd->params.css_param.update_flag.dvs2_coefs =
		(काष्ठा atomisp_dis_coefficients *)
		asd->params.css_param.dvs2_coeff;
	/* FIXME! */
	/*	asd->params.dis_proj_data_valid = false; */
	asd->params.css_update_params_needed = true;

	वापस 0;
पूर्ण

व्योम atomisp_css_set_zoom_factor(काष्ठा atomisp_sub_device *asd,
				 अचिन्हित पूर्णांक zoom)
अणु
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (zoom == asd->params.css_param.dz_config.dx &&
	    zoom == asd->params.css_param.dz_config.dy) अणु
		dev_dbg(isp->dev, "same zoom scale. skipped.\n");
		वापस;
	पूर्ण

	स_रखो(&asd->params.css_param.dz_config, 0,
	       माप(काष्ठा ia_css_dz_config));
	asd->params.css_param.dz_config.dx = zoom;
	asd->params.css_param.dz_config.dy = zoom;

	asd->params.css_param.update_flag.dz_config =
	    (काष्ठा atomisp_dz_config *)&asd->params.css_param.dz_config;
	asd->params.css_update_params_needed = true;
पूर्ण

व्योम atomisp_css_set_क्रमmats_config(काष्ठा atomisp_sub_device *asd,
				    काष्ठा ia_css_क्रमmats_config *क्रमmats_config)
अणु
	asd->params.config.क्रमmats_config = क्रमmats_config;
पूर्ण

पूर्णांक atomisp_css_get_wb_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_wb_config *config)
अणु
	काष्ठा ia_css_wb_config wb_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&wb_config, 0, माप(काष्ठा ia_css_wb_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.wb_config = &wb_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &wb_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_ob_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_ob_config *config)
अणु
	काष्ठा ia_css_ob_config ob_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&ob_config, 0, माप(काष्ठा ia_css_ob_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.ob_config = &ob_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &ob_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_dp_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_dp_config *config)
अणु
	काष्ठा ia_css_dp_config dp_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&dp_config, 0, माप(काष्ठा ia_css_dp_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.dp_config = &dp_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &dp_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_de_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_de_config *config)
अणु
	काष्ठा ia_css_de_config de_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&de_config, 0, माप(काष्ठा ia_css_de_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.de_config = &de_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &de_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_nr_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_nr_config *config)
अणु
	काष्ठा ia_css_nr_config nr_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&nr_config, 0, माप(काष्ठा ia_css_nr_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));

	isp_config.nr_config = &nr_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &nr_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_ee_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_ee_config *config)
अणु
	काष्ठा ia_css_ee_config ee_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&ee_config, 0, माप(काष्ठा ia_css_ee_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.ee_config = &ee_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &ee_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_tnr_config(काष्ठा atomisp_sub_device *asd,
			       काष्ठा atomisp_tnr_config *config)
अणु
	काष्ठा ia_css_tnr_config tnr_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&tnr_config, 0, माप(काष्ठा ia_css_tnr_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.tnr_config = &tnr_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, &tnr_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_ctc_table(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_ctc_table *config)
अणु
	काष्ठा ia_css_ctc_table *tab;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	tab = vzalloc(माप(काष्ठा ia_css_ctc_table));
	अगर (!tab)
		वापस -ENOMEM;

	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.ctc_table = tab;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, tab, माप(*tab));
	vमुक्त(tab);

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_gamma_table(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_gamma_table *config)
अणु
	काष्ठा ia_css_gamma_table *tab;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	tab = vzalloc(माप(काष्ठा ia_css_gamma_table));
	अगर (!tab)
		वापस -ENOMEM;

	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.gamma_table = tab;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	स_नकल(config, tab, माप(*tab));
	vमुक्त(tab);

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_gc_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_gc_config *config)
अणु
	काष्ठा ia_css_gc_config gc_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&gc_config, 0, माप(काष्ठा ia_css_gc_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.gc_config = &gc_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	/* Get gamma correction params from current setup */
	स_नकल(config, &gc_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_3a_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_3a_config *config)
अणु
	काष्ठा ia_css_3a_config s3a_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&s3a_config, 0, माप(काष्ठा ia_css_3a_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.s3a_config = &s3a_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	/* Get white balance from current setup */
	स_नकल(config, &s3a_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_क्रमmats_config(काष्ठा atomisp_sub_device *asd,
				   काष्ठा atomisp_क्रमmats_config *config)
अणु
	काष्ठा ia_css_क्रमmats_config क्रमmats_config;
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&क्रमmats_config, 0, माप(क्रमmats_config));
	स_रखो(&isp_config, 0, माप(isp_config));
	isp_config.क्रमmats_config = &क्रमmats_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	/* Get narrow gamma from current setup */
	स_नकल(config, &क्रमmats_config, माप(*config));

	वापस 0;
पूर्ण

पूर्णांक atomisp_css_get_zoom_factor(काष्ठा atomisp_sub_device *asd,
				अचिन्हित पूर्णांक *zoom)
अणु
	काष्ठा ia_css_dz_config dz_config;  /** Digital Zoom */
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev, "%s called after streamoff, skipping.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	स_रखो(&dz_config, 0, माप(काष्ठा ia_css_dz_config));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.dz_config = &dz_config;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
	*zoom = dz_config.dx;

	वापस 0;
पूर्ण

/*
 * Function to set/get image stablization statistics
 */
पूर्णांक atomisp_css_get_dis_stat(काष्ठा atomisp_sub_device *asd,
			     काष्ठा atomisp_dis_statistics *stats)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_dis_buf *dis_buf;
	अचिन्हित दीर्घ flags;

	अगर (!asd->params.dvs_stat->hor_prod.odd_real ||
	    !asd->params.dvs_stat->hor_prod.odd_imag ||
	    !asd->params.dvs_stat->hor_prod.even_real ||
	    !asd->params.dvs_stat->hor_prod.even_imag ||
	    !asd->params.dvs_stat->ver_prod.odd_real ||
	    !asd->params.dvs_stat->ver_prod.odd_imag ||
	    !asd->params.dvs_stat->ver_prod.even_real ||
	    !asd->params.dvs_stat->ver_prod.even_imag)
		वापस -EINVAL;

	/* isp needs to be streaming to get DIS statistics */
	spin_lock_irqsave(&isp->lock, flags);
	अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED) अणु
		spin_unlock_irqrestore(&isp->lock, flags);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&isp->lock, flags);

	अगर (atomisp_compare_dvs_grid(asd, &stats->dvs2_stat.grid_info) != 0)
		/* If the grid info in the argument dअगरfers from the current
		   grid info, we tell the caller to reset the grid size and
		   try again. */
		वापस -EAGAIN;

	spin_lock_irqsave(&asd->dis_stats_lock, flags);
	अगर (!asd->params.dis_proj_data_valid || list_empty(&asd->dis_stats)) अणु
		spin_unlock_irqrestore(&asd->dis_stats_lock, flags);
		dev_err(isp->dev, "dis statistics is not valid.\n");
		वापस -EAGAIN;
	पूर्ण

	dis_buf = list_entry(asd->dis_stats.next,
			     काष्ठा atomisp_dis_buf, list);
	list_del_init(&dis_buf->list);
	spin_unlock_irqrestore(&asd->dis_stats_lock, flags);

	अगर (dis_buf->dvs_map)
		ia_css_translate_dvs2_statistics(
		    asd->params.dvs_stat, dis_buf->dvs_map);
	अन्यथा
		ia_css_get_dvs2_statistics(asd->params.dvs_stat,
					   dis_buf->dis_data);
	stats->exp_id = dis_buf->dis_data->exp_id;

	spin_lock_irqsave(&asd->dis_stats_lock, flags);
	list_add_tail(&dis_buf->list, &asd->dis_stats);
	spin_unlock_irqrestore(&asd->dis_stats_lock, flags);

	अगर (copy_to_user(stats->dvs2_stat.ver_prod.odd_real,
			 asd->params.dvs_stat->ver_prod.odd_real,
			 asd->params.dvs_ver_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_stat.ver_prod.odd_imag,
			 asd->params.dvs_stat->ver_prod.odd_imag,
			 asd->params.dvs_ver_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_stat.ver_prod.even_real,
			 asd->params.dvs_stat->ver_prod.even_real,
			 asd->params.dvs_ver_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_stat.ver_prod.even_imag,
			 asd->params.dvs_stat->ver_prod.even_imag,
			 asd->params.dvs_ver_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_स्थिति.सor_prod.odd_real,
			 asd->params.dvs_stat->hor_prod.odd_real,
			 asd->params.dvs_hor_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_स्थिति.सor_prod.odd_imag,
			 asd->params.dvs_stat->hor_prod.odd_imag,
			 asd->params.dvs_hor_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_स्थिति.सor_prod.even_real,
			 asd->params.dvs_stat->hor_prod.even_real,
			 asd->params.dvs_hor_proj_bytes))
		वापस -EFAULT;
	अगर (copy_to_user(stats->dvs2_स्थिति.सor_prod.even_imag,
			 asd->params.dvs_stat->hor_prod.even_imag,
			 asd->params.dvs_hor_proj_bytes))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा ia_css_shading_table *atomisp_css_shading_table_alloc(
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	वापस ia_css_shading_table_alloc(width, height);
पूर्ण

व्योम atomisp_css_set_shading_table(काष्ठा atomisp_sub_device *asd,
				   काष्ठा ia_css_shading_table *table)
अणु
	asd->params.config.shading_table = table;
पूर्ण

व्योम atomisp_css_shading_table_मुक्त(काष्ठा ia_css_shading_table *table)
अणु
	ia_css_shading_table_मुक्त(table);
पूर्ण

काष्ठा ia_css_morph_table *atomisp_css_morph_table_allocate(
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	वापस ia_css_morph_table_allocate(width, height);
पूर्ण

व्योम atomisp_css_set_morph_table(काष्ठा atomisp_sub_device *asd,
				 काष्ठा ia_css_morph_table *table)
अणु
	asd->params.config.morph_table = table;
पूर्ण

व्योम atomisp_css_get_morph_table(काष्ठा atomisp_sub_device *asd,
				 काष्ठा ia_css_morph_table *table)
अणु
	काष्ठा ia_css_isp_config isp_config;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (!asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream) अणु
		dev_err(isp->dev,
			"%s called after streamoff, skipping.\n", __func__);
		वापस;
	पूर्ण
	स_रखो(table, 0, माप(काष्ठा ia_css_morph_table));
	स_रखो(&isp_config, 0, माप(काष्ठा ia_css_isp_config));
	isp_config.morph_table = table;
	ia_css_stream_get_isp_config(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    &isp_config);
पूर्ण

व्योम atomisp_css_morph_table_मुक्त(काष्ठा ia_css_morph_table *table)
अणु
	ia_css_morph_table_मुक्त(table);
पूर्ण

व्योम atomisp_css_set_cont_prev_start_समय(काष्ठा atomisp_device *isp,
	अचिन्हित पूर्णांक overlap)
अणु
	/* CSS 2.0 करोesn't support this API. */
	dev_dbg(isp->dev, "set cont prev start time is not supported.\n");
	वापस;
पूर्ण

व्योम atomisp_css_acc_करोne(काष्ठा atomisp_sub_device *asd)
अणु
	complete(&asd->acc.acc_करोne);
पूर्ण

पूर्णांक atomisp_css_रुको_acc_finish(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक ret = 0;
	काष्ठा atomisp_device *isp = asd->isp;

	/* Unlock the isp mutex taken in IOCTL handler beक्रमe sleeping! */
	rt_mutex_unlock(&isp->mutex);
	अगर (रुको_क्रम_completion_पूर्णांकerruptible_समयout(&asd->acc.acc_करोne,
		ATOMISP_ISP_TIMEOUT_DURATION) == 0) अणु
		dev_err(isp->dev, "<%s: completion timeout\n", __func__);
		ia_css_debug_dump_sp_sw_debug_info();
		ia_css_debug_dump_debug_info(__func__);
		ret = -EIO;
	पूर्ण
	rt_mutex_lock(&isp->mutex);

	वापस ret;
पूर्ण

/* Set the ACC binary arguments */
पूर्णांक atomisp_css_set_acc_parameters(काष्ठा atomisp_acc_fw *acc_fw)
अणु
	अचिन्हित पूर्णांक mem;

	क्रम (mem = 0; mem < ATOMISP_ACC_NR_MEMORY; mem++) अणु
		अगर (acc_fw->args[mem].length == 0)
			जारी;

		ia_css_isp_param_set_css_mem_init(&acc_fw->fw->mem_initializers,
						  IA_CSS_PARAM_CLASS_PARAM, mem,
						  acc_fw->args[mem].css_ptr,
						  acc_fw->args[mem].length);
	पूर्ण

	वापस 0;
पूर्ण

/* Load acc binary extension */
पूर्णांक atomisp_css_load_acc_extension(काष्ठा atomisp_sub_device *asd,
				   काष्ठा ia_css_fw_info *fw,
				   क्रमागत ia_css_pipe_id pipe_id,
				   अचिन्हित पूर्णांक type)
अणु
	काष्ठा ia_css_fw_info **hd;

	fw->next = शून्य;
	hd = &(asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	       .pipe_configs[pipe_id].acc_extension);
	जबतक (*hd)
		hd = &(*hd)->next;
	*hd = fw;

	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.update_pipe[pipe_id] = true;
	वापस 0;
पूर्ण

/* Unload acc binary extension */
व्योम atomisp_css_unload_acc_extension(काष्ठा atomisp_sub_device *asd,
				      काष्ठा ia_css_fw_info *fw,
				      क्रमागत ia_css_pipe_id pipe_id)
अणु
	काष्ठा ia_css_fw_info **hd;

	hd = &(asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	       .pipe_configs[pipe_id].acc_extension);
	जबतक (*hd && *hd != fw)
		hd = &(*hd)->next;
	अगर (!*hd) अणु
		dev_err(asd->isp->dev, "did not find acc fw for removal\n");
		वापस;
	पूर्ण
	*hd = fw->next;
	fw->next = शून्य;

	asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
	.update_pipe[pipe_id] = true;
पूर्ण

पूर्णांक atomisp_css_create_acc_pipe(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा ia_css_pipe_config *pipe_config;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];

	अगर (stream_env->acc_stream) अणु
		अगर (stream_env->acc_stream_state == CSS_STREAM_STARTED) अणु
			अगर (ia_css_stream_stop(stream_env->acc_stream)
			    != 0) अणु
				dev_err(isp->dev, "stop acc_stream failed.\n");
				वापस -EBUSY;
			पूर्ण
		पूर्ण

		अगर (ia_css_stream_destroy(stream_env->acc_stream)
		    != 0) अणु
			dev_err(isp->dev, "destroy acc_stream failed.\n");
			वापस -EBUSY;
		पूर्ण
		stream_env->acc_stream = शून्य;
	पूर्ण

	pipe_config = &stream_env->pipe_configs[IA_CSS_PIPE_ID_ACC];
	ia_css_pipe_config_शेषs(pipe_config);
	asd->acc.acc_stages = kzalloc(MAX_ACC_STAGES *
				      माप(व्योम *), GFP_KERNEL);
	अगर (!asd->acc.acc_stages)
		वापस -ENOMEM;
	pipe_config->acc_stages = asd->acc.acc_stages;
	pipe_config->mode = IA_CSS_PIPE_MODE_ACC;
	pipe_config->num_acc_stages = 0;

	/*
	 * We delay the ACC pipeline creation to atomisp_css_start_acc_pipe,
	 * because pipe configuration will soon be changed by
	 * atomisp_css_load_acc_binary()
	 */
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_start_acc_pipe(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	काष्ठा ia_css_pipe_config *pipe_config =
		    &stream_env->pipe_configs[IA_CSS_PIPE_ID_ACC];

	अगर (ia_css_pipe_create(pipe_config,
			       &stream_env->pipes[IA_CSS_PIPE_ID_ACC]) != 0) अणु
		dev_err(isp->dev, "%s: ia_css_pipe_create failed\n",
			__func__);
		वापस -EBADE;
	पूर्ण

	स_रखो(&stream_env->acc_stream_config, 0,
	       माप(काष्ठा ia_css_stream_config));
	अगर (ia_css_stream_create(&stream_env->acc_stream_config, 1,
				 &stream_env->pipes[IA_CSS_PIPE_ID_ACC],
				 &stream_env->acc_stream) != 0) अणु
		dev_err(isp->dev, "%s: create acc_stream error.\n", __func__);
		वापस -EINVAL;
	पूर्ण
	stream_env->acc_stream_state = CSS_STREAM_CREATED;

	init_completion(&asd->acc.acc_करोne);
	asd->acc.pipeline = stream_env->pipes[IA_CSS_PIPE_ID_ACC];

	atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_MAX, false);

	अगर (ia_css_start_sp()) अणु
		dev_err(isp->dev, "start sp error.\n");
		वापस -EIO;
	पूर्ण

	अगर (ia_css_stream_start(stream_env->acc_stream)
	    != 0) अणु
		dev_err(isp->dev, "acc_stream start error.\n");
		वापस -EIO;
	पूर्ण

	stream_env->acc_stream_state = CSS_STREAM_STARTED;
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_stop_acc_pipe(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	अगर (stream_env->acc_stream_state == CSS_STREAM_STARTED) अणु
		ia_css_stream_stop(stream_env->acc_stream);
		stream_env->acc_stream_state = CSS_STREAM_STOPPED;
	पूर्ण
	वापस 0;
पूर्ण

व्योम atomisp_css_destroy_acc_pipe(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_stream_env *stream_env =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL];
	अगर (stream_env->acc_stream) अणु
		अगर (ia_css_stream_destroy(stream_env->acc_stream)
		    != 0)
			dev_warn(asd->isp->dev,
				 "destroy acc_stream failed.\n");
		stream_env->acc_stream = शून्य;
	पूर्ण

	अगर (stream_env->pipes[IA_CSS_PIPE_ID_ACC]) अणु
		अगर (ia_css_pipe_destroy(stream_env->pipes[IA_CSS_PIPE_ID_ACC])
		    != 0)
			dev_warn(asd->isp->dev,
				 "destroy ACC pipe failed.\n");
		stream_env->pipes[IA_CSS_PIPE_ID_ACC] = शून्य;
		stream_env->update_pipe[IA_CSS_PIPE_ID_ACC] = false;
		ia_css_pipe_config_शेषs(
		    &stream_env->pipe_configs[IA_CSS_PIPE_ID_ACC]);
		ia_css_pipe_extra_config_शेषs(
		    &stream_env->pipe_extra_configs[IA_CSS_PIPE_ID_ACC]);
	पूर्ण
	asd->acc.pipeline = शून्य;

	/* css 2.0 API limitation: ia_css_stop_sp() could be only called after
	 * destroy all pipes
	 */
	ia_css_stop_sp();

	kमुक्त(asd->acc.acc_stages);
	asd->acc.acc_stages = शून्य;

	atomisp_freq_scaling(asd->isp, ATOMISP_DFS_MODE_LOW, false);
पूर्ण

पूर्णांक atomisp_css_load_acc_binary(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_fw_info *fw,
				अचिन्हित पूर्णांक index)
अणु
	काष्ठा ia_css_pipe_config *pipe_config =
		    &asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL]
		    .pipe_configs[IA_CSS_PIPE_ID_ACC];

	अगर (index >= MAX_ACC_STAGES) अणु
		dev_dbg(asd->isp->dev, "%s: index(%d) out of range\n",
			__func__, index);
		वापस -ENOMEM;
	पूर्ण

	pipe_config->acc_stages[index] = fw;
	pipe_config->num_acc_stages = index + 1;
	pipe_config->acc_num_execs = 1;

	वापस 0;
पूर्ण

अटल काष्ठा atomisp_sub_device *__get_atomisp_subdev(
    काष्ठा ia_css_pipe *css_pipe,
    काष्ठा atomisp_device *isp,
    क्रमागत atomisp_input_stream_id *stream_id)
अणु
	पूर्णांक i, j, k;
	काष्ठा atomisp_sub_device *asd;
	काष्ठा atomisp_stream_env *stream_env;

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		अगर (asd->streaming == ATOMISP_DEVICE_STREAMING_DISABLED &&
		    !asd->acc.pipeline)
			जारी;
		क्रम (j = 0; j < ATOMISP_INPUT_STREAM_NUM; j++) अणु
			stream_env = &asd->stream_env[j];
			क्रम (k = 0; k < IA_CSS_PIPE_ID_NUM; k++) अणु
				अगर (stream_env->pipes[k] &&
				    stream_env->pipes[k] == css_pipe) अणु
					*stream_id = j;
					वापस asd;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक atomisp_css_isr_thपढ़ो(काष्ठा atomisp_device *isp,
			   bool *frame_करोne_found,
			   bool *css_pipe_करोne)
अणु
	क्रमागत atomisp_input_stream_id stream_id = 0;
	काष्ठा atomisp_css_event current_event;
	काष्ठा atomisp_sub_device *asd;
	bool reset_wdt_समयr[MAX_STREAM_NUM] = अणुfalseपूर्ण;
	पूर्णांक i;

	जबतक (!atomisp_css_dequeue_event(&current_event)) अणु
		अगर (current_event.event.type ==
		    IA_CSS_EVENT_TYPE_FW_ASSERT) अणु
			/*
			 * Received FW निश्चितion संकेत,
			 * trigger WDT to recover
			 */
			dev_err(isp->dev,
				"%s: ISP reports FW_ASSERT event! fw_assert_module_id %d fw_assert_line_no %d\n",
				__func__,
				current_event.event.fw_निश्चित_module_id,
				current_event.event.fw_निश्चित_line_no);
			क्रम (i = 0; i < isp->num_of_streams; i++)
				atomisp_wdt_stop(&isp->asd[i], 0);

			अगर (!IS_ISP2401)
				atomisp_wdt(&isp->asd[0].wdt);
			अन्यथा
				queue_work(isp->wdt_work_queue, &isp->wdt_work);

			वापस -EINVAL;
		पूर्ण अन्यथा अगर (current_event.event.type == IA_CSS_EVENT_TYPE_FW_WARNING) अणु
			dev_warn(isp->dev, "%s: ISP reports warning, code is %d, exp_id %d\n",
				 __func__, current_event.event.fw_warning,
				 current_event.event.exp_id);
			जारी;
		पूर्ण

		asd = __get_atomisp_subdev(current_event.event.pipe,
					   isp, &stream_id);
		अगर (!asd) अणु
			अगर (current_event.event.type == IA_CSS_EVENT_TYPE_TIMER)
				dev_dbg(isp->dev,
					"event: Timer event.");
			अन्यथा
				dev_warn(isp->dev, "%s:no subdev.event:%d",
					 __func__,
					 current_event.event.type);
			जारी;
		पूर्ण

		atomisp_css_temp_pipe_to_pipe_id(asd, &current_event);
		चयन (current_event.event.type) अणु
		हाल IA_CSS_EVENT_TYPE_OUTPUT_FRAME_DONE:
			dev_dbg(isp->dev, "event: Output frame done");
			frame_करोne_found[asd->index] = true;
			atomisp_buf_करोne(asd, 0, IA_CSS_BUFFER_TYPE_OUTPUT_FRAME,
					 current_event.pipe, true, stream_id);

			अगर (!IS_ISP2401)
				reset_wdt_समयr[asd->index] = true; /* ISP running */

			अवरोध;
		हाल IA_CSS_EVENT_TYPE_SECOND_OUTPUT_FRAME_DONE:
			dev_dbg(isp->dev, "event: Second output frame done");
			frame_करोne_found[asd->index] = true;
			atomisp_buf_करोne(asd, 0, IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME,
					 current_event.pipe, true, stream_id);

			अगर (!IS_ISP2401)
				reset_wdt_समयr[asd->index] = true; /* ISP running */

			अवरोध;
		हाल IA_CSS_EVENT_TYPE_3A_STATISTICS_DONE:
			dev_dbg(isp->dev, "event: 3A stats frame done");
			atomisp_buf_करोne(asd, 0,
					 IA_CSS_BUFFER_TYPE_3A_STATISTICS,
					 current_event.pipe,
					 false, stream_id);
			अवरोध;
		हाल IA_CSS_EVENT_TYPE_METADATA_DONE:
			dev_dbg(isp->dev, "event: metadata frame done");
			atomisp_buf_करोne(asd, 0,
					 IA_CSS_BUFFER_TYPE_METADATA,
					 current_event.pipe,
					 false, stream_id);
			अवरोध;
		हाल IA_CSS_EVENT_TYPE_VF_OUTPUT_FRAME_DONE:
			dev_dbg(isp->dev, "event: VF output frame done");
			atomisp_buf_करोne(asd, 0,
					 IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME,
					 current_event.pipe, true, stream_id);

			अगर (!IS_ISP2401)
				reset_wdt_समयr[asd->index] = true; /* ISP running */

			अवरोध;
		हाल IA_CSS_EVENT_TYPE_SECOND_VF_OUTPUT_FRAME_DONE:
			dev_dbg(isp->dev, "event: second VF output frame done");
			atomisp_buf_करोne(asd, 0,
					 IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME,
					 current_event.pipe, true, stream_id);
			अगर (!IS_ISP2401)
				reset_wdt_समयr[asd->index] = true; /* ISP running */

			अवरोध;
		हाल IA_CSS_EVENT_TYPE_DIS_STATISTICS_DONE:
			dev_dbg(isp->dev, "event: dis stats frame done");
			atomisp_buf_करोne(asd, 0,
					 IA_CSS_BUFFER_TYPE_DIS_STATISTICS,
					 current_event.pipe,
					 false, stream_id);
			अवरोध;
		हाल IA_CSS_EVENT_TYPE_PIPELINE_DONE:
			dev_dbg(isp->dev, "event: pipeline done");
			css_pipe_करोne[asd->index] = true;
			अवरोध;
		हाल IA_CSS_EVENT_TYPE_ACC_STAGE_COMPLETE:
			dev_dbg(isp->dev, "event: acc stage done");
			atomisp_acc_करोne(asd, current_event.event.fw_handle);
			अवरोध;
		शेष:
			dev_dbg(isp->dev, "unhandled css stored event: 0x%x\n",
				current_event.event.type);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (IS_ISP2401)
		वापस 0;

	/* ISP2400: If there are no buffers queued then delete wdt समयr. */
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		asd = &isp->asd[i];
		अगर (!asd)
			जारी;
		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
			जारी;
		अगर (!atomisp_buffers_queued(asd))
			atomisp_wdt_stop(asd, false);
		अन्यथा अगर (reset_wdt_समयr[i])
			/* SOF irq should not reset wdt समयr. */
			atomisp_wdt_refresh(asd,
					    ATOMISP_WDT_KEEP_CURRENT_DELAY);
	पूर्ण

	वापस 0;
पूर्ण

bool atomisp_css_valid_sof(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक i, j;

	/* Loop क्रम each css stream */
	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];
		/* Loop क्रम each css vc stream */
		क्रम (j = 0; j < ATOMISP_INPUT_STREAM_NUM; j++) अणु
			अगर (!asd->stream_env[j].stream)
				जारी;

			dev_dbg(isp->dev,
				"stream #%d: mode: %d\n", j,
				asd->stream_env[j].stream_config.mode);
			अगर (asd->stream_env[j].stream_config.mode ==
			    IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक atomisp_css_debug_dump_isp_binary(व्योम)
अणु
	ia_css_debug_dump_isp_binary();
	वापस 0;
पूर्ण

पूर्णांक atomisp_css_dump_sp_raw_copy_linecount(bool reduced)
अणु
	sh_css_dump_sp_raw_copy_linecount(reduced);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर fw_type_name[] = अणु
	[ia_css_sp_firmware]		= "SP",
	[ia_css_isp_firmware]		= "ISP",
	[ia_css_bootloader_firmware]	= "BootLoader",
	[ia_css_acc_firmware]		= "accel",
पूर्ण;

अटल स्थिर अक्षर * स्थिर fw_acc_type_name[] = अणु
	[IA_CSS_ACC_NONE] =		"Normal",
	[IA_CSS_ACC_OUTPUT] =		"Accel stage on output",
	[IA_CSS_ACC_VIEWFINDER] =	"Accel stage on viewfinder",
	[IA_CSS_ACC_STANDALONE] =	"Stand-alone acceleration",
पूर्ण;

पूर्णांक atomisp_css_dump_blob_inक्रम(काष्ठा atomisp_device *isp)
अणु
	काष्ठा ia_css_blob_descr *bd = sh_css_blob_info;
	अचिन्हित पूर्णांक i, nm = sh_css_num_binaries;

	अगर (nm == 0)
		वापस -EPERM;
	अगर (!bd)
		वापस -EPERM;

	/*
	 * The sh_css_load_firmware function discard the initial
	 * "SPS" binaries
	 */
	क्रम (i = 0; i < sh_css_num_binaries - NUM_OF_SPS; i++) अणु
		चयन (bd[i].header.type) अणु
		हाल ia_css_isp_firmware:
			dev_dbg(isp->dev, "Num%2d type %s (%s), binary id is %2d, name is %s\n",
				i + NUM_OF_SPS,
				fw_type_name[bd[i].header.type],
				fw_acc_type_name[bd[i].header.info.isp.type],
				bd[i].header.info.isp.sp.id,
				bd[i].name);
			अवरोध;
		शेष:
			dev_dbg(isp->dev, "Num%2d type %s, name is %s\n",
				i + NUM_OF_SPS, fw_type_name[bd[i].header.type],
				bd[i].name);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomisp_css_set_isp_config_id(काष्ठा atomisp_sub_device *asd,
				   uपूर्णांक32_t isp_config_id)
अणु
	asd->params.config.isp_config_id = isp_config_id;
पूर्ण

व्योम atomisp_css_set_isp_config_applied_frame(काष्ठा atomisp_sub_device *asd,
	काष्ठा ia_css_frame *output_frame)
अणु
	asd->params.config.output_frame = output_frame;
पूर्ण

पूर्णांक atomisp_get_css_dbgfunc(व्योम)
अणु
	वापस dbg_func;
पूर्ण

पूर्णांक atomisp_set_css_dbgfunc(काष्ठा atomisp_device *isp, पूर्णांक opt)
अणु
	पूर्णांक ret;

	ret = __set_css_prपूर्णांक_env(isp, opt);
	अगर (ret == 0)
		dbg_func = opt;

	वापस ret;
पूर्ण

व्योम atomisp_en_dz_capt_pipe(काष्ठा atomisp_sub_device *asd, bool enable)
अणु
	ia_css_en_dz_capt_pipe(
	    asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
	    enable);
पूर्ण

काष्ठा ia_css_dvs_grid_info *atomisp_css_get_dvs_grid_info(
    काष्ठा ia_css_grid_info *grid_info)
अणु
	अगर (!grid_info)
		वापस शून्य;

#अगर_घोषित IA_CSS_DVS_STAT_GRID_INFO_SUPPORTED
	वापस &grid_info->dvs_grid.dvs_grid_info;
#अन्यथा
	वापस &grid_info->dvs_grid;
#पूर्ण_अगर
पूर्ण
