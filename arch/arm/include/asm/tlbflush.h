<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/tlbflush.h
 *
 *  Copyright (C) 1999-2003 Russell King
 */
#अगर_अघोषित _ASMARM_TLBFLUSH_H
#घोषणा _ASMARM_TLBFLUSH_H

#अगर_अघोषित __ASSEMBLY__
# include <linux/mm_types.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU

#समावेश <यंत्र/glue.h>

#घोषणा TLB_V4_U_PAGE	(1 << 1)
#घोषणा TLB_V4_D_PAGE	(1 << 2)
#घोषणा TLB_V4_I_PAGE	(1 << 3)
#घोषणा TLB_V6_U_PAGE	(1 << 4)
#घोषणा TLB_V6_D_PAGE	(1 << 5)
#घोषणा TLB_V6_I_PAGE	(1 << 6)

#घोषणा TLB_V4_U_FULL	(1 << 9)
#घोषणा TLB_V4_D_FULL	(1 << 10)
#घोषणा TLB_V4_I_FULL	(1 << 11)
#घोषणा TLB_V6_U_FULL	(1 << 12)
#घोषणा TLB_V6_D_FULL	(1 << 13)
#घोषणा TLB_V6_I_FULL	(1 << 14)

#घोषणा TLB_V6_U_ASID	(1 << 16)
#घोषणा TLB_V6_D_ASID	(1 << 17)
#घोषणा TLB_V6_I_ASID	(1 << 18)

#घोषणा TLB_V6_BP	(1 << 19)

/* Unअगरied Inner Shareable TLB operations (ARMv7 MP extensions) */
#घोषणा TLB_V7_UIS_PAGE	(1 << 20)
#घोषणा TLB_V7_UIS_FULL (1 << 21)
#घोषणा TLB_V7_UIS_ASID (1 << 22)
#घोषणा TLB_V7_UIS_BP	(1 << 23)

#घोषणा TLB_BARRIER	(1 << 28)
#घोषणा TLB_L2CLEAN_FR	(1 << 29)		/* Feroceon */
#घोषणा TLB_DCLEAN	(1 << 30)
#घोषणा TLB_WB		(1 << 31)

/*
 *	MMU TLB Model
 *	=============
 *
 *	We have the following to choose from:
 *	  v4    - ARMv4 without ग_लिखो buffer
 *	  v4wb  - ARMv4 with ग_लिखो buffer without I TLB flush entry inकाष्ठाion
 *	  v4wbi - ARMv4 with ग_लिखो buffer with I TLB flush entry inकाष्ठाion
 *	  fr    - Feroceon (v4wbi with non-outer-cacheable page table walks)
 *	  fa    - Faraday (v4 with ग_लिखो buffer with UTLB)
 *	  v6wbi - ARMv6 with ग_लिखो buffer with I TLB flush entry inकाष्ठाion
 *	  v7wbi - identical to v6wbi
 */
#अघोषित _TLB
#अघोषित MULTI_TLB

#अगर_घोषित CONFIG_SMP_ON_UP
#घोषणा MULTI_TLB 1
#पूर्ण_अगर

#घोषणा v4_tlb_flags	(TLB_V4_U_FULL | TLB_V4_U_PAGE)

#अगर_घोषित CONFIG_CPU_TLB_V4WT
# define v4_possible_flags	v4_tlb_flags
# define v4_always_flags	v4_tlb_flags
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB v4
# endअगर
#अन्यथा
# define v4_possible_flags	0
# define v4_always_flags	(-1UL)
#पूर्ण_अगर

#घोषणा fa_tlb_flags	(TLB_WB | TLB_DCLEAN | TLB_BARRIER | \
			 TLB_V4_U_FULL | TLB_V4_U_PAGE)

#अगर_घोषित CONFIG_CPU_TLB_FA
# define fa_possible_flags	fa_tlb_flags
# define fa_always_flags	fa_tlb_flags
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB fa
# endअगर
#अन्यथा
# define fa_possible_flags	0
# define fa_always_flags	(-1UL)
#पूर्ण_अगर

