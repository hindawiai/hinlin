<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * handling diagnose inकाष्ठाions
 *
 * Copyright IBM Corp. 2008, 2020
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 */

#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/virtio-ccw.h>
#समावेश "kvm-s390.h"
#समावेश "trace.h"
#समावेश "trace-s390.h"
#समावेश "gaccess.h"

अटल पूर्णांक diag_release_pages(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ prefix  = kvm_s390_get_prefix(vcpu);

	start = vcpu->run->s.regs.gprs[(vcpu->arch.sie_block->ipa & 0xf0) >> 4];
	end = vcpu->run->s.regs.gprs[vcpu->arch.sie_block->ipa & 0xf] + PAGE_SIZE;
	vcpu->stat.diagnose_10++;

	अगर (start & ~PAGE_MASK || end & ~PAGE_MASK || start >= end
	    || start < 2 * PAGE_SIZE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 5, "diag release pages %lX %lX", start, end);

	/*
	 * We checked क्रम start >= end above, so lets check क्रम the
	 * fast path (no prefix swap page involved)
	 */
	अगर (end <= prefix || start >= prefix + 2 * PAGE_SIZE) अणु
		gmap_discard(vcpu->arch.gmap, start, end);
	पूर्ण अन्यथा अणु
		/*
		 * This is slow path.  gmap_discard will check क्रम start
		 * so lets split this पूर्णांकo beक्रमe prefix, prefix, after
		 * prefix and let gmap_discard make some of these calls
		 * NOPs.
		 */
		gmap_discard(vcpu->arch.gmap, start, prefix);
		अगर (start <= prefix)
			gmap_discard(vcpu->arch.gmap, 0, PAGE_SIZE);
		अगर (end > prefix + PAGE_SIZE)
			gmap_discard(vcpu->arch.gmap, PAGE_SIZE, 2 * PAGE_SIZE);
		gmap_discard(vcpu->arch.gmap, prefix + 2 * PAGE_SIZE, end);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __diag_page_ref_service(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा prs_parm अणु
		u16 code;
		u16 subcode;
		u16 parm_len;
		u16 parm_version;
		u64 token_addr;
		u64 select_mask;
		u64 compare_mask;
		u64 zarch;
	पूर्ण;
	काष्ठा prs_parm parm;
	पूर्णांक rc;
	u16 rx = (vcpu->arch.sie_block->ipa & 0xf0) >> 4;
	u16 ry = (vcpu->arch.sie_block->ipa & 0x0f);

	VCPU_EVENT(vcpu, 3, "diag page reference parameter block at 0x%llx",
		   vcpu->run->s.regs.gprs[rx]);
	vcpu->stat.diagnose_258++;
	अगर (vcpu->run->s.regs.gprs[rx] & 7)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	rc = पढ़ो_guest(vcpu, vcpu->run->s.regs.gprs[rx], rx, &parm, माप(parm));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	अगर (parm.parm_version != 2 || parm.parm_len < 5 || parm.code != 0x258)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	चयन (parm.subcode) अणु
	हाल 0: /* TOKEN */
		VCPU_EVENT(vcpu, 3, "pageref token addr 0x%llx "
			   "select mask 0x%llx compare mask 0x%llx",
			   parm.token_addr, parm.select_mask, parm.compare_mask);
		अगर (vcpu->arch.pfault_token != KVM_S390_PFAULT_TOKEN_INVALID) अणु
			/*
			 * If the pagefault handshake is alपढ़ोy activated,
			 * the token must not be changed.  We have to वापस
			 * decimal 8 instead, as mandated in SC24-6084.
			 */
			vcpu->run->s.regs.gprs[ry] = 8;
			वापस 0;
		पूर्ण

		अगर ((parm.compare_mask & parm.select_mask) != parm.compare_mask ||
		    parm.token_addr & 7 || parm.zarch != 0x8000000000000000ULL)
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

		अगर (kvm_is_error_gpa(vcpu->kvm, parm.token_addr))
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);

		vcpu->arch.pfault_token = parm.token_addr;
		vcpu->arch.pfault_select = parm.select_mask;
		vcpu->arch.pfault_compare = parm.compare_mask;
		vcpu->run->s.regs.gprs[ry] = 0;
		rc = 0;
		अवरोध;
	हाल 1: /*
		 * CANCEL
		 * Specअगरication allows to let alपढ़ोy pending tokens survive
		 * the cancel, thereक्रमe to reduce code complनिकासy, we assume
		 * all outstanding tokens are alपढ़ोy pending.
		 */
		VCPU_EVENT(vcpu, 3, "pageref cancel addr 0x%llx", parm.token_addr);
		अगर (parm.token_addr || parm.select_mask ||
		    parm.compare_mask || parm.zarch)
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

		vcpu->run->s.regs.gprs[ry] = 0;
		/*
		 * If the pfault handling was not established or is alपढ़ोy
		 * canceled SC24-6084 requests to वापस decimal 4.
		 */
		अगर (vcpu->arch.pfault_token == KVM_S390_PFAULT_TOKEN_INVALID)
			vcpu->run->s.regs.gprs[ry] = 4;
		अन्यथा
			vcpu->arch.pfault_token = KVM_S390_PFAULT_TOKEN_INVALID;

		rc = 0;
		अवरोध;
	शेष:
		rc = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक __diag_समय_slice_end(काष्ठा kvm_vcpu *vcpu)
अणु
	VCPU_EVENT(vcpu, 5, "%s", "diag time slice end");
	vcpu->stat.diagnose_44++;
	kvm_vcpu_on_spin(vcpu, true);
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमward_cnt;
अटल अचिन्हित दीर्घ cur_slice;

अटल पूर्णांक diag9c_क्रमwarding_overrun(व्योम)
अणु
	/* Reset the count on a new slice */
	अगर (समय_after(jअगरfies, cur_slice)) अणु
		cur_slice = jअगरfies;
		क्रमward_cnt = diag9c_क्रमwarding_hz / HZ;
	पूर्ण
	वापस क्रमward_cnt-- <= 0 ? 1 : 0;
पूर्ण

अटल पूर्णांक __diag_समय_slice_end_directed(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu *tcpu;
	पूर्णांक tid;

	tid = vcpu->run->s.regs.gprs[(vcpu->arch.sie_block->ipa & 0xf0) >> 4];
	vcpu->stat.diagnose_9c++;

	/* yield to self */
	अगर (tid == vcpu->vcpu_id)
		जाओ no_yield;

	/* yield to invalid */
	tcpu = kvm_get_vcpu_by_id(vcpu->kvm, tid);
	अगर (!tcpu)
		जाओ no_yield;

	/* target guest VCPU alपढ़ोy running */
	अगर (READ_ONCE(tcpu->cpu) >= 0) अणु
		अगर (!diag9c_क्रमwarding_hz || diag9c_क्रमwarding_overrun())
			जाओ no_yield;

		/* target host CPU alपढ़ोy running */
		अगर (!vcpu_is_preempted(tcpu->cpu))
			जाओ no_yield;
		smp_yield_cpu(tcpu->cpu);
		VCPU_EVENT(vcpu, 5,
			   "diag time slice end directed to %d: yield forwarded",
			   tid);
		vcpu->stat.diagnose_9c_क्रमward++;
		वापस 0;
	पूर्ण

	अगर (kvm_vcpu_yield_to(tcpu) <= 0)
		जाओ no_yield;

	VCPU_EVENT(vcpu, 5, "diag time slice end directed to %d: done", tid);
	वापस 0;
no_yield:
	VCPU_EVENT(vcpu, 5, "diag time slice end directed to %d: ignored", tid);
	vcpu->stat.diagnose_9c_ignored++;
	वापस 0;
पूर्ण

अटल पूर्णांक __diag_ipl_functions(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक reg = vcpu->arch.sie_block->ipa & 0xf;
	अचिन्हित दीर्घ subcode = vcpu->run->s.regs.gprs[reg] & 0xffff;

	VCPU_EVENT(vcpu, 3, "diag ipl functions, subcode %lx", subcode);
	vcpu->stat.diagnose_308++;
	चयन (subcode) अणु
	हाल 3:
		vcpu->run->s390_reset_flags = KVM_S390_RESET_CLEAR;
		अवरोध;
	हाल 4:
		vcpu->run->s390_reset_flags = 0;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * no need to check the वापस value of vcpu_stop as it can only have
	 * an error क्रम protvirt, but protvirt means user cpu state
	 */
	अगर (!kvm_s390_user_cpu_state_ctrl(vcpu->kvm))
		kvm_s390_vcpu_stop(vcpu);
	vcpu->run->s390_reset_flags |= KVM_S390_RESET_SUBSYSTEM;
	vcpu->run->s390_reset_flags |= KVM_S390_RESET_IPL;
	vcpu->run->s390_reset_flags |= KVM_S390_RESET_CPU_INIT;
	vcpu->run->निकास_reason = KVM_EXIT_S390_RESET;
	VCPU_EVENT(vcpu, 3, "requesting userspace resets %llx",
	  vcpu->run->s390_reset_flags);
	trace_kvm_s390_request_resets(vcpu->run->s390_reset_flags);
	वापस -EREMOTE;
पूर्ण

अटल पूर्णांक __diag_virtio_hypercall(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	vcpu->stat.diagnose_500++;
	/* No virtio-ccw notअगरication? Get out quickly. */
	अगर (!vcpu->kvm->arch.css_support ||
	    (vcpu->run->s.regs.gprs[1] != KVM_S390_VIRTIO_CCW_NOTIFY))
		वापस -EOPNOTSUPP;

	VCPU_EVENT(vcpu, 4, "diag 0x500 schid 0x%8.8x queue 0x%x cookie 0x%llx",
			    (u32) vcpu->run->s.regs.gprs[2],
			    (u32) vcpu->run->s.regs.gprs[3],
			    vcpu->run->s.regs.gprs[4]);

	/*
	 * The layout is as follows:
	 * - gpr 2 contains the subchannel id (passed as addr)
	 * - gpr 3 contains the virtqueue index (passed as datamatch)
	 * - gpr 4 contains the index on the bus (optionally)
	 */
	ret = kvm_io_bus_ग_लिखो_cookie(vcpu, KVM_VIRTIO_CCW_NOTIFY_BUS,
				      vcpu->run->s.regs.gprs[2] & 0xffffffff,
				      8, &vcpu->run->s.regs.gprs[3],
				      vcpu->run->s.regs.gprs[4]);

	/*
	 * Return cookie in gpr 2, but करोn't overग_लिखो the रेजिस्टर अगर the
	 * diagnose will be handled by userspace.
	 */
	अगर (ret != -EOPNOTSUPP)
		vcpu->run->s.regs.gprs[2] = ret;
	/* kvm_io_bus_ग_लिखो_cookie वापसs -EOPNOTSUPP अगर it found no match. */
	वापस ret < 0 ? ret : 0;
पूर्ण

पूर्णांक kvm_s390_handle_diag(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक code = kvm_s390_get_base_disp_rs(vcpu, शून्य) & 0xffff;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	trace_kvm_s390_handle_diag(vcpu, code);
	चयन (code) अणु
	हाल 0x10:
		वापस diag_release_pages(vcpu);
	हाल 0x44:
		वापस __diag_समय_slice_end(vcpu);
	हाल 0x9c:
		वापस __diag_समय_slice_end_directed(vcpu);
	हाल 0x258:
		वापस __diag_page_ref_service(vcpu);
	हाल 0x308:
		वापस __diag_ipl_functions(vcpu);
	हाल 0x500:
		वापस __diag_virtio_hypercall(vcpu);
	शेष:
		vcpu->stat.diagnose_other++;
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
