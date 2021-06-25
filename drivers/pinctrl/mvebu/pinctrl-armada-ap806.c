<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell Armada ap806 pinctrl driver based on mvebu pinctrl core
 *
 * Copyright (C) 2017 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 * Hanna Hawa <hannah@marvell.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-mvebu.h"

अटल काष्ठा mvebu_mpp_mode armada_ap806_mpp_modes[] = अणु
	MPP_MODE(0,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "clk"),
		 MPP_FUNCTION(3, "spi0",    "clk")),
	MPP_MODE(1,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "cmd"),
		 MPP_FUNCTION(3, "spi0",    "miso")),
	MPP_MODE(2,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d0"),
		 MPP_FUNCTION(3, "spi0",    "mosi")),
	MPP_MODE(3,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d1"),
		 MPP_FUNCTION(3, "spi0",    "cs0n")),
	MPP_MODE(4,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d2"),
		 MPP_FUNCTION(3, "i2c0",    "sda")),
	MPP_MODE(5,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d3"),
		 MPP_FUNCTION(3, "i2c0",    "sdk")),
	MPP_MODE(6,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "ds")),
	MPP_MODE(7,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d4"),
		 MPP_FUNCTION(3, "uart1",   "rxd")),
	MPP_MODE(8,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d5"),
		 MPP_FUNCTION(3, "uart1",   "txd")),
	MPP_MODE(9,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d6"),
		 MPP_FUNCTION(3, "spi0",    "cs1n")),
	MPP_MODE(10,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "d7")),
	MPP_MODE(11,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(3, "uart0",   "txd")),
	MPP_MODE(12,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(1, "sdio",    "pw_off"),
		 MPP_FUNCTION(2, "sdio",    "hw_rst")),
	MPP_MODE(13,
		 MPP_FUNCTION(0, "gpio",    शून्य)),
	MPP_MODE(14,
		 MPP_FUNCTION(0, "gpio",    शून्य)),
	MPP_MODE(15,
		 MPP_FUNCTION(0, "gpio",    शून्य)),
	MPP_MODE(16,
		 MPP_FUNCTION(0, "gpio",    शून्य)),
	MPP_MODE(17,
		 MPP_FUNCTION(0, "gpio",    शून्य)),
	MPP_MODE(18,
		 MPP_FUNCTION(0, "gpio",    शून्य)),
	MPP_MODE(19,
		 MPP_FUNCTION(0, "gpio",    शून्य),
		 MPP_FUNCTION(3, "uart0",   "rxd"),
		 MPP_FUNCTION(4, "sdio",    "pw_off")),
पूर्ण;

अटल काष्ठा mvebu_pinctrl_soc_info armada_ap806_pinctrl_info;

अटल स्थिर काष्ठा of_device_id armada_ap806_pinctrl_of_match[] = अणु
	अणु
		.compatible = "marvell,ap806-pinctrl",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mvebu_mpp_ctrl armada_ap806_mpp_controls[] = अणु
	MPP_FUNC_CTRL(0, 19, शून्य, mvebu_regmap_mpp_ctrl),
पूर्ण;

अटल काष्ठा pinctrl_gpio_range armada_ap806_mpp_gpio_ranges[] = अणु
	MPP_GPIO_RANGE(0,   0,  0, 20),
पूर्ण;

अटल पूर्णांक armada_ap806_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_pinctrl_soc_info *soc = &armada_ap806_pinctrl_info;
	स्थिर काष्ठा of_device_id *match =
		of_match_device(armada_ap806_pinctrl_of_match, &pdev->dev);

	अगर (!match || !pdev->dev.parent)
		वापस -ENODEV;

	soc->variant = 0; /* no variants क्रम Armada AP806 */
	soc->controls = armada_ap806_mpp_controls;
	soc->ncontrols = ARRAY_SIZE(armada_ap806_mpp_controls);
	soc->gpioranges = armada_ap806_mpp_gpio_ranges;
	soc->ngpioranges = ARRAY_SIZE(armada_ap806_mpp_gpio_ranges);
	soc->modes = armada_ap806_mpp_modes;
	soc->nmodes = armada_ap806_mpp_controls[0].npins;

	pdev->dev.platक्रमm_data = soc;

	वापस mvebu_pinctrl_simple_regmap_probe(pdev, pdev->dev.parent, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver armada_ap806_pinctrl_driver = अणु
	.driver = अणु
		.name = "armada-ap806-pinctrl",
		.of_match_table = of_match_ptr(armada_ap806_pinctrl_of_match),
	पूर्ण,
	.probe = armada_ap806_pinctrl_probe,
पूर्ण;

builtin_platक्रमm_driver(armada_ap806_pinctrl_driver);
