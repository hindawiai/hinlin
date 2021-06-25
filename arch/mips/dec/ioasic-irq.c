<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	DEC I/O ASIC पूर्णांकerrupts.
 *
 *	Copyright (c) 2002, 2003, 2013  Maciej W. Rozycki
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/dec/ioasic.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>
#समावेश <यंत्र/dec/ioasic_पूर्णांकs.h>

अटल पूर्णांक ioasic_irq_base;

अटल व्योम unmask_ioasic_irq(काष्ठा irq_data *d)
अणु
	u32 simr;

	simr = ioasic_पढ़ो(IO_REG_SIMR);
	simr |= (1 << (d->irq - ioasic_irq_base));
	ioasic_ग_लिखो(IO_REG_SIMR, simr);
पूर्ण

अटल व्योम mask_ioasic_irq(काष्ठा irq_data *d)
अणु
	u32 simr;

	simr = ioasic_पढ़ो(IO_REG_SIMR);
	simr &= ~(1 << (d->irq - ioasic_irq_base));
	ioasic_ग_लिखो(IO_REG_SIMR, simr);
पूर्ण

अटल व्योम ack_ioasic_irq(काष्ठा irq_data *d)
अणु
	mask_ioasic_irq(d);
	fast_iob();
पूर्ण

अटल काष्ठा irq_chip ioasic_irq_type = अणु
	.name = "IO-ASIC",
	.irq_ack = ack_ioasic_irq,
	.irq_mask = mask_ioasic_irq,
	.irq_mask_ack = ack_ioasic_irq,
	.irq_unmask = unmask_ioasic_irq,
पूर्ण;

अटल व्योम clear_ioasic_dma_irq(काष्ठा irq_data *d)
अणु
	u32 sir;

	sir = ~(1 << (d->irq - ioasic_irq_base));
	ioasic_ग_लिखो(IO_REG_SIR, sir);
	fast_iob();
पूर्ण

अटल काष्ठा irq_chip ioasic_dma_irq_type = अणु
	.name = "IO-ASIC-DMA",
	.irq_ack = clear_ioasic_dma_irq,
	.irq_mask = mask_ioasic_irq,
	.irq_unmask = unmask_ioasic_irq,
	.irq_eoi = clear_ioasic_dma_irq,
पूर्ण;

/*
 * I/O ASIC implements two kinds of DMA पूर्णांकerrupts, inक्रमmational and
 * error पूर्णांकerrupts.
 *
 * The क्रमmers करो not stop DMA and should be cleared as soon as possible
 * so that अगर they retrigger beक्रमe the handler has completed, usually as
 * a side effect of actions taken by the handler, then they are reissued.
 * These use the `handle_edge_irq' handler that clears the request right
 * away.
 *
 * The latters stop DMA and करो not resume it until the पूर्णांकerrupt has been
 * cleared.  This cannot be करोne until after a corrective action has been
 * taken and this also means they will not retrigger.  Thereक्रमe they use
 * the `handle_fasteoi_irq' handler that only clears the request on the
 * way out.  Because MIPS processor पूर्णांकerrupt inमाला_दो, one of which the I/O
 * ASIC is cascaded to, are level-triggered it is recommended that error
 * DMA पूर्णांकerrupt action handlers are रेजिस्टरed with the IRQF_ONESHOT flag
 * set so that they are run with the पूर्णांकerrupt line masked.
 *
 * This mask has `1' bits in the positions of inक्रमmational पूर्णांकerrupts.
 */
#घोषणा IO_IRQ_DMA_INFO							\
	(IO_IRQ_MASK(IO_INR_SCC0A_RXDMA) |				\
	 IO_IRQ_MASK(IO_INR_SCC1A_RXDMA) |				\
	 IO_IRQ_MASK(IO_INR_ISDN_TXDMA) |				\
	 IO_IRQ_MASK(IO_INR_ISDN_RXDMA) |				\
	 IO_IRQ_MASK(IO_INR_ASC_DMA))

व्योम __init init_ioasic_irqs(पूर्णांक base)
अणु
	पूर्णांक i;

	/* Mask पूर्णांकerrupts. */
	ioasic_ग_लिखो(IO_REG_SIMR, 0);
	fast_iob();

	क्रम (i = base; i < base + IO_INR_DMA; i++)
		irq_set_chip_and_handler(i, &ioasic_irq_type,
					 handle_level_irq);
	क्रम (; i < base + IO_IRQ_LINES; i++)
		irq_set_chip_and_handler(i, &ioasic_dma_irq_type,
					 1 << (i - base) & IO_IRQ_DMA_INFO ?
					 handle_edge_irq : handle_fasteoi_irq);

	ioasic_irq_base = base;
पूर्ण
