<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_LAPIC_H
#घोषणा __KVM_X86_LAPIC_H

#समावेश <kvm/iodev.h>

#समावेश <linux/kvm_host.h>

#समावेश "hyperv.h"

#घोषणा KVM_APIC_INIT		0
#घोषणा KVM_APIC_SIPI		1
#घोषणा KVM_APIC_LVT_NUM	6

#घोषणा APIC_SHORT_MASK			0xc0000
#घोषणा APIC_DEST_NOSHORT		0x0
#घोषणा APIC_DEST_MASK			0x800

#घोषणा APIC_BUS_CYCLE_NS       1
#घोषणा APIC_BUS_FREQUENCY      (1000000000ULL / APIC_BUS_CYCLE_NS)

#घोषणा APIC_BROADCAST			0xFF
#घोषणा X2APIC_BROADCAST		0xFFFFFFFFul

क्रमागत lapic_mode अणु
	LAPIC_MODE_DISABLED = 0,
	LAPIC_MODE_INVALID = X2APIC_ENABLE,
	LAPIC_MODE_XAPIC = MSR_IA32_APICBASE_ENABLE,
	LAPIC_MODE_X2APIC = MSR_IA32_APICBASE_ENABLE | X2APIC_ENABLE,
पूर्ण;

काष्ठा kvm_समयr अणु
	काष्ठा hrसमयr समयr;
	s64 period; 				/* unit: ns */
	kसमय_प्रकार target_expiration;
	u32 समयr_mode;
	u32 समयr_mode_mask;
	u64 tscdeadline;
	u64 expired_tscdeadline;
	u32 समयr_advance_ns;
	s64 advance_expire_delta;
	atomic_t pending;			/* accumulated triggered समयrs */
	bool hv_समयr_in_use;
पूर्ण;

काष्ठा kvm_lapic अणु
	अचिन्हित दीर्घ base_address;
	काष्ठा kvm_io_device dev;
	काष्ठा kvm_समयr lapic_समयr;
	u32 भागide_count;
	काष्ठा kvm_vcpu *vcpu;
	bool sw_enabled;
	bool irr_pending;
	bool lvt0_in_nmi_mode;
	/* Number of bits set in ISR. */
	s16 isr_count;
	/* The highest vector set in ISR; अगर -1 - invalid, must scan ISR. */
	पूर्णांक highest_isr_cache;
	/**
	 * APIC रेजिस्टर page.  The layout matches the रेजिस्टर layout seen by
	 * the guest 1:1, because it is accessed by the vmx microcode.
	 * Note: Only one रेजिस्टर, the TPR, is used by the microcode.
	 */
	व्योम *regs;
	gpa_t vapic_addr;
	काष्ठा gfn_to_hva_cache vapic_cache;
	अचिन्हित दीर्घ pending_events;
	अचिन्हित पूर्णांक sipi_vector;
पूर्ण;

काष्ठा dest_map;

