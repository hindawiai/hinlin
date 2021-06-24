<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-17 Intel Corporation.

#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश "bus.h"
#समावेश "sysfs_local.h"

अटल व्योम sdw_slave_release(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);

	kमुक्त(slave);
पूर्ण

काष्ठा device_type sdw_slave_type = अणु
	.name =		"sdw_slave",
	.release =	sdw_slave_release,
	.uevent =	sdw_slave_uevent,
पूर्ण;

पूर्णांक sdw_slave_add(काष्ठा sdw_bus *bus,
		  काष्ठा sdw_slave_id *id, काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा sdw_slave *slave;
	पूर्णांक ret;
	पूर्णांक i;

	slave = kzalloc(माप(*slave), GFP_KERNEL);
	अगर (!slave)
		वापस -ENOMEM;

	/* Initialize data काष्ठाure */
	स_नकल(&slave->id, id, माप(*id));
	slave->dev.parent = bus->dev;
	slave->dev.fwnode = fwnode;

	अगर (id->unique_id == SDW_IGNORED_UNIQUE_ID) अणु
		/* name shall be sdw:link:mfg:part:class */
		dev_set_name(&slave->dev, "sdw:%x:%x:%x:%x",
			     bus->link_id, id->mfg_id, id->part_id,
			     id->class_id);
	पूर्ण अन्यथा अणु
		/* name shall be sdw:link:mfg:part:class:unique */
		dev_set_name(&slave->dev, "sdw:%x:%x:%x:%x:%x",
			     bus->link_id, id->mfg_id, id->part_id,
			     id->class_id, id->unique_id);
	पूर्ण

	slave->dev.bus = &sdw_bus_type;
	slave->dev.of_node = of_node_get(to_of_node(fwnode));
	slave->dev.type = &sdw_slave_type;
	slave->dev.groups = sdw_slave_status_attr_groups;
	slave->bus = bus;
	slave->status = SDW_SLAVE_UNATTACHED;
	init_completion(&slave->क्रमागतeration_complete);
	init_completion(&slave->initialization_complete);
	slave->dev_num = 0;
	init_completion(&slave->probe_complete);
	slave->probed = false;
	slave->first_पूर्णांकerrupt_करोne = false;

	क्रम (i = 0; i < SDW_MAX_PORTS; i++)
		init_completion(&slave->port_पढ़ोy[i]);

	mutex_lock(&bus->bus_lock);
	list_add_tail(&slave->node, &bus->slaves);
	mutex_unlock(&bus->bus_lock);

	ret = device_रेजिस्टर(&slave->dev);
	अगर (ret) अणु
		dev_err(bus->dev, "Failed to add slave: ret %d\n", ret);

		/*
		 * On err, करोn't मुक्त but drop ref as this will be मुक्तd
		 * when release method is invoked.
		 */
		mutex_lock(&bus->bus_lock);
		list_del(&slave->node);
		mutex_unlock(&bus->bus_lock);
		put_device(&slave->dev);

		वापस ret;
	पूर्ण
	sdw_slave_debugfs_init(slave);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_slave_add);

#अगर IS_ENABLED(CONFIG_ACPI)

अटल bool find_slave(काष्ठा sdw_bus *bus,
		       काष्ठा acpi_device *adev,
		       काष्ठा sdw_slave_id *id)
अणु
	u64 addr;
	अचिन्हित पूर्णांक link_id;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(adev->handle,
				       METHOD_NAME__ADR, शून्य, &addr);

	अगर (ACPI_FAILURE(status)) अणु
		dev_err(bus->dev, "_ADR resolution failed: %x\n",
			status);
		वापस false;
	पूर्ण

	अगर (bus->ops->override_adr)
		addr = bus->ops->override_adr(bus, addr);

	अगर (!addr)
		वापस false;

	/* Extract link id from ADR, Bit 51 to 48 (included) */
	link_id = SDW_DISCO_LINK_ID(addr);

	/* Check क्रम link_id match */
	अगर (link_id != bus->link_id)
		वापस false;

	sdw_extract_slave_id(bus, addr, id);

	वापस true;
पूर्ण

