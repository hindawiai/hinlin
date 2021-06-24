<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers.c
 *
 * Copyright (c) 1999 The Puffin Group
 * Copyright (c) 2001 Matthew Wilcox क्रम Hewlett Packard
 * Copyright (c) 2001 Helge Deller <deller@gmx.de>
 * Copyright (c) 2001,2002 Ryan Bradetich 
 * Copyright (c) 2004-2005 Thibaut VARENE <varenet@parisc-linux.org>
 * 
 * The file handles रेजिस्टरing devices and drivers, then matching them.
 * It's the बंदst we get to a dating agency.
 *
 * If you're thinking about modअगरying this file, here are some gotchas to
 * bear in mind:
 *  - 715/Mirage device paths have a dummy device between Lasi and its children
 *  - The EISA adapter may show up as a sibling or child of Wax
 *  - Dino has an optionally functional serial port.  If firmware enables it,
 *    it shows up as a child of Dino.  If firmware disables it, the buswalk
 *    finds it and it shows up as a child of Cujo
 *  - Dino has both parisc and pci devices as children
 *  - parisc devices are discovered in a अक्रमom order, including children
 *    beक्रमe parents in some हालs.
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/ropes.h>

/* See comments in include/यंत्र-parisc/pci.h */
स्थिर काष्ठा dma_map_ops *hppa_dma_ops __ro_after_init;
EXPORT_SYMBOL(hppa_dma_ops);

अटल काष्ठा device root = अणु
	.init_name = "parisc",
पूर्ण;

अटल अंतरभूत पूर्णांक check_dev(काष्ठा device *dev)
अणु
	अगर (dev->bus == &parisc_bus_type) अणु
		काष्ठा parisc_device *pdev;
		pdev = to_parisc_device(dev);
		वापस pdev->id.hw_type != HPHW_FAULTY;
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा device *
parse_tree_node(काष्ठा device *parent, पूर्णांक index, काष्ठा hardware_path *modpath);

काष्ठा recurse_काष्ठा अणु
	व्योम * obj;
	पूर्णांक (*fn)(काष्ठा device *, व्योम *);
पूर्ण;

अटल पूर्णांक descend_children(काष्ठा device * dev, व्योम * data)
अणु
	काष्ठा recurse_काष्ठा * recurse_data = (काष्ठा recurse_काष्ठा *)data;

	अगर (recurse_data->fn(dev, recurse_data->obj))
		वापस 1;
	अन्यथा
		वापस device_क्रम_each_child(dev, recurse_data, descend_children);
पूर्ण

/**
 *	क्रम_each_padev - Iterate over all devices in the tree
 *	@fn:	Function to call क्रम each device.
 *	@data:	Data to pass to the called function.
 *
 *	This perक्रमms a depth-first traversal of the tree, calling the
 *	function passed क्रम each node.  It calls the function क्रम parents
 *	beक्रमe children.
 */

अटल पूर्णांक क्रम_each_padev(पूर्णांक (*fn)(काष्ठा device *, व्योम *), व्योम * data)
अणु
	काष्ठा recurse_काष्ठा recurse_data = अणु
		.obj	= data,
		.fn	= fn,
	पूर्ण;
	वापस device_क्रम_each_child(&root, &recurse_data, descend_children);
पूर्ण

/**
 * match_device - Report whether this driver can handle this device
 * @driver: the PA-RISC driver to try
 * @dev: the PA-RISC device to try
 */
अटल पूर्णांक match_device(काष्ठा parisc_driver *driver, काष्ठा parisc_device *dev)
अणु
	स्थिर काष्ठा parisc_device_id *ids;

	क्रम (ids = driver->id_table; ids->sversion; ids++) अणु
		अगर ((ids->sversion != SVERSION_ANY_ID) &&
		    (ids->sversion != dev->id.sversion))
			जारी;

		अगर ((ids->hw_type != HWTYPE_ANY_ID) &&
		    (ids->hw_type != dev->id.hw_type))
			जारी;

		अगर ((ids->hversion != HVERSION_ANY_ID) &&
		    (ids->hversion != dev->id.hversion))
			जारी;

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parisc_driver_probe(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा parisc_device *pa_dev = to_parisc_device(dev);
	काष्ठा parisc_driver *pa_drv = to_parisc_driver(dev->driver);

	rc = pa_drv->probe(pa_dev);

	अगर (!rc)
		pa_dev->driver = pa_drv;

	वापस rc;
पूर्ण

अटल पूर्णांक __निकास parisc_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा parisc_device *pa_dev = to_parisc_device(dev);
	काष्ठा parisc_driver *pa_drv = to_parisc_driver(dev->driver);
	अगर (pa_drv->हटाओ)
		pa_drv->हटाओ(pa_dev);

	वापस 0;
पूर्ण
	

/**
 * रेजिस्टर_parisc_driver - Register this driver अगर it can handle a device
 * @driver: the PA-RISC driver to try
 */
पूर्णांक रेजिस्टर_parisc_driver(काष्ठा parisc_driver *driver)
अणु
	/* FIXME: we need this because apparently the sti
	 * driver can be रेजिस्टरed twice */
	अगर (driver->drv.name) अणु
		pr_warn("BUG: skipping previously registered driver %s\n",
			driver->name);
		वापस 1;
	पूर्ण

	अगर (!driver->probe) अणु
		pr_warn("BUG: driver %s has no probe routine\n", driver->name);
		वापस 1;
	पूर्ण

	driver->drv.bus = &parisc_bus_type;

	/* We install our own probe and हटाओ routines */
	WARN_ON(driver->drv.probe != शून्य);
	WARN_ON(driver->drv.हटाओ != शून्य);

	driver->drv.name = driver->name;

	वापस driver_रेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_parisc_driver);


