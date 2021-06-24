<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * net/dsa/mv88e6060.c - Driver क्रम Marvell 88e6060 चयन chips
 * Copyright (c) 2008-2009 Marvell Semiconductor
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <net/dsa.h>
#समावेश "mv88e6060.h"

अटल पूर्णांक reg_पढ़ो(काष्ठा mv88e6060_priv *priv, पूर्णांक addr, पूर्णांक reg)
अणु
	वापस mdiobus_पढ़ो_nested(priv->bus, priv->sw_addr + addr, reg);
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा mv88e6060_priv *priv, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	वापस mdiobus_ग_लिखो_nested(priv->bus, priv->sw_addr + addr, reg, val);
पूर्ण

अटल स्थिर अक्षर *mv88e6060_get_name(काष्ठा mii_bus *bus, पूर्णांक sw_addr)
अणु
	पूर्णांक ret;

	ret = mdiobus_पढ़ो(bus, sw_addr + REG_PORT(0), PORT_SWITCH_ID);
	अगर (ret >= 0) अणु
		अगर (ret == PORT_SWITCH_ID_6060)
			वापस "Marvell 88E6060 (A0)";
		अगर (ret == PORT_SWITCH_ID_6060_R1 ||
		    ret == PORT_SWITCH_ID_6060_R2)
			वापस "Marvell 88E6060 (B0)";
		अगर ((ret & PORT_SWITCH_ID_6060_MASK) == PORT_SWITCH_ID_6060)
			वापस "Marvell 88E6060";
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत dsa_tag_protocol mv88e6060_get_tag_protocol(काष्ठा dsa_चयन *ds,
							पूर्णांक port,
							क्रमागत dsa_tag_protocol m)
अणु
	वापस DSA_TAG_PROTO_TRAILER;
पूर्ण

अटल पूर्णांक mv88e6060_चयन_reset(काष्ठा mv88e6060_priv *priv)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	/* Set all ports to the disabled state. */
	क्रम (i = 0; i < MV88E6060_PORTS; i++) अणु
		ret = reg_पढ़ो(priv, REG_PORT(i), PORT_CONTROL);
		अगर (ret < 0)
			वापस ret;
		ret = reg_ग_लिखो(priv, REG_PORT(i), PORT_CONTROL,
				ret & ~PORT_CONTROL_STATE_MASK);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Wait क्रम transmit queues to drain. */
	usleep_range(2000, 4000);

	/* Reset the चयन. */
	ret = reg_ग_लिखो(priv, REG_GLOBAL, GLOBAL_ATU_CONTROL,
			GLOBAL_ATU_CONTROL_SWRESET |
			GLOBAL_ATU_CONTROL_LEARNDIS);
	अगर (ret)
		वापस ret;

	/* Wait up to one second क्रम reset to complete. */
	समयout = jअगरfies + 1 * HZ;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		ret = reg_पढ़ो(priv, REG_GLOBAL, GLOBAL_STATUS);
		अगर (ret < 0)
			वापस ret;

		अगर (ret & GLOBAL_STATUS_INIT_READY)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण
	अगर (समय_after(jअगरfies, समयout))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6060_setup_global(काष्ठा mv88e6060_priv *priv)
अणु
	पूर्णांक ret;

	/* Disable discarding of frames with excessive collisions,
	 * set the maximum frame size to 1536 bytes, and mask all
	 * पूर्णांकerrupt sources.
	 */
	ret = reg_ग_लिखो(priv, REG_GLOBAL, GLOBAL_CONTROL,
			GLOBAL_CONTROL_MAX_FRAME_1536);
	अगर (ret)
		वापस ret;

	/* Disable स्वतःmatic address learning.
	 */
	वापस reg_ग_लिखो(priv, REG_GLOBAL, GLOBAL_ATU_CONTROL,
			 GLOBAL_ATU_CONTROL_LEARNDIS);
पूर्ण

अटल पूर्णांक mv88e6060_setup_port(काष्ठा mv88e6060_priv *priv, पूर्णांक p)
अणु
	पूर्णांक addr = REG_PORT(p);
	पूर्णांक ret;

	/* Do not क्रमce flow control, disable Ingress and Egress
	 * Header tagging, disable VLAN tunneling, and set the port
	 * state to Forwarding.  Additionally, अगर this is the CPU
	 * port, enable Ingress and Egress Trailer tagging mode.
	 */
	ret = reg_ग_लिखो(priv, addr, PORT_CONTROL,
			dsa_is_cpu_port(priv->ds, p) ?
			PORT_CONTROL_TRAILER |
			PORT_CONTROL_INGRESS_MODE |
			PORT_CONTROL_STATE_FORWARDING :
			PORT_CONTROL_STATE_FORWARDING);
	अगर (ret)
		वापस ret;

	/* Port based VLAN map: give each port its own address
	 * database, allow the CPU port to talk to each of the 'real'
	 * ports, and allow each of the 'real' ports to only talk to
	 * the CPU port.
	 */
	ret = reg_ग_लिखो(priv, addr, PORT_VLAN_MAP,
			((p & 0xf) << PORT_VLAN_MAP_DBNUM_SHIFT) |
			(dsa_is_cpu_port(priv->ds, p) ?
			 dsa_user_ports(priv->ds) :
			 BIT(dsa_to_port(priv->ds, p)->cpu_dp->index)));
	अगर (ret)
		वापस ret;

	/* Port Association Vector: when learning source addresses
	 * of packets, add the address to the address database using
	 * a port biपंचांगap that has only the bit क्रम this port set and
	 * the other bits clear.
	 */
	वापस reg_ग_लिखो(priv, addr, PORT_ASSOC_VECTOR, BIT(p));