#घोषणा v4wbi_tlb_flags	(TLB_WB | TLB_DCLEAN | \
			 TLB_V4_I_FULL | TLB_V4_D_FULL | \
			 TLB_V4_I_PAGE | TLB_V4_D_PAGE)

#अगर_घोषित CONFIG_CPU_TLB_V4WBI
# define v4wbi_possible_flags	v4wbi_tlb_flags
# define v4wbi_always_flags	v4wbi_tlb_flags
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB v4wbi
# endअगर
#अन्यथा
# define v4wbi_possible_flags	0
# define v4wbi_always_flags	(-1UL)
#पूर्ण_अगर

#घोषणा fr_tlb_flags	(TLB_WB | TLB_DCLEAN | TLB_L2CLEAN_FR | \
			 TLB_V4_I_FULL | TLB_V4_D_FULL | \
			 TLB_V4_I_PAGE | TLB_V4_D_PAGE)

#अगर_घोषित CONFIG_CPU_TLB_FEROCEON
# define fr_possible_flags	fr_tlb_flags
# define fr_always_flags	fr_tlb_flags
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB v4wbi
# endअगर
#अन्यथा
# define fr_possible_flags	0
# define fr_always_flags	(-1UL)
#पूर्ण_अगर

#घोषणा v4wb_tlb_flags	(TLB_WB | TLB_DCLEAN | \
			 TLB_V4_I_FULL | TLB_V4_D_FULL | \
			 TLB_V4_D_PAGE)

#अगर_घोषित CONFIG_CPU_TLB_V4WB
# define v4wb_possible_flags	v4wb_tlb_flags
# define v4wb_always_flags	v4wb_tlb_flags
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB v4wb
# endअगर
#अन्यथा
# define v4wb_possible_flags	0
# define v4wb_always_flags	(-1UL)
#पूर्ण_अगर

#घोषणा v6wbi_tlb_flags (TLB_WB | TLB_DCLEAN | TLB_BARRIER | \
			 TLB_V6_I_FULL | TLB_V6_D_FULL | \
			 TLB_V6_I_PAGE | TLB_V6_D_PAGE | \
			 TLB_V6_I_ASID | TLB_V6_D_ASID | \
			 TLB_V6_BP)

#अगर_घोषित CONFIG_CPU_TLB_V6
# define v6wbi_possible_flags	v6wbi_tlb_flags
# define v6wbi_always_flags	v6wbi_tlb_flags
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB v6wbi
# endअगर
#अन्यथा
# define v6wbi_possible_flags	0
# define v6wbi_always_flags	(-1UL)
#पूर्ण_अगर

#घोषणा v7wbi_tlb_flags_smp	(TLB_WB | TLB_BARRIER | \
				 TLB_V7_UIS_FULL | TLB_V7_UIS_PAGE | \
				 TLB_V7_UIS_ASID | TLB_V7_UIS_BP)
#घोषणा v7wbi_tlb_flags_up	(TLB_WB | TLB_DCLEAN | TLB_BARRIER | \
				 TLB_V6_U_FULL | TLB_V6_U_PAGE | \
				 TLB_V6_U_ASID | TLB_V6_BP)

#अगर_घोषित CONFIG_CPU_TLB_V7

# अगरdef CONFIG_SMP_ON_UP
#  define v7wbi_possible_flags	(v7wbi_tlb_flags_smp | v7wbi_tlb_flags_up)
#  define v7wbi_always_flags	(v7wbi_tlb_flags_smp & v7wbi_tlb_flags_up)
# elअगर defined(CONFIG_SMP)
#  define v7wbi_possible_flags	v7wbi_tlb_flags_smp
#  define v7wbi_always_flags	v7wbi_tlb_flags_smp
# अन्यथा
#  define v7wbi_possible_flags	v7wbi_tlb_flags_up
#  define v7wbi_always_flags	v7wbi_tlb_flags_up
# endअगर
# अगरdef _TLB
#  define MULTI_TLB 1
# अन्यथा
#  define _TLB v7wbi
# endअगर
#अन्यथा
# define v7wbi_possible_flags	0
# define v7wbi_always_flags	(-1UL)
#पूर्ण_अगर

#अगर_अघोषित _TLB
#त्रुटि Unknown TLB model
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/sched.h>

