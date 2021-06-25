<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_drv.c  --  R-Car Display Unit DRM driver
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_du_of.h"
#समावेश "rcar_du_regs.h"

/* -----------------------------------------------------------------------------
 * Device Inक्रमmation
 */

अटल स्थिर काष्ठा rcar_du_device_info rzg1_du_r8a7743_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A774[34] has one RGB output and one LVDS output
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(1) | BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 1,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rzg1_du_r8a7745_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A7745 has two RGB outमाला_दो
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_DPAD1] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rzg1_du_r8a77470_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A77470 has two RGB outमाला_दो, one LVDS output, and
		 * one (currently unsupported) analog video output
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_DPAD1] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0) | BIT(1),
			.port = 2,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a774a1_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(2) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A774A1 has one RGB output, one LVDS output and one HDMI
		 * output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(2),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI0] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
	.dpll_mask =  BIT(1),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a774b1_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(3) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A774B1 has one RGB output, one LVDS output and one HDMI
		 * output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(2),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI0] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
	.dpll_mask =  BIT(1),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a774c0_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A774C0 has one RGB output and two LVDS outमाला_दो
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0) | BIT(1),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS1] = अणु
			.possible_crtcs = BIT(1),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 2,
	.lvds_clk_mask =  BIT(1) | BIT(0),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a774e1_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(3) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A774E1 has one RGB output, one LVDS output and one HDMI
		 * output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(2),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI0] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
	.dpll_mask =  BIT(1),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7779_info = अणु
	.gen = 1,
	.features = RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A7779 has two RGB outमाला_दो and one (currently unsupported)
		 * TCON output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_DPAD1] = अणु
			.possible_crtcs = BIT(1) | BIT(0),
			.port = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7790_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.quirks = RCAR_DU_QUIRK_ALIGN_128B,
	.channels_mask = BIT(2) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A7742 and R8A7790 each have one RGB output and two LVDS
		 * outमाला_दो. Additionally R8A7790 supports one TCON output
		 * (currently unsupported by the driver).
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(2) | BIT(1) | BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS1] = अणु
			.possible_crtcs = BIT(2) | BIT(1),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 2,
पूर्ण;

/* M2-W (r8a7791) and M2-N (r8a7793) are identical */
अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7791_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A779[13] has one RGB output, one LVDS output and one
		 * (currently unsupported) TCON output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(1) | BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 1,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7792_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/* R8A7792 has two RGB outमाला_दो. */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_DPAD1] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7794_info = अणु
	.gen = 2,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A7794 has two RGB outमाला_दो and one (currently unsupported)
		 * TCON output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_DPAD1] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7795_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(3) | BIT(2) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A7795 has one RGB output, two HDMI outमाला_दो and one
		 * LVDS output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(3),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI0] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI1] = अणु
			.possible_crtcs = BIT(2),
			.port = 2,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 3,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
	.dpll_mask =  BIT(2) | BIT(1),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7796_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(2) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A7796 has one RGB output, one LVDS output and one HDMI
		 * output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(2),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI0] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
	.dpll_mask =  BIT(1),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a77965_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(3) | BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A77965 has one RGB output, one LVDS output and one HDMI
		 * output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(2),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_HDMI0] = अणु
			.possible_crtcs = BIT(1),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
	.dpll_mask =  BIT(1),
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a77970_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE
		  | RCAR_DU_FEATURE_INTERLACED
		  | RCAR_DU_FEATURE_TVM_SYNC,
	.channels_mask = BIT(0),
	.routes = अणु
		/*
		 * R8A77970 and R8A77980 have one RGB output and one LVDS
		 * output.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 1,
		पूर्ण,
	पूर्ण,
	.num_lvds = 1,
पूर्ण;

अटल स्थिर काष्ठा rcar_du_device_info rcar_du_r8a7799x_info = अणु
	.gen = 3,
	.features = RCAR_DU_FEATURE_CRTC_IRQ_CLOCK
		  | RCAR_DU_FEATURE_VSP1_SOURCE,
	.channels_mask = BIT(1) | BIT(0),
	.routes = अणु
		/*
		 * R8A77990 and R8A77995 have one RGB output and two LVDS
		 * outमाला_दो.
		 */
		[RCAR_DU_OUTPUT_DPAD0] = अणु
			.possible_crtcs = BIT(0) | BIT(1),
			.port = 0,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS0] = अणु
			.possible_crtcs = BIT(0),
			.port = 1,
		पूर्ण,
		[RCAR_DU_OUTPUT_LVDS1] = अणु
			.possible_crtcs = BIT(1),
			.port = 2,
		पूर्ण,
	पूर्ण,
	.num_lvds = 2,
	.lvds_clk_mask =  BIT(1) | BIT(0),
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_du_of_table[] = अणु
	अणु .compatible = "renesas,du-r8a7742", .data = &rcar_du_r8a7790_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7743", .data = &rzg1_du_r8a7743_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7744", .data = &rzg1_du_r8a7743_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7745", .data = &rzg1_du_r8a7745_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77470", .data = &rzg1_du_r8a77470_info पूर्ण,
	अणु .compatible = "renesas,du-r8a774a1", .data = &rcar_du_r8a774a1_info पूर्ण,
	अणु .compatible = "renesas,du-r8a774b1", .data = &rcar_du_r8a774b1_info पूर्ण,
	अणु .compatible = "renesas,du-r8a774c0", .data = &rcar_du_r8a774c0_info पूर्ण,
	अणु .compatible = "renesas,du-r8a774e1", .data = &rcar_du_r8a774e1_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7779", .data = &rcar_du_r8a7779_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7790", .data = &rcar_du_r8a7790_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7791", .data = &rcar_du_r8a7791_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7792", .data = &rcar_du_r8a7792_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7793", .data = &rcar_du_r8a7791_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7794", .data = &rcar_du_r8a7794_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7795", .data = &rcar_du_r8a7795_info पूर्ण,
	अणु .compatible = "renesas,du-r8a7796", .data = &rcar_du_r8a7796_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77961", .data = &rcar_du_r8a7796_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77965", .data = &rcar_du_r8a77965_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77970", .data = &rcar_du_r8a77970_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77980", .data = &rcar_du_r8a77970_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77990", .data = &rcar_du_r8a7799x_info पूर्ण,
	अणु .compatible = "renesas,du-r8a77995", .data = &rcar_du_r8a7799x_info पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rcar_du_of_table);

