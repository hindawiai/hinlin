<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * handling privileged inकाष्ठाions
 *
 * Copyright IBM Corp. 2008, 2020
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 */

#समावेश <linux/kvm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compat.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/page-states.h>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/ap.h>
#समावेश "gaccess.h"
#समावेश "kvm-s390.h"
#समावेश "trace.h"

अटल पूर्णांक handle_ri(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->stat.inकाष्ठाion_ri++;

	अगर (test_kvm_facility(vcpu->kvm, 64)) अणु
		VCPU_EVENT(vcpu, 3, "%s", "ENABLE: RI (lazy)");
		vcpu->arch.sie_block->ecb3 |= ECB3_RI;
		kvm_s390_retry_instr(vcpu);
		वापस 0;
	पूर्ण अन्यथा
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_OPERATION);
पूर्ण

पूर्णांक kvm_s390_handle_aa(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर ((vcpu->arch.sie_block->ipa & 0xf) <= 4)
		वापस handle_ri(vcpu);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक handle_gs(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->stat.inकाष्ठाion_gs++;

	अगर (test_kvm_facility(vcpu->kvm, 133)) अणु
		VCPU_EVENT(vcpu, 3, "%s", "ENABLE: GS (lazy)");
		preempt_disable();
		__ctl_set_bit(2, 4);
		current->thपढ़ो.gs_cb = (काष्ठा gs_cb *)&vcpu->run->s.regs.gscb;
		restore_gs_cb(current->thपढ़ो.gs_cb);
		preempt_enable();
		vcpu->arch.sie_block->ecb |= ECB_GS;
		vcpu->arch.sie_block->ecd |= ECD_HOSTREGMGMT;
		vcpu->arch.gs_enabled = 1;
		kvm_s390_retry_instr(vcpu);
		वापस 0;
	पूर्ण अन्यथा
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_OPERATION);
पूर्ण

पूर्णांक kvm_s390_handle_e3(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक code = vcpu->arch.sie_block->ipb & 0xff;

	अगर (code == 0x49 || code == 0x4d)
		वापस handle_gs(vcpu);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण
/* Handle SCK (SET CLOCK) पूर्णांकerception */
अटल पूर्णांक handle_set_घड़ी(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_vm_tod_घड़ी gtod = अणु 0 पूर्ण;
	पूर्णांक rc;
	u8 ar;
	u64 op2;

	vcpu->stat.inकाष्ठाion_sck++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	op2 = kvm_s390_get_base_disp_s(vcpu, &ar);
	अगर (op2 & 7)	/* Opeअक्रम must be on a द्विगुनword boundary */
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	rc = पढ़ो_guest(vcpu, op2, ar, &gtod.tod, माप(gtod.tod));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);

	VCPU_EVENT(vcpu, 3, "SCK: setting guest TOD to 0x%llx", gtod.tod);
	kvm_s390_set_tod_घड़ी(vcpu->kvm, &gtod);

	kvm_s390_set_psw_cc(vcpu, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_set_prefix(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 opeअक्रम2;
	u32 address;
	पूर्णांक rc;
	u8 ar;

	vcpu->stat.inकाष्ठाion_spx++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	opeअक्रम2 = kvm_s390_get_base_disp_s(vcpu, &ar);

	/* must be word boundary */
	अगर (opeअक्रम2 & 3)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	/* get the value */
	rc = पढ़ो_guest(vcpu, opeअक्रम2, ar, &address, माप(address));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);

	address &= 0x7fffe000u;

	/*
	 * Make sure the new value is valid memory. We only need to check the
	 * first page, since address is 8k aligned and memory pieces are always
	 * at least 1MB aligned and have at least a size of 1MB.
	 */
	अगर (kvm_is_error_gpa(vcpu->kvm, address))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);

	kvm_s390_set_prefix(vcpu, address);
	trace_kvm_s390_handle_prefix(vcpu, 1, address);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_store_prefix(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 opeअक्रम2;
	u32 address;
	पूर्णांक rc;
	u8 ar;

	vcpu->stat.inकाष्ठाion_stpx++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	opeअक्रम2 = kvm_s390_get_base_disp_s(vcpu, &ar);

	/* must be word boundary */
	अगर (opeअक्रम2 & 3)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	address = kvm_s390_get_prefix(vcpu);

	/* get the value */
	rc = ग_लिखो_guest(vcpu, opeअक्रम2, ar, &address, माप(address));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);

	VCPU_EVENT(vcpu, 3, "STPX: storing prefix 0x%x into 0x%llx", address, opeअक्रम2);
	trace_kvm_s390_handle_prefix(vcpu, 0, address);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_store_cpu_address(काष्ठा kvm_vcpu *vcpu)
अणु
	u16 vcpu_id = vcpu->vcpu_id;
	u64 ga;
	पूर्णांक rc;
	u8 ar;

	vcpu->stat.inकाष्ठाion_stap++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	ga = kvm_s390_get_base_disp_s(vcpu, &ar);

	अगर (ga & 1)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	rc = ग_लिखो_guest(vcpu, ga, ar, &vcpu_id, माप(vcpu_id));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);

	VCPU_EVENT(vcpu, 3, "STAP: storing cpu address (%u) to 0x%llx", vcpu_id, ga);
	trace_kvm_s390_handle_stap(vcpu, ga);
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_skey_check_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc;

	trace_kvm_s390_skey_related_inst(vcpu);
	/* Alपढ़ोy enabled? */
	अगर (vcpu->arch.skey_enabled)
		वापस 0;

	rc = s390_enable_skey();
	VCPU_EVENT(vcpu, 3, "enabling storage keys for guest: %d", rc);
	अगर (rc)
		वापस rc;

	अगर (kvm_s390_test_cpuflags(vcpu, CPUSTAT_KSS))
		kvm_s390_clear_cpuflags(vcpu, CPUSTAT_KSS);
	अगर (!vcpu->kvm->arch.use_skf)
		vcpu->arch.sie_block->ictl |= ICTL_ISKE | ICTL_SSKE | ICTL_RRBE;
	अन्यथा
		vcpu->arch.sie_block->ictl &= ~(ICTL_ISKE | ICTL_SSKE | ICTL_RRBE);
	vcpu->arch.skey_enabled = true;
	वापस 0;
पूर्ण

अटल पूर्णांक try_handle_skey(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc;

	rc = kvm_s390_skey_check_enable(vcpu);
	अगर (rc)
		वापस rc;
	अगर (vcpu->kvm->arch.use_skf) अणु
		/* with storage-key facility, SIE पूर्णांकerprets it क्रम us */
		kvm_s390_retry_instr(vcpu);
		VCPU_EVENT(vcpu, 4, "%s", "retrying storage key operation");
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक handle_iske(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ gaddr, vmaddr;
	अचिन्हित अक्षर key;
	पूर्णांक reg1, reg2;
	bool unlocked;
	पूर्णांक rc;

	vcpu->stat.inकाष्ठाion_iske++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	rc = try_handle_skey(vcpu);
	अगर (rc)
		वापस rc != -EAGAIN ? rc : 0;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	gaddr = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	gaddr = kvm_s390_logical_to_effective(vcpu, gaddr);
	gaddr = kvm_s390_real_to_असल(vcpu, gaddr);
	vmaddr = gfn_to_hva(vcpu->kvm, gpa_to_gfn(gaddr));
	अगर (kvm_is_error_hva(vmaddr))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
retry:
	unlocked = false;
	mmap_पढ़ो_lock(current->mm);
	rc = get_guest_storage_key(current->mm, vmaddr, &key);

	अगर (rc) अणु
		rc = fixup_user_fault(current->mm, vmaddr,
				      FAULT_FLAG_WRITE, &unlocked);
		अगर (!rc) अणु
			mmap_पढ़ो_unlock(current->mm);
			जाओ retry;
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(current->mm);
	अगर (rc == -EFAULT)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
	अगर (rc < 0)
		वापस rc;
	vcpu->run->s.regs.gprs[reg1] &= ~0xff;
	vcpu->run->s.regs.gprs[reg1] |= key;
	वापस 0;
पूर्ण

अटल पूर्णांक handle_rrbe(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ vmaddr, gaddr;
	पूर्णांक reg1, reg2;
	bool unlocked;
	पूर्णांक rc;

	vcpu->stat.inकाष्ठाion_rrbe++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	rc = try_handle_skey(vcpu);
	अगर (rc)
		वापस rc != -EAGAIN ? rc : 0;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	gaddr = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	gaddr = kvm_s390_logical_to_effective(vcpu, gaddr);
	gaddr = kvm_s390_real_to_असल(vcpu, gaddr);
	vmaddr = gfn_to_hva(vcpu->kvm, gpa_to_gfn(gaddr));
	अगर (kvm_is_error_hva(vmaddr))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
retry:
	unlocked = false;
	mmap_पढ़ो_lock(current->mm);
	rc = reset_guest_reference_bit(current->mm, vmaddr);
	अगर (rc < 0) अणु
		rc = fixup_user_fault(current->mm, vmaddr,
				      FAULT_FLAG_WRITE, &unlocked);
		अगर (!rc) अणु
			mmap_पढ़ो_unlock(current->mm);
			जाओ retry;
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(current->mm);
	अगर (rc == -EFAULT)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
	अगर (rc < 0)
		वापस rc;
	kvm_s390_set_psw_cc(vcpu, rc);
	वापस 0;
पूर्ण

#घोषणा SSKE_NQ 0x8
#घोषणा SSKE_MR 0x4
#घोषणा SSKE_MC 0x2
#घोषणा SSKE_MB 0x1
अटल पूर्णांक handle_sske(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित अक्षर m3 = vcpu->arch.sie_block->ipb >> 28;
	अचिन्हित दीर्घ start, end;
	अचिन्हित अक्षर key, oldkey;
	पूर्णांक reg1, reg2;
	bool unlocked;
	पूर्णांक rc;

	vcpu->stat.inकाष्ठाion_sske++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	rc = try_handle_skey(vcpu);
	अगर (rc)
		वापस rc != -EAGAIN ? rc : 0;

	अगर (!test_kvm_facility(vcpu->kvm, 8))
		m3 &= ~SSKE_MB;
	अगर (!test_kvm_facility(vcpu->kvm, 10))
		m3 &= ~(SSKE_MC | SSKE_MR);
	अगर (!test_kvm_facility(vcpu->kvm, 14))
		m3 &= ~SSKE_NQ;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	key = vcpu->run->s.regs.gprs[reg1] & 0xfe;
	start = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	start = kvm_s390_logical_to_effective(vcpu, start);
	अगर (m3 & SSKE_MB) अणु
		/* start alपढ़ोy designates an असलolute address */
		end = (start + _SEGMENT_SIZE) & ~(_SEGMENT_SIZE - 1);
	पूर्ण अन्यथा अणु
		start = kvm_s390_real_to_असल(vcpu, start);
		end = start + PAGE_SIZE;
	पूर्ण

	जबतक (start != end) अणु
		अचिन्हित दीर्घ vmaddr = gfn_to_hva(vcpu->kvm, gpa_to_gfn(start));
		unlocked = false;

		अगर (kvm_is_error_hva(vmaddr))
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);

		mmap_पढ़ो_lock(current->mm);
		rc = cond_set_guest_storage_key(current->mm, vmaddr, key, &oldkey,
						m3 & SSKE_NQ, m3 & SSKE_MR,
						m3 & SSKE_MC);

		अगर (rc < 0) अणु
			rc = fixup_user_fault(current->mm, vmaddr,
					      FAULT_FLAG_WRITE, &unlocked);
			rc = !rc ? -EAGAIN : rc;
		पूर्ण
		mmap_पढ़ो_unlock(current->mm);
		अगर (rc == -EFAULT)
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
		अगर (rc < 0)
			वापस rc;
		start += PAGE_SIZE;
	पूर्ण

	अगर (m3 & (SSKE_MC | SSKE_MR)) अणु
		अगर (m3 & SSKE_MB) अणु
			/* skey in reg1 is unpredictable */
			kvm_s390_set_psw_cc(vcpu, 3);
		पूर्ण अन्यथा अणु
			kvm_s390_set_psw_cc(vcpu, rc);
			vcpu->run->s.regs.gprs[reg1] &= ~0xff00UL;
			vcpu->run->s.regs.gprs[reg1] |= (u64) oldkey << 8;
		पूर्ण
	पूर्ण
	अगर (m3 & SSKE_MB) अणु
		अगर (psw_bits(vcpu->arch.sie_block->gpsw).eaba == PSW_BITS_AMODE_64BIT)
			vcpu->run->s.regs.gprs[reg2] &= ~PAGE_MASK;
		अन्यथा
			vcpu->run->s.regs.gprs[reg2] &= ~0xfffff000UL;
		end = kvm_s390_logical_to_effective(vcpu, end);
		vcpu->run->s.regs.gprs[reg2] |= end;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक handle_ipte_पूर्णांकerlock(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->stat.inकाष्ठाion_ipte_पूर्णांकerlock++;
	अगर (psw_bits(vcpu->arch.sie_block->gpsw).pstate)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);
	रुको_event(vcpu->kvm->arch.ipte_wq, !ipte_lock_held(vcpu));
	kvm_s390_retry_instr(vcpu);
	VCPU_EVENT(vcpu, 4, "%s", "retrying ipte interlock operation");
	वापस 0;
पूर्ण

अटल पूर्णांक handle_test_block(काष्ठा kvm_vcpu *vcpu)
अणु
	gpa_t addr;
	पूर्णांक reg2;

	vcpu->stat.inकाष्ठाion_tb++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	kvm_s390_get_regs_rre(vcpu, शून्य, &reg2);
	addr = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	addr = kvm_s390_logical_to_effective(vcpu, addr);
	अगर (kvm_s390_check_low_addr_prot_real(vcpu, addr))
		वापस kvm_s390_inject_prog_irq(vcpu, &vcpu->arch.pgm);
	addr = kvm_s390_real_to_असल(vcpu, addr);

	अगर (kvm_is_error_gpa(vcpu->kvm, addr))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
	/*
	 * We करोn't expect errors on modern प्रणालीs, and करो not care
	 * about storage keys (yet), so let's just clear the page.
	 */
	अगर (kvm_clear_guest(vcpu->kvm, addr, PAGE_SIZE))
		वापस -EFAULT;
	kvm_s390_set_psw_cc(vcpu, 0);
	vcpu->run->s.regs.gprs[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक handle_tpi(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi;
	अचिन्हित दीर्घ len;
	u32 tpi_data[3];
	पूर्णांक rc;
	u64 addr;
	u8 ar;

	vcpu->stat.inकाष्ठाion_tpi++;

	addr = kvm_s390_get_base_disp_s(vcpu, &ar);
	अगर (addr & 3)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	पूर्णांकi = kvm_s390_get_io_पूर्णांक(vcpu->kvm, vcpu->arch.sie_block->gcr[6], 0);
	अगर (!पूर्णांकi) अणु
		kvm_s390_set_psw_cc(vcpu, 0);
		वापस 0;
	पूर्ण

	tpi_data[0] = पूर्णांकi->io.subchannel_id << 16 | पूर्णांकi->io.subchannel_nr;
	tpi_data[1] = पूर्णांकi->io.io_पूर्णांक_parm;
	tpi_data[2] = पूर्णांकi->io.io_पूर्णांक_word;
	अगर (addr) अणु
		/*
		 * Store the two-word I/O पूर्णांकerruption code पूर्णांकo the
		 * provided area.
		 */
		len = माप(tpi_data) - 4;
		rc = ग_लिखो_guest(vcpu, addr, ar, &tpi_data, len);
		अगर (rc) अणु
			rc = kvm_s390_inject_prog_cond(vcpu, rc);
			जाओ reinject_पूर्णांकerrupt;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Store the three-word I/O पूर्णांकerruption code पूर्णांकo
		 * the appropriate lowcore area.
		 */
		len = माप(tpi_data);
		अगर (ग_लिखो_guest_lc(vcpu, __LC_SUBCHANNEL_ID, &tpi_data, len)) अणु
			/* failed ग_लिखोs to the low core are not recoverable */
			rc = -EFAULT;
			जाओ reinject_पूर्णांकerrupt;
		पूर्ण
	पूर्ण

	/* irq was successfully handed to the guest */
	kमुक्त(पूर्णांकi);
	kvm_s390_set_psw_cc(vcpu, 1);
	वापस 0;
reinject_पूर्णांकerrupt:
	/*
	 * If we encounter a problem storing the पूर्णांकerruption code, the
	 * inकाष्ठाion is suppressed from the guest's view: reinject the
	 * पूर्णांकerrupt.
	 */
	अगर (kvm_s390_reinject_io_पूर्णांक(vcpu->kvm, पूर्णांकi)) अणु
		kमुक्त(पूर्णांकi);
		rc = -EFAULT;
	पूर्ण
	/* करोn't set the cc, a pgm irq was injected or we drop to user space */
	वापस rc ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक handle_tsch(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi = शून्य;
	स्थिर u64 isc_mask = 0xffUL << 24; /* all iscs set */

	vcpu->stat.inकाष्ठाion_tsch++;

	/* a valid schid has at least one bit set */
	अगर (vcpu->run->s.regs.gprs[1])
		पूर्णांकi = kvm_s390_get_io_पूर्णांक(vcpu->kvm, isc_mask,
					   vcpu->run->s.regs.gprs[1]);

	/*
	 * Prepare निकास to userspace.
	 * We indicate whether we dequeued a pending I/O पूर्णांकerrupt
	 * so that userspace can re-inject it अगर the inकाष्ठाion माला_लो
	 * a program check. While this may re-order the pending I/O
	 * पूर्णांकerrupts, this is no problem since the priority is kept
	 * पूर्णांकact.
	 */
	vcpu->run->निकास_reason = KVM_EXIT_S390_TSCH;
	vcpu->run->s390_tsch.dequeued = !!पूर्णांकi;
	अगर (पूर्णांकi) अणु
		vcpu->run->s390_tsch.subchannel_id = पूर्णांकi->io.subchannel_id;
		vcpu->run->s390_tsch.subchannel_nr = पूर्णांकi->io.subchannel_nr;
		vcpu->run->s390_tsch.io_पूर्णांक_parm = पूर्णांकi->io.io_पूर्णांक_parm;
		vcpu->run->s390_tsch.io_पूर्णांक_word = पूर्णांकi->io.io_पूर्णांक_word;
	पूर्ण
	vcpu->run->s390_tsch.ipb = vcpu->arch.sie_block->ipb;
	kमुक्त(पूर्णांकi);
	वापस -EREMOTE;
पूर्ण

अटल पूर्णांक handle_io_inst(काष्ठा kvm_vcpu *vcpu)
अणु
	VCPU_EVENT(vcpu, 4, "%s", "I/O instruction");

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	अगर (vcpu->kvm->arch.css_support) अणु
		/*
		 * Most I/O inकाष्ठाions will be handled by userspace.
		 * Exceptions are tpi and the पूर्णांकerrupt portion of tsch.
		 */
		अगर (vcpu->arch.sie_block->ipa == 0xb236)
			वापस handle_tpi(vcpu);
		अगर (vcpu->arch.sie_block->ipa == 0xb235)
			वापस handle_tsch(vcpu);
		/* Handle in userspace. */
		vcpu->stat.inकाष्ठाion_io_other++;
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		/*
		 * Set condition code 3 to stop the guest from issuing channel
		 * I/O inकाष्ठाions.
		 */
		kvm_s390_set_psw_cc(vcpu, 3);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * handle_pqap: Handling pqap पूर्णांकerception
 * @vcpu: the vcpu having issue the pqap inकाष्ठाion
 *
 * We now support PQAP/AQIC inकाष्ठाions and we need to correctly
 * answer the guest even अगर no dedicated driver's hook is available.
 *
 * The पूर्णांकercepting code calls a dedicated callback क्रम this inकाष्ठाion
 * अगर a driver did रेजिस्टर one in the CRYPTO satellite of the
 * SIE block.
 *
 * If no callback is available, the queues are not available, वापस this
 * response code to the caller and set CC to 3.
 * Else वापस the response code वापसed by the callback.
 */
अटल पूर्णांक handle_pqap(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा ap_queue_status status = अणुपूर्ण;
	अचिन्हित दीर्घ reg0;
	पूर्णांक ret;
	uपूर्णांक8_t fc;

	/* Verअगरy that the AP inकाष्ठाion are available */
	अगर (!ap_inकाष्ठाions_available())
		वापस -EOPNOTSUPP;
	/* Verअगरy that the guest is allowed to use AP inकाष्ठाions */
	अगर (!(vcpu->arch.sie_block->eca & ECA_APIE))
		वापस -EOPNOTSUPP;
	/*
	 * The only possibly पूर्णांकercepted functions when AP inकाष्ठाions are
	 * available क्रम the guest are AQIC and TAPQ with the t bit set
	 * since we करो not set IC.3 (FIII) we currently will only पूर्णांकercept
	 * the AQIC function code.
	 * Note: running nested under z/VM can result in पूर्णांकercepts क्रम other
	 * function codes, e.g. PQAP(QCI). We करो not support this and bail out.
	 */
	reg0 = vcpu->run->s.regs.gprs[0];
	fc = (reg0 >> 24) & 0xff;
	अगर (fc != 0x03)
		वापस -EOPNOTSUPP;

	/* PQAP inकाष्ठाion is allowed क्रम guest kernel only */
	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	/* Common PQAP inकाष्ठाion specअगरication exceptions */
	/* bits 41-47 must all be zeros */
	अगर (reg0 & 0x007f0000UL)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	/* APFT not install and T bit set */
	अगर (!test_kvm_facility(vcpu->kvm, 15) && (reg0 & 0x00800000UL))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	/* APXA not installed and APID greater 64 or APQI greater 16 */
	अगर (!(vcpu->kvm->arch.crypto.crycbd & 0x02) && (reg0 & 0x0000c0f0UL))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	/* AQIC function code specअगरic exception */
	/* facility 65 not present क्रम AQIC function code */
	अगर (!test_kvm_facility(vcpu->kvm, 65))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	/*
	 * Verअगरy that the hook callback is रेजिस्टरed, lock the owner
	 * and call the hook.
	 */
	अगर (vcpu->kvm->arch.crypto.pqap_hook) अणु
		अगर (!try_module_get(vcpu->kvm->arch.crypto.pqap_hook->owner))
			वापस -EOPNOTSUPP;
		ret = vcpu->kvm->arch.crypto.pqap_hook->hook(vcpu);
		module_put(vcpu->kvm->arch.crypto.pqap_hook->owner);
		अगर (!ret && vcpu->run->s.regs.gprs[1] & 0x00ff0000)
			kvm_s390_set_psw_cc(vcpu, 3);
		वापस ret;
	पूर्ण
	/*
	 * A vfio_driver must रेजिस्टर a hook.
	 * No hook means no driver to enable the SIE CRYCB and no queues.
	 * We send this response to the guest.
	 */
	status.response_code = 0x01;
	स_नकल(&vcpu->run->s.regs.gprs[1], &status, माप(status));
	kvm_s390_set_psw_cc(vcpu, 3);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_stfl(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक fac;

	vcpu->stat.inकाष्ठाion_stfl++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	/*
	 * We need to shअगरt the lower 32 facility bits (bit 0-31) from a u64
	 * पूर्णांकo a u32 memory representation. They will reमुख्य bits 0-31.
	 */
	fac = *vcpu->kvm->arch.model.fac_list >> 32;
	rc = ग_लिखो_guest_lc(vcpu, दुरत्व(काष्ठा lowcore, stfl_fac_list),
			    &fac, माप(fac));
	अगर (rc)
		वापस rc;
	VCPU_EVENT(vcpu, 3, "STFL: store facility list 0x%x", fac);
	trace_kvm_s390_handle_stfl(vcpu, fac);
	वापस 0;
पूर्ण

#घोषणा PSW_MASK_ADDR_MODE (PSW_MASK_EA | PSW_MASK_BA)
#घोषणा PSW_MASK_UNASSIGNED 0xb80800fe7fffffffUL
#घोषणा PSW_ADDR_24 0x0000000000ffffffUL
#घोषणा PSW_ADDR_31 0x000000007fffffffUL

पूर्णांक is_valid_psw(psw_t *psw)
अणु
	अगर (psw->mask & PSW_MASK_UNASSIGNED)
		वापस 0;
	अगर ((psw->mask & PSW_MASK_ADDR_MODE) == PSW_MASK_BA) अणु
		अगर (psw->addr & ~PSW_ADDR_31)
			वापस 0;
	पूर्ण
	अगर (!(psw->mask & PSW_MASK_ADDR_MODE) && (psw->addr & ~PSW_ADDR_24))
		वापस 0;
	अगर ((psw->mask & PSW_MASK_ADDR_MODE) ==  PSW_MASK_EA)
		वापस 0;
	अगर (psw->addr & 1)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक kvm_s390_handle_lpsw(काष्ठा kvm_vcpu *vcpu)
अणु
	psw_t *gpsw = &vcpu->arch.sie_block->gpsw;
	psw_compat_t new_psw;
	u64 addr;
	पूर्णांक rc;
	u8 ar;

	vcpu->stat.inकाष्ठाion_lpsw++;

	अगर (gpsw->mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	addr = kvm_s390_get_base_disp_s(vcpu, &ar);
	अगर (addr & 7)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	rc = पढ़ो_guest(vcpu, addr, ar, &new_psw, माप(new_psw));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	अगर (!(new_psw.mask & PSW32_MASK_BASE))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	gpsw->mask = (new_psw.mask & ~PSW32_MASK_BASE) << 32;
	gpsw->mask |= new_psw.addr & PSW32_ADDR_AMODE;
	gpsw->addr = new_psw.addr & ~PSW32_ADDR_AMODE;
	अगर (!is_valid_psw(gpsw))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_lpswe(काष्ठा kvm_vcpu *vcpu)
अणु
	psw_t new_psw;
	u64 addr;
	पूर्णांक rc;
	u8 ar;

	vcpu->stat.inकाष्ठाion_lpswe++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	addr = kvm_s390_get_base_disp_s(vcpu, &ar);
	अगर (addr & 7)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	rc = पढ़ो_guest(vcpu, addr, ar, &new_psw, माप(new_psw));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	vcpu->arch.sie_block->gpsw = new_psw;
	अगर (!is_valid_psw(&vcpu->arch.sie_block->gpsw))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_stidp(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 stidp_data = vcpu->kvm->arch.model.cpuid;
	u64 opeअक्रम2;
	पूर्णांक rc;
	u8 ar;

	vcpu->stat.inकाष्ठाion_stidp++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	opeअक्रम2 = kvm_s390_get_base_disp_s(vcpu, &ar);

	अगर (opeअक्रम2 & 7)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	rc = ग_लिखो_guest(vcpu, opeअक्रम2, ar, &stidp_data, माप(stidp_data));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);

	VCPU_EVENT(vcpu, 3, "STIDP: store cpu id 0x%llx", stidp_data);
	वापस 0;
पूर्ण

अटल व्योम handle_stsi_3_2_2(काष्ठा kvm_vcpu *vcpu, काष्ठा sysinfo_3_2_2 *mem)
अणु
	पूर्णांक cpus = 0;
	पूर्णांक n;

	cpus = atomic_पढ़ो(&vcpu->kvm->online_vcpus);

	/* deal with other level 3 hypervisors */
	अगर (stsi(mem, 3, 2, 2))
		mem->count = 0;
	अगर (mem->count < 8)
		mem->count++;
	क्रम (n = mem->count - 1; n > 0 ; n--)
		स_नकल(&mem->vm[n], &mem->vm[n - 1], माप(mem->vm[0]));

	स_रखो(&mem->vm[0], 0, माप(mem->vm[0]));
	mem->vm[0].cpus_total = cpus;
	mem->vm[0].cpus_configured = cpus;
	mem->vm[0].cpus_standby = 0;
	mem->vm[0].cpus_reserved = 0;
	mem->vm[0].caf = 1000;
	स_नकल(mem->vm[0].name, "KVMguest", 8);
	ASCEBC(mem->vm[0].name, 8);
	स_नकल(mem->vm[0].cpi, "KVM/Linux       ", 16);
	ASCEBC(mem->vm[0].cpi, 16);
पूर्ण

अटल व्योम insert_stsi_usr_data(काष्ठा kvm_vcpu *vcpu, u64 addr, u8 ar,
				 u8 fc, u8 sel1, u16 sel2)
अणु
	vcpu->run->निकास_reason = KVM_EXIT_S390_STSI;
	vcpu->run->s390_stsi.addr = addr;
	vcpu->run->s390_stsi.ar = ar;
	vcpu->run->s390_stsi.fc = fc;
	vcpu->run->s390_stsi.sel1 = sel1;
	vcpu->run->s390_stsi.sel2 = sel2;
पूर्ण

अटल पूर्णांक handle_stsi(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक fc = (vcpu->run->s.regs.gprs[0] & 0xf0000000) >> 28;
	पूर्णांक sel1 = vcpu->run->s.regs.gprs[0] & 0xff;
	पूर्णांक sel2 = vcpu->run->s.regs.gprs[1] & 0xffff;
	अचिन्हित दीर्घ mem = 0;
	u64 opeअक्रम2;
	पूर्णांक rc = 0;
	u8 ar;

	vcpu->stat.inकाष्ठाion_stsi++;
	VCPU_EVENT(vcpu, 3, "STSI: fc: %u sel1: %u sel2: %u", fc, sel1, sel2);

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	अगर (fc > 3) अणु
		kvm_s390_set_psw_cc(vcpu, 3);
		वापस 0;
	पूर्ण

	अगर (vcpu->run->s.regs.gprs[0] & 0x0fffff00
	    || vcpu->run->s.regs.gprs[1] & 0xffff0000)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	अगर (fc == 0) अणु
		vcpu->run->s.regs.gprs[0] = 3 << 28;
		kvm_s390_set_psw_cc(vcpu, 0);
		वापस 0;
	पूर्ण

	opeअक्रम2 = kvm_s390_get_base_disp_s(vcpu, &ar);

	अगर (!kvm_s390_pv_cpu_is_रक्षित(vcpu) && (opeअक्रम2 & 0xfff))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	चयन (fc) अणु
	हाल 1: /* same handling क्रम 1 and 2 */
	हाल 2:
		mem = get_zeroed_page(GFP_KERNEL_ACCOUNT);
		अगर (!mem)
			जाओ out_no_data;
		अगर (stsi((व्योम *) mem, fc, sel1, sel2))
			जाओ out_no_data;
		अवरोध;
	हाल 3:
		अगर (sel1 != 2 || sel2 != 2)
			जाओ out_no_data;
		mem = get_zeroed_page(GFP_KERNEL_ACCOUNT);
		अगर (!mem)
			जाओ out_no_data;
		handle_stsi_3_2_2(vcpu, (व्योम *) mem);
		अवरोध;
	पूर्ण
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		स_नकल((व्योम *)sida_origin(vcpu->arch.sie_block), (व्योम *)mem,
		       PAGE_SIZE);
		rc = 0;
	पूर्ण अन्यथा अणु
		rc = ग_लिखो_guest(vcpu, opeअक्रम2, ar, (व्योम *)mem, PAGE_SIZE);
	पूर्ण
	अगर (rc) अणु
		rc = kvm_s390_inject_prog_cond(vcpu, rc);
		जाओ out;
	पूर्ण
	अगर (vcpu->kvm->arch.user_stsi) अणु
		insert_stsi_usr_data(vcpu, opeअक्रम2, ar, fc, sel1, sel2);
		rc = -EREMOTE;
	पूर्ण
	trace_kvm_s390_handle_stsi(vcpu, fc, sel1, sel2, opeअक्रम2);
	मुक्त_page(mem);
	kvm_s390_set_psw_cc(vcpu, 0);
	vcpu->run->s.regs.gprs[0] = 0;
	वापस rc;
out_no_data:
	kvm_s390_set_psw_cc(vcpu, 3);
out:
	मुक्त_page(mem);
	वापस rc;
पूर्ण

पूर्णांक kvm_s390_handle_b2(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (vcpu->arch.sie_block->ipa & 0x00ff) अणु
	हाल 0x02:
		वापस handle_stidp(vcpu);
	हाल 0x04:
		वापस handle_set_घड़ी(vcpu);
	हाल 0x10:
		वापस handle_set_prefix(vcpu);
	हाल 0x11:
		वापस handle_store_prefix(vcpu);
	हाल 0x12:
		वापस handle_store_cpu_address(vcpu);
	हाल 0x14:
		वापस kvm_s390_handle_vsie(vcpu);
	हाल 0x21:
	हाल 0x50:
		वापस handle_ipte_पूर्णांकerlock(vcpu);
	हाल 0x29:
		वापस handle_iske(vcpu);
	हाल 0x2a:
		वापस handle_rrbe(vcpu);
	हाल 0x2b:
		वापस handle_sske(vcpu);
	हाल 0x2c:
		वापस handle_test_block(vcpu);
	हाल 0x30:
	हाल 0x31:
	हाल 0x32:
	हाल 0x33:
	हाल 0x34:
	हाल 0x35:
	हाल 0x36:
	हाल 0x37:
	हाल 0x38:
	हाल 0x39:
	हाल 0x3a:
	हाल 0x3b:
	हाल 0x3c:
	हाल 0x5f:
	हाल 0x74:
	हाल 0x76:
		वापस handle_io_inst(vcpu);
	हाल 0x56:
		वापस handle_sthyi(vcpu);
	हाल 0x7d:
		वापस handle_stsi(vcpu);
	हाल 0xaf:
		वापस handle_pqap(vcpu);
	हाल 0xb1:
		वापस handle_stfl(vcpu);
	हाल 0xb2:
		वापस handle_lpswe(vcpu);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_epsw(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक reg1, reg2;

	vcpu->stat.inकाष्ठाion_epsw++;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	/* This basically extracts the mask half of the psw. */
	vcpu->run->s.regs.gprs[reg1] &= 0xffffffff00000000UL;
	vcpu->run->s.regs.gprs[reg1] |= vcpu->arch.sie_block->gpsw.mask >> 32;
	अगर (reg2) अणु
		vcpu->run->s.regs.gprs[reg2] &= 0xffffffff00000000UL;
		vcpu->run->s.regs.gprs[reg2] |=
			vcpu->arch.sie_block->gpsw.mask & 0x00000000ffffffffUL;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PFMF_RESERVED   0xfffc0101UL
#घोषणा PFMF_SK         0x00020000UL
#घोषणा PFMF_CF         0x00010000UL
#घोषणा PFMF_UI         0x00008000UL
#घोषणा PFMF_FSC        0x00007000UL
#घोषणा PFMF_NQ         0x00000800UL
#घोषणा PFMF_MR         0x00000400UL
#घोषणा PFMF_MC         0x00000200UL
#घोषणा PFMF_KEY        0x000000feUL

अटल पूर्णांक handle_pfmf(काष्ठा kvm_vcpu *vcpu)
अणु
	bool mr = false, mc = false, nq;
	पूर्णांक reg1, reg2;
	अचिन्हित दीर्घ start, end;
	अचिन्हित अक्षर key;

	vcpu->stat.inकाष्ठाion_pfmf++;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	अगर (!test_kvm_facility(vcpu->kvm, 8))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_OPERATION);

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_RESERVED)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	/* Only provide non-quiescing support अगर enabled क्रम the guest */
	अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_NQ &&
	    !test_kvm_facility(vcpu->kvm, 14))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	/* Only provide conditional-SSKE support अगर enabled क्रम the guest */
	अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_SK &&
	    test_kvm_facility(vcpu->kvm, 10)) अणु
		mr = vcpu->run->s.regs.gprs[reg1] & PFMF_MR;
		mc = vcpu->run->s.regs.gprs[reg1] & PFMF_MC;
	पूर्ण

	nq = vcpu->run->s.regs.gprs[reg1] & PFMF_NQ;
	key = vcpu->run->s.regs.gprs[reg1] & PFMF_KEY;
	start = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	start = kvm_s390_logical_to_effective(vcpu, start);

	अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_CF) अणु
		अगर (kvm_s390_check_low_addr_prot_real(vcpu, start))
			वापस kvm_s390_inject_prog_irq(vcpu, &vcpu->arch.pgm);
	पूर्ण

	चयन (vcpu->run->s.regs.gprs[reg1] & PFMF_FSC) अणु
	हाल 0x00000000:
		/* only 4k frames specअगरy a real address */
		start = kvm_s390_real_to_असल(vcpu, start);
		end = (start + PAGE_SIZE) & ~(PAGE_SIZE - 1);
		अवरोध;
	हाल 0x00001000:
		end = (start + _SEGMENT_SIZE) & ~(_SEGMENT_SIZE - 1);
		अवरोध;
	हाल 0x00002000:
		/* only support 2G frame size अगर EDAT2 is available and we are
		   not in 24-bit addressing mode */
		अगर (!test_kvm_facility(vcpu->kvm, 78) ||
		    psw_bits(vcpu->arch.sie_block->gpsw).eaba == PSW_BITS_AMODE_24BIT)
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
		end = (start + _REGION3_SIZE) & ~(_REGION3_SIZE - 1);
		अवरोध;
	शेष:
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);
	पूर्ण

	जबतक (start != end) अणु
		अचिन्हित दीर्घ vmaddr;
		bool unlocked = false;

		/* Translate guest address to host address */
		vmaddr = gfn_to_hva(vcpu->kvm, gpa_to_gfn(start));
		अगर (kvm_is_error_hva(vmaddr))
			वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);

		अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_CF) अणु
			अगर (kvm_clear_guest(vcpu->kvm, start, PAGE_SIZE))
				वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
		पूर्ण

		अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_SK) अणु
			पूर्णांक rc = kvm_s390_skey_check_enable(vcpu);

			अगर (rc)
				वापस rc;
			mmap_पढ़ो_lock(current->mm);
			rc = cond_set_guest_storage_key(current->mm, vmaddr,
							key, शून्य, nq, mr, mc);
			अगर (rc < 0) अणु
				rc = fixup_user_fault(current->mm, vmaddr,
						      FAULT_FLAG_WRITE, &unlocked);
				rc = !rc ? -EAGAIN : rc;
			पूर्ण
			mmap_पढ़ो_unlock(current->mm);
			अगर (rc == -EFAULT)
				वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
			अगर (rc == -EAGAIN)
				जारी;
			अगर (rc < 0)
				वापस rc;
		पूर्ण
		start += PAGE_SIZE;
	पूर्ण
	अगर (vcpu->run->s.regs.gprs[reg1] & PFMF_FSC) अणु
		अगर (psw_bits(vcpu->arch.sie_block->gpsw).eaba == PSW_BITS_AMODE_64BIT) अणु
			vcpu->run->s.regs.gprs[reg2] = end;
		पूर्ण अन्यथा अणु
			vcpu->run->s.regs.gprs[reg2] &= ~0xffffffffUL;
			end = kvm_s390_logical_to_effective(vcpu, end);
			vcpu->run->s.regs.gprs[reg2] |= end;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Must be called with relevant पढ़ो locks held (kvm->mm->mmap_lock, kvm->srcu)
 */
अटल अंतरभूत पूर्णांक __करो_essa(काष्ठा kvm_vcpu *vcpu, स्थिर पूर्णांक orc)
अणु
	पूर्णांक r1, r2, nappended, entries;
	अचिन्हित दीर्घ gfn, hva, res, pgstev, ptev;
	अचिन्हित दीर्घ *cbrlo;

	/*
	 * We करोn't need to set SD.FPF.SK to 1 here, because अगर we have a
	 * machine check here we either handle it or crash
	 */

	kvm_s390_get_regs_rre(vcpu, &r1, &r2);
	gfn = vcpu->run->s.regs.gprs[r2] >> PAGE_SHIFT;
	hva = gfn_to_hva(vcpu->kvm, gfn);
	entries = (vcpu->arch.sie_block->cbrlo & ~PAGE_MASK) >> 3;

	अगर (kvm_is_error_hva(hva))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);

	nappended = pgste_perक्रमm_essa(vcpu->kvm->mm, hva, orc, &ptev, &pgstev);
	अगर (nappended < 0) अणु
		res = orc ? 0x10 : 0;
		vcpu->run->s.regs.gprs[r1] = res; /* Exception Indication */
		वापस 0;
	पूर्ण
	res = (pgstev & _PGSTE_GPS_USAGE_MASK) >> 22;
	/*
	 * Set the block-content state part of the result. 0 means resident, so
	 * nothing to करो अगर the page is valid. 2 is क्रम preserved pages
	 * (non-present and non-zero), and 3 क्रम zero pages (non-present and
	 * zero).
	 */
	अगर (ptev & _PAGE_INVALID) अणु
		res |= 2;
		अगर (pgstev & _PGSTE_GPS_ZERO)
			res |= 1;
	पूर्ण
	अगर (pgstev & _PGSTE_GPS_NODAT)
		res |= 0x20;
	vcpu->run->s.regs.gprs[r1] = res;
	/*
	 * It is possible that all the normal 511 slots were full, in which हाल
	 * we will now ग_लिखो in the 512th slot, which is reserved क्रम host use.
	 * In both हालs we let the normal essa handling code process all the
	 * slots, including the reserved one, अगर needed.
	 */
	अगर (nappended > 0) अणु
		cbrlo = phys_to_virt(vcpu->arch.sie_block->cbrlo & PAGE_MASK);
		cbrlo[entries] = gfn << PAGE_SHIFT;
	पूर्ण

	अगर (orc) अणु
		काष्ठा kvm_memory_slot *ms = gfn_to_memslot(vcpu->kvm, gfn);

		/* Increment only अगर we are really flipping the bit */
		अगर (ms && !test_and_set_bit(gfn - ms->base_gfn, kvm_second_dirty_biपंचांगap(ms)))
			atomic64_inc(&vcpu->kvm->arch.cmma_dirty_pages);
	पूर्ण

	वापस nappended;
पूर्ण

अटल पूर्णांक handle_essa(काष्ठा kvm_vcpu *vcpu)
अणु
	/* entries expected to be 1FF */
	पूर्णांक entries = (vcpu->arch.sie_block->cbrlo & ~PAGE_MASK) >> 3;
	अचिन्हित दीर्घ *cbrlo;
	काष्ठा gmap *gmap;
	पूर्णांक i, orc;

	VCPU_EVENT(vcpu, 4, "ESSA: release %d pages", entries);
	gmap = vcpu->arch.gmap;
	vcpu->stat.inकाष्ठाion_essa++;
	अगर (!vcpu->kvm->arch.use_cmma)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_OPERATION);

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);
	/* Check क्रम invalid operation request code */
	orc = (vcpu->arch.sie_block->ipb & 0xf0000000) >> 28;
	/* ORCs 0-6 are always valid */
	अगर (orc > (test_kvm_facility(vcpu->kvm, 147) ? ESSA_SET_STABLE_NODAT
						: ESSA_SET_STABLE_IF_RESIDENT))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	अगर (!vcpu->kvm->arch.migration_mode) अणु
		/*
		 * CMMA is enabled in the KVM settings, but is disabled in
		 * the SIE block and in the mm_context, and we are not करोing
		 * a migration. Enable CMMA in the mm_context.
		 * Since we need to take a ग_लिखो lock to ग_लिखो to the context
		 * to aव्योम races with storage keys handling, we check अगर the
		 * value really needs to be written to; अगर the value is
		 * alपढ़ोy correct, we करो nothing and aव्योम the lock.
		 */
		अगर (vcpu->kvm->mm->context.uses_cmm == 0) अणु
			mmap_ग_लिखो_lock(vcpu->kvm->mm);
			vcpu->kvm->mm->context.uses_cmm = 1;
			mmap_ग_लिखो_unlock(vcpu->kvm->mm);
		पूर्ण
		/*
		 * If we are here, we are supposed to have CMMA enabled in
		 * the SIE block. Enabling CMMA works on a per-CPU basis,
		 * जबतक the context use_cmma flag is per process.
		 * It's possible that the context flag is enabled and the
		 * SIE flag is not, so we set the flag always; अगर it was
		 * alपढ़ोy set, nothing changes, otherwise we enable it
		 * on this CPU too.
		 */
		vcpu->arch.sie_block->ecb2 |= ECB2_CMMA;
		/* Retry the ESSA inकाष्ठाion */
		kvm_s390_retry_instr(vcpu);
	पूर्ण अन्यथा अणु
		पूर्णांक srcu_idx;

		mmap_पढ़ो_lock(vcpu->kvm->mm);
		srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		i = __करो_essa(vcpu, orc);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
		mmap_पढ़ो_unlock(vcpu->kvm->mm);
		अगर (i < 0)
			वापस i;
		/* Account क्रम the possible extra cbrl entry */
		entries += i;
	पूर्ण
	vcpu->arch.sie_block->cbrlo &= PAGE_MASK;	/* reset nceo */
	cbrlo = phys_to_virt(vcpu->arch.sie_block->cbrlo);
	mmap_पढ़ो_lock(gmap->mm);
	क्रम (i = 0; i < entries; ++i)
		__gmap_zap(gmap, cbrlo[i]);
	mmap_पढ़ो_unlock(gmap->mm);
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_handle_b9(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (vcpu->arch.sie_block->ipa & 0x00ff) अणु
	हाल 0x8a:
	हाल 0x8e:
	हाल 0x8f:
		वापस handle_ipte_पूर्णांकerlock(vcpu);
	हाल 0x8d:
		वापस handle_epsw(vcpu);
	हाल 0xab:
		वापस handle_essa(vcpu);
	हाल 0xaf:
		वापस handle_pfmf(vcpu);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक kvm_s390_handle_lctl(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक reg1 = (vcpu->arch.sie_block->ipa & 0x00f0) >> 4;
	पूर्णांक reg3 = vcpu->arch.sie_block->ipa & 0x000f;
	पूर्णांक reg, rc, nr_regs;
	u32 ctl_array[16];
	u64 ga;
	u8 ar;

	vcpu->stat.inकाष्ठाion_lctl++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	ga = kvm_s390_get_base_disp_rs(vcpu, &ar);

	अगर (ga & 3)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "LCTL: r1:%d, r3:%d, addr: 0x%llx", reg1, reg3, ga);
	trace_kvm_s390_handle_lctl(vcpu, 0, reg1, reg3, ga);

	nr_regs = ((reg3 - reg1) & 0xf) + 1;
	rc = पढ़ो_guest(vcpu, ga, ar, ctl_array, nr_regs * माप(u32));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	reg = reg1;
	nr_regs = 0;
	करो अणु
		vcpu->arch.sie_block->gcr[reg] &= 0xffffffff00000000ul;
		vcpu->arch.sie_block->gcr[reg] |= ctl_array[nr_regs++];
		अगर (reg == reg3)
			अवरोध;
		reg = (reg + 1) % 16;
	पूर्ण जबतक (1);
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_handle_stctl(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक reg1 = (vcpu->arch.sie_block->ipa & 0x00f0) >> 4;
	पूर्णांक reg3 = vcpu->arch.sie_block->ipa & 0x000f;
	पूर्णांक reg, rc, nr_regs;
	u32 ctl_array[16];
	u64 ga;
	u8 ar;

	vcpu->stat.inकाष्ठाion_stctl++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	ga = kvm_s390_get_base_disp_rs(vcpu, &ar);

	अगर (ga & 3)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "STCTL r1:%d, r3:%d, addr: 0x%llx", reg1, reg3, ga);
	trace_kvm_s390_handle_stctl(vcpu, 0, reg1, reg3, ga);

	reg = reg1;
	nr_regs = 0;
	करो अणु
		ctl_array[nr_regs++] = vcpu->arch.sie_block->gcr[reg];
		अगर (reg == reg3)
			अवरोध;
		reg = (reg + 1) % 16;
	पूर्ण जबतक (1);
	rc = ग_लिखो_guest(vcpu, ga, ar, ctl_array, nr_regs * माप(u32));
	वापस rc ? kvm_s390_inject_prog_cond(vcpu, rc) : 0;
पूर्ण

अटल पूर्णांक handle_lctlg(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक reg1 = (vcpu->arch.sie_block->ipa & 0x00f0) >> 4;
	पूर्णांक reg3 = vcpu->arch.sie_block->ipa & 0x000f;
	पूर्णांक reg, rc, nr_regs;
	u64 ctl_array[16];
	u64 ga;
	u8 ar;

	vcpu->stat.inकाष्ठाion_lctlg++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	ga = kvm_s390_get_base_disp_rsy(vcpu, &ar);

	अगर (ga & 7)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "LCTLG: r1:%d, r3:%d, addr: 0x%llx", reg1, reg3, ga);
	trace_kvm_s390_handle_lctl(vcpu, 1, reg1, reg3, ga);

	nr_regs = ((reg3 - reg1) & 0xf) + 1;
	rc = पढ़ो_guest(vcpu, ga, ar, ctl_array, nr_regs * माप(u64));
	अगर (rc)
		वापस kvm_s390_inject_prog_cond(vcpu, rc);
	reg = reg1;
	nr_regs = 0;
	करो अणु
		vcpu->arch.sie_block->gcr[reg] = ctl_array[nr_regs++];
		अगर (reg == reg3)
			अवरोध;
		reg = (reg + 1) % 16;
	पूर्ण जबतक (1);
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_stctg(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक reg1 = (vcpu->arch.sie_block->ipa & 0x00f0) >> 4;
	पूर्णांक reg3 = vcpu->arch.sie_block->ipa & 0x000f;
	पूर्णांक reg, rc, nr_regs;
	u64 ctl_array[16];
	u64 ga;
	u8 ar;

	vcpu->stat.inकाष्ठाion_stctg++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	ga = kvm_s390_get_base_disp_rsy(vcpu, &ar);

	अगर (ga & 7)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "STCTG r1:%d, r3:%d, addr: 0x%llx", reg1, reg3, ga);
	trace_kvm_s390_handle_stctl(vcpu, 1, reg1, reg3, ga);

	reg = reg1;
	nr_regs = 0;
	करो अणु
		ctl_array[nr_regs++] = vcpu->arch.sie_block->gcr[reg];
		अगर (reg == reg3)
			अवरोध;
		reg = (reg + 1) % 16;
	पूर्ण जबतक (1);
	rc = ग_लिखो_guest(vcpu, ga, ar, ctl_array, nr_regs * माप(u64));
	वापस rc ? kvm_s390_inject_prog_cond(vcpu, rc) : 0;
पूर्ण

पूर्णांक kvm_s390_handle_eb(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (vcpu->arch.sie_block->ipb & 0x000000ff) अणु
	हाल 0x25:
		वापस handle_stctg(vcpu);
	हाल 0x2f:
		वापस handle_lctlg(vcpu);
	हाल 0x60:
	हाल 0x61:
	हाल 0x62:
		वापस handle_ri(vcpu);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_tprot(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 address1, address2;
	अचिन्हित दीर्घ hva, gpa;
	पूर्णांक ret = 0, cc = 0;
	bool writable;
	u8 ar;

	vcpu->stat.inकाष्ठाion_tprot++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	kvm_s390_get_base_disp_sse(vcpu, &address1, &address2, &ar, शून्य);

	/* we only handle the Linux memory detection हाल:
	 * access key == 0
	 * everything अन्यथा goes to userspace. */
	अगर (address2 & 0xf0)
		वापस -EOPNOTSUPP;
	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_DAT)
		ipte_lock(vcpu);
	ret = guest_translate_address(vcpu, address1, ar, &gpa, GACC_STORE);
	अगर (ret == PGM_PROTECTION) अणु
		/* Write रक्षित? Try again with पढ़ो-only... */
		cc = 1;
		ret = guest_translate_address(vcpu, address1, ar, &gpa,
					      GACC_FETCH);
	पूर्ण
	अगर (ret) अणु
		अगर (ret == PGM_ADDRESSING || ret == PGM_TRANSLATION_SPEC) अणु
			ret = kvm_s390_inject_program_पूर्णांक(vcpu, ret);
		पूर्ण अन्यथा अगर (ret > 0) अणु
			/* Translation not available */
			kvm_s390_set_psw_cc(vcpu, 3);
			ret = 0;
		पूर्ण
		जाओ out_unlock;
	पूर्ण

	hva = gfn_to_hva_prot(vcpu->kvm, gpa_to_gfn(gpa), &writable);
	अगर (kvm_is_error_hva(hva)) अणु
		ret = kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
	पूर्ण अन्यथा अणु
		अगर (!writable)
			cc = 1;		/* Write not permitted ==> पढ़ो-only */
		kvm_s390_set_psw_cc(vcpu, cc);
		/* Note: CC2 only occurs क्रम storage keys (not supported yet) */
	पूर्ण
out_unlock:
	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_DAT)
		ipte_unlock(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvm_s390_handle_e5(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (vcpu->arch.sie_block->ipa & 0x00ff) अणु
	हाल 0x01:
		वापस handle_tprot(vcpu);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_sckpf(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 value;

	vcpu->stat.inकाष्ठाion_sckpf++;

	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	अगर (vcpu->run->s.regs.gprs[0] & 0x00000000ffff0000)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu,
						   PGM_SPECIFICATION);

	value = vcpu->run->s.regs.gprs[0] & 0x000000000000ffff;
	vcpu->arch.sie_block->todpr = value;

	वापस 0;
पूर्ण

अटल पूर्णांक handle_ptff(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->stat.inकाष्ठाion_ptff++;

	/* we करोn't emulate any control inकाष्ठाions yet */
	kvm_s390_set_psw_cc(vcpu, 3);
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_handle_01(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (vcpu->arch.sie_block->ipa & 0x00ff) अणु
	हाल 0x04:
		वापस handle_ptff(vcpu);
	हाल 0x07:
		वापस handle_sckpf(vcpu);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
