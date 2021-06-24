<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASMPARISC_SIGCONTEXT_H
#घोषणा _ASMPARISC_SIGCONTEXT_H

#घोषणा PARISC_SC_FLAG_ONSTACK 1<<0
#घोषणा PARISC_SC_FLAG_IN_SYSCALL 1<<1

/* We will add more stuff here as it becomes necessary, until we know
   it works. */
काष्ठा sigcontext अणु
	अचिन्हित दीर्घ sc_flags;

	अचिन्हित दीर्घ sc_gr[32]; /* PSW in sc_gr[0] */
	अचिन्हित दीर्घ दीर्घ sc_fr[32]; /* FIXME, करो we need other state info? */
	अचिन्हित दीर्घ sc_iasq[2];
	अचिन्हित दीर्घ sc_iaoq[2];
	अचिन्हित दीर्घ sc_sar; /* cr11 */
पूर्ण;


#पूर्ण_अगर
