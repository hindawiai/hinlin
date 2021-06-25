<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017 Benjamin Herrenschmidt, IBM Corporation
 */

#अगर_अघोषित _KVM_PPC_BOOK3S_XIVE_H
#घोषणा _KVM_PPC_BOOK3S_XIVE_H

#अगर_घोषित CONFIG_KVM_XICS
#समावेश "book3s_xics.h"

/*
 * The XIVE Interrupt source numbers are within the range 0 to
 * KVMPPC_XICS_NR_IRQS.
 */
#घोषणा KVMPPC_XIVE_FIRST_IRQ	0
#घोषणा KVMPPC_XIVE_NR_IRQS	KVMPPC_XICS_NR_IRQS

/*
 * State क्रम one guest irq source.
 *
 * For each guest source we allocate a HW पूर्णांकerrupt in the XIVE
 * which we use क्रम all SW triggers. It will be unused क्रम
 * pass-through but it's easier to keep around as the same
 * guest पूर्णांकerrupt can alternatively be emulated or pass-through
 * अगर a physical device is hot unplugged and replaced with an
 * emulated one.
 *
 * This state काष्ठाure is very similar to the XICS one with
 * additional XIVE specअगरic tracking.
 */
काष्ठा kvmppc_xive_irq_state अणु
	bool valid;			/* Interrupt entry is valid */

	u32 number;			/* Guest IRQ number */
	u32 ipi_number;			/* XIVE IPI HW number */
	काष्ठा xive_irq_data ipi_data;	/* XIVE IPI associated data */
	u32 pt_number;			/* XIVE Pass-through number अगर any */
	काष्ठा xive_irq_data *pt_data;	/* XIVE Pass-through associated data */

	/* Targetting as set by guest */
	u8 guest_priority;		/* Guest set priority */
	u8 saved_priority;		/* Saved priority when masking */

	/* Actual targetting */
	u32 act_server;			/* Actual server */
	u8 act_priority;		/* Actual priority */

	/* Various state bits */
	bool in_eoi;			/* Synchronize with H_EOI */
	bool old_p;			/* P bit state when masking */
	bool old_q;			/* Q bit state when masking */
	bool lsi;			/* level-sensitive पूर्णांकerrupt */
	bool निश्चितed;			/* Only क्रम emulated LSI: current state */

	/* Saved क्रम migration state */
	bool in_queue;
	bool saved_p;
	bool saved_q;
	u8 saved_scan_prio;

	/* Xive native */
	u32 eisn;			/* Guest Effective IRQ number */
पूर्ण;

/* Select the "right" पूर्णांकerrupt (IPI vs. passthrough) */
अटल अंतरभूत व्योम kvmppc_xive_select_irq(काष्ठा kvmppc_xive_irq_state *state,
					  u32 *out_hw_irq,
					  काष्ठा xive_irq_data **out_xd)
अणु
	अगर (state->pt_number) अणु
		अगर (out_hw_irq)
			*out_hw_irq = state->pt_number;
		अगर (out_xd)
			*out_xd = state->pt_data;
	पूर्ण अन्यथा अणु
		अगर (out_hw_irq)
			*out_hw_irq = state->ipi_number;
		अगर (out_xd)
			*out_xd = &state->ipi_data;
	पूर्ण
पूर्ण

/*
 * This corresponds to an "ICS" in XICS terminology, we use it
 * as a mean to अवरोध up source inक्रमmation पूर्णांकo multiple काष्ठाures.
 */
काष्ठा kvmppc_xive_src_block अणु
	arch_spinlock_t lock;
	u16 id;
	काष्ठा kvmppc_xive_irq_state irq_state[KVMPPC_XICS_IRQ_PER_ICS];
पूर्ण;

काष्ठा kvmppc_xive;

काष्ठा kvmppc_xive_ops अणु
	पूर्णांक (*reset_mapped)(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq);
पूर्ण;

