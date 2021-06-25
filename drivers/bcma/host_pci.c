<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * PCI Host
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/slab.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>

अटल व्योम bcma_host_pci_चयन_core(काष्ठा bcma_device *core)
अणु
	पूर्णांक win2 = core->bus->host_is_pcie2 ?
		BCMA_PCIE2_BAR0_WIN2 : BCMA_PCI_BAR0_WIN2;

	pci_ग_लिखो_config_dword(core->bus->host_pci, BCMA_PCI_BAR0_WIN,
			       core->addr);
	pci_ग_लिखो_config_dword(core->bus->host_pci, win2, core->wrap);
	core->bus->mapped_core = core;
	bcma_debug(core->bus, "Switched to core: 0x%X\n", core->id.id);
पूर्ण

/* Provides access to the requested core. Returns base offset that has to be
 * used. It makes use of fixed winकरोws when possible. */
अटल u16 bcma_host_pci_provide_access_to_core(काष्ठा bcma_device *core)
अणु
	चयन (core->id.id) अणु
	हाल BCMA_CORE_CHIPCOMMON:
		वापस 3 * BCMA_CORE_SIZE;
	हाल BCMA_CORE_PCIE:
		वापस 2 * BCMA_CORE_SIZE;
	पूर्ण

	अगर (core->bus->mapped_core != core)
		bcma_host_pci_चयन_core(core);
	वापस 0;
पूर्ण

अटल u8 bcma_host_pci_पढ़ो8(काष्ठा bcma_device *core, u16 offset)
अणु
	offset += bcma_host_pci_provide_access_to_core(core);
	वापस ioपढ़ो8(core->bus->mmio + offset);
पूर्ण

अटल u16 bcma_host_pci_पढ़ो16(काष्ठा bcma_device *core, u16 offset)
अणु
	offset += bcma_host_pci_provide_access_to_core(core);
	वापस ioपढ़ो16(core->bus->mmio + offset);
पूर्ण

अटल u32 bcma_host_pci_पढ़ो32(काष्ठा bcma_device *core, u16 offset)
अणु
	offset += bcma_host_pci_provide_access_to_core(core);
	वापस ioपढ़ो32(core->bus->mmio + offset);
पूर्ण

अटल व्योम bcma_host_pci_ग_लिखो8(काष्ठा bcma_device *core, u16 offset,
				 u8 value)
अणु
	offset += bcma_host_pci_provide_access_to_core(core);
	ioग_लिखो8(value, core->bus->mmio + offset);
पूर्ण

अटल व्योम bcma_host_pci_ग_लिखो16(काष्ठा bcma_device *core, u16 offset,
				 u16 value)
अणु
	offset += bcma_host_pci_provide_access_to_core(core);
	ioग_लिखो16(value, core->bus->mmio + offset);
पूर्ण

अटल व्योम bcma_host_pci_ग_लिखो32(काष्ठा bcma_device *core, u16 offset,
				 u32 value)
अणु
	offset += bcma_host_pci_provide_access_to_core(core);
	ioग_लिखो32(value, core->bus->mmio + offset);
पूर्ण

