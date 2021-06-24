<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 04, 07 Ralf Baechle <ralf@linux-mips.org>
 * Copyright (C) MIPS Technologies, Inc.
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित _ASM_HAZARDS_H
#घोषणा _ASM_HAZARDS_H

#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/compiler.h>

#घोषणा ___ssnop							\
	sll	$0, $0, 1

#घोषणा ___ehb								\
	sll	$0, $0, 3

/*
 * TLB hazards
 */
#अगर (defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_CPU_MIPSR5) || \
     defined(CONFIG_CPU_MIPSR6)) && \
    !defined(CONFIG_CPU_CAVIUM_OCTEON) && !defined(CONFIG_CPU_LOONGSON64)

/*
 * MIPSR2 defines ehb क्रम hazard aव्योमance
 */

#घोषणा __mtc0_tlbw_hazard						\
	___ehb

#घोषणा __mtc0_tlbr_hazard						\
	___ehb

#घोषणा __tlbw_use_hazard						\
	___ehb

#घोषणा __tlb_पढ़ो_hazard						\
	___ehb

#घोषणा __tlb_probe_hazard						\
	___ehb

#घोषणा __irq_enable_hazard						\
	___ehb

#घोषणा __irq_disable_hazard						\
	___ehb

#घोषणा __back_to_back_c0_hazard					\
	___ehb

/*
 * gcc has a tradition of misscompiling the previous स्थिरruct using the
 * address of a label as argument to अंतरभूत assembler.	Gas otoh has the
 * annoying dअगरference between la and dla which are only usable क्रम 32-bit
 * rsp. 64-bit code, so can't be used without conditional compilation.
 * The alternative is चयनing the assembler to 64-bit code which happens
 * to work right even क्रम 32-bit code...
 */
#घोषणा inकाष्ठाion_hazard()						\
करो अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set "MIPS_ISA_LEVEL"				\n"	\
	"	dla	%0, 1f					\n"	\
	"	jr.hb	%0					\n"	\
	"	.set	pop					\n"	\
	"1:							\n"	\
	: "=r" (पंचांगp));							\
पूर्ण जबतक (0)

#या_अगर (defined(CONFIG_CPU_MIPSR1) && !defined(CONFIG_MIPS_ALCHEMY)) || \
	defined(CONFIG_CPU_BMIPS)

/*
 * These are slightly complicated by the fact that we guarantee R1 kernels to
 * run fine on R2 processors.
 */

#घोषणा __mtc0_tlbw_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __mtc0_tlbr_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __tlbw_use_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __tlb_पढ़ो_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __tlb_probe_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __irq_enable_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __irq_disable_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#घोषणा __back_to_back_c0_hazard					\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

/*
 * gcc has a tradition of misscompiling the previous स्थिरruct using the
 * address of a label as argument to अंतरभूत assembler.	Gas otoh has the
 * annoying dअगरference between la and dla which are only usable क्रम 32-bit
 * rsp. 64-bit code, so can't be used without conditional compilation.
 * The alternative is चयनing the assembler to 64-bit code which happens
 * to work right even क्रम 32-bit code...
 */
#घोषणा __inकाष्ठाion_hazard()						\
करो अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	mips64r2				\n"	\
	"	dla	%0, 1f					\n"	\
	"	jr.hb	%0					\n"	\
	"	.set	pop					\n"	\
	"1:							\n"	\
	: "=r" (पंचांगp));							\
पूर्ण जबतक (0)

#घोषणा inकाष्ठाion_hazard()						\
करो अणु									\
	अगर (cpu_has_mips_r2_r6)						\
		__inकाष्ठाion_hazard();					\
पूर्ण जबतक (0)

#या_अगर defined(CONFIG_MIPS_ALCHEMY) || defined(CONFIG_CPU_CAVIUM_OCTEON) || \
	defined(CONFIG_CPU_LOONGSON2EF) || defined(CONFIG_CPU_LOONGSON64) || \
	defined(CONFIG_CPU_R10000) || defined(CONFIG_CPU_R5500) || defined(CONFIG_CPU_XLR)

/*
 * R10000 rocks - all hazards handled in hardware, so this becomes a nobrainer.
 */

#घोषणा __mtc0_tlbw_hazard

#घोषणा __mtc0_tlbr_hazard

#घोषणा __tlbw_use_hazard

#घोषणा __tlb_पढ़ो_hazard

#घोषणा __tlb_probe_hazard

#घोषणा __irq_enable_hazard

#घोषणा __irq_disable_hazard

#घोषणा __back_to_back_c0_hazard

#घोषणा inकाष्ठाion_hazard() करो अणु पूर्ण जबतक (0)

#या_अगर defined(CONFIG_CPU_SB1)

/*
 * Mostly like R4000 क्रम historic reasons
 */
#घोषणा __mtc0_tlbw_hazard

#घोषणा __mtc0_tlbr_hazard

#घोषणा __tlbw_use_hazard

#घोषणा __tlb_पढ़ो_hazard

