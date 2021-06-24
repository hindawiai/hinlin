<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: Support क्रम hardware भवization extensions
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Yann Le Du <ledu@kymasys.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbex.h>

#समावेश <linux/kvm_host.h>

#समावेश "interrupt.h"
#अगर_घोषित CONFIG_CPU_LOONGSON64
#समावेश "loongson_regs.h"
#पूर्ण_अगर

#समावेश "trace.h"

/* Poपूर्णांकers to last VCPU loaded on each physical CPU */
अटल काष्ठा kvm_vcpu *last_vcpu[NR_CPUS];
/* Poपूर्णांकers to last VCPU executed on each physical CPU */
अटल काष्ठा kvm_vcpu *last_exec_vcpu[NR_CPUS];

/*
 * Number of guest VTLB entries to use, so we can catch inconsistency between
 * CPUs.
 */
अटल अचिन्हित पूर्णांक kvm_vz_guest_vtlb_size;

अटल अंतरभूत दीर्घ kvm_vz_पढ़ो_gc0_ebase(व्योम)
अणु
	अगर (माप(दीर्घ) == 8 && cpu_has_ebase_wg)
		वापस पढ़ो_gc0_ebase_64();
	अन्यथा
		वापस पढ़ो_gc0_ebase();
पूर्ण

अटल अंतरभूत व्योम kvm_vz_ग_लिखो_gc0_ebase(दीर्घ v)
अणु
	/*
	 * First ग_लिखो with WG=1 to ग_लिखो upper bits, then ग_लिखो again in हाल
	 * WG should be left at 0.
	 * ग_लिखो_gc0_ebase_64() is no दीर्घer UNDEFINED since R6.
	 */
	अगर (माप(दीर्घ) == 8 &&
	    (cpu_has_mips64r6 || cpu_has_ebase_wg)) अणु
		ग_लिखो_gc0_ebase_64(v | MIPS_EBASE_WG);
		ग_लिखो_gc0_ebase_64(v);
	पूर्ण अन्यथा अणु
		ग_लिखो_gc0_ebase(v | MIPS_EBASE_WG);
		ग_लिखो_gc0_ebase(v);
	पूर्ण
पूर्ण

/*
 * These Config bits may be writable by the guest:
 * Config:	[K23, KU] (!TLB), K0
 * Config1:	(none)
 * Config2:	[TU, SU] (impl)
 * Config3:	ISAOnExc
 * Config4:	FTLBPageSize
 * Config5:	K, CV, MSAEn, UFE, FRE, SBRI, UFR
 */

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस CONF_CM_CMASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config1_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config2_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config3_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस MIPS_CONF3_ISA_OE;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config4_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	/* no need to be exact */
	वापस MIPS_CONF4_VFTLBPAGESIZE;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config5_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक mask = MIPS_CONF5_K | MIPS_CONF5_CV | MIPS_CONF5_SBRI;

	/* Permit MSAEn changes अगर MSA supported and enabled */
	अगर (kvm_mips_guest_has_msa(&vcpu->arch))
		mask |= MIPS_CONF5_MSAEN;

	/*
	 * Permit guest FPU mode changes अगर FPU is enabled and the relevant
	 * feature exists according to FIR रेजिस्टर.
	 */
	अगर (kvm_mips_guest_has_fpu(&vcpu->arch)) अणु
		अगर (cpu_has_ufr)
			mask |= MIPS_CONF5_UFR;
		अगर (cpu_has_fre)
			mask |= MIPS_CONF5_FRE | MIPS_CONF5_UFE;
	पूर्ण

	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config6_guest_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस LOONGSON_CONF6_INTIMER | LOONGSON_CONF6_EXTIMER;
पूर्ण

/*
 * VZ optionally allows these additional Config bits to be written by root:
 * Config:	M, [MT]
 * Config1:	M, [MMUSize-1, C2, MD, PC, WR, CA], FP
 * Config2:	M
 * Config3:	M, MSAP, [BPG], ULRI, [DSP2P, DSPP], CTXTC, [ITL, LPA, VEIC,
 *		VInt, SP, CDMM, MT, SM, TL]
 * Config4:	M, [VTLBSizeExt, MMUSizeExt]
 * Config5:	MRP
 */

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vz_config_guest_wrmask(vcpu) | MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config1_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक mask = kvm_vz_config1_guest_wrmask(vcpu) | MIPS_CONF_M;

	/* Permit FPU to be present अगर FPU is supported */
	अगर (kvm_mips_guest_can_have_fpu(&vcpu->arch))
		mask |= MIPS_CONF1_FP;

	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config2_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vz_config2_guest_wrmask(vcpu) | MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config3_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक mask = kvm_vz_config3_guest_wrmask(vcpu) | MIPS_CONF_M |
		MIPS_CONF3_ULRI | MIPS_CONF3_CTXTC;

	/* Permit MSA to be present अगर MSA is supported */
	अगर (kvm_mips_guest_can_have_msa(&vcpu->arch))
		mask |= MIPS_CONF3_MSA;

	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config4_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vz_config4_guest_wrmask(vcpu) | MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config5_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vz_config5_guest_wrmask(vcpu) | MIPS_CONF5_MRP;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_vz_config6_user_wrmask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vz_config6_guest_wrmask(vcpu) |
		LOONGSON_CONF6_SFBEN | LOONGSON_CONF6_FTLBDIS;
पूर्ण

अटल gpa_t kvm_vz_gva_to_gpa_cb(gva_t gva)
अणु
	/* VZ guest has alपढ़ोy converted gva to gpa */
	वापस gva;
पूर्ण

अटल व्योम kvm_vz_queue_irq(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority)
अणु
	set_bit(priority, &vcpu->arch.pending_exceptions);
	clear_bit(priority, &vcpu->arch.pending_exceptions_clr);
पूर्ण

अटल व्योम kvm_vz_dequeue_irq(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority)
अणु
	clear_bit(priority, &vcpu->arch.pending_exceptions);
	set_bit(priority, &vcpu->arch.pending_exceptions_clr);
पूर्ण

अटल व्योम kvm_vz_queue_समयr_पूर्णांक_cb(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * समयr expiry is asynchronous to vcpu execution thereक्रमe defer guest
	 * cp0 accesses
	 */
	kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_TIMER);
पूर्ण

अटल व्योम kvm_vz_dequeue_समयr_पूर्णांक_cb(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * समयr expiry is asynchronous to vcpu execution thereक्रमe defer guest
	 * cp0 accesses
	 */
	kvm_vz_dequeue_irq(vcpu, MIPS_EXC_INT_TIMER);
पूर्ण

अटल व्योम kvm_vz_queue_io_पूर्णांक_cb(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_mips_पूर्णांकerrupt *irq)
अणु
	पूर्णांक पूर्णांकr = (पूर्णांक)irq->irq;

	/*
	 * पूर्णांकerrupts are asynchronous to vcpu execution thereक्रमe defer guest
	 * cp0 accesses
	 */
	kvm_vz_queue_irq(vcpu, kvm_irq_to_priority(पूर्णांकr));
पूर्ण

अटल व्योम kvm_vz_dequeue_io_पूर्णांक_cb(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_mips_पूर्णांकerrupt *irq)
अणु
	पूर्णांक पूर्णांकr = (पूर्णांक)irq->irq;

	/*
	 * पूर्णांकerrupts are asynchronous to vcpu execution thereक्रमe defer guest
	 * cp0 accesses
	 */
	kvm_vz_dequeue_irq(vcpu, kvm_irq_to_priority(-पूर्णांकr));
पूर्ण

अटल पूर्णांक kvm_vz_irq_deliver_cb(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority,
				 u32 cause)
अणु
	u32 irq = (priority < MIPS_EXC_MAX) ?
		kvm_priority_to_irq[priority] : 0;

	चयन (priority) अणु
	हाल MIPS_EXC_INT_TIMER:
		set_gc0_cause(C_TI);
		अवरोध;

	हाल MIPS_EXC_INT_IO_1:
	हाल MIPS_EXC_INT_IO_2:
	हाल MIPS_EXC_INT_IPI_1:
	हाल MIPS_EXC_INT_IPI_2:
		अगर (cpu_has_guestctl2)
			set_c0_guestctl2(irq);
		अन्यथा
			set_gc0_cause(irq);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	clear_bit(priority, &vcpu->arch.pending_exceptions);
	वापस 1;
पूर्ण

अटल पूर्णांक kvm_vz_irq_clear_cb(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority,
			       u32 cause)
अणु
	u32 irq = (priority < MIPS_EXC_MAX) ?
		kvm_priority_to_irq[priority] : 0;

	चयन (priority) अणु
	हाल MIPS_EXC_INT_TIMER:
		/*
		 * Explicitly clear irq associated with Cause.IP[IPTI]
		 * अगर GuestCtl2 भव पूर्णांकerrupt रेजिस्टर not
		 * supported or अगर not using GuestCtl2 Hardware Clear.
		 */
		अगर (cpu_has_guestctl2) अणु
			अगर (!(पढ़ो_c0_guestctl2() & (irq << 14)))
				clear_c0_guestctl2(irq);
		पूर्ण अन्यथा अणु
			clear_gc0_cause(irq);
		पूर्ण
		अवरोध;

	हाल MIPS_EXC_INT_IO_1:
	हाल MIPS_EXC_INT_IO_2:
	हाल MIPS_EXC_INT_IPI_1:
	हाल MIPS_EXC_INT_IPI_2:
		/* Clear GuestCtl2.VIP irq अगर not using Hardware Clear */
		अगर (cpu_has_guestctl2) अणु
			अगर (!(पढ़ो_c0_guestctl2() & (irq << 14)))
				clear_c0_guestctl2(irq);
		पूर्ण अन्यथा अणु
			clear_gc0_cause(irq);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	clear_bit(priority, &vcpu->arch.pending_exceptions_clr);
	वापस 1;
पूर्ण

/*
 * VZ guest समयr handling.
 */

/**
 * kvm_vz_should_use_hसमयr() - Find whether to use the VZ hard guest समयr.
 * @vcpu:	Virtual CPU.
 *
 * Returns:	true अगर the VZ GTOffset & real guest CP0_Count should be used
 *		instead of software emulation of guest समयr.
 *		false otherwise.
 */
अटल bool kvm_vz_should_use_hसमयr(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_mips_count_disabled(vcpu))
		वापस false;

	/* Chosen frequency must match real frequency */
	अगर (mips_hpt_frequency != vcpu->arch.count_hz)
		वापस false;

	/* We करोn't support a CP0_GTOffset with fewer bits than CP0_Count */
	अगर (current_cpu_data.gtoffset_mask != 0xffffffff)
		वापस false;

	वापस true;
पूर्ण

/**
 * _kvm_vz_restore_sसमयr() - Restore soft समयr state.
 * @vcpu:	Virtual CPU.
 * @compare:	CP0_Compare रेजिस्टर value, restored by caller.
 * @cause:	CP0_Cause रेजिस्टर to restore.
 *
 * Restore VZ state relating to the soft समयr. The hard समयr can be enabled
 * later.
 */
अटल व्योम _kvm_vz_restore_sसमयr(काष्ठा kvm_vcpu *vcpu, u32 compare,
				   u32 cause)
अणु
	/*
	 * Aव्योम spurious counter पूर्णांकerrupts by setting Guest CP0_Count to just
	 * after Guest CP0_Compare.
	 */
	ग_लिखो_c0_gtoffset(compare - पढ़ो_c0_count());

	back_to_back_c0_hazard();
	ग_लिखो_gc0_cause(cause);
पूर्ण

/**
 * _kvm_vz_restore_hसमयr() - Restore hard समयr state.
 * @vcpu:	Virtual CPU.
 * @compare:	CP0_Compare रेजिस्टर value, restored by caller.
 * @cause:	CP0_Cause रेजिस्टर to restore.
 *
 * Restore hard समयr Guest.Count & Guest.Cause taking care to preserve the
 * value of Guest.CP0_Cause.TI जबतक restoring Guest.CP0_Cause.
 */
अटल व्योम _kvm_vz_restore_hसमयr(काष्ठा kvm_vcpu *vcpu,
				   u32 compare, u32 cause)
अणु
	u32 start_count, after_count;
	kसमय_प्रकार मुक्तze_समय;
	अचिन्हित दीर्घ flags;

	/*
	 * Freeze the soft-समयr and sync the guest CP0_Count with it. We करो
	 * this with पूर्णांकerrupts disabled to aव्योम latency.
	 */
	local_irq_save(flags);
	मुक्तze_समय = kvm_mips_मुक्तze_hrसमयr(vcpu, &start_count);
	ग_लिखो_c0_gtoffset(start_count - पढ़ो_c0_count());
	local_irq_restore(flags);

	/* restore guest CP0_Cause, as TI may alपढ़ोy be set */
	back_to_back_c0_hazard();
	ग_लिखो_gc0_cause(cause);

	/*
	 * The above sequence isn't atomic and would result in lost समयr
	 * पूर्णांकerrupts अगर we're not careful. Detect अगर a समयr पूर्णांकerrupt is due
	 * and निश्चित it.
	 */
	back_to_back_c0_hazard();
	after_count = पढ़ो_gc0_count();
	अगर (after_count - start_count > compare - start_count - 1)
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_TIMER);
पूर्ण

/**
 * kvm_vz_restore_समयr() - Restore समयr state.
 * @vcpu:	Virtual CPU.
 *
 * Restore soft समयr state from saved context.
 */
अटल व्योम kvm_vz_restore_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	u32 cause, compare;

	compare = kvm_पढ़ो_sw_gc0_compare(cop0);
	cause = kvm_पढ़ो_sw_gc0_cause(cop0);

	ग_लिखो_gc0_compare(compare);
	_kvm_vz_restore_sसमयr(vcpu, compare, cause);
पूर्ण

/**
 * kvm_vz_acquire_hसमयr() - Switch to hard समयr state.
 * @vcpu:	Virtual CPU.
 *
 * Restore hard समयr state on top of existing soft समयr state अगर possible.
 *
 * Since hard समयr won't reमुख्य active over preemption, preemption should be
 * disabled by the caller.
 */
व्योम kvm_vz_acquire_hसमयr(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 gctl0;

	gctl0 = पढ़ो_c0_guestctl0();
	अगर (!(gctl0 & MIPS_GCTL0_GT) && kvm_vz_should_use_hसमयr(vcpu)) अणु
		/* enable guest access to hard समयr */
		ग_लिखो_c0_guestctl0(gctl0 | MIPS_GCTL0_GT);

		_kvm_vz_restore_hसमयr(vcpu, पढ़ो_gc0_compare(),
				       पढ़ो_gc0_cause());
	पूर्ण
पूर्ण

/**
 * _kvm_vz_save_hसमयr() - Switch to software emulation of guest समयr.
 * @vcpu:	Virtual CPU.
 * @compare:	Poपूर्णांकer to ग_लिखो compare value to.
 * @cause:	Poपूर्णांकer to ग_लिखो cause value to.
 *
 * Save VZ guest समयr state and चयन to software emulation of guest CP0
 * समयr. The hard समयr must alपढ़ोy be in use, so preemption should be
 * disabled.
 */
अटल व्योम _kvm_vz_save_hसमयr(काष्ठा kvm_vcpu *vcpu,
				u32 *out_compare, u32 *out_cause)
अणु
	u32 cause, compare, beक्रमe_count, end_count;
	kसमय_प्रकार beक्रमe_समय;

	compare = पढ़ो_gc0_compare();
	*out_compare = compare;

	beक्रमe_समय = kसमय_get();

	/*
	 * Record the CP0_Count *prior* to saving CP0_Cause, so we have a समय
	 * at which no pending समयr पूर्णांकerrupt is missing.
	 */
	beक्रमe_count = पढ़ो_gc0_count();
	back_to_back_c0_hazard();
	cause = पढ़ो_gc0_cause();
	*out_cause = cause;

	/*
	 * Record a final CP0_Count which we will transfer to the soft-समयr.
	 * This is recorded *after* saving CP0_Cause, so we करोn't get any समयr
	 * पूर्णांकerrupts from just after the final CP0_Count poपूर्णांक.
	 */
	back_to_back_c0_hazard();
	end_count = पढ़ो_gc0_count();

	/*
	 * The above sequence isn't atomic, so we could miss a समयr पूर्णांकerrupt
	 * between पढ़ोing CP0_Cause and end_count. Detect and record any समयr
	 * पूर्णांकerrupt due between beक्रमe_count and end_count.
	 */
	अगर (end_count - beक्रमe_count > compare - beक्रमe_count - 1)
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_TIMER);

	/*
	 * Restore soft-समयr, ignoring a small amount of negative drअगरt due to
	 * delay between मुक्तze_hrसमयr and setting CP0_GTOffset.
	 */
	kvm_mips_restore_hrसमयr(vcpu, beक्रमe_समय, end_count, -0x10000);
