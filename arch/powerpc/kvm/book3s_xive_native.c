<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017-2019, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "xive-kvm: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/file.h>
#समावेश <यंत्र/uaccess.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/xive-regs.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/opal.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश "book3s_xive.h"

अटल u8 xive_vm_esb_load(काष्ठा xive_irq_data *xd, u32 offset)
अणु
	u64 val;

	/*
	 * The KVM XIVE native device करोes not use the XIVE_ESB_SET_PQ_10
	 * load operation, so there is no need to enक्रमce load-after-store
	 * ordering.
	 */

	val = in_be64(xd->eoi_mmio + offset);
	वापस (u8)val;
पूर्ण

अटल व्योम kvmppc_xive_native_cleanup_queue(काष्ठा kvm_vcpu *vcpu, पूर्णांक prio)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा xive_q *q = &xc->queues[prio];

	xive_native_disable_queue(xc->vp_id, q, prio);
	अगर (q->qpage) अणु
		put_page(virt_to_page(q->qpage));
		q->qpage = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_xive_native_configure_queue(u32 vp_id, काष्ठा xive_q *q,
					      u8 prio, __be32 *qpage,
					      u32 order, bool can_escalate)
अणु
	पूर्णांक rc;
	__be32 *qpage_prev = q->qpage;

	rc = xive_native_configure_queue(vp_id, q, prio, qpage, order,
					 can_escalate);
	अगर (rc)
		वापस rc;

	अगर (qpage_prev)
		put_page(virt_to_page(qpage_prev));

	वापस rc;
पूर्ण

व्योम kvmppc_xive_native_cleanup_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	पूर्णांक i;

	अगर (!kvmppc_xive_enabled(vcpu))
		वापस;

	अगर (!xc)
		वापस;

	pr_devel("native_cleanup_vcpu(cpu=%d)\n", xc->server_num);

	/* Ensure no पूर्णांकerrupt is still routed to that VP */
	xc->valid = false;
	kvmppc_xive_disable_vcpu_पूर्णांकerrupts(vcpu);

	/* Free escalations */
	क्रम (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) अणु
		/* Free the escalation irq */
		अगर (xc->esc_virq[i]) अणु
			अगर (xc->xive->single_escalation)
				xive_cleanup_single_escalation(vcpu, xc,
							xc->esc_virq[i]);
			मुक्त_irq(xc->esc_virq[i], vcpu);
			irq_dispose_mapping(xc->esc_virq[i]);
			kमुक्त(xc->esc_virq_names[i]);
			xc->esc_virq[i] = 0;
		पूर्ण
	पूर्ण

	/* Disable the VP */
	xive_native_disable_vp(xc->vp_id);

	/* Clear the cam word so guest entry won't try to push context */
	vcpu->arch.xive_cam_word = 0;

	/* Free the queues */
	क्रम (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) अणु
		kvmppc_xive_native_cleanup_queue(vcpu, i);
	पूर्ण

	/* Free the VP */
	kमुक्त(xc);

	/* Cleanup the vcpu */
	vcpu->arch.irq_type = KVMPPC_IRQ_DEFAULT;
	vcpu->arch.xive_vcpu = शून्य;
पूर्ण

पूर्णांक kvmppc_xive_native_connect_vcpu(काष्ठा kvm_device *dev,
				    काष्ठा kvm_vcpu *vcpu, u32 server_num)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;
	काष्ठा kvmppc_xive_vcpu *xc = शून्य;
	पूर्णांक rc;
	u32 vp_id;

	pr_devel("native_connect_vcpu(server=%d)\n", server_num);

	अगर (dev->ops != &kvm_xive_native_ops) अणु
		pr_devel("Wrong ops !\n");
		वापस -EPERM;
	पूर्ण
	अगर (xive->kvm != vcpu->kvm)
		वापस -EPERM;
	अगर (vcpu->arch.irq_type != KVMPPC_IRQ_DEFAULT)
		वापस -EBUSY;

	mutex_lock(&xive->lock);

	rc = kvmppc_xive_compute_vp_id(xive, server_num, &vp_id);
	अगर (rc)
		जाओ bail;

	xc = kzalloc(माप(*xc), GFP_KERNEL);
	अगर (!xc) अणु
		rc = -ENOMEM;
		जाओ bail;
	पूर्ण

	vcpu->arch.xive_vcpu = xc;
	xc->xive = xive;
	xc->vcpu = vcpu;
	xc->server_num = server_num;

	xc->vp_id = vp_id;
	xc->valid = true;
	vcpu->arch.irq_type = KVMPPC_IRQ_XIVE;

	rc = xive_native_get_vp_info(xc->vp_id, &xc->vp_cam, &xc->vp_chip_id);
	अगर (rc) अणु
		pr_err("Failed to get VP info from OPAL: %d\n", rc);
		जाओ bail;
	पूर्ण

	/*
	 * Enable the VP first as the single escalation mode will
	 * affect escalation पूर्णांकerrupts numbering
	 */
	rc = xive_native_enable_vp(xc->vp_id, xive->single_escalation);
	अगर (rc) अणु
		pr_err("Failed to enable VP in OPAL: %d\n", rc);
		जाओ bail;
	पूर्ण

	/* Configure VCPU fields क्रम use by assembly push/pull */
	vcpu->arch.xive_saved_state.w01 = cpu_to_be64(0xff000000);
	vcpu->arch.xive_cam_word = cpu_to_be32(xc->vp_cam | TM_QW1W2_VO);

	/* TODO: reset all queues to a clean state ? */
