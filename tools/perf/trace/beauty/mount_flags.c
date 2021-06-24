<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/mount_flags.c
 *
 *  Copyright (C) 2018, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <sys/mount.h>

अटल माप_प्रकार mount__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/mount_flags_array.c"
	अटल DEFINE_STRARRAY(mount_flags, "MS_");

	वापस strarray__scnम_लिखो_flags(&strarray__mount_flags, bf, size, show_prefix, flags);
पूर्ण

अचिन्हित दीर्घ syscall_arg__mask_val_mount_flags(काष्ठा syscall_arg *arg __maybe_unused, अचिन्हित दीर्घ flags)
अणु
	// करो_mount in fs/namespace.c:
	/*
	 * Pre-0.97 versions of mount() didn't have a flags word.  When the
	 * flags word was पूर्णांकroduced its top half was required to have the
	 * magic value 0xC0ED, and this reमुख्यed so until 2.4.0-test9.
	 * Thereक्रमe, अगर this magic number is present, it carries no
	 * inक्रमmation and must be discarded.
	 */
	अगर ((flags & MS_MGC_MSK) == MS_MGC_VAL)
		flags &= ~MS_MGC_MSK;

	वापस flags;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_mount_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	वापस mount__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
