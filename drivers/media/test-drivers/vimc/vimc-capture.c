<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vimc-capture.c Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "vimc-common.h"
#समावेश "vimc-streamer.h"

काष्ठा vimc_cap_device अणु
	काष्ठा vimc_ent_device ved;
	काष्ठा video_device vdev;
	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	काष्ठा vb2_queue queue;
	काष्ठा list_head buf_list;
	/*
	 * NOTE: in a real driver, a spin lock must be used to access the
	 * queue because the frames are generated from a hardware पूर्णांकerruption
	 * and the isr is not allowed to sleep.
	 * Even अगर it is not necessary a spinlock in the vimc driver, we
	 * use it here as a code reference
	 */
	spinlock_t qlock;
	काष्ठा mutex lock;
	u32 sequence;
	काष्ठा vimc_stream stream;
	काष्ठा media_pad pad;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat fmt_शेष = अणु
	.width = 640,
	.height = 480,
	.pixelक्रमmat = V4L2_PIX_FMT_RGB24,
	.field = V4L2_FIELD_NONE,
	.colorspace = V4L2_COLORSPACE_SRGB,
पूर्ण;

काष्ठा vimc_cap_buffer अणु
	/*
	 * काष्ठा vb2_v4l2_buffer must be the first element
	 * the videobuf2 framework will allocate this काष्ठा based on
	 * buf_काष्ठा_size and use the first माप(काष्ठा vb2_buffer) bytes of
	 * memory as a vb2_buffer
	 */
	काष्ठा vb2_v4l2_buffer vb2;
	काष्ठा list_head list;
पूर्ण;