/*
 * sdw_acpi_find_slaves() - Find Slave devices in Master ACPI node
 * @bus: SDW bus instance
 *
 * Scans Master ACPI node क्रम SDW child Slave devices and रेजिस्टरs it.
 */
पूर्णांक sdw_acpi_find_slaves(काष्ठा sdw_bus *bus)
अणु
	काष्ठा acpi_device *adev, *parent;
	काष्ठा acpi_device *adev2, *parent2;

	parent = ACPI_COMPANION(bus->dev);
	अगर (!parent) अणु
		dev_err(bus->dev, "Can't find parent for acpi bind\n");
		वापस -ENODEV;
	पूर्ण

	list_क्रम_each_entry(adev, &parent->children, node) अणु
		काष्ठा sdw_slave_id id;
		काष्ठा sdw_slave_id id2;
		bool ignore_unique_id = true;

		अगर (!find_slave(bus, adev, &id))
			जारी;

		/* brute-क्रमce O(N^2) search क्रम duplicates */
		parent2 = parent;
		list_क्रम_each_entry(adev2, &parent2->children, node) अणु

			अगर (adev == adev2)
				जारी;

			अगर (!find_slave(bus, adev2, &id2))
				जारी;

			अगर (id.sdw_version != id2.sdw_version ||
			    id.mfg_id != id2.mfg_id ||
			    id.part_id != id2.part_id ||
			    id.class_id != id2.class_id)
				जारी;

			अगर (id.unique_id != id2.unique_id) अणु
				dev_dbg(bus->dev,
					"Valid unique IDs 0x%x 0x%x for Slave mfg_id 0x%04x, part_id 0x%04x\n",
					id.unique_id, id2.unique_id, id.mfg_id, id.part_id);
				ignore_unique_id = false;
			पूर्ण अन्यथा अणु
				dev_err(bus->dev,
					"Invalid unique IDs 0x%x 0x%x for Slave mfg_id 0x%04x, part_id 0x%04x\n",
					id.unique_id, id2.unique_id, id.mfg_id, id.part_id);
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		अगर (ignore_unique_id)
			id.unique_id = SDW_IGNORED_UNIQUE_ID;

		/*
		 * करोn't error check क्रम sdw_slave_add as we want to जारी
		 * adding Slaves
		 */
		sdw_slave_add(bus, &id, acpi_fwnode_handle(adev));
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

/*
 * sdw_of_find_slaves() - Find Slave devices in master device tree node
 * @bus: SDW bus instance
 *
 * Scans Master DT node क्रम SDW child Slave devices and रेजिस्टरs it.
 */
पूर्णांक sdw_of_find_slaves(काष्ठा sdw_bus *bus)
अणु
	काष्ठा device *dev = bus->dev;
	काष्ठा device_node *node;

	क्रम_each_child_of_node(bus->dev->of_node, node) अणु
		पूर्णांक link_id, ret, len;
		अचिन्हित पूर्णांक sdw_version;
		स्थिर अक्षर *compat = शून्य;
		काष्ठा sdw_slave_id id;
		स्थिर __be32 *addr;

		compat = of_get_property(node, "compatible", शून्य);
		अगर (!compat)
			जारी;

		ret = माला_पूछो(compat, "sdw%01x%04hx%04hx%02hhx", &sdw_version,
			     &id.mfg_id, &id.part_id, &id.class_id);

		अगर (ret != 4) अणु
			dev_err(dev, "Invalid compatible string found %s\n",
				compat);
			जारी;
		पूर्ण

		addr = of_get_property(node, "reg", &len);
		अगर (!addr || (len < 2 * माप(u32))) अणु
			dev_err(dev, "Invalid Link and Instance ID\n");
			जारी;
		पूर्ण

		link_id = be32_to_cpup(addr++);
		id.unique_id = be32_to_cpup(addr);
		id.sdw_version = sdw_version;

		/* Check क्रम link_id match */
		अगर (link_id != bus->link_id)
			जारी;

		sdw_slave_add(bus, &id, of_fwnode_handle(node));
	पूर्ण

	वापस 0;
पूर्ण
