<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/arch_prctl.c
 *
 *  Copyright (C) 2018, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>

#समावेश "trace/beauty/generated/x86_arch_prctl_code_array.c"

अटल DEFINE_STRARRAY_OFFSET(x86_arch_prctl_codes_1, "ARCH_", x86_arch_prctl_codes_1_offset);
अटल DEFINE_STRARRAY_OFFSET(x86_arch_prctl_codes_2, "ARCH_", x86_arch_prctl_codes_2_offset);

अटल काष्ठा strarray *x86_arch_prctl_codes[] = अणु
	&strarray__x86_arch_prctl_codes_1,
	&strarray__x86_arch_prctl_codes_2,
पूर्ण;

अटल DEFINE_STRARRAYS(x86_arch_prctl_codes);

अटल माप_प्रकार x86_arch_prctl__scnम_लिखो_code(पूर्णांक option, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	वापस strarrays__scnम_लिखो(&strarrays__x86_arch_prctl_codes, bf, size, "%#x", show_prefix, option);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_x86_arch_prctl_code(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ code = arg->val;

	वापस x86_arch_prctl__scnम_लिखो_code(code, bf, size, arg->show_string_prefix);
पूर्ण
