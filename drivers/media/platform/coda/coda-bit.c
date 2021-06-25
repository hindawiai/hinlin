<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Coda multi-standard codec IP - BIT processor functions
 *
 * Copyright (C) 2012 Vista Silicon S.L.
 *    Javier Martin, <javier.martin@vista-silicon.com>
 *    Xavier Duret
 * Copyright (C) 2012-2014 Philipp Zabel, Pengutronix
 */

#समावेश <linux/clk.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "coda.h"
#समावेश "imx-vdoa.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#घोषणा CODA_PARA_BUF_SIZE	(10 * 1024)
#घोषणा CODA7_PS_BUF_SIZE	0x28000
#घोषणा CODA9_PS_SAVE_SIZE	(512 * 1024)

#घोषणा CODA_DEFAULT_GAMMA	4096
#घोषणा CODA9_DEFAULT_GAMMA	24576	/* 0.75 * 32768 */

अटल व्योम coda_मुक्त_bitstream_buffer(काष्ठा coda_ctx *ctx);

अटल अंतरभूत पूर्णांक coda_is_initialized(काष्ठा coda_dev *dev)
अणु
	वापस coda_पढ़ो(dev, CODA_REG_BIT_CUR_PC) != 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ coda_isbusy(काष्ठा coda_dev *dev)
अणु
	वापस coda_पढ़ो(dev, CODA_REG_BIT_BUSY);
पूर्ण

अटल पूर्णांक coda_रुको_समयout(काष्ठा coda_dev *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	जबतक (coda_isbusy(dev)) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम coda_command_async(काष्ठा coda_ctx *ctx, पूर्णांक cmd)
अणु
	काष्ठा coda_dev *dev = ctx->dev;

	अगर (dev->devtype->product == CODA_HX4 ||
	    dev->devtype->product == CODA_7541 ||
	    dev->devtype->product == CODA_960) अणु
		/* Restore context related रेजिस्टरs to CODA */
		coda_ग_लिखो(dev, ctx->bit_stream_param,
				CODA_REG_BIT_BIT_STREAM_PARAM);
		coda_ग_लिखो(dev, ctx->frm_dis_flg,
				CODA_REG_BIT_FRM_DIS_FLG(ctx->reg_idx));
		coda_ग_लिखो(dev, ctx->frame_mem_ctrl,
				CODA_REG_BIT_FRAME_MEM_CTRL);
		coda_ग_लिखो(dev, ctx->workbuf.paddr, CODA_REG_BIT_WORK_BUF_ADDR);
	पूर्ण

	अगर (dev->devtype->product == CODA_960) अणु
		coda_ग_लिखो(dev, 1, CODA9_GDI_WPROT_ERR_CLR);
		coda_ग_लिखो(dev, 0, CODA9_GDI_WPROT_RGN_EN);
	पूर्ण

	coda_ग_लिखो(dev, CODA_REG_BIT_BUSY_FLAG, CODA_REG_BIT_BUSY);

	coda_ग_लिखो(dev, ctx->idx, CODA_REG_BIT_RUN_INDEX);
	coda_ग_लिखो(dev, ctx->params.codec_mode, CODA_REG_BIT_RUN_COD_STD);
	coda_ग_लिखो(dev, ctx->params.codec_mode_aux, CODA7_REG_BIT_RUN_AUX_STD);

	trace_coda_bit_run(ctx, cmd);

	coda_ग_लिखो(dev, cmd, CODA_REG_BIT_RUN_COMMAND);
पूर्ण

अटल पूर्णांक coda_command_sync(काष्ठा coda_ctx *ctx, पूर्णांक cmd)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->coda_mutex);

	coda_command_async(ctx, cmd);
	ret = coda_रुको_समयout(dev);
	trace_coda_bit_करोne(ctx);

	वापस ret;
पूर्ण

पूर्णांक coda_hw_reset(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->coda_mutex);

	अगर (!dev->rstc)
		वापस -ENOENT;

	idx = coda_पढ़ो(dev, CODA_REG_BIT_RUN_INDEX);

	अगर (dev->devtype->product == CODA_960) अणु
		समयout = jअगरfies + msecs_to_jअगरfies(100);
		coda_ग_लिखो(dev, 0x11, CODA9_GDI_BUS_CTRL);
		जबतक (coda_पढ़ो(dev, CODA9_GDI_BUS_STATUS) != 0x77) अणु
			अगर (समय_after(jअगरfies, समयout))
				वापस -ETIME;
			cpu_relax();
		पूर्ण
	पूर्ण

	ret = reset_control_reset(dev->rstc);
	अगर (ret < 0)
		वापस ret;

	अगर (dev->devtype->product == CODA_960)
		coda_ग_लिखो(dev, 0x00, CODA9_GDI_BUS_CTRL);
	coda_ग_लिखो(dev, CODA_REG_BIT_BUSY_FLAG, CODA_REG_BIT_BUSY);
	coda_ग_लिखो(dev, CODA_REG_RUN_ENABLE, CODA_REG_BIT_CODE_RUN);
	ret = coda_रुको_समयout(dev);
	coda_ग_लिखो(dev, idx, CODA_REG_BIT_RUN_INDEX);

	वापस ret;
पूर्ण

अटल व्योम coda_kfअगरo_sync_from_device(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा __kfअगरo *kfअगरo = &ctx->bitstream_fअगरo.kfअगरo;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 rd_ptr;

	rd_ptr = coda_पढ़ो(dev, CODA_REG_BIT_RD_PTR(ctx->reg_idx));
	kfअगरo->out = (kfअगरo->in & ~kfअगरo->mask) |
		      (rd_ptr - ctx->bitstream.paddr);
	अगर (kfअगरo->out > kfअगरo->in)
		kfअगरo->out -= kfअगरo->mask + 1;
पूर्ण

अटल व्योम coda_kfअगरo_sync_to_device_full(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा __kfअगरo *kfअगरo = &ctx->bitstream_fअगरo.kfअगरo;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 rd_ptr, wr_ptr;

	rd_ptr = ctx->bitstream.paddr + (kfअगरo->out & kfअगरo->mask);
	coda_ग_लिखो(dev, rd_ptr, CODA_REG_BIT_RD_PTR(ctx->reg_idx));
	wr_ptr = ctx->bitstream.paddr + (kfअगरo->in & kfअगरo->mask);
	coda_ग_लिखो(dev, wr_ptr, CODA_REG_BIT_WR_PTR(ctx->reg_idx));
पूर्ण

अटल व्योम coda_kfअगरo_sync_to_device_ग_लिखो(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा __kfअगरo *kfअगरo = &ctx->bitstream_fअगरo.kfअगरo;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 wr_ptr;

	wr_ptr = ctx->bitstream.paddr + (kfअगरo->in & kfअगरo->mask);
	coda_ग_लिखो(dev, wr_ptr, CODA_REG_BIT_WR_PTR(ctx->reg_idx));
पूर्ण

अटल पूर्णांक coda_h264_bitstream_pad(काष्ठा coda_ctx *ctx, u32 size)
अणु
	अचिन्हित अक्षर *buf;
	u32 n;

	अगर (size < 6)
		size = 6;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	coda_h264_filler_nal(size, buf);
	n = kfअगरo_in(&ctx->bitstream_fअगरo, buf, size);
	kमुक्त(buf);

	वापस (n < size) ? -ENOSPC : 0;
पूर्ण

पूर्णांक coda_bitstream_flush(काष्ठा coda_ctx *ctx)
अणु
	पूर्णांक ret;

	अगर (ctx->inst_type != CODA_INST_DECODER || !ctx->use_bit)
		वापस 0;

	ret = coda_command_sync(ctx, CODA_COMMAND_DEC_BUF_FLUSH);
	अगर (ret < 0) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "failed to flush bitstream\n");
		वापस ret;
	पूर्ण

	kfअगरo_init(&ctx->bitstream_fअगरo, ctx->bitstream.vaddr,
		   ctx->bitstream.size);
	coda_kfअगरo_sync_to_device_full(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक coda_bitstream_queue(काष्ठा coda_ctx *ctx, स्थिर u8 *buf, u32 size)
अणु
	u32 n = kfअगरo_in(&ctx->bitstream_fअगरo, buf, size);

	वापस (n < size) ? -ENOSPC : 0;
पूर्ण

अटल u32 coda_buffer_parse_headers(काष्ठा coda_ctx *ctx,
				     काष्ठा vb2_v4l2_buffer *src_buf,
				     u32 payload)
अणु
	u8 *vaddr = vb2_plane_vaddr(&src_buf->vb2_buf, 0);
	u32 size = 0;

	चयन (ctx->codec->src_fourcc) अणु
	हाल V4L2_PIX_FMT_MPEG2:
		size = coda_mpeg2_parse_headers(ctx, vaddr, payload);
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG4:
		size = coda_mpeg4_parse_headers(ctx, vaddr, payload);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल bool coda_bitstream_try_queue(काष्ठा coda_ctx *ctx,
				     काष्ठा vb2_v4l2_buffer *src_buf)
अणु
	अचिन्हित दीर्घ payload = vb2_get_plane_payload(&src_buf->vb2_buf, 0);
	u8 *vaddr = vb2_plane_vaddr(&src_buf->vb2_buf, 0);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (coda_get_bitstream_payload(ctx) + payload + 512 >=
	    ctx->bitstream.size)
		वापस false;

	अगर (!vaddr) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "trying to queue empty buffer\n");
		वापस true;
	पूर्ण

	अगर (ctx->qsequence == 0 && payload < 512) अणु
		/*
		 * Add padding after the first buffer, अगर it is too small to be
		 * fetched by the CODA, by repeating the headers. Without
		 * repeated headers, or the first frame alपढ़ोy queued, decoder
		 * sequence initialization fails with error code 0x2000 on i.MX6
		 * or error code 0x1 on i.MX51.
		 */
		u32 header_size = coda_buffer_parse_headers(ctx, src_buf,
							    payload);

		अगर (header_size) अणु
			coda_dbg(1, ctx, "pad with %u-byte header\n",
				 header_size);
			क्रम (i = payload; i < 512; i += header_size) अणु
				ret = coda_bitstream_queue(ctx, vaddr,
							   header_size);
				अगर (ret < 0) अणु
					v4l2_err(&ctx->dev->v4l2_dev,
						 "bitstream buffer overflow\n");
					वापस false;
				पूर्ण
				अगर (ctx->dev->devtype->product == CODA_960)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			coda_dbg(1, ctx,
				 "could not parse header, sequence initialization might fail\n");
		पूर्ण

		/* Add padding beक्रमe the first buffer, अगर it is too small */
		अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264)
			coda_h264_bitstream_pad(ctx, 512 - payload);
	पूर्ण

	ret = coda_bitstream_queue(ctx, vaddr, payload);
	अगर (ret < 0) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "bitstream buffer overflow\n");
		वापस false;
	पूर्ण

	src_buf->sequence = ctx->qsequence++;

	/* Sync पढ़ो poपूर्णांकer to device */
	अगर (ctx == v4l2_m2m_get_curr_priv(ctx->dev->m2m_dev))
		coda_kfअगरo_sync_to_device_ग_लिखो(ctx);

	/* Set the stream-end flag after the last buffer is queued */
	अगर (src_buf->flags & V4L2_BUF_FLAG_LAST)
		coda_bit_stream_end_flag(ctx);
	ctx->hold = false;

	वापस true;
पूर्ण

