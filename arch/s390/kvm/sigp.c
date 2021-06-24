<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * handling पूर्णांकerprocessor communication
 *
 * Copyright IBM Corp. 2008, 2013
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 *               Christian Ehrhardt <ehrhardt@de.ibm.com>
 */

#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/sigp.h>
#समावेश "gaccess.h"
#समावेश "kvm-s390.h"
#समावेश "trace.h"

अटल पूर्णांक __sigp_sense(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_vcpu *dst_vcpu,
			u64 *reg)
अणु
	स्थिर bool stopped = kvm_s390_test_cpuflags(dst_vcpu, CPUSTAT_STOPPED);
	पूर्णांक rc;
	पूर्णांक ext_call_pending;

	ext_call_pending = kvm_s390_ext_call_pending(dst_vcpu);
	अगर (!stopped && !ext_call_pending)
		rc = SIGP_CC_ORDER_CODE_ACCEPTED;
	अन्यथा अणु
		*reg &= 0xffffffff00000000UL;
		अगर (ext_call_pending)
			*reg |= SIGP_STATUS_EXT_CALL_PENDING;
		अगर (stopped)
			*reg |= SIGP_STATUS_STOPPED;
		rc = SIGP_CC_STATUS_STORED;
	पूर्ण

	VCPU_EVENT(vcpu, 4, "sensed status of cpu %x rc %x", dst_vcpu->vcpu_id,
		   rc);
	वापस rc;
पूर्ण

अटल पूर्णांक __inject_sigp_emergency(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_vcpu *dst_vcpu)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_INT_EMERGENCY,
		.u.emerg.code = vcpu->vcpu_id,
	पूर्ण;
	पूर्णांक rc = 0;

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	अगर (!rc)
		VCPU_EVENT(vcpu, 4, "sent sigp emerg to cpu %x",
			   dst_vcpu->vcpu_id);

	वापस rc ? rc : SIGP_CC_ORDER_CODE_ACCEPTED;
पूर्ण

अटल पूर्णांक __sigp_emergency(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_vcpu *dst_vcpu)
अणु
	वापस __inject_sigp_emergency(vcpu, dst_vcpu);
पूर्ण

अटल पूर्णांक __sigp_conditional_emergency(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_vcpu *dst_vcpu,
					u16 asn, u64 *reg)
अणु
	स्थिर u64 psw_पूर्णांक_mask = PSW_MASK_IO | PSW_MASK_EXT;
	u16 p_asn, s_asn;
	psw_t *psw;
	bool idle;

	idle = is_vcpu_idle(vcpu);
	psw = &dst_vcpu->arch.sie_block->gpsw;
	p_asn = dst_vcpu->arch.sie_block->gcr[4] & 0xffff;  /* Primary ASN */
	s_asn = dst_vcpu->arch.sie_block->gcr[3] & 0xffff;  /* Secondary ASN */

	/* Inject the emergency संकेत? */
	अगर (!is_vcpu_stopped(vcpu)
	    || (psw->mask & psw_पूर्णांक_mask) != psw_पूर्णांक_mask
	    || (idle && psw->addr != 0)
	    || (!idle && (asn == p_asn || asn == s_asn))) अणु
		वापस __inject_sigp_emergency(vcpu, dst_vcpu);
	पूर्ण अन्यथा अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INCORRECT_STATE;
		वापस SIGP_CC_STATUS_STORED;
	पूर्ण
पूर्ण

अटल पूर्णांक __sigp_बाह्यal_call(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_vcpu *dst_vcpu, u64 *reg)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_INT_EXTERNAL_CALL,
		.u.extcall.code = vcpu->vcpu_id,
	पूर्ण;
	पूर्णांक rc;

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	अगर (rc == -EBUSY) अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_EXT_CALL_PENDING;
		वापस SIGP_CC_STATUS_STORED;
	पूर्ण अन्यथा अगर (rc == 0) अणु
		VCPU_EVENT(vcpu, 4, "sent sigp ext call to cpu %x",
			   dst_vcpu->vcpu_id);
	पूर्ण

	वापस rc ? rc : SIGP_CC_ORDER_CODE_ACCEPTED;
पूर्ण

अटल पूर्णांक __sigp_stop(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_vcpu *dst_vcpu)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_SIGP_STOP,
	पूर्ण;
	पूर्णांक rc;

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	अगर (rc == -EBUSY)
		rc = SIGP_CC_BUSY;
	अन्यथा अगर (rc == 0)
		VCPU_EVENT(vcpu, 4, "sent sigp stop to cpu %x",
			   dst_vcpu->vcpu_id);

	वापस rc;
