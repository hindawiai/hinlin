<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: MIPS specअगरic KVM APIs
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>

#समावेश <linux/kvm_host.h>

#समावेश "interrupt.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#अगर_अघोषित VECTORSPACING
#घोषणा VECTORSPACING 0x100	/* क्रम EI/VI mode */
#पूर्ण_अगर

काष्ठा kvm_stats_debugfs_item debugfs_entries[] = अणु
	VCPU_STAT("wait", रुको_निकासs),
	VCPU_STAT("cache", cache_निकासs),
	VCPU_STAT("signal", संकेत_निकासs),
	VCPU_STAT("interrupt", पूर्णांक_निकासs),
	VCPU_STAT("cop_unusable", cop_unusable_निकासs),
	VCPU_STAT("tlbmod", tlbmod_निकासs),
	VCPU_STAT("tlbmiss_ld", tlbmiss_ld_निकासs),
	VCPU_STAT("tlbmiss_st", tlbmiss_st_निकासs),
	VCPU_STAT("addrerr_st", addrerr_st_निकासs),
	VCPU_STAT("addrerr_ld", addrerr_ld_निकासs),
	VCPU_STAT("syscall", syscall_निकासs),
	VCPU_STAT("resvd_inst", resvd_inst_निकासs),
	VCPU_STAT("break_inst", अवरोध_inst_निकासs),
	VCPU_STAT("trap_inst", trap_inst_निकासs),
	VCPU_STAT("msa_fpe", msa_fpe_निकासs),
	VCPU_STAT("fpe", fpe_निकासs),
	VCPU_STAT("msa_disabled", msa_disabled_निकासs),
	VCPU_STAT("flush_dcache", flush_dcache_निकासs),
	VCPU_STAT("vz_gpsi", vz_gpsi_निकासs),
	VCPU_STAT("vz_gsfc", vz_gsfc_निकासs),
	VCPU_STAT("vz_hc", vz_hc_निकासs),
	VCPU_STAT("vz_grr", vz_grr_निकासs),
	VCPU_STAT("vz_gva", vz_gva_निकासs),
	VCPU_STAT("vz_ghfc", vz_ghfc_निकासs),
	VCPU_STAT("vz_gpa", vz_gpa_निकासs),
	VCPU_STAT("vz_resvd", vz_resvd_निकासs),
#अगर_घोषित CONFIG_CPU_LOONGSON64
	VCPU_STAT("vz_cpucfg", vz_cpucfg_निकासs),
#पूर्ण_अगर
	VCPU_STAT("halt_successful_poll", halt_successful_poll),
	VCPU_STAT("halt_attempted_poll", halt_attempted_poll),
	VCPU_STAT("halt_poll_invalid", halt_poll_invalid),
	VCPU_STAT("halt_wakeup", halt_wakeup),
	VCPU_STAT("halt_poll_success_ns", halt_poll_success_ns),
	VCPU_STAT("halt_poll_fail_ns", halt_poll_fail_ns),
	अणुशून्यपूर्ण
पूर्ण;

bool kvm_trace_guest_mode_change;

पूर्णांक kvm_guest_mode_change_trace_reg(व्योम)
अणु
	kvm_trace_guest_mode_change = true;
	वापस 0;
पूर्ण

व्योम kvm_guest_mode_change_trace_unreg(व्योम)
अणु
	kvm_trace_guest_mode_change = false;
पूर्ण

/*
 * XXXKYMA: We are simulatoring a processor that has the WII bit set in
 * Config7, so we are "runnable" अगर पूर्णांकerrupts are pending
 */
पूर्णांक kvm_arch_vcpu_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(vcpu->arch.pending_exceptions);
पूर्ण

