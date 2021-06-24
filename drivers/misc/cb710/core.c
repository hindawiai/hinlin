<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cb710/core.c
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/idr.h>
#समावेश <linux/cb710.h>
#समावेश <linux/gfp.h>

अटल DEFINE_IDA(cb710_ida);

व्योम cb710_pci_update_config_reg(काष्ठा pci_dev *pdev,
	पूर्णांक reg, uपूर्णांक32_t mask, uपूर्णांक32_t xor)
अणु
	u32 rval;

	pci_पढ़ो_config_dword(pdev, reg, &rval);
	rval = (rval & mask) ^ xor;
	pci_ग_लिखो_config_dword(pdev, reg, rval);
पूर्ण
EXPORT_SYMBOL_GPL(cb710_pci_update_config_reg);

/* Some magic ग_लिखोs based on Winकरोws driver init code */
अटल पूर्णांक cb710_pci_configure(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	काष्ठा pci_dev *pdev0;
	u32 val;

	cb710_pci_update_config_reg(pdev, 0x48,
		~0x000000FF, 0x0000003F);

	pci_पढ़ो_config_dword(pdev, 0x48, &val);
	अगर (val & 0x80000000)
		वापस 0;

	pdev0 = pci_get_slot(pdev->bus, devfn);
	अगर (!pdev0)
		वापस -ENODEV;

	अगर (pdev0->venकरोr == PCI_VENDOR_ID_ENE
	    && pdev0->device == PCI_DEVICE_ID_ENE_720) अणु
		cb710_pci_update_config_reg(pdev0, 0x8C,
			~0x00F00000, 0x00100000);
		cb710_pci_update_config_reg(pdev0, 0xB0,
			~0x08000000, 0x08000000);
	पूर्ण

	cb710_pci_update_config_reg(pdev0, 0x8C,
		~0x00000F00, 0x00000200);
	cb710_pci_update_config_reg(pdev0, 0x90,
		~0x00060000, 0x00040000);

	pci_dev_put(pdev0);

	वापस 0;
पूर्ण

अटल irqवापस_t cb710_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cb710_chip *chip = data;
	काष्ठा cb710_slot *slot = &chip->slot[0];
	irqवापस_t handled = IRQ_NONE;
	अचिन्हित nr;

	spin_lock(&chip->irq_lock); /* incl. smp_rmb() */

	क्रम (nr = chip->slots; nr; ++slot, --nr) अणु
		cb710_irq_handler_t handler_func = slot->irq_handler;
		अगर (handler_func && handler_func(slot))
			handled = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&chip->irq_lock);

	वापस handled;
पूर्ण

