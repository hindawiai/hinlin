<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/fsmount.c
 *
 *  Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/log2.h>
#समावेश <uapi/linux/mount.h>

अटल माप_प्रकार fsmount__scnम_लिखो_attr_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/fsmount_arrays.c"
       अटल DEFINE_STRARRAY(fsmount_attr_flags, "MOUNT_ATTR_");
       माप_प्रकार prपूर्णांकed = 0;

       अगर ((flags & ~MOUNT_ATTR__ATIME) != 0)
	       prपूर्णांकed += strarray__scnम_लिखो_flags(&strarray__fsmount_attr_flags, bf, size, show_prefix, flags);

       अगर ((flags & MOUNT_ATTR__ATIME) == MOUNT_ATTR_RELATIME) अणु
	       prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s",
			            prपूर्णांकed ? "|" : "", show_prefix ? "MOUNT_ATTR_" : "", "RELATIME");
       पूर्ण

       वापस prपूर्णांकed;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_fsmount_attr_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	वापस fsmount__scnम_लिखो_attr_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
