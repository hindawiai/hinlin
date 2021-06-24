<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bcsr.h -- Db1xxx/Pb1xxx Devboard CPLD रेजिस्टरs ("BCSR") असलtraction.
 *
 * All Alchemy development boards (except, of course, the weird PB1000)
 * have a few रेजिस्टरs in a CPLD with standardised layout; they mostly
 * only dअगरfer in base address.
 * All रेजिस्टरs are 16bits wide with 32bit spacing.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

अटल काष्ठा bcsr_reg अणु
	व्योम __iomem *raddr;
	spinlock_t lock;
पूर्ण bcsr_regs[BCSR_CNT];

अटल व्योम __iomem *bcsr_virt; /* KSEG1 addr of BCSR base */
अटल पूर्णांक bcsr_csc_base;	/* linux-irq of first cascaded irq */

व्योम __init bcsr_init(अचिन्हित दीर्घ bcsr1_phys, अचिन्हित दीर्घ bcsr2_phys)
अणु
	पूर्णांक i;

	bcsr1_phys = KSEG1ADDR(CPHYSADDR(bcsr1_phys));
	bcsr2_phys = KSEG1ADDR(CPHYSADDR(bcsr2_phys));

	bcsr_virt = (व्योम __iomem *)bcsr1_phys;

	क्रम (i = 0; i < BCSR_CNT; i++) अणु
		अगर (i >= BCSR_HEXLEDS)
			bcsr_regs[i].raddr = (व्योम __iomem *)bcsr2_phys +
					(0x04 * (i - BCSR_HEXLEDS));
		अन्यथा
			bcsr_regs[i].raddr = (व्योम __iomem *)bcsr1_phys +
					(0x04 * i);

		spin_lock_init(&bcsr_regs[i].lock);
	पूर्ण
पूर्ण

अचिन्हित लघु bcsr_पढ़ो(क्रमागत bcsr_id reg)
अणु
	अचिन्हित लघु r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bcsr_regs[reg].lock, flags);
	r = __raw_पढ़ोw(bcsr_regs[reg].raddr);
	spin_unlock_irqrestore(&bcsr_regs[reg].lock, flags);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(bcsr_पढ़ो);

व्योम bcsr_ग_लिखो(क्रमागत bcsr_id reg, अचिन्हित लघु val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bcsr_regs[reg].lock, flags);
	__raw_ग_लिखोw(val, bcsr_regs[reg].raddr);
	wmb();
	spin_unlock_irqrestore(&bcsr_regs[reg].lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(bcsr_ग_लिखो);

व्योम bcsr_mod(क्रमागत bcsr_id reg, अचिन्हित लघु clr, अचिन्हित लघु set)
अणु
	अचिन्हित लघु r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bcsr_regs[reg].lock, flags);
	r = __raw_पढ़ोw(bcsr_regs[reg].raddr);
	r &= ~clr;
	r |= set;
	__raw_ग_लिखोw(r, bcsr_regs[reg].raddr);
	wmb();
	spin_unlock_irqrestore(&bcsr_regs[reg].lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(bcsr_mod);

/*
 * DB1200/PB1200 CPLD IRQ muxer
 */
अटल व्योम bcsr_csc_handler(काष्ठा irq_desc *d)
अणु
	अचिन्हित लघु bisr = __raw_पढ़ोw(bcsr_virt + BCSR_REG_INTSTAT);
	काष्ठा irq_chip *chip = irq_desc_get_chip(d);

	chained_irq_enter(chip, d);
	generic_handle_irq(bcsr_csc_base + __ffs(bisr));
	chained_irq_निकास(chip, d);
पूर्ण

अटल व्योम bcsr_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित लघु v = 1 << (d->irq - bcsr_csc_base);
	__raw_ग_लिखोw(v, bcsr_virt + BCSR_REG_MASKCLR);
	wmb();
पूर्ण

अटल व्योम bcsr_irq_maskack(काष्ठा irq_data *d)
अणु
	अचिन्हित लघु v = 1 << (d->irq - bcsr_csc_base);
	__raw_ग_लिखोw(v, bcsr_virt + BCSR_REG_MASKCLR);
	__raw_ग_लिखोw(v, bcsr_virt + BCSR_REG_INTSTAT);	/* ack */
	wmb();
पूर्ण

अटल व्योम bcsr_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित लघु v = 1 << (d->irq - bcsr_csc_base);
	__raw_ग_लिखोw(v, bcsr_virt + BCSR_REG_MASKSET);
	wmb();
पूर्ण

अटल काष्ठा irq_chip bcsr_irq_type = अणु
	.name		= "CPLD",
	.irq_mask	= bcsr_irq_mask,
	.irq_mask_ack	= bcsr_irq_maskack,
	.irq_unmask	= bcsr_irq_unmask,
पूर्ण;

व्योम __init bcsr_init_irq(पूर्णांक csc_start, पूर्णांक csc_end, पूर्णांक hook_irq)
अणु
	अचिन्हित पूर्णांक irq;

	/* mask & enable & ack all */
	__raw_ग_लिखोw(0xffff, bcsr_virt + BCSR_REG_MASKCLR);
	__raw_ग_लिखोw(0xffff, bcsr_virt + BCSR_REG_INTSET);
	__raw_ग_लिखोw(0xffff, bcsr_virt + BCSR_REG_INTSTAT);
	wmb();

	bcsr_csc_base = csc_start;

	क्रम (irq = csc_start; irq <= csc_end; irq++)
		irq_set_chip_and_handler_name(irq, &bcsr_irq_type,
					      handle_level_irq, "level");

	irq_set_chained_handler(hook_irq, bcsr_csc_handler);
पूर्ण
