<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "hva.h"
#समावेश "hva-hw.h"

#घोषणा MIN_FRAMES	1
#घोषणा MIN_STREAMS	1

#घोषणा HVA_MIN_WIDTH	32
#घोषणा HVA_MAX_WIDTH	1920
#घोषणा HVA_MIN_HEIGHT	32
#घोषणा HVA_MAX_HEIGHT	1920

/* HVA requires a 16x16 pixels alignment क्रम frames */
#घोषणा HVA_WIDTH_ALIGNMENT	16
#घोषणा HVA_HEIGHT_ALIGNMENT	16

#घोषणा HVA_DEFAULT_WIDTH	HVA_MIN_WIDTH
#घोषणा	HVA_DEFAULT_HEIGHT	HVA_MIN_HEIGHT
#घोषणा HVA_DEFAULT_FRAME_NUM	1
#घोषणा HVA_DEFAULT_FRAME_DEN	30

#घोषणा to_type_str(type) (type == V4L2_BUF_TYPE_VIDEO_OUTPUT ? \
			   "frame" : "stream")

#घोषणा fh_to_ctx(f)    (container_of(f, काष्ठा hva_ctx, fh))

/* registry of available encoders */
अटल स्थिर काष्ठा hva_enc *hva_encoders[] = अणु
	&nv12h264enc,
	&nv21h264enc,
पूर्ण;

अटल अंतरभूत पूर्णांक frame_size(u32 w, u32 h, u32 fmt)
अणु
	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		वापस (w * h * 3) / 2;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक frame_stride(u32 w, u32 fmt)
अणु
	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		वापस w;
	शेष:
		वापस 0;
	पूर्ण
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

अटल अंतरभूत पूर्णांक estimated_stream_size(u32 w, u32 h)
अणु
	/*
	 * HVA only encodes in YUV420 क्रमmat, whatever the frame क्रमmat.
	 * A compression ratio of 2 is assumed: thus, the maximum size
	 * of a stream is estimated to ((width x height x 3 / 2) / 2)
	 */
	वापस (w * h * 3) / 4;
पूर्ण

अटल व्योम set_शेष_params(काष्ठा hva_ctx *ctx)
अणु
	काष्ठा hva_frameinfo *frameinfo = &ctx->frameinfo;
	काष्ठा hva_streaminfo *streaminfo = &ctx->streaminfo;

	frameinfo->pixelक्रमmat = V4L2_PIX_FMT_NV12;
	frameinfo->width = HVA_DEFAULT_WIDTH;
	frameinfo->height = HVA_DEFAULT_HEIGHT;
	frameinfo->aligned_width = ALIGN(frameinfo->width,
					 HVA_WIDTH_ALIGNMENT);
	frameinfo->aligned_height = ALIGN(frameinfo->height,
					  HVA_HEIGHT_ALIGNMENT);
	frameinfo->size = frame_size(frameinfo->aligned_width,
				     frameinfo->aligned_height,
				     frameinfo->pixelक्रमmat);

	streaminfo->streamक्रमmat = V4L2_PIX_FMT_H264;
	streaminfo->width = HVA_DEFAULT_WIDTH;
	streaminfo->height = HVA_DEFAULT_HEIGHT;

	ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	ctx->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	ctx->quantization = V4L2_QUANTIZATION_DEFAULT;

	ctx->max_stream_size = estimated_stream_size(streaminfo->width,
						     streaminfo->height);
पूर्ण

अटल स्थिर काष्ठा hva_enc *hva_find_encoder(काष्ठा hva_ctx *ctx,
					      u32 pixelक्रमmat,
					      u32 streamक्रमmat)
अणु
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);
	स्थिर काष्ठा hva_enc *enc;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hva->nb_of_encoders; i++) अणु
		enc = hva->encoders[i];
		अगर ((enc->pixelक्रमmat == pixelक्रमmat) &&
		    (enc->streamक्रमmat == streamक्रमmat))
			वापस enc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम रेजिस्टर_क्रमmat(u32 क्रमmat, u32 क्रमmats[], u32 *nb_of_क्रमmats)
अणु
	u32 i;
	bool found = false;

	क्रम (i = 0; i < *nb_of_क्रमmats; i++) अणु
		अगर (क्रमmat == क्रमmats[i]) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		क्रमmats[(*nb_of_क्रमmats)++] = क्रमmat;
पूर्ण

अटल व्योम रेजिस्टर_क्रमmats(काष्ठा hva_dev *hva)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hva->nb_of_encoders; i++) अणु
		रेजिस्टर_क्रमmat(hva->encoders[i]->pixelक्रमmat,
				hva->pixelक्रमmats,
				&hva->nb_of_pixelक्रमmats);

		रेजिस्टर_क्रमmat(hva->encoders[i]->streamक्रमmat,
				hva->streamक्रमmats,
				&hva->nb_of_streamक्रमmats);
	पूर्ण
पूर्ण

