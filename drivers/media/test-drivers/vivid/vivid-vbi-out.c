<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-vbi-out.c - vbi output support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>

#समावेश "vivid-core.h"
#समावेश "vivid-kthread-out.h"
#समावेश "vivid-vbi-out.h"
#समावेश "vivid-vbi-cap.h"

अटल पूर्णांक vbi_out_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित *nbuffers, अचिन्हित *nplanes,
		       अचिन्हित sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	bool is_60hz = dev->std_out & V4L2_STD_525_60;
	अचिन्हित size = vq->type == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT ?
		36 * माप(काष्ठा v4l2_sliced_vbi_data) :
		1440 * 2 * (is_60hz ? 12 : 18);

	अगर (!vivid_is_svid_out(dev))
		वापस -EINVAL;

	sizes[0] = size;

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vbi_out_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	bool is_60hz = dev->std_out & V4L2_STD_525_60;
	अचिन्हित size = vb->vb2_queue->type == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT ?
		36 * माप(काष्ठा v4l2_sliced_vbi_data) :
		1440 * 2 * (is_60hz ? 12 : 18);

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

अटल व्योम vbi_out_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->vbi_out_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक vbi_out_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक err;

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	dev->vbi_out_seq_count = 0;
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = vivid_start_generating_vid_out(dev, &dev->vbi_out_streaming);
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dev->vbi_out_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम vbi_out_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	vivid_stop_generating_vid_out(dev, &dev->vbi_out_streaming);
	dev->vbi_out_have_wss = false;
	dev->vbi_out_have_cc[0] = false;
	dev->vbi_out_have_cc[1] = false;
पूर्ण

अटल व्योम vbi_out_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_vbi_out);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_vbi_out_qops = अणु
	.queue_setup		= vbi_out_queue_setup,
	.buf_prepare		= vbi_out_buf_prepare,
	.buf_queue		= vbi_out_buf_queue,
	.start_streaming	= vbi_out_start_streaming,
	.stop_streaming		= vbi_out_stop_streaming,
	.buf_request_complete	= vbi_out_buf_request_complete,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक vidioc_g_fmt_vbi_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_vbi_क्रमmat *vbi = &f->fmt.vbi;
	bool is_60hz = dev->std_out & V4L2_STD_525_60;

	अगर (!vivid_is_svid_out(dev) || !dev->has_raw_vbi_out)
		वापस -EINVAL;

	vbi->sampling_rate = 25000000;
	vbi->offset = 24;
	vbi->samples_per_line = 1440;
	vbi->sample_क्रमmat = V4L2_PIX_FMT_GREY;
	vbi->start[0] = is_60hz ? V4L2_VBI_ITU_525_F1_START + 9 : V4L2_VBI_ITU_625_F1_START + 5;
	vbi->start[1] = is_60hz ? V4L2_VBI_ITU_525_F2_START + 9 : V4L2_VBI_ITU_625_F2_START + 5;
	vbi->count[0] = vbi->count[1] = is_60hz ? 12 : 18;
	vbi->flags = dev->vbi_cap_पूर्णांकerlaced ? V4L2_VBI_INTERLACED : 0;
	vbi->reserved[0] = 0;
	vbi->reserved[1] = 0;
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_vbi_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	पूर्णांक ret = vidioc_g_fmt_vbi_out(file, priv, f);

	अगर (ret)
		वापस ret;
	अगर (vb2_is_busy(&dev->vb_vbi_out_q))
		वापस -EBUSY;
	dev->stream_sliced_vbi_out = false;
	dev->vbi_out_dev.queue->type = V4L2_BUF_TYPE_VBI_OUTPUT;
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbi = &fmt->fmt.sliced;

	अगर (!vivid_is_svid_out(dev) || !dev->has_sliced_vbi_out)
		वापस -EINVAL;

	vivid_fill_service_lines(vbi, dev->service_set_out);
	वापस 0;
पूर्ण

पूर्णांक vidioc_try_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbi = &fmt->fmt.sliced;
	bool is_60hz = dev->std_out & V4L2_STD_525_60;
	u32 service_set = vbi->service_set;

	अगर (!vivid_is_svid_out(dev) || !dev->has_sliced_vbi_out)
		वापस -EINVAL;

	service_set &= is_60hz ? V4L2_SLICED_CAPTION_525 :
				 V4L2_SLICED_WSS_625 | V4L2_SLICED_TELETEXT_B;
	vivid_fill_service_lines(vbi, service_set);
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbi = &fmt->fmt.sliced;
	पूर्णांक ret = vidioc_try_fmt_sliced_vbi_out(file, fh, fmt);

	अगर (ret)
		वापस ret;
	अगर (vb2_is_busy(&dev->vb_vbi_out_q))
		वापस -EBUSY;
	dev->service_set_out = vbi->service_set;
	dev->stream_sliced_vbi_out = true;
	dev->vbi_out_dev.queue->type = V4L2_BUF_TYPE_SLICED_VBI_OUTPUT;
	वापस 0;
पूर्ण

व्योम vivid_sliced_vbi_out_process(काष्ठा vivid_dev *dev,
		काष्ठा vivid_buffer *buf)
अणु
	काष्ठा v4l2_sliced_vbi_data *vbi =
		vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	अचिन्हित elems =
		vb2_get_plane_payload(&buf->vb.vb2_buf, 0) / माप(*vbi);

	dev->vbi_out_have_cc[0] = false;
	dev->vbi_out_have_cc[1] = false;
	dev->vbi_out_have_wss = false;
	जबतक (elems--) अणु
		चयन (vbi->id) अणु
		हाल V4L2_SLICED_CAPTION_525:
			अगर ((dev->std_out & V4L2_STD_525_60) && vbi->line == 21) अणु
				dev->vbi_out_have_cc[!!vbi->field] = true;
				dev->vbi_out_cc[!!vbi->field][0] = vbi->data[0];
				dev->vbi_out_cc[!!vbi->field][1] = vbi->data[1];
			पूर्ण
			अवरोध;
		हाल V4L2_SLICED_WSS_625:
			अगर ((dev->std_out & V4L2_STD_625_50) &&
			    vbi->field == 0 && vbi->line == 23) अणु
				dev->vbi_out_have_wss = true;
				dev->vbi_out_wss[0] = vbi->data[0];
				dev->vbi_out_wss[1] = vbi->data[1];
			पूर्ण
			अवरोध;
		पूर्ण
		vbi++;
	पूर्ण
पूर्ण
