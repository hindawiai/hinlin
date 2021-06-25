<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/reboot.h>

व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL(pm_घातer_off);

व्योम machine_घातer_off(व्योम)
अणु
	local_irq_disable();
	अगर (pm_घातer_off)
		pm_घातer_off();
	यंत्र अस्थिर ("bkpt");
पूर्ण

व्योम machine_halt(व्योम)
अणु
	local_irq_disable();
	अगर (pm_घातer_off)
		pm_घातer_off();
	यंत्र अस्थिर ("bkpt");
पूर्ण

व्योम machine_restart(अक्षर *cmd)
अणु
	local_irq_disable();
	करो_kernel_restart(cmd);
	यंत्र अस्थिर ("bkpt");
पूर्ण
