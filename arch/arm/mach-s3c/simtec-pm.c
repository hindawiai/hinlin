<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2004 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://armlinux.simtec.co.uk/
//
// Power Management helpers क्रम Simtec S3C24XX implementations

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "map.h"
#समावेश "regs-gpio.h"

#समावेश <यंत्र/mach-types.h>

#समावेश "pm.h"

#समावेश "regs-mem-s3c24xx.h"

#घोषणा COPYRIGHT ", Copyright 2005 Simtec Electronics"

/* pm_simtec_init
 *
 * enable the घातer management functions
*/

अटल __init पूर्णांक pm_simtec_init(व्योम)
अणु
	अचिन्हित दीर्घ gstatus4;

	/* check which machine we are running on */

	अगर (!machine_is_bast() && !machine_is_vr1000() &&
	    !machine_is_anubis() && !machine_is_osiris() &&
	    !machine_is_aml_m5900())
		वापस 0;

	prपूर्णांकk(KERN_INFO "Simtec Board Power Management" COPYRIGHT "\n");

	gstatus4  = (__raw_पढ़ोl(S3C2410_BANKCON7) & 0x3) << 30;
	gstatus4 |= (__raw_पढ़ोl(S3C2410_BANKCON6) & 0x3) << 28;
	gstatus4 |= (__raw_पढ़ोl(S3C2410_BANKSIZE) & S3C2410_BANKSIZE_MASK);

	__raw_ग_लिखोl(gstatus4, S3C2410_GSTATUS4);

	वापस s3c_pm_init();
पूर्ण

arch_initcall(pm_simtec_init);
