<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * FIMC-IS ISP video input and video output DMA पूर्णांकerface driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * The hardware handling code derived from a driver written by
 * Younghwan Joo <yhwan.joo@samsung.com>.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#समावेश "common.h"
#समावेश "media-dev.h"
#समावेश "fimc-is.h"
#समावेश "fimc-isp-video.h"
#समावेश "fimc-is-param.h"

अटल पूर्णांक isp_video_capture_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा fimc_isp *isp = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat_mplane *vid_fmt = &isp->video_capture.pixfmt;
	स्थिर काष्ठा fimc_fmt *fmt = isp->video_capture.क्रमmat;
	अचिन्हित पूर्णांक wh, i;

	wh = vid_fmt->width * vid_fmt->height;

	अगर (fmt == शून्य)
		वापस -EINVAL;

	*num_buffers = clamp_t(u32, *num_buffers, FIMC_ISP_REQ_BUFS_MIN,
						FIMC_ISP_REQ_BUFS_MAX);
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

अटल अंतरभूत काष्ठा param_dma_output *__get_isp_dma2(काष्ठा fimc_is *is)
अणु
	वापस &__get_curr_is_config(is)->isp.dma2_output;
पूर्ण

अटल पूर्णांक isp_video_capture_start_streaming(काष्ठा vb2_queue *q,
						अचिन्हित पूर्णांक count)
अणु
	काष्ठा fimc_isp *isp = vb2_get_drv_priv(q);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	काष्ठा param_dma_output *dma = __get_isp_dma2(is);
	काष्ठा fimc_is_video *video = &isp->video_capture;
	पूर्णांक ret;

	अगर (!test_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state) ||
	    test_bit(ST_ISP_VID_CAP_STREAMING, &isp->state))
		वापस 0;


	dma->cmd = DMA_OUTPUT_COMMAND_ENABLE;
	dma->notअगरy_dma_करोne = DMA_OUTPUT_NOTIFY_DMA_DONE_ENABLE;
	dma->buffer_address = is->is_dma_p_region +
				DMA2_OUTPUT_ADDR_ARRAY_OFFS;
	dma->buffer_number = video->reqbufs_count;
	dma->dma_out_mask = video->buf_mask;

	isp_dbg(2, &video->ve.vdev,
		"buf_count: %d, planes: %d, dma addr table: %#x\n",
		video->buf_count, video->क्रमmat->memplanes,
		dma->buffer_address);

	fimc_is_mem_barrier();

	fimc_is_set_param_bit(is, PARAM_ISP_DMA2_OUTPUT);
	__fimc_is_hw_update_param(is, PARAM_ISP_DMA2_OUTPUT);

	ret = fimc_is_itf_s_param(is, false);
	अगर (ret < 0)
		वापस ret;

	ret = fimc_pipeline_call(&video->ve, set_stream, 1);
	अगर (ret < 0)
		वापस ret;

	set_bit(ST_ISP_VID_CAP_STREAMING, &isp->state);
	वापस ret;
पूर्ण

अटल व्योम isp_video_capture_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा fimc_isp *isp = vb2_get_drv_priv(q);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	काष्ठा param_dma_output *dma = __get_isp_dma2(is);
	पूर्णांक ret;

	ret = fimc_pipeline_call(&isp->video_capture.ve, set_stream, 0);
	अगर (ret < 0)
		वापस;

	dma->cmd = DMA_OUTPUT_COMMAND_DISABLE;
	dma->notअगरy_dma_करोne = DMA_OUTPUT_NOTIFY_DMA_DONE_DISABLE;
	dma->buffer_number = 0;
	dma->buffer_address = 0;
	dma->dma_out_mask = 0;

	fimc_is_set_param_bit(is, PARAM_ISP_DMA2_OUTPUT);
	__fimc_is_hw_update_param(is, PARAM_ISP_DMA2_OUTPUT);

	ret = fimc_is_itf_s_param(is, false);
	अगर (ret < 0)
		dev_warn(&is->pdev->dev, "%s: DMA stop failed\n", __func__);

	fimc_is_hw_set_isp_buf_mask(is, 0);

	clear_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state);
	clear_bit(ST_ISP_VID_CAP_STREAMING, &isp->state);

	isp->video_capture.buf_count = 0;
पूर्ण

