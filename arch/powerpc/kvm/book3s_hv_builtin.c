<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/preempt.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sizes.h>
#समावेश <linux/cma.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/smp.h>

#घोषणा KVM_CMA_CHUNK_ORDER	18

#समावेश "book3s_xics.h"
#समावेश "book3s_xive.h"

/*
 * The XIVE module will populate these when it loads
 */
अचिन्हित दीर्घ (*__xive_vm_h_xirr)(काष्ठा kvm_vcpu *vcpu);
अचिन्हित दीर्घ (*__xive_vm_h_ipoll)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server);
पूर्णांक (*__xive_vm_h_ipi)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
		       अचिन्हित दीर्घ mfrr);
पूर्णांक (*__xive_vm_h_cppr)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr);
पूर्णांक (*__xive_vm_h_eoi)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr);
EXPORT_SYMBOL_GPL(__xive_vm_h_xirr);
EXPORT_SYMBOL_GPL(__xive_vm_h_ipoll);
EXPORT_SYMBOL_GPL(__xive_vm_h_ipi);
EXPORT_SYMBOL_GPL(__xive_vm_h_cppr);
EXPORT_SYMBOL_GPL(__xive_vm_h_eoi);

/*
 * Hash page table alignment on newer cpus(CPU_FTR_ARCH_206)
 * should be घातer of 2.
 */
#घोषणा HPT_ALIGN_PAGES		((1 << 18) >> PAGE_SHIFT) /* 256k */
/*
 * By शेष we reserve 5% of memory क्रम hash pagetable allocation.
 */
अटल अचिन्हित दीर्घ kvm_cma_resv_ratio = 5;

अटल काष्ठा cma *kvm_cma;

अटल पूर्णांक __init early_parse_kvm_cma_resv(अक्षर *p)
अणु
	pr_debug("%s(%s)\n", __func__, p);
	अगर (!p)
		वापस -EINVAL;
	वापस kम_से_अदीर्घ(p, 0, &kvm_cma_resv_ratio);
पूर्ण
early_param("kvm_cma_resv_ratio", early_parse_kvm_cma_resv);

काष्ठा page *kvm_alloc_hpt_cma(अचिन्हित दीर्घ nr_pages)
अणु
	VM_BUG_ON(order_base_2(nr_pages) < KVM_CMA_CHUNK_ORDER - PAGE_SHIFT);

	वापस cma_alloc(kvm_cma, nr_pages, order_base_2(HPT_ALIGN_PAGES),
			 false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_alloc_hpt_cma);

व्योम kvm_मुक्त_hpt_cma(काष्ठा page *page, अचिन्हित दीर्घ nr_pages)
अणु
	cma_release(kvm_cma, page, nr_pages);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_मुक्त_hpt_cma);

/**
 * kvm_cma_reserve() - reserve area क्रम kvm hash pagetable
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specअगरic code once the memblock allocator
 * has been activated and all other subप्रणालीs have alपढ़ोy allocated/reserved
 * memory.
 */
व्योम __init kvm_cma_reserve(व्योम)
अणु
	अचिन्हित दीर्घ align_size;
	phys_addr_t selected_size;

	/*
	 * We need CMA reservation only when we are in HV mode
	 */
	अगर (!cpu_has_feature(CPU_FTR_HVMODE))
		वापस;

	selected_size = PAGE_ALIGN(memblock_phys_mem_size() * kvm_cma_resv_ratio / 100);
	अगर (selected_size) अणु
		pr_info("%s: reserving %ld MiB for global area\n", __func__,
			 (अचिन्हित दीर्घ)selected_size / SZ_1M);
		align_size = HPT_ALIGN_PAGES << PAGE_SHIFT;
		cma_declare_contiguous(0, selected_size, 0, align_size,
			KVM_CMA_CHUNK_ORDER - PAGE_SHIFT, false, "kvm_cma",
			&kvm_cma);
	पूर्ण
पूर्ण

