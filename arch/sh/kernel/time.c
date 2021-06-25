<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  arch/sh/kernel/समय.c
 *
 *  Copyright (C) 1999  Tetsuya Okada & Niibe Yutaka
 *  Copyright (C) 2000  Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 2002 - 2009  Paul Mundt
 *  Copyright (C) 2002  M. R. Brown  <mrbrown@linux-sh.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/profile.h>
#समावेश <linux/समयx.h>
#समावेश <linux/sched.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smp.h>
#समावेश <linux/rtc.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/rtc.h>
#समावेश <यंत्र/platक्रमm_early.h>

अटल व्योम __init sh_late_समय_init(व्योम)
अणु
	/*
	 * Make sure all compiled-in early समयrs रेजिस्टर themselves.
	 *
	 * Run probe() क्रम two "earlytimer" devices, these will be the
	 * घड़ीevents and घड़ीsource devices respectively. In the event
	 * that only a घड़ीevents device is available, we -ENODEV on the
	 * घड़ीsource and the jअगरfies घड़ीsource is used transparently
	 * instead. No error handling is necessary here.
	 */
	sh_early_platक्रमm_driver_रेजिस्टर_all("earlytimer");
	sh_early_platक्रमm_driver_probe("earlytimer", 2, 0);
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	समयr_probe();

	clk_init();

	late_समय_init = sh_late_समय_init;
पूर्ण
