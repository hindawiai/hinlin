<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * in-kernel handling क्रम sie पूर्णांकercepts
 *
 * Copyright IBM Corp. 2008, 2020
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/uv.h>

#समावेश "kvm-s390.h"
#समावेश "gaccess.h"
#समावेश "trace.h"
#समावेश "trace-s390.h"

u8 kvm_s390_get_ilen(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_sie_block *sie_block = vcpu->arch.sie_block;
	u8 ilen = 0;

	चयन (vcpu->arch.sie_block->icptcode) अणु
	हाल ICPT_INST:
	हाल ICPT_INSTPROGI:
	हाल ICPT_OPEREXC:
	हाल ICPT_PARTEXEC:
	हाल ICPT_IOINST:
		/* inकाष्ठाion only stored क्रम these icptcodes */
		ilen = insn_length(vcpu->arch.sie_block->ipa >> 8);
		/* Use the length of the EXECUTE inकाष्ठाion अगर necessary */
		अगर (sie_block->icptstatus & 1) अणु
			ilen = (sie_block->icptstatus >> 4) & 0x6;
			अगर (!ilen)
				ilen = 4;
		पूर्ण
		अवरोध;
	हाल ICPT_PROGI:
		/* bit 1+2 of pgmilc are the ilc, so we directly get ilen */
		ilen = vcpu->arch.sie_block->pgmilc & 0x6;
		अवरोध;
	पूर्ण
	वापस ilen;
पूर्ण

अटल पूर्णांक handle_stop(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_local_पूर्णांकerrupt *li = &vcpu->arch.local_पूर्णांक;
	पूर्णांक rc = 0;
	uपूर्णांक8_t flags, stop_pending;

	vcpu->stat.निकास_stop_request++;

	/* delay the stop अगर any non-stop irq is pending */
	अगर (kvm_s390_vcpu_has_irq(vcpu, 1))
		वापस 0;

	/* aव्योम races with the injection/SIGP STOP code */
	spin_lock(&li->lock);
	flags = li->irq.stop.flags;
	stop_pending = kvm_s390_is_stop_irq_pending(vcpu);
	spin_unlock(&li->lock);

	trace_kvm_s390_stop_request(stop_pending, flags);
	अगर (!stop_pending)
		वापस 0;

	अगर (flags & KVM_S390_STOP_FLAG_STORE_STATUS) अणु
		rc = kvm_s390_vcpu_store_status(vcpu,
						KVM_S390_STORE_STATUS_NOADDR);
		अगर (rc)
			वापस rc;
	पूर्ण

	/*
	 * no need to check the वापस value of vcpu_stop as it can only have
	 * an error क्रम protvirt, but protvirt means user cpu state
	 */
	अगर (!kvm_s390_user_cpu_state_ctrl(vcpu->kvm))
		kvm_s390_vcpu_stop(vcpu);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक handle_validity(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक viwhy = vcpu->arch.sie_block->ipb >> 16;

	vcpu->stat.निकास_validity++;
	trace_kvm_s390_पूर्णांकercept_validity(vcpu, viwhy);
	KVM_EVENT(3, "validity intercept 0x%x for pid %u (kvm 0x%pK)", viwhy,
		  current->pid, vcpu->kvm);

	/* करो not warn on invalid runसमय instrumentation mode */
	WARN_ONCE(viwhy != 0x44, "kvm: unhandled validity intercept 0x%x\n",
		  viwhy);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक handle_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->stat.निकास_inकाष्ठाion++;
	trace_kvm_s390_पूर्णांकercept_inकाष्ठाion(vcpu,
					     vcpu->arch.sie_block->ipa,
					     vcpu->arch.sie_block->ipb);

	चयन (vcpu->arch.sie_block->ipa >> 8) अणु
	हाल 0x01:
		वापस kvm_s390_handle_01(vcpu);
	हाल 0x82:
		वापस kvm_s390_handle_lpsw(vcpu);
	हाल 0x83:
		वापस kvm_s390_handle_diag(vcpu);
	हाल 0xaa:
		वापस kvm_s390_handle_aa(vcpu);
	हाल 0xae:
		वापस kvm_s390_handle_sigp(vcpu);
	हाल 0xb2:
		वापस kvm_s390_handle_b2(vcpu);
	हाल 0xb6:
		वापस kvm_s390_handle_stctl(vcpu);
	हाल 0xb7:
		वापस kvm_s390_handle_lctl(vcpu);
	हाल 0xb9:
		वापस kvm_s390_handle_b9(vcpu);
	हाल 0xe3:
		वापस kvm_s390_handle_e3(vcpu);
	हाल 0xe5:
		वापस kvm_s390_handle_e5(vcpu);
	हाल 0xeb:
		वापस kvm_s390_handle_eb(vcpu);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक inject_prog_on_prog_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_pgm_info pgm_info = अणु
		.code = vcpu->arch.sie_block->iprcc,
		/* the PSW has alपढ़ोy been rewound */
		.flags = KVM_S390_PGM_FLAGS_NO_REWIND,
	पूर्ण;

	चयन (vcpu->arch.sie_block->iprcc & ~PGM_PER) अणु
	हाल PGM_AFX_TRANSLATION:
	हाल PGM_ASX_TRANSLATION:
	हाल PGM_EX_TRANSLATION:
	हाल PGM_LFX_TRANSLATION:
	हाल PGM_LSTE_SEQUENCE:
	हाल PGM_LSX_TRANSLATION:
	हाल PGM_LX_TRANSLATION:
	हाल PGM_PRIMARY_AUTHORITY:
	हाल PGM_SECONDARY_AUTHORITY:
	हाल PGM_SPACE_SWITCH:
		pgm_info.trans_exc_code = vcpu->arch.sie_block->tecmc;
		अवरोध;
	हाल PGM_ALEN_TRANSLATION:
	हाल PGM_ALE_SEQUENCE:
	हाल PGM_ASTE_INSTANCE:
	हाल PGM_ASTE_SEQUENCE:
	हाल PGM_ASTE_VALIDITY:
	हाल PGM_EXTENDED_AUTHORITY:
		pgm_info.exc_access_id = vcpu->arch.sie_block->eai;
		अवरोध;
	हाल PGM_ASCE_TYPE:
	हाल PGM_PAGE_TRANSLATION:
	हाल PGM_REGION_FIRST_TRANS:
	हाल PGM_REGION_SECOND_TRANS:
	हाल PGM_REGION_THIRD_TRANS:
	हाल PGM_SEGMENT_TRANSLATION:
		pgm_info.trans_exc_code = vcpu->arch.sie_block->tecmc;
		pgm_info.exc_access_id  = vcpu->arch.sie_block->eai;
		pgm_info.op_access_id  = vcpu->arch.sie_block->oai;
		अवरोध;
	हाल PGM_MONITOR:
		pgm_info.mon_class_nr = vcpu->arch.sie_block->mcn;
		pgm_info.mon_code = vcpu->arch.sie_block->tecmc;
		अवरोध;
	हाल PGM_VECTOR_PROCESSING:
	हाल PGM_DATA:
		pgm_info.data_exc_code = vcpu->arch.sie_block->dxc;
		अवरोध;
	हाल PGM_PROTECTION:
		pgm_info.trans_exc_code = vcpu->arch.sie_block->tecmc;
		pgm_info.exc_access_id  = vcpu->arch.sie_block->eai;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (vcpu->arch.sie_block->iprcc & PGM_PER) अणु
		pgm_info.per_code = vcpu->arch.sie_block->perc;
		pgm_info.per_aपंचांगid = vcpu->arch.sie_block->peraपंचांगid;
		pgm_info.per_address = vcpu->arch.sie_block->peraddr;
		pgm_info.per_access_id = vcpu->arch.sie_block->peraid;
	पूर्ण
	वापस kvm_s390_inject_prog_irq(vcpu, &pgm_info);
पूर्ण

/*
 * restore ITDB to program-पूर्णांकerruption TDB in guest lowcore
 * and set TX पात indication अगर required
*/
अटल पूर्णांक handle_itdb(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_itdb *itdb;
	पूर्णांक rc;

	अगर (!IS_TE_ENABLED(vcpu) || !IS_ITDB_VALID(vcpu))
		वापस 0;
	अगर (current->thपढ़ो.per_flags & PER_FLAG_NO_TE)
		वापस 0;
	itdb = (काष्ठा kvm_s390_itdb *)vcpu->arch.sie_block->itdba;
	rc = ग_लिखो_guest_lc(vcpu, __LC_PGM_TDB, itdb, माप(*itdb));
	अगर (rc)
		वापस rc;
	स_रखो(itdb, 0, माप(*itdb));

	वापस 0;
पूर्ण

#घोषणा per_event(vcpu) (vcpu->arch.sie_block->iprcc & PGM_PER)

अटल पूर्णांक handle_prog(काष्ठा kvm_vcpu *vcpu)
अणु
	psw_t psw;
	पूर्णांक rc;

	vcpu->stat.निकास_program_पूर्णांकerruption++;

	/*
	 * Intercept 8 indicates a loop of specअगरication exceptions
	 * क्रम रक्षित guests.
	 */
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu))
		वापस -EOPNOTSUPP;

	अगर (guestdbg_enabled(vcpu) && per_event(vcpu)) अणु
		rc = kvm_s390_handle_per_event(vcpu);
		अगर (rc)
			वापस rc;
		/* the पूर्णांकerrupt might have been filtered out completely */
		अगर (vcpu->arch.sie_block->iprcc == 0)
			वापस 0;
	पूर्ण

	trace_kvm_s390_पूर्णांकercept_prog(vcpu, vcpu->arch.sie_block->iprcc);
	अगर (vcpu->arch.sie_block->iprcc == PGM_SPECIFICATION) अणु
		rc = पढ़ो_guest_lc(vcpu, __LC_PGM_NEW_PSW, &psw, माप(psw_t));
		अगर (rc)
			वापस rc;
		/* Aव्योम endless loops of specअगरication exceptions */
		अगर (!is_valid_psw(&psw))
			वापस -EOPNOTSUPP;
	पूर्ण
	rc = handle_itdb(vcpu);
	अगर (rc)
		वापस rc;

	वापस inject_prog_on_prog_पूर्णांकercept(vcpu);
पूर्ण

/**
 * handle_बाह्यal_पूर्णांकerrupt - used क्रम बाह्यal पूर्णांकerruption पूर्णांकerceptions
 *
 * This पूर्णांकerception only occurs अगर the CPUSTAT_EXT_INT bit was set, or अगर
 * the new PSW करोes not have बाह्यal पूर्णांकerrupts disabled. In the first हाल,
 * we've got to deliver the पूर्णांकerrupt manually, and in the second हाल, we
 * drop to userspace to handle the situation there.
 */
अटल पूर्णांक handle_बाह्यal_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	u16 eic = vcpu->arch.sie_block->eic;
	काष्ठा kvm_s390_irq irq;
	psw_t newpsw;
	पूर्णांक rc;

	vcpu->stat.निकास_बाह्यal_पूर्णांकerrupt++;

	rc = पढ़ो_guest_lc(vcpu, __LC_EXT_NEW_PSW, &newpsw, माप(psw_t));
	अगर (rc)
		वापस rc;
	/* We can not handle घड़ी comparator or समयr पूर्णांकerrupt with bad PSW */
	अगर ((eic == EXT_IRQ_CLK_COMP || eic == EXT_IRQ_CPU_TIMER) &&
	    (newpsw.mask & PSW_MASK_EXT))
		वापस -EOPNOTSUPP;

	चयन (eic) अणु
	हाल EXT_IRQ_CLK_COMP:
		irq.type = KVM_S390_INT_CLOCK_COMP;
		अवरोध;
	हाल EXT_IRQ_CPU_TIMER:
		irq.type = KVM_S390_INT_CPU_TIMER;
		अवरोध;
	हाल EXT_IRQ_EXTERNAL_CALL:
		irq.type = KVM_S390_INT_EXTERNAL_CALL;
		irq.u.extcall.code = vcpu->arch.sie_block->extcpuaddr;
		rc = kvm_s390_inject_vcpu(vcpu, &irq);
		/* ignore अगर another बाह्यal call is alपढ़ोy pending */
		अगर (rc == -EBUSY)
			वापस 0;
		वापस rc;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस kvm_s390_inject_vcpu(vcpu, &irq);
पूर्ण

/**
 * Handle MOVE PAGE partial execution पूर्णांकerception.
 *
 * This पूर्णांकerception can only happen क्रम guests with DAT disabled and
 * addresses that are currently not mapped in the host. Thus we try to
 * set up the mappings क्रम the corresponding user pages here (or throw
 * addressing exceptions in हाल of illegal guest addresses).
 */
अटल पूर्णांक handle_mvpg_pei(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ srcaddr, dstaddr;
	पूर्णांक reg1, reg2, rc;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	/* Make sure that the source is paged-in */
	rc = guest_translate_address(vcpu, vcpu->run->s.regs.gprs[reg2],
				     reg2, &srcaddr, GACC_FETCH);
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	rc = kvm_arch_fault_in_page(vcpu, srcaddr, 0);
	अगर (rc != 0)
		वापस rc;

	/* Make sure that the destination is paged-in */
	rc = guest_translate_address(vcpu, vcpu->run->s.regs.gprs[reg1],
				     reg1, &dstaddr, GACC_STORE);
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	rc = kvm_arch_fault_in_page(vcpu, dstaddr, 1);
	अगर (rc != 0)
		वापस rc;

	kvm_s390_retry_instr(vcpu);

	वापस 0;
पूर्ण

अटल पूर्णांक handle_partial_execution(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->stat.निकास_pei++;

	अगर (vcpu->arch.sie_block->ipa == 0xb254)	/* MVPG */
		वापस handle_mvpg_pei(vcpu);
	अगर (vcpu->arch.sie_block->ipa >> 8 == 0xae)	/* SIGP */
		वापस kvm_s390_handle_sigp_pei(vcpu);

	वापस -EOPNOTSUPP;
पूर्ण

/*
 * Handle the sthyi inकाष्ठाion that provides the guest with प्रणाली
 * inक्रमmation, like current CPU resources available at each level of
 * the machine.
 */
पूर्णांक handle_sthyi(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक reg1, reg2, r = 0;
	u64 code, addr, cc = 0, rc = 0;
	काष्ठा sthyi_sctns *sctns = शून्य;

	अगर (!test_kvm_facility(vcpu->kvm, 74))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_OPERATION);

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);
	code = vcpu->run->s.regs.gprs[reg1];
	addr = vcpu->run->s.regs.gprs[reg2];

	vcpu->stat.inकाष्ठाion_sthyi++;
	VCPU_EVENT(vcpu, 3, "STHYI: fc: %llu addr: 0x%016llx", code, addr);
	trace_kvm_s390_handle_sthyi(vcpu, code, addr);

	अगर (reg1 == reg2 || reg1 & 1 || reg2 & 1)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	अगर (code & 0xffff) अणु
		cc = 3;
		rc = 4;
		जाओ out;
	पूर्ण

	अगर (!kvm_s390_pv_cpu_is_रक्षित(vcpu) && (addr & ~PAGE_MASK))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	sctns = (व्योम *)get_zeroed_page(GFP_KERNEL_ACCOUNT);
	अगर (!sctns)
		वापस -ENOMEM;

	cc = sthyi_fill(sctns, &rc);

out:
	अगर (!cc) अणु
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			स_नकल((व्योम *)(sida_origin(vcpu->arch.sie_block)),
			       sctns, PAGE_SIZE);
		पूर्ण अन्यथा अणु
			r = ग_लिखो_guest(vcpu, addr, reg2, sctns, PAGE_SIZE);
			अगर (r) अणु
				मुक्त_page((अचिन्हित दीर्घ)sctns);
				वापस kvm_s390_inject_prog_cond(vcpu, r);
			पूर्ण
		पूर्ण
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)sctns);
	vcpu->run->s.regs.gprs[reg2 + 1] = rc;
	kvm_s390_set_psw_cc(vcpu, cc);
	वापस r;
पूर्ण

अटल पूर्णांक handle_operexc(काष्ठा kvm_vcpu *vcpu)
अणु
	psw_t oldpsw, newpsw;
	पूर्णांक rc;

	vcpu->stat.निकास_operation_exception++;
	trace_kvm_s390_handle_operexc(vcpu, vcpu->arch.sie_block->ipa,
				      vcpu->arch.sie_block->ipb);

	अगर (vcpu->arch.sie_block->ipa == 0xb256)
		वापस handle_sthyi(vcpu);

	अगर (vcpu->arch.sie_block->ipa == 0 && vcpu->kvm->arch.user_instr0)
		वापस -EOPNOTSUPP;
	rc = पढ़ो_guest_lc(vcpu, __LC_PGM_NEW_PSW, &newpsw, माप(psw_t));
	अगर (rc)
		वापस rc;
	/*
	 * Aव्योम endless loops of operation exceptions, अगर the pgm new
	 * PSW will cause a new operation exception.
	 * The heuristic checks अगर the pgm new psw is within 6 bytes beक्रमe
	 * the faulting psw address (with same DAT, AS settings) and the
	 * new psw is not a रुको psw and the fault was not triggered by
	 * problem state.
	 */
	oldpsw = vcpu->arch.sie_block->gpsw;
	अगर (oldpsw.addr - newpsw.addr <= 6 &&
	    !(newpsw.mask & PSW_MASK_WAIT) &&
	    !(oldpsw.mask & PSW_MASK_PSTATE) &&
	    (newpsw.mask & PSW_MASK_ASC) == (oldpsw.mask & PSW_MASK_ASC) &&
	    (newpsw.mask & PSW_MASK_DAT) == (oldpsw.mask & PSW_MASK_DAT))
		वापस -EOPNOTSUPP;

	वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_OPERATION);
