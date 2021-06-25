<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MDIO bus driver क्रम the Xilinx Axi Ethernet device
 *
 * Copyright (c) 2009 Secret Lab Technologies, Ltd.
 * Copyright (c) 2010 - 2011 Michal Simek <monstr@monstr.eu>
 * Copyright (c) 2010 - 2011 PetaLogix
 * Copyright (c) 2019 SED Systems, a भागision of Calian Ltd.
 * Copyright (c) 2010 - 2012 Xilinx, Inc. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/iopoll.h>

#समावेश "xilinx_axienet.h"

#घोषणा MAX_MDIO_FREQ		2500000 /* 2.5 MHz */
#घोषणा DEFAULT_HOST_CLOCK	150000000 /* 150 MHz */

/* Wait till MDIO पूर्णांकerface is पढ़ोy to accept a new transaction.*/
अटल पूर्णांक axienet_mdio_रुको_until_पढ़ोy(काष्ठा axienet_local *lp)
अणु
	u32 val;

	वापस पढ़ोx_poll_समयout(axinet_ior_पढ़ो_mcr, lp,
				  val, val & XAE_MDIO_MCR_READY_MASK,
				  1, 20000);
पूर्ण

/* Enable the MDIO MDC. Called prior to a पढ़ो/ग_लिखो operation */
अटल व्योम axienet_mdio_mdc_enable(काष्ठा axienet_local *lp)
अणु
	axienet_iow(lp, XAE_MDIO_MC_OFFSET,
		    ((u32)lp->mii_clk_भाग | XAE_MDIO_MC_MDIOEN_MASK));
पूर्ण

/* Disable the MDIO MDC. Called after a पढ़ो/ग_लिखो operation*/
अटल व्योम axienet_mdio_mdc_disable(काष्ठा axienet_local *lp)
अणु
	u32 mc_reg;

	mc_reg = axienet_ior(lp, XAE_MDIO_MC_OFFSET);
	axienet_iow(lp, XAE_MDIO_MC_OFFSET,
		    (mc_reg & ~XAE_MDIO_MC_MDIOEN_MASK));
पूर्ण

/**
 * axienet_mdio_पढ़ो - MDIO पूर्णांकerface पढ़ो function
 * @bus:	Poपूर्णांकer to mii bus काष्ठाure
 * @phy_id:	Address of the PHY device
 * @reg:	PHY रेजिस्टर to पढ़ो
 *
 * Return:	The रेजिस्टर contents on success, -ETIMEDOUT on a समयout
 *
 * Reads the contents of the requested रेजिस्टर from the requested PHY
 * address by first writing the details पूर्णांकo MCR रेजिस्टर. After a जबतक
 * the रेजिस्टर MRD is पढ़ो to obtain the PHY रेजिस्टर content.
 */
अटल पूर्णांक axienet_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	u32 rc;
	पूर्णांक ret;
	काष्ठा axienet_local *lp = bus->priv;

	axienet_mdio_mdc_enable(lp);

	ret = axienet_mdio_रुको_until_पढ़ोy(lp);
	अगर (ret < 0) अणु
		axienet_mdio_mdc_disable(lp);
		वापस ret;
	पूर्ण

	axienet_iow(lp, XAE_MDIO_MCR_OFFSET,
		    (((phy_id << XAE_MDIO_MCR_PHYAD_SHIFT) &
		      XAE_MDIO_MCR_PHYAD_MASK) |
		     ((reg << XAE_MDIO_MCR_REGAD_SHIFT) &
		      XAE_MDIO_MCR_REGAD_MASK) |
		     XAE_MDIO_MCR_INITIATE_MASK |
		     XAE_MDIO_MCR_OP_READ_MASK));

	ret = axienet_mdio_रुको_until_पढ़ोy(lp);
	अगर (ret < 0) अणु
		axienet_mdio_mdc_disable(lp);
		वापस ret;
	पूर्ण

	rc = axienet_ior(lp, XAE_MDIO_MRD_OFFSET) & 0x0000FFFF;

	dev_dbg(lp->dev, "axienet_mdio_read(phy_id=%i, reg=%x) == %x\n",
		phy_id, reg, rc);

	axienet_mdio_mdc_disable(lp);
	वापस rc;
पूर्ण

