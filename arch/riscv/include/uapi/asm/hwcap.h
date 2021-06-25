<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copied from arch/arm64/include/यंत्र/hwcap.h
 *
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2017 SiFive
 */
#अगर_अघोषित _UAPI_ASM_RISCV_HWCAP_H
#घोषणा _UAPI_ASM_RISCV_HWCAP_H

/*
 * Linux saves the भग्नing-poपूर्णांक रेजिस्टरs according to the ISA Linux is
 * executing on, as opposed to the ISA the user program is compiled क्रम.  This
 * is necessary क्रम a handful of esoteric use हालs: क्रम example, userspace
 * thपढ़ोing libraries must be able to examine the actual machine state in
 * order to fully reस्थिरruct the state of a thपढ़ो.
 */
#घोषणा COMPAT_HWCAP_ISA_I	(1 << ('I' - 'A'))
#घोषणा COMPAT_HWCAP_ISA_M	(1 << ('M' - 'A'))
#घोषणा COMPAT_HWCAP_ISA_A	(1 << ('A' - 'A'))
#घोषणा COMPAT_HWCAP_ISA_F	(1 << ('F' - 'A'))
#घोषणा COMPAT_HWCAP_ISA_D	(1 << ('D' - 'A'))
#घोषणा COMPAT_HWCAP_ISA_C	(1 << ('C' - 'A'))

#पूर्ण_अगर /* _UAPI_ASM_RISCV_HWCAP_H */
