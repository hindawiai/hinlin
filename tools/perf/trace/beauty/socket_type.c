<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <sys/types.h>
#समावेश <sys/socket.h>

#अगर_अघोषित SOCK_DCCP
# define SOCK_DCCP		6
#पूर्ण_अगर

#अगर_अघोषित SOCK_CLOEXEC
# define SOCK_CLOEXEC		02000000
#पूर्ण_अगर

#अगर_अघोषित SOCK_NONBLOCK
# define SOCK_NONBLOCK		00004000
#पूर्ण_अगर

#अगर_अघोषित SOCK_TYPE_MASK
#घोषणा SOCK_TYPE_MASK 0xf
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_socket_type(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "SOCK_";
	माप_प्रकार prपूर्णांकed;
	पूर्णांक type = arg->val,
	    flags = type & ~SOCK_TYPE_MASK;

	type &= SOCK_TYPE_MASK;
	/*
	 * Can't use a strarray, MIPS may override क्रम ABI reasons.
	 */
	चयन (type) अणु
#घोषणा	P_SK_TYPE(n) हाल SOCK_##n: prपूर्णांकed = scnम_लिखो(bf, size, "%s%s", show_prefix ? prefix : "", #n); अवरोध;
	P_SK_TYPE(STREAM);
	P_SK_TYPE(DGRAM);
	P_SK_TYPE(RAW);
	P_SK_TYPE(RDM);
	P_SK_TYPE(SEQPACKET);
	P_SK_TYPE(DCCP);
	P_SK_TYPE(PACKET);
#अघोषित P_SK_TYPE
	शेष:
		prपूर्णांकed = scnम_लिखो(bf, size, "%#x", type);
	पूर्ण

#घोषणा	P_SK_FLAG(n) \
	अगर (flags & SOCK_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%s", #n); \
		flags &= ~SOCK_##n; \
	पूर्ण

	P_SK_FLAG(CLOEXEC);
	P_SK_FLAG(NONBLOCK);
#अघोषित P_SK_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%#x", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_SK_TYPE syscall_arg__scnम_लिखो_socket_type
