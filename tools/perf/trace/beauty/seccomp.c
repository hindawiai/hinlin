<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#अगर_अघोषित SECCOMP_SET_MODE_STRICT
#घोषणा SECCOMP_SET_MODE_STRICT 0
#पूर्ण_अगर
#अगर_अघोषित SECCOMP_SET_MODE_FILTER
#घोषणा SECCOMP_SET_MODE_FILTER 1
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_seccomp_op(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "SECCOMP_SET_MODE_";
	पूर्णांक op = arg->val;
	माप_प्रकार prपूर्णांकed = 0;

	चयन (op) अणु
#घोषणा	P_SECCOMP_SET_MODE_OP(n) हाल SECCOMP_SET_MODE_##n: prपूर्णांकed = scnम_लिखो(bf, size, "%s%s", show_prefix ? prefix : "", #n); अवरोध
	P_SECCOMP_SET_MODE_OP(STRICT);
	P_SECCOMP_SET_MODE_OP(FILTER);
#अघोषित P_SECCOMP_SET_MODE_OP
	शेष: prपूर्णांकed = scnम_लिखो(bf, size, "%#x", op);			  अवरोध;
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_SECCOMP_OP  syscall_arg__scnम_लिखो_seccomp_op

#अगर_अघोषित SECCOMP_FILTER_FLAG_TSYNC
#घोषणा SECCOMP_FILTER_FLAG_TSYNC 1
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_seccomp_flags(अक्षर *bf, माप_प्रकार size,
						   काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "SECCOMP_FILTER_FLAG_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

#घोषणा	P_FLAG(n) \
	अगर (flags & SECCOMP_FILTER_FLAG_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~SECCOMP_FILTER_FLAG_##n; \
	पूर्ण

	P_FLAG(TSYNC);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_SECCOMP_FLAGS syscall_arg__scnम_लिखो_seccomp_flags
