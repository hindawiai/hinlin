<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/घड़ी/bcm3368-घड़ी.h>
#समावेश <dt-bindings/घड़ी/bcm6318-घड़ी.h>
#समावेश <dt-bindings/घड़ी/bcm6328-घड़ी.h>
#समावेश <dt-bindings/घड़ी/bcm6358-घड़ी.h>
#समावेश <dt-bindings/घड़ी/bcm6362-घड़ी.h>
#समावेश <dt-bindings/घड़ी/bcm6368-घड़ी.h>
#समावेश <dt-bindings/घड़ी/bcm63268-घड़ी.h>

काष्ठा clk_bcm63xx_table_entry अणु
	स्थिर अक्षर * स्थिर name;
	u8 bit;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा clk_bcm63xx_hw अणु
	व्योम __iomem *regs;
	spinlock_t lock;

	काष्ठा clk_hw_onecell_data data;
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm3368_घड़ीs[] = अणु
	अणु
		.name = "mac",
		.bit = BCM3368_CLK_MAC,
	पूर्ण, अणु
		.name = "tc",
		.bit = BCM3368_CLK_TC,
	पूर्ण, अणु
		.name = "us_top",
		.bit = BCM3368_CLK_US_TOP,
	पूर्ण, अणु
		.name = "ds_top",
		.bit = BCM3368_CLK_DS_TOP,
	पूर्ण, अणु
		.name = "acm",
		.bit = BCM3368_CLK_ACM,
	पूर्ण, अणु
		.name = "spi",
		.bit = BCM3368_CLK_SPI,
	पूर्ण, अणु
		.name = "usbs",
		.bit = BCM3368_CLK_USBS,
	पूर्ण, अणु
		.name = "bmu",
		.bit = BCM3368_CLK_BMU,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM3368_CLK_PCM,
	पूर्ण, अणु
		.name = "ntp",
		.bit = BCM3368_CLK_NTP,
	पूर्ण, अणु
		.name = "acp_b",
		.bit = BCM3368_CLK_ACP_B,
	पूर्ण, अणु
		.name = "acp_a",
		.bit = BCM3368_CLK_ACP_A,
	पूर्ण, अणु
		.name = "emusb",
		.bit = BCM3368_CLK_EMUSB,
	पूर्ण, अणु
		.name = "enet0",
		.bit = BCM3368_CLK_ENET0,
	पूर्ण, अणु
		.name = "enet1",
		.bit = BCM3368_CLK_ENET1,
	पूर्ण, अणु
		.name = "usbsu",
		.bit = BCM3368_CLK_USBSU,
	पूर्ण, अणु
		.name = "ephy",
		.bit = BCM3368_CLK_EPHY,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm6318_घड़ीs[] = अणु
	अणु
		.name = "adsl_asb",
		.bit = BCM6318_CLK_ADSL_ASB,
	पूर्ण, अणु
		.name = "usb_asb",
		.bit = BCM6318_CLK_USB_ASB,
	पूर्ण, अणु
		.name = "mips_asb",
		.bit = BCM6318_CLK_MIPS_ASB,
	पूर्ण, अणु
		.name = "pcie_asb",
		.bit = BCM6318_CLK_PCIE_ASB,
	पूर्ण, अणु
		.name = "phymips_asb",
		.bit = BCM6318_CLK_PHYMIPS_ASB,
	पूर्ण, अणु
		.name = "robosw_asb",
		.bit = BCM6318_CLK_ROBOSW_ASB,
	पूर्ण, अणु
		.name = "sar_asb",
		.bit = BCM6318_CLK_SAR_ASB,
	पूर्ण, अणु
		.name = "sdr_asb",
		.bit = BCM6318_CLK_SDR_ASB,
	पूर्ण, अणु
		.name = "swreg_asb",
		.bit = BCM6318_CLK_SWREG_ASB,
	पूर्ण, अणु
		.name = "periph_asb",
		.bit = BCM6318_CLK_PERIPH_ASB,
	पूर्ण, अणु
		.name = "cpubus160",
		.bit = BCM6318_CLK_CPUBUS160,
	पूर्ण, अणु
		.name = "adsl",
		.bit = BCM6318_CLK_ADSL,
	पूर्ण, अणु
		.name = "sar125",
		.bit = BCM6318_CLK_SAR125,
	पूर्ण, अणु
		.name = "mips",
		.bit = BCM6318_CLK_MIPS,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM6318_CLK_PCIE,
	पूर्ण, अणु
		.name = "robosw250",
		.bit = BCM6318_CLK_ROBOSW250,
	पूर्ण, अणु
		.name = "robosw025",
		.bit = BCM6318_CLK_ROBOSW025,
	पूर्ण, अणु
		.name = "sdr",
		.bit = BCM6318_CLK_SDR,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM6318_CLK_USBD,
	पूर्ण, अणु
		.name = "hsspi",
		.bit = BCM6318_CLK_HSSPI,
	पूर्ण, अणु
		.name = "pcie25",
		.bit = BCM6318_CLK_PCIE25,
	पूर्ण, अणु
		.name = "phymips",
		.bit = BCM6318_CLK_PHYMIPS,
	पूर्ण, अणु
		.name = "afe",
		.bit = BCM6318_CLK_AFE,
	पूर्ण, अणु
		.name = "qproc",
		.bit = BCM6318_CLK_QPROC,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm6318_ubus_घड़ीs[] = अणु
	अणु
		.name = "adsl-ubus",
		.bit = BCM6318_UCLK_ADSL,
	पूर्ण, अणु
		.name = "arb-ubus",
		.bit = BCM6318_UCLK_ARB,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "mips-ubus",
		.bit = BCM6318_UCLK_MIPS,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "pcie-ubus",
		.bit = BCM6318_UCLK_PCIE,
	पूर्ण, अणु
		.name = "periph-ubus",
		.bit = BCM6318_UCLK_PERIPH,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "phymips-ubus",
		.bit = BCM6318_UCLK_PHYMIPS,
	पूर्ण, अणु
		.name = "robosw-ubus",
		.bit = BCM6318_UCLK_ROBOSW,
	पूर्ण, अणु
		.name = "sar-ubus",
		.bit = BCM6318_UCLK_SAR,
	पूर्ण, अणु
		.name = "sdr-ubus",
		.bit = BCM6318_UCLK_SDR,
	पूर्ण, अणु
		.name = "usb-ubus",
		.bit = BCM6318_UCLK_USB,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm6328_घड़ीs[] = अणु
	अणु
		.name = "phy_mips",
		.bit = BCM6328_CLK_PHYMIPS,
	पूर्ण, अणु
		.name = "adsl_qproc",
		.bit = BCM6328_CLK_ADSL_QPROC,
	पूर्ण, अणु
		.name = "adsl_afe",
		.bit = BCM6328_CLK_ADSL_AFE,
	पूर्ण, अणु
		.name = "adsl",
		.bit = BCM6328_CLK_ADSL,
	पूर्ण, अणु
		.name = "mips",
		.bit = BCM6328_CLK_MIPS,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "sar",
		.bit = BCM6328_CLK_SAR,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM6328_CLK_PCM,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM6328_CLK_USBD,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM6328_CLK_USBH,
	पूर्ण, अणु
		.name = "hsspi",
		.bit = BCM6328_CLK_HSSPI,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM6328_CLK_PCIE,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM6328_CLK_ROBOSW,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm6358_घड़ीs[] = अणु
	अणु
		.name = "enet",
		.bit = BCM6358_CLK_ENET,
	पूर्ण, अणु
		.name = "adslphy",
		.bit = BCM6358_CLK_ADSLPHY,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM6358_CLK_PCM,
	पूर्ण, अणु
		.name = "spi",
		.bit = BCM6358_CLK_SPI,
	पूर्ण, अणु
		.name = "usbs",
		.bit = BCM6358_CLK_USBS,
	पूर्ण, अणु
		.name = "sar",
		.bit = BCM6358_CLK_SAR,
	पूर्ण, अणु
		.name = "emusb",
		.bit = BCM6358_CLK_EMUSB,
	पूर्ण, अणु
		.name = "enet0",
		.bit = BCM6358_CLK_ENET0,
	पूर्ण, अणु
		.name = "enet1",
		.bit = BCM6358_CLK_ENET1,
	पूर्ण, अणु
		.name = "usbsu",
		.bit = BCM6358_CLK_USBSU,
	पूर्ण, अणु
		.name = "ephy",
		.bit = BCM6358_CLK_EPHY,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm6362_घड़ीs[] = अणु
	अणु
		.name = "adsl_qproc",
		.bit = BCM6362_CLK_ADSL_QPROC,
	पूर्ण, अणु
		.name = "adsl_afe",
		.bit = BCM6362_CLK_ADSL_AFE,
	पूर्ण, अणु
		.name = "adsl",
		.bit = BCM6362_CLK_ADSL,
	पूर्ण, अणु
		.name = "mips",
		.bit = BCM6362_CLK_MIPS,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "wlan_ocp",
		.bit = BCM6362_CLK_WLAN_OCP,
	पूर्ण, अणु
		.name = "swpkt_usb",
		.bit = BCM6362_CLK_SWPKT_USB,
	पूर्ण, अणु
		.name = "swpkt_sar",
		.bit = BCM6362_CLK_SWPKT_SAR,
	पूर्ण, अणु
		.name = "sar",
		.bit = BCM6362_CLK_SAR,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM6362_CLK_ROBOSW,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM6362_CLK_PCM,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM6362_CLK_USBD,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM6362_CLK_USBH,
	पूर्ण, अणु
		.name = "ipsec",
		.bit = BCM6362_CLK_IPSEC,
	पूर्ण, अणु
		.name = "spi",
		.bit = BCM6362_CLK_SPI,
	पूर्ण, अणु
		.name = "hsspi",
		.bit = BCM6362_CLK_HSSPI,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM6362_CLK_PCIE,
	पूर्ण, अणु
		.name = "fap",
		.bit = BCM6362_CLK_FAP,
	पूर्ण, अणु
		.name = "phymips",
		.bit = BCM6362_CLK_PHYMIPS,
	पूर्ण, अणु
		.name = "nand",
		.bit = BCM6362_CLK_न_अंकD,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm6368_घड़ीs[] = अणु
	अणु
		.name = "vdsl_qproc",
		.bit = BCM6368_CLK_VDSL_QPROC,
	पूर्ण, अणु
		.name = "vdsl_afe",
		.bit = BCM6368_CLK_VDSL_AFE,
	पूर्ण, अणु
		.name = "vdsl_bonding",
		.bit = BCM6368_CLK_VDSL_BONDING,
	पूर्ण, अणु
		.name = "vdsl",
		.bit = BCM6368_CLK_VDSL,
	पूर्ण, अणु
		.name = "phymips",
		.bit = BCM6368_CLK_PHYMIPS,
	पूर्ण, अणु
		.name = "swpkt_usb",
		.bit = BCM6368_CLK_SWPKT_USB,
	पूर्ण, अणु
		.name = "swpkt_sar",
		.bit = BCM6368_CLK_SWPKT_SAR,
	पूर्ण, अणु
		.name = "spi",
		.bit = BCM6368_CLK_SPI,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM6368_CLK_USBD,
	पूर्ण, अणु
		.name = "sar",
		.bit = BCM6368_CLK_SAR,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM6368_CLK_ROBOSW,
	पूर्ण, अणु
		.name = "utopia",
		.bit = BCM6368_CLK_UTOPIA,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM6368_CLK_PCM,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM6368_CLK_USBH,
	पूर्ण, अणु
		.name = "disable_gless",
		.bit = BCM6368_CLK_DIS_GLESS,
	पूर्ण, अणु
		.name = "nand",
		.bit = BCM6368_CLK_न_अंकD,
	पूर्ण, अणु
		.name = "ipsec",
		.bit = BCM6368_CLK_IPSEC,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_bcm63xx_table_entry bcm63268_घड़ीs[] = अणु
	अणु
		.name = "disable_gless",
		.bit = BCM63268_CLK_DIS_GLESS,
	पूर्ण, अणु
		.name = "vdsl_qproc",
		.bit = BCM63268_CLK_VDSL_QPROC,
	पूर्ण, अणु
		.name = "vdsl_afe",
		.bit = BCM63268_CLK_VDSL_AFE,
	पूर्ण, अणु
		.name = "vdsl",
		.bit = BCM63268_CLK_VDSL,
	पूर्ण, अणु
		.name = "mips",
		.bit = BCM63268_CLK_MIPS,
		.flags = CLK_IS_CRITICAL,
	पूर्ण, अणु
		.name = "wlan_ocp",
		.bit = BCM63268_CLK_WLAN_OCP,
	पूर्ण, अणु
		.name = "dect",
		.bit = BCM63268_CLK_DECT,
	पूर्ण, अणु
		.name = "fap0",
		.bit = BCM63268_CLK_FAP0,
	पूर्ण, अणु
		.name = "fap1",
		.bit = BCM63268_CLK_FAP1,
	पूर्ण, अणु
		.name = "sar",
		.bit = BCM63268_CLK_SAR,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM63268_CLK_ROBOSW,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM63268_CLK_PCM,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM63268_CLK_USBD,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM63268_CLK_USBH,
	पूर्ण, अणु
		.name = "ipsec",
		.bit = BCM63268_CLK_IPSEC,
	पूर्ण, अणु
		.name = "spi",
		.bit = BCM63268_CLK_SPI,
	पूर्ण, अणु
		.name = "hsspi",
		.bit = BCM63268_CLK_HSSPI,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM63268_CLK_PCIE,
	पूर्ण, अणु
		.name = "phymips",
		.bit = BCM63268_CLK_PHYMIPS,
	पूर्ण, अणु
		.name = "gmac",
		.bit = BCM63268_CLK_GMAC,
	पूर्ण, अणु
		.name = "nand",
		.bit = BCM63268_CLK_न_अंकD,
	पूर्ण, अणु
		.name = "tbus",
		.bit = BCM63268_CLK_TBUS,
	पूर्ण, अणु
		.name = "robosw250",
		.bit = BCM63268_CLK_ROBOSW250,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल पूर्णांक clk_bcm63xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा clk_bcm63xx_table_entry *entry, *table;
	काष्ठा clk_bcm63xx_hw *hw;
	u8 maxbit = 0;
	पूर्णांक i, ret;

	table = of_device_get_match_data(&pdev->dev);
	अगर (!table)
		वापस -EINVAL;

	क्रम (entry = table; entry->name; entry++)
		maxbit = max_t(u8, maxbit, entry->bit);
	maxbit++;

	hw = devm_kzalloc(&pdev->dev, काष्ठा_size(hw, data.hws, maxbit),
			  GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hw);

	spin_lock_init(&hw->lock);

	hw->data.num = maxbit;
	क्रम (i = 0; i < maxbit; i++)
		hw->data.hws[i] = ERR_PTR(-ENODEV);

	hw->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hw->regs))
		वापस PTR_ERR(hw->regs);

	क्रम (entry = table; entry->name; entry++) अणु
		काष्ठा clk_hw *clk;

		clk = clk_hw_रेजिस्टर_gate(&pdev->dev, entry->name, शून्य,
					   entry->flags, hw->regs, entry->bit,
					   CLK_GATE_BIG_ENDIAN, &hw->lock);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			जाओ out_err;
		पूर्ण

		hw->data.hws[entry->bit] = clk;
	पूर्ण

	ret = of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_onecell_get,
				     &hw->data);
	अगर (!ret)
		वापस 0;
