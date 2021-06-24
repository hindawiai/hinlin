<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Framework क्रम finding and configuring PHYs.
 * Also contains generic PHY driver
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_led_triggers.h>
#समावेश <linux/property.h>
#समावेश <linux/sfp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/unistd.h>

MODULE_DESCRIPTION("PHY library");
MODULE_AUTHOR("Andy Fleming");
MODULE_LICENSE("GPL");

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_basic_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_basic_features);

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_basic_t1_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_basic_t1_features);

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_gbit_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_gbit_features);

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_gbit_fibre_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_gbit_fibre_features);

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_gbit_all_ports_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_gbit_all_ports_features);

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_10gbit_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_10gbit_features);

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_10gbit_fec_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_10gbit_fec_features);

स्थिर पूर्णांक phy_basic_ports_array[3] = अणु
	ETHTOOL_LINK_MODE_Autoneg_BIT,
	ETHTOOL_LINK_MODE_TP_BIT,
	ETHTOOL_LINK_MODE_MII_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_basic_ports_array);

स्थिर पूर्णांक phy_fibre_port_array[1] = अणु
	ETHTOOL_LINK_MODE_FIBRE_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_fibre_port_array);

स्थिर पूर्णांक phy_all_ports_features_array[7] = अणु
	ETHTOOL_LINK_MODE_Autoneg_BIT,
	ETHTOOL_LINK_MODE_TP_BIT,
	ETHTOOL_LINK_MODE_MII_BIT,
	ETHTOOL_LINK_MODE_FIBRE_BIT,
	ETHTOOL_LINK_MODE_AUI_BIT,
	ETHTOOL_LINK_MODE_BNC_BIT,
	ETHTOOL_LINK_MODE_Backplane_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_all_ports_features_array);

स्थिर पूर्णांक phy_10_100_features_array[4] = अणु
	ETHTOOL_LINK_MODE_10baseT_Half_BIT,
	ETHTOOL_LINK_MODE_10baseT_Full_BIT,
	ETHTOOL_LINK_MODE_100baseT_Half_BIT,
	ETHTOOL_LINK_MODE_100baseT_Full_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_10_100_features_array);

स्थिर पूर्णांक phy_basic_t1_features_array[2] = अणु
	ETHTOOL_LINK_MODE_TP_BIT,
	ETHTOOL_LINK_MODE_100baseT1_Full_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_basic_t1_features_array);

स्थिर पूर्णांक phy_gbit_features_array[2] = अणु
	ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_gbit_features_array);

स्थिर पूर्णांक phy_10gbit_features_array[1] = अणु
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
पूर्ण;
EXPORT_SYMBOL_GPL(phy_10gbit_features_array);

अटल स्थिर पूर्णांक phy_10gbit_fec_features_array[1] = अणु
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
पूर्ण;

__ETHTOOL_DECLARE_LINK_MODE_MASK(phy_10gbit_full_features) __ro_after_init;
EXPORT_SYMBOL_GPL(phy_10gbit_full_features);

अटल स्थिर पूर्णांक phy_10gbit_full_features_array[] = अणु
	ETHTOOL_LINK_MODE_10baseT_Full_BIT,
	ETHTOOL_LINK_MODE_100baseT_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
पूर्ण;

अटल व्योम features_init(व्योम)
अणु
	/* 10/100 half/full*/
	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phy_basic_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_basic_features);

	/* 100 full, TP */
	linkmode_set_bit_array(phy_basic_t1_features_array,
			       ARRAY_SIZE(phy_basic_t1_features_array),
			       phy_basic_t1_features);

	/* 10/100 half/full + 1000 half/full */
	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phy_gbit_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_gbit_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_gbit_features);

	/* 10/100 half/full + 1000 half/full + fibre*/
	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phy_gbit_fibre_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_gbit_fibre_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_gbit_fibre_features);
	linkmode_set_bit_array(phy_fibre_port_array,
			       ARRAY_SIZE(phy_fibre_port_array),
			       phy_gbit_fibre_features);

	/* 10/100 half/full + 1000 half/full + TP/MII/FIBRE/AUI/BNC/Backplane*/
	linkmode_set_bit_array(phy_all_ports_features_array,
			       ARRAY_SIZE(phy_all_ports_features_array),
			       phy_gbit_all_ports_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_gbit_all_ports_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_gbit_all_ports_features);

	/* 10/100 half/full + 1000 half/full + 10G full*/
	linkmode_set_bit_array(phy_all_ports_features_array,
			       ARRAY_SIZE(phy_all_ports_features_array),
			       phy_10gbit_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_10gbit_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_10gbit_features);
	linkmode_set_bit_array(phy_10gbit_features_array,
			       ARRAY_SIZE(phy_10gbit_features_array),
			       phy_10gbit_features);

	/* 10/100/1000/10G full */
	linkmode_set_bit_array(phy_all_ports_features_array,
			       ARRAY_SIZE(phy_all_ports_features_array),
			       phy_10gbit_full_features);
	linkmode_set_bit_array(phy_10gbit_full_features_array,
			       ARRAY_SIZE(phy_10gbit_full_features_array),
			       phy_10gbit_full_features);
	/* 10G FEC only */
	linkmode_set_bit_array(phy_10gbit_fec_features_array,
			       ARRAY_SIZE(phy_10gbit_fec_features_array),
			       phy_10gbit_fec_features);
पूर्ण

व्योम phy_device_मुक्त(काष्ठा phy_device *phydev)
अणु
	put_device(&phydev->mdio.dev);
पूर्ण
EXPORT_SYMBOL(phy_device_मुक्त);

अटल व्योम phy_mdio_device_मुक्त(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा phy_device *phydev;

	phydev = container_of(mdiodev, काष्ठा phy_device, mdio);
	phy_device_मुक्त(phydev);
पूर्ण

अटल व्योम phy_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_phy_device(dev));
पूर्ण

अटल व्योम phy_mdio_device_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा phy_device *phydev;

	phydev = container_of(mdiodev, काष्ठा phy_device, mdio);
	phy_device_हटाओ(phydev);
पूर्ण

अटल काष्ठा phy_driver genphy_driver;

अटल LIST_HEAD(phy_fixup_list);
अटल DEFINE_MUTEX(phy_fixup_lock);

अटल bool mdio_bus_phy_may_suspend(काष्ठा phy_device *phydev)
अणु
	काष्ठा device_driver *drv = phydev->mdio.dev.driver;
	काष्ठा phy_driver *phydrv = to_phy_driver(drv);
	काष्ठा net_device *netdev = phydev->attached_dev;

	अगर (!drv || !phydrv->suspend)
		वापस false;

	/* PHY not attached? May suspend अगर the PHY has not alपढ़ोy been
	 * suspended as part of a prior call to phy_disconnect() ->
	 * phy_detach() -> phy_suspend() because the parent netdev might be the
	 * MDIO bus driver and घड़ी gated at this poपूर्णांक.
	 */
	अगर (!netdev)
		जाओ out;

	अगर (netdev->wol_enabled)
		वापस false;

	/* As दीर्घ as not all affected network drivers support the
	 * wol_enabled flag, let's check क्रम hपूर्णांकs that WoL is enabled.
	 * Don't suspend PHY अगर the attached netdev parent may wake up.
	 * The parent may poपूर्णांक to a PCI device, as in tg3 driver.
	 */
	अगर (netdev->dev.parent && device_may_wakeup(netdev->dev.parent))
		वापस false;

	/* Also करोn't suspend PHY अगर the netdev itself may wakeup. This
	 * is the हाल क्रम devices w/o underlaying pwr. mgmt. aware bus,
	 * e.g. SoC devices.
	 */
	अगर (device_may_wakeup(&netdev->dev))
		वापस false;

out:
	वापस !phydev->suspended;
पूर्ण

अटल __maybe_unused पूर्णांक mdio_bus_phy_suspend(काष्ठा device *dev)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	अगर (phydev->mac_managed_pm)
		वापस 0;

	/* We must stop the state machine manually, otherwise it stops out of
	 * control, possibly with the phydev->lock held. Upon resume, netdev
	 * may call phy routines that try to grab the same lock, and that may
	 * lead to a deadlock.
	 */
	अगर (phydev->attached_dev && phydev->adjust_link)
		phy_stop_machine(phydev);

	अगर (!mdio_bus_phy_may_suspend(phydev))
		वापस 0;

	phydev->suspended_by_mdio_bus = 1;

	वापस phy_suspend(phydev);
पूर्ण

अटल __maybe_unused पूर्णांक mdio_bus_phy_resume(काष्ठा device *dev)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);
	पूर्णांक ret;

	अगर (phydev->mac_managed_pm)
		वापस 0;

	अगर (!phydev->suspended_by_mdio_bus)
		जाओ no_resume;

	phydev->suspended_by_mdio_bus = 0;

	ret = phy_init_hw(phydev);
	अगर (ret < 0)
		वापस ret;

	ret = phy_resume(phydev);
	अगर (ret < 0)
		वापस ret;
no_resume:
	अगर (phydev->attached_dev && phydev->adjust_link)
		phy_start_machine(phydev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mdio_bus_phy_pm_ops, mdio_bus_phy_suspend,
			 mdio_bus_phy_resume);

/**
 * phy_रेजिस्टर_fixup - creates a new phy_fixup and adds it to the list
 * @bus_id: A string which matches phydev->mdio.dev.bus_id (or PHY_ANY_ID)
 * @phy_uid: Used to match against phydev->phy_id (the UID of the PHY)
 *	It can also be PHY_ANY_UID
 * @phy_uid_mask: Applied to phydev->phy_id and fixup->phy_uid beक्रमe
 *	comparison
 * @run: The actual code to be run when a matching PHY is found
 */
पूर्णांक phy_रेजिस्टर_fixup(स्थिर अक्षर *bus_id, u32 phy_uid, u32 phy_uid_mask,
		       पूर्णांक (*run)(काष्ठा phy_device *))
अणु
	काष्ठा phy_fixup *fixup = kzalloc(माप(*fixup), GFP_KERNEL);

	अगर (!fixup)
		वापस -ENOMEM;

	strlcpy(fixup->bus_id, bus_id, माप(fixup->bus_id));
	fixup->phy_uid = phy_uid;
	fixup->phy_uid_mask = phy_uid_mask;
	fixup->run = run;

	mutex_lock(&phy_fixup_lock);
	list_add_tail(&fixup->list, &phy_fixup_list);
	mutex_unlock(&phy_fixup_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_रेजिस्टर_fixup);

/* Registers a fixup to be run on any PHY with the UID in phy_uid */
पूर्णांक phy_रेजिस्टर_fixup_क्रम_uid(u32 phy_uid, u32 phy_uid_mask,
			       पूर्णांक (*run)(काष्ठा phy_device *))
अणु
	वापस phy_रेजिस्टर_fixup(PHY_ANY_ID, phy_uid, phy_uid_mask, run);
पूर्ण
EXPORT_SYMBOL(phy_रेजिस्टर_fixup_क्रम_uid);

/* Registers a fixup to be run on the PHY with id string bus_id */
पूर्णांक phy_रेजिस्टर_fixup_क्रम_id(स्थिर अक्षर *bus_id,
			      पूर्णांक (*run)(काष्ठा phy_device *))
अणु
	वापस phy_रेजिस्टर_fixup(bus_id, PHY_ANY_UID, 0xffffffff, run);
पूर्ण
EXPORT_SYMBOL(phy_रेजिस्टर_fixup_क्रम_id);

/**
 * phy_unरेजिस्टर_fixup - हटाओ a phy_fixup from the list
 * @bus_id: A string matches fixup->bus_id (or PHY_ANY_ID) in phy_fixup_list
 * @phy_uid: A phy id matches fixup->phy_id (or PHY_ANY_UID) in phy_fixup_list
 * @phy_uid_mask: Applied to phy_uid and fixup->phy_uid beक्रमe comparison
 */
पूर्णांक phy_unरेजिस्टर_fixup(स्थिर अक्षर *bus_id, u32 phy_uid, u32 phy_uid_mask)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा phy_fixup *fixup;
	पूर्णांक ret;

	ret = -ENODEV;

	mutex_lock(&phy_fixup_lock);
	list_क्रम_each_safe(pos, n, &phy_fixup_list) अणु
		fixup = list_entry(pos, काष्ठा phy_fixup, list);

		अगर ((!म_भेद(fixup->bus_id, bus_id)) &&
		    ((fixup->phy_uid & phy_uid_mask) ==
		     (phy_uid & phy_uid_mask))) अणु
			list_del(&fixup->list);
			kमुक्त(fixup);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&phy_fixup_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_unरेजिस्टर_fixup);

/* Unरेजिस्टरs a fixup of any PHY with the UID in phy_uid */
पूर्णांक phy_unरेजिस्टर_fixup_क्रम_uid(u32 phy_uid, u32 phy_uid_mask)
अणु
	वापस phy_unरेजिस्टर_fixup(PHY_ANY_ID, phy_uid, phy_uid_mask);
पूर्ण
EXPORT_SYMBOL(phy_unरेजिस्टर_fixup_क्रम_uid);

