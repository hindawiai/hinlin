<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011 Calxeda, Inc.
 */
#समावेश <linux/पन.स>
#समावेश <यंत्र/proc-fns.h>
#समावेश <linux/reboot.h>

#समावेश "core.h"
#समावेश "sysregs.h"

व्योम highbank_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (mode == REBOOT_HARD)
		highbank_set_pwr_hard_reset();
	अन्यथा
		highbank_set_pwr_soft_reset();

	जबतक (1)
		cpu_करो_idle();
पूर्ण

