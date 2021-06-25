<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Broadcom Limited
 */

/**
 * DOC: VC4 DPI module
 *
 * The VC4 DPI hardware supports MIPI DPI type 4 and Nokia ViSSI
 * संकेतs.  On BCM2835, these can be routed out to GPIO0-27 with the
 * ALT2 function.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा DPI_C			0x00
# define DPI_OUTPUT_ENABLE_MODE		BIT(16)

/* The order field takes the incoming 24 bit RGB from the pixel valve
 * and shuffles the 3 channels.
 */
# define DPI_ORDER_MASK			VC4_MASK(15, 14)
# define DPI_ORDER_SHIFT		14
# define DPI_ORDER_RGB			0
# define DPI_ORDER_BGR			1
# define DPI_ORDER_GRB			2
# define DPI_ORDER_BRG			3

/* The क्रमmat field takes the ORDER-shuffled pixel valve data and
 * क्रमmats it onto the output lines.
 */
# define DPI_FORMAT_MASK		VC4_MASK(13, 11)
# define DPI_FORMAT_SHIFT		11
/* This define is named in the hardware, but actually just outमाला_दो 0. */
# define DPI_FORMAT_9BIT_666_RGB	0
/* Outमाला_दो 00000000rrrrrggggggbbbbb */
# define DPI_FORMAT_16BIT_565_RGB_1	1
/* Outमाला_दो 000rrrrr00gggggg000bbbbb */
# define DPI_FORMAT_16BIT_565_RGB_2	2
/* Outमाला_दो 00rrrrr000gggggg00bbbbb0 */
# define DPI_FORMAT_16BIT_565_RGB_3	3
/* Outमाला_दो 000000rrrrrrggggggbbbbbb */
# define DPI_FORMAT_18BIT_666_RGB_1	4
/* Outमाला_दो 00rrrrrr00gggggg00bbbbbb */
# define DPI_FORMAT_18BIT_666_RGB_2	5
/* Outमाला_दो rrrrrrrrggggggggbbbbbbbb */
# define DPI_FORMAT_24BIT_888_RGB	6

/* Reverses the polarity of the corresponding संकेत */
# define DPI_PIXEL_CLK_INVERT		BIT(10)
# define DPI_HSYNC_INVERT		BIT(9)
# define DPI_VSYNC_INVERT		BIT(8)
# define DPI_OUTPUT_ENABLE_INVERT	BIT(7)

/* Outमाला_दो the संकेत the falling घड़ी edge instead of rising. */
# define DPI_HSYNC_NEGATE		BIT(6)
# define DPI_VSYNC_NEGATE		BIT(5)
# define DPI_OUTPUT_ENABLE_NEGATE	BIT(4)

/* Disables the संकेत */
# define DPI_HSYNC_DISABLE		BIT(3)
# define DPI_VSYNC_DISABLE		BIT(2)
# define DPI_OUTPUT_ENABLE_DISABLE	BIT(1)

/* Power gate to the device, full reset at 0 -> 1 transition */
# define DPI_ENABLE			BIT(0)

/* All other रेजिस्टरs besides DPI_C वापस the ID */
#घोषणा DPI_ID			0x04
# define DPI_ID_VALUE		0x00647069

/* General DPI hardware state. */
काष्ठा vc4_dpi अणु
	काष्ठा platक्रमm_device *pdev;

	काष्ठा drm_encoder *encoder;

	व्योम __iomem *regs;

	काष्ठा clk *pixel_घड़ी;
	काष्ठा clk *core_घड़ी;

	काष्ठा debugfs_regset32 regset;
पूर्ण;

#घोषणा DPI_READ(offset) पढ़ोl(dpi->regs + (offset))
#घोषणा DPI_WRITE(offset, val) ग_लिखोl(val, dpi->regs + (offset))

/* VC4 DPI encoder KMS काष्ठा */
काष्ठा vc4_dpi_encoder अणु
	काष्ठा vc4_encoder base;
	काष्ठा vc4_dpi *dpi;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_dpi_encoder *
to_vc4_dpi_encoder(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा vc4_dpi_encoder, base.base);
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 dpi_regs[] = अणु
	VC4_REG32(DPI_C),
	VC4_REG32(DPI_ID),
पूर्ण;

