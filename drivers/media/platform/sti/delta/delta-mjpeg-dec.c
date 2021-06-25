<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2013
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/slab.h>

#समावेश "delta.h"
#समावेश "delta-ipc.h"
#समावेश "delta-mjpeg.h"
#समावेश "delta-mjpeg-fw.h"

#घोषणा DELTA_MJPEG_MAX_RESO DELTA_MAX_RESO

काष्ठा delta_mjpeg_ctx अणु
	/* jpeg header */
	काष्ठा mjpeg_header header_काष्ठा;
	काष्ठा mjpeg_header *header;

	/* ipc */
	व्योम *ipc_hdl;
	काष्ठा delta_buf *ipc_buf;

	/* decoded output frame */
	काष्ठा delta_frame *out_frame;

	अचिन्हित अक्षर str[3000];
पूर्ण;

#घोषणा to_ctx(ctx) ((काष्ठा delta_mjpeg_ctx *)(ctx)->priv)

अटल अक्षर *ipc_खोलो_param_str(काष्ठा jpeg_video_decode_init_params_t *p,
				अक्षर *str, अचिन्हित पूर्णांक len)
अणु
	अक्षर *b = str;

	अगर (!p)
		वापस "";

	b += snम_लिखो(b, len,
		      "jpeg_video_decode_init_params_t\n"
		      "circular_buffer_begin_addr_p 0x%x\n"
		      "circular_buffer_end_addr_p   0x%x\n",
		      p->circular_buffer_begin_addr_p,
		      p->circular_buffer_end_addr_p);

	वापस str;
पूर्ण

अटल अक्षर *ipc_decode_param_str(काष्ठा jpeg_decode_params_t *p,
				  अक्षर *str, अचिन्हित पूर्णांक len)
अणु
	अक्षर *b = str;

	अगर (!p)
		वापस "";

	b += snम_लिखो(b, len,
		      "jpeg_decode_params_t\n"
		      "picture_start_addr_p                  0x%x\n"
		      "picture_end_addr_p                    0x%x\n"
		      "decoding_mode                        %d\n"
		      "display_buffer_addr.display_decimated_luma_p   0x%x\n"
		      "display_buffer_addr.display_decimated_chroma_p 0x%x\n"
		      "main_aux_enable                       %d\n"
		      "additional_flags                     0x%x\n"
		      "field_flag                           %x\n"
		      "is_jpeg_image                        %x\n",
		      p->picture_start_addr_p,
		      p->picture_end_addr_p,
		      p->decoding_mode,
		      p->display_buffer_addr.display_decimated_luma_p,
		      p->display_buffer_addr.display_decimated_chroma_p,
		      p->मुख्य_aux_enable, p->additional_flags,
		      p->field_flag,
		      p->is_jpeg_image);

	वापस str;
पूर्ण

अटल अंतरभूत bool is_stream_error(क्रमागत jpeg_decoding_error_t err)
अणु
	चयन (err) अणु
	हाल JPEG_DECODER_UNDEFINED_HUFF_TABLE:
	हाल JPEG_DECODER_BAD_RESTART_MARKER:
	हाल JPEG_DECODER_BAD_SOS_SPECTRAL:
	हाल JPEG_DECODER_BAD_SOS_SUCCESSIVE:
	हाल JPEG_DECODER_BAD_HEADER_LENGTH:
	हाल JPEG_DECODER_BAD_COUNT_VALUE:
	हाल JPEG_DECODER_BAD_DHT_MARKER:
	हाल JPEG_DECODER_BAD_INDEX_VALUE:
	हाल JPEG_DECODER_BAD_NUMBER_HUFFMAN_TABLES:
	हाल JPEG_DECODER_BAD_QUANT_TABLE_LENGTH:
	हाल JPEG_DECODER_BAD_NUMBER_QUANT_TABLES:
	हाल JPEG_DECODER_BAD_COMPONENT_COUNT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *err_str(क्रमागत jpeg_decoding_error_t err)
