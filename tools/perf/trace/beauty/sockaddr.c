<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
// Copyright (C) 2018, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>

#समावेश "trace/beauty/beauty.h"
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <sys/un.h>
#समावेश <arpa/inet.h>

#समावेश "trace/beauty/generated/socket_arrays.c"
DEFINE_STRARRAY(socket_families, "PF_");

अटल माप_प्रकार af_inet__scnम_लिखो(काष्ठा sockaddr *sa, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sa;
	अक्षर पंचांगp[16];
	वापस scnम_लिखो(bf, size, ", port: %d, addr: %s", ntohs(sin->sin_port),
			 inet_ntop(sin->sin_family, &sin->sin_addr, पंचांगp, माप(पंचांगp)));
पूर्ण

अटल माप_प्रकार af_inet6__scnम_लिखो(काष्ठा sockaddr *sa, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sa;
	u32 flowinfo = ntohl(sin6->sin6_flowinfo);
	अक्षर पंचांगp[512];
	माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, ", port: %d, addr: %s", ntohs(sin6->sin6_port),
				   inet_ntop(sin6->sin6_family, &sin6->sin6_addr, पंचांगp, माप(पंचांगp)));
	अगर (flowinfo != 0)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, ", flowinfo: %lu", flowinfo);
	अगर (sin6->sin6_scope_id != 0)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, ", scope_id: %lu", sin6->sin6_scope_id);

	वापस prपूर्णांकed;
पूर्ण

अटल माप_प्रकार af_local__scnम_लिखो(काष्ठा sockaddr *sa, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा sockaddr_un *sun = (काष्ठा sockaddr_un *)sa;
	वापस scnम_लिखो(bf, size, ", path: %s", sun->sun_path);
पूर्ण

अटल माप_प्रकार (*af_scnम_लिखोs[])(काष्ठा sockaddr *sa, अक्षर *bf, माप_प्रकार size) = अणु
	[AF_LOCAL] = af_local__scnम_लिखो,
	[AF_INET]  = af_inet__scnम_लिखो,
	[AF_INET6] = af_inet6__scnम_लिखो,
पूर्ण;

अटल माप_प्रकार syscall_arg__scnम_लिखो_augmented_sockaddr(काष्ठा syscall_arg *arg, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)arg->augmented.args;
	अक्षर family[32];
	माप_प्रकार prपूर्णांकed;

	strarray__scnम_लिखो(&strarray__socket_families, family, माप(family), "%d", arg->show_string_prefix, sa->sa_family);
	prपूर्णांकed = scnम_लिखो(bf, size, "{ .family: %s", family);

	अगर (sa->sa_family < ARRAY_SIZE(af_scnम_लिखोs) && af_scnम_लिखोs[sa->sa_family])
		prपूर्णांकed += af_scnम_लिखोs[sa->sa_family](sa, bf + prपूर्णांकed, size - prपूर्णांकed);

	वापस prपूर्णांकed + scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, " }");
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_sockaddr(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अगर (arg->augmented.args)
		वापस syscall_arg__scnम_लिखो_augmented_sockaddr(arg, bf, size);

	वापस scnम_लिखो(bf, size, "%#lx", arg->val);
पूर्ण
