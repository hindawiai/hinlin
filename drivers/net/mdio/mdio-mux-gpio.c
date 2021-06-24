<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011, 2012 Cavium, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_VERSION "1.1"
#घोषणा DRV_DESCRIPTION "GPIO controlled MDIO bus multiplexer driver"

काष्ठा mdio_mux_gpio_state अणु
	काष्ठा gpio_descs *gpios;
	व्योम *mux_handle;
पूर्ण;

अटल पूर्णांक mdio_mux_gpio_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
				   व्योम *data)
अणु
	काष्ठा mdio_mux_gpio_state *s = data;
	DECLARE_BITMAP(values, BITS_PER_TYPE(desired_child));

	अगर (current_child == desired_child)
		वापस 0;

	values[0] = desired_child;

	gpiod_set_array_value_cansleep(s->gpios->ndescs, s->gpios->desc,
				       s->gpios->info, values);

	वापस 0;
पूर्ण

अटल पूर्णांक mdio_mux_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdio_mux_gpio_state *s;
	काष्ठा gpio_descs *gpios;
	पूर्णांक r;

	gpios = devm_gpiod_get_array(&pdev->dev, शून्य, GPIOD_OUT_LOW);
	अगर (IS_ERR(gpios))
		वापस PTR_ERR(gpios);

	s = devm_kzalloc(&pdev->dev, माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s->gpios = gpios;

	r = mdio_mux_init(&pdev->dev, pdev->dev.of_node,
			  mdio_mux_gpio_चयन_fn, &s->mux_handle, s, शून्य);

	अगर (r != 0)
		वापस r;

	pdev->dev.platक्रमm_data = s;
	वापस 0;
पूर्ण

अटल पूर्णांक mdio_mux_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdio_mux_gpio_state *s = dev_get_platdata(&pdev->dev);
	mdio_mux_uninit(s->mux_handle);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mdio_mux_gpio_match[] = अणु
	अणु
		.compatible = "mdio-mux-gpio",
	पूर्ण,
	अणु
		/* Legacy compatible property. */
		.compatible = "cavium,mdio-mux-sn74cbtlv3253",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mdio_mux_gpio_match);

अटल काष्ठा platक्रमm_driver mdio_mux_gpio_driver = अणु
	.driver = अणु
		.name		= "mdio-mux-gpio",
		.of_match_table = mdio_mux_gpio_match,
	पूर्ण,
	.probe		= mdio_mux_gpio_probe,
	.हटाओ		= mdio_mux_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(mdio_mux_gpio_driver);

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL v2");
