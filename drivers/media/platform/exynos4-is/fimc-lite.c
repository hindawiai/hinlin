<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS FIMC-LITE (camera host पूर्णांकerface) driver
*
 * Copyright (C) 2012 - 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-rect.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#समावेश "common.h"
#समावेश "fimc-core.h"
#समावेश "fimc-lite.h"
#समावेश "fimc-lite-reg.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

अटल स्थिर काष्ठा fimc_fmt fimc_lite_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCBYCR422,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.flags		= FMT_FLAGS_YUV,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_CBYCRY422,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
		.flags		= FMT_FLAGS_YUV,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_VYUY,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_CRYCBY422,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_2X8,
		.flags		= FMT_FLAGS_YUV,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCRYCB422,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_2X8,
		.flags		= FMT_FLAGS_YUV,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.depth		= अणु 8 पूर्ण,
		.color		= FIMC_FMT_RAW8,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG8_1X8,
		.flags		= FMT_FLAGS_RAW_BAYER,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG10,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_RAW10,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG10_1X10,
		.flags		= FMT_FLAGS_RAW_BAYER,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG12,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_RAW12,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG12_1X12,
		.flags		= FMT_FLAGS_RAW_BAYER,
	पूर्ण,
पूर्ण;

/**
 * fimc_lite_find_क्रमmat - lookup fimc color क्रमmat by fourcc or media bus code
 * @pixelक्रमmat: fourcc to match, ignored अगर null
 * @mbus_code: media bus code to match, ignored अगर null
 * @mask: the color क्रमmat flags to match
 * @index: index to the fimc_lite_क्रमmats array, ignored अगर negative
 */
अटल स्थिर काष्ठा fimc_fmt *fimc_lite_find_क्रमmat(स्थिर u32 *pixelक्रमmat,
			स्थिर u32 *mbus_code, अचिन्हित पूर्णांक mask, पूर्णांक index)
अणु
	स्थिर काष्ठा fimc_fmt *fmt, *def_fmt = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक id = 0;

	अगर (index >= (पूर्णांक)ARRAY_SIZE(fimc_lite_क्रमmats))
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(fimc_lite_क्रमmats); ++i) अणु
		fmt = &fimc_lite_क्रमmats[i];
		अगर (mask && !(fmt->flags & mask))
			जारी;
		अगर (pixelक्रमmat && fmt->fourcc == *pixelक्रमmat)
			वापस fmt;
		अगर (mbus_code && fmt->mbus_code == *mbus_code)
			वापस fmt;
		अगर (index == id)
			def_fmt = fmt;
		id++;
	पूर्ण
	वापस def_fmt;
पूर्ण

अटल पूर्णांक fimc_lite_hw_init(काष्ठा fimc_lite *fimc, bool isp_output)
अणु
	काष्ठा fimc_source_info *si;
	अचिन्हित दीर्घ flags;

	अगर (fimc->sensor == शून्य)
		वापस -ENXIO;

	अगर (fimc->inp_frame.fmt == शून्य || fimc->out_frame.fmt == शून्य)
		वापस -EINVAL;

	/* Get sensor configuration data from the sensor subdev */
	si = v4l2_get_subdev_hostdata(fimc->sensor);
	अगर (!si)
		वापस -EINVAL;

	spin_lock_irqsave(&fimc->slock, flags);

	flite_hw_set_camera_bus(fimc, si);
	flite_hw_set_source_क्रमmat(fimc, &fimc->inp_frame);
	flite_hw_set_winकरोw_offset(fimc, &fimc->inp_frame);
	flite_hw_set_dma_buf_mask(fimc, 0);
	flite_hw_set_output_dma(fimc, &fimc->out_frame, !isp_output);
	flite_hw_set_पूर्णांकerrupt_mask(fimc);
	flite_hw_set_test_pattern(fimc, fimc->test_pattern->val);

	अगर (debug > 0)
		flite_hw_dump_regs(fimc, __func__);

	spin_unlock_irqrestore(&fimc->slock, flags);
	वापस 0;
पूर्ण

/*
 * Reinitialize the driver so it is पढ़ोy to start the streaming again.
 * Set fimc->state to indicate stream off and the hardware shut करोwn state.
 * If not suspending (@suspend is false), वापस any buffers to videobuf2.
 * Otherwise put any owned buffers onto the pending buffers queue, so they
 * can be re-spun when the device is being resumed. Also perक्रमm FIMC
 * software reset and disable streaming on the whole pipeline अगर required.
 */
अटल पूर्णांक fimc_lite_reinit(काष्ठा fimc_lite *fimc, bool suspend)
अणु
	काष्ठा flite_buffer *buf;
	अचिन्हित दीर्घ flags;
	bool streaming;

	spin_lock_irqsave(&fimc->slock, flags);
	streaming = fimc->state & (1 << ST_SENSOR_STREAM);

	fimc->state &= ~(1 << ST_FLITE_RUN | 1 << ST_FLITE_OFF |
			 1 << ST_FLITE_STREAM | 1 << ST_SENSOR_STREAM);
	अगर (suspend)
		fimc->state |= (1 << ST_FLITE_SUSPENDED);
	अन्यथा
		fimc->state &= ~(1 << ST_FLITE_PENDING |
				 1 << ST_FLITE_SUSPENDED);

	/* Release unused buffers */
	जबतक (!suspend && !list_empty(&fimc->pending_buf_q)) अणु
		buf = fimc_lite_pending_queue_pop(fimc);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	/* If suspending put unused buffers onto pending queue */
	जबतक (!list_empty(&fimc->active_buf_q)) अणु
		buf = fimc_lite_active_queue_pop(fimc);
		अगर (suspend)
			fimc_lite_pending_queue_add(fimc, buf);
		अन्यथा
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	spin_unlock_irqrestore(&fimc->slock, flags);

	flite_hw_reset(fimc);

	अगर (!streaming)
		वापस 0;

	वापस fimc_pipeline_call(&fimc->ve, set_stream, 0);
पूर्ण

अटल पूर्णांक fimc_lite_stop_capture(काष्ठा fimc_lite *fimc, bool suspend)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!fimc_lite_active(fimc))
		वापस 0;

	spin_lock_irqsave(&fimc->slock, flags);
	set_bit(ST_FLITE_OFF, &fimc->state);
	flite_hw_capture_stop(fimc);
	spin_unlock_irqrestore(&fimc->slock, flags);

	रुको_event_समयout(fimc->irq_queue,
			   !test_bit(ST_FLITE_OFF, &fimc->state),
			   (2*HZ/10)); /* 200 ms */

	वापस fimc_lite_reinit(fimc, suspend);
