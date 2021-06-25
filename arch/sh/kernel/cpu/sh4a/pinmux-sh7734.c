<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7734 processor support - PFC hardware block
 *
 * Copyright (C) 2012  Renesas Solutions Corp.
 * Copyright (C) 2012  Nobuhiro Iwamatsu <nobuhiro.iwamatsu.yj@renesas.com>
 */
#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <cpu/pfc.h>

अटल काष्ठा resource sh7734_pfc_resources[] = अणु
	[0] = अणु /* PFC */
		.start	= 0xFFFC0000,
		.end	= 0xFFFC011C,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु /* GPIO */
		.start	= 0xFFC40000,
		.end	= 0xFFC4502B,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init plat_pinmux_setup(व्योम)
अणु
	वापस sh_pfc_रेजिस्टर("pfc-sh7734", sh7734_pfc_resources,
			       ARRAY_SIZE(sh7734_pfc_resources));
पूर्ण
arch_initcall(plat_pinmux_setup);
