<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 *         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_dec.h"
#समावेश "mtk_vcodec_intr.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "vdec_drv_if.h"
#समावेश "mtk_vcodec_dec_pm.h"

#घोषणा OUT_FMT_IDX	0
#घोषणा CAP_FMT_IDX	3

#घोषणा MTK_VDEC_MIN_W	64U
#घोषणा MTK_VDEC_MIN_H	64U
#घोषणा DFT_CFG_WIDTH	MTK_VDEC_MIN_W
#घोषणा DFT_CFG_HEIGHT	MTK_VDEC_MIN_H

अटल स्थिर काष्ठा mtk_video_fmt mtk_video_क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_H264,
		.type = MTK_FMT_DEC,
		.num_planes = 1,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_VP8,
		.type = MTK_FMT_DEC,
		.num_planes = 1,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_VP9,
		.type = MTK_FMT_DEC,
		.num_planes = 1,
		.flags = V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_MT21C,
		.type = MTK_FMT_FRAME,
		.num_planes = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_codec_framesizes mtk_vdec_framesizes[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_H264,
		.stepwise = अणु  MTK_VDEC_MIN_W, MTK_VDEC_MAX_W, 16,
				MTK_VDEC_MIN_H, MTK_VDEC_MAX_H, 16 पूर्ण,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_VP8,
		.stepwise = अणु  MTK_VDEC_MIN_W, MTK_VDEC_MAX_W, 16,
				MTK_VDEC_MIN_H, MTK_VDEC_MAX_H, 16 पूर्ण,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_VP9,
		.stepwise = अणु  MTK_VDEC_MIN_W, MTK_VDEC_MAX_W, 16,
				MTK_VDEC_MIN_H, MTK_VDEC_MAX_H, 16 पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा NUM_SUPPORTED_FRAMESIZE ARRAY_SIZE(mtk_vdec_framesizes)
#घोषणा NUM_FORMATS ARRAY_SIZE(mtk_video_क्रमmats)

अटल स्थिर काष्ठा mtk_video_fmt *mtk_vdec_find_क्रमmat(काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NUM_FORMATS; k++) अणु
		fmt = &mtk_video_क्रमmats[k];
		अगर (fmt->fourcc == f->fmt.pix_mp.pixelक्रमmat)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mtk_q_data *mtk_vdec_get_q_data(काष्ठा mtk_vcodec_ctx *ctx,
					      क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->q_data[MTK_Q_DATA_SRC];

	वापस &ctx->q_data[MTK_Q_DATA_DST];
पूर्ण

/*
 * This function tries to clean all display buffers, the buffers will वापस
 * in display order.
 * Note the buffers वापसed from codec driver may still be in driver's
 * reference list.
 */
अटल काष्ठा vb2_buffer *get_display_buffer(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा vdec_fb *disp_frame_buffer = शून्य;
	काष्ठा mtk_video_dec_buf *dstbuf;
	काष्ठा vb2_v4l2_buffer *vb;

	mtk_v4l2_debug(3, "[%d]", ctx->id);
	अगर (vdec_अगर_get_param(ctx,
			GET_PARAM_DISP_FRAME_BUFFER,
			&disp_frame_buffer)) अणु
		mtk_v4l2_err("[%d]Cannot get param : GET_PARAM_DISP_FRAME_BUFFER",
			ctx->id);
		वापस शून्य;
	पूर्ण

	अगर (disp_frame_buffer == शून्य) अणु
		mtk_v4l2_debug(3, "No display frame buffer");
		वापस शून्य;
	पूर्ण

	dstbuf = container_of(disp_frame_buffer, काष्ठा mtk_video_dec_buf,
				frame_buffer);
	vb = &dstbuf->m2m_buf.vb;
	mutex_lock(&ctx->lock);
	अगर (dstbuf->used) अणु
		vb2_set_plane_payload(&vb->vb2_buf, 0,
				      ctx->picinfo.fb_sz[0]);
		अगर (ctx->q_data[MTK_Q_DATA_DST].fmt->num_planes == 2)
			vb2_set_plane_payload(&vb->vb2_buf, 1,
					      ctx->picinfo.fb_sz[1]);

		mtk_v4l2_debug(2,
				"[%d]status=%x queue id=%d to done_list %d",
				ctx->id, disp_frame_buffer->status,
				vb->vb2_buf.index,
				dstbuf->queued_in_vb2);

		v4l2_m2m_buf_करोne(vb, VB2_BUF_STATE_DONE);
		ctx->decoded_frame_cnt++;
	पूर्ण
	mutex_unlock(&ctx->lock);
	वापस &vb->vb2_buf;
पूर्ण

/*
 * This function tries to clean all capture buffers that are not used as
 * reference buffers by codec driver any more
 * In this हाल, we need re-queue buffer to vb2 buffer अगर user space
 * alपढ़ोy वापसs this buffer to v4l2 or this buffer is just the output of
 * previous sps/pps/resolution change decode, or करो nothing अगर user
 * space still owns this buffer
 */
अटल काष्ठा vb2_buffer *get_मुक्त_buffer(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा mtk_video_dec_buf *dstbuf;
	काष्ठा vdec_fb *मुक्त_frame_buffer = शून्य;
	काष्ठा vb2_v4l2_buffer *vb;

	अगर (vdec_अगर_get_param(ctx,
				GET_PARAM_FREE_FRAME_BUFFER,
				&मुक्त_frame_buffer)) अणु
		mtk_v4l2_err("[%d] Error!! Cannot get param", ctx->id);
		वापस शून्य;
	पूर्ण
	अगर (मुक्त_frame_buffer == शून्य) अणु
		mtk_v4l2_debug(3, " No free frame buffer");
		वापस शून्य;
	पूर्ण

	mtk_v4l2_debug(3, "[%d] tmp_frame_addr = 0x%p",
			ctx->id, मुक्त_frame_buffer);

	dstbuf = container_of(मुक्त_frame_buffer, काष्ठा mtk_video_dec_buf,
				frame_buffer);
	vb = &dstbuf->m2m_buf.vb;

	mutex_lock(&ctx->lock);
	अगर (dstbuf->used) अणु
		अगर ((dstbuf->queued_in_vb2) &&
		    (dstbuf->queued_in_v4l2) &&
		    (मुक्त_frame_buffer->status == FB_ST_FREE)) अणु
			/*
			 * After decode sps/pps or non-display buffer, we करोn't
			 * need to वापस capture buffer to user space, but
			 * just re-queue this capture buffer to vb2 queue.
			 * This reduce overheads that dq/q unused capture
			 * buffer. In this हाल, queued_in_vb2 = true.
			 */
			mtk_v4l2_debug(2,
				"[%d]status=%x queue id=%d to rdy_queue %d",
				ctx->id, मुक्त_frame_buffer->status,
				vb->vb2_buf.index,
				dstbuf->queued_in_vb2);
			v4l2_m2m_buf_queue(ctx->m2m_ctx, vb);
		पूर्ण अन्यथा अगर (!dstbuf->queued_in_vb2 && dstbuf->queued_in_v4l2) अणु
			/*
			 * If buffer in v4l2 driver but not in vb2 queue yet,
			 * and we get this buffer from मुक्त_list, it means
			 * that codec driver करो not use this buffer as
			 * reference buffer anymore. We should q buffer to vb2
			 * queue, so later work thपढ़ो could get this buffer
			 * क्रम decode. In this हाल, queued_in_vb2 = false
			 * means this buffer is not from previous decode
			 * output.
			 */
			mtk_v4l2_debug(2,
					"[%d]status=%x queue id=%d to rdy_queue",
					ctx->id, मुक्त_frame_buffer->status,
					vb->vb2_buf.index);
			v4l2_m2m_buf_queue(ctx->m2m_ctx, vb);
			dstbuf->queued_in_vb2 = true;
		पूर्ण अन्यथा अणु
			/*
			 * Codec driver करो not need to reference this capture
			 * buffer and this buffer is not in v4l2 driver.
			 * Then we करोn't need to करो any thing, just add log when
			 * we need to debug buffer flow.
			 * When this buffer q from user space, it could
			 * directly q to vb2 buffer
			 */
			mtk_v4l2_debug(3, "[%d]status=%x err queue id=%d %d %d",
					ctx->id, मुक्त_frame_buffer->status,
					vb->vb2_buf.index,
					dstbuf->queued_in_vb2,
					dstbuf->queued_in_v4l2);
		पूर्ण
		dstbuf->used = false;
	पूर्ण
	mutex_unlock(&ctx->lock);
	वापस &vb->vb2_buf;
पूर्ण

अटल व्योम clean_display_buffer(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा vb2_buffer *framptr;

	करो अणु
		framptr = get_display_buffer(ctx);
	पूर्ण जबतक (framptr);
पूर्ण

अटल व्योम clean_मुक्त_buffer(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा vb2_buffer *framptr;

	करो अणु
		framptr = get_मुक्त_buffer(ctx);
	पूर्ण जबतक (framptr);
पूर्ण

अटल व्योम mtk_vdec_queue_res_chg_event(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	अटल स्थिर काष्ठा v4l2_event ev_src_ch = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes =
		V4L2_EVENT_SRC_CH_RESOLUTION,
	पूर्ण;

	mtk_v4l2_debug(1, "[%d]", ctx->id);
	v4l2_event_queue_fh(&ctx->fh, &ev_src_ch);
पूर्ण

अटल व्योम mtk_vdec_flush_decoder(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	bool res_chg;
	पूर्णांक ret = 0;

	ret = vdec_अगर_decode(ctx, शून्य, शून्य, &res_chg);
	अगर (ret)
		mtk_v4l2_err("DecodeFinal failed, ret=%d", ret);

	clean_display_buffer(ctx);
	clean_मुक्त_buffer(ctx);
पूर्ण

अटल व्योम mtk_vdec_update_fmt(काष्ठा mtk_vcodec_ctx *ctx,
				अचिन्हित पूर्णांक pixelक्रमmat)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;
	काष्ठा mtk_q_data *dst_q_data;
	अचिन्हित पूर्णांक k;

	dst_q_data = &ctx->q_data[MTK_Q_DATA_DST];
	क्रम (k = 0; k < NUM_FORMATS; k++) अणु
		fmt = &mtk_video_क्रमmats[k];
		अगर (fmt->fourcc == pixelक्रमmat) अणु
			mtk_v4l2_debug(1, "Update cap fourcc(%d -> %d)",
				dst_q_data->fmt->fourcc, pixelक्रमmat);
			dst_q_data->fmt = fmt;
			वापस;
		पूर्ण
	पूर्ण

	mtk_v4l2_err("Cannot get fourcc(%d), using init value", pixelक्रमmat);
पूर्ण

अटल पूर्णांक mtk_vdec_pic_info_update(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	अचिन्हित पूर्णांक dpbsize = 0;
	पूर्णांक ret;

	अगर (vdec_अगर_get_param(ctx,
				GET_PARAM_PIC_INFO,
				&ctx->last_decoded_picinfo)) अणु
		mtk_v4l2_err("[%d]Error!! Cannot get param : GET_PARAM_PICTURE_INFO ERR",
				ctx->id);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->last_decoded_picinfo.pic_w == 0 ||
		ctx->last_decoded_picinfo.pic_h == 0 ||
		ctx->last_decoded_picinfo.buf_w == 0 ||
		ctx->last_decoded_picinfo.buf_h == 0) अणु
		mtk_v4l2_err("Cannot get correct pic info");
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->last_decoded_picinfo.cap_fourcc != ctx->picinfo.cap_fourcc &&
		ctx->picinfo.cap_fourcc != 0)
		mtk_vdec_update_fmt(ctx, ctx->picinfo.cap_fourcc);

	अगर ((ctx->last_decoded_picinfo.pic_w == ctx->picinfo.pic_w) ||
	    (ctx->last_decoded_picinfo.pic_h == ctx->picinfo.pic_h))
		वापस 0;

	mtk_v4l2_debug(1,
			"[%d]-> new(%d,%d), old(%d,%d), real(%d,%d)",
			ctx->id, ctx->last_decoded_picinfo.pic_w,
			ctx->last_decoded_picinfo.pic_h,
			ctx->picinfo.pic_w, ctx->picinfo.pic_h,
			ctx->last_decoded_picinfo.buf_w,
			ctx->last_decoded_picinfo.buf_h);

	ret = vdec_अगर_get_param(ctx, GET_PARAM_DPB_SIZE, &dpbsize);
	अगर (dpbsize == 0)
		mtk_v4l2_err("Incorrect dpb size, ret=%d", ret);

	ctx->dpb_size = dpbsize;

	वापस ret;
पूर्ण

अटल व्योम mtk_vdec_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = container_of(work, काष्ठा mtk_vcodec_ctx,
				decode_work);
	काष्ठा mtk_vcodec_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा mtk_vcodec_mem buf;
	काष्ठा vdec_fb *pfb;
	bool res_chg = false;
	पूर्णांक ret;
	काष्ठा mtk_video_dec_buf *dst_buf_info, *src_buf_info;

	src_buf = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	अगर (src_buf == शून्य) अणु
		v4l2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4l2_debug(1, "[%d] src_buf empty!!", ctx->id);
		वापस;
	पूर्ण

	dst_buf = v4l2_m2m_next_dst_buf(ctx->m2m_ctx);
	अगर (dst_buf == शून्य) अणु
		v4l2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4l2_debug(1, "[%d] dst_buf empty!!", ctx->id);
		वापस;
	पूर्ण

	src_buf_info = container_of(src_buf, काष्ठा mtk_video_dec_buf,
				    m2m_buf.vb);
	dst_buf_info = container_of(dst_buf, काष्ठा mtk_video_dec_buf,
				    m2m_buf.vb);

	pfb = &dst_buf_info->frame_buffer;
	pfb->base_y.va = vb2_plane_vaddr(&dst_buf->vb2_buf, 0);
	pfb->base_y.dma_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	pfb->base_y.size = ctx->picinfo.fb_sz[0];

	pfb->base_c.va = vb2_plane_vaddr(&dst_buf->vb2_buf, 1);
	pfb->base_c.dma_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 1);
	pfb->base_c.size = ctx->picinfo.fb_sz[1];
	pfb->status = 0;
	mtk_v4l2_debug(3, "===>[%d] vdec_if_decode() ===>", ctx->id);

	mtk_v4l2_debug(3,
			"id=%d Framebuf  pfb=%p VA=%p Y_DMA=%pad C_DMA=%pad Size=%zx",
			dst_buf->vb2_buf.index, pfb,
			pfb->base_y.va, &pfb->base_y.dma_addr,
			&pfb->base_c.dma_addr, pfb->base_y.size);

	अगर (src_buf_info->lastframe) अणु
		mtk_v4l2_debug(1, "Got empty flush input buffer.");
		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);

		/* update dst buf status */
		dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);
		mutex_lock(&ctx->lock);
		dst_buf_info->used = false;
		mutex_unlock(&ctx->lock);

		vdec_अगर_decode(ctx, शून्य, शून्य, &res_chg);
		clean_display_buffer(ctx);
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, 0);
		अगर (ctx->q_data[MTK_Q_DATA_DST].fmt->num_planes == 2)
			vb2_set_plane_payload(&dst_buf->vb2_buf, 1, 0);
		dst_buf->flags |= V4L2_BUF_FLAG_LAST;
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);
		clean_मुक्त_buffer(ctx);
		v4l2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		वापस;
	पूर्ण
	buf.va = vb2_plane_vaddr(&src_buf->vb2_buf, 0);
	buf.dma_addr = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	buf.size = (माप_प्रकार)src_buf->vb2_buf.planes[0].bytesused;
	अगर (!buf.va) अणु
		v4l2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4l2_err("[%d] id=%d src_addr is NULL!!",
				ctx->id, src_buf->vb2_buf.index);
		वापस;
	पूर्ण
	mtk_v4l2_debug(3, "[%d] Bitstream VA=%p DMA=%pad Size=%zx vb=%p",
			ctx->id, buf.va, &buf.dma_addr, buf.size, src_buf);
	dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;
	dst_buf->समयcode = src_buf->समयcode;
	mutex_lock(&ctx->lock);
	dst_buf_info->used = true;
	mutex_unlock(&ctx->lock);
	src_buf_info->used = true;

	ret = vdec_अगर_decode(ctx, &buf, pfb, &res_chg);

	अगर (ret) अणु
		mtk_v4l2_err(
			" <===[%d], src_buf[%d] sz=0x%zx pts=%llu dst_buf[%d] vdec_if_decode() ret=%d res_chg=%d===>",
			ctx->id,
			src_buf->vb2_buf.index,
			buf.size,
			src_buf->vb2_buf.बारtamp,
			dst_buf->vb2_buf.index,
			ret, res_chg);
		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
		अगर (ret == -EIO) अणु
			mutex_lock(&ctx->lock);
			src_buf_info->error = true;
			mutex_unlock(&ctx->lock);
		पूर्ण
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अगर (!res_chg) अणु
		/*
		 * we only वापस src buffer with VB2_BUF_STATE_DONE
		 * when decode success without resolution change
		 */
		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);
	clean_display_buffer(ctx);
	clean_मुक्त_buffer(ctx);

	अगर (!ret && res_chg) अणु
		mtk_vdec_pic_info_update(ctx);
		/*
		 * On encountering a resolution change in the stream.
		 * The driver must first process and decode all
		 * reमुख्यing buffers from beक्रमe the resolution change
		 * poपूर्णांक, so call flush decode here
		 */
		mtk_vdec_flush_decoder(ctx);
		/*
		 * After all buffers containing decoded frames from
		 * beक्रमe the resolution change poपूर्णांक पढ़ोy to be
		 * dequeued on the CAPTURE queue, the driver sends a
		 * V4L2_EVENT_SOURCE_CHANGE event क्रम source change
		 * type V4L2_EVENT_SRC_CH_RESOLUTION
		 */
		mtk_vdec_queue_res_chg_event(ctx);
	पूर्ण
	v4l2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
पूर्ण

अटल पूर्णांक vidioc_try_decoder_cmd(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_decoder_cmd *cmd)
अणु
	चयन (cmd->cmd) अणु
	हाल V4L2_DEC_CMD_STOP:
	हाल V4L2_DEC_CMD_START:
		अगर (cmd->flags != 0) अणु
			mtk_v4l2_err("cmd->flags=%u", cmd->flags);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_decoder_cmd(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_decoder_cmd *cmd)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा vb2_queue *src_vq, *dst_vq;
	पूर्णांक ret;

	ret = vidioc_try_decoder_cmd(file, priv, cmd);
	अगर (ret)
		वापस ret;

	mtk_v4l2_debug(1, "decoder cmd=%u", cmd->cmd);
	dst_vq = v4l2_m2m_get_vq(ctx->m2m_ctx,
				V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	चयन (cmd->cmd) अणु
	हाल V4L2_DEC_CMD_STOP:
		src_vq = v4l2_m2m_get_vq(ctx->m2m_ctx,
				V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		अगर (!vb2_is_streaming(src_vq)) अणु
			mtk_v4l2_debug(1, "Output stream is off. No need to flush.");
			वापस 0;
		पूर्ण
		अगर (!vb2_is_streaming(dst_vq)) अणु
			mtk_v4l2_debug(1, "Capture stream is off. No need to flush.");
			वापस 0;
		पूर्ण
		v4l2_m2m_buf_queue(ctx->m2m_ctx,
				   &ctx->empty_flush_buf->m2m_buf.vb);
		v4l2_m2m_try_schedule(ctx->m2m_ctx);
		अवरोध;

	हाल V4L2_DEC_CMD_START:
		vb2_clear_last_buffer_dequeued(dst_vq);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mtk_vdec_unlock(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	mutex_unlock(&ctx->dev->dec_mutex);
पूर्ण

व्योम mtk_vdec_lock(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	mutex_lock(&ctx->dev->dec_mutex);
पूर्ण

व्योम mtk_vcodec_dec_release(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	vdec_अगर_deinit(ctx);
	ctx->state = MTK_STATE_FREE;
पूर्ण

व्योम mtk_vcodec_dec_set_शेष_params(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा mtk_q_data *q_data;

	ctx->m2m_ctx->q_lock = &ctx->dev->dev_mutex;
	ctx->fh.m2m_ctx = ctx->m2m_ctx;
	ctx->fh.ctrl_handler = &ctx->ctrl_hdl;
	INIT_WORK(&ctx->decode_work, mtk_vdec_worker);
	ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	ctx->quantization = V4L2_QUANTIZATION_DEFAULT;
	ctx->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	q_data = &ctx->q_data[MTK_Q_DATA_SRC];
	स_रखो(q_data, 0, माप(काष्ठा mtk_q_data));
	q_data->visible_width = DFT_CFG_WIDTH;
	q_data->visible_height = DFT_CFG_HEIGHT;
	q_data->fmt = &mtk_video_क्रमmats[OUT_FMT_IDX];
	q_data->field = V4L2_FIELD_NONE;

	q_data->sizeimage[0] = DFT_CFG_WIDTH * DFT_CFG_HEIGHT;
	q_data->bytesperline[0] = 0;

	q_data = &ctx->q_data[MTK_Q_DATA_DST];
	स_रखो(q_data, 0, माप(काष्ठा mtk_q_data));
	q_data->visible_width = DFT_CFG_WIDTH;
	q_data->visible_height = DFT_CFG_HEIGHT;
	q_data->coded_width = DFT_CFG_WIDTH;
	q_data->coded_height = DFT_CFG_HEIGHT;
	q_data->fmt = &mtk_video_क्रमmats[CAP_FMT_IDX];
	q_data->field = V4L2_FIELD_NONE;

	v4l_bound_align_image(&q_data->coded_width,
				MTK_VDEC_MIN_W,
				MTK_VDEC_MAX_W, 4,
				&q_data->coded_height,
				MTK_VDEC_MIN_H,
				MTK_VDEC_MAX_H, 5, 6);

	q_data->sizeimage[0] = q_data->coded_width * q_data->coded_height;
	q_data->bytesperline[0] = q_data->coded_width;
	q_data->sizeimage[1] = q_data->sizeimage[0] / 2;
	q_data->bytesperline[1] = q_data->coded_width;
पूर्ण

अटल पूर्णांक vidioc_vdec_qbuf(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->state == MTK_STATE_ABORT) अणु
		mtk_v4l2_err("[%d] Call on QBUF after unrecoverable error",
				ctx->id);
		वापस -EIO;
	पूर्ण

	वापस v4l2_m2m_qbuf(file, ctx->m2m_ctx, buf);
पूर्ण

अटल पूर्णांक vidioc_vdec_dqbuf(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->state == MTK_STATE_ABORT) अणु
		mtk_v4l2_err("[%d] Call on DQBUF after unrecoverable error",
				ctx->id);
		वापस -EIO;
	पूर्ण

	वापस v4l2_m2m_dqbuf(file, ctx->m2m_ctx, buf);
पूर्ण

अटल पूर्णांक vidioc_vdec_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, MTK_VCODEC_DEC_NAME, माप(cap->driver));
	strscpy(cap->bus_info, MTK_PLATFORM_STR, माप(cap->bus_info));
	strscpy(cap->card, MTK_PLATFORM_STR, माप(cap->card));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_vdec_subscribe_evt(काष्ठा v4l2_fh *fh,
				     स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 2, शून्य);
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subscribe(fh, sub);
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा v4l2_क्रमmat *f,
			  स्थिर काष्ठा mtk_video_fmt *fmt)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	pix_fmt_mp->field = V4L2_FIELD_NONE;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		pix_fmt_mp->num_planes = 1;
		pix_fmt_mp->plane_fmt[0].bytesperline = 0;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		पूर्णांक पंचांगp_w, पंचांगp_h;

		pix_fmt_mp->height = clamp(pix_fmt_mp->height,
					MTK_VDEC_MIN_H,
					MTK_VDEC_MAX_H);
		pix_fmt_mp->width = clamp(pix_fmt_mp->width,
					MTK_VDEC_MIN_W,
					MTK_VDEC_MAX_W);

		/*
		 * Find next बंदr width align 64, heign align 64, size align
		 * 64 rectangle
		 * Note: This only get शेष value, the real HW needed value
		 *       only available when ctx in MTK_STATE_HEADER state
		 */
		पंचांगp_w = pix_fmt_mp->width;
		पंचांगp_h = pix_fmt_mp->height;
		v4l_bound_align_image(&pix_fmt_mp->width,
					MTK_VDEC_MIN_W,
					MTK_VDEC_MAX_W, 6,
					&pix_fmt_mp->height,
					MTK_VDEC_MIN_H,
					MTK_VDEC_MAX_H, 6, 9);

		अगर (pix_fmt_mp->width < पंचांगp_w &&
			(pix_fmt_mp->width + 64) <= MTK_VDEC_MAX_W)
			pix_fmt_mp->width += 64;
		अगर (pix_fmt_mp->height < पंचांगp_h &&
			(pix_fmt_mp->height + 64) <= MTK_VDEC_MAX_H)
			pix_fmt_mp->height += 64;

		mtk_v4l2_debug(0,
			"before resize width=%d, height=%d, after resize width=%d, height=%d, sizeimage=%d",
			पंचांगp_w, पंचांगp_h, pix_fmt_mp->width,
			pix_fmt_mp->height,
			pix_fmt_mp->width * pix_fmt_mp->height);

		pix_fmt_mp->num_planes = fmt->num_planes;
		pix_fmt_mp->plane_fmt[0].sizeimage =
				pix_fmt_mp->width * pix_fmt_mp->height;
		pix_fmt_mp->plane_fmt[0].bytesperline = pix_fmt_mp->width;

		अगर (pix_fmt_mp->num_planes == 2) अणु
			pix_fmt_mp->plane_fmt[1].sizeimage =
				(pix_fmt_mp->width * pix_fmt_mp->height) / 2;
			pix_fmt_mp->plane_fmt[1].bytesperline =
				pix_fmt_mp->width;
		पूर्ण
	पूर्ण

	pix_fmt_mp->flags = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;

	fmt = mtk_vdec_find_क्रमmat(f);
	अगर (!fmt) अणु
		f->fmt.pix.pixelक्रमmat = mtk_video_क्रमmats[CAP_FMT_IDX].fourcc;
		fmt = mtk_vdec_find_क्रमmat(f);
	पूर्ण

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;
	स्थिर काष्ठा mtk_video_fmt *fmt;

	fmt = mtk_vdec_find_क्रमmat(f);
	अगर (!fmt) अणु
		f->fmt.pix.pixelक्रमmat = mtk_video_क्रमmats[OUT_FMT_IDX].fourcc;
		fmt = mtk_vdec_find_क्रमmat(f);
	पूर्ण

	अगर (pix_fmt_mp->plane_fmt[0].sizeimage == 0) अणु
		mtk_v4l2_err("sizeimage of output format must be given");
		वापस -EINVAL;
	पूर्ण

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_vdec_g_selection(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा mtk_q_data *q_data;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	q_data = &ctx->q_data[MTK_Q_DATA_DST];

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = ctx->picinfo.pic_w;
		s->r.height = ctx->picinfo.pic_h;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = ctx->picinfo.buf_w;
		s->r.height = ctx->picinfo.buf_h;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (vdec_अगर_get_param(ctx, GET_PARAM_CROP_INFO, &(s->r))) अणु
			/* set to शेष value अगर header info not पढ़ोy yet*/
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->visible_width;
			s->r.height = q_data->visible_height;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->state < MTK_STATE_HEADER) अणु
		/* set to शेष value अगर header info not पढ़ोy yet*/
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = q_data->visible_width;
		s->r.height = q_data->visible_height;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_vdec_s_selection(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = ctx->picinfo.pic_w;
		s->r.height = ctx->picinfo.pic_h;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_vdec_s_fmt(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा mtk_q_data *q_data;
	पूर्णांक ret = 0;
	स्थिर काष्ठा mtk_video_fmt *fmt;

	mtk_v4l2_debug(3, "[%d]", ctx->id);

	q_data = mtk_vdec_get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	pix_mp = &f->fmt.pix_mp;
	/*
	 * Setting OUTPUT क्रमmat after OUTPUT buffers are allocated is invalid
	 * अगर using the stateful API.
	 */
	अगर ((f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) &&
	    vb2_is_busy(&ctx->m2m_ctx->out_q_ctx.q)) अणु
		mtk_v4l2_err("out_q_ctx buffers already requested");
		ret = -EBUSY;
	पूर्ण

	/*
	 * Setting CAPTURE क्रमmat after CAPTURE buffers are allocated is
	 * invalid.
	 */
	अगर ((f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) &&
	    vb2_is_busy(&ctx->m2m_ctx->cap_q_ctx.q)) अणु
		mtk_v4l2_err("cap_q_ctx buffers already requested");
		ret = -EBUSY;
	पूर्ण

	fmt = mtk_vdec_find_क्रमmat(f);
	अगर (fmt == शून्य) अणु
		अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
			f->fmt.pix.pixelक्रमmat =
				mtk_video_क्रमmats[OUT_FMT_IDX].fourcc;
			fmt = mtk_vdec_find_क्रमmat(f);
		पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
			f->fmt.pix.pixelक्रमmat =
				mtk_video_क्रमmats[CAP_FMT_IDX].fourcc;
			fmt = mtk_vdec_find_क्रमmat(f);
		पूर्ण
	पूर्ण
	अगर (fmt == शून्य)
		वापस -EINVAL;

	q_data->fmt = fmt;
	vidioc_try_fmt(f, q_data->fmt);
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		q_data->sizeimage[0] = pix_mp->plane_fmt[0].sizeimage;
		q_data->coded_width = pix_mp->width;
		q_data->coded_height = pix_mp->height;

		ctx->colorspace = pix_mp->colorspace;
		ctx->ycbcr_enc = pix_mp->ycbcr_enc;
		ctx->quantization = pix_mp->quantization;
		ctx->xfer_func = pix_mp->xfer_func;

		अगर (ctx->state == MTK_STATE_FREE) अणु
			ret = vdec_अगर_init(ctx, q_data->fmt->fourcc);
			अगर (ret) अणु
				mtk_v4l2_err("[%d]: vdec_if_init() fail ret=%d",
					ctx->id, ret);
				वापस -EINVAL;
			पूर्ण
			ctx->state = MTK_STATE_INIT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	पूर्णांक i = 0;
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (fsize->index != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_SUPPORTED_FRAMESIZE; ++i) अणु
		अगर (fsize->pixel_क्रमmat != mtk_vdec_framesizes[i].fourcc)
			जारी;

		fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
		fsize->stepwise = mtk_vdec_framesizes[i].stepwise;
		अगर (!(ctx->dev->dec_capability &
				VCODEC_CAPABILITY_4K_DISABLED)) अणु
			mtk_v4l2_debug(3, "4K is enabled");
			fsize->stepwise.max_width =
					VCODEC_DEC_4K_CODED_WIDTH;
			fsize->stepwise.max_height =
					VCODEC_DEC_4K_CODED_HEIGHT;
		पूर्ण
		mtk_v4l2_debug(1, "%x, %d %d %d %d %d %d",
				ctx->dev->dec_capability,
				fsize->stepwise.min_width,
				fsize->stepwise.max_width,
				fsize->stepwise.step_width,
				fsize->stepwise.min_height,
				fsize->stepwise.max_height,
				fsize->stepwise.step_height);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, bool output_queue)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (output_queue && (mtk_video_क्रमmats[i].type != MTK_FMT_DEC))
			जारी;
		अगर (!output_queue &&
			(mtk_video_क्रमmats[i].type != MTK_FMT_FRAME))
			जारी;

		अगर (j == f->index)
			अवरोध;
		++j;
	पूर्ण

	अगर (i == NUM_FORMATS)
		वापस -EINVAL;

	fmt = &mtk_video_क्रमmats[i];
	f->pixelक्रमmat = fmt->fourcc;
	f->flags = fmt->flags;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_vdec_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(f, false);
पूर्ण

अटल पूर्णांक vidioc_vdec_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(f, true);
पूर्ण

अटल पूर्णांक vidioc_vdec_g_fmt(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	अगर (!vq) अणु
		mtk_v4l2_err("no vb2 queue for type=%d", f->type);
		वापस -EINVAL;
	पूर्ण

	q_data = mtk_vdec_get_q_data(ctx, f->type);

	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->colorspace = ctx->colorspace;
	pix_mp->ycbcr_enc = ctx->ycbcr_enc;
	pix_mp->quantization = ctx->quantization;
	pix_mp->xfer_func = ctx->xfer_func;

	अगर ((f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) &&
	    (ctx->state >= MTK_STATE_HEADER)) अणु
		/* Until STREAMOFF is called on the CAPTURE queue
		 * (acknowledging the event), the driver operates as अगर
		 * the resolution hasn't changed yet.
		 * So we just वापस picinfo yet, and update picinfo in
		 * stop_streaming hook function
		 */
		q_data->sizeimage[0] = ctx->picinfo.fb_sz[0];
		q_data->sizeimage[1] = ctx->picinfo.fb_sz[1];
		q_data->bytesperline[0] = ctx->last_decoded_picinfo.buf_w;
		q_data->bytesperline[1] = ctx->last_decoded_picinfo.buf_w;
		q_data->coded_width = ctx->picinfo.buf_w;
		q_data->coded_height = ctx->picinfo.buf_h;
		ctx->last_decoded_picinfo.cap_fourcc = q_data->fmt->fourcc;

		/*
		 * Width and height are set to the dimensions
		 * of the movie, the buffer is bigger and
		 * further processing stages should crop to this
		 * rectangle.
		 */
		pix_mp->width = q_data->coded_width;
		pix_mp->height = q_data->coded_height;

		/*
		 * Set pixelक्रमmat to the क्रमmat in which mt vcodec
		 * outमाला_दो the decoded frame
		 */
		pix_mp->num_planes = q_data->fmt->num_planes;
		pix_mp->pixelक्रमmat = q_data->fmt->fourcc;
		pix_mp->plane_fmt[0].bytesperline = q_data->bytesperline[0];
		pix_mp->plane_fmt[0].sizeimage = q_data->sizeimage[0];
		pix_mp->plane_fmt[1].bytesperline = q_data->bytesperline[1];
		pix_mp->plane_fmt[1].sizeimage = q_data->sizeimage[1];

	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		/*
		 * This is run on OUTPUT
		 * The buffer contains compressed image
		 * so width and height have no meaning.
		 * Assign value here to pass v4l2-compliance test
		 */
		pix_mp->width = q_data->visible_width;
		pix_mp->height = q_data->visible_height;
		pix_mp->plane_fmt[0].bytesperline = q_data->bytesperline[0];
		pix_mp->plane_fmt[0].sizeimage = q_data->sizeimage[0];
		pix_mp->pixelक्रमmat = q_data->fmt->fourcc;
		pix_mp->num_planes = q_data->fmt->num_planes;
	पूर्ण अन्यथा अणु
		pix_mp->width = q_data->coded_width;
		pix_mp->height = q_data->coded_height;
		pix_mp->num_planes = q_data->fmt->num_planes;
		pix_mp->pixelक्रमmat = q_data->fmt->fourcc;
		pix_mp->plane_fmt[0].bytesperline = q_data->bytesperline[0];
		pix_mp->plane_fmt[0].sizeimage = q_data->sizeimage[0];
		pix_mp->plane_fmt[1].bytesperline = q_data->bytesperline[1];
		pix_mp->plane_fmt[1].sizeimage = q_data->sizeimage[1];

		mtk_v4l2_debug(1, "[%d] type=%d state=%d Format information could not be read, not ready yet!",
				ctx->id, f->type, ctx->state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vb2ops_vdec_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers,
				अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा mtk_q_data *q_data;
	अचिन्हित पूर्णांक i;

	q_data = mtk_vdec_get_q_data(ctx, vq->type);

	अगर (q_data == शून्य) अणु
		mtk_v4l2_err("vq->type=%d err\n", vq->type);
		वापस -EINVAL;
	पूर्ण

	अगर (*nplanes) अणु
		क्रम (i = 0; i < *nplanes; i++) अणु
			अगर (sizes[i] < q_data->sizeimage[i])
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
			*nplanes = 2;
		अन्यथा
			*nplanes = 1;

		क्रम (i = 0; i < *nplanes; i++)
			sizes[i] = q_data->sizeimage[i];
	पूर्ण

	mtk_v4l2_debug(1,
			"[%d]\t type = %d, get %d plane(s), %d buffer(s) of size 0x%x 0x%x ",
			ctx->id, vq->type, *nplanes, *nbuffers,
			sizes[0], sizes[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक vb2ops_vdec_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mtk_q_data *q_data;
	पूर्णांक i;

	mtk_v4l2_debug(3, "[%d] (%d) id=%d",
			ctx->id, vb->vb2_queue->type, vb->index);

	q_data = mtk_vdec_get_q_data(ctx, vb->vb2_queue->type);

	क्रम (i = 0; i < q_data->fmt->num_planes; i++) अणु
		अगर (vb2_plane_size(vb, i) < q_data->sizeimage[i]) अणु
			mtk_v4l2_err("data will not fit into plane %d (%lu < %d)",
				i, vb2_plane_size(vb, i),
				q_data->sizeimage[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vb2ops_vdec_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf;
	काष्ठा mtk_vcodec_mem src_mem;
	bool res_chg = false;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक dpbsize = 1, i = 0;
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vb2_v4l2 = शून्य;
	काष्ठा mtk_video_dec_buf *buf = शून्य;
	काष्ठा mtk_q_data *dst_q_data;

	mtk_v4l2_debug(3, "[%d] (%d) id=%d, vb=%p",
			ctx->id, vb->vb2_queue->type,
			vb->index, vb);
	/*
	 * check अगर this buffer is पढ़ोy to be used after decode
	 */
	अगर (vb->vb2_queue->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		vb2_v4l2 = to_vb2_v4l2_buffer(vb);
		buf = container_of(vb2_v4l2, काष्ठा mtk_video_dec_buf,
				   m2m_buf.vb);
		mutex_lock(&ctx->lock);
		अगर (!buf->used) अणु
			v4l2_m2m_buf_queue(ctx->m2m_ctx, vb2_v4l2);
			buf->queued_in_vb2 = true;
			buf->queued_in_v4l2 = true;
		पूर्ण अन्यथा अणु
			buf->queued_in_vb2 = false;
			buf->queued_in_v4l2 = true;
		पूर्ण
		mutex_unlock(&ctx->lock);
		वापस;
	पूर्ण

	v4l2_m2m_buf_queue(ctx->m2m_ctx, to_vb2_v4l2_buffer(vb));

	अगर (ctx->state != MTK_STATE_INIT) अणु
		mtk_v4l2_debug(3, "[%d] already init driver %d",
				ctx->id, ctx->state);
		वापस;
	पूर्ण

	src_buf = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	अगर (!src_buf) अणु
		mtk_v4l2_err("No src buffer");
		वापस;
	पूर्ण
	buf = container_of(src_buf, काष्ठा mtk_video_dec_buf, m2m_buf.vb);
	अगर (buf->lastframe) अणु
		/* This shouldn't happen. Just in हाल. */
		mtk_v4l2_err("Invalid flush buffer.");
		v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
		वापस;
	पूर्ण

	src_mem.va = vb2_plane_vaddr(&src_buf->vb2_buf, 0);
	src_mem.dma_addr = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	src_mem.size = (माप_प्रकार)src_buf->vb2_buf.planes[0].bytesused;
	mtk_v4l2_debug(2,
			"[%d] buf id=%d va=%p dma=%pad size=%zx",
			ctx->id, src_buf->vb2_buf.index,
			src_mem.va, &src_mem.dma_addr,
			src_mem.size);

	ret = vdec_अगर_decode(ctx, &src_mem, शून्य, &res_chg);
	अगर (ret || !res_chg) अणु
		/*
		 * fb == शून्य means to parse SPS/PPS header or
		 * resolution info in src_mem. Decode can fail
		 * अगर there is no SPS header or picture info
		 * in bs
		 */

		src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
		अगर (ret == -EIO) अणु
			mtk_v4l2_err("[%d] Unrecoverable error in vdec_if_decode.",
					ctx->id);
			ctx->state = MTK_STATE_ABORT;
			v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
		पूर्ण अन्यथा अणु
			v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
		पूर्ण
		mtk_v4l2_debug(ret ? 0 : 1,
			       "[%d] vdec_if_decode() src_buf=%d, size=%zu, fail=%d, res_chg=%d",
			       ctx->id, src_buf->vb2_buf.index,
			       src_mem.size, ret, res_chg);
		वापस;
	पूर्ण

	अगर (vdec_अगर_get_param(ctx, GET_PARAM_PIC_INFO, &ctx->picinfo)) अणु
		mtk_v4l2_err("[%d]Error!! Cannot get param : GET_PARAM_PICTURE_INFO ERR",
				ctx->id);
		वापस;
	पूर्ण

	ctx->last_decoded_picinfo = ctx->picinfo;
	dst_q_data = &ctx->q_data[MTK_Q_DATA_DST];
	क्रम (i = 0; i < dst_q_data->fmt->num_planes; i++) अणु
		dst_q_data->sizeimage[i] = ctx->picinfo.fb_sz[i];
		dst_q_data->bytesperline[i] = ctx->picinfo.buf_w;
	पूर्ण

	mtk_v4l2_debug(2, "[%d] vdec_if_init() OK wxh=%dx%d pic wxh=%dx%d sz[0]=0x%x sz[1]=0x%x",
			ctx->id,
			ctx->picinfo.buf_w, ctx->picinfo.buf_h,
			ctx->picinfo.pic_w, ctx->picinfo.pic_h,
			dst_q_data->sizeimage[0],
			dst_q_data->sizeimage[1]);

	ret = vdec_अगर_get_param(ctx, GET_PARAM_DPB_SIZE, &dpbsize);
	अगर (dpbsize == 0)
		mtk_v4l2_err("[%d] GET_PARAM_DPB_SIZE fail=%d", ctx->id, ret);

	ctx->dpb_size = dpbsize;
	ctx->state = MTK_STATE_HEADER;
	mtk_v4l2_debug(1, "[%d] dpbsize=%d", ctx->id, ctx->dpb_size);

	mtk_vdec_queue_res_chg_event(ctx);
पूर्ण

अटल व्योम vb2ops_vdec_buf_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vb2_v4l2;
	काष्ठा mtk_video_dec_buf *buf;
	bool buf_error;

	vb2_v4l2 = container_of(vb, काष्ठा vb2_v4l2_buffer, vb2_buf);
	buf = container_of(vb2_v4l2, काष्ठा mtk_video_dec_buf, m2m_buf.vb);
	mutex_lock(&ctx->lock);
	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		buf->queued_in_v4l2 = false;
		buf->queued_in_vb2 = false;
	पूर्ण
	buf_error = buf->error;
	mutex_unlock(&ctx->lock);

	अगर (buf_error) अणु
		mtk_v4l2_err("Unrecoverable error on buffer.");
		ctx->state = MTK_STATE_ABORT;
	पूर्ण
पूर्ण

अटल पूर्णांक vb2ops_vdec_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vb2_v4l2 = container_of(vb,
					काष्ठा vb2_v4l2_buffer, vb2_buf);
	काष्ठा mtk_video_dec_buf *buf = container_of(vb2_v4l2,
					काष्ठा mtk_video_dec_buf, m2m_buf.vb);

	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		buf->used = false;
		buf->queued_in_v4l2 = false;
	पूर्ण अन्यथा अणु
		buf->lastframe = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vb2ops_vdec_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(q);

	अगर (ctx->state == MTK_STATE_FLUSH)
		ctx->state = MTK_STATE_HEADER;

	वापस 0;
पूर्ण

अटल व्योम vb2ops_vdec_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf = शून्य, *dst_buf = शून्य;
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(q);

	mtk_v4l2_debug(3, "[%d] (%d) state=(%x) ctx->decoded_frame_cnt=%d",
			ctx->id, q->type, ctx->state, ctx->decoded_frame_cnt);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		जबतक ((src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx))) अणु
			काष्ठा mtk_video_dec_buf *buf_info = container_of(
				 src_buf, काष्ठा mtk_video_dec_buf, m2m_buf.vb);
			अगर (!buf_info->lastframe)
				v4l2_m2m_buf_करोne(src_buf,
						VB2_BUF_STATE_ERROR);
		पूर्ण
		वापस;
	पूर्ण

	अगर (ctx->state >= MTK_STATE_HEADER) अणु

		/* Until STREAMOFF is called on the CAPTURE queue
		 * (acknowledging the event), the driver operates
		 * as अगर the resolution hasn't changed yet, i.e.
		 * VIDIOC_G_FMT< etc. वापस previous resolution.
		 * So we update picinfo here
		 */
		ctx->picinfo = ctx->last_decoded_picinfo;

		mtk_v4l2_debug(2,
				"[%d]-> new(%d,%d), old(%d,%d), real(%d,%d)",
				ctx->id, ctx->last_decoded_picinfo.pic_w,
				ctx->last_decoded_picinfo.pic_h,
				ctx->picinfo.pic_w, ctx->picinfo.pic_h,
				ctx->last_decoded_picinfo.buf_w,
				ctx->last_decoded_picinfo.buf_h);

		mtk_vdec_flush_decoder(ctx);
	पूर्ण
	ctx->state = MTK_STATE_FLUSH;

	जबतक ((dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx))) अणु
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, 0);
		अगर (ctx->q_data[MTK_Q_DATA_DST].fmt->num_planes == 2)
			vb2_set_plane_payload(&dst_buf->vb2_buf, 1, 0);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

पूर्ण

अटल व्योम m2mops_vdec_device_run(व्योम *priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;
	काष्ठा mtk_vcodec_dev *dev = ctx->dev;

	queue_work(dev->decode_workqueue, &ctx->decode_work);
पूर्ण

अटल पूर्णांक m2mops_vdec_job_पढ़ोy(व्योम *m2m_priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = m2m_priv;

	mtk_v4l2_debug(3, "[%d]", ctx->id);

	अगर (ctx->state == MTK_STATE_ABORT)
		वापस 0;

	अगर ((ctx->last_decoded_picinfo.pic_w != ctx->picinfo.pic_w) ||
	    (ctx->last_decoded_picinfo.pic_h != ctx->picinfo.pic_h))
		वापस 0;

	अगर (ctx->state != MTK_STATE_HEADER)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम m2mops_vdec_job_पात(व्योम *priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;

	ctx->state = MTK_STATE_ABORT;
पूर्ण

अटल पूर्णांक mtk_vdec_g_v_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = ctrl_to_ctx(ctrl);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		अगर (ctx->state >= MTK_STATE_HEADER) अणु
			ctrl->val = ctx->dpb_size;
		पूर्ण अन्यथा अणु
			mtk_v4l2_debug(0, "Seqinfo not ready");
			ctrl->val = 0;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mtk_vcodec_dec_ctrl_ops = अणु
	.g_अस्थिर_ctrl = mtk_vdec_g_v_ctrl,
पूर्ण;

पूर्णांक mtk_vcodec_dec_ctrls_setup(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl *ctrl;

	v4l2_ctrl_handler_init(&ctx->ctrl_hdl, 1);

	ctrl = v4l2_ctrl_new_std(&ctx->ctrl_hdl,
				&mtk_vcodec_dec_ctrl_ops,
				V4L2_CID_MIN_BUFFERS_FOR_CAPTURE,
				0, 32, 1, 1);
	ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	v4l2_ctrl_new_std_menu(&ctx->ctrl_hdl,
				&mtk_vcodec_dec_ctrl_ops,
				V4L2_CID_MPEG_VIDEO_VP9_PROखाता,
				V4L2_MPEG_VIDEO_VP9_PROखाता_0,
				0, V4L2_MPEG_VIDEO_VP9_PROखाता_0);

	अगर (ctx->ctrl_hdl.error) अणु
		mtk_v4l2_err("Adding control failed %d",
				ctx->ctrl_hdl.error);
		वापस ctx->ctrl_hdl.error;
	पूर्ण

	v4l2_ctrl_handler_setup(&ctx->ctrl_hdl);
	वापस 0;
पूर्ण

स्थिर काष्ठा v4l2_m2m_ops mtk_vdec_m2m_ops = अणु
	.device_run	= m2mops_vdec_device_run,
	.job_पढ़ोy	= m2mops_vdec_job_पढ़ोy,
	.job_पात	= m2mops_vdec_job_पात,
पूर्ण;

अटल स्थिर काष्ठा vb2_ops mtk_vdec_vb2_ops = अणु
	.queue_setup	= vb2ops_vdec_queue_setup,
	.buf_prepare	= vb2ops_vdec_buf_prepare,
	.buf_queue	= vb2ops_vdec_buf_queue,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
	.buf_init	= vb2ops_vdec_buf_init,
	.buf_finish	= vb2ops_vdec_buf_finish,
	.start_streaming	= vb2ops_vdec_start_streaming,
	.stop_streaming	= vb2ops_vdec_stop_streaming,
पूर्ण;

स्थिर काष्ठा v4l2_ioctl_ops mtk_vdec_ioctl_ops = अणु
	.vidioc_streamon	= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,
	.vidioc_reqbufs		= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,

	.vidioc_qbuf		= vidioc_vdec_qbuf,
	.vidioc_dqbuf		= vidioc_vdec_dqbuf,

	.vidioc_try_fmt_vid_cap_mplane	= vidioc_try_fmt_vid_cap_mplane,
	.vidioc_try_fmt_vid_out_mplane	= vidioc_try_fmt_vid_out_mplane,

	.vidioc_s_fmt_vid_cap_mplane	= vidioc_vdec_s_fmt,
	.vidioc_s_fmt_vid_out_mplane	= vidioc_vdec_s_fmt,
	.vidioc_g_fmt_vid_cap_mplane	= vidioc_vdec_g_fmt,
	.vidioc_g_fmt_vid_out_mplane	= vidioc_vdec_g_fmt,

	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,

	.vidioc_क्रमागत_fmt_vid_cap	= vidioc_vdec_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= vidioc_vdec_क्रमागत_fmt_vid_out,
	.vidioc_क्रमागत_framesizes	= vidioc_क्रमागत_framesizes,

	.vidioc_querycap		= vidioc_vdec_querycap,
	.vidioc_subscribe_event		= vidioc_vdec_subscribe_evt,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
	.vidioc_g_selection             = vidioc_vdec_g_selection,
	.vidioc_s_selection             = vidioc_vdec_s_selection,

	.vidioc_decoder_cmd = vidioc_decoder_cmd,
	.vidioc_try_decoder_cmd = vidioc_try_decoder_cmd,
पूर्ण;

पूर्णांक mtk_vcodec_dec_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			   काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;
	पूर्णांक ret = 0;

	mtk_v4l2_debug(3, "[%d]", ctx->id);

	src_vq->type		= V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes	= VB2_DMABUF | VB2_MMAP;
	src_vq->drv_priv	= ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा mtk_video_dec_buf);
	src_vq->ops		= &mtk_vdec_vb2_ops;
	src_vq->mem_ops		= &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock		= &ctx->dev->dev_mutex;
	src_vq->dev             = &ctx->dev->plat_dev->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret) अणु
		mtk_v4l2_err("Failed to initialize videobuf2 queue(output)");
		वापस ret;
	पूर्ण
	dst_vq->type		= V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes	= VB2_DMABUF | VB2_MMAP;
	dst_vq->drv_priv	= ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा mtk_video_dec_buf);
	dst_vq->ops		= &mtk_vdec_vb2_ops;
	dst_vq->mem_ops		= &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock		= &ctx->dev->dev_mutex;
	dst_vq->dev             = &ctx->dev->plat_dev->dev;

	ret = vb2_queue_init(dst_vq);
	अगर (ret)
		mtk_v4l2_err("Failed to initialize videobuf2 queue(capture)");

	वापस ret;
पूर्ण
