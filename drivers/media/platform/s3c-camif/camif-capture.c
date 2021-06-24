<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * s3c24xx/s3c64xx SoC series Camera Interface (CAMIF) driver
 *
 * Copyright (C) 2012 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 * Copyright (C) 2012 Tomasz Figa <tomasz.figa@gmail.com>
 *
 * Based on drivers/media/platक्रमm/s5p-fimc,
 * Copyright (C) 2010 - 2012 Samsung Electronics Co., Ltd.
*/
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "camif-core.h"
#समावेश "camif-regs.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

/* Locking: called with vp->camअगर->slock spinlock held */
अटल व्योम camअगर_cfg_video_path(काष्ठा camअगर_vp *vp)
अणु
	WARN_ON(s3c_camअगर_get_scaler_config(vp, &vp->scaler));
	camअगर_hw_set_scaler(vp);
	camअगर_hw_set_flip(vp);
	camअगर_hw_set_target_क्रमmat(vp);
	camअगर_hw_set_output_dma(vp);
पूर्ण

अटल व्योम camअगर_prepare_dma_offset(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_frame *f = &vp->out_frame;

	f->dma_offset.initial = f->rect.top * f->f_width + f->rect.left;
	f->dma_offset.line = f->f_width - (f->rect.left + f->rect.width);

	pr_debug("dma_offset: initial: %d, line: %d\n",
		 f->dma_offset.initial, f->dma_offset.line);
पूर्ण

/* Locking: called with camअगर->slock spinlock held */
अटल पूर्णांक s3c_camअगर_hw_init(काष्ठा camअगर_dev *camअगर, काष्ठा camअगर_vp *vp)
अणु
	स्थिर काष्ठा s3c_camअगर_variant *variant = camअगर->variant;

	अगर (camअगर->sensor.sd == शून्य || vp->out_fmt == शून्य)
		वापस -EINVAL;

	अगर (variant->ip_revision == S3C244X_CAMIF_IP_REV)
		camअगर_hw_clear_fअगरo_overflow(vp);
	camअगर_hw_set_camera_bus(camअगर);
	camअगर_hw_set_source_क्रमmat(camअगर);
	camअगर_hw_set_camera_crop(camअगर);
	camअगर_hw_set_test_pattern(camअगर, camअगर->test_pattern);
	अगर (variant->has_img_effect)
		camअगर_hw_set_effect(camअगर, camअगर->colorfx,
				camअगर->colorfx_cr, camअगर->colorfx_cb);
	अगर (variant->ip_revision == S3C6410_CAMIF_IP_REV)
		camअगर_hw_set_input_path(vp);
	camअगर_cfg_video_path(vp);
	vp->state &= ~ST_VP_CONFIG;

	वापस 0;
पूर्ण

/*
 * Initialize the video path, only up from the scaler stage. The camera
 * input पूर्णांकerface set up is skipped. This is useful to enable one of the
 * video paths when the other is alपढ़ोy running.
 * Locking: called with camअगर->slock spinlock held.
 */
अटल पूर्णांक s3c_camअगर_hw_vp_init(काष्ठा camअगर_dev *camअगर, काष्ठा camअगर_vp *vp)
अणु
	अचिन्हित पूर्णांक ip_rev = camअगर->variant->ip_revision;

	अगर (vp->out_fmt == शून्य)
		वापस -EINVAL;

	camअगर_prepare_dma_offset(vp);
	अगर (ip_rev == S3C244X_CAMIF_IP_REV)
		camअगर_hw_clear_fअगरo_overflow(vp);
	camअगर_cfg_video_path(vp);
	vp->state &= ~ST_VP_CONFIG;
	वापस 0;
पूर्ण

अटल पूर्णांक sensor_set_घातer(काष्ठा camअगर_dev *camअगर, पूर्णांक on)
अणु
	काष्ठा cam_sensor *sensor = &camअगर->sensor;
	पूर्णांक err = 0;

	अगर (camअगर->sensor.घातer_count == !on)
		err = v4l2_subdev_call(sensor->sd, core, s_घातer, on);
	अगर (err == -ENOIOCTLCMD)
		err = 0;
	अगर (!err)
		sensor->घातer_count += on ? 1 : -1;

	pr_debug("on: %d, power_count: %d, err: %d\n",
		 on, sensor->घातer_count, err);

	वापस err;
पूर्ण

अटल पूर्णांक sensor_set_streaming(काष्ठा camअगर_dev *camअगर, पूर्णांक on)
अणु
	काष्ठा cam_sensor *sensor = &camअगर->sensor;
	पूर्णांक err = 0;

	अगर (camअगर->sensor.stream_count == !on)
		err = v4l2_subdev_call(sensor->sd, video, s_stream, on);
	अगर (!err)
		sensor->stream_count += on ? 1 : -1;

	pr_debug("on: %d, stream_count: %d, err: %d\n",
		 on, sensor->stream_count, err);

	वापस err;
पूर्ण

/*
 * Reinitialize the driver so it is पढ़ोy to start streaming again.
 * Return any buffers to vb2, perक्रमm CAMIF software reset and
 * turn off streaming at the data pipeline (sensor) अगर required.
 */
अटल पूर्णांक camअगर_reinitialize(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा camअगर_buffer *buf;
	अचिन्हित दीर्घ flags;
	bool streaming;

	spin_lock_irqsave(&camअगर->slock, flags);
	streaming = vp->state & ST_VP_SENSOR_STREAMING;

	vp->state &= ~(ST_VP_PENDING | ST_VP_RUNNING | ST_VP_OFF |
		       ST_VP_ABORTING | ST_VP_STREAMING |
		       ST_VP_SENSOR_STREAMING | ST_VP_LASTIRQ);

	/* Release unused buffers */
	जबतक (!list_empty(&vp->pending_buf_q)) अणु
		buf = camअगर_pending_queue_pop(vp);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	जबतक (!list_empty(&vp->active_buf_q)) अणु
		buf = camअगर_active_queue_pop(vp);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	spin_unlock_irqrestore(&camअगर->slock, flags);

	अगर (!streaming)
		वापस 0;

	वापस sensor_set_streaming(camअगर, 0);
पूर्ण

अटल bool s3c_vp_active(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&camअगर->slock, flags);
	ret = (vp->state & ST_VP_RUNNING) || (vp->state & ST_VP_PENDING);
	spin_unlock_irqrestore(&camअगर->slock, flags);

	वापस ret;
पूर्ण

अटल bool camअगर_is_streaming(काष्ठा camअगर_dev *camअगर)
अणु
	अचिन्हित दीर्घ flags;
	bool status;

	spin_lock_irqsave(&camअगर->slock, flags);
	status = camअगर->stream_count > 0;
	spin_unlock_irqrestore(&camअगर->slock, flags);

	वापस status;
पूर्ण

अटल पूर्णांक camअगर_stop_capture(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!s3c_vp_active(vp))
		वापस 0;

	spin_lock_irqsave(&camअगर->slock, flags);
	vp->state &= ~(ST_VP_OFF | ST_VP_LASTIRQ);
	vp->state |= ST_VP_ABORTING;
	spin_unlock_irqrestore(&camअगर->slock, flags);

	ret = रुको_event_समयout(vp->irq_queue,
			   !(vp->state & ST_VP_ABORTING),
			   msecs_to_jअगरfies(CAMIF_STOP_TIMEOUT));

	spin_lock_irqsave(&camअगर->slock, flags);

	अगर (ret == 0 && !(vp->state & ST_VP_OFF)) अणु
		/* Timed out, क्रमcibly stop capture */
		vp->state &= ~(ST_VP_OFF | ST_VP_ABORTING |
			       ST_VP_LASTIRQ);

		camअगर_hw_disable_capture(vp);
		camअगर_hw_enable_scaler(vp, false);
	पूर्ण

	spin_unlock_irqrestore(&camअगर->slock, flags);

	वापस camअगर_reinitialize(vp);
पूर्ण

अटल पूर्णांक camअगर_prepare_addr(काष्ठा camअगर_vp *vp, काष्ठा vb2_buffer *vb,
			      काष्ठा camअगर_addr *paddr)
अणु
	काष्ठा camअगर_frame *frame = &vp->out_frame;
	u32 pix_size;

	अगर (vb == शून्य || frame == शून्य)
		वापस -EINVAL;

	pix_size = frame->rect.width * frame->rect.height;

	pr_debug("colplanes: %d, pix_size: %u\n",
		 vp->out_fmt->colplanes, pix_size);

	paddr->y = vb2_dma_contig_plane_dma_addr(vb, 0);

	चयन (vp->out_fmt->colplanes) अणु
	हाल 1:
		paddr->cb = 0;
		paddr->cr = 0;
		अवरोध;
	हाल 2:
		/* decompose Y पूर्णांकo Y/Cb */
		paddr->cb = (u32)(paddr->y + pix_size);
		paddr->cr = 0;
		अवरोध;
	हाल 3:
		paddr->cb = (u32)(paddr->y + pix_size);
		/* decompose Y पूर्णांकo Y/Cb/Cr */
		अगर (vp->out_fmt->color == IMG_FMT_YCBCR422P)
			paddr->cr = (u32)(paddr->cb + (pix_size >> 1));
		अन्यथा /* 420 */
			paddr->cr = (u32)(paddr->cb + (pix_size >> 2));

		अगर (vp->out_fmt->color == IMG_FMT_YCRCB420)
			swap(paddr->cb, paddr->cr);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pr_debug("DMA address: y: %pad  cb: %pad cr: %pad\n",
		 &paddr->y, &paddr->cb, &paddr->cr);

	वापस 0;
पूर्ण

irqवापस_t s3c_camअगर_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा camअगर_vp *vp = priv;
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	अचिन्हित पूर्णांक ip_rev = camअगर->variant->ip_revision;
	अचिन्हित पूर्णांक status;

	spin_lock(&camअगर->slock);

	अगर (ip_rev == S3C6410_CAMIF_IP_REV)
		camअगर_hw_clear_pending_irq(vp);

	status = camअगर_hw_get_status(vp);

	अगर (ip_rev == S3C244X_CAMIF_IP_REV && (status & CISTATUS_OVF_MASK)) अणु
		camअगर_hw_clear_fअगरo_overflow(vp);
		जाओ unlock;
	पूर्ण

	अगर (vp->state & ST_VP_ABORTING) अणु
		अगर (vp->state & ST_VP_OFF) अणु
			/* Last IRQ */
			vp->state &= ~(ST_VP_OFF | ST_VP_ABORTING |
				       ST_VP_LASTIRQ);
			wake_up(&vp->irq_queue);
			जाओ unlock;
		पूर्ण अन्यथा अगर (vp->state & ST_VP_LASTIRQ) अणु
			camअगर_hw_disable_capture(vp);
			camअगर_hw_enable_scaler(vp, false);
			camअगर_hw_set_lastirq(vp, false);
			vp->state |= ST_VP_OFF;
		पूर्ण अन्यथा अणु
			/* Disable capture, enable last IRQ */
			camअगर_hw_set_lastirq(vp, true);
			vp->state |= ST_VP_LASTIRQ;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&vp->pending_buf_q) && (vp->state & ST_VP_RUNNING) &&
	    !list_empty(&vp->active_buf_q)) अणु
		अचिन्हित पूर्णांक index;
		काष्ठा camअगर_buffer *vbuf;
		/*
		 * Get previous DMA ग_लिखो buffer index:
		 * 0 => DMA buffer 0, 2;
		 * 1 => DMA buffer 1, 3.
		 */
		index = (CISTATUS_FRAMECNT(status) + 2) & 1;
		vbuf = camअगर_active_queue_peek(vp, index);

		अगर (!WARN_ON(vbuf == शून्य)) अणु
			/* Dequeue a filled buffer */
			vbuf->vb.vb2_buf.बारtamp = kसमय_get_ns();
			vbuf->vb.sequence = vp->frame_sequence++;
			vb2_buffer_करोne(&vbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);

			/* Set up an empty buffer at the DMA engine */
			vbuf = camअगर_pending_queue_pop(vp);
			vbuf->index = index;
			camअगर_hw_set_output_addr(vp, &vbuf->paddr, index);
			camअगर_hw_set_output_addr(vp, &vbuf->paddr, index + 2);

			/* Scheduled in H/W, add to the queue */
			camअगर_active_queue_add(vp, vbuf);
		पूर्ण
	पूर्ण अन्यथा अगर (!(vp->state & ST_VP_ABORTING) &&
		   (vp->state & ST_VP_PENDING))  अणु
		vp->state |= ST_VP_RUNNING;
	पूर्ण

	अगर (vp->state & ST_VP_CONFIG) अणु
		camअगर_prepare_dma_offset(vp);
		camअगर_hw_set_camera_crop(camअगर);
		camअगर_hw_set_scaler(vp);
		camअगर_hw_set_flip(vp);
		camअगर_hw_set_test_pattern(camअगर, camअगर->test_pattern);
		अगर (camअगर->variant->has_img_effect)
			camअगर_hw_set_effect(camअगर, camअगर->colorfx,
				    camअगर->colorfx_cr, camअगर->colorfx_cb);
		vp->state &= ~ST_VP_CONFIG;
	पूर्ण
