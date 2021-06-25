<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#अगर_अघोषित __KVM_BOOKE_H__
#घोषणा __KVM_BOOKE_H__

#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश "timing.h"

/* पूर्णांकerrupt priortity ordering */
#घोषणा BOOKE_IRQPRIO_DATA_STORAGE 0
#घोषणा BOOKE_IRQPRIO_INST_STORAGE 1
#घोषणा BOOKE_IRQPRIO_ALIGNMENT 2
#घोषणा BOOKE_IRQPRIO_PROGRAM 3
#घोषणा BOOKE_IRQPRIO_FP_UNAVAIL 4
#अगर_घोषित CONFIG_SPE_POSSIBLE
#घोषणा BOOKE_IRQPRIO_SPE_UNAVAIL 5
#घोषणा BOOKE_IRQPRIO_SPE_FP_DATA 6
#घोषणा BOOKE_IRQPRIO_SPE_FP_ROUND 7
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_E500MC
#घोषणा BOOKE_IRQPRIO_ALTIVEC_UNAVAIL 5
#घोषणा BOOKE_IRQPRIO_ALTIVEC_ASSIST 6
#पूर्ण_अगर
#घोषणा BOOKE_IRQPRIO_SYSCALL 8
#घोषणा BOOKE_IRQPRIO_AP_UNAVAIL 9
#घोषणा BOOKE_IRQPRIO_DTLB_MISS 10
#घोषणा BOOKE_IRQPRIO_ITLB_MISS 11
#घोषणा BOOKE_IRQPRIO_MACHINE_CHECK 12
#घोषणा BOOKE_IRQPRIO_DEBUG 13
#घोषणा BOOKE_IRQPRIO_CRITICAL 14
#घोषणा BOOKE_IRQPRIO_WATCHDOG 15
#घोषणा BOOKE_IRQPRIO_EXTERNAL 16
#घोषणा BOOKE_IRQPRIO_FIT 17
#घोषणा BOOKE_IRQPRIO_DECREMENTER 18
#घोषणा BOOKE_IRQPRIO_PERFORMANCE_MONITOR 19
/* Internal pseuकरो-irqprio क्रम level triggered बाह्यals */
#घोषणा BOOKE_IRQPRIO_EXTERNAL_LEVEL 20
#घोषणा BOOKE_IRQPRIO_DBELL 21
#घोषणा BOOKE_IRQPRIO_DBELL_CRIT 22
#घोषणा BOOKE_IRQPRIO_MAX 23

#घोषणा BOOKE_IRQMASK_EE ((1 << BOOKE_IRQPRIO_EXTERNAL_LEVEL) | \
			  (1 << BOOKE_IRQPRIO_PERFORMANCE_MONITOR) | \
			  (1 << BOOKE_IRQPRIO_DBELL) | \
			  (1 << BOOKE_IRQPRIO_DECREMENTER) | \
			  (1 << BOOKE_IRQPRIO_FIT) | \
			  (1 << BOOKE_IRQPRIO_EXTERNAL))

#घोषणा BOOKE_IRQMASK_CE ((1 << BOOKE_IRQPRIO_DBELL_CRIT) | \
			  (1 << BOOKE_IRQPRIO_WATCHDOG) | \
			  (1 << BOOKE_IRQPRIO_CRITICAL))

बाह्य अचिन्हित दीर्घ kvmppc_booke_handlers;
बाह्य अचिन्हित दीर्घ kvmppc_booke_handler_addr[];

व्योम kvmppc_set_msr(काष्ठा kvm_vcpu *vcpu, u32 new_msr);
व्योम kvmppc_mmu_msr_notअगरy(काष्ठा kvm_vcpu *vcpu, u32 old_msr);

व्योम kvmppc_set_epcr(काष्ठा kvm_vcpu *vcpu, u32 new_epcr);
व्योम kvmppc_set_tcr(काष्ठा kvm_vcpu *vcpu, u32 new_tcr);
व्योम kvmppc_set_tsr_bits(काष्ठा kvm_vcpu *vcpu, u32 tsr_bits);
व्योम kvmppc_clr_tsr_bits(काष्ठा kvm_vcpu *vcpu, u32 tsr_bits);

पूर्णांक kvmppc_booke_emulate_op(काष्ठा kvm_vcpu *vcpu,
                            अचिन्हित पूर्णांक inst, पूर्णांक *advance);
पूर्णांक kvmppc_booke_emulate_mfspr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ *spr_val);
पूर्णांक kvmppc_booke_emulate_mtspr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ spr_val);

/* low-level यंत्र code to transfer guest state */
व्योम kvmppc_load_guest_spe(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_save_guest_spe(काष्ठा kvm_vcpu *vcpu);

/* high-level function, manages flags, host state */
व्योम kvmppc_vcpu_disable_spe(काष्ठा kvm_vcpu *vcpu);

व्योम kvmppc_booke_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
व्योम kvmppc_booke_vcpu_put(काष्ठा kvm_vcpu *vcpu);

क्रमागत पूर्णांक_class अणु
	INT_CLASS_NONCRIT,
	INT_CLASS_CRIT,
	INT_CLASS_MC,
	INT_CLASS_DBG,
पूर्ण;

व्योम kvmppc_set_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, क्रमागत पूर्णांक_class type);

बाह्य पूर्णांक kvmppc_core_emulate_op_e500(काष्ठा kvm_vcpu *vcpu,
				       अचिन्हित पूर्णांक inst, पूर्णांक *advance);
बाह्य पूर्णांक kvmppc_core_emulate_mtspr_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn,
					  uदीर्घ spr_val);
बाह्य पूर्णांक kvmppc_core_emulate_mfspr_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn,
					  uदीर्घ *spr_val);
बाह्य पूर्णांक kvmppc_core_emulate_mtspr_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn,
					  uदीर्घ spr_val);
बाह्य पूर्णांक kvmppc_core_emulate_mfspr_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn,
					  uदीर्घ *spr_val);

अटल अंतरभूत व्योम kvmppc_clear_dbsr(व्योम)
अणु
	mtspr(SPRN_DBSR, mfspr(SPRN_DBSR));
पूर्ण
#पूर्ण_अगर /* __KVM_BOOKE_H__ */
