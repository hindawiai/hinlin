<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Broadcom UniMAC MDIO bus controller driver
 *
 * Copyright (C) 2014-2017 Broadcom
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_data/mdio-bcm-unimac.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>

#घोषणा MDIO_CMD		0x00
#घोषणा  MDIO_START_BUSY	(1 << 29)
#घोषणा  MDIO_READ_FAIL		(1 << 28)
#घोषणा  MDIO_RD		(2 << 26)
#घोषणा  MDIO_WR		(1 << 26)
#घोषणा  MDIO_PMD_SHIFT		21
#घोषणा  MDIO_PMD_MASK		0x1F
#घोषणा  MDIO_REG_SHIFT		16
#घोषणा  MDIO_REG_MASK		0x1F

#घोषणा MDIO_CFG		0x04
#घोषणा  MDIO_C22		(1 << 0)
#घोषणा  MDIO_C45		0
#घोषणा  MDIO_CLK_DIV_SHIFT	4
#घोषणा  MDIO_CLK_DIV_MASK	0x3F
#घोषणा  MDIO_SUPP_PREAMBLE	(1 << 12)

काष्ठा unimac_mdio_priv अणु
	काष्ठा mii_bus		*mii_bus;
	व्योम __iomem		*base;
	पूर्णांक (*रुको_func)	(व्योम *रुको_func_data);
	व्योम			*रुको_func_data;
	काष्ठा clk		*clk;
	u32			clk_freq;
पूर्ण;

अटल अंतरभूत u32 unimac_mdio_पढ़ोl(काष्ठा unimac_mdio_priv *priv, u32 offset)
अणु
	/* MIPS chips strapped क्रम BE will स्वतःmagically configure the
	 * peripheral रेजिस्टरs क्रम CPU-native byte order.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(priv->base + offset);
	अन्यथा
		वापस पढ़ोl_relaxed(priv->base + offset);
पूर्ण

अटल अंतरभूत व्योम unimac_mdio_ग_लिखोl(काष्ठा unimac_mdio_priv *priv, u32 val,
				      u32 offset)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(val, priv->base + offset);
	अन्यथा
		ग_लिखोl_relaxed(val, priv->base + offset);
पूर्ण

अटल अंतरभूत व्योम unimac_mdio_start(काष्ठा unimac_mdio_priv *priv)
अणु
	u32 reg;

	reg = unimac_mdio_पढ़ोl(priv, MDIO_CMD);
	reg |= MDIO_START_BUSY;
	unimac_mdio_ग_लिखोl(priv, reg, MDIO_CMD);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक unimac_mdio_busy(काष्ठा unimac_mdio_priv *priv)
अणु
	वापस unimac_mdio_पढ़ोl(priv, MDIO_CMD) & MDIO_START_BUSY;
पूर्ण

अटल पूर्णांक unimac_mdio_poll(व्योम *रुको_func_data)
अणु
	काष्ठा unimac_mdio_priv *priv = रुको_func_data;
	अचिन्हित पूर्णांक समयout = 1000;

	करो अणु
		अगर (!unimac_mdio_busy(priv))
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण जबतक (--समयout);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक unimac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा unimac_mdio_priv *priv = bus->priv;
	पूर्णांक ret;
	u32 cmd;

	/* Prepare the पढ़ो operation */
	cmd = MDIO_RD | (phy_id << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT);
	unimac_mdio_ग_लिखोl(priv, cmd, MDIO_CMD);

	/* Start MDIO transaction */
	unimac_mdio_start(priv);

	ret = priv->रुको_func(priv->रुको_func_data);
	अगर (ret)
		वापस ret;

	cmd = unimac_mdio_पढ़ोl(priv, MDIO_CMD);

	/* Some broken devices are known not to release the line during
	 * turn-around, e.g: Broadcom BCM53125 बाह्यal चयनes, so check क्रम
	 * that condition here and ignore the MDIO controller पढ़ो failure
	 * indication.
	 */
	अगर (!(bus->phy_ignore_ta_mask & 1 << phy_id) && (cmd & MDIO_READ_FAIL))
		वापस -EIO;

	वापस cmd & 0xffff;