/**
 * axienet_mdio_ग_लिखो - MDIO पूर्णांकerface ग_लिखो function
 * @bus:	Poपूर्णांकer to mii bus काष्ठाure
 * @phy_id:	Address of the PHY device
 * @reg:	PHY रेजिस्टर to ग_लिखो to
 * @val:	Value to be written पूर्णांकo the रेजिस्टर
 *
 * Return:	0 on success, -ETIMEDOUT on a समयout
 *
 * Writes the value to the requested रेजिस्टर by first writing the value
 * पूर्णांकo MWD रेजिस्टर. The the MCR रेजिस्टर is then appropriately setup
 * to finish the ग_लिखो operation.
 */
अटल पूर्णांक axienet_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg,
			      u16 val)
अणु
	पूर्णांक ret;
	काष्ठा axienet_local *lp = bus->priv;

	dev_dbg(lp->dev, "axienet_mdio_write(phy_id=%i, reg=%x, val=%x)\n",
		phy_id, reg, val);

	axienet_mdio_mdc_enable(lp);

	ret = axienet_mdio_रुको_until_पढ़ोy(lp);
	अगर (ret < 0) अणु
		axienet_mdio_mdc_disable(lp);
		वापस ret;
	पूर्ण

	axienet_iow(lp, XAE_MDIO_MWD_OFFSET, (u32) val);
	axienet_iow(lp, XAE_MDIO_MCR_OFFSET,
		    (((phy_id << XAE_MDIO_MCR_PHYAD_SHIFT) &
		      XAE_MDIO_MCR_PHYAD_MASK) |
		     ((reg << XAE_MDIO_MCR_REGAD_SHIFT) &
		      XAE_MDIO_MCR_REGAD_MASK) |
		     XAE_MDIO_MCR_INITIATE_MASK |
		     XAE_MDIO_MCR_OP_WRITE_MASK));

	ret = axienet_mdio_रुको_until_पढ़ोy(lp);
	अगर (ret < 0) अणु
		axienet_mdio_mdc_disable(lp);
		वापस ret;
	पूर्ण
	axienet_mdio_mdc_disable(lp);
	वापस 0;
पूर्ण

/**
 * axienet_mdio_enable - MDIO hardware setup function
 * @lp:		Poपूर्णांकer to axienet local data काष्ठाure.
 *
 * Return:	0 on success, -ETIMEDOUT on a समयout.
 *
 * Sets up the MDIO पूर्णांकerface by initializing the MDIO घड़ी and enabling the
 * MDIO पूर्णांकerface in hardware.
 **/
पूर्णांक axienet_mdio_enable(काष्ठा axienet_local *lp)
अणु
	u32 host_घड़ी;

	lp->mii_clk_भाग = 0;

	अगर (lp->axi_clk) अणु
		host_घड़ी = clk_get_rate(lp->axi_clk);
	पूर्ण अन्यथा अणु
		काष्ठा device_node *np1;

		/* Legacy fallback: detect CPU घड़ी frequency and use as AXI
		 * bus घड़ी frequency. This only works on certain platक्रमms.
		 */
		np1 = of_find_node_by_name(शून्य, "cpu");
		अगर (!np1) अणु
			netdev_warn(lp->ndev, "Could not find CPU device node.\n");
			host_घड़ी = DEFAULT_HOST_CLOCK;
		पूर्ण अन्यथा अणु
			पूर्णांक ret = of_property_पढ़ो_u32(np1, "clock-frequency",
						       &host_घड़ी);
			अगर (ret) अणु
				netdev_warn(lp->ndev, "CPU clock-frequency property not found.\n");
				host_घड़ी = DEFAULT_HOST_CLOCK;
			पूर्ण
			of_node_put(np1);
		पूर्ण
		netdev_info(lp->ndev, "Setting assumed host clock to %u\n",
			    host_घड़ी);
	पूर्ण

	/* clk_भाग can be calculated by deriving it from the equation:
	 * fMDIO = fHOST / ((1 + clk_भाग) * 2)
	 *
	 * Where fMDIO <= 2500000, so we get:
	 * fHOST / ((1 + clk_भाग) * 2) <= 2500000
	 *
	 * Then we get:
	 * 1 / ((1 + clk_भाग) * 2) <= (2500000 / fHOST)
	 *
	 * Then we get:
	 * 1 / (1 + clk_भाग) <= ((2500000 * 2) / fHOST)
	 *
	 * Then we get:
	 * 1 / (1 + clk_भाग) <= (5000000 / fHOST)
	 *
	 * So:
	 * (1 + clk_भाग) >= (fHOST / 5000000)
	 *
	 * And finally:
	 * clk_भाग >= (fHOST / 5000000) - 1
	 *
	 * fHOST can be पढ़ो from the flattened device tree as property
	 * "clock-frequency" from the CPU
	 */

	lp->mii_clk_भाग = (host_घड़ी / (MAX_MDIO_FREQ * 2)) - 1;
	/* If there is any reमुख्यder from the भागision of
	 * fHOST / (MAX_MDIO_FREQ * 2), then we need to add
	 * 1 to the घड़ी भागisor or we will surely be above 2.5 MHz
	 */
	अगर (host_घड़ी % (MAX_MDIO_FREQ * 2))
		lp->mii_clk_भाग++;

	netdev_dbg(lp->ndev,
		   "Setting MDIO clock divisor to %u/%u Hz host clock.\n",
		   lp->mii_clk_भाग, host_घड़ी);

	axienet_iow(lp, XAE_MDIO_MC_OFFSET, lp->mii_clk_भाग | XAE_MDIO_MC_MDIOEN_MASK);

	वापस axienet_mdio_रुको_until_पढ़ोy(lp);