काष्ठा match_count अणु
	काष्ठा parisc_driver * driver;
	पूर्णांक count;
पूर्ण;

अटल पूर्णांक match_and_count(काष्ठा device * dev, व्योम * data)
अणु
	काष्ठा match_count * m = data;
	काष्ठा parisc_device * pdev = to_parisc_device(dev);

	अगर (check_dev(dev)) अणु
		अगर (match_device(m->driver, pdev))
			m->count++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * count_parisc_driver - count # of devices this driver would match
 * @driver: the PA-RISC driver to try
 *
 * Use by IOMMU support to "guess" the right size IOPdir.
 * Formula is something like memsize/(num_iommu * entry_size).
 */
पूर्णांक __init count_parisc_driver(काष्ठा parisc_driver *driver)
अणु
	काष्ठा match_count m = अणु
		.driver	= driver,
		.count	= 0,
	पूर्ण;

	क्रम_each_padev(match_and_count, &m);

	वापस m.count;
पूर्ण



/**
 * unरेजिस्टर_parisc_driver - Unरेजिस्टर this driver from the list of drivers
 * @driver: the PA-RISC driver to unरेजिस्टर
 */
पूर्णांक unरेजिस्टर_parisc_driver(काष्ठा parisc_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->drv);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_parisc_driver);

काष्ठा find_data अणु
	अचिन्हित दीर्घ hpa;
	काष्ठा parisc_device * dev;
पूर्ण;

अटल पूर्णांक find_device(काष्ठा device * dev, व्योम * data)
अणु
	काष्ठा parisc_device * pdev = to_parisc_device(dev);
	काष्ठा find_data * d = (काष्ठा find_data*)data;

	अगर (check_dev(dev)) अणु
		अगर (pdev->hpa.start == d->hpa) अणु
			d->dev = pdev;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा parisc_device *find_device_by_addr(अचिन्हित दीर्घ hpa)
अणु
	काष्ठा find_data d = अणु
		.hpa	= hpa,
	पूर्ण;
	पूर्णांक ret;

	ret = क्रम_each_padev(find_device, &d);
	वापस ret ? d.dev : शून्य;
पूर्ण

अटल पूर्णांक __init is_IKE_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा parisc_device *pdev = to_parisc_device(dev);

	अगर (!check_dev(dev))
		वापस 0;
	अगर (pdev->id.hw_type != HPHW_BCPORT)
		वापस 0;
	अगर (IS_IKE(pdev) ||
		(pdev->id.hversion == REO_MERCED_PORT) ||
		(pdev->id.hversion == REOG_MERCED_PORT)) अणु
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init machine_has_merced_bus(व्योम)
अणु
	पूर्णांक ret;

	ret = क्रम_each_padev(is_IKE_device, शून्य);
	वापस ret ? 1 : 0;
पूर्ण

/**
 * find_pa_parent_type - Find a parent of a specअगरic type
 * @dev: The device to start searching from
 * @type: The device type to search क्रम.
 *
 * Walks up the device tree looking क्रम a device of the specअगरied type.
 * If it finds it, it वापसs it.  If not, it वापसs शून्य.
 */
स्थिर काष्ठा parisc_device *
find_pa_parent_type(स्थिर काष्ठा parisc_device *padev, पूर्णांक type)
अणु
	स्थिर काष्ठा device *dev = &padev->dev;
	जबतक (dev != &root) अणु
		काष्ठा parisc_device *candidate = to_parisc_device(dev);
		अगर (candidate->id.hw_type == type)
			वापस candidate;
		dev = dev->parent;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * get_node_path fills in @path with the firmware path to the device.
 * Note that अगर @node is a parisc device, we करोn't fill in the 'mod' field.
 * This is because both callers pass the parent and fill in the mod
 * themselves.  If @node is a PCI device, we करो fill it in, even though this
 * is inconsistent.
 */
अटल व्योम get_node_path(काष्ठा device *dev, काष्ठा hardware_path *path)
अणु
	पूर्णांक i = 5;
	स_रखो(&path->bc, -1, 6);

	अगर (dev_is_pci(dev)) अणु
		अचिन्हित पूर्णांक devfn = to_pci_dev(dev)->devfn;
		path->mod = PCI_FUNC(devfn);
		path->bc[i--] = PCI_SLOT(devfn);
		dev = dev->parent;
	पूर्ण

	जबतक (dev != &root) अणु
		अगर (dev_is_pci(dev)) अणु
			अचिन्हित पूर्णांक devfn = to_pci_dev(dev)->devfn;
			path->bc[i--] = PCI_SLOT(devfn) | (PCI_FUNC(devfn)<< 5);
		पूर्ण अन्यथा अगर (dev->bus == &parisc_bus_type) अणु
			path->bc[i--] = to_parisc_device(dev)->hw_path;
		पूर्ण
		dev = dev->parent;
	पूर्ण
