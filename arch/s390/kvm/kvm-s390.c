<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hosting IBM Z kernel भव machines (s390x)
 *
 * Copyright IBM Corp. 2008, 2020
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 *               Heiko Carstens <heiko.carstens@de.ibm.com>
 *               Christian Ehrhardt <ehrhardt@de.ibm.com>
 *               Jason J. Herne <jjherne@us.ibm.com>
 */

#घोषणा KMSG_COMPONENT "kvm-s390"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/compiler.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/init.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/mman.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/stp.h>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/cpacf.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/ap.h>
#समावेश <यंत्र/uv.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश "kvm-s390.h"
#समावेश "gaccess.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"
#समावेश "trace-s390.h"

#घोषणा MEM_OP_MAX_SIZE 65536	/* Maximum transfer size क्रम KVM_S390_MEM_OP */
#घोषणा LOCAL_IRQS 32
#घोषणा VCPU_IRQS_MAX_BUF (माप(काष्ठा kvm_s390_irq) * \
			   (KVM_MAX_VCPUS + LOCAL_IRQS))

काष्ठा kvm_stats_debugfs_item debugfs_entries[] = अणु
	VCPU_STAT("userspace_handled", निकास_userspace),
	VCPU_STAT("exit_null", निकास_null),
	VCPU_STAT("pfault_sync", pfault_sync),
	VCPU_STAT("exit_validity", निकास_validity),
	VCPU_STAT("exit_stop_request", निकास_stop_request),
	VCPU_STAT("exit_external_request", निकास_बाह्यal_request),
	VCPU_STAT("exit_io_request", निकास_io_request),
	VCPU_STAT("exit_external_interrupt", निकास_बाह्यal_पूर्णांकerrupt),
	VCPU_STAT("exit_instruction", निकास_inकाष्ठाion),
	VCPU_STAT("exit_pei", निकास_pei),
	VCPU_STAT("exit_program_interruption", निकास_program_पूर्णांकerruption),
	VCPU_STAT("exit_instr_and_program_int", निकास_instr_and_program),
	VCPU_STAT("exit_operation_exception", निकास_operation_exception),
	VCPU_STAT("halt_successful_poll", halt_successful_poll),
	VCPU_STAT("halt_attempted_poll", halt_attempted_poll),
	VCPU_STAT("halt_poll_invalid", halt_poll_invalid),
	VCPU_STAT("halt_no_poll_steal", halt_no_poll_steal),
	VCPU_STAT("halt_wakeup", halt_wakeup),
	VCPU_STAT("halt_poll_success_ns", halt_poll_success_ns),
	VCPU_STAT("halt_poll_fail_ns", halt_poll_fail_ns),
	VCPU_STAT("instruction_lctlg", inकाष्ठाion_lctlg),
	VCPU_STAT("instruction_lctl", inकाष्ठाion_lctl),
	VCPU_STAT("instruction_stctl", inकाष्ठाion_stctl),
	VCPU_STAT("instruction_stctg", inकाष्ठाion_stctg),
	VCPU_STAT("deliver_ckc", deliver_ckc),
	VCPU_STAT("deliver_cputm", deliver_cpuपंचांग),
	VCPU_STAT("deliver_emergency_signal", deliver_emergency_संकेत),
	VCPU_STAT("deliver_external_call", deliver_बाह्यal_call),
	VCPU_STAT("deliver_service_signal", deliver_service_संकेत),
	VCPU_STAT("deliver_virtio", deliver_virtio),
	VCPU_STAT("deliver_stop_signal", deliver_stop_संकेत),
	VCPU_STAT("deliver_prefix_signal", deliver_prefix_संकेत),
	VCPU_STAT("deliver_restart_signal", deliver_restart_संकेत),
	VCPU_STAT("deliver_program", deliver_program),
	VCPU_STAT("deliver_io", deliver_io),
	VCPU_STAT("deliver_machine_check", deliver_machine_check),
	VCPU_STAT("exit_wait_state", निकास_रुको_state),
	VCPU_STAT("inject_ckc", inject_ckc),
	VCPU_STAT("inject_cputm", inject_cpuपंचांग),
	VCPU_STAT("inject_external_call", inject_बाह्यal_call),
	VM_STAT("inject_float_mchk", inject_भग्न_mchk),
	VCPU_STAT("inject_emergency_signal", inject_emergency_संकेत),
	VM_STAT("inject_io", inject_io),
	VCPU_STAT("inject_mchk", inject_mchk),
	VM_STAT("inject_pfault_done", inject_pfault_करोne),
	VCPU_STAT("inject_program", inject_program),
	VCPU_STAT("inject_restart", inject_restart),
	VM_STAT("inject_service_signal", inject_service_संकेत),
	VCPU_STAT("inject_set_prefix", inject_set_prefix),
	VCPU_STAT("inject_stop_signal", inject_stop_संकेत),
	VCPU_STAT("inject_pfault_init", inject_pfault_init),
	VM_STAT("inject_virtio", inject_virtio),
	VCPU_STAT("instruction_epsw", inकाष्ठाion_epsw),
	VCPU_STAT("instruction_gs", inकाष्ठाion_gs),
	VCPU_STAT("instruction_io_other", inकाष्ठाion_io_other),
	VCPU_STAT("instruction_lpsw", inकाष्ठाion_lpsw),
	VCPU_STAT("instruction_lpswe", inकाष्ठाion_lpswe),
	VCPU_STAT("instruction_pfmf", inकाष्ठाion_pfmf),
	VCPU_STAT("instruction_ptff", inकाष्ठाion_ptff),
	VCPU_STAT("instruction_stidp", inकाष्ठाion_stidp),
	VCPU_STAT("instruction_sck", inकाष्ठाion_sck),
	VCPU_STAT("instruction_sckpf", inकाष्ठाion_sckpf),
	VCPU_STAT("instruction_spx", inकाष्ठाion_spx),
	VCPU_STAT("instruction_stpx", inकाष्ठाion_stpx),
	VCPU_STAT("instruction_stap", inकाष्ठाion_stap),
	VCPU_STAT("instruction_iske", inकाष्ठाion_iske),
	VCPU_STAT("instruction_ri", inकाष्ठाion_ri),
	VCPU_STAT("instruction_rrbe", inकाष्ठाion_rrbe),
	VCPU_STAT("instruction_sske", inकाष्ठाion_sske),
	VCPU_STAT("instruction_ipte_interlock", inकाष्ठाion_ipte_पूर्णांकerlock),
	VCPU_STAT("instruction_essa", inकाष्ठाion_essa),
	VCPU_STAT("instruction_stsi", inकाष्ठाion_stsi),
	VCPU_STAT("instruction_stfl", inकाष्ठाion_stfl),
	VCPU_STAT("instruction_tb", inकाष्ठाion_tb),
	VCPU_STAT("instruction_tpi", inकाष्ठाion_tpi),
	VCPU_STAT("instruction_tprot", inकाष्ठाion_tprot),
	VCPU_STAT("instruction_tsch", inकाष्ठाion_tsch),
	VCPU_STAT("instruction_sthyi", inकाष्ठाion_sthyi),
	VCPU_STAT("instruction_sie", inकाष्ठाion_sie),
	VCPU_STAT("instruction_sigp_sense", inकाष्ठाion_sigp_sense),
	VCPU_STAT("instruction_sigp_sense_running", inकाष्ठाion_sigp_sense_running),
	VCPU_STAT("instruction_sigp_external_call", inकाष्ठाion_sigp_बाह्यal_call),
	VCPU_STAT("instruction_sigp_emergency", inकाष्ठाion_sigp_emergency),
	VCPU_STAT("instruction_sigp_cond_emergency", inकाष्ठाion_sigp_cond_emergency),
	VCPU_STAT("instruction_sigp_start", inकाष्ठाion_sigp_start),
	VCPU_STAT("instruction_sigp_stop", inकाष्ठाion_sigp_stop),
	VCPU_STAT("instruction_sigp_stop_store_status", inकाष्ठाion_sigp_stop_store_status),
	VCPU_STAT("instruction_sigp_store_status", inकाष्ठाion_sigp_store_status),
	VCPU_STAT("instruction_sigp_store_adtl_status", inकाष्ठाion_sigp_store_adtl_status),
	VCPU_STAT("instruction_sigp_set_arch", inकाष्ठाion_sigp_arch),
	VCPU_STAT("instruction_sigp_set_prefix", inकाष्ठाion_sigp_prefix),
	VCPU_STAT("instruction_sigp_restart", inकाष्ठाion_sigp_restart),
	VCPU_STAT("instruction_sigp_cpu_reset", inकाष्ठाion_sigp_cpu_reset),
	VCPU_STAT("instruction_sigp_init_cpu_reset", inकाष्ठाion_sigp_init_cpu_reset),
	VCPU_STAT("instruction_sigp_unknown", inकाष्ठाion_sigp_unknown),
	VCPU_STAT("instruction_diag_10", diagnose_10),
	VCPU_STAT("instruction_diag_44", diagnose_44),
	VCPU_STAT("instruction_diag_9c", diagnose_9c),
	VCPU_STAT("diag_9c_ignored", diagnose_9c_ignored),
	VCPU_STAT("diag_9c_forward", diagnose_9c_क्रमward),
	VCPU_STAT("instruction_diag_258", diagnose_258),
	VCPU_STAT("instruction_diag_308", diagnose_308),
	VCPU_STAT("instruction_diag_500", diagnose_500),
	VCPU_STAT("instruction_diag_other", diagnose_other),
	अणु शून्य पूर्ण
पूर्ण;

/* allow nested भवization in KVM (अगर enabled by user space) */
अटल पूर्णांक nested;
module_param(nested, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(nested, "Nested virtualization support");

/* allow 1m huge page guest backing, अगर !nested */
अटल पूर्णांक hpage;
module_param(hpage, पूर्णांक, 0444);
MODULE_PARM_DESC(hpage, "1m huge page backing support");

/* maximum percentage of steal समय क्रम polling.  >100 is treated like 100 */
अटल u8 halt_poll_max_steal = 10;
module_param(halt_poll_max_steal, byte, 0644);
MODULE_PARM_DESC(halt_poll_max_steal, "Maximum percentage of steal time to allow polling");

/* अगर set to true, the GISA will be initialized and used अगर available */
अटल bool use_gisa  = true;
module_param(use_gisa, bool, 0644);
MODULE_PARM_DESC(use_gisa, "Use the GISA if the host supports it.");

/* maximum diag9c क्रमwarding per second */
अचिन्हित पूर्णांक diag9c_क्रमwarding_hz;
module_param(diag9c_क्रमwarding_hz, uपूर्णांक, 0644);
MODULE_PARM_DESC(diag9c_क्रमwarding_hz, "Maximum diag9c forwarding per second, 0 to turn off");

/*
 * For now we handle at most 16 द्विगुन words as this is what the s390 base
 * kernel handles and stores in the prefix page. If we ever need to go beyond
 * this, this requires changes to code, but the बाह्यal uapi can stay.
 */
#घोषणा SIZE_INTERNAL 16

/*
 * Base feature mask that defines शेष mask क्रम facilities. Consists of the
 * defines in FACILITIES_KVM and the non-hypervisor managed bits.
 */
अटल अचिन्हित दीर्घ kvm_s390_fac_base[SIZE_INTERNAL] = अणु FACILITIES_KVM पूर्ण;
/*
 * Extended feature mask. Consists of the defines in FACILITIES_KVM_CPUMODEL
 * and defines the facilities that can be enabled via a cpu model.
 */
अटल अचिन्हित दीर्घ kvm_s390_fac_ext[SIZE_INTERNAL] = अणु FACILITIES_KVM_CPUMODEL पूर्ण;

अटल अचिन्हित दीर्घ kvm_s390_fac_size(व्योम)
अणु
	BUILD_BUG_ON(SIZE_INTERNAL > S390_ARCH_FAC_MASK_SIZE_U64);
	BUILD_BUG_ON(SIZE_INTERNAL > S390_ARCH_FAC_LIST_SIZE_U64);
	BUILD_BUG_ON(SIZE_INTERNAL * माप(अचिन्हित दीर्घ) >
		माप(S390_lowcore.stfle_fac_list));

	वापस SIZE_INTERNAL;
पूर्ण

/* available cpu features supported by kvm */
अटल DECLARE_BITMAP(kvm_s390_available_cpu_feat, KVM_S390_VM_CPU_FEAT_NR_BITS);
/* available subfunctions indicated via query / "test bit" */
अटल काष्ठा kvm_s390_vm_cpu_subfunc kvm_s390_available_subfunc;

अटल काष्ठा gmap_notअगरier gmap_notअगरier;
अटल काष्ठा gmap_notअगरier vsie_gmap_notअगरier;
debug_info_t *kvm_s390_dbf;
debug_info_t *kvm_s390_dbf_uv;

/* Section: not file related */
पूर्णांक kvm_arch_hardware_enable(व्योम)
अणु
	/* every s390 is भवization enabled ;-) */
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_check_processor_compat(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

/* क्रमward declarations */
अटल व्योम kvm_gmap_notअगरier(काष्ठा gmap *gmap, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ end);
अटल पूर्णांक sca_चयन_to_extended(काष्ठा kvm *kvm);

अटल व्योम kvm_घड़ी_sync_scb(काष्ठा kvm_s390_sie_block *scb, u64 delta)
अणु
	u8 delta_idx = 0;

	/*
	 * The TOD jumps by delta, we have to compensate this by adding
	 * -delta to the epoch.
	 */
	delta = -delta;

	/* sign-extension - we're adding to चिन्हित values below */
	अगर ((s64)delta < 0)
		delta_idx = -1;

	scb->epoch += delta;
	अगर (scb->ecd & ECD_MEF) अणु
		scb->epdx += delta_idx;
		अगर (scb->epoch < delta)
			scb->epdx += 1;
	पूर्ण
पूर्ण

/*
 * This callback is executed during stop_machine(). All CPUs are thereक्रमe
 * temporarily stopped. In order not to change guest behavior, we have to
 * disable preemption whenever we touch the epoch of kvm and the VCPUs,
 * so a CPU won't be stopped जबतक calculating with the epoch.
 */
अटल पूर्णांक kvm_घड़ी_sync(काष्ठा notअगरier_block *notअगरier, अचिन्हित दीर्घ val,
			  व्योम *v)
अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ *delta = v;

	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			kvm_घड़ी_sync_scb(vcpu->arch.sie_block, *delta);
			अगर (i == 0) अणु
				kvm->arch.epoch = vcpu->arch.sie_block->epoch;
				kvm->arch.epdx = vcpu->arch.sie_block->epdx;
			पूर्ण
			अगर (vcpu->arch.cpuपंचांग_enabled)
				vcpu->arch.cpuपंचांग_start += *delta;
			अगर (vcpu->arch.vsie_block)
				kvm_घड़ी_sync_scb(vcpu->arch.vsie_block,
						   *delta);
		पूर्ण
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block kvm_घड़ी_notअगरier = अणु
	.notअगरier_call = kvm_घड़ी_sync,
पूर्ण;

पूर्णांक kvm_arch_hardware_setup(व्योम *opaque)
अणु
	gmap_notअगरier.notअगरier_call = kvm_gmap_notअगरier;
	gmap_रेजिस्टर_pte_notअगरier(&gmap_notअगरier);
	vsie_gmap_notअगरier.notअगरier_call = kvm_s390_vsie_gmap_notअगरier;
	gmap_रेजिस्टर_pte_notअगरier(&vsie_gmap_notअगरier);
	atomic_notअगरier_chain_रेजिस्टर(&s390_epoch_delta_notअगरier,
				       &kvm_घड़ी_notअगरier);
	वापस 0;
पूर्ण

व्योम kvm_arch_hardware_unsetup(व्योम)
अणु
	gmap_unरेजिस्टर_pte_notअगरier(&gmap_notअगरier);
	gmap_unरेजिस्टर_pte_notअगरier(&vsie_gmap_notअगरier);
	atomic_notअगरier_chain_unरेजिस्टर(&s390_epoch_delta_notअगरier,
					 &kvm_घड़ी_notअगरier);
पूर्ण

अटल व्योम allow_cpu_feat(अचिन्हित दीर्घ nr)
अणु
	set_bit_inv(nr, kvm_s390_available_cpu_feat);
पूर्ण

अटल अंतरभूत पूर्णांक plo_test_bit(अचिन्हित अक्षर nr)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) nr | 0x100;
	पूर्णांक cc;

	यंत्र अस्थिर(
		/* Parameter रेजिस्टरs are ignored क्रम "test bit" */
		"	plo	0,0,0,0(0)\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc)
		: "d" (r0)
		: "cc");
	वापस cc == 0;
पूर्ण

अटल __always_अंतरभूत व्योम __insn32_query(अचिन्हित पूर्णांक opcode, u8 *query)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = 0;	/* query function */
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) query;

	यंत्र अस्थिर(
		/* Parameter regs are ignored */
		"	.insn	rrf,%[opc] << 16,2,4,6,0\n"
		:
		: "d" (r0), "a" (r1), [opc] "i" (opcode)
		: "cc", "memory");
पूर्ण

#घोषणा INSN_SORTL 0xb938
#घोषणा INSN_DFLTCC 0xb939

अटल व्योम kvm_s390_cpu_feat_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 256; ++i) अणु
		अगर (plo_test_bit(i))
			kvm_s390_available_subfunc.plo[i >> 3] |= 0x80 >> (i & 7);
	पूर्ण

	अगर (test_facility(28)) /* TOD-घड़ी steering */
		ptff(kvm_s390_available_subfunc.ptff,
		     माप(kvm_s390_available_subfunc.ptff),
		     PTFF_QAF);

	अगर (test_facility(17)) अणु /* MSA */
		__cpacf_query(CPACF_KMAC, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kmac);
		__cpacf_query(CPACF_KMC, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kmc);
		__cpacf_query(CPACF_KM, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.km);
		__cpacf_query(CPACF_KIMD, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kimd);
		__cpacf_query(CPACF_KLMD, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.klmd);
	पूर्ण
	अगर (test_facility(76)) /* MSA3 */
		__cpacf_query(CPACF_PCKMO, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.pckmo);
	अगर (test_facility(77)) अणु /* MSA4 */
		__cpacf_query(CPACF_KMCTR, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kmctr);
		__cpacf_query(CPACF_KMF, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kmf);
		__cpacf_query(CPACF_KMO, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kmo);
		__cpacf_query(CPACF_PCC, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.pcc);
	पूर्ण
	अगर (test_facility(57)) /* MSA5 */
		__cpacf_query(CPACF_PRNO, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.ppno);

	अगर (test_facility(146)) /* MSA8 */
		__cpacf_query(CPACF_KMA, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kma);

	अगर (test_facility(155)) /* MSA9 */
		__cpacf_query(CPACF_KDSA, (cpacf_mask_t *)
			      kvm_s390_available_subfunc.kdsa);

	अगर (test_facility(150)) /* SORTL */
		__insn32_query(INSN_SORTL, kvm_s390_available_subfunc.sortl);

	अगर (test_facility(151)) /* DFLTCC */
		__insn32_query(INSN_DFLTCC, kvm_s390_available_subfunc.dfltcc);

	अगर (MACHINE_HAS_ESOP)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_ESOP);
	/*
	 * We need SIE support, ESOP (PROT_READ protection क्रम gmap_shaकरोw),
	 * 64bit SCAO (SCA passthrough) and IDTE (क्रम gmap_shaकरोw unshaकरोwing).
	 */
	अगर (!sclp.has_sief2 || !MACHINE_HAS_ESOP || !sclp.has_64bscao ||
	    !test_facility(3) || !nested)
		वापस;
	allow_cpu_feat(KVM_S390_VM_CPU_FEAT_SIEF2);
	अगर (sclp.has_64bscao)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_64BSCAO);
	अगर (sclp.has_siअगर)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_SIIF);
	अगर (sclp.has_gpere)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_GPERE);
	अगर (sclp.has_gsls)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_GSLS);
	अगर (sclp.has_ib)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_IB);
	अगर (sclp.has_cei)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_CEI);
	अगर (sclp.has_ibs)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_IBS);
	अगर (sclp.has_kss)
		allow_cpu_feat(KVM_S390_VM_CPU_FEAT_KSS);
	/*
	 * KVM_S390_VM_CPU_FEAT_SKEY: Wrong shaकरोw of PTE.I bits will make
	 * all skey handling functions पढ़ो/set the skey from the PGSTE
	 * instead of the real storage key.
	 *
	 * KVM_S390_VM_CPU_FEAT_CMMA: Wrong shaकरोw of PTE.I bits will make
	 * pages being detected as preserved although they are resident.
	 *
	 * KVM_S390_VM_CPU_FEAT_PFMFI: Wrong shaकरोw of PTE.I bits will
	 * have the same effect as क्रम KVM_S390_VM_CPU_FEAT_SKEY.
	 *
	 * For KVM_S390_VM_CPU_FEAT_SKEY, KVM_S390_VM_CPU_FEAT_CMMA and
	 * KVM_S390_VM_CPU_FEAT_PFMFI, all PTE.I and PGSTE bits have to be
	 * correctly shaकरोwed. We can करो that क्रम the PGSTE but not क्रम PTE.I.
	 *
	 * KVM_S390_VM_CPU_FEAT_SIGPIF: Wrong SCB addresses in the SCA. We
	 * cannot easily shaकरोw the SCA because of the ipte lock.
	 */
पूर्ण

पूर्णांक kvm_arch_init(व्योम *opaque)
अणु
	पूर्णांक rc = -ENOMEM;

	kvm_s390_dbf = debug_रेजिस्टर("kvm-trace", 32, 1, 7 * माप(दीर्घ));
	अगर (!kvm_s390_dbf)
		वापस -ENOMEM;

	kvm_s390_dbf_uv = debug_रेजिस्टर("kvm-uv", 32, 1, 7 * माप(दीर्घ));
	अगर (!kvm_s390_dbf_uv)
		जाओ out;

	अगर (debug_रेजिस्टर_view(kvm_s390_dbf, &debug_प्र_लिखो_view) ||
	    debug_रेजिस्टर_view(kvm_s390_dbf_uv, &debug_प्र_लिखो_view))
		जाओ out;

	kvm_s390_cpu_feat_init();

	/* Register भग्नing पूर्णांकerrupt controller पूर्णांकerface. */
	rc = kvm_रेजिस्टर_device_ops(&kvm_flic_ops, KVM_DEV_TYPE_FLIC);
	अगर (rc) अणु
		pr_err("A FLIC registration call failed with rc=%d\n", rc);
		जाओ out;
	पूर्ण

	rc = kvm_s390_gib_init(GAL_ISC);
	अगर (rc)
		जाओ out;

	वापस 0;

out:
	kvm_arch_निकास();
	वापस rc;
पूर्ण

व्योम kvm_arch_निकास(व्योम)
अणु
	kvm_s390_gib_destroy();
	debug_unरेजिस्टर(kvm_s390_dbf);
	debug_unरेजिस्टर(kvm_s390_dbf_uv);
पूर्ण

