<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-vbi-cap.c - vbi capture support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>

#समावेश "vivid-core.h"
#समावेश "vivid-kthread-cap.h"
#समावेश "vivid-vbi-cap.h"
#समावेश "vivid-vbi-gen.h"

अटल व्योम vivid_sliced_vbi_cap_fill(काष्ठा vivid_dev *dev, अचिन्हित seqnr)
अणु
	काष्ठा vivid_vbi_gen_data *vbi_gen = &dev->vbi_gen;
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;

	vivid_vbi_gen_sliced(vbi_gen, is_60hz, seqnr);

	अगर (!is_60hz) अणु
		अगर (dev->loop_video) अणु
			अगर (dev->vbi_out_have_wss) अणु
				vbi_gen->data[12].data[0] = dev->vbi_out_wss[0];
				vbi_gen->data[12].data[1] = dev->vbi_out_wss[1];
			पूर्ण अन्यथा अणु
				vbi_gen->data[12].id = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (tpg_g_video_aspect(&dev->tpg)) अणु
			हाल TPG_VIDEO_ASPECT_14X9_CENTRE:
				vbi_gen->data[12].data[0] = 0x01;
				अवरोध;
			हाल TPG_VIDEO_ASPECT_16X9_CENTRE:
				vbi_gen->data[12].data[0] = 0x0b;
				अवरोध;
			हाल TPG_VIDEO_ASPECT_16X9_ANAMORPHIC:
				vbi_gen->data[12].data[0] = 0x07;
				अवरोध;
			हाल TPG_VIDEO_ASPECT_4X3:
			शेष:
				vbi_gen->data[12].data[0] = 0x08;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (dev->loop_video && is_60hz) अणु
		अगर (dev->vbi_out_have_cc[0]) अणु
			vbi_gen->data[0].data[0] = dev->vbi_out_cc[0][0];
			vbi_gen->data[0].data[1] = dev->vbi_out_cc[0][1];
		पूर्ण अन्यथा अणु
			vbi_gen->data[0].id = 0;
		पूर्ण
		अगर (dev->vbi_out_have_cc[1]) अणु
			vbi_gen->data[1].data[0] = dev->vbi_out_cc[1][0];
			vbi_gen->data[1].data[1] = dev->vbi_out_cc[1][1];
		पूर्ण अन्यथा अणु
			vbi_gen->data[1].id = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vivid_g_fmt_vbi_cap(काष्ठा vivid_dev *dev, काष्ठा v4l2_vbi_क्रमmat *vbi)
अणु
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;

	vbi->sampling_rate = 27000000;
	vbi->offset = 24;
	vbi->samples_per_line = 1440;
	vbi->sample_क्रमmat = V4L2_PIX_FMT_GREY;
	vbi->start[0] = is_60hz ? V4L2_VBI_ITU_525_F1_START + 9 : V4L2_VBI_ITU_625_F1_START + 5;
	vbi->start[1] = is_60hz ? V4L2_VBI_ITU_525_F2_START + 9 : V4L2_VBI_ITU_625_F2_START + 5;
	vbi->count[0] = vbi->count[1] = is_60hz ? 12 : 18;
	vbi->flags = dev->vbi_cap_पूर्णांकerlaced ? V4L2_VBI_INTERLACED : 0;
	vbi->reserved[0] = 0;
	vbi->reserved[1] = 0;
पूर्ण

व्योम vivid_raw_vbi_cap_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf)
अणु
	काष्ठा v4l2_vbi_क्रमmat vbi;
	u8 *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	vivid_g_fmt_vbi_cap(dev, &vbi);
	buf->vb.sequence = dev->vbi_cap_seq_count;
	अगर (dev->field_cap == V4L2_FIELD_ALTERNATE)
		buf->vb.sequence /= 2;

	vivid_sliced_vbi_cap_fill(dev, buf->vb.sequence);

	स_रखो(vbuf, 0x10, vb2_plane_size(&buf->vb.vb2_buf, 0));

	अगर (!VIVID_INVALID_SIGNAL(dev->std_संकेत_mode[dev->input]))
		vivid_vbi_gen_raw(&dev->vbi_gen, &vbi, vbuf);
पूर्ण


व्योम vivid_sliced_vbi_cap_process(काष्ठा vivid_dev *dev,
			काष्ठा vivid_buffer *buf)
अणु
	काष्ठा v4l2_sliced_vbi_data *vbuf =
			vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	buf->vb.sequence = dev->vbi_cap_seq_count;
	अगर (dev->field_cap == V4L2_FIELD_ALTERNATE)
		buf->vb.sequence /= 2;

	vivid_sliced_vbi_cap_fill(dev, buf->vb.sequence);

	स_रखो(vbuf, 0, vb2_plane_size(&buf->vb.vb2_buf, 0));
	अगर (!VIVID_INVALID_SIGNAL(dev->std_संकेत_mode[dev->input])) अणु
		अचिन्हित i;

		क्रम (i = 0; i < 25; i++)
			vbuf[i] = dev->vbi_gen.data[i];
	पूर्ण
पूर्ण

अटल पूर्णांक vbi_cap_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित *nbuffers, अचिन्हित *nplanes,
		       अचिन्हित sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;
	अचिन्हित size = vq->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ?
		36 * माप(काष्ठा v4l2_sliced_vbi_data) :
		1440 * 2 * (is_60hz ? 12 : 18);

	अगर (!vivid_is_sdtv_cap(dev))
		वापस -EINVAL;

	sizes[0] = size;

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vbi_cap_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;
	अचिन्हित size = vb->vb2_queue->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ?
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

