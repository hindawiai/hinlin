<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI Camera Access Layer (CAL) - Driver
 *
 * Copyright (c) 2015-2020 Texas Instruments Inc.
 *
 * Authors:
 *	Benoit Parrot <bparrot@ti.com>
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "cal.h"
#समावेश "cal_regs.h"

MODULE_DESCRIPTION("TI CAL driver");
MODULE_AUTHOR("Benoit Parrot, <bparrot@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("0.1.0");

पूर्णांक cal_video_nr = -1;
module_param_named(video_nr, cal_video_nr, uपूर्णांक, 0644);
MODULE_PARM_DESC(video_nr, "videoX start number, -1 is autodetect");

अचिन्हित पूर्णांक cal_debug;
module_param_named(debug, cal_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "activates debug info");

#अगर_घोषित CONFIG_VIDEO_TI_CAL_MC
#घोषणा CAL_MC_API_DEFAULT 1
#अन्यथा
#घोषणा CAL_MC_API_DEFAULT 0
#पूर्ण_अगर

bool cal_mc_api = CAL_MC_API_DEFAULT;
module_param_named(mc_api, cal_mc_api, bool, 0444);
MODULE_PARM_DESC(mc_api, "activates the MC API");

/* ------------------------------------------------------------------
 *	Format Handling
 * ------------------------------------------------------------------
 */

स्थिर काष्ठा cal_क्रमmat_info cal_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_VYUY,
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565, /* gggbbbbb rrrrrggg */
		.code		= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565X, /* rrrrrggg gggbbbbb */
		.code		= MEDIA_BUS_FMT_RGB565_2X8_BE,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB555, /* gggbbbbb arrrrrgg */
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB555X, /* arrrrrgg gggbbbbb */
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE,
		.bpp		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB24, /* rgb */
		.code		= MEDIA_BUS_FMT_RGB888_2X12_LE,
		.bpp		= 24,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_BGR24, /* bgr */
		.code		= MEDIA_BUS_FMT_RGB888_2X12_BE,
		.bpp		= 24,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB32, /* argb */
		.code		= MEDIA_BUS_FMT_ARGB8888_1X32,
		.bpp		= 32,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR8,
		.code		= MEDIA_BUS_FMT_SBGGR8_1X8,
		.bpp		= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG8,
		.code		= MEDIA_BUS_FMT_SGBRG8_1X8,
		.bpp		= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG8,
		.code		= MEDIA_BUS_FMT_SGRBG8_1X8,
		.bpp		= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB8,
		.code		= MEDIA_BUS_FMT_SRGGB8_1X8,
		.bpp		= 8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR10,
		.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
		.bpp		= 10,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG10,
		.code		= MEDIA_BUS_FMT_SGBRG10_1X10,
		.bpp		= 10,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG10,
		.code		= MEDIA_BUS_FMT_SGRBG10_1X10,
		.bpp		= 10,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB10,
		.code		= MEDIA_BUS_FMT_SRGGB10_1X10,
		.bpp		= 10,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR12,
		.code		= MEDIA_BUS_FMT_SBGGR12_1X12,
		.bpp		= 12,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG12,
		.code		= MEDIA_BUS_FMT_SGBRG12_1X12,
		.bpp		= 12,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG12,
		.code		= MEDIA_BUS_FMT_SGRBG12_1X12,
		.bpp		= 12,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB12,
		.code		= MEDIA_BUS_FMT_SRGGB12_1X12,
		.bpp		= 12,
	पूर्ण,
पूर्ण;

स्थिर अचिन्हित पूर्णांक cal_num_क्रमmats = ARRAY_SIZE(cal_क्रमmats);

स्थिर काष्ठा cal_क्रमmat_info *cal_क्रमmat_by_fourcc(u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cal_क्रमmats); ++i) अणु
		अगर (cal_क्रमmats[i].fourcc == fourcc)
			वापस &cal_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

स्थिर काष्ठा cal_क्रमmat_info *cal_क्रमmat_by_code(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cal_क्रमmats); ++i) अणु
		अगर (cal_क्रमmats[i].code == code)
			वापस &cal_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/* ------------------------------------------------------------------
 *	Platक्रमm Data
 * ------------------------------------------------------------------
 */

अटल स्थिर काष्ठा cal_camerarx_data dra72x_cal_camerarx[] = अणु
	अणु
		.fields = अणु
			[F_CTRLCLKEN] = अणु 10, 10 पूर्ण,
			[F_CAMMODE] = अणु 11, 12 पूर्ण,
			[F_LANEENABLE] = अणु 13, 16 पूर्ण,
			[F_CSI_MODE] = अणु 17, 17 पूर्ण,
		पूर्ण,
		.num_lanes = 4,
	पूर्ण,
	अणु
		.fields = अणु
			[F_CTRLCLKEN] = अणु 0, 0 पूर्ण,
			[F_CAMMODE] = अणु 1, 2 पूर्ण,
			[F_LANEENABLE] = अणु 3, 4 पूर्ण,
			[F_CSI_MODE] = अणु 5, 5 पूर्ण,
		पूर्ण,
		.num_lanes = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cal_data dra72x_cal_data = अणु
	.camerarx = dra72x_cal_camerarx,
	.num_csi2_phy = ARRAY_SIZE(dra72x_cal_camerarx),
