<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap4-restart.c - Common to OMAP4 and OMAP5
 */

#समावेश <linux/types.h>
#समावेश <linux/reboot.h>
#समावेश "common.h"
#समावेश "prm.h"

/**
 * omap44xx_restart - trigger a software restart of the SoC
 * @mode: the "reboot mode", see arch/arm/kernel/अणुsetup,processपूर्ण.c
 * @cmd: passed from the userspace program rebooting the प्रणाली (अगर provided)
 *
 * Resets the SoC.  For @cmd, see the 'reboot' syscall in
 * kernel/sys.c.  No वापस value.
 */
व्योम omap44xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/* XXX Should save 'cmd' पूर्णांकo scratchpad क्रम use after reboot */
	omap_prm_reset_प्रणाली();
पूर्ण
