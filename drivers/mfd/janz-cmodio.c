<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Janz CMOD-IO MODULbus Carrier Board PCI Driver
 *
 * Copyright (c) 2010 Ira W. Snyder <iws@ovro.caltech.edu>
 *
 * Lots of inspiration and code was copied from drivers/mfd/sm501.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/core.h>

#समावेश <linux/mfd/janz.h>

#घोषणा DRV_NAME "janz-cmodio"

/* Size of each MODULbus module in PCI BAR4 */
#घोषणा CMODIO_MODULBUS_SIZE	0x200

/* Maximum number of MODULbus modules on a CMOD-IO carrier board */
#घोषणा CMODIO_MAX_MODULES	4

/* Module Parameters */
अटल अचिन्हित पूर्णांक num_modules = CMODIO_MAX_MODULES;
अटल अक्षर *modules[CMODIO_MAX_MODULES] = अणु
	"empty", "empty", "empty", "empty",
पूर्ण;

module_param_array(modules, अक्षरp, &num_modules, S_IRUGO);
MODULE_PARM_DESC(modules, "MODULbus modules attached to the carrier board");

/* Unique Device Id */
अटल अचिन्हित पूर्णांक cmodio_id;

काष्ठा cmodio_device अणु
	/* Parent PCI device */
	काष्ठा pci_dev *pdev;

	/* PLX control रेजिस्टरs */
	काष्ठा janz_cmodio_onboard_regs __iomem *ctrl;

	/* hex चयन position */
	u8 hex;

	/* mfd-core API */
	काष्ठा mfd_cell cells[CMODIO_MAX_MODULES];
	काष्ठा resource resources[3 * CMODIO_MAX_MODULES];
	काष्ठा janz_platक्रमm_data pdata[CMODIO_MAX_MODULES];
पूर्ण;

/*
 * Subdevices using the mfd-core API
 */

अटल पूर्णांक cmodio_setup_subdevice(काष्ठा cmodio_device *priv,
					    अक्षर *name, अचिन्हित पूर्णांक devno,
					    अचिन्हित पूर्णांक modno)
अणु
	काष्ठा janz_platक्रमm_data *pdata;
	काष्ठा mfd_cell *cell;
	काष्ठा resource *res;
	काष्ठा pci_dev *pci;

	pci = priv->pdev;
	cell = &priv->cells[devno];
	res = &priv->resources[devno * 3];
	pdata = &priv->pdata[devno];

	cell->name = name;
	cell->resources = res;
	cell->num_resources = 3;

	/* Setup the subdevice ID -- must be unique */
	cell->id = cmodio_id++;

	/* Add platक्रमm data */
	pdata->modno = modno;
	cell->platक्रमm_data = pdata;
	cell->pdata_size = माप(*pdata);

	/* MODULbus रेजिस्टरs -- PCI BAR3 is big-endian MODULbus access */
	res->flags = IORESOURCE_MEM;
	res->parent = &pci->resource[3];
	res->start = pci->resource[3].start + (CMODIO_MODULBUS_SIZE * modno);
	res->end = res->start + CMODIO_MODULBUS_SIZE - 1;
	res++;

	/* PLX Control Registers -- PCI BAR4 is पूर्णांकerrupt and other रेजिस्टरs */
	res->flags = IORESOURCE_MEM;
	res->parent = &pci->resource[4];
	res->start = pci->resource[4].start;
	res->end = pci->resource[4].end;
	res++;

	/*
	 * IRQ
	 *
	 * The start and end fields are used as an offset to the irq_base
	 * parameter passed पूर्णांकo the mfd_add_devices() function call. All
	 * devices share the same IRQ.
	 */
	res->flags = IORESOURCE_IRQ;
	res->parent = शून्य;
	res->start = 0;
	res->end = 0;
	res++;

	वापस 0;
पूर्ण

/* Probe each submodule using kernel parameters */
अटल पूर्णांक cmodio_probe_submodules(काष्ठा cmodio_device *priv)
अणु
	काष्ठा pci_dev *pdev = priv->pdev;
	अचिन्हित पूर्णांक num_probed = 0;
	अक्षर *name;
	पूर्णांक i;

	क्रम (i = 0; i < num_modules; i++) अणु
		name = modules[i];
		अगर (!म_भेद(name, "") || !म_भेद(name, "empty"))
			जारी;

		dev_dbg(&priv->pdev->dev, "MODULbus %d: name %s\n", i, name);
		cmodio_setup_subdevice(priv, name, num_probed, i);
		num_probed++;
	पूर्ण

	/* prपूर्णांक an error message अगर no modules were probed */
	अगर (num_probed == 0) अणु
		dev_err(&priv->pdev->dev, "no MODULbus modules specified, "
					  "please set the ``modules'' kernel "
					  "parameter according to your "
					  "hardware configuration\n");
		वापस -ENODEV;
	पूर्ण

	वापस mfd_add_devices(&pdev->dev, 0, priv->cells,
			       num_probed, शून्य, pdev->irq, शून्य);