पूर्ण;

अटल स्थिर काष्ठा cal_data dra72x_es1_cal_data = अणु
	.camerarx = dra72x_cal_camerarx,
	.num_csi2_phy = ARRAY_SIZE(dra72x_cal_camerarx),
	.flags = DRA72_CAL_PRE_ES2_LDO_DISABLE,
पूर्ण;

अटल स्थिर काष्ठा cal_camerarx_data dra76x_cal_csi_phy[] = अणु
	अणु
		.fields = अणु
			[F_CTRLCLKEN] = अणु 8, 8 पूर्ण,
			[F_CAMMODE] = अणु 9, 10 पूर्ण,
			[F_CSI_MODE] = अणु 11, 11 पूर्ण,
			[F_LANEENABLE] = अणु 27, 31 पूर्ण,
		पूर्ण,
		.num_lanes = 5,
	पूर्ण,
	अणु
		.fields = अणु
			[F_CTRLCLKEN] = अणु 0, 0 पूर्ण,
			[F_CAMMODE] = अणु 1, 2 पूर्ण,
			[F_CSI_MODE] = अणु 3, 3 पूर्ण,
			[F_LANEENABLE] = अणु 24, 26 पूर्ण,
		पूर्ण,
		.num_lanes = 3,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cal_data dra76x_cal_data = अणु
	.camerarx = dra76x_cal_csi_phy,
	.num_csi2_phy = ARRAY_SIZE(dra76x_cal_csi_phy),
पूर्ण;

अटल स्थिर काष्ठा cal_camerarx_data am654_cal_csi_phy[] = अणु
	अणु
		.fields = अणु
			[F_CTRLCLKEN] = अणु 15, 15 पूर्ण,
			[F_CAMMODE] = अणु 24, 25 पूर्ण,
			[F_LANEENABLE] = अणु 0, 4 पूर्ण,
		पूर्ण,
		.num_lanes = 5,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cal_data am654_cal_data = अणु
	.camerarx = am654_cal_csi_phy,
	.num_csi2_phy = ARRAY_SIZE(am654_cal_csi_phy),
पूर्ण;

/* ------------------------------------------------------------------
 *	I/O Register Accessors
 * ------------------------------------------------------------------
 */

व्योम cal_quickdump_regs(काष्ठा cal_dev *cal)
अणु
	अचिन्हित पूर्णांक i;

	cal_info(cal, "CAL Registers @ 0x%pa:\n", &cal->res->start);
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 4,
		       (__क्रमce स्थिर व्योम *)cal->base,
		       resource_size(cal->res), false);

	क्रम (i = 0; i < cal->data->num_csi2_phy; ++i) अणु
		काष्ठा cal_camerarx *phy = cal->phy[i];

		cal_info(cal, "CSI2 Core %u Registers @ %pa:\n", i,
			 &phy->res->start);
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 4,
			       (__क्रमce स्थिर व्योम *)phy->base,
			       resource_size(phy->res),
			       false);
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------
 *	Context Management
 * ------------------------------------------------------------------
 */

अटल व्योम cal_ctx_csi2_config(काष्ठा cal_ctx *ctx)
अणु
	u32 val;

	val = cal_पढ़ो(ctx->cal, CAL_CSI2_CTX0(ctx->index));
	cal_set_field(&val, ctx->cport, CAL_CSI2_CTX_CPORT_MASK);
	/*
	 * DT type: MIPI CSI-2 Specs
	 *   0x1: All - DT filter is disabled
	 *  0x24: RGB888 1 pixel  = 3 bytes
	 *  0x2B: RAW10  4 pixels = 5 bytes
	 *  0x2A: RAW8   1 pixel  = 1 byte
	 *  0x1E: YUV422 2 pixels = 4 bytes
	 */
	cal_set_field(&val, 0x1, CAL_CSI2_CTX_DT_MASK);
	cal_set_field(&val, 0, CAL_CSI2_CTX_VC_MASK);
	cal_set_field(&val, ctx->v_fmt.fmt.pix.height, CAL_CSI2_CTX_LINES_MASK);
	cal_set_field(&val, CAL_CSI2_CTX_ATT_PIX, CAL_CSI2_CTX_ATT_MASK);
	cal_set_field(&val, CAL_CSI2_CTX_PACK_MODE_LINE,
		      CAL_CSI2_CTX_PACK_MODE_MASK);
	cal_ग_लिखो(ctx->cal, CAL_CSI2_CTX0(ctx->index), val);
	ctx_dbg(3, ctx, "CAL_CSI2_CTX0(%d) = 0x%08x\n", ctx->index,
		cal_पढ़ो(ctx->cal, CAL_CSI2_CTX0(ctx->index)));
पूर्ण

