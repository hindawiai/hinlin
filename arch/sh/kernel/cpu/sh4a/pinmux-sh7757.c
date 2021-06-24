<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7757 (B0 step) Pinmux
 *
 *  Copyright (C) 2009-2010  Renesas Solutions Corp.
 *
 *  Author : Yoshihiro Shimoda <shimoda.yoshihiro@renesas.com>
 *
 * Based on SH7723 Pinmux
 *  Copyright (C) 2008  Magnus Damm
 */

#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <cpu/pfc.h>

अटल काष्ठा resource sh7757_pfc_resources[] = अणु
	[0] = अणु
		.start	= 0xffec0000,
		.end	= 0xffec008f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init plat_pinmux_setup(व्योम)
अणु
	वापस sh_pfc_रेजिस्टर("pfc-sh7757", sh7757_pfc_resources,
			       ARRAY_SIZE(sh7757_pfc_resources));
पूर्ण
arch_initcall(plat_pinmux_setup);
