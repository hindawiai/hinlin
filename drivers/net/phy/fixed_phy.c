<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Fixed MDIO bus (MDIO bus emulation with fixed PHYs)
 *
 * Author: Vitaly Bordug <vbordug@ru.mvista.com>
 *         Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * Copyright (c) 2006-2007 MontaVista Software, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/idr.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/linkmode.h>

#समावेश "swphy.h"

काष्ठा fixed_mdio_bus अणु
	काष्ठा mii_bus *mii_bus;
	काष्ठा list_head phys;
पूर्ण;

काष्ठा fixed_phy अणु
	पूर्णांक addr;
	काष्ठा phy_device *phydev;
	काष्ठा fixed_phy_status status;
	bool no_carrier;
	पूर्णांक (*link_update)(काष्ठा net_device *, काष्ठा fixed_phy_status *);
	काष्ठा list_head node;
	काष्ठा gpio_desc *link_gpiod;
पूर्ण;

अटल काष्ठा platक्रमm_device *pdev;
अटल काष्ठा fixed_mdio_bus platक्रमm_fmb = अणु
	.phys = LIST_HEAD_INIT(platक्रमm_fmb.phys),
पूर्ण;

पूर्णांक fixed_phy_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	काष्ठा phy_device *phydev = dev->phydev;
	काष्ठा fixed_phy *fp;

	अगर (!phydev || !phydev->mdio.bus)
		वापस -EINVAL;

	list_क्रम_each_entry(fp, &fmb->phys, node) अणु
		अगर (fp->addr == phydev->mdio.addr) अणु
			fp->no_carrier = !new_carrier;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(fixed_phy_change_carrier);

अटल व्योम fixed_phy_update(काष्ठा fixed_phy *fp)
अणु
	अगर (!fp->no_carrier && fp->link_gpiod)
		fp->status.link = !!gpiod_get_value_cansleep(fp->link_gpiod);
पूर्ण

अटल पूर्णांक fixed_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_num)
अणु
	काष्ठा fixed_mdio_bus *fmb = bus->priv;
	काष्ठा fixed_phy *fp;

	list_क्रम_each_entry(fp, &fmb->phys, node) अणु
		अगर (fp->addr == phy_addr) अणु
			काष्ठा fixed_phy_status state;

			fp->status.link = !fp->no_carrier;

			/* Issue callback अगर user रेजिस्टरed it. */
			अगर (fp->link_update)
				fp->link_update(fp->phydev->attached_dev,
						&fp->status);

			/* Check the GPIO क्रम change in status */
			fixed_phy_update(fp);
			state = fp->status;

			वापस swphy_पढ़ो_reg(reg_num, &state);
		पूर्ण
	पूर्ण

	वापस 0xFFFF;
पूर्ण

अटल पूर्णांक fixed_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_num,
			    u16 val)
अणु
	वापस 0;
पूर्ण

/*
 * If something weird is required to be करोne with link/speed,
 * network driver is able to assign a function to implement this.
 * May be useful क्रम PHY's that need to be software-driven.
 */
पूर्णांक fixed_phy_set_link_update(काष्ठा phy_device *phydev,
			      पूर्णांक (*link_update)(काष्ठा net_device *,
						 काष्ठा fixed_phy_status *))
अणु
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	काष्ठा fixed_phy *fp;

	अगर (!phydev || !phydev->mdio.bus)
		वापस -EINVAL;

	list_क्रम_each_entry(fp, &fmb->phys, node) अणु
		अगर (fp->addr == phydev->mdio.addr) अणु
			fp->link_update = link_update;
			fp->phydev = phydev;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(fixed_phy_set_link_update);

अटल पूर्णांक fixed_phy_add_gpiod(अचिन्हित पूर्णांक irq, पूर्णांक phy_addr,
			       काष्ठा fixed_phy_status *status,
			       काष्ठा gpio_desc *gpiod)
अणु
	पूर्णांक ret;
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	काष्ठा fixed_phy *fp;

	ret = swphy_validate_state(status);
	अगर (ret < 0)
		वापस ret;

	fp = kzalloc(माप(*fp), GFP_KERNEL);
	अगर (!fp)
		वापस -ENOMEM;

	अगर (irq != PHY_POLL)
		fmb->mii_bus->irq[phy_addr] = irq;

	fp->addr = phy_addr;
	fp->status = *status;
	fp->link_gpiod = gpiod;

	fixed_phy_update(fp);

	list_add_tail(&fp->node, &fmb->phys);

	वापस 0;
