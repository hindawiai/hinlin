<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I/O SAPIC support.
 *
 * Copyright (C) 1999 Intel Corp.
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 2000-2002 J.I. Lee <jung-ik.lee@पूर्णांकel.com>
 * Copyright (C) 1999-2000, 2002-2003 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999,2000 Walt Drummond <drummond@valinux.com>
 *
 * 00/04/19	D. Mosberger	Rewritten to mirror more बंदly the x86 I/O
 *				APIC code.  In particular, we now have separate
 *				handlers क्रम edge and level triggered
 *				पूर्णांकerrupts.
 * 00/10/27	Asit Mallick, Goutham Rao <goutham.rao@पूर्णांकel.com> IRQ vector
 *				allocation PCI to vector mapping, shared PCI
 *				पूर्णांकerrupts.
 * 00/10/27	D. Mosberger	Document things a bit more to make them more
 *				understandable.  Clean up much of the old
 *				IOSAPIC cruft.
 * 01/07/27	J.I. Lee	PCI irq routing, Platक्रमm/Legacy पूर्णांकerrupts
 *				and fixes क्रम ACPI S5(SoftOff) support.
 * 02/01/23	J.I. Lee	iosapic pgm fixes क्रम PCI irq routing from _PRT
 * 02/01/07     E. Focht        <efocht@ess.nec.de> Redirectable पूर्णांकerrupt
 *				vectors in iosapic_set_affinity(),
 *				initializations क्रम /proc/irq/#/smp_affinity
 * 02/04/02	P. Diefenbaugh	Cleaned up ACPI PCI IRQ routing.
 * 02/04/18	J.I. Lee	bug fix in iosapic_init_pci_irq
 * 02/04/30	J.I. Lee	bug fix in find_iosapic to fix ACPI PCI IRQ to
 *				IOSAPIC mapping error
 * 02/07/29	T. Kochi	Allocate पूर्णांकerrupt vectors dynamically
 * 02/08/04	T. Kochi	Cleaned up terminology (irq, global प्रणाली
 *				पूर्णांकerrupt, vector, etc.)
 * 02/09/20	D. Mosberger	Simplअगरied by taking advantage of ACPI's
 *				pci_irq code.
 * 03/02/19	B. Helgaas	Make pcat_compat प्रणाली-wide, not per-IOSAPIC.
 *				Remove iosapic_address & gsi_base from
 *				बाह्यal पूर्णांकerfaces.  Rationalize
 *				__init/__devinit attributes.
 * 04/12/04 Ashok Raj	<ashok.raj@पूर्णांकel.com> Intel Corporation 2004
 *				Updated to work with irq migration necessary
 *				क्रम CPU Hotplug
 */
/*
 * Here is what the पूर्णांकerrupt logic between a PCI device and the kernel looks
 * like:
 *
 * (1) A PCI device उठाओs one of the four पूर्णांकerrupt pins (INTA, INTB, INTC,
 *     INTD).  The device is uniquely identअगरied by its bus-, and slot-number
 *     (the function number करोes not matter here because all functions share
 *     the same पूर्णांकerrupt lines).
 *
 * (2) The motherboard routes the पूर्णांकerrupt line to a pin on a IOSAPIC
 *     controller.  Multiple पूर्णांकerrupt lines may have to share the same
 *     IOSAPIC pin (अगर they're level triggered and use the same polarity).
 *     Each पूर्णांकerrupt line has a unique Global System Interrupt (GSI) number
 *     which can be calculated as the sum of the controller's base GSI number
 *     and the IOSAPIC pin number to which the line connects.
 *
 * (3) The IOSAPIC uses an पूर्णांकernal routing table entries (RTEs) to map the
 * IOSAPIC pin पूर्णांकo the IA-64 पूर्णांकerrupt vector.  This पूर्णांकerrupt vector is then
 * sent to the CPU.
 *
 * (4) The kernel recognizes an पूर्णांकerrupt as an IRQ.  The IRQ पूर्णांकerface is
 *     used as architecture-independent पूर्णांकerrupt handling mechanism in Linux.
 *     As an IRQ is a number, we have to have
 *     IA-64 पूर्णांकerrupt vector number <-> IRQ number mapping.  On smaller
 *     प्रणालीs, we use one-to-one mapping between IA-64 vector and IRQ.
 *
 * To sum up, there are three levels of mappings involved:
 *
 *	PCI pin -> global प्रणाली पूर्णांकerrupt (GSI) -> IA-64 vector <-> IRQ
 *
 * Note: The term "IRQ" is loosely used everywhere in Linux kernel to
 * describe पूर्णांकerrupts.  Now we use "IRQ" only क्रम Linux IRQ's.  ISA IRQ
 * (isa_irq) is the only exception in this source code.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/iosapic.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/xtp.h>

#अघोषित DEBUG_INTERRUPT_ROUTING

#अगर_घोषित DEBUG_INTERRUPT_ROUTING
#घोषणा DBG(fmt...)	prपूर्णांकk(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(iosapic_lock);

/*
 * These tables map IA-64 vectors to the IOSAPIC pin that generates this
 * vector.
 */

#घोषणा NO_REF_RTE	0

अटल काष्ठा iosapic अणु
	अक्षर __iomem	*addr;		/* base address of IOSAPIC */
	अचिन्हित पूर्णांक	gsi_base;	/* GSI base */
	अचिन्हित लघु	num_rte;	/* # of RTEs on this IOSAPIC */
	पूर्णांक		rtes_inuse;	/* # of RTEs in use on this IOSAPIC */
#अगर_घोषित CONFIG_NUMA
	अचिन्हित लघु	node;		/* numa node association via pxm */
#पूर्ण_अगर
	spinlock_t	lock;		/* lock क्रम indirect reg access */
