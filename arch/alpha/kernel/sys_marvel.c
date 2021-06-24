<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/alpha/kernel/sys_marvel.c
 *
 * Marvel / IO7 support
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_marvel.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/vga.h>

#समावेश "proto.h"
#समावेश "err_impl.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"

#अगर NR_IRQS < MARVEL_NR_IRQS
# error NR_IRQS < MARVEL_NR_IRQS !!!
#पूर्ण_अगर


/*
 * Interrupt handling.
 */
अटल व्योम 
io7_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित पूर्णांक pid;
	अचिन्हित पूर्णांक irq;

	/*
	 * Vector is 0x800 + (पूर्णांकerrupt)
	 *
	 * where (पूर्णांकerrupt) is:
	 *
	 *	...16|15 14|13     4|3 0
	 *	-----+-----+--------+---
	 *	  PE |  0  |   irq  | 0
	 *
	 * where (irq) is 
	 *
	 *       0x0800 - 0x0ff0	 - 0x0800 + (LSI id << 4)
	 *	 0x1000 - 0x2ff0	 - 0x1000 + (MSI_DAT<8:0> << 4)
	 */
	pid = vector >> 16;
	irq = ((vector & 0xffff) - 0x800) >> 4;

	irq += 16;				/* offset क्रम legacy */
	irq &= MARVEL_IRQ_VEC_IRQ_MASK;		/* not too many bits */
	irq |= pid << MARVEL_IRQ_VEC_PE_SHIFT;	/* merge the pid     */

	handle_irq(irq);
पूर्ण

अटल अस्थिर अचिन्हित दीर्घ *
io7_get_irq_ctl(अचिन्हित पूर्णांक irq, काष्ठा io7 **pio7)
अणु
	अस्थिर अचिन्हित दीर्घ *ctl;
	अचिन्हित पूर्णांक pid;
	काष्ठा io7 *io7;

	pid = irq >> MARVEL_IRQ_VEC_PE_SHIFT;

	अगर (!(io7 = marvel_find_io7(pid))) अणु
		prपूर्णांकk(KERN_ERR 
		       "%s for nonexistent io7 -- vec %x, pid %d\n",
		       __func__, irq, pid);
		वापस शून्य;
	पूर्ण

	irq &= MARVEL_IRQ_VEC_IRQ_MASK;	/* isolate the vector    */
	irq -= 16;			/* subtract legacy bias  */

	अगर (irq >= 0x180) अणु
		prपूर्णांकk(KERN_ERR 
		       "%s for invalid irq -- pid %d adjusted irq %x\n",
		       __func__, pid, irq);
		वापस शून्य;
	पूर्ण

	ctl = &io7->csrs->PO7_LSI_CTL[irq & 0xff].csr; /* assume LSI */
	अगर (irq >= 0x80)	     	/* MSI */
		ctl = &io7->csrs->PO7_MSI_CTL[((irq - 0x80) >> 5) & 0x0f].csr;

	अगर (pio7) *pio7 = io7;
	वापस ctl;
पूर्ण

अटल व्योम
io7_enable_irq(काष्ठा irq_data *d)
अणु
	अस्थिर अचिन्हित दीर्घ *ctl;
	अचिन्हित पूर्णांक irq = d->irq;
	काष्ठा io7 *io7;

	ctl = io7_get_irq_ctl(irq, &io7);
	अगर (!ctl || !io7) अणु
		prपूर्णांकk(KERN_ERR "%s: get_ctl failed for irq %x\n",
		       __func__, irq);
		वापस;
	पूर्ण

	raw_spin_lock(&io7->irq_lock);
	*ctl |= 1UL << 24;
	mb();
	*ctl;
	raw_spin_unlock(&io7->irq_lock);
पूर्ण

अटल व्योम
io7_disable_irq(काष्ठा irq_data *d)
अणु
	अस्थिर अचिन्हित दीर्घ *ctl;
	अचिन्हित पूर्णांक irq = d->irq;
	काष्ठा io7 *io7;

	ctl = io7_get_irq_ctl(irq, &io7);
	अगर (!ctl || !io7) अणु
		prपूर्णांकk(KERN_ERR "%s: get_ctl failed for irq %x\n",
		       __func__, irq);
		वापस;
	पूर्ण

	raw_spin_lock(&io7->irq_lock);
	*ctl &= ~(1UL << 24);
	mb();
	*ctl;
	raw_spin_unlock(&io7->irq_lock);