व्योम coda_fill_bitstream(काष्ठा coda_ctx *ctx, काष्ठा list_head *buffer_list)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf;
	काष्ठा coda_buffer_meta *meta;
	u32 start;

	अगर (ctx->bit_stream_param & CODA_BIT_STREAM_END_FLAG)
		वापस;

	जबतक (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) > 0) अणु
		/*
		 * Only queue two JPEGs पूर्णांकo the bitstream buffer to keep
		 * latency low. We need at least one complete buffer and the
		 * header of another buffer (क्रम prescan) in the bitstream.
		 */
		अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG &&
		    ctx->num_metas > 1)
			अवरोध;

		अगर (ctx->num_पूर्णांकernal_frames &&
		    ctx->num_metas >= ctx->num_पूर्णांकernal_frames) अणु
			meta = list_first_entry(&ctx->buffer_meta_list,
						काष्ठा coda_buffer_meta, list);

			/*
			 * If we managed to fill in at least a full reorder
			 * winकरोw of buffers (num_पूर्णांकernal_frames is a
			 * conservative estimate क्रम this) and the bitstream
			 * prefetcher has at least 2 256 bytes periods beyond
			 * the first buffer to fetch, we can safely stop queuing
			 * in order to limit the decoder drain latency.
			 */
			अगर (coda_bitstream_can_fetch_past(ctx, meta->end))
				अवरोध;
		पूर्ण

		src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);

		/* Drop frames that करो not start/end with a SOI/EOI markers */
		अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG &&
		    !coda_jpeg_check_buffer(ctx, &src_buf->vb2_buf)) अणु
			v4l2_err(&ctx->dev->v4l2_dev,
				 "dropping invalid JPEG frame %d\n",
				 ctx->qsequence);
			src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
			अगर (buffer_list) अणु
				काष्ठा v4l2_m2m_buffer *m2m_buf;

				m2m_buf = container_of(src_buf,
						       काष्ठा v4l2_m2m_buffer,
						       vb);
				list_add_tail(&m2m_buf->list, buffer_list);
			पूर्ण अन्यथा अणु
				v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
			पूर्ण
			जारी;
		पूर्ण

		/* Dump empty buffers */
		अगर (!vb2_get_plane_payload(&src_buf->vb2_buf, 0)) अणु
			src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
			v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
			जारी;
		पूर्ण

		/* Buffer start position */
		start = ctx->bitstream_fअगरo.kfअगरo.in;

		अगर (coda_bitstream_try_queue(ctx, src_buf)) अणु
			/*
			 * Source buffer is queued in the bitstream ringbuffer;
			 * queue the बारtamp and mark source buffer as करोne
			 */
			src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);

			meta = kदो_स्मृति(माप(*meta), GFP_KERNEL);
			अगर (meta) अणु
				meta->sequence = src_buf->sequence;
				meta->समयcode = src_buf->समयcode;
				meta->बारtamp = src_buf->vb2_buf.बारtamp;
				meta->start = start;
				meta->end = ctx->bitstream_fअगरo.kfअगरo.in;
				meta->last = src_buf->flags & V4L2_BUF_FLAG_LAST;
				अगर (meta->last)
					coda_dbg(1, ctx, "marking last meta");
				spin_lock(&ctx->buffer_meta_lock);
				list_add_tail(&meta->list,
					      &ctx->buffer_meta_list);
				ctx->num_metas++;
				spin_unlock(&ctx->buffer_meta_lock);

				trace_coda_bit_queue(ctx, src_buf, meta);
			पूर्ण

			अगर (buffer_list) अणु
				काष्ठा v4l2_m2m_buffer *m2m_buf;

				m2m_buf = container_of(src_buf,
						       काष्ठा v4l2_m2m_buffer,
						       vb);
				list_add_tail(&m2m_buf->list, buffer_list);
			पूर्ण अन्यथा अणु
				v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम coda_bit_stream_end_flag(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;

	ctx->bit_stream_param |= CODA_BIT_STREAM_END_FLAG;

	/* If this context is currently running, update the hardware flag */
	अगर ((dev->devtype->product == CODA_960) &&
	    coda_isbusy(dev) &&
	    (ctx->idx == coda_पढ़ो(dev, CODA_REG_BIT_RUN_INDEX))) अणु
		coda_ग_लिखो(dev, ctx->bit_stream_param,
			   CODA_REG_BIT_BIT_STREAM_PARAM);
	पूर्ण
पूर्ण

अटल व्योम coda_parabuf_ग_लिखो(काष्ठा coda_ctx *ctx, पूर्णांक index, u32 value)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	u32 *p = ctx->parabuf.vaddr;

	अगर (dev->devtype->product == CODA_DX6)
		p[index] = value;
	अन्यथा
		p[index ^ 1] = value;
पूर्ण

अटल अंतरभूत पूर्णांक coda_alloc_context_buf(काष्ठा coda_ctx *ctx,
					 काष्ठा coda_aux_buf *buf, माप_प्रकार size,
					 स्थिर अक्षर *name)
अणु
	वापस coda_alloc_aux_buf(ctx->dev, buf, size, name, ctx->debugfs_entry);
पूर्ण


अटल व्योम coda_मुक्त_framebuffers(काष्ठा coda_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CODA_MAX_FRAMEBUFFERS; i++)
		coda_मुक्त_aux_buf(ctx->dev, &ctx->पूर्णांकernal_frames[i].buf);
पूर्ण

अटल पूर्णांक coda_alloc_framebuffers(काष्ठा coda_ctx *ctx,
				   काष्ठा coda_q_data *q_data, u32 fourcc)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक ysize, ycbcr_size;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264 ||
	    ctx->codec->dst_fourcc == V4L2_PIX_FMT_H264 ||
	    ctx->codec->src_fourcc == V4L2_PIX_FMT_MPEG4 ||
	    ctx->codec->dst_fourcc == V4L2_PIX_FMT_MPEG4)
		ysize = round_up(q_data->rect.width, 16) *
			round_up(q_data->rect.height, 16);
	अन्यथा
		ysize = round_up(q_data->rect.width, 8) * q_data->rect.height;

	अगर (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP)
		ycbcr_size = round_up(ysize, 4096) + ysize / 2;
	अन्यथा
		ycbcr_size = ysize + ysize / 2;

	/* Allocate frame buffers */
	क्रम (i = 0; i < ctx->num_पूर्णांकernal_frames; i++) अणु
		माप_प्रकार size = ycbcr_size;
		अक्षर *name;

		/* Add space क्रम mvcol buffers */
		अगर (dev->devtype->product != CODA_DX6 &&
		    (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264 ||
		     (ctx->codec->src_fourcc == V4L2_PIX_FMT_MPEG4 && i == 0)))
			size += ysize / 4;
		name = kaप्र_लिखो(GFP_KERNEL, "fb%d", i);
		अगर (!name) अणु
			coda_मुक्त_framebuffers(ctx);
			वापस -ENOMEM;
		पूर्ण
		ret = coda_alloc_context_buf(ctx, &ctx->पूर्णांकernal_frames[i].buf,
					     size, name);
		kमुक्त(name);
		अगर (ret < 0) अणु
			coda_मुक्त_framebuffers(ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Register frame buffers in the parameter buffer */
	क्रम (i = 0; i < ctx->num_पूर्णांकernal_frames; i++) अणु
		u32 y, cb, cr, mvcol;

		/* Start addresses of Y, Cb, Cr planes */
		y = ctx->पूर्णांकernal_frames[i].buf.paddr;
		cb = y + ysize;
		cr = y + ysize + ysize/4;
		mvcol = y + ysize + ysize/4 + ysize/4;
		अगर (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP) अणु
			cb = round_up(cb, 4096);
			mvcol = cb + ysize/2;
			cr = 0;
			/* Packed 20-bit MSB of base addresses */
			/* YYYYYCCC, CCyyyyyc, cccc.... */
			y = (y & 0xfffff000) | cb >> 20;
			cb = (cb & 0x000ff000) << 12;
		पूर्ण
		coda_parabuf_ग_लिखो(ctx, i * 3 + 0, y);
		coda_parabuf_ग_लिखो(ctx, i * 3 + 1, cb);
		coda_parabuf_ग_लिखो(ctx, i * 3 + 2, cr);

		अगर (dev->devtype->product == CODA_DX6)
			जारी;

		/* mvcol buffer क्रम h.264 and mpeg4 */
		अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264)
			coda_parabuf_ग_लिखो(ctx, 96 + i, mvcol);
		अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_MPEG4 && i == 0)
			coda_parabuf_ग_लिखो(ctx, 97, mvcol);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम coda_मुक्त_context_buffers(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;

	coda_मुक्त_aux_buf(dev, &ctx->slicebuf);
	coda_मुक्त_aux_buf(dev, &ctx->psbuf);
	अगर (dev->devtype->product != CODA_DX6)
		coda_मुक्त_aux_buf(dev, &ctx->workbuf);
	coda_मुक्त_aux_buf(dev, &ctx->parabuf);
पूर्ण

अटल पूर्णांक coda_alloc_context_buffers(काष्ठा coda_ctx *ctx,
				      काष्ठा coda_q_data *q_data)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (!ctx->parabuf.vaddr) अणु
		ret = coda_alloc_context_buf(ctx, &ctx->parabuf,
					     CODA_PARA_BUF_SIZE, "parabuf");
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (dev->devtype->product == CODA_DX6)
		वापस 0;

	अगर (!ctx->slicebuf.vaddr && q_data->fourcc == V4L2_PIX_FMT_H264) अणु
		/* worst हाल slice size */
		size = (DIV_ROUND_UP(q_data->rect.width, 16) *
			DIV_ROUND_UP(q_data->rect.height, 16)) * 3200 / 8 + 512;
		ret = coda_alloc_context_buf(ctx, &ctx->slicebuf, size,
					     "slicebuf");
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (!ctx->psbuf.vaddr && (dev->devtype->product == CODA_HX4 ||
				  dev->devtype->product == CODA_7541)) अणु
		ret = coda_alloc_context_buf(ctx, &ctx->psbuf,
					     CODA7_PS_BUF_SIZE, "psbuf");
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (!ctx->workbuf.vaddr) अणु
		size = dev->devtype->workbuf_size;
		अगर (dev->devtype->product == CODA_960 &&
		    q_data->fourcc == V4L2_PIX_FMT_H264)
			size += CODA9_PS_SAVE_SIZE;
		ret = coda_alloc_context_buf(ctx, &ctx->workbuf, size,
					     "workbuf");
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	coda_मुक्त_context_buffers(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक coda_encode_header(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf,
			      पूर्णांक header_code, u8 *header, पूर्णांक *size)
अणु
	काष्ठा vb2_buffer *vb = &buf->vb2_buf;
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा coda_q_data *q_data_src;
	काष्ठा v4l2_rect *r;
	माप_प्रकार bufsize;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (dev->devtype->product == CODA_960)
		स_रखो(vb2_plane_vaddr(vb, 0), 0, 64);

	coda_ग_लिखो(dev, vb2_dma_contig_plane_dma_addr(vb, 0),
		   CODA_CMD_ENC_HEADER_BB_START);
	bufsize = vb2_plane_size(vb, 0);
	अगर (dev->devtype->product == CODA_960)
		bufsize /= 1024;
	coda_ग_लिखो(dev, bufsize, CODA_CMD_ENC_HEADER_BB_SIZE);
	अगर (dev->devtype->product == CODA_960 &&
	    ctx->codec->dst_fourcc == V4L2_PIX_FMT_H264 &&
	    header_code == CODA_HEADER_H264_SPS) अणु
		q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		r = &q_data_src->rect;

		अगर (r->width % 16 || r->height % 16) अणु
			u32 crop_right = round_up(r->width, 16) -  r->width;
			u32 crop_bottom = round_up(r->height, 16) - r->height;

			coda_ग_लिखो(dev, crop_right,
				   CODA9_CMD_ENC_HEADER_FRAME_CROP_H);
			coda_ग_लिखो(dev, crop_bottom,
				   CODA9_CMD_ENC_HEADER_FRAME_CROP_V);
			header_code |= CODA9_HEADER_FRAME_CROP;
		पूर्ण
	पूर्ण
	coda_ग_लिखो(dev, header_code, CODA_CMD_ENC_HEADER_CODE);
	ret = coda_command_sync(ctx, CODA_COMMAND_ENCODE_HEADER);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "CODA_COMMAND_ENCODE_HEADER timeout\n");
		वापस ret;
	पूर्ण

	अगर (dev->devtype->product == CODA_960) अणु
		क्रम (i = 63; i > 0; i--)
			अगर (((अक्षर *)vb2_plane_vaddr(vb, 0))[i] != 0)
				अवरोध;
		*size = i + 1;
	पूर्ण अन्यथा अणु
		*size = coda_पढ़ो(dev, CODA_REG_BIT_WR_PTR(ctx->reg_idx)) -
			coda_पढ़ो(dev, CODA_CMD_ENC_HEADER_BB_START);
	पूर्ण
	स_नकल(header, vb2_plane_vaddr(vb, 0), *size);

	वापस 0;
पूर्ण

अटल u32 coda_slice_mode(काष्ठा coda_ctx *ctx)
अणु
	पूर्णांक size, unit;

	चयन (ctx->params.slice_mode) अणु
	हाल V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE:
	शेष:
		वापस 0;
	हाल V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB:
		size = ctx->params.slice_max_mb;
		unit = 1;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES:
		size = ctx->params.slice_max_bits;
		unit = 0;
		अवरोध;
	पूर्ण

	वापस ((size & CODA_SLICING_SIZE_MASK) << CODA_SLICING_SIZE_OFFSET) |
	       ((unit & CODA_SLICING_UNIT_MASK) << CODA_SLICING_UNIT_OFFSET) |
	       ((1 & CODA_SLICING_MODE_MASK) << CODA_SLICING_MODE_OFFSET);
पूर्ण

अटल पूर्णांक coda_enc_param_change(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	u32 change_enable = 0;
	u32 success;
	पूर्णांक ret;

	अगर (ctx->params.gop_size_changed) अणु
		change_enable |= CODA_PARAM_CHANGE_RC_GOP;
		coda_ग_लिखो(dev, ctx->params.gop_size,
			   CODA_CMD_ENC_PARAM_RC_GOP);
		ctx->gopcounter = ctx->params.gop_size - 1;
		ctx->params.gop_size_changed = false;
	पूर्ण
	अगर (ctx->params.h264_पूर्णांकra_qp_changed) अणु
		coda_dbg(1, ctx, "parameter change: intra Qp %u\n",
			 ctx->params.h264_पूर्णांकra_qp);

		अगर (ctx->params.bitrate) अणु
			change_enable |= CODA_PARAM_CHANGE_RC_INTRA_QP;
			coda_ग_लिखो(dev, ctx->params.h264_पूर्णांकra_qp,
				   CODA_CMD_ENC_PARAM_RC_INTRA_QP);
		पूर्ण
		ctx->params.h264_पूर्णांकra_qp_changed = false;
	पूर्ण
	अगर (ctx->params.bitrate_changed) अणु
		coda_dbg(1, ctx, "parameter change: bitrate %u kbit/s\n",
			 ctx->params.bitrate);
		change_enable |= CODA_PARAM_CHANGE_RC_BITRATE;
		coda_ग_लिखो(dev, ctx->params.bitrate,
			   CODA_CMD_ENC_PARAM_RC_BITRATE);
		ctx->params.bitrate_changed = false;
	पूर्ण
	अगर (ctx->params.framerate_changed) अणु
		coda_dbg(1, ctx, "parameter change: frame rate %u/%u Hz\n",
			 ctx->params.framerate & 0xffff,
			 (ctx->params.framerate >> 16) + 1);
		change_enable |= CODA_PARAM_CHANGE_RC_FRAME_RATE;
		coda_ग_लिखो(dev, ctx->params.framerate,
			   CODA_CMD_ENC_PARAM_RC_FRAME_RATE);
		ctx->params.framerate_changed = false;
	पूर्ण
	अगर (ctx->params.पूर्णांकra_refresh_changed) अणु
		coda_dbg(1, ctx, "parameter change: intra refresh MBs %u\n",
			 ctx->params.पूर्णांकra_refresh);
		change_enable |= CODA_PARAM_CHANGE_INTRA_MB_NUM;
		coda_ग_लिखो(dev, ctx->params.पूर्णांकra_refresh,
			   CODA_CMD_ENC_PARAM_INTRA_MB_NUM);
		ctx->params.पूर्णांकra_refresh_changed = false;
	पूर्ण
	अगर (ctx->params.slice_mode_changed) अणु
		change_enable |= CODA_PARAM_CHANGE_SLICE_MODE;
		coda_ग_लिखो(dev, coda_slice_mode(ctx),
			   CODA_CMD_ENC_PARAM_SLICE_MODE);
		ctx->params.slice_mode_changed = false;
	पूर्ण

	अगर (!change_enable)
		वापस 0;

	coda_ग_लिखो(dev, change_enable, CODA_CMD_ENC_PARAM_CHANGE_ENABLE);

	ret = coda_command_sync(ctx, CODA_COMMAND_RC_CHANGE_PARAMETER);
	अगर (ret < 0)
		वापस ret;

	success = coda_पढ़ो(dev, CODA_RET_ENC_PARAM_CHANGE_SUCCESS);
	अगर (success != 1)
		coda_dbg(1, ctx, "parameter change failed: %u\n", success);

	वापस 0;
पूर्ण

अटल phys_addr_t coda_iram_alloc(काष्ठा coda_iram_info *iram, माप_प्रकार size)
अणु
	phys_addr_t ret;

	size = round_up(size, 1024);
	अगर (size > iram->reमुख्यing)
		वापस 0;
	iram->reमुख्यing -= size;

	ret = iram->next_paddr;
	iram->next_paddr += size;

	वापस ret;
पूर्ण

अटल व्योम coda_setup_iram(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_iram_info *iram_info = &ctx->iram_info;
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक w64, w128;
	पूर्णांक mb_width;
	पूर्णांक dbk_bits;
	पूर्णांक bit_bits;
	पूर्णांक ip_bits;
	पूर्णांक me_bits;

	स_रखो(iram_info, 0, माप(*iram_info));
	iram_info->next_paddr = dev->iram.paddr;
	iram_info->reमुख्यing = dev->iram.size;

	अगर (!dev->iram.vaddr)
		वापस;

	चयन (dev->devtype->product) अणु
	हाल CODA_HX4:
		dbk_bits = CODA7_USE_HOST_DBK_ENABLE;
		bit_bits = CODA7_USE_HOST_BIT_ENABLE;
		ip_bits = CODA7_USE_HOST_IP_ENABLE;
		me_bits = CODA7_USE_HOST_ME_ENABLE;
		अवरोध;
	हाल CODA_7541:
		dbk_bits = CODA7_USE_HOST_DBK_ENABLE | CODA7_USE_DBK_ENABLE;
		bit_bits = CODA7_USE_HOST_BIT_ENABLE | CODA7_USE_BIT_ENABLE;
		ip_bits = CODA7_USE_HOST_IP_ENABLE | CODA7_USE_IP_ENABLE;
		me_bits = CODA7_USE_HOST_ME_ENABLE | CODA7_USE_ME_ENABLE;
		अवरोध;
	हाल CODA_960:
		dbk_bits = CODA9_USE_HOST_DBK_ENABLE | CODA9_USE_DBK_ENABLE;
		bit_bits = CODA9_USE_HOST_BIT_ENABLE | CODA7_USE_BIT_ENABLE;
		ip_bits = CODA9_USE_HOST_IP_ENABLE | CODA7_USE_IP_ENABLE;
		me_bits = 0;
		अवरोध;
	शेष: /* CODA_DX6 */
		वापस;
	पूर्ण

	अगर (ctx->inst_type == CODA_INST_ENCODER) अणु
		काष्ठा coda_q_data *q_data_src;

		q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		mb_width = DIV_ROUND_UP(q_data_src->rect.width, 16);
		w128 = mb_width * 128;
		w64 = mb_width * 64;

		/* Prioritize in हाल IRAM is too small क्रम everything */
		अगर (dev->devtype->product == CODA_HX4 ||
		    dev->devtype->product == CODA_7541) अणु
			iram_info->search_ram_size = round_up(mb_width * 16 *
							      36 + 2048, 1024);
			iram_info->search_ram_paddr = coda_iram_alloc(iram_info,
						iram_info->search_ram_size);
			अगर (!iram_info->search_ram_paddr) अणु
				pr_err("IRAM is smaller than the search ram size\n");
				जाओ out;
			पूर्ण
			iram_info->axi_sram_use |= me_bits;
		पूर्ण

		/* Only H.264BP and H.263P3 are considered */
		iram_info->buf_dbk_y_use = coda_iram_alloc(iram_info, w64);
		iram_info->buf_dbk_c_use = coda_iram_alloc(iram_info, w64);
		अगर (!iram_info->buf_dbk_c_use)
			जाओ out;
		iram_info->axi_sram_use |= dbk_bits;

		iram_info->buf_bit_use = coda_iram_alloc(iram_info, w128);
		अगर (!iram_info->buf_bit_use)
			जाओ out;
		iram_info->axi_sram_use |= bit_bits;

		iram_info->buf_ip_ac_dc_use = coda_iram_alloc(iram_info, w128);
		अगर (!iram_info->buf_ip_ac_dc_use)
			जाओ out;
		iram_info->axi_sram_use |= ip_bits;

		/* OVL and BTP disabled क्रम encoder */
	पूर्ण अन्यथा अगर (ctx->inst_type == CODA_INST_DECODER) अणु
		काष्ठा coda_q_data *q_data_dst;

		q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		mb_width = DIV_ROUND_UP(q_data_dst->width, 16);
		w128 = mb_width * 128;

		iram_info->buf_dbk_y_use = coda_iram_alloc(iram_info, w128);
		iram_info->buf_dbk_c_use = coda_iram_alloc(iram_info, w128);
		अगर (!iram_info->buf_dbk_c_use)
			जाओ out;
		iram_info->axi_sram_use |= dbk_bits;

		iram_info->buf_bit_use = coda_iram_alloc(iram_info, w128);
		अगर (!iram_info->buf_bit_use)
			जाओ out;
		iram_info->axi_sram_use |= bit_bits;

		iram_info->buf_ip_ac_dc_use = coda_iram_alloc(iram_info, w128);
		अगर (!iram_info->buf_ip_ac_dc_use)
			जाओ out;
		iram_info->axi_sram_use |= ip_bits;

		/* OVL and BTP unused as there is no VC1 support yet */
	पूर्ण

out:
	अगर (!(iram_info->axi_sram_use & CODA7_USE_HOST_IP_ENABLE))
		coda_dbg(1, ctx, "IRAM smaller than needed\n");

	अगर (dev->devtype->product == CODA_HX4 ||
	    dev->devtype->product == CODA_7541) अणु
		/* TODO - Enabling these causes picture errors on CODA7541 */
		अगर (ctx->inst_type == CODA_INST_DECODER) अणु
			/* fw 1.4.50 */
			iram_info->axi_sram_use &= ~(CODA7_USE_HOST_IP_ENABLE |
						     CODA7_USE_IP_ENABLE);
		पूर्ण अन्यथा अणु
			/* fw 13.4.29 */
			iram_info->axi_sram_use &= ~(CODA7_USE_HOST_IP_ENABLE |
						     CODA7_USE_HOST_DBK_ENABLE |
						     CODA7_USE_IP_ENABLE |
						     CODA7_USE_DBK_ENABLE);
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 coda_supported_firmwares[] = अणु
	CODA_FIRMWARE_VERNUM(CODA_DX6, 2, 2, 5),
	CODA_FIRMWARE_VERNUM(CODA_HX4, 1, 4, 50),
	CODA_FIRMWARE_VERNUM(CODA_7541, 1, 4, 50),
	CODA_FIRMWARE_VERNUM(CODA_960, 2, 1, 5),
	CODA_FIRMWARE_VERNUM(CODA_960, 2, 1, 9),
	CODA_FIRMWARE_VERNUM(CODA_960, 2, 3, 10),
	CODA_FIRMWARE_VERNUM(CODA_960, 3, 1, 1),
पूर्ण;

अटल bool coda_firmware_supported(u32 vernum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coda_supported_firmwares); i++)
		अगर (vernum == coda_supported_firmwares[i])
			वापस true;
	वापस false;
पूर्ण

पूर्णांक coda_check_firmware(काष्ठा coda_dev *dev)
अणु
	u16 product, major, minor, release;
	u32 data;
	पूर्णांक ret;

	ret = clk_prepare_enable(dev->clk_per);
	अगर (ret)
		जाओ err_clk_per;

	ret = clk_prepare_enable(dev->clk_ahb);
	अगर (ret)
		जाओ err_clk_ahb;

	coda_ग_लिखो(dev, 0, CODA_CMD_FIRMWARE_VERNUM);
	coda_ग_लिखो(dev, CODA_REG_BIT_BUSY_FLAG, CODA_REG_BIT_BUSY);
	coda_ग_लिखो(dev, 0, CODA_REG_BIT_RUN_INDEX);
	coda_ग_लिखो(dev, 0, CODA_REG_BIT_RUN_COD_STD);
	coda_ग_लिखो(dev, CODA_COMMAND_FIRMWARE_GET, CODA_REG_BIT_RUN_COMMAND);
	अगर (coda_रुको_समयout(dev)) अणु
		v4l2_err(&dev->v4l2_dev, "firmware get command error\n");
		ret = -EIO;
		जाओ err_run_cmd;
	पूर्ण

	अगर (dev->devtype->product == CODA_960) अणु
		data = coda_पढ़ो(dev, CODA9_CMD_FIRMWARE_CODE_REV);
		v4l2_info(&dev->v4l2_dev, "Firmware code revision: %d\n",
			  data);
	पूर्ण

	/* Check we are compatible with the loaded firmware */
	data = coda_पढ़ो(dev, CODA_CMD_FIRMWARE_VERNUM);
	product = CODA_FIRMWARE_PRODUCT(data);
	major = CODA_FIRMWARE_MAJOR(data);
	minor = CODA_FIRMWARE_MINOR(data);
	release = CODA_FIRMWARE_RELEASE(data);

	clk_disable_unprepare(dev->clk_per);
	clk_disable_unprepare(dev->clk_ahb);

	अगर (product != dev->devtype->product) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Wrong firmware. Hw: %s, Fw: %s, Version: %u.%u.%u\n",
			 coda_product_name(dev->devtype->product),
			 coda_product_name(product), major, minor, release);
		वापस -EINVAL;
	पूर्ण

	v4l2_info(&dev->v4l2_dev, "Initialized %s.\n",
		  coda_product_name(product));

	अगर (coda_firmware_supported(data)) अणु
		v4l2_info(&dev->v4l2_dev, "Firmware version: %u.%u.%u\n",
			  major, minor, release);
	पूर्ण अन्यथा अणु
		v4l2_warn(&dev->v4l2_dev,
			  "Unsupported firmware version: %u.%u.%u\n",
			  major, minor, release);
	पूर्ण

	वापस 0;

err_run_cmd:
	clk_disable_unprepare(dev->clk_ahb);
err_clk_ahb:
	clk_disable_unprepare(dev->clk_per);
err_clk_per:
	वापस ret;
पूर्ण

अटल व्योम coda9_set_frame_cache(काष्ठा coda_ctx *ctx, u32 fourcc)
अणु
	u32 cache_size, cache_config;

	अगर (ctx->tiled_map_type == GDI_LINEAR_FRAME_MAP) अणु
		/* Luma 2x0 page, 2x6 cache, chroma 2x0 page, 2x4 cache size */
		cache_size = 0x20262024;
		cache_config = 2 << CODA9_CACHE_PAGEMERGE_OFFSET;
	पूर्ण अन्यथा अणु
		/* Luma 0x2 page, 4x4 cache, chroma 0x2 page, 4x3 cache size */
		cache_size = 0x02440243;
		cache_config = 1 << CODA9_CACHE_PAGEMERGE_OFFSET;
	पूर्ण
	coda_ग_लिखो(ctx->dev, cache_size, CODA9_CMD_SET_FRAME_CACHE_SIZE);
	अगर (fourcc == V4L2_PIX_FMT_NV12 || fourcc == V4L2_PIX_FMT_YUYV) अणु
		cache_config |= 32 << CODA9_CACHE_LUMA_BUFFER_SIZE_OFFSET |
				16 << CODA9_CACHE_CR_BUFFER_SIZE_OFFSET |
				0 << CODA9_CACHE_CB_BUFFER_SIZE_OFFSET;
	पूर्ण अन्यथा अणु
		cache_config |= 32 << CODA9_CACHE_LUMA_BUFFER_SIZE_OFFSET |
				8 << CODA9_CACHE_CR_BUFFER_SIZE_OFFSET |
				8 << CODA9_CACHE_CB_BUFFER_SIZE_OFFSET;
	पूर्ण
	coda_ग_लिखो(ctx->dev, cache_config, CODA9_CMD_SET_FRAME_CACHE_CONFIG);
पूर्ण

/*
 * Encoder context operations
 */

अटल पूर्णांक coda_encoder_reqbufs(काष्ठा coda_ctx *ctx,
				काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा coda_q_data *q_data_src;
	पूर्णांक ret;

	अगर (rb->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस 0;

	अगर (rb->count) अणु
		q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		ret = coda_alloc_context_buffers(ctx, q_data_src);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		coda_मुक्त_context_buffers(ctx);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coda_start_encoding(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा v4l2_device *v4l2_dev = &dev->v4l2_dev;
	काष्ठा coda_q_data *q_data_src, *q_data_dst;
	u32 bitstream_buf, bitstream_size;
	काष्ठा vb2_v4l2_buffer *buf;
	पूर्णांक gamma, ret, value;
	u32 dst_fourcc;
	पूर्णांक num_fb;
	u32 stride;

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	dst_fourcc = q_data_dst->fourcc;

	buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	bitstream_buf = vb2_dma_contig_plane_dma_addr(&buf->vb2_buf, 0);
	bitstream_size = q_data_dst->sizeimage;

	अगर (!coda_is_initialized(dev)) अणु
		v4l2_err(v4l2_dev, "coda is not initialized.\n");
		वापस -EFAULT;
	पूर्ण

	अगर (dst_fourcc == V4L2_PIX_FMT_JPEG) अणु
		अगर (!ctx->params.jpeg_qmat_tab[0])
			ctx->params.jpeg_qmat_tab[0] = kदो_स्मृति(64, GFP_KERNEL);
		अगर (!ctx->params.jpeg_qmat_tab[1])
			ctx->params.jpeg_qmat_tab[1] = kदो_स्मृति(64, GFP_KERNEL);
		coda_set_jpeg_compression_quality(ctx, ctx->params.jpeg_quality);
	पूर्ण

	mutex_lock(&dev->coda_mutex);

	coda_ग_लिखो(dev, ctx->parabuf.paddr, CODA_REG_BIT_PARA_BUF_ADDR);
	coda_ग_लिखो(dev, bitstream_buf, CODA_REG_BIT_RD_PTR(ctx->reg_idx));
	coda_ग_लिखो(dev, bitstream_buf, CODA_REG_BIT_WR_PTR(ctx->reg_idx));
	चयन (dev->devtype->product) अणु
	हाल CODA_DX6:
		coda_ग_लिखो(dev, CODADX6_STREAM_BUF_DYNALLOC_EN |
			CODADX6_STREAM_BUF_PIC_RESET, CODA_REG_BIT_STREAM_CTRL);
		अवरोध;
	हाल CODA_960:
		coda_ग_लिखो(dev, 0, CODA9_GDI_WPROT_RGN_EN);
		fallthrough;
	हाल CODA_HX4:
	हाल CODA_7541:
		coda_ग_लिखो(dev, CODA7_STREAM_BUF_DYNALLOC_EN |
			CODA7_STREAM_BUF_PIC_RESET, CODA_REG_BIT_STREAM_CTRL);
		अवरोध;
	पूर्ण

	ctx->frame_mem_ctrl &= ~(CODA_FRAME_CHROMA_INTERLEAVE | (0x3 << 9) |
				 CODA9_FRAME_TILED2LINEAR);
	अगर (q_data_src->fourcc == V4L2_PIX_FMT_NV12)
		ctx->frame_mem_ctrl |= CODA_FRAME_CHROMA_INTERLEAVE;
	अगर (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP)
		ctx->frame_mem_ctrl |= (0x3 << 9) | CODA9_FRAME_TILED2LINEAR;
	coda_ग_लिखो(dev, ctx->frame_mem_ctrl, CODA_REG_BIT_FRAME_MEM_CTRL);

	अगर (dev->devtype->product == CODA_DX6) अणु
		/* Configure the coda */
		coda_ग_लिखो(dev, dev->iram.paddr,
			   CODADX6_REG_BIT_SEARCH_RAM_BASE_ADDR);
	पूर्ण

	/* Could set rotation here अगर needed */
	value = 0;
	चयन (dev->devtype->product) अणु
	हाल CODA_DX6:
		value = (q_data_src->rect.width & CODADX6_PICWIDTH_MASK)
			<< CODADX6_PICWIDTH_OFFSET;
		value |= (q_data_src->rect.height & CODADX6_PICHEIGHT_MASK)
			 << CODA_PICHEIGHT_OFFSET;
		अवरोध;
	हाल CODA_HX4:
	हाल CODA_7541:
		अगर (dst_fourcc == V4L2_PIX_FMT_H264) अणु
			value = (round_up(q_data_src->rect.width, 16) &
				 CODA7_PICWIDTH_MASK) << CODA7_PICWIDTH_OFFSET;
			value |= (round_up(q_data_src->rect.height, 16) &
				 CODA7_PICHEIGHT_MASK) << CODA_PICHEIGHT_OFFSET;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल CODA_960:
		value = (q_data_src->rect.width & CODA7_PICWIDTH_MASK)
			<< CODA7_PICWIDTH_OFFSET;
		value |= (q_data_src->rect.height & CODA7_PICHEIGHT_MASK)
			 << CODA_PICHEIGHT_OFFSET;
	पूर्ण
	coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_SRC_SIZE);
	अगर (dst_fourcc == V4L2_PIX_FMT_JPEG)
		ctx->params.framerate = 0;
	coda_ग_लिखो(dev, ctx->params.framerate,
		   CODA_CMD_ENC_SEQ_SRC_F_RATE);

	ctx->params.codec_mode = ctx->codec->mode;
	चयन (dst_fourcc) अणु
	हाल V4L2_PIX_FMT_MPEG4:
		अगर (dev->devtype->product == CODA_960)
			coda_ग_लिखो(dev, CODA9_STD_MPEG4,
				   CODA_CMD_ENC_SEQ_COD_STD);
		अन्यथा
			coda_ग_लिखो(dev, CODA_STD_MPEG4,
				   CODA_CMD_ENC_SEQ_COD_STD);
		coda_ग_लिखो(dev, 0, CODA_CMD_ENC_SEQ_MP4_PARA);
		अवरोध;
	हाल V4L2_PIX_FMT_H264:
		अगर (dev->devtype->product == CODA_960)
			coda_ग_लिखो(dev, CODA9_STD_H264,
				   CODA_CMD_ENC_SEQ_COD_STD);
		अन्यथा
			coda_ग_लिखो(dev, CODA_STD_H264,
				   CODA_CMD_ENC_SEQ_COD_STD);
		value = ((ctx->params.h264_disable_deblocking_filter_idc &
			  CODA_264PARAM_DISABLEDEBLK_MASK) <<
			 CODA_264PARAM_DISABLEDEBLK_OFFSET) |
			((ctx->params.h264_slice_alpha_c0_offset_भाग2 &
			  CODA_264PARAM_DEBLKFILTEROFFSETALPHA_MASK) <<
			 CODA_264PARAM_DEBLKFILTEROFFSETALPHA_OFFSET) |
			((ctx->params.h264_slice_beta_offset_भाग2 &
			  CODA_264PARAM_DEBLKFILTEROFFSETBETA_MASK) <<
			 CODA_264PARAM_DEBLKFILTEROFFSETBETA_OFFSET) |
			(ctx->params.h264_स्थिरrained_पूर्णांकra_pred_flag <<
			 CODA_264PARAM_CONSTRAINEDINTRAPREDFLAG_OFFSET) |
			(ctx->params.h264_chroma_qp_index_offset &
			 CODA_264PARAM_CHROMAQPOFFSET_MASK);
		coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_264_PARA);
		अवरोध;
	हाल V4L2_PIX_FMT_JPEG:
		coda_ग_लिखो(dev, 0, CODA_CMD_ENC_SEQ_JPG_PARA);
		coda_ग_लिखो(dev, ctx->params.jpeg_restart_पूर्णांकerval,
				CODA_CMD_ENC_SEQ_JPG_RST_INTERVAL);
		coda_ग_लिखो(dev, 0, CODA_CMD_ENC_SEQ_JPG_THUMB_EN);
		coda_ग_लिखो(dev, 0, CODA_CMD_ENC_SEQ_JPG_THUMB_SIZE);
		coda_ग_लिखो(dev, 0, CODA_CMD_ENC_SEQ_JPG_THUMB_OFFSET);

		coda_jpeg_ग_लिखो_tables(ctx);
		अवरोध;
	शेष:
		v4l2_err(v4l2_dev,
			 "dst format (0x%08x) invalid.\n", dst_fourcc);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * slice mode and GOP size रेजिस्टरs are used क्रम thumb size/offset
	 * in JPEG mode
	 */
	अगर (dst_fourcc != V4L2_PIX_FMT_JPEG) अणु
		value = coda_slice_mode(ctx);
		coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_SLICE_MODE);
		value = ctx->params.gop_size;
		coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_GOP_SIZE);
	पूर्ण

	अगर (ctx->params.bitrate && (ctx->params.frame_rc_enable ||
				    ctx->params.mb_rc_enable)) अणु
		ctx->params.bitrate_changed = false;
		ctx->params.h264_पूर्णांकra_qp_changed = false;

		/* Rate control enabled */
		value = (ctx->params.bitrate & CODA_RATECONTROL_BITRATE_MASK)
			<< CODA_RATECONTROL_BITRATE_OFFSET;
		value |=  1 & CODA_RATECONTROL_ENABLE_MASK;
		value |= (ctx->params.vbv_delay &
			  CODA_RATECONTROL_INITIALDELAY_MASK)
			 << CODA_RATECONTROL_INITIALDELAY_OFFSET;
		अगर (dev->devtype->product == CODA_960)
			value |= BIT(31); /* disable स्वतःskip */
	पूर्ण अन्यथा अणु
		value = 0;
	पूर्ण
	coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_RC_PARA);

	coda_ग_लिखो(dev, ctx->params.vbv_size, CODA_CMD_ENC_SEQ_RC_BUF_SIZE);
	coda_ग_लिखो(dev, ctx->params.पूर्णांकra_refresh,
		   CODA_CMD_ENC_SEQ_INTRA_REFRESH);

	coda_ग_लिखो(dev, bitstream_buf, CODA_CMD_ENC_SEQ_BB_START);
	coda_ग_लिखो(dev, bitstream_size / 1024, CODA_CMD_ENC_SEQ_BB_SIZE);


	value = 0;
	अगर (dev->devtype->product == CODA_960)
		gamma = CODA9_DEFAULT_GAMMA;
	अन्यथा
		gamma = CODA_DEFAULT_GAMMA;
	अगर (gamma > 0) अणु
		coda_ग_लिखो(dev, (gamma & CODA_GAMMA_MASK) << CODA_GAMMA_OFFSET,
			   CODA_CMD_ENC_SEQ_RC_GAMMA);
	पूर्ण

	अगर (ctx->params.h264_min_qp || ctx->params.h264_max_qp) अणु
		coda_ग_लिखो(dev,
			   ctx->params.h264_min_qp << CODA_QPMIN_OFFSET |
			   ctx->params.h264_max_qp << CODA_QPMAX_OFFSET,
			   CODA_CMD_ENC_SEQ_RC_QP_MIN_MAX);
	पूर्ण
	अगर (dev->devtype->product == CODA_960) अणु
		अगर (ctx->params.h264_max_qp)
			value |= 1 << CODA9_OPTION_RCQPMAX_OFFSET;
		अगर (CODA_DEFAULT_GAMMA > 0)
			value |= 1 << CODA9_OPTION_GAMMA_OFFSET;
	पूर्ण अन्यथा अणु
		अगर (CODA_DEFAULT_GAMMA > 0) अणु
			अगर (dev->devtype->product == CODA_DX6)
				value |= 1 << CODADX6_OPTION_GAMMA_OFFSET;
			अन्यथा
				value |= 1 << CODA7_OPTION_GAMMA_OFFSET;
		पूर्ण
		अगर (ctx->params.h264_min_qp)
			value |= 1 << CODA7_OPTION_RCQPMIN_OFFSET;
		अगर (ctx->params.h264_max_qp)
			value |= 1 << CODA7_OPTION_RCQPMAX_OFFSET;
	पूर्ण
	coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_OPTION);

	अगर (ctx->params.frame_rc_enable && !ctx->params.mb_rc_enable)
		value = 1;
	अन्यथा
		value = 0;
	coda_ग_लिखो(dev, value, CODA_CMD_ENC_SEQ_RC_INTERVAL_MODE);

	coda_setup_iram(ctx);

	अगर (dst_fourcc == V4L2_PIX_FMT_H264) अणु
		चयन (dev->devtype->product) अणु
		हाल CODA_DX6:
			value = FMO_SLICE_SAVE_BUF_SIZE << 7;
			coda_ग_लिखो(dev, value, CODADX6_CMD_ENC_SEQ_FMO);
			अवरोध;
		हाल CODA_HX4:
		हाल CODA_7541:
			coda_ग_लिखो(dev, ctx->iram_info.search_ram_paddr,
					CODA7_CMD_ENC_SEQ_SEARCH_BASE);
			coda_ग_लिखो(dev, ctx->iram_info.search_ram_size,
					CODA7_CMD_ENC_SEQ_SEARCH_SIZE);
			अवरोध;
		हाल CODA_960:
			coda_ग_लिखो(dev, 0, CODA9_CMD_ENC_SEQ_ME_OPTION);
			coda_ग_लिखो(dev, 0, CODA9_CMD_ENC_SEQ_INTRA_WEIGHT);
		पूर्ण
	पूर्ण

	ret = coda_command_sync(ctx, CODA_COMMAND_SEQ_INIT);
	अगर (ret < 0) अणु
		v4l2_err(v4l2_dev, "CODA_COMMAND_SEQ_INIT timeout\n");
		जाओ out;
	पूर्ण

	अगर (coda_पढ़ो(dev, CODA_RET_ENC_SEQ_SUCCESS) == 0) अणु
		v4l2_err(v4l2_dev, "CODA_COMMAND_SEQ_INIT failed\n");
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	ctx->initialized = 1;

	अगर (dst_fourcc != V4L2_PIX_FMT_JPEG) अणु
		अगर (dev->devtype->product == CODA_960)
			ctx->num_पूर्णांकernal_frames = 4;
		अन्यथा
			ctx->num_पूर्णांकernal_frames = 2;
		ret = coda_alloc_framebuffers(ctx, q_data_src, dst_fourcc);
		अगर (ret < 0) अणु
			v4l2_err(v4l2_dev, "failed to allocate framebuffers\n");
			जाओ out;
		पूर्ण
		num_fb = 2;
		stride = q_data_src->bytesperline;
	पूर्ण अन्यथा अणु
		ctx->num_पूर्णांकernal_frames = 0;
		num_fb = 0;
		stride = 0;
	पूर्ण
	coda_ग_लिखो(dev, num_fb, CODA_CMD_SET_FRAME_BUF_NUM);
	coda_ग_लिखो(dev, stride, CODA_CMD_SET_FRAME_BUF_STRIDE);

	अगर (dev->devtype->product == CODA_HX4 ||
	    dev->devtype->product == CODA_7541) अणु
		coda_ग_लिखो(dev, q_data_src->bytesperline,
				CODA7_CMD_SET_FRAME_SOURCE_BUF_STRIDE);
	पूर्ण
	अगर (dev->devtype->product != CODA_DX6) अणु
		coda_ग_लिखो(dev, ctx->iram_info.buf_bit_use,
				CODA7_CMD_SET_FRAME_AXI_BIT_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_ip_ac_dc_use,
				CODA7_CMD_SET_FRAME_AXI_IPACDC_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_dbk_y_use,
				CODA7_CMD_SET_FRAME_AXI_DBKY_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_dbk_c_use,
				CODA7_CMD_SET_FRAME_AXI_DBKC_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_ovl_use,
				CODA7_CMD_SET_FRAME_AXI_OVL_ADDR);
		अगर (dev->devtype->product == CODA_960) अणु
			coda_ग_लिखो(dev, ctx->iram_info.buf_btp_use,
					CODA9_CMD_SET_FRAME_AXI_BTP_ADDR);

			coda9_set_frame_cache(ctx, q_data_src->fourcc);

			/* FIXME */
			coda_ग_लिखो(dev, ctx->पूर्णांकernal_frames[2].buf.paddr,
				   CODA9_CMD_SET_FRAME_SUBSAMP_A);
			coda_ग_लिखो(dev, ctx->पूर्णांकernal_frames[3].buf.paddr,
				   CODA9_CMD_SET_FRAME_SUBSAMP_B);
		पूर्ण
	पूर्ण

	ret = coda_command_sync(ctx, CODA_COMMAND_SET_FRAME_BUF);
	अगर (ret < 0) अणु
		v4l2_err(v4l2_dev, "CODA_COMMAND_SET_FRAME_BUF timeout\n");
		जाओ out;
	पूर्ण

	coda_dbg(1, ctx, "start encoding %dx%d %4.4s->%4.4s @ %d/%d Hz\n",
		 q_data_src->rect.width, q_data_src->rect.height,
		 (अक्षर *)&ctx->codec->src_fourcc, (अक्षर *)&dst_fourcc,
		 ctx->params.framerate & 0xffff,
		 (ctx->params.framerate >> 16) + 1);

	/* Save stream headers */
	buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	चयन (dst_fourcc) अणु
	हाल V4L2_PIX_FMT_H264:
		/*
		 * Get SPS in the first frame and copy it to an
		 * पूर्णांकermediate buffer.
		 */
		ret = coda_encode_header(ctx, buf, CODA_HEADER_H264_SPS,
					 &ctx->vpu_header[0][0],
					 &ctx->vpu_header_size[0]);
		अगर (ret < 0)
			जाओ out;

		/*
		 * If visible width or height are not aligned to macroblock
		 * size, the crop_right and crop_bottom SPS fields must be set
		 * to the dअगरference between visible and coded size.  This is
		 * only supported by CODA960 firmware. All others करो not allow
		 * writing frame cropping parameters, so we have to manually
		 * fix up the SPS RBSP (Sequence Parameter Set Raw Byte
		 * Sequence Payload) ourselves.
		 */
		अगर (ctx->dev->devtype->product != CODA_960 &&
		    ((q_data_src->rect.width % 16) ||
		     (q_data_src->rect.height % 16))) अणु
			ret = coda_h264_sps_fixup(ctx, q_data_src->rect.width,
						  q_data_src->rect.height,
						  &ctx->vpu_header[0][0],
						  &ctx->vpu_header_size[0],
						  माप(ctx->vpu_header[0]));
			अगर (ret < 0)
				जाओ out;
		पूर्ण

		/*
		 * Get PPS in the first frame and copy it to an
		 * पूर्णांकermediate buffer.
		 */
		ret = coda_encode_header(ctx, buf, CODA_HEADER_H264_PPS,
					 &ctx->vpu_header[1][0],
					 &ctx->vpu_header_size[1]);
		अगर (ret < 0)
			जाओ out;

		/*
		 * Length of H.264 headers is variable and thus it might not be
		 * aligned क्रम the coda to append the encoded frame. In that is
		 * the हाल a filler NAL must be added to header 2.
		 */
		ctx->vpu_header_size[2] = coda_h264_padding(
					(ctx->vpu_header_size[0] +
					 ctx->vpu_header_size[1]),
					 ctx->vpu_header[2]);
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG4:
		/*
		 * Get VOS in the first frame and copy it to an
		 * पूर्णांकermediate buffer
		 */
		ret = coda_encode_header(ctx, buf, CODA_HEADER_MP4V_VOS,
					 &ctx->vpu_header[0][0],
					 &ctx->vpu_header_size[0]);
		अगर (ret < 0)
			जाओ out;

		ret = coda_encode_header(ctx, buf, CODA_HEADER_MP4V_VIS,
					 &ctx->vpu_header[1][0],
					 &ctx->vpu_header_size[1]);
		अगर (ret < 0)
			जाओ out;

		ret = coda_encode_header(ctx, buf, CODA_HEADER_MP4V_VOL,
					 &ctx->vpu_header[2][0],
					 &ctx->vpu_header_size[2]);
		अगर (ret < 0)
			जाओ out;
		अवरोध;
	शेष:
		/* No more क्रमmats need to save headers at the moment */
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&dev->coda_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक coda_prepare_encode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_q_data *q_data_src, *q_data_dst;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक क्रमce_ipicture;
	पूर्णांक quant_param = 0;
	u32 pic_stream_buffer_addr, pic_stream_buffer_size;
	u32 rot_mode = 0;
	u32 dst_fourcc;
	u32 reg;
	पूर्णांक ret;

	ret = coda_enc_param_change(ctx);
	अगर (ret < 0) अणु
		v4l2_warn(&ctx->dev->v4l2_dev, "parameter change failed: %d\n",
			  ret);
	पूर्ण

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	dst_fourcc = q_data_dst->fourcc;

	src_buf->sequence = ctx->osequence;
	dst_buf->sequence = ctx->osequence;
	ctx->osequence++;

	क्रमce_ipicture = ctx->params.क्रमce_ipicture;
	अगर (क्रमce_ipicture)
		ctx->params.क्रमce_ipicture = false;
	अन्यथा अगर (ctx->params.gop_size != 0 &&
		 (src_buf->sequence % ctx->params.gop_size) == 0)
		क्रमce_ipicture = 1;

	/*
	 * Workaround coda firmware BUG that only marks the first
	 * frame as IDR. This is a problem क्रम some decoders that can't
	 * recover when a frame is lost.
	 */
	अगर (!क्रमce_ipicture) अणु
		src_buf->flags |= V4L2_BUF_FLAG_PFRAME;
		src_buf->flags &= ~V4L2_BUF_FLAG_KEYFRAME;
	पूर्ण अन्यथा अणु
		src_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
		src_buf->flags &= ~V4L2_BUF_FLAG_PFRAME;
	पूर्ण

	अगर (dev->devtype->product == CODA_960)
		coda_set_gdi_regs(ctx);

	/*
	 * Copy headers in front of the first frame and क्रमced I frames क्रम
	 * H.264 only. In MPEG4 they are alपढ़ोy copied by the CODA.
	 */
	अगर (src_buf->sequence == 0 || क्रमce_ipicture) अणु
		pic_stream_buffer_addr =
			vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0) +
			ctx->vpu_header_size[0] +
			ctx->vpu_header_size[1] +
			ctx->vpu_header_size[2];
		pic_stream_buffer_size = q_data_dst->sizeimage -
			ctx->vpu_header_size[0] -
			ctx->vpu_header_size[1] -
			ctx->vpu_header_size[2];
		स_नकल(vb2_plane_vaddr(&dst_buf->vb2_buf, 0),
		       &ctx->vpu_header[0][0], ctx->vpu_header_size[0]);
		स_नकल(vb2_plane_vaddr(&dst_buf->vb2_buf, 0)
			+ ctx->vpu_header_size[0], &ctx->vpu_header[1][0],
			ctx->vpu_header_size[1]);
		स_नकल(vb2_plane_vaddr(&dst_buf->vb2_buf, 0)
			+ ctx->vpu_header_size[0] + ctx->vpu_header_size[1],
			&ctx->vpu_header[2][0], ctx->vpu_header_size[2]);
	पूर्ण अन्यथा अणु
		pic_stream_buffer_addr =
			vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
		pic_stream_buffer_size = q_data_dst->sizeimage;
	पूर्ण

	अगर (क्रमce_ipicture) अणु
		चयन (dst_fourcc) अणु
		हाल V4L2_PIX_FMT_H264:
			quant_param = ctx->params.h264_पूर्णांकra_qp;
			अवरोध;
		हाल V4L2_PIX_FMT_MPEG4:
			quant_param = ctx->params.mpeg4_पूर्णांकra_qp;
			अवरोध;
		हाल V4L2_PIX_FMT_JPEG:
			quant_param = 30;
			अवरोध;
		शेष:
			v4l2_warn(&ctx->dev->v4l2_dev,
				"cannot set intra qp, fmt not supported\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (dst_fourcc) अणु
		हाल V4L2_PIX_FMT_H264:
			quant_param = ctx->params.h264_पूर्णांकer_qp;
			अवरोध;
		हाल V4L2_PIX_FMT_MPEG4:
			quant_param = ctx->params.mpeg4_पूर्णांकer_qp;
			अवरोध;
		शेष:
			v4l2_warn(&ctx->dev->v4l2_dev,
				"cannot set inter qp, fmt not supported\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* submit */
	अगर (ctx->params.rot_mode)
		rot_mode = CODA_ROT_MIR_ENABLE | ctx->params.rot_mode;
	coda_ग_लिखो(dev, rot_mode, CODA_CMD_ENC_PIC_ROT_MODE);
	coda_ग_लिखो(dev, quant_param, CODA_CMD_ENC_PIC_QS);

	अगर (dev->devtype->product == CODA_960) अणु
		coda_ग_लिखो(dev, 4/*FIXME: 0*/, CODA9_CMD_ENC_PIC_SRC_INDEX);
		coda_ग_लिखो(dev, q_data_src->bytesperline,
			   CODA9_CMD_ENC_PIC_SRC_STRIDE);
		coda_ग_लिखो(dev, 0, CODA9_CMD_ENC_PIC_SUB_FRAME_SYNC);

		reg = CODA9_CMD_ENC_PIC_SRC_ADDR_Y;
	पूर्ण अन्यथा अणु
		reg = CODA_CMD_ENC_PIC_SRC_ADDR_Y;
	पूर्ण
	coda_ग_लिखो_base(ctx, q_data_src, src_buf, reg);

	coda_ग_लिखो(dev, क्रमce_ipicture << 1 & 0x2,
		   CODA_CMD_ENC_PIC_OPTION);

	coda_ग_लिखो(dev, pic_stream_buffer_addr, CODA_CMD_ENC_PIC_BB_START);
	coda_ग_लिखो(dev, pic_stream_buffer_size / 1024,
		   CODA_CMD_ENC_PIC_BB_SIZE);

	अगर (!ctx->streamon_out) अणु
		/* After streamoff on the output side, set stream end flag */
		ctx->bit_stream_param |= CODA_BIT_STREAM_END_FLAG;
		coda_ग_लिखो(dev, ctx->bit_stream_param,
			   CODA_REG_BIT_BIT_STREAM_PARAM);
	पूर्ण

	अगर (dev->devtype->product != CODA_DX6)
		coda_ग_लिखो(dev, ctx->iram_info.axi_sram_use,
				CODA7_REG_BIT_AXI_SRAM_USE);

	trace_coda_enc_pic_run(ctx, src_buf);

	coda_command_async(ctx, CODA_COMMAND_PIC_RUN);

	वापस 0;
पूर्ण

अटल अक्षर coda_frame_type_अक्षर(u32 flags)
अणु
	वापस (flags & V4L2_BUF_FLAG_KEYFRAME) ? 'I' :
	       (flags & V4L2_BUF_FLAG_PFRAME) ? 'P' :
	       (flags & V4L2_BUF_FLAG_BFRAME) ? 'B' : '?';
पूर्ण

अटल व्योम coda_finish_encode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 wr_ptr, start_ptr;

	अगर (ctx->पातing)
		वापस;

	/*
	 * Lock to make sure that an encoder stop command running in parallel
	 * will either alपढ़ोy have marked src_buf as last, or it will wake up
	 * the capture queue after the buffers are वापसed.
	 */
	mutex_lock(&ctx->wakeup_mutex);
	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	trace_coda_enc_pic_करोne(ctx, dst_buf);

	/* Get results from the coda */
	start_ptr = coda_पढ़ो(dev, CODA_CMD_ENC_PIC_BB_START);
	wr_ptr = coda_पढ़ो(dev, CODA_REG_BIT_WR_PTR(ctx->reg_idx));

	/* Calculate bytesused field */
	अगर (dst_buf->sequence == 0 ||
	    src_buf->flags & V4L2_BUF_FLAG_KEYFRAME) अणु
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, wr_ptr - start_ptr +
					ctx->vpu_header_size[0] +
					ctx->vpu_header_size[1] +
					ctx->vpu_header_size[2]);
	पूर्ण अन्यथा अणु
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, wr_ptr - start_ptr);
	पूर्ण

	coda_dbg(1, ctx, "frame size = %u\n", wr_ptr - start_ptr);

	coda_पढ़ो(dev, CODA_RET_ENC_PIC_SLICE_NUM);
	coda_पढ़ो(dev, CODA_RET_ENC_PIC_FLAG);

	dst_buf->flags &= ~(V4L2_BUF_FLAG_KEYFRAME |
			    V4L2_BUF_FLAG_PFRAME |
			    V4L2_BUF_FLAG_LAST);
	अगर (coda_पढ़ो(dev, CODA_RET_ENC_PIC_TYPE) == 0)
		dst_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
	अन्यथा
		dst_buf->flags |= V4L2_BUF_FLAG_PFRAME;
	dst_buf->flags |= src_buf->flags & V4L2_BUF_FLAG_LAST;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, false);

	v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);

	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	coda_m2m_buf_करोne(ctx, dst_buf, VB2_BUF_STATE_DONE);
	mutex_unlock(&ctx->wakeup_mutex);

	ctx->gopcounter--;
	अगर (ctx->gopcounter < 0)
		ctx->gopcounter = ctx->params.gop_size - 1;

	coda_dbg(1, ctx, "job finished: encoded %c frame (%d)%s\n",
		 coda_frame_type_अक्षर(dst_buf->flags), dst_buf->sequence,
		 (dst_buf->flags & V4L2_BUF_FLAG_LAST) ? " (last)" : "");
