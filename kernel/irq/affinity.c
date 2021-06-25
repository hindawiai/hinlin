<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 Thomas Gleixner.
 * Copyright (C) 2016-2017 Christoph Hellwig.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sort.h>

अटल व्योम irq_spपढ़ो_init_one(काष्ठा cpumask *irqmsk, काष्ठा cpumask *nmsk,
				अचिन्हित पूर्णांक cpus_per_vec)
अणु
	स्थिर काष्ठा cpumask *siblmsk;
	पूर्णांक cpu, sibl;

	क्रम ( ; cpus_per_vec > 0; ) अणु
		cpu = cpumask_first(nmsk);

		/* Should not happen, but I'm too lazy to think about it */
		अगर (cpu >= nr_cpu_ids)
			वापस;

		cpumask_clear_cpu(cpu, nmsk);
		cpumask_set_cpu(cpu, irqmsk);
		cpus_per_vec--;

		/* If the cpu has siblings, use them first */
		siblmsk = topology_sibling_cpumask(cpu);
		क्रम (sibl = -1; cpus_per_vec > 0; ) अणु
			sibl = cpumask_next(sibl, siblmsk);
			अगर (sibl >= nr_cpu_ids)
				अवरोध;
			अगर (!cpumask_test_and_clear_cpu(sibl, nmsk))
				जारी;
			cpumask_set_cpu(sibl, irqmsk);
			cpus_per_vec--;
		पूर्ण
	पूर्ण
पूर्ण

अटल cpumask_var_t *alloc_node_to_cpumask(व्योम)
अणु
	cpumask_var_t *masks;
	पूर्णांक node;

	masks = kसुस्मृति(nr_node_ids, माप(cpumask_var_t), GFP_KERNEL);
	अगर (!masks)
		वापस शून्य;

	क्रम (node = 0; node < nr_node_ids; node++) अणु
		अगर (!zalloc_cpumask_var(&masks[node], GFP_KERNEL))
			जाओ out_unwind;
	पूर्ण

	वापस masks;

out_unwind:
	जबतक (--node >= 0)
		मुक्त_cpumask_var(masks[node]);
	kमुक्त(masks);
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_node_to_cpumask(cpumask_var_t *masks)
अणु
	पूर्णांक node;

	क्रम (node = 0; node < nr_node_ids; node++)
		मुक्त_cpumask_var(masks[node]);
	kमुक्त(masks);
पूर्ण

अटल व्योम build_node_to_cpumask(cpumask_var_t *masks)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		cpumask_set_cpu(cpu, masks[cpu_to_node(cpu)]);
पूर्ण

अटल पूर्णांक get_nodes_in_cpumask(cpumask_var_t *node_to_cpumask,
				स्थिर काष्ठा cpumask *mask, nodemask_t *nodemsk)
अणु
	पूर्णांक n, nodes = 0;

	/* Calculate the number of nodes in the supplied affinity mask */
	क्रम_each_node(n) अणु
		अगर (cpumask_पूर्णांकersects(mask, node_to_cpumask[n])) अणु
			node_set(n, *nodemsk);
			nodes++;
		पूर्ण
	पूर्ण
	वापस nodes;
पूर्ण

काष्ठा node_vectors अणु
	अचिन्हित id;

	जोड़ अणु
		अचिन्हित nvectors;
		अचिन्हित ncpus;
	पूर्ण;
पूर्ण;

