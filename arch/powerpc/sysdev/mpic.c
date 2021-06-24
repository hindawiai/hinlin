<शैली गुरु>
/*
 *  arch/घातerpc/kernel/mpic.c
 *
 *  Driver क्रम पूर्णांकerrupt controllers following the OpenPIC standard, the
 *  common implementation being IBM's MPIC. This driver also can deal
 *  with various broken implementations of this HW.
 *
 *  Copyright (C) 2004 Benjamin Herrenschmidt, IBM Corp.
 *  Copyright 2010-2012 Freescale Semiconductor, Inc.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अघोषित DEBUG
#अघोषित DEBUG_IPI
#अघोषित DEBUG_IRQ
#अघोषित DEBUG_LOW

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/smp.h>

#समावेश "mpic.h"

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) prपूर्णांकk(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

काष्ठा bus_type mpic_subsys = अणु
	.name = "mpic",
	.dev_name = "mpic",
पूर्ण;
EXPORT_SYMBOL_GPL(mpic_subsys);

अटल काष्ठा mpic *mpics;
अटल काष्ठा mpic *mpic_primary;
अटल DEFINE_RAW_SPINLOCK(mpic_lock);

#अगर_घोषित CONFIG_PPC32	/* XXX क्रम now */
#अगर_घोषित CONFIG_IRQ_ALL_CPUS
#घोषणा distribute_irqs	(1)
#अन्यथा
#घोषणा distribute_irqs	(0)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_MPIC_WEIRD
अटल u32 mpic_infos[][MPIC_IDX_END] = अणु
	[0] = अणु	/* Original OpenPIC compatible MPIC */
		MPIC_GREG_BASE,
		MPIC_GREG_FEATURE_0,
		MPIC_GREG_GLOBAL_CONF_0,
		MPIC_GREG_VENDOR_ID,
		MPIC_GREG_IPI_VECTOR_PRI_0,
		MPIC_GREG_IPI_STRIDE,
		MPIC_GREG_SPURIOUS,
		MPIC_GREG_TIMER_FREQ,

		MPIC_TIMER_BASE,
		MPIC_TIMER_STRIDE,
		MPIC_TIMER_CURRENT_CNT,
		MPIC_TIMER_BASE_CNT,
		MPIC_TIMER_VECTOR_PRI,
		MPIC_TIMER_DESTINATION,

		MPIC_CPU_BASE,
		MPIC_CPU_STRIDE,
		MPIC_CPU_IPI_DISPATCH_0,
		MPIC_CPU_IPI_DISPATCH_STRIDE,
		MPIC_CPU_CURRENT_TASK_PRI,
		MPIC_CPU_WHOAMI,
		MPIC_CPU_INTACK,
		MPIC_CPU_EOI,
		MPIC_CPU_MCACK,

		MPIC_IRQ_BASE,
		MPIC_IRQ_STRIDE,
		MPIC_IRQ_VECTOR_PRI,
		MPIC_VECPRI_VECTOR_MASK,
		MPIC_VECPRI_POLARITY_POSITIVE,
		MPIC_VECPRI_POLARITY_NEGATIVE,
		MPIC_VECPRI_SENSE_LEVEL,
		MPIC_VECPRI_SENSE_EDGE,
		MPIC_VECPRI_POLARITY_MASK,
		MPIC_VECPRI_SENSE_MASK,
		MPIC_IRQ_DESTINATION
	पूर्ण,
	[1] = अणु	/* Tsi108/109 PIC */
		TSI108_GREG_BASE,
		TSI108_GREG_FEATURE_0,
		TSI108_GREG_GLOBAL_CONF_0,
		TSI108_GREG_VENDOR_ID,
		TSI108_GREG_IPI_VECTOR_PRI_0,
		TSI108_GREG_IPI_STRIDE,
		TSI108_GREG_SPURIOUS,
		TSI108_GREG_TIMER_FREQ,

		TSI108_TIMER_BASE,
		TSI108_TIMER_STRIDE,
		TSI108_TIMER_CURRENT_CNT,
		TSI108_TIMER_BASE_CNT,
		TSI108_TIMER_VECTOR_PRI,
		TSI108_TIMER_DESTINATION,

		TSI108_CPU_BASE,
		TSI108_CPU_STRIDE,
		TSI108_CPU_IPI_DISPATCH_0,
		TSI108_CPU_IPI_DISPATCH_STRIDE,
		TSI108_CPU_CURRENT_TASK_PRI,
		TSI108_CPU_WHOAMI,
		TSI108_CPU_INTACK,
		TSI108_CPU_EOI,
		TSI108_CPU_MCACK,

		TSI108_IRQ_BASE,
		TSI108_IRQ_STRIDE,
		TSI108_IRQ_VECTOR_PRI,
		TSI108_VECPRI_VECTOR_MASK,
		TSI108_VECPRI_POLARITY_POSITIVE,
		TSI108_VECPRI_POLARITY_NEGATIVE,
		TSI108_VECPRI_SENSE_LEVEL,
		TSI108_VECPRI_SENSE_EDGE,
		TSI108_VECPRI_POLARITY_MASK,
		TSI108_VECPRI_SENSE_MASK,
		TSI108_IRQ_DESTINATION
	पूर्ण,
पूर्ण;

#घोषणा MPIC_INFO(name) mpic->hw_set[MPIC_IDX_##name]

#अन्यथा /* CONFIG_MPIC_WEIRD */

#घोषणा MPIC_INFO(name) MPIC_##name

#पूर्ण_अगर /* CONFIG_MPIC_WEIRD */

अटल अंतरभूत अचिन्हित पूर्णांक mpic_processor_id(काष्ठा mpic *mpic)
अणु
	अचिन्हित पूर्णांक cpu = 0;

	अगर (!(mpic->flags & MPIC_SECONDARY))
		cpu = hard_smp_processor_id();

	वापस cpu;
पूर्ण

/*
 * Register accessor functions
 */


अटल अंतरभूत u32 _mpic_पढ़ो(क्रमागत mpic_reg_type type,
			     काष्ठा mpic_reg_bank *rb,
			     अचिन्हित पूर्णांक reg)
अणु
	चयन(type) अणु
#अगर_घोषित CONFIG_PPC_DCR
	हाल mpic_access_dcr:
		वापस dcr_पढ़ो(rb->dhost, reg);
#पूर्ण_अगर
	हाल mpic_access_mmio_be:
		वापस in_be32(rb->base + (reg >> 2));
	हाल mpic_access_mmio_le:
	शेष:
		वापस in_le32(rb->base + (reg >> 2));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम _mpic_ग_लिखो(क्रमागत mpic_reg_type type,
			       काष्ठा mpic_reg_bank *rb,
 			       अचिन्हित पूर्णांक reg, u32 value)
अणु
	चयन(type) अणु
#अगर_घोषित CONFIG_PPC_DCR
	हाल mpic_access_dcr:
		dcr_ग_लिखो(rb->dhost, reg, value);
		अवरोध;
#पूर्ण_अगर
	हाल mpic_access_mmio_be:
		out_be32(rb->base + (reg >> 2), value);
		अवरोध;
	हाल mpic_access_mmio_le:
	शेष:
		out_le32(rb->base + (reg >> 2), value);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 _mpic_ipi_पढ़ो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक ipi)
अणु
	क्रमागत mpic_reg_type type = mpic->reg_type;
	अचिन्हित पूर्णांक offset = MPIC_INFO(GREG_IPI_VECTOR_PRI_0) +
			      (ipi * MPIC_INFO(GREG_IPI_STRIDE));

	अगर ((mpic->flags & MPIC_BROKEN_IPI) && type == mpic_access_mmio_le)
		type = mpic_access_mmio_be;
	वापस _mpic_पढ़ो(type, &mpic->gregs, offset);
पूर्ण

अटल अंतरभूत व्योम _mpic_ipi_ग_लिखो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक ipi, u32 value)
अणु
	अचिन्हित पूर्णांक offset = MPIC_INFO(GREG_IPI_VECTOR_PRI_0) +
			      (ipi * MPIC_INFO(GREG_IPI_STRIDE));

	_mpic_ग_लिखो(mpic->reg_type, &mpic->gregs, offset, value);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mpic_पंचांग_offset(काष्ठा mpic *mpic, अचिन्हित पूर्णांक पंचांग)
अणु
	वापस (पंचांग >> 2) * MPIC_TIMER_GROUP_STRIDE +
	       (पंचांग & 3) * MPIC_INFO(TIMER_STRIDE);
पूर्ण

अटल अंतरभूत u32 _mpic_पंचांग_पढ़ो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक पंचांग)
अणु
	अचिन्हित पूर्णांक offset = mpic_पंचांग_offset(mpic, पंचांग) +
			      MPIC_INFO(TIMER_VECTOR_PRI);

	वापस _mpic_पढ़ो(mpic->reg_type, &mpic->पंचांगregs, offset);
पूर्ण

अटल अंतरभूत व्योम _mpic_पंचांग_ग_लिखो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक पंचांग, u32 value)
अणु
	अचिन्हित पूर्णांक offset = mpic_पंचांग_offset(mpic, पंचांग) +
			      MPIC_INFO(TIMER_VECTOR_PRI);

	_mpic_ग_लिखो(mpic->reg_type, &mpic->पंचांगregs, offset, value);
पूर्ण

अटल अंतरभूत u32 _mpic_cpu_पढ़ो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक cpu = mpic_processor_id(mpic);

	वापस _mpic_पढ़ो(mpic->reg_type, &mpic->cpuregs[cpu], reg);
पूर्ण

अटल अंतरभूत व्योम _mpic_cpu_ग_लिखो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक reg, u32 value)
अणु
	अचिन्हित पूर्णांक cpu = mpic_processor_id(mpic);

	_mpic_ग_लिखो(mpic->reg_type, &mpic->cpuregs[cpu], reg, value);
पूर्ण

