<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Local APIC related पूर्णांकerfaces to support IOAPIC, MSI, etc.
 *
 * Copyright (C) 1997, 1998, 1999, 2000, 2009 Ingo Molnar, Hajnalka Szabo
 *	Moved from arch/x86/kernel/apic/io_apic.c.
 * Jiang Liu <jiang.liu@linux.पूर्णांकel.com>
 *	Enable support of hierarchical irqकरोमुख्यs
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/irq_remapping.h>

#समावेश <यंत्र/trace/irq_vectors.h>

काष्ठा apic_chip_data अणु
	काष्ठा irq_cfg		hw_irq_cfg;
	अचिन्हित पूर्णांक		vector;
	अचिन्हित पूर्णांक		prev_vector;
	अचिन्हित पूर्णांक		cpu;
	अचिन्हित पूर्णांक		prev_cpu;
	अचिन्हित पूर्णांक		irq;
	काष्ठा hlist_node	clist;
	अचिन्हित पूर्णांक		move_in_progress	: 1,
				is_managed		: 1,
				can_reserve		: 1,
				has_reserved		: 1;
पूर्ण;

काष्ठा irq_करोमुख्य *x86_vector_करोमुख्य;
EXPORT_SYMBOL_GPL(x86_vector_करोमुख्य);
अटल DEFINE_RAW_SPINLOCK(vector_lock);
अटल cpumask_var_t vector_searchmask;
अटल काष्ठा irq_chip lapic_controller;
अटल काष्ठा irq_matrix *vector_matrix;
#अगर_घोषित CONFIG_SMP
अटल DEFINE_PER_CPU(काष्ठा hlist_head, cleanup_list);
#पूर्ण_अगर

व्योम lock_vector_lock(व्योम)
अणु
	/* Used to the online set of cpus करोes not change
	 * during assign_irq_vector.
	 */
	raw_spin_lock(&vector_lock);
पूर्ण

व्योम unlock_vector_lock(व्योम)
अणु
	raw_spin_unlock(&vector_lock);
पूर्ण

व्योम init_irq_alloc_info(काष्ठा irq_alloc_info *info,
			 स्थिर काष्ठा cpumask *mask)
अणु
	स_रखो(info, 0, माप(*info));
	info->mask = mask;
पूर्ण

व्योम copy_irq_alloc_info(काष्ठा irq_alloc_info *dst, काष्ठा irq_alloc_info *src)
अणु
	अगर (src)
		*dst = *src;
	अन्यथा
		स_रखो(dst, 0, माप(*dst));
पूर्ण

अटल काष्ठा apic_chip_data *apic_chip_data(काष्ठा irq_data *irqd)
अणु
	अगर (!irqd)
		वापस शून्य;

	जबतक (irqd->parent_data)
		irqd = irqd->parent_data;

	वापस irqd->chip_data;
पूर्ण

काष्ठा irq_cfg *irqd_cfg(काष्ठा irq_data *irqd)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);

	वापस apicd ? &apicd->hw_irq_cfg : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(irqd_cfg);

काष्ठा irq_cfg *irq_cfg(अचिन्हित पूर्णांक irq)
अणु
	वापस irqd_cfg(irq_get_irq_data(irq));
पूर्ण

अटल काष्ठा apic_chip_data *alloc_apic_chip_data(पूर्णांक node)
अणु
	काष्ठा apic_chip_data *apicd;

	apicd = kzalloc_node(माप(*apicd), GFP_KERNEL, node);
	अगर (apicd)
		INIT_HLIST_NODE(&apicd->clist);
	वापस apicd;
पूर्ण

अटल व्योम मुक्त_apic_chip_data(काष्ठा apic_chip_data *apicd)
अणु
	kमुक्त(apicd);
पूर्ण

अटल व्योम apic_update_irq_cfg(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक vector,
				अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);

	lockdep_निश्चित_held(&vector_lock);

	apicd->hw_irq_cfg.vector = vector;
	apicd->hw_irq_cfg.dest_apicid = apic->calc_dest_apicid(cpu);
	irq_data_update_effective_affinity(irqd, cpumask_of(cpu));
	trace_vector_config(irqd->irq, vector, cpu,
			    apicd->hw_irq_cfg.dest_apicid);
पूर्ण

अटल व्योम apic_update_vector(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक newvec,
			       अचिन्हित पूर्णांक newcpu)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	काष्ठा irq_desc *desc = irq_data_to_desc(irqd);
	bool managed = irqd_affinity_is_managed(irqd);

	lockdep_निश्चित_held(&vector_lock);

	trace_vector_update(irqd->irq, newvec, newcpu, apicd->vector,
			    apicd->cpu);

	/*
	 * If there is no vector associated or अगर the associated vector is
	 * the shutकरोwn vector, which is associated to make PCI/MSI
	 * shutकरोwn mode work, then there is nothing to release. Clear out
	 * prev_vector क्रम this and the offlined target हाल.
	 */
	apicd->prev_vector = 0;
	अगर (!apicd->vector || apicd->vector == MANAGED_IRQ_SHUTDOWN_VECTOR)
		जाओ setnew;
	/*
	 * If the target CPU of the previous vector is online, then mark
	 * the vector as move in progress and store it क्रम cleanup when the
	 * first पूर्णांकerrupt on the new vector arrives. If the target CPU is
	 * offline then the regular release mechanism via the cleanup
	 * vector is not possible and the vector can be immediately मुक्तd
	 * in the underlying matrix allocator.
	 */
	अगर (cpu_online(apicd->cpu)) अणु
		apicd->move_in_progress = true;
		apicd->prev_vector = apicd->vector;
		apicd->prev_cpu = apicd->cpu;
		WARN_ON_ONCE(apicd->cpu == newcpu);
	पूर्ण अन्यथा अणु
		irq_matrix_मुक्त(vector_matrix, apicd->cpu, apicd->vector,
				managed);
	पूर्ण

setnew:
	apicd->vector = newvec;
	apicd->cpu = newcpu;
	BUG_ON(!IS_ERR_OR_शून्य(per_cpu(vector_irq, newcpu)[newvec]));
	per_cpu(vector_irq, newcpu)[newvec] = desc;
पूर्ण

