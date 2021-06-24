<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/uaccess.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>
#समावेश <यंत्र/arch_समयr.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>

#समावेश <kvm/arm_vgic.h>
#समावेश <kvm/arm_arch_समयr.h>

#समावेश "trace.h"

अटल काष्ठा समयcounter *समयcounter;
अटल अचिन्हित पूर्णांक host_vसमयr_irq;
अटल अचिन्हित पूर्णांक host_pसमयr_irq;
अटल u32 host_vसमयr_irq_flags;
अटल u32 host_pसमयr_irq_flags;

अटल DEFINE_STATIC_KEY_FALSE(has_gic_active_state);

अटल स्थिर काष्ठा kvm_irq_level शेष_pसमयr_irq = अणु
	.irq	= 30,
	.level	= 1,
पूर्ण;

अटल स्थिर काष्ठा kvm_irq_level शेष_vसमयr_irq = अणु
	.irq	= 27,
	.level	= 1,
पूर्ण;

अटल bool kvm_समयr_irq_can_fire(काष्ठा arch_समयr_context *समयr_ctx);
अटल व्योम kvm_समयr_update_irq(काष्ठा kvm_vcpu *vcpu, bool new_level,
				 काष्ठा arch_समयr_context *समयr_ctx);
अटल bool kvm_समयr_should_fire(काष्ठा arch_समयr_context *समयr_ctx);
अटल व्योम kvm_arm_समयr_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				काष्ठा arch_समयr_context *समयr,
				क्रमागत kvm_arch_समयr_regs treg,
				u64 val);
अटल u64 kvm_arm_समयr_पढ़ो(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा arch_समयr_context *समयr,
			      क्रमागत kvm_arch_समयr_regs treg);

u32 समयr_get_ctl(काष्ठा arch_समयr_context *ctxt)
अणु
	काष्ठा kvm_vcpu *vcpu = ctxt->vcpu;

	चयन(arch_समयr_ctx_index(ctxt)) अणु
	हाल TIMER_VTIMER:
		वापस __vcpu_sys_reg(vcpu, CNTV_CTL_EL0);
	हाल TIMER_PTIMER:
		वापस __vcpu_sys_reg(vcpu, CNTP_CTL_EL0);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

u64 समयr_get_cval(काष्ठा arch_समयr_context *ctxt)
अणु
	काष्ठा kvm_vcpu *vcpu = ctxt->vcpu;

	चयन(arch_समयr_ctx_index(ctxt)) अणु
	हाल TIMER_VTIMER:
		वापस __vcpu_sys_reg(vcpu, CNTV_CVAL_EL0);
	हाल TIMER_PTIMER:
		वापस __vcpu_sys_reg(vcpu, CNTP_CVAL_EL0);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल u64 समयr_get_offset(काष्ठा arch_समयr_context *ctxt)
अणु
	काष्ठा kvm_vcpu *vcpu = ctxt->vcpu;

	चयन(arch_समयr_ctx_index(ctxt)) अणु
	हाल TIMER_VTIMER:
		वापस __vcpu_sys_reg(vcpu, CNTVOFF_EL2);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम समयr_set_ctl(काष्ठा arch_समयr_context *ctxt, u32 ctl)
अणु
	काष्ठा kvm_vcpu *vcpu = ctxt->vcpu;

	चयन(arch_समयr_ctx_index(ctxt)) अणु
	हाल TIMER_VTIMER:
		__vcpu_sys_reg(vcpu, CNTV_CTL_EL0) = ctl;
		अवरोध;
	हाल TIMER_PTIMER:
		__vcpu_sys_reg(vcpu, CNTP_CTL_EL0) = ctl;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम समयr_set_cval(काष्ठा arch_समयr_context *ctxt, u64 cval)
अणु
	काष्ठा kvm_vcpu *vcpu = ctxt->vcpu;

	चयन(arch_समयr_ctx_index(ctxt)) अणु
	हाल TIMER_VTIMER:
		__vcpu_sys_reg(vcpu, CNTV_CVAL_EL0) = cval;
		अवरोध;
	हाल TIMER_PTIMER:
		__vcpu_sys_reg(vcpu, CNTP_CVAL_EL0) = cval;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम समयr_set_offset(काष्ठा arch_समयr_context *ctxt, u64 offset)
अणु
	काष्ठा kvm_vcpu *vcpu = ctxt->vcpu;

	चयन(arch_समयr_ctx_index(ctxt)) अणु
	हाल TIMER_VTIMER:
		__vcpu_sys_reg(vcpu, CNTVOFF_EL2) = offset;
		अवरोध;
	शेष:
		WARN(offset, "timer %ld\n", arch_समयr_ctx_index(ctxt));
	पूर्ण
पूर्ण

u64 kvm_phys_समयr_पढ़ो(व्योम)
अणु
	वापस समयcounter->cc->पढ़ो(समयcounter->cc);
पूर्ण

अटल व्योम get_समयr_map(काष्ठा kvm_vcpu *vcpu, काष्ठा समयr_map *map)
अणु
	अगर (has_vhe()) अणु
		map->direct_vसमयr = vcpu_vसमयr(vcpu);
		map->direct_pसमयr = vcpu_pसमयr(vcpu);
		map->emul_pसमयr = शून्य;
	पूर्ण अन्यथा अणु
		map->direct_vसमयr = vcpu_vसमयr(vcpu);
		map->direct_pसमयr = शून्य;
		map->emul_pसमयr = vcpu_pसमयr(vcpu);
	पूर्ण

	trace_kvm_get_समयr_map(vcpu->vcpu_id, map);
पूर्ण

अटल अंतरभूत bool userspace_irqchip(काष्ठा kvm *kvm)
अणु
	वापस अटल_branch_unlikely(&userspace_irqchip_in_use) &&
		unlikely(!irqchip_in_kernel(kvm));
पूर्ण

