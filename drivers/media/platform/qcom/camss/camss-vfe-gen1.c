<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-vfe-gen1.c
 *
 * Qualcomm MSM Camera Subप्रणाली - VFE Common functionality क्रम Gen 1 versions of hw (4.1, 4.7..)
 *
 * Copyright (C) 2020 Linaro Ltd.
 */

#समावेश "camss.h"
#समावेश "camss-vfe.h"
#समावेश "camss-vfe-gen1.h"

/* Max number of frame drop updates per frame */
#घोषणा VFE_FRAME_DROP_UPDATES 2
#घोषणा VFE_NEXT_SOF_MS 500

पूर्णांक vfe_gen1_halt(काष्ठा vfe_device *vfe)
अणु
	अचिन्हित दीर्घ समय;

	reinit_completion(&vfe->halt_complete);

	vfe->ops_gen1->halt_request(vfe);

	समय = रुको_क्रम_completion_समयout(&vfe->halt_complete,
					   msecs_to_jअगरfies(VFE_HALT_TIMEOUT_MS));
	अगर (!समय) अणु
		dev_err(vfe->camss->dev, "VFE halt timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfe_disable_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output = &line->output;
	स्थिर काष्ठा vfe_hw_ops *ops = vfe->ops;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समय;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&vfe->output_lock, flags);

	output->gen1.रुको_sof = 1;
	spin_unlock_irqrestore(&vfe->output_lock, flags);

	समय = रुको_क्रम_completion_समयout(&output->sof, msecs_to_jअगरfies(VFE_NEXT_SOF_MS));
	अगर (!समय)
		dev_err(vfe->camss->dev, "VFE sof timeout\n");

	spin_lock_irqsave(&vfe->output_lock, flags);
	क्रम (i = 0; i < output->wm_num; i++)
		vfe->ops_gen1->wm_enable(vfe, output->wm_idx[i], 0);

	ops->reg_update(vfe, line->id);
	output->रुको_reg_update = 1;
	spin_unlock_irqrestore(&vfe->output_lock, flags);

	समय = रुको_क्रम_completion_समयout(&output->reg_update, msecs_to_jअगरfies(VFE_NEXT_SOF_MS));
	अगर (!समय)
		dev_err(vfe->camss->dev, "VFE reg update timeout\n");

	spin_lock_irqsave(&vfe->output_lock, flags);

	अगर (line->id != VFE_LINE_PIX) अणु
		vfe->ops_gen1->wm_frame_based(vfe, output->wm_idx[0], 0);
		vfe->ops_gen1->bus_disconnect_wm_from_rdi(vfe, output->wm_idx[0], line->id);
		vfe->ops_gen1->enable_irq_wm_line(vfe, output->wm_idx[0], line->id, 0);
		vfe->ops_gen1->set_cgc_override(vfe, output->wm_idx[0], 0);
		spin_unlock_irqrestore(&vfe->output_lock, flags);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < output->wm_num; i++) अणु
			vfe->ops_gen1->wm_line_based(vfe, output->wm_idx[i], शून्य, i, 0);
			vfe->ops_gen1->set_cgc_override(vfe, output->wm_idx[i], 0);
		पूर्ण

		vfe->ops_gen1->enable_irq_pix_line(vfe, 0, line->id, 0);
		vfe->ops_gen1->set_module_cfg(vfe, 0);
		vfe->ops_gen1->set_realign_cfg(vfe, line, 0);
		vfe->ops_gen1->set_xbar_cfg(vfe, output, 0);
		vfe->ops_gen1->set_camअगर_cmd(vfe, 0);

		spin_unlock_irqrestore(&vfe->output_lock, flags);

		vfe->ops_gen1->camअगर_रुको_क्रम_stop(vfe, vfe->camss->dev);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_gen1_disable - Disable streaming on VFE line
 * @line: VFE line
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक vfe_gen1_disable(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);

	vfe_disable_output(line);

	vfe_put_output(line);

	mutex_lock(&vfe->stream_lock);

	अगर (vfe->stream_count == 1)
		vfe->ops_gen1->bus_enable_wr_अगर(vfe, 0);

	vfe->stream_count--;

	mutex_unlock(&vfe->stream_lock);

	वापस 0;
पूर्ण