#अगर_घोषित CONFIG_BCMA_BLOCKIO
अटल व्योम bcma_host_pci_block_पढ़ो(काष्ठा bcma_device *core, व्योम *buffer,
				     माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	व्योम __iomem *addr = core->bus->mmio + offset;
	अगर (core->bus->mapped_core != core)
		bcma_host_pci_चयन_core(core);
	चयन (reg_width) अणु
	हाल माप(u8):
		ioपढ़ो8_rep(addr, buffer, count);
		अवरोध;
	हाल माप(u16):
		WARN_ON(count & 1);
		ioपढ़ो16_rep(addr, buffer, count >> 1);
		अवरोध;
	हाल माप(u32):
		WARN_ON(count & 3);
		ioपढ़ो32_rep(addr, buffer, count >> 2);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम bcma_host_pci_block_ग_लिखो(काष्ठा bcma_device *core,
				      स्थिर व्योम *buffer, माप_प्रकार count,
				      u16 offset, u8 reg_width)
अणु
	व्योम __iomem *addr = core->bus->mmio + offset;
	अगर (core->bus->mapped_core != core)
		bcma_host_pci_चयन_core(core);
	चयन (reg_width) अणु
	हाल माप(u8):
		ioग_लिखो8_rep(addr, buffer, count);
		अवरोध;
	हाल माप(u16):
		WARN_ON(count & 1);
		ioग_लिखो16_rep(addr, buffer, count >> 1);
		अवरोध;
	हाल माप(u32):
		WARN_ON(count & 3);
		ioग_लिखो32_rep(addr, buffer, count >> 2);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल u32 bcma_host_pci_aपढ़ो32(काष्ठा bcma_device *core, u16 offset)
अणु
	अगर (core->bus->mapped_core != core)
		bcma_host_pci_चयन_core(core);
	वापस ioपढ़ो32(core->bus->mmio + (1 * BCMA_CORE_SIZE) + offset);
पूर्ण

अटल व्योम bcma_host_pci_aग_लिखो32(काष्ठा bcma_device *core, u16 offset,
				  u32 value)
अणु
	अगर (core->bus->mapped_core != core)
		bcma_host_pci_चयन_core(core);
	ioग_लिखो32(value, core->bus->mmio + (1 * BCMA_CORE_SIZE) + offset);
पूर्ण

अटल स्थिर काष्ठा bcma_host_ops bcma_host_pci_ops = अणु
	.पढ़ो8		= bcma_host_pci_पढ़ो8,
	.पढ़ो16		= bcma_host_pci_पढ़ो16,
	.पढ़ो32		= bcma_host_pci_पढ़ो32,
	.ग_लिखो8		= bcma_host_pci_ग_लिखो8,
	.ग_लिखो16	= bcma_host_pci_ग_लिखो16,
	.ग_लिखो32	= bcma_host_pci_ग_लिखो32,
#अगर_घोषित CONFIG_BCMA_BLOCKIO
	.block_पढ़ो	= bcma_host_pci_block_पढ़ो,
	.block_ग_लिखो	= bcma_host_pci_block_ग_लिखो,
#पूर्ण_अगर
	.aपढ़ो32	= bcma_host_pci_aपढ़ो32,
	.aग_लिखो32	= bcma_host_pci_aग_लिखो32,
पूर्ण;

अटल पूर्णांक bcma_host_pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा bcma_bus *bus;
	पूर्णांक err = -ENOMEM;
	स्थिर अक्षर *name;
	u32 val;

	/* Alloc */
	bus = kzalloc(माप(*bus), GFP_KERNEL);
	अगर (!bus)
		जाओ out;

	/* Basic PCI configuration */
	err = pci_enable_device(dev);
	अगर (err)
		जाओ err_kमुक्त_bus;

	name = dev_name(&dev->dev);
	अगर (dev->driver && dev->driver->name)
		name = dev->driver->name;
	err = pci_request_regions(dev, name);
	अगर (err)
		जाओ err_pci_disable;
	pci_set_master(dev);

	/* Disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_पढ़ो_config_dword(dev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(dev, 0x40, val & 0xffff00ff);

	/* SSB needed additional घातering up, करो we have any AMBA PCI cards? */
	अगर (!pci_is_pcie(dev)) अणु
		bcma_err(bus, "PCI card detected, they are not supported.\n");
		err = -ENXIO;
		जाओ err_pci_release_regions;
	पूर्ण

	bus->dev = &dev->dev;

	/* Map MMIO */
	err = -ENOMEM;
	bus->mmio = pci_iomap(dev, 0, ~0UL);
	अगर (!bus->mmio)
		जाओ err_pci_release_regions;

	/* Host specअगरic */
	bus->host_pci = dev;
	bus->hosttype = BCMA_HOSTTYPE_PCI;
	bus->ops = &bcma_host_pci_ops;

	bus->boardinfo.venकरोr = bus->host_pci->subप्रणाली_venकरोr;
	bus->boardinfo.type = bus->host_pci->subप्रणाली_device;

	/* Initialize काष्ठा, detect chip */
	bcma_init_bus(bus);

	/* Scan bus to find out generation of PCIe core */
	err = bcma_bus_scan(bus);
	अगर (err)
		जाओ err_pci_unmap_mmio;

	अगर (bcma_find_core(bus, BCMA_CORE_PCIE2))
		bus->host_is_pcie2 = true;

	/* Register */
	err = bcma_bus_रेजिस्टर(bus);
	अगर (err)
		जाओ err_unरेजिस्टर_cores;

	pci_set_drvdata(dev, bus);

out:
	वापस err;

err_unरेजिस्टर_cores:
	bcma_unरेजिस्टर_cores(bus);
err_pci_unmap_mmio:
	pci_iounmap(dev, bus->mmio);
err_pci_release_regions:
	pci_release_regions(dev);
err_pci_disable:
	pci_disable_device(dev);
err_kमुक्त_bus:
	kमुक्त(bus);
	वापस err;
पूर्ण

अटल व्योम bcma_host_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा bcma_bus *bus = pci_get_drvdata(dev);

	bcma_bus_unरेजिस्टर(bus);
	pci_iounmap(dev, bus->mmio);
	pci_release_regions(dev);
	pci_disable_device(dev);
	kमुक्त(bus);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bcma_host_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा bcma_bus *bus = dev_get_drvdata(dev);

	bus->mapped_core = शून्य;

	वापस bcma_bus_suspend(bus);
पूर्ण

अटल पूर्णांक bcma_host_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा bcma_bus *bus = dev_get_drvdata(dev);

	वापस bcma_bus_resume(bus);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bcma_pm_ops, bcma_host_pci_suspend,
			 bcma_host_pci_resume);
