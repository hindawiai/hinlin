<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * AMD SVM support
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Avi Kivity   <avi@qumranet.com>
 */

#घोषणा pr_fmt(fmt) "SVM: " fmt

#समावेश <linux/kvm_types.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/amd-iommu.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/irq_remapping.h>

#समावेश "trace.h"
#समावेश "lapic.h"
#समावेश "x86.h"
#समावेश "irq.h"
#समावेश "svm.h"

/* enable / disable AVIC */
bool avic;
module_param(avic, bool, S_IRUGO);

#घोषणा SVM_AVIC_DOORBELL	0xc001011b

#घोषणा AVIC_HPA_MASK	~((0xFFFULL << 52) | 0xFFF)

/*
 * 0xff is broadcast, so the max index allowed क्रम physical APIC ID
 * table is 0xfe.  APIC IDs above 0xff are reserved.
 */
#घोषणा AVIC_MAX_PHYSICAL_ID_COUNT	255

#घोषणा AVIC_UNACCEL_ACCESS_WRITE_MASK		1
#घोषणा AVIC_UNACCEL_ACCESS_OFFSET_MASK		0xFF0
#घोषणा AVIC_UNACCEL_ACCESS_VECTOR_MASK		0xFFFFFFFF

/* AVIC GATAG is encoded using VM and VCPU IDs */
#घोषणा AVIC_VCPU_ID_BITS		8
#घोषणा AVIC_VCPU_ID_MASK		((1 << AVIC_VCPU_ID_BITS) - 1)

#घोषणा AVIC_VM_ID_BITS			24
#घोषणा AVIC_VM_ID_NR			(1 << AVIC_VM_ID_BITS)
#घोषणा AVIC_VM_ID_MASK			((1 << AVIC_VM_ID_BITS) - 1)

#घोषणा AVIC_GATAG(x, y)		(((x & AVIC_VM_ID_MASK) << AVIC_VCPU_ID_BITS) | \
						(y & AVIC_VCPU_ID_MASK))
#घोषणा AVIC_GATAG_TO_VMID(x)		((x >> AVIC_VCPU_ID_BITS) & AVIC_VM_ID_MASK)
#घोषणा AVIC_GATAG_TO_VCPUID(x)		(x & AVIC_VCPU_ID_MASK)

/* Note:
 * This hash table is used to map VM_ID to a काष्ठा kvm_svm,
 * when handling AMD IOMMU GALOG notअगरication to schedule in
 * a particular vCPU.
 */
#घोषणा SVM_VM_DATA_HASH_BITS	8
अटल DEFINE_HASHTABLE(svm_vm_data_hash, SVM_VM_DATA_HASH_BITS);
अटल u32 next_vm_id = 0;
अटल bool next_vm_id_wrapped = 0;
अटल DEFINE_SPINLOCK(svm_vm_data_hash_lock);

/*
 * This is a wrapper of काष्ठा amd_iommu_ir_data.
 */
काष्ठा amd_svm_iommu_ir अणु
	काष्ठा list_head node;	/* Used by SVM क्रम per-vcpu ir_list */
	व्योम *data;		/* Storing poपूर्णांकer to काष्ठा amd_ir_data */
पूर्ण;

क्रमागत avic_ipi_failure_cause अणु
	AVIC_IPI_FAILURE_INVALID_INT_TYPE,
	AVIC_IPI_FAILURE_TARGET_NOT_RUNNING,
	AVIC_IPI_FAILURE_INVALID_TARGET,
	AVIC_IPI_FAILURE_INVALID_BACKING_PAGE,
पूर्ण;

/* Note:
 * This function is called from IOMMU driver to notअगरy
 * SVM to schedule in a particular vCPU of a particular VM.
 */
पूर्णांक avic_ga_log_notअगरier(u32 ga_tag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kvm_svm *kvm_svm;
	काष्ठा kvm_vcpu *vcpu = शून्य;
	u32 vm_id = AVIC_GATAG_TO_VMID(ga_tag);
	u32 vcpu_id = AVIC_GATAG_TO_VCPUID(ga_tag);

	pr_debug("SVM: %s: vm_id=%#x, vcpu_id=%#x\n", __func__, vm_id, vcpu_id);
	trace_kvm_avic_ga_log(vm_id, vcpu_id);

	spin_lock_irqsave(&svm_vm_data_hash_lock, flags);
	hash_क्रम_each_possible(svm_vm_data_hash, kvm_svm, hnode, vm_id) अणु
		अगर (kvm_svm->avic_vm_id != vm_id)
			जारी;
		vcpu = kvm_get_vcpu_by_id(&kvm_svm->kvm, vcpu_id);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&svm_vm_data_hash_lock, flags);

	/* Note:
	 * At this poपूर्णांक, the IOMMU should have alपढ़ोy set the pending
	 * bit in the vAPIC backing page. So, we just need to schedule
	 * in the vcpu.
	 */
	अगर (vcpu)
		kvm_vcpu_wake_up(vcpu);

	वापस 0;