अणु
	चयन (err) अणु
	हाल JPEG_DECODER_NO_ERROR:
		वापस "JPEG_DECODER_NO_ERROR";
	हाल JPEG_DECODER_UNDEFINED_HUFF_TABLE:
		वापस "JPEG_DECODER_UNDEFINED_HUFF_TABLE";
	हाल JPEG_DECODER_UNSUPPORTED_MARKER:
		वापस "JPEG_DECODER_UNSUPPORTED_MARKER";
	हाल JPEG_DECODER_UNABLE_ALLOCATE_MEMORY:
		वापस "JPEG_DECODER_UNABLE_ALLOCATE_MEMORY";
	हाल JPEG_DECODER_NON_SUPPORTED_SAMP_FACTORS:
		वापस "JPEG_DECODER_NON_SUPPORTED_SAMP_FACTORS";
	हाल JPEG_DECODER_BAD_PARAMETER:
		वापस "JPEG_DECODER_BAD_PARAMETER";
	हाल JPEG_DECODER_DECODE_ERROR:
		वापस "JPEG_DECODER_DECODE_ERROR";
	हाल JPEG_DECODER_BAD_RESTART_MARKER:
		वापस "JPEG_DECODER_BAD_RESTART_MARKER";
	हाल JPEG_DECODER_UNSUPPORTED_COLORSPACE:
		वापस "JPEG_DECODER_UNSUPPORTED_COLORSPACE";
	हाल JPEG_DECODER_BAD_SOS_SPECTRAL:
		वापस "JPEG_DECODER_BAD_SOS_SPECTRAL";
	हाल JPEG_DECODER_BAD_SOS_SUCCESSIVE:
		वापस "JPEG_DECODER_BAD_SOS_SUCCESSIVE";
	हाल JPEG_DECODER_BAD_HEADER_LENGTH:
		वापस "JPEG_DECODER_BAD_HEADER_LENGTH";
	हाल JPEG_DECODER_BAD_COUNT_VALUE:
		वापस "JPEG_DECODER_BAD_COUNT_VALUE";
	हाल JPEG_DECODER_BAD_DHT_MARKER:
		वापस "JPEG_DECODER_BAD_DHT_MARKER";
	हाल JPEG_DECODER_BAD_INDEX_VALUE:
		वापस "JPEG_DECODER_BAD_INDEX_VALUE";
	हाल JPEG_DECODER_BAD_NUMBER_HUFFMAN_TABLES:
		वापस "JPEG_DECODER_BAD_NUMBER_HUFFMAN_TABLES";
	हाल JPEG_DECODER_BAD_QUANT_TABLE_LENGTH:
		वापस "JPEG_DECODER_BAD_QUANT_TABLE_LENGTH";
	हाल JPEG_DECODER_BAD_NUMBER_QUANT_TABLES:
		वापस "JPEG_DECODER_BAD_NUMBER_QUANT_TABLES";
	हाल JPEG_DECODER_BAD_COMPONENT_COUNT:
		वापस "JPEG_DECODER_BAD_COMPONENT_COUNT";
	हाल JPEG_DECODER_DIVIDE_BY_ZERO_ERROR:
		वापस "JPEG_DECODER_DIVIDE_BY_ZERO_ERROR";
	हाल JPEG_DECODER_NOT_JPG_IMAGE:
		वापस "JPEG_DECODER_NOT_JPG_IMAGE";
	हाल JPEG_DECODER_UNSUPPORTED_ROTATION_ANGLE:
		वापस "JPEG_DECODER_UNSUPPORTED_ROTATION_ANGLE";
	हाल JPEG_DECODER_UNSUPPORTED_SCALING:
		वापस "JPEG_DECODER_UNSUPPORTED_SCALING";
	हाल JPEG_DECODER_INSUFFICIENT_OUTPUTBUFFER_SIZE:
		वापस "JPEG_DECODER_INSUFFICIENT_OUTPUTBUFFER_SIZE";
	हाल JPEG_DECODER_BAD_HWCFG_GP_VERSION_VALUE:
		वापस "JPEG_DECODER_BAD_HWCFG_GP_VERSION_VALUE";
	हाल JPEG_DECODER_BAD_VALUE_FROM_RED:
		वापस "JPEG_DECODER_BAD_VALUE_FROM_RED";
	हाल JPEG_DECODER_BAD_SUBREGION_PARAMETERS:
		वापस "JPEG_DECODER_BAD_SUBREGION_PARAMETERS";
	हाल JPEG_DECODER_PROGRESSIVE_DECODE_NOT_SUPPORTED:
		वापस "JPEG_DECODER_PROGRESSIVE_DECODE_NOT_SUPPORTED";
	हाल JPEG_DECODER_ERROR_TASK_TIMEOUT:
		वापस "JPEG_DECODER_ERROR_TASK_TIMEOUT";
	हाल JPEG_DECODER_ERROR_FEATURE_NOT_SUPPORTED:
		वापस "JPEG_DECODER_ERROR_FEATURE_NOT_SUPPORTED";
	शेष:
		वापस "!unknown MJPEG error!";
	पूर्ण
पूर्ण

अटल bool delta_mjpeg_check_status(काष्ठा delta_ctx *pctx,
				     काष्ठा jpeg_decode_वापस_params_t *status)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	bool dump = false;

	अगर (status->error_code == JPEG_DECODER_NO_ERROR)
		जाओ out;

	अगर (is_stream_error(status->error_code)) अणु
		dev_warn_ratelimited(delta->dev,
				     "%s  firmware: stream error @ frame %d (%s)\n",
				     pctx->name, pctx->decoded_frames,
				     err_str(status->error_code));
		pctx->stream_errors++;
	पूर्ण अन्यथा अणु
		dev_warn_ratelimited(delta->dev,
				     "%s  firmware: decode error @ frame %d (%s)\n",
				     pctx->name, pctx->decoded_frames,
				     err_str(status->error_code));
		pctx->decode_errors++;
		dump = true;
	पूर्ण

