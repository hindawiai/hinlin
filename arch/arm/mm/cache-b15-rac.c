<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom Brahma-B15 CPU पढ़ो-ahead cache management functions
 *
 * Copyright (C) 2015-2016 Broadcom
 */

#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/of_address.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hardware/cache-b15-rac.h>

बाह्य व्योम v7_flush_kern_cache_all(व्योम);

/* RAC रेजिस्टर offsets, relative to the HIF_CPU_BIUCTRL रेजिस्टर base */
#घोषणा RAC_CONFIG0_REG			(0x78)
#घोषणा  RACENPREF_MASK			(0x3)
#घोषणा  RACPREFINST_SHIFT		(0)
#घोषणा  RACENINST_SHIFT		(2)
#घोषणा  RACPREFDATA_SHIFT		(4)
#घोषणा  RACENDATA_SHIFT		(6)
#घोषणा  RAC_CPU_SHIFT			(8)
#घोषणा  RACCFG_MASK			(0xff)
#घोषणा RAC_CONFIG1_REG			(0x7c)
/* Brahma-B15 is a quad-core only design */
#घोषणा B15_RAC_FLUSH_REG		(0x80)
/* Brahma-B53 is an octo-core design */
#घोषणा B53_RAC_FLUSH_REG		(0x84)
#घोषणा  FLUSH_RAC			(1 << 0)

/* Biपंचांगask to enable inकाष्ठाion and data prefetching with a 256-bytes stride */
#घोषणा RAC_DATA_INST_EN_MASK		(1 << RACPREFINST_SHIFT | \
					 RACENPREF_MASK << RACENINST_SHIFT | \
					 1 << RACPREFDATA_SHIFT | \
					 RACENPREF_MASK << RACENDATA_SHIFT)

#घोषणा RAC_ENABLED			0
/* Special state where we want to bypass the spinlock and call directly
 * पूर्णांकo the v7 cache मुख्यtenance operations during suspend/resume
 */
#घोषणा RAC_SUSPENDED			1

अटल व्योम __iomem *b15_rac_base;
अटल DEFINE_SPINLOCK(rac_lock);

अटल u32 rac_config0_reg;
अटल u32 rac_flush_offset;

/* Initialization flag to aव्योम checking क्रम b15_rac_base, and to prevent
 * multi-platक्रमm kernels from crashing here as well.
 */
अटल अचिन्हित दीर्घ b15_rac_flags;

अटल अंतरभूत u32 __b15_rac_disable(व्योम)
अणु
	u32 val = __raw_पढ़ोl(b15_rac_base + RAC_CONFIG0_REG);
	__raw_ग_लिखोl(0, b15_rac_base + RAC_CONFIG0_REG);
	dmb();
	वापस val;
पूर्ण

अटल अंतरभूत व्योम __b15_rac_flush(व्योम)
अणु
	u32 reg;

	__raw_ग_लिखोl(FLUSH_RAC, b15_rac_base + rac_flush_offset);
	करो अणु
		/* This dmb() is required to क्रमce the Bus Interface Unit
		 * to clean oustanding ग_लिखोs, and क्रमces an idle cycle
		 * to be inserted.
		 */
		dmb();
		reg = __raw_पढ़ोl(b15_rac_base + rac_flush_offset);
	पूर्ण जबतक (reg & FLUSH_RAC);
पूर्ण

अटल अंतरभूत u32 b15_rac_disable_and_flush(व्योम)
अणु
	u32 reg;

	reg = __b15_rac_disable();
	__b15_rac_flush();
	वापस reg;
पूर्ण

अटल अंतरभूत व्योम __b15_rac_enable(u32 val)
अणु
	__raw_ग_लिखोl(val, b15_rac_base + RAC_CONFIG0_REG);
	/* dsb() is required here to be consistent with __flush_icache_all() */
	dsb();
पूर्ण

#घोषणा BUILD_RAC_CACHE_OP(name, bar)				\
व्योम b15_flush_##name(व्योम)					\
अणु								\
	अचिन्हित पूर्णांक करो_flush;					\
	u32 val = 0;						\
								\
	अगर (test_bit(RAC_SUSPENDED, &b15_rac_flags)) अणु		\
		v7_flush_##name();				\
		bar;						\
		वापस;						\
	पूर्ण							\
								\
	spin_lock(&rac_lock);					\
	करो_flush = test_bit(RAC_ENABLED, &b15_rac_flags);	\
	अगर (करो_flush)						\
		val = b15_rac_disable_and_flush();		\
	v7_flush_##name();					\
	अगर (!करो_flush)						\
		bar;						\
	अन्यथा							\
		__b15_rac_enable(val);				\
	spin_unlock(&rac_lock);					\
पूर्ण

#घोषणा nobarrier

