<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Panel driver क्रम the ARM Versatile family reference designs from
 * ARM Limited.
 *
 * Author:
 * Linus Walleij <linus.wallei@linaro.org>
 *
 * On the Versatile AB, these panels come mounted on daughterboards
 * named "IB1" or "IB2" (Interface Board 1 & 2 respectively.) They
 * are करोcumented in ARM DUI 0225D Appendix C and D. These daughter
 * boards support TFT display panels.
 *
 * - The IB1 is a passive board where the display connector defines a
 *   few wires क्रम encoding the display type क्रम स्वतःdetection,
 *   suitable display settings can then be looked up from this setting.
 *   The magic bits can be पढ़ो out from the प्रणाली controller.
 *
 * - The IB2 is a more complex board पूर्णांकended क्रम GSM phone development
 *   with some logic and a control रेजिस्टर, which needs to be accessed
 *   and the board display needs to be turned on explicitly.
 *
 * On the Versatile PB, a special CLCD adaptor board is available
 * supporting the same displays as the Versatile AB, plus one more
 * Epson QCIF display.
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

/*
 * This configuration रेजिस्टर in the Versatile and RealView
 * family is unअगरormly present but appears more and more
 * unutilized starting with the RealView series.
 */
#घोषणा SYS_CLCD			0x50

/* The Versatile can detect the connected panel type */
#घोषणा SYS_CLCD_CLCDID_MASK		(BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12))
#घोषणा SYS_CLCD_ID_SANYO_3_8		(0x00 << 8)
#घोषणा SYS_CLCD_ID_SHARP_8_4		(0x01 << 8)
#घोषणा SYS_CLCD_ID_EPSON_2_2		(0x02 << 8)
#घोषणा SYS_CLCD_ID_SANYO_2_5		(0x07 << 8)
#घोषणा SYS_CLCD_ID_VGA			(0x1f << 8)

/* IB2 control रेजिस्टर क्रम the Versatile daughterboard */
#घोषणा IB2_CTRL			0x00
#घोषणा IB2_CTRL_LCD_SD			BIT(1) /* 1 = shut करोwn LCD */
#घोषणा IB2_CTRL_LCD_BL_ON		BIT(0)
#घोषणा IB2_CTRL_LCD_MASK		(BIT(0)|BIT(1))

/**
 * काष्ठा versatile_panel_type - lookup काष्ठा क्रम the supported panels
 */
काष्ठा versatile_panel_type अणु
	/**
	 * @name: the name of this panel
	 */
	स्थिर अक्षर *name;
	/**
	 * @magic: the magic value from the detection रेजिस्टर
	 */
	u32 magic;
	/**
	 * @mode: the DRM display mode क्रम this panel
	 */
	काष्ठा drm_display_mode mode;
	/**
	 * @bus_flags: the DRM bus flags क्रम this panel e.g. inverted घड़ी
	 */
	u32 bus_flags;
	/**
	 * @width_mm: the panel width in mm
	 */
	u32 width_mm;
	/**
	 * @height_mm: the panel height in mm
	 */
	u32 height_mm;
	/**
	 * @ib2: the panel may be connected on an IB2 daughterboard
	 */
	bool ib2;
पूर्ण;

/**
 * काष्ठा versatile_panel - state container क्रम the Versatile panels
 */
काष्ठा versatile_panel अणु
	/**
	 * @dev: the container device
	 */
	काष्ठा device *dev;
	/**
	 * @panel: the DRM panel instance क्रम this device
	 */
	काष्ठा drm_panel panel;
	/**
	 * @panel_type: the Versatile panel type as detected
	 */
	स्थिर काष्ठा versatile_panel_type *panel_type;
	/**
	 * @map: map to the parent syscon where the मुख्य रेजिस्टर reside
	 */
	काष्ठा regmap *map;
	/**
	 * @ib2_map: map to the IB2 syscon, अगर applicable
	 */
	काष्ठा regmap *ib2_map;
पूर्ण;

