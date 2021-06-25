<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors:
 *	Eunchul Kim <chulspro.kim@samsung.com>
 *	Jinyoung Jeon <jy0.jeon@samsung.com>
 *	Sangmin Lee <lsmin.lee@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_ipp.h"
#समावेश "regs-fimc.h"

/*
 * FIMC stands क्रम Fully Interactive Mobile Camera and
 * supports image scaler/rotator and input/output DMA operations.
 * input DMA पढ़ोs image data from the memory.
 * output DMA ग_लिखोs image data to memory.
 * FIMC supports image rotation and image effect functions.
 */

#घोषणा FIMC_MAX_DEVS	4
#घोषणा FIMC_MAX_SRC	2
#घोषणा FIMC_MAX_DST	32
#घोषणा FIMC_SHFACTOR	10
#घोषणा FIMC_BUF_STOP	1
#घोषणा FIMC_BUF_START	2
#घोषणा FIMC_WIDTH_ITU_709	1280
#घोषणा FIMC_AUTOSUSPEND_DELAY	2000

अटल अचिन्हित पूर्णांक fimc_mask = 0xc;
module_param_named(fimc_devs, fimc_mask, uपूर्णांक, 0644);
MODULE_PARM_DESC(fimc_devs, "Alias mask for assigning FIMC devices to Exynos DRM");

#घोषणा get_fimc_context(dev)	dev_get_drvdata(dev)

क्रमागत अणु
	FIMC_CLK_LCLK,
	FIMC_CLK_GATE,
	FIMC_CLK_WB_A,
	FIMC_CLK_WB_B,
	FIMC_CLKS_MAX
पूर्ण;

अटल स्थिर अक्षर * स्थिर fimc_घड़ी_names[] = अणु
	[FIMC_CLK_LCLK]   = "sclk_fimc",
	[FIMC_CLK_GATE]   = "fimc",
	[FIMC_CLK_WB_A]   = "pxl_async0",
	[FIMC_CLK_WB_B]   = "pxl_async1",
पूर्ण;

/*
 * A काष्ठाure of scaler.
 *
 * @range: narrow, wide.
 * @bypass: unused scaler path.
 * @up_h: horizontal scale up.
 * @up_v: vertical scale up.
 * @hratio: horizontal ratio.
 * @vratio: vertical ratio.
 */
काष्ठा fimc_scaler अणु
	bool range;
	bool bypass;
	bool up_h;
	bool up_v;
	u32 hratio;
	u32 vratio;
पूर्ण;

/*
 * A काष्ठाure of fimc context.
 *
 * @regs_res: रेजिस्टर resources.
 * @regs: memory mapped io रेजिस्टरs.
 * @lock: locking of operations.
 * @घड़ीs: fimc घड़ीs.
 * @sc: scaler infomations.
 * @pol: porarity of ग_लिखोback.
 * @id: fimc id.
 * @irq: irq number.
 */
काष्ठा fimc_context अणु
	काष्ठा exynos_drm_ipp ipp;
	काष्ठा drm_device *drm_dev;
	व्योम		*dma_priv;
	काष्ठा device	*dev;
	काष्ठा exynos_drm_ipp_task	*task;
	काष्ठा exynos_drm_ipp_क्रमmats	*क्रमmats;
	अचिन्हित पूर्णांक			num_क्रमmats;

	काष्ठा resource	*regs_res;
	व्योम __iomem	*regs;
	spinlock_t	lock;
	काष्ठा clk	*घड़ीs[FIMC_CLKS_MAX];
	काष्ठा fimc_scaler	sc;
	पूर्णांक	id;
	पूर्णांक	irq;
पूर्ण;

अटल u32 fimc_पढ़ो(काष्ठा fimc_context *ctx, u32 reg)
अणु
	वापस पढ़ोl(ctx->regs + reg);
पूर्ण

अटल व्योम fimc_ग_लिखो(काष्ठा fimc_context *ctx, u32 val, u32 reg)
अणु
	ग_लिखोl(val, ctx->regs + reg);
पूर्ण

अटल व्योम fimc_set_bits(काष्ठा fimc_context *ctx, u32 reg, u32 bits)
अणु
	व्योम __iomem *r = ctx->regs + reg;

	ग_लिखोl(पढ़ोl(r) | bits, r);
पूर्ण

अटल व्योम fimc_clear_bits(काष्ठा fimc_context *ctx, u32 reg, u32 bits)
अणु
	व्योम __iomem *r = ctx->regs + reg;

	ग_लिखोl(पढ़ोl(r) & ~bits, r);
पूर्ण

अटल व्योम fimc_sw_reset(काष्ठा fimc_context *ctx)
अणु
	u32 cfg;

	/* stop dma operation */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CISTATUS);
	अगर (EXYNOS_CISTATUS_GET_ENVID_STATUS(cfg))
		fimc_clear_bits(ctx, EXYNOS_MSCTRL, EXYNOS_MSCTRL_ENVID);

	fimc_set_bits(ctx, EXYNOS_CISRCFMT, EXYNOS_CISRCFMT_ITU601_8BIT);

	/* disable image capture */
	fimc_clear_bits(ctx, EXYNOS_CIIMGCPT,
		EXYNOS_CIIMGCPT_IMGCPTEN_SC | EXYNOS_CIIMGCPT_IMGCPTEN);

	/* s/w reset */
	fimc_set_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_SWRST);

	/* s/w reset complete */
	fimc_clear_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_SWRST);

	/* reset sequence */
	fimc_ग_लिखो(ctx, 0x0, EXYNOS_CIFCNTSEQ);
पूर्ण

अटल व्योम fimc_set_type_ctrl(काष्ठा fimc_context *ctx)
अणु
	u32 cfg;

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIGCTRL);
	cfg &= ~(EXYNOS_CIGCTRL_TESTPATTERN_MASK |
		EXYNOS_CIGCTRL_SELCAM_ITU_MASK |
		EXYNOS_CIGCTRL_SELCAM_MIPI_MASK |
		EXYNOS_CIGCTRL_SELCAM_FIMC_MASK |
		EXYNOS_CIGCTRL_SELWB_CAMIF_MASK |
		EXYNOS_CIGCTRL_SELWRITEBACK_MASK);

	cfg |= (EXYNOS_CIGCTRL_SELCAM_ITU_A |
		EXYNOS_CIGCTRL_SELWRITEBACK_A |
		EXYNOS_CIGCTRL_SELCAM_MIPI_A |
		EXYNOS_CIGCTRL_SELCAM_FIMC_ITU);

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIGCTRL);
पूर्ण