अटल पूर्णांक isp_video_capture_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा fimc_isp *isp = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा fimc_is_video *video = &isp->video_capture;
	पूर्णांक i;

	अगर (video->क्रमmat == शून्य)
		वापस -EINVAL;

	क्रम (i = 0; i < video->क्रमmat->memplanes; i++) अणु
		अचिन्हित दीर्घ size = video->pixfmt.plane_fmt[i].sizeimage;

		अगर (vb2_plane_size(vb, i) < size) अणु
			v4l2_err(&video->ve.vdev,
				 "User buffer too small (%ld < %ld)\n",
				 vb2_plane_size(vb, i), size);
			वापस -EINVAL;
		पूर्ण
		vb2_set_plane_payload(vb, i, size);
	पूर्ण

	/* Check अगर we get one of the alपढ़ोy known buffers. */
	अगर (test_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state)) अणु
		dma_addr_t dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
		पूर्णांक i;

		क्रम (i = 0; i < video->buf_count; i++)
			अगर (video->buffers[i]->dma_addr[0] == dma_addr)
				वापस 0;
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम isp_video_capture_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा fimc_isp *isp = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा fimc_is_video *video = &isp->video_capture;
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	काष्ठा isp_video_buf *ivb = to_isp_video_buf(vbuf);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (test_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state)) अणु
		spin_lock_irqsave(&is->slock, flags);
		video->buf_mask |= BIT(ivb->index);
		spin_unlock_irqrestore(&is->slock, flags);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक num_planes = video->क्रमmat->memplanes;

		ivb->index = video->buf_count;
		video->buffers[ivb->index] = ivb;

		क्रम (i = 0; i < num_planes; i++) अणु
			पूर्णांक buf_index = ivb->index * num_planes + i;

			ivb->dma_addr[i] = vb2_dma_contig_plane_dma_addr(vb, i);
			is->is_p_region->shared[32 + buf_index] =
							ivb->dma_addr[i];

			isp_dbg(2, &video->ve.vdev,
				"dma_buf %d (%d/%d/%d) addr: %pad\n",
				buf_index, ivb->index, i, vb->index,
				&ivb->dma_addr[i]);
		पूर्ण

		अगर (++video->buf_count < video->reqbufs_count)
			वापस;

		video->buf_mask = (1UL << video->buf_count) - 1;
		set_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state);
	पूर्ण

	अगर (!test_bit(ST_ISP_VID_CAP_STREAMING, &isp->state))
		isp_video_capture_start_streaming(vb->vb2_queue, 0);
पूर्ण

/*
 * FIMC-IS ISP input and output DMA पूर्णांकerface पूर्णांकerrupt handler.
 * Locking: called with is->slock spinlock held.
 */
व्योम fimc_isp_video_irq_handler(काष्ठा fimc_is *is)
अणु
	काष्ठा fimc_is_video *video = &is->isp.video_capture;
	काष्ठा vb2_v4l2_buffer *vbuf;
	पूर्णांक buf_index;

	/* TODO: Ensure the DMA is really stopped in stop_streaming callback */
	अगर (!test_bit(ST_ISP_VID_CAP_STREAMING, &is->isp.state))
		वापस;

	buf_index = (is->i2h_cmd.args[1] - 1) % video->buf_count;
	vbuf = &video->buffers[buf_index]->vb;

	vbuf->vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	video->buf_mask &= ~BIT(buf_index);
	fimc_is_hw_set_isp_buf_mask(is, video->buf_mask);
पूर्ण

अटल स्थिर काष्ठा vb2_ops isp_video_capture_qops = अणु
	.queue_setup	 = isp_video_capture_queue_setup,
	.buf_prepare	 = isp_video_capture_buffer_prepare,
	.buf_queue	 = isp_video_capture_buffer_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.start_streaming = isp_video_capture_start_streaming,
	.stop_streaming	 = isp_video_capture_stop_streaming,
पूर्ण;

अटल पूर्णांक isp_video_खोलो(काष्ठा file *file)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);
	काष्ठा exynos_video_entity *ve = &isp->video_capture.ve;
	काष्ठा media_entity *me = &ve->vdev.entity;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&isp->video_lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ unlock;

	ret = pm_runसमय_get_sync(&isp->pdev->dev);
	अगर (ret < 0)
		जाओ rel_fh;

	अगर (v4l2_fh_is_singular_file(file)) अणु
		mutex_lock(&me->graph_obj.mdev->graph_mutex);

		ret = fimc_pipeline_call(ve, खोलो, me, true);

		/* Mark the video pipeline as in use. */
		अगर (ret == 0)
			me->use_count++;

		mutex_unlock(&me->graph_obj.mdev->graph_mutex);
	पूर्ण
	अगर (!ret)
		जाओ unlock;
