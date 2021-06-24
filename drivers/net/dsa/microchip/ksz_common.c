<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip चयन driver मुख्य logic
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/microchip-ksz.h>
#समावेश <linux/phy.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/of_net.h>
#समावेश <net/dsa.h>
#समावेश <net/चयनdev.h>

#समावेश "ksz_common.h"

व्योम ksz_update_port_member(काष्ठा ksz_device *dev, पूर्णांक port)
अणु
	काष्ठा ksz_port *p;
	पूर्णांक i;

	क्रम (i = 0; i < dev->port_cnt; i++) अणु
		अगर (i == port || i == dev->cpu_port)
			जारी;
		p = &dev->ports[i];
		अगर (!(dev->member & (1 << i)))
			जारी;

		/* Port is a member of the bridge and is क्रमwarding. */
		अगर (p->stp_state == BR_STATE_FORWARDING &&
		    p->member != dev->member)
			dev->dev_ops->cfg_port_member(dev, i, dev->member);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ksz_update_port_member);

अटल व्योम port_r_cnt(काष्ठा ksz_device *dev, पूर्णांक port)
अणु
	काष्ठा ksz_port_mib *mib = &dev->ports[port].mib;
	u64 *dropped;

	/* Some ports may not have MIB counters beक्रमe SWITCH_COUNTER_NUM. */
	जबतक (mib->cnt_ptr < dev->reg_mib_cnt) अणु
		dev->dev_ops->r_mib_cnt(dev, port, mib->cnt_ptr,
					&mib->counters[mib->cnt_ptr]);
		++mib->cnt_ptr;
	पूर्ण

	/* last one in storage */
	dropped = &mib->counters[dev->mib_cnt];

	/* Some ports may not have MIB counters after SWITCH_COUNTER_NUM. */
	जबतक (mib->cnt_ptr < dev->mib_cnt) अणु
		dev->dev_ops->r_mib_pkt(dev, port, mib->cnt_ptr,
					dropped, &mib->counters[mib->cnt_ptr]);
		++mib->cnt_ptr;
	पूर्ण
	mib->cnt_ptr = 0;
पूर्ण

अटल व्योम ksz_mib_पढ़ो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ksz_device *dev = container_of(work, काष्ठा ksz_device,
					      mib_पढ़ो.work);
	काष्ठा ksz_port_mib *mib;
	काष्ठा ksz_port *p;
	पूर्णांक i;

	क्रम (i = 0; i < dev->port_cnt; i++) अणु
		अगर (dsa_is_unused_port(dev->ds, i))
			जारी;

		p = &dev->ports[i];
		mib = &p->mib;
		mutex_lock(&mib->cnt_mutex);

		/* Only पढ़ो MIB counters when the port is told to करो.
		 * If not, पढ़ो only dropped counters when link is not up.
		 */
		अगर (!p->पढ़ो) अणु
			स्थिर काष्ठा dsa_port *dp = dsa_to_port(dev->ds, i);

			अगर (!netअगर_carrier_ok(dp->slave))
				mib->cnt_ptr = dev->reg_mib_cnt;
		पूर्ण
		port_r_cnt(dev, i);
		p->पढ़ो = false;
		mutex_unlock(&mib->cnt_mutex);
	पूर्ण

	schedule_delayed_work(&dev->mib_पढ़ो, dev->mib_पढ़ो_पूर्णांकerval);
पूर्ण

व्योम ksz_init_mib_समयr(काष्ठा ksz_device *dev)
अणु
	पूर्णांक i;

	INIT_DELAYED_WORK(&dev->mib_पढ़ो, ksz_mib_पढ़ो_work);

	क्रम (i = 0; i < dev->port_cnt; i++)
		dev->dev_ops->port_init_cnt(dev, i);
पूर्ण
EXPORT_SYMBOL_GPL(ksz_init_mib_समयr);

पूर्णांक ksz_phy_पढ़ो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	u16 val = 0xffff;

	dev->dev_ops->r_phy(dev, addr, reg, &val);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_phy_पढ़ो16);

पूर्णांक ksz_phy_ग_लिखो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	dev->dev_ops->w_phy(dev, addr, reg, val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_phy_ग_लिखो16);

व्योम ksz_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
		       phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	काष्ठा ksz_port *p = &dev->ports[port];

	/* Read all MIB counters when the link is going करोwn. */
	p->पढ़ो = true;
	/* समयr started */
	अगर (dev->mib_पढ़ो_पूर्णांकerval)
		schedule_delayed_work(&dev->mib_पढ़ो, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ksz_mac_link_करोwn);

पूर्णांक ksz_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	अगर (sset != ETH_SS_STATS)
		वापस 0;

	वापस dev->mib_cnt;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_sset_count);

