<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>

#समावेश <drm/drm.h>

#समावेश "cdv_device.h"
#समावेश "gma_device.h"
#समावेश "intel_bios.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_reg.h"

#घोषणा VGA_SR_INDEX		0x3c4
#घोषणा VGA_SR_DATA		0x3c5

अटल व्योम cdv_disable_vga(काष्ठा drm_device *dev)
अणु
	u8 sr1;
	u32 vga_reg;

	vga_reg = VGACNTRL;

	outb(1, VGA_SR_INDEX);
	sr1 = inb(VGA_SR_DATA);
	outb(sr1 | 1<<5, VGA_SR_DATA);
	udelay(300);

	REG_WRITE(vga_reg, VGA_DISP_DISABLE);
	REG_READ(vga_reg);
पूर्ण

अटल पूर्णांक cdv_output_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	drm_mode_create_scaling_mode_property(dev);

	cdv_disable_vga(dev);

	cdv_पूर्णांकel_crt_init(dev, &dev_priv->mode_dev);
	cdv_पूर्णांकel_lvds_init(dev, &dev_priv->mode_dev);

	/* These bits indicate HDMI not SDVO on CDV */
	अगर (REG_READ(SDVOB) & SDVO_DETECTED) अणु
		cdv_hdmi_init(dev, &dev_priv->mode_dev, SDVOB);
		अगर (REG_READ(DP_B) & DP_DETECTED)
			cdv_पूर्णांकel_dp_init(dev, &dev_priv->mode_dev, DP_B);
	पूर्ण

	अगर (REG_READ(SDVOC) & SDVO_DETECTED) अणु
		cdv_hdmi_init(dev, &dev_priv->mode_dev, SDVOC);
		अगर (REG_READ(DP_C) & DP_DETECTED)
			cdv_पूर्णांकel_dp_init(dev, &dev_priv->mode_dev, DP_C);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE

/*
 *	Cedartrail Backlght Interfaces
 */

अटल काष्ठा backlight_device *cdv_backlight_device;

अटल पूर्णांक cdv_backlight_combination_mode(काष्ठा drm_device *dev)
अणु
	वापस REG_READ(BLC_PWM_CTL2) & PWM_LEGACY_MODE;
पूर्ण

अटल u32 cdv_get_max_backlight(काष्ठा drm_device *dev)
अणु
	u32 max = REG_READ(BLC_PWM_CTL);

	अगर (max == 0) अणु
		DRM_DEBUG_KMS("LVDS Panel PWM value is 0!\n");
		/* i915 करोes this, I believe which means that we should not
		 * smash PWM control as firmware will take control of it. */
		वापस 1;
	पूर्ण

	max >>= 16;
	अगर (cdv_backlight_combination_mode(dev))
		max *= 0xff;
	वापस max;
पूर्ण

अटल पूर्णांक cdv_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा drm_device *dev = bl_get_data(bd);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 val = REG_READ(BLC_PWM_CTL) & BACKLIGHT_DUTY_CYCLE_MASK;

	अगर (cdv_backlight_combination_mode(dev)) अणु
		u8 lbpc;

		val &= ~1;
		pci_पढ़ो_config_byte(pdev, 0xF4, &lbpc);
		val *= lbpc;
	पूर्ण
	वापस (val * 100)/cdv_get_max_backlight(dev);

पूर्ण

अटल पूर्णांक cdv_set_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा drm_device *dev = bl_get_data(bd);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक level = bd->props.brightness;
	u32 blc_pwm_ctl;

	/* Percentage 1-100% being valid */
	अगर (level < 1)
		level = 1;

	level *= cdv_get_max_backlight(dev);
	level /= 100;

	अगर (cdv_backlight_combination_mode(dev)) अणु
		u32 max = cdv_get_max_backlight(dev);
		u8 lbpc;

		lbpc = level * 0xfe / max + 1;
		level /= lbpc;

		pci_ग_लिखो_config_byte(pdev, 0xF4, lbpc);
	पूर्ण

	blc_pwm_ctl = REG_READ(BLC_PWM_CTL) & ~BACKLIGHT_DUTY_CYCLE_MASK;
	REG_WRITE(BLC_PWM_CTL, (blc_pwm_ctl |
				(level << BACKLIGHT_DUTY_CYCLE_SHIFT)));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops cdv_ops = अणु
	.get_brightness = cdv_get_brightness,
	.update_status  = cdv_set_brightness,