अटल व्योम fimc_handle_jpeg(काष्ठा fimc_context *ctx, bool enable)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "enable[%d]\n", enable);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIGCTRL);
	अगर (enable)
		cfg |= EXYNOS_CIGCTRL_CAM_JPEG;
	अन्यथा
		cfg &= ~EXYNOS_CIGCTRL_CAM_JPEG;

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIGCTRL);
पूर्ण

अटल व्योम fimc_mask_irq(काष्ठा fimc_context *ctx, bool enable)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "enable[%d]\n", enable);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIGCTRL);
	अगर (enable) अणु
		cfg &= ~EXYNOS_CIGCTRL_IRQ_OVFEN;
		cfg |= EXYNOS_CIGCTRL_IRQ_ENABLE | EXYNOS_CIGCTRL_IRQ_LEVEL;
	पूर्ण अन्यथा
		cfg &= ~EXYNOS_CIGCTRL_IRQ_ENABLE;
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIGCTRL);
पूर्ण

अटल व्योम fimc_clear_irq(काष्ठा fimc_context *ctx)
अणु
	fimc_set_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_IRQ_CLR);
पूर्ण

अटल bool fimc_check_ovf(काष्ठा fimc_context *ctx)
अणु
	u32 status, flag;

	status = fimc_पढ़ो(ctx, EXYNOS_CISTATUS);
	flag = EXYNOS_CISTATUS_OVFIY | EXYNOS_CISTATUS_OVFICB |
		EXYNOS_CISTATUS_OVFICR;

	DRM_DEV_DEBUG_KMS(ctx->dev, "flag[0x%x]\n", flag);

	अगर (status & flag) अणु
		fimc_set_bits(ctx, EXYNOS_CIWDOFST,
			EXYNOS_CIWDOFST_CLROVFIY | EXYNOS_CIWDOFST_CLROVFICB |
			EXYNOS_CIWDOFST_CLROVFICR);

		DRM_DEV_ERROR(ctx->dev,
			      "occurred overflow at %d, status 0x%x.\n",
			      ctx->id, status);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool fimc_check_frame_end(काष्ठा fimc_context *ctx)
अणु
	u32 cfg;

	cfg = fimc_पढ़ो(ctx, EXYNOS_CISTATUS);

	DRM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]\n", cfg);

	अगर (!(cfg & EXYNOS_CISTATUS_FRAMEEND))
		वापस false;

	cfg &= ~(EXYNOS_CISTATUS_FRAMEEND);
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CISTATUS);

	वापस true;
पूर्ण

अटल पूर्णांक fimc_get_buf_id(काष्ठा fimc_context *ctx)
अणु
	u32 cfg;
	पूर्णांक frame_cnt, buf_id;

	cfg = fimc_पढ़ो(ctx, EXYNOS_CISTATUS2);
	frame_cnt = EXYNOS_CISTATUS2_GET_FRAMECOUNT_BEFORE(cfg);

	अगर (frame_cnt == 0)
		frame_cnt = EXYNOS_CISTATUS2_GET_FRAMECOUNT_PRESENT(cfg);

	DRM_DEV_DEBUG_KMS(ctx->dev, "present[%d]before[%d]\n",
			  EXYNOS_CISTATUS2_GET_FRAMECOUNT_PRESENT(cfg),
			  EXYNOS_CISTATUS2_GET_FRAMECOUNT_BEFORE(cfg));

	अगर (frame_cnt == 0) अणु
		DRM_DEV_ERROR(ctx->dev, "failed to get frame count.\n");
		वापस -EIO;
	पूर्ण

	buf_id = frame_cnt - 1;
	DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]\n", buf_id);

	वापस buf_id;
पूर्ण

अटल व्योम fimc_handle_lastend(काष्ठा fimc_context *ctx, bool enable)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "enable[%d]\n", enable);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIOCTRL);
	अगर (enable)
		cfg |= EXYNOS_CIOCTRL_LASTENDEN;
	अन्यथा
		cfg &= ~EXYNOS_CIOCTRL_LASTENDEN;

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIOCTRL);
पूर्ण

अटल व्योम fimc_src_set_fmt_order(काष्ठा fimc_context *ctx, u32 fmt)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	/* RGB */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CISCCTRL);
	cfg &= ~EXYNOS_CISCCTRL_INRGB_FMT_RGB_MASK;

	चयन (fmt) अणु
	हाल DRM_FORMAT_RGB565:
		cfg |= EXYNOS_CISCCTRL_INRGB_FMT_RGB565;
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCCTRL);
		वापस;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_XRGB8888:
		cfg |= EXYNOS_CISCCTRL_INRGB_FMT_RGB888;
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCCTRL);
		वापस;
	शेष:
		/* bypass */
		अवरोध;
	पूर्ण

	/* YUV */
	cfg = fimc_पढ़ो(ctx, EXYNOS_MSCTRL);
	cfg &= ~(EXYNOS_MSCTRL_ORDER2P_SHIFT_MASK |
		EXYNOS_MSCTRL_C_INT_IN_2PLANE |
		EXYNOS_MSCTRL_ORDER422_YCBYCR);

	चयन (fmt) अणु
	हाल DRM_FORMAT_YUYV:
		cfg |= EXYNOS_MSCTRL_ORDER422_YCBYCR;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		cfg |= EXYNOS_MSCTRL_ORDER422_YCRYCB;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		cfg |= EXYNOS_MSCTRL_ORDER422_CBYCRY;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
	हाल DRM_FORMAT_YUV444:
		cfg |= EXYNOS_MSCTRL_ORDER422_CRYCBY;
		अवरोध;
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV61:
		cfg |= (EXYNOS_MSCTRL_ORDER2P_LSB_CRCB |
			EXYNOS_MSCTRL_C_INT_IN_2PLANE);
		अवरोध;
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
		cfg |= EXYNOS_MSCTRL_C_INT_IN_3PLANE;
		अवरोध;
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
		cfg |= (EXYNOS_MSCTRL_ORDER2P_LSB_CBCR |
			EXYNOS_MSCTRL_C_INT_IN_2PLANE);
		अवरोध;
	पूर्ण

	fimc_ग_लिखो(ctx, cfg, EXYNOS_MSCTRL);
पूर्ण

