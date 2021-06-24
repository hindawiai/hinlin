<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_histo.c  --  R-Car VSP1 Histogram API
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2016 Laurent Pinअक्षरt
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "vsp1.h"
#समावेश "vsp1_histo.h"
#समावेश "vsp1_pipe.h"

#घोषणा HISTO_MIN_SIZE				4U
#घोषणा HISTO_MAX_SIZE				8192U

/* -----------------------------------------------------------------------------
 * Buffer Operations
 */

अटल अंतरभूत काष्ठा vsp1_histogram_buffer *
to_vsp1_histogram_buffer(काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	वापस container_of(vbuf, काष्ठा vsp1_histogram_buffer, buf);
पूर्ण

काष्ठा vsp1_histogram_buffer *
vsp1_histogram_buffer_get(काष्ठा vsp1_histogram *histo)
अणु
	काष्ठा vsp1_histogram_buffer *buf = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&histo->irqlock, flags);

	अगर (list_empty(&histo->irqqueue))
		जाओ करोne;

	buf = list_first_entry(&histo->irqqueue, काष्ठा vsp1_histogram_buffer,
			       queue);
	list_del(&buf->queue);
	histo->पढ़ोout = true;

करोne:
	spin_unlock_irqrestore(&histo->irqlock, flags);
	वापस buf;
पूर्ण

व्योम vsp1_histogram_buffer_complete(काष्ठा vsp1_histogram *histo,
				    काष्ठा vsp1_histogram_buffer *buf,
				    माप_प्रकार size)
अणु
	काष्ठा vsp1_pipeline *pipe = histo->entity.pipe;
	अचिन्हित दीर्घ flags;

	/*
	 * The pipeline poपूर्णांकer is guaranteed to be valid as this function is
	 * called from the frame completion पूर्णांकerrupt handler, which can only
	 * occur when video streaming is active.
	 */
	buf->buf.sequence = pipe->sequence;
	buf->buf.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, size);
	vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);

	spin_lock_irqsave(&histo->irqlock, flags);
	histo->पढ़ोout = false;
	wake_up(&histo->रुको_queue);
	spin_unlock_irqrestore(&histo->irqlock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * videobuf2 Queue Operations
 */

अटल पूर्णांक histo_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
			     अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			     काष्ठा device *alloc_devs[])
अणु
	काष्ठा vsp1_histogram *histo = vb2_get_drv_priv(vq);

	अगर (*nplanes) अणु
		अगर (*nplanes != 1)
			वापस -EINVAL;

		अगर (sizes[0] < histo->data_size)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	*nplanes = 1;
	sizes[0] = histo->data_size;

	वापस 0;
पूर्ण

अटल पूर्णांक histo_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vsp1_histogram *histo = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vsp1_histogram_buffer *buf = to_vsp1_histogram_buffer(vbuf);

	अगर (vb->num_planes != 1)
		वापस -EINVAL;

	अगर (vb2_plane_size(vb, 0) < histo->data_size)
		वापस -EINVAL;

	buf->addr = vb2_plane_vaddr(vb, 0);

	वापस 0;
पूर्ण

अटल व्योम histo_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vsp1_histogram *histo = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vsp1_histogram_buffer *buf = to_vsp1_histogram_buffer(vbuf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&histo->irqlock, flags);
	list_add_tail(&buf->queue, &histo->irqqueue);
	spin_unlock_irqrestore(&histo->irqlock, flags);
पूर्ण

अटल पूर्णांक histo_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	वापस 0;
पूर्ण

