<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cpu_rmap.c: CPU affinity reverse-map support
 * Copyright 2011 Solarflare Communications Inc.
 */

#समावेश <linux/cpu_rmap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>

/*
 * These functions मुख्यtain a mapping from CPUs to some ordered set of
 * objects with CPU affinities.  This can be seen as a reverse-map of
 * CPU affinity.  However, we करो not assume that the object affinities
 * cover all CPUs in the प्रणाली.  For those CPUs not directly covered
 * by object affinities, we attempt to find a nearest object based on
 * CPU topology.
 */

/**
 * alloc_cpu_rmap - allocate CPU affinity reverse-map
 * @size: Number of objects to be mapped
 * @flags: Allocation flags e.g. %GFP_KERNEL
 */
काष्ठा cpu_rmap *alloc_cpu_rmap(अचिन्हित पूर्णांक size, gfp_t flags)
अणु
	काष्ठा cpu_rmap *rmap;
	अचिन्हित पूर्णांक cpu;
	माप_प्रकार obj_offset;

	/* This is a silly number of objects, and we use u16 indices. */
	अगर (size > 0xffff)
		वापस शून्य;

	/* Offset of object poपूर्णांकer array from base काष्ठाure */
	obj_offset = ALIGN(दुरत्व(काष्ठा cpu_rmap, near[nr_cpu_ids]),
			   माप(व्योम *));

	rmap = kzalloc(obj_offset + size * माप(rmap->obj[0]), flags);
	अगर (!rmap)
		वापस शून्य;

	kref_init(&rmap->refcount);
	rmap->obj = (व्योम **)((अक्षर *)rmap + obj_offset);

	/* Initially assign CPUs to objects on a rota, since we have
	 * no idea where the objects are.  Use infinite distance, so
	 * any object with known distance is preferable.  Include the
	 * CPUs that are not present/online, since we definitely want
	 * any newly-hotplugged CPUs to have some object asचिन्हित.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		rmap->near[cpu].index = cpu % size;
		rmap->near[cpu].dist = CPU_RMAP_DIST_INF;
	पूर्ण

	rmap->size = size;
	वापस rmap;
पूर्ण
EXPORT_SYMBOL(alloc_cpu_rmap);

/**
 * cpu_rmap_release - पूर्णांकernal reclaiming helper called from kref_put
 * @ref: kref to काष्ठा cpu_rmap
 */
अटल व्योम cpu_rmap_release(काष्ठा kref *ref)
अणु
	काष्ठा cpu_rmap *rmap = container_of(ref, काष्ठा cpu_rmap, refcount);
	kमुक्त(rmap);
पूर्ण

/**
 * cpu_rmap_get - पूर्णांकernal helper to get new ref on a cpu_rmap
 * @rmap: reverse-map allocated with alloc_cpu_rmap()
 */
अटल अंतरभूत व्योम cpu_rmap_get(काष्ठा cpu_rmap *rmap)
अणु
	kref_get(&rmap->refcount);
पूर्ण

/**
 * cpu_rmap_put - release ref on a cpu_rmap
 * @rmap: reverse-map allocated with alloc_cpu_rmap()
 */
पूर्णांक cpu_rmap_put(काष्ठा cpu_rmap *rmap)
अणु
	वापस kref_put(&rmap->refcount, cpu_rmap_release);
पूर्ण
EXPORT_SYMBOL(cpu_rmap_put);

/* Reevaluate nearest object क्रम given CPU, comparing with the given
 * neighbours at the given distance.
 */
अटल bool cpu_rmap_copy_neigh(काष्ठा cpu_rmap *rmap, अचिन्हित पूर्णांक cpu,
				स्थिर काष्ठा cpumask *mask, u16 dist)
अणु
	पूर्णांक neigh;

	क्रम_each_cpu(neigh, mask) अणु
		अगर (rmap->near[cpu].dist > dist &&
		    rmap->near[neigh].dist <= dist) अणु
			rmap->near[cpu].index = rmap->near[neigh].index;
			rmap->near[cpu].dist = dist;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम debug_prपूर्णांक_rmap(स्थिर काष्ठा cpu_rmap *rmap, स्थिर अक्षर *prefix)
अणु
	अचिन्हित index;
	अचिन्हित पूर्णांक cpu;

	pr_info("cpu_rmap %p, %s:\n", rmap, prefix);

	क्रम_each_possible_cpu(cpu) अणु
		index = rmap->near[cpu].index;
		pr_info("cpu %d -> obj %u (distance %u)\n",
			cpu, index, rmap->near[cpu].dist);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
debug_prपूर्णांक_rmap(स्थिर काष्ठा cpu_rmap *rmap, स्थिर अक्षर *prefix)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * cpu_rmap_add - add object to a rmap
 * @rmap: CPU rmap allocated with alloc_cpu_rmap()
 * @obj: Object to add to rmap
 *
 * Return index of object.
 */
पूर्णांक cpu_rmap_add(काष्ठा cpu_rmap *rmap, व्योम *obj)
अणु
	u16 index;

	BUG_ON(rmap->used >= rmap->size);
	index = rmap->used++;
	rmap->obj[index] = obj;
	वापस index;
पूर्ण
EXPORT_SYMBOL(cpu_rmap_add);

/**
 * cpu_rmap_update - update CPU rmap following a change of object affinity
 * @rmap: CPU rmap to update
 * @index: Index of object whose affinity changed
 * @affinity: New CPU affinity of object
 */
पूर्णांक cpu_rmap_update(काष्ठा cpu_rmap *rmap, u16 index,
		    स्थिर काष्ठा cpumask *affinity)
