<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car Gen2 PHY driver
 *
 * Copyright (C) 2014 Renesas Solutions Corp.
 * Copyright (C) 2014 Cogent Embedded, Inc.
 * Copyright (C) 2019 Renesas Electronics Corp.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/of_device.h>

#घोषणा USBHS_LPSTS			0x02
#घोषणा USBHS_UGCTRL			0x80
#घोषणा USBHS_UGCTRL2			0x84
#घोषणा USBHS_UGSTS			0x88	/* From technical update */

/* Low Power Status रेजिस्टर (LPSTS) */
#घोषणा USBHS_LPSTS_SUSPM		0x4000

/* USB General control रेजिस्टर (UGCTRL) */
#घोषणा USBHS_UGCTRL_CONNECT		0x00000004
#घोषणा USBHS_UGCTRL_PLLRESET		0x00000001

/* USB General control रेजिस्टर 2 (UGCTRL2) */
#घोषणा USBHS_UGCTRL2_USB2SEL		0x80000000
#घोषणा USBHS_UGCTRL2_USB2SEL_PCI	0x00000000
#घोषणा USBHS_UGCTRL2_USB2SEL_USB30	0x80000000
#घोषणा USBHS_UGCTRL2_USB0SEL		0x00000030
#घोषणा USBHS_UGCTRL2_USB0SEL_PCI	0x00000010
#घोषणा USBHS_UGCTRL2_USB0SEL_HS_USB	0x00000030
#घोषणा USBHS_UGCTRL2_USB0SEL_USB20	0x00000010
#घोषणा USBHS_UGCTRL2_USB0SEL_HS_USB20	0x00000020

/* USB General status रेजिस्टर (UGSTS) */
#घोषणा USBHS_UGSTS_LOCK		0x00000100 /* From technical update */

#घोषणा PHYS_PER_CHANNEL	2

काष्ठा rcar_gen2_phy अणु
	काष्ठा phy *phy;
	काष्ठा rcar_gen2_channel *channel;
	पूर्णांक number;
	u32 select_value;
पूर्ण;

काष्ठा rcar_gen2_channel अणु
	काष्ठा device_node *of_node;
	काष्ठा rcar_gen2_phy_driver *drv;
	काष्ठा rcar_gen2_phy phys[PHYS_PER_CHANNEL];
	पूर्णांक selected_phy;
	u32 select_mask;
पूर्ण;

काष्ठा rcar_gen2_phy_driver अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	spinlock_t lock;
	पूर्णांक num_channels;
	काष्ठा rcar_gen2_channel *channels;
पूर्ण;

काष्ठा rcar_gen2_phy_data अणु
	स्थिर काष्ठा phy_ops *gen2_phy_ops;
	स्थिर u32 (*select_value)[PHYS_PER_CHANNEL];
	स्थिर u32 num_channels;
पूर्ण;