पूर्ण

अटल पूर्णांक __sigp_stop_and_store_status(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_vcpu *dst_vcpu, u64 *reg)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_SIGP_STOP,
		.u.stop.flags = KVM_S390_STOP_FLAG_STORE_STATUS,
	पूर्ण;
	पूर्णांक rc;

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	अगर (rc == -EBUSY)
		rc = SIGP_CC_BUSY;
	अन्यथा अगर (rc == 0)
		VCPU_EVENT(vcpu, 4, "sent sigp stop and store status to cpu %x",
			   dst_vcpu->vcpu_id);

	वापस rc;
पूर्ण

अटल पूर्णांक __sigp_set_arch(काष्ठा kvm_vcpu *vcpu, u32 parameter,
			   u64 *status_reg)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *v;
	bool all_stopped = true;

	kvm_क्रम_each_vcpu(i, v, vcpu->kvm) अणु
		अगर (v == vcpu)
			जारी;
		अगर (!is_vcpu_stopped(v))
			all_stopped = false;
	पूर्ण

	*status_reg &= 0xffffffff00000000UL;

	/* Reject set arch order, with czam we're always in z/Arch mode. */
	*status_reg |= (all_stopped ? SIGP_STATUS_INVALID_PARAMETER :
					SIGP_STATUS_INCORRECT_STATE);
	वापस SIGP_CC_STATUS_STORED;
पूर्ण

अटल पूर्णांक __sigp_set_prefix(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_vcpu *dst_vcpu,
			     u32 address, u64 *reg)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_SIGP_SET_PREFIX,
		.u.prefix.address = address & 0x7fffe000u,
	पूर्ण;
	पूर्णांक rc;

	/*
	 * Make sure the new value is valid memory. We only need to check the
	 * first page, since address is 8k aligned and memory pieces are always
	 * at least 1MB aligned and have at least a size of 1MB.
	 */
	अगर (kvm_is_error_gpa(vcpu->kvm, irq.u.prefix.address)) अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INVALID_PARAMETER;
		वापस SIGP_CC_STATUS_STORED;
	पूर्ण

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	अगर (rc == -EBUSY) अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INCORRECT_STATE;
		वापस SIGP_CC_STATUS_STORED;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक __sigp_store_status_at_addr(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा kvm_vcpu *dst_vcpu,
				       u32 addr, u64 *reg)
अणु
	पूर्णांक rc;

	अगर (!kvm_s390_test_cpuflags(dst_vcpu, CPUSTAT_STOPPED)) अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INCORRECT_STATE;
		वापस SIGP_CC_STATUS_STORED;
	पूर्ण

	addr &= 0x7ffffe00;
	rc = kvm_s390_store_status_unloaded(dst_vcpu, addr);
	अगर (rc == -EFAULT) अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INVALID_PARAMETER;
		rc = SIGP_CC_STATUS_STORED;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक __sigp_sense_running(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_vcpu *dst_vcpu, u64 *reg)
