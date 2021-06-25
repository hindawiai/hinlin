<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Reset an IP27.
 *
 * Copyright (C) 1997, 1998, 1999, 2000, 06 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/smp.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/gda.h>

#समावेश "ip27-common.h"

व्योम machine_restart(अक्षर *command) __noवापस;
व्योम machine_halt(व्योम) __noवापस;
व्योम machine_घातer_off(व्योम) __noवापस;

#घोषणा noवापस जबतक(1);				/* Silence gcc.	 */

/* XXX How to pass the reboot command to the firmware??? */
अटल व्योम ip27_machine_restart(अक्षर *command)
अणु
#अगर 0
	पूर्णांक i;
#पूर्ण_अगर

	prपूर्णांकk("Reboot started from CPU %d\n", smp_processor_id());
#अगर_घोषित CONFIG_SMP
	smp_send_stop();
#पूर्ण_अगर
#अगर 0
	क्रम_each_online_node(i)
		REMOTE_HUB_S(i, PROMOP_REG, PROMOP_REBOOT);
#अन्यथा
	LOCAL_HUB_S(NI_PORT_RESET, NPR_PORTRESET | NPR_LOCALRESET);
#पूर्ण_अगर
	noवापस;
पूर्ण

अटल व्योम ip27_machine_halt(व्योम)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_SMP
	smp_send_stop();
#पूर्ण_अगर
	क्रम_each_online_node(i)
		REMOTE_HUB_S(i, PROMOP_REG, PROMOP_RESTART);
	LOCAL_HUB_S(NI_PORT_RESET, NPR_PORTRESET | NPR_LOCALRESET);
	noवापस;
पूर्ण

अटल व्योम ip27_machine_घातer_off(व्योम)
अणु
	/* To करो ...  */
	noवापस;
पूर्ण

व्योम ip27_reboot_setup(व्योम)
अणु
	_machine_restart = ip27_machine_restart;
	_machine_halt = ip27_machine_halt;
	pm_घातer_off = ip27_machine_घातer_off;
पूर्ण
