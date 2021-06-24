<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Mickael Reulier <mickael.reulier@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश <video/videomode.h>

#समावेश "ltdc.h"

#घोषणा NB_CRTC 1
#घोषणा CRTC_MASK GENMASK(NB_CRTC - 1, 0)

#घोषणा MAX_IRQ 4

#घोषणा HWVER_10200 0x010200
#घोषणा HWVER_10300 0x010300
#घोषणा HWVER_20101 0x020101

/*
 * The address of some रेजिस्टरs depends on the HW version: such रेजिस्टरs have
 * an extra offset specअगरied with reg_ofs.
 */
#घोषणा REG_OFS_NONE	0
#घोषणा REG_OFS_4	4		/* Insertion of "Layer Conf. 2" reg */
#घोषणा REG_OFS		(ldev->caps.reg_ofs)
#घोषणा LAY_OFS		0x80		/* Register Offset between 2 layers */

/* Global रेजिस्टर offsets */
#घोषणा LTDC_IDR	0x0000		/* IDentअगरication */
#घोषणा LTDC_LCR	0x0004		/* Layer Count */
#घोषणा LTDC_SSCR	0x0008		/* Synchronization Size Configuration */
#घोषणा LTDC_BPCR	0x000C		/* Back Porch Configuration */
#घोषणा LTDC_AWCR	0x0010		/* Active Width Configuration */
#घोषणा LTDC_TWCR	0x0014		/* Total Width Configuration */
#घोषणा LTDC_GCR	0x0018		/* Global Control */
#घोषणा LTDC_GC1R	0x001C		/* Global Configuration 1 */
#घोषणा LTDC_GC2R	0x0020		/* Global Configuration 2 */
#घोषणा LTDC_SRCR	0x0024		/* Shaकरोw Reload Configuration */
#घोषणा LTDC_GACR	0x0028		/* GAmma Correction */
#घोषणा LTDC_BCCR	0x002C		/* Background Color Configuration */
#घोषणा LTDC_IER	0x0034		/* Interrupt Enable */
#घोषणा LTDC_ISR	0x0038		/* Interrupt Status */
#घोषणा LTDC_ICR	0x003C		/* Interrupt Clear */
#घोषणा LTDC_LIPCR	0x0040		/* Line Interrupt Position Conf. */
#घोषणा LTDC_CPSR	0x0044		/* Current Position Status */
#घोषणा LTDC_CDSR	0x0048		/* Current Display Status */

/* Layer रेजिस्टर offsets */
#घोषणा LTDC_L1LC1R	(0x80)		/* L1 Layer Configuration 1 */
#घोषणा LTDC_L1LC2R	(0x84)		/* L1 Layer Configuration 2 */
#घोषणा LTDC_L1CR	(0x84 + REG_OFS)/* L1 Control */
#घोषणा LTDC_L1WHPCR	(0x88 + REG_OFS)/* L1 Winकरोw Hor Position Config */
#घोषणा LTDC_L1WVPCR	(0x8C + REG_OFS)/* L1 Winकरोw Vert Position Config */
#घोषणा LTDC_L1CKCR	(0x90 + REG_OFS)/* L1 Color Keying Configuration */
#घोषणा LTDC_L1PFCR	(0x94 + REG_OFS)/* L1 Pixel Format Configuration */
#घोषणा LTDC_L1CACR	(0x98 + REG_OFS)/* L1 Constant Alpha Config */
#घोषणा LTDC_L1DCCR	(0x9C + REG_OFS)/* L1 Default Color Configuration */
#घोषणा LTDC_L1BFCR	(0xA0 + REG_OFS)/* L1 Blend Factors Configuration */
#घोषणा LTDC_L1FBBCR	(0xA4 + REG_OFS)/* L1 FrameBuffer Bus Control */
#घोषणा LTDC_L1AFBCR	(0xA8 + REG_OFS)/* L1 AuxFB Control */
#घोषणा LTDC_L1CFBAR	(0xAC + REG_OFS)/* L1 Color FrameBuffer Address */
#घोषणा LTDC_L1CFBLR	(0xB0 + REG_OFS)/* L1 Color FrameBuffer Length */
#घोषणा LTDC_L1CFBLNR	(0xB4 + REG_OFS)/* L1 Color FrameBuffer Line Nb */
#घोषणा LTDC_L1AFBAR	(0xB8 + REG_OFS)/* L1 AuxFB Address */
#घोषणा LTDC_L1AFBLR	(0xBC + REG_OFS)/* L1 AuxFB Length */
#घोषणा LTDC_L1AFBLNR	(0xC0 + REG_OFS)/* L1 AuxFB Line Number */
#घोषणा LTDC_L1CLUTWR	(0xC4 + REG_OFS)/* L1 CLUT Write */
#घोषणा LTDC_L1YS1R	(0xE0 + REG_OFS)/* L1 YCbCr Scale 1 */
#घोषणा LTDC_L1YS2R	(0xE4 + REG_OFS)/* L1 YCbCr Scale 2 */

/* Bit definitions */
#घोषणा SSCR_VSH	GENMASK(10, 0)	/* Vertical Synchronization Height */
#घोषणा SSCR_HSW	GENMASK(27, 16)	/* Horizontal Synchronization Width */

#घोषणा BPCR_AVBP	GENMASK(10, 0)	/* Accumulated Vertical Back Porch */
#घोषणा BPCR_AHBP	GENMASK(27, 16)	/* Accumulated Horizontal Back Porch */

#घोषणा AWCR_AAH	GENMASK(10, 0)	/* Accumulated Active Height */
#घोषणा AWCR_AAW	GENMASK(27, 16)	/* Accumulated Active Width */

#घोषणा TWCR_TOTALH	GENMASK(10, 0)	/* TOTAL Height */
#घोषणा TWCR_TOTALW	GENMASK(27, 16)	/* TOTAL Width */

#घोषणा GCR_LTDCEN	BIT(0)		/* LTDC ENable */
#घोषणा GCR_DEN		BIT(16)		/* Dither ENable */
#घोषणा GCR_PCPOL	BIT(28)		/* Pixel Clock POLarity-Inverted */
#घोषणा GCR_DEPOL	BIT(29)		/* Data Enable POLarity-High */
#घोषणा GCR_VSPOL	BIT(30)		/* Vertical Synchro POLarity-High */
#घोषणा GCR_HSPOL	BIT(31)		/* Horizontal Synchro POLarity-High */

