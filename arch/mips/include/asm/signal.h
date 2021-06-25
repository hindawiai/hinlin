<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 97, 98, 99, 2003 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_SIGNAL_H
#घोषणा _ASM_SIGNAL_H

#समावेश <uapi/यंत्र/संकेत.स>

#अगर_घोषित CONFIG_MIPS32_O32
बाह्य काष्ठा mips_abi mips_abi_32;

#घोषणा sig_uses_siginfo(ka, abi)                               \
	((abi != &mips_abi_32) ? 1 :                            \
		((ka)->sa.sa_flags & SA_SIGINFO))
#अन्यथा
#घोषणा sig_uses_siginfo(ka, abi)                               \
	(IS_ENABLED(CONFIG_64BIT) ? 1 :                     \
		(IS_ENABLED(CONFIG_TRAD_SIGNALS) ?          \
			((ka)->sa.sa_flags & SA_SIGINFO) : 1) )
#पूर्ण_अगर

#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/siginfo.h>

#घोषणा __ARCH_HAS_IRIX_SIGACTION

बाह्य पूर्णांक रक्षित_save_fp_context(व्योम __user *sc);
बाह्य पूर्णांक रक्षित_restore_fp_context(व्योम __user *sc);

#पूर्ण_अगर /* _ASM_SIGNAL_H */