पूर्ण

/**
 * axienet_mdio_disable - MDIO hardware disable function
 * @lp:		Poपूर्णांकer to axienet local data काष्ठाure.
 *
 * Disable the MDIO पूर्णांकerface in hardware.
 **/
व्योम axienet_mdio_disable(काष्ठा axienet_local *lp)
अणु
	axienet_iow(lp, XAE_MDIO_MC_OFFSET, 0);
पूर्ण

/**
 * axienet_mdio_setup - MDIO setup function
 * @lp:		Poपूर्णांकer to axienet local data काष्ठाure.
 *
 * Return:	0 on success, -ETIMEDOUT on a समयout, -ENOMEM when
 *		mdiobus_alloc (to allocate memory क्रम mii bus काष्ठाure) fails.
 *
 * Sets up the MDIO पूर्णांकerface by initializing the MDIO घड़ी.
 * Register the MDIO पूर्णांकerface.
 **/
पूर्णांक axienet_mdio_setup(काष्ठा axienet_local *lp)
अणु
	काष्ठा device_node *mdio_node;
	काष्ठा mii_bus *bus;
	पूर्णांक ret;

	ret = axienet_mdio_enable(lp);
	अगर (ret < 0)
		वापस ret;

	bus = mdiobus_alloc();
	अगर (!bus)
		वापस -ENOMEM;

	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "axienet-%.8llx",
		 (अचिन्हित दीर्घ दीर्घ)lp->regs_start);

	bus->priv = lp;
	bus->name = "Xilinx Axi Ethernet MDIO";
	bus->पढ़ो = axienet_mdio_पढ़ो;
	bus->ग_लिखो = axienet_mdio_ग_लिखो;
	bus->parent = lp->dev;
	lp->mii_bus = bus;

	mdio_node = of_get_child_by_name(lp->dev->of_node, "mdio");
	ret = of_mdiobus_रेजिस्टर(bus, mdio_node);
	of_node_put(mdio_node);
	अगर (ret) अणु
		mdiobus_मुक्त(bus);
		lp->mii_bus = शून्य;
		वापस ret;
	पूर्ण
	axienet_mdio_mdc_disable(lp);
	वापस 0;
पूर्ण

/**
 * axienet_mdio_tearकरोwn - MDIO हटाओ function
 * @lp:		Poपूर्णांकer to axienet local data काष्ठाure.
 *
 * Unरेजिस्टरs the MDIO and मुक्तs any associate memory क्रम mii bus.
 */
व्योम axienet_mdio_tearकरोwn(काष्ठा axienet_local *lp)
अणु
	mdiobus_unरेजिस्टर(lp->mii_bus);
	mdiobus_मुक्त(lp->mii_bus);
	lp->mii_bus = शून्य;
पूर्ण