rel_fh:
	pm_runसमय_put_noidle(&isp->pdev->dev);
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&isp->video_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक isp_video_release(काष्ठा file *file)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);
	काष्ठा fimc_is_video *ivc = &isp->video_capture;
	काष्ठा media_entity *entity = &ivc->ve.vdev.entity;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;

	mutex_lock(&isp->video_lock);

	अगर (v4l2_fh_is_singular_file(file) && ivc->streaming) अणु
		media_pipeline_stop(entity);
		ivc->streaming = 0;
	पूर्ण

	_vb2_fop_release(file, शून्य);

	अगर (v4l2_fh_is_singular_file(file)) अणु
		fimc_pipeline_call(&ivc->ve, बंद);

		mutex_lock(&mdev->graph_mutex);
		entity->use_count--;
		mutex_unlock(&mdev->graph_mutex);
	पूर्ण

	pm_runसमय_put(&isp->pdev->dev);
	mutex_unlock(&isp->video_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations isp_video_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= isp_video_खोलो,
	.release	= isp_video_release,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/*
 * Video node ioctl operations
 */
अटल पूर्णांक isp_video_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);

	__fimc_vidioc_querycap(&isp->pdev->dev, cap);
	वापस 0;
पूर्ण

अटल पूर्णांक isp_video_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा fimc_fmt *fmt;

	अगर (f->index >= FIMC_ISP_NUM_FORMATS)
		वापस -EINVAL;

	fmt = fimc_isp_find_क्रमmat(शून्य, शून्य, f->index);
	अगर (WARN_ON(fmt == शून्य))
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक isp_video_g_fmt_mplane(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);

	f->fmt.pix_mp = isp->video_capture.pixfmt;
	वापस 0;
पूर्ण

अटल व्योम __isp_video_try_fmt(काष्ठा fimc_isp *isp,
				काष्ठा v4l2_pix_क्रमmat_mplane *pixm,
				स्थिर काष्ठा fimc_fmt **fmt)
अणु
	स्थिर काष्ठा fimc_fmt *__fmt;

	__fmt = fimc_isp_find_क्रमmat(&pixm->pixelक्रमmat, शून्य, 2);

	अगर (fmt)
		*fmt = __fmt;

	pixm->colorspace = V4L2_COLORSPACE_SRGB;
	pixm->field = V4L2_FIELD_NONE;
	pixm->num_planes = __fmt->memplanes;
	pixm->pixelक्रमmat = __fmt->fourcc;
	/*
	 * TODO: द्विगुन check with the करोcmentation these width/height
	 * स्थिरraपूर्णांकs are correct.
	 */
	v4l_bound_align_image(&pixm->width, FIMC_ISP_SOURCE_WIDTH_MIN,
			      FIMC_ISP_SOURCE_WIDTH_MAX, 3,
			      &pixm->height, FIMC_ISP_SOURCE_HEIGHT_MIN,
			      FIMC_ISP_SOURCE_HEIGHT_MAX, 0, 0);
पूर्ण