पूर्ण

/* Must be called  with fimc.slock spinlock held. */
अटल व्योम fimc_lite_config_update(काष्ठा fimc_lite *fimc)
अणु
	flite_hw_set_winकरोw_offset(fimc, &fimc->inp_frame);
	flite_hw_set_dma_winकरोw(fimc, &fimc->out_frame);
	flite_hw_set_test_pattern(fimc, fimc->test_pattern->val);
	clear_bit(ST_FLITE_CONFIG, &fimc->state);
पूर्ण

अटल irqवापस_t flite_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा fimc_lite *fimc = priv;
	काष्ठा flite_buffer *vbuf;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकsrc;

	spin_lock_irqsave(&fimc->slock, flags);

	पूर्णांकsrc = flite_hw_get_पूर्णांकerrupt_source(fimc);
	flite_hw_clear_pending_irq(fimc);

	अगर (test_and_clear_bit(ST_FLITE_OFF, &fimc->state)) अणु
		wake_up(&fimc->irq_queue);
		जाओ करोne;
	पूर्ण

	अगर (पूर्णांकsrc & FLITE_REG_CISTATUS_IRQ_SRC_OVERFLOW) अणु
		clear_bit(ST_FLITE_RUN, &fimc->state);
		fimc->events.data_overflow++;
	पूर्ण

	अगर (पूर्णांकsrc & FLITE_REG_CISTATUS_IRQ_SRC_LASTCAPEND) अणु
		flite_hw_clear_last_capture_end(fimc);
		clear_bit(ST_FLITE_STREAM, &fimc->state);
		wake_up(&fimc->irq_queue);
	पूर्ण

	अगर (atomic_पढ़ो(&fimc->out_path) != FIMC_IO_DMA)
		जाओ करोne;

	अगर ((पूर्णांकsrc & FLITE_REG_CISTATUS_IRQ_SRC_FRMSTART) &&
	    test_bit(ST_FLITE_RUN, &fimc->state) &&
	    !list_empty(&fimc->pending_buf_q)) अणु
		vbuf = fimc_lite_pending_queue_pop(fimc);
		flite_hw_set_dma_buffer(fimc, vbuf);
		fimc_lite_active_queue_add(fimc, vbuf);
	पूर्ण

	अगर ((पूर्णांकsrc & FLITE_REG_CISTATUS_IRQ_SRC_FRMEND) &&
	    test_bit(ST_FLITE_RUN, &fimc->state) &&
	    !list_empty(&fimc->active_buf_q)) अणु
		vbuf = fimc_lite_active_queue_pop(fimc);
		vbuf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		vbuf->vb.sequence = fimc->frame_count++;
		flite_hw_mask_dma_buffer(fimc, vbuf->index);
		vb2_buffer_करोne(&vbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	अगर (test_bit(ST_FLITE_CONFIG, &fimc->state))
		fimc_lite_config_update(fimc);

	अगर (list_empty(&fimc->pending_buf_q)) अणु
		flite_hw_capture_stop(fimc);
		clear_bit(ST_FLITE_STREAM, &fimc->state);
	पूर्ण
करोne:
	set_bit(ST_FLITE_RUN, &fimc->state);
	spin_unlock_irqrestore(&fimc->slock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा fimc_lite *fimc = q->drv_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&fimc->slock, flags);

	fimc->buf_index = 0;
	fimc->frame_count = 0;

	spin_unlock_irqrestore(&fimc->slock, flags);

	ret = fimc_lite_hw_init(fimc, false);
	अगर (ret) अणु
		fimc_lite_reinit(fimc, false);
		वापस ret;
	पूर्ण

	set_bit(ST_FLITE_PENDING, &fimc->state);

	अगर (!list_empty(&fimc->active_buf_q) &&
	    !test_and_set_bit(ST_FLITE_STREAM, &fimc->state)) अणु
		flite_hw_capture_start(fimc);

		अगर (!test_and_set_bit(ST_SENSOR_STREAM, &fimc->state))
			fimc_pipeline_call(&fimc->ve, set_stream, 1);
	पूर्ण
	अगर (debug > 0)
		flite_hw_dump_regs(fimc, __func__);

	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा fimc_lite *fimc = q->drv_priv;

	अगर (!fimc_lite_active(fimc))
		वापस;

	fimc_lite_stop_capture(fimc, false);
पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा fimc_lite *fimc = vq->drv_priv;
	काष्ठा flite_frame *frame = &fimc->out_frame;
	स्थिर काष्ठा fimc_fmt *fmt = frame->fmt;
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

	क्रम (i = 0; i < fmt->memplanes; i++)
		sizes[i] = (wh * fmt->depth[i]) / 8;

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा fimc_lite *fimc = vq->drv_priv;
	पूर्णांक i;

	अगर (fimc->out_frame.fmt == शून्य)
		वापस -EINVAL;

	क्रम (i = 0; i < fimc->out_frame.fmt->memplanes; i++) अणु
		अचिन्हित दीर्घ size = fimc->payload[i];

		अगर (vb2_plane_size(vb, i) < size) अणु
			v4l2_err(&fimc->ve.vdev,
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
	काष्ठा flite_buffer *buf
		= container_of(vbuf, काष्ठा flite_buffer, vb);
	काष्ठा fimc_lite *fimc = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fimc->slock, flags);
	buf->addr = vb2_dma_contig_plane_dma_addr(vb, 0);

	buf->index = fimc->buf_index++;
	अगर (fimc->buf_index >= fimc->reqbufs_count)
		fimc->buf_index = 0;

	अगर (!test_bit(ST_FLITE_SUSPENDED, &fimc->state) &&
	    !test_bit(ST_FLITE_STREAM, &fimc->state) &&
	    list_empty(&fimc->active_buf_q)) अणु
		flite_hw_set_dma_buffer(fimc, buf);
		fimc_lite_active_queue_add(fimc, buf);
	पूर्ण अन्यथा अणु
		fimc_lite_pending_queue_add(fimc, buf);
	पूर्ण

	अगर (vb2_is_streaming(&fimc->vb_queue) &&
	    !list_empty(&fimc->pending_buf_q) &&
	    !test_and_set_bit(ST_FLITE_STREAM, &fimc->state)) अणु
		flite_hw_capture_start(fimc);
		spin_unlock_irqrestore(&fimc->slock, flags);

		अगर (!test_and_set_bit(ST_SENSOR_STREAM, &fimc->state))
			fimc_pipeline_call(&fimc->ve, set_stream, 1);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&fimc->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops fimc_lite_qops = अणु
	.queue_setup	 = queue_setup,
	.buf_prepare	 = buffer_prepare,
	.buf_queue	 = buffer_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming	 = stop_streaming,
पूर्ण;

अटल व्योम fimc_lite_clear_event_counters(काष्ठा fimc_lite *fimc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fimc->slock, flags);
	स_रखो(&fimc->events, 0, माप(fimc->events));
	spin_unlock_irqrestore(&fimc->slock, flags);
पूर्ण

अटल पूर्णांक fimc_lite_खोलो(काष्ठा file *file)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा media_entity *me = &fimc->ve.vdev.entity;
	पूर्णांक ret;

	mutex_lock(&fimc->lock);
	अगर (atomic_पढ़ो(&fimc->out_path) != FIMC_IO_DMA) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	set_bit(ST_FLITE_IN_USE, &fimc->state);
	ret = pm_runसमय_get_sync(&fimc->pdev->dev);
	अगर (ret < 0)
		जाओ err_pm;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ err_pm;

	अगर (!v4l2_fh_is_singular_file(file) ||
	    atomic_पढ़ो(&fimc->out_path) != FIMC_IO_DMA)
		जाओ unlock;

	mutex_lock(&me->graph_obj.mdev->graph_mutex);

	ret = fimc_pipeline_call(&fimc->ve, खोलो, me, true);

	/* Mark video pipeline ending at this video node as in use. */
	अगर (ret == 0)
		me->use_count++;

	mutex_unlock(&me->graph_obj.mdev->graph_mutex);

	अगर (!ret) अणु
		fimc_lite_clear_event_counters(fimc);
		जाओ unlock;
	पूर्ण

	v4l2_fh_release(file);
err_pm:
	pm_runसमय_put_sync(&fimc->pdev->dev);
	clear_bit(ST_FLITE_IN_USE, &fimc->state);
unlock:
	mutex_unlock(&fimc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_lite_release(काष्ठा file *file)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा media_entity *entity = &fimc->ve.vdev.entity;

	mutex_lock(&fimc->lock);

	अगर (v4l2_fh_is_singular_file(file) &&
	    atomic_पढ़ो(&fimc->out_path) == FIMC_IO_DMA) अणु
		अगर (fimc->streaming) अणु
			media_pipeline_stop(entity);
			fimc->streaming = false;
		पूर्ण
		fimc_lite_stop_capture(fimc, false);
		fimc_pipeline_call(&fimc->ve, बंद);
		clear_bit(ST_FLITE_IN_USE, &fimc->state);

		mutex_lock(&entity->graph_obj.mdev->graph_mutex);
		entity->use_count--;
		mutex_unlock(&entity->graph_obj.mdev->graph_mutex);
	पूर्ण

	_vb2_fop_release(file, शून्य);
	pm_runसमय_put(&fimc->pdev->dev);
	clear_bit(ST_FLITE_SUSPENDED, &fimc->state);

	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations fimc_lite_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fimc_lite_खोलो,
	.release	= fimc_lite_release,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/*
 * Format and crop negotiation helpers
 */

अटल स्थिर काष्ठा fimc_fmt *fimc_lite_subdev_try_fmt(काष्ठा fimc_lite *fimc,
					काष्ठा v4l2_subdev_pad_config *cfg,
					काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा flite_drvdata *dd = fimc->dd;
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	स्थिर काष्ठा fimc_fmt *fmt = शून्य;

	अगर (क्रमmat->pad == FLITE_SD_PAD_SINK) अणु
		v4l_bound_align_image(&mf->width, 8, dd->max_width,
				ffs(dd->out_width_align) - 1,
				&mf->height, 0, dd->max_height, 0, 0);

		fmt = fimc_lite_find_क्रमmat(शून्य, &mf->code, 0, 0);
		अगर (WARN_ON(!fmt))
			वापस शून्य;

		mf->colorspace = fmt->colorspace;
		mf->code = fmt->mbus_code;
	पूर्ण अन्यथा अणु
		काष्ठा flite_frame *sink = &fimc->inp_frame;
		काष्ठा v4l2_mbus_framefmt *sink_fmt;
		काष्ठा v4l2_rect *rect;

		अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
			sink_fmt = v4l2_subdev_get_try_क्रमmat(&fimc->subdev, cfg,
						FLITE_SD_PAD_SINK);

			mf->code = sink_fmt->code;
			mf->colorspace = sink_fmt->colorspace;

			rect = v4l2_subdev_get_try_crop(&fimc->subdev, cfg,
						FLITE_SD_PAD_SINK);
		पूर्ण अन्यथा अणु
			mf->code = sink->fmt->mbus_code;
			mf->colorspace = sink->fmt->colorspace;
			rect = &sink->rect;
		पूर्ण

		/* Allow changing क्रमmat only on sink pad */
		mf->width = rect->width;
		mf->height = rect->height;
	पूर्ण

	mf->field = V4L2_FIELD_NONE;

	v4l2_dbg(1, debug, &fimc->subdev, "code: %#x (%d), %dx%d\n",
		 mf->code, mf->colorspace, mf->width, mf->height);

	वापस fmt;
पूर्ण

अटल व्योम fimc_lite_try_crop(काष्ठा fimc_lite *fimc, काष्ठा v4l2_rect *r)
अणु
	काष्ठा flite_frame *frame = &fimc->inp_frame;

	v4l_bound_align_image(&r->width, 0, frame->f_width, 0,
			      &r->height, 0, frame->f_height, 0, 0);

	/* Adjust left/top अगर cropping rectangle got out of bounds */
	r->left = clamp_t(u32, r->left, 0, frame->f_width - r->width);
	r->left = round_करोwn(r->left, fimc->dd->win_hor_offs_align);
	r->top  = clamp_t(u32, r->top, 0, frame->f_height - r->height);

	v4l2_dbg(1, debug, &fimc->subdev, "(%d,%d)/%dx%d, sink fmt: %dx%d\n",
		 r->left, r->top, r->width, r->height,
		 frame->f_width, frame->f_height);
पूर्ण

अटल व्योम fimc_lite_try_compose(काष्ठा fimc_lite *fimc, काष्ठा v4l2_rect *r)
अणु
	काष्ठा flite_frame *frame = &fimc->out_frame;
	काष्ठा v4l2_rect *crop_rect = &fimc->inp_frame.rect;

	/* Scaling is not supported so we enक्रमce compose rectangle size
	   same as size of the sink crop rectangle. */
	r->width = crop_rect->width;
	r->height = crop_rect->height;

	/* Adjust left/top अगर the composing rectangle got out of bounds */
	r->left = clamp_t(u32, r->left, 0, frame->f_width - r->width);
	r->left = round_करोwn(r->left, fimc->dd->out_hor_offs_align);
	r->top  = clamp_t(u32, r->top, 0, fimc->out_frame.f_height - r->height);

	v4l2_dbg(1, debug, &fimc->subdev, "(%d,%d)/%dx%d, source fmt: %dx%d\n",
		 r->left, r->top, r->width, r->height,
		 frame->f_width, frame->f_height);
पूर्ण

/*
 * Video node ioctl operations
 */
अटल पूर्णांक fimc_lite_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);

	strscpy(cap->driver, FIMC_LITE_DRV_NAME, माप(cap->driver));
	strscpy(cap->card, FIMC_LITE_DRV_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
					dev_name(&fimc->pdev->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा fimc_fmt *fmt;

	अगर (f->index >= ARRAY_SIZE(fimc_lite_क्रमmats))
		वापस -EINVAL;

	fmt = &fimc_lite_क्रमmats[f->index];
	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_g_fmt_mplane(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *plane_fmt = &pixm->plane_fmt[0];
	काष्ठा flite_frame *frame = &fimc->out_frame;
	स्थिर काष्ठा fimc_fmt *fmt = frame->fmt;

	plane_fmt->bytesperline = (frame->f_width * fmt->depth[0]) / 8;
	plane_fmt->sizeimage = plane_fmt->bytesperline * frame->f_height;

	pixm->num_planes = fmt->memplanes;
	pixm->pixelक्रमmat = fmt->fourcc;
	pixm->width = frame->f_width;
	pixm->height = frame->f_height;
	pixm->field = V4L2_FIELD_NONE;
	pixm->colorspace = fmt->colorspace;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_try_fmt(काष्ठा fimc_lite *fimc,
			     काष्ठा v4l2_pix_क्रमmat_mplane *pixm,
			     स्थिर काष्ठा fimc_fmt **ffmt)
अणु
	u32 bpl = pixm->plane_fmt[0].bytesperline;
	काष्ठा flite_drvdata *dd = fimc->dd;
	स्थिर काष्ठा fimc_fmt *inp_fmt = fimc->inp_frame.fmt;
	स्थिर काष्ठा fimc_fmt *fmt;

	अगर (WARN_ON(inp_fmt == शून्य))
		वापस -EINVAL;
	/*
	 * We allow some flexibility only क्रम YUV क्रमmats. In हाल of raw
	 * raw Bayer the FIMC-LITE's output क्रमmat must match its camera
	 * पूर्णांकerface input क्रमmat.
	 */
	अगर (inp_fmt->flags & FMT_FLAGS_YUV)
		fmt = fimc_lite_find_क्रमmat(&pixm->pixelक्रमmat, शून्य,
						inp_fmt->flags, 0);
	अन्यथा
		fmt = inp_fmt;

	अगर (WARN_ON(fmt == शून्य))
		वापस -EINVAL;
	अगर (ffmt)
		*ffmt = fmt;
	v4l_bound_align_image(&pixm->width, 8, dd->max_width,
			      ffs(dd->out_width_align) - 1,
			      &pixm->height, 0, dd->max_height, 0, 0);

	अगर ((bpl == 0 || ((bpl * 8) / fmt->depth[0]) < pixm->width))
		pixm->plane_fmt[0].bytesperline = (pixm->width *
						   fmt->depth[0]) / 8;

	अगर (pixm->plane_fmt[0].sizeimage == 0)
		pixm->plane_fmt[0].sizeimage = (pixm->width * pixm->height *
						fmt->depth[0]) / 8;
	pixm->num_planes = fmt->memplanes;
	pixm->pixelक्रमmat = fmt->fourcc;
	pixm->colorspace = fmt->colorspace;
	pixm->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_try_fmt_mplane(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	वापस fimc_lite_try_fmt(fimc, &f->fmt.pix_mp, शून्य);
पूर्ण

अटल पूर्णांक fimc_lite_s_fmt_mplane(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &f->fmt.pix_mp;
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा flite_frame *frame = &fimc->out_frame;
	स्थिर काष्ठा fimc_fmt *fmt = शून्य;
	पूर्णांक ret;

	अगर (vb2_is_busy(&fimc->vb_queue))
		वापस -EBUSY;

	ret = fimc_lite_try_fmt(fimc, &f->fmt.pix_mp, &fmt);
	अगर (ret < 0)
		वापस ret;

	frame->fmt = fmt;
	fimc->payload[0] = max((pixm->width * pixm->height * fmt->depth[0]) / 8,
			       pixm->plane_fmt[0].sizeimage);
	frame->f_width = pixm->width;
	frame->f_height = pixm->height;

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_pipeline_validate(काष्ठा fimc_lite *fimc)
अणु
	काष्ठा v4l2_subdev *sd = &fimc->subdev;
	काष्ठा v4l2_subdev_क्रमmat sink_fmt, src_fmt;
	काष्ठा media_pad *pad;
	पूर्णांक ret;

	जबतक (1) अणु
		/* Retrieve क्रमmat at the sink pad */
		pad = &sd->entity.pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;
		/* Don't call FIMC subdev operation to aव्योम nested locking */
		अगर (sd == &fimc->subdev) अणु
			काष्ठा flite_frame *ff = &fimc->out_frame;
			sink_fmt.क्रमmat.width = ff->f_width;
			sink_fmt.क्रमmat.height = ff->f_height;
			sink_fmt.क्रमmat.code = fimc->inp_frame.fmt->mbus_code;
		पूर्ण अन्यथा अणु
			sink_fmt.pad = pad->index;
			sink_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
			ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य,
					       &sink_fmt);
			अगर (ret < 0 && ret != -ENOIOCTLCMD)
				वापस -EPIPE;
		पूर्ण
		/* Retrieve क्रमmat at the source pad */
		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		sd = media_entity_to_v4l2_subdev(pad->entity);
		src_fmt.pad = pad->index;
		src_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &src_fmt);
		अगर (ret < 0 && ret != -ENOIOCTLCMD)
			वापस -EPIPE;

		अगर (src_fmt.क्रमmat.width != sink_fmt.क्रमmat.width ||
		    src_fmt.क्रमmat.height != sink_fmt.क्रमmat.height ||
		    src_fmt.क्रमmat.code != sink_fmt.क्रमmat.code)
			वापस -EPIPE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_streamon(काष्ठा file *file, व्योम *priv,
			      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा media_entity *entity = &fimc->ve.vdev.entity;
	पूर्णांक ret;

	अगर (fimc_lite_active(fimc))
		वापस -EBUSY;

	ret = media_pipeline_start(entity, &fimc->ve.pipe->mp);
	अगर (ret < 0)
		वापस ret;

	ret = fimc_pipeline_validate(fimc);
	अगर (ret < 0)
		जाओ err_p_stop;

	fimc->sensor = fimc_find_remote_sensor(&fimc->subdev.entity);

	ret = vb2_ioctl_streamon(file, priv, type);
	अगर (!ret) अणु
		fimc->streaming = true;
		वापस ret;
	पूर्ण

err_p_stop:
	media_pipeline_stop(entity);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_streamoff(काष्ठा file *file, व्योम *priv,
			       क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	पूर्णांक ret;

	ret = vb2_ioctl_streamoff(file, priv, type);
	अगर (ret < 0)
		वापस ret;

	media_pipeline_stop(&fimc->ve.vdev.entity);
	fimc->streaming = false;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_reqbufs(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	पूर्णांक ret;

	reqbufs->count = max_t(u32, FLITE_REQ_BUFS_MIN, reqbufs->count);
	ret = vb2_ioctl_reqbufs(file, priv, reqbufs);
	अगर (!ret)
		fimc->reqbufs_count = reqbufs->count;

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_lite_g_selection(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_selection *sel)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा flite_frame *f = &fimc->out_frame;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = f->f_width;
		sel->r.height = f->f_height;
		वापस 0;

	हाल V4L2_SEL_TGT_COMPOSE:
		sel->r = f->rect;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fimc_lite_s_selection(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_selection *sel)
अणु
	काष्ठा fimc_lite *fimc = video_drvdata(file);
	काष्ठा flite_frame *f = &fimc->out_frame;
	काष्ठा v4l2_rect rect = sel->r;
	अचिन्हित दीर्घ flags;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    sel->target != V4L2_SEL_TGT_COMPOSE)
		वापस -EINVAL;

	fimc_lite_try_compose(fimc, &rect);

	अगर ((sel->flags & V4L2_SEL_FLAG_LE) &&
	    !v4l2_rect_enबंदd(&rect, &sel->r))
		वापस -दुस्फल;

	अगर ((sel->flags & V4L2_SEL_FLAG_GE) &&
	    !v4l2_rect_enबंदd(&sel->r, &rect))
		वापस -दुस्फल;

	sel->r = rect;
	spin_lock_irqsave(&fimc->slock, flags);
	f->rect = rect;
	set_bit(ST_FLITE_CONFIG, &fimc->state);
	spin_unlock_irqrestore(&fimc->slock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops fimc_lite_ioctl_ops = अणु
	.vidioc_querycap		= fimc_lite_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= fimc_lite_क्रमागत_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= fimc_lite_try_fmt_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= fimc_lite_s_fmt_mplane,
	.vidioc_g_fmt_vid_cap_mplane	= fimc_lite_g_fmt_mplane,
	.vidioc_g_selection		= fimc_lite_g_selection,
	.vidioc_s_selection		= fimc_lite_s_selection,
	.vidioc_reqbufs			= fimc_lite_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_streamon		= fimc_lite_streamon,
	.vidioc_streamoff		= fimc_lite_streamoff,
पूर्ण;

/* Capture subdev media entity operations */
अटल पूर्णांक fimc_lite_link_setup(काष्ठा media_entity *entity,
				स्थिर काष्ठा media_pad *local,
				स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (WARN_ON(fimc == शून्य))
		वापस 0;

	v4l2_dbg(1, debug, sd, "%s: %s --> %s, flags: 0x%x. source_id: 0x%x\n",
		 __func__, remote->entity->name, local->entity->name,
		 flags, fimc->source_subdev_grp_id);

	चयन (local->index) अणु
	हाल FLITE_SD_PAD_SINK:
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (fimc->source_subdev_grp_id == 0)
				fimc->source_subdev_grp_id = sd->grp_id;
			अन्यथा
				ret = -EBUSY;
		पूर्ण अन्यथा अणु
			fimc->source_subdev_grp_id = 0;
			fimc->sensor = शून्य;
		पूर्ण
		अवरोध;

	हाल FLITE_SD_PAD_SOURCE_DMA:
		अगर (!(flags & MEDIA_LNK_FL_ENABLED))
			atomic_set(&fimc->out_path, FIMC_IO_NONE);
		अन्यथा
			atomic_set(&fimc->out_path, FIMC_IO_DMA);
		अवरोध;

	हाल FLITE_SD_PAD_SOURCE_ISP:
		अगर (!(flags & MEDIA_LNK_FL_ENABLED))
			atomic_set(&fimc->out_path, FIMC_IO_NONE);
		अन्यथा
			atomic_set(&fimc->out_path, FIMC_IO_ISP);
		अवरोध;

	शेष:
		v4l2_err(sd, "Invalid pad index\n");
		ret = -EINVAL;
	पूर्ण
	mb();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations fimc_lite_subdev_media_ops = अणु
	.link_setup = fimc_lite_link_setup,
पूर्ण;

अटल पूर्णांक fimc_lite_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
					   काष्ठा v4l2_subdev_pad_config *cfg,
					   काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	स्थिर काष्ठा fimc_fmt *fmt;

	fmt = fimc_lite_find_क्रमmat(शून्य, शून्य, 0, code->index);
	अगर (!fmt)
		वापस -EINVAL;
	code->code = fmt->mbus_code;
	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *__fimc_lite_subdev_get_try_fmt(
		काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad)
अणु
	अगर (pad != FLITE_SD_PAD_SINK)
		pad = FLITE_SD_PAD_SOURCE_DMA;

	वापस v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);
पूर्ण

अटल पूर्णांक fimc_lite_subdev_get_fmt(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा flite_frame *f = &fimc->inp_frame;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = __fimc_lite_subdev_get_try_fmt(sd, cfg, fmt->pad);
		fmt->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mutex_lock(&fimc->lock);
	mf->colorspace = f->fmt->colorspace;
	mf->code = f->fmt->mbus_code;

	अगर (fmt->pad == FLITE_SD_PAD_SINK) अणु
		/* full camera input frame size */
		mf->width = f->f_width;
		mf->height = f->f_height;
	पूर्ण अन्यथा अणु
		/* crop size */
		mf->width = f->rect.width;
		mf->height = f->rect.height;
	पूर्ण
	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_subdev_set_fmt(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा flite_frame *sink = &fimc->inp_frame;
	काष्ठा flite_frame *source = &fimc->out_frame;
	स्थिर काष्ठा fimc_fmt *ffmt;

	v4l2_dbg(1, debug, sd, "pad%d: code: 0x%x, %dx%d\n",
		 fmt->pad, mf->code, mf->width, mf->height);

	mutex_lock(&fimc->lock);

	अगर ((atomic_पढ़ो(&fimc->out_path) == FIMC_IO_ISP &&
	    sd->entity.stream_count > 0) ||
	    (atomic_पढ़ो(&fimc->out_path) == FIMC_IO_DMA &&
	    vb2_is_busy(&fimc->vb_queue))) अणु
		mutex_unlock(&fimc->lock);
		वापस -EBUSY;
	पूर्ण

	ffmt = fimc_lite_subdev_try_fmt(fimc, cfg, fmt);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *src_fmt;

		mf = __fimc_lite_subdev_get_try_fmt(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;

		अगर (fmt->pad == FLITE_SD_PAD_SINK) अणु
			अचिन्हित पूर्णांक pad = FLITE_SD_PAD_SOURCE_DMA;
			src_fmt = __fimc_lite_subdev_get_try_fmt(sd, cfg, pad);
			*src_fmt = *mf;
		पूर्ण

		mutex_unlock(&fimc->lock);
		वापस 0;
	पूर्ण

	अगर (fmt->pad == FLITE_SD_PAD_SINK) अणु
		sink->f_width = mf->width;
		sink->f_height = mf->height;
		sink->fmt = ffmt;
		/* Set sink crop rectangle */
		sink->rect.width = mf->width;
		sink->rect.height = mf->height;
		sink->rect.left = 0;
		sink->rect.top = 0;
		/* Reset source क्रमmat and crop rectangle */
		source->rect = sink->rect;
		source->f_width = mf->width;
		source->f_height = mf->height;
	पूर्ण

	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_subdev_get_selection(काष्ठा v4l2_subdev *sd,
					  काष्ठा v4l2_subdev_pad_config *cfg,
					  काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	काष्ठा flite_frame *f = &fimc->inp_frame;

	अगर ((sel->target != V4L2_SEL_TGT_CROP &&
	     sel->target != V4L2_SEL_TGT_CROP_BOUNDS) ||
	     sel->pad != FLITE_SD_PAD_SINK)
		वापस -EINVAL;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		sel->r = *v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		वापस 0;
	पूर्ण

	mutex_lock(&fimc->lock);
	अगर (sel->target == V4L2_SEL_TGT_CROP) अणु
		sel->r = f->rect;
	पूर्ण अन्यथा अणु
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = f->f_width;
		sel->r.height = f->f_height;
	पूर्ण
	mutex_unlock(&fimc->lock);

	v4l2_dbg(1, debug, sd, "%s: (%d,%d) %dx%d, f_w: %d, f_h: %d\n",
		 __func__, f->rect.left, f->rect.top, f->rect.width,
		 f->rect.height, f->f_width, f->f_height);

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_subdev_set_selection(काष्ठा v4l2_subdev *sd,
					  काष्ठा v4l2_subdev_pad_config *cfg,
					  काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	काष्ठा flite_frame *f = &fimc->inp_frame;
	पूर्णांक ret = 0;

	अगर (sel->target != V4L2_SEL_TGT_CROP || sel->pad != FLITE_SD_PAD_SINK)
		वापस -EINVAL;

	mutex_lock(&fimc->lock);
	fimc_lite_try_crop(fimc, &sel->r);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_crop(sd, cfg, sel->pad) = sel->r;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&fimc->slock, flags);
		f->rect = sel->r;
		/* Same crop rectangle on the source pad */
		fimc->out_frame.rect = sel->r;
		set_bit(ST_FLITE_CONFIG, &fimc->state);
		spin_unlock_irqrestore(&fimc->slock, flags);
	पूर्ण
	mutex_unlock(&fimc->lock);

	v4l2_dbg(1, debug, sd, "%s: (%d,%d) %dx%d, f_w: %d, f_h: %d\n",
		 __func__, f->rect.left, f->rect.top, f->rect.width,
		 f->rect.height, f->f_width, f->f_height);

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_lite_subdev_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Find sensor subdev linked to FIMC-LITE directly or through
	 * MIPI-CSIS. This is required क्रम configuration where FIMC-LITE
	 * is used as a subdev only and feeds data पूर्णांकernally to FIMC-IS.
	 * The pipeline links are रक्षित through entity.stream_count
	 * so there is no need to take the media graph mutex here.
	 */
	fimc->sensor = fimc_find_remote_sensor(&sd->entity);

	अगर (atomic_पढ़ो(&fimc->out_path) != FIMC_IO_ISP)
		वापस -ENOIOCTLCMD;

	mutex_lock(&fimc->lock);
	अगर (on) अणु
		flite_hw_reset(fimc);
		ret = fimc_lite_hw_init(fimc, true);
		अगर (!ret) अणु
			spin_lock_irqsave(&fimc->slock, flags);
			flite_hw_capture_start(fimc);
			spin_unlock_irqrestore(&fimc->slock, flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(ST_FLITE_OFF, &fimc->state);

		spin_lock_irqsave(&fimc->slock, flags);
		flite_hw_capture_stop(fimc);
		spin_unlock_irqrestore(&fimc->slock, flags);

		ret = रुको_event_समयout(fimc->irq_queue,
				!test_bit(ST_FLITE_OFF, &fimc->state),
				msecs_to_jअगरfies(200));
		अगर (ret == 0)
			v4l2_err(sd, "s_stream(0) timeout\n");
		clear_bit(ST_FLITE_RUN, &fimc->state);
	पूर्ण

	mutex_unlock(&fimc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_lite_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);

	flite_hw_dump_regs(fimc, __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_subdev_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);
	काष्ठा vb2_queue *q = &fimc->vb_queue;
	काष्ठा video_device *vfd = &fimc->ve.vdev;
	पूर्णांक ret;

	स_रखो(vfd, 0, माप(*vfd));
	atomic_set(&fimc->out_path, FIMC_IO_DMA);

	snम_लिखो(vfd->name, माप(vfd->name), "fimc-lite.%d.capture",
		 fimc->index);

	vfd->fops = &fimc_lite_fops;
	vfd->ioctl_ops = &fimc_lite_ioctl_ops;
	vfd->v4l2_dev = sd->v4l2_dev;
	vfd->minor = -1;
	vfd->release = video_device_release_empty;
	vfd->queue = q;
	vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING;
	fimc->reqbufs_count = 0;

	INIT_LIST_HEAD(&fimc->pending_buf_q);
	INIT_LIST_HEAD(&fimc->active_buf_q);

	स_रखो(q, 0, माप(*q));
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_MMAP | VB2_USERPTR;
	q->ops = &fimc_lite_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा flite_buffer);
	q->drv_priv = fimc;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &fimc->lock;
	q->dev = &fimc->pdev->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0)
		वापस ret;

	fimc->vd_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &fimc->vd_pad);
	अगर (ret < 0)
		वापस ret;

	video_set_drvdata(vfd, fimc);
	fimc->ve.pipe = v4l2_get_subdev_hostdata(sd);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		media_entity_cleanup(&vfd->entity);
		fimc->ve.pipe = शून्य;
		वापस ret;
	पूर्ण

	v4l2_info(sd->v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	वापस 0;
पूर्ण

अटल व्योम fimc_lite_subdev_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_lite *fimc = v4l2_get_subdevdata(sd);

	अगर (fimc == शून्य)
		वापस;

	mutex_lock(&fimc->lock);

	अगर (video_is_रेजिस्टरed(&fimc->ve.vdev)) अणु
		video_unरेजिस्टर_device(&fimc->ve.vdev);
		media_entity_cleanup(&fimc->ve.vdev.entity);
		fimc->ve.pipe = शून्य;
	पूर्ण

	mutex_unlock(&fimc->lock);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops fimc_lite_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = fimc_lite_subdev_रेजिस्टरed,
	.unरेजिस्टरed = fimc_lite_subdev_unरेजिस्टरed,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops fimc_lite_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = fimc_lite_subdev_क्रमागत_mbus_code,
	.get_selection = fimc_lite_subdev_get_selection,
	.set_selection = fimc_lite_subdev_set_selection,
	.get_fmt = fimc_lite_subdev_get_fmt,
	.set_fmt = fimc_lite_subdev_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops fimc_lite_subdev_video_ops = अणु
	.s_stream = fimc_lite_subdev_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops fimc_lite_core_ops = अणु
	.log_status = fimc_lite_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops fimc_lite_subdev_ops = अणु
	.core = &fimc_lite_core_ops,
	.video = &fimc_lite_subdev_video_ops,
	.pad = &fimc_lite_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक fimc_lite_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fimc_lite *fimc = container_of(ctrl->handler, काष्ठा fimc_lite,
					      ctrl_handler);
	set_bit(ST_FLITE_CONFIG, &fimc->state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fimc_lite_ctrl_ops = अणु
	.s_ctrl	= fimc_lite_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config fimc_lite_ctrl = अणु
	.ops	= &fimc_lite_ctrl_ops,
	.id	= V4L2_CTRL_CLASS_USER | 0x1001,
	.type	= V4L2_CTRL_TYPE_BOOLEAN,
	.name	= "Test Pattern 640x480",
	.step	= 1,
पूर्ण;

अटल व्योम fimc_lite_set_शेष_config(काष्ठा fimc_lite *fimc)
अणु
	काष्ठा flite_frame *sink = &fimc->inp_frame;
	काष्ठा flite_frame *source = &fimc->out_frame;

	sink->fmt = &fimc_lite_क्रमmats[0];
	sink->f_width = FLITE_DEFAULT_WIDTH;
	sink->f_height = FLITE_DEFAULT_HEIGHT;

	sink->rect.width = FLITE_DEFAULT_WIDTH;
	sink->rect.height = FLITE_DEFAULT_HEIGHT;
	sink->rect.left = 0;
	sink->rect.top = 0;

	*source = *sink;
पूर्ण

अटल पूर्णांक fimc_lite_create_capture_subdev(काष्ठा fimc_lite *fimc)
अणु
	काष्ठा v4l2_ctrl_handler *handler = &fimc->ctrl_handler;
	काष्ठा v4l2_subdev *sd = &fimc->subdev;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &fimc_lite_subdev_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snम_लिखो(sd->name, माप(sd->name), "FIMC-LITE.%d", fimc->index);

	fimc->subdev_pads[FLITE_SD_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	fimc->subdev_pads[FLITE_SD_PAD_SOURCE_DMA].flags = MEDIA_PAD_FL_SOURCE;
	fimc->subdev_pads[FLITE_SD_PAD_SOURCE_ISP].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sd->entity, FLITE_SD_PADS_NUM,
				fimc->subdev_pads);
	अगर (ret)
		वापस ret;

	v4l2_ctrl_handler_init(handler, 1);
	fimc->test_pattern = v4l2_ctrl_new_custom(handler, &fimc_lite_ctrl,
						  शून्य);
	अगर (handler->error) अणु
		media_entity_cleanup(&sd->entity);
		वापस handler->error;
	पूर्ण

	sd->ctrl_handler = handler;
	sd->पूर्णांकernal_ops = &fimc_lite_subdev_पूर्णांकernal_ops;
	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;
	sd->entity.ops = &fimc_lite_subdev_media_ops;
	sd->owner = THIS_MODULE;
	v4l2_set_subdevdata(sd, fimc);

	वापस 0;
पूर्ण

अटल व्योम fimc_lite_unरेजिस्टर_capture_subdev(काष्ठा fimc_lite *fimc)
अणु
	काष्ठा v4l2_subdev *sd = &fimc->subdev;

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(&fimc->ctrl_handler);
	v4l2_set_subdevdata(sd, शून्य);
पूर्ण

अटल व्योम fimc_lite_clk_put(काष्ठा fimc_lite *fimc)
अणु
	अगर (IS_ERR(fimc->घड़ी))
		वापस;

	clk_put(fimc->घड़ी);
	fimc->घड़ी = ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक fimc_lite_clk_get(काष्ठा fimc_lite *fimc)
अणु
	fimc->घड़ी = clk_get(&fimc->pdev->dev, FLITE_CLK_NAME);
	वापस PTR_ERR_OR_ZERO(fimc->घड़ी);
पूर्ण

अटल स्थिर काष्ठा of_device_id flite_of_match[];

अटल पूर्णांक fimc_lite_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा flite_drvdata *drv_data = शून्य;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा fimc_lite *fimc;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस -ENODEV;

	fimc = devm_kzalloc(dev, माप(*fimc), GFP_KERNEL);
	अगर (!fimc)
		वापस -ENOMEM;

	of_id = of_match_node(flite_of_match, dev->of_node);
	अगर (of_id)
		drv_data = (काष्ठा flite_drvdata *)of_id->data;
	fimc->index = of_alias_get_id(dev->of_node, "fimc-lite");

	अगर (!drv_data || fimc->index >= drv_data->num_instances ||
						fimc->index < 0) अणु
		dev_err(dev, "Wrong %pOF node alias\n", dev->of_node);
		वापस -EINVAL;
	पूर्ण

	fimc->dd = drv_data;
	fimc->pdev = pdev;

	init_रुकोqueue_head(&fimc->irq_queue);
	spin_lock_init(&fimc->slock);
	mutex_init(&fimc->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fimc->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(fimc->regs))
		वापस PTR_ERR(fimc->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "Failed to get IRQ resource\n");
		वापस -ENXIO;
	पूर्ण

	ret = fimc_lite_clk_get(fimc);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(dev, res->start, flite_irq_handler,
			       0, dev_name(dev), fimc);
	अगर (ret) अणु
		dev_err(dev, "Failed to install irq (%d)\n", ret);
		जाओ err_clk_put;
	पूर्ण

	/* The video node will be created within the subdev's रेजिस्टरed() op */
	ret = fimc_lite_create_capture_subdev(fimc);
	अगर (ret)
		जाओ err_clk_put;

	platक्रमm_set_drvdata(pdev, fimc);
	pm_runसमय_enable(dev);

	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = clk_prepare_enable(fimc->घड़ी);
		अगर (ret < 0)
			जाओ err_sd;
	पूर्ण

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	fimc_lite_set_शेष_config(fimc);

	dev_dbg(dev, "FIMC-LITE.%d registered successfully\n",
		fimc->index);
	वापस 0;

err_sd:
	fimc_lite_unरेजिस्टर_capture_subdev(fimc);
err_clk_put:
	fimc_lite_clk_put(fimc);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fimc_lite_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_lite *fimc = dev_get_drvdata(dev);

	clk_prepare_enable(fimc->घड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_lite *fimc = dev_get_drvdata(dev);

	clk_disable_unprepare(fimc->घड़ी);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fimc_lite_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_lite *fimc = dev_get_drvdata(dev);
	काष्ठा flite_buffer *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&fimc->slock, flags);
	अगर (!test_and_clear_bit(ST_LPM, &fimc->state) ||
	    !test_bit(ST_FLITE_IN_USE, &fimc->state)) अणु
		spin_unlock_irqrestore(&fimc->slock, flags);
		वापस 0;
	पूर्ण
	flite_hw_reset(fimc);
	spin_unlock_irqrestore(&fimc->slock, flags);

	अगर (!test_and_clear_bit(ST_FLITE_SUSPENDED, &fimc->state))
		वापस 0;

	INIT_LIST_HEAD(&fimc->active_buf_q);
	fimc_pipeline_call(&fimc->ve, खोलो,
			   &fimc->ve.vdev.entity, false);
	fimc_lite_hw_init(fimc, atomic_पढ़ो(&fimc->out_path) == FIMC_IO_ISP);
	clear_bit(ST_FLITE_SUSPENDED, &fimc->state);

	क्रम (i = 0; i < fimc->reqbufs_count; i++) अणु
		अगर (list_empty(&fimc->pending_buf_q))
			अवरोध;
		buf = fimc_lite_pending_queue_pop(fimc);
		buffer_queue(&buf->vb.vb2_buf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_lite_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_lite *fimc = dev_get_drvdata(dev);
	bool suspend = test_bit(ST_FLITE_IN_USE, &fimc->state);
	पूर्णांक ret;

	अगर (test_and_set_bit(ST_LPM, &fimc->state))
		वापस 0;

	ret = fimc_lite_stop_capture(fimc, suspend);
	अगर (ret < 0 || !fimc_lite_active(fimc))
		वापस ret;

	वापस fimc_pipeline_call(&fimc->ve, बंद);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक fimc_lite_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fimc_lite *fimc = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	अगर (!pm_runसमय_enabled(dev))
		clk_disable_unprepare(fimc->घड़ी);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	fimc_lite_unरेजिस्टर_capture_subdev(fimc);
	vb2_dma_contig_clear_max_seg_size(dev);
	fimc_lite_clk_put(fimc);

	dev_info(dev, "Driver unloaded\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fimc_lite_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fimc_lite_suspend, fimc_lite_resume)
	SET_RUNTIME_PM_OPS(fimc_lite_runसमय_suspend, fimc_lite_runसमय_resume,
			   शून्य)
पूर्ण;

/* EXYNOS4412 */
अटल काष्ठा flite_drvdata fimc_lite_drvdata_exynos4 = अणु
	.max_width		= 8192,
	.max_height		= 8192,
	.out_width_align	= 8,
	.win_hor_offs_align	= 2,
	.out_hor_offs_align	= 8,
	.max_dma_bufs		= 1,
	.num_instances		= 2,
पूर्ण;

/* EXYNOS5250 */
अटल काष्ठा flite_drvdata fimc_lite_drvdata_exynos5 = अणु
	.max_width		= 8192,
	.max_height		= 8192,
	.out_width_align	= 8,
	.win_hor_offs_align	= 2,
	.out_hor_offs_align	= 8,
	.max_dma_bufs		= 32,
	.num_instances		= 3,
पूर्ण;

अटल स्थिर काष्ठा of_device_id flite_of_match[] = अणु
	अणु
		.compatible = "samsung,exynos4212-fimc-lite",
		.data = &fimc_lite_drvdata_exynos4,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5250-fimc-lite",
		.data = &fimc_lite_drvdata_exynos5,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, flite_of_match);

अटल काष्ठा platक्रमm_driver fimc_lite_driver = अणु
	.probe		= fimc_lite_probe,
	.हटाओ		= fimc_lite_हटाओ,
	.driver = अणु
		.of_match_table = flite_of_match,
		.name		= FIMC_LITE_DRV_NAME,
		.pm		= &fimc_lite_pm_ops,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(fimc_lite_driver);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" FIMC_LITE_DRV_NAME);