/*
 * Real-mode H_CONFER implementation.
 * We check अगर we are the only vcpu out of this भव core
 * still running in the guest and not ceded.  If so, we pop up
 * to the भव-mode implementation; अगर not, just वापस to
 * the guest.
 */
दीर्घ पूर्णांक kvmppc_rm_h_confer(काष्ठा kvm_vcpu *vcpu, पूर्णांक target,
			    अचिन्हित पूर्णांक yield_count)
अणु
	काष्ठा kvmppc_vcore *vc = local_paca->kvm_hstate.kvm_vcore;
	पूर्णांक ptid = local_paca->kvm_hstate.ptid;
	पूर्णांक thपढ़ोs_running;
	पूर्णांक thपढ़ोs_ceded;
	पूर्णांक thपढ़ोs_conferring;
	u64 stop = get_tb() + 10 * tb_ticks_per_usec;
	पूर्णांक rv = H_SUCCESS; /* => करोn't yield */

	set_bit(ptid, &vc->conferring_thपढ़ोs);
	जबतक ((get_tb() < stop) && !VCORE_IS_EXITING(vc)) अणु
		thपढ़ोs_running = VCORE_ENTRY_MAP(vc);
		thपढ़ोs_ceded = vc->napping_thपढ़ोs;
		thपढ़ोs_conferring = vc->conferring_thपढ़ोs;
		अगर ((thपढ़ोs_ceded | thपढ़ोs_conferring) == thपढ़ोs_running) अणु
			rv = H_TOO_HARD; /* => करो yield */
			अवरोध;
		पूर्ण
	पूर्ण
	clear_bit(ptid, &vc->conferring_thपढ़ोs);
	वापस rv;
पूर्ण

/*
 * When running HV mode KVM we need to block certain operations जबतक KVM VMs
 * exist in the प्रणाली. We use a counter of VMs to track this.
 *
 * One of the operations we need to block is onlining of secondaries, so we
 * protect hv_vm_count with get/put_online_cpus().
 */
अटल atomic_t hv_vm_count;

व्योम kvm_hv_vm_activated(व्योम)
अणु
	get_online_cpus();
	atomic_inc(&hv_vm_count);
	put_online_cpus();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_hv_vm_activated);

व्योम kvm_hv_vm_deactivated(व्योम)
अणु
	get_online_cpus();
	atomic_dec(&hv_vm_count);
	put_online_cpus();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_hv_vm_deactivated);

bool kvm_hv_mode_active(व्योम)
अणु
	वापस atomic_पढ़ो(&hv_vm_count) != 0;
पूर्ण

बाह्य पूर्णांक hcall_real_table[], hcall_real_table_end[];

पूर्णांक kvmppc_hcall_impl_hv_realmode(अचिन्हित दीर्घ cmd)
अणु
	cmd /= 4;
	अगर (cmd < hcall_real_table_end - hcall_real_table &&
	    hcall_real_table[cmd])
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_hcall_impl_hv_realmode);

पूर्णांक kvmppc_hwrng_present(व्योम)
अणु
	वापस घातernv_hwrng_present();
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_hwrng_present);

