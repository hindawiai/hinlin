<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung s3c24xx/s3c64xx SoC CAMIF driver
 *
 * Copyright (C) 2012 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 * Copyright (C) 2012 Tomasz Figa <tomasz.figa@gmail.com>
*/
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/delay.h>
#समावेश "camif-regs.h"

#घोषणा camअगर_ग_लिखो(_camअगर, _off, _val)	ग_लिखोl(_val, (_camअगर)->io_base + (_off))
#घोषणा camअगर_पढ़ो(_camअगर, _off)	पढ़ोl((_camअगर)->io_base + (_off))

व्योम camअगर_hw_reset(काष्ठा camअगर_dev *camअगर)
अणु
	u32 cfg;

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CISRCFMT);
	cfg |= CISRCFMT_ITU601_8BIT;
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISRCFMT, cfg);

	/* S/W reset */
	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIGCTRL);
	cfg |= CIGCTRL_SWRST;
	अगर (camअगर->variant->ip_revision == S3C6410_CAMIF_IP_REV)
		cfg |= CIGCTRL_IRQ_LEVEL;
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIGCTRL, cfg);
	udelay(10);

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIGCTRL);
	cfg &= ~CIGCTRL_SWRST;
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIGCTRL, cfg);
	udelay(10);
पूर्ण

व्योम camअगर_hw_clear_pending_irq(काष्ठा camअगर_vp *vp)
अणु
	u32 cfg = camअगर_पढ़ो(vp->camअगर, S3C_CAMIF_REG_CIGCTRL);
	cfg |= CIGCTRL_IRQ_CLR(vp->id);
	camअगर_ग_लिखो(vp->camअगर, S3C_CAMIF_REG_CIGCTRL, cfg);
पूर्ण

/*
 * Sets video test pattern (off, color bar, horizontal or vertical gradient).
 * External sensor pixel घड़ी must be active क्रम the test pattern to work.
 */
व्योम camअगर_hw_set_test_pattern(काष्ठा camअगर_dev *camअगर, अचिन्हित पूर्णांक pattern)
अणु
	u32 cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIGCTRL);
	cfg &= ~CIGCTRL_TESTPATTERN_MASK;
	cfg |= (pattern << 27);
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIGCTRL, cfg);
पूर्ण

व्योम camअगर_hw_set_effect(काष्ठा camअगर_dev *camअगर, अचिन्हित पूर्णांक effect,
			अचिन्हित पूर्णांक cr, अचिन्हित पूर्णांक cb)
अणु
	अटल स्थिर काष्ठा v4l2_control colorfx[] = अणु
		अणु V4L2_COLORFX_NONE,		CIIMGEFF_FIN_BYPASS पूर्ण,
		अणु V4L2_COLORFX_BW,		CIIMGEFF_FIN_ARBITRARY पूर्ण,
		अणु V4L2_COLORFX_SEPIA,		CIIMGEFF_FIN_ARBITRARY पूर्ण,
		अणु V4L2_COLORFX_NEGATIVE,	CIIMGEFF_FIN_NEGATIVE पूर्ण,
		अणु V4L2_COLORFX_ART_FREEZE,	CIIMGEFF_FIN_ARTFREEZE पूर्ण,
		अणु V4L2_COLORFX_EMBOSS,		CIIMGEFF_FIN_EMBOSSING पूर्ण,
		अणु V4L2_COLORFX_SILHOUETTE,	CIIMGEFF_FIN_SILHOUETTE पूर्ण,
		अणु V4L2_COLORFX_SET_CBCR,	CIIMGEFF_FIN_ARBITRARY पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i, cfg;

	क्रम (i = 0; i < ARRAY_SIZE(colorfx); i++)
		अगर (colorfx[i].id == effect)
			अवरोध;

	अगर (i == ARRAY_SIZE(colorfx))
		वापस;

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIIMGEFF(camअगर->vp->offset));
	/* Set effect */
	cfg &= ~CIIMGEFF_FIN_MASK;
	cfg |= colorfx[i].value;
	/* Set both paths */
	अगर (camअगर->variant->ip_revision >= S3C6400_CAMIF_IP_REV) अणु
		अगर (effect == V4L2_COLORFX_NONE)
			cfg &= ~CIIMGEFF_IE_ENABLE_MASK;
		अन्यथा
			cfg |= CIIMGEFF_IE_ENABLE_MASK;
	पूर्ण
	cfg &= ~CIIMGEFF_PAT_CBCR_MASK;
	cfg |= cr | (cb << 13);
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIIMGEFF(camअगर->vp->offset), cfg);
पूर्ण

