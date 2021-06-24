<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Distributed Switch Architecture loopback driver
 *
 * Copyright (C) 2016, Florian Fainelli <f.fainelli@gmail.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/export.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/dsa/loop.h>
#समावेश <net/dsa.h>

#समावेश "dsa_loop.h"

अटल काष्ठा dsa_loop_mib_entry dsa_loop_mibs[] = अणु
	[DSA_LOOP_PHY_READ_OK]	= अणु "phy_read_ok", पूर्ण,
	[DSA_LOOP_PHY_READ_ERR]	= अणु "phy_read_err", पूर्ण,
	[DSA_LOOP_PHY_WRITE_OK] = अणु "phy_write_ok", पूर्ण,
	[DSA_LOOP_PHY_WRITE_ERR] = अणु "phy_write_err", पूर्ण,
पूर्ण;

अटल काष्ठा phy_device *phydevs[PHY_MAX_ADDR];

क्रमागत dsa_loop_devlink_resource_id अणु
	DSA_LOOP_DEVLINK_PARAM_ID_VTU,
पूर्ण;

अटल u64 dsa_loop_devlink_vtu_get(व्योम *priv)
अणु
	काष्ठा dsa_loop_priv *ps = priv;
	अचिन्हित पूर्णांक i, count = 0;
	काष्ठा dsa_loop_vlan *vl;

	क्रम (i = 0; i < ARRAY_SIZE(ps->vlans); i++) अणु
		vl = &ps->vlans[i];
		अगर (vl->members)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक dsa_loop_setup_devlink_resources(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा devlink_resource_size_params size_params;
	काष्ठा dsa_loop_priv *ps = ds->priv;
	पूर्णांक err;

	devlink_resource_size_params_init(&size_params, ARRAY_SIZE(ps->vlans),
					  ARRAY_SIZE(ps->vlans),
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	err = dsa_devlink_resource_रेजिस्टर(ds, "VTU", ARRAY_SIZE(ps->vlans),
					    DSA_LOOP_DEVLINK_PARAM_ID_VTU,
					    DEVLINK_RESOURCE_ID_PARENT_TOP,
					    &size_params);
	अगर (err)
		जाओ out;

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      DSA_LOOP_DEVLINK_PARAM_ID_VTU,
					      dsa_loop_devlink_vtu_get, ps);

	वापस 0;

out:
	dsa_devlink_resources_unरेजिस्टर(ds);
	वापस err;
पूर्ण

अटल क्रमागत dsa_tag_protocol dsa_loop_get_protocol(काष्ठा dsa_चयन *ds,
						   पूर्णांक port,
						   क्रमागत dsa_tag_protocol mp)
अणु
	dev_dbg(ds->dev, "%s: port: %d\n", __func__, port);

	वापस DSA_TAG_PROTO_NONE;
पूर्ण

अटल पूर्णांक dsa_loop_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_loop_priv *ps = ds->priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ds->num_ports; i++)
		स_नकल(ps->ports[i].mib, dsa_loop_mibs,
		       माप(dsa_loop_mibs));

	dev_dbg(ds->dev, "%s\n", __func__);

	वापस dsa_loop_setup_devlink_resources(ds);
पूर्ण

अटल व्योम dsa_loop_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	dsa_devlink_resources_unरेजिस्टर(ds);
पूर्ण

अटल पूर्णांक dsa_loop_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS && sset != ETH_SS_PHY_STATS)
		वापस 0;

	वापस __DSA_LOOP_CNT_MAX;
पूर्ण

अटल व्योम dsa_loop_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 u32 stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा dsa_loop_priv *ps = ds->priv;
	अचिन्हित पूर्णांक i;

	अगर (stringset != ETH_SS_STATS && stringset != ETH_SS_PHY_STATS)
		वापस;

	क्रम (i = 0; i < __DSA_LOOP_CNT_MAX; i++)
		स_नकल(data + i * ETH_GSTRING_LEN,
		       ps->ports[port].mib[i].name, ETH_GSTRING_LEN);
पूर्ण

अटल व्योम dsa_loop_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       uपूर्णांक64_t *data)
अणु
	काष्ठा dsa_loop_priv *ps = ds->priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < __DSA_LOOP_CNT_MAX; i++)
		data[i] = ps->ports[port].mib[i].val;
पूर्ण

