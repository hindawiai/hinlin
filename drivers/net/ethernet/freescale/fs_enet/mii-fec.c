<शैली गुरु>
/*
 * Combined Ethernet driver क्रम Motorola MPC8xx and MPC82xx.
 *
 * Copyright (c) 2003 Intracom S.A.
 *  by Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2005 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mpc5xxx.h>

#समावेश "fs_enet.h"
#समावेश "fec.h"

/* Make MII पढ़ो/ग_लिखो commands क्रम the FEC.
*/
#घोषणा mk_mii_पढ़ो(REG)	(0x60020000 | ((REG & 0x1f) << 18))
#घोषणा mk_mii_ग_लिखो(REG, VAL)	(0x50020000 | ((REG & 0x1f) << 18) | (VAL & 0xffff))
#घोषणा mk_mii_end		0

#घोषणा FEC_MII_LOOPS	10000

अटल पूर्णांक fs_enet_fec_mii_पढ़ो(काष्ठा mii_bus *bus , पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा fec_info* fec = bus->priv;
	काष्ठा fec __iomem *fecp = fec->fecp;
	पूर्णांक i, ret = -1;

	BUG_ON((in_be32(&fecp->fec_r_cntrl) & FEC_RCNTRL_MII_MODE) == 0);

	/* Add PHY address to रेजिस्टर command.  */
	out_be32(&fecp->fec_mii_data, (phy_id << 23) | mk_mii_पढ़ो(location));

	क्रम (i = 0; i < FEC_MII_LOOPS; i++)
		अगर ((in_be32(&fecp->fec_ievent) & FEC_ENET_MII) != 0)
			अवरोध;

	अगर (i < FEC_MII_LOOPS) अणु
		out_be32(&fecp->fec_ievent, FEC_ENET_MII);
		ret = in_be32(&fecp->fec_mii_data) & 0xffff;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fs_enet_fec_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location, u16 val)
अणु
	काष्ठा fec_info* fec = bus->priv;
	काष्ठा fec __iomem *fecp = fec->fecp;
	पूर्णांक i;

	/* this must never happen */
	BUG_ON((in_be32(&fecp->fec_r_cntrl) & FEC_RCNTRL_MII_MODE) == 0);

	/* Add PHY address to रेजिस्टर command.  */
	out_be32(&fecp->fec_mii_data, (phy_id << 23) | mk_mii_ग_लिखो(location, val));

	क्रम (i = 0; i < FEC_MII_LOOPS; i++)
		अगर ((in_be32(&fecp->fec_ievent) & FEC_ENET_MII) != 0)
			अवरोध;

	अगर (i < FEC_MII_LOOPS)
		out_be32(&fecp->fec_ievent, FEC_ENET_MII);

	वापस 0;

पूर्ण

अटल स्थिर काष्ठा of_device_id fs_enet_mdio_fec_match[];
अटल पूर्णांक fs_enet_mdio_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource res;
	काष्ठा mii_bus *new_bus;
	काष्ठा fec_info *fec;
	पूर्णांक (*get_bus_freq)(काष्ठा device_node *);
	पूर्णांक ret = -ENOMEM, घड़ी, speed;

	match = of_match_device(fs_enet_mdio_fec_match, &ofdev->dev);
	अगर (!match)
		वापस -EINVAL;
	get_bus_freq = match->data;

	new_bus = mdiobus_alloc();
	अगर (!new_bus)
		जाओ out;

	fec = kzalloc(माप(काष्ठा fec_info), GFP_KERNEL);
	अगर (!fec)
		जाओ out_mii;

	new_bus->priv = fec;
	new_bus->name = "FEC MII Bus";
	new_bus->पढ़ो = &fs_enet_fec_mii_पढ़ो;
	new_bus->ग_लिखो = &fs_enet_fec_mii_ग_लिखो;

	ret = of_address_to_resource(ofdev->dev.of_node, 0, &res);
	अगर (ret)
		जाओ out_res;

	snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "%x", res.start);

	fec->fecp = ioremap(res.start, resource_size(&res));
	अगर (!fec->fecp) अणु
		ret = -ENOMEM;
		जाओ out_fec;
	पूर्ण

	अगर (get_bus_freq) अणु
		घड़ी = get_bus_freq(ofdev->dev.of_node);
		अगर (!घड़ी) अणु
			/* Use maximum भागider अगर घड़ी is unknown */
			dev_warn(&ofdev->dev, "could not determine IPS clock\n");
			घड़ी = 0x3F * 5000000;
		पूर्ण
	पूर्ण अन्यथा
		घड़ी = ppc_proc_freq;

	/*
	 * Scale क्रम a MII घड़ी <= 2.5 MHz
	 * Note that only 6 bits (25:30) are available क्रम MII speed.
	 */
	speed = (घड़ी + 4999999) / 5000000;
	अगर (speed > 0x3F) अणु
		speed = 0x3F;
		dev_err(&ofdev->dev,
			"MII clock (%d Hz) exceeds max (2.5 MHz)\n",
			घड़ी / speed);
	पूर्ण

	fec->mii_speed = speed << 1;

	setbits32(&fec->fecp->fec_r_cntrl, FEC_RCNTRL_MII_MODE);
	setbits32(&fec->fecp->fec_ecntrl, FEC_ECNTRL_PINMUX |
	                                  FEC_ECNTRL_ETHER_EN);
	out_be32(&fec->fecp->fec_ievent, FEC_ENET_MII);
	clrsetbits_be32(&fec->fecp->fec_mii_speed, 0x7E, fec->mii_speed);

	new_bus->phy_mask = ~0;

	new_bus->parent = &ofdev->dev;
	platक्रमm_set_drvdata(ofdev, new_bus);

	ret = of_mdiobus_रेजिस्टर(new_bus, ofdev->dev.of_node);
	अगर (ret)
		जाओ out_unmap_regs;

	वापस 0;

out_unmap_regs:
	iounmap(fec->fecp);
out_res:
out_fec:
	kमुक्त(fec);
out_mii:
	mdiobus_मुक्त(new_bus);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक fs_enet_mdio_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(ofdev);
	काष्ठा fec_info *fec = bus->priv;

	mdiobus_unरेजिस्टर(bus);
	iounmap(fec->fecp);
	kमुक्त(fec);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fs_enet_mdio_fec_match[] = अणु
	अणु
		.compatible = "fsl,pq1-fec-mdio",
	पूर्ण,
#अगर defined(CONFIG_PPC_MPC512x)
	अणु
		.compatible = "fsl,mpc5121-fec-mdio",
		.data = mpc5xxx_get_bus_frequency,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fs_enet_mdio_fec_match);

अटल काष्ठा platक्रमm_driver fs_enet_fec_mdio_driver = अणु
	.driver = अणु
		.name = "fsl-fec-mdio",
		.of_match_table = fs_enet_mdio_fec_match,
	पूर्ण,
	.probe = fs_enet_mdio_probe,
	.हटाओ = fs_enet_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(fs_enet_fec_mdio_driver);
MODULE_LICENSE("GPL");