अटल व्योम histo_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vsp1_histogram *histo = vb2_get_drv_priv(vq);
	काष्ठा vsp1_histogram_buffer *buffer;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&histo->irqlock, flags);

	/* Remove all buffers from the IRQ queue. */
	list_क्रम_each_entry(buffer, &histo->irqqueue, queue)
		vb2_buffer_करोne(&buffer->buf.vb2_buf, VB2_BUF_STATE_ERROR);
	INIT_LIST_HEAD(&histo->irqqueue);

	/* Wait क्रम the buffer being पढ़ो out (अगर any) to complete. */
	रुको_event_lock_irq(histo->रुको_queue, !histo->पढ़ोout, histo->irqlock);

	spin_unlock_irqrestore(&histo->irqlock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops histo_video_queue_qops = अणु
	.queue_setup = histo_queue_setup,
	.buf_prepare = histo_buffer_prepare,
	.buf_queue = histo_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = histo_start_streaming,
	.stop_streaming = histo_stop_streaming,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

अटल पूर्णांक histo_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(subdev);

	अगर (code->pad == HISTO_PAD_SOURCE) अणु
		code->code = MEDIA_BUS_FMT_FIXED;
		वापस 0;
	पूर्ण

	वापस vsp1_subdev_क्रमागत_mbus_code(subdev, cfg, code, histo->क्रमmats,
					  histo->num_क्रमmats);
पूर्ण

अटल पूर्णांक histo_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->pad != HISTO_PAD_SINK)
		वापस -EINVAL;

	वापस vsp1_subdev_क्रमागत_frame_size(subdev, cfg, fse, HISTO_MIN_SIZE,
					   HISTO_MIN_SIZE, HISTO_MAX_SIZE,
					   HISTO_MAX_SIZE);
पूर्ण

