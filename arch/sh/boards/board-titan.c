<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/titan/setup.c - Setup क्रम Titan
 *
 *  Copyright (C) 2006  Jamie Lenehan
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <mach/titan.h>
#समावेश <यंत्र/पन.स>

अटल व्योम __init init_titan_irq(व्योम)
अणु
	/* enable inभागidual पूर्णांकerrupt mode क्रम बाह्यals */
	plat_irq_setup_pins(IRQ_MODE_IRQ);
पूर्ण

अटल काष्ठा sh_machine_vector mv_titan __iniपंचांगv = अणु
	.mv_name	= "Titan",
	.mv_init_irq	= init_titan_irq,
पूर्ण;