अटल व्योम vc4_dpi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_dpi_encoder *vc4_encoder = to_vc4_dpi_encoder(encoder);
	काष्ठा vc4_dpi *dpi = vc4_encoder->dpi;

	clk_disable_unprepare(dpi->pixel_घड़ी);
पूर्ण

अटल व्योम vc4_dpi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_display_mode *mode = &encoder->crtc->mode;
	काष्ठा vc4_dpi_encoder *vc4_encoder = to_vc4_dpi_encoder(encoder);
	काष्ठा vc4_dpi *dpi = vc4_encoder->dpi;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_connector *connector = शून्य, *connector_scan;
	u32 dpi_c = DPI_ENABLE | DPI_OUTPUT_ENABLE_MODE;
	पूर्णांक ret;

	/* Look up the connector attached to DPI so we can get the
	 * bus_क्रमmat.  Ideally the bridge would tell us the
	 * bus_क्रमmat we want, but it करोesn't yet, so assume that it's
	 * unअगरorm throughout the bridge chain.
	 */
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector_scan, &conn_iter) अणु
		अगर (connector_scan->encoder == encoder) अणु
			connector = connector_scan;
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (connector && connector->display_info.num_bus_क्रमmats) अणु
		u32 bus_क्रमmat = connector->display_info.bus_क्रमmats[0];

		चयन (bus_क्रमmat) अणु
		हाल MEDIA_BUS_FMT_RGB888_1X24:
			dpi_c |= VC4_SET_FIELD(DPI_FORMAT_24BIT_888_RGB,
					       DPI_FORMAT);
			अवरोध;
		हाल MEDIA_BUS_FMT_BGR888_1X24:
			dpi_c |= VC4_SET_FIELD(DPI_FORMAT_24BIT_888_RGB,
					       DPI_FORMAT);
			dpi_c |= VC4_SET_FIELD(DPI_ORDER_BGR, DPI_ORDER);
			अवरोध;
		हाल MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
			dpi_c |= VC4_SET_FIELD(DPI_FORMAT_18BIT_666_RGB_2,
					       DPI_FORMAT);
			अवरोध;
		हाल MEDIA_BUS_FMT_RGB666_1X18:
			dpi_c |= VC4_SET_FIELD(DPI_FORMAT_18BIT_666_RGB_1,
					       DPI_FORMAT);
			अवरोध;
		हाल MEDIA_BUS_FMT_RGB565_1X16:
			dpi_c |= VC4_SET_FIELD(DPI_FORMAT_16BIT_565_RGB_3,
					       DPI_FORMAT);
			अवरोध;
		शेष:
			DRM_ERROR("Unknown media bus format %d\n", bus_क्रमmat);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Default to 24bit अगर no connector found. */
		dpi_c |= VC4_SET_FIELD(DPI_FORMAT_24BIT_888_RGB, DPI_FORMAT);
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		dpi_c |= DPI_HSYNC_INVERT;
	अन्यथा अगर (!(mode->flags & DRM_MODE_FLAG_PHSYNC))
		dpi_c |= DPI_HSYNC_DISABLE;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		dpi_c |= DPI_VSYNC_INVERT;
	अन्यथा अगर (!(mode->flags & DRM_MODE_FLAG_PVSYNC))
		dpi_c |= DPI_VSYNC_DISABLE;

	DPI_WRITE(DPI_C, dpi_c);

	ret = clk_set_rate(dpi->pixel_घड़ी, mode->घड़ी * 1000);
	अगर (ret)
		DRM_ERROR("Failed to set clock rate: %d\n", ret);

	ret = clk_prepare_enable(dpi->pixel_घड़ी);
	अगर (ret)
		DRM_ERROR("Failed to set clock rate: %d\n", ret);
पूर्ण