पूर्ण

पूर्णांक fixed_phy_add(अचिन्हित पूर्णांक irq, पूर्णांक phy_addr,
		  काष्ठा fixed_phy_status *status) अणु

	वापस fixed_phy_add_gpiod(irq, phy_addr, status, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(fixed_phy_add);

अटल DEFINE_IDA(phy_fixed_ida);

अटल व्योम fixed_phy_del(पूर्णांक phy_addr)
अणु
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	काष्ठा fixed_phy *fp, *पंचांगp;

	list_क्रम_each_entry_safe(fp, पंचांगp, &fmb->phys, node) अणु
		अगर (fp->addr == phy_addr) अणु
			list_del(&fp->node);
			अगर (fp->link_gpiod)
				gpiod_put(fp->link_gpiod);
			kमुक्त(fp);
			ida_simple_हटाओ(&phy_fixed_ida, phy_addr);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF_GPIO
अटल काष्ठा gpio_desc *fixed_phy_get_gpiod(काष्ठा device_node *np)
अणु
	काष्ठा device_node *fixed_link_node;
	काष्ठा gpio_desc *gpiod;

	अगर (!np)
		वापस शून्य;

	fixed_link_node = of_get_child_by_name(np, "fixed-link");
	अगर (!fixed_link_node)
		वापस शून्य;

	/*
	 * As the fixed link is just a device tree node without any
	 * Linux device associated with it, we simply have obtain
	 * the GPIO descriptor from the device tree like this.
	 */
	gpiod = fwnode_gpiod_get_index(of_fwnode_handle(fixed_link_node),
				       "link", 0, GPIOD_IN, "mdio");
	अगर (IS_ERR(gpiod) && PTR_ERR(gpiod) != -EPROBE_DEFER) अणु
		अगर (PTR_ERR(gpiod) != -ENOENT)
			pr_err("error getting GPIO for fixed link %pOF, proceed without\n",
			       fixed_link_node);
		gpiod = शून्य;
	पूर्ण
	of_node_put(fixed_link_node);

	वापस gpiod;
पूर्ण
#अन्यथा
अटल काष्ठा gpio_desc *fixed_phy_get_gpiod(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा phy_device *__fixed_phy_रेजिस्टर(अचिन्हित पूर्णांक irq,
					       काष्ठा fixed_phy_status *status,
					       काष्ठा device_node *np,
					       काष्ठा gpio_desc *gpiod)
अणु
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	काष्ठा phy_device *phy;
	पूर्णांक phy_addr;
	पूर्णांक ret;

	अगर (!fmb->mii_bus || fmb->mii_bus->state != MDIOBUS_REGISTERED)
		वापस ERR_PTR(-EPROBE_DEFER);

	/* Check अगर we have a GPIO associated with this fixed phy */
	अगर (!gpiod) अणु
		gpiod = fixed_phy_get_gpiod(np);
		अगर (IS_ERR(gpiod))
			वापस ERR_CAST(gpiod);
	पूर्ण

	/* Get the next available PHY address, up to PHY_MAX_ADDR */
	phy_addr = ida_simple_get(&phy_fixed_ida, 0, PHY_MAX_ADDR, GFP_KERNEL);
	अगर (phy_addr < 0)
		वापस ERR_PTR(phy_addr);

	ret = fixed_phy_add_gpiod(irq, phy_addr, status, gpiod);
	अगर (ret < 0) अणु
		ida_simple_हटाओ(&phy_fixed_ida, phy_addr);
		वापस ERR_PTR(ret);
	पूर्ण

	phy = get_phy_device(fmb->mii_bus, phy_addr, false);
	अगर (IS_ERR(phy)) अणु
		fixed_phy_del(phy_addr);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* propagate the fixed link values to काष्ठा phy_device */
	phy->link = status->link;
	अगर (status->link) अणु
		phy->speed = status->speed;
		phy->duplex = status->duplex;
		phy->छोड़ो = status->छोड़ो;
		phy->asym_छोड़ो = status->asym_छोड़ो;
	पूर्ण

	of_node_get(np);
	phy->mdio.dev.of_node = np;
	phy->is_pseuकरो_fixed_link = true;

	चयन (status->speed) अणु
	हाल SPEED_1000:
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
				 phy->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 phy->supported);
		fallthrough;
	हाल SPEED_100:
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				 phy->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 phy->supported);
		fallthrough;
	हाल SPEED_10:
	शेष:
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
				 phy->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
				 phy->supported);
	पूर्ण

	phy_advertise_supported(phy);

	ret = phy_device_रेजिस्टर(phy);
	अगर (ret) अणु
		phy_device_मुक्त(phy);
		of_node_put(np);
		fixed_phy_del(phy_addr);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस phy;
