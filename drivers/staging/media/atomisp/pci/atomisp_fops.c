<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
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

#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf-vदो_स्मृति.h>

#समावेश "atomisp_cmd.h"
#समावेश "atomisp_common.h"
#समावेश "atomisp_fops.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp_compat.h"
#समावेश "atomisp_subdev.h"
#समावेश "atomisp_v4l2.h"
#समावेश "atomisp-regs.h"
#समावेश "hmm/hmm.h"

#समावेश "type_support.h"
#समावेश "device_access/device_access.h"

#समावेश "atomisp_acc.h"

#घोषणा ISP_LEFT_PAD			128	/* equal to 2*NWAY */

/*
 * input image data, and current frame resolution क्रम test
 */
#घोषणा	ISP_PARAM_MMAP_OFFSET	0xfffff000

#घोषणा MAGIC_CHECK(is, should)	\
	करो अणु \
		अगर (unlikely((is) != (should))) अणु \
			pr_err("magic mismatch: %x (expected %x)\n", \
				is, should); \
			BUG(); \
		पूर्ण \
	पूर्ण जबतक (0)

/*
 * Videobuf ops
 */
अटल पूर्णांक atomisp_buf_setup(काष्ठा videobuf_queue *vq, अचिन्हित पूर्णांक *count,
			     अचिन्हित पूर्णांक *size)
अणु
	काष्ठा atomisp_video_pipe *pipe = vq->priv_data;

	*size = pipe->pix.sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_buf_prepare(काष्ठा videobuf_queue *vq,
			       काष्ठा videobuf_buffer *vb,
			       क्रमागत v4l2_field field)
