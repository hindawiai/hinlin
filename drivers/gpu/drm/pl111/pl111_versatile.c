<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Versatile family (ARM reference designs) handling क्रम the PL11x.
 * This is based on code and know-how in the previous frame buffer
 * driver in drivers/video/fbdev/amba-clcd.c:
 * Copyright (C) 2001 ARM Limited, by David A Rusling
 * Updated to 2.5 by Deep Blue Solutions Ltd.
 * Major contributions and discoveries by Russell King.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/vexpress.h>

#समावेश "pl111_versatile.h"
#समावेश "pl111_drm.h"

अटल काष्ठा regmap *versatile_syscon_map;

/*
 * We detect the dअगरferent syscon types from the compatible strings.
 */
क्रमागत versatile_clcd अणु
	INTEGRATOR_IMPD1,
	INTEGRATOR_CLCD_CM,
	VERSATILE_CLCD,
	REALVIEW_CLCD_EB,
	REALVIEW_CLCD_PB1176,
	REALVIEW_CLCD_PB11MP,
	REALVIEW_CLCD_PBA8,
	REALVIEW_CLCD_PBX,
	VEXPRESS_CLCD_V2M,
पूर्ण;

अटल स्थिर काष्ठा of_device_id versatile_clcd_of_match[] = अणु
	अणु
		.compatible = "arm,core-module-integrator",
		.data = (व्योम *)INTEGRATOR_CLCD_CM,
	पूर्ण,
	अणु
		.compatible = "arm,versatile-sysreg",
		.data = (व्योम *)VERSATILE_CLCD,
	पूर्ण,
	अणु
		.compatible = "arm,realview-eb-syscon",
		.data = (व्योम *)REALVIEW_CLCD_EB,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb1176-syscon",
		.data = (व्योम *)REALVIEW_CLCD_PB1176,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb11mp-syscon",
		.data = (व्योम *)REALVIEW_CLCD_PB11MP,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pba8-syscon",
		.data = (व्योम *)REALVIEW_CLCD_PBA8,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pbx-syscon",
		.data = (व्योम *)REALVIEW_CLCD_PBX,
	पूर्ण,
	अणु
		.compatible = "arm,vexpress-muxfpga",
		.data = (व्योम *)VEXPRESS_CLCD_V2M,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id impd1_clcd_of_match[] = अणु
	अणु
		.compatible = "arm,im-pd1-syscon",
		.data = (व्योम *)INTEGRATOR_IMPD1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*
 * Core module CLCD control on the Integrator/CP, bits
 * 8 thru 19 of the CM_CONTROL रेजिस्टर controls a bunch
 * of CLCD settings.
 */
#घोषणा INTEGRATOR_HDR_CTRL_OFFSET	0x0C
#घोषणा INTEGRATOR_CLCD_LCDBIASEN	BIT(8)
#घोषणा INTEGRATOR_CLCD_LCDBIASUP	BIT(9)
#घोषणा INTEGRATOR_CLCD_LCDBIASDN	BIT(10)
/* Bits 11,12,13 controls the LCD or VGA bridge type */
#घोषणा INTEGRATOR_CLCD_LCDMUX_LCD24	BIT(11)
#घोषणा INTEGRATOR_CLCD_LCDMUX_SHARP	(BIT(11)|BIT(12))
#घोषणा INTEGRATOR_CLCD_LCDMUX_VGA555	BIT(13)
#घोषणा INTEGRATOR_CLCD_LCDMUX_VGA24	(BIT(11)|BIT(12)|BIT(13))
#घोषणा INTEGRATOR_CLCD_LCD0_EN		BIT(14)
#घोषणा INTEGRATOR_CLCD_LCD1_EN		BIT(15)
/* R/L flip on Sharp */
#घोषणा INTEGRATOR_CLCD_LCD_STATIC1	BIT(16)
/* U/D flip on Sharp */
#घोषणा INTEGRATOR_CLCD_LCD_STATIC2	BIT(17)
/* No connection on Sharp */
#घोषणा INTEGRATOR_CLCD_LCD_STATIC	BIT(18)
/* 0 = 24bit VGA, 1 = 18bit VGA */
#घोषणा INTEGRATOR_CLCD_LCD_N24BITEN	BIT(19)