/* Unरेजिस्टरs a fixup of the PHY with id string bus_id */
पूर्णांक phy_unरेजिस्टर_fixup_क्रम_id(स्थिर अक्षर *bus_id)
अणु
	वापस phy_unरेजिस्टर_fixup(bus_id, PHY_ANY_UID, 0xffffffff);
पूर्ण
EXPORT_SYMBOL(phy_unरेजिस्टर_fixup_क्रम_id);

/* Returns 1 अगर fixup matches phydev in bus_id and phy_uid.
 * Fixups can be set to match any in one or more fields.
 */
अटल पूर्णांक phy_needs_fixup(काष्ठा phy_device *phydev, काष्ठा phy_fixup *fixup)
अणु
	अगर (म_भेद(fixup->bus_id, phydev_name(phydev)) != 0)
		अगर (म_भेद(fixup->bus_id, PHY_ANY_ID) != 0)
			वापस 0;

	अगर ((fixup->phy_uid & fixup->phy_uid_mask) !=
	    (phydev->phy_id & fixup->phy_uid_mask))
		अगर (fixup->phy_uid != PHY_ANY_UID)
			वापस 0;

	वापस 1;
पूर्ण

/* Runs any matching fixups क्रम this phydev */
अटल पूर्णांक phy_scan_fixups(काष्ठा phy_device *phydev)
अणु
	काष्ठा phy_fixup *fixup;

	mutex_lock(&phy_fixup_lock);
	list_क्रम_each_entry(fixup, &phy_fixup_list, list) अणु
		अगर (phy_needs_fixup(phydev, fixup)) अणु
			पूर्णांक err = fixup->run(phydev);

			अगर (err < 0) अणु
				mutex_unlock(&phy_fixup_lock);
				वापस err;
			पूर्ण
			phydev->has_fixups = true;
		पूर्ण
	पूर्ण
	mutex_unlock(&phy_fixup_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);
	काष्ठा phy_driver *phydrv = to_phy_driver(drv);
	स्थिर पूर्णांक num_ids = ARRAY_SIZE(phydev->c45_ids.device_ids);
	पूर्णांक i;

	अगर (!(phydrv->mdiodrv.flags & MDIO_DEVICE_IS_PHY))
		वापस 0;

	अगर (phydrv->match_phy_device)
		वापस phydrv->match_phy_device(phydev);

	अगर (phydev->is_c45) अणु
		क्रम (i = 1; i < num_ids; i++) अणु
			अगर (phydev->c45_ids.device_ids[i] == 0xffffffff)
				जारी;

			अगर ((phydrv->phy_id & phydrv->phy_id_mask) ==
			    (phydev->c45_ids.device_ids[i] &
			     phydrv->phy_id_mask))
				वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस (phydrv->phy_id & phydrv->phy_id_mask) ==
			(phydev->phy_id & phydrv->phy_id_mask);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
phy_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	वापस प्र_लिखो(buf, "0x%.8lx\n", (अचिन्हित दीर्घ)phydev->phy_id);
पूर्ण
अटल DEVICE_ATTR_RO(phy_id);

अटल sमाप_प्रकार
phy_पूर्णांकerface_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);
	स्थिर अक्षर *mode = शून्य;

	अगर (phy_is_पूर्णांकernal(phydev))
		mode = "internal";
	अन्यथा
		mode = phy_modes(phydev->पूर्णांकerface);

	वापस प्र_लिखो(buf, "%s\n", mode);
पूर्ण
अटल DEVICE_ATTR_RO(phy_पूर्णांकerface);

अटल sमाप_प्रकार
phy_has_fixups_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	वापस प्र_लिखो(buf, "%d\n", phydev->has_fixups);
पूर्ण
अटल DEVICE_ATTR_RO(phy_has_fixups);

अटल sमाप_प्रकार phy_dev_flags_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", phydev->dev_flags);
पूर्ण
अटल DEVICE_ATTR_RO(phy_dev_flags);

अटल काष्ठा attribute *phy_dev_attrs[] = अणु
	&dev_attr_phy_id.attr,
	&dev_attr_phy_पूर्णांकerface.attr,
	&dev_attr_phy_has_fixups.attr,
	&dev_attr_phy_dev_flags.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(phy_dev);

अटल स्थिर काष्ठा device_type mdio_bus_phy_type = अणु
	.name = "PHY",
	.groups = phy_dev_groups,
	.release = phy_device_release,
	.pm = pm_ptr(&mdio_bus_phy_pm_ops),
पूर्ण;

