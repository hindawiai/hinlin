<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Bus & driver management routines क्रम devices within
 * a MacIO ASIC. Interface to new driver model mostly
 * stolen from the PCI version.
 * 
 *  Copyright (C) 2005 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 * TODO:
 * 
 *  - Don't probe below media bay by शेष, but instead provide
 *    some hooks क्रम media bay to dynamically add/हटाओ it's own
 *    sub-devices.
 */
 
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/prom.h>

#अघोषित DEBUG

#घोषणा MAX_NODE_NAME_SIZE (20 - 12)

अटल काष्ठा macio_chip      *macio_on_hold;

अटल पूर्णांक macio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv) 
अणु
	स्थिर काष्ठा of_device_id * matches = drv->of_match_table;

	अगर (!matches) 
		वापस 0;

	वापस of_match_device(matches, dev) != शून्य;
पूर्ण

काष्ठा macio_dev *macio_dev_get(काष्ठा macio_dev *dev)
अणु
	काष्ठा device *पंचांगp;

	अगर (!dev)
		वापस शून्य;
	पंचांगp = get_device(&dev->ofdev.dev);
	अगर (पंचांगp)
		वापस to_macio_device(पंचांगp);
	अन्यथा
		वापस शून्य;
पूर्ण

व्योम macio_dev_put(काष्ठा macio_dev *dev)
अणु
	अगर (dev)
		put_device(&dev->ofdev.dev);
पूर्ण


अटल पूर्णांक macio_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = -ENODEV;
	काष्ठा macio_driver *drv;
	काष्ठा macio_dev *macio_dev;
	स्थिर काष्ठा of_device_id *match;

	drv = to_macio_driver(dev->driver);
	macio_dev = to_macio_device(dev);

	अगर (!drv->probe)
		वापस error;

	macio_dev_get(macio_dev);

	match = of_match_device(drv->driver.of_match_table, dev);
	अगर (match)
		error = drv->probe(macio_dev, match);
	अगर (error)
		macio_dev_put(macio_dev);

	वापस error;
पूर्ण

अटल पूर्णांक macio_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा macio_dev * macio_dev = to_macio_device(dev);
	काष्ठा macio_driver * drv = to_macio_driver(dev->driver);

	अगर (dev->driver && drv->हटाओ)
		drv->हटाओ(macio_dev);
	macio_dev_put(macio_dev);

	वापस 0;
पूर्ण

अटल व्योम macio_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा macio_dev * macio_dev = to_macio_device(dev);
	काष्ठा macio_driver * drv = to_macio_driver(dev->driver);

	अगर (dev->driver && drv->shutकरोwn)
		drv->shutकरोwn(macio_dev);
पूर्ण

अटल पूर्णांक macio_device_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा macio_dev * macio_dev = to_macio_device(dev);
	काष्ठा macio_driver * drv = to_macio_driver(dev->driver);

	अगर (dev->driver && drv->suspend)
		वापस drv->suspend(macio_dev, state);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_device_resume(काष्ठा device * dev)
अणु
	काष्ठा macio_dev * macio_dev = to_macio_device(dev);
	काष्ठा macio_driver * drv = to_macio_driver(dev->driver);

	अगर (dev->driver && drv->resume)
		वापस drv->resume(macio_dev);
	वापस 0;
पूर्ण

बाह्य स्थिर काष्ठा attribute_group *macio_dev_groups[];

काष्ठा bus_type macio_bus_type = अणु
       .name	= "macio",
       .match	= macio_bus_match,
       .uevent = of_device_uevent_modalias,
       .probe	= macio_device_probe,
       .हटाओ	= macio_device_हटाओ,
       .shutकरोwn = macio_device_shutकरोwn,
       .suspend	= macio_device_suspend,
       .resume	= macio_device_resume,
       .dev_groups = macio_dev_groups,
पूर्ण;

अटल पूर्णांक __init macio_bus_driver_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&macio_bus_type);
पूर्ण

postcore_initcall(macio_bus_driver_init);


