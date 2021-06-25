<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/irqchip/arm-gic-v3.h>

#समावेश "vgic.h"

/*
 * How KVM uses GICv4 (insert rude comments here):
 *
 * The vgic-v4 layer acts as a bridge between several entities:
 * - The GICv4 ITS representation offered by the ITS driver
 * - VFIO, which is in अक्षरge of the PCI endpoपूर्णांक
 * - The भव ITS, which is the only thing the guest sees
 *
 * The configuration of VLPIs is triggered by a callback from VFIO,
 * inकाष्ठाing KVM that a PCI device has been configured to deliver
 * MSIs to a vITS.
 *
 * kvm_vgic_v4_set_क्रमwarding() is thus called with the routing entry,
 * and this is used to find the corresponding vITS data काष्ठाures
 * (ITS instance, device, event and irq) using a process that is
 * extremely similar to the injection of an MSI.
 *
 * At this stage, we can link the guest's view of an LPI (uniquely
 * identअगरied by the routing entry) and the host irq, using the GICv4
 * driver mapping operation. Should the mapping succeed, we've then
 * successfully upgraded the guest's LPI to a VLPI. We can then start
 * with updating GICv4's view of the property table and generating an
 * INValidation in order to kickstart the delivery of this VLPI to the
 * guest directly, without software पूर्णांकervention. Well, almost.
 *
 * When the PCI endpoपूर्णांक is deconfigured, this operation is reversed
 * with VFIO calling kvm_vgic_v4_unset_क्रमwarding().
 *
 * Once the VLPI has been mapped, it needs to follow any change the
 * guest perक्रमms on its LPI through the vITS. For that, a number of
 * command handlers have hooks to communicate these changes to the HW:
 * - Any invalidation triggers a call to its_prop_update_vlpi()
 * - The INT command results in a irq_set_irqchip_state(), which
 *   generates an INT on the corresponding VLPI.
 * - The CLEAR command results in a irq_set_irqchip_state(), which
 *   generates an CLEAR on the corresponding VLPI.
 * - DISCARD translates पूर्णांकo an unmap, similar to a call to
 *   kvm_vgic_v4_unset_क्रमwarding().
 * - MOVI is translated by an update of the existing mapping, changing
 *   the target vcpu, resulting in a VMOVI being generated.
 * - MOVALL is translated by a string of mapping updates (similar to
 *   the handling of MOVI). MOVALL is horrible.
 *
 * Note that a DISCARD/MAPTI sequence emitted from the guest without
 * reprogramming the PCI endpoपूर्णांक after MAPTI करोes not result in a
 * VLPI being mapped, as there is no callback from VFIO (the guest
 * will get the पूर्णांकerrupt via the normal SW injection). Fixing this is
 * not trivial, and requires some horrible messing with the VFIO
 * पूर्णांकernals. Not fun. Don't करो that.
 *
 * Then there is the scheduling. Each समय a vcpu is about to run on a
 * physical CPU, KVM must tell the corresponding redistributor about
 * it. And अगर we've migrated our vcpu from one CPU to another, we must
 * tell the ITS (so that the messages reach the right redistributor).
 * This is करोne in two steps: first issue a irq_set_affinity() on the
 * irq corresponding to the vcpu, then call its_make_vpe_resident().
 * You must be in a non-preemptible context. On निकास, a call to
 * its_make_vpe_non_resident() tells the redistributor that we're करोne
 * with the vcpu.
 *
 * Finally, the करोorbell handling: Each vcpu is allocated an पूर्णांकerrupt
 * which will fire each समय a VLPI is made pending whilst the vcpu is
 * not running. Each समय the vcpu माला_लो blocked, the करोorbell
 * पूर्णांकerrupt माला_लो enabled. When the vcpu is unblocked (क्रम whatever
 * reason), the करोorbell पूर्णांकerrupt is disabled.
 */

#घोषणा DB_IRQ_FLAGS	(IRQ_NOAUTOEN | IRQ_DISABLE_UNLAZY | IRQ_NO_BALANCING)

अटल irqवापस_t vgic_v4_करोorbell_handler(पूर्णांक irq, व्योम *info)
अणु
	काष्ठा kvm_vcpu *vcpu = info;

	/* We got the message, no need to fire again */
	अगर (!kvm_vgic_global_state.has_gicv4_1 &&
	    !irqd_irq_disabled(&irq_to_desc(irq)->irq_data))
		disable_irq_nosync(irq);

	/*
	 * The v4.1 करोorbell can fire concurrently with the vPE being
	 * made non-resident. Ensure we only update pending_last
	 * *after* the non-residency sequence has completed.
	 */
	raw_spin_lock(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe.vpe_lock);
	vcpu->arch.vgic_cpu.vgic_v3.its_vpe.pending_last = true;
	raw_spin_unlock(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe.vpe_lock);

	kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
	kvm_vcpu_kick(vcpu);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम vgic_v4_sync_sgi_config(काष्ठा its_vpe *vpe, काष्ठा vgic_irq *irq)
