<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __IRQ_USER_H__
#घोषणा __IRQ_USER_H__

#समावेश <sysdep/ptrace.h>
#समावेश <stdbool.h>

क्रमागत um_irq_type अणु
	IRQ_READ,
	IRQ_WRITE,
	NUM_IRQ_TYPES,
पूर्ण;

काष्ठा siginfo;
बाह्य व्योम sigio_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs);
बाह्य व्योम मुक्त_irq_by_fd(पूर्णांक fd);
बाह्य व्योम deactivate_fd(पूर्णांक fd, पूर्णांक irqnum);
बाह्य पूर्णांक deactivate_all_fds(व्योम);
बाह्य पूर्णांक activate_ipi(पूर्णांक fd, पूर्णांक pid);

#पूर्ण_अगर