out_err:
	क्रम (i = 0; i < hw->data.num; i++) अणु
		अगर (!IS_ERR(hw->data.hws[i]))
			clk_hw_unरेजिस्टर_gate(hw->data.hws[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clk_bcm63xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_bcm63xx_hw *hw = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	of_clk_del_provider(pdev->dev.of_node);

	क्रम (i = 0; i < hw->data.num; i++) अणु
		अगर (!IS_ERR(hw->data.hws[i]))
			clk_hw_unरेजिस्टर_gate(hw->data.hws[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clk_bcm63xx_dt_ids[] = अणु
	अणु .compatible = "brcm,bcm3368-clocks", .data = &bcm3368_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm6318-clocks", .data = &bcm6318_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm6318-ubus-clocks", .data = &bcm6318_ubus_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm6328-clocks", .data = &bcm6328_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm6358-clocks", .data = &bcm6358_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm6362-clocks", .data = &bcm6362_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm6368-clocks", .data = &bcm6368_घड़ीs, पूर्ण,
	अणु .compatible = "brcm,bcm63268-clocks", .data = &bcm63268_घड़ीs, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver clk_bcm63xx = अणु
	.probe = clk_bcm63xx_probe,
	.हटाओ = clk_bcm63xx_हटाओ,
	.driver = अणु
		.name = "bcm63xx-clock",
		.of_match_table = clk_bcm63xx_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(clk_bcm63xx);
