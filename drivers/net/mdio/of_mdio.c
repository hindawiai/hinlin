<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OF helpers क्रम the MDIO (Ethernet PHY) API
 *
 * Copyright (c) 2009 Secret Lab Technologies, Ltd.
 *
 * This file provides helper functions क्रम extracting PHY device inक्रमmation
 * out of the OpenFirmware device tree and using it to populate an mii_bus.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>

#घोषणा DEFAULT_GPIO_RESET_DELAY	10	/* in microseconds */

MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_LICENSE("GPL");

/* Extract the clause 22 phy ID from the compatible string of the क्रमm
 * ethernet-phy-idAAAA.BBBB */
अटल पूर्णांक of_get_phy_id(काष्ठा device_node *device, u32 *phy_id)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *cp;
	अचिन्हित पूर्णांक upper, lower;

	of_property_क्रम_each_string(device, "compatible", prop, cp) अणु
		अगर (माला_पूछो(cp, "ethernet-phy-id%4x.%4x", &upper, &lower) == 2) अणु
			*phy_id = ((upper & 0xFFFF) << 16) | (lower & 0xFFFF);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल काष्ठा mii_बारtamper *of_find_mii_बारtamper(काष्ठा device_node *node)
अणु
	काष्ठा of_phandle_args arg;
	पूर्णांक err;

	err = of_parse_phandle_with_fixed_args(node, "timestamper", 1, 0, &arg);

	अगर (err == -ENOENT)
		वापस शून्य;
	अन्यथा अगर (err)
		वापस ERR_PTR(err);

	अगर (arg.args_count != 1)
		वापस ERR_PTR(-EINVAL);

	वापस रेजिस्टर_mii_बारtamper(arg.np, arg.args[0]);
पूर्ण

पूर्णांक of_mdiobus_phy_device_रेजिस्टर(काष्ठा mii_bus *mdio, काष्ठा phy_device *phy,
			      काष्ठा device_node *child, u32 addr)
