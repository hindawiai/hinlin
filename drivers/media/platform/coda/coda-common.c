<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Coda multi-standard codec IP
 *
 * Copyright (C) 2012 Vista Silicon S.L.
 *    Javier Martin, <javier.martin@vista-silicon.com>
 *    Xavier Duret
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gcd.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/of.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/reset.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "coda.h"
#समावेश "imx-vdoa.h"

#घोषणा CODA_NAME		"coda"

#घोषणा CODADX6_MAX_INSTANCES	4
#घोषणा CODA_MAX_FORMATS	4

#घोषणा CODA_ISRAM_SIZE	(2048 * 2)

#घोषणा MIN_W 48
#घोषणा MIN_H 16

#घोषणा S_ALIGN		1 /* multiple of 2 */
#घोषणा W_ALIGN		1 /* multiple of 2 */
#घोषणा H_ALIGN		1 /* multiple of 2 */

#घोषणा fh_to_ctx(__fh)	container_of(__fh, काष्ठा coda_ctx, fh)

पूर्णांक coda_debug;
module_param(coda_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(coda_debug, "Debug level (0-2)");

अटल पूर्णांक disable_tiling;
module_param(disable_tiling, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_tiling, "Disable tiled frame buffers");

अटल पूर्णांक disable_vकरोa;
module_param(disable_vकरोa, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_vकरोa, "Disable Video Data Order Adapter tiled to raster-scan conversion");

अटल पूर्णांक enable_bwb = 0;
module_param(enable_bwb, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_bwb, "Enable BWB unit for decoding, may crash on certain streams");

व्योम coda_ग_लिखो(काष्ठा coda_dev *dev, u32 data, u32 reg)
अणु
	v4l2_dbg(3, coda_debug, &dev->v4l2_dev,
		 "%s: data=0x%x, reg=0x%x\n", __func__, data, reg);
	ग_लिखोl(data, dev->regs_base + reg);
पूर्ण

अचिन्हित पूर्णांक coda_पढ़ो(काष्ठा coda_dev *dev, u32 reg)
अणु
	u32 data;

	data = पढ़ोl(dev->regs_base + reg);
	v4l2_dbg(3, coda_debug, &dev->v4l2_dev,
		 "%s: data=0x%x, reg=0x%x\n", __func__, data, reg);
	वापस data;
पूर्ण

व्योम coda_ग_लिखो_base(काष्ठा coda_ctx *ctx, काष्ठा coda_q_data *q_data,
		     काष्ठा vb2_v4l2_buffer *buf, अचिन्हित पूर्णांक reg_y)
अणु
	u32 base_y = vb2_dma_contig_plane_dma_addr(&buf->vb2_buf, 0);
	u32 base_cb, base_cr;

	चयन (q_data->fourcc) अणु
	हाल V4L2_PIX_FMT_YUYV:
		/* Fallthrough: IN -H264-> CODA -NV12 MB-> VDOA -YUYV-> OUT */
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_YUV420:
	शेष:
		base_cb = base_y + q_data->bytesperline * q_data->height;
		base_cr = base_cb + q_data->bytesperline * q_data->height / 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YVU420:
		/* Switch Cb and Cr क्रम YVU420 क्रमmat */
		base_cr = base_y + q_data->bytesperline * q_data->height;
		base_cb = base_cr + q_data->bytesperline * q_data->height / 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		base_cb = base_y + q_data->bytesperline * q_data->height;
		base_cr = base_cb + q_data->bytesperline * q_data->height / 2;
	पूर्ण

	coda_ग_लिखो(ctx->dev, base_y, reg_y);
	coda_ग_लिखो(ctx->dev, base_cb, reg_y + 4);
	coda_ग_लिखो(ctx->dev, base_cr, reg_y + 8);
पूर्ण

#घोषणा CODA_CODEC(mode, src_fourcc, dst_fourcc, max_w, max_h) \
	अणु mode, src_fourcc, dst_fourcc, max_w, max_h पूर्ण

/*
 * Arrays of codecs supported by each given version of Coda:
 *  i.MX27 -> codadx6
 *  i.MX51 -> codahx4
 *  i.MX53 -> coda7
 *  i.MX6  -> coda960
 * Use V4L2_PIX_FMT_YUV420 as placeholder क्रम all supported YUV 4:2:0 variants
 */
अटल स्थिर काष्ठा coda_codec codadx6_codecs[] = अणु
	CODA_CODEC(CODADX6_MODE_ENCODE_H264, V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_H264,  720, 576),
	CODA_CODEC(CODADX6_MODE_ENCODE_MP4,  V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_MPEG4, 720, 576),
पूर्ण;

अटल स्थिर काष्ठा coda_codec codahx4_codecs[] = अणु
	CODA_CODEC(CODA7_MODE_ENCODE_H264, V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_H264,   720, 576),
	CODA_CODEC(CODA7_MODE_DECODE_H264, V4L2_PIX_FMT_H264,   V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA7_MODE_DECODE_MP2,  V4L2_PIX_FMT_MPEG2,  V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA7_MODE_DECODE_MP4,  V4L2_PIX_FMT_MPEG4,  V4L2_PIX_FMT_YUV420, 1280, 720),
पूर्ण;

अटल स्थिर काष्ठा coda_codec coda7_codecs[] = अणु
	CODA_CODEC(CODA7_MODE_ENCODE_H264, V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_H264,   1280, 720),
	CODA_CODEC(CODA7_MODE_ENCODE_MP4,  V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_MPEG4,  1280, 720),
	CODA_CODEC(CODA7_MODE_ENCODE_MJPG, V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_JPEG,   8192, 8192),
	CODA_CODEC(CODA7_MODE_DECODE_H264, V4L2_PIX_FMT_H264,   V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA7_MODE_DECODE_MP2,  V4L2_PIX_FMT_MPEG2,  V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA7_MODE_DECODE_MP4,  V4L2_PIX_FMT_MPEG4,  V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA7_MODE_DECODE_MJPG, V4L2_PIX_FMT_JPEG,   V4L2_PIX_FMT_YUV420, 8192, 8192),
पूर्ण;

अटल स्थिर काष्ठा coda_codec coda9_codecs[] = अणु
	CODA_CODEC(CODA9_MODE_ENCODE_H264, V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_H264,   1920, 1088),
	CODA_CODEC(CODA9_MODE_ENCODE_MP4,  V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_MPEG4,  1920, 1088),
	CODA_CODEC(CODA9_MODE_ENCODE_MJPG, V4L2_PIX_FMT_YUV420, V4L2_PIX_FMT_JPEG,   8192, 8192),
	CODA_CODEC(CODA9_MODE_DECODE_H264, V4L2_PIX_FMT_H264,   V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA9_MODE_DECODE_MP2,  V4L2_PIX_FMT_MPEG2,  V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA9_MODE_DECODE_MP4,  V4L2_PIX_FMT_MPEG4,  V4L2_PIX_FMT_YUV420, 1920, 1088),
	CODA_CODEC(CODA9_MODE_DECODE_MJPG, V4L2_PIX_FMT_JPEG,	V4L2_PIX_FMT_YUV420, 8192, 8192),
पूर्ण;

काष्ठा coda_video_device अणु
	स्थिर अक्षर *name;
	क्रमागत coda_inst_type type;
	स्थिर काष्ठा coda_context_ops *ops;
	bool direct;
	u32 src_क्रमmats[CODA_MAX_FORMATS];
	u32 dst_क्रमmats[CODA_MAX_FORMATS];
पूर्ण;

अटल स्थिर काष्ठा coda_video_device coda_bit_encoder = अणु
	.name = "coda-video-encoder",
	.type = CODA_INST_ENCODER,
	.ops = &coda_bit_encode_ops,
	.src_क्रमmats = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
	पूर्ण,
	.dst_क्रमmats = अणु
		V4L2_PIX_FMT_H264,
		V4L2_PIX_FMT_MPEG4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device coda_bit_jpeg_encoder = अणु
	.name = "coda-jpeg-encoder",
	.type = CODA_INST_ENCODER,
	.ops = &coda_bit_encode_ops,
	.src_क्रमmats = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
		V4L2_PIX_FMT_YUV422P,
	पूर्ण,
	.dst_क्रमmats = अणु
		V4L2_PIX_FMT_JPEG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device coda_bit_decoder = अणु
	.name = "coda-video-decoder",
	.type = CODA_INST_DECODER,
	.ops = &coda_bit_decode_ops,
	.src_क्रमmats = अणु
		V4L2_PIX_FMT_H264,
		V4L2_PIX_FMT_MPEG2,
		V4L2_PIX_FMT_MPEG4,
	पूर्ण,
	.dst_क्रमmats = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
		/*
		 * If V4L2_PIX_FMT_YUYV should be शेष,
		 * set_शेष_params() must be adjusted.
		 */
		V4L2_PIX_FMT_YUYV,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device coda_bit_jpeg_decoder = अणु
	.name = "coda-jpeg-decoder",
	.type = CODA_INST_DECODER,
	.ops = &coda_bit_decode_ops,
	.src_क्रमmats = अणु
		V4L2_PIX_FMT_JPEG,
	पूर्ण,
	.dst_क्रमmats = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
		V4L2_PIX_FMT_YUV422P,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device coda9_jpeg_encoder = अणु
	.name = "coda-jpeg-encoder",
	.type = CODA_INST_ENCODER,
	.ops = &coda9_jpeg_encode_ops,
	.direct = true,
	.src_क्रमmats = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
		V4L2_PIX_FMT_YUV422P,
	पूर्ण,
	.dst_क्रमmats = अणु
		V4L2_PIX_FMT_JPEG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device coda9_jpeg_decoder = अणु
	.name = "coda-jpeg-decoder",
	.type = CODA_INST_DECODER,
	.ops = &coda9_jpeg_decode_ops,
	.direct = true,
	.src_क्रमmats = अणु
		V4L2_PIX_FMT_JPEG,
	पूर्ण,
	.dst_क्रमmats = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
		V4L2_PIX_FMT_YUV422P,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device *codadx6_video_devices[] = अणु
	&coda_bit_encoder,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device *codahx4_video_devices[] = अणु
	&coda_bit_encoder,
	&coda_bit_decoder,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device *coda7_video_devices[] = अणु
	&coda_bit_jpeg_encoder,
	&coda_bit_jpeg_decoder,
	&coda_bit_encoder,
	&coda_bit_decoder,
पूर्ण;

अटल स्थिर काष्ठा coda_video_device *coda9_video_devices[] = अणु
	&coda9_jpeg_encoder,
	&coda9_jpeg_decoder,
	&coda_bit_encoder,
	&coda_bit_decoder,
पूर्ण;

/*
 * Normalize all supported YUV 4:2:0 क्रमmats to the value used in the codec
 * tables.
 */
अटल u32 coda_क्रमmat_normalize_yuv(u32 fourcc)
अणु
	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_YUYV:
		वापस V4L2_PIX_FMT_YUV420;
	शेष:
		वापस fourcc;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा coda_codec *coda_find_codec(काष्ठा coda_dev *dev,
						पूर्णांक src_fourcc, पूर्णांक dst_fourcc)
अणु
	स्थिर काष्ठा coda_codec *codecs = dev->devtype->codecs;
	पूर्णांक num_codecs = dev->devtype->num_codecs;
	पूर्णांक k;

	src_fourcc = coda_क्रमmat_normalize_yuv(src_fourcc);
	dst_fourcc = coda_क्रमmat_normalize_yuv(dst_fourcc);
	अगर (src_fourcc == dst_fourcc)
		वापस शून्य;

	क्रम (k = 0; k < num_codecs; k++) अणु
		अगर (codecs[k].src_fourcc == src_fourcc &&
		    codecs[k].dst_fourcc == dst_fourcc)
			अवरोध;
	पूर्ण

	अगर (k == num_codecs)
		वापस शून्य;

	वापस &codecs[k];
पूर्ण

अटल व्योम coda_get_max_dimensions(काष्ठा coda_dev *dev,
				    स्थिर काष्ठा coda_codec *codec,
				    पूर्णांक *max_w, पूर्णांक *max_h)
अणु
	स्थिर काष्ठा coda_codec *codecs = dev->devtype->codecs;
	पूर्णांक num_codecs = dev->devtype->num_codecs;
	अचिन्हित पूर्णांक w, h;
	पूर्णांक k;

	अगर (codec) अणु
		w = codec->max_w;
		h = codec->max_h;
	पूर्ण अन्यथा अणु
		क्रम (k = 0, w = 0, h = 0; k < num_codecs; k++) अणु
			w = max(w, codecs[k].max_w);
			h = max(h, codecs[k].max_h);
		पूर्ण
	पूर्ण

	अगर (max_w)
		*max_w = w;
	अगर (max_h)
		*max_h = h;
पूर्ण

अटल स्थिर काष्ठा coda_video_device *to_coda_video_device(काष्ठा video_device
							    *vdev)
अणु
	काष्ठा coda_dev *dev = video_get_drvdata(vdev);
	अचिन्हित पूर्णांक i = vdev - dev->vfd;

	अगर (i >= dev->devtype->num_vdevs)
		वापस शून्य;

	वापस dev->devtype->vdevs[i];
पूर्ण

स्थिर अक्षर *coda_product_name(पूर्णांक product)
अणु
	अटल अक्षर buf[9];

	चयन (product) अणु
	हाल CODA_DX6:
		वापस "CodaDx6";
	हाल CODA_HX4:
		वापस "CodaHx4";
	हाल CODA_7541:
		वापस "CODA7541";
	हाल CODA_960:
		वापस "CODA960";
	शेष:
		snम_लिखो(buf, माप(buf), "(0x%04x)", product);
		वापस buf;
	पूर्ण
पूर्ण

अटल काष्ठा vकरोa_data *coda_get_vकरोa_data(व्योम)
अणु
	काष्ठा device_node *vकरोa_node;
	काष्ठा platक्रमm_device *vकरोa_pdev;
	काष्ठा vकरोa_data *vकरोa_data = शून्य;

	vकरोa_node = of_find_compatible_node(शून्य, शून्य, "fsl,imx6q-vdoa");
	अगर (!vकरोa_node)
		वापस शून्य;

	vकरोa_pdev = of_find_device_by_node(vकरोa_node);
	अगर (!vकरोa_pdev)
		जाओ out;

	vकरोa_data = platक्रमm_get_drvdata(vकरोa_pdev);
	अगर (!vकरोa_data)
		vकरोa_data = ERR_PTR(-EPROBE_DEFER);

out:
	of_node_put(vकरोa_node);

	वापस vकरोa_data;
पूर्ण

/*
 * V4L2 ioctl() operations.
 */
अटल पूर्णांक coda_querycap(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);

	strscpy(cap->driver, CODA_NAME, माप(cap->driver));
	strscpy(cap->card, coda_product_name(ctx->dev->devtype->product),
		माप(cap->card));
	strscpy(cap->bus_info, "platform:" CODA_NAME, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल स्थिर u32 coda_क्रमmats_420[CODA_MAX_FORMATS] = अणु
		V4L2_PIX_FMT_NV12,
		V4L2_PIX_FMT_YUV420,
		V4L2_PIX_FMT_YVU420,
पूर्ण;

अटल पूर्णांक coda_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	स्थिर काष्ठा coda_video_device *cvd = to_coda_video_device(vdev);
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	स्थिर u32 *क्रमmats;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		क्रमmats = cvd->src_क्रमmats;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		काष्ठा coda_q_data *q_data_src;
		काष्ठा vb2_queue *src_vq;

		क्रमmats = cvd->dst_क्रमmats;

		/*
		 * If the source क्रमmat is alपढ़ोy fixed, only allow the same
		 * chroma subsampling.
		 */
		q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		src_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					 V4L2_BUF_TYPE_VIDEO_OUTPUT);
		अगर (q_data_src->fourcc == V4L2_PIX_FMT_JPEG &&
		    vb2_is_streaming(src_vq)) अणु
			अगर (ctx->params.jpeg_chroma_subsampling ==
			    V4L2_JPEG_CHROMA_SUBSAMPLING_420) अणु
				क्रमmats = coda_क्रमmats_420;
			पूर्ण अन्यथा अगर (ctx->params.jpeg_chroma_subsampling ==
				   V4L2_JPEG_CHROMA_SUBSAMPLING_422) अणु
				f->pixelक्रमmat = V4L2_PIX_FMT_YUV422P;
				वापस f->index ? -EINVAL : 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (f->index >= CODA_MAX_FORMATS || क्रमmats[f->index] == 0)
		वापस -EINVAL;

	/* Skip YUYV अगर the vकरोa is not available */
	अगर (!ctx->vकरोa && f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    क्रमmats[f->index] == V4L2_PIX_FMT_YUYV)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index];

	वापस 0;
