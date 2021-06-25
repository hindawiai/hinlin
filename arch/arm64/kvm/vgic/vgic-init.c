<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kvm_host.h>
#समावेश <kvm/arm_vgic.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश "vgic.h"

/*
 * Initialization rules: there are multiple stages to the vgic
 * initialization, both क्रम the distributor and the CPU पूर्णांकerfaces.  The basic
 * idea is that even though the VGIC is not functional or not requested from
 * user space, the critical path of the run loop can still call VGIC functions
 * that just won't करो anything, without them having to check additional
 * initialization flags to ensure they करोn't look at uninitialized data
 * काष्ठाures.
 *
 * Distributor:
 *
 * - kvm_vgic_early_init(): initialization of अटल data that करोesn't
 *   depend on any sizing inक्रमmation or emulation type. No allocation
 *   is allowed there.
 *
 * - vgic_init(): allocation and initialization of the generic data
 *   काष्ठाures that depend on sizing inक्रमmation (number of CPUs,
 *   number of पूर्णांकerrupts). Also initializes the vcpu specअगरic data
 *   काष्ठाures. Can be executed lazily क्रम GICv2.
 *
 * CPU Interface:
 *
 * - kvm_vgic_vcpu_init(): initialization of अटल data that
 *   करोesn't depend on any sizing inक्रमmation or emulation type. No
 *   allocation is allowed there.
 */

/* EARLY INIT */

/**
 * kvm_vgic_early_init() - Initialize अटल VGIC VCPU data काष्ठाures
 * @kvm: The VM whose VGIC districutor should be initialized
 *
 * Only करो initialization of अटल काष्ठाures that करोn't require any
 * allocation or sizing inक्रमmation from userspace.  vgic_init() called
 * kvm_vgic_dist_init() which takes care of the rest.
 */