काष्ठा cpu_tlb_fns अणु
	व्योम (*flush_user_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, काष्ठा vm_area_काष्ठा *);
	व्योम (*flush_kern_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	अचिन्हित दीर्घ tlb_flags;
पूर्ण;

/*
 * Select the calling method
 */
#अगर_घोषित MULTI_TLB

#घोषणा __cpu_flush_user_tlb_range	cpu_tlb.flush_user_range
#घोषणा __cpu_flush_kern_tlb_range	cpu_tlb.flush_kern_range

#अन्यथा

#घोषणा __cpu_flush_user_tlb_range	__glue(_TLB,_flush_user_tlb_range)
#घोषणा __cpu_flush_kern_tlb_range	__glue(_TLB,_flush_kern_tlb_range)

बाह्य व्योम __cpu_flush_user_tlb_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ, काष्ठा vm_area_काष्ठा *);
बाह्य व्योम __cpu_flush_kern_tlb_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

#पूर्ण_अगर

बाह्य काष्ठा cpu_tlb_fns cpu_tlb;

#घोषणा __cpu_tlb_flags			cpu_tlb.tlb_flags

/*
 *	TLB Management
 *	==============
 *
 *	The arch/arm/mm/tlb-*.S files implement these methods.
 *
 *	The TLB specअगरic code is expected to perक्रमm whatever tests it
 *	needs to determine अगर it should invalidate the TLB क्रम each
 *	call.  Start addresses are inclusive and end addresses are
 *	exclusive; it is safe to round these addresses करोwn.
 *
 *	flush_tlb_all()
 *
 *		Invalidate the entire TLB.
 *
 *	flush_tlb_mm(mm)
 *
 *		Invalidate all TLB entries in a particular address
 *		space.
 *		- mm	- mm_काष्ठा describing address space
 *
 *	flush_tlb_range(mm,start,end)
 *
 *		Invalidate a range of TLB entries in the specअगरied
 *		address space.
 *		- mm	- mm_काष्ठा describing address space
 *		- start - start address (may not be aligned)
 *		- end	- end address (exclusive, may not be aligned)
 *
 *	flush_tlb_page(vaddr,vma)
 *
 *		Invalidate the specअगरied page in the specअगरied address range.
 *		- vaddr - भव address (may not be aligned)
 *		- vma	- vma_काष्ठा describing address range
 *
 *	flush_kern_tlb_page(kaddr)
 *
 *		Invalidate the TLB entry क्रम the specअगरied page.  The address
 *		will be in the kernels भव memory space.  Current uses
 *		only require the D-TLB to be invalidated.
 *		- kaddr - Kernel भव memory address
 */

/*
 * We optimise the code below by:
 *  - building a set of TLB flags that might be set in __cpu_tlb_flags
 *  - building a set of TLB flags that will always be set in __cpu_tlb_flags
 *  - अगर we're going to need __cpu_tlb_flags, access it once and only once
 *
 * This allows us to build optimal assembly क्रम the single-CPU type हाल,
 * and as बंद to optimal given the compiler स्थिरrants क्रम multi-CPU
 * हाल.  We could करो better क्रम the multi-CPU हाल अगर the compiler
 * implemented the "%?" method, but this has been disजारीd due to too
 * many people getting it wrong.
 */
#घोषणा possible_tlb_flags	(v4_possible_flags | \
				 v4wbi_possible_flags | \
				 fr_possible_flags | \
				 v4wb_possible_flags | \
				 fa_possible_flags | \
				 v6wbi_possible_flags | \
				 v7wbi_possible_flags)

#घोषणा always_tlb_flags	(v4_always_flags & \
				 v4wbi_always_flags & \
				 fr_always_flags & \
				 v4wb_always_flags & \
				 fa_always_flags & \
				 v6wbi_always_flags & \
				 v7wbi_always_flags)

#घोषणा tlb_flag(f)	((always_tlb_flags & (f)) || (__tlb_flag & possible_tlb_flags & (f)))

