<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#समावेश <linux/reboot.h>
#समावेश <linux/pm.h>

अटल व्योम शेष_घातer_off(व्योम)
अणु
	जबतक (1)
		रुको_क्रम_पूर्णांकerrupt();
पूर्ण

व्योम (*pm_घातer_off)(व्योम) = शेष_घातer_off;
EXPORT_SYMBOL(pm_घातer_off);

व्योम machine_restart(अक्षर *cmd)
अणु
	करो_kernel_restart(cmd);
	जबतक (1);
पूर्ण

व्योम machine_halt(व्योम)
अणु
	pm_घातer_off();
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	pm_घातer_off();
पूर्ण