व्योम kvm_vgic_early_init(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;

	INIT_LIST_HEAD(&dist->lpi_list_head);
	INIT_LIST_HEAD(&dist->lpi_translation_cache);
	raw_spin_lock_init(&dist->lpi_list_lock);
पूर्ण

/* CREATION */

/**
 * kvm_vgic_create: triggered by the instantiation of the VGIC device by
 * user space, either through the legacy KVM_CREATE_IRQCHIP ioctl (v2 only)
 * or through the generic KVM_CREATE_DEVICE API ioctl.
 * irqchip_in_kernel() tells you अगर this function succeeded or not.
 * @kvm: kvm काष्ठा poपूर्णांकer
 * @type: KVM_DEV_TYPE_ARM_VGIC_V[23]
 */
पूर्णांक kvm_vgic_create(काष्ठा kvm *kvm, u32 type)
अणु
	पूर्णांक i, ret;
	काष्ठा kvm_vcpu *vcpu;

	अगर (irqchip_in_kernel(kvm))
		वापस -EEXIST;

	/*
	 * This function is also called by the KVM_CREATE_IRQCHIP handler,
	 * which had no chance yet to check the availability of the GICv2
	 * emulation. So check this here again. KVM_CREATE_DEVICE करोes
	 * the proper checks alपढ़ोy.
	 */
	अगर (type == KVM_DEV_TYPE_ARM_VGIC_V2 &&
		!kvm_vgic_global_state.can_emulate_gicv2)
		वापस -ENODEV;

	ret = -EBUSY;
	अगर (!lock_all_vcpus(kvm))
		वापस ret;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (vcpu->arch.has_run_once)
			जाओ out_unlock;
	पूर्ण
	ret = 0;

	अगर (type == KVM_DEV_TYPE_ARM_VGIC_V2)
		kvm->arch.max_vcpus = VGIC_V2_MAX_CPUS;
	अन्यथा
		kvm->arch.max_vcpus = VGIC_V3_MAX_CPUS;

	अगर (atomic_पढ़ो(&kvm->online_vcpus) > kvm->arch.max_vcpus) अणु
		ret = -E2BIG;
		जाओ out_unlock;
	पूर्ण

	kvm->arch.vgic.in_kernel = true;
	kvm->arch.vgic.vgic_model = type;

	kvm->arch.vgic.vgic_dist_base = VGIC_ADDR_UNDEF;

	अगर (type == KVM_DEV_TYPE_ARM_VGIC_V2)
		kvm->arch.vgic.vgic_cpu_base = VGIC_ADDR_UNDEF;
	अन्यथा
		INIT_LIST_HEAD(&kvm->arch.vgic.rd_regions);

out_unlock:
	unlock_all_vcpus(kvm);
	वापस ret;
पूर्ण

/* INIT/DESTROY */

/**
 * kvm_vgic_dist_init: initialize the dist data काष्ठाures
 * @kvm: kvm काष्ठा poपूर्णांकer
 * @nr_spis: number of spis, frozen by caller
 */
अटल पूर्णांक kvm_vgic_dist_init(काष्ठा kvm *kvm, अचिन्हित पूर्णांक nr_spis)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा kvm_vcpu *vcpu0 = kvm_get_vcpu(kvm, 0);
	पूर्णांक i;

	dist->spis = kसुस्मृति(nr_spis, माप(काष्ठा vgic_irq), GFP_KERNEL);
	अगर (!dist->spis)
		वापस  -ENOMEM;

	/*
	 * In the following code we करो not take the irq काष्ठा lock since
	 * no other action on irq काष्ठाs can happen जबतक the VGIC is
	 * not initialized yet:
	 * If someone wants to inject an पूर्णांकerrupt or करोes a MMIO access, we
	 * require prior initialization in हाल of a भव GICv3 or trigger
	 * initialization when using a भव GICv2.
	 */
	क्रम (i = 0; i < nr_spis; i++) अणु
		काष्ठा vgic_irq *irq = &dist->spis[i];

		irq->पूर्णांकid = i + VGIC_NR_PRIVATE_IRQS;
		INIT_LIST_HEAD(&irq->ap_list);
		raw_spin_lock_init(&irq->irq_lock);
		irq->vcpu = शून्य;
		irq->target_vcpu = vcpu0;
		kref_init(&irq->refcount);
		चयन (dist->vgic_model) अणु
		हाल KVM_DEV_TYPE_ARM_VGIC_V2:
			irq->tarमाला_लो = 0;
			irq->group = 0;
			अवरोध;
		हाल KVM_DEV_TYPE_ARM_VGIC_V3:
			irq->mpidr = 0;
			irq->group = 1;
			अवरोध;
		शेष:
			kमुक्त(dist->spis);
			dist->spis = शून्य;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * kvm_vgic_vcpu_init() - Initialize अटल VGIC VCPU data
 * काष्ठाures and रेजिस्टर VCPU-specअगरic KVM iodevs
 *
 * @vcpu: poपूर्णांकer to the VCPU being created and initialized
 *
 * Only करो initialization, but करो not actually enable the
 * VGIC CPU पूर्णांकerface
 */
पूर्णांक kvm_vgic_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_dist *dist = &vcpu->kvm->arch.vgic;
	पूर्णांक ret = 0;
	पूर्णांक i;

	vgic_cpu->rd_iodev.base_addr = VGIC_ADDR_UNDEF;

	INIT_LIST_HEAD(&vgic_cpu->ap_list_head);
	raw_spin_lock_init(&vgic_cpu->ap_list_lock);
	atomic_set(&vgic_cpu->vgic_v3.its_vpe.vlpi_count, 0);

	/*
	 * Enable and configure all SGIs to be edge-triggered and
	 * configure all PPIs as level-triggered.
	 */
	क्रम (i = 0; i < VGIC_NR_PRIVATE_IRQS; i++) अणु
		काष्ठा vgic_irq *irq = &vgic_cpu->निजी_irqs[i];

		INIT_LIST_HEAD(&irq->ap_list);
		raw_spin_lock_init(&irq->irq_lock);
		irq->पूर्णांकid = i;
		irq->vcpu = शून्य;
		irq->target_vcpu = vcpu;
		kref_init(&irq->refcount);
		अगर (vgic_irq_is_sgi(i)) अणु
			/* SGIs */
			irq->enabled = 1;
			irq->config = VGIC_CONFIG_EDGE;
		पूर्ण अन्यथा अणु
			/* PPIs */
			irq->config = VGIC_CONFIG_LEVEL;
		पूर्ण
	पूर्ण

	अगर (!irqchip_in_kernel(vcpu->kvm))
		वापस 0;

	/*
	 * If we are creating a VCPU with a GICv3 we must also रेजिस्टर the
	 * KVM io device क्रम the redistributor that beदीर्घs to this VCPU.
	 */
	अगर (dist->vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3) अणु
		mutex_lock(&vcpu->kvm->lock);
		ret = vgic_रेजिस्टर_redist_iodev(vcpu);
		mutex_unlock(&vcpu->kvm->lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम kvm_vgic_vcpu_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_enable(vcpu);
	अन्यथा
		vgic_v3_enable(vcpu);
पूर्ण

/*
 * vgic_init: allocates and initializes dist and vcpu data काष्ठाures
 * depending on two dimensioning parameters:
 * - the number of spis
 * - the number of vcpus
 * The function is generally called when nr_spis has been explicitly set
 * by the guest through the KVM DEVICE API. If not nr_spis is set to 256.
 * vgic_initialized() वापसs true when this function has succeeded.
 * Must be called with kvm->lock held!
 */
पूर्णांक vgic_init(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक ret = 0, i, idx;

	अगर (vgic_initialized(kvm))
		वापस 0;

	/* Are we also in the middle of creating a VCPU? */
	अगर (kvm->created_vcpus != atomic_पढ़ो(&kvm->online_vcpus))
		वापस -EBUSY;

	/* मुक्तze the number of spis */
	अगर (!dist->nr_spis)
		dist->nr_spis = VGIC_NR_IRQS_LEGACY - VGIC_NR_PRIVATE_IRQS;

	ret = kvm_vgic_dist_init(kvm, dist->nr_spis);
	अगर (ret)
		जाओ out;

	/* Initialize groups on CPUs created beक्रमe the VGIC type was known */
	kvm_क्रम_each_vcpu(idx, vcpu, kvm) अणु
		काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

		क्रम (i = 0; i < VGIC_NR_PRIVATE_IRQS; i++) अणु
			काष्ठा vgic_irq *irq = &vgic_cpu->निजी_irqs[i];
			चयन (dist->vgic_model) अणु
			हाल KVM_DEV_TYPE_ARM_VGIC_V3:
				irq->group = 1;
				irq->mpidr = kvm_vcpu_get_mpidr_aff(vcpu);
				अवरोध;
			हाल KVM_DEV_TYPE_ARM_VGIC_V2:
				irq->group = 0;
				irq->tarमाला_लो = 1U << idx;
				अवरोध;
			शेष:
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vgic_has_its(kvm))
		vgic_lpi_translation_cache_init(kvm);

	/*
	 * If we have GICv4.1 enabled, unconditionnaly request enable the
	 * v4 support so that we get HW-accelerated vSGIs. Otherwise, only
	 * enable it अगर we present a भव ITS to the guest.
	 */
	अगर (vgic_supports_direct_msis(kvm)) अणु
		ret = vgic_v4_init(kvm);
		अगर (ret)
			जाओ out;
	पूर्ण

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vgic_vcpu_enable(vcpu);

	ret = kvm_vgic_setup_शेष_irq_routing(kvm);
	अगर (ret)
		जाओ out;

	vgic_debug_init(kvm);

	dist->implementation_rev = 2;
	dist->initialized = true;

out:
	वापस ret;
पूर्ण

अटल व्योम kvm_vgic_dist_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_redist_region *rdreg, *next;

	dist->पढ़ोy = false;
	dist->initialized = false;

	kमुक्त(dist->spis);
	dist->spis = शून्य;
	dist->nr_spis = 0;
	dist->vgic_dist_base = VGIC_ADDR_UNDEF;

	अगर (dist->vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3) अणु
		list_क्रम_each_entry_safe(rdreg, next, &dist->rd_regions, list)
			vgic_v3_मुक्त_redist_region(rdreg);
		INIT_LIST_HEAD(&dist->rd_regions);
	पूर्ण अन्यथा अणु
		dist->vgic_cpu_base = VGIC_ADDR_UNDEF;
	पूर्ण

	अगर (vgic_has_its(kvm))
		vgic_lpi_translation_cache_destroy(kvm);

	अगर (vgic_supports_direct_msis(kvm))
		vgic_v4_tearकरोwn(kvm);
पूर्ण

व्योम kvm_vgic_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

	/*
	 * Retire all pending LPIs on this vcpu anyway as we're
	 * going to destroy it.
	 */
	vgic_flush_pending_lpis(vcpu);

	INIT_LIST_HEAD(&vgic_cpu->ap_list_head);
	vgic_cpu->rd_iodev.base_addr = VGIC_ADDR_UNDEF;
पूर्ण

/* To be called with kvm->lock held */
अटल व्योम __kvm_vgic_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	vgic_debug_destroy(kvm);

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vgic_vcpu_destroy(vcpu);

	kvm_vgic_dist_destroy(kvm);
पूर्ण

व्योम kvm_vgic_destroy(काष्ठा kvm *kvm)
अणु
	mutex_lock(&kvm->lock);
	__kvm_vgic_destroy(kvm);
	mutex_unlock(&kvm->lock);
पूर्ण

/**
 * vgic_lazy_init: Lazy init is only allowed अगर the GIC exposed to the guest
 * is a GICv2. A GICv3 must be explicitly initialized by the guest using the
 * KVM_DEV_ARM_VGIC_GRP_CTRL KVM_DEVICE group.
 * @kvm: kvm काष्ठा poपूर्णांकer
 */
पूर्णांक vgic_lazy_init(काष्ठा kvm *kvm)
अणु
	पूर्णांक ret = 0;

	अगर (unlikely(!vgic_initialized(kvm))) अणु
		/*
		 * We only provide the स्वतःmatic initialization of the VGIC
		 * क्रम the legacy हाल of a GICv2. Any other type must
		 * be explicitly initialized once setup with the respective
		 * KVM device call.
		 */
		अगर (kvm->arch.vgic.vgic_model != KVM_DEV_TYPE_ARM_VGIC_V2)
			वापस -EBUSY;

		mutex_lock(&kvm->lock);
		ret = vgic_init(kvm);
		mutex_unlock(&kvm->lock);
	पूर्ण

	वापस ret;
पूर्ण

/* RESOURCE MAPPING */

/**
 * Map the MMIO regions depending on the VGIC model exposed to the guest
 * called on the first VCPU run.
 * Also map the भव CPU पूर्णांकerface पूर्णांकo the VM.
 * v2 calls vgic_init() अगर not alपढ़ोy करोne.
 * v3 and derivatives वापस an error अगर the VGIC is not initialized.
 * vgic_पढ़ोy() वापसs true अगर this function has succeeded.
 * @kvm: kvm काष्ठा poपूर्णांकer
 */
पूर्णांक kvm_vgic_map_resources(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	पूर्णांक ret = 0;

	अगर (likely(vgic_पढ़ोy(kvm)))
		वापस 0;

	mutex_lock(&kvm->lock);
	अगर (vgic_पढ़ोy(kvm))
		जाओ out;

	अगर (!irqchip_in_kernel(kvm))
		जाओ out;

	अगर (dist->vgic_model == KVM_DEV_TYPE_ARM_VGIC_V2)
		ret = vgic_v2_map_resources(kvm);
	अन्यथा
		ret = vgic_v3_map_resources(kvm);

	अगर (ret)
		__kvm_vgic_destroy(kvm);
	अन्यथा
		dist->पढ़ोy = true;

out:
	mutex_unlock(&kvm->lock);
	वापस ret;
पूर्ण

/* GENERIC PROBE */

अटल पूर्णांक vgic_init_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	enable_percpu_irq(kvm_vgic_global_state.मुख्यt_irq, 0);
	वापस 0;
पूर्ण


अटल पूर्णांक vgic_init_cpu_dying(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(kvm_vgic_global_state.मुख्यt_irq);
	वापस 0;
पूर्ण

अटल irqवापस_t vgic_मुख्यtenance_handler(पूर्णांक irq, व्योम *data)
अणु
	/*
	 * We cannot rely on the vgic मुख्यtenance पूर्णांकerrupt to be
	 * delivered synchronously. This means we can only use it to
	 * निकास the VM, and we perक्रमm the handling of EOIed
	 * पूर्णांकerrupts on the निकास path (see vgic_fold_lr_state).
	 */
	वापस IRQ_HANDLED;
पूर्ण

/**
 * kvm_vgic_init_cpu_hardware - initialize the GIC VE hardware
 *
 * For a specअगरic CPU, initialize the GIC VE hardware.
 */
व्योम kvm_vgic_init_cpu_hardware(व्योम)
अणु
	BUG_ON(preemptible());

	/*
	 * We want to make sure the list रेजिस्टरs start out clear so that we
	 * only have the program the used रेजिस्टरs.
	 */
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_init_lrs();
	अन्यथा
		kvm_call_hyp(__vgic_v3_init_lrs);
पूर्ण

/**
 * kvm_vgic_hyp_init: populates the kvm_vgic_global_state variable
 * according to the host GIC model. Accordingly calls either
 * vgic_v2/v3_probe which रेजिस्टरs the KVM_DEVICE that can be
 * instantiated by a guest later on .
 */
पूर्णांक kvm_vgic_hyp_init(व्योम)
अणु
	स्थिर काष्ठा gic_kvm_info *gic_kvm_info;
	पूर्णांक ret;

	gic_kvm_info = gic_get_kvm_info();
	अगर (!gic_kvm_info)
		वापस -ENODEV;

	अगर (!gic_kvm_info->मुख्यt_irq) अणु
		kvm_err("No vgic maintenance irq\n");
		वापस -ENXIO;
	पूर्ण

	चयन (gic_kvm_info->type) अणु
	हाल GIC_V2:
		ret = vgic_v2_probe(gic_kvm_info);
		अवरोध;
	हाल GIC_V3:
		ret = vgic_v3_probe(gic_kvm_info);
		अगर (!ret) अणु
			अटल_branch_enable(&kvm_vgic_global_state.gicv3_cpuअगर);
			kvm_info("GIC system register CPU interface enabled\n");
		पूर्ण
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण

	अगर (ret)
		वापस ret;

	kvm_vgic_global_state.मुख्यt_irq = gic_kvm_info->मुख्यt_irq;
	ret = request_percpu_irq(kvm_vgic_global_state.मुख्यt_irq,
				 vgic_मुख्यtenance_handler,
				 "vgic", kvm_get_running_vcpus());
	अगर (ret) अणु
		kvm_err("Cannot register interrupt %d\n",
			kvm_vgic_global_state.मुख्यt_irq);
		वापस ret;
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_KVM_ARM_VGIC_INIT_STARTING,
				"kvm/arm/vgic:starting",
				vgic_init_cpu_starting, vgic_init_cpu_dying);
	अगर (ret) अणु
		kvm_err("Cannot register vgic CPU notifier\n");
		जाओ out_मुक्त_irq;
	पूर्ण

	kvm_info("vgic interrupt IRQ%d\n", kvm_vgic_global_state.मुख्यt_irq);
	वापस 0;

out_मुक्त_irq:
	मुक्त_percpu_irq(kvm_vgic_global_state.मुख्यt_irq,
			kvm_get_running_vcpus());
	वापस ret;
पूर्ण