अटल व्योम रेजिस्टर_encoders(काष्ठा hva_dev *hva)
अणु
	काष्ठा device *dev = hva_to_dev(hva);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hva_encoders); i++) अणु
		अगर (hva->nb_of_encoders >= HVA_MAX_ENCODERS) अणु
			dev_dbg(dev,
				"%s failed to register %s encoder (%d maximum reached)\n",
				HVA_PREFIX, hva_encoders[i]->name,
				HVA_MAX_ENCODERS);
			वापस;
		पूर्ण

		hva->encoders[hva->nb_of_encoders++] = hva_encoders[i];
		dev_info(dev, "%s %s encoder registered\n", HVA_PREFIX,
			 hva_encoders[i]->name);
	पूर्ण
पूर्ण

अटल पूर्णांक hva_खोलो_encoder(काष्ठा hva_ctx *ctx, u32 streamक्रमmat,
			    u32 pixelक्रमmat, काष्ठा hva_enc **penc)
अणु
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा hva_enc *enc;
	पूर्णांक ret;

	/* find an encoder which can deal with these क्रमmats */
	enc = (काष्ठा hva_enc *)hva_find_encoder(ctx, pixelक्रमmat,
						 streamक्रमmat);
	अगर (!enc) अणु
		dev_err(dev, "%s no encoder found matching %4.4s => %4.4s\n",
			ctx->name, (अक्षर *)&pixelक्रमmat, (अक्षर *)&streamक्रमmat);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "%s one encoder matching %4.4s => %4.4s\n",
		ctx->name, (अक्षर *)&pixelक्रमmat, (अक्षर *)&streamक्रमmat);

	/* update instance name */
	snम_लिखो(ctx->name, माप(ctx->name), "[%3d:%4.4s]",
		 hva->instance_id, (अक्षर *)&streamक्रमmat);

	/* खोलो encoder instance */
	ret = enc->खोलो(ctx);
	अगर (ret) अणु
		dev_err(dev, "%s failed to open encoder instance (%d)\n",
			ctx->name, ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%s %s encoder opened\n", ctx->name, enc->name);

	*penc = enc;

	वापस ret;
पूर्ण

अटल व्योम hva_dbg_summary(काष्ठा hva_ctx *ctx)
अणु
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा hva_streaminfo *stream = &ctx->streaminfo;
	काष्ठा hva_frameinfo *frame = &ctx->frameinfo;

	अगर (!(ctx->flags & HVA_FLAG_STREAMINFO))
		वापस;

	dev_dbg(dev, "%s %4.4s %dx%d > %4.4s %dx%d %s %s: %d frames encoded, %d system errors, %d encoding errors, %d frame errors\n",
		ctx->name,
		(अक्षर *)&frame->pixelक्रमmat,
		frame->aligned_width, frame->aligned_height,
		(अक्षर *)&stream->streamक्रमmat,
		stream->width, stream->height,
		stream->profile, stream->level,
		ctx->encoded_frames,
		ctx->sys_errors,
		ctx->encode_errors,
		ctx->frame_errors);
पूर्ण

/*
 * V4L2 ioctl operations
 */

अटल पूर्णांक hva_querycap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_capability *cap)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);

	strscpy(cap->driver, HVA_NAME, माप(cap->driver));
	strscpy(cap->card, hva->vdev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 hva->pdev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक hva_क्रमागत_fmt_stream(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);

	अगर (unlikely(f->index >= hva->nb_of_streamक्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = hva->streamक्रमmats[f->index];

	वापस 0;
पूर्ण

अटल पूर्णांक hva_क्रमागत_fmt_frame(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);

	अगर (unlikely(f->index >= hva->nb_of_pixelक्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = hva->pixelक्रमmats[f->index];

	वापस 0;
पूर्ण

अटल पूर्णांक hva_g_fmt_stream(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा hva_streaminfo *streaminfo = &ctx->streaminfo;

	f->fmt.pix.width = streaminfo->width;
	f->fmt.pix.height = streaminfo->height;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;
	f->fmt.pix.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix.quantization = ctx->quantization;
	f->fmt.pix.pixelक्रमmat = streaminfo->streamक्रमmat;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = ctx->max_stream_size;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_g_fmt_frame(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा hva_frameinfo *frameinfo = &ctx->frameinfo;

	f->fmt.pix.width = frameinfo->width;
	f->fmt.pix.height = frameinfo->height;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;
	f->fmt.pix.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix.quantization = ctx->quantization;
	f->fmt.pix.pixelक्रमmat = frameinfo->pixelक्रमmat;
	f->fmt.pix.bytesperline = frame_stride(frameinfo->aligned_width,
					       frameinfo->pixelक्रमmat);
	f->fmt.pix.sizeimage = frameinfo->size;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_try_fmt_stream(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	u32 streamक्रमmat = pix->pixelक्रमmat;
	स्थिर काष्ठा hva_enc *enc;
	u32 width, height;
	u32 stream_size;

	enc = hva_find_encoder(ctx, ctx->frameinfo.pixelक्रमmat, streamक्रमmat);
	अगर (!enc) अणु
		dev_dbg(dev,
			"%s V4L2 TRY_FMT (CAPTURE): unsupported format %.4s\n",
			ctx->name, (अक्षर *)&pix->pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	width = pix->width;
	height = pix->height;
	अगर (ctx->flags & HVA_FLAG_FRAMEINFO) अणु
		/*
		 * अगर the frame resolution is alपढ़ोy fixed, only allow the
		 * same stream resolution
		 */
		pix->width = ctx->frameinfo.width;
		pix->height = ctx->frameinfo.height;
		अगर ((pix->width != width) || (pix->height != height))
			dev_dbg(dev,
				"%s V4L2 TRY_FMT (CAPTURE): resolution updated %dx%d -> %dx%d to fit frame resolution\n",
				ctx->name, width, height,
				pix->width, pix->height);
	पूर्ण अन्यथा अणु
		/* adjust width & height */
		v4l_bound_align_image(&pix->width,
				      HVA_MIN_WIDTH, enc->max_width,
				      0,
				      &pix->height,
				      HVA_MIN_HEIGHT, enc->max_height,
				      0,
				      0);

		अगर ((pix->width != width) || (pix->height != height))
			dev_dbg(dev,
				"%s V4L2 TRY_FMT (CAPTURE): resolution updated %dx%d -> %dx%d to fit min/max/alignment\n",
				ctx->name, width, height,
				pix->width, pix->height);
	पूर्ण

	stream_size = estimated_stream_size(pix->width, pix->height);
	अगर (pix->sizeimage < stream_size)
		pix->sizeimage = stream_size;

	pix->bytesperline = 0;
	pix->colorspace = ctx->colorspace;
	pix->xfer_func = ctx->xfer_func;
	pix->ycbcr_enc = ctx->ycbcr_enc;
	pix->quantization = ctx->quantization;
	pix->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_try_fmt_frame(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	u32 pixelक्रमmat = pix->pixelक्रमmat;
	स्थिर काष्ठा hva_enc *enc;
	u32 width, height;

	enc = hva_find_encoder(ctx, pixelक्रमmat, ctx->streaminfo.streamक्रमmat);
	अगर (!enc) अणु
		dev_dbg(dev,
			"%s V4L2 TRY_FMT (OUTPUT): unsupported format %.4s\n",
			ctx->name, (अक्षर *)&pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* adjust width & height */
	width = pix->width;
	height = pix->height;
	v4l_bound_align_image(&pix->width,
			      HVA_MIN_WIDTH, HVA_MAX_WIDTH,
			      frame_alignment(pixelक्रमmat) - 1,
			      &pix->height,
			      HVA_MIN_HEIGHT, HVA_MAX_HEIGHT,
			      frame_alignment(pixelक्रमmat) - 1,
			      0);

	अगर ((pix->width != width) || (pix->height != height))
		dev_dbg(dev,
			"%s V4L2 TRY_FMT (OUTPUT): resolution updated %dx%d -> %dx%d to fit min/max/alignment\n",
			ctx->name, width, height, pix->width, pix->height);

	width = ALIGN(pix->width, HVA_WIDTH_ALIGNMENT);
	height = ALIGN(pix->height, HVA_HEIGHT_ALIGNMENT);

	अगर (!pix->colorspace) अणु
		pix->colorspace = V4L2_COLORSPACE_REC709;
		pix->xfer_func = V4L2_XFER_FUNC_DEFAULT;
		pix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		pix->quantization = V4L2_QUANTIZATION_DEFAULT;
	पूर्ण

	pix->bytesperline = frame_stride(width, pixelक्रमmat);
	pix->sizeimage = frame_size(width, height, pixelक्रमmat);
	pix->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_s_fmt_stream(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	ret = hva_try_fmt_stream(file, fh, f);
	अगर (ret) अणु
		dev_dbg(dev, "%s V4L2 S_FMT (CAPTURE): unsupported format %.4s\n",
			ctx->name, (अक्षर *)&f->fmt.pix.pixelक्रमmat);
		वापस ret;
	पूर्ण

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_streaming(vq)) अणु
		dev_dbg(dev, "%s V4L2 S_FMT (CAPTURE): queue busy\n",
			ctx->name);
		वापस -EBUSY;
	पूर्ण

	ctx->max_stream_size = f->fmt.pix.sizeimage;
	ctx->streaminfo.width = f->fmt.pix.width;
	ctx->streaminfo.height = f->fmt.pix.height;
	ctx->streaminfo.streamक्रमmat = f->fmt.pix.pixelक्रमmat;
	ctx->flags |= HVA_FLAG_STREAMINFO;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_s_fmt_frame(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	ret = hva_try_fmt_frame(file, fh, f);
	अगर (ret) अणु
		dev_dbg(dev, "%s V4L2 S_FMT (OUTPUT): unsupported format %.4s\n",
			ctx->name, (अक्षर *)&pix->pixelक्रमmat);
		वापस ret;
	पूर्ण

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_streaming(vq)) अणु
		dev_dbg(dev, "%s V4L2 S_FMT (OUTPUT): queue busy\n", ctx->name);
		वापस -EBUSY;
	पूर्ण

	ctx->colorspace = pix->colorspace;
	ctx->xfer_func = pix->xfer_func;
	ctx->ycbcr_enc = pix->ycbcr_enc;
	ctx->quantization = pix->quantization;

	ctx->frameinfo.aligned_width = ALIGN(pix->width, HVA_WIDTH_ALIGNMENT);
	ctx->frameinfo.aligned_height = ALIGN(pix->height,
					      HVA_HEIGHT_ALIGNMENT);
	ctx->frameinfo.size = pix->sizeimage;
	ctx->frameinfo.pixelक्रमmat = pix->pixelक्रमmat;
	ctx->frameinfo.width = pix->width;
	ctx->frameinfo.height = pix->height;
	ctx->flags |= HVA_FLAG_FRAMEINFO;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा v4l2_fract *समय_per_frame = &ctx->ctrls.समय_per_frame;

	अगर (sp->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	sp->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	sp->parm.output.समयperframe.numerator = समय_per_frame->numerator;
	sp->parm.output.समयperframe.denominator =
		समय_per_frame->denominator;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा v4l2_fract *समय_per_frame = &ctx->ctrls.समय_per_frame;

	अगर (sp->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	अगर (!sp->parm.output.समयperframe.numerator ||
	    !sp->parm.output.समयperframe.denominator)
		वापस hva_g_parm(file, fh, sp);

	sp->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	समय_per_frame->numerator = sp->parm.output.समयperframe.numerator;
	समय_per_frame->denominator =
		sp->parm.output.समयperframe.denominator;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा device *dev = ctx_to_dev(ctx);

	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		/*
		 * depending on the targeted compressed video क्रमmat, the
		 * capture buffer might contain headers (e.g. H.264 SPS/PPS)
		 * filled in by the driver client; the size of these data is
		 * copied from the bytesused field of the V4L2 buffer in the
		 * payload field of the hva stream buffer
		 */
		काष्ठा vb2_queue *vq;
		काष्ठा hva_stream *stream;
		काष्ठा vb2_buffer *vb2_buf;

		vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, buf->type);

		अगर (buf->index >= vq->num_buffers) अणु
			dev_dbg(dev, "%s buffer index %d out of range (%d)\n",
				ctx->name, buf->index, vq->num_buffers);
			वापस -EINVAL;
		पूर्ण

		vb2_buf = vb2_get_buffer(vq, buf->index);
		stream = to_hva_stream(to_vb2_v4l2_buffer(vb2_buf));
		stream->bytesused = buf->bytesused;
	पूर्ण

	वापस v4l2_m2m_qbuf(file, ctx->fh.m2m_ctx, buf);
पूर्ण

/* V4L2 ioctl ops */
अटल स्थिर काष्ठा v4l2_ioctl_ops hva_ioctl_ops = अणु
	.vidioc_querycap		= hva_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= hva_क्रमागत_fmt_stream,
	.vidioc_क्रमागत_fmt_vid_out	= hva_क्रमागत_fmt_frame,
	.vidioc_g_fmt_vid_cap		= hva_g_fmt_stream,
	.vidioc_g_fmt_vid_out		= hva_g_fmt_frame,
	.vidioc_try_fmt_vid_cap		= hva_try_fmt_stream,
	.vidioc_try_fmt_vid_out		= hva_try_fmt_frame,
	.vidioc_s_fmt_vid_cap		= hva_s_fmt_stream,
	.vidioc_s_fmt_vid_out		= hva_s_fmt_frame,
	.vidioc_g_parm			= hva_g_parm,
	.vidioc_s_parm			= hva_s_parm,
	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_create_bufs             = v4l2_m2m_ioctl_create_bufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_qbuf			= hva_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/*
 * V4L2 control operations
 */

अटल पूर्णांक hva_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hva_ctx *ctx = container_of(ctrl->handler, काष्ठा hva_ctx,
					   ctrl_handler);
	काष्ठा device *dev = ctx_to_dev(ctx);

	dev_dbg(dev, "%s S_CTRL: id = %d, val = %d\n", ctx->name,
		ctrl->id, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctx->ctrls.bitrate_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctx->ctrls.gop_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		ctx->ctrls.bitrate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		ctx->ctrls.aspect = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
		ctx->ctrls.profile = ctrl->val;
		snम_लिखो(ctx->streaminfo.profile,
			 माप(ctx->streaminfo.profile),
			 "%s profile",
			 v4l2_ctrl_get_menu(ctrl->id)[ctrl->val]);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		ctx->ctrls.level = ctrl->val;
		snम_लिखो(ctx->streaminfo.level,
			 माप(ctx->streaminfo.level),
			 "level %s",
			 v4l2_ctrl_get_menu(ctrl->id)[ctrl->val]);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		ctx->ctrls.entropy_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE:
		ctx->ctrls.cpb_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:
		ctx->ctrls.dct8x8 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		ctx->ctrls.qpmin = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		ctx->ctrls.qpmax = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:
		ctx->ctrls.vui_sar = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
		ctx->ctrls.vui_sar_idc = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING:
		ctx->ctrls.sei_fp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:
		ctx->ctrls.sei_fp_type = ctrl->val;
		अवरोध;
	शेष:
		dev_dbg(dev, "%s S_CTRL: invalid control (id = %d)\n",
			ctx->name, ctrl->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* V4L2 control ops */
अटल स्थिर काष्ठा v4l2_ctrl_ops hva_ctrl_ops = अणु
	.s_ctrl = hva_s_ctrl,
पूर्ण;

अटल पूर्णांक hva_ctrls_setup(काष्ठा hva_ctx *ctx)
अणु
	काष्ठा device *dev = ctx_to_dev(ctx);
	u64 mask;
	क्रमागत v4l2_mpeg_video_h264_sei_fp_arrangement_type sei_fp_type =
		V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_TOP_BOTTOM;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 15);

	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
			       V4L2_MPEG_VIDEO_BITRATE_MODE_CBR,
			       0,
			       V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			  1, 60, 1, 16);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_BITRATE,
			  1000, 60000000, 1000, 20000000);

	mask = ~(1 << V4L2_MPEG_VIDEO_ASPECT_1x1);
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_ASPECT,
			       V4L2_MPEG_VIDEO_ASPECT_1x1,
			       mask,
			       V4L2_MPEG_VIDEO_ASPECT_1x1);

	mask = ~((1 << V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE) |
		 (1 << V4L2_MPEG_VIDEO_H264_PROखाता_MAIN) |
		 (1 << V4L2_MPEG_VIDEO_H264_PROखाता_HIGH) |
		 (1 << V4L2_MPEG_VIDEO_H264_PROखाता_STEREO_HIGH));
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_PROखाता,
			       V4L2_MPEG_VIDEO_H264_PROखाता_STEREO_HIGH,
			       mask,
			       V4L2_MPEG_VIDEO_H264_PROखाता_HIGH);

	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			       V4L2_MPEG_VIDEO_H264_LEVEL_4_2,
			       0,
			       V4L2_MPEG_VIDEO_H264_LEVEL_4_0);

	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE,
			       V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC,
			       0,
			       V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE,
			  1, 10000, 1, 3000);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM,
			  0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_MIN_QP,
			  0, 51, 1, 5);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_MAX_QP,
			  0, 51, 1, 51);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE,
			  0, 1, 1, 1);

	mask = ~(1 << V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1);
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC,
			       V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1,
			       mask,
			       V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING,
			  0, 1, 1, 0);

	mask = ~(1 << sei_fp_type);
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE,
			       sei_fp_type,
			       mask,
			       sei_fp_type);

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;

		dev_dbg(dev, "%s controls setup failed (%d)\n",
			ctx->name, err);
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		वापस err;
	पूर्ण

	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);

	/* set शेष समय per frame */
	ctx->ctrls.समय_per_frame.numerator = HVA_DEFAULT_FRAME_NUM;
	ctx->ctrls.समय_per_frame.denominator = HVA_DEFAULT_FRAME_DEN;

	वापस 0;
पूर्ण

/*
 * mem-to-mem operations
 */

अटल व्योम hva_run_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hva_ctx *ctx = container_of(work, काष्ठा hva_ctx, run_work);
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	स्थिर काष्ठा hva_enc *enc = ctx->enc;
	काष्ठा hva_frame *frame;
	काष्ठा hva_stream *stream;
	पूर्णांक ret;

	/* protect instance against reentrancy */
	mutex_lock(&ctx->lock);

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_perf_begin(ctx);
#पूर्ण_अगर

	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	frame = to_hva_frame(src_buf);
	stream = to_hva_stream(dst_buf);
	frame->vbuf.sequence = ctx->frame_num++;

	ret = enc->encode(ctx, frame, stream);

	vb2_set_plane_payload(&dst_buf->vb2_buf, 0, stream->bytesused);
	अगर (ret) अणु
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		/* propagate frame बारtamp */
		dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;
		dst_buf->field = V4L2_FIELD_NONE;
		dst_buf->sequence = ctx->stream_num - 1;

		ctx->encoded_frames++;

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
		hva_dbg_perf_end(ctx, stream);
#पूर्ण_अगर

		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	mutex_unlock(&ctx->lock);

	v4l2_m2m_job_finish(ctx->hva_dev->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम hva_device_run(व्योम *priv)
अणु
	काष्ठा hva_ctx *ctx = priv;
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);

	queue_work(hva->work_queue, &ctx->run_work);
पूर्ण

अटल व्योम hva_job_पात(व्योम *priv)
अणु
	काष्ठा hva_ctx *ctx = priv;
	काष्ठा device *dev = ctx_to_dev(ctx);

	dev_dbg(dev, "%s aborting job\n", ctx->name);

	ctx->पातing = true;
पूर्ण

अटल पूर्णांक hva_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा hva_ctx *ctx = priv;
	काष्ठा device *dev = ctx_to_dev(ctx);

	अगर (!v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx)) अणु
		dev_dbg(dev, "%s job not ready: no frame buffers\n",
			ctx->name);
		वापस 0;
	पूर्ण

	अगर (!v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx)) अणु
		dev_dbg(dev, "%s job not ready: no stream buffers\n",
			ctx->name);
		वापस 0;
	पूर्ण

	अगर (ctx->पातing) अणु
		dev_dbg(dev, "%s job not ready: aborting\n", ctx->name);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* mem-to-mem ops */