unlock:
	spin_unlock(&camअगर->slock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा camअगर_vp *vp = vb2_get_drv_priv(vq);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * We assume the codec capture path is always activated
	 * first, beक्रमe the preview path starts streaming.
	 * This is required to aव्योम पूर्णांकernal FIFO overflow and
	 * a need क्रम CAMIF software reset.
	 */
	spin_lock_irqsave(&camअगर->slock, flags);

	अगर (camअगर->stream_count == 0) अणु
		camअगर_hw_reset(camअगर);
		ret = s3c_camअगर_hw_init(camअगर, vp);
	पूर्ण अन्यथा अणु
		ret = s3c_camअगर_hw_vp_init(camअगर, vp);
	पूर्ण
	spin_unlock_irqrestore(&camअगर->slock, flags);

	अगर (ret < 0) अणु
		camअगर_reinitialize(vp);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&camअगर->slock, flags);
	vp->frame_sequence = 0;
	vp->state |= ST_VP_PENDING;

	अगर (!list_empty(&vp->pending_buf_q) &&
	    (!(vp->state & ST_VP_STREAMING) ||
	     !(vp->state & ST_VP_SENSOR_STREAMING))) अणु

		camअगर_hw_enable_scaler(vp, vp->scaler.enable);
		camअगर_hw_enable_capture(vp);
		vp->state |= ST_VP_STREAMING;

		अगर (!(vp->state & ST_VP_SENSOR_STREAMING)) अणु
			vp->state |= ST_VP_SENSOR_STREAMING;
			spin_unlock_irqrestore(&camअगर->slock, flags);
			ret = sensor_set_streaming(camअगर, 1);
			अगर (ret)
				v4l2_err(&vp->vdev, "Sensor s_stream failed\n");
			अगर (debug)
				camअगर_hw_dump_regs(camअगर, __func__);

			वापस ret;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&camअगर->slock, flags);
	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा camअगर_vp *vp = vb2_get_drv_priv(vq);
	camअगर_stop_capture(vp);
पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा camअगर_vp *vp = vb2_get_drv_priv(vq);
	काष्ठा camअगर_frame *frame = &vp->out_frame;
	स्थिर काष्ठा camअगर_fmt *fmt = vp->out_fmt;
	अचिन्हित पूर्णांक size;

	अगर (fmt == शून्य)
		वापस -EINVAL;

	size = (frame->f_width * frame->f_height * fmt->depth) / 8;

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;

	pr_debug("size: %u\n", sizes[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा camअगर_vp *vp = vb2_get_drv_priv(vb->vb2_queue);

	अगर (vp->out_fmt == शून्य)
		वापस -EINVAL;

	अगर (vb2_plane_size(vb, 0) < vp->payload) अणु
		v4l2_err(&vp->vdev, "buffer too small: %lu, required: %u\n",
			 vb2_plane_size(vb, 0), vp->payload);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, vp->payload);

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा camअगर_buffer *buf = container_of(vbuf, काष्ठा camअगर_buffer, vb);
	काष्ठा camअगर_vp *vp = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&camअगर->slock, flags);
	WARN_ON(camअगर_prepare_addr(vp, &buf->vb.vb2_buf, &buf->paddr));

	अगर (!(vp->state & ST_VP_STREAMING) && vp->active_buffers < 2) अणु
		/* Schedule an empty buffer in H/W */
		buf->index = vp->buf_index;

		camअगर_hw_set_output_addr(vp, &buf->paddr, buf->index);
		camअगर_hw_set_output_addr(vp, &buf->paddr, buf->index + 2);

		camअगर_active_queue_add(vp, buf);
		vp->buf_index = !vp->buf_index;
	पूर्ण अन्यथा अणु
		camअगर_pending_queue_add(vp, buf);
	पूर्ण

	अगर (vb2_is_streaming(&vp->vb_queue) && !list_empty(&vp->pending_buf_q)
		&& !(vp->state & ST_VP_STREAMING)) अणु

		vp->state |= ST_VP_STREAMING;
		camअगर_hw_enable_scaler(vp, vp->scaler.enable);
		camअगर_hw_enable_capture(vp);
		spin_unlock_irqrestore(&camअगर->slock, flags);

		अगर (!(vp->state & ST_VP_SENSOR_STREAMING)) अणु
			अगर (sensor_set_streaming(camअगर, 1) == 0)
				vp->state |= ST_VP_SENSOR_STREAMING;
			अन्यथा
				v4l2_err(&vp->vdev, "Sensor s_stream failed\n");

			अगर (debug)
				camअगर_hw_dump_regs(camअगर, __func__);
		पूर्ण
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&camअगर->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops s3c_camअगर_qops = अणु
	.queue_setup	 = queue_setup,
	.buf_prepare	 = buffer_prepare,
	.buf_queue	 = buffer_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming	 = stop_streaming,
पूर्ण;