अटल स्थिर काष्ठा versatile_panel_type versatile_panels[] = अणु
	/*
	 * Sanyo TM38QV67A02A - 3.8 inch QVGA (320x240) Color TFT
	 * found on the Versatile AB IB1 connector or the Versatile
	 * PB adaptor board connector.
	 */
	अणु
		.name = "Sanyo TM38QV67A02A",
		.magic = SYS_CLCD_ID_SANYO_3_8,
		.width_mm = 79,
		.height_mm = 54,
		.mode = अणु
			.घड़ी = 10000,
			.hdisplay = 320,
			.hsync_start = 320 + 6,
			.hsync_end = 320 + 6 + 6,
			.htotal = 320 + 6 + 6 + 6,
			.vdisplay = 240,
			.vsync_start = 240 + 5,
			.vsync_end = 240 + 5 + 6,
			.vtotal = 240 + 5 + 6 + 5,
			.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
		पूर्ण,
	पूर्ण,
	/*
	 * Sharp LQ084V1DG21 640x480 VGA Color TFT module
	 * found on the Versatile AB IB1 connector or the Versatile
	 * PB adaptor board connector.
	 */
	अणु
		.name = "Sharp LQ084V1DG21",
		.magic = SYS_CLCD_ID_SHARP_8_4,
		.width_mm = 171,
		.height_mm = 130,
		.mode = अणु
			.घड़ी = 25000,
			.hdisplay = 640,
			.hsync_start = 640 + 24,
			.hsync_end = 640 + 24 + 96,
			.htotal = 640 + 24 + 96 + 24,
			.vdisplay = 480,
			.vsync_start = 480 + 11,
			.vsync_end = 480 + 11 + 2,
			.vtotal = 480 + 11 + 2 + 32,
			.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
		पूर्ण,
	पूर्ण,
	/*
	 * Epson L2F50113T00 - 2.2 inch QCIF 176x220 Color TFT
	 * found on the Versatile PB adaptor board connector.
	 */
	अणु
		.name = "Epson L2F50113T00",
		.magic = SYS_CLCD_ID_EPSON_2_2,
		.width_mm = 34,
		.height_mm = 45,
		.mode = अणु
			.घड़ी = 62500,
			.hdisplay = 176,
			.hsync_start = 176 + 2,
			.hsync_end = 176 + 2 + 3,
			.htotal = 176 + 2 + 3 + 3,
			.vdisplay = 220,
			.vsync_start = 220 + 0,
			.vsync_end = 220 + 0 + 2,
			.vtotal = 220 + 0 + 2 + 1,
			.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,
	पूर्ण,
	/*
	 * Sanyo ALR252RGT 240x320 portrait display found on the
	 * Versatile AB IB2 daughterboard क्रम GSM prototyping.
	 */
	अणु
		.name = "Sanyo ALR252RGT",
		.magic = SYS_CLCD_ID_SANYO_2_5,
		.width_mm = 37,
		.height_mm = 50,
		.mode = अणु
			.घड़ी = 5400,
			.hdisplay = 240,
			.hsync_start = 240 + 10,
			.hsync_end = 240 + 10 + 10,
			.htotal = 240 + 10 + 10 + 20,
			.vdisplay = 320,
			.vsync_start = 320 + 2,
			.vsync_end = 320 + 2 + 2,
			.vtotal = 320 + 2 + 2 + 2,
			.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,
		.ib2 = true,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा versatile_panel *
to_versatile_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा versatile_panel, panel);
पूर्ण

