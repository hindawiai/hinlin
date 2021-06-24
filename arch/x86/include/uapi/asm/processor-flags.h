<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_PROCESSOR_FLAGS_H
#घोषणा _UAPI_ASM_X86_PROCESSOR_FLAGS_H
/* Various flags defined: can be included from assembler. */

#समावेश <linux/स्थिर.h>

/*
 * EFLAGS bits
 */
#घोषणा X86_EFLAGS_CF_BIT	0 /* Carry Flag */
#घोषणा X86_EFLAGS_CF		_BITUL(X86_EFLAGS_CF_BIT)
#घोषणा X86_EFLAGS_FIXED_BIT	1 /* Bit 1 - always on */
#घोषणा X86_EFLAGS_FIXED	_BITUL(X86_EFLAGS_FIXED_BIT)
#घोषणा X86_EFLAGS_PF_BIT	2 /* Parity Flag */
#घोषणा X86_EFLAGS_PF		_BITUL(X86_EFLAGS_PF_BIT)
#घोषणा X86_EFLAGS_AF_BIT	4 /* Auxiliary carry Flag */
#घोषणा X86_EFLAGS_AF		_BITUL(X86_EFLAGS_AF_BIT)
#घोषणा X86_EFLAGS_ZF_BIT	6 /* Zero Flag */
#घोषणा X86_EFLAGS_ZF		_BITUL(X86_EFLAGS_ZF_BIT)
#घोषणा X86_EFLAGS_SF_BIT	7 /* Sign Flag */
#घोषणा X86_EFLAGS_SF		_BITUL(X86_EFLAGS_SF_BIT)
#घोषणा X86_EFLAGS_TF_BIT	8 /* Trap Flag */
#घोषणा X86_EFLAGS_TF		_BITUL(X86_EFLAGS_TF_BIT)
#घोषणा X86_EFLAGS_IF_BIT	9 /* Interrupt Flag */
#घोषणा X86_EFLAGS_IF		_BITUL(X86_EFLAGS_IF_BIT)
#घोषणा X86_EFLAGS_DF_BIT	10 /* Direction Flag */
#घोषणा X86_EFLAGS_DF		_BITUL(X86_EFLAGS_DF_BIT)
#घोषणा X86_EFLAGS_OF_BIT	11 /* Overflow Flag */
#घोषणा X86_EFLAGS_OF		_BITUL(X86_EFLAGS_OF_BIT)
#घोषणा X86_EFLAGS_IOPL_BIT	12 /* I/O Privilege Level (2 bits) */
#घोषणा X86_EFLAGS_IOPL		(_AC(3,UL) << X86_EFLAGS_IOPL_BIT)
#घोषणा X86_EFLAGS_NT_BIT	14 /* Nested Task */
#घोषणा X86_EFLAGS_NT		_BITUL(X86_EFLAGS_NT_BIT)
#घोषणा X86_EFLAGS_RF_BIT	16 /* Resume Flag */
#घोषणा X86_EFLAGS_RF		_BITUL(X86_EFLAGS_RF_BIT)
#घोषणा X86_EFLAGS_VM_BIT	17 /* Virtual Mode */
#घोषणा X86_EFLAGS_VM		_BITUL(X86_EFLAGS_VM_BIT)
#घोषणा X86_EFLAGS_AC_BIT	18 /* Alignment Check/Access Control */
#घोषणा X86_EFLAGS_AC		_BITUL(X86_EFLAGS_AC_BIT)
#घोषणा X86_EFLAGS_VIF_BIT	19 /* Virtual Interrupt Flag */
#घोषणा X86_EFLAGS_VIF		_BITUL(X86_EFLAGS_VIF_BIT)
#घोषणा X86_EFLAGS_VIP_BIT	20 /* Virtual Interrupt Pending */
#घोषणा X86_EFLAGS_VIP		_BITUL(X86_EFLAGS_VIP_BIT)
#घोषणा X86_EFLAGS_ID_BIT	21 /* CPUID detection */
#घोषणा X86_EFLAGS_ID		_BITUL(X86_EFLAGS_ID_BIT)

/*
 * Basic CPU control in CR0
 */
