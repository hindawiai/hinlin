<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_si_pci.c
 *
 * Handling क्रम IPMI devices on the PCI bus.
 */

#घोषणा pr_fmt(fmt) "ipmi_pci: " fmt

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "ipmi_si.h"

अटल bool pci_रेजिस्टरed;

अटल bool si_trypci = true;

module_param_named(trypci, si_trypci, bool, 0);
MODULE_PARM_DESC(trypci,
		 "Setting this to zero will disable the default scan of the interfaces identified via pci");

#घोषणा PCI_DEVICE_ID_HP_MMC 0x121A

अटल पूर्णांक ipmi_pci_probe_regspacing(काष्ठा si_sm_io *io)
अणु
	अगर (io->si_type == SI_KCS) अणु
		अचिन्हित अक्षर	status;
		पूर्णांक		regspacing;

		io->regsize = DEFAULT_REGSIZE;
		io->regshअगरt = 0;

		/* detect 1, 4, 16byte spacing */
		क्रम (regspacing = DEFAULT_REGSPACING; regspacing <= 16;) अणु
			io->regspacing = regspacing;
			अगर (io->io_setup(io)) अणु
				dev_err(io->dev, "Could not setup I/O space\n");
				वापस DEFAULT_REGSPACING;
			पूर्ण
			/* ग_लिखो invalid cmd */
			io->outputb(io, 1, 0x10);
			/* पढ़ो status back */
			status = io->inputb(io, 1);
			io->io_cleanup(io);
			अगर (status)
				वापस regspacing;
			regspacing *= 4;
		पूर्ण
	पूर्ण
	वापस DEFAULT_REGSPACING;
पूर्ण

अटल काष्ठा pci_device_id ipmi_pci_blacklist[] = अणु
	/*
	 * This is a "Virtual IPMI device", whatever that is.  It appears
	 * as a KCS device by the class, but it is not one.
	 */
	अणु PCI_VDEVICE(REALTEK, 0x816c) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल पूर्णांक ipmi_pci_probe(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rv;
	काष्ठा si_sm_io io;

	अगर (pci_match_id(ipmi_pci_blacklist, pdev))
		वापस -ENODEV;

	स_रखो(&io, 0, माप(io));
	io.addr_source = SI_PCI;
	dev_info(&pdev->dev, "probing via PCI");

	चयन (pdev->class) अणु
	हाल PCI_CLASS_SERIAL_IPMI_SMIC:
		io.si_type = SI_SMIC;
		अवरोध;

	हाल PCI_CLASS_SERIAL_IPMI_KCS:
		io.si_type = SI_KCS;
		अवरोध;

	हाल PCI_CLASS_SERIAL_IPMI_BT:
		io.si_type = SI_BT;
		अवरोध;

	शेष:
		dev_info(&pdev->dev, "Unknown IPMI class: %x\n", pdev->class);
		वापस -ENOMEM;
	पूर्ण

	rv = pcim_enable_device(pdev);
	अगर (rv) अणु
		dev_err(&pdev->dev, "couldn't enable PCI device\n");
		वापस rv;
	पूर्ण

	अगर (pci_resource_flags(pdev, 0) & IORESOURCE_IO) अणु
		io.addr_space = IPMI_IO_ADDR_SPACE;
		io.io_setup = ipmi_si_port_setup;
	पूर्ण अन्यथा अणु
		io.addr_space = IPMI_MEM_ADDR_SPACE;
		io.io_setup = ipmi_si_mem_setup;
	पूर्ण
	io.addr_data = pci_resource_start(pdev, 0);

	io.dev = &pdev->dev;

	io.regspacing = ipmi_pci_probe_regspacing(&io);
	io.regsize = DEFAULT_REGSIZE;
	io.regshअगरt = 0;

	io.irq = pdev->irq;
	अगर (io.irq)
		io.irq_setup = ipmi_std_irq_setup;

	dev_info(&pdev->dev, "%pR regsize %d spacing %d irq %d\n",
		 &pdev->resource[0], io.regsize, io.regspacing, io.irq);

	वापस ipmi_si_add_smi(&io);
पूर्ण

अटल व्योम ipmi_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	ipmi_si_हटाओ_by_dev(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ipmi_pci_devices[] = अणु
	अणु PCI_VDEVICE(HP, PCI_DEVICE_ID_HP_MMC) पूर्ण,
	अणु PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_IPMI_SMIC, ~0) पूर्ण,
	अणु PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_IPMI_KCS, ~0) पूर्ण,
	अणु PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_IPMI_BT, ~0) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ipmi_pci_devices);

अटल काष्ठा pci_driver ipmi_pci_driver = अणु
	.name =         SI_DEVICE_NAME,
	.id_table =     ipmi_pci_devices,
	.probe =        ipmi_pci_probe,
	.हटाओ =       ipmi_pci_हटाओ,
पूर्ण;

व्योम ipmi_si_pci_init(व्योम)
अणु
	अगर (si_trypci) अणु
		पूर्णांक rv = pci_रेजिस्टर_driver(&ipmi_pci_driver);
		अगर (rv)
			pr_err("Unable to register PCI driver: %d\n", rv);
		अन्यथा
			pci_रेजिस्टरed = true;
	पूर्ण
पूर्ण

व्योम ipmi_si_pci_shutकरोwn(व्योम)
अणु
	अगर (pci_रेजिस्टरed)
		pci_unरेजिस्टर_driver(&ipmi_pci_driver);
पूर्ण
