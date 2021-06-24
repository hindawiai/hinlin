<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_titan.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996, 1999 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *      Copyright (C) 1999, 2000 Jeff Wiedemeier
 *
 * Code supporting TITAN प्रणालीs (EV6+TITAN), currently:
 *      Privateer
 *	Falcon
 *	Granite
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
#समावेश <यंत्र/core_titan.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"
#समावेश "err_impl.h"


/*
 * Titan generic
 */

/*
 * Titan supports up to 4 CPUs
 */
अटल अचिन्हित दीर्घ titan_cpu_irq_affinity[4] = अणु ~0UL, ~0UL, ~0UL, ~0UL पूर्ण;

/*
 * Mask is set (1) अगर enabled
 */
अटल अचिन्हित दीर्घ titan_cached_irq_mask;

/*
 * Need SMP-safe access to पूर्णांकerrupt CSRs
 */
DEFINE_SPINLOCK(titan_irq_lock);

अटल व्योम
titan_update_irq_hw(अचिन्हित दीर्घ mask)
अणु
	रेजिस्टर titan_cchip *cchip = TITAN_cchip;
	अचिन्हित दीर्घ isa_enable = 1UL << 55;
	रेजिस्टर पूर्णांक bcpu = boot_cpuid;

#अगर_घोषित CONFIG_SMP
	cpumask_t cpm;
	अस्थिर अचिन्हित दीर्घ *dim0, *dim1, *dim2, *dim3;
	अचिन्हित दीर्घ mask0, mask1, mask2, mask3, dummy;

	cpumask_copy(&cpm, cpu_present_mask);
	mask &= ~isa_enable;
	mask0 = mask & titan_cpu_irq_affinity[0];
	mask1 = mask & titan_cpu_irq_affinity[1];
	mask2 = mask & titan_cpu_irq_affinity[2];
	mask3 = mask & titan_cpu_irq_affinity[3];

	अगर (bcpu == 0) mask0 |= isa_enable;
	अन्यथा अगर (bcpu == 1) mask1 |= isa_enable;
	अन्यथा अगर (bcpu == 2) mask2 |= isa_enable;
	अन्यथा mask3 |= isa_enable;

	dim0 = &cchip->dim0.csr;
	dim1 = &cchip->dim1.csr;
	dim2 = &cchip->dim2.csr;
	dim3 = &cchip->dim3.csr;
	अगर (!cpumask_test_cpu(0, &cpm)) dim0 = &dummy;
	अगर (!cpumask_test_cpu(1, &cpm)) dim1 = &dummy;
	अगर (!cpumask_test_cpu(2, &cpm)) dim2 = &dummy;
	अगर (!cpumask_test_cpu(3, &cpm)) dim3 = &dummy;

	*dim0 = mask0;
	*dim1 = mask1;
	*dim2 = mask2;
	*dim3 = mask3;
	mb();
	*dim0;
	*dim1;
	*dim2;
	*dim3;
#अन्यथा
	अस्थिर अचिन्हित दीर्घ *dimB;
	dimB = &cchip->dim0.csr;
	अगर (bcpu == 1) dimB = &cchip->dim1.csr;
	अन्यथा अगर (bcpu == 2) dimB = &cchip->dim2.csr;
	अन्यथा अगर (bcpu == 3) dimB = &cchip->dim3.csr;

	*dimB = mask | isa_enable;
	mb();
	*dimB;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम
titan_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	spin_lock(&titan_irq_lock);
	titan_cached_irq_mask |= 1UL << (irq - 16);
	titan_update_irq_hw(titan_cached_irq_mask);
	spin_unlock(&titan_irq_lock);
पूर्ण

अटल अंतरभूत व्योम
titan_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	spin_lock(&titan_irq_lock);
	titan_cached_irq_mask &= ~(1UL << (irq - 16));
	titan_update_irq_hw(titan_cached_irq_mask);
	spin_unlock(&titan_irq_lock);
पूर्ण

