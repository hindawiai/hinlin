<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung S5P/EXYNOS4 SoC series camera पूर्णांकerface (camera capture) driver
 *
 * Copyright (C) 2010 - 2012 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-rect.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "common.h"
#समावेश "fimc-core.h"
#समावेश "fimc-reg.h"
#समावेश "media-dev.h"

अटल पूर्णांक fimc_capture_hw_init(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा fimc_source_info *si = &fimc->vid_cap.source_config;
	काष्ठा fimc_ctx *ctx = fimc->vid_cap.ctx;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (ctx == शून्य || ctx->s_frame.fmt == शून्य)
		वापस -EINVAL;

	अगर (si->fimc_bus_type == FIMC_BUS_TYPE_ISP_WRITEBACK) अणु
		ret = fimc_hw_camblk_cfg_ग_लिखोback(fimc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	spin_lock_irqsave(&fimc->slock, flags);
	fimc_prepare_dma_offset(ctx, &ctx->d_frame);
	fimc_set_yuv_order(ctx);

	fimc_hw_set_camera_polarity(fimc, si);
	fimc_hw_set_camera_type(fimc, si);
	fimc_hw_set_camera_source(fimc, si);
	fimc_hw_set_camera_offset(fimc, &ctx->s_frame);

	ret = fimc_set_scaler_info(ctx);
	अगर (!ret) अणु
		fimc_hw_set_input_path(ctx);
		fimc_hw_set_prescaler(ctx);
		fimc_hw_set_मुख्यscaler(ctx);
		fimc_hw_set_target_क्रमmat(ctx);
		fimc_hw_set_rotation(ctx);
		fimc_hw_set_effect(ctx);
		fimc_hw_set_output_path(ctx);
		fimc_hw_set_out_dma(ctx);
		अगर (fimc->drv_data->alpha_color)
			fimc_hw_set_rgb_alpha(ctx);
		clear_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	पूर्ण
	spin_unlock_irqrestore(&fimc->slock, flags);
	वापस ret;
पूर्ण

/*
 * Reinitialize the driver so it is पढ़ोy to start the streaming again.
 * Set fimc->state to indicate stream off and the hardware shut करोwn state.
 * If not suspending (@suspend is false), वापस any buffers to videobuf2.
 * Otherwise put any owned buffers onto the pending buffers queue, so they
 * can be re-spun when the device is being resumed. Also perक्रमm FIMC
 * software reset and disable streaming on the whole pipeline अगर required.
 */
अटल पूर्णांक fimc_capture_state_cleanup(काष्ठा fimc_dev *fimc, bool suspend)
अणु
	काष्ठा fimc_vid_cap *cap = &fimc->vid_cap;
	काष्ठा fimc_vid_buffer *buf;
	अचिन्हित दीर्घ flags;
	bool streaming;

	spin_lock_irqsave(&fimc->slock, flags);
	streaming = fimc->state & (1 << ST_CAPT_ISP_STREAM);

	fimc->state &= ~(1 << ST_CAPT_RUN | 1 << ST_CAPT_SHUT |
			 1 << ST_CAPT_STREAM | 1 << ST_CAPT_ISP_STREAM);
	अगर (suspend)
		fimc->state |= (1 << ST_CAPT_SUSPENDED);
	अन्यथा
		fimc->state &= ~(1 << ST_CAPT_PEND | 1 << ST_CAPT_SUSPENDED);

	/* Release unused buffers */
	जबतक (!suspend && !list_empty(&cap->pending_buf_q)) अणु
		buf = fimc_pending_queue_pop(cap);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	/* If suspending put unused buffers onto pending queue */
	जबतक (!list_empty(&cap->active_buf_q)) अणु
		buf = fimc_active_queue_pop(cap);
		अगर (suspend)
			fimc_pending_queue_add(cap, buf);
		अन्यथा
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	fimc_hw_reset(fimc);
	cap->buf_index = 0;

	spin_unlock_irqrestore(&fimc->slock, flags);

	अगर (streaming)
		वापस fimc_pipeline_call(&cap->ve, set_stream, 0);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक fimc_stop_capture(काष्ठा fimc_dev *fimc, bool suspend)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!fimc_capture_active(fimc))
		वापस 0;

	spin_lock_irqsave(&fimc->slock, flags);
	set_bit(ST_CAPT_SHUT, &fimc->state);
	fimc_deactivate_capture(fimc);
	spin_unlock_irqrestore(&fimc->slock, flags);

	रुको_event_समयout(fimc->irq_queue,
			   !test_bit(ST_CAPT_SHUT, &fimc->state),
			   (2*HZ/10)); /* 200 ms */

	वापस fimc_capture_state_cleanup(fimc, suspend);
पूर्ण

/**
 * fimc_capture_config_update - apply the camera पूर्णांकerface configuration
 * @ctx: FIMC capture context
 *
 * To be called from within the पूर्णांकerrupt handler with fimc.slock
 * spinlock held. It updates the camera pixel crop, rotation and
 * image flip in H/W.
 */
अटल पूर्णांक fimc_capture_config_update(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	पूर्णांक ret;

	fimc_hw_set_camera_offset(fimc, &ctx->s_frame);

	ret = fimc_set_scaler_info(ctx);
	अगर (ret)
		वापस ret;

	fimc_hw_set_prescaler(ctx);
	fimc_hw_set_मुख्यscaler(ctx);
	fimc_hw_set_target_क्रमmat(ctx);
	fimc_hw_set_rotation(ctx);
	fimc_hw_set_effect(ctx);
	fimc_prepare_dma_offset(ctx, &ctx->d_frame);
	fimc_hw_set_out_dma(ctx);
	अगर (fimc->drv_data->alpha_color)
		fimc_hw_set_rgb_alpha(ctx);

	clear_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	वापस ret;
पूर्ण

व्योम fimc_capture_irq_handler(काष्ठा fimc_dev *fimc, पूर्णांक deq_buf)
अणु
	काष्ठा fimc_vid_cap *cap = &fimc->vid_cap;
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(cap->ve.pipe);
	काष्ठा v4l2_subdev *csis = p->subdevs[IDX_CSIS];
	काष्ठा fimc_frame *f = &cap->ctx->d_frame;
	काष्ठा fimc_vid_buffer *v_buf;

	अगर (test_and_clear_bit(ST_CAPT_SHUT, &fimc->state)) अणु
		wake_up(&fimc->irq_queue);
		जाओ करोne;
	पूर्ण

	अगर (!list_empty(&cap->active_buf_q) &&
	    test_bit(ST_CAPT_RUN, &fimc->state) && deq_buf) अणु
		v_buf = fimc_active_queue_pop(cap);

		v_buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		v_buf->vb.sequence = cap->frame_count++;

		vb2_buffer_करोne(&v_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	अगर (!list_empty(&cap->pending_buf_q)) अणु

		v_buf = fimc_pending_queue_pop(cap);
		fimc_hw_set_output_addr(fimc, &v_buf->addr, cap->buf_index);
		v_buf->index = cap->buf_index;

		/* Move the buffer to the capture active queue */
		fimc_active_queue_add(cap, v_buf);

		dbg("next frame: %d, done frame: %d",
		    fimc_hw_get_frame_index(fimc), v_buf->index);

		अगर (++cap->buf_index >= FIMC_MAX_OUT_BUFS)
			cap->buf_index = 0;
	पूर्ण
	/*
	 * Set up a buffer at MIPI-CSIS अगर current image क्रमmat
	 * requires the frame embedded data capture.
	 */
	अगर (f->fmt->mdataplanes && !list_empty(&cap->active_buf_q)) अणु
		अचिन्हित पूर्णांक plane = ffs(f->fmt->mdataplanes) - 1;
		अचिन्हित पूर्णांक size = f->payload[plane];
		s32 index = fimc_hw_get_frame_index(fimc);
		व्योम *vaddr;

		list_क्रम_each_entry(v_buf, &cap->active_buf_q, list) अणु
			अगर (v_buf->index != index)
				जारी;
			vaddr = vb2_plane_vaddr(&v_buf->vb.vb2_buf, plane);
			v4l2_subdev_call(csis, video, s_rx_buffer,
					 vaddr, &size);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cap->active_buf_cnt == 0) अणु
		अगर (deq_buf)
			clear_bit(ST_CAPT_RUN, &fimc->state);

		अगर (++cap->buf_index >= FIMC_MAX_OUT_BUFS)
			cap->buf_index = 0;
	पूर्ण अन्यथा अणु
		set_bit(ST_CAPT_RUN, &fimc->state);
	पूर्ण

	अगर (test_bit(ST_CAPT_APPLY_CFG, &fimc->state))
		fimc_capture_config_update(cap->ctx);
करोne:
	अगर (cap->active_buf_cnt == 1) अणु
		fimc_deactivate_capture(fimc);
		clear_bit(ST_CAPT_STREAM, &fimc->state);
	पूर्ण

	dbg("frame: %d, active_buf_cnt: %d",
	    fimc_hw_get_frame_index(fimc), cap->active_buf_cnt);
पूर्ण


अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा fimc_ctx *ctx = q->drv_priv;
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा fimc_vid_cap *vid_cap = &fimc->vid_cap;
	पूर्णांक min_bufs;
	पूर्णांक ret;

	vid_cap->frame_count = 0;

	ret = fimc_capture_hw_init(fimc);
	अगर (ret) अणु
		fimc_capture_state_cleanup(fimc, false);
		वापस ret;
	पूर्ण

	set_bit(ST_CAPT_PEND, &fimc->state);

	min_bufs = fimc->vid_cap.reqbufs_count > 1 ? 2 : 1;

	अगर (vid_cap->active_buf_cnt >= min_bufs &&
	    !test_and_set_bit(ST_CAPT_STREAM, &fimc->state)) अणु
		fimc_activate_capture(ctx);

		अगर (!test_and_set_bit(ST_CAPT_ISP_STREAM, &fimc->state))
			वापस fimc_pipeline_call(&vid_cap->ve, set_stream, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा fimc_ctx *ctx = q->drv_priv;
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;

	अगर (!fimc_capture_active(fimc))
		वापस;

	fimc_stop_capture(fimc, false);
पूर्ण

पूर्णांक fimc_capture_suspend(काष्ठा fimc_dev *fimc)
अणु
	bool suspend = fimc_capture_busy(fimc);

	पूर्णांक ret = fimc_stop_capture(fimc, suspend);
	अगर (ret)
		वापस ret;
	वापस fimc_pipeline_call(&fimc->vid_cap.ve, बंद);
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb);

पूर्णांक fimc_capture_resume(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा fimc_vid_cap *vid_cap = &fimc->vid_cap;
	काष्ठा exynos_video_entity *ve = &vid_cap->ve;
	काष्ठा fimc_vid_buffer *buf;
	पूर्णांक i;

	अगर (!test_and_clear_bit(ST_CAPT_SUSPENDED, &fimc->state))
		वापस 0;

	INIT_LIST_HEAD(&fimc->vid_cap.active_buf_q);
	vid_cap->buf_index = 0;
	fimc_pipeline_call(ve, खोलो, &ve->vdev.entity, false);
	fimc_capture_hw_init(fimc);

	clear_bit(ST_CAPT_SUSPENDED, &fimc->state);

	क्रम (i = 0; i < vid_cap->reqbufs_count; i++) अणु
		अगर (list_empty(&vid_cap->pending_buf_q))
			अवरोध;
		buf = fimc_pending_queue_pop(vid_cap);
		buffer_queue(&buf->vb.vb2_buf);
	पूर्ण
	वापस 0;

पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा fimc_ctx *ctx = vq->drv_priv;
	काष्ठा fimc_frame *frame = &ctx->d_frame;
	काष्ठा fimc_fmt *fmt = frame->fmt;
	अचिन्हित दीर्घ wh = frame->f_width * frame->f_height;
	पूर्णांक i;

	अगर (fmt == शून्य)
		वापस -EINVAL;

	अगर (*num_planes) अणु
		अगर (*num_planes != fmt->memplanes)
			वापस -EINVAL;
		क्रम (i = 0; i < *num_planes; i++)
			अगर (sizes[i] < (wh * fmt->depth[i]) / 8)
				वापस -EINVAL;
		वापस 0;
	पूर्ण

	*num_planes = fmt->memplanes;

	क्रम (i = 0; i < fmt->memplanes; i++) अणु
		अचिन्हित पूर्णांक size = (wh * fmt->depth[i]) / 8;

		अगर (fimc_fmt_is_user_defined(fmt->color))
			sizes[i] = frame->payload[i];
		अन्यथा
			sizes[i] = max_t(u32, size, frame->payload[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा fimc_ctx *ctx = vq->drv_priv;
	पूर्णांक i;

	अगर (ctx->d_frame.fmt == शून्य)
		वापस -EINVAL;

	क्रम (i = 0; i < ctx->d_frame.fmt->memplanes; i++) अणु
		अचिन्हित दीर्घ size = ctx->d_frame.payload[i];

		अगर (vb2_plane_size(vb, i) < size) अणु
			v4l2_err(&ctx->fimc_dev->vid_cap.ve.vdev,
				 "User buffer too small (%ld < %ld)\n",
				 vb2_plane_size(vb, i), size);
			वापस -EINVAL;
		पूर्ण
		vb2_set_plane_payload(vb, i, size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा fimc_vid_buffer *buf
		= container_of(vbuf, काष्ठा fimc_vid_buffer, vb);
	काष्ठा fimc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा fimc_vid_cap *vid_cap = &fimc->vid_cap;
	काष्ठा exynos_video_entity *ve = &vid_cap->ve;
	अचिन्हित दीर्घ flags;
	पूर्णांक min_bufs;

	spin_lock_irqsave(&fimc->slock, flags);
	fimc_prepare_addr(ctx, &buf->vb.vb2_buf, &ctx->d_frame, &buf->addr);

	अगर (!test_bit(ST_CAPT_SUSPENDED, &fimc->state) &&
	    !test_bit(ST_CAPT_STREAM, &fimc->state) &&
	    vid_cap->active_buf_cnt < FIMC_MAX_OUT_BUFS) अणु
		/* Setup the buffer directly क्रम processing. */
		पूर्णांक buf_id = (vid_cap->reqbufs_count == 1) ? -1 :
				vid_cap->buf_index;

		fimc_hw_set_output_addr(fimc, &buf->addr, buf_id);
		buf->index = vid_cap->buf_index;
		fimc_active_queue_add(vid_cap, buf);

		अगर (++vid_cap->buf_index >= FIMC_MAX_OUT_BUFS)
			vid_cap->buf_index = 0;
	पूर्ण अन्यथा अणु
		fimc_pending_queue_add(vid_cap, buf);
	पूर्ण

	min_bufs = vid_cap->reqbufs_count > 1 ? 2 : 1;


	अगर (vb2_is_streaming(&vid_cap->vbq) &&
	    vid_cap->active_buf_cnt >= min_bufs &&
	    !test_and_set_bit(ST_CAPT_STREAM, &fimc->state)) अणु
		पूर्णांक ret;

		fimc_activate_capture(ctx);
		spin_unlock_irqrestore(&fimc->slock, flags);

		अगर (test_and_set_bit(ST_CAPT_ISP_STREAM, &fimc->state))
			वापस;

		ret = fimc_pipeline_call(ve, set_stream, 1);
		अगर (ret < 0)
			v4l2_err(&ve->vdev, "stream on failed: %d\n", ret);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&fimc->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops fimc_capture_qops = अणु
	.queue_setup		= queue_setup,
	.buf_prepare		= buffer_prepare,
	.buf_queue		= buffer_queue,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
पूर्ण;

अटल पूर्णांक fimc_capture_set_शेष_क्रमmat(काष्ठा fimc_dev *fimc);

अटल पूर्णांक fimc_capture_खोलो(काष्ठा file *file)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा exynos_video_entity *ve = &vc->ve;
	पूर्णांक ret = -EBUSY;

	dbg("pid: %d, state: 0x%lx", task_pid_nr(current), fimc->state);

	mutex_lock(&fimc->lock);

	अगर (fimc_m2m_active(fimc))
		जाओ unlock;

	set_bit(ST_CAPT_BUSY, &fimc->state);
	ret = pm_runसमय_get_sync(&fimc->pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_sync(&fimc->pdev->dev);
		जाओ unlock;
	पूर्ण

	ret = v4l2_fh_खोलो(file);
	अगर (ret) अणु
		pm_runसमय_put_sync(&fimc->pdev->dev);
		जाओ unlock;
	पूर्ण

	अगर (v4l2_fh_is_singular_file(file)) अणु
		fimc_md_graph_lock(ve);

		ret = fimc_pipeline_call(ve, खोलो, &ve->vdev.entity, true);

		अगर (ret == 0)
			ve->vdev.entity.use_count++;

		fimc_md_graph_unlock(ve);

		अगर (ret == 0)
			ret = fimc_capture_set_शेष_क्रमmat(fimc);

		अगर (ret < 0) अणु
			clear_bit(ST_CAPT_BUSY, &fimc->state);
			pm_runसमय_put_sync(&fimc->pdev->dev);
			v4l2_fh_release(file);
		पूर्ण
	पूर्ण
unlock:
	mutex_unlock(&fimc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_capture_release(काष्ठा file *file)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	bool बंद = v4l2_fh_is_singular_file(file);
	पूर्णांक ret;

	dbg("pid: %d, state: 0x%lx", task_pid_nr(current), fimc->state);

	mutex_lock(&fimc->lock);

	अगर (बंद && vc->streaming) अणु
		media_pipeline_stop(&vc->ve.vdev.entity);
		vc->streaming = false;
	पूर्ण

	ret = _vb2_fop_release(file, शून्य);

	अगर (बंद) अणु
		clear_bit(ST_CAPT_BUSY, &fimc->state);
		fimc_pipeline_call(&vc->ve, बंद);
		clear_bit(ST_CAPT_SUSPENDED, &fimc->state);

		fimc_md_graph_lock(&vc->ve);
		vc->ve.vdev.entity.use_count--;
		fimc_md_graph_unlock(&vc->ve);
	पूर्ण

	pm_runसमय_put_sync(&fimc->pdev->dev);
	mutex_unlock(&fimc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations fimc_capture_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fimc_capture_खोलो,
	.release	= fimc_capture_release,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/*
 * Format and crop negotiation helpers
 */

अटल काष्ठा fimc_fmt *fimc_capture_try_क्रमmat(काष्ठा fimc_ctx *ctx,
						u32 *width, u32 *height,
						u32 *code, u32 *fourcc, पूर्णांक pad)
अणु
	bool rotation = ctx->rotation == 90 || ctx->rotation == 270;
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	स्थिर काष्ठा fimc_variant *var = fimc->variant;
	स्थिर काष्ठा fimc_pix_limit *pl = var->pix_limit;
	काष्ठा fimc_frame *dst = &ctx->d_frame;
	u32 depth, min_w, max_w, min_h, align_h = 3;
	u32 mask = FMT_FLAGS_CAM;
	काष्ठा fimc_fmt *ffmt;

	/* Conversion from/to JPEG or User Defined क्रमmat is not supported */
	अगर (code && ctx->s_frame.fmt && pad == FIMC_SD_PAD_SOURCE &&
	    fimc_fmt_is_user_defined(ctx->s_frame.fmt->color))
		*code = ctx->s_frame.fmt->mbus_code;

	अगर (fourcc && *fourcc != V4L2_PIX_FMT_JPEG && pad == FIMC_SD_PAD_SOURCE)
		mask |= FMT_FLAGS_M2M;

	अगर (pad == FIMC_SD_PAD_SINK_FIFO)
		mask = FMT_FLAGS_WRITEBACK;

	ffmt = fimc_find_क्रमmat(fourcc, code, mask, 0);
	अगर (WARN_ON(!ffmt))
		वापस शून्य;

	अगर (code)
		*code = ffmt->mbus_code;
	अगर (fourcc)
		*fourcc = ffmt->fourcc;

	अगर (pad != FIMC_SD_PAD_SOURCE) अणु
		max_w = fimc_fmt_is_user_defined(ffmt->color) ?
			pl->scaler_dis_w : pl->scaler_en_w;
		/* Apply the camera input पूर्णांकerface pixel स्थिरraपूर्णांकs */
		v4l_bound_align_image(width, max_t(u32, *width, 32), max_w, 4,
				      height, max_t(u32, *height, 32),
				      FIMC_CAMIF_MAX_HEIGHT,
				      fimc_fmt_is_user_defined(ffmt->color) ?
				      3 : 1,
				      0);
		वापस ffmt;
	पूर्ण
	/* Can't scale or crop in transparent (JPEG) transfer mode */
	अगर (fimc_fmt_is_user_defined(ffmt->color)) अणु
		*width  = ctx->s_frame.f_width;
		*height = ctx->s_frame.f_height;
		वापस ffmt;
	पूर्ण
	/* Apply the scaler and the output DMA स्थिरraपूर्णांकs */
	max_w = rotation ? pl->out_rot_en_w : pl->out_rot_dis_w;
	अगर (ctx->state & FIMC_COMPOSE) अणु
		min_w = dst->offs_h + dst->width;
		min_h = dst->offs_v + dst->height;
	पूर्ण अन्यथा अणु
		min_w = var->min_out_pixsize;
		min_h = var->min_out_pixsize;
	पूर्ण
	अगर (var->min_vsize_align == 1 && !rotation)
		align_h = fimc_fmt_is_rgb(ffmt->color) ? 0 : 1;

	depth = fimc_get_क्रमmat_depth(ffmt);
	v4l_bound_align_image(width, min_w, max_w,
			      ffs(var->min_out_pixsize) - 1,
			      height, min_h, FIMC_CAMIF_MAX_HEIGHT,
			      align_h,
			      64/(ALIGN(depth, 8)));

	dbg("pad%d: code: 0x%x, %dx%d. dst fmt: %dx%d",
	    pad, code ? *code : 0, *width, *height,
	    dst->f_width, dst->f_height);

	वापस ffmt;
पूर्ण

अटल व्योम fimc_capture_try_selection(काष्ठा fimc_ctx *ctx,
				       काष्ठा v4l2_rect *r,
				       पूर्णांक target)
अणु
	bool rotate = ctx->rotation == 90 || ctx->rotation == 270;
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	स्थिर काष्ठा fimc_variant *var = fimc->variant;
	स्थिर काष्ठा fimc_pix_limit *pl = var->pix_limit;
	काष्ठा fimc_frame *sink = &ctx->s_frame;
	u32 max_w, max_h, min_w = 0, min_h = 0, min_sz;
	u32 align_sz = 0, align_h = 4;
	u32 max_sc_h, max_sc_v;

	/* In JPEG transparent transfer mode cropping is not supported */
	अगर (fimc_fmt_is_user_defined(ctx->d_frame.fmt->color)) अणु
		r->width  = sink->f_width;
		r->height = sink->f_height;
		r->left   = r->top = 0;
		वापस;
	पूर्ण
	अगर (target == V4L2_SEL_TGT_COMPOSE) अणु
		u32 पंचांगp_min_h = ffs(sink->width) - 3;
		u32 पंचांगp_min_v = ffs(sink->height) - 1;

		अगर (ctx->rotation != 90 && ctx->rotation != 270)
			align_h = 1;
		max_sc_h = min(SCALER_MAX_HRATIO, 1 << पंचांगp_min_h);
		max_sc_v = min(SCALER_MAX_VRATIO, 1 << पंचांगp_min_v);
		min_sz = var->min_out_pixsize;
	पूर्ण अन्यथा अणु
		u32 depth = fimc_get_क्रमmat_depth(sink->fmt);
		align_sz = 64/ALIGN(depth, 8);
		min_sz = var->min_inp_pixsize;
		min_w = min_h = min_sz;
		max_sc_h = max_sc_v = 1;
	पूर्ण
	/*
	 * For the compose rectangle the following स्थिरraपूर्णांकs must be met:
	 * - it must fit in the sink pad क्रमmat rectangle (f_width/f_height);
	 * - maximum करोwnscaling ratio is 64;
	 * - maximum crop size depends अगर the rotator is used or not;
	 * - the sink pad क्रमmat width/height must be 4 multiple of the
	 *   prescaler ratios determined by sink pad size and source pad crop,
	 *   the prescaler ratio is वापसed by fimc_get_scaler_factor().
	 */
	max_w = min_t(u32,
		      rotate ? pl->out_rot_en_w : pl->out_rot_dis_w,
		      rotate ? sink->f_height : sink->f_width);
	max_h = min_t(u32, FIMC_CAMIF_MAX_HEIGHT, sink->f_height);

	अगर (target == V4L2_SEL_TGT_COMPOSE) अणु
		min_w = min_t(u32, max_w, sink->f_width / max_sc_h);
		min_h = min_t(u32, max_h, sink->f_height / max_sc_v);
		अगर (rotate) अणु
			swap(max_sc_h, max_sc_v);
			swap(min_w, min_h);
		पूर्ण
	पूर्ण
	v4l_bound_align_image(&r->width, min_w, max_w, ffs(min_sz) - 1,
			      &r->height, min_h, max_h, align_h,
			      align_sz);
	/* Adjust left/top अगर crop/compose rectangle is out of bounds */
	r->left = clamp_t(u32, r->left, 0, sink->f_width - r->width);
	r->top  = clamp_t(u32, r->top, 0, sink->f_height - r->height);
	r->left = round_करोwn(r->left, var->hor_offs_align);

	dbg("target %#x: (%d,%d)/%dx%d, sink fmt: %dx%d",
	    target, r->left, r->top, r->width, r->height,
	    sink->f_width, sink->f_height);
पूर्ण

/*
 * The video node ioctl operations
 */
अटल पूर्णांक fimc_cap_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);

	__fimc_vidioc_querycap(&fimc->pdev->dev, cap);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_cap_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा fimc_fmt *fmt;

	fmt = fimc_find_क्रमmat(शून्य, शून्य, FMT_FLAGS_CAM | FMT_FLAGS_M2M,
			       f->index);
	अगर (!fmt)
		वापस -EINVAL;
	f->pixelक्रमmat = fmt->fourcc;
	वापस 0;
पूर्ण

अटल काष्ठा media_entity *fimc_pipeline_get_head(काष्ठा media_entity *me)
अणु
	काष्ठा media_pad *pad = &me->pads[0];

	जबतक (!(pad->flags & MEDIA_PAD_FL_SOURCE)) अणु
		pad = media_entity_remote_pad(pad);
		अगर (!pad)
			अवरोध;
		me = pad->entity;
		pad = &me->pads[0];
	पूर्ण

	वापस me;
पूर्ण

/**
 * fimc_pipeline_try_क्रमmat - negotiate and/or set क्रमmats at pipeline
 *                            elements
 * @ctx: FIMC capture context
 * @tfmt: media bus क्रमmat to try/set on subdevs
 * @fmt_id: fimc pixel क्रमmat id corresponding to वापसed @tfmt (output)
 * @set: true to set क्रमmat on subdevs, false to try only
 */
अटल पूर्णांक fimc_pipeline_try_क्रमmat(काष्ठा fimc_ctx *ctx,
				    काष्ठा v4l2_mbus_framefmt *tfmt,
				    काष्ठा fimc_fmt **fmt_id,
				    bool set)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(fimc->vid_cap.ve.pipe);
	काष्ठा v4l2_subdev *sd = p->subdevs[IDX_SENSOR];
	काष्ठा v4l2_subdev_क्रमmat sfmt;
	काष्ठा v4l2_mbus_framefmt *mf = &sfmt.क्रमmat;
	काष्ठा media_entity *me;
	काष्ठा fimc_fmt *ffmt;
	काष्ठा media_pad *pad;
	पूर्णांक ret, i = 1;
	u32 fcc;

	अगर (WARN_ON(!sd || !tfmt))
		वापस -EINVAL;

	स_रखो(&sfmt, 0, माप(sfmt));
	sfmt.क्रमmat = *tfmt;
	sfmt.which = set ? V4L2_SUBDEV_FORMAT_ACTIVE : V4L2_SUBDEV_FORMAT_TRY;

	me = fimc_pipeline_get_head(&sd->entity);

	जबतक (1) अणु
		ffmt = fimc_find_क्रमmat(शून्य, mf->code != 0 ? &mf->code : शून्य,
					FMT_FLAGS_CAM, i++);
		अगर (ffmt == शून्य) अणु
			/*
			 * Notअगरy user-space अगर common pixel code क्रम
			 * host and sensor करोes not exist.
			 */
			वापस -EINVAL;
		पूर्ण
		mf->code = tfmt->code = ffmt->mbus_code;

		/* set क्रमmat on all pipeline subdevs */
		जबतक (me != &fimc->vid_cap.subdev.entity) अणु
			sd = media_entity_to_v4l2_subdev(me);

			sfmt.pad = 0;
			ret = v4l2_subdev_call(sd, pad, set_fmt, शून्य, &sfmt);
			अगर (ret)
				वापस ret;

			अगर (me->pads[0].flags & MEDIA_PAD_FL_SINK) अणु
				sfmt.pad = me->num_pads - 1;
				mf->code = tfmt->code;
				ret = v4l2_subdev_call(sd, pad, set_fmt, शून्य,
									&sfmt);
				अगर (ret)
					वापस ret;
			पूर्ण

			pad = media_entity_remote_pad(&me->pads[sfmt.pad]);
			अगर (!pad)
				वापस -EINVAL;
			me = pad->entity;
		पूर्ण

		अगर (mf->code != tfmt->code)
			जारी;

		fcc = ffmt->fourcc;
		tfmt->width  = mf->width;
		tfmt->height = mf->height;
		ffmt = fimc_capture_try_क्रमmat(ctx, &tfmt->width, &tfmt->height,
					शून्य, &fcc, FIMC_SD_PAD_SINK_CAM);
		ffmt = fimc_capture_try_क्रमmat(ctx, &tfmt->width, &tfmt->height,
					शून्य, &fcc, FIMC_SD_PAD_SOURCE);
		अगर (ffmt && ffmt->mbus_code)
			mf->code = ffmt->mbus_code;
		अगर (mf->width != tfmt->width || mf->height != tfmt->height)
			जारी;
		tfmt->code = mf->code;
		अवरोध;
	पूर्ण

	अगर (fmt_id && ffmt)
		*fmt_id = ffmt;
	*tfmt = *mf;

	वापस 0;
पूर्ण

/**
 * fimc_get_sensor_frame_desc - query the sensor क्रम media bus frame parameters
 * @sensor: poपूर्णांकer to the sensor subdev
 * @plane_fmt: provides plane sizes corresponding to the frame layout entries
 * @num_planes: number of planes
 * @try: true to set the frame parameters, false to query only
 *
 * This function is used by this driver only क्रम compressed/blob data क्रमmats.
 */
अटल पूर्णांक fimc_get_sensor_frame_desc(काष्ठा v4l2_subdev *sensor,
				      काष्ठा v4l2_plane_pix_क्रमmat *plane_fmt,
				      अचिन्हित पूर्णांक num_planes, bool try)
अणु
	काष्ठा v4l2_mbus_frame_desc fd;
	पूर्णांक i, ret;
	पूर्णांक pad;

	क्रम (i = 0; i < num_planes; i++)
		fd.entry[i].length = plane_fmt[i].sizeimage;

	pad = sensor->entity.num_pads - 1;
	अगर (try)
		ret = v4l2_subdev_call(sensor, pad, set_frame_desc, pad, &fd);
	अन्यथा
		ret = v4l2_subdev_call(sensor, pad, get_frame_desc, pad, &fd);

	अगर (ret < 0)
		वापस ret;

	अगर (num_planes != fd.num_entries)
		वापस -EINVAL;

	क्रम (i = 0; i < num_planes; i++)
		plane_fmt[i].sizeimage = fd.entry[i].length;

	अगर (fd.entry[0].length > FIMC_MAX_JPEG_BUF_SIZE) अणु
		v4l2_err(sensor->v4l2_dev,  "Unsupported buffer size: %u\n",
			 fd.entry[0].length);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_cap_g_fmt_mplane(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);

	__fimc_get_क्रमmat(&fimc->vid_cap.ctx->d_frame, f);
	वापस 0;
पूर्ण

/*
 * Try or set क्रमmat on the fimc.X.capture video node and additionally
 * on the whole pipeline अगर @try is false.
 * Locking: the caller must _not_ hold the graph mutex.
 */
अटल पूर्णांक __video_try_or_set_क्रमmat(काष्ठा fimc_dev *fimc,
				     काष्ठा v4l2_क्रमmat *f, bool try,
				     काष्ठा fimc_fmt **inp_fmt,
				     काष्ठा fimc_fmt **out_fmt)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा exynos_video_entity *ve = &vc->ve;
	काष्ठा fimc_ctx *ctx = vc->ctx;
	अचिन्हित पूर्णांक width = 0, height = 0;
	पूर्णांक ret = 0;

	/* Pre-configure क्रमmat at the camera input पूर्णांकerface, क्रम JPEG only */
	अगर (fimc_jpeg_fourcc(pix->pixelक्रमmat)) अणु
		fimc_capture_try_क्रमmat(ctx, &pix->width, &pix->height,
					शून्य, &pix->pixelक्रमmat,
					FIMC_SD_PAD_SINK_CAM);
		अगर (try) अणु
			width = pix->width;
			height = pix->height;
		पूर्ण अन्यथा अणु
			ctx->s_frame.f_width = pix->width;
			ctx->s_frame.f_height = pix->height;
		पूर्ण
	पूर्ण

	/* Try the क्रमmat at the scaler and the DMA output */
	*out_fmt = fimc_capture_try_क्रमmat(ctx, &pix->width, &pix->height,
					  शून्य, &pix->pixelक्रमmat,
					  FIMC_SD_PAD_SOURCE);
	अगर (*out_fmt == शून्य)
		वापस -EINVAL;

	/* Restore image width/height क्रम JPEG (no resizing supported). */
	अगर (try && fimc_jpeg_fourcc(pix->pixelक्रमmat)) अणु
		pix->width = width;
		pix->height = height;
	पूर्ण

	/* Try to match क्रमmat at the host and the sensor */
	अगर (!vc->user_subdev_api) अणु
		काष्ठा v4l2_mbus_framefmt mbus_fmt;
		काष्ठा v4l2_mbus_framefmt *mf;

		mf = try ? &mbus_fmt : &fimc->vid_cap.ci_fmt;

		mf->code = (*out_fmt)->mbus_code;
		mf->width = pix->width;
		mf->height = pix->height;

		fimc_md_graph_lock(ve);
		ret = fimc_pipeline_try_क्रमmat(ctx, mf, inp_fmt, try);
		fimc_md_graph_unlock(ve);

		अगर (ret < 0)
			वापस ret;

		pix->width = mf->width;
		pix->height = mf->height;
	पूर्ण

	fimc_adjust_mplane_क्रमmat(*out_fmt, pix->width, pix->height, pix);

	अगर ((*out_fmt)->flags & FMT_FLAGS_COMPRESSED) अणु
		काष्ठा v4l2_subdev *sensor;

		fimc_md_graph_lock(ve);

		sensor = __fimc_md_get_subdev(ve->pipe, IDX_SENSOR);
		अगर (sensor)
			fimc_get_sensor_frame_desc(sensor, pix->plane_fmt,
						   (*out_fmt)->memplanes, try);
		अन्यथा
			ret = -EPIPE;

		fimc_md_graph_unlock(ve);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_cap_try_fmt_mplane(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_fmt *out_fmt = शून्य, *inp_fmt = शून्य;

	वापस __video_try_or_set_क्रमmat(fimc, f, true, &inp_fmt, &out_fmt);
पूर्ण

अटल व्योम fimc_capture_mark_jpeg_xfer(काष्ठा fimc_ctx *ctx,
					क्रमागत fimc_color_fmt color)
अणु
	bool jpeg = fimc_fmt_is_user_defined(color);

	ctx->scaler.enabled = !jpeg;
	fimc_ctrls_activate(ctx, !jpeg);

	अगर (jpeg)
		set_bit(ST_CAPT_JPEG, &ctx->fimc_dev->state);
	अन्यथा
		clear_bit(ST_CAPT_JPEG, &ctx->fimc_dev->state);
पूर्ण

अटल पूर्णांक __fimc_capture_set_क्रमmat(काष्ठा fimc_dev *fimc,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा fimc_ctx *ctx = vc->ctx;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा fimc_frame *ff = &ctx->d_frame;
	काष्ठा fimc_fmt *inp_fmt = शून्य;
	पूर्णांक ret, i;

	अगर (vb2_is_busy(&fimc->vid_cap.vbq))
		वापस -EBUSY;

	ret = __video_try_or_set_क्रमmat(fimc, f, false, &inp_fmt, &ff->fmt);
	अगर (ret < 0)
		वापस ret;

	/* Update RGB Alpha control state and value range */
	fimc_alpha_ctrl_update(ctx);

	क्रम (i = 0; i < ff->fmt->memplanes; i++) अणु
		ff->bytesperline[i] = pix->plane_fmt[i].bytesperline;
		ff->payload[i] = pix->plane_fmt[i].sizeimage;
	पूर्ण

	set_frame_bounds(ff, pix->width, pix->height);
	/* Reset the composition rectangle अगर not yet configured */
	अगर (!(ctx->state & FIMC_COMPOSE))
		set_frame_crop(ff, 0, 0, pix->width, pix->height);

	fimc_capture_mark_jpeg_xfer(ctx, ff->fmt->color);

	/* Reset cropping and set क्रमmat at the camera पूर्णांकerface input */
	अगर (!vc->user_subdev_api) अणु
		ctx->s_frame.fmt = inp_fmt;
		set_frame_bounds(&ctx->s_frame, pix->width, pix->height);
		set_frame_crop(&ctx->s_frame, 0, 0, pix->width, pix->height);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_cap_s_fmt_mplane(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);

	वापस __fimc_capture_set_क्रमmat(fimc, f);
पूर्ण

अटल पूर्णांक fimc_cap_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_input *i)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा exynos_video_entity *ve = &fimc->vid_cap.ve;
	काष्ठा v4l2_subdev *sd;

	अगर (i->index != 0)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	fimc_md_graph_lock(ve);
	sd = __fimc_md_get_subdev(ve->pipe, IDX_SENSOR);
	fimc_md_graph_unlock(ve);

	अगर (sd)
		strscpy(i->name, sd->name, माप(i->name));

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_cap_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस i == 0 ? i : -EINVAL;
पूर्ण

अटल पूर्णांक fimc_cap_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

/**
 * fimc_pipeline_validate - check क्रम क्रमmats inconsistencies
 *                          between source and sink pad of each link
 * @fimc:	the FIMC device this context applies to
 *
 * Return 0 अगर all क्रमmats match or -EPIPE otherwise.
 */
अटल पूर्णांक fimc_pipeline_validate(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा v4l2_subdev_क्रमmat sink_fmt, src_fmt;
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा v4l2_subdev *sd = &vc->subdev;
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(vc->ve.pipe);
	काष्ठा media_pad *sink_pad, *src_pad;
	पूर्णांक i, ret;

	जबतक (1) अणु
		/*
		 * Find current entity sink pad and any remote sink pad linked
		 * to it. We stop अगर there is no sink pad in current entity or
		 * it is not linked to any other remote entity.
		 */
		src_pad = शून्य;

		क्रम (i = 0; i < sd->entity.num_pads; i++) अणु
			काष्ठा media_pad *p = &sd->entity.pads[i];

			अगर (p->flags & MEDIA_PAD_FL_SINK) अणु
				sink_pad = p;
				src_pad = media_entity_remote_pad(sink_pad);
				अगर (src_pad)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (!src_pad || !is_media_entity_v4l2_subdev(src_pad->entity))
			अवरोध;

		/* Don't call FIMC subdev operation to aव्योम nested locking */
		अगर (sd == &vc->subdev) अणु
			काष्ठा fimc_frame *ff = &vc->ctx->s_frame;
			sink_fmt.क्रमmat.width = ff->f_width;
			sink_fmt.क्रमmat.height = ff->f_height;
			sink_fmt.क्रमmat.code = ff->fmt ? ff->fmt->mbus_code : 0;
		पूर्ण अन्यथा अणु
			sink_fmt.pad = sink_pad->index;
			sink_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
			ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &sink_fmt);
			अगर (ret < 0 && ret != -ENOIOCTLCMD)
				वापस -EPIPE;
		पूर्ण

		/* Retrieve क्रमmat at the source pad */
		sd = media_entity_to_v4l2_subdev(src_pad->entity);
		src_fmt.pad = src_pad->index;
		src_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &src_fmt);
		अगर (ret < 0 && ret != -ENOIOCTLCMD)
			वापस -EPIPE;

		अगर (src_fmt.क्रमmat.width != sink_fmt.क्रमmat.width ||
		    src_fmt.क्रमmat.height != sink_fmt.क्रमmat.height ||
		    src_fmt.क्रमmat.code != sink_fmt.क्रमmat.code)
			वापस -EPIPE;

		अगर (sd == p->subdevs[IDX_SENSOR] &&
		    fimc_user_defined_mbus_fmt(src_fmt.क्रमmat.code)) अणु
			काष्ठा v4l2_plane_pix_क्रमmat plane_fmt[FIMC_MAX_PLANES];
			काष्ठा fimc_frame *frame = &vc->ctx->d_frame;
			अचिन्हित पूर्णांक i;

			ret = fimc_get_sensor_frame_desc(sd, plane_fmt,
							 frame->fmt->memplanes,
							 false);
			अगर (ret < 0)
				वापस -EPIPE;

			क्रम (i = 0; i < frame->fmt->memplanes; i++)
				अगर (frame->payload[i] < plane_fmt[i].sizeimage)
					वापस -EPIPE;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_cap_streamon(काष्ठा file *file, व्योम *priv,
			     क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा media_entity *entity = &vc->ve.vdev.entity;
	काष्ठा fimc_source_info *si = शून्य;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	अगर (fimc_capture_active(fimc))
		वापस -EBUSY;

	ret = media_pipeline_start(entity, &vc->ve.pipe->mp);
	अगर (ret < 0)
		वापस ret;

	sd = __fimc_md_get_subdev(vc->ve.pipe, IDX_SENSOR);
	अगर (sd)
		si = v4l2_get_subdev_hostdata(sd);

	अगर (si == शून्य) अणु
		ret = -EPIPE;
		जाओ err_p_stop;
	पूर्ण
	/*
	 * Save configuration data related to currently attached image
	 * sensor or other data source, e.g. FIMC-IS.
	 */
	vc->source_config = *si;

	अगर (vc->input == GRP_ID_FIMC_IS)
		vc->source_config.fimc_bus_type = FIMC_BUS_TYPE_ISP_WRITEBACK;

	अगर (vc->user_subdev_api) अणु
		ret = fimc_pipeline_validate(fimc);
		अगर (ret < 0)
			जाओ err_p_stop;
	पूर्ण

	ret = vb2_ioctl_streamon(file, priv, type);
	अगर (!ret) अणु
		vc->streaming = true;
		वापस ret;
	पूर्ण

err_p_stop:
	media_pipeline_stop(entity);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_cap_streamoff(काष्ठा file *file, व्योम *priv,
			    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	पूर्णांक ret;

	ret = vb2_ioctl_streamoff(file, priv, type);
	अगर (ret < 0)
		वापस ret;

	अगर (vc->streaming) अणु
		media_pipeline_stop(&vc->ve.vdev.entity);
		vc->streaming = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_cap_reqbufs(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	पूर्णांक ret;

	ret = vb2_ioctl_reqbufs(file, priv, reqbufs);

	अगर (!ret)
		fimc->vid_cap.reqbufs_count = reqbufs->count;

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_cap_g_selection(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_selection *s)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_ctx *ctx = fimc->vid_cap.ctx;
	काष्ठा fimc_frame *f = &ctx->s_frame;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		f = &ctx->d_frame;
		fallthrough;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = f->o_width;
		s->r.height = f->o_height;
		वापस 0;

	हाल V4L2_SEL_TGT_COMPOSE:
		f = &ctx->d_frame;
		fallthrough;
	हाल V4L2_SEL_TGT_CROP:
		s->r.left = f->offs_h;
		s->r.top = f->offs_v;
		s->r.width = f->width;
		s->r.height = f->height;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fimc_cap_s_selection(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_selection *s)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_ctx *ctx = fimc->vid_cap.ctx;
	काष्ठा v4l2_rect rect = s->r;
	काष्ठा fimc_frame *f;
	अचिन्हित दीर्घ flags;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (s->target == V4L2_SEL_TGT_COMPOSE)
		f = &ctx->d_frame;
	अन्यथा अगर (s->target == V4L2_SEL_TGT_CROP)
		f = &ctx->s_frame;
	अन्यथा
		वापस -EINVAL;

	fimc_capture_try_selection(ctx, &rect, s->target);

	अगर (s->flags & V4L2_SEL_FLAG_LE &&
	    !v4l2_rect_enबंदd(&rect, &s->r))
		वापस -दुस्फल;

	अगर (s->flags & V4L2_SEL_FLAG_GE &&
	    !v4l2_rect_enबंदd(&s->r, &rect))
		वापस -दुस्फल;

	s->r = rect;
	spin_lock_irqsave(&fimc->slock, flags);
	set_frame_crop(f, s->r.left, s->r.top, s->r.width,
		       s->r.height);
	spin_unlock_irqrestore(&fimc->slock, flags);

	set_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops fimc_capture_ioctl_ops = अणु
	.vidioc_querycap		= fimc_cap_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= fimc_cap_क्रमागत_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= fimc_cap_try_fmt_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= fimc_cap_s_fmt_mplane,
	.vidioc_g_fmt_vid_cap_mplane	= fimc_cap_g_fmt_mplane,

	.vidioc_reqbufs			= fimc_cap_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,

	.vidioc_streamon		= fimc_cap_streamon,
	.vidioc_streamoff		= fimc_cap_streamoff,

	.vidioc_g_selection		= fimc_cap_g_selection,
	.vidioc_s_selection		= fimc_cap_s_selection,

	.vidioc_क्रमागत_input		= fimc_cap_क्रमागत_input,
	.vidioc_s_input			= fimc_cap_s_input,
	.vidioc_g_input			= fimc_cap_g_input,
पूर्ण;

/* Capture subdev media entity operations */
अटल पूर्णांक fimc_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा v4l2_subdev *sensor;

	अगर (!is_media_entity_v4l2_subdev(remote->entity))
		वापस -EINVAL;

	अगर (WARN_ON(fimc == शून्य))
		वापस 0;

	dbg("%s --> %s, flags: 0x%x. input: 0x%x",
	    local->entity->name, remote->entity->name, flags,
	    fimc->vid_cap.input);

	अगर (!(flags & MEDIA_LNK_FL_ENABLED)) अणु
		fimc->vid_cap.input = 0;
		वापस 0;
	पूर्ण

	अगर (vc->input != 0)
		वापस -EBUSY;

	vc->input = sd->grp_id;

	अगर (vc->user_subdev_api)
		वापस 0;

	/* Inherit V4L2 controls from the image sensor subdev. */
	sensor = fimc_find_remote_sensor(&vc->subdev.entity);
	अगर (sensor == शून्य)
		वापस 0;

	वापस v4l2_ctrl_add_handler(&vc->ctx->ctrls.handler,
				     sensor->ctrl_handler, शून्य, true);
पूर्ण

अटल स्थिर काष्ठा media_entity_operations fimc_sd_media_ops = अणु
	.link_setup = fimc_link_setup,
पूर्ण;

/**
 * fimc_sensor_notअगरy - v4l2_device notअगरication from a sensor subdev
 * @sd: poपूर्णांकer to a subdev generating the notअगरication
 * @notअगरication: the notअगरication type, must be S5P_FIMC_TX_END_NOTIFY
 * @arg: poपूर्णांकer to an u32 type पूर्णांकeger that stores the frame payload value
 *
 * The End Of Frame notअगरication sent by sensor subdev in its still capture
 * mode. If there is only a single VSYNC generated by the sensor at the
 * beginning of a frame transmission, FIMC करोes not issue the LastIrq
 * (end of frame) पूर्णांकerrupt. And this notअगरication is used to complete the
 * frame capture and वापसing a buffer to user-space. Subdev drivers should
 * call this notअगरication from their last 'End of frame capture' पूर्णांकerrupt.
 */
व्योम fimc_sensor_notअगरy(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक notअगरication,
			व्योम *arg)
अणु
	काष्ठा fimc_source_info	*si;
	काष्ठा fimc_vid_buffer *buf;
	काष्ठा fimc_md *fmd;
	काष्ठा fimc_dev *fimc;
	अचिन्हित दीर्घ flags;

	अगर (sd == शून्य)
		वापस;

	si = v4l2_get_subdev_hostdata(sd);
	fmd = entity_to_fimc_mdev(&sd->entity);

	spin_lock_irqsave(&fmd->slock, flags);

	fimc = si ? source_to_sensor_info(si)->host : शून्य;

	अगर (fimc && arg && notअगरication == S5P_FIMC_TX_END_NOTIFY &&
	    test_bit(ST_CAPT_PEND, &fimc->state)) अणु
		अचिन्हित दीर्घ irq_flags;
		spin_lock_irqsave(&fimc->slock, irq_flags);
		अगर (!list_empty(&fimc->vid_cap.active_buf_q)) अणु
			buf = list_entry(fimc->vid_cap.active_buf_q.next,
					 काष्ठा fimc_vid_buffer, list);
			vb2_set_plane_payload(&buf->vb.vb2_buf, 0,
					      *((u32 *)arg));
		पूर्ण
		fimc_capture_irq_handler(fimc, 1);
		fimc_deactivate_capture(fimc);
		spin_unlock_irqrestore(&fimc->slock, irq_flags);
	पूर्ण
	spin_unlock_irqrestore(&fmd->slock, flags);
पूर्ण

अटल पूर्णांक fimc_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा fimc_fmt *fmt;

	fmt = fimc_find_क्रमmat(शून्य, शून्य, FMT_FLAGS_CAM, code->index);
	अगर (!fmt)
		वापस -EINVAL;
	code->code = fmt->mbus_code;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_subdev_get_fmt(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	काष्ठा fimc_ctx *ctx = fimc->vid_cap.ctx;
	काष्ठा fimc_frame *ff = &ctx->s_frame;
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		fmt->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mf = &fmt->क्रमmat;
	mutex_lock(&fimc->lock);

	चयन (fmt->pad) अणु
	हाल FIMC_SD_PAD_SOURCE:
		अगर (!WARN_ON(ff->fmt == शून्य))
			mf->code = ff->fmt->mbus_code;
		/* Sink pads crop rectangle size */
		mf->width = ff->width;
		mf->height = ff->height;
		अवरोध;
	हाल FIMC_SD_PAD_SINK_FIFO:
		*mf = fimc->vid_cap.wb_fmt;
		अवरोध;
	हाल FIMC_SD_PAD_SINK_CAM:
	शेष:
		*mf = fimc->vid_cap.ci_fmt;
		अवरोध;
	पूर्ण

	mutex_unlock(&fimc->lock);
	mf->colorspace = V4L2_COLORSPACE_JPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_subdev_set_fmt(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा fimc_vid_cap *vc = &fimc->vid_cap;
	काष्ठा fimc_ctx *ctx = vc->ctx;
	काष्ठा fimc_frame *ff;
	काष्ठा fimc_fmt *ffmt;

	dbg("pad%d: code: 0x%x, %dx%d",
	    fmt->pad, mf->code, mf->width, mf->height);

	अगर (fmt->pad == FIMC_SD_PAD_SOURCE && vb2_is_busy(&vc->vbq))
		वापस -EBUSY;

	mutex_lock(&fimc->lock);
	ffmt = fimc_capture_try_क्रमmat(ctx, &mf->width, &mf->height,
				       &mf->code, शून्य, fmt->pad);
	mutex_unlock(&fimc->lock);
	mf->colorspace = V4L2_COLORSPACE_JPEG;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;
		वापस 0;
	पूर्ण
	/* There must be a bug in the driver अगर this happens */
	अगर (WARN_ON(ffmt == शून्य))
		वापस -EINVAL;

	/* Update RGB Alpha control state and value range */
	fimc_alpha_ctrl_update(ctx);

	fimc_capture_mark_jpeg_xfer(ctx, ffmt->color);
	अगर (fmt->pad == FIMC_SD_PAD_SOURCE) अणु
		ff = &ctx->d_frame;
		/* Sink pads crop rectangle size */
		mf->width = ctx->s_frame.width;
		mf->height = ctx->s_frame.height;
	पूर्ण अन्यथा अणु
		ff = &ctx->s_frame;
	पूर्ण

	mutex_lock(&fimc->lock);
	set_frame_bounds(ff, mf->width, mf->height);

	अगर (fmt->pad == FIMC_SD_PAD_SINK_FIFO)
		vc->wb_fmt = *mf;
	अन्यथा अगर (fmt->pad == FIMC_SD_PAD_SINK_CAM)
		vc->ci_fmt = *mf;

	ff->fmt = ffmt;

	/* Reset the crop rectangle अगर required. */
	अगर (!(fmt->pad == FIMC_SD_PAD_SOURCE && (ctx->state & FIMC_COMPOSE)))
		set_frame_crop(ff, 0, 0, mf->width, mf->height);

	अगर (fmt->pad != FIMC_SD_PAD_SOURCE)
		ctx->state &= ~FIMC_COMPOSE;

	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_subdev_get_selection(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	काष्ठा fimc_ctx *ctx = fimc->vid_cap.ctx;
	काष्ठा fimc_frame *f = &ctx->s_frame;
	काष्ठा v4l2_rect *r = &sel->r;
	काष्ठा v4l2_rect *try_sel;

	अगर (sel->pad == FIMC_SD_PAD_SOURCE)
		वापस -EINVAL;

	mutex_lock(&fimc->lock);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		f = &ctx->d_frame;
		fallthrough;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		r->width = f->o_width;
		r->height = f->o_height;
		r->left = 0;
		r->top = 0;
		mutex_unlock(&fimc->lock);
		वापस 0;

	हाल V4L2_SEL_TGT_CROP:
		try_sel = v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		try_sel = v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		f = &ctx->d_frame;
		अवरोध;
	शेष:
		mutex_unlock(&fimc->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		sel->r = *try_sel;
	पूर्ण अन्यथा अणु
		r->left = f->offs_h;
		r->top = f->offs_v;
		r->width = f->width;
		r->height = f->height;
	पूर्ण

	dbg("target %#x: l:%d, t:%d, %dx%d, f_w: %d, f_h: %d",
	    sel->pad, r->left, r->top, r->width, r->height,
	    f->f_width, f->f_height);

	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_subdev_set_selection(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	काष्ठा fimc_ctx *ctx = fimc->vid_cap.ctx;
	काष्ठा fimc_frame *f = &ctx->s_frame;
	काष्ठा v4l2_rect *r = &sel->r;
	काष्ठा v4l2_rect *try_sel;
	अचिन्हित दीर्घ flags;

	अगर (sel->pad == FIMC_SD_PAD_SOURCE)
		वापस -EINVAL;

	mutex_lock(&fimc->lock);
	fimc_capture_try_selection(ctx, r, V4L2_SEL_TGT_CROP);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		try_sel = v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		try_sel = v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		f = &ctx->d_frame;
		अवरोध;
	शेष:
		mutex_unlock(&fimc->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*try_sel = sel->r;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&fimc->slock, flags);
		set_frame_crop(f, r->left, r->top, r->width, r->height);
		set_bit(ST_CAPT_APPLY_CFG, &fimc->state);
		अगर (sel->target == V4L2_SEL_TGT_COMPOSE)
			ctx->state |= FIMC_COMPOSE;
		spin_unlock_irqrestore(&fimc->slock, flags);
	पूर्ण

	dbg("target %#x: (%d,%d)/%dx%d", sel->target, r->left, r->top,
	    r->width, r->height);

	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops fimc_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = fimc_subdev_क्रमागत_mbus_code,
	.get_selection = fimc_subdev_get_selection,
	.set_selection = fimc_subdev_set_selection,
	.get_fmt = fimc_subdev_get_fmt,
	.set_fmt = fimc_subdev_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops fimc_subdev_ops = अणु
	.pad = &fimc_subdev_pad_ops,
पूर्ण;

/* Set शेष क्रमmat at the sensor and host पूर्णांकerface */
अटल पूर्णांक fimc_capture_set_शेष_क्रमmat(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा v4l2_क्रमmat fmt = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
		.fmt.pix_mp = अणु
			.width		= FIMC_DEFAULT_WIDTH,
			.height		= FIMC_DEFAULT_HEIGHT,
			.pixelक्रमmat	= V4L2_PIX_FMT_YUYV,
			.field		= V4L2_FIELD_NONE,
			.colorspace	= V4L2_COLORSPACE_JPEG,
		पूर्ण,
	पूर्ण;

	वापस __fimc_capture_set_क्रमmat(fimc, &fmt);
पूर्ण

/* fimc->lock must be alपढ़ोy initialized */
अटल पूर्णांक fimc_रेजिस्टर_capture_device(काष्ठा fimc_dev *fimc,
				 काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा video_device *vfd = &fimc->vid_cap.ve.vdev;
	काष्ठा vb2_queue *q = &fimc->vid_cap.vbq;
	काष्ठा fimc_ctx *ctx;
	काष्ठा fimc_vid_cap *vid_cap;
	काष्ठा fimc_fmt *fmt;
	पूर्णांक ret = -ENOMEM;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->fimc_dev	 = fimc;
	ctx->in_path	 = FIMC_IO_CAMERA;
	ctx->out_path	 = FIMC_IO_DMA;
	ctx->state	 = FIMC_CTX_CAP;
	ctx->s_frame.fmt = fimc_find_क्रमmat(शून्य, शून्य, FMT_FLAGS_CAM, 0);
	ctx->d_frame.fmt = ctx->s_frame.fmt;

	स_रखो(vfd, 0, माप(*vfd));
	snम_लिखो(vfd->name, माप(vfd->name), "fimc.%d.capture", fimc->id);

	vfd->fops	= &fimc_capture_fops;
	vfd->ioctl_ops	= &fimc_capture_ioctl_ops;
	vfd->v4l2_dev	= v4l2_dev;
	vfd->minor	= -1;
	vfd->release	= video_device_release_empty;
	vfd->queue	= q;
	vfd->lock	= &fimc->lock;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE;

	video_set_drvdata(vfd, fimc);
	vid_cap = &fimc->vid_cap;
	vid_cap->active_buf_cnt = 0;
	vid_cap->reqbufs_count = 0;
	vid_cap->ctx = ctx;

	INIT_LIST_HEAD(&vid_cap->pending_buf_q);
	INIT_LIST_HEAD(&vid_cap->active_buf_q);

	स_रखो(q, 0, माप(*q));
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv = ctx;
	q->ops = &fimc_capture_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा fimc_vid_buffer);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &fimc->lock;
	q->dev = &fimc->pdev->dev;

	ret = vb2_queue_init(q);
	अगर (ret)
		जाओ err_मुक्त_ctx;

	/* Default क्रमmat configuration */
	fmt = fimc_find_क्रमmat(शून्य, शून्य, FMT_FLAGS_CAM, 0);
	vid_cap->ci_fmt.width = FIMC_DEFAULT_WIDTH;
	vid_cap->ci_fmt.height = FIMC_DEFAULT_HEIGHT;
	vid_cap->ci_fmt.code = fmt->mbus_code;

	ctx->s_frame.width = FIMC_DEFAULT_WIDTH;
	ctx->s_frame.height = FIMC_DEFAULT_HEIGHT;
	ctx->s_frame.fmt = fmt;

	fmt = fimc_find_क्रमmat(शून्य, शून्य, FMT_FLAGS_WRITEBACK, 0);
	vid_cap->wb_fmt = vid_cap->ci_fmt;
	vid_cap->wb_fmt.code = fmt->mbus_code;

	vid_cap->vd_pad.flags = MEDIA_PAD_FL_SINK;
	vfd->entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;
	ret = media_entity_pads_init(&vfd->entity, 1, &vid_cap->vd_pad);
	अगर (ret)
		जाओ err_मुक्त_ctx;

	ret = fimc_ctrls_create(ctx);
	अगर (ret)
		जाओ err_me_cleanup;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ err_ctrl_मुक्त;

	v4l2_info(v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));

	vfd->ctrl_handler = &ctx->ctrls.handler;
	वापस 0;

err_ctrl_मुक्त:
	fimc_ctrls_delete(ctx);
err_me_cleanup:
	media_entity_cleanup(&vfd->entity);
err_मुक्त_ctx:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_capture_subdev_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (fimc == शून्य)
		वापस -ENXIO;

	ret = fimc_रेजिस्टर_m2m_device(fimc, sd->v4l2_dev);
	अगर (ret)
		वापस ret;

	fimc->vid_cap.ve.pipe = v4l2_get_subdev_hostdata(sd);

	ret = fimc_रेजिस्टर_capture_device(fimc, sd->v4l2_dev);
	अगर (ret) अणु
		fimc_unरेजिस्टर_m2m_device(fimc);
		fimc->vid_cap.ve.pipe = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम fimc_capture_subdev_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_dev *fimc = v4l2_get_subdevdata(sd);
	काष्ठा video_device *vdev;

	अगर (fimc == शून्य)
		वापस;

	mutex_lock(&fimc->lock);

	fimc_unरेजिस्टर_m2m_device(fimc);
	vdev = &fimc->vid_cap.ve.vdev;

	अगर (video_is_रेजिस्टरed(vdev)) अणु
		video_unरेजिस्टर_device(vdev);
		media_entity_cleanup(&vdev->entity);
		fimc_ctrls_delete(fimc->vid_cap.ctx);
		fimc->vid_cap.ve.pipe = शून्य;
	पूर्ण
	kमुक्त(fimc->vid_cap.ctx);
	fimc->vid_cap.ctx = शून्य;

	mutex_unlock(&fimc->lock);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops fimc_capture_sd_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = fimc_capture_subdev_रेजिस्टरed,
	.unरेजिस्टरed = fimc_capture_subdev_unरेजिस्टरed,
पूर्ण;

पूर्णांक fimc_initialize_capture_subdev(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा v4l2_subdev *sd = &fimc->vid_cap.subdev;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &fimc_subdev_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snम_लिखो(sd->name, माप(sd->name), "FIMC.%d", fimc->id);

	fimc->vid_cap.sd_pads[FIMC_SD_PAD_SINK_CAM].flags = MEDIA_PAD_FL_SINK;
	fimc->vid_cap.sd_pads[FIMC_SD_PAD_SINK_FIFO].flags = MEDIA_PAD_FL_SINK;
	fimc->vid_cap.sd_pads[FIMC_SD_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sd->entity, FIMC_SD_PADS_NUM,
				fimc->vid_cap.sd_pads);
	अगर (ret)
		वापस ret;

	sd->entity.ops = &fimc_sd_media_ops;
	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;
	sd->पूर्णांकernal_ops = &fimc_capture_sd_पूर्णांकernal_ops;
	v4l2_set_subdevdata(sd, fimc);
	वापस 0;
पूर्ण

व्योम fimc_unरेजिस्टर_capture_subdev(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा v4l2_subdev *sd = &fimc->vid_cap.subdev;

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_set_subdevdata(sd, शून्य);
पूर्ण