#घोषणा GC1R_WBCH	GENMASK(3, 0)	/* Width of Blue CHannel output */
#घोषणा GC1R_WGCH	GENMASK(7, 4)	/* Width of Green Channel output */
#घोषणा GC1R_WRCH	GENMASK(11, 8)	/* Width of Red Channel output */
#घोषणा GC1R_PBEN	BIT(12)		/* Precise Blending ENable */
#घोषणा GC1R_DT		GENMASK(15, 14)	/* Dithering Technique */
#घोषणा GC1R_GCT	GENMASK(19, 17)	/* Gamma Correction Technique */
#घोषणा GC1R_SHREN	BIT(21)		/* SHaकरोw Registers ENabled */
#घोषणा GC1R_BCP	BIT(22)		/* Background Colour Programmable */
#घोषणा GC1R_BBEN	BIT(23)		/* Background Blending ENabled */
#घोषणा GC1R_LNIP	BIT(24)		/* Line Number IRQ Position */
#घोषणा GC1R_TP		BIT(25)		/* Timing Programmable */
#घोषणा GC1R_IPP	BIT(26)		/* IRQ Polarity Programmable */
#घोषणा GC1R_SPP	BIT(27)		/* Sync Polarity Programmable */
#घोषणा GC1R_DWP	BIT(28)		/* Dither Width Programmable */
#घोषणा GC1R_STREN	BIT(29)		/* STatus Registers ENabled */
#घोषणा GC1R_BMEN	BIT(31)		/* Blind Mode ENabled */

#घोषणा GC2R_EDCA	BIT(0)		/* External Display Control Ability  */
#घोषणा GC2R_STSAEN	BIT(1)		/* Slave Timing Sync Ability ENabled */
#घोषणा GC2R_DVAEN	BIT(2)		/* Dual-View Ability ENabled */
#घोषणा GC2R_DPAEN	BIT(3)		/* Dual-Port Ability ENabled */
#घोषणा GC2R_BW		GENMASK(6, 4)	/* Bus Width (log2 of nb of bytes) */
#घोषणा GC2R_EDCEN	BIT(7)		/* External Display Control ENabled */

#घोषणा SRCR_IMR	BIT(0)		/* IMmediate Reload */
#घोषणा SRCR_VBR	BIT(1)		/* Vertical Blanking Reload */

#घोषणा BCCR_BCBLACK	0x00		/* Background Color BLACK */
#घोषणा BCCR_BCBLUE	GENMASK(7, 0)	/* Background Color BLUE */
#घोषणा BCCR_BCGREEN	GENMASK(15, 8)	/* Background Color GREEN */
#घोषणा BCCR_BCRED	GENMASK(23, 16)	/* Background Color RED */
#घोषणा BCCR_BCWHITE	GENMASK(23, 0)	/* Background Color WHITE */

#घोषणा IER_LIE		BIT(0)		/* Line Interrupt Enable */
#घोषणा IER_FUIE	BIT(1)		/* Fअगरo Underrun Interrupt Enable */
#घोषणा IER_TERRIE	BIT(2)		/* Transfer ERRor Interrupt Enable */
#घोषणा IER_RRIE	BIT(3)		/* Register Reload Interrupt enable */

#घोषणा CPSR_CYPOS	GENMASK(15, 0)	/* Current Y position */

#घोषणा ISR_LIF		BIT(0)		/* Line Interrupt Flag */
#घोषणा ISR_FUIF	BIT(1)		/* Fअगरo Underrun Interrupt Flag */
#घोषणा ISR_TERRIF	BIT(2)		/* Transfer ERRor Interrupt Flag */
#घोषणा ISR_RRIF	BIT(3)		/* Register Reload Interrupt Flag */

#घोषणा LXCR_LEN	BIT(0)		/* Layer ENable */
#घोषणा LXCR_COLKEN	BIT(1)		/* Color Keying Enable */
#घोषणा LXCR_CLUTEN	BIT(4)		/* Color Look-Up Table ENable */

#घोषणा LXWHPCR_WHSTPOS	GENMASK(11, 0)	/* Winकरोw Horizontal StarT POSition */
#घोषणा LXWHPCR_WHSPPOS	GENMASK(27, 16)	/* Winकरोw Horizontal StoP POSition */

#घोषणा LXWVPCR_WVSTPOS	GENMASK(10, 0)	/* Winकरोw Vertical StarT POSition */
#घोषणा LXWVPCR_WVSPPOS	GENMASK(26, 16)	/* Winकरोw Vertical StoP POSition */

#घोषणा LXPFCR_PF	GENMASK(2, 0)	/* Pixel Format */

#घोषणा LXCACR_CONSTA	GENMASK(7, 0)	/* CONSTant Alpha */

#घोषणा LXBFCR_BF2	GENMASK(2, 0)	/* Blending Factor 2 */
#घोषणा LXBFCR_BF1	GENMASK(10, 8)	/* Blending Factor 1 */

#घोषणा LXCFBLR_CFBLL	GENMASK(12, 0)	/* Color Frame Buffer Line Length */
#घोषणा LXCFBLR_CFBP	GENMASK(28, 16)	/* Color Frame Buffer Pitch in bytes */

#घोषणा LXCFBLNR_CFBLN	GENMASK(10, 0)	/* Color Frame Buffer Line Number */

#घोषणा CLUT_SIZE	256

#घोषणा CONSTA_MAX	0xFF		/* CONSTant Alpha MAX= 1.0 */
#घोषणा BF1_PAXCA	0x600		/* Pixel Alpha x Constant Alpha */
#घोषणा BF1_CA		0x400		/* Constant Alpha */
#घोषणा BF2_1PAXCA	0x007		/* 1 - (Pixel Alpha x Constant Alpha) */
#घोषणा BF2_1CA		0x005		/* 1 - Constant Alpha */

#घोषणा NB_PF		8		/* Max nb of HW pixel क्रमmat */

क्रमागत ltdc_pix_fmt अणु
	PF_NONE,
	/* RGB क्रमmats */
	PF_ARGB8888,		/* ARGB [32 bits] */
	PF_RGBA8888,		/* RGBA [32 bits] */
	PF_RGB888,		/* RGB [24 bits] */
	PF_RGB565,		/* RGB [16 bits] */
	PF_ARGB1555,		/* ARGB A:1 bit RGB:15 bits [16 bits] */
	PF_ARGB4444,		/* ARGB A:4 bits R/G/B: 4 bits each [16 bits] */
	/* Indexed क्रमmats */
	PF_L8,			/* Indexed 8 bits [8 bits] */
	PF_AL44,		/* Alpha:4 bits + indexed 4 bits [8 bits] */
	PF_AL88			/* Alpha:8 bits + indexed 8 bits [16 bits] */
पूर्ण;

