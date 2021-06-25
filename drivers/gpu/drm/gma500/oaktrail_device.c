<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>

#समावेश <drm/drm.h>

#समावेश "intel_bios.h"
#समावेश "mid_bios.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_reg.h"

अटल पूर्णांक oaktrail_output_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अगर (dev_priv->iLVDS_enable)
		oaktrail_lvds_init(dev, &dev_priv->mode_dev);
	अन्यथा
		dev_err(dev->dev, "DSI is not supported\n");
	अगर (dev_priv->hdmi_priv)
		oaktrail_hdmi_init(dev, &dev_priv->mode_dev);

	psb_पूर्णांकel_sdvo_init(dev, SDVOB);

	वापस 0;
पूर्ण

/*
 *	Provide the low level पूर्णांकerfaces क्रम the Moorestown backlight
 */

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE

#घोषणा MRST_BLC_MAX_PWM_REG_FREQ	    0xFFFF
#घोषणा BLC_PWM_PRECISION_FACTOR 100	/* 10000000 */
#घोषणा BLC_PWM_FREQ_CALC_CONSTANT 32
#घोषणा MHz 1000000
#घोषणा BLC_ADJUSTMENT_MAX 100

अटल काष्ठा backlight_device *oaktrail_backlight_device;
अटल पूर्णांक oaktrail_brightness;

अटल पूर्णांक oaktrail_set_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा drm_device *dev = bl_get_data(oaktrail_backlight_device);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक level = bd->props.brightness;
	u32 blc_pwm_ctl;
	u32 max_pwm_blc;

	/* Percentage 1-100% being valid */
	अगर (level < 1)
		level = 1;

	अगर (gma_घातer_begin(dev, 0)) अणु
		/* Calculate and set the brightness value */
		max_pwm_blc = REG_READ(BLC_PWM_CTL) >> 16;
		blc_pwm_ctl = level * max_pwm_blc / 100;

		/* Adjust the backlight level with the percent in
		 * dev_priv->blc_adj1;
		 */
		blc_pwm_ctl = blc_pwm_ctl * dev_priv->blc_adj1;
		blc_pwm_ctl = blc_pwm_ctl / 100;

		/* Adjust the backlight level with the percent in
		 * dev_priv->blc_adj2;
		 */
		blc_pwm_ctl = blc_pwm_ctl * dev_priv->blc_adj2;
		blc_pwm_ctl = blc_pwm_ctl / 100;

		/* क्रमce PWM bit on */
		REG_WRITE(BLC_PWM_CTL2, (0x80000000 | REG_READ(BLC_PWM_CTL2)));
		REG_WRITE(BLC_PWM_CTL, (max_pwm_blc << 16) | blc_pwm_ctl);
		gma_घातer_end(dev);
	पूर्ण
	oaktrail_brightness = level;
	वापस 0;
पूर्ण

अटल पूर्णांक oaktrail_get_brightness(काष्ठा backlight_device *bd)
अणु
	/* वापस locally cached var instead of HW पढ़ो (due to DPST etc.) */
	/* FIXME: ideally वापस actual value in हाल firmware fiddled with
	   it */
	वापस oaktrail_brightness;
पूर्ण