काष्ठा kvmppc_xive अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_device *dev;
	काष्ठा dentry *dentry;

	/* VP block associated with the VM */
	u32	vp_base;

	/* Blocks of sources */
	काष्ठा kvmppc_xive_src_block *src_blocks[KVMPPC_XICS_MAX_ICS_ID + 1];
	u32	max_sbid;

	/*
	 * For state save, we lazily scan the queues on the first पूर्णांकerrupt
	 * being migrated. We करोn't have a clean way to reset that flags
	 * so we keep track of the number of valid sources and how many of
	 * them were migrated so we can reset when all of them have been
	 * processed.
	 */
	u32	src_count;
	u32	saved_src_count;

	/*
	 * Some irqs are delayed on restore until the source is created,
	 * keep track here of how many of them
	 */
	u32	delayed_irqs;

	/* Which queues (priorities) are in use by the guest */
	u8	qmap;

	/* Queue orders */
	u32	q_order;
	u32	q_page_order;

	/* Flags */
	u8	single_escalation;

	/* Number of entries in the VP block */
	u32	nr_servers;

	काष्ठा kvmppc_xive_ops *ops;
	काष्ठा address_space   *mapping;
	काष्ठा mutex mapping_lock;
	काष्ठा mutex lock;
पूर्ण;

#घोषणा KVMPPC_XIVE_Q_COUNT	8

काष्ठा kvmppc_xive_vcpu अणु
	काष्ठा kvmppc_xive	*xive;
	काष्ठा kvm_vcpu		*vcpu;
	bool			valid;

	/* Server number. This is the HW CPU ID from a guest perspective */
	u32			server_num;

	/*
	 * HW VP corresponding to this VCPU. This is the base of the VP
	 * block plus the server number.
	 */
	u32			vp_id;
	u32			vp_chip_id;
	u32			vp_cam;

	/* IPI used क्रम sending ... IPIs */
	u32			vp_ipi;
	काष्ठा xive_irq_data	vp_ipi_data;

	/* Local emulation state */
	uपूर्णांक8_t			cppr;	/* guest CPPR */
	uपूर्णांक8_t			hw_cppr;/* Hardware CPPR */
	uपूर्णांक8_t			mfrr;
	uपूर्णांक8_t			pending;

	/* Each VP has 8 queues though we only provision some */
	काष्ठा xive_q		queues[KVMPPC_XIVE_Q_COUNT];
	u32			esc_virq[KVMPPC_XIVE_Q_COUNT];
	अक्षर			*esc_virq_names[KVMPPC_XIVE_Q_COUNT];

	/* Stash a delayed irq on restore from migration (see set_icp) */
	u32			delayed_irq;

	/* Stats */
	u64			stat_rm_h_xirr;
	u64			stat_rm_h_ipoll;
	u64			stat_rm_h_cppr;
	u64			stat_rm_h_eoi;
	u64			stat_rm_h_ipi;
	u64			stat_vm_h_xirr;
	u64			stat_vm_h_ipoll;
	u64			stat_vm_h_cppr;
	u64			stat_vm_h_eoi;
	u64			stat_vm_h_ipi;
पूर्ण;

अटल अंतरभूत काष्ठा kvm_vcpu *kvmppc_xive_find_server(काष्ठा kvm *kvm, u32 nr)
अणु
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (vcpu->arch.xive_vcpu && nr == vcpu->arch.xive_vcpu->server_num)
			वापस vcpu;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा kvmppc_xive_src_block *kvmppc_xive_find_source(काष्ठा kvmppc_xive *xive,
		u32 irq, u16 *source)
अणु
	u32 bid = irq >> KVMPPC_XICS_ICS_SHIFT;
	u16 src = irq & KVMPPC_XICS_SRC_MASK;

	अगर (source)
		*source = src;
	अगर (bid > KVMPPC_XICS_MAX_ICS_ID)
		वापस शून्य;
	वापस xive->src_blocks[bid];
पूर्ण

/*
 * When the XIVE resources are allocated at the HW level, the VP
 * काष्ठाures describing the vCPUs of a guest are distributed among
 * the chips to optimize the PowerBUS usage. For best perक्रमmance, the
 * guest vCPUs can be pinned to match the VP काष्ठाure distribution.
 *
 * Currently, the VP identअगरiers are deduced from the vCPU id using
 * the kvmppc_pack_vcpu_id() routine which is not incorrect but not
 * optimal either. It VSMT is used, the result is not continuous and
 * the स्थिरraपूर्णांकs on HW resources described above can not be met.
 */
