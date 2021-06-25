<शैली गुरु>
/*
 * arch/arm/plat-spear/restart.c
 *
 * SPEAr platक्रमm specअगरic restart functions
 *
 * Copyright (C) 2009 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/पन.स>
#समावेश <linux/amba/sp810.h>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <mach/spear.h>
#समावेश "generic.h"

#घोषणा SPEAR13XX_SYS_SW_RES			(VA_MISC_BASE + 0x204)
व्योम spear_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (mode == REBOOT_SOFT) अणु
		/* software reset, Jump पूर्णांकo ROM at address 0 */
		soft_restart(0);
	पूर्ण अन्यथा अणु
		/* hardware reset, Use on-chip reset capability */
#अगर_घोषित CONFIG_ARCH_SPEAR13XX
		ग_लिखोl_relaxed(0x01, SPEAR13XX_SYS_SW_RES);
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_SPEAR3XX) || defined(CONFIG_ARCH_SPEAR6XX)
		sysctl_soft_reset((व्योम __iomem *)VA_SPEAR_SYS_CTRL_BASE);
#पूर्ण_अगर
	पूर्ण
पूर्ण