पूर्ण

काष्ठा phy_device *fixed_phy_रेजिस्टर(अचिन्हित पूर्णांक irq,
				      काष्ठा fixed_phy_status *status,
				      काष्ठा device_node *np)
अणु
	वापस __fixed_phy_रेजिस्टर(irq, status, np, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(fixed_phy_रेजिस्टर);

काष्ठा phy_device *
fixed_phy_रेजिस्टर_with_gpiod(अचिन्हित पूर्णांक irq,
			      काष्ठा fixed_phy_status *status,
			      काष्ठा gpio_desc *gpiod)
अणु
	वापस __fixed_phy_रेजिस्टर(irq, status, शून्य, gpiod);
पूर्ण
EXPORT_SYMBOL_GPL(fixed_phy_रेजिस्टर_with_gpiod);

व्योम fixed_phy_unरेजिस्टर(काष्ठा phy_device *phy)
अणु
	phy_device_हटाओ(phy);
	of_node_put(phy->mdio.dev.of_node);
	fixed_phy_del(phy->mdio.addr);
पूर्ण
EXPORT_SYMBOL_GPL(fixed_phy_unरेजिस्टर);

अटल पूर्णांक __init fixed_mdio_bus_init(व्योम)
अणु
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	पूर्णांक ret;

	pdev = platक्रमm_device_रेजिस्टर_simple("Fixed MDIO bus", 0, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	fmb->mii_bus = mdiobus_alloc();
	अगर (fmb->mii_bus == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_mdiobus_reg;
	पूर्ण

	snम_लिखो(fmb->mii_bus->id, MII_BUS_ID_SIZE, "fixed-0");
	fmb->mii_bus->name = "Fixed MDIO Bus";
	fmb->mii_bus->priv = fmb;
	fmb->mii_bus->parent = &pdev->dev;
	fmb->mii_bus->पढ़ो = &fixed_mdio_पढ़ो;
	fmb->mii_bus->ग_लिखो = &fixed_mdio_ग_लिखो;

	ret = mdiobus_रेजिस्टर(fmb->mii_bus);
	अगर (ret)
		जाओ err_mdiobus_alloc;

	वापस 0;

err_mdiobus_alloc:
	mdiobus_मुक्त(fmb->mii_bus);
err_mdiobus_reg:
	platक्रमm_device_unरेजिस्टर(pdev);
	वापस ret;
पूर्ण
module_init(fixed_mdio_bus_init);

अटल व्योम __निकास fixed_mdio_bus_निकास(व्योम)
अणु
	काष्ठा fixed_mdio_bus *fmb = &platक्रमm_fmb;
	काष्ठा fixed_phy *fp, *पंचांगp;

	mdiobus_unरेजिस्टर(fmb->mii_bus);
	mdiobus_मुक्त(fmb->mii_bus);
	platक्रमm_device_unरेजिस्टर(pdev);

	list_क्रम_each_entry_safe(fp, पंचांगp, &fmb->phys, node) अणु
		list_del(&fp->node);
		kमुक्त(fp);
	पूर्ण
	ida_destroy(&phy_fixed_ida);
पूर्ण
module_निकास(fixed_mdio_bus_निकास);

MODULE_DESCRIPTION("Fixed MDIO bus (MDIO bus emulation with fixed PHYs)");
MODULE_AUTHOR("Vitaly Bordug");
MODULE_LICENSE("GPL");