/* Section: device related */
दीर्घ kvm_arch_dev_ioctl(काष्ठा file *filp,
			अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	अगर (ioctl == KVM_S390_ENABLE_SIE)
		वापस s390_enable_sie();
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_vm_ioctl_check_extension(काष्ठा kvm *kvm, दीर्घ ext)
अणु
	पूर्णांक r;

	चयन (ext) अणु
	हाल KVM_CAP_S390_PSW:
	हाल KVM_CAP_S390_GMAP:
	हाल KVM_CAP_SYNC_MMU:
#अगर_घोषित CONFIG_KVM_S390_UCONTROL
	हाल KVM_CAP_S390_UCONTROL:
#पूर्ण_अगर
	हाल KVM_CAP_ASYNC_PF:
	हाल KVM_CAP_SYNC_REGS:
	हाल KVM_CAP_ONE_REG:
	हाल KVM_CAP_ENABLE_CAP:
	हाल KVM_CAP_S390_CSS_SUPPORT:
	हाल KVM_CAP_IOEVENTFD:
	हाल KVM_CAP_DEVICE_CTRL:
	हाल KVM_CAP_S390_IRQCHIP:
	हाल KVM_CAP_VM_ATTRIBUTES:
	हाल KVM_CAP_MP_STATE:
	हाल KVM_CAP_IMMEDIATE_EXIT:
	हाल KVM_CAP_S390_INJECT_IRQ:
	हाल KVM_CAP_S390_USER_SIGP:
	हाल KVM_CAP_S390_USER_STSI:
	हाल KVM_CAP_S390_SKEYS:
	हाल KVM_CAP_S390_IRQ_STATE:
	हाल KVM_CAP_S390_USER_INSTR0:
	हाल KVM_CAP_S390_CMMA_MIGRATION:
	हाल KVM_CAP_S390_AIS:
	हाल KVM_CAP_S390_AIS_MIGRATION:
	हाल KVM_CAP_S390_VCPU_RESETS:
	हाल KVM_CAP_SET_GUEST_DEBUG:
	हाल KVM_CAP_S390_DIAG318:
		r = 1;
		अवरोध;
	हाल KVM_CAP_SET_GUEST_DEBUG2:
		r = KVM_GUESTDBG_VALID_MASK;
		अवरोध;
	हाल KVM_CAP_S390_HPAGE_1M:
		r = 0;
		अगर (hpage && !kvm_is_ucontrol(kvm))
			r = 1;
		अवरोध;
	हाल KVM_CAP_S390_MEM_OP:
		r = MEM_OP_MAX_SIZE;
		अवरोध;
	हाल KVM_CAP_NR_VCPUS:
	हाल KVM_CAP_MAX_VCPUS:
	हाल KVM_CAP_MAX_VCPU_ID:
		r = KVM_S390_BSCA_CPU_SLOTS;
		अगर (!kvm_s390_use_sca_entries())
			r = KVM_MAX_VCPUS;
		अन्यथा अगर (sclp.has_esca && sclp.has_64bscao)
			r = KVM_S390_ESCA_CPU_SLOTS;
		अवरोध;
	हाल KVM_CAP_S390_COW:
		r = MACHINE_HAS_ESOP;
		अवरोध;
	हाल KVM_CAP_S390_VECTOR_REGISTERS:
		r = MACHINE_HAS_VX;
		अवरोध;
	हाल KVM_CAP_S390_RI:
		r = test_facility(64);
		अवरोध;
	हाल KVM_CAP_S390_GS:
		r = test_facility(133);
		अवरोध;
	हाल KVM_CAP_S390_BPB:
		r = test_facility(82);
		अवरोध;
	हाल KVM_CAP_S390_PROTECTED:
		r = is_prot_virt_host();
		अवरोध;
	शेष:
		r = 0;
	पूर्ण
	वापस r;
पूर्ण

व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु
	पूर्णांक i;
	gfn_t cur_gfn, last_gfn;
	अचिन्हित दीर्घ gaddr, vmaddr;
	काष्ठा gmap *gmap = kvm->arch.gmap;
	DECLARE_BITMAP(biपंचांगap, _PAGE_ENTRIES);

	/* Loop over all guest segments */
	cur_gfn = memslot->base_gfn;
	last_gfn = memslot->base_gfn + memslot->npages;
	क्रम (; cur_gfn <= last_gfn; cur_gfn += _PAGE_ENTRIES) अणु
		gaddr = gfn_to_gpa(cur_gfn);
		vmaddr = gfn_to_hva_memslot(memslot, cur_gfn);
		अगर (kvm_is_error_hva(vmaddr))
			जारी;

		biपंचांगap_zero(biपंचांगap, _PAGE_ENTRIES);
		gmap_sync_dirty_log_pmd(gmap, biपंचांगap, gaddr, vmaddr);
		क्रम (i = 0; i < _PAGE_ENTRIES; i++) अणु
			अगर (test_bit(i, biपंचांगap))
				mark_page_dirty(kvm, cur_gfn + i);
		पूर्ण

		अगर (fatal_संकेत_pending(current))
			वापस;
		cond_resched();
	पूर्ण
पूर्ण

/* Section: vm related */
अटल व्योम sca_del_vcpu(काष्ठा kvm_vcpu *vcpu);

/*
 * Get (and clear) the dirty memory log क्रम a memory slot.
 */
पूर्णांक kvm_vm_ioctl_get_dirty_log(काष्ठा kvm *kvm,
			       काष्ठा kvm_dirty_log *log)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ n;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक is_dirty;

	अगर (kvm_is_ucontrol(kvm))
		वापस -EINVAL;

	mutex_lock(&kvm->slots_lock);

	r = -EINVAL;
	अगर (log->slot >= KVM_USER_MEM_SLOTS)
		जाओ out;

	r = kvm_get_dirty_log(kvm, log, &is_dirty, &memslot);
	अगर (r)
		जाओ out;

	/* Clear the dirty log */
	अगर (is_dirty) अणु
		n = kvm_dirty_biपंचांगap_bytes(memslot);
		स_रखो(memslot->dirty_biपंचांगap, 0, n);
	पूर्ण
	r = 0;
out:
	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण

अटल व्योम icpt_operexc_on_all_vcpus(काष्ठा kvm *kvm)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		kvm_s390_sync_request(KVM_REQ_ICPT_OPEREXC, vcpu);
	पूर्ण
पूर्ण

पूर्णांक kvm_vm_ioctl_enable_cap(काष्ठा kvm *kvm, काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_S390_IRQCHIP:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_IRQCHIP");
		kvm->arch.use_irqchip = 1;
		r = 0;
		अवरोध;
	हाल KVM_CAP_S390_USER_SIGP:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_USER_SIGP");
		kvm->arch.user_sigp = 1;
		r = 0;
		अवरोध;
	हाल KVM_CAP_S390_VECTOR_REGISTERS:
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus) अणु
			r = -EBUSY;
		पूर्ण अन्यथा अगर (MACHINE_HAS_VX) अणु
			set_kvm_facility(kvm->arch.model.fac_mask, 129);
			set_kvm_facility(kvm->arch.model.fac_list, 129);
			अगर (test_facility(134)) अणु
				set_kvm_facility(kvm->arch.model.fac_mask, 134);
				set_kvm_facility(kvm->arch.model.fac_list, 134);
			पूर्ण
			अगर (test_facility(135)) अणु
				set_kvm_facility(kvm->arch.model.fac_mask, 135);
				set_kvm_facility(kvm->arch.model.fac_list, 135);
			पूर्ण
			अगर (test_facility(148)) अणु
				set_kvm_facility(kvm->arch.model.fac_mask, 148);
				set_kvm_facility(kvm->arch.model.fac_list, 148);
			पूर्ण
			अगर (test_facility(152)) अणु
				set_kvm_facility(kvm->arch.model.fac_mask, 152);
				set_kvm_facility(kvm->arch.model.fac_list, 152);
			पूर्ण
			r = 0;
		पूर्ण अन्यथा
			r = -EINVAL;
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_VECTOR_REGISTERS %s",
			 r ? "(not available)" : "(success)");
		अवरोध;
	हाल KVM_CAP_S390_RI:
		r = -EINVAL;
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus) अणु
			r = -EBUSY;
		पूर्ण अन्यथा अगर (test_facility(64)) अणु
			set_kvm_facility(kvm->arch.model.fac_mask, 64);
			set_kvm_facility(kvm->arch.model.fac_list, 64);
			r = 0;
		पूर्ण
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_RI %s",
			 r ? "(not available)" : "(success)");
		अवरोध;
	हाल KVM_CAP_S390_AIS:
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus) अणु
			r = -EBUSY;
		पूर्ण अन्यथा अणु
			set_kvm_facility(kvm->arch.model.fac_mask, 72);
			set_kvm_facility(kvm->arch.model.fac_list, 72);
			r = 0;
		पूर्ण
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: AIS %s",
			 r ? "(not available)" : "(success)");
		अवरोध;
	हाल KVM_CAP_S390_GS:
		r = -EINVAL;
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus) अणु
			r = -EBUSY;
		पूर्ण अन्यथा अगर (test_facility(133)) अणु
			set_kvm_facility(kvm->arch.model.fac_mask, 133);
			set_kvm_facility(kvm->arch.model.fac_list, 133);
			r = 0;
		पूर्ण
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_GS %s",
			 r ? "(not available)" : "(success)");
		अवरोध;
	हाल KVM_CAP_S390_HPAGE_1M:
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus)
			r = -EBUSY;
		अन्यथा अगर (!hpage || kvm->arch.use_cmma || kvm_is_ucontrol(kvm))
			r = -EINVAL;
		अन्यथा अणु
			r = 0;
			mmap_ग_लिखो_lock(kvm->mm);
			kvm->mm->context.allow_gmap_hpage_1m = 1;
			mmap_ग_लिखो_unlock(kvm->mm);
			/*
			 * We might have to create fake 4k page
			 * tables. To aव्योम that the hardware works on
			 * stale PGSTEs, we emulate these inकाष्ठाions.
			 */
			kvm->arch.use_skf = 0;
			kvm->arch.use_pfmfi = 0;
		पूर्ण
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_HPAGE %s",
			 r ? "(not available)" : "(success)");
		अवरोध;
	हाल KVM_CAP_S390_USER_STSI:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_USER_STSI");
		kvm->arch.user_stsi = 1;
		r = 0;
		अवरोध;
	हाल KVM_CAP_S390_USER_INSTR0:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_USER_INSTR0");
		kvm->arch.user_instr0 = 1;
		icpt_operexc_on_all_vcpus(kvm);
		r = 0;
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक kvm_s390_get_mem_control(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->attr) अणु
	हाल KVM_S390_VM_MEM_LIMIT_SIZE:
		ret = 0;
		VM_EVENT(kvm, 3, "QUERY: max guest memory: %lu bytes",
			 kvm->arch.mem_limit);
		अगर (put_user(kvm->arch.mem_limit, (u64 __user *)attr->addr))
			ret = -EFAULT;
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_set_mem_control(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक idx;
	चयन (attr->attr) अणु
	हाल KVM_S390_VM_MEM_ENABLE_CMMA:
		ret = -ENXIO;
		अगर (!sclp.has_cmma)
			अवरोध;

		VM_EVENT(kvm, 3, "%s", "ENABLE: CMMA support");
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus)
			ret = -EBUSY;
		अन्यथा अगर (kvm->mm->context.allow_gmap_hpage_1m)
			ret = -EINVAL;
		अन्यथा अणु
			kvm->arch.use_cmma = 1;
			/* Not compatible with cmma. */
			kvm->arch.use_pfmfi = 0;
			ret = 0;
		पूर्ण
		mutex_unlock(&kvm->lock);
		अवरोध;
	हाल KVM_S390_VM_MEM_CLR_CMMA:
		ret = -ENXIO;
		अगर (!sclp.has_cmma)
			अवरोध;
		ret = -EINVAL;
		अगर (!kvm->arch.use_cmma)
			अवरोध;

		VM_EVENT(kvm, 3, "%s", "RESET: CMMA states");
		mutex_lock(&kvm->lock);
		idx = srcu_पढ़ो_lock(&kvm->srcu);
		s390_reset_cmma(kvm->arch.gmap->mm);
		srcu_पढ़ो_unlock(&kvm->srcu, idx);
		mutex_unlock(&kvm->lock);
		ret = 0;
		अवरोध;
	हाल KVM_S390_VM_MEM_LIMIT_SIZE: अणु
		अचिन्हित दीर्घ new_limit;

		अगर (kvm_is_ucontrol(kvm))
			वापस -EINVAL;

		अगर (get_user(new_limit, (u64 __user *)attr->addr))
			वापस -EFAULT;

		अगर (kvm->arch.mem_limit != KVM_S390_NO_MEM_LIMIT &&
		    new_limit > kvm->arch.mem_limit)
			वापस -E2BIG;

		अगर (!new_limit)
			वापस -EINVAL;

		/* gmap_create takes last usable address */
		अगर (new_limit != KVM_S390_NO_MEM_LIMIT)
			new_limit -= 1;

		ret = -EBUSY;
		mutex_lock(&kvm->lock);
		अगर (!kvm->created_vcpus) अणु
			/* gmap_create will round the limit up */
			काष्ठा gmap *new = gmap_create(current->mm, new_limit);

			अगर (!new) अणु
				ret = -ENOMEM;
			पूर्ण अन्यथा अणु
				gmap_हटाओ(kvm->arch.gmap);
				new->निजी = kvm;
				kvm->arch.gmap = new;
				ret = 0;
			पूर्ण
		पूर्ण
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "SET: max guest address: %lu", new_limit);
		VM_EVENT(kvm, 3, "New guest asce: 0x%pK",
			 (व्योम *) kvm->arch.gmap->asce);
		अवरोध;
	पूर्ण
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम kvm_s390_vcpu_crypto_setup(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_s390_vcpu_crypto_reset_all(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	kvm_s390_vcpu_block_all(kvm);

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		kvm_s390_vcpu_crypto_setup(vcpu);
		/* recreate the shaकरोw crycb by leaving the VSIE handler */
		kvm_s390_sync_request(KVM_REQ_VSIE_RESTART, vcpu);
	पूर्ण

	kvm_s390_vcpu_unblock_all(kvm);
पूर्ण

अटल पूर्णांक kvm_s390_vm_set_crypto(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	mutex_lock(&kvm->lock);
	चयन (attr->attr) अणु
	हाल KVM_S390_VM_CRYPTO_ENABLE_AES_KW:
		अगर (!test_kvm_facility(kvm, 76)) अणु
			mutex_unlock(&kvm->lock);
			वापस -EINVAL;
		पूर्ण
		get_अक्रमom_bytes(
			kvm->arch.crypto.crycb->aes_wrapping_key_mask,
			माप(kvm->arch.crypto.crycb->aes_wrapping_key_mask));
		kvm->arch.crypto.aes_kw = 1;
		VM_EVENT(kvm, 3, "%s", "ENABLE: AES keywrapping support");
		अवरोध;
	हाल KVM_S390_VM_CRYPTO_ENABLE_DEA_KW:
		अगर (!test_kvm_facility(kvm, 76)) अणु
			mutex_unlock(&kvm->lock);
			वापस -EINVAL;
		पूर्ण
		get_अक्रमom_bytes(
			kvm->arch.crypto.crycb->dea_wrapping_key_mask,
			माप(kvm->arch.crypto.crycb->dea_wrapping_key_mask));
		kvm->arch.crypto.dea_kw = 1;
		VM_EVENT(kvm, 3, "%s", "ENABLE: DEA keywrapping support");
		अवरोध;
	हाल KVM_S390_VM_CRYPTO_DISABLE_AES_KW:
		अगर (!test_kvm_facility(kvm, 76)) अणु
			mutex_unlock(&kvm->lock);
			वापस -EINVAL;
		पूर्ण
		kvm->arch.crypto.aes_kw = 0;
		स_रखो(kvm->arch.crypto.crycb->aes_wrapping_key_mask, 0,
			माप(kvm->arch.crypto.crycb->aes_wrapping_key_mask));
		VM_EVENT(kvm, 3, "%s", "DISABLE: AES keywrapping support");
		अवरोध;
	हाल KVM_S390_VM_CRYPTO_DISABLE_DEA_KW:
		अगर (!test_kvm_facility(kvm, 76)) अणु
			mutex_unlock(&kvm->lock);
			वापस -EINVAL;
		पूर्ण
		kvm->arch.crypto.dea_kw = 0;
		स_रखो(kvm->arch.crypto.crycb->dea_wrapping_key_mask, 0,
			माप(kvm->arch.crypto.crycb->dea_wrapping_key_mask));
		VM_EVENT(kvm, 3, "%s", "DISABLE: DEA keywrapping support");
		अवरोध;
	हाल KVM_S390_VM_CRYPTO_ENABLE_APIE:
		अगर (!ap_inकाष्ठाions_available()) अणु
			mutex_unlock(&kvm->lock);
			वापस -EOPNOTSUPP;
		पूर्ण
		kvm->arch.crypto.apie = 1;
		अवरोध;
	हाल KVM_S390_VM_CRYPTO_DISABLE_APIE:
		अगर (!ap_inकाष्ठाions_available()) अणु
			mutex_unlock(&kvm->lock);
			वापस -EOPNOTSUPP;
		पूर्ण
		kvm->arch.crypto.apie = 0;
		अवरोध;
	शेष:
		mutex_unlock(&kvm->lock);
		वापस -ENXIO;
	पूर्ण

	kvm_s390_vcpu_crypto_reset_all(kvm);
	mutex_unlock(&kvm->lock);
	वापस 0;
पूर्ण

अटल व्योम kvm_s390_sync_request_broadcast(काष्ठा kvm *kvm, पूर्णांक req)
अणु
	पूर्णांक cx;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(cx, vcpu, kvm)
		kvm_s390_sync_request(req, vcpu);
पूर्ण

/*
 * Must be called with kvm->srcu held to aव्योम races on memslots, and with
 * kvm->slots_lock to aव्योम races with ourselves and kvm_s390_vm_stop_migration.
 */
अटल पूर्णांक kvm_s390_vm_start_migration(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_memory_slot *ms;
	काष्ठा kvm_memslots *slots;
	अचिन्हित दीर्घ ram_pages = 0;
	पूर्णांक slotnr;

	/* migration mode alपढ़ोy enabled */
	अगर (kvm->arch.migration_mode)
		वापस 0;
	slots = kvm_memslots(kvm);
	अगर (!slots || !slots->used_slots)
		वापस -EINVAL;

	अगर (!kvm->arch.use_cmma) अणु
		kvm->arch.migration_mode = 1;
		वापस 0;
	पूर्ण
	/* mark all the pages in active slots as dirty */
	क्रम (slotnr = 0; slotnr < slots->used_slots; slotnr++) अणु
		ms = slots->memslots + slotnr;
		अगर (!ms->dirty_biपंचांगap)
			वापस -EINVAL;
		/*
		 * The second half of the biपंचांगap is only used on x86,
		 * and would be wasted otherwise, so we put it to good
		 * use here to keep track of the state of the storage
		 * attributes.
		 */
		स_रखो(kvm_second_dirty_biपंचांगap(ms), 0xff, kvm_dirty_biपंचांगap_bytes(ms));
		ram_pages += ms->npages;
	पूर्ण
	atomic64_set(&kvm->arch.cmma_dirty_pages, ram_pages);
	kvm->arch.migration_mode = 1;
	kvm_s390_sync_request_broadcast(kvm, KVM_REQ_START_MIGRATION);
	वापस 0;
पूर्ण

/*
 * Must be called with kvm->slots_lock to aव्योम races with ourselves and
 * kvm_s390_vm_start_migration.
 */
अटल पूर्णांक kvm_s390_vm_stop_migration(काष्ठा kvm *kvm)
अणु
	/* migration mode alपढ़ोy disabled */
	अगर (!kvm->arch.migration_mode)
		वापस 0;
	kvm->arch.migration_mode = 0;
	अगर (kvm->arch.use_cmma)
		kvm_s390_sync_request_broadcast(kvm, KVM_REQ_STOP_MIGRATION);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_vm_set_migration(काष्ठा kvm *kvm,
				     काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक res = -ENXIO;

	mutex_lock(&kvm->slots_lock);
	चयन (attr->attr) अणु
	हाल KVM_S390_VM_MIGRATION_START:
		res = kvm_s390_vm_start_migration(kvm);
		अवरोध;
	हाल KVM_S390_VM_MIGRATION_STOP:
		res = kvm_s390_vm_stop_migration(kvm);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&kvm->slots_lock);

	वापस res;
पूर्ण

अटल पूर्णांक kvm_s390_vm_get_migration(काष्ठा kvm *kvm,
				     काष्ठा kvm_device_attr *attr)
अणु
	u64 mig = kvm->arch.migration_mode;

	अगर (attr->attr != KVM_S390_VM_MIGRATION_STATUS)
		वापस -ENXIO;

	अगर (copy_to_user((व्योम __user *)attr->addr, &mig, माप(mig)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_set_tod_ext(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_tod_घड़ी gtod;

	अगर (copy_from_user(&gtod, (व्योम __user *)attr->addr, माप(gtod)))
		वापस -EFAULT;

	अगर (!test_kvm_facility(kvm, 139) && gtod.epoch_idx)
		वापस -EINVAL;
	kvm_s390_set_tod_घड़ी(kvm, &gtod);

	VM_EVENT(kvm, 3, "SET: TOD extension: 0x%x, TOD base: 0x%llx",
		gtod.epoch_idx, gtod.tod);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_set_tod_high(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	u8 gtod_high;

	अगर (copy_from_user(&gtod_high, (व्योम __user *)attr->addr,
					   माप(gtod_high)))
		वापस -EFAULT;

	अगर (gtod_high != 0)
		वापस -EINVAL;
	VM_EVENT(kvm, 3, "SET: TOD extension: 0x%x", gtod_high);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_set_tod_low(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_tod_घड़ी gtod = अणु 0 पूर्ण;

	अगर (copy_from_user(&gtod.tod, (व्योम __user *)attr->addr,
			   माप(gtod.tod)))
		वापस -EFAULT;

	kvm_s390_set_tod_घड़ी(kvm, &gtod);
	VM_EVENT(kvm, 3, "SET: TOD base: 0x%llx", gtod.tod);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_set_tod(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	अगर (attr->flags)
		वापस -EINVAL;

	चयन (attr->attr) अणु
	हाल KVM_S390_VM_TOD_EXT:
		ret = kvm_s390_set_tod_ext(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_TOD_HIGH:
		ret = kvm_s390_set_tod_high(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_TOD_LOW:
		ret = kvm_s390_set_tod_low(kvm, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम kvm_s390_get_tod_घड़ी(काष्ठा kvm *kvm,
				   काष्ठा kvm_s390_vm_tod_घड़ी *gtod)
अणु
	जोड़ tod_घड़ी clk;

	preempt_disable();

	store_tod_घड़ी_ext(&clk);

	gtod->tod = clk.tod + kvm->arch.epoch;
	gtod->epoch_idx = 0;
	अगर (test_kvm_facility(kvm, 139)) अणु
		gtod->epoch_idx = clk.ei + kvm->arch.epdx;
		अगर (gtod->tod < clk.tod)
			gtod->epoch_idx += 1;
	पूर्ण

	preempt_enable();
पूर्ण

अटल पूर्णांक kvm_s390_get_tod_ext(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_tod_घड़ी gtod;

	स_रखो(&gtod, 0, माप(gtod));
	kvm_s390_get_tod_घड़ी(kvm, &gtod);
	अगर (copy_to_user((व्योम __user *)attr->addr, &gtod, माप(gtod)))
		वापस -EFAULT;

	VM_EVENT(kvm, 3, "QUERY: TOD extension: 0x%x, TOD base: 0x%llx",
		gtod.epoch_idx, gtod.tod);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_tod_high(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	u8 gtod_high = 0;

	अगर (copy_to_user((व्योम __user *)attr->addr, &gtod_high,
					 माप(gtod_high)))
		वापस -EFAULT;
	VM_EVENT(kvm, 3, "QUERY: TOD extension: 0x%x", gtod_high);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_tod_low(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	u64 gtod;

	gtod = kvm_s390_get_tod_घड़ी_fast(kvm);
	अगर (copy_to_user((व्योम __user *)attr->addr, &gtod, माप(gtod)))
		वापस -EFAULT;
	VM_EVENT(kvm, 3, "QUERY: TOD base: 0x%llx", gtod);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_tod(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	अगर (attr->flags)
		वापस -EINVAL;

	चयन (attr->attr) अणु
	हाल KVM_S390_VM_TOD_EXT:
		ret = kvm_s390_get_tod_ext(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_TOD_HIGH:
		ret = kvm_s390_get_tod_high(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_TOD_LOW:
		ret = kvm_s390_get_tod_low(kvm, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_set_processor(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_cpu_processor *proc;
	u16 lowest_ibc, unblocked_ibc;
	पूर्णांक ret = 0;

	mutex_lock(&kvm->lock);
	अगर (kvm->created_vcpus) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	proc = kzalloc(माप(*proc), GFP_KERNEL_ACCOUNT);
	अगर (!proc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (!copy_from_user(proc, (व्योम __user *)attr->addr,
			    माप(*proc))) अणु
		kvm->arch.model.cpuid = proc->cpuid;
		lowest_ibc = sclp.ibc >> 16 & 0xfff;
		unblocked_ibc = sclp.ibc & 0xfff;
		अगर (lowest_ibc && proc->ibc) अणु
			अगर (proc->ibc > unblocked_ibc)
				kvm->arch.model.ibc = unblocked_ibc;
			अन्यथा अगर (proc->ibc < lowest_ibc)
				kvm->arch.model.ibc = lowest_ibc;
			अन्यथा
				kvm->arch.model.ibc = proc->ibc;
		पूर्ण
		स_नकल(kvm->arch.model.fac_list, proc->fac_list,
		       S390_ARCH_FAC_LIST_SIZE_BYTE);
		VM_EVENT(kvm, 3, "SET: guest ibc: 0x%4.4x, guest cpuid: 0x%16.16llx",
			 kvm->arch.model.ibc,
			 kvm->arch.model.cpuid);
		VM_EVENT(kvm, 3, "SET: guest faclist: 0x%16.16llx.%16.16llx.%16.16llx",
			 kvm->arch.model.fac_list[0],
			 kvm->arch.model.fac_list[1],
			 kvm->arch.model.fac_list[2]);
	पूर्ण अन्यथा
		ret = -EFAULT;
	kमुक्त(proc);
out:
	mutex_unlock(&kvm->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_set_processor_feat(काष्ठा kvm *kvm,
				       काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_cpu_feat data;

	अगर (copy_from_user(&data, (व्योम __user *)attr->addr, माप(data)))
		वापस -EFAULT;
	अगर (!biपंचांगap_subset((अचिन्हित दीर्घ *) data.feat,
			   kvm_s390_available_cpu_feat,
			   KVM_S390_VM_CPU_FEAT_NR_BITS))
		वापस -EINVAL;

	mutex_lock(&kvm->lock);
	अगर (kvm->created_vcpus) अणु
		mutex_unlock(&kvm->lock);
		वापस -EBUSY;
	पूर्ण
	biपंचांगap_copy(kvm->arch.cpu_feat, (अचिन्हित दीर्घ *) data.feat,
		    KVM_S390_VM_CPU_FEAT_NR_BITS);
	mutex_unlock(&kvm->lock);
	VM_EVENT(kvm, 3, "SET: guest feat: 0x%16.16llx.0x%16.16llx.0x%16.16llx",
			 data.feat[0],
			 data.feat[1],
			 data.feat[2]);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_set_processor_subfunc(काष्ठा kvm *kvm,
					  काष्ठा kvm_device_attr *attr)
अणु
	mutex_lock(&kvm->lock);
	अगर (kvm->created_vcpus) अणु
		mutex_unlock(&kvm->lock);
		वापस -EBUSY;
	पूर्ण

	अगर (copy_from_user(&kvm->arch.model.subfuncs, (व्योम __user *)attr->addr,
			   माप(काष्ठा kvm_s390_vm_cpu_subfunc))) अणु
		mutex_unlock(&kvm->lock);
		वापस -EFAULT;
	पूर्ण
	mutex_unlock(&kvm->lock);

	VM_EVENT(kvm, 3, "SET: guest PLO    subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[1],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[2],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[3]);
	VM_EVENT(kvm, 3, "SET: guest PTFF   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ptff)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ptff)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMAC   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmac)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmac)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMC    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmc)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmc)[1]);
	VM_EVENT(kvm, 3, "SET: guest KM     subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.km)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.km)[1]);
	VM_EVENT(kvm, 3, "SET: guest KIMD   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kimd)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kimd)[1]);
	VM_EVENT(kvm, 3, "SET: guest KLMD   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.klmd)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.klmd)[1]);
	VM_EVENT(kvm, 3, "SET: guest PCKMO  subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pckmo)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pckmo)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMCTR  subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmctr)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmctr)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMF    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmf)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmf)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMO    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmo)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmo)[1]);
	VM_EVENT(kvm, 3, "SET: guest PCC    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pcc)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pcc)[1]);
	VM_EVENT(kvm, 3, "SET: guest PPNO   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ppno)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ppno)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMA    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kma)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kma)[1]);
	VM_EVENT(kvm, 3, "SET: guest KDSA   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kdsa)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kdsa)[1]);
	VM_EVENT(kvm, 3, "SET: guest SORTL  subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[1],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[2],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[3]);
	VM_EVENT(kvm, 3, "SET: guest DFLTCC subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[1],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[2],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[3]);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_set_cpu_model(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret = -ENXIO;

	चयन (attr->attr) अणु
	हाल KVM_S390_VM_CPU_PROCESSOR:
		ret = kvm_s390_set_processor(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_PROCESSOR_FEAT:
		ret = kvm_s390_set_processor_feat(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_PROCESSOR_SUBFUNC:
		ret = kvm_s390_set_processor_subfunc(kvm, attr);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_get_processor(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_cpu_processor *proc;
	पूर्णांक ret = 0;

	proc = kzalloc(माप(*proc), GFP_KERNEL_ACCOUNT);
	अगर (!proc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	proc->cpuid = kvm->arch.model.cpuid;
	proc->ibc = kvm->arch.model.ibc;
	स_नकल(&proc->fac_list, kvm->arch.model.fac_list,
	       S390_ARCH_FAC_LIST_SIZE_BYTE);
	VM_EVENT(kvm, 3, "GET: guest ibc: 0x%4.4x, guest cpuid: 0x%16.16llx",
		 kvm->arch.model.ibc,
		 kvm->arch.model.cpuid);
	VM_EVENT(kvm, 3, "GET: guest faclist: 0x%16.16llx.%16.16llx.%16.16llx",
		 kvm->arch.model.fac_list[0],
		 kvm->arch.model.fac_list[1],
		 kvm->arch.model.fac_list[2]);
	अगर (copy_to_user((व्योम __user *)attr->addr, proc, माप(*proc)))
		ret = -EFAULT;
	kमुक्त(proc);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_get_machine(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_cpu_machine *mach;
	पूर्णांक ret = 0;

	mach = kzalloc(माप(*mach), GFP_KERNEL_ACCOUNT);
	अगर (!mach) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	get_cpu_id((काष्ठा cpuid *) &mach->cpuid);
	mach->ibc = sclp.ibc;
	स_नकल(&mach->fac_mask, kvm->arch.model.fac_mask,
	       S390_ARCH_FAC_LIST_SIZE_BYTE);
	स_नकल((अचिन्हित दीर्घ *)&mach->fac_list, S390_lowcore.stfle_fac_list,
	       माप(S390_lowcore.stfle_fac_list));
	VM_EVENT(kvm, 3, "GET: host ibc:  0x%4.4x, host cpuid:  0x%16.16llx",
		 kvm->arch.model.ibc,
		 kvm->arch.model.cpuid);
	VM_EVENT(kvm, 3, "GET: host facmask:  0x%16.16llx.%16.16llx.%16.16llx",
		 mach->fac_mask[0],
		 mach->fac_mask[1],
		 mach->fac_mask[2]);
	VM_EVENT(kvm, 3, "GET: host faclist:  0x%16.16llx.%16.16llx.%16.16llx",
		 mach->fac_list[0],
		 mach->fac_list[1],
		 mach->fac_list[2]);
	अगर (copy_to_user((व्योम __user *)attr->addr, mach, माप(*mach)))
		ret = -EFAULT;
	kमुक्त(mach);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_get_processor_feat(काष्ठा kvm *kvm,
				       काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_cpu_feat data;

	biपंचांगap_copy((अचिन्हित दीर्घ *) data.feat, kvm->arch.cpu_feat,
		    KVM_S390_VM_CPU_FEAT_NR_BITS);
	अगर (copy_to_user((व्योम __user *)attr->addr, &data, माप(data)))
		वापस -EFAULT;
	VM_EVENT(kvm, 3, "GET: guest feat: 0x%16.16llx.0x%16.16llx.0x%16.16llx",
			 data.feat[0],
			 data.feat[1],
			 data.feat[2]);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_machine_feat(काष्ठा kvm *kvm,
				     काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvm_s390_vm_cpu_feat data;

	biपंचांगap_copy((अचिन्हित दीर्घ *) data.feat,
		    kvm_s390_available_cpu_feat,
		    KVM_S390_VM_CPU_FEAT_NR_BITS);
	अगर (copy_to_user((व्योम __user *)attr->addr, &data, माप(data)))
		वापस -EFAULT;
	VM_EVENT(kvm, 3, "GET: host feat:  0x%16.16llx.0x%16.16llx.0x%16.16llx",
			 data.feat[0],
			 data.feat[1],
			 data.feat[2]);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_processor_subfunc(काष्ठा kvm *kvm,
					  काष्ठा kvm_device_attr *attr)
अणु
	अगर (copy_to_user((व्योम __user *)attr->addr, &kvm->arch.model.subfuncs,
	    माप(काष्ठा kvm_s390_vm_cpu_subfunc)))
		वापस -EFAULT;

	VM_EVENT(kvm, 3, "GET: guest PLO    subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[1],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[2],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.plo)[3]);
	VM_EVENT(kvm, 3, "GET: guest PTFF   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ptff)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ptff)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMAC   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmac)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmac)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMC    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmc)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmc)[1]);
	VM_EVENT(kvm, 3, "GET: guest KM     subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.km)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.km)[1]);
	VM_EVENT(kvm, 3, "GET: guest KIMD   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kimd)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kimd)[1]);
	VM_EVENT(kvm, 3, "GET: guest KLMD   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.klmd)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.klmd)[1]);
	VM_EVENT(kvm, 3, "GET: guest PCKMO  subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pckmo)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pckmo)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMCTR  subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmctr)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmctr)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMF    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmf)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmf)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMO    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmo)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kmo)[1]);
	VM_EVENT(kvm, 3, "GET: guest PCC    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pcc)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.pcc)[1]);
	VM_EVENT(kvm, 3, "GET: guest PPNO   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ppno)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.ppno)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMA    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kma)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kma)[1]);
	VM_EVENT(kvm, 3, "GET: guest KDSA   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kdsa)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.kdsa)[1]);
	VM_EVENT(kvm, 3, "GET: guest SORTL  subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[1],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[2],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.sortl)[3]);
	VM_EVENT(kvm, 3, "GET: guest DFLTCC subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[0],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[1],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[2],
		 ((अचिन्हित दीर्घ *) &kvm->arch.model.subfuncs.dfltcc)[3]);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_machine_subfunc(काष्ठा kvm *kvm,
					काष्ठा kvm_device_attr *attr)
अणु
	अगर (copy_to_user((व्योम __user *)attr->addr, &kvm_s390_available_subfunc,
	    माप(काष्ठा kvm_s390_vm_cpu_subfunc)))
		वापस -EFAULT;

	VM_EVENT(kvm, 3, "GET: host  PLO    subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.plo)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.plo)[1],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.plo)[2],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.plo)[3]);
	VM_EVENT(kvm, 3, "GET: host  PTFF   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.ptff)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.ptff)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMAC   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmac)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmac)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMC    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmc)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmc)[1]);
	VM_EVENT(kvm, 3, "GET: host  KM     subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.km)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.km)[1]);
	VM_EVENT(kvm, 3, "GET: host  KIMD   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kimd)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kimd)[1]);
	VM_EVENT(kvm, 3, "GET: host  KLMD   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.klmd)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.klmd)[1]);
	VM_EVENT(kvm, 3, "GET: host  PCKMO  subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.pckmo)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.pckmo)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMCTR  subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmctr)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmctr)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMF    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmf)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmf)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMO    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmo)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kmo)[1]);
	VM_EVENT(kvm, 3, "GET: host  PCC    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.pcc)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.pcc)[1]);
	VM_EVENT(kvm, 3, "GET: host  PPNO   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.ppno)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.ppno)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMA    subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kma)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kma)[1]);
	VM_EVENT(kvm, 3, "GET: host  KDSA   subfunc 0x%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kdsa)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.kdsa)[1]);
	VM_EVENT(kvm, 3, "GET: host  SORTL  subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.sortl)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.sortl)[1],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.sortl)[2],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.sortl)[3]);
	VM_EVENT(kvm, 3, "GET: host  DFLTCC subfunc 0x%16.16lx.%16.16lx.%16.16lx.%16.16lx",
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.dfltcc)[0],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.dfltcc)[1],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.dfltcc)[2],
		 ((अचिन्हित दीर्घ *) &kvm_s390_available_subfunc.dfltcc)[3]);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_s390_get_cpu_model(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret = -ENXIO;

	चयन (attr->attr) अणु
	हाल KVM_S390_VM_CPU_PROCESSOR:
		ret = kvm_s390_get_processor(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_MACHINE:
		ret = kvm_s390_get_machine(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_PROCESSOR_FEAT:
		ret = kvm_s390_get_processor_feat(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_MACHINE_FEAT:
		ret = kvm_s390_get_machine_feat(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_PROCESSOR_SUBFUNC:
		ret = kvm_s390_get_processor_subfunc(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_MACHINE_SUBFUNC:
		ret = kvm_s390_get_machine_subfunc(kvm, attr);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_vm_set_attr(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_S390_VM_MEM_CTRL:
		ret = kvm_s390_set_mem_control(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_TOD:
		ret = kvm_s390_set_tod(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_MODEL:
		ret = kvm_s390_set_cpu_model(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CRYPTO:
		ret = kvm_s390_vm_set_crypto(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_MIGRATION:
		ret = kvm_s390_vm_set_migration(kvm, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_vm_get_attr(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_S390_VM_MEM_CTRL:
		ret = kvm_s390_get_mem_control(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_TOD:
		ret = kvm_s390_get_tod(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_CPU_MODEL:
		ret = kvm_s390_get_cpu_model(kvm, attr);
		अवरोध;
	हाल KVM_S390_VM_MIGRATION:
		ret = kvm_s390_vm_get_migration(kvm, attr);
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_vm_has_attr(काष्ठा kvm *kvm, काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_S390_VM_MEM_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_S390_VM_MEM_ENABLE_CMMA:
		हाल KVM_S390_VM_MEM_CLR_CMMA:
			ret = sclp.has_cmma ? 0 : -ENXIO;
			अवरोध;
		हाल KVM_S390_VM_MEM_LIMIT_SIZE:
			ret = 0;
			अवरोध;
		शेष:
			ret = -ENXIO;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_S390_VM_TOD:
		चयन (attr->attr) अणु
		हाल KVM_S390_VM_TOD_LOW:
		हाल KVM_S390_VM_TOD_HIGH:
			ret = 0;
			अवरोध;
		शेष:
			ret = -ENXIO;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_S390_VM_CPU_MODEL:
		चयन (attr->attr) अणु
		हाल KVM_S390_VM_CPU_PROCESSOR:
		हाल KVM_S390_VM_CPU_MACHINE:
		हाल KVM_S390_VM_CPU_PROCESSOR_FEAT:
		हाल KVM_S390_VM_CPU_MACHINE_FEAT:
		हाल KVM_S390_VM_CPU_MACHINE_SUBFUNC:
		हाल KVM_S390_VM_CPU_PROCESSOR_SUBFUNC:
			ret = 0;
			अवरोध;
		शेष:
			ret = -ENXIO;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_S390_VM_CRYPTO:
		चयन (attr->attr) अणु
		हाल KVM_S390_VM_CRYPTO_ENABLE_AES_KW:
		हाल KVM_S390_VM_CRYPTO_ENABLE_DEA_KW:
		हाल KVM_S390_VM_CRYPTO_DISABLE_AES_KW:
		हाल KVM_S390_VM_CRYPTO_DISABLE_DEA_KW:
			ret = 0;
			अवरोध;
		हाल KVM_S390_VM_CRYPTO_ENABLE_APIE:
		हाल KVM_S390_VM_CRYPTO_DISABLE_APIE:
			ret = ap_inकाष्ठाions_available() ? 0 : -ENXIO;
			अवरोध;
		शेष:
			ret = -ENXIO;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल KVM_S390_VM_MIGRATION:
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ kvm_s390_get_skeys(काष्ठा kvm *kvm, काष्ठा kvm_s390_skeys *args)
अणु
	uपूर्णांक8_t *keys;
	uपूर्णांक64_t hva;
	पूर्णांक srcu_idx, i, r = 0;

	अगर (args->flags != 0)
		वापस -EINVAL;

	/* Is this guest using storage keys? */
	अगर (!mm_uses_skeys(current->mm))
		वापस KVM_S390_GET_SKEYS_NONE;

	/* Enक्रमce sane limit on memory allocation */
	अगर (args->count < 1 || args->count > KVM_S390_SKEYS_MAX)
		वापस -EINVAL;

	keys = kvदो_स्मृति_array(args->count, माप(uपूर्णांक8_t), GFP_KERNEL_ACCOUNT);
	अगर (!keys)
		वापस -ENOMEM;

	mmap_पढ़ो_lock(current->mm);
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	क्रम (i = 0; i < args->count; i++) अणु
		hva = gfn_to_hva(kvm, args->start_gfn + i);
		अगर (kvm_is_error_hva(hva)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		r = get_guest_storage_key(current->mm, hva, &keys[i]);
		अगर (r)
			अवरोध;
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	mmap_पढ़ो_unlock(current->mm);

	अगर (!r) अणु
		r = copy_to_user((uपूर्णांक8_t __user *)args->skeydata_addr, keys,
				 माप(uपूर्णांक8_t) * args->count);
		अगर (r)
			r = -EFAULT;
	पूर्ण

	kvमुक्त(keys);
	वापस r;
पूर्ण

अटल दीर्घ kvm_s390_set_skeys(काष्ठा kvm *kvm, काष्ठा kvm_s390_skeys *args)
अणु
	uपूर्णांक8_t *keys;
	uपूर्णांक64_t hva;
	पूर्णांक srcu_idx, i, r = 0;
	bool unlocked;

	अगर (args->flags != 0)
		वापस -EINVAL;

	/* Enक्रमce sane limit on memory allocation */
	अगर (args->count < 1 || args->count > KVM_S390_SKEYS_MAX)
		वापस -EINVAL;

	keys = kvदो_स्मृति_array(args->count, माप(uपूर्णांक8_t), GFP_KERNEL_ACCOUNT);
	अगर (!keys)
		वापस -ENOMEM;

	r = copy_from_user(keys, (uपूर्णांक8_t __user *)args->skeydata_addr,
			   माप(uपूर्णांक8_t) * args->count);
	अगर (r) अणु
		r = -EFAULT;
		जाओ out;
	पूर्ण

	/* Enable storage key handling क्रम the guest */
	r = s390_enable_skey();
	अगर (r)
		जाओ out;

	i = 0;
	mmap_पढ़ो_lock(current->mm);
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
        जबतक (i < args->count) अणु
		unlocked = false;
		hva = gfn_to_hva(kvm, args->start_gfn + i);
		अगर (kvm_is_error_hva(hva)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		/* Lowest order bit is reserved */
		अगर (keys[i] & 0x01) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = set_guest_storage_key(current->mm, hva, keys[i], 0);
		अगर (r) अणु
			r = fixup_user_fault(current->mm, hva,
					     FAULT_FLAG_WRITE, &unlocked);
			अगर (r)
				अवरोध;
		पूर्ण
		अगर (!r)
			i++;
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	mmap_पढ़ो_unlock(current->mm);
out:
	kvमुक्त(keys);
	वापस r;
पूर्ण

/*
 * Base address and length must be sent at the start of each block, thereक्रमe
 * it's cheaper to send some clean data, as long as it's less than the size of
 * two दीर्घs.
 */
#घोषणा KVM_S390_MAX_BIT_DISTANCE (2 * माप(व्योम *))
/* क्रम consistency */
#घोषणा KVM_S390_CMMA_SIZE_MAX ((u32)KVM_S390_SKEYS_MAX)

/*
 * Similar to gfn_to_memslot, but वापसs the index of a memslot also when the
 * address falls in a hole. In that हाल the index of one of the memslots
 * bordering the hole is वापसed.
 */
अटल पूर्णांक gfn_to_memslot_approx(काष्ठा kvm_memslots *slots, gfn_t gfn)
अणु
	पूर्णांक start = 0, end = slots->used_slots;
	पूर्णांक slot = atomic_पढ़ो(&slots->lru_slot);
	काष्ठा kvm_memory_slot *memslots = slots->memslots;

	अगर (gfn >= memslots[slot].base_gfn &&
	    gfn < memslots[slot].base_gfn + memslots[slot].npages)
		वापस slot;

	जबतक (start < end) अणु
		slot = start + (end - start) / 2;

		अगर (gfn >= memslots[slot].base_gfn)
			end = slot;
		अन्यथा
			start = slot + 1;
	पूर्ण

	अगर (start >= slots->used_slots)
		वापस slots->used_slots - 1;

	अगर (gfn >= memslots[start].base_gfn &&
	    gfn < memslots[start].base_gfn + memslots[start].npages) अणु
		atomic_set(&slots->lru_slot, start);
	पूर्ण

	वापस start;
पूर्ण

अटल पूर्णांक kvm_s390_peek_cmma(काष्ठा kvm *kvm, काष्ठा kvm_s390_cmma_log *args,
			      u8 *res, अचिन्हित दीर्घ bufsize)
अणु
	अचिन्हित दीर्घ pgstev, hva, cur_gfn = args->start_gfn;

	args->count = 0;
	जबतक (args->count < bufsize) अणु
		hva = gfn_to_hva(kvm, cur_gfn);
		/*
		 * We वापस an error अगर the first value was invalid, but we
		 * वापस successfully अगर at least one value was copied.
		 */
		अगर (kvm_is_error_hva(hva))
			वापस args->count ? 0 : -EFAULT;
		अगर (get_pgste(kvm->mm, hva, &pgstev) < 0)
			pgstev = 0;
		res[args->count++] = (pgstev >> 24) & 0x43;
		cur_gfn++;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ kvm_s390_next_dirty_cmma(काष्ठा kvm_memslots *slots,
					      अचिन्हित दीर्घ cur_gfn)
अणु
	पूर्णांक slotidx = gfn_to_memslot_approx(slots, cur_gfn);
	काष्ठा kvm_memory_slot *ms = slots->memslots + slotidx;
	अचिन्हित दीर्घ ofs = cur_gfn - ms->base_gfn;

	अगर (ms->base_gfn + ms->npages <= cur_gfn) अणु
		slotidx--;
		/* If we are above the highest slot, wrap around */
		अगर (slotidx < 0)
			slotidx = slots->used_slots - 1;

		ms = slots->memslots + slotidx;
		ofs = 0;
	पूर्ण
	ofs = find_next_bit(kvm_second_dirty_biपंचांगap(ms), ms->npages, ofs);
	जबतक ((slotidx > 0) && (ofs >= ms->npages)) अणु
		slotidx--;
		ms = slots->memslots + slotidx;
		ofs = find_next_bit(kvm_second_dirty_biपंचांगap(ms), ms->npages, 0);
	पूर्ण
	वापस ms->base_gfn + ofs;
पूर्ण

अटल पूर्णांक kvm_s390_get_cmma(काष्ठा kvm *kvm, काष्ठा kvm_s390_cmma_log *args,
			     u8 *res, अचिन्हित दीर्घ bufsize)
अणु
	अचिन्हित दीर्घ mem_end, cur_gfn, next_gfn, hva, pgstev;
	काष्ठा kvm_memslots *slots = kvm_memslots(kvm);
	काष्ठा kvm_memory_slot *ms;

	अगर (unlikely(!slots->used_slots))
		वापस 0;

	cur_gfn = kvm_s390_next_dirty_cmma(slots, args->start_gfn);
	ms = gfn_to_memslot(kvm, cur_gfn);
	args->count = 0;
	args->start_gfn = cur_gfn;
	अगर (!ms)
		वापस 0;
	next_gfn = kvm_s390_next_dirty_cmma(slots, cur_gfn + 1);
	mem_end = slots->memslots[0].base_gfn + slots->memslots[0].npages;

	जबतक (args->count < bufsize) अणु
		hva = gfn_to_hva(kvm, cur_gfn);
		अगर (kvm_is_error_hva(hva))
			वापस 0;
		/* Decrement only अगर we actually flipped the bit to 0 */
		अगर (test_and_clear_bit(cur_gfn - ms->base_gfn, kvm_second_dirty_biपंचांगap(ms)))
			atomic64_dec(&kvm->arch.cmma_dirty_pages);
		अगर (get_pgste(kvm->mm, hva, &pgstev) < 0)
			pgstev = 0;
		/* Save the value */
		res[args->count++] = (pgstev >> 24) & 0x43;
		/* If the next bit is too far away, stop. */
		अगर (next_gfn > cur_gfn + KVM_S390_MAX_BIT_DISTANCE)
			वापस 0;
		/* If we reached the previous "next", find the next one */
		अगर (cur_gfn == next_gfn)
			next_gfn = kvm_s390_next_dirty_cmma(slots, cur_gfn + 1);
		/* Reached the end of memory or of the buffer, stop */
		अगर ((next_gfn >= mem_end) ||
		    (next_gfn - args->start_gfn >= bufsize))
			वापस 0;
		cur_gfn++;
		/* Reached the end of the current memslot, take the next one. */
		अगर (cur_gfn - ms->base_gfn >= ms->npages) अणु
			ms = gfn_to_memslot(kvm, cur_gfn);
			अगर (!ms)
				वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function searches क्रम the next page with dirty CMMA attributes, and
 * saves the attributes in the buffer up to either the end of the buffer or
 * until a block of at least KVM_S390_MAX_BIT_DISTANCE clean bits is found;
 * no trailing clean bytes are saved.
 * In हाल no dirty bits were found, or अगर CMMA was not enabled or used, the
 * output buffer will indicate 0 as length.
 */
अटल पूर्णांक kvm_s390_get_cmma_bits(काष्ठा kvm *kvm,
				  काष्ठा kvm_s390_cmma_log *args)
अणु
	अचिन्हित दीर्घ bufsize;
	पूर्णांक srcu_idx, peek, ret;
	u8 *values;

	अगर (!kvm->arch.use_cmma)
		वापस -ENXIO;
	/* Invalid/unsupported flags were specअगरied */
	अगर (args->flags & ~KVM_S390_CMMA_PEEK)
		वापस -EINVAL;
	/* Migration mode query, and we are not करोing a migration */
	peek = !!(args->flags & KVM_S390_CMMA_PEEK);
	अगर (!peek && !kvm->arch.migration_mode)
		वापस -EINVAL;
	/* CMMA is disabled or was not used, or the buffer has length zero */
	bufsize = min(args->count, KVM_S390_CMMA_SIZE_MAX);
	अगर (!bufsize || !kvm->mm->context.uses_cmm) अणु
		स_रखो(args, 0, माप(*args));
		वापस 0;
	पूर्ण
	/* We are not peeking, and there are no dirty pages */
	अगर (!peek && !atomic64_पढ़ो(&kvm->arch.cmma_dirty_pages)) अणु
		स_रखो(args, 0, माप(*args));
		वापस 0;
	पूर्ण

	values = vदो_स्मृति(bufsize);
	अगर (!values)
		वापस -ENOMEM;

	mmap_पढ़ो_lock(kvm->mm);
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	अगर (peek)
		ret = kvm_s390_peek_cmma(kvm, args, values, bufsize);
	अन्यथा
		ret = kvm_s390_get_cmma(kvm, args, values, bufsize);
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	mmap_पढ़ो_unlock(kvm->mm);

	अगर (kvm->arch.migration_mode)
		args->reमुख्यing = atomic64_पढ़ो(&kvm->arch.cmma_dirty_pages);
	अन्यथा
		args->reमुख्यing = 0;

	अगर (copy_to_user((व्योम __user *)args->values, values, args->count))
		ret = -EFAULT;

	vमुक्त(values);
	वापस ret;
पूर्ण

/*
 * This function sets the CMMA attributes क्रम the given pages. If the input
 * buffer has zero length, no action is taken, otherwise the attributes are
 * set and the mm->context.uses_cmm flag is set.
 */
अटल पूर्णांक kvm_s390_set_cmma_bits(काष्ठा kvm *kvm,
				  स्थिर काष्ठा kvm_s390_cmma_log *args)
अणु
	अचिन्हित दीर्घ hva, mask, pgstev, i;
	uपूर्णांक8_t *bits;
	पूर्णांक srcu_idx, r = 0;

	mask = args->mask;

	अगर (!kvm->arch.use_cmma)
		वापस -ENXIO;
	/* invalid/unsupported flags */
	अगर (args->flags != 0)
		वापस -EINVAL;
	/* Enक्रमce sane limit on memory allocation */
	अगर (args->count > KVM_S390_CMMA_SIZE_MAX)
		वापस -EINVAL;
	/* Nothing to करो */
	अगर (args->count == 0)
		वापस 0;

	bits = vदो_स्मृति(array_size(माप(*bits), args->count));
	अगर (!bits)
		वापस -ENOMEM;

	r = copy_from_user(bits, (व्योम __user *)args->values, args->count);
	अगर (r) अणु
		r = -EFAULT;
		जाओ out;
	पूर्ण

	mmap_पढ़ो_lock(kvm->mm);
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	क्रम (i = 0; i < args->count; i++) अणु
		hva = gfn_to_hva(kvm, args->start_gfn + i);
		अगर (kvm_is_error_hva(hva)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		pgstev = bits[i];
		pgstev = pgstev << 24;
		mask &= _PGSTE_GPS_USAGE_MASK | _PGSTE_GPS_NODAT;
		set_pgste_bits(kvm->mm, hva, mask, pgstev);
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	mmap_पढ़ो_unlock(kvm->mm);

	अगर (!kvm->mm->context.uses_cmm) अणु
		mmap_ग_लिखो_lock(kvm->mm);
		kvm->mm->context.uses_cmm = 1;
		mmap_ग_लिखो_unlock(kvm->mm);
	पूर्ण
out:
	vमुक्त(bits);
	वापस r;
पूर्ण

अटल पूर्णांक kvm_s390_cpus_from_pv(काष्ठा kvm *kvm, u16 *rcp, u16 *rrcp)
अणु
	काष्ठा kvm_vcpu *vcpu;
	u16 rc, rrc;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/*
	 * We ignore failures and try to destroy as many CPUs as possible.
	 * At the same समय we must not मुक्त the asचिन्हित resources when
	 * this fails, as the ultravisor has still access to that memory.
	 * So kvm_s390_pv_destroy_cpu can leave a "wanted" memory leak
	 * behind.
	 * We want to वापस the first failure rc and rrc, though.
	 */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		mutex_lock(&vcpu->mutex);
		अगर (kvm_s390_pv_destroy_cpu(vcpu, &rc, &rrc) && !ret) अणु
			*rcp = rc;
			*rrcp = rrc;
			ret = -EIO;
		पूर्ण
		mutex_unlock(&vcpu->mutex);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_s390_cpus_to_pv(काष्ठा kvm *kvm, u16 *rc, u16 *rrc)
अणु
	पूर्णांक i, r = 0;
	u16 dummy;

	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		mutex_lock(&vcpu->mutex);
		r = kvm_s390_pv_create_cpu(vcpu, rc, rrc);
		mutex_unlock(&vcpu->mutex);
		अगर (r)
			अवरोध;
	पूर्ण
	अगर (r)
		kvm_s390_cpus_from_pv(kvm, &dummy, &dummy);
	वापस r;
पूर्ण

अटल पूर्णांक kvm_s390_handle_pv(काष्ठा kvm *kvm, काष्ठा kvm_pv_cmd *cmd)
अणु
	पूर्णांक r = 0;
	u16 dummy;
	व्योम __user *argp = (व्योम __user *)cmd->data;

	चयन (cmd->cmd) अणु
	हाल KVM_PV_ENABLE: अणु
		r = -EINVAL;
		अगर (kvm_s390_pv_is_रक्षित(kvm))
			अवरोध;

		/*
		 *  FMT 4 SIE needs esca. As we never चयन back to bsca from
		 *  esca, we need no cleanup in the error हालs below
		 */
		r = sca_चयन_to_extended(kvm);
		अगर (r)
			अवरोध;

		mmap_ग_लिखो_lock(current->mm);
		r = gmap_mark_unmergeable();
		mmap_ग_लिखो_unlock(current->mm);
		अगर (r)
			अवरोध;

		r = kvm_s390_pv_init_vm(kvm, &cmd->rc, &cmd->rrc);
		अगर (r)
			अवरोध;

		r = kvm_s390_cpus_to_pv(kvm, &cmd->rc, &cmd->rrc);
		अगर (r)
			kvm_s390_pv_deinit_vm(kvm, &dummy, &dummy);

		/* we need to block service पूर्णांकerrupts from now on */
		set_bit(IRQ_PEND_EXT_SERVICE, &kvm->arch.भग्न_पूर्णांक.masked_irqs);
		अवरोध;
	पूर्ण
	हाल KVM_PV_DISABLE: अणु
		r = -EINVAL;
		अगर (!kvm_s390_pv_is_रक्षित(kvm))
			अवरोध;

		r = kvm_s390_cpus_from_pv(kvm, &cmd->rc, &cmd->rrc);
		/*
		 * If a CPU could not be destroyed, destroy VM will also fail.
		 * There is no poपूर्णांक in trying to destroy it. Instead वापस
		 * the rc and rrc from the first CPU that failed destroying.
		 */
		अगर (r)
			अवरोध;
		r = kvm_s390_pv_deinit_vm(kvm, &cmd->rc, &cmd->rrc);

		/* no need to block service पूर्णांकerrupts any more */
		clear_bit(IRQ_PEND_EXT_SERVICE, &kvm->arch.भग्न_पूर्णांक.masked_irqs);
		अवरोध;
	पूर्ण
	हाल KVM_PV_SET_SEC_PARMS: अणु
		काष्ठा kvm_s390_pv_sec_parm parms = अणुपूर्ण;
		व्योम *hdr;

		r = -EINVAL;
		अगर (!kvm_s390_pv_is_रक्षित(kvm))
			अवरोध;

		r = -EFAULT;
		अगर (copy_from_user(&parms, argp, माप(parms)))
			अवरोध;

		/* Currently restricted to 8KB */
		r = -EINVAL;
		अगर (parms.length > PAGE_SIZE * 2)
			अवरोध;

		r = -ENOMEM;
		hdr = vदो_स्मृति(parms.length);
		अगर (!hdr)
			अवरोध;

		r = -EFAULT;
		अगर (!copy_from_user(hdr, (व्योम __user *)parms.origin,
				    parms.length))
			r = kvm_s390_pv_set_sec_parms(kvm, hdr, parms.length,
						      &cmd->rc, &cmd->rrc);

		vमुक्त(hdr);
		अवरोध;
	पूर्ण
	हाल KVM_PV_UNPACK: अणु
		काष्ठा kvm_s390_pv_unp unp = अणुपूर्ण;

		r = -EINVAL;
		अगर (!kvm_s390_pv_is_रक्षित(kvm) || !mm_is_रक्षित(kvm->mm))
			अवरोध;

		r = -EFAULT;
		अगर (copy_from_user(&unp, argp, माप(unp)))
			अवरोध;

		r = kvm_s390_pv_unpack(kvm, unp.addr, unp.size, unp.tweak,
				       &cmd->rc, &cmd->rrc);
		अवरोध;
	पूर्ण
	हाल KVM_PV_VERIFY: अणु
		r = -EINVAL;
		अगर (!kvm_s390_pv_is_रक्षित(kvm))
			अवरोध;

		r = uv_cmd_nodata(kvm_s390_pv_get_handle(kvm),
				  UVC_CMD_VERIFY_IMG, &cmd->rc, &cmd->rrc);
		KVM_UV_EVENT(kvm, 3, "PROTVIRT VERIFY: rc %x rrc %x", cmd->rc,
			     cmd->rrc);
		अवरोध;
	पूर्ण
	हाल KVM_PV_PREP_RESET: अणु
		r = -EINVAL;
		अगर (!kvm_s390_pv_is_रक्षित(kvm))
			अवरोध;

		r = uv_cmd_nodata(kvm_s390_pv_get_handle(kvm),
				  UVC_CMD_PREPARE_RESET, &cmd->rc, &cmd->rrc);
		KVM_UV_EVENT(kvm, 3, "PROTVIRT PREP RESET: rc %x rrc %x",
			     cmd->rc, cmd->rrc);
		अवरोध;
	पूर्ण
	हाल KVM_PV_UNSHARE_ALL: अणु
		r = -EINVAL;
		अगर (!kvm_s390_pv_is_रक्षित(kvm))
			अवरोध;

		r = uv_cmd_nodata(kvm_s390_pv_get_handle(kvm),
				  UVC_CMD_SET_UNSHARE_ALL, &cmd->rc, &cmd->rrc);
		KVM_UV_EVENT(kvm, 3, "PROTVIRT UNSHARE: rc %x rrc %x",
			     cmd->rc, cmd->rrc);
		अवरोध;
	पूर्ण
	शेष:
		r = -ENOTTY;
	पूर्ण
	वापस r;
पूर्ण

दीर्घ kvm_arch_vm_ioctl(काष्ठा file *filp,
		       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा kvm_device_attr attr;
	पूर्णांक r;

	चयन (ioctl) अणु
	हाल KVM_S390_INTERRUPT: अणु
		काष्ठा kvm_s390_पूर्णांकerrupt s390पूर्णांक;

		r = -EFAULT;
		अगर (copy_from_user(&s390पूर्णांक, argp, माप(s390पूर्णांक)))
			अवरोध;
		r = kvm_s390_inject_vm(kvm, &s390पूर्णांक);
		अवरोध;
	पूर्ण
	हाल KVM_CREATE_IRQCHIP: अणु
		काष्ठा kvm_irq_routing_entry routing;

		r = -EINVAL;
		अगर (kvm->arch.use_irqchip) अणु
			/* Set up dummy routing. */
			स_रखो(&routing, 0, माप(routing));
			r = kvm_set_irq_routing(kvm, &routing, 0, 0);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल KVM_SET_DEVICE_ATTR: अणु
		r = -EFAULT;
		अगर (copy_from_user(&attr, (व्योम __user *)arg, माप(attr)))
			अवरोध;
		r = kvm_s390_vm_set_attr(kvm, &attr);
		अवरोध;
	पूर्ण
	हाल KVM_GET_DEVICE_ATTR: अणु
		r = -EFAULT;
		अगर (copy_from_user(&attr, (व्योम __user *)arg, माप(attr)))
			अवरोध;
		r = kvm_s390_vm_get_attr(kvm, &attr);
		अवरोध;
	पूर्ण
	हाल KVM_HAS_DEVICE_ATTR: अणु
		r = -EFAULT;
		अगर (copy_from_user(&attr, (व्योम __user *)arg, माप(attr)))
			अवरोध;
		r = kvm_s390_vm_has_attr(kvm, &attr);
		अवरोध;
	पूर्ण
	हाल KVM_S390_GET_SKEYS: अणु
		काष्ठा kvm_s390_skeys args;

		r = -EFAULT;
		अगर (copy_from_user(&args, argp,
				   माप(काष्ठा kvm_s390_skeys)))
			अवरोध;
		r = kvm_s390_get_skeys(kvm, &args);
		अवरोध;
	पूर्ण
	हाल KVM_S390_SET_SKEYS: अणु
		काष्ठा kvm_s390_skeys args;

		r = -EFAULT;
		अगर (copy_from_user(&args, argp,
				   माप(काष्ठा kvm_s390_skeys)))
			अवरोध;
		r = kvm_s390_set_skeys(kvm, &args);
		अवरोध;
	पूर्ण
	हाल KVM_S390_GET_CMMA_BITS: अणु
		काष्ठा kvm_s390_cmma_log args;

		r = -EFAULT;
		अगर (copy_from_user(&args, argp, माप(args)))
			अवरोध;
		mutex_lock(&kvm->slots_lock);
		r = kvm_s390_get_cmma_bits(kvm, &args);
		mutex_unlock(&kvm->slots_lock);
		अगर (!r) अणु
			r = copy_to_user(argp, &args, माप(args));
			अगर (r)
				r = -EFAULT;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल KVM_S390_SET_CMMA_BITS: अणु
		काष्ठा kvm_s390_cmma_log args;

		r = -EFAULT;
		अगर (copy_from_user(&args, argp, माप(args)))
			अवरोध;
		mutex_lock(&kvm->slots_lock);
		r = kvm_s390_set_cmma_bits(kvm, &args);
		mutex_unlock(&kvm->slots_lock);
		अवरोध;
	पूर्ण
	हाल KVM_S390_PV_COMMAND: अणु
		काष्ठा kvm_pv_cmd args;

		/* protvirt means user sigp */
		kvm->arch.user_cpu_state_ctrl = 1;
		r = 0;
		अगर (!is_prot_virt_host()) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&args, argp, माप(args))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (args.flags) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		mutex_lock(&kvm->lock);
		r = kvm_s390_handle_pv(kvm, &args);
		mutex_unlock(&kvm->lock);
		अगर (copy_to_user(argp, &args, माप(args))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		r = -ENOTTY;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_s390_apxa_installed(व्योम)
अणु
	काष्ठा ap_config_info info;

	अगर (ap_inकाष्ठाions_available()) अणु
		अगर (ap_qci(&info) == 0)
			वापस info.apxa;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The क्रमmat of the crypto control block (CRYCB) is specअगरied in the 3 low
 * order bits of the CRYCB designation (CRYCBD) field as follows:
 * Format 0: Neither the message security assist extension 3 (MSAX3) nor the
 *	     AP extended addressing (APXA) facility are installed.
 * Format 1: The APXA facility is not installed but the MSAX3 facility is.
 * Format 2: Both the APXA and MSAX3 facilities are installed
 */
अटल व्योम kvm_s390_set_crycb_क्रमmat(काष्ठा kvm *kvm)
अणु
	kvm->arch.crypto.crycbd = (__u32)(अचिन्हित दीर्घ) kvm->arch.crypto.crycb;

	/* Clear the CRYCB क्रमmat bits - i.e., set क्रमmat 0 by शेष */
	kvm->arch.crypto.crycbd &= ~(CRYCB_FORMAT_MASK);

	/* Check whether MSAX3 is installed */
	अगर (!test_kvm_facility(kvm, 76))
		वापस;

	अगर (kvm_s390_apxa_installed())
		kvm->arch.crypto.crycbd |= CRYCB_FORMAT2;
	अन्यथा
		kvm->arch.crypto.crycbd |= CRYCB_FORMAT1;
पूर्ण

व्योम kvm_arch_crypto_set_masks(काष्ठा kvm *kvm, अचिन्हित दीर्घ *apm,
			       अचिन्हित दीर्घ *aqm, अचिन्हित दीर्घ *adm)
अणु
	काष्ठा kvm_s390_crypto_cb *crycb = kvm->arch.crypto.crycb;

	mutex_lock(&kvm->lock);
	kvm_s390_vcpu_block_all(kvm);

	चयन (kvm->arch.crypto.crycbd & CRYCB_FORMAT_MASK) अणु
	हाल CRYCB_FORMAT2: /* APCB1 use 256 bits */
		स_नकल(crycb->apcb1.apm, apm, 32);
		VM_EVENT(kvm, 3, "SET CRYCB: apm %016lx %016lx %016lx %016lx",
			 apm[0], apm[1], apm[2], apm[3]);
		स_नकल(crycb->apcb1.aqm, aqm, 32);
		VM_EVENT(kvm, 3, "SET CRYCB: aqm %016lx %016lx %016lx %016lx",
			 aqm[0], aqm[1], aqm[2], aqm[3]);
		स_नकल(crycb->apcb1.adm, adm, 32);
		VM_EVENT(kvm, 3, "SET CRYCB: adm %016lx %016lx %016lx %016lx",
			 adm[0], adm[1], adm[2], adm[3]);
		अवरोध;
	हाल CRYCB_FORMAT1:
	हाल CRYCB_FORMAT0: /* Fall through both use APCB0 */
		स_नकल(crycb->apcb0.apm, apm, 8);
		स_नकल(crycb->apcb0.aqm, aqm, 2);
		स_नकल(crycb->apcb0.adm, adm, 2);
		VM_EVENT(kvm, 3, "SET CRYCB: apm %016lx aqm %04x adm %04x",
			 apm[0], *((अचिन्हित लघु *)aqm),
			 *((अचिन्हित लघु *)adm));
		अवरोध;
	शेष:	/* Can not happen */
		अवरोध;
	पूर्ण

	/* recreate the shaकरोw crycb क्रम each vcpu */
	kvm_s390_sync_request_broadcast(kvm, KVM_REQ_VSIE_RESTART);
	kvm_s390_vcpu_unblock_all(kvm);
	mutex_unlock(&kvm->lock);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_crypto_set_masks);

व्योम kvm_arch_crypto_clear_masks(काष्ठा kvm *kvm)
अणु
	mutex_lock(&kvm->lock);
	kvm_s390_vcpu_block_all(kvm);

	स_रखो(&kvm->arch.crypto.crycb->apcb0, 0,
	       माप(kvm->arch.crypto.crycb->apcb0));
	स_रखो(&kvm->arch.crypto.crycb->apcb1, 0,
	       माप(kvm->arch.crypto.crycb->apcb1));

	VM_EVENT(kvm, 3, "%s", "CLR CRYCB:");
	/* recreate the shaकरोw crycb क्रम each vcpu */
	kvm_s390_sync_request_broadcast(kvm, KVM_REQ_VSIE_RESTART);
	kvm_s390_vcpu_unblock_all(kvm);
	mutex_unlock(&kvm->lock);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_crypto_clear_masks);

अटल u64 kvm_s390_get_initial_cpuid(व्योम)
अणु
	काष्ठा cpuid cpuid;

	get_cpu_id(&cpuid);
	cpuid.version = 0xff;
	वापस *((u64 *) &cpuid);
पूर्ण

अटल व्योम kvm_s390_crypto_init(काष्ठा kvm *kvm)
अणु
	kvm->arch.crypto.crycb = &kvm->arch.sie_page2->crycb;
	kvm_s390_set_crycb_क्रमmat(kvm);

	अगर (!test_kvm_facility(kvm, 76))
		वापस;

	/* Enable AES/DEA रक्षित key functions by शेष */
	kvm->arch.crypto.aes_kw = 1;
	kvm->arch.crypto.dea_kw = 1;
	get_अक्रमom_bytes(kvm->arch.crypto.crycb->aes_wrapping_key_mask,
			 माप(kvm->arch.crypto.crycb->aes_wrapping_key_mask));
	get_अक्रमom_bytes(kvm->arch.crypto.crycb->dea_wrapping_key_mask,
			 माप(kvm->arch.crypto.crycb->dea_wrapping_key_mask));
पूर्ण

अटल व्योम sca_dispose(काष्ठा kvm *kvm)
अणु
	अगर (kvm->arch.use_esca)
		मुक्त_pages_exact(kvm->arch.sca, माप(काष्ठा esca_block));
	अन्यथा
		मुक्त_page((अचिन्हित दीर्घ)(kvm->arch.sca));
	kvm->arch.sca = शून्य;
पूर्ण

पूर्णांक kvm_arch_init_vm(काष्ठा kvm *kvm, अचिन्हित दीर्घ type)
अणु
	gfp_t alloc_flags = GFP_KERNEL_ACCOUNT;
	पूर्णांक i, rc;
	अक्षर debug_name[16];
	अटल अचिन्हित दीर्घ sca_offset;

	rc = -EINVAL;
#अगर_घोषित CONFIG_KVM_S390_UCONTROL
	अगर (type & ~KVM_VM_S390_UCONTROL)
		जाओ out_err;
	अगर ((type & KVM_VM_S390_UCONTROL) && (!capable(CAP_SYS_ADMIN)))
		जाओ out_err;
#अन्यथा
	अगर (type)
		जाओ out_err;
#पूर्ण_अगर

	rc = s390_enable_sie();
	अगर (rc)
		जाओ out_err;

	rc = -ENOMEM;

	अगर (!sclp.has_64bscao)
		alloc_flags |= GFP_DMA;
	rwlock_init(&kvm->arch.sca_lock);
	/* start with basic SCA */
	kvm->arch.sca = (काष्ठा bsca_block *) get_zeroed_page(alloc_flags);
	अगर (!kvm->arch.sca)
		जाओ out_err;
	mutex_lock(&kvm_lock);
	sca_offset += 16;
	अगर (sca_offset + माप(काष्ठा bsca_block) > PAGE_SIZE)
		sca_offset = 0;
	kvm->arch.sca = (काष्ठा bsca_block *)
			((अक्षर *) kvm->arch.sca + sca_offset);
	mutex_unlock(&kvm_lock);

	प्र_लिखो(debug_name, "kvm-%u", current->pid);

	kvm->arch.dbf = debug_रेजिस्टर(debug_name, 32, 1, 7 * माप(दीर्घ));
	अगर (!kvm->arch.dbf)
		जाओ out_err;

	BUILD_BUG_ON(माप(काष्ठा sie_page2) != 4096);
	kvm->arch.sie_page2 =
	     (काष्ठा sie_page2 *) get_zeroed_page(GFP_KERNEL_ACCOUNT | GFP_DMA);
	अगर (!kvm->arch.sie_page2)
		जाओ out_err;

	kvm->arch.sie_page2->kvm = kvm;
	kvm->arch.model.fac_list = kvm->arch.sie_page2->fac_list;

	क्रम (i = 0; i < kvm_s390_fac_size(); i++) अणु
		kvm->arch.model.fac_mask[i] = S390_lowcore.stfle_fac_list[i] &
					      (kvm_s390_fac_base[i] |
					       kvm_s390_fac_ext[i]);
		kvm->arch.model.fac_list[i] = S390_lowcore.stfle_fac_list[i] &
					      kvm_s390_fac_base[i];
	पूर्ण
	kvm->arch.model.subfuncs = kvm_s390_available_subfunc;

	/* we are always in czam mode - even on pre z14 machines */
	set_kvm_facility(kvm->arch.model.fac_mask, 138);
	set_kvm_facility(kvm->arch.model.fac_list, 138);
	/* we emulate STHYI in kvm */
	set_kvm_facility(kvm->arch.model.fac_mask, 74);
	set_kvm_facility(kvm->arch.model.fac_list, 74);
	अगर (MACHINE_HAS_TLB_GUEST) अणु
		set_kvm_facility(kvm->arch.model.fac_mask, 147);
		set_kvm_facility(kvm->arch.model.fac_list, 147);
	पूर्ण

	अगर (css_general_अक्षरacteristics.aiv && test_facility(65))
		set_kvm_facility(kvm->arch.model.fac_mask, 65);

	kvm->arch.model.cpuid = kvm_s390_get_initial_cpuid();
	kvm->arch.model.ibc = sclp.ibc & 0x0fff;

	kvm_s390_crypto_init(kvm);

	mutex_init(&kvm->arch.भग्न_पूर्णांक.ais_lock);
	spin_lock_init(&kvm->arch.भग्न_पूर्णांक.lock);
	क्रम (i = 0; i < FIRQ_LIST_COUNT; i++)
		INIT_LIST_HEAD(&kvm->arch.भग्न_पूर्णांक.lists[i]);
	init_रुकोqueue_head(&kvm->arch.ipte_wq);
	mutex_init(&kvm->arch.ipte_mutex);

	debug_रेजिस्टर_view(kvm->arch.dbf, &debug_प्र_लिखो_view);
	VM_EVENT(kvm, 3, "vm created with type %lu", type);

	अगर (type & KVM_VM_S390_UCONTROL) अणु
		kvm->arch.gmap = शून्य;
		kvm->arch.mem_limit = KVM_S390_NO_MEM_LIMIT;
	पूर्ण अन्यथा अणु
		अगर (sclp.hamax == U64_MAX)
			kvm->arch.mem_limit = TASK_SIZE_MAX;
		अन्यथा
			kvm->arch.mem_limit = min_t(अचिन्हित दीर्घ, TASK_SIZE_MAX,
						    sclp.hamax + 1);
		kvm->arch.gmap = gmap_create(current->mm, kvm->arch.mem_limit - 1);
		अगर (!kvm->arch.gmap)
			जाओ out_err;
		kvm->arch.gmap->निजी = kvm;
		kvm->arch.gmap->pfault_enabled = 0;
	पूर्ण

	kvm->arch.use_pfmfi = sclp.has_pfmfi;
	kvm->arch.use_skf = sclp.has_skey;
	spin_lock_init(&kvm->arch.start_stop_lock);
	kvm_s390_vsie_init(kvm);
	अगर (use_gisa)
		kvm_s390_gisa_init(kvm);
	KVM_EVENT(3, "vm 0x%pK created by pid %u", kvm, current->pid);

	वापस 0;
out_err:
	मुक्त_page((अचिन्हित दीर्घ)kvm->arch.sie_page2);
	debug_unरेजिस्टर(kvm->arch.dbf);
	sca_dispose(kvm);
	KVM_EVENT(3, "creation of vm failed: %d", rc);
	वापस rc;
पूर्ण

व्योम kvm_arch_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	u16 rc, rrc;

	VCPU_EVENT(vcpu, 3, "%s", "free cpu");
	trace_kvm_s390_destroy_vcpu(vcpu->vcpu_id);
	kvm_s390_clear_local_irqs(vcpu);
	kvm_clear_async_pf_completion_queue(vcpu);
	अगर (!kvm_is_ucontrol(vcpu->kvm))
		sca_del_vcpu(vcpu);

	अगर (kvm_is_ucontrol(vcpu->kvm))
		gmap_हटाओ(vcpu->arch.gmap);

	अगर (vcpu->kvm->arch.use_cmma)
		kvm_s390_vcpu_unsetup_cmma(vcpu);
	/* We can not hold the vcpu mutex here, we are alपढ़ोy dying */
	अगर (kvm_s390_pv_cpu_get_handle(vcpu))
		kvm_s390_pv_destroy_cpu(vcpu, &rc, &rrc);
	मुक्त_page((अचिन्हित दीर्घ)(vcpu->arch.sie_block));
पूर्ण

अटल व्योम kvm_मुक्त_vcpus(काष्ठा kvm *kvm)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vcpu_destroy(vcpu);

	mutex_lock(&kvm->lock);
	क्रम (i = 0; i < atomic_पढ़ो(&kvm->online_vcpus); i++)
		kvm->vcpus[i] = शून्य;

	atomic_set(&kvm->online_vcpus, 0);
	mutex_unlock(&kvm->lock);
पूर्ण

व्योम kvm_arch_destroy_vm(काष्ठा kvm *kvm)
अणु
	u16 rc, rrc;

	kvm_मुक्त_vcpus(kvm);
	sca_dispose(kvm);
	kvm_s390_gisa_destroy(kvm);
	/*
	 * We are alपढ़ोy at the end of lअगरe and kvm->lock is not taken.
	 * This is ok as the file descriptor is बंदd by now and nobody
	 * can mess with the pv state. To aव्योम lockdep_निश्चित_held from
	 * complaining we करो not use kvm_s390_pv_is_रक्षित.
	 */
	अगर (kvm_s390_pv_get_handle(kvm))
		kvm_s390_pv_deinit_vm(kvm, &rc, &rrc);
	debug_unरेजिस्टर(kvm->arch.dbf);
	मुक्त_page((अचिन्हित दीर्घ)kvm->arch.sie_page2);
	अगर (!kvm_is_ucontrol(kvm))
		gmap_हटाओ(kvm->arch.gmap);
	kvm_s390_destroy_adapters(kvm);
	kvm_s390_clear_भग्न_irqs(kvm);
	kvm_s390_vsie_destroy(kvm);
	KVM_EVENT(3, "vm 0x%pK destroyed", kvm);
पूर्ण

/* Section: vcpu related */
अटल पूर्णांक __kvm_ucontrol_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.gmap = gmap_create(current->mm, -1UL);
	अगर (!vcpu->arch.gmap)
		वापस -ENOMEM;
	vcpu->arch.gmap->निजी = vcpu->kvm;

	वापस 0;
पूर्ण

अटल व्योम sca_del_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_s390_use_sca_entries())
		वापस;
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	अगर (vcpu->kvm->arch.use_esca) अणु
		काष्ठा esca_block *sca = vcpu->kvm->arch.sca;

		clear_bit_inv(vcpu->vcpu_id, (अचिन्हित दीर्घ *) sca->mcn);
		sca->cpu[vcpu->vcpu_id].sda = 0;
	पूर्ण अन्यथा अणु
		काष्ठा bsca_block *sca = vcpu->kvm->arch.sca;

		clear_bit_inv(vcpu->vcpu_id, (अचिन्हित दीर्घ *) &sca->mcn);
		sca->cpu[vcpu->vcpu_id].sda = 0;
	पूर्ण
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
पूर्ण

अटल व्योम sca_add_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_s390_use_sca_entries()) अणु
		काष्ठा bsca_block *sca = vcpu->kvm->arch.sca;

		/* we still need the basic sca क्रम the ipte control */
		vcpu->arch.sie_block->scaoh = (__u32)(((__u64)sca) >> 32);
		vcpu->arch.sie_block->scaol = (__u32)(__u64)sca;
		वापस;
	पूर्ण
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	अगर (vcpu->kvm->arch.use_esca) अणु
		काष्ठा esca_block *sca = vcpu->kvm->arch.sca;

		sca->cpu[vcpu->vcpu_id].sda = (__u64) vcpu->arch.sie_block;
		vcpu->arch.sie_block->scaoh = (__u32)(((__u64)sca) >> 32);
		vcpu->arch.sie_block->scaol = (__u32)(__u64)sca & ~0x3fU;
		vcpu->arch.sie_block->ecb2 |= ECB2_ESCA;
		set_bit_inv(vcpu->vcpu_id, (अचिन्हित दीर्घ *) sca->mcn);
	पूर्ण अन्यथा अणु
		काष्ठा bsca_block *sca = vcpu->kvm->arch.sca;

		sca->cpu[vcpu->vcpu_id].sda = (__u64) vcpu->arch.sie_block;
		vcpu->arch.sie_block->scaoh = (__u32)(((__u64)sca) >> 32);
		vcpu->arch.sie_block->scaol = (__u32)(__u64)sca;
		set_bit_inv(vcpu->vcpu_id, (अचिन्हित दीर्घ *) &sca->mcn);
	पूर्ण
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
पूर्ण

/* Basic SCA to Extended SCA data copy routines */
अटल अंतरभूत व्योम sca_copy_entry(काष्ठा esca_entry *d, काष्ठा bsca_entry *s)
अणु
	d->sda = s->sda;
	d->sigp_ctrl.c = s->sigp_ctrl.c;
	d->sigp_ctrl.scn = s->sigp_ctrl.scn;
पूर्ण

अटल व्योम sca_copy_b_to_e(काष्ठा esca_block *d, काष्ठा bsca_block *s)
अणु
	पूर्णांक i;

	d->ipte_control = s->ipte_control;
	d->mcn[0] = s->mcn;
	क्रम (i = 0; i < KVM_S390_BSCA_CPU_SLOTS; i++)
		sca_copy_entry(&d->cpu[i], &s->cpu[i]);
पूर्ण

अटल पूर्णांक sca_चयन_to_extended(काष्ठा kvm *kvm)
अणु
	काष्ठा bsca_block *old_sca = kvm->arch.sca;
	काष्ठा esca_block *new_sca;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित पूर्णांक vcpu_idx;
	u32 scaol, scaoh;

	अगर (kvm->arch.use_esca)
		वापस 0;

	new_sca = alloc_pages_exact(माप(*new_sca), GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!new_sca)
		वापस -ENOMEM;

	scaoh = (u32)((u64)(new_sca) >> 32);
	scaol = (u32)(u64)(new_sca) & ~0x3fU;

	kvm_s390_vcpu_block_all(kvm);
	ग_लिखो_lock(&kvm->arch.sca_lock);

	sca_copy_b_to_e(new_sca, old_sca);

	kvm_क्रम_each_vcpu(vcpu_idx, vcpu, kvm) अणु
		vcpu->arch.sie_block->scaoh = scaoh;
		vcpu->arch.sie_block->scaol = scaol;
		vcpu->arch.sie_block->ecb2 |= ECB2_ESCA;
	पूर्ण
	kvm->arch.sca = new_sca;
	kvm->arch.use_esca = 1;

	ग_लिखो_unlock(&kvm->arch.sca_lock);
	kvm_s390_vcpu_unblock_all(kvm);

	मुक्त_page((अचिन्हित दीर्घ)old_sca);

	VM_EVENT(kvm, 2, "Switched to ESCA (0x%pK -> 0x%pK)",
		 old_sca, kvm->arch.sca);
	वापस 0;
पूर्ण

अटल पूर्णांक sca_can_add_vcpu(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक rc;

	अगर (!kvm_s390_use_sca_entries()) अणु
		अगर (id < KVM_MAX_VCPUS)
			वापस true;
		वापस false;
	पूर्ण
	अगर (id < KVM_S390_BSCA_CPU_SLOTS)
		वापस true;
	अगर (!sclp.has_esca || !sclp.has_64bscao)
		वापस false;

	mutex_lock(&kvm->lock);
	rc = kvm->arch.use_esca ? 0 : sca_चयन_to_extended(kvm);
	mutex_unlock(&kvm->lock);

	वापस rc == 0 && id < KVM_S390_ESCA_CPU_SLOTS;
पूर्ण

/* needs disabled preemption to protect from TOD sync and vcpu_load/put */
अटल व्योम __start_cpu_समयr_accounting(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON_ONCE(vcpu->arch.cpuपंचांग_start != 0);
	raw_ग_लिखो_seqcount_begin(&vcpu->arch.cpuपंचांग_seqcount);
	vcpu->arch.cpuपंचांग_start = get_tod_घड़ी_fast();
	raw_ग_लिखो_seqcount_end(&vcpu->arch.cpuपंचांग_seqcount);
पूर्ण

/* needs disabled preemption to protect from TOD sync and vcpu_load/put */
अटल व्योम __stop_cpu_समयr_accounting(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON_ONCE(vcpu->arch.cpuपंचांग_start == 0);
	raw_ग_लिखो_seqcount_begin(&vcpu->arch.cpuपंचांग_seqcount);
	vcpu->arch.sie_block->cpuपंचांग -= get_tod_घड़ी_fast() - vcpu->arch.cpuपंचांग_start;
	vcpu->arch.cpuपंचांग_start = 0;
	raw_ग_लिखो_seqcount_end(&vcpu->arch.cpuपंचांग_seqcount);
पूर्ण

/* needs disabled preemption to protect from TOD sync and vcpu_load/put */
अटल व्योम __enable_cpu_समयr_accounting(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON_ONCE(vcpu->arch.cpuपंचांग_enabled);
	vcpu->arch.cpuपंचांग_enabled = true;
	__start_cpu_समयr_accounting(vcpu);
पूर्ण

/* needs disabled preemption to protect from TOD sync and vcpu_load/put */
अटल व्योम __disable_cpu_समयr_accounting(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON_ONCE(!vcpu->arch.cpuपंचांग_enabled);
	__stop_cpu_समयr_accounting(vcpu);
	vcpu->arch.cpuपंचांग_enabled = false;
पूर्ण

अटल व्योम enable_cpu_समयr_accounting(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable(); /* protect from TOD sync and vcpu_load/put */
	__enable_cpu_समयr_accounting(vcpu);
	preempt_enable();
पूर्ण

अटल व्योम disable_cpu_समयr_accounting(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable(); /* protect from TOD sync and vcpu_load/put */
	__disable_cpu_समयr_accounting(vcpu);
	preempt_enable();
पूर्ण

/* set the cpu समयr - may only be called from the VCPU thपढ़ो itself */
व्योम kvm_s390_set_cpu_समयr(काष्ठा kvm_vcpu *vcpu, __u64 cpuपंचांग)
अणु
	preempt_disable(); /* protect from TOD sync and vcpu_load/put */
	raw_ग_लिखो_seqcount_begin(&vcpu->arch.cpuपंचांग_seqcount);
	अगर (vcpu->arch.cpuपंचांग_enabled)
		vcpu->arch.cpuपंचांग_start = get_tod_घड़ी_fast();
	vcpu->arch.sie_block->cpuपंचांग = cpuपंचांग;
	raw_ग_लिखो_seqcount_end(&vcpu->arch.cpuपंचांग_seqcount);
	preempt_enable();
पूर्ण

/* update and get the cpu समयr - can also be called from other VCPU thपढ़ोs */
__u64 kvm_s390_get_cpu_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक seq;
	__u64 value;

	अगर (unlikely(!vcpu->arch.cpuपंचांग_enabled))
		वापस vcpu->arch.sie_block->cpuपंचांग;

	preempt_disable(); /* protect from TOD sync and vcpu_load/put */
	करो अणु
		seq = raw_पढ़ो_seqcount(&vcpu->arch.cpuपंचांग_seqcount);
		/*
		 * If the ग_लिखोr would ever execute a पढ़ो in the critical
		 * section, e.g. in irq context, we have a deadlock.
		 */
		WARN_ON_ONCE((seq & 1) && smp_processor_id() == vcpu->cpu);
		value = vcpu->arch.sie_block->cpuपंचांग;
		/* अगर cpuपंचांग_start is 0, accounting is being started/stopped */
		अगर (likely(vcpu->arch.cpuपंचांग_start))
			value -= get_tod_घड़ी_fast() - vcpu->arch.cpuपंचांग_start;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&vcpu->arch.cpuपंचांग_seqcount, seq & ~1));
	preempt_enable();
	वापस value;
पूर्ण

व्योम kvm_arch_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु

	gmap_enable(vcpu->arch.enabled_gmap);
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_RUNNING);
	अगर (vcpu->arch.cpuपंचांग_enabled && !is_vcpu_idle(vcpu))
		__start_cpu_समयr_accounting(vcpu);
	vcpu->cpu = cpu;
पूर्ण

व्योम kvm_arch_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->cpu = -1;
	अगर (vcpu->arch.cpuपंचांग_enabled && !is_vcpu_idle(vcpu))
		__stop_cpu_समयr_accounting(vcpu);
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_RUNNING);
	vcpu->arch.enabled_gmap = gmap_get_enabled();
	gmap_disable(vcpu->arch.enabled_gmap);

पूर्ण

व्योम kvm_arch_vcpu_postcreate(काष्ठा kvm_vcpu *vcpu)
अणु
	mutex_lock(&vcpu->kvm->lock);
	preempt_disable();
	vcpu->arch.sie_block->epoch = vcpu->kvm->arch.epoch;
	vcpu->arch.sie_block->epdx = vcpu->kvm->arch.epdx;
	preempt_enable();
	mutex_unlock(&vcpu->kvm->lock);
	अगर (!kvm_is_ucontrol(vcpu->kvm)) अणु
		vcpu->arch.gmap = vcpu->kvm->arch.gmap;
		sca_add_vcpu(vcpu);
	पूर्ण
	अगर (test_kvm_facility(vcpu->kvm, 74) || vcpu->kvm->arch.user_instr0)
		vcpu->arch.sie_block->ictl |= ICTL_OPEREXC;
	/* make vcpu_load load the right gmap on the first trigger */
	vcpu->arch.enabled_gmap = vcpu->arch.gmap;
पूर्ण

अटल bool kvm_has_pckmo_subfunc(काष्ठा kvm *kvm, अचिन्हित दीर्घ nr)
अणु
	अगर (test_bit_inv(nr, (अचिन्हित दीर्घ *)&kvm->arch.model.subfuncs.pckmo) &&
	    test_bit_inv(nr, (अचिन्हित दीर्घ *)&kvm_s390_available_subfunc.pckmo))
		वापस true;
	वापस false;
पूर्ण

अटल bool kvm_has_pckmo_ecc(काष्ठा kvm *kvm)
अणु
	/* At least one ECC subfunction must be present */
	वापस kvm_has_pckmo_subfunc(kvm, 32) ||
	       kvm_has_pckmo_subfunc(kvm, 33) ||
	       kvm_has_pckmo_subfunc(kvm, 34) ||
	       kvm_has_pckmo_subfunc(kvm, 40) ||
	       kvm_has_pckmo_subfunc(kvm, 41);

पूर्ण

अटल व्योम kvm_s390_vcpu_crypto_setup(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * If the AP inकाष्ठाions are not being पूर्णांकerpreted and the MSAX3
	 * facility is not configured क्रम the guest, there is nothing to set up.
	 */
	अगर (!vcpu->kvm->arch.crypto.apie && !test_kvm_facility(vcpu->kvm, 76))
		वापस;

	vcpu->arch.sie_block->crycbd = vcpu->kvm->arch.crypto.crycbd;
	vcpu->arch.sie_block->ecb3 &= ~(ECB3_AES | ECB3_DEA);
	vcpu->arch.sie_block->eca &= ~ECA_APIE;
	vcpu->arch.sie_block->ecd &= ~ECD_ECC;

	अगर (vcpu->kvm->arch.crypto.apie)
		vcpu->arch.sie_block->eca |= ECA_APIE;

	/* Set up रक्षित key support */
	अगर (vcpu->kvm->arch.crypto.aes_kw) अणु
		vcpu->arch.sie_block->ecb3 |= ECB3_AES;
		/* ecc is also wrapped with AES key */
		अगर (kvm_has_pckmo_ecc(vcpu->kvm))
			vcpu->arch.sie_block->ecd |= ECD_ECC;
	पूर्ण

	अगर (vcpu->kvm->arch.crypto.dea_kw)
		vcpu->arch.sie_block->ecb3 |= ECB3_DEA;
पूर्ण

व्योम kvm_s390_vcpu_unsetup_cmma(काष्ठा kvm_vcpu *vcpu)
अणु
	मुक्त_page(vcpu->arch.sie_block->cbrlo);
	vcpu->arch.sie_block->cbrlo = 0;
पूर्ण

पूर्णांक kvm_s390_vcpu_setup_cmma(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.sie_block->cbrlo = get_zeroed_page(GFP_KERNEL_ACCOUNT);
	अगर (!vcpu->arch.sie_block->cbrlo)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम kvm_s390_vcpu_setup_model(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_cpu_model *model = &vcpu->kvm->arch.model;

	vcpu->arch.sie_block->ibc = model->ibc;
	अगर (test_kvm_facility(vcpu->kvm, 7))
		vcpu->arch.sie_block->fac = (u32)(u64) model->fac_list;
पूर्ण

अटल पूर्णांक kvm_s390_vcpu_setup(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc = 0;
	u16 uvrc, uvrrc;

	atomic_set(&vcpu->arch.sie_block->cpuflags, CPUSTAT_ZARCH |
						    CPUSTAT_SM |
						    CPUSTAT_STOPPED);

	अगर (test_kvm_facility(vcpu->kvm, 78))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_GED2);
	अन्यथा अगर (test_kvm_facility(vcpu->kvm, 8))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_GED);

	kvm_s390_vcpu_setup_model(vcpu);

	/* pgste_set_pte has special handling क्रम !MACHINE_HAS_ESOP */
	अगर (MACHINE_HAS_ESOP)
		vcpu->arch.sie_block->ecb |= ECB_HOSTPROTINT;
	अगर (test_kvm_facility(vcpu->kvm, 9))
		vcpu->arch.sie_block->ecb |= ECB_SRSI;
	अगर (test_kvm_facility(vcpu->kvm, 73))
		vcpu->arch.sie_block->ecb |= ECB_TE;

	अगर (test_kvm_facility(vcpu->kvm, 8) && vcpu->kvm->arch.use_pfmfi)
		vcpu->arch.sie_block->ecb2 |= ECB2_PFMFI;
	अगर (test_kvm_facility(vcpu->kvm, 130))
		vcpu->arch.sie_block->ecb2 |= ECB2_IEP;
	vcpu->arch.sie_block->eca = ECA_MVPGI | ECA_PROTEXCI;
	अगर (sclp.has_cei)
		vcpu->arch.sie_block->eca |= ECA_CEI;
	अगर (sclp.has_ib)
		vcpu->arch.sie_block->eca |= ECA_IB;
	अगर (sclp.has_siअगर)
		vcpu->arch.sie_block->eca |= ECA_SII;
	अगर (sclp.has_sigpअगर)
		vcpu->arch.sie_block->eca |= ECA_SIGPI;
	अगर (test_kvm_facility(vcpu->kvm, 129)) अणु
		vcpu->arch.sie_block->eca |= ECA_VX;
		vcpu->arch.sie_block->ecd |= ECD_HOSTREGMGMT;
	पूर्ण
	अगर (test_kvm_facility(vcpu->kvm, 139))
		vcpu->arch.sie_block->ecd |= ECD_MEF;
	अगर (test_kvm_facility(vcpu->kvm, 156))
		vcpu->arch.sie_block->ecd |= ECD_ETOKENF;
	अगर (vcpu->arch.sie_block->gd) अणु
		vcpu->arch.sie_block->eca |= ECA_AIV;
		VCPU_EVENT(vcpu, 3, "AIV gisa format-%u enabled for cpu %03u",
			   vcpu->arch.sie_block->gd & 0x3, vcpu->vcpu_id);
	पूर्ण
	vcpu->arch.sie_block->sdnxo = ((अचिन्हित दीर्घ) &vcpu->run->s.regs.sdnx)
					| SDNXC;
	vcpu->arch.sie_block->riccbd = (अचिन्हित दीर्घ) &vcpu->run->s.regs.riccb;

	अगर (sclp.has_kss)
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_KSS);
	अन्यथा
		vcpu->arch.sie_block->ictl |= ICTL_ISKE | ICTL_SSKE | ICTL_RRBE;

	अगर (vcpu->kvm->arch.use_cmma) अणु
		rc = kvm_s390_vcpu_setup_cmma(vcpu);
		अगर (rc)
			वापस rc;
	पूर्ण
	hrसमयr_init(&vcpu->arch.ckc_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	vcpu->arch.ckc_समयr.function = kvm_s390_idle_wakeup;

	vcpu->arch.sie_block->hpid = HPID_KVM;

	kvm_s390_vcpu_crypto_setup(vcpu);

	mutex_lock(&vcpu->kvm->lock);
	अगर (kvm_s390_pv_is_रक्षित(vcpu->kvm)) अणु
		rc = kvm_s390_pv_create_cpu(vcpu, &uvrc, &uvrrc);
		अगर (rc)
			kvm_s390_vcpu_unsetup_cmma(vcpu);
	पूर्ण
	mutex_unlock(&vcpu->kvm->lock);

	वापस rc;
पूर्ण

पूर्णांक kvm_arch_vcpu_precreate(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	अगर (!kvm_is_ucontrol(kvm) && !sca_can_add_vcpu(kvm, id))
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा sie_page *sie_page;
	पूर्णांक rc;

	BUILD_BUG_ON(माप(काष्ठा sie_page) != 4096);
	sie_page = (काष्ठा sie_page *) get_zeroed_page(GFP_KERNEL_ACCOUNT);
	अगर (!sie_page)
		वापस -ENOMEM;

	vcpu->arch.sie_block = &sie_page->sie_block;
	vcpu->arch.sie_block->itdba = (अचिन्हित दीर्घ) &sie_page->itdb;

	/* the real guest size will always be smaller than msl */
	vcpu->arch.sie_block->mso = 0;
	vcpu->arch.sie_block->msl = sclp.hamax;

	vcpu->arch.sie_block->icpua = vcpu->vcpu_id;
	spin_lock_init(&vcpu->arch.local_पूर्णांक.lock);
	vcpu->arch.sie_block->gd = (u32)(u64)vcpu->kvm->arch.gisa_पूर्णांक.origin;
	अगर (vcpu->arch.sie_block->gd && sclp.has_gisaf)
		vcpu->arch.sie_block->gd |= GISA_FORMAT1;
	seqcount_init(&vcpu->arch.cpuपंचांग_seqcount);

	vcpu->arch.pfault_token = KVM_S390_PFAULT_TOKEN_INVALID;
	kvm_clear_async_pf_completion_queue(vcpu);
	vcpu->run->kvm_valid_regs = KVM_SYNC_PREFIX |
				    KVM_SYNC_GPRS |
				    KVM_SYNC_ACRS |
				    KVM_SYNC_CRS |
				    KVM_SYNC_ARCH0 |
				    KVM_SYNC_PFAULT |
				    KVM_SYNC_DIAG318;
	kvm_s390_set_prefix(vcpu, 0);
	अगर (test_kvm_facility(vcpu->kvm, 64))
		vcpu->run->kvm_valid_regs |= KVM_SYNC_RICCB;
	अगर (test_kvm_facility(vcpu->kvm, 82))
		vcpu->run->kvm_valid_regs |= KVM_SYNC_BPBC;
	अगर (test_kvm_facility(vcpu->kvm, 133))
		vcpu->run->kvm_valid_regs |= KVM_SYNC_GSCB;
	अगर (test_kvm_facility(vcpu->kvm, 156))
		vcpu->run->kvm_valid_regs |= KVM_SYNC_ETOKEN;
	/* fprs can be synchronized via vrs, even अगर the guest has no vx. With
	 * MACHINE_HAS_VX, (load|store)_fpu_regs() will work with vrs क्रमmat.
	 */
	अगर (MACHINE_HAS_VX)
		vcpu->run->kvm_valid_regs |= KVM_SYNC_VRS;
	अन्यथा
		vcpu->run->kvm_valid_regs |= KVM_SYNC_FPRS;

	अगर (kvm_is_ucontrol(vcpu->kvm)) अणु
		rc = __kvm_ucontrol_vcpu_init(vcpu);
		अगर (rc)
			जाओ out_मुक्त_sie_block;
	पूर्ण

	VM_EVENT(vcpu->kvm, 3, "create cpu %d at 0x%pK, sie block at 0x%pK",
		 vcpu->vcpu_id, vcpu, vcpu->arch.sie_block);
	trace_kvm_s390_create_vcpu(vcpu->vcpu_id, vcpu, vcpu->arch.sie_block);

	rc = kvm_s390_vcpu_setup(vcpu);
	अगर (rc)
		जाओ out_ucontrol_uninit;
	वापस 0;

out_ucontrol_uninit:
	अगर (kvm_is_ucontrol(vcpu->kvm))
		gmap_हटाओ(vcpu->arch.gmap);
out_मुक्त_sie_block:
	मुक्त_page((अचिन्हित दीर्घ)(vcpu->arch.sie_block));
	वापस rc;
पूर्ण

पूर्णांक kvm_arch_vcpu_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_s390_vcpu_has_irq(vcpu, 0);
पूर्ण

bool kvm_arch_vcpu_in_kernel(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !(vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE);
पूर्ण

व्योम kvm_s390_vcpu_block(काष्ठा kvm_vcpu *vcpu)
अणु
	atomic_or(PROG_BLOCK_SIE, &vcpu->arch.sie_block->prog20);
	निकास_sie(vcpu);
पूर्ण

व्योम kvm_s390_vcpu_unblock(काष्ठा kvm_vcpu *vcpu)
अणु
	atomic_andnot(PROG_BLOCK_SIE, &vcpu->arch.sie_block->prog20);
पूर्ण

अटल व्योम kvm_s390_vcpu_request(काष्ठा kvm_vcpu *vcpu)
अणु
	atomic_or(PROG_REQUEST, &vcpu->arch.sie_block->prog20);
	निकास_sie(vcpu);
पूर्ण

bool kvm_s390_vcpu_sie_inhibited(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस atomic_पढ़ो(&vcpu->arch.sie_block->prog20) &
	       (PROG_BLOCK_SIE | PROG_REQUEST);
पूर्ण

अटल व्योम kvm_s390_vcpu_request_handled(काष्ठा kvm_vcpu *vcpu)
अणु
	atomic_andnot(PROG_REQUEST, &vcpu->arch.sie_block->prog20);
पूर्ण

/*
 * Kick a guest cpu out of (v)SIE and रुको until (v)SIE is not running.
 * If the CPU is not running (e.g. रुकोing as idle) the function will
 * वापस immediately. */
व्योम निकास_sie(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOP_INT);
	kvm_s390_vsie_kick(vcpu);
	जबतक (vcpu->arch.sie_block->prog0c & PROG_IN_SIE)
		cpu_relax();
पूर्ण

/* Kick a guest cpu out of SIE to process a request synchronously */
व्योम kvm_s390_sync_request(पूर्णांक req, काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_make_request(req, vcpu);
	kvm_s390_vcpu_request(vcpu);
पूर्ण

अटल व्योम kvm_gmap_notअगरier(काष्ठा gmap *gmap, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ end)
अणु
	काष्ठा kvm *kvm = gmap->निजी;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित दीर्घ prefix;
	पूर्णांक i;

	अगर (gmap_is_shaकरोw(gmap))
		वापस;
	अगर (start >= 1UL << 31)
		/* We are only पूर्णांकerested in prefix pages */
		वापस;
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		/* match against both prefix pages */
		prefix = kvm_s390_get_prefix(vcpu);
		अगर (prefix <= end && start <= prefix + 2*PAGE_SIZE - 1) अणु
			VCPU_EVENT(vcpu, 2, "gmap notifier for %lx-%lx",
				   start, end);
			kvm_s390_sync_request(KVM_REQ_MMU_RELOAD, vcpu);
		पूर्ण
	पूर्ण
पूर्ण

bool kvm_arch_no_poll(काष्ठा kvm_vcpu *vcpu)
अणु
	/* करो not poll with more than halt_poll_max_steal percent of steal समय */
	अगर (S390_lowcore.avg_steal_समयr * 100 / (TICK_USEC << 12) >=
	    halt_poll_max_steal) अणु
		vcpu->स्थिति.सalt_no_poll_steal++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक kvm_arch_vcpu_should_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	/* kvm common code refers to this, but never calls it */
	BUG();
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_get_one_reg(काष्ठा kvm_vcpu *vcpu,
					   काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक r = -EINVAL;

	चयन (reg->id) अणु
	हाल KVM_REG_S390_TODPR:
		r = put_user(vcpu->arch.sie_block->todpr,
			     (u32 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_EPOCHDIFF:
		r = put_user(vcpu->arch.sie_block->epoch,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_CPU_TIMER:
		r = put_user(kvm_s390_get_cpu_समयr(vcpu),
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_CLOCK_COMP:
		r = put_user(vcpu->arch.sie_block->ckc,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PFTOKEN:
		r = put_user(vcpu->arch.pfault_token,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PFCOMPARE:
		r = put_user(vcpu->arch.pfault_compare,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PFSELECT:
		r = put_user(vcpu->arch.pfault_select,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PP:
		r = put_user(vcpu->arch.sie_block->pp,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_GBEA:
		r = put_user(vcpu->arch.sie_block->gbea,
			     (u64 __user *)reg->addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_set_one_reg(काष्ठा kvm_vcpu *vcpu,
					   काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक r = -EINVAL;
	__u64 val;

	चयन (reg->id) अणु
	हाल KVM_REG_S390_TODPR:
		r = get_user(vcpu->arch.sie_block->todpr,
			     (u32 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_EPOCHDIFF:
		r = get_user(vcpu->arch.sie_block->epoch,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_CPU_TIMER:
		r = get_user(val, (u64 __user *)reg->addr);
		अगर (!r)
			kvm_s390_set_cpu_समयr(vcpu, val);
		अवरोध;
	हाल KVM_REG_S390_CLOCK_COMP:
		r = get_user(vcpu->arch.sie_block->ckc,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PFTOKEN:
		r = get_user(vcpu->arch.pfault_token,
			     (u64 __user *)reg->addr);
		अगर (vcpu->arch.pfault_token == KVM_S390_PFAULT_TOKEN_INVALID)
			kvm_clear_async_pf_completion_queue(vcpu);
		अवरोध;
	हाल KVM_REG_S390_PFCOMPARE:
		r = get_user(vcpu->arch.pfault_compare,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PFSELECT:
		r = get_user(vcpu->arch.pfault_select,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_PP:
		r = get_user(vcpu->arch.sie_block->pp,
			     (u64 __user *)reg->addr);
		अवरोध;
	हाल KVM_REG_S390_GBEA:
		r = get_user(vcpu->arch.sie_block->gbea,
			     (u64 __user *)reg->addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम kvm_arch_vcpu_ioctl_normal_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.sie_block->gpsw.mask &= ~PSW_MASK_RI;
	vcpu->arch.pfault_token = KVM_S390_PFAULT_TOKEN_INVALID;
	स_रखो(vcpu->run->s.regs.riccb, 0, माप(vcpu->run->s.regs.riccb));

	kvm_clear_async_pf_completion_queue(vcpu);
	अगर (!kvm_s390_user_cpu_state_ctrl(vcpu->kvm))
		kvm_s390_vcpu_stop(vcpu);
	kvm_s390_clear_local_irqs(vcpu);
पूर्ण

अटल व्योम kvm_arch_vcpu_ioctl_initial_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Initial reset is a superset of the normal reset */
	kvm_arch_vcpu_ioctl_normal_reset(vcpu);

	/*
	 * This equals initial cpu reset in pop, but we करोn't चयन to ESA.
	 * We करो not only reset the पूर्णांकernal data, but also ...
	 */
	vcpu->arch.sie_block->gpsw.mask = 0;
	vcpu->arch.sie_block->gpsw.addr = 0;
	kvm_s390_set_prefix(vcpu, 0);
	kvm_s390_set_cpu_समयr(vcpu, 0);
	vcpu->arch.sie_block->ckc = 0;
	स_रखो(vcpu->arch.sie_block->gcr, 0, माप(vcpu->arch.sie_block->gcr));
	vcpu->arch.sie_block->gcr[0] = CR0_INITIAL_MASK;
	vcpu->arch.sie_block->gcr[14] = CR14_INITIAL_MASK;

	/* ... the data in sync regs */
	स_रखो(vcpu->run->s.regs.crs, 0, माप(vcpu->run->s.regs.crs));
	vcpu->run->s.regs.ckc = 0;
	vcpu->run->s.regs.crs[0] = CR0_INITIAL_MASK;
	vcpu->run->s.regs.crs[14] = CR14_INITIAL_MASK;
	vcpu->run->psw_addr = 0;
	vcpu->run->psw_mask = 0;
	vcpu->run->s.regs.todpr = 0;
	vcpu->run->s.regs.cpuपंचांग = 0;
	vcpu->run->s.regs.ckc = 0;
	vcpu->run->s.regs.pp = 0;
	vcpu->run->s.regs.gbea = 1;
	vcpu->run->s.regs.fpc = 0;
	/*
	 * Do not reset these रेजिस्टरs in the रक्षित हाल, as some of
	 * them are overlayed and they are not accessible in this हाल
	 * anyway.
	 */
	अगर (!kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		vcpu->arch.sie_block->gbea = 1;
		vcpu->arch.sie_block->pp = 0;
		vcpu->arch.sie_block->fpf &= ~FPF_BPBC;
		vcpu->arch.sie_block->todpr = 0;
	पूर्ण
पूर्ण

अटल व्योम kvm_arch_vcpu_ioctl_clear_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_sync_regs *regs = &vcpu->run->s.regs;

	/* Clear reset is a superset of the initial reset */
	kvm_arch_vcpu_ioctl_initial_reset(vcpu);

	स_रखो(&regs->gprs, 0, माप(regs->gprs));
	स_रखो(&regs->vrs, 0, माप(regs->vrs));
	स_रखो(&regs->acrs, 0, माप(regs->acrs));
	स_रखो(&regs->gscb, 0, माप(regs->gscb));

	regs->etoken = 0;
	regs->etoken_extension = 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	vcpu_load(vcpu);
	स_नकल(&vcpu->run->s.regs.gprs, &regs->gprs, माप(regs->gprs));
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	vcpu_load(vcpu);
	स_नकल(&regs->gprs, &vcpu->run->s.regs.gprs, माप(regs->gprs));
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	vcpu_load(vcpu);

	स_नकल(&vcpu->run->s.regs.acrs, &sregs->acrs, माप(sregs->acrs));
	स_नकल(&vcpu->arch.sie_block->gcr, &sregs->crs, माप(sregs->crs));

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	vcpu_load(vcpu);

	स_नकल(&sregs->acrs, &vcpu->run->s.regs.acrs, माप(sregs->acrs));
	स_नकल(&sregs->crs, &vcpu->arch.sie_block->gcr, माप(sregs->crs));

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	पूर्णांक ret = 0;

	vcpu_load(vcpu);

	अगर (test_fp_ctl(fpu->fpc)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	vcpu->run->s.regs.fpc = fpu->fpc;
	अगर (MACHINE_HAS_VX)
		convert_fp_to_vx((__vector128 *) vcpu->run->s.regs.vrs,
				 (freg_t *) fpu->fprs);
	अन्यथा
		स_नकल(vcpu->run->s.regs.fprs, &fpu->fprs, माप(fpu->fprs));

out:
	vcpu_put(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	vcpu_load(vcpu);

	/* make sure we have the latest values */
	save_fpu_regs();
	अगर (MACHINE_HAS_VX)
		convert_vx_to_fp((freg_t *) fpu->fprs,
				 (__vector128 *) vcpu->run->s.regs.vrs);
	अन्यथा
		स_नकल(fpu->fprs, vcpu->run->s.regs.fprs, माप(fpu->fprs));
	fpu->fpc = vcpu->run->s.regs.fpc;

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_set_initial_psw(काष्ठा kvm_vcpu *vcpu, psw_t psw)
अणु
	पूर्णांक rc = 0;

	अगर (!is_vcpu_stopped(vcpu))
		rc = -EBUSY;
	अन्यथा अणु
		vcpu->run->psw_mask = psw.mask;
		vcpu->run->psw_addr = psw.addr;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_translation *tr)
अणु
	वापस -EINVAL; /* not implemented yet */
पूर्ण

#घोषणा VALID_GUESTDBG_FLAGS (KVM_GUESTDBG_SINGLESTEP | \
			      KVM_GUESTDBG_USE_HW_BP | \
			      KVM_GUESTDBG_ENABLE)

पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_guest_debug *dbg)
अणु
	पूर्णांक rc = 0;

	vcpu_load(vcpu);

	vcpu->guest_debug = 0;
	kvm_s390_clear_bp_data(vcpu);

	अगर (dbg->control & ~VALID_GUESTDBG_FLAGS) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (!sclp.has_gpere) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (dbg->control & KVM_GUESTDBG_ENABLE) अणु
		vcpu->guest_debug = dbg->control;
		/* enक्रमce guest PER */
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_P);

		अगर (dbg->control & KVM_GUESTDBG_USE_HW_BP)
			rc = kvm_s390_import_bp_data(vcpu, dbg);
	पूर्ण अन्यथा अणु
		kvm_s390_clear_cpuflags(vcpu, CPUSTAT_P);
		vcpu->arch.guestdbg.last_bp = 0;
	पूर्ण

	अगर (rc) अणु
		vcpu->guest_debug = 0;
		kvm_s390_clear_bp_data(vcpu);
		kvm_s390_clear_cpuflags(vcpu, CPUSTAT_P);
	पूर्ण

out:
	vcpu_put(vcpu);
	वापस rc;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	पूर्णांक ret;

	vcpu_load(vcpu);

	/* CHECK_STOP and LOAD are not supported yet */
	ret = is_vcpu_stopped(vcpu) ? KVM_MP_STATE_STOPPED :
				      KVM_MP_STATE_OPERATING;

	vcpu_put(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	पूर्णांक rc = 0;

	vcpu_load(vcpu);

	/* user space knows about this पूर्णांकerface - let it control the state */
	vcpu->kvm->arch.user_cpu_state_ctrl = 1;

	चयन (mp_state->mp_state) अणु
	हाल KVM_MP_STATE_STOPPED:
		rc = kvm_s390_vcpu_stop(vcpu);
		अवरोध;
	हाल KVM_MP_STATE_OPERATING:
		rc = kvm_s390_vcpu_start(vcpu);
		अवरोध;
	हाल KVM_MP_STATE_LOAD:
		अगर (!kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			rc = -ENXIO;
			अवरोध;
		पूर्ण
		rc = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_OPR_LOAD);
		अवरोध;
	हाल KVM_MP_STATE_CHECK_STOP:
		fallthrough;	/* CHECK_STOP and LOAD are not supported yet */
	शेष:
		rc = -ENXIO;
	पूर्ण

	vcpu_put(vcpu);
	वापस rc;
पूर्ण

अटल bool ibs_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_s390_test_cpuflags(vcpu, CPUSTAT_IBS);
पूर्ण

अटल पूर्णांक kvm_s390_handle_requests(काष्ठा kvm_vcpu *vcpu)
अणु
retry:
	kvm_s390_vcpu_request_handled(vcpu);
	अगर (!kvm_request_pending(vcpu))
		वापस 0;
	/*
	 * We use MMU_RELOAD just to re-arm the ipte notअगरier क्रम the
	 * guest prefix page. gmap_mprotect_notअगरy will रुको on the ptl lock.
	 * This ensures that the ipte inकाष्ठाion क्रम this request has
	 * alपढ़ोy finished. We might race against a second unmapper that
	 * wants to set the blocking bit. Lets just retry the request loop.
	 */
	अगर (kvm_check_request(KVM_REQ_MMU_RELOAD, vcpu)) अणु
		पूर्णांक rc;
		rc = gmap_mprotect_notअगरy(vcpu->arch.gmap,
					  kvm_s390_get_prefix(vcpu),
					  PAGE_SIZE * 2, PROT_WRITE);
		अगर (rc) अणु
			kvm_make_request(KVM_REQ_MMU_RELOAD, vcpu);
			वापस rc;
		पूर्ण
		जाओ retry;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu)) अणु
		vcpu->arch.sie_block->ihcpu = 0xffff;
		जाओ retry;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_ENABLE_IBS, vcpu)) अणु
		अगर (!ibs_enabled(vcpu)) अणु
			trace_kvm_s390_enable_disable_ibs(vcpu->vcpu_id, 1);
			kvm_s390_set_cpuflags(vcpu, CPUSTAT_IBS);
		पूर्ण
		जाओ retry;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_DISABLE_IBS, vcpu)) अणु
		अगर (ibs_enabled(vcpu)) अणु
			trace_kvm_s390_enable_disable_ibs(vcpu->vcpu_id, 0);
			kvm_s390_clear_cpuflags(vcpu, CPUSTAT_IBS);
		पूर्ण
		जाओ retry;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_ICPT_OPEREXC, vcpu)) अणु
		vcpu->arch.sie_block->ictl |= ICTL_OPEREXC;
		जाओ retry;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_START_MIGRATION, vcpu)) अणु
		/*
		 * Disable CMM भवization; we will emulate the ESSA
		 * inकाष्ठाion manually, in order to provide additional
		 * functionalities needed क्रम live migration.
		 */
		vcpu->arch.sie_block->ecb2 &= ~ECB2_CMMA;
		जाओ retry;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_STOP_MIGRATION, vcpu)) अणु
		/*
		 * Re-enable CMM भवization अगर CMMA is available and
		 * CMM has been used.
		 */
		अगर ((vcpu->kvm->arch.use_cmma) &&
		    (vcpu->kvm->mm->context.uses_cmm))
			vcpu->arch.sie_block->ecb2 |= ECB2_CMMA;
		जाओ retry;
	पूर्ण

	/* nothing to करो, just clear the request */
	kvm_clear_request(KVM_REQ_UNHALT, vcpu);
	/* we left the vsie handler, nothing to करो, just clear the request */
	kvm_clear_request(KVM_REQ_VSIE_RESTART, vcpu);

	वापस 0;
पूर्ण

व्योम kvm_s390_set_tod_घड़ी(काष्ठा kvm *kvm,
			    स्थिर काष्ठा kvm_s390_vm_tod_घड़ी *gtod)
अणु
	काष्ठा kvm_vcpu *vcpu;
	जोड़ tod_घड़ी clk;
	पूर्णांक i;

	mutex_lock(&kvm->lock);
	preempt_disable();

	store_tod_घड़ी_ext(&clk);

	kvm->arch.epoch = gtod->tod - clk.tod;
	kvm->arch.epdx = 0;
	अगर (test_kvm_facility(kvm, 139)) अणु
		kvm->arch.epdx = gtod->epoch_idx - clk.ei;
		अगर (kvm->arch.epoch > gtod->tod)
			kvm->arch.epdx -= 1;
	पूर्ण

	kvm_s390_vcpu_block_all(kvm);
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		vcpu->arch.sie_block->epoch = kvm->arch.epoch;
		vcpu->arch.sie_block->epdx  = kvm->arch.epdx;
	पूर्ण

	kvm_s390_vcpu_unblock_all(kvm);
	preempt_enable();
	mutex_unlock(&kvm->lock);
पूर्ण

/**
 * kvm_arch_fault_in_page - fault-in guest page अगर necessary
 * @vcpu: The corresponding भव cpu
 * @gpa: Guest physical address
 * @writable: Whether the page should be writable or not
 *
 * Make sure that a guest page has been faulted-in on the host.
 *
 * Return: Zero on success, negative error code otherwise.
 */
दीर्घ kvm_arch_fault_in_page(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, पूर्णांक writable)
अणु
	वापस gmap_fault(vcpu->arch.gmap, gpa,
			  writable ? FAULT_FLAG_WRITE : 0);
पूर्ण

अटल व्योम __kvm_inject_pfault_token(काष्ठा kvm_vcpu *vcpu, bool start_token,
				      अचिन्हित दीर्घ token)
अणु
	काष्ठा kvm_s390_पूर्णांकerrupt पूर्णांकi;
	काष्ठा kvm_s390_irq irq;

	अगर (start_token) अणु
		irq.u.ext.ext_params2 = token;
		irq.type = KVM_S390_INT_PFAULT_INIT;
		WARN_ON_ONCE(kvm_s390_inject_vcpu(vcpu, &irq));
	पूर्ण अन्यथा अणु
		पूर्णांकi.type = KVM_S390_INT_PFAULT_DONE;
		पूर्णांकi.parm64 = token;
		WARN_ON_ONCE(kvm_s390_inject_vm(vcpu->kvm, &पूर्णांकi));
	पूर्ण
पूर्ण

bool kvm_arch_async_page_not_present(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_async_pf *work)
अणु
	trace_kvm_s390_pfault_init(vcpu, work->arch.pfault_token);
	__kvm_inject_pfault_token(vcpu, true, work->arch.pfault_token);

	वापस true;
पूर्ण

व्योम kvm_arch_async_page_present(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_async_pf *work)
अणु
	trace_kvm_s390_pfault_करोne(vcpu, work->arch.pfault_token);
	__kvm_inject_pfault_token(vcpu, false, work->arch.pfault_token);
पूर्ण

व्योम kvm_arch_async_page_पढ़ोy(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_async_pf *work)
अणु
	/* s390 will always inject the page directly */
पूर्ण

bool kvm_arch_can_dequeue_async_page_present(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * s390 will always inject the page directly,
	 * but we still want check_async_completion to cleanup
	 */
	वापस true;
पूर्ण

अटल bool kvm_arch_setup_async_pf(काष्ठा kvm_vcpu *vcpu)
अणु
	hva_t hva;
	काष्ठा kvm_arch_async_pf arch;

	अगर (vcpu->arch.pfault_token == KVM_S390_PFAULT_TOKEN_INVALID)
		वापस false;
	अगर ((vcpu->arch.sie_block->gpsw.mask & vcpu->arch.pfault_select) !=
	    vcpu->arch.pfault_compare)
		वापस false;
	अगर (psw_extपूर्णांक_disabled(vcpu))
		वापस false;
	अगर (kvm_s390_vcpu_has_irq(vcpu, 0))
		वापस false;
	अगर (!(vcpu->arch.sie_block->gcr[0] & CR0_SERVICE_SIGNAL_SUBMASK))
		वापस false;
	अगर (!vcpu->arch.gmap->pfault_enabled)
		वापस false;

	hva = gfn_to_hva(vcpu->kvm, gpa_to_gfn(current->thपढ़ो.gmap_addr));
	hva += current->thपढ़ो.gmap_addr & ~PAGE_MASK;
	अगर (पढ़ो_guest_real(vcpu, vcpu->arch.pfault_token, &arch.pfault_token, 8))
		वापस false;

	वापस kvm_setup_async_pf(vcpu, current->thपढ़ो.gmap_addr, hva, &arch);
पूर्ण

अटल पूर्णांक vcpu_pre_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc, cpuflags;

	/*
	 * On s390 notअगरications क्रम arriving pages will be delivered directly
	 * to the guest but the house keeping क्रम completed pfaults is
	 * handled outside the worker.
	 */
	kvm_check_async_pf_completion(vcpu);

	vcpu->arch.sie_block->gg14 = vcpu->run->s.regs.gprs[14];
	vcpu->arch.sie_block->gg15 = vcpu->run->s.regs.gprs[15];

	अगर (need_resched())
		schedule();

	अगर (!kvm_is_ucontrol(vcpu->kvm)) अणु
		rc = kvm_s390_deliver_pending_पूर्णांकerrupts(vcpu);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = kvm_s390_handle_requests(vcpu);
	अगर (rc)
		वापस rc;

	अगर (guestdbg_enabled(vcpu)) अणु
		kvm_s390_backup_guest_per_regs(vcpu);
		kvm_s390_patch_guest_per_regs(vcpu);
	पूर्ण

	clear_bit(vcpu->vcpu_id, vcpu->kvm->arch.gisa_पूर्णांक.kicked_mask);

	vcpu->arch.sie_block->icptcode = 0;
	cpuflags = atomic_पढ़ो(&vcpu->arch.sie_block->cpuflags);
	VCPU_EVENT(vcpu, 6, "entering sie flags %x", cpuflags);
	trace_kvm_s390_sie_enter(vcpu, cpuflags);

	वापस 0;
पूर्ण

अटल पूर्णांक vcpu_post_run_fault_in_sie(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_pgm_info pgm_info = अणु
		.code = PGM_ADDRESSING,
	पूर्ण;
	u8 opcode, ilen;
	पूर्णांक rc;

	VCPU_EVENT(vcpu, 3, "%s", "fault in sie instruction");
	trace_kvm_s390_sie_fault(vcpu);

	/*
	 * We want to inject an addressing exception, which is defined as a
	 * suppressing or terminating exception. However, since we came here
	 * by a DAT access exception, the PSW still poपूर्णांकs to the faulting
	 * inकाष्ठाion since DAT exceptions are nullअगरying. So we've got
	 * to look up the current opcode to get the length of the inकाष्ठाion
	 * to be able to क्रमward the PSW.
	 */
	rc = पढ़ो_guest_instr(vcpu, vcpu->arch.sie_block->gpsw.addr, &opcode, 1);
	ilen = insn_length(opcode);
	अगर (rc < 0) अणु
		वापस rc;
	पूर्ण अन्यथा अगर (rc) अणु
		/* Inकाष्ठाion-Fetching Exceptions - we can't detect the ilen.
		 * Forward by arbitrary ilc, injection will take care of
		 * nullअगरication अगर necessary.
		 */
		pgm_info = vcpu->arch.pgm;
		ilen = 4;
	पूर्ण
	pgm_info.flags = ilen | KVM_S390_PGM_FLAGS_ILC_VALID;
	kvm_s390_क्रमward_psw(vcpu, ilen);
	वापस kvm_s390_inject_prog_irq(vcpu, &pgm_info);
पूर्ण

अटल पूर्णांक vcpu_post_run(काष्ठा kvm_vcpu *vcpu, पूर्णांक निकास_reason)
अणु
	काष्ठा mcck_अस्थिर_info *mcck_info;
	काष्ठा sie_page *sie_page;

	VCPU_EVENT(vcpu, 6, "exit sie icptcode %d",
		   vcpu->arch.sie_block->icptcode);
	trace_kvm_s390_sie_निकास(vcpu, vcpu->arch.sie_block->icptcode);

	अगर (guestdbg_enabled(vcpu))
		kvm_s390_restore_guest_per_regs(vcpu);

	vcpu->run->s.regs.gprs[14] = vcpu->arch.sie_block->gg14;
	vcpu->run->s.regs.gprs[15] = vcpu->arch.sie_block->gg15;

	अगर (निकास_reason == -EINTR) अणु
		VCPU_EVENT(vcpu, 3, "%s", "machine check");
		sie_page = container_of(vcpu->arch.sie_block,
					काष्ठा sie_page, sie_block);
		mcck_info = &sie_page->mcck_info;
		kvm_s390_reinject_machine_check(vcpu, mcck_info);
		वापस 0;
	पूर्ण

	अगर (vcpu->arch.sie_block->icptcode > 0) अणु
		पूर्णांक rc = kvm_handle_sie_पूर्णांकercept(vcpu);

		अगर (rc != -EOPNOTSUPP)
			वापस rc;
		vcpu->run->निकास_reason = KVM_EXIT_S390_SIEIC;
		vcpu->run->s390_sieic.icptcode = vcpu->arch.sie_block->icptcode;
		vcpu->run->s390_sieic.ipa = vcpu->arch.sie_block->ipa;
		vcpu->run->s390_sieic.ipb = vcpu->arch.sie_block->ipb;
		वापस -EREMOTE;
	पूर्ण अन्यथा अगर (निकास_reason != -EFAULT) अणु
		vcpu->stat.निकास_null++;
		वापस 0;
	पूर्ण अन्यथा अगर (kvm_is_ucontrol(vcpu->kvm)) अणु
		vcpu->run->निकास_reason = KVM_EXIT_S390_UCONTROL;
		vcpu->run->s390_ucontrol.trans_exc_code =
						current->thपढ़ो.gmap_addr;
		vcpu->run->s390_ucontrol.pgm_code = 0x10;
		वापस -EREMOTE;
	पूर्ण अन्यथा अगर (current->thपढ़ो.gmap_pfault) अणु
		trace_kvm_s390_major_guest_pfault(vcpu);
		current->thपढ़ो.gmap_pfault = 0;
		अगर (kvm_arch_setup_async_pf(vcpu))
			वापस 0;
		vcpu->stat.pfault_sync++;
		वापस kvm_arch_fault_in_page(vcpu, current->thपढ़ो.gmap_addr, 1);
	पूर्ण
	वापस vcpu_post_run_fault_in_sie(vcpu);
पूर्ण

#घोषणा PSW_INT_MASK (PSW_MASK_EXT | PSW_MASK_IO | PSW_MASK_MCHECK)
अटल पूर्णांक __vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc, निकास_reason;
	काष्ठा sie_page *sie_page = (काष्ठा sie_page *)vcpu->arch.sie_block;

	/*
	 * We try to hold kvm->srcu during most of vcpu_run (except when run-
	 * ning the guest), so that memslots (and other stuff) are रक्षित
	 */
	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	करो अणु
		rc = vcpu_pre_run(vcpu);
		अगर (rc)
			अवरोध;

		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
		/*
		 * As PF_VCPU will be used in fault handler, between
		 * guest_enter and guest_निकास should be no uaccess.
		 */
		local_irq_disable();
		guest_enter_irqoff();
		__disable_cpu_समयr_accounting(vcpu);
		local_irq_enable();
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			स_नकल(sie_page->pv_grregs,
			       vcpu->run->s.regs.gprs,
			       माप(sie_page->pv_grregs));
		पूर्ण
		अगर (test_cpu_flag(CIF_FPU))
			load_fpu_regs();
		निकास_reason = sie64a(vcpu->arch.sie_block,
				     vcpu->run->s.regs.gprs);
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			स_नकल(vcpu->run->s.regs.gprs,
			       sie_page->pv_grregs,
			       माप(sie_page->pv_grregs));
			/*
			 * We're not allowed to inject पूर्णांकerrupts on पूर्णांकercepts
			 * that leave the guest state in an "in-between" state
			 * where the next SIE entry will करो a continuation.
			 * Fence पूर्णांकerrupts in our "internal" PSW.
			 */
			अगर (vcpu->arch.sie_block->icptcode == ICPT_PV_INSTR ||
			    vcpu->arch.sie_block->icptcode == ICPT_PV_PREF) अणु
				vcpu->arch.sie_block->gpsw.mask &= ~PSW_INT_MASK;
			पूर्ण
		पूर्ण
		local_irq_disable();
		__enable_cpu_समयr_accounting(vcpu);
		guest_निकास_irqoff();
		local_irq_enable();
		vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

		rc = vcpu_post_run(vcpu, निकास_reason);
	पूर्ण जबतक (!संकेत_pending(current) && !guestdbg_निकास_pending(vcpu) && !rc);

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	वापस rc;
पूर्ण

अटल व्योम sync_regs_fmt2(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;
	काष्ठा runसमय_instr_cb *riccb;
	काष्ठा gs_cb *gscb;

	riccb = (काष्ठा runसमय_instr_cb *) &kvm_run->s.regs.riccb;
	gscb = (काष्ठा gs_cb *) &kvm_run->s.regs.gscb;
	vcpu->arch.sie_block->gpsw.mask = kvm_run->psw_mask;
	vcpu->arch.sie_block->gpsw.addr = kvm_run->psw_addr;
	अगर (kvm_run->kvm_dirty_regs & KVM_SYNC_ARCH0) अणु
		vcpu->arch.sie_block->todpr = kvm_run->s.regs.todpr;
		vcpu->arch.sie_block->pp = kvm_run->s.regs.pp;
		vcpu->arch.sie_block->gbea = kvm_run->s.regs.gbea;
	पूर्ण
	अगर (kvm_run->kvm_dirty_regs & KVM_SYNC_PFAULT) अणु
		vcpu->arch.pfault_token = kvm_run->s.regs.pft;
		vcpu->arch.pfault_select = kvm_run->s.regs.pfs;
		vcpu->arch.pfault_compare = kvm_run->s.regs.pfc;
		अगर (vcpu->arch.pfault_token == KVM_S390_PFAULT_TOKEN_INVALID)
			kvm_clear_async_pf_completion_queue(vcpu);
	पूर्ण
	अगर (kvm_run->kvm_dirty_regs & KVM_SYNC_DIAG318) अणु
		vcpu->arch.diag318_info.val = kvm_run->s.regs.diag318;
		vcpu->arch.sie_block->cpnc = vcpu->arch.diag318_info.cpnc;
	पूर्ण
	/*
	 * If userspace sets the riccb (e.g. after migration) to a valid state,
	 * we should enable RI here instead of करोing the lazy enablement.
	 */
	अगर ((kvm_run->kvm_dirty_regs & KVM_SYNC_RICCB) &&
	    test_kvm_facility(vcpu->kvm, 64) &&
	    riccb->v &&
	    !(vcpu->arch.sie_block->ecb3 & ECB3_RI)) अणु
		VCPU_EVENT(vcpu, 3, "%s", "ENABLE: RI (sync_regs)");
		vcpu->arch.sie_block->ecb3 |= ECB3_RI;
	पूर्ण
	/*
	 * If userspace sets the gscb (e.g. after migration) to non-zero,
	 * we should enable GS here instead of करोing the lazy enablement.
	 */
	अगर ((kvm_run->kvm_dirty_regs & KVM_SYNC_GSCB) &&
	    test_kvm_facility(vcpu->kvm, 133) &&
	    gscb->gssm &&
	    !vcpu->arch.gs_enabled) अणु
		VCPU_EVENT(vcpu, 3, "%s", "ENABLE: GS (sync_regs)");
		vcpu->arch.sie_block->ecb |= ECB_GS;
		vcpu->arch.sie_block->ecd |= ECD_HOSTREGMGMT;
		vcpu->arch.gs_enabled = 1;
	पूर्ण
	अगर ((kvm_run->kvm_dirty_regs & KVM_SYNC_BPBC) &&
	    test_kvm_facility(vcpu->kvm, 82)) अणु
		vcpu->arch.sie_block->fpf &= ~FPF_BPBC;
		vcpu->arch.sie_block->fpf |= kvm_run->s.regs.bpbc ? FPF_BPBC : 0;
	पूर्ण
	अगर (MACHINE_HAS_GS) अणु
		preempt_disable();
		__ctl_set_bit(2, 4);
		अगर (current->thपढ़ो.gs_cb) अणु
			vcpu->arch.host_gscb = current->thपढ़ो.gs_cb;
			save_gs_cb(vcpu->arch.host_gscb);
		पूर्ण
		अगर (vcpu->arch.gs_enabled) अणु
			current->thपढ़ो.gs_cb = (काष्ठा gs_cb *)
						&vcpu->run->s.regs.gscb;
			restore_gs_cb(current->thपढ़ो.gs_cb);
		पूर्ण
		preempt_enable();
	पूर्ण
	/* SIE will load etoken directly from SDNX and thereक्रमe kvm_run */
पूर्ण

अटल व्योम sync_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;

	अगर (kvm_run->kvm_dirty_regs & KVM_SYNC_PREFIX)
		kvm_s390_set_prefix(vcpu, kvm_run->s.regs.prefix);
	अगर (kvm_run->kvm_dirty_regs & KVM_SYNC_CRS) अणु
		स_नकल(&vcpu->arch.sie_block->gcr, &kvm_run->s.regs.crs, 128);
		/* some control रेजिस्टर changes require a tlb flush */
		kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	पूर्ण
	अगर (kvm_run->kvm_dirty_regs & KVM_SYNC_ARCH0) अणु
		kvm_s390_set_cpu_समयr(vcpu, kvm_run->s.regs.cpuपंचांग);
		vcpu->arch.sie_block->ckc = kvm_run->s.regs.ckc;
	पूर्ण
	save_access_regs(vcpu->arch.host_acrs);
	restore_access_regs(vcpu->run->s.regs.acrs);
	/* save host (userspace) fprs/vrs */
	save_fpu_regs();
	vcpu->arch.host_fpregs.fpc = current->thपढ़ो.fpu.fpc;
	vcpu->arch.host_fpregs.regs = current->thपढ़ो.fpu.regs;
	अगर (MACHINE_HAS_VX)
		current->thपढ़ो.fpu.regs = vcpu->run->s.regs.vrs;
	अन्यथा
		current->thपढ़ो.fpu.regs = vcpu->run->s.regs.fprs;
	current->thपढ़ो.fpu.fpc = vcpu->run->s.regs.fpc;
	अगर (test_fp_ctl(current->thपढ़ो.fpu.fpc))
		/* User space provided an invalid FPC, let's clear it */
		current->thपढ़ो.fpu.fpc = 0;

	/* Sync fmt2 only data */
	अगर (likely(!kvm_s390_pv_cpu_is_रक्षित(vcpu))) अणु
		sync_regs_fmt2(vcpu);
	पूर्ण अन्यथा अणु
		/*
		 * In several places we have to modअगरy our पूर्णांकernal view to
		 * not करो things that are disallowed by the ultravisor. For
		 * example we must not inject पूर्णांकerrupts after specअगरic निकासs
		 * (e.g. 112 prefix page not secure). We करो this by turning
		 * off the machine check, बाह्यal and I/O पूर्णांकerrupt bits
		 * of our PSW copy. To aव्योम getting validity पूर्णांकercepts, we
		 * करो only accept the condition code from userspace.
		 */
		vcpu->arch.sie_block->gpsw.mask &= ~PSW_MASK_CC;
		vcpu->arch.sie_block->gpsw.mask |= kvm_run->psw_mask &
						   PSW_MASK_CC;
	पूर्ण

	kvm_run->kvm_dirty_regs = 0;
पूर्ण

अटल व्योम store_regs_fmt2(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;

	kvm_run->s.regs.todpr = vcpu->arch.sie_block->todpr;
	kvm_run->s.regs.pp = vcpu->arch.sie_block->pp;
	kvm_run->s.regs.gbea = vcpu->arch.sie_block->gbea;
	kvm_run->s.regs.bpbc = (vcpu->arch.sie_block->fpf & FPF_BPBC) == FPF_BPBC;
	kvm_run->s.regs.diag318 = vcpu->arch.diag318_info.val;
	अगर (MACHINE_HAS_GS) अणु
		preempt_disable();
		__ctl_set_bit(2, 4);
		अगर (vcpu->arch.gs_enabled)
			save_gs_cb(current->thपढ़ो.gs_cb);
		current->thपढ़ो.gs_cb = vcpu->arch.host_gscb;
		restore_gs_cb(vcpu->arch.host_gscb);
		अगर (!vcpu->arch.host_gscb)
			__ctl_clear_bit(2, 4);
		vcpu->arch.host_gscb = शून्य;
		preempt_enable();
	पूर्ण
	/* SIE will save etoken directly पूर्णांकo SDNX and thereक्रमe kvm_run */
पूर्ण

अटल व्योम store_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;

	kvm_run->psw_mask = vcpu->arch.sie_block->gpsw.mask;
	kvm_run->psw_addr = vcpu->arch.sie_block->gpsw.addr;
	kvm_run->s.regs.prefix = kvm_s390_get_prefix(vcpu);
	स_नकल(&kvm_run->s.regs.crs, &vcpu->arch.sie_block->gcr, 128);
	kvm_run->s.regs.cpuपंचांग = kvm_s390_get_cpu_समयr(vcpu);
	kvm_run->s.regs.ckc = vcpu->arch.sie_block->ckc;
	kvm_run->s.regs.pft = vcpu->arch.pfault_token;
	kvm_run->s.regs.pfs = vcpu->arch.pfault_select;
	kvm_run->s.regs.pfc = vcpu->arch.pfault_compare;
	save_access_regs(vcpu->run->s.regs.acrs);
	restore_access_regs(vcpu->arch.host_acrs);
	/* Save guest रेजिस्टर state */
	save_fpu_regs();
	vcpu->run->s.regs.fpc = current->thपढ़ो.fpu.fpc;
	/* Restore will be करोne lazily at वापस */
	current->thपढ़ो.fpu.fpc = vcpu->arch.host_fpregs.fpc;
	current->thपढ़ो.fpu.regs = vcpu->arch.host_fpregs.regs;
	अगर (likely(!kvm_s390_pv_cpu_is_रक्षित(vcpu)))
		store_regs_fmt2(vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;
	पूर्णांक rc;

	अगर (kvm_run->immediate_निकास)
		वापस -EINTR;

	अगर (kvm_run->kvm_valid_regs & ~KVM_SYNC_S390_VALID_FIELDS ||
	    kvm_run->kvm_dirty_regs & ~KVM_SYNC_S390_VALID_FIELDS)
		वापस -EINVAL;

	vcpu_load(vcpu);

	अगर (guestdbg_निकास_pending(vcpu)) अणु
		kvm_s390_prepare_debug_निकास(vcpu);
		rc = 0;
		जाओ out;
	पूर्ण

	kvm_sigset_activate(vcpu);

	/*
	 * no need to check the वापस value of vcpu_start as it can only have
	 * an error क्रम protvirt, but protvirt means user cpu state
	 */
	अगर (!kvm_s390_user_cpu_state_ctrl(vcpu->kvm)) अणु
		kvm_s390_vcpu_start(vcpu);
	पूर्ण अन्यथा अगर (is_vcpu_stopped(vcpu)) अणु
		pr_err_ratelimited("can't run stopped vcpu %d\n",
				   vcpu->vcpu_id);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	sync_regs(vcpu);
	enable_cpu_समयr_accounting(vcpu);

	might_fault();
	rc = __vcpu_run(vcpu);

	अगर (संकेत_pending(current) && !rc) अणु
		kvm_run->निकास_reason = KVM_EXIT_INTR;
		rc = -EINTR;
	पूर्ण

	अगर (guestdbg_निकास_pending(vcpu) && !rc)  अणु
		kvm_s390_prepare_debug_निकास(vcpu);
		rc = 0;
	पूर्ण

	अगर (rc == -EREMOTE) अणु
		/* userspace support is needed, kvm_run has been prepared */
		rc = 0;
	पूर्ण

	disable_cpu_समयr_accounting(vcpu);
	store_regs(vcpu);

	kvm_sigset_deactivate(vcpu);

	vcpu->stat.निकास_userspace++;
out:
	vcpu_put(vcpu);
	वापस rc;
पूर्ण

/*
 * store status at address
 * we use have two special हालs:
 * KVM_S390_STORE_STATUS_NOADDR: -> 0x1200 on 64 bit
 * KVM_S390_STORE_STATUS_PREFIXED: -> prefix
 */
पूर्णांक kvm_s390_store_status_unloaded(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gpa)
अणु
	अचिन्हित अक्षर archmode = 1;
	freg_t fprs[NUM_FPRS];
	अचिन्हित पूर्णांक px;
	u64 clkcomp, cpuपंचांग;
	पूर्णांक rc;

	px = kvm_s390_get_prefix(vcpu);
	अगर (gpa == KVM_S390_STORE_STATUS_NOADDR) अणु
		अगर (ग_लिखो_guest_असल(vcpu, 163, &archmode, 1))
			वापस -EFAULT;
		gpa = 0;
	पूर्ण अन्यथा अगर (gpa == KVM_S390_STORE_STATUS_PREFIXED) अणु
		अगर (ग_लिखो_guest_real(vcpu, 163, &archmode, 1))
			वापस -EFAULT;
		gpa = px;
	पूर्ण अन्यथा
		gpa -= __LC_FPREGS_SAVE_AREA;

	/* manually convert vector रेजिस्टरs अगर necessary */
	अगर (MACHINE_HAS_VX) अणु
		convert_vx_to_fp(fprs, (__vector128 *) vcpu->run->s.regs.vrs);
		rc = ग_लिखो_guest_असल(vcpu, gpa + __LC_FPREGS_SAVE_AREA,
				     fprs, 128);
	पूर्ण अन्यथा अणु
		rc = ग_लिखो_guest_असल(vcpu, gpa + __LC_FPREGS_SAVE_AREA,
				     vcpu->run->s.regs.fprs, 128);
	पूर्ण
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_GPREGS_SAVE_AREA,
			      vcpu->run->s.regs.gprs, 128);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_PSW_SAVE_AREA,
			      &vcpu->arch.sie_block->gpsw, 16);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_PREFIX_SAVE_AREA,
			      &px, 4);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_FP_CREG_SAVE_AREA,
			      &vcpu->run->s.regs.fpc, 4);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_TOD_PROGREG_SAVE_AREA,
			      &vcpu->arch.sie_block->todpr, 4);
	cpuपंचांग = kvm_s390_get_cpu_समयr(vcpu);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_CPU_TIMER_SAVE_AREA,
			      &cpuपंचांग, 8);
	clkcomp = vcpu->arch.sie_block->ckc >> 8;
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_CLOCK_COMP_SAVE_AREA,
			      &clkcomp, 8);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_AREGS_SAVE_AREA,
			      &vcpu->run->s.regs.acrs, 64);
	rc |= ग_लिखो_guest_असल(vcpu, gpa + __LC_CREGS_SAVE_AREA,
			      &vcpu->arch.sie_block->gcr, 128);
	वापस rc ? -EFAULT : 0;
पूर्ण

पूर्णांक kvm_s390_vcpu_store_status(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr)
अणु
	/*
	 * The guest FPRS and ACRS are in the host FPRS/ACRS due to the lazy
	 * चयन in the run ioctl. Let's update our copies beक्रमe we save
	 * it पूर्णांकo the save area
	 */
	save_fpu_regs();
	vcpu->run->s.regs.fpc = current->thपढ़ो.fpu.fpc;
	save_access_regs(vcpu->run->s.regs.acrs);

	वापस kvm_s390_store_status_unloaded(vcpu, addr);
पूर्ण

अटल व्योम __disable_ibs_on_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_check_request(KVM_REQ_ENABLE_IBS, vcpu);
	kvm_s390_sync_request(KVM_REQ_DISABLE_IBS, vcpu);
पूर्ण

अटल व्योम __disable_ibs_on_all_vcpus(काष्ठा kvm *kvm)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		__disable_ibs_on_vcpu(vcpu);
	पूर्ण
पूर्ण

अटल व्योम __enable_ibs_on_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!sclp.has_ibs)
		वापस;
	kvm_check_request(KVM_REQ_DISABLE_IBS, vcpu);
	kvm_s390_sync_request(KVM_REQ_ENABLE_IBS, vcpu);
पूर्ण

पूर्णांक kvm_s390_vcpu_start(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i, online_vcpus, r = 0, started_vcpus = 0;

	अगर (!is_vcpu_stopped(vcpu))
		वापस 0;

	trace_kvm_s390_vcpu_start_stop(vcpu->vcpu_id, 1);
	/* Only one cpu at a समय may enter/leave the STOPPED state. */
	spin_lock(&vcpu->kvm->arch.start_stop_lock);
	online_vcpus = atomic_पढ़ो(&vcpu->kvm->online_vcpus);

	/* Let's tell the UV that we want to change पूर्णांकo the operating state */
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		r = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_OPR);
		अगर (r) अणु
			spin_unlock(&vcpu->kvm->arch.start_stop_lock);
			वापस r;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < online_vcpus; i++) अणु
		अगर (!is_vcpu_stopped(vcpu->kvm->vcpus[i]))
			started_vcpus++;
	पूर्ण

	अगर (started_vcpus == 0) अणु
		/* we're the only active VCPU -> speed it up */
		__enable_ibs_on_vcpu(vcpu);
	पूर्ण अन्यथा अगर (started_vcpus == 1) अणु
		/*
		 * As we are starting a second VCPU, we have to disable
		 * the IBS facility on all VCPUs to हटाओ potentially
		 * outstanding ENABLE requests.
		 */
		__disable_ibs_on_all_vcpus(vcpu->kvm);
	पूर्ण

	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_STOPPED);
	/*
	 * The real PSW might have changed due to a RESTART पूर्णांकerpreted by the
	 * ultravisor. We block all पूर्णांकerrupts and let the next sie निकास
	 * refresh our view.
	 */
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu))
		vcpu->arch.sie_block->gpsw.mask &= ~PSW_INT_MASK;
	/*
	 * Another VCPU might have used IBS जबतक we were offline.
	 * Let's play safe and flush the VCPU at startup.
	 */
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	spin_unlock(&vcpu->kvm->arch.start_stop_lock);
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_vcpu_stop(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i, online_vcpus, r = 0, started_vcpus = 0;
	काष्ठा kvm_vcpu *started_vcpu = शून्य;

	अगर (is_vcpu_stopped(vcpu))
		वापस 0;

	trace_kvm_s390_vcpu_start_stop(vcpu->vcpu_id, 0);
	/* Only one cpu at a समय may enter/leave the STOPPED state. */
	spin_lock(&vcpu->kvm->arch.start_stop_lock);
	online_vcpus = atomic_पढ़ो(&vcpu->kvm->online_vcpus);

	/* Let's tell the UV that we want to change पूर्णांकo the stopped state */
	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
		r = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_STP);
		अगर (r) अणु
			spin_unlock(&vcpu->kvm->arch.start_stop_lock);
			वापस r;
		पूर्ण
	पूर्ण

	/* SIGP STOP and SIGP STOP AND STORE STATUS has been fully processed */
	kvm_s390_clear_stop_irq(vcpu);

	kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOPPED);
	__disable_ibs_on_vcpu(vcpu);

	क्रम (i = 0; i < online_vcpus; i++) अणु
		अगर (!is_vcpu_stopped(vcpu->kvm->vcpus[i])) अणु
			started_vcpus++;
			started_vcpu = vcpu->kvm->vcpus[i];
		पूर्ण
	पूर्ण

	अगर (started_vcpus == 1) अणु
		/*
		 * As we only have one VCPU left, we want to enable the
		 * IBS facility क्रम that VCPU to speed it up.
		 */
		__enable_ibs_on_vcpu(started_vcpu);
	पूर्ण

	spin_unlock(&vcpu->kvm->arch.start_stop_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_enable_cap(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_S390_CSS_SUPPORT:
		अगर (!vcpu->kvm->arch.css_support) अणु
			vcpu->kvm->arch.css_support = 1;
			VM_EVENT(vcpu->kvm, 3, "%s", "ENABLE: CSS support");
			trace_kvm_s390_enable_css(vcpu->kvm);
		पूर्ण
		r = 0;
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

अटल दीर्घ kvm_s390_guest_sida_op(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_s390_mem_op *mop)
अणु
	व्योम __user *uaddr = (व्योम __user *)mop->buf;
	पूर्णांक r = 0;

	अगर (mop->flags || !mop->size)
		वापस -EINVAL;
	अगर (mop->size + mop->sida_offset < mop->size)
		वापस -EINVAL;
	अगर (mop->size + mop->sida_offset > sida_size(vcpu->arch.sie_block))
		वापस -E2BIG;

	चयन (mop->op) अणु
	हाल KVM_S390_MEMOP_SIDA_READ:
		अगर (copy_to_user(uaddr, (व्योम *)(sida_origin(vcpu->arch.sie_block) +
				 mop->sida_offset), mop->size))
			r = -EFAULT;

		अवरोध;
	हाल KVM_S390_MEMOP_SIDA_WRITE:
		अगर (copy_from_user((व्योम *)(sida_origin(vcpu->arch.sie_block) +
				   mop->sida_offset), uaddr, mop->size))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण
अटल दीर्घ kvm_s390_guest_mem_op(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_s390_mem_op *mop)
अणु
	व्योम __user *uaddr = (व्योम __user *)mop->buf;
	व्योम *पंचांगpbuf = शून्य;
	पूर्णांक r = 0;
	स्थिर u64 supported_flags = KVM_S390_MEMOP_F_INJECT_EXCEPTION
				    | KVM_S390_MEMOP_F_CHECK_ONLY;

	अगर (mop->flags & ~supported_flags || mop->ar >= NUM_ACRS || !mop->size)
		वापस -EINVAL;

	अगर (mop->size > MEM_OP_MAX_SIZE)
		वापस -E2BIG;

	अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu))
		वापस -EINVAL;

	अगर (!(mop->flags & KVM_S390_MEMOP_F_CHECK_ONLY)) अणु
		पंचांगpbuf = vदो_स्मृति(mop->size);
		अगर (!पंचांगpbuf)
			वापस -ENOMEM;
	पूर्ण

	चयन (mop->op) अणु
	हाल KVM_S390_MEMOP_LOGICAL_READ:
		अगर (mop->flags & KVM_S390_MEMOP_F_CHECK_ONLY) अणु
			r = check_gva_range(vcpu, mop->gaddr, mop->ar,
					    mop->size, GACC_FETCH);
			अवरोध;
		पूर्ण
		r = पढ़ो_guest(vcpu, mop->gaddr, mop->ar, पंचांगpbuf, mop->size);
		अगर (r == 0) अणु
			अगर (copy_to_user(uaddr, पंचांगpbuf, mop->size))
				r = -EFAULT;
		पूर्ण
		अवरोध;
	हाल KVM_S390_MEMOP_LOGICAL_WRITE:
		अगर (mop->flags & KVM_S390_MEMOP_F_CHECK_ONLY) अणु
			r = check_gva_range(vcpu, mop->gaddr, mop->ar,
					    mop->size, GACC_STORE);
			अवरोध;
		पूर्ण
		अगर (copy_from_user(पंचांगpbuf, uaddr, mop->size)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		r = ग_लिखो_guest(vcpu, mop->gaddr, mop->ar, पंचांगpbuf, mop->size);
		अवरोध;
	पूर्ण

	अगर (r > 0 && (mop->flags & KVM_S390_MEMOP_F_INJECT_EXCEPTION) != 0)
		kvm_s390_inject_prog_irq(vcpu, &vcpu->arch.pgm);

	vमुक्त(पंचांगpbuf);
	वापस r;
पूर्ण

अटल दीर्घ kvm_s390_guest_memsida_op(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_s390_mem_op *mop)
अणु
	पूर्णांक r, srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	चयन (mop->op) अणु
	हाल KVM_S390_MEMOP_LOGICAL_READ:
	हाल KVM_S390_MEMOP_LOGICAL_WRITE:
		r = kvm_s390_guest_mem_op(vcpu, mop);
		अवरोध;
	हाल KVM_S390_MEMOP_SIDA_READ:
	हाल KVM_S390_MEMOP_SIDA_WRITE:
		/* we are locked against sida going away by the vcpu->mutex */
		r = kvm_s390_guest_sida_op(vcpu, mop);
		अवरोध;
	शेष:
		r = -EINVAL;
	पूर्ण

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
	वापस r;
पूर्ण

दीर्घ kvm_arch_vcpu_async_ioctl(काष्ठा file *filp,
			       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (ioctl) अणु
	हाल KVM_S390_IRQ: अणु
		काष्ठा kvm_s390_irq s390irq;

		अगर (copy_from_user(&s390irq, argp, माप(s390irq)))
			वापस -EFAULT;
		वापस kvm_s390_inject_vcpu(vcpu, &s390irq);
	पूर्ण
	हाल KVM_S390_INTERRUPT: अणु
		काष्ठा kvm_s390_पूर्णांकerrupt s390पूर्णांक;
		काष्ठा kvm_s390_irq s390irq = अणुपूर्ण;

		अगर (copy_from_user(&s390पूर्णांक, argp, माप(s390पूर्णांक)))
			वापस -EFAULT;
		अगर (s390पूर्णांक_to_s390irq(&s390पूर्णांक, &s390irq))
			वापस -EINVAL;
		वापस kvm_s390_inject_vcpu(vcpu, &s390irq);
	पूर्ण
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

दीर्घ kvm_arch_vcpu_ioctl(काष्ठा file *filp,
			 अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक idx;
	दीर्घ r;
	u16 rc, rrc;

	vcpu_load(vcpu);

	चयन (ioctl) अणु
	हाल KVM_S390_STORE_STATUS:
		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = kvm_s390_store_status_unloaded(vcpu, arg);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	हाल KVM_S390_SET_INITIAL_PSW: अणु
		psw_t psw;

		r = -EFAULT;
		अगर (copy_from_user(&psw, argp, माप(psw)))
			अवरोध;
		r = kvm_arch_vcpu_ioctl_set_initial_psw(vcpu, psw);
		अवरोध;
	पूर्ण
	हाल KVM_S390_CLEAR_RESET:
		r = 0;
		kvm_arch_vcpu_ioctl_clear_reset(vcpu);
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			r = uv_cmd_nodata(kvm_s390_pv_cpu_get_handle(vcpu),
					  UVC_CMD_CPU_RESET_CLEAR, &rc, &rrc);
			VCPU_EVENT(vcpu, 3, "PROTVIRT RESET CLEAR VCPU: rc %x rrc %x",
				   rc, rrc);
		पूर्ण
		अवरोध;
	हाल KVM_S390_INITIAL_RESET:
		r = 0;
		kvm_arch_vcpu_ioctl_initial_reset(vcpu);
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			r = uv_cmd_nodata(kvm_s390_pv_cpu_get_handle(vcpu),
					  UVC_CMD_CPU_RESET_INITIAL,
					  &rc, &rrc);
			VCPU_EVENT(vcpu, 3, "PROTVIRT RESET INITIAL VCPU: rc %x rrc %x",
				   rc, rrc);
		पूर्ण
		अवरोध;
	हाल KVM_S390_NORMAL_RESET:
		r = 0;
		kvm_arch_vcpu_ioctl_normal_reset(vcpu);
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu)) अणु
			r = uv_cmd_nodata(kvm_s390_pv_cpu_get_handle(vcpu),
					  UVC_CMD_CPU_RESET, &rc, &rrc);
			VCPU_EVENT(vcpu, 3, "PROTVIRT RESET NORMAL VCPU: rc %x rrc %x",
				   rc, rrc);
		पूर्ण
		अवरोध;
	हाल KVM_SET_ONE_REG:
	हाल KVM_GET_ONE_REG: अणु
		काष्ठा kvm_one_reg reg;
		r = -EINVAL;
		अगर (kvm_s390_pv_cpu_is_रक्षित(vcpu))
			अवरोध;
		r = -EFAULT;
		अगर (copy_from_user(&reg, argp, माप(reg)))
			अवरोध;
		अगर (ioctl == KVM_SET_ONE_REG)
			r = kvm_arch_vcpu_ioctl_set_one_reg(vcpu, &reg);
		अन्यथा
			r = kvm_arch_vcpu_ioctl_get_one_reg(vcpu, &reg);
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_KVM_S390_UCONTROL
	हाल KVM_S390_UCAS_MAP: अणु
		काष्ठा kvm_s390_ucas_mapping ucयंत्रap;

		अगर (copy_from_user(&ucयंत्रap, argp, माप(ucयंत्रap))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!kvm_is_ucontrol(vcpu->kvm)) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = gmap_map_segment(vcpu->arch.gmap, ucयंत्रap.user_addr,
				     ucयंत्रap.vcpu_addr, ucयंत्रap.length);
		अवरोध;
	पूर्ण
	हाल KVM_S390_UCAS_UNMAP: अणु
		काष्ठा kvm_s390_ucas_mapping ucयंत्रap;

		अगर (copy_from_user(&ucयंत्रap, argp, माप(ucयंत्रap))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!kvm_is_ucontrol(vcpu->kvm)) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = gmap_unmap_segment(vcpu->arch.gmap, ucयंत्रap.vcpu_addr,
			ucयंत्रap.length);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल KVM_S390_VCPU_FAULT: अणु
		r = gmap_fault(vcpu->arch.gmap, arg, 0);
		अवरोध;
	पूर्ण
	हाल KVM_ENABLE_CAP:
	अणु
		काष्ठा kvm_enable_cap cap;
		r = -EFAULT;
		अगर (copy_from_user(&cap, argp, माप(cap)))
			अवरोध;
		r = kvm_vcpu_ioctl_enable_cap(vcpu, &cap);
		अवरोध;
	पूर्ण
	हाल KVM_S390_MEM_OP: अणु
		काष्ठा kvm_s390_mem_op mem_op;

		अगर (copy_from_user(&mem_op, argp, माप(mem_op)) == 0)
			r = kvm_s390_guest_memsida_op(vcpu, &mem_op);
		अन्यथा
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_S390_SET_IRQ_STATE: अणु
		काष्ठा kvm_s390_irq_state irq_state;

		r = -EFAULT;
		अगर (copy_from_user(&irq_state, argp, माप(irq_state)))
			अवरोध;
		अगर (irq_state.len > VCPU_IRQS_MAX_BUF ||
		    irq_state.len == 0 ||
		    irq_state.len % माप(काष्ठा kvm_s390_irq) > 0) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		/* करो not use irq_state.flags, it will अवरोध old QEMUs */
		r = kvm_s390_set_irq_state(vcpu,
					   (व्योम __user *) irq_state.buf,
					   irq_state.len);
		अवरोध;
	पूर्ण
	हाल KVM_S390_GET_IRQ_STATE: अणु
		काष्ठा kvm_s390_irq_state irq_state;

		r = -EFAULT;
		अगर (copy_from_user(&irq_state, argp, माप(irq_state)))
			अवरोध;
		अगर (irq_state.len == 0) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		/* करो not use irq_state.flags, it will अवरोध old QEMUs */
		r = kvm_s390_get_irq_state(vcpu,
					   (__u8 __user *)  irq_state.buf,
					   irq_state.len);
		अवरोध;
	पूर्ण
	शेष:
		r = -ENOTTY;
	पूर्ण

	vcpu_put(vcpu);
	वापस r;
पूर्ण

vm_fault_t kvm_arch_vcpu_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vm_fault *vmf)
अणु
#अगर_घोषित CONFIG_KVM_S390_UCONTROL
	अगर ((vmf->pgoff == KVM_S390_SIE_PAGE_OFFSET)
		 && (kvm_is_ucontrol(vcpu->kvm))) अणु
		vmf->page = virt_to_page(vcpu->arch.sie_block);
		get_page(vmf->page);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	वापस VM_FAULT_SIGBUS;
पूर्ण

/* Section: memory related */
पूर्णांक kvm_arch_prepare_memory_region(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *memslot,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   क्रमागत kvm_mr_change change)
अणु
	/* A few sanity checks. We can have memory slots which have to be
	   located/ended at a segment boundary (1MB). The memory in userland is
	   ok to be fragmented पूर्णांकo various dअगरferent vmas. It is okay to mmap()
	   and munmap() stuff in this slot after करोing this call at any समय */

	अगर (mem->userspace_addr & 0xffffful)
		वापस -EINVAL;

	अगर (mem->memory_size & 0xffffful)
		वापस -EINVAL;

	अगर (mem->guest_phys_addr + mem->memory_size > kvm->arch.mem_limit)
		वापस -EINVAL;

	/* When we are रक्षित, we should not change the memory slots */
	अगर (kvm_s390_pv_get_handle(kvm))
		वापस -EINVAL;
	वापस 0;
पूर्ण

व्योम kvm_arch_commit_memory_region(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change)
अणु
	पूर्णांक rc = 0;

	चयन (change) अणु
	हाल KVM_MR_DELETE:
		rc = gmap_unmap_segment(kvm->arch.gmap, old->base_gfn * PAGE_SIZE,
					old->npages * PAGE_SIZE);
		अवरोध;
	हाल KVM_MR_MOVE:
		rc = gmap_unmap_segment(kvm->arch.gmap, old->base_gfn * PAGE_SIZE,
					old->npages * PAGE_SIZE);
		अगर (rc)
			अवरोध;
		fallthrough;
	हाल KVM_MR_CREATE:
		rc = gmap_map_segment(kvm->arch.gmap, mem->userspace_addr,
				      mem->guest_phys_addr, mem->memory_size);
		अवरोध;
	हाल KVM_MR_FLAGS_ONLY:
		अवरोध;
	शेष:
		WARN(1, "Unknown KVM MR CHANGE: %d\n", change);
	पूर्ण
	अगर (rc)
		pr_warn("failed to commit memory region\n");
	वापस;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nonhyp_mask(पूर्णांक i)
अणु
	अचिन्हित पूर्णांक nonhyp_fai = (sclp.hmfai << i * 2) >> 30;

	वापस 0x0000ffffffffffffUL >> (nonhyp_fai << 4);
पूर्ण

व्योम kvm_arch_vcpu_block_finish(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->valid_wakeup = false;
पूर्ण

अटल पूर्णांक __init kvm_s390_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!sclp.has_sief2) अणु
		pr_info("SIE is not available\n");
		वापस -ENODEV;
	पूर्ण

	अगर (nested && hpage) अणु
		pr_info("A KVM host that supports nesting cannot back its KVM guests with huge pages\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 16; i++)
		kvm_s390_fac_base[i] |=
			S390_lowcore.stfle_fac_list[i] & nonhyp_mask(i);

	वापस kvm_init(शून्य, माप(काष्ठा kvm_vcpu), 0, THIS_MODULE);
पूर्ण

अटल व्योम __निकास kvm_s390_निकास(व्योम)
अणु
	kvm_निकास();
पूर्ण

module_init(kvm_s390_init);
module_निकास(kvm_s390_निकास);

/*
 * Enable स्वतःloading of the kvm module.
 * Note that we add the module alias here instead of virt/kvm/kvm_मुख्य.c
 * since x86 takes a dअगरferent approach.
 */
#समावेश <linux/miscdevice.h>
MODULE_ALIAS_MISCDEV(KVM_MINOR);
MODULE_ALIAS("devname:kvm");