अटल व्योम vfe_output_init_addrs(काष्ठा vfe_device *vfe,
				  काष्ठा vfe_output *output, u8 sync,
				  काष्ठा vfe_line *line)
अणु
	u32 ping_addr;
	u32 pong_addr;
	अचिन्हित पूर्णांक i;

	output->gen1.active_buf = 0;

	क्रम (i = 0; i < output->wm_num; i++) अणु
		अगर (output->buf[0])
			ping_addr = output->buf[0]->addr[i];
		अन्यथा
			ping_addr = 0;

		अगर (output->buf[1])
			pong_addr = output->buf[1]->addr[i];
		अन्यथा
			pong_addr = ping_addr;

		vfe->ops_gen1->wm_set_ping_addr(vfe, output->wm_idx[i], ping_addr);
		vfe->ops_gen1->wm_set_pong_addr(vfe, output->wm_idx[i], pong_addr);
		अगर (sync)
			vfe->ops_gen1->bus_reload_wm(vfe, output->wm_idx[i]);
	पूर्ण
पूर्ण

अटल व्योम vfe_output_frame_drop(काष्ठा vfe_device *vfe,
				  काष्ठा vfe_output *output,
				  u32 drop_pattern)
अणु
	u8 drop_period;
	अचिन्हित पूर्णांक i;

	/* We need to toggle update period to be valid on next frame */
	output->drop_update_idx++;
	output->drop_update_idx %= VFE_FRAME_DROP_UPDATES;
	drop_period = VFE_FRAME_DROP_VAL + output->drop_update_idx;

	क्रम (i = 0; i < output->wm_num; i++) अणु
		vfe->ops_gen1->wm_set_framedrop_period(vfe, output->wm_idx[i], drop_period);
		vfe->ops_gen1->wm_set_framedrop_pattern(vfe, output->wm_idx[i], drop_pattern);
	पूर्ण

	vfe->ops->reg_update(vfe, container_of(output, काष्ठा vfe_line, output)->id);
पूर्ण