अटल व्योम cal_ctx_pix_proc_config(काष्ठा cal_ctx *ctx)
अणु
	u32 val, extract, pack;

	चयन (ctx->fmtinfo->bpp) अणु
	हाल 8:
		extract = CAL_PIX_PROC_EXTRACT_B8;
		pack = CAL_PIX_PROC_PACK_B8;
		अवरोध;
	हाल 10:
		extract = CAL_PIX_PROC_EXTRACT_B10_MIPI;
		pack = CAL_PIX_PROC_PACK_B16;
		अवरोध;
	हाल 12:
		extract = CAL_PIX_PROC_EXTRACT_B12_MIPI;
		pack = CAL_PIX_PROC_PACK_B16;
		अवरोध;
	हाल 16:
		extract = CAL_PIX_PROC_EXTRACT_B16_LE;
		pack = CAL_PIX_PROC_PACK_B16;
		अवरोध;
	शेष:
		/*
		 * If you see this warning then it means that you added
		 * some new entry in the cal_क्रमmats[] array with a dअगरferent
		 * bit per pixel values then the one supported below.
		 * Either add support क्रम the new bpp value below or adjust
		 * the new entry to use one of the value below.
		 *
		 * Instead of failing here just use 8 bpp as a शेष.
		 */
		dev_warn_once(ctx->cal->dev,
			      "%s:%d:%s: bpp:%d unsupported! Overwritten with 8.\n",
			      __खाता__, __LINE__, __func__, ctx->fmtinfo->bpp);
		extract = CAL_PIX_PROC_EXTRACT_B8;
		pack = CAL_PIX_PROC_PACK_B8;
		अवरोध;
	पूर्ण

	val = cal_पढ़ो(ctx->cal, CAL_PIX_PROC(ctx->index));
	cal_set_field(&val, extract, CAL_PIX_PROC_EXTRACT_MASK);
	cal_set_field(&val, CAL_PIX_PROC_DPCMD_BYPASS, CAL_PIX_PROC_DPCMD_MASK);
	cal_set_field(&val, CAL_PIX_PROC_DPCME_BYPASS, CAL_PIX_PROC_DPCME_MASK);
	cal_set_field(&val, pack, CAL_PIX_PROC_PACK_MASK);
	cal_set_field(&val, ctx->cport, CAL_PIX_PROC_CPORT_MASK);
	cal_set_field(&val, 1, CAL_PIX_PROC_EN_MASK);
	cal_ग_लिखो(ctx->cal, CAL_PIX_PROC(ctx->index), val);
	ctx_dbg(3, ctx, "CAL_PIX_PROC(%d) = 0x%08x\n", ctx->index,
		cal_पढ़ो(ctx->cal, CAL_PIX_PROC(ctx->index)));
पूर्ण

अटल व्योम cal_ctx_wr_dma_config(काष्ठा cal_ctx *ctx)
अणु
	अचिन्हित पूर्णांक stride = ctx->v_fmt.fmt.pix.bytesperline;
	u32 val;

	val = cal_पढ़ो(ctx->cal, CAL_WR_DMA_CTRL(ctx->index));
	cal_set_field(&val, ctx->cport, CAL_WR_DMA_CTRL_CPORT_MASK);
	cal_set_field(&val, ctx->v_fmt.fmt.pix.height,
		      CAL_WR_DMA_CTRL_YSIZE_MASK);
	cal_set_field(&val, CAL_WR_DMA_CTRL_DTAG_PIX_DAT,
		      CAL_WR_DMA_CTRL_DTAG_MASK);
	cal_set_field(&val, CAL_WR_DMA_CTRL_MODE_CONST,
		      CAL_WR_DMA_CTRL_MODE_MASK);
	cal_set_field(&val, CAL_WR_DMA_CTRL_PATTERN_LINEAR,
		      CAL_WR_DMA_CTRL_PATTERN_MASK);
	cal_set_field(&val, 1, CAL_WR_DMA_CTRL_STALL_RD_MASK);
	cal_ग_लिखो(ctx->cal, CAL_WR_DMA_CTRL(ctx->index), val);
	ctx_dbg(3, ctx, "CAL_WR_DMA_CTRL(%d) = 0x%08x\n", ctx->index,
		cal_पढ़ो(ctx->cal, CAL_WR_DMA_CTRL(ctx->index)));

	cal_ग_लिखो_field(ctx->cal, CAL_WR_DMA_OFST(ctx->index),
			stride / 16, CAL_WR_DMA_OFST_MASK);
	ctx_dbg(3, ctx, "CAL_WR_DMA_OFST(%d) = 0x%08x\n", ctx->index,
		cal_पढ़ो(ctx->cal, CAL_WR_DMA_OFST(ctx->index)));

	val = cal_पढ़ो(ctx->cal, CAL_WR_DMA_XSIZE(ctx->index));
	/* 64 bit word means no skipping */
	cal_set_field(&val, 0, CAL_WR_DMA_XSIZE_XSKIP_MASK);
	/*
	 * The XSIZE field is expressed in 64-bit units and prevents overflows
	 * in हाल of synchronization issues by limiting the number of bytes
	 * written per line.
	 */
	cal_set_field(&val, stride / 8, CAL_WR_DMA_XSIZE_MASK);
	cal_ग_लिखो(ctx->cal, CAL_WR_DMA_XSIZE(ctx->index), val);
	ctx_dbg(3, ctx, "CAL_WR_DMA_XSIZE(%d) = 0x%08x\n", ctx->index,
		cal_पढ़ो(ctx->cal, CAL_WR_DMA_XSIZE(ctx->index)));

	val = cal_पढ़ो(ctx->cal, CAL_CTRL);
	cal_set_field(&val, CAL_CTRL_BURSTSIZE_BURST128,
		      CAL_CTRL_BURSTSIZE_MASK);
	cal_set_field(&val, 0xF, CAL_CTRL_TAGCNT_MASK);
	cal_set_field(&val, CAL_CTRL_POSTED_WRITES_NONPOSTED,
		      CAL_CTRL_POSTED_WRITES_MASK);
	cal_set_field(&val, 0xFF, CAL_CTRL_MFLAGL_MASK);
	cal_set_field(&val, 0xFF, CAL_CTRL_MFLAGH_MASK);
	cal_ग_लिखो(ctx->cal, CAL_CTRL, val);
	ctx_dbg(3, ctx, "CAL_CTRL = 0x%08x\n", cal_पढ़ो(ctx->cal, CAL_CTRL));
