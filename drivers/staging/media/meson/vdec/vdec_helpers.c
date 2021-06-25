<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#समावेश <linux/gcd.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "vdec_helpers.h"

#घोषणा NUM_CANVAS_NV12 2
#घोषणा NUM_CANVAS_YUV420 3

u32 amvdec_पढ़ो_करोs(काष्ठा amvdec_core *core, u32 reg)
अणु
	वापस पढ़ोl_relaxed(core->करोs_base + reg);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_पढ़ो_करोs);

व्योम amvdec_ग_लिखो_करोs(काष्ठा amvdec_core *core, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, core->करोs_base + reg);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_ग_लिखो_करोs);

व्योम amvdec_ग_लिखो_करोs_bits(काष्ठा amvdec_core *core, u32 reg, u32 val)
अणु
	amvdec_ग_लिखो_करोs(core, reg, amvdec_पढ़ो_करोs(core, reg) | val);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_ग_लिखो_करोs_bits);

व्योम amvdec_clear_करोs_bits(काष्ठा amvdec_core *core, u32 reg, u32 val)
अणु
	amvdec_ग_लिखो_करोs(core, reg, amvdec_पढ़ो_करोs(core, reg) & ~val);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_clear_करोs_bits);

u32 amvdec_पढ़ो_parser(काष्ठा amvdec_core *core, u32 reg)
अणु
	वापस पढ़ोl_relaxed(core->esparser_base + reg);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_पढ़ो_parser);

व्योम amvdec_ग_लिखो_parser(काष्ठा amvdec_core *core, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, core->esparser_base + reg);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_ग_लिखो_parser);

/* 4 KiB per 64x32 block */
u32 amvdec_am21c_body_size(u32 width, u32 height)
अणु
	u32 width_64 = ALIGN(width, 64) / 64;
	u32 height_32 = ALIGN(height, 32) / 32;

	वापस SZ_4K * width_64 * height_32;
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_am21c_body_size);

/* 32 bytes per 128x64 block */
u32 amvdec_am21c_head_size(u32 width, u32 height)
अणु
	u32 width_128 = ALIGN(width, 128) / 128;
	u32 height_64 = ALIGN(height, 64) / 64;

	वापस 32 * width_128 * height_64;
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_am21c_head_size);

u32 amvdec_am21c_size(u32 width, u32 height)
अणु
	वापस ALIGN(amvdec_am21c_body_size(width, height) +
		     amvdec_am21c_head_size(width, height), SZ_64K);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_am21c_size);

अटल पूर्णांक canvas_alloc(काष्ठा amvdec_session *sess, u8 *canvas_id)
अणु
	पूर्णांक ret;

	अगर (sess->canvas_num >= MAX_CANVAS) अणु
		dev_err(sess->core->dev, "Reached max number of canvas\n");
		वापस -ENOMEM;
	पूर्ण

	ret = meson_canvas_alloc(sess->core->canvas, canvas_id);
	अगर (ret)
		वापस ret;

	sess->canvas_alloc[sess->canvas_num++] = *canvas_id;
	वापस 0;
पूर्ण

