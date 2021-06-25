<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  STMMAC Ethernet Driver -- MDIO bus implementation
  Provides Bus पूर्णांकerface क्रम MII रेजिस्टरs

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Carl Shaw <carl.shaw@st.com>
  Maपूर्णांकainer: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mii.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/phy.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

#समावेश "dwxgmac2.h"
#समावेश "stmmac.h"

#घोषणा MII_BUSY 0x00000001
#घोषणा MII_WRITE 0x00000002
#घोषणा MII_DATA_MASK GENMASK(15, 0)

/* GMAC4 defines */
#घोषणा MII_GMAC4_GOC_SHIFT		2
#घोषणा MII_GMAC4_REG_ADDR_SHIFT	16
#घोषणा MII_GMAC4_WRITE			(1 << MII_GMAC4_GOC_SHIFT)
#घोषणा MII_GMAC4_READ			(3 << MII_GMAC4_GOC_SHIFT)
#घोषणा MII_GMAC4_C45E			BIT(1)

/* XGMAC defines */
#घोषणा MII_XGMAC_SADDR			BIT(18)
#घोषणा MII_XGMAC_CMD_SHIFT		16
#घोषणा MII_XGMAC_WRITE			(1 << MII_XGMAC_CMD_SHIFT)
#घोषणा MII_XGMAC_READ			(3 << MII_XGMAC_CMD_SHIFT)
#घोषणा MII_XGMAC_BUSY			BIT(22)
#घोषणा MII_XGMAC_MAX_C22ADDR		3
#घोषणा MII_XGMAC_C22P_MASK		GENMASK(MII_XGMAC_MAX_C22ADDR, 0)
#घोषणा MII_XGMAC_PA_SHIFT		16
#घोषणा MII_XGMAC_DA_SHIFT		21

अटल पूर्णांक sपंचांगmac_xgmac2_c45_क्रमmat(काष्ठा sपंचांगmac_priv *priv, पूर्णांक phyaddr,
				    पूर्णांक phyreg, u32 *hw_addr)
अणु
	u32 पंचांगp;

	/* Set port as Clause 45 */
	पंचांगp = पढ़ोl(priv->ioaddr + XGMAC_MDIO_C22P);
	पंचांगp &= ~BIT(phyaddr);
	ग_लिखोl(पंचांगp, priv->ioaddr + XGMAC_MDIO_C22P);

	*hw_addr = (phyaddr << MII_XGMAC_PA_SHIFT) | (phyreg & 0xffff);
	*hw_addr |= (phyreg >> MII_DEVADDR_C45_SHIFT) << MII_XGMAC_DA_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_xgmac2_c22_क्रमmat(काष्ठा sपंचांगmac_priv *priv, पूर्णांक phyaddr,
				    पूर्णांक phyreg, u32 *hw_addr)