अटल स्थिर काष्ठा v4l2_m2m_ops hva_m2m_ops = अणु
	.device_run	= hva_device_run,
	.job_पात	= hva_job_पात,
	.job_पढ़ोy	= hva_job_पढ़ोy,
पूर्ण;

/*
 * VB2 queue operations
 */

अटल पूर्णांक hva_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा hva_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा device *dev = ctx_to_dev(ctx);
	अचिन्हित पूर्णांक size;

	dev_dbg(dev, "%s %s queue setup: num_buffers %d\n", ctx->name,
		to_type_str(vq->type), *num_buffers);

	size = vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT ?
		ctx->frameinfo.size : ctx->max_stream_size;

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	/* only one plane supported */
	*num_planes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक hva_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा hva_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		काष्ठा hva_frame *frame = to_hva_frame(vbuf);

		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			dev_dbg(dev,
				"%s frame[%d] prepare: %d field not supported\n",
				ctx->name, vb->index, vbuf->field);
			वापस -EINVAL;
		पूर्ण

		अगर (!frame->prepared) अणु
			/* get memory addresses */
			frame->vaddr = vb2_plane_vaddr(&vbuf->vb2_buf, 0);
			frame->paddr = vb2_dma_contig_plane_dma_addr(
					&vbuf->vb2_buf, 0);
			frame->info = ctx->frameinfo;
			frame->prepared = true;

			dev_dbg(dev,
				"%s frame[%d] prepared; virt=%p, phy=%pad\n",
				ctx->name, vb->index,
				frame->vaddr, &frame->paddr);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा hva_stream *stream = to_hva_stream(vbuf);

		अगर (!stream->prepared) अणु
			/* get memory addresses */
			stream->vaddr = vb2_plane_vaddr(&vbuf->vb2_buf, 0);
			stream->paddr = vb2_dma_contig_plane_dma_addr(
					&vbuf->vb2_buf, 0);
			stream->size = vb2_plane_size(&vbuf->vb2_buf, 0);
			stream->prepared = true;

			dev_dbg(dev,
				"%s stream[%d] prepared; virt=%p, phy=%pad\n",
				ctx->name, vb->index,
				stream->vaddr, &stream->paddr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hva_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा hva_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	अगर (ctx->fh.m2m_ctx)
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक hबहु_शुरू_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा hva_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा vb2_v4l2_buffer *vbuf;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	bool found = false;

	dev_dbg(dev, "%s %s start streaming\n", ctx->name,
		to_type_str(vq->type));

	/* खोलो encoder when both start_streaming have been called */
	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		अगर (!vb2_start_streaming_called(&ctx->fh.m2m_ctx->cap_q_ctx.q))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!vb2_start_streaming_called(&ctx->fh.m2m_ctx->out_q_ctx.q))
			वापस 0;
	पूर्ण

	/* store the instance context in the instances array */
	क्रम (i = 0; i < HVA_MAX_INSTANCES; i++) अणु
		अगर (!hva->instances[i]) अणु
			hva->instances[i] = ctx;
			/* save the context identअगरier in the context */
			ctx->id = i;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		dev_err(dev, "%s maximum instances reached\n", ctx->name);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	hva->nb_of_instances++;

	अगर (!ctx->enc) अणु
		ret = hva_खोलो_encoder(ctx,
				       ctx->streaminfo.streamक्रमmat,
				       ctx->frameinfo.pixelक्रमmat,
				       &ctx->enc);
		अगर (ret < 0)
			जाओ err_ctx;
	पूर्ण

	वापस 0;