अटल पूर्णांक set_canvas_yuv420m(काष्ठा amvdec_session *sess,
			      काष्ठा vb2_buffer *vb, u32 width,
			      u32 height, u32 reg)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u8 canvas_id[NUM_CANVAS_YUV420]; /* Y U V */
	dma_addr_t buf_paddr[NUM_CANVAS_YUV420]; /* Y U V */
	पूर्णांक ret, i;

	क्रम (i = 0; i < NUM_CANVAS_YUV420; ++i) अणु
		ret = canvas_alloc(sess, &canvas_id[i]);
		अगर (ret)
			वापस ret;

		buf_paddr[i] =
		    vb2_dma_contig_plane_dma_addr(vb, i);
	पूर्ण

	/* Y plane */
	meson_canvas_config(core->canvas, canvas_id[0], buf_paddr[0],
			    width, height, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* U plane */
	meson_canvas_config(core->canvas, canvas_id[1], buf_paddr[1],
			    width / 2, height / 2, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* V plane */
	meson_canvas_config(core->canvas, canvas_id[2], buf_paddr[2],
			    width / 2, height / 2, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	amvdec_ग_लिखो_करोs(core, reg,
			 ((canvas_id[2]) << 16) |
			 ((canvas_id[1]) << 8)  |
			 (canvas_id[0]));

	वापस 0;
पूर्ण

अटल पूर्णांक set_canvas_nv12m(काष्ठा amvdec_session *sess,
			    काष्ठा vb2_buffer *vb, u32 width,
			    u32 height, u32 reg)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u8 canvas_id[NUM_CANVAS_NV12]; /* Y U/V */
	dma_addr_t buf_paddr[NUM_CANVAS_NV12]; /* Y U/V */
	पूर्णांक ret, i;

	क्रम (i = 0; i < NUM_CANVAS_NV12; ++i) अणु
		ret = canvas_alloc(sess, &canvas_id[i]);
		अगर (ret)
			वापस ret;

		buf_paddr[i] =
		    vb2_dma_contig_plane_dma_addr(vb, i);
	पूर्ण

	/* Y plane */
	meson_canvas_config(core->canvas, canvas_id[0], buf_paddr[0],
			    width, height, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* U/V plane */
	meson_canvas_config(core->canvas, canvas_id[1], buf_paddr[1],
			    width, height / 2, MESON_CANVAS_WRAP_NONE,
			    MESON_CANVAS_BLKMODE_LINEAR,
			    MESON_CANVAS_ENDIAN_SWAP64);

	amvdec_ग_लिखो_करोs(core, reg,
			 ((canvas_id[1]) << 16) |
			 ((canvas_id[1]) << 8)  |
			 (canvas_id[0]));

	वापस 0;
पूर्ण

पूर्णांक amvdec_set_canvases(काष्ठा amvdec_session *sess,
			u32 reg_base[], u32 reg_num[])
अणु
	काष्ठा v4l2_m2m_buffer *buf;
	u32 pixfmt = sess->pixfmt_cap;
	u32 width = ALIGN(sess->width, 32);
	u32 height = ALIGN(sess->height, 32);
	u32 reg_cur = reg_base[0];
	u32 reg_num_cur = 0;
	u32 reg_base_cur = 0;
	पूर्णांक i = 0;
	पूर्णांक ret;

	v4l2_m2m_क्रम_each_dst_buf(sess->m2m_ctx, buf) अणु
		अगर (!reg_base[reg_base_cur])
			वापस -EINVAL;

		reg_cur = reg_base[reg_base_cur] + reg_num_cur * 4;

		चयन (pixfmt) अणु
		हाल V4L2_PIX_FMT_NV12M:
			ret = set_canvas_nv12m(sess, &buf->vb.vb2_buf, width,
					       height, reg_cur);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल V4L2_PIX_FMT_YUV420M:
			ret = set_canvas_yuv420m(sess, &buf->vb.vb2_buf, width,
						 height, reg_cur);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			dev_err(sess->core->dev, "Unsupported pixfmt %08X\n",
				pixfmt);
			वापस -EINVAL;
		पूर्ण

		reg_num_cur++;
		अगर (reg_num_cur >= reg_num[reg_base_cur]) अणु
			reg_base_cur++;
			reg_num_cur = 0;
		पूर्ण

		sess->fw_idx_to_vb2_idx[i++] = buf->vb.vb2_buf.index;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_set_canvases);

व्योम amvdec_add_ts(काष्ठा amvdec_session *sess, u64 ts,
		   काष्ठा v4l2_समयcode tc, u32 offset, u32 vbuf_flags)
अणु
	काष्ठा amvdec_बारtamp *new_ts;
	अचिन्हित दीर्घ flags;

	new_ts = kzalloc(माप(*new_ts), GFP_KERNEL);
	new_ts->ts = ts;
	new_ts->tc = tc;
	new_ts->offset = offset;
	new_ts->flags = vbuf_flags;

	spin_lock_irqsave(&sess->ts_spinlock, flags);
	list_add_tail(&new_ts->list, &sess->बारtamps);
	spin_unlock_irqrestore(&sess->ts_spinlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_add_ts);

व्योम amvdec_हटाओ_ts(काष्ठा amvdec_session *sess, u64 ts)
अणु
	काष्ठा amvdec_बारtamp *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sess->ts_spinlock, flags);
	list_क्रम_each_entry(पंचांगp, &sess->बारtamps, list) अणु
		अगर (पंचांगp->ts == ts) अणु
			list_del(&पंचांगp->list);
			kमुक्त(पंचांगp);
			जाओ unlock;
		पूर्ण
	पूर्ण
	dev_warn(sess->core->dev_dec,
		 "Couldn't remove buffer with timestamp %llu from list\n", ts);

unlock:
	spin_unlock_irqrestore(&sess->ts_spinlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_हटाओ_ts);

अटल व्योम dst_buf_करोne(काष्ठा amvdec_session *sess,
			 काष्ठा vb2_v4l2_buffer *vbuf,
			 u32 field, u64 बारtamp,
			 काष्ठा v4l2_समयcode समयcode, u32 flags)
अणु
	काष्ठा device *dev = sess->core->dev_dec;
	u32 output_size = amvdec_get_output_size(sess);

	चयन (sess->pixfmt_cap) अणु
	हाल V4L2_PIX_FMT_NV12M:
		vbuf->vb2_buf.planes[0].bytesused = output_size;
		vbuf->vb2_buf.planes[1].bytesused = output_size / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420M:
		vbuf->vb2_buf.planes[0].bytesused = output_size;
		vbuf->vb2_buf.planes[1].bytesused = output_size / 4;
		vbuf->vb2_buf.planes[2].bytesused = output_size / 4;
		अवरोध;
	पूर्ण

	vbuf->vb2_buf.बारtamp = बारtamp;
	vbuf->sequence = sess->sequence_cap++;
	vbuf->flags = flags;
	vbuf->समयcode = समयcode;

	अगर (sess->should_stop &&
	    atomic_पढ़ो(&sess->esparser_queued_bufs) <= 1) अणु
		स्थिर काष्ठा v4l2_event ev = अणु .type = V4L2_EVENT_EOS पूर्ण;

		dev_dbg(dev, "Signaling EOS, sequence_cap = %u\n",
			sess->sequence_cap - 1);
		v4l2_event_queue_fh(&sess->fh, &ev);
		vbuf->flags |= V4L2_BUF_FLAG_LAST;
	पूर्ण अन्यथा अगर (sess->status == STATUS_NEEDS_RESUME) अणु
		/* Mark LAST क्रम drained show frames during a source change */
		vbuf->flags |= V4L2_BUF_FLAG_LAST;
		sess->sequence_cap = 0;
	पूर्ण अन्यथा अगर (sess->should_stop)
		dev_dbg(dev, "should_stop, %u bufs remain\n",
			atomic_पढ़ो(&sess->esparser_queued_bufs));

	dev_dbg(dev, "Buffer %u done, ts = %llu, flags = %08X\n",
		vbuf->vb2_buf.index, बारtamp, flags);
	vbuf->field = field;
	v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_DONE);

	/* Buffer करोne probably means the vअगरअगरo got मुक्तd */
	schedule_work(&sess->esparser_queue_work);
पूर्ण

व्योम amvdec_dst_buf_करोne(काष्ठा amvdec_session *sess,
			 काष्ठा vb2_v4l2_buffer *vbuf, u32 field)
अणु
	काष्ठा device *dev = sess->core->dev_dec;
	काष्ठा amvdec_बारtamp *पंचांगp;
	काष्ठा list_head *बारtamps = &sess->बारtamps;
	काष्ठा v4l2_समयcode समयcode;
	u64 बारtamp;
	u32 vbuf_flags;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sess->ts_spinlock, flags);
	अगर (list_empty(बारtamps)) अणु
		dev_err(dev, "Buffer %u done but list is empty\n",
			vbuf->vb2_buf.index);

		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&sess->ts_spinlock, flags);
		वापस;
	पूर्ण

	पंचांगp = list_first_entry(बारtamps, काष्ठा amvdec_बारtamp, list);
	बारtamp = पंचांगp->ts;
	समयcode = पंचांगp->tc;
	vbuf_flags = पंचांगp->flags;
	list_del(&पंचांगp->list);
	kमुक्त(पंचांगp);
	spin_unlock_irqrestore(&sess->ts_spinlock, flags);

	dst_buf_करोne(sess, vbuf, field, बारtamp, समयcode, vbuf_flags);
	atomic_dec(&sess->esparser_queued_bufs);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_dst_buf_करोne);