पूर्ण

अटल अक्षर *prपूर्णांक_hwpath(काष्ठा hardware_path *path, अक्षर *output)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 6; i++) अणु
		अगर (path->bc[i] == -1)
			जारी;
		output += प्र_लिखो(output, "%u/", (अचिन्हित अक्षर) path->bc[i]);
	पूर्ण
	output += प्र_लिखो(output, "%u", (अचिन्हित अक्षर) path->mod);
	वापस output;
पूर्ण

/**
 * prपूर्णांक_pa_hwpath - Returns hardware path क्रम PA devices
 * dev: The device to वापस the path क्रम
 * output: Poपूर्णांकer to a previously-allocated array to place the path in.
 *
 * This function fills in the output array with a human-पढ़ोable path
 * to a PA device.  This string is compatible with that used by PDC, and
 * may be prपूर्णांकed on the outside of the box.
 */
अक्षर *prपूर्णांक_pa_hwpath(काष्ठा parisc_device *dev, अक्षर *output)
अणु
	काष्ठा hardware_path path;

	get_node_path(dev->dev.parent, &path);
	path.mod = dev->hw_path;
	वापस prपूर्णांक_hwpath(&path, output);
पूर्ण
EXPORT_SYMBOL(prपूर्णांक_pa_hwpath);

#अगर defined(CONFIG_PCI) || defined(CONFIG_ISA)
/**
 * get_pci_node_path - Determines the hardware path क्रम a PCI device
 * @pdev: The device to वापस the path क्रम
 * @path: Poपूर्णांकer to a previously-allocated array to place the path in.
 *
 * This function fills in the hardware_path काष्ठाure with the route to
 * the specअगरied PCI device.  This काष्ठाure is suitable क्रम passing to
 * PDC calls.
 */
व्योम get_pci_node_path(काष्ठा pci_dev *pdev, काष्ठा hardware_path *path)
अणु
	get_node_path(&pdev->dev, path);
पूर्ण
EXPORT_SYMBOL(get_pci_node_path);

/**
 * prपूर्णांक_pci_hwpath - Returns hardware path क्रम PCI devices
 * dev: The device to वापस the path क्रम
 * output: Poपूर्णांकer to a previously-allocated array to place the path in.
 *
 * This function fills in the output array with a human-पढ़ोable path
 * to a PCI device.  This string is compatible with that used by PDC, and
 * may be prपूर्णांकed on the outside of the box.
 */
अक्षर *prपूर्णांक_pci_hwpath(काष्ठा pci_dev *dev, अक्षर *output)
अणु
	काष्ठा hardware_path path;

	get_pci_node_path(dev, &path);
	वापस prपूर्णांक_hwpath(&path, output);
पूर्ण
EXPORT_SYMBOL(prपूर्णांक_pci_hwpath);

#पूर्ण_अगर /* defined(CONFIG_PCI) || defined(CONFIG_ISA) */

अटल व्योम setup_bus_id(काष्ठा parisc_device *padev)
अणु
	काष्ठा hardware_path path;
	अक्षर name[28];
	अक्षर *output = name;
	पूर्णांक i;

	get_node_path(padev->dev.parent, &path);

	क्रम (i = 0; i < 6; i++) अणु
		अगर (path.bc[i] == -1)
			जारी;
		output += प्र_लिखो(output, "%u:", (अचिन्हित अक्षर) path.bc[i]);
	पूर्ण
	प्र_लिखो(output, "%u", (अचिन्हित अक्षर) padev->hw_path);
	dev_set_name(&padev->dev, name);
पूर्ण

काष्ठा parisc_device * __init create_tree_node(अक्षर id, काष्ठा device *parent)
अणु
	काष्ठा parisc_device *dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->hw_path = id;
	dev->id.hw_type = HPHW_FAULTY;

	dev->dev.parent = parent;
	setup_bus_id(dev);

	dev->dev.bus = &parisc_bus_type;
	dev->dma_mask = 0xffffffffUL;	/* PARISC devices are 32-bit */

	/* make the generic dma mask a poपूर्णांकer to the parisc one */
	dev->dev.dma_mask = &dev->dma_mask;
	dev->dev.coherent_dma_mask = dev->dma_mask;
	अगर (device_रेजिस्टर(&dev->dev)) अणु
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण

काष्ठा match_id_data अणु
	अक्षर id;
	काष्ठा parisc_device * dev;
पूर्ण;

अटल पूर्णांक match_by_id(काष्ठा device * dev, व्योम * data)
अणु
	काष्ठा parisc_device * pdev = to_parisc_device(dev);
	काष्ठा match_id_data * d = data;

	अगर (pdev->hw_path == d->id) अणु
		d->dev = pdev;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * alloc_tree_node - वापसs a device entry in the iotree
 * @parent: the parent node in the tree
 * @id: the element of the module path क्रम this entry
 *
 * Checks all the children of @parent क्रम a matching @id.  If none
 * found, it allocates a new device and वापसs it.
 */
