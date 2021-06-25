<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/dec21285.c: PCI functions क्रम DC21285
 *
 *  Copyright (C) 1998-2001 Russell King
 *  Copyright (C) 1998-2000 Phil Blundell
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/hardware/dec21285.h>

#घोषणा MAX_SLOTS		21

#घोषणा PCICMD_ABORT		((PCI_STATUS_REC_MASTER_ABORT| \
				  PCI_STATUS_REC_TARGET_ABORT)<<16)

#घोषणा PCICMD_ERROR_BITS	((PCI_STATUS_DETECTED_PARITY | \
				  PCI_STATUS_REC_MASTER_ABORT | \
				  PCI_STATUS_REC_TARGET_ABORT | \
				  PCI_STATUS_PARITY) << 16)

बाह्य पूर्णांक setup_arm_irq(पूर्णांक, काष्ठा irqaction *);

अटल अचिन्हित दीर्घ
dc21285_base_address(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	अचिन्हित दीर्घ addr = 0;

	अगर (bus->number == 0) अणु
		अगर (PCI_SLOT(devfn) == 0)
			/*
			 * For devfn 0, poपूर्णांक at the 21285
			 */
			addr = ARMCSR_BASE;
		अन्यथा अणु
			devfn -= 1 << 3;

			अगर (devfn < PCI_DEVFN(MAX_SLOTS, 0))
				addr = PCICFG0_BASE | 0xc00000 | (devfn << 8);
		पूर्ण
	पूर्ण अन्यथा
		addr = PCICFG1_BASE | (bus->number << 16) | (devfn << 8);

	वापस addr;
पूर्ण

अटल पूर्णांक
dc21285_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		    पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr = dc21285_base_address(bus, devfn);
	u32 v = 0xffffffff;

	अगर (addr)
		चयन (size) अणु
		हाल 1:
			यंत्र अस्थिर("ldrb	%0, [%1, %2]"
				: "=r" (v) : "r" (addr), "r" (where) : "cc");
			अवरोध;
		हाल 2:
			यंत्र अस्थिर("ldrh	%0, [%1, %2]"
				: "=r" (v) : "r" (addr), "r" (where) : "cc");
			अवरोध;
		हाल 4:
			यंत्र अस्थिर("ldr	%0, [%1, %2]"
				: "=r" (v) : "r" (addr), "r" (where) : "cc");
			अवरोध;
		पूर्ण

	*value = v;

	v = *CSR_PCICMD;
	अगर (v & PCICMD_ABORT) अणु
		*CSR_PCICMD = v & (0xffff|PCICMD_ABORT);
		वापस -1;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
dc21285_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		     पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr = dc21285_base_address(bus, devfn);
	u32 v;

	अगर (addr)
		चयन (size) अणु
		हाल 1:
			यंत्र अस्थिर("strb	%0, [%1, %2]"
				: : "r" (value), "r" (addr), "r" (where)
				: "cc");
			अवरोध;
		हाल 2:
			यंत्र अस्थिर("strh	%0, [%1, %2]"
				: : "r" (value), "r" (addr), "r" (where)
				: "cc");
			अवरोध;
		हाल 4:
			यंत्र अस्थिर("str	%0, [%1, %2]"
				: : "r" (value), "r" (addr), "r" (where)
				: "cc");
			अवरोध;
		पूर्ण

	v = *CSR_PCICMD;
	अगर (v & PCICMD_ABORT) अणु
		*CSR_PCICMD = v & (0xffff|PCICMD_ABORT);
		वापस -1;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops dc21285_ops = अणु
	.पढ़ो	= dc21285_पढ़ो_config,
	.ग_लिखो	= dc21285_ग_लिखो_config,
पूर्ण;

अटल काष्ठा समयr_list serr_समयr;
अटल काष्ठा समयr_list perr_समयr;

अटल व्योम dc21285_enable_error(काष्ठा समयr_list *समयr)
अणु
	del_समयr(समयr);

	अगर (समयr == &serr_समयr)
		enable_irq(IRQ_PCI_SERR);
	अन्यथा अगर (समयr == &perr_समयr)
		enable_irq(IRQ_PCI_PERR);
पूर्ण

/*
 * Warn on PCI errors.
 */
अटल irqवापस_t dc21285_पात_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cmd;
	अचिन्हित पूर्णांक status;

	cmd = *CSR_PCICMD;
	status = cmd >> 16;
	cmd = cmd & 0xffff;

	अगर (status & PCI_STATUS_REC_MASTER_ABORT) अणु
		prपूर्णांकk(KERN_DEBUG "PCI: master abort, pc=0x%08lx\n",
			inकाष्ठाion_poपूर्णांकer(get_irq_regs()));
		cmd |= PCI_STATUS_REC_MASTER_ABORT << 16;
	पूर्ण

	अगर (status & PCI_STATUS_REC_TARGET_ABORT) अणु
		prपूर्णांकk(KERN_DEBUG "PCI: target abort: ");
		pcibios_report_status(PCI_STATUS_REC_MASTER_ABORT |
				      PCI_STATUS_SIG_TARGET_ABORT |
				      PCI_STATUS_REC_TARGET_ABORT, 1);
		prपूर्णांकk("\n");

		cmd |= PCI_STATUS_REC_TARGET_ABORT << 16;
	पूर्ण

	*CSR_PCICMD = cmd;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dc21285_serr_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा समयr_list *समयr = dev_id;
	अचिन्हित पूर्णांक cntl;

	prपूर्णांकk(KERN_DEBUG "PCI: system error received: ");
	pcibios_report_status(PCI_STATUS_SIG_SYSTEM_ERROR, 1);
	prपूर्णांकk("\n");

	cntl = *CSR_SA110_CNTL & 0xffffdf07;
	*CSR_SA110_CNTL = cntl | SA110_CNTL_RXSERR;

	/*
	 * back off this पूर्णांकerrupt
	 */
	disable_irq(irq);
	समयr->expires = jअगरfies + HZ;
	add_समयr(समयr);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dc21285_discard_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	prपूर्णांकk(KERN_DEBUG "PCI: discard timer expired\n");
	*CSR_SA110_CNTL &= 0xffffde07;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dc21285_dparity_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cmd;

	prपूर्णांकk(KERN_DEBUG "PCI: data parity error detected: ");
	pcibios_report_status(PCI_STATUS_PARITY | PCI_STATUS_DETECTED_PARITY, 1);
	prपूर्णांकk("\n");

	cmd = *CSR_PCICMD & 0xffff;
	*CSR_PCICMD = cmd | 1 << 24;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dc21285_parity_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा समयr_list *समयr = dev_id;
	अचिन्हित पूर्णांक cmd;

	prपूर्णांकk(KERN_DEBUG "PCI: parity error detected: ");
	pcibios_report_status(PCI_STATUS_PARITY | PCI_STATUS_DETECTED_PARITY, 1);
	prपूर्णांकk("\n");

	cmd = *CSR_PCICMD & 0xffff;
	*CSR_PCICMD = cmd | 1 << 31;

	/*
	 * back off this पूर्णांकerrupt
	 */
	disable_irq(irq);
	समयr->expires = jअगरfies + HZ;
	add_समयr(समयr);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक __init dc21285_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	काष्ठा resource *res;

	अगर (nr || !footbridge_cfn_mode())
		वापस 0;

	res = kसुस्मृति(2, माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res) अणु
		prपूर्णांकk("out of memory for root bus resources");
		वापस 0;
	पूर्ण

	res[0].flags = IORESOURCE_MEM;
	res[0].name  = "Footbridge non-prefetch";
	res[1].flags = IORESOURCE_MEM | IORESOURCE_PREFETCH;
	res[1].name  = "Footbridge prefetch";

	allocate_resource(&iomem_resource, &res[1], 0x20000000,
			  0xa0000000, 0xffffffff, 0x20000000, शून्य, शून्य);
	allocate_resource(&iomem_resource, &res[0], 0x40000000,
			  0x80000000, 0xffffffff, 0x40000000, शून्य, शून्य);

	sys->mem_offset  = DC21285_PCI_MEM;

	pci_add_resource_offset(&sys->resources, &res[0], sys->mem_offset);
	pci_add_resource_offset(&sys->resources, &res[1], sys->mem_offset);

	वापस 1;
पूर्ण

#घोषणा dc21285_request_irq(_a, _b, _c, _d, _e) \
	WARN_ON(request_irq(_a, _b, _c, _d, _e) < 0)

व्योम __init dc21285_preinit(व्योम)
अणु
	अचिन्हित पूर्णांक mem_size, mem_mask;
	पूर्णांक cfn_mode;

	pcibios_min_mem = 0x81000000;

	mem_size = (अचिन्हित पूर्णांक)high_memory - PAGE_OFFSET;
	क्रम (mem_mask = 0x00100000; mem_mask < 0x10000000; mem_mask <<= 1)
		अगर (mem_mask >= mem_size)
			अवरोध;

	/*
	 * These रेजिस्टरs need to be set up whether we're the
	 * central function or not.
	 */
	*CSR_SDRAMBASEMASK    = (mem_mask - 1) & 0x0ffc0000;
	*CSR_SDRAMBASखातापूर्णFSET  = 0;
	*CSR_ROMBASEMASK      = 0x80000000;
	*CSR_CSRBASEMASK      = 0;
	*CSR_CSRBASखातापूर्णFSET    = 0;
	*CSR_PCIADDR_EXTN     = 0;

	cfn_mode = __footbridge_cfn_mode();

	prपूर्णांकk(KERN_INFO "PCI: DC21285 footbridge, revision %02lX, in "
		"%s mode\n", *CSR_CLASSREV & 0xff, cfn_mode ?
		"central function" : "addin");

	अगर (footbridge_cfn_mode()) अणु
		/*
		 * Clear any existing errors - we aren't
		 * पूर्णांकerested in historical data...
		 */
		*CSR_SA110_CNTL	= (*CSR_SA110_CNTL & 0xffffde07) |
				  SA110_CNTL_RXSERR;
		*CSR_PCICMD = (*CSR_PCICMD & 0xffff) | PCICMD_ERROR_BITS;
	पूर्ण

	समयr_setup(&serr_समयr, dc21285_enable_error, 0);
	समयr_setup(&perr_समयr, dc21285_enable_error, 0);

	/*
	 * We करोn't care अगर these fail.
	 */
	dc21285_request_irq(IRQ_PCI_SERR, dc21285_serr_irq, 0,
			    "PCI system error", &serr_समयr);
	dc21285_request_irq(IRQ_PCI_PERR, dc21285_parity_irq, 0,
			    "PCI parity error", &perr_समयr);
	dc21285_request_irq(IRQ_PCI_ABORT, dc21285_पात_irq, 0,
			    "PCI abort", शून्य);
	dc21285_request_irq(IRQ_DISCARD_TIMER, dc21285_discard_irq, 0,
			    "Discard timer", शून्य);
	dc21285_request_irq(IRQ_PCI_DPERR, dc21285_dparity_irq, 0,
			    "PCI data parity", शून्य);

	अगर (cfn_mode) अणु
		/*
		 * Map our SDRAM at a known address in PCI space, just in हाल
		 * the firmware had other ideas.  Using a nonzero base is
		 * necessary, since some VGA cards क्रमcefully use PCI addresses
		 * in the range 0x000a0000 to 0x000c0000. (eg, S3 cards).
		 */
		*CSR_PCICSRBASE       = 0xf4000000;
		*CSR_PCICSRIOBASE     = 0;
		*CSR_PCISDRAMBASE     = __virt_to_bus(PAGE_OFFSET);
		*CSR_PCIROMBASE       = 0;
		*CSR_PCICMD = PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
			      PCI_COMMAND_INVALIDATE | PCICMD_ERROR_BITS;
	पूर्ण अन्यथा अगर (footbridge_cfn_mode() != 0) अणु
		/*
		 * If we are not compiled to accept "add-in" mode, then
		 * we are using a स्थिरant virt_to_bus translation which
		 * can not hope to cater क्रम the way the host BIOS  has
		 * set up the machine.
		 */
		panic("PCI: this kernel is compiled for central "
			"function mode only");
	पूर्ण
पूर्ण

व्योम __init dc21285_postinit(व्योम)
अणु
	रेजिस्टर_isa_ports(DC21285_PCI_MEM, DC21285_PCI_IO, 0);
पूर्ण