व्योम amvdec_dst_buf_करोne_offset(काष्ठा amvdec_session *sess,
				काष्ठा vb2_v4l2_buffer *vbuf,
				u32 offset, u32 field, bool allow_drop)
अणु
	काष्ठा device *dev = sess->core->dev_dec;
	काष्ठा amvdec_बारtamp *match = शून्य;
	काष्ठा amvdec_बारtamp *पंचांगp, *n;
	काष्ठा v4l2_समयcode समयcode = अणु 0 पूर्ण;
	u64 बारtamp = 0;
	u32 vbuf_flags = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sess->ts_spinlock, flags);

	/* Look क्रम our vअगरअगरo offset to get the corresponding बारtamp. */
	list_क्रम_each_entry_safe(पंचांगp, n, &sess->बारtamps, list) अणु
		अगर (पंचांगp->offset > offset) अणु
			/*
			 * Delete any record that reमुख्यed unused क्रम 32 match
			 * checks
			 */
			अगर (पंचांगp->used_count++ >= 32) अणु
				list_del(&पंचांगp->list);
				kमुक्त(पंचांगp);
			पूर्ण
			अवरोध;
		पूर्ण

		match = पंचांगp;
	पूर्ण

	अगर (!match) अणु
		dev_err(dev, "Buffer %u done but can't match offset (%08X)\n",
			vbuf->vb2_buf.index, offset);
	पूर्ण अन्यथा अणु
		बारtamp = match->ts;
		समयcode = match->tc;
		vbuf_flags = match->flags;
		list_del(&match->list);
		kमुक्त(match);
	पूर्ण
	spin_unlock_irqrestore(&sess->ts_spinlock, flags);

	dst_buf_करोne(sess, vbuf, field, बारtamp, समयcode, vbuf_flags);
	अगर (match)
		atomic_dec(&sess->esparser_queued_bufs);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_dst_buf_करोne_offset);

