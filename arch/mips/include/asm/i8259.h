<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/i8259.h
 *
 *	i8259A पूर्णांकerrupt definitions.
 *
 *	Copyright (C) 2003  Maciej W. Rozycki
 *	Copyright (C) 2003  Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित _ASM_I8259_H
#घोषणा _ASM_I8259_H

#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/पन.स>
#समावेश <irq.h>

/* i8259A PIC रेजिस्टरs */
#घोषणा PIC_MASTER_CMD		0x20
#घोषणा PIC_MASTER_IMR		0x21
#घोषणा PIC_MASTER_ISR		PIC_MASTER_CMD
#घोषणा PIC_MASTER_POLL		PIC_MASTER_ISR
#घोषणा PIC_MASTER_OCW3		PIC_MASTER_ISR
#घोषणा PIC_SLAVE_CMD		0xa0
#घोषणा PIC_SLAVE_IMR		0xa1

/* i8259A PIC related value */
#घोषणा PIC_CASCADE_IR		2
#घोषणा MASTER_ICW4_DEFAULT	0x01
#घोषणा SLAVE_ICW4_DEFAULT	0x01
#घोषणा PIC_ICW4_AEOI		2

बाह्य raw_spinlock_t i8259A_lock;

बाह्य व्योम make_8259A_irq(अचिन्हित पूर्णांक irq);

बाह्य व्योम init_i8259_irqs(व्योम);
बाह्य काष्ठा irq_करोमुख्य *__init_i8259_irqs(काष्ठा device_node *node);

/**
 * i8159_set_poll() - Override the i8259 polling function
 * @poll: poपूर्णांकer to platक्रमm-specअगरic polling function
 *
 * Call this to override the generic i8259 polling function, which directly
 * accesses i8259 रेजिस्टरs, with a platक्रमm specअगरic one which may be faster
 * in हालs where hardware provides a more optimal means of polling क्रम an
 * पूर्णांकerrupt.
 */
बाह्य व्योम i8259_set_poll(पूर्णांक (*poll)(व्योम));

/*
 * Do the traditional i8259 पूर्णांकerrupt polling thing.  This is क्रम the few
 * हालs where no better पूर्णांकerrupt acknowledge method is available and we
 * असलolutely must touch the i8259.
 */
अटल अंतरभूत पूर्णांक i8259_irq(व्योम)
अणु
	पूर्णांक irq;

	raw_spin_lock(&i8259A_lock);

	/* Perक्रमm an पूर्णांकerrupt acknowledge cycle on controller 1. */
	outb(0x0C, PIC_MASTER_CMD);		/* prepare क्रम poll */
	irq = inb(PIC_MASTER_CMD) & 7;
	अगर (irq == PIC_CASCADE_IR) अणु
		/*
		 * Interrupt is cascaded so perक्रमm पूर्णांकerrupt
		 * acknowledge on controller 2.
		 */
		outb(0x0C, PIC_SLAVE_CMD);		/* prepare क्रम poll */
		irq = (inb(PIC_SLAVE_CMD) & 7) + 8;
	पूर्ण

	अगर (unlikely(irq == 7)) अणु
		/*
		 * This may be a spurious पूर्णांकerrupt.
		 *
		 * Read the पूर्णांकerrupt status रेजिस्टर (ISR). If the most
		 * signअगरicant bit is not set then there is no valid
		 * पूर्णांकerrupt.
		 */
		outb(0x0B, PIC_MASTER_ISR);		/* ISR रेजिस्टर */
		अगर(~inb(PIC_MASTER_ISR) & 0x80)
			irq = -1;
	पूर्ण

	raw_spin_unlock(&i8259A_lock);

	वापस likely(irq >= 0) ? irq + I8259A_IRQ_BASE : irq;
पूर्ण

#पूर्ण_अगर /* _ASM_I8259_H */