पूर्ण

अटल व्योम
marvel_irq_noop(काष्ठा irq_data *d)
अणु
	वापस;
पूर्ण

अटल काष्ठा irq_chip marvel_legacy_irq_type = अणु
	.name		= "LEGACY",
	.irq_mask	= marvel_irq_noop,
	.irq_unmask	= marvel_irq_noop,
पूर्ण;

अटल काष्ठा irq_chip io7_lsi_irq_type = अणु
	.name		= "LSI",
	.irq_unmask	= io7_enable_irq,
	.irq_mask	= io7_disable_irq,
	.irq_mask_ack	= io7_disable_irq,
पूर्ण;

अटल काष्ठा irq_chip io7_msi_irq_type = अणु
	.name		= "MSI",
	.irq_unmask	= io7_enable_irq,
	.irq_mask	= io7_disable_irq,
	.irq_ack	= marvel_irq_noop,
पूर्ण;

अटल व्योम
io7_redirect_irq(काष्ठा io7 *io7, 
		 अस्थिर अचिन्हित दीर्घ *csr, 
		 अचिन्हित पूर्णांक where)
अणु
	अचिन्हित दीर्घ val;
	
	val = *csr;
	val &= ~(0x1ffUL << 24);		/* clear the target pid   */
	val |= ((अचिन्हित दीर्घ)where << 24);	/* set the new target pid */
	
	*csr = val;
	mb();
	*csr;
पूर्ण

अटल व्योम 
io7_redirect_one_lsi(काष्ठा io7 *io7, अचिन्हित पूर्णांक which, अचिन्हित पूर्णांक where)
अणु
	अचिन्हित दीर्घ val;

	/*
	 * LSI_CTL has target PID @ 14
	 */
	val = io7->csrs->PO7_LSI_CTL[which].csr;
	val &= ~(0x1ffUL << 14);		/* clear the target pid */
	val |= ((अचिन्हित दीर्घ)where << 14);	/* set the new target pid */

	io7->csrs->PO7_LSI_CTL[which].csr = val;
	mb();
	io7->csrs->PO7_LSI_CTL[which].csr;
पूर्ण

अटल व्योम 
io7_redirect_one_msi(काष्ठा io7 *io7, अचिन्हित पूर्णांक which, अचिन्हित पूर्णांक where)
अणु
	अचिन्हित दीर्घ val;

	/*
	 * MSI_CTL has target PID @ 14
	 */
	val = io7->csrs->PO7_MSI_CTL[which].csr;
	val &= ~(0x1ffUL << 14);		/* clear the target pid */
	val |= ((अचिन्हित दीर्घ)where << 14);	/* set the new target pid */

	io7->csrs->PO7_MSI_CTL[which].csr = val;
	mb();
	io7->csrs->PO7_MSI_CTL[which].csr;
पूर्ण

अटल व्योम __init
init_one_io7_lsi(काष्ठा io7 *io7, अचिन्हित पूर्णांक which, अचिन्हित पूर्णांक where)
अणु
	/*
	 * LSI_CTL has target PID @ 14
	 */
	io7->csrs->PO7_LSI_CTL[which].csr = ((अचिन्हित दीर्घ)where << 14);
	mb();
	io7->csrs->PO7_LSI_CTL[which].csr;
पूर्ण

अटल व्योम __init
init_one_io7_msi(काष्ठा io7 *io7, अचिन्हित पूर्णांक which, अचिन्हित पूर्णांक where)
अणु
	/*
	 * MSI_CTL has target PID @ 14
	 */
	io7->csrs->PO7_MSI_CTL[which].csr = ((अचिन्हित दीर्घ)where << 14);
	mb();
	io7->csrs->PO7_MSI_CTL[which].csr;
पूर्ण

अटल व्योम __init
init_io7_irqs(काष्ठा io7 *io7, 
	      काष्ठा irq_chip *lsi_ops,
	      काष्ठा irq_chip *msi_ops)
