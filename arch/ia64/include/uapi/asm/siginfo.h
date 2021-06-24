<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Based on <यंत्र-i386/siginfo.h>.
 *
 * Modअगरied 1998-2002
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */
#अगर_अघोषित _UAPI_ASM_IA64_SIGINFO_H
#घोषणा _UAPI_ASM_IA64_SIGINFO_H


#समावेश <यंत्र-generic/siginfo.h>

#घोषणा si_imm		_sअगरields._sigfault._imm	/* as per UNIX SysV ABI spec */
#घोषणा si_flags	_sअगरields._sigfault._flags
/*
 * si_isr is valid क्रम संक_अवैध, संक_भ_त्रुटि, संक_अंश, SIGBUS, and SIGTRAP provided that
 * si_code is non-zero and __ISR_VALID is set in si_flags.
 */
#घोषणा si_isr		_sअगरields._sigfault._isr

/*
 * Flag values क्रम si_flags:
 */
#घोषणा __ISR_VALID_BIT	0
#घोषणा __ISR_VALID	(1 << __ISR_VALID_BIT)

#पूर्ण_अगर /* _UAPI_ASM_IA64_SIGINFO_H */