/* The index gives the encoding of the pixel क्रमmat क्रम an HW version */
अटल स्थिर क्रमागत ltdc_pix_fmt ltdc_pix_fmt_a0[NB_PF] = अणु
	PF_ARGB8888,		/* 0x00 */
	PF_RGB888,		/* 0x01 */
	PF_RGB565,		/* 0x02 */
	PF_ARGB1555,		/* 0x03 */
	PF_ARGB4444,		/* 0x04 */
	PF_L8,			/* 0x05 */
	PF_AL44,		/* 0x06 */
	PF_AL88			/* 0x07 */
पूर्ण;

अटल स्थिर क्रमागत ltdc_pix_fmt ltdc_pix_fmt_a1[NB_PF] = अणु
	PF_ARGB8888,		/* 0x00 */
	PF_RGB888,		/* 0x01 */
	PF_RGB565,		/* 0x02 */
	PF_RGBA8888,		/* 0x03 */
	PF_AL44,		/* 0x04 */
	PF_L8,			/* 0x05 */
	PF_ARGB1555,		/* 0x06 */
	PF_ARGB4444		/* 0x07 */
पूर्ण;

अटल स्थिर u64 ltdc_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल अंतरभूत u32 reg_पढ़ो(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl_relaxed(base + reg);
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखो(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, base + reg);
पूर्ण

अटल अंतरभूत व्योम reg_set(व्योम __iomem *base, u32 reg, u32 mask)
अणु
	reg_ग_लिखो(base, reg, reg_पढ़ो(base, reg) | mask);
पूर्ण

अटल अंतरभूत व्योम reg_clear(व्योम __iomem *base, u32 reg, u32 mask)
अणु
	reg_ग_लिखो(base, reg, reg_पढ़ो(base, reg) & ~mask);
पूर्ण

अटल अंतरभूत व्योम reg_update_bits(व्योम __iomem *base, u32 reg, u32 mask,
				   u32 val)
अणु
	reg_ग_लिखो(base, reg, (reg_पढ़ो(base, reg) & ~mask) | val);
पूर्ण

अटल अंतरभूत काष्ठा ltdc_device *crtc_to_ltdc(काष्ठा drm_crtc *crtc)
अणु
	वापस (काष्ठा ltdc_device *)crtc->dev->dev_निजी;
पूर्ण

अटल अंतरभूत काष्ठा ltdc_device *plane_to_ltdc(काष्ठा drm_plane *plane)
अणु
	वापस (काष्ठा ltdc_device *)plane->dev->dev_निजी;
पूर्ण

अटल अंतरभूत काष्ठा ltdc_device *encoder_to_ltdc(काष्ठा drm_encoder *enc)
अणु
	वापस (काष्ठा ltdc_device *)enc->dev->dev_निजी;
पूर्ण

अटल अंतरभूत क्रमागत ltdc_pix_fmt to_ltdc_pixelक्रमmat(u32 drm_fmt)
अणु
	क्रमागत ltdc_pix_fmt pf;

	चयन (drm_fmt) अणु
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		pf = PF_ARGB8888;
		अवरोध;
	हाल DRM_FORMAT_RGBA8888:
	हाल DRM_FORMAT_RGBX8888:
		pf = PF_RGBA8888;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		pf = PF_RGB888;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		pf = PF_RGB565;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
		pf = PF_ARGB1555;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_XRGB4444:
		pf = PF_ARGB4444;
		अवरोध;
	हाल DRM_FORMAT_C8:
		pf = PF_L8;
		अवरोध;
	शेष:
		pf = PF_NONE;
		अवरोध;
		/* Note: There are no DRM_FORMAT क्रम AL44 and AL88 */
	पूर्ण

	वापस pf;
पूर्ण

अटल अंतरभूत u32 to_drm_pixelक्रमmat(क्रमागत ltdc_pix_fmt pf)
अणु
	चयन (pf) अणु
	हाल PF_ARGB8888:
		वापस DRM_FORMAT_ARGB8888;
	हाल PF_RGBA8888:
		वापस DRM_FORMAT_RGBA8888;
	हाल PF_RGB888:
		वापस DRM_FORMAT_RGB888;
	हाल PF_RGB565:
		वापस DRM_FORMAT_RGB565;
	हाल PF_ARGB1555:
		वापस DRM_FORMAT_ARGB1555;
	हाल PF_ARGB4444:
		वापस DRM_FORMAT_ARGB4444;
	हाल PF_L8:
		वापस DRM_FORMAT_C8;
	हाल PF_AL44:		/* No DRM support */
	हाल PF_AL88:		/* No DRM support */
	हाल PF_NONE:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 get_pixelक्रमmat_without_alpha(u32 drm)
अणु
	चयन (drm) अणु
	हाल DRM_FORMAT_ARGB4444:
		वापस DRM_FORMAT_XRGB4444;
	हाल DRM_FORMAT_RGBA4444:
		वापस DRM_FORMAT_RGBX4444;
	हाल DRM_FORMAT_ARGB1555:
		वापस DRM_FORMAT_XRGB1555;
	हाल DRM_FORMAT_RGBA5551:
		वापस DRM_FORMAT_RGBX5551;
	हाल DRM_FORMAT_ARGB8888:
		वापस DRM_FORMAT_XRGB8888;
	हाल DRM_FORMAT_RGBA8888:
		वापस DRM_FORMAT_RGBX8888;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल irqवापस_t ltdc_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *ddev = arg;
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	काष्ठा drm_crtc *crtc = drm_crtc_from_index(ddev, 0);

	/* Line IRQ : trigger the vblank event */
	अगर (ldev->irq_status & ISR_LIF)
		drm_crtc_handle_vblank(crtc);

	/* Save FIFO Underrun & Transfer Error status */
	mutex_lock(&ldev->err_lock);
	अगर (ldev->irq_status & ISR_FUIF)
		ldev->error_status |= ISR_FUIF;
	अगर (ldev->irq_status & ISR_TERRIF)
		ldev->error_status |= ISR_TERRIF;
	mutex_unlock(&ldev->err_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ltdc_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *ddev = arg;
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;

	/* Read & Clear the पूर्णांकerrupt status */
	ldev->irq_status = reg_पढ़ो(ldev->regs, LTDC_ISR);
	reg_ग_लिखो(ldev->regs, LTDC_ICR, ldev->irq_status);

	वापस IRQ_WAKE_THREAD;
पूर्ण

/*
 * DRM_CRTC
 */

अटल व्योम ltdc_crtc_update_clut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	काष्ठा drm_color_lut *lut;
	u32 val;
	पूर्णांक i;

	अगर (!crtc->state->color_mgmt_changed || !crtc->state->gamma_lut)
		वापस;

	lut = (काष्ठा drm_color_lut *)crtc->state->gamma_lut->data;

	क्रम (i = 0; i < CLUT_SIZE; i++, lut++) अणु
		val = ((lut->red << 8) & 0xff0000) | (lut->green & 0xff00) |
			(lut->blue >> 8) | (i << 24);
		reg_ग_लिखो(ldev->regs, LTDC_L1CLUTWR, val);
	पूर्ण
पूर्ण

अटल व्योम ltdc_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;

	DRM_DEBUG_DRIVER("\n");

	pm_runसमय_get_sync(ddev->dev);

	/* Sets the background color value */
	reg_ग_लिखो(ldev->regs, LTDC_BCCR, BCCR_BCBLACK);

	/* Enable IRQ */
	reg_set(ldev->regs, LTDC_IER, IER_RRIE | IER_FUIE | IER_TERRIE);

	/* Commit shaकरोw रेजिस्टरs = update planes at next vblank */
	reg_set(ldev->regs, LTDC_SRCR, SRCR_VBR);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम ltdc_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;

	DRM_DEBUG_DRIVER("\n");

	drm_crtc_vblank_off(crtc);

	/* disable IRQ */
	reg_clear(ldev->regs, LTDC_IER, IER_RRIE | IER_FUIE | IER_TERRIE);

	/* immediately commit disable of layers beक्रमe चयनing off LTDC */
	reg_set(ldev->regs, LTDC_SRCR, SRCR_IMR);

	pm_runसमय_put_sync(ddev->dev);
पूर्ण

#घोषणा CLK_TOLERANCE_HZ 50

अटल क्रमागत drm_mode_status
ltdc_crtc_mode_valid(काष्ठा drm_crtc *crtc,
		     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	पूर्णांक target = mode->घड़ी * 1000;
	पूर्णांक target_min = target - CLK_TOLERANCE_HZ;
	पूर्णांक target_max = target + CLK_TOLERANCE_HZ;
	पूर्णांक result;

	result = clk_round_rate(ldev->pixel_clk, target);

	DRM_DEBUG_DRIVER("clk rate target %d, available %d\n", target, result);

	/* Filter modes according to the max frequency supported by the pads */
	अगर (result > ldev->caps.pad_max_freq_hz)
		वापस MODE_CLOCK_HIGH;

	/*
	 * Accept all "preferred" modes:
	 * - this is important क्रम panels because panel घड़ी tolerances are
	 *   bigger than hdmi ones and there is no reason to not accept them
	 *   (the fps may vary a little but it is not a problem).
	 * - the hdmi preferred mode will be accepted too, but userland will
	 *   be able to use others hdmi "valid" modes अगर necessary.
	 */
	अगर (mode->type & DRM_MODE_TYPE_PREFERRED)
		वापस MODE_OK;

	/*
	 * Filter modes according to the घड़ी value, particularly useful क्रम
	 * hdmi modes that require precise pixel घड़ीs.
	 */
	अगर (result < target_min || result > target_max)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल bool ltdc_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	पूर्णांक rate = mode->घड़ी * 1000;

	अगर (clk_set_rate(ldev->pixel_clk, rate) < 0) अणु
		DRM_ERROR("Cannot set rate (%dHz) for pixel clk\n", rate);
		वापस false;
	पूर्ण

	adjusted_mode->घड़ी = clk_get_rate(ldev->pixel_clk) / 1000;

	DRM_DEBUG_DRIVER("requested clock %dkHz, adjusted clock %dkHz\n",
			 mode->घड़ी, adjusted_mode->घड़ी);

	वापस true;
पूर्ण

अटल व्योम ltdc_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा drm_encoder *encoder = शून्य;
	काष्ठा drm_bridge *bridge = शून्य;
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा videomode vm;
	u32 hsync, vsync, accum_hbp, accum_vbp, accum_act_w, accum_act_h;
	u32 total_width, total_height;
	u32 bus_flags = 0;
	u32 val;
	पूर्णांक ret;

	/* get encoder from crtc */
	drm_क्रम_each_encoder(encoder, ddev)
		अगर (encoder->crtc == crtc)
			अवरोध;

	अगर (encoder) अणु
		/* get bridge from encoder */
		list_क्रम_each_entry(bridge, &encoder->bridge_chain, chain_node)
			अगर (bridge->encoder == encoder)
				अवरोध;

		/* Get the connector from encoder */
		drm_connector_list_iter_begin(ddev, &iter);
		drm_क्रम_each_connector_iter(connector, &iter)
			अगर (connector->encoder == encoder)
				अवरोध;
		drm_connector_list_iter_end(&iter);
	पूर्ण

	अगर (bridge && bridge->timings)
		bus_flags = bridge->timings->input_bus_flags;
	अन्यथा अगर (connector)
		bus_flags = connector->display_info.bus_flags;

	अगर (!pm_runसमय_active(ddev->dev)) अणु
		ret = pm_runसमय_get_sync(ddev->dev);
		अगर (ret) अणु
			DRM_ERROR("Failed to set mode, cannot get sync\n");
			वापस;
		पूर्ण
	पूर्ण

	drm_display_mode_to_videomode(mode, &vm);

	DRM_DEBUG_DRIVER("CRTC:%d mode:%s\n", crtc->base.id, mode->name);
	DRM_DEBUG_DRIVER("Video mode: %dx%d", vm.hactive, vm.vactive);
	DRM_DEBUG_DRIVER(" hfp %d hbp %d hsl %d vfp %d vbp %d vsl %d\n",
			 vm.hfront_porch, vm.hback_porch, vm.hsync_len,
			 vm.vfront_porch, vm.vback_porch, vm.vsync_len);

	/* Convert video timings to ltdc timings */
	hsync = vm.hsync_len - 1;
	vsync = vm.vsync_len - 1;
	accum_hbp = hsync + vm.hback_porch;
	accum_vbp = vsync + vm.vback_porch;
	accum_act_w = accum_hbp + vm.hactive;
	accum_act_h = accum_vbp + vm.vactive;
	total_width = accum_act_w + vm.hfront_porch;
	total_height = accum_act_h + vm.vfront_porch;

	/* Configures the HS, VS, DE and PC polarities. Default Active Low */
	val = 0;

	अगर (vm.flags & DISPLAY_FLAGS_HSYNC_HIGH)
		val |= GCR_HSPOL;

	अगर (vm.flags & DISPLAY_FLAGS_VSYNC_HIGH)
		val |= GCR_VSPOL;

	अगर (bus_flags & DRM_BUS_FLAG_DE_LOW)
		val |= GCR_DEPOL;

	अगर (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
		val |= GCR_PCPOL;

	reg_update_bits(ldev->regs, LTDC_GCR,
			GCR_HSPOL | GCR_VSPOL | GCR_DEPOL | GCR_PCPOL, val);

	/* Set Synchronization size */
	val = (hsync << 16) | vsync;
	reg_update_bits(ldev->regs, LTDC_SSCR, SSCR_VSH | SSCR_HSW, val);

	/* Set Accumulated Back porch */
	val = (accum_hbp << 16) | accum_vbp;
	reg_update_bits(ldev->regs, LTDC_BPCR, BPCR_AVBP | BPCR_AHBP, val);

	/* Set Accumulated Active Width */
	val = (accum_act_w << 16) | accum_act_h;
	reg_update_bits(ldev->regs, LTDC_AWCR, AWCR_AAW | AWCR_AAH, val);

	/* Set total width & height */
	val = (total_width << 16) | total_height;
	reg_update_bits(ldev->regs, LTDC_TWCR, TWCR_TOTALH | TWCR_TOTALW, val);

	reg_ग_लिखो(ldev->regs, LTDC_LIPCR, (accum_act_h + 1));
पूर्ण

अटल व्योम ltdc_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;

	DRM_DEBUG_ATOMIC("\n");

	ltdc_crtc_update_clut(crtc);

	/* Commit shaकरोw रेजिस्टरs = update planes at next vblank */
	reg_set(ldev->regs, LTDC_SRCR, SRCR_VBR);

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&ddev->event_lock);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&ddev->event_lock);
	पूर्ण
पूर्ण

अटल bool ltdc_crtc_get_scanout_position(काष्ठा drm_crtc *crtc,
					   bool in_vblank_irq,
					   पूर्णांक *vpos, पूर्णांक *hpos,
					   kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
					   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	पूर्णांक line, vactive_start, vactive_end, vtotal;

	अगर (sसमय)
		*sसमय = kसमय_get();

	/* The active area starts after vsync + front porch and ends
	 * at vsync + front porc + display size.
	 * The total height also include back porch.
	 * We have 3 possible हालs to handle:
	 * - line < vactive_start: vpos = line - vactive_start and will be
	 * negative
	 * - vactive_start < line < vactive_end: vpos = line - vactive_start
	 * and will be positive
	 * - line > vactive_end: vpos = line - vtotal - vactive_start
	 * and will negative
	 *
	 * Computation क्रम the two first हालs are identical so we can
	 * simplअगरy the code and only test अगर line > vactive_end
	 */
	अगर (pm_runसमय_active(ddev->dev)) अणु
		line = reg_पढ़ो(ldev->regs, LTDC_CPSR) & CPSR_CYPOS;
		vactive_start = reg_पढ़ो(ldev->regs, LTDC_BPCR) & BPCR_AVBP;
		vactive_end = reg_पढ़ो(ldev->regs, LTDC_AWCR) & AWCR_AAH;
		vtotal = reg_पढ़ो(ldev->regs, LTDC_TWCR) & TWCR_TOTALH;

		अगर (line > vactive_end)
			*vpos = line - vtotal - vactive_start;
		अन्यथा
			*vpos = line - vactive_start;
	पूर्ण अन्यथा अणु
		*vpos = 0;
	पूर्ण

	*hpos = 0;

	अगर (eसमय)
		*eसमय = kसमय_get();

	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs ltdc_crtc_helper_funcs = अणु
	.mode_valid = ltdc_crtc_mode_valid,
	.mode_fixup = ltdc_crtc_mode_fixup,
	.mode_set_nofb = ltdc_crtc_mode_set_nofb,
	.atomic_flush = ltdc_crtc_atomic_flush,
	.atomic_enable = ltdc_crtc_atomic_enable,
	.atomic_disable = ltdc_crtc_atomic_disable,
	.get_scanout_position = ltdc_crtc_get_scanout_position,
पूर्ण;

अटल पूर्णांक ltdc_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);
	काष्ठा drm_crtc_state *state = crtc->state;

	DRM_DEBUG_DRIVER("\n");

	अगर (state->enable)
		reg_set(ldev->regs, LTDC_IER, IER_LIE);
	अन्यथा
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल व्योम ltdc_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ltdc_device *ldev = crtc_to_ltdc(crtc);

	DRM_DEBUG_DRIVER("\n");
	reg_clear(ldev->regs, LTDC_IER, IER_LIE);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs ltdc_crtc_funcs = अणु
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = ltdc_crtc_enable_vblank,
	.disable_vblank = ltdc_crtc_disable_vblank,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

/*
 * DRM_PLANE
 */

अटल पूर्णांक ltdc_plane_atomic_check(काष्ठा drm_plane *plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	u32 src_w, src_h;

	DRM_DEBUG_DRIVER("\n");

	अगर (!fb)
		वापस 0;

	/* convert src_ from 16:16 क्रमmat */
	src_w = new_plane_state->src_w >> 16;
	src_h = new_plane_state->src_h >> 16;

	/* Reject scaling */
	अगर (src_w != new_plane_state->crtc_w || src_h != new_plane_state->crtc_h) अणु
		DRM_ERROR("Scaling is not supported");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ltdc_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ltdc_device *ldev = plane_to_ltdc(plane);
	काष्ठा drm_plane_state *newstate = drm_atomic_get_new_plane_state(state,
									  plane);
	काष्ठा drm_framebuffer *fb = newstate->fb;
	u32 lofs = plane->index * LAY_OFS;
	u32 x0 = newstate->crtc_x;
	u32 x1 = newstate->crtc_x + newstate->crtc_w - 1;
	u32 y0 = newstate->crtc_y;
	u32 y1 = newstate->crtc_y + newstate->crtc_h - 1;
	u32 src_x, src_y, src_w, src_h;
	u32 val, pitch_in_bytes, line_length, paddr, ahbp, avbp, bpcr;
	क्रमागत ltdc_pix_fmt pf;

	अगर (!newstate->crtc || !fb) अणु
		DRM_DEBUG_DRIVER("fb or crtc NULL");
		वापस;
	पूर्ण

	/* convert src_ from 16:16 क्रमmat */
	src_x = newstate->src_x >> 16;
	src_y = newstate->src_y >> 16;
	src_w = newstate->src_w >> 16;
	src_h = newstate->src_h >> 16;

	DRM_DEBUG_DRIVER("plane:%d fb:%d (%dx%d)@(%d,%d) -> (%dx%d)@(%d,%d)\n",
			 plane->base.id, fb->base.id,
			 src_w, src_h, src_x, src_y,
			 newstate->crtc_w, newstate->crtc_h,
			 newstate->crtc_x, newstate->crtc_y);

	bpcr = reg_पढ़ो(ldev->regs, LTDC_BPCR);
	ahbp = (bpcr & BPCR_AHBP) >> 16;
	avbp = bpcr & BPCR_AVBP;

	/* Configures the horizontal start and stop position */
	val = ((x1 + 1 + ahbp) << 16) + (x0 + 1 + ahbp);
	reg_update_bits(ldev->regs, LTDC_L1WHPCR + lofs,
			LXWHPCR_WHSTPOS | LXWHPCR_WHSPPOS, val);

	/* Configures the vertical start and stop position */
	val = ((y1 + 1 + avbp) << 16) + (y0 + 1 + avbp);
	reg_update_bits(ldev->regs, LTDC_L1WVPCR + lofs,
			LXWVPCR_WVSTPOS | LXWVPCR_WVSPPOS, val);

	/* Specअगरies the pixel क्रमmat */
	pf = to_ltdc_pixelक्रमmat(fb->क्रमmat->क्रमmat);
	क्रम (val = 0; val < NB_PF; val++)
		अगर (ldev->caps.pix_fmt_hw[val] == pf)
			अवरोध;

	अगर (val == NB_PF) अणु
		DRM_ERROR("Pixel format %.4s not supported\n",
			  (अक्षर *)&fb->क्रमmat->क्रमmat);
		val = 0;	/* set by शेष ARGB 32 bits */
	पूर्ण
	reg_update_bits(ldev->regs, LTDC_L1PFCR + lofs, LXPFCR_PF, val);

	/* Configures the color frame buffer pitch in bytes & line length */
	pitch_in_bytes = fb->pitches[0];
	line_length = fb->क्रमmat->cpp[0] *
		      (x1 - x0 + 1) + (ldev->caps.bus_width >> 3) - 1;
	val = ((pitch_in_bytes << 16) | line_length);
	reg_update_bits(ldev->regs, LTDC_L1CFBLR + lofs,
			LXCFBLR_CFBLL | LXCFBLR_CFBP, val);

	/* Specअगरies the स्थिरant alpha value */
	val = CONSTA_MAX;
	reg_update_bits(ldev->regs, LTDC_L1CACR + lofs, LXCACR_CONSTA, val);

	/* Specअगरies the blending factors */
	val = BF1_PAXCA | BF2_1PAXCA;
	अगर (!fb->क्रमmat->has_alpha)
		val = BF1_CA | BF2_1CA;

	/* Manage hw-specअगरic capabilities */
	अगर (ldev->caps.non_alpha_only_l1 &&
	    plane->type != DRM_PLANE_TYPE_PRIMARY)
		val = BF1_PAXCA | BF2_1PAXCA;

	reg_update_bits(ldev->regs, LTDC_L1BFCR + lofs,
			LXBFCR_BF2 | LXBFCR_BF1, val);

	/* Configures the frame buffer line number */
	val = y1 - y0 + 1;
	reg_update_bits(ldev->regs, LTDC_L1CFBLNR + lofs, LXCFBLNR_CFBLN, val);

	/* Sets the FB address */
	paddr = (u32)drm_fb_cma_get_gem_addr(fb, newstate, 0);

	DRM_DEBUG_DRIVER("fb: phys 0x%08x", paddr);
	reg_ग_लिखो(ldev->regs, LTDC_L1CFBAR + lofs, paddr);

	/* Enable layer and CLUT अगर needed */
	val = fb->क्रमmat->क्रमmat == DRM_FORMAT_C8 ? LXCR_CLUTEN : 0;
	val |= LXCR_LEN;
	reg_update_bits(ldev->regs, LTDC_L1CR + lofs,
			LXCR_LEN | LXCR_CLUTEN, val);

	ldev->plane_fpsi[plane->index].counter++;

	mutex_lock(&ldev->err_lock);
	अगर (ldev->error_status & ISR_FUIF) अणु
		DRM_WARN("ltdc fifo underrun: please verify display mode\n");
		ldev->error_status &= ~ISR_FUIF;
	पूर्ण
	अगर (ldev->error_status & ISR_TERRIF) अणु
		DRM_WARN("ltdc transfer error\n");
		ldev->error_status &= ~ISR_TERRIF;
	पूर्ण
	mutex_unlock(&ldev->err_lock);
पूर्ण

अटल व्योम ltdc_plane_atomic_disable(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *oldstate = drm_atomic_get_old_plane_state(state,
									  plane);
	काष्ठा ltdc_device *ldev = plane_to_ltdc(plane);
	u32 lofs = plane->index * LAY_OFS;

	/* disable layer */
	reg_clear(ldev->regs, LTDC_L1CR + lofs, LXCR_LEN);

	DRM_DEBUG_DRIVER("CRTC:%d plane:%d\n",
			 oldstate->crtc->base.id, plane->base.id);
पूर्ण

अटल व्योम ltdc_plane_atomic_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
					  स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_plane *plane = state->plane;
	काष्ठा ltdc_device *ldev = plane_to_ltdc(plane);
	काष्ठा fps_info *fpsi = &ldev->plane_fpsi[plane->index];
	पूर्णांक ms_since_last;
	kसमय_प्रकार now;

	now = kसमय_get();
	ms_since_last = kसमय_प्रकारo_ms(kसमय_sub(now, fpsi->last_बारtamp));

	drm_म_लिखो(p, "\tuser_updates=%dfps\n",
		   DIV_ROUND_CLOSEST(fpsi->counter * 1000, ms_since_last));

	fpsi->last_बारtamp = now;
	fpsi->counter = 0;
पूर्ण

अटल bool ltdc_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					    u32 क्रमmat,
					    u64 modअगरier)
अणु
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs ltdc_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.atomic_prपूर्णांक_state = ltdc_plane_atomic_prपूर्णांक_state,
	.क्रमmat_mod_supported = ltdc_plane_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs ltdc_plane_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = ltdc_plane_atomic_check,
	.atomic_update = ltdc_plane_atomic_update,
	.atomic_disable = ltdc_plane_atomic_disable,
पूर्ण;

अटल काष्ठा drm_plane *ltdc_plane_create(काष्ठा drm_device *ddev,
					   क्रमागत drm_plane_type type)
अणु
	अचिन्हित दीर्घ possible_crtcs = CRTC_MASK;
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	काष्ठा device *dev = ddev->dev;
	काष्ठा drm_plane *plane;
	अचिन्हित पूर्णांक i, nb_fmt = 0;
	u32 क्रमmats[NB_PF * 2];
	u32 drm_fmt, drm_fmt_no_alpha;
	स्थिर u64 *modअगरiers = ltdc_क्रमmat_modअगरiers;
	पूर्णांक ret;

	/* Get supported pixel क्रमmats */
	क्रम (i = 0; i < NB_PF; i++) अणु
		drm_fmt = to_drm_pixelक्रमmat(ldev->caps.pix_fmt_hw[i]);
		अगर (!drm_fmt)
			जारी;
		क्रमmats[nb_fmt++] = drm_fmt;

		/* Add the no-alpha related क्रमmat अगर any & supported */
		drm_fmt_no_alpha = get_pixelक्रमmat_without_alpha(drm_fmt);
		अगर (!drm_fmt_no_alpha)
			जारी;

		/* Manage hw-specअगरic capabilities */
		अगर (ldev->caps.non_alpha_only_l1 &&
		    type != DRM_PLANE_TYPE_PRIMARY)
			जारी;

		क्रमmats[nb_fmt++] = drm_fmt_no_alpha;
	पूर्ण

	plane = devm_kzalloc(dev, माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस शून्य;

	ret = drm_universal_plane_init(ddev, plane, possible_crtcs,
				       &ltdc_plane_funcs, क्रमmats, nb_fmt,
				       modअगरiers, type, शून्य);
	अगर (ret < 0)
		वापस शून्य;

	drm_plane_helper_add(plane, &ltdc_plane_helper_funcs);

	DRM_DEBUG_DRIVER("plane:%d created\n", plane->base.id);

	वापस plane;
पूर्ण

अटल व्योम ltdc_plane_destroy_all(काष्ठा drm_device *ddev)
अणु
	काष्ठा drm_plane *plane, *plane_temp;

	list_क्रम_each_entry_safe(plane, plane_temp,
				 &ddev->mode_config.plane_list, head)
		drm_plane_cleanup(plane);
पूर्ण

अटल पूर्णांक ltdc_crtc_init(काष्ठा drm_device *ddev, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	काष्ठा drm_plane *primary, *overlay;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	primary = ltdc_plane_create(ddev, DRM_PLANE_TYPE_PRIMARY);
	अगर (!primary) अणु
		DRM_ERROR("Can not create primary plane\n");
		वापस -EINVAL;
	पूर्ण

	ret = drm_crtc_init_with_planes(ddev, crtc, primary, शून्य,
					&ltdc_crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Can not initialize CRTC\n");
		जाओ cleanup;
	पूर्ण

	drm_crtc_helper_add(crtc, &ltdc_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(crtc, CLUT_SIZE);
	drm_crtc_enable_color_mgmt(crtc, 0, false, CLUT_SIZE);

	DRM_DEBUG_DRIVER("CRTC:%d created\n", crtc->base.id);

	/* Add planes. Note : the first layer is used by primary plane */
	क्रम (i = 1; i < ldev->caps.nb_layers; i++) अणु
		overlay = ltdc_plane_create(ddev, DRM_PLANE_TYPE_OVERLAY);
		अगर (!overlay) अणु
			ret = -ENOMEM;
			DRM_ERROR("Can not create overlay plane %d\n", i);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

cleanup:
	ltdc_plane_destroy_all(ddev);
	वापस ret;
पूर्ण

अटल व्योम ltdc_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *ddev = encoder->dev;
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;

	DRM_DEBUG_DRIVER("\n");

	/* Disable LTDC */
	reg_clear(ldev->regs, LTDC_GCR, GCR_LTDCEN);

	/* Set to sleep state the pinctrl whatever type of encoder */
	pinctrl_pm_select_sleep_state(ddev->dev);
पूर्ण

अटल व्योम ltdc_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *ddev = encoder->dev;
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;

	DRM_DEBUG_DRIVER("\n");

	/* Enable LTDC */
	reg_set(ldev->regs, LTDC_GCR, GCR_LTDCEN);
पूर्ण

अटल व्योम ltdc_encoder_mode_set(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *ddev = encoder->dev;

	DRM_DEBUG_DRIVER("\n");

	/*
	 * Set to शेष state the pinctrl only with DPI type.
	 * Others types like DSI, करोn't need pinctrl due to
	 * पूर्णांकernal bridge (the संकेतs करो not come out of the chipset).
	 */
	अगर (encoder->encoder_type == DRM_MODE_ENCODER_DPI)
		pinctrl_pm_select_शेष_state(ddev->dev);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs ltdc_encoder_helper_funcs = अणु
	.disable = ltdc_encoder_disable,
	.enable = ltdc_encoder_enable,
	.mode_set = ltdc_encoder_mode_set,
पूर्ण;

अटल पूर्णांक ltdc_encoder_init(काष्ठा drm_device *ddev, काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	encoder = devm_kzalloc(ddev->dev, माप(*encoder), GFP_KERNEL);
	अगर (!encoder)
		वापस -ENOMEM;

	encoder->possible_crtcs = CRTC_MASK;
	encoder->possible_clones = 0;	/* No cloning support */

	drm_simple_encoder_init(ddev, encoder, DRM_MODE_ENCODER_DPI);

	drm_encoder_helper_add(encoder, &ltdc_encoder_helper_funcs);

	ret = drm_bridge_attach(encoder, bridge, शून्य, 0);
	अगर (ret) अणु
		drm_encoder_cleanup(encoder);
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG_DRIVER("Bridge encoder:%d created\n", encoder->base.id);

	वापस 0;
पूर्ण

अटल पूर्णांक ltdc_get_caps(काष्ठा drm_device *ddev)
अणु
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	u32 bus_width_log2, lcr, gc2r;

	/*
	 * at least 1 layer must be managed & the number of layers
	 * must not exceed LTDC_MAX_LAYER
	 */
	lcr = reg_पढ़ो(ldev->regs, LTDC_LCR);

	ldev->caps.nb_layers = clamp((पूर्णांक)lcr, 1, LTDC_MAX_LAYER);

	/* set data bus width */
	gc2r = reg_पढ़ो(ldev->regs, LTDC_GC2R);
	bus_width_log2 = (gc2r & GC2R_BW) >> 4;
	ldev->caps.bus_width = 8 << bus_width_log2;
	ldev->caps.hw_version = reg_पढ़ो(ldev->regs, LTDC_IDR);

	चयन (ldev->caps.hw_version) अणु
	हाल HWVER_10200:
	हाल HWVER_10300:
		ldev->caps.reg_ofs = REG_OFS_NONE;
		ldev->caps.pix_fmt_hw = ltdc_pix_fmt_a0;
		/*
		 * Hw older versions support non-alpha color क्रमmats derived
		 * from native alpha color क्रमmats only on the primary layer.
		 * For instance, RG16 native क्रमmat without alpha works fine
		 * on 2nd layer but XR24 (derived color क्रमmat from AR24)
		 * करोes not work on 2nd layer.
		 */
		ldev->caps.non_alpha_only_l1 = true;
		ldev->caps.pad_max_freq_hz = 90000000;
		अगर (ldev->caps.hw_version == HWVER_10200)
			ldev->caps.pad_max_freq_hz = 65000000;
		ldev->caps.nb_irq = 2;
		अवरोध;
	हाल HWVER_20101:
		ldev->caps.reg_ofs = REG_OFS_4;
		ldev->caps.pix_fmt_hw = ltdc_pix_fmt_a1;
		ldev->caps.non_alpha_only_l1 = false;
		ldev->caps.pad_max_freq_hz = 150000000;
		ldev->caps.nb_irq = 4;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ltdc_suspend(काष्ठा drm_device *ddev)
अणु
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;

	DRM_DEBUG_DRIVER("\n");
	clk_disable_unprepare(ldev->pixel_clk);
पूर्ण

पूर्णांक ltdc_resume(काष्ठा drm_device *ddev)
अणु
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	ret = clk_prepare_enable(ldev->pixel_clk);
	अगर (ret) अणु
		DRM_ERROR("failed to enable pixel clock (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ltdc_load(काष्ठा drm_device *ddev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ddev->dev);
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	काष्ठा device *dev = ddev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	काष्ठा drm_crtc *crtc;
	काष्ठा reset_control *rstc;
	काष्ठा resource *res;
	पूर्णांक irq, i, nb_endpoपूर्णांकs;
	पूर्णांक ret = -ENODEV;

	DRM_DEBUG_DRIVER("\n");

	/* Get number of endpoपूर्णांकs */
	nb_endpoपूर्णांकs = of_graph_get_endpoपूर्णांक_count(np);
	अगर (!nb_endpoपूर्णांकs)
		वापस -ENODEV;

	ldev->pixel_clk = devm_clk_get(dev, "lcd");
	अगर (IS_ERR(ldev->pixel_clk)) अणु
		अगर (PTR_ERR(ldev->pixel_clk) != -EPROBE_DEFER)
			DRM_ERROR("Unable to get lcd clock\n");
		वापस PTR_ERR(ldev->pixel_clk);
	पूर्ण

	अगर (clk_prepare_enable(ldev->pixel_clk)) अणु
		DRM_ERROR("Unable to prepare pixel clock\n");
		वापस -ENODEV;
	पूर्ण

	/* Get endpoपूर्णांकs अगर any */
	क्रम (i = 0; i < nb_endpoपूर्णांकs; i++) अणु
		ret = drm_of_find_panel_or_bridge(np, 0, i, &panel, &bridge);

		/*
		 * If at least one endpoपूर्णांक is -ENODEV, जारी probing,
		 * अन्यथा अगर at least one endpoपूर्णांक वापसed an error
		 * (ie -EPROBE_DEFER) then stop probing.
		 */
		अगर (ret == -ENODEV)
			जारी;
		अन्यथा अगर (ret)
			जाओ err;

		अगर (panel) अणु
			bridge = drm_panel_bridge_add_typed(panel,
							    DRM_MODE_CONNECTOR_DPI);
			अगर (IS_ERR(bridge)) अणु
				DRM_ERROR("panel-bridge endpoint %d\n", i);
				ret = PTR_ERR(bridge);
				जाओ err;
			पूर्ण
		पूर्ण

		अगर (bridge) अणु
			ret = ltdc_encoder_init(ddev, bridge);
			अगर (ret) अणु
				DRM_ERROR("init encoder endpoint %d\n", i);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	rstc = devm_reset_control_get_exclusive(dev, शून्य);

	mutex_init(&ldev->err_lock);

	अगर (!IS_ERR(rstc)) अणु
		reset_control_निश्चित(rstc);
		usleep_range(10, 20);
		reset_control_deनिश्चित(rstc);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ldev->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ldev->regs)) अणु
		DRM_ERROR("Unable to get ltdc registers\n");
		ret = PTR_ERR(ldev->regs);
		जाओ err;
	पूर्ण

	/* Disable पूर्णांकerrupts */
	reg_clear(ldev->regs, LTDC_IER,
		  IER_LIE | IER_RRIE | IER_FUIE | IER_TERRIE);

	ret = ltdc_get_caps(ddev);
	अगर (ret) अणु
		DRM_ERROR("hardware identifier (0x%08x) not supported!\n",
			  ldev->caps.hw_version);
		जाओ err;
	पूर्ण

	DRM_DEBUG_DRIVER("ltdc hw version 0x%08x\n", ldev->caps.hw_version);

	क्रम (i = 0; i < ldev->caps.nb_irq; i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ err;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, irq, ltdc_irq,
						ltdc_irq_thपढ़ो, IRQF_ONESHOT,
						dev_name(dev), ddev);
		अगर (ret) अणु
			DRM_ERROR("Failed to register LTDC interrupt\n");
			जाओ err;
		पूर्ण

	पूर्ण

	crtc = devm_kzalloc(dev, माप(*crtc), GFP_KERNEL);
	अगर (!crtc) अणु
		DRM_ERROR("Failed to allocate crtc\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ddev->mode_config.allow_fb_modअगरiers = true;

	ret = ltdc_crtc_init(ddev, crtc);
	अगर (ret) अणु
		DRM_ERROR("Failed to init crtc\n");
		जाओ err;
	पूर्ण

	ret = drm_vblank_init(ddev, NB_CRTC);
	अगर (ret) अणु
		DRM_ERROR("Failed calling drm_vblank_init()\n");
		जाओ err;
	पूर्ण

	/* Allow usage of vblank without having to call drm_irq_install */
	ddev->irq_enabled = 1;

	clk_disable_unprepare(ldev->pixel_clk);

	pinctrl_pm_select_sleep_state(ddev->dev);

	pm_runसमय_enable(ddev->dev);

	वापस 0;
err:
	क्रम (i = 0; i < nb_endpoपूर्णांकs; i++)
		drm_of_panel_bridge_हटाओ(ddev->dev->of_node, 0, i);

	clk_disable_unprepare(ldev->pixel_clk);

	वापस ret;
पूर्ण

व्योम ltdc_unload(काष्ठा drm_device *ddev)
अणु
	काष्ठा device *dev = ddev->dev;
	पूर्णांक nb_endpoपूर्णांकs, i;

	DRM_DEBUG_DRIVER("\n");

	nb_endpoपूर्णांकs = of_graph_get_endpoपूर्णांक_count(dev->of_node);

	क्रम (i = 0; i < nb_endpoपूर्णांकs; i++)
		drm_of_panel_bridge_हटाओ(ddev->dev->of_node, 0, i);

	pm_runसमय_disable(ddev->dev);
पूर्ण

MODULE_AUTHOR("Philippe Cornu <philippe.cornu@st.com>");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_AUTHOR("Mickael Reulier <mickael.reulier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST DRM LTDC driver");
MODULE_LICENSE("GPL v2");