/**
 * macio_release_dev - मुक्त a macio device काष्ठाure when all users of it are
 * finished.
 * @dev: device that's been disconnected
 *
 * Will be called only by the device core when all users of this macio device
 * are करोne. This currently means never as we करोn't hot हटाओ any macio
 * device yet, though that will happen with mediabay based devices in a later
 * implementation.
 */
अटल व्योम macio_release_dev(काष्ठा device *dev)
अणु
	काष्ठा macio_dev *mdev;

        mdev = to_macio_device(dev);
	kमुक्त(mdev);
पूर्ण

/**
 * macio_resource_quirks - tweak or skip some resources क्रम a device
 * @np: poपूर्णांकer to the device node
 * @res: resulting resource
 * @index: index of resource in node
 *
 * If this routine वापसs non-null, then the resource is completely
 * skipped.
 */
अटल पूर्णांक macio_resource_quirks(काष्ठा device_node *np, काष्ठा resource *res,
				 पूर्णांक index)
अणु
	/* Only quirks क्रम memory resources क्रम now */
	अगर ((res->flags & IORESOURCE_MEM) == 0)
		वापस 0;

	/* Gअक्रम Central has too large resource 0 on some machines */
	अगर (index == 0 && of_node_name_eq(np, "gc"))
		res->end = res->start + 0x1ffff;

	/* Airport has bogus resource 2 */
	अगर (index >= 2 && of_node_name_eq(np, "radio"))
		वापस 1;

#अगर_अघोषित CONFIG_PPC64
	/* DBDMAs may have bogus sizes */
	अगर ((res->start & 0x0001f000) == 0x00008000)
		res->end = res->start + 0xff;
#पूर्ण_अगर /* CONFIG_PPC64 */

	/* ESCC parent eats child resources. We could have added a
	 * level of hierarchy, but I करोn't really feel the need
	 * क्रम it
	 */
	अगर (of_node_name_eq(np, "escc"))
		वापस 1;

	/* ESCC has bogus resources >= 3 */
	अगर (index >= 3 && (of_node_name_eq(np, "ch-a") ||
			   of_node_name_eq(np, "ch-b")))
		वापस 1;

	/* Media bay has too many resources, keep only first one */
	अगर (index > 0 && of_node_name_eq(np, "media-bay"))
		वापस 1;

	/* Some older IDE resources have bogus sizes */
	अगर (of_node_name_eq(np, "IDE") || of_node_name_eq(np, "ATA") ||
	    of_node_is_type(np, "ide") || of_node_is_type(np, "ata")) अणु
		अगर (index == 0 && (res->end - res->start) > 0xfff)
			res->end = res->start + 0xfff;
		अगर (index == 1 && (res->end - res->start) > 0xff)
			res->end = res->start + 0xff;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम macio_create_fixup_irq(काष्ठा macio_dev *dev, पूर्णांक index,
				   अचिन्हित पूर्णांक line)
अणु
	अचिन्हित पूर्णांक irq;

	irq = irq_create_mapping(शून्य, line);
	अगर (!irq) अणु
		dev->पूर्णांकerrupt[index].start = irq;
		dev->पूर्णांकerrupt[index].flags = IORESOURCE_IRQ;
		dev->पूर्णांकerrupt[index].name = dev_name(&dev->ofdev.dev);
	पूर्ण
	अगर (dev->n_पूर्णांकerrupts <= index)
		dev->n_पूर्णांकerrupts = index + 1;
पूर्ण