#घोषणा __tlb_op(f, insnarg, arg)					\
	करो अणु								\
		अगर (always_tlb_flags & (f))				\
			यंत्र("mcr " insnarg				\
			    : : "r" (arg) : "cc");			\
		अन्यथा अगर (possible_tlb_flags & (f))			\
			यंत्र("tst %1, %2\n\t"				\
			    "mcrne " insnarg				\
			    : : "r" (arg), "r" (__tlb_flag), "Ir" (f)	\
			    : "cc");					\
	पूर्ण जबतक (0)

#घोषणा tlb_op(f, regs, arg)	__tlb_op(f, "p15, 0, %0, " regs, arg)
#घोषणा tlb_l2_op(f, regs, arg)	__tlb_op(f, "p15, 1, %0, " regs, arg)

अटल अंतरभूत व्योम __local_flush_tlb_all(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	tlb_op(TLB_V4_U_FULL | TLB_V6_U_FULL, "c8, c7, 0", zero);
	tlb_op(TLB_V4_D_FULL | TLB_V6_D_FULL, "c8, c6, 0", zero);
	tlb_op(TLB_V4_I_FULL | TLB_V6_I_FULL, "c8, c5, 0", zero);
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_all(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	अगर (tlb_flag(TLB_WB))
		dsb(nshst);

	__local_flush_tlb_all();
	tlb_op(TLB_V7_UIS_FULL, "c8, c7, 0", zero);

	अगर (tlb_flag(TLB_BARRIER)) अणु
		dsb(nsh);
		isb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_all(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	अगर (tlb_flag(TLB_WB))
		dsb(ishst);

	__local_flush_tlb_all();
	tlb_op(TLB_V7_UIS_FULL, "c8, c3, 0", zero);

	अगर (tlb_flag(TLB_BARRIER)) अणु
		dsb(ish);
		isb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर पूर्णांक asid = ASID(mm);
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	अगर (possible_tlb_flags & (TLB_V4_U_FULL|TLB_V4_D_FULL|TLB_V4_I_FULL)) अणु
		अगर (cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm))) अणु
			tlb_op(TLB_V4_U_FULL, "c8, c7, 0", zero);
			tlb_op(TLB_V4_D_FULL, "c8, c6, 0", zero);
			tlb_op(TLB_V4_I_FULL, "c8, c5, 0", zero);
		पूर्ण
	पूर्ण

	tlb_op(TLB_V6_U_ASID, "c8, c7, 2", asid);
	tlb_op(TLB_V6_D_ASID, "c8, c6, 2", asid);
	tlb_op(TLB_V6_I_ASID, "c8, c5, 2", asid);
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	स्थिर पूर्णांक asid = ASID(mm);
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	अगर (tlb_flag(TLB_WB))
		dsb(nshst);

	__local_flush_tlb_mm(mm);
	tlb_op(TLB_V7_UIS_ASID, "c8, c7, 2", asid);

	अगर (tlb_flag(TLB_BARRIER))
		dsb(nsh);
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	अगर (tlb_flag(TLB_WB))
		dsb(ishst);

	__local_flush_tlb_mm(mm);
#अगर_घोषित CONFIG_ARM_ERRATA_720789
	tlb_op(TLB_V7_UIS_ASID, "c8, c3, 0", 0);
#अन्यथा
	tlb_op(TLB_V7_UIS_ASID, "c8, c3, 2", ASID(mm));
#पूर्ण_अगर

	अगर (tlb_flag(TLB_BARRIER))
		dsb(ish);
पूर्ण

अटल अंतरभूत व्योम
__local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	uaddr = (uaddr & PAGE_MASK) | ASID(vma->vm_mm);

	अगर (possible_tlb_flags & (TLB_V4_U_PAGE|TLB_V4_D_PAGE|TLB_V4_I_PAGE|TLB_V4_I_FULL) &&
	    cpumask_test_cpu(smp_processor_id(), mm_cpumask(vma->vm_mm))) अणु
		tlb_op(TLB_V4_U_PAGE, "c8, c7, 1", uaddr);
		tlb_op(TLB_V4_D_PAGE, "c8, c6, 1", uaddr);
		tlb_op(TLB_V4_I_PAGE, "c8, c5, 1", uaddr);
		अगर (!tlb_flag(TLB_V4_I_PAGE) && tlb_flag(TLB_V4_I_FULL))
			यंत्र("mcr p15, 0, %0, c8, c5, 0" : : "r" (zero) : "cc");
	पूर्ण

	tlb_op(TLB_V6_U_PAGE, "c8, c7, 1", uaddr);
	tlb_op(TLB_V6_D_PAGE, "c8, c6, 1", uaddr);
	tlb_op(TLB_V6_I_PAGE, "c8, c5, 1", uaddr);
पूर्ण

अटल अंतरभूत व्योम
local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	uaddr = (uaddr & PAGE_MASK) | ASID(vma->vm_mm);

	अगर (tlb_flag(TLB_WB))
		dsb(nshst);

	__local_flush_tlb_page(vma, uaddr);
	tlb_op(TLB_V7_UIS_PAGE, "c8, c7, 1", uaddr);

	अगर (tlb_flag(TLB_BARRIER))
		dsb(nsh);
पूर्ण

अटल अंतरभूत व्योम
__flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	uaddr = (uaddr & PAGE_MASK) | ASID(vma->vm_mm);

	अगर (tlb_flag(TLB_WB))
		dsb(ishst);

	__local_flush_tlb_page(vma, uaddr);
#अगर_घोषित CONFIG_ARM_ERRATA_720789
	tlb_op(TLB_V7_UIS_PAGE, "c8, c3, 3", uaddr & PAGE_MASK);
#अन्यथा
	tlb_op(TLB_V7_UIS_PAGE, "c8, c3, 1", uaddr);
#पूर्ण_अगर

	अगर (tlb_flag(TLB_BARRIER))
		dsb(ish);
पूर्ण

अटल अंतरभूत व्योम __local_flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	tlb_op(TLB_V4_U_PAGE, "c8, c7, 1", kaddr);
	tlb_op(TLB_V4_D_PAGE, "c8, c6, 1", kaddr);
	tlb_op(TLB_V4_I_PAGE, "c8, c5, 1", kaddr);
	अगर (!tlb_flag(TLB_V4_I_PAGE) && tlb_flag(TLB_V4_I_FULL))
		यंत्र("mcr p15, 0, %0, c8, c5, 0" : : "r" (zero) : "cc");

	tlb_op(TLB_V6_U_PAGE, "c8, c7, 1", kaddr);
	tlb_op(TLB_V6_D_PAGE, "c8, c6, 1", kaddr);
	tlb_op(TLB_V6_I_PAGE, "c8, c5, 1", kaddr);
पूर्ण

अटल अंतरभूत व्योम local_flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	kaddr &= PAGE_MASK;

	अगर (tlb_flag(TLB_WB))
		dsb(nshst);

	__local_flush_tlb_kernel_page(kaddr);
	tlb_op(TLB_V7_UIS_PAGE, "c8, c7, 1", kaddr);

	अगर (tlb_flag(TLB_BARRIER)) अणु
		dsb(nsh);
		isb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	kaddr &= PAGE_MASK;

	अगर (tlb_flag(TLB_WB))
		dsb(ishst);

	__local_flush_tlb_kernel_page(kaddr);
	tlb_op(TLB_V7_UIS_PAGE, "c8, c3, 1", kaddr);

	अगर (tlb_flag(TLB_BARRIER)) अणु
		dsb(ish);
		isb();
	पूर्ण
पूर्ण

/*
 * Branch predictor मुख्यtenance is paired with full TLB invalidation, so
 * there is no need क्रम any barriers here.
 */
अटल अंतरभूत व्योम __local_flush_bp_all(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	अगर (tlb_flag(TLB_V6_BP))
		यंत्र("mcr p15, 0, %0, c7, c5, 6" : : "r" (zero));
पूर्ण

अटल अंतरभूत व्योम local_flush_bp_all(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	__local_flush_bp_all();
	अगर (tlb_flag(TLB_V7_UIS_BP))
		यंत्र("mcr p15, 0, %0, c7, c5, 6" : : "r" (zero));
पूर्ण

अटल अंतरभूत व्योम __flush_bp_all(व्योम)
अणु
	स्थिर पूर्णांक zero = 0;
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	__local_flush_bp_all();
	अगर (tlb_flag(TLB_V7_UIS_BP))
		यंत्र("mcr p15, 0, %0, c7, c1, 6" : : "r" (zero));
पूर्ण

/*
 *	flush_pmd_entry
 *
 *	Flush a PMD entry (word aligned, or द्विगुन-word aligned) to
 *	RAM अगर the TLB क्रम the CPU we are running on requires this.
 *	This is typically used when we are creating PMD entries.
 *
 *	clean_pmd_entry
 *
 *	Clean (but करोn't drain the ग_लिखो buffer) अगर the CPU requires
 *	these operations.  This is typically used when we are removing
 *	PMD entries.
 */
अटल अंतरभूत व्योम flush_pmd_entry(व्योम *pmd)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	tlb_op(TLB_DCLEAN, "c7, c10, 1	@ flush_pmd", pmd);
	tlb_l2_op(TLB_L2CLEAN_FR, "c15, c9, 1  @ L2 flush_pmd", pmd);

	अगर (tlb_flag(TLB_WB))
		dsb(ishst);
पूर्ण

अटल अंतरभूत व्योम clean_pmd_entry(व्योम *pmd)
अणु
	स्थिर अचिन्हित पूर्णांक __tlb_flag = __cpu_tlb_flags;

	tlb_op(TLB_DCLEAN, "c7, c10, 1	@ flush_pmd", pmd);
	tlb_l2_op(TLB_L2CLEAN_FR, "c15, c9, 1  @ L2 flush_pmd", pmd);
पूर्ण

#अघोषित tlb_op
#अघोषित tlb_flag
#अघोषित always_tlb_flags
#अघोषित possible_tlb_flags

/*
 * Convert calls to our calling convention.
 */
#घोषणा local_flush_tlb_range(vma,start,end)	__cpu_flush_user_tlb_range(start,end,vma)
#घोषणा local_flush_tlb_kernel_range(s,e)	__cpu_flush_kern_tlb_range(s,e)

#अगर_अघोषित CONFIG_SMP
#घोषणा flush_tlb_all		local_flush_tlb_all
#घोषणा flush_tlb_mm		local_flush_tlb_mm
#घोषणा flush_tlb_page		local_flush_tlb_page
#घोषणा flush_tlb_kernel_page	local_flush_tlb_kernel_page
#घोषणा flush_tlb_range		local_flush_tlb_range
#घोषणा flush_tlb_kernel_range	local_flush_tlb_kernel_range
#घोषणा flush_bp_all		local_flush_bp_all
#अन्यथा
बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr);
बाह्य व्योम flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_bp_all(व्योम);
#पूर्ण_अगर

/*
 * If PG_dcache_clean is not set क्रम the page, we need to ensure that any
 * cache entries क्रम the kernels भव memory range are written
 * back to the page. On ARMv6 and later, the cache coherency is handled via
 * the set_pte_at() function.
 */
#अगर __LINUX_ARM_ARCH__ < 6
बाह्य व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
	pte_t *ptep);
#अन्यथा
अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा update_mmu_cache_pmd(vma, address, pmd) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#या_अगर defined(CONFIG_SMP)	/* !CONFIG_MMU */

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत व्योम local_flush_tlb_all(व्योम)									अणु पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)							अणु पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)			अणु पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr)						अणु पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)	अणु पूर्ण
अटल अंतरभूत व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)				अणु पूर्ण
अटल अंतरभूत व्योम local_flush_bp_all(व्योम)									अणु पूर्ण

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr);
बाह्य व्योम flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_bp_all(व्योम);
#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_ARM_ERRATA_798181
बाह्य व्योम erratum_a15_798181_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम erratum_a15_798181_init(व्योम) अणुपूर्ण
#पूर्ण_अगर
बाह्य bool (*erratum_a15_798181_handler)(व्योम);

अटल अंतरभूत bool erratum_a15_798181(व्योम)
अणु
	अगर (unlikely(IS_ENABLED(CONFIG_ARM_ERRATA_798181) &&
		erratum_a15_798181_handler))
		वापस erratum_a15_798181_handler();
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
