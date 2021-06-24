<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX Pixel Pipeline (PXP) mem-to-mem scaler/CSC/rotator driver
 *
 * Copyright (c) 2018 Pengutronix, Philipp Zabel
 *
 * based on vim2m
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "imx-pxp.h"

अटल अचिन्हित पूर्णांक debug;
module_param(debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "activates debug info");

#घोषणा MIN_W 8
#घोषणा MIN_H 8
#घोषणा MAX_W 4096
#घोषणा MAX_H 4096
#घोषणा ALIGN_W 3 /* 8x8 pixel blocks */
#घोषणा ALIGN_H 3

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा MEM2MEM_CAPTURE	(1 << 0)
#घोषणा MEM2MEM_OUTPUT	(1 << 1)

#घोषणा MEM2MEM_NAME		"pxp"

/* Flags that indicate processing mode */
#घोषणा MEM2MEM_HFLIP	(1 << 0)
#घोषणा MEM2MEM_VFLIP	(1 << 1)

#घोषणा dprपूर्णांकk(dev, fmt, arg...) \
	v4l2_dbg(1, debug, &dev->v4l2_dev, "%s: " fmt, __func__, ## arg)

काष्ठा pxp_fmt अणु
	u32	fourcc;
	पूर्णांक	depth;
	/* Types the क्रमmat can be used क्रम */
	u32	types;
पूर्ण;

अटल काष्ठा pxp_fmt क्रमmats[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_XBGR32,
		.depth	= 32,
		/* Both capture and output क्रमmat */
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_ABGR32,
		.depth	= 32,
		/* Capture-only क्रमmat */
		.types	= MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGR24,
		.depth	= 24,
		.types	= MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB565,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB555,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB444,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_VUYA32,
		.depth	= 32,
		.types	= MEM2MEM_CAPTURE,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_VUYX32,
		.depth	= 32,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_UYVY,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.depth	= 16,
		/* Output-only क्रमmat */
		.types	= MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_VYUY,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVYU,
		.depth	= 16,
		.types	= MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_GREY,
		.depth	= 8,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_Y4,
		.depth	= 4,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.depth	= 12,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV21,
		.depth	= 12,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV61,
		.depth	= 16,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.depth	= 16,
		.types	= MEM2MEM_OUTPUT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV420,
		.depth	= 12,
		.types	= MEM2MEM_OUTPUT,
	पूर्ण,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

/* Per-queue, driver-specअगरic निजी data */
काष्ठा pxp_q_data अणु
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		bytesperline;
	अचिन्हित पूर्णांक		sizeimage;
	अचिन्हित पूर्णांक		sequence;
	काष्ठा pxp_fmt		*fmt;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization	quant;
पूर्ण;

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

अटल काष्ठा pxp_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxp_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NUM_FORMATS; k++) अणु
		fmt = &क्रमmats[k];
		अगर (fmt->fourcc == f->fmt.pix.pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (k == NUM_FORMATS)
		वापस शून्य;

	वापस &क्रमmats[k];
पूर्ण

काष्ठा pxp_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;

	काष्ठा clk		*clk;
	व्योम __iomem		*mmio;

	atomic_t		num_inst;
	काष्ठा mutex		dev_mutex;
	spinlock_t		irqlock;

	काष्ठा v4l2_m2m_dev	*m2m_dev;
पूर्ण;

काष्ठा pxp_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा pxp_dev	*dev;

	काष्ठा v4l2_ctrl_handler hdl;

	/* Abort requested by m2m */
	पूर्णांक			पातing;

	/* Processing mode */
	पूर्णांक			mode;
	u8			alpha_component;

	क्रमागत v4l2_colorspace	colorspace;
	क्रमागत v4l2_xfer_func	xfer_func;

	/* Source and destination queue data */
	काष्ठा pxp_q_data   q_data[2];
पूर्ण;

अटल अंतरभूत काष्ठा pxp_ctx *file2ctx(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा pxp_ctx, fh);
पूर्ण

अटल काष्ठा pxp_q_data *get_q_data(काष्ठा pxp_ctx *ctx,
					 क्रमागत v4l2_buf_type type)
अणु
	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस &ctx->q_data[V4L2_M2M_SRC];
	अन्यथा
		वापस &ctx->q_data[V4L2_M2M_DST];
पूर्ण

अटल u32 pxp_v4l2_pix_fmt_to_ps_क्रमmat(u32 v4l2_pix_fmt)
अणु
	चयन (v4l2_pix_fmt) अणु
	हाल V4L2_PIX_FMT_XBGR32:  वापस BV_PXP_PS_CTRL_FORMAT__RGB888;
	हाल V4L2_PIX_FMT_RGB555:  वापस BV_PXP_PS_CTRL_FORMAT__RGB555;
	हाल V4L2_PIX_FMT_RGB444:  वापस BV_PXP_PS_CTRL_FORMAT__RGB444;
	हाल V4L2_PIX_FMT_RGB565:  वापस BV_PXP_PS_CTRL_FORMAT__RGB565;
	हाल V4L2_PIX_FMT_VUYX32:  वापस BV_PXP_PS_CTRL_FORMAT__YUV1P444;
	हाल V4L2_PIX_FMT_UYVY:    वापस BV_PXP_PS_CTRL_FORMAT__UYVY1P422;
	हाल V4L2_PIX_FMT_YUYV:    वापस BM_PXP_PS_CTRL_WB_SWAP |
					  BV_PXP_PS_CTRL_FORMAT__UYVY1P422;
	हाल V4L2_PIX_FMT_VYUY:    वापस BV_PXP_PS_CTRL_FORMAT__VYUY1P422;
	हाल V4L2_PIX_FMT_YVYU:    वापस BM_PXP_PS_CTRL_WB_SWAP |
					  BV_PXP_PS_CTRL_FORMAT__VYUY1P422;
	हाल V4L2_PIX_FMT_GREY:    वापस BV_PXP_PS_CTRL_FORMAT__Y8;
	शेष:
	हाल V4L2_PIX_FMT_Y4:      वापस BV_PXP_PS_CTRL_FORMAT__Y4;
	हाल V4L2_PIX_FMT_NV16:    वापस BV_PXP_PS_CTRL_FORMAT__YUV2P422;
	हाल V4L2_PIX_FMT_NV12:    वापस BV_PXP_PS_CTRL_FORMAT__YUV2P420;
	हाल V4L2_PIX_FMT_NV21:    वापस BV_PXP_PS_CTRL_FORMAT__YVU2P420;
	हाल V4L2_PIX_FMT_NV61:    वापस BV_PXP_PS_CTRL_FORMAT__YVU2P422;
	हाल V4L2_PIX_FMT_YUV422P: वापस BV_PXP_PS_CTRL_FORMAT__YUV422;
	हाल V4L2_PIX_FMT_YUV420:  वापस BV_PXP_PS_CTRL_FORMAT__YUV420;
	पूर्ण
पूर्ण

अटल u32 pxp_v4l2_pix_fmt_to_out_क्रमmat(u32 v4l2_pix_fmt)
अणु
	चयन (v4l2_pix_fmt) अणु
	हाल V4L2_PIX_FMT_XBGR32:   वापस BV_PXP_OUT_CTRL_FORMAT__RGB888;
	हाल V4L2_PIX_FMT_ABGR32:   वापस BV_PXP_OUT_CTRL_FORMAT__ARGB8888;
	हाल V4L2_PIX_FMT_BGR24:    वापस BV_PXP_OUT_CTRL_FORMAT__RGB888P;
	/* Missing V4L2 pixel क्रमmats क्रम ARGB1555 and ARGB4444 */
	हाल V4L2_PIX_FMT_RGB555:   वापस BV_PXP_OUT_CTRL_FORMAT__RGB555;
	हाल V4L2_PIX_FMT_RGB444:   वापस BV_PXP_OUT_CTRL_FORMAT__RGB444;
	हाल V4L2_PIX_FMT_RGB565:   वापस BV_PXP_OUT_CTRL_FORMAT__RGB565;
	हाल V4L2_PIX_FMT_VUYA32:
	हाल V4L2_PIX_FMT_VUYX32:   वापस BV_PXP_OUT_CTRL_FORMAT__YUV1P444;
	हाल V4L2_PIX_FMT_UYVY:     वापस BV_PXP_OUT_CTRL_FORMAT__UYVY1P422;
	हाल V4L2_PIX_FMT_VYUY:     वापस BV_PXP_OUT_CTRL_FORMAT__VYUY1P422;
	हाल V4L2_PIX_FMT_GREY:     वापस BV_PXP_OUT_CTRL_FORMAT__Y8;
	शेष:
	हाल V4L2_PIX_FMT_Y4:       वापस BV_PXP_OUT_CTRL_FORMAT__Y4;
	हाल V4L2_PIX_FMT_NV16:     वापस BV_PXP_OUT_CTRL_FORMAT__YUV2P422;
	हाल V4L2_PIX_FMT_NV12:     वापस BV_PXP_OUT_CTRL_FORMAT__YUV2P420;
	हाल V4L2_PIX_FMT_NV61:     वापस BV_PXP_OUT_CTRL_FORMAT__YVU2P422;
	हाल V4L2_PIX_FMT_NV21:     वापस BV_PXP_OUT_CTRL_FORMAT__YVU2P420;
	पूर्ण
पूर्ण

अटल bool pxp_v4l2_pix_fmt_is_yuv(u32 v4l2_pix_fmt)
अणु
	चयन (v4l2_pix_fmt) अणु
	हाल V4L2_PIX_FMT_VUYA32:
	हाल V4L2_PIX_FMT_VUYX32:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_VYUY:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_GREY:
	हाल V4L2_PIX_FMT_Y4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम pxp_setup_csc(काष्ठा pxp_ctx *ctx)
अणु
	काष्ठा pxp_dev *dev = ctx->dev;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;

	अगर (pxp_v4l2_pix_fmt_is_yuv(ctx->q_data[V4L2_M2M_SRC].fmt->fourcc) &&
	    !pxp_v4l2_pix_fmt_is_yuv(ctx->q_data[V4L2_M2M_DST].fmt->fourcc)) अणु
		/*
		 * CSC1 YUV/YCbCr to RGB conversion is implemented as follows:
		 *
		 * |R|   |C0 0  C1|   |Y  + Yoffset |
		 * |G| = |C0 C3 C2| * |Cb + UVoffset|
		 * |B|   |C0 C4 0 |   |Cr + UVoffset|
		 *
		 * Results are clamped to 0..255.
		 *
		 * BT.601 limited range:
		 *
		 * |R|   |1.1644  0.0000  1.5960|   |Y  - 16 |
		 * |G| = |1.1644 -0.3917 -0.8129| * |Cb - 128|
		 * |B|   |1.1644  2.0172  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_bt601_lim[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x198) |	/*  1.5938 (-0.23 %) */
			BF_PXP_CSC1_COEF1_C4(0x204),	/*  2.0156 (-0.16 %) */
			BF_PXP_CSC1_COEF2_C2(0x730) |	/* -0.8125 (+0.04 %) */
			BF_PXP_CSC1_COEF2_C3(0x79c),	/* -0.3906 (+0.11 %) */
		पूर्ण;
		/*
		 * BT.601 full range:
		 *
		 * |R|   |1.0000  0.0000  1.4020|   |Y  + 0  |
		 * |G| = |1.0000 -0.3441 -0.7141| * |Cb - 128|
		 * |B|   |1.0000  1.7720  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_bt601_full[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x166) |	/*  1.3984 (-0.36 %) */
			BF_PXP_CSC1_COEF1_C4(0x1c5),	/*  1.7695 (-0.25 %) */
			BF_PXP_CSC1_COEF2_C2(0x74a) |	/* -0.7109 (+0.32 %) */
			BF_PXP_CSC1_COEF2_C3(0x7a8),	/* -0.3438 (+0.04 %) */
		पूर्ण;
		/*
		 * Rec.709 limited range:
		 *
		 * |R|   |1.1644  0.0000  1.7927|   |Y  - 16 |
		 * |G| = |1.1644 -0.2132 -0.5329| * |Cb - 128|
		 * |B|   |1.1644  2.1124  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_rec709_lim[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x1ca) |	/*  1.7891 (-0.37 %) */
			BF_PXP_CSC1_COEF1_C4(0x21c),	/*  2.1094 (-0.30 %) */
			BF_PXP_CSC1_COEF2_C2(0x778) |	/* -0.5312 (+0.16 %) */
			BF_PXP_CSC1_COEF2_C3(0x7ca),	/* -0.2109 (+0.23 %) */
		पूर्ण;
		/*
		 * Rec.709 full range:
		 *
		 * |R|   |1.0000  0.0000  1.5748|   |Y  + 0  |
		 * |G| = |1.0000 -0.1873 -0.4681| * |Cb - 128|
		 * |B|   |1.0000  1.8556  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_rec709_full[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x193) |	/*  1.5742 (-0.06 %) */
			BF_PXP_CSC1_COEF1_C4(0x1db),	/*  1.8555 (-0.01 %) */
			BF_PXP_CSC1_COEF2_C2(0x789) |	/* -0.4648 (+0.33 %) */
			BF_PXP_CSC1_COEF2_C3(0x7d1),	/* -0.1836 (+0.37 %) */
		पूर्ण;
		/*
		 * BT.2020 limited range:
		 *
		 * |R|   |1.1644  0.0000  1.6787|   |Y  - 16 |
		 * |G| = |1.1644 -0.1874 -0.6505| * |Cb - 128|
		 * |B|   |1.1644  2.1418  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_bt2020_lim[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x1ad) |	/*  1.6758 (-0.29 %) */
			BF_PXP_CSC1_COEF1_C4(0x224),	/*  2.1406 (-0.11 %) */
			BF_PXP_CSC1_COEF2_C2(0x75a) |	/* -0.6484 (+0.20 %) */
			BF_PXP_CSC1_COEF2_C3(0x7d1),	/* -0.1836 (+0.38 %) */
		पूर्ण;
		/*
		 * BT.2020 full range:
		 *
		 * |R|   |1.0000  0.0000  1.4746|   |Y  + 0  |
		 * |G| = |1.0000 -0.1646 -0.5714| * |Cb - 128|
		 * |B|   |1.0000  1.8814  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_bt2020_full[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x179) |	/*  1.4727 (-0.19 %) */
			BF_PXP_CSC1_COEF1_C4(0x1e1),	/*  1.8789 (-0.25 %) */
			BF_PXP_CSC1_COEF2_C2(0x76e) |	/* -0.5703 (+0.11 %) */
			BF_PXP_CSC1_COEF2_C3(0x7d6),	/* -0.1641 (+0.05 %) */
		पूर्ण;
		/*
		 * SMPTE 240m limited range:
		 *
		 * |R|   |1.1644  0.0000  1.7937|   |Y  - 16 |
		 * |G| = |1.1644 -0.2565 -0.5427| * |Cb - 128|
		 * |B|   |1.1644  2.0798  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_smpte240m_lim[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x1cb) |	/*  1.7930 (-0.07 %) */
			BF_PXP_CSC1_COEF1_C4(0x214),	/*  2.0781 (-0.17 %) */
			BF_PXP_CSC1_COEF2_C2(0x776) |	/* -0.5391 (+0.36 %) */
			BF_PXP_CSC1_COEF2_C3(0x7bf),	/* -0.2539 (+0.26 %) */
		पूर्ण;
		/*
		 * SMPTE 240m full range:
		 *
		 * |R|   |1.0000  0.0000  1.5756|   |Y  + 0  |
		 * |G| = |1.0000 -0.2253 -0.4767| * |Cb - 128|
		 * |B|   |1.0000  1.8270  0.0000|   |Cr - 128|
		 */
		अटल स्थिर u32 csc1_coef_smpte240m_full[3] = अणु
			BM_PXP_CSC1_COEF0_YCBCR_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x193) |	/*  1.5742 (-0.14 %) */
			BF_PXP_CSC1_COEF1_C4(0x1d3),	/*  1.8242 (-0.28 %) */
			BF_PXP_CSC1_COEF2_C2(0x786) |	/* -0.4766 (+0.01 %) */
			BF_PXP_CSC1_COEF2_C3(0x7c7),	/* -0.2227 (+0.26 %) */
		पूर्ण;
		स्थिर u32 *csc1_coef;

		ycbcr_enc = ctx->q_data[V4L2_M2M_SRC].ycbcr_enc;
		quantization = ctx->q_data[V4L2_M2M_SRC].quant;

		अगर (ycbcr_enc == V4L2_YCBCR_ENC_601) अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc1_coef = csc1_coef_bt601_full;
			अन्यथा
				csc1_coef = csc1_coef_bt601_lim;
		पूर्ण अन्यथा अगर (ycbcr_enc == V4L2_YCBCR_ENC_709) अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc1_coef = csc1_coef_rec709_full;
			अन्यथा
				csc1_coef = csc1_coef_rec709_lim;
		पूर्ण अन्यथा अगर (ycbcr_enc == V4L2_YCBCR_ENC_BT2020) अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc1_coef = csc1_coef_bt2020_full;
			अन्यथा
				csc1_coef = csc1_coef_bt2020_lim;
		पूर्ण अन्यथा अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc1_coef = csc1_coef_smpte240m_full;
			अन्यथा
				csc1_coef = csc1_coef_smpte240m_lim;
		पूर्ण

		ग_लिखोl(csc1_coef[0], dev->mmio + HW_PXP_CSC1_COEF0);
		ग_लिखोl(csc1_coef[1], dev->mmio + HW_PXP_CSC1_COEF1);
		ग_लिखोl(csc1_coef[2], dev->mmio + HW_PXP_CSC1_COEF2);
	पूर्ण अन्यथा अणु
		ग_लिखोl(BM_PXP_CSC1_COEF0_BYPASS, dev->mmio + HW_PXP_CSC1_COEF0);
	पूर्ण

	अगर (!pxp_v4l2_pix_fmt_is_yuv(ctx->q_data[V4L2_M2M_SRC].fmt->fourcc) &&
	    pxp_v4l2_pix_fmt_is_yuv(ctx->q_data[V4L2_M2M_DST].fmt->fourcc)) अणु
		/*
		 * CSC2 RGB to YUV/YCbCr conversion is implemented as follows:
		 *
		 * |Y |   |A1 A2 A3|   |R|   |D1|
		 * |Cb| = |B1 B2 B3| * |G| + |D2|
		 * |Cr|   |C1 C2 C3|   |B|   |D3|
		 *
		 * Results are clamped to 0..255.
		 *
		 * BT.601 limited range:
		 *
		 * |Y |   | 0.2568  0.5041  0.0979|   |R|   |16 |
		 * |Cb| = |-0.1482 -0.2910  0.4392| * |G| + |128|
		 * |Cr|   | 0.4392  0.4392 -0.3678|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_bt601_lim[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x081) |	/*  0.5039 (-0.02 %) */
			BF_PXP_CSC2_COEF0_A1(0x041),	/*  0.2539 (-0.29 %) */
			BF_PXP_CSC2_COEF1_B1(0x7db) |	/* -0.1445 (+0.37 %) */
			BF_PXP_CSC2_COEF1_A3(0x019),	/*  0.0977 (-0.02 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7b6),	/* -0.2891 (+0.20 %) */
			BF_PXP_CSC2_COEF3_C2(0x7a2) |	/* -0.3672 (+0.06 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7ee),	/* -0.0703 (+0.11 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * BT.601 full range:
		 *
		 * |Y |   | 0.2990  0.5870  0.1140|   |R|   |0  |
		 * |Cb| = |-0.1687 -0.3313  0.5000| * |G| + |128|
		 * |Cr|   | 0.5000  0.5000 -0.4187|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_bt601_full[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x096) |	/*  0.5859 (-0.11 %) */
			BF_PXP_CSC2_COEF0_A1(0x04c),	/*  0.2969 (-0.21 %) */
			BF_PXP_CSC2_COEF1_B1(0x7d5) |	/* -0.1680 (+0.07 %) */
			BF_PXP_CSC2_COEF1_A3(0x01d),	/*  0.1133 (-0.07 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x7ac),	/* -0.3281 (+0.32 %) */
			BF_PXP_CSC2_COEF3_C2(0x795) |	/* -0.4180 (+0.07 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7ec),	/* -0.0781 (+0.32 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * Rec.709 limited range:
		 *
		 * |Y |   | 0.1826  0.6142  0.0620|   |R|   |16 |
		 * |Cb| = |-0.1007 -0.3385  0.4392| * |G| + |128|
		 * |Cr|   | 0.4392  0.4392 -0.3990|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_rec709_lim[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x09d) |	/*  0.6133 (-0.09 %) */
			BF_PXP_CSC2_COEF0_A1(0x02e),	/*  0.1797 (-0.29 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e7) |	/* -0.0977 (+0.30 %) */
			BF_PXP_CSC2_COEF1_A3(0x00f),	/*  0.0586 (-0.34 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7aa),	/* -0.3359 (+0.26 %) */
			BF_PXP_CSC2_COEF3_C2(0x79a) |	/* -0.3984 (+0.05 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7f6),	/* -0.0391 (+0.12 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * Rec.709 full range:
		 *
		 * |Y |   | 0.2126  0.7152  0.0722|   |R|   |0  |
		 * |Cb| = |-0.1146 -0.3854  0.5000| * |G| + |128|
		 * |Cr|   | 0.5000  0.5000 -0.4542|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_rec709_full[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x0b7) |	/*  0.7148 (-0.04 %) */
			BF_PXP_CSC2_COEF0_A1(0x036),	/*  0.2109 (-0.17 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e3) |	/* -0.1133 (+0.13 %) */
			BF_PXP_CSC2_COEF1_A3(0x012),	/*  0.0703 (-0.19 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x79e),	/* -0.3828 (+0.26 %) */
			BF_PXP_CSC2_COEF3_C2(0x78c) |	/* -0.4531 (+0.11 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7f5),	/* -0.0430 (+0.28 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * BT.2020 limited range:
		 *
		 * |Y |   | 0.2256  0.5823  0.0509|   |R|   |16 |
		 * |Cb| = |-0.1226 -0.3166  0.4392| * |G| + |128|
		 * |Cr|   | 0.4392  0.4392 -0.4039|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_bt2020_lim[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x095) |	/*  0.5820 (-0.03 %) */
			BF_PXP_CSC2_COEF0_A1(0x039),	/*  0.2227 (-0.30 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e1) |	/* -0.1211 (+0.15 %) */
			BF_PXP_CSC2_COEF1_A3(0x00d),	/*  0.0508 (-0.01 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7af),	/* -0.3164 (+0.02 %) */
			BF_PXP_CSC2_COEF3_C2(0x799) |	/* -0.4023 (+0.16 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7f7),	/* -0.0352 (+0.02 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * BT.2020 full range:
		 *
		 * |Y |   | 0.2627  0.6780  0.0593|   |R|   |0  |
		 * |Cb| = |-0.1396 -0.3604  0.5000| * |G| + |128|
		 * |Cr|   | 0.5000  0.5000 -0.4598|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_bt2020_full[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x0ad) |	/*  0.6758 (-0.22 %) */
			BF_PXP_CSC2_COEF0_A1(0x043),	/*  0.2617 (-0.10 %) */
			BF_PXP_CSC2_COEF1_B1(0x7dd) |	/* -0.1367 (+0.29 %) */
			BF_PXP_CSC2_COEF1_A3(0x00f),	/*  0.0586 (-0.07 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x7a4),	/* -0.3594 (+0.10 %) */
			BF_PXP_CSC2_COEF3_C2(0x78b) |	/* -0.4570 (+0.28 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7f6),	/* -0.0391 (+0.11 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * SMPTE 240m limited range:
		 *
		 * |Y |   | 0.1821  0.6020  0.0747|   |R|   |16 |
		 * |Cb| = |-0.1019 -0.3373  0.4392| * |G| + |128|
		 * |Cr|   | 0.4392  0.4392 -0.3909|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_smpte240m_lim[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x09a) |	/*  0.6016 (-0.05 %) */
			BF_PXP_CSC2_COEF0_A1(0x02e),	/*  0.1797 (-0.24 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e6) |	/* -0.1016 (+0.03 %) */
			BF_PXP_CSC2_COEF1_A3(0x013),	/*  0.0742 (-0.05 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7aa),	/* -0.3359 (+0.14 %) */
			BF_PXP_CSC2_COEF3_C2(0x79c) |	/* -0.3906 (+0.03 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7f4),	/* -0.0469 (+0.14 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		/*
		 * SMPTE 240m full range:
		 *
		 * |Y |   | 0.2120  0.7010  0.0870|   |R|   |0  |
		 * |Cb| = |-0.1160 -0.3840  0.5000| * |G| + |128|
		 * |Cr|   | 0.5000  0.5000 -0.4450|   |B|   |128|
		 */
		अटल स्थिर u32 csc2_coef_smpte240m_full[6] = अणु
			BF_PXP_CSC2_COEF0_A2(0x0b3) |	/*  0.6992 (-0.18 %) */
			BF_PXP_CSC2_COEF0_A1(0x036),	/*  0.2109 (-0.11 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e3) |	/* -0.1133 (+0.27 %) */
			BF_PXP_CSC2_COEF1_A3(0x016),	/*  0.0859 (-0.11 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x79e),	/* -0.3828 (+0.12 %) */
			BF_PXP_CSC2_COEF3_C2(0x78f) |	/* -0.4414 (+0.36 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7f2),	/* -0.0547 (+0.03 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		पूर्ण;
		स्थिर u32 *csc2_coef;
		u32 csc2_ctrl;

		ycbcr_enc = ctx->q_data[V4L2_M2M_DST].ycbcr_enc;
		quantization = ctx->q_data[V4L2_M2M_DST].quant;

		अगर (ycbcr_enc == V4L2_YCBCR_ENC_601) अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc2_coef = csc2_coef_bt601_full;
			अन्यथा
				csc2_coef = csc2_coef_bt601_lim;
		पूर्ण अन्यथा अगर (ycbcr_enc == V4L2_YCBCR_ENC_709) अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc2_coef = csc2_coef_rec709_full;
			अन्यथा
				csc2_coef = csc2_coef_rec709_lim;
		पूर्ण अन्यथा अगर (ycbcr_enc == V4L2_YCBCR_ENC_BT2020) अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc2_coef = csc2_coef_bt2020_full;
			अन्यथा
				csc2_coef = csc2_coef_bt2020_lim;
		पूर्ण अन्यथा अणु
			अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE)
				csc2_coef = csc2_coef_smpte240m_full;
			अन्यथा
				csc2_coef = csc2_coef_smpte240m_lim;
		पूर्ण
		अगर (quantization == V4L2_QUANTIZATION_FULL_RANGE) अणु
			csc2_ctrl = BV_PXP_CSC2_CTRL_CSC_MODE__RGB2YUV <<
				    BP_PXP_CSC2_CTRL_CSC_MODE;
		पूर्ण अन्यथा अणु
			csc2_ctrl = BV_PXP_CSC2_CTRL_CSC_MODE__RGB2YCbCr <<
				    BP_PXP_CSC2_CTRL_CSC_MODE;
		पूर्ण

		ग_लिखोl(csc2_ctrl, dev->mmio + HW_PXP_CSC2_CTRL);
		ग_लिखोl(csc2_coef[0], dev->mmio + HW_PXP_CSC2_COEF0);
		ग_लिखोl(csc2_coef[1], dev->mmio + HW_PXP_CSC2_COEF1);
		ग_लिखोl(csc2_coef[2], dev->mmio + HW_PXP_CSC2_COEF2);
		ग_लिखोl(csc2_coef[3], dev->mmio + HW_PXP_CSC2_COEF3);
		ग_लिखोl(csc2_coef[4], dev->mmio + HW_PXP_CSC2_COEF4);
		ग_लिखोl(csc2_coef[5], dev->mmio + HW_PXP_CSC2_COEF5);
	पूर्ण अन्यथा अणु
		ग_लिखोl(BM_PXP_CSC2_CTRL_BYPASS, dev->mmio + HW_PXP_CSC2_CTRL);
	पूर्ण
पूर्ण

अटल पूर्णांक pxp_start(काष्ठा pxp_ctx *ctx, काष्ठा vb2_v4l2_buffer *in_vb,
		     काष्ठा vb2_v4l2_buffer *out_vb)
अणु
	काष्ठा pxp_dev *dev = ctx->dev;
	काष्ठा pxp_q_data *q_data;
	u32 src_width, src_height, src_stride, src_fourcc;
	u32 dst_width, dst_height, dst_stride, dst_fourcc;
	dma_addr_t p_in, p_out;
	u32 ctrl, out_ctrl, out_buf, out_buf2, out_pitch, out_lrc, out_ps_ulc;
	u32 out_ps_lrc;
	u32 ps_ctrl, ps_buf, ps_ubuf, ps_vbuf, ps_pitch, ps_scale, ps_offset;
	u32 as_ulc, as_lrc;
	u32 y_size;
	u32 decx, decy, xscale, yscale;

	q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

	src_width = ctx->q_data[V4L2_M2M_SRC].width;
	dst_width = ctx->q_data[V4L2_M2M_DST].width;
	src_height = ctx->q_data[V4L2_M2M_SRC].height;
	dst_height = ctx->q_data[V4L2_M2M_DST].height;
	src_stride = ctx->q_data[V4L2_M2M_SRC].bytesperline;
	dst_stride = ctx->q_data[V4L2_M2M_DST].bytesperline;
	src_fourcc = ctx->q_data[V4L2_M2M_SRC].fmt->fourcc;
	dst_fourcc = ctx->q_data[V4L2_M2M_DST].fmt->fourcc;

	p_in = vb2_dma_contig_plane_dma_addr(&in_vb->vb2_buf, 0);
	p_out = vb2_dma_contig_plane_dma_addr(&out_vb->vb2_buf, 0);

	अगर (!p_in || !p_out) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Acquiring DMA addresses of buffers failed\n");
		वापस -EFAULT;
	पूर्ण

	out_vb->sequence =
		get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE)->sequence++;
	in_vb->sequence = q_data->sequence++;
	out_vb->vb2_buf.बारtamp = in_vb->vb2_buf.बारtamp;

	अगर (in_vb->flags & V4L2_BUF_FLAG_TIMECODE)
		out_vb->समयcode = in_vb->समयcode;
	out_vb->field = in_vb->field;
	out_vb->flags = in_vb->flags &
		(V4L2_BUF_FLAG_TIMECODE |
		 V4L2_BUF_FLAG_KEYFRAME |
		 V4L2_BUF_FLAG_PFRAME |
		 V4L2_BUF_FLAG_BFRAME |
		 V4L2_BUF_FLAG_TSTAMP_SRC_MASK);

	/* Rotation disabled, 8x8 block size */
	ctrl = BF_PXP_CTRL_VFLIP0(!!(ctx->mode & MEM2MEM_VFLIP)) |
	       BF_PXP_CTRL_HFLIP0(!!(ctx->mode & MEM2MEM_HFLIP));
	/* Always ग_लिखो alpha value as V4L2_CID_ALPHA_COMPONENT */
	out_ctrl = BF_PXP_OUT_CTRL_ALPHA(ctx->alpha_component) |
		   BF_PXP_OUT_CTRL_ALPHA_OUTPUT(1) |
		   pxp_v4l2_pix_fmt_to_out_क्रमmat(dst_fourcc);
	out_buf = p_out;
	चयन (dst_fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		out_buf2 = out_buf + dst_stride * dst_height;
		अवरोध;
	शेष:
		out_buf2 = 0;
	पूर्ण

	out_pitch = BF_PXP_OUT_PITCH_PITCH(dst_stride);
	out_lrc = BF_PXP_OUT_LRC_X(dst_width - 1) |
		  BF_PXP_OUT_LRC_Y(dst_height - 1);
	/* PS covers whole output */
	out_ps_ulc = BF_PXP_OUT_PS_ULC_X(0) | BF_PXP_OUT_PS_ULC_Y(0);
	out_ps_lrc = BF_PXP_OUT_PS_LRC_X(dst_width - 1) |
		     BF_PXP_OUT_PS_LRC_Y(dst_height - 1);
	/* no AS */
	as_ulc = BF_PXP_OUT_AS_ULC_X(1) | BF_PXP_OUT_AS_ULC_Y(1);
	as_lrc = BF_PXP_OUT_AS_LRC_X(0) | BF_PXP_OUT_AS_LRC_Y(0);

	decx = (src_width <= dst_width) ? 0 : ilog2(src_width / dst_width);
	decy = (src_height <= dst_height) ? 0 : ilog2(src_height / dst_height);
	ps_ctrl = BF_PXP_PS_CTRL_DECX(decx) | BF_PXP_PS_CTRL_DECY(decy) |
		  pxp_v4l2_pix_fmt_to_ps_क्रमmat(src_fourcc);
	ps_buf = p_in;
	y_size = src_stride * src_height;
	चयन (src_fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = ps_ubuf + y_size / 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = ps_ubuf + y_size / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = 0;
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
	हाल V4L2_PIX_FMT_Y4:
		ps_ubuf = 0;
		/* In grayscale mode, ps_vbuf contents are reused as CbCr */
		ps_vbuf = 0x8080;
		अवरोध;
	शेष:
		ps_ubuf = 0;
		ps_vbuf = 0;
		अवरोध;
	पूर्ण
	ps_pitch = BF_PXP_PS_PITCH_PITCH(src_stride);
	अगर (decx) अणु
		xscale = (src_width >> decx) * 0x1000 / dst_width;
	पूर्ण अन्यथा अणु
		चयन (src_fourcc) अणु
		हाल V4L2_PIX_FMT_UYVY:
		हाल V4L2_PIX_FMT_YUYV:
		हाल V4L2_PIX_FMT_VYUY:
		हाल V4L2_PIX_FMT_YVYU:
		हाल V4L2_PIX_FMT_NV16:
		हाल V4L2_PIX_FMT_NV12:
		हाल V4L2_PIX_FMT_NV21:
		हाल V4L2_PIX_FMT_NV61:
		हाल V4L2_PIX_FMT_YUV422P:
		हाल V4L2_PIX_FMT_YUV420:
			/*
			 * This aव्योमs sampling past the right edge क्रम
			 * horizontally chroma subsampled क्रमmats.
			 */
			xscale = (src_width - 2) * 0x1000 / (dst_width - 1);
			अवरोध;
		शेष:
			xscale = (src_width - 1) * 0x1000 / (dst_width - 1);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (decy)
		yscale = (src_height >> decy) * 0x1000 / dst_height;
	अन्यथा
		yscale = (src_height - 1) * 0x1000 / (dst_height - 1);
	ps_scale = BF_PXP_PS_SCALE_YSCALE(yscale) |
		   BF_PXP_PS_SCALE_XSCALE(xscale);
	ps_offset = BF_PXP_PS_OFFSET_YOFFSET(0) | BF_PXP_PS_OFFSET_XOFFSET(0);

	ग_लिखोl(ctrl, dev->mmio + HW_PXP_CTRL);
	/* skip STAT */
	ग_लिखोl(out_ctrl, dev->mmio + HW_PXP_OUT_CTRL);
	ग_लिखोl(out_buf, dev->mmio + HW_PXP_OUT_BUF);
	ग_लिखोl(out_buf2, dev->mmio + HW_PXP_OUT_BUF2);
	ग_लिखोl(out_pitch, dev->mmio + HW_PXP_OUT_PITCH);
	ग_लिखोl(out_lrc, dev->mmio + HW_PXP_OUT_LRC);
	ग_लिखोl(out_ps_ulc, dev->mmio + HW_PXP_OUT_PS_ULC);
	ग_लिखोl(out_ps_lrc, dev->mmio + HW_PXP_OUT_PS_LRC);
	ग_लिखोl(as_ulc, dev->mmio + HW_PXP_OUT_AS_ULC);
	ग_लिखोl(as_lrc, dev->mmio + HW_PXP_OUT_AS_LRC);
	ग_लिखोl(ps_ctrl, dev->mmio + HW_PXP_PS_CTRL);
	ग_लिखोl(ps_buf, dev->mmio + HW_PXP_PS_BUF);
	ग_लिखोl(ps_ubuf, dev->mmio + HW_PXP_PS_UBUF);
	ग_लिखोl(ps_vbuf, dev->mmio + HW_PXP_PS_VBUF);
	ग_लिखोl(ps_pitch, dev->mmio + HW_PXP_PS_PITCH);
	ग_लिखोl(0x00ffffff, dev->mmio + HW_PXP_PS_BACKGROUND_0);
	ग_लिखोl(ps_scale, dev->mmio + HW_PXP_PS_SCALE);
	ग_लिखोl(ps_offset, dev->mmio + HW_PXP_PS_OFFSET);
	/* disable processed surface color keying */
	ग_लिखोl(0x00ffffff, dev->mmio + HW_PXP_PS_CLRKEYLOW_0);
	ग_लिखोl(0x00000000, dev->mmio + HW_PXP_PS_CLRKEYHIGH_0);

	/* disable alpha surface color keying */
	ग_लिखोl(0x00ffffff, dev->mmio + HW_PXP_AS_CLRKEYLOW_0);
	ग_लिखोl(0x00000000, dev->mmio + HW_PXP_AS_CLRKEYHIGH_0);

	/* setup CSC */
	pxp_setup_csc(ctx);

	/* bypass LUT */
	ग_लिखोl(BM_PXP_LUT_CTRL_BYPASS, dev->mmio + HW_PXP_LUT_CTRL);

	ग_लिखोl(BF_PXP_DATA_PATH_CTRL0_MUX15_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX14_SEL(1)|
	       BF_PXP_DATA_PATH_CTRL0_MUX13_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX12_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX11_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX10_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX9_SEL(1)|
	       BF_PXP_DATA_PATH_CTRL0_MUX8_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX7_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX6_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX5_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX4_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX3_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX2_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX1_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX0_SEL(0),
	       dev->mmio + HW_PXP_DATA_PATH_CTRL0);
	ग_लिखोl(BF_PXP_DATA_PATH_CTRL1_MUX17_SEL(1) |
	       BF_PXP_DATA_PATH_CTRL1_MUX16_SEL(1),
	       dev->mmio + HW_PXP_DATA_PATH_CTRL1);

	ग_लिखोl(0xffff, dev->mmio + HW_PXP_IRQ_MASK);

	/* ungate, enable PS/AS/OUT and PXP operation */
	ग_लिखोl(BM_PXP_CTRL_IRQ_ENABLE, dev->mmio + HW_PXP_CTRL_SET);
	ग_लिखोl(BM_PXP_CTRL_ENABLE | BM_PXP_CTRL_ENABLE_CSC2 |
	       BM_PXP_CTRL_ENABLE_LUT | BM_PXP_CTRL_ENABLE_ROTATE0 |
	       BM_PXP_CTRL_ENABLE_PS_AS_OUT, dev->mmio + HW_PXP_CTRL_SET);

	वापस 0;
पूर्ण

अटल व्योम pxp_job_finish(काष्ठा pxp_dev *dev)
अणु
	काष्ठा pxp_ctx *curr_ctx;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;
	अचिन्हित दीर्घ flags;

	curr_ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);

	अगर (curr_ctx == शून्य) अणु
		pr_err("Instance released before the end of transaction\n");
		वापस;
	पूर्ण

	src_vb = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	spin_lock_irqsave(&dev->irqlock, flags);
	v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_DONE);
	spin_unlock_irqrestore(&dev->irqlock, flags);

	dprपूर्णांकk(curr_ctx->dev, "Finishing transaction\n");
	v4l2_m2m_job_finish(dev->m2m_dev, curr_ctx->fh.m2m_ctx);
पूर्ण

/*
 * mem2mem callbacks
 */
अटल व्योम pxp_device_run(व्योम *priv)
अणु
	काष्ठा pxp_ctx *ctx = priv;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	pxp_start(ctx, src_buf, dst_buf);
पूर्ण

अटल पूर्णांक pxp_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा pxp_ctx *ctx = priv;

	अगर (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) < 1 ||
	    v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx) < 1) अणु
		dprपूर्णांकk(ctx->dev, "Not enough buffers available\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम pxp_job_पात(व्योम *priv)
अणु
	काष्ठा pxp_ctx *ctx = priv;

	/* Will cancel the transaction in the next पूर्णांकerrupt handler */
	ctx->पातing = 1;
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t pxp_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxp_dev *dev = dev_id;
	u32 stat;

	stat = पढ़ोl(dev->mmio + HW_PXP_STAT);

	अगर (stat & BM_PXP_STAT_IRQ0) अणु
		/* we expect x = 0, y = height, irq0 = 1 */
		अगर (stat & ~(BM_PXP_STAT_BLOCKX | BM_PXP_STAT_BLOCKY |
			     BM_PXP_STAT_IRQ0))
			dprपूर्णांकk(dev, "%s: stat = 0x%08x\n", __func__, stat);
		ग_लिखोl(BM_PXP_STAT_IRQ0, dev->mmio + HW_PXP_STAT_CLR);

		pxp_job_finish(dev);
	पूर्ण अन्यथा अणु
		u32 irq = पढ़ोl(dev->mmio + HW_PXP_IRQ);

		dprपूर्णांकk(dev, "%s: stat = 0x%08x\n", __func__, stat);
		dprपूर्णांकk(dev, "%s: irq = 0x%08x\n", __func__, irq);

		ग_लिखोl(irq, dev->mmio + HW_PXP_IRQ_CLR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * video ioctls
 */
अटल पूर्णांक pxp_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, MEM2MEM_NAME, माप(cap->driver));
	strscpy(cap->card, MEM2MEM_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
			"platform:%s", MEM2MEM_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक pxp_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num;
	काष्ठा pxp_fmt *fmt;

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

अटल पूर्णांक pxp_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	वापस pxp_क्रमागत_fmt(f, MEM2MEM_CAPTURE);
पूर्ण

अटल पूर्णांक pxp_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	वापस pxp_क्रमागत_fmt(f, MEM2MEM_OUTPUT);
पूर्ण

अटल पूर्णांक pxp_g_fmt(काष्ठा pxp_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा pxp_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.field	= V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat	= q_data->fmt->fourcc;
	f->fmt.pix.bytesperline	= q_data->bytesperline;
	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.colorspace	= ctx->colorspace;
	f->fmt.pix.xfer_func	= ctx->xfer_func;
	f->fmt.pix.ycbcr_enc	= q_data->ycbcr_enc;
	f->fmt.pix.quantization	= q_data->quant;

	वापस 0;
पूर्ण

अटल पूर्णांक pxp_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस pxp_g_fmt(file2ctx(file), f);
पूर्ण

अटल पूर्णांक pxp_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस pxp_g_fmt(file2ctx(file), f);
पूर्ण

अटल अंतरभूत u32 pxp_bytesperline(काष्ठा pxp_fmt *fmt, u32 width)
अणु
	चयन (fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		वापस width;
	शेष:
		वापस (width * fmt->depth) >> 3;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 pxp_sizeimage(काष्ठा pxp_fmt *fmt, u32 width, u32 height)
अणु
	वापस (fmt->depth * width * height) >> 3;
पूर्ण

अटल पूर्णांक pxp_try_fmt(काष्ठा v4l2_क्रमmat *f, काष्ठा pxp_fmt *fmt)
अणु
	v4l_bound_align_image(&f->fmt.pix.width, MIN_W, MAX_W, ALIGN_W,
			      &f->fmt.pix.height, MIN_H, MAX_H, ALIGN_H, 0);

	f->fmt.pix.bytesperline = pxp_bytesperline(fmt, f->fmt.pix.width);
	f->fmt.pix.sizeimage = pxp_sizeimage(fmt, f->fmt.pix.width,
					     f->fmt.pix.height);
	f->fmt.pix.field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल व्योम
pxp_fixup_colorimetry_cap(काष्ठा pxp_ctx *ctx, u32 dst_fourcc,
			  क्रमागत v4l2_ycbcr_encoding *ycbcr_enc,
			  क्रमागत v4l2_quantization *quantization)
अणु
	bool dst_is_yuv = pxp_v4l2_pix_fmt_is_yuv(dst_fourcc);

	अगर (pxp_v4l2_pix_fmt_is_yuv(ctx->q_data[V4L2_M2M_SRC].fmt->fourcc) ==
	    dst_is_yuv) अणु
		/*
		 * There is no support क्रम conversion between dअगरferent YCbCr
		 * encodings or between RGB limited and full range.
		 */
		*ycbcr_enc = ctx->q_data[V4L2_M2M_SRC].ycbcr_enc;
		*quantization = ctx->q_data[V4L2_M2M_SRC].quant;
	पूर्ण अन्यथा अणु
		*ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(ctx->colorspace);
		*quantization = V4L2_MAP_QUANTIZATION_DEFAULT(!dst_is_yuv,
							      ctx->colorspace,
							      *ycbcr_enc);
	पूर्ण
पूर्ण

अटल पूर्णांक pxp_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxp_fmt *fmt;
	काष्ठा pxp_ctx *ctx = file2ctx(file);

	fmt = find_क्रमmat(f);
	अगर (!fmt) अणु
		f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
		fmt = find_क्रमmat(f);
	पूर्ण
	अगर (!(fmt->types & MEM2MEM_CAPTURE)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	f->fmt.pix.colorspace = ctx->colorspace;
	f->fmt.pix.xfer_func = ctx->xfer_func;

	pxp_fixup_colorimetry_cap(ctx, fmt->fourcc,
				  &f->fmt.pix.ycbcr_enc,
				  &f->fmt.pix.quantization);

	वापस pxp_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक pxp_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxp_fmt *fmt;
	काष्ठा pxp_ctx *ctx = file2ctx(file);

	fmt = find_क्रमmat(f);
	अगर (!fmt) अणु
		f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
		fmt = find_क्रमmat(f);
	पूर्ण
	अगर (!(fmt->types & MEM2MEM_OUTPUT)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (!f->fmt.pix.colorspace)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	वापस pxp_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक pxp_s_fmt(काष्ठा pxp_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxp_q_data *q_data;
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

	q_data->fmt		= find_क्रमmat(f);
	q_data->width		= f->fmt.pix.width;
	q_data->height		= f->fmt.pix.height;
	q_data->bytesperline	= f->fmt.pix.bytesperline;
	q_data->sizeimage	= f->fmt.pix.sizeimage;

	dprपूर्णांकk(ctx->dev,
		"Setting format for type %d, wxh: %dx%d, fmt: %d\n",
		f->type, q_data->width, q_data->height, q_data->fmt->fourcc);

	वापस 0;
पूर्ण

अटल पूर्णांक pxp_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxp_ctx *ctx = file2ctx(file);
	पूर्णांक ret;

	ret = pxp_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	ret = pxp_s_fmt(file2ctx(file), f);
	अगर (ret)
		वापस ret;

	ctx->q_data[V4L2_M2M_DST].ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->q_data[V4L2_M2M_DST].quant = f->fmt.pix.quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक pxp_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pxp_ctx *ctx = file2ctx(file);
	पूर्णांक ret;

	ret = pxp_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	ret = pxp_s_fmt(file2ctx(file), f);
	अगर (ret)
		वापस ret;

	ctx->colorspace = f->fmt.pix.colorspace;
	ctx->xfer_func = f->fmt.pix.xfer_func;
	ctx->q_data[V4L2_M2M_SRC].ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->q_data[V4L2_M2M_SRC].quant = f->fmt.pix.quantization;

	pxp_fixup_colorimetry_cap(ctx, ctx->q_data[V4L2_M2M_DST].fmt->fourcc,
				  &ctx->q_data[V4L2_M2M_DST].ycbcr_enc,
				  &ctx->q_data[V4L2_M2M_DST].quant);

	वापस 0;
पूर्ण

अटल पूर्णांक pxp_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा pxp_ctx *ctx =
		container_of(ctrl->handler, काष्ठा pxp_ctx, hdl);

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

	हाल V4L2_CID_ALPHA_COMPONENT:
		ctx->alpha_component = ctrl->val;
		अवरोध;

	शेष:
		v4l2_err(&ctx->dev->v4l2_dev, "Invalid control\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops pxp_ctrl_ops = अणु
	.s_ctrl = pxp_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops pxp_ioctl_ops = अणु
	.vidioc_querycap	= pxp_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = pxp_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= pxp_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= pxp_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= pxp_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out = pxp_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= pxp_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out	= pxp_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= pxp_s_fmt_vid_out,

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
अटल पूर्णांक pxp_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा pxp_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा pxp_q_data *q_data;
	अचिन्हित पूर्णांक size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	size = q_data->sizeimage;

	*nbuffers = count;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dprपूर्णांकk(ctx->dev, "get %d buffer(s) of size %d each.\n", count, size);

	वापस 0;
पूर्ण

अटल पूर्णांक pxp_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा pxp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा pxp_dev *dev = ctx->dev;
	काष्ठा pxp_q_data *q_data;

	dprपूर्णांकk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			dprपूर्णांकk(dev, "%s field isn't supported\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (vb2_plane_size(vb, 0) < q_data->sizeimage) अणु
		dprपूर्णांकk(dev, "%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0),
			(दीर्घ)q_data->sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, q_data->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम pxp_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा pxp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक pxp_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा pxp_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा pxp_q_data *q_data = get_q_data(ctx, q->type);

	q_data->sequence = 0;
	वापस 0;
पूर्ण

अटल व्योम pxp_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा pxp_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;
	अचिन्हित दीर्घ flags;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (vbuf == शून्य)
			वापस;
		spin_lock_irqsave(&ctx->dev->irqlock, flags);
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&ctx->dev->irqlock, flags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops pxp_qops = अणु
	.queue_setup	 = pxp_queue_setup,
	.buf_prepare	 = pxp_buf_prepare,
	.buf_queue	 = pxp_buf_queue,
	.start_streaming = pxp_start_streaming,
	.stop_streaming  = pxp_stop_streaming,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा pxp_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &pxp_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->dev->dev_mutex;
	src_vq->dev = ctx->dev->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &pxp_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

/*
 * File operations
 */
अटल पूर्णांक pxp_खोलो(काष्ठा file *file)
अणु
	काष्ठा pxp_dev *dev = video_drvdata(file);
	काष्ठा pxp_ctx *ctx = शून्य;
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
	v4l2_ctrl_new_std(hdl, &pxp_ctrl_ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &pxp_ctrl_ops, V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &pxp_ctrl_ops, V4L2_CID_ALPHA_COMPONENT,
			  0, 255, 1, 255);
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
	ctx->q_data[V4L2_M2M_SRC].bytesperline =
		pxp_bytesperline(&क्रमmats[0], 640);
	ctx->q_data[V4L2_M2M_SRC].sizeimage =
		pxp_sizeimage(&क्रमmats[0], 640, 480);
	ctx->q_data[V4L2_M2M_DST] = ctx->q_data[V4L2_M2M_SRC];
	ctx->colorspace = V4L2_COLORSPACE_REC709;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		rc = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_मुक्त(hdl);
		v4l2_fh_निकास(&ctx->fh);
		kमुक्त(ctx);
		जाओ खोलो_unlock;
	पूर्ण

	v4l2_fh_add(&ctx->fh);
	atomic_inc(&dev->num_inst);

	dprपूर्णांकk(dev, "Created instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

खोलो_unlock:
	mutex_unlock(&dev->dev_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक pxp_release(काष्ठा file *file)
अणु
	काष्ठा pxp_dev *dev = video_drvdata(file);
	काष्ठा pxp_ctx *ctx = file2ctx(file);

	dprपूर्णांकk(dev, "Releasing instance %p\n", ctx);

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

अटल स्थिर काष्ठा v4l2_file_operations pxp_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= pxp_खोलो,
	.release	= pxp_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device pxp_videodev = अणु
	.name		= MEM2MEM_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &pxp_fops,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
	.ioctl_ops	= &pxp_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= pxp_device_run,
	.job_पढ़ोy	= pxp_job_पढ़ोy,
	.job_पात	= pxp_job_पात,
पूर्ण;

अटल पूर्णांक pxp_soft_reset(काष्ठा pxp_dev *dev)
अणु
	पूर्णांक ret;
	u32 val;

	ग_लिखोl(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_CLR);
	ग_लिखोl(BM_PXP_CTRL_CLKGATE, dev->mmio + HW_PXP_CTRL_CLR);

	ग_लिखोl(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_SET);

	ret = पढ़ोl_poll_समयout(dev->mmio + HW_PXP_CTRL, val,
				 val & BM_PXP_CTRL_CLKGATE, 0, 100);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_CLR);
	ग_लिखोl(BM_PXP_CTRL_CLKGATE, dev->mmio + HW_PXP_CTRL_CLR);

	वापस 0;
पूर्ण

अटल पूर्णांक pxp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxp_dev *dev;
	काष्ठा resource *res;
	काष्ठा video_device *vfd;
	पूर्णांक irq;
	पूर्णांक ret;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->clk = devm_clk_get(&pdev->dev, "axi");
	अगर (IS_ERR(dev->clk)) अणु
		ret = PTR_ERR(dev->clk);
		dev_err(&pdev->dev, "Failed to get clk: %d\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dev->mmio))
		वापस PTR_ERR(dev->mmio);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, pxp_irq_handler,
			IRQF_ONESHOT, dev_name(&pdev->dev), dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dev->clk);
	अगर (ret < 0)
		वापस ret;

	ret = pxp_soft_reset(dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "PXP reset timeout: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	spin_lock_init(&dev->irqlock);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		जाओ err_clk;

	atomic_set(&dev->num_inst, 0);
	mutex_init(&dev->dev_mutex);

	dev->vfd = pxp_videodev;
	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	video_set_drvdata(vfd, dev);
	snम_लिखो(vfd->name, माप(vfd->name), "%s", pxp_videodev.name);
	v4l2_info(&dev->v4l2_dev,
			"Device registered as /dev/video%d\n", vfd->num);

	platक्रमm_set_drvdata(pdev, dev);

	dev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		जाओ err_v4l2;
	पूर्ण

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		जाओ err_m2m;
	पूर्ण

	वापस 0;

err_m2m:
	v4l2_m2m_release(dev->m2m_dev);
err_v4l2:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_clk:
	clk_disable_unprepare(dev->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक pxp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxp_dev *dev = platक्रमm_get_drvdata(pdev);

	ग_लिखोl(BM_PXP_CTRL_CLKGATE, dev->mmio + HW_PXP_CTRL_SET);
	ग_लिखोl(BM_PXP_CTRL_SFTRST, dev->mmio + HW_PXP_CTRL_SET);

	clk_disable_unprepare(dev->clk);

	v4l2_info(&dev->v4l2_dev, "Removing " MEM2MEM_NAME);
	video_unरेजिस्टर_device(&dev->vfd);
	v4l2_m2m_release(dev->m2m_dev);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pxp_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6ull-pxp", .data = शून्य पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxp_dt_ids);

अटल काष्ठा platक्रमm_driver pxp_driver = अणु
	.probe		= pxp_probe,
	.हटाओ		= pxp_हटाओ,
	.driver		= अणु
		.name	= MEM2MEM_NAME,
		.of_match_table = pxp_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxp_driver);

MODULE_DESCRIPTION("i.MX PXP mem2mem scaler/CSC/rotator");
MODULE_AUTHOR("Philipp Zabel <kernel@pengutronix.de>");
MODULE_LICENSE("GPL");
