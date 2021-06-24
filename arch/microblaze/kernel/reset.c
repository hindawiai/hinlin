<शैली गुरु>
/*
 * Copyright (C) 2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2009 PetaLogix
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reboot.h>

व्योम machine_shutकरोwn(व्योम)
अणु
	pr_notice("Machine shutdown...\n");
	जबतक (1)
		;
पूर्ण

व्योम machine_halt(व्योम)
अणु
	pr_notice("Machine halt...\n");
	जबतक (1)
		;
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	pr_notice("Machine power off...\n");
	जबतक (1)
		;
पूर्ण

व्योम machine_restart(अक्षर *cmd)
अणु
	करो_kernel_restart(cmd);
	/* Give the restart hook 1 s to take us करोwn */
	mdelay(1000);
	pr_emerg("Reboot failed -- System halted\n");
	जबतक (1);
पूर्ण
