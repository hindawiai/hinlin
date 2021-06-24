<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/cone.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <sys/types.h>
#समावेश <uapi/linux/sched.h>

अटल माप_प्रकार clone__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	स्थिर अक्षर *prefix = "CLONE_";
	पूर्णांक prपूर्णांकed = 0;

#घोषणा	P_FLAG(n) \
	अगर (flags & CLONE_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~CLONE_##n; \
	पूर्ण

	P_FLAG(VM);
	P_FLAG(FS);
	P_FLAG(खाताS);
	P_FLAG(SIGHAND);
	P_FLAG(PIDFD);
	P_FLAG(PTRACE);
	P_FLAG(VFORK);
	P_FLAG(PARENT);
	P_FLAG(THREAD);
	P_FLAG(NEWNS);
	P_FLAG(SYSVSEM);
	P_FLAG(SETTLS);
	P_FLAG(PARENT_SETTID);
	P_FLAG(CHILD_CLEARTID);
	P_FLAG(DETACHED);
	P_FLAG(UNTRACED);
	P_FLAG(CHILD_SETTID);
	P_FLAG(NEWCGROUP);
	P_FLAG(NEWUTS);
	P_FLAG(NEWIPC);
	P_FLAG(NEWUSER);
	P_FLAG(NEWPID);
	P_FLAG(NEWNET);
	P_FLAG(IO);
	P_FLAG(CLEAR_SIGHAND);
	P_FLAG(INTO_CGROUP);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_clone_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;
	क्रमागत syscall_clone_args अणु
		SCC_FLAGS	  = (1 << 0),
		SCC_CHILD_STACK	  = (1 << 1),
		SCC_PARENT_TIDPTR = (1 << 2),
		SCC_CHILD_TIDPTR  = (1 << 3),
		SCC_TLS		  = (1 << 4),
	पूर्ण;
	अगर (!(flags & CLONE_PARENT_SETTID))
		arg->mask |= SCC_PARENT_TIDPTR;

	अगर (!(flags & (CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID)))
		arg->mask |= SCC_CHILD_TIDPTR;

	अगर (!(flags & CLONE_SETTLS))
		arg->mask |= SCC_TLS;

	वापस clone__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
