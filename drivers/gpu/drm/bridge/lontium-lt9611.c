<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Copyright (c) 2019-2020. Linaro Limited.
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/hdmi-codec.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा EDID_SEG_SIZE	256
#घोषणा EDID_LEN	32
#घोषणा EDID_LOOP	8
#घोषणा KEY_DDC_ACCS_DONE 0x02
#घोषणा DDC_NO_ACK	0x50

#घोषणा LT9611_4LANES	0

काष्ठा lt9611 अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;

	काष्ठा regmap *regmap;

	काष्ठा device_node *dsi0_node;
	काष्ठा device_node *dsi1_node;
	काष्ठा mipi_dsi_device *dsi0;
	काष्ठा mipi_dsi_device *dsi1;
	काष्ठा platक्रमm_device *audio_pdev;

	bool ac_mode;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *enable_gpio;

	bool घातer_on;
	bool sleep;

	काष्ठा regulator_bulk_data supplies[2];

	काष्ठा i2c_client *client;

	क्रमागत drm_connector_status status;

	u8 edid_buf[EDID_SEG_SIZE];
	u32 vic;
पूर्ण;

#घोषणा LT9611_PAGE_CONTROL	0xff

अटल स्थिर काष्ठा regmap_range_cfg lt9611_ranges[] = अणु
	अणु
		.name = "register_range",
		.range_min =  0,
		.range_max = 0x85ff,
		.selector_reg = LT9611_PAGE_CONTROL,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 0x100,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lt9611_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xffff,
	.ranges = lt9611_ranges,
	.num_ranges = ARRAY_SIZE(lt9611_ranges),
पूर्ण;

काष्ठा lt9611_mode अणु
	u16 hdisplay;
	u16 vdisplay;
	u8 vrefresh;
	u8 lanes;
	u8 पूर्णांकfs;
पूर्ण;

अटल काष्ठा lt9611_mode lt9611_modes[] = अणु
	अणु 3840, 2160, 30, 4, 2 पूर्ण, /* 3840x2160 24bit 30Hz 4Lane 2ports */
	अणु 1920, 1080, 60, 4, 1 पूर्ण, /* 1080P 24bit 60Hz 4lane 1port */
	अणु 1920, 1080, 30, 3, 1 पूर्ण, /* 1080P 24bit 30Hz 3lane 1port */
	अणु 1920, 1080, 24, 3, 1 पूर्ण,
	अणु 720, 480, 60, 4, 1 पूर्ण,
	अणु 720, 576, 50, 2, 1 पूर्ण,
	अणु 640, 480, 60, 2, 1 पूर्ण,
पूर्ण;

अटल काष्ठा lt9611 *bridge_to_lt9611(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा lt9611, bridge);
पूर्ण

अटल काष्ठा lt9611 *connector_to_lt9611(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा lt9611, connector);
पूर्ण

अटल पूर्णांक lt9611_mipi_input_analog(काष्ठा lt9611 *lt9611)
अणु
	स्थिर काष्ठा reg_sequence reg_cfg[] = अणु
		अणु 0x8106, 0x40 पूर्ण, /* port A rx current */
		अणु 0x810a, 0xfe पूर्ण, /* port A lकरो voltage set */
		अणु 0x810b, 0xbf पूर्ण, /* enable port A lprx */
		अणु 0x8111, 0x40 पूर्ण, /* port B rx current */
		अणु 0x8115, 0xfe पूर्ण, /* port B lकरो voltage set */
		अणु 0x8116, 0xbf पूर्ण, /* enable port B lprx */

		अणु 0x811c, 0x03 पूर्ण, /* PortA clk lane no-LP mode */
		अणु 0x8120, 0x03 पूर्ण, /* PortB clk lane with-LP mode */
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(lt9611->regmap, reg_cfg, ARRAY_SIZE(reg_cfg));
पूर्ण

