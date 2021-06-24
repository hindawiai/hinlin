<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000, 2001 Keith M Wesolowski
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

#अघोषित DEBUG_MACE_PCI

/*
 * Handle errors from the bridge.  This includes master and target पातs,
 * various command and address errors, and the पूर्णांकerrupt test.	This माला_लो
 * रेजिस्टरed on the bridge error irq.	It's conceivable that some of these
 * conditions warrant a panic.	Anybody care to say which ones?
 */
अटल irqवापस_t macepci_error(पूर्णांक irq, व्योम *dev)
अणु
	अक्षर s;
	अचिन्हित पूर्णांक flags = mace->pci.error;
	अचिन्हित पूर्णांक addr = mace->pci.error_addr;

	अगर (flags & MACEPCI_ERROR_MEMORY_ADDR)
		s = 'M';
	अन्यथा अगर (flags & MACEPCI_ERROR_CONFIG_ADDR)
		s = 'C';
	अन्यथा
		s = 'X';

	अगर (flags & MACEPCI_ERROR_MASTER_ABORT) अणु
		prपूर्णांकk("MACEPCI: Master abort at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_MASTER_ABORT;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_TARGET_ABORT) अणु
		prपूर्णांकk("MACEPCI: Target abort at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_TARGET_ABORT;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_DATA_PARITY_ERR) अणु
		prपूर्णांकk("MACEPCI: Data parity error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_DATA_PARITY_ERR;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_RETRY_ERR) अणु
		prपूर्णांकk("MACEPCI: Retry error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_RETRY_ERR;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_ILLEGAL_CMD) अणु
		prपूर्णांकk("MACEPCI: Illegal command at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_ILLEGAL_CMD;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_SYSTEM_ERR) अणु
		prपूर्णांकk("MACEPCI: System error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_SYSTEM_ERR;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_PARITY_ERR) अणु
		prपूर्णांकk("MACEPCI: Parity error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_PARITY_ERR;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_OVERRUN) अणु
		prपूर्णांकk("MACEPCI: Overrun error at 0x%08x (%c)\n", addr, s);
		flags &= ~MACEPCI_ERROR_OVERRUN;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_SIG_TABORT) अणु
		prपूर्णांकk("MACEPCI: Signaled target abort (clearing)\n");
		flags &= ~MACEPCI_ERROR_SIG_TABORT;
	पूर्ण
	अगर (flags & MACEPCI_ERROR_INTERRUPT_TEST) अणु
		prपूर्णांकk("MACEPCI: Interrupt test triggered (clearing)\n");
		flags &= ~MACEPCI_ERROR_INTERRUPT_TEST;
	पूर्ण

	mace->pci.error = flags;

	वापस IRQ_HANDLED;
पूर्ण


बाह्य काष्ठा pci_ops mace_pci_ops;
#अगर_घोषित CONFIG_64BIT
अटल काष्ठा resource mace_pci_mem_resource = अणु
	.name	= "SGI O2 PCI MEM",
	.start	= MACEPCI_HI_MEMORY,
	.end	= 0x2FFFFFFFFUL,
	.flags	= IORESOURCE_MEM,
पूर्ण;
अटल काष्ठा resource mace_pci_io_resource = अणु
	.name	= "SGI O2 PCI IO",
	.start	= 0x00000000UL,
	.end	= 0xffffffffUL,
	.flags	= IORESOURCE_IO,
पूर्ण;
#घोषणा MACE_PCI_MEM_OFFSET 0x200000000
#अन्यथा
अटल काष्ठा resource mace_pci_mem_resource = अणु
	.name	= "SGI O2 PCI MEM",
	.start	= MACEPCI_LOW_MEMORY,
	.end	= MACEPCI_LOW_MEMORY + 0x2000000 - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;
अटल काष्ठा resource mace_pci_io_resource = अणु
	.name	= "SGI O2 PCI IO",
	.start	= 0x00000000,
	.end	= 0xFFFFFFFF,
	.flags	= IORESOURCE_IO,
पूर्ण;
#घोषणा MACE_PCI_MEM_OFFSET (MACEPCI_LOW_MEMORY - 0x80000000)
#पूर्ण_अगर
अटल काष्ठा pci_controller mace_pci_controller = अणु
	.pci_ops	= &mace_pci_ops,
	.mem_resource	= &mace_pci_mem_resource,
	.io_resource	= &mace_pci_io_resource,
	.mem_offset	= MACE_PCI_MEM_OFFSET,
	.io_offset	= 0,
	.io_map_base	= CKSEG1ADDR(MACEPCI_LOW_IO),
पूर्ण;

अटल पूर्णांक __init mace_init(व्योम)
अणु
	PCIBIOS_MIN_IO = 0x1000;

	/* Clear any outstanding errors and enable पूर्णांकerrupts */
	mace->pci.error_addr = 0;
	mace->pci.error = 0;
	mace->pci.control = 0xff008500;

	prपूर्णांकk("MACE PCI rev %d\n", mace->pci.rev);

	BUG_ON(request_irq(MACE_PCI_BRIDGE_IRQ, macepci_error, 0,
			   "MACE PCI error", शून्य));

	/* extend memory resources */
	iomem_resource.end = mace_pci_mem_resource.end;
	ioport_resource = mace_pci_io_resource;

	रेजिस्टर_pci_controller(&mace_pci_controller);

	वापस 0;
पूर्ण

arch_initcall(mace_init);
