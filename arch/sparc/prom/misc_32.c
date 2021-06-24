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
#समावेश <linux/module.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/auxपन.स>

बाह्य व्योम restore_current(व्योम);

DEFINE_SPINLOCK(prom_lock);

/* Reset and reboot the machine with the command 'bcommand'. */
व्योम
prom_reboot(अक्षर *bcommand)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&prom_lock, flags);
	(*(romvec->pv_reboot))(bcommand);
	/* Never get here. */
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
पूर्ण

/* Forth evaluate the expression contained in 'fstring'. */
व्योम
prom_feval(अक्षर *fstring)
अणु
	अचिन्हित दीर्घ flags;
	अगर(!fstring || fstring[0] == 0)
		वापस;
	spin_lock_irqsave(&prom_lock, flags);
	अगर(prom_vers == PROM_V0)
		(*(romvec->pv_क्रमtheval.v0_eval))(म_माप(fstring), fstring);
	अन्यथा
		(*(romvec->pv_क्रमtheval.v2_eval))(fstring);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
पूर्ण
EXPORT_SYMBOL(prom_feval);

/* Drop पूर्णांकo the prom, with the chance to जारी with the 'go'
 * prom command.
 */
व्योम
prom_cmdline(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prom_lock, flags);
	(*(romvec->pv_पात))();
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	set_auxio(AUXIO_LED, 0);
पूर्ण

/* Drop पूर्णांकo the prom, but completely terminate the program.
 * No chance of continuing.
 */
व्योम __noवापस
prom_halt(व्योम)
अणु
	अचिन्हित दीर्घ flags;
again:
	spin_lock_irqsave(&prom_lock, flags);
	(*(romvec->pv_halt))();
	/* Never get here. */
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	जाओ again; /* PROM is out to get me -DaveM */
पूर्ण

प्रकार व्योम (*sfunc_t)(व्योम);

/* Set prom sync handler to call function 'funcp'. */
व्योम
prom_setsync(sfunc_t funcp)
अणु
	अगर(!funcp) वापस;
	*romvec->pv_synchook = funcp;
पूर्ण

/* Get the idprom and stuff it पूर्णांकo buffer 'idbuf'.  Returns the
 * क्रमmat type.  'num_bytes' is the number of bytes that your idbuf
 * has space क्रम.  Returns 0xff on error.
 */
अचिन्हित अक्षर
prom_get_idprom(अक्षर *idbuf, पूर्णांक num_bytes)
अणु
	पूर्णांक len;

	len = prom_getproplen(prom_root_node, "idprom");
	अगर((len>num_bytes) || (len==-1)) वापस 0xff;
	अगर(!prom_getproperty(prom_root_node, "idprom", idbuf, num_bytes))
		वापस idbuf[0];

	वापस 0xff;
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