अटल काष्ठा parisc_device * __init alloc_tree_node(
			काष्ठा device *parent, अक्षर id)
अणु
	काष्ठा match_id_data d = अणु
		.id = id,
	पूर्ण;
	अगर (device_क्रम_each_child(parent, &d, match_by_id))
		वापस d.dev;
	अन्यथा
		वापस create_tree_node(id, parent);
पूर्ण

अटल काष्ठा parisc_device *create_parisc_device(काष्ठा hardware_path *modpath)
अणु
	पूर्णांक i;
	काष्ठा device *parent = &root;
	क्रम (i = 0; i < 6; i++) अणु
		अगर (modpath->bc[i] == -1)
			जारी;
		parent = &alloc_tree_node(parent, modpath->bc[i])->dev;
	पूर्ण
	वापस alloc_tree_node(parent, modpath->mod);
पूर्ण

काष्ठा parisc_device * __init
alloc_pa_dev(अचिन्हित दीर्घ hpa, काष्ठा hardware_path *mod_path)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ bytecnt;
	u8 iodc_data[32];
	काष्ठा parisc_device *dev;
	स्थिर अक्षर *name;

	/* Check to make sure this device has not alपढ़ोy been added - Ryan */
	अगर (find_device_by_addr(hpa) != शून्य)
		वापस शून्य;

	status = pdc_iodc_पढ़ो(&bytecnt, hpa, 0, &iodc_data, 32);
	अगर (status != PDC_OK)
		वापस शून्य;

	dev = create_parisc_device(mod_path);
	अगर (dev->id.hw_type != HPHW_FAULTY) अणु
		pr_err("Two devices have hardware path [%s].  IODC data for second device: %7phN\n"
		       "Rearranging GSC cards sometimes helps\n",
			parisc_pathname(dev), iodc_data);
		वापस शून्य;
	पूर्ण

	dev->id.hw_type = iodc_data[3] & 0x1f;
	dev->id.hversion = (iodc_data[0] << 4) | ((iodc_data[1] & 0xf0) >> 4);
	dev->id.hversion_rev = iodc_data[1] & 0x0f;
	dev->id.sversion = ((iodc_data[4] & 0x0f) << 16) |
			(iodc_data[5] << 8) | iodc_data[6];
	dev->hpa.name = parisc_pathname(dev);
	dev->hpa.start = hpa;
	/* This is awkward.  The STI spec says that gfx devices may occupy
	 * 32MB or 64MB.  Unक्रमtunately, we करोn't know how to tell whether
	 * it's the क्रमmer or the latter.  Assumptions either way can hurt us.
	 */
	अगर (hpa == 0xf4000000 || hpa == 0xf8000000) अणु
		dev->hpa.end = hpa + 0x03ffffff;
	पूर्ण अन्यथा अगर (hpa == 0xf6000000 || hpa == 0xfa000000) अणु
		dev->hpa.end = hpa + 0x01ffffff;
	पूर्ण अन्यथा अणु
		dev->hpa.end = hpa + 0xfff;
	पूर्ण
	dev->hpa.flags = IORESOURCE_MEM;
	name = parisc_hardware_description(&dev->id);
	अगर (name) अणु
		strlcpy(dev->name, name, माप(dev->name));
	पूर्ण

	/* Silently fail things like mouse ports which are subsumed within
	 * the keyboard controller
	 */
	अगर ((hpa & 0xfff) == 0 && insert_resource(&iomem_resource, &dev->hpa))
		pr_warn("Unable to claim HPA %lx for device %s\n", hpa, name);

	वापस dev;
पूर्ण

अटल पूर्णांक parisc_generic_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस match_device(to_parisc_driver(drv), to_parisc_device(dev));
पूर्ण

अटल sमाप_प्रकार make_modalias(काष्ठा device *dev, अक्षर *buf)
अणु
	स्थिर काष्ठा parisc_device *padev = to_parisc_device(dev);
	स्थिर काष्ठा parisc_device_id *id = &padev->id;

	वापस प्र_लिखो(buf, "parisc:t%02Xhv%04Xrev%02Xsv%08X\n",
		(u8)id->hw_type, (u16)id->hversion, (u8)id->hversion_rev,
		(u32)id->sversion);
पूर्ण

अटल पूर्णांक parisc_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	स्थिर काष्ठा parisc_device *padev;
	अक्षर modalias[40];

	अगर (!dev)
		वापस -ENODEV;

	padev = to_parisc_device(dev);
	अगर (!padev)
		वापस -ENODEV;

	अगर (add_uevent_var(env, "PARISC_NAME=%s", padev->name))
		वापस -ENOMEM;

	make_modalias(dev, modalias);
	अगर (add_uevent_var(env, "MODALIAS=%s", modalias))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#घोषणा pa_dev_attr(name, field, क्रमmat_string)				\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा parisc_device *padev = to_parisc_device(dev);		\
	वापस प्र_लिखो(buf, क्रमmat_string, padev->field);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name);

#घोषणा pa_dev_attr_id(field, क्रमmat) pa_dev_attr(field, id.field, क्रमmat)

