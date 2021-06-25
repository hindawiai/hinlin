<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/sys_wildfire.c
 *
 *  Wildfire support.
 *
 *  Copyright (C) 2000 Andrea Arcangeli <andrea@suse.de> SuSE
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
#समावेश <यंत्र/core_wildfire.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"

अटल अचिन्हित दीर्घ cached_irq_mask[WILDFIRE_NR_IRQS/(माप(दीर्घ)*8)];

DEFINE_SPINLOCK(wildfire_irq_lock);

अटल पूर्णांक करोing_init_irq_hw = 0;

अटल व्योम
wildfire_update_irq_hw(अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक qbbno = (irq >> 8) & (WILDFIRE_MAX_QBB - 1);
	पूर्णांक pcano = (irq >> 6) & (WILDFIRE_PCA_PER_QBB - 1);
	wildfire_pca *pca;
	अस्थिर अचिन्हित दीर्घ * enable0;

	अगर (!WILDFIRE_PCA_EXISTS(qbbno, pcano)) अणु
		अगर (!करोing_init_irq_hw) अणु
			prपूर्णांकk(KERN_ERR "wildfire_update_irq_hw:"
			       " got irq %d for non-existent PCA %d"
			       " on QBB %d.\n",
			       irq, pcano, qbbno);
		पूर्ण
		वापस;
	पूर्ण

	pca = WILDFIRE_pca(qbbno, pcano);
	enable0 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[0].enable; /* ??? */

	*enable0 = cached_irq_mask[qbbno * WILDFIRE_PCA_PER_QBB + pcano];
	mb();
	*enable0;
पूर्ण

अटल व्योम __init
wildfire_init_irq_hw(व्योम)
अणु
#अगर 0
	रेजिस्टर wildfire_pca * pca = WILDFIRE_pca(0, 0);
	अस्थिर अचिन्हित दीर्घ * enable0, * enable1, * enable2, *enable3;
	अस्थिर अचिन्हित दीर्घ * target0, * target1, * target2, *target3;

	enable0 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[0].enable;
	enable1 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[1].enable;
	enable2 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[2].enable;
	enable3 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[3].enable;

	target0 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[0].target;
	target1 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[1].target;
	target2 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[2].target;
	target3 = (अचिन्हित दीर्घ *) &pca->pca_पूर्णांक[3].target;

	*enable0 = *enable1 = *enable2 = *enable3 = 0;

	*target0 = (1UL<<8) | WILDFIRE_QBB(0);
	*target1 = *target2 = *target3 = 0;

	mb();

	*enable0; *enable1; *enable2; *enable3;
	*target0; *target1; *target2; *target3;

#अन्यथा
	पूर्णांक i;

	करोing_init_irq_hw = 1;

	/* Need to update only once क्रम every possible PCA. */
	क्रम (i = 0; i < WILDFIRE_NR_IRQS; i+=WILDFIRE_IRQ_PER_PCA)
		wildfire_update_irq_hw(i);

	करोing_init_irq_hw = 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम
wildfire_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर (irq < 16)
		i8259a_enable_irq(d);

	spin_lock(&wildfire_irq_lock);
	set_bit(irq, &cached_irq_mask);
	wildfire_update_irq_hw(irq);
	spin_unlock(&wildfire_irq_lock);
पूर्ण

अटल व्योम
wildfire_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर (irq < 16)
		i8259a_disable_irq(d);

	spin_lock(&wildfire_irq_lock);
	clear_bit(irq, &cached_irq_mask);
	wildfire_update_irq_hw(irq);
	spin_unlock(&wildfire_irq_lock);
पूर्ण

अटल व्योम
wildfire_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर (irq < 16)
		i8259a_mask_and_ack_irq(d);

	spin_lock(&wildfire_irq_lock);
	clear_bit(irq, &cached_irq_mask);
	wildfire_update_irq_hw(irq);
	spin_unlock(&wildfire_irq_lock);
पूर्ण

अटल काष्ठा irq_chip wildfire_irq_type = अणु
	.name		= "WILDFIRE",
	.irq_unmask	= wildfire_enable_irq,
	.irq_mask	= wildfire_disable_irq,
	.irq_mask_ack	= wildfire_mask_and_ack_irq,
पूर्ण;

अटल व्योम __init
wildfire_init_irq_per_pca(पूर्णांक qbbno, पूर्णांक pcano)
अणु
	पूर्णांक i, irq_bias;

	irq_bias = qbbno * (WILDFIRE_PCA_PER_QBB * WILDFIRE_IRQ_PER_PCA)
		 + pcano * WILDFIRE_IRQ_PER_PCA;

#अगर 0
	अचिन्हित दीर्घ io_bias;

	/* Only need the following क्रम first PCI bus per PCA. */
	io_bias = WILDFIRE_IO(qbbno, pcano<<1) - WILDFIRE_IO_BIAS;

	outb(0, DMA1_RESET_REG + io_bias);
	outb(0, DMA2_RESET_REG + io_bias);
	outb(DMA_MODE_CASCADE, DMA2_MODE_REG + io_bias);
	outb(0, DMA2_MASK_REG + io_bias);
#पूर्ण_अगर

#अगर 0
	/* ??? Not sure how to करो this, yet... */
	init_i8259a_irqs(); /* ??? */
#पूर्ण_अगर

	क्रम (i = 0; i < 16; ++i) अणु
		अगर (i == 2)
			जारी;
		irq_set_chip_and_handler(i + irq_bias, &wildfire_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i + irq_bias, IRQ_LEVEL);
	पूर्ण

	irq_set_chip_and_handler(36 + irq_bias, &wildfire_irq_type,
				 handle_level_irq);
	irq_set_status_flags(36 + irq_bias, IRQ_LEVEL);
	क्रम (i = 40; i < 64; ++i) अणु
		irq_set_chip_and_handler(i + irq_bias, &wildfire_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i + irq_bias, IRQ_LEVEL);
	पूर्ण

	अगर (request_irq(32 + irq_bias, no_action, 0, "isa_enable", शून्य))
		pr_err("Failed to register isa_enable interrupt\n");
पूर्ण

अटल व्योम __init
wildfire_init_irq(व्योम)
अणु
	पूर्णांक qbbno, pcano;

#अगर 1
	wildfire_init_irq_hw();
	init_i8259a_irqs();
#पूर्ण_अगर

	क्रम (qbbno = 0; qbbno < WILDFIRE_MAX_QBB; qbbno++) अणु
	  अगर (WILDFIRE_QBB_EXISTS(qbbno)) अणु
	    क्रम (pcano = 0; pcano < WILDFIRE_PCA_PER_QBB; pcano++) अणु
	      अगर (WILDFIRE_PCA_EXISTS(qbbno, pcano)) अणु
		wildfire_init_irq_per_pca(qbbno, pcano);
	      पूर्ण
	    पूर्ण
	  पूर्ण
	पूर्ण
पूर्ण

अटल व्योम 
wildfire_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * bits 10-8:	source QBB ID
	 * bits 7-6:	PCA
	 * bits 5-0:	irq in PCA
	 */

	handle_irq(irq);
	वापस;
पूर्ण

/*
 * PCI Fixup configuration.
 *
 * Summary per PCA (2 PCI or HIPPI buses):
 *
 * Bit      Meaning
 * 0-15     ISA
 *
 *32        ISA summary
 *33        SMI
 *34        NMI
 *36        builtin QLogic SCSI (or slot 0 अगर no IO module)
 *40        Interrupt Line A from slot 2 PCI0
 *41        Interrupt Line B from slot 2 PCI0
 *42        Interrupt Line C from slot 2 PCI0
 *43        Interrupt Line D from slot 2 PCI0
 *44        Interrupt Line A from slot 3 PCI0
 *45        Interrupt Line B from slot 3 PCI0
 *46        Interrupt Line C from slot 3 PCI0
 *47        Interrupt Line D from slot 3 PCI0
 *
 *48        Interrupt Line A from slot 4 PCI1
 *49        Interrupt Line B from slot 4 PCI1
 *50        Interrupt Line C from slot 4 PCI1
 *51        Interrupt Line D from slot 4 PCI1
 *52        Interrupt Line A from slot 5 PCI1
 *53        Interrupt Line B from slot 5 PCI1
 *54        Interrupt Line C from slot 5 PCI1
 *55        Interrupt Line D from slot 5 PCI1
 *56        Interrupt Line A from slot 6 PCI1
 *57        Interrupt Line B from slot 6 PCI1
 *58        Interrupt Line C from slot 6 PCI1
 *50        Interrupt Line D from slot 6 PCI1
 *60        Interrupt Line A from slot 7 PCI1
 *61        Interrupt Line B from slot 7 PCI1
 *62        Interrupt Line C from slot 7 PCI1
 *63        Interrupt Line D from slot 7 PCI1
 * 
 *
 * IdSel	
 *   0	 Cypress Bridge I/O (ISA summary पूर्णांकerrupt)
 *   1	 64 bit PCI 0 option slot 1 (SCSI QLogic builtin)
 *   2	 64 bit PCI 0 option slot 2
 *   3	 64 bit PCI 0 option slot 3
 *   4	 64 bit PCI 1 option slot 4
 *   5	 64 bit PCI 1 option slot 5
 *   6	 64 bit PCI 1 option slot 6
 *   7	 64 bit PCI 1 option slot 7
 */

अटल पूर्णांक
wildfire_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[8][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 0 ISA Bridge */
		अणु 36,    36,    36+1, 36+2, 36+3पूर्ण, /* IdSel 1 SCSI builtin */
		अणु 40,    40,    40+1, 40+2, 40+3पूर्ण, /* IdSel 2 PCI 0 slot 2 */
		अणु 44,    44,    44+1, 44+2, 44+3पूर्ण, /* IdSel 3 PCI 0 slot 3 */
		अणु 48,    48,    48+1, 48+2, 48+3पूर्ण, /* IdSel 4 PCI 1 slot 4 */
		अणु 52,    52,    52+1, 52+2, 52+3पूर्ण, /* IdSel 5 PCI 1 slot 5 */
		अणु 56,    56,    56+1, 56+2, 56+3पूर्ण, /* IdSel 6 PCI 1 slot 6 */
		अणु 60,    60,    60+1, 60+2, 60+3पूर्ण, /* IdSel 7 PCI 1 slot 7 */
	पूर्ण;
	दीर्घ min_idsel = 0, max_idsel = 7, irqs_per_slot = 5;

	काष्ठा pci_controller *hose = dev->sysdata;
	पूर्णांक irq = COMMON_TABLE_LOOKUP;

	अगर (irq > 0) अणु
		पूर्णांक qbbno = hose->index >> 3;
		पूर्णांक pcano = (hose->index >> 1) & 3;
		irq += (qbbno << 8) + (pcano << 6);
	पूर्ण
	वापस irq;
पूर्ण


/*
 * The System Vectors
 */

काष्ठा alpha_machine_vector wildfire_mv __iniपंचांगv = अणु
	.vector_name		= "WILDFIRE",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_WILDFIRE_IO,
	.machine_check		= wildfire_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,

	.nr_irqs		= WILDFIRE_NR_IRQS,
	.device_पूर्णांकerrupt	= wildfire_device_पूर्णांकerrupt,

	.init_arch		= wildfire_init_arch,
	.init_irq		= wildfire_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.समाप्त_arch		= wildfire_समाप्त_arch,
	.pci_map_irq		= wildfire_map_irq,
	.pci_swizzle		= common_swizzle,

	.pa_to_nid		= wildfire_pa_to_nid,
	.cpuid_to_nid		= wildfire_cpuid_to_nid,
	.node_mem_start		= wildfire_node_mem_start,
	.node_mem_size		= wildfire_node_mem_size,
पूर्ण;
ALIAS_MV(wildfire)