पूर्ण

व्योम cal_ctx_set_dma_addr(काष्ठा cal_ctx *ctx, dma_addr_t addr)
अणु
	cal_ग_लिखो(ctx->cal, CAL_WR_DMA_ADDR(ctx->index), addr);
पूर्ण

अटल व्योम cal_ctx_wr_dma_disable(काष्ठा cal_ctx *ctx)
अणु
	u32 val = cal_पढ़ो(ctx->cal, CAL_WR_DMA_CTRL(ctx->index));

	cal_set_field(&val, CAL_WR_DMA_CTRL_MODE_DIS,
		      CAL_WR_DMA_CTRL_MODE_MASK);
	cal_ग_लिखो(ctx->cal, CAL_WR_DMA_CTRL(ctx->index), val);
पूर्ण

अटल bool cal_ctx_wr_dma_stopped(काष्ठा cal_ctx *ctx)
अणु
	bool stopped;

	spin_lock_irq(&ctx->dma.lock);
	stopped = ctx->dma.state == CAL_DMA_STOPPED;
	spin_unlock_irq(&ctx->dma.lock);

	वापस stopped;
पूर्ण

व्योम cal_ctx_start(काष्ठा cal_ctx *ctx)
अणु
	ctx->sequence = 0;
	ctx->dma.state = CAL_DMA_RUNNING;

	/* Configure the CSI-2, pixel processing and ग_लिखो DMA contexts. */
	cal_ctx_csi2_config(ctx);
	cal_ctx_pix_proc_config(ctx);
	cal_ctx_wr_dma_config(ctx);

	/* Enable IRQ_WDMA_END and IRQ_WDMA_START. */
	cal_ग_लिखो(ctx->cal, CAL_HL_IRQENABLE_SET(1),
		  CAL_HL_IRQ_MASK(ctx->index));
	cal_ग_लिखो(ctx->cal, CAL_HL_IRQENABLE_SET(2),
		  CAL_HL_IRQ_MASK(ctx->index));
पूर्ण

व्योम cal_ctx_stop(काष्ठा cal_ctx *ctx)
अणु
	दीर्घ समयout;

	/*
	 * Request DMA stop and रुको until it completes. If completion बार
	 * out, क्रमcefully disable the DMA.
	 */
	spin_lock_irq(&ctx->dma.lock);
	ctx->dma.state = CAL_DMA_STOP_REQUESTED;
	spin_unlock_irq(&ctx->dma.lock);

	समयout = रुको_event_समयout(ctx->dma.रुको, cal_ctx_wr_dma_stopped(ctx),
				     msecs_to_jअगरfies(500));
	अगर (!समयout) अणु
		ctx_err(ctx, "failed to disable dma cleanly\n");
		cal_ctx_wr_dma_disable(ctx);
	पूर्ण

	/* Disable IRQ_WDMA_END and IRQ_WDMA_START. */
	cal_ग_लिखो(ctx->cal, CAL_HL_IRQENABLE_CLR(1),
		  CAL_HL_IRQ_MASK(ctx->index));
	cal_ग_लिखो(ctx->cal, CAL_HL_IRQENABLE_CLR(2),
		  CAL_HL_IRQ_MASK(ctx->index));

	ctx->dma.state = CAL_DMA_STOPPED;
पूर्ण

/* ------------------------------------------------------------------
 *	IRQ Handling
 * ------------------------------------------------------------------
 */

अटल अंतरभूत व्योम cal_irq_wdma_start(काष्ठा cal_ctx *ctx)
अणु
	spin_lock(&ctx->dma.lock);

	अगर (ctx->dma.state == CAL_DMA_STOP_REQUESTED) अणु
		/*
		 * If a stop is requested, disable the ग_लिखो DMA context
		 * immediately. The CAL_WR_DMA_CTRL_j.MODE field is shaकरोwed,
		 * the current frame will complete and the DMA will then stop.
		 */
		cal_ctx_wr_dma_disable(ctx);
		ctx->dma.state = CAL_DMA_STOP_PENDING;
	पूर्ण अन्यथा अगर (!list_empty(&ctx->dma.queue) && !ctx->dma.pending) अणु
		/*
		 * Otherwise, अगर a new buffer is available, queue it to the
		 * hardware.
		 */
		काष्ठा cal_buffer *buf;
		dma_addr_t addr;

		buf = list_first_entry(&ctx->dma.queue, काष्ठा cal_buffer,
				       list);
		addr = vb2_dma_contig_plane_dma_addr(&buf->vb.vb2_buf, 0);
		cal_ctx_set_dma_addr(ctx, addr);

		ctx->dma.pending = buf;
		list_del(&buf->list);
	पूर्ण

	spin_unlock(&ctx->dma.lock);
