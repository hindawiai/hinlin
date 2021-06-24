<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 * Copyright (C) 2009. SUSE Linux Products GmbH. All rights reserved.
 *
 * Authors:
 *    Paul Mackerras <paulus@au1.ibm.com>
 *    Alexander Graf <agraf@suse.de>
 *    Kevin Wolf <mail@kevin-wolf.de>
 *
 * Description: KVM functions specअगरic to running on Book 3S
 * processors in hypervisor mode (specअगरically POWER7 and later).
 *
 * This file is derived from arch/घातerpc/kvm/book3s.c,
 * by Alexander Graf <agraf@suse.de>.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/preempt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/srcu.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/kvm_irqfd.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/hmi.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/kvm_book3s_uvस्मृति.स>
#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/dtl.h>

#समावेश "book3s.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_hv.h"

/* #घोषणा EXIT_DEBUG */
/* #घोषणा EXIT_DEBUG_SIMPLE */
/* #घोषणा EXIT_DEBUG_INT */

/* Used to indicate that a guest page fault needs to be handled */
#घोषणा RESUME_PAGE_FAULT	(RESUME_GUEST | RESUME_FLAG_ARCH1)
/* Used to indicate that a guest passthrough पूर्णांकerrupt needs to be handled */
#घोषणा RESUME_PASSTHROUGH	(RESUME_GUEST | RESUME_FLAG_ARCH2)

/* Used as a "null" value क्रम समयbase values */
#घोषणा TB_NIL	(~(u64)0)

अटल DECLARE_BITMAP(शेष_enabled_hcalls, MAX_HCALL_OPCODE/4 + 1);

