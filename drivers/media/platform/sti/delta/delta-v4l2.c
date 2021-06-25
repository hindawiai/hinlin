<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Hugues Fruchet <hugues.fruchet@st.com>
 *          Jean-Christophe Trotin <jean-christophe.trotin@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "delta.h"
#समावेश "delta-debug.h"
#समावेश "delta-ipc.h"

#घोषणा DELTA_NAME	"st-delta"

#घोषणा DELTA_PREFIX "[---:----]"

#घोषणा to_ctx(__fh) container_of(__fh, काष्ठा delta_ctx, fh)
#घोषणा to_au(__vbuf) container_of(__vbuf, काष्ठा delta_au, vbuf)
#घोषणा to_frame(__vbuf) container_of(__vbuf, काष्ठा delta_frame, vbuf)

#घोषणा call_dec_op(dec, op, args...)\
		((dec && (dec)->op) ? (dec)->op(args) : 0)

/* registry of available decoders */
अटल स्थिर काष्ठा delta_dec *delta_decoders[] = अणु
#अगर_घोषित CONFIG_VIDEO_STI_DELTA_MJPEG
	&mjpegdec,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत पूर्णांक frame_size(u32 w, u32 h, u32 fmt)
अणु
	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_NV12:
		वापस (w * h * 3) / 2;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक frame_stride(u32 w, u32 fmt)
अणु
	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_NV12:
		वापस w;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम dump_au(काष्ठा delta_ctx *ctx, काष्ठा delta_au *au)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	u32 size = 10;	/* dump first & last 10 bytes */
	u8 *data = (u8 *)(au->vaddr);

	अगर (au->size <= (size * 2))
		dev_dbg(delta->dev, "%s dump au[%d] dts=%lld size=%d data=%*ph\n",
			ctx->name, au->vbuf.vb2_buf.index, au->dts, au->size,
			au->size, data);
	अन्यथा
		dev_dbg(delta->dev, "%s dump au[%d] dts=%lld size=%d data=%*ph..%*ph\n",
			ctx->name, au->vbuf.vb2_buf.index, au->dts, au->size,
			size, data, size, data + au->size - size);
पूर्ण

अटल व्योम dump_frame(काष्ठा delta_ctx *ctx, काष्ठा delta_frame *frame)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	u32 size = 10;	/* dump first 10 bytes */
	u8 *data = (u8 *)(frame->vaddr);

	dev_dbg(delta->dev, "%s dump frame[%d] dts=%lld type=%s field=%s data=%*ph\n",
		ctx->name, frame->index, frame->dts,
		frame_type_str(frame->flags),
		frame_field_str(frame->field),
		size, data);
पूर्ण

