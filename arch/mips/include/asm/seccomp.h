<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SECCOMP_H

#समावेश <linux/unistd.h>

#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत स्थिर पूर्णांक *get_compat_mode1_syscalls(व्योम)
अणु
	अटल स्थिर पूर्णांक syscalls_O32[] = अणु
		__NR_O32_Linux + 3, __NR_O32_Linux + 4,
		__NR_O32_Linux + 1, __NR_O32_Linux + 193,
		-1, /* negative terminated */
	पूर्ण;
	अटल स्थिर पूर्णांक syscalls_N32[] = अणु
		__NR_N32_Linux + 0, __NR_N32_Linux + 1,
		__NR_N32_Linux + 58, __NR_N32_Linux + 211,
		-1, /* negative terminated */
	पूर्ण;

	अगर (IS_ENABLED(CONFIG_MIPS32_O32) && test_thपढ़ो_flag(TIF_32BIT_REGS))
		वापस syscalls_O32;

	अगर (IS_ENABLED(CONFIG_MIPS32_N32))
		वापस syscalls_N32;

	BUG();
पूर्ण

#घोषणा get_compat_mode1_syscalls get_compat_mode1_syscalls

#पूर्ण_अगर /* CONFIG_COMPAT */

#समावेश <यंत्र-generic/seccomp.h>

#पूर्ण_अगर /* __ASM_SECCOMP_H */
