<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/irq/imask.c
 *
 * Copyright (C) 1999, 2000  Niibe Yutaka
 *
 * Simple पूर्णांकerrupt handling using IMASK of SR रेजिस्टर.
 *
 */
/* NOTE: Will not work on level 15 */
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cache.h>
#समावेश <linux/irq.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <यंत्र/irq.h>

/* Biपंचांगap of IRQ masked */
#घोषणा IMASK_PRIORITY	15

अटल DECLARE_BITMAP(imask_mask, IMASK_PRIORITY);
अटल पूर्णांक पूर्णांकerrupt_priority;

अटल अंतरभूत व्योम set_पूर्णांकerrupt_रेजिस्टरs(पूर्णांक ip)
अणु
	अचिन्हित दीर्घ __dummy;

	यंत्र अस्थिर(
#अगर_घोषित CONFIG_CPU_HAS_SR_RB
		     "ldc	%2, r6_bank\n\t"
#पूर्ण_अगर
		     "stc	sr, %0\n\t"
		     "and	#0xf0, %0\n\t"
		     "shlr2	%0\n\t"
		     "cmp/eq	#0x3c, %0\n\t"
		     "bt/s	1f	! CLI-ed\n\t"
		     " stc	sr, %0\n\t"
		     "and	%1, %0\n\t"
		     "or	%2, %0\n\t"
		     "ldc	%0, sr\n"
		     "1:"
		     : "=&z" (__dummy)
		     : "r" (~0xf0), "r" (ip << 4)
		     : "t");
पूर्ण

अटल व्योम mask_imask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	clear_bit(irq, imask_mask);
	अगर (पूर्णांकerrupt_priority < IMASK_PRIORITY - irq)
		पूर्णांकerrupt_priority = IMASK_PRIORITY - irq;
	set_पूर्णांकerrupt_रेजिस्टरs(पूर्णांकerrupt_priority);
पूर्ण

अटल व्योम unmask_imask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	set_bit(irq, imask_mask);
	पूर्णांकerrupt_priority = IMASK_PRIORITY -
		find_first_zero_bit(imask_mask, IMASK_PRIORITY);
	set_पूर्णांकerrupt_रेजिस्टरs(पूर्णांकerrupt_priority);
पूर्ण

अटल काष्ठा irq_chip imask_irq_chip = अणु
	.name		= "SR.IMASK",
	.irq_mask	= mask_imask_irq,
	.irq_unmask	= unmask_imask_irq,
	.irq_mask_ack	= mask_imask_irq,
पूर्ण;

व्योम make_imask_irq(अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler_name(irq, &imask_irq_chip, handle_level_irq,
				      "level");
पूर्ण