अटल अंतरभूत u32 _mpic_irq_पढ़ो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक src_no, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक	isu = src_no >> mpic->isu_shअगरt;
	अचिन्हित पूर्णांक	idx = src_no & mpic->isu_mask;
	अचिन्हित पूर्णांक	val;

	val = _mpic_पढ़ो(mpic->reg_type, &mpic->isus[isu],
			 reg + (idx * MPIC_INFO(IRQ_STRIDE)));
#अगर_घोषित CONFIG_MPIC_BROKEN_REGREAD
	अगर (reg == 0)
		val = (val & (MPIC_VECPRI_MASK | MPIC_VECPRI_ACTIVITY)) |
			mpic->isu_reg0_shaकरोw[src_no];
#पूर्ण_अगर
	वापस val;
पूर्ण

अटल अंतरभूत व्योम _mpic_irq_ग_लिखो(काष्ठा mpic *mpic, अचिन्हित पूर्णांक src_no,
				   अचिन्हित पूर्णांक reg, u32 value)
अणु
	अचिन्हित पूर्णांक	isu = src_no >> mpic->isu_shअगरt;
	अचिन्हित पूर्णांक	idx = src_no & mpic->isu_mask;

	_mpic_ग_लिखो(mpic->reg_type, &mpic->isus[isu],
		    reg + (idx * MPIC_INFO(IRQ_STRIDE)), value);

#अगर_घोषित CONFIG_MPIC_BROKEN_REGREAD
	अगर (reg == 0)
		mpic->isu_reg0_shaकरोw[src_no] =
			value & ~(MPIC_VECPRI_MASK | MPIC_VECPRI_ACTIVITY);
#पूर्ण_अगर
पूर्ण

#घोषणा mpic_पढ़ो(b,r)		_mpic_पढ़ो(mpic->reg_type,&(b),(r))
#घोषणा mpic_ग_लिखो(b,r,v)	_mpic_ग_लिखो(mpic->reg_type,&(b),(r),(v))
#घोषणा mpic_ipi_पढ़ो(i)	_mpic_ipi_पढ़ो(mpic,(i))
#घोषणा mpic_ipi_ग_लिखो(i,v)	_mpic_ipi_ग_लिखो(mpic,(i),(v))
#घोषणा mpic_पंचांग_पढ़ो(i)		_mpic_पंचांग_पढ़ो(mpic,(i))
#घोषणा mpic_पंचांग_ग_लिखो(i,v)	_mpic_पंचांग_ग_लिखो(mpic,(i),(v))
#घोषणा mpic_cpu_पढ़ो(i)	_mpic_cpu_पढ़ो(mpic,(i))
#घोषणा mpic_cpu_ग_लिखो(i,v)	_mpic_cpu_ग_लिखो(mpic,(i),(v))
#घोषणा mpic_irq_पढ़ो(s,r)	_mpic_irq_पढ़ो(mpic,(s),(r))
#घोषणा mpic_irq_ग_लिखो(s,r,v)	_mpic_irq_ग_लिखो(mpic,(s),(r),(v))


/*
 * Low level utility functions
 */


अटल व्योम _mpic_map_mmio(काष्ठा mpic *mpic, phys_addr_t phys_addr,
			   काष्ठा mpic_reg_bank *rb, अचिन्हित पूर्णांक offset,
			   अचिन्हित पूर्णांक size)
अणु
	rb->base = ioremap(phys_addr + offset, size);
	BUG_ON(rb->base == शून्य);
पूर्ण

#अगर_घोषित CONFIG_PPC_DCR
अटल व्योम _mpic_map_dcr(काष्ठा mpic *mpic, काष्ठा mpic_reg_bank *rb,
			  अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size)
अणु
	phys_addr_t phys_addr = dcr_resource_start(mpic->node, 0);
	rb->dhost = dcr_map(mpic->node, phys_addr + offset, size);
	BUG_ON(!DCR_MAP_OK(rb->dhost));
पूर्ण

अटल अंतरभूत व्योम mpic_map(काष्ठा mpic *mpic,
			    phys_addr_t phys_addr, काष्ठा mpic_reg_bank *rb,
			    अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size)
अणु
	अगर (mpic->flags & MPIC_USES_DCR)
		_mpic_map_dcr(mpic, rb, offset, size);
	अन्यथा
		_mpic_map_mmio(mpic, phys_addr, rb, offset, size);
पूर्ण
#अन्यथा /* CONFIG_PPC_DCR */
#घोषणा mpic_map(m,p,b,o,s)	_mpic_map_mmio(m,p,b,o,s)
#पूर्ण_अगर /* !CONFIG_PPC_DCR */



/* Check अगर we have one of those nice broken MPICs with a flipped endian on
 * पढ़ोs from IPI रेजिस्टरs
 */
अटल व्योम __init mpic_test_broken_ipi(काष्ठा mpic *mpic)
अणु
	u32 r;

	mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_IPI_VECTOR_PRI_0), MPIC_VECPRI_MASK);
	r = mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_IPI_VECTOR_PRI_0));

	अगर (r == le32_to_cpu(MPIC_VECPRI_MASK)) अणु
		prपूर्णांकk(KERN_INFO "mpic: Detected reversed IPI registers\n");
		mpic->flags |= MPIC_BROKEN_IPI;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS

/* Test अगर an पूर्णांकerrupt is sourced from HyperTransport (used on broken U3s)
 * to क्रमce the edge setting on the MPIC and करो the ack workaround.
 */
अटल अंतरभूत पूर्णांक mpic_is_ht_पूर्णांकerrupt(काष्ठा mpic *mpic, अचिन्हित पूर्णांक source)
अणु
	अगर (source >= 128 || !mpic->fixups)
		वापस 0;
	वापस mpic->fixups[source].base != शून्य;
पूर्ण


अटल अंतरभूत व्योम mpic_ht_end_irq(काष्ठा mpic *mpic, अचिन्हित पूर्णांक source)
अणु
	काष्ठा mpic_irq_fixup *fixup = &mpic->fixups[source];

	अगर (fixup->applebase) अणु
		अचिन्हित पूर्णांक soff = (fixup->index >> 3) & ~3;
		अचिन्हित पूर्णांक mask = 1U << (fixup->index & 0x1f);
		ग_लिखोl(mask, fixup->applebase + soff);
	पूर्ण अन्यथा अणु
		raw_spin_lock(&mpic->fixup_lock);
		ग_लिखोb(0x11 + 2 * fixup->index, fixup->base + 2);
		ग_लिखोl(fixup->data, fixup->base + 4);
		raw_spin_unlock(&mpic->fixup_lock);
	पूर्ण
पूर्ण

अटल व्योम mpic_startup_ht_पूर्णांकerrupt(काष्ठा mpic *mpic, अचिन्हित पूर्णांक source,
				      bool level)
अणु
	काष्ठा mpic_irq_fixup *fixup = &mpic->fixups[source];
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	अगर (fixup->base == शून्य)
		वापस;

	DBG("startup_ht_interrupt(0x%x) index: %d\n",
	    source, fixup->index);
	raw_spin_lock_irqsave(&mpic->fixup_lock, flags);
	/* Enable and configure */
	ग_लिखोb(0x10 + 2 * fixup->index, fixup->base + 2);
	पंचांगp = पढ़ोl(fixup->base + 4);
	पंचांगp &= ~(0x23U);
	अगर (level)
		पंचांगp |= 0x22;
	ग_लिखोl(पंचांगp, fixup->base + 4);
	raw_spin_unlock_irqrestore(&mpic->fixup_lock, flags);

#अगर_घोषित CONFIG_PM
	/* use the lowest bit inverted to the actual HW,
	 * set अगर this fixup was enabled, clear otherwise */
	mpic->save_data[source].fixup_data = पंचांगp | 1;
#पूर्ण_अगर
पूर्ण

अटल व्योम mpic_shutकरोwn_ht_पूर्णांकerrupt(काष्ठा mpic *mpic, अचिन्हित पूर्णांक source)
अणु
	काष्ठा mpic_irq_fixup *fixup = &mpic->fixups[source];
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	अगर (fixup->base == शून्य)
		वापस;

	DBG("shutdown_ht_interrupt(0x%x)\n", source);

	/* Disable */
	raw_spin_lock_irqsave(&mpic->fixup_lock, flags);
	ग_लिखोb(0x10 + 2 * fixup->index, fixup->base + 2);
	पंचांगp = पढ़ोl(fixup->base + 4);
	पंचांगp |= 1;
	ग_लिखोl(पंचांगp, fixup->base + 4);
	raw_spin_unlock_irqrestore(&mpic->fixup_lock, flags);

#अगर_घोषित CONFIG_PM
	/* use the lowest bit inverted to the actual HW,
	 * set अगर this fixup was enabled, clear otherwise */
	mpic->save_data[source].fixup_data = पंचांगp & ~1;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
अटल व्योम __init mpic_scan_ht_msi(काष्ठा mpic *mpic, u8 __iomem *devbase,
				    अचिन्हित पूर्णांक devfn)
अणु
	u8 __iomem *base;
	u8 pos, flags;
	u64 addr = 0;

	क्रम (pos = पढ़ोb(devbase + PCI_CAPABILITY_LIST); pos != 0;
	     pos = पढ़ोb(devbase + pos + PCI_CAP_LIST_NEXT)) अणु
		u8 id = पढ़ोb(devbase + pos + PCI_CAP_LIST_ID);
		अगर (id == PCI_CAP_ID_HT) अणु
			id = पढ़ोb(devbase + pos + 3);
			अगर ((id & HT_5BIT_CAP_MASK) == HT_CAPTYPE_MSI_MAPPING)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (pos == 0)
		वापस;

	base = devbase + pos;

	flags = पढ़ोb(base + HT_MSI_FLAGS);
	अगर (!(flags & HT_MSI_FLAGS_FIXED)) अणु
		addr = पढ़ोl(base + HT_MSI_ADDR_LO) & HT_MSI_ADDR_LO_MASK;
		addr = addr | ((u64)पढ़ोl(base + HT_MSI_ADDR_HI) << 32);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "mpic:   - HT:%02x.%x %s MSI mapping found @ 0x%llx\n",
		PCI_SLOT(devfn), PCI_FUNC(devfn),
		flags & HT_MSI_FLAGS_ENABLE ? "enabled" : "disabled", addr);

	अगर (!(flags & HT_MSI_FLAGS_ENABLE))
		ग_लिखोb(flags | HT_MSI_FLAGS_ENABLE, base + HT_MSI_FLAGS);
