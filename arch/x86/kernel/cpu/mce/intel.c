<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel specअगरic MCE features.
 * Copyright 2004 Zwane Mwaikambo <zwane@linuxघातer.ca>
 * Copyright (C) 2008, 2009 Intel Corporation
 * Author: Andi Kleen
 */

#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/mce.h>

#समावेश "internal.h"

/*
 * Support क्रम Intel Correct Machine Check Interrupts. This allows
 * the CPU to उठाओ an पूर्णांकerrupt when a corrected machine check happened.
 * Normally we pick those up using a regular polling समयr.
 * Also supports reliable discovery of shared banks.
 */

/*
 * CMCI can be delivered to multiple cpus that share a machine check bank
 * so we need to designate a single cpu to process errors logged in each bank
 * in the पूर्णांकerrupt handler (otherwise we would have many races and potential
 * द्विगुन reporting of the same error).
 * Note that this can change when a cpu is offlined or brought online since
 * some MCA banks are shared across cpus. When a cpu is offlined, cmci_clear()
 * disables CMCI on all banks owned by the cpu and clears this bitfield. At
 * this poपूर्णांक, cmci_rediscover() kicks in and a dअगरferent cpu may end up
 * taking ownership of some of the shared MCA banks that were previously
 * owned by the offlined cpu.
 */
अटल DEFINE_PER_CPU(mce_banks_t, mce_banks_owned);

/*
 * CMCI storm detection backoff counter
 *
 * During storm, we reset this counter to INITIAL_CHECK_INTERVAL in हाल we've
 * encountered an error. If not, we decrement it by one. We संकेत the end of
 * the CMCI storm when it reaches 0.
 */
अटल DEFINE_PER_CPU(पूर्णांक, cmci_backoff_cnt);

/*
 * cmci_discover_lock protects against parallel discovery attempts
 * which could race against each other.
 */
अटल DEFINE_RAW_SPINLOCK(cmci_discover_lock);

#घोषणा CMCI_THRESHOLD		1
#घोषणा CMCI_POLL_INTERVAL	(30 * HZ)
#घोषणा CMCI_STORM_INTERVAL	(HZ)
#घोषणा CMCI_STORM_THRESHOLD	15

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, cmci_समय_stamp);
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, cmci_storm_cnt);
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, cmci_storm_state);

क्रमागत अणु
	CMCI_STORM_NONE,
	CMCI_STORM_ACTIVE,
	CMCI_STORM_SUBSIDED,
पूर्ण;

अटल atomic_t cmci_storm_on_cpus;

अटल पूर्णांक cmci_supported(पूर्णांक *banks)
अणु
	u64 cap;

	अगर (mca_cfg.cmci_disabled || mca_cfg.ignore_ce)
		वापस 0;

	/*
	 * Venकरोr check is not strictly needed, but the initial
	 * initialization is venकरोr keyed and this
	 * makes sure none of the backकरोors are entered otherwise.
	 */
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_ZHAOXIN)
		वापस 0;

	अगर (!boot_cpu_has(X86_FEATURE_APIC) || lapic_get_maxlvt() < 6)
		वापस 0;
	rdmsrl(MSR_IA32_MCG_CAP, cap);
	*banks = min_t(अचिन्हित, MAX_NR_BANKS, cap & 0xff);
	वापस !!(cap & MCG_CMCI_P);
पूर्ण

अटल bool lmce_supported(व्योम)
अणु
	u64 पंचांगp;

	अगर (mca_cfg.lmce_disabled)
		वापस false;

	rdmsrl(MSR_IA32_MCG_CAP, पंचांगp);

	/*
	 * LMCE depends on recovery support in the processor. Hence both
	 * MCG_SER_P and MCG_LMCE_P should be present in MCG_CAP.
	 */
	अगर ((पंचांगp & (MCG_SER_P | MCG_LMCE_P)) !=
		   (MCG_SER_P | MCG_LMCE_P))
		वापस false;

	/*
	 * BIOS should indicate support क्रम LMCE by setting bit 20 in
	 * IA32_FEAT_CTL without which touching MCG_EXT_CTL will generate a #GP
	 * fault.  The MSR must also be locked क्रम LMCE_ENABLED to take effect.
	 * WARN अगर the MSR isn't locked as init_ia32_feat_ctl() unconditionally
	 * locks the MSR in the event that it wasn't alपढ़ोy locked by BIOS.
	 */
	rdmsrl(MSR_IA32_FEAT_CTL, पंचांगp);
	अगर (WARN_ON_ONCE(!(पंचांगp & FEAT_CTL_LOCKED)))
		वापस false;

	वापस पंचांगp & FEAT_CTL_LMCE_ENABLED;
