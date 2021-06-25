<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006, Thomas Gleixner, Russell King
 *
 * This file contains the dummy पूर्णांकerrupt chip implementation
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/export.h>

#समावेश "internals.h"

/*
 * What should we करो अगर we get a hw irq event on an illegal vector?
 * Each architecture has to answer this themselves.
 */
अटल व्योम ack_bad(काष्ठा irq_data *data)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(data);

	prपूर्णांक_irq_desc(data->irq, desc);
	ack_bad_irq(data->irq);
पूर्ण

/*
 * NOP functions
 */
अटल व्योम noop(काष्ठा irq_data *data) अणु पूर्ण

अटल अचिन्हित पूर्णांक noop_ret(काष्ठा irq_data *data)
अणु
	वापस 0;
पूर्ण

/*
 * Generic no controller implementation
 */
काष्ठा irq_chip no_irq_chip = अणु
	.name		= "none",
	.irq_startup	= noop_ret,
	.irq_shutकरोwn	= noop,
	.irq_enable	= noop,
	.irq_disable	= noop,
	.irq_ack	= ack_bad,
	.flags		= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

/*
 * Generic dummy implementation which can be used क्रम
 * real dumb पूर्णांकerrupt sources
 */
काष्ठा irq_chip dummy_irq_chip = अणु
	.name		= "dummy",
	.irq_startup	= noop_ret,
	.irq_shutकरोwn	= noop,
	.irq_enable	= noop,
	.irq_disable	= noop,
	.irq_ack	= noop,
	.irq_mask	= noop,
	.irq_unmask	= noop,
	.flags		= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;
EXPORT_SYMBOL_GPL(dummy_irq_chip);
