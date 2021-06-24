<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-meta-out.c - meta output support functions.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/usb/video.h>

#समावेश "vivid-core.h"
#समावेश "vivid-kthread-out.h"
#समावेश "vivid-meta-out.h"

अटल पूर्णांक meta_out_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
				अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size =  माप(काष्ठा vivid_meta_out_buf);

	अगर (!vivid_is_webcam(dev))
		वापस -EINVAL;

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		sizes[0] = size;
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक meta_out_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित पूर्णांक size = माप(काष्ठा vivid_meta_out_buf);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->buf_prepare_error) अणु
		/*
		 * Error injection: test what happens अगर buf_prepare() वापसs
		 * an error.
		 */
		dev->buf_prepare_error = false;
		वापस -EINVAL;
	पूर्ण
	अगर (vb2_plane_size(vb, 0) < size) अणु
		dprपूर्णांकk(dev, 1, "%s data will not fit into plane (%lu < %u)\n",
			__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम meta_out_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->meta_out_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक meta_out_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक err;

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	dev->meta_out_seq_count = 0;
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = vivid_start_generating_vid_out(dev,
						     &dev->meta_out_streaming);
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp,
					 &dev->meta_out_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम meta_out_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	vivid_stop_generating_vid_out(dev, &dev->meta_out_streaming);
पूर्ण

अटल व्योम meta_out_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_meta_out);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_meta_out_qops = अणु
	.queue_setup            = meta_out_queue_setup,
	.buf_prepare            = meta_out_buf_prepare,
	.buf_queue              = meta_out_buf_queue,
	.start_streaming        = meta_out_start_streaming,
	.stop_streaming         = meta_out_stop_streaming,
	.buf_request_complete   = meta_out_buf_request_complete,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक vidioc_क्रमागत_fmt_meta_out(काष्ठा file *file, व्योम  *priv,
			     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_webcam(dev))
		वापस -EINVAL;

	अगर (f->index > 0)
		वापस -EINVAL;

	f->type = V4L2_BUF_TYPE_META_OUTPUT;
	f->pixelक्रमmat = V4L2_META_FMT_VIVID;
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_fmt_meta_out(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_meta_क्रमmat *meta = &f->fmt.meta;

	अगर (!vivid_is_webcam(dev) || !dev->has_meta_out)
		वापस -EINVAL;

	meta->dataक्रमmat = V4L2_META_FMT_VIVID;
	meta->buffersize = माप(काष्ठा vivid_meta_out_buf);
	वापस 0;
पूर्ण

व्योम vivid_meta_out_process(काष्ठा vivid_dev *dev,
			    काष्ठा vivid_buffer *buf)
अणु
	काष्ठा vivid_meta_out_buf *meta = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	v4l2_ctrl_s_ctrl(dev->brightness, meta->brightness);
	v4l2_ctrl_s_ctrl(dev->contrast, meta->contrast);
	v4l2_ctrl_s_ctrl(dev->saturation, meta->saturation);
	v4l2_ctrl_s_ctrl(dev->hue, meta->hue);

	dprपूर्णांकk(dev, 2, " %s brightness %u contrast %u saturation %u hue %d\n",
		__func__, meta->brightness, meta->contrast,
		meta->saturation, meta->hue);
पूर्ण
