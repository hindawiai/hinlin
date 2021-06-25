<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip30-घातer.c: Software घातerकरोwn and reset handling क्रम IP30 architecture.
 *
 * Copyright (C) 2004-2007 Stanislaw Skowronek <skylark@unaligned.org>
 *               2014 Joshua Kinard <kumba@gentoo.org>
 *               2009 Johannes Dickgreber <tanzy@gmx.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtc/ds1685.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/sgi/heart.h>

अटल व्योम __noवापस ip30_machine_restart(अक्षर *cmd)
अणु
	/*
	 * Execute HEART cold reset
	 *   Yes, it's cold-HEARTed!
	 */
	heart_ग_लिखो((heart_पढ़ो(&heart_regs->mode) | HM_COLD_RST),
		    &heart_regs->mode);
	unreachable();
पूर्ण

अटल पूर्णांक __init ip30_reboot_setup(व्योम)
अणु
	_machine_restart = ip30_machine_restart;

	वापस 0;
पूर्ण

subsys_initcall(ip30_reboot_setup);
