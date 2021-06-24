<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/dreamcast/setup.c
 *
 * Hardware support क्रम the Sega Dreamcast.
 *
 * Copyright (c) 2001, 2002 M. R. Brown <mrbrown@linuxdc.org>
 * Copyright (c) 2002, 2003, 2004 Paul Mundt <lethal@linux-sh.org>
 *
 * This file is part of the LinuxDC project (www.linuxdc.org)
 *
 * This file originally bore the message (with enबंदd-$):
 *	Id: setup_dc.c,v 1.5 2001/05/24 05:09:16 mrbrown Exp
 *	SEGA Dreamcast support
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/rtc.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach/sysasic.h>

अटल व्योम __init dreamcast_setup(अक्षर **cmdline_p)
अणु
पूर्ण

अटल काष्ठा sh_machine_vector mv_dreamcast __iniपंचांगv = अणु
	.mv_name		= "Sega Dreamcast",
	.mv_setup		= dreamcast_setup,
	.mv_irq_demux		= प्रणालीasic_irq_demux,
	.mv_init_irq		= प्रणालीasic_irq_init,
पूर्ण;
