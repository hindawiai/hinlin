<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * handling kvm guest पूर्णांकerrupts
 *
 * Copyright IBM Corp. 2008, 2020
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "kvm-s390"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/nospec.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/dis.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/airq.h>
#समावेश "kvm-s390.h"
#समावेश "gaccess.h"
#समावेश "trace-s390.h"

#घोषणा PFAULT_INIT 0x0600
#घोषणा PFAULT_DONE 0x0680
#घोषणा VIRTIO_PARAM 0x0d00

अटल काष्ठा kvm_s390_gib *gib;

/* handle बाह्यal calls via sigp पूर्णांकerpretation facility */
अटल पूर्णांक sca_ext_call_pending(काष्ठा kvm_vcpu *vcpu, पूर्णांक *src_id)
अणु
	पूर्णांक c, scn;

	अगर (!kvm_s390_test_cpuflags(vcpu, CPUSTAT_ECALL_PEND))
		वापस 0;

	BUG_ON(!kvm_s390_use_sca_entries());
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	अगर (vcpu->kvm->arch.use_esca) अणु
		काष्ठा esca_block *sca = vcpu->kvm->arch.sca;
		जोड़ esca_sigp_ctrl sigp_ctrl =
			sca->cpu[vcpu->vcpu_id].sigp_ctrl;

		c = sigp_ctrl.c;
		scn = sigp_ctrl.scn;
	पूर्ण अन्यथा अणु
		काष्ठा bsca_block *sca = vcpu->kvm->arch.sca;
		जोड़ bsca_sigp_ctrl sigp_ctrl =
			sca->cpu[vcpu->vcpu_id].sigp_ctrl;

		c = sigp_ctrl.c;
		scn = sigp_ctrl.scn;
	पूर्ण
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);

	अगर (src_id)
		*src_id = scn;

	वापस c;
पूर्ण

अटल पूर्णांक sca_inject_ext_call(काष्ठा kvm_vcpu *vcpu, पूर्णांक src_id)
अणु
	पूर्णांक expect, rc;

	BUG_ON(!kvm_s390_use_sca_entries());
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	अगर (vcpu->kvm->arch.use_esca) अणु
		काष्ठा esca_block *sca = vcpu->kvm->arch.sca;
		जोड़ esca_sigp_ctrl *sigp_ctrl =
			&(sca->cpu[vcpu->vcpu_id].sigp_ctrl);
		जोड़ esca_sigp_ctrl new_val = अणु0पूर्ण, old_val = *sigp_ctrl;

		new_val.scn = src_id;
		new_val.c = 1;
		old_val.c = 0;

		expect = old_val.value;
		rc = cmpxchg(&sigp_ctrl->value, old_val.value, new_val.value);
	पूर्ण अन्यथा अणु
		काष्ठा bsca_block *sca = vcpu->kvm->arch.sca;
		जोड़ bsca_sigp_ctrl *sigp_ctrl =
			&(sca->cpu[vcpu->vcpu_id].sigp_ctrl);
		जोड़ bsca_sigp_ctrl new_val = अणु0पूर्ण, old_val = *sigp_ctrl;

		new_val.scn = src_id;
		new_val.c = 1;
		old_val.c = 0;

		expect = old_val.value;
		rc = cmpxchg(&sigp_ctrl->value, old_val.value, new_val.value);
	पूर्ण
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);

	अगर (rc != expect) अणु
		/* another बाह्यal call is pending */
		वापस -EBUSY;
	पूर्ण
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_ECALL_PEND);
	वापस 0;
पूर्ण

अटल व्योम sca_clear_ext_call(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc, expect;

	अगर (!kvm_s390_use_sca_entries())
		वापस;
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_ECALL_PEND);
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	अगर (vcpu->kvm->arch.use_esca) अणु
		काष्ठा esca_block *sca = vcpu->kvm->arch.sca;
		जोड़ esca_sigp_ctrl *sigp_ctrl =
			&(sca->cpu[vcpu->vcpu_id].sigp_ctrl);
		जोड़ esca_sigp_ctrl old = *sigp_ctrl;

		expect = old.value;
		rc = cmpxchg(&sigp_ctrl->value, old.value, 0);
	पूर्ण अन्यथा अणु
		काष्ठा bsca_block *sca = vcpu->kvm->arch.sca;
		जोड़ bsca_sigp_ctrl *sigp_ctrl =
			&(sca->cpu[vcpu->vcpu_id].sigp_ctrl);
		जोड़ bsca_sigp_ctrl old = *sigp_ctrl;

		expect = old.value;
		rc = cmpxchg(&sigp_ctrl->value, old.value, 0);
	पूर्ण
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
	WARN_ON(rc != expect); /* cannot clear? */
पूर्ण

पूर्णांक psw_extपूर्णांक_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !(vcpu->arch.sie_block->gpsw.mask & PSW_MASK_EXT);
पूर्ण

अटल पूर्णांक psw_ioपूर्णांक_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !(vcpu->arch.sie_block->gpsw.mask & PSW_MASK_IO);
पूर्ण

अटल पूर्णांक psw_mchk_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !(vcpu->arch.sie_block->gpsw.mask & PSW_MASK_MCHECK);
पूर्ण

अटल पूर्णांक psw_पूर्णांकerrupts_disabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस psw_extपूर्णांक_disabled(vcpu) &&
	       psw_ioपूर्णांक_disabled(vcpu) &&
	       psw_mchk_disabled(vcpu);
पूर्ण

अटल पूर्णांक ckc_पूर्णांकerrupts_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (psw_extपूर्णांक_disabled(vcpu) ||
	    !(vcpu->arch.sie_block->gcr[0] & CR0_CLOCK_COMPARATOR_SUBMASK))
		वापस 0;
	अगर (guestdbg_enabled(vcpu) && guestdbg_sstep_enabled(vcpu))
		/* No समयr पूर्णांकerrupts when single stepping */
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ckc_irq_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर u64 now = kvm_s390_get_tod_घड़ी_fast(vcpu->kvm);
	स्थिर u64 ckc = vcpu->arch.sie_block->ckc;

	अगर (vcpu->arch.sie_block->gcr[0] & CR0_CLOCK_COMPARATOR_SIGN) अणु
		अगर ((s64)ckc >= (s64)now)
			वापस 0;
	पूर्ण अन्यथा अगर (ckc >= now) अणु
		वापस 0;
	पूर्ण
	वापस ckc_पूर्णांकerrupts_enabled(vcpu);
पूर्ण

अटल पूर्णांक cpu_समयr_पूर्णांकerrupts_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !psw_extपूर्णांक_disabled(vcpu) &&
	       (vcpu->arch.sie_block->gcr[0] & CR0_CPU_TIMER_SUBMASK);
पूर्ण

अटल पूर्णांक cpu_समयr_irq_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!cpu_समयr_पूर्णांकerrupts_enabled(vcpu))
		वापस 0;
	वापस kvm_s390_get_cpu_समयr(vcpu) >> 63;
पूर्ण

अटल uपूर्णांक64_t isc_to_isc_bits(पूर्णांक isc)
अणु
	वापस (0x80 >> isc) << 24;
पूर्ण

अटल अंतरभूत u32 isc_to_पूर्णांक_word(u8 isc)
अणु
	वापस ((u32)isc << 27) | 0x80000000;
पूर्ण

अटल अंतरभूत u8 पूर्णांक_word_to_isc(u32 पूर्णांक_word)
अणु
	वापस (पूर्णांक_word & 0x38000000) >> 27;
पूर्ण

/*
 * To use atomic biपंचांगap functions, we have to provide a biपंचांगap address
 * that is u64 aligned. However, the ipm might be u32 aligned.
 * Thereक्रमe, we logically start the biपंचांगap at the very beginning of the
 * काष्ठा and fixup the bit number.
 */
#घोषणा IPM_BIT_OFFSET (दुरत्व(काष्ठा kvm_s390_gisa, ipm) * BITS_PER_BYTE)

/**
 * gisa_set_iam - change the GISA पूर्णांकerruption alert mask
 *
 * @gisa: gisa to operate on
 * @iam: new IAM value to use
 *
 * Change the IAM atomically with the next alert address and the IPM
 * of the GISA अगर the GISA is not part of the GIB alert list. All three
 * fields are located in the first दीर्घ word of the GISA.
 *
 * Returns: 0 on success
 *          -EBUSY in हाल the gisa is part of the alert list
 */
अटल अंतरभूत पूर्णांक gisa_set_iam(काष्ठा kvm_s390_gisa *gisa, u8 iam)
अणु
	u64 word, _word;

	करो अणु
		word = READ_ONCE(gisa->u64.word[0]);
		अगर ((u64)gisa != word >> 32)
			वापस -EBUSY;
		_word = (word & ~0xffUL) | iam;
	पूर्ण जबतक (cmpxchg(&gisa->u64.word[0], word, _word) != word);

	वापस 0;
पूर्ण

/**
 * gisa_clear_ipm - clear the GISA पूर्णांकerruption pending mask
 *
 * @gisa: gisa to operate on
 *
 * Clear the IPM atomically with the next alert address and the IAM
 * of the GISA unconditionally. All three fields are located in the
 * first दीर्घ word of the GISA.
 */
अटल अंतरभूत व्योम gisa_clear_ipm(काष्ठा kvm_s390_gisa *gisa)
अणु
	u64 word, _word;

	करो अणु
		word = READ_ONCE(gisa->u64.word[0]);
		_word = word & ~(0xffUL << 24);
	पूर्ण जबतक (cmpxchg(&gisa->u64.word[0], word, _word) != word);
पूर्ण

/**
 * gisa_get_ipm_or_restore_iam - वापस IPM or restore GISA IAM
 *
 * @gi: gisa पूर्णांकerrupt काष्ठा to work on
 *
 * Atomically restores the पूर्णांकerruption alert mask अगर none of the
 * relevant ISCs are pending and वापस the IPM.
 *
 * Returns: the relevant pending ISCs
 */
अटल अंतरभूत u8 gisa_get_ipm_or_restore_iam(काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi)
अणु
	u8 pending_mask, alert_mask;
	u64 word, _word;

	करो अणु
		word = READ_ONCE(gi->origin->u64.word[0]);
		alert_mask = READ_ONCE(gi->alert.mask);
		pending_mask = (u8)(word >> 24) & alert_mask;
		अगर (pending_mask)
			वापस pending_mask;
		_word = (word & ~0xffUL) | alert_mask;
	पूर्ण जबतक (cmpxchg(&gi->origin->u64.word[0], word, _word) != word);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gisa_in_alert_list(काष्ठा kvm_s390_gisa *gisa)
अणु
	वापस READ_ONCE(gisa->next_alert) != (u32)(u64)gisa;
पूर्ण

अटल अंतरभूत व्योम gisa_set_ipm_gisc(काष्ठा kvm_s390_gisa *gisa, u32 gisc)
अणु
	set_bit_inv(IPM_BIT_OFFSET + gisc, (अचिन्हित दीर्घ *) gisa);
पूर्ण

अटल अंतरभूत u8 gisa_get_ipm(काष्ठा kvm_s390_gisa *gisa)
अणु
	वापस READ_ONCE(gisa->ipm);
पूर्ण

अटल अंतरभूत व्योम gisa_clear_ipm_gisc(काष्ठा kvm_s390_gisa *gisa, u32 gisc)
अणु
	clear_bit_inv(IPM_BIT_OFFSET + gisc, (अचिन्हित दीर्घ *) gisa);
पूर्ण