पूर्ण

अटल पूर्णांक mv88e6060_setup_addr(काष्ठा mv88e6060_priv *priv)
अणु
	u8 addr[ETH_ALEN];
	पूर्णांक ret;
	u16 val;

	eth_अक्रमom_addr(addr);

	val = addr[0] << 8 | addr[1];

	/* The multicast bit is always transmitted as a zero, so the चयन uses
	 * bit 8 क्रम "DiffAddr", where 0 means all ports transmit the same SA.
	 */
	val &= 0xfeff;

	ret = reg_ग_लिखो(priv, REG_GLOBAL, GLOBAL_MAC_01, val);
	अगर (ret)
		वापस ret;

	ret = reg_ग_लिखो(priv, REG_GLOBAL, GLOBAL_MAC_23,
			(addr[2] << 8) | addr[3]);
	अगर (ret)
		वापस ret;

	वापस reg_ग_लिखो(priv, REG_GLOBAL, GLOBAL_MAC_45,
			 (addr[4] << 8) | addr[5]);
पूर्ण

अटल पूर्णांक mv88e6060_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mv88e6060_priv *priv = ds->priv;
	पूर्णांक ret;
	पूर्णांक i;

	priv->ds = ds;

	ret = mv88e6060_चयन_reset(priv);
	अगर (ret < 0)
		वापस ret;

	/* @@@ initialise atu */

	ret = mv88e6060_setup_global(priv);
	अगर (ret < 0)
		वापस ret;

	ret = mv88e6060_setup_addr(priv);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < MV88E6060_PORTS; i++) अणु
		ret = mv88e6060_setup_port(priv, i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6060_port_to_phy_addr(पूर्णांक port)
अणु
	अगर (port >= 0 && port < MV88E6060_PORTS)
		वापस port;
	वापस -1;
पूर्ण

अटल पूर्णांक mv88e6060_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा mv88e6060_priv *priv = ds->priv;
	पूर्णांक addr;

	addr = mv88e6060_port_to_phy_addr(port);
	अगर (addr == -1)
		वापस 0xffff;

	वापस reg_पढ़ो(priv, addr, regnum);
पूर्ण

अटल पूर्णांक
mv88e6060_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum, u16 val)
अणु
	काष्ठा mv88e6060_priv *priv = ds->priv;
	पूर्णांक addr;

	addr = mv88e6060_port_to_phy_addr(port);
	अगर (addr == -1)
		वापस 0xffff;

	वापस reg_ग_लिखो(priv, addr, regnum, val);
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops mv88e6060_चयन_ops = अणु
	.get_tag_protocol = mv88e6060_get_tag_protocol,
	.setup		= mv88e6060_setup,
	.phy_पढ़ो	= mv88e6060_phy_पढ़ो,
	.phy_ग_लिखो	= mv88e6060_phy_ग_लिखो,
पूर्ण;

अटल पूर्णांक mv88e6060_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा device *dev = &mdiodev->dev;
	काष्ठा mv88e6060_priv *priv;
	काष्ठा dsa_चयन *ds;
	स्थिर अक्षर *name;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->bus = mdiodev->bus;
	priv->sw_addr = mdiodev->addr;

	name = mv88e6060_get_name(priv->bus, priv->sw_addr);
	अगर (!name)
		वापस -ENODEV;

	dev_info(dev, "switch %s detected\n", name);

	ds = devm_kzalloc(dev, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस -ENOMEM;

	ds->dev = dev;
	ds->num_ports = MV88E6060_PORTS;
	ds->priv = priv;
	ds->dev = dev;
	ds->ops = &mv88e6060_चयन_ops;

	dev_set_drvdata(dev, ds);

	वापस dsa_रेजिस्टर_चयन(ds);
पूर्ण

अटल व्योम mv88e6060_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा dsa_चयन *ds = dev_get_drvdata(&mdiodev->dev);

	dsa_unरेजिस्टर_चयन(ds);
पूर्ण

अटल स्थिर काष्ठा of_device_id mv88e6060_of_match[] = अणु
	अणु
		.compatible = "marvell,mv88e6060",
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा mdio_driver mv88e6060_driver = अणु
	.probe	= mv88e6060_probe,
	.हटाओ = mv88e6060_हटाओ,
	.mdiodrv.driver = अणु
		.name = "mv88e6060",
		.of_match_table = mv88e6060_of_match,
	पूर्ण,
पूर्ण;

mdio_module_driver(mv88e6060_driver);

MODULE_AUTHOR("Lennert Buytenhek <buytenh@wantstofly.org>");
MODULE_DESCRIPTION("Driver for Marvell 88E6060 ethernet switch chip");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mv88e6060");