अटल व्योम macio_add_missing_resources(काष्ठा macio_dev *dev)
अणु
	काष्ठा device_node *np = dev->ofdev.dev.of_node;
	अचिन्हित पूर्णांक irq_base;

	/* Gatwick has some missing पूर्णांकerrupts on child nodes */
	अगर (dev->bus->chip->type != macio_gatwick)
		वापस;

	/* irq_base is always 64 on gatwick. I have no cleaner way to get
	 * that value from here at this poपूर्णांक
	 */
	irq_base = 64;

	/* Fix SCC */
	अगर (of_node_name_eq(np, "ch-a")) अणु
		macio_create_fixup_irq(dev, 0, 15 + irq_base);
		macio_create_fixup_irq(dev, 1,  4 + irq_base);
		macio_create_fixup_irq(dev, 2,  5 + irq_base);
		prपूर्णांकk(KERN_INFO "macio: fixed SCC irqs on gatwick\n");
	पूर्ण

	/* Fix media-bay */
	अगर (of_node_name_eq(np, "media-bay")) अणु
		macio_create_fixup_irq(dev, 0, 29 + irq_base);
		prपूर्णांकk(KERN_INFO "macio: fixed media-bay irq on gatwick\n");
	पूर्ण

	/* Fix left media bay childs */
	अगर (dev->media_bay != शून्य && of_node_name_eq(np, "floppy")) अणु
		macio_create_fixup_irq(dev, 0, 19 + irq_base);
		macio_create_fixup_irq(dev, 1,  1 + irq_base);
		prपूर्णांकk(KERN_INFO "macio: fixed left floppy irqs\n");
	पूर्ण
	अगर (dev->media_bay != शून्य && of_node_name_eq(np, "ata4")) अणु
		macio_create_fixup_irq(dev, 0, 14 + irq_base);
		macio_create_fixup_irq(dev, 0,  3 + irq_base);
		prपूर्णांकk(KERN_INFO "macio: fixed left ide irqs\n");
	पूर्ण
पूर्ण

अटल व्योम macio_setup_पूर्णांकerrupts(काष्ठा macio_dev *dev)
अणु
	काष्ठा device_node *np = dev->ofdev.dev.of_node;
	अचिन्हित पूर्णांक irq;
	पूर्णांक i = 0, j = 0;

	क्रम (;;) अणु
		काष्ठा resource *res;

		अगर (j >= MACIO_DEV_COUNT_IRQS)
			अवरोध;
		res = &dev->पूर्णांकerrupt[j];
		irq = irq_of_parse_and_map(np, i++);
		अगर (!irq)
			अवरोध;
		res->start = irq;
		res->flags = IORESOURCE_IRQ;
		res->name = dev_name(&dev->ofdev.dev);
		अगर (macio_resource_quirks(np, res, i - 1)) अणु
			स_रखो(res, 0, माप(काष्ठा resource));
			जारी;
		पूर्ण अन्यथा
			j++;
	पूर्ण
	dev->n_पूर्णांकerrupts = j;
पूर्ण

अटल व्योम macio_setup_resources(काष्ठा macio_dev *dev,
				  काष्ठा resource *parent_res)
अणु
	काष्ठा device_node *np = dev->ofdev.dev.of_node;
	काष्ठा resource r;
	पूर्णांक index;

	क्रम (index = 0; of_address_to_resource(np, index, &r) == 0; index++) अणु
		काष्ठा resource *res;
		अगर (index >= MACIO_DEV_COUNT_RESOURCES)
			अवरोध;
		res = &dev->resource[index];
		*res = r;
		res->name = dev_name(&dev->ofdev.dev);

		अगर (macio_resource_quirks(np, res, index)) अणु
			स_रखो(res, 0, माप(काष्ठा resource));
			जारी;
		पूर्ण
		/* Currently, we consider failure as harmless, this may
		 * change in the future, once I've found all the device
		 * tree bugs in older machines & worked around them
		 */
		अगर (insert_resource(parent_res, res)) अणु
			prपूर्णांकk(KERN_WARNING "Can't request resource "
			       "%d for MacIO device %s\n",
			       index, dev_name(&dev->ofdev.dev));
		पूर्ण
	पूर्ण
	dev->n_resources = index;
पूर्ण

/**
 * macio_add_one_device - Add one device from OF node to the device tree
 * @chip: poपूर्णांकer to the macio_chip holding the device
 * @np: poपूर्णांकer to the device node in the OF tree
 * @in_bay: set to 1 अगर device is part of a media-bay
 *
 * When media-bay is changed to hotswap drivers, this function will
 * be exposed to the bay driver some way...
 */