अटल पूर्णांक phy_request_driver_module(काष्ठा phy_device *dev, u32 phy_id)
अणु
	पूर्णांक ret;

	ret = request_module(MDIO_MODULE_PREFIX MDIO_ID_FMT,
			     MDIO_ID_ARGS(phy_id));
	/* We only check क्रम failures in executing the usermode binary,
	 * not whether a PHY driver module exists क्रम the PHY ID.
	 * Accept -ENOENT because this may occur in हाल no initramfs exists,
	 * then modprobe isn't available.
	 */
	अगर (IS_ENABLED(CONFIG_MODULES) && ret < 0 && ret != -ENOENT) अणु
		phydev_err(dev, "error %d loading PHY driver module for ID 0x%08lx\n",
			   ret, (अचिन्हित दीर्घ)phy_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा phy_device *phy_device_create(काष्ठा mii_bus *bus, पूर्णांक addr, u32 phy_id,
				     bool is_c45,
				     काष्ठा phy_c45_device_ids *c45_ids)
अणु
	काष्ठा phy_device *dev;
	काष्ठा mdio_device *mdiodev;
	पूर्णांक ret = 0;

	/* We allocate the device, and initialize the शेष values */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	mdiodev = &dev->mdio;
	mdiodev->dev.parent = &bus->dev;
	mdiodev->dev.bus = &mdio_bus_type;
	mdiodev->dev.type = &mdio_bus_phy_type;
	mdiodev->bus = bus;
	mdiodev->bus_match = phy_bus_match;
	mdiodev->addr = addr;
	mdiodev->flags = MDIO_DEVICE_FLAG_PHY;
	mdiodev->device_मुक्त = phy_mdio_device_मुक्त;
	mdiodev->device_हटाओ = phy_mdio_device_हटाओ;

	dev->speed = SPEED_UNKNOWN;
	dev->duplex = DUPLEX_UNKNOWN;
	dev->छोड़ो = 0;
	dev->asym_छोड़ो = 0;
	dev->link = 0;
	dev->port = PORT_TP;
	dev->पूर्णांकerface = PHY_INTERFACE_MODE_GMII;

	dev->स्वतःneg = AUTONEG_ENABLE;

	dev->is_c45 = is_c45;
	dev->phy_id = phy_id;
	अगर (c45_ids)
		dev->c45_ids = *c45_ids;
	dev->irq = bus->irq[addr];

	dev_set_name(&mdiodev->dev, PHY_ID_FMT, bus->id, addr);
	device_initialize(&mdiodev->dev);

	dev->state = PHY_DOWN;

	mutex_init(&dev->lock);
	INIT_DELAYED_WORK(&dev->state_queue, phy_state_machine);

	/* Request the appropriate module unconditionally; करोn't
	 * bother trying to करो so only अगर it isn't alपढ़ोy loaded,
	 * because that माला_लो complicated. A hotplug event would have
	 * करोne an unconditional modprobe anyway.
	 * We करोn't do normal hotplug because it won't work क्रम MDIO
	 * -- because it relies on the device staying around क्रम दीर्घ
	 * enough क्रम the driver to get loaded. With MDIO, the NIC
	 * driver will get bored and give up as soon as it finds that
	 * there's no driver _alपढ़ोy_ loaded.
	 */
	अगर (is_c45 && c45_ids) अणु
		स्थिर पूर्णांक num_ids = ARRAY_SIZE(c45_ids->device_ids);
		पूर्णांक i;

		क्रम (i = 1; i < num_ids; i++) अणु
			अगर (c45_ids->device_ids[i] == 0xffffffff)
				जारी;

			ret = phy_request_driver_module(dev,
						c45_ids->device_ids[i]);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = phy_request_driver_module(dev, phy_id);
	पूर्ण

	अगर (ret) अणु
		put_device(&mdiodev->dev);
		dev = ERR_PTR(ret);
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL(phy_device_create);

/* phy_c45_probe_present - checks to see अगर a MMD is present in the package
 * @bus: the target MII bus
 * @prtad: PHY package address on the MII bus
 * @devad: PHY device (MMD) address
 *
 * Read the MDIO_STAT2 रेजिस्टर, and check whether a device is responding
 * at this address.
 *
 * Returns: negative error number on bus access error, zero अगर no device
 * is responding, or positive अगर a device is present.
 */
अटल पूर्णांक phy_c45_probe_present(काष्ठा mii_bus *bus, पूर्णांक prtad, पूर्णांक devad)
अणु
	पूर्णांक stat2;

	stat2 = mdiobus_c45_पढ़ो(bus, prtad, devad, MDIO_STAT2);
	अगर (stat2 < 0)
		वापस stat2;

	वापस (stat2 & MDIO_STAT2_DEVPRST) == MDIO_STAT2_DEVPRST_VAL;
पूर्ण

/* get_phy_c45_devs_in_pkg - पढ़ोs a MMD's devices in package रेजिस्टरs.
 * @bus: the target MII bus
 * @addr: PHY address on the MII bus
 * @dev_addr: MMD address in the PHY.
 * @devices_in_package: where to store the devices in package inक्रमmation.
 *
 * Description: पढ़ोs devices in package रेजिस्टरs of a MMD at @dev_addr
 * from PHY at @addr on @bus.
 *
 * Returns: 0 on success, -EIO on failure.
 */
अटल पूर्णांक get_phy_c45_devs_in_pkg(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक dev_addr,
				   u32 *devices_in_package)
अणु
	पूर्णांक phy_reg;

	phy_reg = mdiobus_c45_पढ़ो(bus, addr, dev_addr, MDIO_DEVS2);
	अगर (phy_reg < 0)
		वापस -EIO;
	*devices_in_package = phy_reg << 16;

	phy_reg = mdiobus_c45_पढ़ो(bus, addr, dev_addr, MDIO_DEVS1);
	अगर (phy_reg < 0)
		वापस -EIO;
	*devices_in_package |= phy_reg;

	वापस 0;
पूर्ण

/**
 * get_phy_c45_ids - पढ़ोs the specअगरied addr क्रम its 802.3-c45 IDs.
 * @bus: the target MII bus
 * @addr: PHY address on the MII bus
 * @c45_ids: where to store the c45 ID inक्रमmation.
 *
 * Read the PHY "devices in package". If this appears to be valid, पढ़ो
 * the PHY identअगरiers क्रम each device. Return the "devices in package"
 * and identअगरiers in @c45_ids.
 *
 * Returns zero on success, %-EIO on bus access error, or %-ENODEV अगर
 * the "devices in package" is invalid.
 */
अटल पूर्णांक get_phy_c45_ids(काष्ठा mii_bus *bus, पूर्णांक addr,
			   काष्ठा phy_c45_device_ids *c45_ids)
अणु
	स्थिर पूर्णांक num_ids = ARRAY_SIZE(c45_ids->device_ids);
	u32 devs_in_pkg = 0;
	पूर्णांक i, ret, phy_reg;

	/* Find first non-zero Devices In package. Device zero is reserved
	 * क्रम 802.3 c45 complied PHYs, so करोn't probe it at first.
	 */
	क्रम (i = 1; i < MDIO_MMD_NUM && (devs_in_pkg == 0 ||
	     (devs_in_pkg & 0x1fffffff) == 0x1fffffff); i++) अणु
		अगर (i == MDIO_MMD_VEND1 || i == MDIO_MMD_VEND2) अणु
			/* Check that there is a device present at this
			 * address beक्रमe पढ़ोing the devices-in-package
			 * रेजिस्टर to aव्योम पढ़ोing garbage from the PHY.
			 * Some PHYs (88x3310) venकरोr space is not IEEE802.3
			 * compliant.
			 */
			ret = phy_c45_probe_present(bus, addr, i);
			अगर (ret < 0)
				वापस -EIO;

			अगर (!ret)
				जारी;
		पूर्ण
		phy_reg = get_phy_c45_devs_in_pkg(bus, addr, i, &devs_in_pkg);
		अगर (phy_reg < 0)
			वापस -EIO;
	पूर्ण

	अगर ((devs_in_pkg & 0x1fffffff) == 0x1fffffff) अणु
		/* If mostly Fs, there is no device there, then let's probe
		 * MMD 0, as some 10G PHYs have zero Devices In package,
		 * e.g. Cortina CS4315/CS4340 PHY.
		 */
		phy_reg = get_phy_c45_devs_in_pkg(bus, addr, 0, &devs_in_pkg);
		अगर (phy_reg < 0)
			वापस -EIO;

		/* no device there, let's get out of here */
		अगर ((devs_in_pkg & 0x1fffffff) == 0x1fffffff)
			वापस -ENODEV;
	पूर्ण

	/* Now probe Device Identअगरiers क्रम each device present. */
	क्रम (i = 1; i < num_ids; i++) अणु
		अगर (!(devs_in_pkg & (1 << i)))
			जारी;

		अगर (i == MDIO_MMD_VEND1 || i == MDIO_MMD_VEND2) अणु
			/* Probe the "Device Present" bits क्रम the venकरोr MMDs
			 * to ignore these अगर they करो not contain IEEE 802.3
			 * रेजिस्टरs.
			 */
			ret = phy_c45_probe_present(bus, addr, i);
			अगर (ret < 0)
				वापस ret;

			अगर (!ret)
				जारी;
		पूर्ण

		phy_reg = mdiobus_c45_पढ़ो(bus, addr, i, MII_PHYSID1);
		अगर (phy_reg < 0)
			वापस -EIO;
		c45_ids->device_ids[i] = phy_reg << 16;

		phy_reg = mdiobus_c45_पढ़ो(bus, addr, i, MII_PHYSID2);
		अगर (phy_reg < 0)
			वापस -EIO;
		c45_ids->device_ids[i] |= phy_reg;
	पूर्ण

	c45_ids->devices_in_package = devs_in_pkg;
	/* Bit 0 करोesn't represent a device, it indicates c22 regs presence */
	c45_ids->mmds_present = devs_in_pkg & ~BIT(0);

	वापस 0;
पूर्ण

/**
 * get_phy_c22_id - पढ़ोs the specअगरied addr क्रम its clause 22 ID.
 * @bus: the target MII bus
 * @addr: PHY address on the MII bus
 * @phy_id: where to store the ID retrieved.
 *
 * Read the 802.3 clause 22 PHY ID from the PHY at @addr on the @bus,
 * placing it in @phy_id. Return zero on successful पढ़ो and the ID is
 * valid, %-EIO on bus access error, or %-ENODEV अगर no device responds
 * or invalid ID.
 */
अटल पूर्णांक get_phy_c22_id(काष्ठा mii_bus *bus, पूर्णांक addr, u32 *phy_id)
अणु
	पूर्णांक phy_reg;

	/* Grab the bits from PHYIR1, and put them in the upper half */
	phy_reg = mdiobus_पढ़ो(bus, addr, MII_PHYSID1);
	अगर (phy_reg < 0) अणु
		/* वापसing -ENODEV करोesn't stop bus scanning */
		वापस (phy_reg == -EIO || phy_reg == -ENODEV) ? -ENODEV : -EIO;
	पूर्ण

	*phy_id = phy_reg << 16;

	/* Grab the bits from PHYIR2, and put them in the lower half */
	phy_reg = mdiobus_पढ़ो(bus, addr, MII_PHYSID2);
	अगर (phy_reg < 0) अणु
		/* वापसing -ENODEV करोesn't stop bus scanning */
		वापस (phy_reg == -EIO || phy_reg == -ENODEV) ? -ENODEV : -EIO;
	पूर्ण

	*phy_id |= phy_reg;

	/* If the phy_id is mostly Fs, there is no device there */
	अगर ((*phy_id & 0x1fffffff) == 0x1fffffff)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/**
 * get_phy_device - पढ़ोs the specअगरied PHY device and वापसs its @phy_device
 *		    काष्ठा
 * @bus: the target MII bus
 * @addr: PHY address on the MII bus
 * @is_c45: If true the PHY uses the 802.3 clause 45 protocol
 *
 * Probe क्रम a PHY at @addr on @bus.
 *
 * When probing क्रम a clause 22 PHY, then पढ़ो the ID रेजिस्टरs. If we find
 * a valid ID, allocate and वापस a &काष्ठा phy_device.
 *
 * When probing क्रम a clause 45 PHY, पढ़ो the "devices in package" रेजिस्टरs.
 * If the "devices in package" appears valid, पढ़ो the ID रेजिस्टरs क्रम each
 * MMD, allocate and वापस a &काष्ठा phy_device.
 *
 * Returns an allocated &काष्ठा phy_device on success, %-ENODEV अगर there is
 * no PHY present, or %-EIO on bus access error.
 */
काष्ठा phy_device *get_phy_device(काष्ठा mii_bus *bus, पूर्णांक addr, bool is_c45)
अणु
	काष्ठा phy_c45_device_ids c45_ids;
	u32 phy_id = 0;
	पूर्णांक r;

	c45_ids.devices_in_package = 0;
	c45_ids.mmds_present = 0;
	स_रखो(c45_ids.device_ids, 0xff, माप(c45_ids.device_ids));

	अगर (is_c45)
		r = get_phy_c45_ids(bus, addr, &c45_ids);
	अन्यथा
		r = get_phy_c22_id(bus, addr, &phy_id);

	अगर (r)
		वापस ERR_PTR(r);

	वापस phy_device_create(bus, addr, phy_id, is_c45, &c45_ids);
पूर्ण
EXPORT_SYMBOL(get_phy_device);

/**
 * phy_device_रेजिस्टर - Register the phy device on the MDIO bus
 * @phydev: phy_device काष्ठाure to be added to the MDIO bus
 */
पूर्णांक phy_device_रेजिस्टर(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = mdiobus_रेजिस्टर_device(&phydev->mdio);
	अगर (err)
		वापस err;

	/* Deनिश्चित the reset संकेत */
	phy_device_reset(phydev, 0);

	/* Run all of the fixups क्रम this PHY */
	err = phy_scan_fixups(phydev);
	अगर (err) अणु
		phydev_err(phydev, "failed to initialize\n");
		जाओ out;
	पूर्ण

	err = device_add(&phydev->mdio.dev);
	अगर (err) अणु
		phydev_err(phydev, "failed to add\n");
		जाओ out;
	पूर्ण

	वापस 0;

 out:
	/* Assert the reset संकेत */
	phy_device_reset(phydev, 1);

	mdiobus_unरेजिस्टर_device(&phydev->mdio);
	वापस err;
पूर्ण
EXPORT_SYMBOL(phy_device_रेजिस्टर);

/**
 * phy_device_हटाओ - Remove a previously रेजिस्टरed phy device from the MDIO bus
 * @phydev: phy_device काष्ठाure to हटाओ
 *
 * This करोesn't मुक्त the phy_device itself, it merely reverses the effects
 * of phy_device_रेजिस्टर(). Use phy_device_मुक्त() to मुक्त the device
 * after calling this function.
 */
व्योम phy_device_हटाओ(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->mii_ts)
		unरेजिस्टर_mii_बारtamper(phydev->mii_ts);

	device_del(&phydev->mdio.dev);

	/* Assert the reset संकेत */
	phy_device_reset(phydev, 1);

	mdiobus_unरेजिस्टर_device(&phydev->mdio);
पूर्ण
EXPORT_SYMBOL(phy_device_हटाओ);

/**
 * phy_find_first - finds the first PHY device on the bus
 * @bus: the target MII bus
 */
काष्ठा phy_device *phy_find_first(काष्ठा mii_bus *bus)
अणु
	काष्ठा phy_device *phydev;
	पूर्णांक addr;

	क्रम (addr = 0; addr < PHY_MAX_ADDR; addr++) अणु
		phydev = mdiobus_get_phy(bus, addr);
		अगर (phydev)
			वापस phydev;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(phy_find_first);

अटल व्योम phy_link_change(काष्ठा phy_device *phydev, bool up)
अणु
	काष्ठा net_device *netdev = phydev->attached_dev;

	अगर (up)
		netअगर_carrier_on(netdev);
	अन्यथा
		netअगर_carrier_off(netdev);
	phydev->adjust_link(netdev);
	अगर (phydev->mii_ts && phydev->mii_ts->link_state)
		phydev->mii_ts->link_state(phydev->mii_ts, phydev);
पूर्ण

/**
 * phy_prepare_link - prepares the PHY layer to monitor link status
 * @phydev: target phy_device काष्ठा
 * @handler: callback function क्रम link status change notअगरications
 *
 * Description: Tells the PHY infraकाष्ठाure to handle the
 *   gory details on monitoring link status (whether through
 *   polling or an पूर्णांकerrupt), and to call back to the
 *   connected device driver when the link status changes.
 *   If you want to monitor your own link state, करोn't call
 *   this function.
 */
अटल व्योम phy_prepare_link(काष्ठा phy_device *phydev,
			     व्योम (*handler)(काष्ठा net_device *))
अणु
	phydev->adjust_link = handler;
पूर्ण

/**
 * phy_connect_direct - connect an ethernet device to a specअगरic phy_device
 * @dev: the network device to connect
 * @phydev: the poपूर्णांकer to the phy device
 * @handler: callback function क्रम state change notअगरications
 * @पूर्णांकerface: PHY device's पूर्णांकerface
 */
पूर्णांक phy_connect_direct(काष्ठा net_device *dev, काष्ठा phy_device *phydev,
		       व्योम (*handler)(काष्ठा net_device *),
		       phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	पूर्णांक rc;

	अगर (!dev)
		वापस -EINVAL;

	rc = phy_attach_direct(dev, phydev, phydev->dev_flags, पूर्णांकerface);
	अगर (rc)
		वापस rc;

	phy_prepare_link(phydev, handler);
	अगर (phy_पूर्णांकerrupt_is_valid(phydev))
		phy_request_पूर्णांकerrupt(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_connect_direct);

/**
 * phy_connect - connect an ethernet device to a PHY device
 * @dev: the network device to connect
 * @bus_id: the id string of the PHY device to connect
 * @handler: callback function क्रम state change notअगरications
 * @पूर्णांकerface: PHY device's पूर्णांकerface
 *
 * Description: Convenience function क्रम connecting ethernet
 *   devices to PHY devices.  The शेष behavior is क्रम
 *   the PHY infraकाष्ठाure to handle everything, and only notअगरy
 *   the connected driver when the link status changes.  If you
 *   करोn't want, or can't use the provided functionality, you may
 *   choose to call only the subset of functions which provide
 *   the desired functionality.
 */
काष्ठा phy_device *phy_connect(काष्ठा net_device *dev, स्थिर अक्षर *bus_id,
			       व्योम (*handler)(काष्ठा net_device *),
			       phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा phy_device *phydev;
	काष्ठा device *d;
	पूर्णांक rc;

	/* Search the list of PHY devices on the mdio bus क्रम the
	 * PHY with the requested name
	 */
	d = bus_find_device_by_name(&mdio_bus_type, शून्य, bus_id);
	अगर (!d) अणु
		pr_err("PHY %s not found\n", bus_id);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	phydev = to_phy_device(d);

	rc = phy_connect_direct(dev, phydev, handler, पूर्णांकerface);
	put_device(d);
	अगर (rc)
		वापस ERR_PTR(rc);

	वापस phydev;
पूर्ण
EXPORT_SYMBOL(phy_connect);

/**
 * phy_disconnect - disable पूर्णांकerrupts, stop state machine, and detach a PHY
 *		    device
 * @phydev: target phy_device काष्ठा
 */
व्योम phy_disconnect(काष्ठा phy_device *phydev)
अणु
	अगर (phy_is_started(phydev))
		phy_stop(phydev);

	अगर (phy_पूर्णांकerrupt_is_valid(phydev))
		phy_मुक्त_पूर्णांकerrupt(phydev);

	phydev->adjust_link = शून्य;

	phy_detach(phydev);
पूर्ण
EXPORT_SYMBOL(phy_disconnect);

/**
 * phy_poll_reset - Safely रुको until a PHY reset has properly completed
 * @phydev: The PHY device to poll
 *
 * Description: According to IEEE 802.3, Section 2, Subsection 22.2.4.1.1, as
 *   published in 2008, a PHY reset may take up to 0.5 seconds.  The MII BMCR
 *   रेजिस्टर must be polled until the BMCR_RESET bit clears.
 *
 *   Furthermore, any attempts to ग_लिखो to PHY रेजिस्टरs may have no effect
 *   or even generate MDIO bus errors until this is complete.
 *
 *   Some PHYs (such as the Marvell 88E1111) करोn't entirely conक्रमm to the
 *   standard and करो not fully reset after the BMCR_RESET bit is set, and may
 *   even *REQUIRE* a soft-reset to properly restart स्वतःnegotiation.  In an
 *   efक्रमt to support such broken PHYs, this function is separate from the
 *   standard phy_init_hw() which will zero all the other bits in the BMCR
 *   and reapply all driver-specअगरic and board-specअगरic fixups.
 */
अटल पूर्णांक phy_poll_reset(काष्ठा phy_device *phydev)
अणु
	/* Poll until the reset bit clears (50ms per retry == 0.6 sec) */
	पूर्णांक ret, val;

	ret = phy_पढ़ो_poll_समयout(phydev, MII_BMCR, val, !(val & BMCR_RESET),
				    50000, 600000, true);
	अगर (ret)
		वापस ret;
	/* Some chips (smsc911x) may still need up to another 1ms after the
	 * BMCR_RESET bit is cleared beक्रमe they are usable.
	 */
	msleep(1);
	वापस 0;
पूर्ण

पूर्णांक phy_init_hw(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = 0;

	/* Deनिश्चित the reset संकेत */
	phy_device_reset(phydev, 0);

	अगर (!phydev->drv)
		वापस 0;

	अगर (phydev->drv->soft_reset) अणु
		ret = phydev->drv->soft_reset(phydev);
		/* see comment in genphy_soft_reset क्रम an explanation */
		अगर (!ret)
			phydev->suspended = 0;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	ret = phy_scan_fixups(phydev);
	अगर (ret < 0)
		वापस ret;

	अगर (phydev->drv->config_init) अणु
		ret = phydev->drv->config_init(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (phydev->drv->config_पूर्णांकr) अणु
		ret = phydev->drv->config_पूर्णांकr(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_init_hw);

व्योम phy_attached_info(काष्ठा phy_device *phydev)
अणु
	phy_attached_prपूर्णांक(phydev, शून्य);
पूर्ण
EXPORT_SYMBOL(phy_attached_info);

#घोषणा ATTACHED_FMT "attached PHY driver %s(mii_bus:phy_addr=%s, irq=%s)"
अक्षर *phy_attached_info_irq(काष्ठा phy_device *phydev)
अणु
	अक्षर *irq_str;
	अक्षर irq_num[8];

	चयन(phydev->irq) अणु
	हाल PHY_POLL:
		irq_str = "POLL";
		अवरोध;
	हाल PHY_MAC_INTERRUPT:
		irq_str = "MAC";
		अवरोध;
	शेष:
		snम_लिखो(irq_num, माप(irq_num), "%d", phydev->irq);
		irq_str = irq_num;
		अवरोध;
	पूर्ण

	वापस kaप्र_लिखो(GFP_KERNEL, "%s", irq_str);
पूर्ण
EXPORT_SYMBOL(phy_attached_info_irq);

व्योम phy_attached_prपूर्णांक(काष्ठा phy_device *phydev, स्थिर अक्षर *fmt, ...)
अणु
	स्थिर अक्षर *unbound = phydev->drv ? "" : "[unbound] ";
	अक्षर *irq_str = phy_attached_info_irq(phydev);

	अगर (!fmt) अणु
		phydev_info(phydev, ATTACHED_FMT "\n", unbound,
			    phydev_name(phydev), irq_str);
	पूर्ण अन्यथा अणु
		बहु_सूची ap;

		phydev_info(phydev, ATTACHED_FMT, unbound,
			    phydev_name(phydev), irq_str);

		बहु_शुरू(ap, fmt);
		vprपूर्णांकk(fmt, ap);
		बहु_पूर्ण(ap);
	पूर्ण
	kमुक्त(irq_str);
पूर्ण
EXPORT_SYMBOL(phy_attached_prपूर्णांक);

अटल व्योम phy_sysfs_create_links(काष्ठा phy_device *phydev)
अणु
	काष्ठा net_device *dev = phydev->attached_dev;
	पूर्णांक err;

	अगर (!dev)
		वापस;

	err = sysfs_create_link(&phydev->mdio.dev.kobj, &dev->dev.kobj,
				"attached_dev");
	अगर (err)
		वापस;

	err = sysfs_create_link_nowarn(&dev->dev.kobj,
				       &phydev->mdio.dev.kobj,
				       "phydev");
	अगर (err) अणु
		dev_err(&dev->dev, "could not add device link to %s err %d\n",
			kobject_name(&phydev->mdio.dev.kobj),
			err);
		/* non-fatal - some net drivers can use one netdevice
		 * with more then one phy
		 */
	पूर्ण

	phydev->sysfs_links = true;
पूर्ण

अटल sमाप_प्रकार
phy_standalone_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	वापस प्र_लिखो(buf, "%d\n", !phydev->attached_dev);
पूर्ण
अटल DEVICE_ATTR_RO(phy_standalone);

/**
 * phy_sfp_attach - attach the SFP bus to the PHY upstream network device
 * @upstream: poपूर्णांकer to the phy device
 * @bus: sfp bus representing cage being attached
 *
 * This is used to fill in the sfp_upstream_ops .attach member.
 */
व्योम phy_sfp_attach(व्योम *upstream, काष्ठा sfp_bus *bus)
अणु
	काष्ठा phy_device *phydev = upstream;

	अगर (phydev->attached_dev)
		phydev->attached_dev->sfp_bus = bus;
	phydev->sfp_bus_attached = true;
पूर्ण
EXPORT_SYMBOL(phy_sfp_attach);

/**
 * phy_sfp_detach - detach the SFP bus from the PHY upstream network device
 * @upstream: poपूर्णांकer to the phy device
 * @bus: sfp bus representing cage being attached
 *
 * This is used to fill in the sfp_upstream_ops .detach member.
 */
व्योम phy_sfp_detach(व्योम *upstream, काष्ठा sfp_bus *bus)
अणु
	काष्ठा phy_device *phydev = upstream;

	अगर (phydev->attached_dev)
		phydev->attached_dev->sfp_bus = शून्य;
	phydev->sfp_bus_attached = false;
पूर्ण
EXPORT_SYMBOL(phy_sfp_detach);

/**
 * phy_sfp_probe - probe क्रम a SFP cage attached to this PHY device
 * @phydev: Poपूर्णांकer to phy_device
 * @ops: SFP's upstream operations
 */
पूर्णांक phy_sfp_probe(काष्ठा phy_device *phydev,
		  स्थिर काष्ठा sfp_upstream_ops *ops)
अणु
	काष्ठा sfp_bus *bus;
	पूर्णांक ret = 0;

	अगर (phydev->mdio.dev.fwnode) अणु
		bus = sfp_bus_find_fwnode(phydev->mdio.dev.fwnode);
		अगर (IS_ERR(bus))
			वापस PTR_ERR(bus);

		phydev->sfp_bus = bus;

		ret = sfp_bus_add_upstream(bus, phydev, ops);
		sfp_bus_put(bus);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_sfp_probe);

/**
 * phy_attach_direct - attach a network device to a given PHY device poपूर्णांकer
 * @dev: network device to attach
 * @phydev: Poपूर्णांकer to phy_device to attach
 * @flags: PHY device's dev_flags
 * @पूर्णांकerface: PHY device's पूर्णांकerface
 *
 * Description: Called by drivers to attach to a particular PHY
 *     device. The phy_device is found, and properly hooked up
 *     to the phy_driver.  If no driver is attached, then a
 *     generic driver is used.  The phy_device is given a ptr to
 *     the attaching device, and given a callback क्रम link status
 *     change.  The phy_device is वापसed to the attaching driver.
 *     This function takes a reference on the phy device.
 */
पूर्णांक phy_attach_direct(काष्ठा net_device *dev, काष्ठा phy_device *phydev,
		      u32 flags, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mii_bus *bus = phydev->mdio.bus;
	काष्ठा device *d = &phydev->mdio.dev;
	काष्ठा module *ndev_owner = शून्य;
	bool using_genphy = false;
	पूर्णांक err;

	/* For Ethernet device drivers that रेजिस्टर their own MDIO bus, we
	 * will have bus->owner match ndev_mod, so we करो not want to increment
	 * our own module->refcnt here, otherwise we would not be able to
	 * unload later on.
	 */
	अगर (dev)
		ndev_owner = dev->dev.parent->driver->owner;
	अगर (ndev_owner != bus->owner && !try_module_get(bus->owner)) अणु
		phydev_err(phydev, "failed to get the bus module\n");
		वापस -EIO;
	पूर्ण

	get_device(d);

	/* Assume that अगर there is no driver, that it करोesn't
	 * exist, and we should use the genphy driver.
	 */
	अगर (!d->driver) अणु
		अगर (phydev->is_c45)
			d->driver = &genphy_c45_driver.mdiodrv.driver;
		अन्यथा
			d->driver = &genphy_driver.mdiodrv.driver;

		using_genphy = true;
	पूर्ण

	अगर (!try_module_get(d->driver->owner)) अणु
		phydev_err(phydev, "failed to get the device driver module\n");
		err = -EIO;
		जाओ error_put_device;
	पूर्ण

	अगर (using_genphy) अणु
		err = d->driver->probe(d);
		अगर (err >= 0)
			err = device_bind_driver(d);

		अगर (err)
			जाओ error_module_put;
	पूर्ण

	अगर (phydev->attached_dev) अणु
		dev_err(&dev->dev, "PHY already attached\n");
		err = -EBUSY;
		जाओ error;
	पूर्ण

	phydev->phy_link_change = phy_link_change;
	अगर (dev) अणु
		phydev->attached_dev = dev;
		dev->phydev = phydev;

		अगर (phydev->sfp_bus_attached)
			dev->sfp_bus = phydev->sfp_bus;
		अन्यथा अगर (dev->sfp_bus)
			phydev->is_on_sfp_module = true;
	पूर्ण

	/* Some Ethernet drivers try to connect to a PHY device beक्रमe
	 * calling रेजिस्टर_netdevice() -> netdev_रेजिस्टर_kobject() and
	 * करोes the dev->dev.kobj initialization. Here we only check क्रम
	 * success which indicates that the network device kobject is
	 * पढ़ोy. Once we करो that we still need to keep track of whether
	 * links were successfully set up or not क्रम phy_detach() to
	 * हटाओ them accordingly.
	 */
	phydev->sysfs_links = false;

	phy_sysfs_create_links(phydev);

	अगर (!phydev->attached_dev) अणु
		err = sysfs_create_file(&phydev->mdio.dev.kobj,
					&dev_attr_phy_standalone.attr);
		अगर (err)
			phydev_err(phydev, "error creating 'phy_standalone' sysfs entry\n");
	पूर्ण

	phydev->dev_flags |= flags;

	phydev->पूर्णांकerface = पूर्णांकerface;

	phydev->state = PHY_READY;

	/* Port is set to PORT_TP by शेष and the actual PHY driver will set
	 * it to dअगरferent value depending on the PHY configuration. If we have
	 * the generic PHY driver we can't figure it out, thus set the old
	 * legacy PORT_MII value.
	 */
	अगर (using_genphy)
		phydev->port = PORT_MII;

	/* Initial carrier state is off as the phy is about to be
	 * (re)initialized.
	 */
	अगर (dev)
		netअगर_carrier_off(phydev->attached_dev);

	/* Do initial configuration here, now that
	 * we have certain key parameters
	 * (dev_flags and पूर्णांकerface)
	 */
	err = phy_init_hw(phydev);
	अगर (err)
		जाओ error;

	err = phy_disable_पूर्णांकerrupts(phydev);
	अगर (err)
		वापस err;

	phy_resume(phydev);
	phy_led_triggers_रेजिस्टर(phydev);

	वापस err;

error:
	/* phy_detach() करोes all of the cleanup below */
	phy_detach(phydev);
	वापस err;

error_module_put:
	module_put(d->driver->owner);
error_put_device:
	put_device(d);
	अगर (ndev_owner != bus->owner)
		module_put(bus->owner);
	वापस err;
पूर्ण
EXPORT_SYMBOL(phy_attach_direct);

/**
 * phy_attach - attach a network device to a particular PHY device
 * @dev: network device to attach
 * @bus_id: Bus ID of PHY device to attach
 * @पूर्णांकerface: PHY device's पूर्णांकerface
 *
 * Description: Same as phy_attach_direct() except that a PHY bus_id
 *     string is passed instead of a poपूर्णांकer to a काष्ठा phy_device.
 */
काष्ठा phy_device *phy_attach(काष्ठा net_device *dev, स्थिर अक्षर *bus_id,
			      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा bus_type *bus = &mdio_bus_type;
	काष्ठा phy_device *phydev;
	काष्ठा device *d;
	पूर्णांक rc;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	/* Search the list of PHY devices on the mdio bus क्रम the
	 * PHY with the requested name
	 */
	d = bus_find_device_by_name(bus, शून्य, bus_id);
	अगर (!d) अणु
		pr_err("PHY %s not found\n", bus_id);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	phydev = to_phy_device(d);

	rc = phy_attach_direct(dev, phydev, phydev->dev_flags, पूर्णांकerface);
	put_device(d);
	अगर (rc)
		वापस ERR_PTR(rc);

	वापस phydev;
पूर्ण
EXPORT_SYMBOL(phy_attach);

अटल bool phy_driver_is_genphy_kind(काष्ठा phy_device *phydev,
				      काष्ठा device_driver *driver)
अणु
	काष्ठा device *d = &phydev->mdio.dev;
	bool ret = false;

	अगर (!phydev->drv)
		वापस ret;

	get_device(d);
	ret = d->driver == driver;
	put_device(d);

	वापस ret;
पूर्ण

bool phy_driver_is_genphy(काष्ठा phy_device *phydev)
अणु
	वापस phy_driver_is_genphy_kind(phydev,
					 &genphy_driver.mdiodrv.driver);
पूर्ण
EXPORT_SYMBOL_GPL(phy_driver_is_genphy);

bool phy_driver_is_genphy_10g(काष्ठा phy_device *phydev)
अणु
	वापस phy_driver_is_genphy_kind(phydev,
					 &genphy_c45_driver.mdiodrv.driver);
पूर्ण
EXPORT_SYMBOL_GPL(phy_driver_is_genphy_10g);

/**
 * phy_package_join - join a common PHY group
 * @phydev: target phy_device काष्ठा
 * @addr: cookie and PHY address क्रम global रेजिस्टर access
 * @priv_size: अगर non-zero allocate this amount of bytes क्रम निजी data
 *
 * This joins a PHY group and provides a shared storage क्रम all phydevs in
 * this group. This is पूर्णांकended to be used क्रम packages which contain
 * more than one PHY, क्रम example a quad PHY transceiver.
 *
 * The addr parameter serves as a cookie which has to have the same value
 * क्रम all members of one group and as a PHY address to access generic
 * रेजिस्टरs of a PHY package. Usually, one of the PHY addresses of the
 * dअगरferent PHYs in the package provides access to these global रेजिस्टरs.
 * The address which is given here, will be used in the phy_package_पढ़ो()
 * and phy_package_ग_लिखो() convenience functions. If your PHY करोesn't have
 * global रेजिस्टरs you can just pick any of the PHY addresses.
 *
 * This will set the shared poपूर्णांकer of the phydev to the shared storage.
 * If this is the first call क्रम a this cookie the shared storage will be
 * allocated. If priv_size is non-zero, the given amount of bytes are
 * allocated क्रम the priv member.
 *
 * Returns < 1 on error, 0 on success. Esp. calling phy_package_join()
 * with the same cookie but a dअगरferent priv_size is an error.
 */
पूर्णांक phy_package_join(काष्ठा phy_device *phydev, पूर्णांक addr, माप_प्रकार priv_size)
अणु
	काष्ठा mii_bus *bus = phydev->mdio.bus;
	काष्ठा phy_package_shared *shared;
	पूर्णांक ret;

	अगर (addr < 0 || addr >= PHY_MAX_ADDR)
		वापस -EINVAL;

	mutex_lock(&bus->shared_lock);
	shared = bus->shared[addr];
	अगर (!shared) अणु
		ret = -ENOMEM;
		shared = kzalloc(माप(*shared), GFP_KERNEL);
		अगर (!shared)
			जाओ err_unlock;
		अगर (priv_size) अणु
			shared->priv = kzalloc(priv_size, GFP_KERNEL);
			अगर (!shared->priv)
				जाओ err_मुक्त;
			shared->priv_size = priv_size;
		पूर्ण
		shared->addr = addr;
		refcount_set(&shared->refcnt, 1);
		bus->shared[addr] = shared;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		अगर (priv_size && priv_size != shared->priv_size)
			जाओ err_unlock;
		refcount_inc(&shared->refcnt);
	पूर्ण
	mutex_unlock(&bus->shared_lock);

	phydev->shared = shared;

	वापस 0;

err_मुक्त:
	kमुक्त(shared);
err_unlock:
	mutex_unlock(&bus->shared_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_package_join);

/**
 * phy_package_leave - leave a common PHY group
 * @phydev: target phy_device काष्ठा
 *
 * This leaves a PHY group created by phy_package_join(). If this phydev
 * was the last user of the shared data between the group, this data is
 * मुक्तd. Resets the phydev->shared poपूर्णांकer to शून्य.
 */
व्योम phy_package_leave(काष्ठा phy_device *phydev)
अणु
	काष्ठा phy_package_shared *shared = phydev->shared;
	काष्ठा mii_bus *bus = phydev->mdio.bus;

	अगर (!shared)
		वापस;

	अगर (refcount_dec_and_mutex_lock(&shared->refcnt, &bus->shared_lock)) अणु
		bus->shared[shared->addr] = शून्य;
		mutex_unlock(&bus->shared_lock);
		kमुक्त(shared->priv);
		kमुक्त(shared);
	पूर्ण

	phydev->shared = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(phy_package_leave);

अटल व्योम devm_phy_package_leave(काष्ठा device *dev, व्योम *res)
अणु
	phy_package_leave(*(काष्ठा phy_device **)res);
पूर्ण

/**
 * devm_phy_package_join - resource managed phy_package_join()
 * @dev: device that is रेजिस्टरing this PHY package
 * @phydev: target phy_device काष्ठा
 * @addr: cookie and PHY address क्रम global रेजिस्टर access
 * @priv_size: अगर non-zero allocate this amount of bytes क्रम निजी data
 *
 * Managed phy_package_join(). Shared storage fetched by this function,
 * phy_package_leave() is स्वतःmatically called on driver detach. See
 * phy_package_join() क्रम more inक्रमmation.
 */
पूर्णांक devm_phy_package_join(काष्ठा device *dev, काष्ठा phy_device *phydev,
			  पूर्णांक addr, माप_प्रकार priv_size)
अणु
	काष्ठा phy_device **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_phy_package_leave, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = phy_package_join(phydev, addr, priv_size);

	अगर (!ret) अणु
		*ptr = phydev;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_phy_package_join);

/**
 * phy_detach - detach a PHY device from its network device
 * @phydev: target phy_device काष्ठा
 *
 * This detaches the phy device from its network device and the phy
 * driver, and drops the reference count taken in phy_attach_direct().
 */
व्योम phy_detach(काष्ठा phy_device *phydev)
अणु
	काष्ठा net_device *dev = phydev->attached_dev;
	काष्ठा module *ndev_owner = शून्य;
	काष्ठा mii_bus *bus;

	अगर (phydev->sysfs_links) अणु
		अगर (dev)
			sysfs_हटाओ_link(&dev->dev.kobj, "phydev");
		sysfs_हटाओ_link(&phydev->mdio.dev.kobj, "attached_dev");
	पूर्ण

	अगर (!phydev->attached_dev)
		sysfs_हटाओ_file(&phydev->mdio.dev.kobj,
				  &dev_attr_phy_standalone.attr);

	phy_suspend(phydev);
	अगर (dev) अणु
		phydev->attached_dev->phydev = शून्य;
		phydev->attached_dev = शून्य;
	पूर्ण
	phydev->phylink = शून्य;

	phy_led_triggers_unरेजिस्टर(phydev);

	अगर (phydev->mdio.dev.driver)
		module_put(phydev->mdio.dev.driver->owner);

	/* If the device had no specअगरic driver beक्रमe (i.e. - it
	 * was using the generic driver), we unbind the device
	 * from the generic driver so that there's a chance a
	 * real driver could be loaded
	 */
	अगर (phy_driver_is_genphy(phydev) ||
	    phy_driver_is_genphy_10g(phydev))
		device_release_driver(&phydev->mdio.dev);

	/*
	 * The phydev might go away on the put_device() below, so aव्योम
	 * a use-after-मुक्त bug by पढ़ोing the underlying bus first.
	 */
	bus = phydev->mdio.bus;

	put_device(&phydev->mdio.dev);
	अगर (dev)
		ndev_owner = dev->dev.parent->driver->owner;
	अगर (ndev_owner != bus->owner)
		module_put(bus->owner);

	/* Assert the reset संकेत */
	phy_device_reset(phydev, 1);
पूर्ण
EXPORT_SYMBOL(phy_detach);

पूर्णांक phy_suspend(काष्ठा phy_device *phydev)
अणु
	काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;
	काष्ठा net_device *netdev = phydev->attached_dev;
	काष्ठा phy_driver *phydrv = phydev->drv;
	पूर्णांक ret;

	अगर (phydev->suspended)
		वापस 0;

	/* If the device has WOL enabled, we cannot suspend the PHY */
	phy_ethtool_get_wol(phydev, &wol);
	अगर (wol.wolopts || (netdev && netdev->wol_enabled))
		वापस -EBUSY;

	अगर (!phydrv || !phydrv->suspend)
		वापस 0;

	ret = phydrv->suspend(phydev);
	अगर (!ret)
		phydev->suspended = true;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_suspend);

पूर्णांक __phy_resume(काष्ठा phy_device *phydev)
अणु
	काष्ठा phy_driver *phydrv = phydev->drv;
	पूर्णांक ret;

	lockdep_निश्चित_held(&phydev->lock);

	अगर (!phydrv || !phydrv->resume)
		वापस 0;

	ret = phydrv->resume(phydev);
	अगर (!ret)
		phydev->suspended = false;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__phy_resume);

पूर्णांक phy_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	mutex_lock(&phydev->lock);
	ret = __phy_resume(phydev);
	mutex_unlock(&phydev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_resume);

पूर्णांक phy_loopback(काष्ठा phy_device *phydev, bool enable)
अणु
	काष्ठा phy_driver *phydrv = to_phy_driver(phydev->mdio.dev.driver);
	पूर्णांक ret = 0;

	अगर (!phydrv)
		वापस -ENODEV;

	mutex_lock(&phydev->lock);

	अगर (enable && phydev->loopback_enabled) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!enable && !phydev->loopback_enabled) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (phydrv->set_loopback)
		ret = phydrv->set_loopback(phydev, enable);
	अन्यथा
		ret = genphy_loopback(phydev, enable);

	अगर (ret)
		जाओ out;

	phydev->loopback_enabled = enable;

out:
	mutex_unlock(&phydev->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_loopback);

/**
 * phy_reset_after_clk_enable - perक्रमm a PHY reset अगर needed
 * @phydev: target phy_device काष्ठा
 *
 * Description: Some PHYs are known to need a reset after their refclk was
 *   enabled. This function evaluates the flags and perक्रमm the reset अगर it's
 *   needed. Returns < 0 on error, 0 अगर the phy wasn't reset and 1 अगर the phy
 *   was reset.
 */
पूर्णांक phy_reset_after_clk_enable(काष्ठा phy_device *phydev)
अणु
	अगर (!phydev || !phydev->drv)
		वापस -ENODEV;

	अगर (phydev->drv->flags & PHY_RST_AFTER_CLK_EN) अणु
		phy_device_reset(phydev, 1);
		phy_device_reset(phydev, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_reset_after_clk_enable);

/* Generic PHY support and helper functions */

/**
 * genphy_config_advert - sanitize and advertise स्वतः-negotiation parameters
 * @phydev: target phy_device काष्ठा
 *
 * Description: Writes MII_ADVERTISE with the appropriate values,
 *   after sanitizing the values to make sure we only advertise
 *   what is supported.  Returns < 0 on error, 0 अगर the PHY's advertisement
 *   hasn't changed, and > 0 अगर it has changed.
 */
अटल पूर्णांक genphy_config_advert(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, bmsr, changed = 0;
	u32 adv;

	/* Only allow advertising what this PHY supports */
	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	adv = linkmode_adv_to_mii_adv_t(phydev->advertising);

	/* Setup standard advertisement */
	err = phy_modअगरy_changed(phydev, MII_ADVERTISE,
				 ADVERTISE_ALL | ADVERTISE_100BASE4 |
				 ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM,
				 adv);
	अगर (err < 0)
		वापस err;
	अगर (err > 0)
		changed = 1;

	bmsr = phy_पढ़ो(phydev, MII_BMSR);
	अगर (bmsr < 0)
		वापस bmsr;

	/* Per 802.3-2008, Section 22.2.4.2.16 Extended status all
	 * 1000Mbits/sec capable PHYs shall have the BMSR_ESTATEN bit set to a
	 * logical 1.
	 */
	अगर (!(bmsr & BMSR_ESTATEN))
		वापस changed;

	adv = linkmode_adv_to_mii_ctrl1000_t(phydev->advertising);

	err = phy_modअगरy_changed(phydev, MII_CTRL1000,
				 ADVERTISE_1000FULL | ADVERTISE_1000HALF,
				 adv);
	अगर (err < 0)
		वापस err;
	अगर (err > 0)
		changed = 1;

	वापस changed;
पूर्ण

/**
 * genphy_c37_config_advert - sanitize and advertise स्वतः-negotiation parameters
 * @phydev: target phy_device काष्ठा
 *
 * Description: Writes MII_ADVERTISE with the appropriate values,
 *   after sanitizing the values to make sure we only advertise
 *   what is supported.  Returns < 0 on error, 0 अगर the PHY's advertisement
 *   hasn't changed, and > 0 अगर it has changed. This function is पूर्णांकended
 *   क्रम Clause 37 1000Base-X mode.
 */
अटल पूर्णांक genphy_c37_config_advert(काष्ठा phy_device *phydev)
अणु
	u16 adv = 0;

	/* Only allow advertising what this PHY supports */
	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
			      phydev->advertising))
		adv |= ADVERTISE_1000XFULL;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			      phydev->advertising))
		adv |= ADVERTISE_1000XPAUSE;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			      phydev->advertising))
		adv |= ADVERTISE_1000XPSE_ASYM;

	वापस phy_modअगरy_changed(phydev, MII_ADVERTISE,
				  ADVERTISE_1000XFULL | ADVERTISE_1000XPAUSE |
				  ADVERTISE_1000XHALF | ADVERTISE_1000XPSE_ASYM,
				  adv);