पूर्ण

अटल पूर्णांक coda_g_fmt(काष्ठा file *file, व्योम *priv,
		      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_q_data *q_data;
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	f->fmt.pix.field	= V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat	= q_data->fourcc;
	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.bytesperline = q_data->bytesperline;

	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.colorspace	= ctx->colorspace;
	f->fmt.pix.xfer_func	= ctx->xfer_func;
	f->fmt.pix.ycbcr_enc	= ctx->ycbcr_enc;
	f->fmt.pix.quantization	= ctx->quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_try_pixelक्रमmat(काष्ठा coda_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_q_data *q_data;
	स्थिर u32 *क्रमmats;
	पूर्णांक i;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		क्रमmats = ctx->cvd->src_क्रमmats;
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		क्रमmats = ctx->cvd->dst_क्रमmats;
	अन्यथा
		वापस -EINVAL;

	क्रम (i = 0; i < CODA_MAX_FORMATS; i++) अणु
		/* Skip YUYV अगर the vकरोa is not available */
		अगर (!ctx->vकरोa && f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE &&
		    क्रमmats[i] == V4L2_PIX_FMT_YUYV)
			जारी;

		अगर (क्रमmats[i] == f->fmt.pix.pixelक्रमmat) अणु
			f->fmt.pix.pixelक्रमmat = क्रमmats[i];
			वापस 0;
		पूर्ण
	पूर्ण

	/* Fall back to currently set pixelक्रमmat */
	q_data = get_q_data(ctx, f->type);
	f->fmt.pix.pixelक्रमmat = q_data->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_try_fmt_vकरोa(काष्ठा coda_ctx *ctx, काष्ठा v4l2_क्रमmat *f,
			     bool *use_vकरोa)
अणु
	पूर्णांक err;

	अगर (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (!use_vकरोa)
		वापस -EINVAL;

	अगर (!ctx->vकरोa) अणु
		*use_vकरोa = false;
		वापस 0;
	पूर्ण

	err = vकरोa_context_configure(शून्य, round_up(f->fmt.pix.width, 16),
				     f->fmt.pix.height, f->fmt.pix.pixelक्रमmat);
	अगर (err) अणु
		*use_vकरोa = false;
		वापस 0;
	पूर्ण

	*use_vकरोa = true;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक coda_estimate_sizeimage(काष्ठा coda_ctx *ctx, u32 sizeimage,
					    u32 width, u32 height)
अणु
	/*
	 * This is a rough estimate क्रम sensible compressed buffer
	 * sizes (between 1 and 16 bits per pixel). This could be
	 * improved by better क्रमmat specअगरic worst हाल estimates.
	 */
	वापस round_up(clamp(sizeimage, width * height / 8,
					 width * height * 2), PAGE_SIZE);
पूर्ण

अटल पूर्णांक coda_try_fmt(काष्ठा coda_ctx *ctx, स्थिर काष्ठा coda_codec *codec,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक max_w, max_h;
	क्रमागत v4l2_field field;

	field = f->fmt.pix.field;
	अगर (field == V4L2_FIELD_ANY)
		field = V4L2_FIELD_NONE;
	अन्यथा अगर (V4L2_FIELD_NONE != field)
		वापस -EINVAL;

	/* V4L2 specअगरication suggests the driver corrects the क्रमmat काष्ठा
	 * अगर any of the dimensions is unsupported */
	f->fmt.pix.field = field;

	coda_get_max_dimensions(dev, codec, &max_w, &max_h);
	v4l_bound_align_image(&f->fmt.pix.width, MIN_W, max_w, W_ALIGN,
			      &f->fmt.pix.height, MIN_H, max_h, H_ALIGN,
			      S_ALIGN);

	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		/*
		 * Frame stride must be at least multiple of 8,
		 * but multiple of 16 क्रम h.264 or JPEG 4:2:x
		 */
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16);
		f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					f->fmt.pix.height * 3 / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16) * 2;
		f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					f->fmt.pix.height;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16);
		f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					f->fmt.pix.height * 2;
		अवरोध;
	हाल V4L2_PIX_FMT_JPEG:
	हाल V4L2_PIX_FMT_H264:
	हाल V4L2_PIX_FMT_MPEG4:
	हाल V4L2_PIX_FMT_MPEG2:
		f->fmt.pix.bytesperline = 0;
		f->fmt.pix.sizeimage = coda_estimate_sizeimage(ctx,
							f->fmt.pix.sizeimage,
							f->fmt.pix.width,
							f->fmt.pix.height);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coda_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा coda_q_data *q_data_src;
	स्थिर काष्ठा coda_codec *codec;
	काष्ठा vb2_queue *src_vq;
	पूर्णांक ret;
	bool use_vकरोa;

	ret = coda_try_pixelक्रमmat(ctx, f);
	अगर (ret < 0)
		वापस ret;

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

	/*
	 * If the source क्रमmat is alपढ़ोy fixed, only allow the same output
	 * resolution. When decoding JPEG images, we also have to make sure to
	 * use the same chroma subsampling.
	 */
	src_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	अगर (vb2_is_streaming(src_vq)) अणु
		f->fmt.pix.width = q_data_src->width;
		f->fmt.pix.height = q_data_src->height;

		अगर (q_data_src->fourcc == V4L2_PIX_FMT_JPEG) अणु
			अगर (ctx->params.jpeg_chroma_subsampling ==
			    V4L2_JPEG_CHROMA_SUBSAMPLING_420 &&
			    f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_YUV422P)
				f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_NV12;
			अन्यथा अगर (ctx->params.jpeg_chroma_subsampling ==
				 V4L2_JPEG_CHROMA_SUBSAMPLING_422)
				f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV422P;
		पूर्ण
	पूर्ण

	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;
	f->fmt.pix.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix.quantization = ctx->quantization;

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	codec = coda_find_codec(ctx->dev, q_data_src->fourcc,
				f->fmt.pix.pixelक्रमmat);
	अगर (!codec)
		वापस -EINVAL;

	ret = coda_try_fmt(ctx, codec, f);
	अगर (ret < 0)
		वापस ret;

	/* The decoders always ग_लिखो complete macroblocks or MCUs */
	अगर (ctx->inst_type == CODA_INST_DECODER) अणु
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16);
		f->fmt.pix.height = round_up(f->fmt.pix.height, 16);
		अगर (codec->src_fourcc == V4L2_PIX_FMT_JPEG &&
		    f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_YUV422P) अणु
			f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					       f->fmt.pix.height * 2;
		पूर्ण अन्यथा अणु
			f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					       f->fmt.pix.height * 3 / 2;
		पूर्ण

		ret = coda_try_fmt_vकरोa(ctx, f, &use_vकरोa);
		अगर (ret < 0)
			वापस ret;

		अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_YUYV) अणु
			अगर (!use_vकरोa)
				वापस -EINVAL;

			f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16) * 2;
			f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
				f->fmt.pix.height;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम coda_set_शेष_colorspace(काष्ठा v4l2_pix_क्रमmat *fmt)
अणु
	क्रमागत v4l2_colorspace colorspace;

	अगर (fmt->pixelक्रमmat == V4L2_PIX_FMT_JPEG)
		colorspace = V4L2_COLORSPACE_JPEG;
	अन्यथा अगर (fmt->width <= 720 && fmt->height <= 576)
		colorspace = V4L2_COLORSPACE_SMPTE170M;
	अन्यथा
		colorspace = V4L2_COLORSPACE_REC709;

	fmt->colorspace = colorspace;
	fmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	fmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	fmt->quantization = V4L2_QUANTIZATION_DEFAULT;
पूर्ण

अटल पूर्णांक coda_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	काष्ठा coda_dev *dev = ctx->dev;
	स्थिर काष्ठा coda_q_data *q_data_dst;
	स्थिर काष्ठा coda_codec *codec;
	पूर्णांक ret;

	ret = coda_try_pixelक्रमmat(ctx, f);
	अगर (ret < 0)
		वापस ret;

	अगर (f->fmt.pix.colorspace == V4L2_COLORSPACE_DEFAULT)
		coda_set_शेष_colorspace(&f->fmt.pix);

	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	codec = coda_find_codec(dev, f->fmt.pix.pixelक्रमmat, q_data_dst->fourcc);

	वापस coda_try_fmt(ctx, codec, f);
पूर्ण

अटल पूर्णांक coda_s_fmt(काष्ठा coda_ctx *ctx, काष्ठा v4l2_क्रमmat *f,
		      काष्ठा v4l2_rect *r)
अणु
	काष्ठा coda_q_data *q_data;
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "%s: %s queue busy: %d\n",
			 __func__, v4l2_type_names[f->type], vq->num_buffers);
		वापस -EBUSY;
	पूर्ण

	q_data->fourcc = f->fmt.pix.pixelक्रमmat;
	q_data->width = f->fmt.pix.width;
	q_data->height = f->fmt.pix.height;
	q_data->bytesperline = f->fmt.pix.bytesperline;
	q_data->sizeimage = f->fmt.pix.sizeimage;
	अगर (r) अणु
		q_data->rect = *r;
	पूर्ण अन्यथा अणु
		q_data->rect.left = 0;
		q_data->rect.top = 0;
		q_data->rect.width = f->fmt.pix.width;
		q_data->rect.height = f->fmt.pix.height;
	पूर्ण

	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		ctx->tiled_map_type = GDI_TILED_FRAME_MB_RASTER_MAP;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		अगर (!disable_tiling && ctx->use_bit &&
		    ctx->dev->devtype->product == CODA_960) अणु
			ctx->tiled_map_type = GDI_TILED_FRAME_MB_RASTER_MAP;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YUV422P:
		ctx->tiled_map_type = GDI_LINEAR_FRAME_MAP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP &&
	    !coda_try_fmt_vकरोa(ctx, f, &ctx->use_vकरोa) &&
	    ctx->use_vकरोa)
		vकरोa_context_configure(ctx->vकरोa,
				       round_up(f->fmt.pix.width, 16),
				       f->fmt.pix.height,
				       f->fmt.pix.pixelक्रमmat);
	अन्यथा
		ctx->use_vकरोa = false;

	coda_dbg(1, ctx, "Setting %s format, wxh: %dx%d, fmt: %4.4s %c\n",
		 v4l2_type_names[f->type], q_data->width, q_data->height,
		 (अक्षर *)&q_data->fourcc,
		 (ctx->tiled_map_type == GDI_LINEAR_FRAME_MAP) ? 'L' : 'T');

	वापस 0;