पूर्ण

अटल व्योम coda_seq_end_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा coda_ctx *ctx = container_of(work, काष्ठा coda_ctx, seq_end_work);
	काष्ठा coda_dev *dev = ctx->dev;

	mutex_lock(&ctx->buffer_mutex);
	mutex_lock(&dev->coda_mutex);

	अगर (ctx->initialized == 0)
		जाओ out;

	coda_dbg(1, ctx, "%s: sent command 'SEQ_END' to coda\n", __func__);
	अगर (coda_command_sync(ctx, CODA_COMMAND_SEQ_END)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "CODA_COMMAND_SEQ_END failed\n");
	पूर्ण

	/*
	 * FIXME: Someबार h.264 encoding fails with 8-byte sequences missing
	 * from the output stream after the h.264 decoder has run. Resetting the
	 * hardware after the decoder has finished seems to help.
	 */
	अगर (dev->devtype->product == CODA_960)
		coda_hw_reset(ctx);

	kfअगरo_init(&ctx->bitstream_fअगरo,
		ctx->bitstream.vaddr, ctx->bitstream.size);

	coda_मुक्त_framebuffers(ctx);

	ctx->initialized = 0;

out:
	mutex_unlock(&dev->coda_mutex);
	mutex_unlock(&ctx->buffer_mutex);
