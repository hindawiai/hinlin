<शैली गुरु>
/*
 * support क्रम probing IDE PCI devices in the PCI bus order
 *
 * Copyright (c) 1998-2000  Andre Hedrick <andre@linux-ide.org>
 * Copyright (c) 1995-1998  Mark Lord
 *
 * May be copied or modअगरied under the terms of the GNU General Public License
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ide.h>

/*
 *	Module पूर्णांकerfaces
 */

अटल पूर्णांक pre_init = 1;		/* Beक्रमe first ordered IDE scan */
अटल LIST_HEAD(ide_pci_drivers);

/*
 *	__ide_pci_रेजिस्टर_driver	-	attach IDE driver
 *	@driver: pci driver
 *	@module: owner module of the driver
 *
 *	Registers a driver with the IDE layer. The IDE layer arranges that
 *	boot समय setup is करोne in the expected device order and then
 *	hands the controllers off to the core PCI code to करो the rest of
 *	the work.
 *
 *	Returns are the same as क्रम pci_रेजिस्टर_driver
 */

पूर्णांक __ide_pci_रेजिस्टर_driver(काष्ठा pci_driver *driver, काष्ठा module *module,
			      स्थिर अक्षर *mod_name)
अणु
	अगर (!pre_init)
		वापस __pci_रेजिस्टर_driver(driver, module, mod_name);
	driver->driver.owner = module;
	list_add_tail(&driver->node, &ide_pci_drivers);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__ide_pci_रेजिस्टर_driver);

/**
 *	ide_scan_pcidev		-	find an IDE driver क्रम a device
 *	@dev: PCI device to check
 *
 *	Look क्रम an IDE driver to handle the device we are considering.
 *	This is only used during boot up to get the ordering correct. After
 *	boot up the pci layer takes over the job.
 */

अटल पूर्णांक __init ide_scan_pcidev(काष्ठा pci_dev *dev)
अणु
	काष्ठा list_head *l;
	काष्ठा pci_driver *d;
	पूर्णांक ret;

	list_क्रम_each(l, &ide_pci_drivers) अणु
		d = list_entry(l, काष्ठा pci_driver, node);
		अगर (d->id_table) अणु
			स्थिर काष्ठा pci_device_id *id =
				pci_match_id(d->id_table, dev);

			अगर (id != शून्य) अणु
				pci_assign_irq(dev);
				ret = d->probe(dev, id);
				अगर (ret >= 0) अणु
					dev->driver = d;
					pci_dev_get(dev);
					वापस 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	ide_scan_pcibus		-	perक्रमm the initial IDE driver scan
 *
 *	Perक्रमm the initial bus rather than driver ordered scan of the
 *	PCI drivers. After this all IDE pci handling becomes standard
 *	module ordering not traditionally ordered.
 */

अटल पूर्णांक __init ide_scan_pcibus(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	काष्ठा pci_driver *d, *पंचांगp;

	pre_init = 0;
	क्रम_each_pci_dev(dev)
		ide_scan_pcidev(dev);

	/*
	 *	Hand the drivers over to the PCI layer now we
	 *	are post init.
	 */

	list_क्रम_each_entry_safe(d, पंचांगp, &ide_pci_drivers, node) अणु
		list_del(&d->node);
		अगर (__pci_रेजिस्टर_driver(d, d->driver.owner,
					  d->driver.mod_name))
			prपूर्णांकk(KERN_ERR "%s: failed to register %s driver\n",
					__func__, d->driver.mod_name);
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(ide_scan_pcibus);
