<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/shmin/setup.c
 *
 * Copyright (C) 2006 Takashi YOSHII
 *
 * SHMIN Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach/shmin.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/पन.स>

#घोषणा PFC_PHCR	0xa400010eUL
#घोषणा INTC_ICR1	0xa4000010UL

अटल व्योम __init init_shmin_irq(व्योम)
अणु
	__raw_ग_लिखोw(0x2a00, PFC_PHCR);	// IRQ0-3=IRQ
	__raw_ग_लिखोw(0x0aaa, INTC_ICR1);	// IRQ0-3=IRQ-mode,Low-active.
	plat_irq_setup_pins(IRQ_MODE_IRQ);
पूर्ण

अटल व्योम __init shmin_setup(अक्षर **cmdline_p)
अणु
	__set_io_port_base(SHMIN_IO_BASE);
पूर्ण

अटल काष्ठा sh_machine_vector mv_shmin __iniपंचांगv = अणु
	.mv_name	= "SHMIN",
	.mv_setup	= shmin_setup,
	.mv_init_irq	= init_shmin_irq,
पूर्ण;