#घोषणा X86_CR0_PE_BIT		0 /* Protection Enable */
#घोषणा X86_CR0_PE		_BITUL(X86_CR0_PE_BIT)
#घोषणा X86_CR0_MP_BIT		1 /* Monitor Coprocessor */
#घोषणा X86_CR0_MP		_BITUL(X86_CR0_MP_BIT)
#घोषणा X86_CR0_EM_BIT		2 /* Emulation */
#घोषणा X86_CR0_EM		_BITUL(X86_CR0_EM_BIT)
#घोषणा X86_CR0_TS_BIT		3 /* Task Switched */
#घोषणा X86_CR0_TS		_BITUL(X86_CR0_TS_BIT)
#घोषणा X86_CR0_ET_BIT		4 /* Extension Type */
#घोषणा X86_CR0_ET		_BITUL(X86_CR0_ET_BIT)
#घोषणा X86_CR0_NE_BIT		5 /* Numeric Error */
#घोषणा X86_CR0_NE		_BITUL(X86_CR0_NE_BIT)
#घोषणा X86_CR0_WP_BIT		16 /* Write Protect */
#घोषणा X86_CR0_WP		_BITUL(X86_CR0_WP_BIT)
#घोषणा X86_CR0_AM_BIT		18 /* Alignment Mask */
#घोषणा X86_CR0_AM		_BITUL(X86_CR0_AM_BIT)
#घोषणा X86_CR0_NW_BIT		29 /* Not Write-through */
#घोषणा X86_CR0_NW		_BITUL(X86_CR0_NW_BIT)
#घोषणा X86_CR0_CD_BIT		30 /* Cache Disable */
#घोषणा X86_CR0_CD		_BITUL(X86_CR0_CD_BIT)
#घोषणा X86_CR0_PG_BIT		31 /* Paging */
#घोषणा X86_CR0_PG		_BITUL(X86_CR0_PG_BIT)

/*
 * Paging options in CR3
 */
#घोषणा X86_CR3_PWT_BIT		3 /* Page Write Through */
#घोषणा X86_CR3_PWT		_BITUL(X86_CR3_PWT_BIT)
#घोषणा X86_CR3_PCD_BIT		4 /* Page Cache Disable */
#घोषणा X86_CR3_PCD		_BITUL(X86_CR3_PCD_BIT)

#घोषणा X86_CR3_PCID_BITS	12
#घोषणा X86_CR3_PCID_MASK	(_AC((1UL << X86_CR3_PCID_BITS) - 1, UL))

#घोषणा X86_CR3_PCID_NOFLUSH_BIT 63 /* Preserve old PCID */
#घोषणा X86_CR3_PCID_NOFLUSH    _BITULL(X86_CR3_PCID_NOFLUSH_BIT)

/*
 * Intel CPU features in CR4
 */