अटल काष्ठा macio_dev * macio_add_one_device(काष्ठा macio_chip *chip,
					       काष्ठा device *parent,
					       काष्ठा device_node *np,
					       काष्ठा macio_dev *in_bay,
					       काष्ठा resource *parent_res)
अणु
	अक्षर name[MAX_NODE_NAME_SIZE + 1];
	काष्ठा macio_dev *dev;
	स्थिर u32 *reg;

	अगर (np == शून्य)
		वापस शून्य;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->bus = &chip->lbus;
	dev->media_bay = in_bay;
	dev->ofdev.dev.of_node = np;
	dev->ofdev.archdata.dma_mask = 0xffffffffUL;
	dev->ofdev.dev.dma_mask = &dev->ofdev.archdata.dma_mask;
	dev->ofdev.dev.coherent_dma_mask = dev->ofdev.archdata.dma_mask;
	dev->ofdev.dev.parent = parent;
	dev->ofdev.dev.bus = &macio_bus_type;
	dev->ofdev.dev.release = macio_release_dev;
	dev->ofdev.dev.dma_parms = &dev->dma_parms;

	/* Standard DMA paremeters */
	dma_set_max_seg_size(&dev->ofdev.dev, 65536);
	dma_set_seg_boundary(&dev->ofdev.dev, 0xffffffff);

#अगर defined(CONFIG_PCI) && defined(CONFIG_DMA_OPS)
	/* Set the DMA ops to the ones from the PCI device, this could be
	 * fishy अगर we didn't know that on PowerMac it's always direct ops
	 * or iommu ops that will work fine
	 *
	 * To get all the fields, copy all archdata
	 */
	dev->ofdev.dev.archdata = chip->lbus.pdev->dev.archdata;
	dev->ofdev.dev.dma_ops = chip->lbus.pdev->dev.dma_ops;
#पूर्ण_अगर /* CONFIG_PCI && CONFIG_DMA_OPS */

#अगर_घोषित DEBUG
	prपूर्णांकk("preparing mdev @%p, ofdev @%p, dev @%p, kobj @%p\n",
	       dev, &dev->ofdev, &dev->ofdev.dev, &dev->ofdev.dev.kobj);
#पूर्ण_अगर

	/* MacIO itself has a dअगरferent reg, we use it's PCI base */
	snम_लिखो(name, माप(name), "%pOFn", np);
	अगर (np == chip->of_node) अणु
		dev_set_name(&dev->ofdev.dev, "%1d.%08x:%.*s",
			     chip->lbus.index,
#अगर_घोषित CONFIG_PCI
			(अचिन्हित पूर्णांक)pci_resource_start(chip->lbus.pdev, 0),
#अन्यथा
			0, /* NuBus may want to करो something better here */
#पूर्ण_अगर
			MAX_NODE_NAME_SIZE, name);
	पूर्ण अन्यथा अणु
		reg = of_get_property(np, "reg", शून्य);
		dev_set_name(&dev->ofdev.dev, "%1d.%08x:%.*s",
			     chip->lbus.index,
			     reg ? *reg : 0, MAX_NODE_NAME_SIZE, name);
	पूर्ण

	/* Setup पूर्णांकerrupts & resources */
	macio_setup_पूर्णांकerrupts(dev);
	macio_setup_resources(dev, parent_res);
	macio_add_missing_resources(dev);

	/* Register with core */
	अगर (of_device_रेजिस्टर(&dev->ofdev) != 0) अणु
		prपूर्णांकk(KERN_DEBUG"macio: device registration error for %s!\n",
		       dev_name(&dev->ofdev.dev));
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण

अटल पूर्णांक macio_skip_device(काष्ठा device_node *np)
अणु
	वापस of_node_name_prefix(np, "battery") ||
	       of_node_name_prefix(np, "escc-legacy");
पूर्ण