#घोषणा INTEGRATOR_CLCD_MASK		GENMASK(19, 8)

अटल व्योम pl111_पूर्णांकegrator_enable(काष्ठा drm_device *drm, u32 क्रमmat)
अणु
	u32 val;

	dev_info(drm->dev, "enable Integrator CLCD connectors\n");

	/* FIXME: really needed? */
	val = INTEGRATOR_CLCD_LCD_STATIC1 | INTEGRATOR_CLCD_LCD_STATIC2 |
		INTEGRATOR_CLCD_LCD0_EN | INTEGRATOR_CLCD_LCD1_EN;

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_XRGB8888:
		/* 24bit क्रमmats */
		val |= INTEGRATOR_CLCD_LCDMUX_VGA24;
		अवरोध;
	हाल DRM_FORMAT_XBGR1555:
	हाल DRM_FORMAT_XRGB1555:
		/* Pseuकरोcolor, RGB555, BGR555 */
		val |= INTEGRATOR_CLCD_LCDMUX_VGA555;
		अवरोध;
	शेष:
		dev_err(drm->dev, "unhandled format on Integrator 0x%08x\n",
			क्रमmat);
		अवरोध;
	पूर्ण

	regmap_update_bits(versatile_syscon_map,
			   INTEGRATOR_HDR_CTRL_OFFSET,
			   INTEGRATOR_CLCD_MASK,
			   val);
पूर्ण

#घोषणा IMPD1_CTRL_OFFSET	0x18
#घोषणा IMPD1_CTRL_DISP_LCD	(0 << 0)
#घोषणा IMPD1_CTRL_DISP_VGA	(1 << 0)
#घोषणा IMPD1_CTRL_DISP_LCD1	(2 << 0)
#घोषणा IMPD1_CTRL_DISP_ENABLE	(1 << 2)
#घोषणा IMPD1_CTRL_DISP_MASK	(7 << 0)

अटल व्योम pl111_impd1_enable(काष्ठा drm_device *drm, u32 क्रमmat)
अणु
	u32 val;

	dev_info(drm->dev, "enable IM-PD1 CLCD connectors\n");
	val = IMPD1_CTRL_DISP_VGA | IMPD1_CTRL_DISP_ENABLE;

	regmap_update_bits(versatile_syscon_map,
			   IMPD1_CTRL_OFFSET,
			   IMPD1_CTRL_DISP_MASK,
			   val);
पूर्ण

अटल व्योम pl111_impd1_disable(काष्ठा drm_device *drm)
अणु
	dev_info(drm->dev, "disable IM-PD1 CLCD connectors\n");

	regmap_update_bits(versatile_syscon_map,
			   IMPD1_CTRL_OFFSET,
			   IMPD1_CTRL_DISP_MASK,
			   0);
पूर्ण

/*
 * This configuration रेजिस्टर in the Versatile and RealView
 * family is unअगरormly present but appears more and more
 * unutilized starting with the RealView series.
 */
#घोषणा SYS_CLCD			0x50
#घोषणा SYS_CLCD_MODE_MASK		(BIT(0)|BIT(1))
#घोषणा SYS_CLCD_MODE_888		0
#घोषणा SYS_CLCD_MODE_5551		BIT(0)
#घोषणा SYS_CLCD_MODE_565_R_LSB		BIT(1)
#घोषणा SYS_CLCD_MODE_565_B_LSB		(BIT(0)|BIT(1))
#घोषणा SYS_CLCD_CONNECTOR_MASK		(BIT(2)|BIT(3)|BIT(4)|BIT(5))
#घोषणा SYS_CLCD_NLCDIOON		BIT(2)
#घोषणा SYS_CLCD_VDDPOSSWITCH		BIT(3)
#घोषणा SYS_CLCD_PWR3V5SWITCH		BIT(4)
#घोषणा SYS_CLCD_VDDNEGSWITCH		BIT(5)