पूर्ण

/**
 * genphy_config_eee_advert - disable unwanted eee mode advertisement
 * @phydev: target phy_device काष्ठा
 *
 * Description: Writes MDIO_AN_EEE_ADV after disabling unsupported energy
 *   efficent ethernet modes. Returns 0 अगर the PHY's advertisement hasn't
 *   changed, and 1 अगर it has changed.
 */
पूर्णांक genphy_config_eee_advert(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Nothing to disable */
	अगर (!phydev->eee_broken_modes)
		वापस 0;

	err = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV,
				     phydev->eee_broken_modes, 0);
	/* If the call failed, we assume that EEE is not supported */
	वापस err < 0 ? 0 : err;
पूर्ण
EXPORT_SYMBOL(genphy_config_eee_advert);

/**
 * genphy_setup_क्रमced - configures/क्रमces speed/duplex from @phydev
 * @phydev: target phy_device काष्ठा
 *
 * Description: Configures MII_BMCR to क्रमce speed/duplex
 *   to the values in phydev. Assumes that the values are valid.
 *   Please see phy_sanitize_settings().
 */
पूर्णांक genphy_setup_क्रमced(काष्ठा phy_device *phydev)
अणु
	u16 ctl = 0;

	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;

	अगर (SPEED_1000 == phydev->speed)
		ctl |= BMCR_SPEED1000;
	अन्यथा अगर (SPEED_100 == phydev->speed)
		ctl |= BMCR_SPEED100;

	अगर (DUPLEX_FULL == phydev->duplex)
		ctl |= BMCR_FULLDPLX;

	वापस phy_modअगरy(phydev, MII_BMCR,
			  ~(BMCR_LOOPBACK | BMCR_ISOLATE | BMCR_PDOWN), ctl);
