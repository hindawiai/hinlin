<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * misc.c:  Miscellaneous prom functions that करोn't beदीर्घ
 *          anywhere अन्यथा.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/sun3-head.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/movs.h>

/* Reset and reboot the machine with the command 'bcommand'. */
व्योम
prom_reboot(अक्षर *bcommand)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	(*(romvec->pv_reboot))(bcommand);
	local_irq_restore(flags);
पूर्ण

/* Drop पूर्णांकo the prom, with the chance to जारी with the 'go'
 * prom command.
 */
व्योम
prom_cmdline(व्योम)
अणु
पूर्ण

/* Drop पूर्णांकo the prom, but completely terminate the program.
 * No chance of continuing.
 */
व्योम
prom_halt(व्योम)
अणु
	अचिन्हित दीर्घ flags;
again:
	local_irq_save(flags);
	(*(romvec->pv_halt))();
	local_irq_restore(flags);
	जाओ again; /* PROM is out to get me -DaveM */
पूर्ण

प्रकार व्योम (*sfunc_t)(व्योम);

/* Get the idprom and stuff it पूर्णांकo buffer 'idbuf'.  Returns the
 * क्रमmat type.  'num_bytes' is the number of bytes that your idbuf
 * has space क्रम.  Returns 0xff on error.
 */
अचिन्हित अक्षर
prom_get_idprom(अक्षर *idbuf, पूर्णांक num_bytes)
अणु
	पूर्णांक i, oldsfc;
	GET_SFC(oldsfc);
	SET_SFC(FC_CONTROL);
	क्रम(i=0;i<num_bytes; i++)
	अणु
		/* There is a problem with the GET_CONTROL_BYTE
		macro; defining the extra variable
		माला_लो around it.
		*/
		पूर्णांक c;
		GET_CONTROL_BYTE(SUN3_IDPROM_BASE + i, c);
		idbuf[i] = c;
	पूर्ण
	SET_SFC(oldsfc);
	वापस idbuf[0];
पूर्ण

/* Get the major prom version number. */
पूर्णांक
prom_version(व्योम)
अणु
	वापस romvec->pv_romvers;
पूर्ण

/* Get the prom plugin-revision. */
पूर्णांक
prom_getrev(व्योम)
अणु
	वापस prom_rev;
पूर्ण

/* Get the prom firmware prपूर्णांक revision. */
पूर्णांक
prom_getprev(व्योम)
अणु
	वापस prom_prev;
पूर्ण