/* The पढ़ोahead cache present in the Brahma-B15 CPU is a special piece of
 * hardware after the पूर्णांकegrated L2 cache of the B15 CPU complex whose purpose
 * is to prefetch inकाष्ठाion and/or data with a line size of either 64 bytes
 * or 256 bytes. The rationale is that the data-bus of the CPU पूर्णांकerface is
 * optimized क्रम 256-bytes transactions, and enabling the पढ़ोahead cache
 * provides a signअगरicant perक्रमmance boost we want it enabled (typically
 * twice the perक्रमmance क्रम a स_नकल benchmark application).
 *
 * The पढ़ोahead cache is transparent क्रम Modअगरied Virtual Addresses
 * cache मुख्यtenance operations: ICIMVAU, DCIMVAC, DCCMVAC, DCCMVAU and
 * DCCIMVAC.
 *
 * It is however not transparent क्रम the following cache मुख्यtenance
 * operations: DCISW, DCCSW, DCCISW, ICIALLUIS and ICIALLU which is precisely
 * what we are patching here with our BUILD_RAC_CACHE_OP here.
 */
BUILD_RAC_CACHE_OP(kern_cache_all, nobarrier);

अटल व्योम b15_rac_enable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;
	u32 enable = 0;

	क्रम_each_possible_cpu(cpu)
		enable |= (RAC_DATA_INST_EN_MASK << (cpu * RAC_CPU_SHIFT));

	b15_rac_disable_and_flush();
	__b15_rac_enable(enable);
पूर्ण

अटल पूर्णांक b15_rac_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action,
				   व्योम *data)
अणु
	/* During kexec, we are not yet migrated on the boot CPU, so we need to
	 * make sure we are SMP safe here. Once the RAC is disabled, flag it as
	 * suspended such that the hotplug notअगरier वापसs early.
	 */
	अगर (action == SYS_RESTART) अणु
		spin_lock(&rac_lock);
		b15_rac_disable_and_flush();
		clear_bit(RAC_ENABLED, &b15_rac_flags);
		set_bit(RAC_SUSPENDED, &b15_rac_flags);
		spin_unlock(&rac_lock);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block b15_rac_reboot_nb = अणु
	.notअगरier_call	= b15_rac_reboot_notअगरier,
पूर्ण;

/* The CPU hotplug हाल is the most पूर्णांकeresting one, we basically need to make
 * sure that the RAC is disabled क्रम the entire प्रणाली prior to having a CPU
 * die, in particular prior to this dying CPU having निकासed the coherency
 * करोमुख्य.
 *
 * Once this CPU is marked dead, we can safely re-enable the RAC क्रम the
 * reमुख्यing CPUs in the प्रणाली which are still online.
 *
 * Offlining a CPU is the problematic हाल, onlining a CPU is not much of an
 * issue since the CPU and its cache-level hierarchy will start filling with
 * the RAC disabled, so L1 and L2 only.
 *
 * In this function, we should NOT have to verअगरy any unsafe setting/condition
 * b15_rac_base:
 *
 *   It is रक्षित by the RAC_ENABLED flag which is cleared by शेष, and
 *   being cleared when initial procedure is करोne. b15_rac_base had been set at
 *   that समय.
 *
 * RAC_ENABLED:
 *   There is a small timing winकरोws, in b15_rac_init(), between
 *      cpuhp_setup_state_*()
 *      ...
 *      set RAC_ENABLED
 *   However, there is no hotplug activity based on the Linux booting procedure.
 *
 * Since we have to disable RAC क्रम all cores, we keep RAC on as दीर्घ as as
 * possible (disable it as late as possible) to gain the cache benefit.
 *
 * Thus, dying/dead states are chosen here
 *
 * We are choosing not करो disable the RAC on a per-CPU basis, here, अगर we did
 * we would want to consider disabling it as early as possible to benefit the
 * other active CPUs.
 */

/* Running on the dying CPU */
अटल पूर्णांक b15_rac_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	/* During kexec/reboot, the RAC is disabled via the reboot notअगरier
	 * वापस early here.
	 */
	अगर (test_bit(RAC_SUSPENDED, &b15_rac_flags))
		वापस 0;

	spin_lock(&rac_lock);

	/* Indicate that we are starting a hotplug procedure */
	__clear_bit(RAC_ENABLED, &b15_rac_flags);

	/* Disable the पढ़ोahead cache and save its value to a global */
	rac_config0_reg = b15_rac_disable_and_flush();

	spin_unlock(&rac_lock);

	वापस 0;
पूर्ण

