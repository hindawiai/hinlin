<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_nautilus.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1998 Riअक्षरd Henderson
 *	Copyright (C) 1999 Alpha Processor, Inc.,
 *		(David Daniel, Stig Telfer, Soohoon Lee)
 *
 * Code supporting NAUTILUS प्रणालीs.
 *
 *
 * NAUTILUS has the following I/O features:
 *
 * a) Driven by AMD 751 aka IRONGATE (northbridge):
 *     4 PCI slots
 *     1 AGP slot
 *
 * b) Driven by ALI M1543C (southbridge)
 *     2 ISA slots
 *     2 IDE connectors
 *     1 dual drive capable FDD controller
 *     2 serial ports
 *     1 ECP/EPP/SP parallel port
 *     2 USB ports
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>
#समावेश <linux/memblock.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_irongate.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "err_impl.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


अटल व्योम __init
nautilus_init_irq(व्योम)
अणु
	अगर (alpha_using_srm) अणु
		alpha_mv.device_पूर्णांकerrupt = srm_device_पूर्णांकerrupt;
	पूर्ण

	init_i8259a_irqs();
	common_init_isa_dma();
पूर्ण

अटल पूर्णांक
nautilus_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	/* Preserve the IRQ set up by the console.  */

	u8 irq;
	/* UP1500: AGP INTA is actually routed to IRQ 5, not IRQ 10 as
	   console reports. Check the device id of AGP bridge to distinguish
	   UP1500 from UP1000/1100. Note: 'pin' is 2 due to bridge swizzle. */
	अगर (slot == 1 && pin == 2 &&
	    dev->bus->self && dev->bus->self->device == 0x700f)
		वापस 5;
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
	वापस irq;
पूर्ण

व्योम
nautilus_समाप्त_arch(पूर्णांक mode)
अणु
	काष्ठा pci_bus *bus = pci_isa_hose->bus;
	u32 pmuport;
	पूर्णांक off;

	चयन (mode) अणु
	हाल LINUX_REBOOT_CMD_RESTART:
		अगर (! alpha_using_srm) अणु
			u8 t8;
			pci_bus_पढ़ो_config_byte(bus, 0x38, 0x43, &t8);
			pci_bus_ग_लिखो_config_byte(bus, 0x38, 0x43, t8 | 0x80);
			outb(1, 0x92);
			outb(0, 0x92);
			/* NOTREACHED */
		पूर्ण
		अवरोध;

	हाल LINUX_REBOOT_CMD_POWER_OFF:
		/* Assume M1543C */
		off = 0x2000;		/* SLP_TYPE = 0, SLP_EN = 1 */
		pci_bus_पढ़ो_config_dword(bus, 0x88, 0x10, &pmuport);
		अगर (!pmuport) अणु
			/* M1535D/D+ */
			off = 0x3400;	/* SLP_TYPE = 5, SLP_EN = 1 */
			pci_bus_पढ़ो_config_dword(bus, 0x88, 0xe0, &pmuport);
		पूर्ण
		pmuport &= 0xfffe;
		outw(0xffff, pmuport);	/* Clear pending events. */
		outw(off, pmuport + 4);
		/* NOTREACHED */
		अवरोध;
	पूर्ण
पूर्ण

/* Perक्रमm analysis of a machine check that arrived from the प्रणाली (NMI) */

अटल व्योम
naut_sys_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr,
		       काष्ठा pt_regs *regs)
अणु
	prपूर्णांकk("PC %lx RA %lx\n", regs->pc, regs->r26);
	irongate_pci_clr_err();
पूर्ण

/* Machine checks can come from two sources - those on the CPU and those
   in the प्रणाली.  They are analysed separately but all starts here.  */

व्योम
nautilus_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	अक्षर *mchk_class;

	/* Now क्रम some analysis.  Machine checks fall पूर्णांकo two classes --
	   those picked up by the प्रणाली, and those picked up by the CPU.
	   Add to that the two levels of severity - correctable or not.  */

	अगर (vector == SCB_Q_SYSMCHK
	    && ((IRONGATE0->dramms & 0x300) == 0x300)) अणु
		अचिन्हित दीर्घ nmi_ctl;

		/* Clear ALI NMI */
		nmi_ctl = inb(0x61);
		nmi_ctl |= 0x0c;
		outb(nmi_ctl, 0x61);
		nmi_ctl &= ~0x0c;
		outb(nmi_ctl, 0x61);

		/* Write again clears error bits.  */
		IRONGATE0->stat_cmd = IRONGATE0->stat_cmd & ~0x100;
		mb();
		IRONGATE0->stat_cmd;

		/* Write again clears error bits.  */
		IRONGATE0->dramms = IRONGATE0->dramms;
		mb();
		IRONGATE0->dramms;

		draina();
		wrmces(0x7);
		mb();
		वापस;
	पूर्ण

	अगर (vector == SCB_Q_SYSERR)
		mchk_class = "Correctable";
	अन्यथा अगर (vector == SCB_Q_SYSMCHK)
		mchk_class = "Fatal";
	अन्यथा अणु
		ev6_machine_check(vector, la_ptr);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_CRIT "NAUTILUS Machine check 0x%lx "
			 "[%s System Machine Check (NMI)]\n",
	       vector, mchk_class);

	naut_sys_machine_check(vector, la_ptr, get_irq_regs());

	/* Tell the PALcode to clear the machine check */
	draina();
	wrmces(0x7);
	mb();
