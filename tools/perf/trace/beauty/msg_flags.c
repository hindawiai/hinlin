<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <sys/types.h>
#समावेश <sys/socket.h>

#अगर_अघोषित MSG_PROBE
#घोषणा MSG_PROBE		     0x10
#पूर्ण_अगर
#अगर_अघोषित MSG_WAITFORONE
#घोषणा MSG_WAITFORONE		   0x10000
#पूर्ण_अगर
#अगर_अघोषित MSG_SENDPAGE_NOTLAST
#घोषणा MSG_SENDPAGE_NOTLAST	   0x20000
#पूर्ण_अगर
#अगर_अघोषित MSG_FASTOPEN
#घोषणा MSG_FASTOPEN		0x20000000
#पूर्ण_अगर
#अगर_अघोषित MSG_CMSG_CLOEXEC
# define MSG_CMSG_CLOEXEC	0x40000000
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_msg_flags(अक्षर *bf, माप_प्रकार size,
					       काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "MSG_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

	अगर (flags == 0)
		वापस scnम_लिखो(bf, size, "NONE");
#घोषणा	P_MSG_FLAG(n) \
	अगर (flags & MSG_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~MSG_##n; \
	पूर्ण

	P_MSG_FLAG(OOB);
	P_MSG_FLAG(PEEK);
	P_MSG_FLAG(DONTROUTE);
	P_MSG_FLAG(CTRUNC);
	P_MSG_FLAG(PROBE);
	P_MSG_FLAG(TRUNC);
	P_MSG_FLAG(DONTWAIT);
	P_MSG_FLAG(EOR);
	P_MSG_FLAG(WAITALL);
	P_MSG_FLAG(FIN);
	P_MSG_FLAG(SYN);
	P_MSG_FLAG(CONFIRM);
	P_MSG_FLAG(RST);
	P_MSG_FLAG(ERRQUEUE);
	P_MSG_FLAG(NOSIGNAL);
	P_MSG_FLAG(MORE);
	P_MSG_FLAG(WAITFORONE);
	P_MSG_FLAG(SENDPAGE_NOTLAST);
	P_MSG_FLAG(FASTOPEN);
	P_MSG_FLAG(CMSG_CLOEXEC);
#अघोषित P_MSG_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_MSG_FLAGS syscall_arg__scnम_लिखो_msg_flags
