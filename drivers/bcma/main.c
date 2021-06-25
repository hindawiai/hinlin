<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * Bus subप्रणाली
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/module.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

MODULE_DESCRIPTION("Broadcom's specific AMBA driver");
MODULE_LICENSE("GPL");

/* contains the number the next bus should get. */
अटल अचिन्हित पूर्णांक bcma_bus_next_num = 0;

/* bcma_buses_mutex locks the bcma_bus_next_num */
अटल DEFINE_MUTEX(bcma_buses_mutex);

अटल पूर्णांक bcma_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv);
अटल पूर्णांक bcma_device_probe(काष्ठा device *dev);
अटल पूर्णांक bcma_device_हटाओ(काष्ठा device *dev);
अटल पूर्णांक bcma_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);

अटल sमाप_प्रकार manuf_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	वापस प्र_लिखो(buf, "0x%03X\n", core->id.manuf);
पूर्ण
अटल DEVICE_ATTR_RO(manuf);

अटल sमाप_प्रकार id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	वापस प्र_लिखो(buf, "0x%03X\n", core->id.id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार rev_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	वापस प्र_लिखो(buf, "0x%02X\n", core->id.rev);
पूर्ण
अटल DEVICE_ATTR_RO(rev);

अटल sमाप_प्रकार class_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	वापस प्र_लिखो(buf, "0x%X\n", core->id.class);
पूर्ण
अटल DEVICE_ATTR_RO(class);

अटल काष्ठा attribute *bcma_device_attrs[] = अणु
	&dev_attr_manuf.attr,
	&dev_attr_id.attr,
	&dev_attr_rev.attr,
	&dev_attr_class.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(bcma_device);

अटल काष्ठा bus_type bcma_bus_type = अणु
	.name		= "bcma",
	.match		= bcma_bus_match,
	.probe		= bcma_device_probe,
	.हटाओ		= bcma_device_हटाओ,
	.uevent		= bcma_device_uevent,
	.dev_groups	= bcma_device_groups,
पूर्ण;

अटल u16 bcma_cc_core_id(काष्ठा bcma_bus *bus)
अणु
	अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
		वापस BCMA_CORE_4706_CHIPCOMMON;
	वापस BCMA_CORE_CHIPCOMMON;
पूर्ण

काष्ठा bcma_device *bcma_find_core_unit(काष्ठा bcma_bus *bus, u16 coreid,
					u8 unit)
अणु
	काष्ठा bcma_device *core;

	list_क्रम_each_entry(core, &bus->cores, list) अणु
		अगर (core->id.id == coreid && core->core_unit == unit)
			वापस core;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_find_core_unit);

bool bcma_रुको_value(काष्ठा bcma_device *core, u16 reg, u32 mask, u32 value,
		     पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + समयout;
	u32 val;

	करो अणु
		val = bcma_पढ़ो32(core, reg);
		अगर ((val & mask) == value)
			वापस true;
		cpu_relax();
		udelay(10);
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	bcma_warn(core->bus, "Timeout waiting for register 0x%04X!\n", reg);

	वापस false;
पूर्ण

अटल व्योम bcma_release_core_dev(काष्ठा device *dev)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	अगर (core->io_addr)
		iounmap(core->io_addr);
	अगर (core->io_wrap)
		iounmap(core->io_wrap);
	kमुक्त(core);
पूर्ण

अटल bool bcma_is_core_needed_early(u16 core_id)
अणु
	चयन (core_id) अणु
	हाल BCMA_CORE_NS_न_अंकD:
	हाल BCMA_CORE_NS_QSPI:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा device_node *bcma_of_find_child_device(काष्ठा device *parent,
						     काष्ठा bcma_device *core)
अणु
	काष्ठा device_node *node;
	u64 size;
	स्थिर __be32 *reg;

	अगर (!parent->of_node)
		वापस शून्य;

	क्रम_each_child_of_node(parent->of_node, node) अणु
		reg = of_get_address(node, 0, &size, शून्य);
		अगर (!reg)
			जारी;
		अगर (of_translate_address(node, reg) == core->addr)
			वापस node;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक bcma_of_irq_parse(काष्ठा device *parent,
			     काष्ठा bcma_device *core,
			     काष्ठा of_phandle_args *out_irq, पूर्णांक num)
अणु
	__be32 laddr[1];
	पूर्णांक rc;

	अगर (core->dev.of_node) अणु
		rc = of_irq_parse_one(core->dev.of_node, num, out_irq);
		अगर (!rc)
			वापस rc;
	पूर्ण

	out_irq->np = parent->of_node;
	out_irq->args_count = 1;
	out_irq->args[0] = num;

	laddr[0] = cpu_to_be32(core->addr);
	वापस of_irq_parse_raw(laddr, out_irq);
पूर्ण

अटल अचिन्हित पूर्णांक bcma_of_get_irq(काष्ठा device *parent,
				    काष्ठा bcma_device *core, पूर्णांक num)
अणु
	काष्ठा of_phandle_args out_irq;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_OF_IRQ) || !parent->of_node)
		वापस 0;

	ret = bcma_of_irq_parse(parent, core, &out_irq, num);
	अगर (ret) अणु
		bcma_debug(core->bus, "bcma_of_get_irq() failed with rc=%d\n",
			   ret);
		वापस 0;
	पूर्ण

	वापस irq_create_of_mapping(&out_irq);