व्योम ksz_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *buf)
अणु
	स्थिर काष्ठा dsa_port *dp = dsa_to_port(ds, port);
	काष्ठा ksz_device *dev = ds->priv;
	काष्ठा ksz_port_mib *mib;

	mib = &dev->ports[port].mib;
	mutex_lock(&mib->cnt_mutex);

	/* Only पढ़ो dropped counters अगर no link. */
	अगर (!netअगर_carrier_ok(dp->slave))
		mib->cnt_ptr = dev->reg_mib_cnt;
	port_r_cnt(dev, port);
	स_नकल(buf, mib->counters, dev->mib_cnt * माप(u64));
	mutex_unlock(&mib->cnt_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ksz_get_ethtool_stats);

पूर्णांक ksz_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 काष्ठा net_device *br)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	mutex_lock(&dev->dev_mutex);
	dev->br_member |= (1 << port);
	mutex_unlock(&dev->dev_mutex);

	/* port_stp_state_set() will be called after to put the port in
	 * appropriate state so there is no need to करो anything.
	 */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_port_bridge_join);

व्योम ksz_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा net_device *br)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	mutex_lock(&dev->dev_mutex);
	dev->br_member &= ~(1 << port);
	dev->member &= ~(1 << port);
	mutex_unlock(&dev->dev_mutex);

	/* port_stp_state_set() will be called after to put the port in
	 * क्रमwarding state so there is no need to करो anything.
	 */
पूर्ण
EXPORT_SYMBOL_GPL(ksz_port_bridge_leave);

व्योम ksz_port_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	dev->dev_ops->flush_dyn_mac_table(dev, port);
पूर्ण
EXPORT_SYMBOL_GPL(ksz_port_fast_age);

पूर्णांक ksz_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port, dsa_fdb_dump_cb_t *cb,
		      व्योम *data)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	पूर्णांक ret = 0;
	u16 i = 0;
	u16 entries = 0;
	u8 बारtamp = 0;
	u8 fid;
	u8 member;
	काष्ठा alu_काष्ठा alu;

	करो अणु
		alu.is_अटल = false;
		ret = dev->dev_ops->r_dyn_mac_table(dev, i, alu.mac, &fid,
						    &member, &बारtamp,
						    &entries);
		अगर (!ret && (member & BIT(port))) अणु
			ret = cb(alu.mac, alu.fid, alu.is_अटल, data);
			अगर (ret)
				अवरोध;
		पूर्ण
		i++;
	पूर्ण जबतक (i < entries);
	अगर (i >= entries)
		ret = 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_port_fdb_dump);

पूर्णांक ksz_port_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	काष्ठा alu_काष्ठा alu;
	पूर्णांक index;
	पूर्णांक empty = 0;

	alu.port_क्रमward = 0;
	क्रम (index = 0; index < dev->num_अटलs; index++) अणु
		अगर (!dev->dev_ops->r_sta_mac_table(dev, index, &alu)) अणु
			/* Found one alपढ़ोy in अटल MAC table. */
			अगर (!स_भेद(alu.mac, mdb->addr, ETH_ALEN) &&
			    alu.fid == mdb->vid)
				अवरोध;
		/* Remember the first empty entry. */
		पूर्ण अन्यथा अगर (!empty) अणु
			empty = index + 1;
		पूर्ण
	पूर्ण

	/* no available entry */
	अगर (index == dev->num_अटलs && !empty)
		वापस -ENOSPC;

	/* add entry */
	अगर (index == dev->num_अटलs) अणु
		index = empty - 1;
		स_रखो(&alu, 0, माप(alu));
		स_नकल(alu.mac, mdb->addr, ETH_ALEN);
		alu.is_अटल = true;
	पूर्ण
	alu.port_क्रमward |= BIT(port);
	अगर (mdb->vid) अणु
		alu.is_use_fid = true;

		/* Need a way to map VID to FID. */
		alu.fid = mdb->vid;
	पूर्ण
	dev->dev_ops->w_sta_mac_table(dev, index, &alu);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_port_mdb_add);

पूर्णांक ksz_port_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ksz_device *dev = ds->priv;
	काष्ठा alu_काष्ठा alu;
	पूर्णांक index;
	पूर्णांक ret = 0;

	क्रम (index = 0; index < dev->num_अटलs; index++) अणु
		अगर (!dev->dev_ops->r_sta_mac_table(dev, index, &alu)) अणु
			/* Found one alपढ़ोy in अटल MAC table. */
			अगर (!स_भेद(alu.mac, mdb->addr, ETH_ALEN) &&
			    alu.fid == mdb->vid)
				अवरोध;
		पूर्ण
	पूर्ण

	/* no available entry */
	अगर (index == dev->num_अटलs)
		जाओ निकास;

	/* clear port */
	alu.port_क्रमward &= ~BIT(port);
	अगर (!alu.port_क्रमward)
		alu.is_अटल = false;
	dev->dev_ops->w_sta_mac_table(dev, index, &alu);