अटल व्योम vector_assign_managed_shutकरोwn(काष्ठा irq_data *irqd)
अणु
	अचिन्हित पूर्णांक cpu = cpumask_first(cpu_online_mask);

	apic_update_irq_cfg(irqd, MANAGED_IRQ_SHUTDOWN_VECTOR, cpu);
पूर्ण

अटल पूर्णांक reserve_managed_vector(काष्ठा irq_data *irqd)
अणु
	स्थिर काष्ठा cpumask *affmsk = irq_data_get_affinity_mask(irqd);
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&vector_lock, flags);
	apicd->is_managed = true;
	ret = irq_matrix_reserve_managed(vector_matrix, affmsk);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	trace_vector_reserve_managed(irqd->irq, ret);
	वापस ret;
पूर्ण

अटल व्योम reserve_irq_vector_locked(काष्ठा irq_data *irqd)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);

	irq_matrix_reserve(vector_matrix);
	apicd->can_reserve = true;
	apicd->has_reserved = true;
	irqd_set_can_reserve(irqd);
	trace_vector_reserve(irqd->irq, 0);
	vector_assign_managed_shutकरोwn(irqd);
पूर्ण

अटल पूर्णांक reserve_irq_vector(काष्ठा irq_data *irqd)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&vector_lock, flags);
	reserve_irq_vector_locked(irqd);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
assign_vector_locked(काष्ठा irq_data *irqd, स्थिर काष्ठा cpumask *dest)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	bool resvd = apicd->has_reserved;
	अचिन्हित पूर्णांक cpu = apicd->cpu;
	पूर्णांक vector = apicd->vector;

	lockdep_निश्चित_held(&vector_lock);

	/*
	 * If the current target CPU is online and in the new requested
	 * affinity mask, there is no poपूर्णांक in moving the पूर्णांकerrupt from
	 * one CPU to another.
	 */
	अगर (vector && cpu_online(cpu) && cpumask_test_cpu(cpu, dest))
		वापस 0;

	/*
	 * Careful here. @apicd might either have move_in_progress set or
	 * be enqueued क्रम cleanup. Assigning a new vector would either
	 * leave a stale vector on some CPU around or in हाल of a pending
	 * cleanup corrupt the hlist.
	 */
	अगर (apicd->move_in_progress || !hlist_unhashed(&apicd->clist))
		वापस -EBUSY;

	vector = irq_matrix_alloc(vector_matrix, dest, resvd, &cpu);
	trace_vector_alloc(irqd->irq, vector, resvd, vector);
	अगर (vector < 0)
		वापस vector;
	apic_update_vector(irqd, vector, cpu);
	apic_update_irq_cfg(irqd, vector, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक assign_irq_vector(काष्ठा irq_data *irqd, स्थिर काष्ठा cpumask *dest)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&vector_lock, flags);
	cpumask_and(vector_searchmask, dest, cpu_online_mask);
	ret = assign_vector_locked(irqd, vector_searchmask);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक assign_irq_vector_any_locked(काष्ठा irq_data *irqd)
अणु
	/* Get the affinity mask - either irq_शेष_affinity or (user) set */
	स्थिर काष्ठा cpumask *affmsk = irq_data_get_affinity_mask(irqd);
	पूर्णांक node = irq_data_get_node(irqd);

	अगर (node != NUMA_NO_NODE) अणु
		/* Try the पूर्णांकersection of @affmsk and node mask */
		cpumask_and(vector_searchmask, cpumask_of_node(node), affmsk);
		अगर (!assign_vector_locked(irqd, vector_searchmask))
			वापस 0;
	पूर्ण

	/* Try the full affinity mask */
	cpumask_and(vector_searchmask, affmsk, cpu_online_mask);
	अगर (!assign_vector_locked(irqd, vector_searchmask))
		वापस 0;

	अगर (node != NUMA_NO_NODE) अणु
		/* Try the node mask */
		अगर (!assign_vector_locked(irqd, cpumask_of_node(node)))
			वापस 0;
	पूर्ण

	/* Try the full online mask */
	वापस assign_vector_locked(irqd, cpu_online_mask);
पूर्ण

अटल पूर्णांक
assign_irq_vector_policy(काष्ठा irq_data *irqd, काष्ठा irq_alloc_info *info)
अणु
	अगर (irqd_affinity_is_managed(irqd))
		वापस reserve_managed_vector(irqd);
	अगर (info->mask)
		वापस assign_irq_vector(irqd, info->mask);
	/*
	 * Make only a global reservation with no guarantee. A real vector
	 * is associated at activation समय.
	 */
	वापस reserve_irq_vector(irqd);
पूर्ण

अटल पूर्णांक
assign_managed_vector(काष्ठा irq_data *irqd, स्थिर काष्ठा cpumask *dest)
अणु
	स्थिर काष्ठा cpumask *affmsk = irq_data_get_affinity_mask(irqd);
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	पूर्णांक vector, cpu;

	cpumask_and(vector_searchmask, dest, affmsk);

	/* set_affinity might call here क्रम nothing */
	अगर (apicd->vector && cpumask_test_cpu(apicd->cpu, vector_searchmask))
		वापस 0;
	vector = irq_matrix_alloc_managed(vector_matrix, vector_searchmask,
					  &cpu);
	trace_vector_alloc_managed(irqd->irq, vector, vector);
	अगर (vector < 0)
		वापस vector;
	apic_update_vector(irqd, vector, cpu);
	apic_update_irq_cfg(irqd, vector, cpu);
	वापस 0;
पूर्ण

अटल व्योम clear_irq_vector(काष्ठा irq_data *irqd)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	bool managed = irqd_affinity_is_managed(irqd);
	अचिन्हित पूर्णांक vector = apicd->vector;

	lockdep_निश्चित_held(&vector_lock);

	अगर (!vector)
		वापस;

	trace_vector_clear(irqd->irq, vector, apicd->cpu, apicd->prev_vector,
			   apicd->prev_cpu);

	per_cpu(vector_irq, apicd->cpu)[vector] = VECTOR_SHUTDOWN;
	irq_matrix_मुक्त(vector_matrix, apicd->cpu, vector, managed);
	apicd->vector = 0;

	/* Clean up move in progress */
	vector = apicd->prev_vector;
	अगर (!vector)
		वापस;

	per_cpu(vector_irq, apicd->prev_cpu)[vector] = VECTOR_SHUTDOWN;
	irq_matrix_मुक्त(vector_matrix, apicd->prev_cpu, vector, managed);
	apicd->prev_vector = 0;
	apicd->move_in_progress = 0;
	hlist_del_init(&apicd->clist);