पूर्ण

अटल व्योम coda_bit_release(काष्ठा coda_ctx *ctx)
अणु
	mutex_lock(&ctx->buffer_mutex);
	coda_मुक्त_framebuffers(ctx);
	coda_मुक्त_context_buffers(ctx);
	coda_मुक्त_bitstream_buffer(ctx);
	mutex_unlock(&ctx->buffer_mutex);
पूर्ण

स्थिर काष्ठा coda_context_ops coda_bit_encode_ops = अणु
	.queue_init = coda_encoder_queue_init,
	.reqbufs = coda_encoder_reqbufs,
	.start_streaming = coda_start_encoding,
	.prepare_run = coda_prepare_encode,
	.finish_run = coda_finish_encode,
	.seq_end_work = coda_seq_end_work,
	.release = coda_bit_release,
पूर्ण;

/*
 * Decoder context operations
 */

अटल पूर्णांक coda_alloc_bitstream_buffer(काष्ठा coda_ctx *ctx,
				       काष्ठा coda_q_data *q_data)
अणु
	अगर (ctx->bitstream.vaddr)
		वापस 0;

	ctx->bitstream.size = roundup_घात_of_two(q_data->sizeimage * 2);
	ctx->bitstream.vaddr = dma_alloc_wc(ctx->dev->dev, ctx->bitstream.size,
					    &ctx->bitstream.paddr, GFP_KERNEL);
	अगर (!ctx->bitstream.vaddr) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "failed to allocate bitstream ringbuffer");
		वापस -ENOMEM;
	पूर्ण
	kfअगरo_init(&ctx->bitstream_fअगरo,
		   ctx->bitstream.vaddr, ctx->bitstream.size);

	वापस 0;