अणु
	u32 पंचांगp;

	/* HW करोes not support C22 addr >= 4 */
	अगर (phyaddr > MII_XGMAC_MAX_C22ADDR)
		वापस -ENODEV;

	/* Set port as Clause 22 */
	पंचांगp = पढ़ोl(priv->ioaddr + XGMAC_MDIO_C22P);
	पंचांगp &= ~MII_XGMAC_C22P_MASK;
	पंचांगp |= BIT(phyaddr);
	ग_लिखोl(पंचांगp, priv->ioaddr + XGMAC_MDIO_C22P);

	*hw_addr = (phyaddr << MII_XGMAC_PA_SHIFT) | (phyreg & 0x1f);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_xgmac2_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक phyreg)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक mii_address = priv->hw->mii.addr;
	अचिन्हित पूर्णांक mii_data = priv->hw->mii.data;
	u32 पंचांगp, addr, value = MII_XGMAC_BUSY;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस ret;
	पूर्ण

	/* Wait until any existing MII operation is complete */
	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_data, पंचांगp,
			       !(पंचांगp & MII_XGMAC_BUSY), 100, 10000)) अणु
		ret = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	अगर (phyreg & MII_ADDR_C45) अणु
		phyreg &= ~MII_ADDR_C45;

		ret = sपंचांगmac_xgmac2_c45_क्रमmat(priv, phyaddr, phyreg, &addr);
		अगर (ret)
			जाओ err_disable_clks;
	पूर्ण अन्यथा अणु
		ret = sपंचांगmac_xgmac2_c22_क्रमmat(priv, phyaddr, phyreg, &addr);
		अगर (ret)
			जाओ err_disable_clks;

		value |= MII_XGMAC_SADDR;
	पूर्ण

	value |= (priv->clk_csr << priv->hw->mii.clk_csr_shअगरt)
		& priv->hw->mii.clk_csr_mask;
	value |= MII_XGMAC_READ;

	/* Wait until any existing MII operation is complete */
	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_data, पंचांगp,
			       !(पंचांगp & MII_XGMAC_BUSY), 100, 10000)) अणु
		ret = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	/* Set the MII address रेजिस्टर to पढ़ो */
	ग_लिखोl(addr, priv->ioaddr + mii_address);
	ग_लिखोl(value, priv->ioaddr + mii_data);

	/* Wait until any existing MII operation is complete */
	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_data, पंचांगp,
			       !(पंचांगp & MII_XGMAC_BUSY), 100, 10000)) अणु
		ret = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	/* Read the data from the MII data रेजिस्टर */
	ret = (पूर्णांक)पढ़ोl(priv->ioaddr + mii_data) & GENMASK(15, 0);

err_disable_clks:
	pm_runसमय_put(priv->device);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_xgmac2_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr,
				    पूर्णांक phyreg, u16 phydata)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक mii_address = priv->hw->mii.addr;
	अचिन्हित पूर्णांक mii_data = priv->hw->mii.data;
	u32 addr, पंचांगp, value = MII_XGMAC_BUSY;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस ret;
	पूर्ण

	/* Wait until any existing MII operation is complete */
	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_data, पंचांगp,
			       !(पंचांगp & MII_XGMAC_BUSY), 100, 10000)) अणु
		ret = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	अगर (phyreg & MII_ADDR_C45) अणु
		phyreg &= ~MII_ADDR_C45;

		ret = sपंचांगmac_xgmac2_c45_क्रमmat(priv, phyaddr, phyreg, &addr);
		अगर (ret)
			जाओ err_disable_clks;
	पूर्ण अन्यथा अणु
		ret = sपंचांगmac_xgmac2_c22_क्रमmat(priv, phyaddr, phyreg, &addr);
		अगर (ret)
			जाओ err_disable_clks;

		value |= MII_XGMAC_SADDR;
	पूर्ण

	value |= (priv->clk_csr << priv->hw->mii.clk_csr_shअगरt)
		& priv->hw->mii.clk_csr_mask;
	value |= phydata;
	value |= MII_XGMAC_WRITE;

	/* Wait until any existing MII operation is complete */
	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_data, पंचांगp,
			       !(पंचांगp & MII_XGMAC_BUSY), 100, 10000)) अणु
		ret = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	/* Set the MII address रेजिस्टर to ग_लिखो */
	ग_लिखोl(addr, priv->ioaddr + mii_address);
	ग_लिखोl(value, priv->ioaddr + mii_data);

	/* Wait until any existing MII operation is complete */
	ret = पढ़ोl_poll_समयout(priv->ioaddr + mii_data, पंचांगp,
				 !(पंचांगp & MII_XGMAC_BUSY), 100, 10000);

err_disable_clks:
	pm_runसमय_put(priv->device);

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_mdio_पढ़ो
 * @bus: poपूर्णांकs to the mii_bus काष्ठाure
 * @phyaddr: MII addr
 * @phyreg: MII reg
 * Description: it पढ़ोs data from the MII रेजिस्टर from within the phy device.
 * For the 7111 GMAC, we must set the bit 0 in the MII address रेजिस्टर जबतक
 * accessing the PHY रेजिस्टरs.
 * Fortunately, it seems this has no drawback क्रम the 7109 MAC.
 */