अटल स्थिर u32 src_pixfmt_map[8][2] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_2X8, CISRCFMT_ORDER422_YCBYCR पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, CISRCFMT_ORDER422_YCRYCB पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, CISRCFMT_ORDER422_CBYCRY पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, CISRCFMT_ORDER422_CRYCBY पूर्ण,
पूर्ण;

/* Set camera input pixel क्रमmat and resolution */
व्योम camअगर_hw_set_source_क्रमmat(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &camअगर->mbus_fmt;
	पूर्णांक i;
	u32 cfg;

	क्रम (i = ARRAY_SIZE(src_pixfmt_map) - 1; i >= 0; i--) अणु
		अगर (src_pixfmt_map[i][0] == mf->code)
			अवरोध;
	पूर्ण
	अगर (i < 0) अणु
		i = 0;
		dev_err(camअगर->dev,
			"Unsupported pixel code, falling back to %#08x\n",
			src_pixfmt_map[i][0]);
	पूर्ण

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CISRCFMT);
	cfg &= ~(CISRCFMT_ORDER422_MASK | CISRCFMT_SIZE_CAM_MASK);
	cfg |= (mf->width << 16) | mf->height;
	cfg |= src_pixfmt_map[i][1];
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISRCFMT, cfg);
पूर्ण

/* Set the camera host input winकरोw offsets (cropping) */
व्योम camअगर_hw_set_camera_crop(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &camअगर->mbus_fmt;
	काष्ठा v4l2_rect *crop = &camअगर->camअगर_crop;
	u32 hoff2, voff2;
	u32 cfg;

	/* Note: s3c244x requirement: left = f_width - rect.width / 2 */
	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIWDOFST);
	cfg &= ~(CIWDOFST_OFST_MASK | CIWDOFST_WINOFSEN);
	cfg |= (crop->left << 16) | crop->top;
	अगर (crop->left != 0 || crop->top != 0)
		cfg |= CIWDOFST_WINOFSEN;
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIWDOFST, cfg);

	अगर (camअगर->variant->ip_revision == S3C6410_CAMIF_IP_REV) अणु
		hoff2 = mf->width - crop->width - crop->left;
		voff2 = mf->height - crop->height - crop->top;
		cfg = (hoff2 << 16) | voff2;
		camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIWDOFST2, cfg);
	पूर्ण
पूर्ण

व्योम camअगर_hw_clear_fअगरo_overflow(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	u32 cfg;

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIWDOFST);
	अगर (vp->id == 0)
		cfg |= (CIWDOFST_CLROVCOFIY | CIWDOFST_CLROVCOFICB |
			CIWDOFST_CLROVCOFICR);
	अन्यथा
		cfg |= (/* CIWDOFST_CLROVPRFIY | */ CIWDOFST_CLROVPRFICB |
			CIWDOFST_CLROVPRFICR);
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIWDOFST, cfg);
पूर्ण