bail:
	mutex_unlock(&xive->lock);
	अगर (rc)
		kvmppc_xive_native_cleanup_vcpu(vcpu);

	वापस rc;
पूर्ण

/*
 * Device passthrough support
 */
अटल पूर्णांक kvmppc_xive_native_reset_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ irq)
अणु
	काष्ठा kvmppc_xive *xive = kvm->arch.xive;
	pgoff_t esb_pgoff = KVM_XIVE_ESB_PAGE_OFFSET + irq * 2;

	अगर (irq >= KVMPPC_XIVE_NR_IRQS)
		वापस -EINVAL;

	/*
	 * Clear the ESB pages of the IRQ number being mapped (or
	 * unmapped) पूर्णांकo the guest and let the the VM fault handler
	 * repopulate with the appropriate ESB pages (device or IC)
	 */
	pr_debug("clearing esb pages for girq 0x%lx\n", irq);
	mutex_lock(&xive->mapping_lock);
	अगर (xive->mapping)
		unmap_mapping_range(xive->mapping,
				    esb_pgoff << PAGE_SHIFT,
				    2ull << PAGE_SHIFT, 1);
	mutex_unlock(&xive->mapping_lock);
	वापस 0;
पूर्ण

अटल काष्ठा kvmppc_xive_ops kvmppc_xive_native_ops =  अणु
	.reset_mapped = kvmppc_xive_native_reset_mapped,
पूर्ण;

अटल vm_fault_t xive_native_esb_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा kvm_device *dev = vma->vm_file->निजी_data;
	काष्ठा kvmppc_xive *xive = dev->निजी;
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	काष्ठा xive_irq_data *xd;
	u32 hw_num;
	u16 src;
	u64 page;
	अचिन्हित दीर्घ irq;
	u64 page_offset;

	/*
	 * Linux/KVM uses a two pages ESB setting, one क्रम trigger and
	 * one क्रम EOI
	 */
	page_offset = vmf->pgoff - vma->vm_pgoff;
	irq = page_offset / 2;

	sb = kvmppc_xive_find_source(xive, irq, &src);
	अगर (!sb) अणु
		pr_devel("%s: source %lx not found !\n", __func__, irq);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	state = &sb->irq_state[src];

	/* Some sanity checking */
	अगर (!state->valid) अणु
		pr_devel("%s: source %lx invalid !\n", __func__, irq);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	kvmppc_xive_select_irq(state, &hw_num, &xd);

	arch_spin_lock(&sb->lock);

	/*
	 * first/even page is क्रम trigger
	 * second/odd page is क्रम EOI and management.
	 */
	page = page_offset % 2 ? xd->eoi_page : xd->trig_page;
	arch_spin_unlock(&sb->lock);

	अगर (WARN_ON(!page)) अणु
		pr_err("%s: accessing invalid ESB page for source %lx !\n",
		       __func__, irq);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	vmf_insert_pfn(vma, vmf->address, page >> PAGE_SHIFT);
	वापस VM_FAULT_NOPAGE;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा xive_native_esb_vmops = अणु
	.fault = xive_native_esb_fault,
पूर्ण;

अटल vm_fault_t xive_native_tima_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;

	चयन (vmf->pgoff - vma->vm_pgoff) अणु
	हाल 0: /* HW - क्रमbid access */
	हाल 1: /* HV - क्रमbid access */
		वापस VM_FAULT_SIGBUS;
	हाल 2: /* OS */
		vmf_insert_pfn(vma, vmf->address, xive_tima_os >> PAGE_SHIFT);
		वापस VM_FAULT_NOPAGE;
	हाल 3: /* USER - TODO */
	शेष:
		वापस VM_FAULT_SIGBUS;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा xive_native_tima_vmops = अणु
	.fault = xive_native_tima_fault,
पूर्ण;