अटल व्योम fimc_src_set_fmt(काष्ठा fimc_context *ctx, u32 fmt, bool tiled)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = fimc_पढ़ो(ctx, EXYNOS_MSCTRL);
	cfg &= ~EXYNOS_MSCTRL_INFORMAT_RGB;

	चयन (fmt) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_XRGB8888:
		cfg |= EXYNOS_MSCTRL_INFORMAT_RGB;
		अवरोध;
	हाल DRM_FORMAT_YUV444:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR420;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR422_1PLANE;
		अवरोध;
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV61:
	हाल DRM_FORMAT_YUV422:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR422;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV21:
		cfg |= EXYNOS_MSCTRL_INFORMAT_YCBCR420;
		अवरोध;
	पूर्ण

	fimc_ग_लिखो(ctx, cfg, EXYNOS_MSCTRL);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIDMAPARAM);
	cfg &= ~EXYNOS_CIDMAPARAM_R_MODE_MASK;

	अगर (tiled)
		cfg |= EXYNOS_CIDMAPARAM_R_MODE_64X32;
	अन्यथा
		cfg |= EXYNOS_CIDMAPARAM_R_MODE_LINEAR;

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIDMAPARAM);

	fimc_src_set_fmt_order(ctx, fmt);
पूर्ण

अटल व्योम fimc_src_set_transf(काष्ठा fimc_context *ctx, अचिन्हित पूर्णांक rotation)
अणु
	अचिन्हित पूर्णांक degree = rotation & DRM_MODE_ROTATE_MASK;
	u32 cfg1, cfg2;

	DRM_DEV_DEBUG_KMS(ctx->dev, "rotation[%x]\n", rotation);

	cfg1 = fimc_पढ़ो(ctx, EXYNOS_MSCTRL);
	cfg1 &= ~(EXYNOS_MSCTRL_FLIP_X_MIRROR |
		EXYNOS_MSCTRL_FLIP_Y_MIRROR);

	cfg2 = fimc_पढ़ो(ctx, EXYNOS_CITRGFMT);
	cfg2 &= ~EXYNOS_CITRGFMT_INROT90_CLOCKWISE;

	चयन (degree) अणु
	हाल DRM_MODE_ROTATE_0:
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg1 |= EXYNOS_MSCTRL_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg1 |= EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		cfg2 |= EXYNOS_CITRGFMT_INROT90_CLOCKWISE;
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg1 |= EXYNOS_MSCTRL_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg1 |= EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		cfg1 |= (EXYNOS_MSCTRL_FLIP_X_MIRROR |
			EXYNOS_MSCTRL_FLIP_Y_MIRROR);
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		cfg1 |= (EXYNOS_MSCTRL_FLIP_X_MIRROR |
			EXYNOS_MSCTRL_FLIP_Y_MIRROR);
		cfg2 |= EXYNOS_CITRGFMT_INROT90_CLOCKWISE;
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg1 &= ~EXYNOS_MSCTRL_FLIP_Y_MIRROR;
		अवरोध;
	पूर्ण

	fimc_ग_लिखो(ctx, cfg1, EXYNOS_MSCTRL);
	fimc_ग_लिखो(ctx, cfg2, EXYNOS_CITRGFMT);
पूर्ण

अटल व्योम fimc_set_winकरोw(काष्ठा fimc_context *ctx,
			    काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	अचिन्हित पूर्णांक real_width = buf->buf.pitch[0] / buf->क्रमmat->cpp[0];
	u32 cfg, h1, h2, v1, v2;

	/* cropped image */
	h1 = buf->rect.x;
	h2 = real_width - buf->rect.w - buf->rect.x;
	v1 = buf->rect.y;
	v2 = buf->buf.height - buf->rect.h - buf->rect.y;

	DRM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]hsize[%d]vsize[%d]\n",
			  buf->rect.x, buf->rect.y, buf->rect.w, buf->rect.h,
			  real_width, buf->buf.height);
	DRM_DEV_DEBUG_KMS(ctx->dev, "h1[%d]h2[%d]v1[%d]v2[%d]\n", h1, h2, v1,
			  v2);

	/*
	 * set winकरोw offset 1, 2 size
	 * check figure 43-21 in user manual
	 */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CIWDOFST);
	cfg &= ~(EXYNOS_CIWDOFST_WINHOROFST_MASK |
		EXYNOS_CIWDOFST_WINVEROFST_MASK);
	cfg |= (EXYNOS_CIWDOFST_WINHOROFST(h1) |
		EXYNOS_CIWDOFST_WINVEROFST(v1));
	cfg |= EXYNOS_CIWDOFST_WINOFSEN;
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIWDOFST);

	cfg = (EXYNOS_CIWDOFST2_WINHOROFST2(h2) |
		EXYNOS_CIWDOFST2_WINVEROFST2(v2));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIWDOFST2);
पूर्ण

अटल व्योम fimc_src_set_size(काष्ठा fimc_context *ctx,
			      काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	अचिन्हित पूर्णांक real_width = buf->buf.pitch[0] / buf->क्रमmat->cpp[0];
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "hsize[%d]vsize[%d]\n", real_width,
			  buf->buf.height);

	/* original size */
	cfg = (EXYNOS_ORGISIZE_HORIZONTAL(real_width) |
		EXYNOS_ORGISIZE_VERTICAL(buf->buf.height));

	fimc_ग_लिखो(ctx, cfg, EXYNOS_ORGISIZE);

	DRM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]\n", buf->rect.x,
			  buf->rect.y, buf->rect.w, buf->rect.h);

	/* set input DMA image size */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CIREAL_ISIZE);
	cfg &= ~(EXYNOS_CIREAL_ISIZE_HEIGHT_MASK |
		EXYNOS_CIREAL_ISIZE_WIDTH_MASK);
	cfg |= (EXYNOS_CIREAL_ISIZE_WIDTH(buf->rect.w) |
		EXYNOS_CIREAL_ISIZE_HEIGHT(buf->rect.h));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIREAL_ISIZE);

	/*
	 * set input FIFO image size
	 * क्रम now, we support only ITU601 8 bit mode
	 */
	cfg = (EXYNOS_CISRCFMT_ITU601_8BIT |
		EXYNOS_CISRCFMT_SOURCEHSIZE(real_width) |
		EXYNOS_CISRCFMT_SOURCEVSIZE(buf->buf.height));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CISRCFMT);

	/* offset Y(RGB), Cb, Cr */
	cfg = (EXYNOS_CIIYOFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIIYOFF_VERTICAL(buf->rect.y));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIIYOFF);
	cfg = (EXYNOS_CIICBOFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIICBOFF_VERTICAL(buf->rect.y));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIICBOFF);
	cfg = (EXYNOS_CIICROFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIICROFF_VERTICAL(buf->rect.y));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIICROFF);

	fimc_set_winकरोw(ctx, buf);
पूर्ण