/* Set video bus संकेतs polarity */
व्योम camअगर_hw_set_camera_bus(काष्ठा camअगर_dev *camअगर)
अणु
	अचिन्हित पूर्णांक flags = camअगर->pdata.sensor.flags;

	u32 cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIGCTRL);

	cfg &= ~(CIGCTRL_INVPOLPCLK | CIGCTRL_INVPOLVSYNC |
		 CIGCTRL_INVPOLHREF | CIGCTRL_INVPOLFIELD);

	अगर (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		cfg |= CIGCTRL_INVPOLPCLK;

	अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		cfg |= CIGCTRL_INVPOLVSYNC;
	/*
	 * HREF is normally high during frame active data
	 * transmission and low during horizontal synchronization
	 * period. Thus HREF active high means HSYNC active low.
	 */
	अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		cfg |= CIGCTRL_INVPOLHREF; /* HREF active low */

	अगर (camअगर->variant->ip_revision == S3C6410_CAMIF_IP_REV) अणु
		अगर (flags & V4L2_MBUS_FIELD_EVEN_LOW)
			cfg |= CIGCTRL_INVPOLFIELD;
		cfg |= CIGCTRL_FIELDMODE;
	पूर्ण

	pr_debug("Setting CIGCTRL to: %#x\n", cfg);

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIGCTRL, cfg);
पूर्ण

व्योम camअगर_hw_set_output_addr(काष्ठा camअगर_vp *vp,
			      काष्ठा camअगर_addr *paddr, पूर्णांक i)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIYSA(vp->id, i), paddr->y);
	अगर (camअगर->variant->ip_revision == S3C6410_CAMIF_IP_REV
		|| vp->id == VP_CODEC) अणु
		camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CICBSA(vp->id, i),
								paddr->cb);
		camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CICRSA(vp->id, i),
								paddr->cr);
	पूर्ण

	pr_debug("dst_buf[%d]: %pad, cb: %pad, cr: %pad\n",
		 i, &paddr->y, &paddr->cb, &paddr->cr);
पूर्ण

अटल व्योम camअगर_hw_set_out_dma_size(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_frame *frame = &vp->out_frame;
	u32 cfg;

	cfg = camअगर_पढ़ो(vp->camअगर, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset));
	cfg &= ~CITRGFMT_TARGETSIZE_MASK;
	cfg |= (frame->f_width << 16) | frame->f_height;
	camअगर_ग_लिखो(vp->camअगर, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset), cfg);
पूर्ण

अटल व्योम camअगर_get_dma_burst(u32 width, u32 ybpp, u32 *mburst, u32 *rburst)
अणु
	अचिन्हित पूर्णांक nwords = width * ybpp / 4;
	अचिन्हित पूर्णांक भाग, rem;

	अगर (WARN_ON(width < 8 || (width * ybpp) & 7))
		वापस;

	क्रम (भाग = 16; भाग >= 2; भाग /= 2) अणु
		अगर (nwords < भाग)
			जारी;

		rem = nwords & (भाग - 1);
		अगर (rem == 0) अणु
			*mburst = भाग;
			*rburst = भाग;
			अवरोध;
		पूर्ण
		अगर (rem == भाग / 2 || rem == भाग / 4) अणु
			*mburst = भाग;
			*rburst = rem;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम camअगर_hw_set_output_dma(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा camअगर_frame *frame = &vp->out_frame;
	स्थिर काष्ठा camअगर_fmt *fmt = vp->out_fmt;
	अचिन्हित पूर्णांक ymburst = 0, yrburst = 0;
	u32 cfg;

	camअगर_hw_set_out_dma_size(vp);

	अगर (camअगर->variant->ip_revision == S3C6410_CAMIF_IP_REV) अणु
		काष्ठा camअगर_dma_offset *offset = &frame->dma_offset;
		/* Set the input dma offsets. */
		cfg = S3C_CISS_OFFS_INITIAL(offset->initial);
		cfg |= S3C_CISS_OFFS_LINE(offset->line);
		camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISSY(vp->id), cfg);
		camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISSCB(vp->id), cfg);
		camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISSCR(vp->id), cfg);
	पूर्ण

	/* Configure DMA burst values */
	camअगर_get_dma_burst(frame->rect.width, fmt->ybpp, &ymburst, &yrburst);

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CICTRL(vp->id, vp->offset));
	cfg &= ~CICTRL_BURST_MASK;

	cfg |= CICTRL_YBURST1(ymburst) | CICTRL_YBURST2(yrburst);
	cfg |= CICTRL_CBURST1(ymburst / 2) | CICTRL_CBURST2(yrburst / 2);

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CICTRL(vp->id, vp->offset), cfg);

	pr_debug("ymburst: %u, yrburst: %u\n", ymburst, yrburst);