/**
 * macio_pci_add_devices - Adds sub-devices of mac-io to the device tree
 * @chip: poपूर्णांकer to the macio_chip holding the devices
 * 
 * This function will करो the job of extracting devices from the
 * Open Firmware device tree, build macio_dev काष्ठाures and add
 * them to the Linux device tree.
 * 
 * For now, childs of media-bay are added now as well. This will
 * change rsn though.
 */
अटल व्योम macio_pci_add_devices(काष्ठा macio_chip *chip)
अणु
	काष्ठा device_node *np, *pnode;
	काष्ठा macio_dev *rdev, *mdev, *mbdev = शून्य, *sdev = शून्य;
	काष्ठा device *parent = शून्य;
	काष्ठा resource *root_res = &iomem_resource;
	
	/* Add a node क्रम the macio bus itself */
#अगर_घोषित CONFIG_PCI
	अगर (chip->lbus.pdev) अणु
		parent = &chip->lbus.pdev->dev;
		root_res = &chip->lbus.pdev->resource[0];
	पूर्ण
#पूर्ण_अगर
	pnode = of_node_get(chip->of_node);
	अगर (pnode == शून्य)
		वापस;

	/* Add macio itself to hierarchy */
	rdev = macio_add_one_device(chip, parent, pnode, शून्य, root_res);
	अगर (rdev == शून्य)
		वापस;
	root_res = &rdev->resource[0];

	/* First scan 1st level */
	क्रम (np = शून्य; (np = of_get_next_child(pnode, np)) != शून्य;) अणु
		अगर (macio_skip_device(np))
			जारी;
		of_node_get(np);
		mdev = macio_add_one_device(chip, &rdev->ofdev.dev, np, शून्य,
					    root_res);
		अगर (mdev == शून्य)
			of_node_put(np);
		अन्यथा अगर (of_node_name_prefix(np, "media-bay"))
			mbdev = mdev;
		अन्यथा अगर (of_node_name_prefix(np, "escc"))
			sdev = mdev;
	पूर्ण

	/* Add media bay devices अगर any */
	अगर (mbdev) अणु
		pnode = mbdev->ofdev.dev.of_node;
		क्रम (np = शून्य; (np = of_get_next_child(pnode, np)) != शून्य;) अणु
			अगर (macio_skip_device(np))
				जारी;
			of_node_get(np);
			अगर (macio_add_one_device(chip, &mbdev->ofdev.dev, np,
						 mbdev,  root_res) == शून्य)
				of_node_put(np);
		पूर्ण
	पूर्ण

	/* Add serial ports अगर any */
	अगर (sdev) अणु
		pnode = sdev->ofdev.dev.of_node;
		क्रम (np = शून्य; (np = of_get_next_child(pnode, np)) != शून्य;) अणु
			अगर (macio_skip_device(np))
				जारी;
			of_node_get(np);
			अगर (macio_add_one_device(chip, &sdev->ofdev.dev, np,
						 शून्य, root_res) == शून्य)
				of_node_put(np);
		पूर्ण
	पूर्ण
पूर्ण


/**
 * macio_रेजिस्टर_driver - Registers a new MacIO device driver
 * @drv: poपूर्णांकer to the driver definition काष्ठाure
 */
पूर्णांक macio_रेजिस्टर_driver(काष्ठा macio_driver *drv)
अणु
	/* initialize common driver fields */
	drv->driver.bus = &macio_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण

/**
 * macio_unरेजिस्टर_driver - Unरेजिस्टरs a new MacIO device driver
 * @drv: poपूर्णांकer to the driver definition काष्ठाure
 */
