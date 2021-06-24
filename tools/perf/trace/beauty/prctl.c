<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/prctl.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <uapi/linux/prctl.h>

#समावेश "trace/beauty/generated/prctl_option_array.c"

DEFINE_STRARRAY(prctl_options, "PR_");

अटल माप_प्रकार prctl__scnम_लिखो_option(पूर्णांक option, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	वापस strarray__scnम_लिखो(&strarray__prctl_options, bf, size, "%d", show_prefix, option);
पूर्ण

अटल माप_प्रकार prctl__scnम_लिखो_set_mm(पूर्णांक option, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	अटल DEFINE_STRARRAY(prctl_set_mm_options, "PR_SET_MM_");
	वापस strarray__scnम_लिखो(&strarray__prctl_set_mm_options, bf, size, "%d", show_prefix, option);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_prctl_arg2(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	पूर्णांक option = syscall_arg__val(arg, 0);

	अगर (option == PR_SET_MM)
		वापस prctl__scnम_लिखो_set_mm(arg->val, bf, size, arg->show_string_prefix);
	/*
	 * We still करोn't grab the contents of poपूर्णांकers on entry or निकास,
	 * so just prपूर्णांक them as hex numbers
	 */
	अगर (option == PR_SET_NAME)
		वापस syscall_arg__scnम_लिखो_hex(bf, size, arg);

	वापस syscall_arg__scnम_लिखो_दीर्घ(bf, size, arg);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_prctl_arg3(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	पूर्णांक option = syscall_arg__val(arg, 0);

	अगर (option == PR_SET_MM)
		वापस syscall_arg__scnम_लिखो_hex(bf, size, arg);

	वापस syscall_arg__scnम_लिखो_दीर्घ(bf, size, arg);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_prctl_option(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ option = arg->val;
	क्रमागत अणु
                SPO_ARG2 = (1 << 1),
                SPO_ARG3 = (1 << 2),
                SPO_ARG4 = (1 << 3),
                SPO_ARG5 = (1 << 4),
                SPO_ARG6 = (1 << 5),
        पूर्ण;
	स्थिर u8 all_but2 = SPO_ARG3 | SPO_ARG4 | SPO_ARG5 | SPO_ARG6;
	स्थिर u8 all = SPO_ARG2 | all_but2;
	स्थिर u8 masks[] = अणु
		[PR_GET_DUMPABLE]	 = all,
		[PR_SET_DUMPABLE]	 = all_but2,
		[PR_SET_NAME]		 = all_but2,
		[PR_GET_CHILD_SUBREAPER] = all_but2,
		[PR_SET_CHILD_SUBREAPER] = all_but2,
		[PR_GET_SECUREBITS]	 = all,
		[PR_SET_SECUREBITS]	 = all_but2,
		[PR_SET_MM]		 = SPO_ARG4 | SPO_ARG5 | SPO_ARG6,
		[PR_GET_PDEATHSIG]	 = all,
		[PR_SET_PDEATHSIG]	 = all_but2,
	पूर्ण;

	अगर (option < ARRAY_SIZE(masks))
		arg->mask |= masks[option];

	वापस prctl__scnम_लिखो_option(option, bf, size, arg->show_string_prefix);
पूर्ण