दीर्घ kvmppc_h_अक्रमom(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;

	/* Only need to करो the expensive mfmsr() on radix */
	अगर (kvm_is_radix(vcpu->kvm) && (mfmsr() & MSR_IR))
		r = घातernv_get_अक्रमom_दीर्घ(&vcpu->arch.regs.gpr[4]);
	अन्यथा
		r = घातernv_get_अक्रमom_real_mode(&vcpu->arch.regs.gpr[4]);
	अगर (r)
		वापस H_SUCCESS;

	वापस H_HARDWARE;
पूर्ण

/*
 * Send an पूर्णांकerrupt or message to another CPU.
 * The caller needs to include any barrier needed to order ग_लिखोs
 * to memory vs. the IPI/message.
 */
व्योम kvmhv_rm_send_ipi(पूर्णांक cpu)
अणु
	व्योम __iomem *xics_phys;
	अचिन्हित दीर्घ msg = PPC_DBELL_TYPE(PPC_DBELL_SERVER);

	/* For a nested hypervisor, use the XICS via hcall */
	अगर (kvmhv_on_pseries()) अणु
		अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

		plpar_hcall_raw(H_IPI, retbuf, get_hard_smp_processor_id(cpu),
				IPI_PRIORITY);
		वापस;
	पूर्ण

	/* On POWER9 we can use msgsnd क्रम any destination cpu. */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		msg |= get_hard_smp_processor_id(cpu);
		__यंत्र__ __अस्थिर__ (PPC_MSGSND(%0) : : "r" (msg));
		वापस;
	पूर्ण

	/* On POWER8 क्रम IPIs to thपढ़ोs in the same core, use msgsnd. */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S) &&
	    cpu_first_thपढ़ो_sibling(cpu) ==
	    cpu_first_thपढ़ो_sibling(raw_smp_processor_id())) अणु
		msg |= cpu_thपढ़ो_in_core(cpu);
		__यंत्र__ __अस्थिर__ (PPC_MSGSND(%0) : : "r" (msg));
		वापस;
	पूर्ण

	/* We should never reach this */
	अगर (WARN_ON_ONCE(xics_on_xive()))
	    वापस;

	/* Else poke the target with an IPI */
	xics_phys = paca_ptrs[cpu]->kvm_hstate.xics_phys;
	अगर (xics_phys)
		__raw_rm_ग_लिखोb(IPI_PRIORITY, xics_phys + XICS_MFRR);
	अन्यथा
		opal_पूर्णांक_set_mfrr(get_hard_smp_processor_id(cpu), IPI_PRIORITY);
पूर्ण

/*
 * The following functions are called from the assembly code
 * in book3s_hv_rmhandlers.S.
 */
अटल व्योम kvmhv_पूर्णांकerrupt_vcore(काष्ठा kvmppc_vcore *vc, पूर्णांक active)
अणु
	पूर्णांक cpu = vc->pcpu;

	/* Order setting of निकास map vs. msgsnd/IPI */
	smp_mb();
	क्रम (; active; active >>= 1, ++cpu)
		अगर (active & 1)
			kvmhv_rm_send_ipi(cpu);
पूर्ण

व्योम kvmhv_commence_निकास(पूर्णांक trap)
अणु
	काष्ठा kvmppc_vcore *vc = local_paca->kvm_hstate.kvm_vcore;
	पूर्णांक ptid = local_paca->kvm_hstate.ptid;
	काष्ठा kvm_split_mode *sip = local_paca->kvm_hstate.kvm_split_mode;
	पूर्णांक me, ee, i;

	/* Set our bit in the thपढ़ोs-निकासing-guest map in the 0xff00
	   bits of vcore->entry_निकास_map */
	me = 0x100 << ptid;
	करो अणु
		ee = vc->entry_निकास_map;
	पूर्ण जबतक (cmpxchg(&vc->entry_निकास_map, ee, ee | me) != ee);

	/* Are we the first here? */
	अगर ((ee >> 8) != 0)
		वापस;

	/*
	 * Trigger the other thपढ़ोs in this vcore to निकास the guest.
	 * If this is a hypervisor decrementer पूर्णांकerrupt then they
	 * will be alपढ़ोy on their way out of the guest.
	 */
	अगर (trap != BOOK3S_INTERRUPT_HV_DECREMENTER)
		kvmhv_पूर्णांकerrupt_vcore(vc, ee & ~(1 << ptid));

	/*
	 * If we are करोing dynamic micro-thपढ़ोing, पूर्णांकerrupt the other
	 * subcores to pull them out of their guests too.
	 */
	अगर (!sip)
		वापस;

	क्रम (i = 0; i < MAX_SUBCORES; ++i) अणु
		vc = sip->vc[i];
		अगर (!vc)
			अवरोध;
		करो अणु
			ee = vc->entry_निकास_map;
			/* Alपढ़ोy asked to निकास? */
			अगर ((ee >> 8) != 0)
				अवरोध;
		पूर्ण जबतक (cmpxchg(&vc->entry_निकास_map, ee,
				 ee | VCORE_EXIT_REQ) != ee);
		अगर ((ee >> 8) == 0)
			kvmhv_पूर्णांकerrupt_vcore(vc, ee);
	पूर्ण
