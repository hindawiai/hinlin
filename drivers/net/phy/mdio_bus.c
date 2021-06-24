<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* MDIO Bus पूर्णांकerface
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/reset.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/unistd.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mdपन.स>

#समावेश "mdio-boardinfo.h"

अटल पूर्णांक mdiobus_रेजिस्टर_gpiod(काष्ठा mdio_device *mdiodev)
अणु
	/* Deनिश्चित the optional reset संकेत */
	mdiodev->reset_gpio = gpiod_get_optional(&mdiodev->dev,
						 "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(mdiodev->reset_gpio))
		वापस PTR_ERR(mdiodev->reset_gpio);

	अगर (mdiodev->reset_gpio)
		gpiod_set_consumer_name(mdiodev->reset_gpio, "PHY reset");

	वापस 0;
पूर्ण

अटल पूर्णांक mdiobus_रेजिस्टर_reset(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा reset_control *reset;

	reset = reset_control_get_optional_exclusive(&mdiodev->dev, "phy");
	अगर (IS_ERR(reset))
		वापस PTR_ERR(reset);

	mdiodev->reset_ctrl = reset;

	वापस 0;
पूर्ण

पूर्णांक mdiobus_रेजिस्टर_device(काष्ठा mdio_device *mdiodev)
अणु
	पूर्णांक err;

	अगर (mdiodev->bus->mdio_map[mdiodev->addr])
		वापस -EBUSY;

	अगर (mdiodev->flags & MDIO_DEVICE_FLAG_PHY) अणु
		err = mdiobus_रेजिस्टर_gpiod(mdiodev);
		अगर (err)
			वापस err;

		err = mdiobus_रेजिस्टर_reset(mdiodev);
		अगर (err)
			वापस err;

		/* Assert the reset संकेत */
		mdio_device_reset(mdiodev, 1);
	पूर्ण

	mdiodev->bus->mdio_map[mdiodev->addr] = mdiodev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdiobus_रेजिस्टर_device);

पूर्णांक mdiobus_unरेजिस्टर_device(काष्ठा mdio_device *mdiodev)
अणु
	अगर (mdiodev->bus->mdio_map[mdiodev->addr] != mdiodev)
		वापस -EINVAL;

	reset_control_put(mdiodev->reset_ctrl);

	mdiodev->bus->mdio_map[mdiodev->addr] = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdiobus_unरेजिस्टर_device);

काष्ठा phy_device *mdiobus_get_phy(काष्ठा mii_bus *bus, पूर्णांक addr)
अणु
	काष्ठा mdio_device *mdiodev = bus->mdio_map[addr];

	अगर (!mdiodev)
		वापस शून्य;

	अगर (!(mdiodev->flags & MDIO_DEVICE_FLAG_PHY))
		वापस शून्य;

	वापस container_of(mdiodev, काष्ठा phy_device, mdio);
पूर्ण
EXPORT_SYMBOL(mdiobus_get_phy);

bool mdiobus_is_रेजिस्टरed_device(काष्ठा mii_bus *bus, पूर्णांक addr)
अणु
	वापस bus->mdio_map[addr];
पूर्ण
EXPORT_SYMBOL(mdiobus_is_रेजिस्टरed_device);

/**
 * mdiobus_alloc_size - allocate a mii_bus काष्ठाure
 * @size: extra amount of memory to allocate क्रम निजी storage.
 * If non-zero, then bus->priv is poपूर्णांकs to that memory.
 *
 * Description: called by a bus driver to allocate an mii_bus
 * काष्ठाure to fill in.
 */