अटल व्योम pl111_versatile_disable(काष्ठा drm_device *drm)
अणु
	dev_info(drm->dev, "disable Versatile CLCD connectors\n");
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_CONNECTOR_MASK,
			   0);
पूर्ण

अटल व्योम pl111_versatile_enable(काष्ठा drm_device *drm, u32 क्रमmat)
अणु
	u32 val = 0;

	dev_info(drm->dev, "enable Versatile CLCD connectors\n");

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		val |= SYS_CLCD_MODE_888;
		अवरोध;
	हाल DRM_FORMAT_BGR565:
		val |= SYS_CLCD_MODE_565_R_LSB;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		val |= SYS_CLCD_MODE_565_B_LSB;
		अवरोध;
	हाल DRM_FORMAT_ABGR1555:
	हाल DRM_FORMAT_XBGR1555:
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
		val |= SYS_CLCD_MODE_5551;
		अवरोध;
	शेष:
		dev_err(drm->dev, "unhandled format on Versatile 0x%08x\n",
			क्रमmat);
		अवरोध;
	पूर्ण

	/* Set up the MUX */
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_MODE_MASK,
			   val);

	/* Then enable the display */
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_CONNECTOR_MASK,
			   SYS_CLCD_NLCDIOON | SYS_CLCD_PWR3V5SWITCH);
पूर्ण

अटल व्योम pl111_realview_clcd_disable(काष्ठा drm_device *drm)
अणु
	dev_info(drm->dev, "disable RealView CLCD connectors\n");
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_CONNECTOR_MASK,
			   0);
पूर्ण

अटल व्योम pl111_realview_clcd_enable(काष्ठा drm_device *drm, u32 क्रमmat)
अणु
	dev_info(drm->dev, "enable RealView CLCD connectors\n");
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_CONNECTOR_MASK,
			   SYS_CLCD_NLCDIOON | SYS_CLCD_PWR3V5SWITCH);
पूर्ण

/* PL110 pixel क्रमmats क्रम Integrator, vanilla PL110 */
अटल स्थिर u32 pl110_पूर्णांकegrator_pixel_क्रमmats[] = अणु
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
पूर्ण;

/* Extended PL110 pixel क्रमmats क्रम Integrator and Versatile */
अटल स्थिर u32 pl110_versatile_pixel_क्रमmats[] = अणु
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_BGR565, /* Uses बाह्यal PLD */
	DRM_FORMAT_RGB565, /* Uses बाह्यal PLD */
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
पूर्ण;

अटल स्थिर u32 pl111_realview_pixel_क्रमmats[] = अणु
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_XBGR4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB4444,
पूर्ण;

/*
 * The Integrator variant is a PL110 with a bunch of broken, or not
 * yet implemented features
 */
अटल स्थिर काष्ठा pl111_variant_data pl110_पूर्णांकegrator = अणु
	.name = "PL110 Integrator",
	.is_pl110 = true,
	.broken_घड़ीभागider = true,
	.broken_vblank = true,
	.क्रमmats = pl110_पूर्णांकegrator_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl110_पूर्णांकegrator_pixel_क्रमmats),
	.fb_bpp = 16,
पूर्ण;

/*
 * The IM-PD1 variant is a PL110 with a bunch of broken, or not
 * yet implemented features
 */
अटल स्थिर काष्ठा pl111_variant_data pl110_impd1 = अणु
	.name = "PL110 IM-PD1",
	.is_pl110 = true,
	.broken_घड़ीभागider = true,
	.broken_vblank = true,
	.क्रमmats = pl110_पूर्णांकegrator_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl110_पूर्णांकegrator_pixel_क्रमmats),
	.fb_bpp = 16,
पूर्ण;

/*
 * This is the in-between PL110 variant found in the ARM Versatile,
 * supporting RGB565/BGR565
 */
अटल स्थिर काष्ठा pl111_variant_data pl110_versatile = अणु
	.name = "PL110 Versatile",
	.is_pl110 = true,
	.बाह्यal_bgr = true,
	.क्रमmats = pl110_versatile_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl110_versatile_pixel_क्रमmats),
	.fb_bpp = 16,
पूर्ण;