पूर्ण

काष्ठा kvmppc_host_rm_ops *kvmppc_host_rm_ops_hv;
EXPORT_SYMBOL_GPL(kvmppc_host_rm_ops_hv);

#अगर_घोषित CONFIG_KVM_XICS
अटल काष्ठा kvmppc_irq_map *get_irqmap(काष्ठा kvmppc_passthru_irqmap *pimap,
					 u32 xisr)
अणु
	पूर्णांक i;

	/*
	 * We access the mapped array here without a lock.  That
	 * is safe because we never reduce the number of entries
	 * in the array and we never change the v_hwirq field of
	 * an entry once it is set.
	 *
	 * We have also carefully ordered the stores in the ग_लिखोr
	 * and the loads here in the पढ़ोer, so that अगर we find a matching
	 * hwirq here, the associated GSI and irq_desc fields are valid.
	 */
	क्रम (i = 0; i < pimap->n_mapped; i++)  अणु
		अगर (xisr == pimap->mapped[i].r_hwirq) अणु
			/*
			 * Order subsequent पढ़ोs in the caller to serialize
			 * with the ग_लिखोr.
			 */
			smp_rmb();
			वापस &pimap->mapped[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * If we have an पूर्णांकerrupt that's not an IPI, check अगर we have a
 * passthrough adapter and अगर so, check अगर this बाह्यal पूर्णांकerrupt
 * is क्रम the adapter.
 * We will attempt to deliver the IRQ directly to the target VCPU's
 * ICP, the भव ICP (based on affinity - the xive value in ICS).
 *
 * If the delivery fails or अगर this is not क्रम a passthrough adapter,
 * वापस to the host to handle this पूर्णांकerrupt. We earlier
 * saved a copy of the XIRR in the PACA, it will be picked up by
 * the host ICP driver.
 */
अटल पूर्णांक kvmppc_check_passthru(u32 xisr, __be32 xirr, bool *again)
अणु
	काष्ठा kvmppc_passthru_irqmap *pimap;
	काष्ठा kvmppc_irq_map *irq_map;
	काष्ठा kvm_vcpu *vcpu;

	vcpu = local_paca->kvm_hstate.kvm_vcpu;
	अगर (!vcpu)
		वापस 1;
	pimap = kvmppc_get_passthru_irqmap(vcpu->kvm);
	अगर (!pimap)
		वापस 1;
	irq_map = get_irqmap(pimap, xisr);
	अगर (!irq_map)
		वापस 1;

	/* We're handling this interrupt, generic code doesn't need to */
	local_paca->kvm_hstate.saved_xirr = 0;

	वापस kvmppc_deliver_irq_passthru(vcpu, xirr, irq_map, pimap, again);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक kvmppc_check_passthru(u32 xisr, __be32 xirr, bool *again)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

/*
 * Determine what sort of बाह्यal पूर्णांकerrupt is pending (अगर any).
 * Returns:
 *	0 अगर no पूर्णांकerrupt is pending
 *	1 अगर an पूर्णांकerrupt is pending that needs to be handled by the host
 *	2 Passthrough that needs completion in the host
 *	-1 अगर there was a guest wakeup IPI (which has now been cleared)
 *	-2 अगर there is PCI passthrough बाह्यal पूर्णांकerrupt that was handled
 */
अटल दीर्घ kvmppc_पढ़ो_one_पूर्णांकr(bool *again);

दीर्घ kvmppc_पढ़ो_पूर्णांकr(व्योम)
अणु
	दीर्घ ret = 0;
	दीर्घ rc;
	bool again;

	अगर (xive_enabled())
		वापस 1;

	करो अणु
		again = false;
		rc = kvmppc_पढ़ो_one_पूर्णांकr(&again);
		अगर (rc && (ret == 0 || rc > ret))
			ret = rc;
	पूर्ण जबतक (again);
	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_पढ़ो_one_पूर्णांकr(bool *again)
अणु
	व्योम __iomem *xics_phys;
	u32 h_xirr;
	__be32 xirr;
	u32 xisr;
	u8 host_ipi;
	पूर्णांक64_t rc;

	अगर (xive_enabled())
		वापस 1;

	/* see अगर a host IPI is pending */
	host_ipi = local_paca->kvm_hstate.host_ipi;
	अगर (host_ipi)
		वापस 1;

	/* Now पढ़ो the पूर्णांकerrupt from the ICP */
	अगर (kvmhv_on_pseries()) अणु
		अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

		rc = plpar_hcall_raw(H_XIRR, retbuf, 0xFF);
		xirr = cpu_to_be32(retbuf[0]);
	पूर्ण अन्यथा अणु
		xics_phys = local_paca->kvm_hstate.xics_phys;
		rc = 0;
		अगर (!xics_phys)
			rc = opal_पूर्णांक_get_xirr(&xirr, false);
		अन्यथा
			xirr = __raw_rm_पढ़ोl(xics_phys + XICS_XIRR);
	पूर्ण
	अगर (rc < 0)
		वापस 1;

	/*
	 * Save XIRR क्रम later. Since we get control in reverse endian
	 * on LE प्रणालीs, save it byte reversed and fetch it back in
	 * host endian. Note that xirr is the value पढ़ो from the
	 * XIRR रेजिस्टर, जबतक h_xirr is the host endian version.
	 */
	h_xirr = be32_to_cpu(xirr);
	local_paca->kvm_hstate.saved_xirr = h_xirr;
	xisr = h_xirr & 0xffffff;
	/*
	 * Ensure that the store/load complete to guarantee all side
	 * effects of loading from XIRR has completed
	 */
	smp_mb();

	/* अगर nothing pending in the ICP */
	अगर (!xisr)
		वापस 0;

	/* We found something in the ICP...
	 *
	 * If it is an IPI, clear the MFRR and EOI it.
	 */
	अगर (xisr == XICS_IPI) अणु
		rc = 0;
		अगर (kvmhv_on_pseries()) अणु
			अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

			plpar_hcall_raw(H_IPI, retbuf,
					hard_smp_processor_id(), 0xff);
			plpar_hcall_raw(H_EOI, retbuf, h_xirr);
		पूर्ण अन्यथा अगर (xics_phys) अणु
			__raw_rm_ग_लिखोb(0xff, xics_phys + XICS_MFRR);
			__raw_rm_ग_लिखोl(xirr, xics_phys + XICS_XIRR);
		पूर्ण अन्यथा अणु
			opal_पूर्णांक_set_mfrr(hard_smp_processor_id(), 0xff);
			rc = opal_पूर्णांक_eoi(h_xirr);
		पूर्ण
		/* If rc > 0, there is another पूर्णांकerrupt pending */
		*again = rc > 0;

		/*
		 * Need to ensure side effects of above stores
		 * complete beक्रमe proceeding.
		 */
		smp_mb();

		/*
		 * We need to re-check host IPI now in हाल it got set in the
		 * meanसमय. If it's clear, we bounce the पूर्णांकerrupt to the
		 * guest
		 */
		host_ipi = local_paca->kvm_hstate.host_ipi;
		अगर (unlikely(host_ipi != 0)) अणु
			/* We raced with the host,
			 * we need to resend that IPI, bummer
			 */
			अगर (kvmhv_on_pseries()) अणु
				अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

				plpar_hcall_raw(H_IPI, retbuf,
						hard_smp_processor_id(),
						IPI_PRIORITY);
			पूर्ण अन्यथा अगर (xics_phys)
				__raw_rm_ग_लिखोb(IPI_PRIORITY,
						xics_phys + XICS_MFRR);
			अन्यथा
				opal_पूर्णांक_set_mfrr(hard_smp_processor_id(),
						  IPI_PRIORITY);
			/* Let side effects complete */
			smp_mb();
			वापस 1;
		पूर्ण

		/* OK, it's an IPI क्रम us */
		local_paca->kvm_hstate.saved_xirr = 0;
		वापस -1;
	पूर्ण

	वापस kvmppc_check_passthru(xisr, xirr, again);
पूर्ण

#अगर_घोषित CONFIG_KVM_XICS
अटल अंतरभूत bool is_rm(व्योम)
अणु
	वापस !(mfmsr() & MSR_DR);
पूर्ण

अचिन्हित दीर्घ kvmppc_rm_h_xirr(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvmppc_xics_enabled(vcpu))
		वापस H_TOO_HARD;
	अगर (xics_on_xive()) अणु
		अगर (is_rm())
			वापस xive_rm_h_xirr(vcpu);
		अगर (unlikely(!__xive_vm_h_xirr))
			वापस H_NOT_AVAILABLE;
		वापस __xive_vm_h_xirr(vcpu);
	पूर्ण अन्यथा
		वापस xics_rm_h_xirr(vcpu);
पूर्ण

अचिन्हित दीर्घ kvmppc_rm_h_xirr_x(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvmppc_xics_enabled(vcpu))
		वापस H_TOO_HARD;
	vcpu->arch.regs.gpr[5] = get_tb();
	अगर (xics_on_xive()) अणु
		अगर (is_rm())
			वापस xive_rm_h_xirr(vcpu);
		अगर (unlikely(!__xive_vm_h_xirr))
			वापस H_NOT_AVAILABLE;
		वापस __xive_vm_h_xirr(vcpu);
	पूर्ण अन्यथा
		वापस xics_rm_h_xirr(vcpu);
पूर्ण

अचिन्हित दीर्घ kvmppc_rm_h_ipoll(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server)
अणु
	अगर (!kvmppc_xics_enabled(vcpu))
		वापस H_TOO_HARD;
	अगर (xics_on_xive()) अणु
		अगर (is_rm())
			वापस xive_rm_h_ipoll(vcpu, server);
		अगर (unlikely(!__xive_vm_h_ipoll))
			वापस H_NOT_AVAILABLE;
		वापस __xive_vm_h_ipoll(vcpu, server);
	पूर्ण अन्यथा
		वापस H_TOO_HARD;
पूर्ण

पूर्णांक kvmppc_rm_h_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
		    अचिन्हित दीर्घ mfrr)
