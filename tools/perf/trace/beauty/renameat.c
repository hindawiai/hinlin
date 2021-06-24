<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
// Copyright (C) 2018, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>

#समावेश "trace/beauty/beauty.h"

अटल माप_प्रकार नामat2__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/rename_flags_array.c"
       अटल DEFINE_STRARRAY(नाम_flags, "RENAME_");

       वापस strarray__scnम_लिखो_flags(&strarray__नाम_flags, bf, size, show_prefix, flags);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_नामat2_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;
	वापस नामat2__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
