<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_NOSPEC_ASM_H
#घोषणा _ASM_S390_NOSPEC_ASM_H

#समावेश <यंत्र/alternative-यंत्र.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/dwarf.h>

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित CC_USING_EXPOLINE

_LC_BR_R1 = __LC_BR_R1

/*
 * The expoline macros are used to create thunks in the same क्रमmat
 * as gcc generates them. The 'comdat' section flag makes sure that
 * the various thunks are merged पूर्णांकo a single copy.
 */
	.macro __THUNK_PROLOG_NAME name
	.pushsection .text.\नame,"axG",@progbits,\नame,comdat
	.globl \नame
	.hidden \नame
	.type \नame,@function
\नame:
	CFI_STARTPROC
	.endm

	.macro __THUNK_EPILOG
	CFI_ENDPROC
	.popsection
	.endm

	.macro __THUNK_PROLOG_BR r1,r2
	__THUNK_PROLOG_NAME __s390_indirect_jump_r\ल2\()use_r\ल1
	.endm

	.macro __THUNK_PROLOG_BC d0,r1,r2
	__THUNK_PROLOG_NAME __s390_indirect_branch_\d0\()_\ल2\()use_\ल1
	.endm

	.macro __THUNK_BR r1,r2
	jg	__s390_indirect_jump_r\ल2\()use_r\ल1
	.endm

	.macro __THUNK_BC d0,r1,r2
	jg	__s390_indirect_branch_\d0\()_\ल2\()use_\ल1
	.endm

	.macro __THUNK_BRASL r1,r2,r3
	brasl	\ल1,__s390_indirect_jump_r\ल3\()use_r\ल2
	.endm

	.macro	__DECODE_RR expand,reg,ruse
	.set __decode_fail,1
	.irp r1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लeg,%r\ल1
	.irp r2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लuse,%r\ल2
	\expand \ल1,\ल2
	.set __decode_fail,0
	.endअगर
	.endr
	.endअगर
	.endr
	.अगर __decode_fail == 1
	.error "__DECODE_RR failed"
	.endअगर
	.endm

	.macro	__DECODE_RRR expand,rsave,rtarget,ruse
	.set __decode_fail,1
	.irp r1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लsave,%r\ल1
	.irp r2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लtarget,%r\ल2
	.irp r3,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लuse,%r\ल3
	\expand \ल1,\ल2,\ल3
	.set __decode_fail,0
	.endअगर
	.endr
	.endअगर
	.endr
	.endअगर
	.endr
	.अगर __decode_fail == 1
	.error "__DECODE_RRR failed"
	.endअगर
	.endm

	.macro	__DECODE_DRR expand,disp,reg,ruse
	.set __decode_fail,1
	.irp r1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लeg,%r\ल1
	.irp r2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.अगरc \लuse,%r\ल2
	\expand \disp,\ल1,\ल2
	.set __decode_fail,0
	.endअगर
	.endr
	.endअगर
	.endr
	.अगर __decode_fail == 1
	.error "__DECODE_DRR failed"
	.endअगर
	.endm

	.macro __THUNK_EX_BR reg,ruse
	# Be very careful when adding inकाष्ठाions to this macro!
	# The ALTERNATIVE replacement code has a .+10 which tarमाला_लो
	# the "br \reg" after the code has been patched.
#अगर_घोषित CONFIG_HAVE_MARCH_Z10_FEATURES
	exrl	0,555f
	j	.
#अन्यथा
	.अगरc \लeg,%r1
	ALTERNATIVE "ex %r0,_LC_BR_R1", ".insn ril,0xc60000000000,0,.+10", 35
	j	.
	.अन्यथा
	larl	\लuse,555f
	ex	0,0(\लuse)
	j	.
	.endअगर
#पूर्ण_अगर
555:	br	\लeg
	.endm

	.macro __THUNK_EX_BC disp,reg,ruse
#अगर_घोषित CONFIG_HAVE_MARCH_Z10_FEATURES
	exrl	0,556f
	j	.
#अन्यथा
	larl	\लuse,556f
	ex	0,0(\लuse)
	j	.
#पूर्ण_अगर
556:	b	\disp(\लeg)
	.endm

	.macro GEN_BR_THUNK reg,ruse=%r1
	__DECODE_RR __THUNK_PROLOG_BR,\लeg,\लuse
	__THUNK_EX_BR \लeg,\लuse
	__THUNK_EPILOG
	.endm

	.macro GEN_B_THUNK disp,reg,ruse=%r1
	__DECODE_DRR __THUNK_PROLOG_BC,\disp,\लeg,\लuse
	__THUNK_EX_BC \disp,\लeg,\लuse
	__THUNK_EPILOG
	.endm

	.macro BR_EX reg,ruse=%r1
557:	__DECODE_RR __THUNK_BR,\लeg,\लuse
	.pushsection .s390_indirect_branches,"a",@progbits
	.दीर्घ	557b-.
	.popsection
	.endm

	 .macro B_EX disp,reg,ruse=%r1
558:	__DECODE_DRR __THUNK_BC,\disp,\लeg,\लuse
	.pushsection .s390_indirect_branches,"a",@progbits
	.दीर्घ	558b-.
	.popsection
	.endm

	.macro BASR_EX rsave,rtarget,ruse=%r1
559:	__DECODE_RRR __THUNK_BRASL,\लsave,\लtarget,\लuse
	.pushsection .s390_indirect_branches,"a",@progbits
	.दीर्घ	559b-.
	.popsection
	.endm

#अन्यथा
	.macro GEN_BR_THUNK reg,ruse=%r1
	.endm

	.macro GEN_B_THUNK disp,reg,ruse=%r1
	.endm

	 .macro BR_EX reg,ruse=%r1
	br	\लeg
	.endm

	 .macro B_EX disp,reg,ruse=%r1
	b	\disp(\लeg)
	.endm

	.macro BASR_EX rsave,rtarget,ruse=%r1
	basr	\लsave,\लtarget
	.endm
#पूर्ण_अगर /* CC_USING_EXPOLINE */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_S390_NOSPEC_ASM_H */