अटल पूर्णांक s3c_camअगर_खोलो(काष्ठा file *file)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	पूर्णांक ret;

	pr_debug("[vp%d] state: %#x,  owner: %p, pid: %d\n", vp->id,
		 vp->state, vp->owner, task_pid_nr(current));

	अगर (mutex_lock_पूर्णांकerruptible(&camअगर->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ unlock;

	ret = pm_runसमय_get_sync(camअगर->dev);
	अगर (ret < 0)
		जाओ err_pm;

	ret = sensor_set_घातer(camअगर, 1);
	अगर (!ret)
		जाओ unlock;

	pm_runसमय_put(camअगर->dev);
err_pm:
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&camअगर->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_बंद(काष्ठा file *file)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	पूर्णांक ret;

	pr_debug("[vp%d] state: %#x, owner: %p, pid: %d\n", vp->id,
		 vp->state, vp->owner, task_pid_nr(current));

	mutex_lock(&camअगर->lock);

	अगर (vp->owner == file->निजी_data) अणु
		camअगर_stop_capture(vp);
		vb2_queue_release(&vp->vb_queue);
		vp->owner = शून्य;
	पूर्ण

	sensor_set_घातer(camअगर, 0);

	pm_runसमय_put(camअगर->dev);
	ret = v4l2_fh_release(file);

	mutex_unlock(&camअगर->lock);
	वापस ret;
पूर्ण

अटल __poll_t s3c_camअगर_poll(काष्ठा file *file,
				   काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	__poll_t ret;

	mutex_lock(&camअगर->lock);
	अगर (vp->owner && vp->owner != file->निजी_data)
		ret = EPOLLERR;
	अन्यथा
		ret = vb2_poll(&vp->vb_queue, file, रुको);

	mutex_unlock(&camअगर->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	पूर्णांक ret;

	अगर (vp->owner && vp->owner != file->निजी_data)
		ret = -EBUSY;
	अन्यथा
		ret = vb2_mmap(&vp->vb_queue, vma);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations s3c_camअगर_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= s3c_camअगर_खोलो,
	.release	= s3c_camअगर_बंद,
	.poll		= s3c_camअगर_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= s3c_camअगर_mmap,
पूर्ण;

/*
 * Video node IOCTLs
 */

अटल पूर्णांक s3c_camअगर_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_capability *cap)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);

	strscpy(cap->driver, S3C_CAMIF_DRIVER_NAME, माप(cap->driver));
	strscpy(cap->card, S3C_CAMIF_DRIVER_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s.%d",
		 dev_name(vp->camअगर->dev), vp->id);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				       काष्ठा v4l2_input *input)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा v4l2_subdev *sensor = vp->camअगर->sensor.sd;

	अगर (input->index || sensor == शून्य)
		वापस -EINVAL;

	input->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(input->name, sensor->name, माप(input->name));
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_s_input(काष्ठा file *file, व्योम *priv,
				    अचिन्हित पूर्णांक i)
अणु
	वापस i == 0 ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_g_input(काष्ठा file *file, व्योम *priv,
				    अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	स्थिर काष्ठा camअगर_fmt *fmt;

	fmt = s3c_camअगर_find_क्रमmat(vp, शून्य, f->index);
	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_g_fmt(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा camअगर_frame *frame = &vp->out_frame;
	स्थिर काष्ठा camअगर_fmt *fmt = vp->out_fmt;

	pix->bytesperline = frame->f_width * fmt->ybpp;
	pix->sizeimage = vp->payload;

	pix->pixelक्रमmat = fmt->fourcc;
	pix->width = frame->f_width;
	pix->height = frame->f_height;
	pix->field = V4L2_FIELD_NONE;
	pix->colorspace = V4L2_COLORSPACE_JPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक __camअगर_video_try_क्रमmat(काष्ठा camअगर_vp *vp,
				    काष्ठा v4l2_pix_क्रमmat *pix,
				    स्थिर काष्ठा camअगर_fmt **ffmt)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा v4l2_rect *crop = &camअगर->camअगर_crop;
	अचिन्हित पूर्णांक wmin, hmin, sc_hrmax, sc_vrmax;
	स्थिर काष्ठा vp_pix_limits *pix_lim;
	स्थिर काष्ठा camअगर_fmt *fmt;

	fmt = s3c_camअगर_find_क्रमmat(vp, &pix->pixelक्रमmat, 0);

	अगर (WARN_ON(fmt == शून्य))
		वापस -EINVAL;

	अगर (ffmt)
		*ffmt = fmt;

	pix_lim = &camअगर->variant->vp_pix_limits[vp->id];

	pr_debug("fmt: %ux%u, crop: %ux%u, bytesperline: %u\n",
		 pix->width, pix->height, crop->width, crop->height,
		 pix->bytesperline);
	/*
	 * Calculate minimum width and height according to the configured
	 * camera input पूर्णांकerface crop rectangle and the resizer's capabilities.
	 */
	sc_hrmax = min(SCALER_MAX_RATIO, 1 << (ffs(crop->width) - 3));
	sc_vrmax = min(SCALER_MAX_RATIO, 1 << (ffs(crop->height) - 1));

	wmin = max_t(u32, pix_lim->min_out_width, crop->width / sc_hrmax);
	wmin = round_up(wmin, pix_lim->out_width_align);
	hmin = max_t(u32, 8, crop->height / sc_vrmax);
	hmin = round_up(hmin, 8);

	v4l_bound_align_image(&pix->width, wmin, pix_lim->max_sc_out_width,
			      ffs(pix_lim->out_width_align) - 1,
			      &pix->height, hmin, pix_lim->max_height, 0, 0);

	pix->bytesperline = pix->width * fmt->ybpp;
	pix->sizeimage = (pix->width * pix->height * fmt->depth) / 8;
	pix->pixelक्रमmat = fmt->fourcc;
	pix->colorspace = V4L2_COLORSPACE_JPEG;
	pix->field = V4L2_FIELD_NONE;

	pr_debug("%ux%u, wmin: %d, hmin: %d, sc_hrmax: %d, sc_vrmax: %d\n",
		 pix->width, pix->height, wmin, hmin, sc_hrmax, sc_vrmax);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_try_fmt(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	वापस __camअगर_video_try_क्रमmat(vp, &f->fmt.pix, शून्य);
पूर्ण

अटल पूर्णांक s3c_camअगर_vidioc_s_fmt(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_frame *out_frame = &vp->out_frame;
	स्थिर काष्ठा camअगर_fmt *fmt = शून्य;
	पूर्णांक ret;

	pr_debug("[vp%d]\n", vp->id);

	अगर (vb2_is_busy(&vp->vb_queue))
		वापस -EBUSY;

	ret = __camअगर_video_try_क्रमmat(vp, &f->fmt.pix, &fmt);
	अगर (ret < 0)
		वापस ret;

	vp->out_fmt = fmt;
	vp->payload = pix->sizeimage;
	out_frame->f_width = pix->width;
	out_frame->f_height = pix->height;

	/* Reset composition rectangle */
	out_frame->rect.width = pix->width;
	out_frame->rect.height = pix->height;
	out_frame->rect.left = 0;
	out_frame->rect.top = 0;

	अगर (vp->owner == शून्य)
		vp->owner = priv;

	pr_debug("%ux%u. payload: %u. fmt: 0x%08x. %d %d. sizeimage: %d. bpl: %d\n",
		 out_frame->f_width, out_frame->f_height, vp->payload,
		 fmt->fourcc, pix->width * pix->height * fmt->depth,
		 fmt->depth, pix->sizeimage, pix->bytesperline);

	वापस 0;
पूर्ण

/* Only check pixel क्रमmats at the sensor and the camअगर subdev pads */
अटल पूर्णांक camअगर_pipeline_validate(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा v4l2_subdev_क्रमmat src_fmt;
	काष्ठा media_pad *pad;
	पूर्णांक ret;

	/* Retrieve क्रमmat at the sensor subdev source pad */
	pad = media_entity_remote_pad(&camअगर->pads[0]);
	अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
		वापस -EPIPE;

	src_fmt.pad = pad->index;
	src_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(camअगर->sensor.sd, pad, get_fmt, शून्य, &src_fmt);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस -EPIPE;

	अगर (src_fmt.क्रमmat.width != camअगर->mbus_fmt.width ||
	    src_fmt.क्रमmat.height != camअगर->mbus_fmt.height ||
	    src_fmt.क्रमmat.code != camअगर->mbus_fmt.code)
		वापस -EPIPE;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_streamon(काष्ठा file *file, व्योम *priv,
			      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा media_entity *sensor = &camअगर->sensor.sd->entity;
	पूर्णांक ret;

	pr_debug("[vp%d]\n", vp->id);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (vp->owner && vp->owner != priv)
		वापस -EBUSY;

	अगर (s3c_vp_active(vp))
		वापस 0;

	ret = media_pipeline_start(sensor, camअगर->m_pipeline);
	अगर (ret < 0)
		वापस ret;

	ret = camअगर_pipeline_validate(camअगर);
	अगर (ret < 0) अणु
		media_pipeline_stop(sensor);
		वापस ret;
	पूर्ण

	वापस vb2_streamon(&vp->vb_queue, type);
पूर्ण

अटल पूर्णांक s3c_camअगर_streamoff(काष्ठा file *file, व्योम *priv,
			       क्रमागत v4l2_buf_type type)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	पूर्णांक ret;

	pr_debug("[vp%d]\n", vp->id);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (vp->owner && vp->owner != priv)
		वापस -EBUSY;

	ret = vb2_streamoff(&vp->vb_queue, type);
	अगर (ret == 0)
		media_pipeline_stop(&camअगर->sensor.sd->entity);
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_reqbufs(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	पूर्णांक ret;

	pr_debug("[vp%d] rb count: %d, owner: %p, priv: %p\n",
		 vp->id, rb->count, vp->owner, priv);

	अगर (vp->owner && vp->owner != priv)
		वापस -EBUSY;

	अगर (rb->count)
		rb->count = max_t(u32, CAMIF_REQ_BUFS_MIN, rb->count);
	अन्यथा
		vp->owner = शून्य;

	ret = vb2_reqbufs(&vp->vb_queue, rb);
	अगर (ret < 0)
		वापस ret;

	अगर (rb->count && rb->count < CAMIF_REQ_BUFS_MIN) अणु
		rb->count = 0;
		vb2_reqbufs(&vp->vb_queue, rb);
		ret = -ENOMEM;
	पूर्ण

	vp->reqbufs_count = rb->count;
	अगर (vp->owner == शून्य && rb->count > 0)
		vp->owner = priv;

	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_querybuf(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	वापस vb2_querybuf(&vp->vb_queue, buf);
पूर्ण

अटल पूर्णांक s3c_camअगर_qbuf(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);

	pr_debug("[vp%d]\n", vp->id);

	अगर (vp->owner && vp->owner != priv)
		वापस -EBUSY;

	वापस vb2_qbuf(&vp->vb_queue, vp->vdev.v4l2_dev->mdev, buf);
पूर्ण

अटल पूर्णांक s3c_camअगर_dqbuf(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);

	pr_debug("[vp%d] sequence: %d\n", vp->id, vp->frame_sequence);

	अगर (vp->owner && vp->owner != priv)
		वापस -EBUSY;

	वापस vb2_dqbuf(&vp->vb_queue, buf, file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक s3c_camअगर_create_bufs(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_create_buffers *create)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	पूर्णांक ret;

	अगर (vp->owner && vp->owner != priv)
		वापस -EBUSY;

	create->count = max_t(u32, 1, create->count);
	ret = vb2_create_bufs(&vp->vb_queue, create);

	अगर (!ret && vp->owner == शून्य)
		vp->owner = priv;

	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_prepare_buf(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_buffer *b)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	वापस vb2_prepare_buf(&vp->vb_queue, vp->vdev.v4l2_dev->mdev, b);
पूर्ण

अटल पूर्णांक s3c_camअगर_g_selection(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_selection *sel)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = vp->out_frame.f_width;
		sel->r.height = vp->out_frame.f_height;
		वापस 0;

	हाल V4L2_SEL_TGT_COMPOSE:
		sel->r = vp->out_frame.rect;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम __camअगर_try_compose(काष्ठा camअगर_dev *camअगर, काष्ठा camअगर_vp *vp,
				काष्ठा v4l2_rect *r)
अणु
	/* s3c244x करोesn't support composition */
	अगर (camअगर->variant->ip_revision == S3C244X_CAMIF_IP_REV) अणु
		*r = vp->out_frame.rect;
		वापस;
	पूर्ण

	/* TODO: s3c64xx */
पूर्ण

अटल पूर्णांक s3c_camअगर_s_selection(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_selection *sel)
अणु
	काष्ठा camअगर_vp *vp = video_drvdata(file);
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा v4l2_rect rect = sel->r;
	अचिन्हित दीर्घ flags;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    sel->target != V4L2_SEL_TGT_COMPOSE)
		वापस -EINVAL;

	__camअगर_try_compose(camअगर, vp, &rect);

	sel->r = rect;
	spin_lock_irqsave(&camअगर->slock, flags);
	vp->out_frame.rect = rect;
	vp->state |= ST_VP_CONFIG;
	spin_unlock_irqrestore(&camअगर->slock, flags);

	pr_debug("type: %#x, target: %#x, flags: %#x, (%d,%d)/%dx%d\n",
		sel->type, sel->target, sel->flags,
		sel->r.left, sel->r.top, sel->r.width, sel->r.height);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops s3c_camअगर_ioctl_ops = अणु
	.vidioc_querycap	  = s3c_camअगर_vidioc_querycap,
	.vidioc_क्रमागत_input	  = s3c_camअगर_vidioc_क्रमागत_input,
	.vidioc_g_input		  = s3c_camअगर_vidioc_g_input,
	.vidioc_s_input		  = s3c_camअगर_vidioc_s_input,
	.vidioc_क्रमागत_fmt_vid_cap  = s3c_camअगर_vidioc_क्रमागत_fmt,
	.vidioc_try_fmt_vid_cap	  = s3c_camअगर_vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap	  = s3c_camअगर_vidioc_s_fmt,
	.vidioc_g_fmt_vid_cap	  = s3c_camअगर_vidioc_g_fmt,
	.vidioc_g_selection	  = s3c_camअगर_g_selection,
	.vidioc_s_selection	  = s3c_camअगर_s_selection,
	.vidioc_reqbufs		  = s3c_camअगर_reqbufs,
	.vidioc_querybuf	  = s3c_camअगर_querybuf,
	.vidioc_prepare_buf	  = s3c_camअगर_prepare_buf,
	.vidioc_create_bufs	  = s3c_camअगर_create_bufs,
	.vidioc_qbuf		  = s3c_camअगर_qbuf,
	.vidioc_dqbuf		  = s3c_camअगर_dqbuf,
	.vidioc_streamon	  = s3c_camअगर_streamon,
	.vidioc_streamoff	  = s3c_camअगर_streamoff,
	.vidioc_subscribe_event	  = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_log_status	  = v4l2_ctrl_log_status,
पूर्ण;

/*
 * Video node controls
 */
अटल पूर्णांक s3c_camअगर_video_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा camअगर_vp *vp = ctrl->priv;
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	अचिन्हित दीर्घ flags;

	pr_debug("[vp%d] ctrl: %s, value: %d\n", vp->id,
		 ctrl->name, ctrl->val);

	spin_lock_irqsave(&camअगर->slock, flags);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		vp->hflip = ctrl->val;
		अवरोध;

	हाल V4L2_CID_VFLIP:
		vp->vflip = ctrl->val;
		अवरोध;
	पूर्ण

	vp->state |= ST_VP_CONFIG;
	spin_unlock_irqrestore(&camअगर->slock, flags);
	वापस 0;
पूर्ण

/* Codec and preview video node control ops */
अटल स्थिर काष्ठा v4l2_ctrl_ops s3c_camअगर_video_ctrl_ops = अणु
	.s_ctrl = s3c_camअगर_video_s_ctrl,
पूर्ण;

पूर्णांक s3c_camअगर_रेजिस्टर_video_node(काष्ठा camअगर_dev *camअगर, पूर्णांक idx)
अणु
	काष्ठा camअगर_vp *vp = &camअगर->vp[idx];
	काष्ठा vb2_queue *q = &vp->vb_queue;
	काष्ठा video_device *vfd = &vp->vdev;
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	स_रखो(vfd, 0, माप(*vfd));
	snम_लिखो(vfd->name, माप(vfd->name), "camif-%s",
		 vp->id == 0 ? "codec" : "preview");

	vfd->fops = &s3c_camअगर_fops;
	vfd->ioctl_ops = &s3c_camअगर_ioctl_ops;
	vfd->v4l2_dev = &camअगर->v4l2_dev;
	vfd->minor = -1;
	vfd->release = video_device_release_empty;
	vfd->lock = &camअगर->lock;
	vp->reqbufs_count = 0;

	INIT_LIST_HEAD(&vp->pending_buf_q);
	INIT_LIST_HEAD(&vp->active_buf_q);

	स_रखो(q, 0, माप(*q));
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR;
	q->ops = &s3c_camअगर_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा camअगर_buffer);
	q->drv_priv = vp;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &vp->camअगर->lock;
	q->dev = camअगर->v4l2_dev.dev;

	ret = vb2_queue_init(q);
	अगर (ret)
		जाओ err_vd_rel;

	vp->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &vp->pad);
	अगर (ret)
		जाओ err_vd_rel;

	video_set_drvdata(vfd, vp);

	v4l2_ctrl_handler_init(&vp->ctrl_handler, 1);
	ctrl = v4l2_ctrl_new_std(&vp->ctrl_handler, &s3c_camअगर_video_ctrl_ops,
				 V4L2_CID_HFLIP, 0, 1, 1, 0);
	अगर (ctrl)
		ctrl->priv = vp;
	ctrl = v4l2_ctrl_new_std(&vp->ctrl_handler, &s3c_camअगर_video_ctrl_ops,
				 V4L2_CID_VFLIP, 0, 1, 1, 0);
	अगर (ctrl)
		ctrl->priv = vp;

	ret = vp->ctrl_handler.error;
	अगर (ret < 0)
		जाओ err_me_cleanup;

	vfd->ctrl_handler = &vp->ctrl_handler;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ err_ctrlh_मुक्त;

	v4l2_info(&camअगर->v4l2_dev, "registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	वापस 0;

err_ctrlh_मुक्त:
	v4l2_ctrl_handler_मुक्त(&vp->ctrl_handler);
err_me_cleanup:
	media_entity_cleanup(&vfd->entity);
err_vd_rel:
	video_device_release(vfd);
	वापस ret;
पूर्ण

व्योम s3c_camअगर_unरेजिस्टर_video_node(काष्ठा camअगर_dev *camअगर, पूर्णांक idx)
अणु
	काष्ठा video_device *vfd = &camअगर->vp[idx].vdev;

	अगर (video_is_रेजिस्टरed(vfd)) अणु
		video_unरेजिस्टर_device(vfd);
		media_entity_cleanup(&vfd->entity);
		v4l2_ctrl_handler_मुक्त(vfd->ctrl_handler);
	पूर्ण
पूर्ण

/* Media bus pixel क्रमmats supported at the camअगर input */
अटल स्थिर u32 camअगर_mbus_क्रमmats[] = अणु
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
पूर्ण;

/*
 *  Camera input पूर्णांकerface subdev operations
 */

अटल पूर्णांक s3c_camअगर_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_subdev_pad_config *cfg,
					काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(camअगर_mbus_क्रमmats))
		वापस -EINVAL;

	code->code = camअगर_mbus_क्रमmats[code->index];
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_subdev_get_fmt(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा camअगर_dev *camअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		fmt->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mutex_lock(&camअगर->lock);

	चयन (fmt->pad) अणु
	हाल CAMIF_SD_PAD_SINK:
		/* full camera input pixel size */
		*mf = camअगर->mbus_fmt;
		अवरोध;

	हाल CAMIF_SD_PAD_SOURCE_C...CAMIF_SD_PAD_SOURCE_P:
		/* crop rectangle at camera पूर्णांकerface input */
		mf->width = camअगर->camअगर_crop.width;
		mf->height = camअगर->camअगर_crop.height;
		mf->code = camअगर->mbus_fmt.code;
		अवरोध;
	पूर्ण

	mutex_unlock(&camअगर->lock);
	mf->field = V4L2_FIELD_NONE;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	वापस 0;
पूर्ण

अटल व्योम __camअगर_subdev_try_क्रमmat(काष्ठा camअगर_dev *camअगर,
				काष्ठा v4l2_mbus_framefmt *mf, पूर्णांक pad)
अणु
	स्थिर काष्ठा s3c_camअगर_variant *variant = camअगर->variant;
	स्थिर काष्ठा vp_pix_limits *pix_lim;
	अचिन्हित पूर्णांक i;

	/* FIXME: स्थिरraपूर्णांकs against codec or preview path ? */
	pix_lim = &variant->vp_pix_limits[VP_CODEC];

	क्रम (i = 0; i < ARRAY_SIZE(camअगर_mbus_क्रमmats); i++)
		अगर (camअगर_mbus_क्रमmats[i] == mf->code)
			अवरोध;

	अगर (i == ARRAY_SIZE(camअगर_mbus_क्रमmats))
		mf->code = camअगर_mbus_क्रमmats[0];

	अगर (pad == CAMIF_SD_PAD_SINK) अणु
		v4l_bound_align_image(&mf->width, 8, CAMIF_MAX_PIX_WIDTH,
				      ffs(pix_lim->out_width_align) - 1,
				      &mf->height, 8, CAMIF_MAX_PIX_HEIGHT, 0,
				      0);
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect *crop = &camअगर->camअगर_crop;
		v4l_bound_align_image(&mf->width, 8, crop->width,
				      ffs(pix_lim->out_width_align) - 1,
				      &mf->height, 8, crop->height,
				      0, 0);
	पूर्ण

	v4l2_dbg(1, debug, &camअगर->subdev, "%ux%u\n", mf->width, mf->height);
पूर्ण

अटल पूर्णांक s3c_camअगर_subdev_set_fmt(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा camअगर_dev *camअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा v4l2_rect *crop = &camअगर->camअगर_crop;
	पूर्णांक i;

	v4l2_dbg(1, debug, sd, "pad%d: code: 0x%x, %ux%u\n",
		 fmt->pad, mf->code, mf->width, mf->height);

	mf->field = V4L2_FIELD_NONE;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	mutex_lock(&camअगर->lock);

	/*
	 * No pixel क्रमmat change at the camera input is allowed
	 * जबतक streaming.
	 */
	अगर (vb2_is_busy(&camअगर->vp[VP_CODEC].vb_queue) ||
	    vb2_is_busy(&camअगर->vp[VP_PREVIEW].vb_queue)) अणु
		mutex_unlock(&camअगर->lock);
		वापस -EBUSY;
	पूर्ण

	__camअगर_subdev_try_क्रमmat(camअगर, mf, fmt->pad);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;
		mutex_unlock(&camअगर->lock);
		वापस 0;
	पूर्ण

	चयन (fmt->pad) अणु
	हाल CAMIF_SD_PAD_SINK:
		camअगर->mbus_fmt = *mf;
		/* Reset sink crop rectangle. */
		crop->width = mf->width;
		crop->height = mf->height;
		crop->left = 0;
		crop->top = 0;
		/*
		 * Reset source क्रमmat (the camअगर's crop rectangle)
		 * and the video output resolution.
		 */
		क्रम (i = 0; i < CAMIF_VP_NUM; i++) अणु
			काष्ठा camअगर_frame *frame = &camअगर->vp[i].out_frame;
			frame->rect = *crop;
			frame->f_width = mf->width;
			frame->f_height = mf->height;
		पूर्ण
		अवरोध;

	हाल CAMIF_SD_PAD_SOURCE_C...CAMIF_SD_PAD_SOURCE_P:
		/* Pixel क्रमmat can be only changed on the sink pad. */
		mf->code = camअगर->mbus_fmt.code;
		mf->width = crop->width;
		mf->height = crop->height;
		अवरोध;
	पूर्ण

	mutex_unlock(&camअगर->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_subdev_get_selection(काष्ठा v4l2_subdev *sd,
					  काष्ठा v4l2_subdev_pad_config *cfg,
					  काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा camअगर_dev *camअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_rect *crop = &camअगर->camअगर_crop;
	काष्ठा v4l2_mbus_framefmt *mf = &camअगर->mbus_fmt;

	अगर ((sel->target != V4L2_SEL_TGT_CROP &&
	    sel->target != V4L2_SEL_TGT_CROP_BOUNDS) ||
	    sel->pad != CAMIF_SD_PAD_SINK)
		वापस -EINVAL;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		sel->r = *v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		वापस 0;
	पूर्ण

	mutex_lock(&camअगर->lock);

	अगर (sel->target == V4L2_SEL_TGT_CROP) अणु
		sel->r = *crop;
	पूर्ण अन्यथा अणु /* crop bounds */
		sel->r.width = mf->width;
		sel->r.height = mf->height;
		sel->r.left = 0;
		sel->r.top = 0;
	पूर्ण

	mutex_unlock(&camअगर->lock);

	v4l2_dbg(1, debug, sd, "%s: crop: (%d,%d) %dx%d, size: %ux%u\n",
		 __func__, crop->left, crop->top, crop->width,
		 crop->height, mf->width, mf->height);

	वापस 0;
पूर्ण

अटल व्योम __camअगर_try_crop(काष्ठा camअगर_dev *camअगर, काष्ठा v4l2_rect *r)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &camअगर->mbus_fmt;
	स्थिर काष्ठा camअगर_pix_limits *pix_lim = &camअगर->variant->pix_limits;
	अचिन्हित पूर्णांक left = 2 * r->left;
	अचिन्हित पूर्णांक top = 2 * r->top;

	/*
	 * Following स्थिरraपूर्णांकs must be met:
	 *  - r->width + 2 * r->left = mf->width;
	 *  - r->height + 2 * r->top = mf->height;
	 *  - crop rectangle size and position must be aligned
	 *    to 8 or 2 pixels, depending on SoC version.
	 */
	v4l_bound_align_image(&r->width, 0, mf->width,
			      ffs(pix_lim->win_hor_offset_align) - 1,
			      &r->height, 0, mf->height, 1, 0);

	v4l_bound_align_image(&left, 0, mf->width - r->width,
			      ffs(pix_lim->win_hor_offset_align),
			      &top, 0, mf->height - r->height, 2, 0);

	r->left = left / 2;
	r->top = top / 2;
	r->width = mf->width - left;
	r->height = mf->height - top;
	/*
	 * Make sure we either करोwnscale or upscale both the pixel
	 * width and height. Just वापस current crop rectangle अगर
	 * this scaler स्थिरraपूर्णांक is not met.
	 */
	अगर (camअगर->variant->ip_revision == S3C244X_CAMIF_IP_REV &&
	    camअगर_is_streaming(camअगर)) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < CAMIF_VP_NUM; i++) अणु
			काष्ठा v4l2_rect *or = &camअगर->vp[i].out_frame.rect;
			अगर ((or->width > r->width) == (or->height > r->height))
				जारी;
			*r = camअगर->camअगर_crop;
			pr_debug("Width/height scaling direction limitation\n");
			अवरोध;
		पूर्ण
	पूर्ण

	v4l2_dbg(1, debug, &camअगर->v4l2_dev, "crop: (%d,%d)/%dx%d, fmt: %ux%u\n",
		 r->left, r->top, r->width, r->height, mf->width, mf->height);
पूर्ण

अटल पूर्णांक s3c_camअगर_subdev_set_selection(काष्ठा v4l2_subdev *sd,
					  काष्ठा v4l2_subdev_pad_config *cfg,
					  काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा camअगर_dev *camअगर = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_rect *crop = &camअगर->camअगर_crop;
	काष्ठा camअगर_scaler scaler;

	अगर (sel->target != V4L2_SEL_TGT_CROP || sel->pad != CAMIF_SD_PAD_SINK)
		वापस -EINVAL;

	mutex_lock(&camअगर->lock);
	__camअगर_try_crop(camअगर, &sel->r);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_crop(sd, cfg, sel->pad) = sel->r;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		अचिन्हित पूर्णांक i;

		spin_lock_irqsave(&camअगर->slock, flags);
		*crop = sel->r;

		क्रम (i = 0; i < CAMIF_VP_NUM; i++) अणु
			काष्ठा camअगर_vp *vp = &camअगर->vp[i];
			scaler = vp->scaler;
			अगर (s3c_camअगर_get_scaler_config(vp, &scaler))
				जारी;
			vp->scaler = scaler;
			vp->state |= ST_VP_CONFIG;
		पूर्ण

		spin_unlock_irqrestore(&camअगर->slock, flags);
	पूर्ण
	mutex_unlock(&camअगर->lock);

	v4l2_dbg(1, debug, sd, "%s: (%d,%d) %dx%d, f_w: %u, f_h: %u\n",
		 __func__, crop->left, crop->top, crop->width, crop->height,
		 camअगर->mbus_fmt.width, camअगर->mbus_fmt.height);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s3c_camअगर_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = s3c_camअगर_subdev_क्रमागत_mbus_code,
	.get_selection = s3c_camअगर_subdev_get_selection,
	.set_selection = s3c_camअगर_subdev_set_selection,
	.get_fmt = s3c_camअगर_subdev_get_fmt,
	.set_fmt = s3c_camअगर_subdev_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s3c_camअगर_subdev_ops = अणु
	.pad = &s3c_camअगर_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक s3c_camअगर_subdev_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा camअगर_dev *camअगर = container_of(ctrl->handler, काष्ठा camअगर_dev,
					       ctrl_handler);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&camअगर->slock, flags);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_COLORFX:
		camअगर->colorfx = camअगर->ctrl_colorfx->val;
		/* Set Cb, Cr */
		चयन (ctrl->val) अणु
		हाल V4L2_COLORFX_SEPIA:
			camअगर->colorfx_cb = 115;
			camअगर->colorfx_cr = 145;
			अवरोध;
		हाल V4L2_COLORFX_SET_CBCR:
			camअगर->colorfx_cb = camअगर->ctrl_colorfx_cbcr->val >> 8;
			camअगर->colorfx_cr = camअगर->ctrl_colorfx_cbcr->val & 0xff;
			अवरोध;
		शेष:
			/* क्रम V4L2_COLORFX_BW and others */
			camअगर->colorfx_cb = 128;
			camअगर->colorfx_cr = 128;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		camअगर->test_pattern = camअगर->ctrl_test_pattern->val;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	camअगर->vp[VP_CODEC].state |= ST_VP_CONFIG;
	camअगर->vp[VP_PREVIEW].state |= ST_VP_CONFIG;
	spin_unlock_irqrestore(&camअगर->slock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s3c_camअगर_subdev_ctrl_ops = अणु
	.s_ctrl	= s3c_camअगर_subdev_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर s3c_camअगर_test_pattern_menu[] = अणु
	"Disabled",
	"Color bars",
	"Horizontal increment",
	"Vertical increment",
पूर्ण;

पूर्णांक s3c_camअगर_create_subdev(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा v4l2_ctrl_handler *handler = &camअगर->ctrl_handler;
	काष्ठा v4l2_subdev *sd = &camअगर->subdev;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &s3c_camअगर_subdev_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(sd->name, "S3C-CAMIF", माप(sd->name));

	camअगर->pads[CAMIF_SD_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	camअगर->pads[CAMIF_SD_PAD_SOURCE_C].flags = MEDIA_PAD_FL_SOURCE;
	camअगर->pads[CAMIF_SD_PAD_SOURCE_P].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&sd->entity, CAMIF_SD_PADS_NUM,
				camअगर->pads);
	अगर (ret)
		वापस ret;

	v4l2_ctrl_handler_init(handler, 3);
	camअगर->ctrl_test_pattern = v4l2_ctrl_new_std_menu_items(handler,
			&s3c_camअगर_subdev_ctrl_ops, V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(s3c_camअगर_test_pattern_menu) - 1, 0, 0,
			s3c_camअगर_test_pattern_menu);

	अगर (camअगर->variant->has_img_effect) अणु
		camअगर->ctrl_colorfx = v4l2_ctrl_new_std_menu(handler,
				&s3c_camअगर_subdev_ctrl_ops,
				V4L2_CID_COLORFX, V4L2_COLORFX_SET_CBCR,
				~0x981f, V4L2_COLORFX_NONE);

		camअगर->ctrl_colorfx_cbcr = v4l2_ctrl_new_std(handler,
				&s3c_camअगर_subdev_ctrl_ops,
				V4L2_CID_COLORFX_CBCR, 0, 0xffff, 1, 0);
	पूर्ण

	अगर (handler->error) अणु
		v4l2_ctrl_handler_मुक्त(handler);
		media_entity_cleanup(&sd->entity);
		वापस handler->error;
	पूर्ण

	अगर (camअगर->variant->has_img_effect)
		v4l2_ctrl_स्वतः_cluster(2, &camअगर->ctrl_colorfx,
			       V4L2_COLORFX_SET_CBCR, false);

	sd->ctrl_handler = handler;
	v4l2_set_subdevdata(sd, camअगर);

	वापस 0;
पूर्ण

व्योम s3c_camअगर_unरेजिस्टर_subdev(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा v4l2_subdev *sd = &camअगर->subdev;

	/* Return अगर not रेजिस्टरed */
	अगर (v4l2_get_subdevdata(sd) == शून्य)
		वापस;

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(&camअगर->ctrl_handler);
	v4l2_set_subdevdata(sd, शून्य);
पूर्ण

पूर्णांक s3c_camअगर_set_शेषs(काष्ठा camअगर_dev *camअगर)
अणु
	अचिन्हित पूर्णांक ip_rev = camअगर->variant->ip_revision;
	पूर्णांक i;

	क्रम (i = 0; i < CAMIF_VP_NUM; i++) अणु
		काष्ठा camअगर_vp *vp = &camअगर->vp[i];
		काष्ठा camअगर_frame *f = &vp->out_frame;

		vp->camअगर = camअगर;
		vp->id = i;
		vp->offset = camअगर->variant->vp_offset;

		अगर (ip_rev == S3C244X_CAMIF_IP_REV)
			vp->fmt_flags = i ? FMT_FL_S3C24XX_PREVIEW :
					FMT_FL_S3C24XX_CODEC;
		अन्यथा
			vp->fmt_flags = FMT_FL_S3C64XX;

		vp->out_fmt = s3c_camअगर_find_क्रमmat(vp, शून्य, 0);
		BUG_ON(vp->out_fmt == शून्य);

		स_रखो(f, 0, माप(*f));
		f->f_width = CAMIF_DEF_WIDTH;
		f->f_height = CAMIF_DEF_HEIGHT;
		f->rect.width = CAMIF_DEF_WIDTH;
		f->rect.height = CAMIF_DEF_HEIGHT;

		/* Scaler is always enabled */
		vp->scaler.enable = 1;

		vp->payload = (f->f_width * f->f_height *
			       vp->out_fmt->depth) / 8;
	पूर्ण

	स_रखो(&camअगर->mbus_fmt, 0, माप(camअगर->mbus_fmt));
	camअगर->mbus_fmt.width = CAMIF_DEF_WIDTH;
	camअगर->mbus_fmt.height = CAMIF_DEF_HEIGHT;
	camअगर->mbus_fmt.code  = camअगर_mbus_क्रमmats[0];

	स_रखो(&camअगर->camअगर_crop, 0, माप(camअगर->camअगर_crop));
	camअगर->camअगर_crop.width = CAMIF_DEF_WIDTH;
	camअगर->camअगर_crop.height = CAMIF_DEF_HEIGHT;

	वापस 0;
पूर्ण
