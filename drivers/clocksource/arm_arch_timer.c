<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/घड़ीsource/arm_arch_समयr.c
 *
 *  Copyright (C) 2011 ARM Ltd.
 *  All Rights Reserved
 */

#घोषणा pr_fmt(fmt) 	"arch_timer: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीsource_ids.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/acpi.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/ptp_kvm.h>

#समावेश <यंत्र/arch_समयr.h>
#समावेश <यंत्र/virt.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#घोषणा CNTTIDR		0x08
#घोषणा CNTTIDR_VIRT(n)	(BIT(1) << ((n) * 4))

#घोषणा CNTACR(n)	(0x40 + ((n) * 4))
#घोषणा CNTACR_RPCT	BIT(0)
#घोषणा CNTACR_RVCT	BIT(1)
#घोषणा CNTACR_RFRQ	BIT(2)
#घोषणा CNTACR_RVOFF	BIT(3)
#घोषणा CNTACR_RWVT	BIT(4)
#घोषणा CNTACR_RWPT	BIT(5)

#घोषणा CNTVCT_LO	0x08
#घोषणा CNTVCT_HI	0x0c
#घोषणा CNTFRQ		0x10
#घोषणा CNTP_TVAL	0x28
#घोषणा CNTP_CTL	0x2c
#घोषणा CNTV_TVAL	0x38
#घोषणा CNTV_CTL	0x3c

अटल अचिन्हित arch_समयrs_present __initdata;

अटल व्योम __iomem *arch_counter_base __ro_after_init;

काष्ठा arch_समयr अणु
	व्योम __iomem *base;
	काष्ठा घड़ी_event_device evt;
पूर्ण;

#घोषणा to_arch_समयr(e) container_of(e, काष्ठा arch_समयr, evt)

अटल u32 arch_समयr_rate __ro_after_init;
u32 arch_समयr_rate1 __ro_after_init;
अटल पूर्णांक arch_समयr_ppi[ARCH_TIMER_MAX_TIMER_PPI] __ro_after_init;

अटल स्थिर अक्षर *arch_समयr_ppi_names[ARCH_TIMER_MAX_TIMER_PPI] = अणु
	[ARCH_TIMER_PHYS_SECURE_PPI]	= "sec-phys",
	[ARCH_TIMER_PHYS_NONSECURE_PPI]	= "phys",
	[ARCH_TIMER_VIRT_PPI]		= "virt",
	[ARCH_TIMER_HYP_PPI]		= "hyp-phys",
	[ARCH_TIMER_HYP_VIRT_PPI]	= "hyp-virt",
पूर्ण;

अटल काष्ठा घड़ी_event_device __percpu *arch_समयr_evt;

अटल क्रमागत arch_समयr_ppi_nr arch_समयr_uses_ppi __ro_after_init = ARCH_TIMER_VIRT_PPI;
अटल bool arch_समयr_c3stop __ro_after_init;
अटल bool arch_समयr_mem_use_भव __ro_after_init;
अटल bool arch_counter_suspend_stop __ro_after_init;
#अगर_घोषित CONFIG_GENERIC_GETTIMखातापूर्णDAY
अटल क्रमागत vdso_घड़ी_mode vdso_शेष = VDSO_CLOCKMODE_ARCHTIMER;
#अन्यथा
अटल क्रमागत vdso_घड़ी_mode vdso_शेष = VDSO_CLOCKMODE_NONE;
#पूर्ण_अगर /* CONFIG_GENERIC_GETTIMखातापूर्णDAY */

अटल cpumask_t evtstrm_available = CPU_MASK_NONE;
अटल bool evtstrm_enable __ro_after_init = IS_ENABLED(CONFIG_ARM_ARCH_TIMER_EVTSTREAM);

अटल पूर्णांक __init early_evtstrm_cfg(अक्षर *buf)
अणु
	वापस strtobool(buf, &evtstrm_enable);
पूर्ण
early_param("clocksource.arm_arch_timer.evtstrm", early_evtstrm_cfg);

/*
 * Architected प्रणाली समयr support.
 */

अटल __always_अंतरभूत
व्योम arch_समयr_reg_ग_लिखो(पूर्णांक access, क्रमागत arch_समयr_reg reg, u32 val,
			  काष्ठा घड़ी_event_device *clk)
अणु
	अगर (access == ARCH_TIMER_MEM_PHYS_ACCESS) अणु
		काष्ठा arch_समयr *समयr = to_arch_समयr(clk);
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			ग_लिखोl_relaxed(val, समयr->base + CNTP_CTL);
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			ग_लिखोl_relaxed(val, समयr->base + CNTP_TVAL);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (access == ARCH_TIMER_MEM_VIRT_ACCESS) अणु
		काष्ठा arch_समयr *समयr = to_arch_समयr(clk);
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			ग_लिखोl_relaxed(val, समयr->base + CNTV_CTL);
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			ग_लिखोl_relaxed(val, समयr->base + CNTV_TVAL);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		arch_समयr_reg_ग_लिखो_cp15(access, reg, val);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत
u32 arch_समयr_reg_पढ़ो(पूर्णांक access, क्रमागत arch_समयr_reg reg,
			काष्ठा घड़ी_event_device *clk)
अणु
	u32 val;

	अगर (access == ARCH_TIMER_MEM_PHYS_ACCESS) अणु
		काष्ठा arch_समयr *समयr = to_arch_समयr(clk);
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			val = पढ़ोl_relaxed(समयr->base + CNTP_CTL);
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			val = पढ़ोl_relaxed(समयr->base + CNTP_TVAL);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (access == ARCH_TIMER_MEM_VIRT_ACCESS) अणु
		काष्ठा arch_समयr *समयr = to_arch_समयr(clk);
		चयन (reg) अणु
		हाल ARCH_TIMER_REG_CTRL:
			val = पढ़ोl_relaxed(समयr->base + CNTV_CTL);
			अवरोध;
		हाल ARCH_TIMER_REG_TVAL:
			val = पढ़ोl_relaxed(समयr->base + CNTV_TVAL);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = arch_समयr_reg_पढ़ो_cp15(access, reg);
	पूर्ण

	वापस val;
पूर्ण

अटल notrace u64 arch_counter_get_cntpct_stable(व्योम)
अणु
	वापस __arch_counter_get_cntpct_stable();
पूर्ण

अटल notrace u64 arch_counter_get_cntpct(व्योम)
अणु
	वापस __arch_counter_get_cntpct();
पूर्ण

अटल notrace u64 arch_counter_get_cntvct_stable(व्योम)
अणु
	वापस __arch_counter_get_cntvct_stable();
पूर्ण

अटल notrace u64 arch_counter_get_cntvct(व्योम)
अणु
	वापस __arch_counter_get_cntvct();
पूर्ण

/*
 * Default to cp15 based access because arm64 uses this function क्रम
 * sched_घड़ी() beक्रमe DT is probed and the cp15 method is guaranteed
 * to exist on arm64. arm करोesn't use this beक्रमe DT is probed so even
 * अगर we करोn't have the cp15 accessors we won't have a problem.
 */
u64 (*arch_समयr_पढ़ो_counter)(व्योम) __ro_after_init = arch_counter_get_cntvct;
EXPORT_SYMBOL_GPL(arch_समयr_पढ़ो_counter);

अटल u64 arch_counter_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस arch_समयr_पढ़ो_counter();
पूर्ण

अटल u64 arch_counter_पढ़ो_cc(स्थिर काष्ठा cyclecounter *cc)
अणु
	वापस arch_समयr_पढ़ो_counter();
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_counter = अणु
	.name	= "arch_sys_counter",
	.id	= CSID_ARM_ARCH_COUNTER,
	.rating	= 400,
	.पढ़ो	= arch_counter_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(56),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल काष्ठा cyclecounter cyclecounter __ro_after_init = अणु
	.पढ़ो	= arch_counter_पढ़ो_cc,
	.mask	= CLOCKSOURCE_MASK(56),
पूर्ण;

काष्ठा ate_acpi_oem_info अणु
	अक्षर oem_id[ACPI_OEM_ID_SIZE + 1];
	अक्षर oem_table_id[ACPI_OEM_TABLE_ID_SIZE + 1];
	u32 oem_revision;
पूर्ण;

#अगर_घोषित CONFIG_FSL_ERRATUM_A008585
/*
 * The number of retries is an arbitrary value well beyond the highest number
 * of iterations the loop has been observed to take.
 */