अणु
	अगर (!kvmppc_xics_enabled(vcpu))
		वापस H_TOO_HARD;
	अगर (xics_on_xive()) अणु
		अगर (is_rm())
			वापस xive_rm_h_ipi(vcpu, server, mfrr);
		अगर (unlikely(!__xive_vm_h_ipi))
			वापस H_NOT_AVAILABLE;
		वापस __xive_vm_h_ipi(vcpu, server, mfrr);
	पूर्ण अन्यथा
		वापस xics_rm_h_ipi(vcpu, server, mfrr);
पूर्ण

पूर्णांक kvmppc_rm_h_cppr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr)
अणु
	अगर (!kvmppc_xics_enabled(vcpu))
		वापस H_TOO_HARD;
	अगर (xics_on_xive()) अणु
		अगर (is_rm())
			वापस xive_rm_h_cppr(vcpu, cppr);
		अगर (unlikely(!__xive_vm_h_cppr))
			वापस H_NOT_AVAILABLE;
		वापस __xive_vm_h_cppr(vcpu, cppr);
	पूर्ण अन्यथा
		वापस xics_rm_h_cppr(vcpu, cppr);
पूर्ण

पूर्णांक kvmppc_rm_h_eoi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr)
अणु
	अगर (!kvmppc_xics_enabled(vcpu))
		वापस H_TOO_HARD;
	अगर (xics_on_xive()) अणु
		अगर (is_rm())
			वापस xive_rm_h_eoi(vcpu, xirr);
		अगर (unlikely(!__xive_vm_h_eoi))
			वापस H_NOT_AVAILABLE;
		वापस __xive_vm_h_eoi(vcpu, xirr);
	पूर्ण अन्यथा
		वापस xics_rm_h_eoi(vcpu, xirr);
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XICS */