out:
	dev_dbg(delta->dev,
		"%s  firmware: decoding time(us)=%d\n", pctx->name,
		status->decode_समय_in_us);

	वापस dump;
पूर्ण

अटल पूर्णांक delta_mjpeg_ipc_खोलो(काष्ठा delta_ctx *pctx)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा delta_mjpeg_ctx *ctx = to_ctx(pctx);
	पूर्णांक ret = 0;
	काष्ठा jpeg_video_decode_init_params_t params_काष्ठा;
	काष्ठा jpeg_video_decode_init_params_t *params = &params_काष्ठा;
	काष्ठा delta_buf *ipc_buf;
	u32 ipc_buf_size;
	काष्ठा delta_ipc_param ipc_param;
	व्योम *hdl;

	स_रखो(params, 0, माप(*params));
	params->circular_buffer_begin_addr_p = 0x00000000;
	params->circular_buffer_end_addr_p = 0xffffffff;

	dev_vdbg(delta->dev,
		 "%s  %s\n", pctx->name,
		 ipc_खोलो_param_str(params, ctx->str, माप(ctx->str)));

	ipc_param.size = माप(*params);
	ipc_param.data = params;
	ipc_buf_size = माप(काष्ठा jpeg_decode_params_t) +
	    माप(काष्ठा jpeg_decode_वापस_params_t);
	ret = delta_ipc_खोलो(pctx, "JPEG_DECODER_HW0", &ipc_param,
			     ipc_buf_size, &ipc_buf, &hdl);
	अगर (ret) अणु
		dev_err(delta->dev,
			"%s  dumping command %s\n", pctx->name,
			ipc_खोलो_param_str(params, ctx->str, माप(ctx->str)));
		वापस ret;
	पूर्ण

	ctx->ipc_buf = ipc_buf;
	ctx->ipc_hdl = hdl;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_mjpeg_ipc_decode(काष्ठा delta_ctx *pctx, काष्ठा delta_au *au)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा delta_mjpeg_ctx *ctx = to_ctx(pctx);
	पूर्णांक ret = 0;
	काष्ठा jpeg_decode_params_t *params = ctx->ipc_buf->vaddr;
	काष्ठा jpeg_decode_वापस_params_t *status =
	    ctx->ipc_buf->vaddr + माप(*params);
	काष्ठा delta_frame *frame;
	काष्ठा delta_ipc_param ipc_param, ipc_status;

	ret = delta_get_मुक्त_frame(pctx, &frame);
	अगर (ret)
		वापस ret;

	स_रखो(params, 0, माप(*params));

	params->picture_start_addr_p = (u32)(au->paddr);
	params->picture_end_addr_p = (u32)(au->paddr + au->size - 1);

	/*
	 * !WARNING!
	 * the NV12 decoded frame is only available
	 * on decimated output when enabling flag
	 * "JPEG_ADDITIONAL_FLAG_420MB"...
	 * the non decimated output gives YUV422SP
	 */
	params->मुख्य_aux_enable = JPEG_DISP_AUX_EN;
	params->additional_flags = JPEG_ADDITIONAL_FLAG_420MB;
	params->horizontal_decimation_factor = JPEG_HDEC_1;
	params->vertical_decimation_factor = JPEG_VDEC_1;
	params->decoding_mode = JPEG_NORMAL_DECODE;

	params->display_buffer_addr.काष्ठा_size =
	    माप(काष्ठा jpeg_display_buffer_address_t);
	params->display_buffer_addr.display_decimated_luma_p =
	    (u32)frame->paddr;
	params->display_buffer_addr.display_decimated_chroma_p =
	    (u32)(frame->paddr
		  + frame->info.aligned_width * frame->info.aligned_height);

	dev_vdbg(delta->dev,
		 "%s  %s\n", pctx->name,
		 ipc_decode_param_str(params, ctx->str, माप(ctx->str)));

	/* status */
	स_रखो(status, 0, माप(*status));
	status->error_code = JPEG_DECODER_NO_ERROR;

	ipc_param.size = माप(*params);
	ipc_param.data = params;
	ipc_status.size = माप(*status);
	ipc_status.data = status;
	ret = delta_ipc_decode(ctx->ipc_hdl, &ipc_param, &ipc_status);
	अगर (ret) अणु
		dev_err(delta->dev,
			"%s  dumping command %s\n", pctx->name,
			ipc_decode_param_str(params, ctx->str,
					     माप(ctx->str)));
		वापस ret;
	पूर्ण

	pctx->decoded_frames++;

	/* check firmware decoding status */
	अगर (delta_mjpeg_check_status(pctx, status)) अणु
		dev_err(delta->dev,
			"%s  dumping command %s\n", pctx->name,
			ipc_decode_param_str(params, ctx->str,
					     माप(ctx->str)));
	पूर्ण

	frame->field = V4L2_FIELD_NONE;
	frame->flags = V4L2_BUF_FLAG_KEYFRAME;
	frame->state |= DELTA_FRAME_DEC;

	ctx->out_frame = frame;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_mjpeg_खोलो(काष्ठा delta_ctx *pctx)