/*
 * RealView PL111 variant, the only real dअगरference from the vanilla
 * PL111 is that we select 16bpp framebuffer by शेष to be able
 * to get 1024x768 without saturating the memory bus.
 */
अटल स्थिर काष्ठा pl111_variant_data pl111_realview = अणु
	.name = "PL111 RealView",
	.क्रमmats = pl111_realview_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl111_realview_pixel_क्रमmats),
	.fb_bpp = 16,
पूर्ण;

/*
 * Versatile Express PL111 variant, again we just push the maximum
 * BPP to 16 to be able to get 1024x768 without saturating the memory
 * bus. The घड़ीभागider also seems broken on the Versatile Express.
 */
अटल स्थिर काष्ठा pl111_variant_data pl111_vexpress = अणु
	.name = "PL111 Versatile Express",
	.क्रमmats = pl111_realview_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl111_realview_pixel_क्रमmats),
	.fb_bpp = 16,
	.broken_घड़ीभागider = true,
पूर्ण;

#घोषणा VEXPRESS_FPGAMUX_MOTHERBOARD		0x00
#घोषणा VEXPRESS_FPGAMUX_DAUGHTERBOARD_1	0x01
#घोषणा VEXPRESS_FPGAMUX_DAUGHTERBOARD_2	0x02