पूर्ण

अटल व्योम bcma_of_fill_device(काष्ठा device *parent,
				काष्ठा bcma_device *core)
अणु
	काष्ठा device_node *node;

	node = bcma_of_find_child_device(parent, core);
	अगर (node)
		core->dev.of_node = node;

	core->irq = bcma_of_get_irq(parent, core, 0);

	of_dma_configure(&core->dev, node, false);
पूर्ण

अचिन्हित पूर्णांक bcma_core_irq(काष्ठा bcma_device *core, पूर्णांक num)
अणु
	काष्ठा bcma_bus *bus = core->bus;
	अचिन्हित पूर्णांक mips_irq;

	चयन (bus->hosttype) अणु
	हाल BCMA_HOSTTYPE_PCI:
		वापस bus->host_pci->irq;
	हाल BCMA_HOSTTYPE_SOC:
		अगर (bus->drv_mips.core && num == 0) अणु
			mips_irq = bcma_core_mips_irq(core);
			वापस mips_irq <= 4 ? mips_irq + 2 : 0;
		पूर्ण
		अगर (bus->dev)
			वापस bcma_of_get_irq(bus->dev, core, num);
		वापस 0;
	हाल BCMA_HOSTTYPE_SDIO:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(bcma_core_irq);

व्योम bcma_prepare_core(काष्ठा bcma_bus *bus, काष्ठा bcma_device *core)
अणु
	core->dev.release = bcma_release_core_dev;
	core->dev.bus = &bcma_bus_type;
	dev_set_name(&core->dev, "bcma%d:%d", bus->num, core->core_index);
	core->dev.parent = bus->dev;
	अगर (bus->dev)
		bcma_of_fill_device(bus->dev, core);

	चयन (bus->hosttype) अणु
	हाल BCMA_HOSTTYPE_PCI:
		core->dma_dev = bus->dev;
		core->irq = bus->host_pci->irq;
		अवरोध;
	हाल BCMA_HOSTTYPE_SOC:
		अगर (IS_ENABLED(CONFIG_OF) && bus->dev) अणु
			core->dma_dev = bus->dev;
		पूर्ण अन्यथा अणु
			core->dev.dma_mask = &core->dev.coherent_dma_mask;
			core->dma_dev = &core->dev;
		पूर्ण
		अवरोध;
	हाल BCMA_HOSTTYPE_SDIO:
		अवरोध;
	पूर्ण
पूर्ण

व्योम bcma_init_bus(काष्ठा bcma_bus *bus)
अणु
	mutex_lock(&bcma_buses_mutex);
	bus->num = bcma_bus_next_num++;
	mutex_unlock(&bcma_buses_mutex);

	INIT_LIST_HEAD(&bus->cores);
	bus->nr_cores = 0;

	bcma_detect_chip(bus);
पूर्ण

अटल व्योम bcma_रेजिस्टर_core(काष्ठा bcma_bus *bus, काष्ठा bcma_device *core)
अणु
	पूर्णांक err;

	err = device_रेजिस्टर(&core->dev);
	अगर (err) अणु
		bcma_err(bus, "Could not register dev for core 0x%03X\n",
			 core->id.id);
		put_device(&core->dev);
		वापस;
	पूर्ण
	core->dev_रेजिस्टरed = true;
पूर्ण