#घोषणा __fsl_a008585_पढ़ो_reg(reg) (अणु			\
	u64 _old, _new;					\
	पूर्णांक _retries = 200;				\
							\
	करो अणु						\
		_old = पढ़ो_sysreg(reg);		\
		_new = पढ़ो_sysreg(reg);		\
		_retries--;				\
	पूर्ण जबतक (unlikely(_old != _new) && _retries);	\
							\
	WARN_ON_ONCE(!_retries);			\
	_new;						\
पूर्ण)

अटल u32 notrace fsl_a008585_पढ़ो_cntp_tval_el0(व्योम)
अणु
	वापस __fsl_a008585_पढ़ो_reg(cntp_tval_el0);
पूर्ण

अटल u32 notrace fsl_a008585_पढ़ो_cntv_tval_el0(व्योम)
अणु
	वापस __fsl_a008585_पढ़ो_reg(cntv_tval_el0);
पूर्ण

अटल u64 notrace fsl_a008585_पढ़ो_cntpct_el0(व्योम)
अणु
	वापस __fsl_a008585_पढ़ो_reg(cntpct_el0);
पूर्ण

अटल u64 notrace fsl_a008585_पढ़ो_cntvct_el0(व्योम)
अणु
	वापस __fsl_a008585_पढ़ो_reg(cntvct_el0);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HISILICON_ERRATUM_161010101
/*
 * Verअगरy whether the value of the second पढ़ो is larger than the first by
 * less than 32 is the only way to confirm the value is correct, so clear the
 * lower 5 bits to check whether the dअगरference is greater than 32 or not.
 * Theoretically the erratum should not occur more than twice in succession
 * when पढ़ोing the प्रणाली counter, but it is possible that some पूर्णांकerrupts
 * may lead to more than twice पढ़ो errors, triggering the warning, so setting
 * the number of retries far beyond the number of iterations the loop has been
 * observed to take.
 */
#घोषणा __hisi_161010101_पढ़ो_reg(reg) (अणु				\
	u64 _old, _new;						\
	पूर्णांक _retries = 50;					\
								\
	करो अणु							\
		_old = पढ़ो_sysreg(reg);			\
		_new = पढ़ो_sysreg(reg);			\
		_retries--;					\
	पूर्ण जबतक (unlikely((_new - _old) >> 5) && _retries);	\
								\
	WARN_ON_ONCE(!_retries);				\
	_new;							\
पूर्ण)

अटल u32 notrace hisi_161010101_पढ़ो_cntp_tval_el0(व्योम)
अणु
	वापस __hisi_161010101_पढ़ो_reg(cntp_tval_el0);
पूर्ण

अटल u32 notrace hisi_161010101_पढ़ो_cntv_tval_el0(व्योम)
अणु
	वापस __hisi_161010101_पढ़ो_reg(cntv_tval_el0);
पूर्ण

अटल u64 notrace hisi_161010101_पढ़ो_cntpct_el0(व्योम)
अणु
	वापस __hisi_161010101_पढ़ो_reg(cntpct_el0);
पूर्ण

अटल u64 notrace hisi_161010101_पढ़ो_cntvct_el0(व्योम)
अणु
	वापस __hisi_161010101_पढ़ो_reg(cntvct_el0);
पूर्ण

अटल काष्ठा ate_acpi_oem_info hisi_161010101_oem_info[] = अणु
	/*
	 * Note that trailing spaces are required to properly match
	 * the OEM table inक्रमmation.
	 */
	अणु
		.oem_id		= "HISI  ",
		.oem_table_id	= "HIP05   ",
		.oem_revision	= 0,
	पूर्ण,
	अणु
		.oem_id		= "HISI  ",
		.oem_table_id	= "HIP06   ",
		.oem_revision	= 0,
	पूर्ण,
	अणु
		.oem_id		= "HISI  ",
		.oem_table_id	= "HIP07   ",
		.oem_revision	= 0,
	पूर्ण,
	अणु /* Sentinel indicating the end of the OEM array */ पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_ERRATUM_858921
अटल u64 notrace arm64_858921_पढ़ो_cntpct_el0(व्योम)
अणु
	u64 old, new;

	old = पढ़ो_sysreg(cntpct_el0);
	new = पढ़ो_sysreg(cntpct_el0);
	वापस (((old ^ new) >> 32) & 1) ? old : new;
पूर्ण

अटल u64 notrace arm64_858921_पढ़ो_cntvct_el0(व्योम)
अणु
	u64 old, new;

	old = पढ़ो_sysreg(cntvct_el0);
	new = पढ़ो_sysreg(cntvct_el0);
	वापस (((old ^ new) >> 32) & 1) ? old : new;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUN50I_ERRATUM_UNKNOWN1
/*
 * The low bits of the counter रेजिस्टरs are indeterminate जबतक bit 10 or
 * greater is rolling over. Since the counter value can jump both backward
 * (7ff -> 000 -> 800) and क्रमward (7ff -> fff -> 800), ignore रेजिस्टर values
 * with all ones or all zeros in the low bits. Bound the loop by the maximum
 * number of CPU cycles in 3 consecutive 24 MHz counter periods.
 */
#घोषणा __sun50i_a64_पढ़ो_reg(reg) (अणु					\
	u64 _val;							\
	पूर्णांक _retries = 150;						\
									\
	करो अणु								\
		_val = पढ़ो_sysreg(reg);				\
		_retries--;						\
	पूर्ण जबतक (((_val + 1) & GENMASK(9, 0)) <= 1 && _retries);	\
									\
	WARN_ON_ONCE(!_retries);					\
	_val;								\
पूर्ण)

अटल u64 notrace sun50i_a64_पढ़ो_cntpct_el0(व्योम)
अणु
	वापस __sun50i_a64_पढ़ो_reg(cntpct_el0);
पूर्ण

अटल u64 notrace sun50i_a64_पढ़ो_cntvct_el0(व्योम)
अणु
	वापस __sun50i_a64_पढ़ो_reg(cntvct_el0);
पूर्ण

अटल u32 notrace sun50i_a64_पढ़ो_cntp_tval_el0(व्योम)
अणु
	वापस पढ़ो_sysreg(cntp_cval_el0) - sun50i_a64_पढ़ो_cntpct_el0();
पूर्ण

अटल u32 notrace sun50i_a64_पढ़ो_cntv_tval_el0(व्योम)
अणु
	वापस पढ़ो_sysreg(cntv_cval_el0) - sun50i_a64_पढ़ो_cntvct_el0();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_ARCH_TIMER_OOL_WORKAROUND
DEFINE_PER_CPU(स्थिर काष्ठा arch_समयr_erratum_workaround *, समयr_unstable_counter_workaround);
EXPORT_SYMBOL_GPL(समयr_unstable_counter_workaround);

अटल atomic_t समयr_unstable_counter_workaround_in_use = ATOMIC_INIT(0);

अटल व्योम erratum_set_next_event_tval_generic(स्थिर पूर्णांक access, अचिन्हित दीर्घ evt,
						काष्ठा घड़ी_event_device *clk)
अणु
	अचिन्हित दीर्घ ctrl;
	u64 cval;

	ctrl = arch_समयr_reg_पढ़ो(access, ARCH_TIMER_REG_CTRL, clk);
	ctrl |= ARCH_TIMER_CTRL_ENABLE;
	ctrl &= ~ARCH_TIMER_CTRL_IT_MASK;

	अगर (access == ARCH_TIMER_PHYS_ACCESS) अणु
		cval = evt + arch_counter_get_cntpct_stable();
		ग_लिखो_sysreg(cval, cntp_cval_el0);
	पूर्ण अन्यथा अणु
		cval = evt + arch_counter_get_cntvct_stable();
		ग_लिखो_sysreg(cval, cntv_cval_el0);
	पूर्ण

	arch_समयr_reg_ग_लिखो(access, ARCH_TIMER_REG_CTRL, ctrl, clk);
पूर्ण

अटल __maybe_unused पूर्णांक erratum_set_next_event_tval_virt(अचिन्हित दीर्घ evt,
					    काष्ठा घड़ी_event_device *clk)
अणु
	erratum_set_next_event_tval_generic(ARCH_TIMER_VIRT_ACCESS, evt, clk);
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक erratum_set_next_event_tval_phys(अचिन्हित दीर्घ evt,
					    काष्ठा घड़ी_event_device *clk)