पूर्ण

अटल पूर्णांक handle_pv_spx(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 pref = *(u32 *)vcpu->arch.sie_block->sidad;

	kvm_s390_set_prefix(vcpu, pref);
	trace_kvm_s390_handle_prefix(vcpu, 1, pref);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_pv_sclp(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt *fi = &vcpu->kvm->arch.भग्न_पूर्णांक;

	spin_lock(&fi->lock);
	/*
	 * 2 हालs:
	 * a: an sccb answering पूर्णांकerrupt was alपढ़ोy pending or in flight.
	 *    As the sccb value is not known we can simply set some value to
	 *    trigger delivery of a saved SCCB. UV will then use its saved
	 *    copy of the SCCB value.
	 * b: an error SCCB पूर्णांकerrupt needs to be injected so we also inject
	 *    a fake SCCB address. Firmware will use the proper one.
	 * This makes sure, that both errors and real sccb वापसs will only
	 * be delivered after a notअगरication पूर्णांकercept (inकाष्ठाion has
	 * finished) but not after others.
	 */
	fi->srv_संकेत.ext_params |= 0x43000;
	set_bit(IRQ_PEND_EXT_SERVICE, &fi->pending_irqs);
	clear_bit(IRQ_PEND_EXT_SERVICE, &fi->masked_irqs);
	spin_unlock(&fi->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_pv_uvc(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा uv_cb_share *guest_uvcb = (व्योम *)vcpu->arch.sie_block->sidad;
	काष्ठा uv_cb_cts uvcb = अणु
		.header.cmd	= UVC_CMD_UNPIN_PAGE_SHARED,
		.header.len	= माप(uvcb),
		.guest_handle	= kvm_s390_pv_get_handle(vcpu->kvm),
		.gaddr		= guest_uvcb->paddr,
	पूर्ण;
	पूर्णांक rc;

	अगर (guest_uvcb->header.cmd != UVC_CMD_REMOVE_SHARED_ACCESS) अणु
		WARN_ONCE(1, "Unexpected notification intercept for UVC 0x%x\n",
			  guest_uvcb->header.cmd);
		वापस 0;
	पूर्ण
	rc = gmap_make_secure(vcpu->arch.gmap, uvcb.gaddr, &uvcb);
	/*
	 * If the unpin did not succeed, the guest will निकास again क्रम the UVC
	 * and we will retry the unpin.
	 */
	अगर (rc == -EINVAL)
		वापस 0;
	वापस rc;
पूर्ण

अटल पूर्णांक handle_pv_notअगरication(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.sie_block->ipa == 0xb210)
		वापस handle_pv_spx(vcpu);
	अगर (vcpu->arch.sie_block->ipa == 0xb220)
		वापस handle_pv_sclp(vcpu);
	अगर (vcpu->arch.sie_block->ipa == 0xb9a4)
		वापस handle_pv_uvc(vcpu);

	वापस handle_inकाष्ठाion(vcpu);
पूर्ण

पूर्णांक kvm_handle_sie_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc, per_rc = 0;

	अगर (kvm_is_ucontrol(vcpu->kvm))
		वापस -EOPNOTSUPP;

	चयन (vcpu->arch.sie_block->icptcode) अणु
	हाल ICPT_EXTREQ:
		vcpu->stat.निकास_बाह्यal_request++;
		वापस 0;
	हाल ICPT_IOREQ:
		vcpu->stat.निकास_io_request++;
		वापस 0;
	हाल ICPT_INST:
		rc = handle_inकाष्ठाion(vcpu);
		अवरोध;
	हाल ICPT_PROGI:
		वापस handle_prog(vcpu);
	हाल ICPT_EXTINT:
		वापस handle_बाह्यal_पूर्णांकerrupt(vcpu);
	हाल ICPT_WAIT:
		वापस kvm_s390_handle_रुको(vcpu);
	हाल ICPT_VALIDITY:
		वापस handle_validity(vcpu);
	हाल ICPT_STOP:
		वापस handle_stop(vcpu);
	हाल ICPT_OPEREXC:
		rc = handle_operexc(vcpu);
		अवरोध;
	हाल ICPT_PARTEXEC:
		rc = handle_partial_execution(vcpu);
		अवरोध;
	हाल ICPT_KSS:
		rc = kvm_s390_skey_check_enable(vcpu);
		अवरोध;
	हाल ICPT_MCHKREQ:
	हाल ICPT_INT_ENABLE:
		/*
		 * PSW bit 13 or a CR (0, 6, 14) changed and we might
		 * now be able to deliver पूर्णांकerrupts. The pre-run code
		 * will take care of this.
		 */
		rc = 0;
		अवरोध;
	हाल ICPT_PV_INSTR:
		rc = handle_inकाष्ठाion(vcpu);
		अवरोध;
	हाल ICPT_PV_NOTIFY:
		rc = handle_pv_notअगरication(vcpu);
		अवरोध;
	हाल ICPT_PV_PREF:
		rc = 0;
		gmap_convert_to_secure(vcpu->arch.gmap,
				       kvm_s390_get_prefix(vcpu));
		gmap_convert_to_secure(vcpu->arch.gmap,
				       kvm_s390_get_prefix(vcpu) + PAGE_SIZE);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* process PER, also अगर the instrution is processed in user space */
	अगर (vcpu->arch.sie_block->icptstatus & 0x02 &&
	    (!rc || rc == -EOPNOTSUPP))
		per_rc = kvm_s390_handle_per_अगरetch_icpt(vcpu);
	वापस per_rc ? per_rc : rc;
पूर्ण