अटल पूर्णांक kvmppc_xive_native_mmap(काष्ठा kvm_device *dev,
				   काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;

	/* We only allow mappings at fixed offset क्रम now */
	अगर (vma->vm_pgoff == KVM_XIVE_TIMA_PAGE_OFFSET) अणु
		अगर (vma_pages(vma) > 4)
			वापस -EINVAL;
		vma->vm_ops = &xive_native_tima_vmops;
	पूर्ण अन्यथा अगर (vma->vm_pgoff == KVM_XIVE_ESB_PAGE_OFFSET) अणु
		अगर (vma_pages(vma) > KVMPPC_XIVE_NR_IRQS * 2)
			वापस -EINVAL;
		vma->vm_ops = &xive_native_esb_vmops;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);

	/*
	 * Grab the KVM device file address_space to be able to clear
	 * the ESB pages mapping when a device is passed-through पूर्णांकo
	 * the guest.
	 */
	xive->mapping = vma->vm_file->f_mapping;
	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_set_source(काष्ठा kvmppc_xive *xive, दीर्घ irq,
					 u64 addr)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u64 __user *ubufp = (u64 __user *) addr;
	u64 val;
	u16 idx;
	पूर्णांक rc;

	pr_devel("%s irq=0x%lx\n", __func__, irq);

	अगर (irq < KVMPPC_XIVE_FIRST_IRQ || irq >= KVMPPC_XIVE_NR_IRQS)
		वापस -E2BIG;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	अगर (!sb) अणु
		pr_debug("No source, creating source block...\n");
		sb = kvmppc_xive_create_src_block(xive, irq);
		अगर (!sb) अणु
			pr_err("Failed to create block...\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	state = &sb->irq_state[idx];

	अगर (get_user(val, ubufp)) अणु
		pr_err("fault getting user info !\n");
		वापस -EFAULT;
	पूर्ण

	arch_spin_lock(&sb->lock);

	/*
	 * If the source करोesn't alपढ़ोy have an IPI, allocate
	 * one and get the corresponding data
	 */
	अगर (!state->ipi_number) अणु
		state->ipi_number = xive_native_alloc_irq();
		अगर (state->ipi_number == 0) अणु
			pr_err("Failed to allocate IRQ !\n");
			rc = -ENXIO;
			जाओ unlock;
		पूर्ण
		xive_native_populate_irq_data(state->ipi_number,
					      &state->ipi_data);
		pr_debug("%s allocated hw_irq=0x%x for irq=0x%lx\n", __func__,
			 state->ipi_number, irq);
	पूर्ण

	/* Restore LSI state */
	अगर (val & KVM_XIVE_LEVEL_SENSITIVE) अणु
		state->lsi = true;
		अगर (val & KVM_XIVE_LEVEL_ASSERTED)
			state->निश्चितed = true;
		pr_devel("  LSI ! Asserted=%d\n", state->निश्चितed);
	पूर्ण

	/* Mask IRQ to start with */
	state->act_server = 0;
	state->act_priority = MASKED;
	xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);
	xive_native_configure_irq(state->ipi_number, 0, MASKED, 0);

	/* Increment the number of valid sources and mark this one valid */
	अगर (!state->valid)
		xive->src_count++;
	state->valid = true;

	rc = 0;