अणु
	दीर्घ base = (io7->pe << MARVEL_IRQ_VEC_PE_SHIFT) + 16;
	दीर्घ i;

	prपूर्णांकk("Initializing interrupts for IO7 at PE %u - base %lx\n",
		io7->pe, base);

	/*
	 * Where should पूर्णांकerrupts from this IO7 go?
	 *
	 * They really should be sent to the local CPU to aव्योम having to
	 * traverse the mesh, but अगर it's not an SMP kernel, they have to
	 * go to the boot CPU. Send them all to the boot CPU क्रम now,
	 * as each secondary starts, it can redirect it's local device 
	 * पूर्णांकerrupts.
	 */
	prपूर्णांकk("  Interrupts reported to CPU at PE %u\n", boot_cpuid);

	raw_spin_lock(&io7->irq_lock);

	/* set up the error irqs */
	io7_redirect_irq(io7, &io7->csrs->HLT_CTL.csr, boot_cpuid);
	io7_redirect_irq(io7, &io7->csrs->HPI_CTL.csr, boot_cpuid);
	io7_redirect_irq(io7, &io7->csrs->CRD_CTL.csr, boot_cpuid);
	io7_redirect_irq(io7, &io7->csrs->STV_CTL.csr, boot_cpuid);
	io7_redirect_irq(io7, &io7->csrs->HEI_CTL.csr, boot_cpuid);

	/* Set up the lsi irqs.  */
	क्रम (i = 0; i < 128; ++i) अणु
		irq_set_chip_and_handler(base + i, lsi_ops, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	/* Disable the implemented irqs in hardware.  */
	क्रम (i = 0; i < 0x60; ++i) 
		init_one_io7_lsi(io7, i, boot_cpuid);

	init_one_io7_lsi(io7, 0x74, boot_cpuid);
	init_one_io7_lsi(io7, 0x75, boot_cpuid);


	/* Set up the msi irqs.  */
	क्रम (i = 128; i < (128 + 512); ++i) अणु
		irq_set_chip_and_handler(base + i, msi_ops, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	क्रम (i = 0; i < 16; ++i)
		init_one_io7_msi(io7, i, boot_cpuid);

	raw_spin_unlock(&io7->irq_lock);
पूर्ण

अटल व्योम __init
marvel_init_irq(व्योम)
अणु
	पूर्णांक i;
	काष्ठा io7 *io7 = शून्य;

	/* Reserve the legacy irqs.  */
	क्रम (i = 0; i < 16; ++i) अणु
		irq_set_chip_and_handler(i, &marvel_legacy_irq_type,
					 handle_level_irq);
	पूर्ण

	/* Init the io7 irqs.  */
	क्रम (io7 = शून्य; (io7 = marvel_next_io7(io7)) != शून्य; )
		init_io7_irqs(io7, &io7_lsi_irq_type, &io7_msi_irq_type);
पूर्ण

अटल पूर्णांक 
marvel_map_irq(स्थिर काष्ठा pci_dev *cdev, u8 slot, u8 pin)
अणु
	काष्ठा pci_dev *dev = (काष्ठा pci_dev *)cdev;
	काष्ठा pci_controller *hose = dev->sysdata;
	काष्ठा io7_port *io7_port = hose->sysdata;
	काष्ठा io7 *io7 = io7_port->io7;
	पूर्णांक msi_loc, msi_data_off;
	u16 msg_ctl;
	u16 msg_dat;
	u8 पूर्णांकline; 
	पूर्णांक irq;

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &पूर्णांकline);
	irq = पूर्णांकline;

	msi_loc = dev->msi_cap;
	msg_ctl = 0;
	अगर (msi_loc) 
		pci_पढ़ो_config_word(dev, msi_loc + PCI_MSI_FLAGS, &msg_ctl);

	अगर (msg_ctl & PCI_MSI_FLAGS_ENABLE) अणु
 		msi_data_off = PCI_MSI_DATA_32;
		अगर (msg_ctl & PCI_MSI_FLAGS_64BIT) 
			msi_data_off = PCI_MSI_DATA_64;
		pci_पढ़ो_config_word(dev, msi_loc + msi_data_off, &msg_dat);

		irq = msg_dat & 0x1ff;		/* we use msg_data<8:0> */
		irq += 0x80;			/* offset क्रम lsi       */

#अगर 1
		prपूर्णांकk("PCI:%d:%d:%d (hose %d) is using MSI\n",
		       dev->bus->number, 
		       PCI_SLOT(dev->devfn), 
		       PCI_FUNC(dev->devfn),
		       hose->index);
		prपूर्णांकk("  %d message(s) from 0x%04x\n", 
		       1 << ((msg_ctl & PCI_MSI_FLAGS_QSIZE) >> 4),
		       msg_dat);
		prपूर्णांकk("  reporting on %d IRQ(s) from %d (0x%x)\n", 
		       1 << ((msg_ctl & PCI_MSI_FLAGS_QSIZE) >> 4),
		       (irq + 16) | (io7->pe << MARVEL_IRQ_VEC_PE_SHIFT),
		       (irq + 16) | (io7->pe << MARVEL_IRQ_VEC_PE_SHIFT));
#पूर्ण_अगर

#अगर 0
		pci_ग_लिखो_config_word(dev, msi_loc + PCI_MSI_FLAGS,
				      msg_ctl & ~PCI_MSI_FLAGS_ENABLE);
		pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &पूर्णांकline);
		irq = पूर्णांकline;

		prपूर्णांकk("  forcing LSI interrupt on irq %d [0x%x]\n", irq, irq);
