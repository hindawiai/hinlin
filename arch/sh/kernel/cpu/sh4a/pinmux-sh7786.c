<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7786 Pinmux
 *
 * Copyright (C) 2008, 2009  Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 *  Based on SH7785 pinmux
 *
 *  Copyright (C) 2008  Magnus Damm
 */

#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <cpu/pfc.h>

अटल काष्ठा resource sh7786_pfc_resources[] = अणु
	[0] = अणु
		.start	= 0xffcc0000,
		.end	= 0xffcc008f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init plat_pinmux_setup(व्योम)
अणु
	वापस sh_pfc_रेजिस्टर("pfc-sh7786", sh7786_pfc_resources,
			       ARRAY_SIZE(sh7786_pfc_resources));
पूर्ण
arch_initcall(plat_pinmux_setup);
