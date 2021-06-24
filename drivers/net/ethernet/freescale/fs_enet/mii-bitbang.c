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
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>

#समावेश "fs_enet.h"

काष्ठा bb_info अणु
	काष्ठा mdiobb_ctrl ctrl;
	__be32 __iomem *dir;
	__be32 __iomem *dat;
	u32 mdio_msk;
	u32 mdc_msk;
पूर्ण;

/* FIXME: If any other users of GPIO crop up, then these will have to
 * have some sort of global synchronization to aव्योम races with other
 * pins on the same port.  The ideal solution would probably be to
 * bind the ports to a GPIO driver, and have this be a client of it.
 */
अटल अंतरभूत व्योम bb_set(u32 __iomem *p, u32 m)
अणु
	out_be32(p, in_be32(p) | m);
पूर्ण

अटल अंतरभूत व्योम bb_clr(u32 __iomem *p, u32 m)
अणु
	out_be32(p, in_be32(p) & ~m);
पूर्ण

अटल अंतरभूत पूर्णांक bb_पढ़ो(u32 __iomem *p, u32 m)
अणु
	वापस (in_be32(p) & m) != 0;
पूर्ण

अटल अंतरभूत व्योम mdio_dir(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक dir)
अणु
	काष्ठा bb_info *bitbang = container_of(ctrl, काष्ठा bb_info, ctrl);

	अगर (dir)
		bb_set(bitbang->dir, bitbang->mdio_msk);
	अन्यथा
		bb_clr(bitbang->dir, bitbang->mdio_msk);

	/* Read back to flush the ग_लिखो. */
	in_be32(bitbang->dir);
पूर्ण

अटल अंतरभूत पूर्णांक mdio_पढ़ो(काष्ठा mdiobb_ctrl *ctrl)
अणु
	काष्ठा bb_info *bitbang = container_of(ctrl, काष्ठा bb_info, ctrl);
	वापस bb_पढ़ो(bitbang->dat, bitbang->mdio_msk);
पूर्ण

अटल अंतरभूत व्योम mdio(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक what)
अणु
	काष्ठा bb_info *bitbang = container_of(ctrl, काष्ठा bb_info, ctrl);

	अगर (what)
		bb_set(bitbang->dat, bitbang->mdio_msk);
	अन्यथा
		bb_clr(bitbang->dat, bitbang->mdio_msk);

	/* Read back to flush the ग_लिखो. */
	in_be32(bitbang->dat);
पूर्ण

अटल अंतरभूत व्योम mdc(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक what)
अणु
	काष्ठा bb_info *bitbang = container_of(ctrl, काष्ठा bb_info, ctrl);

	अगर (what)
		bb_set(bitbang->dat, bitbang->mdc_msk);
	अन्यथा
		bb_clr(bitbang->dat, bitbang->mdc_msk);

	/* Read back to flush the ग_लिखो. */
	in_be32(bitbang->dat);
पूर्ण

अटल स्थिर काष्ठा mdiobb_ops bb_ops = अणु
	.owner = THIS_MODULE,
	.set_mdc = mdc,
	.set_mdio_dir = mdio_dir,
	.set_mdio_data = mdio,
	.get_mdio_data = mdio_पढ़ो,
पूर्ण;

अटल पूर्णांक fs_mii_bitbang_init(काष्ठा mii_bus *bus, काष्ठा device_node *np)
अणु
	काष्ठा resource res;
	स्थिर u32 *data;
	पूर्णांक mdio_pin, mdc_pin, len;
	काष्ठा bb_info *bitbang = bus->priv;

	पूर्णांक ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		वापस ret;

	अगर (resource_size(&res) <= 13)
		वापस -ENODEV;

	/* This should really encode the pin number as well, but all
	 * we get is an पूर्णांक, and the odds of multiple bitbang mdio buses
	 * is low enough that it's not worth going too crazy.
	 */
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%x", res.start);

	data = of_get_property(np, "fsl,mdio-pin", &len);
	अगर (!data || len != 4)
		वापस -ENODEV;
	mdio_pin = *data;

	data = of_get_property(np, "fsl,mdc-pin", &len);
	अगर (!data || len != 4)
		वापस -ENODEV;
	mdc_pin = *data;

	bitbang->dir = ioremap(res.start, resource_size(&res));
	अगर (!bitbang->dir)
		वापस -ENOMEM;

	bitbang->dat = bitbang->dir + 4;
	bitbang->mdio_msk = 1 << (31 - mdio_pin);
	bitbang->mdc_msk = 1 << (31 - mdc_pin);

	वापस 0;
पूर्ण

अटल पूर्णांक fs_enet_mdio_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mii_bus *new_bus;
	काष्ठा bb_info *bitbang;
	पूर्णांक ret = -ENOMEM;

	bitbang = kzalloc(माप(काष्ठा bb_info), GFP_KERNEL);
	अगर (!bitbang)
		जाओ out;

	bitbang->ctrl.ops = &bb_ops;

	new_bus = alloc_mdio_bitbang(&bitbang->ctrl);
	अगर (!new_bus)
		जाओ out_मुक्त_priv;

	new_bus->name = "CPM2 Bitbanged MII",

	ret = fs_mii_bitbang_init(new_bus, ofdev->dev.of_node);
	अगर (ret)
		जाओ out_मुक्त_bus;

	new_bus->phy_mask = ~0;

	new_bus->parent = &ofdev->dev;
	platक्रमm_set_drvdata(ofdev, new_bus);

	ret = of_mdiobus_रेजिस्टर(new_bus, ofdev->dev.of_node);
	अगर (ret)
		जाओ out_unmap_regs;

	वापस 0;

out_unmap_regs:
	iounmap(bitbang->dir);
out_मुक्त_bus:
	मुक्त_mdio_bitbang(new_bus);
out_मुक्त_priv:
	kमुक्त(bitbang);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक fs_enet_mdio_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(ofdev);
	काष्ठा bb_info *bitbang = bus->priv;

	mdiobus_unरेजिस्टर(bus);
	मुक्त_mdio_bitbang(bus);
	iounmap(bitbang->dir);
	kमुक्त(bitbang);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fs_enet_mdio_bb_match[] = अणु
	अणु
		.compatible = "fsl,cpm2-mdio-bitbang",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fs_enet_mdio_bb_match);

अटल काष्ठा platक्रमm_driver fs_enet_bb_mdio_driver = अणु
	.driver = अणु
		.name = "fsl-bb-mdio",
		.of_match_table = fs_enet_mdio_bb_match,
	पूर्ण,
	.probe = fs_enet_mdio_probe,
	.हटाओ = fs_enet_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(fs_enet_bb_mdio_driver);
MODULE_LICENSE("GPL");