#पूर्ण_अगर
	पूर्ण

	irq += 16;					/* offset क्रम legacy */
	irq |= io7->pe << MARVEL_IRQ_VEC_PE_SHIFT;	/* merge the pid     */

	वापस irq; 
पूर्ण

अटल व्योम __init
marvel_init_pci(व्योम)
अणु
	काष्ठा io7 *io7;

	marvel_रेजिस्टर_error_handlers();

	/* Indicate that we trust the console to configure things properly */
	pci_set_flags(PCI_PROBE_ONLY);
	common_init_pci();
	locate_and_init_vga(शून्य);

	/* Clear any io7 errors.  */
	क्रम (io7 = शून्य; (io7 = marvel_next_io7(io7)) != शून्य; ) 
		io7_clear_errors(io7);
पूर्ण

अटल व्योम __init
marvel_init_rtc(व्योम)
अणु
	init_rtc_irq(शून्य);
पूर्ण

अटल व्योम
marvel_smp_callin(व्योम)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();
	काष्ठा io7 *io7 = marvel_find_io7(cpuid);
	अचिन्हित पूर्णांक i;

	अगर (!io7)
		वापस;

	/* 
	 * There is a local IO7 - redirect all of its पूर्णांकerrupts here.
	 */
	prपूर्णांकk("Redirecting IO7 interrupts to local CPU at PE %u\n", cpuid);

	/* Redirect the error IRQS here.  */
	io7_redirect_irq(io7, &io7->csrs->HLT_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->HPI_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->CRD_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->STV_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->HEI_CTL.csr, cpuid);

	/* Redirect the implemented LSIs here.  */
	क्रम (i = 0; i < 0x60; ++i) 
		io7_redirect_one_lsi(io7, i, cpuid);

	io7_redirect_one_lsi(io7, 0x74, cpuid);
	io7_redirect_one_lsi(io7, 0x75, cpuid);

	/* Redirect the MSIs here.  */
	क्रम (i = 0; i < 16; ++i)
		io7_redirect_one_msi(io7, i, cpuid);
पूर्ण

/*
 * System Vectors
 */
काष्ठा alpha_machine_vector marvel_ev7_mv __iniपंचांगv = अणु
	.vector_name		= "MARVEL/EV7",
	DO_EV7_MMU,
	.rtc_port		= 0x70,
	.rtc_boot_cpu_only	= 1,
	DO_MARVEL_IO,
	.machine_check		= marvel_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= IO7_DAC_OFFSET,

	.nr_irqs		= MARVEL_NR_IRQS,
	.device_पूर्णांकerrupt	= io7_device_पूर्णांकerrupt,

	.agp_info		= marvel_agp_info,

	.smp_callin		= marvel_smp_callin,
	.init_arch		= marvel_init_arch,
	.init_irq		= marvel_init_irq,
	.init_rtc		= marvel_init_rtc,
	.init_pci		= marvel_init_pci,
	.समाप्त_arch		= marvel_समाप्त_arch,
	.pci_map_irq		= marvel_map_irq,
	.pci_swizzle		= common_swizzle,

	.pa_to_nid		= marvel_pa_to_nid,
	.cpuid_to_nid		= marvel_cpuid_to_nid,
	.node_mem_start		= marvel_node_mem_start,
	.node_mem_size		= marvel_node_mem_size,
पूर्ण;
ALIAS_MV(marvel_ev7)
