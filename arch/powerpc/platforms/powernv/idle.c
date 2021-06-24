<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV cpuidle code
 *
 * Copyright 2015 IBM Corp.
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/runlatch.h>
#समावेश <यंत्र/dbell.h>

#समावेश "powernv.h"
#समावेश "subcore.h"

/* Power ISA 3.0 allows क्रम stop states 0x0 - 0xF */
#घोषणा MAX_STOP_STATE	0xF

#घोषणा P9_STOP_SPR_MSR 2000
#घोषणा P9_STOP_SPR_PSSCR      855

अटल u32 supported_cpuidle_states;
काष्ठा pnv_idle_states_t *pnv_idle_states;
पूर्णांक nr_pnv_idle_states;

/*
 * The शेष stop state that will be used by ppc_md.घातer_save
 * function on platक्रमms that support stop inकाष्ठाion.
 */
अटल u64 pnv_शेष_stop_val;
अटल u64 pnv_शेष_stop_mask;
अटल bool शेष_stop_found;

/*
 * First stop state levels when SPR and TB loss can occur.
 */
अटल u64 pnv_first_tb_loss_level = MAX_STOP_STATE + 1;
अटल u64 deep_spr_loss_state = MAX_STOP_STATE + 1;

/*
 * psscr value and mask of the deepest stop idle state.
 * Used when a cpu is offlined.
 */
अटल u64 pnv_deepest_stop_psscr_val;
अटल u64 pnv_deepest_stop_psscr_mask;
अटल u64 pnv_deepest_stop_flag;
अटल bool deepest_stop_found;

अटल अचिन्हित दीर्घ घातer7_offline_type;

अटल पूर्णांक pnv_save_sprs_क्रम_deep_states(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक rc;

	/*
	 * hid0, hid1, hid4, hid5, hmeer and lpcr values are symmetric across
	 * all cpus at boot. Get these reg values of current cpu and use the
	 * same across all cpus.
	 */
	uपूर्णांक64_t lpcr_val	= mfspr(SPRN_LPCR);
	uपूर्णांक64_t hid0_val	= mfspr(SPRN_HID0);
	uपूर्णांक64_t hmeer_val	= mfspr(SPRN_HMEER);
	uपूर्णांक64_t msr_val = MSR_IDLE;
	uपूर्णांक64_t psscr_val = pnv_deepest_stop_psscr_val;

	क्रम_each_present_cpu(cpu) अणु
		uपूर्णांक64_t pir = get_hard_smp_processor_id(cpu);
		uपूर्णांक64_t hsprg0_val = (uपूर्णांक64_t)paca_ptrs[cpu];

		rc = opal_slw_set_reg(pir, SPRN_HSPRG0, hsprg0_val);
		अगर (rc != 0)
			वापस rc;

		rc = opal_slw_set_reg(pir, SPRN_LPCR, lpcr_val);
		अगर (rc != 0)
			वापस rc;

		अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			rc = opal_slw_set_reg(pir, P9_STOP_SPR_MSR, msr_val);
			अगर (rc)
				वापस rc;

			rc = opal_slw_set_reg(pir,
					      P9_STOP_SPR_PSSCR, psscr_val);

			अगर (rc)
				वापस rc;
		पूर्ण

		/* HIDs are per core रेजिस्टरs */
		अगर (cpu_thपढ़ो_in_core(cpu) == 0) अणु

			rc = opal_slw_set_reg(pir, SPRN_HMEER, hmeer_val);
			अगर (rc != 0)
				वापस rc;

			rc = opal_slw_set_reg(pir, SPRN_HID0, hid0_val);
			अगर (rc != 0)
				वापस rc;

			/* Only p8 needs to set extra HID regiters */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300)) अणु
				uपूर्णांक64_t hid1_val = mfspr(SPRN_HID1);
				uपूर्णांक64_t hid4_val = mfspr(SPRN_HID4);
				uपूर्णांक64_t hid5_val = mfspr(SPRN_HID5);

				rc = opal_slw_set_reg(pir, SPRN_HID1, hid1_val);
				अगर (rc != 0)
					वापस rc;

				rc = opal_slw_set_reg(pir, SPRN_HID4, hid4_val);
				अगर (rc != 0)
					वापस rc;

				rc = opal_slw_set_reg(pir, SPRN_HID5, hid5_val);
				अगर (rc != 0)
					वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32 pnv_get_supported_cpuidle_states(व्योम)
अणु
	वापस supported_cpuidle_states;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_get_supported_cpuidle_states);

अटल व्योम pnv_fastsleep_workaround_apply(व्योम *info)

अणु
	पूर्णांक rc;
	पूर्णांक *err = info;

	rc = opal_config_cpu_idle_state(OPAL_CONFIG_IDLE_FASTSLEEP,
					OPAL_CONFIG_IDLE_APPLY);
	अगर (rc)
		*err = 1;
पूर्ण

अटल bool घातer7_fastsleep_workaround_entry = true;
अटल bool घातer7_fastsleep_workaround_निकास = true;

/*
 * Used to store fastsleep workaround state
 * 0 - Workaround applied/unकरोne at fastsleep entry/निकास path (Default)
 * 1 - Workaround applied once, never unकरोne.
 */
अटल u8 fastsleep_workaround_applyonce;

