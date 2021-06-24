<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/fcntl.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <uapi/linux/fcntl.h>

अटल माप_प्रकार fcntl__scnम_लिखो_getfd(अचिन्हित दीर्घ val, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	वापस val ? scnम_लिखो(bf, size, "%s", "0") :
		     scnम_लिखो(bf, size, "%s%s", show_prefix ? "FD_" : "", "CLOEXEC");
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_fcntl_getfd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	वापस fcntl__scnम_लिखो_getfd(arg->val, bf, size, arg->show_string_prefix);
पूर्ण

अटल माप_प्रकार fcntl__scnम_लिखो_getlease(अचिन्हित दीर्घ val, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	अटल स्थिर अक्षर *fcntl_setlease[] = अणु "RDLCK", "WRLCK", "UNLCK", पूर्ण;
	अटल DEFINE_STRARRAY(fcntl_setlease, "F_");

	वापस strarray__scnम_लिखो(&strarray__fcntl_setlease, bf, size, "%x", show_prefix, val);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_fcntl_getlease(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	वापस fcntl__scnम_लिखो_getlease(arg->val, bf, size, arg->show_string_prefix);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_fcntl_cmd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अगर (arg->val == F_GETFL) अणु
		syscall_arg__set_ret_scnम_लिखो(arg, syscall_arg__scnम_लिखो_खोलो_flags);
		जाओ mask_arg;
	पूर्ण
	अगर (arg->val == F_GETFD) अणु
		syscall_arg__set_ret_scnम_लिखो(arg, syscall_arg__scnम_लिखो_fcntl_getfd);
		जाओ mask_arg;
	पूर्ण
	अगर (arg->val == F_DUPFD_CLOEXEC || arg->val == F_DUPFD) अणु
		syscall_arg__set_ret_scnम_लिखो(arg, syscall_arg__scnम_लिखो_fd);
		जाओ out;
	पूर्ण
	अगर (arg->val == F_GETOWN) अणु
		syscall_arg__set_ret_scnम_लिखो(arg, syscall_arg__scnम_लिखो_pid);
		जाओ mask_arg;
	पूर्ण
	अगर (arg->val == F_GETLEASE) अणु
		syscall_arg__set_ret_scnम_लिखो(arg, syscall_arg__scnम_लिखो_fcntl_getlease);
		जाओ mask_arg;
	पूर्ण
	/*
	 * Some commands ignore the third fcntl argument, "arg", so mask it
	 */
	अगर (arg->val == F_GET_SEALS ||
	    arg->val == F_GETSIG) अणु
mask_arg:
		arg->mask |= (1 << 2);
	पूर्ण
out:
	वापस syscall_arg__scnम_लिखो_strarrays(bf, size, arg);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_fcntl_arg(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	पूर्णांक cmd = syscall_arg__val(arg, 1);

	अगर (cmd == F_DUPFD)
		वापस syscall_arg__scnम_लिखो_fd(bf, size, arg);

	अगर (cmd == F_SETFD)
		वापस fcntl__scnम_लिखो_getfd(arg->val, bf, size, show_prefix);

	अगर (cmd == F_SETFL)
		वापस खोलो__scnम_लिखो_flags(arg->val, bf, size, show_prefix);

	अगर (cmd == F_SETOWN)
		वापस syscall_arg__scnम_लिखो_pid(bf, size, arg);

	अगर (cmd == F_SETLEASE)
		वापस fcntl__scnम_लिखो_getlease(arg->val, bf, size, show_prefix);
	/*
	 * We still करोn't grab the contents of poपूर्णांकers on entry or निकास,
	 * so just prपूर्णांक them as hex numbers
	 */
	अगर (cmd == F_SETLK || cmd == F_SETLKW || cmd == F_GETLK ||
	    cmd == F_OFD_SETLK || cmd == F_OFD_SETLKW || cmd == F_OFD_GETLK ||
	    cmd == F_GETOWN_EX || cmd == F_SETOWN_EX ||
	    cmd == F_GET_RW_HINT || cmd == F_SET_RW_HINT ||
	    cmd == F_GET_खाता_RW_HINT || cmd == F_SET_खाता_RW_HINT)
		वापस syscall_arg__scnम_लिखो_hex(bf, size, arg);

	वापस syscall_arg__scnम_लिखो_दीर्घ(bf, size, arg);
पूर्ण