/* -----------------------------------------------------------------------------
 * DRM operations
 */

DEFINE_DRM_GEM_CMA_FOPS(rcar_du_fops);

अटल स्थिर काष्ठा drm_driver rcar_du_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(rcar_du_dumb_create),
	.fops			= &rcar_du_fops,
	.name			= "rcar-du",
	.desc			= "Renesas R-Car Display Unit",
	.date			= "20130110",
	.major			= 1,
	.minor			= 0,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Power management
 */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rcar_du_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा rcar_du_device *rcdu = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(&rcdu->ddev);
पूर्ण

अटल पूर्णांक rcar_du_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा rcar_du_device *rcdu = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(&rcdu->ddev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rcar_du_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rcar_du_pm_suspend, rcar_du_pm_resume)
पूर्ण;

/* -----------------------------------------------------------------------------
 * Platक्रमm driver
 */

अटल पूर्णांक rcar_du_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_du_device *rcdu = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_device *ddev = &rcdu->ddev;

	drm_dev_unरेजिस्टर(ddev);

	drm_kms_helper_poll_fini(ddev);

	drm_dev_put(ddev);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_du_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_du_device *rcdu;
	काष्ठा resource *mem;
	पूर्णांक ret;

	/* Allocate and initialize the R-Car device काष्ठाure. */
	rcdu = devm_drm_dev_alloc(&pdev->dev, &rcar_du_driver,
				  काष्ठा rcar_du_device, ddev);
	अगर (IS_ERR(rcdu))
		वापस PTR_ERR(rcdu);

	rcdu->dev = &pdev->dev;
	rcdu->info = of_device_get_match_data(rcdu->dev);

	platक्रमm_set_drvdata(pdev, rcdu);

	/* I/O resources */
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rcdu->mmio = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(rcdu->mmio))
		वापस PTR_ERR(rcdu->mmio);

	/* DRM/KMS objects */
	ret = rcar_du_modeset_init(rcdu);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"failed to initialize DRM/KMS (%d)\n", ret);
		जाओ error;
	पूर्ण

	rcdu->ddev.irq_enabled = 1;

	/*
	 * Register the DRM device with the core and the connectors with
	 * sysfs.
	 */
	ret = drm_dev_रेजिस्टर(&rcdu->ddev, 0);
	अगर (ret)
		जाओ error;

	DRM_INFO("Device %s probed\n", dev_name(&pdev->dev));

	drm_fbdev_generic_setup(&rcdu->ddev, 32);

	वापस 0;

error:
	drm_kms_helper_poll_fini(&rcdu->ddev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver rcar_du_platक्रमm_driver = अणु
	.probe		= rcar_du_probe,
	.हटाओ		= rcar_du_हटाओ,
	.driver		= अणु
		.name	= "rcar-du",
		.pm	= &rcar_du_pm_ops,
		.of_match_table = rcar_du_of_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rcar_du_init(व्योम)
अणु
	rcar_du_of_init(rcar_du_of_table);

	वापस platक्रमm_driver_रेजिस्टर(&rcar_du_platक्रमm_driver);
पूर्ण
module_init(rcar_du_init);

अटल व्योम __निकास rcar_du_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rcar_du_platक्रमm_driver);
पूर्ण
module_निकास(rcar_du_निकास);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas R-Car Display Unit DRM Driver");
MODULE_LICENSE("GPL");