#घोषणा X86_CR4_VME_BIT		0 /* enable vm86 extensions */
#घोषणा X86_CR4_VME		_BITUL(X86_CR4_VME_BIT)
#घोषणा X86_CR4_PVI_BIT		1 /* भव पूर्णांकerrupts flag enable */
#घोषणा X86_CR4_PVI		_BITUL(X86_CR4_PVI_BIT)
#घोषणा X86_CR4_TSD_BIT		2 /* disable समय stamp at ipl 3 */
#घोषणा X86_CR4_TSD		_BITUL(X86_CR4_TSD_BIT)
#घोषणा X86_CR4_DE_BIT		3 /* enable debugging extensions */
#घोषणा X86_CR4_DE		_BITUL(X86_CR4_DE_BIT)
#घोषणा X86_CR4_PSE_BIT		4 /* enable page size extensions */
#घोषणा X86_CR4_PSE		_BITUL(X86_CR4_PSE_BIT)
#घोषणा X86_CR4_PAE_BIT		5 /* enable physical address extensions */
#घोषणा X86_CR4_PAE		_BITUL(X86_CR4_PAE_BIT)
#घोषणा X86_CR4_MCE_BIT		6 /* Machine check enable */
#घोषणा X86_CR4_MCE		_BITUL(X86_CR4_MCE_BIT)
#घोषणा X86_CR4_PGE_BIT		7 /* enable global pages */
#घोषणा X86_CR4_PGE		_BITUL(X86_CR4_PGE_BIT)
#घोषणा X86_CR4_PCE_BIT		8 /* enable perक्रमmance counters at ipl 3 */
#घोषणा X86_CR4_PCE		_BITUL(X86_CR4_PCE_BIT)
#घोषणा X86_CR4_OSFXSR_BIT	9 /* enable fast FPU save and restore */
#घोषणा X86_CR4_OSFXSR		_BITUL(X86_CR4_OSFXSR_BIT)
#घोषणा X86_CR4_OSXMMEXCPT_BIT	10 /* enable unmasked SSE exceptions */
#घोषणा X86_CR4_OSXMMEXCPT	_BITUL(X86_CR4_OSXMMEXCPT_BIT)
#घोषणा X86_CR4_UMIP_BIT	11 /* enable UMIP support */
#घोषणा X86_CR4_UMIP		_BITUL(X86_CR4_UMIP_BIT)
#घोषणा X86_CR4_LA57_BIT	12 /* enable 5-level page tables */
#घोषणा X86_CR4_LA57		_BITUL(X86_CR4_LA57_BIT)
#घोषणा X86_CR4_VMXE_BIT	13 /* enable VMX भवization */
#घोषणा X86_CR4_VMXE		_BITUL(X86_CR4_VMXE_BIT)
#घोषणा X86_CR4_SMXE_BIT	14 /* enable safer mode (TXT) */
#घोषणा X86_CR4_SMXE		_BITUL(X86_CR4_SMXE_BIT)
#घोषणा X86_CR4_FSGSBASE_BIT	16 /* enable RDWRFSGS support */
#घोषणा X86_CR4_FSGSBASE	_BITUL(X86_CR4_FSGSBASE_BIT)
#घोषणा X86_CR4_PCIDE_BIT	17 /* enable PCID support */
#घोषणा X86_CR4_PCIDE		_BITUL(X86_CR4_PCIDE_BIT)
#घोषणा X86_CR4_OSXSAVE_BIT	18 /* enable xsave and xrestore */
#घोषणा X86_CR4_OSXSAVE		_BITUL(X86_CR4_OSXSAVE_BIT)
#घोषणा X86_CR4_SMEP_BIT	20 /* enable SMEP support */
#घोषणा X86_CR4_SMEP		_BITUL(X86_CR4_SMEP_BIT)
#घोषणा X86_CR4_SMAP_BIT	21 /* enable SMAP support */
#घोषणा X86_CR4_SMAP		_BITUL(X86_CR4_SMAP_BIT)
#घोषणा X86_CR4_PKE_BIT		22 /* enable Protection Keys support */
#घोषणा X86_CR4_PKE		_BITUL(X86_CR4_PKE_BIT)

/*
 * x86-64 Task Priority Register, CR8
 */
#घोषणा X86_CR8_TPR		_AC(0x0000000f,UL) /* task priority रेजिस्टर */

/*
 * AMD and Transmeta use MSRs क्रम configuration; see <यंत्र/msr-index.h>
 */

/*
 *      NSC/Cyrix CPU configuration रेजिस्टर indexes
 */
#घोषणा CX86_PCR0	0x20
#घोषणा CX86_GCR	0xb8
#घोषणा CX86_CCR0	0xc0
#घोषणा CX86_CCR1	0xc1
#घोषणा CX86_CCR2	0xc2
#घोषणा CX86_CCR3	0xc3
#घोषणा CX86_CCR4	0xe8
#घोषणा CX86_CCR5	0xe9
#घोषणा CX86_CCR6	0xea
#घोषणा CX86_CCR7	0xeb
#घोषणा CX86_PCR1	0xf0
#घोषणा CX86_सूची0	0xfe
#घोषणा CX86_सूची1	0xff
#घोषणा CX86_ARR_BASE	0xc4
#घोषणा CX86_RCR_BASE	0xdc

#घोषणा CR0_STATE	(X86_CR0_PE | X86_CR0_MP | X86_CR0_ET | \
			 X86_CR0_NE | X86_CR0_WP | X86_CR0_AM | \
			 X86_CR0_PG)

#पूर्ण_अगर /* _UAPI_ASM_X86_PROCESSOR_FLAGS_H */