अणु
	काष्ठा delta_mjpeg_ctx *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	pctx->priv = ctx;

	वापस 0;
पूर्ण

अटल पूर्णांक delta_mjpeg_बंद(काष्ठा delta_ctx *pctx)
अणु
	काष्ठा delta_mjpeg_ctx *ctx = to_ctx(pctx);

	अगर (ctx->ipc_hdl) अणु
		delta_ipc_बंद(ctx->ipc_hdl);
		ctx->ipc_hdl = शून्य;
	पूर्ण

	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक delta_mjpeg_get_streaminfo(काष्ठा delta_ctx *pctx,
				      काष्ठा delta_streaminfo *streaminfo)
अणु
	काष्ठा delta_mjpeg_ctx *ctx = to_ctx(pctx);

	अगर (!ctx->header)
		जाओ nodata;

	streaminfo->streamक्रमmat = V4L2_PIX_FMT_MJPEG;
	streaminfo->width = ctx->header->frame_width;
	streaminfo->height = ctx->header->frame_height;

	/* progressive stream */
	streaminfo->field = V4L2_FIELD_NONE;

	streaminfo->dpb = 1;

	वापस 0;

nodata:
	वापस -ENODATA;
पूर्ण

अटल पूर्णांक delta_mjpeg_decode(काष्ठा delta_ctx *pctx, काष्ठा delta_au *pau)
अणु
	काष्ठा delta_dev *delta = pctx->dev;
	काष्ठा delta_mjpeg_ctx *ctx = to_ctx(pctx);
	पूर्णांक ret;
	काष्ठा delta_au au = *pau;
	अचिन्हित पूर्णांक data_offset = 0;
	काष्ठा mjpeg_header *header = &ctx->header_काष्ठा;

	अगर (!ctx->header) अणु
		ret = delta_mjpeg_पढ़ो_header(pctx, au.vaddr, au.size,
					      header, &data_offset);
		अगर (ret) अणु
			pctx->stream_errors++;
			जाओ err;
		पूर्ण
		अगर (header->frame_width * header->frame_height >
		    DELTA_MJPEG_MAX_RESO) अणु
			dev_err(delta->dev,
				"%s  stream resolution too large: %dx%d > %d pixels budget\n",
				pctx->name,
				header->frame_width,
				header->frame_height, DELTA_MJPEG_MAX_RESO);
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		ctx->header = header;
		जाओ out;
	पूर्ण

	अगर (!ctx->ipc_hdl) अणु
		ret = delta_mjpeg_ipc_खोलो(pctx);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = delta_mjpeg_पढ़ो_header(pctx, au.vaddr, au.size,
				      ctx->header, &data_offset);
	अगर (ret) अणु
		pctx->stream_errors++;
		जाओ err;
	पूर्ण

	au.paddr += data_offset;
	au.vaddr += data_offset;

	ret = delta_mjpeg_ipc_decode(pctx, &au);
	अगर (ret)
		जाओ err;

out:
	वापस 0;

err:
	वापस ret;
पूर्ण

अटल पूर्णांक delta_mjpeg_get_frame(काष्ठा delta_ctx *pctx,
				 काष्ठा delta_frame **frame)
अणु
	काष्ठा delta_mjpeg_ctx *ctx = to_ctx(pctx);

	अगर (!ctx->out_frame)
		वापस -ENODATA;

	*frame = ctx->out_frame;

	ctx->out_frame = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा delta_dec mjpegdec = अणु
	.name = "MJPEG",
	.streamक्रमmat = V4L2_PIX_FMT_MJPEG,
	.pixelक्रमmat = V4L2_PIX_FMT_NV12,
	.खोलो = delta_mjpeg_खोलो,
	.बंद = delta_mjpeg_बंद,
	.get_streaminfo = delta_mjpeg_get_streaminfo,
	.get_frameinfo = delta_get_frameinfo_शेष,
	.decode = delta_mjpeg_decode,
	.get_frame = delta_mjpeg_get_frame,
	.recycle = delta_recycle_शेष,
पूर्ण;
