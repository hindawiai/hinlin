<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_KDEBUG_H
#घोषणा __ASM_SH_KDEBUG_H

/* Grossly misnamed. */
क्रमागत die_val अणु
	DIE_TRAP,
	DIE_NMI,
	DIE_OOPS,
	DIE_BREAKPOINT,
	DIE_SSTEP,
पूर्ण;

/* arch/sh/kernel/dumpstack.c */
बाह्य व्योम prपूर्णांकk_address(अचिन्हित दीर्घ address, पूर्णांक reliable);
बाह्य व्योम dump_mem(स्थिर अक्षर *str, स्थिर अक्षर *loglvl,
		     अचिन्हित दीर्घ bottom, अचिन्हित दीर्घ top);

#पूर्ण_अगर /* __ASM_SH_KDEBUG_H */