अटल पूर्णांक versatile_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा versatile_panel *vpanel = to_versatile_panel(panel);

	/* If we're on an IB2 daughterboard, turn off display */
	अगर (vpanel->ib2_map) अणु
		dev_dbg(vpanel->dev, "disable IB2 display\n");
		regmap_update_bits(vpanel->ib2_map,
				   IB2_CTRL,
				   IB2_CTRL_LCD_MASK,
				   IB2_CTRL_LCD_SD);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक versatile_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा versatile_panel *vpanel = to_versatile_panel(panel);

	/* If we're on an IB2 daughterboard, turn on display */
	अगर (vpanel->ib2_map) अणु
		dev_dbg(vpanel->dev, "enable IB2 display\n");
		regmap_update_bits(vpanel->ib2_map,
				   IB2_CTRL,
				   IB2_CTRL_LCD_MASK,
				   IB2_CTRL_LCD_BL_ON);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक versatile_panel_get_modes(काष्ठा drm_panel *panel,
				     काष्ठा drm_connector *connector)
अणु
	काष्ठा versatile_panel *vpanel = to_versatile_panel(panel);
	काष्ठा drm_display_mode *mode;

	connector->display_info.width_mm = vpanel->panel_type->width_mm;
	connector->display_info.height_mm = vpanel->panel_type->height_mm;
	connector->display_info.bus_flags = vpanel->panel_type->bus_flags;

	mode = drm_mode_duplicate(connector->dev, &vpanel->panel_type->mode);
	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	mode->width_mm = vpanel->panel_type->width_mm;
	mode->height_mm = vpanel->panel_type->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs versatile_panel_drm_funcs = अणु
	.disable = versatile_panel_disable,
	.enable = versatile_panel_enable,
	.get_modes = versatile_panel_get_modes,
पूर्ण;

अटल पूर्णांक versatile_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा versatile_panel *vpanel;
	काष्ठा device *parent;
	काष्ठा regmap *map;
	पूर्णांक ret;
	u32 val;
	पूर्णांक i;

	parent = dev->parent;
	अगर (!parent) अणु
		dev_err(dev, "no parent for versatile panel\n");
		वापस -ENODEV;
	पूर्ण
	map = syscon_node_to_regmap(parent->of_node);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "no regmap for versatile panel parent\n");
		वापस PTR_ERR(map);
	पूर्ण

	vpanel = devm_kzalloc(dev, माप(*vpanel), GFP_KERNEL);
	अगर (!vpanel)
		वापस -ENOMEM;

	ret = regmap_पढ़ो(map, SYS_CLCD, &val);
	अगर (ret) अणु
		dev_err(dev, "cannot access syscon regs\n");
		वापस ret;
	पूर्ण

	val &= SYS_CLCD_CLCDID_MASK;

	क्रम (i = 0; i < ARRAY_SIZE(versatile_panels); i++) अणु
		स्थिर काष्ठा versatile_panel_type *pt;

		pt = &versatile_panels[i];
		अगर (pt->magic == val) अणु
			vpanel->panel_type = pt;
			अवरोध;
		पूर्ण
	पूर्ण

	/* No panel detected or VGA, let's leave this show */
	अगर (i == ARRAY_SIZE(versatile_panels)) अणु
		dev_info(dev, "no panel detected\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(dev, "detected: %s\n", vpanel->panel_type->name);
	vpanel->dev = dev;
	vpanel->map = map;

	/* Check अगर the panel is mounted on an IB2 daughterboard */
	अगर (vpanel->panel_type->ib2) अणु
		vpanel->ib2_map = syscon_regmap_lookup_by_compatible(
			"arm,versatile-ib2-syscon");
		अगर (IS_ERR(vpanel->ib2_map))
			vpanel->ib2_map = शून्य;
		अन्यथा
			dev_info(dev, "panel mounted on IB2 daughterboard\n");
	पूर्ण

	drm_panel_init(&vpanel->panel, dev, &versatile_panel_drm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&vpanel->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id versatile_panel_match[] = अणु
	अणु .compatible = "arm,versatile-tft-panel", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, versatile_panel_match);

अटल काष्ठा platक्रमm_driver versatile_panel_driver = अणु
	.probe		= versatile_panel_probe,
	.driver		= अणु
		.name	= "versatile-tft-panel",
		.of_match_table = versatile_panel_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(versatile_panel_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("ARM Versatile panel driver");
MODULE_LICENSE("GPL v2");
