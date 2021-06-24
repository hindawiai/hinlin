<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-iop32x/irq.c
 *
 * Generic IOP32X IRQ handling functionality
 *
 * Author: Rory Bolt <rorybolt@pacbell.net>
 * Copyright (C) 2002 Rory Bolt
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "hardware.h"

अटल u32 iop32x_mask;

अटल व्योम पूर्णांकctl_ग_लिखो(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c0, c0, 0" : : "r" (val));
पूर्ण

अटल व्योम पूर्णांकstr_ग_लिखो(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c4, c0, 0" : : "r" (val));
पूर्ण

अटल व्योम
iop32x_irq_mask(काष्ठा irq_data *d)
अणु
	iop32x_mask &= ~(1 << d->irq);
	पूर्णांकctl_ग_लिखो(iop32x_mask);
पूर्ण

अटल व्योम
iop32x_irq_unmask(काष्ठा irq_data *d)
अणु
	iop32x_mask |= 1 << d->irq;
	पूर्णांकctl_ग_लिखो(iop32x_mask);
पूर्ण

काष्ठा irq_chip ext_chip = अणु
	.name		= "IOP32x",
	.irq_ack	= iop32x_irq_mask,
	.irq_mask	= iop32x_irq_mask,
	.irq_unmask	= iop32x_irq_unmask,
पूर्ण;

व्योम __init iop32x_init_irq(व्योम)
अणु
	पूर्णांक i;

	iop_init_cp6_handler();

	पूर्णांकctl_ग_लिखो(0);
	पूर्णांकstr_ग_लिखो(0);
	अगर (machine_is_glantank() ||
	    machine_is_iq80321() ||
	    machine_is_iq31244() ||
	    machine_is_n2100() ||
	    machine_is_em7210())
		*IOP3XX_PCIIRSR = 0x0f;

	क्रम (i = 0; i < NR_IRQS; i++) अणु
		irq_set_chip_and_handler(i, &ext_chip, handle_level_irq);
		irq_clear_status_flags(i, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण
पूर्ण