अटल व्योम vbi_cap_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->vbi_cap_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक vbi_cap_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक err;

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	dev->vbi_cap_seq_count = 0;
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = vivid_start_generating_vid_cap(dev, &dev->vbi_cap_streaming);
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dev->vbi_cap_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम vbi_cap_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	vivid_stop_generating_vid_cap(dev, &dev->vbi_cap_streaming);
पूर्ण

अटल व्योम vbi_cap_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_vbi_cap);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_vbi_cap_qops = अणु
	.queue_setup		= vbi_cap_queue_setup,
	.buf_prepare		= vbi_cap_buf_prepare,
	.buf_queue		= vbi_cap_buf_queue,
	.start_streaming	= vbi_cap_start_streaming,
	.stop_streaming		= vbi_cap_stop_streaming,
	.buf_request_complete	= vbi_cap_buf_request_complete,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक vidioc_g_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_vbi_क्रमmat *vbi = &f->fmt.vbi;

	अगर (!vivid_is_sdtv_cap(dev) || !dev->has_raw_vbi_cap)
		वापस -EINVAL;

	vivid_g_fmt_vbi_cap(dev, vbi);
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	पूर्णांक ret = vidioc_g_fmt_vbi_cap(file, priv, f);

	अगर (ret)
		वापस ret;
	अगर (dev->stream_sliced_vbi_cap && vb2_is_busy(&dev->vb_vbi_cap_q))
		वापस -EBUSY;
	dev->stream_sliced_vbi_cap = false;
	dev->vbi_cap_dev.queue->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	वापस 0;
पूर्ण

व्योम vivid_fill_service_lines(काष्ठा v4l2_sliced_vbi_क्रमmat *vbi, u32 service_set)
अणु
	vbi->io_size = माप(काष्ठा v4l2_sliced_vbi_data) * 36;
	vbi->service_set = service_set;
	स_रखो(vbi->service_lines, 0, माप(vbi->service_lines));
	स_रखो(vbi->reserved, 0, माप(vbi->reserved));

	अगर (vbi->service_set == 0)
		वापस;

	अगर (vbi->service_set & V4L2_SLICED_CAPTION_525) अणु
		vbi->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
		vbi->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	पूर्ण
	अगर (vbi->service_set & V4L2_SLICED_WSS_625) अणु
		अचिन्हित i;

		क्रम (i = 7; i <= 18; i++)
			vbi->service_lines[0][i] =
			vbi->service_lines[1][i] = V4L2_SLICED_TELETEXT_B;
		vbi->service_lines[0][23] = V4L2_SLICED_WSS_625;
	पूर्ण
पूर्ण

पूर्णांक vidioc_g_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbi = &fmt->fmt.sliced;

	अगर (!vivid_is_sdtv_cap(dev) || !dev->has_sliced_vbi_cap)
		वापस -EINVAL;

	vivid_fill_service_lines(vbi, dev->service_set_cap);
	वापस 0;
पूर्ण

पूर्णांक vidioc_try_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbi = &fmt->fmt.sliced;
	bool is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;
	u32 service_set = vbi->service_set;

	अगर (!vivid_is_sdtv_cap(dev) || !dev->has_sliced_vbi_cap)
		वापस -EINVAL;

	service_set &= is_60hz ? V4L2_SLICED_CAPTION_525 :
				 V4L2_SLICED_WSS_625 | V4L2_SLICED_TELETEXT_B;
	vivid_fill_service_lines(vbi, service_set);
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbi = &fmt->fmt.sliced;
	पूर्णांक ret = vidioc_try_fmt_sliced_vbi_cap(file, fh, fmt);

	अगर (ret)
		वापस ret;
	अगर (!dev->stream_sliced_vbi_cap && vb2_is_busy(&dev->vb_vbi_cap_q))
		वापस -EBUSY;
	dev->service_set_cap = vbi->service_set;
	dev->stream_sliced_vbi_cap = true;
	dev->vbi_cap_dev.queue->type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_sliced_vbi_cap *cap)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);
	bool is_60hz;

	अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
		is_60hz = dev->std_cap[dev->input] & V4L2_STD_525_60;
		अगर (!vivid_is_sdtv_cap(dev) || !dev->has_sliced_vbi_cap ||
		    cap->type != V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		is_60hz = dev->std_out & V4L2_STD_525_60;
		अगर (!vivid_is_svid_out(dev) || !dev->has_sliced_vbi_out ||
		    cap->type != V4L2_BUF_TYPE_SLICED_VBI_OUTPUT)
			वापस -EINVAL;
	पूर्ण

	cap->service_set = is_60hz ? V4L2_SLICED_CAPTION_525 :
				     V4L2_SLICED_WSS_625 | V4L2_SLICED_TELETEXT_B;
	अगर (is_60hz) अणु
		cap->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
		cap->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	पूर्ण अन्यथा अणु
		अचिन्हित i;

		क्रम (i = 7; i <= 18; i++)
			cap->service_lines[0][i] =
			cap->service_lines[1][i] = V4L2_SLICED_TELETEXT_B;
		cap->service_lines[0][23] = V4L2_SLICED_WSS_625;
	पूर्ण
	वापस 0;
पूर्ण
