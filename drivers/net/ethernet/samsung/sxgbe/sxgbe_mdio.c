<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/slab.h>
#समावेश <linux/sxgbe_platक्रमm.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_reg.h"

#घोषणा SXGBE_SMA_WRITE_CMD	0x01 /* ग_लिखो command */
#घोषणा SXGBE_SMA_PREAD_CMD	0x02 /* post पढ़ो  increament address */
#घोषणा SXGBE_SMA_READ_CMD	0x03 /* पढ़ो command */
#घोषणा SXGBE_SMA_SKIP_ADDRFRM	0x00040000 /* skip the address frame */
#घोषणा SXGBE_MII_BUSY		0x00400000 /* mii busy */

अटल पूर्णांक sxgbe_mdio_busy_रुको(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक mii_data)
अणु
	अचिन्हित दीर्घ fin_समय = jअगरfies + 3 * HZ; /* 3 seconds */

	जबतक (!समय_after(jअगरfies, fin_समय)) अणु
		अगर (!(पढ़ोl(ioaddr + mii_data) & SXGBE_MII_BUSY))
			वापस 0;
		cpu_relax();
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम sxgbe_mdio_ctrl_data(काष्ठा sxgbe_priv_data *sp, u32 cmd,
				 u16 phydata)
अणु
	u32 reg = phydata;

	reg |= (cmd << 16) | SXGBE_SMA_SKIP_ADDRFRM |
	       ((sp->clk_csr & 0x7) << 19) | SXGBE_MII_BUSY;
	ग_लिखोl(reg, sp->ioaddr + sp->hw->mii.data);
पूर्ण

अटल व्योम sxgbe_mdio_c45(काष्ठा sxgbe_priv_data *sp, u32 cmd, पूर्णांक phyaddr,
			   पूर्णांक phyreg, u16 phydata)
अणु
	u32 reg;

	/* set mdio address रेजिस्टर */
	reg = ((phyreg >> 16) & 0x1f) << 21;
	reg |= (phyaddr << 16) | (phyreg & 0xffff);
	ग_लिखोl(reg, sp->ioaddr + sp->hw->mii.addr);

	sxgbe_mdio_ctrl_data(sp, cmd, phydata);
पूर्ण

अटल व्योम sxgbe_mdio_c22(काष्ठा sxgbe_priv_data *sp, u32 cmd, पूर्णांक phyaddr,
			   पूर्णांक phyreg, u16 phydata)
अणु
	u32 reg;

	ग_लिखोl(1 << phyaddr, sp->ioaddr + SXGBE_MDIO_CLAUSE22_PORT_REG);

	/* set mdio address रेजिस्टर */
	reg = (phyaddr << 16) | (phyreg & 0x1f);
	ग_लिखोl(reg, sp->ioaddr + sp->hw->mii.addr);

	sxgbe_mdio_ctrl_data(sp, cmd, phydata);
पूर्ण

अटल पूर्णांक sxgbe_mdio_access(काष्ठा sxgbe_priv_data *sp, u32 cmd, पूर्णांक phyaddr,
			     पूर्णांक phyreg, u16 phydata)
अणु
	स्थिर काष्ठा mii_regs *mii = &sp->hw->mii;
	पूर्णांक rc;

	rc = sxgbe_mdio_busy_रुको(sp->ioaddr, mii->data);
	अगर (rc < 0)
		वापस rc;

	अगर (phyreg & MII_ADDR_C45) अणु
		sxgbe_mdio_c45(sp, cmd, phyaddr, phyreg, phydata);
	पूर्ण अन्यथा अणु
		 /* Ports 0-3 only support C22. */
		अगर (phyaddr >= 4)
			वापस -ENODEV;

		sxgbe_mdio_c22(sp, cmd, phyaddr, phyreg, phydata);
	पूर्ण

	वापस sxgbe_mdio_busy_रुको(sp->ioaddr, mii->data);
पूर्ण

/**
 * sxgbe_mdio_पढ़ो
 * @bus: poपूर्णांकs to the mii_bus काष्ठाure
 * @phyaddr: address of phy port
 * @phyreg: address of रेजिस्टर with in phy रेजिस्टर
 * Description: this function used क्रम C45 and C22 MDIO Read
 */
अटल पूर्णांक sxgbe_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक phyreg)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sxgbe_priv_data *priv = netdev_priv(ndev);
	पूर्णांक rc;

	rc = sxgbe_mdio_access(priv, SXGBE_SMA_READ_CMD, phyaddr, phyreg, 0);
	अगर (rc < 0)
		वापस rc;

	वापस पढ़ोl(priv->ioaddr + priv->hw->mii.data) & 0xffff;
पूर्ण