अटल पूर्णांक sपंचांगmac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक phyreg)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक mii_address = priv->hw->mii.addr;
	अचिन्हित पूर्णांक mii_data = priv->hw->mii.data;
	u32 value = MII_BUSY;
	पूर्णांक data = 0;
	u32 v;

	data = pm_runसमय_get_sync(priv->device);
	अगर (data < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस data;
	पूर्ण

	value |= (phyaddr << priv->hw->mii.addr_shअगरt)
		& priv->hw->mii.addr_mask;
	value |= (phyreg << priv->hw->mii.reg_shअगरt) & priv->hw->mii.reg_mask;
	value |= (priv->clk_csr << priv->hw->mii.clk_csr_shअगरt)
		& priv->hw->mii.clk_csr_mask;
	अगर (priv->plat->has_gmac4) अणु
		value |= MII_GMAC4_READ;
		अगर (phyreg & MII_ADDR_C45) अणु
			value |= MII_GMAC4_C45E;
			value &= ~priv->hw->mii.reg_mask;
			value |= ((phyreg >> MII_DEVADDR_C45_SHIFT) <<
			       priv->hw->mii.reg_shअगरt) &
			       priv->hw->mii.reg_mask;

			data |= (phyreg & MII_REGADDR_C45_MASK) <<
				MII_GMAC4_REG_ADDR_SHIFT;
		पूर्ण
	पूर्ण

	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_address, v, !(v & MII_BUSY),
			       100, 10000)) अणु
		data = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	ग_लिखोl(data, priv->ioaddr + mii_data);
	ग_लिखोl(value, priv->ioaddr + mii_address);

	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_address, v, !(v & MII_BUSY),
			       100, 10000)) अणु
		data = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	/* Read the data from the MII data रेजिस्टर */
	data = (पूर्णांक)पढ़ोl(priv->ioaddr + mii_data) & MII_DATA_MASK;

err_disable_clks:
	pm_runसमय_put(priv->device);

	वापस data;
पूर्ण

/**
 * sपंचांगmac_mdio_ग_लिखो
 * @bus: poपूर्णांकs to the mii_bus काष्ठाure
 * @phyaddr: MII addr
 * @phyreg: MII reg
 * @phydata: phy data
 * Description: it ग_लिखोs the data पूर्णांकo the MII रेजिस्टर from within the device.
 */
अटल पूर्णांक sपंचांगmac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक phyreg,
			     u16 phydata)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक mii_address = priv->hw->mii.addr;
	अचिन्हित पूर्णांक mii_data = priv->hw->mii.data;
	पूर्णांक ret, data = phydata;
	u32 value = MII_BUSY;
	u32 v;

	ret = pm_runसमय_get_sync(priv->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->device);
		वापस ret;
	पूर्ण

	value |= (phyaddr << priv->hw->mii.addr_shअगरt)
		& priv->hw->mii.addr_mask;
	value |= (phyreg << priv->hw->mii.reg_shअगरt) & priv->hw->mii.reg_mask;

	value |= (priv->clk_csr << priv->hw->mii.clk_csr_shअगरt)
		& priv->hw->mii.clk_csr_mask;
	अगर (priv->plat->has_gmac4) अणु
		value |= MII_GMAC4_WRITE;
		अगर (phyreg & MII_ADDR_C45) अणु
			value |= MII_GMAC4_C45E;
			value &= ~priv->hw->mii.reg_mask;
			value |= ((phyreg >> MII_DEVADDR_C45_SHIFT) <<
			       priv->hw->mii.reg_shअगरt) &
			       priv->hw->mii.reg_mask;

			data |= (phyreg & MII_REGADDR_C45_MASK) <<
				MII_GMAC4_REG_ADDR_SHIFT;
		पूर्ण
	पूर्ण अन्यथा अणु
		value |= MII_WRITE;
	पूर्ण

	/* Wait until any existing MII operation is complete */
	अगर (पढ़ोl_poll_समयout(priv->ioaddr + mii_address, v, !(v & MII_BUSY),
			       100, 10000)) अणु
		ret = -EBUSY;
		जाओ err_disable_clks;
	पूर्ण

	/* Set the MII address रेजिस्टर to ग_लिखो */
	ग_लिखोl(data, priv->ioaddr + mii_data);
	ग_लिखोl(value, priv->ioaddr + mii_address);

	/* Wait until any existing MII operation is complete */
	ret = पढ़ोl_poll_समयout(priv->ioaddr + mii_address, v, !(v & MII_BUSY),
				 100, 10000);

