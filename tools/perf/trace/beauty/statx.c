<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/statx.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <sys/types.h>
#समावेश <uapi/linux/fcntl.h>
#समावेश <uapi/linux/स्थिति.स>

माप_प्रकार syscall_arg__scnम_लिखो_statx_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "AT_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

	अगर (flags == 0)
		वापस scnम_लिखो(bf, size, "%s%s", show_prefix ? "AT_STATX_" : "", "SYNC_AS_STAT");
#घोषणा	P_FLAG(n) \
	अगर (flags & AT_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~AT_##n; \
	पूर्ण

	P_FLAG(SYMLINK_NOFOLLOW);
	P_FLAG(REMOVEसूची);
	P_FLAG(SYMLINK_FOLLOW);
	P_FLAG(NO_AUTOMOUNT);
	P_FLAG(EMPTY_PATH);
	P_FLAG(STATX_FORCE_SYNC);
	P_FLAG(STATX_DONT_SYNC);

#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_statx_mask(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "STATX_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

#घोषणा	P_FLAG(n) \
	अगर (flags & STATX_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~STATX_##n; \
	पूर्ण

	P_FLAG(TYPE);
	P_FLAG(MODE);
	P_FLAG(NLINK);
	P_FLAG(UID);
	P_FLAG(GID);
	P_FLAG(ATIME);
	P_FLAG(MTIME);
	P_FLAG(CTIME);
	P_FLAG(INO);
	P_FLAG(SIZE);
	P_FLAG(BLOCKS);
	P_FLAG(BTIME);
	P_FLAG(MNT_ID);

#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण
