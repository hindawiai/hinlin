<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap3-restart.c - Code common to all OMAP3xxx machines.
 *
 * Copyright (C) 2009, 2012 Texas Instruments
 * Copyright (C) 2010 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 * Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>

#समावेश "common.h"
#समावेश "control.h"
#समावेश "prm.h"

/* Global address base setup code */

/**
 * omap3xxx_restart - trigger a software restart of the SoC
 * @mode: the "reboot mode", see arch/arm/kernel/अणुsetup,processपूर्ण.c
 * @cmd: passed from the userspace program rebooting the प्रणाली (अगर provided)
 *
 * Resets the SoC.  For @cmd, see the 'reboot' syscall in
 * kernel/sys.c.  No वापस value.
 */
व्योम omap3xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	omap3_ctrl_ग_लिखो_boot_mode((cmd ? (u8)*cmd : 0));
	omap_prm_reset_प्रणाली();
पूर्ण