अणु
	cpumask_var_t update_mask;
	अचिन्हित पूर्णांक cpu;

	अगर (unlikely(!zalloc_cpumask_var(&update_mask, GFP_KERNEL)))
		वापस -ENOMEM;

	/* Invalidate distance क्रम all CPUs क्रम which this used to be
	 * the nearest object.  Mark those CPUs क्रम update.
	 */
	क्रम_each_online_cpu(cpu) अणु
		अगर (rmap->near[cpu].index == index) अणु
			rmap->near[cpu].dist = CPU_RMAP_DIST_INF;
			cpumask_set_cpu(cpu, update_mask);
		पूर्ण
	पूर्ण

	debug_prपूर्णांक_rmap(rmap, "after invalidating old distances");

	/* Set distance to 0 क्रम all CPUs in the new affinity mask.
	 * Mark all CPUs within their NUMA nodes क्रम update.
	 */
	क्रम_each_cpu(cpu, affinity) अणु
		rmap->near[cpu].index = index;
		rmap->near[cpu].dist = 0;
		cpumask_or(update_mask, update_mask,
			   cpumask_of_node(cpu_to_node(cpu)));
	पूर्ण

	debug_prपूर्णांक_rmap(rmap, "after updating neighbours");

	/* Update distances based on topology */
	क्रम_each_cpu(cpu, update_mask) अणु
		अगर (cpu_rmap_copy_neigh(rmap, cpu,
					topology_sibling_cpumask(cpu), 1))
			जारी;
		अगर (cpu_rmap_copy_neigh(rmap, cpu,
					topology_core_cpumask(cpu), 2))
			जारी;
		अगर (cpu_rmap_copy_neigh(rmap, cpu,
					cpumask_of_node(cpu_to_node(cpu)), 3))
			जारी;
		/* We could जारी पूर्णांकo NUMA node distances, but क्रम now
		 * we give up.
		 */
	पूर्ण

	debug_prपूर्णांक_rmap(rmap, "after copying neighbours");

	मुक्त_cpumask_var(update_mask);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cpu_rmap_update);

/* Glue between IRQ affinity notअगरiers and CPU rmaps */

काष्ठा irq_glue अणु
	काष्ठा irq_affinity_notअगरy notअगरy;
	काष्ठा cpu_rmap *rmap;
	u16 index;
पूर्ण;

/**
 * मुक्त_irq_cpu_rmap - मुक्त a CPU affinity reverse-map used क्रम IRQs
 * @rmap: Reverse-map allocated with alloc_irq_cpu_map(), or %शून्य
 *
 * Must be called in process context, beक्रमe मुक्तing the IRQs.
 */
व्योम मुक्त_irq_cpu_rmap(काष्ठा cpu_rmap *rmap)
अणु
	काष्ठा irq_glue *glue;
	u16 index;

	अगर (!rmap)
		वापस;

	क्रम (index = 0; index < rmap->used; index++) अणु
		glue = rmap->obj[index];
		irq_set_affinity_notअगरier(glue->notअगरy.irq, शून्य);
	पूर्ण

	cpu_rmap_put(rmap);
पूर्ण
EXPORT_SYMBOL(मुक्त_irq_cpu_rmap);

/**
 * irq_cpu_rmap_notअगरy - callback क्रम IRQ subप्रणाली when IRQ affinity updated
 * @notअगरy: काष्ठा irq_affinity_notअगरy passed by irq/manage.c
 * @mask: cpu mask क्रम new SMP affinity
 *
 * This is executed in workqueue context.
 */
अटल व्योम
irq_cpu_rmap_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy, स्थिर cpumask_t *mask)
अणु
	काष्ठा irq_glue *glue =
		container_of(notअगरy, काष्ठा irq_glue, notअगरy);
	पूर्णांक rc;

	rc = cpu_rmap_update(glue->rmap, glue->index, mask);
	अगर (rc)
		pr_warn("irq_cpu_rmap_notify: update failed: %d\n", rc);
पूर्ण

/**
 * irq_cpu_rmap_release - reclaiming callback क्रम IRQ subप्रणाली
 * @ref: kref to काष्ठा irq_affinity_notअगरy passed by irq/manage.c
 */
अटल व्योम irq_cpu_rmap_release(काष्ठा kref *ref)
अणु
	काष्ठा irq_glue *glue =
		container_of(ref, काष्ठा irq_glue, notअगरy.kref);

	cpu_rmap_put(glue->rmap);
	kमुक्त(glue);
पूर्ण

/**
 * irq_cpu_rmap_add - add an IRQ to a CPU affinity reverse-map
 * @rmap: The reverse-map
 * @irq: The IRQ number
 *
 * This adds an IRQ affinity notअगरier that will update the reverse-map
 * स्वतःmatically.
 *
 * Must be called in process context, after the IRQ is allocated but
 * beक्रमe it is bound with request_irq().
 */
पूर्णांक irq_cpu_rmap_add(काष्ठा cpu_rmap *rmap, पूर्णांक irq)
अणु
	काष्ठा irq_glue *glue = kzalloc(माप(*glue), GFP_KERNEL);
	पूर्णांक rc;

	अगर (!glue)
		वापस -ENOMEM;
	glue->notअगरy.notअगरy = irq_cpu_rmap_notअगरy;
	glue->notअगरy.release = irq_cpu_rmap_release;
	glue->rmap = rmap;
	cpu_rmap_get(rmap);
	glue->index = cpu_rmap_add(rmap, glue);
	rc = irq_set_affinity_notअगरier(irq, &glue->notअगरy);
	अगर (rc) अणु
		cpu_rmap_put(glue->rmap);
		kमुक्त(glue);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(irq_cpu_rmap_add);