पूर्ण
EXPORT_SYMBOL(genphy_setup_क्रमced);

अटल पूर्णांक genphy_setup_master_slave(काष्ठा phy_device *phydev)
अणु
	u16 ctl = 0;

	अगर (!phydev->is_gigabit_capable)
		वापस 0;

	चयन (phydev->master_slave_set) अणु
	हाल MASTER_SLAVE_CFG_MASTER_PREFERRED:
		ctl |= CTL1000_PREFER_MASTER;
		अवरोध;
	हाल MASTER_SLAVE_CFG_SLAVE_PREFERRED:
		अवरोध;
	हाल MASTER_SLAVE_CFG_MASTER_FORCE:
		ctl |= CTL1000_AS_MASTER;
		fallthrough;
	हाल MASTER_SLAVE_CFG_SLAVE_FORCE:
		ctl |= CTL1000_ENABLE_MASTER;
		अवरोध;
	हाल MASTER_SLAVE_CFG_UNKNOWN:
	हाल MASTER_SLAVE_CFG_UNSUPPORTED:
		वापस 0;
	शेष:
		phydev_warn(phydev, "Unsupported Master/Slave mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस phy_modअगरy_changed(phydev, MII_CTRL1000,
				  (CTL1000_ENABLE_MASTER | CTL1000_AS_MASTER |
				   CTL1000_PREFER_MASTER), ctl);