अटल पूर्णांक vfe_enable_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output = &line->output;
	स्थिर काष्ठा vfe_hw_ops *ops = vfe->ops;
	काष्ठा media_entity *sensor;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक frame_skip = 0;
	अचिन्हित पूर्णांक i;
	u16 ub_size;

	ub_size = vfe->ops_gen1->get_ub_size(vfe->id);
	अगर (!ub_size)
		वापस -EINVAL;

	sensor = camss_find_sensor(&line->subdev.entity);
	अगर (sensor) अणु
		काष्ठा v4l2_subdev *subdev = media_entity_to_v4l2_subdev(sensor);

		v4l2_subdev_call(subdev, sensor, g_skip_frames, &frame_skip);
		/* Max frame skip is 29 frames */
		अगर (frame_skip > VFE_FRAME_DROP_VAL - 1)
			frame_skip = VFE_FRAME_DROP_VAL - 1;
	पूर्ण

	spin_lock_irqsave(&vfe->output_lock, flags);

	ops->reg_update_clear(vfe, line->id);

	अगर (output->state != VFE_OUTPUT_RESERVED) अणु
		dev_err(vfe->camss->dev, "Output is not in reserved state %d\n", output->state);
		spin_unlock_irqrestore(&vfe->output_lock, flags);
		वापस -EINVAL;
	पूर्ण
	output->state = VFE_OUTPUT_IDLE;

	output->buf[0] = vfe_buf_get_pending(output);
	output->buf[1] = vfe_buf_get_pending(output);

	अगर (!output->buf[0] && output->buf[1]) अणु
		output->buf[0] = output->buf[1];
		output->buf[1] = शून्य;
	पूर्ण

	अगर (output->buf[0])
		output->state = VFE_OUTPUT_SINGLE;

	अगर (output->buf[1])
		output->state = VFE_OUTPUT_CONTINUOUS;

	चयन (output->state) अणु
	हाल VFE_OUTPUT_SINGLE:
		vfe_output_frame_drop(vfe, output, 1 << frame_skip);
		अवरोध;
	हाल VFE_OUTPUT_CONTINUOUS:
		vfe_output_frame_drop(vfe, output, 3 << frame_skip);
		अवरोध;
	शेष:
		vfe_output_frame_drop(vfe, output, 0);
		अवरोध;
	पूर्ण

	output->sequence = 0;
	output->gen1.रुको_sof = 0;
	output->रुको_reg_update = 0;
	reinit_completion(&output->sof);
	reinit_completion(&output->reg_update);

	vfe_output_init_addrs(vfe, output, 0, line);

	अगर (line->id != VFE_LINE_PIX) अणु
		vfe->ops_gen1->set_cgc_override(vfe, output->wm_idx[0], 1);
		vfe->ops_gen1->enable_irq_wm_line(vfe, output->wm_idx[0], line->id, 1);
		vfe->ops_gen1->bus_connect_wm_to_rdi(vfe, output->wm_idx[0], line->id);
		vfe->ops_gen1->wm_set_subsample(vfe, output->wm_idx[0]);
		vfe->ops_gen1->set_rdi_cid(vfe, line->id, 0);
		vfe->ops_gen1->wm_set_ub_cfg(vfe, output->wm_idx[0],
					    (ub_size + 1) * output->wm_idx[0], ub_size);
		vfe->ops_gen1->wm_frame_based(vfe, output->wm_idx[0], 1);
		vfe->ops_gen1->wm_enable(vfe, output->wm_idx[0], 1);
		vfe->ops_gen1->bus_reload_wm(vfe, output->wm_idx[0]);
	पूर्ण अन्यथा अणु
		ub_size /= output->wm_num;
		क्रम (i = 0; i < output->wm_num; i++) अणु
			vfe->ops_gen1->set_cgc_override(vfe, output->wm_idx[i], 1);
			vfe->ops_gen1->wm_set_subsample(vfe, output->wm_idx[i]);
			vfe->ops_gen1->wm_set_ub_cfg(vfe, output->wm_idx[i],
						     (ub_size + 1) * output->wm_idx[i], ub_size);
			vfe->ops_gen1->wm_line_based(vfe, output->wm_idx[i],
						     &line->video_out.active_fmt.fmt.pix_mp, i, 1);
			vfe->ops_gen1->wm_enable(vfe, output->wm_idx[i], 1);
			vfe->ops_gen1->bus_reload_wm(vfe, output->wm_idx[i]);
		पूर्ण
		vfe->ops_gen1->enable_irq_pix_line(vfe, 0, line->id, 1);
		vfe->ops_gen1->set_module_cfg(vfe, 1);
		vfe->ops_gen1->set_camअगर_cfg(vfe, line);
		vfe->ops_gen1->set_realign_cfg(vfe, line, 1);
		vfe->ops_gen1->set_xbar_cfg(vfe, output, 1);
		vfe->ops_gen1->set_demux_cfg(vfe, line);
		vfe->ops_gen1->set_scale_cfg(vfe, line);
		vfe->ops_gen1->set_crop_cfg(vfe, line);
		vfe->ops_gen1->set_clamp_cfg(vfe);
		vfe->ops_gen1->set_camअगर_cmd(vfe, 1);
	पूर्ण

	ops->reg_update(vfe, line->id);

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vfe_get_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output;
	काष्ठा v4l2_क्रमmat *f = &line->video_out.active_fmt;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक wm_idx;

	spin_lock_irqsave(&vfe->output_lock, flags);

	output = &line->output;
	अगर (output->state != VFE_OUTPUT_OFF) अणु
		dev_err(vfe->camss->dev, "Output is running\n");
		जाओ error;
	पूर्ण
	output->state = VFE_OUTPUT_RESERVED;

	output->gen1.active_buf = 0;

	चयन (f->fmt.pix_mp.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		output->wm_num = 2;
		अवरोध;
	शेष:
		output->wm_num = 1;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < output->wm_num; i++) अणु
		wm_idx = vfe_reserve_wm(vfe, line->id);
		अगर (wm_idx < 0) अणु
			dev_err(vfe->camss->dev, "Can not reserve wm\n");
			जाओ error_get_wm;
		पूर्ण
		output->wm_idx[i] = wm_idx;
	पूर्ण

	output->drop_update_idx = 0;

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;

error_get_wm:
	क्रम (i--; i >= 0; i--)
		vfe_release_wm(vfe, output->wm_idx[i]);
	output->state = VFE_OUTPUT_OFF;
error:
	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस -EINVAL;
पूर्ण

