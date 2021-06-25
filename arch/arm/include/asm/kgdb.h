<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ARM KGDB support
 *
 * Author: Deepak Saxena <dsaxena@mvista.com>
 *
 * Copyright (C) 2002 MontaVista Software Inc.
 *
 */

#अगर_अघोषित __ARM_KGDB_H__
#घोषणा __ARM_KGDB_H__

#समावेश <linux/ptrace.h>
#समावेश <यंत्र/opcodes.h>

/*
 * GDB assumes that we're a user process being debugged, so
 * it will send us an SWI command to ग_लिखो पूर्णांकo memory as the
 * debug trap. When an SWI occurs, the next inकाष्ठाion addr is
 * placed पूर्णांकo R14_svc beक्रमe jumping to the vector trap.
 * This करोesn't work क्रम kernel debugging as we are alपढ़ोy in SVC
 * we would loose the kernel's LR, which is a bad thing. This
 * is  bad thing.
 *
 * By करोing this as an undefined inकाष्ठाion trap, we क्रमce a mode
 * चयन from SVC to UND mode, allowing us to save full kernel state.
 *
 * We also define a KGDB_COMPILED_BREAK which can be used to compile
 * in अवरोधpoपूर्णांकs. This is important क्रम things like sysrq-G and क्रम
 * the initial अवरोधpoपूर्णांक from trap_init().
 *
 * Note to ARM HW designers: Add real trap support like SH && PPC to
 * make our lives much much simpler. :)
 */
#घोषणा BREAK_INSTR_SIZE	4
#घोषणा GDB_BREAKINST		0xef9f0001
#घोषणा KGDB_BREAKINST		0xe7ffdefe
#घोषणा KGDB_COMPILED_BREAK	0xe7ffdeff
#घोषणा CACHE_FLUSH_IS_SAFE	1

#अगर_अघोषित	__ASSEMBLY__

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र(__inst_arm(0xe7ffdeff));
पूर्ण

बाह्य व्योम kgdb_handle_bus_error(व्योम);
बाह्य पूर्णांक kgdb_fault_expected;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * From Kevin Hilman:
 *
 * gdb is expecting the following रेजिस्टरs layout.
 *
 * r0-r15: 1 दीर्घ word each
 * f0-f7:  unused, 3 दीर्घ words each !!
 * fps:    unused, 1 दीर्घ word
 * cpsr:   1 दीर्घ word
 *
 * Even though f0-f7 and fps are not used, they need to be
 * present in the रेजिस्टरs sent क्रम correct processing in
 * the host-side gdb.
 *
 * In particular, it is crucial that CPSR is in the right place,
 * otherwise gdb will not be able to correctly पूर्णांकerpret stepping over
 * conditional branches.
 */
#घोषणा _GP_REGS		16
#घोषणा _FP_REGS		8
#घोषणा _EXTRA_REGS		2
#घोषणा GDB_MAX_REGS		(_GP_REGS + (_FP_REGS * 3) + _EXTRA_REGS)
#घोषणा DBG_MAX_REG_NUM		(_GP_REGS + _FP_REGS + _EXTRA_REGS)

#घोषणा KGDB_MAX_NO_CPUS	1
#घोषणा BUFMAX			400
#घोषणा NUMREGBYTES		(GDB_MAX_REGS << 2)
#घोषणा NUMCRITREGBYTES		(32 << 2)

#घोषणा _R0			0
#घोषणा _R1			1
#घोषणा _R2			2
#घोषणा _R3			3
#घोषणा _R4			4
#घोषणा _R5			5
#घोषणा _R6			6
#घोषणा _R7			7
#घोषणा _R8			8
#घोषणा _R9			9
#घोषणा _R10			10
#घोषणा _FP			11
#घोषणा _IP			12
#घोषणा _SPT			13
#घोषणा _LR			14
#घोषणा _PC			15
#घोषणा _CPSR			(GDB_MAX_REGS - 1)

/*
 * So that we can denote the end of a frame क्रम tracing,
 * in the simple हाल:
 */
#घोषणा CFI_END_FRAME(func)	__CFI_END_FRAME(_PC, _SPT, func)

#पूर्ण_अगर /* __ASM_KGDB_H__ */