/* Running on a non-dying CPU */
अटल पूर्णांक b15_rac_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	/* During kexec/reboot, the RAC is disabled via the reboot notअगरier
	 * वापस early here.
	 */
	अगर (test_bit(RAC_SUSPENDED, &b15_rac_flags))
		वापस 0;

	spin_lock(&rac_lock);

	/* And enable it */
	__b15_rac_enable(rac_config0_reg);
	__set_bit(RAC_ENABLED, &b15_rac_flags);

	spin_unlock(&rac_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक b15_rac_suspend(व्योम)
अणु
	/* Suspend the पढ़ो-ahead cache oeprations, क्रमcing our cache
	 * implementation to fallback to the regular ARMv7 calls.
	 *
	 * We are guaranteed to be running on the boot CPU at this poपूर्णांक and
	 * with every other CPU quiesced, so setting RAC_SUSPENDED is not racy
	 * here.
	 */
	rac_config0_reg = b15_rac_disable_and_flush();
	set_bit(RAC_SUSPENDED, &b15_rac_flags);

	वापस 0;
पूर्ण

अटल व्योम b15_rac_resume(व्योम)
अणु
	/* Coming out of a S3 suspend/resume cycle, the पढ़ो-ahead cache
	 * रेजिस्टर RAC_CONFIG0_REG will be restored to its शेष value, make
	 * sure we re-enable it and set the enable flag, we are also guaranteed
	 * to run on the boot CPU, so not racy again.
	 */
	__b15_rac_enable(rac_config0_reg);
	clear_bit(RAC_SUSPENDED, &b15_rac_flags);
पूर्ण

अटल काष्ठा syscore_ops b15_rac_syscore_ops = अणु
	.suspend	= b15_rac_suspend,
	.resume		= b15_rac_resume,
पूर्ण;

अटल पूर्णांक __init b15_rac_init(व्योम)
अणु
	काष्ठा device_node *dn, *cpu_dn;
	पूर्णांक ret = 0, cpu;
	u32 reg, en_mask = 0;

	dn = of_find_compatible_node(शून्य, शून्य, "brcm,brcmstb-cpu-biu-ctrl");
	अगर (!dn)
		वापस -ENODEV;

	अगर (WARN(num_possible_cpus() > 4, "RAC only supports 4 CPUs\n"))
		जाओ out;

	b15_rac_base = of_iomap(dn, 0);
	अगर (!b15_rac_base) अणु
		pr_err("failed to remap BIU control base\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cpu_dn = of_get_cpu_node(0, शून्य);
	अगर (!cpu_dn) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (of_device_is_compatible(cpu_dn, "brcm,brahma-b15"))
		rac_flush_offset = B15_RAC_FLUSH_REG;
	अन्यथा अगर (of_device_is_compatible(cpu_dn, "brcm,brahma-b53"))
		rac_flush_offset = B53_RAC_FLUSH_REG;
	अन्यथा अणु
		pr_err("Unsupported CPU\n");
		of_node_put(cpu_dn);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	of_node_put(cpu_dn);

	ret = रेजिस्टर_reboot_notअगरier(&b15_rac_reboot_nb);
	अगर (ret) अणु
		pr_err("failed to register reboot notifier\n");
		iounmap(b15_rac_base);
		जाओ out;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_HOTPLUG_CPU)) अणु
		ret = cpuhp_setup_state_nocalls(CPUHP_AP_ARM_CACHE_B15_RAC_DEAD,
					"arm/cache-b15-rac:dead",
					शून्य, b15_rac_dead_cpu);
		अगर (ret)
			जाओ out_unmap;

		ret = cpuhp_setup_state_nocalls(CPUHP_AP_ARM_CACHE_B15_RAC_DYING,
					"arm/cache-b15-rac:dying",
					शून्य, b15_rac_dying_cpu);
		अगर (ret)
			जाओ out_cpu_dead;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PM_SLEEP))
		रेजिस्टर_syscore_ops(&b15_rac_syscore_ops);

	spin_lock(&rac_lock);
	reg = __raw_पढ़ोl(b15_rac_base + RAC_CONFIG0_REG);
	क्रम_each_possible_cpu(cpu)
		en_mask |= ((1 << RACPREFDATA_SHIFT) << (cpu * RAC_CPU_SHIFT));
	WARN(reg & en_mask, "Read-ahead cache not previously disabled\n");

	b15_rac_enable();
	set_bit(RAC_ENABLED, &b15_rac_flags);
	spin_unlock(&rac_lock);

	pr_info("%pOF: Broadcom Brahma-B15 readahead cache\n", dn);

	जाओ out;

out_cpu_dead:
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CACHE_B15_RAC_DYING);
out_unmap:
	unरेजिस्टर_reboot_notअगरier(&b15_rac_reboot_nb);
	iounmap(b15_rac_base);
out:
	of_node_put(dn);
	वापस ret;
पूर्ण
arch_initcall(b15_rac_init);