पूर्ण

व्योम camअगर_hw_set_input_path(काष्ठा camअगर_vp *vp)
अणु
	u32 cfg = camअगर_पढ़ो(vp->camअगर, S3C_CAMIF_REG_MSCTRL(vp->id));
	cfg &= ~MSCTRL_SEL_DMA_CAM;
	camअगर_ग_लिखो(vp->camअगर, S3C_CAMIF_REG_MSCTRL(vp->id), cfg);
पूर्ण

व्योम camअगर_hw_set_target_क्रमmat(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा camअगर_frame *frame = &vp->out_frame;
	u32 cfg;

	pr_debug("fw: %d, fh: %d color: %d\n", frame->f_width,
		 frame->f_height, vp->out_fmt->color);

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset));
	cfg &= ~CITRGFMT_TARGETSIZE_MASK;

	अगर (camअगर->variant->ip_revision == S3C244X_CAMIF_IP_REV) अणु
		/* We currently support only YCbCr 4:2:2 at the camera input */
		cfg |= CITRGFMT_IN422;
		cfg &= ~CITRGFMT_OUT422;
		अगर (vp->out_fmt->color == IMG_FMT_YCBCR422P)
			cfg |= CITRGFMT_OUT422;
	पूर्ण अन्यथा अणु
		cfg &= ~CITRGFMT_OUTFORMAT_MASK;
		चयन (vp->out_fmt->color) अणु
		हाल IMG_FMT_RGB565...IMG_FMT_XRGB8888:
			cfg |= CITRGFMT_OUTFORMAT_RGB;
			अवरोध;
		हाल IMG_FMT_YCBCR420...IMG_FMT_YCRCB420:
			cfg |= CITRGFMT_OUTFORMAT_YCBCR420;
			अवरोध;
		हाल IMG_FMT_YCBCR422P:
			cfg |= CITRGFMT_OUTFORMAT_YCBCR422;
			अवरोध;
		हाल IMG_FMT_YCBYCR422...IMG_FMT_CRYCBY422:
			cfg |= CITRGFMT_OUTFORMAT_YCBCR422I;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Rotation is only supported by s3c64xx */
	अगर (vp->rotation == 90 || vp->rotation == 270)
		cfg |= (frame->f_height << 16) | frame->f_width;
	अन्यथा
		cfg |= (frame->f_width << 16) | frame->f_height;
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset), cfg);

	/* Target area, output pixel width * height */
	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CITAREA(vp->id, vp->offset));
	cfg &= ~CITAREA_MASK;
	cfg |= (frame->f_width * frame->f_height);
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CITAREA(vp->id, vp->offset), cfg);
पूर्ण

व्योम camअगर_hw_set_flip(काष्ठा camअगर_vp *vp)
अणु
	u32 cfg = camअगर_पढ़ो(vp->camअगर,
				S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset));

	cfg &= ~CITRGFMT_FLIP_MASK;

	अगर (vp->hflip)
		cfg |= CITRGFMT_FLIP_Y_MIRROR;
	अगर (vp->vflip)
		cfg |= CITRGFMT_FLIP_X_MIRROR;

	camअगर_ग_लिखो(vp->camअगर, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset), cfg);
पूर्ण

अटल व्योम camअगर_hw_set_prescaler(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा camअगर_scaler *sc = &vp->scaler;
	u32 cfg, shfactor, addr;

	addr = S3C_CAMIF_REG_CISCPRERATIO(vp->id, vp->offset);

	shfactor = 10 - (sc->h_shअगरt + sc->v_shअगरt);
	cfg = shfactor << 28;

	cfg |= (sc->pre_h_ratio << 16) | sc->pre_v_ratio;
	camअगर_ग_लिखो(camअगर, addr, cfg);

	cfg = (sc->pre_dst_width << 16) | sc->pre_dst_height;
	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISCPREDST(vp->id, vp->offset), cfg);
