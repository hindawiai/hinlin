<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_AUXVEC_H
#घोषणा _ASM_X86_AUXVEC_H
/*
 * Architecture-neutral AT_ values in 0-17, leave some room
 * क्रम more of them, start the x86-specअगरic ones at 32.
 */
#अगर_घोषित __i386__
#घोषणा AT_SYSINFO		32
#पूर्ण_अगर
#घोषणा AT_SYSINFO_EHDR		33

/* entries in ARCH_DLINFO: */
#अगर defined(CONFIG_IA32_EMULATION) || !defined(CONFIG_X86_64)
# define AT_VECTOR_SIZE_ARCH 2
#अन्यथा /* अन्यथा it's non-compat x86-64 */
# define AT_VECTOR_SIZE_ARCH 1
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_AUXVEC_H */