अटल व्योम fimc_src_set_addr(काष्ठा fimc_context *ctx,
			      काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	fimc_ग_लिखो(ctx, buf->dma_addr[0], EXYNOS_CIIYSA(0));
	fimc_ग_लिखो(ctx, buf->dma_addr[1], EXYNOS_CIICBSA(0));
	fimc_ग_लिखो(ctx, buf->dma_addr[2], EXYNOS_CIICRSA(0));
पूर्ण

अटल व्योम fimc_dst_set_fmt_order(काष्ठा fimc_context *ctx, u32 fmt)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	/* RGB */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CISCCTRL);
	cfg &= ~EXYNOS_CISCCTRL_OUTRGB_FMT_RGB_MASK;

	चयन (fmt) अणु
	हाल DRM_FORMAT_RGB565:
		cfg |= EXYNOS_CISCCTRL_OUTRGB_FMT_RGB565;
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCCTRL);
		वापस;
	हाल DRM_FORMAT_RGB888:
		cfg |= EXYNOS_CISCCTRL_OUTRGB_FMT_RGB888;
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCCTRL);
		वापस;
	हाल DRM_FORMAT_XRGB8888:
		cfg |= (EXYNOS_CISCCTRL_OUTRGB_FMT_RGB888 |
			EXYNOS_CISCCTRL_EXTRGB_EXTENSION);
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCCTRL);
		अवरोध;
	शेष:
		/* bypass */
		अवरोध;
	पूर्ण

	/* YUV */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CIOCTRL);
	cfg &= ~(EXYNOS_CIOCTRL_ORDER2P_MASK |
		EXYNOS_CIOCTRL_ORDER422_MASK |
		EXYNOS_CIOCTRL_YCBCR_PLANE_MASK);

	चयन (fmt) अणु
	हाल DRM_FORMAT_XRGB8888:
		cfg |= EXYNOS_CIOCTRL_ALPHA_OUT;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		cfg |= EXYNOS_CIOCTRL_ORDER422_YCBYCR;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		cfg |= EXYNOS_CIOCTRL_ORDER422_YCRYCB;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		cfg |= EXYNOS_CIOCTRL_ORDER422_CBYCRY;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		cfg |= EXYNOS_CIOCTRL_ORDER422_CRYCBY;
		अवरोध;
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV61:
		cfg |= EXYNOS_CIOCTRL_ORDER2P_LSB_CRCB;
		cfg |= EXYNOS_CIOCTRL_YCBCR_2PLANE;
		अवरोध;
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
		cfg |= EXYNOS_CIOCTRL_YCBCR_3PLANE;
		अवरोध;
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
		cfg |= EXYNOS_CIOCTRL_ORDER2P_LSB_CBCR;
		cfg |= EXYNOS_CIOCTRL_YCBCR_2PLANE;
		अवरोध;
	पूर्ण

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIOCTRL);
पूर्ण

अटल व्योम fimc_dst_set_fmt(काष्ठा fimc_context *ctx, u32 fmt, bool tiled)
अणु
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIEXTEN);

	अगर (fmt == DRM_FORMAT_AYUV) अणु
		cfg |= EXYNOS_CIEXTEN_YUV444_OUT;
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CIEXTEN);
	पूर्ण अन्यथा अणु
		cfg &= ~EXYNOS_CIEXTEN_YUV444_OUT;
		fimc_ग_लिखो(ctx, cfg, EXYNOS_CIEXTEN);

		cfg = fimc_पढ़ो(ctx, EXYNOS_CITRGFMT);
		cfg &= ~EXYNOS_CITRGFMT_OUTFORMAT_MASK;

		चयन (fmt) अणु
		हाल DRM_FORMAT_RGB565:
		हाल DRM_FORMAT_RGB888:
		हाल DRM_FORMAT_XRGB8888:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_RGB;
			अवरोध;
		हाल DRM_FORMAT_YUYV:
		हाल DRM_FORMAT_YVYU:
		हाल DRM_FORMAT_UYVY:
		हाल DRM_FORMAT_VYUY:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_YCBCR422_1PLANE;
			अवरोध;
		हाल DRM_FORMAT_NV16:
		हाल DRM_FORMAT_NV61:
		हाल DRM_FORMAT_YUV422:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_YCBCR422;
			अवरोध;
		हाल DRM_FORMAT_YUV420:
		हाल DRM_FORMAT_YVU420:
		हाल DRM_FORMAT_NV12:
		हाल DRM_FORMAT_NV21:
			cfg |= EXYNOS_CITRGFMT_OUTFORMAT_YCBCR420;
			अवरोध;
		पूर्ण

		fimc_ग_लिखो(ctx, cfg, EXYNOS_CITRGFMT);
	पूर्ण

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIDMAPARAM);
	cfg &= ~EXYNOS_CIDMAPARAM_W_MODE_MASK;

	अगर (tiled)
		cfg |= EXYNOS_CIDMAPARAM_W_MODE_64X32;
	अन्यथा
		cfg |= EXYNOS_CIDMAPARAM_W_MODE_LINEAR;

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIDMAPARAM);

	fimc_dst_set_fmt_order(ctx, fmt);
पूर्ण