पूर्ण

अटल व्योम camअगर_s3c244x_hw_set_scaler(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा camअगर_scaler *scaler = &vp->scaler;
	अचिन्हित पूर्णांक color = vp->out_fmt->color;
	u32 cfg;

	camअगर_hw_set_prescaler(vp);

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CISCCTRL(vp->id, vp->offset));

	cfg &= ~(CISCCTRL_SCALEUP_MASK | CISCCTRL_SCALERBYPASS |
		 CISCCTRL_MAIN_RATIO_MASK | CIPRSCCTRL_RGB_FORMAT_24BIT);

	अगर (scaler->enable) अणु
		अगर (scaler->scaleup_h) अणु
			अगर (vp->id == VP_CODEC)
				cfg |= CISCCTRL_SCALEUP_H;
			अन्यथा
				cfg |= CIPRSCCTRL_SCALEUP_H;
		पूर्ण
		अगर (scaler->scaleup_v) अणु
			अगर (vp->id == VP_CODEC)
				cfg |= CISCCTRL_SCALEUP_V;
			अन्यथा
				cfg |= CIPRSCCTRL_SCALEUP_V;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (vp->id == VP_CODEC)
			cfg |= CISCCTRL_SCALERBYPASS;
	पूर्ण

	cfg |= ((scaler->मुख्य_h_ratio & 0x1ff) << 16);
	cfg |= scaler->मुख्य_v_ratio & 0x1ff;

	अगर (vp->id == VP_PREVIEW) अणु
		अगर (color == IMG_FMT_XRGB8888)
			cfg |= CIPRSCCTRL_RGB_FORMAT_24BIT;
		cfg |= CIPRSCCTRL_SAMPLE;
	पूर्ण

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISCCTRL(vp->id, vp->offset), cfg);

	pr_debug("main: h_ratio: %#x, v_ratio: %#x",
		 scaler->मुख्य_h_ratio, scaler->मुख्य_v_ratio);
पूर्ण

अटल व्योम camअगर_s3c64xx_hw_set_scaler(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	काष्ठा camअगर_scaler *scaler = &vp->scaler;
	अचिन्हित पूर्णांक color = vp->out_fmt->color;
	u32 cfg;

	camअगर_hw_set_prescaler(vp);

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CISCCTRL(vp->id, vp->offset));

	cfg &= ~(CISCCTRL_CSCR2Y_WIDE | CISCCTRL_CSCY2R_WIDE
		| CISCCTRL_SCALEUP_H | CISCCTRL_SCALEUP_V
		| CISCCTRL_SCALERBYPASS | CISCCTRL_ONE2ONE
		| CISCCTRL_INRGB_FMT_MASK | CISCCTRL_OUTRGB_FMT_MASK
		| CISCCTRL_INTERLACE | CISCCTRL_EXTRGB_EXTENSION
		| CISCCTRL_MAIN_RATIO_MASK);

	cfg |= (CISCCTRL_CSCR2Y_WIDE | CISCCTRL_CSCY2R_WIDE);

	अगर (!scaler->enable) अणु
		cfg |= CISCCTRL_SCALERBYPASS;
	पूर्ण अन्यथा अणु
		अगर (scaler->scaleup_h)
			cfg |= CISCCTRL_SCALEUP_H;
		अगर (scaler->scaleup_v)
			cfg |= CISCCTRL_SCALEUP_V;
		अगर (scaler->copy)
			cfg |= CISCCTRL_ONE2ONE;
	पूर्ण

	चयन (color) अणु
	हाल IMG_FMT_RGB666:
		cfg |= CISCCTRL_OUTRGB_FMT_RGB666;
		अवरोध;
	हाल IMG_FMT_XRGB8888:
		cfg |= CISCCTRL_OUTRGB_FMT_RGB888;
		अवरोध;
	पूर्ण

	cfg |= (scaler->मुख्य_h_ratio & 0x1ff) << 16;
	cfg |= scaler->मुख्य_v_ratio & 0x1ff;

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CISCCTRL(vp->id, vp->offset), cfg);

	pr_debug("main: h_ratio: %#x, v_ratio: %#x",
		 scaler->मुख्य_h_ratio, scaler->मुख्य_v_ratio);