अणु
	erratum_set_next_event_tval_generic(ARCH_TIMER_PHYS_ACCESS, evt, clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा arch_समयr_erratum_workaround ool_workarounds[] = अणु
#अगर_घोषित CONFIG_FSL_ERRATUM_A008585
	अणु
		.match_type = ate_match_dt,
		.id = "fsl,erratum-a008585",
		.desc = "Freescale erratum a005858",
		.पढ़ो_cntp_tval_el0 = fsl_a008585_पढ़ो_cntp_tval_el0,
		.पढ़ो_cntv_tval_el0 = fsl_a008585_पढ़ो_cntv_tval_el0,
		.पढ़ो_cntpct_el0 = fsl_a008585_पढ़ो_cntpct_el0,
		.पढ़ो_cntvct_el0 = fsl_a008585_पढ़ो_cntvct_el0,
		.set_next_event_phys = erratum_set_next_event_tval_phys,
		.set_next_event_virt = erratum_set_next_event_tval_virt,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_HISILICON_ERRATUM_161010101
	अणु
		.match_type = ate_match_dt,
		.id = "hisilicon,erratum-161010101",
		.desc = "HiSilicon erratum 161010101",
		.पढ़ो_cntp_tval_el0 = hisi_161010101_पढ़ो_cntp_tval_el0,
		.पढ़ो_cntv_tval_el0 = hisi_161010101_पढ़ो_cntv_tval_el0,
		.पढ़ो_cntpct_el0 = hisi_161010101_पढ़ो_cntpct_el0,
		.पढ़ो_cntvct_el0 = hisi_161010101_पढ़ो_cntvct_el0,
		.set_next_event_phys = erratum_set_next_event_tval_phys,
		.set_next_event_virt = erratum_set_next_event_tval_virt,
	पूर्ण,
	अणु
		.match_type = ate_match_acpi_oem_info,
		.id = hisi_161010101_oem_info,
		.desc = "HiSilicon erratum 161010101",
		.पढ़ो_cntp_tval_el0 = hisi_161010101_पढ़ो_cntp_tval_el0,
		.पढ़ो_cntv_tval_el0 = hisi_161010101_पढ़ो_cntv_tval_el0,
		.पढ़ो_cntpct_el0 = hisi_161010101_पढ़ो_cntpct_el0,
		.पढ़ो_cntvct_el0 = hisi_161010101_पढ़ो_cntvct_el0,
		.set_next_event_phys = erratum_set_next_event_tval_phys,
		.set_next_event_virt = erratum_set_next_event_tval_virt,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_858921
	अणु
		.match_type = ate_match_local_cap_id,
		.id = (व्योम *)ARM64_WORKAROUND_858921,
		.desc = "ARM erratum 858921",
		.पढ़ो_cntpct_el0 = arm64_858921_पढ़ो_cntpct_el0,
		.पढ़ो_cntvct_el0 = arm64_858921_पढ़ो_cntvct_el0,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN50I_ERRATUM_UNKNOWN1
	अणु
		.match_type = ate_match_dt,
		.id = "allwinner,erratum-unknown1",
		.desc = "Allwinner erratum UNKNOWN1",
		.पढ़ो_cntp_tval_el0 = sun50i_a64_पढ़ो_cntp_tval_el0,
		.पढ़ो_cntv_tval_el0 = sun50i_a64_पढ़ो_cntv_tval_el0,
		.पढ़ो_cntpct_el0 = sun50i_a64_पढ़ो_cntpct_el0,
		.पढ़ो_cntvct_el0 = sun50i_a64_पढ़ो_cntvct_el0,
		.set_next_event_phys = erratum_set_next_event_tval_phys,
		.set_next_event_virt = erratum_set_next_event_tval_virt,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1418040
	अणु
		.match_type = ate_match_local_cap_id,
		.id = (व्योम *)ARM64_WORKAROUND_1418040,
		.desc = "ARM erratum 1418040",
		.disable_compat_vdso = true,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

प्रकार bool (*ate_match_fn_t)(स्थिर काष्ठा arch_समयr_erratum_workaround *,
			       स्थिर व्योम *);

अटल
bool arch_समयr_check_dt_erratum(स्थिर काष्ठा arch_समयr_erratum_workaround *wa,
				 स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा device_node *np = arg;

	वापस of_property_पढ़ो_bool(np, wa->id);
पूर्ण

अटल
bool arch_समयr_check_local_cap_erratum(स्थिर काष्ठा arch_समयr_erratum_workaround *wa,
					स्थिर व्योम *arg)
अणु
	वापस this_cpu_has_cap((uपूर्णांकptr_t)wa->id);
पूर्ण


अटल
bool arch_समयr_check_acpi_oem_erratum(स्थिर काष्ठा arch_समयr_erratum_workaround *wa,
				       स्थिर व्योम *arg)
अणु
	अटल स्थिर काष्ठा ate_acpi_oem_info empty_oem_info = अणुपूर्ण;
	स्थिर काष्ठा ate_acpi_oem_info *info = wa->id;
	स्थिर काष्ठा acpi_table_header *table = arg;

	/* Iterate over the ACPI OEM info array, looking क्रम a match */
	जबतक (स_भेद(info, &empty_oem_info, माप(*info))) अणु
		अगर (!स_भेद(info->oem_id, table->oem_id, ACPI_OEM_ID_SIZE) &&
		    !स_भेद(info->oem_table_id, table->oem_table_id, ACPI_OEM_TABLE_ID_SIZE) &&
		    info->oem_revision == table->oem_revision)
			वापस true;

		info++;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा arch_समयr_erratum_workaround *
arch_समयr_iterate_errata(क्रमागत arch_समयr_erratum_match_type type,
			  ate_match_fn_t match_fn,
			  व्योम *arg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ool_workarounds); i++) अणु
		अगर (ool_workarounds[i].match_type != type)
			जारी;

		अगर (match_fn(&ool_workarounds[i], arg))
			वापस &ool_workarounds[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल
व्योम arch_समयr_enable_workaround(स्थिर काष्ठा arch_समयr_erratum_workaround *wa,
				  bool local)
अणु
	पूर्णांक i;

	अगर (local) अणु
		__this_cpu_ग_लिखो(समयr_unstable_counter_workaround, wa);
	पूर्ण अन्यथा अणु
		क्रम_each_possible_cpu(i)
			per_cpu(समयr_unstable_counter_workaround, i) = wa;
	पूर्ण

	अगर (wa->पढ़ो_cntvct_el0 || wa->पढ़ो_cntpct_el0)
		atomic_set(&समयr_unstable_counter_workaround_in_use, 1);

	/*
	 * Don't use the vdso fastpath अगर errata require using the
	 * out-of-line counter accessor. We may change our mind pretty
	 * late in the game (with a per-CPU erratum, क्रम example), so
	 * change both the शेष value and the vdso itself.
	 */
	अगर (wa->पढ़ो_cntvct_el0) अणु
		घड़ीsource_counter.vdso_घड़ी_mode = VDSO_CLOCKMODE_NONE;
		vdso_शेष = VDSO_CLOCKMODE_NONE;
	पूर्ण अन्यथा अगर (wa->disable_compat_vdso && vdso_शेष != VDSO_CLOCKMODE_NONE) अणु
		vdso_शेष = VDSO_CLOCKMODE_ARCHTIMER_NOCOMPAT;
		घड़ीsource_counter.vdso_घड़ी_mode = vdso_शेष;
	पूर्ण
पूर्ण

अटल व्योम arch_समयr_check_ool_workaround(क्रमागत arch_समयr_erratum_match_type type,
					    व्योम *arg)
अणु
	स्थिर काष्ठा arch_समयr_erratum_workaround *wa, *__wa;
	ate_match_fn_t match_fn = शून्य;
	bool local = false;

	चयन (type) अणु
	हाल ate_match_dt:
		match_fn = arch_समयr_check_dt_erratum;
		अवरोध;
	हाल ate_match_local_cap_id:
		match_fn = arch_समयr_check_local_cap_erratum;
		local = true;
		अवरोध;
	हाल ate_match_acpi_oem_info:
		match_fn = arch_समयr_check_acpi_oem_erratum;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	wa = arch_समयr_iterate_errata(type, match_fn, arg);
	अगर (!wa)
		वापस;

	__wa = __this_cpu_पढ़ो(समयr_unstable_counter_workaround);
	अगर (__wa && wa != __wa)
		pr_warn("Can't enable workaround for %s (clashes with %s\n)",
			wa->desc, __wa->desc);

	अगर (__wa)
		वापस;

	arch_समयr_enable_workaround(wa, local);
	pr_info("Enabling %s workaround for %s\n",
		local ? "local" : "global", wa->desc);
पूर्ण

अटल bool arch_समयr_this_cpu_has_cntvct_wa(व्योम)
अणु
	वापस has_erratum_handler(पढ़ो_cntvct_el0);
पूर्ण

अटल bool arch_समयr_counter_has_wa(व्योम)
अणु
	वापस atomic_पढ़ो(&समयr_unstable_counter_workaround_in_use);
पूर्ण
#अन्यथा
#घोषणा arch_समयr_check_ool_workaround(t,a)		करो अणु पूर्ण जबतक(0)
#घोषणा arch_समयr_this_cpu_has_cntvct_wa()		(अणुfalse;पूर्ण)
#घोषणा arch_समयr_counter_has_wa()			(अणुfalse;पूर्ण)
#पूर्ण_अगर /* CONFIG_ARM_ARCH_TIMER_OOL_WORKAROUND */

अटल __always_अंतरभूत irqवापस_t समयr_handler(स्थिर पूर्णांक access,
					काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ ctrl;

	ctrl = arch_समयr_reg_पढ़ो(access, ARCH_TIMER_REG_CTRL, evt);
	अगर (ctrl & ARCH_TIMER_CTRL_IT_STAT) अणु
		ctrl |= ARCH_TIMER_CTRL_IT_MASK;
		arch_समयr_reg_ग_लिखो(access, ARCH_TIMER_REG_CTRL, ctrl, evt);
		evt->event_handler(evt);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t arch_समयr_handler_virt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	वापस समयr_handler(ARCH_TIMER_VIRT_ACCESS, evt);
पूर्ण

अटल irqवापस_t arch_समयr_handler_phys(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	वापस समयr_handler(ARCH_TIMER_PHYS_ACCESS, evt);
पूर्ण

अटल irqवापस_t arch_समयr_handler_phys_mem(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	वापस समयr_handler(ARCH_TIMER_MEM_PHYS_ACCESS, evt);
पूर्ण

अटल irqवापस_t arch_समयr_handler_virt_mem(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	वापस समयr_handler(ARCH_TIMER_MEM_VIRT_ACCESS, evt);
पूर्ण

अटल __always_अंतरभूत पूर्णांक समयr_shutकरोwn(स्थिर पूर्णांक access,
					  काष्ठा घड़ी_event_device *clk)
अणु
	अचिन्हित दीर्घ ctrl;

	ctrl = arch_समयr_reg_पढ़ो(access, ARCH_TIMER_REG_CTRL, clk);
	ctrl &= ~ARCH_TIMER_CTRL_ENABLE;
	arch_समयr_reg_ग_लिखो(access, ARCH_TIMER_REG_CTRL, ctrl, clk);

	वापस 0;
पूर्ण

अटल पूर्णांक arch_समयr_shutकरोwn_virt(काष्ठा घड़ी_event_device *clk)
अणु
	वापस समयr_shutकरोwn(ARCH_TIMER_VIRT_ACCESS, clk);
पूर्ण

अटल पूर्णांक arch_समयr_shutकरोwn_phys(काष्ठा घड़ी_event_device *clk)
अणु
	वापस समयr_shutकरोwn(ARCH_TIMER_PHYS_ACCESS, clk);
पूर्ण

अटल पूर्णांक arch_समयr_shutकरोwn_virt_mem(काष्ठा घड़ी_event_device *clk)
अणु
	वापस समयr_shutकरोwn(ARCH_TIMER_MEM_VIRT_ACCESS, clk);
पूर्ण

अटल पूर्णांक arch_समयr_shutकरोwn_phys_mem(काष्ठा घड़ी_event_device *clk)
अणु
	वापस समयr_shutकरोwn(ARCH_TIMER_MEM_PHYS_ACCESS, clk);
पूर्ण

अटल __always_अंतरभूत व्योम set_next_event(स्थिर पूर्णांक access, अचिन्हित दीर्घ evt,
					   काष्ठा घड़ी_event_device *clk)
अणु
	अचिन्हित दीर्घ ctrl;
	ctrl = arch_समयr_reg_पढ़ो(access, ARCH_TIMER_REG_CTRL, clk);
	ctrl |= ARCH_TIMER_CTRL_ENABLE;
	ctrl &= ~ARCH_TIMER_CTRL_IT_MASK;
	arch_समयr_reg_ग_लिखो(access, ARCH_TIMER_REG_TVAL, evt, clk);
	arch_समयr_reg_ग_लिखो(access, ARCH_TIMER_REG_CTRL, ctrl, clk);
पूर्ण

अटल पूर्णांक arch_समयr_set_next_event_virt(अचिन्हित दीर्घ evt,
					  काष्ठा घड़ी_event_device *clk)
अणु
	set_next_event(ARCH_TIMER_VIRT_ACCESS, evt, clk);
	वापस 0;
पूर्ण

अटल पूर्णांक arch_समयr_set_next_event_phys(अचिन्हित दीर्घ evt,
					  काष्ठा घड़ी_event_device *clk)
अणु
	set_next_event(ARCH_TIMER_PHYS_ACCESS, evt, clk);
	वापस 0;
पूर्ण

अटल पूर्णांक arch_समयr_set_next_event_virt_mem(अचिन्हित दीर्घ evt,
					      काष्ठा घड़ी_event_device *clk)
अणु
	set_next_event(ARCH_TIMER_MEM_VIRT_ACCESS, evt, clk);
	वापस 0;
पूर्ण

अटल पूर्णांक arch_समयr_set_next_event_phys_mem(अचिन्हित दीर्घ evt,
					      काष्ठा घड़ी_event_device *clk)
अणु
	set_next_event(ARCH_TIMER_MEM_PHYS_ACCESS, evt, clk);
	वापस 0;
पूर्ण

अटल व्योम __arch_समयr_setup(अचिन्हित type,
			       काष्ठा घड़ी_event_device *clk)
अणु
	clk->features = CLOCK_EVT_FEAT_ONESHOT;

	अगर (type == ARCH_TIMER_TYPE_CP15) अणु
		typeof(clk->set_next_event) sne;

		arch_समयr_check_ool_workaround(ate_match_local_cap_id, शून्य);

		अगर (arch_समयr_c3stop)
			clk->features |= CLOCK_EVT_FEAT_C3STOP;
		clk->name = "arch_sys_timer";
		clk->rating = 450;
		clk->cpumask = cpumask_of(smp_processor_id());
		clk->irq = arch_समयr_ppi[arch_समयr_uses_ppi];
		चयन (arch_समयr_uses_ppi) अणु
		हाल ARCH_TIMER_VIRT_PPI:
			clk->set_state_shutकरोwn = arch_समयr_shutकरोwn_virt;
			clk->set_state_oneshot_stopped = arch_समयr_shutकरोwn_virt;
			sne = erratum_handler(set_next_event_virt);
			अवरोध;
		हाल ARCH_TIMER_PHYS_SECURE_PPI:
		हाल ARCH_TIMER_PHYS_NONSECURE_PPI:
		हाल ARCH_TIMER_HYP_PPI:
			clk->set_state_shutकरोwn = arch_समयr_shutकरोwn_phys;
			clk->set_state_oneshot_stopped = arch_समयr_shutकरोwn_phys;
			sne = erratum_handler(set_next_event_phys);
			अवरोध;
		शेष:
			BUG();
		पूर्ण

		clk->set_next_event = sne;
	पूर्ण अन्यथा अणु
		clk->features |= CLOCK_EVT_FEAT_DYNIRQ;
		clk->name = "arch_mem_timer";
		clk->rating = 400;
		clk->cpumask = cpu_possible_mask;
		अगर (arch_समयr_mem_use_भव) अणु
			clk->set_state_shutकरोwn = arch_समयr_shutकरोwn_virt_mem;
			clk->set_state_oneshot_stopped = arch_समयr_shutकरोwn_virt_mem;
			clk->set_next_event =
				arch_समयr_set_next_event_virt_mem;
		पूर्ण अन्यथा अणु
			clk->set_state_shutकरोwn = arch_समयr_shutकरोwn_phys_mem;
			clk->set_state_oneshot_stopped = arch_समयr_shutकरोwn_phys_mem;
			clk->set_next_event =
				arch_समयr_set_next_event_phys_mem;
		पूर्ण
	पूर्ण

	clk->set_state_shutकरोwn(clk);

	घड़ीevents_config_and_रेजिस्टर(clk, arch_समयr_rate, 0xf, 0x7fffffff);
पूर्ण

अटल व्योम arch_समयr_evtstrm_enable(पूर्णांक भागider)
अणु
	u32 cntkctl = arch_समयr_get_cntkctl();

	cntkctl &= ~ARCH_TIMER_EVT_TRIGGER_MASK;
	/* Set the भागider and enable भव event stream */
	cntkctl |= (भागider << ARCH_TIMER_EVT_TRIGGER_SHIFT)
			| ARCH_TIMER_VIRT_EVT_EN;
	arch_समयr_set_cntkctl(cntkctl);
	arch_समयr_set_evtstrm_feature();
	cpumask_set_cpu(smp_processor_id(), &evtstrm_available);
पूर्ण

अटल व्योम arch_समयr_configure_evtstream(व्योम)
अणु
	पूर्णांक evt_stream_भाग, lsb;

	/*
	 * As the event stream can at most be generated at half the frequency
	 * of the counter, use half the frequency when computing the भागider.
	 */
	evt_stream_भाग = arch_समयr_rate / ARCH_TIMER_EVT_STREAM_FREQ / 2;

	/*
	 * Find the बंदst घातer of two to the भागisor. If the adjacent bit
	 * of lsb (last set bit, starts from 0) is set, then we use (lsb + 1).
	 */
	lsb = fls(evt_stream_भाग) - 1;
	अगर (lsb > 0 && (evt_stream_भाग & BIT(lsb - 1)))
		lsb++;

	/* enable event stream */
	arch_समयr_evtstrm_enable(max(0, min(lsb, 15)));
पूर्ण

अटल व्योम arch_counter_set_user_access(व्योम)
अणु
	u32 cntkctl = arch_समयr_get_cntkctl();

	/* Disable user access to the समयrs and both counters */
	/* Also disable भव event stream */
	cntkctl &= ~(ARCH_TIMER_USR_PT_ACCESS_EN
			| ARCH_TIMER_USR_VT_ACCESS_EN
		        | ARCH_TIMER_USR_VCT_ACCESS_EN
			| ARCH_TIMER_VIRT_EVT_EN
			| ARCH_TIMER_USR_PCT_ACCESS_EN);

	/*
	 * Enable user access to the भव counter अगर it करोesn't
	 * need to be workaround. The vdso may have been alपढ़ोy
	 * disabled though.
	 */
	अगर (arch_समयr_this_cpu_has_cntvct_wa())
		pr_info("CPU%d: Trapping CNTVCT access\n", smp_processor_id());
	अन्यथा
		cntkctl |= ARCH_TIMER_USR_VCT_ACCESS_EN;

	arch_समयr_set_cntkctl(cntkctl);
पूर्ण

अटल bool arch_समयr_has_nonsecure_ppi(व्योम)
अणु
	वापस (arch_समयr_uses_ppi == ARCH_TIMER_PHYS_SECURE_PPI &&
		arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI]);
पूर्ण

अटल u32 check_ppi_trigger(पूर्णांक irq)
अणु
	u32 flags = irq_get_trigger_type(irq);

	अगर (flags != IRQF_TRIGGER_HIGH && flags != IRQF_TRIGGER_LOW) अणु
		pr_warn("WARNING: Invalid trigger for IRQ%d, assuming level low\n", irq);
		pr_warn("WARNING: Please fix your firmware\n");
		flags = IRQF_TRIGGER_LOW;
	पूर्ण

	वापस flags;
पूर्ण

अटल पूर्णांक arch_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *clk = this_cpu_ptr(arch_समयr_evt);
	u32 flags;

	__arch_समयr_setup(ARCH_TIMER_TYPE_CP15, clk);

	flags = check_ppi_trigger(arch_समयr_ppi[arch_समयr_uses_ppi]);
	enable_percpu_irq(arch_समयr_ppi[arch_समयr_uses_ppi], flags);

	अगर (arch_समयr_has_nonsecure_ppi()) अणु
		flags = check_ppi_trigger(arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI]);
		enable_percpu_irq(arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI],
				  flags);
	पूर्ण

	arch_counter_set_user_access();
	अगर (evtstrm_enable)
		arch_समयr_configure_evtstream();

	वापस 0;
पूर्ण

अटल पूर्णांक validate_समयr_rate(व्योम)
अणु
	अगर (!arch_समयr_rate)
		वापस -EINVAL;

	/* Arch समयr frequency < 1MHz can cause trouble */
	WARN_ON(arch_समयr_rate < 1000000);

	वापस 0;
पूर्ण

/*
 * For historical reasons, when probing with DT we use whichever (non-zero)
 * rate was probed first, and करोn't verअगरy that others match. If the first node
 * probed has a घड़ी-frequency property, this overrides the HW रेजिस्टर.
 */
अटल व्योम __init arch_समयr_of_configure_rate(u32 rate, काष्ठा device_node *np)
अणु
	/* Who has more than one independent प्रणाली counter? */
	अगर (arch_समयr_rate)
		वापस;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &arch_समयr_rate))
		arch_समयr_rate = rate;

	/* Check the समयr frequency. */
	अगर (validate_समयr_rate())
		pr_warn("frequency not available\n");
पूर्ण

अटल व्योम __init arch_समयr_banner(अचिन्हित type)
अणु
	pr_info("%s%s%s timer(s) running at %lu.%02luMHz (%s%s%s).\n",
		type & ARCH_TIMER_TYPE_CP15 ? "cp15" : "",
		type == (ARCH_TIMER_TYPE_CP15 | ARCH_TIMER_TYPE_MEM) ?
			" and " : "",
		type & ARCH_TIMER_TYPE_MEM ? "mmio" : "",
		(अचिन्हित दीर्घ)arch_समयr_rate / 1000000,
		(अचिन्हित दीर्घ)(arch_समयr_rate / 10000) % 100,
		type & ARCH_TIMER_TYPE_CP15 ?
			(arch_समयr_uses_ppi == ARCH_TIMER_VIRT_PPI) ? "virt" : "phys" :
			"",
		type == (ARCH_TIMER_TYPE_CP15 | ARCH_TIMER_TYPE_MEM) ? "/" : "",
		type & ARCH_TIMER_TYPE_MEM ?
			arch_समयr_mem_use_भव ? "virt" : "phys" :
			"");
पूर्ण

u32 arch_समयr_get_rate(व्योम)
अणु
	वापस arch_समयr_rate;
पूर्ण

bool arch_समयr_evtstrm_available(व्योम)
अणु
	/*
	 * We might get called from a preemptible context. This is fine
	 * because availability of the event stream should be always the same
	 * क्रम a preemptible context and context where we might resume a task.
	 */
	वापस cpumask_test_cpu(raw_smp_processor_id(), &evtstrm_available);
पूर्ण

अटल u64 arch_counter_get_cntvct_mem(व्योम)
अणु
	u32 vct_lo, vct_hi, पंचांगp_hi;

	करो अणु
		vct_hi = पढ़ोl_relaxed(arch_counter_base + CNTVCT_HI);
		vct_lo = पढ़ोl_relaxed(arch_counter_base + CNTVCT_LO);
		पंचांगp_hi = पढ़ोl_relaxed(arch_counter_base + CNTVCT_HI);
	पूर्ण जबतक (vct_hi != पंचांगp_hi);

	वापस ((u64) vct_hi << 32) | vct_lo;
पूर्ण

अटल काष्ठा arch_समयr_kvm_info arch_समयr_kvm_info;

काष्ठा arch_समयr_kvm_info *arch_समयr_get_kvm_info(व्योम)
अणु
	वापस &arch_समयr_kvm_info;
पूर्ण

अटल व्योम __init arch_counter_रेजिस्टर(अचिन्हित type)
अणु
	u64 start_count;

	/* Register the CP15 based counter अगर we have one */
	अगर (type & ARCH_TIMER_TYPE_CP15) अणु
		u64 (*rd)(व्योम);

		अगर ((IS_ENABLED(CONFIG_ARM64) && !is_hyp_mode_available()) ||
		    arch_समयr_uses_ppi == ARCH_TIMER_VIRT_PPI) अणु
			अगर (arch_समयr_counter_has_wa())
				rd = arch_counter_get_cntvct_stable;
			अन्यथा
				rd = arch_counter_get_cntvct;
		पूर्ण अन्यथा अणु
			अगर (arch_समयr_counter_has_wa())
				rd = arch_counter_get_cntpct_stable;
			अन्यथा
				rd = arch_counter_get_cntpct;
		पूर्ण

		arch_समयr_पढ़ो_counter = rd;
		घड़ीsource_counter.vdso_घड़ी_mode = vdso_शेष;
	पूर्ण अन्यथा अणु
		arch_समयr_पढ़ो_counter = arch_counter_get_cntvct_mem;
	पूर्ण

	अगर (!arch_counter_suspend_stop)
		घड़ीsource_counter.flags |= CLOCK_SOURCE_SUSPEND_NONSTOP;
	start_count = arch_समयr_पढ़ो_counter();
	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_counter, arch_समयr_rate);
	cyclecounter.mult = घड़ीsource_counter.mult;
	cyclecounter.shअगरt = घड़ीsource_counter.shअगरt;
	समयcounter_init(&arch_समयr_kvm_info.समयcounter,
			 &cyclecounter, start_count);

	/* 56 bits minimum, so we assume worst हाल rollover */
	sched_घड़ी_रेजिस्टर(arch_समयr_पढ़ो_counter, 56, arch_समयr_rate);