अणु
	पूर्णांक rc;

	अगर (!test_kvm_facility(vcpu->kvm, 9)) अणु
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INVALID_ORDER;
		वापस SIGP_CC_STATUS_STORED;
	पूर्ण

	अगर (kvm_s390_test_cpuflags(dst_vcpu, CPUSTAT_RUNNING)) अणु
		/* running */
		rc = SIGP_CC_ORDER_CODE_ACCEPTED;
	पूर्ण अन्यथा अणु
		/* not running */
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_NOT_RUNNING;
		rc = SIGP_CC_STATUS_STORED;
	पूर्ण

	VCPU_EVENT(vcpu, 4, "sensed running status of cpu %x rc %x",
		   dst_vcpu->vcpu_id, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक __prepare_sigp_re_start(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_vcpu *dst_vcpu, u8 order_code)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &dst_vcpu->arch.local_पूर्णांक;
	/* handle (RE)START in user space */
	पूर्णांक rc = -EOPNOTSUPP;

	/* make sure we करोn't race with STOP irq injection */
	spin_lock(&li->lock);
	अगर (kvm_s390_is_stop_irq_pending(dst_vcpu))
		rc = SIGP_CC_BUSY;
	spin_unlock(&li->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक __prepare_sigp_cpu_reset(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_vcpu *dst_vcpu, u8 order_code)
अणु
	/* handle (INITIAL) CPU RESET in user space */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक __prepare_sigp_unknown(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_vcpu *dst_vcpu)
अणु
	/* handle unknown orders in user space */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक handle_sigp_dst(काष्ठा kvm_vcpu *vcpu, u8 order_code,
			   u16 cpu_addr, u32 parameter, u64 *status_reg)
अणु
	पूर्णांक rc;
	काष्ठा kvm_vcpu *dst_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, cpu_addr);

	अगर (!dst_vcpu)
		वापस SIGP_CC_NOT_OPERATIONAL;

	चयन (order_code) अणु
	हाल SIGP_SENSE:
		vcpu->stat.inकाष्ठाion_sigp_sense++;
		rc = __sigp_sense(vcpu, dst_vcpu, status_reg);
		अवरोध;
	हाल SIGP_EXTERNAL_CALL:
		vcpu->stat.inकाष्ठाion_sigp_बाह्यal_call++;
		rc = __sigp_बाह्यal_call(vcpu, dst_vcpu, status_reg);
		अवरोध;
	हाल SIGP_EMERGENCY_SIGNAL:
		vcpu->stat.inकाष्ठाion_sigp_emergency++;
		rc = __sigp_emergency(vcpu, dst_vcpu);
		अवरोध;
	हाल SIGP_STOP:
		vcpu->stat.inकाष्ठाion_sigp_stop++;
		rc = __sigp_stop(vcpu, dst_vcpu);
		अवरोध;
	हाल SIGP_STOP_AND_STORE_STATUS:
		vcpu->stat.inकाष्ठाion_sigp_stop_store_status++;
		rc = __sigp_stop_and_store_status(vcpu, dst_vcpu, status_reg);
		अवरोध;
	हाल SIGP_STORE_STATUS_AT_ADDRESS:
		vcpu->stat.inकाष्ठाion_sigp_store_status++;
		rc = __sigp_store_status_at_addr(vcpu, dst_vcpu, parameter,
						 status_reg);
		अवरोध;
	हाल SIGP_SET_PREFIX:
		vcpu->stat.inकाष्ठाion_sigp_prefix++;
		rc = __sigp_set_prefix(vcpu, dst_vcpu, parameter, status_reg);
		अवरोध;
	हाल SIGP_COND_EMERGENCY_SIGNAL:
		vcpu->stat.inकाष्ठाion_sigp_cond_emergency++;
		rc = __sigp_conditional_emergency(vcpu, dst_vcpu, parameter,
						  status_reg);
		अवरोध;
	हाल SIGP_SENSE_RUNNING:
		vcpu->stat.inकाष्ठाion_sigp_sense_running++;
		rc = __sigp_sense_running(vcpu, dst_vcpu, status_reg);
		अवरोध;
	हाल SIGP_START:
		vcpu->stat.inकाष्ठाion_sigp_start++;
		rc = __prepare_sigp_re_start(vcpu, dst_vcpu, order_code);
		अवरोध;
	हाल SIGP_RESTART:
		vcpu->stat.inकाष्ठाion_sigp_restart++;
		rc = __prepare_sigp_re_start(vcpu, dst_vcpu, order_code);
		अवरोध;
	हाल SIGP_INITIAL_CPU_RESET:
		vcpu->stat.inकाष्ठाion_sigp_init_cpu_reset++;
		rc = __prepare_sigp_cpu_reset(vcpu, dst_vcpu, order_code);
		अवरोध;
	हाल SIGP_CPU_RESET:
		vcpu->stat.inकाष्ठाion_sigp_cpu_reset++;
		rc = __prepare_sigp_cpu_reset(vcpu, dst_vcpu, order_code);
		अवरोध;
	शेष:
		vcpu->stat.inकाष्ठाion_sigp_unknown++;
		rc = __prepare_sigp_unknown(vcpu, dst_vcpu);
	पूर्ण

	अगर (rc == -EOPNOTSUPP)
		VCPU_EVENT(vcpu, 4,
			   "sigp order %u -> cpu %x: handled in user space",
			   order_code, dst_vcpu->vcpu_id);

	वापस rc;
पूर्ण

अटल पूर्णांक handle_sigp_order_in_user_space(काष्ठा kvm_vcpu *vcpu, u8 order_code,
					   u16 cpu_addr)
अणु
	अगर (!vcpu->kvm->arch.user_sigp)
		वापस 0;

	चयन (order_code) अणु
	हाल SIGP_SENSE:
	हाल SIGP_EXTERNAL_CALL:
	हाल SIGP_EMERGENCY_SIGNAL:
	हाल SIGP_COND_EMERGENCY_SIGNAL:
	हाल SIGP_SENSE_RUNNING:
		वापस 0;
	/* update counters as we're directly dropping to user space */
	हाल SIGP_STOP:
		vcpu->stat.inकाष्ठाion_sigp_stop++;
		अवरोध;
	हाल SIGP_STOP_AND_STORE_STATUS:
		vcpu->stat.inकाष्ठाion_sigp_stop_store_status++;
		अवरोध;
	हाल SIGP_STORE_STATUS_AT_ADDRESS:
		vcpu->stat.inकाष्ठाion_sigp_store_status++;
		अवरोध;
	हाल SIGP_STORE_ADDITIONAL_STATUS:
		vcpu->stat.inकाष्ठाion_sigp_store_adtl_status++;
		अवरोध;
	हाल SIGP_SET_PREFIX:
		vcpu->stat.inकाष्ठाion_sigp_prefix++;
		अवरोध;
	हाल SIGP_START:
		vcpu->stat.inकाष्ठाion_sigp_start++;
		अवरोध;
	हाल SIGP_RESTART:
		vcpu->stat.inकाष्ठाion_sigp_restart++;
		अवरोध;
	हाल SIGP_INITIAL_CPU_RESET:
		vcpu->stat.inकाष्ठाion_sigp_init_cpu_reset++;
		अवरोध;
	हाल SIGP_CPU_RESET:
		vcpu->stat.inकाष्ठाion_sigp_cpu_reset++;
		अवरोध;
	शेष:
		vcpu->stat.inकाष्ठाion_sigp_unknown++;
	पूर्ण
	VCPU_EVENT(vcpu, 3, "SIGP: order %u for CPU %d handled in userspace",
		   order_code, cpu_addr);

	वापस 1;
पूर्ण

पूर्णांक kvm_s390_handle_sigp(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r1 = (vcpu->arch.sie_block->ipa & 0x00f0) >> 4;
	पूर्णांक r3 = vcpu->arch.sie_block->ipa & 0x000f;
	u32 parameter;
	u16 cpu_addr = vcpu->run->s.regs.gprs[r3];
	u8 order_code;
	पूर्णांक rc;

	/* sigp in userspace can निकास */
	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	order_code = kvm_s390_get_base_disp_rs(vcpu, शून्य);
	अगर (handle_sigp_order_in_user_space(vcpu, order_code, cpu_addr))
		वापस -EOPNOTSUPP;

	अगर (r1 % 2)
		parameter = vcpu->run->s.regs.gprs[r1];
	अन्यथा
		parameter = vcpu->run->s.regs.gprs[r1 + 1];

	trace_kvm_s390_handle_sigp(vcpu, order_code, cpu_addr, parameter);
	चयन (order_code) अणु
	हाल SIGP_SET_ARCHITECTURE:
		vcpu->stat.inकाष्ठाion_sigp_arch++;
		rc = __sigp_set_arch(vcpu, parameter,
				     &vcpu->run->s.regs.gprs[r1]);
		अवरोध;
	शेष:
		rc = handle_sigp_dst(vcpu, order_code, cpu_addr,
				     parameter,
				     &vcpu->run->s.regs.gprs[r1]);
	पूर्ण

	अगर (rc < 0)
		वापस rc;

	kvm_s390_set_psw_cc(vcpu, rc);
	वापस 0;
पूर्ण

/*
 * Handle SIGP partial execution पूर्णांकerception.
 *
 * This पूर्णांकerception will occur at the source cpu when a source cpu sends an
 * बाह्यal call to a target cpu and the target cpu has the WAIT bit set in
 * its cpuflags. Interception will occurr after the पूर्णांकerrupt indicator bits at
 * the target cpu have been set. All error हालs will lead to inकाष्ठाion
 * पूर्णांकerception, thereक्रमe nothing is to be checked or prepared.
 */
पूर्णांक kvm_s390_handle_sigp_pei(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r3 = vcpu->arch.sie_block->ipa & 0x000f;
	u16 cpu_addr = vcpu->run->s.regs.gprs[r3];
	काष्ठा kvm_vcpu *dest_vcpu;
	u8 order_code = kvm_s390_get_base_disp_rs(vcpu, शून्य);

	trace_kvm_s390_handle_sigp_pei(vcpu, order_code, cpu_addr);

	अगर (order_code == SIGP_EXTERNAL_CALL) अणु
		dest_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, cpu_addr);
		BUG_ON(dest_vcpu == शून्य);

		kvm_s390_vcpu_wakeup(dest_vcpu);
		kvm_s390_set_psw_cc(vcpu, SIGP_CC_ORDER_CODE_ACCEPTED);
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण
