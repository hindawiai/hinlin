<शैली गुरु>
/*
 * Copyright तऊ 2010 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Li Peng <peng.li@पूर्णांकel.com>
 */

#समावेश <linux/delay.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

#घोषणा HDMI_READ(reg)		पढ़ोl(hdmi_dev->regs + (reg))
#घोषणा HDMI_WRITE(reg, val)	ग_लिखोl(val, hdmi_dev->regs + (reg))

#घोषणा HDMI_HCR	0x1000
#घोषणा HCR_ENABLE_HDCP		(1 << 5)
#घोषणा HCR_ENABLE_AUDIO	(1 << 2)
#घोषणा HCR_ENABLE_PIXEL	(1 << 1)
#घोषणा HCR_ENABLE_TMDS		(1 << 0)

#घोषणा HDMI_HICR	0x1004
#घोषणा HDMI_HSR	0x1008
#घोषणा HDMI_HISR	0x100C
#घोषणा HDMI_DETECT_HDP		(1 << 0)

#घोषणा HDMI_VIDEO_REG	0x3000
#घोषणा HDMI_UNIT_EN		(1 << 7)
#घोषणा HDMI_MODE_OUTPUT	(1 << 0)
#घोषणा HDMI_HBLANK_A	0x3100

#घोषणा HDMI_AUDIO_CTRL	0x4000
#घोषणा HDMI_ENABLE_AUDIO	(1 << 0)

#घोषणा PCH_HTOTAL_B	0x3100
#घोषणा PCH_HBLANK_B	0x3104
#घोषणा PCH_HSYNC_B	0x3108
#घोषणा PCH_VTOTAL_B	0x310C
#घोषणा PCH_VBLANK_B	0x3110
#घोषणा PCH_VSYNC_B	0x3114
#घोषणा PCH_PIPEBSRC	0x311C

#घोषणा PCH_PIPEB_DSL	0x3800
#घोषणा PCH_PIPEB_SLC	0x3804
#घोषणा PCH_PIPEBCONF	0x3808
#घोषणा PCH_PIPEBSTAT	0x3824

#घोषणा CDVO_DFT	0x5000
#घोषणा CDVO_SLEWRATE	0x5004
#घोषणा CDVO_STRENGTH	0x5008
#घोषणा CDVO_RCOMP	0x500C

#घोषणा DPLL_CTRL       0x6000
#घोषणा DPLL_PDIV_SHIFT		16
#घोषणा DPLL_PDIV_MASK		(0xf << 16)
#घोषणा DPLL_PWRDN		(1 << 4)
#घोषणा DPLL_RESET		(1 << 3)
#घोषणा DPLL_FASTEN		(1 << 2)
#घोषणा DPLL_ENSTAT		(1 << 1)
#घोषणा DPLL_DITHEN		(1 << 0)

#घोषणा DPLL_DIV_CTRL   0x6004
#घोषणा DPLL_CLKF_MASK		0xffffffc0
#घोषणा DPLL_CLKR_MASK		(0x3f)

#घोषणा DPLL_CLK_ENABLE 0x6008
#घोषणा DPLL_EN_DISP		(1 << 31)
#घोषणा DPLL_SEL_HDMI		(1 << 8)
#घोषणा DPLL_EN_HDMI		(1 << 1)
#घोषणा DPLL_EN_VGA		(1 << 0)

#घोषणा DPLL_ADJUST     0x600C
#घोषणा DPLL_STATUS     0x6010
#घोषणा DPLL_UPDATE     0x6014
#घोषणा DPLL_DFT        0x6020

काष्ठा पूर्णांकel_range अणु
	पूर्णांक	min, max;
पूर्ण;

काष्ठा oaktrail_hdmi_limit अणु
	काष्ठा पूर्णांकel_range vco, np, nr, nf;
पूर्ण;

काष्ठा oaktrail_hdmi_घड़ी अणु
	पूर्णांक np;
	पूर्णांक nr;
	पूर्णांक nf;
	पूर्णांक करोt;
पूर्ण;

#घोषणा VCO_MIN		320000
#घोषणा VCO_MAX		1650000
#घोषणा	NP_MIN		1
#घोषणा	NP_MAX		15
#घोषणा	NR_MIN		1
#घोषणा	NR_MAX		64
#घोषणा NF_MIN		2
#घोषणा NF_MAX		4095

