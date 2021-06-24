<शैली गुरु>
/*
 * QorIQ 10G MDIO Controller
 *
 * Copyright 2012 Freescale Semiconductor, Inc.
 *
 * Authors: Andy Fleming <afleming@मुक्तscale.com>
 *          Timur Tabi <timur@मुक्तscale.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_mdपन.स>

/* Number of microseconds to रुको क्रम a रेजिस्टर to respond */
#घोषणा TIMEOUT	1000

काष्ठा tgec_mdio_controller अणु
	__be32	reserved[12];
	__be32	mdio_stat;	/* MDIO configuration and status */
	__be32	mdio_ctl;	/* MDIO control */
	__be32	mdio_data;	/* MDIO data */
	__be32	mdio_addr;	/* MDIO address */
पूर्ण __packed;

#घोषणा MDIO_STAT_ENC		BIT(6)
#घोषणा MDIO_STAT_CLKDIV(x)	(((x>>1) & 0xff) << 8)
#घोषणा MDIO_STAT_BSY		BIT(0)
#घोषणा MDIO_STAT_RD_ER		BIT(1)
#घोषणा MDIO_CTL_DEV_ADDR(x) 	(x & 0x1f)
#घोषणा MDIO_CTL_PORT_ADDR(x)	((x & 0x1f) << 5)
#घोषणा MDIO_CTL_PRE_DIS	BIT(10)
#घोषणा MDIO_CTL_SCAN_EN	BIT(11)
#घोषणा MDIO_CTL_POST_INC	BIT(14)
#घोषणा MDIO_CTL_READ		BIT(15)

#घोषणा MDIO_DATA(x)		(x & 0xffff)
#घोषणा MDIO_DATA_BSY		BIT(31)

काष्ठा mdio_fsl_priv अणु
	काष्ठा	tgec_mdio_controller __iomem *mdio_base;
	bool	is_little_endian;
	bool	has_a011043;
पूर्ण;

अटल u32 xgmac_पढ़ो32(व्योम __iomem *regs,
			bool is_little_endian)
अणु
	अगर (is_little_endian)
		वापस ioपढ़ो32(regs);
	अन्यथा
		वापस ioपढ़ो32be(regs);
पूर्ण

अटल व्योम xgmac_ग_लिखो32(u32 value,
			  व्योम __iomem *regs,
			  bool is_little_endian)
अणु
	अगर (is_little_endian)
		ioग_लिखो32(value, regs);
	अन्यथा
		ioग_लिखो32be(value, regs);
पूर्ण

/*
 * Wait until the MDIO bus is मुक्त
 */
अटल पूर्णांक xgmac_रुको_until_मुक्त(काष्ठा device *dev,
				 काष्ठा tgec_mdio_controller __iomem *regs,
				 bool is_little_endian)