पूर्ण

अटल पूर्णांक coda_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	काष्ठा coda_q_data *q_data_src;
	स्थिर काष्ठा coda_codec *codec;
	काष्ठा v4l2_rect r;
	पूर्णांक ret;

	ret = coda_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	r.left = 0;
	r.top = 0;
	r.width = q_data_src->width;
	r.height = q_data_src->height;

	ret = coda_s_fmt(ctx, f, &r);
	अगर (ret)
		वापस ret;

	अगर (ctx->inst_type != CODA_INST_ENCODER)
		वापस 0;

	/* Setting the coded क्रमmat determines the selected codec */
	codec = coda_find_codec(ctx->dev, q_data_src->fourcc,
				f->fmt.pix.pixelक्रमmat);
	अगर (!codec) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "failed to determine codec\n");
		वापस -EINVAL;
	पूर्ण
	ctx->codec = codec;

	ctx->colorspace = f->fmt.pix.colorspace;
	ctx->xfer_func = f->fmt.pix.xfer_func;
	ctx->ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->quantization = f->fmt.pix.quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा coda_codec *codec;
	काष्ठा v4l2_क्रमmat f_cap;
	काष्ठा vb2_queue *dst_vq;
	पूर्णांक ret;

	ret = coda_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	ret = coda_s_fmt(ctx, f, शून्य);
	अगर (ret)
		वापस ret;

	ctx->colorspace = f->fmt.pix.colorspace;
	ctx->xfer_func = f->fmt.pix.xfer_func;
	ctx->ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->quantization = f->fmt.pix.quantization;

	अगर (ctx->inst_type != CODA_INST_DECODER)
		वापस 0;

	/* Setting the coded क्रमmat determines the selected codec */
	codec = coda_find_codec(ctx->dev, f->fmt.pix.pixelक्रमmat,
				V4L2_PIX_FMT_YUV420);
	अगर (!codec) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "failed to determine codec\n");
		वापस -EINVAL;
	पूर्ण
	ctx->codec = codec;

	dst_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (!dst_vq)
		वापस -EINVAL;

	/*
	 * Setting the capture queue क्रमmat is not possible जबतक the capture
	 * queue is still busy. This is not an error, but the user will have to
	 * make sure themselves that the capture क्रमmat is set correctly beक्रमe
	 * starting the output queue again.
	 */
	अगर (vb2_is_busy(dst_vq))
		वापस 0;

	स_रखो(&f_cap, 0, माप(f_cap));
	f_cap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	coda_g_fmt(file, priv, &f_cap);
	f_cap.fmt.pix.width = f->fmt.pix.width;
	f_cap.fmt.pix.height = f->fmt.pix.height;

	वापस coda_s_fmt_vid_cap(file, priv, &f_cap);
पूर्ण

अटल पूर्णांक coda_reqbufs(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret;

	ret = v4l2_m2m_reqbufs(file, ctx->fh.m2m_ctx, rb);
	अगर (ret)
		वापस ret;

	/*
	 * Allow to allocate instance specअगरic per-context buffers, such as
	 * bitstream ringbuffer, slice buffer, work buffer, etc. अगर needed.
	 */
	अगर (rb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT && ctx->ops->reqbufs)
		वापस ctx->ops->reqbufs(ctx, rb);

	वापस 0;
पूर्ण

अटल पूर्णांक coda_qbuf(काष्ठा file *file, व्योम *priv,
		     काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->inst_type == CODA_INST_DECODER &&
	    buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		buf->flags &= ~V4L2_BUF_FLAG_LAST;

	वापस v4l2_m2m_qbuf(file, ctx->fh.m2m_ctx, buf);
पूर्ण

अटल पूर्णांक coda_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret;

	ret = v4l2_m2m_dqbuf(file, ctx->fh.m2m_ctx, buf);

	अगर (ctx->inst_type == CODA_INST_DECODER &&
	    buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		buf->flags &= ~V4L2_BUF_FLAG_LAST;

	वापस ret;
पूर्ण

व्योम coda_m2m_buf_करोne(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf,
		       क्रमागत vb2_buffer_state state)
अणु
	स्थिर काष्ठा v4l2_event eos_event = अणु
		.type = V4L2_EVENT_EOS
	पूर्ण;

	अगर (buf->flags & V4L2_BUF_FLAG_LAST)
		v4l2_event_queue_fh(&ctx->fh, &eos_event);

	v4l2_m2m_buf_करोne(buf, state);
पूर्ण

अटल पूर्णांक coda_g_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *s)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा coda_q_data *q_data;
	काष्ठा v4l2_rect r, *rsel;

	q_data = get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;

	r.left = 0;
	r.top = 0;
	r.width = q_data->width;
	r.height = q_data->height;
	rsel = &q_data->rect;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		rsel = &r;
		fallthrough;
	हाल V4L2_SEL_TGT_CROP:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
		    ctx->inst_type == CODA_INST_DECODER)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_PADDED:
		rsel = &r;
		fallthrough;
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
		    ctx->inst_type == CODA_INST_ENCODER)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	s->r = *rsel;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_s_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *s)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा coda_q_data *q_data;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (ctx->inst_type == CODA_INST_ENCODER &&
		    s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
			q_data = get_q_data(ctx, s->type);
			अगर (!q_data)
				वापस -EINVAL;

			s->r.left = 0;
			s->r.top = 0;
			s->r.width = clamp(s->r.width, 2U, q_data->width);
			s->r.height = clamp(s->r.height, 2U, q_data->height);

			अगर (s->flags & V4L2_SEL_FLAG_LE) अणु
				s->r.width = round_up(s->r.width, 2);
				s->r.height = round_up(s->r.height, 2);
			पूर्ण अन्यथा अणु
				s->r.width = round_करोwn(s->r.width, 2);
				s->r.height = round_करोwn(s->r.height, 2);
			पूर्ण

			q_data->rect = s->r;

			coda_dbg(1, ctx, "Setting crop rectangle: %dx%d\n",
				 s->r.width, s->r.height);

			वापस 0;
		पूर्ण
		fallthrough;
	हाल V4L2_SEL_TGT_NATIVE_SIZE:
	हाल V4L2_SEL_TGT_COMPOSE:
		वापस coda_g_selection(file, fh, s);
	शेष:
		/* v4l2-compliance expects this to fail क्रम पढ़ो-only tarमाला_लो */
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक coda_try_encoder_cmd(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_encoder_cmd *ec)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);

	अगर (ctx->inst_type != CODA_INST_ENCODER)
		वापस -ENOTTY;

	वापस v4l2_m2m_ioctl_try_encoder_cmd(file, fh, ec);
पूर्ण

अटल व्योम coda_wake_up_capture_queue(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा vb2_queue *dst_vq;

	coda_dbg(1, ctx, "waking up capture queue\n");

	dst_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	dst_vq->last_buffer_dequeued = true;
	wake_up(&dst_vq->करोne_wq);
पूर्ण

अटल पूर्णांक coda_encoder_cmd(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_encoder_cmd *ec)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा vb2_v4l2_buffer *buf;
	पूर्णांक ret;

	ret = coda_try_encoder_cmd(file, fh, ec);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&ctx->wakeup_mutex);
	buf = v4l2_m2m_last_src_buf(ctx->fh.m2m_ctx);
	अगर (buf) अणु
		/*
		 * If the last output buffer is still on the queue, make sure
		 * that decoder finish_run will see the last flag and report it
		 * to userspace.
		 */
		buf->flags |= V4L2_BUF_FLAG_LAST;
	पूर्ण अन्यथा अणु
		/* Set the stream-end flag on this context */
		ctx->bit_stream_param |= CODA_BIT_STREAM_END_FLAG;

		/*
		 * If the last output buffer has alपढ़ोy been taken from the
		 * queue, wake up the capture queue and संकेत end of stream
		 * via the -EPIPE mechanism.
		 */
		coda_wake_up_capture_queue(ctx);
	पूर्ण
	mutex_unlock(&ctx->wakeup_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक coda_try_decoder_cmd(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_decoder_cmd *dc)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);

	अगर (ctx->inst_type != CODA_INST_DECODER)
		वापस -ENOTTY;

	वापस v4l2_m2m_ioctl_try_decoder_cmd(file, fh, dc);
पूर्ण

अटल bool coda_mark_last_meta(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा coda_buffer_meta *meta;

	coda_dbg(1, ctx, "marking last meta\n");

	spin_lock(&ctx->buffer_meta_lock);
	अगर (list_empty(&ctx->buffer_meta_list)) अणु
		spin_unlock(&ctx->buffer_meta_lock);
		वापस false;
	पूर्ण

	meta = list_last_entry(&ctx->buffer_meta_list, काष्ठा coda_buffer_meta,
			       list);
	meta->last = true;

	spin_unlock(&ctx->buffer_meta_lock);
	वापस true;
पूर्ण

अटल bool coda_mark_last_dst_buf(काष्ठा coda_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *buf;
	काष्ठा vb2_buffer *dst_vb;
	काष्ठा vb2_queue *dst_vq;
	अचिन्हित दीर्घ flags;

	coda_dbg(1, ctx, "marking last capture buffer\n");

	dst_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	spin_lock_irqsave(&dst_vq->करोne_lock, flags);
	अगर (list_empty(&dst_vq->करोne_list)) अणु
		spin_unlock_irqrestore(&dst_vq->करोne_lock, flags);
		वापस false;
	पूर्ण

	dst_vb = list_last_entry(&dst_vq->करोne_list, काष्ठा vb2_buffer,
				 करोne_entry);
	buf = to_vb2_v4l2_buffer(dst_vb);
	buf->flags |= V4L2_BUF_FLAG_LAST;

	spin_unlock_irqrestore(&dst_vq->करोne_lock, flags);
	वापस true;
पूर्ण

अटल पूर्णांक coda_decoder_cmd(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_decoder_cmd *dc)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *buf;
	काष्ठा vb2_queue *dst_vq;
	bool stream_end;
	bool wakeup;
	पूर्णांक ret;

	ret = coda_try_decoder_cmd(file, fh, dc);
	अगर (ret < 0)
		वापस ret;

	चयन (dc->cmd) अणु
	हाल V4L2_DEC_CMD_START:
		mutex_lock(&dev->coda_mutex);
		mutex_lock(&ctx->bitstream_mutex);
		coda_bitstream_flush(ctx);
		dst_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					 V4L2_BUF_TYPE_VIDEO_CAPTURE);
		vb2_clear_last_buffer_dequeued(dst_vq);
		ctx->bit_stream_param &= ~CODA_BIT_STREAM_END_FLAG;
		coda_fill_bitstream(ctx, शून्य);
		mutex_unlock(&ctx->bitstream_mutex);
		mutex_unlock(&dev->coda_mutex);
		अवरोध;
	हाल V4L2_DEC_CMD_STOP:
		stream_end = false;
		wakeup = false;

		mutex_lock(&ctx->wakeup_mutex);

		buf = v4l2_m2m_last_src_buf(ctx->fh.m2m_ctx);
		अगर (buf) अणु
			coda_dbg(1, ctx, "marking last pending buffer\n");

			/* Mark last buffer */
			buf->flags |= V4L2_BUF_FLAG_LAST;

			अगर (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) == 0) अणु
				coda_dbg(1, ctx, "all remaining buffers queued\n");
				stream_end = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ctx->use_bit)
				अगर (coda_mark_last_meta(ctx))
					stream_end = true;
				अन्यथा
					wakeup = true;
			अन्यथा
				अगर (!coda_mark_last_dst_buf(ctx))
					wakeup = true;
		पूर्ण

		अगर (stream_end) अणु
			coda_dbg(1, ctx, "all remaining buffers queued\n");

			/* Set the stream-end flag on this context */
			coda_bit_stream_end_flag(ctx);
			ctx->hold = false;
			v4l2_m2m_try_schedule(ctx->fh.m2m_ctx);
		पूर्ण

		अगर (wakeup) अणु
			/* If there is no buffer in flight, wake up */
			coda_wake_up_capture_queue(ctx);
		पूर्ण

		mutex_unlock(&ctx->wakeup_mutex);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coda_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा coda_q_data *q_data_dst;
	स्थिर काष्ठा coda_codec *codec;

	अगर (ctx->inst_type != CODA_INST_ENCODER)
		वापस -ENOTTY;

	अगर (fsize->index)
		वापस -EINVAL;

	अगर (coda_क्रमmat_normalize_yuv(fsize->pixel_क्रमmat) ==
	    V4L2_PIX_FMT_YUV420) अणु
		q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		codec = coda_find_codec(ctx->dev, fsize->pixel_क्रमmat,
					q_data_dst->fourcc);
	पूर्ण अन्यथा अणु
		codec = coda_find_codec(ctx->dev, V4L2_PIX_FMT_YUV420,
					fsize->pixel_क्रमmat);
	पूर्ण
	अगर (!codec)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = MIN_W;
	fsize->stepwise.max_width = codec->max_w;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = MIN_H;
	fsize->stepwise.max_height = codec->max_h;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frmivalक्रमागत *f)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	पूर्णांक i;

	अगर (f->index)
		वापस -EINVAL;

	/* Disallow YUYV अगर the vकरोa is not available */
	अगर (!ctx->vकरोa && f->pixel_क्रमmat == V4L2_PIX_FMT_YUYV)
		वापस -EINVAL;

	क्रम (i = 0; i < CODA_MAX_FORMATS; i++) अणु
		अगर (f->pixel_क्रमmat == ctx->cvd->src_क्रमmats[i] ||
		    f->pixel_क्रमmat == ctx->cvd->dst_क्रमmats[i])
			अवरोध;
	पूर्ण
	अगर (i == CODA_MAX_FORMATS)
		वापस -EINVAL;

	f->type = V4L2_FRMIVAL_TYPE_CONTINUOUS;
	f->stepwise.min.numerator = 1;
	f->stepwise.min.denominator = 65535;
	f->stepwise.max.numerator = 65536;
	f->stepwise.max.denominator = 1;
	f->stepwise.step.numerator = 1;
	f->stepwise.step.denominator = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा v4l2_fract *tpf;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	tpf = &a->parm.output.समयperframe;
	tpf->denominator = ctx->params.framerate & CODA_FRATE_RES_MASK;
	tpf->numerator = 1 + (ctx->params.framerate >>
			      CODA_FRATE_DIV_OFFSET);

	वापस 0;