पूर्ण

अटल व्योम x86_vector_deactivate(काष्ठा irq_करोमुख्य *करोm, काष्ठा irq_data *irqd)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	अचिन्हित दीर्घ flags;

	trace_vector_deactivate(irqd->irq, apicd->is_managed,
				apicd->can_reserve, false);

	/* Regular fixed asचिन्हित पूर्णांकerrupt */
	अगर (!apicd->is_managed && !apicd->can_reserve)
		वापस;
	/* If the पूर्णांकerrupt has a global reservation, nothing to करो */
	अगर (apicd->has_reserved)
		वापस;

	raw_spin_lock_irqsave(&vector_lock, flags);
	clear_irq_vector(irqd);
	अगर (apicd->can_reserve)
		reserve_irq_vector_locked(irqd);
	अन्यथा
		vector_assign_managed_shutकरोwn(irqd);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
पूर्ण

अटल पूर्णांक activate_reserved(काष्ठा irq_data *irqd)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	पूर्णांक ret;

	ret = assign_irq_vector_any_locked(irqd);
	अगर (!ret) अणु
		apicd->has_reserved = false;
		/*
		 * Core might have disabled reservation mode after
		 * allocating the irq descriptor. Ideally this should
		 * happen beक्रमe allocation समय, but that would require
		 * completely convoluted ways of transporting that
		 * inक्रमmation.
		 */
		अगर (!irqd_can_reserve(irqd))
			apicd->can_reserve = false;
	पूर्ण

	/*
	 * Check to ensure that the effective affinity mask is a subset
	 * the user supplied affinity mask, and warn the user अगर it is not
	 */
	अगर (!cpumask_subset(irq_data_get_effective_affinity_mask(irqd),
			    irq_data_get_affinity_mask(irqd))) अणु
		pr_warn("irq %u: Affinity broken due to vector space exhaustion.\n",
			irqd->irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक activate_managed(काष्ठा irq_data *irqd)
अणु
	स्थिर काष्ठा cpumask *dest = irq_data_get_affinity_mask(irqd);
	पूर्णांक ret;

	cpumask_and(vector_searchmask, dest, cpu_online_mask);
	अगर (WARN_ON_ONCE(cpumask_empty(vector_searchmask))) अणु
		/* Something in the core code broke! Survive gracefully */
		pr_err("Managed startup for irq %u, but no CPU\n", irqd->irq);
		वापस -EINVAL;
	पूर्ण

	ret = assign_managed_vector(irqd, vector_searchmask);
	/*
	 * This should not happen. The vector reservation got buggered.  Handle
	 * it gracefully.
	 */
	अगर (WARN_ON_ONCE(ret < 0)) अणु
		pr_err("Managed startup irq %u, no vector available\n",
		       irqd->irq);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक x86_vector_activate(काष्ठा irq_करोमुख्य *करोm, काष्ठा irq_data *irqd,
			       bool reserve)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	trace_vector_activate(irqd->irq, apicd->is_managed,
			      apicd->can_reserve, reserve);

	raw_spin_lock_irqsave(&vector_lock, flags);
	अगर (!apicd->can_reserve && !apicd->is_managed)
		assign_irq_vector_any_locked(irqd);
	अन्यथा अगर (reserve || irqd_is_managed_and_shutकरोwn(irqd))
		vector_assign_managed_shutकरोwn(irqd);
	अन्यथा अगर (apicd->is_managed)
		ret = activate_managed(irqd);
	अन्यथा अगर (apicd->has_reserved)
		ret = activate_reserved(irqd);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम vector_मुक्त_reserved_and_managed(काष्ठा irq_data *irqd)
अणु
	स्थिर काष्ठा cpumask *dest = irq_data_get_affinity_mask(irqd);
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);

	trace_vector_tearकरोwn(irqd->irq, apicd->is_managed,
			      apicd->has_reserved);

	अगर (apicd->has_reserved)
		irq_matrix_हटाओ_reserved(vector_matrix);
	अगर (apicd->is_managed)
		irq_matrix_हटाओ_managed(vector_matrix, dest);
पूर्ण

अटल व्योम x86_vector_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा apic_chip_data *apicd;
	काष्ठा irq_data *irqd;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irqd = irq_करोमुख्य_get_irq_data(x86_vector_करोमुख्य, virq + i);
		अगर (irqd && irqd->chip_data) अणु
			raw_spin_lock_irqsave(&vector_lock, flags);
			clear_irq_vector(irqd);
			vector_मुक्त_reserved_and_managed(irqd);
			apicd = irqd->chip_data;
			irq_करोमुख्य_reset_irq_data(irqd);
			raw_spin_unlock_irqrestore(&vector_lock, flags);
			मुक्त_apic_chip_data(apicd);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool vector_configure_legacy(अचिन्हित पूर्णांक virq, काष्ठा irq_data *irqd,
				    काष्ठा apic_chip_data *apicd)
अणु
	अचिन्हित दीर्घ flags;
	bool पुनः_स्मृति = false;

	apicd->vector = ISA_IRQ_VECTOR(virq);
	apicd->cpu = 0;

	raw_spin_lock_irqsave(&vector_lock, flags);
	/*
	 * If the पूर्णांकerrupt is activated, then it must stay at this vector
	 * position. That's usually the समयr पूर्णांकerrupt (0).
	 */
	अगर (irqd_is_activated(irqd)) अणु
		trace_vector_setup(virq, true, 0);
		apic_update_irq_cfg(irqd, apicd->vector, apicd->cpu);
	पूर्ण अन्यथा अणु
		/* Release the vector */
		apicd->can_reserve = true;
		irqd_set_can_reserve(irqd);
		clear_irq_vector(irqd);
		पुनः_स्मृति = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	वापस पुनः_स्मृति;
पूर्ण