पूर्ण

/**
 * kvm_vz_save_समयr() - Save guest समयr state.
 * @vcpu:	Virtual CPU.
 *
 * Save VZ guest समयr state and चयन to soft guest समयr अगर hard समयr was in
 * use.
 */
अटल व्योम kvm_vz_save_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	u32 gctl0, compare, cause;

	gctl0 = पढ़ो_c0_guestctl0();
	अगर (gctl0 & MIPS_GCTL0_GT) अणु
		/* disable guest use of hard समयr */
		ग_लिखो_c0_guestctl0(gctl0 & ~MIPS_GCTL0_GT);

		/* save hard समयr state */
		_kvm_vz_save_hसमयr(vcpu, &compare, &cause);
	पूर्ण अन्यथा अणु
		compare = पढ़ो_gc0_compare();
		cause = पढ़ो_gc0_cause();
	पूर्ण

	/* save समयr-related state to VCPU context */
	kvm_ग_लिखो_sw_gc0_cause(cop0, cause);
	kvm_ग_लिखो_sw_gc0_compare(cop0, compare);
पूर्ण

/**
 * kvm_vz_lose_hसमयr() - Ensure hard guest समयr is not in use.
 * @vcpu:	Virtual CPU.
 *
 * Transfers the state of the hard guest समयr to the soft guest समयr, leaving
 * guest state पूर्णांकact so it can जारी to be used with the soft समयr.
 */
व्योम kvm_vz_lose_hसमयr(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 gctl0, compare, cause;

	preempt_disable();
	gctl0 = पढ़ो_c0_guestctl0();
	अगर (gctl0 & MIPS_GCTL0_GT) अणु
		/* disable guest use of समयr */
		ग_लिखो_c0_guestctl0(gctl0 & ~MIPS_GCTL0_GT);

		/* चयन to soft समयr */
		_kvm_vz_save_hसमयr(vcpu, &compare, &cause);

		/* leave soft समयr in usable state */
		_kvm_vz_restore_sसमयr(vcpu, compare, cause);
	पूर्ण
	preempt_enable();
पूर्ण

/**
 * is_eva_access() - Find whether an inकाष्ठाion is an EVA memory accessor.
 * @inst:	32-bit inकाष्ठाion encoding.
 *
 * Finds whether @inst encodes an EVA memory access inकाष्ठाion, which would
 * indicate that emulation of it should access the user mode address space
 * instead of the kernel mode address space. This matters क्रम MUSUK segments
 * which are TLB mapped क्रम user mode but unmapped क्रम kernel mode.
 *
 * Returns:	Whether @inst encodes an EVA accessor inकाष्ठाion.
 */
अटल bool is_eva_access(जोड़ mips_inकाष्ठाion inst)
अणु
	अगर (inst.spec3_क्रमmat.opcode != spec3_op)
		वापस false;

	चयन (inst.spec3_क्रमmat.func) अणु
	हाल lwle_op:
	हाल lwre_op:
	हाल cachee_op:
	हाल sbe_op:
	हाल she_op:
	हाल sce_op:
	हाल swe_op:
	हाल swle_op:
	हाल swre_op:
	हाल prefe_op:
	हाल lbue_op:
	हाल lhue_op:
	हाल lbe_op:
	हाल lhe_op:
	हाल lle_op:
	हाल lwe_op:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * is_eva_am_mapped() - Find whether an access mode is mapped.
 * @vcpu:	KVM VCPU state.
 * @am:		3-bit encoded access mode.
 * @eu:		Segment becomes unmapped and uncached when Status.ERL=1.
 *
 * Decode @am to find whether it encodes a mapped segment क्रम the current VCPU
 * state. Where necessary @eu and the actual inकाष्ठाion causing the fault are
 * taken पूर्णांकo account to make the decision.
 *
 * Returns:	Whether the VCPU faulted on a TLB mapped address.
 */
अटल bool is_eva_am_mapped(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक am, bool eu)
अणु
	u32 am_lookup;
	पूर्णांक err;

	/*
	 * Interpret access control mode. We assume address errors will alपढ़ोy
	 * have been caught by the guest, leaving us with:
	 *      AM      UM  SM  KM  31..24 23..16
	 * UK    0 000          Unm   0      0
	 * MK    1 001          TLB   1
	 * MSK   2 010      TLB TLB   1
	 * MUSK  3 011  TLB TLB TLB   1
	 * MUSUK 4 100  TLB TLB Unm   0      1
	 * USK   5 101      Unm Unm   0      0
	 * -     6 110                0      0
	 * UUSK  7 111  Unm Unm Unm   0      0
	 *
	 * We shअगरt a magic value by AM across the sign bit to find अगर always
	 * TLB mapped, and अगर not shअगरt by 8 again to find अगर it depends on KM.
	 */
	am_lookup = 0x70080000 << am;
	अगर ((s32)am_lookup < 0) अणु
		/*
		 * MK, MSK, MUSK
		 * Always TLB mapped, unless SegCtl.EU && ERL
		 */
		अगर (!eu || !(पढ़ो_gc0_status() & ST0_ERL))
			वापस true;
	पूर्ण अन्यथा अणु
		am_lookup <<= 8;
		अगर ((s32)am_lookup < 0) अणु
			जोड़ mips_inकाष्ठाion inst;
			अचिन्हित पूर्णांक status;
			u32 *opc;

			/*
			 * MUSUK
			 * TLB mapped अगर not in kernel mode
			 */
			status = पढ़ो_gc0_status();
			अगर (!(status & (ST0_EXL | ST0_ERL)) &&
			    (status & ST0_KSU))
				वापस true;
			/*
			 * EVA access inकाष्ठाions in kernel
			 * mode access user address space.
			 */
			opc = (u32 *)vcpu->arch.pc;
			अगर (vcpu->arch.host_cp0_cause & CAUSEF_BD)
				opc += 1;
			err = kvm_get_badinstr(opc, vcpu, &inst.word);
			अगर (!err && is_eva_access(inst))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/**
 * kvm_vz_gva_to_gpa() - Convert valid GVA to GPA.
 * @vcpu:	KVM VCPU state.
 * @gva:	Guest भव address to convert.
 * @gpa:	Output guest physical address.
 *
 * Convert a guest भव address (GVA) which is valid according to the guest
 * context, to a guest physical address (GPA).
 *
 * Returns:	0 on success.
 *		-त्रुटि_सं on failure.
 */
अटल पूर्णांक kvm_vz_gva_to_gpa(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
			     अचिन्हित दीर्घ *gpa)
अणु
	u32 gva32 = gva;
	अचिन्हित दीर्घ segctl;

	अगर ((दीर्घ)gva == (s32)gva32) अणु
		/* Handle canonical 32-bit भव address */
		अगर (cpu_guest_has_segments) अणु
			अचिन्हित दीर्घ mask, pa;

			चयन (gva32 >> 29) अणु
			हाल 0:
			हाल 1: /* CFG5 (1GB) */
				segctl = पढ़ो_gc0_segctl2() >> 16;
				mask = (अचिन्हित दीर्घ)0xfc0000000ull;
				अवरोध;
			हाल 2:
			हाल 3: /* CFG4 (1GB) */
				segctl = पढ़ो_gc0_segctl2();
				mask = (अचिन्हित दीर्घ)0xfc0000000ull;
				अवरोध;
			हाल 4: /* CFG3 (512MB) */
				segctl = पढ़ो_gc0_segctl1() >> 16;
				mask = (अचिन्हित दीर्घ)0xfe0000000ull;
				अवरोध;
			हाल 5: /* CFG2 (512MB) */
				segctl = पढ़ो_gc0_segctl1();
				mask = (अचिन्हित दीर्घ)0xfe0000000ull;
				अवरोध;
			हाल 6: /* CFG1 (512MB) */
				segctl = पढ़ो_gc0_segctl0() >> 16;
				mask = (अचिन्हित दीर्घ)0xfe0000000ull;
				अवरोध;
			हाल 7: /* CFG0 (512MB) */
				segctl = पढ़ो_gc0_segctl0();
				mask = (अचिन्हित दीर्घ)0xfe0000000ull;
				अवरोध;
			शेष:
				/*
				 * GCC 4.9 isn't smart enough to figure out that
				 * segctl and mask are always initialised.
				 */
				unreachable();
			पूर्ण

			अगर (is_eva_am_mapped(vcpu, (segctl >> 4) & 0x7,
					     segctl & 0x0008))
				जाओ tlb_mapped;

			/* Unmapped, find guest physical address */
			pa = (segctl << 20) & mask;
			pa |= gva32 & ~mask;
			*gpa = pa;
			वापस 0;
		पूर्ण अन्यथा अगर ((s32)gva32 < (s32)0xc0000000) अणु
			/* legacy unmapped KSeg0 or KSeg1 */
			*gpa = gva32 & 0x1fffffff;
			वापस 0;
		पूर्ण
#अगर_घोषित CONFIG_64BIT
	पूर्ण अन्यथा अगर ((gva & 0xc000000000000000) == 0x8000000000000000) अणु
		/* XKPHYS */
		अगर (cpu_guest_has_segments) अणु
			/*
			 * Each of the 8 regions can be overridden by SegCtl2.XR
			 * to use SegCtl1.XAM.
			 */
			segctl = पढ़ो_gc0_segctl2();
			अगर (segctl & (1ull << (56 + ((gva >> 59) & 0x7)))) अणु
				segctl = पढ़ो_gc0_segctl1();
				अगर (is_eva_am_mapped(vcpu, (segctl >> 59) & 0x7,
						     0))
					जाओ tlb_mapped;
			पूर्ण

		पूर्ण
		/*
		 * Traditionally fully unmapped.
		 * Bits 61:59 specअगरy the CCA, which we can just mask off here.
		 * Bits 58:PABITS should be zero, but we shouldn't have got here
		 * अगर it wasn't.
		 */
		*gpa = gva & 0x07ffffffffffffff;
		वापस 0;
#पूर्ण_अगर
	पूर्ण

tlb_mapped:
	वापस kvm_vz_guest_tlb_lookup(vcpu, gva, gpa);
पूर्ण

/**
 * kvm_vz_badvaddr_to_gpa() - Convert GVA BadVAddr from root exception to GPA.
 * @vcpu:	KVM VCPU state.
 * @badvaddr:	Root BadVAddr.
 * @gpa:	Output guest physical address.
 *
 * VZ implementations are permitted to report guest भव addresses (GVA) in
 * BadVAddr on a root exception during guest execution, instead of the more
 * convenient guest physical addresses (GPA). When we get a GVA, this function
 * converts it to a GPA, taking पूर्णांकo account guest segmentation and guest TLB
 * state.
 *
 * Returns:	0 on success.
 *		-त्रुटि_सं on failure.
 */
अटल पूर्णांक kvm_vz_badvaddr_to_gpa(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ badvaddr,
				  अचिन्हित दीर्घ *gpa)
अणु
	अचिन्हित पूर्णांक gexccode = (vcpu->arch.host_cp0_guestctl0 &
				 MIPS_GCTL0_GEXC) >> MIPS_GCTL0_GEXC_SHIFT;

	/* If BadVAddr is GPA, then all is well in the world */
	अगर (likely(gexccode == MIPS_GCTL0_GEXC_GPA)) अणु
		*gpa = badvaddr;
		वापस 0;
	पूर्ण

	/* Otherwise we'd expect it to be GVA ... */
	अगर (WARN(gexccode != MIPS_GCTL0_GEXC_GVA,
		 "Unexpected gexccode %#x\n", gexccode))
		वापस -EINVAL;

	/* ... and we need to perक्रमm the GVA->GPA translation in software */
	वापस kvm_vz_gva_to_gpa(vcpu, badvaddr, gpa);
पूर्ण

अटल पूर्णांक kvm_trap_vz_no_handler(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 *opc = (u32 *) vcpu->arch.pc;
	u32 cause = vcpu->arch.host_cp0_cause;
	u32 exccode = (cause & CAUSEF_EXCCODE) >> CAUSEB_EXCCODE;
	अचिन्हित दीर्घ badvaddr = vcpu->arch.host_cp0_badvaddr;
	u32 inst = 0;

	/*
	 *  Fetch the inकाष्ठाion.
	 */
	अगर (cause & CAUSEF_BD)
		opc += 1;
	kvm_get_badinstr(opc, vcpu, &inst);

	kvm_err("Exception Code: %d not handled @ PC: %p, inst: 0x%08x BadVaddr: %#lx Status: %#x\n",
		exccode, opc, inst, badvaddr,
		पढ़ो_gc0_status());
	kvm_arch_vcpu_dump_regs(vcpu);
	vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
	वापस RESUME_HOST;
पूर्ण

अटल अचिन्हित दीर्घ mips_process_maar(अचिन्हित पूर्णांक op, अचिन्हित दीर्घ val)
अणु
	/* Mask off unused bits */
	अचिन्हित दीर्घ mask = 0xfffff000 | MIPS_MAAR_S | MIPS_MAAR_VL;

	अगर (पढ़ो_gc0_pagegrain() & PG_ELPA)
		mask |= 0x00ffffff00000000ull;
	अगर (cpu_guest_has_mvh)
		mask |= MIPS_MAAR_VH;

	/* Set or clear VH */
	अगर (op == mtc_op) अणु
		/* clear VH */
		val &= ~MIPS_MAAR_VH;
	पूर्ण अन्यथा अगर (op == dmtc_op) अणु
		/* set VH to match VL */
		val &= ~MIPS_MAAR_VH;
		अगर (val & MIPS_MAAR_VL)
			val |= MIPS_MAAR_VH;
	पूर्ण

	वापस val & mask;
पूर्ण

अटल व्योम kvm_ग_लिखो_maari(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;

	val &= MIPS_MAARI_INDEX;
	अगर (val == MIPS_MAARI_INDEX)
		kvm_ग_लिखो_sw_gc0_maari(cop0, ARRAY_SIZE(vcpu->arch.maar) - 1);
	अन्यथा अगर (val < ARRAY_SIZE(vcpu->arch.maar))
		kvm_ग_लिखो_sw_gc0_maari(cop0, val);
पूर्ण

अटल क्रमागत emulation_result kvm_vz_gpsi_cop0(जोड़ mips_inकाष्ठाion inst,
					      u32 *opc, u32 cause,
					      काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	क्रमागत emulation_result er = EMULATE_DONE;
	u32 rt, rd, sel;
	अचिन्हित दीर्घ curr_pc;
	अचिन्हित दीर्घ val;

	/*
	 * Update PC and hold onto current PC in हाल there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	अगर (er == EMULATE_FAIL)
		वापस er;

	अगर (inst.co_क्रमmat.co) अणु
		चयन (inst.co_क्रमmat.func) अणु
		हाल रुको_op:
			er = kvm_mips_emul_रुको(vcpu);
			अवरोध;
		शेष:
			er = EMULATE_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		rt = inst.c0r_क्रमmat.rt;
		rd = inst.c0r_क्रमmat.rd;
		sel = inst.c0r_क्रमmat.sel;

		चयन (inst.c0r_क्रमmat.rs) अणु
		हाल dmfc_op:
		हाल mfc_op:
#अगर_घोषित CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
			cop0->stat[rd][sel]++;
#पूर्ण_अगर
			अगर (rd == MIPS_CP0_COUNT &&
			    sel == 0) अणु			/* Count */
				val = kvm_mips_पढ़ो_count(vcpu);
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_COMPARE &&
				   sel == 0) अणु		/* Compare */
				val = पढ़ो_gc0_compare();
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_LLADDR &&
				   sel == 0) अणु		/* LLAddr */
				अगर (cpu_guest_has_rw_llb)
					val = पढ़ो_gc0_lladdr() &
						MIPS_LLADDR_LLB;
				अन्यथा
					val = 0;
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_LLADDR &&
				   sel == 1 &&		/* MAAR */
				   cpu_guest_has_maar &&
				   !cpu_guest_has_dyn_maar) अणु
				/* MAARI must be in range */
				BUG_ON(kvm_पढ़ो_sw_gc0_maari(cop0) >=
						ARRAY_SIZE(vcpu->arch.maar));
				val = vcpu->arch.maar[
					kvm_पढ़ो_sw_gc0_maari(cop0)];
			पूर्ण अन्यथा अगर ((rd == MIPS_CP0_PRID &&
				    (sel == 0 ||	/* PRid */
				     sel == 2 ||	/* CDMMBase */
				     sel == 3)) ||	/* CMGCRBase */
				   (rd == MIPS_CP0_STATUS &&
				    (sel == 2 ||	/* SRSCtl */
				     sel == 3)) ||	/* SRSMap */
				   (rd == MIPS_CP0_CONFIG &&
				    (sel == 6 ||	/* Config6 */
				     sel == 7)) ||	/* Config7 */
				   (rd == MIPS_CP0_LLADDR &&
				    (sel == 2) &&	/* MAARI */
				    cpu_guest_has_maar &&
				    !cpu_guest_has_dyn_maar) ||
				   (rd == MIPS_CP0_ERRCTL &&
				    (sel == 0))) अणु	/* ErrCtl */
				val = cop0->reg[rd][sel];
#अगर_घोषित CONFIG_CPU_LOONGSON64
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_DIAG &&
				   (sel == 0)) अणु	/* Diag */
				val = cop0->reg[rd][sel];