पूर्ण

अटल पूर्णांक unimac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id,
			     पूर्णांक reg, u16 val)
अणु
	काष्ठा unimac_mdio_priv *priv = bus->priv;
	u32 cmd;

	/* Prepare the ग_लिखो operation */
	cmd = MDIO_WR | (phy_id << MDIO_PMD_SHIFT) |
		(reg << MDIO_REG_SHIFT) | (0xffff & val);
	unimac_mdio_ग_लिखोl(priv, cmd, MDIO_CMD);

	unimac_mdio_start(priv);

	वापस priv->रुको_func(priv->रुको_func_data);
पूर्ण

/* Workaround क्रम पूर्णांकegrated BCM7xxx Gigabit PHYs which have a problem with
 * their पूर्णांकernal MDIO management controller making them fail to successfully
 * be पढ़ो from or written to क्रम the first transaction.  We insert a dummy
 * BMSR पढ़ो here to make sure that phy_get_device() and get_phy_id() can
 * correctly पढ़ो the PHY MII_PHYSID1/2 रेजिस्टरs and successfully रेजिस्टर a
 * PHY device क्रम this peripheral.
 *
 * Once the PHY driver is रेजिस्टरed, we can workaround subsequent पढ़ोs from
 * there (e.g: during प्रणाली-wide घातer management).
 *
 * bus->reset is invoked beक्रमe mdiobus_scan during mdiobus_रेजिस्टर and is
 * thereक्रमe the right location to stick that workaround. Since we करो not want
 * to पढ़ो from non-existing PHYs, we either use bus->phy_mask or करो a manual
 * Device Tree scan to limit the search area.
 */
अटल पूर्णांक unimac_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा device_node *np = bus->dev.of_node;
	काष्ठा device_node *child;
	u32 पढ़ो_mask = 0;
	पूर्णांक addr;

	अगर (!np) अणु
		पढ़ो_mask = ~bus->phy_mask;
	पूर्ण अन्यथा अणु
		क्रम_each_available_child_of_node(np, child) अणु
			addr = of_mdio_parse_addr(&bus->dev, child);
			अगर (addr < 0)
				जारी;

			पढ़ो_mask |= 1 << addr;
		पूर्ण
	पूर्ण

	क्रम (addr = 0; addr < PHY_MAX_ADDR; addr++) अणु
		अगर (पढ़ो_mask & 1 << addr) अणु
			dev_dbg(&bus->dev, "Workaround for PHY @ %d\n", addr);
			mdiobus_पढ़ो(bus, addr, MII_BMSR);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम unimac_mdio_clk_set(काष्ठा unimac_mdio_priv *priv)
अणु
	अचिन्हित दीर्घ rate;
	u32 reg, भाग;

	/* Keep the hardware शेष values */
	अगर (!priv->clk_freq)
		वापस;

	अगर (!priv->clk)
		rate = 250000000;
	अन्यथा
		rate = clk_get_rate(priv->clk);

	भाग = (rate / (2 * priv->clk_freq)) - 1;
	अगर (भाग & ~MDIO_CLK_DIV_MASK) अणु
		pr_warn("Incorrect MDIO clock frequency, ignoring\n");
		वापस;
	पूर्ण

	/* The MDIO घड़ी is the reference घड़ी (typicaly 250Mhz) भागided by
	 * 2 x (MDIO_CLK_DIV + 1)
	 */
	reg = unimac_mdio_पढ़ोl(priv, MDIO_CFG);
	reg &= ~(MDIO_CLK_DIV_MASK << MDIO_CLK_DIV_SHIFT);
	reg |= भाग << MDIO_CLK_DIV_SHIFT;
	unimac_mdio_ग_लिखोl(priv, reg, MDIO_CFG);
