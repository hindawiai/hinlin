<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7721/irq.c
 *
 * Copyright (C) 2008  Renesas Solutions Corp.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <mach-se/mach/se7721.h>

क्रमागत अणु
	UNUSED = 0,

	/* board specअगरic पूर्णांकerrupt sources */
	MRSHPC,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(MRSHPC, MRSHPC_IRQ0),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु FPGA_ILSR6, 0, 8, 4, /* IRLMSK */
	  अणु 0, MRSHPC पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "SE7721", vectors,
			 शून्य, शून्य, prio_रेजिस्टरs, शून्य);

/*
 * Initialize IRQ setting
 */
व्योम __init init_se7721_IRQ(व्योम)
अणु
	/* PPCR */
	__raw_ग_लिखोw(__raw_पढ़ोw(0xa4050118) & ~0x00ff, 0xa4050118);

	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	पूर्णांकc_set_priority(MRSHPC_IRQ0, 0xf - MRSHPC_IRQ0);
पूर्ण
