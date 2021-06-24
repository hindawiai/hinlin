<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_MMU_CONTEXT_H
#घोषणा __ALPHA_MMU_CONTEXT_H

/*
 * get a new mmu context..
 *
 * Copyright (C) 1996, Linus Torvalds
 */

#समावेश <linux/mm_types.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र-generic/mm_hooks.h>

/*
 * Force a context reload. This is needed when we change the page
 * table poपूर्णांकer or when we update the ASN of the current process.
 */

/* Don't get पूर्णांकo trouble with dueling __EXTERN_INLINEs.  */
#अगर_अघोषित __EXTERN_INLINE
#समावेश <यंत्र/पन.स>
#पूर्ण_अगर


अटल अंतरभूत अचिन्हित दीर्घ
__reload_thपढ़ो(काष्ठा pcb_काष्ठा *pcb)
अणु
	रेजिस्टर अचिन्हित दीर्घ a0 __यंत्र__("$16");
	रेजिस्टर अचिन्हित दीर्घ v0 __यंत्र__("$0");

	a0 = virt_to_phys(pcb);
	__यंत्र__ __अस्थिर__(
		"call_pal %2 #__reload_thread"
		: "=r"(v0), "=r"(a0)
		: "i"(PAL_swpctx), "r"(a0)
		: "$1", "$22", "$23", "$24", "$25");

	वापस v0;
पूर्ण


/*
 * The maximum ASN's the processor supports.  On the EV4 this is 63
 * but the PAL-code करोesn't actually use this inक्रमmation.  On the
 * EV5 this is 127, and EV6 has 255.
 *
 * On the EV4, the ASNs are more-or-less useless anyway, as they are
 * only used as an icache tag, not क्रम TB entries.  On the EV5 and EV6,
 * ASN's also validate the TB entries, and thus make a lot more sense.
 *
 * The EV4 ASN's don't even match the architecture manual, ugh.  And
 * I quote: "If a processor implements address space numbers (ASNs),
 * and the old PTE has the Address Space Match (ASM) bit clear (ASNs
 * in use) and the Valid bit set, then entries can also effectively be
 * made coherent by assigning a new, unused ASN to the currently
 * running process and not reusing the previous ASN beक्रमe calling the
 * appropriate PALcode routine to invalidate the translation buffer (TB)". 
 *
 * In लघु, the EV4 has a "kind of" ASN capability, but it करोesn't actually
 * work correctly and can thus not be used (explaining the lack of PAL-code
 * support).
 */
#घोषणा EV4_MAX_ASN 63
#घोषणा EV5_MAX_ASN 127
#घोषणा EV6_MAX_ASN 255

#अगर_घोषित CONFIG_ALPHA_GENERIC
# define MAX_ASN	(alpha_mv.max_asn)
#अन्यथा
# अगरdef CONFIG_ALPHA_EV4
#  define MAX_ASN	EV4_MAX_ASN
# elअगर defined(CONFIG_ALPHA_EV5)
#  define MAX_ASN	EV5_MAX_ASN
# अन्यथा
#  define MAX_ASN	EV6_MAX_ASN
# endअगर
#पूर्ण_अगर

/*
 * cpu_last_asn(processor):
 * 63                                            0
 * +-------------+----------------+--------------+
 * | asn version | this processor | hardware asn |
 * +-------------+----------------+--------------+
 */

#समावेश <यंत्र/smp.h>
#अगर_घोषित CONFIG_SMP
#घोषणा cpu_last_asn(cpuid)	(cpu_data[cpuid].last_asn)
#अन्यथा
बाह्य अचिन्हित दीर्घ last_asn;
#घोषणा cpu_last_asn(cpuid)	last_asn
#पूर्ण_अगर /* CONFIG_SMP */

#घोषणा WIDTH_HARDWARE_ASN	8
#घोषणा ASN_FIRST_VERSION (1UL << WIDTH_HARDWARE_ASN)
#घोषणा HARDWARE_ASN_MASK ((1UL << WIDTH_HARDWARE_ASN) - 1)

/*
 * NOTE! The way this is set up, the high bits of the "asn_cache" (and
 * the "mm->context") are the ASN _version_ code. A version of 0 is
 * always considered invalid, so to invalidate another process you only
 * need to करो "p->mm->context = 0".
 *
 * If we need more ASN's than the processor has, we invalidate the old
 * user TLB's (tbiap()) and start a new ASN version. That will स्वतःmatically
 * क्रमce a new asn क्रम any other processes the next समय they want to
 * run.
 */

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __MMU_EXTERN_INLINE
#पूर्ण_अगर

बाह्य अंतरभूत अचिन्हित दीर्घ
__get_new_mm_context(काष्ठा mm_काष्ठा *mm, दीर्घ cpu)
अणु
	अचिन्हित दीर्घ asn = cpu_last_asn(cpu);
	अचिन्हित दीर्घ next = asn + 1;

	अगर ((asn & HARDWARE_ASN_MASK) >= MAX_ASN) अणु
		tbiap();
		imb();
		next = (asn & ~HARDWARE_ASN_MASK) + ASN_FIRST_VERSION;
	पूर्ण
	cpu_last_asn(cpu) = next;
	वापस next;
पूर्ण