अटल पूर्णांक device_backlight_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ core_घड़ी;
	u16 bl_max_freq;
	uपूर्णांक32_t value;
	uपूर्णांक32_t blc_pwm_precision_factor;

	dev_priv->blc_adj1 = BLC_ADJUSTMENT_MAX;
	dev_priv->blc_adj2 = BLC_ADJUSTMENT_MAX;
	bl_max_freq = 256;
	/* this needs to be set अन्यथाwhere */
	blc_pwm_precision_factor = BLC_PWM_PRECISION_FACTOR;

	core_घड़ी = dev_priv->core_freq;

	value = (core_घड़ी * MHz) / BLC_PWM_FREQ_CALC_CONSTANT;
	value *= blc_pwm_precision_factor;
	value /= bl_max_freq;
	value /= blc_pwm_precision_factor;

	अगर (value > (अचिन्हित दीर्घ दीर्घ)MRST_BLC_MAX_PWM_REG_FREQ)
			वापस -दुस्फल;

	अगर (gma_घातer_begin(dev, false)) अणु
		REG_WRITE(BLC_PWM_CTL2, (0x80000000 | REG_READ(BLC_PWM_CTL2)));
		REG_WRITE(BLC_PWM_CTL, value | (value << 16));
		gma_घातer_end(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops oaktrail_ops = अणु
	.get_brightness = oaktrail_get_brightness,
	.update_status  = oaktrail_set_brightness,
पूर्ण;

अटल पूर्णांक oaktrail_backlight_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret;
	काष्ठा backlight_properties props;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.max_brightness = 100;
	props.type = BACKLIGHT_PLATFORM;

	oaktrail_backlight_device = backlight_device_रेजिस्टर("oaktrail-bl",
				शून्य, (व्योम *)dev, &oaktrail_ops, &props);

	अगर (IS_ERR(oaktrail_backlight_device))
		वापस PTR_ERR(oaktrail_backlight_device);

	ret = device_backlight_init(dev);
	अगर (ret < 0) अणु
		backlight_device_unरेजिस्टर(oaktrail_backlight_device);
		वापस ret;
	पूर्ण
	oaktrail_backlight_device->props.brightness = 100;
	oaktrail_backlight_device->props.max_brightness = 100;
	backlight_update_status(oaktrail_backlight_device);
	dev_priv->backlight_device = oaktrail_backlight_device;
	वापस 0;
पूर्ण

#पूर्ण_अगर

/*
 *	Provide the Moorestown specअगरic chip logic and low level methods
 *	क्रम घातer management
 */

/**
 *	oaktrail_save_display_रेजिस्टरs	-	save रेजिस्टरs lost on suspend
 *	@dev: our DRM device
 *
 *	Save the state we need in order to be able to restore the पूर्णांकerface
 *	upon resume from suspend
 */
अटल पूर्णांक oaktrail_save_display_रेजिस्टरs(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_save_area *regs = &dev_priv->regs;
	काष्ठा psb_pipe *p = &regs->pipe[0];
	पूर्णांक i;
	u32 pp_stat;

	/* Display arbitration control + watermarks */
	regs->psb.saveDSPARB = PSB_RVDC32(DSPARB);
	regs->psb.saveDSPFW1 = PSB_RVDC32(DSPFW1);
	regs->psb.saveDSPFW2 = PSB_RVDC32(DSPFW2);
	regs->psb.saveDSPFW3 = PSB_RVDC32(DSPFW3);
	regs->psb.saveDSPFW4 = PSB_RVDC32(DSPFW4);
	regs->psb.saveDSPFW5 = PSB_RVDC32(DSPFW5);
	regs->psb.saveDSPFW6 = PSB_RVDC32(DSPFW6);
	regs->psb.saveCHICKENBIT = PSB_RVDC32(DSPCHICKENBIT);

	/* Pipe & plane A info */
	p->conf = PSB_RVDC32(PIPEACONF);
	p->src = PSB_RVDC32(PIPEASRC);
	p->fp0 = PSB_RVDC32(MRST_FPA0);
	p->fp1 = PSB_RVDC32(MRST_FPA1);
	p->dpll = PSB_RVDC32(MRST_DPLL_A);
	p->htotal = PSB_RVDC32(HTOTAL_A);
	p->hblank = PSB_RVDC32(HBLANK_A);
	p->hsync = PSB_RVDC32(HSYNC_A);
	p->vtotal = PSB_RVDC32(VTOTAL_A);
	p->vblank = PSB_RVDC32(VBLANK_A);
	p->vsync = PSB_RVDC32(VSYNC_A);
	regs->psb.saveBCLRPAT_A = PSB_RVDC32(BCLRPAT_A);
	p->cntr = PSB_RVDC32(DSPACNTR);
	p->stride = PSB_RVDC32(DSPASTRIDE);
	p->addr = PSB_RVDC32(DSPABASE);
	p->surf = PSB_RVDC32(DSPASURF);
	p->linoff = PSB_RVDC32(DSPALINOFF);
	p->tileoff = PSB_RVDC32(DSPATILखातापूर्णF);

	/* Save cursor regs */
	regs->psb.saveDSPACURSOR_CTRL = PSB_RVDC32(CURACNTR);
	regs->psb.saveDSPACURSOR_BASE = PSB_RVDC32(CURABASE);
	regs->psb.saveDSPACURSOR_POS = PSB_RVDC32(CURAPOS);

	/* Save palette (gamma) */
	क्रम (i = 0; i < 256; i++)
		p->palette[i] = PSB_RVDC32(PALETTE_A + (i << 2));

	अगर (dev_priv->hdmi_priv)
		oaktrail_hdmi_save(dev);

	/* Save perक्रमmance state */
	regs->psb.savePERF_MODE = PSB_RVDC32(MRST_PERF_MODE);

	/* LVDS state */
	regs->psb.savePP_CONTROL = PSB_RVDC32(PP_CONTROL);
	regs->psb.savePFIT_PGM_RATIOS = PSB_RVDC32(PFIT_PGM_RATIOS);
	regs->psb.savePFIT_AUTO_RATIOS = PSB_RVDC32(PFIT_AUTO_RATIOS);
	regs->saveBLC_PWM_CTL = PSB_RVDC32(BLC_PWM_CTL);
	regs->saveBLC_PWM_CTL2 = PSB_RVDC32(BLC_PWM_CTL2);
	regs->psb.saveLVDS = PSB_RVDC32(LVDS);
	regs->psb.savePFIT_CONTROL = PSB_RVDC32(PFIT_CONTROL);
	regs->psb.savePP_ON_DELAYS = PSB_RVDC32(LVDSPP_ON);
	regs->psb.savePP_OFF_DELAYS = PSB_RVDC32(LVDSPP_OFF);
	regs->psb.savePP_DIVISOR = PSB_RVDC32(PP_CYCLE);

	/* HW overlay */
	regs->psb.saveOV_OVADD = PSB_RVDC32(OV_OVADD);
	regs->psb.saveOV_OGAMC0 = PSB_RVDC32(OV_OGAMC0);
	regs->psb.saveOV_OGAMC1 = PSB_RVDC32(OV_OGAMC1);
	regs->psb.saveOV_OGAMC2 = PSB_RVDC32(OV_OGAMC2);
	regs->psb.saveOV_OGAMC3 = PSB_RVDC32(OV_OGAMC3);
	regs->psb.saveOV_OGAMC4 = PSB_RVDC32(OV_OGAMC4);
	regs->psb.saveOV_OGAMC5 = PSB_RVDC32(OV_OGAMC5);

	/* DPST रेजिस्टरs */
	regs->psb.saveHISTOGRAM_INT_CONTROL_REG =
					PSB_RVDC32(HISTOGRAM_INT_CONTROL);
	regs->psb.saveHISTOGRAM_LOGIC_CONTROL_REG =
					PSB_RVDC32(HISTOGRAM_LOGIC_CONTROL);
	regs->psb.savePWM_CONTROL_LOGIC = PSB_RVDC32(PWM_CONTROL_LOGIC);

	अगर (dev_priv->iLVDS_enable) अणु
		/* Shut करोwn the panel */
		PSB_WVDC32(0, PP_CONTROL);

		करो अणु
			pp_stat = PSB_RVDC32(PP_STATUS);
		पूर्ण जबतक (pp_stat & 0x80000000);

		/* Turn off the plane */
		PSB_WVDC32(0x58000000, DSPACNTR);
		/* Trigger the plane disable */
		PSB_WVDC32(0, DSPASURF);

		/* Wait ~4 ticks */
		msleep(4);

		/* Turn off pipe */
		PSB_WVDC32(0x0, PIPEACONF);
		/* Wait ~8 ticks */
		msleep(8);

		/* Turn off PLLs */
		PSB_WVDC32(0, MRST_DPLL_A);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	oaktrail_restore_display_रेजिस्टरs	-	restore lost रेजिस्टर state
 *	@dev: our DRM device
 *
 *	Restore रेजिस्टर state that was lost during suspend and resume.
 */
अटल पूर्णांक oaktrail_restore_display_रेजिस्टरs(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_save_area *regs = &dev_priv->regs;
	काष्ठा psb_pipe *p = &regs->pipe[0];
	u32 pp_stat;
	पूर्णांक i;

	/* Display arbitration + watermarks */
	PSB_WVDC32(regs->psb.saveDSPARB, DSPARB);
	PSB_WVDC32(regs->psb.saveDSPFW1, DSPFW1);
	PSB_WVDC32(regs->psb.saveDSPFW2, DSPFW2);
	PSB_WVDC32(regs->psb.saveDSPFW3, DSPFW3);
	PSB_WVDC32(regs->psb.saveDSPFW4, DSPFW4);
	PSB_WVDC32(regs->psb.saveDSPFW5, DSPFW5);
	PSB_WVDC32(regs->psb.saveDSPFW6, DSPFW6);
	PSB_WVDC32(regs->psb.saveCHICKENBIT, DSPCHICKENBIT);

	/* Make sure VGA plane is off. it initializes to on after reset!*/
	PSB_WVDC32(0x80000000, VGACNTRL);

	/* set the plls */
	PSB_WVDC32(p->fp0, MRST_FPA0);
	PSB_WVDC32(p->fp1, MRST_FPA1);

	/* Actually enable it */
	PSB_WVDC32(p->dpll, MRST_DPLL_A);
	udelay(150);

	/* Restore mode */
	PSB_WVDC32(p->htotal, HTOTAL_A);
	PSB_WVDC32(p->hblank, HBLANK_A);
	PSB_WVDC32(p->hsync, HSYNC_A);
	PSB_WVDC32(p->vtotal, VTOTAL_A);
	PSB_WVDC32(p->vblank, VBLANK_A);
	PSB_WVDC32(p->vsync, VSYNC_A);
	PSB_WVDC32(p->src, PIPEASRC);
	PSB_WVDC32(regs->psb.saveBCLRPAT_A, BCLRPAT_A);

	/* Restore perक्रमmance mode*/
	PSB_WVDC32(regs->psb.savePERF_MODE, MRST_PERF_MODE);

	/* Enable the pipe*/
	अगर (dev_priv->iLVDS_enable)
		PSB_WVDC32(p->conf, PIPEACONF);

	/* Set up the plane*/
	PSB_WVDC32(p->linoff, DSPALINOFF);
	PSB_WVDC32(p->stride, DSPASTRIDE);
	PSB_WVDC32(p->tileoff, DSPATILखातापूर्णF);

	/* Enable the plane */
	PSB_WVDC32(p->cntr, DSPACNTR);
	PSB_WVDC32(p->surf, DSPASURF);

	/* Enable Cursor A */
	PSB_WVDC32(regs->psb.saveDSPACURSOR_CTRL, CURACNTR);
	PSB_WVDC32(regs->psb.saveDSPACURSOR_POS, CURAPOS);
	PSB_WVDC32(regs->psb.saveDSPACURSOR_BASE, CURABASE);

	/* Restore palette (gamma) */
	क्रम (i = 0; i < 256; i++)
		PSB_WVDC32(p->palette[i], PALETTE_A + (i << 2));

	अगर (dev_priv->hdmi_priv)
		oaktrail_hdmi_restore(dev);

	अगर (dev_priv->iLVDS_enable) अणु
		PSB_WVDC32(regs->saveBLC_PWM_CTL2, BLC_PWM_CTL2);
		PSB_WVDC32(regs->psb.saveLVDS, LVDS); /*port 61180h*/
		PSB_WVDC32(regs->psb.savePFIT_CONTROL, PFIT_CONTROL);
		PSB_WVDC32(regs->psb.savePFIT_PGM_RATIOS, PFIT_PGM_RATIOS);
		PSB_WVDC32(regs->psb.savePFIT_AUTO_RATIOS, PFIT_AUTO_RATIOS);
		PSB_WVDC32(regs->saveBLC_PWM_CTL, BLC_PWM_CTL);
		PSB_WVDC32(regs->psb.savePP_ON_DELAYS, LVDSPP_ON);
		PSB_WVDC32(regs->psb.savePP_OFF_DELAYS, LVDSPP_OFF);
		PSB_WVDC32(regs->psb.savePP_DIVISOR, PP_CYCLE);
		PSB_WVDC32(regs->psb.savePP_CONTROL, PP_CONTROL);
	पूर्ण

	/* Wait क्रम cycle delay */
	करो अणु
		pp_stat = PSB_RVDC32(PP_STATUS);
	पूर्ण जबतक (pp_stat & 0x08000000);

	/* Wait क्रम panel घातer up */
	करो अणु
		pp_stat = PSB_RVDC32(PP_STATUS);
	पूर्ण जबतक (pp_stat & 0x10000000);

	/* Restore HW overlay */
	PSB_WVDC32(regs->psb.saveOV_OVADD, OV_OVADD);
	PSB_WVDC32(regs->psb.saveOV_OGAMC0, OV_OGAMC0);
	PSB_WVDC32(regs->psb.saveOV_OGAMC1, OV_OGAMC1);
	PSB_WVDC32(regs->psb.saveOV_OGAMC2, OV_OGAMC2);
	PSB_WVDC32(regs->psb.saveOV_OGAMC3, OV_OGAMC3);
	PSB_WVDC32(regs->psb.saveOV_OGAMC4, OV_OGAMC4);
	PSB_WVDC32(regs->psb.saveOV_OGAMC5, OV_OGAMC5);

	/* DPST रेजिस्टरs */
	PSB_WVDC32(regs->psb.saveHISTOGRAM_INT_CONTROL_REG,
						HISTOGRAM_INT_CONTROL);
	PSB_WVDC32(regs->psb.saveHISTOGRAM_LOGIC_CONTROL_REG,
						HISTOGRAM_LOGIC_CONTROL);
	PSB_WVDC32(regs->psb.savePWM_CONTROL_LOGIC, PWM_CONTROL_LOGIC);

	वापस 0;
पूर्ण

/**
 *	oaktrail_घातer_करोwn	-	घातer करोwn the display island
 *	@dev: our DRM device
 *
 *	Power करोwn the display पूर्णांकerface of our device
 */
अटल पूर्णांक oaktrail_घातer_करोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 pwr_mask ;
	u32 pwr_sts;

	pwr_mask = PSB_PWRGT_DISPLAY_MASK;
	outl(pwr_mask, dev_priv->ospm_base + PSB_PM_SSC);

	जबतक (true) अणु
		pwr_sts = inl(dev_priv->ospm_base + PSB_PM_SSS);
		अगर ((pwr_sts & pwr_mask) == pwr_mask)
			अवरोध;
		अन्यथा
			udelay(10);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * oaktrail_घातer_up
 *
 * Restore घातer to the specअगरied island(s) (घातergating)
 */
अटल पूर्णांक oaktrail_घातer_up(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 pwr_mask = PSB_PWRGT_DISPLAY_MASK;
	u32 pwr_sts, pwr_cnt;

	pwr_cnt = inl(dev_priv->ospm_base + PSB_PM_SSC);
	pwr_cnt &= ~pwr_mask;
	outl(pwr_cnt, (dev_priv->ospm_base + PSB_PM_SSC));

	जबतक (true) अणु
		pwr_sts = inl(dev_priv->ospm_base + PSB_PM_SSS);
		अगर ((pwr_sts & pwr_mask) == 0)
			अवरोध;
		अन्यथा
			udelay(10);
	पूर्ण
	वापस 0;
पूर्ण

/* Oaktrail */
अटल स्थिर काष्ठा psb_offset oaktrail_regmap[2] = अणु
	अणु
		.fp0 = MRST_FPA0,
		.fp1 = MRST_FPA1,
		.cntr = DSPACNTR,
		.conf = PIPEACONF,
		.src = PIPEASRC,
		.dpll = MRST_DPLL_A,
		.htotal = HTOTAL_A,
		.hblank = HBLANK_A,
		.hsync = HSYNC_A,
		.vtotal = VTOTAL_A,
		.vblank = VBLANK_A,
		.vsync = VSYNC_A,
		.stride = DSPASTRIDE,
		.size = DSPASIZE,
		.pos = DSPAPOS,
		.surf = DSPASURF,
		.addr = MRST_DSPABASE,
		.base = MRST_DSPABASE,
		.status = PIPEASTAT,
		.linoff = DSPALINOFF,
		.tileoff = DSPATILखातापूर्णF,
		.palette = PALETTE_A,
	पूर्ण,
	अणु
		.fp0 = FPB0,
		.fp1 = FPB1,
		.cntr = DSPBCNTR,
		.conf = PIPEBCONF,
		.src = PIPEBSRC,
		.dpll = DPLL_B,
		.htotal = HTOTAL_B,
		.hblank = HBLANK_B,
		.hsync = HSYNC_B,
		.vtotal = VTOTAL_B,
		.vblank = VBLANK_B,
		.vsync = VSYNC_B,
		.stride = DSPBSTRIDE,
		.size = DSPBSIZE,
		.pos = DSPBPOS,
		.surf = DSPBSURF,
		.addr = DSPBBASE,
		.base = DSPBBASE,
		.status = PIPEBSTAT,
		.linoff = DSPBLINOFF,
		.tileoff = DSPBTILखातापूर्णF,
		.palette = PALETTE_B,
	पूर्ण,
पूर्ण;

अटल पूर्णांक oaktrail_chip_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक ret;

	अगर (pci_enable_msi(pdev))
		dev_warn(dev->dev, "Enabling MSI failed!\n");

	dev_priv->regmap = oaktrail_regmap;

	ret = mid_chip_setup(dev);
	अगर (ret < 0)
		वापस ret;
	अगर (!dev_priv->has_gct) अणु
		/* Now pull the BIOS data */
		psb_पूर्णांकel_opregion_init(dev);
		psb_पूर्णांकel_init_bios(dev);
	पूर्ण
	gma_पूर्णांकel_setup_gmbus(dev);
	oaktrail_hdmi_setup(dev);
	वापस 0;
पूर्ण

अटल व्योम oaktrail_tearकरोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	gma_पूर्णांकel_tearकरोwn_gmbus(dev);
	oaktrail_hdmi_tearकरोwn(dev);
	अगर (!dev_priv->has_gct)
		psb_पूर्णांकel_destroy_bios(dev);
पूर्ण

स्थिर काष्ठा psb_ops oaktrail_chip_ops = अणु
	.name = "Oaktrail",
	.pipes = 2,
	.crtcs = 2,
	.hdmi_mask = (1 << 1),
	.lvds_mask = (1 << 0),
	.sdvo_mask = (1 << 1),
	.cursor_needs_phys = 0,
	.sgx_offset = MRST_SGX_OFFSET,

	.chip_setup = oaktrail_chip_setup,
	.chip_tearकरोwn = oaktrail_tearकरोwn,
	.crtc_helper = &oaktrail_helper_funcs,
	.crtc_funcs = &gma_पूर्णांकel_crtc_funcs,

	.output_init = oaktrail_output_init,

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	.backlight_init = oaktrail_backlight_init,
#पूर्ण_अगर

	.save_regs = oaktrail_save_display_रेजिस्टरs,
	.restore_regs = oaktrail_restore_display_रेजिस्टरs,
	.save_crtc = gma_crtc_save,
	.restore_crtc = gma_crtc_restore,
	.घातer_करोwn = oaktrail_घातer_करोwn,
	.घातer_up = oaktrail_घातer_up,

	.i2c_bus = 1,
पूर्ण;