pa_dev_attr(irq, irq, "%u\n");
pa_dev_attr_id(hw_type, "0x%02x\n");
pa_dev_attr(rev, id.hversion_rev, "0x%x\n");
pa_dev_attr_id(hversion, "0x%03x\n");
pa_dev_attr_id(sversion, "0x%05x\n");

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस make_modalias(dev, buf);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *parisc_device_attrs[] = अणु
	&dev_attr_irq.attr,
	&dev_attr_hw_type.attr,
	&dev_attr_rev.attr,
	&dev_attr_hversion.attr,
	&dev_attr_sversion.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(parisc_device);

काष्ठा bus_type parisc_bus_type = अणु
	.name = "parisc",
	.match = parisc_generic_match,
	.uevent = parisc_uevent,
	.dev_groups = parisc_device_groups,
	.probe = parisc_driver_probe,
	.हटाओ = __निकास_p(parisc_driver_हटाओ),
पूर्ण;

/**
 * रेजिस्टर_parisc_device - Locate a driver to manage this device.
 * @dev: The parisc device.
 *
 * Search the driver list क्रम a driver that is willing to manage
 * this device.
 */
पूर्णांक __init रेजिस्टर_parisc_device(काष्ठा parisc_device *dev)
अणु
	अगर (!dev)
		वापस 0;

	अगर (dev->driver)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * match_pci_device - Matches a pci device against a given hardware path
 * entry.
 * @dev: the generic device (known to be contained by a pci_dev).
 * @index: the current BC index
 * @modpath: the hardware path.
 * @वापस: true अगर the device matches the hardware path.
 */
अटल पूर्णांक match_pci_device(काष्ठा device *dev, पूर्णांक index,
		काष्ठा hardware_path *modpath)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक id;

	अगर (index == 5) अणु
		/* we are at the end of the path, and on the actual device */
		अचिन्हित पूर्णांक devfn = pdev->devfn;
		वापस ((modpath->bc[5] == PCI_SLOT(devfn)) &&
					(modpath->mod == PCI_FUNC(devfn)));
	पूर्ण

	/* index might be out of bounds क्रम bc[] */
	अगर (index >= 6)
		वापस 0;

	id = PCI_SLOT(pdev->devfn) | (PCI_FUNC(pdev->devfn) << 5);
	वापस (modpath->bc[index] == id);
पूर्ण

/**
 * match_parisc_device - Matches a parisc device against a given hardware
 * path entry.
 * @dev: the generic device (known to be contained by a parisc_device).
 * @index: the current BC index
 * @modpath: the hardware path.
 * @वापस: true अगर the device matches the hardware path.
 */
अटल पूर्णांक match_parisc_device(काष्ठा device *dev, पूर्णांक index,
		काष्ठा hardware_path *modpath)
अणु
	काष्ठा parisc_device *curr = to_parisc_device(dev);
	अक्षर id = (index == 6) ? modpath->mod : modpath->bc[index];

	वापस (curr->hw_path == id);
पूर्ण

काष्ठा parse_tree_data अणु
	पूर्णांक index;
	काष्ठा hardware_path * modpath;
	काष्ठा device * dev;
पूर्ण;

अटल पूर्णांक check_parent(काष्ठा device * dev, व्योम * data)
अणु
	काष्ठा parse_tree_data * d = data;

	अगर (check_dev(dev)) अणु
		अगर (dev->bus == &parisc_bus_type) अणु
			अगर (match_parisc_device(dev, d->index, d->modpath))
				d->dev = dev;
		पूर्ण अन्यथा अगर (dev_is_pci(dev)) अणु
			अगर (match_pci_device(dev, d->index, d->modpath))
				d->dev = dev;
		पूर्ण अन्यथा अगर (dev->bus == शून्य) अणु
			/* we are on a bus bridge */
			काष्ठा device *new = parse_tree_node(dev, d->index, d->modpath);
			अगर (new)
				d->dev = new;
		पूर्ण
	पूर्ण
	वापस d->dev != शून्य;
पूर्ण

/**
 * parse_tree_node - वापसs a device entry in the iotree
 * @parent: the parent node in the tree
 * @index: the current BC index
 * @modpath: the hardware_path काष्ठा to match a device against
 * @वापस: The corresponding device अगर found, शून्य otherwise.
 *
 * Checks all the children of @parent क्रम a matching @id.  If none
 * found, it वापसs शून्य.
 */
अटल काष्ठा device *
parse_tree_node(काष्ठा device *parent, पूर्णांक index, काष्ठा hardware_path *modpath)
अणु
	काष्ठा parse_tree_data d = अणु
		.index          = index,
		.modpath        = modpath,
	पूर्ण;

	काष्ठा recurse_काष्ठा recurse_data = अणु
		.obj	= &d,
		.fn	= check_parent,
	पूर्ण;

	अगर (device_क्रम_each_child(parent, &recurse_data, descend_children))
		/* nothing */;

	वापस d.dev;
पूर्ण

/**
 * hwpath_to_device - Finds the generic device corresponding to a given hardware path.
 * @modpath: the hardware path.
 * @वापस: The target device, शून्य अगर not found.
 */
