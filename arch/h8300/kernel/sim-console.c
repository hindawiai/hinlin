<शैली गुरु>
/*
 * arch/h8300/kernel/sim-console.c
 *
 *  Copyright (C) 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>

अटल व्योम sim_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	रेजिस्टर स्थिर अक्षर *_ptr __यंत्र__("er1") = s;
	रेजिस्टर स्थिर अचिन्हित _len __यंत्र__("er2") = n;

	__यंत्र__("sub.l er0,er0\n\t"		/* er0 = 1 (मानक_निकास) */
		"inc.l #1,er0\n\t"
		".byte 0x5e,0x00,0x00,0xc7\n\t" /* jsr @0xc7 (sys_ग_लिखो) */
		: : "g"(_ptr), "g"(_len):"er0");
पूर्ण

अटल पूर्णांक __init sim_setup(काष्ठा earlycon_device *device, स्थिर अक्षर *opt)
अणु
	device->con->ग_लिखो = sim_ग_लिखो;
	वापस 0;
पूर्ण

EARLYCON_DECLARE(h8sim, sim_setup);
