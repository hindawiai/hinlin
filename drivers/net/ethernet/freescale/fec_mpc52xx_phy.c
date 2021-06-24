<शैली गुरु>
/*
 * Driver क्रम the MPC5200 Fast Ethernet Controller - MDIO bus driver
 *
 * Copyright (C) 2007  Domen Puncer, Telargo, Inc.
 * Copyright (C) 2008  Wolfram Sang, Pengutronix
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_mdपन.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mpc52xx.h>
#समावेश "fec_mpc52xx.h"

काष्ठा mpc52xx_fec_mdio_priv अणु
	काष्ठा mpc52xx_fec __iomem *regs;
पूर्ण;

अटल पूर्णांक mpc52xx_fec_mdio_transfer(काष्ठा mii_bus *bus, पूर्णांक phy_id,
		पूर्णांक reg, u32 value)
अणु
	काष्ठा mpc52xx_fec_mdio_priv *priv = bus->priv;
	काष्ठा mpc52xx_fec __iomem *fec = priv->regs;
	पूर्णांक tries = 3;

	value |= (phy_id << FEC_MII_DATA_PA_SHIFT) & FEC_MII_DATA_PA_MSK;
	value |= (reg << FEC_MII_DATA_RA_SHIFT) & FEC_MII_DATA_RA_MSK;

	out_be32(&fec->ievent, FEC_IEVENT_MII);
	out_be32(&fec->mii_data, value);

	/* रुको क्रम it to finish, this takes about 23 us on lite5200b */
	जबतक (!(in_be32(&fec->ievent) & FEC_IEVENT_MII) && --tries)
		msleep(1);

	अगर (!tries)
		वापस -ETIMEDOUT;

	वापस value & FEC_MII_DATA_OP_RD ?
		in_be32(&fec->mii_data) & FEC_MII_DATA_DATAMSK : 0;
पूर्ण

अटल पूर्णांक mpc52xx_fec_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	वापस mpc52xx_fec_mdio_transfer(bus, phy_id, reg, FEC_MII_READ_FRAME);
पूर्ण

अटल पूर्णांक mpc52xx_fec_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg,
		u16 data)
अणु
	वापस mpc52xx_fec_mdio_transfer(bus, phy_id, reg,
		data | FEC_MII_WRITE_FRAME);
पूर्ण

अटल पूर्णांक mpc52xx_fec_mdio_probe(काष्ठा platक्रमm_device *of)
अणु
	काष्ठा device *dev = &of->dev;
	काष्ठा device_node *np = of->dev.of_node;
	काष्ठा mii_bus *bus;
	काष्ठा mpc52xx_fec_mdio_priv *priv;
	काष्ठा resource res;
	पूर्णांक err;

	bus = mdiobus_alloc();
	अगर (bus == शून्य)
		वापस -ENOMEM;
	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	bus->name = "mpc52xx MII bus";
	bus->पढ़ो = mpc52xx_fec_mdio_पढ़ो;
	bus->ग_लिखो = mpc52xx_fec_mdio_ग_लिखो;

	/* setup रेजिस्टरs */
	err = of_address_to_resource(np, 0, &res);
	अगर (err)
		जाओ out_मुक्त;
	priv->regs = ioremap(res.start, resource_size(&res));
	अगर (priv->regs == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%x", res.start);
	bus->priv = priv;

	bus->parent = dev;
	dev_set_drvdata(dev, bus);

	/* set MII speed */
	out_be32(&priv->regs->mii_speed,
		((mpc5xxx_get_bus_frequency(of->dev.of_node) >> 20) / 5) << 1);

	err = of_mdiobus_रेजिस्टर(bus, np);
	अगर (err)
		जाओ out_unmap;

	वापस 0;

 out_unmap:
	iounmap(priv->regs);
 out_मुक्त:
	kमुक्त(priv);
	mdiobus_मुक्त(bus);

	वापस err;
पूर्ण

अटल पूर्णांक mpc52xx_fec_mdio_हटाओ(काष्ठा platक्रमm_device *of)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(of);
	काष्ठा mpc52xx_fec_mdio_priv *priv = bus->priv;

	mdiobus_unरेजिस्टर(bus);
	iounmap(priv->regs);
	kमुक्त(priv);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_fec_mdio_match[] = अणु
	अणु .compatible = "fsl,mpc5200b-mdio", पूर्ण,
	अणु .compatible = "fsl,mpc5200-mdio", पूर्ण,
	अणु .compatible = "mpc5200b-fec-phy", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc52xx_fec_mdio_match);

काष्ठा platक्रमm_driver mpc52xx_fec_mdio_driver = अणु
	.driver = अणु
		.name = "mpc5200b-fec-phy",
		.owner = THIS_MODULE,
		.of_match_table = mpc52xx_fec_mdio_match,
	पूर्ण,
	.probe = mpc52xx_fec_mdio_probe,
	.हटाओ = mpc52xx_fec_mdio_हटाओ,
पूर्ण;

/* let fec driver call it, since this has to be रेजिस्टरed beक्रमe it */
EXPORT_SYMBOL_GPL(mpc52xx_fec_mdio_driver);

MODULE_LICENSE("Dual BSD/GPL");