पूर्ण

/*
 * Approximate समयperframe v4l2_fract with values that can be written
 * पूर्णांकo the 16-bit CODA_FRATE_DIV and CODA_FRATE_RES fields.
 */
अटल व्योम coda_approximate_समयperframe(काष्ठा v4l2_fract *समयperframe)
अणु
	काष्ठा v4l2_fract s = *समयperframe;
	काष्ठा v4l2_fract f0;
	काष्ठा v4l2_fract f1 = अणु 1, 0 पूर्ण;
	काष्ठा v4l2_fract f2 = अणु 0, 1 पूर्ण;
	अचिन्हित पूर्णांक i, भाग, s_denominator;

	/* Lower bound is 1/65535 */
	अगर (s.numerator == 0 || s.denominator / s.numerator > 65535) अणु
		समयperframe->numerator = 1;
		समयperframe->denominator = 65535;
		वापस;
	पूर्ण

	/* Upper bound is 65536/1 */
	अगर (s.denominator == 0 || s.numerator / s.denominator > 65536) अणु
		समयperframe->numerator = 65536;
		समयperframe->denominator = 1;
		वापस;
	पूर्ण

	/* Reduce fraction to lowest terms */
	भाग = gcd(s.numerator, s.denominator);
	अगर (भाग > 1) अणु
		s.numerator /= भाग;
		s.denominator /= भाग;
	पूर्ण

	अगर (s.numerator <= 65536 && s.denominator < 65536) अणु
		*समयperframe = s;
		वापस;
	पूर्ण

	/* Find successive convergents from जारीd fraction expansion */
	जबतक (f2.numerator <= 65536 && f2.denominator < 65536) अणु
		f0 = f1;
		f1 = f2;

		/* Stop when f2 exactly equals समयperframe */
		अगर (s.numerator == 0)
			अवरोध;

		i = s.denominator / s.numerator;

		f2.numerator = f0.numerator + i * f1.numerator;
		f2.denominator = f0.denominator + i * f2.denominator;

		s_denominator = s.numerator;
		s.numerator = s.denominator % s.numerator;
		s.denominator = s_denominator;
	पूर्ण

	*समयperframe = f1;
पूर्ण

अटल uपूर्णांक32_t coda_समयperframe_to_frate(काष्ठा v4l2_fract *समयperframe)
अणु
	वापस ((समयperframe->numerator - 1) << CODA_FRATE_DIV_OFFSET) |
		समयperframe->denominator;
पूर्ण

अटल पूर्णांक coda_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);
	काष्ठा v4l2_fract *tpf;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	tpf = &a->parm.output.समयperframe;
	coda_approximate_समयperframe(tpf);
	ctx->params.framerate = coda_समयperframe_to_frate(tpf);
	ctx->params.framerate_changed = true;

	वापस 0;
पूर्ण

अटल पूर्णांक coda_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	काष्ठा coda_ctx *ctx = fh_to_ctx(fh);

	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	हाल V4L2_EVENT_SOURCE_CHANGE:
		अगर (ctx->inst_type == CODA_INST_DECODER)
			वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
		अन्यथा
			वापस -EINVAL;
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops coda_ioctl_ops = अणु
	.vidioc_querycap	= coda_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = coda_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap	= coda_g_fmt,
	.vidioc_try_fmt_vid_cap	= coda_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= coda_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out = coda_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out	= coda_g_fmt,
	.vidioc_try_fmt_vid_out	= coda_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= coda_s_fmt_vid_out,

	.vidioc_reqbufs		= coda_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,

	.vidioc_qbuf		= coda_qbuf,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,
	.vidioc_dqbuf		= coda_dqbuf,
	.vidioc_create_bufs	= v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf	= v4l2_m2m_ioctl_prepare_buf,

	.vidioc_streamon	= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,

	.vidioc_g_selection	= coda_g_selection,
	.vidioc_s_selection	= coda_s_selection,

	.vidioc_try_encoder_cmd	= coda_try_encoder_cmd,
	.vidioc_encoder_cmd	= coda_encoder_cmd,
	.vidioc_try_decoder_cmd	= coda_try_decoder_cmd,
	.vidioc_decoder_cmd	= coda_decoder_cmd,

	.vidioc_g_parm		= coda_g_parm,
	.vidioc_s_parm		= coda_s_parm,

	.vidioc_क्रमागत_framesizes	= coda_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = coda_क्रमागत_frameपूर्णांकervals,

	.vidioc_subscribe_event = coda_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/*
 * Mem-to-mem operations.
 */

अटल व्योम coda_device_run(व्योम *m2m_priv)
अणु
	काष्ठा coda_ctx *ctx = m2m_priv;
	काष्ठा coda_dev *dev = ctx->dev;

	queue_work(dev->workqueue, &ctx->pic_run_work);
पूर्ण

अटल व्योम coda_pic_run_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा coda_ctx *ctx = container_of(work, काष्ठा coda_ctx, pic_run_work);
	काष्ठा coda_dev *dev = ctx->dev;
	पूर्णांक ret;

	mutex_lock(&ctx->buffer_mutex);
	mutex_lock(&dev->coda_mutex);

	ret = ctx->ops->prepare_run(ctx);
	अगर (ret < 0 && ctx->inst_type == CODA_INST_DECODER) अणु
		mutex_unlock(&dev->coda_mutex);
		mutex_unlock(&ctx->buffer_mutex);
		/* job_finish scheduled by prepare_decode */
		वापस;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&ctx->completion,
					 msecs_to_jअगरfies(1000))) अणु
		dev_err(dev->dev, "CODA PIC_RUN timeout\n");

		ctx->hold = true;

		coda_hw_reset(ctx);

		अगर (ctx->ops->run_समयout)
			ctx->ops->run_समयout(ctx);
	पूर्ण अन्यथा अणु
		ctx->ops->finish_run(ctx);
	पूर्ण

	अगर ((ctx->पातing || (!ctx->streamon_cap && !ctx->streamon_out)) &&
	    ctx->ops->seq_end_work)
		queue_work(dev->workqueue, &ctx->seq_end_work);

	mutex_unlock(&dev->coda_mutex);
	mutex_unlock(&ctx->buffer_mutex);

	v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल पूर्णांक coda_job_पढ़ोy(व्योम *m2m_priv)
अणु
	काष्ठा coda_ctx *ctx = m2m_priv;
	पूर्णांक src_bufs = v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx);

	/*
	 * For both 'P' and 'key' frame हालs 1 picture
	 * and 1 frame are needed. In the decoder हाल,
	 * the compressed frame can be in the bitstream.
	 */
	अगर (!src_bufs && ctx->inst_type != CODA_INST_DECODER) अणु
		coda_dbg(1, ctx, "not ready: not enough vid-out buffers.\n");
		वापस 0;
	पूर्ण

	अगर (!v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx)) अणु
		coda_dbg(1, ctx, "not ready: not enough vid-cap buffers.\n");
		वापस 0;
	पूर्ण

	अगर (ctx->inst_type == CODA_INST_DECODER && ctx->use_bit) अणु
		bool stream_end = ctx->bit_stream_param &
				  CODA_BIT_STREAM_END_FLAG;
		पूर्णांक num_metas = ctx->num_metas;
		काष्ठा coda_buffer_meta *meta;
		अचिन्हित पूर्णांक count;

		count = hweight32(ctx->frm_dis_flg);
		अगर (ctx->use_vकरोa && count >= (ctx->num_पूर्णांकernal_frames - 1)) अणु
			coda_dbg(1, ctx,
				 "not ready: all internal buffers in use: %d/%d (0x%x)",
				 count, ctx->num_पूर्णांकernal_frames,
				 ctx->frm_dis_flg);
			वापस 0;
		पूर्ण

		अगर (ctx->hold && !src_bufs) अणु
			coda_dbg(1, ctx,
				 "not ready: on hold for more buffers.\n");
			वापस 0;
		पूर्ण

		अगर (!stream_end && (num_metas + src_bufs) < 2) अणु
			coda_dbg(1, ctx,
				 "not ready: need 2 buffers available (queue:%d + bitstream:%d)\n",
				 num_metas, src_bufs);
			वापस 0;
		पूर्ण

		meta = list_first_entry(&ctx->buffer_meta_list,
					काष्ठा coda_buffer_meta, list);
		अगर (!coda_bitstream_can_fetch_past(ctx, meta->end) &&
		    !stream_end) अणु
			coda_dbg(1, ctx,
				 "not ready: not enough bitstream data to read past %u (%u)\n",
				 meta->end, ctx->bitstream_fअगरo.kfअगरo.in);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (ctx->पातing) अणु
		coda_dbg(1, ctx, "not ready: aborting\n");
		वापस 0;
	पूर्ण

	coda_dbg(2, ctx, "job ready\n");

	वापस 1;
पूर्ण

अटल व्योम coda_job_पात(व्योम *priv)
अणु
	काष्ठा coda_ctx *ctx = priv;

	ctx->पातing = 1;

	coda_dbg(1, ctx, "job abort\n");
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops coda_m2m_ops = अणु
	.device_run	= coda_device_run,
	.job_पढ़ोy	= coda_job_पढ़ोy,
	.job_पात	= coda_job_पात,
पूर्ण;

अटल व्योम set_शेष_params(काष्ठा coda_ctx *ctx)
अणु
	अचिन्हित पूर्णांक max_w, max_h, usize, csize;

	ctx->codec = coda_find_codec(ctx->dev, ctx->cvd->src_क्रमmats[0],
				     ctx->cvd->dst_क्रमmats[0]);
	max_w = min(ctx->codec->max_w, 1920U);
	max_h = min(ctx->codec->max_h, 1088U);
	usize = max_w * max_h * 3 / 2;
	csize = coda_estimate_sizeimage(ctx, usize, max_w, max_h);

	ctx->params.codec_mode = ctx->codec->mode;
	अगर (ctx->cvd->src_क्रमmats[0] == V4L2_PIX_FMT_JPEG)
		ctx->colorspace = V4L2_COLORSPACE_JPEG;
	अन्यथा
		ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	ctx->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	ctx->quantization = V4L2_QUANTIZATION_DEFAULT;
	ctx->params.framerate = 30;

	/* Default क्रमmats क्रम output and input queues */
	ctx->q_data[V4L2_M2M_SRC].fourcc = ctx->cvd->src_क्रमmats[0];
	ctx->q_data[V4L2_M2M_DST].fourcc = ctx->cvd->dst_क्रमmats[0];
	ctx->q_data[V4L2_M2M_SRC].width = max_w;
	ctx->q_data[V4L2_M2M_SRC].height = max_h;
	ctx->q_data[V4L2_M2M_DST].width = max_w;
	ctx->q_data[V4L2_M2M_DST].height = max_h;
	अगर (ctx->codec->src_fourcc == V4L2_PIX_FMT_YUV420) अणु
		ctx->q_data[V4L2_M2M_SRC].bytesperline = max_w;
		ctx->q_data[V4L2_M2M_SRC].sizeimage = usize;
		ctx->q_data[V4L2_M2M_DST].bytesperline = 0;
		ctx->q_data[V4L2_M2M_DST].sizeimage = csize;
	पूर्ण अन्यथा अणु
		ctx->q_data[V4L2_M2M_SRC].bytesperline = 0;
		ctx->q_data[V4L2_M2M_SRC].sizeimage = csize;
		ctx->q_data[V4L2_M2M_DST].bytesperline = max_w;
		ctx->q_data[V4L2_M2M_DST].sizeimage = usize;
	पूर्ण
	ctx->q_data[V4L2_M2M_SRC].rect.width = max_w;
	ctx->q_data[V4L2_M2M_SRC].rect.height = max_h;
	ctx->q_data[V4L2_M2M_DST].rect.width = max_w;
	ctx->q_data[V4L2_M2M_DST].rect.height = max_h;

	/*
	 * Since the RBC2AXI logic only supports a single chroma plane,
	 * macroblock tiling only works क्रम to NV12 pixel क्रमmat.
	 */
	ctx->tiled_map_type = GDI_LINEAR_FRAME_MAP;
