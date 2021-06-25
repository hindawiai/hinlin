<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Embedded Alley Solutions, Inc
 * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_MACH_GENERIC_KERNEL_ENTRY_H
#घोषणा __ASM_MACH_GENERIC_KERNEL_ENTRY_H

/* Intentionally empty macro, used in head.S. Override in
 * arch/mips/mach-xxx/kernel-entry-init.h when necessary.
 */
	.macro	kernel_entry_setup
	.endm

/*
 * Do SMP slave processor setup necessary beक्रमe we can safely execute C code.
 */
	.macro	smp_slave_setup
	.endm


#पूर्ण_अगर /* __ASM_MACH_GENERIC_KERNEL_ENTRY_H */