अटल पूर्णांक histo_get_selection(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;
	पूर्णांक ret = 0;

	अगर (sel->pad != HISTO_PAD_SINK)
		वापस -EINVAL;

	mutex_lock(&histo->entity.lock);

	config = vsp1_entity_get_pad_config(&histo->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		crop = vsp1_entity_get_pad_selection(&histo->entity, config,
						     HISTO_PAD_SINK,
						     V4L2_SEL_TGT_CROP);
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = crop->width;
		sel->r.height = crop->height;
		अवरोध;

	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		क्रमmat = vsp1_entity_get_pad_क्रमmat(&histo->entity, config,
						    HISTO_PAD_SINK);
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = क्रमmat->width;
		sel->r.height = क्रमmat->height;
		अवरोध;

	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *vsp1_entity_get_pad_selection(&histo->entity, config,
							sel->pad, sel->target);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

करोne:
	mutex_unlock(&histo->entity.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक histo_set_crop(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *config,
			 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *selection;

	/* The crop rectangle must be inside the input frame. */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&histo->entity, config,
					    HISTO_PAD_SINK);
	sel->r.left = clamp_t(अचिन्हित पूर्णांक, sel->r.left, 0, क्रमmat->width - 1);
	sel->r.top = clamp_t(अचिन्हित पूर्णांक, sel->r.top, 0, क्रमmat->height - 1);
	sel->r.width = clamp_t(अचिन्हित पूर्णांक, sel->r.width, HISTO_MIN_SIZE,
			       क्रमmat->width - sel->r.left);
	sel->r.height = clamp_t(अचिन्हित पूर्णांक, sel->r.height, HISTO_MIN_SIZE,
				क्रमmat->height - sel->r.top);

	/* Set the crop rectangle and reset the compose rectangle. */
	selection = vsp1_entity_get_pad_selection(&histo->entity, config,
						  sel->pad, V4L2_SEL_TGT_CROP);
	*selection = sel->r;

	selection = vsp1_entity_get_pad_selection(&histo->entity, config,
						  sel->pad,
						  V4L2_SEL_TGT_COMPOSE);
	*selection = sel->r;

	वापस 0;
पूर्ण

अटल पूर्णांक histo_set_compose(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *config,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(subdev);
	काष्ठा v4l2_rect *compose;
	काष्ठा v4l2_rect *crop;
	अचिन्हित पूर्णांक ratio;

	/*
	 * The compose rectangle is used to configure करोwnscaling, the top left
	 * corner is fixed to (0,0) and the size to 1/2 or 1/4 of the crop
	 * rectangle.
	 */
	sel->r.left = 0;
	sel->r.top = 0;

	crop = vsp1_entity_get_pad_selection(&histo->entity, config, sel->pad,
					     V4L2_SEL_TGT_CROP);

	/*
	 * Clamp the width and height to acceptable values first and then
	 * compute the बंदst rounded भागiding ratio.
	 *
	 * Ratio	Rounded ratio
	 * --------------------------
	 * [1.0 1.5[	1
	 * [1.5 3.0[	2
	 * [3.0 4.0]	4
	 *
	 * The rounded ratio can be computed using
	 *
	 * 1 << (उच्चमान(ratio * 2) / 3)
	 */
	sel->r.width = clamp(sel->r.width, crop->width / 4, crop->width);
	ratio = 1 << (crop->width * 2 / sel->r.width / 3);
	sel->r.width = crop->width / ratio;


	sel->r.height = clamp(sel->r.height, crop->height / 4, crop->height);
	ratio = 1 << (crop->height * 2 / sel->r.height / 3);
	sel->r.height = crop->height / ratio;

	compose = vsp1_entity_get_pad_selection(&histo->entity, config,
						sel->pad,
						V4L2_SEL_TGT_COMPOSE);
	*compose = sel->r;

	वापस 0;
पूर्ण

अटल पूर्णांक histo_set_selection(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(subdev);
	काष्ठा v4l2_subdev_pad_config *config;
	पूर्णांक ret;

	अगर (sel->pad != HISTO_PAD_SINK)
		वापस -EINVAL;

	mutex_lock(&histo->entity.lock);

	config = vsp1_entity_get_pad_config(&histo->entity, cfg, sel->which);
	अगर (!config) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (sel->target == V4L2_SEL_TGT_CROP)
		ret = histo_set_crop(subdev, config, sel);
	अन्यथा अगर (sel->target == V4L2_SEL_TGT_COMPOSE)
		ret = histo_set_compose(subdev, config, sel);
	अन्यथा
		ret = -EINVAL;

करोne:
	mutex_unlock(&histo->entity.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक histo_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अगर (fmt->pad == HISTO_PAD_SOURCE) अणु
		fmt->क्रमmat.code = MEDIA_BUS_FMT_FIXED;
		fmt->क्रमmat.width = 0;
		fmt->क्रमmat.height = 0;
		fmt->क्रमmat.field = V4L2_FIELD_NONE;
		fmt->क्रमmat.colorspace = V4L2_COLORSPACE_RAW;
		वापस 0;
	पूर्ण

	वापस vsp1_subdev_get_pad_क्रमmat(subdev, cfg, fmt);
पूर्ण

अटल पूर्णांक histo_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(subdev);

	अगर (fmt->pad != HISTO_PAD_SINK)
		वापस histo_get_क्रमmat(subdev, cfg, fmt);

	वापस vsp1_subdev_set_pad_क्रमmat(subdev, cfg, fmt,
					  histo->क्रमmats, histo->num_क्रमmats,
					  HISTO_MIN_SIZE, HISTO_MIN_SIZE,
					  HISTO_MAX_SIZE, HISTO_MAX_SIZE);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops histo_pad_ops = अणु
	.क्रमागत_mbus_code = histo_क्रमागत_mbus_code,
	.क्रमागत_frame_size = histo_क्रमागत_frame_size,
	.get_fmt = histo_get_क्रमmat,
	.set_fmt = histo_set_क्रमmat,
	.get_selection = histo_get_selection,
	.set_selection = histo_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops histo_ops = अणु
	.pad    = &histo_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक histo_v4l2_querycap(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_capability *cap)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_histogram *histo = vdev_to_histo(vfh->vdev);

	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | V4L2_CAP_VIDEO_CAPTURE_MPLANE
			  | V4L2_CAP_VIDEO_OUTPUT_MPLANE
			  | V4L2_CAP_META_CAPTURE;

	strscpy(cap->driver, "vsp1", माप(cap->driver));
	strscpy(cap->card, histo->video.name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(histo->entity.vsp1->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक histo_v4l2_क्रमागत_क्रमmat(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_histogram *histo = vdev_to_histo(vfh->vdev);

	अगर (f->index > 0 || f->type != histo->queue.type)
		वापस -EINVAL;

	f->pixelक्रमmat = histo->meta_क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक histo_v4l2_get_क्रमmat(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_histogram *histo = vdev_to_histo(vfh->vdev);
	काष्ठा v4l2_meta_क्रमmat *meta = &क्रमmat->fmt.meta;

	अगर (क्रमmat->type != histo->queue.type)
		वापस -EINVAL;

	स_रखो(meta, 0, माप(*meta));

	meta->dataक्रमmat = histo->meta_क्रमmat;
	meta->buffersize = histo->data_size;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops histo_v4l2_ioctl_ops = अणु
	.vidioc_querycap		= histo_v4l2_querycap,
	.vidioc_क्रमागत_fmt_meta_cap	= histo_v4l2_क्रमागत_क्रमmat,
	.vidioc_g_fmt_meta_cap		= histo_v4l2_get_क्रमmat,
	.vidioc_s_fmt_meta_cap		= histo_v4l2_get_क्रमmat,
	.vidioc_try_fmt_meta_cap	= histo_v4l2_get_क्रमmat,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 File Operations
 */

अटल स्थिर काष्ठा v4l2_file_operations histo_v4l2_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
पूर्ण;

अटल व्योम vsp1_histogram_cleanup(काष्ठा vsp1_histogram *histo)
अणु
	अगर (video_is_रेजिस्टरed(&histo->video))
		video_unरेजिस्टर_device(&histo->video);

	media_entity_cleanup(&histo->video.entity);
पूर्ण

व्योम vsp1_histogram_destroy(काष्ठा vsp1_entity *entity)
अणु
	काष्ठा vsp1_histogram *histo = subdev_to_histo(&entity->subdev);

	vsp1_histogram_cleanup(histo);
पूर्ण

पूर्णांक vsp1_histogram_init(काष्ठा vsp1_device *vsp1, काष्ठा vsp1_histogram *histo,
			क्रमागत vsp1_entity_type type, स्थिर अक्षर *name,
			स्थिर काष्ठा vsp1_entity_operations *ops,
			स्थिर अचिन्हित पूर्णांक *क्रमmats, अचिन्हित पूर्णांक num_क्रमmats,
			माप_प्रकार data_size, u32 meta_क्रमmat)
अणु
	पूर्णांक ret;

	histo->क्रमmats = क्रमmats;
	histo->num_क्रमmats = num_क्रमmats;
	histo->data_size = data_size;
	histo->meta_क्रमmat = meta_क्रमmat;

	histo->pad.flags = MEDIA_PAD_FL_SINK;
	histo->video.vfl_dir = VFL_सूची_RX;

	mutex_init(&histo->lock);
	spin_lock_init(&histo->irqlock);
	INIT_LIST_HEAD(&histo->irqqueue);
	init_रुकोqueue_head(&histo->रुको_queue);

	/* Initialize the VSP entity... */
	histo->entity.ops = ops;
	histo->entity.type = type;

	ret = vsp1_entity_init(vsp1, &histo->entity, name, 2, &histo_ops,
			       MEDIA_ENT_F_PROC_VIDEO_STATISTICS);
	अगर (ret < 0)
		वापस ret;

	/* ... and the media entity... */
	ret = media_entity_pads_init(&histo->video.entity, 1, &histo->pad);
	अगर (ret < 0)
		वापस ret;

	/* ... and the video node... */
	histo->video.v4l2_dev = &vsp1->v4l2_dev;
	histo->video.fops = &histo_v4l2_fops;
	snम_लिखो(histo->video.name, माप(histo->video.name),
		 "%s histo", histo->entity.subdev.name);
	histo->video.vfl_type = VFL_TYPE_VIDEO;
	histo->video.release = video_device_release_empty;
	histo->video.ioctl_ops = &histo_v4l2_ioctl_ops;
	histo->video.device_caps = V4L2_CAP_META_CAPTURE | V4L2_CAP_STREAMING;

	video_set_drvdata(&histo->video, histo);

	/* ... and the buffers queue... */
	histo->queue.type = V4L2_BUF_TYPE_META_CAPTURE;
	histo->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	histo->queue.lock = &histo->lock;
	histo->queue.drv_priv = histo;
	histo->queue.buf_काष्ठा_size = माप(काष्ठा vsp1_histogram_buffer);
	histo->queue.ops = &histo_video_queue_qops;
	histo->queue.mem_ops = &vb2_vदो_स्मृति_memops;
	histo->queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	histo->queue.dev = vsp1->dev;
	ret = vb2_queue_init(&histo->queue);
	अगर (ret < 0) अणु
		dev_err(vsp1->dev, "failed to initialize vb2 queue\n");
		जाओ error;
	पूर्ण

	/* ... and रेजिस्टर the video device. */
	histo->video.queue = &histo->queue;
	ret = video_रेजिस्टर_device(&histo->video, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_err(vsp1->dev, "failed to register video device\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	vsp1_histogram_cleanup(histo);
	वापस ret;
पूर्ण
