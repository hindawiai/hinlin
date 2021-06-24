<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* reboot.c: reboot/shutकरोwn/halt/घातeroff handling
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/setup.h>

/* sysctl - toggle घातer-off restriction क्रम serial console
 * प्रणालीs in machine_घातer_off()
 */
पूर्णांक scons_pwroff = 1;

/* This isn't actually used, it exists merely to satisfy the
 * reference in kernel/sys.c
 */
व्योम (*pm_घातer_off)(व्योम) = machine_घातer_off;
EXPORT_SYMBOL(pm_घातer_off);

व्योम machine_घातer_off(व्योम)
अणु
	अगर (!of_node_is_type(of_console_device, "serial") || scons_pwroff)
		prom_halt_घातer_off();

	prom_halt();
पूर्ण

व्योम machine_halt(व्योम)
अणु
	prom_halt();
	panic("Halt failed!");
पूर्ण

व्योम machine_restart(अक्षर *cmd)
अणु
	अक्षर *p;

	p = म_अक्षर(reboot_command, '\n');
	अगर (p)
		*p = 0;
	अगर (cmd)
		prom_reboot(cmd);
	अगर (*reboot_command)
		prom_reboot(reboot_command);
	prom_reboot("");
	panic("Reboot failed!");
पूर्ण