अटल व्योम
titan_cpu_set_irq_affinity(अचिन्हित पूर्णांक irq, cpumask_t affinity)
अणु
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < 4; cpu++) अणु
		अगर (cpumask_test_cpu(cpu, &affinity))
			titan_cpu_irq_affinity[cpu] |= 1UL << irq;
		अन्यथा
			titan_cpu_irq_affinity[cpu] &= ~(1UL << irq);
	पूर्ण

पूर्ण

अटल पूर्णांक
titan_set_irq_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *affinity,
		       bool क्रमce)
अणु 
	अचिन्हित पूर्णांक irq = d->irq;
	spin_lock(&titan_irq_lock);
	titan_cpu_set_irq_affinity(irq - 16, *affinity);
	titan_update_irq_hw(titan_cached_irq_mask);
	spin_unlock(&titan_irq_lock);

	वापस 0;
पूर्ण

अटल व्योम
titan_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	prपूर्णांकk("titan_device_interrupt: NOT IMPLEMENTED YET!!\n");
पूर्ण

अटल व्योम 
titan_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;
	handle_irq(irq);
पूर्ण


अटल व्योम __init
init_titan_irqs(काष्ठा irq_chip * ops, पूर्णांक imin, पूर्णांक imax)
अणु
	दीर्घ i;
	क्रम (i = imin; i <= imax; ++i) अणु
		irq_set_chip_and_handler(i, ops, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip titan_irq_type = अणु
       .name			= "TITAN",
       .irq_unmask		= titan_enable_irq,
       .irq_mask		= titan_disable_irq,
       .irq_mask_ack		= titan_disable_irq,
       .irq_set_affinity	= titan_set_irq_affinity,
पूर्ण;

अटल irqवापस_t
titan_पूर्णांकr_nop(पूर्णांक irq, व्योम *dev_id)
अणु
      /*
       * This is a NOP पूर्णांकerrupt handler क्रम the purposes of
       * event counting -- just वापस.
       */                                                                     
       वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init
titan_init_irq(व्योम)
अणु
	अगर (alpha_using_srm && !alpha_mv.device_पूर्णांकerrupt)
		alpha_mv.device_पूर्णांकerrupt = titan_srm_device_पूर्णांकerrupt;
	अगर (!alpha_mv.device_पूर्णांकerrupt)
		alpha_mv.device_पूर्णांकerrupt = titan_device_पूर्णांकerrupt;

	titan_update_irq_hw(0);

	init_titan_irqs(&titan_irq_type, 16, 63 + 16);
पूर्ण
  
अटल व्योम __init
titan_legacy_init_irq(व्योम)
अणु
	/* init the legacy dma controller */
	outb(0, DMA1_RESET_REG);
	outb(0, DMA2_RESET_REG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_REG);
	outb(0, DMA2_MASK_REG);

	/* init the legacy irq controller */
	init_i8259a_irqs();

	/* init the titan irqs */
	titan_init_irq();
पूर्ण

व्योम
titan_dispatch_irqs(u64 mask)
अणु
	अचिन्हित दीर्घ vector;

	/*
	 * Mask करोwn to those पूर्णांकerrupts which are enable on this processor
	 */
	mask &= titan_cpu_irq_affinity[smp_processor_id()];

	/*
	 * Dispatch all requested पूर्णांकerrupts 
	 */
	जबतक (mask) अणु
		/* convert to SRM vector... priority is <63> -> <0> */
		vector = 63 - __kernel_ctlz(mask);
		mask &= ~(1UL << vector);	/* clear it out 	 */
		vector = 0x900 + (vector << 4);	/* convert to SRM vector */
		
		/* dispatch it */
		alpha_mv.device_पूर्णांकerrupt(vector);
	पूर्ण
पूर्ण
  

/*
 * Titan Family
 */
अटल व्योम __init
titan_request_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		  अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname,
		  व्योम *dev_id)
अणु
	पूर्णांक err;
	err = request_irq(irq, handler, irqflags, devname, dev_id);
	अगर (err) अणु
		prपूर्णांकk("titan_request_irq for IRQ %d returned %d; ignoring\n",
		       irq, err);
	पूर्ण
पूर्ण