अणु
	अचिन्हित पूर्णांक समयout;

	/* Wait till the bus is मुक्त */
	समयout = TIMEOUT;
	जबतक ((xgmac_पढ़ो32(&regs->mdio_stat, is_little_endian) &
		MDIO_STAT_BSY) && समयout) अणु
		cpu_relax();
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		dev_err(dev, "timeout waiting for bus to be free\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wait till the MDIO पढ़ो or ग_लिखो operation is complete
 */
अटल पूर्णांक xgmac_रुको_until_करोne(काष्ठा device *dev,
				 काष्ठा tgec_mdio_controller __iomem *regs,
				 bool is_little_endian)
अणु
	अचिन्हित पूर्णांक समयout;

	/* Wait till the MDIO ग_लिखो is complete */
	समयout = TIMEOUT;
	जबतक ((xgmac_पढ़ो32(&regs->mdio_stat, is_little_endian) &
		MDIO_STAT_BSY) && समयout) अणु
		cpu_relax();
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		dev_err(dev, "timeout waiting for operation to complete\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write value to the PHY क्रम this device to the रेजिस्टर at regnum,रुकोing
 * until the ग_लिखो is करोne beक्रमe it वापसs.  All PHY configuration has to be
 * करोne through the TSEC1 MIIM regs.
 */
अटल पूर्णांक xgmac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum, u16 value)
अणु
	काष्ठा mdio_fsl_priv *priv = (काष्ठा mdio_fsl_priv *)bus->priv;
	काष्ठा tgec_mdio_controller __iomem *regs = priv->mdio_base;
	uपूर्णांक16_t dev_addr;
	u32 mdio_ctl, mdio_stat;
	पूर्णांक ret;
	bool endian = priv->is_little_endian;

	mdio_stat = xgmac_पढ़ो32(&regs->mdio_stat, endian);
	अगर (regnum & MII_ADDR_C45) अणु
		/* Clause 45 (ie 10G) */
		dev_addr = (regnum >> 16) & 0x1f;
		mdio_stat |= MDIO_STAT_ENC;
	पूर्ण अन्यथा अणु
		/* Clause 22 (ie 1G) */
		dev_addr = regnum & 0x1f;
		mdio_stat &= ~MDIO_STAT_ENC;
	पूर्ण

	xgmac_ग_लिखो32(mdio_stat, &regs->mdio_stat, endian);

	ret = xgmac_रुको_until_मुक्त(&bus->dev, regs, endian);
	अगर (ret)
		वापस ret;

	/* Set the port and dev addr */
	mdio_ctl = MDIO_CTL_PORT_ADDR(phy_id) | MDIO_CTL_DEV_ADDR(dev_addr);
	xgmac_ग_लिखो32(mdio_ctl, &regs->mdio_ctl, endian);

	/* Set the रेजिस्टर address */
	अगर (regnum & MII_ADDR_C45) अणु
		xgmac_ग_लिखो32(regnum & 0xffff, &regs->mdio_addr, endian);

		ret = xgmac_रुको_until_मुक्त(&bus->dev, regs, endian);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Write the value to the रेजिस्टर */
	xgmac_ग_लिखो32(MDIO_DATA(value), &regs->mdio_data, endian);

	ret = xgmac_रुको_until_करोne(&bus->dev, regs, endian);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Reads from रेजिस्टर regnum in the PHY क्रम device dev, वापसing the value.
 * Clears miimcom first.  All PHY configuration has to be करोne through the
 * TSEC1 MIIM regs.
 */
अटल पूर्णांक xgmac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा mdio_fsl_priv *priv = (काष्ठा mdio_fsl_priv *)bus->priv;
	काष्ठा tgec_mdio_controller __iomem *regs = priv->mdio_base;
	uपूर्णांक16_t dev_addr;
	uपूर्णांक32_t mdio_stat;
	uपूर्णांक32_t mdio_ctl;
	uपूर्णांक16_t value;
	पूर्णांक ret;
	bool endian = priv->is_little_endian;

	mdio_stat = xgmac_पढ़ो32(&regs->mdio_stat, endian);
	अगर (regnum & MII_ADDR_C45) अणु
		dev_addr = (regnum >> 16) & 0x1f;
		mdio_stat |= MDIO_STAT_ENC;
	पूर्ण अन्यथा अणु
		dev_addr = regnum & 0x1f;
		mdio_stat &= ~MDIO_STAT_ENC;
	पूर्ण

	xgmac_ग_लिखो32(mdio_stat, &regs->mdio_stat, endian);

	ret = xgmac_रुको_until_मुक्त(&bus->dev, regs, endian);
	अगर (ret)
		वापस ret;

	/* Set the Port and Device Addrs */
	mdio_ctl = MDIO_CTL_PORT_ADDR(phy_id) | MDIO_CTL_DEV_ADDR(dev_addr);
	xgmac_ग_लिखो32(mdio_ctl, &regs->mdio_ctl, endian);

	/* Set the रेजिस्टर address */
	अगर (regnum & MII_ADDR_C45) अणु
		xgmac_ग_लिखो32(regnum & 0xffff, &regs->mdio_addr, endian);

		ret = xgmac_रुको_until_मुक्त(&bus->dev, regs, endian);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Initiate the पढ़ो */
	xgmac_ग_लिखो32(mdio_ctl | MDIO_CTL_READ, &regs->mdio_ctl, endian);

	ret = xgmac_रुको_until_करोne(&bus->dev, regs, endian);
	अगर (ret)
		वापस ret;

	/* Return all Fs अगर nothing was there */
	अगर ((xgmac_पढ़ो32(&regs->mdio_stat, endian) & MDIO_STAT_RD_ER) &&
	    !priv->has_a011043) अणु
		dev_dbg(&bus->dev,
			"Error while reading PHY%d reg at %d.%hhu\n",
			phy_id, dev_addr, regnum);
		वापस 0xffff;
	पूर्ण

	value = xgmac_पढ़ो32(&regs->mdio_data, endian) & 0xffff;
	dev_dbg(&bus->dev, "read %04x\n", value);

	वापस value;
पूर्ण

अटल पूर्णांक xgmac_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mii_bus *bus;
	काष्ठा resource *res;
	काष्ठा mdio_fsl_priv *priv;
	पूर्णांक ret;

	/* In DPAA-1, MDIO is one of the many FMan sub-devices. The FMan
	 * defines a रेजिस्टर space that spans a large area, covering all the
	 * subdevice areas. Thereक्रमe, MDIO cannot claim exclusive access to
	 * this रेजिस्टर area.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "could not obtain address\n");
		वापस -EINVAL;
	पूर्ण

	bus = mdiobus_alloc_size(माप(काष्ठा mdio_fsl_priv));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "Freescale XGMAC MDIO Bus";
	bus->पढ़ो = xgmac_mdio_पढ़ो;
	bus->ग_लिखो = xgmac_mdio_ग_लिखो;
	bus->parent = &pdev->dev;
	bus->probe_capabilities = MDIOBUS_C22_C45;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%pa", &res->start);

	/* Set the PHY base address */
	priv = bus->priv;
	priv->mdio_base = ioremap(res->start, resource_size(res));
	अगर (!priv->mdio_base) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	priv->is_little_endian = device_property_पढ़ो_bool(&pdev->dev,
							   "little-endian");

	priv->has_a011043 = device_property_पढ़ो_bool(&pdev->dev,
						      "fsl,erratum-a011043");

	ret = of_mdiobus_रेजिस्टर(bus, np);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot register MDIO bus\n");
		जाओ err_registration;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;

err_registration:
	iounmap(priv->mdio_base);

err_ioremap:
	mdiobus_मुक्त(bus);

	वापस ret;
पूर्ण

अटल पूर्णांक xgmac_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus);
	iounmap(bus->priv);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgmac_mdio_match[] = अणु
	अणु
		.compatible = "fsl,fman-xmdio",
	पूर्ण,
	अणु
		.compatible = "fsl,fman-memac-mdio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgmac_mdio_match);

अटल स्थिर काष्ठा acpi_device_id xgmac_acpi_match[] = अणु
	अणु "NXP0006" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgmac_acpi_match);

अटल काष्ठा platक्रमm_driver xgmac_mdio_driver = अणु
	.driver = अणु
		.name = "fsl-fman_xmdio",
		.of_match_table = xgmac_mdio_match,
		.acpi_match_table = xgmac_acpi_match,
	पूर्ण,
	.probe = xgmac_mdio_probe,
	.हटाओ = xgmac_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(xgmac_mdio_driver);

MODULE_DESCRIPTION("Freescale QorIQ 10G MDIO Controller");
MODULE_LICENSE("GPL v2");
