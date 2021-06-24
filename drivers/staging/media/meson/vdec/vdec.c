<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-dev.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "vdec.h"
#समावेश "esparser.h"
#समावेश "vdec_helpers.h"

काष्ठा dummy_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

/* 16 MiB क्रम parsed bitstream swap exchange */
#घोषणा SIZE_VIFIFO SZ_16M

अटल u32 get_output_size(u32 width, u32 height)
अणु
	वापस ALIGN(width * height, SZ_64K);
पूर्ण

u32 amvdec_get_output_size(काष्ठा amvdec_session *sess)
अणु
	वापस get_output_size(sess->width, sess->height);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_get_output_size);

अटल पूर्णांक vdec_codec_needs_recycle(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	वापस codec_ops->can_recycle && codec_ops->recycle;
पूर्ण

अटल पूर्णांक vdec_recycle_thपढ़ो(व्योम *data)
अणु
	काष्ठा amvdec_session *sess = data;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	काष्ठा amvdec_buffer *पंचांगp, *n;

	जबतक (!kthपढ़ो_should_stop()) अणु
		mutex_lock(&sess->bufs_recycle_lock);
		list_क्रम_each_entry_safe(पंचांगp, n, &sess->bufs_recycle, list) अणु
			अगर (!codec_ops->can_recycle(core))
				अवरोध;

			codec_ops->recycle(core, पंचांगp->vb->index);
			list_del(&पंचांगp->list);
			kमुक्त(पंचांगp);
		पूर्ण
		mutex_unlock(&sess->bufs_recycle_lock);

		usleep_range(5000, 10000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_घातeron(काष्ठा amvdec_session *sess)
अणु
	पूर्णांक ret;
	काष्ठा amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;

	ret = clk_prepare_enable(sess->core->करोs_parser_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(sess->core->करोs_clk);
	अगर (ret)
		जाओ disable_करोs_parser;

	ret = vdec_ops->start(sess);
	अगर (ret)
		जाओ disable_करोs;

	esparser_घातer_up(sess);

	वापस 0;

disable_करोs:
	clk_disable_unprepare(sess->core->करोs_clk);
disable_करोs_parser:
	clk_disable_unprepare(sess->core->करोs_parser_clk);

	वापस ret;
पूर्ण

अटल व्योम vdec_रुको_inactive(काष्ठा amvdec_session *sess)
अणु
	/* We consider 50ms with no IRQ to be inactive. */
	जबतक (समय_is_after_jअगरfies64(sess->last_irq_jअगरfies +
				       msecs_to_jअगरfies(50)))
		msleep(25);
पूर्ण

अटल व्योम vdec_घातeroff(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	sess->should_stop = 1;
	vdec_रुको_inactive(sess);
	अगर (codec_ops->drain)
		codec_ops->drain(sess);

	vdec_ops->stop(sess);
	clk_disable_unprepare(sess->core->करोs_clk);
	clk_disable_unprepare(sess->core->करोs_parser_clk);
पूर्ण

अटल व्योम
vdec_queue_recycle(काष्ठा amvdec_session *sess, काष्ठा vb2_buffer *vb)
अणु
	काष्ठा amvdec_buffer *new_buf;

	new_buf = kदो_स्मृति(माप(*new_buf), GFP_KERNEL);
	अगर (!new_buf)
		वापस;
	new_buf->vb = vb;

	mutex_lock(&sess->bufs_recycle_lock);
	list_add_tail(&new_buf->list, &sess->bufs_recycle);
	mutex_unlock(&sess->bufs_recycle_lock);
पूर्ण

अटल व्योम vdec_m2m_device_run(व्योम *priv)
अणु
	काष्ठा amvdec_session *sess = priv;

	schedule_work(&sess->esparser_queue_work);
पूर्ण

अटल व्योम vdec_m2m_job_पात(व्योम *priv)
अणु
	काष्ठा amvdec_session *sess = priv;

	v4l2_m2m_job_finish(sess->m2m_dev, sess->m2m_ctx);
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops vdec_m2m_ops = अणु
	.device_run = vdec_m2m_device_run,
	.job_पात = vdec_m2m_job_पात,
पूर्ण;

अटल व्योम process_num_buffers(काष्ठा vb2_queue *q,
				काष्ठा amvdec_session *sess,
				अचिन्हित पूर्णांक *num_buffers,
				bool is_reqbufs)
अणु
	स्थिर काष्ठा amvdec_क्रमmat *fmt_out = sess->fmt_out;
	अचिन्हित पूर्णांक buffers_total = q->num_buffers + *num_buffers;
	u32 min_buf_capture = v4l2_ctrl_g_ctrl(sess->ctrl_min_buf_capture);

	अगर (q->num_buffers + *num_buffers < min_buf_capture)
		*num_buffers = min_buf_capture - q->num_buffers;
	अगर (is_reqbufs && buffers_total < fmt_out->min_buffers)
		*num_buffers = fmt_out->min_buffers - q->num_buffers;
	अगर (buffers_total > fmt_out->max_buffers)
		*num_buffers = fmt_out->max_buffers - q->num_buffers;

	/* We need to program the complete CAPTURE buffer list
	 * in रेजिस्टरs during start_streaming, and the firmwares
	 * are मुक्त to choose any of them to ग_लिखो frames to. As such,
	 * we need all of them to be queued पूर्णांकo the driver
	 */
	sess->num_dst_bufs = q->num_buffers + *num_buffers;
	q->min_buffers_needed = max(fmt_out->min_buffers, sess->num_dst_bufs);
पूर्ण

अटल पूर्णांक vdec_queue_setup(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक *num_buffers,
			    अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
			    काष्ठा device *alloc_devs[])
अणु
	काष्ठा amvdec_session *sess = vb2_get_drv_priv(q);
	u32 output_size = amvdec_get_output_size(sess);

	अगर (*num_planes) अणु
		चयन (q->type) अणु
		हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
			अगर (*num_planes != 1 ||
			    sizes[0] < sess->src_buffer_size)
				वापस -EINVAL;
			अवरोध;
		हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
			चयन (sess->pixfmt_cap) अणु
			हाल V4L2_PIX_FMT_NV12M:
				अगर (*num_planes != 2 ||
				    sizes[0] < output_size ||
				    sizes[1] < output_size / 2)
					वापस -EINVAL;
				अवरोध;
			हाल V4L2_PIX_FMT_YUV420M:
				अगर (*num_planes != 3 ||
				    sizes[0] < output_size ||
				    sizes[1] < output_size / 4 ||
				    sizes[2] < output_size / 4)
					वापस -EINVAL;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			process_num_buffers(q, sess, num_buffers, false);
			अवरोध;
		पूर्ण

		वापस 0;
	पूर्ण

	चयन (q->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		sizes[0] = sess->src_buffer_size;
		*num_planes = 1;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		चयन (sess->pixfmt_cap) अणु
		हाल V4L2_PIX_FMT_NV12M:
			sizes[0] = output_size;
			sizes[1] = output_size / 2;
			*num_planes = 2;
			अवरोध;
		हाल V4L2_PIX_FMT_YUV420M:
			sizes[0] = output_size;
			sizes[1] = output_size / 4;
			sizes[2] = output_size / 4;
			*num_planes = 3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		process_num_buffers(q, sess, num_buffers, true);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sess->changed_क्रमmat = 1;
	वापस 0;
पूर्ण

अटल व्योम vdec_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा amvdec_session *sess = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा v4l2_m2m_ctx *m2m_ctx = sess->m2m_ctx;

	v4l2_m2m_buf_queue(m2m_ctx, vbuf);

	अगर (!sess->streamon_out)
		वापस;

	अगर (sess->streamon_cap &&
	    vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    vdec_codec_needs_recycle(sess))
		vdec_queue_recycle(sess, vb);

	schedule_work(&sess->esparser_queue_work);
पूर्ण

अटल पूर्णांक vdec_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा amvdec_session *sess = vb2_get_drv_priv(q);
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा vb2_v4l2_buffer *buf;
	पूर्णांक ret;

	अगर (core->cur_sess && core->cur_sess != sess) अणु
		ret = -EBUSY;
		जाओ bufs_करोne;
	पूर्ण

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		sess->streamon_out = 1;
	अन्यथा
		sess->streamon_cap = 1;

	अगर (!sess->streamon_out)
		वापस 0;

	अगर (sess->status == STATUS_NEEDS_RESUME &&
	    q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    sess->changed_क्रमmat) अणु
		codec_ops->resume(sess);
		sess->status = STATUS_RUNNING;
		वापस 0;
	पूर्ण

	अगर (sess->status == STATUS_RUNNING ||
	    sess->status == STATUS_NEEDS_RESUME ||
	    sess->status == STATUS_INIT)
		वापस 0;

	sess->vअगरअगरo_size = SIZE_VIFIFO;
	sess->vअगरअगरo_vaddr =
		dma_alloc_coherent(sess->core->dev, sess->vअगरअगरo_size,
				   &sess->vअगरअगरo_paddr, GFP_KERNEL);
	अगर (!sess->vअगरअगरo_vaddr) अणु
		dev_err(sess->core->dev, "Failed to request VIFIFO buffer\n");
		ret = -ENOMEM;
		जाओ bufs_करोne;
	पूर्ण

	sess->should_stop = 0;
	sess->keyframe_found = 0;
	sess->last_offset = 0;
	sess->wrap_count = 0;
	sess->pixelaspect.numerator = 1;
	sess->pixelaspect.denominator = 1;
	atomic_set(&sess->esparser_queued_bufs, 0);
	v4l2_ctrl_s_ctrl(sess->ctrl_min_buf_capture, 1);

	ret = vdec_घातeron(sess);
	अगर (ret)
		जाओ vअगरअगरo_मुक्त;

	sess->sequence_cap = 0;
	sess->sequence_out = 0;
	अगर (vdec_codec_needs_recycle(sess))
		sess->recycle_thपढ़ो = kthपढ़ो_run(vdec_recycle_thपढ़ो, sess,
						   "vdec_recycle");

	sess->status = STATUS_INIT;
	core->cur_sess = sess;
	schedule_work(&sess->esparser_queue_work);
	वापस 0;

vअगरअगरo_मुक्त:
	dma_मुक्त_coherent(sess->core->dev, sess->vअगरअगरo_size,
			  sess->vअगरअगरo_vaddr, sess->vअगरअगरo_paddr);
bufs_करोne:
	जबतक ((buf = v4l2_m2m_src_buf_हटाओ(sess->m2m_ctx)))
		v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
	जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(sess->m2m_ctx)))
		v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		sess->streamon_out = 0;
	अन्यथा
		sess->streamon_cap = 0;

	वापस ret;
पूर्ण

अटल व्योम vdec_मुक्त_canvas(काष्ठा amvdec_session *sess)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sess->canvas_num; ++i)
		meson_canvas_मुक्त(sess->core->canvas, sess->canvas_alloc[i]);

	sess->canvas_num = 0;
पूर्ण

अटल व्योम vdec_reset_बारtamps(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_बारtamp *पंचांगp, *n;

	list_क्रम_each_entry_safe(पंचांगp, n, &sess->बारtamps, list) अणु
		list_del(&पंचांगp->list);
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम vdec_reset_bufs_recycle(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_buffer *पंचांगp, *n;

	list_क्रम_each_entry_safe(पंचांगp, n, &sess->bufs_recycle, list) अणु
		list_del(&पंचांगp->list);
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम vdec_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा amvdec_session *sess = vb2_get_drv_priv(q);
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा vb2_v4l2_buffer *buf;

	अगर (sess->status == STATUS_RUNNING ||
	    sess->status == STATUS_INIT ||
	    (sess->status == STATUS_NEEDS_RESUME &&
	     (!sess->streamon_out || !sess->streamon_cap))) अणु
		अगर (vdec_codec_needs_recycle(sess))
			kthपढ़ो_stop(sess->recycle_thपढ़ो);

		vdec_घातeroff(sess);
		vdec_मुक्त_canvas(sess);
		dma_मुक्त_coherent(sess->core->dev, sess->vअगरअगरo_size,
				  sess->vअगरअगरo_vaddr, sess->vअगरअगरo_paddr);
		vdec_reset_बारtamps(sess);
		vdec_reset_bufs_recycle(sess);
		kमुक्त(sess->priv);
		sess->priv = शून्य;
		core->cur_sess = शून्य;
		sess->status = STATUS_STOPPED;
	पूर्ण

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		जबतक ((buf = v4l2_m2m_src_buf_हटाओ(sess->m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);

		sess->streamon_out = 0;
	पूर्ण अन्यथा अणु
		/* Drain reमुख्यing refs अगर was still running */
		अगर (sess->status >= STATUS_RUNNING && codec_ops->drain)
			codec_ops->drain(sess);

		जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(sess->m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);

		sess->streamon_cap = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक vdec_vb2_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops vdec_vb2_ops = अणु
	.queue_setup = vdec_queue_setup,
	.start_streaming = vdec_start_streaming,
	.stop_streaming = vdec_stop_streaming,
	.buf_queue = vdec_vb2_buf_queue,
	.buf_prepare = vdec_vb2_buf_prepare,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक
vdec_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "meson-vdec", माप(cap->driver));
	strscpy(cap->card, "Amlogic Video Decoder", माप(cap->card));
	strscpy(cap->bus_info, "platform:meson-vdec", माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amvdec_क्रमmat *
find_क्रमmat(स्थिर काष्ठा amvdec_क्रमmat *fmts, u32 size, u32 pixfmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (fmts[i].pixfmt == pixfmt)
			वापस &fmts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक
vdec_supports_pixfmt_cap(स्थिर काष्ठा amvdec_क्रमmat *fmt_out, u32 pixfmt_cap)
अणु
	पूर्णांक i;

	क्रम (i = 0; fmt_out->pixfmts_cap[i]; i++)
		अगर (fmt_out->pixfmts_cap[i] == pixfmt_cap)
			वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amvdec_क्रमmat *
vdec_try_fmt_common(काष्ठा amvdec_session *sess, u32 size,
		    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *pfmt = pixmp->plane_fmt;
	स्थिर काष्ठा amvdec_क्रमmat *fmts = sess->core->platक्रमm->क्रमmats;
	स्थिर काष्ठा amvdec_क्रमmat *fmt_out = शून्य;
	u32 output_size = 0;

	स_रखो(pfmt[0].reserved, 0, माप(pfmt[0].reserved));
	स_रखो(pixmp->reserved, 0, माप(pixmp->reserved));

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		fmt_out = find_क्रमmat(fmts, size, pixmp->pixelक्रमmat);
		अगर (!fmt_out) अणु
			pixmp->pixelक्रमmat = V4L2_PIX_FMT_MPEG2;
			fmt_out = find_क्रमmat(fmts, size, pixmp->pixelक्रमmat);
		पूर्ण
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		fmt_out = sess->fmt_out;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	pixmp->width  = clamp(pixmp->width,  (u32)256, fmt_out->max_width);
	pixmp->height = clamp(pixmp->height, (u32)144, fmt_out->max_height);
	output_size = get_output_size(pixmp->width, pixmp->height);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (!pfmt[0].sizeimage)
			pfmt[0].sizeimage = sess->src_buffer_size;
		pfmt[0].bytesperline = 0;
		pixmp->num_planes = 1;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		fmt_out = sess->fmt_out;
		अगर (!vdec_supports_pixfmt_cap(fmt_out, pixmp->pixelक्रमmat))
			pixmp->pixelक्रमmat = fmt_out->pixfmts_cap[0];

		स_रखो(pfmt[1].reserved, 0, माप(pfmt[1].reserved));
		अगर (pixmp->pixelक्रमmat == V4L2_PIX_FMT_NV12M) अणु
			pfmt[0].sizeimage = output_size;
			pfmt[0].bytesperline = ALIGN(pixmp->width, 32);

			pfmt[1].sizeimage = output_size / 2;
			pfmt[1].bytesperline = ALIGN(pixmp->width, 32);
			pixmp->num_planes = 2;
		पूर्ण अन्यथा अगर (pixmp->pixelक्रमmat == V4L2_PIX_FMT_YUV420M) अणु
			pfmt[0].sizeimage = output_size;
			pfmt[0].bytesperline = ALIGN(pixmp->width, 32);

			pfmt[1].sizeimage = output_size / 4;
			pfmt[1].bytesperline = ALIGN(pixmp->width, 32) / 2;

			pfmt[2].sizeimage = output_size / 2;
			pfmt[2].bytesperline = ALIGN(pixmp->width, 32) / 2;
			pixmp->num_planes = 3;
		पूर्ण
	पूर्ण

	अगर (pixmp->field == V4L2_FIELD_ANY)
		pixmp->field = V4L2_FIELD_NONE;

	वापस fmt_out;
पूर्ण

अटल पूर्णांक vdec_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);

	vdec_try_fmt_common(sess, sess->core->platक्रमm->num_क्रमmats, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_g_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		pixmp->pixelक्रमmat = sess->pixfmt_cap;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		pixmp->pixelक्रमmat = sess->fmt_out->pixfmt;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		pixmp->width = sess->width;
		pixmp->height = sess->height;
		pixmp->colorspace = sess->colorspace;
		pixmp->ycbcr_enc = sess->ycbcr_enc;
		pixmp->quantization = sess->quantization;
		pixmp->xfer_func = sess->xfer_func;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		pixmp->width = sess->width;
		pixmp->height = sess->height;
	पूर्ण

	vdec_try_fmt_common(sess, sess->core->platक्रमm->num_क्रमmats, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);
	काष्ठा v4l2_pix_क्रमmat_mplane *pixmp = &f->fmt.pix_mp;
	u32 num_क्रमmats = sess->core->platक्रमm->num_क्रमmats;
	स्थिर काष्ठा amvdec_क्रमmat *fmt_out;
	काष्ठा v4l2_pix_क्रमmat_mplane orig_pixmp;
	काष्ठा v4l2_क्रमmat क्रमmat;
	u32 pixfmt_out = 0, pixfmt_cap = 0;

	orig_pixmp = *pixmp;

	fmt_out = vdec_try_fmt_common(sess, num_क्रमmats, f);
	अगर (!fmt_out)
		वापस -EINVAL;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		pixfmt_out = pixmp->pixelक्रमmat;
		pixfmt_cap = sess->pixfmt_cap;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		pixfmt_cap = pixmp->pixelक्रमmat;
		pixfmt_out = sess->fmt_out->pixfmt;
	पूर्ण

	स_रखो(&क्रमmat, 0, माप(क्रमmat));

	क्रमmat.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	क्रमmat.fmt.pix_mp.pixelक्रमmat = pixfmt_out;
	क्रमmat.fmt.pix_mp.width = orig_pixmp.width;
	क्रमmat.fmt.pix_mp.height = orig_pixmp.height;
	vdec_try_fmt_common(sess, num_क्रमmats, &क्रमmat);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		sess->width = क्रमmat.fmt.pix_mp.width;
		sess->height = क्रमmat.fmt.pix_mp.height;
		sess->colorspace = pixmp->colorspace;
		sess->ycbcr_enc = pixmp->ycbcr_enc;
		sess->quantization = pixmp->quantization;
		sess->xfer_func = pixmp->xfer_func;
		sess->src_buffer_size = pixmp->plane_fmt[0].sizeimage;
	पूर्ण

	स_रखो(&क्रमmat, 0, माप(क्रमmat));

	क्रमmat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	क्रमmat.fmt.pix_mp.pixelक्रमmat = pixfmt_cap;
	क्रमmat.fmt.pix_mp.width = orig_pixmp.width;
	क्रमmat.fmt.pix_mp.height = orig_pixmp.height;
	vdec_try_fmt_common(sess, num_क्रमmats, &क्रमmat);

	sess->width = क्रमmat.fmt.pix_mp.width;
	sess->height = क्रमmat.fmt.pix_mp.height;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		sess->fmt_out = fmt_out;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		sess->pixfmt_cap = क्रमmat.fmt.pix_mp.pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_क्रमागत_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);
	स्थिर काष्ठा vdec_platक्रमm *platक्रमm = sess->core->platक्रमm;
	स्थिर काष्ठा amvdec_क्रमmat *fmt_out;

	स_रखो(f->reserved, 0, माप(f->reserved));

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (f->index >= platक्रमm->num_क्रमmats)
			वापस -EINVAL;

		fmt_out = &platक्रमm->क्रमmats[f->index];
		f->pixelक्रमmat = fmt_out->pixfmt;
		f->flags = fmt_out->flags;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		fmt_out = sess->fmt_out;
		अगर (f->index >= 4 || !fmt_out->pixfmts_cap[f->index])
			वापस -EINVAL;

		f->pixelक्रमmat = fmt_out->pixfmts_cap[f->index];
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);
	स्थिर काष्ठा amvdec_क्रमmat *क्रमmats = sess->core->platक्रमm->क्रमmats;
	स्थिर काष्ठा amvdec_क्रमmat *fmt;
	u32 num_क्रमmats = sess->core->platक्रमm->num_क्रमmats;

	fmt = find_क्रमmat(क्रमmats, num_क्रमmats, fsize->pixel_क्रमmat);
	अगर (!fmt || fsize->index)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;

	fsize->stepwise.min_width = 256;
	fsize->stepwise.max_width = fmt->max_width;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = 144;
	fsize->stepwise.max_height = fmt->max_height;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
vdec_decoder_cmd(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_decoder_cmd *cmd)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	काष्ठा device *dev = sess->core->dev;
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_try_decoder_cmd(file, fh, cmd);
	अगर (ret)
		वापस ret;

	अगर (!(sess->streamon_out & sess->streamon_cap))
		वापस 0;

	अगर (cmd->cmd == V4L2_DEC_CMD_START) अणु
		v4l2_m2m_clear_state(sess->m2m_ctx);
		sess->should_stop = 0;
		वापस 0;
	पूर्ण

	/* Should not happen */
	अगर (cmd->cmd != V4L2_DEC_CMD_STOP)
		वापस -EINVAL;

	dev_dbg(dev, "Received V4L2_DEC_CMD_STOP\n");

	sess->should_stop = 1;

	v4l2_m2m_mark_stopped(sess->m2m_ctx);

	अगर (codec_ops->drain) अणु
		vdec_रुको_inactive(sess);
		codec_ops->drain(sess);
	पूर्ण अन्यथा अगर (codec_ops->eos_sequence) अणु
		u32 len;
		स्थिर u8 *data = codec_ops->eos_sequence(&len);

		esparser_queue_eos(sess->core, data, len);
		vdec_रुको_inactive(sess);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vdec_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vdec_g_pixelaspect(काष्ठा file *file, व्योम *fh, पूर्णांक type,
			      काष्ठा v4l2_fract *f)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;

	*f = sess->pixelaspect;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops vdec_ioctl_ops = अणु
	.vidioc_querycap = vdec_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vdec_क्रमागत_fmt,
	.vidioc_क्रमागत_fmt_vid_out = vdec_क्रमागत_fmt,
	.vidioc_s_fmt_vid_cap_mplane = vdec_s_fmt,
	.vidioc_s_fmt_vid_out_mplane = vdec_s_fmt,
	.vidioc_g_fmt_vid_cap_mplane = vdec_g_fmt,
	.vidioc_g_fmt_vid_out_mplane = vdec_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane = vdec_try_fmt,
	.vidioc_try_fmt_vid_out_mplane = vdec_try_fmt,
	.vidioc_reqbufs = v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf = v4l2_m2m_ioctl_querybuf,
	.vidioc_prepare_buf = v4l2_m2m_ioctl_prepare_buf,
	.vidioc_qbuf = v4l2_m2m_ioctl_qbuf,
	.vidioc_expbuf = v4l2_m2m_ioctl_expbuf,
	.vidioc_dqbuf = v4l2_m2m_ioctl_dqbuf,
	.vidioc_create_bufs = v4l2_m2m_ioctl_create_bufs,
	.vidioc_streamon = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff = v4l2_m2m_ioctl_streamoff,
	.vidioc_क्रमागत_framesizes = vdec_क्रमागत_framesizes,
	.vidioc_subscribe_event = vdec_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_try_decoder_cmd = v4l2_m2m_ioctl_try_decoder_cmd,
	.vidioc_decoder_cmd = vdec_decoder_cmd,
	.vidioc_g_pixelaspect = vdec_g_pixelaspect,
पूर्ण;

अटल पूर्णांक m2m_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा amvdec_session *sess = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->ops = &vdec_vb2_ops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->drv_priv = sess;
	src_vq->buf_काष्ठा_size = माप(काष्ठा dummy_buf);
	src_vq->min_buffers_needed = 1;
	src_vq->dev = sess->core->dev;
	src_vq->lock = &sess->lock;
	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->ops = &vdec_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->drv_priv = sess;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा dummy_buf);
	dst_vq->min_buffers_needed = 1;
	dst_vq->dev = sess->core->dev;
	dst_vq->lock = &sess->lock;
	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक vdec_init_ctrls(काष्ठा amvdec_session *sess)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_handler = &sess->ctrl_handler;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(ctrl_handler, 1);
	अगर (ret)
		वापस ret;

	sess->ctrl_min_buf_capture =
		v4l2_ctrl_new_std(ctrl_handler, शून्य,
				  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE, 1, 32, 1,
				  1);

	ret = ctrl_handler->error;
	अगर (ret) अणु
		v4l2_ctrl_handler_मुक्त(ctrl_handler);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_खोलो(काष्ठा file *file)
अणु
	काष्ठा amvdec_core *core = video_drvdata(file);
	काष्ठा device *dev = core->dev;
	स्थिर काष्ठा amvdec_क्रमmat *क्रमmats = core->platक्रमm->क्रमmats;
	काष्ठा amvdec_session *sess;
	पूर्णांक ret;

	sess = kzalloc(माप(*sess), GFP_KERNEL);
	अगर (!sess)
		वापस -ENOMEM;

	sess->core = core;

	sess->m2m_dev = v4l2_m2m_init(&vdec_m2m_ops);
	अगर (IS_ERR(sess->m2m_dev)) अणु
		dev_err(dev, "Fail to v4l2_m2m_init\n");
		ret = PTR_ERR(sess->m2m_dev);
		जाओ err_मुक्त_sess;
	पूर्ण

	sess->m2m_ctx = v4l2_m2m_ctx_init(sess->m2m_dev, sess, m2m_queue_init);
	अगर (IS_ERR(sess->m2m_ctx)) अणु
		dev_err(dev, "Fail to v4l2_m2m_ctx_init\n");
		ret = PTR_ERR(sess->m2m_ctx);
		जाओ err_m2m_release;
	पूर्ण

	ret = vdec_init_ctrls(sess);
	अगर (ret)
		जाओ err_m2m_release;

	sess->pixfmt_cap = क्रमmats[0].pixfmts_cap[0];
	sess->fmt_out = &क्रमmats[0];
	sess->width = 1280;
	sess->height = 720;
	sess->pixelaspect.numerator = 1;
	sess->pixelaspect.denominator = 1;
	sess->src_buffer_size = SZ_1M;

	INIT_LIST_HEAD(&sess->बारtamps);
	INIT_LIST_HEAD(&sess->bufs_recycle);
	INIT_WORK(&sess->esparser_queue_work, esparser_queue_all_src);
	mutex_init(&sess->lock);
	mutex_init(&sess->bufs_recycle_lock);
	spin_lock_init(&sess->ts_spinlock);

	v4l2_fh_init(&sess->fh, core->vdev_dec);
	sess->fh.ctrl_handler = &sess->ctrl_handler;
	v4l2_fh_add(&sess->fh);
	sess->fh.m2m_ctx = sess->m2m_ctx;
	file->निजी_data = &sess->fh;

	वापस 0;

err_m2m_release:
	v4l2_m2m_release(sess->m2m_dev);
err_मुक्त_sess:
	kमुक्त(sess);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_बंद(काष्ठा file *file)
अणु
	काष्ठा amvdec_session *sess =
		container_of(file->निजी_data, काष्ठा amvdec_session, fh);

	v4l2_m2m_ctx_release(sess->m2m_ctx);
	v4l2_m2m_release(sess->m2m_dev);
	v4l2_fh_del(&sess->fh);
	v4l2_fh_निकास(&sess->fh);

	mutex_destroy(&sess->lock);
	mutex_destroy(&sess->bufs_recycle_lock);

	kमुक्त(sess);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vdec_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = vdec_खोलो,
	.release = vdec_बंद,
	.unlocked_ioctl = video_ioctl2,
	.poll = v4l2_m2m_fop_poll,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल irqवापस_t vdec_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा amvdec_core *core = data;
	काष्ठा amvdec_session *sess = core->cur_sess;

	sess->last_irq_jअगरfies = get_jअगरfies_64();

	वापस sess->fmt_out->codec_ops->isr(sess);
पूर्ण

अटल irqवापस_t vdec_thपढ़ोed_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा amvdec_core *core = data;
	काष्ठा amvdec_session *sess = core->cur_sess;

	वापस sess->fmt_out->codec_ops->thपढ़ोed_isr(sess);
पूर्ण

अटल स्थिर काष्ठा of_device_id vdec_dt_match[] = अणु
	अणु .compatible = "amlogic,gxbb-vdec",
	  .data = &vdec_platक्रमm_gxbb पूर्ण,
	अणु .compatible = "amlogic,gxm-vdec",
	  .data = &vdec_platक्रमm_gxm पूर्ण,
	अणु .compatible = "amlogic,gxl-vdec",
	  .data = &vdec_platक्रमm_gxl पूर्ण,
	अणु .compatible = "amlogic,g12a-vdec",
	  .data = &vdec_platक्रमm_g12a पूर्ण,
	अणु .compatible = "amlogic,sm1-vdec",
	  .data = &vdec_platक्रमm_sm1 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vdec_dt_match);

अटल पूर्णांक vdec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा video_device *vdev;
	काष्ठा amvdec_core *core;
	काष्ठा resource *r;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक irq;
	पूर्णांक ret;

	core = devm_kzalloc(dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	core->dev = dev;
	platक्रमm_set_drvdata(pdev, core);

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dos");
	core->करोs_base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(core->करोs_base))
		वापस PTR_ERR(core->करोs_base);

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "esparser");
	core->esparser_base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(core->esparser_base))
		वापस PTR_ERR(core->esparser_base);

	core->regmap_ao =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"amlogic,ao-sysctrl");
	अगर (IS_ERR(core->regmap_ao)) अणु
		dev_err(dev, "Couldn't regmap AO sysctrl\n");
		वापस PTR_ERR(core->regmap_ao);
	पूर्ण

	core->canvas = meson_canvas_get(dev);
	अगर (IS_ERR(core->canvas))
		वापस PTR_ERR(core->canvas);

	of_id = of_match_node(vdec_dt_match, dev->of_node);
	core->platक्रमm = of_id->data;

	अगर (core->platक्रमm->revision == VDEC_REVISION_G12A ||
	    core->platक्रमm->revision == VDEC_REVISION_SM1) अणु
		core->vdec_hevcf_clk = devm_clk_get(dev, "vdec_hevcf");
		अगर (IS_ERR(core->vdec_hevcf_clk))
			वापस -EPROBE_DEFER;
	पूर्ण

	core->करोs_parser_clk = devm_clk_get(dev, "dos_parser");
	अगर (IS_ERR(core->करोs_parser_clk))
		वापस -EPROBE_DEFER;

	core->करोs_clk = devm_clk_get(dev, "dos");
	अगर (IS_ERR(core->करोs_clk))
		वापस -EPROBE_DEFER;

	core->vdec_1_clk = devm_clk_get(dev, "vdec_1");
	अगर (IS_ERR(core->vdec_1_clk))
		वापस -EPROBE_DEFER;

	core->vdec_hevc_clk = devm_clk_get(dev, "vdec_hevc");
	अगर (IS_ERR(core->vdec_hevc_clk))
		वापस -EPROBE_DEFER;

	irq = platक्रमm_get_irq_byname(pdev, "vdec");
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(core->dev, irq, vdec_isr,
					vdec_thपढ़ोed_isr, IRQF_ONESHOT,
					"vdec", core);
	अगर (ret)
		वापस ret;

	ret = esparser_init(pdev, core);
	अगर (ret)
		वापस ret;

	ret = v4l2_device_रेजिस्टर(dev, &core->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register v4l2 device\n");
		वापस -ENOMEM;
	पूर्ण

	vdev = video_device_alloc();
	अगर (!vdev) अणु
		ret = -ENOMEM;
		जाओ err_vdev_release;
	पूर्ण

	core->vdev_dec = vdev;
	core->dev_dec = dev;
	mutex_init(&core->lock);

	strscpy(vdev->name, "meson-video-decoder", माप(vdev->name));
	vdev->release = video_device_release;
	vdev->fops = &vdec_fops;
	vdev->ioctl_ops = &vdec_ioctl_ops;
	vdev->vfl_dir = VFL_सूची_M2M;
	vdev->v4l2_dev = &core->v4l2_dev;
	vdev->lock = &core->lock;
	vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;

	video_set_drvdata(vdev, core);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed registering video device\n");
		जाओ err_vdev_release;
	पूर्ण

	वापस 0;

err_vdev_release:
	video_device_release(vdev);
	वापस ret;
पूर्ण

अटल पूर्णांक vdec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amvdec_core *core = platक्रमm_get_drvdata(pdev);

	video_unरेजिस्टर_device(core->vdev_dec);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver meson_vdec_driver = अणु
	.probe = vdec_probe,
	.हटाओ = vdec_हटाओ,
	.driver = अणु
		.name = "meson-vdec",
		.of_match_table = vdec_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_vdec_driver);

MODULE_DESCRIPTION("Meson video decoder driver for GXBB/GXL/GXM/G12/SM1");
MODULE_AUTHOR("Maxime Jourdan <mjourdan@baylibre.com>");
MODULE_LICENSE("GPL");
