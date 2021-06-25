<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMARM_ARCH_TIMER_H
#घोषणा __ASMARM_ARCH_TIMER_H

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/hwcap.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#अगर_घोषित CONFIG_ARM_ARCH_TIMER
/* 32bit ARM करोesn't know anything about समयr errata... */
#घोषणा has_erratum_handler(h)		(false)
#घोषणा erratum_handler(h)		(arch_समयr_##h)

पूर्णांक arch_समयr_arch_init(व्योम);

/*
 * These रेजिस्टर accessors are marked अंतरभूत so the compiler can
 * nicely work out which रेजिस्टर we want, and chuck away the rest of
 * the code. At least it करोes so with a recent GCC (4.6.3).
 */
अटल __always_अंतरभूत
व्योम arch_समयr_reg_ग_लिखो_cp15(पूर्णांक access, क्रमागत arch_समयr_reg reg, u32 val)
अणु
	अगर (access == ARCH_TIMER_PHYS_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			यंत्र अस्थिर("mcr p15, 0, %0, c14, c2, 1" : : "r" (val));
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			यंत्र अस्थिर("mcr p15, 0, %0, c14, c2, 0" : : "r" (val));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (access == ARCH_TIMER_VIRT_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			यंत्र अस्थिर("mcr p15, 0, %0, c14, c3, 1" : : "r" (val));
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			यंत्र अस्थिर("mcr p15, 0, %0, c14, c3, 0" : : "r" (val));
			अवरोध;
		पूर्ण
	पूर्ण

	isb();
पूर्ण

अटल __always_अंतरभूत
u32 arch_समयr_reg_पढ़ो_cp15(पूर्णांक access, क्रमागत arch_समयr_reg reg)
अणु
	u32 val = 0;

	अगर (access == ARCH_TIMER_PHYS_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			यंत्र अस्थिर("mrc p15, 0, %0, c14, c2, 1" : "=r" (val));
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			यंत्र अस्थिर("mrc p15, 0, %0, c14, c2, 0" : "=r" (val));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (access == ARCH_TIMER_VIRT_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			यंत्र अस्थिर("mrc p15, 0, %0, c14, c3, 1" : "=r" (val));
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			यंत्र अस्थिर("mrc p15, 0, %0, c14, c3, 0" : "=r" (val));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत u32 arch_समयr_get_cntfrq(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p15, 0, %0, c14, c0, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत u64 __arch_counter_get_cntpct(व्योम)
अणु
	u64 cval;

	isb();
	यंत्र अस्थिर("mrrc p15, 0, %Q0, %R0, c14" : "=r" (cval));
	वापस cval;
पूर्ण

अटल अंतरभूत u64 __arch_counter_get_cntpct_stable(व्योम)
अणु
	वापस __arch_counter_get_cntpct();
पूर्ण

अटल अंतरभूत u64 __arch_counter_get_cntvct(व्योम)
अणु
	u64 cval;

	isb();
	यंत्र अस्थिर("mrrc p15, 1, %Q0, %R0, c14" : "=r" (cval));
	वापस cval;
पूर्ण

अटल अंतरभूत u64 __arch_counter_get_cntvct_stable(व्योम)
अणु
	वापस __arch_counter_get_cntvct();
पूर्ण

अटल अंतरभूत u32 arch_समयr_get_cntkctl(व्योम)
अणु
	u32 cntkctl;
	यंत्र अस्थिर("mrc p15, 0, %0, c14, c1, 0" : "=r" (cntkctl));
	वापस cntkctl;
पूर्ण

अटल अंतरभूत व्योम arch_समयr_set_cntkctl(u32 cntkctl)
अणु
	यंत्र अस्थिर("mcr p15, 0, %0, c14, c1, 0" : : "r" (cntkctl));
	isb();
पूर्ण

अटल अंतरभूत व्योम arch_समयr_set_evtstrm_feature(व्योम)
अणु
	elf_hwcap |= HWCAP_EVTSTRM;
पूर्ण

अटल अंतरभूत bool arch_समयr_have_evtstrm_feature(व्योम)
अणु
	वापस elf_hwcap & HWCAP_EVTSTRM;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