पूर्ण

अटल पूर्णांक unimac_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा unimac_mdio_pdata *pdata = pdev->dev.platक्रमm_data;
	काष्ठा unimac_mdio_priv *priv;
	काष्ठा device_node *np;
	काष्ठा mii_bus *bus;
	काष्ठा resource *r;
	पूर्णांक ret;

	np = pdev->dev.of_node;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -EINVAL;

	/* Just ioremap, as this MDIO block is usually पूर्णांकegrated पूर्णांकo an
	 * Ethernet MAC controller रेजिस्टर range
	 */
	priv->base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!priv->base) अणु
		dev_err(&pdev->dev, "failed to remap register\n");
		वापस -ENOMEM;
	पूर्ण

	priv->clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &priv->clk_freq))
		priv->clk_freq = 0;

	unimac_mdio_clk_set(priv);

	priv->mii_bus = mdiobus_alloc();
	अगर (!priv->mii_bus) अणु
		ret = -ENOMEM;
		जाओ out_clk_disable;
	पूर्ण

	bus = priv->mii_bus;
	bus->priv = priv;
	अगर (pdata) अणु
		bus->name = pdata->bus_name;
		priv->रुको_func = pdata->रुको_func;
		priv->रुको_func_data = pdata->रुको_func_data;
		bus->phy_mask = ~pdata->phy_mask;
	पूर्ण अन्यथा अणु
		bus->name = "unimac MII bus";
		priv->रुको_func_data = priv;
		priv->रुको_func = unimac_mdio_poll;
	पूर्ण
	bus->parent = &pdev->dev;
	bus->पढ़ो = unimac_mdio_पढ़ो;
	bus->ग_लिखो = unimac_mdio_ग_लिखो;
	bus->reset = unimac_mdio_reset;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);

	ret = of_mdiobus_रेजिस्टर(bus, np);
	अगर (ret) अणु
		dev_err(&pdev->dev, "MDIO bus registration failed\n");
		जाओ out_mdio_मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Broadcom UniMAC MDIO bus\n");

	वापस 0;

out_mdio_मुक्त:
	mdiobus_मुक्त(bus);
out_clk_disable:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक unimac_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा unimac_mdio_priv *priv = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(priv->mii_bus);
	mdiobus_मुक्त(priv->mii_bus);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused unimac_mdio_suspend(काष्ठा device *d)
अणु
	काष्ठा unimac_mdio_priv *priv = dev_get_drvdata(d);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused unimac_mdio_resume(काष्ठा device *d)
अणु
	काष्ठा unimac_mdio_priv *priv = dev_get_drvdata(d);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	unimac_mdio_clk_set(priv);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(unimac_mdio_pm_ops,
			 unimac_mdio_suspend, unimac_mdio_resume);

अटल स्थिर काष्ठा of_device_id unimac_mdio_ids[] = अणु
	अणु .compatible = "brcm,genet-mdio-v5", पूर्ण,
	अणु .compatible = "brcm,genet-mdio-v4", पूर्ण,
	अणु .compatible = "brcm,genet-mdio-v3", पूर्ण,
	अणु .compatible = "brcm,genet-mdio-v2", पूर्ण,
	अणु .compatible = "brcm,genet-mdio-v1", पूर्ण,
	अणु .compatible = "brcm,unimac-mdio", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, unimac_mdio_ids);

अटल काष्ठा platक्रमm_driver unimac_mdio_driver = अणु
	.driver = अणु
		.name = UNIMAC_MDIO_DRV_NAME,
		.of_match_table = unimac_mdio_ids,
		.pm = &unimac_mdio_pm_ops,
	पूर्ण,
	.probe	= unimac_mdio_probe,
	.हटाओ	= unimac_mdio_हटाओ,
पूर्ण;
module_platक्रमm_driver(unimac_mdio_driver);

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom UniMAC MDIO bus controller");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" UNIMAC_MDIO_DRV_NAME);
