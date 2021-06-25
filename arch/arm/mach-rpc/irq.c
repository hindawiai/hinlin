<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/hardware/iomd.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/fiq.h>

// These are offsets from the stat रेजिस्टर क्रम each IRQ bank
#घोषणा STAT	0x00
#घोषणा REQ	0x04
#घोषणा CLR	0x04
#घोषणा MASK	0x08

अटल व्योम __iomem *iomd_get_base(काष्ठा irq_data *d)
अणु
	व्योम *cd = irq_data_get_irq_chip_data(d);

	वापस (व्योम __iomem *)(अचिन्हित दीर्घ)cd;
पूर्ण

अटल व्योम iomd_set_base_mask(अचिन्हित पूर्णांक irq, व्योम __iomem *base, u32 mask)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);

	d->mask = mask;
	irq_set_chip_data(irq, (व्योम *)(अचिन्हित दीर्घ)base);
पूर्ण

अटल व्योम iomd_irq_mask_ack(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = iomd_get_base(d);
	अचिन्हित पूर्णांक val, mask = d->mask;

	val = पढ़ोb(base + MASK);
	ग_लिखोb(val & ~mask, base + MASK);
	ग_लिखोb(mask, base + CLR);
पूर्ण

अटल व्योम iomd_irq_mask(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = iomd_get_base(d);
	अचिन्हित पूर्णांक val, mask = d->mask;

	val = पढ़ोb(base + MASK);
	ग_लिखोb(val & ~mask, base + MASK);
पूर्ण

अटल व्योम iomd_irq_unmask(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = iomd_get_base(d);
	अचिन्हित पूर्णांक val, mask = d->mask;

	val = पढ़ोb(base + MASK);
	ग_लिखोb(val | mask, base + MASK);
पूर्ण

अटल काष्ठा irq_chip iomd_chip_clr = अणु
	.irq_mask_ack	= iomd_irq_mask_ack,
	.irq_mask	= iomd_irq_mask,
	.irq_unmask	= iomd_irq_unmask,
पूर्ण;

अटल काष्ठा irq_chip iomd_chip_noclr = अणु
	.irq_mask	= iomd_irq_mask,
	.irq_unmask	= iomd_irq_unmask,
पूर्ण;

बाह्य अचिन्हित अक्षर rpc_शेष_fiq_start, rpc_शेष_fiq_end;

व्योम __init rpc_init_irq(व्योम)
अणु
	अचिन्हित पूर्णांक irq, clr, set;

	iomd_ग_लिखोb(0, IOMD_IRQMASKA);
	iomd_ग_लिखोb(0, IOMD_IRQMASKB);
	iomd_ग_लिखोb(0, IOMD_FIQMASK);
	iomd_ग_लिखोb(0, IOMD_DMAMASK);

	set_fiq_handler(&rpc_शेष_fiq_start,
		&rpc_शेष_fiq_end - &rpc_शेष_fiq_start);

	क्रम (irq = 0; irq < NR_IRQS; irq++) अणु
		clr = IRQ_NOREQUEST;
		set = 0;

		अगर (irq <= 6 || (irq >= 9 && irq <= 15))
			clr |= IRQ_NOPROBE;

		अगर (irq == 21 || (irq >= 16 && irq <= 19) ||
		    irq == IRQ_KEYBOARDTX)
			set |= IRQ_NOAUTOEN;

		चयन (irq) अणु
		हाल 0 ... 7:
			irq_set_chip_and_handler(irq, &iomd_chip_clr,
						 handle_level_irq);
			irq_modअगरy_status(irq, clr, set);
			iomd_set_base_mask(irq, IOMD_BASE + IOMD_IRQSTATA,
					   BIT(irq));
			अवरोध;

		हाल 8 ... 15:
			irq_set_chip_and_handler(irq, &iomd_chip_noclr,
						 handle_level_irq);
			irq_modअगरy_status(irq, clr, set);
			iomd_set_base_mask(irq, IOMD_BASE + IOMD_IRQSTATB,
					   BIT(irq - 8));
			अवरोध;

		हाल 16 ... 21:
			irq_set_chip_and_handler(irq, &iomd_chip_noclr,
						 handle_level_irq);
			irq_modअगरy_status(irq, clr, set);
			iomd_set_base_mask(irq, IOMD_BASE + IOMD_DMASTAT,
					   BIT(irq - 16));
			अवरोध;

		हाल 64 ... 71:
			irq_set_chip(irq, &iomd_chip_noclr);
			irq_modअगरy_status(irq, clr, set);
			iomd_set_base_mask(irq, IOMD_BASE + IOMD_FIQSTAT,
					   BIT(irq - 64));
			अवरोध;
		पूर्ण
	पूर्ण

	init_FIQ(FIQ_START);
पूर्ण