पूर्णांक vfe_gen1_enable(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	पूर्णांक ret;

	mutex_lock(&vfe->stream_lock);

	अगर (!vfe->stream_count) अणु
		vfe->ops_gen1->enable_irq_common(vfe);
		vfe->ops_gen1->bus_enable_wr_अगर(vfe, 1);
		vfe->ops_gen1->set_qos(vfe);
		vfe->ops_gen1->set_ds(vfe);
	पूर्ण

	vfe->stream_count++;

	mutex_unlock(&vfe->stream_lock);

	ret = vfe_get_output(line);
	अगर (ret < 0)
		जाओ error_get_output;

	ret = vfe_enable_output(line);
	अगर (ret < 0)
		जाओ error_enable_output;

	vfe->was_streaming = 1;

	वापस 0;

error_enable_output:
	vfe_put_output(line);

error_get_output:
	mutex_lock(&vfe->stream_lock);

	अगर (vfe->stream_count == 1)
		vfe->ops_gen1->bus_enable_wr_अगर(vfe, 0);

	vfe->stream_count--;

	mutex_unlock(&vfe->stream_lock);

	वापस ret;
पूर्ण

अटल व्योम vfe_output_update_ping_addr(काष्ठा vfe_device *vfe,
					काष्ठा vfe_output *output, u8 sync,
					काष्ठा vfe_line *line)
अणु
	u32 addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < output->wm_num; i++) अणु
		अगर (output->buf[0])
			addr = output->buf[0]->addr[i];
		अन्यथा
			addr = 0;

		vfe->ops_gen1->wm_set_ping_addr(vfe, output->wm_idx[i], addr);
		अगर (sync)
			vfe->ops_gen1->bus_reload_wm(vfe, output->wm_idx[i]);
	पूर्ण
पूर्ण

अटल व्योम vfe_output_update_pong_addr(काष्ठा vfe_device *vfe,
					काष्ठा vfe_output *output, u8 sync,
					काष्ठा vfe_line *line)
अणु
	u32 addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < output->wm_num; i++) अणु
		अगर (output->buf[1])
			addr = output->buf[1]->addr[i];
		अन्यथा
			addr = 0;

		vfe->ops_gen1->wm_set_pong_addr(vfe, output->wm_idx[i], addr);
		अगर (sync)
			vfe->ops_gen1->bus_reload_wm(vfe, output->wm_idx[i]);
	पूर्ण
पूर्ण

अटल व्योम vfe_buf_update_wm_on_next(काष्ठा vfe_device *vfe,
				      काष्ठा vfe_output *output)
