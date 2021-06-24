<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace-abi.h>

व्योम clear_flushed_tls(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

पूर्णांक arch_set_tls(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ tls)
अणु
	/*
	 * If CLONE_SETTLS is set, we need to save the thपढ़ो id
	 * so it can be set during context चयनes.
	 */
	t->thपढ़ो.arch.fs = tls;

	वापस 0;
पूर्ण