अटल पूर्णांक isp_video_try_fmt_mplane(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);

	__isp_video_try_fmt(isp, &f->fmt.pix_mp, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक isp_video_s_fmt_mplane(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &f->fmt.pix_mp;
	स्थिर काष्ठा fimc_fmt *अगरmt = शून्य;
	काष्ठा param_dma_output *dma = __get_isp_dma2(is);

	__isp_video_try_fmt(isp, pixm, &अगरmt);

	अगर (WARN_ON(अगरmt == शून्य))
		वापस -EINVAL;

	dma->क्रमmat = DMA_OUTPUT_FORMAT_BAYER;
	dma->order = DMA_OUTPUT_ORDER_GB_BG;
	dma->plane = अगरmt->memplanes;
	dma->bitwidth = अगरmt->depth[0];
	dma->width = pixm->width;
	dma->height = pixm->height;

	fimc_is_mem_barrier();

	isp->video_capture.क्रमmat = अगरmt;
	isp->video_capture.pixfmt = *pixm;

	वापस 0;
पूर्ण

/*
 * Check क्रम source/sink क्रमmat dअगरferences at each link.
 * Return 0 अगर the क्रमmats match or -EPIPE otherwise.
 */
अटल पूर्णांक isp_video_pipeline_validate(काष्ठा fimc_isp *isp)
अणु
	काष्ठा v4l2_subdev *sd = &isp->subdev;
	काष्ठा v4l2_subdev_क्रमmat sink_fmt, src_fmt;
	काष्ठा media_pad *pad;
	पूर्णांक ret;

	जबतक (1) अणु
		/* Retrieve क्रमmat at the sink pad */
		pad = &sd->entity.pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;
		sink_fmt.pad = pad->index;
		sink_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &sink_fmt);
		अगर (ret < 0 && ret != -ENOIOCTLCMD)
			वापस -EPIPE;

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

अटल पूर्णांक isp_video_streamon(काष्ठा file *file, व्योम *priv,
				      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);
	काष्ठा exynos_video_entity *ve = &isp->video_capture.ve;
	काष्ठा media_entity *me = &ve->vdev.entity;
	पूर्णांक ret;

	ret = media_pipeline_start(me, &ve->pipe->mp);
	अगर (ret < 0)
		वापस ret;

	ret = isp_video_pipeline_validate(isp);
	अगर (ret < 0)
		जाओ p_stop;

	ret = vb2_ioctl_streamon(file, priv, type);
	अगर (ret < 0)
		जाओ p_stop;

	isp->video_capture.streaming = 1;
	वापस 0;
p_stop:
	media_pipeline_stop(me);
	वापस ret;
पूर्ण

अटल पूर्णांक isp_video_streamoff(काष्ठा file *file, व्योम *priv,
					क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);
	काष्ठा fimc_is_video *video = &isp->video_capture;
	पूर्णांक ret;

	ret = vb2_ioctl_streamoff(file, priv, type);
	अगर (ret < 0)
		वापस ret;

	media_pipeline_stop(&video->ve.vdev.entity);
	video->streaming = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक isp_video_reqbufs(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा fimc_isp *isp = video_drvdata(file);
	पूर्णांक ret;

	ret = vb2_ioctl_reqbufs(file, priv, rb);
	अगर (ret < 0)
		वापस ret;

	अगर (rb->count && rb->count < FIMC_ISP_REQ_BUFS_MIN) अणु
		rb->count = 0;
		vb2_ioctl_reqbufs(file, priv, rb);
		ret = -ENOMEM;
	पूर्ण

	isp->video_capture.reqbufs_count = rb->count;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops isp_video_ioctl_ops = अणु
	.vidioc_querycap		= isp_video_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= isp_video_क्रमागत_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= isp_video_try_fmt_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= isp_video_s_fmt_mplane,
	.vidioc_g_fmt_vid_cap_mplane	= isp_video_g_fmt_mplane,
	.vidioc_reqbufs			= isp_video_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_streamon		= isp_video_streamon,
	.vidioc_streamoff		= isp_video_streamoff,
पूर्ण;

पूर्णांक fimc_isp_video_device_रेजिस्टर(काष्ठा fimc_isp *isp,
				   काष्ठा v4l2_device *v4l2_dev,
				   क्रमागत v4l2_buf_type type)
अणु
	काष्ठा vb2_queue *q = &isp->video_capture.vb_queue;
	काष्ठा fimc_is_video *iv;
	काष्ठा video_device *vdev;
	पूर्णांक ret;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		iv = &isp->video_capture;
	अन्यथा
		वापस -ENOSYS;

	mutex_init(&isp->video_lock);
	INIT_LIST_HEAD(&iv->pending_buf_q);
	INIT_LIST_HEAD(&iv->active_buf_q);
	iv->क्रमmat = fimc_isp_find_क्रमmat(शून्य, शून्य, 0);
	iv->pixfmt.width = IS_DEFAULT_WIDTH;
	iv->pixfmt.height = IS_DEFAULT_HEIGHT;
	iv->pixfmt.pixelक्रमmat = iv->क्रमmat->fourcc;
	iv->pixfmt.colorspace = V4L2_COLORSPACE_SRGB;
	iv->reqbufs_count = 0;

	स_रखो(q, 0, माप(*q));
	q->type = type;
	q->io_modes = VB2_MMAP | VB2_USERPTR;
	q->ops = &isp_video_capture_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा isp_video_buf);
	q->drv_priv = isp;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &isp->video_lock;
	q->dev = &isp->pdev->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0)
		वापस ret;

	vdev = &iv->ve.vdev;
	स_रखो(vdev, 0, माप(*vdev));
	strscpy(vdev->name, "fimc-is-isp.capture", माप(vdev->name));
	vdev->queue = q;
	vdev->fops = &isp_video_fops;
	vdev->ioctl_ops = &isp_video_ioctl_ops;
	vdev->v4l2_dev = v4l2_dev;
	vdev->minor = -1;
	vdev->release = video_device_release_empty;
	vdev->lock = &isp->video_lock;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE;

	iv->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vdev->entity, 1, &iv->pad);
	अगर (ret < 0)
		वापस ret;

	video_set_drvdata(vdev, isp);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		media_entity_cleanup(&vdev->entity);
		वापस ret;
	पूर्ण

	v4l2_info(v4l2_dev, "Registered %s as /dev/%s\n",
		  vdev->name, video_device_node_name(vdev));

	वापस 0;
पूर्ण

व्योम fimc_isp_video_device_unरेजिस्टर(काष्ठा fimc_isp *isp,
				      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा exynos_video_entity *ve;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		ve = &isp->video_capture.ve;
	अन्यथा
		वापस;

	mutex_lock(&isp->video_lock);

	अगर (video_is_रेजिस्टरed(&ve->vdev)) अणु
		video_unरेजिस्टर_device(&ve->vdev);
		media_entity_cleanup(&ve->vdev.entity);
		ve->pipe = शून्य;
	पूर्ण

	mutex_unlock(&isp->video_lock);
पूर्ण
