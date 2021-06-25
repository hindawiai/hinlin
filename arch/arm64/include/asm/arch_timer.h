<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/arch_समयr.h
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */
#अगर_अघोषित __ASM_ARCH_TIMER_H
#घोषणा __ASM_ARCH_TIMER_H

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/sysreg.h>

#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#अगर IS_ENABLED(CONFIG_ARM_ARCH_TIMER_OOL_WORKAROUND)
#घोषणा has_erratum_handler(h)						\
	(अणु								\
		स्थिर काष्ठा arch_समयr_erratum_workaround *__wa;	\
		__wa = __this_cpu_पढ़ो(समयr_unstable_counter_workaround); \
		(__wa && __wa->h);					\
	पूर्ण)

#घोषणा erratum_handler(h)						\
	(अणु								\
		स्थिर काष्ठा arch_समयr_erratum_workaround *__wa;	\
		__wa = __this_cpu_पढ़ो(समयr_unstable_counter_workaround); \
		(__wa && __wa->h) ? __wa->h : arch_समयr_##h;		\
	पूर्ण)

#अन्यथा
#घोषणा has_erratum_handler(h)			   false
#घोषणा erratum_handler(h)			   (arch_समयr_##h)
#पूर्ण_अगर

क्रमागत arch_समयr_erratum_match_type अणु
	ate_match_dt,
	ate_match_local_cap_id,
	ate_match_acpi_oem_info,
पूर्ण;

काष्ठा घड़ी_event_device;

काष्ठा arch_समयr_erratum_workaround अणु
	क्रमागत arch_समयr_erratum_match_type match_type;
	स्थिर व्योम *id;
	स्थिर अक्षर *desc;
	u32 (*पढ़ो_cntp_tval_el0)(व्योम);
	u32 (*पढ़ो_cntv_tval_el0)(व्योम);
	u64 (*पढ़ो_cntpct_el0)(व्योम);
	u64 (*पढ़ो_cntvct_el0)(व्योम);
	पूर्णांक (*set_next_event_phys)(अचिन्हित दीर्घ, काष्ठा घड़ी_event_device *);
	पूर्णांक (*set_next_event_virt)(अचिन्हित दीर्घ, काष्ठा घड़ी_event_device *);
	bool disable_compat_vdso;
पूर्ण;

DECLARE_PER_CPU(स्थिर काष्ठा arch_समयr_erratum_workaround *,
		समयr_unstable_counter_workaround);

/* अंतरभूत sysreg accessors that make erratum_handler() work */
अटल अंतरभूत notrace u32 arch_समयr_पढ़ो_cntp_tval_el0(व्योम)
अणु
	वापस पढ़ो_sysreg(cntp_tval_el0);
पूर्ण

अटल अंतरभूत notrace u32 arch_समयr_पढ़ो_cntv_tval_el0(व्योम)
अणु
	वापस पढ़ो_sysreg(cntv_tval_el0);
पूर्ण

अटल अंतरभूत notrace u64 arch_समयr_पढ़ो_cntpct_el0(व्योम)
अणु
	वापस पढ़ो_sysreg(cntpct_el0);
पूर्ण

अटल अंतरभूत notrace u64 arch_समयr_पढ़ो_cntvct_el0(व्योम)
अणु
	वापस पढ़ो_sysreg(cntvct_el0);
पूर्ण

#घोषणा arch_समयr_reg_पढ़ो_stable(reg)					\
	(अणु								\
		u64 _val;						\
									\
		preempt_disable_notrace();				\
		_val = erratum_handler(पढ़ो_ ## reg)();			\
		preempt_enable_notrace();				\
									\
		_val;							\
	पूर्ण)

/*
 * These रेजिस्टर accessors are marked अंतरभूत so the compiler can
 * nicely work out which रेजिस्टर we want, and chuck away the rest of
 * the code.
 */
अटल __always_अंतरभूत
व्योम arch_समयr_reg_ग_लिखो_cp15(पूर्णांक access, क्रमागत arch_समयr_reg reg, u32 val)
अणु
	अगर (access == ARCH_TIMER_PHYS_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			ग_लिखो_sysreg(val, cntp_ctl_el0);
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			ग_लिखो_sysreg(val, cntp_tval_el0);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (access == ARCH_TIMER_VIRT_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			ग_लिखो_sysreg(val, cntv_ctl_el0);
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			ग_लिखो_sysreg(val, cntv_tval_el0);
			अवरोध;
		पूर्ण
	पूर्ण

	isb();
पूर्ण

अटल __always_अंतरभूत
u32 arch_समयr_reg_पढ़ो_cp15(पूर्णांक access, क्रमागत arch_समयr_reg reg)
अणु
	अगर (access == ARCH_TIMER_PHYS_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			वापस पढ़ो_sysreg(cntp_ctl_el0);
		हाल ARCH_TIMER_REG_TVAL:
			वापस arch_समयr_reg_पढ़ो_stable(cntp_tval_el0);
		पूर्ण
	पूर्ण अन्यथा अगर (access == ARCH_TIMER_VIRT_ACCESS) अणु
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			वापस पढ़ो_sysreg(cntv_ctl_el0);
		हाल ARCH_TIMER_REG_TVAL:
			वापस arch_समयr_reg_पढ़ो_stable(cntv_tval_el0);
		पूर्ण
	पूर्ण

	BUG();
पूर्ण

अटल अंतरभूत u32 arch_समयr_get_cntfrq(व्योम)
अणु
	वापस पढ़ो_sysreg(cntfrq_el0);
पूर्ण

अटल अंतरभूत u32 arch_समयr_get_cntkctl(व्योम)
अणु
	वापस पढ़ो_sysreg(cntkctl_el1);
पूर्ण

अटल अंतरभूत व्योम arch_समयr_set_cntkctl(u32 cntkctl)
अणु
	ग_लिखो_sysreg(cntkctl, cntkctl_el1);
	isb();
पूर्ण

अटल __always_अंतरभूत u64 __arch_counter_get_cntpct_stable(व्योम)
अणु
	u64 cnt;

	isb();
	cnt = arch_समयr_reg_पढ़ो_stable(cntpct_el0);
	arch_counter_enक्रमce_ordering(cnt);
	वापस cnt;
पूर्ण

अटल __always_अंतरभूत u64 __arch_counter_get_cntpct(व्योम)
अणु
	u64 cnt;

	isb();
	cnt = पढ़ो_sysreg(cntpct_el0);
	arch_counter_enक्रमce_ordering(cnt);
	वापस cnt;
पूर्ण

अटल __always_अंतरभूत u64 __arch_counter_get_cntvct_stable(व्योम)
अणु
	u64 cnt;

	isb();
	cnt = arch_समयr_reg_पढ़ो_stable(cntvct_el0);
	arch_counter_enक्रमce_ordering(cnt);
	वापस cnt;
पूर्ण

अटल __always_अंतरभूत u64 __arch_counter_get_cntvct(व्योम)
अणु
	u64 cnt;

	isb();
	cnt = पढ़ो_sysreg(cntvct_el0);
	arch_counter_enक्रमce_ordering(cnt);
	वापस cnt;
पूर्ण

अटल अंतरभूत पूर्णांक arch_समयr_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम arch_समयr_set_evtstrm_feature(व्योम)
अणु
	cpu_set_named_feature(EVTSTRM);
#अगर_घोषित CONFIG_COMPAT
	compat_elf_hwcap |= COMPAT_HWCAP_EVTSTRM;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool arch_समयr_have_evtstrm_feature(व्योम)
अणु
	वापस cpu_have_named_feature(EVTSTRM);
पूर्ण
#पूर्ण_अगर