bool kvm_arch_vcpu_in_kernel(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण

पूर्णांक kvm_arch_vcpu_should_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 1;
पूर्ण

पूर्णांक kvm_arch_hardware_enable(व्योम)
अणु
	वापस kvm_mips_callbacks->hardware_enable();
पूर्ण

व्योम kvm_arch_hardware_disable(व्योम)
अणु
	kvm_mips_callbacks->hardware_disable();
पूर्ण

पूर्णांक kvm_arch_hardware_setup(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_check_processor_compat(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

बाह्य व्योम kvm_init_loongson_ipi(काष्ठा kvm *kvm);

पूर्णांक kvm_arch_init_vm(काष्ठा kvm *kvm, अचिन्हित दीर्घ type)
अणु
	चयन (type) अणु
	हाल KVM_VM_MIPS_AUTO:
		अवरोध;
	हाल KVM_VM_MIPS_VZ:
		अवरोध;
	शेष:
		/* Unsupported KVM type */
		वापस -EINVAL;
	पूर्ण

	/* Allocate page table to map GPA -> RPA */
	kvm->arch.gpa_mm.pgd = kvm_pgd_alloc();
	अगर (!kvm->arch.gpa_mm.pgd)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_CPU_LOONGSON64
	kvm_init_loongson_ipi(kvm);
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम kvm_mips_मुक्त_vcpus(काष्ठा kvm *kvm)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		kvm_vcpu_destroy(vcpu);
	पूर्ण

	mutex_lock(&kvm->lock);

	क्रम (i = 0; i < atomic_पढ़ो(&kvm->online_vcpus); i++)
		kvm->vcpus[i] = शून्य;

	atomic_set(&kvm->online_vcpus, 0);

	mutex_unlock(&kvm->lock);
पूर्ण

अटल व्योम kvm_mips_मुक्त_gpa_pt(काष्ठा kvm *kvm)
अणु
	/* It should always be safe to हटाओ after flushing the whole range */
	WARN_ON(!kvm_mips_flush_gpa_pt(kvm, 0, ~0));
	pgd_मुक्त(शून्य, kvm->arch.gpa_mm.pgd);
पूर्ण

व्योम kvm_arch_destroy_vm(काष्ठा kvm *kvm)
अणु
	kvm_mips_मुक्त_vcpus(kvm);
	kvm_mips_मुक्त_gpa_pt(kvm);
पूर्ण

दीर्घ kvm_arch_dev_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			अचिन्हित दीर्घ arg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

व्योम kvm_arch_flush_shaकरोw_all(काष्ठा kvm *kvm)
अणु
	/* Flush whole GPA */
	kvm_mips_flush_gpa_pt(kvm, 0, ~0);
	kvm_flush_remote_tlbs(kvm);
पूर्ण

व्योम kvm_arch_flush_shaकरोw_memslot(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot)
अणु
	/*
	 * The slot has been made invalid (पढ़ोy क्रम moving or deletion), so we
	 * need to ensure that it can no दीर्घer be accessed by any guest VCPUs.
	 */

	spin_lock(&kvm->mmu_lock);
	/* Flush slot from GPA */
	kvm_mips_flush_gpa_pt(kvm, slot->base_gfn,
			      slot->base_gfn + slot->npages - 1);
	kvm_arch_flush_remote_tlbs_memslot(kvm, slot);
	spin_unlock(&kvm->mmu_lock);
पूर्ण

पूर्णांक kvm_arch_prepare_memory_region(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *memslot,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   क्रमागत kvm_mr_change change)
अणु
	वापस 0;
पूर्ण

व्योम kvm_arch_commit_memory_region(काष्ठा kvm *kvm,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   काष्ठा kvm_memory_slot *old,
				   स्थिर काष्ठा kvm_memory_slot *new,
				   क्रमागत kvm_mr_change change)
अणु
	पूर्णांक needs_flush;

	kvm_debug("%s: kvm: %p slot: %d, GPA: %llx, size: %llx, QVA: %llx\n",
		  __func__, kvm, mem->slot, mem->guest_phys_addr,
		  mem->memory_size, mem->userspace_addr);

	/*
	 * If dirty page logging is enabled, ग_लिखो protect all pages in the slot
	 * पढ़ोy क्रम dirty logging.
	 *
	 * There is no need to करो this in any of the following हालs:
	 * CREATE:	No dirty mappings will alपढ़ोy exist.
	 * MOVE/DELETE:	The old mappings will alपढ़ोy have been cleaned up by
	 *		kvm_arch_flush_shaकरोw_memslot()
	 */
	अगर (change == KVM_MR_FLAGS_ONLY &&
	    (!(old->flags & KVM_MEM_LOG_सूचीTY_PAGES) &&
	     new->flags & KVM_MEM_LOG_सूचीTY_PAGES)) अणु
		spin_lock(&kvm->mmu_lock);
		/* Write protect GPA page table entries */
		needs_flush = kvm_mips_mkclean_gpa_pt(kvm, new->base_gfn,
					new->base_gfn + new->npages - 1);
		अगर (needs_flush)
			kvm_arch_flush_remote_tlbs_memslot(kvm, new);
		spin_unlock(&kvm->mmu_lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dump_handler(स्थिर अक्षर *symbol, व्योम *start, व्योम *end)
अणु
	u32 *p;

	pr_debug("LEAF(%s)\n", symbol);

	pr_debug("\t.set push\n");
	pr_debug("\t.set noreorder\n");

	क्रम (p = start; p < (u32 *)end; ++p)
		pr_debug("\t.word\t0x%08x\t\t# %p\n", *p, p);

	pr_debug("\t.set\tpop\n");

	pr_debug("\tEND(%s)\n", symbol);
पूर्ण

/* low level hrसमयr wake routine */
अटल क्रमागत hrसमयr_restart kvm_mips_comparecount_wakeup(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा kvm_vcpu *vcpu;

	vcpu = container_of(समयr, काष्ठा kvm_vcpu, arch.comparecount_समयr);

	kvm_mips_callbacks->queue_समयr_पूर्णांक(vcpu);

	vcpu->arch.रुको = 0;
	rcuरुको_wake_up(&vcpu->रुको);

	वापस kvm_mips_count_समयout(vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_precreate(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक err, size;
	व्योम *gebase, *p, *handler, *refill_start, *refill_end;
	पूर्णांक i;

	kvm_debug("kvm @ %p: create cpu %d at %p\n",
		  vcpu->kvm, vcpu->vcpu_id, vcpu);

	err = kvm_mips_callbacks->vcpu_init(vcpu);
	अगर (err)
		वापस err;

	hrसमयr_init(&vcpu->arch.comparecount_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	vcpu->arch.comparecount_समयr.function = kvm_mips_comparecount_wakeup;

	/*
	 * Allocate space क्रम host mode exception handlers that handle
	 * guest mode निकासs
	 */
	अगर (cpu_has_veic || cpu_has_vपूर्णांक)
		size = 0x200 + VECTORSPACING * 64;
	अन्यथा
		size = 0x4000;

	gebase = kzalloc(ALIGN(size, PAGE_SIZE), GFP_KERNEL);

	अगर (!gebase) अणु
		err = -ENOMEM;
		जाओ out_uninit_vcpu;
	पूर्ण
	kvm_debug("Allocated %d bytes for KVM Exception Handlers @ %p\n",
		  ALIGN(size, PAGE_SIZE), gebase);

	/*
	 * Check new ebase actually fits in CP0_EBase. The lack of a ग_लिखो gate
	 * limits us to the low 512MB of physical address space. If the memory
	 * we allocate is out of range, just give up now.
	 */
	अगर (!cpu_has_ebase_wg && virt_to_phys(gebase) >= 0x20000000) अणु
		kvm_err("CP0_EBase.WG required for guest exception base %pK\n",
			gebase);
		err = -ENOMEM;
		जाओ out_मुक्त_gebase;
	पूर्ण

	/* Save new ebase */
	vcpu->arch.guest_ebase = gebase;

	/* Build guest exception vectors dynamically in unmapped memory */
	handler = gebase + 0x2000;

	/* TLB refill (or XTLB refill on 64-bit VZ where KX=1) */
	refill_start = gebase;
	अगर (IS_ENABLED(CONFIG_64BIT))
		refill_start += 0x080;
	refill_end = kvm_mips_build_tlb_refill_exception(refill_start, handler);

	/* General Exception Entry poपूर्णांक */
	kvm_mips_build_exception(gebase + 0x180, handler);

	/* For vectored पूर्णांकerrupts poke the exception code @ all offsets 0-7 */
	क्रम (i = 0; i < 8; i++) अणु
		kvm_debug("L1 Vectored handler @ %p\n",
			  gebase + 0x200 + (i * VECTORSPACING));
		kvm_mips_build_exception(gebase + 0x200 + i * VECTORSPACING,
					 handler);
	पूर्ण

	/* General निकास handler */
	p = handler;
	p = kvm_mips_build_निकास(p);

	/* Guest entry routine */
	vcpu->arch.vcpu_run = p;
	p = kvm_mips_build_vcpu_run(p);

	/* Dump the generated code */
	pr_debug("#include <asm/asm.h>\n");
	pr_debug("#include <asm/regdef.h>\n");
	pr_debug("\n");
	dump_handler("kvm_vcpu_run", vcpu->arch.vcpu_run, p);
	dump_handler("kvm_tlb_refill", refill_start, refill_end);
	dump_handler("kvm_gen_exc", gebase + 0x180, gebase + 0x200);
	dump_handler("kvm_exit", gebase + 0x2000, vcpu->arch.vcpu_run);

	/* Invalidate the icache क्रम these ranges */
	flush_icache_range((अचिन्हित दीर्घ)gebase,
			   (अचिन्हित दीर्घ)gebase + ALIGN(size, PAGE_SIZE));

	/* Init */
	vcpu->arch.last_sched_cpu = -1;
	vcpu->arch.last_exec_cpu = -1;

	/* Initial guest state */
	err = kvm_mips_callbacks->vcpu_setup(vcpu);
	अगर (err)
		जाओ out_मुक्त_gebase;

	वापस 0;

out_मुक्त_gebase:
	kमुक्त(gebase);
out_uninit_vcpu:
	kvm_mips_callbacks->vcpu_uninit(vcpu);
	वापस err;
पूर्ण

व्योम kvm_arch_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	hrसमयr_cancel(&vcpu->arch.comparecount_समयr);

	kvm_mips_dump_stats(vcpu);

	kvm_mmu_मुक्त_memory_caches(vcpu);
	kमुक्त(vcpu->arch.guest_ebase);

	kvm_mips_callbacks->vcpu_uninit(vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_guest_debug *dbg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r = -EINTR;

	vcpu_load(vcpu);

	kvm_sigset_activate(vcpu);

	अगर (vcpu->mmio_needed) अणु
		अगर (!vcpu->mmio_is_ग_लिखो)
			kvm_mips_complete_mmio_load(vcpu);
		vcpu->mmio_needed = 0;
	पूर्ण

	अगर (vcpu->run->immediate_निकास)
		जाओ out;

	lose_fpu(1);

	local_irq_disable();
	guest_enter_irqoff();
	trace_kvm_enter(vcpu);

	/*
	 * Make sure the पढ़ो of VCPU requests in vcpu_run() callback is not
	 * reordered ahead of the ग_लिखो to vcpu->mode, or we could miss a TLB
	 * flush request जबतक the requester sees the VCPU as outside of guest
	 * mode and not needing an IPI.
	 */
	smp_store_mb(vcpu->mode, IN_GUEST_MODE);

	r = kvm_mips_callbacks->vcpu_run(vcpu);

	trace_kvm_out(vcpu);
	guest_निकास_irqoff();
	local_irq_enable();

out:
	kvm_sigset_deactivate(vcpu);

	vcpu_put(vcpu);
	वापस r;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_mips_पूर्णांकerrupt *irq)
अणु
	पूर्णांक पूर्णांकr = (पूर्णांक)irq->irq;
	काष्ठा kvm_vcpu *dvcpu = शून्य;

	अगर (पूर्णांकr == kvm_priority_to_irq[MIPS_EXC_INT_IPI_1] ||
	    पूर्णांकr == kvm_priority_to_irq[MIPS_EXC_INT_IPI_2] ||
	    पूर्णांकr == (-kvm_priority_to_irq[MIPS_EXC_INT_IPI_1]) ||
	    पूर्णांकr == (-kvm_priority_to_irq[MIPS_EXC_INT_IPI_2]))
		kvm_debug("%s: CPU: %d, INTR: %d\n", __func__, irq->cpu,
			  (पूर्णांक)पूर्णांकr);

	अगर (irq->cpu == -1)
		dvcpu = vcpu;
	अन्यथा
		dvcpu = vcpu->kvm->vcpus[irq->cpu];

	अगर (पूर्णांकr == 2 || पूर्णांकr == 3 || पूर्णांकr == 4 || पूर्णांकr == 6) अणु
		kvm_mips_callbacks->queue_io_पूर्णांक(dvcpu, irq);

	पूर्ण अन्यथा अगर (पूर्णांकr == -2 || पूर्णांकr == -3 || पूर्णांकr == -4 || पूर्णांकr == -6) अणु
		kvm_mips_callbacks->dequeue_io_पूर्णांक(dvcpu, irq);
	पूर्ण अन्यथा अणु
		kvm_err("%s: invalid interrupt ioctl (%d:%d)\n", __func__,
			irq->cpu, irq->irq);
		वापस -EINVAL;
	पूर्ण

	dvcpu->arch.रुको = 0;

	rcuरुको_wake_up(&dvcpu->रुको);

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

अटल u64 kvm_mips_get_one_regs[] = अणु
	KVM_REG_MIPS_R0,
	KVM_REG_MIPS_R1,
	KVM_REG_MIPS_R2,
	KVM_REG_MIPS_R3,
	KVM_REG_MIPS_R4,
	KVM_REG_MIPS_R5,
	KVM_REG_MIPS_R6,
	KVM_REG_MIPS_R7,
	KVM_REG_MIPS_R8,
	KVM_REG_MIPS_R9,
	KVM_REG_MIPS_R10,
	KVM_REG_MIPS_R11,
	KVM_REG_MIPS_R12,
	KVM_REG_MIPS_R13,
	KVM_REG_MIPS_R14,
	KVM_REG_MIPS_R15,
	KVM_REG_MIPS_R16,
	KVM_REG_MIPS_R17,
	KVM_REG_MIPS_R18,
	KVM_REG_MIPS_R19,
	KVM_REG_MIPS_R20,
	KVM_REG_MIPS_R21,
	KVM_REG_MIPS_R22,
	KVM_REG_MIPS_R23,
	KVM_REG_MIPS_R24,
	KVM_REG_MIPS_R25,
	KVM_REG_MIPS_R26,
	KVM_REG_MIPS_R27,
	KVM_REG_MIPS_R28,
	KVM_REG_MIPS_R29,
	KVM_REG_MIPS_R30,
	KVM_REG_MIPS_R31,

#अगर_अघोषित CONFIG_CPU_MIPSR6
	KVM_REG_MIPS_HI,
	KVM_REG_MIPS_LO,
#पूर्ण_अगर
	KVM_REG_MIPS_PC,
पूर्ण;

अटल u64 kvm_mips_get_one_regs_fpu[] = अणु
	KVM_REG_MIPS_FCR_IR,
	KVM_REG_MIPS_FCR_CSR,
पूर्ण;

अटल u64 kvm_mips_get_one_regs_msa[] = अणु
	KVM_REG_MIPS_MSA_IR,
	KVM_REG_MIPS_MSA_CSR,
पूर्ण;

अटल अचिन्हित दीर्घ kvm_mips_num_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ ret;

	ret = ARRAY_SIZE(kvm_mips_get_one_regs);
	अगर (kvm_mips_guest_can_have_fpu(&vcpu->arch)) अणु
		ret += ARRAY_SIZE(kvm_mips_get_one_regs_fpu) + 48;
		/* odd द्विगुनs */
		अगर (boot_cpu_data.fpu_id & MIPS_FPIR_F64)
			ret += 16;
	पूर्ण
	अगर (kvm_mips_guest_can_have_msa(&vcpu->arch))
		ret += ARRAY_SIZE(kvm_mips_get_one_regs_msa) + 32;
	ret += kvm_mips_callbacks->num_regs(vcpu);

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_mips_copy_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *indices)
अणु
	u64 index;
	अचिन्हित पूर्णांक i;

	अगर (copy_to_user(indices, kvm_mips_get_one_regs,
			 माप(kvm_mips_get_one_regs)))
		वापस -EFAULT;
	indices += ARRAY_SIZE(kvm_mips_get_one_regs);

	अगर (kvm_mips_guest_can_have_fpu(&vcpu->arch)) अणु
		अगर (copy_to_user(indices, kvm_mips_get_one_regs_fpu,
				 माप(kvm_mips_get_one_regs_fpu)))
			वापस -EFAULT;
		indices += ARRAY_SIZE(kvm_mips_get_one_regs_fpu);

		क्रम (i = 0; i < 32; ++i) अणु
			index = KVM_REG_MIPS_FPR_32(i);
			अगर (copy_to_user(indices, &index, माप(index)))
				वापस -EFAULT;
			++indices;

			/* skip odd द्विगुनs अगर no F64 */
			अगर (i & 1 && !(boot_cpu_data.fpu_id & MIPS_FPIR_F64))
				जारी;

			index = KVM_REG_MIPS_FPR_64(i);
			अगर (copy_to_user(indices, &index, माप(index)))
				वापस -EFAULT;
			++indices;
		पूर्ण
	पूर्ण

	अगर (kvm_mips_guest_can_have_msa(&vcpu->arch)) अणु
		अगर (copy_to_user(indices, kvm_mips_get_one_regs_msa,
				 माप(kvm_mips_get_one_regs_msa)))
			वापस -EFAULT;
		indices += ARRAY_SIZE(kvm_mips_get_one_regs_msa);

		क्रम (i = 0; i < 32; ++i) अणु
			index = KVM_REG_MIPS_VEC_128(i);
			अगर (copy_to_user(indices, &index, माप(index)))
				वापस -EFAULT;
			++indices;
		पूर्ण
	पूर्ण

	वापस kvm_mips_callbacks->copy_reg_indices(vcpu, indices);
पूर्ण

अटल पूर्णांक kvm_mips_get_reg(काष्ठा kvm_vcpu *vcpu,
			    स्थिर काष्ठा kvm_one_reg *reg)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	काष्ठा mips_fpu_काष्ठा *fpu = &vcpu->arch.fpu;
	पूर्णांक ret;
	s64 v;
	s64 vs[2];
	अचिन्हित पूर्णांक idx;

	चयन (reg->id) अणु
	/* General purpose रेजिस्टरs */
	हाल KVM_REG_MIPS_R0 ... KVM_REG_MIPS_R31:
		v = (दीर्घ)vcpu->arch.gprs[reg->id - KVM_REG_MIPS_R0];
		अवरोध;
#अगर_अघोषित CONFIG_CPU_MIPSR6
	हाल KVM_REG_MIPS_HI:
		v = (दीर्घ)vcpu->arch.hi;
		अवरोध;
	हाल KVM_REG_MIPS_LO:
		v = (दीर्घ)vcpu->arch.lo;
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_MIPS_PC:
		v = (दीर्घ)vcpu->arch.pc;
		अवरोध;

	/* Floating poपूर्णांक रेजिस्टरs */
	हाल KVM_REG_MIPS_FPR_32(0) ... KVM_REG_MIPS_FPR_32(31):
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_FPR_32(0);
		/* Odd singles in top of even द्विगुन when FR=0 */
		अगर (kvm_पढ़ो_c0_guest_status(cop0) & ST0_FR)
			v = get_fpr32(&fpu->fpr[idx], 0);
		अन्यथा
			v = get_fpr32(&fpu->fpr[idx & ~1], idx & 1);
		अवरोध;
	हाल KVM_REG_MIPS_FPR_64(0) ... KVM_REG_MIPS_FPR_64(31):
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_FPR_64(0);
		/* Can't access odd द्विगुनs in FR=0 mode */
		अगर (idx & 1 && !(kvm_पढ़ो_c0_guest_status(cop0) & ST0_FR))
			वापस -EINVAL;
		v = get_fpr64(&fpu->fpr[idx], 0);
		अवरोध;
	हाल KVM_REG_MIPS_FCR_IR:
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		v = boot_cpu_data.fpu_id;
		अवरोध;
	हाल KVM_REG_MIPS_FCR_CSR:
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		v = fpu->fcr31;
		अवरोध;

	/* MIPS SIMD Architecture (MSA) रेजिस्टरs */
	हाल KVM_REG_MIPS_VEC_128(0) ... KVM_REG_MIPS_VEC_128(31):
		अगर (!kvm_mips_guest_has_msa(&vcpu->arch))
			वापस -EINVAL;
		/* Can't access MSA रेजिस्टरs in FR=0 mode */
		अगर (!(kvm_पढ़ो_c0_guest_status(cop0) & ST0_FR))
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_VEC_128(0);
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
		/* least signअगरicant byte first */
		vs[0] = get_fpr64(&fpu->fpr[idx], 0);
		vs[1] = get_fpr64(&fpu->fpr[idx], 1);
#अन्यथा
		/* most signअगरicant byte first */
		vs[0] = get_fpr64(&fpu->fpr[idx], 1);
		vs[1] = get_fpr64(&fpu->fpr[idx], 0);
#पूर्ण_अगर
		अवरोध;
	हाल KVM_REG_MIPS_MSA_IR:
		अगर (!kvm_mips_guest_has_msa(&vcpu->arch))
			वापस -EINVAL;
		v = boot_cpu_data.msa_id;
		अवरोध;
	हाल KVM_REG_MIPS_MSA_CSR:
		अगर (!kvm_mips_guest_has_msa(&vcpu->arch))
			वापस -EINVAL;
		v = fpu->msacsr;
		अवरोध;

	/* रेजिस्टरs to be handled specially */
	शेष:
		ret = kvm_mips_callbacks->get_one_reg(vcpu, reg, &v);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण
	अगर ((reg->id & KVM_REG_SIZE_MASK) == KVM_REG_SIZE_U64) अणु
		u64 __user *uaddr64 = (u64 __user *)(दीर्घ)reg->addr;

		वापस put_user(v, uaddr64);
	पूर्ण अन्यथा अगर ((reg->id & KVM_REG_SIZE_MASK) == KVM_REG_SIZE_U32) अणु
		u32 __user *uaddr32 = (u32 __user *)(दीर्घ)reg->addr;
		u32 v32 = (u32)v;

		वापस put_user(v32, uaddr32);
	पूर्ण अन्यथा अगर ((reg->id & KVM_REG_SIZE_MASK) == KVM_REG_SIZE_U128) अणु
		व्योम __user *uaddr = (व्योम __user *)(दीर्घ)reg->addr;

		वापस copy_to_user(uaddr, vs, 16) ? -EFAULT : 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_mips_set_reg(काष्ठा kvm_vcpu *vcpu,
			    स्थिर काष्ठा kvm_one_reg *reg)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	काष्ठा mips_fpu_काष्ठा *fpu = &vcpu->arch.fpu;
	s64 v;
	s64 vs[2];
	अचिन्हित पूर्णांक idx;

	अगर ((reg->id & KVM_REG_SIZE_MASK) == KVM_REG_SIZE_U64) अणु
		u64 __user *uaddr64 = (u64 __user *)(दीर्घ)reg->addr;

		अगर (get_user(v, uaddr64) != 0)
			वापस -EFAULT;
	पूर्ण अन्यथा अगर ((reg->id & KVM_REG_SIZE_MASK) == KVM_REG_SIZE_U32) अणु
		u32 __user *uaddr32 = (u32 __user *)(दीर्घ)reg->addr;
		s32 v32;

		अगर (get_user(v32, uaddr32) != 0)
			वापस -EFAULT;
		v = (s64)v32;
	पूर्ण अन्यथा अगर ((reg->id & KVM_REG_SIZE_MASK) == KVM_REG_SIZE_U128) अणु
		व्योम __user *uaddr = (व्योम __user *)(दीर्घ)reg->addr;

		वापस copy_from_user(vs, uaddr, 16) ? -EFAULT : 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	चयन (reg->id) अणु
	/* General purpose रेजिस्टरs */
	हाल KVM_REG_MIPS_R0:
		/* Silently ignore requests to set $0 */
		अवरोध;
	हाल KVM_REG_MIPS_R1 ... KVM_REG_MIPS_R31:
		vcpu->arch.gprs[reg->id - KVM_REG_MIPS_R0] = v;
		अवरोध;
#अगर_अघोषित CONFIG_CPU_MIPSR6
	हाल KVM_REG_MIPS_HI:
		vcpu->arch.hi = v;
		अवरोध;
	हाल KVM_REG_MIPS_LO:
		vcpu->arch.lo = v;
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_MIPS_PC:
		vcpu->arch.pc = v;
		अवरोध;

	/* Floating poपूर्णांक रेजिस्टरs */
	हाल KVM_REG_MIPS_FPR_32(0) ... KVM_REG_MIPS_FPR_32(31):
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_FPR_32(0);
		/* Odd singles in top of even द्विगुन when FR=0 */
		अगर (kvm_पढ़ो_c0_guest_status(cop0) & ST0_FR)
			set_fpr32(&fpu->fpr[idx], 0, v);
		अन्यथा
			set_fpr32(&fpu->fpr[idx & ~1], idx & 1, v);
		अवरोध;
	हाल KVM_REG_MIPS_FPR_64(0) ... KVM_REG_MIPS_FPR_64(31):
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_FPR_64(0);
		/* Can't access odd द्विगुनs in FR=0 mode */
		अगर (idx & 1 && !(kvm_पढ़ो_c0_guest_status(cop0) & ST0_FR))
			वापस -EINVAL;
		set_fpr64(&fpu->fpr[idx], 0, v);
		अवरोध;
	हाल KVM_REG_MIPS_FCR_IR:
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		/* Read-only */
		अवरोध;
	हाल KVM_REG_MIPS_FCR_CSR:
		अगर (!kvm_mips_guest_has_fpu(&vcpu->arch))
			वापस -EINVAL;
		fpu->fcr31 = v;
		अवरोध;

	/* MIPS SIMD Architecture (MSA) रेजिस्टरs */
	हाल KVM_REG_MIPS_VEC_128(0) ... KVM_REG_MIPS_VEC_128(31):
		अगर (!kvm_mips_guest_has_msa(&vcpu->arch))
			वापस -EINVAL;
		idx = reg->id - KVM_REG_MIPS_VEC_128(0);
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
		/* least signअगरicant byte first */
		set_fpr64(&fpu->fpr[idx], 0, vs[0]);
		set_fpr64(&fpu->fpr[idx], 1, vs[1]);
#अन्यथा
		/* most signअगरicant byte first */
		set_fpr64(&fpu->fpr[idx], 1, vs[0]);
		set_fpr64(&fpu->fpr[idx], 0, vs[1]);
#पूर्ण_अगर
		अवरोध;
	हाल KVM_REG_MIPS_MSA_IR:
		अगर (!kvm_mips_guest_has_msa(&vcpu->arch))
			वापस -EINVAL;
		/* Read-only */
		अवरोध;
	हाल KVM_REG_MIPS_MSA_CSR:
		अगर (!kvm_mips_guest_has_msa(&vcpu->arch))
			वापस -EINVAL;
		fpu->msacsr = v;
		अवरोध;

	/* रेजिस्टरs to be handled specially */
	शेष:
		वापस kvm_mips_callbacks->set_one_reg(vcpu, reg, v);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_enable_cap(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r = 0;

	अगर (!kvm_vm_ioctl_check_extension(vcpu->kvm, cap->cap))
		वापस -EINVAL;
	अगर (cap->flags)
		वापस -EINVAL;
	अगर (cap->args[0])
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_MIPS_FPU:
		vcpu->arch.fpu_enabled = true;
		अवरोध;
	हाल KVM_CAP_MIPS_MSA:
		vcpu->arch.msa_enabled = true;
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

दीर्घ kvm_arch_vcpu_async_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (ioctl == KVM_INTERRUPT) अणु
		काष्ठा kvm_mips_पूर्णांकerrupt irq;

		अगर (copy_from_user(&irq, argp, माप(irq)))
			वापस -EFAULT;
		kvm_debug("[%d] %s: irq: %d\n", vcpu->vcpu_id, __func__,
			  irq.irq);

		वापस kvm_vcpu_ioctl_पूर्णांकerrupt(vcpu, &irq);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

दीर्घ kvm_arch_vcpu_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			 अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	दीर्घ r;

	vcpu_load(vcpu);

	चयन (ioctl) अणु
	हाल KVM_SET_ONE_REG:
	हाल KVM_GET_ONE_REG: अणु
		काष्ठा kvm_one_reg reg;

		r = -EFAULT;
		अगर (copy_from_user(&reg, argp, माप(reg)))
			अवरोध;
		अगर (ioctl == KVM_SET_ONE_REG)
			r = kvm_mips_set_reg(vcpu, &reg);
		अन्यथा
			r = kvm_mips_get_reg(vcpu, &reg);
		अवरोध;
	पूर्ण
	हाल KVM_GET_REG_LIST: अणु
		काष्ठा kvm_reg_list __user *user_list = argp;
		काष्ठा kvm_reg_list reg_list;
		अचिन्हित n;

		r = -EFAULT;
		अगर (copy_from_user(&reg_list, user_list, माप(reg_list)))
			अवरोध;
		n = reg_list.n;
		reg_list.n = kvm_mips_num_regs(vcpu);
		अगर (copy_to_user(user_list, &reg_list, माप(reg_list)))
			अवरोध;
		r = -E2BIG;
		अगर (n < reg_list.n)
			अवरोध;
		r = kvm_mips_copy_reg_indices(vcpu, user_list->reg);
		अवरोध;
	पूर्ण
	हाल KVM_ENABLE_CAP: अणु
		काष्ठा kvm_enable_cap cap;

		r = -EFAULT;
		अगर (copy_from_user(&cap, argp, माप(cap)))
			अवरोध;
		r = kvm_vcpu_ioctl_enable_cap(vcpu, &cap);
		अवरोध;
	पूर्ण
	शेष:
		r = -ENOIOCTLCMD;
	पूर्ण

	vcpu_put(vcpu);
	वापस r;
पूर्ण

व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु

पूर्ण

पूर्णांक kvm_arch_flush_remote_tlb(काष्ठा kvm *kvm)
अणु
	kvm_mips_callbacks->prepare_flush_shaकरोw(kvm);
	वापस 1;
पूर्ण

व्योम kvm_arch_flush_remote_tlbs_memslot(काष्ठा kvm *kvm,
					स्थिर काष्ठा kvm_memory_slot *memslot)
अणु
	kvm_flush_remote_tlbs(kvm);
पूर्ण

दीर्घ kvm_arch_vm_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	दीर्घ r;

	चयन (ioctl) अणु
	शेष:
		r = -ENOIOCTLCMD;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvm_arch_init(व्योम *opaque)
अणु
	अगर (kvm_mips_callbacks) अणु
		kvm_err("kvm: module already exists\n");
		वापस -EEXIST;
	पूर्ण

	वापस kvm_mips_emulation_init(&kvm_mips_callbacks);
पूर्ण

व्योम kvm_arch_निकास(व्योम)
अणु
	kvm_mips_callbacks = शून्य;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

व्योम kvm_arch_vcpu_postcreate(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

vm_fault_t kvm_arch_vcpu_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण

पूर्णांक kvm_vm_ioctl_check_extension(काष्ठा kvm *kvm, दीर्घ ext)
अणु
	पूर्णांक r;

	चयन (ext) अणु
	हाल KVM_CAP_ONE_REG:
	हाल KVM_CAP_ENABLE_CAP:
	हाल KVM_CAP_READONLY_MEM:
	हाल KVM_CAP_SYNC_MMU:
	हाल KVM_CAP_IMMEDIATE_EXIT:
		r = 1;
		अवरोध;
	हाल KVM_CAP_NR_VCPUS:
		r = num_online_cpus();
		अवरोध;
	हाल KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		अवरोध;
	हाल KVM_CAP_MAX_VCPU_ID:
		r = KVM_MAX_VCPU_ID;
		अवरोध;
	हाल KVM_CAP_MIPS_FPU:
		/* We करोn't handle प्रणालीs with inconsistent cpu_has_fpu */
		r = !!raw_cpu_has_fpu;
		अवरोध;
	हाल KVM_CAP_MIPS_MSA:
		/*
		 * We करोn't support MSA vector partitioning yet:
		 * 1) It would require explicit support which can't be tested
		 *    yet due to lack of support in current hardware.
		 * 2) It extends the state that would need to be saved/restored
		 *    by e.g. QEMU क्रम migration.
		 *
		 * When vector partitioning hardware becomes available, support
		 * could be added by requiring a flag when enabling
		 * KVM_CAP_MIPS_MSA capability to indicate that userland knows
		 * to save/restore the appropriate extra state.
		 */
		r = cpu_has_msa && !(boot_cpu_data.msa_id & MSA_IR_WRPF);
		अवरोध;
	शेष:
		r = kvm_mips_callbacks->check_extension(kvm, ext);
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक kvm_cpu_has_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_mips_pending_समयr(vcpu) ||
		kvm_पढ़ो_c0_guest_cause(vcpu->arch.cop0) & C_TI;
पूर्ण

पूर्णांक kvm_arch_vcpu_dump_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा mips_coproc *cop0;

	अगर (!vcpu)
		वापस -1;

	kvm_debug("VCPU Register Dump:\n");
	kvm_debug("\tpc = 0x%08lx\n", vcpu->arch.pc);
	kvm_debug("\texceptions: %08lx\n", vcpu->arch.pending_exceptions);

	क्रम (i = 0; i < 32; i += 4) अणु
		kvm_debug("\tgpr%02d: %08lx %08lx %08lx %08lx\n", i,
		       vcpu->arch.gprs[i],
		       vcpu->arch.gprs[i + 1],
		       vcpu->arch.gprs[i + 2], vcpu->arch.gprs[i + 3]);
	पूर्ण
	kvm_debug("\thi: 0x%08lx\n", vcpu->arch.hi);
	kvm_debug("\tlo: 0x%08lx\n", vcpu->arch.lo);

	cop0 = vcpu->arch.cop0;
	kvm_debug("\tStatus: 0x%08x, Cause: 0x%08x\n",
		  kvm_पढ़ो_c0_guest_status(cop0),
		  kvm_पढ़ो_c0_guest_cause(cop0));

	kvm_debug("\tEPC: 0x%08lx\n", kvm_पढ़ो_c0_guest_epc(cop0));

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	पूर्णांक i;

	vcpu_load(vcpu);

	क्रम (i = 1; i < ARRAY_SIZE(vcpu->arch.gprs); i++)
		vcpu->arch.gprs[i] = regs->gpr[i];
	vcpu->arch.gprs[0] = 0; /* zero is special, and cannot be set. */
	vcpu->arch.hi = regs->hi;
	vcpu->arch.lo = regs->lo;
	vcpu->arch.pc = regs->pc;

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	पूर्णांक i;

	vcpu_load(vcpu);

	क्रम (i = 0; i < ARRAY_SIZE(vcpu->arch.gprs); i++)
		regs->gpr[i] = vcpu->arch.gprs[i];

	regs->hi = vcpu->arch.hi;
	regs->lo = vcpu->arch.lo;
	regs->pc = vcpu->arch.pc;

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_translation *tr)
अणु
	वापस 0;
पूर्ण

अटल व्योम kvm_mips_set_c0_status(व्योम)
अणु
	u32 status = पढ़ो_c0_status();

	अगर (cpu_has_dsp)
		status |= (ST0_MX);

	ग_लिखो_c0_status(status);
	ehb();
पूर्ण

/*
 * Return value is in the क्रमm (errcode<<2 | RESUME_FLAG_HOST | RESUME_FLAG_NV)
 */
पूर्णांक kvm_mips_handle_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	u32 cause = vcpu->arch.host_cp0_cause;
	u32 exccode = (cause >> CAUSEB_EXCCODE) & 0x1f;
	u32 __user *opc = (u32 __user *) vcpu->arch.pc;
	अचिन्हित दीर्घ badvaddr = vcpu->arch.host_cp0_badvaddr;
	क्रमागत emulation_result er = EMULATE_DONE;
	u32 inst;
	पूर्णांक ret = RESUME_GUEST;

	vcpu->mode = OUTSIDE_GUEST_MODE;

	/* Set a शेष निकास reason */
	run->निकास_reason = KVM_EXIT_UNKNOWN;
	run->पढ़ोy_क्रम_पूर्णांकerrupt_injection = 1;

	/*
	 * Set the appropriate status bits based on host CPU features,
	 * beक्रमe we hit the scheduler
	 */
	kvm_mips_set_c0_status();

	local_irq_enable();

	kvm_debug("kvm_mips_handle_exit: cause: %#x, PC: %p, kvm_run: %p, kvm_vcpu: %p\n",
			cause, opc, run, vcpu);
	trace_kvm_निकास(vcpu, exccode);

	चयन (exccode) अणु
	हाल EXCCODE_INT:
		kvm_debug("[%d]EXCCODE_INT @ %p\n", vcpu->vcpu_id, opc);

		++vcpu->stat.पूर्णांक_निकासs;

		अगर (need_resched())
			cond_resched();

		ret = RESUME_GUEST;
		अवरोध;

	हाल EXCCODE_CPU:
		kvm_debug("EXCCODE_CPU: @ PC: %p\n", opc);

		++vcpu->stat.cop_unusable_निकासs;
		ret = kvm_mips_callbacks->handle_cop_unusable(vcpu);
		/* XXXKYMA: Might need to वापस to user space */
		अगर (run->निकास_reason == KVM_EXIT_IRQ_WINDOW_OPEN)
			ret = RESUME_HOST;
		अवरोध;

	हाल EXCCODE_MOD:
		++vcpu->stat.tlbmod_निकासs;
		ret = kvm_mips_callbacks->handle_tlb_mod(vcpu);
		अवरोध;

	हाल EXCCODE_TLBS:
		kvm_debug("TLB ST fault:  cause %#x, status %#x, PC: %p, BadVaddr: %#lx\n",
			  cause, kvm_पढ़ो_c0_guest_status(vcpu->arch.cop0), opc,
			  badvaddr);

		++vcpu->stat.tlbmiss_st_निकासs;
		ret = kvm_mips_callbacks->handle_tlb_st_miss(vcpu);
		अवरोध;

	हाल EXCCODE_TLBL:
		kvm_debug("TLB LD fault: cause %#x, PC: %p, BadVaddr: %#lx\n",
			  cause, opc, badvaddr);

		++vcpu->stat.tlbmiss_ld_निकासs;
		ret = kvm_mips_callbacks->handle_tlb_ld_miss(vcpu);
		अवरोध;

	हाल EXCCODE_ADES:
		++vcpu->stat.addrerr_st_निकासs;
		ret = kvm_mips_callbacks->handle_addr_err_st(vcpu);
		अवरोध;

	हाल EXCCODE_ADEL:
		++vcpu->stat.addrerr_ld_निकासs;
		ret = kvm_mips_callbacks->handle_addr_err_ld(vcpu);
		अवरोध;

	हाल EXCCODE_SYS:
		++vcpu->stat.syscall_निकासs;
		ret = kvm_mips_callbacks->handle_syscall(vcpu);
		अवरोध;

	हाल EXCCODE_RI:
		++vcpu->stat.resvd_inst_निकासs;
		ret = kvm_mips_callbacks->handle_res_inst(vcpu);
		अवरोध;

	हाल EXCCODE_BP:
		++vcpu->stat.अवरोध_inst_निकासs;
		ret = kvm_mips_callbacks->handle_अवरोध(vcpu);
		अवरोध;

	हाल EXCCODE_TR:
		++vcpu->stat.trap_inst_निकासs;
		ret = kvm_mips_callbacks->handle_trap(vcpu);
		अवरोध;

	हाल EXCCODE_MSAFPE:
		++vcpu->stat.msa_fpe_निकासs;
		ret = kvm_mips_callbacks->handle_msa_fpe(vcpu);
		अवरोध;

	हाल EXCCODE_FPE:
		++vcpu->stat.fpe_निकासs;
		ret = kvm_mips_callbacks->handle_fpe(vcpu);
		अवरोध;

	हाल EXCCODE_MSADIS:
		++vcpu->stat.msa_disabled_निकासs;
		ret = kvm_mips_callbacks->handle_msa_disabled(vcpu);
		अवरोध;

	हाल EXCCODE_GE:
		/* defer निकास accounting to handler */
		ret = kvm_mips_callbacks->handle_guest_निकास(vcpu);
		अवरोध;

	शेष:
		अगर (cause & CAUSEF_BD)
			opc += 1;
		inst = 0;
		kvm_get_badinstr(opc, vcpu, &inst);
		kvm_err("Exception Code: %d, not yet handled, @ PC: %p, inst: 0x%08x  BadVaddr: %#lx Status: %#x\n",
			exccode, opc, inst, badvaddr,
			kvm_पढ़ो_c0_guest_status(vcpu->arch.cop0));
		kvm_arch_vcpu_dump_regs(vcpu);
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
		अवरोध;

	पूर्ण

	local_irq_disable();

	अगर (ret == RESUME_GUEST)
		kvm_vz_acquire_hसमयr(vcpu);

	अगर (er == EMULATE_DONE && !(ret & RESUME_HOST))
		kvm_mips_deliver_पूर्णांकerrupts(vcpu, cause);

	अगर (!(ret & RESUME_HOST)) अणु
		/* Only check क्रम संकेतs अगर not alपढ़ोy निकासing to userspace */
		अगर (संकेत_pending(current)) अणु
			run->निकास_reason = KVM_EXIT_INTR;
			ret = (-EINTR << 2) | RESUME_HOST;
			++vcpu->stat.संकेत_निकासs;
			trace_kvm_निकास(vcpu, KVM_TRACE_EXIT_SIGNAL);
		पूर्ण
	पूर्ण

	अगर (ret == RESUME_GUEST) अणु
		trace_kvm_reenter(vcpu);

		/*
		 * Make sure the पढ़ो of VCPU requests in vcpu_reenter()
		 * callback is not reordered ahead of the ग_लिखो to vcpu->mode,
		 * or we could miss a TLB flush request जबतक the requester sees
		 * the VCPU as outside of guest mode and not needing an IPI.
		 */
		smp_store_mb(vcpu->mode, IN_GUEST_MODE);

		kvm_mips_callbacks->vcpu_reenter(vcpu);

		/*
		 * If FPU / MSA are enabled (i.e. the guest's FPU / MSA context
		 * is live), restore FCR31 / MSACSR.
		 *
		 * This should be beक्रमe वापसing to the guest exception
		 * vector, as it may well cause an [MSA] FP exception अगर there
		 * are pending exception bits unmasked. (see
		 * kvm_mips_csr_die_notअगरier() क्रम how that is handled).
		 */
		अगर (kvm_mips_guest_has_fpu(&vcpu->arch) &&
		    पढ़ो_c0_status() & ST0_CU1)
			__kvm_restore_fcsr(&vcpu->arch);

		अगर (kvm_mips_guest_has_msa(&vcpu->arch) &&
		    पढ़ो_c0_config5() & MIPS_CONF5_MSAEN)
			__kvm_restore_msacsr(&vcpu->arch);
	पूर्ण
	वापस ret;
पूर्ण

/* Enable FPU क्रम guest and restore context */
व्योम kvm_own_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	अचिन्हित पूर्णांक sr, cfg5;

	preempt_disable();

	sr = kvm_पढ़ो_c0_guest_status(cop0);

	/*
	 * If MSA state is alपढ़ोy live, it is undefined how it पूर्णांकeracts with
	 * FR=0 FPU state, and we करोn't want to hit reserved inकाष्ठाion
	 * exceptions trying to save the MSA state later when CU=1 && FR=1, so
	 * play it safe and save it first.
	 */
	अगर (cpu_has_msa && sr & ST0_CU1 && !(sr & ST0_FR) &&
	    vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA)
		kvm_lose_fpu(vcpu);

	/*
	 * Enable FPU क्रम guest
	 * We set FR and FRE according to guest context
	 */
	change_c0_status(ST0_CU1 | ST0_FR, sr);
	अगर (cpu_has_fre) अणु
		cfg5 = kvm_पढ़ो_c0_guest_config5(cop0);
		change_c0_config5(MIPS_CONF5_FRE, cfg5);
	पूर्ण
	enable_fpu_hazard();

	/* If guest FPU state not active, restore it now */
	अगर (!(vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)) अणु
		__kvm_restore_fpu(&vcpu->arch);
		vcpu->arch.aux_inuse |= KVM_MIPS_AUX_FPU;
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_RESTORE, KVM_TRACE_AUX_FPU);
	पूर्ण अन्यथा अणु
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_ENABLE, KVM_TRACE_AUX_FPU);
	पूर्ण

	preempt_enable();
पूर्ण

#अगर_घोषित CONFIG_CPU_HAS_MSA
/* Enable MSA क्रम guest and restore context */
व्योम kvm_own_msa(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mips_coproc *cop0 = vcpu->arch.cop0;
	अचिन्हित पूर्णांक sr, cfg5;

	preempt_disable();

	/*
	 * Enable FPU अगर enabled in guest, since we're restoring FPU context
	 * anyway. We set FR and FRE according to guest context.
	 */
	अगर (kvm_mips_guest_has_fpu(&vcpu->arch)) अणु
		sr = kvm_पढ़ो_c0_guest_status(cop0);

		/*
		 * If FR=0 FPU state is alपढ़ोy live, it is undefined how it
		 * पूर्णांकeracts with MSA state, so play it safe and save it first.
		 */
		अगर (!(sr & ST0_FR) &&
		    (vcpu->arch.aux_inuse & (KVM_MIPS_AUX_FPU |
				KVM_MIPS_AUX_MSA)) == KVM_MIPS_AUX_FPU)
			kvm_lose_fpu(vcpu);

		change_c0_status(ST0_CU1 | ST0_FR, sr);
		अगर (sr & ST0_CU1 && cpu_has_fre) अणु
			cfg5 = kvm_पढ़ो_c0_guest_config5(cop0);
			change_c0_config5(MIPS_CONF5_FRE, cfg5);
		पूर्ण
	पूर्ण

	/* Enable MSA क्रम guest */
	set_c0_config5(MIPS_CONF5_MSAEN);
	enable_fpu_hazard();

	चयन (vcpu->arch.aux_inuse & (KVM_MIPS_AUX_FPU | KVM_MIPS_AUX_MSA)) अणु
	हाल KVM_MIPS_AUX_FPU:
		/*
		 * Guest FPU state alपढ़ोy loaded, only restore upper MSA state
		 */
		__kvm_restore_msa_upper(&vcpu->arch);
		vcpu->arch.aux_inuse |= KVM_MIPS_AUX_MSA;
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_RESTORE, KVM_TRACE_AUX_MSA);
		अवरोध;
	हाल 0:
		/* Neither FPU or MSA alपढ़ोy active, restore full MSA state */
		__kvm_restore_msa(&vcpu->arch);
		vcpu->arch.aux_inuse |= KVM_MIPS_AUX_MSA;
		अगर (kvm_mips_guest_has_fpu(&vcpu->arch))
			vcpu->arch.aux_inuse |= KVM_MIPS_AUX_FPU;
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_RESTORE,
			      KVM_TRACE_AUX_FPU_MSA);
		अवरोध;
	शेष:
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_ENABLE, KVM_TRACE_AUX_MSA);
		अवरोध;
	पूर्ण

	preempt_enable();
पूर्ण
#पूर्ण_अगर

/* Drop FPU & MSA without saving it */
व्योम kvm_drop_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	अगर (cpu_has_msa && vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA) अणु
		disable_msa();
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_DISCARD, KVM_TRACE_AUX_MSA);
		vcpu->arch.aux_inuse &= ~KVM_MIPS_AUX_MSA;
	पूर्ण
	अगर (vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU) अणु
		clear_c0_status(ST0_CU1 | ST0_FR);
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_DISCARD, KVM_TRACE_AUX_FPU);
		vcpu->arch.aux_inuse &= ~KVM_MIPS_AUX_FPU;
	पूर्ण
	preempt_enable();
पूर्ण

/* Save and disable FPU & MSA */
व्योम kvm_lose_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * With T&E, FPU & MSA get disabled in root context (hardware) when it
	 * is disabled in guest context (software), but the रेजिस्टर state in
	 * the hardware may still be in use.
	 * This is why we explicitly re-enable the hardware beक्रमe saving.
	 */

	preempt_disable();
	अगर (cpu_has_msa && vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA) अणु
		__kvm_save_msa(&vcpu->arch);
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_SAVE, KVM_TRACE_AUX_FPU_MSA);

		/* Disable MSA & FPU */
		disable_msa();
		अगर (vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU) अणु
			clear_c0_status(ST0_CU1 | ST0_FR);
			disable_fpu_hazard();
		पूर्ण
		vcpu->arch.aux_inuse &= ~(KVM_MIPS_AUX_FPU | KVM_MIPS_AUX_MSA);
	पूर्ण अन्यथा अगर (vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU) अणु
		__kvm_save_fpu(&vcpu->arch);
		vcpu->arch.aux_inuse &= ~KVM_MIPS_AUX_FPU;
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_SAVE, KVM_TRACE_AUX_FPU);

		/* Disable FPU */
		clear_c0_status(ST0_CU1 | ST0_FR);
		disable_fpu_hazard();
	पूर्ण
	preempt_enable();