अणु
	काष्ठा atomisp_video_pipe *pipe = vq->priv_data;

	vb->size = pipe->pix.sizeimage;
	vb->width = pipe->pix.width;
	vb->height = pipe->pix.height;
	vb->field = field;
	vb->state = VIDEOBUF_PREPARED;

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_q_one_metadata_buffer(काष्ठा atomisp_sub_device *asd,
	क्रमागत atomisp_input_stream_id stream_id,
	क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_metadata_buf *metadata_buf;
	क्रमागत atomisp_metadata_type md_type =
	    atomisp_get_metadata_type(asd, css_pipe_id);
	काष्ठा list_head *metadata_list;

	अगर (asd->metadata_bufs_in_css[stream_id][css_pipe_id] >=
	    ATOMISP_CSS_Q_DEPTH)
		वापस 0; /* we have reached CSS queue depth */

	अगर (!list_empty(&asd->metadata[md_type])) अणु
		metadata_list = &asd->metadata[md_type];
	पूर्ण अन्यथा अगर (!list_empty(&asd->metadata_पढ़ोy[md_type])) अणु
		metadata_list = &asd->metadata_पढ़ोy[md_type];
	पूर्ण अन्यथा अणु
		dev_warn(asd->isp->dev, "%s: No metadata buffers available for type %d!\n",
			 __func__, md_type);
		वापस -EINVAL;
	पूर्ण

	metadata_buf = list_entry(metadata_list->next,
				  काष्ठा atomisp_metadata_buf, list);
	list_del_init(&metadata_buf->list);

	अगर (atomisp_q_metadata_buffer_to_css(asd, metadata_buf,
					     stream_id, css_pipe_id)) अणु
		list_add(&metadata_buf->list, metadata_list);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		list_add_tail(&metadata_buf->list,
			      &asd->metadata_in_css[md_type]);
	पूर्ण
	asd->metadata_bufs_in_css[stream_id][css_pipe_id]++;

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_q_one_s3a_buffer(काष्ठा atomisp_sub_device *asd,
				    क्रमागत atomisp_input_stream_id stream_id,
				    क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_s3a_buf *s3a_buf;
	काष्ठा list_head *s3a_list;
	अचिन्हित पूर्णांक exp_id;

	अगर (asd->s3a_bufs_in_css[css_pipe_id] >= ATOMISP_CSS_Q_DEPTH)
		वापस 0; /* we have reached CSS queue depth */

	अगर (!list_empty(&asd->s3a_stats)) अणु
		s3a_list = &asd->s3a_stats;
	पूर्ण अन्यथा अगर (!list_empty(&asd->s3a_stats_पढ़ोy)) अणु
		s3a_list = &asd->s3a_stats_पढ़ोy;
	पूर्ण अन्यथा अणु
		dev_warn(asd->isp->dev, "%s: No s3a buffers available!\n",
			 __func__);
		वापस -EINVAL;
	पूर्ण

	s3a_buf = list_entry(s3a_list->next, काष्ठा atomisp_s3a_buf, list);
	list_del_init(&s3a_buf->list);
	exp_id = s3a_buf->s3a_data->exp_id;

	hmm_flush_vmap(s3a_buf->s3a_data->data_ptr);
	अगर (atomisp_q_s3a_buffer_to_css(asd, s3a_buf,
					stream_id, css_pipe_id)) अणु
		/* got from head, so वापस back to the head */
		list_add(&s3a_buf->list, s3a_list);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		list_add_tail(&s3a_buf->list, &asd->s3a_stats_in_css);
		अगर (s3a_list == &asd->s3a_stats_पढ़ोy)
			dev_warn(asd->isp->dev, "%s: drop one s3a stat which has exp_id %d!\n",
				 __func__, exp_id);
	पूर्ण

	asd->s3a_bufs_in_css[css_pipe_id]++;
	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_q_one_dis_buffer(काष्ठा atomisp_sub_device *asd,
				    क्रमागत atomisp_input_stream_id stream_id,
				    क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा atomisp_dis_buf *dis_buf;
	अचिन्हित दीर्घ irqflags;

	अगर (asd->dis_bufs_in_css >=  ATOMISP_CSS_Q_DEPTH)
		वापस 0; /* we have reached CSS queue depth */

	spin_lock_irqsave(&asd->dis_stats_lock, irqflags);
	अगर (list_empty(&asd->dis_stats)) अणु
		spin_unlock_irqrestore(&asd->dis_stats_lock, irqflags);
		dev_warn(asd->isp->dev, "%s: No dis buffers available!\n",
			 __func__);
		वापस -EINVAL;
	पूर्ण

	dis_buf = list_entry(asd->dis_stats.prev,
			     काष्ठा atomisp_dis_buf, list);
	list_del_init(&dis_buf->list);
	spin_unlock_irqrestore(&asd->dis_stats_lock, irqflags);

	hmm_flush_vmap(dis_buf->dis_data->data_ptr);
	अगर (atomisp_q_dis_buffer_to_css(asd, dis_buf,
					stream_id, css_pipe_id)) अणु
		spin_lock_irqsave(&asd->dis_stats_lock, irqflags);
		/* got from tail, so वापस back to the tail */
		list_add_tail(&dis_buf->list, &asd->dis_stats);
		spin_unlock_irqrestore(&asd->dis_stats_lock, irqflags);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&asd->dis_stats_lock, irqflags);
		list_add_tail(&dis_buf->list, &asd->dis_stats_in_css);
		spin_unlock_irqrestore(&asd->dis_stats_lock, irqflags);
	पूर्ण

	asd->dis_bufs_in_css++;

	वापस 0;
पूर्ण

पूर्णांक atomisp_q_video_buffers_to_css(काष्ठा atomisp_sub_device *asd,
				   काष्ठा atomisp_video_pipe *pipe,
				   क्रमागत atomisp_input_stream_id stream_id,
				   क्रमागत ia_css_buffer_type css_buf_type,
				   क्रमागत ia_css_pipe_id css_pipe_id)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;
	काष्ठा atomisp_css_params_with_list *param;
	काष्ठा ia_css_dvs_grid_info *dvs_grid =
	    atomisp_css_get_dvs_grid_info(&asd->params.curr_grid_info);
	अचिन्हित दीर्घ irqflags;
	पूर्णांक err = 0;

	अगर (WARN_ON(css_pipe_id >= IA_CSS_PIPE_ID_NUM))
		वापस -EINVAL;

	जबतक (pipe->buffers_in_css < ATOMISP_CSS_Q_DEPTH) अणु
		काष्ठा videobuf_buffer *vb;

		spin_lock_irqsave(&pipe->irq_lock, irqflags);
		अगर (list_empty(&pipe->activeq)) अणु
			spin_unlock_irqrestore(&pipe->irq_lock, irqflags);
			वापस -EINVAL;
		पूर्ण
		vb = list_entry(pipe->activeq.next,
				काष्ठा videobuf_buffer, queue);
		list_del_init(&vb->queue);
		vb->state = VIDEOBUF_ACTIVE;
		spin_unlock_irqrestore(&pipe->irq_lock, irqflags);

		/*
		 * If there is a per_frame setting to apply on the buffer,
		 * करो it beक्रमe buffer en-queueing.
		 */
		vm_mem = vb->priv;

		param = pipe->frame_params[vb->i];
		अगर (param) अणु
			atomisp_makeup_css_parameters(asd,
						      &asd->params.css_param.update_flag,
						      &param->params);
			atomisp_apply_css_parameters(asd, &param->params);

			अगर (param->params.update_flag.dz_config &&
			    asd->run_mode->val != ATOMISP_RUN_MODE_VIDEO) अणु
				err = atomisp_calculate_real_zoom_region(asd,
					&param->params.dz_config, css_pipe_id);
				अगर (!err)
					asd->params.config.dz_config = &param->params.dz_config;
			पूर्ण
			atomisp_css_set_isp_config_applied_frame(asd,
				vm_mem->vaddr);
			atomisp_css_update_isp_params_on_pipe(asd,
							      asd->stream_env[stream_id].pipes[css_pipe_id]);
			asd->params.dvs_6axis = (काष्ठा ia_css_dvs_6axis_config *)
						param->params.dvs_6axis;

			/*
			 * WORKAROUND:
			 * Because the camera halv3 can't ensure to set zoom
			 * region to per_frame setting and global setting at
			 * same समय and only set zoom region to pre_frame
			 * setting now.so when the pre_frame setting include
			 * zoom region,I will set it to global setting.
			 */
			अगर (param->params.update_flag.dz_config &&
			    asd->run_mode->val != ATOMISP_RUN_MODE_VIDEO
			    && !err) अणु
				स_नकल(&asd->params.css_param.dz_config,
				       &param->params.dz_config,
				       माप(काष्ठा ia_css_dz_config));
				asd->params.css_param.update_flag.dz_config =
				    (काष्ठा atomisp_dz_config *)
				    &asd->params.css_param.dz_config;
				asd->params.css_update_params_needed = true;
			पूर्ण
		पूर्ण
		/* Enqueue buffer */
		err = atomisp_q_video_buffer_to_css(asd, vm_mem, stream_id,
						    css_buf_type, css_pipe_id);
		अगर (err) अणु
			spin_lock_irqsave(&pipe->irq_lock, irqflags);
			list_add_tail(&vb->queue, &pipe->activeq);
			vb->state = VIDEOBUF_QUEUED;
			spin_unlock_irqrestore(&pipe->irq_lock, irqflags);
			dev_err(asd->isp->dev, "%s, css q fails: %d\n",
				__func__, err);
			वापस -EINVAL;
		पूर्ण
		pipe->buffers_in_css++;

		/* enqueue 3A/DIS/metadata buffers */
		अगर (asd->params.curr_grid_info.s3a_grid.enable &&
		    css_pipe_id == asd->params.s3a_enabled_pipe &&
		    css_buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
			atomisp_q_one_s3a_buffer(asd, stream_id,
						 css_pipe_id);

		अगर (asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream_info.
		    metadata_info.size &&
		    css_buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
			atomisp_q_one_metadata_buffer(asd, stream_id,
						      css_pipe_id);

		अगर (dvs_grid && dvs_grid->enable &&
		    css_pipe_id == IA_CSS_PIPE_ID_VIDEO &&
		    css_buf_type == IA_CSS_BUFFER_TYPE_OUTPUT_FRAME)
			atomisp_q_one_dis_buffer(asd, stream_id,
						 css_pipe_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_get_css_buf_type(काष्ठा atomisp_sub_device *asd,
				    क्रमागत ia_css_pipe_id pipe_id,
				    uपूर्णांक16_t source_pad)
अणु
	अगर (ATOMISP_USE_YUVPP(asd)) अणु
		/* when run ZSL हाल */
		अगर (asd->continuous_mode->val &&
		    asd->run_mode->val == ATOMISP_RUN_MODE_PREVIEW) अणु
			अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE)
				वापस IA_CSS_BUFFER_TYPE_OUTPUT_FRAME;
			अन्यथा अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW)
				वापस IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME;
			अन्यथा
				वापस IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME;
		पूर्ण

		/*when run SDV हाल*/
		अगर (asd->continuous_mode->val &&
		    asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
			अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE)
				वापस IA_CSS_BUFFER_TYPE_OUTPUT_FRAME;
			अन्यथा अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW)
				वापस IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME;
			अन्यथा अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO)
				वापस IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME;
			अन्यथा
				वापस IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME;
		पूर्ण

		/*other हाल: शेष setting*/
		अगर (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE ||
		    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO ||
		    (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW &&
		     asd->run_mode->val != ATOMISP_RUN_MODE_VIDEO))
			वापस IA_CSS_BUFFER_TYPE_OUTPUT_FRAME;
		अन्यथा
			वापस IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME;
	पूर्ण

	अगर (pipe_id == IA_CSS_PIPE_ID_COPY ||
	    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE ||
	    source_pad == ATOMISP_SUBDEV_PAD_SOURCE_VIDEO ||
	    (source_pad == ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW &&
	     asd->run_mode->val != ATOMISP_RUN_MODE_VIDEO))
		वापस IA_CSS_BUFFER_TYPE_OUTPUT_FRAME;
	अन्यथा
		वापस IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME;
पूर्ण

अटल पूर्णांक atomisp_qbuffers_to_css_क्रम_all_pipes(काष्ठा atomisp_sub_device *asd)
अणु
	क्रमागत ia_css_buffer_type buf_type;
	क्रमागत ia_css_pipe_id css_capture_pipe_id = IA_CSS_PIPE_ID_COPY;
	क्रमागत ia_css_pipe_id css_preview_pipe_id = IA_CSS_PIPE_ID_COPY;
	क्रमागत ia_css_pipe_id css_video_pipe_id = IA_CSS_PIPE_ID_COPY;
	क्रमागत atomisp_input_stream_id input_stream_id;
	काष्ठा atomisp_video_pipe *capture_pipe;
	काष्ठा atomisp_video_pipe *preview_pipe;
	काष्ठा atomisp_video_pipe *video_pipe;

	capture_pipe = &asd->video_out_capture;
	preview_pipe = &asd->video_out_preview;
	video_pipe = &asd->video_out_video_capture;

	buf_type = atomisp_get_css_buf_type(
		       asd, css_preview_pipe_id,
		       atomisp_subdev_source_pad(&preview_pipe->vdev));
	input_stream_id = ATOMISP_INPUT_STREAM_PREVIEW;
	atomisp_q_video_buffers_to_css(asd, preview_pipe,
				       input_stream_id,
				       buf_type, css_preview_pipe_id);

	buf_type = atomisp_get_css_buf_type(asd, css_capture_pipe_id,
					    atomisp_subdev_source_pad(&capture_pipe->vdev));
	input_stream_id = ATOMISP_INPUT_STREAM_GENERAL;
	atomisp_q_video_buffers_to_css(asd, capture_pipe,
				       input_stream_id,
				       buf_type, css_capture_pipe_id);

	buf_type = atomisp_get_css_buf_type(asd, css_video_pipe_id,
					    atomisp_subdev_source_pad(&video_pipe->vdev));
	input_stream_id = ATOMISP_INPUT_STREAM_VIDEO;
	atomisp_q_video_buffers_to_css(asd, video_pipe,
				       input_stream_id,
				       buf_type, css_video_pipe_id);
	वापस 0;
पूर्ण

/* queue all available buffers to css */
पूर्णांक atomisp_qbuffers_to_css(काष्ठा atomisp_sub_device *asd)
अणु
	क्रमागत ia_css_buffer_type buf_type;
	क्रमागत ia_css_pipe_id css_capture_pipe_id = IA_CSS_PIPE_ID_NUM;
	क्रमागत ia_css_pipe_id css_preview_pipe_id = IA_CSS_PIPE_ID_NUM;
	क्रमागत ia_css_pipe_id css_video_pipe_id = IA_CSS_PIPE_ID_NUM;
	क्रमागत atomisp_input_stream_id input_stream_id;
	काष्ठा atomisp_video_pipe *capture_pipe = शून्य;
	काष्ठा atomisp_video_pipe *vf_pipe = शून्य;
	काष्ठा atomisp_video_pipe *preview_pipe = शून्य;
	काष्ठा atomisp_video_pipe *video_pipe = शून्य;
	bool raw_mode = atomisp_is_mbuscode_raw(
			    asd->fmt[asd->capture_pad].fmt.code);

	अगर (asd->isp->inमाला_दो[asd->input_curr].camera_caps->
	    sensor[asd->sensor_curr].stream_num == 2 &&
	    !asd->yuvpp_mode)
		वापस atomisp_qbuffers_to_css_क्रम_all_pipes(asd);

	अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_SCALER) अणु
		video_pipe = &asd->video_out_video_capture;
		css_video_pipe_id = IA_CSS_PIPE_ID_VIDEO;
	पूर्ण अन्यथा अगर (asd->vfpp->val == ATOMISP_VFPP_DISABLE_LOWLAT) अणु
		preview_pipe = &asd->video_out_capture;
		css_preview_pipe_id = IA_CSS_PIPE_ID_CAPTURE;
	पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_VIDEO) अणु
		अगर (asd->continuous_mode->val) अणु
			capture_pipe = &asd->video_out_capture;
			vf_pipe = &asd->video_out_vf;
			css_capture_pipe_id = IA_CSS_PIPE_ID_CAPTURE;
		पूर्ण
		video_pipe = &asd->video_out_video_capture;
		preview_pipe = &asd->video_out_preview;
		css_video_pipe_id = IA_CSS_PIPE_ID_VIDEO;
		css_preview_pipe_id = IA_CSS_PIPE_ID_VIDEO;
	पूर्ण अन्यथा अगर (asd->continuous_mode->val) अणु
		capture_pipe = &asd->video_out_capture;
		vf_pipe = &asd->video_out_vf;
		preview_pipe = &asd->video_out_preview;

		css_preview_pipe_id = IA_CSS_PIPE_ID_PREVIEW;
		css_capture_pipe_id = IA_CSS_PIPE_ID_CAPTURE;
	पूर्ण अन्यथा अगर (asd->run_mode->val == ATOMISP_RUN_MODE_PREVIEW) अणु
		preview_pipe = &asd->video_out_preview;
		css_preview_pipe_id = IA_CSS_PIPE_ID_PREVIEW;
	पूर्ण अन्यथा अणु
		/* ATOMISP_RUN_MODE_STILL_CAPTURE */
		capture_pipe = &asd->video_out_capture;
		अगर (!raw_mode)
			vf_pipe = &asd->video_out_vf;
		css_capture_pipe_id = IA_CSS_PIPE_ID_CAPTURE;
	पूर्ण