अटल पूर्णांक pl111_vexpress_clcd_init(काष्ठा device *dev, काष्ठा device_node *np,
				    काष्ठा pl111_drm_dev_निजी *priv)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *root;
	काष्ठा device_node *child;
	काष्ठा device_node *ct_clcd = शून्य;
	काष्ठा regmap *map;
	bool has_coretile_clcd = false;
	bool has_coretile_hdlcd = false;
	bool mux_motherboard = true;
	u32 val;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_VEXPRESS_CONFIG))
		वापस -ENODEV;

	/*
	 * Check अगर we have a CLCD or HDLCD on the core tile by checking अगर a
	 * CLCD or HDLCD is available in the root of the device tree.
	 */
	root = of_find_node_by_path("/");
	अगर (!root)
		वापस -EINVAL;

	क्रम_each_available_child_of_node(root, child) अणु
		अगर (of_device_is_compatible(child, "arm,pl111")) अणु
			has_coretile_clcd = true;
			ct_clcd = child;
			अवरोध;
		पूर्ण
		अगर (of_device_is_compatible(child, "arm,hdlcd")) अणु
			has_coretile_hdlcd = true;
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(root);

	/*
	 * If there is a coretile HDLCD and it has a driver,
	 * करो not mux the CLCD on the motherboard to the DVI.
	 */
	अगर (has_coretile_hdlcd && IS_ENABLED(CONFIG_DRM_HDLCD))
		mux_motherboard = false;

	/*
	 * On the Vexpress CA9 we let the CLCD on the coretile
	 * take precedence, so also in this हाल करो not mux the
	 * motherboard to the DVI.
	 */
	अगर (has_coretile_clcd)
		mux_motherboard = false;

	अगर (mux_motherboard) अणु
		dev_info(dev, "DVI muxed to motherboard CLCD\n");
		val = VEXPRESS_FPGAMUX_MOTHERBOARD;
	पूर्ण अन्यथा अगर (ct_clcd == dev->of_node) अणु
		dev_info(dev,
			 "DVI muxed to daughterboard 1 (core tile) CLCD\n");
		val = VEXPRESS_FPGAMUX_DAUGHTERBOARD_1;
	पूर्ण अन्यथा अणु
		dev_info(dev, "core tile graphics present\n");
		dev_info(dev, "this device will be deactivated\n");
		वापस -ENODEV;
	पूर्ण

	/* Call पूर्णांकo deep Vexpress configuration API */
	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		dev_err(dev, "can't find the sysreg device, deferring\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	map = devm_regmap_init_vexpress_config(&pdev->dev);
	अगर (IS_ERR(map)) अणु
		platक्रमm_device_put(pdev);
		वापस PTR_ERR(map);
	पूर्ण

	ret = regmap_ग_लिखो(map, 0, val);
	platक्रमm_device_put(pdev);
	अगर (ret) अणु
		dev_err(dev, "error setting DVI muxmode\n");
		वापस -ENODEV;
	पूर्ण

	priv->variant = &pl111_vexpress;
	dev_info(dev, "initializing Versatile Express PL111\n");

	वापस 0;
पूर्ण

पूर्णांक pl111_versatile_init(काष्ठा device *dev, काष्ठा pl111_drm_dev_निजी *priv)
अणु
	स्थिर काष्ठा of_device_id *clcd_id;
	क्रमागत versatile_clcd versatile_clcd_type;
	काष्ठा device_node *np;
	काष्ठा regmap *map;

	np = of_find_matching_node_and_match(शून्य, versatile_clcd_of_match,
					     &clcd_id);
	अगर (!np) अणु
		/* Non-ARM reference designs, just bail out */
		वापस 0;
	पूर्ण

	versatile_clcd_type = (क्रमागत versatile_clcd)clcd_id->data;

	/* Versatile Express special handling */
	अगर (versatile_clcd_type == VEXPRESS_CLCD_V2M) अणु
		पूर्णांक ret = pl111_vexpress_clcd_init(dev, np, priv);
		of_node_put(np);
		अगर (ret)
			dev_err(dev, "Versatile Express init failed - %d", ret);
		वापस ret;
	पूर्ण

	/*
	 * On the Integrator, check अगर we should use the IM-PD1 instead,
	 * अगर we find it, it will take precedence. This is on the Integrator/AP
	 * which only has this option क्रम PL110 graphics.
	 */
	 अगर (versatile_clcd_type == INTEGRATOR_CLCD_CM) अणु
		np = of_find_matching_node_and_match(शून्य, impd1_clcd_of_match,
						     &clcd_id);
		अगर (np)
			versatile_clcd_type = (क्रमागत versatile_clcd)clcd_id->data;
	पूर्ण

	map = syscon_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "no Versatile syscon regmap\n");
		वापस PTR_ERR(map);
	पूर्ण

	चयन (versatile_clcd_type) अणु
	हाल INTEGRATOR_CLCD_CM:
		versatile_syscon_map = map;
		priv->variant = &pl110_पूर्णांकegrator;
		priv->variant_display_enable = pl111_पूर्णांकegrator_enable;
		dev_info(dev, "set up callbacks for Integrator PL110\n");
		अवरोध;
	हाल INTEGRATOR_IMPD1:
		versatile_syscon_map = map;
		priv->variant = &pl110_impd1;
		priv->variant_display_enable = pl111_impd1_enable;
		priv->variant_display_disable = pl111_impd1_disable;
		dev_info(dev, "set up callbacks for IM-PD1 PL110\n");
		अवरोध;
	हाल VERSATILE_CLCD:
		versatile_syscon_map = map;
		/* This can करो RGB565 with बाह्यal PLD */
		priv->variant = &pl110_versatile;
		priv->variant_display_enable = pl111_versatile_enable;
		priv->variant_display_disable = pl111_versatile_disable;
		/*
		 * The Versatile has a variant halfway between PL110
		 * and PL111 where these two रेजिस्टरs have alपढ़ोy been
		 * swapped.
		 */
		priv->ienb = CLCD_PL111_IENB;
		priv->ctrl = CLCD_PL111_CNTL;
		dev_info(dev, "set up callbacks for Versatile PL110\n");
		अवरोध;
	हाल REALVIEW_CLCD_EB:
	हाल REALVIEW_CLCD_PB1176:
	हाल REALVIEW_CLCD_PB11MP:
	हाल REALVIEW_CLCD_PBA8:
	हाल REALVIEW_CLCD_PBX:
		versatile_syscon_map = map;
		priv->variant = &pl111_realview;
		priv->variant_display_enable = pl111_realview_clcd_enable;
		priv->variant_display_disable = pl111_realview_clcd_disable;
		dev_info(dev, "set up callbacks for RealView PL111\n");
		अवरोध;
	शेष:
		dev_info(dev, "unknown Versatile system controller\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pl111_versatile_init);
