<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PARISC_ALTERNATIVE_H
#घोषणा __ASM_PARISC_ALTERNATIVE_H

#घोषणा ALT_COND_ALWAYS		0x80	/* always replace inकाष्ठाion */
#घोषणा ALT_COND_NO_SMP		0x01	/* when running UP instead of SMP */
#घोषणा ALT_COND_NO_DCACHE	0x02	/* अगर प्रणाली has no d-cache  */
#घोषणा ALT_COND_NO_ICACHE	0x04	/* अगर प्रणाली has no i-cache  */
#घोषणा ALT_COND_NO_SPLIT_TLB	0x08	/* अगर split_tlb == 0  */
#घोषणा ALT_COND_NO_IOC_FDC	0x10	/* अगर I/O cache करोes not need flushes */
#घोषणा ALT_COND_RUN_ON_QEMU	0x20	/* अगर running on QEMU */

#घोषणा INSN_PxTLB	0x02		/* modअगरy pdtlb, pitlb */
#घोषणा INSN_NOP	0x08000240	/* nop */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/stringअगरy.h>

काष्ठा alt_instr अणु
	s32 orig_offset;	/* offset to original inकाष्ठाions */
	s32 len;		/* end of original inकाष्ठाions */
	u32 cond;		/* see ALT_COND_XXX */
	u32 replacement;	/* replacement inकाष्ठाion or code */
पूर्ण;

व्योम set_kernel_text_rw(पूर्णांक enable_पढ़ो_ग_लिखो);
व्योम apply_alternatives_all(व्योम);
व्योम apply_alternatives(काष्ठा alt_instr *start, काष्ठा alt_instr *end,
	स्थिर अक्षर *module_name);

/* Alternative SMP implementation. */
#घोषणा ALTERNATIVE(cond, replacement)		"!0:"	\
	".section .altinstructions, \"aw\"	!"	\
	".word (0b-4-.), 1, " __stringअगरy(cond) ","	\
		__stringअगरy(replacement) "	!"	\
	".previous"

#अन्यथा

/* to replace one single inकाष्ठाions by a new inकाष्ठाion */
#घोषणा ALTERNATIVE(from, to, cond, replacement)\
	.section .altinकाष्ठाions, "aw"	!	\
	.word (from - .), (to - from)/4	!	\
	.word cond, replacement		!	\
	.previous

/* to replace multiple inकाष्ठाions by new code */
#घोषणा ALTERNATIVE_CODE(from, num_inकाष्ठाions, cond, new_instr_ptr)\
	.section .altinकाष्ठाions, "aw"	!	\
	.word (from - .), -num_inकाष्ठाions !	\
	.word cond, (new_instr_ptr - .)	!	\
	.previous

#पूर्ण_अगर  /*  __ASSEMBLY__  */

#पूर्ण_अगर /* __ASM_PARISC_ALTERNATIVE_H */