err_disable_clks:
	pm_runसमय_put(priv->device);

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_mdio_reset
 * @bus: poपूर्णांकs to the mii_bus काष्ठाure
 * Description: reset the MII bus
 */
पूर्णांक sपंचांगmac_mdio_reset(काष्ठा mii_bus *bus)
अणु
#अगर IS_ENABLED(CONFIG_STMMAC_PLATFORM)
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक mii_address = priv->hw->mii.addr;

#अगर_घोषित CONFIG_OF
	अगर (priv->device->of_node) अणु
		काष्ठा gpio_desc *reset_gpio;
		u32 delays[3] = अणु 0, 0, 0 पूर्ण;

		reset_gpio = devm_gpiod_get_optional(priv->device,
						     "snps,reset",
						     GPIOD_OUT_LOW);
		अगर (IS_ERR(reset_gpio))
			वापस PTR_ERR(reset_gpio);

		device_property_पढ़ो_u32_array(priv->device,
					       "snps,reset-delays-us",
					       delays, ARRAY_SIZE(delays));

		अगर (delays[0])
			msleep(DIV_ROUND_UP(delays[0], 1000));

		gpiod_set_value_cansleep(reset_gpio, 1);
		अगर (delays[1])
			msleep(DIV_ROUND_UP(delays[1], 1000));

		gpiod_set_value_cansleep(reset_gpio, 0);
		अगर (delays[2])
			msleep(DIV_ROUND_UP(delays[2], 1000));
	पूर्ण
#पूर्ण_अगर

	/* This is a workaround क्रम problems with the STE101P PHY.
	 * It करोesn't complete its reset until at least one घड़ी cycle
	 * on MDC, so perक्रमm a dummy mdio पढ़ो. To be updated क्रम GMAC4
	 * अगर needed.
	 */
	अगर (!priv->plat->has_gmac4)
		ग_लिखोl(0, priv->ioaddr + mii_address);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * sपंचांगmac_mdio_रेजिस्टर
 * @ndev: net device काष्ठाure
 * Description: it रेजिस्टरs the MII bus
 */