निकास:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_port_mdb_del);

पूर्णांक ksz_enable_port(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा phy_device *phy)
अणु
	काष्ठा ksz_device *dev = ds->priv;

	अगर (!dsa_is_user_port(ds, port))
		वापस 0;

	/* setup slave port */
	dev->dev_ops->port_setup(dev, port, false);

	/* port_stp_state_set() will be called after to enable the port so
	 * there is no need to करो anything.
	 */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ksz_enable_port);

काष्ठा ksz_device *ksz_चयन_alloc(काष्ठा device *base, व्योम *priv)
अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा ksz_device *swdev;

	ds = devm_kzalloc(base, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस शून्य;

	ds->dev = base;
	ds->num_ports = DSA_MAX_PORTS;

	swdev = devm_kzalloc(base, माप(*swdev), GFP_KERNEL);
	अगर (!swdev)
		वापस शून्य;

	ds->priv = swdev;
	swdev->dev = base;

	swdev->ds = ds;
	swdev->priv = priv;

	वापस swdev;
पूर्ण
EXPORT_SYMBOL(ksz_चयन_alloc);

पूर्णांक ksz_चयन_रेजिस्टर(काष्ठा ksz_device *dev,
			स्थिर काष्ठा ksz_dev_ops *ops)
अणु
	काष्ठा device_node *port, *ports;
	phy_पूर्णांकerface_t पूर्णांकerface;
	अचिन्हित पूर्णांक port_num;
	पूर्णांक ret;

	अगर (dev->pdata)
		dev->chip_id = dev->pdata->chip_id;

	dev->reset_gpio = devm_gpiod_get_optional(dev->dev, "reset",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(dev->reset_gpio))
		वापस PTR_ERR(dev->reset_gpio);

	अगर (dev->reset_gpio) अणु
		gpiod_set_value_cansleep(dev->reset_gpio, 1);
		usleep_range(10000, 12000);
		gpiod_set_value_cansleep(dev->reset_gpio, 0);
		msleep(100);
	पूर्ण

	mutex_init(&dev->dev_mutex);
	mutex_init(&dev->regmap_mutex);
	mutex_init(&dev->alu_mutex);
	mutex_init(&dev->vlan_mutex);

	dev->dev_ops = ops;

	अगर (dev->dev_ops->detect(dev))
		वापस -EINVAL;

	ret = dev->dev_ops->init(dev);
	अगर (ret)
		वापस ret;

	/* Host port पूर्णांकerface will be self detected, or specअगरically set in
	 * device tree.
	 */
	क्रम (port_num = 0; port_num < dev->port_cnt; ++port_num)
		dev->ports[port_num].पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	अगर (dev->dev->of_node) अणु
		ret = of_get_phy_mode(dev->dev->of_node, &पूर्णांकerface);
		अगर (ret == 0)
			dev->compat_पूर्णांकerface = पूर्णांकerface;
		ports = of_get_child_by_name(dev->dev->of_node, "ethernet-ports");
		अगर (!ports)
			ports = of_get_child_by_name(dev->dev->of_node, "ports");
		अगर (ports)
			क्रम_each_available_child_of_node(ports, port) अणु
				अगर (of_property_पढ़ो_u32(port, "reg",
							 &port_num))
					जारी;
				अगर (!(dev->port_mask & BIT(port_num)))
					वापस -EINVAL;
				of_get_phy_mode(port,
						&dev->ports[port_num].पूर्णांकerface);
			पूर्ण
		dev->synclko_125 = of_property_पढ़ो_bool(dev->dev->of_node,
							 "microchip,synclko-125");
	पूर्ण

	ret = dsa_रेजिस्टर_चयन(dev->ds);
	अगर (ret) अणु
		dev->dev_ops->निकास(dev);
		वापस ret;
	पूर्ण

	/* Read MIB counters every 30 seconds to aव्योम overflow. */
	dev->mib_पढ़ो_पूर्णांकerval = msecs_to_jअगरfies(30000);

	/* Start the MIB समयr. */
	schedule_delayed_work(&dev->mib_पढ़ो, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ksz_चयन_रेजिस्टर);

व्योम ksz_चयन_हटाओ(काष्ठा ksz_device *dev)
अणु
	/* समयr started */
	अगर (dev->mib_पढ़ो_पूर्णांकerval)
		cancel_delayed_work_sync(&dev->mib_पढ़ो);

	dev->dev_ops->निकास(dev);
	dsa_unरेजिस्टर_चयन(dev->ds);

	अगर (dev->reset_gpio)
		gpiod_set_value_cansleep(dev->reset_gpio, 1);

पूर्ण
EXPORT_SYMBOL(ksz_चयन_हटाओ);

MODULE_AUTHOR("Woojung Huh <Woojung.Huh@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ Series Switch DSA Driver");
MODULE_LICENSE("GPL");
