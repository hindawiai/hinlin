<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/plat-iop/pci.c
 *
 * PCI support क्रम the Intel IOP32X and IOP33X processors
 *
 * Author: Rory Bolt <rorybolt@pacbell.net>
 * Copyright (C) 2002 Rory Bolt
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/mach/pci.h>
#समावेश "hardware.h"
#समावेश "iop3xx.h"

// #घोषणा DEBUG

#अगर_घोषित DEBUG
#घोषणा  DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा  DBG(x...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * This routine builds either a type0 or type1 configuration command.  If the
 * bus is on the 803xx then a type0 made, अन्यथा a type1 is created.
 */
अटल u32 iop3xx_cfg_address(काष्ठा pci_bus *bus, पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा pci_sys_data *sys = bus->sysdata;
	u32 addr;

	अगर (sys->busnr == bus->number)
		addr = 1 << (PCI_SLOT(devfn) + 16) | (PCI_SLOT(devfn) << 11);
	अन्यथा
		addr = bus->number << 16 | PCI_SLOT(devfn) << 11 | 1;

	addr |=	PCI_FUNC(devfn) << 8 | (where & ~3);

	वापस addr;
पूर्ण

/*
 * This routine checks the status of the last configuration cycle.  If an error
 * was detected it वापसs a 1, अन्यथा it वापसs a 0.  The errors being checked
 * are parity, master पात, target पात (master and target).  These types of
 * errors occur during a config cycle where there is no device, like during
 * the discovery stage.
 */
अटल पूर्णांक iop3xx_pci_status(व्योम)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक ret = 0;

	/*
	 * Check the status रेजिस्टरs.
	 */
	status = *IOP3XX_ATUSR;
	अगर (status & 0xf900) अणु
		DBG("\t\t\tPCI: P0 - status = 0x%08x\n", status);
		*IOP3XX_ATUSR = status & 0xf900;
		ret = 1;
	पूर्ण

	status = *IOP3XX_ATUISR;
	अगर (status & 0x679f) अणु
		DBG("\t\t\tPCI: P1 - status = 0x%08x\n", status);
		*IOP3XX_ATUISR = status & 0x679f;
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Simply ग_लिखो the address रेजिस्टर and पढ़ो the configuration
 * data.  Note that the 4 nops ensure that we are able to handle
 * a delayed पात (in theory.)
 */
अटल u32 iop3xx_पढ़ो(अचिन्हित दीर्घ addr)
अणु
	u32 val;

	__यंत्र__ __अस्थिर__(
		"str	%1, [%2]\n\t"
		"ldr	%0, [%3]\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		: "=r" (val)
		: "r" (addr), "r" (IOP3XX_OCCAR), "r" (IOP3XX_OCCDR));

	वापस val;
पूर्ण

/*
 * The पढ़ो routines must check the error status of the last configuration
 * cycle.  If there was an error, the routine वापसs all hex f's.
 */
अटल पूर्णांक
iop3xx_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		पूर्णांक size, u32 *value)
अणु
	अचिन्हित दीर्घ addr = iop3xx_cfg_address(bus, devfn, where);
	u32 val = iop3xx_पढ़ो(addr) >> ((where & 3) * 8);

	अगर (iop3xx_pci_status())
		val = 0xffffffff;

	*value = val;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
iop3xx_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		पूर्णांक size, u32 value)
अणु
	अचिन्हित दीर्घ addr = iop3xx_cfg_address(bus, devfn, where);
	u32 val;

	अगर (size != 4) अणु
		val = iop3xx_पढ़ो(addr);
		अगर (iop3xx_pci_status())
			वापस PCIBIOS_SUCCESSFUL;

		where = (where & 3) * 8;

		अगर (size == 1)
			val &= ~(0xff << where);
		अन्यथा
			val &= ~(0xffff << where);

		*IOP3XX_OCCDR = val | value << where;
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर(
			"str	%1, [%2]\n\t"
			"str	%0, [%3]\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			:
			: "r" (value), "r" (addr),
			  "r" (IOP3XX_OCCAR), "r" (IOP3XX_OCCDR));
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops iop3xx_ops = अणु
	.पढ़ो	= iop3xx_पढ़ो_config,
	.ग_लिखो	= iop3xx_ग_लिखो_config,
पूर्ण;

/*
 * When a PCI device करोes not exist during config cycles, the 80200 माला_लो a
 * bus error instead of वापसing 0xffffffff. This handler simply वापसs.
 */
