<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <संकेत.स>
#समावेश <sched.h>
#समावेश <यंत्र/unistd.h>
#समावेश <sys/समय.स>
#समावेश <as-layout.h>
#समावेश <ptrace_user.h>
#समावेश <stub-data.h>
#समावेश <sysdep/stub.h>

/*
 * This is in a separate file because it needs to be compiled with any
 * extraneous gcc flags (-pg, -fprofile-arcs, -ftest-coverage) disabled
 *
 * Use UM_KERN_PAGE_SIZE instead of PAGE_SIZE because that calls getpagesize
 * on some प्रणालीs.
 */

व्योम __attribute__ ((__section__ (".__syscall_stub")))
stub_clone_handler(व्योम)
अणु
	पूर्णांक stack;
	काष्ठा stub_data *data = (व्योम *) ((अचिन्हित दीर्घ)&stack & ~(UM_KERN_PAGE_SIZE - 1));
	दीर्घ err;

	err = stub_syscall2(__NR_clone, CLONE_PARENT | CLONE_खाताS | SIGCHLD,
			    (अचिन्हित दीर्घ)data + UM_KERN_PAGE_SIZE / 2 - माप(व्योम *));
	अगर (err) अणु
		data->parent_err = err;
		जाओ करोne;
	पूर्ण

	err = stub_syscall4(__NR_ptrace, PTRACE_TRACEME, 0, 0, 0);
	अगर (err) अणु
		data->child_err = err;
		जाओ करोne;
	पूर्ण

	remap_stack_and_trap();

 करोne:
	trap_myself();
पूर्ण