व्योम amvdec_dst_buf_करोne_idx(काष्ठा amvdec_session *sess,
			     u32 buf_idx, u32 offset, u32 field)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा device *dev = sess->core->dev_dec;

	vbuf = v4l2_m2m_dst_buf_हटाओ_by_idx(sess->m2m_ctx,
					      sess->fw_idx_to_vb2_idx[buf_idx]);

	अगर (!vbuf) अणु
		dev_err(dev,
			"Buffer %u done but it doesn't exist in m2m_ctx\n",
			buf_idx);
		वापस;
	पूर्ण

	अगर (offset != -1)
		amvdec_dst_buf_करोne_offset(sess, vbuf, offset, field, true);
	अन्यथा
		amvdec_dst_buf_करोne(sess, vbuf, field);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_dst_buf_करोne_idx);

व्योम amvdec_set_par_from_dar(काष्ठा amvdec_session *sess,
			     u32 dar_num, u32 dar_den)
अणु
	u32 भाग;

	sess->pixelaspect.numerator = sess->height * dar_num;
	sess->pixelaspect.denominator = sess->width * dar_den;
	भाग = gcd(sess->pixelaspect.numerator, sess->pixelaspect.denominator);
	sess->pixelaspect.numerator /= भाग;
	sess->pixelaspect.denominator /= भाग;
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_set_par_from_dar);

व्योम amvdec_src_change(काष्ठा amvdec_session *sess, u32 width,
		       u32 height, u32 dpb_size)
अणु
	अटल स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION पूर्ण;

	v4l2_ctrl_s_ctrl(sess->ctrl_min_buf_capture, dpb_size);

	/*
	 * Check अगर the capture queue is alपढ़ोy configured well क्रम our
	 * useहाल. If so, keep decoding with it and करो not send the event
	 */
	अगर (sess->streamon_cap &&
	    sess->width == width &&
	    sess->height == height &&
	    dpb_size <= sess->num_dst_bufs) अणु
		sess->fmt_out->codec_ops->resume(sess);
		वापस;
	पूर्ण

	sess->changed_क्रमmat = 0;
	sess->width = width;
	sess->height = height;
	sess->status = STATUS_NEEDS_RESUME;

	dev_dbg(sess->core->dev, "Res. changed (%ux%u), DPB size %u\n",
		width, height, dpb_size);
	v4l2_event_queue_fh(&sess->fh, &ev);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_src_change);

व्योम amvdec_पात(काष्ठा amvdec_session *sess)
अणु
	dev_info(sess->core->dev, "Aborting decoding session!\n");
	vb2_queue_error(&sess->m2m_ctx->cap_q_ctx.q);
	vb2_queue_error(&sess->m2m_ctx->out_q_ctx.q);
पूर्ण
EXPORT_SYMBOL_GPL(amvdec_पात);