अटल स्थिर काष्ठा oaktrail_hdmi_limit oaktrail_hdmi_limit = अणु
	.vco = अणु .min = VCO_MIN,		.max = VCO_MAX पूर्ण,
	.np  = अणु .min = NP_MIN,			.max = NP_MAX  पूर्ण,
	.nr  = अणु .min = NR_MIN,			.max = NR_MAX  पूर्ण,
	.nf  = अणु .min = NF_MIN,			.max = NF_MAX  पूर्ण,
पूर्ण;

अटल व्योम oaktrail_hdmi_audio_enable(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;

	HDMI_WRITE(HDMI_HCR, 0x67);
	HDMI_READ(HDMI_HCR);

	HDMI_WRITE(0x51a8, 0x10);
	HDMI_READ(0x51a8);

	HDMI_WRITE(HDMI_AUDIO_CTRL, 0x1);
	HDMI_READ(HDMI_AUDIO_CTRL);
पूर्ण

अटल व्योम oaktrail_hdmi_audio_disable(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;

	HDMI_WRITE(0x51a8, 0x0);
	HDMI_READ(0x51a8);

	HDMI_WRITE(HDMI_AUDIO_CTRL, 0x0);
	HDMI_READ(HDMI_AUDIO_CTRL);

	HDMI_WRITE(HDMI_HCR, 0x47);
	HDMI_READ(HDMI_HCR);
पूर्ण

अटल अचिन्हित पूर्णांक htotal_calculate(काष्ठा drm_display_mode *mode)
अणु
	u32 new_crtc_htotal;

	/*
	 * 1024 x 768  new_crtc_htotal = 0x1024;
	 * 1280 x 1024 new_crtc_htotal = 0x0c34;
	 */
	new_crtc_htotal = (mode->crtc_htotal - 1) * 200 * 1000 / mode->घड़ी;

	DRM_DEBUG_KMS("new crtc htotal 0x%4x\n", new_crtc_htotal);
	वापस (mode->crtc_hdisplay - 1) | (new_crtc_htotal << 16);
पूर्ण

अटल व्योम oaktrail_hdmi_find_dpll(काष्ठा drm_crtc *crtc, पूर्णांक target,
				पूर्णांक refclk, काष्ठा oaktrail_hdmi_घड़ी *best_घड़ी)
अणु
	पूर्णांक np_min, np_max, nr_min, nr_max;
	पूर्णांक np, nr, nf;

	np_min = DIV_ROUND_UP(oaktrail_hdmi_limit.vco.min, target * 10);
	np_max = oaktrail_hdmi_limit.vco.max / (target * 10);
	अगर (np_min < oaktrail_hdmi_limit.np.min)
		np_min = oaktrail_hdmi_limit.np.min;
	अगर (np_max > oaktrail_hdmi_limit.np.max)
		np_max = oaktrail_hdmi_limit.np.max;

	nr_min = DIV_ROUND_UP((refclk * 1000), (target * 10 * np_max));
	nr_max = DIV_ROUND_UP((refclk * 1000), (target * 10 * np_min));
	अगर (nr_min < oaktrail_hdmi_limit.nr.min)
		nr_min = oaktrail_hdmi_limit.nr.min;
	अगर (nr_max > oaktrail_hdmi_limit.nr.max)
		nr_max = oaktrail_hdmi_limit.nr.max;

	np = DIV_ROUND_UP((refclk * 1000), (target * 10 * nr_max));
	nr = DIV_ROUND_UP((refclk * 1000), (target * 10 * np));
	nf = DIV_ROUND_CLOSEST((target * 10 * np * nr), refclk);
	DRM_DEBUG_KMS("np, nr, nf %d %d %d\n", np, nr, nf);

	/*
	 * 1024 x 768  np = 1; nr = 0x26; nf = 0x0fd8000;
	 * 1280 x 1024 np = 1; nr = 0x17; nf = 0x1034000;
	 */
	best_घड़ी->np = np;
	best_घड़ी->nr = nr - 1;
	best_घड़ी->nf = (nf << 14);
पूर्ण

अटल व्योम scu_busy_loop(व्योम __iomem *scu_base)
अणु
	u32 status = 0;
	u32 loop_count = 0;

	status = पढ़ोl(scu_base + 0x04);
	जबतक (status & 1) अणु
		udelay(1); /* scu processing समय is in few u secods */
		status = पढ़ोl(scu_base + 0x04);
		loop_count++;
		/* अवरोध अगर scu करोesn't reset busy bit after huge retry */
		अगर (loop_count > 1000) अणु
			DRM_DEBUG_KMS("SCU IPC timed out");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	You करोn't want to know, you really really don't want to know....
 *
 *	This is magic. However it's safe magic because of the way the platक्रमm
 *	works and it is necessary magic.
 */
अटल व्योम oaktrail_hdmi_reset(काष्ठा drm_device *dev)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ scu_ipc_mmio = 0xff11c000UL;
	पूर्णांक scu_len = 1024;

	base = ioremap((resource_माप_प्रकार)scu_ipc_mmio, scu_len);
	अगर (base == शून्य) अणु
		DRM_ERROR("failed to map scu mmio\n");
		वापस;
	पूर्ण

	/* scu ipc: निश्चित hdmi controller reset */
	ग_लिखोl(0xff11d118, base + 0x0c);
	ग_लिखोl(0x7fffffdf, base + 0x80);
	ग_लिखोl(0x42005, base + 0x0);
	scu_busy_loop(base);

	/* scu ipc: de-निश्चित hdmi controller reset */
	ग_लिखोl(0xff11d118, base + 0x0c);
	ग_लिखोl(0x7fffffff, base + 0x80);
	ग_लिखोl(0x42005, base + 0x0);
	scu_busy_loop(base);

	iounmap(base);
पूर्ण

पूर्णांक oaktrail_crtc_hdmi_mode_set(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_display_mode *mode,
			    काष्ठा drm_display_mode *adjusted_mode,
			    पूर्णांक x, पूर्णांक y,
			    काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	पूर्णांक pipe = 1;
	पूर्णांक htot_reg = (pipe == 0) ? HTOTAL_A : HTOTAL_B;
	पूर्णांक hblank_reg = (pipe == 0) ? HBLANK_A : HBLANK_B;
	पूर्णांक hsync_reg = (pipe == 0) ? HSYNC_A : HSYNC_B;
	पूर्णांक vtot_reg = (pipe == 0) ? VTOTAL_A : VTOTAL_B;
	पूर्णांक vblank_reg = (pipe == 0) ? VBLANK_A : VBLANK_B;
	पूर्णांक vsync_reg = (pipe == 0) ? VSYNC_A : VSYNC_B;
	पूर्णांक dspsize_reg = (pipe == 0) ? DSPASIZE : DSPBSIZE;
	पूर्णांक dsppos_reg = (pipe == 0) ? DSPAPOS : DSPBPOS;
	पूर्णांक pipesrc_reg = (pipe == 0) ? PIPEASRC : PIPEBSRC;
	पूर्णांक pipeconf_reg = (pipe == 0) ? PIPEACONF : PIPEBCONF;
	पूर्णांक refclk;
	काष्ठा oaktrail_hdmi_घड़ी घड़ी;
	u32 dspcntr, pipeconf, dpll, temp;
	पूर्णांक dspcntr_reg = DSPBCNTR;

	अगर (!gma_घातer_begin(dev, true))
		वापस 0;

	/* Disable the VGA plane that we never use */
	REG_WRITE(VGACNTRL, VGA_DISP_DISABLE);

	/* Disable dpll अगर necessary */
	dpll = REG_READ(DPLL_CTRL);
	अगर ((dpll & DPLL_PWRDN) == 0) अणु
		REG_WRITE(DPLL_CTRL, dpll | (DPLL_PWRDN | DPLL_RESET));
		REG_WRITE(DPLL_DIV_CTRL, 0x00000000);
		REG_WRITE(DPLL_STATUS, 0x1);
	पूर्ण
	udelay(150);

	/* Reset controller */
	oaktrail_hdmi_reset(dev);

	/* program and enable dpll */
	refclk = 25000;
	oaktrail_hdmi_find_dpll(crtc, adjusted_mode->घड़ी, refclk, &घड़ी);

	/* Set the DPLL */
	dpll = REG_READ(DPLL_CTRL);
	dpll &= ~DPLL_PDIV_MASK;
	dpll &= ~(DPLL_PWRDN | DPLL_RESET);
	REG_WRITE(DPLL_CTRL, 0x00000008);
	REG_WRITE(DPLL_DIV_CTRL, ((घड़ी.nf << 6) | घड़ी.nr));
	REG_WRITE(DPLL_ADJUST, ((घड़ी.nf >> 14) - 1));
	REG_WRITE(DPLL_CTRL, (dpll | (घड़ी.np << DPLL_PDIV_SHIFT) | DPLL_ENSTAT | DPLL_DITHEN));
	REG_WRITE(DPLL_UPDATE, 0x80000000);
	REG_WRITE(DPLL_CLK_ENABLE, 0x80050102);
	udelay(150);

	/* configure HDMI */
	HDMI_WRITE(0x1004, 0x1fd);
	HDMI_WRITE(0x2000, 0x1);
	HDMI_WRITE(0x2008, 0x0);
	HDMI_WRITE(0x3130, 0x8);
	HDMI_WRITE(0x101c, 0x1800810);

	temp = htotal_calculate(adjusted_mode);
	REG_WRITE(htot_reg, temp);
	REG_WRITE(hblank_reg, (adjusted_mode->crtc_hblank_start - 1) | ((adjusted_mode->crtc_hblank_end - 1) << 16));
	REG_WRITE(hsync_reg, (adjusted_mode->crtc_hsync_start - 1) | ((adjusted_mode->crtc_hsync_end - 1) << 16));
	REG_WRITE(vtot_reg, (adjusted_mode->crtc_vdisplay - 1) | ((adjusted_mode->crtc_vtotal - 1) << 16));
	REG_WRITE(vblank_reg, (adjusted_mode->crtc_vblank_start - 1) | ((adjusted_mode->crtc_vblank_end - 1) << 16));
	REG_WRITE(vsync_reg, (adjusted_mode->crtc_vsync_start - 1) | ((adjusted_mode->crtc_vsync_end - 1) << 16));
	REG_WRITE(pipesrc_reg, ((mode->crtc_hdisplay - 1) << 16) |  (mode->crtc_vdisplay - 1));

	REG_WRITE(PCH_HTOTAL_B, (adjusted_mode->crtc_hdisplay - 1) | ((adjusted_mode->crtc_htotal - 1) << 16));
	REG_WRITE(PCH_HBLANK_B, (adjusted_mode->crtc_hblank_start - 1) | ((adjusted_mode->crtc_hblank_end - 1) << 16));
	REG_WRITE(PCH_HSYNC_B, (adjusted_mode->crtc_hsync_start - 1) | ((adjusted_mode->crtc_hsync_end - 1) << 16));
	REG_WRITE(PCH_VTOTAL_B, (adjusted_mode->crtc_vdisplay - 1) | ((adjusted_mode->crtc_vtotal - 1) << 16));
	REG_WRITE(PCH_VBLANK_B, (adjusted_mode->crtc_vblank_start - 1) | ((adjusted_mode->crtc_vblank_end - 1) << 16));
	REG_WRITE(PCH_VSYNC_B, (adjusted_mode->crtc_vsync_start - 1) | ((adjusted_mode->crtc_vsync_end - 1) << 16));
	REG_WRITE(PCH_PIPEBSRC, ((mode->crtc_hdisplay - 1) << 16) |  (mode->crtc_vdisplay - 1));

	temp = adjusted_mode->crtc_hblank_end - adjusted_mode->crtc_hblank_start;
	HDMI_WRITE(HDMI_HBLANK_A, ((adjusted_mode->crtc_hdisplay - 1) << 16) |  temp);

	REG_WRITE(dspsize_reg, ((mode->vdisplay - 1) << 16) | (mode->hdisplay - 1));
	REG_WRITE(dsppos_reg, 0);

	/* Flush the plane changes */
	अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;
		crtc_funcs->mode_set_base(crtc, x, y, old_fb);
	पूर्ण

	/* Set up the display plane रेजिस्टर */
	dspcntr = REG_READ(dspcntr_reg);
	dspcntr |= DISPPLANE_GAMMA_ENABLE;
	dspcntr |= DISPPLANE_SEL_PIPE_B;
	dspcntr |= DISPLAY_PLANE_ENABLE;

	/* setup pipeconf */
	pipeconf = REG_READ(pipeconf_reg);
	pipeconf |= PIPEACONF_ENABLE;

	REG_WRITE(pipeconf_reg, pipeconf);
	REG_READ(pipeconf_reg);

	REG_WRITE(PCH_PIPEBCONF, pipeconf);
	REG_READ(PCH_PIPEBCONF);
	gma_रुको_क्रम_vblank(dev);

	REG_WRITE(dspcntr_reg, dspcntr);
	gma_रुको_क्रम_vblank(dev);

	gma_घातer_end(dev);

	वापस 0;
पूर्ण

व्योम oaktrail_crtc_hdmi_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	u32 temp;

	DRM_DEBUG_KMS("%s %d\n", __func__, mode);

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_OFF:
		REG_WRITE(VGACNTRL, 0x80000000);

		/* Disable plane */
		temp = REG_READ(DSPBCNTR);
		अगर ((temp & DISPLAY_PLANE_ENABLE) != 0) अणु
			REG_WRITE(DSPBCNTR, temp & ~DISPLAY_PLANE_ENABLE);
			REG_READ(DSPBCNTR);
			/* Flush the plane changes */
			REG_WRITE(DSPBSURF, REG_READ(DSPBSURF));
			REG_READ(DSPBSURF);
		पूर्ण

		/* Disable pipe B */
		temp = REG_READ(PIPEBCONF);
		अगर ((temp & PIPEACONF_ENABLE) != 0) अणु
			REG_WRITE(PIPEBCONF, temp & ~PIPEACONF_ENABLE);
			REG_READ(PIPEBCONF);
		पूर्ण

		/* Disable LNW Pipes, etc */
		temp = REG_READ(PCH_PIPEBCONF);
		अगर ((temp & PIPEACONF_ENABLE) != 0) अणु
			REG_WRITE(PCH_PIPEBCONF, temp & ~PIPEACONF_ENABLE);
			REG_READ(PCH_PIPEBCONF);
		पूर्ण

		/* रुको क्रम pipe off */
		udelay(150);

		/* Disable dpll */
		temp = REG_READ(DPLL_CTRL);
		अगर ((temp & DPLL_PWRDN) == 0) अणु
			REG_WRITE(DPLL_CTRL, temp | (DPLL_PWRDN | DPLL_RESET));
			REG_WRITE(DPLL_STATUS, 0x1);
		पूर्ण

		/* रुको क्रम dpll off */
		udelay(150);

		अवरोध;
	हाल DRM_MODE_DPMS_ON:
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
		/* Enable dpll */
		temp = REG_READ(DPLL_CTRL);
		अगर ((temp & DPLL_PWRDN) != 0) अणु
			REG_WRITE(DPLL_CTRL, temp & ~(DPLL_PWRDN | DPLL_RESET));
			temp = REG_READ(DPLL_CLK_ENABLE);
			REG_WRITE(DPLL_CLK_ENABLE, temp | DPLL_EN_DISP | DPLL_SEL_HDMI | DPLL_EN_HDMI);
			REG_READ(DPLL_CLK_ENABLE);
		पूर्ण
		/* रुको क्रम dpll warm up */
		udelay(150);

		/* Enable pipe B */
		temp = REG_READ(PIPEBCONF);
		अगर ((temp & PIPEACONF_ENABLE) == 0) अणु
			REG_WRITE(PIPEBCONF, temp | PIPEACONF_ENABLE);
			REG_READ(PIPEBCONF);
		पूर्ण

		/* Enable LNW Pipe B */
		temp = REG_READ(PCH_PIPEBCONF);
		अगर ((temp & PIPEACONF_ENABLE) == 0) अणु
			REG_WRITE(PCH_PIPEBCONF, temp | PIPEACONF_ENABLE);
			REG_READ(PCH_PIPEBCONF);
		पूर्ण

		gma_रुको_क्रम_vblank(dev);

		/* Enable plane */
		temp = REG_READ(DSPBCNTR);
		अगर ((temp & DISPLAY_PLANE_ENABLE) == 0) अणु
			REG_WRITE(DSPBCNTR, temp | DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(DSPBSURF, REG_READ(DSPBSURF));
			REG_READ(DSPBSURF);
		पूर्ण

		gma_crtc_load_lut(crtc);
	पूर्ण

	/* DSPARB */
	REG_WRITE(DSPARB, 0x00003fbf);

	/* FW1 */
	REG_WRITE(0x70034, 0x3f880a0a);

	/* FW2 */
	REG_WRITE(0x70038, 0x0b060808);

	/* FW4 */
	REG_WRITE(0x70050, 0x08030404);

	/* FW5 */
	REG_WRITE(0x70054, 0x04040404);

	/* LNC Chicken Bits - Squawk! */
	REG_WRITE(0x70400, 0x4000);

	वापस;
पूर्ण

अटल व्योम oaktrail_hdmi_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	अटल पूर्णांक dpms_mode = -1;

	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	u32 temp;

	अगर (dpms_mode == mode)
		वापस;

	अगर (mode != DRM_MODE_DPMS_ON)
		temp = 0x0;
	अन्यथा
		temp = 0x99;

	dpms_mode = mode;
	HDMI_WRITE(HDMI_VIDEO_REG, temp);
पूर्ण

अटल क्रमागत drm_mode_status oaktrail_hdmi_mode_valid(काष्ठा drm_connector *connector,
				काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 165000)
		वापस MODE_CLOCK_HIGH;
	अगर (mode->घड़ी < 20000)
		वापस MODE_CLOCK_LOW;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_connector_status
oaktrail_hdmi_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	क्रमागत drm_connector_status status;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	u32 temp;

	temp = HDMI_READ(HDMI_HSR);
	DRM_DEBUG_KMS("HDMI_HSR %x\n", temp);

	अगर ((temp & HDMI_DETECT_HDP) != 0)
		status = connector_status_connected;
	अन्यथा
		status = connector_status_disconnected;

	वापस status;
पूर्ण

अटल स्थिर अचिन्हित अक्षर raw_edid[] = अणु
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x10, 0xac, 0x2f, 0xa0,
	0x53, 0x55, 0x33, 0x30, 0x16, 0x13, 0x01, 0x03, 0x0e, 0x3a, 0x24, 0x78,
	0xea, 0xe9, 0xf5, 0xac, 0x51, 0x30, 0xb4, 0x25, 0x11, 0x50, 0x54, 0xa5,
	0x4b, 0x00, 0x81, 0x80, 0xa9, 0x40, 0x71, 0x4f, 0xb3, 0x00, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x28, 0x3c, 0x80, 0xa0, 0x70, 0xb0,
	0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x46, 0x6c, 0x21, 0x00, 0x00, 0x1a,
	0x00, 0x00, 0x00, 0xff, 0x00, 0x47, 0x4e, 0x37, 0x32, 0x31, 0x39, 0x35,
	0x52, 0x30, 0x33, 0x55, 0x53, 0x0a, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x44,
	0x45, 0x4c, 0x4c, 0x20, 0x32, 0x37, 0x30, 0x39, 0x57, 0x0a, 0x20, 0x20,
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x38, 0x4c, 0x1e, 0x53, 0x11, 0x00, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x8d
पूर्ण;

अटल पूर्णांक oaktrail_hdmi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	/*
	 *	FIXME: We need to figure this lot out. In theory we can
	 *	पढ़ो the EDID somehow but I've yet to find working reference
	 *	code.
	 */
	i2c_adap = i2c_get_adapter(3);
	अगर (i2c_adap == शून्य) अणु
		DRM_ERROR("No ddc adapter available!\n");
		edid = (काष्ठा edid *)raw_edid;
	पूर्ण अन्यथा अणु
		edid = (काष्ठा edid *)raw_edid;
		/* FIXME ? edid = drm_get_edid(connector, i2c_adap); */
	पूर्ण

	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम oaktrail_hdmi_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;

	oaktrail_hdmi_audio_enable(dev);
	वापस;
पूर्ण

अटल व्योम oaktrail_hdmi_destroy(काष्ठा drm_connector *connector)
अणु
	वापस;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs oaktrail_hdmi_helper_funcs = अणु
	.dpms = oaktrail_hdmi_dpms,
	.prepare = gma_encoder_prepare,
	.mode_set = oaktrail_hdmi_mode_set,
	.commit = gma_encoder_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs
					oaktrail_hdmi_connector_helper_funcs = अणु
	.get_modes = oaktrail_hdmi_get_modes,
	.mode_valid = oaktrail_hdmi_mode_valid,
	.best_encoder = gma_best_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs oaktrail_hdmi_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = oaktrail_hdmi_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = oaktrail_hdmi_destroy,
पूर्ण;

व्योम oaktrail_hdmi_init(काष्ठा drm_device *dev,
					काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा gma_connector *gma_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder), GFP_KERNEL);
	अगर (!gma_encoder)
		वापस;

	gma_connector = kzalloc(माप(काष्ठा gma_connector), GFP_KERNEL);
	अगर (!gma_connector)
		जाओ failed_connector;

	connector = &gma_connector->base;
	encoder = &gma_encoder->base;
	drm_connector_init(dev, connector,
			   &oaktrail_hdmi_connector_funcs,
			   DRM_MODE_CONNECTOR_DVID);

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_TMDS);

	gma_connector_attach_encoder(gma_connector, gma_encoder);

	gma_encoder->type = INTEL_OUTPUT_HDMI;
	drm_encoder_helper_add(encoder, &oaktrail_hdmi_helper_funcs);
	drm_connector_helper_add(connector, &oaktrail_hdmi_connector_helper_funcs);

	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;
	drm_connector_रेजिस्टर(connector);
	dev_info(dev->dev, "HDMI initialised.\n");

	वापस;

failed_connector:
	kमुक्त(gma_encoder);
पूर्ण

व्योम oaktrail_hdmi_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev;
	पूर्णांक ret;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x080d, शून्य);
	अगर (!pdev)
		वापस;

	hdmi_dev = kzalloc(माप(काष्ठा oaktrail_hdmi_dev), GFP_KERNEL);
	अगर (!hdmi_dev) अणु
		dev_err(dev->dev, "failed to allocate memory\n");
		जाओ out;
	पूर्ण


	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to enable hdmi controller\n");
		जाओ मुक्त;
	पूर्ण

	hdmi_dev->mmio = pci_resource_start(pdev, 0);
	hdmi_dev->mmio_len = pci_resource_len(pdev, 0);
	hdmi_dev->regs = ioremap(hdmi_dev->mmio, hdmi_dev->mmio_len);
	अगर (!hdmi_dev->regs) अणु
		dev_err(dev->dev, "failed to map hdmi mmio\n");
		जाओ मुक्त;
	पूर्ण

	hdmi_dev->dev = pdev;
	pci_set_drvdata(pdev, hdmi_dev);

	/* Initialize i2c controller */
	ret = oaktrail_hdmi_i2c_init(hdmi_dev->dev);
	अगर (ret)
		dev_err(dev->dev, "HDMI I2C initialization failed\n");

	dev_priv->hdmi_priv = hdmi_dev;
	oaktrail_hdmi_audio_disable(dev);

	dev_info(dev->dev, "HDMI hardware present.\n");

	वापस;

मुक्त:
	kमुक्त(hdmi_dev);
out:
	वापस;
पूर्ण

व्योम oaktrail_hdmi_tearकरोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	काष्ठा pci_dev *pdev;

	अगर (hdmi_dev) अणु
		pdev = hdmi_dev->dev;
		pci_set_drvdata(pdev, शून्य);
		oaktrail_hdmi_i2c_निकास(pdev);
		iounmap(hdmi_dev->regs);
		kमुक्त(hdmi_dev);
		pci_dev_put(pdev);
	पूर्ण
पूर्ण

/* save HDMI रेजिस्टर state */
व्योम oaktrail_hdmi_save(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	काष्ठा psb_state *regs = &dev_priv->regs.psb;
	काष्ठा psb_pipe *pipeb = &dev_priv->regs.pipe[1];
	पूर्णांक i;

	/* dpll */
	hdmi_dev->saveDPLL_CTRL = PSB_RVDC32(DPLL_CTRL);
	hdmi_dev->saveDPLL_DIV_CTRL = PSB_RVDC32(DPLL_DIV_CTRL);
	hdmi_dev->saveDPLL_ADJUST = PSB_RVDC32(DPLL_ADJUST);
	hdmi_dev->saveDPLL_UPDATE = PSB_RVDC32(DPLL_UPDATE);
	hdmi_dev->saveDPLL_CLK_ENABLE = PSB_RVDC32(DPLL_CLK_ENABLE);

	/* pipe B */
	pipeb->conf = PSB_RVDC32(PIPEBCONF);
	pipeb->src = PSB_RVDC32(PIPEBSRC);
	pipeb->htotal = PSB_RVDC32(HTOTAL_B);
	pipeb->hblank = PSB_RVDC32(HBLANK_B);
	pipeb->hsync = PSB_RVDC32(HSYNC_B);
	pipeb->vtotal = PSB_RVDC32(VTOTAL_B);
	pipeb->vblank = PSB_RVDC32(VBLANK_B);
	pipeb->vsync = PSB_RVDC32(VSYNC_B);

	hdmi_dev->savePCH_PIPEBCONF = PSB_RVDC32(PCH_PIPEBCONF);
	hdmi_dev->savePCH_PIPEBSRC = PSB_RVDC32(PCH_PIPEBSRC);
	hdmi_dev->savePCH_HTOTAL_B = PSB_RVDC32(PCH_HTOTAL_B);
	hdmi_dev->savePCH_HBLANK_B = PSB_RVDC32(PCH_HBLANK_B);
	hdmi_dev->savePCH_HSYNC_B  = PSB_RVDC32(PCH_HSYNC_B);
	hdmi_dev->savePCH_VTOTAL_B = PSB_RVDC32(PCH_VTOTAL_B);
	hdmi_dev->savePCH_VBLANK_B = PSB_RVDC32(PCH_VBLANK_B);
	hdmi_dev->savePCH_VSYNC_B  = PSB_RVDC32(PCH_VSYNC_B);

	/* plane */
	pipeb->cntr = PSB_RVDC32(DSPBCNTR);
	pipeb->stride = PSB_RVDC32(DSPBSTRIDE);
	pipeb->addr = PSB_RVDC32(DSPBBASE);
	pipeb->surf = PSB_RVDC32(DSPBSURF);
	pipeb->linoff = PSB_RVDC32(DSPBLINOFF);
	pipeb->tileoff = PSB_RVDC32(DSPBTILखातापूर्णF);

	/* cursor B */
	regs->saveDSPBCURSOR_CTRL = PSB_RVDC32(CURBCNTR);
	regs->saveDSPBCURSOR_BASE = PSB_RVDC32(CURBBASE);
	regs->saveDSPBCURSOR_POS = PSB_RVDC32(CURBPOS);

	/* save palette */
	क्रम (i = 0; i < 256; i++)
		pipeb->palette[i] = PSB_RVDC32(PALETTE_B + (i << 2));
पूर्ण

/* restore HDMI रेजिस्टर state */
व्योम oaktrail_hdmi_restore(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	काष्ठा psb_state *regs = &dev_priv->regs.psb;
	काष्ठा psb_pipe *pipeb = &dev_priv->regs.pipe[1];
	पूर्णांक i;

	/* dpll */
	PSB_WVDC32(hdmi_dev->saveDPLL_CTRL, DPLL_CTRL);
	PSB_WVDC32(hdmi_dev->saveDPLL_DIV_CTRL, DPLL_DIV_CTRL);
	PSB_WVDC32(hdmi_dev->saveDPLL_ADJUST, DPLL_ADJUST);
	PSB_WVDC32(hdmi_dev->saveDPLL_UPDATE, DPLL_UPDATE);
	PSB_WVDC32(hdmi_dev->saveDPLL_CLK_ENABLE, DPLL_CLK_ENABLE);
	udelay(150);

	/* pipe */
	PSB_WVDC32(pipeb->src, PIPEBSRC);
	PSB_WVDC32(pipeb->htotal, HTOTAL_B);
	PSB_WVDC32(pipeb->hblank, HBLANK_B);
	PSB_WVDC32(pipeb->hsync,  HSYNC_B);
	PSB_WVDC32(pipeb->vtotal, VTOTAL_B);
	PSB_WVDC32(pipeb->vblank, VBLANK_B);
	PSB_WVDC32(pipeb->vsync,  VSYNC_B);

	PSB_WVDC32(hdmi_dev->savePCH_PIPEBSRC, PCH_PIPEBSRC);
	PSB_WVDC32(hdmi_dev->savePCH_HTOTAL_B, PCH_HTOTAL_B);
	PSB_WVDC32(hdmi_dev->savePCH_HBLANK_B, PCH_HBLANK_B);
	PSB_WVDC32(hdmi_dev->savePCH_HSYNC_B,  PCH_HSYNC_B);
	PSB_WVDC32(hdmi_dev->savePCH_VTOTAL_B, PCH_VTOTAL_B);
	PSB_WVDC32(hdmi_dev->savePCH_VBLANK_B, PCH_VBLANK_B);
	PSB_WVDC32(hdmi_dev->savePCH_VSYNC_B,  PCH_VSYNC_B);

	PSB_WVDC32(pipeb->conf, PIPEBCONF);
	PSB_WVDC32(hdmi_dev->savePCH_PIPEBCONF, PCH_PIPEBCONF);

	/* plane */
	PSB_WVDC32(pipeb->linoff, DSPBLINOFF);
	PSB_WVDC32(pipeb->stride, DSPBSTRIDE);
	PSB_WVDC32(pipeb->tileoff, DSPBTILखातापूर्णF);
	PSB_WVDC32(pipeb->cntr, DSPBCNTR);
	PSB_WVDC32(pipeb->surf, DSPBSURF);

	/* cursor B */
	PSB_WVDC32(regs->saveDSPBCURSOR_CTRL, CURBCNTR);
	PSB_WVDC32(regs->saveDSPBCURSOR_POS, CURBPOS);
	PSB_WVDC32(regs->saveDSPBCURSOR_BASE, CURBBASE);

	/* restore palette */
	क्रम (i = 0; i < 256; i++)
		PSB_WVDC32(pipeb->palette[i], PALETTE_B + (i << 2));
पूर्ण