#पूर्ण_अगर
			पूर्ण अन्यथा अणु
				val = 0;
				er = EMULATE_FAIL;
			पूर्ण

			अगर (er != EMULATE_FAIL) अणु
				/* Sign extend */
				अगर (inst.c0r_क्रमmat.rs == mfc_op)
					val = (पूर्णांक)val;
				vcpu->arch.gprs[rt] = val;
			पूर्ण

			trace_kvm_hwr(vcpu, (inst.c0r_क्रमmat.rs == mfc_op) ?
					KVM_TRACE_MFC0 : KVM_TRACE_DMFC0,
				      KVM_TRACE_COP0(rd, sel), val);
			अवरोध;

		हाल dmtc_op:
		हाल mtc_op:
#अगर_घोषित CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
			cop0->stat[rd][sel]++;
#पूर्ण_अगर
			val = vcpu->arch.gprs[rt];
			trace_kvm_hwr(vcpu, (inst.c0r_क्रमmat.rs == mtc_op) ?
					KVM_TRACE_MTC0 : KVM_TRACE_DMTC0,
				      KVM_TRACE_COP0(rd, sel), val);

			अगर (rd == MIPS_CP0_COUNT &&
			    sel == 0) अणु			/* Count */
				kvm_vz_lose_hसमयr(vcpu);
				kvm_mips_ग_लिखो_count(vcpu, vcpu->arch.gprs[rt]);
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_COMPARE &&
				   sel == 0) अणु		/* Compare */
				kvm_mips_ग_लिखो_compare(vcpu,
						       vcpu->arch.gprs[rt],
						       true);
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_LLADDR &&
				   sel == 0) अणु		/* LLAddr */
				/*
				 * P5600 generates GPSI on guest MTC0 LLAddr.
				 * Only allow the guest to clear LLB.
				 */
				अगर (cpu_guest_has_rw_llb &&
				    !(val & MIPS_LLADDR_LLB))
					ग_लिखो_gc0_lladdr(0);
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_LLADDR &&
				   sel == 1 &&		/* MAAR */
				   cpu_guest_has_maar &&
				   !cpu_guest_has_dyn_maar) अणु
				val = mips_process_maar(inst.c0r_क्रमmat.rs,
							val);

				/* MAARI must be in range */
				BUG_ON(kvm_पढ़ो_sw_gc0_maari(cop0) >=
						ARRAY_SIZE(vcpu->arch.maar));
				vcpu->arch.maar[kvm_पढ़ो_sw_gc0_maari(cop0)] =
									val;
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_LLADDR &&
				   (sel == 2) &&	/* MAARI */
				   cpu_guest_has_maar &&
				   !cpu_guest_has_dyn_maar) अणु
				kvm_ग_लिखो_maari(vcpu, val);
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_CONFIG &&
				   (sel == 6)) अणु
				cop0->reg[rd][sel] = (पूर्णांक)val;
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_ERRCTL &&
				   (sel == 0)) अणु	/* ErrCtl */
				/* ignore the written value */
#अगर_घोषित CONFIG_CPU_LOONGSON64
			पूर्ण अन्यथा अगर (rd == MIPS_CP0_DIAG &&
				   (sel == 0)) अणु	/* Diag */
				अचिन्हित दीर्घ flags;

				local_irq_save(flags);
				अगर (val & LOONGSON_DIAG_BTB) अणु
					/* Flush BTB */
					set_c0_diag(LOONGSON_DIAG_BTB);
				पूर्ण
				अगर (val & LOONGSON_DIAG_ITLB) अणु
					/* Flush ITLB */
					set_c0_diag(LOONGSON_DIAG_ITLB);
				पूर्ण
				अगर (val & LOONGSON_DIAG_DTLB) अणु
					/* Flush DTLB */
					set_c0_diag(LOONGSON_DIAG_DTLB);
				पूर्ण
				अगर (val & LOONGSON_DIAG_VTLB) अणु
					/* Flush VTLB */
					kvm_loongson_clear_guest_vtlb();
				पूर्ण
				अगर (val & LOONGSON_DIAG_FTLB) अणु
					/* Flush FTLB */
					kvm_loongson_clear_guest_ftlb();
				पूर्ण
				local_irq_restore(flags);
#पूर्ण_अगर
			पूर्ण अन्यथा अणु
				er = EMULATE_FAIL;
			पूर्ण
			अवरोध;

		शेष:
			er = EMULATE_FAIL;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Rollback PC only अगर emulation was unsuccessful */
	अगर (er == EMULATE_FAIL) अणु
		kvm_err("[%#lx]%s: unsupported cop0 instruction 0x%08x\n",
			curr_pc, __func__, inst.word);

		vcpu->arch.pc = curr_pc;
	पूर्ण

	वापस er;
पूर्ण

अटल क्रमागत emulation_result kvm_vz_gpsi_cache(जोड़ mips_inकाष्ठाion inst,
					       u32 *opc, u32 cause,
					       काष्ठा kvm_vcpu *vcpu)
अणु
	क्रमागत emulation_result er = EMULATE_DONE;
	u32 cache, op_inst, op, base;
	s16 offset;
	काष्ठा kvm_vcpu_arch *arch = &vcpu->arch;
	अचिन्हित दीर्घ va, curr_pc;

	/*
	 * Update PC and hold onto current PC in हाल there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	अगर (er == EMULATE_FAIL)
		वापस er;

	base = inst.i_क्रमmat.rs;
	op_inst = inst.i_क्रमmat.rt;
	अगर (cpu_has_mips_r6)
		offset = inst.spec3_क्रमmat.simmediate;
	अन्यथा
		offset = inst.i_क्रमmat.simmediate;
	cache = op_inst & CacheOp_Cache;
	op = op_inst & CacheOp_Op;

	va = arch->gprs[base] + offset;

	kvm_debug("CACHE (cache: %#x, op: %#x, base[%d]: %#lx, offset: %#x\n",
		  cache, op, base, arch->gprs[base], offset);

	/* Secondary or tirtiary cache ops ignored */
	अगर (cache != Cache_I && cache != Cache_D)
		वापस EMULATE_DONE;

	चयन (op_inst) अणु
	हाल Index_Invalidate_I:
		flush_icache_line_indexed(va);
		वापस EMULATE_DONE;
	हाल Index_Writeback_Inv_D:
		flush_dcache_line_indexed(va);
		वापस EMULATE_DONE;
	हाल Hit_Invalidate_I:
	हाल Hit_Invalidate_D:
	हाल Hit_Writeback_Inv_D:
		अगर (boot_cpu_type() == CPU_CAVIUM_OCTEON3) अणु
			/* We can just flush entire icache */
			local_flush_icache_range(0, 0);
			वापस EMULATE_DONE;
		पूर्ण

		/* So far, other platक्रमms support guest hit cache ops */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kvm_err("@ %#lx/%#lx CACHE (cache: %#x, op: %#x, base[%d]: %#lx, offset: %#x\n",
		curr_pc, vcpu->arch.gprs[31], cache, op, base, arch->gprs[base],
		offset);
	/* Rollback PC */
	vcpu->arch.pc = curr_pc;

	वापस EMULATE_FAIL;
पूर्ण

