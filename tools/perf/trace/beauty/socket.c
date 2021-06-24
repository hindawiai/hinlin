<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/socket.c
 *
 *  Copyright (C) 2018, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <sys/types.h>
#समावेश <sys/socket.h>

अटल माप_प्रकार socket__scnम_लिखो_ipproto(पूर्णांक protocol, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
#समावेश "trace/beauty/generated/socket_ipproto_array.c"
	अटल DEFINE_STRARRAY(socket_ipproto, "IPPROTO_");

	वापस strarray__scnम_लिखो(&strarray__socket_ipproto, bf, size, "%d", show_prefix, protocol);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_socket_protocol(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	पूर्णांक करोमुख्य = syscall_arg__val(arg, 0);

	अगर (करोमुख्य == AF_INET || करोमुख्य == AF_INET6)
		वापस socket__scnम_लिखो_ipproto(arg->val, bf, size, arg->show_string_prefix);

	वापस syscall_arg__scnम_लिखो_पूर्णांक(bf, size, arg);
पूर्ण