पूर्ण
#अन्यथा
अटल व्योम __init mpic_scan_ht_msi(काष्ठा mpic *mpic, u8 __iomem *devbase,
				    अचिन्हित पूर्णांक devfn)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init mpic_scan_ht_pic(काष्ठा mpic *mpic, u8 __iomem *devbase,
				    अचिन्हित पूर्णांक devfn, u32 vdid)
अणु
	पूर्णांक i, irq, n;
	u8 __iomem *base;
	u32 पंचांगp;
	u8 pos;

	क्रम (pos = पढ़ोb(devbase + PCI_CAPABILITY_LIST); pos != 0;
	     pos = पढ़ोb(devbase + pos + PCI_CAP_LIST_NEXT)) अणु
		u8 id = पढ़ोb(devbase + pos + PCI_CAP_LIST_ID);
		अगर (id == PCI_CAP_ID_HT) अणु
			id = पढ़ोb(devbase + pos + 3);
			अगर ((id & HT_5BIT_CAP_MASK) == HT_CAPTYPE_IRQ)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (pos == 0)
		वापस;

	base = devbase + pos;
	ग_लिखोb(0x01, base + 2);
	n = (पढ़ोl(base + 4) >> 16) & 0xff;

	prपूर्णांकk(KERN_INFO "mpic:   - HT:%02x.%x [0x%02x] vendor %04x device %04x"
	       " has %d irqs\n",
	       devfn >> 3, devfn & 0x7, pos, vdid & 0xffff, vdid >> 16, n + 1);

	क्रम (i = 0; i <= n; i++) अणु
		ग_लिखोb(0x10 + 2 * i, base + 2);
		पंचांगp = पढ़ोl(base + 4);
		irq = (पंचांगp >> 16) & 0xff;
		DBG("HT PIC index 0x%x, irq 0x%x, tmp: %08x\n", i, irq, पंचांगp);
		/* mask it , will be unmasked later */
		पंचांगp |= 0x1;
		ग_लिखोl(पंचांगp, base + 4);
		mpic->fixups[irq].index = i;
		mpic->fixups[irq].base = base;
		/* Apple HT PIC has a non-standard way of करोing EOIs */
		अगर ((vdid & 0xffff) == 0x106b)
			mpic->fixups[irq].applebase = devbase + 0x60;
		अन्यथा
			mpic->fixups[irq].applebase = शून्य;
		ग_लिखोb(0x11 + 2 * i, base + 2);
		mpic->fixups[irq].data = पढ़ोl(base + 4) | 0x80000000;
	पूर्ण
पूर्ण


अटल व्योम __init mpic_scan_ht_pics(काष्ठा mpic *mpic)
अणु
	अचिन्हित पूर्णांक devfn;
	u8 __iomem *cfgspace;

	prपूर्णांकk(KERN_INFO "mpic: Setting up HT PICs workarounds for U3/U4\n");

	/* Allocate fixups array */
	mpic->fixups = kसुस्मृति(128, माप(*mpic->fixups), GFP_KERNEL);
	BUG_ON(mpic->fixups == शून्य);

	/* Init spinlock */
	raw_spin_lock_init(&mpic->fixup_lock);

	/* Map U3 config space. We assume all IO-APICs are on the primary bus
	 * so we only need to map 64kB.
	 */
	cfgspace = ioremap(0xf2000000, 0x10000);
	BUG_ON(cfgspace == शून्य);

	/* Now we scan all slots. We करो a very quick scan, we पढ़ो the header
	 * type, venकरोr ID and device ID only, that's plenty enough
	 */
	क्रम (devfn = 0; devfn < 0x100; devfn++) अणु
		u8 __iomem *devbase = cfgspace + (devfn << 8);
		u8 hdr_type = पढ़ोb(devbase + PCI_HEADER_TYPE);
		u32 l = पढ़ोl(devbase + PCI_VENDOR_ID);
		u16 s;

		DBG("devfn %x, l: %x\n", devfn, l);

		/* If no device, skip */
		अगर (l == 0xffffffff || l == 0x00000000 ||
		    l == 0x0000ffff || l == 0xffff0000)
			जाओ next;
		/* Check अगर is supports capability lists */
		s = पढ़ोw(devbase + PCI_STATUS);
		अगर (!(s & PCI_STATUS_CAP_LIST))
			जाओ next;

		mpic_scan_ht_pic(mpic, devbase, devfn, l);
		mpic_scan_ht_msi(mpic, devbase, devfn);

	next:
		/* next device, अगर function 0 */
		अगर (PCI_FUNC(devfn) == 0 && (hdr_type & 0x80) == 0)
			devfn += 7;
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_MPIC_U3_HT_IRQS */

अटल अंतरभूत पूर्णांक mpic_is_ht_पूर्णांकerrupt(काष्ठा mpic *mpic, अचिन्हित पूर्णांक source)
अणु
	वापस 0;
पूर्ण

अटल व्योम __init mpic_scan_ht_pics(काष्ठा mpic *mpic)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MPIC_U3_HT_IRQS */

/* Find an mpic associated with a given linux पूर्णांकerrupt */
अटल काष्ठा mpic *mpic_find(अचिन्हित पूर्णांक irq)
अणु
	अगर (irq < NUM_ISA_INTERRUPTS)
		वापस शून्य;

	वापस irq_get_chip_data(irq);
पूर्ण

/* Determine अगर the linux irq is an IPI */
अटल अचिन्हित पूर्णांक mpic_is_ipi(काष्ठा mpic *mpic, अचिन्हित पूर्णांक src)
अणु
	वापस (src >= mpic->ipi_vecs[0] && src <= mpic->ipi_vecs[3]);
पूर्ण

/* Determine अगर the linux irq is a समयr */
अटल अचिन्हित पूर्णांक mpic_is_पंचांग(काष्ठा mpic *mpic, अचिन्हित पूर्णांक src)
अणु
	वापस (src >= mpic->समयr_vecs[0] && src <= mpic->समयr_vecs[7]);
पूर्ण

/* Convert a cpu mask from logical to physical cpu numbers. */
अटल अंतरभूत u32 mpic_physmask(u32 cpumask)
अणु
	पूर्णांक i;
	u32 mask = 0;

	क्रम (i = 0; i < min(32, NR_CPUS) && cpu_possible(i); ++i, cpumask >>= 1)
		mask |= (cpumask & 1) << get_hard_smp_processor_id(i);
	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_SMP
/* Get the mpic काष्ठाure from the IPI number */
अटल अंतरभूत काष्ठा mpic * mpic_from_ipi(काष्ठा irq_data *d)
अणु
	वापस irq_data_get_irq_chip_data(d);
पूर्ण
#पूर्ण_अगर

/* Get the mpic काष्ठाure from the irq number */
अटल अंतरभूत काष्ठा mpic * mpic_from_irq(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_get_chip_data(irq);
पूर्ण

/* Get the mpic काष्ठाure from the irq data */
अटल अंतरभूत काष्ठा mpic * mpic_from_irq_data(काष्ठा irq_data *d)
अणु
	वापस irq_data_get_irq_chip_data(d);
पूर्ण

/* Send an EOI */
अटल अंतरभूत व्योम mpic_eoi(काष्ठा mpic *mpic)
अणु
	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_EOI), 0);
पूर्ण

/*
 * Linux descriptor level callbacks
 */


व्योम mpic_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक loops = 100000;
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	DBG("%p: %s: enable_irq: %d (src %d)\n", mpic, mpic->name, d->irq, src);

	mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_VECTOR_PRI),
		       mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI)) &
		       ~MPIC_VECPRI_MASK);
	/* make sure mask माला_लो to controller beक्रमe we वापस to user */
	करो अणु
		अगर (!loops--) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout on hwirq %u\n",
			       __func__, src);
			अवरोध;
		पूर्ण
	पूर्ण जबतक(mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI)) & MPIC_VECPRI_MASK);
पूर्ण

व्योम mpic_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक loops = 100000;
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	DBG("%s: disable_irq: %d (src %d)\n", mpic->name, d->irq, src);

	mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_VECTOR_PRI),
		       mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI)) |
		       MPIC_VECPRI_MASK);

	/* make sure mask माला_लो to controller beक्रमe we वापस to user */
	करो अणु
		अगर (!loops--) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout on hwirq %u\n",
			       __func__, src);
			अवरोध;
		पूर्ण
	पूर्ण जबतक(!(mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI)) & MPIC_VECPRI_MASK));
पूर्ण

व्योम mpic_end_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);

#अगर_घोषित DEBUG_IRQ
	DBG("%s: end_irq: %d\n", mpic->name, d->irq);
#पूर्ण_अगर
	/* We always EOI on end_irq() even क्रम edge पूर्णांकerrupts since that
	 * should only lower the priority, the MPIC should have properly
	 * latched another edge पूर्णांकerrupt coming in anyway
	 */

	mpic_eoi(mpic);
पूर्ण

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS

अटल व्योम mpic_unmask_ht_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	mpic_unmask_irq(d);

	अगर (irqd_is_level_type(d))
		mpic_ht_end_irq(mpic, src);
पूर्ण

अटल अचिन्हित पूर्णांक mpic_startup_ht_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	mpic_unmask_irq(d);
	mpic_startup_ht_पूर्णांकerrupt(mpic, src, irqd_is_level_type(d));

	वापस 0;
