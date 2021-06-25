<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#अगर_अघोषित PERF_FLAG_FD_NO_GROUP
# define PERF_FLAG_FD_NO_GROUP		(1UL << 0)
#पूर्ण_अगर

#अगर_अघोषित PERF_FLAG_FD_OUTPUT
# define PERF_FLAG_FD_OUTPUT		(1UL << 1)
#पूर्ण_अगर

#अगर_अघोषित PERF_FLAG_PID_CGROUP
# define PERF_FLAG_PID_CGROUP		(1UL << 2) /* pid=cgroup id, per-cpu mode only */
#पूर्ण_अगर

#अगर_अघोषित PERF_FLAG_FD_CLOEXEC
# define PERF_FLAG_FD_CLOEXEC		(1UL << 3) /* O_CLOEXEC */
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_perf_flags(अक्षर *bf, माप_प्रकार size,
						काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "PERF_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

	अगर (flags == 0)
		वापस 0;

#घोषणा	P_FLAG(n) \
	अगर (flags & PERF_FLAG_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~PERF_FLAG_##n; \
	पूर्ण

	P_FLAG(FD_NO_GROUP);
	P_FLAG(FD_OUTPUT);
	P_FLAG(PID_CGROUP);
	P_FLAG(FD_CLOEXEC);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_PERF_FLAGS syscall_arg__scnम_लिखो_perf_flags
