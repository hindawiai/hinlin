<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AArch64 KGDB support
 *
 * Based on arch/arm/include/kgdb.h
 *
 * Copyright (C) 2013 Cavium Inc.
 * Author: Vijaya Kumar K <vijaya.kumar@caviumnetworks.com>
 */

#अगर_अघोषित __ARM_KGDB_H
#घोषणा __ARM_KGDB_H

#समावेश <linux/ptrace.h>
#समावेश <यंत्र/debug-monitors.h>

#अगर_अघोषित	__ASSEMBLY__

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र ("brk %0" : : "I" (KGDB_COMPILED_DBG_BRK_IMM));
पूर्ण

बाह्य व्योम kgdb_handle_bus_error(व्योम);
बाह्य पूर्णांक kgdb_fault_expected;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * gdb remote procotol (well most versions of it) expects the following
 * रेजिस्टर layout.
 *
 * General purpose regs:
 *     r0-r30: 64 bit
 *     sp,pc : 64 bit
 *     pstate  : 32 bit
 *     Total: 33 + 1
 * FPU regs:
 *     f0-f31: 128 bit
 *     fpsr & fpcr: 32 bit
 *     Total: 32 + 2
 *
 * To expand a little on the "most versions of it"... when the gdb remote
 * protocol क्रम AArch64 was developed it depended on a statement in the
 * Architecture Reference Manual that claimed "SPSR_ELx is a 32-bit register".
 * and, as a result, allocated only 32-bits क्रम the PSTATE in the remote
 * protocol. In fact this statement is still present in ARM DDI 0487A.i.
 *
 * Unक्रमtunately "is a 32-bit register" has a very special meaning क्रम
 * प्रणाली रेजिस्टरs. It means that "the upper bits, bits[63:32], are
 * RES0.". RES0 is heavily used in the ARM architecture करोcuments as a
 * way to leave space क्रम future architecture changes. So to translate a
 * little क्रम people who करोn't spend their spare समय पढ़ोing ARM architecture
 * manuals, what "is a 32-bit register" actually means in this context is
 * "is a 64-bit रेजिस्टर but one with no meaning allocated to any of the
 * upper 32-bits... *yet*".
 *
 * Perhaps then we should not be surprised that this has led to some
 * confusion. Specअगरically a patch, influenced by the above translation,
 * that extended PSTATE to 64-bit was accepted पूर्णांकo gdb-7.7 but the patch
 * was reverted in gdb-7.8.1 and all later releases, when this was
 * discovered to be an unकरोcumented protocol change.
 *
 * So... it is *not* wrong क्रम us to only allocate 32-bits to PSTATE
 * here even though the kernel itself allocates 64-bits क्रम the same
 * state. That is because this bit of code tells the kernel how the gdb
 * remote protocol (well most versions of it) describes the रेजिस्टर state.
 *
 * Note that अगर you are using one of the versions of gdb that supports
 * the gdb-7.7 version of the protocol you cannot use kgdb directly
 * without providing a custom रेजिस्टर description (gdb can load new
 * protocol descriptions at runसमय).
 */

#घोषणा _GP_REGS		33
#घोषणा _FP_REGS		32
#घोषणा _EXTRA_REGS		3
/*
 * general purpose रेजिस्टरs size in bytes.
 * pstate is only 4 bytes. subtract 4 bytes
 */
#घोषणा GP_REG_BYTES		(_GP_REGS * 8)
#घोषणा DBG_MAX_REG_NUM		(_GP_REGS + _FP_REGS + _EXTRA_REGS)

/*
 * Size of I/O buffer क्रम gdb packet.
 * considering to hold all रेजिस्टर contents, size is set
 */

#घोषणा BUFMAX			2048

/*
 * Number of bytes required क्रम gdb_regs buffer.
 * _GP_REGS: 8 bytes, _FP_REGS: 16 bytes and _EXTRA_REGS: 4 bytes each
 * GDB fails to connect क्रम size beyond this with error
 * "'g' packet reply is too long"
 */

#घोषणा NUMREGBYTES	((_GP_REGS * 8) + (_FP_REGS * 16) + \
			(_EXTRA_REGS * 4))

#पूर्ण_अगर /* __ASM_KGDB_H */