पूर्ण

अटल व्योम mpic_shutकरोwn_ht_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	mpic_shutकरोwn_ht_पूर्णांकerrupt(mpic, src);
	mpic_mask_irq(d);
पूर्ण

अटल व्योम mpic_end_ht_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

#अगर_घोषित DEBUG_IRQ
	DBG("%s: end_irq: %d\n", mpic->name, d->irq);
#पूर्ण_अगर
	/* We always EOI on end_irq() even क्रम edge पूर्णांकerrupts since that
	 * should only lower the priority, the MPIC should have properly
	 * latched another edge पूर्णांकerrupt coming in anyway
	 */

	अगर (irqd_is_level_type(d))
		mpic_ht_end_irq(mpic, src);
	mpic_eoi(mpic);
पूर्ण
#पूर्ण_अगर /* !CONFIG_MPIC_U3_HT_IRQS */

#अगर_घोषित CONFIG_SMP

अटल व्योम mpic_unmask_ipi(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_ipi(d);
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq) - mpic->ipi_vecs[0];

	DBG("%s: enable_ipi: %d (ipi %d)\n", mpic->name, d->irq, src);
	mpic_ipi_ग_लिखो(src, mpic_ipi_पढ़ो(src) & ~MPIC_VECPRI_MASK);
पूर्ण

अटल व्योम mpic_mask_ipi(काष्ठा irq_data *d)
अणु
	/* NEVER disable an IPI... that's just plain wrong! */
पूर्ण

अटल व्योम mpic_end_ipi(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_ipi(d);

	/*
	 * IPIs are marked IRQ_PER_CPU. This has the side effect of
	 * preventing the IRQ_PENDING/IRQ_INPROGRESS logic from
	 * applying to them. We EOI them late to aव्योम re-entering.
	 */
	mpic_eoi(mpic);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम mpic_unmask_पंचांग(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq) - mpic->समयr_vecs[0];

	DBG("%s: enable_tm: %d (tm %d)\n", mpic->name, d->irq, src);
	mpic_पंचांग_ग_लिखो(src, mpic_पंचांग_पढ़ो(src) & ~MPIC_VECPRI_MASK);
	mpic_पंचांग_पढ़ो(src);
पूर्ण

अटल व्योम mpic_mask_पंचांग(काष्ठा irq_data *d)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq) - mpic->समयr_vecs[0];

	mpic_पंचांग_ग_लिखो(src, mpic_पंचांग_पढ़ो(src) | MPIC_VECPRI_MASK);
	mpic_पंचांग_पढ़ो(src);
पूर्ण

पूर्णांक mpic_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *cpumask,
		      bool क्रमce)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	अगर (mpic->flags & MPIC_SINGLE_DEST_CPU) अणु
		पूर्णांक cpuid = irq_choose_cpu(cpumask);

		mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_DESTINATION), 1 << cpuid);
	पूर्ण अन्यथा अणु
		u32 mask = cpumask_bits(cpumask)[0];

		mask &= cpumask_bits(cpu_online_mask)[0];

		mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_DESTINATION),
			       mpic_physmask(mask));
	पूर्ण

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल अचिन्हित पूर्णांक mpic_type_to_vecpri(काष्ठा mpic *mpic, अचिन्हित पूर्णांक type)
अणु
	/* Now convert sense value */
	चयन(type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		वापस MPIC_INFO(VECPRI_SENSE_EDGE) |
		       MPIC_INFO(VECPRI_POLARITY_POSITIVE);
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		वापस MPIC_INFO(VECPRI_SENSE_EDGE) |
		       MPIC_INFO(VECPRI_POLARITY_NEGATIVE);
	हाल IRQ_TYPE_LEVEL_HIGH:
		वापस MPIC_INFO(VECPRI_SENSE_LEVEL) |
		       MPIC_INFO(VECPRI_POLARITY_POSITIVE);
	हाल IRQ_TYPE_LEVEL_LOW:
	शेष:
		वापस MPIC_INFO(VECPRI_SENSE_LEVEL) |
		       MPIC_INFO(VECPRI_POLARITY_NEGATIVE);
	पूर्ण
पूर्ण

पूर्णांक mpic_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा mpic *mpic = mpic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित पूर्णांक vecpri, vold, vnew;

	DBG("mpic: set_irq_type(mpic:@%p,virq:%d,src:0x%x,type:0x%x)\n",
	    mpic, d->irq, src, flow_type);

	अगर (src >= mpic->num_sources)
		वापस -EINVAL;

	vold = mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI));

	/* We करोn't support "none" type */
	अगर (flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_DEFAULT;

	/* Default: पढ़ो HW settings */
	अगर (flow_type == IRQ_TYPE_DEFAULT) अणु
		पूर्णांक vold_ps;

		vold_ps = vold & (MPIC_INFO(VECPRI_POLARITY_MASK) |
				  MPIC_INFO(VECPRI_SENSE_MASK));

		अगर (vold_ps == (MPIC_INFO(VECPRI_SENSE_EDGE) |
				MPIC_INFO(VECPRI_POLARITY_POSITIVE)))
			flow_type = IRQ_TYPE_EDGE_RISING;
		अन्यथा अगर	(vold_ps == (MPIC_INFO(VECPRI_SENSE_EDGE) |
				     MPIC_INFO(VECPRI_POLARITY_NEGATIVE)))
			flow_type = IRQ_TYPE_EDGE_FALLING;
		अन्यथा अगर (vold_ps == (MPIC_INFO(VECPRI_SENSE_LEVEL) |
				     MPIC_INFO(VECPRI_POLARITY_POSITIVE)))
			flow_type = IRQ_TYPE_LEVEL_HIGH;
		अन्यथा अगर (vold_ps == (MPIC_INFO(VECPRI_SENSE_LEVEL) |
				     MPIC_INFO(VECPRI_POLARITY_NEGATIVE)))
			flow_type = IRQ_TYPE_LEVEL_LOW;
		अन्यथा
			WARN_ONCE(1, "mpic: unknown IRQ type %d\n", vold);
	पूर्ण

	/* Apply to irq desc */
	irqd_set_trigger_type(d, flow_type);

	/* Apply to HW */
	अगर (mpic_is_ht_पूर्णांकerrupt(mpic, src))
		vecpri = MPIC_VECPRI_POLARITY_POSITIVE |
			MPIC_VECPRI_SENSE_EDGE;
	अन्यथा
		vecpri = mpic_type_to_vecpri(mpic, flow_type);

	vnew = vold & ~(MPIC_INFO(VECPRI_POLARITY_MASK) |
			MPIC_INFO(VECPRI_SENSE_MASK));
	vnew |= vecpri;
	अगर (vold != vnew)
		mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_VECTOR_PRI), vnew);

	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

व्योम mpic_set_vector(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक vector)
अणु
	काष्ठा mpic *mpic = mpic_from_irq(virq);
	अचिन्हित पूर्णांक src = virq_to_hw(virq);
	अचिन्हित पूर्णांक vecpri;

	DBG("mpic: set_vector(mpic:@%p,virq:%d,src:%d,vector:0x%x)\n",
	    mpic, virq, src, vector);

	अगर (src >= mpic->num_sources)
		वापस;

	vecpri = mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI));
	vecpri = vecpri & ~MPIC_INFO(VECPRI_VECTOR_MASK);
	vecpri |= vector;
	mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_VECTOR_PRI), vecpri);
पूर्ण

अटल व्योम mpic_set_destination(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा mpic *mpic = mpic_from_irq(virq);
	अचिन्हित पूर्णांक src = virq_to_hw(virq);

	DBG("mpic: set_destination(mpic:@%p,virq:%d,src:%d,cpuid:0x%x)\n",
	    mpic, virq, src, cpuid);

	अगर (src >= mpic->num_sources)
		वापस;

	mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_DESTINATION), 1 << cpuid);
पूर्ण

अटल काष्ठा irq_chip mpic_irq_chip = अणु
	.irq_mask	= mpic_mask_irq,
	.irq_unmask	= mpic_unmask_irq,
	.irq_eoi	= mpic_end_irq,
	.irq_set_type	= mpic_set_irq_type,
पूर्ण;

#अगर_घोषित CONFIG_SMP
अटल स्थिर काष्ठा irq_chip mpic_ipi_chip = अणु
	.irq_mask	= mpic_mask_ipi,
	.irq_unmask	= mpic_unmask_ipi,
	.irq_eoi	= mpic_end_ipi,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SMP */

अटल काष्ठा irq_chip mpic_पंचांग_chip = अणु
	.irq_mask	= mpic_mask_पंचांग,
	.irq_unmask	= mpic_unmask_पंचांग,
	.irq_eoi	= mpic_end_irq,
पूर्ण;

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
अटल स्थिर काष्ठा irq_chip mpic_irq_ht_chip = अणु
	.irq_startup	= mpic_startup_ht_irq,
	.irq_shutकरोwn	= mpic_shutकरोwn_ht_irq,
	.irq_mask	= mpic_mask_irq,
	.irq_unmask	= mpic_unmask_ht_irq,
	.irq_eoi	= mpic_end_ht_irq,
	.irq_set_type	= mpic_set_irq_type,
पूर्ण;
#पूर्ण_अगर /* CONFIG_MPIC_U3_HT_IRQS */


अटल पूर्णांक mpic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			   क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Exact match, unless mpic node is शून्य */
	काष्ठा device_node *of_node = irq_करोमुख्य_get_of_node(h);
	वापस of_node == शून्य || of_node == node;
पूर्ण