पूर्ण

व्योम camअगर_hw_set_scaler(काष्ठा camअगर_vp *vp)
अणु
	अचिन्हित पूर्णांक ip_rev = vp->camअगर->variant->ip_revision;

	अगर (ip_rev == S3C244X_CAMIF_IP_REV)
		camअगर_s3c244x_hw_set_scaler(vp);
	अन्यथा
		camअगर_s3c64xx_hw_set_scaler(vp);
पूर्ण

व्योम camअगर_hw_enable_scaler(काष्ठा camअगर_vp *vp, bool on)
अणु
	u32 addr = S3C_CAMIF_REG_CISCCTRL(vp->id, vp->offset);
	u32 cfg;

	cfg = camअगर_पढ़ो(vp->camअगर, addr);
	अगर (on)
		cfg |= CISCCTRL_SCALERSTART;
	अन्यथा
		cfg &= ~CISCCTRL_SCALERSTART;
	camअगर_ग_लिखो(vp->camअगर, addr, cfg);
पूर्ण

व्योम camअगर_hw_set_lastirq(काष्ठा camअगर_vp *vp, पूर्णांक enable)
अणु
	u32 addr = S3C_CAMIF_REG_CICTRL(vp->id, vp->offset);
	u32 cfg;

	cfg = camअगर_पढ़ो(vp->camअगर, addr);
	अगर (enable)
		cfg |= CICTRL_LASTIRQ_ENABLE;
	अन्यथा
		cfg &= ~CICTRL_LASTIRQ_ENABLE;
	camअगर_ग_लिखो(vp->camअगर, addr, cfg);
पूर्ण

व्योम camअगर_hw_enable_capture(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	u32 cfg;

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIIMGCPT(vp->offset));
	camअगर->stream_count++;

	अगर (camअगर->variant->ip_revision == S3C6410_CAMIF_IP_REV)
		cfg |= CIIMGCPT_CPT_FREN_ENABLE(vp->id);

	अगर (vp->scaler.enable)
		cfg |= CIIMGCPT_IMGCPTEN_SC(vp->id);

	अगर (camअगर->stream_count == 1)
		cfg |= CIIMGCPT_IMGCPTEN;

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIIMGCPT(vp->offset), cfg);

	pr_debug("CIIMGCPT: %#x, camif->stream_count: %d\n",
		 cfg, camअगर->stream_count);
पूर्ण