#घोषणा BCMA_PM_OPS	(&bcma_pm_ops)

#अन्यथा /* CONFIG_PM_SLEEP */

#घोषणा BCMA_PM_OPS     शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा pci_device_id bcma_pci_bridge_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x0576) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4313) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 43224) पूर्ण,	/* 0xa8d8 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4331) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4353) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4357) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4358) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4359) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4360) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, 0x4365, PCI_VENDOR_ID_DELL, 0x0016) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, 0x4365, PCI_VENDOR_ID_DELL, 0x0018) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, 0x4365, PCI_VENDOR_ID_FOXCONN, 0xe092) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, 0x4365, PCI_VENDOR_ID_HP, 0x804a) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x43a0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x43a9) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x43aa) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x43b1) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4727) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 43227) पूर्ण,	/* 0xa8db, BCM43217 (sic!) */
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 43228) पूर्ण,	/* 0xa8dc */
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, bcma_pci_bridge_tbl);

अटल काष्ठा pci_driver bcma_pci_bridge_driver = अणु
	.name = "bcma-pci-bridge",
	.id_table = bcma_pci_bridge_tbl,
	.probe = bcma_host_pci_probe,
	.हटाओ = bcma_host_pci_हटाओ,
	.driver.pm = BCMA_PM_OPS,
पूर्ण;

पूर्णांक __init bcma_host_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&bcma_pci_bridge_driver);
पूर्ण

व्योम __निकास bcma_host_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bcma_pci_bridge_driver);
पूर्ण

/**************************************************
 * Runसमय ops क्रम drivers.
 **************************************************/

/* See also pcicore_up */
व्योम bcma_host_pci_up(काष्ठा bcma_bus *bus)
अणु
	अगर (bus->hosttype != BCMA_HOSTTYPE_PCI)
		वापस;

	अगर (bus->host_is_pcie2)
		bcma_core_pcie2_up(&bus->drv_pcie2);
	अन्यथा
		bcma_core_pci_up(&bus->drv_pci[0]);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_host_pci_up);

/* See also pcicore_करोwn */
व्योम bcma_host_pci_करोwn(काष्ठा bcma_bus *bus)
अणु
	अगर (bus->hosttype != BCMA_HOSTTYPE_PCI)
		वापस;

	अगर (!bus->host_is_pcie2)
		bcma_core_pci_करोwn(&bus->drv_pci[0]);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_host_pci_करोwn);

/* See also si_pci_setup */
पूर्णांक bcma_host_pci_irq_ctl(काष्ठा bcma_bus *bus, काष्ठा bcma_device *core,
			  bool enable)
अणु
	काष्ठा pci_dev *pdev;
	u32 coremask, पंचांगp;
	पूर्णांक err = 0;

	अगर (bus->hosttype != BCMA_HOSTTYPE_PCI) अणु
		/* This bcma device is not on a PCI host-bus. So the IRQs are
		 * not routed through the PCI core.
		 * So we must not enable routing through the PCI core. */
		जाओ out;
	पूर्ण

	pdev = bus->host_pci;

	err = pci_पढ़ो_config_dword(pdev, BCMA_PCI_IRQMASK, &पंचांगp);
	अगर (err)
		जाओ out;

	coremask = BIT(core->core_index) << 8;
	अगर (enable)
		पंचांगp |= coremask;
	अन्यथा
		पंचांगp &= ~coremask;

	err = pci_ग_लिखो_config_dword(pdev, BCMA_PCI_IRQMASK, पंचांगp);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_host_pci_irq_ctl);