अटल पूर्णांक mpic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	काष्ठा mpic *mpic = h->host_data;
	काष्ठा irq_chip *chip;

	DBG("mpic: map virq %d, hwirq 0x%lx\n", virq, hw);

	अगर (hw == mpic->spurious_vec)
		वापस -EINVAL;
	अगर (mpic->रक्षित && test_bit(hw, mpic->रक्षित)) अणु
		pr_warn("mpic: Mapping of source 0x%x failed, source protected by firmware !\n",
			(अचिन्हित पूर्णांक)hw);
		वापस -EPERM;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	अन्यथा अगर (hw >= mpic->ipi_vecs[0]) अणु
		WARN_ON(mpic->flags & MPIC_SECONDARY);

		DBG("mpic: mapping as IPI\n");
		irq_set_chip_data(virq, mpic);
		irq_set_chip_and_handler(virq, &mpic->hc_ipi,
					 handle_percpu_irq);
		वापस 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

	अगर (hw >= mpic->समयr_vecs[0] && hw <= mpic->समयr_vecs[7]) अणु
		WARN_ON(mpic->flags & MPIC_SECONDARY);

		DBG("mpic: mapping as timer\n");
		irq_set_chip_data(virq, mpic);
		irq_set_chip_and_handler(virq, &mpic->hc_पंचांग,
					 handle_fasteoi_irq);
		वापस 0;
	पूर्ण

	अगर (mpic_map_error_पूर्णांक(mpic, virq, hw))
		वापस 0;

	अगर (hw >= mpic->num_sources) अणु
		pr_warn("mpic: Mapping of source 0x%x failed, source out of range !\n",
			(अचिन्हित पूर्णांक)hw);
		वापस -EINVAL;
	पूर्ण

	mpic_msi_reserve_hwirq(mpic, hw);

	/* Default chip */
	chip = &mpic->hc_irq;

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
	/* Check क्रम HT पूर्णांकerrupts, override vecpri */
	अगर (mpic_is_ht_पूर्णांकerrupt(mpic, hw))
		chip = &mpic->hc_ht_irq;
#पूर्ण_अगर /* CONFIG_MPIC_U3_HT_IRQS */

	DBG("mpic: mapping to irq chip @%p\n", chip);

	irq_set_chip_data(virq, mpic);
	irq_set_chip_and_handler(virq, chip, handle_fasteoi_irq);

	/* Set शेष irq type */
	irq_set_irq_type(virq, IRQ_TYPE_DEFAULT);

	/* If the MPIC was reset, then all vectors have alपढ़ोy been
	 * initialized.  Otherwise, a per source lazy initialization
	 * is करोne here.
	 */
	अगर (!mpic_is_ipi(mpic, hw) && (mpic->flags & MPIC_NO_RESET)) अणु
		पूर्णांक cpu;

		preempt_disable();
		cpu = mpic_processor_id(mpic);
		preempt_enable();

		mpic_set_vector(virq, hw);
		mpic_set_destination(virq, cpu);
		mpic_irq_set_priority(virq, 8);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpic_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)

अणु
	काष्ठा mpic *mpic = h->host_data;
	अटल अचिन्हित अक्षर map_mpic_senses[4] = अणु
		IRQ_TYPE_EDGE_RISING,
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
		IRQ_TYPE_EDGE_FALLING,
	पूर्ण;

	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize >= 4 && (mpic->flags & MPIC_FSL)) अणु
		/*
		 * Freescale MPIC with extended पूर्णांकspec:
		 * First two cells are as usual.  Third specअगरies
		 * an "interrupt type".  Fourth is type-specअगरic data.
		 *
		 * See Documentation/devicetree/bindings/घातerpc/fsl/mpic.txt
		 */
		चयन (पूर्णांकspec[2]) अणु
		हाल 0:
			अवरोध;
		हाल 1:
			अगर (!(mpic->flags & MPIC_FSL_HAS_EIMR))
				अवरोध;

			अगर (पूर्णांकspec[3] >= ARRAY_SIZE(mpic->err_पूर्णांक_vecs))
				वापस -EINVAL;

			*out_hwirq = mpic->err_पूर्णांक_vecs[पूर्णांकspec[3]];

			अवरोध;
		हाल 2:
			अगर (पूर्णांकspec[0] >= ARRAY_SIZE(mpic->ipi_vecs))
				वापस -EINVAL;

			*out_hwirq = mpic->ipi_vecs[पूर्णांकspec[0]];
			अवरोध;
		हाल 3:
			अगर (पूर्णांकspec[0] >= ARRAY_SIZE(mpic->समयr_vecs))
				वापस -EINVAL;

			*out_hwirq = mpic->समयr_vecs[पूर्णांकspec[0]];
			अवरोध;
		शेष:
			pr_debug("%s: unknown irq type %u\n",
				 __func__, पूर्णांकspec[2]);
			वापस -EINVAL;
		पूर्ण

		*out_flags = map_mpic_senses[पूर्णांकspec[1] & 3];
	पूर्ण अन्यथा अगर (पूर्णांकsize > 1) अणु
		u32 mask = 0x3;

		/* Apple invented a new race of encoding on machines with
		 * an HT APIC. They encode, among others, the index within
		 * the HT APIC. We करोn't care about it here since thankfully,
		 * it appears that they have the APIC alपढ़ोy properly
		 * configured, and thus our current fixup code that पढ़ोs the
		 * APIC config works fine. However, we still need to mask out
		 * bits in the specअगरier to make sure we only get bit 0 which
		 * is the level/edge bit (the only sense bit exposed by Apple),
		 * as their bit 1 means something अन्यथा.
		 */
		अगर (machine_is(घातermac))
			mask = 0x1;
		*out_flags = map_mpic_senses[पूर्णांकspec[1] & mask];
	पूर्ण अन्यथा
		*out_flags = IRQ_TYPE_NONE;

	DBG("mpic: xlate (%d cells: 0x%08x 0x%08x) to line 0x%lx sense 0x%x\n",
	    पूर्णांकsize, पूर्णांकspec[0], पूर्णांकspec[1], *out_hwirq, *out_flags);

	वापस 0;
पूर्ण

