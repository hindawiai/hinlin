<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/sync_file_range.c
 *
 *  Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/log2.h>
#समावेश <uapi/linux/fs.h>

अटल माप_प्रकार sync_file_range__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/sync_file_range_arrays.c"
       अटल DEFINE_STRARRAY(sync_file_range_flags, "SYNC_FILE_RANGE_");
       माप_प्रकार prपूर्णांकed = 0;

       अगर ((flags & SYNC_खाता_RANGE_WRITE_AND_WAIT) == SYNC_खाता_RANGE_WRITE_AND_WAIT) अणु
               prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", show_prefix ? "SYNC_FILE_RANGE_" : "", "WRITE_AND_WAIT");
	       flags &= ~SYNC_खाता_RANGE_WRITE_AND_WAIT;
       पूर्ण

       वापस prपूर्णांकed + strarray__scnम_लिखो_flags(&strarray__sync_file_range_flags, bf + prपूर्णांकed, size - prपूर्णांकed, show_prefix, flags);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_sync_file_range_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ flags = arg->val;

	वापस sync_file_range__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
