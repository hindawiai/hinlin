<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  lpc_sch.c - LPC पूर्णांकerface क्रम Intel Poulsbo SCH
 *
 *  LPC bridge function of the Intel SCH contains many other
 *  functional units, such as Interrupt controllers, Timers,
 *  Power Management, System Management, GPIO, RTC, and LPC
 *  Configuration Registers.
 *
 *  Copyright (c) 2010 CompuLab Ltd
 *  Copyright (c) 2014 Intel Corp.
 *  Author: Denis Turischev <denis@compulab.co.il>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/mfd/core.h>

#घोषणा SMBASE		0x40
#घोषणा SMBUS_IO_SIZE	64

#घोषणा GPIOBASE	0x44
#घोषणा GPIO_IO_SIZE	64
#घोषणा GPIO_IO_SIZE_CENTERTON	128

#घोषणा WDTBASE		0x84
#घोषणा WDT_IO_SIZE	64

क्रमागत sch_chipsets अणु
	LPC_SCH = 0,		/* Intel Poulsbo SCH */
	LPC_ITC,		/* Intel Tunnel Creek */
	LPC_CENTERTON,		/* Intel Centerton */
	LPC_QUARK_X1000,	/* Intel Quark X1000 */
पूर्ण;

काष्ठा lpc_sch_info अणु
	अचिन्हित पूर्णांक io_size_smbus;
	अचिन्हित पूर्णांक io_size_gpio;
	अचिन्हित पूर्णांक io_size_wdt;
पूर्ण;

अटल काष्ठा lpc_sch_info sch_chipset_info[] = अणु
	[LPC_SCH] = अणु
		.io_size_smbus = SMBUS_IO_SIZE,
		.io_size_gpio = GPIO_IO_SIZE,
	पूर्ण,
	[LPC_ITC] = अणु
		.io_size_smbus = SMBUS_IO_SIZE,
		.io_size_gpio = GPIO_IO_SIZE,
		.io_size_wdt = WDT_IO_SIZE,
	पूर्ण,
	[LPC_CENTERTON] = अणु
		.io_size_smbus = SMBUS_IO_SIZE,
		.io_size_gpio = GPIO_IO_SIZE_CENTERTON,
		.io_size_wdt = WDT_IO_SIZE,
	पूर्ण,
	[LPC_QUARK_X1000] = अणु
		.io_size_gpio = GPIO_IO_SIZE,
		.io_size_wdt = WDT_IO_SIZE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id lpc_sch_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_SCH_LPC), LPC_SCH पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ITC_LPC), LPC_ITC पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CENTERTON_ILB), LPC_CENTERTON पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_QUARK_X1000_ILB), LPC_QUARK_X1000 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, lpc_sch_ids);

#घोषणा LPC_NO_RESOURCE		1
#घोषणा LPC_SKIP_RESOURCE	2

अटल पूर्णांक lpc_sch_get_io(काष्ठा pci_dev *pdev, पूर्णांक where, स्थिर अक्षर *name,
			  काष्ठा resource *res, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक base_addr_cfg;
	अचिन्हित लघु base_addr;

	अगर (size == 0)
		वापस LPC_NO_RESOURCE;

	pci_पढ़ो_config_dword(pdev, where, &base_addr_cfg);
	base_addr = 0;
	अगर (!(base_addr_cfg & (1 << 31)))
		dev_warn(&pdev->dev, "Decode of the %s I/O range disabled\n",
			 name);
	अन्यथा
		base_addr = (अचिन्हित लघु)base_addr_cfg;

	अगर (base_addr == 0) अणु
		dev_warn(&pdev->dev, "I/O space for %s uninitialized\n", name);
		वापस LPC_SKIP_RESOURCE;
	पूर्ण

	res->start = base_addr;
	res->end = base_addr + size - 1;
	res->flags = IORESOURCE_IO;

	वापस 0;
पूर्ण

अटल पूर्णांक lpc_sch_populate_cell(काष्ठा pci_dev *pdev, पूर्णांक where,
				 स्थिर अक्षर *name, पूर्णांक size, पूर्णांक id,
				 काष्ठा mfd_cell *cell)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	res = devm_kzalloc(&pdev->dev, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	ret = lpc_sch_get_io(pdev, where, name, res, size);
	अगर (ret)
		वापस ret;

	स_रखो(cell, 0, माप(*cell));

	cell->name = name;
	cell->resources = res;
	cell->num_resources = 1;
	cell->ignore_resource_conflicts = true;
	cell->id = id;

	वापस 0;
पूर्ण

अटल पूर्णांक lpc_sch_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mfd_cell lpc_sch_cells[3];
	काष्ठा lpc_sch_info *info = &sch_chipset_info[id->driver_data];
	अचिन्हित पूर्णांक cells = 0;
	पूर्णांक ret;

	ret = lpc_sch_populate_cell(dev, SMBASE, "isch_smbus",
				    info->io_size_smbus,
				    id->device, &lpc_sch_cells[cells]);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		cells++;

	ret = lpc_sch_populate_cell(dev, GPIOBASE, "sch_gpio",
				    info->io_size_gpio,
				    id->device, &lpc_sch_cells[cells]);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		cells++;

	ret = lpc_sch_populate_cell(dev, WDTBASE, "ie6xx_wdt",
				    info->io_size_wdt,
				    id->device, &lpc_sch_cells[cells]);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		cells++;

	अगर (cells == 0) अणु
		dev_err(&dev->dev, "All decode registers disabled.\n");
		वापस -ENODEV;
	पूर्ण

	वापस mfd_add_devices(&dev->dev, 0, lpc_sch_cells, cells, शून्य, 0, शून्य);
पूर्ण

अटल व्योम lpc_sch_हटाओ(काष्ठा pci_dev *dev)
अणु
	mfd_हटाओ_devices(&dev->dev);
पूर्ण

अटल काष्ठा pci_driver lpc_sch_driver = अणु
	.name		= "lpc_sch",
	.id_table	= lpc_sch_ids,
	.probe		= lpc_sch_probe,
	.हटाओ		= lpc_sch_हटाओ,
पूर्ण;

module_pci_driver(lpc_sch_driver);

MODULE_AUTHOR("Denis Turischev <denis@compulab.co.il>");
MODULE_DESCRIPTION("LPC interface for Intel Poulsbo SCH");
MODULE_LICENSE("GPL");
