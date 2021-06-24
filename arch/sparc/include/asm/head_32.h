<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_HEAD_H
#घोषणा __SPARC_HEAD_H

#घोषणा KERNBASE        0xf0000000  /* First address the kernel will eventually be */

#घोषणा WRITE_PAUSE      nop; nop; nop; /* Have to करो this after %wim/%psr chg */

/* Here are some trap goodies */

/* Generic trap entry. */
#घोषणा TRAP_ENTRY(type, label) \
	rd %psr, %l0; b label; rd %wim, %l3; nop;

/* Data/text faults */
#घोषणा SRMMU_TFAULT rd %psr, %l0; rd %wim, %l3; b srmmu_fault; mov 1, %l7;
#घोषणा SRMMU_DFAULT rd %psr, %l0; rd %wim, %l3; b srmmu_fault; mov 0, %l7;

/* This is क्रम traps we should NEVER get. */
#घोषणा BAD_TRAP(num) \
        rd %psr, %l0; mov num, %l7; b bad_trap_handler; rd %wim, %l3;

/* This is क्रम traps when we want just skip the inकाष्ठाion which caused it */
#घोषणा SKIP_TRAP(type, name) \
	jmpl %l2, %g0; rett %l2 + 4; nop; nop;

/* Notice that क्रम the प्रणाली calls we pull a trick.  We load up a
 * dअगरferent poपूर्णांकer to the प्रणाली call vector table in %l7, but call
 * the same generic प्रणाली call low-level entry poपूर्णांक.  The trap table
 * entry sequences are also HyperSparc pipeline मित्रly ;-)
 */

/* Software trap क्रम Linux प्रणाली calls. */
#घोषणा LINUX_SYSCALL_TRAP \
        sethi %hi(sys_call_table), %l7; \
        or %l7, %lo(sys_call_table), %l7; \
        b linux_sparc_syscall; \
        rd %psr, %l0;

#घोषणा BREAKPOINT_TRAP \
	b अवरोधpoपूर्णांक_trap; \
	rd %psr,%l0; \
	nop; \
	nop;

#अगर_घोषित CONFIG_KGDB
#घोषणा KGDB_TRAP(num)                  \
	mov num, %l7;                   \
	b kgdb_trap_low;                \
	rd %psr,%l0;                    \
	nop;
#अन्यथा
#घोषणा KGDB_TRAP(num) \
	BAD_TRAP(num)
#पूर्ण_अगर

/* The Get Condition Codes software trap क्रम userland. */
#घोषणा GETCC_TRAP \
        b अ_लोc_trap_handler; rd %psr, %l0; nop; nop;

/* The Set Condition Codes software trap क्रम userland. */
#घोषणा SETCC_TRAP \
        b setcc_trap_handler; rd %psr, %l0; nop; nop;

/* The Get PSR software trap क्रम userland. */
#घोषणा GETPSR_TRAP \
	rd %psr, %i0; jmp %l2; rett %l2 + 4; nop;

/* This is क्रम hard पूर्णांकerrupts from level 1-14, 15 is non-maskable (nmi) and
 * माला_लो handled with another macro.
 */
#घोषणा TRAP_ENTRY_INTERRUPT(पूर्णांक_level) \
        mov पूर्णांक_level, %l7; rd %psr, %l0; b real_irq_entry; rd %wim, %l3;

/* Winकरोw overflows/underflows are special and we need to try to be as
 * efficient as possible here....
 */
#घोषणा WINDOW_SPILL \
        rd %psr, %l0; rd %wim, %l3; b spill_winकरोw_entry; andcc %l0, PSR_PS, %g0;

#घोषणा WINDOW_FILL \
        rd %psr, %l0; rd %wim, %l3; b fill_winकरोw_entry; andcc %l0, PSR_PS, %g0;

#पूर्ण_अगर /* __SPARC_HEAD_H */