अटल पूर्णांक dsa_loop_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा dsa_loop_priv *ps = ds->priv;
	काष्ठा mii_bus *bus = ps->bus;
	पूर्णांक ret;

	ret = mdiobus_पढ़ो_nested(bus, ps->port_base + port, regnum);
	अगर (ret < 0)
		ps->ports[port].mib[DSA_LOOP_PHY_READ_ERR].val++;
	अन्यथा
		ps->ports[port].mib[DSA_LOOP_PHY_READ_OK].val++;

	वापस ret;
पूर्ण

अटल पूर्णांक dsa_loop_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      पूर्णांक regnum, u16 value)
अणु
	काष्ठा dsa_loop_priv *ps = ds->priv;
	काष्ठा mii_bus *bus = ps->bus;
	पूर्णांक ret;

	ret = mdiobus_ग_लिखो_nested(bus, ps->port_base + port, regnum, value);
	अगर (ret < 0)
		ps->ports[port].mib[DSA_LOOP_PHY_WRITE_ERR].val++;
	अन्यथा
		ps->ports[port].mib[DSA_LOOP_PHY_WRITE_OK].val++;

	वापस ret;
पूर्ण

अटल पूर्णांक dsa_loop_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा net_device *bridge)
अणु
	dev_dbg(ds->dev, "%s: port: %d, bridge: %s\n",
		__func__, port, bridge->name);

	वापस 0;
पूर्ण

अटल व्योम dsa_loop_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       काष्ठा net_device *bridge)
अणु
	dev_dbg(ds->dev, "%s: port: %d, bridge: %s\n",
		__func__, port, bridge->name);
पूर्ण

अटल व्योम dsa_loop_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
					u8 state)
अणु
	dev_dbg(ds->dev, "%s: port: %d, state: %d\n",
		__func__, port, state);
पूर्ण

अटल पूर्णांक dsa_loop_port_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port,
					bool vlan_filtering,
					काष्ठा netlink_ext_ack *extack)
अणु
	dev_dbg(ds->dev, "%s: port: %d, vlan_filtering: %d\n",
		__func__, port, vlan_filtering);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_loop_port_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				  काष्ठा netlink_ext_ack *extack)
अणु
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा dsa_loop_priv *ps = ds->priv;
	काष्ठा mii_bus *bus = ps->bus;
	काष्ठा dsa_loop_vlan *vl;

	अगर (vlan->vid >= ARRAY_SIZE(ps->vlans))
		वापस -दुस्फल;

	/* Just करो a sleeping operation to make lockdep checks effective */
	mdiobus_पढ़ो(bus, ps->port_base + port, MII_BMSR);

	vl = &ps->vlans[vlan->vid];

	vl->members |= BIT(port);
	अगर (untagged)
		vl->untagged |= BIT(port);
	अन्यथा
		vl->untagged &= ~BIT(port);

	dev_dbg(ds->dev, "%s: port: %d vlan: %d, %stagged, pvid: %d\n",
		__func__, port, vlan->vid, untagged ? "un" : "", pvid);

	अगर (pvid)
		ps->ports[port].pvid = vlan->vid;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_loop_port_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	काष्ठा dsa_loop_priv *ps = ds->priv;
	u16 pvid = ps->ports[port].pvid;
	काष्ठा mii_bus *bus = ps->bus;
	काष्ठा dsa_loop_vlan *vl;

	/* Just करो a sleeping operation to make lockdep checks effective */
	mdiobus_पढ़ो(bus, ps->port_base + port, MII_BMSR);

	vl = &ps->vlans[vlan->vid];

	vl->members &= ~BIT(port);
	अगर (untagged)
		vl->untagged &= ~BIT(port);

	अगर (pvid == vlan->vid)
		pvid = 1;

	dev_dbg(ds->dev, "%s: port: %d vlan: %d, %stagged, pvid: %d\n",
		__func__, port, vlan->vid, untagged ? "un" : "", pvid);
	ps->ports[port].pvid = pvid;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_loop_port_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    पूर्णांक new_mtu)