__EXTERN_INLINE व्योम
ev5_चयन_mm(काष्ठा mm_काष्ठा *prev_mm, काष्ठा mm_काष्ठा *next_mm,
	      काष्ठा task_काष्ठा *next)
अणु
	/* Check अगर our ASN is of an older version, and thus invalid. */
	अचिन्हित दीर्घ asn;
	अचिन्हित दीर्घ mmc;
	दीर्घ cpu = smp_processor_id();

#अगर_घोषित CONFIG_SMP
	cpu_data[cpu].asn_lock = 1;
	barrier();
#पूर्ण_अगर
	asn = cpu_last_asn(cpu);
	mmc = next_mm->context[cpu];
	अगर ((mmc ^ asn) & ~HARDWARE_ASN_MASK) अणु
		mmc = __get_new_mm_context(next_mm, cpu);
		next_mm->context[cpu] = mmc;
	पूर्ण
#अगर_घोषित CONFIG_SMP
	अन्यथा
		cpu_data[cpu].need_new_asn = 1;
#पूर्ण_अगर

	/* Always update the PCB ASN.  Another thपढ़ो may have allocated
	   a new mm->context (via flush_tlb_mm) without the ASN serial
	   number wrapping.  We have no way to detect when this is needed.  */
	task_thपढ़ो_info(next)->pcb.asn = mmc & HARDWARE_ASN_MASK;
पूर्ण

__EXTERN_INLINE व्योम
ev4_चयन_mm(काष्ठा mm_काष्ठा *prev_mm, काष्ठा mm_काष्ठा *next_mm,
	      काष्ठा task_काष्ठा *next)
अणु
	/* As described, ASN's are broken क्रम TLB usage.  But we can
	   optimize क्रम चयनing between thपढ़ोs -- अगर the mm is
	   unchanged from current we needn't flush.  */
	/* ??? May not be needed because EV4 PALcode recognizes that
	   ASN's are broken and करोes a tbiap itself on swpctx, under
	   the "Must set ASN or flush" rule.  At least this is true
	   क्रम a 1992 SRM, reports Joseph Martin (jmartin@hlo.dec.com).
	   I'm going to leave this here anyway, just to Be Sure.  -- r~  */
	अगर (prev_mm != next_mm)
		tbiap();

	/* Do जारी to allocate ASNs, because we can still use them
	   to aव्योम flushing the icache.  */
	ev5_चयन_mm(prev_mm, next_mm, next);
पूर्ण

बाह्य व्योम __load_new_mm_context(काष्ठा mm_काष्ठा *);

#अगर_घोषित CONFIG_SMP
#घोषणा check_mmu_context()					\
करो अणु								\
	पूर्णांक cpu = smp_processor_id();				\
	cpu_data[cpu].asn_lock = 0;				\
	barrier();						\
	अगर (cpu_data[cpu].need_new_asn) अणु			\
		काष्ठा mm_काष्ठा * mm = current->active_mm;	\
		cpu_data[cpu].need_new_asn = 0;			\
		अगर (!mm->context[cpu])			\
			__load_new_mm_context(mm);		\
	पूर्ण							\
पूर्ण जबतक(0)
#अन्यथा
#घोषणा check_mmu_context()  करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

__EXTERN_INLINE व्योम
ev5_activate_mm(काष्ठा mm_काष्ठा *prev_mm, काष्ठा mm_काष्ठा *next_mm)
अणु
	__load_new_mm_context(next_mm);
पूर्ण

__EXTERN_INLINE व्योम
ev4_activate_mm(काष्ठा mm_काष्ठा *prev_mm, काष्ठा mm_काष्ठा *next_mm)
अणु
	__load_new_mm_context(next_mm);
	tbiap();
पूर्ण

#अगर_घोषित CONFIG_ALPHA_GENERIC
# define चयन_mm(a,b,c)	alpha_mv.mv_चयन_mm((a),(b),(c))
# define activate_mm(x,y)	alpha_mv.mv_activate_mm((x),(y))
#अन्यथा
# अगरdef CONFIG_ALPHA_EV4
#  define चयन_mm(a,b,c)	ev4_चयन_mm((a),(b),(c))
#  define activate_mm(x,y)	ev4_activate_mm((x),(y))
# अन्यथा
#  define चयन_mm(a,b,c)	ev5_चयन_mm((a),(b),(c))
#  define activate_mm(x,y)	ev5_activate_mm((x),(y))
# endअगर
#पूर्ण_अगर

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i)
		mm->context[i] = 0;
	अगर (tsk != current)
		task_thपढ़ो_info(tsk)->pcb.ptbr
		  = ((अचिन्हित दीर्घ)mm->pgd - IDENT_ADDR) >> PAGE_SHIFT;
	वापस 0;
पूर्ण

#घोषणा enter_lazy_tlb enter_lazy_tlb
अटल अंतरभूत व्योम
enter_lazy_tlb(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk)
अणु
	task_thपढ़ो_info(tsk)->pcb.ptbr
	  = ((अचिन्हित दीर्घ)mm->pgd - IDENT_ADDR) >> PAGE_SHIFT;
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#अगर_घोषित __MMU_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __MMU_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __ALPHA_MMU_CONTEXT_H */
