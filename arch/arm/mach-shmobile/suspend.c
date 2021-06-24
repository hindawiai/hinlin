<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Suspend-to-RAM support code क्रम SH-Mobile ARM
 *
 *  Copyright (C) 2011 Magnus Damm
 */

#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "common.h"

अटल पूर्णांक shmobile_suspend_शेष_enter(suspend_state_t suspend_state)
अणु
	cpu_करो_idle();
	वापस 0;
पूर्ण

अटल पूर्णांक shmobile_suspend_begin(suspend_state_t state)
अणु
	cpu_idle_poll_ctrl(true);
	वापस 0;
पूर्ण

अटल व्योम shmobile_suspend_end(व्योम)
अणु
	cpu_idle_poll_ctrl(false);
पूर्ण

काष्ठा platक्रमm_suspend_ops shmobile_suspend_ops = अणु
	.begin		= shmobile_suspend_begin,
	.end		= shmobile_suspend_end,
	.enter		= shmobile_suspend_शेष_enter,
	.valid		= suspend_valid_only_mem,
पूर्ण;

पूर्णांक __init shmobile_suspend_init(व्योम)
अणु
	suspend_set_ops(&shmobile_suspend_ops);
	वापस 0;
पूर्ण
