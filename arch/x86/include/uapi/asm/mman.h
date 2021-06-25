<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_MMAN_H
#घोषणा _ASM_X86_MMAN_H

#घोषणा MAP_32BIT	0x40		/* only give out 32bit addresses */

#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
/*
 * Take the 4 protection key bits out of the vma->vm_flags
 * value and turn them in to the bits that we can put in
 * to a pte.
 *
 * Only override these अगर Protection Keys are available
 * (which is only on 64-bit).
 */
#घोषणा arch_vm_get_page_prot(vm_flags)	__pgprot(	\
		((vm_flags) & VM_PKEY_BIT0 ? _PAGE_PKEY_BIT0 : 0) |	\
		((vm_flags) & VM_PKEY_BIT1 ? _PAGE_PKEY_BIT1 : 0) |	\
		((vm_flags) & VM_PKEY_BIT2 ? _PAGE_PKEY_BIT2 : 0) |	\
		((vm_flags) & VM_PKEY_BIT3 ? _PAGE_PKEY_BIT3 : 0))

#घोषणा arch_calc_vm_prot_bits(prot, key) (		\
		((key) & 0x1 ? VM_PKEY_BIT0 : 0) |      \
		((key) & 0x2 ? VM_PKEY_BIT1 : 0) |      \
		((key) & 0x4 ? VM_PKEY_BIT2 : 0) |      \
		((key) & 0x8 ? VM_PKEY_BIT3 : 0))
#पूर्ण_अगर

#समावेश <यंत्र-generic/mman.h>

#पूर्ण_अगर /* _ASM_X86_MMAN_H */