काष्ठा device *hwpath_to_device(काष्ठा hardware_path *modpath)
अणु
	पूर्णांक i;
	काष्ठा device *parent = &root;
	क्रम (i = 0; i < 6; i++) अणु
		अगर (modpath->bc[i] == -1)
			जारी;
		parent = parse_tree_node(parent, i, modpath);
		अगर (!parent)
			वापस शून्य;
	पूर्ण
	अगर (dev_is_pci(parent)) /* pci devices alपढ़ोy parse MOD */
		वापस parent;
	अन्यथा
		वापस parse_tree_node(parent, 6, modpath);
पूर्ण
EXPORT_SYMBOL(hwpath_to_device);

/**
 * device_to_hwpath - Populates the hwpath corresponding to the given device.
 * @param dev the target device
 * @param path poपूर्णांकer to a previously allocated hwpath काष्ठा to be filled in
 */
व्योम device_to_hwpath(काष्ठा device *dev, काष्ठा hardware_path *path)
अणु
	काष्ठा parisc_device *padev;
	अगर (dev->bus == &parisc_bus_type) अणु
		padev = to_parisc_device(dev);
		get_node_path(dev->parent, path);
		path->mod = padev->hw_path;
	पूर्ण अन्यथा अगर (dev_is_pci(dev)) अणु
		get_node_path(dev, path);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(device_to_hwpath);

#घोषणा BC_PORT_MASK 0x8
#घोषणा BC_LOWER_PORT 0x8

#घोषणा BUS_CONVERTER(dev) \
        ((dev->id.hw_type == HPHW_IOA) || (dev->id.hw_type == HPHW_BCPORT))

#घोषणा IS_LOWER_PORT(dev) \
        ((gsc_पढ़ोl(dev->hpa.start + दुरत्व(काष्ठा bc_module, io_status)) \
                & BC_PORT_MASK) == BC_LOWER_PORT)

#घोषणा MAX_NATIVE_DEVICES 64
#घोषणा NATIVE_DEVICE_OFFSET 0x1000

#घोषणा FLEX_MASK 	F_EXTEND(0xfffc0000)
#घोषणा IO_IO_LOW	दुरत्व(काष्ठा bc_module, io_io_low)
#घोषणा IO_IO_HIGH	दुरत्व(काष्ठा bc_module, io_io_high)
#घोषणा READ_IO_IO_LOW(dev)  (अचिन्हित दीर्घ)(चिन्हित पूर्णांक)gsc_पढ़ोl(dev->hpa.start + IO_IO_LOW)
#घोषणा READ_IO_IO_HIGH(dev) (अचिन्हित दीर्घ)(चिन्हित पूर्णांक)gsc_पढ़ोl(dev->hpa.start + IO_IO_HIGH)

अटल व्योम walk_native_bus(अचिन्हित दीर्घ io_io_low, अचिन्हित दीर्घ io_io_high,
                            काष्ठा device *parent);

अटल व्योम __init walk_lower_bus(काष्ठा parisc_device *dev)
अणु
	अचिन्हित दीर्घ io_io_low, io_io_high;

	अगर (!BUS_CONVERTER(dev) || IS_LOWER_PORT(dev))
		वापस;

	अगर (dev->id.hw_type == HPHW_IOA) अणु
		io_io_low = (अचिन्हित दीर्घ)(चिन्हित पूर्णांक)(READ_IO_IO_LOW(dev) << 16);
		io_io_high = io_io_low + MAX_NATIVE_DEVICES * NATIVE_DEVICE_OFFSET;
	पूर्ण अन्यथा अणु
		io_io_low = (READ_IO_IO_LOW(dev) + ~FLEX_MASK) & FLEX_MASK;
		io_io_high = (READ_IO_IO_HIGH(dev)+ ~FLEX_MASK) & FLEX_MASK;
	पूर्ण

	walk_native_bus(io_io_low, io_io_high, &dev->dev);
पूर्ण

/**
 * walk_native_bus -- Probe a bus क्रम devices
 * @io_io_low: Base address of this bus.
 * @io_io_high: Last address of this bus.
 * @parent: The parent bus device.
 * 
 * A native bus (eg Runway or GSC) may have up to 64 devices on it,
 * spaced at पूर्णांकervals of 0x1000 bytes.  PDC may not inक्रमm us of these
 * devices, so we have to probe क्रम them.  Unक्रमtunately, we may find
 * devices which are not physically connected (such as extra serial &
 * keyboard ports).  This problem is not yet solved.
 */
अटल व्योम __init walk_native_bus(अचिन्हित दीर्घ io_io_low,
	अचिन्हित दीर्घ io_io_high, काष्ठा device *parent)
अणु
	पूर्णांक i, devices_found = 0;
	अचिन्हित दीर्घ hpa = io_io_low;
	काष्ठा hardware_path path;

	get_node_path(parent, &path);
	करो अणु
		क्रम(i = 0; i < MAX_NATIVE_DEVICES; i++, hpa += NATIVE_DEVICE_OFFSET) अणु
			काष्ठा parisc_device *dev;

			/* Was the device alपढ़ोy added by Firmware? */
			dev = find_device_by_addr(hpa);
			अगर (!dev) अणु
				path.mod = i;
				dev = alloc_pa_dev(hpa, &path);
				अगर (!dev)
					जारी;

				रेजिस्टर_parisc_device(dev);
				devices_found++;
			पूर्ण
			walk_lower_bus(dev);
		पूर्ण
	पूर्ण जबतक(!devices_found && hpa < io_io_high);
