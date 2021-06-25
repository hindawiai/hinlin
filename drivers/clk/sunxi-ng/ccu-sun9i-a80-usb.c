<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chen-Yu Tsai. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ccu_common.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_reset.h"

#समावेश "ccu-sun9i-a80-usb.h"

अटल स्थिर काष्ठा clk_parent_data clk_parent_hosc[] = अणु
	अणु .fw_name = "hosc" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data clk_parent_bus[] = अणु
	अणु .fw_name = "bus" पूर्ण,
पूर्ण;

अटल SUNXI_CCU_GATE_DATA(bus_hci0_clk, "bus-hci0", clk_parent_bus, 0x0, BIT(1), 0);
अटल SUNXI_CCU_GATE_DATA(usb_ohci0_clk, "usb-ohci0", clk_parent_hosc, 0x0, BIT(2), 0);
अटल SUNXI_CCU_GATE_DATA(bus_hci1_clk, "bus-hci1", clk_parent_bus, 0x0, BIT(3), 0);
अटल SUNXI_CCU_GATE_DATA(bus_hci2_clk, "bus-hci2", clk_parent_bus, 0x0, BIT(5), 0);
अटल SUNXI_CCU_GATE_DATA(usb_ohci2_clk, "usb-ohci2", clk_parent_hosc, 0x0, BIT(6), 0);

अटल SUNXI_CCU_GATE_DATA(usb0_phy_clk, "usb0-phy", clk_parent_hosc, 0x4, BIT(1), 0);
अटल SUNXI_CCU_GATE_DATA(usb1_hsic_clk, "usb1-hsic", clk_parent_hosc, 0x4, BIT(2), 0);
अटल SUNXI_CCU_GATE_DATA(usb1_phy_clk, "usb1-phy", clk_parent_hosc, 0x4, BIT(3), 0);
अटल SUNXI_CCU_GATE_DATA(usb2_hsic_clk, "usb2-hsic", clk_parent_hosc, 0x4, BIT(4), 0);
अटल SUNXI_CCU_GATE_DATA(usb2_phy_clk, "usb2-phy", clk_parent_hosc, 0x4, BIT(5), 0);
अटल SUNXI_CCU_GATE_DATA(usb_hsic_clk, "usb-hsic", clk_parent_hosc, 0x4, BIT(10), 0);

अटल काष्ठा ccu_common *sun9i_a80_usb_clks[] = अणु
	&bus_hci0_clk.common,
	&usb_ohci0_clk.common,
	&bus_hci1_clk.common,
	&bus_hci2_clk.common,
	&usb_ohci2_clk.common,

	&usb0_phy_clk.common,
	&usb1_hsic_clk.common,
	&usb1_phy_clk.common,
	&usb2_hsic_clk.common,
	&usb2_phy_clk.common,
	&usb_hsic_clk.common,
पूर्ण;

अटल काष्ठा clk_hw_onecell_data sun9i_a80_usb_hw_clks = अणु
	.hws	= अणु
		[CLK_BUS_HCI0]	= &bus_hci0_clk.common.hw,
		[CLK_USB_OHCI0]	= &usb_ohci0_clk.common.hw,
		[CLK_BUS_HCI1]	= &bus_hci1_clk.common.hw,
		[CLK_BUS_HCI2]	= &bus_hci2_clk.common.hw,
		[CLK_USB_OHCI2]	= &usb_ohci2_clk.common.hw,

		[CLK_USB0_PHY]	= &usb0_phy_clk.common.hw,
		[CLK_USB1_HSIC]	= &usb1_hsic_clk.common.hw,
		[CLK_USB1_PHY]	= &usb1_phy_clk.common.hw,
		[CLK_USB2_HSIC]	= &usb2_hsic_clk.common.hw,
		[CLK_USB2_PHY]	= &usb2_phy_clk.common.hw,
		[CLK_USB_HSIC]	= &usb_hsic_clk.common.hw,
	पूर्ण,
	.num	= CLK_NUMBER,
पूर्ण;

अटल काष्ठा ccu_reset_map sun9i_a80_usb_resets[] = अणु
	[RST_USB0_HCI]		= अणु 0x0, BIT(17) पूर्ण,
	[RST_USB1_HCI]		= अणु 0x0, BIT(18) पूर्ण,
	[RST_USB2_HCI]		= अणु 0x0, BIT(19) पूर्ण,

	[RST_USB0_PHY]		= अणु 0x4, BIT(17) पूर्ण,
	[RST_USB1_HSIC]		= अणु 0x4, BIT(18) पूर्ण,
	[RST_USB1_PHY]		= अणु 0x4, BIT(19) पूर्ण,
	[RST_USB2_HSIC]		= अणु 0x4, BIT(20) पूर्ण,
	[RST_USB2_PHY]		= अणु 0x4, BIT(21) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ccu_desc sun9i_a80_usb_clk_desc = अणु
	.ccu_clks	= sun9i_a80_usb_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun9i_a80_usb_clks),

	.hw_clks	= &sun9i_a80_usb_hw_clks,

	.resets		= sun9i_a80_usb_resets,
	.num_resets	= ARRAY_SIZE(sun9i_a80_usb_resets),
पूर्ण;

अटल पूर्णांक sun9i_a80_usb_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा clk *bus_clk;
	व्योम __iomem *reg;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(bus_clk)) अणु
		ret = PTR_ERR(bus_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Couldn't get bus clk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The bus घड़ी needs to be enabled क्रम us to access the रेजिस्टरs */
	ret = clk_prepare_enable(bus_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable bus clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = sunxi_ccu_probe(pdev->dev.of_node, reg,
			      &sun9i_a80_usb_clk_desc);
	अगर (ret)
		जाओ err_disable_clk;

	वापस 0;

err_disable_clk:
	clk_disable_unprepare(bus_clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun9i_a80_usb_clk_ids[] = अणु
	अणु .compatible = "allwinner,sun9i-a80-usb-clks" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun9i_a80_usb_clk_driver = अणु
	.probe	= sun9i_a80_usb_clk_probe,
	.driver	= अणु
		.name	= "sun9i-a80-usb-clks",
		.of_match_table	= sun9i_a80_usb_clk_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun9i_a80_usb_clk_driver);
