<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_ASMMACRO_H
#घोषणा _ASM_IA64_ASMMACRO_H

/*
 * Copyright (C) 2000-2001, 2003-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */


#घोषणा ENTRY(name)				\
	.align 32;				\
	.proc name;				\
name:

#घोषणा ENTRY_MIN_ALIGN(name)			\
	.align 16;				\
	.proc name;				\
name:

#घोषणा GLOBAL_ENTRY(name)			\
	.global name;				\
	ENTRY(name)

#घोषणा END(name)				\
	.endp name

/*
 * Helper macros to make unwind directives more पढ़ोable:
 */

/* prologue_gr: */
#घोषणा ASM_UNW_PRLG_RP			0x8
#घोषणा ASM_UNW_PRLG_PFS		0x4
#घोषणा ASM_UNW_PRLG_PSP		0x2
#घोषणा ASM_UNW_PRLG_PR			0x1
#घोषणा ASM_UNW_PRLG_GRSAVE(ninमाला_दो)	(32+(ninमाला_दो))

/*
 * Helper macros क्रम accessing user memory.
 *
 * When adding any new .section/.previous entries here, make sure to
 * also add it to the DISCARD section in arch/ia64/kernel/gate.lds.S or
 * unpleasant things will happen.
 */

	.section "__ex_table", "a"		// declare section & section attributes
	.previous

# define EX(y,x...)				\
	.xdata4 "__ex_table", 99f-., y-.;	\
  [99:]	x
# define EXCLR(y,x...)				\
	.xdata4 "__ex_table", 99f-., y-.+4;	\
  [99:]	x

/*
 * Tag MCA recoverable inकाष्ठाion ranges.
 */

	.section "__mca_table", "a"		// declare section & section attributes
	.previous

# define MCA_RECOVER_RANGE(y)			\
	.xdata4 "__mca_table", y-., 99f-.;	\
  [99:]

/*
 * Mark inकाष्ठाions that need a load of a भव address patched to be
 * a load of a physical address.  We use this either in critical perक्रमmance
 * path (ivt.S - TLB miss processing) or in places where it might not be
 * safe to use a "tpa" inकाष्ठाion (mca_यंत्र.S - error recovery).
 */
	.section ".data..patch.vtop", "a"	// declare section & section attributes
	.previous

#घोषणा	LOAD_PHYSICAL(pr, reg, obj)		\
[1:](pr)movl reg = obj;				\
	.xdata4 ".data..patch.vtop", 1b-.

/*
 * For now, we always put in the McKinley E9 workaround.  On CPUs that करोn't need it,
 * we'll patch out the work-around bundles with NOPs, so their impact is minimal.
 */
#घोषणा DO_MCKINLEY_E9_WORKAROUND

#अगर_घोषित DO_MCKINLEY_E9_WORKAROUND
	.section ".data..patch.mckinley_e9", "a"
	.previous
/* workaround क्रम Itanium 2 Errata 9: */
# define FSYS_RETURN					\
	.xdata4 ".data..patch.mckinley_e9", 1f-.;	\
1:अणु .mib;						\
	nop.m 0;					\
	mov r16=ar.pfs;					\
	br.call.sptk.many b7=2f;;			\
  पूर्ण;							\
2:अणु .mib;						\
	nop.m 0;					\
	mov ar.pfs=r16;					\
	br.ret.sptk.many b6;;				\
  पूर्ण
#अन्यथा
# define FSYS_RETURN	br.ret.sptk.many b6
#पूर्ण_अगर

/*
 * If physical stack रेजिस्टर size is dअगरferent from DEF_NUM_STACK_REG,
 * dynamically patch the kernel क्रम correct size.
 */
	.section ".data..patch.phys_stack_reg", "a"
	.previous
#घोषणा LOAD_PHYS_STACK_REG_SIZE(reg)			\
[1:]	adds reg=IA64_NUM_PHYS_STACK_REG*8+8,r0;	\
	.xdata4 ".data..patch.phys_stack_reg", 1b-.

/*
 * Up until early 2004, use of .align within a function caused bad unwind info.
 * TEXT_ALIGN(n) expands पूर्णांकo ".align n" अगर a fixed GAS is available or पूर्णांकo nothing
 * otherwise.
 */
#अगर_घोषित HAVE_WORKING_TEXT_ALIGN
# define TEXT_ALIGN(n)	.align n
#अन्यथा
# define TEXT_ALIGN(n)
#पूर्ण_अगर

#अगर_घोषित HAVE_SERIALIZE_सूचीECTIVE
# define dv_serialize_data		.serialize.data
# define dv_serialize_inकाष्ठाion	.serialize.inकाष्ठाion
#अन्यथा
# define dv_serialize_data
# define dv_serialize_inकाष्ठाion
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IA64_ASMMACRO_H */