व्योम kvmppc_bad_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	/*
	 * 100 could happen at any समय, 200 can happen due to invalid real
	 * address access क्रम example (or any समय due to a hardware problem).
	 */
	अगर (TRAP(regs) == 0x100) अणु
		get_paca()->in_nmi++;
		प्रणाली_reset_exception(regs);
		get_paca()->in_nmi--;
	पूर्ण अन्यथा अगर (TRAP(regs) == 0x200) अणु
		machine_check_exception(regs);
	पूर्ण अन्यथा अणु
		die("Bad interrupt in KVM entry/exit code", regs, SIGABRT);
	पूर्ण
	panic("Bad KVM trap");
पूर्ण

अटल व्योम kvmppc_end_cede(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.ceded = 0;
	अगर (vcpu->arch.समयr_running) अणु
		hrसमयr_try_to_cancel(&vcpu->arch.dec_समयr);
		vcpu->arch.समयr_running = 0;
	पूर्ण
पूर्ण

व्योम kvmppc_set_msr_hv(काष्ठा kvm_vcpu *vcpu, u64 msr)
अणु
	/* Guest must always run with ME enabled, HV disabled. */
	msr = (msr | MSR_ME) & ~MSR_HV;

	/*
	 * Check क्रम illegal transactional state bit combination
	 * and अगर we find it, क्रमce the TS field to a safe state.
	 */
	अगर ((msr & MSR_TS_MASK) == MSR_TS_MASK)
		msr &= ~MSR_TS_MASK;
	vcpu->arch.shregs.msr = msr;
	kvmppc_end_cede(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_set_msr_hv);

अटल व्योम inject_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 srr1_flags)
अणु
	अचिन्हित दीर्घ msr, pc, new_msr, new_pc;

	msr = kvmppc_get_msr(vcpu);
	pc = kvmppc_get_pc(vcpu);
	new_msr = vcpu->arch.पूर्णांकr_msr;
	new_pc = vec;

	/* If transactional, change to suspend mode on IRQ delivery */
	अगर (MSR_TM_TRANSACTIONAL(msr))
		new_msr |= MSR_TS_S;
	अन्यथा
		new_msr |= msr & MSR_TS_MASK;

	/*
	 * Perक्रमm MSR and PC adjusपंचांगent क्रम LPCR[AIL]=3 अगर it is set and
	 * applicable. AIL=2 is not supported.
	 *
	 * AIL करोes not apply to SRESET, MCE, or HMI (which is never
	 * delivered to the guest), and करोes not apply अगर IR=0 or DR=0.
	 */
	अगर (vec != BOOK3S_INTERRUPT_SYSTEM_RESET &&
	    vec != BOOK3S_INTERRUPT_MACHINE_CHECK &&
	    (vcpu->arch.vcore->lpcr & LPCR_AIL) == LPCR_AIL_3 &&
	    (msr & (MSR_IR|MSR_DR)) == (MSR_IR|MSR_DR) ) अणु
		new_msr |= MSR_IR | MSR_DR;
		new_pc += 0xC000000000004000ULL;
	पूर्ण

	kvmppc_set_srr0(vcpu, pc);
	kvmppc_set_srr1(vcpu, (msr & SRR1_MSR_BITS) | srr1_flags);
	kvmppc_set_pc(vcpu, new_pc);
	vcpu->arch.shregs.msr = new_msr;
