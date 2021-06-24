<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mfd/mfd-core.c
 *
 * core MFD support
 * Copyright (c) 2006 Ian Molton
 * Copyright (c) 2007,2008 Dmitry Baryshkov
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/list.h>
#समावेश <linux/property.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regulator/consumer.h>

अटल LIST_HEAD(mfd_of_node_list);

काष्ठा mfd_of_node_entry अणु
	काष्ठा list_head list;
	काष्ठा device *dev;
	काष्ठा device_node *np;
पूर्ण;

अटल काष्ठा device_type mfd_dev_type = अणु
	.name	= "mfd_device",
पूर्ण;

पूर्णांक mfd_cell_enable(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);

	अगर (!cell->enable) अणु
		dev_dbg(&pdev->dev, "No .enable() call-back registered\n");
		वापस 0;
	पूर्ण

	वापस cell->enable(pdev);
पूर्ण
EXPORT_SYMBOL(mfd_cell_enable);

पूर्णांक mfd_cell_disable(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);

	अगर (!cell->disable) अणु
		dev_dbg(&pdev->dev, "No .disable() call-back registered\n");
		वापस 0;
	पूर्ण

	वापस cell->disable(pdev);
पूर्ण
EXPORT_SYMBOL(mfd_cell_disable);

#अगर IS_ENABLED(CONFIG_ACPI)
अटल व्योम mfd_acpi_add_device(स्थिर काष्ठा mfd_cell *cell,
				काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell_acpi_match *match = cell->acpi_match;
	काष्ठा acpi_device *parent, *child;
	काष्ठा acpi_device *adev = शून्य;

	parent = ACPI_COMPANION(pdev->dev.parent);
	अगर (!parent)
		वापस;

	/*
	 * MFD child device माला_लो its ACPI handle either from the ACPI device
	 * directly under the parent that matches the either _HID or _CID, or
	 * _ADR or it will use the parent handle अगर is no ID is given.
	 *
	 * Note that use of _ADR is a grey area in the ACPI specअगरication,
	 * though at least Intel Galileo Gen 2 is using it to distinguish
	 * the children devices.
	 */
	अगर (match) अणु
		अगर (match->pnpid) अणु
			काष्ठा acpi_device_id ids[2] = अणुपूर्ण;

			strlcpy(ids[0].id, match->pnpid, माप(ids[0].id));
			list_क्रम_each_entry(child, &parent->children, node) अणु
				अगर (!acpi_match_device_ids(child, ids)) अणु
					adev = child;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			adev = acpi_find_child_device(parent, match->adr, false);
		पूर्ण
	पूर्ण

	ACPI_COMPANION_SET(&pdev->dev, adev ?: parent);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mfd_acpi_add_device(स्थिर काष्ठा mfd_cell *cell,
				       काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mfd_match_of_node_to_dev(काष्ठा platक्रमm_device *pdev,
				    काष्ठा device_node *np,
				    स्थिर काष्ठा mfd_cell *cell)
अणु
#अगर IS_ENABLED(CONFIG_OF)
	काष्ठा mfd_of_node_entry *of_entry;
	स्थिर __be32 *reg;
	u64 of_node_addr;

	/* Skip अगर OF node has previously been allocated to a device */
	list_क्रम_each_entry(of_entry, &mfd_of_node_list, list)
		अगर (of_entry->np == np)
			वापस -EAGAIN;

	अगर (!cell->use_of_reg)
		/* No of_reg defined - allocate first मुक्त compatible match */
		जाओ allocate_of_node;

	/* We only care about each node's first defined address */
	reg = of_get_address(np, 0, शून्य, शून्य);
	अगर (!reg)
		/* OF node करोes not contatin a 'reg' property to match to */
		वापस -EAGAIN;

	of_node_addr = of_पढ़ो_number(reg, of_n_addr_cells(np));

	अगर (cell->of_reg != of_node_addr)
		/* No match */
		वापस -EAGAIN;

allocate_of_node:
	of_entry = kzalloc(माप(*of_entry), GFP_KERNEL);
	अगर (!of_entry)
		वापस -ENOMEM;

	of_entry->dev = &pdev->dev;
	of_entry->np = np;
	list_add_tail(&of_entry->list, &mfd_of_node_list);

	pdev->dev.of_node = np;
	pdev->dev.fwnode = &np->fwnode;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक mfd_add_device(काष्ठा device *parent, पूर्णांक id,
			  स्थिर काष्ठा mfd_cell *cell,
			  काष्ठा resource *mem_base,
			  पूर्णांक irq_base, काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा resource *res;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np = शून्य;
	काष्ठा mfd_of_node_entry *of_entry, *पंचांगp;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक platक्रमm_id;
	पूर्णांक r;

	अगर (id == PLATFORM_DEVID_AUTO)
		platक्रमm_id = id;
	अन्यथा
		platक्रमm_id = id + cell->id;

	pdev = platक्रमm_device_alloc(cell->name, platक्रमm_id);
	अगर (!pdev)
		जाओ fail_alloc;

	pdev->mfd_cell = kmemdup(cell, माप(*cell), GFP_KERNEL);
	अगर (!pdev->mfd_cell)
		जाओ fail_device;

	res = kसुस्मृति(cell->num_resources, माप(*res), GFP_KERNEL);
	अगर (!res)
		जाओ fail_device;

	pdev->dev.parent = parent;
	pdev->dev.type = &mfd_dev_type;
	pdev->dev.dma_mask = parent->dma_mask;
	pdev->dev.dma_parms = parent->dma_parms;
	pdev->dev.coherent_dma_mask = parent->coherent_dma_mask;

	ret = regulator_bulk_रेजिस्टर_supply_alias(
			&pdev->dev, cell->parent_supplies,
			parent, cell->parent_supplies,
			cell->num_parent_supplies);
	अगर (ret < 0)
		जाओ fail_res;

	अगर (IS_ENABLED(CONFIG_OF) && parent->of_node && cell->of_compatible) अणु
		क्रम_each_child_of_node(parent->of_node, np) अणु
			अगर (of_device_is_compatible(np, cell->of_compatible)) अणु
				/* Ignore 'disabled' devices error मुक्त */
				अगर (!of_device_is_available(np)) अणु
					ret = 0;
					जाओ fail_alias;
				पूर्ण

				ret = mfd_match_of_node_to_dev(pdev, np, cell);
				अगर (ret == -EAGAIN)
					जारी;
				अगर (ret)
					जाओ fail_alias;

				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!pdev->dev.of_node)
			pr_warn("%s: Failed to locate of_node [id: %d]\n",
				cell->name, platक्रमm_id);
	पूर्ण

	mfd_acpi_add_device(cell, pdev);

	अगर (cell->pdata_size) अणु
		ret = platक्रमm_device_add_data(pdev,
					cell->platक्रमm_data, cell->pdata_size);
		अगर (ret)
			जाओ fail_of_entry;
	पूर्ण

	अगर (cell->swnode) अणु
		ret = device_add_software_node(&pdev->dev, cell->swnode);
		अगर (ret)
			जाओ fail_of_entry;
	पूर्ण

	क्रम (r = 0; r < cell->num_resources; r++) अणु
		res[r].name = cell->resources[r].name;
		res[r].flags = cell->resources[r].flags;

		/* Find out base to use */
		अगर ((cell->resources[r].flags & IORESOURCE_MEM) && mem_base) अणु
			res[r].parent = mem_base;
			res[r].start = mem_base->start +
				cell->resources[r].start;
			res[r].end = mem_base->start +
				cell->resources[r].end;
		पूर्ण अन्यथा अगर (cell->resources[r].flags & IORESOURCE_IRQ) अणु
			अगर (करोमुख्य) अणु
				/* Unable to create mappings क्रम IRQ ranges. */
				WARN_ON(cell->resources[r].start !=
					cell->resources[r].end);
				res[r].start = res[r].end = irq_create_mapping(
					करोमुख्य, cell->resources[r].start);
			पूर्ण अन्यथा अणु
				res[r].start = irq_base +
					cell->resources[r].start;
				res[r].end   = irq_base +
					cell->resources[r].end;
			पूर्ण
		पूर्ण अन्यथा अणु
			res[r].parent = cell->resources[r].parent;
			res[r].start = cell->resources[r].start;
			res[r].end   = cell->resources[r].end;
		पूर्ण

		अगर (!cell->ignore_resource_conflicts) अणु
			अगर (has_acpi_companion(&pdev->dev)) अणु
				ret = acpi_check_resource_conflict(&res[r]);
				अगर (ret)
					जाओ fail_of_entry;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = platक्रमm_device_add_resources(pdev, res, cell->num_resources);
	अगर (ret)
		जाओ fail_of_entry;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ fail_of_entry;

	अगर (cell->pm_runसमय_no_callbacks)
		pm_runसमय_no_callbacks(&pdev->dev);

	kमुक्त(res);

	वापस 0;

fail_of_entry:
	list_क्रम_each_entry_safe(of_entry, पंचांगp, &mfd_of_node_list, list)
		अगर (of_entry->dev == &pdev->dev) अणु
			list_del(&of_entry->list);
			kमुक्त(of_entry);
		पूर्ण
	device_हटाओ_software_node(&pdev->dev);
fail_alias:
	regulator_bulk_unरेजिस्टर_supply_alias(&pdev->dev,
					       cell->parent_supplies,
					       cell->num_parent_supplies);
fail_res:
	kमुक्त(res);
fail_device:
	platक्रमm_device_put(pdev);
fail_alloc:
	वापस ret;
पूर्ण

/**
 * mfd_add_devices - रेजिस्टर child devices
 *
 * @parent:	Poपूर्णांकer to parent device.
 * @id:		Can be PLATFORM_DEVID_AUTO to let the Platक्रमm API take care
 *		of device numbering, or will be added to a device's cell_id.
 * @cells:	Array of (काष्ठा mfd_cell)s describing child devices.
 * @n_devs:	Number of child devices to रेजिस्टर.
 * @mem_base:	Parent रेजिस्टर range resource क्रम child devices.
 * @irq_base:	Base of the range of भव पूर्णांकerrupt numbers allocated क्रम
 *		this MFD device. Unused अगर @करोमुख्य is specअगरied.
 * @करोमुख्य:	Interrupt करोमुख्य to create mappings क्रम hardware पूर्णांकerrupts.
 */
पूर्णांक mfd_add_devices(काष्ठा device *parent, पूर्णांक id,
		    स्थिर काष्ठा mfd_cell *cells, पूर्णांक n_devs,
		    काष्ठा resource *mem_base,
		    पूर्णांक irq_base, काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < n_devs; i++) अणु
		ret = mfd_add_device(parent, id, cells + i, mem_base,
				     irq_base, करोमुख्य);
		अगर (ret)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	अगर (i)
		mfd_हटाओ_devices(parent);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mfd_add_devices);

अटल पूर्णांक mfd_हटाओ_devices_fn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा mfd_cell *cell;
	पूर्णांक *level = data;

	अगर (dev->type != &mfd_dev_type)
		वापस 0;

	pdev = to_platक्रमm_device(dev);
	cell = mfd_get_cell(pdev);

	अगर (level && cell->level > *level)
		वापस 0;

	regulator_bulk_unरेजिस्टर_supply_alias(dev, cell->parent_supplies,
					       cell->num_parent_supplies);

	device_हटाओ_software_node(&pdev->dev);

	platक्रमm_device_unरेजिस्टर(pdev);
	वापस 0;
पूर्ण

व्योम mfd_हटाओ_devices_late(काष्ठा device *parent)
अणु
	पूर्णांक level = MFD_DEP_LEVEL_HIGH;

	device_क्रम_each_child_reverse(parent, &level, mfd_हटाओ_devices_fn);
पूर्ण
EXPORT_SYMBOL(mfd_हटाओ_devices_late);

व्योम mfd_हटाओ_devices(काष्ठा device *parent)
अणु
	पूर्णांक level = MFD_DEP_LEVEL_NORMAL;

	device_क्रम_each_child_reverse(parent, &level, mfd_हटाओ_devices_fn);
पूर्ण
EXPORT_SYMBOL(mfd_हटाओ_devices);

अटल व्योम devm_mfd_dev_release(काष्ठा device *dev, व्योम *res)
अणु
	mfd_हटाओ_devices(dev);
पूर्ण

/**
 * devm_mfd_add_devices - Resource managed version of mfd_add_devices()
 *
 * Returns 0 on success or an appropriate negative error number on failure.
 * All child-devices of the MFD will स्वतःmatically be हटाओd when it माला_लो
 * unbinded.
 *
 * @dev:	Poपूर्णांकer to parent device.
 * @id:		Can be PLATFORM_DEVID_AUTO to let the Platक्रमm API take care
 *		of device numbering, or will be added to a device's cell_id.
 * @cells:	Array of (काष्ठा mfd_cell)s describing child devices.
 * @n_devs:	Number of child devices to रेजिस्टर.
 * @mem_base:	Parent रेजिस्टर range resource क्रम child devices.
 * @irq_base:	Base of the range of भव पूर्णांकerrupt numbers allocated क्रम
 *		this MFD device. Unused अगर @करोमुख्य is specअगरied.
 * @करोमुख्य:	Interrupt करोमुख्य to create mappings क्रम hardware पूर्णांकerrupts.
 */
पूर्णांक devm_mfd_add_devices(काष्ठा device *dev, पूर्णांक id,
			 स्थिर काष्ठा mfd_cell *cells, पूर्णांक n_devs,
			 काष्ठा resource *mem_base,
			 पूर्णांक irq_base, काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_mfd_dev_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = mfd_add_devices(dev, id, cells, n_devs, mem_base,
			      irq_base, करोमुख्य);
	अगर (ret < 0) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	*ptr = dev;
	devres_add(dev, ptr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(devm_mfd_add_devices);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ian Molton, Dmitry Baryshkov");
