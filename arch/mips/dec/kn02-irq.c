<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	DECstation 5000/200 (KN02) Control and Status Register
 *	पूर्णांकerrupts.
 *
 *	Copyright (c) 2002, 2003, 2005  Maciej W. Rozycki
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/dec/kn02.h>


/*
 * Bits 7:0 of the Control Register are ग_लिखो-only -- the
 * corresponding bits of the Status Register have a dअगरferent
 * meaning.  Hence we use a cache.  It speeds up things a bit
 * as well.
 *
 * There is no शेष value -- it has to be initialized.
 */
u32 cached_kn02_csr;

अटल पूर्णांक kn02_irq_base;

अटल व्योम unmask_kn02_irq(काष्ठा irq_data *d)
अणु
	अस्थिर u32 *csr = (अस्थिर u32 *)CKSEG1ADDR(KN02_SLOT_BASE +
						       KN02_CSR);

	cached_kn02_csr |= (1 << (d->irq - kn02_irq_base + 16));
	*csr = cached_kn02_csr;
पूर्ण

अटल व्योम mask_kn02_irq(काष्ठा irq_data *d)
अणु
	अस्थिर u32 *csr = (अस्थिर u32 *)CKSEG1ADDR(KN02_SLOT_BASE +
						       KN02_CSR);

	cached_kn02_csr &= ~(1 << (d->irq - kn02_irq_base + 16));
	*csr = cached_kn02_csr;
पूर्ण

अटल व्योम ack_kn02_irq(काष्ठा irq_data *d)
अणु
	mask_kn02_irq(d);
	iob();
पूर्ण

अटल काष्ठा irq_chip kn02_irq_type = अणु
	.name = "KN02-CSR",
	.irq_ack = ack_kn02_irq,
	.irq_mask = mask_kn02_irq,
	.irq_mask_ack = ack_kn02_irq,
	.irq_unmask = unmask_kn02_irq,
पूर्ण;

व्योम __init init_kn02_irqs(पूर्णांक base)
अणु
	अस्थिर u32 *csr = (अस्थिर u32 *)CKSEG1ADDR(KN02_SLOT_BASE +
						       KN02_CSR);
	पूर्णांक i;

	/* Mask पूर्णांकerrupts. */
	cached_kn02_csr &= ~KN02_CSR_IOINTEN;
	*csr = cached_kn02_csr;
	iob();

	क्रम (i = base; i < base + KN02_IRQ_LINES; i++)
		irq_set_chip_and_handler(i, &kn02_irq_type, handle_level_irq);

	kn02_irq_base = base;
पूर्ण