पूर्ण

bool mce_पूर्णांकel_cmci_poll(व्योम)
अणु
	अगर (__this_cpu_पढ़ो(cmci_storm_state) == CMCI_STORM_NONE)
		वापस false;

	/*
	 * Reset the counter अगर we've logged an error in the last poll
	 * during the storm.
	 */
	अगर (machine_check_poll(0, this_cpu_ptr(&mce_banks_owned)))
		this_cpu_ग_लिखो(cmci_backoff_cnt, INITIAL_CHECK_INTERVAL);
	अन्यथा
		this_cpu_dec(cmci_backoff_cnt);

	वापस true;
पूर्ण

व्योम mce_पूर्णांकel_hcpu_update(अचिन्हित दीर्घ cpu)
अणु
	अगर (per_cpu(cmci_storm_state, cpu) == CMCI_STORM_ACTIVE)
		atomic_dec(&cmci_storm_on_cpus);

	per_cpu(cmci_storm_state, cpu) = CMCI_STORM_NONE;
पूर्ण

अटल व्योम cmci_toggle_पूर्णांकerrupt_mode(bool on)
अणु
	अचिन्हित दीर्घ flags, *owned;
	पूर्णांक bank;
	u64 val;

	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	owned = this_cpu_ptr(mce_banks_owned);
	क्रम_each_set_bit(bank, owned, MAX_NR_BANKS) अणु
		rdmsrl(MSR_IA32_MCx_CTL2(bank), val);

		अगर (on)
			val |= MCI_CTL2_CMCI_EN;
		अन्यथा
			val &= ~MCI_CTL2_CMCI_EN;

		wrmsrl(MSR_IA32_MCx_CTL2(bank), val);
	पूर्ण
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
पूर्ण

अचिन्हित दीर्घ cmci_पूर्णांकel_adjust_समयr(अचिन्हित दीर्घ पूर्णांकerval)
अणु
	अगर ((this_cpu_पढ़ो(cmci_backoff_cnt) > 0) &&
	    (__this_cpu_पढ़ो(cmci_storm_state) == CMCI_STORM_ACTIVE)) अणु
		mce_notअगरy_irq();
		वापस CMCI_STORM_INTERVAL;
	पूर्ण

	चयन (__this_cpu_पढ़ो(cmci_storm_state)) अणु
	हाल CMCI_STORM_ACTIVE:

		/*
		 * We चयन back to पूर्णांकerrupt mode once the poll समयr has
		 * silenced itself. That means no events recorded and the समयr
		 * पूर्णांकerval is back to our poll पूर्णांकerval.
		 */
		__this_cpu_ग_लिखो(cmci_storm_state, CMCI_STORM_SUBSIDED);
		अगर (!atomic_sub_वापस(1, &cmci_storm_on_cpus))
			pr_notice("CMCI storm subsided: switching to interrupt mode\n");

		fallthrough;

	हाल CMCI_STORM_SUBSIDED:
		/*
		 * We रुको क्रम all CPUs to go back to SUBSIDED state. When that
		 * happens we चयन back to पूर्णांकerrupt mode.
		 */
		अगर (!atomic_पढ़ो(&cmci_storm_on_cpus)) अणु
			__this_cpu_ग_लिखो(cmci_storm_state, CMCI_STORM_NONE);
			cmci_toggle_पूर्णांकerrupt_mode(true);
			cmci_recheck();
		पूर्ण
		वापस CMCI_POLL_INTERVAL;
	शेष:

		/* We have shiny weather. Let the poll करो whatever it thinks. */
		वापस पूर्णांकerval;
	पूर्ण
