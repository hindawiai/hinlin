<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH-X3 prototype CPU pinmux
 *
 * Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <cpu/pfc.h>

अटल काष्ठा resource shx3_pfc_resources[] = अणु
	[0] = अणु
		.start	= 0xffc70000,
		.end	= 0xffc7001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init plat_pinmux_setup(व्योम)
अणु
	वापस sh_pfc_रेजिस्टर("pfc-shx3", shx3_pfc_resources,
			       ARRAY_SIZE(shx3_pfc_resources));
पूर्ण
arch_initcall(plat_pinmux_setup);