अणु
	vpe->sgi_config[irq->पूर्णांकid].enabled	= irq->enabled;
	vpe->sgi_config[irq->पूर्णांकid].group 	= irq->group;
	vpe->sgi_config[irq->पूर्णांकid].priority	= irq->priority;
पूर्ण

अटल व्योम vgic_v4_enable_vsgis(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा its_vpe *vpe = &vcpu->arch.vgic_cpu.vgic_v3.its_vpe;
	पूर्णांक i;

	/*
	 * With GICv4.1, every भव SGI can be directly injected. So
	 * let's pretend that they are HW पूर्णांकerrupts, tied to a host
	 * IRQ. The SGI code will करो its magic.
	 */
	क्रम (i = 0; i < VGIC_NR_SGIS; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, i);
		काष्ठा irq_desc *desc;
		अचिन्हित दीर्घ flags;
		पूर्णांक ret;

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		अगर (irq->hw)
			जाओ unlock;

		irq->hw = true;
		irq->host_irq = irq_find_mapping(vpe->sgi_करोमुख्य, i);

		/* Transfer the full irq state to the vPE */
		vgic_v4_sync_sgi_config(vpe, irq);
		desc = irq_to_desc(irq->host_irq);
		ret = irq_करोमुख्य_activate_irq(irq_desc_get_irq_data(desc),
					      false);
		अगर (!WARN_ON(ret)) अणु
			/* Transfer pending state */
			ret = irq_set_irqchip_state(irq->host_irq,
						    IRQCHIP_STATE_PENDING,
						    irq->pending_latch);
			WARN_ON(ret);
			irq->pending_latch = false;
		पूर्ण
	unlock:
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

अटल व्योम vgic_v4_disable_vsgis(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VGIC_NR_SGIS; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, i);
		काष्ठा irq_desc *desc;
		अचिन्हित दीर्घ flags;
		पूर्णांक ret;

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		अगर (!irq->hw)
			जाओ unlock;

		irq->hw = false;
		ret = irq_get_irqchip_state(irq->host_irq,
					    IRQCHIP_STATE_PENDING,
					    &irq->pending_latch);
		WARN_ON(ret);

		desc = irq_to_desc(irq->host_irq);
		irq_करोमुख्य_deactivate_irq(irq_desc_get_irq_data(desc));
	unlock:
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

/* Must be called with the kvm lock held */
व्योम vgic_v4_configure_vsgis(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	kvm_arm_halt_guest(kvm);

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (dist->nassgireq)
			vgic_v4_enable_vsgis(vcpu);
		अन्यथा
			vgic_v4_disable_vsgis(vcpu);
	पूर्ण

	kvm_arm_resume_guest(kvm);
पूर्ण

/*
 * Must be called with GICv4.1 and the vPE unmapped, which
 * indicates the invalidation of any VPT caches associated
 * with the vPE, thus we can get the VLPI state by peeking
 * at the VPT.
 */
व्योम vgic_v4_get_vlpi_state(काष्ठा vgic_irq *irq, bool *val)
अणु
	काष्ठा its_vpe *vpe = &irq->target_vcpu->arch.vgic_cpu.vgic_v3.its_vpe;
	पूर्णांक mask = BIT(irq->पूर्णांकid % BITS_PER_BYTE);
	व्योम *va;
	u8 *ptr;

	va = page_address(vpe->vpt_page);
	ptr = va + irq->पूर्णांकid / BITS_PER_BYTE;

	*val = !!(*ptr & mask);
पूर्ण

/**
 * vgic_v4_init - Initialize the GICv4 data काष्ठाures
 * @kvm:	Poपूर्णांकer to the VM being initialized
 *
 * We may be called each समय a vITS is created, or when the
 * vgic is initialized. This relies on kvm->lock to be
 * held. In both हालs, the number of vcpus should now be
 * fixed.
 */
पूर्णांक vgic_v4_init(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i, nr_vcpus, ret;

	अगर (!kvm_vgic_global_state.has_gicv4)
		वापस 0; /* Nothing to see here... move aदीर्घ. */

	अगर (dist->its_vm.vpes)
		वापस 0;

	nr_vcpus = atomic_पढ़ो(&kvm->online_vcpus);

	dist->its_vm.vpes = kसुस्मृति(nr_vcpus, माप(*dist->its_vm.vpes),
				    GFP_KERNEL);
	अगर (!dist->its_vm.vpes)
		वापस -ENOMEM;

	dist->its_vm.nr_vpes = nr_vcpus;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		dist->its_vm.vpes[i] = &vcpu->arch.vgic_cpu.vgic_v3.its_vpe;

	ret = its_alloc_vcpu_irqs(&dist->its_vm);
	अगर (ret < 0) अणु
		kvm_err("VPE IRQ allocation failure\n");
		kमुक्त(dist->its_vm.vpes);
		dist->its_vm.nr_vpes = 0;
		dist->its_vm.vpes = शून्य;
		वापस ret;
	पूर्ण

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		पूर्णांक irq = dist->its_vm.vpes[i]->irq;
		अचिन्हित दीर्घ irq_flags = DB_IRQ_FLAGS;

		/*
		 * Don't automatically enable the doorbell, as we're
		 * flipping it back and क्रमth when the vcpu माला_लो
		 * blocked. Also disable the lazy disabling, as the
		 * करोorbell could kick us out of the guest too
		 * early...
		 *
		 * On GICv4.1, the करोorbell is managed in HW and must
		 * be left enabled.
		 */
		अगर (kvm_vgic_global_state.has_gicv4_1)
			irq_flags &= ~IRQ_NOAUTOEN;
		irq_set_status_flags(irq, irq_flags);

		ret = request_irq(irq, vgic_v4_करोorbell_handler,
				  0, "vcpu", vcpu);
		अगर (ret) अणु
			kvm_err("failed to allocate vcpu IRQ%d\n", irq);
			/*
			 * Trick: adjust the number of vpes so we know
			 * how many to nuke on tearकरोwn...
			 */
			dist->its_vm.nr_vpes = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		vgic_v4_tearकरोwn(kvm);

	वापस ret;
पूर्ण

/**
 * vgic_v4_tearकरोwn - Free the GICv4 data काष्ठाures
 * @kvm:	Poपूर्णांकer to the VM being destroyed
 *
 * Relies on kvm->lock to be held.
 */
व्योम vgic_v4_tearकरोwn(काष्ठा kvm *kvm)
अणु
	काष्ठा its_vm *its_vm = &kvm->arch.vgic.its_vm;
	पूर्णांक i;

	अगर (!its_vm->vpes)
		वापस;

	क्रम (i = 0; i < its_vm->nr_vpes; i++) अणु
		काष्ठा kvm_vcpu *vcpu = kvm_get_vcpu(kvm, i);
		पूर्णांक irq = its_vm->vpes[i]->irq;

		irq_clear_status_flags(irq, DB_IRQ_FLAGS);
		मुक्त_irq(irq, vcpu);
	पूर्ण

	its_मुक्त_vcpu_irqs(its_vm);
	kमुक्त(its_vm->vpes);
	its_vm->nr_vpes = 0;
	its_vm->vpes = शून्य;
पूर्ण

पूर्णांक vgic_v4_put(काष्ठा kvm_vcpu *vcpu, bool need_db)
अणु
	काष्ठा its_vpe *vpe = &vcpu->arch.vgic_cpu.vgic_v3.its_vpe;

	अगर (!vgic_supports_direct_msis(vcpu->kvm) || !vpe->resident)
		वापस 0;

	वापस its_make_vpe_non_resident(vpe, need_db);
पूर्ण

पूर्णांक vgic_v4_load(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा its_vpe *vpe = &vcpu->arch.vgic_cpu.vgic_v3.its_vpe;
	पूर्णांक err;

	अगर (!vgic_supports_direct_msis(vcpu->kvm) || vpe->resident)
		वापस 0;

	/*
	 * Beक्रमe making the VPE resident, make sure the redistributor
	 * corresponding to our current CPU expects us here. See the
	 * करोc in drivers/irqchip/irq-gic-v4.c to understand how this
	 * turns पूर्णांकo a VMOVP command at the ITS level.
	 */
	err = irq_set_affinity(vpe->irq, cpumask_of(smp_processor_id()));
	अगर (err)
		वापस err;

	err = its_make_vpe_resident(vpe, false, vcpu->kvm->arch.vgic.enabled);
	अगर (err)
		वापस err;

	/*
	 * Now that the VPE is resident, let's get rid of a potential
	 * करोorbell पूर्णांकerrupt that would still be pending. This is a
	 * GICv4.0 only "feature"...
	 */
	अगर (!kvm_vgic_global_state.has_gicv4_1)
		err = irq_set_irqchip_state(vpe->irq, IRQCHIP_STATE_PENDING, false);

	वापस err;
पूर्ण

व्योम vgic_v4_commit(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा its_vpe *vpe = &vcpu->arch.vgic_cpu.vgic_v3.its_vpe;

	/*
	 * No need to रुको क्रम the vPE to be पढ़ोy across a shallow guest
	 * निकास, as only a vcpu_put will invalidate it.
	 */
	अगर (!vpe->पढ़ोy)
		its_commit_vpe(vpe);
पूर्ण

अटल काष्ठा vgic_its *vgic_get_its(काष्ठा kvm *kvm,
				     काष्ठा kvm_kernel_irq_routing_entry *irq_entry)
अणु
	काष्ठा kvm_msi msi  = (काष्ठा kvm_msi) अणु
		.address_lo	= irq_entry->msi.address_lo,
		.address_hi	= irq_entry->msi.address_hi,
		.data		= irq_entry->msi.data,
		.flags		= irq_entry->msi.flags,
		.devid		= irq_entry->msi.devid,
	पूर्ण;

	वापस vgic_msi_to_its(kvm, &msi);
पूर्ण

पूर्णांक kvm_vgic_v4_set_क्रमwarding(काष्ठा kvm *kvm, पूर्णांक virq,
			       काष्ठा kvm_kernel_irq_routing_entry *irq_entry)
अणु
	काष्ठा vgic_its *its;
	काष्ठा vgic_irq *irq;
	काष्ठा its_vlpi_map map;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!vgic_supports_direct_msis(kvm))
		वापस 0;

	/*
	 * Get the ITS, and escape early on error (not a valid
	 * करोorbell क्रम any of our vITSs).
	 */
	its = vgic_get_its(kvm, irq_entry);
	अगर (IS_ERR(its))
		वापस 0;

	mutex_lock(&its->its_lock);

	/* Perक्रमm the actual DevID/EventID -> LPI translation. */
	ret = vgic_its_resolve_lpi(kvm, its, irq_entry->msi.devid,
				   irq_entry->msi.data, &irq);
	अगर (ret)
		जाओ out;

	/*
	 * Emit the mapping request. If it fails, the ITS probably
	 * isn't v4 compatible, so let's silently bail out. Holding
	 * the ITS lock should ensure that nothing can modअगरy the
	 * target vcpu.
	 */
	map = (काष्ठा its_vlpi_map) अणु
		.vm		= &kvm->arch.vgic.its_vm,
		.vpe		= &irq->target_vcpu->arch.vgic_cpu.vgic_v3.its_vpe,
		.vपूर्णांकid		= irq->पूर्णांकid,
		.properties	= ((irq->priority & 0xfc) |
				   (irq->enabled ? LPI_PROP_ENABLED : 0) |
				   LPI_PROP_GROUP1),
		.db_enabled	= true,
	पूर्ण;

	ret = its_map_vlpi(virq, &map);
	अगर (ret)
		जाओ out;

	irq->hw		= true;
	irq->host_irq	= virq;
	atomic_inc(&map.vpe->vlpi_count);

	/* Transfer pending state */
	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	अगर (irq->pending_latch) अणु
		ret = irq_set_irqchip_state(irq->host_irq,
					    IRQCHIP_STATE_PENDING,
					    irq->pending_latch);
		WARN_RATELIMIT(ret, "IRQ %d", irq->host_irq);

		/*
		 * Clear pending_latch and communicate this state
		 * change via vgic_queue_irq_unlock.
		 */
		irq->pending_latch = false;
		vgic_queue_irq_unlock(kvm, irq, flags);
	पूर्ण अन्यथा अणु
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	पूर्ण

out:
	mutex_unlock(&its->its_lock);
	वापस ret;
पूर्ण

पूर्णांक kvm_vgic_v4_unset_क्रमwarding(काष्ठा kvm *kvm, पूर्णांक virq,
				 काष्ठा kvm_kernel_irq_routing_entry *irq_entry)
अणु
	काष्ठा vgic_its *its;
	काष्ठा vgic_irq *irq;
	पूर्णांक ret;

	अगर (!vgic_supports_direct_msis(kvm))
		वापस 0;

	/*
	 * Get the ITS, and escape early on error (not a valid
	 * करोorbell क्रम any of our vITSs).
	 */
	its = vgic_get_its(kvm, irq_entry);
	अगर (IS_ERR(its))
		वापस 0;

	mutex_lock(&its->its_lock);

	ret = vgic_its_resolve_lpi(kvm, its, irq_entry->msi.devid,
				   irq_entry->msi.data, &irq);
	अगर (ret)
		जाओ out;

	WARN_ON(!(irq->hw && irq->host_irq == virq));
	अगर (irq->hw) अणु
		atomic_dec(&irq->target_vcpu->arch.vgic_cpu.vgic_v3.its_vpe.vlpi_count);
		irq->hw = false;
		ret = its_unmap_vlpi(virq);
	पूर्ण

out:
	mutex_unlock(&its->its_lock);
	वापस ret;
पूर्ण
