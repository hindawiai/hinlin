<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/kcmp.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <sys/types.h>
#समावेश <machine.h>
#समावेश <uapi/linux/kcmp.h>

#समावेश "trace/beauty/generated/kcmp_type_array.c"

माप_प्रकार syscall_arg__scnम_लिखो_kcmp_idx(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ fd = arg->val;
	पूर्णांक type = syscall_arg__val(arg, 2);
	pid_t pid;

	अगर (type != KCMP_खाता)
		वापस syscall_arg__scnम_लिखो_दीर्घ(bf, size, arg);

	pid = syscall_arg__val(arg, arg->idx == 3 ? 0 : 1); /* idx1 -> pid1, idx2 -> pid2 */
	वापस pid__scnम_लिखो_fd(arg->trace, pid, fd, bf, size);
पूर्ण

अटल माप_प्रकार kcmp__scnम_लिखो_type(पूर्णांक type, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	अटल DEFINE_STRARRAY(kcmp_types, "KCMP_");
	वापस strarray__scnम_लिखो(&strarray__kcmp_types, bf, size, "%d", show_prefix, type);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_kcmp_type(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ type = arg->val;

	अगर (type != KCMP_खाता)
		arg->mask |= (1 << 3) | (1 << 4); /* Ignore idx1 and idx2 */

	वापस kcmp__scnम_लिखो_type(type, bf, size, arg->show_string_prefix);
पूर्ण