अटल व्योम soft_समयr_start(काष्ठा hrसमयr *hrt, u64 ns)
अणु
	hrसमयr_start(hrt, kसमय_add_ns(kसमय_get(), ns),
		      HRTIMER_MODE_ABS_HARD);
पूर्ण

अटल व्योम soft_समयr_cancel(काष्ठा hrसमयr *hrt)
अणु
	hrसमयr_cancel(hrt);
पूर्ण

अटल irqवापस_t kvm_arch_समयr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा kvm_vcpu *vcpu = *(काष्ठा kvm_vcpu **)dev_id;
	काष्ठा arch_समयr_context *ctx;
	काष्ठा समयr_map map;

	/*
	 * We may see a समयr पूर्णांकerrupt after vcpu_put() has been called which
	 * sets the CPU's vcpu poपूर्णांकer to शून्य, because even though the समयr
	 * has been disabled in समयr_save_state(), the hardware पूर्णांकerrupt
	 * संकेत may not have been retired from the पूर्णांकerrupt controller yet.
	 */
	अगर (!vcpu)
		वापस IRQ_HANDLED;

	get_समयr_map(vcpu, &map);

	अगर (irq == host_vसमयr_irq)
		ctx = map.direct_vसमयr;
	अन्यथा
		ctx = map.direct_pसमयr;

	अगर (kvm_समयr_should_fire(ctx))
		kvm_समयr_update_irq(vcpu, true, ctx);

	अगर (userspace_irqchip(vcpu->kvm) &&
	    !अटल_branch_unlikely(&has_gic_active_state))
		disable_percpu_irq(host_vसमयr_irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल u64 kvm_समयr_compute_delta(काष्ठा arch_समयr_context *समयr_ctx)
अणु
	u64 cval, now;

	cval = समयr_get_cval(समयr_ctx);
	now = kvm_phys_समयr_पढ़ो() - समयr_get_offset(समयr_ctx);

	अगर (now < cval) अणु
		u64 ns;

		ns = cyclecounter_cyc2ns(समयcounter->cc,
					 cval - now,
					 समयcounter->mask,
					 &समयcounter->frac);
		वापस ns;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool kvm_समयr_irq_can_fire(काष्ठा arch_समयr_context *समयr_ctx)
अणु
	WARN_ON(समयr_ctx && समयr_ctx->loaded);
	वापस समयr_ctx &&
		((समयr_get_ctl(समयr_ctx) &
		  (ARCH_TIMER_CTRL_IT_MASK | ARCH_TIMER_CTRL_ENABLE)) == ARCH_TIMER_CTRL_ENABLE);
पूर्ण

/*
 * Returns the earliest expiration समय in ns among guest समयrs.
 * Note that it will वापस 0 अगर none of समयrs can fire.
 */
अटल u64 kvm_समयr_earliest_exp(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 min_delta = ULदीर्घ_उच्च;
	पूर्णांक i;

	क्रम (i = 0; i < NR_KVM_TIMERS; i++) अणु
		काष्ठा arch_समयr_context *ctx = &vcpu->arch.समयr_cpu.समयrs[i];

		WARN(ctx->loaded, "timer %d loaded\n", i);
		अगर (kvm_समयr_irq_can_fire(ctx))
			min_delta = min(min_delta, kvm_समयr_compute_delta(ctx));
	पूर्ण

	/* If none of समयrs can fire, then वापस 0 */
	अगर (min_delta == ULदीर्घ_उच्च)
		वापस 0;

	वापस min_delta;
पूर्ण

अटल क्रमागत hrसमयr_restart kvm_bg_समयr_expire(काष्ठा hrसमयr *hrt)
अणु
	काष्ठा arch_समयr_cpu *समयr;
	काष्ठा kvm_vcpu *vcpu;
	u64 ns;

	समयr = container_of(hrt, काष्ठा arch_समयr_cpu, bg_समयr);
	vcpu = container_of(समयr, काष्ठा kvm_vcpu, arch.समयr_cpu);

	/*
	 * Check that the समयr has really expired from the guest's
	 * PoV (NTP on the host may have क्रमced it to expire
	 * early). If we should have slept दीर्घer, restart it.
	 */
	ns = kvm_समयr_earliest_exp(vcpu);
	अगर (unlikely(ns)) अणु
		hrसमयr_क्रमward_now(hrt, ns_to_kसमय(ns));
		वापस HRTIMER_RESTART;
	पूर्ण

	kvm_vcpu_wake_up(vcpu);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल क्रमागत hrसमयr_restart kvm_hrसमयr_expire(काष्ठा hrसमयr *hrt)
अणु
	काष्ठा arch_समयr_context *ctx;
	काष्ठा kvm_vcpu *vcpu;
	u64 ns;

	ctx = container_of(hrt, काष्ठा arch_समयr_context, hrसमयr);
	vcpu = ctx->vcpu;

	trace_kvm_समयr_hrसमयr_expire(ctx);

	/*
	 * Check that the समयr has really expired from the guest's
	 * PoV (NTP on the host may have क्रमced it to expire
	 * early). If not पढ़ोy, schedule क्रम a later समय.
	 */
	ns = kvm_समयr_compute_delta(ctx);
	अगर (unlikely(ns)) अणु
		hrसमयr_क्रमward_now(hrt, ns_to_kसमय(ns));
		वापस HRTIMER_RESTART;
	पूर्ण

	kvm_समयr_update_irq(vcpu, true, ctx);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल bool kvm_समयr_should_fire(काष्ठा arch_समयr_context *समयr_ctx)
अणु
	क्रमागत kvm_arch_समयrs index;
	u64 cval, now;

	अगर (!समयr_ctx)
		वापस false;

	index = arch_समयr_ctx_index(समयr_ctx);

	अगर (समयr_ctx->loaded) अणु
		u32 cnt_ctl = 0;

		चयन (index) अणु
		हाल TIMER_VTIMER:
			cnt_ctl = पढ़ो_sysreg_el0(SYS_CNTV_CTL);
			अवरोध;
		हाल TIMER_PTIMER:
			cnt_ctl = पढ़ो_sysreg_el0(SYS_CNTP_CTL);
			अवरोध;
		हाल NR_KVM_TIMERS:
			/* GCC is braindead */
			cnt_ctl = 0;
			अवरोध;
		पूर्ण

		वापस  (cnt_ctl & ARCH_TIMER_CTRL_ENABLE) &&
		        (cnt_ctl & ARCH_TIMER_CTRL_IT_STAT) &&
		       !(cnt_ctl & ARCH_TIMER_CTRL_IT_MASK);
	पूर्ण

	अगर (!kvm_समयr_irq_can_fire(समयr_ctx))
		वापस false;

	cval = समयr_get_cval(समयr_ctx);
	now = kvm_phys_समयr_पढ़ो() - समयr_get_offset(समयr_ctx);

	वापस cval <= now;
पूर्ण

bool kvm_समयr_is_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा समयr_map map;

	get_समयr_map(vcpu, &map);

	वापस kvm_समयr_should_fire(map.direct_vसमयr) ||
	       kvm_समयr_should_fire(map.direct_pसमयr) ||
	       kvm_समयr_should_fire(map.emul_pसमयr);
पूर्ण

/*
 * Reflect the समयr output level पूर्णांकo the kvm_run काष्ठाure
 */
व्योम kvm_समयr_update_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_context *vसमयr = vcpu_vसमयr(vcpu);
	काष्ठा arch_समयr_context *pसमयr = vcpu_pसमयr(vcpu);
	काष्ठा kvm_sync_regs *regs = &vcpu->run->s.regs;

	/* Populate the device biपंचांगap with the समयr states */
	regs->device_irq_level &= ~(KVM_ARM_DEV_EL1_VTIMER |
				    KVM_ARM_DEV_EL1_PTIMER);
	अगर (kvm_समयr_should_fire(vसमयr))
		regs->device_irq_level |= KVM_ARM_DEV_EL1_VTIMER;
	अगर (kvm_समयr_should_fire(pसमयr))
		regs->device_irq_level |= KVM_ARM_DEV_EL1_PTIMER;
पूर्ण

अटल व्योम kvm_समयr_update_irq(काष्ठा kvm_vcpu *vcpu, bool new_level,
				 काष्ठा arch_समयr_context *समयr_ctx)
अणु
	पूर्णांक ret;

	समयr_ctx->irq.level = new_level;
	trace_kvm_समयr_update_irq(vcpu->vcpu_id, समयr_ctx->irq.irq,
				   समयr_ctx->irq.level);

	अगर (!userspace_irqchip(vcpu->kvm)) अणु
		ret = kvm_vgic_inject_irq(vcpu->kvm, vcpu->vcpu_id,
					  समयr_ctx->irq.irq,
					  समयr_ctx->irq.level,
					  समयr_ctx);
		WARN_ON(ret);
	पूर्ण
पूर्ण

/* Only called क्रम a fully emulated समयr */
अटल व्योम समयr_emulate(काष्ठा arch_समयr_context *ctx)
अणु
	bool should_fire = kvm_समयr_should_fire(ctx);

	trace_kvm_समयr_emulate(ctx, should_fire);

	अगर (should_fire != ctx->irq.level) अणु
		kvm_समयr_update_irq(ctx->vcpu, should_fire, ctx);
		वापस;
	पूर्ण

	/*
	 * If the समयr can fire now, we करोn't need to have a soft समयr
	 * scheduled क्रम the future.  If the समयr cannot fire at all,
	 * then we also करोn't need a soft समयr.
	 */
	अगर (!kvm_समयr_irq_can_fire(ctx)) अणु
		soft_समयr_cancel(&ctx->hrसमयr);
		वापस;
	पूर्ण

	soft_समयr_start(&ctx->hrसमयr, kvm_समयr_compute_delta(ctx));
पूर्ण

अटल व्योम समयr_save_state(काष्ठा arch_समयr_context *ctx)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(ctx->vcpu);
	क्रमागत kvm_arch_समयrs index = arch_समयr_ctx_index(ctx);
	अचिन्हित दीर्घ flags;

	अगर (!समयr->enabled)
		वापस;

	local_irq_save(flags);

	अगर (!ctx->loaded)
		जाओ out;

	चयन (index) अणु
	हाल TIMER_VTIMER:
		समयr_set_ctl(ctx, पढ़ो_sysreg_el0(SYS_CNTV_CTL));
		समयr_set_cval(ctx, पढ़ो_sysreg_el0(SYS_CNTV_CVAL));

		/* Disable the समयr */
		ग_लिखो_sysreg_el0(0, SYS_CNTV_CTL);
		isb();

		अवरोध;
	हाल TIMER_PTIMER:
		समयr_set_ctl(ctx, पढ़ो_sysreg_el0(SYS_CNTP_CTL));
		समयr_set_cval(ctx, पढ़ो_sysreg_el0(SYS_CNTP_CVAL));

		/* Disable the समयr */
		ग_लिखो_sysreg_el0(0, SYS_CNTP_CTL);
		isb();

		अवरोध;
	हाल NR_KVM_TIMERS:
		BUG();
	पूर्ण

	trace_kvm_समयr_save_state(ctx);

	ctx->loaded = false;
out:
	local_irq_restore(flags);
पूर्ण

/*
 * Schedule the background समयr beक्रमe calling kvm_vcpu_block, so that this
 * thपढ़ो is हटाओd from its रुकोqueue and made runnable when there's a समयr
 * पूर्णांकerrupt to handle.
 */
अटल व्योम kvm_समयr_blocking(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);
	काष्ठा समयr_map map;

	get_समयr_map(vcpu, &map);

	/*
	 * If no समयrs are capable of raising पूर्णांकerrupts (disabled or
	 * masked), then there's no more work क्रम us to करो.
	 */
	अगर (!kvm_समयr_irq_can_fire(map.direct_vसमयr) &&
	    !kvm_समयr_irq_can_fire(map.direct_pसमयr) &&
	    !kvm_समयr_irq_can_fire(map.emul_pसमयr))
		वापस;

	/*
	 * At least one guest समय will expire. Schedule a background समयr.
	 * Set the earliest expiration समय among the guest समयrs.
	 */
	soft_समयr_start(&समयr->bg_समयr, kvm_समयr_earliest_exp(vcpu));
पूर्ण

अटल व्योम kvm_समयr_unblocking(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);

	soft_समयr_cancel(&समयr->bg_समयr);
पूर्ण

अटल व्योम समयr_restore_state(काष्ठा arch_समयr_context *ctx)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(ctx->vcpu);
	क्रमागत kvm_arch_समयrs index = arch_समयr_ctx_index(ctx);
	अचिन्हित दीर्घ flags;

	अगर (!समयr->enabled)
		वापस;

	local_irq_save(flags);

	अगर (ctx->loaded)
		जाओ out;

	चयन (index) अणु
	हाल TIMER_VTIMER:
		ग_लिखो_sysreg_el0(समयr_get_cval(ctx), SYS_CNTV_CVAL);
		isb();
		ग_लिखो_sysreg_el0(समयr_get_ctl(ctx), SYS_CNTV_CTL);
		अवरोध;
	हाल TIMER_PTIMER:
		ग_लिखो_sysreg_el0(समयr_get_cval(ctx), SYS_CNTP_CVAL);
		isb();
		ग_लिखो_sysreg_el0(समयr_get_ctl(ctx), SYS_CNTP_CTL);
		अवरोध;
	हाल NR_KVM_TIMERS:
		BUG();
	पूर्ण

	trace_kvm_समयr_restore_state(ctx);

	ctx->loaded = true;
out:
	local_irq_restore(flags);
पूर्ण

अटल व्योम set_cntvoff(u64 cntvoff)
अणु
	kvm_call_hyp(__kvm_समयr_set_cntvoff, cntvoff);
पूर्ण

अटल अंतरभूत व्योम set_समयr_irq_phys_active(काष्ठा arch_समयr_context *ctx, bool active)
अणु
	पूर्णांक r;
	r = irq_set_irqchip_state(ctx->host_समयr_irq, IRQCHIP_STATE_ACTIVE, active);
	WARN_ON(r);
पूर्ण

अटल व्योम kvm_समयr_vcpu_load_gic(काष्ठा arch_समयr_context *ctx)
अणु
	काष्ठा kvm_vcpu *vcpu = ctx->vcpu;
	bool phys_active = false;

	/*
	 * Update the समयr output so that it is likely to match the
	 * state we're about to restore. If the समयr expires between
	 * this poपूर्णांक and the रेजिस्टर restoration, we'll take the
	 * पूर्णांकerrupt anyway.
	 */
	kvm_समयr_update_irq(ctx->vcpu, kvm_समयr_should_fire(ctx), ctx);

	अगर (irqchip_in_kernel(vcpu->kvm))
		phys_active = kvm_vgic_map_is_active(vcpu, ctx->irq.irq);

	phys_active |= ctx->irq.level;

	set_समयr_irq_phys_active(ctx, phys_active);
पूर्ण

अटल व्योम kvm_समयr_vcpu_load_nogic(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_context *vसमयr = vcpu_vसमयr(vcpu);

	/*
	 * Update the समयr output so that it is likely to match the
	 * state we're about to restore. If the समयr expires between
	 * this poपूर्णांक and the रेजिस्टर restoration, we'll take the
	 * पूर्णांकerrupt anyway.
	 */
	kvm_समयr_update_irq(vcpu, kvm_समयr_should_fire(vसमयr), vसमयr);

	/*
	 * When using a userspace irqchip with the architected समयrs and a
	 * host पूर्णांकerrupt controller that करोesn't support an active state, we
	 * must still prevent continuously निकासing from the guest, and
	 * thereक्रमe mask the physical पूर्णांकerrupt by disabling it on the host
	 * पूर्णांकerrupt controller when the भव level is high, such that the
	 * guest can make क्रमward progress.  Once we detect the output level
	 * being de-निश्चितed, we unmask the पूर्णांकerrupt again so that we निकास
	 * from the guest when the समयr fires.
	 */
	अगर (vसमयr->irq.level)
		disable_percpu_irq(host_vसमयr_irq);
	अन्यथा
		enable_percpu_irq(host_vसमयr_irq, host_vसमयr_irq_flags);
पूर्ण

व्योम kvm_समयr_vcpu_load(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);
	काष्ठा समयr_map map;

	अगर (unlikely(!समयr->enabled))
		वापस;

	get_समयr_map(vcpu, &map);

	अगर (अटल_branch_likely(&has_gic_active_state)) अणु
		kvm_समयr_vcpu_load_gic(map.direct_vसमयr);
		अगर (map.direct_pसमयr)
			kvm_समयr_vcpu_load_gic(map.direct_pसमयr);
	पूर्ण अन्यथा अणु
		kvm_समयr_vcpu_load_nogic(vcpu);
	पूर्ण

	set_cntvoff(समयr_get_offset(map.direct_vसमयr));

	kvm_समयr_unblocking(vcpu);

	समयr_restore_state(map.direct_vसमयr);
	अगर (map.direct_pसमयr)
		समयr_restore_state(map.direct_pसमयr);

	अगर (map.emul_pसमयr)
		समयr_emulate(map.emul_pसमयr);
पूर्ण

bool kvm_समयr_should_notअगरy_user(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_context *vसमयr = vcpu_vसमयr(vcpu);
	काष्ठा arch_समयr_context *pसमयr = vcpu_pसमयr(vcpu);
	काष्ठा kvm_sync_regs *sregs = &vcpu->run->s.regs;
	bool vlevel, plevel;

	अगर (likely(irqchip_in_kernel(vcpu->kvm)))
		वापस false;

	vlevel = sregs->device_irq_level & KVM_ARM_DEV_EL1_VTIMER;
	plevel = sregs->device_irq_level & KVM_ARM_DEV_EL1_PTIMER;

	वापस kvm_समयr_should_fire(vसमयr) != vlevel ||
	       kvm_समयr_should_fire(pसमयr) != plevel;
पूर्ण

व्योम kvm_समयr_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);
	काष्ठा समयr_map map;
	काष्ठा rcuरुको *रुको = kvm_arch_vcpu_get_रुको(vcpu);

	अगर (unlikely(!समयr->enabled))
		वापस;

	get_समयr_map(vcpu, &map);

	समयr_save_state(map.direct_vसमयr);
	अगर (map.direct_pसमयr)
		समयr_save_state(map.direct_pसमयr);

	/*
	 * Cancel soft समयr emulation, because the only हाल where we
	 * need it after a vcpu_put is in the context of a sleeping VCPU, and
	 * in that हाल we alपढ़ोy factor in the deadline क्रम the physical
	 * समयr when scheduling the bg_समयr.
	 *
	 * In any हाल, we re-schedule the hrसमयr क्रम the physical समयr when
	 * coming back to the VCPU thपढ़ो in kvm_समयr_vcpu_load().
	 */
	अगर (map.emul_pसमयr)
		soft_समयr_cancel(&map.emul_pसमयr->hrसमयr);

	अगर (rcuरुको_active(रुको))
		kvm_समयr_blocking(vcpu);

	/*
	 * The kernel may decide to run userspace after calling vcpu_put, so
	 * we reset cntvoff to 0 to ensure a consistent पढ़ो between user
	 * accesses to the भव counter and kernel access to the physical
	 * counter of non-VHE हाल. For VHE, the भव counter uses a fixed
	 * भव offset of zero, so no need to zero CNTVOFF_EL2 रेजिस्टर.
	 */
	set_cntvoff(0);
पूर्ण

/*
 * With a userspace irqchip we have to check अगर the guest de-निश्चितed the
 * समयr and अगर so, unmask the समयr irq संकेत on the host पूर्णांकerrupt
 * controller to ensure that we see future समयr संकेतs.
 */
अटल व्योम unmask_vसमयr_irq_user(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_context *vसमयr = vcpu_vसमयr(vcpu);

	अगर (!kvm_समयr_should_fire(vसमयr)) अणु
		kvm_समयr_update_irq(vcpu, false, vसमयr);
		अगर (अटल_branch_likely(&has_gic_active_state))
			set_समयr_irq_phys_active(vसमयr, false);
		अन्यथा
			enable_percpu_irq(host_vसमयr_irq, host_vसमयr_irq_flags);
	पूर्ण
पूर्ण

व्योम kvm_समयr_sync_user(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);

	अगर (unlikely(!समयr->enabled))
		वापस;

	अगर (unlikely(!irqchip_in_kernel(vcpu->kvm)))
		unmask_vसमयr_irq_user(vcpu);
पूर्ण

पूर्णांक kvm_समयr_vcpu_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);
	काष्ठा समयr_map map;

	get_समयr_map(vcpu, &map);

	/*
	 * The bits in CNTV_CTL are architecturally reset to UNKNOWN क्रम ARMv8
	 * and to 0 क्रम ARMv7.  We provide an implementation that always
	 * resets the समयr to be disabled and unmasked and is compliant with
	 * the ARMv7 architecture.
	 */
	समयr_set_ctl(vcpu_vसमयr(vcpu), 0);
	समयr_set_ctl(vcpu_pसमयr(vcpu), 0);

	अगर (समयr->enabled) अणु
		kvm_समयr_update_irq(vcpu, false, vcpu_vसमयr(vcpu));
		kvm_समयr_update_irq(vcpu, false, vcpu_pसमयr(vcpu));

		अगर (irqchip_in_kernel(vcpu->kvm)) अणु
			kvm_vgic_reset_mapped_irq(vcpu, map.direct_vसमयr->irq.irq);
			अगर (map.direct_pसमयr)
				kvm_vgic_reset_mapped_irq(vcpu, map.direct_pसमयr->irq.irq);
		पूर्ण
	पूर्ण

	अगर (map.emul_pसमयr)
		soft_समयr_cancel(&map.emul_pसमयr->hrसमयr);

	वापस 0;
पूर्ण

/* Make the updates of cntvoff क्रम all vसमयr contexts atomic */
अटल व्योम update_vसमयr_cntvoff(काष्ठा kvm_vcpu *vcpu, u64 cntvoff)
अणु
	पूर्णांक i;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_vcpu *पंचांगp;

	mutex_lock(&kvm->lock);
	kvm_क्रम_each_vcpu(i, पंचांगp, kvm)
		समयr_set_offset(vcpu_vसमयr(पंचांगp), cntvoff);

	/*
	 * When called from the vcpu create path, the CPU being created is not
	 * included in the loop above, so we just set it here as well.
	 */
	समयr_set_offset(vcpu_vसमयr(vcpu), cntvoff);
	mutex_unlock(&kvm->lock);
पूर्ण

व्योम kvm_समयr_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);
	काष्ठा arch_समयr_context *vसमयr = vcpu_vसमयr(vcpu);
	काष्ठा arch_समयr_context *pसमयr = vcpu_pसमयr(vcpu);

	vसमयr->vcpu = vcpu;
	pसमयr->vcpu = vcpu;

	/* Synchronize cntvoff across all vसमयrs of a VM. */
	update_vसमयr_cntvoff(vcpu, kvm_phys_समयr_पढ़ो());
	समयr_set_offset(pसमयr, 0);

	hrसमयr_init(&समयr->bg_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	समयr->bg_समयr.function = kvm_bg_समयr_expire;

	hrसमयr_init(&vसमयr->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	hrसमयr_init(&pसमयr->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	vसमयr->hrसमयr.function = kvm_hrसमयr_expire;
	pसमयr->hrसमयr.function = kvm_hrसमयr_expire;

	vसमयr->irq.irq = शेष_vसमयr_irq.irq;
	pसमयr->irq.irq = शेष_pसमयr_irq.irq;

	vसमयr->host_समयr_irq = host_vसमयr_irq;
	pसमयr->host_समयr_irq = host_pसमयr_irq;

	vसमयr->host_समयr_irq_flags = host_vसमयr_irq_flags;
	pसमयr->host_समयr_irq_flags = host_pसमयr_irq_flags;
पूर्ण

अटल व्योम kvm_समयr_init_पूर्णांकerrupt(व्योम *info)
अणु
	enable_percpu_irq(host_vसमयr_irq, host_vसमयr_irq_flags);
	enable_percpu_irq(host_pसमयr_irq, host_pसमयr_irq_flags);
पूर्ण

पूर्णांक kvm_arm_समयr_set_reg(काष्ठा kvm_vcpu *vcpu, u64 regid, u64 value)
अणु
	काष्ठा arch_समयr_context *समयr;

	चयन (regid) अणु
	हाल KVM_REG_ARM_TIMER_CTL:
		समयr = vcpu_vसमयr(vcpu);
		kvm_arm_समयr_ग_लिखो(vcpu, समयr, TIMER_REG_CTL, value);
		अवरोध;
	हाल KVM_REG_ARM_TIMER_CNT:
		समयr = vcpu_vसमयr(vcpu);
		update_vसमयr_cntvoff(vcpu, kvm_phys_समयr_पढ़ो() - value);
		अवरोध;
	हाल KVM_REG_ARM_TIMER_CVAL:
		समयr = vcpu_vसमयr(vcpu);
		kvm_arm_समयr_ग_लिखो(vcpu, समयr, TIMER_REG_CVAL, value);
		अवरोध;
	हाल KVM_REG_ARM_PTIMER_CTL:
		समयr = vcpu_pसमयr(vcpu);
		kvm_arm_समयr_ग_लिखो(vcpu, समयr, TIMER_REG_CTL, value);
		अवरोध;
	हाल KVM_REG_ARM_PTIMER_CVAL:
		समयr = vcpu_pसमयr(vcpu);
		kvm_arm_समयr_ग_लिखो(vcpu, समयr, TIMER_REG_CVAL, value);
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 पढ़ो_समयr_ctl(काष्ठा arch_समयr_context *समयr)
अणु
	/*
	 * Set ISTATUS bit अगर it's expired.
	 * Note that according to ARMv8 ARM Issue A.k, ISTATUS bit is
	 * UNKNOWN when ENABLE bit is 0, so we chose to set ISTATUS bit
	 * regardless of ENABLE bit क्रम our implementation convenience.
	 */
	u32 ctl = समयr_get_ctl(समयr);

	अगर (!kvm_समयr_compute_delta(समयr))
		ctl |= ARCH_TIMER_CTRL_IT_STAT;

	वापस ctl;
पूर्ण

u64 kvm_arm_समयr_get_reg(काष्ठा kvm_vcpu *vcpu, u64 regid)
अणु
	चयन (regid) अणु
	हाल KVM_REG_ARM_TIMER_CTL:
		वापस kvm_arm_समयr_पढ़ो(vcpu,
					  vcpu_vसमयr(vcpu), TIMER_REG_CTL);
	हाल KVM_REG_ARM_TIMER_CNT:
		वापस kvm_arm_समयr_पढ़ो(vcpu,
					  vcpu_vसमयr(vcpu), TIMER_REG_CNT);
	हाल KVM_REG_ARM_TIMER_CVAL:
		वापस kvm_arm_समयr_पढ़ो(vcpu,
					  vcpu_vसमयr(vcpu), TIMER_REG_CVAL);
	हाल KVM_REG_ARM_PTIMER_CTL:
		वापस kvm_arm_समयr_पढ़ो(vcpu,
					  vcpu_pसमयr(vcpu), TIMER_REG_CTL);
	हाल KVM_REG_ARM_PTIMER_CNT:
		वापस kvm_arm_समयr_पढ़ो(vcpu,
					  vcpu_pसमयr(vcpu), TIMER_REG_CNT);
	हाल KVM_REG_ARM_PTIMER_CVAL:
		वापस kvm_arm_समयr_पढ़ो(vcpu,
					  vcpu_pसमयr(vcpu), TIMER_REG_CVAL);
	पूर्ण
	वापस (u64)-1;
पूर्ण

अटल u64 kvm_arm_समयr_पढ़ो(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा arch_समयr_context *समयr,
			      क्रमागत kvm_arch_समयr_regs treg)
अणु
	u64 val;

	चयन (treg) अणु
	हाल TIMER_REG_TVAL:
		val = समयr_get_cval(समयr) - kvm_phys_समयr_पढ़ो() + समयr_get_offset(समयr);
		val = lower_32_bits(val);
		अवरोध;

	हाल TIMER_REG_CTL:
		val = पढ़ो_समयr_ctl(समयr);
		अवरोध;

	हाल TIMER_REG_CVAL:
		val = समयr_get_cval(समयr);
		अवरोध;

	हाल TIMER_REG_CNT:
		val = kvm_phys_समयr_पढ़ो() - समयr_get_offset(समयr);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस val;
पूर्ण

u64 kvm_arm_समयr_पढ़ो_sysreg(काष्ठा kvm_vcpu *vcpu,
			      क्रमागत kvm_arch_समयrs पंचांगr,
			      क्रमागत kvm_arch_समयr_regs treg)
अणु
	u64 val;

	preempt_disable();
	kvm_समयr_vcpu_put(vcpu);

	val = kvm_arm_समयr_पढ़ो(vcpu, vcpu_get_समयr(vcpu, पंचांगr), treg);

	kvm_समयr_vcpu_load(vcpu);
	preempt_enable();

	वापस val;
पूर्ण

अटल व्योम kvm_arm_समयr_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				काष्ठा arch_समयr_context *समयr,
				क्रमागत kvm_arch_समयr_regs treg,
				u64 val)
अणु
	चयन (treg) अणु
	हाल TIMER_REG_TVAL:
		समयr_set_cval(समयr, kvm_phys_समयr_पढ़ो() - समयr_get_offset(समयr) + (s32)val);
		अवरोध;

	हाल TIMER_REG_CTL:
		समयr_set_ctl(समयr, val & ~ARCH_TIMER_CTRL_IT_STAT);
		अवरोध;

	हाल TIMER_REG_CVAL:
		समयr_set_cval(समयr, val);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम kvm_arm_समयr_ग_लिखो_sysreg(काष्ठा kvm_vcpu *vcpu,
				क्रमागत kvm_arch_समयrs पंचांगr,
				क्रमागत kvm_arch_समयr_regs treg,
				u64 val)
अणु
	preempt_disable();
	kvm_समयr_vcpu_put(vcpu);

	kvm_arm_समयr_ग_लिखो(vcpu, vcpu_get_समयr(vcpu, पंचांगr), treg, val);

	kvm_समयr_vcpu_load(vcpu);
	preempt_enable();
पूर्ण

अटल पूर्णांक kvm_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	kvm_समयr_init_पूर्णांकerrupt(शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(host_vसमयr_irq);
	वापस 0;
पूर्ण

पूर्णांक kvm_समयr_hyp_init(bool has_gic)
अणु
	काष्ठा arch_समयr_kvm_info *info;
	पूर्णांक err;

	info = arch_समयr_get_kvm_info();
	समयcounter = &info->समयcounter;

	अगर (!समयcounter->cc) अणु
		kvm_err("kvm_arch_timer: uninitialized timecounter\n");
		वापस -ENODEV;
	पूर्ण

	/* First, करो the भव EL1 समयr irq */

	अगर (info->भव_irq <= 0) अणु
		kvm_err("kvm_arch_timer: invalid virtual timer IRQ: %d\n",
			info->भव_irq);
		वापस -ENODEV;
	पूर्ण
	host_vसमयr_irq = info->भव_irq;

	host_vसमयr_irq_flags = irq_get_trigger_type(host_vसमयr_irq);
	अगर (host_vसमयr_irq_flags != IRQF_TRIGGER_HIGH &&
	    host_vसमयr_irq_flags != IRQF_TRIGGER_LOW) अणु
		kvm_err("Invalid trigger for vtimer IRQ%d, assuming level low\n",
			host_vसमयr_irq);
		host_vसमयr_irq_flags = IRQF_TRIGGER_LOW;
	पूर्ण

	err = request_percpu_irq(host_vसमयr_irq, kvm_arch_समयr_handler,
				 "kvm guest vtimer", kvm_get_running_vcpus());
	अगर (err) अणु
		kvm_err("kvm_arch_timer: can't request vtimer interrupt %d (%d)\n",
			host_vसमयr_irq, err);
		वापस err;
	पूर्ण

	अगर (has_gic) अणु
		err = irq_set_vcpu_affinity(host_vसमयr_irq,
					    kvm_get_running_vcpus());
		अगर (err) अणु
			kvm_err("kvm_arch_timer: error setting vcpu affinity\n");
			जाओ out_मुक्त_irq;
		पूर्ण

		अटल_branch_enable(&has_gic_active_state);
	पूर्ण

	kvm_debug("virtual timer IRQ%d\n", host_vसमयr_irq);

	/* Now let's करो the physical EL1 समयr irq */

	अगर (info->physical_irq > 0) अणु
		host_pसमयr_irq = info->physical_irq;
		host_pसमयr_irq_flags = irq_get_trigger_type(host_pसमयr_irq);
		अगर (host_pसमयr_irq_flags != IRQF_TRIGGER_HIGH &&
		    host_pसमयr_irq_flags != IRQF_TRIGGER_LOW) अणु
			kvm_err("Invalid trigger for ptimer IRQ%d, assuming level low\n",
				host_pसमयr_irq);
			host_pसमयr_irq_flags = IRQF_TRIGGER_LOW;
		पूर्ण

		err = request_percpu_irq(host_pसमयr_irq, kvm_arch_समयr_handler,
					 "kvm guest ptimer", kvm_get_running_vcpus());
		अगर (err) अणु
			kvm_err("kvm_arch_timer: can't request ptimer interrupt %d (%d)\n",
				host_pसमयr_irq, err);
			वापस err;
		पूर्ण

		अगर (has_gic) अणु
			err = irq_set_vcpu_affinity(host_pसमयr_irq,
						    kvm_get_running_vcpus());
			अगर (err) अणु
				kvm_err("kvm_arch_timer: error setting vcpu affinity\n");
				जाओ out_मुक्त_irq;
			पूर्ण
		पूर्ण

		kvm_debug("physical timer IRQ%d\n", host_pसमयr_irq);
	पूर्ण अन्यथा अगर (has_vhe()) अणु
		kvm_err("kvm_arch_timer: invalid physical timer IRQ: %d\n",
			info->physical_irq);
		err = -ENODEV;
		जाओ out_मुक्त_irq;
	पूर्ण

	cpuhp_setup_state(CPUHP_AP_KVM_ARM_TIMER_STARTING,
			  "kvm/arm/timer:starting", kvm_समयr_starting_cpu,
			  kvm_समयr_dying_cpu);
	वापस 0;
out_मुक्त_irq:
	मुक्त_percpu_irq(host_vसमयr_irq, kvm_get_running_vcpus());
	वापस err;
पूर्ण

व्योम kvm_समयr_vcpu_terminate(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);

	soft_समयr_cancel(&समयr->bg_समयr);
पूर्ण

अटल bool समयr_irqs_are_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक vसमयr_irq, pसमयr_irq;
	पूर्णांक i, ret;

	vसमयr_irq = vcpu_vसमयr(vcpu)->irq.irq;
	ret = kvm_vgic_set_owner(vcpu, vसमयr_irq, vcpu_vसमयr(vcpu));
	अगर (ret)
		वापस false;

	pसमयr_irq = vcpu_pसमयr(vcpu)->irq.irq;
	ret = kvm_vgic_set_owner(vcpu, pसमयr_irq, vcpu_pसमयr(vcpu));
	अगर (ret)
		वापस false;

	kvm_क्रम_each_vcpu(i, vcpu, vcpu->kvm) अणु
		अगर (vcpu_vसमयr(vcpu)->irq.irq != vसमयr_irq ||
		    vcpu_pसमयr(vcpu)->irq.irq != pसमयr_irq)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool kvm_arch_समयr_get_input_level(पूर्णांक vपूर्णांकid)
अणु
	काष्ठा kvm_vcpu *vcpu = kvm_get_running_vcpu();
	काष्ठा arch_समयr_context *समयr;

	अगर (vपूर्णांकid == vcpu_vसमयr(vcpu)->irq.irq)
		समयr = vcpu_vसमयr(vcpu);
	अन्यथा अगर (vपूर्णांकid == vcpu_pसमयr(vcpu)->irq.irq)
		समयr = vcpu_pसमयr(vcpu);
	अन्यथा
		BUG();

	वापस kvm_समयr_should_fire(समयr);
पूर्ण

पूर्णांक kvm_समयr_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा arch_समयr_cpu *समयr = vcpu_समयr(vcpu);
	काष्ठा समयr_map map;
	पूर्णांक ret;

	अगर (समयr->enabled)
		वापस 0;

	/* Without a VGIC we करो not map भव IRQs to physical IRQs */
	अगर (!irqchip_in_kernel(vcpu->kvm))
		जाओ no_vgic;

	/*
	 * At this stage, we have the guarantee that the vgic is both
	 * available and initialized.
	 */
	अगर (!समयr_irqs_are_valid(vcpu)) अणु
		kvm_debug("incorrectly configured timer irqs\n");
		वापस -EINVAL;
	पूर्ण

	get_समयr_map(vcpu, &map);

	ret = kvm_vgic_map_phys_irq(vcpu,
				    map.direct_vसमयr->host_समयr_irq,
				    map.direct_vसमयr->irq.irq,
				    kvm_arch_समयr_get_input_level);
	अगर (ret)
		वापस ret;

	अगर (map.direct_pसमयr) अणु
		ret = kvm_vgic_map_phys_irq(vcpu,
					    map.direct_pसमयr->host_समयr_irq,
					    map.direct_pसमयr->irq.irq,
					    kvm_arch_समयr_get_input_level);
	पूर्ण

	अगर (ret)
		वापस ret;

no_vgic:
	समयr->enabled = 1;
	वापस 0;
पूर्ण

/*
 * On VHE प्रणाली, we only need to configure the EL2 समयr trap रेजिस्टर once,
 * not क्रम every world चयन.
 * The host kernel runs at EL2 with HCR_EL2.TGE == 1,
 * and this makes those bits have no effect क्रम the host kernel execution.
 */
व्योम kvm_समयr_init_vhe(व्योम)
अणु
	/* When HCR_EL2.E2H ==1, EL1PCEN and EL1PCTEN are shअगरted by 10 */
	u32 cnthctl_shअगरt = 10;
	u64 val;

	/*
	 * VHE प्रणालीs allow the guest direct access to the EL1 physical
	 * समयr/counter.
	 */
	val = पढ़ो_sysreg(cnthctl_el2);
	val |= (CNTHCTL_EL1PCEN << cnthctl_shअगरt);
	val |= (CNTHCTL_EL1PCTEN << cnthctl_shअगरt);
	ग_लिखो_sysreg(val, cnthctl_el2);
पूर्ण

अटल व्योम set_समयr_irqs(काष्ठा kvm *kvm, पूर्णांक vसमयr_irq, पूर्णांक pसमयr_irq)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		vcpu_vसमयr(vcpu)->irq.irq = vसमयr_irq;
		vcpu_pसमयr(vcpu)->irq.irq = pसमयr_irq;
	पूर्ण
पूर्ण

पूर्णांक kvm_arm_समयr_set_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक __user *uaddr = (पूर्णांक __user *)(दीर्घ)attr->addr;
	काष्ठा arch_समयr_context *vसमयr = vcpu_vसमयr(vcpu);
	काष्ठा arch_समयr_context *pसमयr = vcpu_pसमयr(vcpu);
	पूर्णांक irq;

	अगर (!irqchip_in_kernel(vcpu->kvm))
		वापस -EINVAL;

	अगर (get_user(irq, uaddr))
		वापस -EFAULT;

	अगर (!(irq_is_ppi(irq)))
		वापस -EINVAL;

	अगर (vcpu->arch.समयr_cpu.enabled)
		वापस -EBUSY;

	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_TIMER_IRQ_VTIMER:
		set_समयr_irqs(vcpu->kvm, irq, pसमयr->irq.irq);
		अवरोध;
	हाल KVM_ARM_VCPU_TIMER_IRQ_PTIMER:
		set_समयr_irqs(vcpu->kvm, vसमयr->irq.irq, irq);
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvm_arm_समयr_get_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक __user *uaddr = (पूर्णांक __user *)(दीर्घ)attr->addr;
	काष्ठा arch_समयr_context *समयr;
	पूर्णांक irq;

	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_TIMER_IRQ_VTIMER:
		समयr = vcpu_vसमयr(vcpu);
		अवरोध;
	हाल KVM_ARM_VCPU_TIMER_IRQ_PTIMER:
		समयr = vcpu_pसमयr(vcpu);
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	irq = समयr->irq.irq;
	वापस put_user(irq, uaddr);
पूर्ण

पूर्णांक kvm_arm_समयr_has_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_TIMER_IRQ_VTIMER:
	हाल KVM_ARM_VCPU_TIMER_IRQ_PTIMER:
		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण
