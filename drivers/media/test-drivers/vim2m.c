<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * A भव v4l2-mem2mem example device.
 *
 * This is a भव device driver क्रम testing mem-to-mem videobuf framework.
 * It simulates a device that uses memory buffers क्रम both source and
 * destination, processes the data and issues an "irq" (simulated by a delayed
 * workqueue).
 * The device is capable of multi-instance, multi-buffer-per-transaction
 * operation (via the mem2mem framework).
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version
 */
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

MODULE_DESCRIPTION("Virtual device for mem2mem framework testing");
MODULE_AUTHOR("Pawel Osciak, <pawel@osciak.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
MODULE_ALIAS("mem2mem_testdev");

अटल अचिन्हित पूर्णांक debug;
module_param(debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level");

/* Default transaction समय in msec */
अटल अचिन्हित पूर्णांक शेष_transसमय = 40; /* Max 25 fps */
module_param(शेष_transसमय, uपूर्णांक, 0644);
MODULE_PARM_DESC(शेष_transसमय, "default transaction time in ms");

#घोषणा MIN_W 32
#घोषणा MIN_H 32
#घोषणा MAX_W 640
#घोषणा MAX_H 480

/* Pixel alignment क्रम non-bayer क्रमmats */
#घोषणा WIDTH_ALIGN 2
#घोषणा HEIGHT_ALIGN 1

/* Pixel alignment क्रम bayer क्रमmats */
#घोषणा BAYER_WIDTH_ALIGN  2
#घोषणा BAYER_HEIGHT_ALIGN 2

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा MEM2MEM_CAPTURE	BIT(0)
#घोषणा MEM2MEM_OUTPUT	BIT(1)

#घोषणा MEM2MEM_NAME		"vim2m"

/* Per queue */
#घोषणा MEM2MEM_DEF_NUM_BUFS	VIDEO_MAX_FRAME
/* In bytes, per queue */
#घोषणा MEM2MEM_VID_MEM_LIMIT	(16 * 1024 * 1024)

/* Flags that indicate processing mode */
#घोषणा MEM2MEM_HFLIP	BIT(0)
#घोषणा MEM2MEM_VFLIP	BIT(1)

#घोषणा dprपूर्णांकk(dev, lvl, fmt, arg...) \
	v4l2_dbg(lvl, debug, &(dev)->v4l2_dev, "%s: " fmt, __func__, ## arg)

अटल व्योम vim2m_dev_release(काष्ठा device *dev)
अणुपूर्ण

अटल काष्ठा platक्रमm_device vim2m_pdev = अणु
	.name		= MEM2MEM_NAME,
	.dev.release	= vim2m_dev_release,
पूर्ण;

काष्ठा vim2m_fmt अणु
	u32	fourcc;
	पूर्णांक	depth;
	/* Types the क्रमmat can be used क्रम */
	u32     types;
पूर्ण;

अटल काष्ठा vim2m_fmt क्रमmats[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB565,  /* rrrrrggg gggbbbbb */
		.depth	= 16,
		.types  = MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB565X, /* gggbbbbb rrrrrggg */
		.depth	= 16,
		.types  = MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB24,
		.depth	= 24,
		.types  = MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGR24,
		.depth	= 24,
		.types  = MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_YUYV,
		.depth	= 16,
		.types  = MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_SBGGR8,
		.depth	= 8,
		.types  = MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_SGBRG8,
		.depth	= 8,
		.types  = MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_SGRBG8,
		.depth	= 8,
		.types  = MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_SRGGB8,
		.depth	= 8,
		.types  = MEM2MEM_CAPTURE,
	पूर्ण,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

/* Per-queue, driver-specअगरic निजी data */
काष्ठा vim2m_q_data अणु
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		sizeimage;
	अचिन्हित पूर्णांक		sequence;
	काष्ठा vim2m_fmt	*fmt;
पूर्ण;

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

#घोषणा V4L2_CID_TRANS_TIME_MSEC	(V4L2_CID_USER_BASE + 0x1000)
#घोषणा V4L2_CID_TRANS_NUM_BUFS		(V4L2_CID_USER_BASE + 0x1001)

अटल काष्ठा vim2m_fmt *find_क्रमmat(u32 fourcc)
अणु
	काष्ठा vim2m_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NUM_FORMATS; k++) अणु
		fmt = &क्रमmats[k];
		अगर (fmt->fourcc == fourcc)
			अवरोध;
	पूर्ण

	अगर (k == NUM_FORMATS)
		वापस शून्य;

	वापस &क्रमmats[k];
पूर्ण

अटल व्योम get_alignment(u32 fourcc,
			  अचिन्हित पूर्णांक *walign, अचिन्हित पूर्णांक *halign)
अणु
	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		*walign = BAYER_WIDTH_ALIGN;
		*halign = BAYER_HEIGHT_ALIGN;
		वापस;
	शेष:
		*walign = WIDTH_ALIGN;
		*halign = HEIGHT_ALIGN;
		वापस;
	पूर्ण
पूर्ण

काष्ठा vim2m_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device	mdev;
#पूर्ण_अगर

	atomic_t		num_inst;
	काष्ठा mutex		dev_mutex;

	काष्ठा v4l2_m2m_dev	*m2m_dev;
पूर्ण;

काष्ठा vim2m_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा vim2m_dev	*dev;

	काष्ठा v4l2_ctrl_handler hdl;

	/* Processed buffers in this transaction */
	u8			num_processed;

	/* Transaction length (i.e. how many buffers per transaction) */
	u32			translen;
	/* Transaction समय (i.e. simulated processing समय) in milliseconds */
	u32			transसमय;

	काष्ठा mutex		vb_mutex;
	काष्ठा delayed_work	work_run;

	/* Abort requested by m2m */
	पूर्णांक			पातing;

	/* Processing mode */
	पूर्णांक			mode;

	क्रमागत v4l2_colorspace	colorspace;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_xfer_func	xfer_func;
	क्रमागत v4l2_quantization	quant;

	/* Source and destination queue data */
	काष्ठा vim2m_q_data   q_data[2];
पूर्ण;

अटल अंतरभूत काष्ठा vim2m_ctx *file2ctx(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा vim2m_ctx, fh);
पूर्ण

अटल काष्ठा vim2m_q_data *get_q_data(काष्ठा vim2m_ctx *ctx,
				       क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &ctx->q_data[V4L2_M2M_SRC];
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &ctx->q_data[V4L2_M2M_DST];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *type_name(क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस "Output";
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस "Capture";
	शेष:
		वापस "Invalid";
	पूर्ण
पूर्ण

#घोषणा CLIP(__color) \
	(u8)(((__color) > 0xff) ? 0xff : (((__color) < 0) ? 0 : (__color)))

अटल व्योम copy_line(काष्ठा vim2m_q_data *q_data_out,
		      u8 *src, u8 *dst, bool reverse)
अणु
	पूर्णांक x, depth = q_data_out->fmt->depth >> 3;

	अगर (!reverse) अणु
		स_नकल(dst, src, q_data_out->width * depth);
	पूर्ण अन्यथा अणु
		क्रम (x = 0; x < q_data_out->width >> 1; x++) अणु
			स_नकल(dst, src, depth);
			स_नकल(dst + depth, src - depth, depth);
			src -= depth << 1;
			dst += depth << 1;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल व्योम copy_two_pixels(काष्ठा vim2m_q_data *q_data_in,
			    काष्ठा vim2m_q_data *q_data_out,
			    u8 *src[2], u8 **dst, पूर्णांक ypos, bool reverse)
अणु
	काष्ठा vim2m_fmt *out = q_data_out->fmt;
	काष्ठा vim2m_fmt *in = q_data_in->fmt;
	u8 _r[2], _g[2], _b[2], *r, *g, *b;
	पूर्णांक i;

	/* Step 1: पढ़ो two consecutive pixels from src poपूर्णांकer */

	r = _r;
	g = _g;
	b = _b;

	चयन (in->fourcc) अणु
	हाल V4L2_PIX_FMT_RGB565: /* rrrrrggg gggbbbbb */
		क्रम (i = 0; i < 2; i++) अणु
			u16 pix = le16_to_cpu(*(__le16 *)(src[i]));

			*r++ = (u8)(((pix & 0xf800) >> 11) << 3) | 0x07;
			*g++ = (u8)((((pix & 0x07e0) >> 5)) << 2) | 0x03;
			*b++ = (u8)((pix & 0x1f) << 3) | 0x07;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565X: /* gggbbbbb rrrrrggg */
		क्रम (i = 0; i < 2; i++) अणु
			u16 pix = be16_to_cpu(*(__be16 *)(src[i]));

			*r++ = (u8)(((pix & 0xf800) >> 11) << 3) | 0x07;
			*g++ = (u8)((((pix & 0x07e0) >> 5)) << 2) | 0x03;
			*b++ = (u8)((pix & 0x1f) << 3) | 0x07;
		पूर्ण
		अवरोध;
	शेष:
	हाल V4L2_PIX_FMT_RGB24:
		क्रम (i = 0; i < 2; i++) अणु
			*r++ = src[i][0];
			*g++ = src[i][1];
			*b++ = src[i][2];
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_BGR24:
		क्रम (i = 0; i < 2; i++) अणु
			*b++ = src[i][0];
			*g++ = src[i][1];
			*r++ = src[i][2];
		पूर्ण
		अवरोध;
	पूर्ण

	/* Step 2: store two consecutive poपूर्णांकs, reversing them अगर needed */

	r = _r;
	g = _g;
	b = _b;

	चयन (out->fourcc) अणु
	हाल V4L2_PIX_FMT_RGB565: /* rrrrrggg gggbbbbb */
		क्रम (i = 0; i < 2; i++) अणु
			u16 pix;
			__le16 *dst_pix = (__le16 *)*dst;

			pix = ((*r << 8) & 0xf800) | ((*g << 3) & 0x07e0) |
			      (*b >> 3);

			*dst_pix = cpu_to_le16(pix);

			*dst += 2;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_RGB565X: /* gggbbbbb rrrrrggg */
		क्रम (i = 0; i < 2; i++) अणु
			u16 pix;
			__be16 *dst_pix = (__be16 *)*dst;

			pix = ((*r << 8) & 0xf800) | ((*g << 3) & 0x07e0) |
			      (*b >> 3);

			*dst_pix = cpu_to_be16(pix);

			*dst += 2;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_RGB24:
		क्रम (i = 0; i < 2; i++) अणु
			*(*dst)++ = *r++;
			*(*dst)++ = *g++;
			*(*dst)++ = *b++;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_BGR24:
		क्रम (i = 0; i < 2; i++) अणु
			*(*dst)++ = *b++;
			*(*dst)++ = *g++;
			*(*dst)++ = *r++;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
	अणु
		u8 y, y1, u, v;

		y = ((8453  * (*r) + 16594 * (*g) +  3223 * (*b)
		     + 524288) >> 15);
		u = ((-4878 * (*r) - 9578  * (*g) + 14456 * (*b)
		     + 4210688) >> 15);
		v = ((14456 * (*r++) - 12105 * (*g++) - 2351 * (*b++)
		     + 4210688) >> 15);
		y1 = ((8453 * (*r) + 16594 * (*g) +  3223 * (*b)
		     + 524288) >> 15);

		*(*dst)++ = y;
		*(*dst)++ = u;

		*(*dst)++ = y1;
		*(*dst)++ = v;
		वापस;
	पूर्ण
	हाल V4L2_PIX_FMT_SBGGR8:
		अगर (!(ypos & 1)) अणु
			*(*dst)++ = *b;
			*(*dst)++ = *++g;
		पूर्ण अन्यथा अणु
			*(*dst)++ = *g;
			*(*dst)++ = *++r;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_SGBRG8:
		अगर (!(ypos & 1)) अणु
			*(*dst)++ = *g;
			*(*dst)++ = *++b;
		पूर्ण अन्यथा अणु
			*(*dst)++ = *r;
			*(*dst)++ = *++g;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_SGRBG8:
		अगर (!(ypos & 1)) अणु
			*(*dst)++ = *g;
			*(*dst)++ = *++r;
		पूर्ण अन्यथा अणु
			*(*dst)++ = *b;
			*(*dst)++ = *++g;
		पूर्ण
		वापस;
	हाल V4L2_PIX_FMT_SRGGB8:
		अगर (!(ypos & 1)) अणु
			*(*dst)++ = *r;
			*(*dst)++ = *++g;
		पूर्ण अन्यथा अणु
			*(*dst)++ = *g;
			*(*dst)++ = *++b;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक device_process(काष्ठा vim2m_ctx *ctx,
			  काष्ठा vb2_v4l2_buffer *in_vb,
			  काष्ठा vb2_v4l2_buffer *out_vb)
अणु
	काष्ठा vim2m_dev *dev = ctx->dev;
	काष्ठा vim2m_q_data *q_data_in, *q_data_out;
	u8 *p_in, *p_line, *p_in_x[2], *p, *p_out;
	अचिन्हित पूर्णांक width, height, bytesperline, bytes_per_pixel;
	अचिन्हित पूर्णांक x, y, y_in, y_out, x_पूर्णांक, x_fract, x_err, x_offset;
	पूर्णांक start, end, step;

	q_data_in = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	अगर (!q_data_in)
		वापस 0;
	bytesperline = (q_data_in->width * q_data_in->fmt->depth) >> 3;
	bytes_per_pixel = q_data_in->fmt->depth >> 3;

	q_data_out = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (!q_data_out)
		वापस 0;

	/* As we're करोing scaling, use the output dimensions here */
	height = q_data_out->height;
	width = q_data_out->width;

	p_in = vb2_plane_vaddr(&in_vb->vb2_buf, 0);
	p_out = vb2_plane_vaddr(&out_vb->vb2_buf, 0);
	अगर (!p_in || !p_out) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Acquiring kernel pointers to buffers failed\n");
		वापस -EFAULT;
	पूर्ण

	out_vb->sequence = q_data_out->sequence++;
	in_vb->sequence = q_data_in->sequence++;
	v4l2_m2m_buf_copy_metadata(in_vb, out_vb, true);

	अगर (ctx->mode & MEM2MEM_VFLIP) अणु
		start = height - 1;
		end = -1;
		step = -1;
	पूर्ण अन्यथा अणु
		start = 0;
		end = height;
		step = 1;
	पूर्ण
	y_out = 0;

	/*
	 * When क्रमmat and resolution are identical,
	 * we can use a faster copy logic
	 */
	अगर (q_data_in->fmt->fourcc == q_data_out->fmt->fourcc &&
	    q_data_in->width == q_data_out->width &&
	    q_data_in->height == q_data_out->height) अणु
		क्रम (y = start; y != end; y += step, y_out++) अणु
			p = p_in + (y * bytesperline);
			अगर (ctx->mode & MEM2MEM_HFLIP)
				p += bytesperline - (q_data_in->fmt->depth >> 3);

			copy_line(q_data_out, p, p_out,
				  ctx->mode & MEM2MEM_HFLIP);

			p_out += bytesperline;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Slower algorithm with क्रमmat conversion, hflip, vflip and scaler */

	/* To speed scaler up, use Bresenham क्रम X dimension */
	x_पूर्णांक = q_data_in->width / q_data_out->width;
	x_fract = q_data_in->width % q_data_out->width;

	क्रम (y = start; y != end; y += step, y_out++) अणु
		y_in = (y * q_data_in->height) / q_data_out->height;
		x_offset = 0;
		x_err = 0;

		p_line = p_in + (y_in * bytesperline);
		अगर (ctx->mode & MEM2MEM_HFLIP)
			p_line += bytesperline - (q_data_in->fmt->depth >> 3);
		p_in_x[0] = p_line;

		क्रम (x = 0; x < width >> 1; x++) अणु
			x_offset += x_पूर्णांक;
			x_err += x_fract;
			अगर (x_err > width) अणु
				x_offset++;
				x_err -= width;
			पूर्ण

			अगर (ctx->mode & MEM2MEM_HFLIP)
				p_in_x[1] = p_line - x_offset * bytes_per_pixel;
			अन्यथा
				p_in_x[1] = p_line + x_offset * bytes_per_pixel;

			copy_two_pixels(q_data_in, q_data_out,
					p_in_x, &p_out, y_out,
					ctx->mode & MEM2MEM_HFLIP);

			/* Calculate the next p_in_x0 */
			x_offset += x_पूर्णांक;
			x_err += x_fract;
			अगर (x_err > width) अणु
				x_offset++;
				x_err -= width;
			पूर्ण

			अगर (ctx->mode & MEM2MEM_HFLIP)
				p_in_x[0] = p_line - x_offset * bytes_per_pixel;
			अन्यथा
				p_in_x[0] = p_line + x_offset * bytes_per_pixel;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * mem2mem callbacks
 */

/*
 * job_पढ़ोy() - check whether an instance is पढ़ोy to be scheduled to run
 */
अटल पूर्णांक job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा vim2m_ctx *ctx = priv;

	अगर (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) < ctx->translen
	    || v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx) < ctx->translen) अणु
		dprपूर्णांकk(ctx->dev, 1, "Not enough buffers available\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम job_पात(व्योम *priv)
अणु
	काष्ठा vim2m_ctx *ctx = priv;

	/* Will cancel the transaction in the next पूर्णांकerrupt handler */
	ctx->पातing = 1;
पूर्ण

/* device_run() - prepares and starts the device
 *
 * This simulates all the immediate preparations required beक्रमe starting
 * a device. This will be called by the framework when it decides to schedule
 * a particular instance.
 */
अटल व्योम device_run(व्योम *priv)
अणु
	काष्ठा vim2m_ctx *ctx = priv;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	/* Apply request controls अगर any */
	v4l2_ctrl_request_setup(src_buf->vb2_buf.req_obj.req,
				&ctx->hdl);

	device_process(ctx, src_buf, dst_buf);

	/* Complete request controls अगर any */
	v4l2_ctrl_request_complete(src_buf->vb2_buf.req_obj.req,
				   &ctx->hdl);

	/* Run delayed work, which simulates a hardware irq  */
	schedule_delayed_work(&ctx->work_run, msecs_to_jअगरfies(ctx->transसमय));
पूर्ण

अटल व्योम device_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा vim2m_ctx *curr_ctx;
	काष्ठा vim2m_dev *vim2m_dev;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;

	curr_ctx = container_of(w, काष्ठा vim2m_ctx, work_run.work);

	अगर (!curr_ctx) अणु
		pr_err("Instance released before the end of transaction\n");
		वापस;
	पूर्ण

	vim2m_dev = curr_ctx->dev;

	src_vb = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	curr_ctx->num_processed++;

	v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_DONE);

	अगर (curr_ctx->num_processed == curr_ctx->translen
	    || curr_ctx->पातing) अणु
		dprपूर्णांकk(curr_ctx->dev, 2, "Finishing capture buffer fill\n");
		curr_ctx->num_processed = 0;
		v4l2_m2m_job_finish(vim2m_dev->m2m_dev, curr_ctx->fh.m2m_ctx);
	पूर्ण अन्यथा अणु
		device_run(curr_ctx);
	पूर्ण
पूर्ण

/*
 * video ioctls
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, MEM2MEM_NAME, माप(cap->driver));
	strscpy(cap->card, MEM2MEM_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", MEM2MEM_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num;
	काष्ठा vim2m_fmt *fmt;

	num = 0;

	क्रम (i = 0; i < NUM_FORMATS; ++i) अणु
		अगर (क्रमmats[i].types & type) अणु
			/* index-th क्रमmat of type type found ? */
			अगर (num == f->index)
				अवरोध;
			/*
			 * Correct type but haven't reached our index yet,
			 * just increment per-type index
			 */
			++num;
		पूर्ण
	पूर्ण

	अगर (i < NUM_FORMATS) अणु
		/* Format found */
		fmt = &क्रमmats[i];
		f->pixelक्रमmat = fmt->fourcc;
		वापस 0;
	पूर्ण

	/* Format not found */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस क्रमागत_fmt(f, MEM2MEM_CAPTURE);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस क्रमागत_fmt(f, MEM2MEM_OUTPUT);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	अगर (fsize->index != 0)
		वापस -EINVAL;

	अगर (!find_क्रमmat(fsize->pixel_क्रमmat))
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = MIN_W;
	fsize->stepwise.min_height = MIN_H;
	fsize->stepwise.max_width = MAX_W;
	fsize->stepwise.max_height = MAX_H;

	get_alignment(fsize->pixel_क्रमmat,
		      &fsize->stepwise.step_width,
		      &fsize->stepwise.step_height);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा vim2m_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा vim2m_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.field	= V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat	= q_data->fmt->fourcc;
	f->fmt.pix.bytesperline	= (q_data->width * q_data->fmt->depth) >> 3;
	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.colorspace	= ctx->colorspace;
	f->fmt.pix.xfer_func	= ctx->xfer_func;
	f->fmt.pix.ycbcr_enc	= ctx->ycbcr_enc;
	f->fmt.pix.quantization	= ctx->quant;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा v4l2_क्रमmat *f, काष्ठा vim2m_fmt *fmt)
अणु
	पूर्णांक walign, halign;
	/*
	 * V4L2 specअगरication specअगरies the driver corrects the
	 * क्रमmat काष्ठा अगर any of the dimensions is unsupported
	 */
	अगर (f->fmt.pix.height < MIN_H)
		f->fmt.pix.height = MIN_H;
	अन्यथा अगर (f->fmt.pix.height > MAX_H)
		f->fmt.pix.height = MAX_H;

	अगर (f->fmt.pix.width < MIN_W)
		f->fmt.pix.width = MIN_W;
	अन्यथा अगर (f->fmt.pix.width > MAX_W)
		f->fmt.pix.width = MAX_W;

	get_alignment(f->fmt.pix.pixelक्रमmat, &walign, &halign);
	f->fmt.pix.width &= ~(walign - 1);
	f->fmt.pix.height &= ~(halign - 1);
	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vim2m_fmt *fmt;
	काष्ठा vim2m_ctx *ctx = file2ctx(file);

	fmt = find_क्रमmat(f->fmt.pix.pixelक्रमmat);
	अगर (!fmt) अणु
		f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
		fmt = find_क्रमmat(f->fmt.pix.pixelक्रमmat);
	पूर्ण
	अगर (!(fmt->types & MEM2MEM_CAPTURE)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण
	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;
	f->fmt.pix.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix.quantization = ctx->quant;

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vim2m_fmt *fmt;
	काष्ठा vim2m_ctx *ctx = file2ctx(file);

	fmt = find_क्रमmat(f->fmt.pix.pixelक्रमmat);
	अगर (!fmt) अणु
		f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
		fmt = find_क्रमmat(f->fmt.pix.pixelक्रमmat);
	पूर्ण
	अगर (!(fmt->types & MEM2MEM_OUTPUT)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण
	अगर (!f->fmt.pix.colorspace)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा vim2m_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vim2m_q_data *q_data;
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	q_data->fmt		= find_क्रमmat(f->fmt.pix.pixelक्रमmat);
	q_data->width		= f->fmt.pix.width;
	q_data->height		= f->fmt.pix.height;
	q_data->sizeimage	= q_data->width * q_data->height
				* q_data->fmt->depth >> 3;

	dprपूर्णांकk(ctx->dev, 1,
		"Format for type %s: %dx%d (%d bpp), fmt: %c%c%c%c\n",
		type_name(f->type), q_data->width, q_data->height,
		q_data->fmt->depth,
		(q_data->fmt->fourcc & 0xff),
		(q_data->fmt->fourcc >>  8) & 0xff,
		(q_data->fmt->fourcc >> 16) & 0xff,
		(q_data->fmt->fourcc >> 24) & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस vidioc_s_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vim2m_ctx *ctx = file2ctx(file);
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	ret = vidioc_s_fmt(file2ctx(file), f);
	अगर (!ret) अणु
		ctx->colorspace = f->fmt.pix.colorspace;
		ctx->xfer_func = f->fmt.pix.xfer_func;
		ctx->ycbcr_enc = f->fmt.pix.ycbcr_enc;
		ctx->quant = f->fmt.pix.quantization;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vim2m_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vim2m_ctx *ctx =
		container_of(ctrl->handler, काष्ठा vim2m_ctx, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		अगर (ctrl->val)
			ctx->mode |= MEM2MEM_HFLIP;
		अन्यथा
			ctx->mode &= ~MEM2MEM_HFLIP;
		अवरोध;

	हाल V4L2_CID_VFLIP:
		अगर (ctrl->val)
			ctx->mode |= MEM2MEM_VFLIP;
		अन्यथा
			ctx->mode &= ~MEM2MEM_VFLIP;
		अवरोध;

	हाल V4L2_CID_TRANS_TIME_MSEC:
		ctx->transसमय = ctrl->val;
		अगर (ctx->transसमय < 1)
			ctx->transसमय = 1;
		अवरोध;

	हाल V4L2_CID_TRANS_NUM_BUFS:
		ctx->translen = ctrl->val;
		अवरोध;

	शेष:
		v4l2_err(&ctx->dev->v4l2_dev, "Invalid control\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vim2m_ctrl_ops = अणु
	.s_ctrl = vim2m_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops vim2m_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_framesizes = vidioc_क्रमागत_framesizes,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out	= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= vidioc_s_fmt_vid_out,

	.vidioc_reqbufs		= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf		= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf		= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf	= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs	= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon	= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,

	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/*
 * Queue operations
 */

अटल पूर्णांक vim2m_queue_setup(काष्ठा vb2_queue *vq,
			     अचिन्हित पूर्णांक *nbuffers,
			     अचिन्हित पूर्णांक *nplanes,
			     अचिन्हित पूर्णांक sizes[],
			     काष्ठा device *alloc_devs[])
अणु
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vim2m_q_data *q_data;
	अचिन्हित पूर्णांक size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);
	अगर (!q_data)
		वापस -EINVAL;

	size = q_data->width * q_data->height * q_data->fmt->depth >> 3;

	जबतक (size * count > MEM2MEM_VID_MEM_LIMIT)
		(count)--;
	*nbuffers = count;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dprपूर्णांकk(ctx->dev, 1, "%s: get %d buffer(s) of size %d each.\n",
		type_name(vq->type), count, size);

	वापस 0;
पूर्ण

अटल पूर्णांक vim2m_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	अगर (vbuf->field == V4L2_FIELD_ANY)
		vbuf->field = V4L2_FIELD_NONE;
	अगर (vbuf->field != V4L2_FIELD_NONE) अणु
		dprपूर्णांकk(ctx->dev, 1, "%s field isn't supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vim2m_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vim2m_q_data *q_data;

	dprपूर्णांकk(ctx->dev, 2, "type: %s\n", type_name(vb->vb2_queue->type));

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	अगर (!q_data)
		वापस -EINVAL;
	अगर (vb2_plane_size(vb, 0) < q_data->sizeimage) अणु
		dprपूर्णांकk(ctx->dev, 1,
			"%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0),
			(दीर्घ)q_data->sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, q_data->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम vim2m_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक vim2m_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vim2m_q_data *q_data = get_q_data(ctx, q->type);

	अगर (!q_data)
		वापस -EINVAL;

	अगर (V4L2_TYPE_IS_OUTPUT(q->type))
		ctx->पातing = 0;

	q_data->sequence = 0;
	वापस 0;
पूर्ण

अटल व्योम vim2m_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;

	cancel_delayed_work_sync(&ctx->work_run);

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (!vbuf)
			वापस;
		v4l2_ctrl_request_complete(vbuf->vb2_buf.req_obj.req,
					   &ctx->hdl);
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल व्योम vim2m_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vim2m_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &ctx->hdl);
पूर्ण

अटल स्थिर काष्ठा vb2_ops vim2m_qops = अणु
	.queue_setup	 = vim2m_queue_setup,
	.buf_out_validate	 = vim2m_buf_out_validate,
	.buf_prepare	 = vim2m_buf_prepare,
	.buf_queue	 = vim2m_buf_queue,
	.start_streaming = vim2m_start_streaming,
	.stop_streaming  = vim2m_stop_streaming,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.buf_request_complete = vim2m_buf_request_complete,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा vim2m_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &vim2m_qops;
	src_vq->mem_ops = &vb2_vदो_स्मृति_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->vb_mutex;
	src_vq->supports_requests = true;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &vim2m_qops;
	dst_vq->mem_ops = &vb2_vदो_स्मृति_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->vb_mutex;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल काष्ठा v4l2_ctrl_config vim2m_ctrl_trans_समय_msec = अणु
	.ops = &vim2m_ctrl_ops,
	.id = V4L2_CID_TRANS_TIME_MSEC,
	.name = "Transaction Time (msec)",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 1,
	.max = 10001,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vim2m_ctrl_trans_num_bufs = अणु
	.ops = &vim2m_ctrl_ops,
	.id = V4L2_CID_TRANS_NUM_BUFS,
	.name = "Buffers Per Transaction",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 1,
	.min = 1,
	.max = MEM2MEM_DEF_NUM_BUFS,
	.step = 1,
पूर्ण;

/*
 * File operations
 */
अटल पूर्णांक vim2m_खोलो(काष्ठा file *file)
अणु
	काष्ठा vim2m_dev *dev = video_drvdata(file);
	काष्ठा vim2m_ctx *ctx = शून्य;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक rc = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->dev_mutex))
		वापस -ERESTARTSYS;
	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		rc = -ENOMEM;
		जाओ खोलो_unlock;
	पूर्ण

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = dev;
	hdl = &ctx->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &vim2m_ctrl_ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &vim2m_ctrl_ops, V4L2_CID_VFLIP, 0, 1, 1, 0);

	vim2m_ctrl_trans_समय_msec.def = शेष_transसमय;
	v4l2_ctrl_new_custom(hdl, &vim2m_ctrl_trans_समय_msec, शून्य);
	v4l2_ctrl_new_custom(hdl, &vim2m_ctrl_trans_num_bufs, शून्य);
	अगर (hdl->error) अणु
		rc = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		kमुक्त(ctx);
		जाओ खोलो_unlock;
	पूर्ण
	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	ctx->q_data[V4L2_M2M_SRC].fmt = &क्रमmats[0];
	ctx->q_data[V4L2_M2M_SRC].width = 640;
	ctx->q_data[V4L2_M2M_SRC].height = 480;
	ctx->q_data[V4L2_M2M_SRC].sizeimage =
		ctx->q_data[V4L2_M2M_SRC].width *
		ctx->q_data[V4L2_M2M_SRC].height *
		(ctx->q_data[V4L2_M2M_SRC].fmt->depth >> 3);
	ctx->q_data[V4L2_M2M_DST] = ctx->q_data[V4L2_M2M_SRC];
	ctx->colorspace = V4L2_COLORSPACE_REC709;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	mutex_init(&ctx->vb_mutex);
	INIT_DELAYED_WORK(&ctx->work_run, device_work);

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		rc = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_मुक्त(hdl);
		v4l2_fh_निकास(&ctx->fh);
		kमुक्त(ctx);
		जाओ खोलो_unlock;
	पूर्ण

	v4l2_fh_add(&ctx->fh);
	atomic_inc(&dev->num_inst);

	dprपूर्णांकk(dev, 1, "Created instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

खोलो_unlock:
	mutex_unlock(&dev->dev_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक vim2m_release(काष्ठा file *file)
अणु
	काष्ठा vim2m_dev *dev = video_drvdata(file);
	काष्ठा vim2m_ctx *ctx = file2ctx(file);

	dprपूर्णांकk(dev, 1, "Releasing instance %p\n", ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->hdl);
	mutex_lock(&dev->dev_mutex);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(&dev->dev_mutex);
	kमुक्त(ctx);

	atomic_dec(&dev->num_inst);

	वापस 0;
पूर्ण

अटल व्योम vim2m_device_release(काष्ठा video_device *vdev)
अणु
	काष्ठा vim2m_dev *dev = container_of(vdev, काष्ठा vim2m_dev, vfd);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	v4l2_m2m_release(dev->m2m_dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_device_cleanup(&dev->mdev);
#पूर्ण_अगर
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vim2m_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vim2m_खोलो,
	.release	= vim2m_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device vim2m_videodev = अणु
	.name		= MEM2MEM_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &vim2m_fops,
	.ioctl_ops	= &vim2m_ioctl_ops,
	.minor		= -1,
	.release	= vim2m_device_release,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= device_run,
	.job_पढ़ोy	= job_पढ़ोy,
	.job_पात	= job_पात,
पूर्ण;

अटल स्थिर काष्ठा media_device_ops m2m_media_ops = अणु
	.req_validate = vb2_request_validate,
	.req_queue = v4l2_m2m_request_queue,
पूर्ण;

अटल पूर्णांक vim2m_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vim2m_dev *dev;
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		जाओ error_मुक्त;

	atomic_set(&dev->num_inst, 0);
	mutex_init(&dev->dev_mutex);

	dev->vfd = vim2m_videodev;
	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	video_set_drvdata(vfd, dev);
	v4l2_info(&dev->v4l2_dev,
		  "Device registered as /dev/video%d\n", vfd->num);

	platक्रमm_set_drvdata(pdev, dev);

	dev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		dev->m2m_dev = शून्य;
		जाओ error_dev;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->mdev.dev = &pdev->dev;
	strscpy(dev->mdev.model, "vim2m", माप(dev->mdev.model));
	strscpy(dev->mdev.bus_info, "platform:vim2m",
		माप(dev->mdev.bus_info));
	media_device_init(&dev->mdev);
	dev->mdev.ops = &m2m_media_ops;
	dev->v4l2_dev.mdev = &dev->mdev;
#पूर्ण_अगर

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		जाओ error_m2m;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	ret = v4l2_m2m_रेजिस्टर_media_controller(dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PROC_VIDEO_SCALER);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem media controller\n");
		जाओ error_v4l2;
	पूर्ण

	ret = media_device_रेजिस्टर(&dev->mdev);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register mem2mem media device\n");
		जाओ error_m2m_mc;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
error_m2m_mc:
	v4l2_m2m_unरेजिस्टर_media_controller(dev->m2m_dev);
#पूर्ण_अगर
error_v4l2:
	video_unरेजिस्टर_device(&dev->vfd);
	/* vim2m_device_release called by video_unरेजिस्टर_device to release various objects */
	वापस ret;
error_m2m:
	v4l2_m2m_release(dev->m2m_dev);
error_dev:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
error_मुक्त:
	kमुक्त(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक vim2m_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vim2m_dev *dev = platक्रमm_get_drvdata(pdev);

	v4l2_info(&dev->v4l2_dev, "Removing " MEM2MEM_NAME);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_device_unरेजिस्टर(&dev->mdev);
	v4l2_m2m_unरेजिस्टर_media_controller(dev->m2m_dev);
#पूर्ण_अगर
	video_unरेजिस्टर_device(&dev->vfd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vim2m_pdrv = अणु
	.probe		= vim2m_probe,
	.हटाओ		= vim2m_हटाओ,
	.driver		= अणु
		.name	= MEM2MEM_NAME,
	पूर्ण,
पूर्ण;

अटल व्योम __निकास vim2m_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vim2m_pdrv);
	platक्रमm_device_unरेजिस्टर(&vim2m_pdev);
पूर्ण

अटल पूर्णांक __init vim2m_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&vim2m_pdev);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&vim2m_pdrv);
	अगर (ret)
		platक्रमm_device_unरेजिस्टर(&vim2m_pdev);

	वापस ret;
पूर्ण

module_init(vim2m_init);
module_निकास(vim2m_निकास);
