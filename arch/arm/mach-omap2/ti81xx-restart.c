<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "control.h"
#समावेश "prm3xxx.h"

#घोषणा TI81XX_PRM_DEVICE_RSTCTRL	0x00a0
#घोषणा TI81XX_GLOBAL_RST_COLD		BIT(1)

/**
 * ti81xx_restart - trigger a software restart of the SoC
 * @mode: the "reboot mode", see arch/arm/kernel/अणुsetup,processपूर्ण.c
 * @cmd: passed from the userspace program rebooting the प्रणाली (अगर provided)
 *
 * Resets the SoC.  For @cmd, see the 'reboot' syscall in
 * kernel/sys.c.  No वापस value.
 *
 * NOTE: Warm reset करोes not seem to work, may require resetting
 * घड़ीs to bypass mode.
 */
व्योम ti81xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	omap2_prm_set_mod_reg_bits(TI81XX_GLOBAL_RST_COLD, 0,
				   TI81XX_PRM_DEVICE_RSTCTRL);
	जबतक (1);
पूर्ण