अटल अंतरभूत u32 kvmppc_xive_vp(काष्ठा kvmppc_xive *xive, u32 server)
अणु
	वापस xive->vp_base + kvmppc_pack_vcpu_id(xive->kvm, server);
पूर्ण

अटल अंतरभूत bool kvmppc_xive_vp_in_use(काष्ठा kvm *kvm, u32 vp_id)
अणु
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (vcpu->arch.xive_vcpu && vp_id == vcpu->arch.xive_vcpu->vp_id)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Mapping between guest priorities and host priorities
 * is as follow.
 *
 * Guest request क्रम 0...6 are honored. Guest request क्रम anything
 * higher results in a priority of 6 being applied.
 *
 * Similar mapping is करोne क्रम CPPR values
 */
अटल अंतरभूत u8 xive_prio_from_guest(u8 prio)
अणु
	अगर (prio == 0xff || prio < 6)
		वापस prio;
	वापस 6;
पूर्ण

अटल अंतरभूत u8 xive_prio_to_guest(u8 prio)
अणु
	वापस prio;
पूर्ण

अटल अंतरभूत u32 __xive_पढ़ो_eq(__be32 *qpage, u32 msk, u32 *idx, u32 *toggle)
अणु
	u32 cur;

	अगर (!qpage)
		वापस 0;
	cur = be32_to_cpup(qpage + *idx);
	अगर ((cur >> 31) == *toggle)
		वापस 0;
	*idx = (*idx + 1) & msk;
	अगर (*idx == 0)
		(*toggle) ^= 1;
	वापस cur & 0x7fffffff;
पूर्ण

बाह्य अचिन्हित दीर्घ xive_rm_h_xirr(काष्ठा kvm_vcpu *vcpu);
बाह्य अचिन्हित दीर्घ xive_rm_h_ipoll(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server);
बाह्य पूर्णांक xive_rm_h_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
			 अचिन्हित दीर्घ mfrr);
बाह्य पूर्णांक xive_rm_h_cppr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr);
बाह्य पूर्णांक xive_rm_h_eoi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr);

बाह्य अचिन्हित दीर्घ (*__xive_vm_h_xirr)(काष्ठा kvm_vcpu *vcpu);
बाह्य अचिन्हित दीर्घ (*__xive_vm_h_ipoll)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server);
बाह्य पूर्णांक (*__xive_vm_h_ipi)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
			      अचिन्हित दीर्घ mfrr);
बाह्य पूर्णांक (*__xive_vm_h_cppr)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr);
बाह्य पूर्णांक (*__xive_vm_h_eoi)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr);

/*
 * Common Xive routines क्रम XICS-over-XIVE and XIVE native
 */
व्योम kvmppc_xive_disable_vcpu_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvmppc_xive_debug_show_queues(काष्ठा seq_file *m, काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_xive_debug_show_sources(काष्ठा seq_file *m,
				    काष्ठा kvmppc_xive_src_block *sb);
काष्ठा kvmppc_xive_src_block *kvmppc_xive_create_src_block(
	काष्ठा kvmppc_xive *xive, पूर्णांक irq);
व्योम kvmppc_xive_मुक्त_sources(काष्ठा kvmppc_xive_src_block *sb);
पूर्णांक kvmppc_xive_select_target(काष्ठा kvm *kvm, u32 *server, u8 prio);
पूर्णांक kvmppc_xive_attach_escalation(काष्ठा kvm_vcpu *vcpu, u8 prio,
				  bool single_escalation);
काष्ठा kvmppc_xive *kvmppc_xive_get_device(काष्ठा kvm *kvm, u32 type);
व्योम xive_cleanup_single_escalation(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvmppc_xive_vcpu *xc, पूर्णांक irq);
पूर्णांक kvmppc_xive_compute_vp_id(काष्ठा kvmppc_xive *xive, u32 cpu, u32 *vp);
पूर्णांक kvmppc_xive_set_nr_servers(काष्ठा kvmppc_xive *xive, u64 addr);

#पूर्ण_अगर /* CONFIG_KVM_XICS */
#पूर्ण_अगर /* _KVM_PPC_BOOK3S_XICS_H */