पूर्ण

बाह्य व्योम pcibios_claim_one_bus(काष्ठा pci_bus *);

अटल काष्ठा resource irongate_mem = अणु
	.name	= "Irongate PCI MEM",
	.flags	= IORESOURCE_MEM,
पूर्ण;
अटल काष्ठा resource busn_resource = अणु
	.name	= "PCI busn",
	.start	= 0,
	.end	= 255,
	.flags	= IORESOURCE_BUS,
पूर्ण;

व्योम __init
nautilus_init_pci(व्योम)
अणु
	काष्ठा pci_controller *hose = hose_head;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा pci_bus *bus;
	अचिन्हित दीर्घ bus_align, bus_size, pci_mem;
	अचिन्हित दीर्घ memtop = max_low_pfn << PAGE_SHIFT;

	bridge = pci_alloc_host_bridge(0);
	अगर (!bridge)
		वापस;

	/* Use शेष IO. */
	pci_add_resource(&bridge->winकरोws, &ioport_resource);
	/* Irongate PCI memory aperture, calculate requred size beक्रमe
	   setting it up. */
	pci_add_resource(&bridge->winकरोws, &irongate_mem);

	pci_add_resource(&bridge->winकरोws, &busn_resource);
	bridge->dev.parent = शून्य;
	bridge->sysdata = hose;
	bridge->busnr = 0;
	bridge->ops = alpha_mv.pci_ops;
	bridge->swizzle_irq = alpha_mv.pci_swizzle;
	bridge->map_irq = alpha_mv.pci_map_irq;
	bridge->size_winकरोws = 1;

	/* Scan our single hose.  */
	अगर (pci_scan_root_bus_bridge(bridge)) अणु
		pci_मुक्त_host_bridge(bridge);
		वापस;
	पूर्ण
	bus = hose->bus = bridge->bus;
	pcibios_claim_one_bus(bus);

	pci_bus_size_bridges(bus);

	/* Now we've got the size and alignment of PCI memory resources
	   stored in irongate_mem. Set up the PCI memory range: limit is
	   hardwired to 0xffffffff, base must be aligned to 16Mb. */
	bus_align = irongate_mem.start;
	bus_size = irongate_mem.end + 1 - bus_align;
	अगर (bus_align < 0x1000000UL)
		bus_align = 0x1000000UL;

	pci_mem = (0x100000000UL - bus_size) & -bus_align;
	irongate_mem.start = pci_mem;
	irongate_mem.end = 0xffffffffUL;

	/* Register our newly calculated PCI memory winकरोw in the resource
	   tree. */
	अगर (request_resource(&iomem_resource, &irongate_mem) < 0)
		prपूर्णांकk(KERN_ERR "Failed to request MEM on hose 0\n");

	prपूर्णांकk(KERN_INFO "Irongate pci_mem %pR\n", &irongate_mem);

	अगर (pci_mem < memtop)
		memtop = pci_mem;
	अगर (memtop > alpha_mv.min_mem_address) अणु
		मुक्त_reserved_area(__va(alpha_mv.min_mem_address),
				   __va(memtop), -1, शून्य);
		prपूर्णांकk(KERN_INFO "nautilus_init_pci: %ldk freed\n",
			(memtop - alpha_mv.min_mem_address) >> 10);
	पूर्ण
	अगर ((IRONGATE0->dev_venकरोr >> 16) > 0x7006)	/* Albacore? */
		IRONGATE0->pci_mem = pci_mem;

	pci_bus_assign_resources(bus);
	pci_bus_add_devices(bus);
पूर्ण

/*
 * The System Vectors
 */

काष्ठा alpha_machine_vector nautilus_mv __iniपंचांगv = अणु
	.vector_name		= "Nautilus",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_IRONGATE_IO,
	.machine_check		= nautilus_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= IRONGATE_DEFAULT_MEM_BASE,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= isa_device_पूर्णांकerrupt,

	.init_arch		= irongate_init_arch,
	.init_irq		= nautilus_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= nautilus_init_pci,
	.समाप्त_arch		= nautilus_समाप्त_arch,
	.pci_map_irq		= nautilus_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(nautilus)