पूर्ण;

अटल पूर्णांक cdv_backlight_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा backlight_properties props;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.max_brightness = 100;
	props.type = BACKLIGHT_PLATFORM;

	cdv_backlight_device = backlight_device_रेजिस्टर("psb-bl",
					शून्य, (व्योम *)dev, &cdv_ops, &props);
	अगर (IS_ERR(cdv_backlight_device))
		वापस PTR_ERR(cdv_backlight_device);

	cdv_backlight_device->props.brightness =
			cdv_get_brightness(cdv_backlight_device);
	backlight_update_status(cdv_backlight_device);
	dev_priv->backlight_device = cdv_backlight_device;
	dev_priv->backlight_enabled = true;
	वापस 0;
पूर्ण

#पूर्ण_अगर

/*
 *	Provide the Cedarview specअगरic chip logic and low level methods
 *	क्रम घातer management
 *
 *	FIXME: we need to implement the apm/ospm base management bits
 *	क्रम this and the MID devices.
 */

अटल अंतरभूत u32 CDV_MSG_READ32(पूर्णांक करोमुख्य, uपूर्णांक port, uपूर्णांक offset)
अणु
	पूर्णांक mcr = (0x10<<24) | (port << 16) | (offset << 8);
	uपूर्णांक32_t ret_val = 0;
	काष्ठा pci_dev *pci_root = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 0);
	pci_ग_लिखो_config_dword(pci_root, 0xD0, mcr);
	pci_पढ़ो_config_dword(pci_root, 0xD4, &ret_val);
	pci_dev_put(pci_root);
	वापस ret_val;
पूर्ण

अटल अंतरभूत व्योम CDV_MSG_WRITE32(पूर्णांक करोमुख्य, uपूर्णांक port, uपूर्णांक offset,
				   u32 value)
अणु
	पूर्णांक mcr = (0x11<<24) | (port << 16) | (offset << 8) | 0xF0;
	काष्ठा pci_dev *pci_root = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 0);
	pci_ग_लिखो_config_dword(pci_root, 0xD4, value);
	pci_ग_लिखो_config_dword(pci_root, 0xD0, mcr);
	pci_dev_put(pci_root);
पूर्ण

#घोषणा PSB_PM_SSC			0x20
#घोषणा PSB_PM_SSS			0x30
#घोषणा PSB_PWRGT_GFX_ON		0x02
#घोषणा PSB_PWRGT_GFX_OFF		0x01
#घोषणा PSB_PWRGT_GFX_D0		0x00
#घोषणा PSB_PWRGT_GFX_D3		0x03