पूर्ण

अटल पूर्णांक genphy_पढ़ो_master_slave(काष्ठा phy_device *phydev)
अणु
	पूर्णांक cfg, state;
	पूर्णांक val;

	अगर (!phydev->is_gigabit_capable) अणु
		phydev->master_slave_get = MASTER_SLAVE_CFG_UNSUPPORTED;
		phydev->master_slave_state = MASTER_SLAVE_STATE_UNSUPPORTED;
		वापस 0;
	पूर्ण

	phydev->master_slave_get = MASTER_SLAVE_CFG_UNKNOWN;
	phydev->master_slave_state = MASTER_SLAVE_STATE_UNKNOWN;

	val = phy_पढ़ो(phydev, MII_CTRL1000);
	अगर (val < 0)
		वापस val;

	अगर (val & CTL1000_ENABLE_MASTER) अणु
		अगर (val & CTL1000_AS_MASTER)
			cfg = MASTER_SLAVE_CFG_MASTER_FORCE;
		अन्यथा
			cfg = MASTER_SLAVE_CFG_SLAVE_FORCE;
	पूर्ण अन्यथा अणु
		अगर (val & CTL1000_PREFER_MASTER)
			cfg = MASTER_SLAVE_CFG_MASTER_PREFERRED;
		अन्यथा
			cfg = MASTER_SLAVE_CFG_SLAVE_PREFERRED;
	पूर्ण

	val = phy_पढ़ो(phydev, MII_STAT1000);
	अगर (val < 0)
		वापस val;

	अगर (val & LPA_1000MSFAIL) अणु
		state = MASTER_SLAVE_STATE_ERR;
	पूर्ण अन्यथा अगर (phydev->link) अणु
		/* this bits are valid only क्रम active link */
		अगर (val & LPA_1000MSRES)
			state = MASTER_SLAVE_STATE_MASTER;
		अन्यथा
			state = MASTER_SLAVE_STATE_SLAVE;
	पूर्ण अन्यथा अणु
		state = MASTER_SLAVE_STATE_UNKNOWN;
	पूर्ण

	phydev->master_slave_get = cfg;
	phydev->master_slave_state = state;

	वापस 0;
पूर्ण

/**
 * genphy_restart_aneg - Enable and Restart Autonegotiation
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक genphy_restart_aneg(काष्ठा phy_device *phydev)
अणु
	/* Don't isolate the PHY if we're negotiating */
	वापस phy_modअगरy(phydev, MII_BMCR, BMCR_ISOLATE,
			  BMCR_ANENABLE | BMCR_ANRESTART);
पूर्ण
EXPORT_SYMBOL(genphy_restart_aneg);

/**
 * genphy_check_and_restart_aneg - Enable and restart स्वतः-negotiation
 * @phydev: target phy_device काष्ठा
 * @restart: whether aneg restart is requested
 *
 * Check, and restart स्वतः-negotiation अगर needed.
 */
पूर्णांक genphy_check_and_restart_aneg(काष्ठा phy_device *phydev, bool restart)
अणु
	पूर्णांक ret;

	अगर (!restart) अणु
		/* Advertisement hasn't changed, but maybe aneg was never on to
		 * begin with?  Or maybe phy was isolated?
		 */
		ret = phy_पढ़ो(phydev, MII_BMCR);
		अगर (ret < 0)
			वापस ret;

		अगर (!(ret & BMCR_ANENABLE) || (ret & BMCR_ISOLATE))
			restart = true;
	पूर्ण

	अगर (restart)
		वापस genphy_restart_aneg(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_check_and_restart_aneg);

/**
 * __genphy_config_aneg - restart स्वतः-negotiation or ग_लिखो BMCR
 * @phydev: target phy_device काष्ठा
 * @changed: whether स्वतःneg is requested
 *
 * Description: If स्वतः-negotiation is enabled, we configure the
 *   advertising, and then restart स्वतः-negotiation.  If it is not
 *   enabled, then we ग_लिखो the BMCR.
 */
पूर्णांक __genphy_config_aneg(काष्ठा phy_device *phydev, bool changed)
अणु
	पूर्णांक err;

	अगर (genphy_config_eee_advert(phydev))
		changed = true;

	err = genphy_setup_master_slave(phydev);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (err)
		changed = true;

	अगर (AUTONEG_ENABLE != phydev->स्वतःneg)
		वापस genphy_setup_क्रमced(phydev);

	err = genphy_config_advert(phydev);
	अगर (err < 0) /* error */
		वापस err;
	अन्यथा अगर (err)
		changed = true;

	वापस genphy_check_and_restart_aneg(phydev, changed);
पूर्ण
EXPORT_SYMBOL(__genphy_config_aneg);

/**
 * genphy_c37_config_aneg - restart स्वतः-negotiation or ग_लिखो BMCR
 * @phydev: target phy_device काष्ठा
 *
 * Description: If स्वतः-negotiation is enabled, we configure the
 *   advertising, and then restart स्वतः-negotiation.  If it is not
 *   enabled, then we ग_लिखो the BMCR. This function is पूर्णांकended
 *   क्रम use with Clause 37 1000Base-X mode.
 */
पूर्णांक genphy_c37_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, changed;

	अगर (phydev->स्वतःneg != AUTONEG_ENABLE)
		वापस genphy_setup_क्रमced(phydev);

	err = phy_modअगरy(phydev, MII_BMCR, BMCR_SPEED1000 | BMCR_SPEED100,
			 BMCR_SPEED1000);
	अगर (err)
		वापस err;

	changed = genphy_c37_config_advert(phydev);
	अगर (changed < 0) /* error */
		वापस changed;

	अगर (!changed) अणु
		/* Advertisement hasn't changed, but maybe aneg was never on to
		 * begin with?  Or maybe phy was isolated?
		 */
		पूर्णांक ctl = phy_पढ़ो(phydev, MII_BMCR);

		अगर (ctl < 0)
			वापस ctl;

		अगर (!(ctl & BMCR_ANENABLE) || (ctl & BMCR_ISOLATE))
			changed = 1; /* करो restart aneg */
	पूर्ण

	/* Only restart aneg अगर we are advertising something dअगरferent
	 * than we were beक्रमe.
	 */
	अगर (changed > 0)
		वापस genphy_restart_aneg(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_c37_config_aneg);

/**
 * genphy_aneg_करोne - वापस स्वतः-negotiation status
 * @phydev: target phy_device काष्ठा
 *
 * Description: Reads the status रेजिस्टर and वापसs 0 either अगर
 *   स्वतः-negotiation is incomplete, or अगर there was an error.
 *   Returns BMSR_ANEGCOMPLETE अगर स्वतः-negotiation is करोne.
 */
पूर्णांक genphy_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	पूर्णांक retval = phy_पढ़ो(phydev, MII_BMSR);

	वापस (retval < 0) ? retval : (retval & BMSR_ANEGCOMPLETE);
पूर्ण
EXPORT_SYMBOL(genphy_aneg_करोne);

/**
 * genphy_update_link - update link status in @phydev
 * @phydev: target phy_device काष्ठा
 *
 * Description: Update the value in phydev->link to reflect the
 *   current link value.  In order to करो this, we need to पढ़ो
 *   the status रेजिस्टर twice, keeping the second value.
 */
पूर्णांक genphy_update_link(काष्ठा phy_device *phydev)
अणु
	पूर्णांक status = 0, bmcr;

	bmcr = phy_पढ़ो(phydev, MII_BMCR);
	अगर (bmcr < 0)
		वापस bmcr;

	/* Autoneg is being started, thereक्रमe disregard BMSR value and
	 * report link as करोwn.
	 */
	अगर (bmcr & BMCR_ANRESTART)
		जाओ करोne;

	/* The link state is latched low so that momentary link
	 * drops can be detected. Do not द्विगुन-पढ़ो the status
	 * in polling mode to detect such लघु link drops except
	 * the link was alपढ़ोy करोwn.
	 */
	अगर (!phy_polling_mode(phydev) || !phydev->link) अणु
		status = phy_पढ़ो(phydev, MII_BMSR);
		अगर (status < 0)
			वापस status;
		अन्यथा अगर (status & BMSR_LSTATUS)
			जाओ करोne;
	पूर्ण

	/* Read link and स्वतःnegotiation status */
	status = phy_पढ़ो(phydev, MII_BMSR);
	अगर (status < 0)
		वापस status;
करोne:
	phydev->link = status & BMSR_LSTATUS ? 1 : 0;
	phydev->स्वतःneg_complete = status & BMSR_ANEGCOMPLETE ? 1 : 0;

	/* Consider the हाल that स्वतःneg was started and "aneg complete"
	 * bit has been reset, but "link up" bit not yet.
	 */
	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && !phydev->स्वतःneg_complete)
		phydev->link = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_update_link);

पूर्णांक genphy_पढ़ो_lpa(काष्ठा phy_device *phydev)
अणु
	पूर्णांक lpa, lpagb;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (!phydev->स्वतःneg_complete) अणु
			mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising,
							0);
			mii_lpa_mod_linkmode_lpa_t(phydev->lp_advertising, 0);
			वापस 0;
		पूर्ण

		अगर (phydev->is_gigabit_capable) अणु
			lpagb = phy_पढ़ो(phydev, MII_STAT1000);
			अगर (lpagb < 0)
				वापस lpagb;

			अगर (lpagb & LPA_1000MSFAIL) अणु
				पूर्णांक adv = phy_पढ़ो(phydev, MII_CTRL1000);

				अगर (adv < 0)
					वापस adv;

				अगर (adv & CTL1000_ENABLE_MASTER)
					phydev_err(phydev, "Master/Slave resolution failed, maybe conflicting manual settings?\n");
				अन्यथा
					phydev_err(phydev, "Master/Slave resolution failed\n");
				वापस -ENOLINK;
			पूर्ण

			mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising,
							lpagb);
		पूर्ण

		lpa = phy_पढ़ो(phydev, MII_LPA);
		अगर (lpa < 0)
			वापस lpa;

		mii_lpa_mod_linkmode_lpa_t(phydev->lp_advertising, lpa);
	पूर्ण अन्यथा अणु
		linkmode_zero(phydev->lp_advertising);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_पढ़ो_lpa);

/**
 * genphy_पढ़ो_status_fixed - पढ़ो the link parameters क्रम !aneg mode
 * @phydev: target phy_device काष्ठा
 *
 * Read the current duplex and speed state क्रम a PHY operating with
 * स्वतःnegotiation disabled.
 */