अटल पूर्णांक x86_vector_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा apic_chip_data *apicd;
	काष्ठा irq_data *irqd;
	पूर्णांक i, err, node;

	अगर (disable_apic)
		वापस -ENXIO;

	/* Currently vector allocator can't guarantee contiguous allocations */
	अगर ((info->flags & X86_IRQ_ALLOC_CONTIGUOUS_VECTORS) && nr_irqs > 1)
		वापस -ENOSYS;

	/*
	 * Catch any attempt to touch the cascade पूर्णांकerrupt on a PIC
	 * equipped प्रणाली.
	 */
	अगर (WARN_ON_ONCE(info->flags & X86_IRQ_ALLOC_LEGACY &&
			 virq == PIC_CASCADE_IR))
		वापस -EINVAL;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		BUG_ON(!irqd);
		node = irq_data_get_node(irqd);
		WARN_ON_ONCE(irqd->chip_data);
		apicd = alloc_apic_chip_data(node);
		अगर (!apicd) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण

		apicd->irq = virq + i;
		irqd->chip = &lapic_controller;
		irqd->chip_data = apicd;
		irqd->hwirq = virq + i;
		irqd_set_single_target(irqd);
		/*
		 * Prevent that any of these पूर्णांकerrupts is invoked in
		 * non पूर्णांकerrupt context via e.g. generic_handle_irq()
		 * as that can corrupt the affinity move state.
		 */
		irqd_set_handle_enक्रमce_irqctx(irqd);

		/* Don't invoke affinity setter on deactivated पूर्णांकerrupts */
		irqd_set_affinity_on_activate(irqd);

		/*
		 * Legacy vectors are alपढ़ोy asचिन्हित when the IOAPIC
		 * takes them over. They stay on the same vector. This is
		 * required क्रम check_समयr() to work correctly as it might
		 * चयन back to legacy mode. Only update the hardware
		 * config.
		 */
		अगर (info->flags & X86_IRQ_ALLOC_LEGACY) अणु
			अगर (!vector_configure_legacy(virq + i, irqd, apicd))
				जारी;
		पूर्ण

		err = assign_irq_vector_policy(irqd, info);
		trace_vector_setup(virq + i, false, err);
		अगर (err) अणु
			irqd->chip_data = शून्य;
			मुक्त_apic_chip_data(apicd);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	x86_vector_मुक्त_irqs(करोमुख्य, virq, i);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
अटल व्योम x86_vector_debug_show(काष्ठा seq_file *m, काष्ठा irq_करोमुख्य *d,
				  काष्ठा irq_data *irqd, पूर्णांक ind)
अणु
	काष्ठा apic_chip_data apicd;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq;

	अगर (!irqd) अणु
		irq_matrix_debug_show(m, vector_matrix, ind);
		वापस;
	पूर्ण

	irq = irqd->irq;
	अगर (irq < nr_legacy_irqs() && !test_bit(irq, &io_apic_irqs)) अणु
		seq_म_लिखो(m, "%*sVector: %5d\n", ind, "", ISA_IRQ_VECTOR(irq));
		seq_म_लिखो(m, "%*sTarget: Legacy PIC all CPUs\n", ind, "");
		वापस;
	पूर्ण

	अगर (!irqd->chip_data) अणु
		seq_म_लिखो(m, "%*sVector: Not assigned\n", ind, "");
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&vector_lock, flags);
	स_नकल(&apicd, irqd->chip_data, माप(apicd));
	raw_spin_unlock_irqrestore(&vector_lock, flags);

	seq_म_लिखो(m, "%*sVector: %5u\n", ind, "", apicd.vector);
	seq_म_लिखो(m, "%*sTarget: %5u\n", ind, "", apicd.cpu);
	अगर (apicd.prev_vector) अणु
		seq_म_लिखो(m, "%*sPrevious vector: %5u\n", ind, "", apicd.prev_vector);
		seq_म_लिखो(m, "%*sPrevious target: %5u\n", ind, "", apicd.prev_cpu);
	पूर्ण
	seq_म_लिखो(m, "%*smove_in_progress: %u\n", ind, "", apicd.move_in_progress ? 1 : 0);
	seq_म_लिखो(m, "%*sis_managed:       %u\n", ind, "", apicd.is_managed ? 1 : 0);
	seq_म_लिखो(m, "%*scan_reserve:      %u\n", ind, "", apicd.can_reserve ? 1 : 0);
	seq_म_लिखो(m, "%*shas_reserved:     %u\n", ind, "", apicd.has_reserved ? 1 : 0);
	seq_म_लिखो(m, "%*scleanup_pending:  %u\n", ind, "", !hlist_unhashed(&apicd.clist));
पूर्ण
#पूर्ण_अगर

पूर्णांक x86_fwspec_is_ioapic(काष्ठा irq_fwspec *fwspec)
अणु
	अगर (fwspec->param_count != 1)
		वापस 0;

	अगर (is_fwnode_irqchip(fwspec->fwnode)) अणु
		स्थिर अक्षर *fwname = fwnode_get_name(fwspec->fwnode);
		वापस fwname && !म_भेदन(fwname, "IO-APIC-", 8) &&
			simple_म_से_दीर्घ(fwname+8, शून्य, 10) == fwspec->param[0];
	पूर्ण
	वापस to_of_node(fwspec->fwnode) &&
		of_device_is_compatible(to_of_node(fwspec->fwnode),
					"intel,ce4100-ioapic");
पूर्ण

