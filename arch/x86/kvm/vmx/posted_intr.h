<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_POSTED_INTR_H
#घोषणा __KVM_X86_VMX_POSTED_INTR_H

#घोषणा POSTED_INTR_ON  0
#घोषणा POSTED_INTR_SN  1

/* Posted-Interrupt Descriptor */
काष्ठा pi_desc अणु
	u32 pir[8];     /* Posted पूर्णांकerrupt requested */
	जोड़ अणु
		काष्ठा अणु
				/* bit 256 - Outstanding Notअगरication */
			u16	on	: 1,
				/* bit 257 - Suppress Notअगरication */
				sn	: 1,
				/* bit 271:258 - Reserved */
				rsvd_1	: 14;
				/* bit 279:272 - Notअगरication Vector */
			u8	nv;
				/* bit 287:280 - Reserved */
			u8	rsvd_2;
				/* bit 319:288 - Notअगरication Destination */
			u32	ndst;
		पूर्ण;
		u64 control;
	पूर्ण;
	u32 rsvd[6];
पूर्ण __aligned(64);

अटल अंतरभूत bool pi_test_and_set_on(काष्ठा pi_desc *pi_desc)
अणु
	वापस test_and_set_bit(POSTED_INTR_ON,
			(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत bool pi_test_and_clear_on(काष्ठा pi_desc *pi_desc)
अणु
	वापस test_and_clear_bit(POSTED_INTR_ON,
			(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत पूर्णांक pi_test_and_set_pir(पूर्णांक vector, काष्ठा pi_desc *pi_desc)
अणु
	वापस test_and_set_bit(vector, (अचिन्हित दीर्घ *)pi_desc->pir);
पूर्ण

अटल अंतरभूत bool pi_is_pir_empty(काष्ठा pi_desc *pi_desc)
अणु
	वापस biपंचांगap_empty((अचिन्हित दीर्घ *)pi_desc->pir, NR_VECTORS);
पूर्ण

अटल अंतरभूत व्योम pi_set_sn(काष्ठा pi_desc *pi_desc)
अणु
	set_bit(POSTED_INTR_SN,
		(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत व्योम pi_set_on(काष्ठा pi_desc *pi_desc)
अणु
	set_bit(POSTED_INTR_ON,
		(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत व्योम pi_clear_on(काष्ठा pi_desc *pi_desc)
अणु
	clear_bit(POSTED_INTR_ON,
		(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत व्योम pi_clear_sn(काष्ठा pi_desc *pi_desc)
अणु
	clear_bit(POSTED_INTR_SN,
		(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत पूर्णांक pi_test_on(काष्ठा pi_desc *pi_desc)
अणु
	वापस test_bit(POSTED_INTR_ON,
			(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

अटल अंतरभूत पूर्णांक pi_test_sn(काष्ठा pi_desc *pi_desc)
अणु
	वापस test_bit(POSTED_INTR_SN,
			(अचिन्हित दीर्घ *)&pi_desc->control);
पूर्ण

व्योम vmx_vcpu_pi_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
व्योम vmx_vcpu_pi_put(काष्ठा kvm_vcpu *vcpu);
पूर्णांक pi_pre_block(काष्ठा kvm_vcpu *vcpu);
व्योम pi_post_block(काष्ठा kvm_vcpu *vcpu);
व्योम pi_wakeup_handler(व्योम);
व्योम __init pi_init_cpu(पूर्णांक cpu);
bool pi_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक pi_update_irte(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq, uपूर्णांक32_t guest_irq,
		   bool set);
व्योम vmx_pi_start_assignment(काष्ठा kvm *kvm);

#पूर्ण_अगर /* __KVM_X86_VMX_POSTED_INTR_H */
