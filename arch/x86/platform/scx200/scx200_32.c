<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>
 *
 *  National Semiconductor SCx200 support.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>

#समावेश <linux/scx200.h>
#समावेश <linux/scx200_gpपन.स>

/* Verअगरy that the configuration block really is there */
#घोषणा scx200_cb_probe(base) (inw((base) + SCx200_CBA) == (base))

MODULE_AUTHOR("Christer Weinigel <wingel@nano-system.com>");
MODULE_DESCRIPTION("NatSemi SCx200 Driver");
MODULE_LICENSE("GPL");

अचिन्हित scx200_gpio_base = 0;
अचिन्हित दीर्घ scx200_gpio_shaकरोw[2];

अचिन्हित scx200_cb_base = 0;

अटल काष्ठा pci_device_id scx200_tbl[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SCx200_BRIDGE) पूर्ण,
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SC1100_BRIDGE) पूर्ण,
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SCx200_XBUS)   पूर्ण,
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SC1100_XBUS)   पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci,scx200_tbl);

अटल पूर्णांक scx200_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);

अटल काष्ठा pci_driver scx200_pci_driver = अणु
	.name = "scx200",
	.id_table = scx200_tbl,
	.probe = scx200_probe,
पूर्ण;

अटल DEFINE_MUTEX(scx200_gpio_config_lock);

अटल व्योम scx200_init_shaकरोw(व्योम)
अणु
	पूर्णांक bank;

	/* पढ़ो the current values driven on the GPIO संकेतs */
	क्रम (bank = 0; bank < 2; ++bank)
		scx200_gpio_shaकरोw[bank] = inl(scx200_gpio_base + 0x10 * bank);
पूर्ण

अटल पूर्णांक scx200_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित base;

	अगर (pdev->device == PCI_DEVICE_ID_NS_SCx200_BRIDGE ||
	    pdev->device == PCI_DEVICE_ID_NS_SC1100_BRIDGE) अणु
		base = pci_resource_start(pdev, 0);
		pr_info("GPIO base 0x%x\n", base);

		अगर (!request_region(base, SCx200_GPIO_SIZE,
				    "NatSemi SCx200 GPIO")) अणु
			pr_err("can't allocate I/O for GPIOs\n");
			वापस -EBUSY;
		पूर्ण

		scx200_gpio_base = base;
		scx200_init_shaकरोw();

	पूर्ण अन्यथा अणु
		/* find the base of the Configuration Block */
		अगर (scx200_cb_probe(SCx200_CB_BASE_FIXED)) अणु
			scx200_cb_base = SCx200_CB_BASE_FIXED;
		पूर्ण अन्यथा अणु
			pci_पढ़ो_config_dword(pdev, SCx200_CBA_SCRATCH, &base);
			अगर (scx200_cb_probe(base)) अणु
				scx200_cb_base = base;
			पूर्ण अन्यथा अणु
				pr_warn("Configuration Block not found\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		pr_info("Configuration Block base 0x%x\n", scx200_cb_base);
	पूर्ण

	वापस 0;
पूर्ण

u32 scx200_gpio_configure(अचिन्हित index, u32 mask, u32 bits)
अणु
	u32 config, new_config;

	mutex_lock(&scx200_gpio_config_lock);

	outl(index, scx200_gpio_base + 0x20);
	config = inl(scx200_gpio_base + 0x24);

	new_config = (config & mask) | bits;
	outl(new_config, scx200_gpio_base + 0x24);

	mutex_unlock(&scx200_gpio_config_lock);

	वापस config;
पूर्ण

अटल पूर्णांक __init scx200_init(व्योम)
अणु
	pr_info("NatSemi SCx200 Driver\n");
	वापस pci_रेजिस्टर_driver(&scx200_pci_driver);
पूर्ण

अटल व्योम __निकास scx200_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&scx200_pci_driver);
	release_region(scx200_gpio_base, SCx200_GPIO_SIZE);
पूर्ण

module_init(scx200_init);
module_निकास(scx200_cleanup);

EXPORT_SYMBOL(scx200_gpio_base);
EXPORT_SYMBOL(scx200_gpio_shaकरोw);
EXPORT_SYMBOL(scx200_gpio_configure);
EXPORT_SYMBOL(scx200_cb_base);