पूर्ण

अटल व्योम arch_समयr_stop(काष्ठा घड़ी_event_device *clk)
अणु
	pr_debug("disable IRQ%d cpu #%d\n", clk->irq, smp_processor_id());

	disable_percpu_irq(arch_समयr_ppi[arch_समयr_uses_ppi]);
	अगर (arch_समयr_has_nonsecure_ppi())
		disable_percpu_irq(arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI]);

	clk->set_state_shutकरोwn(clk);
पूर्ण

अटल पूर्णांक arch_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *clk = this_cpu_ptr(arch_समयr_evt);

	cpumask_clear_cpu(smp_processor_id(), &evtstrm_available);

	arch_समयr_stop(clk);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, saved_cntkctl);
अटल पूर्णांक arch_समयr_cpu_pm_notअगरy(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ action, व्योम *hcpu)
अणु
	अगर (action == CPU_PM_ENTER) अणु
		__this_cpu_ग_लिखो(saved_cntkctl, arch_समयr_get_cntkctl());

		cpumask_clear_cpu(smp_processor_id(), &evtstrm_available);
	पूर्ण अन्यथा अगर (action == CPU_PM_ENTER_FAILED || action == CPU_PM_EXIT) अणु
		arch_समयr_set_cntkctl(__this_cpu_पढ़ो(saved_cntkctl));

		अगर (arch_समयr_have_evtstrm_feature())
			cpumask_set_cpu(smp_processor_id(), &evtstrm_available);
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block arch_समयr_cpu_pm_notअगरier = अणु
	.notअगरier_call = arch_समयr_cpu_pm_notअगरy,
