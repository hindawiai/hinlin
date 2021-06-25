<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/export.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/notअगरier.h>

#समावेश <यंत्र/current.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/svm.h>

#समावेश "cacheinfo.h"
#समावेश "setup.h"

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/lppaca.h>
#पूर्ण_अगर

अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_devices);

#अगर_घोषित CONFIG_PPC64

/*
 * Snooze delay has not been hooked up since 3fa8cad82b94 ("घातerpc/pseries/cpuidle:
 * smt-snooze-delay cleanup.") and has been broken even दीर्घer. As was क्रमetold in
 * 2014:
 *
 *  "ppc64_util currently utilises it. Once we fix ppc64_util, propose to clean
 *  up the kernel code."
 *
 * घातerpc-utils stopped using it as of 1.3.8. At some poपूर्णांक in the future this
 * code should be हटाओd.
 */

अटल sमाप_प्रकार store_smt_snooze_delay(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf,
				      माप_प्रकार count)
अणु
	pr_warn_once("%s (%d) stored to unsupported smt_snooze_delay, which has no effect.\n",
		     current->comm, current->pid);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_smt_snooze_delay(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	pr_warn_once("%s (%d) read from unsupported smt_snooze_delay\n",
		     current->comm, current->pid);
	वापस प्र_लिखो(buf, "100\n");
पूर्ण

अटल DEVICE_ATTR(smt_snooze_delay, 0644, show_smt_snooze_delay,
		   store_smt_snooze_delay);

अटल पूर्णांक __init setup_smt_snooze_delay(अक्षर *str)
अणु
	अगर (!cpu_has_feature(CPU_FTR_SMT))
		वापस 1;

	pr_warn("smt-snooze-delay command line option has no effect\n");
	वापस 1;
पूर्ण
__setup("smt-snooze-delay=", setup_smt_snooze_delay);

#पूर्ण_अगर /* CONFIG_PPC64 */

#घोषणा __SYSFS_SPRSETUP_READ_WRITE(NAME, ADDRESS, EXTRA) \
अटल व्योम पढ़ो_##NAME(व्योम *val) \
अणु \
	*(अचिन्हित दीर्घ *)val = mfspr(ADDRESS);	\
पूर्ण \
अटल व्योम ग_लिखो_##NAME(व्योम *val) \
अणु \
	EXTRA; \
	mtspr(ADDRESS, *(अचिन्हित दीर्घ *)val);	\
पूर्ण

#घोषणा __SYSFS_SPRSETUP_SHOW_STORE(NAME) \
अटल sमाप_प्रकार show_##NAME(काष्ठा device *dev, \
			काष्ठा device_attribute *attr, \
			अक्षर *buf) \