पूर्ण

व्योम kvmppc_inject_पूर्णांकerrupt_hv(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 srr1_flags)
अणु
	inject_पूर्णांकerrupt(vcpu, vec, srr1_flags);
	kvmppc_end_cede(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_inject_पूर्णांकerrupt_hv);

/*
 * Is there a PRIV_DOORBELL pending क्रम the guest (on POWER9)?
 * Can we inject a Decrementer or a External पूर्णांकerrupt?
 */
व्योम kvmppc_guest_entry_inject_पूर्णांक(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ext;
	अचिन्हित दीर्घ lpcr;

	/* Insert EXTERNAL bit पूर्णांकo LPCR at the MER bit position */
	ext = (vcpu->arch.pending_exceptions >> BOOK3S_IRQPRIO_EXTERNAL) & 1;
	lpcr = mfspr(SPRN_LPCR);
	lpcr |= ext << LPCR_MER_SH;
	mtspr(SPRN_LPCR, lpcr);
	isync();

	अगर (vcpu->arch.shregs.msr & MSR_EE) अणु
		अगर (ext) अणु
			inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_EXTERNAL, 0);
		पूर्ण अन्यथा अणु
			दीर्घ पूर्णांक dec = mfspr(SPRN_DEC);
			अगर (!(lpcr & LPCR_LD))
				dec = (पूर्णांक) dec;
			अगर (dec < 0)
				inject_पूर्णांकerrupt(vcpu,
					BOOK3S_INTERRUPT_DECREMENTER, 0);
		पूर्ण
	पूर्ण

	अगर (vcpu->arch.करोorbell_request) अणु
		mtspr(SPRN_DPDES, 1);
		vcpu->arch.vcore->dpdes = 1;
		smp_wmb();
		vcpu->arch.करोorbell_request = 0;
	पूर्ण