पूर्ण

अटल bool cmci_storm_detect(व्योम)
अणु
	अचिन्हित पूर्णांक cnt = __this_cpu_पढ़ो(cmci_storm_cnt);
	अचिन्हित दीर्घ ts = __this_cpu_पढ़ो(cmci_समय_stamp);
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक r;

	अगर (__this_cpu_पढ़ो(cmci_storm_state) != CMCI_STORM_NONE)
		वापस true;

	अगर (समय_beक्रमe_eq(now, ts + CMCI_STORM_INTERVAL)) अणु
		cnt++;
	पूर्ण अन्यथा अणु
		cnt = 1;
		__this_cpu_ग_लिखो(cmci_समय_stamp, now);
	पूर्ण
	__this_cpu_ग_लिखो(cmci_storm_cnt, cnt);

	अगर (cnt <= CMCI_STORM_THRESHOLD)
		वापस false;

	cmci_toggle_पूर्णांकerrupt_mode(false);
	__this_cpu_ग_लिखो(cmci_storm_state, CMCI_STORM_ACTIVE);
	r = atomic_add_वापस(1, &cmci_storm_on_cpus);
	mce_समयr_kick(CMCI_STORM_INTERVAL);
	this_cpu_ग_लिखो(cmci_backoff_cnt, INITIAL_CHECK_INTERVAL);

	अगर (r == 1)
		pr_notice("CMCI storm detected: switching to poll mode\n");
	वापस true;
पूर्ण

/*
 * The पूर्णांकerrupt handler. This is called on every event.
 * Just call the poller directly to log any events.
 * This could in theory increase the threshold under high load,
 * but करोesn't क्रम now.
 */
अटल व्योम पूर्णांकel_threshold_पूर्णांकerrupt(व्योम)
अणु
	अगर (cmci_storm_detect())
		वापस;

	machine_check_poll(MCP_TIMESTAMP, this_cpu_ptr(&mce_banks_owned));
पूर्ण

/*
 * Enable CMCI (Corrected Machine Check Interrupt) क्रम available MCE banks
 * on this CPU. Use the algorithm recommended in the SDM to discover shared
 * banks.
 */
अटल व्योम cmci_discover(पूर्णांक banks)
अणु
	अचिन्हित दीर्घ *owned = (व्योम *)this_cpu_ptr(&mce_banks_owned);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक bios_wrong_thresh = 0;

	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	क्रम (i = 0; i < banks; i++) अणु
		u64 val;
		पूर्णांक bios_zero_thresh = 0;

		अगर (test_bit(i, owned))
			जारी;

		/* Skip banks in firmware first mode */
		अगर (test_bit(i, mce_banks_ce_disabled))
			जारी;

		rdmsrl(MSR_IA32_MCx_CTL2(i), val);

		/* Alपढ़ोy owned by someone अन्यथा? */
		अगर (val & MCI_CTL2_CMCI_EN) अणु
			clear_bit(i, owned);
			__clear_bit(i, this_cpu_ptr(mce_poll_banks));
			जारी;
		पूर्ण

		अगर (!mca_cfg.bios_cmci_threshold) अणु
			val &= ~MCI_CTL2_CMCI_THRESHOLD_MASK;
			val |= CMCI_THRESHOLD;
		पूर्ण अन्यथा अगर (!(val & MCI_CTL2_CMCI_THRESHOLD_MASK)) अणु
			/*
			 * If bios_cmci_threshold boot option was specअगरied
			 * but the threshold is zero, we'll try to initialize
			 * it to 1.
			 */
			bios_zero_thresh = 1;
			val |= CMCI_THRESHOLD;
		पूर्ण

		val |= MCI_CTL2_CMCI_EN;
		wrmsrl(MSR_IA32_MCx_CTL2(i), val);
		rdmsrl(MSR_IA32_MCx_CTL2(i), val);

		/* Did the enable bit stick? -- the bank supports CMCI */
		अगर (val & MCI_CTL2_CMCI_EN) अणु
			set_bit(i, owned);
			__clear_bit(i, this_cpu_ptr(mce_poll_banks));
			/*
			 * We are able to set thresholds क्रम some banks that
			 * had a threshold of 0. This means the BIOS has not
			 * set the thresholds properly or करोes not work with
			 * this boot option. Note करोwn now and report later.
			 */
			अगर (mca_cfg.bios_cmci_threshold && bios_zero_thresh &&
					(val & MCI_CTL2_CMCI_THRESHOLD_MASK))
				bios_wrong_thresh = 1;
		पूर्ण अन्यथा अणु
			WARN_ON(!test_bit(i, this_cpu_ptr(mce_poll_banks)));
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
	अगर (mca_cfg.bios_cmci_threshold && bios_wrong_thresh) अणु
		pr_info_once(
			"bios_cmci_threshold: Some banks do not have valid thresholds set\n");
		pr_info_once(
			"bios_cmci_threshold: Make sure your BIOS supports this boot option\n");
	पूर्ण