अटल पूर्णांक rcar_gen2_phy_init(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen2_phy *phy = phy_get_drvdata(p);
	काष्ठा rcar_gen2_channel *channel = phy->channel;
	काष्ठा rcar_gen2_phy_driver *drv = channel->drv;
	अचिन्हित दीर्घ flags;
	u32 ugctrl2;

	/*
	 * Try to acquire exclusive access to PHY.  The first driver calling
	 * phy_init()  on a given channel wins, and all attempts  to use another
	 * PHY on this channel will fail until phy_निकास() is called by the first
	 * driver.   Achieving this with cmpxcgh() should be SMP-safe.
	 */
	अगर (cmpxchg(&channel->selected_phy, -1, phy->number) != -1)
		वापस -EBUSY;

	clk_prepare_enable(drv->clk);

	spin_lock_irqsave(&drv->lock, flags);
	ugctrl2 = पढ़ोl(drv->base + USBHS_UGCTRL2);
	ugctrl2 &= ~channel->select_mask;
	ugctrl2 |= phy->select_value;
	ग_लिखोl(ugctrl2, drv->base + USBHS_UGCTRL2);
	spin_unlock_irqrestore(&drv->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक rcar_gen2_phy_निकास(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen2_phy *phy = phy_get_drvdata(p);
	काष्ठा rcar_gen2_channel *channel = phy->channel;

	clk_disable_unprepare(channel->drv->clk);

	channel->selected_phy = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_gen2_phy_घातer_on(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen2_phy *phy = phy_get_drvdata(p);
	काष्ठा rcar_gen2_phy_driver *drv = phy->channel->drv;
	व्योम __iomem *base = drv->base;
	अचिन्हित दीर्घ flags;
	u32 value;
	पूर्णांक err = 0, i;

	/* Skip अगर it's not USBHS */
	अगर (phy->select_value != USBHS_UGCTRL2_USB0SEL_HS_USB)
		वापस 0;

	spin_lock_irqsave(&drv->lock, flags);

	/* Power on USBHS PHY */
	value = पढ़ोl(base + USBHS_UGCTRL);
	value &= ~USBHS_UGCTRL_PLLRESET;
	ग_लिखोl(value, base + USBHS_UGCTRL);

	value = पढ़ोw(base + USBHS_LPSTS);
	value |= USBHS_LPSTS_SUSPM;
	ग_लिखोw(value, base + USBHS_LPSTS);

	क्रम (i = 0; i < 20; i++) अणु
		value = पढ़ोl(base + USBHS_UGSTS);
		अगर ((value & USBHS_UGSTS_LOCK) == USBHS_UGSTS_LOCK) अणु
			value = पढ़ोl(base + USBHS_UGCTRL);
			value |= USBHS_UGCTRL_CONNECT;
			ग_लिखोl(value, base + USBHS_UGCTRL);
			जाओ out;
		पूर्ण
		udelay(1);
	पूर्ण

	/* Timed out रुकोing क्रम the PLL lock */
	err = -ETIMEDOUT;

out:
	spin_unlock_irqrestore(&drv->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक rcar_gen2_phy_घातer_off(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen2_phy *phy = phy_get_drvdata(p);
	काष्ठा rcar_gen2_phy_driver *drv = phy->channel->drv;
	व्योम __iomem *base = drv->base;
	अचिन्हित दीर्घ flags;
	u32 value;

	/* Skip अगर it's not USBHS */
	अगर (phy->select_value != USBHS_UGCTRL2_USB0SEL_HS_USB)
		वापस 0;

	spin_lock_irqsave(&drv->lock, flags);

	/* Power off USBHS PHY */
	value = पढ़ोl(base + USBHS_UGCTRL);
	value &= ~USBHS_UGCTRL_CONNECT;
	ग_लिखोl(value, base + USBHS_UGCTRL);

	value = पढ़ोw(base + USBHS_LPSTS);
	value &= ~USBHS_LPSTS_SUSPM;
	ग_लिखोw(value, base + USBHS_LPSTS);

	value = पढ़ोl(base + USBHS_UGCTRL);
	value |= USBHS_UGCTRL_PLLRESET;
	ग_लिखोl(value, base + USBHS_UGCTRL);

	spin_unlock_irqrestore(&drv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rz_g1c_phy_घातer_on(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen2_phy *phy = phy_get_drvdata(p);
	काष्ठा rcar_gen2_phy_driver *drv = phy->channel->drv;
	व्योम __iomem *base = drv->base;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&drv->lock, flags);

	/* Power on USBHS PHY */
	value = पढ़ोl(base + USBHS_UGCTRL);
	value &= ~USBHS_UGCTRL_PLLRESET;
	ग_लिखोl(value, base + USBHS_UGCTRL);

	/* As per the data sheet रुको 340 micro sec क्रम घातer stable */
	udelay(340);

	अगर (phy->select_value == USBHS_UGCTRL2_USB0SEL_HS_USB20) अणु
		value = पढ़ोw(base + USBHS_LPSTS);
		value |= USBHS_LPSTS_SUSPM;
		ग_लिखोw(value, base + USBHS_LPSTS);
	पूर्ण

	spin_unlock_irqrestore(&drv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rz_g1c_phy_घातer_off(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen2_phy *phy = phy_get_drvdata(p);
	काष्ठा rcar_gen2_phy_driver *drv = phy->channel->drv;
	व्योम __iomem *base = drv->base;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&drv->lock, flags);
	/* Power off USBHS PHY */
	अगर (phy->select_value == USBHS_UGCTRL2_USB0SEL_HS_USB20) अणु
		value = पढ़ोw(base + USBHS_LPSTS);
		value &= ~USBHS_LPSTS_SUSPM;
		ग_लिखोw(value, base + USBHS_LPSTS);
	पूर्ण

	value = पढ़ोl(base + USBHS_UGCTRL);
	value |= USBHS_UGCTRL_PLLRESET;
	ग_लिखोl(value, base + USBHS_UGCTRL);

	spin_unlock_irqrestore(&drv->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops rcar_gen2_phy_ops = अणु
	.init		= rcar_gen2_phy_init,
	.निकास		= rcar_gen2_phy_निकास,
	.घातer_on	= rcar_gen2_phy_घातer_on,
	.घातer_off	= rcar_gen2_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा phy_ops rz_g1c_phy_ops = अणु
	.init		= rcar_gen2_phy_init,
	.निकास		= rcar_gen2_phy_निकास,
	.घातer_on	= rz_g1c_phy_घातer_on,
	.घातer_off	= rz_g1c_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर u32 pci_select_value[][PHYS_PER_CHANNEL] = अणु
	[0]	= अणु USBHS_UGCTRL2_USB0SEL_PCI, USBHS_UGCTRL2_USB0SEL_HS_USB पूर्ण,
	[2]	= अणु USBHS_UGCTRL2_USB2SEL_PCI, USBHS_UGCTRL2_USB2SEL_USB30 पूर्ण,
पूर्ण;

अटल स्थिर u32 usb20_select_value[][PHYS_PER_CHANNEL] = अणु
	अणु USBHS_UGCTRL2_USB0SEL_USB20, USBHS_UGCTRL2_USB0SEL_HS_USB20 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_gen2_phy_data rcar_gen2_usb_phy_data = अणु
	.gen2_phy_ops = &rcar_gen2_phy_ops,
	.select_value = pci_select_value,
	.num_channels = ARRAY_SIZE(pci_select_value),
पूर्ण;

अटल स्थिर काष्ठा rcar_gen2_phy_data rz_g1c_usb_phy_data = अणु
	.gen2_phy_ops = &rz_g1c_phy_ops,
	.select_value = usb20_select_value,
	.num_channels = ARRAY_SIZE(usb20_select_value),
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_gen2_phy_match_table[] = अणु
	अणु
		.compatible = "renesas,usb-phy-r8a77470",
		.data = &rz_g1c_usb_phy_data,
	पूर्ण,
	अणु
		.compatible = "renesas,usb-phy-r8a7790",
		.data = &rcar_gen2_usb_phy_data,
	पूर्ण,
	अणु
		.compatible = "renesas,usb-phy-r8a7791",
		.data = &rcar_gen2_usb_phy_data,
	पूर्ण,
	अणु
		.compatible = "renesas,usb-phy-r8a7794",
		.data = &rcar_gen2_usb_phy_data,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-usb-phy",
		.data = &rcar_gen2_usb_phy_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_gen2_phy_match_table);

अटल काष्ठा phy *rcar_gen2_phy_xlate(काष्ठा device *dev,
				       काष्ठा of_phandle_args *args)
अणु
	काष्ठा rcar_gen2_phy_driver *drv;
	काष्ठा device_node *np = args->np;
	पूर्णांक i;

	drv = dev_get_drvdata(dev);
	अगर (!drv)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < drv->num_channels; i++) अणु
		अगर (np == drv->channels[i].of_node)
			अवरोध;
	पूर्ण

	अगर (i >= drv->num_channels || args->args[0] >= 2)
		वापस ERR_PTR(-ENODEV);

	वापस drv->channels[i].phys[args->args[0]].phy;
पूर्ण

अटल स्थिर u32 select_mask[] = अणु
	[0]	= USBHS_UGCTRL2_USB0SEL,
	[2]	= USBHS_UGCTRL2_USB2SEL,
पूर्ण;

अटल पूर्णांक rcar_gen2_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_gen2_phy_driver *drv;
	काष्ठा phy_provider *provider;
	काष्ठा device_node *np;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	स्थिर काष्ठा rcar_gen2_phy_data *data;
	पूर्णांक i = 0;

	अगर (!dev->of_node) अणु
		dev_err(dev,
			"This driver is required to be instantiated from device tree\n");
		वापस -EINVAL;
	पूर्ण

	clk = devm_clk_get(dev, "usbhs");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "Can't get USBHS clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	drv = devm_kzalloc(dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	spin_lock_init(&drv->lock);

	drv->clk = clk;
	drv->base = base;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	drv->num_channels = of_get_child_count(dev->of_node);
	drv->channels = devm_kसुस्मृति(dev, drv->num_channels,
				     माप(काष्ठा rcar_gen2_channel),
				     GFP_KERNEL);
	अगर (!drv->channels)
		वापस -ENOMEM;

	क्रम_each_child_of_node(dev->of_node, np) अणु
		काष्ठा rcar_gen2_channel *channel = drv->channels + i;
		u32 channel_num;
		पूर्णांक error, n;

		channel->of_node = np;
		channel->drv = drv;
		channel->selected_phy = -1;

		error = of_property_पढ़ो_u32(np, "reg", &channel_num);
		अगर (error || channel_num >= data->num_channels) अणु
			dev_err(dev, "Invalid \"reg\" property\n");
			of_node_put(np);
			वापस error;
		पूर्ण
		channel->select_mask = select_mask[channel_num];

		क्रम (n = 0; n < PHYS_PER_CHANNEL; n++) अणु
			काष्ठा rcar_gen2_phy *phy = &channel->phys[n];

			phy->channel = channel;
			phy->number = n;
			phy->select_value = data->select_value[channel_num][n];

			phy->phy = devm_phy_create(dev, शून्य,
						   data->gen2_phy_ops);
			अगर (IS_ERR(phy->phy)) अणु
				dev_err(dev, "Failed to create PHY\n");
				of_node_put(np);
				वापस PTR_ERR(phy->phy);
			पूर्ण
			phy_set_drvdata(phy->phy, phy);
		पूर्ण

		i++;
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(dev, rcar_gen2_phy_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "Failed to register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	dev_set_drvdata(dev, drv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rcar_gen2_phy_driver = अणु
	.driver = अणु
		.name		= "phy_rcar_gen2",
		.of_match_table	= rcar_gen2_phy_match_table,
	पूर्ण,
	.probe	= rcar_gen2_phy_probe,
पूर्ण;

module_platक्रमm_driver(rcar_gen2_phy_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renesas R-Car Gen2 PHY");
MODULE_AUTHOR("Sergei Shtylyov <sergei.shtylyov@cogentembedded.com>");