अटल अंतरभूत पूर्णांक gisa_tac_ipm_gisc(काष्ठा kvm_s390_gisa *gisa, u32 gisc)
अणु
	वापस test_and_clear_bit_inv(IPM_BIT_OFFSET + gisc, (अचिन्हित दीर्घ *) gisa);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pending_irqs_no_gisa(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ pending = vcpu->kvm->arch.भग्न_पूर्णांक.pending_irqs |
				vcpu->arch.local_पूर्णांक.pending_irqs;

	pending &= ~vcpu->kvm->arch.भग्न_पूर्णांक.masked_irqs;
	वापस pending;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pending_irqs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &vcpu->kvm->arch.gisa_पूर्णांक;
	अचिन्हित दीर्घ pending_mask;

	pending_mask = pending_irqs_no_gisa(vcpu);
	अगर (gi->origin)
		pending_mask |= gisa_get_ipm(gi->origin) << IRQ_PEND_IO_ISC_7;
	वापस pending_mask;
पूर्ण

अटल अंतरभूत पूर्णांक isc_to_irq_type(अचिन्हित दीर्घ isc)
अणु
	वापस IRQ_PEND_IO_ISC_0 - isc;
पूर्ण

अटल अंतरभूत पूर्णांक irq_type_to_isc(अचिन्हित दीर्घ irq_type)
अणु
	वापस IRQ_PEND_IO_ISC_0 - irq_type;
पूर्ण

अटल अचिन्हित दीर्घ disable_iscs(काष्ठा kvm_vcpu *vcpu,
				   अचिन्हित दीर्घ active_mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= MAX_ISC; i++)
		अगर (!(vcpu->arch.sie_block->gcr[6] & isc_to_isc_bits(i)))
			active_mask &= ~(1UL << (isc_to_irq_type(i)));

	वापस active_mask;
पूर्ण

अटल अचिन्हित दीर्घ deliverable_irqs(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ active_mask;

	active_mask = pending_irqs(vcpu);
	अगर (!active_mask)
		वापस 0;

	अगर (psw_extपूर्णांक_disabled(vcpu))
		active_mask &= ~IRQ_PEND_EXT_MASK;
	अगर (psw_ioपूर्णांक_disabled(vcpu))
		active_mask &= ~IRQ_PEND_IO_MASK;
	अन्यथा
		active_mask = disable_iscs(vcpu, active_mask);
	अगर (!(vcpu->arch.sie_block->gcr[0] & CR0_EXTERNAL_CALL_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_EXTERNAL, &active_mask);
	अगर (!(vcpu->arch.sie_block->gcr[0] & CR0_EMERGENCY_SIGNAL_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_EMERGENCY, &active_mask);
	अगर (!(vcpu->arch.sie_block->gcr[0] & CR0_CLOCK_COMPARATOR_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_CLOCK_COMP, &active_mask);
	अगर (!(vcpu->arch.sie_block->gcr[0] & CR0_CPU_TIMER_SUBMASK))
		__clear_bit(IRQ_PEND_EXT_CPU_TIMER, &active_mask);
	अगर (!(vcpu->arch.sie_block->gcr[0] & CR0_SERVICE_SIGNAL_SUBMASK)) अणु
		__clear_bit(IRQ_PEND_EXT_SERVICE, &active_mask);
		__clear_bit(IRQ_PEND_EXT_SERVICE_EV, &active_mask);
	पूर्ण
	अगर (psw_mchk_disabled(vcpu))
		active_mask &= ~IRQ_PEND_MCHK_MASK;
	/* PV guest cpus can have a single पूर्णांकerruption injected at a समय. */
	अगर (kvm_s390_pv_cpu_get_handle(vcpu) &&
	    vcpu->arch.sie_block->iictl != IICTL_CODE_NONE)
		active_mask &= ~(IRQ_PEND_EXT_II_MASK |
				 IRQ_PEND_IO_MASK |
				 IRQ_PEND_MCHK_MASK);
	/*
	 * Check both भग्नing and local पूर्णांकerrupt's cr14 because
	 * bit IRQ_PEND_MCHK_REP could be set in both हालs.
	 */
	अगर (!(vcpu->arch.sie_block->gcr[14] &
	   (vcpu->kvm->arch.भग्न_पूर्णांक.mchk.cr14 |
	   vcpu->arch.local_पूर्णांक.irq.mchk.cr14)))
		__clear_bit(IRQ_PEND_MCHK_REP, &active_mask);

	/*
	 * STOP irqs will never be actively delivered. They are triggered via
	 * पूर्णांकercept requests and cleared when the stop पूर्णांकercept is perक्रमmed.
	 */
	__clear_bit(IRQ_PEND_SIGP_STOP, &active_mask);

	वापस active_mask;
पूर्ण

अटल व्योम __set_cpu_idle(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_WAIT);
	set_bit(vcpu->vcpu_id, vcpu->kvm->arch.idle_mask);
पूर्ण

अटल व्योम __unset_cpu_idle(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_WAIT);
	clear_bit(vcpu->vcpu_id, vcpu->kvm->arch.idle_mask);
पूर्ण

अटल व्योम __reset_पूर्णांकercept_indicators(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_IO_INT | CPUSTAT_EXT_INT |
				      CPUSTAT_STOP_INT);
	vcpu->arch.sie_block->lctl = 0x0000;
	vcpu->arch.sie_block->ictl &= ~(ICTL_LPSW | ICTL_STCTL | ICTL_PINT);

	अगर (guestdbg_enabled(vcpu)) अणु
		vcpu->arch.sie_block->lctl |= (LCTL_CR0 | LCTL_CR9 |
					       LCTL_CR10 | LCTL_CR11);
		vcpu->arch.sie_block->ictl |= (ICTL_STCTL | ICTL_PINT);
	पूर्ण
पूर्ण

अटल व्योम set_पूर्णांकercept_indicators_io(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(pending_irqs_no_gisa(vcpu) & IRQ_PEND_IO_MASK))
		वापस;
	अगर (psw_ioपूर्णांक_disabled(vcpu))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_IO_INT);
	अन्यथा
		vcpu->arch.sie_block->lctl |= LCTL_CR6;
पूर्ण

अटल व्योम set_पूर्णांकercept_indicators_ext(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(pending_irqs_no_gisa(vcpu) & IRQ_PEND_EXT_MASK))
		वापस;
	अगर (psw_extपूर्णांक_disabled(vcpu))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_EXT_INT);
	अन्यथा
		vcpu->arch.sie_block->lctl |= LCTL_CR0;
पूर्ण

अटल व्योम set_पूर्णांकercept_indicators_mchk(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(pending_irqs_no_gisa(vcpu) & IRQ_PEND_MCHK_MASK))
		वापस;
	अगर (psw_mchk_disabled(vcpu))
		vcpu->arch.sie_block->ictl |= ICTL_LPSW;
	अन्यथा
		vcpu->arch.sie_block->lctl |= LCTL_CR14;
पूर्ण

अटल व्योम set_पूर्णांकercept_indicators_stop(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_s390_is_stop_irq_pending(vcpu))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOP_INT);
पूर्ण

/* Set पूर्णांकerception request क्रम non-deliverable पूर्णांकerrupts */
अटल व्योम set_पूर्णांकercept_indicators(काष्ठा kvm_vcpu *vcpu)
अणु
	set_पूर्णांकercept_indicators_io(vcpu);
	set_पूर्णांकercept_indicators_ext(vcpu);
	set_पूर्णांकercept_indicators_mchk(vcpu);
	set_पूर्णांकercept_indicators_stop(vcpu);
पूर्ण

अटल पूर्णांक __must_check __deliver_cpu_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc = 0;

	vcpu->stat.deliver_cpuपंचांग++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_INT_CPU_TIMER,
					 0, 0);
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_EXT;
		vcpu->arch.sie_block->eic = EXT_IRQ_CPU_TIMER;
	पूर्ण अन्यथा अणु
		rc  = put_guest_lc(vcpu, EXT_IRQ_CPU_TIMER,
				   (u16 *)__LC_EXT_INT_CODE);
		rc |= put_guest_lc(vcpu, 0, (u16 *)__LC_EXT_CPU_ADDR);
		rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
				     &vcpu->arch.sie_block->gpsw, माप(psw_t));
		rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
				    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	पूर्ण
	clear_bit(IRQ_PEND_EXT_CPU_TIMER, &li->pending_irqs);
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_ckc(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc = 0;

	vcpu->stat.deliver_ckc++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_INT_CLOCK_COMP,
					 0, 0);
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_EXT;
		vcpu->arch.sie_block->eic = EXT_IRQ_CLK_COMP;
	पूर्ण अन्यथा अणु
		rc  = put_guest_lc(vcpu, EXT_IRQ_CLK_COMP,
				   (u16 __user *)__LC_EXT_INT_CODE);
		rc |= put_guest_lc(vcpu, 0, (u16 *)__LC_EXT_CPU_ADDR);
		rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
				     &vcpu->arch.sie_block->gpsw, माप(psw_t));
		rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
				    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	पूर्ण
	clear_bit(IRQ_PEND_EXT_CLOCK_COMP, &li->pending_irqs);
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_pfault_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_ext_info ext;
	पूर्णांक rc;

	spin_lock(&li->lock);
	ext = li->irq.ext;
	clear_bit(IRQ_PEND_PFAULT_INIT, &li->pending_irqs);
	li->irq.ext.ext_params2 = 0;
	spin_unlock(&li->lock);

	VCPU_EVENT(vcpu, 4, "deliver: pfault init token 0x%llx",
		   ext.ext_params2);
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
					 KVM_S390_INT_PFAULT_INIT,
					 0, ext.ext_params2);

	rc  = put_guest_lc(vcpu, EXT_IRQ_CP_SERVICE, (u16 *) __LC_EXT_INT_CODE);
	rc |= put_guest_lc(vcpu, PFAULT_INIT, (u16 *) __LC_EXT_CPU_ADDR);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
			    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= put_guest_lc(vcpu, ext.ext_params2, (u64 *) __LC_EXT_PARAMS2);
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __ग_लिखो_machine_check(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_s390_mchk_info *mchk)
अणु
	अचिन्हित दीर्घ ext_sa_addr;
	अचिन्हित दीर्घ lc;
	freg_t fprs[NUM_FPRS];
	जोड़ mci mci;
	पूर्णांक rc;

	/*
	 * All other possible payload क्रम a machine check (e.g. the रेजिस्टर
	 * contents in the save area) will be handled by the ultravisor, as
	 * the hypervisor करोes not not have the needed inक्रमmation क्रम
	 * रक्षित guests.
	 */
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_MCHK;
		vcpu->arch.sie_block->mcic = mchk->mcic;
		vcpu->arch.sie_block->faddr = mchk->failing_storage_address;
		vcpu->arch.sie_block->edc = mchk->ext_damage_code;
		वापस 0;
	पूर्ण

	mci.val = mchk->mcic;
	/* take care of lazy रेजिस्टर loading */
	save_fpu_regs();
	save_access_regs(vcpu->run->s.regs.acrs);
	अगर (MACHINE_HAS_GS && vcpu->arch.gs_enabled)
		save_gs_cb(current->thपढ़ो.gs_cb);

	/* Extended save area */
	rc = पढ़ो_guest_lc(vcpu, __LC_MCESAD, &ext_sa_addr,
			   माप(अचिन्हित दीर्घ));
	/* Only bits 0 through 63-LC are used क्रम address क्रमmation */
	lc = ext_sa_addr & MCESA_LC_MASK;
	अगर (test_kvm_facility(vcpu->kvm, 133)) अणु
		चयन (lc) अणु
		हाल 0:
		हाल 10:
			ext_sa_addr &= ~0x3ffUL;
			अवरोध;
		हाल 11:
			ext_sa_addr &= ~0x7ffUL;
			अवरोध;
		हाल 12:
			ext_sa_addr &= ~0xfffUL;
			अवरोध;
		शेष:
			ext_sa_addr = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ext_sa_addr &= ~0x3ffUL;
	पूर्ण

	अगर (!rc && mci.vr && ext_sa_addr && test_kvm_facility(vcpu->kvm, 129)) अणु
		अगर (ग_लिखो_guest_असल(vcpu, ext_sa_addr, vcpu->run->s.regs.vrs,
				    512))
			mci.vr = 0;
	पूर्ण अन्यथा अणु
		mci.vr = 0;
	पूर्ण
	अगर (!rc && mci.gs && ext_sa_addr && test_kvm_facility(vcpu->kvm, 133)
	    && (lc == 11 || lc == 12)) अणु
		अगर (ग_लिखो_guest_असल(vcpu, ext_sa_addr + 1024,
				    &vcpu->run->s.regs.gscb, 32))
			mci.gs = 0;
	पूर्ण अन्यथा अणु
		mci.gs = 0;
	पूर्ण

	/* General पूर्णांकerruption inक्रमmation */
	rc |= put_guest_lc(vcpu, 1, (u8 __user *) __LC_AR_MODE_ID);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_MCK_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_MCK_NEW_PSW,
			    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= put_guest_lc(vcpu, mci.val, (u64 __user *) __LC_MCCK_CODE);

	/* Register-save areas */
	अगर (MACHINE_HAS_VX) अणु
		convert_vx_to_fp(fprs, (__vector128 *) vcpu->run->s.regs.vrs);
		rc |= ग_लिखो_guest_lc(vcpu, __LC_FPREGS_SAVE_AREA, fprs, 128);
	पूर्ण अन्यथा अणु
		rc |= ग_लिखो_guest_lc(vcpu, __LC_FPREGS_SAVE_AREA,
				     vcpu->run->s.regs.fprs, 128);
	पूर्ण
	rc |= ग_लिखो_guest_lc(vcpu, __LC_GPREGS_SAVE_AREA,
			     vcpu->run->s.regs.gprs, 128);
	rc |= put_guest_lc(vcpu, current->thपढ़ो.fpu.fpc,
			   (u32 __user *) __LC_FP_CREG_SAVE_AREA);
	rc |= put_guest_lc(vcpu, vcpu->arch.sie_block->todpr,
			   (u32 __user *) __LC_TOD_PROGREG_SAVE_AREA);
	rc |= put_guest_lc(vcpu, kvm_s390_get_cpu_समयr(vcpu),
			   (u64 __user *) __LC_CPU_TIMER_SAVE_AREA);
	rc |= put_guest_lc(vcpu, vcpu->arch.sie_block->ckc >> 8,
			   (u64 __user *) __LC_CLOCK_COMP_SAVE_AREA);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_AREGS_SAVE_AREA,
			     &vcpu->run->s.regs.acrs, 64);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_CREGS_SAVE_AREA,
			     &vcpu->arch.sie_block->gcr, 128);

	/* Extended पूर्णांकerruption inक्रमmation */
	rc |= put_guest_lc(vcpu, mchk->ext_damage_code,
			   (u32 __user *) __LC_EXT_DAMAGE_CODE);
	rc |= put_guest_lc(vcpu, mchk->failing_storage_address,
			   (u64 __user *) __LC_MCCK_FAIL_STOR_ADDR);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_PSW_SAVE_AREA, &mchk->fixed_logout,
			     माप(mchk->fixed_logout));
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_machine_check(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &vcpu->kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_mchk_info mchk = अणुपूर्ण;
	पूर्णांक deliver = 0;
	पूर्णांक rc = 0;

	spin_lock(&fi->lock);
	spin_lock(&li->lock);
	अगर (test_bit(IRQ_PEND_MCHK_EX, &li->pending_irqs) ||
	    test_bit(IRQ_PEND_MCHK_REP, &li->pending_irqs)) अणु
		/*
		 * If there was an exigent machine check pending, then any
		 * repressible machine checks that might have been pending
		 * are indicated aदीर्घ with it, so always clear bits क्रम
		 * repressible and exigent पूर्णांकerrupts
		 */
		mchk = li->irq.mchk;
		clear_bit(IRQ_PEND_MCHK_EX, &li->pending_irqs);
		clear_bit(IRQ_PEND_MCHK_REP, &li->pending_irqs);
		स_रखो(&li->irq.mchk, 0, माप(mchk));
		deliver = 1;
	पूर्ण
	/*
	 * We indicate भग्नing repressible conditions aदीर्घ with
	 * other pending conditions. Channel Report Pending and Channel
	 * Subप्रणाली damage are the only two and and are indicated by
	 * bits in mcic and masked in cr14.
	 */
	अगर (test_and_clear_bit(IRQ_PEND_MCHK_REP, &fi->pending_irqs)) अणु
		mchk.mcic |= fi->mchk.mcic;
		mchk.cr14 |= fi->mchk.cr14;
		स_रखो(&fi->mchk, 0, माप(mchk));
		deliver = 1;
	पूर्ण
	spin_unlock(&li->lock);
	spin_unlock(&fi->lock);

	अगर (deliver) अणु
		VCPU_EVENT(vcpu, 3, "deliver: machine check mcic 0x%llx",
			   mchk.mcic);
		trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
						 KVM_S390_MCHK,
						 mchk.cr14, mchk.mcic);
		vcpu->stat.deliver_machine_check++;
		rc = __ग_लिखो_machine_check(vcpu, &mchk);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक __must_check __deliver_restart(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc = 0;

	VCPU_EVENT(vcpu, 3, "%s", "deliver: cpu restart");
	vcpu->stat.deliver_restart_संकेत++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_RESTART, 0, 0);

	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_RESTART;
	पूर्ण अन्यथा अणु
		rc  = ग_लिखो_guest_lc(vcpu,
				     दुरत्व(काष्ठा lowcore, restart_old_psw),
				     &vcpu->arch.sie_block->gpsw, माप(psw_t));
		rc |= पढ़ो_guest_lc(vcpu, दुरत्व(काष्ठा lowcore, restart_psw),
				    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	पूर्ण
	clear_bit(IRQ_PEND_RESTART, &li->pending_irqs);
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_set_prefix(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_prefix_info prefix;

	spin_lock(&li->lock);
	prefix = li->irq.prefix;
	li->irq.prefix.address = 0;
	clear_bit(IRQ_PEND_SET_PREFIX, &li->pending_irqs);
	spin_unlock(&li->lock);

	vcpu->stat.deliver_prefix_संकेत++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
					 KVM_S390_SIGP_SET_PREFIX,
					 prefix.address, 0);

	kvm_s390_set_prefix(vcpu, prefix.address);
	वापस 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_emergency_संकेत(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc;
	पूर्णांक cpu_addr;

	spin_lock(&li->lock);
	cpu_addr = find_first_bit(li->sigp_emerg_pending, KVM_MAX_VCPUS);
	clear_bit(cpu_addr, li->sigp_emerg_pending);
	अगर (biपंचांगap_empty(li->sigp_emerg_pending, KVM_MAX_VCPUS))
		clear_bit(IRQ_PEND_EXT_EMERGENCY, &li->pending_irqs);
	spin_unlock(&li->lock);

	VCPU_EVENT(vcpu, 4, "%s", "deliver: sigp emerg");
	vcpu->stat.deliver_emergency_संकेत++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_INT_EMERGENCY,
					 cpu_addr, 0);
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_EXT;
		vcpu->arch.sie_block->eic = EXT_IRQ_EMERGENCY_SIG;
		vcpu->arch.sie_block->extcpuaddr = cpu_addr;
		वापस 0;
	पूर्ण

	rc  = put_guest_lc(vcpu, EXT_IRQ_EMERGENCY_SIG,
			   (u16 *)__LC_EXT_INT_CODE);
	rc |= put_guest_lc(vcpu, cpu_addr, (u16 *)__LC_EXT_CPU_ADDR);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
			    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_बाह्यal_call(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_extcall_info extcall;
	पूर्णांक rc;

	spin_lock(&li->lock);
	extcall = li->irq.extcall;
	li->irq.extcall.code = 0;
	clear_bit(IRQ_PEND_EXT_EXTERNAL, &li->pending_irqs);
	spin_unlock(&li->lock);

	VCPU_EVENT(vcpu, 4, "%s", "deliver: sigp ext call");
	vcpu->stat.deliver_बाह्यal_call++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
					 KVM_S390_INT_EXTERNAL_CALL,
					 extcall.code, 0);
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_EXT;
		vcpu->arch.sie_block->eic = EXT_IRQ_EXTERNAL_CALL;
		vcpu->arch.sie_block->extcpuaddr = extcall.code;
		वापस 0;
	पूर्ण

	rc  = put_guest_lc(vcpu, EXT_IRQ_EXTERNAL_CALL,
			   (u16 *)__LC_EXT_INT_CODE);
	rc |= put_guest_lc(vcpu, extcall.code, (u16 *)__LC_EXT_CPU_ADDR);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW, &vcpu->arch.sie_block->gpsw,
			    माप(psw_t));
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __deliver_prog_pv(काष्ठा kvm_vcpu *vcpu, u16 code)
अणु
	चयन (code) अणु
	हाल PGM_SPECIFICATION:
		vcpu->arch.sie_block->iictl = IICTL_CODE_SPECIFICATION;
		अवरोध;
	हाल PGM_OPERAND:
		vcpu->arch.sie_block->iictl = IICTL_CODE_OPERAND;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_prog(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_pgm_info pgm_info;
	पूर्णांक rc = 0, nullअगरying = false;
	u16 ilen;

	spin_lock(&li->lock);
	pgm_info = li->irq.pgm;
	clear_bit(IRQ_PEND_PROG, &li->pending_irqs);
	स_रखो(&li->irq.pgm, 0, माप(pgm_info));
	spin_unlock(&li->lock);

	ilen = pgm_info.flags & KVM_S390_PGM_FLAGS_ILC_MASK;
	VCPU_EVENT(vcpu, 3, "deliver: program irq code 0x%x, ilen:%d",
		   pgm_info.code, ilen);
	vcpu->stat.deliver_program++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_PROGRAM_INT,
					 pgm_info.code, 0);

	/* PER is handled by the ultravisor */
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu))
		वापस __deliver_prog_pv(vcpu, pgm_info.code & ~PGM_PER);

	चयन (pgm_info.code & ~PGM_PER) अणु
	हाल PGM_AFX_TRANSLATION:
	हाल PGM_ASX_TRANSLATION:
	हाल PGM_EX_TRANSLATION:
	हाल PGM_LFX_TRANSLATION:
	हाल PGM_LSTE_SEQUENCE:
	हाल PGM_LSX_TRANSLATION:
	हाल PGM_LX_TRANSLATION:
	हाल PGM_PRIMARY_AUTHORITY:
	हाल PGM_SECONDARY_AUTHORITY:
		nullअगरying = true;
		fallthrough;
	हाल PGM_SPACE_SWITCH:
		rc = put_guest_lc(vcpu, pgm_info.trans_exc_code,
				  (u64 *)__LC_TRANS_EXC_CODE);
		अवरोध;
	हाल PGM_ALEN_TRANSLATION:
	हाल PGM_ALE_SEQUENCE:
	हाल PGM_ASTE_INSTANCE:
	हाल PGM_ASTE_SEQUENCE:
	हाल PGM_ASTE_VALIDITY:
	हाल PGM_EXTENDED_AUTHORITY:
		rc = put_guest_lc(vcpu, pgm_info.exc_access_id,
				  (u8 *)__LC_EXC_ACCESS_ID);
		nullअगरying = true;
		अवरोध;
	हाल PGM_ASCE_TYPE:
	हाल PGM_PAGE_TRANSLATION:
	हाल PGM_REGION_FIRST_TRANS:
	हाल PGM_REGION_SECOND_TRANS:
	हाल PGM_REGION_THIRD_TRANS:
	हाल PGM_SEGMENT_TRANSLATION:
		rc = put_guest_lc(vcpu, pgm_info.trans_exc_code,
				  (u64 *)__LC_TRANS_EXC_CODE);
		rc |= put_guest_lc(vcpu, pgm_info.exc_access_id,
				   (u8 *)__LC_EXC_ACCESS_ID);
		rc |= put_guest_lc(vcpu, pgm_info.op_access_id,
				   (u8 *)__LC_OP_ACCESS_ID);
		nullअगरying = true;
		अवरोध;
	हाल PGM_MONITOR:
		rc = put_guest_lc(vcpu, pgm_info.mon_class_nr,
				  (u16 *)__LC_MON_CLASS_NR);
		rc |= put_guest_lc(vcpu, pgm_info.mon_code,
				   (u64 *)__LC_MON_CODE);
		अवरोध;
	हाल PGM_VECTOR_PROCESSING:
	हाल PGM_DATA:
		rc = put_guest_lc(vcpu, pgm_info.data_exc_code,
				  (u32 *)__LC_DATA_EXC_CODE);
		अवरोध;
	हाल PGM_PROTECTION:
		rc = put_guest_lc(vcpu, pgm_info.trans_exc_code,
				  (u64 *)__LC_TRANS_EXC_CODE);
		rc |= put_guest_lc(vcpu, pgm_info.exc_access_id,
				   (u8 *)__LC_EXC_ACCESS_ID);
		अवरोध;
	हाल PGM_STACK_FULL:
	हाल PGM_STACK_EMPTY:
	हाल PGM_STACK_SPECIFICATION:
	हाल PGM_STACK_TYPE:
	हाल PGM_STACK_OPERATION:
	हाल PGM_TRACE_TABEL:
	हाल PGM_CRYPTO_OPERATION:
		nullअगरying = true;
		अवरोध;
	पूर्ण

	अगर (pgm_info.code & PGM_PER) अणु
		rc |= put_guest_lc(vcpu, pgm_info.per_code,
				   (u8 *) __LC_PER_CODE);
		rc |= put_guest_lc(vcpu, pgm_info.per_aपंचांगid,
				   (u8 *)__LC_PER_ATMID);
		rc |= put_guest_lc(vcpu, pgm_info.per_address,
				   (u64 *) __LC_PER_ADDRESS);
		rc |= put_guest_lc(vcpu, pgm_info.per_access_id,
				   (u8 *) __LC_PER_ACCESS_ID);
	पूर्ण

	अगर (nullअगरying && !(pgm_info.flags & KVM_S390_PGM_FLAGS_NO_REWIND))
		kvm_s390_शुरुआत_psw(vcpu, ilen);

	/* bit 1+2 of the target are the ilc, so we can directly use ilen */
	rc |= put_guest_lc(vcpu, ilen, (u16 *) __LC_PGM_ILC);
	rc |= put_guest_lc(vcpu, vcpu->arch.sie_block->gbea,
				 (u64 *) __LC_LAST_BREAK);
	rc |= put_guest_lc(vcpu, pgm_info.code,
			   (u16 *)__LC_PGM_INT_CODE);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_PGM_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_PGM_NEW_PSW,
			    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	वापस rc ? -EFAULT : 0;
