<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/pkey_alloc.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>

माप_प्रकार strarray__scnम_लिखो_flags(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, bool show_prefix, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक i, prपूर्णांकed = 0;

	अगर (flags == 0) अणु
		स्थिर अक्षर *s = sa->entries[0];
		अगर (s)
			वापस scnम_लिखो(bf, size, "%s%s", show_prefix ? sa->prefix : "", s);
		वापस scnम_लिखो(bf, size, "%d", 0);
	पूर्ण

	क्रम (i = 1; i < sa->nr_entries; ++i) अणु
		अचिन्हित दीर्घ bit = 1UL << (i - 1);

		अगर (!(flags & bit))
			जारी;

		अगर (prपूर्णांकed != 0)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|");

		अगर (sa->entries[i] != शून्य)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", show_prefix ? sa->prefix : "", sa->entries[i]);
		अन्यथा
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "0x%#", bit);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल माप_प्रकार pkey_alloc__scnम_लिखो_access_rights(पूर्णांक access_rights, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/pkey_alloc_access_rights_array.c"
	अटल DEFINE_STRARRAY(pkey_alloc_access_rights, "PKEY_");

	वापस strarray__scnम_लिखो_flags(&strarray__pkey_alloc_access_rights, bf, size, show_prefix, access_rights);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_pkey_alloc_access_rights(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ cmd = arg->val;

	वापस pkey_alloc__scnम_लिखो_access_rights(cmd, bf, size, arg->show_string_prefix);
पूर्ण