पूर्ण

/*
 * Queue operations
 */
अटल पूर्णांक coda_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा coda_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा coda_q_data *q_data;
	अचिन्हित पूर्णांक size;

	q_data = get_q_data(ctx, vq->type);
	size = q_data->sizeimage;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	coda_dbg(1, ctx, "get %d buffer(s) of size %d each.\n", *nbuffers,
		 size);

	वापस 0;
पूर्ण

अटल पूर्णांक coda_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा coda_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा coda_q_data *q_data;

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			v4l2_warn(&ctx->dev->v4l2_dev,
				  "%s field isn't supported\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (vb2_plane_size(vb, 0) < q_data->sizeimage) अणु
		v4l2_warn(&ctx->dev->v4l2_dev,
			  "%s data will not fit into plane (%lu < %lu)\n",
			  __func__, vb2_plane_size(vb, 0),
			  (दीर्घ)q_data->sizeimage);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम coda_update_menu_ctrl(काष्ठा v4l2_ctrl *ctrl, पूर्णांक value)
अणु
	अगर (!ctrl)
		वापस;

	v4l2_ctrl_lock(ctrl);

	/*
	 * Extend the control range अगर the parsed stream contains a known but
	 * unsupported value or level.
	 */
	अगर (value > ctrl->maximum) अणु
		__v4l2_ctrl_modअगरy_range(ctrl, ctrl->minimum, value,
			ctrl->menu_skip_mask & ~(1 << value),
			ctrl->शेष_value);
	पूर्ण अन्यथा अगर (value < ctrl->minimum) अणु
		__v4l2_ctrl_modअगरy_range(ctrl, value, ctrl->maximum,
			ctrl->menu_skip_mask & ~(1 << value),
			ctrl->शेष_value);
	पूर्ण

	__v4l2_ctrl_s_ctrl(ctrl, value);

	v4l2_ctrl_unlock(ctrl);
पूर्ण

व्योम coda_update_profile_level_ctrls(काष्ठा coda_ctx *ctx, u8 profile_idc,
				     u8 level_idc)
अणु
	स्थिर अक्षर * स्थिर *profile_names;
	स्थिर अक्षर * स्थिर *level_names;
	काष्ठा v4l2_ctrl *profile_ctrl;
	काष्ठा v4l2_ctrl *level_ctrl;
	स्थिर अक्षर *codec_name;
	u32 profile_cid;
	u32 level_cid;
	पूर्णांक profile;
	पूर्णांक level;

	चयन (ctx->codec->src_fourcc) अणु
	हाल V4L2_PIX_FMT_H264:
		codec_name = "H264";
		profile_cid = V4L2_CID_MPEG_VIDEO_H264_PROखाता;
		level_cid = V4L2_CID_MPEG_VIDEO_H264_LEVEL;
		profile_ctrl = ctx->h264_profile_ctrl;
		level_ctrl = ctx->h264_level_ctrl;
		profile = coda_h264_profile(profile_idc);
		level = coda_h264_level(level_idc);
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG2:
		codec_name = "MPEG-2";
		profile_cid = V4L2_CID_MPEG_VIDEO_MPEG2_PROखाता;
		level_cid = V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL;
		profile_ctrl = ctx->mpeg2_profile_ctrl;
		level_ctrl = ctx->mpeg2_level_ctrl;
		profile = coda_mpeg2_profile(profile_idc);
		level = coda_mpeg2_level(level_idc);
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG4:
		codec_name = "MPEG-4";
		profile_cid = V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता;
		level_cid = V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL;
		profile_ctrl = ctx->mpeg4_profile_ctrl;
		level_ctrl = ctx->mpeg4_level_ctrl;
		profile = coda_mpeg4_profile(profile_idc);
		level = coda_mpeg4_level(level_idc);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	profile_names = v4l2_ctrl_get_menu(profile_cid);
	level_names = v4l2_ctrl_get_menu(level_cid);

	अगर (profile < 0) अणु
		v4l2_warn(&ctx->dev->v4l2_dev, "Invalid %s profile: %u\n",
			  codec_name, profile_idc);
	पूर्ण अन्यथा अणु
		coda_dbg(1, ctx, "Parsed %s profile: %s\n", codec_name,
			 profile_names[profile]);
		coda_update_menu_ctrl(profile_ctrl, profile);
	पूर्ण

	अगर (level < 0) अणु
		v4l2_warn(&ctx->dev->v4l2_dev, "Invalid %s level: %u\n",
			  codec_name, level_idc);
	पूर्ण अन्यथा अणु
		coda_dbg(1, ctx, "Parsed %s level: %s\n", codec_name,
			 level_names[level]);
		coda_update_menu_ctrl(level_ctrl, level);
	पूर्ण
पूर्ण

अटल व्योम coda_queue_source_change_event(काष्ठा coda_ctx *ctx)
अणु
	अटल स्थिर काष्ठा v4l2_event source_change_event = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
	पूर्ण;

	v4l2_event_queue_fh(&ctx->fh, &source_change_event);
पूर्ण

अटल व्योम coda_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा coda_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा coda_q_data *q_data;

	q_data = get_q_data(ctx, vb->vb2_queue->type);

	/*
	 * In the decoder हाल, immediately try to copy the buffer पूर्णांकo the
	 * bitstream ringbuffer and mark it as पढ़ोy to be dequeued.
	 */
	अगर (ctx->bitstream.size && vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		/*
		 * For backwards compatibility, queuing an empty buffer marks
		 * the stream end
		 */
		अगर (vb2_get_plane_payload(vb, 0) == 0)
			coda_bit_stream_end_flag(ctx);

		अगर (q_data->fourcc == V4L2_PIX_FMT_H264) अणु
			/*
			 * Unless alपढ़ोy करोne, try to obtain profile_idc and
			 * level_idc from the SPS header. This allows to decide
			 * whether to enable reordering during sequence
			 * initialization.
			 */
			अगर (!ctx->params.h264_profile_idc) अणु
				coda_sps_parse_profile(ctx, vb);
				coda_update_profile_level_ctrls(ctx,
						ctx->params.h264_profile_idc,
						ctx->params.h264_level_idc);
			पूर्ण
		पूर्ण

		mutex_lock(&ctx->bitstream_mutex);
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		अगर (vb2_is_streaming(vb->vb2_queue))
			/* This set buf->sequence = ctx->qsequence++ */
			coda_fill_bitstream(ctx, शून्य);
		mutex_unlock(&ctx->bitstream_mutex);

		अगर (!ctx->initialized) अणु
			/*
			 * Run sequence initialization in हाल the queued
			 * buffer contained headers.
			 */
			अगर (vb2_is_streaming(vb->vb2_queue) &&
			    ctx->ops->seq_init_work) अणु
				queue_work(ctx->dev->workqueue,
					   &ctx->seq_init_work);
				flush_work(&ctx->seq_init_work);
			पूर्ण

			अगर (ctx->initialized)
				coda_queue_source_change_event(ctx);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((ctx->inst_type == CODA_INST_ENCODER || !ctx->use_bit) &&
		    vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			vbuf->sequence = ctx->qsequence++;
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
	पूर्ण
पूर्ण

पूर्णांक coda_alloc_aux_buf(काष्ठा coda_dev *dev, काष्ठा coda_aux_buf *buf,
		       माप_प्रकार size, स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	buf->vaddr = dma_alloc_coherent(dev->dev, size, &buf->paddr,
					GFP_KERNEL);
	अगर (!buf->vaddr) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to allocate %s buffer of size %zu\n",
			 name, size);
		वापस -ENOMEM;
	पूर्ण

	buf->size = size;

	अगर (name && parent) अणु
		buf->blob.data = buf->vaddr;
		buf->blob.size = size;
		buf->dentry = debugfs_create_blob(name, 0644, parent,
						  &buf->blob);
	पूर्ण

	वापस 0;
पूर्ण

व्योम coda_मुक्त_aux_buf(काष्ठा coda_dev *dev,
		       काष्ठा coda_aux_buf *buf)
अणु
	अगर (buf->vaddr) अणु
		dma_मुक्त_coherent(dev->dev, buf->size, buf->vaddr, buf->paddr);
		buf->vaddr = शून्य;
		buf->size = 0;
		debugfs_हटाओ(buf->dentry);
		buf->dentry = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक coda_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा coda_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा v4l2_device *v4l2_dev = &ctx->dev->v4l2_dev;
	काष्ठा coda_q_data *q_data_src, *q_data_dst;
	काष्ठा v4l2_m2m_buffer *m2m_buf, *पंचांगp;
	काष्ठा vb2_v4l2_buffer *buf;
	काष्ठा list_head list;
	पूर्णांक ret = 0;

	अगर (count < 1)
		वापस -EINVAL;

	coda_dbg(1, ctx, "start streaming %s\n", v4l2_type_names[q->type]);

	INIT_LIST_HEAD(&list);

	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		अगर (ctx->inst_type == CODA_INST_DECODER && ctx->use_bit) अणु
			/* copy the buffers that were queued beक्रमe streamon */
			mutex_lock(&ctx->bitstream_mutex);
			coda_fill_bitstream(ctx, &list);
			mutex_unlock(&ctx->bitstream_mutex);

			अगर (ctx->dev->devtype->product != CODA_960 &&
			    coda_get_bitstream_payload(ctx) < 512) अणु
				v4l2_err(v4l2_dev, "start payload < 512\n");
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			अगर (!ctx->initialized) अणु
				/* Run sequence initialization */
				अगर (ctx->ops->seq_init_work) अणु
					queue_work(ctx->dev->workqueue,
						   &ctx->seq_init_work);
					flush_work(&ctx->seq_init_work);
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * Check the first input JPEG buffer to determine chroma
		 * subsampling.
		 */
		अगर (q_data_src->fourcc == V4L2_PIX_FMT_JPEG) अणु
			buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
			ret = coda_jpeg_decode_header(ctx, &buf->vb2_buf);
			अगर (ret < 0) अणु
				v4l2_err(v4l2_dev,
					 "failed to decode JPEG header: %d\n",
					 ret);
				जाओ err;
			पूर्ण

			q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
			q_data_dst->width = round_up(q_data_src->width, 16);
			q_data_dst->height = round_up(q_data_src->height, 16);
			q_data_dst->bytesperline = q_data_dst->width;
			अगर (ctx->params.jpeg_chroma_subsampling ==
			    V4L2_JPEG_CHROMA_SUBSAMPLING_420) अणु
				q_data_dst->sizeimage =
						q_data_dst->bytesperline *
						q_data_dst->height * 3 / 2;
				अगर (q_data_dst->fourcc != V4L2_PIX_FMT_YUV420)
					q_data_dst->fourcc = V4L2_PIX_FMT_NV12;
			पूर्ण अन्यथा अणु
				q_data_dst->sizeimage =
						q_data_dst->bytesperline *
						q_data_dst->height * 2;
				q_data_dst->fourcc = V4L2_PIX_FMT_YUV422P;
			पूर्ण
			q_data_dst->rect.left = 0;
			q_data_dst->rect.top = 0;
			q_data_dst->rect.width = q_data_src->width;
			q_data_dst->rect.height = q_data_src->height;
		पूर्ण
		ctx->streamon_out = 1;
	पूर्ण अन्यथा अणु
		ctx->streamon_cap = 1;
	पूर्ण

	/* Don't start the coda unless both queues are on */
	अगर (!(ctx->streamon_out && ctx->streamon_cap))
		जाओ out;

	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर ((q_data_src->rect.width != q_data_dst->width &&
	     round_up(q_data_src->rect.width, 16) != q_data_dst->width) ||
	    (q_data_src->rect.height != q_data_dst->height &&
	     round_up(q_data_src->rect.height, 16) != q_data_dst->height)) अणु
		v4l2_err(v4l2_dev, "can't convert %dx%d to %dx%d\n",
			 q_data_src->rect.width, q_data_src->rect.height,
			 q_data_dst->width, q_data_dst->height);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Allow BIT decoder device_run with no new buffers queued */
	अगर (ctx->inst_type == CODA_INST_DECODER && ctx->use_bit)
		v4l2_m2m_set_src_buffered(ctx->fh.m2m_ctx, true);

	ctx->gopcounter = ctx->params.gop_size - 1;

	अगर (q_data_dst->fourcc == V4L2_PIX_FMT_JPEG)
		ctx->params.gop_size = 1;
	ctx->gopcounter = ctx->params.gop_size - 1;
	/* Only decoders have this control */
	अगर (ctx->mb_err_cnt_ctrl)
		v4l2_ctrl_s_ctrl(ctx->mb_err_cnt_ctrl, 0);

	ret = ctx->ops->start_streaming(ctx);
	अगर (ctx->inst_type == CODA_INST_DECODER) अणु
		अगर (ret == -EAGAIN)
			जाओ out;
	पूर्ण
	अगर (ret < 0)
		जाओ err;

out:
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		list_क्रम_each_entry_safe(m2m_buf, पंचांगp, &list, list) अणु
			list_del(&m2m_buf->list);
			v4l2_m2m_buf_करोne(&m2m_buf->vb, VB2_BUF_STATE_DONE);
		पूर्ण
	पूर्ण
	वापस 0;

err:
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		list_क्रम_each_entry_safe(m2m_buf, पंचांगp, &list, list) अणु
			list_del(&m2m_buf->list);
			v4l2_m2m_buf_करोne(&m2m_buf->vb, VB2_BUF_STATE_QUEUED);
		पूर्ण
		जबतक ((buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
	पूर्ण अन्यथा अणु
		जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम coda_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा coda_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा coda_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *buf;
	bool stop;

	stop = ctx->streamon_out && ctx->streamon_cap;

	coda_dbg(1, ctx, "stop streaming %s\n", v4l2_type_names[q->type]);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		ctx->streamon_out = 0;

		coda_bit_stream_end_flag(ctx);

		ctx->qsequence = 0;

		जबतक ((buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		ctx->streamon_cap = 0;

		ctx->osequence = 0;
		ctx->sequence_offset = 0;

		जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	अगर (stop) अणु
		काष्ठा coda_buffer_meta *meta;

		अगर (ctx->ops->seq_end_work) अणु
			queue_work(dev->workqueue, &ctx->seq_end_work);
			flush_work(&ctx->seq_end_work);
		पूर्ण
		spin_lock(&ctx->buffer_meta_lock);
		जबतक (!list_empty(&ctx->buffer_meta_list)) अणु
			meta = list_first_entry(&ctx->buffer_meta_list,
						काष्ठा coda_buffer_meta, list);
			list_del(&meta->list);
			kमुक्त(meta);
		पूर्ण
		ctx->num_metas = 0;
		spin_unlock(&ctx->buffer_meta_lock);
		kfअगरo_init(&ctx->bitstream_fअगरo,
			ctx->bitstream.vaddr, ctx->bitstream.size);
		ctx->runcounter = 0;
		ctx->पातing = 0;
		ctx->hold = false;
	पूर्ण

	अगर (!ctx->streamon_out && !ctx->streamon_cap)
		ctx->bit_stream_param &= ~CODA_BIT_STREAM_END_FLAG;
पूर्ण

अटल स्थिर काष्ठा vb2_ops coda_qops = अणु
	.queue_setup		= coda_queue_setup,
	.buf_prepare		= coda_buf_prepare,
	.buf_queue		= coda_buf_queue,
	.start_streaming	= coda_start_streaming,
	.stop_streaming		= coda_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक coda_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	स्थिर अक्षर * स्थिर *val_names = v4l2_ctrl_get_menu(ctrl->id);
	काष्ठा coda_ctx *ctx =
			container_of(ctrl->handler, काष्ठा coda_ctx, ctrls);

	अगर (val_names)
		coda_dbg(2, ctx, "s_ctrl: id = 0x%x, name = \"%s\", val = %d (\"%s\")\n",
			 ctrl->id, ctrl->name, ctrl->val, val_names[ctrl->val]);
	अन्यथा
		coda_dbg(2, ctx, "s_ctrl: id = 0x%x, name = \"%s\", val = %d\n",
			 ctrl->id, ctrl->name, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		अगर (ctrl->val)
			ctx->params.rot_mode |= CODA_MIR_HOR;
		अन्यथा
			ctx->params.rot_mode &= ~CODA_MIR_HOR;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		अगर (ctrl->val)
			ctx->params.rot_mode |= CODA_MIR_VER;
		अन्यथा
			ctx->params.rot_mode &= ~CODA_MIR_VER;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		ctx->params.bitrate = ctrl->val / 1000;
		ctx->params.bitrate_changed = true;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctx->params.gop_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
		ctx->params.h264_पूर्णांकra_qp = ctrl->val;
		ctx->params.h264_पूर्णांकra_qp_changed = true;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
		ctx->params.h264_पूर्णांकer_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		ctx->params.h264_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		ctx->params.h264_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:
		ctx->params.h264_slice_alpha_c0_offset_भाग2 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:
		ctx->params.h264_slice_beta_offset_भाग2 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		ctx->params.h264_disable_deblocking_filter_idc = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_CONSTRAINED_INTRA_PREDICTION:
		ctx->params.h264_स्थिरrained_पूर्णांकra_pred_flag = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		ctx->params.frame_rc_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
		ctx->params.mb_rc_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_CHROMA_QP_INDEX_OFFSET:
		ctx->params.h264_chroma_qp_index_offset = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
		/* TODO: चयन between baseline and स्थिरrained baseline */
		अगर (ctx->inst_type == CODA_INST_ENCODER)
			ctx->params.h264_profile_idc = 66;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		/* nothing to करो, this is set by the encoder */
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP:
		ctx->params.mpeg4_पूर्णांकra_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP:
		ctx->params.mpeg4_पूर्णांकer_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		/* nothing to करो, these are fixed */
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		ctx->params.slice_mode = ctrl->val;
		ctx->params.slice_mode_changed = true;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:
		ctx->params.slice_max_mb = ctrl->val;
		ctx->params.slice_mode_changed = true;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:
		ctx->params.slice_max_bits = ctrl->val * 8;
		ctx->params.slice_mode_changed = true;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:
		ctx->params.पूर्णांकra_refresh = ctrl->val;
		ctx->params.पूर्णांकra_refresh_changed = true;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		ctx->params.क्रमce_ipicture = true;
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		coda_set_jpeg_compression_quality(ctx, ctrl->val);
		अवरोध;
	हाल V4L2_CID_JPEG_RESTART_INTERVAL:
		ctx->params.jpeg_restart_पूर्णांकerval = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VBV_DELAY:
		ctx->params.vbv_delay = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VBV_SIZE:
		ctx->params.vbv_size = min(ctrl->val * 8192, 0x7fffffff);
		अवरोध;
	शेष:
		coda_dbg(1, ctx, "Invalid control, id=%d, val=%d\n",
			 ctrl->id, ctrl->val);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops coda_ctrl_ops = अणु
	.s_ctrl = coda_s_ctrl,
पूर्ण;

अटल व्योम coda_encode_ctrls(काष्ठा coda_ctx *ctx)
अणु
	पूर्णांक max_gop_size = (ctx->dev->devtype->product == CODA_DX6) ? 60 : 99;

	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE, 0, 32767000, 1000, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_GOP_SIZE, 0, max_gop_size, 1, 16);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP, 0, 51, 1, 25);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP, 0, 51, 1, 25);
	अगर (ctx->dev->devtype->product != CODA_960) अणु
		v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_MIN_QP, 0, 51, 1, 12);
	पूर्ण
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_MAX_QP, 0, 51, 1, 51);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA, -6, 6, 1, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA, -6, 6, 1, 0);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE,
		V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY,
		0x0, V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_CONSTRAINED_INTRA_PREDICTION, 0, 1, 1,
		0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_CHROMA_QP_INDEX_OFFSET, -12, 12, 1, 0);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE, 0x0,
		V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE);
	अगर (ctx->dev->devtype->product == CODA_HX4 ||
	    ctx->dev->devtype->product == CODA_7541) अणु
		v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			V4L2_MPEG_VIDEO_H264_LEVEL_3_1,
			~((1 << V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_1)),
			V4L2_MPEG_VIDEO_H264_LEVEL_3_1);
	पूर्ण
	अगर (ctx->dev->devtype->product == CODA_960) अणु
		v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			V4L2_MPEG_VIDEO_H264_LEVEL_4_0,
			~((1 << V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_1) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_2) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_4_0)),
			V4L2_MPEG_VIDEO_H264_LEVEL_4_0);
	पूर्ण
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP, 1, 31, 1, 2);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP, 1, 31, 1, 2);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता,
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE, 0x0,
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE);
	अगर (ctx->dev->devtype->product == CODA_HX4 ||
	    ctx->dev->devtype->product == CODA_7541 ||
	    ctx->dev->devtype->product == CODA_960) अणु
		v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
			V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
			~(1 << V4L2_MPEG_VIDEO_MPEG4_LEVEL_5),
			V4L2_MPEG_VIDEO_MPEG4_LEVEL_5);
	पूर्ण
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE,
		V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES, 0x0,
		V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB, 1, 0x3fffffff, 1, 1);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES, 1, 0x3fffffff, 1,
		500);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEADER_MODE,
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
		(1 << V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE),
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB, 0,
		1920 * 1088 / 256, 1, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VBV_DELAY, 0, 0x7fff, 1, 0);
	/*
	 * The maximum VBV size value is 0x7fffffff bits,
	 * one bit less than 262144 KiB
	 */
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VBV_SIZE, 0, 262144, 1, 0);
पूर्ण

