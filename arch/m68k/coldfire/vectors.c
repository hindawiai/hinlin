<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	vectors.c  -- high level trap setup क्रम ColdFire
 *
 *	Copyright (C) 1999-2007, Greg Ungerer <gerg@snapgear.com>
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfwdebug.h>

/***************************************************************************/

#अगर_घोषित TRAP_DBG_INTERRUPT

यंत्रlinkage व्योम dbgपूर्णांकerrupt_c(काष्ठा frame *fp)
अणु
	बाह्य व्योम dump(काष्ठा pt_regs *fp);
	prपूर्णांकk(KERN_DEBUG "%s(%d): BUS ERROR TRAP\n", __खाता__, __LINE__);
	dump((काष्ठा pt_regs *) fp);
	यंत्र("halt");
पूर्ण

#पूर्ण_अगर

/***************************************************************************/

/* Assembler routines */
यंत्रlinkage व्योम buserr(व्योम);
यंत्रlinkage व्योम trap(व्योम);
यंत्रlinkage व्योम प्रणाली_call(व्योम);
यंत्रlinkage व्योम पूर्णांकhandler(व्योम);

व्योम __init trap_init(व्योम)
अणु
	पूर्णांक i;

	/*
	 *	There is a common trap handler and common पूर्णांकerrupt
	 *	handler that handle almost every vector. We treat
	 *	the प्रणाली call and bus error special, they get their
	 *	own first level handlers.
	 */
	क्रम (i = 3; (i <= 23); i++)
		_ramvec[i] = trap;
	क्रम (i = 33; (i <= 63); i++)
		_ramvec[i] = trap;
	क्रम (i = 24; (i <= 31); i++)
		_ramvec[i] = पूर्णांकhandler;
	क्रम (i = 64; (i < 255); i++)
		_ramvec[i] = पूर्णांकhandler;
	_ramvec[255] = 0;

	_ramvec[2] = buserr;
	_ramvec[32] = प्रणाली_call;

#अगर_घोषित TRAP_DBG_INTERRUPT
	_ramvec[12] = dbgपूर्णांकerrupt;
#पूर्ण_अगर
पूर्ण

/***************************************************************************/