पूर्ण

#घोषणा SCCB_MASK 0xFFFFFFF8
#घोषणा SCCB_EVENT_PENDING 0x3

अटल पूर्णांक ग_लिखो_sclp(काष्ठा kvm_vcpu *vcpu, u32 parm)
अणु
	पूर्णांक rc;

	अगर (kvm_s390_pv_cpu_get_handle(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_EXT;
		vcpu->arch.sie_block->eic = EXT_IRQ_SERVICE_SIG;
		vcpu->arch.sie_block->eiparams = parm;
		वापस 0;
	पूर्ण

	rc  = put_guest_lc(vcpu, EXT_IRQ_SERVICE_SIG, (u16 *)__LC_EXT_INT_CODE);
	rc |= put_guest_lc(vcpu, 0, (u16 *)__LC_EXT_CPU_ADDR);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
			    &vcpu->arch.sie_block->gpsw, माप(psw_t));
	rc |= put_guest_lc(vcpu, parm,
			   (u32 *)__LC_EXT_PARAMS);

	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_service(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &vcpu->kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_ext_info ext;

	spin_lock(&fi->lock);
	अगर (test_bit(IRQ_PEND_EXT_SERVICE, &fi->masked_irqs) ||
	    !(test_bit(IRQ_PEND_EXT_SERVICE, &fi->pending_irqs))) अणु
		spin_unlock(&fi->lock);
		वापस 0;
	पूर्ण
	ext = fi->srv_संकेत;
	स_रखो(&fi->srv_संकेत, 0, माप(ext));
	clear_bit(IRQ_PEND_EXT_SERVICE, &fi->pending_irqs);
	clear_bit(IRQ_PEND_EXT_SERVICE_EV, &fi->pending_irqs);
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu))
		set_bit(IRQ_PEND_EXT_SERVICE, &fi->masked_irqs);
	spin_unlock(&fi->lock);

	VCPU_EVENT(vcpu, 4, "deliver: sclp parameter 0x%x",
		   ext.ext_params);
	vcpu->stat.deliver_service_संकेत++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_INT_SERVICE,
					 ext.ext_params, 0);

	वापस ग_लिखो_sclp(vcpu, ext.ext_params);
पूर्ण

अटल पूर्णांक __must_check __deliver_service_ev(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &vcpu->kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_ext_info ext;

	spin_lock(&fi->lock);
	अगर (!(test_bit(IRQ_PEND_EXT_SERVICE_EV, &fi->pending_irqs))) अणु
		spin_unlock(&fi->lock);
		वापस 0;
	पूर्ण
	ext = fi->srv_संकेत;
	/* only clear the event bit */
	fi->srv_संकेत.ext_params &= ~SCCB_EVENT_PENDING;
	clear_bit(IRQ_PEND_EXT_SERVICE_EV, &fi->pending_irqs);
	spin_unlock(&fi->lock);

	VCPU_EVENT(vcpu, 4, "%s", "deliver: sclp parameter event");
	vcpu->stat.deliver_service_संकेत++;
	trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id, KVM_S390_INT_SERVICE,
					 ext.ext_params, 0);

	वापस ग_लिखो_sclp(vcpu, SCCB_EVENT_PENDING);
पूर्ण

अटल पूर्णांक __must_check __deliver_pfault_करोne(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &vcpu->kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi;
	पूर्णांक rc = 0;

	spin_lock(&fi->lock);
	पूर्णांकi = list_first_entry_or_null(&fi->lists[FIRQ_LIST_PFAULT],
					काष्ठा kvm_s390_पूर्णांकerrupt_info,
					list);
	अगर (पूर्णांकi) अणु
		list_del(&पूर्णांकi->list);
		fi->counters[FIRQ_CNTR_PFAULT] -= 1;
	पूर्ण
	अगर (list_empty(&fi->lists[FIRQ_LIST_PFAULT]))
		clear_bit(IRQ_PEND_PFAULT_DONE, &fi->pending_irqs);
	spin_unlock(&fi->lock);

	अगर (पूर्णांकi) अणु
		trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
						 KVM_S390_INT_PFAULT_DONE, 0,
						 पूर्णांकi->ext.ext_params2);
		VCPU_EVENT(vcpu, 4, "deliver: pfault done token 0x%llx",
			   पूर्णांकi->ext.ext_params2);

		rc  = put_guest_lc(vcpu, EXT_IRQ_CP_SERVICE,
				(u16 *)__LC_EXT_INT_CODE);
		rc |= put_guest_lc(vcpu, PFAULT_DONE,
				(u16 *)__LC_EXT_CPU_ADDR);
		rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
				&vcpu->arch.sie_block->gpsw,
				माप(psw_t));
		rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
				&vcpu->arch.sie_block->gpsw,
				माप(psw_t));
		rc |= put_guest_lc(vcpu, पूर्णांकi->ext.ext_params2,
				(u64 *)__LC_EXT_PARAMS2);
		kमुक्त(पूर्णांकi);
	पूर्ण
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_virtio(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &vcpu->kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi;
	पूर्णांक rc = 0;

	spin_lock(&fi->lock);
	पूर्णांकi = list_first_entry_or_null(&fi->lists[FIRQ_LIST_VIRTIO],
					काष्ठा kvm_s390_पूर्णांकerrupt_info,
					list);
	अगर (पूर्णांकi) अणु
		VCPU_EVENT(vcpu, 4,
			   "deliver: virtio parm: 0x%x,parm64: 0x%llx",
			   पूर्णांकi->ext.ext_params, पूर्णांकi->ext.ext_params2);
		vcpu->stat.deliver_virtio++;
		trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
				पूर्णांकi->type,
				पूर्णांकi->ext.ext_params,
				पूर्णांकi->ext.ext_params2);
		list_del(&पूर्णांकi->list);
		fi->counters[FIRQ_CNTR_VIRTIO] -= 1;
	पूर्ण
	अगर (list_empty(&fi->lists[FIRQ_LIST_VIRTIO]))
		clear_bit(IRQ_PEND_VIRTIO, &fi->pending_irqs);
	spin_unlock(&fi->lock);

	अगर (पूर्णांकi) अणु
		rc  = put_guest_lc(vcpu, EXT_IRQ_CP_SERVICE,
				(u16 *)__LC_EXT_INT_CODE);
		rc |= put_guest_lc(vcpu, VIRTIO_PARAM,
				(u16 *)__LC_EXT_CPU_ADDR);
		rc |= ग_लिखो_guest_lc(vcpu, __LC_EXT_OLD_PSW,
				&vcpu->arch.sie_block->gpsw,
				माप(psw_t));
		rc |= पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW,
				&vcpu->arch.sie_block->gpsw,
				माप(psw_t));
		rc |= put_guest_lc(vcpu, पूर्णांकi->ext.ext_params,
				(u32 *)__LC_EXT_PARAMS);
		rc |= put_guest_lc(vcpu, पूर्णांकi->ext.ext_params2,
				(u64 *)__LC_EXT_PARAMS2);
		kमुक्त(पूर्णांकi);
	पूर्ण
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __करो_deliver_io(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_io_info *io)
अणु
	पूर्णांक rc;

	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->iictl = IICTL_CODE_IO;
		vcpu->arch.sie_block->subchannel_id = io->subchannel_id;
		vcpu->arch.sie_block->subchannel_nr = io->subchannel_nr;
		vcpu->arch.sie_block->io_पूर्णांक_parm = io->io_पूर्णांक_parm;
		vcpu->arch.sie_block->io_पूर्णांक_word = io->io_पूर्णांक_word;
		वापस 0;
	पूर्ण

	rc  = put_guest_lc(vcpu, io->subchannel_id, (u16 *)__LC_SUBCHANNEL_ID);
	rc |= put_guest_lc(vcpu, io->subchannel_nr, (u16 *)__LC_SUBCHANNEL_NR);
	rc |= put_guest_lc(vcpu, io->io_पूर्णांक_parm, (u32 *)__LC_IO_INT_PARM);
	rc |= put_guest_lc(vcpu, io->io_पूर्णांक_word, (u32 *)__LC_IO_INT_WORD);
	rc |= ग_लिखो_guest_lc(vcpu, __LC_IO_OLD_PSW,
			     &vcpu->arch.sie_block->gpsw,
			     माप(psw_t));
	rc |= पढ़ो_guest_lc(vcpu, __LC_IO_NEW_PSW,
			    &vcpu->arch.sie_block->gpsw,
			    माप(psw_t));
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक __must_check __deliver_io(काष्ठा kvm_vcpu *vcpu,
				     अचिन्हित दीर्घ irq_type)
अणु
	काष्ठा list_head *isc_list;
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi;
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &vcpu->kvm->arch.gisa_पूर्णांक;
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi = शून्य;
	काष्ठा kvm_s390_io_info io;
	u32 isc;
	पूर्णांक rc = 0;

	fi = &vcpu->kvm->arch.भग्न_पूर्णांक;

	spin_lock(&fi->lock);
	isc = irq_type_to_isc(irq_type);
	isc_list = &fi->lists[isc];
	पूर्णांकi = list_first_entry_or_null(isc_list,
					काष्ठा kvm_s390_पूर्णांकerrupt_info,
					list);
	अगर (पूर्णांकi) अणु
		अगर (पूर्णांकi->type & KVM_S390_INT_IO_AI_MASK)
			VCPU_EVENT(vcpu, 4, "%s", "deliver: I/O (AI)");
		अन्यथा
			VCPU_EVENT(vcpu, 4, "deliver: I/O %x ss %x schid %04x",
			पूर्णांकi->io.subchannel_id >> 8,
			पूर्णांकi->io.subchannel_id >> 1 & 0x3,
			पूर्णांकi->io.subchannel_nr);

		vcpu->stat.deliver_io++;
		trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
				पूर्णांकi->type,
				((__u32)पूर्णांकi->io.subchannel_id << 16) |
				पूर्णांकi->io.subchannel_nr,
				((__u64)पूर्णांकi->io.io_पूर्णांक_parm << 32) |
				पूर्णांकi->io.io_पूर्णांक_word);
		list_del(&पूर्णांकi->list);
		fi->counters[FIRQ_CNTR_IO] -= 1;
	पूर्ण
	अगर (list_empty(isc_list))
		clear_bit(irq_type, &fi->pending_irqs);
	spin_unlock(&fi->lock);

	अगर (पूर्णांकi) अणु
		rc = __करो_deliver_io(vcpu, &(पूर्णांकi->io));
		kमुक्त(पूर्णांकi);
		जाओ out;
	पूर्ण

	अगर (gi->origin && gisa_tac_ipm_gisc(gi->origin, isc)) अणु
		/*
		 * in हाल an adapter पूर्णांकerrupt was not delivered
		 * in SIE context KVM will handle the delivery
		 */
		VCPU_EVENT(vcpu, 4, "%s isc %u", "deliver: I/O (AI/gisa)", isc);
		स_रखो(&io, 0, माप(io));
		io.io_पूर्णांक_word = isc_to_पूर्णांक_word(isc);
		vcpu->stat.deliver_io++;
		trace_kvm_s390_deliver_पूर्णांकerrupt(vcpu->vcpu_id,
			KVM_S390_INT_IO(1, 0, 0, 0),
			((__u32)io.subchannel_id << 16) |
			io.subchannel_nr,
			((__u64)io.io_पूर्णांक_parm << 32) |
			io.io_पूर्णांक_word);
		rc = __करो_deliver_io(vcpu, &io);
	पूर्ण