पूर्ण

अटल व्योम flush_guest_tlb(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ rb, set;

	rb = PPC_BIT(52);	/* IS = 2 */
	अगर (kvm_is_radix(kvm)) अणु
		/* R=1 PRS=1 RIC=2 */
		यंत्र अस्थिर(PPC_TLBIEL(%0, %4, %3, %2, %1)
			     : : "r" (rb), "i" (1), "i" (1), "i" (2),
			       "r" (0) : "memory");
		क्रम (set = 1; set < kvm->arch.tlb_sets; ++set) अणु
			rb += PPC_BIT(51);	/* increment set number */
			/* R=1 PRS=1 RIC=0 */
			यंत्र अस्थिर(PPC_TLBIEL(%0, %4, %3, %2, %1)
				     : : "r" (rb), "i" (1), "i" (1), "i" (0),
				       "r" (0) : "memory");
		पूर्ण
		यंत्र अस्थिर("ptesync": : :"memory");
		यंत्र अस्थिर(PPC_RADIX_INVALIDATE_ERAT_GUEST : : :"memory");
	पूर्ण अन्यथा अणु
		क्रम (set = 0; set < kvm->arch.tlb_sets; ++set) अणु
			/* R=0 PRS=0 RIC=0 */
			यंत्र अस्थिर(PPC_TLBIEL(%0, %4, %3, %2, %1)
				     : : "r" (rb), "i" (0), "i" (0), "i" (0),
				       "r" (0) : "memory");
			rb += PPC_BIT(51);	/* increment set number */
		पूर्ण
		यंत्र अस्थिर("ptesync": : :"memory");
		यंत्र अस्थिर(PPC_ISA_3_0_INVALIDATE_ERAT : : :"memory");
	पूर्ण
पूर्ण

व्योम kvmppc_check_need_tlb_flush(काष्ठा kvm *kvm, पूर्णांक pcpu,
				 काष्ठा kvm_nested_guest *nested)
अणु
	cpumask_t *need_tlb_flush;

	/*
	 * On POWER9, inभागidual thपढ़ोs can come in here, but the
	 * TLB is shared between the 4 thपढ़ोs in a core, hence
	 * invalidating on one thपढ़ो invalidates क्रम all.
	 * Thus we make all 4 thपढ़ोs use the same bit.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		pcpu = cpu_first_thपढ़ो_sibling(pcpu);

	अगर (nested)
		need_tlb_flush = &nested->need_tlb_flush;
	अन्यथा
		need_tlb_flush = &kvm->arch.need_tlb_flush;

	अगर (cpumask_test_cpu(pcpu, need_tlb_flush)) अणु
		flush_guest_tlb(kvm);

		/* Clear the bit after the TLB flush */
		cpumask_clear_cpu(pcpu, need_tlb_flush);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_check_need_tlb_flush);