अणु \
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev); \
	अचिन्हित दीर्घ val; \
	smp_call_function_single(cpu->dev.id, पढ़ो_##NAME, &val, 1);	\
	वापस प्र_लिखो(buf, "%lx\n", val); \
पूर्ण \
अटल sमाप_प्रकार __used \
	store_##NAME(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev); \
	अचिन्हित दीर्घ val; \
	पूर्णांक ret = माला_पूछो(buf, "%lx", &val); \
	अगर (ret != 1) \
		वापस -EINVAL; \
	smp_call_function_single(cpu->dev.id, ग_लिखो_##NAME, &val, 1); \
	वापस count; \
पूर्ण

#घोषणा SYSFS_PMCSETUP(NAME, ADDRESS) \
	__SYSFS_SPRSETUP_READ_WRITE(NAME, ADDRESS, ppc_enable_pmcs()) \
	__SYSFS_SPRSETUP_SHOW_STORE(NAME)
#घोषणा SYSFS_SPRSETUP(NAME, ADDRESS) \
	__SYSFS_SPRSETUP_READ_WRITE(NAME, ADDRESS, ) \
	__SYSFS_SPRSETUP_SHOW_STORE(NAME)

#घोषणा SYSFS_SPRSETUP_SHOW_STORE(NAME) \
	__SYSFS_SPRSETUP_SHOW_STORE(NAME)

#अगर_घोषित CONFIG_PPC64

/*
 * This is the प्रणाली wide DSCR रेजिस्टर शेष value. Any
 * change to this शेष value through the sysfs पूर्णांकerface
 * will update all per cpu DSCR शेष values across the
 * प्रणाली stored in their respective PACA काष्ठाures.
 */
अटल अचिन्हित दीर्घ dscr_शेष;

/**
 * पढ़ो_dscr() - Fetch the cpu specअगरic DSCR शेष
 * @val:	Returned cpu specअगरic DSCR शेष value
 *
 * This function वापसs the per cpu DSCR शेष value
 * क्रम any cpu which is contained in it's PACA काष्ठाure.
 */
अटल व्योम पढ़ो_dscr(व्योम *val)
अणु
	*(अचिन्हित दीर्घ *)val = get_paca()->dscr_शेष;
पूर्ण


/**
 * ग_लिखो_dscr() - Update the cpu specअगरic DSCR शेष
 * @val:	New cpu specअगरic DSCR शेष value to update
 *
 * This function updates the per cpu DSCR शेष value
 * क्रम any cpu which is contained in it's PACA काष्ठाure.
 */
अटल व्योम ग_लिखो_dscr(व्योम *val)
अणु
	get_paca()->dscr_शेष = *(अचिन्हित दीर्घ *)val;
	अगर (!current->thपढ़ो.dscr_inherit) अणु
		current->thपढ़ो.dscr = *(अचिन्हित दीर्घ *)val;
		mtspr(SPRN_DSCR, *(अचिन्हित दीर्घ *)val);
	पूर्ण
पूर्ण

SYSFS_SPRSETUP_SHOW_STORE(dscr);
अटल DEVICE_ATTR(dscr, 0600, show_dscr, store_dscr);

अटल व्योम add_ग_लिखो_permission_dev_attr(काष्ठा device_attribute *attr)
अणु
	attr->attr.mode |= 0200;
पूर्ण

/**
 * show_dscr_शेष() - Fetch the प्रणाली wide DSCR शेष
 * @dev:	Device काष्ठाure
 * @attr:	Device attribute काष्ठाure
 * @buf:	Interface buffer
 *
 * This function वापसs the प्रणाली wide DSCR शेष value.
 */
अटल sमाप_प्रकार show_dscr_शेष(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lx\n", dscr_शेष);
पूर्ण

/**
 * store_dscr_शेष() - Update the प्रणाली wide DSCR शेष
 * @dev:	Device काष्ठाure
 * @attr:	Device attribute काष्ठाure
 * @buf:	Interface buffer
 * @count:	Size of the update
 *
 * This function updates the प्रणाली wide DSCR शेष value.
 */
अटल sमाप_प्रकार __used store_dscr_शेष(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret = 0;

	ret = माला_पूछो(buf, "%lx", &val);
	अगर (ret != 1)
		वापस -EINVAL;
	dscr_शेष = val;

	on_each_cpu(ग_लिखो_dscr, &val, 1);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(dscr_शेष, 0600,
		show_dscr_शेष, store_dscr_शेष);

अटल व्योम sysfs_create_dscr_शेष(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_DSCR)) अणु
		पूर्णांक cpu;

		dscr_शेष = spr_शेष_dscr;
		क्रम_each_possible_cpu(cpu)
			paca_ptrs[cpu]->dscr_शेष = dscr_शेष;

		device_create_file(cpu_subsys.dev_root, &dev_attr_dscr_शेष);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
#घोषणा MAX_BIT				63

अटल u64 pw20_wt;
अटल u64 altivec_idle_wt;

अटल अचिन्हित पूर्णांक get_idle_ticks_bit(u64 ns)
अणु
	u64 cycle;

	अगर (ns >= 10000)
		cycle = भाग_u64(ns + 500, 1000) * tb_ticks_per_usec;
	अन्यथा
		cycle = भाग_u64(ns * tb_ticks_per_usec, 1000);

	अगर (!cycle)
		वापस 0;

	वापस ilog2(cycle);
पूर्ण

अटल व्योम करो_show_pwrmgtcr0(व्योम *val)
अणु
	u32 *value = val;

	*value = mfspr(SPRN_PWRMGTCR0);
पूर्ण

अटल sमाप_प्रकार show_pw20_state(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;
	अचिन्हित पूर्णांक cpu = dev->id;

	smp_call_function_single(cpu, करो_show_pwrmgtcr0, &value, 1);

	value &= PWRMGTCR0_PW20_WAIT;

	वापस प्र_लिखो(buf, "%u\n", value ? 1 : 0);
पूर्ण

अटल व्योम करो_store_pw20_state(व्योम *val)
अणु
	u32 *value = val;
	u32 pw20_state;

	pw20_state = mfspr(SPRN_PWRMGTCR0);

	अगर (*value)
		pw20_state |= PWRMGTCR0_PW20_WAIT;
	अन्यथा
		pw20_state &= ~PWRMGTCR0_PW20_WAIT;

	mtspr(SPRN_PWRMGTCR0, pw20_state);
पूर्ण

अटल sमाप_प्रकार store_pw20_state(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 value;
	अचिन्हित पूर्णांक cpu = dev->id;

	अगर (kstrtou32(buf, 0, &value))
		वापस -EINVAL;

	अगर (value > 1)
		वापस -EINVAL;

	smp_call_function_single(cpu, करो_store_pw20_state, &value, 1);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pw20_रुको_समय(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;
	u64 tb_cycle = 1;
	u64 समय;

	अचिन्हित पूर्णांक cpu = dev->id;

	अगर (!pw20_wt) अणु
		smp_call_function_single(cpu, करो_show_pwrmgtcr0, &value, 1);
		value = (value & PWRMGTCR0_PW20_ENT) >>
					PWRMGTCR0_PW20_ENT_SHIFT;

		tb_cycle = (tb_cycle << (MAX_BIT - value + 1));
		/* convert ms to ns */
		अगर (tb_ticks_per_usec > 1000) अणु
			समय = भाग_u64(tb_cycle, tb_ticks_per_usec / 1000);
		पूर्ण अन्यथा अणु
			u32 rem_us;

			समय = भाग_u64_rem(tb_cycle, tb_ticks_per_usec,
						&rem_us);
			समय = समय * 1000 + rem_us * 1000 / tb_ticks_per_usec;
		पूर्ण
	पूर्ण अन्यथा अणु
		समय = pw20_wt;
	पूर्ण

	वापस प्र_लिखो(buf, "%llu\n", समय > 0 ? समय : 0);
पूर्ण

अटल व्योम set_pw20_रुको_entry_bit(व्योम *val)
अणु
	u32 *value = val;
	u32 pw20_idle;

	pw20_idle = mfspr(SPRN_PWRMGTCR0);

	/* Set Automatic PW20 Core Idle Count */
	/* clear count */
	pw20_idle &= ~PWRMGTCR0_PW20_ENT;

	/* set count */
	pw20_idle |= ((MAX_BIT - *value) << PWRMGTCR0_PW20_ENT_SHIFT);

	mtspr(SPRN_PWRMGTCR0, pw20_idle);
पूर्ण

अटल sमाप_प्रकार store_pw20_रुको_समय(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 entry_bit;
	u64 value;

	अचिन्हित पूर्णांक cpu = dev->id;

	अगर (kstrtou64(buf, 0, &value))
		वापस -EINVAL;

	अगर (!value)
		वापस -EINVAL;

	entry_bit = get_idle_ticks_bit(value);
	अगर (entry_bit > MAX_BIT)
		वापस -EINVAL;

	pw20_wt = value;

	smp_call_function_single(cpu, set_pw20_रुको_entry_bit,
				&entry_bit, 1);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_altivec_idle(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;
	अचिन्हित पूर्णांक cpu = dev->id;

	smp_call_function_single(cpu, करो_show_pwrmgtcr0, &value, 1);

	value &= PWRMGTCR0_AV_IDLE_PD_EN;

	वापस प्र_लिखो(buf, "%u\n", value ? 1 : 0);
पूर्ण

अटल व्योम करो_store_altivec_idle(व्योम *val)
अणु
	u32 *value = val;
	u32 altivec_idle;

	altivec_idle = mfspr(SPRN_PWRMGTCR0);

	अगर (*value)
		altivec_idle |= PWRMGTCR0_AV_IDLE_PD_EN;
	अन्यथा
		altivec_idle &= ~PWRMGTCR0_AV_IDLE_PD_EN;

	mtspr(SPRN_PWRMGTCR0, altivec_idle);
पूर्ण

अटल sमाप_प्रकार store_altivec_idle(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 value;
	अचिन्हित पूर्णांक cpu = dev->id;

	अगर (kstrtou32(buf, 0, &value))
		वापस -EINVAL;

	अगर (value > 1)
		वापस -EINVAL;

	smp_call_function_single(cpu, करो_store_altivec_idle, &value, 1);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_altivec_idle_रुको_समय(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;
	u64 tb_cycle = 1;
	u64 समय;

	अचिन्हित पूर्णांक cpu = dev->id;

	अगर (!altivec_idle_wt) अणु
		smp_call_function_single(cpu, करो_show_pwrmgtcr0, &value, 1);
		value = (value & PWRMGTCR0_AV_IDLE_CNT) >>
					PWRMGTCR0_AV_IDLE_CNT_SHIFT;

		tb_cycle = (tb_cycle << (MAX_BIT - value + 1));
		/* convert ms to ns */
		अगर (tb_ticks_per_usec > 1000) अणु
			समय = भाग_u64(tb_cycle, tb_ticks_per_usec / 1000);
		पूर्ण अन्यथा अणु
			u32 rem_us;

			समय = भाग_u64_rem(tb_cycle, tb_ticks_per_usec,
						&rem_us);
			समय = समय * 1000 + rem_us * 1000 / tb_ticks_per_usec;
		पूर्ण
	पूर्ण अन्यथा अणु
		समय = altivec_idle_wt;
	पूर्ण

	वापस प्र_लिखो(buf, "%llu\n", समय > 0 ? समय : 0);
पूर्ण

अटल व्योम set_altivec_idle_रुको_entry_bit(व्योम *val)
अणु
	u32 *value = val;
	u32 altivec_idle;

	altivec_idle = mfspr(SPRN_PWRMGTCR0);

	/* Set Automatic AltiVec Idle Count */
	/* clear count */
	altivec_idle &= ~PWRMGTCR0_AV_IDLE_CNT;

	/* set count */
	altivec_idle |= ((MAX_BIT - *value) << PWRMGTCR0_AV_IDLE_CNT_SHIFT);

	mtspr(SPRN_PWRMGTCR0, altivec_idle);
पूर्ण

अटल sमाप_प्रकार store_altivec_idle_रुको_समय(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 entry_bit;
	u64 value;

	अचिन्हित पूर्णांक cpu = dev->id;

	अगर (kstrtou64(buf, 0, &value))
		वापस -EINVAL;

	अगर (!value)
		वापस -EINVAL;

	entry_bit = get_idle_ticks_bit(value);
	अगर (entry_bit > MAX_BIT)
		वापस -EINVAL;

	altivec_idle_wt = value;

	smp_call_function_single(cpu, set_altivec_idle_रुको_entry_bit,
				&entry_bit, 1);

	वापस count;
पूर्ण

/*
 * Enable/Disable पूर्णांकerface:
 * 0, disable. 1, enable.
 */
अटल DEVICE_ATTR(pw20_state, 0600, show_pw20_state, store_pw20_state);
अटल DEVICE_ATTR(altivec_idle, 0600, show_altivec_idle, store_altivec_idle);

/*
 * Set रुको समय पूर्णांकerface:(Nanosecond)
 * Example: Base on TBfreq is 41MHZ.
 * 1~48(ns): TB[63]
 * 49~97(ns): TB[62]
 * 98~195(ns): TB[61]
 * 196~390(ns): TB[60]
 * 391~780(ns): TB[59]
 * 781~1560(ns): TB[58]
 * ...
 */
अटल DEVICE_ATTR(pw20_रुको_समय, 0600,
			show_pw20_रुको_समय,
			store_pw20_रुको_समय);
अटल DEVICE_ATTR(altivec_idle_रुको_समय, 0600,
			show_altivec_idle_रुको_समय,
			store_altivec_idle_रुको_समय);
#पूर्ण_अगर

/*
 * Enabling PMCs will slow partition context चयन बार so we only करो
 * it the first समय we ग_लिखो to the PMCs.
 */

अटल DEFINE_PER_CPU(अक्षर, pmcs_enabled);

व्योम ppc_enable_pmcs(व्योम)
अणु
	ppc_set_pmu_inuse(1);

	/* Only need to enable them once */
	अगर (__this_cpu_पढ़ो(pmcs_enabled))
		वापस;

	__this_cpu_ग_लिखो(pmcs_enabled, 1);

	अगर (ppc_md.enable_pmcs)
		ppc_md.enable_pmcs();
पूर्ण
EXPORT_SYMBOL(ppc_enable_pmcs);



/* Let's define all possible registers, we'll only hook up the ones
 * that are implemented on the current processor
 */

#अगर_घोषित CONFIG_PMU_SYSFS
#अगर defined(CONFIG_PPC64) || defined(CONFIG_PPC_BOOK3S_32)
#घोषणा HAS_PPC_PMC_CLASSIC	1
#घोषणा HAS_PPC_PMC_IBM		1
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा HAS_PPC_PMC_PA6T	1
#घोषणा HAS_PPC_PMC56          1
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_32
#घोषणा HAS_PPC_PMC_G4		1
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PMU_SYSFS */

#अगर defined(CONFIG_PPC64) && defined(CONFIG_DEBUG_MISC)
#घोषणा HAS_PPC_PA6T
#पूर्ण_अगर
/*
 * SPRs which are not related to PMU.
 */
#अगर_घोषित CONFIG_PPC64
SYSFS_SPRSETUP(purr, SPRN_PURR);
SYSFS_SPRSETUP(spurr, SPRN_SPURR);
SYSFS_SPRSETUP(pir, SPRN_PIR);
SYSFS_SPRSETUP(tscr, SPRN_TSCR);

/*
  Lets only enable पढ़ो क्रम phyp resources and
  enable ग_लिखो when needed with a separate function.
  Lets be conservative and शेष to pseries.
*/
अटल DEVICE_ATTR(spurr, 0400, show_spurr, शून्य);
अटल DEVICE_ATTR(purr, 0400, show_purr, store_purr);
अटल DEVICE_ATTR(pir, 0400, show_pir, शून्य);
अटल DEVICE_ATTR(tscr, 0600, show_tscr, store_tscr);
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित HAS_PPC_PMC_CLASSIC
SYSFS_PMCSETUP(mmcr0, SPRN_MMCR0);
SYSFS_PMCSETUP(mmcr1, SPRN_MMCR1);
SYSFS_PMCSETUP(pmc1, SPRN_PMC1);
SYSFS_PMCSETUP(pmc2, SPRN_PMC2);
SYSFS_PMCSETUP(pmc3, SPRN_PMC3);
SYSFS_PMCSETUP(pmc4, SPRN_PMC4);
SYSFS_PMCSETUP(pmc5, SPRN_PMC5);
SYSFS_PMCSETUP(pmc6, SPRN_PMC6);
#पूर्ण_अगर

#अगर_घोषित HAS_PPC_PMC_G4
SYSFS_PMCSETUP(mmcr2, SPRN_MMCR2);
#पूर्ण_अगर

#अगर_घोषित HAS_PPC_PMC56
SYSFS_PMCSETUP(pmc7, SPRN_PMC7);
SYSFS_PMCSETUP(pmc8, SPRN_PMC8);

SYSFS_PMCSETUP(mmcra, SPRN_MMCRA);
SYSFS_PMCSETUP(mmcr3, SPRN_MMCR3);

अटल DEVICE_ATTR(mmcra, 0600, show_mmcra, store_mmcra);
अटल DEVICE_ATTR(mmcr3, 0600, show_mmcr3, store_mmcr3);
#पूर्ण_अगर /* HAS_PPC_PMC56 */




#अगर_घोषित HAS_PPC_PMC_PA6T
SYSFS_PMCSETUP(pa6t_pmc0, SPRN_PA6T_PMC0);
SYSFS_PMCSETUP(pa6t_pmc1, SPRN_PA6T_PMC1);
SYSFS_PMCSETUP(pa6t_pmc2, SPRN_PA6T_PMC2);
SYSFS_PMCSETUP(pa6t_pmc3, SPRN_PA6T_PMC3);
SYSFS_PMCSETUP(pa6t_pmc4, SPRN_PA6T_PMC4);
SYSFS_PMCSETUP(pa6t_pmc5, SPRN_PA6T_PMC5);
#पूर्ण_अगर

#अगर_घोषित HAS_PPC_PA6T
SYSFS_SPRSETUP(hid0, SPRN_HID0);
SYSFS_SPRSETUP(hid1, SPRN_HID1);
SYSFS_SPRSETUP(hid4, SPRN_HID4);
SYSFS_SPRSETUP(hid5, SPRN_HID5);
SYSFS_SPRSETUP(ima0, SPRN_PA6T_IMA0);
SYSFS_SPRSETUP(ima1, SPRN_PA6T_IMA1);
SYSFS_SPRSETUP(ima2, SPRN_PA6T_IMA2);
SYSFS_SPRSETUP(ima3, SPRN_PA6T_IMA3);
SYSFS_SPRSETUP(ima4, SPRN_PA6T_IMA4);
SYSFS_SPRSETUP(ima5, SPRN_PA6T_IMA5);
SYSFS_SPRSETUP(ima6, SPRN_PA6T_IMA6);
SYSFS_SPRSETUP(ima7, SPRN_PA6T_IMA7);
SYSFS_SPRSETUP(ima8, SPRN_PA6T_IMA8);
SYSFS_SPRSETUP(ima9, SPRN_PA6T_IMA9);
SYSFS_SPRSETUP(imaat, SPRN_PA6T_IMAAT);
SYSFS_SPRSETUP(btcr, SPRN_PA6T_BTCR);
SYSFS_SPRSETUP(pccr, SPRN_PA6T_PCCR);
SYSFS_SPRSETUP(rpccr, SPRN_PA6T_RPCCR);
SYSFS_SPRSETUP(der, SPRN_PA6T_DER);
SYSFS_SPRSETUP(mer, SPRN_PA6T_MER);
SYSFS_SPRSETUP(ber, SPRN_PA6T_BER);
SYSFS_SPRSETUP(ier, SPRN_PA6T_IER);
SYSFS_SPRSETUP(sier, SPRN_PA6T_SIER);
SYSFS_SPRSETUP(siar, SPRN_PA6T_SIAR);
SYSFS_SPRSETUP(tsr0, SPRN_PA6T_TSR0);
SYSFS_SPRSETUP(tsr1, SPRN_PA6T_TSR1);
SYSFS_SPRSETUP(tsr2, SPRN_PA6T_TSR2);
SYSFS_SPRSETUP(tsr3, SPRN_PA6T_TSR3);
#पूर्ण_अगर /* HAS_PPC_PA6T */

#अगर_घोषित HAS_PPC_PMC_IBM
अटल काष्ठा device_attribute ibm_common_attrs[] = अणु
	__ATTR(mmcr0, 0600, show_mmcr0, store_mmcr0),
	__ATTR(mmcr1, 0600, show_mmcr1, store_mmcr1),
पूर्ण;
#पूर्ण_अगर /* HAS_PPC_PMC_IBM */

#अगर_घोषित HAS_PPC_PMC_G4
अटल काष्ठा device_attribute g4_common_attrs[] = अणु
	__ATTR(mmcr0, 0600, show_mmcr0, store_mmcr0),
	__ATTR(mmcr1, 0600, show_mmcr1, store_mmcr1),
	__ATTR(mmcr2, 0600, show_mmcr2, store_mmcr2),
पूर्ण;
#पूर्ण_अगर /* HAS_PPC_PMC_G4 */

#अगर_घोषित HAS_PPC_PMC_CLASSIC
अटल काष्ठा device_attribute classic_pmc_attrs[] = अणु
	__ATTR(pmc1, 0600, show_pmc1, store_pmc1),
	__ATTR(pmc2, 0600, show_pmc2, store_pmc2),
	__ATTR(pmc3, 0600, show_pmc3, store_pmc3),
	__ATTR(pmc4, 0600, show_pmc4, store_pmc4),
	__ATTR(pmc5, 0600, show_pmc5, store_pmc5),
	__ATTR(pmc6, 0600, show_pmc6, store_pmc6),
#अगर_घोषित HAS_PPC_PMC56
	__ATTR(pmc7, 0600, show_pmc7, store_pmc7),
	__ATTR(pmc8, 0600, show_pmc8, store_pmc8),
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर

#अगर defined(HAS_PPC_PMC_PA6T) || defined(HAS_PPC_PA6T)
अटल काष्ठा device_attribute pa6t_attrs[] = अणु
#अगर_घोषित HAS_PPC_PMC_PA6T
	__ATTR(mmcr0, 0600, show_mmcr0, store_mmcr0),
	__ATTR(mmcr1, 0600, show_mmcr1, store_mmcr1),
	__ATTR(pmc0, 0600, show_pa6t_pmc0, store_pa6t_pmc0),
	__ATTR(pmc1, 0600, show_pa6t_pmc1, store_pa6t_pmc1),
	__ATTR(pmc2, 0600, show_pa6t_pmc2, store_pa6t_pmc2),
	__ATTR(pmc3, 0600, show_pa6t_pmc3, store_pa6t_pmc3),
	__ATTR(pmc4, 0600, show_pa6t_pmc4, store_pa6t_pmc4),
	__ATTR(pmc5, 0600, show_pa6t_pmc5, store_pa6t_pmc5),
#पूर्ण_अगर
#अगर_घोषित HAS_PPC_PA6T
	__ATTR(hid0, 0600, show_hid0, store_hid0),
	__ATTR(hid1, 0600, show_hid1, store_hid1),
	__ATTR(hid4, 0600, show_hid4, store_hid4),
	__ATTR(hid5, 0600, show_hid5, store_hid5),
	__ATTR(ima0, 0600, show_ima0, store_ima0),
	__ATTR(ima1, 0600, show_ima1, store_ima1),
	__ATTR(ima2, 0600, show_ima2, store_ima2),
	__ATTR(ima3, 0600, show_ima3, store_ima3),
	__ATTR(ima4, 0600, show_ima4, store_ima4),
	__ATTR(ima5, 0600, show_ima5, store_ima5),
	__ATTR(ima6, 0600, show_ima6, store_ima6),
	__ATTR(ima7, 0600, show_ima7, store_ima7),
	__ATTR(ima8, 0600, show_ima8, store_ima8),
	__ATTR(ima9, 0600, show_ima9, store_ima9),
	__ATTR(imaat, 0600, show_imaat, store_imaat),
	__ATTR(btcr, 0600, show_btcr, store_btcr),
	__ATTR(pccr, 0600, show_pccr, store_pccr),
	__ATTR(rpccr, 0600, show_rpccr, store_rpccr),
	__ATTR(der, 0600, show_der, store_der),
	__ATTR(mer, 0600, show_mer, store_mer),
	__ATTR(ber, 0600, show_ber, store_ber),
	__ATTR(ier, 0600, show_ier, store_ier),
	__ATTR(sier, 0600, show_sier, store_sier),
	__ATTR(siar, 0600, show_siar, store_siar),
	__ATTR(tsr0, 0600, show_tsr0, store_tsr0),
	__ATTR(tsr1, 0600, show_tsr1, store_tsr1),
	__ATTR(tsr2, 0600, show_tsr2, store_tsr2),
	__ATTR(tsr3, 0600, show_tsr3, store_tsr3),
#पूर्ण_अगर /* HAS_PPC_PA6T */
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_SVM
अटल sमाप_प्रकार show_svm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", is_secure_guest());
पूर्ण
अटल DEVICE_ATTR(svm, 0444, show_svm, शून्य);

अटल व्योम create_svm_file(व्योम)
अणु
	device_create_file(cpu_subsys.dev_root, &dev_attr_svm);
पूर्ण
#अन्यथा
अटल व्योम create_svm_file(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SVM */

#अगर_घोषित CONFIG_PPC_PSERIES
अटल व्योम पढ़ो_idle_purr(व्योम *val)
अणु
	u64 *ret = val;

	*ret = पढ़ो_this_idle_purr();
पूर्ण

अटल sमाप_प्रकार idle_purr_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev);
	u64 val;

	smp_call_function_single(cpu->dev.id, पढ़ो_idle_purr, &val, 1);
	वापस प्र_लिखो(buf, "%llx\n", val);
पूर्ण
अटल DEVICE_ATTR(idle_purr, 0400, idle_purr_show, शून्य);

अटल व्योम create_idle_purr_file(काष्ठा device *s)
अणु
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		device_create_file(s, &dev_attr_idle_purr);
पूर्ण

अटल व्योम हटाओ_idle_purr_file(काष्ठा device *s)
अणु
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		device_हटाओ_file(s, &dev_attr_idle_purr);
पूर्ण

अटल व्योम पढ़ो_idle_spurr(व्योम *val)
अणु
	u64 *ret = val;

	*ret = पढ़ो_this_idle_spurr();
पूर्ण

अटल sमाप_प्रकार idle_spurr_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev);
	u64 val;

	smp_call_function_single(cpu->dev.id, पढ़ो_idle_spurr, &val, 1);
	वापस प्र_लिखो(buf, "%llx\n", val);
पूर्ण
अटल DEVICE_ATTR(idle_spurr, 0400, idle_spurr_show, शून्य);

अटल व्योम create_idle_spurr_file(काष्ठा device *s)
अणु
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		device_create_file(s, &dev_attr_idle_spurr);
पूर्ण

अटल व्योम हटाओ_idle_spurr_file(काष्ठा device *s)
अणु
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		device_हटाओ_file(s, &dev_attr_idle_spurr);
पूर्ण

#अन्यथा /* CONFIG_PPC_PSERIES */
#घोषणा create_idle_purr_file(s)
#घोषणा हटाओ_idle_purr_file(s)
#घोषणा create_idle_spurr_file(s)
#घोषणा हटाओ_idle_spurr_file(s)
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

अटल पूर्णांक रेजिस्टर_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu *c = &per_cpu(cpu_devices, cpu);
	काष्ठा device *s = &c->dev;
	काष्ठा device_attribute *attrs, *pmc_attrs;
	पूर्णांक i, nattrs;

	/* For cpus present at boot a reference was alपढ़ोy grabbed in रेजिस्टर_cpu() */
	अगर (!s->of_node)
		s->of_node = of_get_cpu_node(cpu, शून्य);

#अगर_घोषित CONFIG_PPC64
	अगर (cpu_has_feature(CPU_FTR_SMT))
		device_create_file(s, &dev_attr_smt_snooze_delay);
#पूर्ण_अगर

	/* PMC stuff */
	चयन (cur_cpu_spec->pmc_type) अणु
#अगर_घोषित HAS_PPC_PMC_IBM
	हाल PPC_PMC_IBM:
		attrs = ibm_common_attrs;
		nattrs = माप(ibm_common_attrs) / माप(काष्ठा device_attribute);
		pmc_attrs = classic_pmc_attrs;
		अवरोध;
#पूर्ण_अगर /* HAS_PPC_PMC_IBM */
#अगर_घोषित HAS_PPC_PMC_G4
	हाल PPC_PMC_G4:
		attrs = g4_common_attrs;
		nattrs = माप(g4_common_attrs) / माप(काष्ठा device_attribute);
		pmc_attrs = classic_pmc_attrs;
		अवरोध;
#पूर्ण_अगर /* HAS_PPC_PMC_G4 */
#अगर defined(HAS_PPC_PMC_PA6T) || defined(HAS_PPC_PA6T)
	हाल PPC_PMC_PA6T:
		/* PA Semi starts counting at PMC0 */
		attrs = pa6t_attrs;
		nattrs = माप(pa6t_attrs) / माप(काष्ठा device_attribute);
		pmc_attrs = शून्य;
		अवरोध;
#पूर्ण_अगर
	शेष:
		attrs = शून्य;
		nattrs = 0;
		pmc_attrs = शून्य;
	पूर्ण

	क्रम (i = 0; i < nattrs; i++)
		device_create_file(s, &attrs[i]);

	अगर (pmc_attrs)
		क्रम (i = 0; i < cur_cpu_spec->num_pmcs; i++)
			device_create_file(s, &pmc_attrs[i]);

#अगर_घोषित CONFIG_PPC64
#अगर_घोषित	CONFIG_PMU_SYSFS
	अगर (cpu_has_feature(CPU_FTR_MMCRA))
		device_create_file(s, &dev_attr_mmcra);

	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		device_create_file(s, &dev_attr_mmcr3);
#पूर्ण_अगर /* CONFIG_PMU_SYSFS */

	अगर (cpu_has_feature(CPU_FTR_PURR)) अणु
		अगर (!firmware_has_feature(FW_FEATURE_LPAR))
			add_ग_लिखो_permission_dev_attr(&dev_attr_purr);
		device_create_file(s, &dev_attr_purr);
		create_idle_purr_file(s);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_SPURR)) अणु
		device_create_file(s, &dev_attr_spurr);
		create_idle_spurr_file(s);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_DSCR))
		device_create_file(s, &dev_attr_dscr);

	अगर (cpu_has_feature(CPU_FTR_PPCAS_ARCH_V2))
		device_create_file(s, &dev_attr_pir);

	अगर (cpu_has_feature(CPU_FTR_ARCH_206) &&
		!firmware_has_feature(FW_FEATURE_LPAR))
		device_create_file(s, &dev_attr_tscr);
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अगर (PVR_VER(cur_cpu_spec->pvr_value) == PVR_VER_E6500) अणु
		device_create_file(s, &dev_attr_pw20_state);
		device_create_file(s, &dev_attr_pw20_रुको_समय);

		device_create_file(s, &dev_attr_altivec_idle);
		device_create_file(s, &dev_attr_altivec_idle_रुको_समय);
	पूर्ण
#पूर्ण_अगर
	cacheinfo_cpu_online(cpu);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक unरेजिस्टर_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu *c = &per_cpu(cpu_devices, cpu);
	काष्ठा device *s = &c->dev;
	काष्ठा device_attribute *attrs, *pmc_attrs;
	पूर्णांक i, nattrs;

	BUG_ON(!c->hotpluggable);

#अगर_घोषित CONFIG_PPC64
	अगर (cpu_has_feature(CPU_FTR_SMT))
		device_हटाओ_file(s, &dev_attr_smt_snooze_delay);
#पूर्ण_अगर

	/* PMC stuff */
	चयन (cur_cpu_spec->pmc_type) अणु
#अगर_घोषित HAS_PPC_PMC_IBM
	हाल PPC_PMC_IBM:
		attrs = ibm_common_attrs;
		nattrs = माप(ibm_common_attrs) / माप(काष्ठा device_attribute);
		pmc_attrs = classic_pmc_attrs;
		अवरोध;
#पूर्ण_अगर /* HAS_PPC_PMC_IBM */
#अगर_घोषित HAS_PPC_PMC_G4
	हाल PPC_PMC_G4:
		attrs = g4_common_attrs;
		nattrs = माप(g4_common_attrs) / माप(काष्ठा device_attribute);
		pmc_attrs = classic_pmc_attrs;
		अवरोध;
#पूर्ण_अगर /* HAS_PPC_PMC_G4 */
#अगर defined(HAS_PPC_PMC_PA6T) || defined(HAS_PPC_PA6T)
	हाल PPC_PMC_PA6T:
		/* PA Semi starts counting at PMC0 */
		attrs = pa6t_attrs;
		nattrs = माप(pa6t_attrs) / माप(काष्ठा device_attribute);
		pmc_attrs = शून्य;
		अवरोध;
#पूर्ण_अगर
	शेष:
		attrs = शून्य;
		nattrs = 0;
		pmc_attrs = शून्य;
	पूर्ण

	क्रम (i = 0; i < nattrs; i++)
		device_हटाओ_file(s, &attrs[i]);

	अगर (pmc_attrs)
		क्रम (i = 0; i < cur_cpu_spec->num_pmcs; i++)
			device_हटाओ_file(s, &pmc_attrs[i]);

#अगर_घोषित CONFIG_PPC64
#अगर_घोषित CONFIG_PMU_SYSFS
	अगर (cpu_has_feature(CPU_FTR_MMCRA))
		device_हटाओ_file(s, &dev_attr_mmcra);

	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		device_हटाओ_file(s, &dev_attr_mmcr3);
#पूर्ण_अगर /* CONFIG_PMU_SYSFS */

	अगर (cpu_has_feature(CPU_FTR_PURR)) अणु
		device_हटाओ_file(s, &dev_attr_purr);
		हटाओ_idle_purr_file(s);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_SPURR)) अणु
		device_हटाओ_file(s, &dev_attr_spurr);
		हटाओ_idle_spurr_file(s);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_DSCR))
		device_हटाओ_file(s, &dev_attr_dscr);

	अगर (cpu_has_feature(CPU_FTR_PPCAS_ARCH_V2))
		device_हटाओ_file(s, &dev_attr_pir);

	अगर (cpu_has_feature(CPU_FTR_ARCH_206) &&
		!firmware_has_feature(FW_FEATURE_LPAR))
		device_हटाओ_file(s, &dev_attr_tscr);
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अगर (PVR_VER(cur_cpu_spec->pvr_value) == PVR_VER_E6500) अणु
		device_हटाओ_file(s, &dev_attr_pw20_state);
		device_हटाओ_file(s, &dev_attr_pw20_रुको_समय);

		device_हटाओ_file(s, &dev_attr_altivec_idle);
		device_हटाओ_file(s, &dev_attr_altivec_idle_रुको_समय);
	पूर्ण
#पूर्ण_अगर
	cacheinfo_cpu_offline(cpu);
	of_node_put(s->of_node);
	s->of_node = शून्य;
	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_HOTPLUG_CPU */
#घोषणा unरेजिस्टर_cpu_online शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_CPU_PROBE_RELEASE
sमाप_प्रकार arch_cpu_probe(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (ppc_md.cpu_probe)
		वापस ppc_md.cpu_probe(buf, count);

	वापस -EINVAL;
पूर्ण

sमाप_प्रकार arch_cpu_release(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (ppc_md.cpu_release)
		वापस ppc_md.cpu_release(buf, count);

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_CPU_PROBE_RELEASE */

अटल DEFINE_MUTEX(cpu_mutex);

पूर्णांक cpu_add_dev_attr(काष्ठा device_attribute *attr)
अणु
	पूर्णांक cpu;

	mutex_lock(&cpu_mutex);

	क्रम_each_possible_cpu(cpu) अणु
		device_create_file(get_cpu_device(cpu), attr);
	पूर्ण

	mutex_unlock(&cpu_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_add_dev_attr);

पूर्णांक cpu_add_dev_attr_group(काष्ठा attribute_group *attrs)
अणु
	पूर्णांक cpu;
	काष्ठा device *dev;
	पूर्णांक ret;

	mutex_lock(&cpu_mutex);

	क्रम_each_possible_cpu(cpu) अणु
		dev = get_cpu_device(cpu);
		ret = sysfs_create_group(&dev->kobj, attrs);
		WARN_ON(ret != 0);
	पूर्ण

	mutex_unlock(&cpu_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_add_dev_attr_group);


व्योम cpu_हटाओ_dev_attr(काष्ठा device_attribute *attr)
अणु
	पूर्णांक cpu;

	mutex_lock(&cpu_mutex);

	क्रम_each_possible_cpu(cpu) अणु
		device_हटाओ_file(get_cpu_device(cpu), attr);
	पूर्ण

	mutex_unlock(&cpu_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_हटाओ_dev_attr);

व्योम cpu_हटाओ_dev_attr_group(काष्ठा attribute_group *attrs)
अणु
	पूर्णांक cpu;
	काष्ठा device *dev;

	mutex_lock(&cpu_mutex);

	क्रम_each_possible_cpu(cpu) अणु
		dev = get_cpu_device(cpu);
		sysfs_हटाओ_group(&dev->kobj, attrs);
	पूर्ण

	mutex_unlock(&cpu_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_हटाओ_dev_attr_group);


/* NUMA stuff */

#अगर_घोषित CONFIG_NUMA
अटल व्योम रेजिस्टर_nodes(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUMNODES; i++)
		रेजिस्टर_one_node(i);
पूर्ण

पूर्णांक sysfs_add_device_to_node(काष्ठा device *dev, पूर्णांक nid)
अणु
	काष्ठा node *node = node_devices[nid];
	वापस sysfs_create_link(&node->dev.kobj, &dev->kobj,
			kobject_name(&dev->kobj));
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_add_device_to_node);

व्योम sysfs_हटाओ_device_from_node(काष्ठा device *dev, पूर्णांक nid)
अणु
	काष्ठा node *node = node_devices[nid];
	sysfs_हटाओ_link(&node->dev.kobj, kobject_name(&dev->kobj));
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_device_from_node);

#अन्यथा
अटल व्योम रेजिस्टर_nodes(व्योम)
अणु
	वापस;
पूर्ण

#पूर्ण_अगर

/* Only valid अगर CPU is present. */
अटल sमाप_प्रकार show_physical_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev);

	वापस प्र_लिखो(buf, "%d\n", get_hard_smp_processor_id(cpu->dev.id));
पूर्ण
अटल DEVICE_ATTR(physical_id, 0444, show_physical_id, शून्य);

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक cpu, r;

	रेजिस्टर_nodes();

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpu *c = &per_cpu(cpu_devices, cpu);

#अगर_घोषित CONFIG_HOTPLUG_CPU
		/*
		 * For now, we just see अगर the प्रणाली supports making
		 * the RTAS calls क्रम CPU hotplug.  But, there may be a
		 * more comprehensive way to करो this क्रम an inभागidual
		 * CPU.  For instance, the boot cpu might never be valid
		 * क्रम hotplugging.
		 */
		अगर (smp_ops->cpu_offline_self)
			c->hotpluggable = 1;
#पूर्ण_अगर

		अगर (cpu_online(cpu) || c->hotpluggable) अणु
			रेजिस्टर_cpu(c, cpu);

			device_create_file(&c->dev, &dev_attr_physical_id);
		पूर्ण
	पूर्ण
	r = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "powerpc/topology:online",
			      रेजिस्टर_cpu_online, unरेजिस्टर_cpu_online);
	WARN_ON(r < 0);
#अगर_घोषित CONFIG_PPC64
	sysfs_create_dscr_शेष();
#पूर्ण_अगर /* CONFIG_PPC64 */

	create_svm_file();

	वापस 0;
पूर्ण
subsys_initcall(topology_init);
