<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * kdebug.h:  Defines and definitions क्रम debugging the Linux kernel
 *            under various kernel debuggers.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित _SPARC_KDEBUG_H
#घोषणा _SPARC_KDEBUG_H

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/vaddrs.h>

/* Breakpoपूर्णांकs are enter through trap table entry 126.  So in sparc assembly
 * अगर you want to drop पूर्णांकo the debugger you करो:
 *
 * t DEBUG_BP_TRAP
 */

#घोषणा DEBUG_BP_TRAP     126

#अगर_अघोषित __ASSEMBLY__
/* The debug vector is passed in %o1 at boot समय.  It is a poपूर्णांकer to
 * a काष्ठाure in the debuggers address space.  Here is its क्रमmat.
 */

प्रकार अचिन्हित पूर्णांक (*debugger_funct)(व्योम);

काष्ठा kernel_debug अणु
	/* First the entry poपूर्णांक पूर्णांकo the debugger.  You jump here
	 * to give control over to the debugger.
	 */
	अचिन्हित दीर्घ kdebug_entry;
	अचिन्हित दीर्घ kdebug_trapme;   /* Figure out later... */
	/* The following is the number of pages that the debugger has
	 * taken from to total pool.
	 */
	अचिन्हित दीर्घ *kdebug_stolen_pages;
	/* Ok, after you remap yourself and/or change the trap table
	 * from what you were left with at boot समय you have to call
	 * this synchronization function so the debugger can check out
	 * what you have करोne.
	 */
	debugger_funct teach_debugger;
पूर्ण; /* I think that is it... */

बाह्य काष्ठा kernel_debug *linux_dbvec;

/* Use this macro in C-code to enter the debugger. */
अटल अंतरभूत व्योम sp_enter_debugger(व्योम)
अणु
	__यंत्र__ __अस्थिर__("jmpl %0, %%o7\n\t"
			     "nop\n\t" : :
			     "r" (linux_dbvec) : "o7", "memory");
पूर्ण

#घोषणा SP_ENTER_DEBUGGER करो अणु \
	     अगर((linux_dbvec!=0) && ((*(लघु *)linux_dbvec)!=-1)) \
	       sp_enter_debugger(); \
		       पूर्ण जबतक(0)

क्रमागत die_val अणु
	DIE_UNUSED,
	DIE_OOPS,
पूर्ण;

#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* Some nice offset defines क्रम assembler code. */
#घोषणा KDEBUG_ENTRY_OFF    0x0
#घोषणा KDEBUG_DUNNO_OFF    0x4
#घोषणा KDEBUG_DUNNO2_OFF   0x8
#घोषणा KDEBUG_TEACH_OFF    0xc

#पूर्ण_अगर /* !(_SPARC_KDEBUG_H) */
