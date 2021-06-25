<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/यंत्र-generic/seccomp.h
 *
 * Copyright (C) 2014 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */
#अगर_अघोषित _ASM_GENERIC_SECCOMP_H
#घोषणा _ASM_GENERIC_SECCOMP_H

#समावेश <linux/unistd.h>

#अगर defined(CONFIG_COMPAT) && !defined(__NR_seccomp_पढ़ो_32)
#घोषणा __NR_seccomp_पढ़ो_32		__NR_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो_32		__NR_ग_लिखो
#घोषणा __NR_seccomp_निकास_32		__NR_निकास
#अगर_अघोषित __NR_seccomp_sigवापस_32
#घोषणा __NR_seccomp_sigवापस_32	__NR_rt_sigवापस
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_COMPAT && ! alपढ़ोy defined */

#घोषणा __NR_seccomp_पढ़ो		__NR_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो		__NR_ग_लिखो
#घोषणा __NR_seccomp_निकास		__NR_निकास
#अगर_अघोषित __NR_seccomp_sigवापस
#घोषणा __NR_seccomp_sigवापस		__NR_rt_sigवापस
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
#अगर_अघोषित get_compat_mode1_syscalls
अटल अंतरभूत स्थिर पूर्णांक *get_compat_mode1_syscalls(व्योम)
अणु
	अटल स्थिर पूर्णांक mode1_syscalls_32[] = अणु
		__NR_seccomp_पढ़ो_32, __NR_seccomp_ग_लिखो_32,
		__NR_seccomp_निकास_32, __NR_seccomp_sigवापस_32,
		-1, /* negative terminated */
	पूर्ण;
	वापस mode1_syscalls_32;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_COMPAT */

#पूर्ण_अगर /* _ASM_GENERIC_SECCOMP_H */