/* IRQ handler क्रम a secondary MPIC cascaded from another IRQ controller */
अटल व्योम mpic_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा mpic *mpic = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक virq;

	BUG_ON(!(mpic->flags & MPIC_SECONDARY));

	virq = mpic_get_one_irq(mpic);
	अगर (virq)
		generic_handle_irq(virq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mpic_host_ops = अणु
	.match = mpic_host_match,
	.map = mpic_host_map,
	.xlate = mpic_host_xlate,
पूर्ण;

अटल u32 fsl_mpic_get_version(काष्ठा mpic *mpic)
अणु
	u32 brr1;

	अगर (!(mpic->flags & MPIC_FSL))
		वापस 0;

	brr1 = _mpic_पढ़ो(mpic->reg_type, &mpic->thiscpuregs,
			MPIC_FSL_BRR1);

	वापस brr1 & MPIC_FSL_BRR1_VER;
पूर्ण

/*
 * Exported functions
 */

u32 fsl_mpic_primary_get_version(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_primary;

	अगर (mpic)
		वापस fsl_mpic_get_version(mpic);

	वापस 0;
पूर्ण

काष्ठा mpic * __init mpic_alloc(काष्ठा device_node *node,
				phys_addr_t phys_addr,
				अचिन्हित पूर्णांक flags,
				अचिन्हित पूर्णांक isu_size,
				अचिन्हित पूर्णांक irq_count,
				स्थिर अक्षर *name)
अणु
	पूर्णांक i, psize, पूर्णांकvec_top;
	काष्ठा mpic *mpic;
	u32 greg_feature;
	स्थिर अक्षर *vers;
	स्थिर u32 *psrc;
	u32 last_irq;
	u32 fsl_version = 0;

	/* Default MPIC search parameters */
	अटल स्थिर काष्ठा of_device_id __initस्थिर mpic_device_id[] = अणु
		अणु .type	      = "open-pic", पूर्ण,
		अणु .compatible = "open-pic", पूर्ण,
		अणुपूर्ण,
	पूर्ण;

	/*
	 * If we were not passed a device-tree node, then perक्रमm the शेष
	 * search क्रम standardized a standardized OpenPIC.
	 */
	अगर (node) अणु
		node = of_node_get(node);
	पूर्ण अन्यथा अणु
		node = of_find_matching_node(शून्य, mpic_device_id);
		अगर (!node)
			वापस शून्य;
	पूर्ण

	/* Pick the physical address from the device tree अगर unspecअगरied */
	अगर (!phys_addr) अणु
		/* Check अगर it is DCR-based */
		अगर (of_property_पढ़ो_bool(node, "dcr-reg")) अणु
			flags |= MPIC_USES_DCR;
		पूर्ण अन्यथा अणु
			काष्ठा resource r;
			अगर (of_address_to_resource(node, 0, &r))
				जाओ err_of_node_put;
			phys_addr = r.start;
		पूर्ण
	पूर्ण

	/* Read extra device-tree properties पूर्णांकo the flags variable */
	अगर (of_get_property(node, "big-endian", शून्य))
		flags |= MPIC_BIG_ENDIAN;
	अगर (of_get_property(node, "pic-no-reset", शून्य))
		flags |= MPIC_NO_RESET;
	अगर (of_get_property(node, "single-cpu-affinity", शून्य))
		flags |= MPIC_SINGLE_DEST_CPU;
	अगर (of_device_is_compatible(node, "fsl,mpic")) अणु
		flags |= MPIC_FSL | MPIC_LARGE_VECTORS;
		mpic_irq_chip.flags |= IRQCHIP_SKIP_SET_WAKE;
		mpic_पंचांग_chip.flags |= IRQCHIP_SKIP_SET_WAKE;
	पूर्ण

	mpic = kzalloc(माप(काष्ठा mpic), GFP_KERNEL);
	अगर (mpic == शून्य)
		जाओ err_of_node_put;

	mpic->name = name;
	mpic->node = node;
	mpic->paddr = phys_addr;
	mpic->flags = flags;

	mpic->hc_irq = mpic_irq_chip;
	mpic->hc_irq.name = name;
	अगर (!(mpic->flags & MPIC_SECONDARY))
		mpic->hc_irq.irq_set_affinity = mpic_set_affinity;
#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
	mpic->hc_ht_irq = mpic_irq_ht_chip;
	mpic->hc_ht_irq.name = name;
	अगर (!(mpic->flags & MPIC_SECONDARY))
		mpic->hc_ht_irq.irq_set_affinity = mpic_set_affinity;
#पूर्ण_अगर /* CONFIG_MPIC_U3_HT_IRQS */

#अगर_घोषित CONFIG_SMP
	mpic->hc_ipi = mpic_ipi_chip;
	mpic->hc_ipi.name = name;
#पूर्ण_अगर /* CONFIG_SMP */

	mpic->hc_पंचांग = mpic_पंचांग_chip;
	mpic->hc_पंचांग.name = name;

	mpic->num_sources = 0; /* so far */

	अगर (mpic->flags & MPIC_LARGE_VECTORS)
		पूर्णांकvec_top = 2047;
	अन्यथा
		पूर्णांकvec_top = 255;

	mpic->समयr_vecs[0] = पूर्णांकvec_top - 12;
	mpic->समयr_vecs[1] = पूर्णांकvec_top - 11;
	mpic->समयr_vecs[2] = पूर्णांकvec_top - 10;
	mpic->समयr_vecs[3] = पूर्णांकvec_top - 9;
	mpic->समयr_vecs[4] = पूर्णांकvec_top - 8;
	mpic->समयr_vecs[5] = पूर्णांकvec_top - 7;
	mpic->समयr_vecs[6] = पूर्णांकvec_top - 6;
	mpic->समयr_vecs[7] = पूर्णांकvec_top - 5;
	mpic->ipi_vecs[0]   = पूर्णांकvec_top - 4;
	mpic->ipi_vecs[1]   = पूर्णांकvec_top - 3;
	mpic->ipi_vecs[2]   = पूर्णांकvec_top - 2;
	mpic->ipi_vecs[3]   = पूर्णांकvec_top - 1;
	mpic->spurious_vec  = पूर्णांकvec_top;

	/* Look क्रम रक्षित sources */
	psrc = of_get_property(mpic->node, "protected-sources", &psize);
	अगर (psrc) अणु
		/* Allocate a biपंचांगap with one bit per पूर्णांकerrupt */
		अचिन्हित पूर्णांक mapsize = BITS_TO_LONGS(पूर्णांकvec_top + 1);
		mpic->रक्षित = kसुस्मृति(mapsize, माप(दीर्घ), GFP_KERNEL);
		BUG_ON(mpic->रक्षित == शून्य);
		क्रम (i = 0; i < psize/माप(u32); i++) अणु
			अगर (psrc[i] > पूर्णांकvec_top)
				जारी;
			__set_bit(psrc[i], mpic->रक्षित);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_MPIC_WEIRD
	mpic->hw_set = mpic_infos[MPIC_GET_REGSET(mpic->flags)];
#पूर्ण_अगर

	/* शेष रेजिस्टर type */
	अगर (mpic->flags & MPIC_BIG_ENDIAN)
		mpic->reg_type = mpic_access_mmio_be;
	अन्यथा
		mpic->reg_type = mpic_access_mmio_le;

	/*
	 * An MPIC with a "dcr-reg" property must be accessed that way, but
	 * only अगर the kernel includes DCR support.
	 */
#अगर_घोषित CONFIG_PPC_DCR
	अगर (mpic->flags & MPIC_USES_DCR)
		mpic->reg_type = mpic_access_dcr;
#अन्यथा
	BUG_ON(mpic->flags & MPIC_USES_DCR);
#पूर्ण_अगर

	/* Map the global रेजिस्टरs */
	mpic_map(mpic, mpic->paddr, &mpic->gregs, MPIC_INFO(GREG_BASE), 0x1000);
	mpic_map(mpic, mpic->paddr, &mpic->पंचांगregs, MPIC_INFO(TIMER_BASE), 0x1000);

	अगर (mpic->flags & MPIC_FSL) अणु
		पूर्णांक ret;

		/*
		 * Yes, Freescale really did put global रेजिस्टरs in the
		 * magic per-cpu area -- and they करोn't even show up in the
		 * non-magic per-cpu copies that this driver normally uses.
		 */
		mpic_map(mpic, mpic->paddr, &mpic->thiscpuregs,
			 MPIC_CPU_THISBASE, 0x1000);

		fsl_version = fsl_mpic_get_version(mpic);

		/* Error पूर्णांकerrupt mask रेजिस्टर (EIMR) is required क्रम
		 * handling inभागidual device error पूर्णांकerrupts. EIMR
		 * was added in MPIC version 4.1.
		 *
		 * Over here we reserve vector number space क्रम error
		 * पूर्णांकerrupt vectors. This space is stolen from the
		 * global vector number space, as in हाल of ipis
		 * and समयr पूर्णांकerrupts.
		 *
		 * Available vector space = पूर्णांकvec_top - 13, where 13
		 * is the number of vectors which have been consumed by
		 * ipis, समयr पूर्णांकerrupts and spurious.
		 */
		अगर (fsl_version >= 0x401) अणु
			ret = mpic_setup_error_पूर्णांक(mpic, पूर्णांकvec_top - 13);
			अगर (ret)
				वापस शून्य;
		पूर्ण

	पूर्ण

	/*
	 * EPR is only available starting with v4.0.  To support
	 * platक्रमms that करोn't know the MPIC version at compile-समय,
	 * such as qemu-e500, turn off coreपूर्णांक अगर this MPIC करोesn't
	 * support it.  Note that we never enable it अगर it wasn't
	 * requested in the first place.
	 *
	 * This is करोne outside the MPIC_FSL check, so that we
	 * also disable coreपूर्णांक अगर the MPIC node करोesn't have
	 * an "fsl,mpic" compatible at all.  This will be the हाल
	 * with device trees generated by older versions of QEMU.
	 * fsl_version will be zero अगर MPIC_FSL is not set.
	 */
	अगर (fsl_version < 0x400 && (flags & MPIC_ENABLE_COREINT)) अणु
		WARN_ON(ppc_md.get_irq != mpic_get_coreपूर्णांक_irq);
		ppc_md.get_irq = mpic_get_irq;
	पूर्ण

	/* Reset */

	/* When using a device-node, reset requests are only honored अगर the MPIC
	 * is allowed to reset.
	 */
	अगर (!(mpic->flags & MPIC_NO_RESET)) अणु
		prपूर्णांकk(KERN_DEBUG "mpic: Resetting\n");
		mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0),
			   mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0))
			   | MPIC_GREG_GCONF_RESET);
		जबतक( mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0))
		       & MPIC_GREG_GCONF_RESET)
			mb();
	पूर्ण

	/* CoreInt */
	अगर (mpic->flags & MPIC_ENABLE_COREINT)
		mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0),
			   mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0))
			   | MPIC_GREG_GCONF_COREINT);

	अगर (mpic->flags & MPIC_ENABLE_MCK)
		mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0),
			   mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0))
			   | MPIC_GREG_GCONF_MCK);

	/*
	 * The MPIC driver will crash अगर there are more cores than we
	 * can initialize, so we may as well catch that problem here.
	 */
	BUG_ON(num_possible_cpus() > MPIC_MAX_CPUS);

	/* Map the per-CPU रेजिस्टरs */
	क्रम_each_possible_cpu(i) अणु
		अचिन्हित पूर्णांक cpu = get_hard_smp_processor_id(i);

		mpic_map(mpic, mpic->paddr, &mpic->cpuregs[cpu],
			 MPIC_INFO(CPU_BASE) + cpu * MPIC_INFO(CPU_STRIDE),
			 0x1000);
	पूर्ण

	/*
	 * Read feature रेजिस्टर.  For non-ISU MPICs, num sources as well. On
	 * ISU MPICs, sources are counted as ISUs are added
	 */
	greg_feature = mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_FEATURE_0));

	/*
	 * By शेष, the last source number comes from the MPIC, but the
	 * device-tree and board support code can override it on buggy hw.
	 * If we get passed an isu_size (multi-isu MPIC) then we use that
	 * as a शेष instead of the value पढ़ो from the HW.
	 */
	last_irq = (greg_feature & MPIC_GREG_FEATURE_LAST_SRC_MASK)
				>> MPIC_GREG_FEATURE_LAST_SRC_SHIFT;
	अगर (isu_size)
		last_irq = isu_size  * MPIC_MAX_ISU - 1;
	of_property_पढ़ो_u32(mpic->node, "last-interrupt-source", &last_irq);
	अगर (irq_count)
		last_irq = irq_count - 1;

	/* Initialize मुख्य ISU अगर none provided */
	अगर (!isu_size) अणु
		isu_size = last_irq + 1;
		mpic->num_sources = isu_size;
		mpic_map(mpic, mpic->paddr, &mpic->isus[0],
				MPIC_INFO(IRQ_BASE),
				MPIC_INFO(IRQ_STRIDE) * isu_size);
	पूर्ण

	mpic->isu_size = isu_size;
	mpic->isu_shअगरt = 1 + __ilog2(mpic->isu_size - 1);
	mpic->isu_mask = (1 << mpic->isu_shअगरt) - 1;

	mpic->irqhost = irq_करोमुख्य_add_linear(mpic->node,
				       पूर्णांकvec_top,
				       &mpic_host_ops, mpic);

	/*
	 * FIXME: The code leaks the MPIC object and mappings here; this
	 * is very unlikely to fail but it ought to be fixed anyways.
	 */
	अगर (mpic->irqhost == शून्य)
		वापस शून्य;

	/* Display version */
	चयन (greg_feature & MPIC_GREG_FEATURE_VERSION_MASK) अणु
	हाल 1:
		vers = "1.0";
		अवरोध;
	हाल 2:
		vers = "1.2";
		अवरोध;
	हाल 3:
		vers = "1.3";
		अवरोध;
	शेष:
		vers = "<unknown>";
		अवरोध;
	पूर्ण
	prपूर्णांकk(KERN_INFO "mpic: Setting up MPIC \"%s\" version %s at %llx,"
	       " max %d CPUs\n",
	       name, vers, (अचिन्हित दीर्घ दीर्घ)mpic->paddr, num_possible_cpus());
	prपूर्णांकk(KERN_INFO "mpic: ISU size: %d, shift: %d, mask: %x\n",
	       mpic->isu_size, mpic->isu_shअगरt, mpic->isu_mask);

	mpic->next = mpics;
	mpics = mpic;

	अगर (!(mpic->flags & MPIC_SECONDARY)) अणु
		mpic_primary = mpic;
		irq_set_शेष_host(mpic->irqhost);
	पूर्ण

	वापस mpic;