पूर्ण

#घोषणा CENTRAL_BUS_ADDR F_EXTEND(0xfff80000)

/**
 * walk_central_bus - Find devices attached to the central bus
 *
 * PDC करोesn't tell us about all devices in the प्रणाली.  This routine
 * finds devices connected to the central bus.
 */
व्योम __init walk_central_bus(व्योम)
अणु
	walk_native_bus(CENTRAL_BUS_ADDR,
			CENTRAL_BUS_ADDR + (MAX_NATIVE_DEVICES * NATIVE_DEVICE_OFFSET),
			&root);
पूर्ण

अटल व्योम prपूर्णांक_parisc_device(काष्ठा parisc_device *dev)
अणु
	अक्षर hw_path[64];
	अटल पूर्णांक count;

	prपूर्णांक_pa_hwpath(dev, hw_path);
	pr_info("%d. %s at %pap [%s] { %d, 0x%x, 0x%.3x, 0x%.5x }",
		++count, dev->name, &(dev->hpa.start), hw_path, dev->id.hw_type,
		dev->id.hversion_rev, dev->id.hversion, dev->id.sversion);

	अगर (dev->num_addrs) अणु
		पूर्णांक k;
		pr_cont(", additional addresses: ");
		क्रम (k = 0; k < dev->num_addrs; k++)
			pr_cont("0x%lx ", dev->addr[k]);
	पूर्ण
	pr_cont("\n");
पूर्ण

/**
 * init_parisc_bus - Some preparation to be करोne beक्रमe inventory
 */
व्योम __init init_parisc_bus(व्योम)
अणु
	अगर (bus_रेजिस्टर(&parisc_bus_type))
		panic("Could not register PA-RISC bus type\n");
	अगर (device_रेजिस्टर(&root))
		panic("Could not register PA-RISC root device\n");
	get_device(&root);
पूर्ण

