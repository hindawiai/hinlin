<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_TIMEX_H
#घोषणा _ASM_RISCV_TIMEX_H

#समावेश <यंत्र/csr.h>

प्रकार अचिन्हित दीर्घ cycles_t;

#अगर_घोषित CONFIG_RISCV_M_MODE

#समावेश <यंत्र/clपूर्णांक.h>

#अगर_घोषित CONFIG_64BIT
अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस पढ़ोq_relaxed(clपूर्णांक_समय_val);
पूर्ण
#अन्यथा /* !CONFIG_64BIT */
अटल अंतरभूत u32 get_cycles(व्योम)
अणु
	वापस पढ़ोl_relaxed(((u32 *)clपूर्णांक_समय_val));
पूर्ण
#घोषणा get_cycles get_cycles

अटल अंतरभूत u32 get_cycles_hi(व्योम)
अणु
	वापस पढ़ोl_relaxed(((u32 *)clपूर्णांक_समय_val) + 1);
पूर्ण
#घोषणा get_cycles_hi get_cycles_hi
#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * Much like MIPS, we may not have a viable counter to use at an early poपूर्णांक
 * in the boot process. Unक्रमtunately we करोn't have a fallback, so instead
 * we just वापस 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ अक्रमom_get_entropy(व्योम)
अणु
	अगर (unlikely(clपूर्णांक_समय_val == शून्य))
		वापस 0;
	वापस get_cycles();
पूर्ण
#घोषणा अक्रमom_get_entropy()	अक्रमom_get_entropy()

#अन्यथा /* CONFIG_RISCV_M_MODE */

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस csr_पढ़ो(CSR_TIME);
पूर्ण
#घोषणा get_cycles get_cycles

अटल अंतरभूत u32 get_cycles_hi(व्योम)
अणु
	वापस csr_पढ़ो(CSR_TIMEH);
पूर्ण
#घोषणा get_cycles_hi get_cycles_hi

#पूर्ण_अगर /* !CONFIG_RISCV_M_MODE */

#अगर_घोषित CONFIG_64BIT
अटल अंतरभूत u64 get_cycles64(व्योम)
अणु
	वापस get_cycles();
पूर्ण
#अन्यथा /* CONFIG_64BIT */
अटल अंतरभूत u64 get_cycles64(व्योम)
अणु
	u32 hi, lo;

	करो अणु
		hi = get_cycles_hi();
		lo = get_cycles();
	पूर्ण जबतक (hi != get_cycles_hi());

	वापस ((u64)hi << 32) | lo;
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

#घोषणा ARCH_HAS_READ_CURRENT_TIMER
अटल अंतरभूत पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_val)
अणु
	*समयr_val = get_cycles();
	वापस 0;
पूर्ण

बाह्य व्योम समय_init(व्योम);

#पूर्ण_अगर /* _ASM_RISCV_TIMEX_H */
