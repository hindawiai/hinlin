<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Michael Ellerman, IBM Corporation.
 * Copyright 2012 Benjamin Herrenschmidt, IBM Corporation
 */

#अगर_अघोषित _KVM_PPC_BOOK3S_XICS_H
#घोषणा _KVM_PPC_BOOK3S_XICS_H

#अगर_घोषित CONFIG_KVM_XICS
/*
 * We use a two-level tree to store पूर्णांकerrupt source inक्रमmation.
 * There are up to 1024 ICS nodes, each of which can represent
 * 1024 sources.
 */
#घोषणा KVMPPC_XICS_MAX_ICS_ID	1023
#घोषणा KVMPPC_XICS_ICS_SHIFT	10
#घोषणा KVMPPC_XICS_IRQ_PER_ICS	(1 << KVMPPC_XICS_ICS_SHIFT)
#घोषणा KVMPPC_XICS_SRC_MASK	(KVMPPC_XICS_IRQ_PER_ICS - 1)

/*
 * Interrupt source numbers below this are reserved, क्रम example
 * 0 is "no interrupt", and 2 is used क्रम IPIs.
 */
#घोषणा KVMPPC_XICS_FIRST_IRQ	16
#घोषणा KVMPPC_XICS_NR_IRQS	((KVMPPC_XICS_MAX_ICS_ID + 1) * \
				 KVMPPC_XICS_IRQ_PER_ICS)

/* Priority value to use क्रम disabling an पूर्णांकerrupt */
#घोषणा MASKED	0xff

#घोषणा PQ_PRESENTED	1
#घोषणा PQ_QUEUED	2

/* State क्रम one irq source */
काष्ठा ics_irq_state अणु
	u32 number;
	u32 server;
	u32 pq_state;
	u8  priority;
	u8  saved_priority;
	u8  resend;
	u8  masked_pending;
	u8  lsi;		/* level-sensitive पूर्णांकerrupt */
	u8  exists;
	पूर्णांक पूर्णांकr_cpu;
	u32 host_irq;
पूर्ण;

/* Atomic ICP state, updated with a single compare & swap */
जोड़ kvmppc_icp_state अणु
	अचिन्हित दीर्घ raw;
	काष्ठा अणु
		u8 out_ee:1;
		u8 need_resend:1;
		u8 cppr;
		u8 mfrr;
		u8 pending_pri;
		u32 xisr;
	पूर्ण;
पूर्ण;

/* One bit per ICS */
#घोषणा ICP_RESEND_MAP_SIZE	(KVMPPC_XICS_MAX_ICS_ID / BITS_PER_LONG + 1)

काष्ठा kvmppc_icp अणु
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित दीर्घ server_num;
	जोड़ kvmppc_icp_state state;
	अचिन्हित दीर्घ resend_map[ICP_RESEND_MAP_SIZE];

	/* Real mode might find something too hard, here's the action
	 * it might request from भव mode
	 */
#घोषणा XICS_RM_KICK_VCPU	0x1
#घोषणा XICS_RM_CHECK_RESEND	0x2
#घोषणा XICS_RM_NOTIFY_EOI	0x8
	u32 rm_action;
	काष्ठा kvm_vcpu *rm_kick_target;
	काष्ठा kvmppc_icp *rm_resend_icp;
	u32  rm_reject;
	u32  rm_eoied_irq;

	/* Counters क्रम each reason we निकासed real mode */
	अचिन्हित दीर्घ n_rm_kick_vcpu;
	अचिन्हित दीर्घ n_rm_check_resend;
	अचिन्हित दीर्घ n_rm_notअगरy_eoi;
	/* Counters क्रम handling ICP processing in real mode */
	अचिन्हित दीर्घ n_check_resend;
	अचिन्हित दीर्घ n_reject;

	/* Debug stuff क्रम real mode */
	जोड़ kvmppc_icp_state rm_dbgstate;
	काष्ठा kvm_vcpu *rm_dbgtgt;
पूर्ण;

काष्ठा kvmppc_ics अणु
	arch_spinlock_t lock;
	u16 icsid;
	काष्ठा ics_irq_state irq_state[KVMPPC_XICS_IRQ_PER_ICS];
पूर्ण;

काष्ठा kvmppc_xics अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_device *dev;
	काष्ठा dentry *dentry;
	u32 max_icsid;
	bool real_mode;
	bool real_mode_dbg;
	u32 err_noics;
	u32 err_noicp;
	काष्ठा kvmppc_ics *ics[KVMPPC_XICS_MAX_ICS_ID + 1];
पूर्ण;

अटल अंतरभूत काष्ठा kvmppc_icp *kvmppc_xics_find_server(काष्ठा kvm *kvm,
							 u32 nr)
अणु
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (vcpu->arch.icp && nr == vcpu->arch.icp->server_num)
			वापस vcpu->arch.icp;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा kvmppc_ics *kvmppc_xics_find_ics(काष्ठा kvmppc_xics *xics,
						      u32 irq, u16 *source)
अणु
	u32 icsid = irq >> KVMPPC_XICS_ICS_SHIFT;
	u16 src = irq & KVMPPC_XICS_SRC_MASK;
	काष्ठा kvmppc_ics *ics;

	अगर (source)
		*source = src;
	अगर (icsid > KVMPPC_XICS_MAX_ICS_ID)
		वापस शून्य;
	ics = xics->ics[icsid];
	अगर (!ics)
		वापस शून्य;
	वापस ics;
पूर्ण

बाह्य अचिन्हित दीर्घ xics_rm_h_xirr(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक xics_rm_h_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
			 अचिन्हित दीर्घ mfrr);
बाह्य पूर्णांक xics_rm_h_cppr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr);
बाह्य पूर्णांक xics_rm_h_eoi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr);

#पूर्ण_अगर /* CONFIG_KVM_XICS */
#पूर्ण_अगर /* _KVM_PPC_BOOK3S_XICS_H */
