<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ASM_ARM_KVM_ARCH_TIMER_H
#घोषणा __ASM_ARM_KVM_ARCH_TIMER_H

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/hrसमयr.h>

क्रमागत kvm_arch_समयrs अणु
	TIMER_PTIMER,
	TIMER_VTIMER,
	NR_KVM_TIMERS
पूर्ण;

क्रमागत kvm_arch_समयr_regs अणु
	TIMER_REG_CNT,
	TIMER_REG_CVAL,
	TIMER_REG_TVAL,
	TIMER_REG_CTL,
पूर्ण;

काष्ठा arch_समयr_context अणु
	काष्ठा kvm_vcpu			*vcpu;

	/* Timer IRQ */
	काष्ठा kvm_irq_level		irq;

	/* Emulated Timer (may be unused) */
	काष्ठा hrसमयr			hrसमयr;

	/*
	 * We have multiple paths which can save/restore the समयr state onto
	 * the hardware, so we need some way of keeping track of where the
	 * latest state is.
	 */
	bool				loaded;

	/* Duplicated state from arch_समयr.c क्रम convenience */
	u32				host_समयr_irq;
	u32				host_समयr_irq_flags;
पूर्ण;

काष्ठा समयr_map अणु
	काष्ठा arch_समयr_context *direct_vसमयr;
	काष्ठा arch_समयr_context *direct_pसमयr;
	काष्ठा arch_समयr_context *emul_pसमयr;
पूर्ण;

काष्ठा arch_समयr_cpu अणु
	काष्ठा arch_समयr_context समयrs[NR_KVM_TIMERS];

	/* Background समयr used when the guest is not running */
	काष्ठा hrसमयr			bg_समयr;

	/* Is the समयr enabled */
	bool			enabled;
पूर्ण;

पूर्णांक kvm_समयr_hyp_init(bool);
पूर्णांक kvm_समयr_enable(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_समयr_vcpu_reset(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_समयr_vcpu_init(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_समयr_sync_user(काष्ठा kvm_vcpu *vcpu);
bool kvm_समयr_should_notअगरy_user(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_समयr_update_run(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_समयr_vcpu_terminate(काष्ठा kvm_vcpu *vcpu);

u64 kvm_arm_समयr_get_reg(काष्ठा kvm_vcpu *, u64 regid);
पूर्णांक kvm_arm_समयr_set_reg(काष्ठा kvm_vcpu *, u64 regid, u64 value);

पूर्णांक kvm_arm_समयr_set_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_समयr_get_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_समयr_has_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr);

bool kvm_समयr_is_pending(काष्ठा kvm_vcpu *vcpu);

u64 kvm_phys_समयr_पढ़ो(व्योम);

व्योम kvm_समयr_vcpu_load(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_समयr_vcpu_put(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_समयr_init_vhe(व्योम);

bool kvm_arch_समयr_get_input_level(पूर्णांक vपूर्णांकid);

#घोषणा vcpu_समयr(v)	(&(v)->arch.समयr_cpu)
#घोषणा vcpu_get_समयr(v,t)	(&vcpu_समयr(v)->समयrs[(t)])
#घोषणा vcpu_vसमयr(v)	(&(v)->arch.समयr_cpu.समयrs[TIMER_VTIMER])
#घोषणा vcpu_pसमयr(v)	(&(v)->arch.समयr_cpu.समयrs[TIMER_PTIMER])

#घोषणा arch_समयr_ctx_index(ctx)	((ctx) - vcpu_समयr((ctx)->vcpu)->समयrs)

u64 kvm_arm_समयr_पढ़ो_sysreg(काष्ठा kvm_vcpu *vcpu,
			      क्रमागत kvm_arch_समयrs पंचांगr,
			      क्रमागत kvm_arch_समयr_regs treg);
व्योम kvm_arm_समयr_ग_लिखो_sysreg(काष्ठा kvm_vcpu *vcpu,
				क्रमागत kvm_arch_समयrs पंचांगr,
				क्रमागत kvm_arch_समयr_regs treg,
				u64 val);

/* Needed क्रम tracing */
u32 समयr_get_ctl(काष्ठा arch_समयr_context *ctxt);
u64 समयr_get_cval(काष्ठा arch_समयr_context *ctxt);

#पूर्ण_अगर