पूर्ण

अटल अंतरभूत व्योम cal_irq_wdma_end(काष्ठा cal_ctx *ctx)
अणु
	काष्ठा cal_buffer *buf = शून्य;

	spin_lock(&ctx->dma.lock);

	/* If the DMA context was stopping, it is now stopped. */
	अगर (ctx->dma.state == CAL_DMA_STOP_PENDING) अणु
		ctx->dma.state = CAL_DMA_STOPPED;
		wake_up(&ctx->dma.रुको);
	पूर्ण

	/* If a new buffer was queued, complete the current buffer. */
	अगर (ctx->dma.pending) अणु
		buf = ctx->dma.active;
		ctx->dma.active = ctx->dma.pending;
		ctx->dma.pending = शून्य;
	पूर्ण

	spin_unlock(&ctx->dma.lock);

	अगर (buf) अणु
		buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		buf->vb.field = ctx->v_fmt.fmt.pix.field;
		buf->vb.sequence = ctx->sequence++;
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण
पूर्ण

अटल irqवापस_t cal_irq(पूर्णांक irq_cal, व्योम *data)
अणु
	काष्ठा cal_dev *cal = data;
	u32 status;

	status = cal_पढ़ो(cal, CAL_HL_IRQSTATUS(0));
	अगर (status) अणु
		अचिन्हित पूर्णांक i;

		cal_ग_लिखो(cal, CAL_HL_IRQSTATUS(0), status);

		अगर (status & CAL_HL_IRQ_OCPO_ERR_MASK)
			dev_err_ratelimited(cal->dev, "OCPO ERROR\n");

		क्रम (i = 0; i < cal->data->num_csi2_phy; ++i) अणु
			अगर (status & CAL_HL_IRQ_CIO_MASK(i)) अणु
				u32 cio_stat = cal_पढ़ो(cal,
							CAL_CSI2_COMPLEXIO_IRQSTATUS(i));

				dev_err_ratelimited(cal->dev,
						    "CIO%u error: %#08x\n", i, cio_stat);

				cal_ग_लिखो(cal, CAL_CSI2_COMPLEXIO_IRQSTATUS(i),
					  cio_stat);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Check which DMA just finished */
	status = cal_पढ़ो(cal, CAL_HL_IRQSTATUS(1));
	अगर (status) अणु
		अचिन्हित पूर्णांक i;

		/* Clear Interrupt status */
		cal_ग_लिखो(cal, CAL_HL_IRQSTATUS(1), status);

		क्रम (i = 0; i < ARRAY_SIZE(cal->ctx); ++i) अणु
			अगर (status & CAL_HL_IRQ_MASK(i))
				cal_irq_wdma_end(cal->ctx[i]);
		पूर्ण
	पूर्ण

	/* Check which DMA just started */
	status = cal_पढ़ो(cal, CAL_HL_IRQSTATUS(2));
	अगर (status) अणु
		अचिन्हित पूर्णांक i;

		/* Clear Interrupt status */
		cal_ग_लिखो(cal, CAL_HL_IRQSTATUS(2), status);

		क्रम (i = 0; i < ARRAY_SIZE(cal->ctx); ++i) अणु
			अगर (status & CAL_HL_IRQ_MASK(i))
				cal_irq_wdma_start(cal->ctx[i]);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* ------------------------------------------------------------------
 *	Asynchronous V4L2 subdev binding
 * ------------------------------------------------------------------
 */

काष्ठा cal_v4l2_async_subdev अणु
	काष्ठा v4l2_async_subdev asd; /* Must be first */
	काष्ठा cal_camerarx *phy;
पूर्ण;

अटल अंतरभूत काष्ठा cal_v4l2_async_subdev *
to_cal_asd(काष्ठा v4l2_async_subdev *asd)
अणु
	वापस container_of(asd, काष्ठा cal_v4l2_async_subdev, asd);
पूर्ण