पूर्ण iosapic_lists[NR_IOSAPICS];

काष्ठा iosapic_rte_info अणु
	काष्ठा list_head rte_list;	/* RTEs sharing the same vector */
	अक्षर		rte_index;	/* IOSAPIC RTE index */
	पूर्णांक		refcnt;		/* reference counter */
	काष्ठा iosapic	*iosapic;
पूर्ण ____cacheline_aligned;

अटल काष्ठा iosapic_पूर्णांकr_info अणु
	काष्ठा list_head rtes;		/* RTEs using this vector (empty =>
					 * not an IOSAPIC पूर्णांकerrupt) */
	पूर्णांक		count;		/* # of रेजिस्टरed RTEs */
	u32		low32;		/* current value of low word of
					 * Redirection table entry */
	अचिन्हित पूर्णांक	dest;		/* destination CPU physical ID */
	अचिन्हित अक्षर	dmode	: 3;	/* delivery mode (see iosapic.h) */
	अचिन्हित अक्षर 	polarity: 1;	/* पूर्णांकerrupt polarity
					 * (see iosapic.h) */
	अचिन्हित अक्षर	trigger	: 1;	/* trigger mode (see iosapic.h) */
पूर्ण iosapic_पूर्णांकr_info[NR_IRQS];

अटल अचिन्हित अक्षर pcat_compat;	/* 8259 compatibility flag */

अटल अंतरभूत व्योम
iosapic_ग_लिखो(काष्ठा iosapic *iosapic, अचिन्हित पूर्णांक reg, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iosapic->lock, flags);
	__iosapic_ग_लिखो(iosapic->addr, reg, val);
	spin_unlock_irqrestore(&iosapic->lock, flags);
पूर्ण

/*
 * Find an IOSAPIC associated with a GSI
 */
अटल अंतरभूत पूर्णांक
find_iosapic (अचिन्हित पूर्णांक gsi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_IOSAPICS; i++) अणु
		अगर ((अचिन्हित) (gsi - iosapic_lists[i].gsi_base) <
		    iosapic_lists[i].num_rte)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक __gsi_to_irq(अचिन्हित पूर्णांक gsi)
अणु
	पूर्णांक irq;
	काष्ठा iosapic_पूर्णांकr_info *info;
	काष्ठा iosapic_rte_info *rte;

	क्रम (irq = 0; irq < NR_IRQS; irq++) अणु
		info = &iosapic_पूर्णांकr_info[irq];
		list_क्रम_each_entry(rte, &info->rtes, rte_list)
			अगर (rte->iosapic->gsi_base + rte->rte_index == gsi)
				वापस irq;
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक
gsi_to_irq (अचिन्हित पूर्णांक gsi)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक irq;

	spin_lock_irqsave(&iosapic_lock, flags);
	irq = __gsi_to_irq(gsi);
	spin_unlock_irqrestore(&iosapic_lock, flags);
	वापस irq;
पूर्ण

अटल काष्ठा iosapic_rte_info *find_rte(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक gsi)
अणु
	काष्ठा iosapic_rte_info *rte;

	list_क्रम_each_entry(rte, &iosapic_पूर्णांकr_info[irq].rtes, rte_list)
		अगर (rte->iosapic->gsi_base + rte->rte_index == gsi)
			वापस rte;
	वापस शून्य;
पूर्ण

अटल व्योम
set_rte (अचिन्हित पूर्णांक gsi, अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक dest, पूर्णांक mask)
अणु
	अचिन्हित दीर्घ pol, trigger, dmode;
	u32 low32, high32;
	पूर्णांक rte_index;
	अक्षर redir;
	काष्ठा iosapic_rte_info *rte;
	ia64_vector vector = irq_to_vector(irq);

	DBG(KERN_DEBUG"IOSAPIC: routing vector %d to 0x%x\n", vector, dest);

	rte = find_rte(irq, gsi);
	अगर (!rte)
		वापस;		/* not an IOSAPIC पूर्णांकerrupt */

	rte_index = rte->rte_index;
	pol     = iosapic_पूर्णांकr_info[irq].polarity;
	trigger = iosapic_पूर्णांकr_info[irq].trigger;
	dmode   = iosapic_पूर्णांकr_info[irq].dmode;

	redir = (dmode == IOSAPIC_LOWEST_PRIORITY) ? 1 : 0;

#अगर_घोषित CONFIG_SMP
	set_irq_affinity_info(irq, (पूर्णांक)(dest & 0xffff), redir);
#पूर्ण_अगर

	low32 = ((pol << IOSAPIC_POLARITY_SHIFT) |
		 (trigger << IOSAPIC_TRIGGER_SHIFT) |
		 (dmode << IOSAPIC_DELIVERY_SHIFT) |
		 ((mask ? 1 : 0) << IOSAPIC_MASK_SHIFT) |
		 vector);

	/* dest contains both id and eid */
	high32 = (dest << IOSAPIC_DEST_SHIFT);

	iosapic_ग_लिखो(rte->iosapic, IOSAPIC_RTE_HIGH(rte_index), high32);
	iosapic_ग_लिखो(rte->iosapic, IOSAPIC_RTE_LOW(rte_index), low32);
	iosapic_पूर्णांकr_info[irq].low32 = low32;
	iosapic_पूर्णांकr_info[irq].dest = dest;
पूर्ण

अटल व्योम
iosapic_nop (काष्ठा irq_data *data)
अणु
	/* करो nothing... */
पूर्ण


