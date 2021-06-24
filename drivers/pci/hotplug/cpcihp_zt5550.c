<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cpcihp_zt5550.c
 *
 * Intel/Ziatech ZT5550 CompactPCI Host Controller driver
 *
 * Copyright 2002 SOMA Networks, Inc.
 * Copyright 2001 Intel San Luis Obispo
 * Copyright 2000,2001 MontaVista Software Inc.
 *
 * Send feedback to <scotपंचांग@somanetworks.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/संकेत.स>	/* IRQF_SHARED */
#समावेश "cpci_hotplug.h"
#समावेश "cpcihp_zt5550.h"

#घोषणा DRIVER_VERSION	"0.2"
#घोषणा DRIVER_AUTHOR	"Scott Murray <scottm@somanetworks.com>"
#घोषणा DRIVER_DESC	"ZT5550 CompactPCI Hot Plug Driver"

#घोषणा MY_NAME	"cpcihp_zt5550"

#घोषणा dbg(क्रमmat, arg...)					\
	करो अणु							\
		अगर (debug)					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n",	\
				MY_NAME, ## arg);		\
	पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat "\n", MY_NAME, ## arg)

/* local variables */
अटल bool debug;
अटल bool poll;
अटल काष्ठा cpci_hp_controller_ops zt5550_hpc_ops;
अटल काष्ठा cpci_hp_controller zt5550_hpc;

/* Primary cPCI bus bridge device */
अटल काष्ठा pci_dev *bus0_dev;
अटल काष्ठा pci_bus *bus0;

/* Host controller device */
अटल काष्ठा pci_dev *hc_dev;

/* Host controller रेजिस्टर addresses */
अटल व्योम __iomem *hc_रेजिस्टरs;
अटल व्योम __iomem *csr_hc_index;
अटल व्योम __iomem *csr_hc_data;
अटल व्योम __iomem *csr_पूर्णांक_status;
अटल व्योम __iomem *csr_पूर्णांक_mask;