पूर्ण

व्योम avic_vm_destroy(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kvm_svm *kvm_svm = to_kvm_svm(kvm);

	अगर (!avic)
		वापस;

	अगर (kvm_svm->avic_logical_id_table_page)
		__मुक्त_page(kvm_svm->avic_logical_id_table_page);
	अगर (kvm_svm->avic_physical_id_table_page)
		__मुक्त_page(kvm_svm->avic_physical_id_table_page);

	spin_lock_irqsave(&svm_vm_data_hash_lock, flags);
	hash_del(&kvm_svm->hnode);
	spin_unlock_irqrestore(&svm_vm_data_hash_lock, flags);
पूर्ण

पूर्णांक avic_vm_init(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -ENOMEM;
	काष्ठा kvm_svm *kvm_svm = to_kvm_svm(kvm);
	काष्ठा kvm_svm *k2;
	काष्ठा page *p_page;
	काष्ठा page *l_page;
	u32 vm_id;

	अगर (!avic)
		वापस 0;

	/* Allocating physical APIC ID table (4KB) */
	p_page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!p_page)
		जाओ मुक्त_avic;

	kvm_svm->avic_physical_id_table_page = p_page;

	/* Allocating logical APIC ID table (4KB) */
	l_page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!l_page)
		जाओ मुक्त_avic;

	kvm_svm->avic_logical_id_table_page = l_page;

	spin_lock_irqsave(&svm_vm_data_hash_lock, flags);
 again:
	vm_id = next_vm_id = (next_vm_id + 1) & AVIC_VM_ID_MASK;
	अगर (vm_id == 0) अणु /* id is 1-based, zero is not okay */
		next_vm_id_wrapped = 1;
		जाओ again;
	पूर्ण
	/* Is it still in use? Only possible अगर wrapped at least once */
	अगर (next_vm_id_wrapped) अणु
		hash_क्रम_each_possible(svm_vm_data_hash, k2, hnode, vm_id) अणु
			अगर (k2->avic_vm_id == vm_id)
				जाओ again;
		पूर्ण
	पूर्ण
	kvm_svm->avic_vm_id = vm_id;
	hash_add(svm_vm_data_hash, &kvm_svm->hnode, kvm_svm->avic_vm_id);
	spin_unlock_irqrestore(&svm_vm_data_hash_lock, flags);

	वापस 0;

मुक्त_avic:
	avic_vm_destroy(kvm);
	वापस err;
पूर्ण