err_of_node_put:
	of_node_put(node);
	वापस शून्य;
पूर्ण

व्योम __init mpic_assign_isu(काष्ठा mpic *mpic, अचिन्हित पूर्णांक isu_num,
			    phys_addr_t paddr)
अणु
	अचिन्हित पूर्णांक isu_first = isu_num * mpic->isu_size;

	BUG_ON(isu_num >= MPIC_MAX_ISU);

	mpic_map(mpic,
		 paddr, &mpic->isus[isu_num], 0,
		 MPIC_INFO(IRQ_STRIDE) * mpic->isu_size);

	अगर ((isu_first + mpic->isu_size) > mpic->num_sources)
		mpic->num_sources = isu_first + mpic->isu_size;
पूर्ण

व्योम __init mpic_init(काष्ठा mpic *mpic)
अणु
	पूर्णांक i, cpu;
	पूर्णांक num_समयrs = 4;

	BUG_ON(mpic->num_sources == 0);

	prपूर्णांकk(KERN_INFO "mpic: Initializing for %d sources\n", mpic->num_sources);

	/* Set current processor priority to max */
	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_CURRENT_TASK_PRI), 0xf);

	अगर (mpic->flags & MPIC_FSL) अणु
		u32 version = fsl_mpic_get_version(mpic);

		/*
		 * Timer group B is present at the latest in MPIC 3.1 (e.g.
		 * mpc8536).  It is not present in MPIC 2.0 (e.g. mpc8544).
		 * I करोn't know about the status of पूर्णांकermediate versions (or
		 * whether they even exist).
		 */
		अगर (version >= 0x0301)
			num_समयrs = 8;
	पूर्ण

	/* Initialize समयrs to our reserved vectors and mask them क्रम now */
	क्रम (i = 0; i < num_समयrs; i++) अणु
		अचिन्हित पूर्णांक offset = mpic_पंचांग_offset(mpic, i);

		mpic_ग_लिखो(mpic->पंचांगregs,
			   offset + MPIC_INFO(TIMER_DESTINATION),
			   1 << hard_smp_processor_id());
		mpic_ग_लिखो(mpic->पंचांगregs,
			   offset + MPIC_INFO(TIMER_VECTOR_PRI),
			   MPIC_VECPRI_MASK |
			   (9 << MPIC_VECPRI_PRIORITY_SHIFT) |
			   (mpic->समयr_vecs[0] + i));
	पूर्ण

	/* Initialize IPIs to our reserved vectors and mark them disabled क्रम now */
	mpic_test_broken_ipi(mpic);
	क्रम (i = 0; i < 4; i++) अणु
		mpic_ipi_ग_लिखो(i,
			       MPIC_VECPRI_MASK |
			       (10 << MPIC_VECPRI_PRIORITY_SHIFT) |
			       (mpic->ipi_vecs[0] + i));
	पूर्ण

	/* Do the HT PIC fixups on U3 broken mpic */
	DBG("MPIC flags: %x\n", mpic->flags);
	अगर ((mpic->flags & MPIC_U3_HT_IRQS) && !(mpic->flags & MPIC_SECONDARY)) अणु
		mpic_scan_ht_pics(mpic);
		mpic_u3msi_init(mpic);
	पूर्ण

	mpic_pasemi_msi_init(mpic);

	cpu = mpic_processor_id(mpic);

	अगर (!(mpic->flags & MPIC_NO_RESET)) अणु
		क्रम (i = 0; i < mpic->num_sources; i++) अणु
			/* start with vector = source number, and masked */
			u32 vecpri = MPIC_VECPRI_MASK | i |
				(8 << MPIC_VECPRI_PRIORITY_SHIFT);

			/* check अगर रक्षित */
			अगर (mpic->रक्षित && test_bit(i, mpic->रक्षित))
				जारी;
			/* init hw */
			mpic_irq_ग_लिखो(i, MPIC_INFO(IRQ_VECTOR_PRI), vecpri);
			mpic_irq_ग_लिखो(i, MPIC_INFO(IRQ_DESTINATION), 1 << cpu);
		पूर्ण
	पूर्ण

	/* Init spurious vector */
	mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_SPURIOUS), mpic->spurious_vec);

	/* Disable 8259 passthrough, अगर supported */
	अगर (!(mpic->flags & MPIC_NO_PTHROU_DIS))
		mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0),
			   mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0))
			   | MPIC_GREG_GCONF_8259_PTHROU_DIS);

	अगर (mpic->flags & MPIC_NO_BIAS)
		mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0),
			mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_GLOBAL_CONF_0))
			| MPIC_GREG_GCONF_NO_BIAS);

	/* Set current processor priority to 0 */
	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_CURRENT_TASK_PRI), 0);

#अगर_घोषित CONFIG_PM
	/* allocate memory to save mpic state */
	mpic->save_data = kदो_स्मृति_array(mpic->num_sources,
				        माप(*mpic->save_data),
				        GFP_KERNEL);
	BUG_ON(mpic->save_data == शून्य);
#पूर्ण_अगर

	/* Check अगर this MPIC is chained from a parent पूर्णांकerrupt controller */
	अगर (mpic->flags & MPIC_SECONDARY) अणु
		पूर्णांक virq = irq_of_parse_and_map(mpic->node, 0);
		अगर (virq) अणु
			prपूर्णांकk(KERN_INFO "%pOF: hooking up to IRQ %d\n",
					mpic->node, virq);
			irq_set_handler_data(virq, mpic);
			irq_set_chained_handler(virq, &mpic_cascade);
		पूर्ण
	पूर्ण

	/* FSL mpic error पूर्णांकerrupt initialization */
	अगर (mpic->flags & MPIC_FSL_HAS_EIMR)
		mpic_err_पूर्णांक_init(mpic, MPIC_FSL_ERR_INT);
पूर्ण

व्योम mpic_irq_set_priority(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक pri)
अणु
	काष्ठा mpic *mpic = mpic_find(irq);
	अचिन्हित पूर्णांक src = virq_to_hw(irq);
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!mpic)
		वापस;

	raw_spin_lock_irqsave(&mpic_lock, flags);
	अगर (mpic_is_ipi(mpic, src)) अणु
		reg = mpic_ipi_पढ़ो(src - mpic->ipi_vecs[0]) &
			~MPIC_VECPRI_PRIORITY_MASK;
		mpic_ipi_ग_लिखो(src - mpic->ipi_vecs[0],
			       reg | (pri << MPIC_VECPRI_PRIORITY_SHIFT));
	पूर्ण अन्यथा अगर (mpic_is_पंचांग(mpic, src)) अणु
		reg = mpic_पंचांग_पढ़ो(src - mpic->समयr_vecs[0]) &
			~MPIC_VECPRI_PRIORITY_MASK;
		mpic_पंचांग_ग_लिखो(src - mpic->समयr_vecs[0],
			      reg | (pri << MPIC_VECPRI_PRIORITY_SHIFT));
	पूर्ण अन्यथा अणु
		reg = mpic_irq_पढ़ो(src, MPIC_INFO(IRQ_VECTOR_PRI))
			& ~MPIC_VECPRI_PRIORITY_MASK;
		mpic_irq_ग_लिखो(src, MPIC_INFO(IRQ_VECTOR_PRI),
			       reg | (pri << MPIC_VECPRI_PRIORITY_SHIFT));
	पूर्ण
	raw_spin_unlock_irqrestore(&mpic_lock, flags);
पूर्ण

व्योम mpic_setup_this_cpu(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	काष्ठा mpic *mpic = mpic_primary;
	अचिन्हित दीर्घ flags;
	u32 msk = 1 << hard_smp_processor_id();
	अचिन्हित पूर्णांक i;

	BUG_ON(mpic == शून्य);

	DBG("%s: setup_this_cpu(%d)\n", mpic->name, hard_smp_processor_id());

	raw_spin_lock_irqsave(&mpic_lock, flags);

 	/* let the mpic know we want पूर्णांकrs. शेष affinity is 0xffffffff
	 * until changed via /proc. That's how it's करोne on x86. If we want
	 * it dअगरferently, then we should make sure we also change the शेष
	 * values of irq_desc[].affinity in irq.c.
 	 */
	अगर (distribute_irqs && !(mpic->flags & MPIC_SINGLE_DEST_CPU)) अणु
	 	क्रम (i = 0; i < mpic->num_sources ; i++)
			mpic_irq_ग_लिखो(i, MPIC_INFO(IRQ_DESTINATION),
				mpic_irq_पढ़ो(i, MPIC_INFO(IRQ_DESTINATION)) | msk);
	पूर्ण

	/* Set current processor priority to 0 */
	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_CURRENT_TASK_PRI), 0);

	raw_spin_unlock_irqrestore(&mpic_lock, flags);
#पूर्ण_अगर /* CONFIG_SMP */
पूर्ण