अटल व्योम __init
titan_late_init(व्योम)
अणु
	/*
	 * Enable the प्रणाली error पूर्णांकerrupts. These पूर्णांकerrupts are 
	 * all reported to the kernel as machine checks, so the handler
	 * is a nop so it can be called to count the inभागidual events.
	 */
	titan_request_irq(63+16, titan_पूर्णांकr_nop, 0,
		    "CChip Error", शून्य);
	titan_request_irq(62+16, titan_पूर्णांकr_nop, 0,
		    "PChip 0 H_Error", शून्य);
	titan_request_irq(61+16, titan_पूर्णांकr_nop, 0,
		    "PChip 1 H_Error", शून्य);
	titan_request_irq(60+16, titan_पूर्णांकr_nop, 0,
		    "PChip 0 C_Error", शून्य);
	titan_request_irq(59+16, titan_पूर्णांकr_nop, 0,
		    "PChip 1 C_Error", शून्य);

	/* 
	 * Register our error handlers.
	 */
	titan_रेजिस्टर_error_handlers();

	/*
	 * Check अगर the console left us any error logs.
	 */
	cdl_check_console_data_log();

पूर्ण

अटल पूर्णांक
titan_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	u8 पूर्णांकline;
	पूर्णांक irq;

 	/* Get the current पूर्णांकline.  */
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &पूर्णांकline);
	irq = पूर्णांकline;

 	/* Is it explicitly routed through ISA?  */
 	अगर ((irq & 0xF0) == 0xE0)
 		वापस irq;
 
 	/* Offset by 16 to make room क्रम ISA पूर्णांकerrupts 0 - 15.  */
 	वापस irq + 16;
पूर्ण

अटल व्योम __init
titan_init_pci(व्योम)
अणु
 	/*
 	 * This isn't really the right place, but there's some init
 	 * that needs to be करोne after everything is basically up.
 	 */
 	titan_late_init();
 
	/* Indicate that we trust the console to configure things properly */
	pci_set_flags(PCI_PROBE_ONLY);
	common_init_pci();
	SMC669_Init(0);
	locate_and_init_vga(शून्य);
पूर्ण


/*
 * Privateer
 */
अटल व्योम __init
निजीer_init_pci(व्योम)
अणु
	/*
	 * Hook a couple of extra err पूर्णांकerrupts that the
	 * common titan code won't.
	 */
	titan_request_irq(53+16, titan_पूर्णांकr_nop, 0,
		    "NMI", शून्य);
	titan_request_irq(50+16, titan_पूर्णांकr_nop, 0,
		    "Temperature Warning", शून्य);

	/*
	 * Finish with the common version.
	 */
	वापस titan_init_pci();
पूर्ण


/*
 * The System Vectors.
 */
काष्ठा alpha_machine_vector titan_mv __iniपंचांगv = अणु
	.vector_name		= "TITAN",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TITAN_IO,
	.machine_check		= titan_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TITAN_DAC_OFFSET,

	.nr_irqs		= 80,	/* 64 + 16 */
	/* device_पूर्णांकerrupt will be filled in by titan_init_irq */

	.agp_info		= titan_agp_info,

	.init_arch		= titan_init_arch,
	.init_irq		= titan_legacy_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= titan_init_pci,

	.समाप्त_arch		= titan_समाप्त_arch,
	.pci_map_irq		= titan_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(titan)

काष्ठा alpha_machine_vector निजीer_mv __iniपंचांगv = अणु
	.vector_name		= "PRIVATEER",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TITAN_IO,
	.machine_check		= निजीer_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TITAN_DAC_OFFSET,

	.nr_irqs		= 80,	/* 64 + 16 */
	/* device_पूर्णांकerrupt will be filled in by titan_init_irq */

	.agp_info		= titan_agp_info,

	.init_arch		= titan_init_arch,
	.init_irq		= titan_legacy_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= निजीer_init_pci,

	.समाप्त_arch		= titan_समाप्त_arch,
	.pci_map_irq		= titan_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
/* No alpha_mv alias क्रम निजीer since we compile it 
   in unconditionally with titan; setup_arch knows how to cope. */