पूर्णांक sपंचांगmac_mdio_रेजिस्टर(काष्ठा net_device *ndev)
अणु
	पूर्णांक err = 0;
	काष्ठा mii_bus *new_bus;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा sपंचांगmac_mdio_bus_data *mdio_bus_data = priv->plat->mdio_bus_data;
	काष्ठा device_node *mdio_node = priv->plat->mdio_node;
	काष्ठा device *dev = ndev->dev.parent;
	पूर्णांक addr, found, max_addr;

	अगर (!mdio_bus_data)
		वापस 0;

	new_bus = mdiobus_alloc();
	अगर (!new_bus)
		वापस -ENOMEM;

	अगर (mdio_bus_data->irqs)
		स_नकल(new_bus->irq, mdio_bus_data->irqs, माप(new_bus->irq));

	new_bus->name = "stmmac";

	अगर (priv->plat->has_gmac4)
		new_bus->probe_capabilities = MDIOBUS_C22_C45;

	अगर (priv->plat->has_xgmac) अणु
		new_bus->पढ़ो = &sपंचांगmac_xgmac2_mdio_पढ़ो;
		new_bus->ग_लिखो = &sपंचांगmac_xgmac2_mdio_ग_लिखो;

		/* Right now only C22 phys are supported */
		max_addr = MII_XGMAC_MAX_C22ADDR + 1;

		/* Check अगर DT specअगरied an unsupported phy addr */
		अगर (priv->plat->phy_addr > MII_XGMAC_MAX_C22ADDR)
			dev_err(dev, "Unsupported phy_addr (max=%d)\n",
					MII_XGMAC_MAX_C22ADDR);
	पूर्ण अन्यथा अणु
		new_bus->पढ़ो = &sपंचांगmac_mdio_पढ़ो;
		new_bus->ग_लिखो = &sपंचांगmac_mdio_ग_लिखो;
		max_addr = PHY_MAX_ADDR;
	पूर्ण

	अगर (mdio_bus_data->has_xpcs) अणु
		priv->hw->xpcs = mdio_xpcs_get_ops();
		अगर (!priv->hw->xpcs) अणु
			err = -ENODEV;
			जाओ bus_रेजिस्टर_fail;
		पूर्ण
	पूर्ण

	अगर (mdio_bus_data->needs_reset)
		new_bus->reset = &sपंचांगmac_mdio_reset;

	snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 new_bus->name, priv->plat->bus_id);
	new_bus->priv = ndev;
	new_bus->phy_mask = mdio_bus_data->phy_mask;
	new_bus->parent = priv->device;

	err = of_mdiobus_रेजिस्टर(new_bus, mdio_node);
	अगर (err != 0) अणु
		dev_err(dev, "Cannot register the MDIO bus\n");
		जाओ bus_रेजिस्टर_fail;
	पूर्ण

	/* Looks like we need a dummy पढ़ो क्रम XGMAC only and C45 PHYs */
	अगर (priv->plat->has_xgmac)
		sपंचांगmac_xgmac2_mdio_पढ़ो(new_bus, 0, MII_ADDR_C45);

	अगर (priv->plat->phy_node || mdio_node)
		जाओ bus_रेजिस्टर_करोne;

	found = 0;
	क्रम (addr = 0; addr < max_addr; addr++) अणु
		काष्ठा phy_device *phydev = mdiobus_get_phy(new_bus, addr);

		अगर (!phydev)
			जारी;

		/*
		 * If an IRQ was provided to be asचिन्हित after
		 * the bus probe, करो it here.
		 */
		अगर (!mdio_bus_data->irqs &&
		    (mdio_bus_data->probed_phy_irq > 0)) अणु
			new_bus->irq[addr] = mdio_bus_data->probed_phy_irq;
			phydev->irq = mdio_bus_data->probed_phy_irq;
		पूर्ण

		/*
		 * If we're going to bind the MAC to this PHY bus,
		 * and no PHY number was provided to the MAC,
		 * use the one probed here.
		 */
		अगर (priv->plat->phy_addr == -1)
			priv->plat->phy_addr = addr;

		phy_attached_info(phydev);
		found = 1;
	पूर्ण

	/* Try to probe the XPCS by scanning all addresses. */
	अगर (priv->hw->xpcs) अणु
		काष्ठा mdio_xpcs_args *xpcs = &priv->hw->xpcs_args;
		पूर्णांक ret, mode = priv->plat->phy_पूर्णांकerface;
		max_addr = PHY_MAX_ADDR;

		xpcs->bus = new_bus;

		क्रम (addr = 0; addr < max_addr; addr++) अणु
			xpcs->addr = addr;

			ret = sपंचांगmac_xpcs_probe(priv, xpcs, mode);
			अगर (!ret) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!found && !mdio_node) अणु
		dev_warn(dev, "No PHY found\n");
		mdiobus_unरेजिस्टर(new_bus);
		mdiobus_मुक्त(new_bus);
		वापस -ENODEV;
	पूर्ण

bus_रेजिस्टर_करोne:
	priv->mii = new_bus;

	वापस 0;

bus_रेजिस्टर_fail:
	mdiobus_मुक्त(new_bus);
	वापस err;
पूर्ण

/**
 * sपंचांगmac_mdio_unरेजिस्टर
 * @ndev: net device काष्ठाure
 * Description: it unरेजिस्टरs the MII bus
 */
पूर्णांक sपंचांगmac_mdio_unरेजिस्टर(काष्ठा net_device *ndev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	अगर (!priv->mii)
		वापस 0;

	mdiobus_unरेजिस्टर(priv->mii);
	priv->mii->priv = शून्य;
	mdiobus_मुक्त(priv->mii);
	priv->mii = शून्य;

	वापस 0;
पूर्ण