अटल __init व्योम qemu_header(व्योम)
अणु
	पूर्णांक num;
	अचिन्हित दीर्घ *p;

	pr_info("--- cut here ---\n");
	pr_info("/* AUTO-GENERATED HEADER FILE FOR SEABIOS FIRMWARE */\n");
	pr_cont("/* generated with Linux kernel */\n");
	pr_cont("/* search for PARISC_QEMU_MACHINE_HEADER in Linux */\n\n");

	pr_info("#define PARISC_MODEL \"%s\"\n\n",
			boot_cpu_data.pdc.sys_model_name);

	pr_info("#define PARISC_PDC_MODEL 0x%lx, 0x%lx, 0x%lx, "
		"0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx\n\n",
	#घोषणा p ((अचिन्हित दीर्घ *)&boot_cpu_data.pdc.model)
		p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	#अघोषित p

	pr_info("#define PARISC_PDC_VERSION 0x%04lx\n\n",
			boot_cpu_data.pdc.versions);

	pr_info("#define PARISC_PDC_CPUID 0x%04lx\n\n",
			boot_cpu_data.pdc.cpuid);

	pr_info("#define PARISC_PDC_CAPABILITIES 0x%04lx\n\n",
			boot_cpu_data.pdc.capabilities);

	pr_info("#define PARISC_PDC_ENTRY_ORG 0x%04lx\n\n",
#अगर_घोषित CONFIG_64BIT
		(अचिन्हित दीर्घ)(PAGE0->mem_pdc_hi) << 32 |
#पूर्ण_अगर
		(अचिन्हित दीर्घ)PAGE0->mem_pdc);

	pr_info("#define PARISC_PDC_CACHE_INFO");
	p = (अचिन्हित दीर्घ *) &cache_info;
	क्रम (num = 0; num < माप(cache_info); num += माप(अचिन्हित दीर्घ)) अणु
		अगर (((num % 5) == 0)) अणु
			pr_cont(" \\\n");
			pr_info("\t");
		पूर्ण
		pr_cont("%s0x%04lx",
			num?", ":"", *p++);
	पूर्ण
	pr_cont("\n\n");
पूर्ण

अटल __init पूर्णांक qemu_prपूर्णांक_hpa(काष्ठा device *lin_dev, व्योम *data)
अणु
	काष्ठा parisc_device *dev = to_parisc_device(lin_dev);
	अचिन्हित दीर्घ hpa = dev->hpa.start;

	pr_cont("\t{\t.hpa = 0x%08lx,\\\n", hpa);
	pr_cont("\t\t.iodc = &iodc_data_hpa_%08lx,\\\n", hpa);
	pr_cont("\t\t.mod_info = &mod_info_hpa_%08lx,\\\n", hpa);
	pr_cont("\t\t.mod_path = &mod_path_hpa_%08lx,\\\n", hpa);
	pr_cont("\t\t.num_addr = HPA_%08lx_num_addr,\\\n", hpa);
	pr_cont("\t\t.add_addr = { HPA_%08lx_add_addr } },\\\n", hpa);
	वापस 0;
पूर्ण


अटल __init व्योम qemu_footer(व्योम)
अणु
	pr_info("\n\n#define PARISC_DEVICE_LIST \\\n");
	क्रम_each_padev(qemu_prपूर्णांक_hpa, शून्य);
	pr_cont("\t{ 0, }\n");
	pr_info("--- cut here ---\n");
पूर्ण

/* prपूर्णांक iodc data of the various hpa modules क्रम qemu inclusion */
अटल __init पूर्णांक qemu_prपूर्णांक_iodc_data(काष्ठा device *lin_dev, व्योम *data)
अणु
	काष्ठा parisc_device *dev = to_parisc_device(lin_dev);
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ hpa = dev->hpa.start;
	पूर्णांक status;
	काष्ठा pdc_iodc iodc_data;

	पूर्णांक mod_index;
	काष्ठा pdc_प्रणाली_map_mod_info pdc_mod_info;
	काष्ठा pdc_module_path mod_path;

	status = pdc_iodc_पढ़ो(&count, hpa, 0,
		&iodc_data, माप(iodc_data));
	अगर (status != PDC_OK) अणु
		pr_info("No IODC data for hpa 0x%08lx\n", hpa);
		वापस 0;
	पूर्ण

	pr_info("\n");

	pr_info("#define HPA_%08lx_DESCRIPTION \"%s\"\n",
		hpa, parisc_hardware_description(&dev->id));

	mod_index = 0;
	करो अणु
		status = pdc_प्रणाली_map_find_mods(&pdc_mod_info,
				&mod_path, mod_index++);
	पूर्ण जबतक (status == PDC_OK && pdc_mod_info.mod_addr != hpa);

	pr_info("static struct pdc_system_map_mod_info"
		" mod_info_hpa_%08lx = {\n", hpa);
	#घोषणा DO(member) \
		pr_cont("\t." #member " = 0x%x,\n", \
			(अचिन्हित पूर्णांक)pdc_mod_info.member)
	DO(mod_addr);
	DO(mod_pgs);
	DO(add_addrs);
	pr_cont("};\n");
	#अघोषित DO
	pr_info("static struct pdc_module_path "
		"mod_path_hpa_%08lx = {\n", hpa);
	pr_cont("\t.path = { ");
	pr_cont(".flags = 0x%x, ", mod_path.path.flags);
	pr_cont(".bc = { 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x }, ",
		(अचिन्हित अक्षर)mod_path.path.bc[0],
		(अचिन्हित अक्षर)mod_path.path.bc[1],
		(अचिन्हित अक्षर)mod_path.path.bc[2],
		(अचिन्हित अक्षर)mod_path.path.bc[3],
		(अचिन्हित अक्षर)mod_path.path.bc[4],
		(अचिन्हित अक्षर)mod_path.path.bc[5]);
	pr_cont(".mod = 0x%x ", mod_path.path.mod);
	pr_cont(" },\n");
	pr_cont("\t.layers = { 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x }\n",
		mod_path.layers[0], mod_path.layers[1], mod_path.layers[2],
		mod_path.layers[3], mod_path.layers[4], mod_path.layers[5]);
	pr_cont("};\n");

	pr_info("static struct pdc_iodc iodc_data_hpa_%08lx = {\n", hpa);
	#घोषणा DO(member) \
		pr_cont("\t." #member " = 0x%04lx,\n", \
			(अचिन्हित दीर्घ)iodc_data.member)
	DO(hversion_model);
	DO(hversion);
	DO(spa);
	DO(type);
	DO(sversion_rev);
	DO(sversion_model);
	DO(sversion_opt);
	DO(rev);
	DO(dep);
	DO(features);
	DO(checksum);
	DO(length);
	#अघोषित DO
	pr_cont("\t/* pad: 0x%04x, 0x%04x */\n",
		iodc_data.pad[0], iodc_data.pad[1]);
	pr_cont("};\n");

	pr_info("#define HPA_%08lx_num_addr %d\n", hpa, dev->num_addrs);
	pr_info("#define HPA_%08lx_add_addr ", hpa);
	count = 0;
	अगर (dev->num_addrs == 0)
		pr_cont("0");
	जबतक (count < dev->num_addrs) अणु
		pr_cont("0x%08lx, ", dev->addr[count]);
		count++;
	पूर्ण
	pr_cont("\n\n");

	वापस 0;
पूर्ण



अटल पूर्णांक prपूर्णांक_one_device(काष्ठा device * dev, व्योम * data)
अणु
	काष्ठा parisc_device * pdev = to_parisc_device(dev);

	अगर (check_dev(dev))
		prपूर्णांक_parisc_device(pdev);
	वापस 0;
पूर्ण

/**
 * prपूर्णांक_parisc_devices - Prपूर्णांक out a list of devices found in this प्रणाली
 */
व्योम __init prपूर्णांक_parisc_devices(व्योम)
अणु
	क्रम_each_padev(prपूर्णांक_one_device, शून्य);
	#घोषणा PARISC_QEMU_MACHINE_HEADER 0
	अगर (PARISC_QEMU_MACHINE_HEADER) अणु
		qemu_header();
		क्रम_each_padev(qemu_prपूर्णांक_iodc_data, शून्य);
		qemu_footer();
	पूर्ण
पूर्ण
