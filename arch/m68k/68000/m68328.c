<शैली गुरु>
/***************************************************************************/

/*
 *  m68328.c - 68328/68EZ328/68VZ328 specअगरic config
 *
 *  Copyright (C) 1993 Hamish Macकरोnald
 *  Copyright (C) 1999 D. Jeff Dionne
 *  Copyright (C) 2001 Georges Menie, Ken Desmet
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * VZ Support/Fixes             Evan Stawnyczy <e@lineo.ca>
 */

/***************************************************************************/

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rtc.h>
#समावेश <यंत्र/machdep.h>

#अगर defined(CONFIG_INIT_LCD) && defined(CONFIG_M68VZ328)
#समावेश "bootlogo-vz.h"
#या_अगर defined(CONFIG_PILOT) || defined(CONFIG_INIT_LCD)
#समावेश "bootlogo.h"
#पूर्ण_अगर

#समावेश "m68328.h"

/***************************************************************************/

अटल व्योम m68328_reset(व्योम)
अणु
  local_irq_disable();
  यंत्र अस्थिर ("moveal #0x10c00000, %a0;\n\t"
		"moveb #0, 0xFFFFF300;\n\t"
		"moveal 0(%a0), %sp;\n\t"
		"moveal 4(%a0), %a0;\n\t"
		"jmp (%a0);");
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *command, पूर्णांक len)
अणु
	mach_sched_init = hw_समयr_init;
	mach_hwclk = m68328_hwclk;
	mach_reset = m68328_reset;

#अगर   defined(CONFIG_PILOT) && defined(CONFIG_M68328)
	mach_sched_init = शून्य;
#या_अगर defined(CONFIG_UCSIMM)
	init_ucsimm(command, len);
#या_अगर defined(CONFIG_UCDIMM)
	init_ucsimm(command, len);
#या_अगर defined(CONFIG_DRAGEN2)
	init_dragen2(command, len);
#पूर्ण_अगर
पूर्ण

/***************************************************************************/