पूर्ण

/*
 * SYSFS Attributes
 */

अटल sमाप_प्रकार mbus_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा cmodio_device *priv = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", priv->hex);
पूर्ण

अटल DEVICE_ATTR(modulbus_number, S_IRUGO, mbus_show, शून्य);

अटल काष्ठा attribute *cmodio_sysfs_attrs[] = अणु
	&dev_attr_modulbus_number.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cmodio_sysfs_attr_group = अणु
	.attrs = cmodio_sysfs_attrs,
पूर्ण;

/*
 * PCI Driver
 */

अटल पूर्णांक cmodio_pci_probe(काष्ठा pci_dev *dev,
				      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा cmodio_device *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	pci_set_drvdata(dev, priv);
	priv->pdev = dev;

	/* Hardware Initialization */
	ret = pci_enable_device(dev);
	अगर (ret) अणु
		dev_err(&dev->dev, "unable to enable device\n");
		वापस ret;
	पूर्ण

	pci_set_master(dev);
	ret = pci_request_regions(dev, DRV_NAME);
	अगर (ret) अणु
		dev_err(&dev->dev, "unable to request regions\n");
		जाओ out_pci_disable_device;
	पूर्ण

	/* Onboard configuration रेजिस्टरs */
	priv->ctrl = pci_ioremap_bar(dev, 4);
	अगर (!priv->ctrl) अणु
		dev_err(&dev->dev, "unable to remap onboard regs\n");
		ret = -ENOMEM;
		जाओ out_pci_release_regions;
	पूर्ण

	/* Read the hex चयन on the carrier board */
	priv->hex = ioपढ़ो8(&priv->ctrl->पूर्णांक_enable);

	/* Add the MODULbus number (hex चयन value) to the device's sysfs */
	ret = sysfs_create_group(&dev->dev.kobj, &cmodio_sysfs_attr_group);
	अगर (ret) अणु
		dev_err(&dev->dev, "unable to create sysfs attributes\n");
		जाओ out_unmap_ctrl;
	पूर्ण

	/*
	 * Disable all पूर्णांकerrupt lines, each submodule will enable its
	 * own पूर्णांकerrupt line अगर needed
	 */
	ioग_लिखो8(0xf, &priv->ctrl->पूर्णांक_disable);

	/* Register drivers क्रम all submodules */
	ret = cmodio_probe_submodules(priv);
	अगर (ret) अणु
		dev_err(&dev->dev, "unable to probe submodules\n");
		जाओ out_sysfs_हटाओ_group;
	पूर्ण

	वापस 0;

out_sysfs_हटाओ_group:
	sysfs_हटाओ_group(&dev->dev.kobj, &cmodio_sysfs_attr_group);
out_unmap_ctrl:
	iounmap(priv->ctrl);
out_pci_release_regions:
	pci_release_regions(dev);
out_pci_disable_device:
	pci_disable_device(dev);

	वापस ret;
पूर्ण

अटल व्योम cmodio_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा cmodio_device *priv = pci_get_drvdata(dev);

	mfd_हटाओ_devices(&dev->dev);
	sysfs_हटाओ_group(&dev->dev.kobj, &cmodio_sysfs_attr_group);
	iounmap(priv->ctrl);
	pci_release_regions(dev);
	pci_disable_device(dev);
पूर्ण

#घोषणा PCI_VENDOR_ID_JANZ		0x13c3

/* The list of devices that this module will support */
अटल स्थिर काष्ठा pci_device_id cmodio_pci_ids[] = अणु
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_JANZ, 0x0101 पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050, PCI_VENDOR_ID_JANZ, 0x0100 पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_JANZ, 0x0201 पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_JANZ, 0x0202 पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050, PCI_VENDOR_ID_JANZ, 0x0201 पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050, PCI_VENDOR_ID_JANZ, 0x0202 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cmodio_pci_ids);

अटल काष्ठा pci_driver cmodio_pci_driver = अणु
	.name     = DRV_NAME,
	.id_table = cmodio_pci_ids,
	.probe    = cmodio_pci_probe,
	.हटाओ   = cmodio_pci_हटाओ,
पूर्ण;

module_pci_driver(cmodio_pci_driver);

MODULE_AUTHOR("Ira W. Snyder <iws@ovro.caltech.edu>");
MODULE_DESCRIPTION("Janz CMOD-IO PCI MODULbus Carrier Board Driver");
MODULE_LICENSE("GPL");