अटल व्योम coda_jpeg_encode_ctrls(काष्ठा coda_ctx *ctx)
अणु
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_JPEG_COMPRESSION_QUALITY, 5, 100, 1, 50);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_JPEG_RESTART_INTERVAL, 0, 100, 1, 0);
पूर्ण

अटल व्योम coda_decode_ctrls(काष्ठा coda_ctx *ctx)
अणु
	u8 max;

	ctx->h264_profile_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
		~((1 << V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_HIGH)),
		V4L2_MPEG_VIDEO_H264_PROखाता_HIGH);
	अगर (ctx->h264_profile_ctrl)
		ctx->h264_profile_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	अगर (ctx->dev->devtype->product == CODA_HX4 ||
	    ctx->dev->devtype->product == CODA_7541)
		max = V4L2_MPEG_VIDEO_H264_LEVEL_4_0;
	अन्यथा अगर (ctx->dev->devtype->product == CODA_960)
		max = V4L2_MPEG_VIDEO_H264_LEVEL_4_1;
	अन्यथा
		वापस;
	ctx->h264_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_H264_LEVEL, max, 0, max);
	अगर (ctx->h264_level_ctrl)
		ctx->h264_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg2_profile_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG2_PROखाता,
		V4L2_MPEG_VIDEO_MPEG2_PROखाता_HIGH, 0,
		V4L2_MPEG_VIDEO_MPEG2_PROखाता_HIGH);
	अगर (ctx->mpeg2_profile_ctrl)
		ctx->mpeg2_profile_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg2_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL,
		V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH, 0,
		V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH);
	अगर (ctx->mpeg2_level_ctrl)
		ctx->mpeg2_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg4_profile_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता,
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_CODING_EFFICIENCY, 0,
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_CODING_EFFICIENCY);
	अगर (ctx->mpeg4_profile_ctrl)
		ctx->mpeg4_profile_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg4_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
		V4L2_MPEG_VIDEO_MPEG4_LEVEL_5, 0,
		V4L2_MPEG_VIDEO_MPEG4_LEVEL_5);
	अगर (ctx->mpeg4_level_ctrl)
		ctx->mpeg4_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_config coda_mb_err_cnt_ctrl_config = अणु
	.id	= V4L2_CID_CODA_MB_ERR_CNT,
	.name	= "Macroblocks Error Count",
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.min	= 0,
	.max	= 0x7fffffff,
	.step	= 1,
पूर्ण;

अटल पूर्णांक coda_ctrls_setup(काष्ठा coda_ctx *ctx)
अणु
	v4l2_ctrl_handler_init(&ctx->ctrls, 2);

	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_VFLIP, 0, 1, 1, 0);
	अगर (ctx->inst_type == CODA_INST_ENCODER) अणु
		v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
				  V4L2_CID_MIN_BUFFERS_FOR_OUTPUT,
				  1, 1, 1, 1);
		अगर (ctx->cvd->dst_क्रमmats[0] == V4L2_PIX_FMT_JPEG)
			coda_jpeg_encode_ctrls(ctx);
		अन्यथा
			coda_encode_ctrls(ctx);
	पूर्ण अन्यथा अणु
		v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
				  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE,
				  1, 1, 1, 1);
		अगर (ctx->cvd->src_क्रमmats[0] == V4L2_PIX_FMT_H264)
			coda_decode_ctrls(ctx);

		ctx->mb_err_cnt_ctrl = v4l2_ctrl_new_custom(&ctx->ctrls,
						&coda_mb_err_cnt_ctrl_config,
						शून्य);
		अगर (ctx->mb_err_cnt_ctrl)
			ctx->mb_err_cnt_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	पूर्ण

	अगर (ctx->ctrls.error) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			"control initialization error (%d)",
			ctx->ctrls.error);
		वापस -EINVAL;
	पूर्ण

	वापस v4l2_ctrl_handler_setup(&ctx->ctrls);
पूर्ण

अटल पूर्णांक coda_queue_init(काष्ठा coda_ctx *ctx, काष्ठा vb2_queue *vq)
अणु
	vq->drv_priv = ctx;
	vq->ops = &coda_qops;
	vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	vq->lock = &ctx->dev->dev_mutex;
	/* One way to indicate end-of-stream क्रम coda is to set the
	 * bytesused == 0. However by शेष videobuf2 handles bytesused
	 * equal to 0 as a special हाल and changes its value to the size
	 * of the buffer. Set the allow_zero_bytesused flag, so
	 * that videobuf2 will keep the value of bytesused पूर्णांकact.
	 */
	vq->allow_zero_bytesused = 1;
	/*
	 * We might be fine with no buffers on some of the queues, but that
	 * would need to be reflected in job_पढ़ोy(). Currently we expect all
	 * queues to have at least one buffer queued.
	 */
	vq->min_buffers_needed = 1;
	vq->dev = ctx->dev->dev;

	वापस vb2_queue_init(vq);
पूर्ण