अटल पूर्णांक cal_async_notअगरier_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				    काष्ठा v4l2_subdev *subdev,
				    काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा cal_camerarx *phy = to_cal_asd(asd)->phy;
	पूर्णांक pad;
	पूर्णांक ret;

	अगर (phy->sensor) अणु
		phy_info(phy, "Rejecting subdev %s (Already set!!)",
			 subdev->name);
		वापस 0;
	पूर्ण

	phy->sensor = subdev;
	phy_dbg(1, phy, "Using sensor %s for capture\n", subdev->name);

	pad = media_entity_get_fwnode_pad(&subdev->entity,
					  of_fwnode_handle(phy->sensor_ep_node),
					  MEDIA_PAD_FL_SOURCE);
	अगर (pad < 0) अणु
		phy_err(phy, "Sensor %s has no connected source pad\n",
			subdev->name);
		वापस pad;
	पूर्ण

	ret = media_create_pad_link(&subdev->entity, pad,
				    &phy->subdev.entity, CAL_CAMERARX_PAD_SINK,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	अगर (ret) अणु
		phy_err(phy, "Failed to create media link for sensor %s\n",
			subdev->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cal_async_notअगरier_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा cal_dev *cal = container_of(notअगरier, काष्ठा cal_dev, notअगरier);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(cal->ctx); ++i) अणु
		अगर (cal->ctx[i])
			cal_ctx_v4l2_रेजिस्टर(cal->ctx[i]);
	पूर्ण

	अगर (cal_mc_api)
		ret = v4l2_device_रेजिस्टर_subdev_nodes(&cal->v4l2_dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations cal_async_notअगरier_ops = अणु
	.bound = cal_async_notअगरier_bound,
	.complete = cal_async_notअगरier_complete,
पूर्ण;

अटल पूर्णांक cal_async_notअगरier_रेजिस्टर(काष्ठा cal_dev *cal)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&cal->notअगरier);
	cal->notअगरier.ops = &cal_async_notअगरier_ops;

	क्रम (i = 0; i < cal->data->num_csi2_phy; ++i) अणु
		काष्ठा cal_camerarx *phy = cal->phy[i];
		काष्ठा cal_v4l2_async_subdev *casd;
		काष्ठा fwnode_handle *fwnode;

		अगर (!phy->sensor_node)
			जारी;

		fwnode = of_fwnode_handle(phy->sensor_node);
		casd = v4l2_async_notअगरier_add_fwnode_subdev(&cal->notअगरier,
							     fwnode,
							     काष्ठा cal_v4l2_async_subdev);
		अगर (IS_ERR(casd)) अणु
			phy_err(phy, "Failed to add subdev to notifier\n");
			ret = PTR_ERR(casd);
			जाओ error;
		पूर्ण

		casd->phy = phy;
	पूर्ण

	ret = v4l2_async_notअगरier_रेजिस्टर(&cal->v4l2_dev, &cal->notअगरier);
	अगर (ret) अणु
		cal_err(cal, "Error registering async notifier\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	v4l2_async_notअगरier_cleanup(&cal->notअगरier);
	वापस ret;
पूर्ण

अटल व्योम cal_async_notअगरier_unरेजिस्टर(काष्ठा cal_dev *cal)
अणु
	v4l2_async_notअगरier_unरेजिस्टर(&cal->notअगरier);
	v4l2_async_notअगरier_cleanup(&cal->notअगरier);
पूर्ण

/* ------------------------------------------------------------------
 *	Media and V4L2 device handling
 * ------------------------------------------------------------------
 */

/*
 * Register user-facing devices. To be called at the end of the probe function
 * when all resources are initialized and पढ़ोy.
 */
अटल पूर्णांक cal_media_रेजिस्टर(काष्ठा cal_dev *cal)
अणु
	पूर्णांक ret;

	ret = media_device_रेजिस्टर(&cal->mdev);
	अगर (ret) अणु
		cal_err(cal, "Failed to register media device\n");
		वापस ret;
	पूर्ण

	/*
	 * Register the async notअगरier. This may trigger registration of the
	 * V4L2 video devices अगर all subdevs are पढ़ोy.
	 */
	ret = cal_async_notअगरier_रेजिस्टर(cal);
	अगर (ret) अणु
		media_device_unरेजिस्टर(&cal->mdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Unरेजिस्टर the user-facing devices, but करोn't मुक्त memory yet. To be called
 * at the beginning of the हटाओ function, to disallow access from userspace.
 */
अटल व्योम cal_media_unरेजिस्टर(काष्ठा cal_dev *cal)
अणु
	अचिन्हित पूर्णांक i;

	/* Unरेजिस्टर all the V4L2 video devices. */
	क्रम (i = 0; i < ARRAY_SIZE(cal->ctx); i++) अणु
		अगर (cal->ctx[i])
			cal_ctx_v4l2_unरेजिस्टर(cal->ctx[i]);
	पूर्ण

	cal_async_notअगरier_unरेजिस्टर(cal);
	media_device_unरेजिस्टर(&cal->mdev);
पूर्ण

/*
 * Initialize the in-kernel objects. To be called at the beginning of the probe
 * function, beक्रमe the V4L2 device is used by the driver.
 */
अटल पूर्णांक cal_media_init(काष्ठा cal_dev *cal)
अणु
	काष्ठा media_device *mdev = &cal->mdev;
	पूर्णांक ret;

	mdev->dev = cal->dev;
	mdev->hw_revision = cal->revision;
	strscpy(mdev->model, "CAL", माप(mdev->model));
	snम_लिखो(mdev->bus_info, माप(mdev->bus_info), "platform:%s",
		 dev_name(mdev->dev));
	media_device_init(mdev);

	/*
	 * Initialize the V4L2 device (despite the function name, this perक्रमms
	 * initialization, not registration).
	 */
	cal->v4l2_dev.mdev = mdev;
	ret = v4l2_device_रेजिस्टर(cal->dev, &cal->v4l2_dev);
	अगर (ret) अणु
		cal_err(cal, "Failed to register V4L2 device\n");
		वापस ret;
	पूर्ण

	vb2_dma_contig_set_max_seg_size(cal->dev, DMA_BIT_MASK(32));

	वापस 0;
पूर्ण

/*
 * Cleanup the in-kernel objects, मुक्तing memory. To be called at the very end
 * of the हटाओ sequence, when nothing (including userspace) can access the
 * objects anymore.
 */
अटल व्योम cal_media_cleanup(काष्ठा cal_dev *cal)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cal->ctx); i++) अणु
		अगर (cal->ctx[i])
			cal_ctx_v4l2_cleanup(cal->ctx[i]);
	पूर्ण

	v4l2_device_unरेजिस्टर(&cal->v4l2_dev);
	media_device_cleanup(&cal->mdev);

	vb2_dma_contig_clear_max_seg_size(cal->dev);
पूर्ण

/* ------------------------------------------------------------------
 *	Initialization and module stuff
 * ------------------------------------------------------------------
 */

अटल काष्ठा cal_ctx *cal_ctx_create(काष्ठा cal_dev *cal, पूर्णांक inst)
अणु
	काष्ठा cal_ctx *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(cal->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	ctx->cal = cal;
	ctx->phy = cal->phy[inst];
	ctx->index = inst;
	ctx->cport = inst;

	ret = cal_ctx_v4l2_init(ctx);
	अगर (ret)
		वापस शून्य;

	वापस ctx;
पूर्ण

अटल स्थिर काष्ठा of_device_id cal_of_match[] = अणु
	अणु
		.compatible = "ti,dra72-cal",
		.data = (व्योम *)&dra72x_cal_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra72-pre-es2-cal",
		.data = (व्योम *)&dra72x_es1_cal_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra76-cal",
		.data = (व्योम *)&dra76x_cal_data,
	पूर्ण,
	अणु
		.compatible = "ti,am654-cal",
		.data = (व्योम *)&am654_cal_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cal_of_match);

/* Get hardware revision and info. */

#घोषणा CAL_HL_HWINFO_VALUE		0xa3c90469

अटल व्योम cal_get_hwinfo(काष्ठा cal_dev *cal)
अणु
	u32 hwinfo;

	cal->revision = cal_पढ़ो(cal, CAL_HL_REVISION);
	चयन (FIELD_GET(CAL_HL_REVISION_SCHEME_MASK, cal->revision)) अणु
	हाल CAL_HL_REVISION_SCHEME_H08:
		cal_dbg(3, cal, "CAL HW revision %lu.%lu.%lu (0x%08x)\n",
			FIELD_GET(CAL_HL_REVISION_MAJOR_MASK, cal->revision),
			FIELD_GET(CAL_HL_REVISION_MINOR_MASK, cal->revision),
			FIELD_GET(CAL_HL_REVISION_RTL_MASK, cal->revision),
			cal->revision);
		अवरोध;

	हाल CAL_HL_REVISION_SCHEME_LEGACY:
	शेष:
		cal_info(cal, "Unexpected CAL HW revision 0x%08x\n",
			 cal->revision);
		अवरोध;
	पूर्ण

	hwinfo = cal_पढ़ो(cal, CAL_HL_HWINFO);
	अगर (hwinfo != CAL_HL_HWINFO_VALUE)
		cal_info(cal, "CAL_HL_HWINFO = 0x%08x, expected 0x%08x\n",
			 hwinfo, CAL_HL_HWINFO_VALUE);
पूर्ण

अटल पूर्णांक cal_init_camerarx_regmap(काष्ठा cal_dev *cal)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(cal->dev);
	काष्ठा device_node *np = cal->dev->of_node;
	काष्ठा regmap_config config = अणु पूर्ण;
	काष्ठा regmap *syscon;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक offset;
	व्योम __iomem *base;

	syscon = syscon_regmap_lookup_by_phandle_args(np, "ti,camerrx-control",
						      1, &offset);
	अगर (!IS_ERR(syscon)) अणु
		cal->syscon_camerrx = syscon;
		cal->syscon_camerrx_offset = offset;
		वापस 0;
	पूर्ण

	dev_warn(cal->dev, "failed to get ti,camerrx-control: %ld\n",
		 PTR_ERR(syscon));

	/*
	 * Backward DTS compatibility. If syscon entry is not present then
	 * check अगर the camerrx_control resource is present.
	 */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "camerrx_control");
	base = devm_ioremap_resource(cal->dev, res);
	अगर (IS_ERR(base)) अणु
		cal_err(cal, "failed to ioremap camerrx_control\n");
		वापस PTR_ERR(base);
	पूर्ण

	cal_dbg(1, cal, "ioresource %s at %pa - %pa\n",
		res->name, &res->start, &res->end);

	config.reg_bits = 32;
	config.reg_stride = 4;
	config.val_bits = 32;
	config.max_रेजिस्टर = resource_size(res) - 4;

	syscon = regmap_init_mmio(शून्य, base, &config);
	अगर (IS_ERR(syscon)) अणु
		pr_err("regmap init failed\n");
		वापस PTR_ERR(syscon);
	पूर्ण

	/*
	 * In this हाल the base alपढ़ोy poपूर्णांक to the direct CM रेजिस्टर so no
	 * need क्रम an offset.
	 */
	cal->syscon_camerrx = syscon;
	cal->syscon_camerrx_offset = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cal_dev *cal;
	काष्ठा cal_ctx *ctx;
	bool connected = false;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक irq;

	cal = devm_kzalloc(&pdev->dev, माप(*cal), GFP_KERNEL);
	अगर (!cal)
		वापस -ENOMEM;

	cal->data = of_device_get_match_data(&pdev->dev);
	अगर (!cal->data) अणु
		dev_err(&pdev->dev, "Could not get feature data based on compatible version\n");
		वापस -ENODEV;
	पूर्ण

	cal->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, cal);

	/* Acquire resources: घड़ीs, CAMERARX regmap, I/O memory and IRQ. */
	cal->fclk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(cal->fclk)) अणु
		dev_err(&pdev->dev, "cannot get CAL fclk\n");
		वापस PTR_ERR(cal->fclk);
	पूर्ण

	ret = cal_init_camerarx_regmap(cal);
	अगर (ret < 0)
		वापस ret;

	cal->res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						"cal_top");
	cal->base = devm_ioremap_resource(&pdev->dev, cal->res);
	अगर (IS_ERR(cal->base))
		वापस PTR_ERR(cal->base);

	cal_dbg(1, cal, "ioresource %s at %pa - %pa\n",
		cal->res->name, &cal->res->start, &cal->res->end);

	irq = platक्रमm_get_irq(pdev, 0);
	cal_dbg(1, cal, "got irq# %d\n", irq);
	ret = devm_request_irq(&pdev->dev, irq, cal_irq, 0, CAL_MODULE_NAME,
			       cal);
	अगर (ret)
		वापस ret;

	/* Read the revision and hardware info to verअगरy hardware access. */
	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret)
		जाओ error_pm_runसमय;

	cal_get_hwinfo(cal);
	pm_runसमय_put_sync(&pdev->dev);

	/* Initialize the media device. */
	ret = cal_media_init(cal);
	अगर (ret < 0)
		जाओ error_pm_runसमय;

	/* Create CAMERARX PHYs. */
	क्रम (i = 0; i < cal->data->num_csi2_phy; ++i) अणु
		cal->phy[i] = cal_camerarx_create(cal, i);
		अगर (IS_ERR(cal->phy[i])) अणु
			ret = PTR_ERR(cal->phy[i]);
			cal->phy[i] = शून्य;
			जाओ error_camerarx;
		पूर्ण

		अगर (cal->phy[i]->sensor_node)
			connected = true;
	पूर्ण

	अगर (!connected) अणु
		cal_err(cal, "Neither port is configured, no point in staying up\n");
		ret = -ENODEV;
		जाओ error_camerarx;
	पूर्ण

	/* Create contexts. */
	क्रम (i = 0; i < cal->data->num_csi2_phy; ++i) अणु
		अगर (!cal->phy[i]->sensor_node)
			जारी;

		cal->ctx[i] = cal_ctx_create(cal, i);
		अगर (!cal->ctx[i]) अणु
			cal_err(cal, "Failed to create context %u\n", i);
			ret = -ENODEV;
			जाओ error_context;
		पूर्ण
	पूर्ण

	/* Register the media device. */
	ret = cal_media_रेजिस्टर(cal);
	अगर (ret)
		जाओ error_context;

	वापस 0;