व्योम avic_init_vmcb(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb;
	काष्ठा kvm_svm *kvm_svm = to_kvm_svm(svm->vcpu.kvm);
	phys_addr_t bpa = __sme_set(page_to_phys(svm->avic_backing_page));
	phys_addr_t lpa = __sme_set(page_to_phys(kvm_svm->avic_logical_id_table_page));
	phys_addr_t ppa = __sme_set(page_to_phys(kvm_svm->avic_physical_id_table_page));

	vmcb->control.avic_backing_page = bpa & AVIC_HPA_MASK;
	vmcb->control.avic_logical_id = lpa & AVIC_HPA_MASK;
	vmcb->control.avic_physical_id = ppa & AVIC_HPA_MASK;
	vmcb->control.avic_physical_id |= AVIC_MAX_PHYSICAL_ID_COUNT;
	अगर (kvm_apicv_activated(svm->vcpu.kvm))
		vmcb->control.पूर्णांक_ctl |= AVIC_ENABLE_MASK;
	अन्यथा
		vmcb->control.पूर्णांक_ctl &= ~AVIC_ENABLE_MASK;
पूर्ण

अटल u64 *avic_get_physical_id_entry(काष्ठा kvm_vcpu *vcpu,
				       अचिन्हित पूर्णांक index)
अणु
	u64 *avic_physical_id_table;
	काष्ठा kvm_svm *kvm_svm = to_kvm_svm(vcpu->kvm);

	अगर (index >= AVIC_MAX_PHYSICAL_ID_COUNT)
		वापस शून्य;

	avic_physical_id_table = page_address(kvm_svm->avic_physical_id_table_page);

	वापस &avic_physical_id_table[index];
पूर्ण

/*
 * Note:
 * AVIC hardware walks the nested page table to check permissions,
 * but करोes not use the SPA address specअगरied in the leaf page
 * table entry since it uses  address in the AVIC_BACKING_PAGE poपूर्णांकer
 * field of the VMCB. Thereक्रमe, we set up the
 * APIC_ACCESS_PAGE_PRIVATE_MEMSLOT (4KB) here.
 */
अटल पूर्णांक avic_update_access_page(काष्ठा kvm *kvm, bool activate)
अणु
	व्योम __user *ret;
	पूर्णांक r = 0;

	mutex_lock(&kvm->slots_lock);
	/*
	 * During kvm_destroy_vm(), kvm_pit_set_reinject() could trigger
	 * APICv mode change, which update APIC_ACCESS_PAGE_PRIVATE_MEMSLOT
	 * memory region. So, we need to ensure that kvm->mm == current->mm.
	 */
	अगर ((kvm->arch.apic_access_page_करोne == activate) ||
	    (kvm->mm != current->mm))
		जाओ out;

	ret = __x86_set_memory_region(kvm,
				      APIC_ACCESS_PAGE_PRIVATE_MEMSLOT,
				      APIC_DEFAULT_PHYS_BASE,
				      activate ? PAGE_SIZE : 0);
	अगर (IS_ERR(ret)) अणु
		r = PTR_ERR(ret);
		जाओ out;
	पूर्ण

	kvm->arch.apic_access_page_करोne = activate;
out:
	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण

अटल पूर्णांक avic_init_backing_page(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 *entry, new_entry;
	पूर्णांक id = vcpu->vcpu_id;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (id >= AVIC_MAX_PHYSICAL_ID_COUNT)
		वापस -EINVAL;

	अगर (!vcpu->arch.apic->regs)
		वापस -EINVAL;

	अगर (kvm_apicv_activated(vcpu->kvm)) अणु
		पूर्णांक ret;

		ret = avic_update_access_page(vcpu->kvm, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	svm->avic_backing_page = virt_to_page(vcpu->arch.apic->regs);

	/* Setting AVIC backing page address in the phy APIC ID table */
	entry = avic_get_physical_id_entry(vcpu, id);
	अगर (!entry)
		वापस -EINVAL;

	new_entry = __sme_set((page_to_phys(svm->avic_backing_page) &
			      AVIC_PHYSICAL_ID_ENTRY_BACKING_PAGE_MASK) |
			      AVIC_PHYSICAL_ID_ENTRY_VALID_MASK);
	WRITE_ONCE(*entry, new_entry);

	svm->avic_physical_id_cache = entry;

	वापस 0;
पूर्ण

अटल व्योम avic_kick_target_vcpus(काष्ठा kvm *kvm, काष्ठा kvm_lapic *source,
				   u32 icrl, u32 icrh)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		bool m = kvm_apic_match_dest(vcpu, source,
					     icrl & APIC_SHORT_MASK,
					     GET_APIC_DEST_FIELD(icrh),
					     icrl & APIC_DEST_MASK);

		अगर (m && !avic_vcpu_is_running(vcpu))
			kvm_vcpu_wake_up(vcpu);
	पूर्ण
पूर्ण

पूर्णांक avic_incomplete_ipi_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 icrh = svm->vmcb->control.निकास_info_1 >> 32;
	u32 icrl = svm->vmcb->control.निकास_info_1;
	u32 id = svm->vmcb->control.निकास_info_2 >> 32;
	u32 index = svm->vmcb->control.निकास_info_2 & 0xFF;
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	trace_kvm_avic_incomplete_ipi(vcpu->vcpu_id, icrh, icrl, id, index);

	चयन (id) अणु
	हाल AVIC_IPI_FAILURE_INVALID_INT_TYPE:
		/*
		 * AVIC hardware handles the generation of
		 * IPIs when the specअगरied Message Type is Fixed
		 * (also known as fixed delivery mode) and
		 * the Trigger Mode is edge-triggered. The hardware
		 * also supports self and broadcast delivery modes
		 * specअगरied via the Destination Shorthand(DSH)
		 * field of the ICRL. Logical and physical APIC ID
		 * क्रमmats are supported. All other IPI types cause
		 * a #VMEXIT, which needs to emulated.
		 */
		kvm_lapic_reg_ग_लिखो(apic, APIC_ICR2, icrh);
		kvm_lapic_reg_ग_लिखो(apic, APIC_ICR, icrl);
		अवरोध;
	हाल AVIC_IPI_FAILURE_TARGET_NOT_RUNNING:
		/*
		 * At this poपूर्णांक, we expect that the AVIC HW has alपढ़ोy
		 * set the appropriate IRR bits on the valid target
		 * vcpus. So, we just need to kick the appropriate vcpu.
		 */
		avic_kick_target_vcpus(vcpu->kvm, apic, icrl, icrh);
		अवरोध;
	हाल AVIC_IPI_FAILURE_INVALID_TARGET:
		WARN_ONCE(1, "Invalid IPI target: index=%u, vcpu=%d, icr=%#0x:%#0x\n",
			  index, vcpu->vcpu_id, icrh, icrl);
		अवरोध;
	हाल AVIC_IPI_FAILURE_INVALID_BACKING_PAGE:
		WARN_ONCE(1, "Invalid backing page\n");
		अवरोध;
	शेष:
		pr_err("Unknown IPI interception\n");
	पूर्ण

	वापस 1;
पूर्ण

अटल u32 *avic_get_logical_id_entry(काष्ठा kvm_vcpu *vcpu, u32 ldr, bool flat)
अणु
	काष्ठा kvm_svm *kvm_svm = to_kvm_svm(vcpu->kvm);
	पूर्णांक index;
	u32 *logical_apic_id_table;
	पूर्णांक dlid = GET_APIC_LOGICAL_ID(ldr);

	अगर (!dlid)
		वापस शून्य;

	अगर (flat) अणु /* flat */
		index = ffs(dlid) - 1;
		अगर (index > 7)
			वापस शून्य;
	पूर्ण अन्यथा अणु /* cluster */
		पूर्णांक cluster = (dlid & 0xf0) >> 4;
		पूर्णांक apic = ffs(dlid & 0x0f) - 1;

		अगर ((apic < 0) || (apic > 7) ||
		    (cluster >= 0xf))
			वापस शून्य;
		index = (cluster << 2) + apic;
	पूर्ण

	logical_apic_id_table = (u32 *) page_address(kvm_svm->avic_logical_id_table_page);

	वापस &logical_apic_id_table[index];
पूर्ण

अटल पूर्णांक avic_ldr_ग_लिखो(काष्ठा kvm_vcpu *vcpu, u8 g_physical_id, u32 ldr)
अणु
	bool flat;
	u32 *entry, new_entry;

	flat = kvm_lapic_get_reg(vcpu->arch.apic, APIC_DFR) == APIC_DFR_FLAT;
	entry = avic_get_logical_id_entry(vcpu, ldr, flat);
	अगर (!entry)
		वापस -EINVAL;

	new_entry = READ_ONCE(*entry);
	new_entry &= ~AVIC_LOGICAL_ID_ENTRY_GUEST_PHYSICAL_ID_MASK;
	new_entry |= (g_physical_id & AVIC_LOGICAL_ID_ENTRY_GUEST_PHYSICAL_ID_MASK);
	new_entry |= AVIC_LOGICAL_ID_ENTRY_VALID_MASK;
	WRITE_ONCE(*entry, new_entry);

	वापस 0;
पूर्ण

अटल व्योम avic_invalidate_logical_id_entry(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	bool flat = svm->dfr_reg == APIC_DFR_FLAT;
	u32 *entry = avic_get_logical_id_entry(vcpu, svm->ldr_reg, flat);

	अगर (entry)
		clear_bit(AVIC_LOGICAL_ID_ENTRY_VALID_BIT, (अचिन्हित दीर्घ *)entry);
पूर्ण

अटल पूर्णांक avic_handle_ldr_update(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret = 0;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 ldr = kvm_lapic_get_reg(vcpu->arch.apic, APIC_LDR);
	u32 id = kvm_xapic_id(vcpu->arch.apic);

	अगर (ldr == svm->ldr_reg)
		वापस 0;

	avic_invalidate_logical_id_entry(vcpu);

	अगर (ldr)
		ret = avic_ldr_ग_लिखो(vcpu, id, ldr);

	अगर (!ret)
		svm->ldr_reg = ldr;

	वापस ret;
पूर्ण

अटल पूर्णांक avic_handle_apic_id_update(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 *old, *new;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 id = kvm_xapic_id(vcpu->arch.apic);

	अगर (vcpu->vcpu_id == id)
		वापस 0;

	old = avic_get_physical_id_entry(vcpu, vcpu->vcpu_id);
	new = avic_get_physical_id_entry(vcpu, id);
	अगर (!new || !old)
		वापस 1;

	/* We need to move physical_id_entry to new offset */
	*new = *old;
	*old = 0ULL;
	to_svm(vcpu)->avic_physical_id_cache = new;

	/*
	 * Also update the guest physical APIC ID in the logical
	 * APIC ID table entry अगर alपढ़ोy setup the LDR.
	 */
	अगर (svm->ldr_reg)
		avic_handle_ldr_update(vcpu);

	वापस 0;
पूर्ण

अटल व्योम avic_handle_dfr_update(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 dfr = kvm_lapic_get_reg(vcpu->arch.apic, APIC_DFR);

	अगर (svm->dfr_reg == dfr)
		वापस;

	avic_invalidate_logical_id_entry(vcpu);
	svm->dfr_reg = dfr;
पूर्ण

अटल पूर्णांक avic_unaccel_trap_ग_लिखो(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा kvm_lapic *apic = svm->vcpu.arch.apic;
	u32 offset = svm->vmcb->control.निकास_info_1 &
				AVIC_UNACCEL_ACCESS_OFFSET_MASK;

	चयन (offset) अणु
	हाल APIC_ID:
		अगर (avic_handle_apic_id_update(&svm->vcpu))
			वापस 0;
		अवरोध;
	हाल APIC_LDR:
		अगर (avic_handle_ldr_update(&svm->vcpu))
			वापस 0;
		अवरोध;
	हाल APIC_DFR:
		avic_handle_dfr_update(&svm->vcpu);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kvm_lapic_reg_ग_लिखो(apic, offset, kvm_lapic_get_reg(apic, offset));

	वापस 1;
पूर्ण

अटल bool is_avic_unaccelerated_access_trap(u32 offset)
अणु
	bool ret = false;

	चयन (offset) अणु
	हाल APIC_ID:
	हाल APIC_EOI:
	हाल APIC_RRR:
	हाल APIC_LDR:
	हाल APIC_DFR:
	हाल APIC_SPIV:
	हाल APIC_ESR:
	हाल APIC_ICR:
	हाल APIC_LVTT:
	हाल APIC_LVTTHMR:
	हाल APIC_LVTPC:
	हाल APIC_LVT0:
	हाल APIC_LVT1:
	हाल APIC_LVTERR:
	हाल APIC_TMICT:
	हाल APIC_TDCR:
		ret = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक avic_unaccelerated_access_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक ret = 0;
	u32 offset = svm->vmcb->control.निकास_info_1 &
		     AVIC_UNACCEL_ACCESS_OFFSET_MASK;
	u32 vector = svm->vmcb->control.निकास_info_2 &
		     AVIC_UNACCEL_ACCESS_VECTOR_MASK;
	bool ग_लिखो = (svm->vmcb->control.निकास_info_1 >> 32) &
		     AVIC_UNACCEL_ACCESS_WRITE_MASK;
	bool trap = is_avic_unaccelerated_access_trap(offset);

	trace_kvm_avic_unaccelerated_access(vcpu->vcpu_id, offset,
					    trap, ग_लिखो, vector);
	अगर (trap) अणु
		/* Handling Trap */
		WARN_ONCE(!ग_लिखो, "svm: Handling trap read.\n");
		ret = avic_unaccel_trap_ग_लिखो(svm);
	पूर्ण अन्यथा अणु
		/* Handling Fault */
		ret = kvm_emulate_inकाष्ठाion(vcpu, 0);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक avic_init_vcpu(काष्ठा vcpu_svm *svm)
अणु
	पूर्णांक ret;
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;

	अगर (!avic || !irqchip_in_kernel(vcpu->kvm))
		वापस 0;

	ret = avic_init_backing_page(vcpu);
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&svm->ir_list);
	spin_lock_init(&svm->ir_list_lock);
	svm->dfr_reg = APIC_DFR_FLAT;

	वापस ret;
पूर्ण

व्योम avic_post_state_restore(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (avic_handle_apic_id_update(vcpu) != 0)
		वापस;
	avic_handle_dfr_update(vcpu);
	avic_handle_ldr_update(vcpu);
पूर्ण

व्योम svm_toggle_avic_क्रम_irq_winकरोw(काष्ठा kvm_vcpu *vcpu, bool activate)
अणु
	अगर (!avic || !lapic_in_kernel(vcpu))
		वापस;

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	kvm_request_apicv_update(vcpu->kvm, activate,
				 APICV_INHIBIT_REASON_IRQWIN);
	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
पूर्ण

व्योम svm_set_भव_apic_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस;
पूर्ण

व्योम svm_hwapic_irr_update(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_irr)
अणु
पूर्ण

व्योम svm_hwapic_isr_update(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_isr)
अणु
पूर्ण

अटल पूर्णांक svm_set_pi_irte_mode(काष्ठा kvm_vcpu *vcpu, bool activate)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_svm_iommu_ir *ir;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (!kvm_arch_has_asचिन्हित_device(vcpu->kvm))
		वापस 0;

	/*
	 * Here, we go through the per-vcpu ir_list to update all existing
	 * पूर्णांकerrupt remapping table entry targeting this vcpu.
	 */
	spin_lock_irqsave(&svm->ir_list_lock, flags);

	अगर (list_empty(&svm->ir_list))
		जाओ out;

	list_क्रम_each_entry(ir, &svm->ir_list, node) अणु
		अगर (activate)
			ret = amd_iommu_activate_guest_mode(ir->data);
		अन्यथा
			ret = amd_iommu_deactivate_guest_mode(ir->data);
		अगर (ret)
			अवरोध;
	पूर्ण
out:
	spin_unlock_irqrestore(&svm->ir_list_lock, flags);
	वापस ret;
पूर्ण

व्योम svm_refresh_apicv_exec_ctrl(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb *vmcb = svm->vmcb;
	bool activated = kvm_vcpu_apicv_active(vcpu);

	अगर (!avic)
		वापस;

	अगर (activated) अणु
		/**
		 * During AVIC temporary deactivation, guest could update
		 * APIC ID, DFR and LDR रेजिस्टरs, which would not be trapped
		 * by avic_unaccelerated_access_पूर्णांकerception(). In this हाल,
		 * we need to check and update the AVIC logical APIC ID table
		 * accordingly beक्रमe re-activating.
		 */
		avic_post_state_restore(vcpu);
		vmcb->control.पूर्णांक_ctl |= AVIC_ENABLE_MASK;
	पूर्ण अन्यथा अणु
		vmcb->control.पूर्णांक_ctl &= ~AVIC_ENABLE_MASK;
	पूर्ण
	vmcb_mark_dirty(vmcb, VMCB_AVIC);

	svm_set_pi_irte_mode(vcpu, activated);
पूर्ण

व्योम svm_load_eoi_निकासmap(काष्ठा kvm_vcpu *vcpu, u64 *eoi_निकास_biपंचांगap)
अणु
	वापस;
पूर्ण

पूर्णांक svm_deliver_avic_पूर्णांकr(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec)
अणु
	अगर (!vcpu->arch.apicv_active)
		वापस -1;

	kvm_lapic_set_irr(vec, vcpu->arch.apic);
	smp_mb__after_atomic();

	अगर (avic_vcpu_is_running(vcpu)) अणु
		पूर्णांक cpuid = vcpu->cpu;

		अगर (cpuid != get_cpu())
			wrmsrl(SVM_AVIC_DOORBELL, kvm_cpu_get_apicid(cpuid));
		put_cpu();
	पूर्ण अन्यथा
		kvm_vcpu_wake_up(vcpu);

	वापस 0;
पूर्ण

bool svm_dy_apicv_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण

अटल व्योम svm_ir_list_del(काष्ठा vcpu_svm *svm, काष्ठा amd_iommu_pi_data *pi)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amd_svm_iommu_ir *cur;

	spin_lock_irqsave(&svm->ir_list_lock, flags);
	list_क्रम_each_entry(cur, &svm->ir_list, node) अणु
		अगर (cur->data != pi->ir_data)
			जारी;
		list_del(&cur->node);
		kमुक्त(cur);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&svm->ir_list_lock, flags);
पूर्ण

अटल पूर्णांक svm_ir_list_add(काष्ठा vcpu_svm *svm, काष्ठा amd_iommu_pi_data *pi)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_svm_iommu_ir *ir;

	/**
	 * In some हालs, the existing irte is updated and re-set,
	 * so we need to check here अगर it's alपढ़ोy been * added
	 * to the ir_list.
	 */
	अगर (pi->ir_data && (pi->prev_ga_tag != 0)) अणु
		काष्ठा kvm *kvm = svm->vcpu.kvm;
		u32 vcpu_id = AVIC_GATAG_TO_VCPUID(pi->prev_ga_tag);
		काष्ठा kvm_vcpu *prev_vcpu = kvm_get_vcpu_by_id(kvm, vcpu_id);
		काष्ठा vcpu_svm *prev_svm;

		अगर (!prev_vcpu) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		prev_svm = to_svm(prev_vcpu);
		svm_ir_list_del(prev_svm, pi);
	पूर्ण

	/**
	 * Allocating new amd_iommu_pi_data, which will get
	 * add to the per-vcpu ir_list.
	 */
	ir = kzalloc(माप(काष्ठा amd_svm_iommu_ir), GFP_KERNEL_ACCOUNT);
	अगर (!ir) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ir->data = pi->ir_data;

	spin_lock_irqsave(&svm->ir_list_lock, flags);
	list_add(&ir->node, &svm->ir_list);
	spin_unlock_irqrestore(&svm->ir_list_lock, flags);
out:
	वापस ret;
पूर्ण

/*
 * Note:
 * The HW cannot support posting multicast/broadcast
 * पूर्णांकerrupts to a vCPU. So, we still use legacy पूर्णांकerrupt
 * remapping क्रम these kind of पूर्णांकerrupts.
 *
 * For lowest-priority पूर्णांकerrupts, we only support
 * those with single CPU as the destination, e.g. user
 * configures the पूर्णांकerrupts via /proc/irq or uses
 * irqbalance to make the पूर्णांकerrupts single-CPU.
 */
अटल पूर्णांक
get_pi_vcpu_info(काष्ठा kvm *kvm, काष्ठा kvm_kernel_irq_routing_entry *e,
		 काष्ठा vcpu_data *vcpu_info, काष्ठा vcpu_svm **svm)
अणु
	काष्ठा kvm_lapic_irq irq;
	काष्ठा kvm_vcpu *vcpu = शून्य;

	kvm_set_msi_irq(kvm, e, &irq);

	अगर (!kvm_पूर्णांकr_is_single_vcpu(kvm, &irq, &vcpu) ||
	    !kvm_irq_is_postable(&irq)) अणु
		pr_debug("SVM: %s: use legacy intr remap mode for irq %u\n",
			 __func__, irq.vector);
		वापस -1;
	पूर्ण

	pr_debug("SVM: %s: use GA mode for irq %u\n", __func__,
		 irq.vector);
	*svm = to_svm(vcpu);
	vcpu_info->pi_desc_addr = __sme_set(page_to_phys((*svm)->avic_backing_page));
	vcpu_info->vector = irq.vector;

	वापस 0;
पूर्ण

/*
 * svm_update_pi_irte - set IRTE क्रम Posted-Interrupts
 *
 * @kvm: kvm
 * @host_irq: host irq of the पूर्णांकerrupt
 * @guest_irq: gsi of the पूर्णांकerrupt
 * @set: set or unset PI
 * वापसs 0 on success, < 0 on failure
 */
पूर्णांक svm_update_pi_irte(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq,
		       uपूर्णांक32_t guest_irq, bool set)
अणु
	काष्ठा kvm_kernel_irq_routing_entry *e;
	काष्ठा kvm_irq_routing_table *irq_rt;
	पूर्णांक idx, ret = -EINVAL;

	अगर (!kvm_arch_has_asचिन्हित_device(kvm) ||
	    !irq_remapping_cap(IRQ_POSTING_CAP))
		वापस 0;

	pr_debug("SVM: %s: host_irq=%#x, guest_irq=%#x, set=%#x\n",
		 __func__, host_irq, guest_irq, set);

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	irq_rt = srcu_dereference(kvm->irq_routing, &kvm->irq_srcu);
	WARN_ON(guest_irq >= irq_rt->nr_rt_entries);

	hlist_क्रम_each_entry(e, &irq_rt->map[guest_irq], link) अणु
		काष्ठा vcpu_data vcpu_info;
		काष्ठा vcpu_svm *svm = शून्य;

		अगर (e->type != KVM_IRQ_ROUTING_MSI)
			जारी;

		/**
		 * Here, we setup with legacy mode in the following हालs:
		 * 1. When cannot target पूर्णांकerrupt to a specअगरic vcpu.
		 * 2. Unsetting posted पूर्णांकerrupt.
		 * 3. APIC भवization is disabled क्रम the vcpu.
		 * 4. IRQ has incompatible delivery mode (SMI, INIT, etc)
		 */
		अगर (!get_pi_vcpu_info(kvm, e, &vcpu_info, &svm) && set &&
		    kvm_vcpu_apicv_active(&svm->vcpu)) अणु
			काष्ठा amd_iommu_pi_data pi;

			/* Try to enable guest_mode in IRTE */
			pi.base = __sme_set(page_to_phys(svm->avic_backing_page) &
					    AVIC_HPA_MASK);
			pi.ga_tag = AVIC_GATAG(to_kvm_svm(kvm)->avic_vm_id,
						     svm->vcpu.vcpu_id);
			pi.is_guest_mode = true;
			pi.vcpu_data = &vcpu_info;
			ret = irq_set_vcpu_affinity(host_irq, &pi);

			/**
			 * Here, we successfully setting up vcpu affinity in
			 * IOMMU guest mode. Now, we need to store the posted
			 * पूर्णांकerrupt inक्रमmation in a per-vcpu ir_list so that
			 * we can reference to them directly when we update vcpu
			 * scheduling inक्रमmation in IOMMU irte.
			 */
			अगर (!ret && pi.is_guest_mode)
				svm_ir_list_add(svm, &pi);
		पूर्ण अन्यथा अणु
			/* Use legacy mode in IRTE */
			काष्ठा amd_iommu_pi_data pi;

			/**
			 * Here, pi is used to:
			 * - Tell IOMMU to use legacy mode क्रम this पूर्णांकerrupt.
			 * - Retrieve ga_tag of prior पूर्णांकerrupt remapping data.
			 */
			pi.prev_ga_tag = 0;
			pi.is_guest_mode = false;
			ret = irq_set_vcpu_affinity(host_irq, &pi);

			/**
			 * Check अगर the posted पूर्णांकerrupt was previously
			 * setup with the guest_mode by checking अगर the ga_tag
			 * was cached. If so, we need to clean up the per-vcpu
			 * ir_list.
			 */
			अगर (!ret && pi.prev_ga_tag) अणु
				पूर्णांक id = AVIC_GATAG_TO_VCPUID(pi.prev_ga_tag);
				काष्ठा kvm_vcpu *vcpu;

				vcpu = kvm_get_vcpu_by_id(kvm, id);
				अगर (vcpu)
					svm_ir_list_del(to_svm(vcpu), &pi);
			पूर्ण
		पूर्ण

		अगर (!ret && svm) अणु
			trace_kvm_pi_irte_update(host_irq, svm->vcpu.vcpu_id,
						 e->gsi, vcpu_info.vector,
						 vcpu_info.pi_desc_addr, set);
		पूर्ण

		अगर (ret < 0) अणु
			pr_err("%s: failed to update PI IRTE\n", __func__);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
	वापस ret;
पूर्ण

bool svm_check_apicv_inhibit_reasons(uदीर्घ bit)
अणु
	uदीर्घ supported = BIT(APICV_INHIBIT_REASON_DISABLE) |
			  BIT(APICV_INHIBIT_REASON_HYPERV) |
			  BIT(APICV_INHIBIT_REASON_NESTED) |
			  BIT(APICV_INHIBIT_REASON_IRQWIN) |
			  BIT(APICV_INHIBIT_REASON_PIT_REINJ) |
			  BIT(APICV_INHIBIT_REASON_X2APIC);

	वापस supported & BIT(bit);
पूर्ण

व्योम svm_pre_update_apicv_exec_ctrl(काष्ठा kvm *kvm, bool activate)
अणु
	avic_update_access_page(kvm, activate);
पूर्ण

अटल अंतरभूत पूर्णांक
avic_update_iommu_vcpu_affinity(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu, bool r)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_svm_iommu_ir *ir;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (!kvm_arch_has_asचिन्हित_device(vcpu->kvm))
		वापस 0;

	/*
	 * Here, we go through the per-vcpu ir_list to update all existing
	 * पूर्णांकerrupt remapping table entry targeting this vcpu.
	 */
	spin_lock_irqsave(&svm->ir_list_lock, flags);

	अगर (list_empty(&svm->ir_list))
		जाओ out;

	list_क्रम_each_entry(ir, &svm->ir_list, node) अणु
		ret = amd_iommu_update_ga(cpu, r, ir->data);
		अगर (ret)
			अवरोध;
	पूर्ण
out:
	spin_unlock_irqrestore(&svm->ir_list_lock, flags);
	वापस ret;
पूर्ण

व्योम avic_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	u64 entry;
	/* ID = 0xff (broadcast), ID > 0xff (reserved) */
	पूर्णांक h_physical_id = kvm_cpu_get_apicid(cpu);
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (!kvm_vcpu_apicv_active(vcpu))
		वापस;

	/*
	 * Since the host physical APIC id is 8 bits,
	 * we can support host APIC ID upto 255.
	 */
	अगर (WARN_ON(h_physical_id > AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK))
		वापस;

	entry = READ_ONCE(*(svm->avic_physical_id_cache));
	WARN_ON(entry & AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK);

	entry &= ~AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK;
	entry |= (h_physical_id & AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK);

	entry &= ~AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK;
	अगर (svm->avic_is_running)
		entry |= AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK;

	WRITE_ONCE(*(svm->avic_physical_id_cache), entry);
	avic_update_iommu_vcpu_affinity(vcpu, h_physical_id,
					svm->avic_is_running);
पूर्ण

व्योम avic_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 entry;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (!kvm_vcpu_apicv_active(vcpu))
		वापस;

	entry = READ_ONCE(*(svm->avic_physical_id_cache));
	अगर (entry & AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK)
		avic_update_iommu_vcpu_affinity(vcpu, -1, 0);

	entry &= ~AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK;
	WRITE_ONCE(*(svm->avic_physical_id_cache), entry);
पूर्ण

/*
 * This function is called during VCPU halt/unhalt.
 */
अटल व्योम avic_set_running(काष्ठा kvm_vcpu *vcpu, bool is_run)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	svm->avic_is_running = is_run;
	अगर (is_run)
		avic_vcpu_load(vcpu, vcpu->cpu);
	अन्यथा
		avic_vcpu_put(vcpu);
पूर्ण

व्योम svm_vcpu_blocking(काष्ठा kvm_vcpu *vcpu)
अणु
	avic_set_running(vcpu, false);
पूर्ण

व्योम svm_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_check_request(KVM_REQ_APICV_UPDATE, vcpu))
		kvm_vcpu_update_apicv(vcpu);
	avic_set_running(vcpu, true);
पूर्ण
