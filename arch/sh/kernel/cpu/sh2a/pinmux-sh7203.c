<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7203 Pinmux
 *
 *  Copyright (C) 2008  Magnus Damm
 */

#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <cpu/pfc.h>

अटल काष्ठा resource sh7203_pfc_resources[] = अणु
	[0] = अणु
		.start	= 0xfffe3800,
		.end	= 0xfffe3a9f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init plat_pinmux_setup(व्योम)
अणु
	वापस sh_pfc_रेजिस्टर("pfc-sh7203", sh7203_pfc_resources,
			       ARRAY_SIZE(sh7203_pfc_resources));
पूर्ण
arch_initcall(plat_pinmux_setup);