अटल sमाप_प्रकार show_fastsleep_workaround_applyonce(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", fastsleep_workaround_applyonce);
पूर्ण

अटल sमाप_प्रकार store_fastsleep_workaround_applyonce(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	cpumask_t primary_thपढ़ो_mask;
	पूर्णांक err;
	u8 val;

	अगर (kstrtou8(buf, 0, &val) || val != 1)
		वापस -EINVAL;

	अगर (fastsleep_workaround_applyonce == 1)
		वापस count;

	/*
	 * fastsleep_workaround_applyonce = 1 implies
	 * fastsleep workaround needs to be left in 'applied' state on all
	 * the cores. Do this by-
	 * 1. Disable the 'undo' workaround in fastsleep निकास path
	 * 2. Sendi IPIs to all the cores which have at least one online thपढ़ो
	 * 3. Disable the 'apply' workaround in fastsleep entry path
	 *
	 * There is no need to send ipi to cores which have all thपढ़ोs
	 * offlined, as last thपढ़ो of the core entering fastsleep or deeper
	 * state would have applied workaround.
	 */
	घातer7_fastsleep_workaround_निकास = false;

	get_online_cpus();
	primary_thपढ़ो_mask = cpu_online_cores_map();
	on_each_cpu_mask(&primary_thपढ़ो_mask,
				pnv_fastsleep_workaround_apply,
				&err, 1);
	put_online_cpus();
	अगर (err) अणु
		pr_err("fastsleep_workaround_applyonce change failed while running pnv_fastsleep_workaround_apply");
		जाओ fail;
	पूर्ण

	घातer7_fastsleep_workaround_entry = false;

	fastsleep_workaround_applyonce = 1;

	वापस count;
fail:
	वापस -EIO;
पूर्ण

अटल DEVICE_ATTR(fastsleep_workaround_applyonce, 0600,
			show_fastsleep_workaround_applyonce,
			store_fastsleep_workaround_applyonce);

अटल अंतरभूत व्योम atomic_start_thपढ़ो_idle(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	पूर्णांक thपढ़ो_nr = cpu_thपढ़ो_in_core(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;

	clear_bit(thपढ़ो_nr, state);
पूर्ण

अटल अंतरभूत व्योम atomic_stop_thपढ़ो_idle(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	पूर्णांक thपढ़ो_nr = cpu_thपढ़ो_in_core(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;

	set_bit(thपढ़ो_nr, state);
पूर्ण

अटल अंतरभूत व्योम atomic_lock_thपढ़ो_idle(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;

	जबतक (unlikely(test_and_set_bit_lock(NR_PNV_CORE_IDLE_LOCK_BIT, state)))
		barrier();
पूर्ण

अटल अंतरभूत व्योम atomic_unlock_and_stop_thपढ़ो_idle(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	अचिन्हित दीर्घ thपढ़ो = 1UL << cpu_thपढ़ो_in_core(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;
	u64 s = READ_ONCE(*state);
	u64 new, पंचांगp;

	BUG_ON(!(s & PNV_CORE_IDLE_LOCK_BIT));
	BUG_ON(s & thपढ़ो);

again:
	new = (s | thपढ़ो) & ~PNV_CORE_IDLE_LOCK_BIT;
	पंचांगp = cmpxchg(state, s, new);
	अगर (unlikely(पंचांगp != s)) अणु
		s = पंचांगp;
		जाओ again;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम atomic_unlock_thपढ़ो_idle(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;

	BUG_ON(!test_bit(NR_PNV_CORE_IDLE_LOCK_BIT, state));
	clear_bit_unlock(NR_PNV_CORE_IDLE_LOCK_BIT, state);
पूर्ण

/* P7 and P8 */
काष्ठा p7_sprs अणु
	/* per core */
	u64 tscr;
	u64 worc;

	/* per subcore */
	u64 sdr1;
	u64 rpr;

	/* per thपढ़ो */
	u64 lpcr;
	u64 hfscr;
	u64 fscr;
	u64 purr;
	u64 spurr;
	u64 dscr;
	u64 wort;

	/* per thपढ़ो SPRs that get lost in shallow states */
	u64 amr;
	u64 iamr;
	u64 amor;
	u64 uamor;
पूर्ण;

अटल अचिन्हित दीर्घ घातer7_idle_insn(अचिन्हित दीर्घ type)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;
	अचिन्हित दीर्घ thपढ़ो = 1UL << cpu_thपढ़ो_in_core(cpu);
	अचिन्हित दीर्घ core_thपढ़ो_mask = (1UL << thपढ़ोs_per_core) - 1;
	अचिन्हित दीर्घ srr1;
	bool full_winkle;
	काष्ठा p7_sprs sprs = अणुपूर्ण; /* aव्योम false use-uninitialised */
	bool sprs_saved = false;
	पूर्णांक rc;

	अगर (unlikely(type != PNV_THREAD_NAP)) अणु
		atomic_lock_thपढ़ो_idle();

		BUG_ON(!(*state & thपढ़ो));
		*state &= ~thपढ़ो;

		अगर (घातer7_fastsleep_workaround_entry) अणु
			अगर ((*state & core_thपढ़ो_mask) == 0) अणु
				rc = opal_config_cpu_idle_state(
						OPAL_CONFIG_IDLE_FASTSLEEP,
						OPAL_CONFIG_IDLE_APPLY);
				BUG_ON(rc);
			पूर्ण
		पूर्ण

		अगर (type == PNV_THREAD_WINKLE) अणु
			sprs.tscr	= mfspr(SPRN_TSCR);
			sprs.worc	= mfspr(SPRN_WORC);

			sprs.sdr1	= mfspr(SPRN_SDR1);
			sprs.rpr	= mfspr(SPRN_RPR);

			sprs.lpcr	= mfspr(SPRN_LPCR);
			अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
				sprs.hfscr	= mfspr(SPRN_HFSCR);
				sprs.fscr	= mfspr(SPRN_FSCR);
			पूर्ण
			sprs.purr	= mfspr(SPRN_PURR);
			sprs.spurr	= mfspr(SPRN_SPURR);
			sprs.dscr	= mfspr(SPRN_DSCR);
			sprs.wort	= mfspr(SPRN_WORT);

			sprs_saved = true;

			/*
			 * Increment winkle counter and set all winkle bits अगर
			 * all thपढ़ोs are winkling. This allows wakeup side to
			 * distinguish between fast sleep and winkle state
			 * loss. Fast sleep still has to resync the समयbase so
			 * this may not be a really big win.
			 */
			*state += 1 << PNV_CORE_IDLE_WINKLE_COUNT_SHIFT;
			अगर ((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS)
					>> PNV_CORE_IDLE_WINKLE_COUNT_SHIFT
					== thपढ़ोs_per_core)
				*state |= PNV_CORE_IDLE_THREAD_WINKLE_BITS;
			WARN_ON((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS) == 0);
		पूर्ण

		atomic_unlock_thपढ़ो_idle();
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		sprs.amr	= mfspr(SPRN_AMR);
		sprs.iamr	= mfspr(SPRN_IAMR);
		sprs.amor	= mfspr(SPRN_AMOR);
		sprs.uamor	= mfspr(SPRN_UAMOR);
	पूर्ण

	local_paca->thपढ़ो_idle_state = type;
	srr1 = isa206_idle_insn_mayloss(type);		/* go idle */
	local_paca->thपढ़ो_idle_state = PNV_THREAD_RUNNING;

	WARN_ON_ONCE(!srr1);
	WARN_ON_ONCE(mfmsr() & (MSR_IR|MSR_DR));

	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		अगर ((srr1 & SRR1_WAKESTATE) != SRR1_WS_NOLOSS) अणु
			/*
			 * We करोn't need an isync after the mtsprs here because
			 * the upcoming mपंचांगsrd is execution synchronizing.
			 */
			mtspr(SPRN_AMR,		sprs.amr);
			mtspr(SPRN_IAMR,	sprs.iamr);
			mtspr(SPRN_AMOR,	sprs.amor);
			mtspr(SPRN_UAMOR,	sprs.uamor);
		पूर्ण
	पूर्ण

	अगर (unlikely((srr1 & SRR1_WAKEMASK_P8) == SRR1_WAKEHMI))
		hmi_exception_realmode(शून्य);

	अगर (likely((srr1 & SRR1_WAKESTATE) != SRR1_WS_HVLOSS)) अणु
		अगर (unlikely(type != PNV_THREAD_NAP)) अणु
			atomic_lock_thपढ़ो_idle();
			अगर (type == PNV_THREAD_WINKLE) अणु
				WARN_ON((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS) == 0);
				*state -= 1 << PNV_CORE_IDLE_WINKLE_COUNT_SHIFT;
				*state &= ~(thपढ़ो << PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT);
			पूर्ण
			atomic_unlock_and_stop_thपढ़ो_idle();
		पूर्ण
		वापस srr1;
	पूर्ण

	/* HV state loss */
	BUG_ON(type == PNV_THREAD_NAP);

	atomic_lock_thपढ़ो_idle();

	full_winkle = false;
	अगर (type == PNV_THREAD_WINKLE) अणु
		WARN_ON((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS) == 0);
		*state -= 1 << PNV_CORE_IDLE_WINKLE_COUNT_SHIFT;
		अगर (*state & (thपढ़ो << PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT)) अणु
			*state &= ~(thपढ़ो << PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT);
			full_winkle = true;
			BUG_ON(!sprs_saved);
		पूर्ण
	पूर्ण

	WARN_ON(*state & thपढ़ो);

	अगर ((*state & core_thपढ़ो_mask) != 0)
		जाओ core_woken;

	/* Per-core SPRs */
	अगर (full_winkle) अणु
		mtspr(SPRN_TSCR,	sprs.tscr);
		mtspr(SPRN_WORC,	sprs.worc);
	पूर्ण

	अगर (घातer7_fastsleep_workaround_निकास) अणु
		rc = opal_config_cpu_idle_state(OPAL_CONFIG_IDLE_FASTSLEEP,
						OPAL_CONFIG_IDLE_UNDO);
		BUG_ON(rc);
	पूर्ण

	/* TB */
	अगर (opal_resync_समयbase() != OPAL_SUCCESS)
		BUG();

core_woken:
	अगर (!full_winkle)
		जाओ subcore_woken;

	अगर ((*state & local_paca->subcore_sibling_mask) != 0)
		जाओ subcore_woken;

	/* Per-subcore SPRs */
	mtspr(SPRN_SDR1,	sprs.sdr1);
	mtspr(SPRN_RPR,		sprs.rpr);

subcore_woken:
	/*
	 * isync after restoring shared SPRs and beक्रमe unlocking. Unlock
	 * only contains hwsync which करोes not necessarily करो the right
	 * thing क्रम SPRs.
	 */
	isync();
	atomic_unlock_and_stop_thपढ़ो_idle();

	/* Fast sleep करोes not lose SPRs */
	अगर (!full_winkle)
		वापस srr1;

	/* Per-thपढ़ो SPRs */
	mtspr(SPRN_LPCR,	sprs.lpcr);
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		mtspr(SPRN_HFSCR,	sprs.hfscr);
		mtspr(SPRN_FSCR,	sprs.fscr);
	पूर्ण
	mtspr(SPRN_PURR,	sprs.purr);
	mtspr(SPRN_SPURR,	sprs.spurr);
	mtspr(SPRN_DSCR,	sprs.dscr);
	mtspr(SPRN_WORT,	sprs.wort);

	mtspr(SPRN_SPRG3,	local_paca->sprg_vdso);

	/*
	 * The SLB has to be restored here, but it someबार still
	 * contains entries, so the __ variant must be used to prevent
	 * multi hits.
	 */
	__slb_restore_bolted_realmode();

	वापस srr1;
पूर्ण

बाह्य अचिन्हित दीर्घ idle_kvm_start_guest(अचिन्हित दीर्घ srr1);

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अचिन्हित दीर्घ घातer7_offline(व्योम)
अणु
	अचिन्हित दीर्घ srr1;

	mपंचांगsr(MSR_IDLE);

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	/* Tell KVM we're entering idle. */
	/******************************************************/
	/*  N O T E   W E L L    ! ! !    N O T E   W E L L   */
	/* The following store to HSTATE_HWTHREAD_STATE(r13)  */
	/* MUST occur in real mode, i.e. with the MMU off,    */
	/* and the MMU must stay off until we clear this flag */
	/* and test HSTATE_HWTHREAD_REQ(r13) in               */
	/* pnv_घातersave_wakeup in this file.                 */
	/* The reason is that another thपढ़ो can चयन the   */
	/* MMU to a guest context whenever this flag is set   */
	/* to KVM_HWTHREAD_IN_IDLE, and अगर the MMU was on,    */
	/* that would potentially cause this thपढ़ो to start  */
	/* executing inकाष्ठाions from guest memory in        */
	/* hypervisor mode, leading to a host crash or data   */
	/* corruption, or worse.                              */
	/******************************************************/
	local_paca->kvm_hstate.hwthपढ़ो_state = KVM_HWTHREAD_IN_IDLE;
#पूर्ण_अगर

	__ppc64_runlatch_off();
	srr1 = घातer7_idle_insn(घातer7_offline_type);
	__ppc64_runlatch_on();

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	local_paca->kvm_hstate.hwthपढ़ो_state = KVM_HWTHREAD_IN_KERNEL;
	/* Order setting hwthपढ़ो_state vs. testing hwthपढ़ो_req */
	smp_mb();
	अगर (local_paca->kvm_hstate.hwthपढ़ो_req)
		srr1 = idle_kvm_start_guest(srr1);
#पूर्ण_अगर

	mपंचांगsr(MSR_KERNEL);

	वापस srr1;
पूर्ण
#पूर्ण_अगर

व्योम घातer7_idle_type(अचिन्हित दीर्घ type)
अणु
	अचिन्हित दीर्घ srr1;

	अगर (!prep_irq_क्रम_idle_irqsoff())
		वापस;

	mपंचांगsr(MSR_IDLE);
	__ppc64_runlatch_off();
	srr1 = घातer7_idle_insn(type);
	__ppc64_runlatch_on();
	mपंचांगsr(MSR_KERNEL);

	fini_irq_क्रम_idle_irqsoff();
	irq_set_pending_from_srr1(srr1);
पूर्ण

अटल व्योम घातer7_idle(व्योम)
अणु
	अगर (!घातersave_nap)
		वापस;

	घातer7_idle_type(PNV_THREAD_NAP);
पूर्ण

काष्ठा p9_sprs अणु
	/* per core */
	u64 ptcr;
	u64 rpr;
	u64 tscr;
	u64 ldbar;

	/* per thपढ़ो */
	u64 lpcr;
	u64 hfscr;
	u64 fscr;
	u64 pid;
	u64 purr;
	u64 spurr;
	u64 dscr;
	u64 wort;
	u64 ciabr;

	u64 mmcra;
	u32 mmcr0;
	u32 mmcr1;
	u64 mmcr2;

	/* per thपढ़ो SPRs that get lost in shallow states */
	u64 amr;
	u64 iamr;
	u64 amor;
	u64 uamor;
पूर्ण;

अटल अचिन्हित दीर्घ घातer9_idle_stop(अचिन्हित दीर्घ psscr, bool mmu_on)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;
	अचिन्हित दीर्घ core_thपढ़ो_mask = (1UL << thपढ़ोs_per_core) - 1;
	अचिन्हित दीर्घ srr1;
	अचिन्हित दीर्घ pls;
	अचिन्हित दीर्घ mmcr0 = 0;
	अचिन्हित दीर्घ mmcra = 0;
	काष्ठा p9_sprs sprs = अणुपूर्ण; /* aव्योम false used-uninitialised */
	bool sprs_saved = false;

	अगर (!(psscr & (PSSCR_EC|PSSCR_ESL))) अणु
		/* EC=ESL=0 हाल */

		BUG_ON(!mmu_on);

		/*
		 * Wake synchronously. SRESET via xscom may still cause
		 * a 0x100 घातersave wakeup with SRR1 reason!
		 */
		srr1 = isa300_idle_stop_noloss(psscr);		/* go idle */
		अगर (likely(!srr1))
			वापस 0;

		/*
		 * Registers not saved, can't recover!
		 * This would be a hardware bug
		 */
		BUG_ON((srr1 & SRR1_WAKESTATE) != SRR1_WS_NOLOSS);

		जाओ out;
	पूर्ण

	/* EC=ESL=1 हाल */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	अगर (cpu_has_feature(CPU_FTR_P9_TM_XER_SO_BUG)) अणु
		local_paca->requested_psscr = psscr;
		/* order setting requested_psscr vs testing करोnt_stop */
		smp_mb();
		अगर (atomic_पढ़ो(&local_paca->करोnt_stop)) अणु
			local_paca->requested_psscr = 0;
			वापस 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (!cpu_has_feature(CPU_FTR_POWER9_DD2_1)) अणु
		 /*
		  * POWER9 DD2 can incorrectly set PMAO when waking up
		  * after a state-loss idle. Saving and restoring MMCR0
		  * over idle is a workaround.
		  */
		mmcr0		= mfspr(SPRN_MMCR0);
	पूर्ण

	अगर ((psscr & PSSCR_RL_MASK) >= deep_spr_loss_state) अणु
		sprs.lpcr	= mfspr(SPRN_LPCR);
		sprs.hfscr	= mfspr(SPRN_HFSCR);
		sprs.fscr	= mfspr(SPRN_FSCR);
		sprs.pid	= mfspr(SPRN_PID);
		sprs.purr	= mfspr(SPRN_PURR);
		sprs.spurr	= mfspr(SPRN_SPURR);
		sprs.dscr	= mfspr(SPRN_DSCR);
		sprs.wort	= mfspr(SPRN_WORT);
		sprs.ciabr	= mfspr(SPRN_CIABR);

		sprs.mmcra	= mfspr(SPRN_MMCRA);
		sprs.mmcr0	= mfspr(SPRN_MMCR0);
		sprs.mmcr1	= mfspr(SPRN_MMCR1);
		sprs.mmcr2	= mfspr(SPRN_MMCR2);

		sprs.ptcr	= mfspr(SPRN_PTCR);
		sprs.rpr	= mfspr(SPRN_RPR);
		sprs.tscr	= mfspr(SPRN_TSCR);
		अगर (!firmware_has_feature(FW_FEATURE_ULTRAVISOR))
			sprs.ldbar = mfspr(SPRN_LDBAR);

		sprs_saved = true;

		atomic_start_thपढ़ो_idle();
	पूर्ण

	sprs.amr	= mfspr(SPRN_AMR);
	sprs.iamr	= mfspr(SPRN_IAMR);
	sprs.amor	= mfspr(SPRN_AMOR);
	sprs.uamor	= mfspr(SPRN_UAMOR);

	srr1 = isa300_idle_stop_mayloss(psscr);		/* go idle */

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	local_paca->requested_psscr = 0;
#पूर्ण_अगर

	psscr = mfspr(SPRN_PSSCR);

	WARN_ON_ONCE(!srr1);
	WARN_ON_ONCE(mfmsr() & (MSR_IR|MSR_DR));

	अगर ((srr1 & SRR1_WAKESTATE) != SRR1_WS_NOLOSS) अणु
		/*
		 * We करोn't need an isync after the mtsprs here because the
		 * upcoming mपंचांगsrd is execution synchronizing.
		 */
		mtspr(SPRN_AMR,		sprs.amr);
		mtspr(SPRN_IAMR,	sprs.iamr);
		mtspr(SPRN_AMOR,	sprs.amor);
		mtspr(SPRN_UAMOR,	sprs.uamor);

		/*
		 * Workaround क्रम POWER9 DD2.0, अगर we lost resources, the ERAT
		 * might have been corrupted and needs flushing. We also need
		 * to reload MMCR0 (see mmcr0 comment above).
		 */
		अगर (!cpu_has_feature(CPU_FTR_POWER9_DD2_1)) अणु
			यंत्र अस्थिर(PPC_ISA_3_0_INVALIDATE_ERAT);
			mtspr(SPRN_MMCR0, mmcr0);
		पूर्ण

		/*
		 * DD2.2 and earlier need to set then clear bit 60 in MMCRA
		 * to ensure the PMU starts running.
		 */
		mmcra = mfspr(SPRN_MMCRA);
		mmcra |= PPC_BIT(60);
		mtspr(SPRN_MMCRA, mmcra);
		mmcra &= ~PPC_BIT(60);
		mtspr(SPRN_MMCRA, mmcra);
	पूर्ण

	अगर (unlikely((srr1 & SRR1_WAKEMASK_P8) == SRR1_WAKEHMI))
		hmi_exception_realmode(शून्य);

	/*
	 * On POWER9, SRR1 bits करो not match exactly as expected.
	 * SRR1_WS_GPRLOSS (10b) can also result in SPR loss, so
	 * just always test PSSCR क्रम SPR/TB state loss.
	 */
	pls = (psscr & PSSCR_PLS) >> PSSCR_PLS_SHIFT;
	अगर (likely(pls < deep_spr_loss_state)) अणु
		अगर (sprs_saved)
			atomic_stop_thपढ़ो_idle();
		जाओ out;
	पूर्ण

	/* HV state loss */
	BUG_ON(!sprs_saved);

	atomic_lock_thपढ़ो_idle();

	अगर ((*state & core_thपढ़ो_mask) != 0)
		जाओ core_woken;

	/* Per-core SPRs */
	mtspr(SPRN_PTCR,	sprs.ptcr);
	mtspr(SPRN_RPR,		sprs.rpr);
	mtspr(SPRN_TSCR,	sprs.tscr);

	अगर (pls >= pnv_first_tb_loss_level) अणु
		/* TB loss */
		अगर (opal_resync_समयbase() != OPAL_SUCCESS)
			BUG();
	पूर्ण

	/*
	 * isync after restoring shared SPRs and beक्रमe unlocking. Unlock
	 * only contains hwsync which करोes not necessarily करो the right
	 * thing क्रम SPRs.
	 */
	isync();

core_woken:
	atomic_unlock_and_stop_thपढ़ो_idle();

	/* Per-thपढ़ो SPRs */
	mtspr(SPRN_LPCR,	sprs.lpcr);
	mtspr(SPRN_HFSCR,	sprs.hfscr);
	mtspr(SPRN_FSCR,	sprs.fscr);
	mtspr(SPRN_PID,		sprs.pid);
	mtspr(SPRN_PURR,	sprs.purr);
	mtspr(SPRN_SPURR,	sprs.spurr);
	mtspr(SPRN_DSCR,	sprs.dscr);
	mtspr(SPRN_WORT,	sprs.wort);
	mtspr(SPRN_CIABR,	sprs.ciabr);

	mtspr(SPRN_MMCRA,	sprs.mmcra);
	mtspr(SPRN_MMCR0,	sprs.mmcr0);
	mtspr(SPRN_MMCR1,	sprs.mmcr1);
	mtspr(SPRN_MMCR2,	sprs.mmcr2);
	अगर (!firmware_has_feature(FW_FEATURE_ULTRAVISOR))
		mtspr(SPRN_LDBAR, sprs.ldbar);

	mtspr(SPRN_SPRG3,	local_paca->sprg_vdso);

	अगर (!radix_enabled())
		__slb_restore_bolted_realmode();

out:
	अगर (mmu_on)
		mपंचांगsr(MSR_KERNEL);

	वापस srr1;
पूर्ण

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
/*
 * This is used in working around bugs in thपढ़ो reconfiguration
 * on POWER9 (at least up to Nimbus DD2.2) relating to transactional
 * memory and the way that XER[SO] is checkpoपूर्णांकed.
 * This function क्रमces the core पूर्णांकo SMT4 in order by asking
 * all other thपढ़ोs not to stop, and sending a message to any
 * that are in a stop state.
 * Must be called with preemption disabled.
 */
व्योम pnv_घातer9_क्रमce_smt4_catch(व्योम)
अणु
	पूर्णांक cpu, cpu0, thr;
	पूर्णांक awake_thपढ़ोs = 1;		/* this thपढ़ो is awake */
	पूर्णांक poke_thपढ़ोs = 0;
	पूर्णांक need_awake = thपढ़ोs_per_core;

	cpu = smp_processor_id();
	cpu0 = cpu & ~(thपढ़ोs_per_core - 1);
	क्रम (thr = 0; thr < thपढ़ोs_per_core; ++thr) अणु
		अगर (cpu != cpu0 + thr)
			atomic_inc(&paca_ptrs[cpu0+thr]->करोnt_stop);
	पूर्ण
	/* order setting करोnt_stop vs testing requested_psscr */
	smp_mb();
	क्रम (thr = 0; thr < thपढ़ोs_per_core; ++thr) अणु
		अगर (!paca_ptrs[cpu0+thr]->requested_psscr)
			++awake_thपढ़ोs;
		अन्यथा
			poke_thपढ़ोs |= (1 << thr);
	पूर्ण

	/* If at least 3 thपढ़ोs are awake, the core is in SMT4 alपढ़ोy */
	अगर (awake_thपढ़ोs < need_awake) अणु
		/* We have to wake some thपढ़ोs; we'll use msgsnd */
		क्रम (thr = 0; thr < thपढ़ोs_per_core; ++thr) अणु
			अगर (poke_thपढ़ोs & (1 << thr)) अणु
				ppc_msgsnd_sync();
				ppc_msgsnd(PPC_DBELL_MSGTYPE, 0,
					   paca_ptrs[cpu0+thr]->hw_cpu_id);
			पूर्ण
		पूर्ण
		/* now spin until at least 3 thपढ़ोs are awake */
		करो अणु
			क्रम (thr = 0; thr < thपढ़ोs_per_core; ++thr) अणु
				अगर ((poke_thपढ़ोs & (1 << thr)) &&
				    !paca_ptrs[cpu0+thr]->requested_psscr) अणु
					++awake_thपढ़ोs;
					poke_thपढ़ोs &= ~(1 << thr);
				पूर्ण
			पूर्ण
		पूर्ण जबतक (awake_thपढ़ोs < need_awake);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnv_घातer9_क्रमce_smt4_catch);

व्योम pnv_घातer9_क्रमce_smt4_release(व्योम)
अणु
	पूर्णांक cpu, cpu0, thr;

	cpu = smp_processor_id();
	cpu0 = cpu & ~(thपढ़ोs_per_core - 1);

	/* clear all the करोnt_stop flags */
	क्रम (thr = 0; thr < thपढ़ोs_per_core; ++thr) अणु
		अगर (cpu != cpu0 + thr)
			atomic_dec(&paca_ptrs[cpu0+thr]->करोnt_stop);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnv_घातer9_क्रमce_smt4_release);
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */

काष्ठा p10_sprs अणु
	/*
	 * SPRs that get lost in shallow states:
	 *
	 * P10 loses CR, LR, CTR, FPSCR, VSCR, XER, TAR, SPRG2, and HSPRG1
	 * isa300 idle routines restore CR, LR.
	 * CTR is अस्थिर
	 * idle thपढ़ो करोesn't use FP or VEC
	 * kernel करोesn't use TAR
	 * HSPRG1 is only live in HV पूर्णांकerrupt entry
	 * SPRG2 is only live in KVM guests, KVM handles it.
	 */
पूर्ण;

अटल अचिन्हित दीर्घ घातer10_idle_stop(अचिन्हित दीर्घ psscr, bool mmu_on)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);
	अचिन्हित दीर्घ *state = &paca_ptrs[first]->idle_state;
	अचिन्हित दीर्घ core_thपढ़ो_mask = (1UL << thपढ़ोs_per_core) - 1;
	अचिन्हित दीर्घ srr1;
	अचिन्हित दीर्घ pls;
//	काष्ठा p10_sprs sprs = अणुपूर्ण; /* aव्योम false used-uninitialised */
	bool sprs_saved = false;

	अगर (!(psscr & (PSSCR_EC|PSSCR_ESL))) अणु
		/* EC=ESL=0 हाल */

		BUG_ON(!mmu_on);

		/*
		 * Wake synchronously. SRESET via xscom may still cause
		 * a 0x100 घातersave wakeup with SRR1 reason!
		 */
		srr1 = isa300_idle_stop_noloss(psscr);		/* go idle */
		अगर (likely(!srr1))
			वापस 0;

		/*
		 * Registers not saved, can't recover!
		 * This would be a hardware bug
		 */
		BUG_ON((srr1 & SRR1_WAKESTATE) != SRR1_WS_NOLOSS);

		जाओ out;
	पूर्ण

	/* EC=ESL=1 हाल */
	अगर ((psscr & PSSCR_RL_MASK) >= deep_spr_loss_state) अणु
		/* XXX: save SPRs क्रम deep state loss here. */

		sprs_saved = true;

		atomic_start_thपढ़ो_idle();
	पूर्ण

	srr1 = isa300_idle_stop_mayloss(psscr);		/* go idle */

	psscr = mfspr(SPRN_PSSCR);

	WARN_ON_ONCE(!srr1);
	WARN_ON_ONCE(mfmsr() & (MSR_IR|MSR_DR));

	अगर (unlikely((srr1 & SRR1_WAKEMASK_P8) == SRR1_WAKEHMI))
		hmi_exception_realmode(शून्य);

	/*
	 * On POWER10, SRR1 bits करो not match exactly as expected.
	 * SRR1_WS_GPRLOSS (10b) can also result in SPR loss, so
	 * just always test PSSCR क्रम SPR/TB state loss.
	 */
	pls = (psscr & PSSCR_PLS) >> PSSCR_PLS_SHIFT;
	अगर (likely(pls < deep_spr_loss_state)) अणु
		अगर (sprs_saved)
			atomic_stop_thपढ़ो_idle();
		जाओ out;
	पूर्ण

	/* HV state loss */
	BUG_ON(!sprs_saved);

	atomic_lock_thपढ़ो_idle();

	अगर ((*state & core_thपढ़ो_mask) != 0)
		जाओ core_woken;

	/* XXX: restore per-core SPRs here */

	अगर (pls >= pnv_first_tb_loss_level) अणु
		/* TB loss */
		अगर (opal_resync_समयbase() != OPAL_SUCCESS)
			BUG();
	पूर्ण

	/*
	 * isync after restoring shared SPRs and beक्रमe unlocking. Unlock
	 * only contains hwsync which करोes not necessarily करो the right
	 * thing क्रम SPRs.
	 */
	isync();

core_woken:
	atomic_unlock_and_stop_thपढ़ो_idle();

	/* XXX: restore per-thपढ़ो SPRs here */

	अगर (!radix_enabled())
		__slb_restore_bolted_realmode();

out:
	अगर (mmu_on)
		mपंचांगsr(MSR_KERNEL);

	वापस srr1;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अचिन्हित दीर्घ arch300_offline_stop(अचिन्हित दीर्घ psscr)
अणु
	अचिन्हित दीर्घ srr1;

#अगर_अघोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	__ppc64_runlatch_off();
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		srr1 = घातer10_idle_stop(psscr, true);
	अन्यथा
		srr1 = घातer9_idle_stop(psscr, true);
	__ppc64_runlatch_on();
#अन्यथा
	/*
	 * Tell KVM we're entering idle.
	 * This करोes not have to be करोne in real mode because the P9 MMU
	 * is independent per-thपढ़ो. Some steppings share radix/hash mode
	 * between thपढ़ोs, but in that हाल KVM has a barrier sync in real
	 * mode beक्रमe and after चयनing between radix and hash.
	 *
	 * kvm_start_guest must still be called in real mode though, hence
	 * the false argument.
	 */
	local_paca->kvm_hstate.hwthपढ़ो_state = KVM_HWTHREAD_IN_IDLE;

	__ppc64_runlatch_off();
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		srr1 = घातer10_idle_stop(psscr, false);
	अन्यथा
		srr1 = घातer9_idle_stop(psscr, false);
	__ppc64_runlatch_on();

	local_paca->kvm_hstate.hwthपढ़ो_state = KVM_HWTHREAD_IN_KERNEL;
	/* Order setting hwthपढ़ो_state vs. testing hwthपढ़ो_req */
	smp_mb();
	अगर (local_paca->kvm_hstate.hwthपढ़ो_req)
		srr1 = idle_kvm_start_guest(srr1);
	mपंचांगsr(MSR_KERNEL);
#पूर्ण_अगर

	वापस srr1;
पूर्ण
#पूर्ण_अगर

व्योम arch300_idle_type(अचिन्हित दीर्घ stop_psscr_val,
				      अचिन्हित दीर्घ stop_psscr_mask)
अणु
	अचिन्हित दीर्घ psscr;
	अचिन्हित दीर्घ srr1;

	अगर (!prep_irq_क्रम_idle_irqsoff())
		वापस;

	psscr = mfspr(SPRN_PSSCR);
	psscr = (psscr & ~stop_psscr_mask) | stop_psscr_val;

	__ppc64_runlatch_off();
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		srr1 = घातer10_idle_stop(psscr, true);
	अन्यथा
		srr1 = घातer9_idle_stop(psscr, true);
	__ppc64_runlatch_on();

	fini_irq_क्रम_idle_irqsoff();

	irq_set_pending_from_srr1(srr1);
पूर्ण

/*
 * Used क्रम ppc_md.घातer_save which needs a function with no parameters
 */
अटल व्योम arch300_idle(व्योम)
अणु
	arch300_idle_type(pnv_शेष_stop_val, pnv_शेष_stop_mask);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

व्योम pnv_program_cpu_hotplug_lpcr(अचिन्हित पूर्णांक cpu, u64 lpcr_val)
अणु
	u64 pir = get_hard_smp_processor_id(cpu);

	mtspr(SPRN_LPCR, lpcr_val);

	/*
	 * Program the LPCR via stop-api only अगर the deepest stop state
	 * can lose hypervisor context.
	 */
	अगर (supported_cpuidle_states & OPAL_PM_LOSE_FULL_CONTEXT)
		opal_slw_set_reg(pir, SPRN_LPCR, lpcr_val);
पूर्ण

/*
 * pnv_cpu_offline: A function that माला_दो the CPU पूर्णांकo the deepest
 * available platक्रमm idle state on a CPU-Offline.
 * पूर्णांकerrupts hard disabled and no lazy irq pending.
 */
अचिन्हित दीर्घ pnv_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ srr1;

	__ppc64_runlatch_off();

	अगर (cpu_has_feature(CPU_FTR_ARCH_300) && deepest_stop_found) अणु
		अचिन्हित दीर्घ psscr;

		psscr = mfspr(SPRN_PSSCR);
		psscr = (psscr & ~pnv_deepest_stop_psscr_mask) |
						pnv_deepest_stop_psscr_val;
		srr1 = arch300_offline_stop(psscr);
	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_206) && घातer7_offline_type) अणु
		srr1 = घातer7_offline();
	पूर्ण अन्यथा अणु
		/* This is the fallback method. We emulate snooze */
		जबतक (!generic_check_cpu_restart(cpu)) अणु
			HMT_low();
			HMT_very_low();
		पूर्ण
		srr1 = 0;
		HMT_medium();
	पूर्ण

	__ppc64_runlatch_on();

	वापस srr1;
पूर्ण
#पूर्ण_अगर

/*
 * Power ISA 3.0 idle initialization.
 *
 * POWER ISA 3.0 defines a new SPR Processor stop Status and Control
 * Register (PSSCR) to control idle behavior.
 *
 * PSSCR layout:
 * ----------------------------------------------------------
 * | PLS | /// | SD | ESL | EC | PSLL | /// | TR | MTL | RL |
 * ----------------------------------------------------------
 * 0      4     41   42    43   44     48    54   56    60
 *
 * PSSCR key fields:
 *	Bits 0:3  - Power-Saving Level Status (PLS). This field indicates the
 *	lowest घातer-saving state the thपढ़ो entered since stop inकाष्ठाion was
 *	last executed.
 *
 *	Bit 41 - Status Disable(SD)
 *	0 - Shows PLS entries
 *	1 - PLS entries are all 0
 *
 *	Bit 42 - Enable State Loss
 *	0 - No state is lost irrespective of other fields
 *	1 - Allows state loss
 *
 *	Bit 43 - Exit Criterion
 *	0 - Exit from घातer-save mode on any पूर्णांकerrupt
 *	1 - Exit from घातer-save mode controlled by LPCR's PECE bits
 *
 *	Bits 44:47 - Power-Saving Level Limit
 *	This limits the घातer-saving level that can be entered पूर्णांकo.
 *
 *	Bits 60:63 - Requested Level
 *	Used to specअगरy which घातer-saving level must be entered on executing
 *	stop inकाष्ठाion
 */

पूर्णांक validate_psscr_val_mask(u64 *psscr_val, u64 *psscr_mask, u32 flags)
अणु
	पूर्णांक err = 0;

	/*
	 * psscr_mask == 0xf indicates an older firmware.
	 * Set reमुख्यing fields of psscr to the शेष values.
	 * See NOTE above definition of PSSCR_HV_DEFAULT_VAL
	 */
	अगर (*psscr_mask == 0xf) अणु
		*psscr_val = *psscr_val | PSSCR_HV_DEFAULT_VAL;
		*psscr_mask = PSSCR_HV_DEFAULT_MASK;
		वापस err;
	पूर्ण

	/*
	 * New firmware is expected to set the psscr_val bits correctly.
	 * Validate that the following invariants are correctly मुख्यtained by
	 * the new firmware.
	 * - ESL bit value matches the EC bit value.
	 * - ESL bit is set क्रम all the deep stop states.
	 */
	अगर (GET_PSSCR_ESL(*psscr_val) != GET_PSSCR_EC(*psscr_val)) अणु
		err = ERR_EC_ESL_MISMATCH;
	पूर्ण अन्यथा अगर ((flags & OPAL_PM_LOSE_FULL_CONTEXT) &&
		GET_PSSCR_ESL(*psscr_val) == 0) अणु
		err = ERR_DEEP_STATE_ESL_MISMATCH;
	पूर्ण

	वापस err;
पूर्ण

/*
 * pnv_arch300_idle_init: Initializes the शेष idle state, first
 *                        deep idle state and deepest idle state on
 *                        ISA 3.0 CPUs.
 *
 * @np: /ibm,opal/घातer-mgt device node
 * @flags: cpu-idle-state-flags array
 * @dt_idle_states: Number of idle state entries
 * Returns 0 on success
 */
अटल व्योम __init pnv_arch300_idle_init(व्योम)
अणु
	u64 max_residency_ns = 0;
	पूर्णांक i;

	/* stop is not really architected, we only have p9,p10 drivers */
	अगर (!pvr_version_is(PVR_POWER10) && !pvr_version_is(PVR_POWER9))
		वापस;

	/*
	 * pnv_deepest_stop_अणुval,maskपूर्ण should be set to values corresponding to
	 * the deepest stop state.
	 *
	 * pnv_शेष_stop_अणुval,maskपूर्ण should be set to values corresponding to
	 * the deepest loss-less (OPAL_PM_STOP_INST_FAST) stop state.
	 */
	pnv_first_tb_loss_level = MAX_STOP_STATE + 1;
	deep_spr_loss_state = MAX_STOP_STATE + 1;
	क्रम (i = 0; i < nr_pnv_idle_states; i++) अणु
		पूर्णांक err;
		काष्ठा pnv_idle_states_t *state = &pnv_idle_states[i];
		u64 psscr_rl = state->psscr_val & PSSCR_RL_MASK;

		/* No deep loss driver implemented क्रम POWER10 yet */
		अगर (pvr_version_is(PVR_POWER10) &&
				state->flags & (OPAL_PM_TIMEBASE_STOP|OPAL_PM_LOSE_FULL_CONTEXT))
			जारी;

		अगर ((state->flags & OPAL_PM_TIMEBASE_STOP) &&
		     (pnv_first_tb_loss_level > psscr_rl))
			pnv_first_tb_loss_level = psscr_rl;

		अगर ((state->flags & OPAL_PM_LOSE_FULL_CONTEXT) &&
		     (deep_spr_loss_state > psscr_rl))
			deep_spr_loss_state = psscr_rl;

		/*
		 * The idle code करोes not deal with TB loss occurring
		 * in a shallower state than SPR loss, so क्रमce it to
		 * behave like SPRs are lost अगर TB is lost. POWER9 would
		 * never encouter this, but a POWER8 core would अगर it
		 * implemented the stop inकाष्ठाion. So this is क्रम क्रमward
		 * compatibility.
		 */
		अगर ((state->flags & OPAL_PM_TIMEBASE_STOP) &&
		     (deep_spr_loss_state > psscr_rl))
			deep_spr_loss_state = psscr_rl;

		err = validate_psscr_val_mask(&state->psscr_val,
					      &state->psscr_mask,
					      state->flags);
		अगर (err) अणु
			report_invalid_psscr_val(state->psscr_val, err);
			जारी;
		पूर्ण

		state->valid = true;

		अगर (max_residency_ns < state->residency_ns) अणु
			max_residency_ns = state->residency_ns;
			pnv_deepest_stop_psscr_val = state->psscr_val;
			pnv_deepest_stop_psscr_mask = state->psscr_mask;
			pnv_deepest_stop_flag = state->flags;
			deepest_stop_found = true;
		पूर्ण

		अगर (!शेष_stop_found &&
		    (state->flags & OPAL_PM_STOP_INST_FAST)) अणु
			pnv_शेष_stop_val = state->psscr_val;
			pnv_शेष_stop_mask = state->psscr_mask;
			शेष_stop_found = true;
			WARN_ON(state->flags & OPAL_PM_LOSE_FULL_CONTEXT);
		पूर्ण
	पूर्ण

	अगर (unlikely(!शेष_stop_found)) अणु
		pr_warn("cpuidle-powernv: No suitable default stop state found. Disabling platform idle.\n");
	पूर्ण अन्यथा अणु
		ppc_md.घातer_save = arch300_idle;
		pr_info("cpuidle-powernv: Default stop: psscr = 0x%016llx,mask=0x%016llx\n",
			pnv_शेष_stop_val, pnv_शेष_stop_mask);
	पूर्ण

	अगर (unlikely(!deepest_stop_found)) अणु
		pr_warn("cpuidle-powernv: No suitable stop state for CPU-Hotplug. Offlined CPUs will busy wait");
	पूर्ण अन्यथा अणु
		pr_info("cpuidle-powernv: Deepest stop: psscr = 0x%016llx,mask=0x%016llx\n",
			pnv_deepest_stop_psscr_val,
			pnv_deepest_stop_psscr_mask);
	पूर्ण

	pr_info("cpuidle-powernv: First stop level that may lose SPRs = 0x%llx\n",
		deep_spr_loss_state);

	pr_info("cpuidle-powernv: First stop level that may lose timebase = 0x%llx\n",
		pnv_first_tb_loss_level);
पूर्ण

अटल व्योम __init pnv_disable_deep_states(व्योम)
अणु
	/*
	 * The stop-api is unable to restore hypervisor
	 * resources on wakeup from platक्रमm idle states which
	 * lose full context. So disable such states.
	 */
	supported_cpuidle_states &= ~OPAL_PM_LOSE_FULL_CONTEXT;
	pr_warn("cpuidle-powernv: Disabling idle states that lose full context\n");
	pr_warn("cpuidle-powernv: Idle power-savings, CPU-Hotplug affected\n");

	अगर (cpu_has_feature(CPU_FTR_ARCH_300) &&
	    (pnv_deepest_stop_flag & OPAL_PM_LOSE_FULL_CONTEXT)) अणु
		/*
		 * Use the शेष stop state क्रम CPU-Hotplug
		 * अगर available.
		 */
		अगर (शेष_stop_found) अणु
			pnv_deepest_stop_psscr_val = pnv_शेष_stop_val;
			pnv_deepest_stop_psscr_mask = pnv_शेष_stop_mask;
			pr_warn("cpuidle-powernv: Offlined CPUs will stop with psscr = 0x%016llx\n",
				pnv_deepest_stop_psscr_val);
		पूर्ण अन्यथा अणु /* Fallback to snooze loop क्रम CPU-Hotplug */
			deepest_stop_found = false;
			pr_warn("cpuidle-powernv: Offlined CPUs will busy wait\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Probe device tree क्रम supported idle states
 */
अटल व्योम __init pnv_probe_idle_states(व्योम)
अणु
	पूर्णांक i;

	अगर (nr_pnv_idle_states < 0) अणु
		pr_warn("cpuidle-powernv: no idle states found in the DT\n");
		वापस;
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		pnv_arch300_idle_init();

	क्रम (i = 0; i < nr_pnv_idle_states; i++)
		supported_cpuidle_states |= pnv_idle_states[i].flags;
पूर्ण

/*
 * This function parses device-tree and populates all the inक्रमmation
 * पूर्णांकo pnv_idle_states काष्ठाure. It also sets up nr_pnv_idle_states
 * which is the number of cpuidle states discovered through device-tree.
 */

अटल पूर्णांक pnv_parse_cpuidle_dt(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक nr_idle_states, i;
	पूर्णांक rc = 0;
	u32 *temp_u32;
	u64 *temp_u64;
	स्थिर अक्षर **temp_string;

	np = of_find_node_by_path("/ibm,opal/power-mgt");
	अगर (!np) अणु
		pr_warn("opal: PowerMgmt Node not found\n");
		वापस -ENODEV;
	पूर्ण
	nr_idle_states = of_property_count_u32_elems(np,
						"ibm,cpu-idle-state-flags");

	pnv_idle_states = kसुस्मृति(nr_idle_states, माप(*pnv_idle_states),
				  GFP_KERNEL);
	temp_u32 = kसुस्मृति(nr_idle_states, माप(u32),  GFP_KERNEL);
	temp_u64 = kसुस्मृति(nr_idle_states, माप(u64),  GFP_KERNEL);
	temp_string = kसुस्मृति(nr_idle_states, माप(अक्षर *),  GFP_KERNEL);

	अगर (!(pnv_idle_states && temp_u32 && temp_u64 && temp_string)) अणु
		pr_err("Could not allocate memory for dt parsing\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Read flags */
	अगर (of_property_पढ़ो_u32_array(np, "ibm,cpu-idle-state-flags",
				       temp_u32, nr_idle_states)) अणु
		pr_warn("cpuidle-powernv: missing ibm,cpu-idle-state-flags in DT\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < nr_idle_states; i++)
		pnv_idle_states[i].flags = temp_u32[i];

	/* Read latencies */
	अगर (of_property_पढ़ो_u32_array(np, "ibm,cpu-idle-state-latencies-ns",
				       temp_u32, nr_idle_states)) अणु
		pr_warn("cpuidle-powernv: missing ibm,cpu-idle-state-latencies-ns in DT\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < nr_idle_states; i++)
		pnv_idle_states[i].latency_ns = temp_u32[i];

	/* Read residencies */
	अगर (of_property_पढ़ो_u32_array(np, "ibm,cpu-idle-state-residency-ns",
				       temp_u32, nr_idle_states)) अणु
		pr_warn("cpuidle-powernv: missing ibm,cpu-idle-state-residency-ns in DT\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < nr_idle_states; i++)
		pnv_idle_states[i].residency_ns = temp_u32[i];

	/* For घातer9 and later */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		/* Read pm_crtl_val */
		अगर (of_property_पढ़ो_u64_array(np, "ibm,cpu-idle-state-psscr",
					       temp_u64, nr_idle_states)) अणु
			pr_warn("cpuidle-powernv: missing ibm,cpu-idle-state-psscr in DT\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < nr_idle_states; i++)
			pnv_idle_states[i].psscr_val = temp_u64[i];

		/* Read pm_crtl_mask */
		अगर (of_property_पढ़ो_u64_array(np, "ibm,cpu-idle-state-psscr-mask",
					       temp_u64, nr_idle_states)) अणु
			pr_warn("cpuidle-powernv: missing ibm,cpu-idle-state-psscr-mask in DT\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < nr_idle_states; i++)
			pnv_idle_states[i].psscr_mask = temp_u64[i];
	पूर्ण

	/*
	 * घातer8 specअगरic properties ibm,cpu-idle-state-pmicr-mask and
	 * ibm,cpu-idle-state-pmicr-val were never used and there is no
	 * plan to use it in near future. Hence, not parsing these properties
	 */

	अगर (of_property_पढ़ो_string_array(np, "ibm,cpu-idle-state-names",
					  temp_string, nr_idle_states) < 0) अणु
		pr_warn("cpuidle-powernv: missing ibm,cpu-idle-state-names in DT\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < nr_idle_states; i++)
		strlcpy(pnv_idle_states[i].name, temp_string[i],
			PNV_IDLE_NAME_LEN);
	nr_pnv_idle_states = nr_idle_states;
	rc = 0;
out:
	kमुक्त(temp_u32);
	kमुक्त(temp_u64);
	kमुक्त(temp_string);
	वापस rc;
पूर्ण

अटल पूर्णांक __init pnv_init_idle_states(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक rc = 0;

	/* Set up PACA fields */
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा paca_काष्ठा *p = paca_ptrs[cpu];

		p->idle_state = 0;
		अगर (cpu == cpu_first_thपढ़ो_sibling(cpu))
			p->idle_state = (1 << thपढ़ोs_per_core) - 1;

		अगर (!cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			/* P7/P8 nap */
			p->thपढ़ो_idle_state = PNV_THREAD_RUNNING;
		पूर्ण अन्यथा अगर (pvr_version_is(PVR_POWER9)) अणु
			/* P9 stop workarounds */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
			p->requested_psscr = 0;
			atomic_set(&p->करोnt_stop, 0);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	/* In हाल we error out nr_pnv_idle_states will be zero */
	nr_pnv_idle_states = 0;
	supported_cpuidle_states = 0;

	अगर (cpuidle_disable != IDLE_NO_OVERRIDE)
		जाओ out;
	rc = pnv_parse_cpuidle_dt();
	अगर (rc)
		वापस rc;
	pnv_probe_idle_states();

	अगर (!cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (!(supported_cpuidle_states & OPAL_PM_SLEEP_ENABLED_ER1)) अणु
			घातer7_fastsleep_workaround_entry = false;
			घातer7_fastsleep_workaround_निकास = false;
		पूर्ण अन्यथा अणु
			/*
			 * OPAL_PM_SLEEP_ENABLED_ER1 is set. It indicates that
			 * workaround is needed to use fastsleep. Provide sysfs
			 * control to choose how this workaround has to be
			 * applied.
			 */
			device_create_file(cpu_subsys.dev_root,
				&dev_attr_fastsleep_workaround_applyonce);
		पूर्ण

		update_subcore_sibling_mask();

		अगर (supported_cpuidle_states & OPAL_PM_NAP_ENABLED) अणु
			ppc_md.घातer_save = घातer7_idle;
			घातer7_offline_type = PNV_THREAD_NAP;
		पूर्ण

		अगर ((supported_cpuidle_states & OPAL_PM_WINKLE_ENABLED) &&
			   (supported_cpuidle_states & OPAL_PM_LOSE_FULL_CONTEXT))
			घातer7_offline_type = PNV_THREAD_WINKLE;
		अन्यथा अगर ((supported_cpuidle_states & OPAL_PM_SLEEP_ENABLED) ||
			   (supported_cpuidle_states & OPAL_PM_SLEEP_ENABLED_ER1))
			घातer7_offline_type = PNV_THREAD_SLEEP;
	पूर्ण

	अगर (supported_cpuidle_states & OPAL_PM_LOSE_FULL_CONTEXT) अणु
		अगर (pnv_save_sprs_क्रम_deep_states())
			pnv_disable_deep_states();
	पूर्ण

out:
	वापस 0;
पूर्ण
machine_subsys_initcall(घातernv, pnv_init_idle_states);
