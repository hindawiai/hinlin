<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: Inकाष्ठाion/Exception emulation
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/kvm_host.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/memblock.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/inst.h>

#अघोषित CONFIG_MIPS_MT
#समावेश <यंत्र/r4kcache.h>
#घोषणा CONFIG_MIPS_MT

#समावेश "interrupt.h"

#समावेश "trace.h"

/*
 * Compute the वापस address and करो emulate branch simulation, अगर required.
 * This function should be called only in branch delay slot active.
 */
अटल पूर्णांक kvm_compute_वापस_epc(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ instpc,
				  अचिन्हित दीर्घ *out)
अणु
	अचिन्हित पूर्णांक dspcontrol;
	जोड़ mips_inकाष्ठाion insn;
	काष्ठा kvm_vcpu_arch *arch = &vcpu->arch;
	दीर्घ epc = instpc;
	दीर्घ nextpc;
	पूर्णांक err;

	अगर (epc & 3) अणु
		kvm_err("%s: unaligned epc\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Read the inकाष्ठाion */
	err = kvm_get_badinstrp((u32 *)epc, vcpu, &insn.word);
	अगर (err)
		वापस err;

	चयन (insn.i_क्रमmat.opcode) अणु
		/* jr and jalr are in r_क्रमmat क्रमmat. */
	हाल spec_op:
		चयन (insn.r_क्रमmat.func) अणु
		हाल jalr_op:
			arch->gprs[insn.r_क्रमmat.rd] = epc + 8;
			fallthrough;
		हाल jr_op:
			nextpc = arch->gprs[insn.r_क्रमmat.rs];
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

		/*
		 * This group contains:
		 * bltz_op, bgez_op, bltzl_op, bgezl_op,
		 * bltzal_op, bgezal_op, bltzall_op, bgezall_op.
		 */
	हाल bcond_op:
		चयन (insn.i_क्रमmat.rt) अणु
		हाल bltz_op:
		हाल bltzl_op:
			अगर ((दीर्घ)arch->gprs[insn.i_क्रमmat.rs] < 0)
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				epc += 8;
			nextpc = epc;
			अवरोध;

		हाल bgez_op:
		हाल bgezl_op:
			अगर ((दीर्घ)arch->gprs[insn.i_क्रमmat.rs] >= 0)
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				epc += 8;
			nextpc = epc;
			अवरोध;

		हाल bltzal_op:
		हाल bltzall_op:
			arch->gprs[31] = epc + 8;
			अगर ((दीर्घ)arch->gprs[insn.i_क्रमmat.rs] < 0)
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				epc += 8;
			nextpc = epc;
			अवरोध;

		हाल bgezal_op:
		हाल bgezall_op:
			arch->gprs[31] = epc + 8;
			अगर ((दीर्घ)arch->gprs[insn.i_क्रमmat.rs] >= 0)
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				epc += 8;
			nextpc = epc;
			अवरोध;
		हाल bposge32_op:
			अगर (!cpu_has_dsp) अणु
				kvm_err("%s: DSP branch but not DSP ASE\n",
					__func__);
				वापस -EINVAL;
			पूर्ण

			dspcontrol = rddsp(0x01);

			अगर (dspcontrol >= 32)
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				epc += 8;
			nextpc = epc;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

		/* These are unconditional and in j_क्रमmat. */
	हाल jal_op:
		arch->gprs[31] = instpc + 8;
		fallthrough;
	हाल j_op:
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		epc |= (insn.j_क्रमmat.target << 2);
		nextpc = epc;
		अवरोध;

		/* These are conditional and in i_क्रमmat. */
	हाल beq_op:
	हाल beql_op:
		अगर (arch->gprs[insn.i_क्रमmat.rs] ==
		    arch->gprs[insn.i_क्रमmat.rt])
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		nextpc = epc;
		अवरोध;

	हाल bne_op:
	हाल bnel_op:
		अगर (arch->gprs[insn.i_क्रमmat.rs] !=
		    arch->gprs[insn.i_क्रमmat.rt])
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		nextpc = epc;
		अवरोध;

	हाल blez_op:	/* POP06 */
#अगर_अघोषित CONFIG_CPU_MIPSR6
	हाल blezl_op:	/* हटाओd in R6 */
#पूर्ण_अगर
		अगर (insn.i_क्रमmat.rt != 0)
			जाओ compact_branch;
		अगर ((दीर्घ)arch->gprs[insn.i_क्रमmat.rs] <= 0)
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		nextpc = epc;
		अवरोध;

	हाल bgtz_op:	/* POP07 */
#अगर_अघोषित CONFIG_CPU_MIPSR6
	हाल bgtzl_op:	/* हटाओd in R6 */
#पूर्ण_अगर
		अगर (insn.i_क्रमmat.rt != 0)
			जाओ compact_branch;
		अगर ((दीर्घ)arch->gprs[insn.i_क्रमmat.rs] > 0)
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		nextpc = epc;
		अवरोध;

		/* And now the FPA/cp1 branch inकाष्ठाions. */
	हाल cop1_op:
		kvm_err("%s: unsupported cop1_op\n", __func__);
		वापस -EINVAL;

#अगर_घोषित CONFIG_CPU_MIPSR6
	/* R6 added the following compact branches with क्रमbidden slots */
	हाल blezl_op:	/* POP26 */
	हाल bgtzl_op:	/* POP27 */
		/* only rt == 0 isn't compact branch */
		अगर (insn.i_क्रमmat.rt != 0)
			जाओ compact_branch;
		वापस -EINVAL;
	हाल pop10_op:
	हाल pop30_op:
		/* only rs == rt == 0 is reserved, rest are compact branches */
		अगर (insn.i_क्रमmat.rs != 0 || insn.i_क्रमmat.rt != 0)
			जाओ compact_branch;
		वापस -EINVAL;
	हाल pop66_op:
	हाल pop76_op:
		/* only rs == 0 isn't compact branch */
		अगर (insn.i_क्रमmat.rs != 0)
			जाओ compact_branch;
		वापस -EINVAL;
compact_branch:
		/*
		 * If we've hit an exception on the क्रमbidden slot, then
		 * the branch must not have been taken.
		 */
		epc += 8;
		nextpc = epc;
		अवरोध;
#अन्यथा
compact_branch:
		/* Fall through - Compact branches not supported beक्रमe R6 */
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	*out = nextpc;
	वापस 0;
पूर्ण

क्रमागत emulation_result update_pc(काष्ठा kvm_vcpu *vcpu, u32 cause)
अणु
	पूर्णांक err;

	अगर (cause & CAUSEF_BD) अणु
		err = kvm_compute_वापस_epc(vcpu, vcpu->arch.pc,
					     &vcpu->arch.pc);
		अगर (err)
			वापस EMULATE_FAIL;
	पूर्ण अन्यथा अणु
		vcpu->arch.pc += 4;
	पूर्ण

	kvm_debug("update_pc(): New PC: %#lx\n", vcpu->arch.pc);

	वापस EMULATE_DONE;
पूर्ण

/**
 * kvm_get_badinstr() - Get bad inकाष्ठाion encoding.
 * @opc:	Guest poपूर्णांकer to faulting inकाष्ठाion.
 * @vcpu:	KVM VCPU inक्रमmation.
 *
 * Gets the inकाष्ठाion encoding of the faulting inकाष्ठाion, using the saved
 * BadInstr रेजिस्टर value अगर it exists, otherwise falling back to पढ़ोing guest
 * memory at @opc.
 *
 * Returns:	The inकाष्ठाion encoding of the faulting inकाष्ठाion.
 */
पूर्णांक kvm_get_badinstr(u32 *opc, काष्ठा kvm_vcpu *vcpu, u32 *out)
अणु
	अगर (cpu_has_badinstr) अणु
		*out = vcpu->arch.host_cp0_badinstr;
		वापस 0;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "CPU doesn't have BadInstr register\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * kvm_get_badinstrp() - Get bad prior inकाष्ठाion encoding.
 * @opc:	Guest poपूर्णांकer to prior faulting inकाष्ठाion.
 * @vcpu:	KVM VCPU inक्रमmation.
 *
 * Gets the inकाष्ठाion encoding of the prior faulting inकाष्ठाion (the branch
 * containing the delay slot which faulted), using the saved BadInstrP रेजिस्टर
 * value अगर it exists, otherwise falling back to पढ़ोing guest memory at @opc.
 *
 * Returns:	The inकाष्ठाion encoding of the prior faulting inकाष्ठाion.
 */
पूर्णांक kvm_get_badinstrp(u32 *opc, काष्ठा kvm_vcpu *vcpu, u32 *out)
अणु
	अगर (cpu_has_badinstrp) अणु
		*out = vcpu->arch.host_cp0_badinstrp;
		वापस 0;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "CPU doesn't have BadInstrp register\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * kvm_mips_count_disabled() - Find whether the CP0_Count समयr is disabled.
 * @vcpu:	Virtual CPU.
 *
 * Returns:	1 अगर the CP0_Count समयr is disabled by either the guest
 *		CP0_Cause.DC bit or the count_ctl.DC bit.
 *		0 otherwise (in which हाल CP0_Count समयr is running).
 */
पूर्णांक kvm_mips_count_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;

	वापस	(vcpu->arch.count_ctl & KVM_REG_MIPS_COUNT_CTL_DC) ||
		(kvm_पढ़ो_c0_guest_cause(cop0) & CAUSEF_DC);
पूर्ण

/**
 * kvm_mips_kसमय_प्रकारo_count() - Scale kसमय_प्रकार to a 32-bit count.
 *
 * Caches the dynamic nanosecond bias in vcpu->arch.count_dyn_bias.
 *
 * Assumes !kvm_mips_count_disabled(@vcpu) (guest CP0_Count समयr is running).
 */
अटल u32 kvm_mips_kसमय_प्रकारo_count(काष्ठा kvm_vcpu *vcpu, kसमय_प्रकार now)
अणु
	s64 now_ns, periods;
	u64 delta;

	now_ns = kसमय_प्रकारo_ns(now);
	delta = now_ns + vcpu->arch.count_dyn_bias;

	अगर (delta >= vcpu->arch.count_period) अणु
		/* If delta is out of safe range the bias needs adjusting */
		periods = भाग64_s64(now_ns, vcpu->arch.count_period);
		vcpu->arch.count_dyn_bias = -periods * vcpu->arch.count_period;
		/* Recalculate delta with new bias */
		delta = now_ns + vcpu->arch.count_dyn_bias;
	पूर्ण

	/*
	 * We've ensured that:
	 *   delta < count_period
	 *
	 * Thereक्रमe the पूर्णांकermediate delta*count_hz will never overflow since
	 * at the boundary condition:
	 *   delta = count_period
	 *   delta = NSEC_PER_SEC * 2^32 / count_hz
	 *   delta * count_hz = NSEC_PER_SEC * 2^32
	 */
	वापस भाग_u64(delta * vcpu->arch.count_hz, NSEC_PER_SEC);
पूर्ण

/**
 * kvm_mips_count_समय() - Get effective current समय.
 * @vcpu:	Virtual CPU.
 *
 * Get effective monotonic kसमय. This is usually a straightक्रमward kसमय_get(),
 * except when the master disable bit is set in count_ctl, in which हाल it is
 * count_resume, i.e. the समय that the count was disabled.
 *
 * Returns:	Effective monotonic kसमय क्रम CP0_Count.
 */
अटल अंतरभूत kसमय_प्रकार kvm_mips_count_समय(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (unlikely(vcpu->arch.count_ctl & KVM_REG_MIPS_COUNT_CTL_DC))
		वापस vcpu->arch.count_resume;

	वापस kसमय_get();
पूर्ण

/**
 * kvm_mips_पढ़ो_count_running() - Read the current count value as अगर running.
 * @vcpu:	Virtual CPU.
 * @now:	Kernel समय to पढ़ो CP0_Count at.
 *
 * Returns the current guest CP0_Count रेजिस्टर at समय @now and handles अगर the
 * समयr पूर्णांकerrupt is pending and hasn't been handled yet.
 *
 * Returns:	The current value of the guest CP0_Count रेजिस्टर.
 */
अटल u32 kvm_mips_पढ़ो_count_running(काष्ठा kvm_vcpu *vcpu, kसमय_प्रकार now)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	kसमय_प्रकार expires, threshold;
	u32 count, compare;
	पूर्णांक running;

	/* Calculate the biased and scaled guest CP0_Count */
	count = vcpu->arch.count_bias + kvm_mips_kसमय_प्रकारo_count(vcpu, now);
	compare = kvm_पढ़ो_c0_guest_compare(cop0);

	/*
	 * Find whether CP0_Count has reached the बंदst समयr पूर्णांकerrupt. If
	 * not, we shouldn't inject it.
	 */
	अगर ((s32)(count - compare) < 0)
		वापस count;

	/*
	 * The CP0_Count we're going to वापस has alपढ़ोy reached the बंदst
	 * समयr पूर्णांकerrupt. Quickly check अगर it really is a new पूर्णांकerrupt by
	 * looking at whether the पूर्णांकerval until the hrसमयr expiry समय is
	 * less than 1/4 of the समयr period.
	 */
	expires = hrसमयr_get_expires(&vcpu->arch.comparecount_समयr);
	threshold = kसमय_add_ns(now, vcpu->arch.count_period / 4);
	अगर (kसमय_beक्रमe(expires, threshold)) अणु
		/*
		 * Cancel it जबतक we handle it so there's no chance of
		 * पूर्णांकerference with the समयout handler.
		 */
		running = hrसमयr_cancel(&vcpu->arch.comparecount_समयr);

		/* Nothing should be रुकोing on the समयout */
		kvm_mips_callbacks->queue_समयr_पूर्णांक(vcpu);

		/*
		 * Restart the समयr अगर it was running based on the expiry समय
		 * we पढ़ो, so that we करोn't push it back 2 periods.
		 */
		अगर (running) अणु
			expires = kसमय_add_ns(expires,
					       vcpu->arch.count_period);
			hrसमयr_start(&vcpu->arch.comparecount_समयr, expires,
				      HRTIMER_MODE_ABS);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/**
 * kvm_mips_पढ़ो_count() - Read the current count value.
 * @vcpu:	Virtual CPU.
 *
 * Read the current guest CP0_Count value, taking पूर्णांकo account whether the समयr
 * is stopped.
 *
 * Returns:	The current guest CP0_Count value.
 */
u32 kvm_mips_पढ़ो_count(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;

	/* If count disabled just पढ़ो अटल copy of count */
	अगर (kvm_mips_count_disabled(vcpu))
		वापस kvm_पढ़ो_c0_guest_count(cop0);

	वापस kvm_mips_पढ़ो_count_running(vcpu, kसमय_get());
पूर्ण

/**
 * kvm_mips_मुक्तze_hrसमयr() - Safely stop the hrसमयr.
 * @vcpu:	Virtual CPU.
 * @count:	Output poपूर्णांकer क्रम CP0_Count value at poपूर्णांक of मुक्तze.
 *
 * Freeze the hrसमयr safely and वापस both the kसमय and the CP0_Count value
 * at the poपूर्णांक it was frozen. It is guaranteed that any pending पूर्णांकerrupts at
 * the poपूर्णांक it was frozen are handled, and none after that poपूर्णांक.
 *
 * This is useful where the समय/CP0_Count is needed in the calculation of the
 * new parameters.
 *
 * Assumes !kvm_mips_count_disabled(@vcpu) (guest CP0_Count समयr is running).
 *
 * Returns:	The kसमय at the poपूर्णांक of मुक्तze.
 */
kसमय_प्रकार kvm_mips_मुक्तze_hrसमयr(काष्ठा kvm_vcpu *vcpu, u32 *count)
अणु
	kसमय_प्रकार now;

	/* stop hrसमयr beक्रमe finding समय */
	hrसमयr_cancel(&vcpu->arch.comparecount_समयr);
	now = kसमय_get();

	/* find count at this poपूर्णांक and handle pending hrसमयr */
	*count = kvm_mips_पढ़ो_count_running(vcpu, now);

	वापस now;
पूर्ण

/**
 * kvm_mips_resume_hrसमयr() - Resume hrसमयr, updating expiry.
 * @vcpu:	Virtual CPU.
 * @now:	kसमय at poपूर्णांक of resume.
 * @count:	CP0_Count at poपूर्णांक of resume.
 *
 * Resumes the समयr and updates the समयr expiry based on @now and @count.
 * This can be used in conjunction with kvm_mips_मुक्तze_समयr() when समयr
 * parameters need to be changed.
 *
 * It is guaranteed that a समयr पूर्णांकerrupt immediately after resume will be
 * handled, but not अगर CP_Compare is exactly at @count. That हाल is alपढ़ोy
 * handled by kvm_mips_मुक्तze_समयr().
 *
 * Assumes !kvm_mips_count_disabled(@vcpu) (guest CP0_Count समयr is running).
 */
अटल व्योम kvm_mips_resume_hrसमयr(काष्ठा kvm_vcpu *vcpu,
				    kसमय_प्रकार now, u32 count)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	u32 compare;
	u64 delta;
	kसमय_प्रकार expire;

	/* Calculate समयout (wrap 0 to 2^32) */
	compare = kvm_पढ़ो_c0_guest_compare(cop0);
	delta = (u64)(u32)(compare - count - 1) + 1;
	delta = भाग_u64(delta * NSEC_PER_SEC, vcpu->arch.count_hz);
	expire = kसमय_add_ns(now, delta);

	/* Update hrसमयr to use new समयout */
	hrसमयr_cancel(&vcpu->arch.comparecount_समयr);
	hrसमयr_start(&vcpu->arch.comparecount_समयr, expire, HRTIMER_MODE_ABS);
पूर्ण

/**
 * kvm_mips_restore_hrसमयr() - Restore hrसमयr after a gap, updating expiry.
 * @vcpu:	Virtual CPU.
 * @beक्रमe:	Time beक्रमe Count was saved, lower bound of drअगरt calculation.
 * @count:	CP0_Count at poपूर्णांक of restore.
 * @min_drअगरt:	Minimum amount of drअगरt permitted beक्रमe correction.
 *		Must be <= 0.
 *
 * Restores the समयr from a particular @count, accounting क्रम drअगरt. This can
 * be used in conjunction with kvm_mips_मुक्तze_समयr() when a hardware समयr is
 * to be used क्रम a period of समय, but the exact kसमय corresponding to the
 * final Count that must be restored is not known.
 *
 * It is gauranteed that a समयr पूर्णांकerrupt immediately after restore will be
 * handled, but not अगर CP0_Compare is exactly at @count. That हाल should
 * alपढ़ोy be handled when the hardware समयr state is saved.
 *
 * Assumes !kvm_mips_count_disabled(@vcpu) (guest CP0_Count समयr is not
 * stopped).
 *
 * Returns:	Amount of correction to count_bias due to drअगरt.
 */
पूर्णांक kvm_mips_restore_hrसमयr(काष्ठा kvm_vcpu *vcpu, kसमय_प्रकार beक्रमe,
			     u32 count, पूर्णांक min_drअगरt)
अणु
	kसमय_प्रकार now, count_समय;
	u32 now_count, beक्रमe_count;
	u64 delta;
	पूर्णांक drअगरt, ret = 0;

	/* Calculate expected count at beक्रमe */
	beक्रमe_count = vcpu->arch.count_bias +
			kvm_mips_kसमय_प्रकारo_count(vcpu, beक्रमe);

	/*
	 * Detect signअगरicantly negative drअगरt, where count is lower than
	 * expected. Some negative drअगरt is expected when hardware counter is
	 * set after kvm_mips_मुक्तze_समयr(), and it is harmless to allow the
	 * समय to jump क्रमwards a little, within reason. If the drअगरt is too
	 * signअगरicant, adjust the bias to aव्योम a big Guest.CP0_Count jump.
	 */
	drअगरt = count - beक्रमe_count;
	अगर (drअगरt < min_drअगरt) अणु
		count_समय = beक्रमe;
		vcpu->arch.count_bias += drअगरt;
		ret = drअगरt;
		जाओ resume;
	पूर्ण

	/* Calculate expected count right now */
	now = kसमय_get();
	now_count = vcpu->arch.count_bias + kvm_mips_kसमय_प्रकारo_count(vcpu, now);

	/*
	 * Detect positive drअगरt, where count is higher than expected, and
	 * adjust the bias to aव्योम guest समय going backwards.
	 */
	drअगरt = count - now_count;
	अगर (drअगरt > 0) अणु
		count_समय = now;
		vcpu->arch.count_bias += drअगरt;
		ret = drअगरt;
		जाओ resume;
	पूर्ण

	/* Subtract nanosecond delta to find kसमय when count was पढ़ो */
	delta = (u64)(u32)(now_count - count);
	delta = भाग_u64(delta * NSEC_PER_SEC, vcpu->arch.count_hz);
	count_समय = kसमय_sub_ns(now, delta);

resume:
	/* Resume using the calculated kसमय */
	kvm_mips_resume_hrसमयr(vcpu, count_समय, count);
	वापस ret;
पूर्ण

/**
 * kvm_mips_ग_लिखो_count() - Modअगरy the count and update समयr.
 * @vcpu:	Virtual CPU.
 * @count:	Guest CP0_Count value to set.
 *
 * Sets the CP0_Count value and updates the समयr accordingly.
 */
व्योम kvm_mips_ग_लिखो_count(काष्ठा kvm_vcpu *vcpu, u32 count)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	kसमय_प्रकार now;

	/* Calculate bias */
	now = kvm_mips_count_समय(vcpu);
	vcpu->arch.count_bias = count - kvm_mips_kसमय_प्रकारo_count(vcpu, now);

	अगर (kvm_mips_count_disabled(vcpu))
		/* The समयr's disabled, adjust the अटल count */
		kvm_ग_लिखो_c0_guest_count(cop0, count);
	अन्यथा
		/* Update समयout */
		kvm_mips_resume_hrसमयr(vcpu, now, count);
पूर्ण

/**
 * kvm_mips_init_count() - Initialise समयr.
 * @vcpu:	Virtual CPU.
 * @count_hz:	Frequency of समयr.
 *
 * Initialise the समयr to the specअगरied frequency, zero it, and set it going अगर
 * it's enabled.
 */
व्योम kvm_mips_init_count(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ count_hz)
अणु
	vcpu->arch.count_hz = count_hz;
	vcpu->arch.count_period = भाग_u64((u64)NSEC_PER_SEC << 32, count_hz);
	vcpu->arch.count_dyn_bias = 0;

	/* Starting at 0 */
	kvm_mips_ग_लिखो_count(vcpu, 0);
पूर्ण

/**
 * kvm_mips_set_count_hz() - Update the frequency of the समयr.
 * @vcpu:	Virtual CPU.
 * @count_hz:	Frequency of CP0_Count समयr in Hz.
 *
 * Change the frequency of the CP0_Count समयr. This is करोne atomically so that
 * CP0_Count is continuous and no समयr पूर्णांकerrupt is lost.
 *
 * Returns:	-EINVAL अगर @count_hz is out of range.
 *		0 on success.
 */
पूर्णांक kvm_mips_set_count_hz(काष्ठा kvm_vcpu *vcpu, s64 count_hz)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	पूर्णांक dc;
	kसमय_प्रकार now;
	u32 count;

	/* ensure the frequency is in a sensible range... */
	अगर (count_hz <= 0 || count_hz > NSEC_PER_SEC)
		वापस -EINVAL;
	/* ... and has actually changed */
	अगर (vcpu->arch.count_hz == count_hz)
		वापस 0;

	/* Safely मुक्तze समयr so we can keep it continuous */
	dc = kvm_mips_count_disabled(vcpu);
	अगर (dc) अणु
		now = kvm_mips_count_समय(vcpu);
		count = kvm_पढ़ो_c0_guest_count(cop0);
	पूर्ण अन्यथा अणु
		now = kvm_mips_मुक्तze_hrसमयr(vcpu, &count);
	पूर्ण

	/* Update the frequency */
	vcpu->arch.count_hz = count_hz;
	vcpu->arch.count_period = भाग_u64((u64)NSEC_PER_SEC << 32, count_hz);
	vcpu->arch.count_dyn_bias = 0;

	/* Calculate adjusted bias so dynamic count is unchanged */
	vcpu->arch.count_bias = count - kvm_mips_kसमय_प्रकारo_count(vcpu, now);

	/* Update and resume hrसमयr */
	अगर (!dc)
		kvm_mips_resume_hrसमयr(vcpu, now, count);
	वापस 0;
पूर्ण

/**
 * kvm_mips_ग_लिखो_compare() - Modअगरy compare and update समयr.
 * @vcpu:	Virtual CPU.
 * @compare:	New CP0_Compare value.
 * @ack:	Whether to acknowledge समयr पूर्णांकerrupt.
 *
 * Update CP0_Compare to a new value and update the समयout.
 * If @ack, atomically acknowledge any pending समयr पूर्णांकerrupt, otherwise ensure
 * any pending समयr पूर्णांकerrupt is preserved.
 */
व्योम kvm_mips_ग_लिखो_compare(काष्ठा kvm_vcpu *vcpu, u32 compare, bool ack)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	पूर्णांक dc;
	u32 old_compare = kvm_पढ़ो_c0_guest_compare(cop0);
	s32 delta = compare - old_compare;
	u32 cause;
	kसमय_प्रकार now = kसमय_set(0, 0); /* silence bogus GCC warning */
	u32 count;

	/* अगर unchanged, must just be an ack */
	अगर (old_compare == compare) अणु
		अगर (!ack)
			वापस;
		kvm_mips_callbacks->dequeue_समयr_पूर्णांक(vcpu);
		kvm_ग_लिखो_c0_guest_compare(cop0, compare);
		वापस;
	पूर्ण

	/*
	 * If guest CP0_Compare moves क्रमward, CP0_GTOffset should be adjusted
	 * too to prevent guest CP0_Count hitting guest CP0_Compare.
	 *
	 * The new GTOffset corresponds to the new value of CP0_Compare, and is
	 * set prior to it being written पूर्णांकo the guest context. We disable
	 * preemption until the new value is written to prevent restore of a
	 * GTOffset corresponding to the old CP0_Compare value.
	 */
	अगर (delta > 0) अणु
		preempt_disable();
		ग_लिखो_c0_gtoffset(compare - पढ़ो_c0_count());
		back_to_back_c0_hazard();
	पूर्ण

	/* मुक्तze_hrसमयr() takes care of समयr पूर्णांकerrupts <= count */
	dc = kvm_mips_count_disabled(vcpu);
	अगर (!dc)
		now = kvm_mips_मुक्तze_hrसमयr(vcpu, &count);

	अगर (ack)
		kvm_mips_callbacks->dequeue_समयr_पूर्णांक(vcpu);
	अन्यथा
		/*
		 * With VZ, writing CP0_Compare acks (clears) CP0_Cause.TI, so
		 * preserve guest CP0_Cause.TI अगर we करोn't want to ack it.
		 */
		cause = kvm_पढ़ो_c0_guest_cause(cop0);

	kvm_ग_लिखो_c0_guest_compare(cop0, compare);

	अगर (delta > 0)
		preempt_enable();

	back_to_back_c0_hazard();

	अगर (!ack && cause & CAUSEF_TI)
		kvm_ग_लिखो_c0_guest_cause(cop0, cause);

	/* resume_hrसमयr() takes care of समयr पूर्णांकerrupts > count */
	अगर (!dc)
		kvm_mips_resume_hrसमयr(vcpu, now, count);

	/*
	 * If guest CP0_Compare is moving backward, we delay CP0_GTOffset change
	 * until after the new CP0_Compare is written, otherwise new guest
	 * CP0_Count could hit new guest CP0_Compare.
	 */
	अगर (delta <= 0)
		ग_लिखो_c0_gtoffset(compare - पढ़ो_c0_count());
पूर्ण

/**
 * kvm_mips_count_disable() - Disable count.
 * @vcpu:	Virtual CPU.
 *
 * Disable the CP0_Count समयr. A समयr पूर्णांकerrupt on or beक्रमe the final stop
 * समय will be handled but not after.
 *
 * Assumes CP0_Count was previously enabled but now Guest.CP0_Cause.DC or
 * count_ctl.DC has been set (count disabled).
 *
 * Returns:	The समय that the समयr was stopped.
 */
अटल kसमय_प्रकार kvm_mips_count_disable(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	u32 count;
	kसमय_प्रकार now;

	/* Stop hrसमयr */
	hrसमयr_cancel(&vcpu->arch.comparecount_समयr);

	/* Set the अटल count from the dynamic count, handling pending TI */
	now = kसमय_get();
	count = kvm_mips_पढ़ो_count_running(vcpu, now);
	kvm_ग_लिखो_c0_guest_count(cop0, count);

	वापस now;
पूर्ण

/**
 * kvm_mips_count_disable_cause() - Disable count using CP0_Cause.DC.
 * @vcpu:	Virtual CPU.
 *
 * Disable the CP0_Count समयr and set CP0_Cause.DC. A समयr पूर्णांकerrupt on or
 * beक्रमe the final stop समय will be handled अगर the समयr isn't disabled by
 * count_ctl.DC, but not after.
 *
 * Assumes CP0_Cause.DC is clear (count enabled).
 */
व्योम kvm_mips_count_disable_cause(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;

	kvm_set_c0_guest_cause(cop0, CAUSEF_DC);
	अगर (!(vcpu->arch.count_ctl & KVM_REG_MIPS_COUNT_CTL_DC))
		kvm_mips_count_disable(vcpu);
पूर्ण

/**
 * kvm_mips_count_enable_cause() - Enable count using CP0_Cause.DC.
 * @vcpu:	Virtual CPU.
 *
 * Enable the CP0_Count समयr and clear CP0_Cause.DC. A समयr पूर्णांकerrupt after
 * the start समय will be handled अगर the समयr isn't disabled by count_ctl.DC,
 * potentially beक्रमe even वापसing, so the caller should be careful with
 * ordering of CP0_Cause modअगरications so as not to lose it.
 *
 * Assumes CP0_Cause.DC is set (count disabled).
 */
व्योम kvm_mips_count_enable_cause(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	u32 count;

	kvm_clear_c0_guest_cause(cop0, CAUSEF_DC);

	/*
	 * Set the dynamic count to match the अटल count.
	 * This starts the hrसमयr अगर count_ctl.DC allows it.
	 * Otherwise it conveniently updates the biases.
	 */
	count = kvm_पढ़ो_c0_guest_count(cop0);
	kvm_mips_ग_लिखो_count(vcpu, count);
पूर्ण

/**
 * kvm_mips_set_count_ctl() - Update the count control KVM रेजिस्टर.
 * @vcpu:	Virtual CPU.
 * @count_ctl:	Count control रेजिस्टर new value.
 *
 * Set the count control KVM रेजिस्टर. The समयr is updated accordingly.
 *
 * Returns:	-EINVAL अगर reserved bits are set.
 *		0 on success.
 */
पूर्णांक kvm_mips_set_count_ctl(काष्ठा kvm_vcpu *vcpu, s64 count_ctl)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	s64 changed = count_ctl ^ vcpu->arch.count_ctl;
	s64 delta;
	kसमय_प्रकार expire, now;
	u32 count, compare;

	/* Only allow defined bits to be changed */
	अगर (changed & ~(s64)(KVM_REG_MIPS_COUNT_CTL_DC))
		वापस -EINVAL;

	/* Apply new value */
	vcpu->arch.count_ctl = count_ctl;

	/* Master CP0_Count disable */
	अगर (changed & KVM_REG_MIPS_COUNT_CTL_DC) अणु
		/* Is CP0_Cause.DC alपढ़ोy disabling CP0_Count? */
		अगर (kvm_पढ़ो_c0_guest_cause(cop0) & CAUSEF_DC) अणु
			अगर (count_ctl & KVM_REG_MIPS_COUNT_CTL_DC)
				/* Just record the current समय */
				vcpu->arch.count_resume = kसमय_get();
		पूर्ण अन्यथा अगर (count_ctl & KVM_REG_MIPS_COUNT_CTL_DC) अणु
			/* disable समयr and record current समय */
			vcpu->arch.count_resume = kvm_mips_count_disable(vcpu);
		पूर्ण अन्यथा अणु
			/*
			 * Calculate समयout relative to अटल count at resume
			 * समय (wrap 0 to 2^32).
			 */
			count = kvm_पढ़ो_c0_guest_count(cop0);
			compare = kvm_पढ़ो_c0_guest_compare(cop0);
			delta = (u64)(u32)(compare - count - 1) + 1;
			delta = भाग_u64(delta * NSEC_PER_SEC,
					vcpu->arch.count_hz);
			expire = kसमय_add_ns(vcpu->arch.count_resume, delta);

			/* Handle pending पूर्णांकerrupt */
			now = kसमय_get();
			अगर (kसमय_compare(now, expire) >= 0)
				/* Nothing should be रुकोing on the समयout */
				kvm_mips_callbacks->queue_समयr_पूर्णांक(vcpu);

			/* Resume hrसमयr without changing bias */
			count = kvm_mips_पढ़ो_count_running(vcpu, now);
			kvm_mips_resume_hrसमयr(vcpu, now, count);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * kvm_mips_set_count_resume() - Update the count resume KVM रेजिस्टर.
 * @vcpu:		Virtual CPU.
 * @count_resume:	Count resume रेजिस्टर new value.
 *
 * Set the count resume KVM रेजिस्टर.
 *
 * Returns:	-EINVAL अगर out of valid range (0..now).
 *		0 on success.
 */
पूर्णांक kvm_mips_set_count_resume(काष्ठा kvm_vcpu *vcpu, s64 count_resume)
अणु
	/*
	 * It करोesn't make sense क्रम the resume समय to be in the future, as it
	 * would be possible क्रम the next पूर्णांकerrupt to be more than a full
	 * period in the future.
	 */
	अगर (count_resume < 0 || count_resume > kसमय_प्रकारo_ns(kसमय_get()))
		वापस -EINVAL;

	vcpu->arch.count_resume = ns_to_kसमय(count_resume);
	वापस 0;
पूर्ण

/**
 * kvm_mips_count_समयout() - Push समयr क्रमward on समयout.
 * @vcpu:	Virtual CPU.
 *
 * Handle an hrसमयr event by push the hrसमयr क्रमward a period.
 *
 * Returns:	The hrसमयr_restart value to वापस to the hrसमयr subप्रणाली.
 */
क्रमागत hrसमयr_restart kvm_mips_count_समयout(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Add the Count period to the current expiry समय */
	hrसमयr_add_expires_ns(&vcpu->arch.comparecount_समयr,
			       vcpu->arch.count_period);
	वापस HRTIMER_RESTART;
पूर्ण

क्रमागत emulation_result kvm_mips_emul_रुको(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_debug("[%#lx] !!!WAIT!!! (%#lx)\n", vcpu->arch.pc,
		  vcpu->arch.pending_exceptions);

	++vcpu->stat.रुको_निकासs;
	trace_kvm_निकास(vcpu, KVM_TRACE_EXIT_WAIT);
	अगर (!vcpu->arch.pending_exceptions) अणु
		kvm_vz_lose_hसमयr(vcpu);
		vcpu->arch.रुको = 1;
		kvm_vcpu_block(vcpu);

		/*
		 * We we are runnable, then definitely go off to user space to
		 * check अगर any I/O पूर्णांकerrupts are pending.
		 */
		अगर (kvm_check_request(KVM_REQ_UNHALT, vcpu)) अणु
			kvm_clear_request(KVM_REQ_UNHALT, vcpu);
			vcpu->run->निकास_reason = KVM_EXIT_IRQ_WINDOW_OPEN;
		पूर्ण
	पूर्ण

	वापस EMULATE_DONE;
पूर्ण

क्रमागत emulation_result kvm_mips_emulate_store(जोड़ mips_inकाष्ठाion inst,
					     u32 cause,
					     काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;
	क्रमागत emulation_result er;
	u32 rt;
	काष्ठा kvm_run *run = vcpu->run;
	व्योम *data = run->mmio.data;
	अचिन्हित पूर्णांक imme;
	अचिन्हित दीर्घ curr_pc;

	/*
	 * Update PC and hold onto current PC in हाल there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	अगर (er == EMULATE_FAIL)
		वापस er;

	rt = inst.i_क्रमmat.rt;

	run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
						vcpu->arch.host_cp0_badvaddr);
	अगर (run->mmio.phys_addr == KVM_INVALID_ADDR)
		जाओ out_fail;

	चयन (inst.i_क्रमmat.opcode) अणु
#अगर defined(CONFIG_64BIT)
	हाल sd_op:
		run->mmio.len = 8;
		*(u64 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SD: eaddr: %#lx, gpr: %#lx, data: %#llx\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u64 *)data);
		अवरोध;
#पूर्ण_अगर

	हाल sw_op:
		run->mmio.len = 4;
		*(u32 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SW: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u32 *)data);
		अवरोध;

	हाल sh_op:
		run->mmio.len = 2;
		*(u16 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SH: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u16 *)data);
		अवरोध;

	हाल sb_op:
		run->mmio.len = 1;
		*(u8 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SB: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u8 *)data);
		अवरोध;

	हाल swl_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x3);
		run->mmio.len = 4;
		imme = vcpu->arch.host_cp0_badvaddr & 0x3;
		चयन (imme) अणु
		हाल 0:
			*(u32 *)data = ((*(u32 *)data) & 0xffffff00) |
					(vcpu->arch.gprs[rt] >> 24);
			अवरोध;
		हाल 1:
			*(u32 *)data = ((*(u32 *)data) & 0xffff0000) |
					(vcpu->arch.gprs[rt] >> 16);
			अवरोध;
		हाल 2:
			*(u32 *)data = ((*(u32 *)data) & 0xff000000) |
					(vcpu->arch.gprs[rt] >> 8);
			अवरोध;
		हाल 3:
			*(u32 *)data = vcpu->arch.gprs[rt];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		kvm_debug("[%#lx] OP_SWL: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u32 *)data);
		अवरोध;

	हाल swr_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x3);
		run->mmio.len = 4;
		imme = vcpu->arch.host_cp0_badvaddr & 0x3;
		चयन (imme) अणु
		हाल 0:
			*(u32 *)data = vcpu->arch.gprs[rt];
			अवरोध;
		हाल 1:
			*(u32 *)data = ((*(u32 *)data) & 0xff) |
					(vcpu->arch.gprs[rt] << 8);
			अवरोध;
		हाल 2:
			*(u32 *)data = ((*(u32 *)data) & 0xffff) |
					(vcpu->arch.gprs[rt] << 16);
			अवरोध;
		हाल 3:
			*(u32 *)data = ((*(u32 *)data) & 0xffffff) |
					(vcpu->arch.gprs[rt] << 24);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		kvm_debug("[%#lx] OP_SWR: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u32 *)data);
		अवरोध;

#अगर defined(CONFIG_64BIT)
	हाल sdl_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x7);

		run->mmio.len = 8;
		imme = vcpu->arch.host_cp0_badvaddr & 0x7;
		चयन (imme) अणु
		हाल 0:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffffffffff00) |
					((vcpu->arch.gprs[rt] >> 56) & 0xff);
			अवरोध;
		हाल 1:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffffffff0000) |
					((vcpu->arch.gprs[rt] >> 48) & 0xffff);
			अवरोध;
		हाल 2:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffffff000000) |
					((vcpu->arch.gprs[rt] >> 40) & 0xffffff);
			अवरोध;
		हाल 3:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffff00000000) |
					((vcpu->arch.gprs[rt] >> 32) & 0xffffffff);
			अवरोध;
		हाल 4:
			*(u64 *)data = ((*(u64 *)data) & 0xffffff0000000000) |
					((vcpu->arch.gprs[rt] >> 24) & 0xffffffffff);
			अवरोध;
		हाल 5:
			*(u64 *)data = ((*(u64 *)data) & 0xffff000000000000) |
					((vcpu->arch.gprs[rt] >> 16) & 0xffffffffffff);
			अवरोध;
		हाल 6:
			*(u64 *)data = ((*(u64 *)data) & 0xff00000000000000) |
					((vcpu->arch.gprs[rt] >> 8) & 0xffffffffffffff);
			अवरोध;
		हाल 7:
			*(u64 *)data = vcpu->arch.gprs[rt];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		kvm_debug("[%#lx] OP_SDL: eaddr: %#lx, gpr: %#lx, data: %llx\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u64 *)data);
		अवरोध;

	हाल sdr_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x7);

		run->mmio.len = 8;
		imme = vcpu->arch.host_cp0_badvaddr & 0x7;
		चयन (imme) अणु
		हाल 0:
			*(u64 *)data = vcpu->arch.gprs[rt];
			अवरोध;
		हाल 1:
			*(u64 *)data = ((*(u64 *)data) & 0xff) |
					(vcpu->arch.gprs[rt] << 8);
			अवरोध;
		हाल 2:
			*(u64 *)data = ((*(u64 *)data) & 0xffff) |
					(vcpu->arch.gprs[rt] << 16);
			अवरोध;
		हाल 3:
			*(u64 *)data = ((*(u64 *)data) & 0xffffff) |
					(vcpu->arch.gprs[rt] << 24);
			अवरोध;
		हाल 4:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffff) |
					(vcpu->arch.gprs[rt] << 32);
			अवरोध;
		हाल 5:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffffff) |
					(vcpu->arch.gprs[rt] << 40);
			अवरोध;
		हाल 6:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffffffff) |
					(vcpu->arch.gprs[rt] << 48);
			अवरोध;
		हाल 7:
			*(u64 *)data = ((*(u64 *)data) & 0xffffffffffffff) |
					(vcpu->arch.gprs[rt] << 56);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		kvm_debug("[%#lx] OP_SDR: eaddr: %#lx, gpr: %#lx, data: %llx\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u64 *)data);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_LOONGSON64
	हाल sdc2_op:
		rt = inst.loongson3_lsdc2_क्रमmat.rt;
		चयन (inst.loongson3_lsdc2_क्रमmat.opcode1) अणु
		/*
		 * Loongson-3 overridden sdc2 inकाष्ठाions.
		 * opcode1              inकाष्ठाion
		 *   0x0          gssbx: store 1 bytes from GPR
		 *   0x1          gsshx: store 2 bytes from GPR
		 *   0x2          gsswx: store 4 bytes from GPR
		 *   0x3          gssdx: store 8 bytes from GPR
		 */
		हाल 0x0:
			run->mmio.len = 1;
			*(u8 *)data = vcpu->arch.gprs[rt];

			kvm_debug("[%#lx] OP_GSSBX: eaddr: %#lx, gpr: %#lx, data: %#x\n",
				  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
				  vcpu->arch.gprs[rt], *(u8 *)data);
			अवरोध;
		हाल 0x1:
			run->mmio.len = 2;
			*(u16 *)data = vcpu->arch.gprs[rt];

			kvm_debug("[%#lx] OP_GSSSHX: eaddr: %#lx, gpr: %#lx, data: %#x\n",
				  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
				  vcpu->arch.gprs[rt], *(u16 *)data);
			अवरोध;
		हाल 0x2:
			run->mmio.len = 4;
			*(u32 *)data = vcpu->arch.gprs[rt];

			kvm_debug("[%#lx] OP_GSSWX: eaddr: %#lx, gpr: %#lx, data: %#x\n",
				  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
				  vcpu->arch.gprs[rt], *(u32 *)data);
			अवरोध;
		हाल 0x3:
			run->mmio.len = 8;
			*(u64 *)data = vcpu->arch.gprs[rt];

			kvm_debug("[%#lx] OP_GSSDX: eaddr: %#lx, gpr: %#lx, data: %#llx\n",
				  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
				  vcpu->arch.gprs[rt], *(u64 *)data);
			अवरोध;
		शेष:
			kvm_err("Godson Extended GS-Store not yet supported (inst=0x%08x)\n",
				inst.word);
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		kvm_err("Store not yet supported (inst=0x%08x)\n",
			inst.word);
		जाओ out_fail;
	पूर्ण

	vcpu->mmio_needed = 1;
	run->mmio.is_ग_लिखो = 1;
	vcpu->mmio_is_ग_लिखो = 1;

	r = kvm_io_bus_ग_लिखो(vcpu, KVM_MMIO_BUS,
			run->mmio.phys_addr, run->mmio.len, data);

	अगर (!r) अणु
		vcpu->mmio_needed = 0;
		वापस EMULATE_DONE;
	पूर्ण

	वापस EMULATE_DO_MMIO;

out_fail:
	/* Rollback PC अगर emulation was unsuccessful */
	vcpu->arch.pc = curr_pc;
	वापस EMULATE_FAIL;
पूर्ण

क्रमागत emulation_result kvm_mips_emulate_load(जोड़ mips_inकाष्ठाion inst,
					    u32 cause, काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक r;
	क्रमागत emulation_result er;
	अचिन्हित दीर्घ curr_pc;
	u32 op, rt;
	अचिन्हित पूर्णांक imme;

	rt = inst.i_क्रमmat.rt;
	op = inst.i_क्रमmat.opcode;

	/*
	 * Find the resume PC now जबतक we have safe and easy access to the
	 * prior branch inकाष्ठाion, and save it क्रम
	 * kvm_mips_complete_mmio_load() to restore later.
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	अगर (er == EMULATE_FAIL)
		वापस er;
	vcpu->arch.io_pc = vcpu->arch.pc;
	vcpu->arch.pc = curr_pc;

	vcpu->arch.io_gpr = rt;

	run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
						vcpu->arch.host_cp0_badvaddr);
	अगर (run->mmio.phys_addr == KVM_INVALID_ADDR)
		वापस EMULATE_FAIL;

	vcpu->mmio_needed = 2;	/* चिन्हित */
	चयन (op) अणु
#अगर defined(CONFIG_64BIT)
	हाल ld_op:
		run->mmio.len = 8;
		अवरोध;

	हाल lwu_op:
		vcpu->mmio_needed = 1;	/* अचिन्हित */
		fallthrough;
#पूर्ण_अगर
	हाल lw_op:
		run->mmio.len = 4;
		अवरोध;

	हाल lhu_op:
		vcpu->mmio_needed = 1;	/* अचिन्हित */
		fallthrough;
	हाल lh_op:
		run->mmio.len = 2;
		अवरोध;

	हाल lbu_op:
		vcpu->mmio_needed = 1;	/* अचिन्हित */
		fallthrough;
	हाल lb_op:
		run->mmio.len = 1;
		अवरोध;

	हाल lwl_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x3);

		run->mmio.len = 4;
		imme = vcpu->arch.host_cp0_badvaddr & 0x3;
		चयन (imme) अणु
		हाल 0:
			vcpu->mmio_needed = 3;	/* 1 byte */
			अवरोध;
		हाल 1:
			vcpu->mmio_needed = 4;	/* 2 bytes */
			अवरोध;
		हाल 2:
			vcpu->mmio_needed = 5;	/* 3 bytes */
			अवरोध;
		हाल 3:
			vcpu->mmio_needed = 6;	/* 4 bytes */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल lwr_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x3);

		run->mmio.len = 4;
		imme = vcpu->arch.host_cp0_badvaddr & 0x3;
		चयन (imme) अणु
		हाल 0:
			vcpu->mmio_needed = 7;	/* 4 bytes */
			अवरोध;
		हाल 1:
			vcpu->mmio_needed = 8;	/* 3 bytes */
			अवरोध;
		हाल 2:
			vcpu->mmio_needed = 9;	/* 2 bytes */
			अवरोध;
		हाल 3:
			vcpu->mmio_needed = 10;	/* 1 byte */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

#अगर defined(CONFIG_64BIT)
	हाल ldl_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x7);

		run->mmio.len = 8;
		imme = vcpu->arch.host_cp0_badvaddr & 0x7;
		चयन (imme) अणु
		हाल 0:
			vcpu->mmio_needed = 11;	/* 1 byte */
			अवरोध;
		हाल 1:
			vcpu->mmio_needed = 12;	/* 2 bytes */
			अवरोध;
		हाल 2:
			vcpu->mmio_needed = 13;	/* 3 bytes */
			अवरोध;
		हाल 3:
			vcpu->mmio_needed = 14;	/* 4 bytes */
			अवरोध;
		हाल 4:
			vcpu->mmio_needed = 15;	/* 5 bytes */
			अवरोध;
		हाल 5:
			vcpu->mmio_needed = 16;	/* 6 bytes */
			अवरोध;
		हाल 6:
			vcpu->mmio_needed = 17;	/* 7 bytes */
			अवरोध;
		हाल 7:
			vcpu->mmio_needed = 18;	/* 8 bytes */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ldr_op:
		run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
					vcpu->arch.host_cp0_badvaddr) & (~0x7);

		run->mmio.len = 8;
		imme = vcpu->arch.host_cp0_badvaddr & 0x7;
		चयन (imme) अणु
		हाल 0:
			vcpu->mmio_needed = 19;	/* 8 bytes */
			अवरोध;
		हाल 1:
			vcpu->mmio_needed = 20;	/* 7 bytes */
			अवरोध;
		हाल 2:
			vcpu->mmio_needed = 21;	/* 6 bytes */
			अवरोध;
		हाल 3:
			vcpu->mmio_needed = 22;	/* 5 bytes */
			अवरोध;
		हाल 4:
			vcpu->mmio_needed = 23;	/* 4 bytes */
			अवरोध;
		हाल 5:
			vcpu->mmio_needed = 24;	/* 3 bytes */
			अवरोध;
		हाल 6:
			vcpu->mmio_needed = 25;	/* 2 bytes */
			अवरोध;
		हाल 7:
			vcpu->mmio_needed = 26;	/* 1 byte */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_LOONGSON64
	हाल ldc2_op:
		rt = inst.loongson3_lsdc2_क्रमmat.rt;
		चयन (inst.loongson3_lsdc2_क्रमmat.opcode1) अणु
		/*
		 * Loongson-3 overridden ldc2 inकाष्ठाions.
		 * opcode1              inकाष्ठाion
		 *   0x0          gslbx: store 1 bytes from GPR
		 *   0x1          gslhx: store 2 bytes from GPR
		 *   0x2          gslwx: store 4 bytes from GPR
		 *   0x3          gsldx: store 8 bytes from GPR
		 */
		हाल 0x0:
			run->mmio.len = 1;
			vcpu->mmio_needed = 27;	/* चिन्हित */
			अवरोध;
		हाल 0x1:
			run->mmio.len = 2;
			vcpu->mmio_needed = 28;	/* चिन्हित */
			अवरोध;
		हाल 0x2:
			run->mmio.len = 4;
			vcpu->mmio_needed = 29;	/* चिन्हित */
			अवरोध;
		हाल 0x3:
			run->mmio.len = 8;
			vcpu->mmio_needed = 30;	/* चिन्हित */
			अवरोध;
		शेष:
			kvm_err("Godson Extended GS-Load for float not yet supported (inst=0x%08x)\n",
				inst.word);
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	शेष:
		kvm_err("Load not yet supported (inst=0x%08x)\n",
			inst.word);
		vcpu->mmio_needed = 0;
		वापस EMULATE_FAIL;
	पूर्ण

	run->mmio.is_ग_लिखो = 0;
	vcpu->mmio_is_ग_लिखो = 0;

	r = kvm_io_bus_पढ़ो(vcpu, KVM_MMIO_BUS,
			run->mmio.phys_addr, run->mmio.len, run->mmio.data);

	अगर (!r) अणु
		kvm_mips_complete_mmio_load(vcpu);
		vcpu->mmio_needed = 0;
		वापस EMULATE_DONE;
	पूर्ण

	वापस EMULATE_DO_MMIO;
पूर्ण

क्रमागत emulation_result kvm_mips_complete_mmio_load(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	अचिन्हित दीर्घ *gpr = &vcpu->arch.gprs[vcpu->arch.io_gpr];
	क्रमागत emulation_result er = EMULATE_DONE;

	अगर (run->mmio.len > माप(*gpr)) अणु
		kvm_err("Bad MMIO length: %d", run->mmio.len);
		er = EMULATE_FAIL;
		जाओ करोne;
	पूर्ण

	/* Restore saved resume PC */
	vcpu->arch.pc = vcpu->arch.io_pc;

	चयन (run->mmio.len) अणु
	हाल 8:
		चयन (vcpu->mmio_needed) अणु
		हाल 11:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffffffffff) |
				(((*(s64 *)run->mmio.data) & 0xff) << 56);
			अवरोध;
		हाल 12:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffffffff) |
				(((*(s64 *)run->mmio.data) & 0xffff) << 48);
			अवरोध;
		हाल 13:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffffff) |
				(((*(s64 *)run->mmio.data) & 0xffffff) << 40);
			अवरोध;
		हाल 14:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffff) |
				(((*(s64 *)run->mmio.data) & 0xffffffff) << 32);
			अवरोध;
		हाल 15:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffff) |
				(((*(s64 *)run->mmio.data) & 0xffffffffff) << 24);
			अवरोध;
		हाल 16:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffff) |
				(((*(s64 *)run->mmio.data) & 0xffffffffffff) << 16);
			अवरोध;
		हाल 17:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xff) |
				(((*(s64 *)run->mmio.data) & 0xffffffffffffff) << 8);
			अवरोध;
		हाल 18:
		हाल 19:
			*gpr = *(s64 *)run->mmio.data;
			अवरोध;
		हाल 20:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xff00000000000000) |
				((((*(s64 *)run->mmio.data)) >> 8) & 0xffffffffffffff);
			अवरोध;
		हाल 21:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffff000000000000) |
				((((*(s64 *)run->mmio.data)) >> 16) & 0xffffffffffff);
			अवरोध;
		हाल 22:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffff0000000000) |
				((((*(s64 *)run->mmio.data)) >> 24) & 0xffffffffff);
			अवरोध;
		हाल 23:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffff00000000) |
				((((*(s64 *)run->mmio.data)) >> 32) & 0xffffffff);
			अवरोध;
		हाल 24:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffffff000000) |
				((((*(s64 *)run->mmio.data)) >> 40) & 0xffffff);
			अवरोध;
		हाल 25:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffffffff0000) |
				((((*(s64 *)run->mmio.data)) >> 48) & 0xffff);
			अवरोध;
		हाल 26:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffffffffffff00) |
				((((*(s64 *)run->mmio.data)) >> 56) & 0xff);
			अवरोध;
		शेष:
			*gpr = *(s64 *)run->mmio.data;
		पूर्ण
		अवरोध;

	हाल 4:
		चयन (vcpu->mmio_needed) अणु
		हाल 1:
			*gpr = *(u32 *)run->mmio.data;
			अवरोध;
		हाल 2:
			*gpr = *(s32 *)run->mmio.data;
			अवरोध;
		हाल 3:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffff) |
				(((*(s32 *)run->mmio.data) & 0xff) << 24);
			अवरोध;
		हाल 4:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffff) |
				(((*(s32 *)run->mmio.data) & 0xffff) << 16);
			अवरोध;
		हाल 5:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xff) |
				(((*(s32 *)run->mmio.data) & 0xffffff) << 8);
			अवरोध;
		हाल 6:
		हाल 7:
			*gpr = *(s32 *)run->mmio.data;
			अवरोध;
		हाल 8:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xff000000) |
				((((*(s32 *)run->mmio.data)) >> 8) & 0xffffff);
			अवरोध;
		हाल 9:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffff0000) |
				((((*(s32 *)run->mmio.data)) >> 16) & 0xffff);
			अवरोध;
		हाल 10:
			*gpr = (vcpu->arch.gprs[vcpu->arch.io_gpr] & 0xffffff00) |
				((((*(s32 *)run->mmio.data)) >> 24) & 0xff);
			अवरोध;
		शेष:
			*gpr = *(s32 *)run->mmio.data;
		पूर्ण
		अवरोध;

	हाल 2:
		अगर (vcpu->mmio_needed == 1)
			*gpr = *(u16 *)run->mmio.data;
		अन्यथा
			*gpr = *(s16 *)run->mmio.data;

		अवरोध;
	हाल 1:
		अगर (vcpu->mmio_needed == 1)
			*gpr = *(u8 *)run->mmio.data;
		अन्यथा
			*gpr = *(s8 *)run->mmio.data;
		अवरोध;
	पूर्ण

करोne:
	वापस er;
पूर्ण