अटल व्योम delta_au_करोne(काष्ठा delta_ctx *ctx, काष्ठा delta_au *au, पूर्णांक err)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;

	vbuf = &au->vbuf;
	vbuf->sequence = ctx->au_num++;
	v4l2_m2m_buf_करोne(vbuf, err ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
पूर्ण

अटल व्योम delta_frame_करोne(काष्ठा delta_ctx *ctx, काष्ठा delta_frame *frame,
			     पूर्णांक err)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;

	dump_frame(ctx, frame);

	/* decoded frame is now output to user */
	frame->state |= DELTA_FRAME_OUT;

	vbuf = &frame->vbuf;
	vbuf->sequence = ctx->frame_num++;
	v4l2_m2m_buf_करोne(vbuf, err ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);

	अगर (frame->info.size) /* ignore EOS */
		ctx->output_frames++;
पूर्ण

अटल व्योम requeue_मुक्त_frames(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा delta_frame *frame;
	अचिन्हित पूर्णांक i;

	/* requeue all मुक्त frames */
	क्रम (i = 0; i < ctx->nb_of_frames; i++) अणु
		frame = ctx->frames[i];
		अगर (frame->state == DELTA_FRAME_FREE) अणु
			vbuf = &frame->vbuf;
			v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
			frame->state = DELTA_FRAME_M2M;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक delta_recycle(काष्ठा delta_ctx *ctx, काष्ठा delta_frame *frame)
अणु
	स्थिर काष्ठा delta_dec *dec = ctx->dec;

	/* recycle frame on decoder side */
	call_dec_op(dec, recycle, ctx, frame);

	/* this frame is no more output */
	frame->state &= ~DELTA_FRAME_OUT;

	/* requeue मुक्त frame */
	अगर (frame->state == DELTA_FRAME_FREE) अणु
		काष्ठा vb2_v4l2_buffer *vbuf = &frame->vbuf;

		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		frame->state = DELTA_FRAME_M2M;
	पूर्ण

	/* reset other frame fields */
	frame->flags = 0;
	frame->dts = 0;

	वापस 0;
पूर्ण

अटल व्योम delta_push_dts(काष्ठा delta_ctx *ctx, u64 val)
अणु
	काष्ठा delta_dts *dts;

	dts = kzalloc(माप(*dts), GFP_KERNEL);
	अगर (!dts)
		वापस;

	INIT_LIST_HEAD(&dts->list);

	/*
	 * रक्षित by global lock acquired
	 * by V4L2 when calling delta_vb2_au_queue
	 */
	dts->val = val;
	list_add_tail(&dts->list, &ctx->dts);
पूर्ण

अटल व्योम delta_pop_dts(काष्ठा delta_ctx *ctx, u64 *val)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा delta_dts *dts;

	/*
	 * रक्षित by global lock acquired
	 * by V4L2 when calling delta_vb2_au_queue
	 */
	अगर (list_empty(&ctx->dts)) अणु
		dev_warn(delta->dev, "%s no dts to pop ... output dts = 0\n",
			 ctx->name);
		*val = 0;
		वापस;
	पूर्ण

	dts = list_first_entry(&ctx->dts, काष्ठा delta_dts, list);
	list_del(&dts->list);

	*val = dts->val;

	kमुक्त(dts);
पूर्ण

अटल व्योम delta_flush_dts(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा delta_dts *dts;
	काष्ठा delta_dts *next;

	/*
	 * रक्षित by global lock acquired
	 * by V4L2 when calling delta_vb2_au_queue
	 */

	/* मुक्त all pending dts */
	list_क्रम_each_entry_safe(dts, next, &ctx->dts, list)
		kमुक्त(dts);

	/* reset list */
	INIT_LIST_HEAD(&ctx->dts);
पूर्ण

अटल अंतरभूत पूर्णांक frame_alignment(u32 fmt)
अणु
	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		/* multiple of 2 */
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक estimated_au_size(u32 w, u32 h)
अणु
	/*
	 * क्रम a MJPEG stream encoded from YUV422 pixel क्रमmat,
	 * assuming a compression ratio of 2, the maximum size
	 * of an access unit is (width x height x 2) / 2,
	 * so (width x height)
	 */
	वापस (w * h);
पूर्ण

अटल व्योम set_शेष_params(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा delta_frameinfo *frameinfo = &ctx->frameinfo;
	काष्ठा delta_streaminfo *streaminfo = &ctx->streaminfo;

	स_रखो(frameinfo, 0, माप(*frameinfo));
	frameinfo->pixelक्रमmat = V4L2_PIX_FMT_NV12;
	frameinfo->width = DELTA_DEFAULT_WIDTH;
	frameinfo->height = DELTA_DEFAULT_HEIGHT;
	frameinfo->aligned_width = ALIGN(frameinfo->width,
					 DELTA_WIDTH_ALIGNMENT);
	frameinfo->aligned_height = ALIGN(frameinfo->height,
					  DELTA_HEIGHT_ALIGNMENT);
	frameinfo->size = frame_size(frameinfo->aligned_width,
				     frameinfo->aligned_height,
				     frameinfo->pixelक्रमmat);
	frameinfo->field = V4L2_FIELD_NONE;
	frameinfo->colorspace = V4L2_COLORSPACE_REC709;
	frameinfo->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	frameinfo->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	frameinfo->quantization = V4L2_QUANTIZATION_DEFAULT;

	स_रखो(streaminfo, 0, माप(*streaminfo));
	streaminfo->streamक्रमmat = DELTA_DEFAULT_STREAMFORMAT;
	streaminfo->width = DELTA_DEFAULT_WIDTH;
	streaminfo->height = DELTA_DEFAULT_HEIGHT;
	streaminfo->field = V4L2_FIELD_NONE;
	streaminfo->colorspace = V4L2_COLORSPACE_REC709;
	streaminfo->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	streaminfo->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	streaminfo->quantization = V4L2_QUANTIZATION_DEFAULT;

	ctx->max_au_size = estimated_au_size(streaminfo->width,
					     streaminfo->height);
पूर्ण

अटल स्थिर काष्ठा delta_dec *delta_find_decoder(काष्ठा delta_ctx *ctx,
						  u32 streamक्रमmat,
						  u32 pixelक्रमmat)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < delta->nb_of_decoders; i++) अणु
		dec = delta->decoders[i];
		अगर ((dec->pixelक्रमmat == pixelक्रमmat) &&
		    (dec->streamक्रमmat == streamक्रमmat))
			वापस dec;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम रेजिस्टर_क्रमmat(u32 क्रमmat, u32 क्रमmats[], u32 *nb_of_क्रमmats)
अणु
	u32 i;

	क्रम (i = 0; i < *nb_of_क्रमmats; i++) अणु
		अगर (क्रमmat == क्रमmats[i])
			वापस;
	पूर्ण

	क्रमmats[(*nb_of_क्रमmats)++] = क्रमmat;
पूर्ण

अटल व्योम रेजिस्टर_क्रमmats(काष्ठा delta_dev *delta)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < delta->nb_of_decoders; i++) अणु
		रेजिस्टर_क्रमmat(delta->decoders[i]->pixelक्रमmat,
				delta->pixelक्रमmats,
				&delta->nb_of_pixelक्रमmats);

		रेजिस्टर_क्रमmat(delta->decoders[i]->streamक्रमmat,
				delta->streamक्रमmats,
				&delta->nb_of_streamक्रमmats);
	पूर्ण
पूर्ण

अटल व्योम रेजिस्टर_decoders(काष्ठा delta_dev *delta)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(delta_decoders); i++) अणु
		अगर (delta->nb_of_decoders >= DELTA_MAX_DECODERS) अणु
			dev_dbg(delta->dev,
				"%s failed to register %s decoder (%d maximum reached)\n",
				DELTA_PREFIX, delta_decoders[i]->name,
				DELTA_MAX_DECODERS);
			वापस;
		पूर्ण

		delta->decoders[delta->nb_of_decoders++] = delta_decoders[i];
		dev_info(delta->dev, "%s %s decoder registered\n",
			 DELTA_PREFIX, delta_decoders[i]->name);
	पूर्ण
पूर्ण

अटल पूर्णांक delta_खोलो_decoder(काष्ठा delta_ctx *ctx, u32 streamक्रमmat,
			      u32 pixelक्रमmat, स्थिर काष्ठा delta_dec **pdec)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec;
	पूर्णांक ret;

	dec = delta_find_decoder(ctx, streamक्रमmat, ctx->frameinfo.pixelक्रमmat);
	अगर (!dec) अणु
		dev_err(delta->dev, "%s no decoder found matching %4.4s => %4.4s\n",
			ctx->name, (अक्षर *)&streamक्रमmat, (अक्षर *)&pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(delta->dev, "%s one decoder matching %4.4s => %4.4s\n",
		ctx->name, (अक्षर *)&streamक्रमmat, (अक्षर *)&pixelक्रमmat);

	/* update instance name */
	snम_लिखो(ctx->name, माप(ctx->name), "[%3d:%4.4s]",
		 delta->instance_id, (अक्षर *)&streamक्रमmat);

	/* खोलो decoder instance */
	ret = call_dec_op(dec, खोलो, ctx);
	अगर (ret) अणु
		dev_err(delta->dev, "%s failed to open decoder instance (%d)\n",
			ctx->name, ret);
		वापस ret;
	पूर्ण

	dev_dbg(delta->dev, "%s %s decoder opened\n", ctx->name, dec->name);

	*pdec = dec;

	वापस ret;
पूर्ण

/*
 * V4L2 ioctl operations
 */

अटल पूर्णांक delta_querycap(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_capability *cap)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;

	strscpy(cap->driver, DELTA_NAME, माप(cap->driver));
	strscpy(cap->card, delta->vdev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 delta->pdev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक delta_क्रमागत_fmt_stream(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;

	अगर (unlikely(f->index >= delta->nb_of_streamक्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = delta->streamक्रमmats[f->index];

	वापस 0;
पूर्ण

अटल पूर्णांक delta_क्रमागत_fmt_frame(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;

	अगर (unlikely(f->index >= delta->nb_of_pixelक्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = delta->pixelक्रमmats[f->index];

	वापस 0;
पूर्ण

अटल पूर्णांक delta_g_fmt_stream(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा delta_streaminfo *streaminfo = &ctx->streaminfo;
	अचिन्हित अक्षर str[100] = "";

	अगर (!(ctx->flags & DELTA_FLAG_STREAMINFO))
		dev_dbg(delta->dev,
			"%s V4L2 GET_FMT (OUTPUT): no stream information available, default to %s\n",
			ctx->name,
			delta_streaminfo_str(streaminfo, str, माप(str)));

	pix->pixelक्रमmat = streaminfo->streamक्रमmat;
	pix->width = streaminfo->width;
	pix->height = streaminfo->height;
	pix->field = streaminfo->field;
	pix->bytesperline = 0;
	pix->sizeimage = ctx->max_au_size;
	pix->colorspace = streaminfo->colorspace;
	pix->xfer_func = streaminfo->xfer_func;
	pix->ycbcr_enc = streaminfo->ycbcr_enc;
	pix->quantization = streaminfo->quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_g_fmt_frame(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा delta_frameinfo *frameinfo = &ctx->frameinfo;
	काष्ठा delta_streaminfo *streaminfo = &ctx->streaminfo;
	अचिन्हित अक्षर str[100] = "";

	अगर (!(ctx->flags & DELTA_FLAG_FRAMEINFO))
		dev_dbg(delta->dev,
			"%s V4L2 GET_FMT (CAPTURE): no frame information available, default to %s\n",
			ctx->name,
			delta_frameinfo_str(frameinfo, str, माप(str)));

	pix->pixelक्रमmat = frameinfo->pixelक्रमmat;
	pix->width = frameinfo->aligned_width;
	pix->height = frameinfo->aligned_height;
	pix->field = frameinfo->field;
	pix->bytesperline = frame_stride(frameinfo->aligned_width,
					       frameinfo->pixelक्रमmat);
	pix->sizeimage = frameinfo->size;

	अगर (ctx->flags & DELTA_FLAG_STREAMINFO) अणु
		/* align colorspace & मित्रs on stream ones अगर any set */
		frameinfo->colorspace = streaminfo->colorspace;
		frameinfo->xfer_func = streaminfo->xfer_func;
		frameinfo->ycbcr_enc = streaminfo->ycbcr_enc;
		frameinfo->quantization = streaminfo->quantization;
	पूर्ण
	pix->colorspace = frameinfo->colorspace;
	pix->xfer_func = frameinfo->xfer_func;
	pix->ycbcr_enc = frameinfo->ycbcr_enc;
	pix->quantization = frameinfo->quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_try_fmt_stream(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	u32 streamक्रमmat = pix->pixelक्रमmat;
	स्थिर काष्ठा delta_dec *dec;
	u32 width, height;
	u32 au_size;

	dec = delta_find_decoder(ctx, streamक्रमmat, ctx->frameinfo.pixelक्रमmat);
	अगर (!dec) अणु
		dev_dbg(delta->dev,
			"%s V4L2 TRY_FMT (OUTPUT): unsupported format %4.4s\n",
			ctx->name, (अक्षर *)&pix->pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* adjust width & height */
	width = pix->width;
	height = pix->height;
	v4l_bound_align_image
		(&pix->width,
		 DELTA_MIN_WIDTH,
		 dec->max_width ? dec->max_width : DELTA_MAX_WIDTH,
		 0,
		 &pix->height,
		 DELTA_MIN_HEIGHT,
		 dec->max_height ? dec->max_height : DELTA_MAX_HEIGHT,
		 0, 0);

	अगर ((pix->width != width) || (pix->height != height))
		dev_dbg(delta->dev,
			"%s V4L2 TRY_FMT (OUTPUT): resolution updated %dx%d -> %dx%d to fit min/max/alignment\n",
			ctx->name, width, height,
			pix->width, pix->height);

	au_size = estimated_au_size(pix->width, pix->height);
	अगर (pix->sizeimage < au_size) अणु
		dev_dbg(delta->dev,
			"%s V4L2 TRY_FMT (OUTPUT): size updated %d -> %d to fit estimated size\n",
			ctx->name, pix->sizeimage, au_size);
		pix->sizeimage = au_size;
	पूर्ण

	pix->bytesperline = 0;

	अगर (pix->field == V4L2_FIELD_ANY)
		pix->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_try_fmt_frame(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	u32 pixelक्रमmat = pix->pixelक्रमmat;
	स्थिर काष्ठा delta_dec *dec;
	u32 width, height;

	dec = delta_find_decoder(ctx, ctx->streaminfo.streamक्रमmat,
				 pixelक्रमmat);
	अगर (!dec) अणु
		dev_dbg(delta->dev,
			"%s V4L2 TRY_FMT (CAPTURE): unsupported format %4.4s\n",
			ctx->name, (अक्षर *)&pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* adjust width & height */
	width = pix->width;
	height = pix->height;
	v4l_bound_align_image(&pix->width,
			      DELTA_MIN_WIDTH, DELTA_MAX_WIDTH,
			      frame_alignment(pixelक्रमmat) - 1,
			      &pix->height,
			      DELTA_MIN_HEIGHT, DELTA_MAX_HEIGHT,
			      frame_alignment(pixelक्रमmat) - 1, 0);

	अगर ((pix->width != width) || (pix->height != height))
		dev_dbg(delta->dev,
			"%s V4L2 TRY_FMT (CAPTURE): resolution updated %dx%d -> %dx%d to fit min/max/alignment\n",
			ctx->name, width, height, pix->width, pix->height);

	/* शेष decoder alignment स्थिरraपूर्णांक */
	width = ALIGN(pix->width, DELTA_WIDTH_ALIGNMENT);
	height = ALIGN(pix->height, DELTA_HEIGHT_ALIGNMENT);
	अगर ((pix->width != width) || (pix->height != height))
		dev_dbg(delta->dev,
			"%s V4L2 TRY_FMT (CAPTURE): resolution updated %dx%d -> %dx%d to fit decoder alignment\n",
			ctx->name, width, height, pix->width, pix->height);

	अगर (!pix->colorspace) अणु
		pix->colorspace = V4L2_COLORSPACE_REC709;
		pix->xfer_func = V4L2_XFER_FUNC_DEFAULT;
		pix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		pix->quantization = V4L2_QUANTIZATION_DEFAULT;
	पूर्ण

	pix->width = width;
	pix->height = height;
	pix->bytesperline = frame_stride(pix->width, pixelक्रमmat);
	pix->sizeimage = frame_size(pix->width, pix->height, pixelक्रमmat);

	अगर (pix->field == V4L2_FIELD_ANY)
		pix->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_s_fmt_stream(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा vb2_queue *vq;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	पूर्णांक ret;

	ret = delta_try_fmt_stream(file, fh, f);
	अगर (ret) अणु
		dev_dbg(delta->dev,
			"%s V4L2 S_FMT (OUTPUT): unsupported format %4.4s\n",
			ctx->name, (अक्षर *)&pix->pixelक्रमmat);
		वापस ret;
	पूर्ण

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_streaming(vq)) अणु
		dev_dbg(delta->dev, "%s V4L2 S_FMT (OUTPUT): queue busy\n",
			ctx->name);
		वापस -EBUSY;
	पूर्ण

	ctx->max_au_size = pix->sizeimage;
	ctx->streaminfo.width = pix->width;
	ctx->streaminfo.height = pix->height;
	ctx->streaminfo.streamक्रमmat = pix->pixelक्रमmat;
	ctx->streaminfo.colorspace = pix->colorspace;
	ctx->streaminfo.xfer_func = pix->xfer_func;
	ctx->streaminfo.ycbcr_enc = pix->ycbcr_enc;
	ctx->streaminfo.quantization = pix->quantization;
	ctx->flags |= DELTA_FLAG_STREAMINFO;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_s_fmt_frame(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec = ctx->dec;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा delta_frameinfo frameinfo;
	अचिन्हित अक्षर str[100] = "";
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_streaming(vq)) अणु
		dev_dbg(delta->dev, "%s V4L2 S_FMT (CAPTURE): queue busy\n",
			ctx->name);
		वापस -EBUSY;
	पूर्ण

	अगर (ctx->state < DELTA_STATE_READY) अणु
		/*
		 * decoder not yet खोलोed and valid stream header not found,
		 * could not negotiate क्रमmat with decoder, check at least
		 * pixel क्रमmat & negotiate resolution boundaries
		 * and alignment...
		 */
		ret = delta_try_fmt_frame(file, fh, f);
		अगर (ret) अणु
			dev_dbg(delta->dev,
				"%s V4L2 S_FMT (CAPTURE): unsupported format %4.4s\n",
				ctx->name, (अक्षर *)&pix->pixelक्रमmat);
			वापस ret;
		पूर्ण

		वापस 0;
	पूर्ण

	/* set frame inक्रमmation to decoder */
	स_रखो(&frameinfo, 0, माप(frameinfo));
	frameinfo.pixelक्रमmat = pix->pixelक्रमmat;
	frameinfo.width = pix->width;
	frameinfo.height = pix->height;
	frameinfo.aligned_width = pix->width;
	frameinfo.aligned_height = pix->height;
	frameinfo.size = pix->sizeimage;
	frameinfo.field = pix->field;
	frameinfo.colorspace = pix->colorspace;
	frameinfo.xfer_func = pix->xfer_func;
	frameinfo.ycbcr_enc = pix->ycbcr_enc;
	frameinfo.quantization = pix->quantization;
	ret = call_dec_op(dec, set_frameinfo, ctx, &frameinfo);
	अगर (ret)
		वापस ret;

	/* then get what decoder can really करो */
	ret = call_dec_op(dec, get_frameinfo, ctx, &frameinfo);
	अगर (ret)
		वापस ret;

	ctx->flags |= DELTA_FLAG_FRAMEINFO;
	ctx->frameinfo = frameinfo;
	dev_dbg(delta->dev,
		"%s V4L2 SET_FMT (CAPTURE): frameinfo updated to %s\n",
		ctx->name,
		delta_frameinfo_str(&frameinfo, str, माप(str)));

	pix->pixelक्रमmat = frameinfo.pixelक्रमmat;
	pix->width = frameinfo.aligned_width;
	pix->height = frameinfo.aligned_height;
	pix->bytesperline = frame_stride(pix->width, pix->pixelक्रमmat);
	pix->sizeimage = frameinfo.size;
	pix->field = frameinfo.field;
	pix->colorspace = frameinfo.colorspace;
	pix->xfer_func = frameinfo.xfer_func;
	pix->ycbcr_enc = frameinfo.ycbcr_enc;
	pix->quantization = frameinfo.quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_g_selection(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_selection *s)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(fh);
	काष्ठा delta_frameinfo *frameinfo = &ctx->frameinfo;
	काष्ठा v4l2_rect crop;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर ((ctx->flags & DELTA_FLAG_FRAMEINFO) &&
	    (frameinfo->flags & DELTA_FRAMEINFO_FLAG_CROP)) अणु
		crop = frameinfo->crop;
	पूर्ण अन्यथा अणु
		/* शेष to video dimensions */
		crop.left = 0;
		crop.top = 0;
		crop.width = frameinfo->width;
		crop.height = frameinfo->height;
	पूर्ण

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		/* visible area inside video */
		s->r = crop;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_PADDED:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		/* up to aligned dimensions */
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frameinfo->aligned_width;
		s->r.height = frameinfo->aligned_height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम delta_complete_eos(काष्ठा delta_ctx *ctx,
			       काष्ठा delta_frame *frame)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा v4l2_event ev = अणु.type = V4L2_EVENT_EOSपूर्ण;

	/*
	 * Send EOS to user:
	 * - by वापसing an empty frame flagged to V4L2_BUF_FLAG_LAST
	 * - and then send EOS event
	 */

	/* empty frame */
	frame->info.size = 0;

	/* set the last buffer flag */
	frame->flags |= V4L2_BUF_FLAG_LAST;

	/* release frame to user */
	delta_frame_करोne(ctx, frame, 0);

	/* send EOS event */
	v4l2_event_queue_fh(&ctx->fh, &ev);

	dev_dbg(delta->dev, "%s EOS completed\n", ctx->name);
पूर्ण

अटल पूर्णांक delta_try_decoder_cmd(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_decoder_cmd *cmd)
अणु
	अगर (cmd->cmd != V4L2_DEC_CMD_STOP)
		वापस -EINVAL;

	अगर (cmd->flags & V4L2_DEC_CMD_STOP_TO_BLACK)
		वापस -EINVAL;

	अगर (!(cmd->flags & V4L2_DEC_CMD_STOP_IMMEDIATELY) &&
	    (cmd->stop.pts != 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_decoder_stop_cmd(काष्ठा delta_ctx *ctx, व्योम *fh)
अणु
	स्थिर काष्ठा delta_dec *dec = ctx->dec;
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा delta_frame *frame = शून्य;
	पूर्णांक ret = 0;

	dev_dbg(delta->dev, "%s EOS received\n", ctx->name);

	अगर (ctx->state != DELTA_STATE_READY)
		वापस 0;

	/* drain the decoder */
	call_dec_op(dec, drain, ctx);

	/* release to user drained frames */
	जबतक (1) अणु
		frame = शून्य;
		ret = call_dec_op(dec, get_frame, ctx, &frame);
		अगर (ret == -ENODATA) अणु
			/* no more decoded frames */
			अवरोध;
		पूर्ण
		अगर (frame) अणु
			dev_dbg(delta->dev, "%s drain frame[%d]\n",
				ctx->name, frame->index);

			/* pop बारtamp and mark frame with it */
			delta_pop_dts(ctx, &frame->dts);

			/* release decoded frame to user */
			delta_frame_करोne(ctx, frame, 0);
		पूर्ण
	पूर्ण

	/* try to complete EOS */
	ret = delta_get_मुक्त_frame(ctx, &frame);
	अगर (ret)
		जाओ delay_eos;

	/* new frame available, EOS can now be completed */
	delta_complete_eos(ctx, frame);

	ctx->state = DELTA_STATE_EOS;

	वापस 0;

delay_eos:
	/*
	 * EOS completion from driver is delayed because
	 * we करोn't have a मुक्त empty frame available.
	 * EOS completion is so delayed till next frame_queue() call
	 * to be sure to have a मुक्त empty frame available.
	 */
	ctx->state = DELTA_STATE_WF_EOS;
	dev_dbg(delta->dev, "%s EOS delayed\n", ctx->name);

	वापस 0;
पूर्ण

अटल पूर्णांक delta_decoder_cmd(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_decoder_cmd *cmd)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(fh);
	पूर्णांक ret = 0;

	ret = delta_try_decoder_cmd(file, fh, cmd);
	अगर (ret)
		वापस ret;

	वापस delta_decoder_stop_cmd(ctx, fh);
पूर्ण

अटल पूर्णांक delta_subscribe_event(काष्ठा v4l2_fh *fh,
				 स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 2, शून्य);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* v4l2 ioctl ops */
अटल स्थिर काष्ठा v4l2_ioctl_ops delta_ioctl_ops = अणु
	.vidioc_querycap = delta_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = delta_क्रमागत_fmt_frame,
	.vidioc_g_fmt_vid_cap = delta_g_fmt_frame,
	.vidioc_try_fmt_vid_cap = delta_try_fmt_frame,
	.vidioc_s_fmt_vid_cap = delta_s_fmt_frame,
	.vidioc_क्रमागत_fmt_vid_out = delta_क्रमागत_fmt_stream,
	.vidioc_g_fmt_vid_out = delta_g_fmt_stream,
	.vidioc_try_fmt_vid_out = delta_try_fmt_stream,
	.vidioc_s_fmt_vid_out = delta_s_fmt_stream,
	.vidioc_reqbufs = v4l2_m2m_ioctl_reqbufs,
	.vidioc_create_bufs = v4l2_m2m_ioctl_create_bufs,
	.vidioc_querybuf = v4l2_m2m_ioctl_querybuf,
	.vidioc_expbuf = v4l2_m2m_ioctl_expbuf,
	.vidioc_qbuf = v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf = v4l2_m2m_ioctl_dqbuf,
	.vidioc_streamon = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff = v4l2_m2m_ioctl_streamoff,
	.vidioc_g_selection = delta_g_selection,
	.vidioc_try_decoder_cmd = delta_try_decoder_cmd,
	.vidioc_decoder_cmd = delta_decoder_cmd,
	.vidioc_subscribe_event = delta_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/*
 * mem-to-mem operations
 */

अटल व्योम delta_run_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delta_ctx *ctx = container_of(work, काष्ठा delta_ctx, run_work);
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec = ctx->dec;
	काष्ठा delta_au *au;
	काष्ठा delta_frame *frame = शून्य;
	पूर्णांक ret = 0;
	bool discard = false;
	काष्ठा vb2_v4l2_buffer *vbuf;

	अगर (!dec) अणु
		dev_err(delta->dev, "%s no decoder opened yet\n", ctx->name);
		वापस;
	पूर्ण

	/* protect instance against reentrancy */
	mutex_lock(&ctx->lock);

	vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	अगर (!vbuf) अणु
		dev_err(delta->dev, "%s no buffer to decode\n", ctx->name);
		mutex_unlock(&ctx->lock);
		वापस;
	पूर्ण
	au = to_au(vbuf);
	au->size = vb2_get_plane_payload(&vbuf->vb2_buf, 0);
	au->dts = vbuf->vb2_buf.बारtamp;

	/* dump access unit */
	dump_au(ctx, au);

	/* enable the hardware */
	अगर (!dec->pm) अणु
		ret = delta_get_sync(ctx);
		अगर (ret) अणु
			delta_put_स्वतःsuspend(ctx);
			जाओ err;
		पूर्ण
	पूर्ण

	/* decode this access unit */
	ret = call_dec_op(dec, decode, ctx, au);

	/*
	 * अगर the (-ENODATA) value is वापसed, it refers to the पूर्णांकerlaced
	 * stream हाल क्रम which 2 access units are needed to get 1 frame.
	 * So, this वापसed value करोesn't mean that the decoding fails, but
	 * indicates that the बारtamp inक्रमmation of the access unit shall
	 * not be taken पूर्णांकo account, and that the V4L2 buffer associated with
	 * the access unit shall be flagged with V4L2_BUF_FLAG_ERROR to inक्रमm
	 * the user of this situation
	 */
	अगर (ret == -ENODATA) अणु
		discard = true;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(delta->dev, "%s decoding failed (%d)\n",
			ctx->name, ret);

		/* disable the hardware */
		अगर (!dec->pm)
			delta_put_स्वतःsuspend(ctx);

		जाओ err;
	पूर्ण

	/* disable the hardware */
	अगर (!dec->pm)
		delta_put_स्वतःsuspend(ctx);

	/* push au बारtamp in FIFO */
	अगर (!discard)
		delta_push_dts(ctx, au->dts);

	/* get available decoded frames */
	जबतक (1) अणु
		ret = call_dec_op(dec, get_frame, ctx, &frame);
		अगर (ret == -ENODATA) अणु
			/* no more decoded frames */
			जाओ out;
		पूर्ण
		अगर (ret) अणु
			dev_err(delta->dev, "%s  cannot get decoded frame (%d)\n",
				ctx->name, ret);
			जाओ out;
		पूर्ण
		अगर (!frame) अणु
			dev_err(delta->dev,
				"%s  NULL decoded frame\n",
				ctx->name);
			ret = -EIO;
			जाओ out;
		पूर्ण

		/* pop बारtamp and mark frame with it */
		delta_pop_dts(ctx, &frame->dts);

		/* release decoded frame to user */
		delta_frame_करोne(ctx, frame, 0);
	पूर्ण

out:
	requeue_मुक्त_frames(ctx);
	delta_au_करोne(ctx, au, (discard ? -ENODATA : 0));
	mutex_unlock(&ctx->lock);
	v4l2_m2m_job_finish(delta->m2m_dev, ctx->fh.m2m_ctx);
	वापस;

err:
	requeue_मुक्त_frames(ctx);
	delta_au_करोne(ctx, au, ret);
	mutex_unlock(&ctx->lock);
	v4l2_m2m_job_finish(delta->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम delta_device_run(व्योम *priv)
अणु
	काष्ठा delta_ctx *ctx = priv;
	काष्ठा delta_dev *delta = ctx->dev;

	queue_work(delta->work_queue, &ctx->run_work);
पूर्ण

अटल व्योम delta_job_पात(व्योम *priv)
अणु
	काष्ठा delta_ctx *ctx = priv;
	काष्ठा delta_dev *delta = ctx->dev;

	dev_dbg(delta->dev, "%s aborting job\n", ctx->name);

	ctx->पातing = true;
पूर्ण

अटल पूर्णांक delta_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा delta_ctx *ctx = priv;
	काष्ठा delta_dev *delta = ctx->dev;
	पूर्णांक src_bufs = v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx);

	अगर (!src_bufs) अणु
		dev_dbg(delta->dev, "%s not ready: not enough video buffers.\n",
			ctx->name);
		वापस 0;
	पूर्ण

	अगर (!v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx)) अणु
		dev_dbg(delta->dev, "%s not ready: not enough video capture buffers.\n",
			ctx->name);
		वापस 0;
	पूर्ण

	अगर (ctx->पातing) अणु
		dev_dbg(delta->dev, "%s job not ready: aborting\n", ctx->name);
		वापस 0;
	पूर्ण

	dev_dbg(delta->dev, "%s job ready\n", ctx->name);

	वापस 1;
पूर्ण

/* mem-to-mem ops */
अटल स्थिर काष्ठा v4l2_m2m_ops delta_m2m_ops = अणु
	.device_run     = delta_device_run,
	.job_पढ़ोy	= delta_job_पढ़ोy,
	.job_पात      = delta_job_पात,
पूर्ण;

/*
 * VB2 queue operations
 */

अटल पूर्णांक delta_vb2_au_queue_setup(काष्ठा vb2_queue *vq,
				    अचिन्हित पूर्णांक *num_buffers,
				    अचिन्हित पूर्णांक *num_planes,
				    अचिन्हित पूर्णांक sizes[],
				    काष्ठा device *alloc_devs[])
अणु
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = ctx->max_au_size;

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	अगर (*num_buffers < 1)
		*num_buffers = 1;
	अगर (*num_buffers > DELTA_MAX_AUS)
		*num_buffers = DELTA_MAX_AUS;

	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_vb2_au_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा delta_au *au = to_au(vbuf);

	अगर (!au->prepared) अणु
		/* get memory addresses */
		au->vaddr = vb2_plane_vaddr(&au->vbuf.vb2_buf, 0);
		au->paddr = vb2_dma_contig_plane_dma_addr
				(&au->vbuf.vb2_buf, 0);
		au->prepared = true;
		dev_dbg(delta->dev, "%s au[%d] prepared; virt=0x%p, phy=0x%pad\n",
			ctx->name, vb->index, au->vaddr, &au->paddr);
	पूर्ण

	अगर (vbuf->field == V4L2_FIELD_ANY)
		vbuf->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_setup_frame(काष्ठा delta_ctx *ctx,
			     काष्ठा delta_frame *frame)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec = ctx->dec;

	अगर (frame->index >= DELTA_MAX_FRAMES) अणु
		dev_err(delta->dev,
			"%s frame index=%d exceeds output frame count (%d)\n",
			ctx->name, frame->index, DELTA_MAX_FRAMES);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->nb_of_frames >= DELTA_MAX_FRAMES) अणु
		dev_err(delta->dev,
			"%s number of frames exceeds output frame count (%d > %d)\n",
			ctx->name, ctx->nb_of_frames, DELTA_MAX_FRAMES);
		वापस -EINVAL;
	पूर्ण

	अगर (frame->index != ctx->nb_of_frames) अणु
		dev_warn(delta->dev,
			 "%s frame index discontinuity detected, expected %d, got %d\n",
			 ctx->name, ctx->nb_of_frames, frame->index);
	पूर्ण

	frame->state = DELTA_FRAME_FREE;
	ctx->frames[ctx->nb_of_frames] = frame;
	ctx->nb_of_frames++;

	/* setup frame on decoder side */
	वापस call_dec_op(dec, setup_frame, ctx, frame);
पूर्ण

/*
 * शेष implementation of get_frameinfo decoder ops
 * matching frame inक्रमmation from stream inक्रमmation
 * & with शेष pixel क्रमmat & शेष alignment.
 */
पूर्णांक delta_get_frameinfo_शेष(काष्ठा delta_ctx *ctx,
				काष्ठा delta_frameinfo *frameinfo)
अणु
	काष्ठा delta_streaminfo *streaminfo = &ctx->streaminfo;

	स_रखो(frameinfo, 0, माप(*frameinfo));
	frameinfo->pixelक्रमmat = V4L2_PIX_FMT_NV12;
	frameinfo->width = streaminfo->width;
	frameinfo->height = streaminfo->height;
	frameinfo->aligned_width = ALIGN(streaminfo->width,
					 DELTA_WIDTH_ALIGNMENT);
	frameinfo->aligned_height = ALIGN(streaminfo->height,
					  DELTA_HEIGHT_ALIGNMENT);
	frameinfo->size = frame_size(frameinfo->aligned_width,
				     frameinfo->aligned_height,
				     frameinfo->pixelक्रमmat);
	अगर (streaminfo->flags & DELTA_STREAMINFO_FLAG_CROP) अणु
		frameinfo->flags |= DELTA_FRAMEINFO_FLAG_CROP;
		frameinfo->crop = streaminfo->crop;
	पूर्ण
	अगर (streaminfo->flags & DELTA_STREAMINFO_FLAG_PIXELASPECT) अणु
		frameinfo->flags |= DELTA_FRAMEINFO_FLAG_PIXELASPECT;
		frameinfo->pixelaspect = streaminfo->pixelaspect;
	पूर्ण
	frameinfo->field = streaminfo->field;

	वापस 0;
पूर्ण

/*
 * शेष implementation of recycle decoder ops
 * consisting to relax the "decoded" frame state
 */
पूर्णांक delta_recycle_शेष(काष्ठा delta_ctx *pctx,
			  काष्ठा delta_frame *frame)
अणु
	frame->state &= ~DELTA_FRAME_DEC;

	वापस 0;
पूर्ण

अटल व्योम dump_frames_status(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	अचिन्हित पूर्णांक i;
	काष्ठा delta_frame *frame;
	अचिन्हित अक्षर str[100] = "";

	dev_info(delta->dev,
		 "%s dumping frames status...\n", ctx->name);

	क्रम (i = 0; i < ctx->nb_of_frames; i++) अणु
		frame = ctx->frames[i];
		dev_info(delta->dev,
			 "%s frame[%d] %s\n",
			 ctx->name, frame->index,
			 frame_state_str(frame->state,
					 str, माप(str)));
	पूर्ण
पूर्ण

पूर्णांक delta_get_मुक्त_frame(काष्ठा delta_ctx *ctx,
			 काष्ठा delta_frame **pframe)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा delta_frame *frame;

	*pframe = शून्य;

	vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	अगर (!vbuf) अणु
		dev_err(delta->dev, "%s no frame available",
			ctx->name);
		वापस -EIO;
	पूर्ण

	frame = to_frame(vbuf);
	frame->state &= ~DELTA_FRAME_M2M;
	अगर (frame->state != DELTA_FRAME_FREE) अणु
		dev_err(delta->dev,
			"%s frame[%d] is not free\n",
			ctx->name, frame->index);
		dump_frames_status(ctx);
		वापस -ENODATA;
	पूर्ण

	dev_dbg(delta->dev,
		"%s get free frame[%d]\n", ctx->name, frame->index);

	*pframe = frame;
	वापस 0;
पूर्ण

पूर्णांक delta_get_sync(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	पूर्णांक ret = 0;

	/* enable the hardware */
	ret = pm_runसमय_get_sync(delta->dev);
	अगर (ret < 0) अणु
		dev_err(delta->dev, "%s pm_runtime_get_sync failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम delta_put_स्वतःsuspend(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा delta_dev *delta = ctx->dev;

	pm_runसमय_put_स्वतःsuspend(delta->dev);
पूर्ण

अटल व्योम delta_vb2_au_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक delta_vb2_au_start_streaming(काष्ठा vb2_queue *q,
					अचिन्हित पूर्णांक count)
अणु
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec = ctx->dec;
	काष्ठा delta_au *au;
	पूर्णांक ret = 0;
	काष्ठा vb2_v4l2_buffer *vbuf = शून्य;
	काष्ठा delta_streaminfo *streaminfo = &ctx->streaminfo;
	काष्ठा delta_frameinfo *frameinfo = &ctx->frameinfo;
	अचिन्हित अक्षर str1[100] = "";
	अचिन्हित अक्षर str2[100] = "";

	अगर ((ctx->state != DELTA_STATE_WF_FORMAT) &&
	    (ctx->state != DELTA_STATE_WF_STREAMINFO))
		वापस 0;

	अगर (ctx->state == DELTA_STATE_WF_FORMAT) अणु
		/* खोलो decoder अगर not yet करोne */
		ret = delta_खोलो_decoder(ctx,
					 ctx->streaminfo.streamक्रमmat,
					 ctx->frameinfo.pixelक्रमmat, &dec);
		अगर (ret)
			जाओ err;
		ctx->dec = dec;
		ctx->state = DELTA_STATE_WF_STREAMINFO;
	पूर्ण

	/*
	 * first buffer should contain stream header,
	 * decode it to get the infos related to stream
	 * such as width, height, dpb, ...
	 */
	vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	अगर (!vbuf) अणु
		dev_err(delta->dev, "%s failed to start streaming, no stream header buffer enqueued\n",
			ctx->name);
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	au = to_au(vbuf);
	au->size = vb2_get_plane_payload(&vbuf->vb2_buf, 0);
	au->dts = vbuf->vb2_buf.बारtamp;

	delta_push_dts(ctx, au->dts);

	/* dump access unit */
	dump_au(ctx, au);

	/* decode this access unit */
	ret = call_dec_op(dec, decode, ctx, au);
	अगर (ret) अणु
		dev_err(delta->dev, "%s failed to start streaming, header decoding failed (%d)\n",
			ctx->name, ret);
		जाओ err;
	पूर्ण

	ret = call_dec_op(dec, get_streaminfo, ctx, streaminfo);
	अगर (ret) अणु
		dev_dbg_ratelimited(delta->dev,
				    "%s failed to start streaming, valid stream header not yet decoded\n",
				    ctx->name);
		जाओ err;
	पूर्ण
	ctx->flags |= DELTA_FLAG_STREAMINFO;

	ret = call_dec_op(dec, get_frameinfo, ctx, frameinfo);
	अगर (ret)
		जाओ err;
	ctx->flags |= DELTA_FLAG_FRAMEINFO;

	ctx->state = DELTA_STATE_READY;

	dev_dbg(delta->dev, "%s %s => %s\n", ctx->name,
		delta_streaminfo_str(streaminfo, str1, माप(str1)),
		delta_frameinfo_str(frameinfo, str2, माप(str2)));

	delta_au_करोne(ctx, au, ret);
	वापस 0;

err:
	/*
	 * वापस all buffers to vb2 in QUEUED state.
	 * This will give ownership back to userspace
	 */
	अगर (vbuf)
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_QUEUED);

	जबतक ((vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम delta_vb2_au_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;

	delta_flush_dts(ctx);

	/* वापस all buffers to vb2 in ERROR state */
	जबतक ((vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);

	ctx->au_num = 0;

	ctx->पातing = false;
पूर्ण

अटल पूर्णांक delta_vb2_frame_queue_setup(काष्ठा vb2_queue *vq,
				       अचिन्हित पूर्णांक *num_buffers,
				       अचिन्हित पूर्णांक *num_planes,
				       अचिन्हित पूर्णांक sizes[],
				       काष्ठा device *alloc_devs[])
अणु
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा delta_streaminfo *streaminfo = &ctx->streaminfo;
	काष्ठा delta_frameinfo *frameinfo = &ctx->frameinfo;
	अचिन्हित पूर्णांक size = frameinfo->size;

	/*
	 * the number of output buffers needed क्रम decoding =
	 * user need (*num_buffers given, usually क्रम display pipeline) +
	 * stream need (streaminfo->dpb) +
	 * decoding peak smoothing (depends on DELTA IP perf)
	 */
	अगर (*num_buffers < DELTA_MIN_FRAME_USER) अणु
		dev_dbg(delta->dev,
			"%s num_buffers too low (%d), increasing to %d\n",
			ctx->name, *num_buffers, DELTA_MIN_FRAME_USER);
		*num_buffers = DELTA_MIN_FRAME_USER;
	पूर्ण

	*num_buffers += streaminfo->dpb + DELTA_PEAK_FRAME_SMOOTHING;

	अगर (*num_buffers > DELTA_MAX_FRAMES) अणु
		dev_dbg(delta->dev,
			"%s output frame count too high (%d), cut to %d\n",
			ctx->name, *num_buffers, DELTA_MAX_FRAMES);
		*num_buffers = DELTA_MAX_FRAMES;
	पूर्ण

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	/* single plane क्रम Y and CbCr */
	*num_planes = 1;

	sizes[0] = size;

	ctx->nb_of_frames = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_vb2_frame_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा delta_frame *frame = to_frame(vbuf);
	पूर्णांक ret = 0;

	अगर (!frame->prepared) अणु
		frame->index = vbuf->vb2_buf.index;
		frame->vaddr = vb2_plane_vaddr(&vbuf->vb2_buf, 0);
		frame->paddr = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, 0);
		frame->info = ctx->frameinfo;

		ret = delta_setup_frame(ctx, frame);
		अगर (ret) अणु
			dev_err(delta->dev,
				"%s setup_frame() failed (%d)\n",
				ctx->name, ret);
			वापस ret;
		पूर्ण
		frame->prepared = true;
		dev_dbg(delta->dev,
			"%s frame[%d] prepared; virt=0x%p, phy=0x%pad\n",
			ctx->name, vb->index, frame->vaddr,
			&frame->paddr);
	पूर्ण

	frame->flags = vbuf->flags;

	वापस 0;
पूर्ण

अटल व्योम delta_vb2_frame_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा delta_frame *frame = to_frame(vbuf);

	/* update V4L2 fields क्रम user */
	vb2_set_plane_payload(&vbuf->vb2_buf, 0, frame->info.size);
	vb->बारtamp = frame->dts;
	vbuf->field = frame->field;
	vbuf->flags = frame->flags;
पूर्ण

अटल व्योम delta_vb2_frame_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा delta_frame *frame = to_frame(vbuf);

	अगर (ctx->state == DELTA_STATE_WF_EOS) अणु
		/* new frame available, EOS can now be completed */
		delta_complete_eos(ctx, frame);

		ctx->state = DELTA_STATE_EOS;

		/* वापस, no need to recycle this buffer to decoder */
		वापस;
	पूर्ण

	/* recycle this frame */
	delta_recycle(ctx, frame);
पूर्ण

अटल व्योम delta_vb2_frame_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा delta_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा delta_frame *frame;
	स्थिर काष्ठा delta_dec *dec = ctx->dec;
	अचिन्हित पूर्णांक i;

	delta_flush_dts(ctx);

	call_dec_op(dec, flush, ctx);

	/*
	 * वापस all buffers to vb2 in ERROR state
	 * & reset each frame state to OUT
	 */
	क्रम (i = 0; i < ctx->nb_of_frames; i++) अणु
		frame = ctx->frames[i];
		अगर (!(frame->state & DELTA_FRAME_OUT)) अणु
			vbuf = &frame->vbuf;
			v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
		पूर्ण
		frame->state = DELTA_FRAME_OUT;
	पूर्ण

	ctx->frame_num = 0;

	ctx->पातing = false;
पूर्ण

/* VB2 queue ops */
अटल स्थिर काष्ठा vb2_ops delta_vb2_au_ops = अणु
	.queue_setup = delta_vb2_au_queue_setup,
	.buf_prepare = delta_vb2_au_prepare,
	.buf_queue = delta_vb2_au_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = delta_vb2_au_start_streaming,
	.stop_streaming = delta_vb2_au_stop_streaming,
पूर्ण;

अटल स्थिर काष्ठा vb2_ops delta_vb2_frame_ops = अणु
	.queue_setup = delta_vb2_frame_queue_setup,
	.buf_prepare = delta_vb2_frame_prepare,
	.buf_finish = delta_vb2_frame_finish,
	.buf_queue = delta_vb2_frame_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.stop_streaming = delta_vb2_frame_stop_streaming,
पूर्ण;

/*
 * V4L2 file operations
 */

अटल पूर्णांक queue_init(व्योम *priv,
		      काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा vb2_queue *q;
	काष्ठा delta_ctx *ctx = priv;
	काष्ठा delta_dev *delta = ctx->dev;
	पूर्णांक ret;

	/* setup vb2 queue क्रम stream input */
	q = src_vq;
	q->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->drv_priv = ctx;
	/* overload vb2 buf with निजी au काष्ठा */
	q->buf_काष्ठा_size = माप(काष्ठा delta_au);
	q->ops = &delta_vb2_au_ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	q->lock = &delta->lock;
	q->dev = delta->dev;

	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;

	/* setup vb2 queue क्रम frame output */
	q = dst_vq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->drv_priv = ctx;
	/* overload vb2 buf with निजी frame काष्ठा */
	q->buf_काष्ठा_size = माप(काष्ठा delta_frame)
			     + DELTA_MAX_FRAME_PRIV_SIZE;
	q->ops = &delta_vb2_frame_ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	q->lock = &delta->lock;
	q->dev = delta->dev;

	वापस vb2_queue_init(q);
पूर्ण

अटल पूर्णांक delta_खोलो(काष्ठा file *file)
अणु
	काष्ठा delta_dev *delta = video_drvdata(file);
	काष्ठा delta_ctx *ctx = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&delta->lock);

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ctx->dev = delta;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	INIT_WORK(&ctx->run_work, delta_run_work);
	mutex_init(&ctx->lock);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(delta->m2m_dev, ctx,
					    queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		dev_err(delta->dev, "%s failed to initialize m2m context (%d)\n",
			DELTA_PREFIX, ret);
		जाओ err_fh_del;
	पूर्ण

	/*
	 * रुको stream क्रमmat to determine which
	 * decoder to खोलो
	 */
	ctx->state = DELTA_STATE_WF_FORMAT;

	INIT_LIST_HEAD(&ctx->dts);

	/* set the instance name */
	delta->instance_id++;
	snम_लिखो(ctx->name, माप(ctx->name), "[%3d:----]",
		 delta->instance_id);

	/* शेष parameters क्रम frame and stream */
	set_शेष_params(ctx);

	/* enable ST231 घड़ीs */
	अगर (delta->clk_st231)
		अगर (clk_prepare_enable(delta->clk_st231))
			dev_warn(delta->dev, "failed to enable st231 clk\n");

	/* enable FLASH_PROMIP घड़ी */
	अगर (delta->clk_flash_promip)
		अगर (clk_prepare_enable(delta->clk_flash_promip))
			dev_warn(delta->dev, "failed to enable delta promip clk\n");

	mutex_unlock(&delta->lock);

	dev_dbg(delta->dev, "%s decoder instance created\n", ctx->name);

	वापस 0;

err_fh_del:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
err:
	mutex_unlock(&delta->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक delta_release(काष्ठा file *file)
अणु
	काष्ठा delta_ctx *ctx = to_ctx(file->निजी_data);
	काष्ठा delta_dev *delta = ctx->dev;
	स्थिर काष्ठा delta_dec *dec = ctx->dec;

	mutex_lock(&delta->lock);

	/* बंद decoder */
	call_dec_op(dec, बंद, ctx);

	/*
	 * trace a summary of instance
	 * beक्रमe closing (debug purpose)
	 */
	delta_trace_summary(ctx);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);

	/* disable ST231 घड़ीs */
	अगर (delta->clk_st231)
		clk_disable_unprepare(delta->clk_st231);

	/* disable FLASH_PROMIP घड़ी */
	अगर (delta->clk_flash_promip)
		clk_disable_unprepare(delta->clk_flash_promip);

	dev_dbg(delta->dev, "%s decoder instance released\n", ctx->name);

	kमुक्त(ctx);

	mutex_unlock(&delta->lock);
	वापस 0;
पूर्ण

/* V4L2 file ops */
अटल स्थिर काष्ठा v4l2_file_operations delta_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = delta_खोलो,
	.release = delta_release,
	.unlocked_ioctl = video_ioctl2,
	.mmap = v4l2_m2m_fop_mmap,
	.poll = v4l2_m2m_fop_poll,
पूर्ण;

/*
 * Platक्रमm device operations
 */

अटल पूर्णांक delta_रेजिस्टर_device(काष्ठा delta_dev *delta)
अणु
	पूर्णांक ret;
	काष्ठा video_device *vdev;

	अगर (!delta)
		वापस -ENODEV;

	delta->m2m_dev = v4l2_m2m_init(&delta_m2m_ops);
	अगर (IS_ERR(delta->m2m_dev)) अणु
		dev_err(delta->dev, "%s failed to initialize v4l2-m2m device\n",
			DELTA_PREFIX);
		ret = PTR_ERR(delta->m2m_dev);
		जाओ err;
	पूर्ण

	vdev = video_device_alloc();
	अगर (!vdev) अणु
		dev_err(delta->dev, "%s failed to allocate video device\n",
			DELTA_PREFIX);
		ret = -ENOMEM;
		जाओ err_m2m_release;
	पूर्ण

	vdev->fops = &delta_fops;
	vdev->ioctl_ops = &delta_ioctl_ops;
	vdev->release = video_device_release;
	vdev->lock = &delta->lock;
	vdev->vfl_dir = VFL_सूची_M2M;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;
	vdev->v4l2_dev = &delta->v4l2_dev;
	snम_लिखो(vdev->name, माप(vdev->name), "%s-%s",
		 DELTA_NAME, DELTA_FW_VERSION);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(delta->dev, "%s failed to register video device\n",
			DELTA_PREFIX);
		जाओ err_vdev_release;
	पूर्ण

	delta->vdev = vdev;
	video_set_drvdata(vdev, delta);
	वापस 0;

err_vdev_release:
	video_device_release(vdev);
err_m2m_release:
	v4l2_m2m_release(delta->m2m_dev);
err:
	वापस ret;
पूर्ण

अटल व्योम delta_unरेजिस्टर_device(काष्ठा delta_dev *delta)
अणु
	अगर (!delta)
		वापस;

	अगर (delta->m2m_dev)
		v4l2_m2m_release(delta->m2m_dev);

	video_unरेजिस्टर_device(delta->vdev);
पूर्ण

अटल पूर्णांक delta_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा delta_dev *delta;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	delta = devm_kzalloc(dev, माप(*delta), GFP_KERNEL);
	अगर (!delta) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	delta->dev = dev;
	delta->pdev = pdev;
	platक्रमm_set_drvdata(pdev, delta);

	mutex_init(&delta->lock);

	/* get घड़ी resources */
	delta->clk_delta = devm_clk_get(dev, "delta");
	अगर (IS_ERR(delta->clk_delta)) अणु
		dev_dbg(dev, "%s can't get delta clock\n", DELTA_PREFIX);
		delta->clk_delta = शून्य;
	पूर्ण

	delta->clk_st231 = devm_clk_get(dev, "delta-st231");
	अगर (IS_ERR(delta->clk_st231)) अणु
		dev_dbg(dev, "%s can't get delta-st231 clock\n", DELTA_PREFIX);
		delta->clk_st231 = शून्य;
	पूर्ण

	delta->clk_flash_promip = devm_clk_get(dev, "delta-flash-promip");
	अगर (IS_ERR(delta->clk_flash_promip)) अणु
		dev_dbg(dev, "%s can't get delta-flash-promip clock\n",
			DELTA_PREFIX);
		delta->clk_flash_promip = शून्य;
	पूर्ण

	/* init pm_runसमय used क्रम घातer management */
	pm_runसमय_set_स्वतःsuspend_delay(dev, DELTA_HW_AUTOSUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_enable(dev);

	/* init firmware ipc channel */
	ret = delta_ipc_init(delta);
	अगर (ret) अणु
		dev_err(delta->dev, "%s failed to initialize firmware ipc channel\n",
			DELTA_PREFIX);
		जाओ err;
	पूर्ण

	/* रेजिस्टर all available decoders */
	रेजिस्टर_decoders(delta);

	/* रेजिस्टर all supported क्रमmats */
	रेजिस्टर_क्रमmats(delta);

	/* रेजिस्टर on V4L2 */
	ret = v4l2_device_रेजिस्टर(dev, &delta->v4l2_dev);
	अगर (ret) अणु
		dev_err(delta->dev, "%s failed to register V4L2 device\n",
			DELTA_PREFIX);
		जाओ err;
	पूर्ण

	delta->work_queue = create_workqueue(DELTA_NAME);
	अगर (!delta->work_queue) अणु
		dev_err(delta->dev, "%s failed to allocate work queue\n",
			DELTA_PREFIX);
		ret = -ENOMEM;
		जाओ err_v4l2;
	पूर्ण

	/* रेजिस्टर device */
	ret = delta_रेजिस्टर_device(delta);
	अगर (ret)
		जाओ err_work_queue;

	dev_info(dev, "%s %s registered as /dev/video%d\n",
		 DELTA_PREFIX, delta->vdev->name, delta->vdev->num);

	वापस 0;

err_work_queue:
	destroy_workqueue(delta->work_queue);
err_v4l2:
	v4l2_device_unरेजिस्टर(&delta->v4l2_dev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक delta_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा delta_dev *delta = platक्रमm_get_drvdata(pdev);

	delta_ipc_निकास(delta);

	delta_unरेजिस्टर_device(delta);

	destroy_workqueue(delta->work_queue);

	pm_runसमय_put_स्वतःsuspend(delta->dev);
	pm_runसमय_disable(delta->dev);

	v4l2_device_unरेजिस्टर(&delta->v4l2_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक delta_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा delta_dev *delta = dev_get_drvdata(dev);

	अगर (delta->clk_delta)
		clk_disable_unprepare(delta->clk_delta);

	वापस 0;
पूर्ण

अटल पूर्णांक delta_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा delta_dev *delta = dev_get_drvdata(dev);

	अगर (delta->clk_delta)
		अगर (clk_prepare_enable(delta->clk_delta))
			dev_warn(dev, "failed to prepare/enable delta clk\n");

	वापस 0;
पूर्ण

/* PM ops */
अटल स्थिर काष्ठा dev_pm_ops delta_pm_ops = अणु
	.runसमय_suspend = delta_runसमय_suspend,
	.runसमय_resume = delta_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id delta_match_types[] = अणु
	अणु
	 .compatible = "st,st-delta",
	पूर्ण,
	अणु
	 /* end node */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, delta_match_types);

अटल काष्ठा platक्रमm_driver delta_driver = अणु
	.probe = delta_probe,
	.हटाओ = delta_हटाओ,
	.driver = अणु
		   .name = DELTA_NAME,
		   .of_match_table = delta_match_types,
		   .pm = &delta_pm_opsपूर्ण,
पूर्ण;

module_platक्रमm_driver(delta_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hugues Fruchet <hugues.fruchet@st.com>");
MODULE_DESCRIPTION("STMicroelectronics DELTA video decoder V4L2 driver");