पूर्ण

/*
 * Step over a specअगरic ctc1 to FCSR and a specअगरic ctcmsa to MSACSR which are
 * used to restore guest FCSR/MSACSR state and may trigger a "harmless" FP/MSAFP
 * exception अगर cause bits are set in the value being written.
 */
अटल पूर्णांक kvm_mips_csr_die_notअगरy(काष्ठा notअगरier_block *self,
				   अचिन्हित दीर्घ cmd, व्योम *ptr)
अणु
	काष्ठा die_args *args = (काष्ठा die_args *)ptr;
	काष्ठा pt_regs *regs = args->regs;
	अचिन्हित दीर्घ pc;

	/* Only पूर्णांकerested in FPE and MSAFPE */
	अगर (cmd != DIE_FP && cmd != DIE_MSAFP)
		वापस NOTIFY_DONE;

	/* Return immediately अगर guest context isn't active */
	अगर (!(current->flags & PF_VCPU))
		वापस NOTIFY_DONE;

	/* Should never get here from user mode */
	BUG_ON(user_mode(regs));

	pc = inकाष्ठाion_poपूर्णांकer(regs);
	चयन (cmd) अणु
	हाल DIE_FP:
		/* match 2nd inकाष्ठाion in __kvm_restore_fcsr */
		अगर (pc != (अचिन्हित दीर्घ)&__kvm_restore_fcsr + 4)
			वापस NOTIFY_DONE;
		अवरोध;
	हाल DIE_MSAFP:
		/* match 2nd/3rd inकाष्ठाion in __kvm_restore_msacsr */
		अगर (!cpu_has_msa ||
		    pc < (अचिन्हित दीर्घ)&__kvm_restore_msacsr + 4 ||
		    pc > (अचिन्हित दीर्घ)&__kvm_restore_msacsr + 8)
			वापस NOTIFY_DONE;
		अवरोध;
	पूर्ण

	/* Move PC क्रमward a little and जारी executing */
	inकाष्ठाion_poपूर्णांकer(regs) += 4;

	वापस NOTIFY_STOP;
