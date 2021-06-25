<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_SIGNAL_H
#घोषणा __ASM_SH_SIGNAL_H

#घोषणा SA_RESTORER	0x04000000

#समावेश <यंत्र-generic/संकेत.स>

#अगर_अघोषित __KERNEL__
काष्ठा old_sigaction अणु
	__sighandler_t sa_handler;
	old_sigset_t sa_mask;
	अचिन्हित दीर्घ sa_flags;
	व्योम (*sa_restorer)(व्योम);
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_SIGNAL_H */
