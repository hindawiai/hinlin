<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>

अटल माप_प्रकार syscall_arg__scnम_लिखो_रुकोid_options(अक्षर *bf, माप_प्रकार size,
						    काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "W";
	पूर्णांक prपूर्णांकed = 0, options = arg->val;

#घोषणा	P_OPTION(n) \
	अगर (options & W##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "",  #n); \
		options &= ~W##n; \
	पूर्ण

	P_OPTION(NOHANG);
	P_OPTION(UNTRACED);
	P_OPTION(CONTINUED);
#अघोषित P_OPTION

	अगर (options)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", options);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_WAITID_OPTIONS syscall_arg__scnम_लिखो_रुकोid_options