पूर्णांक genphy_पढ़ो_status_fixed(काष्ठा phy_device *phydev)
अणु
	पूर्णांक bmcr = phy_पढ़ो(phydev, MII_BMCR);

	अगर (bmcr < 0)
		वापस bmcr;

	अगर (bmcr & BMCR_FULLDPLX)
		phydev->duplex = DUPLEX_FULL;
	अन्यथा
		phydev->duplex = DUPLEX_HALF;

	अगर (bmcr & BMCR_SPEED1000)
		phydev->speed = SPEED_1000;
	अन्यथा अगर (bmcr & BMCR_SPEED100)
		phydev->speed = SPEED_100;
	अन्यथा
		phydev->speed = SPEED_10;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_पढ़ो_status_fixed);

/**
 * genphy_पढ़ो_status - check the link status and update current link state
 * @phydev: target phy_device काष्ठा
 *
 * Description: Check the link, then figure out the current state
 *   by comparing what we advertise with what the link partner
 *   advertises.  Start by checking the gigabit possibilities,
 *   then move on to 10/100.
 */
पूर्णांक genphy_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, old_link = phydev->link;

	/* Update the link, but वापस अगर there was an error */
	err = genphy_update_link(phydev);
	अगर (err)
		वापस err;

	/* why bother the PHY अगर nothing can have changed */
	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && old_link && phydev->link)
		वापस 0;

	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;

	err = genphy_पढ़ो_master_slave(phydev);
	अगर (err < 0)
		वापस err;

	err = genphy_पढ़ो_lpa(phydev);
	अगर (err < 0)
		वापस err;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && phydev->स्वतःneg_complete) अणु
		phy_resolve_aneg_linkmode(phydev);
	पूर्ण अन्यथा अगर (phydev->स्वतःneg == AUTONEG_DISABLE) अणु
		err = genphy_पढ़ो_status_fixed(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_पढ़ो_status);

/**
 * genphy_c37_पढ़ो_status - check the link status and update current link state
 * @phydev: target phy_device काष्ठा
 *
 * Description: Check the link, then figure out the current state
 *   by comparing what we advertise with what the link partner
 *   advertises. This function is क्रम Clause 37 1000Base-X mode.
 */
पूर्णांक genphy_c37_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक lpa, err, old_link = phydev->link;

	/* Update the link, but वापस अगर there was an error */
	err = genphy_update_link(phydev);
	अगर (err)
		वापस err;

	/* why bother the PHY अगर nothing can have changed */
	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && old_link && phydev->link)
		वापस 0;

	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && phydev->स्वतःneg_complete) अणु
		lpa = phy_पढ़ो(phydev, MII_LPA);
		अगर (lpa < 0)
			वापस lpa;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				 phydev->lp_advertising, lpa & LPA_LPACK);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
				 phydev->lp_advertising, lpa & LPA_1000XFULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				 phydev->lp_advertising, lpa & LPA_1000XPAUSE);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				 phydev->lp_advertising,
				 lpa & LPA_1000XPAUSE_ASYM);

		phy_resolve_aneg_linkmode(phydev);
	पूर्ण अन्यथा अगर (phydev->स्वतःneg == AUTONEG_DISABLE) अणु
		पूर्णांक bmcr = phy_पढ़ो(phydev, MII_BMCR);

		अगर (bmcr < 0)
			वापस bmcr;

		अगर (bmcr & BMCR_FULLDPLX)
			phydev->duplex = DUPLEX_FULL;
		अन्यथा
			phydev->duplex = DUPLEX_HALF;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_c37_पढ़ो_status);

/**
 * genphy_soft_reset - software reset the PHY via BMCR_RESET bit
 * @phydev: target phy_device काष्ठा
 *
 * Description: Perक्रमm a software PHY reset using the standard
 * BMCR_RESET bit and poll क्रम the reset bit to be cleared.
 *
 * Returns: 0 on success, < 0 on failure
 */
पूर्णांक genphy_soft_reset(काष्ठा phy_device *phydev)
अणु
	u16 res = BMCR_RESET;
	पूर्णांक ret;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE)
		res |= BMCR_ANRESTART;

	ret = phy_modअगरy(phydev, MII_BMCR, BMCR_ISOLATE, res);
	अगर (ret < 0)
		वापस ret;

	/* Clause 22 states that setting bit BMCR_RESET sets control रेजिस्टरs
	 * to their शेष value. Thereक्रमe the POWER DOWN bit is supposed to
	 * be cleared after soft reset.
	 */
	phydev->suspended = 0;

	ret = phy_poll_reset(phydev);
	अगर (ret)
		वापस ret;

	/* BMCR may be reset to शेषs */
	अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
		ret = genphy_setup_क्रमced(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(genphy_soft_reset);

irqवापस_t genphy_handle_पूर्णांकerrupt_no_ack(काष्ठा phy_device *phydev)
अणु
	/* It seems there are हालs where the पूर्णांकerrupts are handled by another
	 * entity (ie an IRQ controller embedded inside the PHY) and करो not
	 * need any other पूर्णांकerraction from phylib. In this हाल, just trigger
	 * the state machine directly.
	 */
	phy_trigger_machine(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_handle_पूर्णांकerrupt_no_ack);

/**
 * genphy_पढ़ो_abilities - पढ़ो PHY abilities from Clause 22 रेजिस्टरs
 * @phydev: target phy_device काष्ठा
 *
 * Description: Reads the PHY's abilities and populates
 * phydev->supported accordingly.
 *
 * Returns: 0 on success, < 0 on failure
 */
पूर्णांक genphy_पढ़ो_abilities(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phydev->supported);

	val = phy_पढ़ो(phydev, MII_BMSR);
	अगर (val < 0)
		वापस val;

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, phydev->supported,
			 val & BMSR_ANEGCAPABLE);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, phydev->supported,
			 val & BMSR_100FULL);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, phydev->supported,
			 val & BMSR_100HALF);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, phydev->supported,
			 val & BMSR_10FULL);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, phydev->supported,
			 val & BMSR_10HALF);

	अगर (val & BMSR_ESTATEN) अणु
		val = phy_पढ़ो(phydev, MII_ESTATUS);
		अगर (val < 0)
			वापस val;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 phydev->supported, val & ESTATUS_1000_TFULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
				 phydev->supported, val & ESTATUS_1000_THALF);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
				 phydev->supported, val & ESTATUS_1000_XFULL);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_पढ़ो_abilities);

/* This is used क्रम the phy device which करोesn't support the MMD extended
 * रेजिस्टर access, but it करोes have side effect when we are trying to access
 * the MMD रेजिस्टर via indirect method.
 */
पूर्णांक genphy_पढ़ो_mmd_unsupported(काष्ठा phy_device *phdev, पूर्णांक devad, u16 regnum)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(genphy_पढ़ो_mmd_unsupported);

पूर्णांक genphy_ग_लिखो_mmd_unsupported(काष्ठा phy_device *phdev, पूर्णांक devnum,
				 u16 regnum, u16 val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(genphy_ग_लिखो_mmd_unsupported);

पूर्णांक genphy_suspend(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits(phydev, MII_BMCR, BMCR_PDOWN);
पूर्ण
EXPORT_SYMBOL(genphy_suspend);

पूर्णांक genphy_resume(काष्ठा phy_device *phydev)
अणु
	वापस phy_clear_bits(phydev, MII_BMCR, BMCR_PDOWN);
पूर्ण
EXPORT_SYMBOL(genphy_resume);

पूर्णांक genphy_loopback(काष्ठा phy_device *phydev, bool enable)
अणु
	अगर (enable) अणु
		u16 val, ctl = BMCR_LOOPBACK;
		पूर्णांक ret;

		अगर (phydev->speed == SPEED_1000)
			ctl |= BMCR_SPEED1000;
		अन्यथा अगर (phydev->speed == SPEED_100)
			ctl |= BMCR_SPEED100;

		अगर (phydev->duplex == DUPLEX_FULL)
			ctl |= BMCR_FULLDPLX;

		phy_modअगरy(phydev, MII_BMCR, ~0, ctl);

		ret = phy_पढ़ो_poll_समयout(phydev, MII_BMSR, val,
					    val & BMSR_LSTATUS,
				    5000, 500000, true);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		phy_modअगरy(phydev, MII_BMCR, BMCR_LOOPBACK, 0);

		phy_config_aneg(phydev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genphy_loopback);

/**
 * phy_हटाओ_link_mode - Remove a supported link mode
 * @phydev: phy_device काष्ठाure to हटाओ link mode from
 * @link_mode: Link mode to be हटाओd
 *
 * Description: Some MACs करोn't support all link modes which the PHY
 * करोes.  e.g. a 1G MAC often करोes not support 1000Half. Add a helper
 * to हटाओ a link mode.
 */
व्योम phy_हटाओ_link_mode(काष्ठा phy_device *phydev, u32 link_mode)
अणु
	linkmode_clear_bit(link_mode, phydev->supported);
	phy_advertise_supported(phydev);
पूर्ण
EXPORT_SYMBOL(phy_हटाओ_link_mode);

अटल व्योम phy_copy_छोड़ो_bits(अचिन्हित दीर्घ *dst, अचिन्हित दीर्घ *src)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, dst,
		linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, src));
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT, dst,
		linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, src));
पूर्ण

/**
 * phy_advertise_supported - Advertise all supported modes
 * @phydev: target phy_device काष्ठा
 *
 * Description: Called to advertise all supported modes, करोesn't touch
 * छोड़ो mode advertising.
 */
व्योम phy_advertise_supported(काष्ठा phy_device *phydev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(new);

	linkmode_copy(new, phydev->supported);
	phy_copy_छोड़ो_bits(new, phydev->advertising);
	linkmode_copy(phydev->advertising, new);
पूर्ण
EXPORT_SYMBOL(phy_advertise_supported);

/**
 * phy_support_sym_छोड़ो - Enable support of symmetrical छोड़ो
 * @phydev: target phy_device काष्ठा
 *
 * Description: Called by the MAC to indicate is supports symmetrical
 * Pause, but not asym छोड़ो.
 */
व्योम phy_support_sym_छोड़ो(काष्ठा phy_device *phydev)
अणु
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, phydev->supported);
	phy_copy_छोड़ो_bits(phydev->advertising, phydev->supported);
पूर्ण
EXPORT_SYMBOL(phy_support_sym_छोड़ो);

/**
 * phy_support_asym_छोड़ो - Enable support of asym छोड़ो
 * @phydev: target phy_device काष्ठा
 *
 * Description: Called by the MAC to indicate is supports Asym Pause.
 */
व्योम phy_support_asym_छोड़ो(काष्ठा phy_device *phydev)
अणु
	phy_copy_छोड़ो_bits(phydev->advertising, phydev->supported);
पूर्ण
EXPORT_SYMBOL(phy_support_asym_छोड़ो);

/**
 * phy_set_sym_छोड़ो - Configure symmetric Pause
 * @phydev: target phy_device काष्ठा
 * @rx: Receiver Pause is supported
 * @tx: Transmit Pause is supported
 * @स्वतःneg: Auto neg should be used
 *
 * Description: Configure advertised Pause support depending on अगर
 * receiver छोड़ो and छोड़ो स्वतः neg is supported. Generally called
 * from the set_छोड़ोparam .nकरो.
 */
व्योम phy_set_sym_छोड़ो(काष्ठा phy_device *phydev, bool rx, bool tx,
		       bool स्वतःneg)
अणु
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Pause_BIT, phydev->supported);

	अगर (rx && tx && स्वतःneg)
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				 phydev->supported);

	linkmode_copy(phydev->advertising, phydev->supported);
पूर्ण
EXPORT_SYMBOL(phy_set_sym_छोड़ो);

/**
 * phy_set_asym_छोड़ो - Configure Pause and Asym Pause
 * @phydev: target phy_device काष्ठा
 * @rx: Receiver Pause is supported
 * @tx: Transmit Pause is supported
 *
 * Description: Configure advertised Pause support depending on अगर
 * transmit and receiver छोड़ो is supported. If there has been a
 * change in adverting, trigger a new स्वतःneg. Generally called from
 * the set_छोड़ोparam .nकरो.
 */
व्योम phy_set_asym_छोड़ो(काष्ठा phy_device *phydev, bool rx, bool tx)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(oldadv);

	linkmode_copy(oldadv, phydev->advertising);
	linkmode_set_छोड़ो(phydev->advertising, tx, rx);

	अगर (!linkmode_equal(oldadv, phydev->advertising) &&
	    phydev->स्वतःneg)
		phy_start_aneg(phydev);
पूर्ण
EXPORT_SYMBOL(phy_set_asym_छोड़ो);

/**
 * phy_validate_छोड़ो - Test अगर the PHY/MAC support the छोड़ो configuration
 * @phydev: phy_device काष्ठा
 * @pp: requested छोड़ो configuration
 *
 * Description: Test अगर the PHY/MAC combination supports the Pause
 * configuration the user is requesting. Returns True अगर it is
 * supported, false otherwise.
 */
bool phy_validate_छोड़ो(काष्ठा phy_device *phydev,
			काष्ठा ethtool_छोड़ोparam *pp)