पूर्ण;

अटल पूर्णांक __init arch_समयr_cpu_pm_init(व्योम)
अणु
	वापस cpu_pm_रेजिस्टर_notअगरier(&arch_समयr_cpu_pm_notअगरier);
पूर्ण

अटल व्योम __init arch_समयr_cpu_pm_deinit(व्योम)
अणु
	WARN_ON(cpu_pm_unरेजिस्टर_notअगरier(&arch_समयr_cpu_pm_notअगरier));
पूर्ण

#अन्यथा
अटल पूर्णांक __init arch_समयr_cpu_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __init arch_समयr_cpu_pm_deinit(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init arch_समयr_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक ppi;

	arch_समयr_evt = alloc_percpu(काष्ठा घड़ी_event_device);
	अगर (!arch_समयr_evt) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	ppi = arch_समयr_ppi[arch_समयr_uses_ppi];
	चयन (arch_समयr_uses_ppi) अणु
	हाल ARCH_TIMER_VIRT_PPI:
		err = request_percpu_irq(ppi, arch_समयr_handler_virt,
					 "arch_timer", arch_समयr_evt);
		अवरोध;
	हाल ARCH_TIMER_PHYS_SECURE_PPI:
	हाल ARCH_TIMER_PHYS_NONSECURE_PPI:
		err = request_percpu_irq(ppi, arch_समयr_handler_phys,
					 "arch_timer", arch_समयr_evt);
		अगर (!err && arch_समयr_has_nonsecure_ppi()) अणु
			ppi = arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI];
			err = request_percpu_irq(ppi, arch_समयr_handler_phys,
						 "arch_timer", arch_समयr_evt);
			अगर (err)
				मुक्त_percpu_irq(arch_समयr_ppi[ARCH_TIMER_PHYS_SECURE_PPI],
						arch_समयr_evt);
		पूर्ण
		अवरोध;
	हाल ARCH_TIMER_HYP_PPI:
		err = request_percpu_irq(ppi, arch_समयr_handler_phys,
					 "arch_timer", arch_समयr_evt);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (err) अणु
		pr_err("can't register interrupt %d (%d)\n", ppi, err);
		जाओ out_मुक्त;
	पूर्ण

	err = arch_समयr_cpu_pm_init();
	अगर (err)
		जाओ out_unreg_notअगरy;

	/* Register and immediately configure the समयr on the boot CPU */
	err = cpuhp_setup_state(CPUHP_AP_ARM_ARCH_TIMER_STARTING,
				"clockevents/arm/arch_timer:starting",
				arch_समयr_starting_cpu, arch_समयr_dying_cpu);
	अगर (err)
		जाओ out_unreg_cpupm;
	वापस 0;