पूर्णांक kvm_create_lapic(काष्ठा kvm_vcpu *vcpu, पूर्णांक समयr_advance_ns);
व्योम kvm_मुक्त_lapic(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_apic_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_apic_accept_pic_पूर्णांकr(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_get_apic_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_apic_accept_events(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_reset(काष्ठा kvm_vcpu *vcpu, bool init_event);
u64 kvm_lapic_get_cr8(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_set_tpr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr8);
व्योम kvm_lapic_set_eoi(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_set_base(काष्ठा kvm_vcpu *vcpu, u64 value);
u64 kvm_lapic_get_base(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_recalculate_apic_map(काष्ठा kvm *kvm);
व्योम kvm_apic_set_version(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_lapic_reg_ग_लिखो(काष्ठा kvm_lapic *apic, u32 reg, u32 val);
पूर्णांक kvm_lapic_reg_पढ़ो(काष्ठा kvm_lapic *apic, u32 offset, पूर्णांक len,
		       व्योम *data);
bool kvm_apic_match_dest(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic *source,
			   पूर्णांक लघुhand, अचिन्हित पूर्णांक dest, पूर्णांक dest_mode);
पूर्णांक kvm_apic_compare_prio(काष्ठा kvm_vcpu *vcpu1, काष्ठा kvm_vcpu *vcpu2);
व्योम kvm_apic_clear_irr(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec);
bool __kvm_apic_update_irr(u32 *pir, व्योम *regs, पूर्णांक *max_irr);
bool kvm_apic_update_irr(काष्ठा kvm_vcpu *vcpu, u32 *pir, पूर्णांक *max_irr);
व्योम kvm_apic_update_ppr(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_apic_set_irq(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic_irq *irq,
		     काष्ठा dest_map *dest_map);
पूर्णांक kvm_apic_local_deliver(काष्ठा kvm_lapic *apic, पूर्णांक lvt_type);
व्योम kvm_apic_update_apicv(काष्ठा kvm_vcpu *vcpu);

bool kvm_irq_delivery_to_apic_fast(काष्ठा kvm *kvm, काष्ठा kvm_lapic *src,
		काष्ठा kvm_lapic_irq *irq, पूर्णांक *r, काष्ठा dest_map *dest_map);
व्योम kvm_apic_send_ipi(काष्ठा kvm_lapic *apic, u32 icr_low, u32 icr_high);

u64 kvm_get_apic_base(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_set_apic_base(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info);
पूर्णांक kvm_apic_get_state(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic_state *s);
पूर्णांक kvm_apic_set_state(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic_state *s);
क्रमागत lapic_mode kvm_get_apic_mode(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_lapic_find_highest_irr(काष्ठा kvm_vcpu *vcpu);

u64 kvm_get_lapic_tscdeadline_msr(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_set_lapic_tscdeadline_msr(काष्ठा kvm_vcpu *vcpu, u64 data);

व्योम kvm_apic_ग_लिखो_nodecode(काष्ठा kvm_vcpu *vcpu, u32 offset);
व्योम kvm_apic_set_eoi_accelerated(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector);

पूर्णांक kvm_lapic_set_vapic_addr(काष्ठा kvm_vcpu *vcpu, gpa_t vapic_addr);
व्योम kvm_lapic_sync_from_vapic(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_sync_to_vapic(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_x2apic_msr_ग_लिखो(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data);
पूर्णांक kvm_x2apic_msr_पढ़ो(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *data);

पूर्णांक kvm_hv_vapic_msr_ग_लिखो(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data);
पूर्णांक kvm_hv_vapic_msr_पढ़ो(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *data);

पूर्णांक kvm_lapic_enable_pv_eoi(काष्ठा kvm_vcpu *vcpu, u64 data, अचिन्हित दीर्घ len);
व्योम kvm_lapic_निकास(व्योम);

#घोषणा VEC_POS(v) ((v) & (32 - 1))
#घोषणा REG_POS(v) (((v) >> 5) << 4)

अटल अंतरभूत व्योम kvm_lapic_clear_vector(पूर्णांक vec, व्योम *biपंचांगap)
अणु
	clear_bit(VEC_POS(vec), (biपंचांगap) + REG_POS(vec));
पूर्ण

अटल अंतरभूत व्योम kvm_lapic_set_vector(पूर्णांक vec, व्योम *biपंचांगap)
अणु
	set_bit(VEC_POS(vec), (biपंचांगap) + REG_POS(vec));
पूर्ण

अटल अंतरभूत व्योम kvm_lapic_set_irr(पूर्णांक vec, काष्ठा kvm_lapic *apic)
अणु
	kvm_lapic_set_vector(vec, apic->regs + APIC_IRR);
	/*
	 * irr_pending must be true अगर any पूर्णांकerrupt is pending; set it after
	 * APIC_IRR to aव्योम race with apic_clear_irr
	 */
	apic->irr_pending = true;
पूर्ण

अटल अंतरभूत u32 kvm_lapic_get_reg(काष्ठा kvm_lapic *apic, पूर्णांक reg_off)
अणु
	वापस *((u32 *) (apic->regs + reg_off));
पूर्ण

अटल अंतरभूत व्योम __kvm_lapic_set_reg(अक्षर *regs, पूर्णांक reg_off, u32 val)
अणु
	*((u32 *) (regs + reg_off)) = val;
पूर्ण

अटल अंतरभूत व्योम kvm_lapic_set_reg(काष्ठा kvm_lapic *apic, पूर्णांक reg_off, u32 val)
अणु
	__kvm_lapic_set_reg(apic->regs, reg_off, val);
पूर्ण

DECLARE_STATIC_KEY_FALSE(kvm_has_noapic_vcpu);

अटल अंतरभूत bool lapic_in_kernel(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (अटल_branch_unlikely(&kvm_has_noapic_vcpu))
		वापस vcpu->arch.apic;
	वापस true;
पूर्ण

बाह्य काष्ठा अटल_key_false_deferred apic_hw_disabled;

अटल अंतरभूत पूर्णांक kvm_apic_hw_enabled(काष्ठा kvm_lapic *apic)
अणु
	अगर (अटल_branch_unlikely(&apic_hw_disabled.key))
		वापस apic->vcpu->arch.apic_base & MSR_IA32_APICBASE_ENABLE;
	वापस MSR_IA32_APICBASE_ENABLE;
पूर्ण

बाह्य काष्ठा अटल_key_false_deferred apic_sw_disabled;

अटल अंतरभूत bool kvm_apic_sw_enabled(काष्ठा kvm_lapic *apic)
अणु
	अगर (अटल_branch_unlikely(&apic_sw_disabled.key))
		वापस apic->sw_enabled;
	वापस true;
पूर्ण

अटल अंतरभूत bool kvm_apic_present(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस lapic_in_kernel(vcpu) && kvm_apic_hw_enabled(vcpu->arch.apic);
पूर्ण

अटल अंतरभूत पूर्णांक kvm_lapic_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_apic_present(vcpu) && kvm_apic_sw_enabled(vcpu->arch.apic);
पूर्ण

अटल अंतरभूत पूर्णांक apic_x2apic_mode(काष्ठा kvm_lapic *apic)
अणु
	वापस apic->vcpu->arch.apic_base & X2APIC_ENABLE;
पूर्ण

अटल अंतरभूत bool kvm_vcpu_apicv_active(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.apic && vcpu->arch.apicv_active;
पूर्ण

अटल अंतरभूत bool kvm_apic_has_events(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस lapic_in_kernel(vcpu) && vcpu->arch.apic->pending_events;
पूर्ण

अटल अंतरभूत bool kvm_lowest_prio_delivery(काष्ठा kvm_lapic_irq *irq)
अणु
	वापस (irq->delivery_mode == APIC_DM_LOWEST ||
			irq->msi_redir_hपूर्णांक);
पूर्ण

अटल अंतरभूत पूर्णांक kvm_lapic_latched_init(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस lapic_in_kernel(vcpu) && test_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
पूर्ण

bool kvm_apic_pending_eoi(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector);

व्योम kvm_रुको_lapic_expire(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_biपंचांगap_or_dest_vcpus(काष्ठा kvm *kvm, काष्ठा kvm_lapic_irq *irq,
			      अचिन्हित दीर्घ *vcpu_biपंचांगap);

bool kvm_पूर्णांकr_is_single_vcpu_fast(काष्ठा kvm *kvm, काष्ठा kvm_lapic_irq *irq,
			काष्ठा kvm_vcpu **dest_vcpu);
पूर्णांक kvm_vector_to_index(u32 vector, u32 dest_vcpus,
			स्थिर अचिन्हित दीर्घ *biपंचांगap, u32 biपंचांगap_size);
व्योम kvm_lapic_चयन_to_sw_समयr(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_चयन_to_hv_समयr(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_expired_hv_समयr(काष्ठा kvm_vcpu *vcpu);
bool kvm_lapic_hv_समयr_in_use(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lapic_restart_hv_समयr(काष्ठा kvm_vcpu *vcpu);
bool kvm_can_use_hv_समयr(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत क्रमागत lapic_mode kvm_apic_mode(u64 apic_base)
अणु
	वापस apic_base & (MSR_IA32_APICBASE_ENABLE | X2APIC_ENABLE);
पूर्ण

अटल अंतरभूत u8 kvm_xapic_id(काष्ठा kvm_lapic *apic)
अणु
	वापस kvm_lapic_get_reg(apic, APIC_ID) >> 24;
पूर्ण

#पूर्ण_अगर