पूर्णांक x86_fwspec_is_hpet(काष्ठा irq_fwspec *fwspec)
अणु
	अगर (fwspec->param_count != 1)
		वापस 0;

	अगर (is_fwnode_irqchip(fwspec->fwnode)) अणु
		स्थिर अक्षर *fwname = fwnode_get_name(fwspec->fwnode);
		वापस fwname && !म_भेदन(fwname, "HPET-MSI-", 9) &&
			simple_म_से_दीर्घ(fwname+9, शून्य, 10) == fwspec->param[0];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक x86_vector_select(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
			     क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/*
	 * HPET and I/OAPIC cannot be parented in the vector करोमुख्य
	 * अगर IRQ remapping is enabled. APIC IDs above 15 bits are
	 * only permitted अगर IRQ remapping is enabled, so check that.
	 */
	अगर (apic->apic_id_valid(32768))
		वापस 0;

	वापस x86_fwspec_is_ioapic(fwspec) || x86_fwspec_is_hpet(fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops x86_vector_करोमुख्य_ops = अणु
	.select		= x86_vector_select,
	.alloc		= x86_vector_alloc_irqs,
	.मुक्त		= x86_vector_मुक्त_irqs,
	.activate	= x86_vector_activate,
	.deactivate	= x86_vector_deactivate,
#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
	.debug_show	= x86_vector_debug_show,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init arch_probe_nr_irqs(व्योम)
अणु
	पूर्णांक nr;

	अगर (nr_irqs > (NR_VECTORS * nr_cpu_ids))
		nr_irqs = NR_VECTORS * nr_cpu_ids;

	nr = (gsi_top + nr_legacy_irqs()) + 8 * nr_cpu_ids;
#अगर defined(CONFIG_PCI_MSI)
	/*
	 * क्रम MSI and HT dyn irq
	 */
	अगर (gsi_top <= NR_IRQS_LEGACY)
		nr +=  8 * nr_cpu_ids;
	अन्यथा
		nr += gsi_top * 16;
#पूर्ण_अगर
	अगर (nr < nr_irqs)
		nr_irqs = nr;

	/*
	 * We करोn't know अगर PIC is present at this poपूर्णांक so we need to करो
	 * probe() to get the right number of legacy IRQs.
	 */
	वापस legacy_pic->probe();
पूर्ण

व्योम lapic_assign_legacy_vector(अचिन्हित पूर्णांक irq, bool replace)
अणु
	/*
	 * Use assign प्रणाली here so it wont get accounted as allocated
	 * and moveable in the cpu hotplug check and it prevents managed
	 * irq reservation from touching it.
	 */
	irq_matrix_assign_प्रणाली(vector_matrix, ISA_IRQ_VECTOR(irq), replace);
पूर्ण

व्योम __init lapic_update_legacy_vectors(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (IS_ENABLED(CONFIG_X86_IO_APIC) && nr_ioapics > 0)
		वापस;

	/*
	 * If the IO/APIC is disabled via config, kernel command line or
	 * lack of क्रमागतeration then all legacy पूर्णांकerrupts are routed
	 * through the PIC. Make sure that they are marked as legacy
	 * vectors. PIC_CASCADE_IRQ has alपढ़ोy been marked in
	 * lapic_assign_प्रणाली_vectors().
	 */
	क्रम (i = 0; i < nr_legacy_irqs(); i++) अणु
		अगर (i != PIC_CASCADE_IR)
			lapic_assign_legacy_vector(i, true);
	पूर्ण
पूर्ण

व्योम __init lapic_assign_प्रणाली_vectors(व्योम)
अणु
	अचिन्हित पूर्णांक i, vector = 0;

	क्रम_each_set_bit_from(vector, प्रणाली_vectors, NR_VECTORS)
		irq_matrix_assign_प्रणाली(vector_matrix, vector, false);

	अगर (nr_legacy_irqs() > 1)
		lapic_assign_legacy_vector(PIC_CASCADE_IR, false);

	/* System vectors are reserved, online it */
	irq_matrix_online(vector_matrix);

	/* Mark the pपुनः_स्मृतिated legacy पूर्णांकerrupts */
	क्रम (i = 0; i < nr_legacy_irqs(); i++) अणु
		/*
		 * Don't touch the cascade interrupt. It's unusable
		 * on PIC equipped machines. See the large comment
		 * in the IO/APIC code.
		 */
		अगर (i != PIC_CASCADE_IR)
			irq_matrix_assign(vector_matrix, ISA_IRQ_VECTOR(i));
	पूर्ण
पूर्ण

पूर्णांक __init arch_early_irq_init(व्योम)
अणु
	काष्ठा fwnode_handle *fn;

	fn = irq_करोमुख्य_alloc_named_fwnode("VECTOR");
	BUG_ON(!fn);
	x86_vector_करोमुख्य = irq_करोमुख्य_create_tree(fn, &x86_vector_करोमुख्य_ops,
						   शून्य);
	BUG_ON(x86_vector_करोमुख्य == शून्य);
	irq_set_शेष_host(x86_vector_करोमुख्य);

	BUG_ON(!alloc_cpumask_var(&vector_searchmask, GFP_KERNEL));

	/*
	 * Allocate the vector matrix allocator data काष्ठाure and limit the
	 * search area.
	 */
	vector_matrix = irq_alloc_matrix(NR_VECTORS, FIRST_EXTERNAL_VECTOR,
					 FIRST_SYSTEM_VECTOR);
	BUG_ON(!vector_matrix);

	वापस arch_early_ioapic_init();
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल काष्ठा irq_desc *__setup_vector_irq(पूर्णांक vector)
अणु
	पूर्णांक isairq = vector - ISA_IRQ_VECTOR(0);

	/* Check whether the irq is in the legacy space */
	अगर (isairq < 0 || isairq >= nr_legacy_irqs())
		वापस VECTOR_UNUSED;
	/* Check whether the irq is handled by the IOAPIC */
	अगर (test_bit(isairq, &io_apic_irqs))
		वापस VECTOR_UNUSED;
	वापस irq_to_desc(isairq);
पूर्ण

/* Online the local APIC infraकाष्ठाure and initialize the vectors */
व्योम lapic_online(व्योम)
अणु
	अचिन्हित पूर्णांक vector;

	lockdep_निश्चित_held(&vector_lock);

	/* Online the vector matrix array क्रम this CPU */
	irq_matrix_online(vector_matrix);

	/*
	 * The पूर्णांकerrupt affinity logic never tarमाला_लो पूर्णांकerrupts to offline
	 * CPUs. The exception are the legacy PIC पूर्णांकerrupts. In general
	 * they are only targeted to CPU0, but depending on the platक्रमm
	 * they can be distributed to any online CPU in hardware. The
	 * kernel has no influence on that. So all active legacy vectors
	 * must be installed on all CPUs. All non legacy पूर्णांकerrupts can be
	 * cleared.
	 */
	क्रम (vector = 0; vector < NR_VECTORS; vector++)
		this_cpu_ग_लिखो(vector_irq[vector], __setup_vector_irq(vector));
पूर्ण

व्योम lapic_offline(व्योम)
अणु
	lock_vector_lock();
	irq_matrix_offline(vector_matrix);
	unlock_vector_lock();
पूर्ण

अटल पूर्णांक apic_set_affinity(काष्ठा irq_data *irqd,
			     स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	पूर्णांक err;

	अगर (WARN_ON_ONCE(!irqd_is_activated(irqd)))
		वापस -EIO;

	raw_spin_lock(&vector_lock);
	cpumask_and(vector_searchmask, dest, cpu_online_mask);
	अगर (irqd_affinity_is_managed(irqd))
		err = assign_managed_vector(irqd, vector_searchmask);
	अन्यथा
		err = assign_vector_locked(irqd, vector_searchmask);
	raw_spin_unlock(&vector_lock);
	वापस err ? err : IRQ_SET_MASK_OK;
पूर्ण

#अन्यथा
# define apic_set_affinity	शून्य
#पूर्ण_अगर

अटल पूर्णांक apic_retrigger_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा apic_chip_data *apicd = apic_chip_data(irqd);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&vector_lock, flags);
	apic->send_IPI(apicd->cpu, apicd->vector);
	raw_spin_unlock_irqrestore(&vector_lock, flags);

	वापस 1;
पूर्ण

व्योम apic_ack_irq(काष्ठा irq_data *irqd)
अणु
	irq_move_irq(irqd);
	ack_APIC_irq();
पूर्ण

व्योम apic_ack_edge(काष्ठा irq_data *irqd)
अणु
	irq_complete_move(irqd_cfg(irqd));
	apic_ack_irq(irqd);
पूर्ण

अटल व्योम x86_vector_msi_compose_msg(काष्ठा irq_data *data,
				       काष्ठा msi_msg *msg)
अणु
       __irq_msi_compose_msg(irqd_cfg(data), msg, false);
पूर्ण

अटल काष्ठा irq_chip lapic_controller = अणु
	.name			= "APIC",
	.irq_ack		= apic_ack_edge,
	.irq_set_affinity	= apic_set_affinity,
	.irq_compose_msi_msg	= x86_vector_msi_compose_msg,
	.irq_retrigger		= apic_retrigger_irq,
पूर्ण;

#अगर_घोषित CONFIG_SMP

अटल व्योम मुक्त_moved_vector(काष्ठा apic_chip_data *apicd)
अणु
	अचिन्हित पूर्णांक vector = apicd->prev_vector;
	अचिन्हित पूर्णांक cpu = apicd->prev_cpu;
	bool managed = apicd->is_managed;

	/*
	 * Managed पूर्णांकerrupts are usually not migrated away
	 * from an online CPU, but CPU isolation 'managed_irq'
	 * can make that happen.
	 * 1) Activation करोes not take the isolation पूर्णांकo account
	 *    to keep the code simple
	 * 2) Migration away from an isolated CPU can happen when
	 *    a non-isolated CPU which is in the calculated
	 *    affinity mask comes online.
	 */
	trace_vector_मुक्त_moved(apicd->irq, cpu, vector, managed);
	irq_matrix_मुक्त(vector_matrix, cpu, vector, managed);
	per_cpu(vector_irq, cpu)[vector] = VECTOR_UNUSED;
	hlist_del_init(&apicd->clist);
	apicd->prev_vector = 0;
	apicd->move_in_progress = 0;
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_irq_move_cleanup)
अणु
	काष्ठा hlist_head *clhead = this_cpu_ptr(&cleanup_list);
	काष्ठा apic_chip_data *apicd;
	काष्ठा hlist_node *पंचांगp;

	ack_APIC_irq();
	/* Prevent vectors vanishing under us */
	raw_spin_lock(&vector_lock);

	hlist_क्रम_each_entry_safe(apicd, पंचांगp, clhead, clist) अणु
		अचिन्हित पूर्णांक irr, vector = apicd->prev_vector;

		/*
		 * Paranoia: Check अगर the vector that needs to be cleaned
		 * up is रेजिस्टरed at the APICs IRR. If so, then this is
		 * not the best समय to clean it up. Clean it up in the
		 * next attempt by sending another IRQ_MOVE_CLEANUP_VECTOR
		 * to this CPU. IRQ_MOVE_CLEANUP_VECTOR is the lowest
		 * priority बाह्यal vector, so on वापस from this
		 * पूर्णांकerrupt the device पूर्णांकerrupt will happen first.
		 */
		irr = apic_पढ़ो(APIC_IRR + (vector / 32 * 0x10));
		अगर (irr & (1U << (vector % 32))) अणु
			apic->send_IPI_self(IRQ_MOVE_CLEANUP_VECTOR);
			जारी;
		पूर्ण
		मुक्त_moved_vector(apicd);
	पूर्ण

	raw_spin_unlock(&vector_lock);
पूर्ण

अटल व्योम __send_cleanup_vector(काष्ठा apic_chip_data *apicd)
अणु
	अचिन्हित पूर्णांक cpu;

	raw_spin_lock(&vector_lock);
	apicd->move_in_progress = 0;
	cpu = apicd->prev_cpu;
	अगर (cpu_online(cpu)) अणु
		hlist_add_head(&apicd->clist, per_cpu_ptr(&cleanup_list, cpu));
		apic->send_IPI(cpu, IRQ_MOVE_CLEANUP_VECTOR);
	पूर्ण अन्यथा अणु
		apicd->prev_vector = 0;
	पूर्ण
	raw_spin_unlock(&vector_lock);
पूर्ण

व्योम send_cleanup_vector(काष्ठा irq_cfg *cfg)
अणु
	काष्ठा apic_chip_data *apicd;

	apicd = container_of(cfg, काष्ठा apic_chip_data, hw_irq_cfg);
	अगर (apicd->move_in_progress)
		__send_cleanup_vector(apicd);
पूर्ण

व्योम irq_complete_move(काष्ठा irq_cfg *cfg)
अणु
	काष्ठा apic_chip_data *apicd;

	apicd = container_of(cfg, काष्ठा apic_chip_data, hw_irq_cfg);
	अगर (likely(!apicd->move_in_progress))
		वापस;

	/*
	 * If the पूर्णांकerrupt arrived on the new target CPU, cleanup the
	 * vector on the old target CPU. A vector check is not required
	 * because an पूर्णांकerrupt can never move from one vector to another
	 * on the same CPU.
	 */
	अगर (apicd->cpu == smp_processor_id())
		__send_cleanup_vector(apicd);
पूर्ण

/*
 * Called from fixup_irqs() with @desc->lock held and पूर्णांकerrupts disabled.
 */
व्योम irq_क्रमce_complete_move(काष्ठा irq_desc *desc)
अणु
	काष्ठा apic_chip_data *apicd;
	काष्ठा irq_data *irqd;
	अचिन्हित पूर्णांक vector;

	/*
	 * The function is called क्रम all descriptors regardless of which
	 * irqकरोमुख्य they beदीर्घ to. For example अगर an IRQ is provided by
	 * an irq_chip as part of a GPIO driver, the chip data क्रम that
	 * descriptor is specअगरic to the irq_chip in question.
	 *
	 * Check first that the chip_data is what we expect
	 * (apic_chip_data) beक्रमe touching it any further.
	 */
	irqd = irq_करोमुख्य_get_irq_data(x86_vector_करोमुख्य,
				       irq_desc_get_irq(desc));
	अगर (!irqd)
		वापस;

	raw_spin_lock(&vector_lock);
	apicd = apic_chip_data(irqd);
	अगर (!apicd)
		जाओ unlock;

	/*
	 * If prev_vector is empty, no action required.
	 */
	vector = apicd->prev_vector;
	अगर (!vector)
		जाओ unlock;

	/*
	 * This is tricky. If the cleanup of the old vector has not been
	 * करोne yet, then the following setaffinity call will fail with
	 * -EBUSY. This can leave the पूर्णांकerrupt in a stale state.
	 *
	 * All CPUs are stuck in stop machine with पूर्णांकerrupts disabled so
	 * calling __irq_complete_move() would be completely poपूर्णांकless.
	 *
	 * 1) The पूर्णांकerrupt is in move_in_progress state. That means that we
	 *    have not seen an पूर्णांकerrupt since the io_apic was reprogrammed to
	 *    the new vector.
	 *
	 * 2) The पूर्णांकerrupt has fired on the new vector, but the cleanup IPIs
	 *    have not been processed yet.
	 */
	अगर (apicd->move_in_progress) अणु
		/*
		 * In theory there is a race:
		 *
		 * set_ioapic(new_vector) <-- Interrupt is उठाओd beक्रमe update
		 *			      is effective, i.e. it's उठाओd on
		 *			      the old vector.
		 *
		 * So अगर the target cpu cannot handle that पूर्णांकerrupt beक्रमe
		 * the old vector is cleaned up, we get a spurious पूर्णांकerrupt
		 * and in the worst हाल the ioapic irq line becomes stale.
		 *
		 * But in हाल of cpu hotplug this should be a non issue
		 * because अगर the affinity update happens right beक्रमe all
		 * cpus rendezvous in stop machine, there is no way that the
		 * पूर्णांकerrupt can be blocked on the target cpu because all cpus
		 * loops first with पूर्णांकerrupts enabled in stop machine, so the
		 * old vector is not yet cleaned up when the पूर्णांकerrupt fires.
		 *
		 * So the only way to run पूर्णांकo this issue is अगर the delivery
		 * of the पूर्णांकerrupt on the apic/प्रणाली bus would be delayed
		 * beyond the poपूर्णांक where the target cpu disables पूर्णांकerrupts
		 * in stop machine. I करोubt that it can happen, but at least
		 * there is a theoretical chance. Virtualization might be
		 * able to expose this, but AFAICT the IOAPIC emulation is not
		 * as stupid as the real hardware.
		 *
		 * Anyway, there is nothing we can करो about that at this poपूर्णांक
		 * w/o refactoring the whole fixup_irq() business completely.
		 * We prपूर्णांक at least the irq number and the old vector number,
		 * so we have the necessary inक्रमmation when a problem in that
		 * area arises.
		 */
		pr_warn("IRQ fixup: irq %d move in progress, old vector %d\n",
			irqd->irq, vector);
	पूर्ण
	मुक्त_moved_vector(apicd);
unlock:
	raw_spin_unlock(&vector_lock);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * Note, this is not accurate accounting, but at least good enough to
 * prevent that the actual पूर्णांकerrupt move will run out of vectors.
 */
पूर्णांक lapic_can_unplug_cpu(व्योम)
अणु
	अचिन्हित पूर्णांक rsvd, avl, tomove, cpu = smp_processor_id();
	पूर्णांक ret = 0;

	raw_spin_lock(&vector_lock);
	tomove = irq_matrix_allocated(vector_matrix);
	avl = irq_matrix_available(vector_matrix, true);
	अगर (avl < tomove) अणु
		pr_warn("CPU %u has %u vectors, %u available. Cannot disable CPU\n",
			cpu, tomove, avl);
		ret = -ENOSPC;
		जाओ out;
	पूर्ण
	rsvd = irq_matrix_reserved(vector_matrix);
	अगर (avl < rsvd) अणु
		pr_warn("Reserved vectors %u > available %u. IRQ request may fail\n",
			rsvd, avl);
	पूर्ण
out:
	raw_spin_unlock(&vector_lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* HOTPLUG_CPU */
#पूर्ण_अगर /* SMP */

अटल व्योम __init prपूर्णांक_APIC_field(पूर्णांक base)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG);

	क्रम (i = 0; i < 8; i++)
		pr_cont("%08x", apic_पढ़ो(base + i*0x10));

	pr_cont("\n");
पूर्ण

अटल व्योम __init prपूर्णांक_local_APIC(व्योम *dummy)
अणु
	अचिन्हित पूर्णांक i, v, ver, maxlvt;
	u64 icr;

	pr_debug("printing local APIC contents on CPU#%d/%d:\n",
		 smp_processor_id(), hard_smp_processor_id());
	v = apic_पढ़ो(APIC_ID);
	pr_info("... APIC ID:      %08x (%01x)\n", v, पढ़ो_apic_id());
	v = apic_पढ़ो(APIC_LVR);
	pr_info("... APIC VERSION: %08x\n", v);
	ver = GET_APIC_VERSION(v);
	maxlvt = lapic_get_maxlvt();

	v = apic_पढ़ो(APIC_TASKPRI);
	pr_debug("... APIC TASKPRI: %08x (%02x)\n", v, v & APIC_TPRI_MASK);

	/* !82489DX */
	अगर (APIC_INTEGRATED(ver)) अणु
		अगर (!APIC_XAPIC(ver)) अणु
			v = apic_पढ़ो(APIC_ARBPRI);
			pr_debug("... APIC ARBPRI: %08x (%02x)\n",
				 v, v & APIC_ARBPRI_MASK);
		पूर्ण
		v = apic_पढ़ो(APIC_PROCPRI);
		pr_debug("... APIC PROCPRI: %08x\n", v);
	पूर्ण

	/*
	 * Remote पढ़ो supported only in the 82489DX and local APIC क्रम
	 * Pentium processors.
	 */
	अगर (!APIC_INTEGRATED(ver) || maxlvt == 3) अणु
		v = apic_पढ़ो(APIC_RRR);
		pr_debug("... APIC RRR: %08x\n", v);
	पूर्ण

	v = apic_पढ़ो(APIC_LDR);
	pr_debug("... APIC LDR: %08x\n", v);
	अगर (!x2apic_enabled()) अणु
		v = apic_पढ़ो(APIC_DFR);
		pr_debug("... APIC DFR: %08x\n", v);
	पूर्ण
	v = apic_पढ़ो(APIC_SPIV);
	pr_debug("... APIC SPIV: %08x\n", v);

	pr_debug("... APIC ISR field:\n");
	prपूर्णांक_APIC_field(APIC_ISR);
	pr_debug("... APIC TMR field:\n");
	prपूर्णांक_APIC_field(APIC_TMR);
	pr_debug("... APIC IRR field:\n");
	prपूर्णांक_APIC_field(APIC_IRR);

	/* !82489DX */
	अगर (APIC_INTEGRATED(ver)) अणु
		/* Due to the Pentium erratum 3AP. */
		अगर (maxlvt > 3)
			apic_ग_लिखो(APIC_ESR, 0);

		v = apic_पढ़ो(APIC_ESR);
		pr_debug("... APIC ESR: %08x\n", v);
	पूर्ण

	icr = apic_icr_पढ़ो();
	pr_debug("... APIC ICR: %08x\n", (u32)icr);
	pr_debug("... APIC ICR2: %08x\n", (u32)(icr >> 32));

	v = apic_पढ़ो(APIC_LVTT);
	pr_debug("... APIC LVTT: %08x\n", v);

	अगर (maxlvt > 3) अणु
		/* PC is LVT#4. */
		v = apic_पढ़ो(APIC_LVTPC);
		pr_debug("... APIC LVTPC: %08x\n", v);
	पूर्ण
	v = apic_पढ़ो(APIC_LVT0);
	pr_debug("... APIC LVT0: %08x\n", v);
	v = apic_पढ़ो(APIC_LVT1);
	pr_debug("... APIC LVT1: %08x\n", v);

	अगर (maxlvt > 2) अणु
		/* ERR is LVT#3. */
		v = apic_पढ़ो(APIC_LVTERR);
		pr_debug("... APIC LVTERR: %08x\n", v);
	पूर्ण

	v = apic_पढ़ो(APIC_TMICT);
	pr_debug("... APIC TMICT: %08x\n", v);
	v = apic_पढ़ो(APIC_TMCCT);
	pr_debug("... APIC TMCCT: %08x\n", v);
	v = apic_पढ़ो(APIC_TDCR);
	pr_debug("... APIC TDCR: %08x\n", v);

	अगर (boot_cpu_has(X86_FEATURE_EXTAPIC)) अणु
		v = apic_पढ़ो(APIC_EFEAT);
		maxlvt = (v >> 16) & 0xff;
		pr_debug("... APIC EFEAT: %08x\n", v);
		v = apic_पढ़ो(APIC_ECTRL);
		pr_debug("... APIC ECTRL: %08x\n", v);
		क्रम (i = 0; i < maxlvt; i++) अणु
			v = apic_पढ़ो(APIC_EILVTn(i));
			pr_debug("... APIC EILVT%d: %08x\n", i, v);
		पूर्ण
	पूर्ण
	pr_cont("\n");
पूर्ण

अटल व्योम __init prपूर्णांक_local_APICs(पूर्णांक maxcpu)
अणु
	पूर्णांक cpu;

	अगर (!maxcpu)
		वापस;

	preempt_disable();
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu >= maxcpu)
			अवरोध;
		smp_call_function_single(cpu, prपूर्णांक_local_APIC, शून्य, 1);
	पूर्ण
	preempt_enable();
पूर्ण

अटल व्योम __init prपूर्णांक_PIC(व्योम)
अणु
	अचिन्हित पूर्णांक v;
	अचिन्हित दीर्घ flags;

	अगर (!nr_legacy_irqs())
		वापस;

	pr_debug("\nprinting PIC contents\n");

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	v = inb(0xa1) << 8 | inb(0x21);
	pr_debug("... PIC  IMR: %04x\n", v);

	v = inb(0xa0) << 8 | inb(0x20);
	pr_debug("... PIC  IRR: %04x\n", v);

	outb(0x0b, 0xa0);
	outb(0x0b, 0x20);
	v = inb(0xa0) << 8 | inb(0x20);
	outb(0x0a, 0xa0);
	outb(0x0a, 0x20);

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);

	pr_debug("... PIC  ISR: %04x\n", v);

	v = inb(0x4d1) << 8 | inb(0x4d0);
	pr_debug("... PIC ELCR: %04x\n", v);
पूर्ण

अटल पूर्णांक show_lapic __initdata = 1;
अटल __init पूर्णांक setup_show_lapic(अक्षर *arg)
अणु
	पूर्णांक num = -1;

	अगर (म_भेद(arg, "all") == 0) अणु
		show_lapic = CONFIG_NR_CPUS;
	पूर्ण अन्यथा अणु
		get_option(&arg, &num);
		अगर (num >= 0)
			show_lapic = num;
	पूर्ण

	वापस 1;
पूर्ण
__setup("show_lapic=", setup_show_lapic);

अटल पूर्णांक __init prपूर्णांक_ICs(व्योम)
अणु
	अगर (apic_verbosity == APIC_QUIET)
		वापस 0;

	prपूर्णांक_PIC();

	/* करोn't prपूर्णांक out अगर apic is not there */
	अगर (!boot_cpu_has(X86_FEATURE_APIC) && !apic_from_smp_config())
		वापस 0;

	prपूर्णांक_local_APICs(show_lapic);
	prपूर्णांक_IO_APICs();

	वापस 0;
पूर्ण

late_initcall(prपूर्णांक_ICs);