अटल व्योम fimc_dst_set_transf(काष्ठा fimc_context *ctx, अचिन्हित पूर्णांक rotation)
अणु
	अचिन्हित पूर्णांक degree = rotation & DRM_MODE_ROTATE_MASK;
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "rotation[0x%x]\n", rotation);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CITRGFMT);
	cfg &= ~EXYNOS_CITRGFMT_FLIP_MASK;
	cfg &= ~EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE;

	चयन (degree) अणु
	हाल DRM_MODE_ROTATE_0:
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg |= EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg |= EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		cfg |= EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE;
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg |= EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg |= EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		cfg |= (EXYNOS_CITRGFMT_FLIP_X_MIRROR |
			EXYNOS_CITRGFMT_FLIP_Y_MIRROR);
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		cfg |= (EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE |
			EXYNOS_CITRGFMT_FLIP_X_MIRROR |
			EXYNOS_CITRGFMT_FLIP_Y_MIRROR);
		अगर (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_X_MIRROR;
		अगर (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~EXYNOS_CITRGFMT_FLIP_Y_MIRROR;
		अवरोध;
	पूर्ण

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CITRGFMT);
पूर्ण

अटल पूर्णांक fimc_set_prescaler(काष्ठा fimc_context *ctx, काष्ठा fimc_scaler *sc,
			      काष्ठा drm_exynos_ipp_task_rect *src,
			      काष्ठा drm_exynos_ipp_task_rect *dst)
अणु
	u32 cfg, cfg_ext, shfactor;
	u32 pre_dst_width, pre_dst_height;
	u32 hfactor, vfactor;
	पूर्णांक ret = 0;
	u32 src_w, src_h, dst_w, dst_h;

	cfg_ext = fimc_पढ़ो(ctx, EXYNOS_CITRGFMT);
	अगर (cfg_ext & EXYNOS_CITRGFMT_INROT90_CLOCKWISE) अणु
		src_w = src->h;
		src_h = src->w;
	पूर्ण अन्यथा अणु
		src_w = src->w;
		src_h = src->h;
	पूर्ण

	अगर (cfg_ext & EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE) अणु
		dst_w = dst->h;
		dst_h = dst->w;
	पूर्ण अन्यथा अणु
		dst_w = dst->w;
		dst_h = dst->h;
	पूर्ण

	/* fimc_ippdrv_check_property assures that भागiders are not null */
	hfactor = fls(src_w / dst_w / 2);
	अगर (hfactor > FIMC_SHFACTOR / 2) अणु
		dev_err(ctx->dev, "failed to get ratio horizontal.\n");
		वापस -EINVAL;
	पूर्ण

	vfactor = fls(src_h / dst_h / 2);
	अगर (vfactor > FIMC_SHFACTOR / 2) अणु
		dev_err(ctx->dev, "failed to get ratio vertical.\n");
		वापस -EINVAL;
	पूर्ण

	pre_dst_width = src_w >> hfactor;
	pre_dst_height = src_h >> vfactor;
	DRM_DEV_DEBUG_KMS(ctx->dev, "pre_dst_width[%d]pre_dst_height[%d]\n",
			  pre_dst_width, pre_dst_height);
	DRM_DEV_DEBUG_KMS(ctx->dev, "hfactor[%d]vfactor[%d]\n", hfactor,
			  vfactor);

	sc->hratio = (src_w << 14) / (dst_w << hfactor);
	sc->vratio = (src_h << 14) / (dst_h << vfactor);
	sc->up_h = (dst_w >= src_w) ? true : false;
	sc->up_v = (dst_h >= src_h) ? true : false;
	DRM_DEV_DEBUG_KMS(ctx->dev, "hratio[%d]vratio[%d]up_h[%d]up_v[%d]\n",
			  sc->hratio, sc->vratio, sc->up_h, sc->up_v);

	shfactor = FIMC_SHFACTOR - (hfactor + vfactor);
	DRM_DEV_DEBUG_KMS(ctx->dev, "shfactor[%d]\n", shfactor);

	cfg = (EXYNOS_CISCPRERATIO_SHFACTOR(shfactor) |
		EXYNOS_CISCPRERATIO_PREHORRATIO(1 << hfactor) |
		EXYNOS_CISCPRERATIO_PREVERRATIO(1 << vfactor));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCPRERATIO);

	cfg = (EXYNOS_CISCPREDST_PREDSTWIDTH(pre_dst_width) |
		EXYNOS_CISCPREDST_PREDSTHEIGHT(pre_dst_height));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCPREDST);

	वापस ret;
पूर्ण

अटल व्योम fimc_set_scaler(काष्ठा fimc_context *ctx, काष्ठा fimc_scaler *sc)
अणु
	u32 cfg, cfg_ext;

	DRM_DEV_DEBUG_KMS(ctx->dev, "range[%d]bypass[%d]up_h[%d]up_v[%d]\n",
			  sc->range, sc->bypass, sc->up_h, sc->up_v);
	DRM_DEV_DEBUG_KMS(ctx->dev, "hratio[%d]vratio[%d]\n",
			  sc->hratio, sc->vratio);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CISCCTRL);
	cfg &= ~(EXYNOS_CISCCTRL_SCALERBYPASS |
		EXYNOS_CISCCTRL_SCALEUP_H | EXYNOS_CISCCTRL_SCALEUP_V |
		EXYNOS_CISCCTRL_MAIN_V_RATIO_MASK |
		EXYNOS_CISCCTRL_MAIN_H_RATIO_MASK |
		EXYNOS_CISCCTRL_CSCR2Y_WIDE |
		EXYNOS_CISCCTRL_CSCY2R_WIDE);

	अगर (sc->range)
		cfg |= (EXYNOS_CISCCTRL_CSCR2Y_WIDE |
			EXYNOS_CISCCTRL_CSCY2R_WIDE);
	अगर (sc->bypass)
		cfg |= EXYNOS_CISCCTRL_SCALERBYPASS;
	अगर (sc->up_h)
		cfg |= EXYNOS_CISCCTRL_SCALEUP_H;
	अगर (sc->up_v)
		cfg |= EXYNOS_CISCCTRL_SCALEUP_V;

	cfg |= (EXYNOS_CISCCTRL_MAINHORRATIO((sc->hratio >> 6)) |
		EXYNOS_CISCCTRL_MAINVERRATIO((sc->vratio >> 6)));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CISCCTRL);

	cfg_ext = fimc_पढ़ो(ctx, EXYNOS_CIEXTEN);
	cfg_ext &= ~EXYNOS_CIEXTEN_MAINHORRATIO_EXT_MASK;
	cfg_ext &= ~EXYNOS_CIEXTEN_MAINVERRATIO_EXT_MASK;
	cfg_ext |= (EXYNOS_CIEXTEN_MAINHORRATIO_EXT(sc->hratio) |
		EXYNOS_CIEXTEN_MAINVERRATIO_EXT(sc->vratio));
	fimc_ग_लिखो(ctx, cfg_ext, EXYNOS_CIEXTEN);
पूर्ण

अटल व्योम fimc_dst_set_size(काष्ठा fimc_context *ctx,
			     काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	अचिन्हित पूर्णांक real_width = buf->buf.pitch[0] / buf->क्रमmat->cpp[0];
	u32 cfg, cfg_ext;

	DRM_DEV_DEBUG_KMS(ctx->dev, "hsize[%d]vsize[%d]\n", real_width,
			  buf->buf.height);

	/* original size */
	cfg = (EXYNOS_ORGOSIZE_HORIZONTAL(real_width) |
		EXYNOS_ORGOSIZE_VERTICAL(buf->buf.height));

	fimc_ग_लिखो(ctx, cfg, EXYNOS_ORGOSIZE);

	DRM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]\n", buf->rect.x,
			  buf->rect.y,
			  buf->rect.w, buf->rect.h);

	/* CSC ITU */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CIGCTRL);
	cfg &= ~EXYNOS_CIGCTRL_CSC_MASK;

	अगर (buf->buf.width >= FIMC_WIDTH_ITU_709)
		cfg |= EXYNOS_CIGCTRL_CSC_ITU709;
	अन्यथा
		cfg |= EXYNOS_CIGCTRL_CSC_ITU601;

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIGCTRL);

	cfg_ext = fimc_पढ़ो(ctx, EXYNOS_CITRGFMT);

	/* target image size */
	cfg = fimc_पढ़ो(ctx, EXYNOS_CITRGFMT);
	cfg &= ~(EXYNOS_CITRGFMT_TARGETH_MASK |
		EXYNOS_CITRGFMT_TARGETV_MASK);
	अगर (cfg_ext & EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE)
		cfg |= (EXYNOS_CITRGFMT_TARGETHSIZE(buf->rect.h) |
			EXYNOS_CITRGFMT_TARGETVSIZE(buf->rect.w));
	अन्यथा
		cfg |= (EXYNOS_CITRGFMT_TARGETHSIZE(buf->rect.w) |
			EXYNOS_CITRGFMT_TARGETVSIZE(buf->rect.h));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CITRGFMT);

	/* target area */
	cfg = EXYNOS_CITAREA_TARGET_AREA(buf->rect.w * buf->rect.h);
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CITAREA);

	/* offset Y(RGB), Cb, Cr */
	cfg = (EXYNOS_CIOYOFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIOYOFF_VERTICAL(buf->rect.y));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIOYOFF);
	cfg = (EXYNOS_CIOCBOFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIOCBOFF_VERTICAL(buf->rect.y));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIOCBOFF);
	cfg = (EXYNOS_CIOCROFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIOCROFF_VERTICAL(buf->rect.y));
	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIOCROFF);