अटल पूर्णांक lt9611_mipi_input_digital(काष्ठा lt9611 *lt9611,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा reg_sequence reg_cfg[] = अणु
		अणु 0x8300, LT9611_4LANES पूर्ण,
		अणु 0x830a, 0x00 पूर्ण,
		अणु 0x824f, 0x80 पूर्ण,
		अणु 0x8250, 0x10 पूर्ण,
		अणु 0x8302, 0x0a पूर्ण,
		अणु 0x8306, 0x0a पूर्ण,
	पूर्ण;

	अगर (mode->hdisplay == 3840)
		reg_cfg[1].def = 0x03;

	वापस regmap_multi_reg_ग_लिखो(lt9611->regmap, reg_cfg, ARRAY_SIZE(reg_cfg));
पूर्ण

अटल व्योम lt9611_mipi_video_setup(काष्ठा lt9611 *lt9611,
				    स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 h_total, hactive, hsync_len, hfront_porch, hsync_porch;
	u32 v_total, vactive, vsync_len, vfront_porch, vsync_porch;

	h_total = mode->htotal;
	v_total = mode->vtotal;

	hactive = mode->hdisplay;
	hsync_len = mode->hsync_end - mode->hsync_start;
	hfront_porch = mode->hsync_start - mode->hdisplay;
	hsync_porch = hsync_len + mode->htotal - mode->hsync_end;

	vactive = mode->vdisplay;
	vsync_len = mode->vsync_end - mode->vsync_start;
	vfront_porch = mode->vsync_start - mode->vdisplay;
	vsync_porch = vsync_len + mode->vtotal - mode->vsync_end;

	regmap_ग_लिखो(lt9611->regmap, 0x830d, (u8)(v_total / 256));
	regmap_ग_लिखो(lt9611->regmap, 0x830e, (u8)(v_total % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x830f, (u8)(vactive / 256));
	regmap_ग_लिखो(lt9611->regmap, 0x8310, (u8)(vactive % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x8311, (u8)(h_total / 256));
	regmap_ग_लिखो(lt9611->regmap, 0x8312, (u8)(h_total % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x8313, (u8)(hactive / 256));
	regmap_ग_लिखो(lt9611->regmap, 0x8314, (u8)(hactive % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x8315, (u8)(vsync_len % 256));
	regmap_ग_लिखो(lt9611->regmap, 0x8316, (u8)(hsync_len % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x8317, (u8)(vfront_porch % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x8318, (u8)(vsync_porch % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x8319, (u8)(hfront_porch % 256));

	regmap_ग_लिखो(lt9611->regmap, 0x831a, (u8)(hsync_porch / 256));
	regmap_ग_लिखो(lt9611->regmap, 0x831b, (u8)(hsync_porch % 256));
पूर्ण

अटल व्योम lt9611_pcr_setup(काष्ठा lt9611 *lt9611, स्थिर काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा reg_sequence reg_cfg[] = अणु
		अणु 0x830b, 0x01 पूर्ण,
		अणु 0x830c, 0x10 पूर्ण,
		अणु 0x8348, 0x00 पूर्ण,
		अणु 0x8349, 0x81 पूर्ण,

		/* stage 1 */
		अणु 0x8321, 0x4a पूर्ण,
		अणु 0x8324, 0x71 पूर्ण,
		अणु 0x8325, 0x30 पूर्ण,
		अणु 0x832a, 0x01 पूर्ण,

		/* stage 2 */
		अणु 0x834a, 0x40 पूर्ण,
		अणु 0x831d, 0x10 पूर्ण,

		/* MK limit */
		अणु 0x832d, 0x38 पूर्ण,
		अणु 0x8331, 0x08 पूर्ण,
	पूर्ण;
	स्थिर काष्ठा reg_sequence reg_cfg2[] = अणु
		अणु 0x830b, 0x03 पूर्ण,
		अणु 0x830c, 0xd0 पूर्ण,
		अणु 0x8348, 0x03 पूर्ण,
		अणु 0x8349, 0xe0 पूर्ण,
		अणु 0x8324, 0x72 पूर्ण,
		अणु 0x8325, 0x00 पूर्ण,
		अणु 0x832a, 0x01 पूर्ण,
		अणु 0x834a, 0x10 पूर्ण,
		अणु 0x831d, 0x10 पूर्ण,
		अणु 0x8326, 0x37 पूर्ण,
	पूर्ण;

	regmap_multi_reg_ग_लिखो(lt9611->regmap, reg_cfg, ARRAY_SIZE(reg_cfg));

	चयन (mode->hdisplay) अणु
	हाल 640:
		regmap_ग_लिखो(lt9611->regmap, 0x8326, 0x14);
		अवरोध;
	हाल 1920:
		regmap_ग_लिखो(lt9611->regmap, 0x8326, 0x37);
		अवरोध;
	हाल 3840:
		regmap_multi_reg_ग_लिखो(lt9611->regmap, reg_cfg2, ARRAY_SIZE(reg_cfg2));
		अवरोध;
	पूर्ण

	/* pcr rst */
	regmap_ग_लिखो(lt9611->regmap, 0x8011, 0x5a);
	regmap_ग_लिखो(lt9611->regmap, 0x8011, 0xfa);
पूर्ण

अटल पूर्णांक lt9611_pll_setup(काष्ठा lt9611 *lt9611, स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक pclk = mode->घड़ी;
	स्थिर काष्ठा reg_sequence reg_cfg[] = अणु
		/* txpll init */
		अणु 0x8123, 0x40 पूर्ण,
		अणु 0x8124, 0x64 पूर्ण,
		अणु 0x8125, 0x80 पूर्ण,
		अणु 0x8126, 0x55 पूर्ण,
		अणु 0x812c, 0x37 पूर्ण,
		अणु 0x812f, 0x01 पूर्ण,
		अणु 0x8126, 0x55 पूर्ण,
		अणु 0x8127, 0x66 पूर्ण,
		अणु 0x8128, 0x88 पूर्ण,
	पूर्ण;

	regmap_multi_reg_ग_लिखो(lt9611->regmap, reg_cfg, ARRAY_SIZE(reg_cfg));

	अगर (pclk > 150000)
		regmap_ग_लिखो(lt9611->regmap, 0x812d, 0x88);
	अन्यथा अगर (pclk > 70000)
		regmap_ग_लिखो(lt9611->regmap, 0x812d, 0x99);
	अन्यथा
		regmap_ग_लिखो(lt9611->regmap, 0x812d, 0xaa);

	/*
	 * first भागide pclk by 2 first
	 *  - ग_लिखो भागide by 64k to 19:16 bits which means shअगरt by 17
	 *  - ग_लिखो भागide by 256 to 15:8 bits which means shअगरt by 9
	 *  - ग_लिखो reमुख्यder to 7:0 bits, which means shअगरt by 1
	 */
	regmap_ग_लिखो(lt9611->regmap, 0x82e3, pclk >> 17); /* pclk[19:16] */
	regmap_ग_लिखो(lt9611->regmap, 0x82e4, pclk >> 9);  /* pclk[15:8]  */
	regmap_ग_लिखो(lt9611->regmap, 0x82e5, pclk >> 1);  /* pclk[7:0]   */

	regmap_ग_लिखो(lt9611->regmap, 0x82de, 0x20);
	regmap_ग_लिखो(lt9611->regmap, 0x82de, 0xe0);

	regmap_ग_लिखो(lt9611->regmap, 0x8016, 0xf1);
	regmap_ग_लिखो(lt9611->regmap, 0x8016, 0xf3);

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611_पढ़ो_video_check(काष्ठा lt9611 *lt9611, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक temp, temp2;
	पूर्णांक ret;

	ret = regmap_पढ़ो(lt9611->regmap, reg, &temp);
	अगर (ret)
		वापस ret;
	temp <<= 8;
	ret = regmap_पढ़ो(lt9611->regmap, reg + 1, &temp2);
	अगर (ret)
		वापस ret;

	वापस (temp + temp2);
पूर्ण

अटल पूर्णांक lt9611_video_check(काष्ठा lt9611 *lt9611)
अणु
	u32 v_total, vactive, hactive_a, hactive_b, h_total_sysclk;
	पूर्णांक temp;

	/* top module video check */

	/* vactive */
	temp = lt9611_पढ़ो_video_check(lt9611, 0x8282);
	अगर (temp < 0)
		जाओ end;
	vactive = temp;

	/* v_total */
	temp = lt9611_पढ़ो_video_check(lt9611, 0x826c);
	अगर (temp < 0)
		जाओ end;
	v_total = temp;

	/* h_total_sysclk */
	temp = lt9611_पढ़ो_video_check(lt9611, 0x8286);
	अगर (temp < 0)
		जाओ end;
	h_total_sysclk = temp;

	/* hactive_a */
	temp = lt9611_पढ़ो_video_check(lt9611, 0x8382);
	अगर (temp < 0)
		जाओ end;
	hactive_a = temp / 3;

	/* hactive_b */
	temp = lt9611_पढ़ो_video_check(lt9611, 0x8386);
	अगर (temp < 0)
		जाओ end;
	hactive_b = temp / 3;

	dev_info(lt9611->dev,
		 "video check: hactive_a=%d, hactive_b=%d, vactive=%d, v_total=%d, h_total_sysclk=%d\n",
		 hactive_a, hactive_b, vactive, v_total, h_total_sysclk);

	वापस 0;

end:
	dev_err(lt9611->dev, "read video check error\n");
	वापस temp;
पूर्ण

अटल व्योम lt9611_hdmi_tx_digital(काष्ठा lt9611 *lt9611)
अणु
	regmap_ग_लिखो(lt9611->regmap, 0x8443, 0x46 - lt9611->vic);
	regmap_ग_लिखो(lt9611->regmap, 0x8447, lt9611->vic);
	regmap_ग_लिखो(lt9611->regmap, 0x843d, 0x0a); /* UD1 infoframe */

	regmap_ग_लिखो(lt9611->regmap, 0x82d6, 0x8c);
	regmap_ग_लिखो(lt9611->regmap, 0x82d7, 0x04);
पूर्ण

अटल व्योम lt9611_hdmi_tx_phy(काष्ठा lt9611 *lt9611)
अणु
	काष्ठा reg_sequence reg_cfg[] = अणु
		अणु 0x8130, 0x6a पूर्ण,
		अणु 0x8131, 0x44 पूर्ण, /* HDMI DC mode */
		अणु 0x8132, 0x4a पूर्ण,
		अणु 0x8133, 0x0b पूर्ण,
		अणु 0x8134, 0x00 पूर्ण,
		अणु 0x8135, 0x00 पूर्ण,
		अणु 0x8136, 0x00 पूर्ण,
		अणु 0x8137, 0x44 पूर्ण,
		अणु 0x813f, 0x0f पूर्ण,
		अणु 0x8140, 0xa0 पूर्ण,
		अणु 0x8141, 0xa0 पूर्ण,
		अणु 0x8142, 0xa0 पूर्ण,
		अणु 0x8143, 0xa0 पूर्ण,
		अणु 0x8144, 0x0a पूर्ण,
	पूर्ण;

	/* HDMI AC mode */
	अगर (lt9611->ac_mode)
		reg_cfg[2].def = 0x73;

	regmap_multi_reg_ग_लिखो(lt9611->regmap, reg_cfg, ARRAY_SIZE(reg_cfg));
पूर्ण

अटल irqवापस_t lt9611_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lt9611 *lt9611 = dev_id;
	अचिन्हित पूर्णांक irq_flag0 = 0;
	अचिन्हित पूर्णांक irq_flag3 = 0;

	regmap_पढ़ो(lt9611->regmap, 0x820f, &irq_flag3);
	regmap_पढ़ो(lt9611->regmap, 0x820c, &irq_flag0);

	/* hpd changed low */
	अगर (irq_flag3 & 0x80) अणु
		dev_info(lt9611->dev, "hdmi cable disconnected\n");

		regmap_ग_लिखो(lt9611->regmap, 0x8207, 0xbf);
		regmap_ग_लिखो(lt9611->regmap, 0x8207, 0x3f);
	पूर्ण

	/* hpd changed high */
	अगर (irq_flag3 & 0x40) अणु
		dev_info(lt9611->dev, "hdmi cable connected\n");

		regmap_ग_लिखो(lt9611->regmap, 0x8207, 0x7f);
		regmap_ग_लिखो(lt9611->regmap, 0x8207, 0x3f);
	पूर्ण

	अगर (irq_flag3 & 0xc0 && lt9611->bridge.dev)
		drm_kms_helper_hotplug_event(lt9611->bridge.dev);

	/* video input changed */
	अगर (irq_flag0 & 0x01) अणु
		dev_info(lt9611->dev, "video input changed\n");
		regmap_ग_लिखो(lt9611->regmap, 0x829e, 0xff);
		regmap_ग_लिखो(lt9611->regmap, 0x829e, 0xf7);
		regmap_ग_लिखो(lt9611->regmap, 0x8204, 0xff);
		regmap_ग_लिखो(lt9611->regmap, 0x8204, 0xfe);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम lt9611_enable_hpd_पूर्णांकerrupts(काष्ठा lt9611 *lt9611)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(lt9611->regmap, 0x8203, &val);

	val &= ~0xc0;
	regmap_ग_लिखो(lt9611->regmap, 0x8203, val);
	regmap_ग_लिखो(lt9611->regmap, 0x8207, 0xff); /* clear */
	regmap_ग_लिखो(lt9611->regmap, 0x8207, 0x3f);
पूर्ण

अटल व्योम lt9611_sleep_setup(काष्ठा lt9611 *lt9611)
अणु
	स्थिर काष्ठा reg_sequence sleep_setup[] = अणु
		अणु 0x8024, 0x76 पूर्ण,
		अणु 0x8023, 0x01 पूर्ण,
		अणु 0x8157, 0x03 पूर्ण, /* set addr pin as output */
		अणु 0x8149, 0x0b पूर्ण,
		अणु 0x8151, 0x30 पूर्ण, /* disable IRQ */
		अणु 0x8102, 0x48 पूर्ण, /* MIPI Rx घातer करोwn */
		अणु 0x8123, 0x80 पूर्ण,
		अणु 0x8130, 0x00 पूर्ण,
		अणु 0x8100, 0x01 पूर्ण, /* bandgap घातer करोwn */
		अणु 0x8101, 0x00 पूर्ण, /* प्रणाली clk घातer करोwn */
	पूर्ण;

	regmap_multi_reg_ग_लिखो(lt9611->regmap,
			       sleep_setup, ARRAY_SIZE(sleep_setup));
	lt9611->sleep = true;
पूर्ण

अटल पूर्णांक lt9611_घातer_on(काष्ठा lt9611 *lt9611)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा reg_sequence seq[] = अणु
		/* LT9611_System_Init */
		अणु 0x8101, 0x18 पूर्ण, /* sel xtal घड़ी */

		/* समयr क्रम frequency meter */
		अणु 0x821b, 0x69 पूर्ण, /* समयr 2 */
		अणु 0x821c, 0x78 पूर्ण,
		अणु 0x82cb, 0x69 पूर्ण, /* समयr 1 */
		अणु 0x82cc, 0x78 पूर्ण,

		/* irq init */
		अणु 0x8251, 0x01 पूर्ण,
		अणु 0x8258, 0x0a पूर्ण, /* hpd irq */
		अणु 0x8259, 0x80 पूर्ण, /* hpd debounce width */
		अणु 0x829e, 0xf7 पूर्ण, /* video check irq */

		/* घातer consumption क्रम work */
		अणु 0x8004, 0xf0 पूर्ण,
		अणु 0x8006, 0xf0 पूर्ण,
		अणु 0x800a, 0x80 पूर्ण,
		अणु 0x800b, 0x40 पूर्ण,
		अणु 0x800d, 0xef पूर्ण,
		अणु 0x8011, 0xfa पूर्ण,
	पूर्ण;

	अगर (lt9611->घातer_on)
		वापस 0;

	ret = regmap_multi_reg_ग_लिखो(lt9611->regmap, seq, ARRAY_SIZE(seq));
	अगर (!ret)
		lt9611->घातer_on = true;

	वापस ret;
पूर्ण

अटल पूर्णांक lt9611_घातer_off(काष्ठा lt9611 *lt9611)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(lt9611->regmap, 0x8130, 0x6a);
	अगर (!ret)
		lt9611->घातer_on = false;

	वापस ret;
पूर्ण

अटल व्योम lt9611_reset(काष्ठा lt9611 *lt9611)
अणु
	gpiod_set_value_cansleep(lt9611->reset_gpio, 1);
	msleep(20);

	gpiod_set_value_cansleep(lt9611->reset_gpio, 0);
	msleep(20);

	gpiod_set_value_cansleep(lt9611->reset_gpio, 1);
	msleep(100);
पूर्ण

अटल व्योम lt9611_निश्चित_5v(काष्ठा lt9611 *lt9611)
अणु
	अगर (!lt9611->enable_gpio)
		वापस;

	gpiod_set_value_cansleep(lt9611->enable_gpio, 1);
	msleep(20);
पूर्ण

अटल पूर्णांक lt9611_regulator_init(काष्ठा lt9611 *lt9611)
अणु
	पूर्णांक ret;

	lt9611->supplies[0].supply = "vdd";
	lt9611->supplies[1].supply = "vcc";

	ret = devm_regulator_bulk_get(lt9611->dev, 2, lt9611->supplies);
	अगर (ret < 0)
		वापस ret;

	वापस regulator_set_load(lt9611->supplies[0].consumer, 300000);
पूर्ण

अटल पूर्णांक lt9611_regulator_enable(काष्ठा lt9611 *lt9611)
अणु
	पूर्णांक ret;

	ret = regulator_enable(lt9611->supplies[0].consumer);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 10000);

	ret = regulator_enable(lt9611->supplies[1].consumer);
	अगर (ret < 0) अणु
		regulator_disable(lt9611->supplies[0].consumer);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lt9611_mode *lt9611_find_mode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lt9611_modes); i++) अणु
		अगर (lt9611_modes[i].hdisplay == mode->hdisplay &&
		    lt9611_modes[i].vdisplay == mode->vdisplay &&
		    lt9611_modes[i].vrefresh == drm_mode_vrefresh(mode)) अणु
			वापस &lt9611_modes[i];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* connector funcs */
अटल क्रमागत drm_connector_status
lt9611_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा lt9611 *lt9611 = connector_to_lt9611(connector);
	अचिन्हित पूर्णांक reg_val = 0;
	पूर्णांक connected = 0;

	regmap_पढ़ो(lt9611->regmap, 0x825e, &reg_val);
	connected  = (reg_val & BIT(2));

	lt9611->status = connected ?  connector_status_connected :
				connector_status_disconnected;

	वापस lt9611->status;
पूर्ण

अटल पूर्णांक lt9611_पढ़ो_edid(काष्ठा lt9611 *lt9611)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret = 0;
	पूर्णांक i, j;

	/* स_रखो to clear old buffer, अगर any */
	स_रखो(lt9611->edid_buf, 0, माप(lt9611->edid_buf));

	regmap_ग_लिखो(lt9611->regmap, 0x8503, 0xc9);

	/* 0xA0 is EDID device address */
	regmap_ग_लिखो(lt9611->regmap, 0x8504, 0xa0);
	/* 0x00 is EDID offset address */
	regmap_ग_लिखो(lt9611->regmap, 0x8505, 0x00);

	/* length क्रम पढ़ो */
	regmap_ग_लिखो(lt9611->regmap, 0x8506, EDID_LEN);
	regmap_ग_लिखो(lt9611->regmap, 0x8514, 0x7f);

	क्रम (i = 0; i < EDID_LOOP; i++) अणु
		/* offset address */
		regmap_ग_लिखो(lt9611->regmap, 0x8505, i * EDID_LEN);
		regmap_ग_लिखो(lt9611->regmap, 0x8507, 0x36);
		regmap_ग_लिखो(lt9611->regmap, 0x8507, 0x31);
		regmap_ग_लिखो(lt9611->regmap, 0x8507, 0x37);
		usleep_range(5000, 10000);

		regmap_पढ़ो(lt9611->regmap, 0x8540, &temp);

		अगर (temp & KEY_DDC_ACCS_DONE) अणु
			क्रम (j = 0; j < EDID_LEN; j++) अणु
				regmap_पढ़ो(lt9611->regmap, 0x8583, &temp);
				lt9611->edid_buf[i * EDID_LEN + j] = temp;
			पूर्ण

		पूर्ण अन्यथा अगर (temp & DDC_NO_ACK) अणु /* DDC No Ack or Abitration lost */
			dev_err(lt9611->dev, "read edid failed: no ack\n");
			ret = -EIO;
			जाओ end;

		पूर्ण अन्यथा अणु
			dev_err(lt9611->dev, "read edid failed: access not done\n");
			ret = -EIO;
			जाओ end;
		पूर्ण
	पूर्ण

end:
	regmap_ग_लिखो(lt9611->regmap, 0x8507, 0x1f);
	वापस ret;
पूर्ण

अटल पूर्णांक
lt9611_get_edid_block(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block, माप_प्रकार len)
अणु
	काष्ठा lt9611 *lt9611 = data;
	पूर्णांक ret;

	अगर (len > 128)
		वापस -EINVAL;

	/* supports up to 1 extension block */
	/* TODO: add support क्रम more extension blocks */
	अगर (block > 1)
		वापस -EINVAL;

	अगर (block == 0) अणु
		ret = lt9611_पढ़ो_edid(lt9611);
		अगर (ret) अणु
			dev_err(lt9611->dev, "edid read failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	block %= 2;
	स_नकल(buf, lt9611->edid_buf + (block * 128), len);

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा lt9611 *lt9611 = connector_to_lt9611(connector);
	अचिन्हित पूर्णांक count;
	काष्ठा edid *edid;

	lt9611_घातer_on(lt9611);
	edid = drm_करो_get_edid(connector, lt9611_get_edid_block, lt9611);
	drm_connector_update_edid_property(connector, edid);
	count = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस count;
पूर्ण

अटल क्रमागत drm_mode_status
lt9611_connector_mode_valid(काष्ठा drm_connector *connector,
			    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा lt9611_mode *lt9611_mode = lt9611_find_mode(mode);

	वापस lt9611_mode ? MODE_OK : MODE_BAD;
पूर्ण

/* bridge funcs */
अटल व्योम lt9611_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	अगर (lt9611_घातer_on(lt9611)) अणु
		dev_err(lt9611->dev, "power on failed\n");
		वापस;
	पूर्ण

	lt9611_mipi_input_analog(lt9611);
	lt9611_hdmi_tx_digital(lt9611);
	lt9611_hdmi_tx_phy(lt9611);

	msleep(500);

	lt9611_video_check(lt9611);

	/* Enable HDMI output */
	regmap_ग_लिखो(lt9611->regmap, 0x8130, 0xea);
पूर्ण

अटल व्योम lt9611_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);
	पूर्णांक ret;

	/* Disable HDMI output */
	ret = regmap_ग_लिखो(lt9611->regmap, 0x8130, 0x6a);
	अगर (ret) अणु
		dev_err(lt9611->dev, "video on failed\n");
		वापस;
	पूर्ण

	अगर (lt9611_घातer_off(lt9611)) अणु
		dev_err(lt9611->dev, "power on failed\n");
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा
drm_connector_helper_funcs lt9611_bridge_connector_helper_funcs = अणु
	.get_modes = lt9611_connector_get_modes,
	.mode_valid = lt9611_connector_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs lt9611_bridge_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = lt9611_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल काष्ठा mipi_dsi_device *lt9611_attach_dsi(काष्ठा lt9611 *lt9611,
						 काष्ठा device_node *dsi_node)
अणु
	स्थिर काष्ठा mipi_dsi_device_info info = अणु "lt9611", 0, शून्य पूर्ण;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा mipi_dsi_host *host;
	पूर्णांक ret;

	host = of_find_mipi_dsi_host_by_node(dsi_node);
	अगर (!host) अणु
		dev_err(lt9611->dev, "failed to find dsi host\n");
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		dev_err(lt9611->dev, "failed to create dsi device\n");
		वापस dsi;
	पूर्ण

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			  MIPI_DSI_MODE_VIDEO_HSE;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(lt9611->dev, "failed to attach dsi to host\n");
		mipi_dsi_device_unरेजिस्टर(dsi);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस dsi;
पूर्ण

अटल व्योम lt9611_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	अगर (lt9611->dsi1) अणु
		mipi_dsi_detach(lt9611->dsi1);
		mipi_dsi_device_unरेजिस्टर(lt9611->dsi1);
	पूर्ण

	mipi_dsi_detach(lt9611->dsi0);
	mipi_dsi_device_unरेजिस्टर(lt9611->dsi0);
पूर्ण

अटल पूर्णांक lt9611_connector_init(काष्ठा drm_bridge *bridge, काष्ठा lt9611 *lt9611)
अणु
	पूर्णांक ret;

	ret = drm_connector_init(bridge->dev, &lt9611->connector,
				 &lt9611_bridge_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(&lt9611->connector,
				 &lt9611_bridge_connector_helper_funcs);
	drm_connector_attach_encoder(&lt9611->connector, bridge->encoder);

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611_bridge_attach(काष्ठा drm_bridge *bridge,
				क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);
	पूर्णांक ret;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)) अणु
		ret = lt9611_connector_init(bridge, lt9611);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Attach primary DSI */
	lt9611->dsi0 = lt9611_attach_dsi(lt9611, lt9611->dsi0_node);
	अगर (IS_ERR(lt9611->dsi0))
		वापस PTR_ERR(lt9611->dsi0);

	/* Attach secondary DSI, अगर specअगरied */
	अगर (lt9611->dsi1_node) अणु
		lt9611->dsi1 = lt9611_attach_dsi(lt9611, lt9611->dsi1_node);
		अगर (IS_ERR(lt9611->dsi1)) अणु
			ret = PTR_ERR(lt9611->dsi1);
			जाओ err_unरेजिस्टर_dsi0;
		पूर्ण
	पूर्ण

	वापस 0;

err_unरेजिस्टर_dsi0:
	lt9611_bridge_detach(bridge);
	drm_connector_cleanup(&lt9611->connector);
	mipi_dsi_device_unरेजिस्टर(lt9611->dsi0);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status lt9611_bridge_mode_valid(काष्ठा drm_bridge *bridge,
						     स्थिर काष्ठा drm_display_info *info,
						     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा lt9611_mode *lt9611_mode = lt9611_find_mode(mode);
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	अगर (!lt9611_mode)
		वापस MODE_BAD;
	अन्यथा अगर (lt9611_mode->पूर्णांकfs > 1 && !lt9611->dsi1)
		वापस MODE_PANEL;
	अन्यथा
		वापस MODE_OK;
पूर्ण

अटल व्योम lt9611_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	अगर (!lt9611->sleep)
		वापस;

	lt9611_reset(lt9611);
	regmap_ग_लिखो(lt9611->regmap, 0x80ee, 0x01);

	lt9611->sleep = false;
पूर्ण

अटल व्योम lt9611_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	lt9611_sleep_setup(lt9611);
पूर्ण

अटल व्योम lt9611_bridge_mode_set(काष्ठा drm_bridge *bridge,
				   स्थिर काष्ठा drm_display_mode *mode,
				   स्थिर काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);
	काष्ठा hdmi_avi_infoframe avi_frame;
	पूर्णांक ret;

	lt9611_bridge_pre_enable(bridge);

	lt9611_mipi_input_digital(lt9611, mode);
	lt9611_pll_setup(lt9611, mode);
	lt9611_mipi_video_setup(lt9611, mode);
	lt9611_pcr_setup(lt9611, mode);

	ret = drm_hdmi_avi_infoframe_from_display_mode(&avi_frame,
						       &lt9611->connector,
						       mode);
	अगर (!ret)
		lt9611->vic = avi_frame.video_code;
पूर्ण

अटल क्रमागत drm_connector_status lt9611_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);
	अचिन्हित पूर्णांक reg_val = 0;
	पूर्णांक connected;

	regmap_पढ़ो(lt9611->regmap, 0x825e, &reg_val);
	connected  = reg_val & BIT(2);

	lt9611->status = connected ?  connector_status_connected :
				connector_status_disconnected;

	वापस lt9611->status;
पूर्ण

अटल काष्ठा edid *lt9611_bridge_get_edid(काष्ठा drm_bridge *bridge,
					   काष्ठा drm_connector *connector)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	lt9611_घातer_on(lt9611);
	वापस drm_करो_get_edid(connector, lt9611_get_edid_block, lt9611);
पूर्ण

अटल व्योम lt9611_bridge_hpd_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611 *lt9611 = bridge_to_lt9611(bridge);

	lt9611_enable_hpd_पूर्णांकerrupts(lt9611);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs lt9611_bridge_funcs = अणु
	.attach = lt9611_bridge_attach,
	.detach = lt9611_bridge_detach,
	.mode_valid = lt9611_bridge_mode_valid,
	.enable = lt9611_bridge_enable,
	.disable = lt9611_bridge_disable,
	.post_disable = lt9611_bridge_post_disable,
	.mode_set = lt9611_bridge_mode_set,
	.detect = lt9611_bridge_detect,
	.get_edid = lt9611_bridge_get_edid,
	.hpd_enable = lt9611_bridge_hpd_enable,
पूर्ण;

अटल पूर्णांक lt9611_parse_dt(काष्ठा device *dev,
			   काष्ठा lt9611 *lt9611)
अणु
	lt9611->dsi0_node = of_graph_get_remote_node(dev->of_node, 0, -1);
	अगर (!lt9611->dsi0_node) अणु
		dev_err(lt9611->dev, "failed to get remote node for primary dsi\n");
		वापस -ENODEV;
	पूर्ण

	lt9611->dsi1_node = of_graph_get_remote_node(dev->of_node, 1, -1);

	lt9611->ac_mode = of_property_पढ़ो_bool(dev->of_node, "lt,ac-mode");

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611_gpio_init(काष्ठा lt9611 *lt9611)
अणु
	काष्ठा device *dev = lt9611->dev;

	lt9611->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lt9611->reset_gpio)) अणु
		dev_err(dev, "failed to acquire reset gpio\n");
		वापस PTR_ERR(lt9611->reset_gpio);
	पूर्ण

	lt9611->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(lt9611->enable_gpio)) अणु
		dev_err(dev, "failed to acquire enable gpio\n");
		वापस PTR_ERR(lt9611->enable_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611_पढ़ो_device_rev(काष्ठा lt9611 *lt9611)
अणु
	अचिन्हित पूर्णांक rev;
	पूर्णांक ret;

	regmap_ग_लिखो(lt9611->regmap, 0x80ee, 0x01);
	ret = regmap_पढ़ो(lt9611->regmap, 0x8002, &rev);
	अगर (ret)
		dev_err(lt9611->dev, "failed to read revision: %d\n", ret);
	अन्यथा
		dev_info(lt9611->dev, "LT9611 revision: 0x%x\n", rev);

	वापस ret;
पूर्ण

अटल पूर्णांक lt9611_hdmi_hw_params(काष्ठा device *dev, व्योम *data,
				 काष्ठा hdmi_codec_daअगरmt *fmt,
				 काष्ठा hdmi_codec_params *hparms)
अणु
	काष्ठा lt9611 *lt9611 = data;

	अगर (hparms->sample_rate == 48000)
		regmap_ग_लिखो(lt9611->regmap, 0x840f, 0x2b);
	अन्यथा अगर (hparms->sample_rate == 96000)
		regmap_ग_लिखो(lt9611->regmap, 0x840f, 0xab);
	अन्यथा
		वापस -EINVAL;

	regmap_ग_लिखो(lt9611->regmap, 0x8435, 0x00);
	regmap_ग_लिखो(lt9611->regmap, 0x8436, 0x18);
	regmap_ग_लिखो(lt9611->regmap, 0x8437, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611_audio_startup(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा lt9611 *lt9611 = data;

	regmap_ग_लिखो(lt9611->regmap, 0x82d6, 0x8c);
	regmap_ग_लिखो(lt9611->regmap, 0x82d7, 0x04);

	regmap_ग_लिखो(lt9611->regmap, 0x8406, 0x08);
	regmap_ग_लिखो(lt9611->regmap, 0x8407, 0x10);

	regmap_ग_लिखो(lt9611->regmap, 0x8434, 0xd5);

	वापस 0;
पूर्ण

अटल व्योम lt9611_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा lt9611 *lt9611 = data;

	regmap_ग_लिखो(lt9611->regmap, 0x8406, 0x00);
	regmap_ग_लिखो(lt9611->regmap, 0x8407, 0x00);
पूर्ण

अटल पूर्णांक lt9611_hdmi_i2s_get_dai_id(काष्ठा snd_soc_component *component,
				      काष्ठा device_node *endpoपूर्णांक)
अणु
	काष्ठा of_endpoपूर्णांक of_ep;
	पूर्णांक ret;

	ret = of_graph_parse_endpoपूर्णांक(endpoपूर्णांक, &of_ep);
	अगर (ret < 0)
		वापस ret;

	/*
	 * HDMI sound should be located as reg = <2>
	 * Then, it is sound port 0
	 */
	अगर (of_ep.port == 2)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops lt9611_codec_ops = अणु
	.hw_params	= lt9611_hdmi_hw_params,
	.audio_shutकरोwn = lt9611_audio_shutकरोwn,
	.audio_startup	= lt9611_audio_startup,
	.get_dai_id	= lt9611_hdmi_i2s_get_dai_id,
पूर्ण;

अटल काष्ठा hdmi_codec_pdata codec_data = अणु
	.ops = &lt9611_codec_ops,
	.max_i2s_channels = 8,
	.i2s = 1,
पूर्ण;

अटल पूर्णांक lt9611_audio_init(काष्ठा device *dev, काष्ठा lt9611 *lt9611)
अणु
	codec_data.data = lt9611;
	lt9611->audio_pdev =
		platक्रमm_device_रेजिस्टर_data(dev, HDMI_CODEC_DRV_NAME,
					      PLATFORM_DEVID_AUTO,
					      &codec_data, माप(codec_data));

	वापस PTR_ERR_OR_ZERO(lt9611->audio_pdev);
पूर्ण

अटल व्योम lt9611_audio_निकास(काष्ठा lt9611 *lt9611)
अणु
	अगर (lt9611->audio_pdev) अणु
		platक्रमm_device_unरेजिस्टर(lt9611->audio_pdev);
		lt9611->audio_pdev = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक lt9611_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lt9611 *lt9611;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "device doesn't support I2C\n");
		वापस -ENODEV;
	पूर्ण

	lt9611 = devm_kzalloc(dev, माप(*lt9611), GFP_KERNEL);
	अगर (!lt9611)
		वापस -ENOMEM;

	lt9611->dev = &client->dev;
	lt9611->client = client;
	lt9611->sleep = false;

	lt9611->regmap = devm_regmap_init_i2c(client, &lt9611_regmap_config);
	अगर (IS_ERR(lt9611->regmap)) अणु
		dev_err(lt9611->dev, "regmap i2c init failed\n");
		वापस PTR_ERR(lt9611->regmap);
	पूर्ण

	ret = lt9611_parse_dt(&client->dev, lt9611);
	अगर (ret) अणु
		dev_err(dev, "failed to parse device tree\n");
		वापस ret;
	पूर्ण

	ret = lt9611_gpio_init(lt9611);
	अगर (ret < 0)
		जाओ err_of_put;

	ret = lt9611_regulator_init(lt9611);
	अगर (ret < 0)
		जाओ err_of_put;

	lt9611_निश्चित_5v(lt9611);

	ret = lt9611_regulator_enable(lt9611);
	अगर (ret)
		जाओ err_of_put;

	lt9611_reset(lt9611);

	ret = lt9611_पढ़ो_device_rev(lt9611);
	अगर (ret) अणु
		dev_err(dev, "failed to read chip rev\n");
		जाओ err_disable_regulators;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					lt9611_irq_thपढ़ो_handler,
					IRQF_ONESHOT, "lt9611", lt9611);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		जाओ err_disable_regulators;
	पूर्ण

	i2c_set_clientdata(client, lt9611);

	lt9611->bridge.funcs = &lt9611_bridge_funcs;
	lt9611->bridge.of_node = client->dev.of_node;
	lt9611->bridge.ops = DRM_BRIDGE_OP_DETECT | DRM_BRIDGE_OP_EDID |
			     DRM_BRIDGE_OP_HPD | DRM_BRIDGE_OP_MODES;
	lt9611->bridge.type = DRM_MODE_CONNECTOR_HDMIA;

	drm_bridge_add(&lt9611->bridge);

	lt9611_enable_hpd_पूर्णांकerrupts(lt9611);

	वापस lt9611_audio_init(dev, lt9611);

err_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(lt9611->supplies), lt9611->supplies);

err_of_put:
	of_node_put(lt9611->dsi1_node);
	of_node_put(lt9611->dsi0_node);

	वापस ret;
पूर्ण

अटल पूर्णांक lt9611_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lt9611 *lt9611 = i2c_get_clientdata(client);

	disable_irq(client->irq);
	lt9611_audio_निकास(lt9611);
	drm_bridge_हटाओ(&lt9611->bridge);

	regulator_bulk_disable(ARRAY_SIZE(lt9611->supplies), lt9611->supplies);

	of_node_put(lt9611->dsi1_node);
	of_node_put(lt9611->dsi0_node);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_device_id lt9611_id[] = अणु
	अणु "lontium,lt9611", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id lt9611_match_table[] = अणु
	अणु .compatible = "lontium,lt9611" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lt9611_match_table);

अटल काष्ठा i2c_driver lt9611_driver = अणु
	.driver = अणु
		.name = "lt9611",
		.of_match_table = lt9611_match_table,
	पूर्ण,
	.probe = lt9611_probe,
	.हटाओ = lt9611_हटाओ,
	.id_table = lt9611_id,
पूर्ण;
module_i2c_driver(lt9611_driver);

MODULE_LICENSE("GPL v2");
