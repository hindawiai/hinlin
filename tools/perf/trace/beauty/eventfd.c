<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#अगर_अघोषित EFD_SEMAPHORE
#घोषणा EFD_SEMAPHORE		1
#पूर्ण_अगर

#अगर_अघोषित EFD_NONBLOCK
#घोषणा EFD_NONBLOCK		00004000
#पूर्ण_अगर

#अगर_अघोषित EFD_CLOEXEC
#घोषणा EFD_CLOEXEC		02000000
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_eventfd_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "EFD_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

	अगर (flags == 0)
		वापस scnम_लिखो(bf, size, "NONE");
#घोषणा	P_FLAG(n) \
	अगर (flags & EFD_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~EFD_##n; \
	पूर्ण

	P_FLAG(SEMAPHORE);
	P_FLAG(CLOEXEC);
	P_FLAG(NONBLOCK);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_EFD_FLAGS syscall_arg__scnम_लिखो_eventfd_flags
