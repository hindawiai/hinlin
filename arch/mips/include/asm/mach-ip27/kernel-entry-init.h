<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Copyright (C) 2005 Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित __ASM_MACH_IP27_KERNEL_ENTRY_H
#घोषणा __ASM_MACH_IP27_KERNEL_ENTRY_H

#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/klkernvars.h>

/*
 * TLB bits
 */
#घोषणा PAGE_GLOBAL		(1 << 6)
#घोषणा PAGE_VALID		(1 << 7)
#घोषणा PAGE_सूचीTY		(1 << 8)
#घोषणा CACHE_CACHABLE_COW	(5 << 9)

	/*
	 * inमाला_दो are the text nasid in t1, data nasid in t2.
	 */
	.macro MAPPED_KERNEL_SETUP_TLB
#अगर_घोषित CONFIG_MAPPED_KERNEL
	/*
	 * This needs to पढ़ो the nasid - assume 0 क्रम now.
	 * Drop in 0xffffffffc0000000 in tlbhi, 0+VG in tlblo_0,
	 * 0+DVG in tlblo_1.
	 */
	dli	t0, 0xffffffffc0000000
	dmtc0	t0, CP0_ENTRYHI
	li	t0, 0x1c000		# Offset of text पूर्णांकo node memory
	dsll	t1, NASID_SHFT		# Shअगरt text nasid पूर्णांकo place
	dsll	t2, NASID_SHFT		# Same क्रम data nasid
	or	t1, t1, t0		# Physical load address of kernel text
	or	t2, t2, t0		# Physical load address of kernel data
	dsrl	t1, 12			# 4K pfn
	dsrl	t2, 12			# 4K pfn
	dsll	t1, 6			# Get pfn पूर्णांकo place
	dsll	t2, 6			# Get pfn पूर्णांकo place
	li	t0, ((PAGE_GLOBAL | PAGE_VALID | CACHE_CACHABLE_COW) >> 6)
	or	t0, t0, t1
	mtc0	t0, CP0_ENTRYLO0	# physaddr, VG, cach exlwr
	li	t0, ((PAGE_GLOBAL | PAGE_VALID |  PAGE_सूचीTY | CACHE_CACHABLE_COW) >> 6)
	or	t0, t0, t2
	mtc0	t0, CP0_ENTRYLO1	# physaddr, DVG, cach exlwr
	li	t0, 0x1ffe000		# MAPPED_KERN_TLBMASK, TLBPGMASK_16M
	mtc0	t0, CP0_PAGEMASK
	li	t0, 0			# KMAP_INX
	mtc0	t0, CP0_INDEX
	li	t0, 1
	mtc0	t0, CP0_WIRED
	tlbwi
#अन्यथा
	mtc0	zero, CP0_WIRED
#पूर्ण_अगर
	.endm

/*
 * Intentionally empty macro, used in head.S. Override in
 * arch/mips/mach-xxx/kernel-entry-init.h when necessary.
 */
	.macro	kernel_entry_setup
	GET_NASID_ASM	t1
	move		t2, t1			# text and data are here
	MAPPED_KERNEL_SETUP_TLB
	.endm

/*
 * Do SMP slave processor setup necessary beक्रमe we can safely execute C code.
 */
	.macro	smp_slave_setup
	GET_NASID_ASM	t1
	dli	t0, KLसूची_OFFSET + (KLI_KERN_VARS * KLसूची_ENT_SIZE) + \
		    KLसूची_OFF_POINTER + CAC_BASE
	dsll	t1, NASID_SHFT
	or	t0, t0, t1
	ld	t0, 0(t0)			# t0 poपूर्णांकs to kern_vars काष्ठा
	lh	t1, KV_RO_NASID_OFFSET(t0)
	lh	t2, KV_RW_NASID_OFFSET(t0)
	MAPPED_KERNEL_SETUP_TLB

	/*
	 * We might not get launched at the address the kernel is linked to,
	 * so we jump there.
	 */
	PTR_LA	t0, 0f
	jr	t0
0:
	.endm

#पूर्ण_अगर /* __ASM_MACH_IP27_KERNEL_ENTRY_H */
