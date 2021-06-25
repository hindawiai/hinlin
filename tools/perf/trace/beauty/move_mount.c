<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/move_mount.c
 *
 *  Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/log2.h>

अटल माप_प्रकार move_mount__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/move_mount_flags_array.c"
       अटल DEFINE_STRARRAY(move_mount_flags, "MOVE_MOUNT_");

       वापस strarray__scnम_लिखो_flags(&strarray__move_mount_flags, bf, size, show_prefix, flags);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_move_mount_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	वापस move_mount__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