अटल व्योम cdv_init_pm(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 pwr_cnt;
	पूर्णांक करोमुख्य = pci_करोमुख्य_nr(pdev->bus);
	पूर्णांक i;

	dev_priv->apm_base = CDV_MSG_READ32(करोमुख्य, PSB_PUNIT_PORT,
							PSB_APMBA) & 0xFFFF;
	dev_priv->ospm_base = CDV_MSG_READ32(करोमुख्य, PSB_PUNIT_PORT,
							PSB_OSPMBA) & 0xFFFF;

	/* Power status */
	pwr_cnt = inl(dev_priv->apm_base + PSB_APM_CMD);

	/* Enable the GPU */
	pwr_cnt &= ~PSB_PWRGT_GFX_MASK;
	pwr_cnt |= PSB_PWRGT_GFX_ON;
	outl(pwr_cnt, dev_priv->apm_base + PSB_APM_CMD);

	/* Wait क्रम the GPU घातer */
	क्रम (i = 0; i < 5; i++) अणु
		u32 pwr_sts = inl(dev_priv->apm_base + PSB_APM_STS);
		अगर ((pwr_sts & PSB_PWRGT_GFX_MASK) == 0)
			वापस;
		udelay(10);
	पूर्ण
	dev_err(dev->dev, "GPU: power management timed out.\n");
पूर्ण

अटल व्योम cdv_errata(काष्ठा drm_device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	/* Disable bonus launch.
	 *	CPU and GPU competes क्रम memory and display misses updates and
	 *	flickers. Worst with dual core, dual displays.
	 *
	 *	Fixes were करोne to Win 7 gfx driver to disable a feature called
	 *	Bonus Launch to work around the issue, by degrading
	 *	perक्रमmance.
	 */
	 CDV_MSG_WRITE32(pci_करोमुख्य_nr(pdev->bus), 3, 0x30, 0x08027108);
पूर्ण

/**
 *	cdv_save_display_रेजिस्टरs	-	save रेजिस्टरs lost on suspend
 *	@dev: our DRM device
 *
 *	Save the state we need in order to be able to restore the पूर्णांकerface
 *	upon resume from suspend
 */
अटल पूर्णांक cdv_save_display_रेजिस्टरs(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा psb_save_area *regs = &dev_priv->regs;
	काष्ठा drm_connector *connector;

	dev_dbg(dev->dev, "Saving GPU registers.\n");

	pci_पढ़ो_config_byte(pdev, 0xF4, &regs->cdv.saveLBB);

	regs->cdv.saveDSPCLK_GATE_D = REG_READ(DSPCLK_GATE_D);
	regs->cdv.saveRAMCLK_GATE_D = REG_READ(RAMCLK_GATE_D);

	regs->cdv.saveDSPARB = REG_READ(DSPARB);
	regs->cdv.saveDSPFW[0] = REG_READ(DSPFW1);
	regs->cdv.saveDSPFW[1] = REG_READ(DSPFW2);
	regs->cdv.saveDSPFW[2] = REG_READ(DSPFW3);
	regs->cdv.saveDSPFW[3] = REG_READ(DSPFW4);
	regs->cdv.saveDSPFW[4] = REG_READ(DSPFW5);
	regs->cdv.saveDSPFW[5] = REG_READ(DSPFW6);

	regs->cdv.saveADPA = REG_READ(ADPA);

	regs->cdv.savePP_CONTROL = REG_READ(PP_CONTROL);
	regs->cdv.savePFIT_PGM_RATIOS = REG_READ(PFIT_PGM_RATIOS);
	regs->saveBLC_PWM_CTL = REG_READ(BLC_PWM_CTL);
	regs->saveBLC_PWM_CTL2 = REG_READ(BLC_PWM_CTL2);
	regs->cdv.saveLVDS = REG_READ(LVDS);

	regs->cdv.savePFIT_CONTROL = REG_READ(PFIT_CONTROL);

	regs->cdv.savePP_ON_DELAYS = REG_READ(PP_ON_DELAYS);
	regs->cdv.savePP_OFF_DELAYS = REG_READ(PP_OFF_DELAYS);
	regs->cdv.savePP_CYCLE = REG_READ(PP_CYCLE);

	regs->cdv.saveVGACNTRL = REG_READ(VGACNTRL);

	regs->cdv.saveIER = REG_READ(PSB_INT_ENABLE_R);
	regs->cdv.saveIMR = REG_READ(PSB_INT_MASK_R);

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head)
		connector->funcs->dpms(connector, DRM_MODE_DPMS_OFF);

	वापस 0;
पूर्ण

/**
 *	cdv_restore_display_रेजिस्टरs	-	restore lost रेजिस्टर state
 *	@dev: our DRM device
 *
 *	Restore रेजिस्टर state that was lost during suspend and resume.
 *
 *	FIXME: review
 */
अटल पूर्णांक cdv_restore_display_रेजिस्टरs(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा psb_save_area *regs = &dev_priv->regs;
	काष्ठा drm_connector *connector;
	u32 temp;

	pci_ग_लिखो_config_byte(pdev, 0xF4, regs->cdv.saveLBB);

	REG_WRITE(DSPCLK_GATE_D, regs->cdv.saveDSPCLK_GATE_D);
	REG_WRITE(RAMCLK_GATE_D, regs->cdv.saveRAMCLK_GATE_D);

	/* BIOS करोes below anyway */
	REG_WRITE(DPIO_CFG, 0);
	REG_WRITE(DPIO_CFG, DPIO_MODE_SELECT_0 | DPIO_CMN_RESET_N);

	temp = REG_READ(DPLL_A);
	अगर ((temp & DPLL_SYNCLOCK_ENABLE) == 0) अणु
		REG_WRITE(DPLL_A, temp | DPLL_SYNCLOCK_ENABLE);
		REG_READ(DPLL_A);
	पूर्ण

	temp = REG_READ(DPLL_B);
	अगर ((temp & DPLL_SYNCLOCK_ENABLE) == 0) अणु
		REG_WRITE(DPLL_B, temp | DPLL_SYNCLOCK_ENABLE);
		REG_READ(DPLL_B);
	पूर्ण

	udelay(500);

	REG_WRITE(DSPFW1, regs->cdv.saveDSPFW[0]);
	REG_WRITE(DSPFW2, regs->cdv.saveDSPFW[1]);
	REG_WRITE(DSPFW3, regs->cdv.saveDSPFW[2]);
	REG_WRITE(DSPFW4, regs->cdv.saveDSPFW[3]);
	REG_WRITE(DSPFW5, regs->cdv.saveDSPFW[4]);
	REG_WRITE(DSPFW6, regs->cdv.saveDSPFW[5]);

	REG_WRITE(DSPARB, regs->cdv.saveDSPARB);
	REG_WRITE(ADPA, regs->cdv.saveADPA);

	REG_WRITE(BLC_PWM_CTL2, regs->saveBLC_PWM_CTL2);
	REG_WRITE(LVDS, regs->cdv.saveLVDS);
	REG_WRITE(PFIT_CONTROL, regs->cdv.savePFIT_CONTROL);
	REG_WRITE(PFIT_PGM_RATIOS, regs->cdv.savePFIT_PGM_RATIOS);
	REG_WRITE(BLC_PWM_CTL, regs->saveBLC_PWM_CTL);
	REG_WRITE(PP_ON_DELAYS, regs->cdv.savePP_ON_DELAYS);
	REG_WRITE(PP_OFF_DELAYS, regs->cdv.savePP_OFF_DELAYS);
	REG_WRITE(PP_CYCLE, regs->cdv.savePP_CYCLE);
	REG_WRITE(PP_CONTROL, regs->cdv.savePP_CONTROL);

	REG_WRITE(VGACNTRL, regs->cdv.saveVGACNTRL);

	REG_WRITE(PSB_INT_ENABLE_R, regs->cdv.saveIER);
	REG_WRITE(PSB_INT_MASK_R, regs->cdv.saveIMR);

	/* Fix arbitration bug */
	cdv_errata(dev);

	drm_mode_config_reset(dev);

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head)
		connector->funcs->dpms(connector, DRM_MODE_DPMS_ON);

	/* Resume the modeset क्रम every activated CRTC */
	drm_helper_resume_क्रमce_mode(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक cdv_घातer_करोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 pwr_cnt, pwr_mask, pwr_sts;
	पूर्णांक tries = 5;

	pwr_cnt = inl(dev_priv->apm_base + PSB_APM_CMD);
	pwr_cnt &= ~PSB_PWRGT_GFX_MASK;
	pwr_cnt |= PSB_PWRGT_GFX_OFF;
	pwr_mask = PSB_PWRGT_GFX_MASK;

	outl(pwr_cnt, dev_priv->apm_base + PSB_APM_CMD);

	जबतक (tries--) अणु
		pwr_sts = inl(dev_priv->apm_base + PSB_APM_STS);
		अगर ((pwr_sts & pwr_mask) == PSB_PWRGT_GFX_D3)
			वापस 0;
		udelay(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cdv_घातer_up(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 pwr_cnt, pwr_mask, pwr_sts;
	पूर्णांक tries = 5;

	pwr_cnt = inl(dev_priv->apm_base + PSB_APM_CMD);
	pwr_cnt &= ~PSB_PWRGT_GFX_MASK;
	pwr_cnt |= PSB_PWRGT_GFX_ON;
	pwr_mask = PSB_PWRGT_GFX_MASK;

	outl(pwr_cnt, dev_priv->apm_base + PSB_APM_CMD);

	जबतक (tries--) अणु
		pwr_sts = inl(dev_priv->apm_base + PSB_APM_STS);
		अगर ((pwr_sts & pwr_mask) == PSB_PWRGT_GFX_D0)
			वापस 0;
		udelay(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cdv_hotplug_work_func(काष्ठा work_काष्ठा *work)
अणु
        काष्ठा drm_psb_निजी *dev_priv = container_of(work, काष्ठा drm_psb_निजी,
							hotplug_work);
        काष्ठा drm_device *dev = dev_priv->dev;

        /* Just fire off a uevent and let userspace tell us what to करो */
        drm_helper_hpd_irq_event(dev);
पूर्ण

/* The core driver has received a hotplug IRQ. We are in IRQ context
   so extract the needed inक्रमmation and kick off queued processing */

अटल पूर्णांक cdv_hotplug_event(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	schedule_work(&dev_priv->hotplug_work);
	REG_WRITE(PORT_HOTPLUG_STAT, REG_READ(PORT_HOTPLUG_STAT));
	वापस 1;
पूर्ण

अटल व्योम cdv_hotplug_enable(काष्ठा drm_device *dev, bool on)
अणु
	अगर (on) अणु
		u32 hotplug = REG_READ(PORT_HOTPLUG_EN);
		hotplug |= HDMIB_HOTPLUG_INT_EN | HDMIC_HOTPLUG_INT_EN |
			   HDMID_HOTPLUG_INT_EN | CRT_HOTPLUG_INT_EN;
		REG_WRITE(PORT_HOTPLUG_EN, hotplug);
	पूर्ण  अन्यथा अणु
		REG_WRITE(PORT_HOTPLUG_EN, 0);
		REG_WRITE(PORT_HOTPLUG_STAT, REG_READ(PORT_HOTPLUG_STAT));
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *क्रमce_audio_names[] = अणु
	"off",
	"auto",
	"on",
पूर्ण;

व्योम cdv_पूर्णांकel_attach_क्रमce_audio_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_property *prop;
	पूर्णांक i;

	prop = dev_priv->क्रमce_audio_property;
	अगर (prop == शून्य) अणु
		prop = drm_property_create(dev, DRM_MODE_PROP_ENUM,
					   "audio",
					   ARRAY_SIZE(क्रमce_audio_names));
		अगर (prop == शून्य)
			वापस;

		क्रम (i = 0; i < ARRAY_SIZE(क्रमce_audio_names); i++)
			drm_property_add_क्रमागत(prop, i-1, क्रमce_audio_names[i]);

		dev_priv->क्रमce_audio_property = prop;
	पूर्ण
	drm_object_attach_property(&connector->base, prop, 0);
पूर्ण


अटल स्थिर अक्षर *broadcast_rgb_names[] = अणु
	"Full",
	"Limited 16:235",
पूर्ण;

व्योम cdv_पूर्णांकel_attach_broadcast_rgb_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_property *prop;
	पूर्णांक i;

	prop = dev_priv->broadcast_rgb_property;
	अगर (prop == शून्य) अणु
		prop = drm_property_create(dev, DRM_MODE_PROP_ENUM,
					   "Broadcast RGB",
					   ARRAY_SIZE(broadcast_rgb_names));
		अगर (prop == शून्य)
			वापस;

		क्रम (i = 0; i < ARRAY_SIZE(broadcast_rgb_names); i++)
			drm_property_add_क्रमागत(prop, i, broadcast_rgb_names[i]);

		dev_priv->broadcast_rgb_property = prop;
	पूर्ण

	drm_object_attach_property(&connector->base, prop, 0);
पूर्ण

/* Cedarview */
अटल स्थिर काष्ठा psb_offset cdv_regmap[2] = अणु
	अणु
		.fp0 = FPA0,
		.fp1 = FPA1,
		.cntr = DSPACNTR,
		.conf = PIPEACONF,
		.src = PIPEASRC,
		.dpll = DPLL_A,
		.dpll_md = DPLL_A_MD,
		.htotal = HTOTAL_A,
		.hblank = HBLANK_A,
		.hsync = HSYNC_A,
		.vtotal = VTOTAL_A,
		.vblank = VBLANK_A,
		.vsync = VSYNC_A,
		.stride = DSPASTRIDE,
		.size = DSPASIZE,
		.pos = DSPAPOS,
		.base = DSPABASE,
		.surf = DSPASURF,
		.addr = DSPABASE,
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
		.dpll_md = DPLL_B_MD,
		.htotal = HTOTAL_B,
		.hblank = HBLANK_B,
		.hsync = HSYNC_B,
		.vtotal = VTOTAL_B,
		.vblank = VBLANK_B,
		.vsync = VSYNC_B,
		.stride = DSPBSTRIDE,
		.size = DSPBSIZE,
		.pos = DSPBPOS,
		.base = DSPBBASE,
		.surf = DSPBSURF,
		.addr = DSPBBASE,
		.status = PIPEBSTAT,
		.linoff = DSPBLINOFF,
		.tileoff = DSPBTILखातापूर्णF,
		.palette = PALETTE_B,
	पूर्ण
पूर्ण;

अटल पूर्णांक cdv_chip_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	INIT_WORK(&dev_priv->hotplug_work, cdv_hotplug_work_func);

	अगर (pci_enable_msi(pdev))
		dev_warn(dev->dev, "Enabling MSI failed!\n");
	dev_priv->regmap = cdv_regmap;
	gma_get_core_freq(dev);
	psb_पूर्णांकel_opregion_init(dev);
	psb_पूर्णांकel_init_bios(dev);
	cdv_hotplug_enable(dev, false);
	वापस 0;
पूर्ण

/* CDV is much like Poulsbo but has MID like SGX offsets and PM */

स्थिर काष्ठा psb_ops cdv_chip_ops = अणु
	.name = "GMA3600/3650",
	.pipes = 2,
	.crtcs = 2,
	.hdmi_mask = (1 << 0) | (1 << 1),
	.lvds_mask = (1 << 1),
	.sdvo_mask = (1 << 0),
	.cursor_needs_phys = 0,
	.sgx_offset = MRST_SGX_OFFSET,
	.chip_setup = cdv_chip_setup,
	.errata = cdv_errata,

	.crtc_helper = &cdv_पूर्णांकel_helper_funcs,
	.crtc_funcs = &gma_पूर्णांकel_crtc_funcs,
	.घड़ी_funcs = &cdv_घड़ी_funcs,

	.output_init = cdv_output_init,
	.hotplug = cdv_hotplug_event,
	.hotplug_enable = cdv_hotplug_enable,

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	.backlight_init = cdv_backlight_init,
#पूर्ण_अगर

	.init_pm = cdv_init_pm,
	.save_regs = cdv_save_display_रेजिस्टरs,
	.restore_regs = cdv_restore_display_रेजिस्टरs,
	.save_crtc = gma_crtc_save,
	.restore_crtc = gma_crtc_restore,
	.घातer_करोwn = cdv_घातer_करोwn,
	.घातer_up = cdv_घातer_up,
	.update_wm = cdv_update_wm,
	.disable_sr = cdv_disable_sr,
पूर्ण;