unlock:
	arch_spin_unlock(&sb->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_update_source_config(काष्ठा kvmppc_xive *xive,
					काष्ठा kvmppc_xive_src_block *sb,
					काष्ठा kvmppc_xive_irq_state *state,
					u32 server, u8 priority, bool masked,
					u32 eisn)
अणु
	काष्ठा kvm *kvm = xive->kvm;
	u32 hw_num;
	पूर्णांक rc = 0;

	arch_spin_lock(&sb->lock);

	अगर (state->act_server == server && state->act_priority == priority &&
	    state->eisn == eisn)
		जाओ unlock;

	pr_devel("new_act_prio=%d new_act_server=%d mask=%d act_server=%d act_prio=%d\n",
		 priority, server, masked, state->act_server,
		 state->act_priority);

	kvmppc_xive_select_irq(state, &hw_num, शून्य);

	अगर (priority != MASKED && !masked) अणु
		rc = kvmppc_xive_select_target(kvm, &server, priority);
		अगर (rc)
			जाओ unlock;

		state->act_priority = priority;
		state->act_server = server;
		state->eisn = eisn;

		rc = xive_native_configure_irq(hw_num,
					       kvmppc_xive_vp(xive, server),
					       priority, eisn);
	पूर्ण अन्यथा अणु
		state->act_priority = MASKED;
		state->act_server = 0;
		state->eisn = 0;

		rc = xive_native_configure_irq(hw_num, 0, MASKED, 0);
	पूर्ण

unlock:
	arch_spin_unlock(&sb->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_set_source_config(काष्ठा kvmppc_xive *xive,
						दीर्घ irq, u64 addr)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	u64 __user *ubufp = (u64 __user *) addr;
	u16 src;
	u64 kvm_cfg;
	u32 server;
	u8 priority;
	bool masked;
	u32 eisn;

	sb = kvmppc_xive_find_source(xive, irq, &src);
	अगर (!sb)
		वापस -ENOENT;

	state = &sb->irq_state[src];

	अगर (!state->valid)
		वापस -EINVAL;

	अगर (get_user(kvm_cfg, ubufp))
		वापस -EFAULT;

	pr_devel("%s irq=0x%lx cfg=%016llx\n", __func__, irq, kvm_cfg);

	priority = (kvm_cfg & KVM_XIVE_SOURCE_PRIORITY_MASK) >>
		KVM_XIVE_SOURCE_PRIORITY_SHIFT;
	server = (kvm_cfg & KVM_XIVE_SOURCE_SERVER_MASK) >>
		KVM_XIVE_SOURCE_SERVER_SHIFT;
	masked = (kvm_cfg & KVM_XIVE_SOURCE_MASKED_MASK) >>
		KVM_XIVE_SOURCE_MASKED_SHIFT;
	eisn = (kvm_cfg & KVM_XIVE_SOURCE_EISN_MASK) >>
		KVM_XIVE_SOURCE_EISN_SHIFT;

	अगर (priority != xive_prio_from_guest(priority)) अणु
		pr_err("invalid priority for queue %d for VCPU %d\n",
		       priority, server);
		वापस -EINVAL;
	पूर्ण

	वापस kvmppc_xive_native_update_source_config(xive, sb, state, server,
						       priority, masked, eisn);
पूर्ण

अटल पूर्णांक kvmppc_xive_native_sync_source(काष्ठा kvmppc_xive *xive,
					  दीर्घ irq, u64 addr)
अणु
	काष्ठा kvmppc_xive_src_block *sb;
	काष्ठा kvmppc_xive_irq_state *state;
	काष्ठा xive_irq_data *xd;
	u32 hw_num;
	u16 src;
	पूर्णांक rc = 0;

	pr_devel("%s irq=0x%lx", __func__, irq);

	sb = kvmppc_xive_find_source(xive, irq, &src);
	अगर (!sb)
		वापस -ENOENT;

	state = &sb->irq_state[src];

	rc = -EINVAL;

	arch_spin_lock(&sb->lock);

	अगर (state->valid) अणु
		kvmppc_xive_select_irq(state, &hw_num, &xd);
		xive_native_sync_source(hw_num);
		rc = 0;
	पूर्ण

	arch_spin_unlock(&sb->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक xive_native_validate_queue_size(u32 qshअगरt)
अणु
	/*
	 * We only support 64K pages क्रम the moment. This is also
	 * advertised in the DT property "ibm,xive-eq-sizes"
	 */
	चयन (qshअगरt) अणु
	हाल 0: /* EQ reset */
	हाल 16:
		वापस 0;
	हाल 12:
	हाल 21:
	हाल 24:
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_xive_native_set_queue_config(काष्ठा kvmppc_xive *xive,
					       दीर्घ eq_idx, u64 addr)
अणु
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvmppc_xive_vcpu *xc;
	व्योम __user *ubufp = (व्योम __user *) addr;
	u32 server;
	u8 priority;
	काष्ठा kvm_ppc_xive_eq kvm_eq;
	पूर्णांक rc;
	__be32 *qaddr = 0;
	काष्ठा page *page;
	काष्ठा xive_q *q;
	gfn_t gfn;
	अचिन्हित दीर्घ page_size;
	पूर्णांक srcu_idx;

	/*
	 * Demangle priority/server tuple from the EQ identअगरier
	 */
	priority = (eq_idx & KVM_XIVE_EQ_PRIORITY_MASK) >>
		KVM_XIVE_EQ_PRIORITY_SHIFT;
	server = (eq_idx & KVM_XIVE_EQ_SERVER_MASK) >>
		KVM_XIVE_EQ_SERVER_SHIFT;

	अगर (copy_from_user(&kvm_eq, ubufp, माप(kvm_eq)))
		वापस -EFAULT;

	vcpu = kvmppc_xive_find_server(kvm, server);
	अगर (!vcpu) अणु
		pr_err("Can't find server %d\n", server);
		वापस -ENOENT;
	पूर्ण
	xc = vcpu->arch.xive_vcpu;

	अगर (priority != xive_prio_from_guest(priority)) अणु
		pr_err("Trying to restore invalid queue %d for VCPU %d\n",
		       priority, server);
		वापस -EINVAL;
	पूर्ण
	q = &xc->queues[priority];

	pr_devel("%s VCPU %d priority %d fl:%x shift:%d addr:%llx g:%d idx:%d\n",
		 __func__, server, priority, kvm_eq.flags,
		 kvm_eq.qshअगरt, kvm_eq.qaddr, kvm_eq.qtoggle, kvm_eq.qindex);

	/* reset queue and disable queueing */
	अगर (!kvm_eq.qshअगरt) अणु
		q->guest_qaddr  = 0;
		q->guest_qshअगरt = 0;

		rc = kvmppc_xive_native_configure_queue(xc->vp_id, q, priority,
							शून्य, 0, true);
		अगर (rc) अणु
			pr_err("Failed to reset queue %d for VCPU %d: %d\n",
			       priority, xc->server_num, rc);
			वापस rc;
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 * sPAPR specअगरies a "Unconditional Notify (n) flag" क्रम the
	 * H_INT_SET_QUEUE_CONFIG hcall which क्रमces notअगरication
	 * without using the coalescing mechanisms provided by the
	 * XIVE END ESBs. This is required on KVM as notअगरication
	 * using the END ESBs is not supported.
	 */
	अगर (kvm_eq.flags != KVM_XIVE_EQ_ALWAYS_NOTIFY) अणु
		pr_err("invalid flags %d\n", kvm_eq.flags);
		वापस -EINVAL;
	पूर्ण

	rc = xive_native_validate_queue_size(kvm_eq.qshअगरt);
	अगर (rc) अणु
		pr_err("invalid queue size %d\n", kvm_eq.qshअगरt);
		वापस rc;
	पूर्ण

	अगर (kvm_eq.qaddr & ((1ull << kvm_eq.qshअगरt) - 1)) अणु
		pr_err("queue page is not aligned %llx/%llx\n", kvm_eq.qaddr,
		       1ull << kvm_eq.qshअगरt);
		वापस -EINVAL;
	पूर्ण

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	gfn = gpa_to_gfn(kvm_eq.qaddr);

	page_size = kvm_host_page_size(vcpu, gfn);
	अगर (1ull << kvm_eq.qshअगरt > page_size) अणु
		srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
		pr_warn("Incompatible host page size %lx!\n", page_size);
		वापस -EINVAL;
	पूर्ण

	page = gfn_to_page(kvm, gfn);
	अगर (is_error_page(page)) अणु
		srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
		pr_err("Couldn't get queue page %llx!\n", kvm_eq.qaddr);
		वापस -EINVAL;
	पूर्ण

	qaddr = page_to_virt(page) + (kvm_eq.qaddr & ~PAGE_MASK);
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	/*
	 * Backup the queue page guest address to the mark EQ page
	 * dirty क्रम migration.
	 */
	q->guest_qaddr  = kvm_eq.qaddr;
	q->guest_qshअगरt = kvm_eq.qshअगरt;

	 /*
	  * Unconditional Notअगरication is क्रमced by शेष at the
	  * OPAL level because the use of END ESBs is not supported by
	  * Linux.
	  */
	rc = kvmppc_xive_native_configure_queue(xc->vp_id, q, priority,
					(__be32 *) qaddr, kvm_eq.qshअगरt, true);
	अगर (rc) अणु
		pr_err("Failed to configure queue %d for VCPU %d: %d\n",
		       priority, xc->server_num, rc);
		put_page(page);
		वापस rc;
	पूर्ण

	/*
	 * Only restore the queue state when needed. When करोing the
	 * H_INT_SET_SOURCE_CONFIG hcall, it should not.
	 */
	अगर (kvm_eq.qtoggle != 1 || kvm_eq.qindex != 0) अणु
		rc = xive_native_set_queue_state(xc->vp_id, priority,
						 kvm_eq.qtoggle,
						 kvm_eq.qindex);
		अगर (rc)
			जाओ error;
	पूर्ण

	rc = kvmppc_xive_attach_escalation(vcpu, priority,
					   xive->single_escalation);
error:
	अगर (rc)
		kvmppc_xive_native_cleanup_queue(vcpu, priority);
	वापस rc;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_get_queue_config(काष्ठा kvmppc_xive *xive,
					       दीर्घ eq_idx, u64 addr)
अणु
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvmppc_xive_vcpu *xc;
	काष्ठा xive_q *q;
	व्योम __user *ubufp = (u64 __user *) addr;
	u32 server;
	u8 priority;
	काष्ठा kvm_ppc_xive_eq kvm_eq;
	u64 qaddr;
	u64 qshअगरt;
	u64 qeoi_page;
	u32 escalate_irq;
	u64 qflags;
	पूर्णांक rc;

	/*
	 * Demangle priority/server tuple from the EQ identअगरier
	 */
	priority = (eq_idx & KVM_XIVE_EQ_PRIORITY_MASK) >>
		KVM_XIVE_EQ_PRIORITY_SHIFT;
	server = (eq_idx & KVM_XIVE_EQ_SERVER_MASK) >>
		KVM_XIVE_EQ_SERVER_SHIFT;

	vcpu = kvmppc_xive_find_server(kvm, server);
	अगर (!vcpu) अणु
		pr_err("Can't find server %d\n", server);
		वापस -ENOENT;
	पूर्ण
	xc = vcpu->arch.xive_vcpu;

	अगर (priority != xive_prio_from_guest(priority)) अणु
		pr_err("invalid priority for queue %d for VCPU %d\n",
		       priority, server);
		वापस -EINVAL;
	पूर्ण
	q = &xc->queues[priority];

	स_रखो(&kvm_eq, 0, माप(kvm_eq));

	अगर (!q->qpage)
		वापस 0;

	rc = xive_native_get_queue_info(xc->vp_id, priority, &qaddr, &qshअगरt,
					&qeoi_page, &escalate_irq, &qflags);
	अगर (rc)
		वापस rc;

	kvm_eq.flags = 0;
	अगर (qflags & OPAL_XIVE_EQ_ALWAYS_NOTIFY)
		kvm_eq.flags |= KVM_XIVE_EQ_ALWAYS_NOTIFY;

	kvm_eq.qshअगरt = q->guest_qshअगरt;
	kvm_eq.qaddr  = q->guest_qaddr;

	rc = xive_native_get_queue_state(xc->vp_id, priority, &kvm_eq.qtoggle,
					 &kvm_eq.qindex);
	अगर (rc)
		वापस rc;

	pr_devel("%s VCPU %d priority %d fl:%x shift:%d addr:%llx g:%d idx:%d\n",
		 __func__, server, priority, kvm_eq.flags,
		 kvm_eq.qshअगरt, kvm_eq.qaddr, kvm_eq.qtoggle, kvm_eq.qindex);

	अगर (copy_to_user(ubufp, &kvm_eq, माप(kvm_eq)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम kvmppc_xive_reset_sources(काष्ठा kvmppc_xive_src_block *sb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) अणु
		काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[i];

		अगर (!state->valid)
			जारी;

		अगर (state->act_priority == MASKED)
			जारी;

		state->eisn = 0;
		state->act_server = 0;
		state->act_priority = MASKED;
		xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);
		xive_native_configure_irq(state->ipi_number, 0, MASKED, 0);
		अगर (state->pt_number) अणु
			xive_vm_esb_load(state->pt_data, XIVE_ESB_SET_PQ_01);
			xive_native_configure_irq(state->pt_number,
						  0, MASKED, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_xive_reset(काष्ठा kvmppc_xive *xive)
अणु
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित पूर्णांक i;

	pr_devel("%s\n", __func__);

	mutex_lock(&xive->lock);

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
		अचिन्हित पूर्णांक prio;

		अगर (!xc)
			जारी;

		kvmppc_xive_disable_vcpu_पूर्णांकerrupts(vcpu);

		क्रम (prio = 0; prio < KVMPPC_XIVE_Q_COUNT; prio++) अणु

			/* Single escalation, no queue 7 */
			अगर (prio == 7 && xive->single_escalation)
				अवरोध;

			अगर (xc->esc_virq[prio]) अणु
				मुक्त_irq(xc->esc_virq[prio], vcpu);
				irq_dispose_mapping(xc->esc_virq[prio]);
				kमुक्त(xc->esc_virq_names[prio]);
				xc->esc_virq[prio] = 0;
			पूर्ण

			kvmppc_xive_native_cleanup_queue(vcpu, prio);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];

		अगर (sb) अणु
			arch_spin_lock(&sb->lock);
			kvmppc_xive_reset_sources(sb);
			arch_spin_unlock(&sb->lock);
		पूर्ण
	पूर्ण

	mutex_unlock(&xive->lock);

	वापस 0;
पूर्ण

अटल व्योम kvmppc_xive_native_sync_sources(काष्ठा kvmppc_xive_src_block *sb)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < KVMPPC_XICS_IRQ_PER_ICS; j++) अणु
		काष्ठा kvmppc_xive_irq_state *state = &sb->irq_state[j];
		काष्ठा xive_irq_data *xd;
		u32 hw_num;

		अगर (!state->valid)
			जारी;

		/*
		 * The काष्ठा kvmppc_xive_irq_state reflects the state
		 * of the EAS configuration and not the state of the
		 * source. The source is masked setting the PQ bits to
		 * '-Q', which is what is being करोne beक्रमe calling
		 * the KVM_DEV_XIVE_EQ_SYNC control.
		 *
		 * If a source EAS is configured, OPAL syncs the XIVE
		 * IC of the source and the XIVE IC of the previous
		 * target अगर any.
		 *
		 * So it should be fine ignoring MASKED sources as
		 * they have been synced alपढ़ोy.
		 */
		अगर (state->act_priority == MASKED)
			जारी;

		kvmppc_xive_select_irq(state, &hw_num, &xd);
		xive_native_sync_source(hw_num);
		xive_native_sync_queue(hw_num);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_xive_native_vcpu_eq_sync(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	अचिन्हित पूर्णांक prio;
	पूर्णांक srcu_idx;

	अगर (!xc)
		वापस -ENOENT;

	क्रम (prio = 0; prio < KVMPPC_XIVE_Q_COUNT; prio++) अणु
		काष्ठा xive_q *q = &xc->queues[prio];

		अगर (!q->qpage)
			जारी;

		/* Mark EQ page dirty क्रम migration */
		srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		mark_page_dirty(vcpu->kvm, gpa_to_gfn(q->guest_qaddr));
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_eq_sync(काष्ठा kvmppc_xive *xive)
अणु
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित पूर्णांक i;

	pr_devel("%s\n", __func__);

	mutex_lock(&xive->lock);
	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];

		अगर (sb) अणु
			arch_spin_lock(&sb->lock);
			kvmppc_xive_native_sync_sources(sb);
			arch_spin_unlock(&sb->lock);
		पूर्ण
	पूर्ण

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		kvmppc_xive_native_vcpu_eq_sync(vcpu);
	पूर्ण
	mutex_unlock(&xive->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_set_attr(काष्ठा kvm_device *dev,
				       काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;

	चयन (attr->group) अणु
	हाल KVM_DEV_XIVE_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_XIVE_RESET:
			वापस kvmppc_xive_reset(xive);
		हाल KVM_DEV_XIVE_EQ_SYNC:
			वापस kvmppc_xive_native_eq_sync(xive);
		हाल KVM_DEV_XIVE_NR_SERVERS:
			वापस kvmppc_xive_set_nr_servers(xive, attr->addr);
		पूर्ण
		अवरोध;
	हाल KVM_DEV_XIVE_GRP_SOURCE:
		वापस kvmppc_xive_native_set_source(xive, attr->attr,
						     attr->addr);
	हाल KVM_DEV_XIVE_GRP_SOURCE_CONFIG:
		वापस kvmppc_xive_native_set_source_config(xive, attr->attr,
							    attr->addr);
	हाल KVM_DEV_XIVE_GRP_EQ_CONFIG:
		वापस kvmppc_xive_native_set_queue_config(xive, attr->attr,
							   attr->addr);
	हाल KVM_DEV_XIVE_GRP_SOURCE_SYNC:
		वापस kvmppc_xive_native_sync_source(xive, attr->attr,
						      attr->addr);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_get_attr(काष्ठा kvm_device *dev,
				       काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;

	चयन (attr->group) अणु
	हाल KVM_DEV_XIVE_GRP_EQ_CONFIG:
		वापस kvmppc_xive_native_get_queue_config(xive, attr->attr,
							   attr->addr);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक kvmppc_xive_native_has_attr(काष्ठा kvm_device *dev,
				       काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_XIVE_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_XIVE_RESET:
		हाल KVM_DEV_XIVE_EQ_SYNC:
		हाल KVM_DEV_XIVE_NR_SERVERS:
			वापस 0;
		पूर्ण
		अवरोध;
	हाल KVM_DEV_XIVE_GRP_SOURCE:
	हाल KVM_DEV_XIVE_GRP_SOURCE_CONFIG:
	हाल KVM_DEV_XIVE_GRP_SOURCE_SYNC:
		अगर (attr->attr >= KVMPPC_XIVE_FIRST_IRQ &&
		    attr->attr < KVMPPC_XIVE_NR_IRQS)
			वापस 0;
		अवरोध;
	हाल KVM_DEV_XIVE_GRP_EQ_CONFIG:
		वापस 0;
	पूर्ण
	वापस -ENXIO;
पूर्ण

/*
 * Called when device fd is बंदd.  kvm->lock is held.
 */
अटल व्योम kvmppc_xive_native_release(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvmppc_xive *xive = dev->निजी;
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	pr_devel("Releasing xive native device\n");

	/*
	 * Clear the KVM device file address_space which is used to
	 * unmap the ESB pages when a device is passed-through.
	 */
	mutex_lock(&xive->mapping_lock);
	xive->mapping = शून्य;
	mutex_unlock(&xive->mapping_lock);

	/*
	 * Since this is the device release function, we know that
	 * userspace करोes not have any खोलो fd or mmap referring to
	 * the device.  Thereक्रमe there can not be any of the
	 * device attribute set/get, mmap, or page fault functions
	 * being executed concurrently, and similarly, the
	 * connect_vcpu and set/clr_mapped functions also cannot
	 * be being executed.
	 */

	debugfs_हटाओ(xive->dentry);

	/*
	 * We should clean up the vCPU पूर्णांकerrupt presenters first.
	 */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		/*
		 * Take vcpu->mutex to ensure that no one_reg get/set ioctl
		 * (i.e. kvmppc_xive_native_[gs]et_vp) can be being करोne.
		 * Holding the vcpu->mutex also means that the vcpu cannot
		 * be executing the KVM_RUN ioctl, and thereक्रमe it cannot
		 * be executing the XIVE push or pull code or accessing
		 * the XIVE MMIO regions.
		 */
		mutex_lock(&vcpu->mutex);
		kvmppc_xive_native_cleanup_vcpu(vcpu);
		mutex_unlock(&vcpu->mutex);
	पूर्ण

	/*
	 * Now that we have cleared vcpu->arch.xive_vcpu, vcpu->arch.irq_type
	 * and vcpu->arch.xive_esc_[vr]addr on each vcpu, we are safe
	 * against xive code getting called during vcpu execution or
	 * set/get one_reg operations.
	 */
	kvm->arch.xive = शून्य;

	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		अगर (xive->src_blocks[i])
			kvmppc_xive_मुक्त_sources(xive->src_blocks[i]);
		kमुक्त(xive->src_blocks[i]);
		xive->src_blocks[i] = शून्य;
	पूर्ण

	अगर (xive->vp_base != XIVE_INVALID_VP)
		xive_native_मुक्त_vp_block(xive->vp_base);

	/*
	 * A reference of the kvmppc_xive poपूर्णांकer is now kept under
	 * the xive_devices काष्ठा of the machine क्रम reuse. It is
	 * मुक्तd when the VM is destroyed क्रम now until we fix all the
	 * execution paths.
	 */

	kमुक्त(dev);
पूर्ण

/*
 * Create a XIVE device.  kvm->lock is held.
 */
अटल पूर्णांक kvmppc_xive_native_create(काष्ठा kvm_device *dev, u32 type)
अणु
	काष्ठा kvmppc_xive *xive;
	काष्ठा kvm *kvm = dev->kvm;

	pr_devel("Creating xive native device\n");

	अगर (kvm->arch.xive)
		वापस -EEXIST;

	xive = kvmppc_xive_get_device(kvm, type);
	अगर (!xive)
		वापस -ENOMEM;

	dev->निजी = xive;
	xive->dev = dev;
	xive->kvm = kvm;
	mutex_init(&xive->mapping_lock);
	mutex_init(&xive->lock);

	/* VP allocation is delayed to the first call to connect_vcpu */
	xive->vp_base = XIVE_INVALID_VP;
	/* KVM_MAX_VCPUS limits the number of VMs to roughly 64 per sockets
	 * on a POWER9 प्रणाली.
	 */
	xive->nr_servers = KVM_MAX_VCPUS;

	xive->single_escalation = xive_native_has_single_escalation();
	xive->ops = &kvmppc_xive_native_ops;

	kvm->arch.xive = xive;
	वापस 0;
पूर्ण

/*
 * Interrupt Pending Buffer (IPB) offset
 */
#घोषणा TM_IPB_SHIFT 40
#घोषणा TM_IPB_MASK  (((u64) 0xFF) << TM_IPB_SHIFT)

पूर्णांक kvmppc_xive_native_get_vp(काष्ठा kvm_vcpu *vcpu, जोड़ kvmppc_one_reg *val)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	u64 opal_state;
	पूर्णांक rc;

	अगर (!kvmppc_xive_enabled(vcpu))
		वापस -EPERM;

	अगर (!xc)
		वापस -ENOENT;

	/* Thपढ़ो context रेजिस्टरs. We only care about IPB and CPPR */
	val->xive_timaval[0] = vcpu->arch.xive_saved_state.w01;

	/* Get the VP state from OPAL */
	rc = xive_native_get_vp_state(xc->vp_id, &opal_state);
	अगर (rc)
		वापस rc;

	/*
	 * Capture the backup of IPB रेजिस्टर in the NVT काष्ठाure and
	 * merge it in our KVM VP state.
	 */
	val->xive_timaval[0] |= cpu_to_be64(opal_state & TM_IPB_MASK);

	pr_devel("%s NSR=%02x CPPR=%02x IBP=%02x PIPR=%02x w01=%016llx w2=%08x opal=%016llx\n",
		 __func__,
		 vcpu->arch.xive_saved_state.nsr,
		 vcpu->arch.xive_saved_state.cppr,
		 vcpu->arch.xive_saved_state.ipb,
		 vcpu->arch.xive_saved_state.pipr,
		 vcpu->arch.xive_saved_state.w01,
		 (u32) vcpu->arch.xive_cam_word, opal_state);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_xive_native_set_vp(काष्ठा kvm_vcpu *vcpu, जोड़ kvmppc_one_reg *val)
अणु
	काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	काष्ठा kvmppc_xive *xive = vcpu->kvm->arch.xive;

	pr_devel("%s w01=%016llx vp=%016llx\n", __func__,
		 val->xive_timaval[0], val->xive_timaval[1]);

	अगर (!kvmppc_xive_enabled(vcpu))
		वापस -EPERM;

	अगर (!xc || !xive)
		वापस -ENOENT;

	/* We can't update the state of a "pushed" VCPU	 */
	अगर (WARN_ON(vcpu->arch.xive_pushed))
		वापस -EBUSY;

	/*
	 * Restore the thपढ़ो context रेजिस्टरs. IPB and CPPR should
	 * be the only ones that matter.
	 */
	vcpu->arch.xive_saved_state.w01 = val->xive_timaval[0];

	/*
	 * There is no need to restore the XIVE पूर्णांकernal state (IPB
	 * stored in the NVT) as the IPB रेजिस्टर was merged in KVM VP
	 * state when captured.
	 */
	वापस 0;
पूर्ण

bool kvmppc_xive_native_supported(व्योम)
अणु
	वापस xive_native_has_queue_state_support();
पूर्ण

अटल पूर्णांक xive_native_debug_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा kvmppc_xive *xive = m->निजी;
	काष्ठा kvm *kvm = xive->kvm;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित पूर्णांक i;

	अगर (!kvm)
		वापस 0;

	seq_माला_दो(m, "=========\nVCPU state\n=========\n");

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;

		अगर (!xc)
			जारी;

		seq_म_लिखो(m, "VCPU %d: VP=%#x/%02x\n"
			   "    NSR=%02x CPPR=%02x IBP=%02x PIPR=%02x w01=%016llx w2=%08x\n",
			   xc->server_num, xc->vp_id, xc->vp_chip_id,
			   vcpu->arch.xive_saved_state.nsr,
			   vcpu->arch.xive_saved_state.cppr,
			   vcpu->arch.xive_saved_state.ipb,
			   vcpu->arch.xive_saved_state.pipr,
			   be64_to_cpu(vcpu->arch.xive_saved_state.w01),
			   be32_to_cpu(vcpu->arch.xive_cam_word));

		kvmppc_xive_debug_show_queues(m, vcpu);
	पूर्ण

	seq_माला_दो(m, "=========\nSources\n=========\n");

	क्रम (i = 0; i <= xive->max_sbid; i++) अणु
		काष्ठा kvmppc_xive_src_block *sb = xive->src_blocks[i];

		अगर (sb) अणु
			arch_spin_lock(&sb->lock);
			kvmppc_xive_debug_show_sources(m, sb);
			arch_spin_unlock(&sb->lock);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(xive_native_debug);

अटल व्योम xive_native_debugfs_init(काष्ठा kvmppc_xive *xive)
अणु
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "kvm-xive-%p", xive);
	अगर (!name) अणु
		pr_err("%s: no memory for name\n", __func__);
		वापस;
	पूर्ण

	xive->dentry = debugfs_create_file(name, 0444, घातerpc_debugfs_root,
					   xive, &xive_native_debug_fops);

	pr_debug("%s: created %s\n", __func__, name);
	kमुक्त(name);
पूर्ण

अटल व्योम kvmppc_xive_native_init(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvmppc_xive *xive = (काष्ठा kvmppc_xive *)dev->निजी;

	/* Register some debug पूर्णांकerfaces */
	xive_native_debugfs_init(xive);
पूर्ण

काष्ठा kvm_device_ops kvm_xive_native_ops = अणु
	.name = "kvm-xive-native",
	.create = kvmppc_xive_native_create,
	.init = kvmppc_xive_native_init,
	.release = kvmppc_xive_native_release,
	.set_attr = kvmppc_xive_native_set_attr,
	.get_attr = kvmppc_xive_native_get_attr,
	.has_attr = kvmppc_xive_native_has_attr,
	.mmap = kvmppc_xive_native_mmap,
पूर्ण;

व्योम kvmppc_xive_native_init_module(व्योम)
अणु
	;
पूर्ण

व्योम kvmppc_xive_native_निकास_module(व्योम)
अणु
	;
पूर्ण