व्योम camअगर_hw_disable_capture(काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_dev *camअगर = vp->camअगर;
	u32 cfg;

	cfg = camअगर_पढ़ो(camअगर, S3C_CAMIF_REG_CIIMGCPT(vp->offset));
	cfg &= ~CIIMGCPT_IMGCPTEN_SC(vp->id);

	अगर (WARN_ON(--(camअगर->stream_count) < 0))
		camअगर->stream_count = 0;

	अगर (camअगर->stream_count == 0)
		cfg &= ~CIIMGCPT_IMGCPTEN;

	pr_debug("CIIMGCPT: %#x, camif->stream_count: %d\n",
		 cfg, camअगर->stream_count);

	camअगर_ग_लिखो(camअगर, S3C_CAMIF_REG_CIIMGCPT(vp->offset), cfg);
पूर्ण

व्योम camअगर_hw_dump_regs(काष्ठा camअगर_dev *camअगर, स्थिर अक्षर *label)
अणु
	अटल स्थिर काष्ठा अणु
		u32 offset;
		स्थिर अक्षर * स्थिर name;
	पूर्ण रेजिस्टरs[] = अणु
		अणु S3C_CAMIF_REG_CISRCFMT,		"CISRCFMT" पूर्ण,
		अणु S3C_CAMIF_REG_CIWDOFST,		"CIWDOFST" पूर्ण,
		अणु S3C_CAMIF_REG_CIGCTRL,		"CIGCTRL" पूर्ण,
		अणु S3C_CAMIF_REG_CIWDOFST2,		"CIWDOFST2" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(0, 0),		"CICOYSA0" पूर्ण,
		अणु S3C_CAMIF_REG_CICBSA(0, 0),		"CICOCBSA0" पूर्ण,
		अणु S3C_CAMIF_REG_CICRSA(0, 0),		"CICOCRSA0" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(0, 1),		"CICOYSA1" पूर्ण,
		अणु S3C_CAMIF_REG_CICBSA(0, 1),		"CICOCBSA1" पूर्ण,
		अणु S3C_CAMIF_REG_CICRSA(0, 1),		"CICOCRSA1" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(0, 2),		"CICOYSA2" पूर्ण,
		अणु S3C_CAMIF_REG_CICBSA(0, 2),		"CICOCBSA2" पूर्ण,
		अणु S3C_CAMIF_REG_CICRSA(0, 2),		"CICOCRSA2" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(0, 3),		"CICOYSA3" पूर्ण,
		अणु S3C_CAMIF_REG_CICBSA(0, 3),		"CICOCBSA3" पूर्ण,
		अणु S3C_CAMIF_REG_CICRSA(0, 3),		"CICOCRSA3" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(1, 0),		"CIPRYSA0" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(1, 1),		"CIPRYSA1" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(1, 2),		"CIPRYSA2" पूर्ण,
		अणु S3C_CAMIF_REG_CIYSA(1, 3),		"CIPRYSA3" पूर्ण,
		अणु S3C_CAMIF_REG_CITRGFMT(0, 0),		"CICOTRGFMT" पूर्ण,
		अणु S3C_CAMIF_REG_CITRGFMT(1, 0),		"CIPRTRGFMT" पूर्ण,
		अणु S3C_CAMIF_REG_CICTRL(0, 0),		"CICOCTRL" पूर्ण,
		अणु S3C_CAMIF_REG_CICTRL(1, 0),		"CIPRCTRL" पूर्ण,
		अणु S3C_CAMIF_REG_CISCPREDST(0, 0),	"CICOSCPREDST" पूर्ण,
		अणु S3C_CAMIF_REG_CISCPREDST(1, 0),	"CIPRSCPREDST" पूर्ण,
		अणु S3C_CAMIF_REG_CISCPRERATIO(0, 0),	"CICOSCPRERATIO" पूर्ण,
		अणु S3C_CAMIF_REG_CISCPRERATIO(1, 0),	"CIPRSCPRERATIO" पूर्ण,
		अणु S3C_CAMIF_REG_CISCCTRL(0, 0),		"CICOSCCTRL" पूर्ण,
		अणु S3C_CAMIF_REG_CISCCTRL(1, 0),		"CIPRSCCTRL" पूर्ण,
		अणु S3C_CAMIF_REG_CITAREA(0, 0),		"CICOTAREA" पूर्ण,
		अणु S3C_CAMIF_REG_CITAREA(1, 0),		"CIPRTAREA" पूर्ण,
		अणु S3C_CAMIF_REG_CISTATUS(0, 0),		"CICOSTATUS" पूर्ण,
		अणु S3C_CAMIF_REG_CISTATUS(1, 0),		"CIPRSTATUS" पूर्ण,
		अणु S3C_CAMIF_REG_CIIMGCPT(0),		"CIIMGCPT" पूर्ण,
	पूर्ण;
	u32 i;

	pr_info("--- %s ---\n", label);
	क्रम (i = 0; i < ARRAY_SIZE(रेजिस्टरs); i++) अणु
		u32 cfg = पढ़ोl(camअगर->io_base + रेजिस्टरs[i].offset);
		dev_info(camअगर->dev, "%s:\t0x%08x\n", रेजिस्टरs[i].name, cfg);
	पूर्ण
पूर्ण