#अगर_घोषित CONFIG_KEXEC
व्योम
kexec_disable_iosapic(व्योम)
अणु
	काष्ठा iosapic_पूर्णांकr_info *info;
	काष्ठा iosapic_rte_info *rte;
	ia64_vector vec;
	पूर्णांक irq;

	क्रम (irq = 0; irq < NR_IRQS; irq++) अणु
		info = &iosapic_पूर्णांकr_info[irq];
		vec = irq_to_vector(irq);
		list_क्रम_each_entry(rte, &info->rtes,
				rte_list) अणु
			iosapic_ग_लिखो(rte->iosapic,
					IOSAPIC_RTE_LOW(rte->rte_index),
					IOSAPIC_MASK|vec);
			iosapic_eoi(rte->iosapic->addr, vec);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम
mask_irq (काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	u32 low32;
	पूर्णांक rte_index;
	काष्ठा iosapic_rte_info *rte;

	अगर (!iosapic_पूर्णांकr_info[irq].count)
		वापस;			/* not an IOSAPIC पूर्णांकerrupt! */

	/* set only the mask bit */
	low32 = iosapic_पूर्णांकr_info[irq].low32 |= IOSAPIC_MASK;
	list_क्रम_each_entry(rte, &iosapic_पूर्णांकr_info[irq].rtes, rte_list) अणु
		rte_index = rte->rte_index;
		iosapic_ग_लिखो(rte->iosapic, IOSAPIC_RTE_LOW(rte_index), low32);
	पूर्ण
पूर्ण

अटल व्योम
unmask_irq (काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	u32 low32;
	पूर्णांक rte_index;
	काष्ठा iosapic_rte_info *rte;

	अगर (!iosapic_पूर्णांकr_info[irq].count)
		वापस;			/* not an IOSAPIC पूर्णांकerrupt! */

	low32 = iosapic_पूर्णांकr_info[irq].low32 &= ~IOSAPIC_MASK;
	list_क्रम_each_entry(rte, &iosapic_पूर्णांकr_info[irq].rtes, rte_list) अणु
		rte_index = rte->rte_index;
		iosapic_ग_लिखो(rte->iosapic, IOSAPIC_RTE_LOW(rte_index), low32);
	पूर्ण
पूर्ण


अटल पूर्णांक
iosapic_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *mask,
		     bool क्रमce)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक irq = data->irq;
	u32 high32, low32;
	पूर्णांक cpu, dest, rte_index;
	पूर्णांक redir = (irq & IA64_IRQ_REसूचीECTED) ? 1 : 0;
	काष्ठा iosapic_rte_info *rte;
	काष्ठा iosapic *iosapic;

	irq &= (~IA64_IRQ_REसूचीECTED);

	cpu = cpumask_first_and(cpu_online_mask, mask);
	अगर (cpu >= nr_cpu_ids)
		वापस -1;

	अगर (irq_prepare_move(irq, cpu))
		वापस -1;

	dest = cpu_physical_id(cpu);

	अगर (!iosapic_पूर्णांकr_info[irq].count)
		वापस -1;			/* not an IOSAPIC पूर्णांकerrupt */

	set_irq_affinity_info(irq, dest, redir);

	/* dest contains both id and eid */
	high32 = dest << IOSAPIC_DEST_SHIFT;

	low32 = iosapic_पूर्णांकr_info[irq].low32 & ~(7 << IOSAPIC_DELIVERY_SHIFT);
	अगर (redir)
		/* change delivery mode to lowest priority */
		low32 |= (IOSAPIC_LOWEST_PRIORITY << IOSAPIC_DELIVERY_SHIFT);
	अन्यथा
		/* change delivery mode to fixed */
		low32 |= (IOSAPIC_FIXED << IOSAPIC_DELIVERY_SHIFT);
	low32 &= IOSAPIC_VECTOR_MASK;
	low32 |= irq_to_vector(irq);

	iosapic_पूर्णांकr_info[irq].low32 = low32;
	iosapic_पूर्णांकr_info[irq].dest = dest;
	list_क्रम_each_entry(rte, &iosapic_पूर्णांकr_info[irq].rtes, rte_list) अणु
		iosapic = rte->iosapic;
		rte_index = rte->rte_index;
		iosapic_ग_लिखो(iosapic, IOSAPIC_RTE_HIGH(rte_index), high32);
		iosapic_ग_लिखो(iosapic, IOSAPIC_RTE_LOW(rte_index), low32);
	पूर्ण

#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Handlers क्रम level-triggered पूर्णांकerrupts.
 */

अटल अचिन्हित पूर्णांक
iosapic_startup_level_irq (काष्ठा irq_data *data)
अणु
	unmask_irq(data);
	वापस 0;
पूर्ण

अटल व्योम
iosapic_unmask_level_irq (काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	ia64_vector vec = irq_to_vector(irq);
	काष्ठा iosapic_rte_info *rte;
	पूर्णांक करो_unmask_irq = 0;

	irq_complete_move(irq);
	अगर (unlikely(irqd_is_setaffinity_pending(data))) अणु
		करो_unmask_irq = 1;
		mask_irq(data);
	पूर्ण अन्यथा
		unmask_irq(data);

	list_क्रम_each_entry(rte, &iosapic_पूर्णांकr_info[irq].rtes, rte_list)
		iosapic_eoi(rte->iosapic->addr, vec);

	अगर (unlikely(करो_unmask_irq)) अणु
		irq_move_masked_irq(data);
		unmask_irq(data);
	पूर्ण
पूर्ण

#घोषणा iosapic_shutकरोwn_level_irq	mask_irq
#घोषणा iosapic_enable_level_irq	unmask_irq
#घोषणा iosapic_disable_level_irq	mask_irq
#घोषणा iosapic_ack_level_irq		iosapic_nop

अटल काष्ठा irq_chip irq_type_iosapic_level = अणु
	.name =			"IO-SAPIC-level",
	.irq_startup =		iosapic_startup_level_irq,
	.irq_shutकरोwn =		iosapic_shutकरोwn_level_irq,
	.irq_enable =		iosapic_enable_level_irq,
	.irq_disable =		iosapic_disable_level_irq,
	.irq_ack =		iosapic_ack_level_irq,
	.irq_mask =		mask_irq,
	.irq_unmask =		iosapic_unmask_level_irq,
	.irq_set_affinity =	iosapic_set_affinity
पूर्ण;

/*
 * Handlers क्रम edge-triggered पूर्णांकerrupts.
 */

अटल अचिन्हित पूर्णांक
iosapic_startup_edge_irq (काष्ठा irq_data *data)
अणु
	unmask_irq(data);
	/*
	 * IOSAPIC simply drops पूर्णांकerrupts pended जबतक the
	 * corresponding pin was masked, so we can't know अगर an
	 * पूर्णांकerrupt is pending alपढ़ोy.  Let's hope not...
	 */
	वापस 0;
पूर्ण

अटल व्योम
iosapic_ack_edge_irq (काष्ठा irq_data *data)
अणु
	irq_complete_move(data->irq);
	irq_move_irq(data);
पूर्ण

#घोषणा iosapic_enable_edge_irq		unmask_irq
#घोषणा iosapic_disable_edge_irq	iosapic_nop

अटल काष्ठा irq_chip irq_type_iosapic_edge = अणु
	.name =			"IO-SAPIC-edge",
	.irq_startup =		iosapic_startup_edge_irq,
	.irq_shutकरोwn =		iosapic_disable_edge_irq,
	.irq_enable =		iosapic_enable_edge_irq,
	.irq_disable =		iosapic_disable_edge_irq,
	.irq_ack =		iosapic_ack_edge_irq,
	.irq_mask =		mask_irq,
	.irq_unmask =		unmask_irq,
	.irq_set_affinity =	iosapic_set_affinity
पूर्ण;

अटल अचिन्हित पूर्णांक
iosapic_version (अक्षर __iomem *addr)
अणु
	/*
	 * IOSAPIC Version Register वापस 32 bit काष्ठाure like:
	 * अणु
	 *	अचिन्हित पूर्णांक version   : 8;
	 *	अचिन्हित पूर्णांक reserved1 : 8;
	 *	अचिन्हित पूर्णांक max_redir : 8;
	 *	अचिन्हित पूर्णांक reserved2 : 8;
	 * पूर्ण
	 */
	वापस __iosapic_पढ़ो(addr, IOSAPIC_VERSION);
पूर्ण

अटल पूर्णांक iosapic_find_sharable_irq(अचिन्हित दीर्घ trigger, अचिन्हित दीर्घ pol)
अणु
	पूर्णांक i, irq = -ENOSPC, min_count = -1;
	काष्ठा iosapic_पूर्णांकr_info *info;

	/*
	 * shared vectors क्रम edge-triggered पूर्णांकerrupts are not
	 * supported yet
	 */
	अगर (trigger == IOSAPIC_EDGE)
		वापस -EINVAL;

	क्रम (i = 0; i < NR_IRQS; i++) अणु
		info = &iosapic_पूर्णांकr_info[i];
		अगर (info->trigger == trigger && info->polarity == pol &&
		    (info->dmode == IOSAPIC_FIXED ||
		     info->dmode == IOSAPIC_LOWEST_PRIORITY) &&
		    can_request_irq(i, IRQF_SHARED)) अणु
			अगर (min_count == -1 || info->count < min_count) अणु
				irq = i;
				min_count = info->count;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस irq;
पूर्ण

/*
 * अगर the given vector is alपढ़ोy owned by other,
 *  assign a new vector क्रम the other and make the vector available
 */
अटल व्योम __init
iosapic_reassign_vector (पूर्णांक irq)
अणु
	पूर्णांक new_irq;

	अगर (iosapic_पूर्णांकr_info[irq].count) अणु
		new_irq = create_irq();
		अगर (new_irq < 0)
			panic("%s: out of interrupt vectors!\n", __func__);
		prपूर्णांकk(KERN_INFO "Reassigning vector %d to %d\n",
		       irq_to_vector(irq), irq_to_vector(new_irq));
		स_नकल(&iosapic_पूर्णांकr_info[new_irq], &iosapic_पूर्णांकr_info[irq],
		       माप(काष्ठा iosapic_पूर्णांकr_info));
		INIT_LIST_HEAD(&iosapic_पूर्णांकr_info[new_irq].rtes);
		list_move(iosapic_पूर्णांकr_info[irq].rtes.next,
			  &iosapic_पूर्णांकr_info[new_irq].rtes);
		स_रखो(&iosapic_पूर्णांकr_info[irq], 0,
		       माप(काष्ठा iosapic_पूर्णांकr_info));
		iosapic_पूर्णांकr_info[irq].low32 = IOSAPIC_MASK;
		INIT_LIST_HEAD(&iosapic_पूर्णांकr_info[irq].rtes);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक irq_is_shared (पूर्णांक irq)
अणु
	वापस (iosapic_पूर्णांकr_info[irq].count > 1);
पूर्ण

काष्ठा irq_chip*
ia64_native_iosapic_get_irq_chip(अचिन्हित दीर्घ trigger)
अणु
	अगर (trigger == IOSAPIC_EDGE)
		वापस &irq_type_iosapic_edge;
	अन्यथा
		वापस &irq_type_iosapic_level;
पूर्ण

अटल पूर्णांक
रेजिस्टर_पूर्णांकr (अचिन्हित पूर्णांक gsi, पूर्णांक irq, अचिन्हित अक्षर delivery,
	       अचिन्हित दीर्घ polarity, अचिन्हित दीर्घ trigger)
अणु
	काष्ठा irq_chip *chip, *irq_type;
	पूर्णांक index;
	काष्ठा iosapic_rte_info *rte;

	index = find_iosapic(gsi);
	अगर (index < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: No IOSAPIC for GSI %u\n",
		       __func__, gsi);
		वापस -ENODEV;
	पूर्ण

	rte = find_rte(irq, gsi);
	अगर (!rte) अणु
		rte = kzalloc(माप (*rte), GFP_ATOMIC);
		अगर (!rte) अणु
			prपूर्णांकk(KERN_WARNING "%s: cannot allocate memory\n",
			       __func__);
			वापस -ENOMEM;
		पूर्ण

		rte->iosapic	= &iosapic_lists[index];
		rte->rte_index	= gsi - rte->iosapic->gsi_base;
		rte->refcnt++;
		list_add_tail(&rte->rte_list, &iosapic_पूर्णांकr_info[irq].rtes);
		iosapic_पूर्णांकr_info[irq].count++;
		iosapic_lists[index].rtes_inuse++;
	पूर्ण
	अन्यथा अगर (rte->refcnt == NO_REF_RTE) अणु
		काष्ठा iosapic_पूर्णांकr_info *info = &iosapic_पूर्णांकr_info[irq];
		अगर (info->count > 0 &&
		    (info->trigger != trigger || info->polarity != polarity))अणु
			prपूर्णांकk (KERN_WARNING
				"%s: cannot override the interrupt\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
		rte->refcnt++;
		iosapic_पूर्णांकr_info[irq].count++;
		iosapic_lists[index].rtes_inuse++;
	पूर्ण

	iosapic_पूर्णांकr_info[irq].polarity = polarity;
	iosapic_पूर्णांकr_info[irq].dmode    = delivery;
	iosapic_पूर्णांकr_info[irq].trigger  = trigger;

	irq_type = iosapic_get_irq_chip(trigger);

	chip = irq_get_chip(irq);
	अगर (irq_type != शून्य && chip != irq_type) अणु
		अगर (chip != &no_irq_chip)
			prपूर्णांकk(KERN_WARNING
			       "%s: changing vector %d from %s to %s\n",
			       __func__, irq_to_vector(irq),
			       chip->name, irq_type->name);
		chip = irq_type;
	पूर्ण
	irq_set_chip_handler_name_locked(irq_get_irq_data(irq), chip,
		trigger == IOSAPIC_EDGE ? handle_edge_irq : handle_level_irq,
		शून्य);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
get_target_cpu (अचिन्हित पूर्णांक gsi, पूर्णांक irq)
अणु
#अगर_घोषित CONFIG_SMP
	अटल पूर्णांक cpu = -1;
	बाह्य पूर्णांक cpe_vector;
	cpumask_t करोमुख्य = irq_to_करोमुख्य(irq);

	/*
	 * In हाल of vector shared by multiple RTEs, all RTEs that
	 * share the vector need to use the same destination CPU.
	 */
	अगर (iosapic_पूर्णांकr_info[irq].count)
		वापस iosapic_पूर्णांकr_info[irq].dest;

	/*
	 * If the platक्रमm supports redirection via XTP, let it
	 * distribute पूर्णांकerrupts.
	 */
	अगर (smp_पूर्णांक_redirect & SMP_IRQ_REसूचीECTION)
		वापस cpu_physical_id(smp_processor_id());

	/*
	 * Some पूर्णांकerrupts (ACPI SCI, क्रम instance) are रेजिस्टरed
	 * beक्रमe the BSP is marked as online.
	 */
	अगर (!cpu_online(smp_processor_id()))
		वापस cpu_physical_id(smp_processor_id());

	अगर (cpe_vector > 0 && irq_to_vector(irq) == IA64_CPEP_VECTOR)
		वापस get_cpei_target_cpu();

#अगर_घोषित CONFIG_NUMA
	अणु
		पूर्णांक num_cpus, cpu_index, iosapic_index, numa_cpu, i = 0;
		स्थिर काष्ठा cpumask *cpu_mask;

		iosapic_index = find_iosapic(gsi);
		अगर (iosapic_index < 0 ||
		    iosapic_lists[iosapic_index].node == MAX_NUMNODES)
			जाओ skip_numa_setup;

		cpu_mask = cpumask_of_node(iosapic_lists[iosapic_index].node);
		num_cpus = 0;
		क्रम_each_cpu_and(numa_cpu, cpu_mask, &करोमुख्य) अणु
			अगर (cpu_online(numa_cpu))
				num_cpus++;
		पूर्ण

		अगर (!num_cpus)
			जाओ skip_numa_setup;

		/* Use irq assignment to distribute across cpus in node */
		cpu_index = irq % num_cpus;

		क्रम_each_cpu_and(numa_cpu, cpu_mask, &करोमुख्य)
			अगर (cpu_online(numa_cpu) && i++ >= cpu_index)
				अवरोध;

		अगर (numa_cpu < nr_cpu_ids)
			वापस cpu_physical_id(numa_cpu);
	पूर्ण
skip_numa_setup:
#पूर्ण_अगर
	/*
	 * Otherwise, round-robin पूर्णांकerrupt vectors across all the
	 * processors.  (It'd be nice अगर we could be smarter in the
	 * हाल of NUMA.)
	 */
	करो अणु
		अगर (++cpu >= nr_cpu_ids)
			cpu = 0;
	पूर्ण जबतक (!cpu_online(cpu) || !cpumask_test_cpu(cpu, &करोमुख्य));

	वापस cpu_physical_id(cpu);
#अन्यथा  /* CONFIG_SMP */
	वापस cpu_physical_id(smp_processor_id());
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर choose_dmode(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (smp_पूर्णांक_redirect & SMP_IRQ_REसूचीECTION)
		वापस IOSAPIC_LOWEST_PRIORITY;
#पूर्ण_अगर
	वापस IOSAPIC_FIXED;
पूर्ण

/*
 * ACPI can describe IOSAPIC पूर्णांकerrupts via अटल tables and namespace
 * methods.  This provides an पूर्णांकerface to रेजिस्टर those पूर्णांकerrupts and
 * program the IOSAPIC RTE.
 */
पूर्णांक
iosapic_रेजिस्टर_पूर्णांकr (अचिन्हित पूर्णांक gsi,
		       अचिन्हित दीर्घ polarity, अचिन्हित दीर्घ trigger)
अणु
	पूर्णांक irq, mask = 1, err;
	अचिन्हित पूर्णांक dest;
	अचिन्हित दीर्घ flags;
	काष्ठा iosapic_rte_info *rte;
	u32 low32;
	अचिन्हित अक्षर dmode;
	काष्ठा irq_desc *desc;

	/*
	 * If this GSI has alपढ़ोy been रेजिस्टरed (i.e., it's a
	 * shared पूर्णांकerrupt, or we lost a race to रेजिस्टर it),
	 * करोn't touch the RTE.
	 */
	spin_lock_irqsave(&iosapic_lock, flags);
	irq = __gsi_to_irq(gsi);
	अगर (irq > 0) अणु
		rte = find_rte(irq, gsi);
		अगर(iosapic_पूर्णांकr_info[irq].count == 0) अणु
			assign_irq_vector(irq);
			irq_init_desc(irq);
		पूर्ण अन्यथा अगर (rte->refcnt != NO_REF_RTE) अणु
			rte->refcnt++;
			जाओ unlock_iosapic_lock;
		पूर्ण
	पूर्ण अन्यथा
		irq = create_irq();

	/* If vector is running out, we try to find a sharable vector */
	अगर (irq < 0) अणु
		irq = iosapic_find_sharable_irq(trigger, polarity);
		अगर (irq < 0)
			जाओ unlock_iosapic_lock;
	पूर्ण

	desc = irq_to_desc(irq);
	raw_spin_lock(&desc->lock);
	dest = get_target_cpu(gsi, irq);
	dmode = choose_dmode();
	err = रेजिस्टर_पूर्णांकr(gsi, irq, dmode, polarity, trigger);
	अगर (err < 0) अणु
		raw_spin_unlock(&desc->lock);
		irq = err;
		जाओ unlock_iosapic_lock;
	पूर्ण

	/*
	 * If the vector is shared and alपढ़ोy unmasked क्रम other
	 * पूर्णांकerrupt sources, करोn't mask it.
	 */
	low32 = iosapic_पूर्णांकr_info[irq].low32;
	अगर (irq_is_shared(irq) && !(low32 & IOSAPIC_MASK))
		mask = 0;
	set_rte(gsi, irq, dest, mask);

	prपूर्णांकk(KERN_INFO "GSI %u (%s, %s) -> CPU %d (0x%04x) vector %d\n",
	       gsi, (trigger == IOSAPIC_EDGE ? "edge" : "level"),
	       (polarity == IOSAPIC_POL_HIGH ? "high" : "low"),
	       cpu_logical_id(dest), dest, irq_to_vector(irq));

	raw_spin_unlock(&desc->lock);
 unlock_iosapic_lock:
	spin_unlock_irqrestore(&iosapic_lock, flags);
	वापस irq;
पूर्ण

व्योम
iosapic_unरेजिस्टर_पूर्णांकr (अचिन्हित पूर्णांक gsi)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक irq, index;
	u32 low32;
	अचिन्हित दीर्घ trigger, polarity;
	अचिन्हित पूर्णांक dest;
	काष्ठा iosapic_rte_info *rte;

	/*
	 * If the irq associated with the gsi is not found,
	 * iosapic_unरेजिस्टर_पूर्णांकr() is unbalanced. We need to check
	 * this again after getting locks.
	 */
	irq = gsi_to_irq(gsi);
	अगर (irq < 0) अणु
		prपूर्णांकk(KERN_ERR "iosapic_unregister_intr(%u) unbalanced\n",
		       gsi);
		WARN_ON(1);
		वापस;
	पूर्ण

	spin_lock_irqsave(&iosapic_lock, flags);
	अगर ((rte = find_rte(irq, gsi)) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "iosapic_unregister_intr(%u) unbalanced\n",
		       gsi);
		WARN_ON(1);
		जाओ out;
	पूर्ण

	अगर (--rte->refcnt > 0)
		जाओ out;

	rte->refcnt = NO_REF_RTE;

	/* Mask the पूर्णांकerrupt */
	low32 = iosapic_पूर्णांकr_info[irq].low32 | IOSAPIC_MASK;
	iosapic_ग_लिखो(rte->iosapic, IOSAPIC_RTE_LOW(rte->rte_index), low32);

	iosapic_पूर्णांकr_info[irq].count--;
	index = find_iosapic(gsi);
	iosapic_lists[index].rtes_inuse--;
	WARN_ON(iosapic_lists[index].rtes_inuse < 0);

	trigger  = iosapic_पूर्णांकr_info[irq].trigger;
	polarity = iosapic_पूर्णांकr_info[irq].polarity;
	dest     = iosapic_पूर्णांकr_info[irq].dest;
	prपूर्णांकk(KERN_INFO
	       "GSI %u (%s, %s) -> CPU %d (0x%04x) vector %d unregistered\n",
	       gsi, (trigger == IOSAPIC_EDGE ? "edge" : "level"),
	       (polarity == IOSAPIC_POL_HIGH ? "high" : "low"),
	       cpu_logical_id(dest), dest, irq_to_vector(irq));

	अगर (iosapic_पूर्णांकr_info[irq].count == 0) अणु
#अगर_घोषित CONFIG_SMP
		/* Clear affinity */
		cpumask_setall(irq_get_affinity_mask(irq));
#पूर्ण_अगर
		/* Clear the पूर्णांकerrupt inक्रमmation */
		iosapic_पूर्णांकr_info[irq].dest = 0;
		iosapic_पूर्णांकr_info[irq].dmode = 0;
		iosapic_पूर्णांकr_info[irq].polarity = 0;
		iosapic_पूर्णांकr_info[irq].trigger = 0;
		iosapic_पूर्णांकr_info[irq].low32 |= IOSAPIC_MASK;

		/* Destroy and reserve IRQ */
		destroy_and_reserve_irq(irq);
	पूर्ण
 out:
	spin_unlock_irqrestore(&iosapic_lock, flags);
पूर्ण

/*
 * ACPI calls this when it finds an entry क्रम a platक्रमm पूर्णांकerrupt.
 */
पूर्णांक __init
iosapic_रेजिस्टर_platक्रमm_पूर्णांकr (u32 पूर्णांक_type, अचिन्हित पूर्णांक gsi,
				पूर्णांक iosapic_vector, u16 eid, u16 id,
				अचिन्हित दीर्घ polarity, अचिन्हित दीर्घ trigger)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु"unknown", "PMI", "INIT", "CPEI"पूर्ण;
	अचिन्हित अक्षर delivery;
	पूर्णांक irq, vector, mask = 0;
	अचिन्हित पूर्णांक dest = ((id << 8) | eid) & 0xffff;

	चयन (पूर्णांक_type) अणु
	      हाल ACPI_INTERRUPT_PMI:
		irq = vector = iosapic_vector;
		bind_irq_vector(irq, vector, CPU_MASK_ALL);
		/*
		 * since PMI vector is alloc'd by FW(ACPI) not by kernel,
		 * we need to make sure the vector is available
		 */
		iosapic_reassign_vector(irq);
		delivery = IOSAPIC_PMI;
		अवरोध;
	      हाल ACPI_INTERRUPT_INIT:
		irq = create_irq();
		अगर (irq < 0)
			panic("%s: out of interrupt vectors!\n", __func__);
		vector = irq_to_vector(irq);
		delivery = IOSAPIC_INIT;
		अवरोध;
	      हाल ACPI_INTERRUPT_CPEI:
		irq = vector = IA64_CPE_VECTOR;
		BUG_ON(bind_irq_vector(irq, vector, CPU_MASK_ALL));
		delivery = IOSAPIC_FIXED;
		mask = 1;
		अवरोध;
	      शेष:
		prपूर्णांकk(KERN_ERR "%s: invalid int type 0x%x\n", __func__,
		       पूर्णांक_type);
		वापस -1;
	पूर्ण

	रेजिस्टर_पूर्णांकr(gsi, irq, delivery, polarity, trigger);

	prपूर्णांकk(KERN_INFO
	       "PLATFORM int %s (0x%x): GSI %u (%s, %s) -> CPU %d (0x%04x)"
	       " vector %d\n",
	       पूर्णांक_type < ARRAY_SIZE(name) ? name[पूर्णांक_type] : "unknown",
	       पूर्णांक_type, gsi, (trigger == IOSAPIC_EDGE ? "edge" : "level"),
	       (polarity == IOSAPIC_POL_HIGH ? "high" : "low"),
	       cpu_logical_id(dest), dest, vector);

	set_rte(gsi, irq, dest, mask);
	वापस vector;
पूर्ण

/*
 * ACPI calls this when it finds an entry क्रम a legacy ISA IRQ override.
 */
व्योम iosapic_override_isa_irq(अचिन्हित पूर्णांक isa_irq, अचिन्हित पूर्णांक gsi,
			      अचिन्हित दीर्घ polarity, अचिन्हित दीर्घ trigger)
अणु
	पूर्णांक vector, irq;
	अचिन्हित पूर्णांक dest = cpu_physical_id(smp_processor_id());
	अचिन्हित अक्षर dmode;

	irq = vector = isa_irq_to_vector(isa_irq);
	BUG_ON(bind_irq_vector(irq, vector, CPU_MASK_ALL));
	dmode = choose_dmode();
	रेजिस्टर_पूर्णांकr(gsi, irq, dmode, polarity, trigger);

	DBG("ISA: IRQ %u -> GSI %u (%s,%s) -> CPU %d (0x%04x) vector %d\n",
	    isa_irq, gsi, trigger == IOSAPIC_EDGE ? "edge" : "level",
	    polarity == IOSAPIC_POL_HIGH ? "high" : "low",
	    cpu_logical_id(dest), dest, vector);

	set_rte(gsi, irq, dest, 1);
पूर्ण

व्योम __init
ia64_native_iosapic_pcat_compat_init(व्योम)
अणु
	अगर (pcat_compat) अणु
		/*
		 * Disable the compatibility mode पूर्णांकerrupts (8259 style),
		 * needs IN/OUT support enabled.
		 */
		prपूर्णांकk(KERN_INFO
		       "%s: Disabling PC-AT compatible 8259 interrupts\n",
		       __func__);
		outb(0xff, 0xA1);
		outb(0xff, 0x21);
	पूर्ण
पूर्ण

व्योम __init
iosapic_प्रणाली_init (पूर्णांक प्रणाली_pcat_compat)
अणु
	पूर्णांक irq;

	क्रम (irq = 0; irq < NR_IRQS; ++irq) अणु
		iosapic_पूर्णांकr_info[irq].low32 = IOSAPIC_MASK;
		/* mark as unused */
		INIT_LIST_HEAD(&iosapic_पूर्णांकr_info[irq].rtes);

		iosapic_पूर्णांकr_info[irq].count = 0;
	पूर्ण

	pcat_compat = प्रणाली_pcat_compat;
	अगर (pcat_compat)
		iosapic_pcat_compat_init();
पूर्ण

अटल अंतरभूत पूर्णांक
iosapic_alloc (व्योम)
अणु
	पूर्णांक index;

	क्रम (index = 0; index < NR_IOSAPICS; index++)
		अगर (!iosapic_lists[index].addr)
			वापस index;

	prपूर्णांकk(KERN_WARNING "%s: failed to allocate iosapic\n", __func__);
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम
iosapic_मुक्त (पूर्णांक index)
अणु
	स_रखो(&iosapic_lists[index], 0, माप(iosapic_lists[0]));
पूर्ण

अटल अंतरभूत पूर्णांक
iosapic_check_gsi_range (अचिन्हित पूर्णांक gsi_base, अचिन्हित पूर्णांक ver)
अणु
	पूर्णांक index;
	अचिन्हित पूर्णांक gsi_end, base, end;

	/* check gsi range */
	gsi_end = gsi_base + ((ver >> 16) & 0xff);
	क्रम (index = 0; index < NR_IOSAPICS; index++) अणु
		अगर (!iosapic_lists[index].addr)
			जारी;

		base = iosapic_lists[index].gsi_base;
		end  = base + iosapic_lists[index].num_rte - 1;

		अगर (gsi_end < base || end < gsi_base)
			जारी; /* OK */

		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
iosapic_delete_rte(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक gsi)
अणु
	काष्ठा iosapic_rte_info *rte, *temp;

	list_क्रम_each_entry_safe(rte, temp, &iosapic_पूर्णांकr_info[irq].rtes,
								rte_list) अणु
		अगर (rte->iosapic->gsi_base + rte->rte_index == gsi) अणु
			अगर (rte->refcnt)
				वापस -EBUSY;

			list_del(&rte->rte_list);
			kमुक्त(rte);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक iosapic_init(अचिन्हित दीर्घ phys_addr, अचिन्हित पूर्णांक gsi_base)
अणु
	पूर्णांक num_rte, err, index;
	अचिन्हित पूर्णांक isa_irq, ver;
	अक्षर __iomem *addr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iosapic_lock, flags);
	index = find_iosapic(gsi_base);
	अगर (index >= 0) अणु
		spin_unlock_irqrestore(&iosapic_lock, flags);
		वापस -EBUSY;
	पूर्ण

	addr = ioremap(phys_addr, 0);
	अगर (addr == शून्य) अणु
		spin_unlock_irqrestore(&iosapic_lock, flags);
		वापस -ENOMEM;
	पूर्ण
	ver = iosapic_version(addr);
	अगर ((err = iosapic_check_gsi_range(gsi_base, ver))) अणु
		iounmap(addr);
		spin_unlock_irqrestore(&iosapic_lock, flags);
		वापस err;
	पूर्ण

	/*
	 * The MAX_REसूची रेजिस्टर holds the highest input pin number
	 * (starting from 0).  We add 1 so that we can use it क्रम
	 * number of pins (= RTEs)
	 */
	num_rte = ((ver >> 16) & 0xff) + 1;

	index = iosapic_alloc();
	iosapic_lists[index].addr = addr;
	iosapic_lists[index].gsi_base = gsi_base;
	iosapic_lists[index].num_rte = num_rte;
#अगर_घोषित CONFIG_NUMA
	iosapic_lists[index].node = MAX_NUMNODES;
#पूर्ण_अगर
	spin_lock_init(&iosapic_lists[index].lock);
	spin_unlock_irqrestore(&iosapic_lock, flags);

	अगर ((gsi_base == 0) && pcat_compat) अणु
		/*
		 * Map the legacy ISA devices पूर्णांकo the IOSAPIC data.  Some of
		 * these may get reprogrammed later on with data from the ACPI
		 * Interrupt Source Override table.
		 */
		क्रम (isa_irq = 0; isa_irq < 16; ++isa_irq)
			iosapic_override_isa_irq(isa_irq, isa_irq,
						 IOSAPIC_POL_HIGH,
						 IOSAPIC_EDGE);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक iosapic_हटाओ(अचिन्हित पूर्णांक gsi_base)
अणु
	पूर्णांक i, irq, index, err = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iosapic_lock, flags);
	index = find_iosapic(gsi_base);
	अगर (index < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: No IOSAPIC for GSI base %u\n",
		       __func__, gsi_base);
		जाओ out;
	पूर्ण

	अगर (iosapic_lists[index].rtes_inuse) अणु
		err = -EBUSY;
		prपूर्णांकk(KERN_WARNING "%s: IOSAPIC for GSI base %u is busy\n",
		       __func__, gsi_base);
		जाओ out;
	पूर्ण

	क्रम (i = gsi_base; i < gsi_base + iosapic_lists[index].num_rte; i++) अणु
		irq = __gsi_to_irq(i);
		अगर (irq < 0)
			जारी;

		err = iosapic_delete_rte(irq, i);
		अगर (err)
			जाओ out;
	पूर्ण

	iounmap(iosapic_lists[index].addr);
	iosapic_मुक्त(index);
 out:
	spin_unlock_irqrestore(&iosapic_lock, flags);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NUMA
व्योम map_iosapic_to_node(अचिन्हित पूर्णांक gsi_base, पूर्णांक node)
अणु
	पूर्णांक index;

	index = find_iosapic(gsi_base);
	अगर (index < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: No IOSAPIC for GSI %u\n",
		       __func__, gsi_base);
		वापस;
	पूर्ण
	iosapic_lists[index].node = node;
	वापस;
पूर्ण
#पूर्ण_अगर
