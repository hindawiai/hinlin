<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * definition क्रम kvm on s390
 *
 * Copyright IBM Corp. 2008, 2020
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 *               Christian Ehrhardt <ehrhardt@de.ibm.com>
 */

#अगर_अघोषित ARCH_S390_KVM_S390_H
#घोषणा ARCH_S390_KVM_S390_H

#समावेश <linux/hrसमयr.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/lockdep.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sclp.h>

/* Transactional Memory Execution related macros */
#घोषणा IS_TE_ENABLED(vcpu)	((vcpu->arch.sie_block->ecb & ECB_TE))
#घोषणा TDB_FORMAT1		1
#घोषणा IS_ITDB_VALID(vcpu)	((*(अक्षर *)vcpu->arch.sie_block->itdba == TDB_FORMAT1))

बाह्य debug_info_t *kvm_s390_dbf;
बाह्य debug_info_t *kvm_s390_dbf_uv;

#घोषणा KVM_UV_EVENT(d_kvm, d_loglevel, d_string, d_args...)\
करो अणु \
	debug_प्र_लिखो_event((d_kvm)->arch.dbf, d_loglevel, d_string "\n", \
	  d_args); \
	debug_प्र_लिखो_event(kvm_s390_dbf_uv, d_loglevel, \
			    "%d: " d_string "\n", (d_kvm)->userspace_pid, \
			    d_args); \
पूर्ण जबतक (0)

#घोषणा KVM_EVENT(d_loglevel, d_string, d_args...)\
करो अणु \
	debug_प्र_लिखो_event(kvm_s390_dbf, d_loglevel, d_string "\n", \
	  d_args); \
पूर्ण जबतक (0)

#घोषणा VM_EVENT(d_kvm, d_loglevel, d_string, d_args...)\
करो अणु \
	debug_प्र_लिखो_event(d_kvm->arch.dbf, d_loglevel, d_string "\n", \
	  d_args); \
पूर्ण जबतक (0)

#घोषणा VCPU_EVENT(d_vcpu, d_loglevel, d_string, d_args...)\
करो अणु \
	debug_प्र_लिखो_event(d_vcpu->kvm->arch.dbf, d_loglevel, \
	  "%02d[%016lx-%016lx]: " d_string "\n", d_vcpu->vcpu_id, \
	  d_vcpu->arch.sie_block->gpsw.mask, d_vcpu->arch.sie_block->gpsw.addr,\
	  d_args); \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम kvm_s390_set_cpuflags(काष्ठा kvm_vcpu *vcpu, u32 flags)
अणु
	atomic_or(flags, &vcpu->arch.sie_block->cpuflags);
पूर्ण

अटल अंतरभूत व्योम kvm_s390_clear_cpuflags(काष्ठा kvm_vcpu *vcpu, u32 flags)
अणु
	atomic_andnot(flags, &vcpu->arch.sie_block->cpuflags);
पूर्ण

अटल अंतरभूत bool kvm_s390_test_cpuflags(काष्ठा kvm_vcpu *vcpu, u32 flags)
अणु
	वापस (atomic_पढ़ो(&vcpu->arch.sie_block->cpuflags) & flags) == flags;
पूर्ण