अटल पूर्णांक ncpus_cmp_func(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	स्थिर काष्ठा node_vectors *ln = l;
	स्थिर काष्ठा node_vectors *rn = r;

	वापस ln->ncpus - rn->ncpus;
पूर्ण

/*
 * Allocate vector number क्रम each node, so that क्रम each node:
 *
 * 1) the allocated number is >= 1
 *
 * 2) the allocated numbver is <= active CPU number of this node
 *
 * The actual allocated total vectors may be less than @numvecs when
 * active total CPU number is less than @numvecs.
 *
 * Active CPUs means the CPUs in '@cpu_mask AND @node_to_cpumask[]'
 * क्रम each node.
 */
अटल व्योम alloc_nodes_vectors(अचिन्हित पूर्णांक numvecs,
				cpumask_var_t *node_to_cpumask,
				स्थिर काष्ठा cpumask *cpu_mask,
				स्थिर nodemask_t nodemsk,
				काष्ठा cpumask *nmsk,
				काष्ठा node_vectors *node_vectors)
अणु
	अचिन्हित n, reमुख्यing_ncpus = 0;

	क्रम (n = 0; n < nr_node_ids; n++) अणु
		node_vectors[n].id = n;
		node_vectors[n].ncpus = अच_पूर्णांक_उच्च;
	पूर्ण

	क्रम_each_node_mask(n, nodemsk) अणु
		अचिन्हित ncpus;

		cpumask_and(nmsk, cpu_mask, node_to_cpumask[n]);
		ncpus = cpumask_weight(nmsk);

		अगर (!ncpus)
			जारी;
		reमुख्यing_ncpus += ncpus;
		node_vectors[n].ncpus = ncpus;
	पूर्ण

	numvecs = min_t(अचिन्हित, reमुख्यing_ncpus, numvecs);

	sort(node_vectors, nr_node_ids, माप(node_vectors[0]),
	     ncpus_cmp_func, शून्य);

	/*
	 * Allocate vectors क्रम each node according to the ratio of this
	 * node's nr_cpus to remaining un-assigned ncpus. 'numvecs' is
	 * bigger than number of active numa nodes. Always start the
	 * allocation from the node with minimized nr_cpus.
	 *
	 * This way guarantees that each active node माला_लो allocated at
	 * least one vector, and the theory is simple: over-allocation
	 * is only करोne when this node is asचिन्हित by one vector, so
	 * other nodes will be allocated >= 1 vector, since 'numvecs' is
	 * bigger than number of numa nodes.
	 *
	 * One perfect invariant is that number of allocated vectors क्रम
	 * each node is <= CPU count of this node:
	 *
	 * 1) suppose there are two nodes: A and B
	 * 	ncpu(X) is CPU count of node X
	 * 	vecs(X) is the vector count allocated to node X via this
	 * 	algorithm
	 *
	 * 	ncpu(A) <= ncpu(B)
	 * 	ncpu(A) + ncpu(B) = N
	 * 	vecs(A) + vecs(B) = V
	 *
	 * 	vecs(A) = max(1, round_करोwn(V * ncpu(A) / N))
	 * 	vecs(B) = V - vecs(A)
	 *
	 * 	both N and V are पूर्णांकeger, and 2 <= V <= N, suppose
	 * 	V = N - delta, and 0 <= delta <= N - 2
	 *
	 * 2) obviously vecs(A) <= ncpu(A) because:
	 *
	 * 	अगर vecs(A) is 1, then vecs(A) <= ncpu(A) given
	 * 	ncpu(A) >= 1
	 *
	 * 	otherwise,
	 * 		vecs(A) <= V * ncpu(A) / N <= ncpu(A), given V <= N
	 *
	 * 3) prove how vecs(B) <= ncpu(B):
	 *
	 * 	अगर round_करोwn(V * ncpu(A) / N) == 0, vecs(B) won't be
	 * 	over-allocated, so vecs(B) <= ncpu(B),
	 *
	 * 	otherwise:
	 *
	 * 	vecs(A) =
	 * 		round_करोwn(V * ncpu(A) / N) =
	 * 		round_करोwn((N - delta) * ncpu(A) / N) =
	 * 		round_करोwn((N * ncpu(A) - delta * ncpu(A)) / N)	 >=
	 * 		round_करोwn((N * ncpu(A) - delta * N) / N)	 =
	 * 		cpu(A) - delta
	 *
	 * 	then:
	 *
	 * 	vecs(A) - V >= ncpu(A) - delta - V
	 * 	=>
	 * 	V - vecs(A) <= V + delta - ncpu(A)
	 * 	=>
	 * 	vecs(B) <= N - ncpu(A)
	 * 	=>
	 * 	vecs(B) <= cpu(B)
	 *
	 * For nodes >= 3, it can be thought as one node and another big
	 * node given that is exactly what this algorithm is implemented,
	 * and we always re-calculate 'remaining_ncpus' & 'numvecs', and
	 * finally क्रम each node X: vecs(X) <= ncpu(X).
	 *
	 */
	क्रम (n = 0; n < nr_node_ids; n++) अणु
		अचिन्हित nvectors, ncpus;

		अगर (node_vectors[n].ncpus == अच_पूर्णांक_उच्च)
			जारी;

		WARN_ON_ONCE(numvecs == 0);

		ncpus = node_vectors[n].ncpus;
		nvectors = max_t(अचिन्हित, 1,
				 numvecs * ncpus / reमुख्यing_ncpus);
		WARN_ON_ONCE(nvectors > ncpus);

		node_vectors[n].nvectors = nvectors;

		reमुख्यing_ncpus -= ncpus;
		numvecs -= nvectors;
	पूर्ण
पूर्ण

अटल पूर्णांक __irq_build_affinity_masks(अचिन्हित पूर्णांक startvec,
				      अचिन्हित पूर्णांक numvecs,
				      अचिन्हित पूर्णांक firstvec,
				      cpumask_var_t *node_to_cpumask,
				      स्थिर काष्ठा cpumask *cpu_mask,
				      काष्ठा cpumask *nmsk,
				      काष्ठा irq_affinity_desc *masks)
अणु
	अचिन्हित पूर्णांक i, n, nodes, cpus_per_vec, extra_vecs, करोne = 0;
	अचिन्हित पूर्णांक last_affv = firstvec + numvecs;
	अचिन्हित पूर्णांक curvec = startvec;
	nodemask_t nodemsk = NODE_MASK_NONE;
	काष्ठा node_vectors *node_vectors;

	अगर (!cpumask_weight(cpu_mask))
		वापस 0;

	nodes = get_nodes_in_cpumask(node_to_cpumask, cpu_mask, &nodemsk);

	/*
	 * If the number of nodes in the mask is greater than or equal the
	 * number of vectors we just spपढ़ो the vectors across the nodes.
	 */
	अगर (numvecs <= nodes) अणु
		क्रम_each_node_mask(n, nodemsk) अणु
			cpumask_or(&masks[curvec].mask, &masks[curvec].mask,
				   node_to_cpumask[n]);
			अगर (++curvec == last_affv)
				curvec = firstvec;
		पूर्ण
		वापस numvecs;
	पूर्ण

	node_vectors = kसुस्मृति(nr_node_ids,
			       माप(काष्ठा node_vectors),
			       GFP_KERNEL);
	अगर (!node_vectors)
		वापस -ENOMEM;

	/* allocate vector number क्रम each node */
	alloc_nodes_vectors(numvecs, node_to_cpumask, cpu_mask,
			    nodemsk, nmsk, node_vectors);

	क्रम (i = 0; i < nr_node_ids; i++) अणु
		अचिन्हित पूर्णांक ncpus, v;
		काष्ठा node_vectors *nv = &node_vectors[i];

		अगर (nv->nvectors == अच_पूर्णांक_उच्च)
			जारी;

		/* Get the cpus on this node which are in the mask */
		cpumask_and(nmsk, cpu_mask, node_to_cpumask[nv->id]);
		ncpus = cpumask_weight(nmsk);
		अगर (!ncpus)
			जारी;

		WARN_ON_ONCE(nv->nvectors > ncpus);

		/* Account क्रम rounding errors */
		extra_vecs = ncpus - nv->nvectors * (ncpus / nv->nvectors);

		/* Spपढ़ो allocated vectors on CPUs of the current node */
		क्रम (v = 0; v < nv->nvectors; v++, curvec++) अणु
			cpus_per_vec = ncpus / nv->nvectors;

			/* Account क्रम extra vectors to compensate rounding errors */
			अगर (extra_vecs) अणु
				cpus_per_vec++;
				--extra_vecs;
			पूर्ण

			/*
			 * wrapping has to be considered given 'startvec'
			 * may start anywhere
			 */
			अगर (curvec >= last_affv)
				curvec = firstvec;
			irq_spपढ़ो_init_one(&masks[curvec].mask, nmsk,
						cpus_per_vec);
		पूर्ण
		करोne += nv->nvectors;
	पूर्ण
	kमुक्त(node_vectors);
	वापस करोne;
पूर्ण

/*
 * build affinity in two stages:
 *	1) spपढ़ो present CPU on these vectors
 *	2) spपढ़ो other possible CPUs on these vectors
 */
अटल पूर्णांक irq_build_affinity_masks(अचिन्हित पूर्णांक startvec, अचिन्हित पूर्णांक numvecs,
				    अचिन्हित पूर्णांक firstvec,
				    काष्ठा irq_affinity_desc *masks)
अणु
	अचिन्हित पूर्णांक curvec = startvec, nr_present = 0, nr_others = 0;
	cpumask_var_t *node_to_cpumask;
	cpumask_var_t nmsk, npresmsk;
	पूर्णांक ret = -ENOMEM;

	अगर (!zalloc_cpumask_var(&nmsk, GFP_KERNEL))
		वापस ret;

	अगर (!zalloc_cpumask_var(&npresmsk, GFP_KERNEL))
		जाओ fail_nmsk;

	node_to_cpumask = alloc_node_to_cpumask();
	अगर (!node_to_cpumask)
		जाओ fail_npresmsk;

	/* Stabilize the cpumasks */
	get_online_cpus();
	build_node_to_cpumask(node_to_cpumask);

	/* Spपढ़ो on present CPUs starting from affd->pre_vectors */
	ret = __irq_build_affinity_masks(curvec, numvecs, firstvec,
					 node_to_cpumask, cpu_present_mask,
					 nmsk, masks);
	अगर (ret < 0)
		जाओ fail_build_affinity;
	nr_present = ret;

	/*
	 * Spपढ़ो on non present CPUs starting from the next vector to be
	 * handled. If the spपढ़ोing of present CPUs alपढ़ोy exhausted the
	 * vector space, assign the non present CPUs to the alपढ़ोy spपढ़ो
	 * out vectors.
	 */
	अगर (nr_present >= numvecs)
		curvec = firstvec;
	अन्यथा
		curvec = firstvec + nr_present;
	cpumask_andnot(npresmsk, cpu_possible_mask, cpu_present_mask);
	ret = __irq_build_affinity_masks(curvec, numvecs, firstvec,
					 node_to_cpumask, npresmsk, nmsk,
					 masks);
	अगर (ret >= 0)
		nr_others = ret;

 fail_build_affinity:
	put_online_cpus();

	अगर (ret >= 0)
		WARN_ON(nr_present + nr_others < numvecs);

	मुक्त_node_to_cpumask(node_to_cpumask);

 fail_npresmsk:
	मुक्त_cpumask_var(npresmsk);

 fail_nmsk:
	मुक्त_cpumask_var(nmsk);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम शेष_calc_sets(काष्ठा irq_affinity *affd, अचिन्हित पूर्णांक affvecs)
अणु
	affd->nr_sets = 1;
	affd->set_size[0] = affvecs;
पूर्ण

/**
 * irq_create_affinity_masks - Create affinity masks क्रम multiqueue spपढ़ोing
 * @nvecs:	The total number of vectors
 * @affd:	Description of the affinity requirements
 *
 * Returns the irq_affinity_desc poपूर्णांकer or शून्य अगर allocation failed.
 */
काष्ठा irq_affinity_desc *
irq_create_affinity_masks(अचिन्हित पूर्णांक nvecs, काष्ठा irq_affinity *affd)
अणु
	अचिन्हित पूर्णांक affvecs, curvec, usedvecs, i;
	काष्ठा irq_affinity_desc *masks = शून्य;

	/*
	 * Determine the number of vectors which need पूर्णांकerrupt affinities
	 * asचिन्हित. If the pre/post request exhausts the available vectors
	 * then nothing to करो here except क्रम invoking the calc_sets()
	 * callback so the device driver can adjust to the situation.
	 */
	अगर (nvecs > affd->pre_vectors + affd->post_vectors)
		affvecs = nvecs - affd->pre_vectors - affd->post_vectors;
	अन्यथा
		affvecs = 0;

	/*
	 * Simple invocations करो not provide a calc_sets() callback. Install
	 * the generic one.
	 */
	अगर (!affd->calc_sets)
		affd->calc_sets = शेष_calc_sets;

	/* Recalculate the sets */
	affd->calc_sets(affd, affvecs);

	अगर (WARN_ON_ONCE(affd->nr_sets > IRQ_AFFINITY_MAX_SETS))
		वापस शून्य;

	/* Nothing to assign? */
	अगर (!affvecs)
		वापस शून्य;

	masks = kसुस्मृति(nvecs, माप(*masks), GFP_KERNEL);
	अगर (!masks)
		वापस शून्य;

	/* Fill out vectors at the beginning that करोn't need affinity */
	क्रम (curvec = 0; curvec < affd->pre_vectors; curvec++)
		cpumask_copy(&masks[curvec].mask, irq_शेष_affinity);

	/*
	 * Spपढ़ो on present CPUs starting from affd->pre_vectors. If we
	 * have multiple sets, build each sets affinity mask separately.
	 */
	क्रम (i = 0, usedvecs = 0; i < affd->nr_sets; i++) अणु
		अचिन्हित पूर्णांक this_vecs = affd->set_size[i];
		पूर्णांक ret;

		ret = irq_build_affinity_masks(curvec, this_vecs,
					       curvec, masks);
		अगर (ret) अणु
			kमुक्त(masks);
			वापस शून्य;
		पूर्ण
		curvec += this_vecs;
		usedvecs += this_vecs;
	पूर्ण

	/* Fill out vectors at the end that करोn't need affinity */
	अगर (usedvecs >= affvecs)
		curvec = affd->pre_vectors + affvecs;
	अन्यथा
		curvec = affd->pre_vectors + usedvecs;
	क्रम (; curvec < nvecs; curvec++)
		cpumask_copy(&masks[curvec].mask, irq_शेष_affinity);

	/* Mark the managed पूर्णांकerrupts */
	क्रम (i = affd->pre_vectors; i < nvecs - affd->post_vectors; i++)
		masks[i].is_managed = 1;

	वापस masks;
पूर्ण

/**
 * irq_calc_affinity_vectors - Calculate the optimal number of vectors
 * @minvec:	The minimum number of vectors available
 * @maxvec:	The maximum number of vectors available
 * @affd:	Description of the affinity requirements
 */
अचिन्हित पूर्णांक irq_calc_affinity_vectors(अचिन्हित पूर्णांक minvec, अचिन्हित पूर्णांक maxvec,
				       स्थिर काष्ठा irq_affinity *affd)
अणु
	अचिन्हित पूर्णांक resv = affd->pre_vectors + affd->post_vectors;
	अचिन्हित पूर्णांक set_vecs;

	अगर (resv > minvec)
		वापस 0;

	अगर (affd->calc_sets) अणु
		set_vecs = maxvec - resv;
	पूर्ण अन्यथा अणु
		get_online_cpus();
		set_vecs = cpumask_weight(cpu_possible_mask);
		put_online_cpus();
	पूर्ण

	वापस resv + min(set_vecs, maxvec - resv);
पूर्ण