अटल पूर्णांक bcma_रेजिस्टर_devices(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_device *core;
	पूर्णांक err;

	list_क्रम_each_entry(core, &bus->cores, list) अणु
		/* We support that cores ourself */
		चयन (core->id.id) अणु
		हाल BCMA_CORE_4706_CHIPCOMMON:
		हाल BCMA_CORE_CHIPCOMMON:
		हाल BCMA_CORE_NS_CHIPCOMMON_B:
		हाल BCMA_CORE_PCI:
		हाल BCMA_CORE_PCIE:
		हाल BCMA_CORE_PCIE2:
		हाल BCMA_CORE_MIPS_74K:
		हाल BCMA_CORE_4706_MAC_GBIT_COMMON:
			जारी;
		पूर्ण

		/* Early cores were alपढ़ोy रेजिस्टरed */
		अगर (bcma_is_core_needed_early(core->id.id))
			जारी;

		/* Only first GMAC core on BCM4706 is connected and working */
		अगर (core->id.id == BCMA_CORE_4706_MAC_GBIT &&
		    core->core_unit > 0)
			जारी;

		bcma_रेजिस्टर_core(bus, core);
	पूर्ण

#अगर_घोषित CONFIG_BCMA_PFLASH
	अगर (bus->drv_cc.pflash.present) अणु
		err = platक्रमm_device_रेजिस्टर(&bcma_pflash_dev);
		अगर (err)
			bcma_err(bus, "Error registering parallel flash\n");
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_SFLASH
	अगर (bus->drv_cc.sflash.present) अणु
		err = platक्रमm_device_रेजिस्टर(&bcma_sflash_dev);
		अगर (err)
			bcma_err(bus, "Error registering serial flash\n");
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_NFLASH
	अगर (bus->drv_cc.nflash.present) अणु
		err = platक्रमm_device_रेजिस्टर(&bcma_nflash_dev);
		अगर (err)
			bcma_err(bus, "Error registering NAND flash\n");
	पूर्ण
#पूर्ण_अगर
	err = bcma_gpio_init(&bus->drv_cc);
	अगर (err == -ENOTSUPP)
		bcma_debug(bus, "GPIO driver not activated\n");
	अन्यथा अगर (err)
		bcma_err(bus, "Error registering GPIO driver: %i\n", err);

	अगर (bus->hosttype == BCMA_HOSTTYPE_SOC) अणु
		err = bcma_chipco_watchकरोg_रेजिस्टर(&bus->drv_cc);
		अगर (err)
			bcma_err(bus, "Error registering watchdog driver\n");
	पूर्ण

	वापस 0;
पूर्ण

व्योम bcma_unरेजिस्टर_cores(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_device *core, *पंचांगp;

	list_क्रम_each_entry_safe(core, पंचांगp, &bus->cores, list) अणु
		अगर (!core->dev_रेजिस्टरed)
			जारी;
		list_del(&core->list);
		device_unरेजिस्टर(&core->dev);
	पूर्ण
	अगर (bus->hosttype == BCMA_HOSTTYPE_SOC)
		platक्रमm_device_unरेजिस्टर(bus->drv_cc.watchकरोg);

	/* Now noone uses पूर्णांकernally-handled cores, we can मुक्त them */
	list_क्रम_each_entry_safe(core, पंचांगp, &bus->cores, list) अणु
		list_del(&core->list);
		kमुक्त(core);
	पूर्ण
पूर्ण

पूर्णांक bcma_bus_रेजिस्टर(काष्ठा bcma_bus *bus)
अणु
	पूर्णांक err;
	काष्ठा bcma_device *core;

	/* Scan क्रम devices (cores) */
	err = bcma_bus_scan(bus);
	अगर (err) अणु
		bcma_err(bus, "Failed to scan: %d\n", err);
		वापस err;
	पूर्ण

	/* Early init CC core */
	core = bcma_find_core(bus, bcma_cc_core_id(bus));
	अगर (core) अणु
		bus->drv_cc.core = core;
		bcma_core_chipcommon_early_init(&bus->drv_cc);
	पूर्ण

	/* Early init PCIE core */
	core = bcma_find_core(bus, BCMA_CORE_PCIE);
	अगर (core) अणु
		bus->drv_pci[0].core = core;
		bcma_core_pci_early_init(&bus->drv_pci[0]);
	पूर्ण

	अगर (bus->dev)
		of_platक्रमm_शेष_populate(bus->dev->of_node, शून्य, bus->dev);

	/* Cores providing flash access go beक्रमe SPROM init */
	list_क्रम_each_entry(core, &bus->cores, list) अणु
		अगर (bcma_is_core_needed_early(core->id.id))
			bcma_रेजिस्टर_core(bus, core);
	पूर्ण

	/* Try to get SPROM */
	err = bcma_sprom_get(bus);
	अगर (err == -ENOENT) अणु
		bcma_err(bus, "No SPROM available\n");
	पूर्ण अन्यथा अगर (err)
		bcma_err(bus, "Failed to get SPROM: %d\n", err);

	/* Init CC core */
	core = bcma_find_core(bus, bcma_cc_core_id(bus));
	अगर (core) अणु
		bus->drv_cc.core = core;
		bcma_core_chipcommon_init(&bus->drv_cc);
	पूर्ण

	/* Init CC core */
	core = bcma_find_core(bus, BCMA_CORE_NS_CHIPCOMMON_B);
	अगर (core) अणु
		bus->drv_cc_b.core = core;
		bcma_core_chipcommon_b_init(&bus->drv_cc_b);
	पूर्ण

	/* Init MIPS core */
	core = bcma_find_core(bus, BCMA_CORE_MIPS_74K);
	अगर (core) अणु
		bus->drv_mips.core = core;
		bcma_core_mips_init(&bus->drv_mips);
	पूर्ण

	/* Init PCIE core */
	core = bcma_find_core_unit(bus, BCMA_CORE_PCIE, 0);
	अगर (core) अणु
		bus->drv_pci[0].core = core;
		bcma_core_pci_init(&bus->drv_pci[0]);
	पूर्ण

	/* Init PCIE core */
	core = bcma_find_core_unit(bus, BCMA_CORE_PCIE, 1);
	अगर (core) अणु
		bus->drv_pci[1].core = core;
		bcma_core_pci_init(&bus->drv_pci[1]);
	पूर्ण

	/* Init PCIe Gen 2 core */
	core = bcma_find_core_unit(bus, BCMA_CORE_PCIE2, 0);
	अगर (core) अणु
		bus->drv_pcie2.core = core;
		bcma_core_pcie2_init(&bus->drv_pcie2);
	पूर्ण

	/* Init GBIT MAC COMMON core */
	core = bcma_find_core(bus, BCMA_CORE_4706_MAC_GBIT_COMMON);
	अगर (core) अणु
		bus->drv_gmac_cmn.core = core;
		bcma_core_gmac_cmn_init(&bus->drv_gmac_cmn);
	पूर्ण

	/* Register found cores */
	bcma_रेजिस्टर_devices(bus);

	bcma_info(bus, "Bus registered\n");

	वापस 0;
पूर्ण

व्योम bcma_bus_unरेजिस्टर(काष्ठा bcma_bus *bus)
अणु
	पूर्णांक err;

	err = bcma_gpio_unरेजिस्टर(&bus->drv_cc);
	अगर (err == -EBUSY)
		bcma_err(bus, "Some GPIOs are still in use.\n");
	अन्यथा अगर (err)
		bcma_err(bus, "Can not unregister GPIO driver: %i\n", err);

	bcma_core_chipcommon_b_मुक्त(&bus->drv_cc_b);

	bcma_unरेजिस्टर_cores(bus);
पूर्ण

/*
 * This is a special version of bus registration function deचिन्हित क्रम SoCs.
 * It scans bus and perक्रमms basic initialization of मुख्य cores only.
 * Please note it requires memory allocation, however it won't try to sleep.
 */
पूर्णांक __init bcma_bus_early_रेजिस्टर(काष्ठा bcma_bus *bus)
अणु
	पूर्णांक err;
	काष्ठा bcma_device *core;

	/* Scan क्रम devices (cores) */
	err = bcma_bus_scan(bus);
	अगर (err) अणु
		bcma_err(bus, "Failed to scan bus: %d\n", err);
		वापस -1;
	पूर्ण

	/* Early init CC core */
	core = bcma_find_core(bus, bcma_cc_core_id(bus));
	अगर (core) अणु
		bus->drv_cc.core = core;
		bcma_core_chipcommon_early_init(&bus->drv_cc);
	पूर्ण

	/* Early init MIPS core */
	core = bcma_find_core(bus, BCMA_CORE_MIPS_74K);
	अगर (core) अणु
		bus->drv_mips.core = core;
		bcma_core_mips_early_init(&bus->drv_mips);
	पूर्ण

	bcma_info(bus, "Early bus registered\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक bcma_bus_suspend(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_device *core;

	list_क्रम_each_entry(core, &bus->cores, list) अणु
		काष्ठा device_driver *drv = core->dev.driver;
		अगर (drv) अणु
			काष्ठा bcma_driver *adrv = container_of(drv, काष्ठा bcma_driver, drv);
			अगर (adrv->suspend)
				adrv->suspend(core);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bcma_bus_resume(काष्ठा bcma_bus *bus)
अणु
	काष्ठा bcma_device *core;

	/* Init CC core */
	अगर (bus->drv_cc.core) अणु
		bus->drv_cc.setup_करोne = false;
		bcma_core_chipcommon_init(&bus->drv_cc);
	पूर्ण

	list_क्रम_each_entry(core, &bus->cores, list) अणु
		काष्ठा device_driver *drv = core->dev.driver;
		अगर (drv) अणु
			काष्ठा bcma_driver *adrv = container_of(drv, काष्ठा bcma_driver, drv);
			अगर (adrv->resume)
				adrv->resume(core);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक __bcma_driver_रेजिस्टर(काष्ठा bcma_driver *drv, काष्ठा module *owner)
अणु
	drv->drv.name = drv->name;
	drv->drv.bus = &bcma_bus_type;
	drv->drv.owner = owner;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(__bcma_driver_रेजिस्टर);

व्योम bcma_driver_unरेजिस्टर(काष्ठा bcma_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_driver_unरेजिस्टर);

अटल पूर्णांक bcma_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	काष्ठा bcma_driver *adrv = container_of(drv, काष्ठा bcma_driver, drv);
	स्थिर काष्ठा bcma_device_id *cid = &core->id;
	स्थिर काष्ठा bcma_device_id *did;

	क्रम (did = adrv->id_table; did->manuf || did->id || did->rev; did++) अणु
	    अगर ((did->manuf == cid->manuf || did->manuf == BCMA_ANY_MANUF) &&
		(did->id == cid->id || did->id == BCMA_ANY_ID) &&
		(did->rev == cid->rev || did->rev == BCMA_ANY_REV) &&
		(did->class == cid->class || did->class == BCMA_ANY_CLASS))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcma_device_probe(काष्ठा device *dev)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	काष्ठा bcma_driver *adrv = container_of(dev->driver, काष्ठा bcma_driver,
					       drv);
	पूर्णांक err = 0;

	get_device(dev);
	अगर (adrv->probe)
		err = adrv->probe(core);
	अगर (err)
		put_device(dev);

	वापस err;
पूर्ण

अटल पूर्णांक bcma_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);
	काष्ठा bcma_driver *adrv = container_of(dev->driver, काष्ठा bcma_driver,
					       drv);

	अगर (adrv->हटाओ)
		adrv->हटाओ(core);
	put_device(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bcma_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा bcma_device *core = container_of(dev, काष्ठा bcma_device, dev);

	वापस add_uevent_var(env,
			      "MODALIAS=bcma:m%04Xid%04Xrev%02Xcl%02X",
			      core->id.manuf, core->id.id,
			      core->id.rev, core->id.class);
पूर्ण

अटल अचिन्हित पूर्णांक bcma_bus_रेजिस्टरed;

/*
 * If built-in, bus has to be रेजिस्टरed early, beक्रमe any driver calls
 * bcma_driver_रेजिस्टर.
 * Otherwise रेजिस्टरing driver would trigger BUG in driver_रेजिस्टर.
 */
अटल पूर्णांक __init bcma_init_bus_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	अगर (bcma_bus_रेजिस्टरed)
		वापस 0;

	err = bus_रेजिस्टर(&bcma_bus_type);
	अगर (!err)
		bcma_bus_रेजिस्टरed = 1;

	वापस err;
पूर्ण
#अगर_अघोषित MODULE
fs_initcall(bcma_init_bus_रेजिस्टर);
#पूर्ण_अगर

/* Main initialization has to be करोne with SPI/mtd/न_अंकD/SPROM available */
अटल पूर्णांक __init bcma_modinit(व्योम)
अणु
	पूर्णांक err;

	err = bcma_init_bus_रेजिस्टर();
	अगर (err)
		वापस err;

	err = bcma_host_soc_रेजिस्टर_driver();
	अगर (err) अणु
		pr_err("SoC host initialization failed\n");
		err = 0;
	पूर्ण
#अगर_घोषित CONFIG_BCMA_HOST_PCI
	err = bcma_host_pci_init();
	अगर (err) अणु
		pr_err("PCI host initialization failed\n");
		err = 0;
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण
module_init(bcma_modinit);

अटल व्योम __निकास bcma_modनिकास(व्योम)
अणु
#अगर_घोषित CONFIG_BCMA_HOST_PCI
	bcma_host_pci_निकास();
#पूर्ण_अगर
	bcma_host_soc_unरेजिस्टर_driver();
	bus_unरेजिस्टर(&bcma_bus_type);
पूर्ण
module_निकास(bcma_modनिकास)
