<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_MMU_CONTEXT_32_H
#घोषणा __ASM_SH_MMU_CONTEXT_32_H

#अगर_घोषित CONFIG_CPU_HAS_PTEAEX
अटल अंतरभूत व्योम set_asid(अचिन्हित दीर्घ asid)
अणु
	__raw_ग_लिखोl(asid, MMU_PTEAEX);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_asid(व्योम)
अणु
	वापस __raw_पढ़ोl(MMU_PTEAEX) & MMU_CONTEXT_ASID_MASK;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम set_asid(अचिन्हित दीर्घ asid)
अणु
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__ ("mov.l	%2, %0\n\t"
			      "and	%3, %0\n\t"
			      "or	%1, %0\n\t"
			      "mov.l	%0, %2"
			      : "=&r" (__dummy)
			      : "r" (asid), "m" (__m(MMU_PTEH)),
			        "r" (0xffffff00));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_asid(व्योम)
अणु
	अचिन्हित दीर्घ asid;

	__यंत्र__ __अस्थिर__ ("mov.l	%1, %0"
			      : "=r" (asid)
			      : "m" (__m(MMU_PTEH)));
	asid &= MMU_CONTEXT_ASID_MASK;
	वापस asid;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_HAS_PTEAEX */

/* MMU_TTB is used क्रम optimizing the fault handling. */
अटल अंतरभूत व्योम set_TTB(pgd_t *pgd)
अणु
	__raw_ग_लिखोl((अचिन्हित दीर्घ)pgd, MMU_TTB);
पूर्ण

अटल अंतरभूत pgd_t *get_TTB(व्योम)
अणु
	वापस (pgd_t *)__raw_पढ़ोl(MMU_TTB);
पूर्ण
#पूर्ण_अगर /* __ASM_SH_MMU_CONTEXT_32_H */