#अगर_घोषित ISP2401_NEW_INPUT_SYSTEM
	अगर (asd->copy_mode) अणु
		css_capture_pipe_id = IA_CSS_PIPE_ID_COPY;
		css_preview_pipe_id = IA_CSS_PIPE_ID_COPY;
		css_video_pipe_id = IA_CSS_PIPE_ID_COPY;
	पूर्ण
#पूर्ण_अगर

	अगर (asd->yuvpp_mode) अणु
		capture_pipe = &asd->video_out_capture;
		video_pipe   = &asd->video_out_video_capture;
		preview_pipe = &asd->video_out_preview;
		css_capture_pipe_id = IA_CSS_PIPE_ID_COPY;
		css_video_pipe_id   = IA_CSS_PIPE_ID_YUVPP;
		css_preview_pipe_id = IA_CSS_PIPE_ID_YUVPP;
	पूर्ण

	अगर (capture_pipe) अणु
		buf_type = atomisp_get_css_buf_type(
			       asd, css_capture_pipe_id,
			       atomisp_subdev_source_pad(&capture_pipe->vdev));
		input_stream_id = ATOMISP_INPUT_STREAM_GENERAL;

		/*
		 * use yuvpp pipe क्रम SOC camera.
		 */
		अगर (ATOMISP_USE_YUVPP(asd))
			css_capture_pipe_id = IA_CSS_PIPE_ID_YUVPP;

		atomisp_q_video_buffers_to_css(asd, capture_pipe,
					       input_stream_id,
					       buf_type, css_capture_pipe_id);
	पूर्ण

	अगर (vf_pipe) अणु
		buf_type = atomisp_get_css_buf_type(
			       asd, css_capture_pipe_id,
			       atomisp_subdev_source_pad(&vf_pipe->vdev));
		अगर (asd->stream_env[ATOMISP_INPUT_STREAM_POSTVIEW].stream)
			input_stream_id = ATOMISP_INPUT_STREAM_POSTVIEW;
		अन्यथा
			input_stream_id = ATOMISP_INPUT_STREAM_GENERAL;

		/*
		 * use yuvpp pipe क्रम SOC camera.
		 */
		अगर (ATOMISP_USE_YUVPP(asd))
			css_capture_pipe_id = IA_CSS_PIPE_ID_YUVPP;
		atomisp_q_video_buffers_to_css(asd, vf_pipe,
					       input_stream_id,
					       buf_type, css_capture_pipe_id);
	पूर्ण

	अगर (preview_pipe) अणु
		buf_type = atomisp_get_css_buf_type(
			       asd, css_preview_pipe_id,
			       atomisp_subdev_source_pad(&preview_pipe->vdev));
		अगर (ATOMISP_SOC_CAMERA(asd) && css_preview_pipe_id == IA_CSS_PIPE_ID_YUVPP)
			input_stream_id = ATOMISP_INPUT_STREAM_GENERAL;
		/* अन्यथा क्रम ext isp use हाल */
		अन्यथा अगर (css_preview_pipe_id == IA_CSS_PIPE_ID_YUVPP)
			input_stream_id = ATOMISP_INPUT_STREAM_VIDEO;
		अन्यथा अगर (asd->stream_env[ATOMISP_INPUT_STREAM_PREVIEW].stream)
			input_stream_id = ATOMISP_INPUT_STREAM_PREVIEW;
		अन्यथा
			input_stream_id = ATOMISP_INPUT_STREAM_GENERAL;

		/*
		 * use yuvpp pipe क्रम SOC camera.
		 */
		अगर (ATOMISP_USE_YUVPP(asd))
			css_preview_pipe_id = IA_CSS_PIPE_ID_YUVPP;

		atomisp_q_video_buffers_to_css(asd, preview_pipe,
					       input_stream_id,
					       buf_type, css_preview_pipe_id);
	पूर्ण

	अगर (video_pipe) अणु
		buf_type = atomisp_get_css_buf_type(
			       asd, css_video_pipe_id,
			       atomisp_subdev_source_pad(&video_pipe->vdev));
		अगर (asd->stream_env[ATOMISP_INPUT_STREAM_VIDEO].stream)
			input_stream_id = ATOMISP_INPUT_STREAM_VIDEO;
		अन्यथा
			input_stream_id = ATOMISP_INPUT_STREAM_GENERAL;

		/*
		 * use yuvpp pipe क्रम SOC camera.
		 */
		अगर (ATOMISP_USE_YUVPP(asd))
			css_video_pipe_id = IA_CSS_PIPE_ID_YUVPP;

		atomisp_q_video_buffers_to_css(asd, video_pipe,
					       input_stream_id,
					       buf_type, css_video_pipe_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम atomisp_buf_queue(काष्ठा videobuf_queue *vq,
			      काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा atomisp_video_pipe *pipe = vq->priv_data;

	/*
	 * when a frame buffer meets following conditions, it should be put पूर्णांकo
	 * the रुकोing list:
	 * 1.  It is not a मुख्य output frame, and it has a per-frame parameter
	 *     to go with it.
	 * 2.  It is not a मुख्य output frame, and the रुकोing buffer list is not
	 *     empty, to keep the FIFO sequence of frame buffer processing, it
	 *     is put to रुकोing list until previous per-frame parameter buffers
	 *     get enqueued.
	 */
	अगर (!atomisp_is_vf_pipe(pipe) &&
	    (pipe->frame_request_config_id[vb->i] ||
	     !list_empty(&pipe->buffers_रुकोing_क्रम_param)))
		list_add_tail(&vb->queue, &pipe->buffers_रुकोing_क्रम_param);
	अन्यथा
		list_add_tail(&vb->queue, &pipe->activeq);

	vb->state = VIDEOBUF_QUEUED;
पूर्ण

अटल व्योम atomisp_buf_release(काष्ठा videobuf_queue *vq,
				काष्ठा videobuf_buffer *vb)
अणु
	vb->state = VIDEOBUF_NEEDS_INIT;
	atomisp_videobuf_मुक्त_buf(vb);
पूर्ण

अटल पूर्णांक atomisp_buf_setup_output(काष्ठा videobuf_queue *vq,
				    अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा atomisp_video_pipe *pipe = vq->priv_data;

	*size = pipe->pix.sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_buf_prepare_output(काष्ठा videobuf_queue *vq,
				      काष्ठा videobuf_buffer *vb,
				      क्रमागत v4l2_field field)
अणु
	काष्ठा atomisp_video_pipe *pipe = vq->priv_data;

	vb->size = pipe->pix.sizeimage;
	vb->width = pipe->pix.width;
	vb->height = pipe->pix.height;
	vb->field = field;
	vb->state = VIDEOBUF_PREPARED;

	वापस 0;
पूर्ण

अटल व्योम atomisp_buf_queue_output(काष्ठा videobuf_queue *vq,
				     काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा atomisp_video_pipe *pipe = vq->priv_data;

	list_add_tail(&vb->queue, &pipe->activeq_out);
	vb->state = VIDEOBUF_QUEUED;
पूर्ण

अटल व्योम atomisp_buf_release_output(काष्ठा videobuf_queue *vq,
				       काष्ठा videobuf_buffer *vb)
अणु
	videobuf_vदो_स्मृति_मुक्त(vb);
	vb->state = VIDEOBUF_NEEDS_INIT;
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops videobuf_qops = अणु
	.buf_setup	= atomisp_buf_setup,
	.buf_prepare	= atomisp_buf_prepare,
	.buf_queue	= atomisp_buf_queue,
	.buf_release	= atomisp_buf_release,
पूर्ण;

अटल स्थिर काष्ठा videobuf_queue_ops videobuf_qops_output = अणु
	.buf_setup	= atomisp_buf_setup_output,
	.buf_prepare	= atomisp_buf_prepare_output,
	.buf_queue	= atomisp_buf_queue_output,
	.buf_release	= atomisp_buf_release_output,
पूर्ण;

अटल पूर्णांक atomisp_init_pipe(काष्ठा atomisp_video_pipe *pipe)
अणु
	/* init locks */
	spin_lock_init(&pipe->irq_lock);

	videobuf_queue_vदो_स्मृति_init(&pipe->capq, &videobuf_qops, शून्य,
				    &pipe->irq_lock,
				    V4L2_BUF_TYPE_VIDEO_CAPTURE,
				    V4L2_FIELD_NONE,
				    माप(काष्ठा atomisp_buffer), pipe,
				    शून्य);	/* ext_lock: शून्य */

	videobuf_queue_vदो_स्मृति_init(&pipe->outq, &videobuf_qops_output, शून्य,
				    &pipe->irq_lock,
				    V4L2_BUF_TYPE_VIDEO_OUTPUT,
				    V4L2_FIELD_NONE,
				    माप(काष्ठा atomisp_buffer), pipe,
				    शून्य);	/* ext_lock: शून्य */

	INIT_LIST_HEAD(&pipe->activeq);
	INIT_LIST_HEAD(&pipe->activeq_out);
	INIT_LIST_HEAD(&pipe->buffers_रुकोing_क्रम_param);
	INIT_LIST_HEAD(&pipe->per_frame_params);
	स_रखो(pipe->frame_request_config_id, 0,
	       VIDEO_MAX_FRAME * माप(अचिन्हित पूर्णांक));
	स_रखो(pipe->frame_params, 0,
	       VIDEO_MAX_FRAME *
	       माप(काष्ठा atomisp_css_params_with_list *));

	वापस 0;
पूर्ण

अटल व्योम atomisp_dev_init_काष्ठा(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक i;

	isp->sw_contex.file_input = false;
	isp->need_gfx_throttle = true;
	isp->isp_fatal_error = false;
	isp->mipi_frame_size = 0;

	क्रम (i = 0; i < isp->input_cnt; i++)
		isp->inमाला_दो[i].asd = शून्य;
	/*
	 * For Merrअगरield, frequency is scalable.
	 * After boot-up, the शेष frequency is 200MHz.
	 */
	isp->sw_contex.running_freq = ISP_FREQ_200MHZ;
पूर्ण

अटल व्योम atomisp_subdev_init_काष्ठा(काष्ठा atomisp_sub_device *asd)
अणु
	v4l2_ctrl_s_ctrl(asd->run_mode, ATOMISP_RUN_MODE_STILL_CAPTURE);
	स_रखो(&asd->params.css_param, 0, माप(asd->params.css_param));
	asd->params.color_effect = V4L2_COLORFX_NONE;
	asd->params.bad_pixel_en = true;
	asd->params.gdc_cac_en = false;
	asd->params.video_dis_en = false;
	asd->params.sc_en = false;
	asd->params.fpn_en = false;
	asd->params.xnr_en = false;
	asd->params.false_color = 0;
	asd->params.online_process = 1;
	asd->params.yuv_ds_en = 0;
	/* s3a grid not enabled क्रम any pipe */
	asd->params.s3a_enabled_pipe = IA_CSS_PIPE_ID_NUM;

	asd->params.offline_parm.num_captures = 1;
	asd->params.offline_parm.skip_frames = 0;
	asd->params.offline_parm.offset = 0;
	asd->delayed_init = ATOMISP_DELAYED_INIT_NOT_QUEUED;
	/* Add क्रम channel */
	asd->input_curr = 0;

	asd->mipi_frame_size = 0;
	asd->copy_mode = false;
	asd->yuvpp_mode = false;

	asd->stream_prepared = false;
	asd->high_speed_mode = false;
	asd->sensor_array_res.height = 0;
	asd->sensor_array_res.width = 0;
	atomisp_css_init_काष्ठा(asd);
पूर्ण

/*
 * file operation functions
 */
अटल अचिन्हित पूर्णांक atomisp_subdev_users(काष्ठा atomisp_sub_device *asd)
अणु
	वापस asd->video_out_preview.users +
	       asd->video_out_vf.users +
	       asd->video_out_capture.users +
	       asd->video_out_video_capture.users +
	       asd->video_acc.users +
	       asd->video_in.users;
पूर्ण

अचिन्हित पूर्णांक atomisp_dev_users(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक i, sum;

	क्रम (i = 0, sum = 0; i < isp->num_of_streams; i++)
		sum += atomisp_subdev_users(&isp->asd[i]);

	वापस sum;
पूर्ण

अटल पूर्णांक atomisp_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = शून्य;
	काष्ठा atomisp_acc_pipe *acc_pipe = शून्य;
	काष्ठा atomisp_sub_device *asd;
	bool acc_node = false;
	पूर्णांक ret;

	dev_dbg(isp->dev, "open device %s\n", vdev->name);

	rt_mutex_lock(&isp->mutex);

	acc_node = !म_भेद(vdev->name, "ATOMISP ISP ACC");
	अगर (acc_node) अणु
		acc_pipe = atomisp_to_acc_pipe(vdev);
		asd = acc_pipe->asd;
	पूर्ण अन्यथा अणु
		pipe = atomisp_to_video_pipe(vdev);
		asd = pipe->asd;
	पूर्ण
	asd->subdev.devnode = vdev;
	/* Deferred firmware loading हाल. */
	अगर (isp->css_env.isp_css_fw.bytes == 0) अणु
		dev_err(isp->dev, "Deferred firmware load.\n");
		isp->firmware = atomisp_load_firmware(isp);
		अगर (!isp->firmware) अणु
			dev_err(isp->dev, "Failed to load ISP firmware.\n");
			ret = -ENOENT;
			जाओ error;
		पूर्ण
		ret = atomisp_css_load_firmware(isp);
		अगर (ret) अणु
			dev_err(isp->dev, "Failed to init css.\n");
			जाओ error;
		पूर्ण
		/* No need to keep FW in memory anymore. */
		release_firmware(isp->firmware);
		isp->firmware = शून्य;
		isp->css_env.isp_css_fw.data = शून्य;
	पूर्ण

	अगर (acc_node && acc_pipe->users) अणु
		dev_dbg(isp->dev, "acc node already opened\n");
		rt_mutex_unlock(&isp->mutex);
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (acc_node) अणु
		जाओ dev_init;
	पूर्ण

	अगर (!isp->input_cnt) अणु
		dev_err(isp->dev, "no camera attached\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * atomisp करोes not allow multiple खोलो
	 */
	अगर (pipe->users) अणु
		dev_dbg(isp->dev, "video node already opened\n");
		rt_mutex_unlock(&isp->mutex);
		वापस -EBUSY;
	पूर्ण

	ret = atomisp_init_pipe(pipe);
	अगर (ret)
		जाओ error;

dev_init:
	अगर (atomisp_dev_users(isp)) अणु
		dev_dbg(isp->dev, "skip init isp in open\n");
		जाओ init_subdev;
	पूर्ण

	/* runसमय घातer management, turn on ISP */
	ret = pm_runसमय_get_sync(vdev->v4l2_dev->dev);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "Failed to power on device\n");
		जाओ error;
	पूर्ण

	अगर (dypool_enable) अणु
		ret = hmm_pool_रेजिस्टर(dypool_pgnr, HMM_POOL_TYPE_DYNAMIC);
		अगर (ret)
			dev_err(isp->dev, "Failed to register dynamic memory pool.\n");
	पूर्ण

	/* Init ISP */
	अगर (atomisp_css_init(isp)) अणु
		ret = -EINVAL;
		/* Need to clean up CSS init अगर it fails. */
		जाओ css_error;
	पूर्ण

	atomisp_dev_init_काष्ठा(isp);

	ret = v4l2_subdev_call(isp->flash, core, s_घातer, 1);
	अगर (ret < 0 && ret != -ENODEV && ret != -ENOIOCTLCMD) अणु
		dev_err(isp->dev, "Failed to power-on flash\n");
		जाओ css_error;
	पूर्ण

init_subdev:
	अगर (atomisp_subdev_users(asd))
		जाओ करोne;

	atomisp_subdev_init_काष्ठा(asd);

करोne:

	अगर (acc_node)
		acc_pipe->users++;
	अन्यथा
		pipe->users++;
	rt_mutex_unlock(&isp->mutex);
	वापस 0;

css_error:
	atomisp_css_uninit(isp);
error:
	hmm_pool_unरेजिस्टर(HMM_POOL_TYPE_DYNAMIC);
	pm_runसमय_put(vdev->v4l2_dev->dev);
	rt_mutex_unlock(&isp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe;
	काष्ठा atomisp_acc_pipe *acc_pipe;
	काष्ठा atomisp_sub_device *asd;
	bool acc_node;
	काष्ठा v4l2_requestbuffers req;
	काष्ठा v4l2_subdev_fh fh;
	काष्ठा v4l2_rect clear_compose = अणु0पूर्ण;
	पूर्णांक ret = 0;

	v4l2_fh_init(&fh.vfh, vdev);

	req.count = 0;
	अगर (!isp)
		वापस -EBADF;

	mutex_lock(&isp->streamoff_mutex);
	rt_mutex_lock(&isp->mutex);

	dev_dbg(isp->dev, "release device %s\n", vdev->name);
	acc_node = !म_भेद(vdev->name, "ATOMISP ISP ACC");
	अगर (acc_node) अणु
		acc_pipe = atomisp_to_acc_pipe(vdev);
		asd = acc_pipe->asd;
	पूर्ण अन्यथा अणु
		pipe = atomisp_to_video_pipe(vdev);
		asd = pipe->asd;
	पूर्ण
	asd->subdev.devnode = vdev;
	अगर (acc_node) अणु
		acc_pipe->users--;
		जाओ subdev_uninit;
	पूर्ण
	pipe->users--;

	अगर (pipe->capq.streaming)
		dev_warn(isp->dev,
			 "%s: ISP still streaming while closing!",
			 __func__);

	अगर (pipe->capq.streaming &&
	    __atomisp_streamoff(file, शून्य, V4L2_BUF_TYPE_VIDEO_CAPTURE)) अणु
		dev_err(isp->dev,
			"atomisp_streamoff failed on release, driver bug");
		जाओ करोne;
	पूर्ण

	अगर (pipe->users)
		जाओ करोne;

	अगर (__atomisp_reqbufs(file, शून्य, &req)) अणु
		dev_err(isp->dev,
			"atomisp_reqbufs failed on release, driver bug");
		जाओ करोne;
	पूर्ण

	अगर (pipe->outq.bufs[0]) अणु
		mutex_lock(&pipe->outq.vb_lock);
		videobuf_queue_cancel(&pipe->outq);
		mutex_unlock(&pipe->outq.vb_lock);
	पूर्ण

	/*
	 * A little trick here:
	 * file injection input resolution is recorded in the sink pad,
	 * thereक्रमe can not be cleared when releaseing one device node.
	 * The sink pad setting can only be cleared when all device nodes
	 * get released.
	 */
	अगर (!isp->sw_contex.file_input && asd->fmt_स्वतः->val) अणु
		काष्ठा v4l2_mbus_framefmt isp_sink_fmt = अणु 0 पूर्ण;

		atomisp_subdev_set_ffmt(&asd->subdev, fh.pad,
					V4L2_SUBDEV_FORMAT_ACTIVE,
					ATOMISP_SUBDEV_PAD_SINK, &isp_sink_fmt);
	पूर्ण
subdev_uninit:
	अगर (atomisp_subdev_users(asd))
		जाओ करोne;

	/* clear the sink pad क्रम file input */
	अगर (isp->sw_contex.file_input && asd->fmt_स्वतः->val) अणु
		काष्ठा v4l2_mbus_framefmt isp_sink_fmt = अणु 0 पूर्ण;

		atomisp_subdev_set_ffmt(&asd->subdev, fh.pad,
					V4L2_SUBDEV_FORMAT_ACTIVE,
					ATOMISP_SUBDEV_PAD_SINK, &isp_sink_fmt);
	पूर्ण

	atomisp_css_मुक्त_stat_buffers(asd);
	atomisp_मुक्त_पूर्णांकernal_buffers(asd);
	ret = v4l2_subdev_call(isp->inमाला_दो[asd->input_curr].camera,
			       core, s_घातer, 0);
	अगर (ret)
		dev_warn(isp->dev, "Failed to power-off sensor\n");

	/* clear the asd field to show this camera is not used */
	isp->inमाला_दो[asd->input_curr].asd = शून्य;
	asd->streaming = ATOMISP_DEVICE_STREAMING_DISABLED;

	अगर (atomisp_dev_users(isp))
		जाओ करोne;

	atomisp_acc_release(asd);

	atomisp_destroy_pipes_stream_क्रमce(asd);
	atomisp_css_uninit(isp);

	अगर (defer_fw_load) अणु
		ia_css_unload_firmware();
		isp->css_env.isp_css_fw.data = शून्य;
		isp->css_env.isp_css_fw.bytes = 0;
	पूर्ण

	hmm_pool_unरेजिस्टर(HMM_POOL_TYPE_DYNAMIC);

	ret = v4l2_subdev_call(isp->flash, core, s_घातer, 0);
	अगर (ret < 0 && ret != -ENODEV && ret != -ENOIOCTLCMD)
		dev_warn(isp->dev, "Failed to power-off flash\n");

	अगर (pm_runसमय_put_sync(vdev->v4l2_dev->dev) < 0)
		dev_err(isp->dev, "Failed to power off device\n");

करोne:
	अगर (!acc_node) अणु
		atomisp_subdev_set_selection(&asd->subdev, fh.pad,
					     V4L2_SUBDEV_FORMAT_ACTIVE,
					     atomisp_subdev_source_pad(vdev),
					     V4L2_SEL_TGT_COMPOSE, 0,
					     &clear_compose);
	पूर्ण
	rt_mutex_unlock(&isp->mutex);
	mutex_unlock(&isp->streamoff_mutex);

	वापस 0;
पूर्ण

/*
 * Memory help functions क्रम image frame and निजी parameters
 */
अटल पूर्णांक करो_isp_mm_remap(काष्ठा atomisp_device *isp,
			   काष्ठा vm_area_काष्ठा *vma,
			   ia_css_ptr isp_virt, u32 host_virt, u32 pgnr)
अणु
	u32 pfn;

	जबतक (pgnr) अणु
		pfn = hmm_virt_to_phys(isp_virt) >> PAGE_SHIFT;
		अगर (remap_pfn_range(vma, host_virt, pfn,
				    PAGE_SIZE, PAGE_SHARED)) अणु
			dev_err(isp->dev, "remap_pfn_range err.\n");
			वापस -EAGAIN;
		पूर्ण

		isp_virt += PAGE_SIZE;
		host_virt += PAGE_SIZE;
		pgnr--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक frame_mmap(काष्ठा atomisp_device *isp,
		      स्थिर काष्ठा ia_css_frame *frame, काष्ठा vm_area_काष्ठा *vma)
अणु
	ia_css_ptr isp_virt;
	u32 host_virt;
	u32 pgnr;

	अगर (!frame) अणु
		dev_err(isp->dev, "%s: NULL frame pointer.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	host_virt = vma->vm_start;
	isp_virt = frame->data;
	atomisp_get_frame_pgnr(isp, frame, &pgnr);

	अगर (करो_isp_mm_remap(isp, vma, isp_virt, host_virt, pgnr))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

पूर्णांक atomisp_videobuf_mmap_mapper(काष्ठा videobuf_queue *q,
				 काष्ठा vm_area_काष्ठा *vma)
अणु
	u32 offset = vma->vm_pgoff << PAGE_SHIFT;
	पूर्णांक ret = -EINVAL, i;
	काष्ठा atomisp_device *isp =
	    ((काष्ठा atomisp_video_pipe *)(q->priv_data))->isp;
	काष्ठा videobuf_vदो_स्मृति_memory *vm_mem;
	काष्ठा videobuf_mapping *map;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);
	अगर (!(vma->vm_flags & VM_WRITE) || !(vma->vm_flags & VM_SHARED)) अणु
		dev_err(isp->dev, "map appl bug: PROT_WRITE and MAP_SHARED are required\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&q->vb_lock);
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		काष्ठा videobuf_buffer *buf = q->bufs[i];

		अगर (!buf)
			जारी;

		map = kzalloc(माप(काष्ठा videobuf_mapping), GFP_KERNEL);
		अगर (!map) अणु
			mutex_unlock(&q->vb_lock);
			वापस -ENOMEM;
		पूर्ण

		buf->map = map;
		map->q = q;

		buf->baddr = vma->vm_start;

		अगर (buf && buf->memory == V4L2_MEMORY_MMAP &&
		    buf->boff == offset) अणु
			vm_mem = buf->priv;
			ret = frame_mmap(isp, vm_mem->vaddr, vma);
			vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&q->vb_lock);

	वापस ret;
पूर्ण

/* The input frame contains left and right padding that need to be हटाओd.
 * There is always ISP_LEFT_PAD padding on the left side.
 * There is also padding on the right (padded_width - width).
 */
अटल पूर्णांक हटाओ_pad_from_frame(काष्ठा atomisp_device *isp,
				 काष्ठा ia_css_frame *in_frame, __u32 width, __u32 height)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित लघु *buffer;
	पूर्णांक ret = 0;
	ia_css_ptr load = in_frame->data;
	ia_css_ptr store = load;

	buffer = kदो_स्मृति_array(width, माप(load), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	load += ISP_LEFT_PAD;
	क्रम (i = 0; i < height; i++) अणु
		ret = hmm_load(load, buffer, width * माप(load));
		अगर (ret < 0)
			जाओ हटाओ_pad_error;

		ret = hmm_store(store, buffer, width * माप(store));
		अगर (ret < 0)
			जाओ हटाओ_pad_error;

		load  += in_frame->info.padded_width;
		store += width;
	पूर्ण

हटाओ_pad_error:
	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	काष्ठा atomisp_sub_device *asd = pipe->asd;
	काष्ठा ia_css_frame *raw_virt_addr;
	u32 start = vma->vm_start;
	u32 end = vma->vm_end;
	u32 size = end - start;
	u32 origin_size, new_size;
	पूर्णांक ret;

	अगर (!(vma->vm_flags & (VM_WRITE | VM_READ)))
		वापस -EACCES;

	rt_mutex_lock(&isp->mutex);

	अगर (!(vma->vm_flags & VM_SHARED)) अणु
		/* Map निजी buffer.
		 * Set VM_SHARED to the flags since we need
		 * to map the buffer page by page.
		 * Without VM_SHARED, remap_pfn_range() treats
		 * this kind of mapping as invalid.
		 */
		vma->vm_flags |= VM_SHARED;
		ret = hmm_mmap(vma, vma->vm_pgoff << PAGE_SHIFT);
		rt_mutex_unlock(&isp->mutex);
		वापस ret;
	पूर्ण

	/* mmap क्रम ISP offline raw data */
	अगर (atomisp_subdev_source_pad(vdev)
	    == ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE &&
	    vma->vm_pgoff == (ISP_PARAM_MMAP_OFFSET >> PAGE_SHIFT)) अणु
		new_size = pipe->pix.width * pipe->pix.height * 2;
		अगर (asd->params.online_process != 0) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		raw_virt_addr = asd->raw_output_frame;
		अगर (!raw_virt_addr) अणु
			dev_err(isp->dev, "Failed to request RAW frame\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		ret = हटाओ_pad_from_frame(isp, raw_virt_addr,
					    pipe->pix.width, pipe->pix.height);
		अगर (ret < 0) अणु
			dev_err(isp->dev, "remove pad failed.\n");
			जाओ error;
		पूर्ण
		origin_size = raw_virt_addr->data_bytes;
		raw_virt_addr->data_bytes = new_size;

		अगर (size != PAGE_ALIGN(new_size)) अणु
			dev_err(isp->dev, "incorrect size for mmap ISP  Raw Frame\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		अगर (frame_mmap(isp, raw_virt_addr, vma)) अणु
			dev_err(isp->dev, "frame_mmap failed.\n");
			raw_virt_addr->data_bytes = origin_size;
			ret = -EAGAIN;
			जाओ error;
		पूर्ण
		raw_virt_addr->data_bytes = origin_size;
		vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
		rt_mutex_unlock(&isp->mutex);
		वापस 0;
	पूर्ण

	/*
	 * mmap क्रम normal frames
	 */
	अगर (size != pipe->pix.sizeimage) अणु
		dev_err(isp->dev, "incorrect size for mmap ISP frames\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	rt_mutex_unlock(&isp->mutex);

	वापस atomisp_videobuf_mmap_mapper(&pipe->capq, vma);

error:
	rt_mutex_unlock(&isp->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	वापस videobuf_mmap_mapper(&pipe->outq, vma);
पूर्ण

अटल __poll_t atomisp_poll(काष्ठा file *file,
			     काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	काष्ठा atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);

	rt_mutex_lock(&isp->mutex);
	अगर (pipe->capq.streaming != 1) अणु
		rt_mutex_unlock(&isp->mutex);
		वापस EPOLLERR;
	पूर्ण
	rt_mutex_unlock(&isp->mutex);

	वापस videobuf_poll_stream(file, &pipe->capq, pt);
पूर्ण

स्थिर काष्ठा v4l2_file_operations atomisp_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = atomisp_खोलो,
	.release = atomisp_release,
	.mmap = atomisp_mmap,
	.unlocked_ioctl = video_ioctl2,
#अगर_घोषित CONFIG_COMPAT
	/*
	 * There are problems with this code. Disable this क्रम now.
	.compat_ioctl32 = atomisp_compat_ioctl32,
	 */
#पूर्ण_अगर
	.poll = atomisp_poll,
पूर्ण;

स्थिर काष्ठा v4l2_file_operations atomisp_file_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = atomisp_खोलो,
	.release = atomisp_release,
	.mmap = atomisp_file_mmap,
	.unlocked_ioctl = video_ioctl2,
#अगर_घोषित CONFIG_COMPAT
	/*
	 * There are problems with this code. Disable this क्रम now.
	.compat_ioctl32 = atomisp_compat_ioctl32,
	 */
#पूर्ण_अगर
	.poll = atomisp_poll,
पूर्ण;