पूर्ण

/*
 * Just in हाल we missed an event during initialization check
 * all the CMCI owned banks.
 */
व्योम cmci_recheck(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक banks;

	अगर (!mce_available(raw_cpu_ptr(&cpu_info)) || !cmci_supported(&banks))
		वापस;

	local_irq_save(flags);
	machine_check_poll(0, this_cpu_ptr(&mce_banks_owned));
	local_irq_restore(flags);
पूर्ण

/* Caller must hold the lock on cmci_discover_lock */
अटल व्योम __cmci_disable_bank(पूर्णांक bank)
अणु
	u64 val;

	अगर (!test_bit(bank, this_cpu_ptr(mce_banks_owned)))
		वापस;
	rdmsrl(MSR_IA32_MCx_CTL2(bank), val);
	val &= ~MCI_CTL2_CMCI_EN;
	wrmsrl(MSR_IA32_MCx_CTL2(bank), val);
	__clear_bit(bank, this_cpu_ptr(mce_banks_owned));
पूर्ण

/*
 * Disable CMCI on this CPU क्रम all banks it owns when it goes करोwn.
 * This allows other CPUs to claim the banks on rediscovery.
 */
व्योम cmci_clear(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक banks;

	अगर (!cmci_supported(&banks))
		वापस;
	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	क्रम (i = 0; i < banks; i++)
		__cmci_disable_bank(i);
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
पूर्ण

अटल व्योम cmci_rediscover_work_func(व्योम *arg)
अणु
	पूर्णांक banks;

	/* Recheck banks in हाल CPUs करोn't all have the same */
	अगर (cmci_supported(&banks))
		cmci_discover(banks);
पूर्ण

/* After a CPU went करोwn cycle through all the others and rediscover */
व्योम cmci_rediscover(व्योम)
अणु
	पूर्णांक banks;

	अगर (!cmci_supported(&banks))
		वापस;

	on_each_cpu(cmci_rediscover_work_func, शून्य, 1);
पूर्ण

/*
 * Reenable CMCI on this CPU in हाल a CPU करोwn failed.
 */
व्योम cmci_reenable(व्योम)
अणु
	पूर्णांक banks;
	अगर (cmci_supported(&banks))
		cmci_discover(banks);
पूर्ण

व्योम cmci_disable_bank(पूर्णांक bank)
अणु
	पूर्णांक banks;
	अचिन्हित दीर्घ flags;

	अगर (!cmci_supported(&banks))
		वापस;

	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	__cmci_disable_bank(bank);
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
पूर्ण

व्योम पूर्णांकel_init_cmci(व्योम)
अणु
	पूर्णांक banks;

	अगर (!cmci_supported(&banks))
		वापस;

	mce_threshold_vector = पूर्णांकel_threshold_पूर्णांकerrupt;
	cmci_discover(banks);
	/*
	 * For CPU #0 this runs with still disabled APIC, but that's
	 * ok because only the vector is set up. We still करो another
	 * check क्रम the banks later क्रम CPU #0 just to make sure
	 * to not miss any events.
	 */
	apic_ग_लिखो(APIC_LVTCMCI, THRESHOLD_APIC_VECTOR|APIC_DM_FIXED);
	cmci_recheck();
पूर्ण

व्योम पूर्णांकel_init_lmce(व्योम)
अणु
	u64 val;

	अगर (!lmce_supported())
		वापस;

	rdmsrl(MSR_IA32_MCG_EXT_CTL, val);

	अगर (!(val & MCG_EXT_CTL_LMCE_EN))
		wrmsrl(MSR_IA32_MCG_EXT_CTL, val | MCG_EXT_CTL_LMCE_EN);
पूर्ण

व्योम पूर्णांकel_clear_lmce(व्योम)
अणु
	u64 val;

	अगर (!lmce_supported())
		वापस;

	rdmsrl(MSR_IA32_MCG_EXT_CTL, val);
	val &= ~MCG_EXT_CTL_LMCE_EN;
	wrmsrl(MSR_IA32_MCG_EXT_CTL, val);
पूर्ण

अटल व्योम पूर्णांकel_ppin_init(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	/*
	 * Even अगर testing the presence of the MSR would be enough, we करोn't
	 * want to risk the situation where other models reuse this MSR क्रम
	 * other purposes.
	 */
	चयन (c->x86_model) अणु
	हाल INTEL_FAM6_IVYBRIDGE_X:
	हाल INTEL_FAM6_HASWELL_X:
	हाल INTEL_FAM6_BROADWELL_D:
	हाल INTEL_FAM6_BROADWELL_X:
	हाल INTEL_FAM6_SKYLAKE_X:
	हाल INTEL_FAM6_ICELAKE_X:
	हाल INTEL_FAM6_SAPPHIRERAPIDS_X:
	हाल INTEL_FAM6_XEON_PHI_KNL:
	हाल INTEL_FAM6_XEON_PHI_KNM:

		अगर (rdmsrl_safe(MSR_PPIN_CTL, &val))
			वापस;

		अगर ((val & 3UL) == 1UL) अणु
			/* PPIN locked in disabled mode */
			वापस;
		पूर्ण

		/* If PPIN is disabled, try to enable */
		अगर (!(val & 2UL)) अणु
			wrmsrl_safe(MSR_PPIN_CTL,  val | 2UL);
			rdmsrl_safe(MSR_PPIN_CTL, &val);
		पूर्ण

		/* Is the enable bit set? */
		अगर (val & 2UL)
			set_cpu_cap(c, X86_FEATURE_INTEL_PPIN);
	पूर्ण
पूर्ण

/*
 * Enable additional error logs from the पूर्णांकegrated
 * memory controller on processors that support this.
 */
अटल व्योम पूर्णांकel_imc_init(काष्ठा cpuinfo_x86 *c)
अणु
	u64 error_control;

	चयन (c->x86_model) अणु
	हाल INTEL_FAM6_SANDYBRIDGE_X:
	हाल INTEL_FAM6_IVYBRIDGE_X:
	हाल INTEL_FAM6_HASWELL_X:
		अगर (rdmsrl_safe(MSR_ERROR_CONTROL, &error_control))
			वापस;
		error_control |= 2;
		wrmsrl_safe(MSR_ERROR_CONTROL, error_control);
		अवरोध;
	पूर्ण
पूर्ण

व्योम mce_पूर्णांकel_feature_init(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांकel_init_cmci();
	पूर्णांकel_init_lmce();
	पूर्णांकel_ppin_init(c);
	पूर्णांकel_imc_init(c);
पूर्ण

व्योम mce_पूर्णांकel_feature_clear(काष्ठा cpuinfo_x86 *c)
अणु
	पूर्णांकel_clear_lmce();
पूर्ण

bool पूर्णांकel_filter_mce(काष्ठा mce *m)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	/* MCE errata HSD131, HSM142, HSW131, BDM48, and HSM142 */
	अगर ((c->x86 == 6) &&
	    ((c->x86_model == INTEL_FAM6_HASWELL) ||
	     (c->x86_model == INTEL_FAM6_HASWELL_L) ||
	     (c->x86_model == INTEL_FAM6_BROADWELL) ||
	     (c->x86_model == INTEL_FAM6_HASWELL_G)) &&
	    (m->bank == 0) &&
	    ((m->status & 0xa0000000ffffffff) == 0x80000000000f0005))
		वापस true;

	वापस false;
पूर्ण
