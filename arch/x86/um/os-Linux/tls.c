<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <linux/unistd.h>

#समावेश <sys/ptrace.h>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>

#समावेश <sysdep/tls.h>

#अगर_अघोषित PTRACE_GET_THREAD_AREA
#घोषणा PTRACE_GET_THREAD_AREA 25
#पूर्ण_अगर

#अगर_अघोषित PTRACE_SET_THREAD_AREA
#घोषणा PTRACE_SET_THREAD_AREA 26
#पूर्ण_अगर

/* Checks whether host supports TLS, and sets *tls_min according to the value
 * valid on the host.
 * i386 host have it == 6; x86_64 host have it == 12, क्रम i386 emulation. */
व्योम check_host_supports_tls(पूर्णांक *supports_tls, पूर्णांक *tls_min)
अणु
	/* Values क्रम x86 and x86_64.*/
	पूर्णांक val[] = अणुGDT_ENTRY_TLS_MIN_I386, GDT_ENTRY_TLS_MIN_X86_64पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(val); i++) अणु
		user_desc_t info;
		info.entry_number = val[i];

		अगर (syscall(__NR_get_thपढ़ो_area, &info) == 0) अणु
			*tls_min = val[i];
			*supports_tls = 1;
			वापस;
		पूर्ण अन्यथा अणु
			अगर (त्रुटि_सं == EINVAL)
				जारी;
			अन्यथा अगर (त्रुटि_सं == ENOSYS)
				*supports_tls = 0;
			वापस;
		पूर्ण
	पूर्ण

	*supports_tls = 0;
पूर्ण

पूर्णांक os_set_thपढ़ो_area(user_desc_t *info, पूर्णांक pid)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_SET_THREAD_AREA, pid, info->entry_number,
		     (अचिन्हित दीर्घ) info);
	अगर (ret < 0)
		ret = -त्रुटि_सं;
	वापस ret;
पूर्ण

पूर्णांक os_get_thपढ़ो_area(user_desc_t *info, पूर्णांक pid)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_GET_THREAD_AREA, pid, info->entry_number,
		     (अचिन्हित दीर्घ) info);
	अगर (ret < 0)
		ret = -त्रुटि_सं;
	वापस ret;
पूर्ण