अणु
	अगर (!linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			       phydev->supported) && pp->rx_छोड़ो)
		वापस false;

	अगर (!linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			       phydev->supported) &&
	    pp->rx_छोड़ो != pp->tx_छोड़ो)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(phy_validate_छोड़ो);

/**
 * phy_get_छोड़ो - resolve negotiated छोड़ो modes
 * @phydev: phy_device काष्ठा
 * @tx_छोड़ो: poपूर्णांकer to bool to indicate whether transmit छोड़ो should be
 * enabled.
 * @rx_छोड़ो: poपूर्णांकer to bool to indicate whether receive छोड़ो should be
 * enabled.
 *
 * Resolve and वापस the flow control modes according to the negotiation
 * result. This includes checking that we are operating in full duplex mode.
 * See linkmode_resolve_छोड़ो() क्रम further details.
 */
व्योम phy_get_छोड़ो(काष्ठा phy_device *phydev, bool *tx_छोड़ो, bool *rx_छोड़ो)
अणु
	अगर (phydev->duplex != DUPLEX_FULL) अणु
		*tx_छोड़ो = false;
		*rx_छोड़ो = false;
		वापस;
	पूर्ण

	वापस linkmode_resolve_छोड़ो(phydev->advertising,
				      phydev->lp_advertising,
				      tx_छोड़ो, rx_छोड़ो);
पूर्ण
EXPORT_SYMBOL(phy_get_छोड़ो);

#अगर IS_ENABLED(CONFIG_OF_MDIO)
अटल पूर्णांक phy_get_पूर्णांक_delay_property(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	s32 पूर्णांक_delay;
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, name, &पूर्णांक_delay);
	अगर (ret)
		वापस ret;

	वापस पूर्णांक_delay;
पूर्ण
#अन्यथा
अटल पूर्णांक phy_get_पूर्णांक_delay_property(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/**
 * phy_get_पूर्णांकernal_delay - वापसs the index of the पूर्णांकernal delay
 * @phydev: phy_device काष्ठा
 * @dev: poपूर्णांकer to the devices device काष्ठा
 * @delay_values: array of delays the PHY supports
 * @size: the size of the delay array
 * @is_rx: boolean to indicate to get the rx पूर्णांकernal delay
 *
 * Returns the index within the array of पूर्णांकernal delay passed in.
 * If the device property is not present then the पूर्णांकerface type is checked
 * अगर the पूर्णांकerface defines use of पूर्णांकernal delay then a 1 is वापसed otherwise
 * a 0 is वापसed.
 * The array must be in ascending order. If PHY करोes not have an ascending order
 * array then size = 0 and the value of the delay property is वापसed.
 * Return -EINVAL अगर the delay is invalid or cannot be found.
 */
s32 phy_get_पूर्णांकernal_delay(काष्ठा phy_device *phydev, काष्ठा device *dev,
			   स्थिर पूर्णांक *delay_values, पूर्णांक size, bool is_rx)
अणु
	s32 delay;
	पूर्णांक i;

	अगर (is_rx) अणु
		delay = phy_get_पूर्णांक_delay_property(dev, "rx-internal-delay-ps");
		अगर (delay < 0 && size == 0) अणु
			अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
			    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
				वापस 1;
			अन्यथा
				वापस 0;
		पूर्ण

	पूर्ण अन्यथा अणु
		delay = phy_get_पूर्णांक_delay_property(dev, "tx-internal-delay-ps");
		अगर (delay < 0 && size == 0) अणु
			अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
			    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
				वापस 1;
			अन्यथा
				वापस 0;
		पूर्ण
	पूर्ण

	अगर (delay < 0)
		वापस delay;

	अगर (delay && size == 0)
		वापस delay;

	अगर (delay < delay_values[0] || delay > delay_values[size - 1]) अणु
		phydev_err(phydev, "Delay %d is out of range\n", delay);
		वापस -EINVAL;
	पूर्ण

	अगर (delay == delay_values[0])
		वापस 0;

	क्रम (i = 1; i < size; i++) अणु
		अगर (delay == delay_values[i])
			वापस i;

		/* Find an approximate index by looking up the table */
		अगर (delay > delay_values[i - 1] &&
		    delay < delay_values[i]) अणु
			अगर (delay - delay_values[i - 1] <
			    delay_values[i] - delay)
				वापस i - 1;
			अन्यथा
				वापस i;
		पूर्ण
	पूर्ण

	phydev_err(phydev, "error finding internal delay index for %d\n",
		   delay);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(phy_get_पूर्णांकernal_delay);

अटल bool phy_drv_supports_irq(काष्ठा phy_driver *phydrv)
अणु
	वापस phydrv->config_पूर्णांकr && phydrv->handle_पूर्णांकerrupt;
पूर्ण

/**
 * phy_probe - probe and init a PHY device
 * @dev: device to probe and init
 *
 * Description: Take care of setting up the phy_device काष्ठाure,
 *   set the state to READY (the driver's init function should
 *   set it to STARTING अगर needed).
 */
अटल पूर्णांक phy_probe(काष्ठा device *dev)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);
	काष्ठा device_driver *drv = phydev->mdio.dev.driver;
	काष्ठा phy_driver *phydrv = to_phy_driver(drv);
	पूर्णांक err = 0;

	phydev->drv = phydrv;

	/* Disable the पूर्णांकerrupt अगर the PHY करोesn't support it
	 * but the पूर्णांकerrupt is still a valid one
	 */
	 अगर (!phy_drv_supports_irq(phydrv) && phy_पूर्णांकerrupt_is_valid(phydev))
		phydev->irq = PHY_POLL;

	अगर (phydrv->flags & PHY_IS_INTERNAL)
		phydev->is_पूर्णांकernal = true;

	mutex_lock(&phydev->lock);

	/* Deनिश्चित the reset संकेत */
	phy_device_reset(phydev, 0);

	अगर (phydev->drv->probe) अणु
		err = phydev->drv->probe(phydev);
		अगर (err)
			जाओ out;
	पूर्ण

	/* Start out supporting everything. Eventually,
	 * a controller will attach, and may modअगरy one
	 * or both of these values
	 */
	अगर (phydrv->features) अणु
		linkmode_copy(phydev->supported, phydrv->features);
	पूर्ण अन्यथा अगर (phydrv->get_features) अणु
		err = phydrv->get_features(phydev);
	पूर्ण अन्यथा अगर (phydev->is_c45) अणु
		err = genphy_c45_pma_पढ़ो_abilities(phydev);
	पूर्ण अन्यथा अणु
		err = genphy_पढ़ो_abilities(phydev);
	पूर्ण

	अगर (err)
		जाओ out;

	अगर (!linkmode_test_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
			       phydev->supported))
		phydev->स्वतःneg = 0;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			      phydev->supported))
		phydev->is_gigabit_capable = 1;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			      phydev->supported))
		phydev->is_gigabit_capable = 1;

	of_set_phy_supported(phydev);
	phy_advertise_supported(phydev);

	/* Get the EEE modes we want to prohibit. We will ask
	 * the PHY stop advertising these mode later on
	 */
	of_set_phy_eee_broken(phydev);

	/* The Pause Frame bits indicate that the PHY can support passing
	 * छोड़ो frames. During स्वतःnegotiation, the PHYs will determine अगर
	 * they should allow छोड़ो frames to pass.  The MAC driver should then
	 * use that result to determine whether to enable flow control via
	 * छोड़ो frames.
	 *
	 * Normally, PHY drivers should not set the Pause bits, and instead
	 * allow phylib to करो that.  However, there may be some situations
	 * (e.g. hardware erratum) where the driver wants to set only one
	 * of these bits.
	 */
	अगर (!test_bit(ETHTOOL_LINK_MODE_Pause_BIT, phydev->supported) &&
	    !test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, phydev->supported)) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				 phydev->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				 phydev->supported);
	पूर्ण

	/* Set the state to READY by शेष */
	phydev->state = PHY_READY;

out:
	/* Assert the reset संकेत */
	अगर (err)
		phy_device_reset(phydev, 1);

	mutex_unlock(&phydev->lock);

	वापस err;
पूर्ण

अटल पूर्णांक phy_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	cancel_delayed_work_sync(&phydev->state_queue);

	mutex_lock(&phydev->lock);
	phydev->state = PHY_DOWN;
	mutex_unlock(&phydev->lock);

	sfp_bus_del_upstream(phydev->sfp_bus);
	phydev->sfp_bus = शून्य;

	अगर (phydev->drv && phydev->drv->हटाओ)
		phydev->drv->हटाओ(phydev);

	/* Assert the reset संकेत */
	phy_device_reset(phydev, 1);

	phydev->drv = शून्य;

	वापस 0;
पूर्ण

अटल व्योम phy_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा phy_device *phydev = to_phy_device(dev);

	phy_disable_पूर्णांकerrupts(phydev);
पूर्ण

/**
 * phy_driver_रेजिस्टर - रेजिस्टर a phy_driver with the PHY layer
 * @new_driver: new phy_driver to रेजिस्टर
 * @owner: module owning this PHY
 */
पूर्णांक phy_driver_रेजिस्टर(काष्ठा phy_driver *new_driver, काष्ठा module *owner)
अणु
	पूर्णांक retval;

	/* Either the features are hard coded, or dynamically
	 * determined. It cannot be both.
	 */
	अगर (WARN_ON(new_driver->features && new_driver->get_features)) अणु
		pr_err("%s: features and get_features must not both be set\n",
		       new_driver->name);
		वापस -EINVAL;
	पूर्ण

	new_driver->mdiodrv.flags |= MDIO_DEVICE_IS_PHY;
	new_driver->mdiodrv.driver.name = new_driver->name;
	new_driver->mdiodrv.driver.bus = &mdio_bus_type;
	new_driver->mdiodrv.driver.probe = phy_probe;
	new_driver->mdiodrv.driver.हटाओ = phy_हटाओ;
	new_driver->mdiodrv.driver.shutकरोwn = phy_shutकरोwn;
	new_driver->mdiodrv.driver.owner = owner;
	new_driver->mdiodrv.driver.probe_type = PROBE_FORCE_SYNCHRONOUS;

	retval = driver_रेजिस्टर(&new_driver->mdiodrv.driver);
	अगर (retval) अणु
		pr_err("%s: Error %d in registering driver\n",
		       new_driver->name, retval);

		वापस retval;
	पूर्ण

	pr_debug("%s: Registered new driver\n", new_driver->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_driver_रेजिस्टर);

पूर्णांक phy_drivers_रेजिस्टर(काष्ठा phy_driver *new_driver, पूर्णांक n,
			 काष्ठा module *owner)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < n; i++) अणु
		ret = phy_driver_रेजिस्टर(new_driver + i, owner);
		अगर (ret) अणु
			जबतक (i-- > 0)
				phy_driver_unरेजिस्टर(new_driver + i);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_drivers_रेजिस्टर);

व्योम phy_driver_unरेजिस्टर(काष्ठा phy_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->mdiodrv.driver);
पूर्ण
EXPORT_SYMBOL(phy_driver_unरेजिस्टर);

व्योम phy_drivers_unरेजिस्टर(काष्ठा phy_driver *drv, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		phy_driver_unरेजिस्टर(drv + i);
पूर्ण
EXPORT_SYMBOL(phy_drivers_unरेजिस्टर);

अटल काष्ठा phy_driver genphy_driver = अणु
	.phy_id		= 0xffffffff,
	.phy_id_mask	= 0xffffffff,
	.name		= "Generic PHY",
	.get_features	= genphy_पढ़ो_abilities,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
	.set_loopback   = genphy_loopback,
पूर्ण;

अटल स्थिर काष्ठा ethtool_phy_ops phy_ethtool_phy_ops = अणु
	.get_sset_count		= phy_ethtool_get_sset_count,
	.get_strings		= phy_ethtool_get_strings,
	.get_stats		= phy_ethtool_get_stats,
	.start_cable_test	= phy_start_cable_test,
	.start_cable_test_tdr	= phy_start_cable_test_tdr,
पूर्ण;

अटल पूर्णांक __init phy_init(व्योम)
अणु
	पूर्णांक rc;

	rc = mdio_bus_init();
	अगर (rc)
		वापस rc;

	ethtool_set_ethtool_phy_ops(&phy_ethtool_phy_ops);
	features_init();

	rc = phy_driver_रेजिस्टर(&genphy_c45_driver, THIS_MODULE);
	अगर (rc)
		जाओ err_c45;

	rc = phy_driver_रेजिस्टर(&genphy_driver, THIS_MODULE);
	अगर (rc) अणु
		phy_driver_unरेजिस्टर(&genphy_c45_driver);
err_c45:
		mdio_bus_निकास();
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम __निकास phy_निकास(व्योम)
अणु
	phy_driver_unरेजिस्टर(&genphy_c45_driver);
	phy_driver_unरेजिस्टर(&genphy_driver);
	mdio_bus_निकास();
	ethtool_set_ethtool_phy_ops(शून्य);
पूर्ण

subsys_initcall(phy_init);
module_निकास(phy_निकास);
