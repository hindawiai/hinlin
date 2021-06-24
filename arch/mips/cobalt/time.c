<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Cobalt समय initialization.
 *
 *  Copyright (C) 2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/i8253.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/gt64120.h>
#समावेश <यंत्र/समय.स>

#घोषणा GT641XX_BASE_CLOCK	50000000	/* 50MHz */

व्योम __init plat_समय_init(व्योम)
अणु
	u32 start, end;
	पूर्णांक i = HZ / 10;

	setup_pit_समयr();

	gt641xx_set_base_घड़ी(GT641XX_BASE_CLOCK);

	/*
	 * MIPS counter frequency is measured during a 100msec पूर्णांकerval
	 * using GT64111 समयr0.
	 */
	जबतक (!gt641xx_समयr0_state())
		;

	start = पढ़ो_c0_count();

	जबतक (i--)
		जबतक (!gt641xx_समयr0_state())
			;

	end = पढ़ो_c0_count();

	mips_hpt_frequency = (end - start) * 10;
	prपूर्णांकk(KERN_INFO "MIPS counter frequency %dHz\n", mips_hpt_frequency);
पूर्ण
