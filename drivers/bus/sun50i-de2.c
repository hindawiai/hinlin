<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Allwinner A64 Display Engine 2.0 Bus Driver
 *
 * Copyright (C) 2018 Icenowy Zheng <icenowy@aosc.io>
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/sunxi/sunxi_sram.h>

अटल पूर्णांक sun50i_de2_bus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	ret = sunxi_sram_claim(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error couldn't map SRAM to device\n");
		वापस ret;
	पूर्ण

	of_platक्रमm_populate(np, शून्य, शून्य, &pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sun50i_de2_bus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sunxi_sram_release(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun50i_de2_bus_of_match[] = अणु
	अणु .compatible = "allwinner,sun50i-a64-de2", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun50i_de2_bus_driver = अणु
	.probe = sun50i_de2_bus_probe,
	.हटाओ = sun50i_de2_bus_हटाओ,
	.driver = अणु
		.name = "sun50i-de2-bus",
		.of_match_table = sun50i_de2_bus_of_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(sun50i_de2_bus_driver);