out:
	वापस rc;
पूर्ण

/* Check whether an बाह्यal call is pending (deliverable or not) */
पूर्णांक kvm_s390_ext_call_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	अगर (!sclp.has_sigpअगर)
		वापस test_bit(IRQ_PEND_EXT_EXTERNAL, &li->pending_irqs);

	वापस sca_ext_call_pending(vcpu, शून्य);
पूर्ण

पूर्णांक kvm_s390_vcpu_has_irq(काष्ठा kvm_vcpu *vcpu, पूर्णांक exclude_stop)
अणु
	अगर (deliverable_irqs(vcpu))
		वापस 1;

	अगर (kvm_cpu_has_pending_समयr(vcpu))
		वापस 1;

	/* बाह्यal call pending and deliverable */
	अगर (kvm_s390_ext_call_pending(vcpu) &&
	    !psw_extपूर्णांक_disabled(vcpu) &&
	    (vcpu->arch.sie_block->gcr[0] & CR0_EXTERNAL_CALL_SUBMASK))
		वापस 1;

	अगर (!exclude_stop && kvm_s390_is_stop_irq_pending(vcpu))
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक kvm_cpu_has_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस ckc_irq_pending(vcpu) || cpu_समयr_irq_pending(vcpu);
पूर्ण

अटल u64 __calculate_slसमय(काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर u64 now = kvm_s390_get_tod_घड़ी_fast(vcpu->kvm);
	स्थिर u64 ckc = vcpu->arch.sie_block->ckc;
	u64 cpuपंचांग, slसमय = 0;

	अगर (ckc_पूर्णांकerrupts_enabled(vcpu)) अणु
		अगर (vcpu->arch.sie_block->gcr[0] & CR0_CLOCK_COMPARATOR_SIGN) अणु
			अगर ((s64)now < (s64)ckc)
				slसमय = tod_to_ns((s64)ckc - (s64)now);
		पूर्ण अन्यथा अगर (now < ckc) अणु
			slसमय = tod_to_ns(ckc - now);
		पूर्ण
		/* alपढ़ोy expired */
		अगर (!slसमय)
			वापस 0;
		अगर (cpu_समयr_पूर्णांकerrupts_enabled(vcpu)) अणु
			cpuपंचांग = kvm_s390_get_cpu_समयr(vcpu);
			/* alपढ़ोy expired? */
			अगर (cpuपंचांग >> 63)
				वापस 0;
			वापस min_t(u64, slसमय, tod_to_ns(cpuपंचांग));
		पूर्ण
	पूर्ण अन्यथा अगर (cpu_समयr_पूर्णांकerrupts_enabled(vcpu)) अणु
		slसमय = kvm_s390_get_cpu_समयr(vcpu);
		/* alपढ़ोy expired? */
		अगर (slसमय >> 63)
			वापस 0;
	पूर्ण
	वापस slसमय;
पूर्ण

पूर्णांक kvm_s390_handle_रुको(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &vcpu->kvm->arch.gisa_पूर्णांक;
	u64 slसमय;

	vcpu->stat.निकास_रुको_state++;

	/* fast path */
	अगर (kvm_arch_vcpu_runnable(vcpu))
		वापस 0;

	अगर (psw_पूर्णांकerrupts_disabled(vcpu)) अणु
		VCPU_EVENT(vcpu, 3, "%s", "disabled wait");
		वापस -EOPNOTSUPP; /* disabled रुको */
	पूर्ण

	अगर (gi->origin &&
	    (gisa_get_ipm_or_restore_iam(gi) &
	     vcpu->arch.sie_block->gcr[6] >> 24))
		वापस 0;

	अगर (!ckc_पूर्णांकerrupts_enabled(vcpu) &&
	    !cpu_समयr_पूर्णांकerrupts_enabled(vcpu)) अणु
		VCPU_EVENT(vcpu, 3, "%s", "enabled wait w/o timer");
		__set_cpu_idle(vcpu);
		जाओ no_समयr;
	पूर्ण

	slसमय = __calculate_slसमय(vcpu);
	अगर (!slसमय)
		वापस 0;

	__set_cpu_idle(vcpu);
	hrसमयr_start(&vcpu->arch.ckc_समयr, slसमय, HRTIMER_MODE_REL);
	VCPU_EVENT(vcpu, 4, "enabled wait: %llu ns", slसमय);
no_समयr:
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	kvm_vcpu_block(vcpu);
	__unset_cpu_idle(vcpu);
	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	hrसमयr_cancel(&vcpu->arch.ckc_समयr);
	वापस 0;
पूर्ण

व्योम kvm_s390_vcpu_wakeup(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->valid_wakeup = true;
	kvm_vcpu_wake_up(vcpu);

	/*
	 * The VCPU might not be sleeping but rather executing VSIE. Let's
	 * kick it, so it leaves the SIE to process the request.
	 */
	kvm_s390_vsie_kick(vcpu);
पूर्ण

क्रमागत hrसमयr_restart kvm_s390_idle_wakeup(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा kvm_vcpu *vcpu;
	u64 slसमय;

	vcpu = container_of(समयr, काष्ठा kvm_vcpu, arch.ckc_समयr);
	slसमय = __calculate_slसमय(vcpu);

	/*
	 * If the monotonic घड़ी runs faster than the tod घड़ी we might be
	 * woken up too early and have to go back to sleep to aव्योम deadlocks.
	 */
	अगर (slसमय && hrसमयr_क्रमward_now(समयr, ns_to_kसमय(slसमय)))
		वापस HRTIMER_RESTART;
	kvm_s390_vcpu_wakeup(vcpu);
	वापस HRTIMER_NORESTART;
पूर्ण

व्योम kvm_s390_clear_local_irqs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	spin_lock(&li->lock);
	li->pending_irqs = 0;
	biपंचांगap_zero(li->sigp_emerg_pending, KVM_MAX_VCPUS);
	स_रखो(&li->irq, 0, माप(li->irq));
	spin_unlock(&li->lock);

	sca_clear_ext_call(vcpu);
पूर्ण

पूर्णांक __must_check kvm_s390_deliver_pending_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ irq_type;
	अचिन्हित दीर्घ irqs;

	__reset_पूर्णांकercept_indicators(vcpu);

	/* pending ckc conditions might have been invalidated */
	clear_bit(IRQ_PEND_EXT_CLOCK_COMP, &li->pending_irqs);
	अगर (ckc_irq_pending(vcpu))
		set_bit(IRQ_PEND_EXT_CLOCK_COMP, &li->pending_irqs);

	/* pending cpu समयr conditions might have been invalidated */
	clear_bit(IRQ_PEND_EXT_CPU_TIMER, &li->pending_irqs);
	अगर (cpu_समयr_irq_pending(vcpu))
		set_bit(IRQ_PEND_EXT_CPU_TIMER, &li->pending_irqs);

	जबतक ((irqs = deliverable_irqs(vcpu)) && !rc) अणु
		/* bits are in the reverse order of पूर्णांकerrupt priority */
		irq_type = find_last_bit(&irqs, IRQ_PEND_COUNT);
		चयन (irq_type) अणु
		हाल IRQ_PEND_IO_ISC_0:
		हाल IRQ_PEND_IO_ISC_1:
		हाल IRQ_PEND_IO_ISC_2:
		हाल IRQ_PEND_IO_ISC_3:
		हाल IRQ_PEND_IO_ISC_4:
		हाल IRQ_PEND_IO_ISC_5:
		हाल IRQ_PEND_IO_ISC_6:
		हाल IRQ_PEND_IO_ISC_7:
			rc = __deliver_io(vcpu, irq_type);
			अवरोध;
		हाल IRQ_PEND_MCHK_EX:
		हाल IRQ_PEND_MCHK_REP:
			rc = __deliver_machine_check(vcpu);
			अवरोध;
		हाल IRQ_PEND_PROG:
			rc = __deliver_prog(vcpu);
			अवरोध;
		हाल IRQ_PEND_EXT_EMERGENCY:
			rc = __deliver_emergency_संकेत(vcpu);
			अवरोध;
		हाल IRQ_PEND_EXT_EXTERNAL:
			rc = __deliver_बाह्यal_call(vcpu);
			अवरोध;
		हाल IRQ_PEND_EXT_CLOCK_COMP:
			rc = __deliver_ckc(vcpu);
			अवरोध;
		हाल IRQ_PEND_EXT_CPU_TIMER:
			rc = __deliver_cpu_समयr(vcpu);
			अवरोध;
		हाल IRQ_PEND_RESTART:
			rc = __deliver_restart(vcpu);
			अवरोध;
		हाल IRQ_PEND_SET_PREFIX:
			rc = __deliver_set_prefix(vcpu);
			अवरोध;
		हाल IRQ_PEND_PFAULT_INIT:
			rc = __deliver_pfault_init(vcpu);
			अवरोध;
		हाल IRQ_PEND_EXT_SERVICE:
			rc = __deliver_service(vcpu);
			अवरोध;
		हाल IRQ_PEND_EXT_SERVICE_EV:
			rc = __deliver_service_ev(vcpu);
			अवरोध;
		हाल IRQ_PEND_PFAULT_DONE:
			rc = __deliver_pfault_करोne(vcpu);
			अवरोध;
		हाल IRQ_PEND_VIRTIO:
			rc = __deliver_virtio(vcpu);
			अवरोध;
		शेष:
			WARN_ONCE(1, "Unknown pending irq type %ld", irq_type);
			clear_bit(irq_type, &li->pending_irqs);
		पूर्ण
	पूर्ण

	set_पूर्णांकercept_indicators(vcpu);

	वापस rc;
पूर्ण

अटल पूर्णांक __inject_prog(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	vcpu->stat.inject_program++;
	VCPU_EVENT(vcpu, 3, "inject: program irq code 0x%x", irq->u.pgm.code);
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_PROGRAM_INT,
				   irq->u.pgm.code, 0);

	अगर (!(irq->u.pgm.flags & KVM_S390_PGM_FLAGS_ILC_VALID)) अणु
		/* स्वतः detection अगर no valid ILC was given */
		irq->u.pgm.flags &= ~KVM_S390_PGM_FLAGS_ILC_MASK;
		irq->u.pgm.flags |= kvm_s390_get_ilen(vcpu);
		irq->u.pgm.flags |= KVM_S390_PGM_FLAGS_ILC_VALID;
	पूर्ण

	अगर (irq->u.pgm.code == PGM_PER) अणु
		li->irq.pgm.code |= PGM_PER;
		li->irq.pgm.flags = irq->u.pgm.flags;
		/* only modअगरy PER related inक्रमmation */
		li->irq.pgm.per_address = irq->u.pgm.per_address;
		li->irq.pgm.per_code = irq->u.pgm.per_code;
		li->irq.pgm.per_aपंचांगid = irq->u.pgm.per_aपंचांगid;
		li->irq.pgm.per_access_id = irq->u.pgm.per_access_id;
	पूर्ण अन्यथा अगर (!(irq->u.pgm.code & PGM_PER)) अणु
		li->irq.pgm.code = (li->irq.pgm.code & PGM_PER) |
				   irq->u.pgm.code;
		li->irq.pgm.flags = irq->u.pgm.flags;
		/* only modअगरy non-PER inक्रमmation */
		li->irq.pgm.trans_exc_code = irq->u.pgm.trans_exc_code;
		li->irq.pgm.mon_code = irq->u.pgm.mon_code;
		li->irq.pgm.data_exc_code = irq->u.pgm.data_exc_code;
		li->irq.pgm.mon_class_nr = irq->u.pgm.mon_class_nr;
		li->irq.pgm.exc_access_id = irq->u.pgm.exc_access_id;
		li->irq.pgm.op_access_id = irq->u.pgm.op_access_id;
	पूर्ण अन्यथा अणु
		li->irq.pgm = irq->u.pgm;
	पूर्ण
	set_bit(IRQ_PEND_PROG, &li->pending_irqs);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_pfault_init(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	vcpu->stat.inject_pfault_init++;
	VCPU_EVENT(vcpu, 4, "inject: pfault init parameter block at 0x%llx",
		   irq->u.ext.ext_params2);
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_INT_PFAULT_INIT,
				   irq->u.ext.ext_params,
				   irq->u.ext.ext_params2);

	li->irq.ext = irq->u.ext;
	set_bit(IRQ_PEND_PFAULT_INIT, &li->pending_irqs);
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_EXT_INT);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_extcall(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_extcall_info *extcall = &li->irq.extcall;
	uपूर्णांक16_t src_id = irq->u.extcall.code;

	vcpu->stat.inject_बाह्यal_call++;
	VCPU_EVENT(vcpu, 4, "inject: external call source-cpu:%u",
		   src_id);
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_INT_EXTERNAL_CALL,
				   src_id, 0);

	/* sending vcpu invalid */
	अगर (kvm_get_vcpu_by_id(vcpu->kvm, src_id) == शून्य)
		वापस -EINVAL;

	अगर (sclp.has_sigpअगर && !kvm_s390_pv_cpu_get_handle(vcpu))
		वापस sca_inject_ext_call(vcpu, src_id);

	अगर (test_and_set_bit(IRQ_PEND_EXT_EXTERNAL, &li->pending_irqs))
		वापस -EBUSY;
	*extcall = irq->u.extcall;
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_EXT_INT);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_set_prefix(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_prefix_info *prefix = &li->irq.prefix;

	vcpu->stat.inject_set_prefix++;
	VCPU_EVENT(vcpu, 3, "inject: set prefix to %x",
		   irq->u.prefix.address);
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_SIGP_SET_PREFIX,
				   irq->u.prefix.address, 0);

	अगर (!is_vcpu_stopped(vcpu))
		वापस -EBUSY;

	*prefix = irq->u.prefix;
	set_bit(IRQ_PEND_SET_PREFIX, &li->pending_irqs);
	वापस 0;
पूर्ण

#घोषणा KVM_S390_STOP_SUPP_FLAGS (KVM_S390_STOP_FLAG_STORE_STATUS)
अटल पूर्णांक __inject_sigp_stop(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_stop_info *stop = &li->irq.stop;
	पूर्णांक rc = 0;

	vcpu->stat.inject_stop_संकेत++;
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_SIGP_STOP, 0, 0);

	अगर (irq->u.stop.flags & ~KVM_S390_STOP_SUPP_FLAGS)
		वापस -EINVAL;

	अगर (is_vcpu_stopped(vcpu)) अणु
		अगर (irq->u.stop.flags & KVM_S390_STOP_FLAG_STORE_STATUS)
			rc = kvm_s390_store_status_unloaded(vcpu,
						KVM_S390_STORE_STATUS_NOADDR);
		वापस rc;
	पूर्ण

	अगर (test_and_set_bit(IRQ_PEND_SIGP_STOP, &li->pending_irqs))
		वापस -EBUSY;
	stop->flags = irq->u.stop.flags;
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOP_INT);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_sigp_restart(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	vcpu->stat.inject_restart++;
	VCPU_EVENT(vcpu, 3, "%s", "inject: restart int");
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_RESTART, 0, 0);

	set_bit(IRQ_PEND_RESTART, &li->pending_irqs);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_sigp_emergency(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	vcpu->stat.inject_emergency_संकेत++;
	VCPU_EVENT(vcpu, 4, "inject: emergency from cpu %u",
		   irq->u.emerg.code);
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_INT_EMERGENCY,
				   irq->u.emerg.code, 0);

	/* sending vcpu invalid */
	अगर (kvm_get_vcpu_by_id(vcpu->kvm, irq->u.emerg.code) == शून्य)
		वापस -EINVAL;

	set_bit(irq->u.emerg.code, li->sigp_emerg_pending);
	set_bit(IRQ_PEND_EXT_EMERGENCY, &li->pending_irqs);
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_EXT_INT);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_mchk(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_mchk_info *mchk = &li->irq.mchk;

	vcpu->stat.inject_mchk++;
	VCPU_EVENT(vcpu, 3, "inject: machine check mcic 0x%llx",
		   irq->u.mchk.mcic);
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_MCHK, 0,
				   irq->u.mchk.mcic);

	/*
	 * Because repressible machine checks can be indicated aदीर्घ with
	 * exigent machine checks (PoP, Chapter 11, Interruption action)
	 * we need to combine cr14, mcic and बाह्यal damage code.
	 * Failing storage address and the logout area should not be or'ed
	 * together, we just indicate the last occurrence of the corresponding
	 * machine check
	 */
	mchk->cr14 |= irq->u.mchk.cr14;
	mchk->mcic |= irq->u.mchk.mcic;
	mchk->ext_damage_code |= irq->u.mchk.ext_damage_code;
	mchk->failing_storage_address = irq->u.mchk.failing_storage_address;
	स_नकल(&mchk->fixed_logout, &irq->u.mchk.fixed_logout,
	       माप(mchk->fixed_logout));
	अगर (mchk->mcic & MCHK_EX_MASK)
		set_bit(IRQ_PEND_MCHK_EX, &li->pending_irqs);
	अन्यथा अगर (mchk->mcic & MCHK_REP_MASK)
		set_bit(IRQ_PEND_MCHK_REP,  &li->pending_irqs);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_ckc(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	vcpu->stat.inject_ckc++;
	VCPU_EVENT(vcpu, 3, "%s", "inject: clock comparator external");
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_INT_CLOCK_COMP,
				   0, 0);

	set_bit(IRQ_PEND_EXT_CLOCK_COMP, &li->pending_irqs);
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_EXT_INT);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_cpu_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	vcpu->stat.inject_cpuपंचांग++;
	VCPU_EVENT(vcpu, 3, "%s", "inject: cpu timer external");
	trace_kvm_s390_inject_vcpu(vcpu->vcpu_id, KVM_S390_INT_CPU_TIMER,
				   0, 0);

	set_bit(IRQ_PEND_EXT_CPU_TIMER, &li->pending_irqs);
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_EXT_INT);
	वापस 0;
