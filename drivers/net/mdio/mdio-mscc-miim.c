<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Driver क्रम the MDIO पूर्णांकerface of Microsemi network चयनes.
 *
 * Author: Alexandre Belloni <alexandre.belloni@bootlin.com>
 * Copyright (c) 2017 Microsemi Corporation
 */

#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MSCC_MIIM_REG_STATUS		0x0
#घोषणा		MSCC_MIIM_STATUS_STAT_PENDING	BIT(2)
#घोषणा		MSCC_MIIM_STATUS_STAT_BUSY	BIT(3)
#घोषणा MSCC_MIIM_REG_CMD		0x8
#घोषणा		MSCC_MIIM_CMD_OPR_WRITE		BIT(1)
#घोषणा		MSCC_MIIM_CMD_OPR_READ		BIT(2)
#घोषणा		MSCC_MIIM_CMD_WRDATA_SHIFT	4
#घोषणा		MSCC_MIIM_CMD_REGAD_SHIFT	20
#घोषणा		MSCC_MIIM_CMD_PHYAD_SHIFT	25
#घोषणा		MSCC_MIIM_CMD_VLD		BIT(31)
#घोषणा MSCC_MIIM_REG_DATA		0xC
#घोषणा		MSCC_MIIM_DATA_ERROR		(BIT(16) | BIT(17))

#घोषणा MSCC_PHY_REG_PHY_CFG	0x0
#घोषणा		PHY_CFG_PHY_ENA		(BIT(0) | BIT(1) | BIT(2) | BIT(3))
#घोषणा		PHY_CFG_PHY_COMMON_RESET BIT(4)
#घोषणा		PHY_CFG_PHY_RESET	(BIT(5) | BIT(6) | BIT(7) | BIT(8))
#घोषणा MSCC_PHY_REG_PHY_STATUS	0x4

काष्ठा mscc_miim_dev अणु
	व्योम __iomem *regs;
	व्योम __iomem *phy_regs;
पूर्ण;

/* When high resolution समयrs aren't built-in: we can't use usleep_range() as
 * we would sleep way too दीर्घ. Use udelay() instead.
 */
#घोषणा mscc_पढ़ोl_poll_समयout(addr, val, cond, delay_us, समयout_us)	\
(अणु									\
	अगर (!IS_ENABLED(CONFIG_HIGH_RES_TIMERS))			\
		पढ़ोl_poll_समयout_atomic(addr, val, cond, delay_us,	\
					  समयout_us);			\
	पढ़ोl_poll_समयout(addr, val, cond, delay_us, समयout_us);	\
पूर्ण)

अटल पूर्णांक mscc_miim_रुको_पढ़ोy(काष्ठा mii_bus *bus)
अणु
	काष्ठा mscc_miim_dev *miim = bus->priv;
	u32 val;

	वापस mscc_पढ़ोl_poll_समयout(miim->regs + MSCC_MIIM_REG_STATUS, val,
				       !(val & MSCC_MIIM_STATUS_STAT_BUSY), 50,
				       10000);
पूर्ण

अटल पूर्णांक mscc_miim_रुको_pending(काष्ठा mii_bus *bus)
अणु
	काष्ठा mscc_miim_dev *miim = bus->priv;
	u32 val;

	वापस mscc_पढ़ोl_poll_समयout(miim->regs + MSCC_MIIM_REG_STATUS, val,
				       !(val & MSCC_MIIM_STATUS_STAT_PENDING),
				       50, 10000);
पूर्ण

अटल पूर्णांक mscc_miim_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा mscc_miim_dev *miim = bus->priv;
	u32 val;
	पूर्णांक ret;

	ret = mscc_miim_रुको_pending(bus);
	अगर (ret)
		जाओ out;

	ग_लिखोl(MSCC_MIIM_CMD_VLD | (mii_id << MSCC_MIIM_CMD_PHYAD_SHIFT) |
	       (regnum << MSCC_MIIM_CMD_REGAD_SHIFT) | MSCC_MIIM_CMD_OPR_READ,
	       miim->regs + MSCC_MIIM_REG_CMD);

	ret = mscc_miim_रुको_पढ़ोy(bus);
	अगर (ret)
		जाओ out;

	val = पढ़ोl(miim->regs + MSCC_MIIM_REG_DATA);
	अगर (val & MSCC_MIIM_DATA_ERROR) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = val & 0xFFFF;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक mscc_miim_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id,
			   पूर्णांक regnum, u16 value)
अणु
	काष्ठा mscc_miim_dev *miim = bus->priv;
	पूर्णांक ret;

	ret = mscc_miim_रुको_pending(bus);
	अगर (ret < 0)
		जाओ out;

	ग_लिखोl(MSCC_MIIM_CMD_VLD | (mii_id << MSCC_MIIM_CMD_PHYAD_SHIFT) |
	       (regnum << MSCC_MIIM_CMD_REGAD_SHIFT) |
	       (value << MSCC_MIIM_CMD_WRDATA_SHIFT) |
	       MSCC_MIIM_CMD_OPR_WRITE,
	       miim->regs + MSCC_MIIM_REG_CMD);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक mscc_miim_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा mscc_miim_dev *miim = bus->priv;

	अगर (miim->phy_regs) अणु
		ग_लिखोl(0, miim->phy_regs + MSCC_PHY_REG_PHY_CFG);
		ग_लिखोl(0x1ff, miim->phy_regs + MSCC_PHY_REG_PHY_CFG);
		mdelay(500);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mscc_miim_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा mii_bus *bus;
	काष्ठा mscc_miim_dev *dev;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	bus = devm_mdiobus_alloc_size(&pdev->dev, माप(*dev));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "mscc_miim";
	bus->पढ़ो = mscc_miim_पढ़ो;
	bus->ग_लिखो = mscc_miim_ग_लिखो;
	bus->reset = mscc_miim_reset;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	bus->parent = &pdev->dev;

	dev = bus->priv;
	dev->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dev->regs)) अणु
		dev_err(&pdev->dev, "Unable to map MIIM registers\n");
		वापस PTR_ERR(dev->regs);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		dev->phy_regs = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(dev->phy_regs)) अणु
			dev_err(&pdev->dev, "Unable to map internal phy registers\n");
			वापस PTR_ERR(dev->phy_regs);
		पूर्ण
	पूर्ण

	ret = of_mdiobus_रेजिस्टर(bus, pdev->dev.of_node);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot register MDIO bus (%d)\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;
पूर्ण

अटल पूर्णांक mscc_miim_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mscc_miim_match[] = अणु
	अणु .compatible = "mscc,ocelot-miim" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mscc_miim_match);

अटल काष्ठा platक्रमm_driver mscc_miim_driver = अणु
	.probe = mscc_miim_probe,
	.हटाओ = mscc_miim_हटाओ,
	.driver = अणु
		.name = "mscc-miim",
		.of_match_table = mscc_miim_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mscc_miim_driver);

MODULE_DESCRIPTION("Microsemi MIIM driver");
MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_LICENSE("Dual MIT/GPL");