पूर्णांक coda_encoder_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			    काष्ठा vb2_queue *dst_vq)
अणु
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	src_vq->mem_ops = &vb2_dma_contig_memops;

	ret = coda_queue_init(priv, src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	dst_vq->mem_ops = &vb2_dma_contig_memops;

	वापस coda_queue_init(priv, dst_vq);
पूर्ण

पूर्णांक coda_decoder_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			    काष्ठा vb2_queue *dst_vq)
अणु
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_DMABUF | VB2_MMAP | VB2_USERPTR;
	src_vq->mem_ops = &vb2_vदो_स्मृति_memops;

	ret = coda_queue_init(priv, src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	dst_vq->dma_attrs = DMA_ATTR_NO_KERNEL_MAPPING;
	dst_vq->mem_ops = &vb2_dma_contig_memops;

	वापस coda_queue_init(priv, dst_vq);
पूर्ण

/*
 * File operations
 */

अटल पूर्णांक coda_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा coda_dev *dev = video_get_drvdata(vdev);
	काष्ठा coda_ctx *ctx;
	अचिन्हित पूर्णांक max = ~0;
	अक्षर *name;
	पूर्णांक ret;
	पूर्णांक idx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (dev->devtype->product == CODA_DX6)
		max = CODADX6_MAX_INSTANCES - 1;
	idx = ida_alloc_max(&dev->ida, max, GFP_KERNEL);
	अगर (idx < 0) अणु
		ret = idx;
		जाओ err_coda_max;
	पूर्ण

	name = kaप्र_लिखो(GFP_KERNEL, "context%d", idx);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ err_coda_name_init;
	पूर्ण

	ctx->debugfs_entry = debugfs_create_dir(name, dev->debugfs_root);
	kमुक्त(name);

	ctx->cvd = to_coda_video_device(vdev);
	ctx->inst_type = ctx->cvd->type;
	ctx->ops = ctx->cvd->ops;
	ctx->use_bit = !ctx->cvd->direct;
	init_completion(&ctx->completion);
	INIT_WORK(&ctx->pic_run_work, coda_pic_run_work);
	अगर (ctx->ops->seq_init_work)
		INIT_WORK(&ctx->seq_init_work, ctx->ops->seq_init_work);
	अगर (ctx->ops->seq_end_work)
		INIT_WORK(&ctx->seq_end_work, ctx->ops->seq_end_work);
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);
	ctx->dev = dev;
	ctx->idx = idx;

	coda_dbg(1, ctx, "open instance (%p)\n", ctx);

	चयन (dev->devtype->product) अणु
	हाल CODA_960:
		/*
		 * Enabling the BWB when decoding can hang the firmware with
		 * certain streams. The issue was tracked as ENGR00293425 by
		 * Freescale. As a workaround, disable BWB क्रम all decoders.
		 * The enable_bwb module parameter allows to override this.
		 */
		अगर (enable_bwb || ctx->inst_type == CODA_INST_ENCODER)
			ctx->frame_mem_ctrl = CODA9_FRAME_ENABLE_BWB;
		fallthrough;
	हाल CODA_HX4:
	हाल CODA_7541:
		ctx->reg_idx = 0;
		अवरोध;
	शेष:
		ctx->reg_idx = idx;
	पूर्ण
	अगर (ctx->dev->vकरोa && !disable_vकरोa) अणु
		ctx->vकरोa = vकरोa_context_create(dev->vकरोa);
		अगर (!ctx->vकरोa)
			v4l2_warn(&dev->v4l2_dev,
				  "Failed to create vdoa context: not using vdoa");
	पूर्ण
	ctx->use_vकरोa = false;

	/* Power up and upload firmware अगर necessary */
	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "failed to power up: %d\n", ret);
		जाओ err_pm_get;
	पूर्ण

	ret = clk_prepare_enable(dev->clk_per);
	अगर (ret)
		जाओ err_pm_get;

	ret = clk_prepare_enable(dev->clk_ahb);
	अगर (ret)
		जाओ err_clk_ahb;

	set_शेष_params(ctx);
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx,
					    ctx->ops->queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_err(&dev->v4l2_dev, "%s return error (%d)\n",
			 __func__, ret);
		जाओ err_ctx_init;
	पूर्ण

	ret = coda_ctrls_setup(ctx);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "failed to setup coda controls\n");
		जाओ err_ctrls_setup;
	पूर्ण

	ctx->fh.ctrl_handler = &ctx->ctrls;

	mutex_init(&ctx->bitstream_mutex);
	mutex_init(&ctx->buffer_mutex);
	mutex_init(&ctx->wakeup_mutex);
	INIT_LIST_HEAD(&ctx->buffer_meta_list);
	spin_lock_init(&ctx->buffer_meta_lock);

	वापस 0;

err_ctrls_setup:
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
err_ctx_init:
	clk_disable_unprepare(dev->clk_ahb);
err_clk_ahb:
	clk_disable_unprepare(dev->clk_per);
err_pm_get:
	pm_runसमय_put_sync(dev->dev);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
err_coda_name_init:
	ida_मुक्त(&dev->ida, ctx->idx);
err_coda_max:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक coda_release(काष्ठा file *file)
अणु
	काष्ठा coda_dev *dev = video_drvdata(file);
	काष्ठा coda_ctx *ctx = fh_to_ctx(file->निजी_data);

	coda_dbg(1, ctx, "release instance (%p)\n", ctx);

	अगर (ctx->inst_type == CODA_INST_DECODER && ctx->use_bit)
		coda_bit_stream_end_flag(ctx);

	/* If this instance is running, call .job_पात and रुको क्रम it to end */
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	अगर (ctx->vकरोa)
		vकरोa_context_destroy(ctx->vकरोa);

	/* In हाल the instance was not running, we still need to call SEQ_END */
	अगर (ctx->ops->seq_end_work) अणु
		queue_work(dev->workqueue, &ctx->seq_end_work);
		flush_work(&ctx->seq_end_work);
	पूर्ण

	अगर (ctx->dev->devtype->product == CODA_DX6)
		coda_मुक्त_aux_buf(dev, &ctx->workbuf);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrls);
	clk_disable_unprepare(dev->clk_ahb);
	clk_disable_unprepare(dev->clk_per);
	pm_runसमय_put_sync(dev->dev);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	ida_मुक्त(&dev->ida, ctx->idx);
	अगर (ctx->ops->release)
		ctx->ops->release(ctx);
	debugfs_हटाओ_recursive(ctx->debugfs_entry);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations coda_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= coda_खोलो,
	.release	= coda_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक coda_hw_init(काष्ठा coda_dev *dev)
अणु
	u32 data;
	u16 *p;
	पूर्णांक i, ret;

	ret = clk_prepare_enable(dev->clk_per);
	अगर (ret)
		जाओ err_clk_per;

	ret = clk_prepare_enable(dev->clk_ahb);
	अगर (ret)
		जाओ err_clk_ahb;

	reset_control_reset(dev->rstc);

	/*
	 * Copy the first CODA_ISRAM_SIZE in the पूर्णांकernal SRAM.
	 * The 16-bit अक्षरs in the code buffer are in memory access
	 * order, re-sort them to CODA order क्रम रेजिस्टर करोwnload.
	 * Data in this SRAM survives a reboot.
	 */
	p = (u16 *)dev->codebuf.vaddr;
	अगर (dev->devtype->product == CODA_DX6) अणु
		क्रम (i = 0; i < (CODA_ISRAM_SIZE / 2); i++)  अणु
			data = CODA_DOWN_ADDRESS_SET(i) |
				CODA_DOWN_DATA_SET(p[i ^ 1]);
			coda_ग_लिखो(dev, data, CODA_REG_BIT_CODE_DOWN);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (CODA_ISRAM_SIZE / 2); i++) अणु
			data = CODA_DOWN_ADDRESS_SET(i) |
				CODA_DOWN_DATA_SET(p[round_करोwn(i, 4) +
							3 - (i % 4)]);
			coda_ग_लिखो(dev, data, CODA_REG_BIT_CODE_DOWN);
		पूर्ण
	पूर्ण

	/* Clear रेजिस्टरs */
	क्रम (i = 0; i < 64; i++)
		coda_ग_लिखो(dev, 0, CODA_REG_BIT_CODE_BUF_ADDR + i * 4);

	/* Tell the BIT where to find everything it needs */
	अगर (dev->devtype->product == CODA_960 ||
	    dev->devtype->product == CODA_7541 ||
	    dev->devtype->product == CODA_HX4) अणु
		coda_ग_लिखो(dev, dev->tempbuf.paddr,
				CODA_REG_BIT_TEMP_BUF_ADDR);
		coda_ग_लिखो(dev, 0, CODA_REG_BIT_BIT_STREAM_PARAM);
	पूर्ण अन्यथा अणु
		coda_ग_लिखो(dev, dev->workbuf.paddr,
			      CODA_REG_BIT_WORK_BUF_ADDR);
	पूर्ण
	coda_ग_लिखो(dev, dev->codebuf.paddr,
		      CODA_REG_BIT_CODE_BUF_ADDR);
	coda_ग_लिखो(dev, 0, CODA_REG_BIT_CODE_RUN);

	/* Set शेष values */
	चयन (dev->devtype->product) अणु
	हाल CODA_DX6:
		coda_ग_लिखो(dev, CODADX6_STREAM_BUF_PIC_FLUSH,
			   CODA_REG_BIT_STREAM_CTRL);
		अवरोध;
	शेष:
		coda_ग_लिखो(dev, CODA7_STREAM_BUF_PIC_FLUSH,
			   CODA_REG_BIT_STREAM_CTRL);
	पूर्ण
	अगर (dev->devtype->product == CODA_960)
		coda_ग_लिखो(dev, CODA9_FRAME_ENABLE_BWB,
				CODA_REG_BIT_FRAME_MEM_CTRL);
	अन्यथा
		coda_ग_लिखो(dev, 0, CODA_REG_BIT_FRAME_MEM_CTRL);

	अगर (dev->devtype->product != CODA_DX6)
		coda_ग_लिखो(dev, 0, CODA7_REG_BIT_AXI_SRAM_USE);

	coda_ग_लिखो(dev, CODA_INT_INTERRUPT_ENABLE,
		      CODA_REG_BIT_INT_ENABLE);

	/* Reset VPU and start processor */
	data = coda_पढ़ो(dev, CODA_REG_BIT_CODE_RESET);
	data |= CODA_REG_RESET_ENABLE;
	coda_ग_लिखो(dev, data, CODA_REG_BIT_CODE_RESET);
	udelay(10);
	data &= ~CODA_REG_RESET_ENABLE;
	coda_ग_लिखो(dev, data, CODA_REG_BIT_CODE_RESET);
	coda_ग_लिखो(dev, CODA_REG_RUN_ENABLE, CODA_REG_BIT_CODE_RUN);

	clk_disable_unprepare(dev->clk_ahb);
	clk_disable_unprepare(dev->clk_per);

	वापस 0;

err_clk_ahb:
	clk_disable_unprepare(dev->clk_per);
err_clk_per:
	वापस ret;
पूर्ण

अटल पूर्णांक coda_रेजिस्टर_device(काष्ठा coda_dev *dev, पूर्णांक i)
अणु
	काष्ठा video_device *vfd = &dev->vfd[i];
	स्थिर अक्षर *name;
	पूर्णांक ret;

	अगर (i >= dev->devtype->num_vdevs)
		वापस -EINVAL;
	name = dev->devtype->vdevs[i]->name;

	strscpy(vfd->name, dev->devtype->vdevs[i]->name, माप(vfd->name));
	vfd->fops	= &coda_fops;
	vfd->ioctl_ops	= &coda_ioctl_ops;
	vfd->release	= video_device_release_empty;
	vfd->lock	= &dev->dev_mutex;
	vfd->v4l2_dev	= &dev->v4l2_dev;
	vfd->vfl_dir	= VFL_सूची_M2M;
	vfd->device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING;
	video_set_drvdata(vfd, dev);

	/* Not applicable, use the selection API instead */
	v4l2_disable_ioctl(vfd, VIDIOC_CROPCAP);
	v4l2_disable_ioctl(vfd, VIDIOC_G_CROP);
	v4l2_disable_ioctl(vfd, VIDIOC_S_CROP);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (!ret)
		v4l2_info(&dev->v4l2_dev, "%s registered as %s\n",
			  name, video_device_node_name(vfd));
	वापस ret;
पूर्ण

अटल व्योम coda_copy_firmware(काष्ठा coda_dev *dev, स्थिर u8 * स्थिर buf,
			       माप_प्रकार size)
अणु
	u32 *src = (u32 *)buf;

	/* Check अगर the firmware has a 16-byte Freescale header, skip it */
	अगर (buf[0] == 'M' && buf[1] == 'X')
		src += 4;
	/*
	 * Check whether the firmware is in native order or pre-reordered क्रम
	 * memory access. The first inकाष्ठाion opcode always is 0xe40e.
	 */
	अगर (__le16_to_cpup((__le16 *)src) == 0xe40e) अणु
		u32 *dst = dev->codebuf.vaddr;
		पूर्णांक i;

		/* Firmware in native order, reorder जबतक copying */
		अगर (dev->devtype->product == CODA_DX6) अणु
			क्रम (i = 0; i < (size - 16) / 4; i++)
				dst[i] = (src[i] << 16) | (src[i] >> 16);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < (size - 16) / 4; i += 2) अणु
				dst[i] = (src[i + 1] << 16) | (src[i + 1] >> 16);
				dst[i + 1] = (src[i] << 16) | (src[i] >> 16);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Copy the alपढ़ोy reordered firmware image */
		स_नकल(dev->codebuf.vaddr, src, size);
	पूर्ण
पूर्ण

