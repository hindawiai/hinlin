<शैली गुरु>
/*
 * reset.c  -- common ColdFire SoC reset support
 *
 * (C) Copyright 2012, Greg Ungerer <gerg@uclinux.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>

/*
 *	There are 2 common methods amongst the ColdFure parts क्रम reseting
 *	the CPU. But there are couple of exceptions, the 5272 and the 547x
 *	have something completely special to them, and we let their specअगरic
 *	subarch code handle them.
 */

#अगर_घोषित MCFSIM_SYPCR
अटल व्योम mcf_cpu_reset(व्योम)
अणु
	local_irq_disable();
	/* Set watchकरोg to soft reset, and enabled */
	__raw_ग_लिखोb(0xc0, MCFSIM_SYPCR);
	क्रम (;;)
		/* रुको क्रम watchकरोg to समयout */;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित MCF_RCR
अटल व्योम mcf_cpu_reset(व्योम)
अणु
	local_irq_disable();
	__raw_ग_लिखोb(MCF_RCR_SWRESET, MCF_RCR);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mcf_setup_reset(व्योम)
अणु
	mach_reset = mcf_cpu_reset;
	वापस 0;
पूर्ण

arch_initcall(mcf_setup_reset);