अटल क्रमागत drm_mode_status vc4_dpi_encoder_mode_valid(काष्ठा drm_encoder *encoder,
						       स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs vc4_dpi_encoder_helper_funcs = अणु
	.disable = vc4_dpi_encoder_disable,
	.enable = vc4_dpi_encoder_enable,
	.mode_valid = vc4_dpi_encoder_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vc4_dpi_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2835-dpi", .data = शून्य पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Sets up the next link in the display chain, whether it's a panel or
 * a bridge.
 */
अटल पूर्णांक vc4_dpi_init_bridge(काष्ठा vc4_dpi *dpi)
अणु
	काष्ठा device *dev = &dpi->pdev->dev;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0,
					  &panel, &bridge);
	अगर (ret) अणु
		/* If nothing was connected in the DT, that's not an
		 * error.
		 */
		अगर (ret == -ENODEV)
			वापस 0;
		अन्यथा
			वापस ret;
	पूर्ण

	अगर (panel)
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_DPI);

	वापस drm_bridge_attach(dpi->encoder, bridge, शून्य, 0);
पूर्ण

अटल पूर्णांक vc4_dpi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_dpi *dpi;
	काष्ठा vc4_dpi_encoder *vc4_dpi_encoder;
	पूर्णांक ret;

	dpi = devm_kzalloc(dev, माप(*dpi), GFP_KERNEL);
	अगर (!dpi)
		वापस -ENOMEM;

	vc4_dpi_encoder = devm_kzalloc(dev, माप(*vc4_dpi_encoder),
				       GFP_KERNEL);
	अगर (!vc4_dpi_encoder)
		वापस -ENOMEM;
	vc4_dpi_encoder->base.type = VC4_ENCODER_TYPE_DPI;
	vc4_dpi_encoder->dpi = dpi;
	dpi->encoder = &vc4_dpi_encoder->base.base;

	dpi->pdev = pdev;
	dpi->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(dpi->regs))
		वापस PTR_ERR(dpi->regs);
	dpi->regset.base = dpi->regs;
	dpi->regset.regs = dpi_regs;
	dpi->regset.nregs = ARRAY_SIZE(dpi_regs);

	अगर (DPI_READ(DPI_ID) != DPI_ID_VALUE) अणु
		dev_err(dev, "Port returned 0x%08x for ID instead of 0x%08x\n",
			DPI_READ(DPI_ID), DPI_ID_VALUE);
		वापस -ENODEV;
	पूर्ण

	dpi->core_घड़ी = devm_clk_get(dev, "core");
	अगर (IS_ERR(dpi->core_घड़ी)) अणु
		ret = PTR_ERR(dpi->core_घड़ी);
		अगर (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get core clock: %d\n", ret);
		वापस ret;
	पूर्ण
	dpi->pixel_घड़ी = devm_clk_get(dev, "pixel");
	अगर (IS_ERR(dpi->pixel_घड़ी)) अणु
		ret = PTR_ERR(dpi->pixel_घड़ी);
		अगर (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get pixel clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dpi->core_घड़ी);
	अगर (ret)
		DRM_ERROR("Failed to turn on core clock: %d\n", ret);

	drm_simple_encoder_init(drm, dpi->encoder, DRM_MODE_ENCODER_DPI);
	drm_encoder_helper_add(dpi->encoder, &vc4_dpi_encoder_helper_funcs);

	ret = vc4_dpi_init_bridge(dpi);
	अगर (ret)
		जाओ err_destroy_encoder;

	dev_set_drvdata(dev, dpi);

	vc4->dpi = dpi;

	vc4_debugfs_add_regset32(drm, "dpi_regs", &dpi->regset);

	वापस 0;

err_destroy_encoder:
	drm_encoder_cleanup(dpi->encoder);
	clk_disable_unprepare(dpi->core_घड़ी);
	वापस ret;
पूर्ण

अटल व्योम vc4_dpi_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_dpi *dpi = dev_get_drvdata(dev);

	drm_of_panel_bridge_हटाओ(dev->of_node, 0, 0);

	drm_encoder_cleanup(dpi->encoder);

	clk_disable_unprepare(dpi->core_घड़ी);

	vc4->dpi = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_dpi_ops = अणु
	.bind   = vc4_dpi_bind,
	.unbind = vc4_dpi_unbind,
पूर्ण;

अटल पूर्णांक vc4_dpi_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_dpi_ops);
पूर्ण

अटल पूर्णांक vc4_dpi_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_dpi_ops);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver vc4_dpi_driver = अणु
	.probe = vc4_dpi_dev_probe,
	.हटाओ = vc4_dpi_dev_हटाओ,
	.driver = अणु
		.name = "vc4_dpi",
		.of_match_table = vc4_dpi_dt_match,
	पूर्ण,
पूर्ण;