#अगर_घोषित CONFIG_CPU_LOONGSON64
अटल क्रमागत emulation_result kvm_vz_gpsi_lwc2(जोड़ mips_inकाष्ठाion inst,
					      u32 *opc, u32 cause,
					      काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक rs, rd;
	अचिन्हित पूर्णांक hostcfg;
	अचिन्हित दीर्घ curr_pc;
	क्रमागत emulation_result er = EMULATE_DONE;

	/*
	 * Update PC and hold onto current PC in हाल there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	अगर (er == EMULATE_FAIL)
		वापस er;

	rs = inst.loongson3_lscsr_क्रमmat.rs;
	rd = inst.loongson3_lscsr_क्रमmat.rd;
	चयन (inst.loongson3_lscsr_क्रमmat.fr) अणु
	हाल 0x8:  /* Read CPUCFG */
		++vcpu->stat.vz_cpucfg_निकासs;
		hostcfg = पढ़ो_cpucfg(vcpu->arch.gprs[rs]);

		चयन (vcpu->arch.gprs[rs]) अणु
		हाल LOONGSON_CFG0:
			vcpu->arch.gprs[rd] = 0x14c000;
			अवरोध;
		हाल LOONGSON_CFG1:
			hostcfg &= (LOONGSON_CFG1_FP | LOONGSON_CFG1_MMI |
				    LOONGSON_CFG1_MSA1 | LOONGSON_CFG1_MSA2 |
				    LOONGSON_CFG1_SFBP);
			vcpu->arch.gprs[rd] = hostcfg;
			अवरोध;
		हाल LOONGSON_CFG2:
			hostcfg &= (LOONGSON_CFG2_LEXT1 | LOONGSON_CFG2_LEXT2 |
				    LOONGSON_CFG2_LEXT3 | LOONGSON_CFG2_LSPW);
			vcpu->arch.gprs[rd] = hostcfg;
			अवरोध;
		हाल LOONGSON_CFG3:
			vcpu->arch.gprs[rd] = hostcfg;
			अवरोध;
		शेष:
			/* Don't export any other advanced features to guest */
			vcpu->arch.gprs[rd] = 0;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		kvm_err("lwc2 emulate not impl %d rs %lx @%lx\n",
			inst.loongson3_lscsr_क्रमmat.fr, vcpu->arch.gprs[rs], curr_pc);
		er = EMULATE_FAIL;
		अवरोध;
	पूर्ण

	/* Rollback PC only अगर emulation was unsuccessful */
	अगर (er == EMULATE_FAIL) अणु
		kvm_err("[%#lx]%s: unsupported lwc2 instruction 0x%08x 0x%08x\n",
			curr_pc, __func__, inst.word, inst.loongson3_lscsr_क्रमmat.fr);

		vcpu->arch.pc = curr_pc;
	पूर्ण

	वापस er;
पूर्ण
#पूर्ण_अगर

अटल क्रमागत emulation_result kvm_trap_vz_handle_gpsi(u32 cause, u32 *opc,
						     काष्ठा kvm_vcpu *vcpu)
अणु
	क्रमागत emulation_result er = EMULATE_DONE;
	काष्ठा kvm_vcpu_arch *arch = &vcpu->arch;
	जोड़ mips_inकाष्ठाion inst;
	पूर्णांक rd, rt, sel;
	पूर्णांक err;

	/*
	 *  Fetch the inकाष्ठाion.
	 */
	अगर (cause & CAUSEF_BD)
		opc += 1;
	err = kvm_get_badinstr(opc, vcpu, &inst.word);
	अगर (err)
		वापस EMULATE_FAIL;

	चयन (inst.r_क्रमmat.opcode) अणु
	हाल cop0_op:
		er = kvm_vz_gpsi_cop0(inst, opc, cause, vcpu);
		अवरोध;
#अगर_अघोषित CONFIG_CPU_MIPSR6
	हाल cache_op:
		trace_kvm_निकास(vcpu, KVM_TRACE_EXIT_CACHE);
		er = kvm_vz_gpsi_cache(inst, opc, cause, vcpu);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_LOONGSON64
	हाल lwc2_op:
		er = kvm_vz_gpsi_lwc2(inst, opc, cause, vcpu);
		अवरोध;
#पूर्ण_अगर
	हाल spec3_op:
		चयन (inst.spec3_क्रमmat.func) अणु
#अगर_घोषित CONFIG_CPU_MIPSR6
		हाल cache6_op:
			trace_kvm_निकास(vcpu, KVM_TRACE_EXIT_CACHE);
			er = kvm_vz_gpsi_cache(inst, opc, cause, vcpu);
			अवरोध;
#पूर्ण_अगर
		हाल rdhwr_op:
			अगर (inst.r_क्रमmat.rs || (inst.r_क्रमmat.re >> 3))
				जाओ unknown;

			rd = inst.r_क्रमmat.rd;
			rt = inst.r_क्रमmat.rt;
			sel = inst.r_क्रमmat.re & 0x7;

			चयन (rd) अणु
			हाल MIPS_HWR_CC:	/* Read count रेजिस्टर */
				arch->gprs[rt] =
					(दीर्घ)(पूर्णांक)kvm_mips_पढ़ो_count(vcpu);
				अवरोध;
			शेष:
				trace_kvm_hwr(vcpu, KVM_TRACE_RDHWR,
					      KVM_TRACE_HWR(rd, sel), 0);
				जाओ unknown;
			पूर्ण

			trace_kvm_hwr(vcpu, KVM_TRACE_RDHWR,
				      KVM_TRACE_HWR(rd, sel), arch->gprs[rt]);

			er = update_pc(vcpu, cause);
			अवरोध;
		शेष:
			जाओ unknown;
		पूर्ण
		अवरोध;
unknown:

	शेष:
		kvm_err("GPSI exception not supported (%p/%#x)\n",
				opc, inst.word);
		kvm_arch_vcpu_dump_regs(vcpu);
		er = EMULATE_FAIL;
		अवरोध;
	पूर्ण

	वापस er;
पूर्ण

अटल क्रमागत emulation_result kvm_trap_vz_handle_gsfc(u32 cause, u32 *opc,
						     काष्ठा kvm_vcpu *vcpu)
अणु
	क्रमागत emulation_result er = EMULATE_DONE;
	काष्ठा kvm_vcpu_arch *arch = &vcpu->arch;
	जोड़ mips_inकाष्ठाion inst;
	पूर्णांक err;

	/*
	 *  Fetch the inकाष्ठाion.
	 */
	अगर (cause & CAUSEF_BD)
		opc += 1;
	err = kvm_get_badinstr(opc, vcpu, &inst.word);
	अगर (err)
		वापस EMULATE_FAIL;

	/* complete MTC0 on behalf of guest and advance EPC */
	अगर (inst.c0r_क्रमmat.opcode == cop0_op &&
	    inst.c0r_क्रमmat.rs == mtc_op &&
	    inst.c0r_क्रमmat.z == 0) अणु
		पूर्णांक rt = inst.c0r_क्रमmat.rt;
		पूर्णांक rd = inst.c0r_क्रमmat.rd;
		पूर्णांक sel = inst.c0r_क्रमmat.sel;
		अचिन्हित पूर्णांक val = arch->gprs[rt];
		अचिन्हित पूर्णांक old_val, change;

		trace_kvm_hwr(vcpu, KVM_TRACE_MTC0, KVM_TRACE_COP0(rd, sel),
			      val);

		अगर ((rd == MIPS_CP0_STATUS) && (sel == 0)) अणु
			/* FR bit should पढ़ो as zero अगर no FPU */
			अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
				val &= ~(ST0_CU1 | ST0_FR);

			/*
			 * Also करोn't allow FR to be set if host doesn't support
			 * it.
			 */
			अगर (!(boot_cpu_data.fpu_id & MIPS_FPIR_F64))
				val &= ~ST0_FR;

			old_val = पढ़ो_gc0_status();
			change = val ^ old_val;

			अगर (change & ST0_FR) अणु
				/*
				 * FPU and Vector रेजिस्टर state is made
				 * UNPREDICTABLE by a change of FR, so करोn't
				 * even bother saving it.
				 */
				kvm_drop_fpu(vcpu);
			पूर्ण

			/*
			 * If MSA state is alपढ़ोy live, it is undefined how it
			 * पूर्णांकeracts with FR=0 FPU state, and we करोn't want to
			 * hit reserved inकाष्ठाion exceptions trying to save
			 * the MSA state later when CU=1 && FR=1, so play it
			 * safe and save it first.
			 */
			अगर (change & ST0_CU1 && !(val & ST0_FR) &&
			    vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA)
				kvm_lose_fpu(vcpu);

			ग_लिखो_gc0_status(val);
		पूर्ण अन्यथा अगर ((rd == MIPS_CP0_CAUSE) && (sel == 0)) अणु
			u32 old_cause = पढ़ो_gc0_cause();
			u32 change = old_cause ^ val;

			/* DC bit enabling/disabling समयr? */
			अगर (change & CAUSEF_DC) अणु
				अगर (val & CAUSEF_DC) अणु
					kvm_vz_lose_hसमयr(vcpu);
					kvm_mips_count_disable_cause(vcpu);
				पूर्ण अन्यथा अणु
					kvm_mips_count_enable_cause(vcpu);
				पूर्ण
			पूर्ण

			/* Only certain bits are RW to the guest */
			change &= (CAUSEF_DC | CAUSEF_IV | CAUSEF_WP |
				   CAUSEF_IP0 | CAUSEF_IP1);

			/* WP can only be cleared */
			change &= ~CAUSEF_WP | old_cause;

			ग_लिखो_gc0_cause(old_cause ^ change);
		पूर्ण अन्यथा अगर ((rd == MIPS_CP0_STATUS) && (sel == 1)) अणु /* IntCtl */
			ग_लिखो_gc0_पूर्णांकctl(val);
		पूर्ण अन्यथा अगर ((rd == MIPS_CP0_CONFIG) && (sel == 5)) अणु
			old_val = पढ़ो_gc0_config5();
			change = val ^ old_val;
			/* Handle changes in FPU/MSA modes */
			preempt_disable();

			/*
			 * Propagate FRE changes immediately अगर the FPU
			 * context is alपढ़ोy loaded.
			 */
			अगर (change & MIPS_CONF5_FRE &&
			    vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)
				change_c0_config5(MIPS_CONF5_FRE, val);

			preempt_enable();

			val = old_val ^
				(change & kvm_vz_config5_guest_wrmask(vcpu));
			ग_लिखो_gc0_config5(val);
		पूर्ण अन्यथा अणु
			kvm_err("Handle GSFC, unsupported field change @ %p: %#x\n",
			    opc, inst.word);
			er = EMULATE_FAIL;
		पूर्ण

		अगर (er != EMULATE_FAIL)
			er = update_pc(vcpu, cause);
	पूर्ण अन्यथा अणु
		kvm_err("Handle GSFC, unrecognized instruction @ %p: %#x\n",
			opc, inst.word);
		er = EMULATE_FAIL;
	पूर्ण

	वापस er;
पूर्ण

अटल क्रमागत emulation_result kvm_trap_vz_handle_ghfc(u32 cause, u32 *opc,
						     काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * Presumably this is due to MC (guest mode change), so lets trace some
	 * relevant info.
	 */
	trace_kvm_guest_mode_change(vcpu);

	वापस EMULATE_DONE;
पूर्ण

अटल क्रमागत emulation_result kvm_trap_vz_handle_hc(u32 cause, u32 *opc,
						   काष्ठा kvm_vcpu *vcpu)
अणु
	क्रमागत emulation_result er;
	जोड़ mips_inकाष्ठाion inst;
	अचिन्हित दीर्घ curr_pc;
	पूर्णांक err;

	अगर (cause & CAUSEF_BD)
		opc += 1;
	err = kvm_get_badinstr(opc, vcpu, &inst.word);
	अगर (err)
		वापस EMULATE_FAIL;

	/*
	 * Update PC and hold onto current PC in हाल there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	अगर (er == EMULATE_FAIL)
		वापस er;

	er = kvm_mips_emul_hypcall(vcpu, inst);
	अगर (er == EMULATE_FAIL)
		vcpu->arch.pc = curr_pc;

	वापस er;
पूर्ण

अटल क्रमागत emulation_result kvm_trap_vz_no_handler_guest_निकास(u32 gexccode,
							u32 cause,
							u32 *opc,
							काष्ठा kvm_vcpu *vcpu)
अणु
	u32 inst;

	/*
	 *  Fetch the inकाष्ठाion.
	 */
	अगर (cause & CAUSEF_BD)
		opc += 1;
	kvm_get_badinstr(opc, vcpu, &inst);

	kvm_err("Guest Exception Code: %d not yet handled @ PC: %p, inst: 0x%08x  Status: %#x\n",
		gexccode, opc, inst, पढ़ो_gc0_status());

	वापस EMULATE_FAIL;
पूर्ण

अटल पूर्णांक kvm_trap_vz_handle_guest_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 *opc = (u32 *) vcpu->arch.pc;
	u32 cause = vcpu->arch.host_cp0_cause;
	क्रमागत emulation_result er = EMULATE_DONE;
	u32 gexccode = (vcpu->arch.host_cp0_guestctl0 &
			MIPS_GCTL0_GEXC) >> MIPS_GCTL0_GEXC_SHIFT;
	पूर्णांक ret = RESUME_GUEST;

	trace_kvm_निकास(vcpu, KVM_TRACE_EXIT_GEXCCODE_BASE + gexccode);
	चयन (gexccode) अणु
	हाल MIPS_GCTL0_GEXC_GPSI:
		++vcpu->stat.vz_gpsi_निकासs;
		er = kvm_trap_vz_handle_gpsi(cause, opc, vcpu);
		अवरोध;
	हाल MIPS_GCTL0_GEXC_GSFC:
		++vcpu->stat.vz_gsfc_निकासs;
		er = kvm_trap_vz_handle_gsfc(cause, opc, vcpu);
		अवरोध;
	हाल MIPS_GCTL0_GEXC_HC:
		++vcpu->stat.vz_hc_निकासs;
		er = kvm_trap_vz_handle_hc(cause, opc, vcpu);
		अवरोध;
	हाल MIPS_GCTL0_GEXC_GRR:
		++vcpu->stat.vz_grr_निकासs;
		er = kvm_trap_vz_no_handler_guest_निकास(gexccode, cause, opc,
						       vcpu);
		अवरोध;
	हाल MIPS_GCTL0_GEXC_GVA:
		++vcpu->stat.vz_gva_निकासs;
		er = kvm_trap_vz_no_handler_guest_निकास(gexccode, cause, opc,
						       vcpu);
		अवरोध;
	हाल MIPS_GCTL0_GEXC_GHFC:
		++vcpu->stat.vz_ghfc_निकासs;
		er = kvm_trap_vz_handle_ghfc(cause, opc, vcpu);
		अवरोध;
	हाल MIPS_GCTL0_GEXC_GPA:
		++vcpu->stat.vz_gpa_निकासs;
		er = kvm_trap_vz_no_handler_guest_निकास(gexccode, cause, opc,
						       vcpu);
		अवरोध;
	शेष:
		++vcpu->stat.vz_resvd_निकासs;
		er = kvm_trap_vz_no_handler_guest_निकास(gexccode, cause, opc,
						       vcpu);
		अवरोध;

	पूर्ण

	अगर (er == EMULATE_DONE) अणु
		ret = RESUME_GUEST;
	पूर्ण अन्यथा अगर (er == EMULATE_HYPERCALL) अणु
		ret = kvm_mips_handle_hypcall(vcpu);
	पूर्ण अन्यथा अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * kvm_trap_vz_handle_cop_unusuable() - Guest used unusable coprocessor.
 * @vcpu:	Virtual CPU context.
 *
 * Handle when the guest attempts to use a coprocessor which hasn't been allowed
 * by the root context.
 */
अटल पूर्णांक kvm_trap_vz_handle_cop_unusable(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 cause = vcpu->arch.host_cp0_cause;
	क्रमागत emulation_result er = EMULATE_FAIL;
	पूर्णांक ret = RESUME_GUEST;

	अगर (((cause & CAUSEF_CE) >> CAUSEB_CE) == 1) अणु
		/*
		 * If guest FPU not present, the FPU operation should have been
		 * treated as a reserved inकाष्ठाion!
		 * If FPU alपढ़ोy in use, we shouldn't get this at all.
		 */
		अगर (WARN_ON(!kvm_mips_guest_has_fpu(&vcpu->arch) ||
			    vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)) अणु
			preempt_enable();
			वापस EMULATE_FAIL;
		पूर्ण

		kvm_own_fpu(vcpu);
		er = EMULATE_DONE;
	पूर्ण
	/* other coprocessors not handled */

	चयन (er) अणु
	हाल EMULATE_DONE:
		ret = RESUME_GUEST;
		अवरोध;

	हाल EMULATE_FAIL:
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	वापस ret;
पूर्ण

/**
 * kvm_trap_vz_handle_msa_disabled() - Guest used MSA जबतक disabled in root.
 * @vcpu:	Virtual CPU context.
 *
 * Handle when the guest attempts to use MSA when it is disabled in the root
 * context.
 */
अटल पूर्णांक kvm_trap_vz_handle_msa_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * If MSA not present or not exposed to guest or FR=0, the MSA operation
	 * should have been treated as a reserved inकाष्ठाion!
	 * Same अगर CU1=1, FR=0.
	 * If MSA alपढ़ोy in use, we shouldn't get this at all.
	 */
	अगर (!kvm_mips_guest_has_msa(&vcpu->arch) ||
	    (पढ़ो_gc0_status() & (ST0_CU1 | ST0_FR)) == ST0_CU1 ||
	    !(पढ़ो_gc0_config5() & MIPS_CONF5_MSAEN) ||
	    vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		वापस RESUME_HOST;
	पूर्ण

	kvm_own_msa(vcpu);

	वापस RESUME_GUEST;
पूर्ण

अटल पूर्णांक kvm_trap_vz_handle_tlb_ld_miss(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	u32 *opc = (u32 *) vcpu->arch.pc;
	u32 cause = vcpu->arch.host_cp0_cause;
	uदीर्घ badvaddr = vcpu->arch.host_cp0_badvaddr;
	जोड़ mips_inकाष्ठाion inst;
	क्रमागत emulation_result er = EMULATE_DONE;
	पूर्णांक err, ret = RESUME_GUEST;

	अगर (kvm_mips_handle_vz_root_tlb_fault(badvaddr, vcpu, false)) अणु
		/* A code fetch fault करोesn't count as an MMIO */
		अगर (kvm_is_अगरetch_fault(&vcpu->arch)) अणु
			run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
			वापस RESUME_HOST;
		पूर्ण

		/* Fetch the inकाष्ठाion */
		अगर (cause & CAUSEF_BD)
			opc += 1;
		err = kvm_get_badinstr(opc, vcpu, &inst.word);
		अगर (err) अणु
			run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
			वापस RESUME_HOST;
		पूर्ण

		/* Treat as MMIO */
		er = kvm_mips_emulate_load(inst, cause, vcpu);
		अगर (er == EMULATE_FAIL) अणु
			kvm_err("Guest Emulate Load from MMIO space failed: PC: %p, BadVaddr: %#lx\n",
				opc, badvaddr);
			run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		पूर्ण
	पूर्ण

	अगर (er == EMULATE_DONE) अणु
		ret = RESUME_GUEST;
	पूर्ण अन्यथा अगर (er == EMULATE_DO_MMIO) अणु
		run->निकास_reason = KVM_EXIT_MMIO;
		ret = RESUME_HOST;
	पूर्ण अन्यथा अणु
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_trap_vz_handle_tlb_st_miss(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	u32 *opc = (u32 *) vcpu->arch.pc;
	u32 cause = vcpu->arch.host_cp0_cause;
	uदीर्घ badvaddr = vcpu->arch.host_cp0_badvaddr;
	जोड़ mips_inकाष्ठाion inst;
	क्रमागत emulation_result er = EMULATE_DONE;
	पूर्णांक err;
	पूर्णांक ret = RESUME_GUEST;

	/* Just try the access again अगर we couldn't करो the translation */
	अगर (kvm_vz_badvaddr_to_gpa(vcpu, badvaddr, &badvaddr))
		वापस RESUME_GUEST;
	vcpu->arch.host_cp0_badvaddr = badvaddr;

	अगर (kvm_mips_handle_vz_root_tlb_fault(badvaddr, vcpu, true)) अणु
		/* Fetch the inकाष्ठाion */
		अगर (cause & CAUSEF_BD)
			opc += 1;
		err = kvm_get_badinstr(opc, vcpu, &inst.word);
		अगर (err) अणु
			run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
			वापस RESUME_HOST;
		पूर्ण

		/* Treat as MMIO */
		er = kvm_mips_emulate_store(inst, cause, vcpu);
		अगर (er == EMULATE_FAIL) अणु
			kvm_err("Guest Emulate Store to MMIO space failed: PC: %p, BadVaddr: %#lx\n",
				opc, badvaddr);
			run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		पूर्ण
	पूर्ण

	अगर (er == EMULATE_DONE) अणु
		ret = RESUME_GUEST;
	पूर्ण अन्यथा अगर (er == EMULATE_DO_MMIO) अणु
		run->निकास_reason = KVM_EXIT_MMIO;
		ret = RESUME_HOST;
	पूर्ण अन्यथा अणु
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
	पूर्ण
	वापस ret;
पूर्ण

अटल u64 kvm_vz_get_one_regs[] = अणु
	KVM_REG_MIPS_CP0_INDEX,
	KVM_REG_MIPS_CP0_ENTRYLO0,
	KVM_REG_MIPS_CP0_ENTRYLO1,
	KVM_REG_MIPS_CP0_CONTEXT,
	KVM_REG_MIPS_CP0_PAGEMASK,
	KVM_REG_MIPS_CP0_PAGEGRAIN,
	KVM_REG_MIPS_CP0_WIRED,
	KVM_REG_MIPS_CP0_HWRENA,
	KVM_REG_MIPS_CP0_BADVADDR,
	KVM_REG_MIPS_CP0_COUNT,
	KVM_REG_MIPS_CP0_ENTRYHI,
	KVM_REG_MIPS_CP0_COMPARE,
	KVM_REG_MIPS_CP0_STATUS,
	KVM_REG_MIPS_CP0_INTCTL,
	KVM_REG_MIPS_CP0_CAUSE,
	KVM_REG_MIPS_CP0_EPC,
	KVM_REG_MIPS_CP0_PRID,
	KVM_REG_MIPS_CP0_EBASE,
	KVM_REG_MIPS_CP0_CONFIG,
	KVM_REG_MIPS_CP0_CONFIG1,
	KVM_REG_MIPS_CP0_CONFIG2,
	KVM_REG_MIPS_CP0_CONFIG3,
	KVM_REG_MIPS_CP0_CONFIG4,
	KVM_REG_MIPS_CP0_CONFIG5,
	KVM_REG_MIPS_CP0_CONFIG6,
#अगर_घोषित CONFIG_64BIT
	KVM_REG_MIPS_CP0_XCONTEXT,
#पूर्ण_अगर
	KVM_REG_MIPS_CP0_ERROREPC,

	KVM_REG_MIPS_COUNT_CTL,
	KVM_REG_MIPS_COUNT_RESUME,
	KVM_REG_MIPS_COUNT_HZ,
पूर्ण;

अटल u64 kvm_vz_get_one_regs_contextconfig[] = अणु
	KVM_REG_MIPS_CP0_CONTEXTCONFIG,
#अगर_घोषित CONFIG_64BIT
	KVM_REG_MIPS_CP0_XCONTEXTCONFIG,
#पूर्ण_अगर
पूर्ण;

अटल u64 kvm_vz_get_one_regs_segments[] = अणु
	KVM_REG_MIPS_CP0_SEGCTL0,
	KVM_REG_MIPS_CP0_SEGCTL1,
	KVM_REG_MIPS_CP0_SEGCTL2,
पूर्ण;

अटल u64 kvm_vz_get_one_regs_htw[] = अणु
	KVM_REG_MIPS_CP0_PWBASE,
	KVM_REG_MIPS_CP0_PWFIELD,
	KVM_REG_MIPS_CP0_PWSIZE,
	KVM_REG_MIPS_CP0_PWCTL,
पूर्ण;

अटल u64 kvm_vz_get_one_regs_kscratch[] = अणु
	KVM_REG_MIPS_CP0_KSCRATCH1,
	KVM_REG_MIPS_CP0_KSCRATCH2,
	KVM_REG_MIPS_CP0_KSCRATCH3,
	KVM_REG_MIPS_CP0_KSCRATCH4,
	KVM_REG_MIPS_CP0_KSCRATCH5,
	KVM_REG_MIPS_CP0_KSCRATCH6,
पूर्ण;

अटल अचिन्हित दीर्घ kvm_vz_num_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ ret;

	ret = ARRAY_SIZE(kvm_vz_get_one_regs);
	अगर (cpu_guest_has_userlocal)
		++ret;
	अगर (cpu_guest_has_badinstr)
		++ret;
	अगर (cpu_guest_has_badinstrp)
		++ret;
	अगर (cpu_guest_has_contextconfig)
		ret += ARRAY_SIZE(kvm_vz_get_one_regs_contextconfig);
	अगर (cpu_guest_has_segments)
		ret += ARRAY_SIZE(kvm_vz_get_one_regs_segments);
	अगर (cpu_guest_has_htw || cpu_guest_has_ldpte)
		ret += ARRAY_SIZE(kvm_vz_get_one_regs_htw);
	अगर (cpu_guest_has_maar && !cpu_guest_has_dyn_maar)
		ret += 1 + ARRAY_SIZE(vcpu->arch.maar);
	ret += __arch_hweight8(cpu_data[0].guest.kscratch_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_vz_copy_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *indices)
अणु
	u64 index;
	अचिन्हित पूर्णांक i;

	अगर (copy_to_user(indices, kvm_vz_get_one_regs,
			 माप(kvm_vz_get_one_regs)))
		वापस -EFAULT;
	indices += ARRAY_SIZE(kvm_vz_get_one_regs);

	अगर (cpu_guest_has_userlocal) अणु
		index = KVM_REG_MIPS_CP0_USERLOCAL;
		अगर (copy_to_user(indices, &index, माप(index)))
			वापस -EFAULT;
		++indices;
	पूर्ण
	अगर (cpu_guest_has_badinstr) अणु
		index = KVM_REG_MIPS_CP0_BADINSTR;
		अगर (copy_to_user(indices, &index, माप(index)))
			वापस -EFAULT;
		++indices;
	पूर्ण
	अगर (cpu_guest_has_badinstrp) अणु
		index = KVM_REG_MIPS_CP0_BADINSTRP;
		अगर (copy_to_user(indices, &index, माप(index)))
			वापस -EFAULT;
		++indices;
	पूर्ण
	अगर (cpu_guest_has_contextconfig) अणु
		अगर (copy_to_user(indices, kvm_vz_get_one_regs_contextconfig,
				 माप(kvm_vz_get_one_regs_contextconfig)))
			वापस -EFAULT;
		indices += ARRAY_SIZE(kvm_vz_get_one_regs_contextconfig);
	पूर्ण
	अगर (cpu_guest_has_segments) अणु
		अगर (copy_to_user(indices, kvm_vz_get_one_regs_segments,
				 माप(kvm_vz_get_one_regs_segments)))
			वापस -EFAULT;
		indices += ARRAY_SIZE(kvm_vz_get_one_regs_segments);
	पूर्ण
	अगर (cpu_guest_has_htw || cpu_guest_has_ldpte) अणु
		अगर (copy_to_user(indices, kvm_vz_get_one_regs_htw,
				 माप(kvm_vz_get_one_regs_htw)))
			वापस -EFAULT;
		indices += ARRAY_SIZE(kvm_vz_get_one_regs_htw);
	पूर्ण
	अगर (cpu_guest_has_maar && !cpu_guest_has_dyn_maar) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vcpu->arch.maar); ++i) अणु
			index = KVM_REG_MIPS_CP0_MAAR(i);
			अगर (copy_to_user(indices, &index, माप(index)))
				वापस -EFAULT;
			++indices;
		पूर्ण

		index = KVM_REG_MIPS_CP0_MAARI;
		अगर (copy_to_user(indices, &index, माप(index)))
			वापस -EFAULT;
		++indices;
	पूर्ण
	क्रम (i = 0; i < 6; ++i) अणु
		अगर (!cpu_guest_has_kscr(i + 2))
			जारी;

		अगर (copy_to_user(indices, &kvm_vz_get_one_regs_kscratch[i],
				 माप(kvm_vz_get_one_regs_kscratch[i])))
			वापस -EFAULT;
		++indices;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत s64 entrylo_kvm_to_user(अचिन्हित दीर्घ v)
अणु
	s64 mask, ret = v;

	अगर (BITS_PER_LONG == 32) अणु
		/*
		 * KVM API exposes 64-bit version of the रेजिस्टर, so move the
		 * RI/XI bits up पूर्णांकo place.
		 */
		mask = MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI;
		ret &= ~mask;
		ret |= ((s64)v & mask) << 32;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ entrylo_user_to_kvm(s64 v)
अणु
	अचिन्हित दीर्घ mask, ret = v;

	अगर (BITS_PER_LONG == 32) अणु
		/*
		 * KVM API exposes 64-bit versiono of the रेजिस्टर, so move the
		 * RI/XI bits करोwn पूर्णांकo place.
		 */
		mask = MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI;
		ret &= ~mask;
		ret |= (v >> 32) & mask;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_vz_get_one_reg(काष्ठा kvm_vcpu *vcpu,
			      स्थिर काष्ठा kvm_one_reg *reg,
			      s64 *v)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	अचिन्हित पूर्णांक idx;

	चयन (reg->id) अणु
	हाल KVM_REG_MIPS_CP0_INDEX:
		*v = (दीर्घ)पढ़ो_gc0_index();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_ENTRYLO0:
		*v = entrylo_kvm_to_user(पढ़ो_gc0_entrylo0());
		अवरोध;
	हाल KVM_REG_MIPS_CP0_ENTRYLO1:
		*v = entrylo_kvm_to_user(पढ़ो_gc0_entrylo1());
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONTEXT:
		*v = (दीर्घ)पढ़ो_gc0_context();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONTEXTCONFIG:
		अगर (!cpu_guest_has_contextconfig)
			वापस -EINVAL;
		*v = पढ़ो_gc0_contextconfig();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_USERLOCAL:
		अगर (!cpu_guest_has_userlocal)
			वापस -EINVAL;
		*v = पढ़ो_gc0_userlocal();
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल KVM_REG_MIPS_CP0_XCONTEXTCONFIG:
		अगर (!cpu_guest_has_contextconfig)
			वापस -EINVAL;
		*v = पढ़ो_gc0_xcontextconfig();
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_MIPS_CP0_PAGEMASK:
		*v = (दीर्घ)पढ़ो_gc0_pagemask();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PAGEGRAIN:
		*v = (दीर्घ)पढ़ो_gc0_pagegrain();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_SEGCTL0:
		अगर (!cpu_guest_has_segments)
			वापस -EINVAL;
		*v = पढ़ो_gc0_segctl0();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_SEGCTL1:
		अगर (!cpu_guest_has_segments)
			वापस -EINVAL;
		*v = पढ़ो_gc0_segctl1();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_SEGCTL2:
		अगर (!cpu_guest_has_segments)
			वापस -EINVAL;
		*v = पढ़ो_gc0_segctl2();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWBASE:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		*v = पढ़ो_gc0_pwbase();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWFIELD:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		*v = पढ़ो_gc0_pwfield();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWSIZE:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		*v = पढ़ो_gc0_pwsize();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_WIRED:
		*v = (दीर्घ)पढ़ो_gc0_wired();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWCTL:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		*v = पढ़ो_gc0_pwctl();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_HWRENA:
		*v = (दीर्घ)पढ़ो_gc0_hwrena();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_BADVADDR:
		*v = (दीर्घ)पढ़ो_gc0_badvaddr();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_BADINSTR:
		अगर (!cpu_guest_has_badinstr)
			वापस -EINVAL;
		*v = पढ़ो_gc0_badinstr();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_BADINSTRP:
		अगर (!cpu_guest_has_badinstrp)
			वापस -EINVAL;
		*v = पढ़ो_gc0_badinstrp();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_COUNT:
		*v = kvm_mips_पढ़ो_count(vcpu);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_ENTRYHI:
		*v = (दीर्घ)पढ़ो_gc0_entryhi();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_COMPARE:
		*v = (दीर्घ)पढ़ो_gc0_compare();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_STATUS:
		*v = (दीर्घ)पढ़ो_gc0_status();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_INTCTL:
		*v = पढ़ो_gc0_पूर्णांकctl();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CAUSE:
		*v = (दीर्घ)पढ़ो_gc0_cause();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_EPC:
		*v = (दीर्घ)पढ़ो_gc0_epc();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PRID:
		चयन (boot_cpu_type()) अणु
		हाल CPU_CAVIUM_OCTEON3:
			/* Octeon III has a पढ़ो-only guest.PRid */
			*v = पढ़ो_gc0_prid();
			अवरोध;
		शेष:
			*v = (दीर्घ)kvm_पढ़ो_c0_guest_prid(cop0);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_EBASE:
		*v = kvm_vz_पढ़ो_gc0_ebase();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG:
		*v = पढ़ो_gc0_config();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG1:
		अगर (!cpu_guest_has_conf1)
			वापस -EINVAL;
		*v = पढ़ो_gc0_config1();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG2:
		अगर (!cpu_guest_has_conf2)
			वापस -EINVAL;
		*v = पढ़ो_gc0_config2();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG3:
		अगर (!cpu_guest_has_conf3)
			वापस -EINVAL;
		*v = पढ़ो_gc0_config3();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG4:
		अगर (!cpu_guest_has_conf4)
			वापस -EINVAL;
		*v = पढ़ो_gc0_config4();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG5:
		अगर (!cpu_guest_has_conf5)
			वापस -EINVAL;
		*v = पढ़ो_gc0_config5();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG6:
		*v = kvm_पढ़ो_sw_gc0_config6(cop0);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_MAAR(0) ... KVM_REG_MIPS_CP0_MAAR(0x3f):
		अगर (!cpu_guest_has_maar || cpu_guest_has_dyn_maar)
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_CP0_MAAR(0);
		अगर (idx >= ARRAY_SIZE(vcpu->arch.maar))
			वापस -EINVAL;
		*v = vcpu->arch.maar[idx];
		अवरोध;
	हाल KVM_REG_MIPS_CP0_MAARI:
		अगर (!cpu_guest_has_maar || cpu_guest_has_dyn_maar)
			वापस -EINVAL;
		*v = kvm_पढ़ो_sw_gc0_maari(vcpu->arch.cop0);
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल KVM_REG_MIPS_CP0_XCONTEXT:
		*v = पढ़ो_gc0_xcontext();
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_MIPS_CP0_ERROREPC:
		*v = (दीर्घ)पढ़ो_gc0_errorepc();
		अवरोध;
	हाल KVM_REG_MIPS_CP0_KSCRATCH1 ... KVM_REG_MIPS_CP0_KSCRATCH6:
		idx = reg->id - KVM_REG_MIPS_CP0_KSCRATCH1 + 2;
		अगर (!cpu_guest_has_kscr(idx))
			वापस -EINVAL;
		चयन (idx) अणु
		हाल 2:
			*v = (दीर्घ)पढ़ो_gc0_kscratch1();
			अवरोध;
		हाल 3:
			*v = (दीर्घ)पढ़ो_gc0_kscratch2();
			अवरोध;
		हाल 4:
			*v = (दीर्घ)पढ़ो_gc0_kscratch3();
			अवरोध;
		हाल 5:
			*v = (दीर्घ)पढ़ो_gc0_kscratch4();
			अवरोध;
		हाल 6:
			*v = (दीर्घ)पढ़ो_gc0_kscratch5();
			अवरोध;
		हाल 7:
			*v = (दीर्घ)पढ़ो_gc0_kscratch6();
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_COUNT_CTL:
		*v = vcpu->arch.count_ctl;
		अवरोध;
	हाल KVM_REG_MIPS_COUNT_RESUME:
		*v = kसमय_प्रकारo_ns(vcpu->arch.count_resume);
		अवरोध;
	हाल KVM_REG_MIPS_COUNT_HZ:
		*v = vcpu->arch.count_hz;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vz_set_one_reg(काष्ठा kvm_vcpu *vcpu,
			      स्थिर काष्ठा kvm_one_reg *reg,
			      s64 v)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cur, change;

	चयन (reg->id) अणु
	हाल KVM_REG_MIPS_CP0_INDEX:
		ग_लिखो_gc0_index(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_ENTRYLO0:
		ग_लिखो_gc0_entrylo0(entrylo_user_to_kvm(v));
		अवरोध;
	हाल KVM_REG_MIPS_CP0_ENTRYLO1:
		ग_लिखो_gc0_entrylo1(entrylo_user_to_kvm(v));
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONTEXT:
		ग_लिखो_gc0_context(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONTEXTCONFIG:
		अगर (!cpu_guest_has_contextconfig)
			वापस -EINVAL;
		ग_लिखो_gc0_contextconfig(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_USERLOCAL:
		अगर (!cpu_guest_has_userlocal)
			वापस -EINVAL;
		ग_लिखो_gc0_userlocal(v);
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल KVM_REG_MIPS_CP0_XCONTEXTCONFIG:
		अगर (!cpu_guest_has_contextconfig)
			वापस -EINVAL;
		ग_लिखो_gc0_xcontextconfig(v);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_MIPS_CP0_PAGEMASK:
		ग_लिखो_gc0_pagemask(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PAGEGRAIN:
		ग_लिखो_gc0_pagegrain(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_SEGCTL0:
		अगर (!cpu_guest_has_segments)
			वापस -EINVAL;
		ग_लिखो_gc0_segctl0(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_SEGCTL1:
		अगर (!cpu_guest_has_segments)
			वापस -EINVAL;
		ग_लिखो_gc0_segctl1(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_SEGCTL2:
		अगर (!cpu_guest_has_segments)
			वापस -EINVAL;
		ग_लिखो_gc0_segctl2(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWBASE:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		ग_लिखो_gc0_pwbase(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWFIELD:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		ग_लिखो_gc0_pwfield(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWSIZE:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		ग_लिखो_gc0_pwsize(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_WIRED:
		change_gc0_wired(MIPSR6_WIRED_WIRED, v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PWCTL:
		अगर (!cpu_guest_has_htw && !cpu_guest_has_ldpte)
			वापस -EINVAL;
		ग_लिखो_gc0_pwctl(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_HWRENA:
		ग_लिखो_gc0_hwrena(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_BADVADDR:
		ग_लिखो_gc0_badvaddr(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_BADINSTR:
		अगर (!cpu_guest_has_badinstr)
			वापस -EINVAL;
		ग_लिखो_gc0_badinstr(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_BADINSTRP:
		अगर (!cpu_guest_has_badinstrp)
			वापस -EINVAL;
		ग_लिखो_gc0_badinstrp(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_COUNT:
		kvm_mips_ग_लिखो_count(vcpu, v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_ENTRYHI:
		ग_लिखो_gc0_entryhi(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_COMPARE:
		kvm_mips_ग_लिखो_compare(vcpu, v, false);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_STATUS:
		ग_लिखो_gc0_status(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_INTCTL:
		ग_लिखो_gc0_पूर्णांकctl(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CAUSE:
		/*
		 * If the समयr is stopped or started (DC bit) it must look
		 * atomic with changes to the समयr पूर्णांकerrupt pending bit (TI).
		 * A समयr पूर्णांकerrupt should not happen in between.
		 */
		अगर ((पढ़ो_gc0_cause() ^ v) & CAUSEF_DC) अणु
			अगर (v & CAUSEF_DC) अणु
				/* disable समयr first */
				kvm_mips_count_disable_cause(vcpu);
				change_gc0_cause((u32)~CAUSEF_DC, v);
			पूर्ण अन्यथा अणु
				/* enable समयr last */
				change_gc0_cause((u32)~CAUSEF_DC, v);
				kvm_mips_count_enable_cause(vcpu);
			पूर्ण
		पूर्ण अन्यथा अणु
			ग_लिखो_gc0_cause(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_EPC:
		ग_लिखो_gc0_epc(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_PRID:
		चयन (boot_cpu_type()) अणु
		हाल CPU_CAVIUM_OCTEON3:
			/* Octeon III has a guest.PRid, but its पढ़ो-only */
			अवरोध;
		शेष:
			kvm_ग_लिखो_c0_guest_prid(cop0, v);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_EBASE:
		kvm_vz_ग_लिखो_gc0_ebase(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG:
		cur = पढ़ो_gc0_config();
		change = (cur ^ v) & kvm_vz_config_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			ग_लिखो_gc0_config(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG1:
		अगर (!cpu_guest_has_conf1)
			अवरोध;
		cur = पढ़ो_gc0_config1();
		change = (cur ^ v) & kvm_vz_config1_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			ग_लिखो_gc0_config1(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG2:
		अगर (!cpu_guest_has_conf2)
			अवरोध;
		cur = पढ़ो_gc0_config2();
		change = (cur ^ v) & kvm_vz_config2_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			ग_लिखो_gc0_config2(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG3:
		अगर (!cpu_guest_has_conf3)
			अवरोध;
		cur = पढ़ो_gc0_config3();
		change = (cur ^ v) & kvm_vz_config3_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			ग_लिखो_gc0_config3(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG4:
		अगर (!cpu_guest_has_conf4)
			अवरोध;
		cur = पढ़ो_gc0_config4();
		change = (cur ^ v) & kvm_vz_config4_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			ग_लिखो_gc0_config4(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG5:
		अगर (!cpu_guest_has_conf5)
			अवरोध;
		cur = पढ़ो_gc0_config5();
		change = (cur ^ v) & kvm_vz_config5_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			ग_लिखो_gc0_config5(v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_CONFIG6:
		cur = kvm_पढ़ो_sw_gc0_config6(cop0);
		change = (cur ^ v) & kvm_vz_config6_user_wrmask(vcpu);
		अगर (change) अणु
			v = cur ^ change;
			kvm_ग_लिखो_sw_gc0_config6(cop0, (पूर्णांक)v);
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_CP0_MAAR(0) ... KVM_REG_MIPS_CP0_MAAR(0x3f):
		अगर (!cpu_guest_has_maar || cpu_guest_has_dyn_maar)
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_CP0_MAAR(0);
		अगर (idx >= ARRAY_SIZE(vcpu->arch.maar))
			वापस -EINVAL;
		vcpu->arch.maar[idx] = mips_process_maar(dmtc_op, v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_MAARI:
		अगर (!cpu_guest_has_maar || cpu_guest_has_dyn_maar)
			वापस -EINVAL;
		kvm_ग_लिखो_maari(vcpu, v);
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल KVM_REG_MIPS_CP0_XCONTEXT:
		ग_लिखो_gc0_xcontext(v);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_MIPS_CP0_ERROREPC:
		ग_लिखो_gc0_errorepc(v);
		अवरोध;
	हाल KVM_REG_MIPS_CP0_KSCRATCH1 ... KVM_REG_MIPS_CP0_KSCRATCH6:
		idx = reg->id - KVM_REG_MIPS_CP0_KSCRATCH1 + 2;
		अगर (!cpu_guest_has_kscr(idx))
			वापस -EINVAL;
		चयन (idx) अणु
		हाल 2:
			ग_लिखो_gc0_kscratch1(v);
			अवरोध;
		हाल 3:
			ग_लिखो_gc0_kscratch2(v);
			अवरोध;
		हाल 4:
			ग_लिखो_gc0_kscratch3(v);
			अवरोध;
		हाल 5:
			ग_लिखो_gc0_kscratch4(v);
			अवरोध;
		हाल 6:
			ग_लिखो_gc0_kscratch5(v);
			अवरोध;
		हाल 7:
			ग_लिखो_gc0_kscratch6(v);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_REG_MIPS_COUNT_CTL:
		ret = kvm_mips_set_count_ctl(vcpu, v);
		अवरोध;
	हाल KVM_REG_MIPS_COUNT_RESUME:
		ret = kvm_mips_set_count_resume(vcpu, v);
		अवरोध;
	हाल KVM_REG_MIPS_COUNT_HZ:
		ret = kvm_mips_set_count_hz(vcpu, v);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा guestid_cache(cpu)	(cpu_data[cpu].guestid_cache)
अटल व्योम kvm_vz_get_new_guestid(अचिन्हित दीर्घ cpu, काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ guestid = guestid_cache(cpu);

	अगर (!(++guestid & GUESTID_MASK)) अणु
		अगर (cpu_has_vtag_icache)
			flush_icache_all();

		अगर (!guestid)		/* fix version अगर needed */
			guestid = GUESTID_FIRST_VERSION;

		++guestid;		/* guestid 0 reserved क्रम root */

		/* start new guestid cycle */
		kvm_vz_local_flush_roottlb_all_guests();
		kvm_vz_local_flush_guesttlb_all();
	पूर्ण

	guestid_cache(cpu) = guestid;
पूर्ण

/* Returns 1 अगर the guest TLB may be clobbered */
अटल पूर्णांक kvm_vz_check_requests(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!kvm_request_pending(vcpu))
		वापस 0;

	अगर (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu)) अणु
		अगर (cpu_has_guestid) अणु
			/* Drop all GuestIDs क्रम this VCPU */
			क्रम_each_possible_cpu(i)
				vcpu->arch.vzguestid[i] = 0;
			/* This will clobber guest TLB contents too */
			ret = 1;
		पूर्ण
		/*
		 * For Root ASID Dealias (RAD) we करोn't करो anything here, but we
		 * still need the request to ensure we recheck asid_flush_mask.
		 * We can still वापस 0 as only the root TLB will be affected
		 * by a root ASID flush.
		 */
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम kvm_vz_vcpu_save_wired(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक wired = पढ़ो_gc0_wired();
	काष्ठा kvm_mips_tlb *tlbs;
	पूर्णांक i;

	/* Expand the wired TLB array अगर necessary */
	wired &= MIPSR6_WIRED_WIRED;
	अगर (wired > vcpu->arch.wired_tlb_limit) अणु
		tlbs = kपुनः_स्मृति(vcpu->arch.wired_tlb, wired *
				माप(*vcpu->arch.wired_tlb), GFP_ATOMIC);
		अगर (WARN_ON(!tlbs)) अणु
			/* Save whatever we can */
			wired = vcpu->arch.wired_tlb_limit;
		पूर्ण अन्यथा अणु
			vcpu->arch.wired_tlb = tlbs;
			vcpu->arch.wired_tlb_limit = wired;
		पूर्ण
	पूर्ण

	अगर (wired)
		/* Save wired entries from the guest TLB */
		kvm_vz_save_guesttlb(vcpu->arch.wired_tlb, 0, wired);
	/* Invalidate any dropped entries since last समय */
	क्रम (i = wired; i < vcpu->arch.wired_tlb_used; ++i) अणु
		vcpu->arch.wired_tlb[i].tlb_hi = UNIQUE_GUEST_ENTRYHI(i);
		vcpu->arch.wired_tlb[i].tlb_lo[0] = 0;
		vcpu->arch.wired_tlb[i].tlb_lo[1] = 0;
		vcpu->arch.wired_tlb[i].tlb_mask = 0;
	पूर्ण
	vcpu->arch.wired_tlb_used = wired;
पूर्ण

अटल व्योम kvm_vz_vcpu_load_wired(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Load wired entries पूर्णांकo the guest TLB */
	अगर (vcpu->arch.wired_tlb)
		kvm_vz_load_guesttlb(vcpu->arch.wired_tlb, 0,
				     vcpu->arch.wired_tlb_used);
पूर्ण

अटल व्योम kvm_vz_vcpu_load_tlb(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा mm_काष्ठा *gpa_mm = &kvm->arch.gpa_mm;
	bool migrated;

	/*
	 * Are we entering guest context on a dअगरferent CPU to last समय?
	 * If so, the VCPU's guest TLB state on this CPU may be stale.
	 */
	migrated = (vcpu->arch.last_exec_cpu != cpu);
	vcpu->arch.last_exec_cpu = cpu;

	/*
	 * A vcpu's GuestID is set in GuestCtl1.ID when the vcpu is loaded and
	 * reमुख्यs set until another vcpu is loaded in.  As a rule GuestRID
	 * reमुख्यs zeroed when in root context unless the kernel is busy
	 * manipulating guest tlb entries.
	 */
	अगर (cpu_has_guestid) अणु
		/*
		 * Check अगर our GuestID is of an older version and thus invalid.
		 *
		 * We also discard the stored GuestID अगर we've executed on
		 * another CPU, as the guest mappings may have changed without
		 * hypervisor knowledge.
		 */
		अगर (migrated ||
		    (vcpu->arch.vzguestid[cpu] ^ guestid_cache(cpu)) &
					GUESTID_VERSION_MASK) अणु
			kvm_vz_get_new_guestid(cpu, vcpu);
			vcpu->arch.vzguestid[cpu] = guestid_cache(cpu);
			trace_kvm_guestid_change(vcpu,
						 vcpu->arch.vzguestid[cpu]);
		पूर्ण

		/* Restore GuestID */
		change_c0_guestctl1(GUESTID_MASK, vcpu->arch.vzguestid[cpu]);
	पूर्ण अन्यथा अणु
		/*
		 * The Guest TLB only stores a single guest's TLB state, so
		 * flush it अगर another VCPU has executed on this CPU.
		 *
		 * We also flush अगर we've executed on another CPU, as the guest
		 * mappings may have changed without hypervisor knowledge.
		 */
		अगर (migrated || last_exec_vcpu[cpu] != vcpu)
			kvm_vz_local_flush_guesttlb_all();
		last_exec_vcpu[cpu] = vcpu;

		/*
		 * Root ASID dealiases guest GPA mappings in the root TLB.
		 * Allocate new root ASID अगर needed.
		 */
		अगर (cpumask_test_and_clear_cpu(cpu, &kvm->arch.asid_flush_mask))
			get_new_mmu_context(gpa_mm);
		अन्यथा
			check_mmu_context(gpa_mm);
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_vz_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	bool migrated, all;

	/*
	 * Have we migrated to a dअगरferent CPU?
	 * If so, any old guest TLB state may be stale.
	 */
	migrated = (vcpu->arch.last_sched_cpu != cpu);

	/*
	 * Was this the last VCPU to run on this CPU?
	 * If not, any old guest state from this VCPU will have been clobbered.
	 */
	all = migrated || (last_vcpu[cpu] != vcpu);
	last_vcpu[cpu] = vcpu;

	/*
	 * Restore CP0_Wired unconditionally as we clear it after use, and
	 * restore wired guest TLB entries (जबतक in guest context).
	 */
	kvm_restore_gc0_wired(cop0);
	अगर (current->flags & PF_VCPU) अणु
		tlbw_use_hazard();
		kvm_vz_vcpu_load_tlb(vcpu, cpu);
		kvm_vz_vcpu_load_wired(vcpu);
	पूर्ण

	/*
	 * Restore समयr state regardless, as e.g. Cause.TI can change over समय
	 * अगर left unमुख्यtained.
	 */
	kvm_vz_restore_समयr(vcpu);

	/* Set MC bit अगर we want to trace guest mode changes */
	अगर (kvm_trace_guest_mode_change)
		set_c0_guestctl0(MIPS_GCTL0_MC);
	अन्यथा
		clear_c0_guestctl0(MIPS_GCTL0_MC);

	/* Don't bother restoring रेजिस्टरs multiple बार unless necessary */
	अगर (!all)
		वापस 0;

	/*
	 * Restore config रेजिस्टरs first, as some implementations restrict
	 * ग_लिखोs to other रेजिस्टरs when the corresponding feature bits aren't
	 * set. For example Status.CU1 cannot be set unless Config1.FP is set.
	 */
	kvm_restore_gc0_config(cop0);
	अगर (cpu_guest_has_conf1)
		kvm_restore_gc0_config1(cop0);
	अगर (cpu_guest_has_conf2)
		kvm_restore_gc0_config2(cop0);
	अगर (cpu_guest_has_conf3)
		kvm_restore_gc0_config3(cop0);
	अगर (cpu_guest_has_conf4)
		kvm_restore_gc0_config4(cop0);
	अगर (cpu_guest_has_conf5)
		kvm_restore_gc0_config5(cop0);
	अगर (cpu_guest_has_conf6)
		kvm_restore_gc0_config6(cop0);
	अगर (cpu_guest_has_conf7)
		kvm_restore_gc0_config7(cop0);

	kvm_restore_gc0_index(cop0);
	kvm_restore_gc0_entrylo0(cop0);
	kvm_restore_gc0_entrylo1(cop0);
	kvm_restore_gc0_context(cop0);
	अगर (cpu_guest_has_contextconfig)
		kvm_restore_gc0_contextconfig(cop0);
#अगर_घोषित CONFIG_64BIT
	kvm_restore_gc0_xcontext(cop0);
	अगर (cpu_guest_has_contextconfig)
		kvm_restore_gc0_xcontextconfig(cop0);
#पूर्ण_अगर
	kvm_restore_gc0_pagemask(cop0);
	kvm_restore_gc0_pagegrain(cop0);
	kvm_restore_gc0_hwrena(cop0);
	kvm_restore_gc0_badvaddr(cop0);
	kvm_restore_gc0_entryhi(cop0);
	kvm_restore_gc0_status(cop0);
	kvm_restore_gc0_पूर्णांकctl(cop0);
	kvm_restore_gc0_epc(cop0);
	kvm_vz_ग_लिखो_gc0_ebase(kvm_पढ़ो_sw_gc0_ebase(cop0));
	अगर (cpu_guest_has_userlocal)
		kvm_restore_gc0_userlocal(cop0);

	kvm_restore_gc0_errorepc(cop0);

	/* restore KScratch रेजिस्टरs अगर enabled in guest */
	अगर (cpu_guest_has_conf4) अणु
		अगर (cpu_guest_has_kscr(2))
			kvm_restore_gc0_kscratch1(cop0);
		अगर (cpu_guest_has_kscr(3))
			kvm_restore_gc0_kscratch2(cop0);
		अगर (cpu_guest_has_kscr(4))
			kvm_restore_gc0_kscratch3(cop0);
		अगर (cpu_guest_has_kscr(5))
			kvm_restore_gc0_kscratch4(cop0);
		अगर (cpu_guest_has_kscr(6))
			kvm_restore_gc0_kscratch5(cop0);
		अगर (cpu_guest_has_kscr(7))
			kvm_restore_gc0_kscratch6(cop0);
	पूर्ण

	अगर (cpu_guest_has_badinstr)
		kvm_restore_gc0_badinstr(cop0);
	अगर (cpu_guest_has_badinstrp)
		kvm_restore_gc0_badinstrp(cop0);

	अगर (cpu_guest_has_segments) अणु
		kvm_restore_gc0_segctl0(cop0);
		kvm_restore_gc0_segctl1(cop0);
		kvm_restore_gc0_segctl2(cop0);
	पूर्ण

	/* restore HTW रेजिस्टरs */
	अगर (cpu_guest_has_htw || cpu_guest_has_ldpte) अणु
		kvm_restore_gc0_pwbase(cop0);
		kvm_restore_gc0_pwfield(cop0);
		kvm_restore_gc0_pwsize(cop0);
		kvm_restore_gc0_pwctl(cop0);
	पूर्ण

	/* restore Root.GuestCtl2 from unused Guest guestctl2 रेजिस्टर */
	अगर (cpu_has_guestctl2)
		ग_लिखो_c0_guestctl2(
			cop0->reg[MIPS_CP0_GUESTCTL2][MIPS_CP0_GUESTCTL2_SEL]);

	/*
	 * We should clear linked load bit to अवरोध पूर्णांकerrupted atomics. This
	 * prevents a SC on the next VCPU from succeeding by matching a LL on
	 * the previous VCPU.
	 */
	अगर (vcpu->kvm->created_vcpus > 1)
		ग_लिखो_gc0_lladdr(0);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vz_vcpu_put(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;

	अगर (current->flags & PF_VCPU)
		kvm_vz_vcpu_save_wired(vcpu);

	kvm_lose_fpu(vcpu);

	kvm_save_gc0_index(cop0);
	kvm_save_gc0_entrylo0(cop0);
	kvm_save_gc0_entrylo1(cop0);
	kvm_save_gc0_context(cop0);
	अगर (cpu_guest_has_contextconfig)
		kvm_save_gc0_contextconfig(cop0);
#अगर_घोषित CONFIG_64BIT
	kvm_save_gc0_xcontext(cop0);
	अगर (cpu_guest_has_contextconfig)
		kvm_save_gc0_xcontextconfig(cop0);
#पूर्ण_अगर
	kvm_save_gc0_pagemask(cop0);
	kvm_save_gc0_pagegrain(cop0);
	kvm_save_gc0_wired(cop0);
	/* allow wired TLB entries to be overwritten */
	clear_gc0_wired(MIPSR6_WIRED_WIRED);
	kvm_save_gc0_hwrena(cop0);
	kvm_save_gc0_badvaddr(cop0);
	kvm_save_gc0_entryhi(cop0);
	kvm_save_gc0_status(cop0);
	kvm_save_gc0_पूर्णांकctl(cop0);
	kvm_save_gc0_epc(cop0);
	kvm_ग_लिखो_sw_gc0_ebase(cop0, kvm_vz_पढ़ो_gc0_ebase());
	अगर (cpu_guest_has_userlocal)
		kvm_save_gc0_userlocal(cop0);

	/* only save implemented config रेजिस्टरs */
	kvm_save_gc0_config(cop0);
	अगर (cpu_guest_has_conf1)
		kvm_save_gc0_config1(cop0);
	अगर (cpu_guest_has_conf2)
		kvm_save_gc0_config2(cop0);
	अगर (cpu_guest_has_conf3)
		kvm_save_gc0_config3(cop0);
	अगर (cpu_guest_has_conf4)
		kvm_save_gc0_config4(cop0);
	अगर (cpu_guest_has_conf5)
		kvm_save_gc0_config5(cop0);
	अगर (cpu_guest_has_conf6)
		kvm_save_gc0_config6(cop0);
	अगर (cpu_guest_has_conf7)
		kvm_save_gc0_config7(cop0);

	kvm_save_gc0_errorepc(cop0);

	/* save KScratch रेजिस्टरs अगर enabled in guest */
	अगर (cpu_guest_has_conf4) अणु
		अगर (cpu_guest_has_kscr(2))
			kvm_save_gc0_kscratch1(cop0);
		अगर (cpu_guest_has_kscr(3))
			kvm_save_gc0_kscratch2(cop0);
		अगर (cpu_guest_has_kscr(4))
			kvm_save_gc0_kscratch3(cop0);
		अगर (cpu_guest_has_kscr(5))
			kvm_save_gc0_kscratch4(cop0);
		अगर (cpu_guest_has_kscr(6))
			kvm_save_gc0_kscratch5(cop0);
		अगर (cpu_guest_has_kscr(7))
			kvm_save_gc0_kscratch6(cop0);
	पूर्ण

	अगर (cpu_guest_has_badinstr)
		kvm_save_gc0_badinstr(cop0);
	अगर (cpu_guest_has_badinstrp)
		kvm_save_gc0_badinstrp(cop0);

	अगर (cpu_guest_has_segments) अणु
		kvm_save_gc0_segctl0(cop0);
		kvm_save_gc0_segctl1(cop0);
		kvm_save_gc0_segctl2(cop0);
	पूर्ण

	/* save HTW रेजिस्टरs अगर enabled in guest */
	अगर (cpu_guest_has_ldpte || (cpu_guest_has_htw &&
	    kvm_पढ़ो_sw_gc0_config3(cop0) & MIPS_CONF3_PW)) अणु
		kvm_save_gc0_pwbase(cop0);
		kvm_save_gc0_pwfield(cop0);
		kvm_save_gc0_pwsize(cop0);
		kvm_save_gc0_pwctl(cop0);
	पूर्ण

	kvm_vz_save_समयr(vcpu);

	/* save Root.GuestCtl2 in unused Guest guestctl2 रेजिस्टर */
	अगर (cpu_has_guestctl2)
		cop0->reg[MIPS_CP0_GUESTCTL2][MIPS_CP0_GUESTCTL2_SEL] =
			पढ़ो_c0_guestctl2();

	वापस 0;
पूर्ण

/**
 * kvm_vz_resize_guest_vtlb() - Attempt to resize guest VTLB.
 * @size:	Number of guest VTLB entries (0 < @size <= root VTLB entries).
 *
 * Attempt to resize the guest VTLB by writing guest Config रेजिस्टरs. This is
 * necessary क्रम cores with a shared root/guest TLB to aव्योम overlap with wired
 * entries in the root VTLB.
 *
 * Returns:	The resulting guest VTLB size.
 */
अटल अचिन्हित पूर्णांक kvm_vz_resize_guest_vtlb(अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक config4 = 0, ret = 0, limit;

	/* Write MMUSize - 1 पूर्णांकo guest Config रेजिस्टरs */
	अगर (cpu_guest_has_conf1)
		change_gc0_config1(MIPS_CONF1_TLBS,
				   (size - 1) << MIPS_CONF1_TLBS_SHIFT);
	अगर (cpu_guest_has_conf4) अणु
		config4 = पढ़ो_gc0_config4();
		अगर (cpu_has_mips_r6 || (config4 & MIPS_CONF4_MMUEXTDEF) ==
		    MIPS_CONF4_MMUEXTDEF_VTLBSIZEEXT) अणु
			config4 &= ~MIPS_CONF4_VTLBSIZEEXT;
			config4 |= ((size - 1) >> MIPS_CONF1_TLBS_SIZE) <<
				MIPS_CONF4_VTLBSIZEEXT_SHIFT;
		पूर्ण अन्यथा अगर ((config4 & MIPS_CONF4_MMUEXTDEF) ==
			   MIPS_CONF4_MMUEXTDEF_MMUSIZEEXT) अणु
			config4 &= ~MIPS_CONF4_MMUSIZEEXT;
			config4 |= ((size - 1) >> MIPS_CONF1_TLBS_SIZE) <<
				MIPS_CONF4_MMUSIZEEXT_SHIFT;
		पूर्ण
		ग_लिखो_gc0_config4(config4);
	पूर्ण

	/*
	 * Set Guest.Wired.Limit = 0 (no limit up to Guest.MMUSize-1), unless it
	 * would exceed Root.Wired.Limit (clearing Guest.Wired.Wired so ग_लिखो
	 * not dropped)
	 */
	अगर (cpu_has_mips_r6) अणु
		limit = (पढ़ो_c0_wired() & MIPSR6_WIRED_LIMIT) >>
						MIPSR6_WIRED_LIMIT_SHIFT;
		अगर (size - 1 <= limit)
			limit = 0;
		ग_लिखो_gc0_wired(limit << MIPSR6_WIRED_LIMIT_SHIFT);
	पूर्ण

	/* Read back MMUSize - 1 */
	back_to_back_c0_hazard();
	अगर (cpu_guest_has_conf1)
		ret = (पढ़ो_gc0_config1() & MIPS_CONF1_TLBS) >>
						MIPS_CONF1_TLBS_SHIFT;
	अगर (config4) अणु
		अगर (cpu_has_mips_r6 || (config4 & MIPS_CONF4_MMUEXTDEF) ==
		    MIPS_CONF4_MMUEXTDEF_VTLBSIZEEXT)
			ret |= ((config4 & MIPS_CONF4_VTLBSIZEEXT) >>
				MIPS_CONF4_VTLBSIZEEXT_SHIFT) <<
				MIPS_CONF1_TLBS_SIZE;
		अन्यथा अगर ((config4 & MIPS_CONF4_MMUEXTDEF) ==
			 MIPS_CONF4_MMUEXTDEF_MMUSIZEEXT)
			ret |= ((config4 & MIPS_CONF4_MMUSIZEEXT) >>
				MIPS_CONF4_MMUSIZEEXT_SHIFT) <<
				MIPS_CONF1_TLBS_SIZE;
	पूर्ण
	वापस ret + 1;
पूर्ण

अटल पूर्णांक kvm_vz_hardware_enable(व्योम)
अणु
	अचिन्हित पूर्णांक mmu_size, guest_mmu_size, ftlb_size;
	u64 guest_cvmctl, cvmvmconfig;

	चयन (current_cpu_type()) अणु
	हाल CPU_CAVIUM_OCTEON3:
		/* Set up guest समयr/perfcount IRQ lines */
		guest_cvmctl = पढ़ो_gc0_cvmctl();
		guest_cvmctl &= ~CVMCTL_IPTI;
		guest_cvmctl |= 7ull << CVMCTL_IPTI_SHIFT;
		guest_cvmctl &= ~CVMCTL_IPPCI;
		guest_cvmctl |= 6ull << CVMCTL_IPPCI_SHIFT;
		ग_लिखो_gc0_cvmctl(guest_cvmctl);

		cvmvmconfig = पढ़ो_c0_cvmvmconfig();
		/* No I/O hole translation. */
		cvmvmconfig |= CVMVMCONF_DGHT;
		/* Halve the root MMU size */
		mmu_size = ((cvmvmconfig & CVMVMCONF_MMUSIZEM1)
			    >> CVMVMCONF_MMUSIZEM1_S) + 1;
		guest_mmu_size = mmu_size / 2;
		mmu_size -= guest_mmu_size;
		cvmvmconfig &= ~CVMVMCONF_RMMUSIZEM1;
		cvmvmconfig |= mmu_size - 1;
		ग_लिखो_c0_cvmvmconfig(cvmvmconfig);

		/* Update our records */
		current_cpu_data.tlbsize = mmu_size;
		current_cpu_data.tlbsizevtlb = mmu_size;
		current_cpu_data.guest.tlbsize = guest_mmu_size;

		/* Flush moved entries in new (guest) context */
		kvm_vz_local_flush_guesttlb_all();
		अवरोध;
	शेष:
		/*
		 * ImgTec cores tend to use a shared root/guest TLB. To aव्योम
		 * overlap of root wired and guest entries, the guest TLB may
		 * need resizing.
		 */
		mmu_size = current_cpu_data.tlbsizevtlb;
		ftlb_size = current_cpu_data.tlbsize - mmu_size;

		/* Try चयनing to maximum guest VTLB size क्रम flush */
		guest_mmu_size = kvm_vz_resize_guest_vtlb(mmu_size);
		current_cpu_data.guest.tlbsize = guest_mmu_size + ftlb_size;
		kvm_vz_local_flush_guesttlb_all();

		/*
		 * Reduce to make space क्रम root wired entries and at least 2
		 * root non-wired entries. This करोes assume that दीर्घ-term wired
		 * entries won't be added later.
		 */
		guest_mmu_size = mmu_size - num_wired_entries() - 2;
		guest_mmu_size = kvm_vz_resize_guest_vtlb(guest_mmu_size);
		current_cpu_data.guest.tlbsize = guest_mmu_size + ftlb_size;

		/*
		 * Write the VTLB size, but अगर another CPU has alपढ़ोy written,
		 * check it matches or we won't provide a consistent view to the
		 * guest. If this ever happens it suggests an asymmetric number
		 * of wired entries.
		 */
		अगर (cmpxchg(&kvm_vz_guest_vtlb_size, 0, guest_mmu_size) &&
		    WARN(guest_mmu_size != kvm_vz_guest_vtlb_size,
			 "Available guest VTLB size mismatch"))
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	/*
	 * Enable भवization features granting guest direct control of
	 * certain features:
	 * CP0=1:	Guest coprocessor 0 context.
	 * AT=Guest:	Guest MMU.
	 * CG=1:	Hit (भव address) CACHE operations (optional).
	 * CF=1:	Guest Config रेजिस्टरs.
	 * CGI=1:	Indexed flush CACHE operations (optional).
	 */
	ग_लिखो_c0_guestctl0(MIPS_GCTL0_CP0 |
			   (MIPS_GCTL0_AT_GUEST << MIPS_GCTL0_AT_SHIFT) |
			   MIPS_GCTL0_CG | MIPS_GCTL0_CF);
	अगर (cpu_has_guestctl0ext) अणु
		अगर (current_cpu_type() != CPU_LOONGSON64)
			set_c0_guestctl0ext(MIPS_GCTL0EXT_CGI);
		अन्यथा
			clear_c0_guestctl0ext(MIPS_GCTL0EXT_CGI);
	पूर्ण

	अगर (cpu_has_guestid) अणु
		ग_लिखो_c0_guestctl1(0);
		kvm_vz_local_flush_roottlb_all_guests();

		GUESTID_MASK = current_cpu_data.guestid_mask;
		GUESTID_FIRST_VERSION = GUESTID_MASK + 1;
		GUESTID_VERSION_MASK = ~GUESTID_MASK;

		current_cpu_data.guestid_cache = GUESTID_FIRST_VERSION;
	पूर्ण

	/* clear any pending injected भव guest पूर्णांकerrupts */
	अगर (cpu_has_guestctl2)
		clear_c0_guestctl2(0x3f << 10);

#अगर_घोषित CONFIG_CPU_LOONGSON64
	/* Control guest CCA attribute */
	अगर (cpu_has_csr())
		csr_ग_लिखोl(csr_पढ़ोl(0xffffffec) | 0x1, 0xffffffec);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम kvm_vz_hardware_disable(व्योम)
अणु
	u64 cvmvmconfig;
	अचिन्हित पूर्णांक mmu_size;

	/* Flush any reमुख्यing guest TLB entries */
	kvm_vz_local_flush_guesttlb_all();

	चयन (current_cpu_type()) अणु
	हाल CPU_CAVIUM_OCTEON3:
		/*
		 * Allocate whole TLB क्रम root. Existing guest TLB entries will
		 * change ownership to the root TLB. We should be safe though as
		 * they've alपढ़ोy been flushed above जबतक in guest TLB.
		 */
		cvmvmconfig = पढ़ो_c0_cvmvmconfig();
		mmu_size = ((cvmvmconfig & CVMVMCONF_MMUSIZEM1)
			    >> CVMVMCONF_MMUSIZEM1_S) + 1;
		cvmvmconfig &= ~CVMVMCONF_RMMUSIZEM1;
		cvmvmconfig |= mmu_size - 1;
		ग_लिखो_c0_cvmvmconfig(cvmvmconfig);

		/* Update our records */
		current_cpu_data.tlbsize = mmu_size;
		current_cpu_data.tlbsizevtlb = mmu_size;
		current_cpu_data.guest.tlbsize = 0;

		/* Flush moved entries in new (root) context */
		local_flush_tlb_all();
		अवरोध;
	पूर्ण

	अगर (cpu_has_guestid) अणु
		ग_लिखो_c0_guestctl1(0);
		kvm_vz_local_flush_roottlb_all_guests();
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_vz_check_extension(काष्ठा kvm *kvm, दीर्घ ext)
अणु
	पूर्णांक r;

	चयन (ext) अणु
	हाल KVM_CAP_MIPS_VZ:
		/* we wouldn't be here unless cpu_has_vz */
		r = 1;
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल KVM_CAP_MIPS_64BIT:
		/* We support 64-bit रेजिस्टरs/operations and addresses */
		r = 2;
		अवरोध;
#पूर्ण_अगर
	हाल KVM_CAP_IOEVENTFD:
		r = 1;
		अवरोध;
	शेष:
		r = 0;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_vz_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		vcpu->arch.vzguestid[i] = 0;

	वापस 0;
पूर्ण

अटल व्योम kvm_vz_vcpu_uninit(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक cpu;

	/*
	 * If the VCPU is मुक्तd and reused as another VCPU, we करोn't want the
	 * matching poपूर्णांकer wrongly hanging around in last_vcpu[] or
	 * last_exec_vcpu[].
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (last_vcpu[cpu] == vcpu)
			last_vcpu[cpu] = शून्य;
		अगर (last_exec_vcpu[cpu] == vcpu)
			last_exec_vcpu[cpu] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_vz_vcpu_setup(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	अचिन्हित दीर्घ count_hz = 100*1000*1000; /* शेष to 100 MHz */

	/*
	 * Start off the समयr at the same frequency as the host समयr, but the
	 * soft समयr करोesn't handle frequencies greater than 1GHz yet.
	 */
	अगर (mips_hpt_frequency && mips_hpt_frequency <= NSEC_PER_SEC)
		count_hz = mips_hpt_frequency;
	kvm_mips_init_count(vcpu, count_hz);

	/*
	 * Initialize guest रेजिस्टर state to valid architectural reset state.
	 */

	/* PageGrain */
	अगर (cpu_has_mips_r5 || cpu_has_mips_r6)
		kvm_ग_लिखो_sw_gc0_pagegrain(cop0, PG_RIE | PG_XIE | PG_IEC);
	/* Wired */
	अगर (cpu_has_mips_r6)
		kvm_ग_लिखो_sw_gc0_wired(cop0,
				       पढ़ो_gc0_wired() & MIPSR6_WIRED_LIMIT);
	/* Status */
	kvm_ग_लिखो_sw_gc0_status(cop0, ST0_BEV | ST0_ERL);
	अगर (cpu_has_mips_r5 || cpu_has_mips_r6)
		kvm_change_sw_gc0_status(cop0, ST0_FR, पढ़ो_gc0_status());
	/* IntCtl */
	kvm_ग_लिखो_sw_gc0_पूर्णांकctl(cop0, पढ़ो_gc0_पूर्णांकctl() &
				(INTCTLF_IPFDC | INTCTLF_IPPCI | INTCTLF_IPTI));
	/* PRId */
	kvm_ग_लिखो_sw_gc0_prid(cop0, boot_cpu_data.processor_id);
	/* EBase */
	kvm_ग_लिखो_sw_gc0_ebase(cop0, (s32)0x80000000 | vcpu->vcpu_id);
	/* Config */
	kvm_save_gc0_config(cop0);
	/* architecturally writable (e.g. from guest) */
	kvm_change_sw_gc0_config(cop0, CONF_CM_CMASK,
				 _page_cachable_शेष >> _CACHE_SHIFT);
	/* architecturally पढ़ो only, but maybe writable from root */
	kvm_change_sw_gc0_config(cop0, MIPS_CONF_MT, पढ़ो_c0_config());
	अगर (cpu_guest_has_conf1) अणु
		kvm_set_sw_gc0_config(cop0, MIPS_CONF_M);
		/* Config1 */
		kvm_save_gc0_config1(cop0);
		/* architecturally पढ़ो only, but maybe writable from root */
		kvm_clear_sw_gc0_config1(cop0, MIPS_CONF1_C2	|
					       MIPS_CONF1_MD	|
					       MIPS_CONF1_PC	|
					       MIPS_CONF1_WR	|
					       MIPS_CONF1_CA	|
					       MIPS_CONF1_FP);
	पूर्ण
	अगर (cpu_guest_has_conf2) अणु
		kvm_set_sw_gc0_config1(cop0, MIPS_CONF_M);
		/* Config2 */
		kvm_save_gc0_config2(cop0);
	पूर्ण
	अगर (cpu_guest_has_conf3) अणु
		kvm_set_sw_gc0_config2(cop0, MIPS_CONF_M);
		/* Config3 */
		kvm_save_gc0_config3(cop0);
		/* architecturally writable (e.g. from guest) */
		kvm_clear_sw_gc0_config3(cop0, MIPS_CONF3_ISA_OE);
		/* architecturally पढ़ो only, but maybe writable from root */
		kvm_clear_sw_gc0_config3(cop0, MIPS_CONF3_MSA	|
					       MIPS_CONF3_BPG	|
					       MIPS_CONF3_ULRI	|
					       MIPS_CONF3_DSP	|
					       MIPS_CONF3_CTXTC	|
					       MIPS_CONF3_ITL	|
					       MIPS_CONF3_LPA	|
					       MIPS_CONF3_VEIC	|
					       MIPS_CONF3_VINT	|
					       MIPS_CONF3_SP	|
					       MIPS_CONF3_CDMM	|
					       MIPS_CONF3_MT	|
					       MIPS_CONF3_SM	|
					       MIPS_CONF3_TL);
	पूर्ण
	अगर (cpu_guest_has_conf4) अणु
		kvm_set_sw_gc0_config3(cop0, MIPS_CONF_M);
		/* Config4 */
		kvm_save_gc0_config4(cop0);
	पूर्ण
	अगर (cpu_guest_has_conf5) अणु
		kvm_set_sw_gc0_config4(cop0, MIPS_CONF_M);
		/* Config5 */
		kvm_save_gc0_config5(cop0);
		/* architecturally writable (e.g. from guest) */
		kvm_clear_sw_gc0_config5(cop0, MIPS_CONF5_K	|
					       MIPS_CONF5_CV	|
					       MIPS_CONF5_MSAEN	|
					       MIPS_CONF5_UFE	|
					       MIPS_CONF5_FRE	|
					       MIPS_CONF5_SBRI	|
					       MIPS_CONF5_UFR);
		/* architecturally पढ़ो only, but maybe writable from root */
		kvm_clear_sw_gc0_config5(cop0, MIPS_CONF5_MRP);
	पूर्ण

	अगर (cpu_guest_has_contextconfig) अणु
		/* ContextConfig */
		kvm_ग_लिखो_sw_gc0_contextconfig(cop0, 0x007ffff0);
#अगर_घोषित CONFIG_64BIT
		/* XContextConfig */
		/* bits SEGBITS-13+3:4 set */
		kvm_ग_लिखो_sw_gc0_xcontextconfig(cop0,
					((1ull << (cpu_vmbits - 13)) - 1) << 4);
#पूर्ण_अगर
	पूर्ण

	/* Implementation dependent, use the legacy layout */
	अगर (cpu_guest_has_segments) अणु
		/* SegCtl0, SegCtl1, SegCtl2 */
		kvm_ग_लिखो_sw_gc0_segctl0(cop0, 0x00200010);
		kvm_ग_लिखो_sw_gc0_segctl1(cop0, 0x00000002 |
				(_page_cachable_शेष >> _CACHE_SHIFT) <<
						(16 + MIPS_SEGCFG_C_SHIFT));
		kvm_ग_लिखो_sw_gc0_segctl2(cop0, 0x00380438);
	पूर्ण

	/* reset HTW रेजिस्टरs */
	अगर (cpu_guest_has_htw && (cpu_has_mips_r5 || cpu_has_mips_r6)) अणु
		/* PWField */
		kvm_ग_लिखो_sw_gc0_pwfield(cop0, 0x0c30c302);
		/* PWSize */
		kvm_ग_लिखो_sw_gc0_pwsize(cop0, 1 << MIPS_PWSIZE_PTW_SHIFT);
	पूर्ण

	/* start with no pending भव guest पूर्णांकerrupts */
	अगर (cpu_has_guestctl2)
		cop0->reg[MIPS_CP0_GUESTCTL2][MIPS_CP0_GUESTCTL2_SEL] = 0;

	/* Put PC at reset vector */
	vcpu->arch.pc = CKSEG1ADDR(0x1fc00000);

	वापस 0;
पूर्ण

अटल व्योम kvm_vz_prepare_flush_shaकरोw(काष्ठा kvm *kvm)
अणु
	अगर (!cpu_has_guestid) अणु
		/*
		 * For each CPU there is a single GPA ASID used by all VCPUs in
		 * the VM, so it करोesn't make sense क्रम the VCPUs to handle
		 * invalidation of these ASIDs inभागidually.
		 *
		 * Instead mark all CPUs as needing ASID invalidation in
		 * asid_flush_mask, and kvm_flush_remote_tlbs(kvm) will
		 * kick any running VCPUs so they check asid_flush_mask.
		 */
		cpumask_setall(&kvm->arch.asid_flush_mask);
	पूर्ण
पूर्ण

अटल व्योम kvm_vz_vcpu_reenter(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक preserve_guest_tlb;

	preserve_guest_tlb = kvm_vz_check_requests(vcpu, cpu);

	अगर (preserve_guest_tlb)
		kvm_vz_vcpu_save_wired(vcpu);

	kvm_vz_vcpu_load_tlb(vcpu, cpu);

	अगर (preserve_guest_tlb)
		kvm_vz_vcpu_load_wired(vcpu);
पूर्ण

अटल पूर्णांक kvm_vz_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक r;

	kvm_vz_acquire_hसमयr(vcpu);
	/* Check अगर we have any exceptions/पूर्णांकerrupts pending */
	kvm_mips_deliver_पूर्णांकerrupts(vcpu, पढ़ो_gc0_cause());

	kvm_vz_check_requests(vcpu, cpu);
	kvm_vz_vcpu_load_tlb(vcpu, cpu);
	kvm_vz_vcpu_load_wired(vcpu);

	r = vcpu->arch.vcpu_run(vcpu);

	kvm_vz_vcpu_save_wired(vcpu);

	वापस r;
पूर्ण

अटल काष्ठा kvm_mips_callbacks kvm_vz_callbacks = अणु
	.handle_cop_unusable = kvm_trap_vz_handle_cop_unusable,
	.handle_tlb_mod = kvm_trap_vz_handle_tlb_st_miss,
	.handle_tlb_ld_miss = kvm_trap_vz_handle_tlb_ld_miss,
	.handle_tlb_st_miss = kvm_trap_vz_handle_tlb_st_miss,
	.handle_addr_err_st = kvm_trap_vz_no_handler,
	.handle_addr_err_ld = kvm_trap_vz_no_handler,
	.handle_syscall = kvm_trap_vz_no_handler,
	.handle_res_inst = kvm_trap_vz_no_handler,
	.handle_अवरोध = kvm_trap_vz_no_handler,
	.handle_msa_disabled = kvm_trap_vz_handle_msa_disabled,
	.handle_guest_निकास = kvm_trap_vz_handle_guest_निकास,

	.hardware_enable = kvm_vz_hardware_enable,
	.hardware_disable = kvm_vz_hardware_disable,
	.check_extension = kvm_vz_check_extension,
	.vcpu_init = kvm_vz_vcpu_init,
	.vcpu_uninit = kvm_vz_vcpu_uninit,
	.vcpu_setup = kvm_vz_vcpu_setup,
	.prepare_flush_shaकरोw = kvm_vz_prepare_flush_shaकरोw,
	.gva_to_gpa = kvm_vz_gva_to_gpa_cb,
	.queue_समयr_पूर्णांक = kvm_vz_queue_समयr_पूर्णांक_cb,
	.dequeue_समयr_पूर्णांक = kvm_vz_dequeue_समयr_पूर्णांक_cb,
	.queue_io_पूर्णांक = kvm_vz_queue_io_पूर्णांक_cb,
	.dequeue_io_पूर्णांक = kvm_vz_dequeue_io_पूर्णांक_cb,
	.irq_deliver = kvm_vz_irq_deliver_cb,
	.irq_clear = kvm_vz_irq_clear_cb,
	.num_regs = kvm_vz_num_regs,
	.copy_reg_indices = kvm_vz_copy_reg_indices,
	.get_one_reg = kvm_vz_get_one_reg,
	.set_one_reg = kvm_vz_set_one_reg,
	.vcpu_load = kvm_vz_vcpu_load,
	.vcpu_put = kvm_vz_vcpu_put,
	.vcpu_run = kvm_vz_vcpu_run,
	.vcpu_reenter = kvm_vz_vcpu_reenter,
पूर्ण;

पूर्णांक kvm_mips_emulation_init(काष्ठा kvm_mips_callbacks **install_callbacks)
अणु
	अगर (!cpu_has_vz)
		वापस -ENODEV;

	/*
	 * VZ requires at least 2 KScratch रेजिस्टरs, so it should have been
	 * possible to allocate pgd_reg.
	 */
	अगर (WARN(pgd_reg == -1,
		 "pgd_reg not allocated even though cpu_has_vz\n"))
		वापस -ENODEV;

	pr_info("Starting KVM with MIPS VZ extensions\n");

	*install_callbacks = &kvm_vz_callbacks;
	वापस 0;
पूर्ण