/**
 * sxgbe_mdio_ग_लिखो
 * @bus: poपूर्णांकs to the mii_bus काष्ठाure
 * @phyaddr: address of phy port
 * @phyreg: address of phy रेजिस्टरs
 * @phydata: data to be written पूर्णांकo phy रेजिस्टर
 * Description: this function is used क्रम C45 and C22 MDIO ग_लिखो
 */
अटल पूर्णांक sxgbe_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक phyreg,
			     u16 phydata)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा sxgbe_priv_data *priv = netdev_priv(ndev);

	वापस sxgbe_mdio_access(priv, SXGBE_SMA_WRITE_CMD, phyaddr, phyreg,
				 phydata);
पूर्ण

पूर्णांक sxgbe_mdio_रेजिस्टर(काष्ठा net_device *ndev)
अणु
	काष्ठा mii_bus *mdio_bus;
	काष्ठा sxgbe_priv_data *priv = netdev_priv(ndev);
	काष्ठा sxgbe_mdio_bus_data *mdio_data = priv->plat->mdio_bus_data;
	पूर्णांक err, phy_addr;
	पूर्णांक *irqlist;
	bool phy_found = false;
	bool act;

	/* allocate the new mdio bus */
	mdio_bus = mdiobus_alloc();
	अगर (!mdio_bus) अणु
		netdev_err(ndev, "%s: mii bus allocation failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (mdio_data->irqs)
		irqlist = mdio_data->irqs;
	अन्यथा
		irqlist = priv->mii_irq;

	/* assign mii bus fields */
	mdio_bus->name = "sxgbe";
	mdio_bus->पढ़ो = &sxgbe_mdio_पढ़ो;
	mdio_bus->ग_लिखो = &sxgbe_mdio_ग_लिखो;
	snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 mdio_bus->name, priv->plat->bus_id);
	mdio_bus->priv = ndev;
	mdio_bus->phy_mask = mdio_data->phy_mask;
	mdio_bus->parent = priv->device;

	/* रेजिस्टर with kernel subप्रणाली */
	err = mdiobus_रेजिस्टर(mdio_bus);
	अगर (err != 0) अणु
		netdev_err(ndev, "mdiobus register failed\n");
		जाओ mdiobus_err;
	पूर्ण

	क्रम (phy_addr = 0; phy_addr < PHY_MAX_ADDR; phy_addr++) अणु
		काष्ठा phy_device *phy = mdiobus_get_phy(mdio_bus, phy_addr);

		अगर (phy) अणु
			अक्षर irq_num[4];
			अक्षर *irq_str;
			/* If an IRQ was provided to be asचिन्हित after
			 * the bus probe, करो it here.
			 */
			अगर ((mdio_data->irqs == शून्य) &&
			    (mdio_data->probed_phy_irq > 0)) अणु
				irqlist[phy_addr] = mdio_data->probed_phy_irq;
				phy->irq = mdio_data->probed_phy_irq;
			पूर्ण

			/* If we're  going to bind the MAC to this PHY bus,
			 * and no PHY number was provided to the MAC,
			 * use the one probed here.
			 */
			अगर (priv->plat->phy_addr == -1)
				priv->plat->phy_addr = phy_addr;

			act = (priv->plat->phy_addr == phy_addr);
			चयन (phy->irq) अणु
			हाल PHY_POLL:
				irq_str = "POLL";
				अवरोध;
			हाल PHY_MAC_INTERRUPT:
				irq_str = "MAC";
				अवरोध;
			शेष:
				प्र_लिखो(irq_num, "%d", phy->irq);
				irq_str = irq_num;
				अवरोध;
			पूर्ण
			netdev_info(ndev, "PHY ID %08x at %d IRQ %s (%s)%s\n",
				    phy->phy_id, phy_addr, irq_str,
				    phydev_name(phy), act ? " active" : "");
			phy_found = true;
		पूर्ण
	पूर्ण

	अगर (!phy_found) अणु
		netdev_err(ndev, "PHY not found\n");
		जाओ phyfound_err;
	पूर्ण

	priv->mii = mdio_bus;

	वापस 0;

phyfound_err:
	err = -ENODEV;
	mdiobus_unरेजिस्टर(mdio_bus);
mdiobus_err:
	mdiobus_मुक्त(mdio_bus);
	वापस err;
पूर्ण

पूर्णांक sxgbe_mdio_unरेजिस्टर(काष्ठा net_device *ndev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(ndev);

	अगर (!priv->mii)
		वापस 0;

	mdiobus_unरेजिस्टर(priv->mii);
	priv->mii->priv = शून्य;
	mdiobus_मुक्त(priv->mii);
	priv->mii = शून्य;

	वापस 0;
पूर्ण
