<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_jensen.c
 *
 *	Copyright (C) 1995 Linus Torvalds
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the Jensen.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ptrace.h>

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/jensen.h>
#अघोषित  __EXTERN_INLINE

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/*
 * Jensen is special: the vector is 0x8X0 क्रम EISA पूर्णांकerrupt X, and
 * 0x9X0 क्रम the local motherboard पूर्णांकerrupts.
 *
 * Note especially that those local पूर्णांकerrupts CANNOT be masked,
 * which causes much of the pain below...
 *
 *	0x660 - NMI
 *
 *	0x800 - IRQ0  पूर्णांकerval समयr (not used, as we use the RTC समयr)
 *	0x810 - IRQ1  line prपूर्णांकer (duh..)
 *	0x860 - IRQ6  floppy disk
 *
 *	0x900 - COM1
 *	0x920 - COM2
 *	0x980 - keyboard
 *	0x990 - mouse
 *
 * PCI-based प्रणालीs are more sane: they करोn't have the local
 * पूर्णांकerrupts at all, and have only normal PCI पूर्णांकerrupts from
 * devices.  Happily it's easy enough to करो a sane mapping from the
 * Jensen.
 * 
 * Note that this means that we may have to करो a hardware
 * "local_op" to a dअगरferent पूर्णांकerrupt than we report to the rest of the
 * world.
 */

अटल व्योम
jensen_local_enable(काष्ठा irq_data *d)
अणु
	/* the parport is really hw IRQ 1, silly Jensen.  */
	अगर (d->irq == 7)
		i8259a_enable_irq(d);
पूर्ण

अटल व्योम
jensen_local_disable(काष्ठा irq_data *d)
अणु
	/* the parport is really hw IRQ 1, silly Jensen.  */
	अगर (d->irq == 7)
		i8259a_disable_irq(d);
पूर्ण

अटल व्योम
jensen_local_mask_ack(काष्ठा irq_data *d)
अणु
	/* the parport is really hw IRQ 1, silly Jensen.  */
	अगर (d->irq == 7)
		i8259a_mask_and_ack_irq(d);
पूर्ण

अटल काष्ठा irq_chip jensen_local_irq_type = अणु
	.name		= "LOCAL",
	.irq_unmask	= jensen_local_enable,
	.irq_mask	= jensen_local_disable,
	.irq_mask_ack	= jensen_local_mask_ack,
पूर्ण;

अटल व्योम 
jensen_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	चयन (vector) अणु
	हाल 0x660:
		prपूर्णांकk("Whee.. NMI received. Probable hardware error\n");
		prपूर्णांकk("61=%02x, 461=%02x\n", inb(0x61), inb(0x461));
		वापस;

	/* local device पूर्णांकerrupts: */
	हाल 0x900: irq = 4; अवरोध;		/* com1 -> irq 4 */
	हाल 0x920: irq = 3; अवरोध;		/* com2 -> irq 3 */
	हाल 0x980: irq = 1; अवरोध;		/* kbd -> irq 1 */
	हाल 0x990: irq = 9; अवरोध;		/* mouse -> irq 9 */

	शेष:
		अगर (vector > 0x900) अणु
			prपूर्णांकk("Unknown local interrupt %lx\n", vector);
			वापस;
		पूर्ण

		irq = (vector - 0x800) >> 4;
		अगर (irq == 1)
			irq = 7;
		अवरोध;
	पूर्ण

	/* If there is no handler yet... */
	अगर (!irq_has_action(irq)) अणु
	    /* If it is a local पूर्णांकerrupt that cannot be masked... */
	    अगर (vector >= 0x900)
	    अणु
	        /* Clear keyboard/mouse state */
	    	inb(0x64);
		inb(0x60);
		/* Reset serial ports */
		inb(0x3fa);
		inb(0x2fa);
		outb(0x0c, 0x3fc);
		outb(0x0c, 0x2fc);
		/* Clear NMI */
		outb(0,0x61);
		outb(0,0x461);
	    पूर्ण
	पूर्ण

#अगर 0
        /* A useful bit of code to find out अगर an पूर्णांकerrupt is going wild.  */
        अणु
          अटल अचिन्हित पूर्णांक last_msg = 0, last_cc = 0;
          अटल पूर्णांक last_irq = -1, count = 0;
          अचिन्हित पूर्णांक cc;

          __यंत्र __अस्थिर("rpcc %0" : "=r"(cc));
          ++count;
#घोषणा JENSEN_CYCLES_PER_SEC	(150000000)
          अगर (cc - last_msg > ((JENSEN_CYCLES_PER_SEC) * 3) ||
	      irq != last_irq) अणु
                prपूर्णांकk(KERN_CRIT " irq %d count %d cc %u @ %lx\n",
                       irq, count, cc-last_cc, get_irq_regs()->pc);
                count = 0;
                last_msg = cc;
                last_irq = irq;
          पूर्ण
          last_cc = cc;
        पूर्ण
#पूर्ण_अगर

	handle_irq(irq);
पूर्ण

अटल व्योम __init
jensen_init_irq(व्योम)
अणु
	init_i8259a_irqs();

	irq_set_chip_and_handler(1, &jensen_local_irq_type, handle_level_irq);
	irq_set_chip_and_handler(4, &jensen_local_irq_type, handle_level_irq);
	irq_set_chip_and_handler(3, &jensen_local_irq_type, handle_level_irq);
	irq_set_chip_and_handler(7, &jensen_local_irq_type, handle_level_irq);
	irq_set_chip_and_handler(9, &jensen_local_irq_type, handle_level_irq);

	common_init_isa_dma();
पूर्ण

अटल व्योम __init
jensen_init_arch(व्योम)
अणु
	काष्ठा pci_controller *hose;
#अगर_घोषित CONFIG_PCI
	अटल काष्ठा pci_dev fake_isa_bridge = अणु .dma_mask = 0xffffffffUL, पूर्ण;

	isa_bridge = &fake_isa_bridge;
#पूर्ण_अगर

	/* Create a hose so that we can report i/o base addresses to
	   userland.  */

	pci_isa_hose = hose = alloc_pci_controller();
	hose->io_space = &ioport_resource;
	hose->mem_space = &iomem_resource;
	hose->index = 0;

	hose->sparse_mem_base = EISA_MEM - IDENT_ADDR;
	hose->dense_mem_base = 0;
	hose->sparse_io_base = EISA_IO - IDENT_ADDR;
	hose->dense_io_base = 0;

	hose->sg_isa = hose->sg_pci = शून्य;
	__direct_map_base = 0;
	__direct_map_size = 0xffffffff;
पूर्ण

अटल व्योम
jensen_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la)
अणु
	prपूर्णांकk(KERN_CRIT "Machine check\n");
पूर्ण

/*
 * The System Vector
 */

काष्ठा alpha_machine_vector jensen_mv __iniपंचांगv = अणु
	.vector_name		= "Jensen",
	DO_EV4_MMU,
	IO_LITE(JENSEN,jensen),
	.machine_check		= jensen_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.rtc_port		= 0x170,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= jensen_device_पूर्णांकerrupt,

	.init_arch		= jensen_init_arch,
	.init_irq		= jensen_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= शून्य,
	.समाप्त_arch		= शून्य,
पूर्ण;
ALIAS_MV(jensen)