काष्ठा mii_bus *mdiobus_alloc_size(माप_प्रकार size)
अणु
	काष्ठा mii_bus *bus;
	माप_प्रकार aligned_size = ALIGN(माप(*bus), NETDEV_ALIGN);
	माप_प्रकार alloc_size;
	पूर्णांक i;

	/* If we alloc extra space, it should be aligned */
	अगर (size)
		alloc_size = aligned_size + size;
	अन्यथा
		alloc_size = माप(*bus);

	bus = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!bus)
		वापस शून्य;

	bus->state = MDIOBUS_ALLOCATED;
	अगर (size)
		bus->priv = (व्योम *)bus + aligned_size;

	/* Initialise the पूर्णांकerrupts to polling and 64-bit seqcounts */
	क्रम (i = 0; i < PHY_MAX_ADDR; i++) अणु
		bus->irq[i] = PHY_POLL;
		u64_stats_init(&bus->stats[i].syncp);
	पूर्ण

	वापस bus;
पूर्ण
EXPORT_SYMBOL(mdiobus_alloc_size);

/**
 * mdiobus_release - mii_bus device release callback
 * @d: the target काष्ठा device that contains the mii_bus
 *
 * Description: called when the last reference to an mii_bus is
 * dropped, to मुक्त the underlying memory.
 */
अटल व्योम mdiobus_release(काष्ठा device *d)
अणु
	काष्ठा mii_bus *bus = to_mii_bus(d);
	BUG_ON(bus->state != MDIOBUS_RELEASED &&
	       /* क्रम compatibility with error handling in drivers */
	       bus->state != MDIOBUS_ALLOCATED);
	kमुक्त(bus);
पूर्ण

काष्ठा mdio_bus_stat_attr अणु
	पूर्णांक addr;
	अचिन्हित पूर्णांक field_offset;
पूर्ण;

अटल u64 mdio_bus_get_stat(काष्ठा mdio_bus_stats *s, अचिन्हित पूर्णांक offset)
अणु
	स्थिर अक्षर *p = (स्थिर अक्षर *)s + offset;
	अचिन्हित पूर्णांक start;
	u64 val = 0;

	करो अणु
		start = u64_stats_fetch_begin(&s->syncp);
		val = u64_stats_पढ़ो((स्थिर u64_stats_t *)p);
	पूर्ण जबतक (u64_stats_fetch_retry(&s->syncp, start));

	वापस val;
पूर्ण