अटल पूर्णांक dynamic_mt_modes = 6;
module_param(dynamic_mt_modes, पूर्णांक, 0644);
MODULE_PARM_DESC(dynamic_mt_modes, "Set of allowed dynamic micro-threading modes: 0 (= none), 2, 4, or 6 (= 2 or 4)");
अटल पूर्णांक target_smt_mode;
module_param(target_smt_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(target_smt_mode, "Target threads per core (0 = max)");

अटल bool indep_thपढ़ोs_mode = true;
module_param(indep_thपढ़ोs_mode, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(indep_thपढ़ोs_mode, "Independent-threads mode (only on POWER9)");

अटल bool one_vm_per_core;
module_param(one_vm_per_core, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(one_vm_per_core, "Only run vCPUs from the same VM on a core (requires indep_threads_mode=N)");

#अगर_घोषित CONFIG_KVM_XICS
अटल स्थिर काष्ठा kernel_param_ops module_param_ops = अणु
	.set = param_set_पूर्णांक,
	.get = param_get_पूर्णांक,
पूर्ण;

module_param_cb(kvm_irq_bypass, &module_param_ops, &kvm_irq_bypass, 0644);
MODULE_PARM_DESC(kvm_irq_bypass, "Bypass passthrough interrupt optimization");

module_param_cb(h_ipi_redirect, &module_param_ops, &h_ipi_redirect, 0644);
MODULE_PARM_DESC(h_ipi_redirect, "Redirect H_IPI wakeup to a free host core");
#पूर्ण_अगर

/* If set, guests are allowed to create and control nested guests */
अटल bool nested = true;
module_param(nested, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(nested, "Enable nested virtualization (only on POWER9)");

अटल अंतरभूत bool nesting_enabled(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.nested_enable && kvm_is_radix(kvm);
पूर्ण

/* If set, the thपढ़ोs on each CPU core have to be in the same MMU mode */
अटल bool no_mixing_hpt_and_radix __पढ़ो_mostly;

अटल पूर्णांक kvmppc_hv_setup_htab_rma(काष्ठा kvm_vcpu *vcpu);

/*
 * RWMR values क्रम POWER8.  These control the rate at which PURR
 * and SPURR count and should be set according to the number of
 * online thपढ़ोs in the vcore being run.
 */
#घोषणा RWMR_RPA_P8_1THREAD	0x164520C62609AECAUL
#घोषणा RWMR_RPA_P8_2THREAD	0x7FFF2908450D8DA9UL
#घोषणा RWMR_RPA_P8_3THREAD	0x164520C62609AECAUL
#घोषणा RWMR_RPA_P8_4THREAD	0x199A421245058DA9UL
#घोषणा RWMR_RPA_P8_5THREAD	0x164520C62609AECAUL
#घोषणा RWMR_RPA_P8_6THREAD	0x164520C62609AECAUL
#घोषणा RWMR_RPA_P8_7THREAD	0x164520C62609AECAUL
#घोषणा RWMR_RPA_P8_8THREAD	0x164520C62609AECAUL

अटल अचिन्हित दीर्घ p8_rwmr_values[MAX_SMT_THREADS + 1] = अणु
	RWMR_RPA_P8_1THREAD,
	RWMR_RPA_P8_1THREAD,
	RWMR_RPA_P8_2THREAD,
	RWMR_RPA_P8_3THREAD,
	RWMR_RPA_P8_4THREAD,
	RWMR_RPA_P8_5THREAD,
	RWMR_RPA_P8_6THREAD,
	RWMR_RPA_P8_7THREAD,
	RWMR_RPA_P8_8THREAD,
पूर्ण;

अटल अंतरभूत काष्ठा kvm_vcpu *next_runnable_thपढ़ो(काष्ठा kvmppc_vcore *vc,
		पूर्णांक *ip)
अणु
	पूर्णांक i = *ip;
	काष्ठा kvm_vcpu *vcpu;

	जबतक (++i < MAX_SMT_THREADS) अणु
		vcpu = READ_ONCE(vc->runnable_thपढ़ोs[i]);
		अगर (vcpu) अणु
			*ip = i;
			वापस vcpu;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Used to traverse the list of runnable thपढ़ोs क्रम a given vcore */
#घोषणा क्रम_each_runnable_thपढ़ो(i, vcpu, vc) \
	क्रम (i = -1; (vcpu = next_runnable_thपढ़ो(vc, &i)); )

अटल bool kvmppc_ipi_thपढ़ो(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ msg = PPC_DBELL_TYPE(PPC_DBELL_SERVER);

	/* If we're a nested hypervisor, fall back to ordinary IPIs क्रम now */
	अगर (kvmhv_on_pseries())
		वापस false;

	/* On POWER9 we can use msgsnd to IPI any cpu */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		msg |= get_hard_smp_processor_id(cpu);
		smp_mb();
		__यंत्र__ __अस्थिर__ (PPC_MSGSND(%0) : : "r" (msg));
		वापस true;
	पूर्ण

	/* On POWER8 क्रम IPIs to thपढ़ोs in the same core, use msgsnd */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		preempt_disable();
		अगर (cpu_first_thपढ़ो_sibling(cpu) ==
		    cpu_first_thपढ़ो_sibling(smp_processor_id())) अणु
			msg |= cpu_thपढ़ो_in_core(cpu);
			smp_mb();
			__यंत्र__ __अस्थिर__ (PPC_MSGSND(%0) : : "r" (msg));
			preempt_enable();
			वापस true;
		पूर्ण
		preempt_enable();
	पूर्ण

#अगर defined(CONFIG_PPC_ICP_NATIVE) && defined(CONFIG_SMP)
	अगर (cpu >= 0 && cpu < nr_cpu_ids) अणु
		अगर (paca_ptrs[cpu]->kvm_hstate.xics_phys) अणु
			xics_wake_cpu(cpu);
			वापस true;
		पूर्ण
		opal_पूर्णांक_set_mfrr(get_hard_smp_processor_id(cpu), IPI_PRIORITY);
		वापस true;
	पूर्ण
#पूर्ण_अगर

	वापस false;
पूर्ण

अटल व्योम kvmppc_fast_vcpu_kick_hv(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक cpu;
	काष्ठा rcuरुको *रुकोp;

	रुकोp = kvm_arch_vcpu_get_रुको(vcpu);
	अगर (rcuरुको_wake_up(रुकोp))
		++vcpu->स्थिति.सalt_wakeup;

	cpu = READ_ONCE(vcpu->arch.thपढ़ो_cpu);
	अगर (cpu >= 0 && kvmppc_ipi_thपढ़ो(cpu))
		वापस;

	/* CPU poपूर्णांकs to the first thपढ़ो of the core */
	cpu = vcpu->cpu;
	अगर (cpu >= 0 && cpu < nr_cpu_ids && cpu_online(cpu))
		smp_send_reschedule(cpu);
पूर्ण

/*
 * We use the vcpu_load/put functions to measure stolen समय.
 * Stolen समय is counted as समय when either the vcpu is able to
 * run as part of a भव core, but the task running the vcore
 * is preempted or sleeping, or when the vcpu needs something करोne
 * in the kernel by the task running the vcpu, but that task is
 * preempted or sleeping.  Those two things have to be counted
 * separately, since one of the vcpu tasks will take on the job
 * of running the core, and the other vcpu tasks in the vcore will
 * sleep रुकोing क्रम it to करो that, but that sleep shouldn't count
 * as stolen समय.
 *
 * Hence we accumulate stolen समय when the vcpu can run as part of
 * a vcore using vc->stolen_tb, and the stolen समय when the vcpu
 * needs its task to करो other things in the kernel (क्रम example,
 * service a page fault) in busy_stolen.  We करोn't accumulate
 * stolen समय क्रम a vcore when it is inactive, or क्रम a vcpu
 * when it is in state RUNNING or NOTREADY.  NOTREADY is a bit of
 * a misnomer; it means that the vcpu task is not executing in
 * the KVM_VCPU_RUN ioctl, i.e. it is in userspace or अन्यथाwhere in
 * the kernel.  We करोn't have any way of भागiding up that समय
 * between समय that the vcpu is genuinely stopped, समय that
 * the task is actively working on behalf of the vcpu, and समय
 * that the task is preempted, so we करोn't count any of it as
 * stolen.
 *
 * Updates to busy_stolen are रक्षित by arch.tbacct_lock;
 * updates to vc->stolen_tb are रक्षित by the vcore->stoltb_lock
 * lock.  The stolen बार are measured in units of समयbase ticks.
 * (Note that the != TB_NIL checks below are purely defensive;
 * they should never fail.)
 */

अटल व्योम kvmppc_core_start_stolen(काष्ठा kvmppc_vcore *vc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->stoltb_lock, flags);
	vc->preempt_tb = mftb();
	spin_unlock_irqrestore(&vc->stoltb_lock, flags);
पूर्ण

अटल व्योम kvmppc_core_end_stolen(काष्ठा kvmppc_vcore *vc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->stoltb_lock, flags);
	अगर (vc->preempt_tb != TB_NIL) अणु
		vc->stolen_tb += mftb() - vc->preempt_tb;
		vc->preempt_tb = TB_NIL;
	पूर्ण
	spin_unlock_irqrestore(&vc->stoltb_lock, flags);
पूर्ण

अटल व्योम kvmppc_core_vcpu_load_hv(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	अचिन्हित दीर्घ flags;

	/*
	 * We can test vc->runner without taking the vcore lock,
	 * because only this task ever sets vc->runner to this
	 * vcpu, and once it is set to this vcpu, only this task
	 * ever sets it to शून्य.
	 */
	अगर (vc->runner == vcpu && vc->vcore_state >= VCORE_SLEEPING)
		kvmppc_core_end_stolen(vc);

	spin_lock_irqsave(&vcpu->arch.tbacct_lock, flags);
	अगर (vcpu->arch.state == KVMPPC_VCPU_BUSY_IN_HOST &&
	    vcpu->arch.busy_preempt != TB_NIL) अणु
		vcpu->arch.busy_stolen += mftb() - vcpu->arch.busy_preempt;
		vcpu->arch.busy_preempt = TB_NIL;
	पूर्ण
	spin_unlock_irqrestore(&vcpu->arch.tbacct_lock, flags);
पूर्ण

अटल व्योम kvmppc_core_vcpu_put_hv(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	अचिन्हित दीर्घ flags;

	अगर (vc->runner == vcpu && vc->vcore_state >= VCORE_SLEEPING)
		kvmppc_core_start_stolen(vc);

	spin_lock_irqsave(&vcpu->arch.tbacct_lock, flags);
	अगर (vcpu->arch.state == KVMPPC_VCPU_BUSY_IN_HOST)
		vcpu->arch.busy_preempt = mftb();
	spin_unlock_irqrestore(&vcpu->arch.tbacct_lock, flags);
पूर्ण

अटल व्योम kvmppc_set_pvr_hv(काष्ठा kvm_vcpu *vcpu, u32 pvr)
अणु
	vcpu->arch.pvr = pvr;
पूर्ण

/* Dummy value used in computing PCR value below */
#घोषणा PCR_ARCH_31    (PCR_ARCH_300 << 1)

अटल पूर्णांक kvmppc_set_arch_compat(काष्ठा kvm_vcpu *vcpu, u32 arch_compat)
अणु
	अचिन्हित दीर्घ host_pcr_bit = 0, guest_pcr_bit = 0;
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;

	/* We can (emulate) our own architecture version and anything older */
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		host_pcr_bit = PCR_ARCH_31;
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		host_pcr_bit = PCR_ARCH_300;
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		host_pcr_bit = PCR_ARCH_207;
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_206))
		host_pcr_bit = PCR_ARCH_206;
	अन्यथा
		host_pcr_bit = PCR_ARCH_205;

	/* Determine lowest PCR bit needed to run guest in given PVR level */
	guest_pcr_bit = host_pcr_bit;
	अगर (arch_compat) अणु
		चयन (arch_compat) अणु
		हाल PVR_ARCH_205:
			guest_pcr_bit = PCR_ARCH_205;
			अवरोध;
		हाल PVR_ARCH_206:
		हाल PVR_ARCH_206p:
			guest_pcr_bit = PCR_ARCH_206;
			अवरोध;
		हाल PVR_ARCH_207:
			guest_pcr_bit = PCR_ARCH_207;
			अवरोध;
		हाल PVR_ARCH_300:
			guest_pcr_bit = PCR_ARCH_300;
			अवरोध;
		हाल PVR_ARCH_31:
			guest_pcr_bit = PCR_ARCH_31;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check requested PCR bits करोn't exceed our capabilities */
	अगर (guest_pcr_bit > host_pcr_bit)
		वापस -EINVAL;

	spin_lock(&vc->lock);
	vc->arch_compat = arch_compat;
	/*
	 * Set all PCR bits क्रम which guest_pcr_bit <= bit < host_pcr_bit
	 * Also set all reserved PCR bits
	 */
	vc->pcr = (host_pcr_bit - guest_pcr_bit) | PCR_MASK;
	spin_unlock(&vc->lock);

	वापस 0;
पूर्ण

अटल व्योम kvmppc_dump_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;

	pr_err("vcpu %p (%d):\n", vcpu, vcpu->vcpu_id);
	pr_err("pc  = %.16lx  msr = %.16llx  trap = %x\n",
	       vcpu->arch.regs.nip, vcpu->arch.shregs.msr, vcpu->arch.trap);
	क्रम (r = 0; r < 16; ++r)
		pr_err("r%2d = %.16lx  r%d = %.16lx\n",
		       r, kvmppc_get_gpr(vcpu, r),
		       r+16, kvmppc_get_gpr(vcpu, r+16));
	pr_err("ctr = %.16lx  lr  = %.16lx\n",
	       vcpu->arch.regs.ctr, vcpu->arch.regs.link);
	pr_err("srr0 = %.16llx srr1 = %.16llx\n",
	       vcpu->arch.shregs.srr0, vcpu->arch.shregs.srr1);
	pr_err("sprg0 = %.16llx sprg1 = %.16llx\n",
	       vcpu->arch.shregs.sprg0, vcpu->arch.shregs.sprg1);
	pr_err("sprg2 = %.16llx sprg3 = %.16llx\n",
	       vcpu->arch.shregs.sprg2, vcpu->arch.shregs.sprg3);
	pr_err("cr = %.8lx  xer = %.16lx  dsisr = %.8x\n",
	       vcpu->arch.regs.ccr, vcpu->arch.regs.xer, vcpu->arch.shregs.dsisr);
	pr_err("dar = %.16llx\n", vcpu->arch.shregs.dar);
	pr_err("fault dar = %.16lx dsisr = %.8x\n",
	       vcpu->arch.fault_dar, vcpu->arch.fault_dsisr);
	pr_err("SLB (%d entries):\n", vcpu->arch.slb_max);
	क्रम (r = 0; r < vcpu->arch.slb_max; ++r)
		pr_err("  ESID = %.16llx VSID = %.16llx\n",
		       vcpu->arch.slb[r].orige, vcpu->arch.slb[r].origv);
	pr_err("lpcr = %.16lx sdr1 = %.16lx last_inst = %.8x\n",
	       vcpu->arch.vcore->lpcr, vcpu->kvm->arch.sdr1,
	       vcpu->arch.last_inst);
पूर्ण

अटल काष्ठा kvm_vcpu *kvmppc_find_vcpu(काष्ठा kvm *kvm, पूर्णांक id)
अणु
	वापस kvm_get_vcpu_by_id(kvm, id);
पूर्ण

अटल व्योम init_vpa(काष्ठा kvm_vcpu *vcpu, काष्ठा lppaca *vpa)
अणु
	vpa->__old_status |= LPPACA_OLD_SHARED_PROC;
	vpa->yield_count = cpu_to_be32(1);
पूर्ण

अटल पूर्णांक set_vpa(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_vpa *v,
		   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	/* check address is cacheline aligned */
	अगर (addr & (L1_CACHE_BYTES - 1))
		वापस -EINVAL;
	spin_lock(&vcpu->arch.vpa_update_lock);
	अगर (v->next_gpa != addr || v->len != len) अणु
		v->next_gpa = addr;
		v->len = addr ? len : 0;
		v->update_pending = 1;
	पूर्ण
	spin_unlock(&vcpu->arch.vpa_update_lock);
	वापस 0;
पूर्ण

/* Length क्रम a per-processor buffer is passed in at offset 4 in the buffer */
काष्ठा reg_vpa अणु
	u32 dummy;
	जोड़ अणु
		__be16 hword;
		__be32 word;
	पूर्ण length;
पूर्ण;

अटल पूर्णांक vpa_is_रेजिस्टरed(काष्ठा kvmppc_vpa *vpap)
अणु
	अगर (vpap->update_pending)
		वापस vpap->next_gpa != 0;
	वापस vpap->pinned_addr != शून्य;
पूर्ण

अटल अचिन्हित दीर्घ करो_h_रेजिस्टर_vpa(काष्ठा kvm_vcpu *vcpu,
				       अचिन्हित दीर्घ flags,
				       अचिन्हित दीर्घ vcpuid, अचिन्हित दीर्घ vpa)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ len, nb;
	व्योम *va;
	काष्ठा kvm_vcpu *tvcpu;
	पूर्णांक err;
	पूर्णांक subfunc;
	काष्ठा kvmppc_vpa *vpap;

	tvcpu = kvmppc_find_vcpu(kvm, vcpuid);
	अगर (!tvcpu)
		वापस H_PARAMETER;

	subfunc = (flags >> H_VPA_FUNC_SHIFT) & H_VPA_FUNC_MASK;
	अगर (subfunc == H_VPA_REG_VPA || subfunc == H_VPA_REG_DTL ||
	    subfunc == H_VPA_REG_SLB) अणु
		/* Registering new area - address must be cache-line aligned */
		अगर ((vpa & (L1_CACHE_BYTES - 1)) || !vpa)
			वापस H_PARAMETER;

		/* convert logical addr to kernel addr and पढ़ो length */
		va = kvmppc_pin_guest_page(kvm, vpa, &nb);
		अगर (va == शून्य)
			वापस H_PARAMETER;
		अगर (subfunc == H_VPA_REG_VPA)
			len = be16_to_cpu(((काष्ठा reg_vpa *)va)->length.hword);
		अन्यथा
			len = be32_to_cpu(((काष्ठा reg_vpa *)va)->length.word);
		kvmppc_unpin_guest_page(kvm, va, vpa, false);

		/* Check length */
		अगर (len > nb || len < माप(काष्ठा reg_vpa))
			वापस H_PARAMETER;
	पूर्ण अन्यथा अणु
		vpa = 0;
		len = 0;
	पूर्ण

	err = H_PARAMETER;
	vpap = शून्य;
	spin_lock(&tvcpu->arch.vpa_update_lock);

	चयन (subfunc) अणु
	हाल H_VPA_REG_VPA:		/* रेजिस्टर VPA */
		/*
		 * The size of our lppaca is 1kB because of the way we align
		 * it क्रम the guest to aव्योम crossing a 4kB boundary. We only
		 * use 640 bytes of the काष्ठाure though, so we should accept
		 * clients that set a size of 640.
		 */
		BUILD_BUG_ON(माप(काष्ठा lppaca) != 640);
		अगर (len < माप(काष्ठा lppaca))
			अवरोध;
		vpap = &tvcpu->arch.vpa;
		err = 0;
		अवरोध;

	हाल H_VPA_REG_DTL:		/* रेजिस्टर DTL */
		अगर (len < माप(काष्ठा dtl_entry))
			अवरोध;
		len -= len % माप(काष्ठा dtl_entry);

		/* Check that they have previously रेजिस्टरed a VPA */
		err = H_RESOURCE;
		अगर (!vpa_is_रेजिस्टरed(&tvcpu->arch.vpa))
			अवरोध;

		vpap = &tvcpu->arch.dtl;
		err = 0;
		अवरोध;

	हाल H_VPA_REG_SLB:		/* रेजिस्टर SLB shaकरोw buffer */
		/* Check that they have previously रेजिस्टरed a VPA */
		err = H_RESOURCE;
		अगर (!vpa_is_रेजिस्टरed(&tvcpu->arch.vpa))
			अवरोध;

		vpap = &tvcpu->arch.slb_shaकरोw;
		err = 0;
		अवरोध;

	हाल H_VPA_DEREG_VPA:		/* deरेजिस्टर VPA */
		/* Check they करोn't still have a DTL or SLB buf रेजिस्टरed */
		err = H_RESOURCE;
		अगर (vpa_is_रेजिस्टरed(&tvcpu->arch.dtl) ||
		    vpa_is_रेजिस्टरed(&tvcpu->arch.slb_shaकरोw))
			अवरोध;

		vpap = &tvcpu->arch.vpa;
		err = 0;
		अवरोध;

	हाल H_VPA_DEREG_DTL:		/* deरेजिस्टर DTL */
		vpap = &tvcpu->arch.dtl;
		err = 0;
		अवरोध;

	हाल H_VPA_DEREG_SLB:		/* deरेजिस्टर SLB shaकरोw buffer */
		vpap = &tvcpu->arch.slb_shaकरोw;
		err = 0;
		अवरोध;
	पूर्ण

	अगर (vpap) अणु
		vpap->next_gpa = vpa;
		vpap->len = len;
		vpap->update_pending = 1;
	पूर्ण

	spin_unlock(&tvcpu->arch.vpa_update_lock);

	वापस err;
पूर्ण

अटल व्योम kvmppc_update_vpa(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_vpa *vpap)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	व्योम *va;
	अचिन्हित दीर्घ nb;
	अचिन्हित दीर्घ gpa;

	/*
	 * We need to pin the page poपूर्णांकed to by vpap->next_gpa,
	 * but we can't call kvmppc_pin_guest_page under the lock
	 * as it करोes get_user_pages() and करोwn_पढ़ो().  So we
	 * have to drop the lock, pin the page, then get the lock
	 * again and check that a new area didn't get रेजिस्टरed
	 * in the meanसमय.
	 */
	क्रम (;;) अणु
		gpa = vpap->next_gpa;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		va = शून्य;
		nb = 0;
		अगर (gpa)
			va = kvmppc_pin_guest_page(kvm, gpa, &nb);
		spin_lock(&vcpu->arch.vpa_update_lock);
		अगर (gpa == vpap->next_gpa)
			अवरोध;
		/* sigh... unpin that one and try again */
		अगर (va)
			kvmppc_unpin_guest_page(kvm, va, gpa, false);
	पूर्ण

	vpap->update_pending = 0;
	अगर (va && nb < vpap->len) अणु
		/*
		 * If it's now too लघु, it must be that userspace
		 * has changed the mappings underlying guest memory,
		 * so unरेजिस्टर the region.
		 */
		kvmppc_unpin_guest_page(kvm, va, gpa, false);
		va = शून्य;
	पूर्ण
	अगर (vpap->pinned_addr)
		kvmppc_unpin_guest_page(kvm, vpap->pinned_addr, vpap->gpa,
					vpap->dirty);
	vpap->gpa = gpa;
	vpap->pinned_addr = va;
	vpap->dirty = false;
	अगर (va)
		vpap->pinned_end = va + vpap->len;
पूर्ण

अटल व्योम kvmppc_update_vpas(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(vcpu->arch.vpa.update_pending ||
	      vcpu->arch.slb_shaकरोw.update_pending ||
	      vcpu->arch.dtl.update_pending))
		वापस;

	spin_lock(&vcpu->arch.vpa_update_lock);
	अगर (vcpu->arch.vpa.update_pending) अणु
		kvmppc_update_vpa(vcpu, &vcpu->arch.vpa);
		अगर (vcpu->arch.vpa.pinned_addr)
			init_vpa(vcpu, vcpu->arch.vpa.pinned_addr);
	पूर्ण
	अगर (vcpu->arch.dtl.update_pending) अणु
		kvmppc_update_vpa(vcpu, &vcpu->arch.dtl);
		vcpu->arch.dtl_ptr = vcpu->arch.dtl.pinned_addr;
		vcpu->arch.dtl_index = 0;
	पूर्ण
	अगर (vcpu->arch.slb_shaकरोw.update_pending)
		kvmppc_update_vpa(vcpu, &vcpu->arch.slb_shaकरोw);
	spin_unlock(&vcpu->arch.vpa_update_lock);
पूर्ण

/*
 * Return the accumulated stolen समय क्रम the vcore up until `now'.
 * The caller should hold the vcore lock.
 */
अटल u64 vcore_stolen_समय(काष्ठा kvmppc_vcore *vc, u64 now)
अणु
	u64 p;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->stoltb_lock, flags);
	p = vc->stolen_tb;
	अगर (vc->vcore_state != VCORE_INACTIVE &&
	    vc->preempt_tb != TB_NIL)
		p += now - vc->preempt_tb;
	spin_unlock_irqrestore(&vc->stoltb_lock, flags);
	वापस p;
पूर्ण

अटल व्योम kvmppc_create_dtl_entry(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvmppc_vcore *vc)
अणु
	काष्ठा dtl_entry *dt;
	काष्ठा lppaca *vpa;
	अचिन्हित दीर्घ stolen;
	अचिन्हित दीर्घ core_stolen;
	u64 now;
	अचिन्हित दीर्घ flags;

	dt = vcpu->arch.dtl_ptr;
	vpa = vcpu->arch.vpa.pinned_addr;
	now = mftb();
	core_stolen = vcore_stolen_समय(vc, now);
	stolen = core_stolen - vcpu->arch.stolen_logged;
	vcpu->arch.stolen_logged = core_stolen;
	spin_lock_irqsave(&vcpu->arch.tbacct_lock, flags);
	stolen += vcpu->arch.busy_stolen;
	vcpu->arch.busy_stolen = 0;
	spin_unlock_irqrestore(&vcpu->arch.tbacct_lock, flags);
	अगर (!dt || !vpa)
		वापस;
	स_रखो(dt, 0, माप(काष्ठा dtl_entry));
	dt->dispatch_reason = 7;
	dt->processor_id = cpu_to_be16(vc->pcpu + vcpu->arch.ptid);
	dt->समयbase = cpu_to_be64(now + vc->tb_offset);
	dt->enqueue_to_dispatch_समय = cpu_to_be32(stolen);
	dt->srr0 = cpu_to_be64(kvmppc_get_pc(vcpu));
	dt->srr1 = cpu_to_be64(vcpu->arch.shregs.msr);
	++dt;
	अगर (dt == vcpu->arch.dtl.pinned_end)
		dt = vcpu->arch.dtl.pinned_addr;
	vcpu->arch.dtl_ptr = dt;
	/* order writing *dt vs. writing vpa->dtl_idx */
	smp_wmb();
	vpa->dtl_idx = cpu_to_be64(++vcpu->arch.dtl_index);
	vcpu->arch.dtl.dirty = true;
पूर्ण

/* See अगर there is a करोorbell पूर्णांकerrupt pending क्रम a vcpu */
अटल bool kvmppc_करोorbell_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक thr;
	काष्ठा kvmppc_vcore *vc;

	अगर (vcpu->arch.करोorbell_request)
		वापस true;
	/*
	 * Ensure that the पढ़ो of vcore->dpdes comes after the पढ़ो
	 * of vcpu->करोorbell_request.  This barrier matches the
	 * smp_wmb() in kvmppc_guest_entry_inject().
	 */
	smp_rmb();
	vc = vcpu->arch.vcore;
	thr = vcpu->vcpu_id - vc->first_vcpuid;
	वापस !!(vc->dpdes & (1 << thr));
पूर्ण

अटल bool kvmppc_घातer8_compatible(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.vcore->arch_compat >= PVR_ARCH_207)
		वापस true;
	अगर ((!vcpu->arch.vcore->arch_compat) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक kvmppc_h_set_mode(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ mflags,
			     अचिन्हित दीर्घ resource, अचिन्हित दीर्घ value1,
			     अचिन्हित दीर्घ value2)
अणु
	चयन (resource) अणु
	हाल H_SET_MODE_RESOURCE_SET_CIABR:
		अगर (!kvmppc_घातer8_compatible(vcpu))
			वापस H_P2;
		अगर (value2)
			वापस H_P4;
		अगर (mflags)
			वापस H_UNSUPPORTED_FLAG_START;
		/* Guests can't अवरोधpoपूर्णांक the hypervisor */
		अगर ((value1 & CIABR_PRIV) == CIABR_PRIV_HYPER)
			वापस H_P3;
		vcpu->arch.ciabr  = value1;
		वापस H_SUCCESS;
	हाल H_SET_MODE_RESOURCE_SET_DAWR0:
		अगर (!kvmppc_घातer8_compatible(vcpu))
			वापस H_P2;
		अगर (!ppc_अवरोधpoपूर्णांक_available())
			वापस H_P2;
		अगर (mflags)
			वापस H_UNSUPPORTED_FLAG_START;
		अगर (value2 & DABRX_HYP)
			वापस H_P4;
		vcpu->arch.dawr0  = value1;
		vcpu->arch.dawrx0 = value2;
		वापस H_SUCCESS;
	हाल H_SET_MODE_RESOURCE_SET_DAWR1:
		अगर (!kvmppc_घातer8_compatible(vcpu))
			वापस H_P2;
		अगर (!ppc_अवरोधpoपूर्णांक_available())
			वापस H_P2;
		अगर (!cpu_has_feature(CPU_FTR_DAWR1))
			वापस H_P2;
		अगर (!vcpu->kvm->arch.dawr1_enabled)
			वापस H_FUNCTION;
		अगर (mflags)
			वापस H_UNSUPPORTED_FLAG_START;
		अगर (value2 & DABRX_HYP)
			वापस H_P4;
		vcpu->arch.dawr1  = value1;
		vcpu->arch.dawrx1 = value2;
		वापस H_SUCCESS;
	हाल H_SET_MODE_RESOURCE_ADDR_TRANS_MODE:
		/*
		 * KVM करोes not support mflags=2 (AIL=2) and AIL=1 is reserved.
		 * Keep this in synch with kvmppc_filter_guest_lpcr_hv.
		 */
		अगर (mflags != 0 && mflags != 3)
			वापस H_UNSUPPORTED_FLAG_START;
		वापस H_TOO_HARD;
	शेष:
		वापस H_TOO_HARD;
	पूर्ण
पूर्ण

/* Copy guest memory in place - must reside within a single memslot */
अटल पूर्णांक kvmppc_copy_guest(काष्ठा kvm *kvm, gpa_t to, gpa_t from,
				  अचिन्हित दीर्घ len)
अणु
	काष्ठा kvm_memory_slot *to_memslot = शून्य;
	काष्ठा kvm_memory_slot *from_memslot = शून्य;
	अचिन्हित दीर्घ to_addr, from_addr;
	पूर्णांक r;

	/* Get HPA क्रम from address */
	from_memslot = gfn_to_memslot(kvm, from >> PAGE_SHIFT);
	अगर (!from_memslot)
		वापस -EFAULT;
	अगर ((from + len) >= ((from_memslot->base_gfn + from_memslot->npages)
			     << PAGE_SHIFT))
		वापस -EINVAL;
	from_addr = gfn_to_hva_memslot(from_memslot, from >> PAGE_SHIFT);
	अगर (kvm_is_error_hva(from_addr))
		वापस -EFAULT;
	from_addr |= (from & (PAGE_SIZE - 1));

	/* Get HPA क्रम to address */
	to_memslot = gfn_to_memslot(kvm, to >> PAGE_SHIFT);
	अगर (!to_memslot)
		वापस -EFAULT;
	अगर ((to + len) >= ((to_memslot->base_gfn + to_memslot->npages)
			   << PAGE_SHIFT))
		वापस -EINVAL;
	to_addr = gfn_to_hva_memslot(to_memslot, to >> PAGE_SHIFT);
	अगर (kvm_is_error_hva(to_addr))
		वापस -EFAULT;
	to_addr |= (to & (PAGE_SIZE - 1));

	/* Perक्रमm copy */
	r = raw_copy_in_user((व्योम __user *)to_addr, (व्योम __user *)from_addr,
			     len);
	अगर (r)
		वापस -EFAULT;
	mark_page_dirty(kvm, to >> PAGE_SHIFT);
	वापस 0;
पूर्ण

अटल दीर्घ kvmppc_h_page_init(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
			       अचिन्हित दीर्घ dest, अचिन्हित दीर्घ src)
अणु
	u64 pg_sz = SZ_4K;		/* 4K page size */
	u64 pg_mask = SZ_4K - 1;
	पूर्णांक ret;

	/* Check क्रम invalid flags (H_PAGE_SET_LOANED covers all CMO flags) */
	अगर (flags & ~(H_ICACHE_INVALIDATE | H_ICACHE_SYNCHRONIZE |
		      H_ZERO_PAGE | H_COPY_PAGE | H_PAGE_SET_LOANED))
		वापस H_PARAMETER;

	/* dest (and src अगर copy_page flag set) must be page aligned */
	अगर ((dest & pg_mask) || ((flags & H_COPY_PAGE) && (src & pg_mask)))
		वापस H_PARAMETER;

	/* zero and/or copy the page as determined by the flags */
	अगर (flags & H_COPY_PAGE) अणु
		ret = kvmppc_copy_guest(vcpu->kvm, dest, src, pg_sz);
		अगर (ret < 0)
			वापस H_PARAMETER;
	पूर्ण अन्यथा अगर (flags & H_ZERO_PAGE) अणु
		ret = kvm_clear_guest(vcpu->kvm, dest, pg_sz);
		अगर (ret < 0)
			वापस H_PARAMETER;
	पूर्ण

	/* We can ignore the reमुख्यing flags */

	वापस H_SUCCESS;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_yield_to(काष्ठा kvm_vcpu *target)
अणु
	काष्ठा kvmppc_vcore *vcore = target->arch.vcore;

	/*
	 * We expect to have been called by the real mode handler
	 * (kvmppc_rm_h_confer()) which would have directly वापसed
	 * H_SUCCESS अगर the source vcore wasn't idle (e.g. अगर it may
	 * have useful work to करो and should not confer) so we करोn't
	 * recheck that here.
	 */

	spin_lock(&vcore->lock);
	अगर (target->arch.state == KVMPPC_VCPU_RUNNABLE &&
	    vcore->vcore_state != VCORE_INACTIVE &&
	    vcore->runner)
		target = vcore->runner;
	spin_unlock(&vcore->lock);

	वापस kvm_vcpu_yield_to(target);
पूर्ण

अटल पूर्णांक kvmppc_get_yield_count(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक yield_count = 0;
	काष्ठा lppaca *lppaca;

	spin_lock(&vcpu->arch.vpa_update_lock);
	lppaca = (काष्ठा lppaca *)vcpu->arch.vpa.pinned_addr;
	अगर (lppaca)
		yield_count = be32_to_cpu(lppaca->yield_count);
	spin_unlock(&vcpu->arch.vpa_update_lock);
	वापस yield_count;
पूर्ण

पूर्णांक kvmppc_pseries_करो_hcall(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ req = kvmppc_get_gpr(vcpu, 3);
	अचिन्हित दीर्घ target, ret = H_SUCCESS;
	पूर्णांक yield_count;
	काष्ठा kvm_vcpu *tvcpu;
	पूर्णांक idx, rc;

	अगर (req <= MAX_HCALL_OPCODE &&
	    !test_bit(req/4, vcpu->kvm->arch.enabled_hcalls))
		वापस RESUME_HOST;

	चयन (req) अणु
	हाल H_CEDE:
		अवरोध;
	हाल H_PROD:
		target = kvmppc_get_gpr(vcpu, 4);
		tvcpu = kvmppc_find_vcpu(vcpu->kvm, target);
		अगर (!tvcpu) अणु
			ret = H_PARAMETER;
			अवरोध;
		पूर्ण
		tvcpu->arch.prodded = 1;
		smp_mb();
		अगर (tvcpu->arch.ceded)
			kvmppc_fast_vcpu_kick_hv(tvcpu);
		अवरोध;
	हाल H_CONFER:
		target = kvmppc_get_gpr(vcpu, 4);
		अगर (target == -1)
			अवरोध;
		tvcpu = kvmppc_find_vcpu(vcpu->kvm, target);
		अगर (!tvcpu) अणु
			ret = H_PARAMETER;
			अवरोध;
		पूर्ण
		yield_count = kvmppc_get_gpr(vcpu, 5);
		अगर (kvmppc_get_yield_count(tvcpu) != yield_count)
			अवरोध;
		kvm_arch_vcpu_yield_to(tvcpu);
		अवरोध;
	हाल H_REGISTER_VPA:
		ret = करो_h_रेजिस्टर_vpa(vcpu, kvmppc_get_gpr(vcpu, 4),
					kvmppc_get_gpr(vcpu, 5),
					kvmppc_get_gpr(vcpu, 6));
		अवरोध;
	हाल H_RTAS:
		अगर (list_empty(&vcpu->kvm->arch.rtas_tokens))
			वापस RESUME_HOST;

		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		rc = kvmppc_rtas_hcall(vcpu);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

		अगर (rc == -ENOENT)
			वापस RESUME_HOST;
		अन्यथा अगर (rc == 0)
			अवरोध;

		/* Send the error out to userspace via KVM_RUN */
		वापस rc;
	हाल H_LOGICAL_CI_LOAD:
		ret = kvmppc_h_logical_ci_load(vcpu);
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
	हाल H_LOGICAL_CI_STORE:
		ret = kvmppc_h_logical_ci_store(vcpu);
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
	हाल H_SET_MODE:
		ret = kvmppc_h_set_mode(vcpu, kvmppc_get_gpr(vcpu, 4),
					kvmppc_get_gpr(vcpu, 5),
					kvmppc_get_gpr(vcpu, 6),
					kvmppc_get_gpr(vcpu, 7));
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
	हाल H_XIRR:
	हाल H_CPPR:
	हाल H_EOI:
	हाल H_IPI:
	हाल H_IPOLL:
	हाल H_XIRR_X:
		अगर (kvmppc_xics_enabled(vcpu)) अणु
			अगर (xics_on_xive()) अणु
				ret = H_NOT_AVAILABLE;
				वापस RESUME_GUEST;
			पूर्ण
			ret = kvmppc_xics_hcall(vcpu, req);
			अवरोध;
		पूर्ण
		वापस RESUME_HOST;
	हाल H_SET_DABR:
		ret = kvmppc_h_set_dabr(vcpu, kvmppc_get_gpr(vcpu, 4));
		अवरोध;
	हाल H_SET_XDABR:
		ret = kvmppc_h_set_xdabr(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5));
		अवरोध;
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	हाल H_GET_TCE:
		ret = kvmppc_h_get_tce(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5));
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
	हाल H_PUT_TCE:
		ret = kvmppc_h_put_tce(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5),
						kvmppc_get_gpr(vcpu, 6));
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
	हाल H_PUT_TCE_INसूचीECT:
		ret = kvmppc_h_put_tce_indirect(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5),
						kvmppc_get_gpr(vcpu, 6),
						kvmppc_get_gpr(vcpu, 7));
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
	हाल H_STUFF_TCE:
		ret = kvmppc_h_stuff_tce(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5),
						kvmppc_get_gpr(vcpu, 6),
						kvmppc_get_gpr(vcpu, 7));
		अगर (ret == H_TOO_HARD)
			वापस RESUME_HOST;
		अवरोध;
#पूर्ण_अगर
	हाल H_RANDOM:
		अगर (!घातernv_get_अक्रमom_दीर्घ(&vcpu->arch.regs.gpr[4]))
			ret = H_HARDWARE;
		अवरोध;

	हाल H_SET_PARTITION_TABLE:
		ret = H_FUNCTION;
		अगर (nesting_enabled(vcpu->kvm))
			ret = kvmhv_set_partition_table(vcpu);
		अवरोध;
	हाल H_ENTER_NESTED:
		ret = H_FUNCTION;
		अगर (!nesting_enabled(vcpu->kvm))
			अवरोध;
		ret = kvmhv_enter_nested_guest(vcpu);
		अगर (ret == H_INTERRUPT) अणु
			kvmppc_set_gpr(vcpu, 3, 0);
			vcpu->arch.hcall_needed = 0;
			वापस -EINTR;
		पूर्ण अन्यथा अगर (ret == H_TOO_HARD) अणु
			kvmppc_set_gpr(vcpu, 3, 0);
			vcpu->arch.hcall_needed = 0;
			वापस RESUME_HOST;
		पूर्ण
		अवरोध;
	हाल H_TLB_INVALIDATE:
		ret = H_FUNCTION;
		अगर (nesting_enabled(vcpu->kvm))
			ret = kvmhv_करो_nested_tlbie(vcpu);
		अवरोध;
	हाल H_COPY_TOFROM_GUEST:
		ret = H_FUNCTION;
		अगर (nesting_enabled(vcpu->kvm))
			ret = kvmhv_copy_tofrom_guest_nested(vcpu);
		अवरोध;
	हाल H_PAGE_INIT:
		ret = kvmppc_h_page_init(vcpu, kvmppc_get_gpr(vcpu, 4),
					 kvmppc_get_gpr(vcpu, 5),
					 kvmppc_get_gpr(vcpu, 6));
		अवरोध;
	हाल H_SVM_PAGE_IN:
		ret = H_UNSUPPORTED;
		अगर (kvmppc_get_srr1(vcpu) & MSR_S)
			ret = kvmppc_h_svm_page_in(vcpu->kvm,
						   kvmppc_get_gpr(vcpu, 4),
						   kvmppc_get_gpr(vcpu, 5),
						   kvmppc_get_gpr(vcpu, 6));
		अवरोध;
	हाल H_SVM_PAGE_OUT:
		ret = H_UNSUPPORTED;
		अगर (kvmppc_get_srr1(vcpu) & MSR_S)
			ret = kvmppc_h_svm_page_out(vcpu->kvm,
						    kvmppc_get_gpr(vcpu, 4),
						    kvmppc_get_gpr(vcpu, 5),
						    kvmppc_get_gpr(vcpu, 6));
		अवरोध;
	हाल H_SVM_INIT_START:
		ret = H_UNSUPPORTED;
		अगर (kvmppc_get_srr1(vcpu) & MSR_S)
			ret = kvmppc_h_svm_init_start(vcpu->kvm);
		अवरोध;
	हाल H_SVM_INIT_DONE:
		ret = H_UNSUPPORTED;
		अगर (kvmppc_get_srr1(vcpu) & MSR_S)
			ret = kvmppc_h_svm_init_करोne(vcpu->kvm);
		अवरोध;
	हाल H_SVM_INIT_ABORT:
		/*
		 * Even अगर that call is made by the Ultravisor, the SSR1 value
		 * is the guest context one, with the secure bit clear as it has
		 * not yet been secured. So we can't check it here.
		 * Instead the kvm->arch.secure_guest flag is checked inside
		 * kvmppc_h_svm_init_पात().
		 */
		ret = kvmppc_h_svm_init_पात(vcpu->kvm);
		अवरोध;

	शेष:
		वापस RESUME_HOST;
	पूर्ण
	kvmppc_set_gpr(vcpu, 3, ret);
	vcpu->arch.hcall_needed = 0;
	वापस RESUME_GUEST;
पूर्ण

/*
 * Handle H_CEDE in the nested भवization हाल where we haven't
 * called the real-mode hcall handlers in book3s_hv_rmhandlers.S.
 * This has to be करोne early, not in kvmppc_pseries_करो_hcall(), so
 * that the cede logic in kvmppc_run_single_vcpu() works properly.
 */
अटल व्योम kvmppc_nested_cede(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.shregs.msr |= MSR_EE;
	vcpu->arch.ceded = 1;
	smp_mb();
	अगर (vcpu->arch.prodded) अणु
		vcpu->arch.prodded = 0;
		smp_mb();
		vcpu->arch.ceded = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_hcall_impl_hv(अचिन्हित दीर्घ cmd)
अणु
	चयन (cmd) अणु
	हाल H_CEDE:
	हाल H_PROD:
	हाल H_CONFER:
	हाल H_REGISTER_VPA:
	हाल H_SET_MODE:
	हाल H_LOGICAL_CI_LOAD:
	हाल H_LOGICAL_CI_STORE:
#अगर_घोषित CONFIG_KVM_XICS
	हाल H_XIRR:
	हाल H_CPPR:
	हाल H_EOI:
	हाल H_IPI:
	हाल H_IPOLL:
	हाल H_XIRR_X:
#पूर्ण_अगर
	हाल H_PAGE_INIT:
		वापस 1;
	पूर्ण

	/* See अगर it's in the real-mode table */
	वापस kvmppc_hcall_impl_hv_realmode(cmd);
पूर्ण

अटल पूर्णांक kvmppc_emulate_debug_inst(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 last_inst;

	अगर (kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst) !=
					EMULATE_DONE) अणु
		/*
		 * Fetch failed, so वापस to guest and
		 * try executing it again.
		 */
		वापस RESUME_GUEST;
	पूर्ण

	अगर (last_inst == KVMPPC_INST_SW_BREAKPOINT) अणु
		vcpu->run->निकास_reason = KVM_EXIT_DEBUG;
		vcpu->run->debug.arch.address = kvmppc_get_pc(vcpu);
		वापस RESUME_HOST;
	पूर्ण अन्यथा अणु
		kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
		वापस RESUME_GUEST;
	पूर्ण
पूर्ण

अटल व्योम करो_nothing(व्योम *x)
अणु
पूर्ण

अटल अचिन्हित दीर्घ kvmppc_पढ़ो_dpdes(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक thr, cpu, pcpu, nthपढ़ोs;
	काष्ठा kvm_vcpu *v;
	अचिन्हित दीर्घ dpdes;

	nthपढ़ोs = vcpu->kvm->arch.emul_smt_mode;
	dpdes = 0;
	cpu = vcpu->vcpu_id & ~(nthपढ़ोs - 1);
	क्रम (thr = 0; thr < nthपढ़ोs; ++thr, ++cpu) अणु
		v = kvmppc_find_vcpu(vcpu->kvm, cpu);
		अगर (!v)
			जारी;
		/*
		 * If the vcpu is currently running on a physical cpu thपढ़ो,
		 * पूर्णांकerrupt it in order to pull it out of the guest briefly,
		 * which will update its vcore->dpdes value.
		 */
		pcpu = READ_ONCE(v->cpu);
		अगर (pcpu >= 0)
			smp_call_function_single(pcpu, करो_nothing, शून्य, 1);
		अगर (kvmppc_करोorbell_pending(v))
			dpdes |= 1 << thr;
	पूर्ण
	वापस dpdes;
पूर्ण

/*
 * On POWER9, emulate करोorbell-related inकाष्ठाions in order to
 * give the guest the illusion of running on a multi-thपढ़ोed core.
 * The inकाष्ठाions emulated are msgsndp, msgclrp, mfspr TIR,
 * and mfspr DPDES.
 */
अटल पूर्णांक kvmppc_emulate_करोorbell_instr(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 inst, rb, thr;
	अचिन्हित दीर्घ arg;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_vcpu *tvcpu;

	अगर (kvmppc_get_last_inst(vcpu, INST_GENERIC, &inst) != EMULATE_DONE)
		वापस RESUME_GUEST;
	अगर (get_op(inst) != 31)
		वापस EMULATE_FAIL;
	rb = get_rb(inst);
	thr = vcpu->vcpu_id & (kvm->arch.emul_smt_mode - 1);
	चयन (get_xop(inst)) अणु
	हाल OP_31_XOP_MSGSNDP:
		arg = kvmppc_get_gpr(vcpu, rb);
		अगर (((arg >> 27) & 0x1f) != PPC_DBELL_SERVER)
			अवरोध;
		arg &= 0x7f;
		अगर (arg >= kvm->arch.emul_smt_mode)
			अवरोध;
		tvcpu = kvmppc_find_vcpu(kvm, vcpu->vcpu_id - thr + arg);
		अगर (!tvcpu)
			अवरोध;
		अगर (!tvcpu->arch.करोorbell_request) अणु
			tvcpu->arch.करोorbell_request = 1;
			kvmppc_fast_vcpu_kick_hv(tvcpu);
		पूर्ण
		अवरोध;
	हाल OP_31_XOP_MSGCLRP:
		arg = kvmppc_get_gpr(vcpu, rb);
		अगर (((arg >> 27) & 0x1f) != PPC_DBELL_SERVER)
			अवरोध;
		vcpu->arch.vcore->dpdes = 0;
		vcpu->arch.करोorbell_request = 0;
		अवरोध;
	हाल OP_31_XOP_MFSPR:
		चयन (get_sprn(inst)) अणु
		हाल SPRN_TIR:
			arg = thr;
			अवरोध;
		हाल SPRN_DPDES:
			arg = kvmppc_पढ़ो_dpdes(vcpu);
			अवरोध;
		शेष:
			वापस EMULATE_FAIL;
		पूर्ण
		kvmppc_set_gpr(vcpu, get_rt(inst), arg);
		अवरोध;
	शेष:
		वापस EMULATE_FAIL;
	पूर्ण
	kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
	वापस RESUME_GUEST;
पूर्ण

अटल पूर्णांक kvmppc_handle_निकास_hv(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक r = RESUME_HOST;

	vcpu->stat.sum_निकासs++;

	/*
	 * This can happen अगर an पूर्णांकerrupt occurs in the last stages
	 * of guest entry or the first stages of guest निकास (i.e. after
	 * setting paca->kvm_hstate.in_guest to KVM_GUEST_MODE_GUEST_HV
	 * and beक्रमe setting it to KVM_GUEST_MODE_HOST_HV).
	 * That can happen due to a bug, or due to a machine check
	 * occurring at just the wrong समय.
	 */
	अगर (vcpu->arch.shregs.msr & MSR_HV) अणु
		prपूर्णांकk(KERN_EMERG "KVM trap in HV mode!\n");
		prपूर्णांकk(KERN_EMERG "trap=0x%x | pc=0x%lx | msr=0x%llx\n",
			vcpu->arch.trap, kvmppc_get_pc(vcpu),
			vcpu->arch.shregs.msr);
		kvmppc_dump_regs(vcpu);
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		run->hw.hardware_निकास_reason = vcpu->arch.trap;
		वापस RESUME_HOST;
	पूर्ण
	run->निकास_reason = KVM_EXIT_UNKNOWN;
	run->पढ़ोy_क्रम_पूर्णांकerrupt_injection = 1;
	चयन (vcpu->arch.trap) अणु
	/* We're good on these - the host merely wanted to get our attention */
	हाल BOOK3S_INTERRUPT_HV_DECREMENTER:
		vcpu->stat.dec_निकासs++;
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_EXTERNAL:
	हाल BOOK3S_INTERRUPT_H_DOORBELL:
	हाल BOOK3S_INTERRUPT_H_VIRT:
		vcpu->stat.ext_पूर्णांकr_निकासs++;
		r = RESUME_GUEST;
		अवरोध;
	/* SR/HMI/PMI are HV पूर्णांकerrupts that host has handled. Resume guest.*/
	हाल BOOK3S_INTERRUPT_HMI:
	हाल BOOK3S_INTERRUPT_PERFMON:
	हाल BOOK3S_INTERRUPT_SYSTEM_RESET:
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_MACHINE_CHECK: अणु
		अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
					      DEFAULT_RATELIMIT_BURST);
		/*
		 * Prपूर्णांक the MCE event to host console. Ratelimit so the guest
		 * can't flood the host log.
		 */
		अगर (__ratelimit(&rs))
			machine_check_prपूर्णांक_event_info(&vcpu->arch.mce_evt,false, true);

		/*
		 * If the guest can करो FWNMI, निकास to userspace so it can
		 * deliver a FWNMI to the guest.
		 * Otherwise we synthesize a machine check क्रम the guest
		 * so that it knows that the machine check occurred.
		 */
		अगर (!vcpu->kvm->arch.fwnmi_enabled) अणु
			uदीर्घ flags = vcpu->arch.shregs.msr & 0x083c0000;
			kvmppc_core_queue_machine_check(vcpu, flags);
			r = RESUME_GUEST;
			अवरोध;
		पूर्ण

		/* Exit to guest with KVM_EXIT_NMI as निकास reason */
		run->निकास_reason = KVM_EXIT_NMI;
		run->hw.hardware_निकास_reason = vcpu->arch.trap;
		/* Clear out the old NMI status from run->flags */
		run->flags &= ~KVM_RUN_PPC_NMI_DISP_MASK;
		/* Now set the NMI status */
		अगर (vcpu->arch.mce_evt.disposition == MCE_DISPOSITION_RECOVERED)
			run->flags |= KVM_RUN_PPC_NMI_DISP_FULLY_RECOV;
		अन्यथा
			run->flags |= KVM_RUN_PPC_NMI_DISP_NOT_RECOV;

		r = RESUME_HOST;
		अवरोध;
	पूर्ण
	हाल BOOK3S_INTERRUPT_PROGRAM:
	अणु
		uदीर्घ flags;
		/*
		 * Normally program पूर्णांकerrupts are delivered directly
		 * to the guest by the hardware, but we can get here
		 * as a result of a hypervisor emulation पूर्णांकerrupt
		 * (e40) getting turned पूर्णांकo a 700 by BML RTAS.
		 */
		flags = vcpu->arch.shregs.msr & 0x1f0000ull;
		kvmppc_core_queue_program(vcpu, flags);
		r = RESUME_GUEST;
		अवरोध;
	पूर्ण
	हाल BOOK3S_INTERRUPT_SYSCALL:
	अणु
		/* hcall - punt to userspace */
		पूर्णांक i;

		/* hypercall with MSR_PR has alपढ़ोy been handled in rmode,
		 * and never reaches here.
		 */

		run->papr_hcall.nr = kvmppc_get_gpr(vcpu, 3);
		क्रम (i = 0; i < 9; ++i)
			run->papr_hcall.args[i] = kvmppc_get_gpr(vcpu, 4 + i);
		run->निकास_reason = KVM_EXIT_PAPR_HCALL;
		vcpu->arch.hcall_needed = 1;
		r = RESUME_HOST;
		अवरोध;
	पूर्ण
	/*
	 * We get these next two अगर the guest accesses a page which it thinks
	 * it has mapped but which is not actually present, either because
	 * it is क्रम an emulated I/O device or because the corresonding
	 * host page has been paged out.  Any other HDSI/HISI पूर्णांकerrupts
	 * have been handled alपढ़ोy.
	 */
	हाल BOOK3S_INTERRUPT_H_DATA_STORAGE:
		r = RESUME_PAGE_FAULT;
		अवरोध;
	हाल BOOK3S_INTERRUPT_H_INST_STORAGE:
		vcpu->arch.fault_dar = kvmppc_get_pc(vcpu);
		vcpu->arch.fault_dsisr = vcpu->arch.shregs.msr &
			DSISR_SRR1_MATCH_64S;
		अगर (vcpu->arch.shregs.msr & HSRR1_HISI_WRITE)
			vcpu->arch.fault_dsisr |= DSISR_ISSTORE;
		r = RESUME_PAGE_FAULT;
		अवरोध;
	/*
	 * This occurs अगर the guest executes an illegal inकाष्ठाion.
	 * If the guest debug is disabled, generate a program पूर्णांकerrupt
	 * to the guest. If guest debug is enabled, we need to check
	 * whether the inकाष्ठाion is a software अवरोधpoपूर्णांक inकाष्ठाion.
	 * Accordingly वापस to Guest or Host.
	 */
	हाल BOOK3S_INTERRUPT_H_EMUL_ASSIST:
		अगर (vcpu->arch.emul_inst != KVM_INST_FETCH_FAILED)
			vcpu->arch.last_inst = kvmppc_need_byteswap(vcpu) ?
				swab32(vcpu->arch.emul_inst) :
				vcpu->arch.emul_inst;
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP) अणु
			r = kvmppc_emulate_debug_inst(vcpu);
		पूर्ण अन्यथा अणु
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			r = RESUME_GUEST;
		पूर्ण
		अवरोध;
	/*
	 * This occurs अगर the guest (kernel or userspace), करोes something that
	 * is prohibited by HFSCR.
	 * On POWER9, this could be a करोorbell inकाष्ठाion that we need
	 * to emulate.
	 * Otherwise, we just generate a program पूर्णांकerrupt to the guest.
	 */
	हाल BOOK3S_INTERRUPT_H_FAC_UNAVAIL:
		r = EMULATE_FAIL;
		अगर (((vcpu->arch.hfscr >> 56) == FSCR_MSGP_LG) &&
		    cpu_has_feature(CPU_FTR_ARCH_300))
			r = kvmppc_emulate_करोorbell_instr(vcpu);
		अगर (r == EMULATE_FAIL) अणु
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			r = RESUME_GUEST;
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल BOOK3S_INTERRUPT_HV_SOFTPATCH:
		/*
		 * This occurs क्रम various TM-related inकाष्ठाions that
		 * we need to emulate on POWER9 DD2.2.  We have alपढ़ोy
		 * handled the हालs where the guest was in real-suspend
		 * mode and was transitioning to transactional state.
		 */
		r = kvmhv_p9_पंचांग_emulation(vcpu);
		अवरोध;
#पूर्ण_अगर

	हाल BOOK3S_INTERRUPT_HV_RM_HARD:
		r = RESUME_PASSTHROUGH;
		अवरोध;
	शेष:
		kvmppc_dump_regs(vcpu);
		prपूर्णांकk(KERN_EMERG "trap=0x%x | pc=0x%lx | msr=0x%llx\n",
			vcpu->arch.trap, kvmppc_get_pc(vcpu),
			vcpu->arch.shregs.msr);
		run->hw.hardware_निकास_reason = vcpu->arch.trap;
		r = RESUME_HOST;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_handle_nested_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;
	पूर्णांक srcu_idx;

	vcpu->stat.sum_निकासs++;

	/*
	 * This can happen अगर an पूर्णांकerrupt occurs in the last stages
	 * of guest entry or the first stages of guest निकास (i.e. after
	 * setting paca->kvm_hstate.in_guest to KVM_GUEST_MODE_GUEST_HV
	 * and beक्रमe setting it to KVM_GUEST_MODE_HOST_HV).
	 * That can happen due to a bug, or due to a machine check
	 * occurring at just the wrong समय.
	 */
	अगर (vcpu->arch.shregs.msr & MSR_HV) अणु
		pr_emerg("KVM trap in HV mode while nested!\n");
		pr_emerg("trap=0x%x | pc=0x%lx | msr=0x%llx\n",
			 vcpu->arch.trap, kvmppc_get_pc(vcpu),
			 vcpu->arch.shregs.msr);
		kvmppc_dump_regs(vcpu);
		वापस RESUME_HOST;
	पूर्ण
	चयन (vcpu->arch.trap) अणु
	/* We're good on these - the host merely wanted to get our attention */
	हाल BOOK3S_INTERRUPT_HV_DECREMENTER:
		vcpu->stat.dec_निकासs++;
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_EXTERNAL:
		vcpu->stat.ext_पूर्णांकr_निकासs++;
		r = RESUME_HOST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_H_DOORBELL:
	हाल BOOK3S_INTERRUPT_H_VIRT:
		vcpu->stat.ext_पूर्णांकr_निकासs++;
		r = RESUME_GUEST;
		अवरोध;
	/* SR/HMI/PMI are HV पूर्णांकerrupts that host has handled. Resume guest.*/
	हाल BOOK3S_INTERRUPT_HMI:
	हाल BOOK3S_INTERRUPT_PERFMON:
	हाल BOOK3S_INTERRUPT_SYSTEM_RESET:
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_MACHINE_CHECK:
	अणु
		अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
					      DEFAULT_RATELIMIT_BURST);
		/* Pass the machine check to the L1 guest */
		r = RESUME_HOST;
		/* Prपूर्णांक the MCE event to host console. */
		अगर (__ratelimit(&rs))
			machine_check_prपूर्णांक_event_info(&vcpu->arch.mce_evt, false, true);
		अवरोध;
	पूर्ण
	/*
	 * We get these next two अगर the guest accesses a page which it thinks
	 * it has mapped but which is not actually present, either because
	 * it is क्रम an emulated I/O device or because the corresonding
	 * host page has been paged out.
	 */
	हाल BOOK3S_INTERRUPT_H_DATA_STORAGE:
		srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = kvmhv_nested_page_fault(vcpu);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
		अवरोध;
	हाल BOOK3S_INTERRUPT_H_INST_STORAGE:
		vcpu->arch.fault_dar = kvmppc_get_pc(vcpu);
		vcpu->arch.fault_dsisr = kvmppc_get_msr(vcpu) &
					 DSISR_SRR1_MATCH_64S;
		अगर (vcpu->arch.shregs.msr & HSRR1_HISI_WRITE)
			vcpu->arch.fault_dsisr |= DSISR_ISSTORE;
		srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = kvmhv_nested_page_fault(vcpu);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
		अवरोध;

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल BOOK3S_INTERRUPT_HV_SOFTPATCH:
		/*
		 * This occurs क्रम various TM-related inकाष्ठाions that
		 * we need to emulate on POWER9 DD2.2.  We have alपढ़ोy
		 * handled the हालs where the guest was in real-suspend
		 * mode and was transitioning to transactional state.
		 */
		r = kvmhv_p9_पंचांग_emulation(vcpu);
		अवरोध;
#पूर्ण_अगर

	हाल BOOK3S_INTERRUPT_HV_RM_HARD:
		vcpu->arch.trap = 0;
		r = RESUME_GUEST;
		अगर (!xics_on_xive())
			kvmppc_xics_rm_complete(vcpu, 0);
		अवरोध;
	शेष:
		r = RESUME_HOST;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_get_sregs_hv(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक i;

	स_रखो(sregs, 0, माप(काष्ठा kvm_sregs));
	sregs->pvr = vcpu->arch.pvr;
	क्रम (i = 0; i < vcpu->arch.slb_max; i++) अणु
		sregs->u.s.ppc64.slb[i].slbe = vcpu->arch.slb[i].orige;
		sregs->u.s.ppc64.slb[i].slbv = vcpu->arch.slb[i].origv;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_set_sregs_hv(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक i, j;

	/* Only accept the same PVR as the host's, since we can't spoof it */
	अगर (sregs->pvr != vcpu->arch.pvr)
		वापस -EINVAL;

	j = 0;
	क्रम (i = 0; i < vcpu->arch.slb_nr; i++) अणु
		अगर (sregs->u.s.ppc64.slb[i].slbe & SLB_ESID_V) अणु
			vcpu->arch.slb[j].orige = sregs->u.s.ppc64.slb[i].slbe;
			vcpu->arch.slb[j].origv = sregs->u.s.ppc64.slb[i].slbv;
			++j;
		पूर्ण
	पूर्ण
	vcpu->arch.slb_max = j;

	वापस 0;
पूर्ण

/*
 * Enक्रमce limits on guest LPCR values based on hardware availability,
 * guest configuration, and possibly hypervisor support and security
 * concerns.
 */
अचिन्हित दीर्घ kvmppc_filter_lpcr_hv(काष्ठा kvm *kvm, अचिन्हित दीर्घ lpcr)
अणु
	/* LPCR_TC only applies to HPT guests */
	अगर (kvm_is_radix(kvm))
		lpcr &= ~LPCR_TC;

	/* On POWER8 and above, userspace can modअगरy AIL */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		lpcr &= ~LPCR_AIL;
	अगर ((lpcr & LPCR_AIL) != LPCR_AIL_3)
		lpcr &= ~LPCR_AIL; /* LPCR[AIL]=1/2 is disallowed */

	/*
	 * On POWER9, allow userspace to enable large decrementer क्रम the
	 * guest, whether or not the host has it enabled.
	 */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		lpcr &= ~LPCR_LD;

	वापस lpcr;
पूर्ण

अटल व्योम verअगरy_lpcr(काष्ठा kvm *kvm, अचिन्हित दीर्घ lpcr)
अणु
	अगर (lpcr != kvmppc_filter_lpcr_hv(kvm, lpcr)) अणु
		WARN_ONCE(1, "lpcr 0x%lx differs from filtered 0x%lx\n",
			  lpcr, kvmppc_filter_lpcr_hv(kvm, lpcr));
	पूर्ण
पूर्ण

अटल व्योम kvmppc_set_lpcr(काष्ठा kvm_vcpu *vcpu, u64 new_lpcr,
		bool preserve_top32)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	u64 mask;

	spin_lock(&vc->lock);

	/*
	 * Userspace can only modअगरy
	 * DPFD (शेष prefetch depth), ILE (पूर्णांकerrupt little-endian),
	 * TC (translation control), AIL (alternate पूर्णांकerrupt location),
	 * LD (large decrementer).
	 * These are subject to restrictions from kvmppc_filter_lcpr_hv().
	 */
	mask = LPCR_DPFD | LPCR_ILE | LPCR_TC | LPCR_AIL | LPCR_LD;

	/* Broken 32-bit version of LPCR must not clear top bits */
	अगर (preserve_top32)
		mask &= 0xFFFFFFFF;

	new_lpcr = kvmppc_filter_lpcr_hv(kvm,
			(vc->lpcr & ~mask) | (new_lpcr & mask));

	/*
	 * If ILE (पूर्णांकerrupt little-endian) has changed, update the
	 * MSR_LE bit in the पूर्णांकr_msr क्रम each vcpu in this vcore.
	 */
	अगर ((new_lpcr & LPCR_ILE) != (vc->lpcr & LPCR_ILE)) अणु
		काष्ठा kvm_vcpu *vcpu;
		पूर्णांक i;

		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			अगर (vcpu->arch.vcore != vc)
				जारी;
			अगर (new_lpcr & LPCR_ILE)
				vcpu->arch.पूर्णांकr_msr |= MSR_LE;
			अन्यथा
				vcpu->arch.पूर्णांकr_msr &= ~MSR_LE;
		पूर्ण
	पूर्ण

	vc->lpcr = new_lpcr;

	spin_unlock(&vc->lock);
पूर्ण

अटल पूर्णांक kvmppc_get_one_reg_hv(काष्ठा kvm_vcpu *vcpu, u64 id,
				 जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;
	दीर्घ पूर्णांक i;

	चयन (id) अणु
	हाल KVM_REG_PPC_DEBUG_INST:
		*val = get_reg_val(id, KVMPPC_INST_SW_BREAKPOINT);
		अवरोध;
	हाल KVM_REG_PPC_HIOR:
		*val = get_reg_val(id, 0);
		अवरोध;
	हाल KVM_REG_PPC_DABR:
		*val = get_reg_val(id, vcpu->arch.dabr);
		अवरोध;
	हाल KVM_REG_PPC_DABRX:
		*val = get_reg_val(id, vcpu->arch.dabrx);
		अवरोध;
	हाल KVM_REG_PPC_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr);
		अवरोध;
	हाल KVM_REG_PPC_PURR:
		*val = get_reg_val(id, vcpu->arch.purr);
		अवरोध;
	हाल KVM_REG_PPC_SPURR:
		*val = get_reg_val(id, vcpu->arch.spurr);
		अवरोध;
	हाल KVM_REG_PPC_AMR:
		*val = get_reg_val(id, vcpu->arch.amr);
		अवरोध;
	हाल KVM_REG_PPC_UAMOR:
		*val = get_reg_val(id, vcpu->arch.uamor);
		अवरोध;
	हाल KVM_REG_PPC_MMCR0 ... KVM_REG_PPC_MMCR1:
		i = id - KVM_REG_PPC_MMCR0;
		*val = get_reg_val(id, vcpu->arch.mmcr[i]);
		अवरोध;
	हाल KVM_REG_PPC_MMCR2:
		*val = get_reg_val(id, vcpu->arch.mmcr[2]);
		अवरोध;
	हाल KVM_REG_PPC_MMCRA:
		*val = get_reg_val(id, vcpu->arch.mmcra);
		अवरोध;
	हाल KVM_REG_PPC_MMCRS:
		*val = get_reg_val(id, vcpu->arch.mmcrs);
		अवरोध;
	हाल KVM_REG_PPC_MMCR3:
		*val = get_reg_val(id, vcpu->arch.mmcr[3]);
		अवरोध;
	हाल KVM_REG_PPC_PMC1 ... KVM_REG_PPC_PMC8:
		i = id - KVM_REG_PPC_PMC1;
		*val = get_reg_val(id, vcpu->arch.pmc[i]);
		अवरोध;
	हाल KVM_REG_PPC_SPMC1 ... KVM_REG_PPC_SPMC2:
		i = id - KVM_REG_PPC_SPMC1;
		*val = get_reg_val(id, vcpu->arch.spmc[i]);
		अवरोध;
	हाल KVM_REG_PPC_SIAR:
		*val = get_reg_val(id, vcpu->arch.siar);
		अवरोध;
	हाल KVM_REG_PPC_SDAR:
		*val = get_reg_val(id, vcpu->arch.sdar);
		अवरोध;
	हाल KVM_REG_PPC_SIER:
		*val = get_reg_val(id, vcpu->arch.sier[0]);
		अवरोध;
	हाल KVM_REG_PPC_SIER2:
		*val = get_reg_val(id, vcpu->arch.sier[1]);
		अवरोध;
	हाल KVM_REG_PPC_SIER3:
		*val = get_reg_val(id, vcpu->arch.sier[2]);
		अवरोध;
	हाल KVM_REG_PPC_IAMR:
		*val = get_reg_val(id, vcpu->arch.iamr);
		अवरोध;
	हाल KVM_REG_PPC_PSPB:
		*val = get_reg_val(id, vcpu->arch.pspb);
		अवरोध;
	हाल KVM_REG_PPC_DPDES:
		/*
		 * On POWER9, where we are emulating msgsndp etc.,
		 * we वापस 1 bit क्रम each vcpu, which can come from
		 * either vcore->dpdes or करोorbell_request.
		 * On POWER8, करोorbell_request is 0.
		 */
		*val = get_reg_val(id, vcpu->arch.vcore->dpdes |
				   vcpu->arch.करोorbell_request);
		अवरोध;
	हाल KVM_REG_PPC_VTB:
		*val = get_reg_val(id, vcpu->arch.vcore->vtb);
		अवरोध;
	हाल KVM_REG_PPC_DAWR:
		*val = get_reg_val(id, vcpu->arch.dawr0);
		अवरोध;
	हाल KVM_REG_PPC_DAWRX:
		*val = get_reg_val(id, vcpu->arch.dawrx0);
		अवरोध;
	हाल KVM_REG_PPC_DAWR1:
		*val = get_reg_val(id, vcpu->arch.dawr1);
		अवरोध;
	हाल KVM_REG_PPC_DAWRX1:
		*val = get_reg_val(id, vcpu->arch.dawrx1);
		अवरोध;
	हाल KVM_REG_PPC_CIABR:
		*val = get_reg_val(id, vcpu->arch.ciabr);
		अवरोध;
	हाल KVM_REG_PPC_CSIGR:
		*val = get_reg_val(id, vcpu->arch.csigr);
		अवरोध;
	हाल KVM_REG_PPC_TACR:
		*val = get_reg_val(id, vcpu->arch.tacr);
		अवरोध;
	हाल KVM_REG_PPC_TCSCR:
		*val = get_reg_val(id, vcpu->arch.tcscr);
		अवरोध;
	हाल KVM_REG_PPC_PID:
		*val = get_reg_val(id, vcpu->arch.pid);
		अवरोध;
	हाल KVM_REG_PPC_ACOP:
		*val = get_reg_val(id, vcpu->arch.acop);
		अवरोध;
	हाल KVM_REG_PPC_WORT:
		*val = get_reg_val(id, vcpu->arch.wort);
		अवरोध;
	हाल KVM_REG_PPC_TIDR:
		*val = get_reg_val(id, vcpu->arch.tid);
		अवरोध;
	हाल KVM_REG_PPC_PSSCR:
		*val = get_reg_val(id, vcpu->arch.psscr);
		अवरोध;
	हाल KVM_REG_PPC_VPA_ADDR:
		spin_lock(&vcpu->arch.vpa_update_lock);
		*val = get_reg_val(id, vcpu->arch.vpa.next_gpa);
		spin_unlock(&vcpu->arch.vpa_update_lock);
		अवरोध;
	हाल KVM_REG_PPC_VPA_SLB:
		spin_lock(&vcpu->arch.vpa_update_lock);
		val->vpaval.addr = vcpu->arch.slb_shaकरोw.next_gpa;
		val->vpaval.length = vcpu->arch.slb_shaकरोw.len;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		अवरोध;
	हाल KVM_REG_PPC_VPA_DTL:
		spin_lock(&vcpu->arch.vpa_update_lock);
		val->vpaval.addr = vcpu->arch.dtl.next_gpa;
		val->vpaval.length = vcpu->arch.dtl.len;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		अवरोध;
	हाल KVM_REG_PPC_TB_OFFSET:
		*val = get_reg_val(id, vcpu->arch.vcore->tb_offset);
		अवरोध;
	हाल KVM_REG_PPC_LPCR:
	हाल KVM_REG_PPC_LPCR_64:
		*val = get_reg_val(id, vcpu->arch.vcore->lpcr);
		अवरोध;
	हाल KVM_REG_PPC_PPR:
		*val = get_reg_val(id, vcpu->arch.ppr);
		अवरोध;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल KVM_REG_PPC_TFHAR:
		*val = get_reg_val(id, vcpu->arch.tfhar);
		अवरोध;
	हाल KVM_REG_PPC_TFIAR:
		*val = get_reg_val(id, vcpu->arch.tfiar);
		अवरोध;
	हाल KVM_REG_PPC_TEXASR:
		*val = get_reg_val(id, vcpu->arch.texasr);
		अवरोध;
	हाल KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		i = id - KVM_REG_PPC_TM_GPR0;
		*val = get_reg_val(id, vcpu->arch.gpr_पंचांग[i]);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	अणु
		पूर्णांक j;
		i = id - KVM_REG_PPC_TM_VSR0;
		अगर (i < 32)
			क्रम (j = 0; j < TS_FPRWIDTH; j++)
				val->vsxval[j] = vcpu->arch.fp_पंचांग.fpr[i][j];
		अन्यथा अणु
			अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
				val->vval = vcpu->arch.vr_पंचांग.vr[i-32];
			अन्यथा
				r = -ENXIO;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TM_CR:
		*val = get_reg_val(id, vcpu->arch.cr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_XER:
		*val = get_reg_val(id, vcpu->arch.xer_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_LR:
		*val = get_reg_val(id, vcpu->arch.lr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_CTR:
		*val = get_reg_val(id, vcpu->arch.ctr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_FPSCR:
		*val = get_reg_val(id, vcpu->arch.fp_पंचांग.fpscr);
		अवरोध;
	हाल KVM_REG_PPC_TM_AMR:
		*val = get_reg_val(id, vcpu->arch.amr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_PPR:
		*val = get_reg_val(id, vcpu->arch.ppr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_VRSAVE:
		*val = get_reg_val(id, vcpu->arch.vrsave_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSCR:
		अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
			*val = get_reg_val(id, vcpu->arch.vr_पंचांग.vscr.u[3]);
		अन्यथा
			r = -ENXIO;
		अवरोध;
	हाल KVM_REG_PPC_TM_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_TAR:
		*val = get_reg_val(id, vcpu->arch.tar_पंचांग);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_PPC_ARCH_COMPAT:
		*val = get_reg_val(id, vcpu->arch.vcore->arch_compat);
		अवरोध;
	हाल KVM_REG_PPC_DEC_EXPIRY:
		*val = get_reg_val(id, vcpu->arch.dec_expires +
				   vcpu->arch.vcore->tb_offset);
		अवरोध;
	हाल KVM_REG_PPC_ONLINE:
		*val = get_reg_val(id, vcpu->arch.online);
		अवरोध;
	हाल KVM_REG_PPC_PTCR:
		*val = get_reg_val(id, vcpu->kvm->arch.l1_ptcr);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_set_one_reg_hv(काष्ठा kvm_vcpu *vcpu, u64 id,
				 जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;
	दीर्घ पूर्णांक i;
	अचिन्हित दीर्घ addr, len;

	चयन (id) अणु
	हाल KVM_REG_PPC_HIOR:
		/* Only allow this to be set to zero */
		अगर (set_reg_val(id, *val))
			r = -EINVAL;
		अवरोध;
	हाल KVM_REG_PPC_DABR:
		vcpu->arch.dabr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_DABRX:
		vcpu->arch.dabrx = set_reg_val(id, *val) & ~DABRX_HYP;
		अवरोध;
	हाल KVM_REG_PPC_DSCR:
		vcpu->arch.dscr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_PURR:
		vcpu->arch.purr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SPURR:
		vcpu->arch.spurr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_AMR:
		vcpu->arch.amr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_UAMOR:
		vcpu->arch.uamor = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MMCR0 ... KVM_REG_PPC_MMCR1:
		i = id - KVM_REG_PPC_MMCR0;
		vcpu->arch.mmcr[i] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MMCR2:
		vcpu->arch.mmcr[2] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MMCRA:
		vcpu->arch.mmcra = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MMCRS:
		vcpu->arch.mmcrs = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MMCR3:
		*val = get_reg_val(id, vcpu->arch.mmcr[3]);
		अवरोध;
	हाल KVM_REG_PPC_PMC1 ... KVM_REG_PPC_PMC8:
		i = id - KVM_REG_PPC_PMC1;
		vcpu->arch.pmc[i] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SPMC1 ... KVM_REG_PPC_SPMC2:
		i = id - KVM_REG_PPC_SPMC1;
		vcpu->arch.spmc[i] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SIAR:
		vcpu->arch.siar = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SDAR:
		vcpu->arch.sdar = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SIER:
		vcpu->arch.sier[0] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SIER2:
		vcpu->arch.sier[1] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_SIER3:
		vcpu->arch.sier[2] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_IAMR:
		vcpu->arch.iamr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_PSPB:
		vcpu->arch.pspb = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_DPDES:
		vcpu->arch.vcore->dpdes = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_VTB:
		vcpu->arch.vcore->vtb = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_DAWR:
		vcpu->arch.dawr0 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_DAWRX:
		vcpu->arch.dawrx0 = set_reg_val(id, *val) & ~DAWRX_HYP;
		अवरोध;
	हाल KVM_REG_PPC_DAWR1:
		vcpu->arch.dawr1 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_DAWRX1:
		vcpu->arch.dawrx1 = set_reg_val(id, *val) & ~DAWRX_HYP;
		अवरोध;
	हाल KVM_REG_PPC_CIABR:
		vcpu->arch.ciabr = set_reg_val(id, *val);
		/* Don't allow setting अवरोधpoपूर्णांकs in hypervisor code */
		अगर ((vcpu->arch.ciabr & CIABR_PRIV) == CIABR_PRIV_HYPER)
			vcpu->arch.ciabr &= ~CIABR_PRIV;	/* disable */
		अवरोध;
	हाल KVM_REG_PPC_CSIGR:
		vcpu->arch.csigr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TACR:
		vcpu->arch.tacr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TCSCR:
		vcpu->arch.tcscr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_PID:
		vcpu->arch.pid = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_ACOP:
		vcpu->arch.acop = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_WORT:
		vcpu->arch.wort = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TIDR:
		vcpu->arch.tid = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_PSSCR:
		vcpu->arch.psscr = set_reg_val(id, *val) & PSSCR_GUEST_VIS;
		अवरोध;
	हाल KVM_REG_PPC_VPA_ADDR:
		addr = set_reg_val(id, *val);
		r = -EINVAL;
		अगर (!addr && (vcpu->arch.slb_shaकरोw.next_gpa ||
			      vcpu->arch.dtl.next_gpa))
			अवरोध;
		r = set_vpa(vcpu, &vcpu->arch.vpa, addr, माप(काष्ठा lppaca));
		अवरोध;
	हाल KVM_REG_PPC_VPA_SLB:
		addr = val->vpaval.addr;
		len = val->vpaval.length;
		r = -EINVAL;
		अगर (addr && !vcpu->arch.vpa.next_gpa)
			अवरोध;
		r = set_vpa(vcpu, &vcpu->arch.slb_shaकरोw, addr, len);
		अवरोध;
	हाल KVM_REG_PPC_VPA_DTL:
		addr = val->vpaval.addr;
		len = val->vpaval.length;
		r = -EINVAL;
		अगर (addr && (len < माप(काष्ठा dtl_entry) ||
			     !vcpu->arch.vpa.next_gpa))
			अवरोध;
		len -= len % माप(काष्ठा dtl_entry);
		r = set_vpa(vcpu, &vcpu->arch.dtl, addr, len);
		अवरोध;
	हाल KVM_REG_PPC_TB_OFFSET:
		/* round up to multiple of 2^24 */
		vcpu->arch.vcore->tb_offset =
			ALIGN(set_reg_val(id, *val), 1UL << 24);
		अवरोध;
	हाल KVM_REG_PPC_LPCR:
		kvmppc_set_lpcr(vcpu, set_reg_val(id, *val), true);
		अवरोध;
	हाल KVM_REG_PPC_LPCR_64:
		kvmppc_set_lpcr(vcpu, set_reg_val(id, *val), false);
		अवरोध;
	हाल KVM_REG_PPC_PPR:
		vcpu->arch.ppr = set_reg_val(id, *val);
		अवरोध;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल KVM_REG_PPC_TFHAR:
		vcpu->arch.tfhar = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TFIAR:
		vcpu->arch.tfiar = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TEXASR:
		vcpu->arch.texasr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		i = id - KVM_REG_PPC_TM_GPR0;
		vcpu->arch.gpr_पंचांग[i] = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	अणु
		पूर्णांक j;
		i = id - KVM_REG_PPC_TM_VSR0;
		अगर (i < 32)
			क्रम (j = 0; j < TS_FPRWIDTH; j++)
				vcpu->arch.fp_पंचांग.fpr[i][j] = val->vsxval[j];
		अन्यथा
			अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
				vcpu->arch.vr_पंचांग.vr[i-32] = val->vval;
			अन्यथा
				r = -ENXIO;
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TM_CR:
		vcpu->arch.cr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_XER:
		vcpu->arch.xer_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_LR:
		vcpu->arch.lr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_CTR:
		vcpu->arch.ctr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_FPSCR:
		vcpu->arch.fp_पंचांग.fpscr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_AMR:
		vcpu->arch.amr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_PPR:
		vcpu->arch.ppr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_VRSAVE:
		vcpu->arch.vrsave_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSCR:
		अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
			vcpu->arch.vr.vscr.u[3] = set_reg_val(id, *val);
		अन्यथा
			r = - ENXIO;
		अवरोध;
	हाल KVM_REG_PPC_TM_DSCR:
		vcpu->arch.dscr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_TAR:
		vcpu->arch.tar_पंचांग = set_reg_val(id, *val);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_PPC_ARCH_COMPAT:
		r = kvmppc_set_arch_compat(vcpu, set_reg_val(id, *val));
		अवरोध;
	हाल KVM_REG_PPC_DEC_EXPIRY:
		vcpu->arch.dec_expires = set_reg_val(id, *val) -
			vcpu->arch.vcore->tb_offset;
		अवरोध;
	हाल KVM_REG_PPC_ONLINE:
		i = set_reg_val(id, *val);
		अगर (i && !vcpu->arch.online)
			atomic_inc(&vcpu->arch.vcore->online_count);
		अन्यथा अगर (!i && vcpu->arch.online)
			atomic_dec(&vcpu->arch.vcore->online_count);
		vcpu->arch.online = i;
		अवरोध;
	हाल KVM_REG_PPC_PTCR:
		vcpu->kvm->arch.l1_ptcr = set_reg_val(id, *val);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

/*
 * On POWER9, thपढ़ोs are independent and can be in dअगरferent partitions.
 * Thereक्रमe we consider each thपढ़ो to be a subcore.
 * There is a restriction that all thपढ़ोs have to be in the same
 * MMU mode (radix or HPT), unक्रमtunately, but since we only support
 * HPT guests on a HPT host so far, that isn't an impediment yet.
 */
अटल पूर्णांक thपढ़ोs_per_vcore(काष्ठा kvm *kvm)
अणु
	अगर (kvm->arch.thपढ़ोs_indep)
		वापस 1;
	वापस thपढ़ोs_per_subcore;
पूर्ण

अटल काष्ठा kvmppc_vcore *kvmppc_vcore_create(काष्ठा kvm *kvm, पूर्णांक id)
अणु
	काष्ठा kvmppc_vcore *vcore;

	vcore = kzalloc(माप(काष्ठा kvmppc_vcore), GFP_KERNEL);

	अगर (vcore == शून्य)
		वापस शून्य;

	spin_lock_init(&vcore->lock);
	spin_lock_init(&vcore->stoltb_lock);
	rcuरुको_init(&vcore->रुको);
	vcore->preempt_tb = TB_NIL;
	vcore->lpcr = kvm->arch.lpcr;
	vcore->first_vcpuid = id;
	vcore->kvm = kvm;
	INIT_LIST_HEAD(&vcore->preempt_list);

	वापस vcore;
पूर्ण

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_EXIT_TIMING
अटल काष्ठा debugfs_timings_element अणु
	स्थिर अक्षर *name;
	माप_प्रकार offset;
पूर्ण timings[] = अणु
	अणु"rm_entry",	दुरत्व(काष्ठा kvm_vcpu, arch.rm_entry)पूर्ण,
	अणु"rm_intr",	दुरत्व(काष्ठा kvm_vcpu, arch.rm_पूर्णांकr)पूर्ण,
	अणु"rm_exit",	दुरत्व(काष्ठा kvm_vcpu, arch.rm_निकास)पूर्ण,
	अणु"guest",	दुरत्व(काष्ठा kvm_vcpu, arch.guest_समय)पूर्ण,
	अणु"cede",	दुरत्व(काष्ठा kvm_vcpu, arch.cede_समय)पूर्ण,
पूर्ण;

#घोषणा N_TIMINGS	(ARRAY_SIZE(timings))

काष्ठा debugfs_timings_state अणु
	काष्ठा kvm_vcpu	*vcpu;
	अचिन्हित पूर्णांक	buflen;
	अक्षर		buf[N_TIMINGS * 100];
पूर्ण;

अटल पूर्णांक debugfs_timings_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा kvm_vcpu *vcpu = inode->i_निजी;
	काष्ठा debugfs_timings_state *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	kvm_get_kvm(vcpu->kvm);
	p->vcpu = vcpu;
	file->निजी_data = p;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक debugfs_timings_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debugfs_timings_state *p = file->निजी_data;

	kvm_put_kvm(p->vcpu->kvm);
	kमुक्त(p);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_timings_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				    माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा debugfs_timings_state *p = file->निजी_data;
	काष्ठा kvm_vcpu *vcpu = p->vcpu;
	अक्षर *s, *buf_end;
	काष्ठा kvmhv_tb_accumulator tb;
	u64 count;
	loff_t pos;
	sमाप_प्रकार n;
	पूर्णांक i, loops;
	bool ok;

	अगर (!p->buflen) अणु
		s = p->buf;
		buf_end = s + माप(p->buf);
		क्रम (i = 0; i < N_TIMINGS; ++i) अणु
			काष्ठा kvmhv_tb_accumulator *acc;

			acc = (काष्ठा kvmhv_tb_accumulator *)
				((अचिन्हित दीर्घ)vcpu + timings[i].offset);
			ok = false;
			क्रम (loops = 0; loops < 1000; ++loops) अणु
				count = acc->seqcount;
				अगर (!(count & 1)) अणु
					smp_rmb();
					tb = *acc;
					smp_rmb();
					अगर (count == acc->seqcount) अणु
						ok = true;
						अवरोध;
					पूर्ण
				पूर्ण
				udelay(1);
			पूर्ण
			अगर (!ok)
				snम_लिखो(s, buf_end - s, "%s: stuck\n",
					timings[i].name);
			अन्यथा
				snम_लिखो(s, buf_end - s,
					"%s: %llu %llu %llu %llu\n",
					timings[i].name, count / 2,
					tb_to_ns(tb.tb_total),
					tb_to_ns(tb.tb_min),
					tb_to_ns(tb.tb_max));
			s += म_माप(s);
		पूर्ण
		p->buflen = s - p->buf;
	पूर्ण

	pos = *ppos;
	अगर (pos >= p->buflen)
		वापस 0;
	अगर (len > p->buflen - pos)
		len = p->buflen - pos;
	n = copy_to_user(buf, p->buf + pos, len);
	अगर (n) अणु
		अगर (n == len)
			वापस -EFAULT;
		len -= n;
	पूर्ण
	*ppos = pos + len;
	वापस len;
पूर्ण

अटल sमाप_प्रकार debugfs_timings_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				     माप_प्रकार len, loff_t *ppos)
अणु
	वापस -EACCES;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_timings_ops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = debugfs_timings_खोलो,
	.release = debugfs_timings_release,
	.पढ़ो	 = debugfs_timings_पढ़ो,
	.ग_लिखो	 = debugfs_timings_ग_लिखो,
	.llseek	 = generic_file_llseek,
पूर्ण;

/* Create a debugfs directory क्रम the vcpu */
अटल व्योम debugfs_vcpu_init(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक id)
अणु
	अक्षर buf[16];
	काष्ठा kvm *kvm = vcpu->kvm;

	snम_लिखो(buf, माप(buf), "vcpu%u", id);
	vcpu->arch.debugfs_dir = debugfs_create_dir(buf, kvm->arch.debugfs_dir);
	debugfs_create_file("timings", 0444, vcpu->arch.debugfs_dir, vcpu,
			    &debugfs_timings_ops);
पूर्ण

#अन्यथा /* CONFIG_KVM_BOOK3S_HV_EXIT_TIMING */
अटल व्योम debugfs_vcpu_init(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक id)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_EXIT_TIMING */

अटल पूर्णांक kvmppc_core_vcpu_create_hv(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक err;
	पूर्णांक core;
	काष्ठा kvmppc_vcore *vcore;
	काष्ठा kvm *kvm;
	अचिन्हित पूर्णांक id;

	kvm = vcpu->kvm;
	id = vcpu->vcpu_id;

	vcpu->arch.shared = &vcpu->arch.shregs;
#अगर_घोषित CONFIG_KVM_BOOK3S_PR_POSSIBLE
	/*
	 * The shared काष्ठा is never shared on HV,
	 * so we can always use host endianness
	 */
#अगर_घोषित __BIG_ENDIAN__
	vcpu->arch.shared_big_endian = true;
#अन्यथा
	vcpu->arch.shared_big_endian = false;
#पूर्ण_अगर
#पूर्ण_अगर
	vcpu->arch.mmcr[0] = MMCR0_FC;
	vcpu->arch.ctrl = CTRL_RUNLATCH;
	/* शेष to host PVR, since we can't spoof it */
	kvmppc_set_pvr_hv(vcpu, mfspr(SPRN_PVR));
	spin_lock_init(&vcpu->arch.vpa_update_lock);
	spin_lock_init(&vcpu->arch.tbacct_lock);
	vcpu->arch.busy_preempt = TB_NIL;
	vcpu->arch.पूर्णांकr_msr = MSR_SF | MSR_ME;

	/*
	 * Set the शेष HFSCR क्रम the guest from the host value.
	 * This value is only used on POWER9.
	 * On POWER9, we want to भवize the करोorbell facility, so we
	 * करोn't set the HFSCR_MSGP bit, and that causes those inकाष्ठाions
	 * to trap and then we emulate them.
	 */
	vcpu->arch.hfscr = HFSCR_TAR | HFSCR_EBB | HFSCR_PM | HFSCR_BHRB |
		HFSCR_DSCR | HFSCR_VECVSX | HFSCR_FP | HFSCR_PREFIX;
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		vcpu->arch.hfscr &= mfspr(SPRN_HFSCR);
		अगर (cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST))
			vcpu->arch.hfscr |= HFSCR_TM;
	पूर्ण
	अगर (cpu_has_feature(CPU_FTR_TM_COMP))
		vcpu->arch.hfscr |= HFSCR_TM;

	kvmppc_mmu_book3s_hv_init(vcpu);

	vcpu->arch.state = KVMPPC_VCPU_NOTREADY;

	init_रुकोqueue_head(&vcpu->arch.cpu_run);

	mutex_lock(&kvm->lock);
	vcore = शून्य;
	err = -EINVAL;
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (id >= (KVM_MAX_VCPUS * kvm->arch.emul_smt_mode)) अणु
			pr_devel("KVM: VCPU ID too high\n");
			core = KVM_MAX_VCORES;
		पूर्ण अन्यथा अणु
			BUG_ON(kvm->arch.smt_mode != 1);
			core = kvmppc_pack_vcpu_id(kvm, id);
		पूर्ण
	पूर्ण अन्यथा अणु
		core = id / kvm->arch.smt_mode;
	पूर्ण
	अगर (core < KVM_MAX_VCORES) अणु
		vcore = kvm->arch.vcores[core];
		अगर (vcore && cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			pr_devel("KVM: collision on id %u", id);
			vcore = शून्य;
		पूर्ण अन्यथा अगर (!vcore) अणु
			/*
			 * Take mmu_setup_lock क्रम mutual exclusion
			 * with kvmppc_update_lpcr().
			 */
			err = -ENOMEM;
			vcore = kvmppc_vcore_create(kvm,
					id & ~(kvm->arch.smt_mode - 1));
			mutex_lock(&kvm->arch.mmu_setup_lock);
			kvm->arch.vcores[core] = vcore;
			kvm->arch.online_vcores++;
			mutex_unlock(&kvm->arch.mmu_setup_lock);
		पूर्ण
	पूर्ण
	mutex_unlock(&kvm->lock);

	अगर (!vcore)
		वापस err;

	spin_lock(&vcore->lock);
	++vcore->num_thपढ़ोs;
	spin_unlock(&vcore->lock);
	vcpu->arch.vcore = vcore;
	vcpu->arch.ptid = vcpu->vcpu_id - vcore->first_vcpuid;
	vcpu->arch.thपढ़ो_cpu = -1;
	vcpu->arch.prev_cpu = -1;

	vcpu->arch.cpu_type = KVM_CPU_3S_64;
	kvmppc_sanity_check(vcpu);

	debugfs_vcpu_init(vcpu, id);

	वापस 0;
पूर्ण

अटल पूर्णांक kvmhv_set_smt_mode(काष्ठा kvm *kvm, अचिन्हित दीर्घ smt_mode,
			      अचिन्हित दीर्घ flags)
अणु
	पूर्णांक err;
	पूर्णांक esmt = 0;

	अगर (flags)
		वापस -EINVAL;
	अगर (smt_mode > MAX_SMT_THREADS || !is_घातer_of_2(smt_mode))
		वापस -EINVAL;
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		/*
		 * On POWER8 (or POWER7), the thपढ़ोing mode is "strict",
		 * so we pack smt_mode vcpus per vcore.
		 */
		अगर (smt_mode > thपढ़ोs_per_subcore)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/*
		 * On POWER9, the thपढ़ोing mode is "loose",
		 * so each vcpu माला_लो its own vcore.
		 */
		esmt = smt_mode;
		smt_mode = 1;
	पूर्ण
	mutex_lock(&kvm->lock);
	err = -EBUSY;
	अगर (!kvm->arch.online_vcores) अणु
		kvm->arch.smt_mode = smt_mode;
		kvm->arch.emul_smt_mode = esmt;
		err = 0;
	पूर्ण
	mutex_unlock(&kvm->lock);

	वापस err;
पूर्ण

अटल व्योम unpin_vpa(काष्ठा kvm *kvm, काष्ठा kvmppc_vpa *vpa)
अणु
	अगर (vpa->pinned_addr)
		kvmppc_unpin_guest_page(kvm, vpa->pinned_addr, vpa->gpa,
					vpa->dirty);
पूर्ण

अटल व्योम kvmppc_core_vcpu_मुक्त_hv(काष्ठा kvm_vcpu *vcpu)
अणु
	spin_lock(&vcpu->arch.vpa_update_lock);
	unpin_vpa(vcpu->kvm, &vcpu->arch.dtl);
	unpin_vpa(vcpu->kvm, &vcpu->arch.slb_shaकरोw);
	unpin_vpa(vcpu->kvm, &vcpu->arch.vpa);
	spin_unlock(&vcpu->arch.vpa_update_lock);
पूर्ण

अटल पूर्णांक kvmppc_core_check_requests_hv(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Indicate we want to get back पूर्णांकo the guest */
	वापस 1;
पूर्ण

अटल व्योम kvmppc_set_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ dec_nsec, now;

	now = get_tb();
	अगर (now > vcpu->arch.dec_expires) अणु
		/* decrementer has alपढ़ोy gone negative */
		kvmppc_core_queue_dec(vcpu);
		kvmppc_core_prepare_to_enter(vcpu);
		वापस;
	पूर्ण
	dec_nsec = tb_to_ns(vcpu->arch.dec_expires - now);
	hrसमयr_start(&vcpu->arch.dec_समयr, dec_nsec, HRTIMER_MODE_REL);
	vcpu->arch.समयr_running = 1;
पूर्ण

बाह्य पूर्णांक __kvmppc_vcore_entry(व्योम);

अटल व्योम kvmppc_हटाओ_runnable(काष्ठा kvmppc_vcore *vc,
				   काष्ठा kvm_vcpu *vcpu)
अणु
	u64 now;

	अगर (vcpu->arch.state != KVMPPC_VCPU_RUNNABLE)
		वापस;
	spin_lock_irq(&vcpu->arch.tbacct_lock);
	now = mftb();
	vcpu->arch.busy_stolen += vcore_stolen_समय(vc, now) -
		vcpu->arch.stolen_logged;
	vcpu->arch.busy_preempt = now;
	vcpu->arch.state = KVMPPC_VCPU_BUSY_IN_HOST;
	spin_unlock_irq(&vcpu->arch.tbacct_lock);
	--vc->n_runnable;
	WRITE_ONCE(vc->runnable_thपढ़ोs[vcpu->arch.ptid], शून्य);
पूर्ण

अटल पूर्णांक kvmppc_grab_hwthपढ़ो(पूर्णांक cpu)
अणु
	काष्ठा paca_काष्ठा *tpaca;
	दीर्घ समयout = 10000;

	tpaca = paca_ptrs[cpu];

	/* Ensure the thपढ़ो won't go पूर्णांकo the kernel अगर it wakes */
	tpaca->kvm_hstate.kvm_vcpu = शून्य;
	tpaca->kvm_hstate.kvm_vcore = शून्य;
	tpaca->kvm_hstate.napping = 0;
	smp_wmb();
	tpaca->kvm_hstate.hwthपढ़ो_req = 1;

	/*
	 * If the thपढ़ो is alपढ़ोy executing in the kernel (e.g. handling
	 * a stray पूर्णांकerrupt), रुको क्रम it to get back to nap mode.
	 * The smp_mb() is to ensure that our setting of hwthपढ़ो_req
	 * is visible beक्रमe we look at hwthपढ़ो_state, so अगर this
	 * races with the code at प्रणाली_reset_pSeries and the thपढ़ो
	 * misses our setting of hwthपढ़ो_req, we are sure to see its
	 * setting of hwthपढ़ो_state, and vice versa.
	 */
	smp_mb();
	जबतक (tpaca->kvm_hstate.hwthपढ़ो_state == KVM_HWTHREAD_IN_KERNEL) अणु
		अगर (--समयout <= 0) अणु
			pr_err("KVM: couldn't grab cpu %d\n", cpu);
			वापस -EBUSY;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम kvmppc_release_hwthपढ़ो(पूर्णांक cpu)
अणु
	काष्ठा paca_काष्ठा *tpaca;

	tpaca = paca_ptrs[cpu];
	tpaca->kvm_hstate.hwthपढ़ो_req = 0;
	tpaca->kvm_hstate.kvm_vcpu = शून्य;
	tpaca->kvm_hstate.kvm_vcore = शून्य;
	tpaca->kvm_hstate.kvm_split_mode = शून्य;
पूर्ण

अटल व्योम radix_flush_cpu(काष्ठा kvm *kvm, पूर्णांक cpu, काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_nested_guest *nested = vcpu->arch.nested;
	cpumask_t *cpu_in_guest;
	पूर्णांक i;

	cpu = cpu_first_thपढ़ो_sibling(cpu);
	अगर (nested) अणु
		cpumask_set_cpu(cpu, &nested->need_tlb_flush);
		cpu_in_guest = &nested->cpu_in_guest;
	पूर्ण अन्यथा अणु
		cpumask_set_cpu(cpu, &kvm->arch.need_tlb_flush);
		cpu_in_guest = &kvm->arch.cpu_in_guest;
	पूर्ण
	/*
	 * Make sure setting of bit in need_tlb_flush precedes
	 * testing of cpu_in_guest bits.  The matching barrier on
	 * the other side is the first smp_mb() in kvmppc_run_core().
	 */
	smp_mb();
	क्रम (i = 0; i < thपढ़ोs_per_core; ++i)
		अगर (cpumask_test_cpu(cpu + i, cpu_in_guest))
			smp_call_function_single(cpu + i, करो_nothing, शून्य, 1);
पूर्ण

अटल व्योम kvmppc_prepare_radix_vcpu(काष्ठा kvm_vcpu *vcpu, पूर्णांक pcpu)
अणु
	काष्ठा kvm_nested_guest *nested = vcpu->arch.nested;
	काष्ठा kvm *kvm = vcpu->kvm;
	पूर्णांक prev_cpu;

	अगर (!cpu_has_feature(CPU_FTR_HVMODE))
		वापस;

	अगर (nested)
		prev_cpu = nested->prev_cpu[vcpu->arch.nested_vcpu_id];
	अन्यथा
		prev_cpu = vcpu->arch.prev_cpu;

	/*
	 * With radix, the guest can करो TLB invalidations itself,
	 * and it could choose to use the local क्रमm (tlbiel) अगर
	 * it is invalidating a translation that has only ever been
	 * used on one vcpu.  However, that करोesn't mean it has
	 * only ever been used on one physical cpu, since vcpus
	 * can move around between pcpus.  To cope with this, when
	 * a vcpu moves from one pcpu to another, we need to tell
	 * any vcpus running on the same core as this vcpu previously
	 * ran to flush the TLB.  The TLB is shared between thपढ़ोs,
	 * so we use a single bit in .need_tlb_flush क्रम all 4 thपढ़ोs.
	 */
	अगर (prev_cpu != pcpu) अणु
		अगर (prev_cpu >= 0 &&
		    cpu_first_thपढ़ो_sibling(prev_cpu) !=
		    cpu_first_thपढ़ो_sibling(pcpu))
			radix_flush_cpu(kvm, prev_cpu, vcpu);
		अगर (nested)
			nested->prev_cpu[vcpu->arch.nested_vcpu_id] = pcpu;
		अन्यथा
			vcpu->arch.prev_cpu = pcpu;
	पूर्ण
पूर्ण

अटल व्योम kvmppc_start_thपढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_vcore *vc)
अणु
	पूर्णांक cpu;
	काष्ठा paca_काष्ठा *tpaca;
	काष्ठा kvm *kvm = vc->kvm;

	cpu = vc->pcpu;
	अगर (vcpu) अणु
		अगर (vcpu->arch.समयr_running) अणु
			hrसमयr_try_to_cancel(&vcpu->arch.dec_समयr);
			vcpu->arch.समयr_running = 0;
		पूर्ण
		cpu += vcpu->arch.ptid;
		vcpu->cpu = vc->pcpu;
		vcpu->arch.thपढ़ो_cpu = cpu;
		cpumask_set_cpu(cpu, &kvm->arch.cpu_in_guest);
	पूर्ण
	tpaca = paca_ptrs[cpu];
	tpaca->kvm_hstate.kvm_vcpu = vcpu;
	tpaca->kvm_hstate.ptid = cpu - vc->pcpu;
	tpaca->kvm_hstate.fake_suspend = 0;
	/* Order stores to hstate.kvm_vcpu etc. beक्रमe store to kvm_vcore */
	smp_wmb();
	tpaca->kvm_hstate.kvm_vcore = vc;
	अगर (cpu != smp_processor_id())
		kvmppc_ipi_thपढ़ो(cpu);
पूर्ण

अटल व्योम kvmppc_रुको_क्रम_nap(पूर्णांक n_thपढ़ोs)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक i, loops;

	अगर (n_thपढ़ोs <= 1)
		वापस;
	क्रम (loops = 0; loops < 1000000; ++loops) अणु
		/*
		 * Check अगर all thपढ़ोs are finished.
		 * We set the vcore poपूर्णांकer when starting a thपढ़ो
		 * and the thपढ़ो clears it when finished, so we look
		 * क्रम any thपढ़ोs that still have a non-शून्य vcore ptr.
		 */
		क्रम (i = 1; i < n_thपढ़ोs; ++i)
			अगर (paca_ptrs[cpu + i]->kvm_hstate.kvm_vcore)
				अवरोध;
		अगर (i == n_thपढ़ोs) अणु
			HMT_medium();
			वापस;
		पूर्ण
		HMT_low();
	पूर्ण
	HMT_medium();
	क्रम (i = 1; i < n_thपढ़ोs; ++i)
		अगर (paca_ptrs[cpu + i]->kvm_hstate.kvm_vcore)
			pr_err("KVM: CPU %d seems to be stuck\n", cpu + i);
पूर्ण

/*
 * Check that we are on thपढ़ो 0 and that any other thपढ़ोs in
 * this core are off-line.  Then grab the thपढ़ोs so they can't
 * enter the kernel.
 */
अटल पूर्णांक on_primary_thपढ़ो(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक thr;

	/* Are we on a primary subcore? */
	अगर (cpu_thपढ़ो_in_subcore(cpu))
		वापस 0;

	thr = 0;
	जबतक (++thr < thपढ़ोs_per_subcore)
		अगर (cpu_online(cpu + thr))
			वापस 0;

	/* Grab all hw thपढ़ोs so they can't go पूर्णांकo the kernel */
	क्रम (thr = 1; thr < thपढ़ोs_per_subcore; ++thr) अणु
		अगर (kvmppc_grab_hwthपढ़ो(cpu + thr)) अणु
			/* Couldn't grab one; let the others go */
			करो अणु
				kvmppc_release_hwthपढ़ो(cpu + thr);
			पूर्ण जबतक (--thr > 0);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * A list of भव cores क्रम each physical CPU.
 * These are vcores that could run but their runner VCPU tasks are
 * (or may be) preempted.
 */
काष्ठा preempted_vcore_list अणु
	काष्ठा list_head	list;
	spinlock_t		lock;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा preempted_vcore_list, preempted_vcores);

अटल व्योम init_vcore_lists(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा preempted_vcore_list *lp = &per_cpu(preempted_vcores, cpu);
		spin_lock_init(&lp->lock);
		INIT_LIST_HEAD(&lp->list);
	पूर्ण
पूर्ण

अटल व्योम kvmppc_vcore_preempt(काष्ठा kvmppc_vcore *vc)
अणु
	काष्ठा preempted_vcore_list *lp = this_cpu_ptr(&preempted_vcores);

	vc->vcore_state = VCORE_PREEMPT;
	vc->pcpu = smp_processor_id();
	अगर (vc->num_thपढ़ोs < thपढ़ोs_per_vcore(vc->kvm)) अणु
		spin_lock(&lp->lock);
		list_add_tail(&vc->preempt_list, &lp->list);
		spin_unlock(&lp->lock);
	पूर्ण

	/* Start accumulating stolen समय */
	kvmppc_core_start_stolen(vc);
पूर्ण

अटल व्योम kvmppc_vcore_end_preempt(काष्ठा kvmppc_vcore *vc)
अणु
	काष्ठा preempted_vcore_list *lp;

	kvmppc_core_end_stolen(vc);
	अगर (!list_empty(&vc->preempt_list)) अणु
		lp = &per_cpu(preempted_vcores, vc->pcpu);
		spin_lock(&lp->lock);
		list_del_init(&vc->preempt_list);
		spin_unlock(&lp->lock);
	पूर्ण
	vc->vcore_state = VCORE_INACTIVE;
पूर्ण

/*
 * This stores inक्रमmation about the भव cores currently
 * asचिन्हित to a physical core.
 */
काष्ठा core_info अणु
	पूर्णांक		n_subcores;
	पूर्णांक		max_subcore_thपढ़ोs;
	पूर्णांक		total_thपढ़ोs;
	पूर्णांक		subcore_thपढ़ोs[MAX_SUBCORES];
	काष्ठा kvmppc_vcore *vc[MAX_SUBCORES];
पूर्ण;

/*
 * This mapping means subcores 0 and 1 can use thपढ़ोs 0-3 and 4-7
 * respectively in 2-way micro-thपढ़ोing (split-core) mode on POWER8.
 */
अटल पूर्णांक subcore_thपढ़ो_map[MAX_SUBCORES] = अणु 0, 4, 2, 6 पूर्ण;

अटल व्योम init_core_info(काष्ठा core_info *cip, काष्ठा kvmppc_vcore *vc)
अणु
	स_रखो(cip, 0, माप(*cip));
	cip->n_subcores = 1;
	cip->max_subcore_thपढ़ोs = vc->num_thपढ़ोs;
	cip->total_thपढ़ोs = vc->num_thपढ़ोs;
	cip->subcore_thपढ़ोs[0] = vc->num_thपढ़ोs;
	cip->vc[0] = vc;
पूर्ण

अटल bool subcore_config_ok(पूर्णांक n_subcores, पूर्णांक n_thपढ़ोs)
अणु
	/*
	 * POWER9 "SMT4" cores are permanently in what is effectively a 4-way
	 * split-core mode, with one thपढ़ो per subcore.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		वापस n_subcores <= 4 && n_thपढ़ोs == 1;

	/* On POWER8, can only dynamically split अगर unsplit to begin with */
	अगर (n_subcores > 1 && thपढ़ोs_per_subcore < MAX_SMT_THREADS)
		वापस false;
	अगर (n_subcores > MAX_SUBCORES)
		वापस false;
	अगर (n_subcores > 1) अणु
		अगर (!(dynamic_mt_modes & 2))
			n_subcores = 4;
		अगर (n_subcores > 2 && !(dynamic_mt_modes & 4))
			वापस false;
	पूर्ण

	वापस n_subcores * roundup_घात_of_two(n_thपढ़ोs) <= MAX_SMT_THREADS;
पूर्ण

अटल व्योम init_vcore_to_run(काष्ठा kvmppc_vcore *vc)
अणु
	vc->entry_निकास_map = 0;
	vc->in_guest = 0;
	vc->napping_thपढ़ोs = 0;
	vc->conferring_thपढ़ोs = 0;
	vc->tb_offset_applied = 0;
पूर्ण

अटल bool can_dynamic_split(काष्ठा kvmppc_vcore *vc, काष्ठा core_info *cip)
अणु
	पूर्णांक n_thपढ़ोs = vc->num_thपढ़ोs;
	पूर्णांक sub;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस false;

	/* In one_vm_per_core mode, require all vcores to be from the same vm */
	अगर (one_vm_per_core && vc->kvm != cip->vc[0]->kvm)
		वापस false;

	अगर (n_thपढ़ोs < cip->max_subcore_thपढ़ोs)
		n_thपढ़ोs = cip->max_subcore_thपढ़ोs;
	अगर (!subcore_config_ok(cip->n_subcores + 1, n_thपढ़ोs))
		वापस false;
	cip->max_subcore_thपढ़ोs = n_thपढ़ोs;

	sub = cip->n_subcores;
	++cip->n_subcores;
	cip->total_thपढ़ोs += vc->num_thपढ़ोs;
	cip->subcore_thपढ़ोs[sub] = vc->num_thपढ़ोs;
	cip->vc[sub] = vc;
	init_vcore_to_run(vc);
	list_del_init(&vc->preempt_list);

	वापस true;
पूर्ण

/*
 * Work out whether it is possible to piggyback the execution of
 * vcore *pvc onto the execution of the other vcores described in *cip.
 */
अटल bool can_piggyback(काष्ठा kvmppc_vcore *pvc, काष्ठा core_info *cip,
			  पूर्णांक target_thपढ़ोs)
अणु
	अगर (cip->total_thपढ़ोs + pvc->num_thपढ़ोs > target_thपढ़ोs)
		वापस false;

	वापस can_dynamic_split(pvc, cip);
पूर्ण

अटल व्योम prepare_thपढ़ोs(काष्ठा kvmppc_vcore *vc)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	क्रम_each_runnable_thपढ़ो(i, vcpu, vc) अणु
		अगर (संकेत_pending(vcpu->arch.run_task))
			vcpu->arch.ret = -EINTR;
		अन्यथा अगर (no_mixing_hpt_and_radix &&
			 kvm_is_radix(vc->kvm) != radix_enabled())
			vcpu->arch.ret = -EINVAL;
		अन्यथा अगर (vcpu->arch.vpa.update_pending ||
			 vcpu->arch.slb_shaकरोw.update_pending ||
			 vcpu->arch.dtl.update_pending)
			vcpu->arch.ret = RESUME_GUEST;
		अन्यथा
			जारी;
		kvmppc_हटाओ_runnable(vc, vcpu);
		wake_up(&vcpu->arch.cpu_run);
	पूर्ण
पूर्ण

अटल व्योम collect_piggybacks(काष्ठा core_info *cip, पूर्णांक target_thपढ़ोs)
अणु
	काष्ठा preempted_vcore_list *lp = this_cpu_ptr(&preempted_vcores);
	काष्ठा kvmppc_vcore *pvc, *vcnext;

	spin_lock(&lp->lock);
	list_क्रम_each_entry_safe(pvc, vcnext, &lp->list, preempt_list) अणु
		अगर (!spin_trylock(&pvc->lock))
			जारी;
		prepare_thपढ़ोs(pvc);
		अगर (!pvc->n_runnable || !pvc->kvm->arch.mmu_पढ़ोy) अणु
			list_del_init(&pvc->preempt_list);
			अगर (pvc->runner == शून्य) अणु
				pvc->vcore_state = VCORE_INACTIVE;
				kvmppc_core_end_stolen(pvc);
			पूर्ण
			spin_unlock(&pvc->lock);
			जारी;
		पूर्ण
		अगर (!can_piggyback(pvc, cip, target_thपढ़ोs)) अणु
			spin_unlock(&pvc->lock);
			जारी;
		पूर्ण
		kvmppc_core_end_stolen(pvc);
		pvc->vcore_state = VCORE_PIGGYBACK;
		अगर (cip->total_thपढ़ोs >= target_thपढ़ोs)
			अवरोध;
	पूर्ण
	spin_unlock(&lp->lock);
पूर्ण

अटल bool recheck_संकेतs_and_mmu(काष्ठा core_info *cip)
अणु
	पूर्णांक sub, i;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvmppc_vcore *vc;

	क्रम (sub = 0; sub < cip->n_subcores; ++sub) अणु
		vc = cip->vc[sub];
		अगर (!vc->kvm->arch.mmu_पढ़ोy)
			वापस true;
		क्रम_each_runnable_thपढ़ो(i, vcpu, vc)
			अगर (संकेत_pending(vcpu->arch.run_task))
				वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम post_guest_process(काष्ठा kvmppc_vcore *vc, bool is_master)
अणु
	पूर्णांक still_running = 0, i;
	u64 now;
	दीर्घ ret;
	काष्ठा kvm_vcpu *vcpu;

	spin_lock(&vc->lock);
	now = get_tb();
	क्रम_each_runnable_thपढ़ो(i, vcpu, vc) अणु
		/*
		 * It's safe to unlock the vcore in the loop here, because
		 * क्रम_each_runnable_thपढ़ो() is safe against removal of
		 * the vcpu, and the vcore state is VCORE_EXITING here,
		 * so any vcpus becoming runnable will have their arch.trap
		 * set to zero and can't actually run in the guest.
		 */
		spin_unlock(&vc->lock);
		/* cancel pending dec exception अगर dec is positive */
		अगर (now < vcpu->arch.dec_expires &&
		    kvmppc_core_pending_dec(vcpu))
			kvmppc_core_dequeue_dec(vcpu);

		trace_kvm_guest_निकास(vcpu);

		ret = RESUME_GUEST;
		अगर (vcpu->arch.trap)
			ret = kvmppc_handle_निकास_hv(vcpu,
						    vcpu->arch.run_task);

		vcpu->arch.ret = ret;
		vcpu->arch.trap = 0;

		spin_lock(&vc->lock);
		अगर (is_kvmppc_resume_guest(vcpu->arch.ret)) अणु
			अगर (vcpu->arch.pending_exceptions)
				kvmppc_core_prepare_to_enter(vcpu);
			अगर (vcpu->arch.ceded)
				kvmppc_set_समयr(vcpu);
			अन्यथा
				++still_running;
		पूर्ण अन्यथा अणु
			kvmppc_हटाओ_runnable(vc, vcpu);
			wake_up(&vcpu->arch.cpu_run);
		पूर्ण
	पूर्ण
	अगर (!is_master) अणु
		अगर (still_running > 0) अणु
			kvmppc_vcore_preempt(vc);
		पूर्ण अन्यथा अगर (vc->runner) अणु
			vc->vcore_state = VCORE_PREEMPT;
			kvmppc_core_start_stolen(vc);
		पूर्ण अन्यथा अणु
			vc->vcore_state = VCORE_INACTIVE;
		पूर्ण
		अगर (vc->n_runnable > 0 && vc->runner == शून्य) अणु
			/* make sure there's a candidate runner awake */
			i = -1;
			vcpu = next_runnable_thपढ़ो(vc, &i);
			wake_up(&vcpu->arch.cpu_run);
		पूर्ण
	पूर्ण
	spin_unlock(&vc->lock);
पूर्ण

/*
 * Clear core from the list of active host cores as we are about to
 * enter the guest. Only करो this अगर it is the primary thपढ़ो of the
 * core (not अगर a subcore) that is entering the guest.
 */
अटल अंतरभूत पूर्णांक kvmppc_clear_host_core(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक core;

	अगर (!kvmppc_host_rm_ops_hv || cpu_thपढ़ो_in_core(cpu))
		वापस 0;
	/*
	 * Memory barrier can be omitted here as we will करो a smp_wmb()
	 * later in kvmppc_start_thपढ़ो and we need ensure that state is
	 * visible to other CPUs only after we enter guest.
	 */
	core = cpu >> thपढ़ोs_shअगरt;
	kvmppc_host_rm_ops_hv->rm_core[core].rm_state.in_host = 0;
	वापस 0;
पूर्ण

/*
 * Advertise this core as an active host core since we निकासed the guest
 * Only need to करो this अगर it is the primary thपढ़ो of the core that is
 * निकासing.
 */
अटल अंतरभूत पूर्णांक kvmppc_set_host_core(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक core;

	अगर (!kvmppc_host_rm_ops_hv || cpu_thपढ़ो_in_core(cpu))
		वापस 0;

	/*
	 * Memory barrier can be omitted here because we करो a spin_unlock
	 * immediately after this which provides the memory barrier.
	 */
	core = cpu >> thपढ़ोs_shअगरt;
	kvmppc_host_rm_ops_hv->rm_core[core].rm_state.in_host = 1;
	वापस 0;
पूर्ण

अटल व्योम set_irq_happened(पूर्णांक trap)
अणु
	चयन (trap) अणु
	हाल BOOK3S_INTERRUPT_EXTERNAL:
		local_paca->irq_happened |= PACA_IRQ_EE;
		अवरोध;
	हाल BOOK3S_INTERRUPT_H_DOORBELL:
		local_paca->irq_happened |= PACA_IRQ_DBELL;
		अवरोध;
	हाल BOOK3S_INTERRUPT_HMI:
		local_paca->irq_happened |= PACA_IRQ_HMI;
		अवरोध;
	हाल BOOK3S_INTERRUPT_SYSTEM_RESET:
		replay_प्रणाली_reset();
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Run a set of guest thपढ़ोs on a physical core.
 * Called with vc->lock held.
 */
अटल noअंतरभूत व्योम kvmppc_run_core(काष्ठा kvmppc_vcore *vc)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;
	पूर्णांक srcu_idx;
	काष्ठा core_info core_info;
	काष्ठा kvmppc_vcore *pvc;
	काष्ठा kvm_split_mode split_info, *sip;
	पूर्णांक split, subcore_size, active;
	पूर्णांक sub;
	bool thr0_करोne;
	अचिन्हित दीर्घ cmd_bit, stat_bit;
	पूर्णांक pcpu, thr;
	पूर्णांक target_thपढ़ोs;
	पूर्णांक controlled_thपढ़ोs;
	पूर्णांक trap;
	bool is_घातer8;

	/*
	 * Remove from the list any thपढ़ोs that have a संकेत pending
	 * or need a VPA update करोne
	 */
	prepare_thपढ़ोs(vc);

	/* अगर the runner is no दीर्घer runnable, let the caller pick a new one */
	अगर (vc->runner->arch.state != KVMPPC_VCPU_RUNNABLE)
		वापस;

	/*
	 * Initialize *vc.
	 */
	init_vcore_to_run(vc);
	vc->preempt_tb = TB_NIL;

	/*
	 * Number of thपढ़ोs that we will be controlling: the same as
	 * the number of thपढ़ोs per subcore, except on POWER9,
	 * where it's 1 because the thपढ़ोs are (mostly) independent.
	 */
	controlled_thपढ़ोs = thपढ़ोs_per_vcore(vc->kvm);

	/*
	 * Make sure we are running on primary thपढ़ोs, and that secondary
	 * thपढ़ोs are offline.  Also check अगर the number of thपढ़ोs in this
	 * guest are greater than the current प्रणाली thपढ़ोs per guest.
	 * On POWER9, we need to be not in independent-thपढ़ोs mode अगर
	 * this is a HPT guest on a radix host machine where the
	 * CPU thपढ़ोs may not be in dअगरferent MMU modes.
	 */
	अगर ((controlled_thपढ़ोs > 1) &&
	    ((vc->num_thपढ़ोs > thपढ़ोs_per_subcore) || !on_primary_thपढ़ो())) अणु
		क्रम_each_runnable_thपढ़ो(i, vcpu, vc) अणु
			vcpu->arch.ret = -EBUSY;
			kvmppc_हटाओ_runnable(vc, vcpu);
			wake_up(&vcpu->arch.cpu_run);
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * See अगर we could run any other vcores on the physical core
	 * aदीर्घ with this one.
	 */
	init_core_info(&core_info, vc);
	pcpu = smp_processor_id();
	target_thपढ़ोs = controlled_thपढ़ोs;
	अगर (target_smt_mode && target_smt_mode < target_thपढ़ोs)
		target_thपढ़ोs = target_smt_mode;
	अगर (vc->num_thपढ़ोs < target_thपढ़ोs)
		collect_piggybacks(&core_info, target_thपढ़ोs);

	/*
	 * On radix, arrange क्रम TLB flushing अगर necessary.
	 * This has to be करोne beक्रमe disabling पूर्णांकerrupts since
	 * it uses smp_call_function().
	 */
	pcpu = smp_processor_id();
	अगर (kvm_is_radix(vc->kvm)) अणु
		क्रम (sub = 0; sub < core_info.n_subcores; ++sub)
			क्रम_each_runnable_thपढ़ो(i, vcpu, core_info.vc[sub])
				kvmppc_prepare_radix_vcpu(vcpu, pcpu);
	पूर्ण

	/*
	 * Hard-disable पूर्णांकerrupts, and check resched flag and संकेतs.
	 * If we need to reschedule or deliver a संकेत, clean up
	 * and वापस without going पूर्णांकo the guest(s).
	 * If the mmu_पढ़ोy flag has been cleared, करोn't go पूर्णांकo the
	 * guest because that means a HPT resize operation is in progress.
	 */
	local_irq_disable();
	hard_irq_disable();
	अगर (lazy_irq_pending() || need_resched() ||
	    recheck_संकेतs_and_mmu(&core_info)) अणु
		local_irq_enable();
		vc->vcore_state = VCORE_INACTIVE;
		/* Unlock all except the primary vcore */
		क्रम (sub = 1; sub < core_info.n_subcores; ++sub) अणु
			pvc = core_info.vc[sub];
			/* Put back on to the preempted vcores list */
			kvmppc_vcore_preempt(pvc);
			spin_unlock(&pvc->lock);
		पूर्ण
		क्रम (i = 0; i < controlled_thपढ़ोs; ++i)
			kvmppc_release_hwthपढ़ो(pcpu + i);
		वापस;
	पूर्ण

	kvmppc_clear_host_core(pcpu);

	/* Decide on micro-thपढ़ोing (split-core) mode */
	subcore_size = thपढ़ोs_per_subcore;
	cmd_bit = stat_bit = 0;
	split = core_info.n_subcores;
	sip = शून्य;
	is_घातer8 = cpu_has_feature(CPU_FTR_ARCH_207S)
		&& !cpu_has_feature(CPU_FTR_ARCH_300);

	अगर (split > 1) अणु
		sip = &split_info;
		स_रखो(&split_info, 0, माप(split_info));
		क्रम (sub = 0; sub < core_info.n_subcores; ++sub)
			split_info.vc[sub] = core_info.vc[sub];

		अगर (is_घातer8) अणु
			अगर (split == 2 && (dynamic_mt_modes & 2)) अणु
				cmd_bit = HID0_POWER8_1TO2LPAR;
				stat_bit = HID0_POWER8_2LPARMODE;
			पूर्ण अन्यथा अणु
				split = 4;
				cmd_bit = HID0_POWER8_1TO4LPAR;
				stat_bit = HID0_POWER8_4LPARMODE;
			पूर्ण
			subcore_size = MAX_SMT_THREADS / split;
			split_info.rpr = mfspr(SPRN_RPR);
			split_info.pmmar = mfspr(SPRN_PMMAR);
			split_info.ldbar = mfspr(SPRN_LDBAR);
			split_info.subcore_size = subcore_size;
		पूर्ण अन्यथा अणु
			split_info.subcore_size = 1;
		पूर्ण

		/* order ग_लिखोs to split_info beक्रमe kvm_split_mode poपूर्णांकer */
		smp_wmb();
	पूर्ण

	क्रम (thr = 0; thr < controlled_thपढ़ोs; ++thr) अणु
		काष्ठा paca_काष्ठा *paca = paca_ptrs[pcpu + thr];

		paca->kvm_hstate.napping = 0;
		paca->kvm_hstate.kvm_split_mode = sip;
	पूर्ण

	/* Initiate micro-thपढ़ोing (split-core) on POWER8 अगर required */
	अगर (cmd_bit) अणु
		अचिन्हित दीर्घ hid0 = mfspr(SPRN_HID0);

		hid0 |= cmd_bit | HID0_POWER8_DYNLPARDIS;
		mb();
		mtspr(SPRN_HID0, hid0);
		isync();
		क्रम (;;) अणु
			hid0 = mfspr(SPRN_HID0);
			अगर (hid0 & stat_bit)
				अवरोध;
			cpu_relax();
		पूर्ण
	पूर्ण

	/*
	 * On POWER8, set RWMR रेजिस्टर.
	 * Since it only affects PURR and SPURR, it करोesn't affect
	 * the host, so we करोn't save/restore the host value.
	 */
	अगर (is_घातer8) अणु
		अचिन्हित दीर्घ rwmr_val = RWMR_RPA_P8_8THREAD;
		पूर्णांक n_online = atomic_पढ़ो(&vc->online_count);

		/*
		 * Use the 8-thपढ़ो value अगर we're करोing split-core
		 * or अगर the vcore's online count looks bogus.
		 */
		अगर (split == 1 && thपढ़ोs_per_subcore == MAX_SMT_THREADS &&
		    n_online >= 1 && n_online <= MAX_SMT_THREADS)
			rwmr_val = p8_rwmr_values[n_online];
		mtspr(SPRN_RWMR, rwmr_val);
	पूर्ण

	/* Start all the thपढ़ोs */
	active = 0;
	क्रम (sub = 0; sub < core_info.n_subcores; ++sub) अणु
		thr = is_घातer8 ? subcore_thपढ़ो_map[sub] : sub;
		thr0_करोne = false;
		active |= 1 << thr;
		pvc = core_info.vc[sub];
		pvc->pcpu = pcpu + thr;
		क्रम_each_runnable_thपढ़ो(i, vcpu, pvc) अणु
			kvmppc_start_thपढ़ो(vcpu, pvc);
			kvmppc_create_dtl_entry(vcpu, pvc);
			trace_kvm_guest_enter(vcpu);
			अगर (!vcpu->arch.ptid)
				thr0_करोne = true;
			active |= 1 << (thr + vcpu->arch.ptid);
		पूर्ण
		/*
		 * We need to start the first thपढ़ो of each subcore
		 * even अगर it करोesn't have a vcpu.
		 */
		अगर (!thr0_करोne)
			kvmppc_start_thपढ़ो(शून्य, pvc);
	पूर्ण

	/*
	 * Ensure that split_info.करो_nap is set after setting
	 * the vcore poपूर्णांकer in the PACA of the secondaries.
	 */
	smp_mb();

	/*
	 * When करोing micro-thपढ़ोing, poke the inactive thपढ़ोs as well.
	 * This माला_लो them to the nap inकाष्ठाion after kvm_करो_nap,
	 * which reduces the समय taken to unsplit later.
	 */
	अगर (cmd_bit) अणु
		split_info.करो_nap = 1;	/* ask secondaries to nap when करोne */
		क्रम (thr = 1; thr < thपढ़ोs_per_subcore; ++thr)
			अगर (!(active & (1 << thr)))
				kvmppc_ipi_thपढ़ो(pcpu + thr);
	पूर्ण

	vc->vcore_state = VCORE_RUNNING;
	preempt_disable();

	trace_kvmppc_run_core(vc, 0);

	क्रम (sub = 0; sub < core_info.n_subcores; ++sub)
		spin_unlock(&core_info.vc[sub]->lock);

	guest_enter_irqoff();

	srcu_idx = srcu_पढ़ो_lock(&vc->kvm->srcu);

	this_cpu_disable_ftrace();

	/*
	 * Interrupts will be enabled once we get पूर्णांकo the guest,
	 * so tell lockdep that we're about to enable पूर्णांकerrupts.
	 */
	trace_hardirqs_on();

	trap = __kvmppc_vcore_entry();

	trace_hardirqs_off();

	this_cpu_enable_ftrace();

	srcu_पढ़ो_unlock(&vc->kvm->srcu, srcu_idx);

	set_irq_happened(trap);

	spin_lock(&vc->lock);
	/* prevent other vcpu thपढ़ोs from करोing kvmppc_start_thपढ़ो() now */
	vc->vcore_state = VCORE_EXITING;

	/* रुको क्रम secondary thपढ़ोs to finish writing their state to memory */
	kvmppc_रुको_क्रम_nap(controlled_thपढ़ोs);

	/* Return to whole-core mode अगर we split the core earlier */
	अगर (cmd_bit) अणु
		अचिन्हित दीर्घ hid0 = mfspr(SPRN_HID0);
		अचिन्हित दीर्घ loops = 0;

		hid0 &= ~HID0_POWER8_DYNLPARDIS;
		stat_bit = HID0_POWER8_2LPARMODE | HID0_POWER8_4LPARMODE;
		mb();
		mtspr(SPRN_HID0, hid0);
		isync();
		क्रम (;;) अणु
			hid0 = mfspr(SPRN_HID0);
			अगर (!(hid0 & stat_bit))
				अवरोध;
			cpu_relax();
			++loops;
		पूर्ण
		split_info.करो_nap = 0;
	पूर्ण

	kvmppc_set_host_core(pcpu);

	guest_निकास_irqoff();

	local_irq_enable();

	/* Let secondaries go back to the offline loop */
	क्रम (i = 0; i < controlled_thपढ़ोs; ++i) अणु
		kvmppc_release_hwthपढ़ो(pcpu + i);
		अगर (sip && sip->napped[i])
			kvmppc_ipi_thपढ़ो(pcpu + i);
		cpumask_clear_cpu(pcpu + i, &vc->kvm->arch.cpu_in_guest);
	पूर्ण

	spin_unlock(&vc->lock);

	/* make sure updates to secondary vcpu काष्ठाs are visible now */
	smp_mb();

	preempt_enable();

	क्रम (sub = 0; sub < core_info.n_subcores; ++sub) अणु
		pvc = core_info.vc[sub];
		post_guest_process(pvc, pvc == vc);
	पूर्ण

	spin_lock(&vc->lock);

 out:
	vc->vcore_state = VCORE_INACTIVE;
	trace_kvmppc_run_core(vc, 1);
पूर्ण

/*
 * Load up hypervisor-mode रेजिस्टरs on P9.
 */
अटल पूर्णांक kvmhv_load_hv_regs_and_go(काष्ठा kvm_vcpu *vcpu, u64 समय_limit,
				     अचिन्हित दीर्घ lpcr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	s64 hdec;
	u64 tb, purr, spurr;
	पूर्णांक trap;
	अचिन्हित दीर्घ host_hfscr = mfspr(SPRN_HFSCR);
	अचिन्हित दीर्घ host_ciabr = mfspr(SPRN_CIABR);
	अचिन्हित दीर्घ host_dawr0 = mfspr(SPRN_DAWR0);
	अचिन्हित दीर्घ host_dawrx0 = mfspr(SPRN_DAWRX0);
	अचिन्हित दीर्घ host_psscr = mfspr(SPRN_PSSCR);
	अचिन्हित दीर्घ host_pidr = mfspr(SPRN_PID);
	अचिन्हित दीर्घ host_dawr1 = 0;
	अचिन्हित दीर्घ host_dawrx1 = 0;

	अगर (cpu_has_feature(CPU_FTR_DAWR1)) अणु
		host_dawr1 = mfspr(SPRN_DAWR1);
		host_dawrx1 = mfspr(SPRN_DAWRX1);
	पूर्ण

	/*
	 * P8 and P9 suppress the HDEC exception when LPCR[HDICE] = 0,
	 * so set HDICE beक्रमe writing HDEC.
	 */
	mtspr(SPRN_LPCR, vcpu->kvm->arch.host_lpcr | LPCR_HDICE);
	isync();

	hdec = समय_limit - mftb();
	अगर (hdec < 0) अणु
		mtspr(SPRN_LPCR, vcpu->kvm->arch.host_lpcr);
		isync();
		वापस BOOK3S_INTERRUPT_HV_DECREMENTER;
	पूर्ण
	mtspr(SPRN_HDEC, hdec);

	अगर (vc->tb_offset) अणु
		u64 new_tb = mftb() + vc->tb_offset;
		mtspr(SPRN_TBU40, new_tb);
		tb = mftb();
		अगर ((tb & 0xffffff) < (new_tb & 0xffffff))
			mtspr(SPRN_TBU40, new_tb + 0x1000000);
		vc->tb_offset_applied = vc->tb_offset;
	पूर्ण

	अगर (vc->pcr)
		mtspr(SPRN_PCR, vc->pcr | PCR_MASK);
	mtspr(SPRN_DPDES, vc->dpdes);
	mtspr(SPRN_VTB, vc->vtb);

	local_paca->kvm_hstate.host_purr = mfspr(SPRN_PURR);
	local_paca->kvm_hstate.host_spurr = mfspr(SPRN_SPURR);
	mtspr(SPRN_PURR, vcpu->arch.purr);
	mtspr(SPRN_SPURR, vcpu->arch.spurr);

	अगर (dawr_enabled()) अणु
		mtspr(SPRN_DAWR0, vcpu->arch.dawr0);
		mtspr(SPRN_DAWRX0, vcpu->arch.dawrx0);
		अगर (cpu_has_feature(CPU_FTR_DAWR1)) अणु
			mtspr(SPRN_DAWR1, vcpu->arch.dawr1);
			mtspr(SPRN_DAWRX1, vcpu->arch.dawrx1);
		पूर्ण
	पूर्ण
	mtspr(SPRN_CIABR, vcpu->arch.ciabr);
	mtspr(SPRN_IC, vcpu->arch.ic);
	mtspr(SPRN_PID, vcpu->arch.pid);

	mtspr(SPRN_PSSCR, vcpu->arch.psscr | PSSCR_EC |
	      (local_paca->kvm_hstate.fake_suspend << PSSCR_FAKE_SUSPEND_LG));

	mtspr(SPRN_HFSCR, vcpu->arch.hfscr);

	mtspr(SPRN_SPRG0, vcpu->arch.shregs.sprg0);
	mtspr(SPRN_SPRG1, vcpu->arch.shregs.sprg1);
	mtspr(SPRN_SPRG2, vcpu->arch.shregs.sprg2);
	mtspr(SPRN_SPRG3, vcpu->arch.shregs.sprg3);

	mtspr(SPRN_AMOR, ~0UL);

	mtspr(SPRN_LPCR, lpcr);
	isync();

	kvmppc_xive_push_vcpu(vcpu);

	mtspr(SPRN_SRR0, vcpu->arch.shregs.srr0);
	mtspr(SPRN_SRR1, vcpu->arch.shregs.srr1);

	trap = __kvmhv_vcpu_entry_p9(vcpu);

	/* Advance host PURR/SPURR by the amount used by guest */
	purr = mfspr(SPRN_PURR);
	spurr = mfspr(SPRN_SPURR);
	mtspr(SPRN_PURR, local_paca->kvm_hstate.host_purr +
	      purr - vcpu->arch.purr);
	mtspr(SPRN_SPURR, local_paca->kvm_hstate.host_spurr +
	      spurr - vcpu->arch.spurr);
	vcpu->arch.purr = purr;
	vcpu->arch.spurr = spurr;

	vcpu->arch.ic = mfspr(SPRN_IC);
	vcpu->arch.pid = mfspr(SPRN_PID);
	vcpu->arch.psscr = mfspr(SPRN_PSSCR) & PSSCR_GUEST_VIS;

	vcpu->arch.shregs.sprg0 = mfspr(SPRN_SPRG0);
	vcpu->arch.shregs.sprg1 = mfspr(SPRN_SPRG1);
	vcpu->arch.shregs.sprg2 = mfspr(SPRN_SPRG2);
	vcpu->arch.shregs.sprg3 = mfspr(SPRN_SPRG3);

	/* Preserve PSSCR[FAKE_SUSPEND] until we've called kvmppc_save_पंचांग_hv */
	mtspr(SPRN_PSSCR, host_psscr |
	      (local_paca->kvm_hstate.fake_suspend << PSSCR_FAKE_SUSPEND_LG));
	mtspr(SPRN_HFSCR, host_hfscr);
	mtspr(SPRN_CIABR, host_ciabr);
	mtspr(SPRN_DAWR0, host_dawr0);
	mtspr(SPRN_DAWRX0, host_dawrx0);
	अगर (cpu_has_feature(CPU_FTR_DAWR1)) अणु
		mtspr(SPRN_DAWR1, host_dawr1);
		mtspr(SPRN_DAWRX1, host_dawrx1);
	पूर्ण
	mtspr(SPRN_PID, host_pidr);

	/*
	 * Since this is radix, करो a eieio; tlbsync; ptesync sequence in
	 * हाल we पूर्णांकerrupted the guest between a tlbie and a ptesync.
	 */
	यंत्र अस्थिर("eieio; tlbsync; ptesync");

	/*
	 * cp_पात is required अगर the processor supports local copy-paste
	 * to clear the copy buffer that was under control of the guest.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		यंत्र अस्थिर(PPC_CP_ABORT);

	mtspr(SPRN_LPID, vcpu->kvm->arch.host_lpid);	/* restore host LPID */
	isync();

	vc->dpdes = mfspr(SPRN_DPDES);
	vc->vtb = mfspr(SPRN_VTB);
	mtspr(SPRN_DPDES, 0);
	अगर (vc->pcr)
		mtspr(SPRN_PCR, PCR_MASK);

	अगर (vc->tb_offset_applied) अणु
		u64 new_tb = mftb() - vc->tb_offset_applied;
		mtspr(SPRN_TBU40, new_tb);
		tb = mftb();
		अगर ((tb & 0xffffff) < (new_tb & 0xffffff))
			mtspr(SPRN_TBU40, new_tb + 0x1000000);
		vc->tb_offset_applied = 0;
	पूर्ण

	mtspr(SPRN_HDEC, 0x7fffffff);
	mtspr(SPRN_LPCR, vcpu->kvm->arch.host_lpcr);

	वापस trap;
पूर्ण

/*
 * Virtual-mode guest entry क्रम POWER9 and later when the host and
 * guest are both using the radix MMU.  The LPIDR has alपढ़ोy been set.
 */
अटल पूर्णांक kvmhv_p9_guest_entry(काष्ठा kvm_vcpu *vcpu, u64 समय_limit,
			 अचिन्हित दीर्घ lpcr)
अणु
	काष्ठा kvmppc_vcore *vc = vcpu->arch.vcore;
	अचिन्हित दीर्घ host_dscr = mfspr(SPRN_DSCR);
	अचिन्हित दीर्घ host_tidr = mfspr(SPRN_TIDR);
	अचिन्हित दीर्घ host_iamr = mfspr(SPRN_IAMR);
	अचिन्हित दीर्घ host_amr = mfspr(SPRN_AMR);
	अचिन्हित दीर्घ host_fscr = mfspr(SPRN_FSCR);
	s64 dec;
	u64 tb;
	पूर्णांक trap, save_pmu;

	dec = mfspr(SPRN_DEC);
	tb = mftb();
	अगर (dec < 0)
		वापस BOOK3S_INTERRUPT_HV_DECREMENTER;
	local_paca->kvm_hstate.dec_expires = dec + tb;
	अगर (local_paca->kvm_hstate.dec_expires < समय_limit)
		समय_limit = local_paca->kvm_hstate.dec_expires;

	vcpu->arch.ceded = 0;

	kvmhv_save_host_pmu();		/* saves it to PACA kvm_hstate */

	kvmppc_subcore_enter_guest();

	vc->entry_निकास_map = 1;
	vc->in_guest = 1;

	अगर (vcpu->arch.vpa.pinned_addr) अणु
		काष्ठा lppaca *lp = vcpu->arch.vpa.pinned_addr;
		u32 yield_count = be32_to_cpu(lp->yield_count) + 1;
		lp->yield_count = cpu_to_be32(yield_count);
		vcpu->arch.vpa.dirty = 1;
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_TM) ||
	    cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST))
		kvmppc_restore_पंचांग_hv(vcpu, vcpu->arch.shregs.msr, true);

	kvmhv_load_guest_pmu(vcpu);

	msr_check_and_set(MSR_FP | MSR_VEC | MSR_VSX);
	load_fp_state(&vcpu->arch.fp);
#अगर_घोषित CONFIG_ALTIVEC
	load_vr_state(&vcpu->arch.vr);
#पूर्ण_अगर
	mtspr(SPRN_VRSAVE, vcpu->arch.vrsave);

	mtspr(SPRN_DSCR, vcpu->arch.dscr);
	mtspr(SPRN_IAMR, vcpu->arch.iamr);
	mtspr(SPRN_PSPB, vcpu->arch.pspb);
	mtspr(SPRN_FSCR, vcpu->arch.fscr);
	mtspr(SPRN_TAR, vcpu->arch.tar);
	mtspr(SPRN_EBBHR, vcpu->arch.ebbhr);
	mtspr(SPRN_EBBRR, vcpu->arch.ebbrr);
	mtspr(SPRN_BESCR, vcpu->arch.bescr);
	mtspr(SPRN_WORT, vcpu->arch.wort);
	mtspr(SPRN_TIDR, vcpu->arch.tid);
	mtspr(SPRN_DAR, vcpu->arch.shregs.dar);
	mtspr(SPRN_DSISR, vcpu->arch.shregs.dsisr);
	mtspr(SPRN_AMR, vcpu->arch.amr);
	mtspr(SPRN_UAMOR, vcpu->arch.uamor);

	अगर (!(vcpu->arch.ctrl & 1))
		mtspr(SPRN_CTRLT, mfspr(SPRN_CTRLF) & ~1);

	mtspr(SPRN_DEC, vcpu->arch.dec_expires - mftb());

	अगर (kvmhv_on_pseries()) अणु
		/*
		 * We need to save and restore the guest visible part of the
		 * psscr (i.e. using SPRN_PSSCR_PR) since the hypervisor
		 * करोesn't करो this क्रम us. Note only required अगर pseries since
		 * this is करोne in kvmhv_load_hv_regs_and_go() below otherwise.
		 */
		अचिन्हित दीर्घ host_psscr;
		/* call our hypervisor to load up HV regs and go */
		काष्ठा hv_guest_state hvregs;

		host_psscr = mfspr(SPRN_PSSCR_PR);
		mtspr(SPRN_PSSCR_PR, vcpu->arch.psscr);
		kvmhv_save_hv_regs(vcpu, &hvregs);
		hvregs.lpcr = lpcr;
		vcpu->arch.regs.msr = vcpu->arch.shregs.msr;
		hvregs.version = HV_GUEST_STATE_VERSION;
		अगर (vcpu->arch.nested) अणु
			hvregs.lpid = vcpu->arch.nested->shaकरोw_lpid;
			hvregs.vcpu_token = vcpu->arch.nested_vcpu_id;
		पूर्ण अन्यथा अणु
			hvregs.lpid = vcpu->kvm->arch.lpid;
			hvregs.vcpu_token = vcpu->vcpu_id;
		पूर्ण
		hvregs.hdec_expiry = समय_limit;
		trap = plpar_hcall_norets(H_ENTER_NESTED, __pa(&hvregs),
					  __pa(&vcpu->arch.regs));
		kvmhv_restore_hv_वापस_state(vcpu, &hvregs);
		vcpu->arch.shregs.msr = vcpu->arch.regs.msr;
		vcpu->arch.shregs.dar = mfspr(SPRN_DAR);
		vcpu->arch.shregs.dsisr = mfspr(SPRN_DSISR);
		vcpu->arch.psscr = mfspr(SPRN_PSSCR_PR);
		mtspr(SPRN_PSSCR_PR, host_psscr);

		/* H_CEDE has to be handled now, not later */
		अगर (trap == BOOK3S_INTERRUPT_SYSCALL && !vcpu->arch.nested &&
		    kvmppc_get_gpr(vcpu, 3) == H_CEDE) अणु
			kvmppc_nested_cede(vcpu);
			kvmppc_set_gpr(vcpu, 3, 0);
			trap = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		trap = kvmhv_load_hv_regs_and_go(vcpu, समय_limit, lpcr);
	पूर्ण

	vcpu->arch.slb_max = 0;
	dec = mfspr(SPRN_DEC);
	अगर (!(lpcr & LPCR_LD)) /* Sign extend अगर not using large decrementer */
		dec = (s32) dec;
	tb = mftb();
	vcpu->arch.dec_expires = dec + tb;
	vcpu->cpu = -1;
	vcpu->arch.thपढ़ो_cpu = -1;
	/* Save guest CTRL रेजिस्टर, set runlatch to 1 */
	vcpu->arch.ctrl = mfspr(SPRN_CTRLF);
	अगर (!(vcpu->arch.ctrl & 1))
		mtspr(SPRN_CTRLT, vcpu->arch.ctrl | 1);

	vcpu->arch.iamr = mfspr(SPRN_IAMR);
	vcpu->arch.pspb = mfspr(SPRN_PSPB);
	vcpu->arch.fscr = mfspr(SPRN_FSCR);
	vcpu->arch.tar = mfspr(SPRN_TAR);
	vcpu->arch.ebbhr = mfspr(SPRN_EBBHR);
	vcpu->arch.ebbrr = mfspr(SPRN_EBBRR);
	vcpu->arch.bescr = mfspr(SPRN_BESCR);
	vcpu->arch.wort = mfspr(SPRN_WORT);
	vcpu->arch.tid = mfspr(SPRN_TIDR);
	vcpu->arch.amr = mfspr(SPRN_AMR);
	vcpu->arch.uamor = mfspr(SPRN_UAMOR);
	vcpu->arch.dscr = mfspr(SPRN_DSCR);

	mtspr(SPRN_PSPB, 0);
	mtspr(SPRN_WORT, 0);
	mtspr(SPRN_UAMOR, 0);
	mtspr(SPRN_DSCR, host_dscr);
	mtspr(SPRN_TIDR, host_tidr);
	mtspr(SPRN_IAMR, host_iamr);

	अगर (host_amr != vcpu->arch.amr)
		mtspr(SPRN_AMR, host_amr);

	अगर (host_fscr != vcpu->arch.fscr)
		mtspr(SPRN_FSCR, host_fscr);

	msr_check_and_set(MSR_FP | MSR_VEC | MSR_VSX);
	store_fp_state(&vcpu->arch.fp);
#अगर_घोषित CONFIG_ALTIVEC
	store_vr_state(&vcpu->arch.vr);
#पूर्ण_अगर
	vcpu->arch.vrsave = mfspr(SPRN_VRSAVE);

	अगर (cpu_has_feature(CPU_FTR_TM) ||
	    cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST))
		kvmppc_save_पंचांग_hv(vcpu, vcpu->arch.shregs.msr, true);

	save_pmu = 1;
	अगर (vcpu->arch.vpa.pinned_addr) अणु
		काष्ठा lppaca *lp = vcpu->arch.vpa.pinned_addr;
		u32 yield_count = be32_to_cpu(lp->yield_count) + 1;
		lp->yield_count = cpu_to_be32(yield_count);
		vcpu->arch.vpa.dirty = 1;
		save_pmu = lp->pmcregs_in_use;
	पूर्ण
	/* Must save pmu अगर this guest is capable of running nested guests */
	save_pmu |= nesting_enabled(vcpu->kvm);

	kvmhv_save_guest_pmu(vcpu, save_pmu);

	vc->entry_निकास_map = 0x101;
	vc->in_guest = 0;

	mtspr(SPRN_DEC, local_paca->kvm_hstate.dec_expires - mftb());
	mtspr(SPRN_SPRG_VDSO_WRITE, local_paca->sprg_vdso);

	kvmhv_load_host_pmu();

	kvmppc_subcore_निकास_guest();

	वापस trap;
पूर्ण

/*
 * Wait क्रम some other vcpu thपढ़ो to execute us, and
 * wake us up when we need to handle something in the host.
 */
अटल व्योम kvmppc_रुको_क्रम_exec(काष्ठा kvmppc_vcore *vc,
				 काष्ठा kvm_vcpu *vcpu, पूर्णांक रुको_state)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(&vcpu->arch.cpu_run, &रुको, रुको_state);
	अगर (vcpu->arch.state == KVMPPC_VCPU_RUNNABLE) अणु
		spin_unlock(&vc->lock);
		schedule();
		spin_lock(&vc->lock);
	पूर्ण
	finish_रुको(&vcpu->arch.cpu_run, &रुको);
पूर्ण

अटल व्योम grow_halt_poll_ns(काष्ठा kvmppc_vcore *vc)
अणु
	अगर (!halt_poll_ns_grow)
		वापस;

	vc->halt_poll_ns *= halt_poll_ns_grow;
	अगर (vc->halt_poll_ns < halt_poll_ns_grow_start)
		vc->halt_poll_ns = halt_poll_ns_grow_start;
पूर्ण

अटल व्योम shrink_halt_poll_ns(काष्ठा kvmppc_vcore *vc)
अणु
	अगर (halt_poll_ns_shrink == 0)
		vc->halt_poll_ns = 0;
	अन्यथा
		vc->halt_poll_ns /= halt_poll_ns_shrink;
पूर्ण

#अगर_घोषित CONFIG_KVM_XICS
अटल अंतरभूत bool xive_पूर्णांकerrupt_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!xics_on_xive())
		वापस false;
	वापस vcpu->arch.irq_pending || vcpu->arch.xive_saved_state.pipr <
		vcpu->arch.xive_saved_state.cppr;
पूर्ण
#अन्यथा
अटल अंतरभूत bool xive_पूर्णांकerrupt_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XICS */

अटल bool kvmppc_vcpu_woken(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.pending_exceptions || vcpu->arch.prodded ||
	    kvmppc_करोorbell_pending(vcpu) || xive_पूर्णांकerrupt_pending(vcpu))
		वापस true;

	वापस false;
पूर्ण

/*
 * Check to see अगर any of the runnable vcpus on the vcore have pending
 * exceptions or are no दीर्घer ceded
 */
अटल पूर्णांक kvmppc_vcore_check_block(काष्ठा kvmppc_vcore *vc)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	क्रम_each_runnable_thपढ़ो(i, vcpu, vc) अणु
		अगर (!vcpu->arch.ceded || kvmppc_vcpu_woken(vcpu))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * All the vcpus in this vcore are idle, so रुको क्रम a decrementer
 * or बाह्यal पूर्णांकerrupt to one of the vcpus.  vc->lock is held.
 */
अटल व्योम kvmppc_vcore_blocked(काष्ठा kvmppc_vcore *vc)
अणु
	kसमय_प्रकार cur, start_poll, start_रुको;
	पूर्णांक करो_sleep = 1;
	u64 block_ns;

	/* Poll क्रम pending exceptions and ceded state */
	cur = start_poll = kसमय_get();
	अगर (vc->halt_poll_ns) अणु
		kसमय_प्रकार stop = kसमय_add_ns(start_poll, vc->halt_poll_ns);
		++vc->runner->स्थिति.सalt_attempted_poll;

		vc->vcore_state = VCORE_POLLING;
		spin_unlock(&vc->lock);

		करो अणु
			अगर (kvmppc_vcore_check_block(vc)) अणु
				करो_sleep = 0;
				अवरोध;
			पूर्ण
			cur = kसमय_get();
		पूर्ण जबतक (kvm_vcpu_can_poll(cur, stop));

		spin_lock(&vc->lock);
		vc->vcore_state = VCORE_INACTIVE;

		अगर (!करो_sleep) अणु
			++vc->runner->स्थिति.सalt_successful_poll;
			जाओ out;
		पूर्ण
	पूर्ण

	prepare_to_rcuरुको(&vc->रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	अगर (kvmppc_vcore_check_block(vc)) अणु
		finish_rcuरुको(&vc->रुको);
		करो_sleep = 0;
		/* If we polled, count this as a successful poll */
		अगर (vc->halt_poll_ns)
			++vc->runner->स्थिति.सalt_successful_poll;
		जाओ out;
	पूर्ण

	start_रुको = kसमय_get();

	vc->vcore_state = VCORE_SLEEPING;
	trace_kvmppc_vcore_blocked(vc, 0);
	spin_unlock(&vc->lock);
	schedule();
	finish_rcuरुको(&vc->रुको);
	spin_lock(&vc->lock);
	vc->vcore_state = VCORE_INACTIVE;
	trace_kvmppc_vcore_blocked(vc, 1);
	++vc->runner->स्थिति.सalt_successful_रुको;

	cur = kसमय_get();

out:
	block_ns = kसमय_प्रकारo_ns(cur) - kसमय_प्रकारo_ns(start_poll);

	/* Attribute रुको समय */
	अगर (करो_sleep) अणु
		vc->runner->स्थिति.सalt_रुको_ns +=
			kसमय_प्रकारo_ns(cur) - kसमय_प्रकारo_ns(start_रुको);
		/* Attribute failed poll समय */
		अगर (vc->halt_poll_ns)
			vc->runner->स्थिति.सalt_poll_fail_ns +=
				kसमय_प्रकारo_ns(start_रुको) -
				kसमय_प्रकारo_ns(start_poll);
	पूर्ण अन्यथा अणु
		/* Attribute successful poll समय */
		अगर (vc->halt_poll_ns)
			vc->runner->स्थिति.सalt_poll_success_ns +=
				kसमय_प्रकारo_ns(cur) -
				kसमय_प्रकारo_ns(start_poll);
	पूर्ण

	/* Adjust poll समय */
	अगर (halt_poll_ns) अणु
		अगर (block_ns <= vc->halt_poll_ns)
			;
		/* We slept and blocked क्रम दीर्घer than the max halt समय */
		अन्यथा अगर (vc->halt_poll_ns && block_ns > halt_poll_ns)
			shrink_halt_poll_ns(vc);
		/* We slept and our poll समय is too small */
		अन्यथा अगर (vc->halt_poll_ns < halt_poll_ns &&
				block_ns < halt_poll_ns)
			grow_halt_poll_ns(vc);
		अगर (vc->halt_poll_ns > halt_poll_ns)
			vc->halt_poll_ns = halt_poll_ns;
	पूर्ण अन्यथा
		vc->halt_poll_ns = 0;

	trace_kvmppc_vcore_wakeup(करो_sleep, block_ns);
पूर्ण

/*
 * This never fails क्रम a radix guest, as none of the operations it करोes
 * क्रम a radix guest can fail or have a way to report failure.
 * kvmhv_run_single_vcpu() relies on this fact.
 */
अटल पूर्णांक kvmhv_setup_mmu(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r = 0;
	काष्ठा kvm *kvm = vcpu->kvm;

	mutex_lock(&kvm->arch.mmu_setup_lock);
	अगर (!kvm->arch.mmu_पढ़ोy) अणु
		अगर (!kvm_is_radix(kvm))
			r = kvmppc_hv_setup_htab_rma(vcpu);
		अगर (!r) अणु
			अगर (cpu_has_feature(CPU_FTR_ARCH_300))
				kvmppc_setup_partition_table(kvm);
			kvm->arch.mmu_पढ़ोy = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_run_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक n_ceded, i, r;
	काष्ठा kvmppc_vcore *vc;
	काष्ठा kvm_vcpu *v;

	trace_kvmppc_run_vcpu_enter(vcpu);

	run->निकास_reason = 0;
	vcpu->arch.ret = RESUME_GUEST;
	vcpu->arch.trap = 0;
	kvmppc_update_vpas(vcpu);

	/*
	 * Synchronize with other thपढ़ोs in this भव core
	 */
	vc = vcpu->arch.vcore;
	spin_lock(&vc->lock);
	vcpu->arch.ceded = 0;
	vcpu->arch.run_task = current;
	vcpu->arch.stolen_logged = vcore_stolen_समय(vc, mftb());
	vcpu->arch.state = KVMPPC_VCPU_RUNNABLE;
	vcpu->arch.busy_preempt = TB_NIL;
	WRITE_ONCE(vc->runnable_thपढ़ोs[vcpu->arch.ptid], vcpu);
	++vc->n_runnable;

	/*
	 * This happens the first समय this is called क्रम a vcpu.
	 * If the vcore is alपढ़ोy running, we may be able to start
	 * this thपढ़ो straight away and have it join in.
	 */
	अगर (!संकेत_pending(current)) अणु
		अगर ((vc->vcore_state == VCORE_PIGGYBACK ||
		     vc->vcore_state == VCORE_RUNNING) &&
			   !VCORE_IS_EXITING(vc)) अणु
			kvmppc_create_dtl_entry(vcpu, vc);
			kvmppc_start_thपढ़ो(vcpu, vc);
			trace_kvm_guest_enter(vcpu);
		पूर्ण अन्यथा अगर (vc->vcore_state == VCORE_SLEEPING) अणु
		        rcuरुको_wake_up(&vc->रुको);
		पूर्ण

	पूर्ण

	जबतक (vcpu->arch.state == KVMPPC_VCPU_RUNNABLE &&
	       !संकेत_pending(current)) अणु
		/* See अगर the MMU is पढ़ोy to go */
		अगर (!vcpu->kvm->arch.mmu_पढ़ोy) अणु
			spin_unlock(&vc->lock);
			r = kvmhv_setup_mmu(vcpu);
			spin_lock(&vc->lock);
			अगर (r) अणु
				run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
				run->fail_entry.
					hardware_entry_failure_reason = 0;
				vcpu->arch.ret = r;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (vc->vcore_state == VCORE_PREEMPT && vc->runner == शून्य)
			kvmppc_vcore_end_preempt(vc);

		अगर (vc->vcore_state != VCORE_INACTIVE) अणु
			kvmppc_रुको_क्रम_exec(vc, vcpu, TASK_INTERRUPTIBLE);
			जारी;
		पूर्ण
		क्रम_each_runnable_thपढ़ो(i, v, vc) अणु
			kvmppc_core_prepare_to_enter(v);
			अगर (संकेत_pending(v->arch.run_task)) अणु
				kvmppc_हटाओ_runnable(vc, v);
				v->stat.संकेत_निकासs++;
				v->run->निकास_reason = KVM_EXIT_INTR;
				v->arch.ret = -EINTR;
				wake_up(&v->arch.cpu_run);
			पूर्ण
		पूर्ण
		अगर (!vc->n_runnable || vcpu->arch.state != KVMPPC_VCPU_RUNNABLE)
			अवरोध;
		n_ceded = 0;
		क्रम_each_runnable_thपढ़ो(i, v, vc) अणु
			अगर (!kvmppc_vcpu_woken(v))
				n_ceded += v->arch.ceded;
			अन्यथा
				v->arch.ceded = 0;
		पूर्ण
		vc->runner = vcpu;
		अगर (n_ceded == vc->n_runnable) अणु
			kvmppc_vcore_blocked(vc);
		पूर्ण अन्यथा अगर (need_resched()) अणु
			kvmppc_vcore_preempt(vc);
			/* Let something अन्यथा run */
			cond_resched_lock(&vc->lock);
			अगर (vc->vcore_state == VCORE_PREEMPT)
				kvmppc_vcore_end_preempt(vc);
		पूर्ण अन्यथा अणु
			kvmppc_run_core(vc);
		पूर्ण
		vc->runner = शून्य;
	पूर्ण

	जबतक (vcpu->arch.state == KVMPPC_VCPU_RUNNABLE &&
	       (vc->vcore_state == VCORE_RUNNING ||
		vc->vcore_state == VCORE_EXITING ||
		vc->vcore_state == VCORE_PIGGYBACK))
		kvmppc_रुको_क्रम_exec(vc, vcpu, TASK_UNINTERRUPTIBLE);

	अगर (vc->vcore_state == VCORE_PREEMPT && vc->runner == शून्य)
		kvmppc_vcore_end_preempt(vc);

	अगर (vcpu->arch.state == KVMPPC_VCPU_RUNNABLE) अणु
		kvmppc_हटाओ_runnable(vc, vcpu);
		vcpu->stat.संकेत_निकासs++;
		run->निकास_reason = KVM_EXIT_INTR;
		vcpu->arch.ret = -EINTR;
	पूर्ण

	अगर (vc->n_runnable && vc->vcore_state == VCORE_INACTIVE) अणु
		/* Wake up some vcpu to run the core */
		i = -1;
		v = next_runnable_thपढ़ो(vc, &i);
		wake_up(&v->arch.cpu_run);
	पूर्ण

	trace_kvmppc_run_vcpu_निकास(vcpu);
	spin_unlock(&vc->lock);
	वापस vcpu->arch.ret;
पूर्ण

पूर्णांक kvmhv_run_single_vcpu(काष्ठा kvm_vcpu *vcpu, u64 समय_limit,
			  अचिन्हित दीर्घ lpcr)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक trap, r, pcpu;
	पूर्णांक srcu_idx, lpid;
	काष्ठा kvmppc_vcore *vc;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_nested_guest *nested = vcpu->arch.nested;

	trace_kvmppc_run_vcpu_enter(vcpu);

	run->निकास_reason = 0;
	vcpu->arch.ret = RESUME_GUEST;
	vcpu->arch.trap = 0;

	vc = vcpu->arch.vcore;
	vcpu->arch.ceded = 0;
	vcpu->arch.run_task = current;
	vcpu->arch.stolen_logged = vcore_stolen_समय(vc, mftb());
	vcpu->arch.state = KVMPPC_VCPU_RUNNABLE;
	vcpu->arch.busy_preempt = TB_NIL;
	vcpu->arch.last_inst = KVM_INST_FETCH_FAILED;
	vc->runnable_thपढ़ोs[0] = vcpu;
	vc->n_runnable = 1;
	vc->runner = vcpu;

	/* See अगर the MMU is पढ़ोy to go */
	अगर (!kvm->arch.mmu_पढ़ोy)
		kvmhv_setup_mmu(vcpu);

	अगर (need_resched())
		cond_resched();

	kvmppc_update_vpas(vcpu);

	init_vcore_to_run(vc);
	vc->preempt_tb = TB_NIL;

	preempt_disable();
	pcpu = smp_processor_id();
	vc->pcpu = pcpu;
	kvmppc_prepare_radix_vcpu(vcpu, pcpu);

	local_irq_disable();
	hard_irq_disable();
	अगर (संकेत_pending(current))
		जाओ sigpend;
	अगर (lazy_irq_pending() || need_resched() || !kvm->arch.mmu_पढ़ोy)
		जाओ out;

	अगर (!nested) अणु
		kvmppc_core_prepare_to_enter(vcpu);
		अगर (vcpu->arch.करोorbell_request) अणु
			vc->dpdes = 1;
			smp_wmb();
			vcpu->arch.करोorbell_request = 0;
		पूर्ण
		अगर (test_bit(BOOK3S_IRQPRIO_EXTERNAL,
			     &vcpu->arch.pending_exceptions))
			lpcr |= LPCR_MER;
	पूर्ण अन्यथा अगर (vcpu->arch.pending_exceptions ||
		   vcpu->arch.करोorbell_request ||
		   xive_पूर्णांकerrupt_pending(vcpu)) अणु
		vcpu->arch.ret = RESUME_HOST;
		जाओ out;
	पूर्ण

	kvmppc_clear_host_core(pcpu);

	local_paca->kvm_hstate.napping = 0;
	local_paca->kvm_hstate.kvm_split_mode = शून्य;
	kvmppc_start_thपढ़ो(vcpu, vc);
	kvmppc_create_dtl_entry(vcpu, vc);
	trace_kvm_guest_enter(vcpu);

	vc->vcore_state = VCORE_RUNNING;
	trace_kvmppc_run_core(vc, 0);

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		lpid = nested ? nested->shaकरोw_lpid : kvm->arch.lpid;
		mtspr(SPRN_LPID, lpid);
		isync();
		kvmppc_check_need_tlb_flush(kvm, pcpu, nested);
	पूर्ण

	guest_enter_irqoff();

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);

	this_cpu_disable_ftrace();

	/* Tell lockdep that we're about to enable पूर्णांकerrupts */
	trace_hardirqs_on();

	trap = kvmhv_p9_guest_entry(vcpu, समय_limit, lpcr);
	vcpu->arch.trap = trap;

	trace_hardirqs_off();

	this_cpu_enable_ftrace();

	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		mtspr(SPRN_LPID, kvm->arch.host_lpid);
		isync();
	पूर्ण

	set_irq_happened(trap);

	kvmppc_set_host_core(pcpu);

	guest_निकास_irqoff();

	local_irq_enable();

	cpumask_clear_cpu(pcpu, &kvm->arch.cpu_in_guest);

	preempt_enable();

	/*
	 * cancel pending decrementer exception अगर DEC is now positive, or अगर
	 * entering a nested guest in which हाल the decrementer is now owned
	 * by L2 and the L1 decrementer is provided in hdec_expires
	 */
	अगर (kvmppc_core_pending_dec(vcpu) &&
			((get_tb() < vcpu->arch.dec_expires) ||
			 (trap == BOOK3S_INTERRUPT_SYSCALL &&
			  kvmppc_get_gpr(vcpu, 3) == H_ENTER_NESTED)))
		kvmppc_core_dequeue_dec(vcpu);

	trace_kvm_guest_निकास(vcpu);
	r = RESUME_GUEST;
	अगर (trap) अणु
		अगर (!nested)
			r = kvmppc_handle_निकास_hv(vcpu, current);
		अन्यथा
			r = kvmppc_handle_nested_निकास(vcpu);
	पूर्ण
	vcpu->arch.ret = r;

	अगर (is_kvmppc_resume_guest(r) && vcpu->arch.ceded &&
	    !kvmppc_vcpu_woken(vcpu)) अणु
		kvmppc_set_समयr(vcpu);
		जबतक (vcpu->arch.ceded && !kvmppc_vcpu_woken(vcpu)) अणु
			अगर (संकेत_pending(current)) अणु
				vcpu->stat.संकेत_निकासs++;
				run->निकास_reason = KVM_EXIT_INTR;
				vcpu->arch.ret = -EINTR;
				अवरोध;
			पूर्ण
			spin_lock(&vc->lock);
			kvmppc_vcore_blocked(vc);
			spin_unlock(&vc->lock);
		पूर्ण
	पूर्ण
	vcpu->arch.ceded = 0;

	vc->vcore_state = VCORE_INACTIVE;
	trace_kvmppc_run_core(vc, 1);

 करोne:
	kvmppc_हटाओ_runnable(vc, vcpu);
	trace_kvmppc_run_vcpu_निकास(vcpu);

	वापस vcpu->arch.ret;

 sigpend:
	vcpu->stat.संकेत_निकासs++;
	run->निकास_reason = KVM_EXIT_INTR;
	vcpu->arch.ret = -EINTR;
 out:
	local_irq_enable();
	preempt_enable();
	जाओ करोne;
पूर्ण

अटल पूर्णांक kvmppc_vcpu_run_hv(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक r;
	पूर्णांक srcu_idx;
	अचिन्हित दीर्घ ebb_regs[3] = अणुपूर्ण;	/* shut up GCC */
	अचिन्हित दीर्घ user_tar = 0;
	अचिन्हित पूर्णांक user_vrsave;
	काष्ठा kvm *kvm;

	अगर (!vcpu->arch.sane) अणु
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		वापस -EINVAL;
	पूर्ण

	/*
	 * Don't allow entry with a suspended transaction, because
	 * the guest entry/निकास code will lose it.
	 * If the guest has TM enabled, save away their TM-related SPRs
	 * (they will get restored by the TM unavailable पूर्णांकerrupt).
	 */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	अगर (cpu_has_feature(CPU_FTR_TM) && current->thपढ़ो.regs &&
	    (current->thपढ़ो.regs->msr & MSR_TM)) अणु
		अगर (MSR_TM_ACTIVE(current->thपढ़ो.regs->msr)) अणु
			run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
			run->fail_entry.hardware_entry_failure_reason = 0;
			वापस -EINVAL;
		पूर्ण
		/* Enable TM so we can पढ़ो the TM SPRs */
		mपंचांगsr(mfmsr() | MSR_TM);
		current->thपढ़ो.पंचांग_tfhar = mfspr(SPRN_TFHAR);
		current->thपढ़ो.पंचांग_tfiar = mfspr(SPRN_TFIAR);
		current->thपढ़ो.पंचांग_texasr = mfspr(SPRN_TEXASR);
		current->thपढ़ो.regs->msr &= ~MSR_TM;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Force online to 1 क्रम the sake of old userspace which करोesn't
	 * set it.
	 */
	अगर (!vcpu->arch.online) अणु
		atomic_inc(&vcpu->arch.vcore->online_count);
		vcpu->arch.online = 1;
	पूर्ण

	kvmppc_core_prepare_to_enter(vcpu);

	/* No need to go पूर्णांकo the guest when all we'll करो is come back out */
	अगर (संकेत_pending(current)) अणु
		run->निकास_reason = KVM_EXIT_INTR;
		वापस -EINTR;
	पूर्ण

	kvm = vcpu->kvm;
	atomic_inc(&kvm->arch.vcpus_running);
	/* Order vcpus_running vs. mmu_पढ़ोy, see kvmppc_alloc_reset_hpt */
	smp_mb();

	flush_all_to_thपढ़ो(current);

	/* Save userspace EBB and other रेजिस्टर values */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		ebb_regs[0] = mfspr(SPRN_EBBHR);
		ebb_regs[1] = mfspr(SPRN_EBBRR);
		ebb_regs[2] = mfspr(SPRN_BESCR);
		user_tar = mfspr(SPRN_TAR);
	पूर्ण
	user_vrsave = mfspr(SPRN_VRSAVE);

	vcpu->arch.रुकोp = &vcpu->arch.vcore->रुको;
	vcpu->arch.pgdir = kvm->mm->pgd;
	vcpu->arch.state = KVMPPC_VCPU_BUSY_IN_HOST;

	करो अणु
		/*
		 * The TLB prefetch bug fixup is only in the kvmppc_run_vcpu
		 * path, which also handles hash and dependent thपढ़ोs mode.
		 */
		अगर (kvm->arch.thपढ़ोs_indep && kvm_is_radix(kvm) &&
		    !cpu_has_feature(CPU_FTR_P9_RADIX_PREFETCH_BUG))
			r = kvmhv_run_single_vcpu(vcpu, ~(u64)0,
						  vcpu->arch.vcore->lpcr);
		अन्यथा
			r = kvmppc_run_vcpu(vcpu);

		अगर (run->निकास_reason == KVM_EXIT_PAPR_HCALL &&
		    !(vcpu->arch.shregs.msr & MSR_PR)) अणु
			trace_kvm_hcall_enter(vcpu);
			r = kvmppc_pseries_करो_hcall(vcpu);
			trace_kvm_hcall_निकास(vcpu, r);
			kvmppc_core_prepare_to_enter(vcpu);
		पूर्ण अन्यथा अगर (r == RESUME_PAGE_FAULT) अणु
			srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
			r = kvmppc_book3s_hv_page_fault(vcpu,
				vcpu->arch.fault_dar, vcpu->arch.fault_dsisr);
			srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
		पूर्ण अन्यथा अगर (r == RESUME_PASSTHROUGH) अणु
			अगर (WARN_ON(xics_on_xive()))
				r = H_SUCCESS;
			अन्यथा
				r = kvmppc_xics_rm_complete(vcpu, 0);
		पूर्ण
	पूर्ण जबतक (is_kvmppc_resume_guest(r));

	/* Restore userspace EBB and other रेजिस्टर values */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		mtspr(SPRN_EBBHR, ebb_regs[0]);
		mtspr(SPRN_EBBRR, ebb_regs[1]);
		mtspr(SPRN_BESCR, ebb_regs[2]);
		mtspr(SPRN_TAR, user_tar);
	पूर्ण
	mtspr(SPRN_VRSAVE, user_vrsave);

	vcpu->arch.state = KVMPPC_VCPU_NOTREADY;
	atomic_dec(&kvm->arch.vcpus_running);
	वापस r;
पूर्ण

अटल व्योम kvmppc_add_seg_page_size(काष्ठा kvm_ppc_one_seg_page_size **sps,
				     पूर्णांक shअगरt, पूर्णांक sllp)
अणु
	(*sps)->page_shअगरt = shअगरt;
	(*sps)->slb_enc = sllp;
	(*sps)->enc[0].page_shअगरt = shअगरt;
	(*sps)->enc[0].pte_enc = kvmppc_pgsize_lp_encoding(shअगरt, shअगरt);
	/*
	 * Add 16MB MPSS support (may get filtered out by userspace)
	 */
	अगर (shअगरt != 24) अणु
		पूर्णांक penc = kvmppc_pgsize_lp_encoding(shअगरt, 24);
		अगर (penc != -1) अणु
			(*sps)->enc[1].page_shअगरt = 24;
			(*sps)->enc[1].pte_enc = penc;
		पूर्ण
	पूर्ण
	(*sps)++;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_get_smmu_info_hv(काष्ठा kvm *kvm,
					 काष्ठा kvm_ppc_smmu_info *info)
अणु
	काष्ठा kvm_ppc_one_seg_page_size *sps;

	/*
	 * POWER7, POWER8 and POWER9 all support 32 storage keys क्रम data.
	 * POWER7 करोesn't support keys क्रम inकाष्ठाion accesses,
	 * POWER8 and POWER9 करो.
	 */
	info->data_keys = 32;
	info->instr_keys = cpu_has_feature(CPU_FTR_ARCH_207S) ? 32 : 0;

	/* POWER7, 8 and 9 all have 1T segments and 32-entry SLB */
	info->flags = KVM_PPC_PAGE_SIZES_REAL | KVM_PPC_1T_SEGMENTS;
	info->slb_size = 32;

	/* We only support these sizes क्रम now, and no muti-size segments */
	sps = &info->sps[0];
	kvmppc_add_seg_page_size(&sps, 12, 0);
	kvmppc_add_seg_page_size(&sps, 16, SLB_VSID_L | SLB_VSID_LP_01);
	kvmppc_add_seg_page_size(&sps, 24, SLB_VSID_L);

	/* If running as a nested hypervisor, we करोn't support HPT guests */
	अगर (kvmhv_on_pseries())
		info->flags |= KVM_PPC_NO_HASH;

	वापस 0;
पूर्ण

/*
 * Get (and clear) the dirty memory log क्रम a memory slot.
 */
अटल पूर्णांक kvm_vm_ioctl_get_dirty_log_hv(काष्ठा kvm *kvm,
					 काष्ठा kvm_dirty_log *log)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक i, r;
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ *buf, *p;
	काष्ठा kvm_vcpu *vcpu;

	mutex_lock(&kvm->slots_lock);

	r = -EINVAL;
	अगर (log->slot >= KVM_USER_MEM_SLOTS)
		जाओ out;

	slots = kvm_memslots(kvm);
	memslot = id_to_memslot(slots, log->slot);
	r = -ENOENT;
	अगर (!memslot || !memslot->dirty_biपंचांगap)
		जाओ out;

	/*
	 * Use second half of biपंचांगap area because both HPT and radix
	 * accumulate bits in the first half.
	 */
	n = kvm_dirty_biपंचांगap_bytes(memslot);
	buf = memslot->dirty_biपंचांगap + n / माप(दीर्घ);
	स_रखो(buf, 0, n);

	अगर (kvm_is_radix(kvm))
		r = kvmppc_hv_get_dirty_log_radix(kvm, memslot, buf);
	अन्यथा
		r = kvmppc_hv_get_dirty_log_hpt(kvm, memslot, buf);
	अगर (r)
		जाओ out;

	/*
	 * We accumulate dirty bits in the first half of the
	 * memslot's dirty_biपंचांगap area, क्रम when pages are paged
	 * out or modअगरied by the host directly.  Pick up these
	 * bits and add them to the map.
	 */
	p = memslot->dirty_biपंचांगap;
	क्रम (i = 0; i < n / माप(दीर्घ); ++i)
		buf[i] |= xchg(&p[i], 0);

	/* Harvest dirty bits from VPA and DTL updates */
	/* Note: we never modअगरy the SLB shaकरोw buffer areas */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		spin_lock(&vcpu->arch.vpa_update_lock);
		kvmppc_harvest_vpa_dirty(&vcpu->arch.vpa, memslot, buf);
		kvmppc_harvest_vpa_dirty(&vcpu->arch.dtl, memslot, buf);
		spin_unlock(&vcpu->arch.vpa_update_lock);
	पूर्ण

	r = -EFAULT;
	अगर (copy_to_user(log->dirty_biपंचांगap, buf, n))
		जाओ out;

	r = 0;
out:
	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण

अटल व्योम kvmppc_core_मुक्त_memslot_hv(काष्ठा kvm_memory_slot *slot)
अणु
	vमुक्त(slot->arch.rmap);
	slot->arch.rmap = शून्य;
पूर्ण

अटल पूर्णांक kvmppc_core_prepare_memory_region_hv(काष्ठा kvm *kvm,
					काष्ठा kvm_memory_slot *slot,
					स्थिर काष्ठा kvm_userspace_memory_region *mem,
					क्रमागत kvm_mr_change change)
अणु
	अचिन्हित दीर्घ npages = mem->memory_size >> PAGE_SHIFT;

	अगर (change == KVM_MR_CREATE) अणु
		slot->arch.rmap = vzalloc(array_size(npages,
					  माप(*slot->arch.rmap)));
		अगर (!slot->arch.rmap)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kvmppc_core_commit_memory_region_hv(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				स्थिर काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change)
अणु
	अचिन्हित दीर्घ npages = mem->memory_size >> PAGE_SHIFT;

	/*
	 * If we are making a new memslot, it might make
	 * some address that was previously cached as emulated
	 * MMIO be no दीर्घer emulated MMIO, so invalidate
	 * all the caches of emulated MMIO translations.
	 */
	अगर (npages)
		atomic64_inc(&kvm->arch.mmio_update);

	/*
	 * For change == KVM_MR_MOVE or KVM_MR_DELETE, higher levels
	 * have alपढ़ोy called kvm_arch_flush_shaकरोw_memslot() to
	 * flush shaकरोw mappings.  For KVM_MR_CREATE we have no
	 * previous mappings.  So the only हाल to handle is
	 * KVM_MR_FLAGS_ONLY when the KVM_MEM_LOG_सूचीTY_PAGES bit
	 * has been changed.
	 * For radix guests, we flush on setting KVM_MEM_LOG_सूचीTY_PAGES
	 * to get rid of any THP PTEs in the partition-scoped page tables
	 * so we can track dirtiness at the page level; we flush when
	 * clearing KVM_MEM_LOG_सूचीTY_PAGES so that we can go back to
	 * using THP PTEs.
	 */
	अगर (change == KVM_MR_FLAGS_ONLY && kvm_is_radix(kvm) &&
	    ((new->flags ^ old->flags) & KVM_MEM_LOG_सूचीTY_PAGES))
		kvmppc_radix_flush_memslot(kvm, old);
	/*
	 * If UV hasn't yet called H_SVM_INIT_START, don't रेजिस्टर memslots.
	 */
	अगर (!kvm->arch.secure_guest)
		वापस;

	चयन (change) अणु
	हाल KVM_MR_CREATE:
		/*
		 * @TODO kvmppc_uvmem_memslot_create() can fail and
		 * वापस error. Fix this.
		 */
		kvmppc_uvmem_memslot_create(kvm, new);
		अवरोध;
	हाल KVM_MR_DELETE:
		kvmppc_uvmem_memslot_delete(kvm, old);
		अवरोध;
	शेष:
		/* TODO: Handle KVM_MR_MOVE */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Update LPCR values in kvm->arch and in vcores.
 * Caller must hold kvm->arch.mmu_setup_lock (क्रम mutual exclusion
 * of kvm->arch.lpcr update).
 */
व्योम kvmppc_update_lpcr(काष्ठा kvm *kvm, अचिन्हित दीर्घ lpcr, अचिन्हित दीर्घ mask)
अणु
	दीर्घ पूर्णांक i;
	u32 cores_करोne = 0;

	अगर ((kvm->arch.lpcr & mask) == lpcr)
		वापस;

	kvm->arch.lpcr = (kvm->arch.lpcr & ~mask) | lpcr;

	क्रम (i = 0; i < KVM_MAX_VCORES; ++i) अणु
		काष्ठा kvmppc_vcore *vc = kvm->arch.vcores[i];
		अगर (!vc)
			जारी;

		spin_lock(&vc->lock);
		vc->lpcr = (vc->lpcr & ~mask) | lpcr;
		verअगरy_lpcr(kvm, vc->lpcr);
		spin_unlock(&vc->lock);
		अगर (++cores_करोne >= kvm->arch.online_vcores)
			अवरोध;
	पूर्ण
पूर्ण

व्योम kvmppc_setup_partition_table(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ dw0, dw1;

	अगर (!kvm_is_radix(kvm)) अणु
		/* PS field - page size क्रम VRMA */
		dw0 = ((kvm->arch.vrma_slb_v & SLB_VSID_L) >> 1) |
			((kvm->arch.vrma_slb_v & SLB_VSID_LP) << 1);
		/* HTABSIZE and HTABORG fields */
		dw0 |= kvm->arch.sdr1;

		/* Second dword as set by userspace */
		dw1 = kvm->arch.process_table;
	पूर्ण अन्यथा अणु
		dw0 = PATB_HR | radix__get_tree_size() |
			__pa(kvm->arch.pgtable) | RADIX_PGD_INDEX_SIZE;
		dw1 = PATB_GR | kvm->arch.process_table;
	पूर्ण
	kvmhv_set_ptbl_entry(kvm->arch.lpid, dw0, dw1);
पूर्ण

/*
 * Set up HPT (hashed page table) and RMA (real-mode area).
 * Must be called with kvm->arch.mmu_setup_lock held.
 */
अटल पूर्णांक kvmppc_hv_setup_htab_rma(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक err = 0;
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ hva;
	काष्ठा kvm_memory_slot *memslot;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ lpcr = 0, senc;
	अचिन्हित दीर्घ psize, porder;
	पूर्णांक srcu_idx;

	/* Allocate hashed page table (अगर not करोne alपढ़ोy) and reset it */
	अगर (!kvm->arch.hpt.virt) अणु
		पूर्णांक order = KVM_DEFAULT_HPT_ORDER;
		काष्ठा kvm_hpt_info info;

		err = kvmppc_allocate_hpt(&info, order);
		/* If we get here, it means userspace didn't specअगरy a
		 * size explicitly.  So, try successively smaller
		 * sizes अगर the शेष failed. */
		जबतक ((err == -ENOMEM) && --order >= PPC_MIN_HPT_ORDER)
			err  = kvmppc_allocate_hpt(&info, order);

		अगर (err < 0) अणु
			pr_err("KVM: Couldn't alloc HPT\n");
			जाओ out;
		पूर्ण

		kvmppc_set_hpt(kvm, &info);
	पूर्ण

	/* Look up the memslot क्रम guest physical address 0 */
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	memslot = gfn_to_memslot(kvm, 0);

	/* We must have some memory at 0 by now */
	err = -EINVAL;
	अगर (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		जाओ out_srcu;

	/* Look up the VMA क्रम the start of this memory slot */
	hva = memslot->userspace_addr;
	mmap_पढ़ो_lock(kvm->mm);
	vma = find_vma(kvm->mm, hva);
	अगर (!vma || vma->vm_start > hva || (vma->vm_flags & VM_IO))
		जाओ up_out;

	psize = vma_kernel_pagesize(vma);

	mmap_पढ़ो_unlock(kvm->mm);

	/* We can handle 4k, 64k or 16M pages in the VRMA */
	अगर (psize >= 0x1000000)
		psize = 0x1000000;
	अन्यथा अगर (psize >= 0x10000)
		psize = 0x10000;
	अन्यथा
		psize = 0x1000;
	porder = __ilog2(psize);

	senc = slb_pgsize_encoding(psize);
	kvm->arch.vrma_slb_v = senc | SLB_VSID_B_1T |
		(VRMA_VSID << SLB_VSID_SHIFT_1T);
	/* Create HPTEs in the hash page table क्रम the VRMA */
	kvmppc_map_vrma(vcpu, memslot, porder);

	/* Update VRMASD field in the LPCR */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		/* the -4 is to account क्रम senc values starting at 0x10 */
		lpcr = senc << (LPCR_VRMASD_SH - 4);
		kvmppc_update_lpcr(kvm, lpcr, LPCR_VRMASD);
	पूर्ण

	/* Order updates to kvm->arch.lpcr etc. vs. mmu_पढ़ोy */
	smp_wmb();
	err = 0;
 out_srcu:
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
 out:
	वापस err;

 up_out:
	mmap_पढ़ो_unlock(kvm->mm);
	जाओ out_srcu;
पूर्ण

/*
 * Must be called with kvm->arch.mmu_setup_lock held and
 * mmu_पढ़ोy = 0 and no vcpus running.
 */
पूर्णांक kvmppc_चयन_mmu_to_hpt(काष्ठा kvm *kvm)
अणु
	अगर (nesting_enabled(kvm))
		kvmhv_release_all_nested(kvm);
	kvmppc_rmap_reset(kvm);
	kvm->arch.process_table = 0;
	/* Mutual exclusion with kvm_unmap_gfn_range etc. */
	spin_lock(&kvm->mmu_lock);
	kvm->arch.radix = 0;
	spin_unlock(&kvm->mmu_lock);
	kvmppc_मुक्त_radix(kvm);
	kvmppc_update_lpcr(kvm, LPCR_VPM1,
			   LPCR_VPM1 | LPCR_UPRT | LPCR_GTSE | LPCR_HR);
	वापस 0;
पूर्ण

/*
 * Must be called with kvm->arch.mmu_setup_lock held and
 * mmu_पढ़ोy = 0 and no vcpus running.
 */
पूर्णांक kvmppc_चयन_mmu_to_radix(काष्ठा kvm *kvm)
अणु
	पूर्णांक err;

	err = kvmppc_init_vm_radix(kvm);
	अगर (err)
		वापस err;
	kvmppc_rmap_reset(kvm);
	/* Mutual exclusion with kvm_unmap_gfn_range etc. */
	spin_lock(&kvm->mmu_lock);
	kvm->arch.radix = 1;
	spin_unlock(&kvm->mmu_lock);
	kvmppc_मुक्त_hpt(&kvm->arch.hpt);
	kvmppc_update_lpcr(kvm, LPCR_UPRT | LPCR_GTSE | LPCR_HR,
			   LPCR_VPM1 | LPCR_UPRT | LPCR_GTSE | LPCR_HR);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_KVM_XICS
/*
 * Allocate a per-core काष्ठाure क्रम managing state about which cores are
 * running in the host versus the guest and क्रम exchanging data between
 * real mode KVM and CPU running in the host.
 * This is only करोne क्रम the first VM.
 * The allocated काष्ठाure stays even अगर all VMs have stopped.
 * It is only मुक्तd when the kvm-hv module is unloaded.
 * It's OK for this routine to fail, we just don't support host
 * core operations like redirecting H_IPI wakeups.
 */
व्योम kvmppc_alloc_host_rm_ops(व्योम)
अणु
	काष्ठा kvmppc_host_rm_ops *ops;
	अचिन्हित दीर्घ l_ops;
	पूर्णांक cpu, core;
	पूर्णांक size;

	/* Not the first समय here ? */
	अगर (kvmppc_host_rm_ops_hv != शून्य)
		वापस;

	ops = kzalloc(माप(काष्ठा kvmppc_host_rm_ops), GFP_KERNEL);
	अगर (!ops)
		वापस;

	size = cpu_nr_cores() * माप(काष्ठा kvmppc_host_rm_core);
	ops->rm_core = kzalloc(size, GFP_KERNEL);

	अगर (!ops->rm_core) अणु
		kमुक्त(ops);
		वापस;
	पूर्ण

	cpus_पढ़ो_lock();

	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu += thपढ़ोs_per_core) अणु
		अगर (!cpu_online(cpu))
			जारी;

		core = cpu >> thपढ़ोs_shअगरt;
		ops->rm_core[core].rm_state.in_host = 1;
	पूर्ण

	ops->vcpu_kick = kvmppc_fast_vcpu_kick_hv;

	/*
	 * Make the contents of the kvmppc_host_rm_ops काष्ठाure visible
	 * to other CPUs beक्रमe we assign it to the global variable.
	 * Do an atomic assignment (no locks used here), but अगर someone
	 * beats us to it, just मुक्त our copy and वापस.
	 */
	smp_wmb();
	l_ops = (अचिन्हित दीर्घ) ops;

	अगर (cmpxchg64((अचिन्हित दीर्घ *)&kvmppc_host_rm_ops_hv, 0, l_ops)) अणु
		cpus_पढ़ो_unlock();
		kमुक्त(ops->rm_core);
		kमुक्त(ops);
		वापस;
	पूर्ण

	cpuhp_setup_state_nocalls_cpuslocked(CPUHP_KVM_PPC_BOOK3S_PREPARE,
					     "ppc/kvm_book3s:prepare",
					     kvmppc_set_host_core,
					     kvmppc_clear_host_core);
	cpus_पढ़ो_unlock();
पूर्ण

व्योम kvmppc_मुक्त_host_rm_ops(व्योम)
अणु
	अगर (kvmppc_host_rm_ops_hv) अणु
		cpuhp_हटाओ_state_nocalls(CPUHP_KVM_PPC_BOOK3S_PREPARE);
		kमुक्त(kvmppc_host_rm_ops_hv->rm_core);
		kमुक्त(kvmppc_host_rm_ops_hv);
		kvmppc_host_rm_ops_hv = शून्य;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kvmppc_core_init_vm_hv(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ lpcr, lpid;
	अक्षर buf[32];
	पूर्णांक ret;

	mutex_init(&kvm->arch.uvmem_lock);
	INIT_LIST_HEAD(&kvm->arch.uvmem_pfns);
	mutex_init(&kvm->arch.mmu_setup_lock);

	/* Allocate the guest's logical partition ID */

	lpid = kvmppc_alloc_lpid();
	अगर ((दीर्घ)lpid < 0)
		वापस -ENOMEM;
	kvm->arch.lpid = lpid;

	kvmppc_alloc_host_rm_ops();

	kvmhv_vm_nested_init(kvm);

	/*
	 * Since we करोn't flush the TLB when tearing करोwn a VM,
	 * and this lpid might have previously been used,
	 * make sure we flush on each core beक्रमe running the new VM.
	 * On POWER9, the tlbie in mmu_partition_table_set_entry()
	 * करोes this flush क्रम us.
	 */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		cpumask_setall(&kvm->arch.need_tlb_flush);

	/* Start out with the शेष set of hcalls enabled */
	स_नकल(kvm->arch.enabled_hcalls, शेष_enabled_hcalls,
	       माप(kvm->arch.enabled_hcalls));

	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		kvm->arch.host_sdr1 = mfspr(SPRN_SDR1);

	/* Init LPCR क्रम भव RMA mode */
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		kvm->arch.host_lpid = mfspr(SPRN_LPID);
		kvm->arch.host_lpcr = lpcr = mfspr(SPRN_LPCR);
		lpcr &= LPCR_PECE | LPCR_LPES;
	पूर्ण अन्यथा अणु
		lpcr = 0;
	पूर्ण
	lpcr |= (4UL << LPCR_DPFD_SH) | LPCR_HDICE |
		LPCR_VPM0 | LPCR_VPM1;
	kvm->arch.vrma_slb_v = SLB_VSID_B_1T |
		(VRMA_VSID << SLB_VSID_SHIFT_1T);
	/* On POWER8 turn on online bit to enable PURR/SPURR */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		lpcr |= LPCR_ONL;
	/*
	 * On POWER9, VPM0 bit is reserved (VPM0=1 behaviour is assumed)
	 * Set HVICE bit to enable hypervisor भवization पूर्णांकerrupts.
	 * Set HEIC to prevent OS पूर्णांकerrupts to go to hypervisor (should
	 * be unnecessary but better safe than sorry in हाल we re-enable
	 * EE in HV mode with this LPCR still set)
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		lpcr &= ~LPCR_VPM0;
		lpcr |= LPCR_HVICE | LPCR_HEIC;

		/*
		 * If xive is enabled, we route 0x500 पूर्णांकerrupts directly
		 * to the guest.
		 */
		अगर (xics_on_xive())
			lpcr |= LPCR_LPES;
	पूर्ण

	/*
	 * If the host uses radix, the guest starts out as radix.
	 */
	अगर (radix_enabled()) अणु
		kvm->arch.radix = 1;
		kvm->arch.mmu_पढ़ोy = 1;
		lpcr &= ~LPCR_VPM1;
		lpcr |= LPCR_UPRT | LPCR_GTSE | LPCR_HR;
		ret = kvmppc_init_vm_radix(kvm);
		अगर (ret) अणु
			kvmppc_मुक्त_lpid(kvm->arch.lpid);
			वापस ret;
		पूर्ण
		kvmppc_setup_partition_table(kvm);
	पूर्ण

	verअगरy_lpcr(kvm, lpcr);
	kvm->arch.lpcr = lpcr;

	/* Initialization क्रम future HPT resizes */
	kvm->arch.resize_hpt = शून्य;

	/*
	 * Work out how many sets the TLB has, क्रम the use of
	 * the TLB invalidation loop in book3s_hv_rmhandlers.S.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		/*
		 * P10 will flush all the congruence class with a single tlbiel
		 */
		kvm->arch.tlb_sets = 1;
	पूर्ण अन्यथा अगर (radix_enabled())
		kvm->arch.tlb_sets = POWER9_TLB_SETS_RADIX;	/* 128 */
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		kvm->arch.tlb_sets = POWER9_TLB_SETS_HASH;	/* 256 */
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		kvm->arch.tlb_sets = POWER8_TLB_SETS;		/* 512 */
	अन्यथा
		kvm->arch.tlb_sets = POWER7_TLB_SETS;		/* 128 */

	/*
	 * Track that we now have a HV mode VM active. This blocks secondary
	 * CPU thपढ़ोs from coming online.
	 * On POWER9, we only need to करो this अगर the "indep_threads_mode"
	 * module parameter has been set to N.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (!indep_thपढ़ोs_mode && !cpu_has_feature(CPU_FTR_HVMODE)) अणु
			pr_warn("KVM: Ignoring indep_threads_mode=N in nested hypervisor\n");
			kvm->arch.thपढ़ोs_indep = true;
		पूर्ण अन्यथा अणु
			kvm->arch.thपढ़ोs_indep = indep_thपढ़ोs_mode;
		पूर्ण
	पूर्ण
	अगर (!kvm->arch.thपढ़ोs_indep)
		kvm_hv_vm_activated();

	/*
	 * Initialize smt_mode depending on processor.
	 * POWER8 and earlier have to use "strict" thपढ़ोing, where
	 * all vCPUs in a vcore have to run on the same (sub)core,
	 * whereas on POWER9 the thपढ़ोs can each run a dअगरferent
	 * guest.
	 */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		kvm->arch.smt_mode = thपढ़ोs_per_subcore;
	अन्यथा
		kvm->arch.smt_mode = 1;
	kvm->arch.emul_smt_mode = 1;

	/*
	 * Create a debugfs directory क्रम the VM
	 */
	snम_लिखो(buf, माप(buf), "vm%d", current->pid);
	kvm->arch.debugfs_dir = debugfs_create_dir(buf, kvm_debugfs_dir);
	kvmppc_mmu_debugfs_init(kvm);
	अगर (radix_enabled())
		kvmhv_radix_debugfs_init(kvm);

	वापस 0;
पूर्ण

अटल व्योम kvmppc_मुक्त_vcores(काष्ठा kvm *kvm)
अणु
	दीर्घ पूर्णांक i;

	क्रम (i = 0; i < KVM_MAX_VCORES; ++i)
		kमुक्त(kvm->arch.vcores[i]);
	kvm->arch.online_vcores = 0;
पूर्ण

अटल व्योम kvmppc_core_destroy_vm_hv(काष्ठा kvm *kvm)
अणु
	debugfs_हटाओ_recursive(kvm->arch.debugfs_dir);

	अगर (!kvm->arch.thपढ़ोs_indep)
		kvm_hv_vm_deactivated();

	kvmppc_मुक्त_vcores(kvm);


	अगर (kvm_is_radix(kvm))
		kvmppc_मुक्त_radix(kvm);
	अन्यथा
		kvmppc_मुक्त_hpt(&kvm->arch.hpt);

	/* Perक्रमm global invalidation and वापस lpid to the pool */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (nesting_enabled(kvm))
			kvmhv_release_all_nested(kvm);
		kvm->arch.process_table = 0;
		अगर (kvm->arch.secure_guest)
			uv_svm_terminate(kvm->arch.lpid);
		kvmhv_set_ptbl_entry(kvm->arch.lpid, 0, 0);
	पूर्ण

	kvmppc_मुक्त_lpid(kvm->arch.lpid);

	kvmppc_मुक्त_pimap(kvm);
पूर्ण

/* We करोn't need to emulate any privileged inकाष्ठाions or dcbz */
अटल पूर्णांक kvmppc_core_emulate_op_hv(काष्ठा kvm_vcpu *vcpu,
				     अचिन्हित पूर्णांक inst, पूर्णांक *advance)
अणु
	वापस EMULATE_FAIL;
पूर्ण

अटल पूर्णांक kvmppc_core_emulate_mtspr_hv(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn,
					uदीर्घ spr_val)
अणु
	वापस EMULATE_FAIL;
पूर्ण

अटल पूर्णांक kvmppc_core_emulate_mfspr_hv(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn,
					uदीर्घ *spr_val)
अणु
	वापस EMULATE_FAIL;
पूर्ण

अटल पूर्णांक kvmppc_core_check_processor_compat_hv(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_HVMODE) &&
	    cpu_has_feature(CPU_FTR_ARCH_206))
		वापस 0;

	/* POWER9 in radix mode is capable of being a nested hypervisor. */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300) && radix_enabled())
		वापस 0;

	वापस -EIO;
पूर्ण

#अगर_घोषित CONFIG_KVM_XICS

व्योम kvmppc_मुक्त_pimap(काष्ठा kvm *kvm)
अणु
	kमुक्त(kvm->arch.pimap);
पूर्ण

अटल काष्ठा kvmppc_passthru_irqmap *kvmppc_alloc_pimap(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा kvmppc_passthru_irqmap), GFP_KERNEL);
पूर्ण

अटल पूर्णांक kvmppc_set_passthru_irq(काष्ठा kvm *kvm, पूर्णांक host_irq, पूर्णांक guest_gsi)
अणु
	काष्ठा irq_desc *desc;
	काष्ठा kvmppc_irq_map *irq_map;
	काष्ठा kvmppc_passthru_irqmap *pimap;
	काष्ठा irq_chip *chip;
	पूर्णांक i, rc = 0;

	अगर (!kvm_irq_bypass)
		वापस 1;

	desc = irq_to_desc(host_irq);
	अगर (!desc)
		वापस -EIO;

	mutex_lock(&kvm->lock);

	pimap = kvm->arch.pimap;
	अगर (pimap == शून्य) अणु
		/* First call, allocate काष्ठाure to hold IRQ map */
		pimap = kvmppc_alloc_pimap();
		अगर (pimap == शून्य) अणु
			mutex_unlock(&kvm->lock);
			वापस -ENOMEM;
		पूर्ण
		kvm->arch.pimap = pimap;
	पूर्ण

	/*
	 * For now, we only support पूर्णांकerrupts क्रम which the EOI operation
	 * is an OPAL call followed by a ग_लिखो to XIRR, since that's
	 * what our real-mode EOI code करोes, or a XIVE पूर्णांकerrupt
	 */
	chip = irq_data_get_irq_chip(&desc->irq_data);
	अगर (!chip || !(is_pnv_opal_msi(chip) || is_xive_irq(chip))) अणु
		pr_warn("kvmppc_set_passthru_irq_hv: Could not assign IRQ map for (%d,%d)\n",
			host_irq, guest_gsi);
		mutex_unlock(&kvm->lock);
		वापस -ENOENT;
	पूर्ण

	/*
	 * See अगर we alपढ़ोy have an entry क्रम this guest IRQ number.
	 * If it's mapped to a hardware IRQ number, that's an error,
	 * otherwise re-use this entry.
	 */
	क्रम (i = 0; i < pimap->n_mapped; i++) अणु
		अगर (guest_gsi == pimap->mapped[i].v_hwirq) अणु
			अगर (pimap->mapped[i].r_hwirq) अणु
				mutex_unlock(&kvm->lock);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == KVMPPC_PIRQ_MAPPED) अणु
		mutex_unlock(&kvm->lock);
		वापस -EAGAIN;		/* table is full */
	पूर्ण

	irq_map = &pimap->mapped[i];

	irq_map->v_hwirq = guest_gsi;
	irq_map->desc = desc;

	/*
	 * Order the above two stores beक्रमe the next to serialize with
	 * the KVM real mode handler.
	 */
	smp_wmb();
	irq_map->r_hwirq = desc->irq_data.hwirq;

	अगर (i == pimap->n_mapped)
		pimap->n_mapped++;

	अगर (xics_on_xive())
		rc = kvmppc_xive_set_mapped(kvm, guest_gsi, desc);
	अन्यथा
		kvmppc_xics_set_mapped(kvm, guest_gsi, desc->irq_data.hwirq);
	अगर (rc)
		irq_map->r_hwirq = 0;

	mutex_unlock(&kvm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_clr_passthru_irq(काष्ठा kvm *kvm, पूर्णांक host_irq, पूर्णांक guest_gsi)
अणु
	काष्ठा irq_desc *desc;
	काष्ठा kvmppc_passthru_irqmap *pimap;
	पूर्णांक i, rc = 0;

	अगर (!kvm_irq_bypass)
		वापस 0;

	desc = irq_to_desc(host_irq);
	अगर (!desc)
		वापस -EIO;

	mutex_lock(&kvm->lock);
	अगर (!kvm->arch.pimap)
		जाओ unlock;

	pimap = kvm->arch.pimap;

	क्रम (i = 0; i < pimap->n_mapped; i++) अणु
		अगर (guest_gsi == pimap->mapped[i].v_hwirq)
			अवरोध;
	पूर्ण

	अगर (i == pimap->n_mapped) अणु
		mutex_unlock(&kvm->lock);
		वापस -ENODEV;
	पूर्ण

	अगर (xics_on_xive())
		rc = kvmppc_xive_clr_mapped(kvm, guest_gsi, pimap->mapped[i].desc);
	अन्यथा
		kvmppc_xics_clr_mapped(kvm, guest_gsi, pimap->mapped[i].r_hwirq);

	/* invalidate the entry (what करो करो on error from the above ?) */
	pimap->mapped[i].r_hwirq = 0;

	/*
	 * We करोn't मुक्त this काष्ठाure even when the count goes to
	 * zero. The काष्ठाure is मुक्तd when we destroy the VM.
	 */
 unlock:
	mutex_unlock(&kvm->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक kvmppc_irq_bypass_add_producer_hv(काष्ठा irq_bypass_consumer *cons,
					     काष्ठा irq_bypass_producer *prod)
अणु
	पूर्णांक ret = 0;
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	irqfd->producer = prod;

	ret = kvmppc_set_passthru_irq(irqfd->kvm, prod->irq, irqfd->gsi);
	अगर (ret)
		pr_info("kvmppc_set_passthru_irq (irq %d, gsi %d) fails: %d\n",
			prod->irq, irqfd->gsi, ret);

	वापस ret;
पूर्ण

अटल व्योम kvmppc_irq_bypass_del_producer_hv(काष्ठा irq_bypass_consumer *cons,
					      काष्ठा irq_bypass_producer *prod)
अणु
	पूर्णांक ret;
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	irqfd->producer = शून्य;

	/*
	 * When producer of consumer is unरेजिस्टरed, we change back to
	 * शेष बाह्यal पूर्णांकerrupt handling mode - KVM real mode
	 * will चयन back to host.
	 */
	ret = kvmppc_clr_passthru_irq(irqfd->kvm, prod->irq, irqfd->gsi);
	अगर (ret)
		pr_warn("kvmppc_clr_passthru_irq (irq %d, gsi %d) fails: %d\n",
			prod->irq, irqfd->gsi, ret);
पूर्ण
#पूर्ण_अगर

अटल दीर्घ kvm_arch_vm_ioctl_hv(काष्ठा file *filp,
				 अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm __maybe_unused = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	दीर्घ r;

	चयन (ioctl) अणु

	हाल KVM_PPC_ALLOCATE_HTAB: अणु
		u32 htab_order;

		/* If we're a nested hypervisor, we currently only support radix */
		अगर (kvmhv_on_pseries()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		r = -EFAULT;
		अगर (get_user(htab_order, (u32 __user *)argp))
			अवरोध;
		r = kvmppc_alloc_reset_hpt(kvm, htab_order);
		अगर (r)
			अवरोध;
		r = 0;
		अवरोध;
	पूर्ण

	हाल KVM_PPC_GET_HTAB_FD: अणु
		काष्ठा kvm_get_htab_fd ghf;

		r = -EFAULT;
		अगर (copy_from_user(&ghf, argp, माप(ghf)))
			अवरोध;
		r = kvm_vm_ioctl_get_htab_fd(kvm, &ghf);
		अवरोध;
	पूर्ण

	हाल KVM_PPC_RESIZE_HPT_PREPARE: अणु
		काष्ठा kvm_ppc_resize_hpt rhpt;

		r = -EFAULT;
		अगर (copy_from_user(&rhpt, argp, माप(rhpt)))
			अवरोध;

		r = kvm_vm_ioctl_resize_hpt_prepare(kvm, &rhpt);
		अवरोध;
	पूर्ण

	हाल KVM_PPC_RESIZE_HPT_COMMIT: अणु
		काष्ठा kvm_ppc_resize_hpt rhpt;

		r = -EFAULT;
		अगर (copy_from_user(&rhpt, argp, माप(rhpt)))
			अवरोध;

		r = kvm_vm_ioctl_resize_hpt_commit(kvm, &rhpt);
		अवरोध;
	पूर्ण

	शेष:
		r = -ENOTTY;
	पूर्ण

	वापस r;
पूर्ण

/*
 * List of hcall numbers to enable by शेष.
 * For compatibility with old userspace, we enable by शेष
 * all hcalls that were implemented beक्रमe the hcall-enabling
 * facility was added.  Note this list should not include H_RTAS.
 */
अटल अचिन्हित पूर्णांक शेष_hcall_list[] = अणु
	H_REMOVE,
	H_ENTER,
	H_READ,
	H_PROTECT,
	H_BULK_REMOVE,
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	H_GET_TCE,
	H_PUT_TCE,
#पूर्ण_अगर
	H_SET_DABR,
	H_SET_XDABR,
	H_CEDE,
	H_PROD,
	H_CONFER,
	H_REGISTER_VPA,
#अगर_घोषित CONFIG_KVM_XICS
	H_EOI,
	H_CPPR,
	H_IPI,
	H_IPOLL,
	H_XIRR,
	H_XIRR_X,
#पूर्ण_अगर
	0
पूर्ण;

अटल व्योम init_शेष_hcalls(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक hcall;

	क्रम (i = 0; शेष_hcall_list[i]; ++i) अणु
		hcall = शेष_hcall_list[i];
		WARN_ON(!kvmppc_hcall_impl_hv(hcall));
		__set_bit(hcall / 4, शेष_enabled_hcalls);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmhv_configure_mmu(काष्ठा kvm *kvm, काष्ठा kvm_ppc_mmuv3_cfg *cfg)
अणु
	अचिन्हित दीर्घ lpcr;
	पूर्णांक radix;
	पूर्णांक err;

	/* If not on a POWER9, reject it */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		वापस -ENODEV;

	/* If any unknown flags set, reject it */
	अगर (cfg->flags & ~(KVM_PPC_MMUV3_RADIX | KVM_PPC_MMUV3_GTSE))
		वापस -EINVAL;

	/* GR (guest radix) bit in process_table field must match */
	radix = !!(cfg->flags & KVM_PPC_MMUV3_RADIX);
	अगर (!!(cfg->process_table & PATB_GR) != radix)
		वापस -EINVAL;

	/* Process table size field must be reasonable, i.e. <= 24 */
	अगर ((cfg->process_table & PRTS_MASK) > 24)
		वापस -EINVAL;

	/* We can change a guest to/from radix now, अगर the host is radix */
	अगर (radix && !radix_enabled())
		वापस -EINVAL;

	/* If we're a nested hypervisor, we currently only support radix */
	अगर (kvmhv_on_pseries() && !radix)
		वापस -EINVAL;

	mutex_lock(&kvm->arch.mmu_setup_lock);
	अगर (radix != kvm_is_radix(kvm)) अणु
		अगर (kvm->arch.mmu_पढ़ोy) अणु
			kvm->arch.mmu_पढ़ोy = 0;
			/* order mmu_पढ़ोy vs. vcpus_running */
			smp_mb();
			अगर (atomic_पढ़ो(&kvm->arch.vcpus_running)) अणु
				kvm->arch.mmu_पढ़ोy = 1;
				err = -EBUSY;
				जाओ out_unlock;
			पूर्ण
		पूर्ण
		अगर (radix)
			err = kvmppc_चयन_mmu_to_radix(kvm);
		अन्यथा
			err = kvmppc_चयन_mmu_to_hpt(kvm);
		अगर (err)
			जाओ out_unlock;
	पूर्ण

	kvm->arch.process_table = cfg->process_table;
	kvmppc_setup_partition_table(kvm);

	lpcr = (cfg->flags & KVM_PPC_MMUV3_GTSE) ? LPCR_GTSE : 0;
	kvmppc_update_lpcr(kvm, lpcr, LPCR_GTSE);
	err = 0;

 out_unlock:
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	वापस err;
पूर्ण

अटल पूर्णांक kvmhv_enable_nested(काष्ठा kvm *kvm)
अणु
	अगर (!nested)
		वापस -EPERM;
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300) || no_mixing_hpt_and_radix)
		वापस -ENODEV;

	/* kvm == शून्य means the caller is testing अगर the capability exists */
	अगर (kvm)
		kvm->arch.nested_enable = true;
	वापस 0;
पूर्ण

अटल पूर्णांक kvmhv_load_from_eaddr(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, व्योम *ptr,
				 पूर्णांक size)
अणु
	पूर्णांक rc = -EINVAL;

	अगर (kvmhv_vcpu_is_radix(vcpu)) अणु
		rc = kvmhv_copy_from_guest_radix(vcpu, *eaddr, ptr, size);

		अगर (rc > 0)
			rc = -EINVAL;
	पूर्ण

	/* For now quadrants are the only way to access nested guest memory */
	अगर (rc && vcpu->arch.nested)
		rc = -EAGAIN;

	वापस rc;
पूर्ण

अटल पूर्णांक kvmhv_store_to_eaddr(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, व्योम *ptr,
				पूर्णांक size)
अणु
	पूर्णांक rc = -EINVAL;

	अगर (kvmhv_vcpu_is_radix(vcpu)) अणु
		rc = kvmhv_copy_to_guest_radix(vcpu, *eaddr, ptr, size);

		अगर (rc > 0)
			rc = -EINVAL;
	पूर्ण

	/* For now quadrants are the only way to access nested guest memory */
	अगर (rc && vcpu->arch.nested)
		rc = -EAGAIN;

	वापस rc;
पूर्ण

अटल व्योम unpin_vpa_reset(काष्ठा kvm *kvm, काष्ठा kvmppc_vpa *vpa)
अणु
	unpin_vpa(kvm, vpa);
	vpa->gpa = 0;
	vpa->pinned_addr = शून्य;
	vpa->dirty = false;
	vpa->update_pending = 0;
पूर्ण

/*
 * Enable a guest to become a secure VM, or test whether
 * that could be enabled.
 * Called when the KVM_CAP_PPC_SECURE_GUEST capability is
 * tested (kvm == शून्य) or enabled (kvm != शून्य).
 */
अटल पूर्णांक kvmhv_enable_svm(काष्ठा kvm *kvm)
अणु
	अगर (!kvmppc_uvmem_available())
		वापस -EINVAL;
	अगर (kvm)
		kvm->arch.svm_enabled = 1;
	वापस 0;
पूर्ण

/*
 *  IOCTL handler to turn off secure mode of guest
 *
 * - Release all device pages
 * - Issue ucall to terminate the guest on the UV side
 * - Unpin the VPA pages.
 * - Reinit the partition scoped page tables
 */
अटल पूर्णांक kvmhv_svm_off(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक mmu_was_पढ़ोy;
	पूर्णांक srcu_idx;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!(kvm->arch.secure_guest & KVMPPC_SECURE_INIT_START))
		वापस ret;

	mutex_lock(&kvm->arch.mmu_setup_lock);
	mmu_was_पढ़ोy = kvm->arch.mmu_पढ़ोy;
	अगर (kvm->arch.mmu_पढ़ोy) अणु
		kvm->arch.mmu_पढ़ोy = 0;
		/* order mmu_पढ़ोy vs. vcpus_running */
		smp_mb();
		अगर (atomic_पढ़ो(&kvm->arch.vcpus_running)) अणु
			kvm->arch.mmu_पढ़ोy = 1;
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) अणु
		काष्ठा kvm_memory_slot *memslot;
		काष्ठा kvm_memslots *slots = __kvm_memslots(kvm, i);

		अगर (!slots)
			जारी;

		kvm_क्रम_each_memslot(memslot, slots) अणु
			kvmppc_uvmem_drop_pages(memslot, kvm, true);
			uv_unरेजिस्टर_mem_slot(kvm->arch.lpid, memslot->id);
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	ret = uv_svm_terminate(kvm->arch.lpid);
	अगर (ret != U_SUCCESS) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * When secure guest is reset, all the guest pages are sent
	 * to UV via UV_PAGE_IN beक्रमe the non-boot vcpus get a
	 * chance to run and unpin their VPA pages. Unpinning of all
	 * VPA pages is करोne here explicitly so that VPA pages
	 * can be migrated to the secure side.
	 *
	 * This is required to क्रम the secure SMP guest to reboot
	 * correctly.
	 */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		spin_lock(&vcpu->arch.vpa_update_lock);
		unpin_vpa_reset(kvm, &vcpu->arch.dtl);
		unpin_vpa_reset(kvm, &vcpu->arch.slb_shaकरोw);
		unpin_vpa_reset(kvm, &vcpu->arch.vpa);
		spin_unlock(&vcpu->arch.vpa_update_lock);
	पूर्ण

	kvmppc_setup_partition_table(kvm);
	kvm->arch.secure_guest = 0;
	kvm->arch.mmu_पढ़ोy = mmu_was_पढ़ोy;
out:
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक kvmhv_enable_dawr1(काष्ठा kvm *kvm)
अणु
	अगर (!cpu_has_feature(CPU_FTR_DAWR1))
		वापस -ENODEV;

	/* kvm == शून्य means the caller is testing अगर the capability exists */
	अगर (kvm)
		kvm->arch.dawr1_enabled = true;
	वापस 0;
पूर्ण

अटल bool kvmppc_hash_v3_possible(व्योम)
अणु
	अगर (radix_enabled() && no_mixing_hpt_and_radix)
		वापस false;

	वापस cpu_has_feature(CPU_FTR_ARCH_300) &&
		cpu_has_feature(CPU_FTR_HVMODE);
पूर्ण

अटल काष्ठा kvmppc_ops kvm_ops_hv = अणु
	.get_sregs = kvm_arch_vcpu_ioctl_get_sregs_hv,
	.set_sregs = kvm_arch_vcpu_ioctl_set_sregs_hv,
	.get_one_reg = kvmppc_get_one_reg_hv,
	.set_one_reg = kvmppc_set_one_reg_hv,
	.vcpu_load   = kvmppc_core_vcpu_load_hv,
	.vcpu_put    = kvmppc_core_vcpu_put_hv,
	.inject_पूर्णांकerrupt = kvmppc_inject_पूर्णांकerrupt_hv,
	.set_msr     = kvmppc_set_msr_hv,
	.vcpu_run    = kvmppc_vcpu_run_hv,
	.vcpu_create = kvmppc_core_vcpu_create_hv,
	.vcpu_मुक्त   = kvmppc_core_vcpu_मुक्त_hv,
	.check_requests = kvmppc_core_check_requests_hv,
	.get_dirty_log  = kvm_vm_ioctl_get_dirty_log_hv,
	.flush_memslot  = kvmppc_core_flush_memslot_hv,
	.prepare_memory_region = kvmppc_core_prepare_memory_region_hv,
	.commit_memory_region  = kvmppc_core_commit_memory_region_hv,
	.unmap_gfn_range = kvm_unmap_gfn_range_hv,
	.age_gfn = kvm_age_gfn_hv,
	.test_age_gfn = kvm_test_age_gfn_hv,
	.set_spte_gfn = kvm_set_spte_gfn_hv,
	.मुक्त_memslot = kvmppc_core_मुक्त_memslot_hv,
	.init_vm =  kvmppc_core_init_vm_hv,
	.destroy_vm = kvmppc_core_destroy_vm_hv,
	.get_smmu_info = kvm_vm_ioctl_get_smmu_info_hv,
	.emulate_op = kvmppc_core_emulate_op_hv,
	.emulate_mtspr = kvmppc_core_emulate_mtspr_hv,
	.emulate_mfspr = kvmppc_core_emulate_mfspr_hv,
	.fast_vcpu_kick = kvmppc_fast_vcpu_kick_hv,
	.arch_vm_ioctl  = kvm_arch_vm_ioctl_hv,
	.hcall_implemented = kvmppc_hcall_impl_hv,
#अगर_घोषित CONFIG_KVM_XICS
	.irq_bypass_add_producer = kvmppc_irq_bypass_add_producer_hv,
	.irq_bypass_del_producer = kvmppc_irq_bypass_del_producer_hv,
#पूर्ण_अगर
	.configure_mmu = kvmhv_configure_mmu,
	.get_rmmu_info = kvmhv_get_rmmu_info,
	.set_smt_mode = kvmhv_set_smt_mode,
	.enable_nested = kvmhv_enable_nested,
	.load_from_eaddr = kvmhv_load_from_eaddr,
	.store_to_eaddr = kvmhv_store_to_eaddr,
	.enable_svm = kvmhv_enable_svm,
	.svm_off = kvmhv_svm_off,
	.enable_dawr1 = kvmhv_enable_dawr1,
	.hash_v3_possible = kvmppc_hash_v3_possible,
पूर्ण;

अटल पूर्णांक kvm_init_subcore_biपंचांगap(व्योम)
अणु
	पूर्णांक i, j;
	पूर्णांक nr_cores = cpu_nr_cores();
	काष्ठा sibling_subcore_state *sibling_subcore_state;

	क्रम (i = 0; i < nr_cores; i++) अणु
		पूर्णांक first_cpu = i * thपढ़ोs_per_core;
		पूर्णांक node = cpu_to_node(first_cpu);

		/* Ignore अगर it is alपढ़ोy allocated. */
		अगर (paca_ptrs[first_cpu]->sibling_subcore_state)
			जारी;

		sibling_subcore_state =
			kzalloc_node(माप(काष्ठा sibling_subcore_state),
							GFP_KERNEL, node);
		अगर (!sibling_subcore_state)
			वापस -ENOMEM;


		क्रम (j = 0; j < thपढ़ोs_per_core; j++) अणु
			पूर्णांक cpu = first_cpu + j;

			paca_ptrs[cpu]->sibling_subcore_state =
						sibling_subcore_state;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_radix_possible(व्योम)
अणु
	वापस cpu_has_feature(CPU_FTR_ARCH_300) && radix_enabled();
पूर्ण

अटल पूर्णांक kvmppc_book3s_init_hv(व्योम)
अणु
	पूर्णांक r;

	अगर (!tlbie_capable) अणु
		pr_err("KVM-HV: Host does not support TLBIE\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * FIXME!! Do we need to check on all cpus ?
	 */
	r = kvmppc_core_check_processor_compat_hv();
	अगर (r < 0)
		वापस -ENODEV;

	r = kvmhv_nested_init();
	अगर (r)
		वापस r;

	r = kvm_init_subcore_biपंचांगap();
	अगर (r)
		वापस r;

	/*
	 * We need a way of accessing the XICS पूर्णांकerrupt controller,
	 * either directly, via paca_ptrs[cpu]->kvm_hstate.xics_phys, or
	 * indirectly, via OPAL.
	 */
#अगर_घोषित CONFIG_SMP
	अगर (!xics_on_xive() && !kvmhv_on_pseries() &&
	    !local_paca->kvm_hstate.xics_phys) अणु
		काष्ठा device_node *np;

		np = of_find_compatible_node(शून्य, शून्य, "ibm,opal-intc");
		अगर (!np) अणु
			pr_err("KVM-HV: Cannot determine method for accessing XICS\n");
			वापस -ENODEV;
		पूर्ण
		/* presence of पूर्णांकc confirmed - node can be dropped again */
		of_node_put(np);
	पूर्ण
#पूर्ण_अगर

	kvm_ops_hv.owner = THIS_MODULE;
	kvmppc_hv_ops = &kvm_ops_hv;

	init_शेष_hcalls();

	init_vcore_lists();

	r = kvmppc_mmu_hv_init();
	अगर (r)
		वापस r;

	अगर (kvmppc_radix_possible())
		r = kvmppc_radix_init();

	/*
	 * POWER9 chips beक्रमe version 2.02 can't have some thपढ़ोs in
	 * HPT mode and some in radix mode on the same core.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अचिन्हित पूर्णांक pvr = mfspr(SPRN_PVR);
		अगर ((pvr >> 16) == PVR_POWER9 &&
		    (((pvr & 0xe000) == 0 && (pvr & 0xfff) < 0x202) ||
		     ((pvr & 0xe000) == 0x2000 && (pvr & 0xfff) < 0x101)))
			no_mixing_hpt_and_radix = true;
	पूर्ण

	r = kvmppc_uvmem_init();
	अगर (r < 0)
		pr_err("KVM-HV: kvmppc_uvmem_init failed %d\n", r);

	वापस r;
पूर्ण

अटल व्योम kvmppc_book3s_निकास_hv(व्योम)
अणु
	kvmppc_uvmem_मुक्त();
	kvmppc_मुक्त_host_rm_ops();
	अगर (kvmppc_radix_possible())
		kvmppc_radix_निकास();
	kvmppc_hv_ops = शून्य;
	kvmhv_nested_निकास();
पूर्ण

module_init(kvmppc_book3s_init_hv);
module_निकास(kvmppc_book3s_निकास_hv);
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(KVM_MINOR);
MODULE_ALIAS("devname:kvm");