व्योम macio_unरेजिस्टर_driver(काष्ठा macio_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण

/* Managed MacIO resources */
काष्ठा macio_devres अणु
	u32	res_mask;
पूर्ण;

अटल व्योम maciom_release(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा macio_dev *dev = to_macio_device(gendev);
	काष्ठा macio_devres *dr = res;
	पूर्णांक i, max;

	max = min(dev->n_resources, 32);
	क्रम (i = 0; i < max; i++) अणु
		अगर (dr->res_mask & (1 << i))
			macio_release_resource(dev, i);
	पूर्ण
पूर्ण

पूर्णांक macio_enable_devres(काष्ठा macio_dev *dev)
अणु
	काष्ठा macio_devres *dr;

	dr = devres_find(&dev->ofdev.dev, maciom_release, शून्य, शून्य);
	अगर (!dr) अणु
		dr = devres_alloc(maciom_release, माप(*dr), GFP_KERNEL);
		अगर (!dr)
			वापस -ENOMEM;
	पूर्ण
	वापस devres_get(&dev->ofdev.dev, dr, शून्य, शून्य) != शून्य;
पूर्ण

अटल काष्ठा macio_devres * find_macio_dr(काष्ठा macio_dev *dev)
अणु
	वापस devres_find(&dev->ofdev.dev, maciom_release, शून्य, शून्य);
पूर्ण

/**
 *	macio_request_resource - Request an MMIO resource
 * 	@dev: poपूर्णांकer to the device holding the resource
 *	@resource_no: resource number to request
 *	@name: resource name
 *
 *	Mark  memory region number @resource_no associated with MacIO
 *	device @dev as being reserved by owner @name.  Do not access
 *	any address inside the memory regions unless this call वापसs
 *	successfully.
 *
 *	Returns 0 on success, or %EBUSY on error.  A warning
 *	message is also prपूर्णांकed on failure.
 */
पूर्णांक macio_request_resource(काष्ठा macio_dev *dev, पूर्णांक resource_no,
			   स्थिर अक्षर *name)
अणु
	काष्ठा macio_devres *dr = find_macio_dr(dev);

	अगर (macio_resource_len(dev, resource_no) == 0)
		वापस 0;
		
	अगर (!request_mem_region(macio_resource_start(dev, resource_no),
				macio_resource_len(dev, resource_no),
				name))
		जाओ err_out;

	अगर (dr && resource_no < 32)
		dr->res_mask |= 1 << resource_no;
	
	वापस 0;

err_out:
	prपूर्णांकk (KERN_WARNING "MacIO: Unable to reserve resource #%d:%lx@%lx"
		" for device %s\n",
		resource_no,
		macio_resource_len(dev, resource_no),
		macio_resource_start(dev, resource_no),
		dev_name(&dev->ofdev.dev));
	वापस -EBUSY;
पूर्ण

/**
 * macio_release_resource - Release an MMIO resource
 * @dev: poपूर्णांकer to the device holding the resource
 * @resource_no: resource number to release
 */
व्योम macio_release_resource(काष्ठा macio_dev *dev, पूर्णांक resource_no)
अणु
	काष्ठा macio_devres *dr = find_macio_dr(dev);

	अगर (macio_resource_len(dev, resource_no) == 0)
		वापस;
	release_mem_region(macio_resource_start(dev, resource_no),
			   macio_resource_len(dev, resource_no));
	अगर (dr && resource_no < 32)
		dr->res_mask &= ~(1 << resource_no);
पूर्ण

/**
 *	macio_request_resources - Reserve all memory resources
 *	@dev: MacIO device whose resources are to be reserved
 *	@name: Name to be associated with resource.
 *
 *	Mark all memory regions associated with MacIO device @dev as
 *	being reserved by owner @name.  Do not access any address inside
 *	the memory regions unless this call वापसs successfully.
 *
 *	Returns 0 on success, or %EBUSY on error.  A warning
 *	message is also prपूर्णांकed on failure.
 */
पूर्णांक macio_request_resources(काष्ठा macio_dev *dev, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	
	क्रम (i = 0; i < dev->n_resources; i++)
		अगर (macio_request_resource(dev, i, name))
			जाओ err_out;
	वापस 0;

err_out:
	जबतक(--i >= 0)
		macio_release_resource(dev, i);
		
	वापस -EBUSY;
पूर्ण

/**
 *	macio_release_resources - Release reserved memory resources
 *	@dev: MacIO device whose resources were previously reserved
 */

व्योम macio_release_resources(काष्ठा macio_dev *dev)
अणु
	पूर्णांक i;
	
	क्रम (i = 0; i < dev->n_resources; i++)
		macio_release_resource(dev, i);
पूर्ण


#अगर_घोषित CONFIG_PCI

अटल पूर्णांक macio_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device_node* np;
	काष्ठा macio_chip* chip;
	
	अगर (ent->venकरोr != PCI_VENDOR_ID_APPLE)
		वापस -ENODEV;

	/* Note regarding refcounting: We assume pci_device_to_OF_node() is
	 * ported to new OF APIs and वापसs a node with refcount incremented.
	 */
	np = pci_device_to_OF_node(pdev);
	अगर (np == शून्य)
		वापस -ENODEV;

	/* The above assumption is wrong !!!
	 * fix that here क्रम now until I fix the arch code
	 */
	of_node_get(np);

	/* We also assume that pmac_feature will have करोne a get() on nodes
	 * stored in the macio chips array
	 */
	chip = macio_find(np, macio_unknown);
       	of_node_put(np);
	अगर (chip == शून्य)
		वापस -ENODEV;

	/* XXX Need locking ??? */
	अगर (chip->lbus.pdev == शून्य) अणु
		chip->lbus.pdev = pdev;
		chip->lbus.chip = chip;
		pci_set_drvdata(pdev, &chip->lbus);
		pci_set_master(pdev);
	पूर्ण

	prपूर्णांकk(KERN_INFO "MacIO PCI driver attached to %s chipset\n",
		chip->name);

	/*
	 * HACK ALERT: The WallStreet PowerBook and some OHare based machines
	 * have 2 macio ASICs. I must probe the "main" one first or IDE
	 * ordering will be incorrect. So I put on "hold" the second one since
	 * it seem to appear first on PCI
	 */
	अगर (chip->type == macio_gatwick || chip->type == macio_ohareII)
		अगर (macio_chips[0].lbus.pdev == शून्य) अणु
			macio_on_hold = chip;
			वापस 0;
		पूर्ण

	macio_pci_add_devices(chip);
	अगर (macio_on_hold && macio_chips[0].lbus.pdev != शून्य) अणु
		macio_pci_add_devices(macio_on_hold);
		macio_on_hold = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम macio_pci_हटाओ(काष्ठा pci_dev* pdev)
अणु
	panic("removing of macio-asic not supported !\n");
पूर्ण

/*
 * MacIO is matched against any Apple ID, it's probe() function
 * will then decide wether it applies or not
 */
अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु अणु
	.venकरोr		= PCI_VENDOR_ID_APPLE,
	.device		= PCI_ANY_ID,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,

	पूर्ण, अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, pci_ids);

/* pci driver glue; this is a "new style" PCI driver module */
अटल काष्ठा pci_driver macio_pci_driver = अणु
	.name		= (अक्षर *) "macio",
	.id_table	= pci_ids,

	.probe		= macio_pci_probe,
	.हटाओ		= macio_pci_हटाओ,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PCI */

अटल पूर्णांक __init macio_module_init (व्योम) 
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक rc;

	rc = pci_रेजिस्टर_driver(&macio_pci_driver);
	अगर (rc)
		वापस rc;
#पूर्ण_अगर /* CONFIG_PCI */
	वापस 0;
पूर्ण

module_init(macio_module_init);

EXPORT_SYMBOL(macio_रेजिस्टर_driver);
EXPORT_SYMBOL(macio_unरेजिस्टर_driver);
EXPORT_SYMBOL(macio_dev_get);
EXPORT_SYMBOL(macio_dev_put);
EXPORT_SYMBOL(macio_request_resource);
EXPORT_SYMBOL(macio_release_resource);
EXPORT_SYMBOL(macio_request_resources);
EXPORT_SYMBOL(macio_release_resources);
EXPORT_SYMBOL(macio_enable_devres);