out_unreg_cpupm:
	arch_समयr_cpu_pm_deinit();

out_unreg_notअगरy:
	मुक्त_percpu_irq(arch_समयr_ppi[arch_समयr_uses_ppi], arch_समयr_evt);
	अगर (arch_समयr_has_nonsecure_ppi())
		मुक्त_percpu_irq(arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI],
				arch_समयr_evt);

out_मुक्त:
	मुक्त_percpu(arch_समयr_evt);
out:
	वापस err;
पूर्ण

अटल पूर्णांक __init arch_समयr_mem_रेजिस्टर(व्योम __iomem *base, अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक ret;
	irq_handler_t func;
	काष्ठा arch_समयr *t;

	t = kzalloc(माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस -ENOMEM;

	t->base = base;
	t->evt.irq = irq;
	__arch_समयr_setup(ARCH_TIMER_TYPE_MEM, &t->evt);

	अगर (arch_समयr_mem_use_भव)
		func = arch_समयr_handler_virt_mem;
	अन्यथा
		func = arch_समयr_handler_phys_mem;

	ret = request_irq(irq, func, IRQF_TIMER, "arch_mem_timer", &t->evt);
	अगर (ret) अणु
		pr_err("Failed to request mem timer irq\n");
		kमुक्त(t);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id arch_समयr_of_match[] __initस्थिर = अणु
	अणु .compatible   = "arm,armv7-timer",    पूर्ण,
	अणु .compatible   = "arm,armv8-timer",    पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id arch_समयr_mem_of_match[] __initस्थिर = अणु
	अणु .compatible   = "arm,armv7-timer-mem", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल bool __init arch_समयr_needs_of_probing(व्योम)
अणु
	काष्ठा device_node *dn;
	bool needs_probing = false;
	अचिन्हित पूर्णांक mask = ARCH_TIMER_TYPE_CP15 | ARCH_TIMER_TYPE_MEM;

	/* We have two समयrs, and both device-tree nodes are probed. */
	अगर ((arch_समयrs_present & mask) == mask)
		वापस false;

	/*
	 * Only one type of समयr is probed,
	 * check अगर we have another type of समयr node in device-tree.
	 */
	अगर (arch_समयrs_present & ARCH_TIMER_TYPE_CP15)
		dn = of_find_matching_node(शून्य, arch_समयr_mem_of_match);
	अन्यथा
		dn = of_find_matching_node(शून्य, arch_समयr_of_match);

	अगर (dn && of_device_is_available(dn))
		needs_probing = true;

	of_node_put(dn);

	वापस needs_probing;
पूर्ण

अटल पूर्णांक __init arch_समयr_common_init(व्योम)
अणु
	arch_समयr_banner(arch_समयrs_present);
	arch_counter_रेजिस्टर(arch_समयrs_present);
	वापस arch_समयr_arch_init();
पूर्ण

/**
 * arch_समयr_select_ppi() - Select suitable PPI क्रम the current प्रणाली.
 *
 * If HYP mode is available, we know that the physical समयr
 * has been configured to be accessible from PL1. Use it, so
 * that a guest can use the भव समयr instead.
 *
 * On ARMv8.1 with VH extensions, the kernel runs in HYP. VHE
 * accesses to CNTP_*_EL1 रेजिस्टरs are silently redirected to
 * their CNTHP_*_EL2 counterparts, and use a dअगरferent PPI
 * number.
 *
 * If no पूर्णांकerrupt provided क्रम भव समयr, we'll have to
 * stick to the physical समयr. It'd better be accessible...
 * For arm64 we never use the secure पूर्णांकerrupt.
 *
 * Return: a suitable PPI type क्रम the current प्रणाली.
 */
अटल क्रमागत arch_समयr_ppi_nr __init arch_समयr_select_ppi(व्योम)
अणु
	अगर (is_kernel_in_hyp_mode())
		वापस ARCH_TIMER_HYP_PPI;

	अगर (!is_hyp_mode_available() && arch_समयr_ppi[ARCH_TIMER_VIRT_PPI])
		वापस ARCH_TIMER_VIRT_PPI;

	अगर (IS_ENABLED(CONFIG_ARM64))
		वापस ARCH_TIMER_PHYS_NONSECURE_PPI;

	वापस ARCH_TIMER_PHYS_SECURE_PPI;
पूर्ण

अटल व्योम __init arch_समयr_populate_kvm_info(व्योम)
अणु
	arch_समयr_kvm_info.भव_irq = arch_समयr_ppi[ARCH_TIMER_VIRT_PPI];
	अगर (is_kernel_in_hyp_mode())
		arch_समयr_kvm_info.physical_irq = arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI];
पूर्ण

अटल पूर्णांक __init arch_समयr_of_init(काष्ठा device_node *np)
अणु
	पूर्णांक i, irq, ret;
	u32 rate;
	bool has_names;

	अगर (arch_समयrs_present & ARCH_TIMER_TYPE_CP15) अणु
		pr_warn("multiple nodes in dt, skipping\n");
		वापस 0;
	पूर्ण

	arch_समयrs_present |= ARCH_TIMER_TYPE_CP15;

	has_names = of_property_पढ़ो_bool(np, "interrupt-names");

	क्रम (i = ARCH_TIMER_PHYS_SECURE_PPI; i < ARCH_TIMER_MAX_TIMER_PPI; i++) अणु
		अगर (has_names)
			irq = of_irq_get_byname(np, arch_समयr_ppi_names[i]);
		अन्यथा
			irq = of_irq_get(np, i);
		अगर (irq > 0)
			arch_समयr_ppi[i] = irq;
	पूर्ण

	arch_समयr_populate_kvm_info();

	rate = arch_समयr_get_cntfrq();
	arch_समयr_of_configure_rate(rate, np);

	arch_समयr_c3stop = !of_property_पढ़ो_bool(np, "always-on");

	/* Check क्रम globally applicable workarounds */
	arch_समयr_check_ool_workaround(ate_match_dt, np);

	/*
	 * If we cannot rely on firmware initializing the समयr रेजिस्टरs then
	 * we should use the physical समयrs instead.
	 */
	अगर (IS_ENABLED(CONFIG_ARM) &&
	    of_property_पढ़ो_bool(np, "arm,cpu-registers-not-fw-configured"))
		arch_समयr_uses_ppi = ARCH_TIMER_PHYS_SECURE_PPI;
	अन्यथा
		arch_समयr_uses_ppi = arch_समयr_select_ppi();

	अगर (!arch_समयr_ppi[arch_समयr_uses_ppi]) अणु
		pr_err("No interrupt available, giving up\n");
		वापस -EINVAL;
	पूर्ण

	/* On some प्रणालीs, the counter stops ticking when in suspend. */
	arch_counter_suspend_stop = of_property_पढ़ो_bool(np,
							 "arm,no-tick-in-suspend");

	ret = arch_समयr_रेजिस्टर();
	अगर (ret)
		वापस ret;

	अगर (arch_समयr_needs_of_probing())
		वापस 0;

	वापस arch_समयr_common_init();
पूर्ण
TIMER_OF_DECLARE(armv7_arch_समयr, "arm,armv7-timer", arch_समयr_of_init);
TIMER_OF_DECLARE(armv8_arch_समयr, "arm,armv8-timer", arch_समयr_of_init);

अटल u32 __init
arch_समयr_mem_frame_get_cntfrq(काष्ठा arch_समयr_mem_frame *frame)
अणु
	व्योम __iomem *base;
	u32 rate;

	base = ioremap(frame->cntbase, frame->size);
	अगर (!base) अणु
		pr_err("Unable to map frame @ %pa\n", &frame->cntbase);
		वापस 0;
	पूर्ण

	rate = पढ़ोl_relaxed(base + CNTFRQ);

	iounmap(base);

	वापस rate;
पूर्ण

अटल काष्ठा arch_समयr_mem_frame * __init
arch_समयr_mem_find_best_frame(काष्ठा arch_समयr_mem *समयr_mem)
अणु
	काष्ठा arch_समयr_mem_frame *frame, *best_frame = शून्य;
	व्योम __iomem *cntctlbase;
	u32 cnttidr;
	पूर्णांक i;

	cntctlbase = ioremap(समयr_mem->cntctlbase, समयr_mem->size);
	अगर (!cntctlbase) अणु
		pr_err("Can't map CNTCTLBase @ %pa\n",
			&समयr_mem->cntctlbase);
		वापस शून्य;
	पूर्ण

	cnttidr = पढ़ोl_relaxed(cntctlbase + CNTTIDR);

	/*
	 * Try to find a भव capable frame. Otherwise fall back to a
	 * physical capable frame.
	 */
	क्रम (i = 0; i < ARCH_TIMER_MEM_MAX_FRAMES; i++) अणु
		u32 cntacr = CNTACR_RFRQ | CNTACR_RWPT | CNTACR_RPCT |
			     CNTACR_RWVT | CNTACR_RVOFF | CNTACR_RVCT;

		frame = &समयr_mem->frame[i];
		अगर (!frame->valid)
			जारी;

		/* Try enabling everything, and see what sticks */
		ग_लिखोl_relaxed(cntacr, cntctlbase + CNTACR(i));
		cntacr = पढ़ोl_relaxed(cntctlbase + CNTACR(i));

		अगर ((cnttidr & CNTTIDR_VIRT(i)) &&
		    !(~cntacr & (CNTACR_RWVT | CNTACR_RVCT))) अणु
			best_frame = frame;
			arch_समयr_mem_use_भव = true;
			अवरोध;
		पूर्ण

		अगर (~cntacr & (CNTACR_RWPT | CNTACR_RPCT))
			जारी;

		best_frame = frame;
	पूर्ण

	iounmap(cntctlbase);

	वापस best_frame;
पूर्ण

अटल पूर्णांक __init
arch_समयr_mem_frame_रेजिस्टर(काष्ठा arch_समयr_mem_frame *frame)
अणु
	व्योम __iomem *base;
	पूर्णांक ret, irq = 0;

	अगर (arch_समयr_mem_use_भव)
		irq = frame->virt_irq;
	अन्यथा
		irq = frame->phys_irq;

	अगर (!irq) अणु
		pr_err("Frame missing %s irq.\n",
		       arch_समयr_mem_use_भव ? "virt" : "phys");
		वापस -EINVAL;
	पूर्ण

	अगर (!request_mem_region(frame->cntbase, frame->size,
				"arch_mem_timer"))
		वापस -EBUSY;

	base = ioremap(frame->cntbase, frame->size);
	अगर (!base) अणु
		pr_err("Can't map frame's registers\n");
		वापस -ENXIO;
	पूर्ण

	ret = arch_समयr_mem_रेजिस्टर(base, irq);
	अगर (ret) अणु
		iounmap(base);
		वापस ret;
	पूर्ण

	arch_counter_base = base;
	arch_समयrs_present |= ARCH_TIMER_TYPE_MEM;

	वापस 0;
पूर्ण

अटल पूर्णांक __init arch_समयr_mem_of_init(काष्ठा device_node *np)
अणु
	काष्ठा arch_समयr_mem *समयr_mem;
	काष्ठा arch_समयr_mem_frame *frame;
	काष्ठा device_node *frame_node;
	काष्ठा resource res;
	पूर्णांक ret = -EINVAL;
	u32 rate;

	समयr_mem = kzalloc(माप(*समयr_mem), GFP_KERNEL);
	अगर (!समयr_mem)
		वापस -ENOMEM;

	अगर (of_address_to_resource(np, 0, &res))
		जाओ out;
	समयr_mem->cntctlbase = res.start;
	समयr_mem->size = resource_size(&res);

	क्रम_each_available_child_of_node(np, frame_node) अणु
		u32 n;
		काष्ठा arch_समयr_mem_frame *frame;

		अगर (of_property_पढ़ो_u32(frame_node, "frame-number", &n)) अणु
			pr_err(FW_BUG "Missing frame-number.\n");
			of_node_put(frame_node);
			जाओ out;
		पूर्ण
		अगर (n >= ARCH_TIMER_MEM_MAX_FRAMES) अणु
			pr_err(FW_BUG "Wrong frame-number, only 0-%u are permitted.\n",
			       ARCH_TIMER_MEM_MAX_FRAMES - 1);
			of_node_put(frame_node);
			जाओ out;
		पूर्ण
		frame = &समयr_mem->frame[n];

		अगर (frame->valid) अणु
			pr_err(FW_BUG "Duplicated frame-number.\n");
			of_node_put(frame_node);
			जाओ out;
		पूर्ण

		अगर (of_address_to_resource(frame_node, 0, &res)) अणु
			of_node_put(frame_node);
			जाओ out;
		पूर्ण
		frame->cntbase = res.start;
		frame->size = resource_size(&res);

		frame->virt_irq = irq_of_parse_and_map(frame_node,
						       ARCH_TIMER_VIRT_SPI);
		frame->phys_irq = irq_of_parse_and_map(frame_node,
						       ARCH_TIMER_PHYS_SPI);

		frame->valid = true;
	पूर्ण

	frame = arch_समयr_mem_find_best_frame(समयr_mem);
	अगर (!frame) अणु
		pr_err("Unable to find a suitable frame in timer @ %pa\n",
			&समयr_mem->cntctlbase);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	rate = arch_समयr_mem_frame_get_cntfrq(frame);
	arch_समयr_of_configure_rate(rate, np);

	ret = arch_समयr_mem_frame_रेजिस्टर(frame);
	अगर (!ret && !arch_समयr_needs_of_probing())
		ret = arch_समयr_common_init();
out:
	kमुक्त(समयr_mem);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(armv7_arch_समयr_mem, "arm,armv7-timer-mem",
		       arch_समयr_mem_of_init);

#अगर_घोषित CONFIG_ACPI_GTDT
अटल पूर्णांक __init
arch_समयr_mem_verअगरy_cntfrq(काष्ठा arch_समयr_mem *समयr_mem)
अणु
	काष्ठा arch_समयr_mem_frame *frame;
	u32 rate;
	पूर्णांक i;

	क्रम (i = 0; i < ARCH_TIMER_MEM_MAX_FRAMES; i++) अणु
		frame = &समयr_mem->frame[i];

		अगर (!frame->valid)
			जारी;

		rate = arch_समयr_mem_frame_get_cntfrq(frame);
		अगर (rate == arch_समयr_rate)
			जारी;

		pr_err(FW_BUG "CNTFRQ mismatch: frame @ %pa: (0x%08lx), CPU: (0x%08lx)\n",
			&frame->cntbase,
			(अचिन्हित दीर्घ)rate, (अचिन्हित दीर्घ)arch_समयr_rate);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init arch_समयr_mem_acpi_init(पूर्णांक platक्रमm_समयr_count)
अणु
	काष्ठा arch_समयr_mem *समयrs, *समयr;
	काष्ठा arch_समयr_mem_frame *frame, *best_frame = शून्य;
	पूर्णांक समयr_count, i, ret = 0;

	समयrs = kसुस्मृति(platक्रमm_समयr_count, माप(*समयrs),
			    GFP_KERNEL);
	अगर (!समयrs)
		वापस -ENOMEM;

	ret = acpi_arch_समयr_mem_init(समयrs, &समयr_count);
	अगर (ret || !समयr_count)
		जाओ out;

	/*
	 * While unlikely, it's theoretically possible that none of the frames
	 * in a समयr expose the combination of feature we want.
	 */
	क्रम (i = 0; i < समयr_count; i++) अणु
		समयr = &समयrs[i];

		frame = arch_समयr_mem_find_best_frame(समयr);
		अगर (!best_frame)
			best_frame = frame;

		ret = arch_समयr_mem_verअगरy_cntfrq(समयr);
		अगर (ret) अणु
			pr_err("Disabling MMIO timers due to CNTFRQ mismatch\n");
			जाओ out;
		पूर्ण

		अगर (!best_frame) /* implies !frame */
			/*
			 * Only complain about missing suitable frames अगर we
			 * haven't alपढ़ोy found one in a previous iteration.
			 */
			pr_err("Unable to find a suitable frame in timer @ %pa\n",
				&समयr->cntctlbase);
	पूर्ण

	अगर (best_frame)
		ret = arch_समयr_mem_frame_रेजिस्टर(best_frame);
out:
	kमुक्त(समयrs);
	वापस ret;
पूर्ण

/* Initialize per-processor generic समयr and memory-mapped समयr(अगर present) */
अटल पूर्णांक __init arch_समयr_acpi_init(काष्ठा acpi_table_header *table)
अणु
	पूर्णांक ret, platक्रमm_समयr_count;

	अगर (arch_समयrs_present & ARCH_TIMER_TYPE_CP15) अणु
		pr_warn("already initialized, skipping\n");
		वापस -EINVAL;
	पूर्ण

	arch_समयrs_present |= ARCH_TIMER_TYPE_CP15;

	ret = acpi_gtdt_init(table, &platक्रमm_समयr_count);
	अगर (ret)
		वापस ret;

	arch_समयr_ppi[ARCH_TIMER_PHYS_NONSECURE_PPI] =
		acpi_gtdt_map_ppi(ARCH_TIMER_PHYS_NONSECURE_PPI);

	arch_समयr_ppi[ARCH_TIMER_VIRT_PPI] =
		acpi_gtdt_map_ppi(ARCH_TIMER_VIRT_PPI);

	arch_समयr_ppi[ARCH_TIMER_HYP_PPI] =
		acpi_gtdt_map_ppi(ARCH_TIMER_HYP_PPI);

	arch_समयr_populate_kvm_info();

	/*
	 * When probing via ACPI, we have no mechanism to override the sysreg
	 * CNTFRQ value. This *must* be correct.
	 */
	arch_समयr_rate = arch_समयr_get_cntfrq();
	ret = validate_समयr_rate();
	अगर (ret) अणु
		pr_err(FW_BUG "frequency not available.\n");
		वापस ret;
	पूर्ण

	arch_समयr_uses_ppi = arch_समयr_select_ppi();
	अगर (!arch_समयr_ppi[arch_समयr_uses_ppi]) अणु
		pr_err("No interrupt available, giving up\n");
		वापस -EINVAL;
	पूर्ण

	/* Always-on capability */
	arch_समयr_c3stop = acpi_gtdt_c3stop(arch_समयr_uses_ppi);

	/* Check क्रम globally applicable workarounds */
	arch_समयr_check_ool_workaround(ate_match_acpi_oem_info, table);

	ret = arch_समयr_रेजिस्टर();
	अगर (ret)
		वापस ret;

	अगर (platक्रमm_समयr_count &&
	    arch_समयr_mem_acpi_init(platक्रमm_समयr_count))
		pr_err("Failed to initialize memory-mapped timer.\n");

	वापस arch_समयr_common_init();
पूर्ण
TIMER_ACPI_DECLARE(arch_समयr, ACPI_SIG_GTDT, arch_समयr_acpi_init);
#पूर्ण_अगर

पूर्णांक kvm_arch_ptp_get_crosststamp(u64 *cycle, काष्ठा बारpec64 *ts,
				 काष्ठा घड़ीsource **cs)
अणु
	काष्ठा arm_smccc_res hvc_res;
	u32 ptp_counter;
	kसमय_प्रकार kसमय;

	अगर (!IS_ENABLED(CONFIG_HAVE_ARM_SMCCC_DISCOVERY))
		वापस -EOPNOTSUPP;

	अगर (arch_समयr_uses_ppi == ARCH_TIMER_VIRT_PPI)
		ptp_counter = KVM_PTP_VIRT_COUNTER;
	अन्यथा
		ptp_counter = KVM_PTP_PHYS_COUNTER;

	arm_smccc_1_1_invoke(ARM_SMCCC_VENDOR_HYP_KVM_PTP_FUNC_ID,
			     ptp_counter, &hvc_res);

	अगर ((पूर्णांक)(hvc_res.a0) < 0)
		वापस -EOPNOTSUPP;

	kसमय = (u64)hvc_res.a0 << 32 | hvc_res.a1;
	*ts = kसमय_प्रकारo_बारpec64(kसमय);
	अगर (cycle)
		*cycle = (u64)hvc_res.a2 << 32 | hvc_res.a3;
	अगर (cs)
		*cs = &घड़ीsource_counter;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_ptp_get_crosststamp);