err_ctx:
	hva->instances[ctx->id] = शून्य;
	hva->nb_of_instances--;
err:
	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		/* वापस of all pending buffers to vb2 (in queued state) */
		जबतक ((vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_QUEUED);
	पूर्ण अन्यथा अणु
		/* वापस of all pending buffers to vb2 (in queued state) */
		जबतक ((vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_QUEUED);
	पूर्ण

	ctx->sys_errors++;

	वापस ret;
पूर्ण

अटल व्योम hva_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा hva_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);
	काष्ठा device *dev = ctx_to_dev(ctx);
	स्थिर काष्ठा hva_enc *enc = ctx->enc;
	काष्ठा vb2_v4l2_buffer *vbuf;

	dev_dbg(dev, "%s %s stop streaming\n", ctx->name,
		to_type_str(vq->type));

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		/* वापस of all pending buffers to vb2 (in error state) */
		ctx->frame_num = 0;
		जबतक ((vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		/* वापस of all pending buffers to vb2 (in error state) */
		ctx->stream_num = 0;
		जबतक ((vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
	पूर्ण

	अगर ((V4L2_TYPE_IS_OUTPUT(vq->type) &&
	     vb2_is_streaming(&ctx->fh.m2m_ctx->cap_q_ctx.q)) ||
	    (V4L2_TYPE_IS_CAPTURE(vq->type) &&
	     vb2_is_streaming(&ctx->fh.m2m_ctx->out_q_ctx.q))) अणु
		dev_dbg(dev, "%s %s out=%d cap=%d\n",
			ctx->name, to_type_str(vq->type),
			vb2_is_streaming(&ctx->fh.m2m_ctx->out_q_ctx.q),
			vb2_is_streaming(&ctx->fh.m2m_ctx->cap_q_ctx.q));
		वापस;
	पूर्ण

	/* बंद encoder when both stop_streaming have been called */
	अगर (enc) अणु
		dev_dbg(dev, "%s %s encoder closed\n", ctx->name, enc->name);
		enc->बंद(ctx);
		ctx->enc = शून्य;

		/* clear instance context in instances array */
		hva->instances[ctx->id] = शून्य;
		hva->nb_of_instances--;
	पूर्ण

	ctx->पातing = false;
पूर्ण

/* VB2 queue ops */
अटल स्थिर काष्ठा vb2_ops hva_qops = अणु
	.queue_setup		= hva_queue_setup,
	.buf_prepare		= hva_buf_prepare,
	.buf_queue		= hva_buf_queue,
	.start_streaming	= hबहु_शुरू_streaming,
	.stop_streaming		= hva_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/*
 * V4L2 file operations
 */

अटल पूर्णांक queue_init(काष्ठा hva_ctx *ctx, काष्ठा vb2_queue *vq)
अणु
	vq->io_modes = VB2_MMAP | VB2_DMABUF;
	vq->drv_priv = ctx;
	vq->ops = &hva_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	vq->lock = &ctx->hva_dev->lock;

	वापस vb2_queue_init(vq);
पूर्ण

अटल पूर्णांक hva_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा hva_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->buf_काष्ठा_size = माप(काष्ठा hva_frame);
	src_vq->min_buffers_needed = MIN_FRAMES;
	src_vq->dev = ctx->hva_dev->dev;

	ret = queue_init(ctx, src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा hva_stream);
	dst_vq->min_buffers_needed = MIN_STREAMS;
	dst_vq->dev = ctx->hva_dev->dev;

	वापस queue_init(ctx, dst_vq);
पूर्ण

अटल पूर्णांक hva_खोलो(काष्ठा file *file)
अणु
	काष्ठा hva_dev *hva = video_drvdata(file);
	काष्ठा device *dev = hva_to_dev(hva);
	काष्ठा hva_ctx *ctx;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ctx->hva_dev = hva;

	INIT_WORK(&ctx->run_work, hva_run_work);
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ret = hva_ctrls_setup(ctx);
	अगर (ret) अणु
		dev_err(dev, "%s [x:x] failed to setup controls\n",
			HVA_PREFIX);
		ctx->sys_errors++;
		जाओ err_fh;
	पूर्ण
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;

	mutex_init(&ctx->lock);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(hva->m2m_dev, ctx,
					    &hva_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		dev_err(dev, "%s failed to initialize m2m context (%d)\n",
			HVA_PREFIX, ret);
		ctx->sys_errors++;
		जाओ err_ctrls;
	पूर्ण

	/* set the instance name */
	mutex_lock(&hva->lock);
	hva->instance_id++;
	snम_लिखो(ctx->name, माप(ctx->name), "[%3d:----]",
		 hva->instance_id);
	mutex_unlock(&hva->lock);

	/* शेष parameters क्रम frame and stream */
	set_शेष_params(ctx);

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_ctx_create(ctx);
#पूर्ण_अगर

	dev_info(dev, "%s encoder instance created\n", ctx->name);

	वापस 0;

err_ctrls:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
err_fh:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hva_release(काष्ठा file *file)
अणु
	काष्ठा hva_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा hva_dev *hva = ctx_to_hdev(ctx);
	काष्ठा device *dev = ctx_to_dev(ctx);
	स्थिर काष्ठा hva_enc *enc = ctx->enc;

	अगर (enc) अणु
		dev_dbg(dev, "%s %s encoder closed\n", ctx->name, enc->name);
		enc->बंद(ctx);
		ctx->enc = शून्य;

		/* clear instance context in instances array */
		hva->instances[ctx->id] = शून्य;
		hva->nb_of_instances--;
	पूर्ण

	/* trace a summary of instance beक्रमe closing (debug purpose) */
	hva_dbg_summary(ctx);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_ctx_हटाओ(ctx);
#पूर्ण_अगर

	dev_info(dev, "%s encoder instance released\n", ctx->name);

	kमुक्त(ctx);

	वापस 0;
पूर्ण

/* V4L2 file ops */
अटल स्थिर काष्ठा v4l2_file_operations hva_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= hva_खोलो,
	.release		= hva_release,
	.unlocked_ioctl		= video_ioctl2,
	.mmap			= v4l2_m2m_fop_mmap,
	.poll			= v4l2_m2m_fop_poll,
पूर्ण;

/*
 * Platक्रमm device operations
 */

अटल पूर्णांक hva_रेजिस्टर_device(काष्ठा hva_dev *hva)
अणु
	पूर्णांक ret;
	काष्ठा video_device *vdev;
	काष्ठा device *dev;

	अगर (!hva)
		वापस -ENODEV;
	dev = hva_to_dev(hva);

	hva->m2m_dev = v4l2_m2m_init(&hva_m2m_ops);
	अगर (IS_ERR(hva->m2m_dev)) अणु
		dev_err(dev, "%s failed to initialize v4l2-m2m device\n",
			HVA_PREFIX);
		ret = PTR_ERR(hva->m2m_dev);
		जाओ err;
	पूर्ण

	vdev = video_device_alloc();
	अगर (!vdev) अणु
		dev_err(dev, "%s failed to allocate video device\n",
			HVA_PREFIX);
		ret = -ENOMEM;
		जाओ err_m2m_release;
	पूर्ण

	vdev->fops = &hva_fops;
	vdev->ioctl_ops = &hva_ioctl_ops;
	vdev->release = video_device_release;
	vdev->lock = &hva->lock;
	vdev->vfl_dir = VFL_सूची_M2M;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;
	vdev->v4l2_dev = &hva->v4l2_dev;
	snम_लिखो(vdev->name, माप(vdev->name), "%s%lx", HVA_NAME,
		 hva->ip_version);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(dev, "%s failed to register video device\n",
			HVA_PREFIX);
		जाओ err_vdev_release;
	पूर्ण

	hva->vdev = vdev;
	video_set_drvdata(vdev, hva);
	वापस 0;

err_vdev_release:
	video_device_release(vdev);
err_m2m_release:
	v4l2_m2m_release(hva->m2m_dev);
err:
	वापस ret;
पूर्ण

अटल व्योम hva_unरेजिस्टर_device(काष्ठा hva_dev *hva)
अणु
	अगर (!hva)
		वापस;

	अगर (hva->m2m_dev)
		v4l2_m2m_release(hva->m2m_dev);

	video_unरेजिस्टर_device(hva->vdev);
पूर्ण

अटल पूर्णांक hva_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hva_dev *hva;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	hva = devm_kzalloc(dev, माप(*hva), GFP_KERNEL);
	अगर (!hva) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	hva->dev = dev;
	hva->pdev = pdev;
	platक्रमm_set_drvdata(pdev, hva);

	mutex_init(&hva->lock);

	/* probe hardware */
	ret = hva_hw_probe(pdev, hva);
	अगर (ret)
		जाओ err;

	/* रेजिस्टर all available encoders */
	रेजिस्टर_encoders(hva);

	/* रेजिस्टर all supported क्रमmats */
	रेजिस्टर_क्रमmats(hva);

	/* रेजिस्टर on V4L2 */
	ret = v4l2_device_रेजिस्टर(dev, &hva->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev, "%s %s failed to register V4L2 device\n",
			HVA_PREFIX, HVA_NAME);
		जाओ err_hw;
	पूर्ण

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_create(hva);
#पूर्ण_अगर

	hva->work_queue = create_workqueue(HVA_NAME);
	अगर (!hva->work_queue) अणु
		dev_err(dev, "%s %s failed to allocate work queue\n",
			HVA_PREFIX, HVA_NAME);
		ret = -ENOMEM;
		जाओ err_v4l2;
	पूर्ण

	/* रेजिस्टर device */
	ret = hva_रेजिस्टर_device(hva);
	अगर (ret)
		जाओ err_work_queue;

	dev_info(dev, "%s %s registered as /dev/video%d\n", HVA_PREFIX,
		 HVA_NAME, hva->vdev->num);

	वापस 0;

err_work_queue:
	destroy_workqueue(hva->work_queue);
err_v4l2:
#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_हटाओ(hva);
#पूर्ण_अगर
	v4l2_device_unरेजिस्टर(&hva->v4l2_dev);
err_hw:
	hva_hw_हटाओ(hva);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक hva_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hva_dev *hva = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = hva_to_dev(hva);

	hva_unरेजिस्टर_device(hva);

	destroy_workqueue(hva->work_queue);

	hva_hw_हटाओ(hva);

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_हटाओ(hva);
#पूर्ण_अगर

	v4l2_device_unरेजिस्टर(&hva->v4l2_dev);

	dev_info(dev, "%s %s removed\n", HVA_PREFIX, pdev->name);

	वापस 0;
पूर्ण

/* PM ops */
अटल स्थिर काष्ठा dev_pm_ops hva_pm_ops = अणु
	.runसमय_suspend	= hva_hw_runसमय_suspend,
	.runसमय_resume		= hva_hw_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hva_match_types[] = अणु
	अणु
	 .compatible = "st,st-hva",
	पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, hva_match_types);

अटल काष्ठा platक्रमm_driver hva_driver = अणु
	.probe  = hva_probe,
	.हटाओ = hva_हटाओ,
	.driver = अणु
		.name		= HVA_NAME,
		.of_match_table	= hva_match_types,
		.pm		= &hva_pm_ops,
		पूर्ण,
पूर्ण;

module_platक्रमm_driver(hva_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_DESCRIPTION("STMicroelectronics HVA video encoder V4L2 driver");