अटल व्योम cb710_release_slot(काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_CB710_DEBUG_ASSUMPTIONS
	काष्ठा cb710_slot *slot = cb710_pdev_to_slot(to_platक्रमm_device(dev));
	काष्ठा cb710_chip *chip = cb710_slot_to_chip(slot);

	/* slot काष्ठा can be मुक्तd now */
	atomic_dec(&chip->slot_refs_count);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक cb710_रेजिस्टर_slot(काष्ठा cb710_chip *chip,
	अचिन्हित slot_mask, अचिन्हित io_offset, स्थिर अक्षर *name)
अणु
	पूर्णांक nr = chip->slots;
	काष्ठा cb710_slot *slot = &chip->slot[nr];
	पूर्णांक err;

	dev_dbg(cb710_chip_dev(chip),
		"register: %s.%d; slot %d; mask %d; IO offset: 0x%02X\n",
		name, chip->platक्रमm_id, nr, slot_mask, io_offset);

	/* slot->irq_handler == शून्य here; this needs to be
	 * seen beक्रमe platक्रमm_device_रेजिस्टर() */
	++chip->slots;
	smp_wmb();

	slot->iobase = chip->iobase + io_offset;
	slot->pdev.name = name;
	slot->pdev.id = chip->platक्रमm_id;
	slot->pdev.dev.parent = &chip->pdev->dev;
	slot->pdev.dev.release = cb710_release_slot;

	err = platक्रमm_device_रेजिस्टर(&slot->pdev);

#अगर_घोषित CONFIG_CB710_DEBUG_ASSUMPTIONS
	atomic_inc(&chip->slot_refs_count);
#पूर्ण_अगर

	अगर (err) अणु
		/* device_initialize() called from platक्रमm_device_रेजिस्टर()
		 * wants this on error path */
		platक्रमm_device_put(&slot->pdev);

		/* slot->irq_handler == शून्य here anyway, so no lock needed */
		--chip->slots;
		वापस err;
	पूर्ण

	chip->slot_mask |= slot_mask;

	वापस 0;
पूर्ण

अटल व्योम cb710_unरेजिस्टर_slot(काष्ठा cb710_chip *chip,
	अचिन्हित slot_mask)
अणु
	पूर्णांक nr = chip->slots - 1;

	अगर (!(chip->slot_mask & slot_mask))
		वापस;

	platक्रमm_device_unरेजिस्टर(&chip->slot[nr].pdev);

	/* complementary to spin_unlock() in cb710_set_irq_handler() */
	smp_rmb();
	BUG_ON(chip->slot[nr].irq_handler != शून्य);

	/* slot->irq_handler == शून्य here, so no lock needed */
	--chip->slots;
	chip->slot_mask &= ~slot_mask;
पूर्ण

व्योम cb710_set_irq_handler(काष्ठा cb710_slot *slot,
	cb710_irq_handler_t handler)
अणु
	काष्ठा cb710_chip *chip = cb710_slot_to_chip(slot);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->irq_lock, flags);
	slot->irq_handler = handler;
	spin_unlock_irqrestore(&chip->irq_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(cb710_set_irq_handler);

अटल पूर्णांक __maybe_unused cb710_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा cb710_chip *chip = pci_get_drvdata(pdev);

	devm_मुक्त_irq(&pdev->dev, pdev->irq, chip);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cb710_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा cb710_chip *chip = pci_get_drvdata(pdev);

	वापस devm_request_irq(&pdev->dev, pdev->irq,
		cb710_irq_handler, IRQF_SHARED, KBUILD_MODNAME, chip);
पूर्ण

अटल पूर्णांक cb710_probe(काष्ठा pci_dev *pdev,
	स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा cb710_chip *chip;
	u32 val;
	पूर्णांक err;
	पूर्णांक n = 0;

	err = cb710_pci_configure(pdev);
	अगर (err)
		वापस err;

	/* this is actually magic... */
	pci_पढ़ो_config_dword(pdev, 0x48, &val);
	अगर (!(val & 0x80000000)) अणु
		pci_ग_लिखो_config_dword(pdev, 0x48, val|0x71000000);
		pci_पढ़ो_config_dword(pdev, 0x48, &val);
	पूर्ण

	dev_dbg(&pdev->dev, "PCI config[0x48] = 0x%08X\n", val);
	अगर (!(val & 0x70000000))
		वापस -ENODEV;
	val = (val >> 28) & 7;
	अगर (val & CB710_SLOT_MMC)
		++n;
	अगर (val & CB710_SLOT_MS)
		++n;
	अगर (val & CB710_SLOT_SM)
		++n;

	chip = devm_kzalloc(&pdev->dev, काष्ठा_size(chip, slot, n),
			    GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	err = pcim_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pcim_iomap_regions(pdev, 0x0001, KBUILD_MODNAME);
	अगर (err)
		वापस err;

	spin_lock_init(&chip->irq_lock);
	chip->pdev = pdev;
	chip->iobase = pcim_iomap_table(pdev)[0];

	pci_set_drvdata(pdev, chip);

	err = devm_request_irq(&pdev->dev, pdev->irq,
		cb710_irq_handler, IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (err)
		वापस err;

	err = ida_alloc(&cb710_ida, GFP_KERNEL);
	अगर (err < 0)
		वापस err;
	chip->platक्रमm_id = err;

	dev_info(&pdev->dev, "id %d, IO 0x%p, IRQ %d\n",
		chip->platक्रमm_id, chip->iobase, pdev->irq);

	अगर (val & CB710_SLOT_MMC) अणु	/* MMC/SD slot */
		err = cb710_रेजिस्टर_slot(chip,
			CB710_SLOT_MMC, 0x00, "cb710-mmc");
		अगर (err)
			वापस err;
	पूर्ण

	अगर (val & CB710_SLOT_MS) अणु	/* MemoryStick slot */
		err = cb710_रेजिस्टर_slot(chip,
			CB710_SLOT_MS, 0x40, "cb710-ms");
		अगर (err)
			जाओ unreg_mmc;
	पूर्ण

	अगर (val & CB710_SLOT_SM) अणु	/* SmartMedia slot */
		err = cb710_रेजिस्टर_slot(chip,
			CB710_SLOT_SM, 0x60, "cb710-sm");
		अगर (err)
			जाओ unreg_ms;
	पूर्ण

	वापस 0;
unreg_ms:
	cb710_unरेजिस्टर_slot(chip, CB710_SLOT_MS);
unreg_mmc:
	cb710_unरेजिस्टर_slot(chip, CB710_SLOT_MMC);

#अगर_घोषित CONFIG_CB710_DEBUG_ASSUMPTIONS
	BUG_ON(atomic_पढ़ो(&chip->slot_refs_count) != 0);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम cb710_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cb710_chip *chip = pci_get_drvdata(pdev);

	cb710_unरेजिस्टर_slot(chip, CB710_SLOT_SM);
	cb710_unरेजिस्टर_slot(chip, CB710_SLOT_MS);
	cb710_unरेजिस्टर_slot(chip, CB710_SLOT_MMC);
#अगर_घोषित CONFIG_CB710_DEBUG_ASSUMPTIONS
	BUG_ON(atomic_पढ़ो(&chip->slot_refs_count) != 0);
#पूर्ण_अगर

	ida_मुक्त(&cb710_ida, chip->platक्रमm_id);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cb710_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_CB710_FLASH,
		PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(cb710_pm_ops, cb710_suspend, cb710_resume);

अटल काष्ठा pci_driver cb710_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = cb710_pci_tbl,
	.probe = cb710_probe,
	.हटाओ = cb710_हटाओ_one,
	.driver.pm = &cb710_pm_ops,
पूर्ण;

अटल पूर्णांक __init cb710_init_module(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&cb710_driver);
पूर्ण

अटल व्योम __निकास cb710_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cb710_driver);
	ida_destroy(&cb710_ida);
पूर्ण

module_init(cb710_init_module);
module_निकास(cb710_cleanup_module);

MODULE_AUTHOR("Michaध Mirosधaw <mirq-linux@rere.qmqm.pl>");
MODULE_DESCRIPTION("ENE CB710 memory card reader driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cb710_pci_tbl);