पूर्ण

अटल काष्ठा kvm_s390_पूर्णांकerrupt_info *get_io_पूर्णांक(काष्ठा kvm *kvm,
						  पूर्णांक isc, u32 schid)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;
	काष्ठा list_head *isc_list = &fi->lists[FIRQ_LIST_IO_ISC_0 + isc];
	काष्ठा kvm_s390_पूर्णांकerrupt_info *iter;
	u16 id = (schid & 0xffff0000U) >> 16;
	u16 nr = schid & 0x0000ffffU;

	spin_lock(&fi->lock);
	list_क्रम_each_entry(iter, isc_list, list) अणु
		अगर (schid && (id != iter->io.subchannel_id ||
			      nr != iter->io.subchannel_nr))
			जारी;
		/* found an appropriate entry */
		list_del_init(&iter->list);
		fi->counters[FIRQ_CNTR_IO] -= 1;
		अगर (list_empty(isc_list))
			clear_bit(isc_to_irq_type(isc), &fi->pending_irqs);
		spin_unlock(&fi->lock);
		वापस iter;
	पूर्ण
	spin_unlock(&fi->lock);
	वापस शून्य;
पूर्ण

अटल काष्ठा kvm_s390_पूर्णांकerrupt_info *get_top_io_पूर्णांक(काष्ठा kvm *kvm,
						      u64 isc_mask, u32 schid)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi = शून्य;
	पूर्णांक isc;

	क्रम (isc = 0; isc <= MAX_ISC && !पूर्णांकi; isc++) अणु
		अगर (isc_mask & isc_to_isc_bits(isc))
			पूर्णांकi = get_io_पूर्णांक(kvm, isc, schid);
	पूर्ण
	वापस पूर्णांकi;
पूर्ण

अटल पूर्णांक get_top_gisa_isc(काष्ठा kvm *kvm, u64 isc_mask, u32 schid)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;
	अचिन्हित दीर्घ active_mask;
	पूर्णांक isc;

	अगर (schid)
		जाओ out;
	अगर (!gi->origin)
		जाओ out;

	active_mask = (isc_mask & gisa_get_ipm(gi->origin) << 24) << 32;
	जबतक (active_mask) अणु
		isc = __fls(active_mask) ^ (BITS_PER_LONG - 1);
		अगर (gisa_tac_ipm_gisc(gi->origin, isc))
			वापस isc;
		clear_bit_inv(isc, &active_mask);
	पूर्ण
out:
	वापस -EINVAL;
पूर्ण

/*
 * Dequeue and वापस an I/O पूर्णांकerrupt matching any of the पूर्णांकerruption
 * subclasses as designated by the isc mask in cr6 and the schid (अगर != 0).
 * Take पूर्णांकo account the पूर्णांकerrupts pending in the पूर्णांकerrupt list and in GISA.
 *
 * Note that क्रम a guest that करोes not enable I/O पूर्णांकerrupts
 * but relies on TPI, a flood of classic पूर्णांकerrupts may starve
 * out adapter पूर्णांकerrupts on the same isc. Linux करोes not करो
 * that, and it is possible to work around the issue by configuring
 * dअगरferent iscs क्रम classic and adapter पूर्णांकerrupts in the guest,
 * but we may want to revisit this in the future.
 */
काष्ठा kvm_s390_पूर्णांकerrupt_info *kvm_s390_get_io_पूर्णांक(काष्ठा kvm *kvm,
						    u64 isc_mask, u32 schid)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi, *पंचांगp_पूर्णांकi;
	पूर्णांक isc;

	पूर्णांकi = get_top_io_पूर्णांक(kvm, isc_mask, schid);

	isc = get_top_gisa_isc(kvm, isc_mask, schid);
	अगर (isc < 0)
		/* no AI in GISA */
		जाओ out;

	अगर (!पूर्णांकi)
		/* AI in GISA but no classical IO पूर्णांक */
		जाओ gisa_out;

	/* both types of पूर्णांकerrupts present */
	अगर (पूर्णांक_word_to_isc(पूर्णांकi->io.io_पूर्णांक_word) <= isc) अणु
		/* classical IO पूर्णांक with higher priority */
		gisa_set_ipm_gisc(gi->origin, isc);
		जाओ out;
	पूर्ण
gisa_out:
	पंचांगp_पूर्णांकi = kzalloc(माप(*पूर्णांकi), GFP_KERNEL_ACCOUNT);
	अगर (पंचांगp_पूर्णांकi) अणु
		पंचांगp_पूर्णांकi->type = KVM_S390_INT_IO(1, 0, 0, 0);
		पंचांगp_पूर्णांकi->io.io_पूर्णांक_word = isc_to_पूर्णांक_word(isc);
		अगर (पूर्णांकi)
			kvm_s390_reinject_io_पूर्णांक(kvm, पूर्णांकi);
		पूर्णांकi = पंचांगp_पूर्णांकi;
	पूर्ण अन्यथा
		gisa_set_ipm_gisc(gi->origin, isc);
out:
	वापस पूर्णांकi;
पूर्ण

