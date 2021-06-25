<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kernel.h>

/*
 * These functions are used early on beक्रमe PCI scanning is करोne
 * and all of the pci_dev and pci_bus काष्ठाures have been created.
 */
अटल काष्ठा pci_dev *fake_pci_dev(काष्ठा pci_channel *hose,
	पूर्णांक top_bus, पूर्णांक busnr, पूर्णांक devfn)
अणु
	अटल काष्ठा pci_dev dev;
	अटल काष्ठा pci_bus bus;

	dev.bus = &bus;
	dev.sysdata = hose;
	dev.devfn = devfn;
	bus.number = busnr;
	bus.sysdata = hose;
	bus.ops = hose->pci_ops;

	अगर(busnr != top_bus)
		/* Fake a parent bus काष्ठाure. */
		bus.parent = &bus;
	अन्यथा
		bus.parent = शून्य;

	वापस &dev;
पूर्ण

#घोषणा EARLY_PCI_OP(rw, size, type)					\
पूर्णांक __init early_##rw##_config_##size(काष्ठा pci_channel *hose,		\
	पूर्णांक top_bus, पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, type value)	\
अणु									\
	वापस pci_##rw##_config_##size(				\
		fake_pci_dev(hose, top_bus, bus, devfn),		\
		offset, value);						\
पूर्ण

EARLY_PCI_OP(पढ़ो, byte, u8 *)
EARLY_PCI_OP(पढ़ो, word, u16 *)
EARLY_PCI_OP(पढ़ो, dword, u32 *)
EARLY_PCI_OP(ग_लिखो, byte, u8)
EARLY_PCI_OP(ग_लिखो, word, u16)
EARLY_PCI_OP(ग_लिखो, dword, u32)

पूर्णांक __init pci_is_66mhz_capable(काष्ठा pci_channel *hose,
				पूर्णांक top_bus, पूर्णांक current_bus)
अणु
	u32 pci_devfn;
	अचिन्हित लघु vid;
	पूर्णांक cap66 = -1;
	u16 stat;

	pr_info("PCI: Checking 66MHz capabilities...\n");

	क्रम (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++) अणु
		अगर (PCI_FUNC(pci_devfn))
			जारी;
		अगर (early_पढ़ो_config_word(hose, top_bus, current_bus,
					   pci_devfn, PCI_VENDOR_ID, &vid) !=
		    PCIBIOS_SUCCESSFUL)
			जारी;
		अगर (vid == 0xffff)
			जारी;

		/* check 66MHz capability */
		अगर (cap66 < 0)
			cap66 = 1;
		अगर (cap66) अणु
			early_पढ़ो_config_word(hose, top_bus, current_bus,
					       pci_devfn, PCI_STATUS, &stat);
			अगर (!(stat & PCI_STATUS_66MHZ)) अणु
				prपूर्णांकk(KERN_DEBUG
				       "PCI: %02x:%02x not 66MHz capable.\n",
				       current_bus, pci_devfn);
				cap66 = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस cap66 > 0;
पूर्ण

अटल व्योम pcibios_enable_err(काष्ठा समयr_list *t)
अणु
	काष्ठा pci_channel *hose = from_समयr(hose, t, err_समयr);

	del_समयr(&hose->err_समयr);
	prपूर्णांकk(KERN_DEBUG "PCI: re-enabling error IRQ.\n");
	enable_irq(hose->err_irq);
पूर्ण

अटल व्योम pcibios_enable_serr(काष्ठा समयr_list *t)
अणु
	काष्ठा pci_channel *hose = from_समयr(hose, t, serr_समयr);

	del_समयr(&hose->serr_समयr);
	prपूर्णांकk(KERN_DEBUG "PCI: re-enabling system error IRQ.\n");
	enable_irq(hose->serr_irq);
पूर्ण

व्योम pcibios_enable_समयrs(काष्ठा pci_channel *hose)
अणु
	अगर (hose->err_irq) अणु
		समयr_setup(&hose->err_समयr, pcibios_enable_err, 0);
	पूर्ण

	अगर (hose->serr_irq) अणु
		समयr_setup(&hose->serr_समयr, pcibios_enable_serr, 0);
	पूर्ण
पूर्ण

/*
 * A simple handler क्रम the regular PCI status errors, called from IRQ
 * context.
 */
अचिन्हित पूर्णांक pcibios_handle_status_errors(अचिन्हित दीर्घ addr,
					  अचिन्हित पूर्णांक status,
					  काष्ठा pci_channel *hose)
अणु
	अचिन्हित पूर्णांक cmd = 0;

	अगर (status & PCI_STATUS_REC_MASTER_ABORT) अणु
		prपूर्णांकk(KERN_DEBUG "PCI: master abort, pc=0x%08lx\n", addr);
		cmd |= PCI_STATUS_REC_MASTER_ABORT;
	पूर्ण

	अगर (status & PCI_STATUS_REC_TARGET_ABORT) अणु
		prपूर्णांकk(KERN_DEBUG "PCI: target abort: ");
		pcibios_report_status(PCI_STATUS_REC_TARGET_ABORT |
				      PCI_STATUS_SIG_TARGET_ABORT |
				      PCI_STATUS_REC_MASTER_ABORT, 1);
		pr_cont("\n");

		cmd |= PCI_STATUS_REC_TARGET_ABORT;
	पूर्ण

	अगर (status & (PCI_STATUS_PARITY | PCI_STATUS_DETECTED_PARITY)) अणु
		prपूर्णांकk(KERN_DEBUG "PCI: parity error detected: ");
		pcibios_report_status(PCI_STATUS_PARITY |
				      PCI_STATUS_DETECTED_PARITY, 1);
		pr_cont("\n");

		cmd |= PCI_STATUS_PARITY | PCI_STATUS_DETECTED_PARITY;

		/* Now back off of the IRQ क्रम aजबतक */
		अगर (hose->err_irq) अणु
			disable_irq_nosync(hose->err_irq);
			hose->err_समयr.expires = jअगरfies + HZ;
			add_समयr(&hose->err_समयr);
		पूर्ण
	पूर्ण

	वापस cmd;
पूर्ण