अटल पूर्णांक zt5550_hc_config(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	/* Since we know that no boards exist with two HC chips, treat it as an error */
	अगर (hc_dev) अणु
		err("too many host controller devices?");
		वापस -EBUSY;
	पूर्ण

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		err("cannot enable %s\n", pci_name(pdev));
		वापस ret;
	पूर्ण

	hc_dev = pdev;
	dbg("hc_dev = %p", hc_dev);
	dbg("pci resource start %llx", (अचिन्हित दीर्घ दीर्घ)pci_resource_start(hc_dev, 1));
	dbg("pci resource len %llx", (अचिन्हित दीर्घ दीर्घ)pci_resource_len(hc_dev, 1));

	अगर (!request_mem_region(pci_resource_start(hc_dev, 1),
				pci_resource_len(hc_dev, 1), MY_NAME)) अणु
		err("cannot reserve MMIO region");
		ret = -ENOMEM;
		जाओ निकास_disable_device;
	पूर्ण

	hc_रेजिस्टरs =
	    ioremap(pci_resource_start(hc_dev, 1), pci_resource_len(hc_dev, 1));
	अगर (!hc_रेजिस्टरs) अणु
		err("cannot remap MMIO region %llx @ %llx",
			(अचिन्हित दीर्घ दीर्घ)pci_resource_len(hc_dev, 1),
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(hc_dev, 1));
		ret = -ENODEV;
		जाओ निकास_release_region;
	पूर्ण

	csr_hc_index = hc_रेजिस्टरs + CSR_HCINDEX;
	csr_hc_data = hc_रेजिस्टरs + CSR_HCDATA;
	csr_पूर्णांक_status = hc_रेजिस्टरs + CSR_INTSTAT;
	csr_पूर्णांक_mask = hc_रेजिस्टरs + CSR_INTMASK;

	/*
	 * Disable host control, fault and serial पूर्णांकerrupts
	 */
	dbg("disabling host control, fault and serial interrupts");
	ग_लिखोb((u8) HC_INT_MASK_REG, csr_hc_index);
	ग_लिखोb((u8) ALL_INDEXED_INTS_MASK, csr_hc_data);
	dbg("disabled host control, fault and serial interrupts");

	/*
	 * Disable समयr0, समयr1 and ENUM पूर्णांकerrupts
	 */
	dbg("disabling timer0, timer1 and ENUM interrupts");
	ग_लिखोb((u8) ALL_सूचीECT_INTS_MASK, csr_पूर्णांक_mask);
	dbg("disabled timer0, timer1 and ENUM interrupts");
	वापस 0;

निकास_release_region:
	release_mem_region(pci_resource_start(hc_dev, 1),
			   pci_resource_len(hc_dev, 1));
निकास_disable_device:
	pci_disable_device(hc_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक zt5550_hc_cleanup(व्योम)
अणु
	अगर (!hc_dev)
		वापस -ENODEV;

	iounmap(hc_रेजिस्टरs);
	release_mem_region(pci_resource_start(hc_dev, 1),
			   pci_resource_len(hc_dev, 1));
	pci_disable_device(hc_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक zt5550_hc_query_क्रमागत(व्योम)
अणु
	u8 value;

	value = inb_p(ENUM_PORT);
	वापस ((value & ENUM_MASK) == ENUM_MASK);
पूर्ण

अटल पूर्णांक zt5550_hc_check_irq(व्योम *dev_id)
अणु
	पूर्णांक ret;
	u8 reg;

	ret = 0;
	अगर (dev_id == zt5550_hpc.dev_id) अणु
		reg = पढ़ोb(csr_पूर्णांक_status);
		अगर (reg)
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक zt5550_hc_enable_irq(व्योम)
अणु
	u8 reg;

	अगर (hc_dev == शून्य)
		वापस -ENODEV;

	reg = पढ़ोb(csr_पूर्णांक_mask);
	reg = reg & ~ENUM_INT_MASK;
	ग_लिखोb(reg, csr_पूर्णांक_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक zt5550_hc_disable_irq(व्योम)
अणु
	u8 reg;

	अगर (hc_dev == शून्य)
		वापस -ENODEV;

	reg = पढ़ोb(csr_पूर्णांक_mask);
	reg = reg | ENUM_INT_MASK;
	ग_लिखोb(reg, csr_पूर्णांक_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक zt5550_hc_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक status;

	status = zt5550_hc_config(pdev);
	अगर (status != 0)
		वापस status;

	dbg("returned from zt5550_hc_config");

	स_रखो(&zt5550_hpc, 0, माप(काष्ठा cpci_hp_controller));
	zt5550_hpc_ops.query_क्रमागत = zt5550_hc_query_क्रमागत;
	zt5550_hpc.ops = &zt5550_hpc_ops;
	अगर (!poll) अणु
		zt5550_hpc.irq = hc_dev->irq;
		zt5550_hpc.irq_flags = IRQF_SHARED;
		zt5550_hpc.dev_id = hc_dev;

		zt5550_hpc_ops.enable_irq = zt5550_hc_enable_irq;
		zt5550_hpc_ops.disable_irq = zt5550_hc_disable_irq;
		zt5550_hpc_ops.check_irq = zt5550_hc_check_irq;
	पूर्ण अन्यथा अणु
		info("using ENUM# polling mode");
	पूर्ण

	status = cpci_hp_रेजिस्टर_controller(&zt5550_hpc);
	अगर (status != 0) अणु
		err("could not register cPCI hotplug controller");
		जाओ init_hc_error;
	पूर्ण
	dbg("registered controller");

	/* Look क्रम first device matching cPCI bus's bridge venकरोr and device IDs */
	bus0_dev = pci_get_device(PCI_VENDOR_ID_DEC,
				  PCI_DEVICE_ID_DEC_21154, शून्य);
	अगर (!bus0_dev) अणु
		status = -ENODEV;
		जाओ init_रेजिस्टर_error;
	पूर्ण
	bus0 = bus0_dev->subordinate;
	pci_dev_put(bus0_dev);

	status = cpci_hp_रेजिस्टर_bus(bus0, 0x0a, 0x0f);
	अगर (status != 0) अणु
		err("could not register cPCI hotplug bus");
		जाओ init_रेजिस्टर_error;
	पूर्ण
	dbg("registered bus");

	status = cpci_hp_start();
	अगर (status != 0) अणु
		err("could not started cPCI hotplug system");
		cpci_hp_unरेजिस्टर_bus(bus0);
		जाओ init_रेजिस्टर_error;
	पूर्ण
	dbg("started cpci hp system");

	वापस 0;
init_रेजिस्टर_error:
	cpci_hp_unरेजिस्टर_controller(&zt5550_hpc);
init_hc_error:
	err("status = %d", status);
	zt5550_hc_cleanup();
	वापस status;

पूर्ण

अटल व्योम zt5550_hc_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	cpci_hp_stop();
	cpci_hp_unरेजिस्टर_bus(bus0);
	cpci_hp_unरेजिस्टर_controller(&zt5550_hpc);
	zt5550_hc_cleanup();
पूर्ण


अटल स्थिर काष्ठा pci_device_id zt5550_hc_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_ZIATECH, PCI_DEVICE_ID_ZIATECH_5550_HC, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, zt5550_hc_pci_tbl);

अटल काष्ठा pci_driver zt5550_hc_driver = अणु
	.name		= "zt5550_hc",
	.id_table	= zt5550_hc_pci_tbl,
	.probe		= zt5550_hc_init_one,
	.हटाओ		= zt5550_hc_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init zt5550_init(व्योम)
अणु
	काष्ठा resource *r;
	पूर्णांक rc;

	info(DRIVER_DESC " version: " DRIVER_VERSION);
	r = request_region(ENUM_PORT, 1, "#ENUM hotswap signal register");
	अगर (!r)
		वापस -EBUSY;

	rc = pci_रेजिस्टर_driver(&zt5550_hc_driver);
	अगर (rc < 0)
		release_region(ENUM_PORT, 1);
	वापस rc;
पूर्ण

अटल व्योम __निकास
zt5550_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&zt5550_hc_driver);
	release_region(ENUM_PORT, 1);
पूर्ण

module_init(zt5550_init);
module_निकास(zt5550_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debugging mode enabled or not");
module_param(poll, bool, 0644);
MODULE_PARM_DESC(poll, "#ENUM polling mode enabled or not");
