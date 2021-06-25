<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/reboot.h>
#समावेश <linux/pm.h>

व्योम machine_halt(व्योम)
अणु
	/* Halt the processor */
	__यंत्र__ __अस्थिर__("flag  1\n");
पूर्ण

व्योम machine_restart(अक्षर *__unused)
अणु
	/* Soft reset : jump to reset vector */
	pr_info("Put your restart handler here\n");
	machine_halt();
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	/* FIXME ::  घातer off ??? */
	machine_halt();
पूर्ण

व्योम (*pm_घातer_off) (व्योम) = शून्य;
EXPORT_SYMBOL(pm_घातer_off);
