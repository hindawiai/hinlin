<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * am33xx-restart.c - Code common to all AM33xx machines.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>

#समावेश "common.h"
#समावेश "prm.h"

/**
 * am3xx_restart - trigger a software restart of the SoC
 * @mode: the "reboot mode", see arch/arm/kernel/अणुsetup,processपूर्ण.c
 * @cmd: passed from the userspace program rebooting the प्रणाली (अगर provided)
 *
 * Resets the SoC.  For @cmd, see the 'reboot' syscall in
 * kernel/sys.c.  No वापस value.
 */
व्योम am33xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/* TODO: Handle mode and cmd अगर necessary */

	omap_prm_reset_प्रणाली();
पूर्ण