पूर्ण

अटल व्योम coda_मुक्त_bitstream_buffer(काष्ठा coda_ctx *ctx)
अणु
	अगर (ctx->bitstream.vaddr == शून्य)
		वापस;

	dma_मुक्त_wc(ctx->dev->dev, ctx->bitstream.size, ctx->bitstream.vaddr,
		    ctx->bitstream.paddr);
	ctx->bitstream.vaddr = शून्य;
	kfअगरo_init(&ctx->bitstream_fअगरo, शून्य, 0);
पूर्ण

अटल पूर्णांक coda_decoder_reqbufs(काष्ठा coda_ctx *ctx,
				काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा coda_q_data *q_data_src;
	पूर्णांक ret;

	अगर (rb->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस 0;

	अगर (rb->count) अणु
		q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		ret = coda_alloc_context_buffers(ctx, q_data_src);
		अगर (ret < 0)
			वापस ret;
		ret = coda_alloc_bitstream_buffer(ctx, q_data_src);
		अगर (ret < 0) अणु
			coda_मुक्त_context_buffers(ctx);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		coda_मुक्त_bitstream_buffer(ctx);
		coda_मुक्त_context_buffers(ctx);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool coda_reorder_enable(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक profile;

	अगर (dev->devtype->product != CODA_HX4 &&
	    dev->devtype->product != CODA_7541 &&
	    dev->devtype->product != CODA_960)
		वापस false;

	अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG)
		वापस false;

	अगर (ctx->codec->src_fourcc != V4L2_PIX_FMT_H264)
		वापस true;

	profile = coda_h264_profile(ctx->params.h264_profile_idc);
	अगर (profile < 0)
		v4l2_warn(&dev->v4l2_dev, "Unknown H264 Profile: %u\n",
			  ctx->params.h264_profile_idc);

	/* Baseline profile करोes not support reordering */
	वापस profile > V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE;
पूर्ण

अटल व्योम coda_decoder_drop_used_metas(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_buffer_meta *meta, *पंचांगp;

	/*
	 * All metas that end at or beक्रमe the RD poपूर्णांकer (fअगरo out),
	 * are now consumed by the VPU and should be released.
	 */
	spin_lock(&ctx->buffer_meta_lock);
	list_क्रम_each_entry_safe(meta, पंचांगp, &ctx->buffer_meta_list, list) अणु
		अगर (ctx->bitstream_fअगरo.kfअगरo.out >= meta->end) अणु
			coda_dbg(2, ctx, "releasing meta: seq=%d start=%d end=%d\n",
				 meta->sequence, meta->start, meta->end);

			list_del(&meta->list);
			ctx->num_metas--;
			ctx->first_frame_sequence++;
			kमुक्त(meta);
		पूर्ण
	पूर्ण
	spin_unlock(&ctx->buffer_meta_lock);
पूर्ण

अटल पूर्णांक __coda_decoder_seq_init(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_q_data *q_data_src, *q_data_dst;
	u32 bitstream_buf, bitstream_size;
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक width, height;
	u32 src_fourcc, dst_fourcc;
	u32 val;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->coda_mutex);

	coda_dbg(1, ctx, "Video Data Order Adapter: %s\n",
		 ctx->use_vकरोa ? "Enabled" : "Disabled");

	/* Start decoding */
	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	bitstream_buf = ctx->bitstream.paddr;
	bitstream_size = ctx->bitstream.size;
	src_fourcc = q_data_src->fourcc;
	dst_fourcc = q_data_dst->fourcc;

	/* Update coda bitstream पढ़ो and ग_लिखो poपूर्णांकers from kfअगरo */
	coda_kfअगरo_sync_to_device_full(ctx);

	ctx->frame_mem_ctrl &= ~(CODA_FRAME_CHROMA_INTERLEAVE | (0x3 << 9) |
				 CODA9_FRAME_TILED2LINEAR);
	अगर (dst_fourcc == V4L2_PIX_FMT_NV12 || dst_fourcc == V4L2_PIX_FMT_YUYV)
		ctx->frame_mem_ctrl |= CODA_FRAME_CHROMA_INTERLEAVE;
	अगर (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP)
		ctx->frame_mem_ctrl |= (0x3 << 9) |
			((ctx->use_vकरोa) ? 0 : CODA9_FRAME_TILED2LINEAR);
	coda_ग_लिखो(dev, ctx->frame_mem_ctrl, CODA_REG_BIT_FRAME_MEM_CTRL);

	ctx->display_idx = -1;
	ctx->frm_dis_flg = 0;
	coda_ग_लिखो(dev, 0, CODA_REG_BIT_FRM_DIS_FLG(ctx->reg_idx));

	coda_ग_लिखो(dev, bitstream_buf, CODA_CMD_DEC_SEQ_BB_START);
	coda_ग_लिखो(dev, bitstream_size / 1024, CODA_CMD_DEC_SEQ_BB_SIZE);
	val = 0;
	अगर (coda_reorder_enable(ctx))
		val |= CODA_REORDER_ENABLE;
	अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG)
		val |= CODA_NO_INT_ENABLE;
	coda_ग_लिखो(dev, val, CODA_CMD_DEC_SEQ_OPTION);

	ctx->params.codec_mode = ctx->codec->mode;
	अगर (dev->devtype->product == CODA_960 &&
	    src_fourcc == V4L2_PIX_FMT_MPEG4)
		ctx->params.codec_mode_aux = CODA_MP4_AUX_MPEG4;
	अन्यथा
		ctx->params.codec_mode_aux = 0;
	अगर (src_fourcc == V4L2_PIX_FMT_MPEG4) अणु
		coda_ग_लिखो(dev, CODA_MP4_CLASS_MPEG4,
			   CODA_CMD_DEC_SEQ_MP4_ASP_CLASS);
	पूर्ण
	अगर (src_fourcc == V4L2_PIX_FMT_H264) अणु
		अगर (dev->devtype->product == CODA_HX4 ||
		    dev->devtype->product == CODA_7541) अणु
			coda_ग_लिखो(dev, ctx->psbuf.paddr,
					CODA_CMD_DEC_SEQ_PS_BB_START);
			coda_ग_लिखो(dev, (CODA7_PS_BUF_SIZE / 1024),
					CODA_CMD_DEC_SEQ_PS_BB_SIZE);
		पूर्ण
		अगर (dev->devtype->product == CODA_960) अणु
			coda_ग_लिखो(dev, 0, CODA_CMD_DEC_SEQ_X264_MV_EN);
			coda_ग_लिखो(dev, 512, CODA_CMD_DEC_SEQ_SPP_CHUNK_SIZE);
		पूर्ण
	पूर्ण
	अगर (src_fourcc == V4L2_PIX_FMT_JPEG)
		coda_ग_लिखो(dev, 0, CODA_CMD_DEC_SEQ_JPG_THUMB_EN);
	अगर (dev->devtype->product != CODA_960)
		coda_ग_लिखो(dev, 0, CODA_CMD_DEC_SEQ_SRC_SIZE);

	ctx->bit_stream_param = CODA_BIT_DEC_SEQ_INIT_ESCAPE;
	ret = coda_command_sync(ctx, CODA_COMMAND_SEQ_INIT);
	ctx->bit_stream_param = 0;
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "CODA_COMMAND_SEQ_INIT timeout\n");
		वापस ret;
	पूर्ण
	ctx->sequence_offset = ~0U;
	ctx->initialized = 1;
	ctx->first_frame_sequence = 0;

	/* Update kfअगरo out poपूर्णांकer from coda bitstream पढ़ो poपूर्णांकer */
	coda_kfअगरo_sync_from_device(ctx);

	/*
	 * After updating the पढ़ो poपूर्णांकer, we need to check अगर
	 * any metas are consumed and should be released.
	 */
	coda_decoder_drop_used_metas(ctx);

	अगर (coda_पढ़ो(dev, CODA_RET_DEC_SEQ_SUCCESS) == 0) अणु
		v4l2_err(&dev->v4l2_dev,
			"CODA_COMMAND_SEQ_INIT failed, error code = 0x%x\n",
			coda_पढ़ो(dev, CODA_RET_DEC_SEQ_ERR_REASON));
		वापस -EAGAIN;
	पूर्ण

	val = coda_पढ़ो(dev, CODA_RET_DEC_SEQ_SRC_SIZE);
	अगर (dev->devtype->product == CODA_DX6) अणु
		width = (val >> CODADX6_PICWIDTH_OFFSET) & CODADX6_PICWIDTH_MASK;
		height = val & CODADX6_PICHEIGHT_MASK;
	पूर्ण अन्यथा अणु
		width = (val >> CODA7_PICWIDTH_OFFSET) & CODA7_PICWIDTH_MASK;
		height = val & CODA7_PICHEIGHT_MASK;
	पूर्ण

	अगर (width > q_data_dst->bytesperline || height > q_data_dst->height) अणु
		v4l2_err(&dev->v4l2_dev, "stream is %dx%d, not %dx%d\n",
			 width, height, q_data_dst->bytesperline,
			 q_data_dst->height);
		वापस -EINVAL;
	पूर्ण

	width = round_up(width, 16);
	height = round_up(height, 16);

	coda_dbg(1, ctx, "start decoding: %dx%d\n", width, height);

	ctx->num_पूर्णांकernal_frames = coda_पढ़ो(dev, CODA_RET_DEC_SEQ_FRAME_NEED);
	/*
	 * If the VDOA is used, the decoder needs one additional frame,
	 * because the frames are मुक्तd when the next frame is decoded.
	 * Otherwise there are visible errors in the decoded frames (green
	 * regions in displayed frames) and a broken order of frames (earlier
	 * frames are sporadically displayed after later frames).
	 */
	अगर (ctx->use_vकरोa)
		ctx->num_पूर्णांकernal_frames += 1;
	अगर (ctx->num_पूर्णांकernal_frames > CODA_MAX_FRAMEBUFFERS) अणु
		v4l2_err(&dev->v4l2_dev,
			 "not enough framebuffers to decode (%d < %d)\n",
			 CODA_MAX_FRAMEBUFFERS, ctx->num_पूर्णांकernal_frames);
		वापस -EINVAL;
	पूर्ण

	अगर (src_fourcc == V4L2_PIX_FMT_H264) अणु
		u32 left_right;
		u32 top_bottom;

		left_right = coda_पढ़ो(dev, CODA_RET_DEC_SEQ_CROP_LEFT_RIGHT);
		top_bottom = coda_पढ़ो(dev, CODA_RET_DEC_SEQ_CROP_TOP_BOTTOM);

		q_data_dst->rect.left = (left_right >> 10) & 0x3ff;
		q_data_dst->rect.top = (top_bottom >> 10) & 0x3ff;
		q_data_dst->rect.width = width - q_data_dst->rect.left -
					 (left_right & 0x3ff);
		q_data_dst->rect.height = height - q_data_dst->rect.top -
					  (top_bottom & 0x3ff);
	पूर्ण

	अगर (dev->devtype->product != CODA_DX6) अणु
		u8 profile, level;

		val = coda_पढ़ो(dev, CODA7_RET_DEC_SEQ_HEADER_REPORT);
		profile = val & 0xff;
		level = (val >> 8) & 0x7f;

		अगर (profile || level)
			coda_update_profile_level_ctrls(ctx, profile, level);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम coda_dec_seq_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा coda_ctx *ctx = container_of(work,
					    काष्ठा coda_ctx, seq_init_work);
	काष्ठा coda_dev *dev = ctx->dev;

	mutex_lock(&ctx->buffer_mutex);
	mutex_lock(&dev->coda_mutex);

	अगर (!ctx->initialized)
		__coda_decoder_seq_init(ctx);

	mutex_unlock(&dev->coda_mutex);
	mutex_unlock(&ctx->buffer_mutex);
पूर्ण

अटल पूर्णांक __coda_start_decoding(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_q_data *q_data_src, *q_data_dst;
	काष्ठा coda_dev *dev = ctx->dev;
	u32 src_fourcc, dst_fourcc;
	पूर्णांक ret;

	अगर (!ctx->initialized) अणु
		ret = __coda_decoder_seq_init(ctx);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	src_fourcc = q_data_src->fourcc;
	dst_fourcc = q_data_dst->fourcc;

	coda_ग_लिखो(dev, ctx->parabuf.paddr, CODA_REG_BIT_PARA_BUF_ADDR);

	ret = coda_alloc_framebuffers(ctx, q_data_dst, src_fourcc);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "failed to allocate framebuffers\n");
		वापस ret;
	पूर्ण

	/* Tell the decoder how many frame buffers we allocated. */
	coda_ग_लिखो(dev, ctx->num_पूर्णांकernal_frames, CODA_CMD_SET_FRAME_BUF_NUM);
	coda_ग_लिखो(dev, round_up(q_data_dst->rect.width, 16),
		   CODA_CMD_SET_FRAME_BUF_STRIDE);

	अगर (dev->devtype->product != CODA_DX6) अणु
		/* Set secondary AXI IRAM */
		coda_setup_iram(ctx);

		coda_ग_लिखो(dev, ctx->iram_info.buf_bit_use,
				CODA7_CMD_SET_FRAME_AXI_BIT_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_ip_ac_dc_use,
				CODA7_CMD_SET_FRAME_AXI_IPACDC_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_dbk_y_use,
				CODA7_CMD_SET_FRAME_AXI_DBKY_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_dbk_c_use,
				CODA7_CMD_SET_FRAME_AXI_DBKC_ADDR);
		coda_ग_लिखो(dev, ctx->iram_info.buf_ovl_use,
				CODA7_CMD_SET_FRAME_AXI_OVL_ADDR);
		अगर (dev->devtype->product == CODA_960) अणु
			coda_ग_लिखो(dev, ctx->iram_info.buf_btp_use,
					CODA9_CMD_SET_FRAME_AXI_BTP_ADDR);

			coda_ग_लिखो(dev, -1, CODA9_CMD_SET_FRAME_DELAY);
			coda9_set_frame_cache(ctx, dst_fourcc);
		पूर्ण
	पूर्ण

	अगर (src_fourcc == V4L2_PIX_FMT_H264) अणु
		coda_ग_लिखो(dev, ctx->slicebuf.paddr,
				CODA_CMD_SET_FRAME_SLICE_BB_START);
		coda_ग_लिखो(dev, ctx->slicebuf.size / 1024,
				CODA_CMD_SET_FRAME_SLICE_BB_SIZE);
	पूर्ण

	अगर (dev->devtype->product == CODA_HX4 ||
	    dev->devtype->product == CODA_7541) अणु
		पूर्णांक max_mb_x = 1920 / 16;
		पूर्णांक max_mb_y = 1088 / 16;
		पूर्णांक max_mb_num = max_mb_x * max_mb_y;

		coda_ग_लिखो(dev, max_mb_num << 16 | max_mb_x << 8 | max_mb_y,
				CODA7_CMD_SET_FRAME_MAX_DEC_SIZE);
	पूर्ण अन्यथा अगर (dev->devtype->product == CODA_960) अणु
		पूर्णांक max_mb_x = 1920 / 16;
		पूर्णांक max_mb_y = 1088 / 16;
		पूर्णांक max_mb_num = max_mb_x * max_mb_y;

		coda_ग_लिखो(dev, max_mb_num << 16 | max_mb_x << 8 | max_mb_y,
				CODA9_CMD_SET_FRAME_MAX_DEC_SIZE);
	पूर्ण

	अगर (coda_command_sync(ctx, CODA_COMMAND_SET_FRAME_BUF)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "CODA_COMMAND_SET_FRAME_BUF timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coda_start_decoding(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक ret;

	mutex_lock(&dev->coda_mutex);
	ret = __coda_start_decoding(ctx);
	mutex_unlock(&dev->coda_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक coda_prepare_decode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *dst_buf;
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा coda_q_data *q_data_dst;
	काष्ठा coda_buffer_meta *meta;
	u32 rot_mode = 0;
	u32 reg_addr, reg_stride;

	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	/* Try to copy source buffer contents पूर्णांकo the bitstream ringbuffer */
	mutex_lock(&ctx->bitstream_mutex);
	coda_fill_bitstream(ctx, शून्य);
	mutex_unlock(&ctx->bitstream_mutex);

	अगर (coda_get_bitstream_payload(ctx) < 512 &&
	    (!(ctx->bit_stream_param & CODA_BIT_STREAM_END_FLAG))) अणु
		coda_dbg(1, ctx, "bitstream payload: %d, skipping\n",
			 coda_get_bitstream_payload(ctx));
		v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
		वापस -EAGAIN;
	पूर्ण

	/* Run coda_start_decoding (again) अगर not yet initialized */
	अगर (!ctx->initialized) अणु
		पूर्णांक ret = __coda_start_decoding(ctx);

		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev, "failed to start decoding\n");
			v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
			वापस -EAGAIN;
		पूर्ण अन्यथा अणु
			ctx->initialized = 1;
		पूर्ण
	पूर्ण

	अगर (dev->devtype->product == CODA_960)
		coda_set_gdi_regs(ctx);

	अगर (ctx->use_vकरोa &&
	    ctx->display_idx >= 0 &&
	    ctx->display_idx < ctx->num_पूर्णांकernal_frames) अणु
		vकरोa_device_run(ctx->vकरोa,
				vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0),
				ctx->पूर्णांकernal_frames[ctx->display_idx].buf.paddr);
	पूर्ण अन्यथा अणु
		अगर (dev->devtype->product == CODA_960) अणु
			/*
			 * It was previously assumed that the CODA960 has an
			 * पूर्णांकernal list of 64 buffer entries that contains
			 * both the रेजिस्टरed पूर्णांकernal frame buffers as well
			 * as the rotator buffer output, and that the ROT_INDEX
			 * रेजिस्टर must be set to a value between the last
			 * पूर्णांकernal frame buffers' index and 64.
			 * At least on firmware version 3.1.1 it turns out that
			 * setting ROT_INDEX to any value >= 32 causes CODA
			 * hangups that it can not recover from with the SRC VPU
			 * reset.
			 * It करोes appear to work however, to just set it to a
			 * fixed value in the [ctx->num_पूर्णांकernal_frames, 31]
			 * range, क्रम example CODA_MAX_FRAMEBUFFERS.
			 */
			coda_ग_लिखो(dev, CODA_MAX_FRAMEBUFFERS,
				   CODA9_CMD_DEC_PIC_ROT_INDEX);

			reg_addr = CODA9_CMD_DEC_PIC_ROT_ADDR_Y;
			reg_stride = CODA9_CMD_DEC_PIC_ROT_STRIDE;
		पूर्ण अन्यथा अणु
			reg_addr = CODA_CMD_DEC_PIC_ROT_ADDR_Y;
			reg_stride = CODA_CMD_DEC_PIC_ROT_STRIDE;
		पूर्ण
		coda_ग_लिखो_base(ctx, q_data_dst, dst_buf, reg_addr);
		coda_ग_लिखो(dev, q_data_dst->bytesperline, reg_stride);

		rot_mode = CODA_ROT_MIR_ENABLE | ctx->params.rot_mode;
	पूर्ण

	coda_ग_लिखो(dev, rot_mode, CODA_CMD_DEC_PIC_ROT_MODE);

	चयन (dev->devtype->product) अणु
	हाल CODA_DX6:
		/* TBD */
	हाल CODA_HX4:
	हाल CODA_7541:
		coda_ग_लिखो(dev, CODA_PRE_SCAN_EN, CODA_CMD_DEC_PIC_OPTION);
		अवरोध;
	हाल CODA_960:
		/* 'hardcode to use interrupt disable mode'? */
		coda_ग_लिखो(dev, (1 << 10), CODA_CMD_DEC_PIC_OPTION);
		अवरोध;
	पूर्ण

	coda_ग_लिखो(dev, 0, CODA_CMD_DEC_PIC_SKIP_NUM);

	coda_ग_लिखो(dev, 0, CODA_CMD_DEC_PIC_BB_START);
	coda_ग_लिखो(dev, 0, CODA_CMD_DEC_PIC_START_BYTE);

	अगर (dev->devtype->product != CODA_DX6)
		coda_ग_लिखो(dev, ctx->iram_info.axi_sram_use,
				CODA7_REG_BIT_AXI_SRAM_USE);

	spin_lock(&ctx->buffer_meta_lock);
	meta = list_first_entry_or_null(&ctx->buffer_meta_list,
					काष्ठा coda_buffer_meta, list);

	अगर (meta && ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG) अणु

		/* If this is the last buffer in the bitstream, add padding */
		अगर (meta->end == ctx->bitstream_fअगरo.kfअगरo.in) अणु
			अटल अचिन्हित अक्षर buf[512];
			अचिन्हित पूर्णांक pad;

			/* Pad to multiple of 256 and then add 256 more */
			pad = ((0 - meta->end) & 0xff) + 256;

			स_रखो(buf, 0xff, माप(buf));

			kfअगरo_in(&ctx->bitstream_fअगरo, buf, pad);
		पूर्ण
	पूर्ण
	spin_unlock(&ctx->buffer_meta_lock);

	coda_kfअगरo_sync_to_device_full(ctx);

	/* Clear decode success flag */
	coda_ग_लिखो(dev, 0, CODA_RET_DEC_PIC_SUCCESS);

	/* Clear error वापस value */
	coda_ग_लिखो(dev, 0, CODA_RET_DEC_PIC_ERR_MB);

	trace_coda_dec_pic_run(ctx, meta);

	coda_command_async(ctx, CODA_COMMAND_PIC_RUN);

	वापस 0;
पूर्ण

अटल व्योम coda_finish_decode(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा coda_q_data *q_data_src;
	काष्ठा coda_q_data *q_data_dst;
	काष्ठा vb2_v4l2_buffer *dst_buf;
	काष्ठा coda_buffer_meta *meta;
	पूर्णांक width, height;
	पूर्णांक decoded_idx;
	पूर्णांक display_idx;
	काष्ठा coda_पूर्णांकernal_frame *decoded_frame = शून्य;
	u32 src_fourcc;
	पूर्णांक success;
	u32 err_mb;
	पूर्णांक err_vकरोa = 0;
	u32 val;

	अगर (ctx->पातing)
		वापस;

	/* Update kfअगरo out poपूर्णांकer from coda bitstream पढ़ो poपूर्णांकer */
	coda_kfअगरo_sync_from_device(ctx);

	/*
	 * in stream-end mode, the पढ़ो poपूर्णांकer can overshoot the ग_लिखो poपूर्णांकer
	 * by up to 512 bytes
	 */
	अगर (ctx->bit_stream_param & CODA_BIT_STREAM_END_FLAG) अणु
		अगर (coda_get_bitstream_payload(ctx) >= ctx->bitstream.size - 512)
			kfअगरo_init(&ctx->bitstream_fअगरo,
				ctx->bitstream.vaddr, ctx->bitstream.size);
	पूर्ण

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	src_fourcc = q_data_src->fourcc;

	val = coda_पढ़ो(dev, CODA_RET_DEC_PIC_SUCCESS);
	अगर (val != 1)
		pr_err("DEC_PIC_SUCCESS = %d\n", val);

	success = val & 0x1;
	अगर (!success)
		v4l2_err(&dev->v4l2_dev, "decode failed\n");

	अगर (src_fourcc == V4L2_PIX_FMT_H264) अणु
		अगर (val & (1 << 3))
			v4l2_err(&dev->v4l2_dev,
				 "insufficient PS buffer space (%d bytes)\n",
				 ctx->psbuf.size);
		अगर (val & (1 << 2))
			v4l2_err(&dev->v4l2_dev,
				 "insufficient slice buffer space (%d bytes)\n",
				 ctx->slicebuf.size);
	पूर्ण

	val = coda_पढ़ो(dev, CODA_RET_DEC_PIC_SIZE);
	width = (val >> 16) & 0xffff;
	height = val & 0xffff;

	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	/* frame crop inक्रमmation */
	अगर (src_fourcc == V4L2_PIX_FMT_H264) अणु
		u32 left_right;
		u32 top_bottom;

		left_right = coda_पढ़ो(dev, CODA_RET_DEC_PIC_CROP_LEFT_RIGHT);
		top_bottom = coda_पढ़ो(dev, CODA_RET_DEC_PIC_CROP_TOP_BOTTOM);

		अगर (left_right == 0xffffffff && top_bottom == 0xffffffff) अणु
			/* Keep current crop inक्रमmation */
		पूर्ण अन्यथा अणु
			काष्ठा v4l2_rect *rect = &q_data_dst->rect;

			rect->left = left_right >> 16 & 0xffff;
			rect->top = top_bottom >> 16 & 0xffff;
			rect->width = width - rect->left -
				      (left_right & 0xffff);
			rect->height = height - rect->top -
				       (top_bottom & 0xffff);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* no cropping */
	पूर्ण

	err_mb = coda_पढ़ो(dev, CODA_RET_DEC_PIC_ERR_MB);
	अगर (err_mb > 0) अणु
		अगर (__ratelimit(&dev->mb_err_rs))
			coda_dbg(1, ctx, "errors in %d macroblocks\n", err_mb);
		v4l2_ctrl_s_ctrl(ctx->mb_err_cnt_ctrl,
				 v4l2_ctrl_g_ctrl(ctx->mb_err_cnt_ctrl) + err_mb);
	पूर्ण

	अगर (dev->devtype->product == CODA_HX4 ||
	    dev->devtype->product == CODA_7541) अणु
		val = coda_पढ़ो(dev, CODA_RET_DEC_PIC_OPTION);
		अगर (val == 0) अणु
			/* not enough bitstream data */
			coda_dbg(1, ctx, "prescan failed: %d\n", val);
			ctx->hold = true;
			वापस;
		पूर्ण
	पूर्ण

	/* Wait until the VDOA finished writing the previous display frame */
	अगर (ctx->use_vकरोa &&
	    ctx->display_idx >= 0 &&
	    ctx->display_idx < ctx->num_पूर्णांकernal_frames) अणु
		err_vकरोa = vकरोa_रुको_क्रम_completion(ctx->vकरोa);
	पूर्ण

	ctx->frm_dis_flg = coda_पढ़ो(dev,
				     CODA_REG_BIT_FRM_DIS_FLG(ctx->reg_idx));

	/* The previous display frame was copied out and can be overwritten */
	अगर (ctx->display_idx >= 0 &&
	    ctx->display_idx < ctx->num_पूर्णांकernal_frames) अणु
		ctx->frm_dis_flg &= ~(1 << ctx->display_idx);
		coda_ग_लिखो(dev, ctx->frm_dis_flg,
				CODA_REG_BIT_FRM_DIS_FLG(ctx->reg_idx));
	पूर्ण

	/*
	 * The index of the last decoded frame, not necessarily in
	 * display order, and the index of the next display frame.
	 * The latter could have been decoded in a previous run.
	 */
	decoded_idx = coda_पढ़ो(dev, CODA_RET_DEC_PIC_CUR_IDX);
	display_idx = coda_पढ़ो(dev, CODA_RET_DEC_PIC_FRAME_IDX);

	अगर (decoded_idx == -1) अणु
		/* no frame was decoded, but we might have a display frame */
		अगर (display_idx >= 0 && display_idx < ctx->num_पूर्णांकernal_frames)
			ctx->sequence_offset++;
		अन्यथा अगर (ctx->display_idx < 0)
			ctx->hold = true;
	पूर्ण अन्यथा अगर (decoded_idx == -2) अणु
		अगर (ctx->display_idx >= 0 &&
		    ctx->display_idx < ctx->num_पूर्णांकernal_frames)
			ctx->sequence_offset++;
		/* no frame was decoded, we still वापस reमुख्यing buffers */
	पूर्ण अन्यथा अगर (decoded_idx < 0 || decoded_idx >= ctx->num_पूर्णांकernal_frames) अणु
		v4l2_err(&dev->v4l2_dev,
			 "decoded frame index out of range: %d\n", decoded_idx);
	पूर्ण अन्यथा अणु
		पूर्णांक sequence;

		decoded_frame = &ctx->पूर्णांकernal_frames[decoded_idx];

		val = coda_पढ़ो(dev, CODA_RET_DEC_PIC_FRAME_NUM);
		अगर (ctx->sequence_offset == -1)
			ctx->sequence_offset = val;

		sequence = val + ctx->first_frame_sequence
			       - ctx->sequence_offset;
		spin_lock(&ctx->buffer_meta_lock);
		अगर (!list_empty(&ctx->buffer_meta_list)) अणु
			meta = list_first_entry(&ctx->buffer_meta_list,
					      काष्ठा coda_buffer_meta, list);
			list_del(&meta->list);
			ctx->num_metas--;
			spin_unlock(&ctx->buffer_meta_lock);
			/*
			 * Clamp counters to 16 bits क्रम comparison, as the HW
			 * counter rolls over at this poपूर्णांक क्रम h.264. This
			 * may be dअगरferent क्रम other क्रमmats, but using 16 bits
			 * should be enough to detect most errors and saves us
			 * from करोing dअगरferent things based on the क्रमmat.
			 */
			अगर ((sequence & 0xffff) != (meta->sequence & 0xffff)) अणु
				v4l2_err(&dev->v4l2_dev,
					 "sequence number mismatch (%d(%d) != %d)\n",
					 sequence, ctx->sequence_offset,
					 meta->sequence);
			पूर्ण
			decoded_frame->meta = *meta;
			kमुक्त(meta);
		पूर्ण अन्यथा अणु
			spin_unlock(&ctx->buffer_meta_lock);
			v4l2_err(&dev->v4l2_dev, "empty timestamp list!\n");
			स_रखो(&decoded_frame->meta, 0,
			       माप(काष्ठा coda_buffer_meta));
			decoded_frame->meta.sequence = sequence;
			decoded_frame->meta.last = false;
			ctx->sequence_offset++;
		पूर्ण

		trace_coda_dec_pic_करोne(ctx, &decoded_frame->meta);

		val = coda_पढ़ो(dev, CODA_RET_DEC_PIC_TYPE) & 0x7;
		decoded_frame->type = (val == 0) ? V4L2_BUF_FLAG_KEYFRAME :
				      (val == 1) ? V4L2_BUF_FLAG_PFRAME :
						   V4L2_BUF_FLAG_BFRAME;

		decoded_frame->error = err_mb;
	पूर्ण

	अगर (display_idx == -1) अणु
		/*
		 * no more frames to be decoded, but there could still
		 * be rotator output to dequeue
		 */
		ctx->hold = true;
	पूर्ण अन्यथा अगर (display_idx == -3) अणु
		/* possibly prescan failure */
	पूर्ण अन्यथा अगर (display_idx < 0 || display_idx >= ctx->num_पूर्णांकernal_frames) अणु
		v4l2_err(&dev->v4l2_dev,
			 "presentation frame index out of range: %d\n",
			 display_idx);
	पूर्ण

	/* If a frame was copied out, वापस it */
	अगर (ctx->display_idx >= 0 &&
	    ctx->display_idx < ctx->num_पूर्णांकernal_frames) अणु
		काष्ठा coda_पूर्णांकernal_frame *पढ़ोy_frame;

		पढ़ोy_frame = &ctx->पूर्णांकernal_frames[ctx->display_idx];

		dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		dst_buf->sequence = ctx->osequence++;

		dst_buf->field = V4L2_FIELD_NONE;
		dst_buf->flags &= ~(V4L2_BUF_FLAG_KEYFRAME |
					     V4L2_BUF_FLAG_PFRAME |
					     V4L2_BUF_FLAG_BFRAME);
		dst_buf->flags |= पढ़ोy_frame->type;
		meta = &पढ़ोy_frame->meta;
		अगर (meta->last && !coda_reorder_enable(ctx)) अणु
			/*
			 * If this was the last decoded frame, and reordering
			 * is disabled, this will be the last display frame.
			 */
			coda_dbg(1, ctx, "last meta, marking as last frame\n");
			dst_buf->flags |= V4L2_BUF_FLAG_LAST;
		पूर्ण अन्यथा अगर (ctx->bit_stream_param & CODA_BIT_STREAM_END_FLAG &&
			   display_idx == -1) अणु
			/*
			 * If there is no designated presentation frame anymore,
			 * this frame has to be the last one.
			 */
			coda_dbg(1, ctx,
				 "no more frames to return, marking as last frame\n");
			dst_buf->flags |= V4L2_BUF_FLAG_LAST;
		पूर्ण
		dst_buf->समयcode = meta->समयcode;
		dst_buf->vb2_buf.बारtamp = meta->बारtamp;

		trace_coda_dec_rot_करोne(ctx, dst_buf, meta);

		vb2_set_plane_payload(&dst_buf->vb2_buf, 0,
				      q_data_dst->sizeimage);

		अगर (पढ़ोy_frame->error || err_vकरोa)
			coda_m2m_buf_करोne(ctx, dst_buf, VB2_BUF_STATE_ERROR);
		अन्यथा
			coda_m2m_buf_करोne(ctx, dst_buf, VB2_BUF_STATE_DONE);

		अगर (decoded_frame) अणु
			coda_dbg(1, ctx, "job finished: decoded %c frame %u, returned %c frame %u (%u/%u)%s\n",
				 coda_frame_type_अक्षर(decoded_frame->type),
				 decoded_frame->meta.sequence,
				 coda_frame_type_अक्षर(dst_buf->flags),
				 पढ़ोy_frame->meta.sequence,
				 dst_buf->sequence, ctx->qsequence,
				 (dst_buf->flags & V4L2_BUF_FLAG_LAST) ?
				 " (last)" : "");
		पूर्ण अन्यथा अणु
			coda_dbg(1, ctx, "job finished: no frame decoded (%d), returned %c frame %u (%u/%u)%s\n",
				 decoded_idx,
				 coda_frame_type_अक्षर(dst_buf->flags),
				 पढ़ोy_frame->meta.sequence,
				 dst_buf->sequence, ctx->qsequence,
				 (dst_buf->flags & V4L2_BUF_FLAG_LAST) ?
				 " (last)" : "");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (decoded_frame) अणु
			coda_dbg(1, ctx, "job finished: decoded %c frame %u, no frame returned (%d)\n",
				 coda_frame_type_अक्षर(decoded_frame->type),
				 decoded_frame->meta.sequence,
				 ctx->display_idx);
		पूर्ण अन्यथा अणु
			coda_dbg(1, ctx, "job finished: no frame decoded (%d) or returned (%d)\n",
				 decoded_idx, ctx->display_idx);
		पूर्ण
	पूर्ण

	/* The rotator will copy the current display frame next समय */
	ctx->display_idx = display_idx;

	/*
	 * The current decode run might have brought the bitstream fill level
	 * below the size where we can start the next decode run. As userspace
	 * might have filled the output queue completely and might thus be
	 * blocked, we can't rely on the next qbuf to trigger the bitstream
	 * refill. Check अगर we have data to refill the bitstream now.
	 */
	mutex_lock(&ctx->bitstream_mutex);
	coda_fill_bitstream(ctx, शून्य);
	mutex_unlock(&ctx->bitstream_mutex);
पूर्ण

अटल व्योम coda_decode_समयout(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *dst_buf;

	/*
	 * For now this only handles the हाल where we would deadlock with
	 * userspace, i.e. userspace issued DEC_CMD_STOP and रुकोs क्रम EOS,
	 * but after a failed decode run we would hold the context and रुको क्रम
	 * userspace to queue more buffers.
	 */
	अगर (!(ctx->bit_stream_param & CODA_BIT_STREAM_END_FLAG))
		वापस;

	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf->sequence = ctx->qsequence - 1;

	coda_m2m_buf_करोne(ctx, dst_buf, VB2_BUF_STATE_ERROR);
पूर्ण

स्थिर काष्ठा coda_context_ops coda_bit_decode_ops = अणु
	.queue_init = coda_decoder_queue_init,
	.reqbufs = coda_decoder_reqbufs,
	.start_streaming = coda_start_decoding,
	.prepare_run = coda_prepare_decode,
	.finish_run = coda_finish_decode,
	.run_समयout = coda_decode_समयout,
	.seq_init_work = coda_dec_seq_init_work,
	.seq_end_work = coda_seq_end_work,
	.release = coda_bit_release,
पूर्ण;

irqवापस_t coda_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा coda_dev *dev = data;
	काष्ठा coda_ctx *ctx;

	/* पढ़ो status रेजिस्टर to attend the IRQ */
	coda_पढ़ो(dev, CODA_REG_BIT_INT_STATUS);
	coda_ग_लिखो(dev, 0, CODA_REG_BIT_INT_REASON);
	coda_ग_लिखो(dev, CODA_REG_BIT_INT_CLEAR_SET,
		      CODA_REG_BIT_INT_CLEAR);

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	अगर (ctx == शून्य) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Instance released before the end of transaction\n");
		वापस IRQ_HANDLED;
	पूर्ण

	trace_coda_bit_करोne(ctx);

	अगर (ctx->पातing) अणु
		coda_dbg(1, ctx, "task has been aborted\n");
	पूर्ण

	अगर (coda_isbusy(ctx->dev)) अणु
		coda_dbg(1, ctx, "coda is still busy!!!!\n");
		वापस IRQ_NONE;
	पूर्ण

	complete(&ctx->completion);

	वापस IRQ_HANDLED;
पूर्ण