अटल अंतरभूत पूर्णांक is_vcpu_stopped(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_s390_test_cpuflags(vcpu, CPUSTAT_STOPPED);
पूर्ण

अटल अंतरभूत पूर्णांक is_vcpu_idle(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस test_bit(vcpu->vcpu_id, vcpu->kvm->arch.idle_mask);
पूर्ण

अटल अंतरभूत पूर्णांक kvm_is_ucontrol(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_KVM_S390_UCONTROL
	अगर (kvm->arch.gmap)
		वापस 0;
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#घोषणा GUEST_PREFIX_SHIFT 13
अटल अंतरभूत u32 kvm_s390_get_prefix(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.sie_block->prefix << GUEST_PREFIX_SHIFT;
पूर्ण

अटल अंतरभूत व्योम kvm_s390_set_prefix(काष्ठा kvm_vcpu *vcpu, u32 prefix)
अणु
	VCPU_EVENT(vcpu, 3, "set prefix of cpu %03u to 0x%x", vcpu->vcpu_id,
		   prefix);
	vcpu->arch.sie_block->prefix = prefix >> GUEST_PREFIX_SHIFT;
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	kvm_make_request(KVM_REQ_MMU_RELOAD, vcpu);
पूर्ण

अटल अंतरभूत u64 kvm_s390_get_base_disp_s(काष्ठा kvm_vcpu *vcpu, u8 *ar)
अणु
	u32 base2 = vcpu->arch.sie_block->ipb >> 28;
	u32 disp2 = ((vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16);

	अगर (ar)
		*ar = base2;

	वापस (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + disp2;
पूर्ण

अटल अंतरभूत व्योम kvm_s390_get_base_disp_sse(काष्ठा kvm_vcpu *vcpu,
					      u64 *address1, u64 *address2,
					      u8 *ar_b1, u8 *ar_b2)
अणु
	u32 base1 = (vcpu->arch.sie_block->ipb & 0xf0000000) >> 28;
	u32 disp1 = (vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16;
	u32 base2 = (vcpu->arch.sie_block->ipb & 0xf000) >> 12;
	u32 disp2 = vcpu->arch.sie_block->ipb & 0x0fff;

	*address1 = (base1 ? vcpu->run->s.regs.gprs[base1] : 0) + disp1;
	*address2 = (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + disp2;

	अगर (ar_b1)
		*ar_b1 = base1;
	अगर (ar_b2)
		*ar_b2 = base2;
पूर्ण

अटल अंतरभूत व्योम kvm_s390_get_regs_rre(काष्ठा kvm_vcpu *vcpu, पूर्णांक *r1, पूर्णांक *r2)
अणु
	अगर (r1)
		*r1 = (vcpu->arch.sie_block->ipb & 0x00f00000) >> 20;
	अगर (r2)
		*r2 = (vcpu->arch.sie_block->ipb & 0x000f0000) >> 16;
पूर्ण

अटल अंतरभूत u64 kvm_s390_get_base_disp_rsy(काष्ठा kvm_vcpu *vcpu, u8 *ar)
अणु
	u32 base2 = vcpu->arch.sie_block->ipb >> 28;
	u32 disp2 = ((vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16) +
			((vcpu->arch.sie_block->ipb & 0xff00) << 4);
	/* The displacement is a 20bit _SIGNED_ value */
	अगर (disp2 & 0x80000)
		disp2+=0xfff00000;

	अगर (ar)
		*ar = base2;

	वापस (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + (दीर्घ)(पूर्णांक)disp2;
पूर्ण

अटल अंतरभूत u64 kvm_s390_get_base_disp_rs(काष्ठा kvm_vcpu *vcpu, u8 *ar)
अणु
	u32 base2 = vcpu->arch.sie_block->ipb >> 28;
	u32 disp2 = ((vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16);

	अगर (ar)
		*ar = base2;

	वापस (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + disp2;
पूर्ण

/* Set the condition code in the guest program status word */
अटल अंतरभूत व्योम kvm_s390_set_psw_cc(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cc)
अणु
	vcpu->arch.sie_block->gpsw.mask &= ~(3UL << 44);
	vcpu->arch.sie_block->gpsw.mask |= cc << 44;
पूर्ण

/* test availability of facility in a kvm instance */
अटल अंतरभूत पूर्णांक test_kvm_facility(काष्ठा kvm *kvm, अचिन्हित दीर्घ nr)
अणु
	वापस __test_facility(nr, kvm->arch.model.fac_mask) &&
		__test_facility(nr, kvm->arch.model.fac_list);
पूर्ण

अटल अंतरभूत पूर्णांक set_kvm_facility(u64 *fac_list, अचिन्हित दीर्घ nr)
अणु
	अचिन्हित अक्षर *ptr;

	अगर (nr >= MAX_FACILITY_BIT)
		वापस -EINVAL;
	ptr = (अचिन्हित अक्षर *) fac_list + (nr >> 3);
	*ptr |= (0x80UL >> (nr & 7));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक test_kvm_cpu_feat(काष्ठा kvm *kvm, अचिन्हित दीर्घ nr)
अणु
	WARN_ON_ONCE(nr >= KVM_S390_VM_CPU_FEAT_NR_BITS);
	वापस test_bit_inv(nr, kvm->arch.cpu_feat);
पूर्ण

/* are cpu states controlled by user space */
अटल अंतरभूत पूर्णांक kvm_s390_user_cpu_state_ctrl(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.user_cpu_state_ctrl != 0;
पूर्ण

/* implemented in pv.c */
पूर्णांक kvm_s390_pv_destroy_cpu(काष्ठा kvm_vcpu *vcpu, u16 *rc, u16 *rrc);
पूर्णांक kvm_s390_pv_create_cpu(काष्ठा kvm_vcpu *vcpu, u16 *rc, u16 *rrc);
पूर्णांक kvm_s390_pv_deinit_vm(काष्ठा kvm *kvm, u16 *rc, u16 *rrc);
पूर्णांक kvm_s390_pv_init_vm(काष्ठा kvm *kvm, u16 *rc, u16 *rrc);
पूर्णांक kvm_s390_pv_set_sec_parms(काष्ठा kvm *kvm, व्योम *hdr, u64 length, u16 *rc,
			      u16 *rrc);
पूर्णांक kvm_s390_pv_unpack(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
		       अचिन्हित दीर्घ tweak, u16 *rc, u16 *rrc);
पूर्णांक kvm_s390_pv_set_cpu_state(काष्ठा kvm_vcpu *vcpu, u8 state);

अटल अंतरभूत u64 kvm_s390_pv_get_handle(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.pv.handle;
पूर्ण

अटल अंतरभूत u64 kvm_s390_pv_cpu_get_handle(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.pv.handle;
पूर्ण

अटल अंतरभूत bool kvm_s390_pv_is_रक्षित(काष्ठा kvm *kvm)
अणु
	lockdep_निश्चित_held(&kvm->lock);
	वापस !!kvm_s390_pv_get_handle(kvm);
पूर्ण

अटल अंतरभूत bool kvm_s390_pv_cpu_is_रक्षित(काष्ठा kvm_vcpu *vcpu)
अणु
	lockdep_निश्चित_held(&vcpu->mutex);
	वापस !!kvm_s390_pv_cpu_get_handle(vcpu);
पूर्ण

/* implemented in पूर्णांकerrupt.c */
पूर्णांक kvm_s390_handle_रुको(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_vcpu_wakeup(काष्ठा kvm_vcpu *vcpu);
क्रमागत hrसमयr_restart kvm_s390_idle_wakeup(काष्ठा hrसमयr *समयr);
पूर्णांक __must_check kvm_s390_deliver_pending_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_clear_local_irqs(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_clear_भग्न_irqs(काष्ठा kvm *kvm);
पूर्णांक __must_check kvm_s390_inject_vm(काष्ठा kvm *kvm,
				    काष्ठा kvm_s390_पूर्णांकerrupt *s390पूर्णांक);
पूर्णांक __must_check kvm_s390_inject_vcpu(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_s390_irq *irq);
अटल अंतरभूत पूर्णांक kvm_s390_inject_prog_irq(काष्ठा kvm_vcpu *vcpu,
					   काष्ठा kvm_s390_pgm_info *pgm_info)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_PROGRAM_INT,
		.u.pgm = *pgm_info,
	पूर्ण;

	वापस kvm_s390_inject_vcpu(vcpu, &irq);
पूर्ण
अटल अंतरभूत पूर्णांक kvm_s390_inject_program_पूर्णांक(काष्ठा kvm_vcpu *vcpu, u16 code)
अणु
	काष्ठा kvm_s390_irq irq = अणु
		.type = KVM_S390_PROGRAM_INT,
		.u.pgm.code = code,
	पूर्ण;

	वापस kvm_s390_inject_vcpu(vcpu, &irq);
पूर्ण
काष्ठा kvm_s390_पूर्णांकerrupt_info *kvm_s390_get_io_पूर्णांक(काष्ठा kvm *kvm,
						    u64 isc_mask, u32 schid);
पूर्णांक kvm_s390_reinject_io_पूर्णांक(काष्ठा kvm *kvm,
			     काष्ठा kvm_s390_पूर्णांकerrupt_info *पूर्णांकi);
पूर्णांक kvm_s390_mask_adapter(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id, bool masked);

/* implemented in पूर्णांकercept.c */
u8 kvm_s390_get_ilen(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_sie_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu);
अटल अंतरभूत व्योम kvm_s390_शुरुआत_psw(काष्ठा kvm_vcpu *vcpu, पूर्णांक ilen)
अणु
	काष्ठा kvm_s390_sie_block *sie_block = vcpu->arch.sie_block;

	sie_block->gpsw.addr = __शुरुआत_psw(sie_block->gpsw, ilen);
पूर्ण
अटल अंतरभूत व्योम kvm_s390_क्रमward_psw(काष्ठा kvm_vcpu *vcpu, पूर्णांक ilen)
अणु
	kvm_s390_शुरुआत_psw(vcpu, -ilen);
पूर्ण
अटल अंतरभूत व्योम kvm_s390_retry_instr(काष्ठा kvm_vcpu *vcpu)
अणु
	/* करोn't inject PER events अगर we re-execute the inकाष्ठाion */
	vcpu->arch.sie_block->icptstatus &= ~0x02;
	kvm_s390_शुरुआत_psw(vcpu, kvm_s390_get_ilen(vcpu));
पूर्ण

पूर्णांक handle_sthyi(काष्ठा kvm_vcpu *vcpu);

/* implemented in priv.c */
पूर्णांक is_valid_psw(psw_t *psw);
पूर्णांक kvm_s390_handle_aa(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_b2(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_e3(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_e5(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_01(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_b9(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_lpsw(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_stctl(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_lctl(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_eb(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_skey_check_enable(काष्ठा kvm_vcpu *vcpu);

/* implemented in vsie.c */
पूर्णांक kvm_s390_handle_vsie(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_vsie_kick(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_vsie_gmap_notअगरier(काष्ठा gmap *gmap, अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ end);
व्योम kvm_s390_vsie_init(काष्ठा kvm *kvm);
व्योम kvm_s390_vsie_destroy(काष्ठा kvm *kvm);

/* implemented in sigp.c */
पूर्णांक kvm_s390_handle_sigp(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_sigp_pei(काष्ठा kvm_vcpu *vcpu);

/* implemented in kvm-s390.c */
व्योम kvm_s390_set_tod_घड़ी(काष्ठा kvm *kvm,
			    स्थिर काष्ठा kvm_s390_vm_tod_घड़ी *gtod);
दीर्घ kvm_arch_fault_in_page(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, पूर्णांक writable);
पूर्णांक kvm_s390_store_status_unloaded(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr);
पूर्णांक kvm_s390_vcpu_store_status(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr);
पूर्णांक kvm_s390_vcpu_start(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_vcpu_stop(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_vcpu_block(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_vcpu_unblock(काष्ठा kvm_vcpu *vcpu);
bool kvm_s390_vcpu_sie_inhibited(काष्ठा kvm_vcpu *vcpu);
व्योम निकास_sie(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_sync_request(पूर्णांक req, काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_vcpu_setup_cmma(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_vcpu_unsetup_cmma(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_set_cpu_समयr(काष्ठा kvm_vcpu *vcpu, __u64 cpuपंचांग);
__u64 kvm_s390_get_cpu_समयr(काष्ठा kvm_vcpu *vcpu);

/* implemented in diag.c */
पूर्णांक kvm_s390_handle_diag(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत व्योम kvm_s390_vcpu_block_all(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	WARN_ON(!mutex_is_locked(&kvm->lock));
	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_s390_vcpu_block(vcpu);
पूर्ण

अटल अंतरभूत व्योम kvm_s390_vcpu_unblock_all(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_s390_vcpu_unblock(vcpu);
पूर्ण

अटल अंतरभूत u64 kvm_s390_get_tod_घड़ी_fast(काष्ठा kvm *kvm)
अणु
	u64 rc;

	preempt_disable();
	rc = get_tod_घड़ी_fast() + kvm->arch.epoch;
	preempt_enable();
	वापस rc;
पूर्ण

/**
 * kvm_s390_inject_prog_cond - conditionally inject a program check
 * @vcpu: भव cpu
 * @rc: original वापस/error code
 *
 * This function is supposed to be used after regular guest access functions
 * failed, to conditionally inject a program check to a vcpu. The typical
 * pattern would look like
 *
 * rc = ग_लिखो_guest(vcpu, addr, data, len);
 * अगर (rc)
 *	वापस kvm_s390_inject_prog_cond(vcpu, rc);
 *
 * A negative वापस code from guest access functions implies an पूर्णांकernal error
 * like e.g. out of memory. In these हालs no program check should be injected
 * to the guest.
 * A positive value implies that an exception happened जबतक accessing a guest's
 * memory. In this हाल all data beदीर्घing to the corresponding program check
 * has been stored in vcpu->arch.pgm and can be injected with
 * kvm_s390_inject_prog_irq().
 *
 * Returns: - the original @rc value अगर @rc was negative (पूर्णांकernal error)
 *	    - zero अगर @rc was alपढ़ोy zero
 *	    - zero or error code from injecting अगर @rc was positive
 *	      (program check injected to @vcpu)
 */
अटल अंतरभूत पूर्णांक kvm_s390_inject_prog_cond(काष्ठा kvm_vcpu *vcpu, पूर्णांक rc)
अणु
	अगर (rc <= 0)
		वापस rc;
	वापस kvm_s390_inject_prog_irq(vcpu, &vcpu->arch.pgm);
पूर्ण

पूर्णांक s390पूर्णांक_to_s390irq(काष्ठा kvm_s390_पूर्णांकerrupt *s390पूर्णांक,
			काष्ठा kvm_s390_irq *s390irq);

/* implemented in पूर्णांकerrupt.c */
पूर्णांक kvm_s390_vcpu_has_irq(काष्ठा kvm_vcpu *vcpu, पूर्णांक exclude_stop);
पूर्णांक psw_extपूर्णांक_disabled(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_destroy_adapters(काष्ठा kvm *kvm);
पूर्णांक kvm_s390_ext_call_pending(काष्ठा kvm_vcpu *vcpu);
बाह्य काष्ठा kvm_device_ops kvm_flic_ops;
पूर्णांक kvm_s390_is_stop_irq_pending(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_clear_stop_irq(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_set_irq_state(काष्ठा kvm_vcpu *vcpu,
			   व्योम __user *buf, पूर्णांक len);
पूर्णांक kvm_s390_get_irq_state(काष्ठा kvm_vcpu *vcpu,
			   __u8 __user *buf, पूर्णांक len);
व्योम kvm_s390_gisa_init(काष्ठा kvm *kvm);
व्योम kvm_s390_gisa_clear(काष्ठा kvm *kvm);
व्योम kvm_s390_gisa_destroy(काष्ठा kvm *kvm);
पूर्णांक kvm_s390_gib_init(u8 nisc);
व्योम kvm_s390_gib_destroy(व्योम);

/* implemented in guestdbg.c */
व्योम kvm_s390_backup_guest_per_regs(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_restore_guest_per_regs(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_patch_guest_per_regs(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_import_bp_data(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_guest_debug *dbg);
व्योम kvm_s390_clear_bp_data(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_s390_prepare_debug_निकास(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_per_अगरetch_icpt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_handle_per_event(काष्ठा kvm_vcpu *vcpu);

/* support क्रम Basic/Extended SCA handling */
अटल अंतरभूत जोड़ ipte_control *kvm_s390_get_ipte_control(काष्ठा kvm *kvm)
अणु
	काष्ठा bsca_block *sca = kvm->arch.sca; /* SCA version करोesn't matter */

	वापस &sca->ipte_control;
पूर्ण
अटल अंतरभूत पूर्णांक kvm_s390_use_sca_entries(व्योम)
अणु
	/*
	 * Without SIGP पूर्णांकerpretation, only SRS पूर्णांकerpretation (अगर available)
	 * might use the entries. By not setting the entries and keeping them
	 * invalid, hardware will not access them but पूर्णांकercept.
	 */
	वापस sclp.has_sigpअगर;
पूर्ण
व्योम kvm_s390_reinject_machine_check(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा mcck_अस्थिर_info *mcck_info);

/**
 * kvm_s390_vcpu_crypto_reset_all
 *
 * Reset the crypto attributes क्रम each vcpu. This can be करोne जबतक the vcpus
 * are running as each vcpu will be हटाओd from SIE beक्रमe resetting the crypt
 * attributes and restored to SIE afterward.
 *
 * Note: The kvm->lock must be held जबतक calling this function
 *
 * @kvm: the KVM guest
 */
व्योम kvm_s390_vcpu_crypto_reset_all(काष्ठा kvm *kvm);

/**
 * diag9c_क्रमwarding_hz
 *
 * Set the maximum number of diag9c क्रमwarding per second
 */
बाह्य अचिन्हित पूर्णांक diag9c_क्रमwarding_hz;

#पूर्ण_अगर