पूर्णांक mpic_cpu_get_priority(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_primary;

	वापस mpic_cpu_पढ़ो(MPIC_INFO(CPU_CURRENT_TASK_PRI));
पूर्ण

व्योम mpic_cpu_set_priority(पूर्णांक prio)
अणु
	काष्ठा mpic *mpic = mpic_primary;

	prio &= MPIC_CPU_TASKPRI_MASK;
	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_CURRENT_TASK_PRI), prio);
पूर्ण

व्योम mpic_tearकरोwn_this_cpu(पूर्णांक secondary)
अणु
	काष्ठा mpic *mpic = mpic_primary;
	अचिन्हित दीर्घ flags;
	u32 msk = 1 << hard_smp_processor_id();
	अचिन्हित पूर्णांक i;

	BUG_ON(mpic == शून्य);

	DBG("%s: teardown_this_cpu(%d)\n", mpic->name, hard_smp_processor_id());
	raw_spin_lock_irqsave(&mpic_lock, flags);

	/* let the mpic know we करोn't want पूर्णांकrs.  */
	क्रम (i = 0; i < mpic->num_sources ; i++)
		mpic_irq_ग_लिखो(i, MPIC_INFO(IRQ_DESTINATION),
			mpic_irq_पढ़ो(i, MPIC_INFO(IRQ_DESTINATION)) & ~msk);

	/* Set current processor priority to max */
	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_CURRENT_TASK_PRI), 0xf);
	/* We need to EOI the IPI since not all platक्रमms reset the MPIC
	 * on boot and new पूर्णांकerrupts wouldn't get delivered otherwise.
	 */
	mpic_eoi(mpic);

	raw_spin_unlock_irqrestore(&mpic_lock, flags);
पूर्ण


अटल अचिन्हित पूर्णांक _mpic_get_one_irq(काष्ठा mpic *mpic, पूर्णांक reg)
अणु
	u32 src;

	src = mpic_cpu_पढ़ो(reg) & MPIC_INFO(VECPRI_VECTOR_MASK);
#अगर_घोषित DEBUG_LOW
	DBG("%s: get_one_irq(reg 0x%x): %d\n", mpic->name, reg, src);
#पूर्ण_अगर
	अगर (unlikely(src == mpic->spurious_vec)) अणु
		अगर (mpic->flags & MPIC_SPV_EOI)
			mpic_eoi(mpic);
		वापस 0;
	पूर्ण
	अगर (unlikely(mpic->रक्षित && test_bit(src, mpic->रक्षित))) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING "%s: Got protected source %d !\n",
				   mpic->name, (पूर्णांक)src);
		mpic_eoi(mpic);
		वापस 0;
	पूर्ण

	वापस irq_linear_revmap(mpic->irqhost, src);
पूर्ण

अचिन्हित पूर्णांक mpic_get_one_irq(काष्ठा mpic *mpic)
अणु
	वापस _mpic_get_one_irq(mpic, MPIC_INFO(CPU_INTACK));
पूर्ण

अचिन्हित पूर्णांक mpic_get_irq(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_primary;

	BUG_ON(mpic == शून्य);

	वापस mpic_get_one_irq(mpic);
पूर्ण

अचिन्हित पूर्णांक mpic_get_coreपूर्णांक_irq(व्योम)
अणु
#अगर_घोषित CONFIG_BOOKE
	काष्ठा mpic *mpic = mpic_primary;
	u32 src;

	BUG_ON(mpic == शून्य);

	src = mfspr(SPRN_EPR);

	अगर (unlikely(src == mpic->spurious_vec)) अणु
		अगर (mpic->flags & MPIC_SPV_EOI)
			mpic_eoi(mpic);
		वापस 0;
	पूर्ण
	अगर (unlikely(mpic->रक्षित && test_bit(src, mpic->रक्षित))) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING "%s: Got protected source %d !\n",
				   mpic->name, (पूर्णांक)src);
		वापस 0;
	पूर्ण

	वापस irq_linear_revmap(mpic->irqhost, src);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अचिन्हित पूर्णांक mpic_get_mcirq(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_primary;

	BUG_ON(mpic == शून्य);

	वापस _mpic_get_one_irq(mpic, MPIC_INFO(CPU_MCACK));
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम mpic_request_ipis(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_primary;
	पूर्णांक i;
	BUG_ON(mpic == शून्य);

	prपूर्णांकk(KERN_INFO "mpic: requesting IPIs...\n");

	क्रम (i = 0; i < 4; i++) अणु
		अचिन्हित पूर्णांक vipi = irq_create_mapping(mpic->irqhost,
						       mpic->ipi_vecs[0] + i);
		अगर (!vipi) अणु
			prपूर्णांकk(KERN_ERR "Failed to map %s\n", smp_ipi_name[i]);
			जारी;
		पूर्ण
		smp_request_message_ipi(vipi, i);
	पूर्ण
पूर्ण

व्योम smp_mpic_message_pass(पूर्णांक cpu, पूर्णांक msg)
अणु
	काष्ठा mpic *mpic = mpic_primary;
	u32 physmask;

	BUG_ON(mpic == शून्य);

	/* make sure we're sending something that translates to an IPI */
	अगर ((अचिन्हित पूर्णांक)msg > 3) अणु
		prपूर्णांकk("SMP %d: smp_message_pass: unknown msg %d\n",
		       smp_processor_id(), msg);
		वापस;
	पूर्ण

#अगर_घोषित DEBUG_IPI
	DBG("%s: send_ipi(ipi_no: %d)\n", mpic->name, msg);
#पूर्ण_अगर

	physmask = 1 << get_hard_smp_processor_id(cpu);

	mpic_cpu_ग_लिखो(MPIC_INFO(CPU_IPI_DISPATCH_0) +
		       msg * MPIC_INFO(CPU_IPI_DISPATCH_STRIDE), physmask);
पूर्ण

व्योम __init smp_mpic_probe(व्योम)
अणु
	पूर्णांक nr_cpus;

	DBG("smp_mpic_probe()...\n");

	nr_cpus = num_possible_cpus();

	DBG("nr_cpus: %d\n", nr_cpus);

	अगर (nr_cpus > 1)
		mpic_request_ipis();
पूर्ण

व्योम smp_mpic_setup_cpu(पूर्णांक cpu)
अणु
	mpic_setup_this_cpu();
पूर्ण

व्योम mpic_reset_core(पूर्णांक cpu)
अणु
	काष्ठा mpic *mpic = mpic_primary;
	u32 pir;
	पूर्णांक cpuid = get_hard_smp_processor_id(cpu);
	पूर्णांक i;

	/* Set target bit क्रम core reset */
	pir = mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_PROCESSOR_INIT));
	pir |= (1 << cpuid);
	mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_PROCESSOR_INIT), pir);
	mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_PROCESSOR_INIT));

	/* Restore target bit after reset complete */
	pir &= ~(1 << cpuid);
	mpic_ग_लिखो(mpic->gregs, MPIC_INFO(GREG_PROCESSOR_INIT), pir);
	mpic_पढ़ो(mpic->gregs, MPIC_INFO(GREG_PROCESSOR_INIT));

	/* Perक्रमm 15 EOI on each reset core to clear pending पूर्णांकerrupts.
	 * This is required क्रम FSL CoreNet based devices */
	अगर (mpic->flags & MPIC_FSL) अणु
		क्रम (i = 0; i < 15; i++) अणु
			_mpic_ग_लिखो(mpic->reg_type, &mpic->cpuregs[cpuid],
				      MPIC_CPU_EOI, 0);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_PM
अटल व्योम mpic_suspend_one(काष्ठा mpic *mpic)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mpic->num_sources; i++) अणु
		mpic->save_data[i].vecprio =
			mpic_irq_पढ़ो(i, MPIC_INFO(IRQ_VECTOR_PRI));
		mpic->save_data[i].dest =
			mpic_irq_पढ़ो(i, MPIC_INFO(IRQ_DESTINATION));
	पूर्ण
पूर्ण

अटल पूर्णांक mpic_suspend(व्योम)
अणु
	काष्ठा mpic *mpic = mpics;

	जबतक (mpic) अणु
		mpic_suspend_one(mpic);
		mpic = mpic->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mpic_resume_one(काष्ठा mpic *mpic)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mpic->num_sources; i++) अणु
		mpic_irq_ग_लिखो(i, MPIC_INFO(IRQ_VECTOR_PRI),
			       mpic->save_data[i].vecprio);
		mpic_irq_ग_लिखो(i, MPIC_INFO(IRQ_DESTINATION),
			       mpic->save_data[i].dest);

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
	अगर (mpic->fixups) अणु
		काष्ठा mpic_irq_fixup *fixup = &mpic->fixups[i];

		अगर (fixup->base) अणु
			/* we use the lowest bit in an inverted meaning */
			अगर ((mpic->save_data[i].fixup_data & 1) == 0)
				जारी;

			/* Enable and configure */
			ग_लिखोb(0x10 + 2 * fixup->index, fixup->base + 2);

			ग_लिखोl(mpic->save_data[i].fixup_data & ~1,
			       fixup->base + 4);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	पूर्ण /* end क्रम loop */
पूर्ण

अटल व्योम mpic_resume(व्योम)
अणु
	काष्ठा mpic *mpic = mpics;

	जबतक (mpic) अणु
		mpic_resume_one(mpic);
		mpic = mpic->next;
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops mpic_syscore_ops = अणु
	.resume = mpic_resume,
	.suspend = mpic_suspend,
पूर्ण;

अटल पूर्णांक mpic_init_sys(व्योम)
अणु
	पूर्णांक rc;

	रेजिस्टर_syscore_ops(&mpic_syscore_ops);
	rc = subsys_प्रणाली_रेजिस्टर(&mpic_subsys, शून्य);
	अगर (rc) अणु
		unरेजिस्टर_syscore_ops(&mpic_syscore_ops);
		pr_err("mpic: Failed to register subsystem!\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

device_initcall(mpic_init_sys);
#पूर्ण_अगर