पूर्ण

अटल व्योम fimc_dst_set_buf_seq(काष्ठा fimc_context *ctx, u32 buf_id,
		bool enqueue)
अणु
	अचिन्हित दीर्घ flags;
	u32 buf_num;
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]enqueu[%d]\n", buf_id, enqueue);

	spin_lock_irqsave(&ctx->lock, flags);

	cfg = fimc_पढ़ो(ctx, EXYNOS_CIFCNTSEQ);

	अगर (enqueue)
		cfg |= (1 << buf_id);
	अन्यथा
		cfg &= ~(1 << buf_id);

	fimc_ग_लिखो(ctx, cfg, EXYNOS_CIFCNTSEQ);

	buf_num = hweight32(cfg);

	अगर (enqueue && buf_num >= FIMC_BUF_START)
		fimc_mask_irq(ctx, true);
	अन्यथा अगर (!enqueue && buf_num <= FIMC_BUF_STOP)
		fimc_mask_irq(ctx, false);

	spin_unlock_irqrestore(&ctx->lock, flags);
पूर्ण

अटल व्योम fimc_dst_set_addr(काष्ठा fimc_context *ctx,
			     काष्ठा exynos_drm_ipp_buffer *buf)
अणु
	fimc_ग_लिखो(ctx, buf->dma_addr[0], EXYNOS_CIOYSA(0));
	fimc_ग_लिखो(ctx, buf->dma_addr[1], EXYNOS_CIOCBSA(0));
	fimc_ग_लिखो(ctx, buf->dma_addr[2], EXYNOS_CIOCRSA(0));

	fimc_dst_set_buf_seq(ctx, 0, true);
पूर्ण

अटल व्योम fimc_stop(काष्ठा fimc_context *ctx);

अटल irqवापस_t fimc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fimc_context *ctx = dev_id;
	पूर्णांक buf_id;

	DRM_DEV_DEBUG_KMS(ctx->dev, "fimc id[%d]\n", ctx->id);

	fimc_clear_irq(ctx);
	अगर (fimc_check_ovf(ctx))
		वापस IRQ_NONE;

	अगर (!fimc_check_frame_end(ctx))
		वापस IRQ_NONE;

	buf_id = fimc_get_buf_id(ctx);
	अगर (buf_id < 0)
		वापस IRQ_HANDLED;

	DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]\n", buf_id);

	अगर (ctx->task) अणु
		काष्ठा exynos_drm_ipp_task *task = ctx->task;

		ctx->task = शून्य;
		pm_runसमय_mark_last_busy(ctx->dev);
		pm_runसमय_put_स्वतःsuspend(ctx->dev);
		exynos_drm_ipp_task_करोne(task, 0);
	पूर्ण

	fimc_dst_set_buf_seq(ctx, buf_id, false);
	fimc_stop(ctx);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fimc_clear_addr(काष्ठा fimc_context *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FIMC_MAX_SRC; i++) अणु
		fimc_ग_लिखो(ctx, 0, EXYNOS_CIIYSA(i));
		fimc_ग_लिखो(ctx, 0, EXYNOS_CIICBSA(i));
		fimc_ग_लिखो(ctx, 0, EXYNOS_CIICRSA(i));
	पूर्ण

	क्रम (i = 0; i < FIMC_MAX_DST; i++) अणु
		fimc_ग_लिखो(ctx, 0, EXYNOS_CIOYSA(i));
		fimc_ग_लिखो(ctx, 0, EXYNOS_CIOCBSA(i));
		fimc_ग_लिखो(ctx, 0, EXYNOS_CIOCRSA(i));
	पूर्ण
पूर्ण

अटल व्योम fimc_reset(काष्ठा fimc_context *ctx)
अणु
	/* reset h/w block */
	fimc_sw_reset(ctx);

	/* reset scaler capability */
	स_रखो(&ctx->sc, 0x0, माप(ctx->sc));

	fimc_clear_addr(ctx);
पूर्ण

अटल व्योम fimc_start(काष्ठा fimc_context *ctx)
अणु
	u32 cfg0, cfg1;

	fimc_mask_irq(ctx, true);

	/* If set true, we can save jpeg about screen */
	fimc_handle_jpeg(ctx, false);
	fimc_set_scaler(ctx, &ctx->sc);

	fimc_set_type_ctrl(ctx);
	fimc_handle_lastend(ctx, false);

	/* setup dma */
	cfg0 = fimc_पढ़ो(ctx, EXYNOS_MSCTRL);
	cfg0 &= ~EXYNOS_MSCTRL_INPUT_MASK;
	cfg0 |= EXYNOS_MSCTRL_INPUT_MEMORY;
	fimc_ग_लिखो(ctx, cfg0, EXYNOS_MSCTRL);

	/* Reset status */
	fimc_ग_लिखो(ctx, 0x0, EXYNOS_CISTATUS);

	cfg0 = fimc_पढ़ो(ctx, EXYNOS_CIIMGCPT);
	cfg0 &= ~EXYNOS_CIIMGCPT_IMGCPTEN_SC;
	cfg0 |= EXYNOS_CIIMGCPT_IMGCPTEN_SC;

	/* Scaler */
	cfg1 = fimc_पढ़ो(ctx, EXYNOS_CISCCTRL);
	cfg1 &= ~EXYNOS_CISCCTRL_SCAN_MASK;
	cfg1 |= (EXYNOS_CISCCTRL_PROGRESSIVE |
		EXYNOS_CISCCTRL_SCALERSTART);

	fimc_ग_लिखो(ctx, cfg1, EXYNOS_CISCCTRL);

	/* Enable image capture*/
	cfg0 |= EXYNOS_CIIMGCPT_IMGCPTEN;
	fimc_ग_लिखो(ctx, cfg0, EXYNOS_CIIMGCPT);

	/* Disable frame end irq */
	fimc_clear_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_IRQ_END_DISABLE);

	fimc_clear_bits(ctx, EXYNOS_CIOCTRL, EXYNOS_CIOCTRL_WEAVE_MASK);

	fimc_set_bits(ctx, EXYNOS_MSCTRL, EXYNOS_MSCTRL_ENVID);