अणु
	काष्ठा dsa_loop_priv *priv = ds->priv;

	priv->ports[port].mtu = new_mtu;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_loop_port_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस ETH_MAX_MTU;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops dsa_loop_driver = अणु
	.get_tag_protocol	= dsa_loop_get_protocol,
	.setup			= dsa_loop_setup,
	.tearकरोwn		= dsa_loop_tearकरोwn,
	.get_strings		= dsa_loop_get_strings,
	.get_ethtool_stats	= dsa_loop_get_ethtool_stats,
	.get_sset_count		= dsa_loop_get_sset_count,
	.get_ethtool_phy_stats	= dsa_loop_get_ethtool_stats,
	.phy_पढ़ो		= dsa_loop_phy_पढ़ो,
	.phy_ग_लिखो		= dsa_loop_phy_ग_लिखो,
	.port_bridge_join	= dsa_loop_port_bridge_join,
	.port_bridge_leave	= dsa_loop_port_bridge_leave,
	.port_stp_state_set	= dsa_loop_port_stp_state_set,
	.port_vlan_filtering	= dsa_loop_port_vlan_filtering,
	.port_vlan_add		= dsa_loop_port_vlan_add,
	.port_vlan_del		= dsa_loop_port_vlan_del,
	.port_change_mtu	= dsa_loop_port_change_mtu,
	.port_max_mtu		= dsa_loop_port_max_mtu,
पूर्ण;

अटल पूर्णांक dsa_loop_drv_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा dsa_loop_pdata *pdata = mdiodev->dev.platक्रमm_data;
	काष्ठा dsa_loop_priv *ps;
	काष्ठा dsa_चयन *ds;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -ENODEV;

	ds = devm_kzalloc(&mdiodev->dev, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस -ENOMEM;

	ds->dev = &mdiodev->dev;
	ds->num_ports = DSA_LOOP_NUM_PORTS;

	ps = devm_kzalloc(&mdiodev->dev, माप(*ps), GFP_KERNEL);
	अगर (!ps)
		वापस -ENOMEM;

	ps->netdev = dev_get_by_name(&init_net, pdata->netdev);
	अगर (!ps->netdev)
		वापस -EPROBE_DEFER;

	pdata->cd.netdev[DSA_LOOP_CPU_PORT] = &ps->netdev->dev;

	ds->dev = &mdiodev->dev;
	ds->ops = &dsa_loop_driver;
	ds->priv = ps;
	ps->bus = mdiodev->bus;

	dev_set_drvdata(&mdiodev->dev, ds);

	ret = dsa_रेजिस्टर_चयन(ds);
	अगर (!ret)
		dev_info(&mdiodev->dev, "%s: 0x%0x\n",
			 pdata->name, pdata->enabled_ports);

	वापस ret;
पूर्ण

अटल व्योम dsa_loop_drv_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा dsa_चयन *ds = dev_get_drvdata(&mdiodev->dev);
	काष्ठा dsa_loop_priv *ps = ds->priv;

	dsa_unरेजिस्टर_चयन(ds);
	dev_put(ps->netdev);
पूर्ण

अटल काष्ठा mdio_driver dsa_loop_drv = अणु
	.mdiodrv.driver	= अणु
		.name	= "dsa-loop",
	पूर्ण,
	.probe	= dsa_loop_drv_probe,
	.हटाओ	= dsa_loop_drv_हटाओ,
पूर्ण;

#घोषणा NUM_FIXED_PHYS	(DSA_LOOP_NUM_PORTS - 2)

अटल पूर्णांक __init dsa_loop_init(व्योम)
अणु
	काष्ठा fixed_phy_status status = अणु
		.link = 1,
		.speed = SPEED_100,
		.duplex = DUPLEX_FULL,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_FIXED_PHYS; i++)
		phydevs[i] = fixed_phy_रेजिस्टर(PHY_POLL, &status, शून्य);

	वापस mdio_driver_रेजिस्टर(&dsa_loop_drv);
पूर्ण
module_init(dsa_loop_init);

अटल व्योम __निकास dsa_loop_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	mdio_driver_unरेजिस्टर(&dsa_loop_drv);
	क्रम (i = 0; i < NUM_FIXED_PHYS; i++)
		अगर (!IS_ERR(phydevs[i]))
			fixed_phy_unरेजिस्टर(phydevs[i]);
पूर्ण
module_निकास(dsa_loop_निकास);

MODULE_SOFTDEP("pre: dsa_loop_bdinfo");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Fainelli");
MODULE_DESCRIPTION("DSA loopback driver");
