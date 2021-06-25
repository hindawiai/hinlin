<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TPD12S015 HDMI ESD protection & level shअगरter chip driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic encoder-opa362 driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_bridge.h>

काष्ठा tpd12s015_device अणु
	काष्ठा drm_bridge bridge;

	काष्ठा gpio_desc *ct_cp_hpd_gpio;
	काष्ठा gpio_desc *ls_oe_gpio;
	काष्ठा gpio_desc *hpd_gpio;
	पूर्णांक hpd_irq;

	काष्ठा drm_bridge *next_bridge;
पूर्ण;

अटल अंतरभूत काष्ठा tpd12s015_device *to_tpd12s015(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा tpd12s015_device, bridge);
पूर्ण

अटल पूर्णांक tpd12s015_attach(काष्ठा drm_bridge *bridge,
			    क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tpd12s015_device *tpd = to_tpd12s015(bridge);
	पूर्णांक ret;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	ret = drm_bridge_attach(bridge->encoder, tpd->next_bridge,
				bridge, flags);
	अगर (ret < 0)
		वापस ret;

	gpiod_set_value_cansleep(tpd->ls_oe_gpio, 1);

	/* DC-DC converter needs at max 300us to get to 90% of 5V. */
	usleep_range(300, 1000);

	वापस 0;
पूर्ण

अटल व्योम tpd12s015_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tpd12s015_device *tpd = to_tpd12s015(bridge);

	gpiod_set_value_cansleep(tpd->ls_oe_gpio, 0);
पूर्ण

अटल क्रमागत drm_connector_status tpd12s015_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tpd12s015_device *tpd = to_tpd12s015(bridge);

	अगर (gpiod_get_value_cansleep(tpd->hpd_gpio))
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल व्योम tpd12s015_hpd_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tpd12s015_device *tpd = to_tpd12s015(bridge);

	gpiod_set_value_cansleep(tpd->ct_cp_hpd_gpio, 1);
पूर्ण

अटल व्योम tpd12s015_hpd_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tpd12s015_device *tpd = to_tpd12s015(bridge);

	gpiod_set_value_cansleep(tpd->ct_cp_hpd_gpio, 0);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tpd12s015_bridge_funcs = अणु
	.attach			= tpd12s015_attach,
	.detach			= tpd12s015_detach,
	.detect			= tpd12s015_detect,
	.hpd_enable		= tpd12s015_hpd_enable,
	.hpd_disable		= tpd12s015_hpd_disable,
पूर्ण;

अटल irqवापस_t tpd12s015_hpd_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tpd12s015_device *tpd = data;
	काष्ठा drm_bridge *bridge = &tpd->bridge;

	drm_bridge_hpd_notअगरy(bridge, tpd12s015_detect(bridge));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tpd12s015_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpd12s015_device *tpd;
	काष्ठा device_node *node;
	काष्ठा gpio_desc *gpio;
	पूर्णांक ret;

	tpd = devm_kzalloc(&pdev->dev, माप(*tpd), GFP_KERNEL);
	अगर (!tpd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, tpd);

	tpd->bridge.funcs = &tpd12s015_bridge_funcs;
	tpd->bridge.of_node = pdev->dev.of_node;
	tpd->bridge.type = DRM_MODE_CONNECTOR_HDMIA;
	tpd->bridge.ops = DRM_BRIDGE_OP_DETECT;

	/* Get the next bridge, connected to port@1. */
	node = of_graph_get_remote_node(pdev->dev.of_node, 1, -1);
	अगर (!node)
		वापस -ENODEV;

	tpd->next_bridge = of_drm_find_bridge(node);
	of_node_put(node);

	अगर (!tpd->next_bridge)
		वापस -EPROBE_DEFER;

	/* Get the control and HPD GPIOs. */
	gpio = devm_gpiod_get_index_optional(&pdev->dev, शून्य, 0,
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	tpd->ct_cp_hpd_gpio = gpio;

	gpio = devm_gpiod_get_index_optional(&pdev->dev, शून्य, 1,
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	tpd->ls_oe_gpio = gpio;

	gpio = devm_gpiod_get_index(&pdev->dev, शून्य, 2, GPIOD_IN);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	tpd->hpd_gpio = gpio;

	/* Register the IRQ अगर the HPD GPIO is IRQ-capable. */
	tpd->hpd_irq = gpiod_to_irq(tpd->hpd_gpio);
	अगर (tpd->hpd_irq >= 0) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, tpd->hpd_irq, शून्य,
						tpd12s015_hpd_isr,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"tpd12s015 hpd", tpd);
		अगर (ret)
			वापस ret;

		tpd->bridge.ops |= DRM_BRIDGE_OP_HPD;
	पूर्ण

	/* Register the DRM bridge. */
	drm_bridge_add(&tpd->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास tpd12s015_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpd12s015_device *tpd = platक्रमm_get_drvdata(pdev);

	drm_bridge_हटाओ(&tpd->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tpd12s015_of_match[] = अणु
	अणु .compatible = "ti,tpd12s015", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tpd12s015_of_match);

अटल काष्ठा platक्रमm_driver tpd12s015_driver = अणु
	.probe	= tpd12s015_probe,
	.हटाओ	= __निकास_p(tpd12s015_हटाओ),
	.driver	= अणु
		.name	= "tpd12s015",
		.of_match_table = tpd12s015_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tpd12s015_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("TPD12S015 HDMI level shifter and ESD protection driver");
MODULE_LICENSE("GPL");