पूर्ण

अटल व्योम fimc_stop(काष्ठा fimc_context *ctx)
अणु
	u32 cfg;

	/* Source clear */
	cfg = fimc_पढ़ो(ctx, EXYNOS_MSCTRL);
	cfg &= ~EXYNOS_MSCTRL_INPUT_MASK;
	cfg &= ~EXYNOS_MSCTRL_ENVID;
	fimc_ग_लिखो(ctx, cfg, EXYNOS_MSCTRL);

	fimc_mask_irq(ctx, false);

	/* reset sequence */
	fimc_ग_लिखो(ctx, 0x0, EXYNOS_CIFCNTSEQ);

	/* Scaler disable */
	fimc_clear_bits(ctx, EXYNOS_CISCCTRL, EXYNOS_CISCCTRL_SCALERSTART);

	/* Disable image capture */
	fimc_clear_bits(ctx, EXYNOS_CIIMGCPT,
		EXYNOS_CIIMGCPT_IMGCPTEN_SC | EXYNOS_CIIMGCPT_IMGCPTEN);

	/* Enable frame end irq */
	fimc_set_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_IRQ_END_DISABLE);
पूर्ण

अटल पूर्णांक fimc_commit(काष्ठा exynos_drm_ipp *ipp,
			  काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा fimc_context *ctx =
			container_of(ipp, काष्ठा fimc_context, ipp);

	pm_runसमय_get_sync(ctx->dev);
	ctx->task = task;

	fimc_src_set_fmt(ctx, task->src.buf.fourcc, task->src.buf.modअगरier);
	fimc_src_set_size(ctx, &task->src);
	fimc_src_set_transf(ctx, DRM_MODE_ROTATE_0);
	fimc_src_set_addr(ctx, &task->src);
	fimc_dst_set_fmt(ctx, task->dst.buf.fourcc, task->dst.buf.modअगरier);
	fimc_dst_set_transf(ctx, task->transक्रमm.rotation);
	fimc_dst_set_size(ctx, &task->dst);
	fimc_dst_set_addr(ctx, &task->dst);
	fimc_set_prescaler(ctx, &ctx->sc, &task->src.rect, &task->dst.rect);
	fimc_start(ctx);

	वापस 0;
पूर्ण

अटल व्योम fimc_पात(काष्ठा exynos_drm_ipp *ipp,
			  काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा fimc_context *ctx =
			container_of(ipp, काष्ठा fimc_context, ipp);

	fimc_reset(ctx);

	अगर (ctx->task) अणु
		काष्ठा exynos_drm_ipp_task *task = ctx->task;

		ctx->task = शून्य;
		pm_runसमय_mark_last_busy(ctx->dev);
		pm_runसमय_put_स्वतःsuspend(ctx->dev);
		exynos_drm_ipp_task_करोne(task, -EIO);
	पूर्ण
पूर्ण

अटल काष्ठा exynos_drm_ipp_funcs ipp_funcs = अणु
	.commit = fimc_commit,
	.पात = fimc_पात,
पूर्ण;

अटल पूर्णांक fimc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा fimc_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_ipp *ipp = &ctx->ipp;

	ctx->drm_dev = drm_dev;
	ipp->drm_dev = drm_dev;
	exynos_drm_रेजिस्टर_dma(drm_dev, dev, &ctx->dma_priv);

	exynos_drm_ipp_रेजिस्टर(dev, ipp, &ipp_funcs,
			DRM_EXYNOS_IPP_CAP_CROP | DRM_EXYNOS_IPP_CAP_ROTATE |
			DRM_EXYNOS_IPP_CAP_SCALE | DRM_EXYNOS_IPP_CAP_CONVERT,
			ctx->क्रमmats, ctx->num_क्रमmats, "fimc");

	dev_info(dev, "The exynos fimc has been probed successfully\n");

	वापस 0;
पूर्ण

अटल व्योम fimc_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा fimc_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_ipp *ipp = &ctx->ipp;

	exynos_drm_ipp_unरेजिस्टर(dev, ipp);
	exynos_drm_unरेजिस्टर_dma(drm_dev, dev, &ctx->dma_priv);
पूर्ण

अटल स्थिर काष्ठा component_ops fimc_component_ops = अणु
	.bind	= fimc_bind,
	.unbind = fimc_unbind,
पूर्ण;

अटल व्योम fimc_put_घड़ीs(काष्ठा fimc_context *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FIMC_CLKS_MAX; i++) अणु
		अगर (IS_ERR(ctx->घड़ीs[i]))
			जारी;
		clk_put(ctx->घड़ीs[i]);
		ctx->घड़ीs[i] = ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_setup_घड़ीs(काष्ठा fimc_context *ctx)
अणु
	काष्ठा device *fimc_dev = ctx->dev;
	काष्ठा device *dev;
	पूर्णांक ret, i;

	क्रम (i = 0; i < FIMC_CLKS_MAX; i++)
		ctx->घड़ीs[i] = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < FIMC_CLKS_MAX; i++) अणु
		अगर (i == FIMC_CLK_WB_A || i == FIMC_CLK_WB_B)
			dev = fimc_dev->parent;
		अन्यथा
			dev = fimc_dev;

		ctx->घड़ीs[i] = clk_get(dev, fimc_घड़ी_names[i]);
		अगर (IS_ERR(ctx->घड़ीs[i])) अणु
			ret = PTR_ERR(ctx->घड़ीs[i]);
			dev_err(fimc_dev, "failed to get clock: %s\n",
						fimc_घड़ी_names[i]);
			जाओ e_clk_मुक्त;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(ctx->घड़ीs[FIMC_CLK_LCLK]);
	अगर (!ret)
		वापस ret;
e_clk_मुक्त:
	fimc_put_घड़ीs(ctx);
	वापस ret;
पूर्ण

पूर्णांक exynos_drm_check_fimc_device(काष्ठा device *dev)
अणु
	पूर्णांक id = of_alias_get_id(dev->of_node, "fimc");

	अगर (id >= 0 && (BIT(id) & fimc_mask))
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक fimc_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888, DRM_FORMAT_RGB565,
	DRM_FORMAT_NV12, DRM_FORMAT_NV16, DRM_FORMAT_NV21, DRM_FORMAT_NV61,
	DRM_FORMAT_UYVY, DRM_FORMAT_VYUY, DRM_FORMAT_YUYV, DRM_FORMAT_YVYU,
	DRM_FORMAT_YUV420, DRM_FORMAT_YVU420, DRM_FORMAT_YUV422,
	DRM_FORMAT_YUV444,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fimc_tiled_क्रमmats[] = अणु
	DRM_FORMAT_NV12, DRM_FORMAT_NV21,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit fimc_4210_limits_v1[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 16, 8192, 8 पूर्ण, .v = अणु 16, 8192, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 16, 4224, 2 पूर्ण, .v = अणु 16, 0, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(ROTATED, .h = अणु 128, 1920 पूर्ण, .v = अणु 128, 0 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण,
			  .v = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit fimc_4210_limits_v2[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 16, 8192, 8 पूर्ण, .v = अणु 16, 8192, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 16, 1920, 2 पूर्ण, .v = अणु 16, 0, 2 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(ROTATED, .h = अणु 128, 1366 पूर्ण, .v = अणु 128, 0 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण,
			  .v = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit fimc_4210_limits_tiled_v1[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 128, 1920, 128 पूर्ण, .v = अणु 32, 1920, 32 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 128, 1920, 2 पूर्ण, .v = अणु 128, 0, 2 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण,
			  .v = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit fimc_4210_limits_tiled_v2[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 128, 1920, 128 पूर्ण, .v = अणु 32, 1920, 32 पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h = अणु 128, 1366, 2 पूर्ण, .v = अणु 128, 0, 2 पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण,
			  .v = अणु (1 << 16) / 64, (1 << 16) * 64 पूर्ण) पूर्ण,
पूर्ण;

अटल पूर्णांक fimc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा drm_exynos_ipp_limit *limits;
	काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fimc_context *ctx;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक i, j, num_limits, num_क्रमmats;

	अगर (exynos_drm_check_fimc_device(dev) != 0)
		वापस -ENODEV;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;
	ctx->id = of_alias_get_id(dev->of_node, "fimc");

	/* स्थिरruct क्रमmats/limits array */
	num_क्रमmats = ARRAY_SIZE(fimc_क्रमmats) + ARRAY_SIZE(fimc_tiled_क्रमmats);
	क्रमmats = devm_kसुस्मृति(dev, num_क्रमmats, माप(*क्रमmats),
			       GFP_KERNEL);
	अगर (!क्रमmats)
		वापस -ENOMEM;

	/* linear क्रमmats */
	अगर (ctx->id < 3) अणु
		limits = fimc_4210_limits_v1;
		num_limits = ARRAY_SIZE(fimc_4210_limits_v1);
	पूर्ण अन्यथा अणु
		limits = fimc_4210_limits_v2;
		num_limits = ARRAY_SIZE(fimc_4210_limits_v2);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(fimc_क्रमmats); i++) अणु
		क्रमmats[i].fourcc = fimc_क्रमmats[i];
		क्रमmats[i].type = DRM_EXYNOS_IPP_FORMAT_SOURCE |
				  DRM_EXYNOS_IPP_FORMAT_DESTINATION;
		क्रमmats[i].limits = limits;
		क्रमmats[i].num_limits = num_limits;
	पूर्ण

	/* tiled क्रमmats */
	अगर (ctx->id < 3) अणु
		limits = fimc_4210_limits_tiled_v1;
		num_limits = ARRAY_SIZE(fimc_4210_limits_tiled_v1);
	पूर्ण अन्यथा अणु
		limits = fimc_4210_limits_tiled_v2;
		num_limits = ARRAY_SIZE(fimc_4210_limits_tiled_v2);
	पूर्ण
	क्रम (j = i, i = 0; i < ARRAY_SIZE(fimc_tiled_क्रमmats); j++, i++) अणु
		क्रमmats[j].fourcc = fimc_tiled_क्रमmats[i];
		क्रमmats[j].modअगरier = DRM_FORMAT_MOD_SAMSUNG_64_32_TILE;
		क्रमmats[j].type = DRM_EXYNOS_IPP_FORMAT_SOURCE |
				  DRM_EXYNOS_IPP_FORMAT_DESTINATION;
		क्रमmats[j].limits = limits;
		क्रमmats[j].num_limits = num_limits;
	पूर्ण

	ctx->क्रमmats = क्रमmats;
	ctx->num_क्रमmats = num_क्रमmats;

	/* resource memory */
	ctx->regs_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->regs = devm_ioremap_resource(dev, ctx->regs_res);
	अगर (IS_ERR(ctx->regs))
		वापस PTR_ERR(ctx->regs);

	/* resource irq */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to request irq resource.\n");
		वापस -ENOENT;
	पूर्ण

	ret = devm_request_irq(dev, res->start, fimc_irq_handler,
		0, dev_name(dev), ctx);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request irq.\n");
		वापस ret;
	पूर्ण

	ret = fimc_setup_घड़ीs(ctx);
	अगर (ret < 0)
		वापस ret;

	spin_lock_init(&ctx->lock);
	platक्रमm_set_drvdata(pdev, ctx);

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, FIMC_AUTOSUSPEND_DELAY);
	pm_runसमय_enable(dev);

	ret = component_add(dev, &fimc_component_ops);
	अगर (ret)
		जाओ err_pm_dis;

	dev_info(dev, "drm fimc registered successfully.\n");

	वापस 0;

err_pm_dis:
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
	fimc_put_घड़ीs(ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fimc_context *ctx = get_fimc_context(dev);

	component_del(dev, &fimc_component_ops);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);

	fimc_put_घड़ीs(ctx);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fimc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_context *ctx = get_fimc_context(dev);

	DRM_DEV_DEBUG_KMS(dev, "id[%d]\n", ctx->id);
	clk_disable_unprepare(ctx->घड़ीs[FIMC_CLK_GATE]);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_context *ctx = get_fimc_context(dev);

	DRM_DEV_DEBUG_KMS(dev, "id[%d]\n", ctx->id);
	वापस clk_prepare_enable(ctx->घड़ीs[FIMC_CLK_GATE]);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fimc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(fimc_runसमय_suspend, fimc_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id fimc_of_match[] = अणु
	अणु .compatible = "samsung,exynos4210-fimc" पूर्ण,
	अणु .compatible = "samsung,exynos4212-fimc" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fimc_of_match);

काष्ठा platक्रमm_driver fimc_driver = अणु
	.probe		= fimc_probe,
	.हटाओ		= fimc_हटाओ,
	.driver		= अणु
		.of_match_table = fimc_of_match,
		.name	= "exynos-drm-fimc",
		.owner	= THIS_MODULE,
		.pm	= &fimc_pm_ops,
	पूर्ण,
पूर्ण;