पूर्ण

अटल काष्ठा notअगरier_block kvm_mips_csr_die_notअगरier = अणु
	.notअगरier_call = kvm_mips_csr_die_notअगरy,
पूर्ण;

अटल u32 kvm_शेष_priority_to_irq[MIPS_EXC_MAX] = अणु
	[MIPS_EXC_INT_TIMER] = C_IRQ5,
	[MIPS_EXC_INT_IO_1]  = C_IRQ0,
	[MIPS_EXC_INT_IPI_1] = C_IRQ1,
	[MIPS_EXC_INT_IPI_2] = C_IRQ2,
पूर्ण;

अटल u32 kvm_loongson3_priority_to_irq[MIPS_EXC_MAX] = अणु
	[MIPS_EXC_INT_TIMER] = C_IRQ5,
	[MIPS_EXC_INT_IO_1]  = C_IRQ0,
	[MIPS_EXC_INT_IO_2]  = C_IRQ1,
	[MIPS_EXC_INT_IPI_1] = C_IRQ4,
पूर्ण;

u32 *kvm_priority_to_irq = kvm_शेष_priority_to_irq;

u32 kvm_irq_to_priority(u32 irq)
अणु
	पूर्णांक i;

	क्रम (i = MIPS_EXC_INT_TIMER; i < MIPS_EXC_MAX; i++) अणु
		अगर (kvm_priority_to_irq[i] == (1 << (irq + 8)))
			वापस i;
	पूर्ण

	वापस MIPS_EXC_MAX;
पूर्ण

अटल पूर्णांक __init kvm_mips_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (cpu_has_mmid) अणु
		pr_warn("KVM does not yet support MMIDs. KVM Disabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = kvm_mips_entry_setup();
	अगर (ret)
		वापस ret;

	ret = kvm_init(शून्य, माप(काष्ठा kvm_vcpu), 0, THIS_MODULE);

	अगर (ret)
		वापस ret;

	अगर (boot_cpu_type() == CPU_LOONGSON64)
		kvm_priority_to_irq = kvm_loongson3_priority_to_irq;

	रेजिस्टर_die_notअगरier(&kvm_mips_csr_die_notअगरier);

	वापस 0;
पूर्ण

अटल व्योम __निकास kvm_mips_निकास(व्योम)
अणु
	kvm_निकास();

	unरेजिस्टर_die_notअगरier(&kvm_mips_csr_die_notअगरier);
पूर्ण

module_init(kvm_mips_init);
module_निकास(kvm_mips_निकास);

EXPORT_TRACEPOINT_SYMBOL(kvm_निकास);