अटल पूर्णांक
iop3xx_pci_पात(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	DBG("PCI abort: address = 0x%08lx fsr = 0x%03x PC = 0x%08lx LR = 0x%08lx\n",
		addr, fsr, regs->ARM_pc, regs->ARM_lr);

	/*
	 * If it was an imprecise पात, then we need to correct the
	 * वापस address to be _after_ the inकाष्ठाion.
	 */
	अगर (fsr & (1 << 10))
		regs->ARM_pc += 4;

	वापस 0;
पूर्ण

पूर्णांक iop3xx_pci_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	काष्ठा resource *res;

	अगर (nr != 0)
		वापस 0;

	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res)
		panic("PCI: unable to alloc resources");

	res->start = IOP3XX_PCI_LOWER_MEM_PA;
	res->end   = IOP3XX_PCI_LOWER_MEM_PA + IOP3XX_PCI_MEM_WINDOW_SIZE - 1;
	res->name  = "IOP3XX PCI Memory Space";
	res->flags = IORESOURCE_MEM;
	request_resource(&iomem_resource, res);

	/*
	 * Use whatever translation is alपढ़ोy setup.
	 */
	sys->mem_offset = IOP3XX_PCI_LOWER_MEM_PA - *IOP3XX_OMWTVR0;

	pci_add_resource_offset(&sys->resources, res, sys->mem_offset);

	pci_ioremap_io(0, IOP3XX_PCI_LOWER_IO_PA);

	वापस 1;
पूर्ण

व्योम __init iop3xx_atu_setup(व्योम)
अणु
	/* BAR 0 ( Disabled ) */
	*IOP3XX_IAUBAR0 = 0x0;
	*IOP3XX_IABAR0  = 0x0;
	*IOP3XX_IATVR0  = 0x0;
	*IOP3XX_IALR0   = 0x0;

	/* BAR 1 ( Disabled ) */
	*IOP3XX_IAUBAR1 = 0x0;
	*IOP3XX_IABAR1  = 0x0;
	*IOP3XX_IALR1   = 0x0;

	/* BAR 2 (1:1 mapping with Physical RAM) */
	/* Set limit and enable */
	*IOP3XX_IALR2 = ~((u32)IOP3XX_MAX_RAM_SIZE - 1) & ~0x1;
	*IOP3XX_IAUBAR2 = 0x0;

	/* Align the inbound bar with the base of memory */
	*IOP3XX_IABAR2 = PHYS_OFFSET |
			       PCI_BASE_ADDRESS_MEM_TYPE_64 |
			       PCI_BASE_ADDRESS_MEM_PREFETCH;

	*IOP3XX_IATVR2 = PHYS_OFFSET;

	/* Outbound winकरोw 0 */
	*IOP3XX_OMWTVR0 = IOP3XX_PCI_LOWER_MEM_BA;
	*IOP3XX_OUMWTVR0 = 0;

	/* Outbound winकरोw 1 */
	*IOP3XX_OMWTVR1 = IOP3XX_PCI_LOWER_MEM_BA +
			  IOP3XX_PCI_MEM_WINDOW_SIZE / 2;
	*IOP3XX_OUMWTVR1 = 0;

	/* BAR 3 ( Disabled ) */
	*IOP3XX_IAUBAR3 = 0x0;
	*IOP3XX_IABAR3  = 0x0;
	*IOP3XX_IATVR3  = 0x0;
	*IOP3XX_IALR3   = 0x0;

	/* Setup the I/O Bar
	 */
	*IOP3XX_OIOWTVR = IOP3XX_PCI_LOWER_IO_BA;

	/* Enable inbound and outbound cycles
	 */
	*IOP3XX_ATUCMD |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
			       PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
	*IOP3XX_ATUCR |= IOP3XX_ATUCR_OUT_EN;
पूर्ण

व्योम __init iop3xx_atu_disable(व्योम)
अणु
	*IOP3XX_ATUCMD = 0;
	*IOP3XX_ATUCR = 0;

	/* रुको क्रम cycles to quiesce */
	जबतक (*IOP3XX_PCSR & (IOP3XX_PCSR_OUT_Q_BUSY |
				     IOP3XX_PCSR_IN_Q_BUSY))
		cpu_relax();

	/* BAR 0 ( Disabled ) */
	*IOP3XX_IAUBAR0 = 0x0;
	*IOP3XX_IABAR0  = 0x0;
	*IOP3XX_IATVR0  = 0x0;
	*IOP3XX_IALR0   = 0x0;

	/* BAR 1 ( Disabled ) */
	*IOP3XX_IAUBAR1 = 0x0;
	*IOP3XX_IABAR1  = 0x0;
	*IOP3XX_IALR1   = 0x0;

	/* BAR 2 ( Disabled ) */
	*IOP3XX_IAUBAR2 = 0x0;
	*IOP3XX_IABAR2  = 0x0;
	*IOP3XX_IATVR2  = 0x0;
	*IOP3XX_IALR2   = 0x0;

	/* BAR 3 ( Disabled ) */
	*IOP3XX_IAUBAR3 = 0x0;
	*IOP3XX_IABAR3  = 0x0;
	*IOP3XX_IATVR3  = 0x0;
	*IOP3XX_IALR3   = 0x0;

	/* Clear the outbound winकरोws */
	*IOP3XX_OIOWTVR  = 0;

	/* Outbound winकरोw 0 */
	*IOP3XX_OMWTVR0 = 0;
	*IOP3XX_OUMWTVR0 = 0;

	/* Outbound winकरोw 1 */
	*IOP3XX_OMWTVR1 = 0;
	*IOP3XX_OUMWTVR1 = 0;