अणु
	चयन (output->state) अणु
	हाल VFE_OUTPUT_CONTINUOUS:
		vfe_output_frame_drop(vfe, output, 3);
		अवरोध;
	हाल VFE_OUTPUT_SINGLE:
	शेष:
		dev_err_ratelimited(vfe->camss->dev,
				    "Next buf in wrong state! %d\n",
				    output->state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vfe_buf_update_wm_on_last(काष्ठा vfe_device *vfe,
				      काष्ठा vfe_output *output)
अणु
	चयन (output->state) अणु
	हाल VFE_OUTPUT_CONTINUOUS:
		output->state = VFE_OUTPUT_SINGLE;
		vfe_output_frame_drop(vfe, output, 1);
		अवरोध;
	हाल VFE_OUTPUT_SINGLE:
		output->state = VFE_OUTPUT_STOPPING;
		vfe_output_frame_drop(vfe, output, 0);
		अवरोध;
	शेष:
		dev_err_ratelimited(vfe->camss->dev,
				    "Last buff in wrong state! %d\n",
				    output->state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vfe_buf_update_wm_on_new(काष्ठा vfe_device *vfe,
				     काष्ठा vfe_output *output,
				     काष्ठा camss_buffer *new_buf,
				     काष्ठा vfe_line *line)
अणु
	पूर्णांक inactive_idx;

	चयन (output->state) अणु
	हाल VFE_OUTPUT_SINGLE:
		inactive_idx = !output->gen1.active_buf;

		अगर (!output->buf[inactive_idx]) अणु
			output->buf[inactive_idx] = new_buf;

			अगर (inactive_idx)
				vfe_output_update_pong_addr(vfe, output, 0, line);
			अन्यथा
				vfe_output_update_ping_addr(vfe, output, 0, line);

			vfe_output_frame_drop(vfe, output, 3);
			output->state = VFE_OUTPUT_CONTINUOUS;
		पूर्ण अन्यथा अणु
			vfe_buf_add_pending(output, new_buf);
			dev_err_ratelimited(vfe->camss->dev,
					    "Inactive buffer is busy\n");
		पूर्ण
		अवरोध;

	हाल VFE_OUTPUT_IDLE:
		अगर (!output->buf[0]) अणु
			output->buf[0] = new_buf;

			vfe_output_init_addrs(vfe, output, 1, line);
			vfe_output_frame_drop(vfe, output, 1);

			output->state = VFE_OUTPUT_SINGLE;
		पूर्ण अन्यथा अणु
			vfe_buf_add_pending(output, new_buf);
			dev_err_ratelimited(vfe->camss->dev,
					    "Output idle with buffer set!\n");
		पूर्ण
		अवरोध;

	हाल VFE_OUTPUT_CONTINUOUS:
	शेष:
		vfe_buf_add_pending(output, new_buf);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * vfe_isr_halt_ack - Process halt ack
 * @vfe: VFE Device
 */
अटल व्योम vfe_isr_halt_ack(काष्ठा vfe_device *vfe)
अणु
	complete(&vfe->halt_complete);
	vfe->ops_gen1->halt_clear(vfe);
पूर्ण

/*
 * vfe_isr_sof - Process start of frame पूर्णांकerrupt
 * @vfe: VFE Device
 * @line_id: VFE line
 */
अटल व्योम vfe_isr_sof(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vfe->output_lock, flags);
	output = &vfe->line[line_id].output;
	अगर (output->gen1.रुको_sof) अणु
		output->gen1.रुको_sof = 0;
		complete(&output->sof);
	पूर्ण
	spin_unlock_irqrestore(&vfe->output_lock, flags);
पूर्ण

/*
 * vfe_isr_reg_update - Process reg update पूर्णांकerrupt
 * @vfe: VFE Device
 * @line_id: VFE line
 */
अटल व्योम vfe_isr_reg_update(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	काष्ठा vfe_output *output;
	काष्ठा vfe_line *line = &vfe->line[line_id];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vfe->output_lock, flags);
	vfe->ops->reg_update_clear(vfe, line_id);

	output = &line->output;

	अगर (output->रुको_reg_update) अणु
		output->रुको_reg_update = 0;
		complete(&output->reg_update);
		spin_unlock_irqrestore(&vfe->output_lock, flags);
		वापस;
	पूर्ण

	अगर (output->state == VFE_OUTPUT_STOPPING) अणु
		/* Release last buffer when hw is idle */
		अगर (output->last_buffer) अणु
			vb2_buffer_करोne(&output->last_buffer->vb.vb2_buf,
					VB2_BUF_STATE_DONE);
			output->last_buffer = शून्य;
		पूर्ण
		output->state = VFE_OUTPUT_IDLE;

		/* Buffers received in stopping state are queued in */
		/* dma pending queue, start next capture here */

		output->buf[0] = vfe_buf_get_pending(output);
		output->buf[1] = vfe_buf_get_pending(output);

		अगर (!output->buf[0] && output->buf[1]) अणु
			output->buf[0] = output->buf[1];
			output->buf[1] = शून्य;
		पूर्ण

		अगर (output->buf[0])
			output->state = VFE_OUTPUT_SINGLE;

		अगर (output->buf[1])
			output->state = VFE_OUTPUT_CONTINUOUS;

		चयन (output->state) अणु
		हाल VFE_OUTPUT_SINGLE:
			vfe_output_frame_drop(vfe, output, 2);
			अवरोध;
		हाल VFE_OUTPUT_CONTINUOUS:
			vfe_output_frame_drop(vfe, output, 3);
			अवरोध;
		शेष:
			vfe_output_frame_drop(vfe, output, 0);
			अवरोध;
		पूर्ण

		vfe_output_init_addrs(vfe, output, 1, &vfe->line[line_id]);
	पूर्ण

	spin_unlock_irqrestore(&vfe->output_lock, flags);
पूर्ण

/*
 * vfe_isr_wm_करोne - Process ग_लिखो master करोne पूर्णांकerrupt
 * @vfe: VFE Device
 * @wm: Write master id
 */
अटल व्योम vfe_isr_wm_करोne(काष्ठा vfe_device *vfe, u8 wm)
अणु
	काष्ठा camss_buffer *पढ़ोy_buf;
	काष्ठा vfe_output *output;
	dma_addr_t *new_addr;
	अचिन्हित दीर्घ flags;
	u32 active_index;
	u64 ts = kसमय_get_ns();
	अचिन्हित पूर्णांक i;

	active_index = vfe->ops_gen1->wm_get_ping_pong_status(vfe, wm);

	spin_lock_irqsave(&vfe->output_lock, flags);

	अगर (vfe->wm_output_map[wm] == VFE_LINE_NONE) अणु
		dev_err_ratelimited(vfe->camss->dev,
				    "Received wm done for unmapped index\n");
		जाओ out_unlock;
	पूर्ण
	output = &vfe->line[vfe->wm_output_map[wm]].output;

	अगर (output->gen1.active_buf == active_index && 0) अणु
		dev_err_ratelimited(vfe->camss->dev,
				    "Active buffer mismatch!\n");
		जाओ out_unlock;
	पूर्ण
	output->gen1.active_buf = active_index;

	पढ़ोy_buf = output->buf[!active_index];
	अगर (!पढ़ोy_buf) अणु
		dev_err_ratelimited(vfe->camss->dev,
				    "Missing ready buf %d %d!\n",
				    !active_index, output->state);
		जाओ out_unlock;
	पूर्ण

	पढ़ोy_buf->vb.vb2_buf.बारtamp = ts;
	पढ़ोy_buf->vb.sequence = output->sequence++;

	/* Get next buffer */
	output->buf[!active_index] = vfe_buf_get_pending(output);
	अगर (!output->buf[!active_index]) अणु
		/* No next buffer - set same address */
		new_addr = पढ़ोy_buf->addr;
		vfe_buf_update_wm_on_last(vfe, output);
	पूर्ण अन्यथा अणु
		new_addr = output->buf[!active_index]->addr;
		vfe_buf_update_wm_on_next(vfe, output);
	पूर्ण

	अगर (active_index)
		क्रम (i = 0; i < output->wm_num; i++)
			vfe->ops_gen1->wm_set_ping_addr(vfe, output->wm_idx[i], new_addr[i]);
	अन्यथा
		क्रम (i = 0; i < output->wm_num; i++)
			vfe->ops_gen1->wm_set_pong_addr(vfe, output->wm_idx[i], new_addr[i]);

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	अगर (output->state == VFE_OUTPUT_STOPPING)
		output->last_buffer = पढ़ोy_buf;
	अन्यथा
		vb2_buffer_करोne(&पढ़ोy_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	वापस;

out_unlock:
	spin_unlock_irqrestore(&vfe->output_lock, flags);
पूर्ण

/*
 * vfe_queue_buffer - Add empty buffer
 * @vid: Video device काष्ठाure
 * @buf: Buffer to be enqueued
 *
 * Add an empty buffer - depending on the current number of buffers it will be
 * put in pending buffer queue or directly given to the hardware to be filled.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_queue_buffer(काष्ठा camss_video *vid, काष्ठा camss_buffer *buf)
अणु
	काष्ठा vfe_line *line = container_of(vid, काष्ठा vfe_line, video_out);
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;

	output = &line->output;

	spin_lock_irqsave(&vfe->output_lock, flags);

	vfe_buf_update_wm_on_new(vfe, output, buf, line);

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;
पूर्ण

#घोषणा CALC_WORD(width, M, N) (((width) * (M) + (N) - 1) / (N))

पूर्णांक vfe_word_per_line(u32 क्रमmat, u32 width)
अणु
	पूर्णांक val = 0;

	चयन (क्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		val = CALC_WORD(width, 1, 8);
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
		val = CALC_WORD(width, 2, 8);
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

स्थिर काष्ठा vfe_isr_ops vfe_isr_ops_gen1 = अणु
	.reset_ack = vfe_isr_reset_ack,
	.halt_ack = vfe_isr_halt_ack,
	.reg_update = vfe_isr_reg_update,
	.sof = vfe_isr_sof,
	.comp_करोne = vfe_isr_comp_करोne,
	.wm_करोne = vfe_isr_wm_करोne,
पूर्ण;

स्थिर काष्ठा camss_video_ops vfe_video_ops_gen1 = अणु
	.queue_buffer = vfe_queue_buffer,
	.flush_buffers = vfe_flush_buffers,
पूर्ण;