अटल व्योम coda_fw_callback(स्थिर काष्ठा firmware *fw, व्योम *context);

अटल पूर्णांक coda_firmware_request(काष्ठा coda_dev *dev)
अणु
	अक्षर *fw;

	अगर (dev->firmware >= ARRAY_SIZE(dev->devtype->firmware))
		वापस -EINVAL;

	fw = dev->devtype->firmware[dev->firmware];

	dev_dbg(dev->dev, "requesting firmware '%s' for %s\n", fw,
		coda_product_name(dev->devtype->product));

	वापस request_firmware_noरुको(THIS_MODULE, true, fw, dev->dev,
				       GFP_KERNEL, dev, coda_fw_callback);
पूर्ण

अटल व्योम coda_fw_callback(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा coda_dev *dev = context;
	पूर्णांक i, ret;

	अगर (!fw) अणु
		dev->firmware++;
		ret = coda_firmware_request(dev);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev, "firmware request failed\n");
			जाओ put_pm;
		पूर्ण
		वापस;
	पूर्ण
	अगर (dev->firmware > 0) अणु
		/*
		 * Since we can't suppress warnings क्रम failed asynchronous
		 * firmware requests, report that the fallback firmware was
		 * found.
		 */
		dev_info(dev->dev, "Using fallback firmware %s\n",
			 dev->devtype->firmware[dev->firmware]);
	पूर्ण

	/* allocate auxiliary per-device code buffer क्रम the BIT processor */
	ret = coda_alloc_aux_buf(dev, &dev->codebuf, fw->size, "codebuf",
				 dev->debugfs_root);
	अगर (ret < 0)
		जाओ put_pm;

	coda_copy_firmware(dev, fw->data, fw->size);
	release_firmware(fw);

	ret = coda_hw_init(dev);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "HW initialization failed\n");
		जाओ put_pm;
	पूर्ण

	ret = coda_check_firmware(dev);
	अगर (ret < 0)
		जाओ put_pm;

	dev->m2m_dev = v4l2_m2m_init(&coda_m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem device\n");
		जाओ put_pm;
	पूर्ण

	क्रम (i = 0; i < dev->devtype->num_vdevs; i++) अणु
		ret = coda_रेजिस्टर_device(dev, i);
		अगर (ret) अणु
			v4l2_err(&dev->v4l2_dev,
				 "Failed to register %s video device: %d\n",
				 dev->devtype->vdevs[i]->name, ret);
			जाओ rel_vfd;
		पूर्ण
	पूर्ण

	pm_runसमय_put_sync(dev->dev);
	वापस;

rel_vfd:
	जबतक (--i >= 0)
		video_unरेजिस्टर_device(&dev->vfd[i]);
	v4l2_m2m_release(dev->m2m_dev);
put_pm:
	pm_runसमय_put_sync(dev->dev);
पूर्ण

क्रमागत coda_platक्रमm अणु
	CODA_IMX27,
	CODA_IMX51,
	CODA_IMX53,
	CODA_IMX6Q,
	CODA_IMX6DL,
पूर्ण;

अटल स्थिर काष्ठा coda_devtype coda_devdata[] = अणु
	[CODA_IMX27] = अणु
		.firmware     = अणु
			"vpu_fw_imx27_TO2.bin",
			"vpu/vpu_fw_imx27_TO2.bin",
			"v4l-codadx6-imx27.bin"
		पूर्ण,
		.product      = CODA_DX6,
		.codecs       = codadx6_codecs,
		.num_codecs   = ARRAY_SIZE(codadx6_codecs),
		.vdevs        = codadx6_video_devices,
		.num_vdevs    = ARRAY_SIZE(codadx6_video_devices),
		.workbuf_size = 288 * 1024 + FMO_SLICE_SAVE_BUF_SIZE * 8 * 1024,
		.iram_size    = 0xb000,
	पूर्ण,
	[CODA_IMX51] = अणु
		.firmware     = अणु
			"vpu_fw_imx51.bin",
			"vpu/vpu_fw_imx51.bin",
			"v4l-codahx4-imx51.bin"
		पूर्ण,
		.product      = CODA_HX4,
		.codecs       = codahx4_codecs,
		.num_codecs   = ARRAY_SIZE(codahx4_codecs),
		.vdevs        = codahx4_video_devices,
		.num_vdevs    = ARRAY_SIZE(codahx4_video_devices),
		.workbuf_size = 128 * 1024,
		.tempbuf_size = 304 * 1024,
		.iram_size    = 0x14000,
	पूर्ण,
	[CODA_IMX53] = अणु
		.firmware     = अणु
			"vpu_fw_imx53.bin",
			"vpu/vpu_fw_imx53.bin",
			"v4l-coda7541-imx53.bin"
		पूर्ण,
		.product      = CODA_7541,
		.codecs       = coda7_codecs,
		.num_codecs   = ARRAY_SIZE(coda7_codecs),
		.vdevs        = coda7_video_devices,
		.num_vdevs    = ARRAY_SIZE(coda7_video_devices),
		.workbuf_size = 128 * 1024,
		.tempbuf_size = 304 * 1024,
		.iram_size    = 0x14000,
	पूर्ण,
	[CODA_IMX6Q] = अणु
		.firmware     = अणु
			"vpu_fw_imx6q.bin",
			"vpu/vpu_fw_imx6q.bin",
			"v4l-coda960-imx6q.bin"
		पूर्ण,
		.product      = CODA_960,
		.codecs       = coda9_codecs,
		.num_codecs   = ARRAY_SIZE(coda9_codecs),
		.vdevs        = coda9_video_devices,
		.num_vdevs    = ARRAY_SIZE(coda9_video_devices),
		.workbuf_size = 80 * 1024,
		.tempbuf_size = 204 * 1024,
		.iram_size    = 0x21000,
	पूर्ण,
	[CODA_IMX6DL] = अणु
		.firmware     = अणु
			"vpu_fw_imx6d.bin",
			"vpu/vpu_fw_imx6d.bin",
			"v4l-coda960-imx6dl.bin"
		पूर्ण,
		.product      = CODA_960,
		.codecs       = coda9_codecs,
		.num_codecs   = ARRAY_SIZE(coda9_codecs),
		.vdevs        = coda9_video_devices,
		.num_vdevs    = ARRAY_SIZE(coda9_video_devices),
		.workbuf_size = 80 * 1024,
		.tempbuf_size = 204 * 1024,
		.iram_size    = 0x1f000, /* leave 4k क्रम suspend code */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id coda_dt_ids[] = अणु
	अणु .compatible = "fsl,imx27-vpu", .data = &coda_devdata[CODA_IMX27] पूर्ण,
	अणु .compatible = "fsl,imx51-vpu", .data = &coda_devdata[CODA_IMX51] पूर्ण,
	अणु .compatible = "fsl,imx53-vpu", .data = &coda_devdata[CODA_IMX53] पूर्ण,
	अणु .compatible = "fsl,imx6q-vpu", .data = &coda_devdata[CODA_IMX6Q] पूर्ण,
	अणु .compatible = "fsl,imx6dl-vpu", .data = &coda_devdata[CODA_IMX6DL] पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, coda_dt_ids);

अटल पूर्णांक coda_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा gen_pool *pool;
	काष्ठा coda_dev *dev;
	पूर्णांक ret, irq;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->devtype = of_device_get_match_data(&pdev->dev);

	dev->dev = &pdev->dev;
	dev->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(dev->clk_per)) अणु
		dev_err(&pdev->dev, "Could not get per clock\n");
		वापस PTR_ERR(dev->clk_per);
	पूर्ण

	dev->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(dev->clk_ahb)) अणु
		dev_err(&pdev->dev, "Could not get ahb clock\n");
		वापस PTR_ERR(dev->clk_ahb);
	पूर्ण

	/* Get  memory क्रम physical रेजिस्टरs */
	dev->regs_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->regs_base))
		वापस PTR_ERR(dev->regs_base);

	/* IRQ */
	irq = platक्रमm_get_irq_byname(pdev, "bit");
	अगर (irq < 0)
		irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, coda_irq_handler, 0,
			       CODA_NAME "-video", dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request irq: %d\n", ret);
		वापस ret;
	पूर्ण

	/* JPEG IRQ */
	अगर (dev->devtype->product == CODA_960) अणु
		irq = platक्रमm_get_irq_byname(pdev, "jpeg");
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						coda9_jpeg_irq_handler,
						IRQF_ONESHOT, CODA_NAME "-jpeg",
						dev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to request jpeg irq\n");
			वापस ret;
		पूर्ण
	पूर्ण

	dev->rstc = devm_reset_control_get_optional_exclusive(&pdev->dev,
							      शून्य);
	अगर (IS_ERR(dev->rstc)) अणु
		ret = PTR_ERR(dev->rstc);
		dev_err(&pdev->dev, "failed get reset control: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Get IRAM pool from device tree */
	pool = of_gen_pool_get(np, "iram", 0);
	अगर (!pool) अणु
		dev_err(&pdev->dev, "iram pool not available\n");
		वापस -ENOMEM;
	पूर्ण
	dev->iram_pool = pool;

	/* Get vकरोa_data अगर supported by the platक्रमm */
	dev->vकरोa = coda_get_vकरोa_data();
	अगर (PTR_ERR(dev->vकरोa) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		वापस ret;

	ratelimit_शेष_init(&dev->mb_err_rs);
	mutex_init(&dev->dev_mutex);
	mutex_init(&dev->coda_mutex);
	ida_init(&dev->ida);

	dev->debugfs_root = debugfs_create_dir("coda", शून्य);

	/* allocate auxiliary per-device buffers क्रम the BIT processor */
	अगर (dev->devtype->product == CODA_DX6) अणु
		ret = coda_alloc_aux_buf(dev, &dev->workbuf,
					 dev->devtype->workbuf_size, "workbuf",
					 dev->debugfs_root);
		अगर (ret < 0)
			जाओ err_v4l2_रेजिस्टर;
	पूर्ण

	अगर (dev->devtype->tempbuf_size) अणु
		ret = coda_alloc_aux_buf(dev, &dev->tempbuf,
					 dev->devtype->tempbuf_size, "tempbuf",
					 dev->debugfs_root);
		अगर (ret < 0)
			जाओ err_v4l2_रेजिस्टर;
	पूर्ण

	dev->iram.size = dev->devtype->iram_size;
	dev->iram.vaddr = gen_pool_dma_alloc(dev->iram_pool, dev->iram.size,
					     &dev->iram.paddr);
	अगर (!dev->iram.vaddr) अणु
		dev_warn(&pdev->dev, "unable to alloc iram\n");
	पूर्ण अन्यथा अणु
		स_रखो(dev->iram.vaddr, 0, dev->iram.size);
		dev->iram.blob.data = dev->iram.vaddr;
		dev->iram.blob.size = dev->iram.size;
		dev->iram.dentry = debugfs_create_blob("iram", 0644,
						       dev->debugfs_root,
						       &dev->iram.blob);
	पूर्ण

	dev->workqueue = alloc_workqueue("coda", WQ_UNBOUND | WQ_MEM_RECLAIM, 1);
	अगर (!dev->workqueue) अणु
		dev_err(&pdev->dev, "unable to alloc workqueue\n");
		ret = -ENOMEM;
		जाओ err_v4l2_रेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);

	/*
	 * Start activated so we can directly call coda_hw_init in
	 * coda_fw_callback regardless of whether CONFIG_PM is
	 * enabled or whether the device is associated with a PM करोमुख्य.
	 */
	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = coda_firmware_request(dev);
	अगर (ret)
		जाओ err_alloc_workqueue;
	वापस 0;

err_alloc_workqueue:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	destroy_workqueue(dev->workqueue);
err_v4l2_रेजिस्टर:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक coda_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा coda_dev *dev = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dev->vfd); i++) अणु
		अगर (video_get_drvdata(&dev->vfd[i]))
			video_unरेजिस्टर_device(&dev->vfd[i]);
	पूर्ण
	अगर (dev->m2m_dev)
		v4l2_m2m_release(dev->m2m_dev);
	pm_runसमय_disable(&pdev->dev);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	destroy_workqueue(dev->workqueue);
	अगर (dev->iram.vaddr)
		gen_pool_मुक्त(dev->iram_pool, (अचिन्हित दीर्घ)dev->iram.vaddr,
			      dev->iram.size);
	coda_मुक्त_aux_buf(dev, &dev->codebuf);
	coda_मुक्त_aux_buf(dev, &dev->tempbuf);
	coda_मुक्त_aux_buf(dev, &dev->workbuf);
	debugfs_हटाओ_recursive(dev->debugfs_root);
	ida_destroy(&dev->ida);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक coda_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा coda_dev *cdev = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (dev->pm_करोमुख्य && cdev->codebuf.vaddr) अणु
		ret = coda_hw_init(cdev);
		अगर (ret)
			v4l2_err(&cdev->v4l2_dev, "HW initialization failed\n");
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops coda_pm_ops = अणु
	SET_RUNTIME_PM_OPS(शून्य, coda_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver coda_driver = अणु
	.probe	= coda_probe,
	.हटाओ	= coda_हटाओ,
	.driver	= अणु
		.name	= CODA_NAME,
		.of_match_table = coda_dt_ids,
		.pm	= &coda_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(coda_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Javier Martin <javier.martin@vista-silicon.com>");
MODULE_DESCRIPTION("Coda multi-standard codec V4L2 driver");