अटल u64 mdio_bus_get_global_stat(काष्ठा mii_bus *bus, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक i;
	u64 val = 0;

	क्रम (i = 0; i < PHY_MAX_ADDR; i++)
		val += mdio_bus_get_stat(&bus->stats[i], offset);

	वापस val;
पूर्ण

अटल sमाप_प्रकार mdio_bus_stat_field_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा mii_bus *bus = to_mii_bus(dev);
	काष्ठा mdio_bus_stat_attr *sattr;
	काष्ठा dev_ext_attribute *eattr;
	u64 val;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	sattr = eattr->var;

	अगर (sattr->addr < 0)
		val = mdio_bus_get_global_stat(bus, sattr->field_offset);
	अन्यथा
		val = mdio_bus_get_stat(&bus->stats[sattr->addr],
					sattr->field_offset);

	वापस प्र_लिखो(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार mdio_bus_device_stat_field_show(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा mdio_device *mdiodev = to_mdio_device(dev);
	काष्ठा mii_bus *bus = mdiodev->bus;
	काष्ठा mdio_bus_stat_attr *sattr;
	काष्ठा dev_ext_attribute *eattr;
	पूर्णांक addr = mdiodev->addr;
	u64 val;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	sattr = eattr->var;

	val = mdio_bus_get_stat(&bus->stats[addr], sattr->field_offset);

	वापस प्र_लिखो(buf, "%llu\n", val);
पूर्ण

#घोषणा MDIO_BUS_STATS_ATTR_DECL(field, file)				\
अटल काष्ठा dev_ext_attribute dev_attr_mdio_bus_##field = अणु		\
	.attr = अणु .attr = अणु .name = file, .mode = 0444 पूर्ण,		\
		     .show = mdio_bus_stat_field_show,			\
	पूर्ण,								\
	.var = &((काष्ठा mdio_bus_stat_attr) अणु				\
		-1, दुरत्व(काष्ठा mdio_bus_stats, field)		\
	पूर्ण),								\
पूर्ण;									\
अटल काष्ठा dev_ext_attribute dev_attr_mdio_bus_device_##field = अणु	\
	.attr = अणु .attr = अणु .name = file, .mode = 0444 पूर्ण,		\
		     .show = mdio_bus_device_stat_field_show,		\
	पूर्ण,								\
	.var = &((काष्ठा mdio_bus_stat_attr) अणु				\
		-1, दुरत्व(काष्ठा mdio_bus_stats, field)		\
	पूर्ण),								\
पूर्ण;

#घोषणा MDIO_BUS_STATS_ATTR(field)					\
	MDIO_BUS_STATS_ATTR_DECL(field, __stringअगरy(field))

MDIO_BUS_STATS_ATTR(transfers);
MDIO_BUS_STATS_ATTR(errors);
MDIO_BUS_STATS_ATTR(ग_लिखोs);
MDIO_BUS_STATS_ATTR(पढ़ोs);

#घोषणा MDIO_BUS_STATS_ADDR_ATTR_DECL(field, addr, file)		\
अटल काष्ठा dev_ext_attribute dev_attr_mdio_bus_addr_##field##_##addr = अणु \
	.attr = अणु .attr = अणु .name = file, .mode = 0444 पूर्ण,		\
		     .show = mdio_bus_stat_field_show,			\
	पूर्ण,								\
	.var = &((काष्ठा mdio_bus_stat_attr) अणु				\
		addr, दुरत्व(काष्ठा mdio_bus_stats, field)		\
	पूर्ण),								\
पूर्ण

#घोषणा MDIO_BUS_STATS_ADDR_ATTR(field, addr)				\
	MDIO_BUS_STATS_ADDR_ATTR_DECL(field, addr,			\
				 __stringअगरy(field) "_" __stringअगरy(addr))

#घोषणा MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(addr)			\
	MDIO_BUS_STATS_ADDR_ATTR(transfers, addr);			\
	MDIO_BUS_STATS_ADDR_ATTR(errors, addr);				\
	MDIO_BUS_STATS_ADDR_ATTR(ग_लिखोs, addr);				\
	MDIO_BUS_STATS_ADDR_ATTR(पढ़ोs, addr)				\

MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(0);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(1);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(2);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(3);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(4);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(5);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(6);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(7);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(8);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(9);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(10);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(11);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(12);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(13);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(14);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(15);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(16);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(17);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(18);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(19);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(20);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(21);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(22);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(23);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(24);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(25);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(26);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(27);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(28);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(29);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(30);
MDIO_BUS_STATS_ADDR_ATTR_GROUP_DECL(31);

#घोषणा MDIO_BUS_STATS_ADDR_ATTR_GROUP(addr)				\
	&dev_attr_mdio_bus_addr_transfers_##addr.attr.attr,		\
	&dev_attr_mdio_bus_addr_errors_##addr.attr.attr,		\
	&dev_attr_mdio_bus_addr_ग_लिखोs_##addr.attr.attr,		\
	&dev_attr_mdio_bus_addr_पढ़ोs_##addr.attr.attr			\

अटल काष्ठा attribute *mdio_bus_statistics_attrs[] = अणु
	&dev_attr_mdio_bus_transfers.attr.attr,
	&dev_attr_mdio_bus_errors.attr.attr,
	&dev_attr_mdio_bus_ग_लिखोs.attr.attr,
	&dev_attr_mdio_bus_पढ़ोs.attr.attr,
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(0),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(1),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(2),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(3),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(4),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(5),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(6),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(7),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(8),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(9),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(10),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(11),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(12),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(13),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(14),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(15),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(16),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(17),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(18),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(19),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(20),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(21),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(22),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(23),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(24),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(25),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(26),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(27),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(28),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(29),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(30),
	MDIO_BUS_STATS_ADDR_ATTR_GROUP(31),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mdio_bus_statistics_group = अणु
	.name	= "statistics",
	.attrs	= mdio_bus_statistics_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mdio_bus_groups[] = अणु
	&mdio_bus_statistics_group,
	शून्य,
पूर्ण;

अटल काष्ठा class mdio_bus_class = अणु
	.name		= "mdio_bus",
	.dev_release	= mdiobus_release,
	.dev_groups	= mdio_bus_groups,
पूर्ण;

/**
 * mdio_find_bus - Given the name of a mdiobus, find the mii_bus.
 * @mdio_name: The name of a mdiobus.
 *
 * Returns a reference to the mii_bus, or शून्य अगर none found.  The
 * embedded काष्ठा device will have its reference count incremented,
 * and this must be put_deviced'ed once the bus is finished with.
 */
काष्ठा mii_bus *mdio_find_bus(स्थिर अक्षर *mdio_name)
अणु
	काष्ठा device *d;

	d = class_find_device_by_name(&mdio_bus_class, mdio_name);
	वापस d ? to_mii_bus(d) : शून्य;
पूर्ण
EXPORT_SYMBOL(mdio_find_bus);

#अगर IS_ENABLED(CONFIG_OF_MDIO)
/**
 * of_mdio_find_bus - Given an mii_bus node, find the mii_bus.
 * @mdio_bus_np: Poपूर्णांकer to the mii_bus.
 *
 * Returns a reference to the mii_bus, or शून्य अगर none found.  The
 * embedded काष्ठा device will have its reference count incremented,
 * and this must be put once the bus is finished with.
 *
 * Because the association of a device_node and mii_bus is made via
 * of_mdiobus_रेजिस्टर(), the mii_bus cannot be found beक्रमe it is
 * रेजिस्टरed with of_mdiobus_रेजिस्टर().
 *
 */
काष्ठा mii_bus *of_mdio_find_bus(काष्ठा device_node *mdio_bus_np)
अणु
	काष्ठा device *d;

	अगर (!mdio_bus_np)
		वापस शून्य;

	d = class_find_device_by_of_node(&mdio_bus_class, mdio_bus_np);
	वापस d ? to_mii_bus(d) : शून्य;
पूर्ण
EXPORT_SYMBOL(of_mdio_find_bus);

/* Walk the list of subnodes of a mdio bus and look क्रम a node that
 * matches the mdio device's address with its 'reg' property. If
 * found, set the of_node poपूर्णांकer क्रम the mdio device. This allows
 * स्वतः-probed phy devices to be supplied with inक्रमmation passed in
 * via DT.
 */
अटल व्योम of_mdiobus_link_mdiodev(काष्ठा mii_bus *bus,
				    काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा device *dev = &mdiodev->dev;
	काष्ठा device_node *child;

	अगर (dev->of_node || !bus->dev.of_node)
		वापस;

	क्रम_each_available_child_of_node(bus->dev.of_node, child) अणु
		पूर्णांक addr;

		addr = of_mdio_parse_addr(dev, child);
		अगर (addr < 0)
			जारी;

		अगर (addr == mdiodev->addr) अणु
			dev->of_node = child;
			dev->fwnode = of_fwnode_handle(child);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा /* !IS_ENABLED(CONFIG_OF_MDIO) */
अटल अंतरभूत व्योम of_mdiobus_link_mdiodev(काष्ठा mii_bus *mdio,
					   काष्ठा mdio_device *mdiodev)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * mdiobus_create_device - create a full MDIO device given
 * a mdio_board_info काष्ठाure
 * @bus: MDIO bus to create the devices on
 * @bi: mdio_board_info काष्ठाure describing the devices
 *
 * Returns 0 on success or < 0 on error.
 */
अटल पूर्णांक mdiobus_create_device(काष्ठा mii_bus *bus,
				 काष्ठा mdio_board_info *bi)
अणु
	काष्ठा mdio_device *mdiodev;
	पूर्णांक ret = 0;

	mdiodev = mdio_device_create(bus, bi->mdio_addr);
	अगर (IS_ERR(mdiodev))
		वापस -ENODEV;

	म_नकलन(mdiodev->modalias, bi->modalias,
		माप(mdiodev->modalias));
	mdiodev->bus_match = mdio_device_bus_match;
	mdiodev->dev.platक्रमm_data = (व्योम *)bi->platक्रमm_data;

	ret = mdio_device_रेजिस्टर(mdiodev);
	अगर (ret)
		mdio_device_मुक्त(mdiodev);

	वापस ret;
पूर्ण

/**
 * __mdiobus_रेजिस्टर - bring up all the PHYs on a given bus and attach them to bus
 * @bus: target mii_bus
 * @owner: module containing bus accessor functions
 *
 * Description: Called by a bus driver to bring up all the PHYs
 *   on a given bus, and attach them to the bus. Drivers should use
 *   mdiobus_रेजिस्टर() rather than __mdiobus_रेजिस्टर() unless they
 *   need to pass a specअगरic owner module. MDIO devices which are not
 *   PHYs will not be brought up by this function. They are expected
 *   to be explicitly listed in DT and instantiated by of_mdiobus_रेजिस्टर().
 *
 * Returns 0 on success or < 0 on error.
 */
पूर्णांक __mdiobus_रेजिस्टर(काष्ठा mii_bus *bus, काष्ठा module *owner)
अणु
	काष्ठा mdio_device *mdiodev;
	पूर्णांक i, err;
	काष्ठा gpio_desc *gpiod;

	अगर (शून्य == bus || शून्य == bus->name ||
	    शून्य == bus->पढ़ो || शून्य == bus->ग_लिखो)
		वापस -EINVAL;

	BUG_ON(bus->state != MDIOBUS_ALLOCATED &&
	       bus->state != MDIOBUS_UNREGISTERED);

	bus->owner = owner;
	bus->dev.parent = bus->parent;
	bus->dev.class = &mdio_bus_class;
	bus->dev.groups = शून्य;
	dev_set_name(&bus->dev, "%s", bus->id);

	err = device_रेजिस्टर(&bus->dev);
	अगर (err) अणु
		pr_err("mii_bus %s failed to register\n", bus->id);
		वापस -EINVAL;
	पूर्ण

	mutex_init(&bus->mdio_lock);
	mutex_init(&bus->shared_lock);

	/* निश्चित bus level PHY GPIO reset */
	gpiod = devm_gpiod_get_optional(&bus->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod)) अणु
		err = dev_err_probe(&bus->dev, PTR_ERR(gpiod),
				    "mii_bus %s couldn't get reset GPIO\n",
				    bus->id);
		device_del(&bus->dev);
		वापस err;
	पूर्ण अन्यथा	अगर (gpiod) अणु
		bus->reset_gpiod = gpiod;
		fsleep(bus->reset_delay_us);
		gpiod_set_value_cansleep(gpiod, 0);
		अगर (bus->reset_post_delay_us > 0)
			fsleep(bus->reset_post_delay_us);
	पूर्ण

	अगर (bus->reset) अणु
		err = bus->reset(bus);
		अगर (err)
			जाओ error_reset_gpiod;
	पूर्ण

	क्रम (i = 0; i < PHY_MAX_ADDR; i++) अणु
		अगर ((bus->phy_mask & (1 << i)) == 0) अणु
			काष्ठा phy_device *phydev;

			phydev = mdiobus_scan(bus, i);
			अगर (IS_ERR(phydev) && (PTR_ERR(phydev) != -ENODEV)) अणु
				err = PTR_ERR(phydev);
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	mdiobus_setup_mdiodev_from_board_info(bus, mdiobus_create_device);

	bus->state = MDIOBUS_REGISTERED;
	pr_info("%s: probed\n", bus->name);
	वापस 0;

error:
	जबतक (--i >= 0) अणु
		mdiodev = bus->mdio_map[i];
		अगर (!mdiodev)
			जारी;

		mdiodev->device_हटाओ(mdiodev);
		mdiodev->device_मुक्त(mdiodev);
	पूर्ण
error_reset_gpiod:
	/* Put PHYs in RESET to save घातer */
	अगर (bus->reset_gpiod)
		gpiod_set_value_cansleep(bus->reset_gpiod, 1);

	device_del(&bus->dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(__mdiobus_रेजिस्टर);

व्योम mdiobus_unरेजिस्टर(काष्ठा mii_bus *bus)
अणु
	काष्ठा mdio_device *mdiodev;
	पूर्णांक i;

	अगर (WARN_ON_ONCE(bus->state != MDIOBUS_REGISTERED))
		वापस;
	bus->state = MDIOBUS_UNREGISTERED;

	क्रम (i = 0; i < PHY_MAX_ADDR; i++) अणु
		mdiodev = bus->mdio_map[i];
		अगर (!mdiodev)
			जारी;

		अगर (mdiodev->reset_gpio)
			gpiod_put(mdiodev->reset_gpio);

		mdiodev->device_हटाओ(mdiodev);
		mdiodev->device_मुक्त(mdiodev);
	पूर्ण

	/* Put PHYs in RESET to save घातer */
	अगर (bus->reset_gpiod)
		gpiod_set_value_cansleep(bus->reset_gpiod, 1);

	device_del(&bus->dev);
पूर्ण
EXPORT_SYMBOL(mdiobus_unरेजिस्टर);

/**
 * mdiobus_मुक्त - मुक्त a काष्ठा mii_bus
 * @bus: mii_bus to मुक्त
 *
 * This function releases the reference to the underlying device
 * object in the mii_bus.  If this is the last reference, the mii_bus
 * will be मुक्तd.
 */
व्योम mdiobus_मुक्त(काष्ठा mii_bus *bus)
अणु
	/* For compatibility with error handling in drivers. */
	अगर (bus->state == MDIOBUS_ALLOCATED) अणु
		kमुक्त(bus);
		वापस;
	पूर्ण

	BUG_ON(bus->state != MDIOBUS_UNREGISTERED);
	bus->state = MDIOBUS_RELEASED;

	put_device(&bus->dev);
पूर्ण
EXPORT_SYMBOL(mdiobus_मुक्त);

/**
 * mdiobus_scan - scan a bus क्रम MDIO devices.
 * @bus: mii_bus to scan
 * @addr: address on bus to scan
 *
 * This function scans the MDIO bus, looking क्रम devices which can be
 * identअगरied using a venकरोr/product ID in रेजिस्टरs 2 and 3. Not all
 * MDIO devices have such रेजिस्टरs, but PHY devices typically
 * करो. Hence this function assumes anything found is a PHY, or can be
 * treated as a PHY. Other MDIO devices, such as चयनes, will
 * probably not be found during the scan.
 */
काष्ठा phy_device *mdiobus_scan(काष्ठा mii_bus *bus, पूर्णांक addr)
अणु
	काष्ठा phy_device *phydev = ERR_PTR(-ENODEV);
	पूर्णांक err;

	चयन (bus->probe_capabilities) अणु
	हाल MDIOBUS_NO_CAP:
	हाल MDIOBUS_C22:
		phydev = get_phy_device(bus, addr, false);
		अवरोध;
	हाल MDIOBUS_C45:
		phydev = get_phy_device(bus, addr, true);
		अवरोध;
	हाल MDIOBUS_C22_C45:
		phydev = get_phy_device(bus, addr, false);
		अगर (IS_ERR(phydev))
			phydev = get_phy_device(bus, addr, true);
		अवरोध;
	पूर्ण

	अगर (IS_ERR(phydev))
		वापस phydev;

	/*
	 * For DT, see अगर the स्वतः-probed phy has a correspoding child
	 * in the bus node, and set the of_node poपूर्णांकer in this हाल.
	 */
	of_mdiobus_link_mdiodev(bus, &phydev->mdio);

	err = phy_device_रेजिस्टर(phydev);
	अगर (err) अणु
		phy_device_मुक्त(phydev);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस phydev;
पूर्ण
EXPORT_SYMBOL(mdiobus_scan);

अटल व्योम mdiobus_stats_acct(काष्ठा mdio_bus_stats *stats, bool op, पूर्णांक ret)
अणु
	preempt_disable();
	u64_stats_update_begin(&stats->syncp);

	u64_stats_inc(&stats->transfers);
	अगर (ret < 0) अणु
		u64_stats_inc(&stats->errors);
		जाओ out;
	पूर्ण

	अगर (op)
		u64_stats_inc(&stats->पढ़ोs);
	अन्यथा
		u64_stats_inc(&stats->ग_लिखोs);
out:
	u64_stats_update_end(&stats->syncp);
	preempt_enable();
पूर्ण

/**
 * __mdiobus_पढ़ो - Unlocked version of the mdiobus_पढ़ो function
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to पढ़ो
 *
 * Read a MDIO bus रेजिस्टर. Caller must hold the mdio bus lock.
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context.
 */
पूर्णांक __mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum)
अणु
	पूर्णांक retval;

	lockdep_निश्चित_held_once(&bus->mdio_lock);

	retval = bus->पढ़ो(bus, addr, regnum);

	trace_mdio_access(bus, 1, addr, regnum, retval, retval);
	mdiobus_stats_acct(&bus->stats[addr], true, retval);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(__mdiobus_पढ़ो);

/**
 * __mdiobus_ग_लिखो - Unlocked version of the mdiobus_ग_लिखो function
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: value to ग_लिखो to @regnum
 *
 * Write a MDIO bus रेजिस्टर. Caller must hold the mdio bus lock.
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context.
 */
पूर्णांक __mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 val)
अणु
	पूर्णांक err;

	lockdep_निश्चित_held_once(&bus->mdio_lock);

	err = bus->ग_लिखो(bus, addr, regnum, val);

	trace_mdio_access(bus, 0, addr, regnum, val, err);
	mdiobus_stats_acct(&bus->stats[addr], false, err);

	वापस err;
पूर्ण
EXPORT_SYMBOL(__mdiobus_ग_लिखो);

/**
 * __mdiobus_modअगरy_changed - Unlocked version of the mdiobus_modअगरy function
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: bit mask of bits to set
 *
 * Read, modअगरy, and अगर any change, ग_लिखो the रेजिस्टर value back to the
 * device. Any error वापसs a negative number.
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context.
 */
पूर्णांक __mdiobus_modअगरy_changed(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum,
			     u16 mask, u16 set)
अणु
	पूर्णांक new, ret;

	ret = __mdiobus_पढ़ो(bus, addr, regnum);
	अगर (ret < 0)
		वापस ret;

	new = (ret & ~mask) | set;
	अगर (new == ret)
		वापस 0;

	ret = __mdiobus_ग_लिखो(bus, addr, regnum, new);

	वापस ret < 0 ? ret : 1;
पूर्ण
EXPORT_SYMBOL_GPL(__mdiobus_modअगरy_changed);

/**
 * mdiobus_पढ़ो_nested - Nested version of the mdiobus_पढ़ो function
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to पढ़ो
 *
 * In हाल of nested MDIO bus access aव्योम lockdep false positives by
 * using mutex_lock_nested().
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक mdiobus_पढ़ो_nested(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum)
अणु
	पूर्णांक retval;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);
	retval = __mdiobus_पढ़ो(bus, addr, regnum);
	mutex_unlock(&bus->mdio_lock);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(mdiobus_पढ़ो_nested);

/**
 * mdiobus_पढ़ो - Convenience function क्रम पढ़ोing a given MII mgmt रेजिस्टर
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to पढ़ो
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum)
अणु
	पूर्णांक retval;

	mutex_lock(&bus->mdio_lock);
	retval = __mdiobus_पढ़ो(bus, addr, regnum);
	mutex_unlock(&bus->mdio_lock);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(mdiobus_पढ़ो);

/**
 * mdiobus_ग_लिखो_nested - Nested version of the mdiobus_ग_लिखो function
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: value to ग_लिखो to @regnum
 *
 * In हाल of nested MDIO bus access aव्योम lockdep false positives by
 * using mutex_lock_nested().
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक mdiobus_ग_लिखो_nested(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 val)
अणु
	पूर्णांक err;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);
	err = __mdiobus_ग_लिखो(bus, addr, regnum, val);
	mutex_unlock(&bus->mdio_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mdiobus_ग_लिखो_nested);

/**
 * mdiobus_ग_लिखो - Convenience function क्रम writing a given MII mgmt रेजिस्टर
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: value to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 val)
अणु
	पूर्णांक err;

	mutex_lock(&bus->mdio_lock);
	err = __mdiobus_ग_लिखो(bus, addr, regnum, val);
	mutex_unlock(&bus->mdio_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mdiobus_ग_लिखो);

/**
 * mdiobus_modअगरy - Convenience function क्रम modअगरying a given mdio device
 *	रेजिस्टर
 * @bus: the mii_bus काष्ठा
 * @addr: the phy address
 * @regnum: रेजिस्टर number to ग_लिखो
 * @mask: bit mask of bits to clear
 * @set: bit mask of bits to set
 */
पूर्णांक mdiobus_modअगरy(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 mask, u16 set)
अणु
	पूर्णांक err;

	mutex_lock(&bus->mdio_lock);
	err = __mdiobus_modअगरy_changed(bus, addr, regnum, mask, set);
	mutex_unlock(&bus->mdio_lock);

	वापस err < 0 ? err : 0;
पूर्ण
EXPORT_SYMBOL_GPL(mdiobus_modअगरy);

/**
 * mdio_bus_match - determine अगर given MDIO driver supports the given
 *		    MDIO device
 * @dev: target MDIO device
 * @drv: given MDIO driver
 *
 * Description: Given a MDIO device, and a MDIO driver, वापस 1 अगर
 *   the driver supports the device.  Otherwise, वापस 0. This may
 *   require calling the devices own match function, since dअगरferent classes
 *   of MDIO devices have dअगरferent match criteria.
 */
अटल पूर्णांक mdio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mdio_device *mdio = to_mdio_device(dev);

	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	अगर (mdio->bus_match)
		वापस mdio->bus_match(dev, drv);

	वापस 0;
पूर्ण

अटल पूर्णांक mdio_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक rc;

	/* Some devices have extra OF data and an OF-style MODALIAS */
	rc = of_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	वापस 0;
पूर्ण

अटल काष्ठा attribute *mdio_bus_device_statistics_attrs[] = अणु
	&dev_attr_mdio_bus_device_transfers.attr.attr,
	&dev_attr_mdio_bus_device_errors.attr.attr,
	&dev_attr_mdio_bus_device_ग_लिखोs.attr.attr,
	&dev_attr_mdio_bus_device_पढ़ोs.attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mdio_bus_device_statistics_group = अणु
	.name	= "statistics",
	.attrs	= mdio_bus_device_statistics_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mdio_bus_dev_groups[] = अणु
	&mdio_bus_device_statistics_group,
	शून्य,
पूर्ण;

काष्ठा bus_type mdio_bus_type = अणु
	.name		= "mdio_bus",
	.dev_groups	= mdio_bus_dev_groups,
	.match		= mdio_bus_match,
	.uevent		= mdio_uevent,
पूर्ण;
EXPORT_SYMBOL(mdio_bus_type);

पूर्णांक __init mdio_bus_init(व्योम)
अणु
	पूर्णांक ret;

	ret = class_रेजिस्टर(&mdio_bus_class);
	अगर (!ret) अणु
		ret = bus_रेजिस्टर(&mdio_bus_type);
		अगर (ret)
			class_unरेजिस्टर(&mdio_bus_class);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mdio_bus_init);

#अगर IS_ENABLED(CONFIG_PHYLIB)
व्योम mdio_bus_निकास(व्योम)
अणु
	class_unरेजिस्टर(&mdio_bus_class);
	bus_unरेजिस्टर(&mdio_bus_type);
पूर्ण
EXPORT_SYMBOL_GPL(mdio_bus_निकास);
#अन्यथा
module_init(mdio_bus_init);
/* no module_निकास, पूर्णांकentional */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MDIO bus/device layer");
#पूर्ण_अगर