अटल पूर्णांक __inject_service(काष्ठा kvm *kvm,
			     काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;

	kvm->stat.inject_service_संकेत++;
	spin_lock(&fi->lock);
	fi->srv_संकेत.ext_params |= पूर्णांकi->ext.ext_params & SCCB_EVENT_PENDING;

	/* We always allow events, track them separately from the sccb पूर्णांकs */
	अगर (fi->srv_संकेत.ext_params & SCCB_EVENT_PENDING)
		set_bit(IRQ_PEND_EXT_SERVICE_EV, &fi->pending_irqs);

	/*
	 * Early versions of the QEMU s390 bios will inject several
	 * service पूर्णांकerrupts after another without handling a
	 * condition code indicating busy.
	 * We will silently ignore those superfluous sccb values.
	 * A future version of QEMU will take care of serialization
	 * of servc requests
	 */
	अगर (fi->srv_संकेत.ext_params & SCCB_MASK)
		जाओ out;
	fi->srv_संकेत.ext_params |= पूर्णांकi->ext.ext_params & SCCB_MASK;
	set_bit(IRQ_PEND_EXT_SERVICE, &fi->pending_irqs);
out:
	spin_unlock(&fi->lock);
	kमुक्त(पूर्णांकi);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_virtio(काष्ठा kvm *kvm,
			    काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;

	kvm->stat.inject_virtio++;
	spin_lock(&fi->lock);
	अगर (fi->counters[FIRQ_CNTR_VIRTIO] >= KVM_S390_MAX_VIRTIO_IRQS) अणु
		spin_unlock(&fi->lock);
		वापस -EBUSY;
	पूर्ण
	fi->counters[FIRQ_CNTR_VIRTIO] += 1;
	list_add_tail(&पूर्णांकi->list, &fi->lists[FIRQ_LIST_VIRTIO]);
	set_bit(IRQ_PEND_VIRTIO, &fi->pending_irqs);
	spin_unlock(&fi->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_pfault_करोne(काष्ठा kvm *kvm,
				 काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;

	kvm->stat.inject_pfault_करोne++;
	spin_lock(&fi->lock);
	अगर (fi->counters[FIRQ_CNTR_PFAULT] >=
		(ASYNC_PF_PER_VCPU * KVM_MAX_VCPUS)) अणु
		spin_unlock(&fi->lock);
		वापस -EBUSY;
	पूर्ण
	fi->counters[FIRQ_CNTR_PFAULT] += 1;
	list_add_tail(&पूर्णांकi->list, &fi->lists[FIRQ_LIST_PFAULT]);
	set_bit(IRQ_PEND_PFAULT_DONE, &fi->pending_irqs);
	spin_unlock(&fi->lock);
	वापस 0;
पूर्ण

#घोषणा CR_PENDING_SUBCLASS 28
अटल पूर्णांक __inject_भग्न_mchk(काष्ठा kvm *kvm,
				काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;

	kvm->stat.inject_भग्न_mchk++;
	spin_lock(&fi->lock);
	fi->mchk.cr14 |= पूर्णांकi->mchk.cr14 & (1UL << CR_PENDING_SUBCLASS);
	fi->mchk.mcic |= पूर्णांकi->mchk.mcic;
	set_bit(IRQ_PEND_MCHK_REP, &fi->pending_irqs);
	spin_unlock(&fi->lock);
	kमुक्त(पूर्णांकi);
	वापस 0;
पूर्ण

अटल पूर्णांक __inject_io(काष्ठा kvm *kvm, काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi;
	काष्ठा list_head *list;
	पूर्णांक isc;

	kvm->stat.inject_io++;
	isc = पूर्णांक_word_to_isc(पूर्णांकi->io.io_पूर्णांक_word);

	/*
	 * Do not make use of gisa in रक्षित mode. We करो not use the lock
	 * checking variant as this is just a perक्रमmance optimization and we
	 * करो not hold the lock here. This is ok as the code will pick
	 * पूर्णांकerrupts from both "lists" क्रम delivery.
	 */
	अगर (!kvm_s390_pv_get_handle(kvm) &&
	    gi->origin && पूर्णांकi->type & KVM_S390_INT_IO_AI_MASK) अणु
		VM_EVENT(kvm, 4, "%s isc %1u", "inject: I/O (AI/gisa)", isc);
		gisa_set_ipm_gisc(gi->origin, isc);
		kमुक्त(पूर्णांकi);
		वापस 0;
	पूर्ण

	fi = &kvm->arch.भग्न_पूर्णांक;
	spin_lock(&fi->lock);
	अगर (fi->counters[FIRQ_CNTR_IO] >= KVM_S390_MAX_FLOAT_IRQS) अणु
		spin_unlock(&fi->lock);
		वापस -EBUSY;
	पूर्ण
	fi->counters[FIRQ_CNTR_IO] += 1;

	अगर (पूर्णांकi->type & KVM_S390_INT_IO_AI_MASK)
		VM_EVENT(kvm, 4, "%s", "inject: I/O (AI)");
	अन्यथा
		VM_EVENT(kvm, 4, "inject: I/O %x ss %x schid %04x",
			पूर्णांकi->io.subchannel_id >> 8,
			पूर्णांकi->io.subchannel_id >> 1 & 0x3,
			पूर्णांकi->io.subchannel_nr);
	list = &fi->lists[FIRQ_LIST_IO_ISC_0 + isc];
	list_add_tail(&पूर्णांकi->list, list);
	set_bit(isc_to_irq_type(isc), &fi->pending_irqs);
	spin_unlock(&fi->lock);
	वापस 0;
पूर्ण

/*
 * Find a destination VCPU क्रम a भग्नing irq and kick it.
 */
अटल व्योम __भग्नing_irq_kick(काष्ठा kvm *kvm, u64 type)
अणु
	काष्ठा kvm_vcpu *dst_vcpu;
	पूर्णांक sigcpu, online_vcpus, nr_tries = 0;

	online_vcpus = atomic_पढ़ो(&kvm->online_vcpus);
	अगर (!online_vcpus)
		वापस;

	/* find idle VCPUs first, then round robin */
	sigcpu = find_first_bit(kvm->arch.idle_mask, online_vcpus);
	अगर (sigcpu == online_vcpus) अणु
		करो अणु
			sigcpu = kvm->arch.भग्न_पूर्णांक.next_rr_cpu++;
			kvm->arch.भग्न_पूर्णांक.next_rr_cpu %= online_vcpus;
			/* aव्योम endless loops अगर all vcpus are stopped */
			अगर (nr_tries++ >= online_vcpus)
				वापस;
		पूर्ण जबतक (is_vcpu_stopped(kvm_get_vcpu(kvm, sigcpu)));
	पूर्ण
	dst_vcpu = kvm_get_vcpu(kvm, sigcpu);

	/* make the VCPU drop out of the SIE, or wake it up अगर sleeping */
	चयन (type) अणु
	हाल KVM_S390_MCHK:
		kvm_s390_set_cpuflags(dst_vcpu, CPUSTAT_STOP_INT);
		अवरोध;
	हाल KVM_S390_INT_IO_MIN...KVM_S390_INT_IO_MAX:
		अगर (!(type & KVM_S390_INT_IO_AI_MASK &&
		      kvm->arch.gisa_पूर्णांक.origin) ||
		      kvm_s390_pv_cpu_get_handle(dst_vcpu))
			kvm_s390_set_cpuflags(dst_vcpu, CPUSTAT_IO_INT);
		अवरोध;
	शेष:
		kvm_s390_set_cpuflags(dst_vcpu, CPUSTAT_EXT_INT);
		अवरोध;
	पूर्ण
	kvm_s390_vcpu_wakeup(dst_vcpu);
पूर्ण

अटल पूर्णांक __inject_vm(काष्ठा kvm *kvm, काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	u64 type = READ_ONCE(पूर्णांकi->type);
	पूर्णांक rc;

	चयन (type) अणु
	हाल KVM_S390_MCHK:
		rc = __inject_भग्न_mchk(kvm, पूर्णांकi);
		अवरोध;
	हाल KVM_S390_INT_VIRTIO:
		rc = __inject_virtio(kvm, पूर्णांकi);
		अवरोध;
	हाल KVM_S390_INT_SERVICE:
		rc = __inject_service(kvm, पूर्णांकi);
		अवरोध;
	हाल KVM_S390_INT_PFAULT_DONE:
		rc = __inject_pfault_करोne(kvm, पूर्णांकi);
		अवरोध;
	हाल KVM_S390_INT_IO_MIN...KVM_S390_INT_IO_MAX:
		rc = __inject_io(kvm, पूर्णांकi);
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण
	अगर (rc)
		वापस rc;

	__भग्नing_irq_kick(kvm, type);
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_inject_vm(काष्ठा kvm *kvm,
		       काष्ठा kvm_s390_पूर्णांकerrupt *s390पूर्णांक)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi;
	पूर्णांक rc;

	पूर्णांकi = kzalloc(माप(*पूर्णांकi), GFP_KERNEL_ACCOUNT);
	अगर (!पूर्णांकi)
		वापस -ENOMEM;

	पूर्णांकi->type = s390पूर्णांक->type;
	चयन (पूर्णांकi->type) अणु
	हाल KVM_S390_INT_VIRTIO:
		VM_EVENT(kvm, 5, "inject: virtio parm:%x,parm64:%llx",
			 s390पूर्णांक->parm, s390पूर्णांक->parm64);
		पूर्णांकi->ext.ext_params = s390पूर्णांक->parm;
		पूर्णांकi->ext.ext_params2 = s390पूर्णांक->parm64;
		अवरोध;
	हाल KVM_S390_INT_SERVICE:
		VM_EVENT(kvm, 4, "inject: sclp parm:%x", s390पूर्णांक->parm);
		पूर्णांकi->ext.ext_params = s390पूर्णांक->parm;
		अवरोध;
	हाल KVM_S390_INT_PFAULT_DONE:
		पूर्णांकi->ext.ext_params2 = s390पूर्णांक->parm64;
		अवरोध;
	हाल KVM_S390_MCHK:
		VM_EVENT(kvm, 3, "inject: machine check mcic 0x%llx",
			 s390पूर्णांक->parm64);
		पूर्णांकi->mchk.cr14 = s390पूर्णांक->parm; /* upper bits are not used */
		पूर्णांकi->mchk.mcic = s390पूर्णांक->parm64;
		अवरोध;
	हाल KVM_S390_INT_IO_MIN...KVM_S390_INT_IO_MAX:
		पूर्णांकi->io.subchannel_id = s390पूर्णांक->parm >> 16;
		पूर्णांकi->io.subchannel_nr = s390पूर्णांक->parm & 0x0000ffffu;
		पूर्णांकi->io.io_पूर्णांक_parm = s390पूर्णांक->parm64 >> 32;
		पूर्णांकi->io.io_पूर्णांक_word = s390पूर्णांक->parm64 & 0x00000000ffffffffull;
		अवरोध;
	शेष:
		kमुक्त(पूर्णांकi);
		वापस -EINVAL;
	पूर्ण
	trace_kvm_s390_inject_vm(s390पूर्णांक->type, s390पूर्णांक->parm, s390पूर्णांक->parm64,
				 2);

	rc = __inject_vm(kvm, पूर्णांकi);
	अगर (rc)
		kमुक्त(पूर्णांकi);
	वापस rc;
पूर्ण

पूर्णांक kvm_s390_reinject_io_पूर्णांक(काष्ठा kvm *kvm,
			      काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi)
अणु
	वापस __inject_vm(kvm, पूर्णांकi);
पूर्ण

पूर्णांक s390पूर्णांक_to_s390irq(काष्ठा kvm_s390_पूर्णांकerrupt *s390पूर्णांक,
		       काष्ठा kvm_s390_irq *irq)
अणु
	irq->type = s390पूर्णांक->type;
	चयन (irq->type) अणु
	हाल KVM_S390_PROGRAM_INT:
		अगर (s390पूर्णांक->parm & 0xffff0000)
			वापस -EINVAL;
		irq->u.pgm.code = s390पूर्णांक->parm;
		अवरोध;
	हाल KVM_S390_SIGP_SET_PREFIX:
		irq->u.prefix.address = s390पूर्णांक->parm;
		अवरोध;
	हाल KVM_S390_SIGP_STOP:
		irq->u.stop.flags = s390पूर्णांक->parm;
		अवरोध;
	हाल KVM_S390_INT_EXTERNAL_CALL:
		अगर (s390पूर्णांक->parm & 0xffff0000)
			वापस -EINVAL;
		irq->u.extcall.code = s390पूर्णांक->parm;
		अवरोध;
	हाल KVM_S390_INT_EMERGENCY:
		अगर (s390पूर्णांक->parm & 0xffff0000)
			वापस -EINVAL;
		irq->u.emerg.code = s390पूर्णांक->parm;
		अवरोध;
	हाल KVM_S390_MCHK:
		irq->u.mchk.mcic = s390पूर्णांक->parm64;
		अवरोध;
	हाल KVM_S390_INT_PFAULT_INIT:
		irq->u.ext.ext_params = s390पूर्णांक->parm;
		irq->u.ext.ext_params2 = s390पूर्णांक->parm64;
		अवरोध;
	हाल KVM_S390_RESTART:
	हाल KVM_S390_INT_CLOCK_COMP:
	हाल KVM_S390_INT_CPU_TIMER:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_is_stop_irq_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	वापस test_bit(IRQ_PEND_SIGP_STOP, &li->pending_irqs);
पूर्ण

व्योम kvm_s390_clear_stop_irq(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;

	spin_lock(&li->lock);
	li->irq.stop.flags = 0;
	clear_bit(IRQ_PEND_SIGP_STOP, &li->pending_irqs);
	spin_unlock(&li->lock);
पूर्ण

अटल पूर्णांक करो_inject_vcpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	पूर्णांक rc;

	चयन (irq->type) अणु
	हाल KVM_S390_PROGRAM_INT:
		rc = __inject_prog(vcpu, irq);
		अवरोध;
	हाल KVM_S390_SIGP_SET_PREFIX:
		rc = __inject_set_prefix(vcpu, irq);
		अवरोध;
	हाल KVM_S390_SIGP_STOP:
		rc = __inject_sigp_stop(vcpu, irq);
		अवरोध;
	हाल KVM_S390_RESTART:
		rc = __inject_sigp_restart(vcpu);
		अवरोध;
	हाल KVM_S390_INT_CLOCK_COMP:
		rc = __inject_ckc(vcpu);
		अवरोध;
	हाल KVM_S390_INT_CPU_TIMER:
		rc = __inject_cpu_समयr(vcpu);
		अवरोध;
	हाल KVM_S390_INT_EXTERNAL_CALL:
		rc = __inject_extcall(vcpu, irq);
		अवरोध;
	हाल KVM_S390_INT_EMERGENCY:
		rc = __inject_sigp_emergency(vcpu, irq);
		अवरोध;
	हाल KVM_S390_MCHK:
		rc = __inject_mchk(vcpu, irq);
		अवरोध;
	हाल KVM_S390_INT_PFAULT_INIT:
		rc = __inject_pfault_init(vcpu, irq);
		अवरोध;
	हाल KVM_S390_INT_VIRTIO:
	हाल KVM_S390_INT_SERVICE:
	हाल KVM_S390_INT_IO_MIN...KVM_S390_INT_IO_MAX:
	शेष:
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक kvm_s390_inject_vcpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_irq *irq)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc;

	spin_lock(&li->lock);
	rc = करो_inject_vcpu(vcpu, irq);
	spin_unlock(&li->lock);
	अगर (!rc)
		kvm_s390_vcpu_wakeup(vcpu);
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम clear_irq_list(काष्ठा list_head *_list)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi, *n;

	list_क्रम_each_entry_safe(पूर्णांकi, n, _list, list) अणु
		list_del(&पूर्णांकi->list);
		kमुक्त(पूर्णांकi);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकi_to_irq(काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi,
		       काष्ठा kvm_s390_irq *irq)
अणु
	irq->type = पूर्णांकi->type;
	चयन (पूर्णांकi->type) अणु
	हाल KVM_S390_INT_PFAULT_INIT:
	हाल KVM_S390_INT_PFAULT_DONE:
	हाल KVM_S390_INT_VIRTIO:
		irq->u.ext = पूर्णांकi->ext;
		अवरोध;
	हाल KVM_S390_INT_IO_MIN...KVM_S390_INT_IO_MAX:
		irq->u.io = पूर्णांकi->io;
		अवरोध;
	पूर्ण
पूर्ण

व्योम kvm_s390_clear_भग्न_irqs(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;
	पूर्णांक i;

	mutex_lock(&kvm->lock);
	अगर (!kvm_s390_pv_is_रक्षित(kvm))
		fi->masked_irqs = 0;
	mutex_unlock(&kvm->lock);
	spin_lock(&fi->lock);
	fi->pending_irqs = 0;
	स_रखो(&fi->srv_संकेत, 0, माप(fi->srv_संकेत));
	स_रखो(&fi->mchk, 0, माप(fi->mchk));
	क्रम (i = 0; i < FIRQ_LIST_COUNT; i++)
		clear_irq_list(&fi->lists[i]);
	क्रम (i = 0; i < FIRQ_MAX_COUNT; i++)
		fi->counters[i] = 0;
	spin_unlock(&fi->lock);
	kvm_s390_gisa_clear(kvm);
पूर्ण;

अटल पूर्णांक get_all_भग्नing_irqs(काष्ठा kvm *kvm, u8 __user *usrbuf, u64 len)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi;
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi;
	काष्ठा kvm_s390_irq *buf;
	काष्ठा kvm_s390_irq *irq;
	पूर्णांक max_irqs;
	पूर्णांक ret = 0;
	पूर्णांक n = 0;
	पूर्णांक i;

	अगर (len > KVM_S390_FLIC_MAX_BUFFER || len == 0)
		वापस -EINVAL;

	/*
	 * We are alपढ़ोy using -ENOMEM to संकेत
	 * userspace it may retry with a bigger buffer,
	 * so we need to use something अन्यथा क्रम this हाल
	 */
	buf = vzalloc(len);
	अगर (!buf)
		वापस -ENOBUFS;

	max_irqs = len / माप(काष्ठा kvm_s390_irq);

	अगर (gi->origin && gisa_get_ipm(gi->origin)) अणु
		क्रम (i = 0; i <= MAX_ISC; i++) अणु
			अगर (n == max_irqs) अणु
				/* संकेत userspace to try again */
				ret = -ENOMEM;
				जाओ out_nolock;
			पूर्ण
			अगर (gisa_tac_ipm_gisc(gi->origin, i)) अणु
				irq = (काष्ठा kvm_s390_irq *) &buf[n];
				irq->type = KVM_S390_INT_IO(1, 0, 0, 0);
				irq->u.io.io_पूर्णांक_word = isc_to_पूर्णांक_word(i);
				n++;
			पूर्ण
		पूर्ण
	पूर्ण
	fi = &kvm->arch.भग्न_पूर्णांक;
	spin_lock(&fi->lock);
	क्रम (i = 0; i < FIRQ_LIST_COUNT; i++) अणु
		list_क्रम_each_entry(पूर्णांकi, &fi->lists[i], list) अणु
			अगर (n == max_irqs) अणु
				/* संकेत userspace to try again */
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			पूर्णांकi_to_irq(पूर्णांकi, &buf[n]);
			n++;
		पूर्ण
	पूर्ण
	अगर (test_bit(IRQ_PEND_EXT_SERVICE, &fi->pending_irqs) ||
	    test_bit(IRQ_PEND_EXT_SERVICE_EV, &fi->pending_irqs)) अणु
		अगर (n == max_irqs) अणु
			/* संकेत userspace to try again */
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		irq = (काष्ठा kvm_s390_irq *) &buf[n];
		irq->type = KVM_S390_INT_SERVICE;
		irq->u.ext = fi->srv_संकेत;
		n++;
	पूर्ण
	अगर (test_bit(IRQ_PEND_MCHK_REP, &fi->pending_irqs)) अणु
		अगर (n == max_irqs) अणु
				/* संकेत userspace to try again */
				ret = -ENOMEM;
				जाओ out;
		पूर्ण
		irq = (काष्ठा kvm_s390_irq *) &buf[n];
		irq->type = KVM_S390_MCHK;
		irq->u.mchk = fi->mchk;
		n++;
पूर्ण

out:
	spin_unlock(&fi->lock);
out_nolock:
	अगर (!ret && n > 0) अणु
		अगर (copy_to_user(usrbuf, buf, माप(काष्ठा kvm_s390_irq) * n))
			ret = -EFAULT;
	पूर्ण
	vमुक्त(buf);

	वापस ret < 0 ? ret : n;
पूर्ण

अटल पूर्णांक flic_ais_mode_get_all(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_ais_all ais;

	अगर (attr->attr < माप(ais))
		वापस -EINVAL;

	अगर (!test_kvm_facility(kvm, 72))
		वापस -EOPNOTSUPP;

	mutex_lock(&fi->ais_lock);
	ais.simm = fi->simm;
	ais.nimm = fi->nimm;
	mutex_unlock(&fi->ais_lock);

	अगर (copy_to_user((व्योम __user *)attr->addr, &ais, माप(ais)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक flic_get_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक r;

	चयन (attr->group) अणु
	हाल KVM_DEV_FLIC_GET_ALL_IRQS:
		r = get_all_भग्नing_irqs(dev->kvm, (u8 __user *) attr->addr,
					  attr->attr);
		अवरोध;
	हाल KVM_DEV_FLIC_AISM_ALL:
		r = flic_ais_mode_get_all(dev->kvm, attr);
		अवरोध;
	शेष:
		r = -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

अटल अंतरभूत पूर्णांक copy_irq_from_user(काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi,
				     u64 addr)
अणु
	काष्ठा kvm_s390_irq __user *uptr = (काष्ठा kvm_s390_irq __user *) addr;
	व्योम *target = शून्य;
	व्योम __user *source;
	u64 size;

	अगर (get_user(पूर्णांकi->type, (u64 __user *)addr))
		वापस -EFAULT;

	चयन (पूर्णांकi->type) अणु
	हाल KVM_S390_INT_PFAULT_INIT:
	हाल KVM_S390_INT_PFAULT_DONE:
	हाल KVM_S390_INT_VIRTIO:
	हाल KVM_S390_INT_SERVICE:
		target = (व्योम *) &पूर्णांकi->ext;
		source = &uptr->u.ext;
		size = माप(पूर्णांकi->ext);
		अवरोध;
	हाल KVM_S390_INT_IO_MIN...KVM_S390_INT_IO_MAX:
		target = (व्योम *) &पूर्णांकi->io;
		source = &uptr->u.io;
		size = माप(पूर्णांकi->io);
		अवरोध;
	हाल KVM_S390_MCHK:
		target = (व्योम *) &पूर्णांकi->mchk;
		source = &uptr->u.mchk;
		size = माप(पूर्णांकi->mchk);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(target, source, size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक enqueue_भग्नing_irq(काष्ठा kvm_device *dev,
				काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi = शून्य;
	पूर्णांक r = 0;
	पूर्णांक len = attr->attr;

	अगर (len % माप(काष्ठा kvm_s390_irq) != 0)
		वापस -EINVAL;
	अन्यथा अगर (len > KVM_S390_FLIC_MAX_BUFFER)
		वापस -EINVAL;

	जबतक (len >= माप(काष्ठा kvm_s390_irq)) अणु
		पूर्णांकi = kzalloc(माप(*पूर्णांकi), GFP_KERNEL_ACCOUNT);
		अगर (!पूर्णांकi)
			वापस -ENOMEM;

		r = copy_irq_from_user(पूर्णांकi, attr->addr);
		अगर (r) अणु
			kमुक्त(पूर्णांकi);
			वापस r;
		पूर्ण
		r = __inject_vm(dev->kvm, पूर्णांकi);
		अगर (r) अणु
			kमुक्त(पूर्णांकi);
			वापस r;
		पूर्ण
		len -= माप(काष्ठा kvm_s390_irq);
		attr->addr += माप(काष्ठा kvm_s390_irq);
	पूर्ण

	वापस r;
पूर्ण

अटल काष्ठा s390_io_adapter *get_io_adapter(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	अगर (id >= MAX_S390_IO_ADAPTERS)
		वापस शून्य;
	id = array_index_nospec(id, MAX_S390_IO_ADAPTERS);
	वापस kvm->arch.adapters[id];
पूर्ण

अटल पूर्णांक रेजिस्टर_io_adapter(काष्ठा kvm_device *dev,
			       काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा s390_io_adapter *adapter;
	काष्ठा kvm_s390_io_adapter adapter_info;

	अगर (copy_from_user(&adapter_info,
			   (व्योम __user *)attr->addr, माप(adapter_info)))
		वापस -EFAULT;

	अगर (adapter_info.id >= MAX_S390_IO_ADAPTERS)
		वापस -EINVAL;

	adapter_info.id = array_index_nospec(adapter_info.id,
					     MAX_S390_IO_ADAPTERS);

	अगर (dev->kvm->arch.adapters[adapter_info.id] != शून्य)
		वापस -EINVAL;

	adapter = kzalloc(माप(*adapter), GFP_KERNEL_ACCOUNT);
	अगर (!adapter)
		वापस -ENOMEM;

	adapter->id = adapter_info.id;
	adapter->isc = adapter_info.isc;
	adapter->maskable = adapter_info.maskable;
	adapter->masked = false;
	adapter->swap = adapter_info.swap;
	adapter->suppressible = (adapter_info.flags) &
				KVM_S390_ADAPTER_SUPPRESSIBLE;
	dev->kvm->arch.adapters[adapter->id] = adapter;

	वापस 0;
पूर्ण

पूर्णांक kvm_s390_mask_adapter(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id, bool masked)
अणु
	पूर्णांक ret;
	काष्ठा s390_io_adapter *adapter = get_io_adapter(kvm, id);

	अगर (!adapter || !adapter->maskable)
		वापस -EINVAL;
	ret = adapter->masked;
	adapter->masked = masked;
	वापस ret;
पूर्ण

व्योम kvm_s390_destroy_adapters(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_S390_IO_ADAPTERS; i++)
		kमुक्त(kvm->arch.adapters[i]);
पूर्ण

अटल पूर्णांक modअगरy_io_adapter(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_io_adapter_req req;
	काष्ठा s390_io_adapter *adapter;
	पूर्णांक ret;

	अगर (copy_from_user(&req, (व्योम __user *)attr->addr, माप(req)))
		वापस -EFAULT;

	adapter = get_io_adapter(dev->kvm, req.id);
	अगर (!adapter)
		वापस -EINVAL;
	चयन (req.type) अणु
	हाल KVM_S390_IO_ADAPTER_MASK:
		ret = kvm_s390_mask_adapter(dev->kvm, req.id, req.mask);
		अगर (ret > 0)
			ret = 0;
		अवरोध;
	/*
	 * The following operations are no दीर्घer needed and thereक्रमe no-ops.
	 * The gpa to hva translation is करोne when an IRQ route is set up. The
	 * set_irq code uses get_user_pages_remote() to करो the actual ग_लिखो.
	 */
	हाल KVM_S390_IO_ADAPTER_MAP:
	हाल KVM_S390_IO_ADAPTER_UNMAP:
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clear_io_irq(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)

अणु
	स्थिर u64 isc_mask = 0xffUL << 24; /* all iscs set */
	u32 schid;

	अगर (attr->flags)
		वापस -EINVAL;
	अगर (attr->attr != माप(schid))
		वापस -EINVAL;
	अगर (copy_from_user(&schid, (व्योम __user *) attr->addr, माप(schid)))
		वापस -EFAULT;
	अगर (!schid)
		वापस -EINVAL;
	kमुक्त(kvm_s390_get_io_पूर्णांक(kvm, isc_mask, schid));
	/*
	 * If userspace is conक्रमming to the architecture, we can have at most
	 * one pending I/O पूर्णांकerrupt per subchannel, so this is effectively a
	 * clear all.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक modअगरy_ais_mode(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_ais_req req;
	पूर्णांक ret = 0;

	अगर (!test_kvm_facility(kvm, 72))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&req, (व्योम __user *)attr->addr, माप(req)))
		वापस -EFAULT;

	अगर (req.isc > MAX_ISC)
		वापस -EINVAL;

	trace_kvm_s390_modअगरy_ais_mode(req.isc,
				       (fi->simm & AIS_MODE_MASK(req.isc)) ?
				       (fi->nimm & AIS_MODE_MASK(req.isc)) ?
				       2 : KVM_S390_AIS_MODE_SINGLE :
				       KVM_S390_AIS_MODE_ALL, req.mode);

	mutex_lock(&fi->ais_lock);
	चयन (req.mode) अणु
	हाल KVM_S390_AIS_MODE_ALL:
		fi->simm &= ~AIS_MODE_MASK(req.isc);
		fi->nimm &= ~AIS_MODE_MASK(req.isc);
		अवरोध;
	हाल KVM_S390_AIS_MODE_SINGLE:
		fi->simm |= AIS_MODE_MASK(req.isc);
		fi->nimm &= ~AIS_MODE_MASK(req.isc);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&fi->ais_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_inject_airq(काष्ठा kvm *kvm,
				काष्ठा s390_io_adapter *adapter)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_पूर्णांकerrupt s390पूर्णांक = अणु
		.type = KVM_S390_INT_IO(1, 0, 0, 0),
		.parm = 0,
		.parm64 = isc_to_पूर्णांक_word(adapter->isc),
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (!test_kvm_facility(kvm, 72) || !adapter->suppressible)
		वापस kvm_s390_inject_vm(kvm, &s390पूर्णांक);

	mutex_lock(&fi->ais_lock);
	अगर (fi->nimm & AIS_MODE_MASK(adapter->isc)) अणु
		trace_kvm_s390_airq_suppressed(adapter->id, adapter->isc);
		जाओ out;
	पूर्ण

	ret = kvm_s390_inject_vm(kvm, &s390पूर्णांक);
	अगर (!ret && (fi->simm & AIS_MODE_MASK(adapter->isc))) अणु
		fi->nimm |= AIS_MODE_MASK(adapter->isc);
		trace_kvm_s390_modअगरy_ais_mode(adapter->isc,
					       KVM_S390_AIS_MODE_SINGLE, 2);
	पूर्ण
out:
	mutex_unlock(&fi->ais_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक flic_inject_airq(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	अचिन्हित पूर्णांक id = attr->attr;
	काष्ठा s390_io_adapter *adapter = get_io_adapter(kvm, id);

	अगर (!adapter)
		वापस -EINVAL;

	वापस kvm_s390_inject_airq(kvm, adapter);
पूर्ण

अटल पूर्णांक flic_ais_mode_set_all(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &kvm->arch.भग्न_पूर्णांक;
	काष्ठा kvm_s390_ais_all ais;

	अगर (!test_kvm_facility(kvm, 72))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&ais, (व्योम __user *)attr->addr, माप(ais)))
		वापस -EFAULT;

	mutex_lock(&fi->ais_lock);
	fi->simm = ais.simm;
	fi->nimm = ais.nimm;
	mutex_unlock(&fi->ais_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक flic_set_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक r = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	चयन (attr->group) अणु
	हाल KVM_DEV_FLIC_ENQUEUE:
		r = enqueue_भग्नing_irq(dev, attr);
		अवरोध;
	हाल KVM_DEV_FLIC_CLEAR_IRQS:
		kvm_s390_clear_भग्न_irqs(dev->kvm);
		अवरोध;
	हाल KVM_DEV_FLIC_APF_ENABLE:
		dev->kvm->arch.gmap->pfault_enabled = 1;
		अवरोध;
	हाल KVM_DEV_FLIC_APF_DISABLE_WAIT:
		dev->kvm->arch.gmap->pfault_enabled = 0;
		/*
		 * Make sure no async faults are in transition when
		 * clearing the queues. So we करोn't need to worry
		 * about late coming workers.
		 */
		synchronize_srcu(&dev->kvm->srcu);
		kvm_क्रम_each_vcpu(i, vcpu, dev->kvm)
			kvm_clear_async_pf_completion_queue(vcpu);
		अवरोध;
	हाल KVM_DEV_FLIC_ADAPTER_REGISTER:
		r = रेजिस्टर_io_adapter(dev, attr);
		अवरोध;
	हाल KVM_DEV_FLIC_ADAPTER_MODIFY:
		r = modअगरy_io_adapter(dev, attr);
		अवरोध;
	हाल KVM_DEV_FLIC_CLEAR_IO_IRQ:
		r = clear_io_irq(dev->kvm, attr);
		अवरोध;
	हाल KVM_DEV_FLIC_AISM:
		r = modअगरy_ais_mode(dev->kvm, attr);
		अवरोध;
	हाल KVM_DEV_FLIC_AIRQ_INJECT:
		r = flic_inject_airq(dev->kvm, attr);
		अवरोध;
	हाल KVM_DEV_FLIC_AISM_ALL:
		r = flic_ais_mode_set_all(dev->kvm, attr);
		अवरोध;
	शेष:
		r = -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक flic_has_attr(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_FLIC_GET_ALL_IRQS:
	हाल KVM_DEV_FLIC_ENQUEUE:
	हाल KVM_DEV_FLIC_CLEAR_IRQS:
	हाल KVM_DEV_FLIC_APF_ENABLE:
	हाल KVM_DEV_FLIC_APF_DISABLE_WAIT:
	हाल KVM_DEV_FLIC_ADAPTER_REGISTER:
	हाल KVM_DEV_FLIC_ADAPTER_MODIFY:
	हाल KVM_DEV_FLIC_CLEAR_IO_IRQ:
	हाल KVM_DEV_FLIC_AISM:
	हाल KVM_DEV_FLIC_AIRQ_INJECT:
	हाल KVM_DEV_FLIC_AISM_ALL:
		वापस 0;
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक flic_create(काष्ठा kvm_device *dev, u32 type)
अणु
	अगर (!dev)
		वापस -EINVAL;
	अगर (dev->kvm->arch.flic)
		वापस -EINVAL;
	dev->kvm->arch.flic = dev;
	वापस 0;
पूर्ण

अटल व्योम flic_destroy(काष्ठा kvm_device *dev)
अणु
	dev->kvm->arch.flic = शून्य;
	kमुक्त(dev);
पूर्ण

/* s390 भग्नing irq controller (flic) */
काष्ठा kvm_device_ops kvm_flic_ops = अणु
	.name = "kvm-flic",
	.get_attr = flic_get_attr,
	.set_attr = flic_set_attr,
	.has_attr = flic_has_attr,
	.create = flic_create,
	.destroy = flic_destroy,
पूर्ण;

अटल अचिन्हित दीर्घ get_ind_bit(__u64 addr, अचिन्हित दीर्घ bit_nr, bool swap)
अणु
	अचिन्हित दीर्घ bit;

	bit = bit_nr + (addr % PAGE_SIZE) * 8;

	वापस swap ? (bit ^ (BITS_PER_LONG - 1)) : bit;
पूर्ण

अटल काष्ठा page *get_map_page(काष्ठा kvm *kvm, u64 uaddr)
अणु
	काष्ठा page *page = शून्य;

	mmap_पढ़ो_lock(kvm->mm);
	get_user_pages_remote(kvm->mm, uaddr, 1, FOLL_WRITE,
			      &page, शून्य, शून्य);
	mmap_पढ़ो_unlock(kvm->mm);
	वापस page;
पूर्ण

अटल पूर्णांक adapter_indicators_set(काष्ठा kvm *kvm,
				  काष्ठा s390_io_adapter *adapter,
				  काष्ठा kvm_s390_adapter_पूर्णांक *adapter_पूर्णांक)
अणु
	अचिन्हित दीर्घ bit;
	पूर्णांक summary_set, idx;
	काष्ठा page *ind_page, *summary_page;
	व्योम *map;

	ind_page = get_map_page(kvm, adapter_पूर्णांक->ind_addr);
	अगर (!ind_page)
		वापस -1;
	summary_page = get_map_page(kvm, adapter_पूर्णांक->summary_addr);
	अगर (!summary_page) अणु
		put_page(ind_page);
		वापस -1;
	पूर्ण

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	map = page_address(ind_page);
	bit = get_ind_bit(adapter_पूर्णांक->ind_addr,
			  adapter_पूर्णांक->ind_offset, adapter->swap);
	set_bit(bit, map);
	mark_page_dirty(kvm, adapter_पूर्णांक->ind_addr >> PAGE_SHIFT);
	set_page_dirty_lock(ind_page);
	map = page_address(summary_page);
	bit = get_ind_bit(adapter_पूर्णांक->summary_addr,
			  adapter_पूर्णांक->summary_offset, adapter->swap);
	summary_set = test_and_set_bit(bit, map);
	mark_page_dirty(kvm, adapter_पूर्णांक->summary_addr >> PAGE_SHIFT);
	set_page_dirty_lock(summary_page);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);

	put_page(ind_page);
	put_page(summary_page);
	वापस summary_set ? 0 : 1;
पूर्ण

/*
 * < 0 - not injected due to error
 * = 0 - coalesced, summary indicator alपढ़ोy active
 * > 0 - injected पूर्णांकerrupt
 */
अटल पूर्णांक set_adapter_पूर्णांक(काष्ठा kvm_kernel_irq_routing_entry *e,
			   काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
			   bool line_status)
अणु
	पूर्णांक ret;
	काष्ठा s390_io_adapter *adapter;

	/* We're only पूर्णांकerested in the 0->1 transition. */
	अगर (!level)
		वापस 0;
	adapter = get_io_adapter(kvm, e->adapter.adapter_id);
	अगर (!adapter)
		वापस -1;
	ret = adapter_indicators_set(kvm, adapter, &e->adapter);
	अगर ((ret > 0) && !adapter->masked) अणु
		ret = kvm_s390_inject_airq(kvm, adapter);
		अगर (ret == 0)
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Inject the machine check to the guest.
 */
व्योम kvm_s390_reinject_machine_check(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा mcck_अस्थिर_info *mcck_info)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info पूर्णांकi;
	काष्ठा kvm_s390_irq irq;
	काष्ठा kvm_s390_mchk_info *mchk;
	जोड़ mci mci;
	__u64 cr14 = 0;         /* upper bits are not used */
	पूर्णांक rc;

	mci.val = mcck_info->mcic;
	अगर (mci.sr)
		cr14 |= CR14_RECOVERY_SUBMASK;
	अगर (mci.dg)
		cr14 |= CR14_DEGRADATION_SUBMASK;
	अगर (mci.w)
		cr14 |= CR14_WARNING_SUBMASK;

	mchk = mci.ck ? &पूर्णांकi.mchk : &irq.u.mchk;
	mchk->cr14 = cr14;
	mchk->mcic = mcck_info->mcic;
	mchk->ext_damage_code = mcck_info->ext_damage_code;
	mchk->failing_storage_address = mcck_info->failing_storage_address;
	अगर (mci.ck) अणु
		/* Inject the भग्नing machine check */
		पूर्णांकi.type = KVM_S390_MCHK;
		rc = __inject_vm(vcpu->kvm, &पूर्णांकi);
	पूर्ण अन्यथा अणु
		/* Inject the machine check to specअगरied vcpu */
		irq.type = KVM_S390_MCHK;
		rc = kvm_s390_inject_vcpu(vcpu, &irq);
	पूर्ण
	WARN_ON_ONCE(rc);
पूर्ण

पूर्णांक kvm_set_routing_entry(काष्ठा kvm *kvm,
			  काष्ठा kvm_kernel_irq_routing_entry *e,
			  स्थिर काष्ठा kvm_irq_routing_entry *ue)
अणु
	u64 uaddr;

	चयन (ue->type) अणु
	/* we store the userspace addresses instead of the guest addresses */
	हाल KVM_IRQ_ROUTING_S390_ADAPTER:
		e->set = set_adapter_पूर्णांक;
		uaddr =  gmap_translate(kvm->arch.gmap, ue->u.adapter.summary_addr);
		अगर (uaddr == -EFAULT)
			वापस -EFAULT;
		e->adapter.summary_addr = uaddr;
		uaddr =  gmap_translate(kvm->arch.gmap, ue->u.adapter.ind_addr);
		अगर (uaddr == -EFAULT)
			वापस -EFAULT;
		e->adapter.ind_addr = uaddr;
		e->adapter.summary_offset = ue->u.adapter.summary_offset;
		e->adapter.ind_offset = ue->u.adapter.ind_offset;
		e->adapter.adapter_id = ue->u.adapter.adapter_id;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक kvm_set_msi(काष्ठा kvm_kernel_irq_routing_entry *e, काष्ठा kvm *kvm,
		पूर्णांक irq_source_id, पूर्णांक level, bool line_status)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_s390_set_irq_state(काष्ठा kvm_vcpu *vcpu, व्योम __user *irqstate, पूर्णांक len)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	काष्ठा kvm_s390_irq *buf;
	पूर्णांक r = 0;
	पूर्णांक n;

	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (copy_from_user((व्योम *) buf, irqstate, len)) अणु
		r = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	/*
	 * Don't allow setting the पूर्णांकerrupt state
	 * when there are alपढ़ोy पूर्णांकerrupts pending
	 */
	spin_lock(&li->lock);
	अगर (li->pending_irqs) अणु
		r = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	क्रम (n = 0; n < len / माप(*buf); n++) अणु
		r = करो_inject_vcpu(vcpu, &buf[n]);
		अगर (r)
			अवरोध;
	पूर्ण

out_unlock:
	spin_unlock(&li->lock);
out_मुक्त:
	vमुक्त(buf);

	वापस r;
पूर्ण

अटल व्योम store_local_irq(काष्ठा kvm_s390_local_पूर्णांकerrupt *li,
			    काष्ठा kvm_s390_irq *irq,
			    अचिन्हित दीर्घ irq_type)
अणु
	चयन (irq_type) अणु
	हाल IRQ_PEND_MCHK_EX:
	हाल IRQ_PEND_MCHK_REP:
		irq->type = KVM_S390_MCHK;
		irq->u.mchk = li->irq.mchk;
		अवरोध;
	हाल IRQ_PEND_PROG:
		irq->type = KVM_S390_PROGRAM_INT;
		irq->u.pgm = li->irq.pgm;
		अवरोध;
	हाल IRQ_PEND_PFAULT_INIT:
		irq->type = KVM_S390_INT_PFAULT_INIT;
		irq->u.ext = li->irq.ext;
		अवरोध;
	हाल IRQ_PEND_EXT_EXTERNAL:
		irq->type = KVM_S390_INT_EXTERNAL_CALL;
		irq->u.extcall = li->irq.extcall;
		अवरोध;
	हाल IRQ_PEND_EXT_CLOCK_COMP:
		irq->type = KVM_S390_INT_CLOCK_COMP;
		अवरोध;
	हाल IRQ_PEND_EXT_CPU_TIMER:
		irq->type = KVM_S390_INT_CPU_TIMER;
		अवरोध;
	हाल IRQ_PEND_SIGP_STOP:
		irq->type = KVM_S390_SIGP_STOP;
		irq->u.stop = li->irq.stop;
		अवरोध;
	हाल IRQ_PEND_RESTART:
		irq->type = KVM_S390_RESTART;
		अवरोध;
	हाल IRQ_PEND_SET_PREFIX:
		irq->type = KVM_S390_SIGP_SET_PREFIX;
		irq->u.prefix = li->irq.prefix;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक kvm_s390_get_irq_state(काष्ठा kvm_vcpu *vcpu, __u8 __user *buf, पूर्णांक len)
अणु
	पूर्णांक scn;
	DECLARE_BITMAP(sigp_emerg_pending, KVM_MAX_VCPUS);
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	अचिन्हित दीर्घ pending_irqs;
	काष्ठा kvm_s390_irq irq;
	अचिन्हित दीर्घ irq_type;
	पूर्णांक cpuaddr;
	पूर्णांक n = 0;

	spin_lock(&li->lock);
	pending_irqs = li->pending_irqs;
	स_नकल(&sigp_emerg_pending, &li->sigp_emerg_pending,
	       माप(sigp_emerg_pending));
	spin_unlock(&li->lock);

	क्रम_each_set_bit(irq_type, &pending_irqs, IRQ_PEND_COUNT) अणु
		स_रखो(&irq, 0, माप(irq));
		अगर (irq_type == IRQ_PEND_EXT_EMERGENCY)
			जारी;
		अगर (n + माप(irq) > len)
			वापस -ENOBUFS;
		store_local_irq(&vcpu->arch.local_पूर्णांक, &irq, irq_type);
		अगर (copy_to_user(&buf[n], &irq, माप(irq)))
			वापस -EFAULT;
		n += माप(irq);
	पूर्ण

	अगर (test_bit(IRQ_PEND_EXT_EMERGENCY, &pending_irqs)) अणु
		क्रम_each_set_bit(cpuaddr, sigp_emerg_pending, KVM_MAX_VCPUS) अणु
			स_रखो(&irq, 0, माप(irq));
			अगर (n + माप(irq) > len)
				वापस -ENOBUFS;
			irq.type = KVM_S390_INT_EMERGENCY;
			irq.u.emerg.code = cpuaddr;
			अगर (copy_to_user(&buf[n], &irq, माप(irq)))
				वापस -EFAULT;
			n += माप(irq);
		पूर्ण
	पूर्ण

	अगर (sca_ext_call_pending(vcpu, &scn)) अणु
		अगर (n + माप(irq) > len)
			वापस -ENOBUFS;
		स_रखो(&irq, 0, माप(irq));
		irq.type = KVM_S390_INT_EXTERNAL_CALL;
		irq.u.extcall.code = scn;
		अगर (copy_to_user(&buf[n], &irq, माप(irq)))
			वापस -EFAULT;
		n += माप(irq);
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम __airqs_kick_single_vcpu(काष्ठा kvm *kvm, u8 deliverable_mask)
अणु
	पूर्णांक vcpu_id, online_vcpus = atomic_पढ़ो(&kvm->online_vcpus);
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;
	काष्ठा kvm_vcpu *vcpu;

	क्रम_each_set_bit(vcpu_id, kvm->arch.idle_mask, online_vcpus) अणु
		vcpu = kvm_get_vcpu(kvm, vcpu_id);
		अगर (psw_ioपूर्णांक_disabled(vcpu))
			जारी;
		deliverable_mask &= (u8)(vcpu->arch.sie_block->gcr[6] >> 24);
		अगर (deliverable_mask) अणु
			/* lately kicked but not yet running */
			अगर (test_and_set_bit(vcpu_id, gi->kicked_mask))
				वापस;
			kvm_s390_vcpu_wakeup(vcpu);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart gisa_vcpu_kicker(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi =
		container_of(समयr, काष्ठा kvm_s390_gisa_पूर्णांकerrupt, समयr);
	काष्ठा kvm *kvm =
		container_of(gi->origin, काष्ठा sie_page2, gisa)->kvm;
	u8 pending_mask;

	pending_mask = gisa_get_ipm_or_restore_iam(gi);
	अगर (pending_mask) अणु
		__airqs_kick_single_vcpu(kvm, pending_mask);
		hrसमयr_क्रमward_now(समयr, ns_to_kसमय(gi->expires));
		वापस HRTIMER_RESTART;
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

#घोषणा शून्य_GISA_ADDR 0x00000000UL
#घोषणा NONE_GISA_ADDR 0x00000001UL
#घोषणा GISA_ADDR_MASK 0xfffff000UL

अटल व्योम process_gib_alert_list(व्योम)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi;
	काष्ठा kvm_s390_gisa *gisa;
	काष्ठा kvm *kvm;
	u32 final, origin = 0UL;

	करो अणु
		/*
		 * If the NONE_GISA_ADDR is still stored in the alert list
		 * origin, we will leave the outer loop. No further GISA has
		 * been added to the alert list by millicode जबतक processing
		 * the current alert list.
		 */
		final = (origin & NONE_GISA_ADDR);
		/*
		 * Cut off the alert list and store the NONE_GISA_ADDR in the
		 * alert list origin to aव्योम further GAL पूर्णांकerruptions.
		 * A new alert list can be build up by millicode in parallel
		 * क्रम guests not in the yet cut-off alert list. When in the
		 * final loop, store the शून्य_GISA_ADDR instead. This will re-
		 * enable GAL पूर्णांकerruptions on the host again.
		 */
		origin = xchg(&gib->alert_list_origin,
			      (!final) ? NONE_GISA_ADDR : शून्य_GISA_ADDR);
		/*
		 * Loop through the just cut-off alert list and start the
		 * gisa समयrs to kick idle vcpus to consume the pending
		 * पूर्णांकerruptions asap.
		 */
		जबतक (origin & GISA_ADDR_MASK) अणु
			gisa = (काष्ठा kvm_s390_gisa *)(u64)origin;
			origin = gisa->next_alert;
			gisa->next_alert = (u32)(u64)gisa;
			kvm = container_of(gisa, काष्ठा sie_page2, gisa)->kvm;
			gi = &kvm->arch.gisa_पूर्णांक;
			अगर (hrसमयr_active(&gi->समयr))
				hrसमयr_cancel(&gi->समयr);
			hrसमयr_start(&gi->समयr, 0, HRTIMER_MODE_REL);
		पूर्ण
	पूर्ण जबतक (!final);

पूर्ण

व्योम kvm_s390_gisa_clear(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;

	अगर (!gi->origin)
		वापस;
	gisa_clear_ipm(gi->origin);
	VM_EVENT(kvm, 3, "gisa 0x%pK cleared", gi->origin);
पूर्ण

व्योम kvm_s390_gisa_init(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;

	अगर (!css_general_अक्षरacteristics.aiv)
		वापस;
	gi->origin = &kvm->arch.sie_page2->gisa;
	gi->alert.mask = 0;
	spin_lock_init(&gi->alert.ref_lock);
	gi->expires = 50 * 1000; /* 50 usec */
	hrसमयr_init(&gi->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	gi->समयr.function = gisa_vcpu_kicker;
	स_रखो(gi->origin, 0, माप(काष्ठा kvm_s390_gisa));
	gi->origin->next_alert = (u32)(u64)gi->origin;
	VM_EVENT(kvm, 3, "gisa 0x%pK initialized", gi->origin);
पूर्ण

व्योम kvm_s390_gisa_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;

	अगर (!gi->origin)
		वापस;
	अगर (gi->alert.mask)
		KVM_EVENT(3, "vm 0x%pK has unexpected iam 0x%02x",
			  kvm, gi->alert.mask);
	जबतक (gisa_in_alert_list(gi->origin))
		cpu_relax();
	hrसमयr_cancel(&gi->समयr);
	gi->origin = शून्य;
पूर्ण

/**
 * kvm_s390_gisc_रेजिस्टर - रेजिस्टर a guest ISC
 *
 * @kvm:  the kernel vm to work with
 * @gisc: the guest पूर्णांकerruption sub class to रेजिस्टर
 *
 * The function extends the vm specअगरic alert mask to use.
 * The effective IAM mask in the GISA is updated as well
 * in हाल the GISA is not part of the GIB alert list.
 * It will be updated latest when the IAM माला_लो restored
 * by gisa_get_ipm_or_restore_iam().
 *
 * Returns: the nonspecअगरic ISC (NISC) the gib alert mechanism
 *          has रेजिस्टरed with the channel subप्रणाली.
 *          -ENODEV in हाल the vm uses no GISA
 *          -दुस्फल in हाल the guest ISC is invalid
 */
पूर्णांक kvm_s390_gisc_रेजिस्टर(काष्ठा kvm *kvm, u32 gisc)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;

	अगर (!gi->origin)
		वापस -ENODEV;
	अगर (gisc > MAX_ISC)
		वापस -दुस्फल;

	spin_lock(&gi->alert.ref_lock);
	gi->alert.ref_count[gisc]++;
	अगर (gi->alert.ref_count[gisc] == 1) अणु
		gi->alert.mask |= 0x80 >> gisc;
		gisa_set_iam(gi->origin, gi->alert.mask);
	पूर्ण
	spin_unlock(&gi->alert.ref_lock);

	वापस gib->nisc;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_s390_gisc_रेजिस्टर);

/**
 * kvm_s390_gisc_unरेजिस्टर - unरेजिस्टर a guest ISC
 *
 * @kvm:  the kernel vm to work with
 * @gisc: the guest पूर्णांकerruption sub class to रेजिस्टर
 *
 * The function reduces the vm specअगरic alert mask to use.
 * The effective IAM mask in the GISA is updated as well
 * in हाल the GISA is not part of the GIB alert list.
 * It will be updated latest when the IAM माला_लो restored
 * by gisa_get_ipm_or_restore_iam().
 *
 * Returns: the nonspecअगरic ISC (NISC) the gib alert mechanism
 *          has रेजिस्टरed with the channel subप्रणाली.
 *          -ENODEV in हाल the vm uses no GISA
 *          -दुस्फल in हाल the guest ISC is invalid
 *          -EINVAL in हाल the guest ISC is not रेजिस्टरed
 */
पूर्णांक kvm_s390_gisc_unरेजिस्टर(काष्ठा kvm *kvm, u32 gisc)
अणु
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt *gi = &kvm->arch.gisa_पूर्णांक;
	पूर्णांक rc = 0;

	अगर (!gi->origin)
		वापस -ENODEV;
	अगर (gisc > MAX_ISC)
		वापस -दुस्फल;

	spin_lock(&gi->alert.ref_lock);
	अगर (gi->alert.ref_count[gisc] == 0) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	gi->alert.ref_count[gisc]--;
	अगर (gi->alert.ref_count[gisc] == 0) अणु
		gi->alert.mask &= ~(0x80 >> gisc);
		gisa_set_iam(gi->origin, gi->alert.mask);
	पूर्ण
out:
	spin_unlock(&gi->alert.ref_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_s390_gisc_unरेजिस्टर);

अटल व्योम gib_alert_irq_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing)
अणु
	inc_irq_stat(IRQIO_GAL);
	process_gib_alert_list();
पूर्ण

अटल काष्ठा airq_काष्ठा gib_alert_irq = अणु
	.handler = gib_alert_irq_handler,
	.lsi_ptr = &gib_alert_irq.lsi_mask,
पूर्ण;

व्योम kvm_s390_gib_destroy(व्योम)
अणु
	अगर (!gib)
		वापस;
	chsc_sgib(0);
	unरेजिस्टर_adapter_पूर्णांकerrupt(&gib_alert_irq);
	मुक्त_page((अचिन्हित दीर्घ)gib);
	gib = शून्य;
पूर्ण

पूर्णांक kvm_s390_gib_init(u8 nisc)
अणु
	पूर्णांक rc = 0;

	अगर (!css_general_अक्षरacteristics.aiv) अणु
		KVM_EVENT(3, "%s", "gib not initialized, no AIV facility");
		जाओ out;
	पूर्ण

	gib = (काष्ठा kvm_s390_gib *)get_zeroed_page(GFP_KERNEL_ACCOUNT | GFP_DMA);
	अगर (!gib) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	gib_alert_irq.isc = nisc;
	अगर (रेजिस्टर_adapter_पूर्णांकerrupt(&gib_alert_irq)) अणु
		pr_err("Registering the GIB alert interruption handler failed\n");
		rc = -EIO;
		जाओ out_मुक्त_gib;
	पूर्ण

	gib->nisc = nisc;
	अगर (chsc_sgib((u32)(u64)gib)) अणु
		pr_err("Associating the GIB with the AIV facility failed\n");
		मुक्त_page((अचिन्हित दीर्घ)gib);
		gib = शून्य;
		rc = -EIO;
		जाओ out_unreg_gal;
	पूर्ण

	KVM_EVENT(3, "gib 0x%pK (nisc=%d) initialized", gib, gib->nisc);
	जाओ out;

out_unreg_gal:
	unरेजिस्टर_adapter_पूर्णांकerrupt(&gib_alert_irq);
out_मुक्त_gib:
	मुक्त_page((अचिन्हित दीर्घ)gib);
	gib = शून्य;
out:
	वापस rc;
पूर्ण