अणु
	पूर्णांक rc;

	rc = of_irq_get(child, 0);
	अगर (rc == -EPROBE_DEFER)
		वापस rc;

	अगर (rc > 0) अणु
		phy->irq = rc;
		mdio->irq[addr] = rc;
	पूर्ण अन्यथा अणु
		phy->irq = mdio->irq[addr];
	पूर्ण

	अगर (of_property_पढ़ो_bool(child, "broken-turn-around"))
		mdio->phy_ignore_ta_mask |= 1 << addr;

	of_property_पढ़ो_u32(child, "reset-assert-us",
			     &phy->mdio.reset_निश्चित_delay);
	of_property_पढ़ो_u32(child, "reset-deassert-us",
			     &phy->mdio.reset_deनिश्चित_delay);

	/* Associate the OF node with the device काष्ठाure so it
	 * can be looked up later */
	of_node_get(child);
	phy->mdio.dev.of_node = child;
	phy->mdio.dev.fwnode = of_fwnode_handle(child);

	/* All data is now stored in the phy काष्ठा;
	 * रेजिस्टर it */
	rc = phy_device_रेजिस्टर(phy);
	अगर (rc) अणु
		of_node_put(child);
		वापस rc;
	पूर्ण

	dev_dbg(&mdio->dev, "registered phy %pOFn at address %i\n",
		child, addr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(of_mdiobus_phy_device_रेजिस्टर);

अटल पूर्णांक of_mdiobus_रेजिस्टर_phy(काष्ठा mii_bus *mdio,
				    काष्ठा device_node *child, u32 addr)
अणु
	काष्ठा mii_बारtamper *mii_ts;
	काष्ठा phy_device *phy;
	bool is_c45;
	पूर्णांक rc;
	u32 phy_id;

	mii_ts = of_find_mii_बारtamper(child);
	अगर (IS_ERR(mii_ts))
		वापस PTR_ERR(mii_ts);

	is_c45 = of_device_is_compatible(child,
					 "ethernet-phy-ieee802.3-c45");

	अगर (!is_c45 && !of_get_phy_id(child, &phy_id))
		phy = phy_device_create(mdio, addr, phy_id, 0, शून्य);
	अन्यथा
		phy = get_phy_device(mdio, addr, is_c45);
	अगर (IS_ERR(phy)) अणु
		अगर (mii_ts)
			unरेजिस्टर_mii_बारtamper(mii_ts);
		वापस PTR_ERR(phy);
	पूर्ण

	rc = of_mdiobus_phy_device_रेजिस्टर(mdio, phy, child, addr);
	अगर (rc) अणु
		अगर (mii_ts)
			unरेजिस्टर_mii_बारtamper(mii_ts);
		phy_device_मुक्त(phy);
		वापस rc;
	पूर्ण

	/* phy->mii_ts may alपढ़ोy be defined by the PHY driver. A
	 * mii_बारtamper probed via the device tree will still have
	 * precedence.
	 */
	अगर (mii_ts)
		phy->mii_ts = mii_ts;

	वापस 0;
पूर्ण

अटल पूर्णांक of_mdiobus_रेजिस्टर_device(काष्ठा mii_bus *mdio,
				      काष्ठा device_node *child, u32 addr)
अणु
	काष्ठा mdio_device *mdiodev;
	पूर्णांक rc;

	mdiodev = mdio_device_create(mdio, addr);
	अगर (IS_ERR(mdiodev))
		वापस PTR_ERR(mdiodev);

	/* Associate the OF node with the device काष्ठाure so it
	 * can be looked up later.
	 */
	of_node_get(child);
	mdiodev->dev.of_node = child;
	mdiodev->dev.fwnode = of_fwnode_handle(child);

	/* All data is now stored in the mdiodev काष्ठा; रेजिस्टर it. */
	rc = mdio_device_रेजिस्टर(mdiodev);
	अगर (rc) अणु
		mdio_device_मुक्त(mdiodev);
		of_node_put(child);
		वापस rc;
	पूर्ण

	dev_dbg(&mdio->dev, "registered mdio device %pOFn at address %i\n",
		child, addr);
	वापस 0;
पूर्ण

/* The following is a list of PHY compatible strings which appear in
 * some DTBs. The compatible string is never matched against a PHY
 * driver, so is poपूर्णांकless. We only expect devices which are not PHYs
 * to have a compatible string, so they can be matched to an MDIO
 * driver.  Encourage users to upgrade their DT blobs to हटाओ these.
 */
अटल स्थिर काष्ठा of_device_id whitelist_phys[] = अणु
	अणु .compatible = "brcm,40nm-ephy" पूर्ण,
	अणु .compatible = "broadcom,bcm5241" पूर्ण,
	अणु .compatible = "marvell,88E1111", पूर्ण,
	अणु .compatible = "marvell,88e1116", पूर्ण,
	अणु .compatible = "marvell,88e1118", पूर्ण,
	अणु .compatible = "marvell,88e1145", पूर्ण,
	अणु .compatible = "marvell,88e1149r", पूर्ण,
	अणु .compatible = "marvell,88e1310", पूर्ण,
	अणु .compatible = "marvell,88E1510", पूर्ण,
	अणु .compatible = "marvell,88E1514", पूर्ण,
	अणु .compatible = "moxa,moxart-rtl8201cp", पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Return true अगर the child node is क्रम a phy. It must either:
 * o Compatible string of "ethernet-phy-idX.X"
 * o Compatible string of "ethernet-phy-ieee802.3-c45"
 * o Compatible string of "ethernet-phy-ieee802.3-c22"
 * o In the white list above (and issue a warning)
 * o No compatibility string
 *
 * A device which is not a phy is expected to have a compatible string
 * indicating what sort of device it is.
 */
bool of_mdiobus_child_is_phy(काष्ठा device_node *child)
अणु
	u32 phy_id;

	अगर (of_get_phy_id(child, &phy_id) != -EINVAL)
		वापस true;

	अगर (of_device_is_compatible(child, "ethernet-phy-ieee802.3-c45"))
		वापस true;

	अगर (of_device_is_compatible(child, "ethernet-phy-ieee802.3-c22"))
		वापस true;

	अगर (of_match_node(whitelist_phys, child)) अणु
		pr_warn(FW_WARN
			"%pOF: Whitelisted compatible string. Please remove\n",
			child);
		वापस true;
	पूर्ण

	अगर (!of_find_property(child, "compatible", शून्य))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(of_mdiobus_child_is_phy);

/**
 * of_mdiobus_रेजिस्टर - Register mii_bus and create PHYs from the device tree
 * @mdio: poपूर्णांकer to mii_bus काष्ठाure
 * @np: poपूर्णांकer to device_node of MDIO bus.
 *
 * This function रेजिस्टरs the mii_bus काष्ठाure and रेजिस्टरs a phy_device
 * क्रम each child node of @np.
 */
पूर्णांक of_mdiobus_रेजिस्टर(काष्ठा mii_bus *mdio, काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	bool scanphys = false;
	पूर्णांक addr, rc;

	अगर (!np)
		वापस mdiobus_रेजिस्टर(mdio);

	/* Do not जारी अगर the node is disabled */
	अगर (!of_device_is_available(np))
		वापस -ENODEV;

	/* Mask out all PHYs from स्वतः probing.  Instead the PHYs listed in
	 * the device tree are populated after the bus has been रेजिस्टरed */
	mdio->phy_mask = ~0;

	mdio->dev.of_node = np;
	mdio->dev.fwnode = of_fwnode_handle(np);

	/* Get bus level PHY reset GPIO details */
	mdio->reset_delay_us = DEFAULT_GPIO_RESET_DELAY;
	of_property_पढ़ो_u32(np, "reset-delay-us", &mdio->reset_delay_us);
	mdio->reset_post_delay_us = 0;
	of_property_पढ़ो_u32(np, "reset-post-delay-us", &mdio->reset_post_delay_us);

	/* Register the MDIO bus */
	rc = mdiobus_रेजिस्टर(mdio);
	अगर (rc)
		वापस rc;

	/* Loop over the child nodes and रेजिस्टर a phy_device क्रम each phy */
	क्रम_each_available_child_of_node(np, child) अणु
		addr = of_mdio_parse_addr(&mdio->dev, child);
		अगर (addr < 0) अणु
			scanphys = true;
			जारी;
		पूर्ण

		अगर (of_mdiobus_child_is_phy(child))
			rc = of_mdiobus_रेजिस्टर_phy(mdio, child, addr);
		अन्यथा
			rc = of_mdiobus_रेजिस्टर_device(mdio, child, addr);

		अगर (rc == -ENODEV)
			dev_err(&mdio->dev,
				"MDIO device at address %d is missing.\n",
				addr);
		अन्यथा अगर (rc)
			जाओ unरेजिस्टर;
	पूर्ण

	अगर (!scanphys)
		वापस 0;

	/* स्वतः scan क्रम PHYs with empty reg property */
	क्रम_each_available_child_of_node(np, child) अणु
		/* Skip PHYs with reg property set */
		अगर (of_find_property(child, "reg", शून्य))
			जारी;

		क्रम (addr = 0; addr < PHY_MAX_ADDR; addr++) अणु
			/* skip alपढ़ोy रेजिस्टरed PHYs */
			अगर (mdiobus_is_रेजिस्टरed_device(mdio, addr))
				जारी;

			/* be noisy to encourage people to set reg property */
			dev_info(&mdio->dev, "scan phy %pOFn at address %i\n",
				 child, addr);

			अगर (of_mdiobus_child_is_phy(child)) अणु
				/* -ENODEV is the वापस code that PHYLIB has
				 * standardized on to indicate that bus
				 * scanning should जारी.
				 */
				rc = of_mdiobus_रेजिस्टर_phy(mdio, child, addr);
				अगर (!rc)
					अवरोध;
				अगर (rc != -ENODEV)
					जाओ unरेजिस्टर;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

unरेजिस्टर:
	mdiobus_unरेजिस्टर(mdio);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(of_mdiobus_रेजिस्टर);

/**
 * of_mdio_find_device - Given a device tree node, find the mdio_device
 * @np: poपूर्णांकer to the mdio_device's device tree node
 *
 * If successful, वापसs a poपूर्णांकer to the mdio_device with the embedded
 * काष्ठा device refcount incremented by one, or शून्य on failure.
 * The caller should call put_device() on the mdio_device after its use
 */
काष्ठा mdio_device *of_mdio_find_device(काष्ठा device_node *np)
अणु
	काष्ठा device *d;

	अगर (!np)
		वापस शून्य;

	d = bus_find_device_by_of_node(&mdio_bus_type, np);
	अगर (!d)
		वापस शून्य;

	वापस to_mdio_device(d);
पूर्ण
EXPORT_SYMBOL(of_mdio_find_device);

/**
 * of_phy_find_device - Give a PHY node, find the phy_device
 * @phy_np: Poपूर्णांकer to the phy's device tree node
 *
 * If successful, वापसs a poपूर्णांकer to the phy_device with the embedded
 * काष्ठा device refcount incremented by one, or शून्य on failure.
 */
काष्ठा phy_device *of_phy_find_device(काष्ठा device_node *phy_np)
अणु
	काष्ठा mdio_device *mdiodev;

	mdiodev = of_mdio_find_device(phy_np);
	अगर (!mdiodev)
		वापस शून्य;

	अगर (mdiodev->flags & MDIO_DEVICE_FLAG_PHY)
		वापस to_phy_device(&mdiodev->dev);

	put_device(&mdiodev->dev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_phy_find_device);

/**
 * of_phy_connect - Connect to the phy described in the device tree
 * @dev: poपूर्णांकer to net_device claiming the phy
 * @phy_np: Poपूर्णांकer to device tree node क्रम the PHY
 * @hndlr: Link state callback क्रम the network device
 * @flags: flags to pass to the PHY
 * @अगरace: PHY data पूर्णांकerface type
 *
 * If successful, वापसs a poपूर्णांकer to the phy_device with the embedded
 * काष्ठा device refcount incremented by one, or शून्य on failure. The
 * refcount must be dropped by calling phy_disconnect() or phy_detach().
 */
काष्ठा phy_device *of_phy_connect(काष्ठा net_device *dev,
				  काष्ठा device_node *phy_np,
				  व्योम (*hndlr)(काष्ठा net_device *), u32 flags,
				  phy_पूर्णांकerface_t अगरace)
अणु
	काष्ठा phy_device *phy = of_phy_find_device(phy_np);
	पूर्णांक ret;

	अगर (!phy)
		वापस शून्य;

	phy->dev_flags |= flags;

	ret = phy_connect_direct(dev, phy, hndlr, अगरace);

	/* refcount is held by phy_connect_direct() on success */
	put_device(&phy->mdio.dev);

	वापस ret ? शून्य : phy;
पूर्ण
EXPORT_SYMBOL(of_phy_connect);

/**
 * of_phy_get_and_connect
 * - Get phy node and connect to the phy described in the device tree
 * @dev: poपूर्णांकer to net_device claiming the phy
 * @np: Poपूर्णांकer to device tree node क्रम the net_device claiming the phy
 * @hndlr: Link state callback क्रम the network device
 *
 * If successful, वापसs a poपूर्णांकer to the phy_device with the embedded
 * काष्ठा device refcount incremented by one, or शून्य on failure. The
 * refcount must be dropped by calling phy_disconnect() or phy_detach().
 */
काष्ठा phy_device *of_phy_get_and_connect(काष्ठा net_device *dev,
					  काष्ठा device_node *np,
					  व्योम (*hndlr)(काष्ठा net_device *))
अणु
	phy_पूर्णांकerface_t अगरace;
	काष्ठा device_node *phy_np;
	काष्ठा phy_device *phy;
	पूर्णांक ret;

	ret = of_get_phy_mode(np, &अगरace);
	अगर (ret)
		वापस शून्य;
	अगर (of_phy_is_fixed_link(np)) अणु
		ret = of_phy_रेजिस्टर_fixed_link(np);
		अगर (ret < 0) अणु
			netdev_err(dev, "broken fixed-link specification\n");
			वापस शून्य;
		पूर्ण
		phy_np = of_node_get(np);
	पूर्ण अन्यथा अणु
		phy_np = of_parse_phandle(np, "phy-handle", 0);
		अगर (!phy_np)
			वापस शून्य;
	पूर्ण

	phy = of_phy_connect(dev, phy_np, hndlr, 0, अगरace);

	of_node_put(phy_np);

	वापस phy;
पूर्ण
EXPORT_SYMBOL(of_phy_get_and_connect);

/*
 * of_phy_is_fixed_link() and of_phy_रेजिस्टर_fixed_link() must
 * support two DT bindings:
 * - the old DT binding, where 'fixed-link' was a property with 5
 *   cells encoding various inक्रमmations about the fixed PHY
 * - the new DT binding, where 'fixed-link' is a sub-node of the
 *   Ethernet device.
 */
bool of_phy_is_fixed_link(काष्ठा device_node *np)
अणु
	काष्ठा device_node *dn;
	पूर्णांक len, err;
	स्थिर अक्षर *managed;

	/* New binding */
	dn = of_get_child_by_name(np, "fixed-link");
	अगर (dn) अणु
		of_node_put(dn);
		वापस true;
	पूर्ण

	err = of_property_पढ़ो_string(np, "managed", &managed);
	अगर (err == 0 && म_भेद(managed, "auto") != 0)
		वापस true;

	/* Old binding */
	अगर (of_get_property(np, "fixed-link", &len) &&
	    len == (5 * माप(__be32)))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(of_phy_is_fixed_link);

पूर्णांक of_phy_रेजिस्टर_fixed_link(काष्ठा device_node *np)
अणु
	काष्ठा fixed_phy_status status = अणुपूर्ण;
	काष्ठा device_node *fixed_link_node;
	u32 fixed_link_prop[5];
	स्थिर अक्षर *managed;

	अगर (of_property_पढ़ो_string(np, "managed", &managed) == 0 &&
	    म_भेद(managed, "in-band-status") == 0) अणु
		/* status is zeroed, namely its .link member */
		जाओ रेजिस्टर_phy;
	पूर्ण

	/* New binding */
	fixed_link_node = of_get_child_by_name(np, "fixed-link");
	अगर (fixed_link_node) अणु
		status.link = 1;
		status.duplex = of_property_पढ़ो_bool(fixed_link_node,
						      "full-duplex");
		अगर (of_property_पढ़ो_u32(fixed_link_node, "speed",
					 &status.speed)) अणु
			of_node_put(fixed_link_node);
			वापस -EINVAL;
		पूर्ण
		status.छोड़ो = of_property_पढ़ो_bool(fixed_link_node, "pause");
		status.asym_छोड़ो = of_property_पढ़ो_bool(fixed_link_node,
							  "asym-pause");
		of_node_put(fixed_link_node);

		जाओ रेजिस्टर_phy;
	पूर्ण

	/* Old binding */
	अगर (of_property_पढ़ो_u32_array(np, "fixed-link", fixed_link_prop,
				       ARRAY_SIZE(fixed_link_prop)) == 0) अणु
		status.link = 1;
		status.duplex = fixed_link_prop[1];
		status.speed  = fixed_link_prop[2];
		status.छोड़ो  = fixed_link_prop[3];
		status.asym_छोड़ो = fixed_link_prop[4];
		जाओ रेजिस्टर_phy;
	पूर्ण

	वापस -ENODEV;

रेजिस्टर_phy:
	वापस PTR_ERR_OR_ZERO(fixed_phy_रेजिस्टर(PHY_POLL, &status, np));
पूर्ण
EXPORT_SYMBOL(of_phy_रेजिस्टर_fixed_link);

व्योम of_phy_deरेजिस्टर_fixed_link(काष्ठा device_node *np)
अणु
	काष्ठा phy_device *phydev;

	phydev = of_phy_find_device(np);
	अगर (!phydev)
		वापस;

	fixed_phy_unरेजिस्टर(phydev);

	put_device(&phydev->mdio.dev);	/* of_phy_find_device() */
	phy_device_मुक्त(phydev);	/* fixed_phy_रेजिस्टर() */
पूर्ण
EXPORT_SYMBOL(of_phy_deरेजिस्टर_fixed_link);
