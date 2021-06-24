<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#समावेश "system.h"
#समावेश "signal.h"

पूर्णांक sigemptyset(sigset_t *s)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < _NSIG_WORDS; ++i)
		s->sig[i] = 0;

	वापस 0;
पूर्ण

पूर्णांक sigaddset(sigset_t *s, पूर्णांक n)
अणु
	अगर (n < 1 || n > _NSIG)
		वापस -EINVAL;

	s->sig[(n - 1) / _NSIG_BPW] |= 1UL << (n - 1) % _NSIG_BPW;
	वापस 0;
पूर्ण

पूर्णांक sigaction(पूर्णांक n, काष्ठा sigaction *sa, स्थिर काष्ठा sigaction *old)
अणु
	वापस syscall(__NR_rt_sigaction, n, sa, old, माप(sa->sa_mask));
पूर्ण

पूर्णांक sigprocmask(पूर्णांक how, स्थिर sigset_t *mask, sigset_t *old)
अणु
	वापस syscall(__NR_rt_sigprocmask, how, mask, old, माप(*mask));
पूर्ण
