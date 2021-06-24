<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7269 Pinmux
 *
 * Copyright (C) 2012  Renesas Electronics Europe Ltd
 * Copyright (C) 2012  Phil Edworthy
 */

#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <cpu/pfc.h>

अटल काष्ठा resource sh7269_pfc_resources[] = अणु
	[0] = अणु
		.start	= 0xfffe3800,
		.end	= 0xfffe391f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init plat_pinmux_setup(व्योम)
अणु
	वापस sh_pfc_रेजिस्टर("pfc-sh7269", sh7269_pfc_resources,
			       ARRAY_SIZE(sh7269_pfc_resources));
पूर्ण
arch_initcall(plat_pinmux_setup);