#घोषणा __tlb_probe_hazard

#घोषणा __irq_enable_hazard

#घोषणा __irq_disable_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop

#घोषणा __back_to_back_c0_hazard

#घोषणा inकाष्ठाion_hazard() करो अणु पूर्ण जबतक (0)

#अन्यथा

/*
 * Finally the catchall हाल क्रम all other processors including R4000, R4400,
 * R4600, R4700, R5000, RM7000, NEC VR41xx etc.
 *
 * The taken branch will result in a two cycle penalty क्रम the two समाप्तed
 * inकाष्ठाions on R4000 / R4400.  Other processors only have a single cycle
 * hazard so this is nice trick to have an optimal code क्रम a range of
 * processors.
 */
#घोषणा __mtc0_tlbw_hazard						\
	nop;								\
	nop

#घोषणा __mtc0_tlbr_hazard						\
	nop;								\
	nop

#घोषणा __tlbw_use_hazard						\
	nop;								\
	nop;								\
	nop

#घोषणा __tlb_पढ़ो_hazard						\
	nop;								\
	nop;								\
	nop

#घोषणा __tlb_probe_hazard						\
	nop;								\
	nop;								\
	nop

#घोषणा __irq_enable_hazard						\
	___ssnop;							\
	___ssnop;							\
	___ssnop

#घोषणा __irq_disable_hazard						\
	nop;								\
	nop;								\
	nop

#घोषणा __back_to_back_c0_hazard					\
	___ssnop;							\
	___ssnop;							\
	___ssnop

#घोषणा inकाष्ठाion_hazard() करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर


/* FPU hazards */

#अगर defined(CONFIG_CPU_SB1)

#घोषणा __enable_fpu_hazard						\
	.set	push;							\
	.set	mips64;							\
	.set	noreorder;						\
	___ssnop;							\
	bnezl	$0, .+4;						\
	___ssnop;							\
	.set	pop

#घोषणा __disable_fpu_hazard

#या_अगर defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_CPU_MIPSR5) || \
      defined(CONFIG_CPU_MIPSR6)

#घोषणा __enable_fpu_hazard						\
	___ehb

#घोषणा __disable_fpu_hazard						\
	___ehb

#अन्यथा

#घोषणा __enable_fpu_hazard						\
	nop;								\
	nop;								\
	nop;								\
	nop

#घोषणा __disable_fpu_hazard						\
	___ehb

#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__

#घोषणा _ssnop ___ssnop
#घोषणा	_ehb ___ehb
#घोषणा mtc0_tlbw_hazard __mtc0_tlbw_hazard
#घोषणा mtc0_tlbr_hazard __mtc0_tlbr_hazard
#घोषणा tlbw_use_hazard __tlbw_use_hazard
#घोषणा tlb_पढ़ो_hazard __tlb_पढ़ो_hazard
#घोषणा tlb_probe_hazard __tlb_probe_hazard
#घोषणा irq_enable_hazard __irq_enable_hazard
#घोषणा irq_disable_hazard __irq_disable_hazard
#घोषणा back_to_back_c0_hazard __back_to_back_c0_hazard
#घोषणा enable_fpu_hazard __enable_fpu_hazard
#घोषणा disable_fpu_hazard __disable_fpu_hazard

#अन्यथा

#घोषणा _ssnop()							\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(___ssnop)						\
	);								\
पूर्ण जबतक (0)

#घोषणा	_ehb()								\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(___ehb)						\
	);								\
पूर्ण जबतक (0)


#घोषणा mtc0_tlbw_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__mtc0_tlbw_hazard)					\
	);								\
पूर्ण जबतक (0)


#घोषणा mtc0_tlbr_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__mtc0_tlbr_hazard)					\
	);								\
पूर्ण जबतक (0)


#घोषणा tlbw_use_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__tlbw_use_hazard)					\
	);								\
पूर्ण जबतक (0)


#घोषणा tlb_पढ़ो_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__tlb_पढ़ो_hazard)					\
	);								\
पूर्ण जबतक (0)


#घोषणा tlb_probe_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__tlb_probe_hazard)					\
	);								\
पूर्ण जबतक (0)


#घोषणा irq_enable_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__irq_enable_hazard)				\
	);								\
पूर्ण जबतक (0)


#घोषणा irq_disable_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__irq_disable_hazard)				\
	);								\
पूर्ण जबतक (0)


#घोषणा back_to_back_c0_hazard() 					\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__back_to_back_c0_hazard)				\
	);								\
पूर्ण जबतक (0)


#घोषणा enable_fpu_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__enable_fpu_hazard)				\
	);								\
पूर्ण जबतक (0)


#घोषणा disable_fpu_hazard()						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	__stringअगरy(__disable_fpu_hazard)				\
	);								\
पूर्ण जबतक (0)

/*
 * MIPS R2 inकाष्ठाion hazard barrier.   Needs to be called as a subroutine.
 */
बाह्य व्योम mips_ihb(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__  */

#पूर्ण_अगर /* _ASM_HAZARDS_H */