error_context:
	क्रम (i = 0; i < ARRAY_SIZE(cal->ctx); i++) अणु
		ctx = cal->ctx[i];
		अगर (ctx)
			cal_ctx_v4l2_cleanup(ctx);
	पूर्ण

error_camerarx:
	क्रम (i = 0; i < cal->data->num_csi2_phy; i++)
		cal_camerarx_destroy(cal->phy[i]);

	cal_media_cleanup(cal);

error_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक cal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cal_dev *cal = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;

	cal_dbg(1, cal, "Removing %s\n", CAL_MODULE_NAME);

	pm_runसमय_get_sync(&pdev->dev);

	cal_media_unरेजिस्टर(cal);

	क्रम (i = 0; i < ARRAY_SIZE(cal->phy); i++) अणु
		अगर (cal->phy[i])
			cal_camerarx_disable(cal->phy[i]);
	पूर्ण

	cal_media_cleanup(cal);

	क्रम (i = 0; i < cal->data->num_csi2_phy; i++)
		cal_camerarx_destroy(cal->phy[i]);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cal_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cal_dev *cal = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	अगर (cal->data->flags & DRA72_CAL_PRE_ES2_LDO_DISABLE) अणु
		/*
		 * Apply errata on both port everyसमय we (re-)enable
		 * the घड़ी
		 */
		क्रम (i = 0; i < cal->data->num_csi2_phy; i++)
			cal_camerarx_i913_errata(cal->phy[i]);
	पूर्ण

	/*
	 * Enable global पूर्णांकerrupts that are not related to a particular
	 * CAMERARAX or context.
	 */
	cal_ग_लिखो(cal, CAL_HL_IRQENABLE_SET(0), CAL_HL_IRQ_OCPO_ERR_MASK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cal_pm_ops = अणु
	.runसमय_resume = cal_runसमय_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver cal_pdrv = अणु
	.probe		= cal_probe,
	.हटाओ		= cal_हटाओ,
	.driver		= अणु
		.name	= CAL_MODULE_NAME,
		.pm	= &cal_pm_ops,
		.of_match_table = cal_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cal_pdrv);