अटल पूर्णांक vimc_cap_querycap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, VIMC_PDEV_NAME, माप(cap->driver));
	strscpy(cap->card, KBUILD_MODNAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", VIMC_PDEV_NAME);

	वापस 0;
पूर्ण

अटल व्योम vimc_cap_get_क्रमmat(काष्ठा vimc_ent_device *ved,
				काष्ठा v4l2_pix_क्रमmat *fmt)
अणु
	काष्ठा vimc_cap_device *vcap = container_of(ved, काष्ठा vimc_cap_device,
						    ved);

	*fmt = vcap->क्रमmat;
पूर्ण

अटल पूर्णांक vimc_cap_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vimc_cap_device *vcap = video_drvdata(file);

	f->fmt.pix = vcap->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_cap_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat *क्रमmat = &f->fmt.pix;
	स्थिर काष्ठा vimc_pix_map *vpix;

	क्रमmat->width = clamp_t(u32, क्रमmat->width, VIMC_FRAME_MIN_WIDTH,
				VIMC_FRAME_MAX_WIDTH) & ~1;
	क्रमmat->height = clamp_t(u32, क्रमmat->height, VIMC_FRAME_MIN_HEIGHT,
				 VIMC_FRAME_MAX_HEIGHT) & ~1;

	/* Don't accept a pixelक्रमmat that is not on the table */
	vpix = vimc_pix_map_by_pixelक्रमmat(क्रमmat->pixelक्रमmat);
	अगर (!vpix) अणु
		क्रमmat->pixelक्रमmat = fmt_शेष.pixelक्रमmat;
		vpix = vimc_pix_map_by_pixelक्रमmat(क्रमmat->pixelक्रमmat);
	पूर्ण
	/* TODO: Add support क्रम custom bytesperline values */
	क्रमmat->bytesperline = क्रमmat->width * vpix->bpp;
	क्रमmat->sizeimage = क्रमmat->bytesperline * क्रमmat->height;

	अगर (क्रमmat->field == V4L2_FIELD_ANY)
		क्रमmat->field = fmt_शेष.field;

	vimc_colorimetry_clamp(क्रमmat);

	अगर (क्रमmat->colorspace == V4L2_COLORSPACE_DEFAULT)
		क्रमmat->colorspace = fmt_शेष.colorspace;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_cap_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vimc_cap_device *vcap = video_drvdata(file);
	पूर्णांक ret;

	/* Do not change the क्रमmat जबतक stream is on */
	अगर (vb2_is_busy(&vcap->queue))
		वापस -EBUSY;

	ret = vimc_cap_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	dev_dbg(vcap->ved.dev, "%s: format update: "
		"old:%dx%d (0x%x, %d, %d, %d, %d) "
		"new:%dx%d (0x%x, %d, %d, %d, %d)\n", vcap->vdev.name,
		/* old */
		vcap->क्रमmat.width, vcap->क्रमmat.height,
		vcap->क्रमmat.pixelक्रमmat, vcap->क्रमmat.colorspace,
		vcap->क्रमmat.quantization, vcap->क्रमmat.xfer_func,
		vcap->क्रमmat.ycbcr_enc,
		/* new */
		f->fmt.pix.width, f->fmt.pix.height,
		f->fmt.pix.pixelक्रमmat,	f->fmt.pix.colorspace,
		f->fmt.pix.quantization, f->fmt.pix.xfer_func,
		f->fmt.pix.ycbcr_enc);

	vcap->क्रमmat = f->fmt.pix;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_cap_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;

	अगर (f->mbus_code) अणु
		अगर (f->index > 0)
			वापस -EINVAL;

		vpix = vimc_pix_map_by_code(f->mbus_code);
	पूर्ण अन्यथा अणु
		vpix = vimc_pix_map_by_index(f->index);
	पूर्ण

	अगर (!vpix)
		वापस -EINVAL;

	f->pixelक्रमmat = vpix->pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_cap_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;

	अगर (fsize->index)
		वापस -EINVAL;

	/* Only accept code in the pix map table */
	vpix = vimc_pix_map_by_code(fsize->pixel_क्रमmat);
	अगर (!vpix)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = VIMC_FRAME_MIN_WIDTH;
	fsize->stepwise.max_width = VIMC_FRAME_MAX_WIDTH;
	fsize->stepwise.min_height = VIMC_FRAME_MIN_HEIGHT;
	fsize->stepwise.max_height = VIMC_FRAME_MAX_HEIGHT;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vimc_cap_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.पढ़ो           = vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops vimc_cap_ioctl_ops = अणु
	.vidioc_querycap = vimc_cap_querycap,

	.vidioc_g_fmt_vid_cap = vimc_cap_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vimc_cap_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = vimc_cap_try_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap = vimc_cap_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_framesizes = vimc_cap_क्रमागत_framesizes,

	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
पूर्ण;

अटल व्योम vimc_cap_वापस_all_buffers(काष्ठा vimc_cap_device *vcap,
					क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vimc_cap_buffer *vbuf, *node;

	spin_lock(&vcap->qlock);

	list_क्रम_each_entry_safe(vbuf, node, &vcap->buf_list, list) अणु
		list_del(&vbuf->list);
		vb2_buffer_करोne(&vbuf->vb2.vb2_buf, state);
	पूर्ण

	spin_unlock(&vcap->qlock);
पूर्ण

अटल पूर्णांक vimc_cap_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vimc_cap_device *vcap = vb2_get_drv_priv(vq);
	काष्ठा media_entity *entity = &vcap->vdev.entity;
	पूर्णांक ret;

	vcap->sequence = 0;

	/* Start the media pipeline */
	ret = media_pipeline_start(entity, &vcap->stream.pipe);
	अगर (ret) अणु
		vimc_cap_वापस_all_buffers(vcap, VB2_BUF_STATE_QUEUED);
		वापस ret;
	पूर्ण

	ret = vimc_streamer_s_stream(&vcap->stream, &vcap->ved, 1);
	अगर (ret) अणु
		media_pipeline_stop(entity);
		vimc_cap_वापस_all_buffers(vcap, VB2_BUF_STATE_QUEUED);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Stop the stream engine. Any reमुख्यing buffers in the stream queue are
 * dequeued and passed on to the vb2 framework marked as STATE_ERROR.
 */
अटल व्योम vimc_cap_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vimc_cap_device *vcap = vb2_get_drv_priv(vq);

	vimc_streamer_s_stream(&vcap->stream, &vcap->ved, 0);

	/* Stop the media pipeline */
	media_pipeline_stop(&vcap->vdev.entity);

	/* Release all active buffers */
	vimc_cap_वापस_all_buffers(vcap, VB2_BUF_STATE_ERROR);
पूर्ण

अटल व्योम vimc_cap_buf_queue(काष्ठा vb2_buffer *vb2_buf)
अणु
	काष्ठा vimc_cap_device *vcap = vb2_get_drv_priv(vb2_buf->vb2_queue);
	काष्ठा vimc_cap_buffer *buf = container_of(vb2_buf,
						   काष्ठा vimc_cap_buffer,
						   vb2.vb2_buf);

	spin_lock(&vcap->qlock);
	list_add_tail(&buf->list, &vcap->buf_list);
	spin_unlock(&vcap->qlock);
पूर्ण

अटल पूर्णांक vimc_cap_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
				अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	काष्ठा vimc_cap_device *vcap = vb2_get_drv_priv(vq);

	अगर (*nplanes)
		वापस sizes[0] < vcap->क्रमmat.sizeimage ? -EINVAL : 0;
	/* We करोn't support multiplanes क्रम now */
	*nplanes = 1;
	sizes[0] = vcap->क्रमmat.sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_cap_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vimc_cap_device *vcap = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = vcap->क्रमmat.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_err(vcap->ved.dev, "%s: buffer too small (%lu < %lu)\n",
			vcap->vdev.name, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops vimc_cap_qops = अणु
	.start_streaming	= vimc_cap_start_streaming,
	.stop_streaming		= vimc_cap_stop_streaming,
	.buf_queue		= vimc_cap_buf_queue,
	.queue_setup		= vimc_cap_queue_setup,
	.buf_prepare		= vimc_cap_buffer_prepare,
	/*
	 * Since q->lock is set we can use the standard
	 * vb2_ops_रुको_prepare/finish helper functions.
	 */
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations vimc_cap_mops = अणु
	.link_validate		= vimc_vdev_link_validate,
पूर्ण;

अटल व्योम vimc_cap_release(काष्ठा vimc_ent_device *ved)
अणु
	काष्ठा vimc_cap_device *vcap =
		container_of(ved, काष्ठा vimc_cap_device, ved);

	media_entity_cleanup(vcap->ved.ent);
	kमुक्त(vcap);
पूर्ण

अटल व्योम vimc_cap_unरेजिस्टर(काष्ठा vimc_ent_device *ved)
अणु
	काष्ठा vimc_cap_device *vcap =
		container_of(ved, काष्ठा vimc_cap_device, ved);

	vb2_video_unरेजिस्टर_device(&vcap->vdev);
पूर्ण

अटल व्योम *vimc_cap_process_frame(काष्ठा vimc_ent_device *ved,
				    स्थिर व्योम *frame)
अणु
	काष्ठा vimc_cap_device *vcap = container_of(ved, काष्ठा vimc_cap_device,
						    ved);
	काष्ठा vimc_cap_buffer *vimc_buf;
	व्योम *vbuf;

	spin_lock(&vcap->qlock);

	/* Get the first entry of the list */
	vimc_buf = list_first_entry_or_null(&vcap->buf_list,
					    typeof(*vimc_buf), list);
	अगर (!vimc_buf) अणु
		spin_unlock(&vcap->qlock);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण

	/* Remove this entry from the list */
	list_del(&vimc_buf->list);

	spin_unlock(&vcap->qlock);

	/* Fill the buffer */
	vimc_buf->vb2.vb2_buf.बारtamp = kसमय_get_ns();
	vimc_buf->vb2.sequence = vcap->sequence++;
	vimc_buf->vb2.field = vcap->क्रमmat.field;

	vbuf = vb2_plane_vaddr(&vimc_buf->vb2.vb2_buf, 0);

	स_नकल(vbuf, frame, vcap->क्रमmat.sizeimage);

	/* Set it as पढ़ोy */
	vb2_set_plane_payload(&vimc_buf->vb2.vb2_buf, 0,
			      vcap->क्रमmat.sizeimage);
	vb2_buffer_करोne(&vimc_buf->vb2.vb2_buf, VB2_BUF_STATE_DONE);
	वापस शून्य;
पूर्ण

अटल काष्ठा vimc_ent_device *vimc_cap_add(काष्ठा vimc_device *vimc,
					    स्थिर अक्षर *vcfg_name)
अणु
	काष्ठा v4l2_device *v4l2_dev = &vimc->v4l2_dev;
	स्थिर काष्ठा vimc_pix_map *vpix;
	काष्ठा vimc_cap_device *vcap;
	काष्ठा video_device *vdev;
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	/* Allocate the vimc_cap_device काष्ठा */
	vcap = kzalloc(माप(*vcap), GFP_KERNEL);
	अगर (!vcap)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize the media entity */
	vcap->vdev.entity.name = vcfg_name;
	vcap->vdev.entity.function = MEDIA_ENT_F_IO_V4L;
	vcap->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vcap->vdev.entity,
				     1, &vcap->pad);
	अगर (ret)
		जाओ err_मुक्त_vcap;

	/* Initialize the lock */
	mutex_init(&vcap->lock);

	/* Initialize the vb2 queue */
	q = &vcap->queue;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_USERPTR;
	q->drv_priv = vcap;
	q->buf_काष्ठा_size = माप(काष्ठा vimc_cap_buffer);
	q->ops = &vimc_cap_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->lock = &vcap->lock;

	ret = vb2_queue_init(q);
	अगर (ret) अणु
		dev_err(vimc->mdev.dev, "%s: vb2 queue init failed (err=%d)\n",
			vcfg_name, ret);
		जाओ err_clean_m_ent;
	पूर्ण

	/* Initialize buffer list and its lock */
	INIT_LIST_HEAD(&vcap->buf_list);
	spin_lock_init(&vcap->qlock);

	/* Set शेष frame क्रमmat */
	vcap->क्रमmat = fmt_शेष;
	vpix = vimc_pix_map_by_pixelक्रमmat(vcap->क्रमmat.pixelक्रमmat);
	vcap->क्रमmat.bytesperline = vcap->क्रमmat.width * vpix->bpp;
	vcap->क्रमmat.sizeimage = vcap->क्रमmat.bytesperline *
				 vcap->क्रमmat.height;

	/* Fill the vimc_ent_device काष्ठा */
	vcap->ved.ent = &vcap->vdev.entity;
	vcap->ved.process_frame = vimc_cap_process_frame;
	vcap->ved.vdev_get_क्रमmat = vimc_cap_get_क्रमmat;
	vcap->ved.dev = vimc->mdev.dev;

	/* Initialize the video_device काष्ठा */
	vdev = &vcap->vdev;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING
			  | V4L2_CAP_IO_MC;
	vdev->entity.ops = &vimc_cap_mops;
	vdev->release = video_device_release_empty;
	vdev->fops = &vimc_cap_fops;
	vdev->ioctl_ops = &vimc_cap_ioctl_ops;
	vdev->lock = &vcap->lock;
	vdev->queue = q;
	vdev->v4l2_dev = v4l2_dev;
	vdev->vfl_dir = VFL_सूची_RX;
	strscpy(vdev->name, vcfg_name, माप(vdev->name));
	video_set_drvdata(vdev, &vcap->ved);

	/* Register the video_device with the v4l2 and the media framework */
	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(vimc->mdev.dev, "%s: video register failed (err=%d)\n",
			vcap->vdev.name, ret);
		जाओ err_clean_m_ent;
	पूर्ण

	वापस &vcap->ved;

err_clean_m_ent:
	media_entity_cleanup(&vcap->vdev.entity);
err_मुक्त_vcap:
	kमुक्त(vcap);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा vimc_ent_type vimc_cap_type = अणु
	.add = vimc_cap_add,
	.unरेजिस्टर = vimc_cap_unरेजिस्टर,
	.release = vimc_cap_release
पूर्ण;
