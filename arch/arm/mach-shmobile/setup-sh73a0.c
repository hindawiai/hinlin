<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sh73a0 processor support
 *
 * Copyright (C) 2010  Takashi Yoshii
 * Copyright (C) 2010  Magnus Damm
 * Copyright (C) 2008  Yoshihiro Shimoda
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "common.h"
#समावेश "sh73a0.h"

अटल व्योम __init sh73a0_generic_init(व्योम)
अणु
#अगर_घोषित CONFIG_CACHE_L2X0
	/* Shared attribute override enable, 64K*8way */
	l2x0_init(ioremap(0xf0100000, PAGE_SIZE), 0x00400000, 0xc20f0fff);
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर *स्थिर sh73a0_boards_compat_dt[] __initस्थिर = अणु
	"renesas,sh73a0",
	शून्य,
पूर्ण;

DT_MACHINE_START(SH73A0_DT, "Generic SH73A0 (Flattened Device Tree)")
	.smp		= smp_ops(sh73a0_smp_ops),
	.init_machine	= sh73a0_generic_init,
	.init_late	= shmobile_init_late,
	.dt_compat	= sh73a0_boards_compat_dt,
MACHINE_END