पूर्ण

/* Flag to determine whether the ATU is initialized and the PCI bus scanned */
पूर्णांक init_atu;

पूर्णांक iop3xx_get_init_atu(व्योम) अणु
	/* check अगर शेष has been overridden */
	अगर (init_atu != IOP3XX_INIT_ATU_DEFAULT)
		वापस init_atu;
	अन्यथा
		वापस IOP3XX_INIT_ATU_DISABLE;
पूर्ण

अटल व्योम __init iop3xx_atu_debug(व्योम)
अणु
	DBG("PCI: Intel IOP3xx PCI init.\n");
	DBG("PCI: Outbound memory window 0: PCI 0x%08x%08x\n",
		*IOP3XX_OUMWTVR0, *IOP3XX_OMWTVR0);
	DBG("PCI: Outbound memory window 1: PCI 0x%08x%08x\n",
		*IOP3XX_OUMWTVR1, *IOP3XX_OMWTVR1);
	DBG("PCI: Outbound IO window: PCI 0x%08x\n",
		*IOP3XX_OIOWTVR);

	DBG("PCI: Inbound memory window 0: PCI 0x%08x%08x 0x%08x -> 0x%08x\n",
		*IOP3XX_IAUBAR0, *IOP3XX_IABAR0, *IOP3XX_IALR0, *IOP3XX_IATVR0);
	DBG("PCI: Inbound memory window 1: PCI 0x%08x%08x 0x%08x\n",
		*IOP3XX_IAUBAR1, *IOP3XX_IABAR1, *IOP3XX_IALR1);
	DBG("PCI: Inbound memory window 2: PCI 0x%08x%08x 0x%08x -> 0x%08x\n",
		*IOP3XX_IAUBAR2, *IOP3XX_IABAR2, *IOP3XX_IALR2, *IOP3XX_IATVR2);
	DBG("PCI: Inbound memory window 3: PCI 0x%08x%08x 0x%08x -> 0x%08x\n",
		*IOP3XX_IAUBAR3, *IOP3XX_IABAR3, *IOP3XX_IALR3, *IOP3XX_IATVR3);

	DBG("PCI: Expansion ROM window: PCI 0x%08x%08x 0x%08x -> 0x%08x\n",
		0, *IOP3XX_ERBAR, *IOP3XX_ERLR, *IOP3XX_ERTVR);

	DBG("ATU: IOP3XX_ATUCMD=0x%04x\n", *IOP3XX_ATUCMD);
	DBG("ATU: IOP3XX_ATUCR=0x%08x\n", *IOP3XX_ATUCR);

	hook_fault_code(16+6, iop3xx_pci_पात, SIGBUS, 0, "imprecise external abort");
पूर्ण

/* क्रम platक्रमms that might be host-bus-adapters */
व्योम __init iop3xx_pci_preinit_cond(व्योम)
अणु
	अगर (iop3xx_get_init_atu() == IOP3XX_INIT_ATU_ENABLE) अणु
		iop3xx_atu_disable();
		iop3xx_atu_setup();
		iop3xx_atu_debug();
	पूर्ण
पूर्ण

व्योम __init iop3xx_pci_preinit(व्योम)
अणु
	pcibios_min_mem = 0;

	iop3xx_atu_disable();
	iop3xx_atu_setup();
	iop3xx_atu_debug();
पूर्ण

/* allow init_atu to be user overridden */
अटल पूर्णांक __init iop3xx_init_atu_setup(अक्षर *str)
अणु
	init_atu = IOP3XX_INIT_ATU_DEFAULT;
	अगर (str) अणु
		जबतक (*str != '\0') अणु
			चयन (*str) अणु
			हाल 'y':
			हाल 'Y':
				init_atu = IOP3XX_INIT_ATU_ENABLE;
				अवरोध;
			हाल 'n':
			हाल 'N':
				init_atu = IOP3XX_INIT_ATU_DISABLE;
				अवरोध;
			हाल ',':
			हाल '=':
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_DEBUG "\"%s\" malformed at "
					    "character: \'%c\'",
					    __func__,
					    *str);
				*(str + 1) = '\0';
			पूर्ण
			str++;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

__setup("iop3xx_init_atu", iop3xx_init_atu_setup);

