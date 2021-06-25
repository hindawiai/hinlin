<शैली गुरु>
/*
 * Copyright(c) 2015 - 2020 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/topology.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/numa.h>

#समावेश "hfi.h"
#समावेश "affinity.h"
#समावेश "sdma.h"
#समावेश "trace.h"

काष्ठा hfi1_affinity_node_list node_affinity = अणु
	.list = LIST_HEAD_INIT(node_affinity.list),
	.lock = __MUTEX_INITIALIZER(node_affinity.lock)
पूर्ण;

/* Name of IRQ types, indexed by क्रमागत irq_type */
अटल स्थिर अक्षर * स्थिर irq_type_names[] = अणु
	"SDMA",
	"RCVCTXT",
	"NETDEVCTXT",
	"GENERAL",
	"OTHER",
पूर्ण;

/* Per NUMA node count of HFI devices */
अटल अचिन्हित पूर्णांक *hfi1_per_node_cntr;

अटल अंतरभूत व्योम init_cpu_mask_set(काष्ठा cpu_mask_set *set)
अणु
	cpumask_clear(&set->mask);
	cpumask_clear(&set->used);
	set->gen = 0;
पूर्ण

/* Increment generation of CPU set अगर needed */
अटल व्योम _cpu_mask_set_gen_inc(काष्ठा cpu_mask_set *set)
अणु
	अगर (cpumask_equal(&set->mask, &set->used)) अणु
		/*
		 * We've used up all the CPUs, bump up the generation
		 * and reset the 'used' map
		 */
		set->gen++;
		cpumask_clear(&set->used);
	पूर्ण
पूर्ण

अटल व्योम _cpu_mask_set_gen_dec(काष्ठा cpu_mask_set *set)
अणु
	अगर (cpumask_empty(&set->used) && set->gen) अणु
		set->gen--;
		cpumask_copy(&set->used, &set->mask);
	पूर्ण
पूर्ण

/* Get the first CPU from the list of unused CPUs in a CPU set data काष्ठाure */
अटल पूर्णांक cpu_mask_set_get_first(काष्ठा cpu_mask_set *set, cpumask_var_t dअगरf)
अणु
	पूर्णांक cpu;

	अगर (!dअगरf || !set)
		वापस -EINVAL;

	_cpu_mask_set_gen_inc(set);

	/* Find out CPUs left in CPU mask */
	cpumask_andnot(dअगरf, &set->mask, &set->used);

	cpu = cpumask_first(dअगरf);
	अगर (cpu >= nr_cpu_ids) /* empty */
		cpu = -EINVAL;
	अन्यथा
		cpumask_set_cpu(cpu, &set->used);

	वापस cpu;
पूर्ण

अटल व्योम cpu_mask_set_put(काष्ठा cpu_mask_set *set, पूर्णांक cpu)
अणु
	अगर (!set)
		वापस;

	cpumask_clear_cpu(cpu, &set->used);
	_cpu_mask_set_gen_dec(set);
पूर्ण

/* Initialize non-HT cpu cores mask */
व्योम init_real_cpu_mask(व्योम)
अणु
	पूर्णांक possible, curr_cpu, i, ht;

	cpumask_clear(&node_affinity.real_cpu_mask);

	/* Start with cpu online mask as the real cpu mask */
	cpumask_copy(&node_affinity.real_cpu_mask, cpu_online_mask);

	/*
	 * Remove HT cores from the real cpu mask.  Do this in two steps below.
	 */
	possible = cpumask_weight(&node_affinity.real_cpu_mask);
	ht = cpumask_weight(topology_sibling_cpumask(
				cpumask_first(&node_affinity.real_cpu_mask)));
	/*
	 * Step 1.  Skip over the first N HT siblings and use them as the
	 * "real" cores.  Assumes that HT cores are not क्रमागतerated in
	 * succession (except in the single core हाल).
	 */
	curr_cpu = cpumask_first(&node_affinity.real_cpu_mask);
	क्रम (i = 0; i < possible / ht; i++)
		curr_cpu = cpumask_next(curr_cpu, &node_affinity.real_cpu_mask);
	/*
	 * Step 2.  Remove the reमुख्यing HT siblings.  Use cpumask_next() to
	 * skip any gaps.
	 */
	क्रम (; i < possible; i++) अणु
		cpumask_clear_cpu(curr_cpu, &node_affinity.real_cpu_mask);
		curr_cpu = cpumask_next(curr_cpu, &node_affinity.real_cpu_mask);
	पूर्ण
पूर्ण

पूर्णांक node_affinity_init(व्योम)
अणु
	पूर्णांक node;
	काष्ठा pci_dev *dev = शून्य;
	स्थिर काष्ठा pci_device_id *ids = hfi1_pci_tbl;

	cpumask_clear(&node_affinity.proc.used);
	cpumask_copy(&node_affinity.proc.mask, cpu_online_mask);

	node_affinity.proc.gen = 0;
	node_affinity.num_core_siblings =
				cpumask_weight(topology_sibling_cpumask(
					cpumask_first(&node_affinity.proc.mask)
					));
	node_affinity.num_possible_nodes = num_possible_nodes();
	node_affinity.num_online_nodes = num_online_nodes();
	node_affinity.num_online_cpus = num_online_cpus();

	/*
	 * The real cpu mask is part of the affinity काष्ठा but it has to be
	 * initialized early. It is needed to calculate the number of user
	 * contexts in set_up_context_variables().
	 */
	init_real_cpu_mask();

	hfi1_per_node_cntr = kसुस्मृति(node_affinity.num_possible_nodes,
				     माप(*hfi1_per_node_cntr), GFP_KERNEL);
	अगर (!hfi1_per_node_cntr)
		वापस -ENOMEM;

	जबतक (ids->venकरोr) अणु
		dev = शून्य;
		जबतक ((dev = pci_get_device(ids->venकरोr, ids->device, dev))) अणु
			node = pcibus_to_node(dev->bus);
			अगर (node < 0)
				जाओ out;

			hfi1_per_node_cntr[node]++;
		पूर्ण
		ids++;
	पूर्ण

	वापस 0;

out:
	/*
	 * Invalid PCI NUMA node inक्रमmation found, note it, and populate
	 * our database 1:1.
	 */
	pr_err("HFI: Invalid PCI NUMA node. Performance may be affected\n");
	pr_err("HFI: System BIOS may need to be upgraded\n");
	क्रम (node = 0; node < node_affinity.num_possible_nodes; node++)
		hfi1_per_node_cntr[node] = 1;

	वापस 0;
पूर्ण

अटल व्योम node_affinity_destroy(काष्ठा hfi1_affinity_node *entry)
अणु
	मुक्त_percpu(entry->comp_vect_affinity);
	kमुक्त(entry);
पूर्ण

व्योम node_affinity_destroy_all(व्योम)
अणु
	काष्ठा list_head *pos, *q;
	काष्ठा hfi1_affinity_node *entry;

	mutex_lock(&node_affinity.lock);
	list_क्रम_each_safe(pos, q, &node_affinity.list) अणु
		entry = list_entry(pos, काष्ठा hfi1_affinity_node,
				   list);
		list_del(pos);
		node_affinity_destroy(entry);
	पूर्ण
	mutex_unlock(&node_affinity.lock);
	kमुक्त(hfi1_per_node_cntr);
पूर्ण

अटल काष्ठा hfi1_affinity_node *node_affinity_allocate(पूर्णांक node)
अणु
	काष्ठा hfi1_affinity_node *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस शून्य;
	entry->node = node;
	entry->comp_vect_affinity = alloc_percpu(u16);
	INIT_LIST_HEAD(&entry->list);

	वापस entry;
पूर्ण

/*
 * It appends an entry to the list.
 * It *must* be called with node_affinity.lock held.
 */
अटल व्योम node_affinity_add_tail(काष्ठा hfi1_affinity_node *entry)
अणु
	list_add_tail(&entry->list, &node_affinity.list);
पूर्ण

/* It must be called with node_affinity.lock held */
अटल काष्ठा hfi1_affinity_node *node_affinity_lookup(पूर्णांक node)
अणु
	काष्ठा list_head *pos;
	काष्ठा hfi1_affinity_node *entry;

	list_क्रम_each(pos, &node_affinity.list) अणु
		entry = list_entry(pos, काष्ठा hfi1_affinity_node, list);
		अगर (entry->node == node)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक per_cpu_affinity_get(cpumask_var_t possible_cpumask,
				u16 __percpu *comp_vect_affinity)
अणु
	पूर्णांक curr_cpu;
	u16 cntr;
	u16 prev_cntr;
	पूर्णांक ret_cpu;

	अगर (!possible_cpumask) अणु
		ret_cpu = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (!comp_vect_affinity) अणु
		ret_cpu = -EINVAL;
		जाओ fail;
	पूर्ण

	ret_cpu = cpumask_first(possible_cpumask);
	अगर (ret_cpu >= nr_cpu_ids) अणु
		ret_cpu = -EINVAL;
		जाओ fail;
	पूर्ण

	prev_cntr = *per_cpu_ptr(comp_vect_affinity, ret_cpu);
	क्रम_each_cpu(curr_cpu, possible_cpumask) अणु
		cntr = *per_cpu_ptr(comp_vect_affinity, curr_cpu);

		अगर (cntr < prev_cntr) अणु
			ret_cpu = curr_cpu;
			prev_cntr = cntr;
		पूर्ण
	पूर्ण

	*per_cpu_ptr(comp_vect_affinity, ret_cpu) += 1;

fail:
	वापस ret_cpu;
पूर्ण

अटल पूर्णांक per_cpu_affinity_put_max(cpumask_var_t possible_cpumask,
				    u16 __percpu *comp_vect_affinity)
अणु
	पूर्णांक curr_cpu;
	पूर्णांक max_cpu;
	u16 cntr;
	u16 prev_cntr;

	अगर (!possible_cpumask)
		वापस -EINVAL;

	अगर (!comp_vect_affinity)
		वापस -EINVAL;

	max_cpu = cpumask_first(possible_cpumask);
	अगर (max_cpu >= nr_cpu_ids)
		वापस -EINVAL;

	prev_cntr = *per_cpu_ptr(comp_vect_affinity, max_cpu);
	क्रम_each_cpu(curr_cpu, possible_cpumask) अणु
		cntr = *per_cpu_ptr(comp_vect_affinity, curr_cpu);

		अगर (cntr > prev_cntr) अणु
			max_cpu = curr_cpu;
			prev_cntr = cntr;
		पूर्ण
	पूर्ण

	*per_cpu_ptr(comp_vect_affinity, max_cpu) -= 1;

	वापस max_cpu;
पूर्ण

/*
 * Non-पूर्णांकerrupt CPUs are used first, then पूर्णांकerrupt CPUs.
 * Two alपढ़ोy allocated cpu masks must be passed.
 */
अटल पूर्णांक _dev_comp_vect_cpu_get(काष्ठा hfi1_devdata *dd,
				  काष्ठा hfi1_affinity_node *entry,
				  cpumask_var_t non_पूर्णांकr_cpus,
				  cpumask_var_t available_cpus)
	__must_hold(&node_affinity.lock)
अणु
	पूर्णांक cpu;
	काष्ठा cpu_mask_set *set = dd->comp_vect;

	lockdep_निश्चित_held(&node_affinity.lock);
	अगर (!non_पूर्णांकr_cpus) अणु
		cpu = -1;
		जाओ fail;
	पूर्ण

	अगर (!available_cpus) अणु
		cpu = -1;
		जाओ fail;
	पूर्ण

	/* Available CPUs क्रम pinning completion vectors */
	_cpu_mask_set_gen_inc(set);
	cpumask_andnot(available_cpus, &set->mask, &set->used);

	/* Available CPUs without SDMA engine पूर्णांकerrupts */
	cpumask_andnot(non_पूर्णांकr_cpus, available_cpus,
		       &entry->def_पूर्णांकr.used);

	/* If there are non-पूर्णांकerrupt CPUs available, use them first */
	अगर (!cpumask_empty(non_पूर्णांकr_cpus))
		cpu = cpumask_first(non_पूर्णांकr_cpus);
	अन्यथा /* Otherwise, use पूर्णांकerrupt CPUs */
		cpu = cpumask_first(available_cpus);

	अगर (cpu >= nr_cpu_ids) अणु /* empty */
		cpu = -1;
		जाओ fail;
	पूर्ण
	cpumask_set_cpu(cpu, &set->used);

fail:
	वापस cpu;
पूर्ण

अटल व्योम _dev_comp_vect_cpu_put(काष्ठा hfi1_devdata *dd, पूर्णांक cpu)
अणु
	काष्ठा cpu_mask_set *set = dd->comp_vect;

	अगर (cpu < 0)
		वापस;

	cpu_mask_set_put(set, cpu);
पूर्ण

/* _dev_comp_vect_mappings_destroy() is reentrant */
अटल व्योम _dev_comp_vect_mappings_destroy(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i, cpu;

	अगर (!dd->comp_vect_mappings)
		वापस;

	क्रम (i = 0; i < dd->comp_vect_possible_cpus; i++) अणु
		cpu = dd->comp_vect_mappings[i];
		_dev_comp_vect_cpu_put(dd, cpu);
		dd->comp_vect_mappings[i] = -1;
		hfi1_cdbg(AFFINITY,
			  "[%s] Release CPU %d from completion vector %d",
			  rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), cpu, i);
	पूर्ण

	kमुक्त(dd->comp_vect_mappings);
	dd->comp_vect_mappings = शून्य;
पूर्ण

/*
 * This function creates the table क्रम looking up CPUs क्रम completion vectors.
 * num_comp_vectors needs to have been initilized beक्रमe calling this function.
 */
अटल पूर्णांक _dev_comp_vect_mappings_create(काष्ठा hfi1_devdata *dd,
					  काष्ठा hfi1_affinity_node *entry)
	__must_hold(&node_affinity.lock)
अणु
	पूर्णांक i, cpu, ret;
	cpumask_var_t non_पूर्णांकr_cpus;
	cpumask_var_t available_cpus;

	lockdep_निश्चित_held(&node_affinity.lock);

	अगर (!zalloc_cpumask_var(&non_पूर्णांकr_cpus, GFP_KERNEL))
		वापस -ENOMEM;

	अगर (!zalloc_cpumask_var(&available_cpus, GFP_KERNEL)) अणु
		मुक्त_cpumask_var(non_पूर्णांकr_cpus);
		वापस -ENOMEM;
	पूर्ण

	dd->comp_vect_mappings = kसुस्मृति(dd->comp_vect_possible_cpus,
					 माप(*dd->comp_vect_mappings),
					 GFP_KERNEL);
	अगर (!dd->comp_vect_mappings) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	क्रम (i = 0; i < dd->comp_vect_possible_cpus; i++)
		dd->comp_vect_mappings[i] = -1;

	क्रम (i = 0; i < dd->comp_vect_possible_cpus; i++) अणु
		cpu = _dev_comp_vect_cpu_get(dd, entry, non_पूर्णांकr_cpus,
					     available_cpus);
		अगर (cpu < 0) अणु
			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		dd->comp_vect_mappings[i] = cpu;
		hfi1_cdbg(AFFINITY,
			  "[%s] Completion Vector %d -> CPU %d",
			  rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), i, cpu);
	पूर्ण

	मुक्त_cpumask_var(available_cpus);
	मुक्त_cpumask_var(non_पूर्णांकr_cpus);
	वापस 0;

fail:
	मुक्त_cpumask_var(available_cpus);
	मुक्त_cpumask_var(non_पूर्णांकr_cpus);
	_dev_comp_vect_mappings_destroy(dd);

	वापस ret;
पूर्ण

पूर्णांक hfi1_comp_vectors_set_up(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_affinity_node *entry;

	mutex_lock(&node_affinity.lock);
	entry = node_affinity_lookup(dd->node);
	अगर (!entry) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण
	ret = _dev_comp_vect_mappings_create(dd, entry);
unlock:
	mutex_unlock(&node_affinity.lock);

	वापस ret;
पूर्ण

व्योम hfi1_comp_vectors_clean_up(काष्ठा hfi1_devdata *dd)
अणु
	_dev_comp_vect_mappings_destroy(dd);
पूर्ण

पूर्णांक hfi1_comp_vect_mappings_lookup(काष्ठा rvt_dev_info *rdi, पूर्णांक comp_vect)
अणु
	काष्ठा hfi1_ibdev *verbs_dev = dev_from_rdi(rdi);
	काष्ठा hfi1_devdata *dd = dd_from_dev(verbs_dev);

	अगर (!dd->comp_vect_mappings)
		वापस -EINVAL;
	अगर (comp_vect >= dd->comp_vect_possible_cpus)
		वापस -EINVAL;

	वापस dd->comp_vect_mappings[comp_vect];
पूर्ण

/*
 * It assumes dd->comp_vect_possible_cpus is available.
 */
अटल पूर्णांक _dev_comp_vect_cpu_mask_init(काष्ठा hfi1_devdata *dd,
					काष्ठा hfi1_affinity_node *entry,
					bool first_dev_init)
	__must_hold(&node_affinity.lock)
अणु
	पूर्णांक i, j, curr_cpu;
	पूर्णांक possible_cpus_comp_vect = 0;
	काष्ठा cpumask *dev_comp_vect_mask = &dd->comp_vect->mask;

	lockdep_निश्चित_held(&node_affinity.lock);
	/*
	 * If there's only one CPU available क्रम completion vectors, then
	 * there will only be one completion vector available. Othewise,
	 * the number of completion vector available will be the number of
	 * available CPUs भागide it by the number of devices in the
	 * local NUMA node.
	 */
	अगर (cpumask_weight(&entry->comp_vect_mask) == 1) अणु
		possible_cpus_comp_vect = 1;
		dd_dev_warn(dd,
			    "Number of kernel receive queues is too large for completion vector affinity to be effective\n");
	पूर्ण अन्यथा अणु
		possible_cpus_comp_vect +=
			cpumask_weight(&entry->comp_vect_mask) /
				       hfi1_per_node_cntr[dd->node];

		/*
		 * If the completion vector CPUs available करोesn't भागide
		 * evenly among devices, then the first device device to be
		 * initialized माला_लो an extra CPU.
		 */
		अगर (first_dev_init &&
		    cpumask_weight(&entry->comp_vect_mask) %
		    hfi1_per_node_cntr[dd->node] != 0)
			possible_cpus_comp_vect++;
	पूर्ण

	dd->comp_vect_possible_cpus = possible_cpus_comp_vect;

	/* Reserving CPUs क्रम device completion vector */
	क्रम (i = 0; i < dd->comp_vect_possible_cpus; i++) अणु
		curr_cpu = per_cpu_affinity_get(&entry->comp_vect_mask,
						entry->comp_vect_affinity);
		अगर (curr_cpu < 0)
			जाओ fail;

		cpumask_set_cpu(curr_cpu, dev_comp_vect_mask);
	पूर्ण

	hfi1_cdbg(AFFINITY,
		  "[%s] Completion vector affinity CPU set(s) %*pbl",
		  rvt_get_ibdev_name(&(dd)->verbs_dev.rdi),
		  cpumask_pr_args(dev_comp_vect_mask));

	वापस 0;

fail:
	क्रम (j = 0; j < i; j++)
		per_cpu_affinity_put_max(&entry->comp_vect_mask,
					 entry->comp_vect_affinity);

	वापस curr_cpu;
पूर्ण

/*
 * It assumes dd->comp_vect_possible_cpus is available.
 */
अटल व्योम _dev_comp_vect_cpu_mask_clean_up(काष्ठा hfi1_devdata *dd,
					     काष्ठा hfi1_affinity_node *entry)
	__must_hold(&node_affinity.lock)
अणु
	पूर्णांक i, cpu;

	lockdep_निश्चित_held(&node_affinity.lock);
	अगर (!dd->comp_vect_possible_cpus)
		वापस;

	क्रम (i = 0; i < dd->comp_vect_possible_cpus; i++) अणु
		cpu = per_cpu_affinity_put_max(&dd->comp_vect->mask,
					       entry->comp_vect_affinity);
		/* Clearing CPU in device completion vector cpu mask */
		अगर (cpu >= 0)
			cpumask_clear_cpu(cpu, &dd->comp_vect->mask);
	पूर्ण

	dd->comp_vect_possible_cpus = 0;
पूर्ण

/*
 * Interrupt affinity.
 *
 * non-rcv avail माला_लो a शेष mask that
 * starts as possible cpus with thपढ़ोs reset
 * and each rcv avail reset.
 *
 * rcv avail माला_लो node relative 1 wrapping back
 * to the node relative 1 as necessary.
 *
 */
पूर्णांक hfi1_dev_affinity_init(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_affinity_node *entry;
	स्थिर काष्ठा cpumask *local_mask;
	पूर्णांक curr_cpu, possible, i, ret;
	bool new_entry = false;

	local_mask = cpumask_of_node(dd->node);
	अगर (cpumask_first(local_mask) >= nr_cpu_ids)
		local_mask = topology_core_cpumask(0);

	mutex_lock(&node_affinity.lock);
	entry = node_affinity_lookup(dd->node);

	/*
	 * If this is the first समय this NUMA node's affinity is used,
	 * create an entry in the global affinity काष्ठाure and initialize it.
	 */
	अगर (!entry) अणु
		entry = node_affinity_allocate(dd->node);
		अगर (!entry) अणु
			dd_dev_err(dd,
				   "Unable to allocate global affinity node\n");
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
		new_entry = true;

		init_cpu_mask_set(&entry->def_पूर्णांकr);
		init_cpu_mask_set(&entry->rcv_पूर्णांकr);
		cpumask_clear(&entry->comp_vect_mask);
		cpumask_clear(&entry->general_पूर्णांकr_mask);
		/* Use the "real" cpu mask of this node as the शेष */
		cpumask_and(&entry->def_पूर्णांकr.mask, &node_affinity.real_cpu_mask,
			    local_mask);

		/* fill in the receive list */
		possible = cpumask_weight(&entry->def_पूर्णांकr.mask);
		curr_cpu = cpumask_first(&entry->def_पूर्णांकr.mask);

		अगर (possible == 1) अणु
			/* only one CPU, everyone will use it */
			cpumask_set_cpu(curr_cpu, &entry->rcv_पूर्णांकr.mask);
			cpumask_set_cpu(curr_cpu, &entry->general_पूर्णांकr_mask);
		पूर्ण अन्यथा अणु
			/*
			 * The general/control context will be the first CPU in
			 * the शेष list, so it is हटाओd from the शेष
			 * list and added to the general पूर्णांकerrupt list.
			 */
			cpumask_clear_cpu(curr_cpu, &entry->def_पूर्णांकr.mask);
			cpumask_set_cpu(curr_cpu, &entry->general_पूर्णांकr_mask);
			curr_cpu = cpumask_next(curr_cpu,
						&entry->def_पूर्णांकr.mask);

			/*
			 * Remove the reमुख्यing kernel receive queues from
			 * the शेष list and add them to the receive list.
			 */
			क्रम (i = 0;
			     i < (dd->n_krcv_queues - 1) *
				  hfi1_per_node_cntr[dd->node];
			     i++) अणु
				cpumask_clear_cpu(curr_cpu,
						  &entry->def_पूर्णांकr.mask);
				cpumask_set_cpu(curr_cpu,
						&entry->rcv_पूर्णांकr.mask);
				curr_cpu = cpumask_next(curr_cpu,
							&entry->def_पूर्णांकr.mask);
				अगर (curr_cpu >= nr_cpu_ids)
					अवरोध;
			पूर्ण

			/*
			 * If there ends up being 0 CPU cores leftover क्रम SDMA
			 * engines, use the same CPU cores as general/control
			 * context.
			 */
			अगर (cpumask_weight(&entry->def_पूर्णांकr.mask) == 0)
				cpumask_copy(&entry->def_पूर्णांकr.mask,
					     &entry->general_पूर्णांकr_mask);
		पूर्ण

		/* Determine completion vector CPUs क्रम the entire node */
		cpumask_and(&entry->comp_vect_mask,
			    &node_affinity.real_cpu_mask, local_mask);
		cpumask_andnot(&entry->comp_vect_mask,
			       &entry->comp_vect_mask,
			       &entry->rcv_पूर्णांकr.mask);
		cpumask_andnot(&entry->comp_vect_mask,
			       &entry->comp_vect_mask,
			       &entry->general_पूर्णांकr_mask);

		/*
		 * If there ends up being 0 CPU cores leftover क्रम completion
		 * vectors, use the same CPU core as the general/control
		 * context.
		 */
		अगर (cpumask_weight(&entry->comp_vect_mask) == 0)
			cpumask_copy(&entry->comp_vect_mask,
				     &entry->general_पूर्णांकr_mask);
	पूर्ण

	ret = _dev_comp_vect_cpu_mask_init(dd, entry, new_entry);
	अगर (ret < 0)
		जाओ fail;

	अगर (new_entry)
		node_affinity_add_tail(entry);

	dd->affinity_entry = entry;
	mutex_unlock(&node_affinity.lock);

	वापस 0;

fail:
	अगर (new_entry)
		node_affinity_destroy(entry);
	mutex_unlock(&node_affinity.lock);
	वापस ret;
पूर्ण

व्योम hfi1_dev_affinity_clean_up(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_affinity_node *entry;

	mutex_lock(&node_affinity.lock);
	अगर (!dd->affinity_entry)
		जाओ unlock;
	entry = node_affinity_lookup(dd->node);
	अगर (!entry)
		जाओ unlock;

	/*
	 * Free device completion vector CPUs to be used by future
	 * completion vectors
	 */
	_dev_comp_vect_cpu_mask_clean_up(dd, entry);
unlock:
	dd->affinity_entry = शून्य;
	mutex_unlock(&node_affinity.lock);
पूर्ण

/*
 * Function updates the irq affinity hपूर्णांक क्रम msix after it has been changed
 * by the user using the /proc/irq पूर्णांकerface. This function only accepts
 * one cpu in the mask.
 */
अटल व्योम hfi1_update_sdma_affinity(काष्ठा hfi1_msix_entry *msix, पूर्णांक cpu)
अणु
	काष्ठा sdma_engine *sde = msix->arg;
	काष्ठा hfi1_devdata *dd = sde->dd;
	काष्ठा hfi1_affinity_node *entry;
	काष्ठा cpu_mask_set *set;
	पूर्णांक i, old_cpu;

	अगर (cpu > num_online_cpus() || cpu == sde->cpu)
		वापस;

	mutex_lock(&node_affinity.lock);
	entry = node_affinity_lookup(dd->node);
	अगर (!entry)
		जाओ unlock;

	old_cpu = sde->cpu;
	sde->cpu = cpu;
	cpumask_clear(&msix->mask);
	cpumask_set_cpu(cpu, &msix->mask);
	dd_dev_dbg(dd, "IRQ: %u, type %s engine %u -> cpu: %d\n",
		   msix->irq, irq_type_names[msix->type],
		   sde->this_idx, cpu);
	irq_set_affinity_hपूर्णांक(msix->irq, &msix->mask);

	/*
	 * Set the new cpu in the hfi1_affinity_node and clean
	 * the old cpu अगर it is not used by any other IRQ
	 */
	set = &entry->def_पूर्णांकr;
	cpumask_set_cpu(cpu, &set->mask);
	cpumask_set_cpu(cpu, &set->used);
	क्रम (i = 0; i < dd->msix_info.max_requested; i++) अणु
		काष्ठा hfi1_msix_entry *other_msix;

		other_msix = &dd->msix_info.msix_entries[i];
		अगर (other_msix->type != IRQ_SDMA || other_msix == msix)
			जारी;

		अगर (cpumask_test_cpu(old_cpu, &other_msix->mask))
			जाओ unlock;
	पूर्ण
	cpumask_clear_cpu(old_cpu, &set->mask);
	cpumask_clear_cpu(old_cpu, &set->used);
unlock:
	mutex_unlock(&node_affinity.lock);
पूर्ण

अटल व्योम hfi1_irq_notअगरier_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy,
				     स्थिर cpumask_t *mask)
अणु
	पूर्णांक cpu = cpumask_first(mask);
	काष्ठा hfi1_msix_entry *msix = container_of(notअगरy,
						    काष्ठा hfi1_msix_entry,
						    notअगरy);

	/* Only one CPU configuration supported currently */
	hfi1_update_sdma_affinity(msix, cpu);
पूर्ण

अटल व्योम hfi1_irq_notअगरier_release(काष्ठा kref *ref)
अणु
	/*
	 * This is required by affinity notअगरier. We करोn't have anything to
	 * मुक्त here.
	 */
पूर्ण

अटल व्योम hfi1_setup_sdma_notअगरier(काष्ठा hfi1_msix_entry *msix)
अणु
	काष्ठा irq_affinity_notअगरy *notअगरy = &msix->notअगरy;

	notअगरy->irq = msix->irq;
	notअगरy->notअगरy = hfi1_irq_notअगरier_notअगरy;
	notअगरy->release = hfi1_irq_notअगरier_release;

	अगर (irq_set_affinity_notअगरier(notअगरy->irq, notअगरy))
		pr_err("Failed to register sdma irq affinity notifier for irq %d\n",
		       notअगरy->irq);
पूर्ण

अटल व्योम hfi1_cleanup_sdma_notअगरier(काष्ठा hfi1_msix_entry *msix)
अणु
	काष्ठा irq_affinity_notअगरy *notअगरy = &msix->notअगरy;

	अगर (irq_set_affinity_notअगरier(notअगरy->irq, शून्य))
		pr_err("Failed to cleanup sdma irq affinity notifier for irq %d\n",
		       notअगरy->irq);
पूर्ण

/*
 * Function sets the irq affinity क्रम msix.
 * It *must* be called with node_affinity.lock held.
 */
अटल पूर्णांक get_irq_affinity(काष्ठा hfi1_devdata *dd,
			    काष्ठा hfi1_msix_entry *msix)
अणु
	cpumask_var_t dअगरf;
	काष्ठा hfi1_affinity_node *entry;
	काष्ठा cpu_mask_set *set = शून्य;
	काष्ठा sdma_engine *sde = शून्य;
	काष्ठा hfi1_ctxtdata *rcd = शून्य;
	अक्षर extra[64];
	पूर्णांक cpu = -1;

	extra[0] = '\0';
	cpumask_clear(&msix->mask);

	entry = node_affinity_lookup(dd->node);

	चयन (msix->type) अणु
	हाल IRQ_SDMA:
		sde = (काष्ठा sdma_engine *)msix->arg;
		scnम_लिखो(extra, 64, "engine %u", sde->this_idx);
		set = &entry->def_पूर्णांकr;
		अवरोध;
	हाल IRQ_GENERAL:
		cpu = cpumask_first(&entry->general_पूर्णांकr_mask);
		अवरोध;
	हाल IRQ_RCVCTXT:
		rcd = (काष्ठा hfi1_ctxtdata *)msix->arg;
		अगर (rcd->ctxt == HFI1_CTRL_CTXT)
			cpu = cpumask_first(&entry->general_पूर्णांकr_mask);
		अन्यथा
			set = &entry->rcv_पूर्णांकr;
		scnम_लिखो(extra, 64, "ctxt %u", rcd->ctxt);
		अवरोध;
	हाल IRQ_NETDEVCTXT:
		rcd = (काष्ठा hfi1_ctxtdata *)msix->arg;
		set = &entry->def_पूर्णांकr;
		scnम_लिखो(extra, 64, "ctxt %u", rcd->ctxt);
		अवरोध;
	शेष:
		dd_dev_err(dd, "Invalid IRQ type %d\n", msix->type);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The general and control contexts are placed on a particular
	 * CPU, which is set above. Skip accounting क्रम it. Everything अन्यथा
	 * finds its CPU here.
	 */
	अगर (cpu == -1 && set) अणु
		अगर (!zalloc_cpumask_var(&dअगरf, GFP_KERNEL))
			वापस -ENOMEM;

		cpu = cpu_mask_set_get_first(set, dअगरf);
		अगर (cpu < 0) अणु
			मुक्त_cpumask_var(dअगरf);
			dd_dev_err(dd, "Failure to obtain CPU for IRQ\n");
			वापस cpu;
		पूर्ण

		मुक्त_cpumask_var(dअगरf);
	पूर्ण

	cpumask_set_cpu(cpu, &msix->mask);
	dd_dev_info(dd, "IRQ: %u, type %s %s -> cpu: %d\n",
		    msix->irq, irq_type_names[msix->type],
		    extra, cpu);
	irq_set_affinity_hपूर्णांक(msix->irq, &msix->mask);

	अगर (msix->type == IRQ_SDMA) अणु
		sde->cpu = cpu;
		hfi1_setup_sdma_notअगरier(msix);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hfi1_get_irq_affinity(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_msix_entry *msix)
अणु
	पूर्णांक ret;

	mutex_lock(&node_affinity.lock);
	ret = get_irq_affinity(dd, msix);
	mutex_unlock(&node_affinity.lock);
	वापस ret;
पूर्ण

व्योम hfi1_put_irq_affinity(काष्ठा hfi1_devdata *dd,
			   काष्ठा hfi1_msix_entry *msix)
अणु
	काष्ठा cpu_mask_set *set = शून्य;
	काष्ठा hfi1_affinity_node *entry;

	mutex_lock(&node_affinity.lock);
	entry = node_affinity_lookup(dd->node);

	चयन (msix->type) अणु
	हाल IRQ_SDMA:
		set = &entry->def_पूर्णांकr;
		hfi1_cleanup_sdma_notअगरier(msix);
		अवरोध;
	हाल IRQ_GENERAL:
		/* Don't करो accounting क्रम general contexts */
		अवरोध;
	हाल IRQ_RCVCTXT: अणु
		काष्ठा hfi1_ctxtdata *rcd = msix->arg;

		/* Don't करो accounting क्रम control contexts */
		अगर (rcd->ctxt != HFI1_CTRL_CTXT)
			set = &entry->rcv_पूर्णांकr;
		अवरोध;
	पूर्ण
	हाल IRQ_NETDEVCTXT:
		set = &entry->def_पूर्णांकr;
		अवरोध;
	शेष:
		mutex_unlock(&node_affinity.lock);
		वापस;
	पूर्ण

	अगर (set) अणु
		cpumask_andnot(&set->used, &set->used, &msix->mask);
		_cpu_mask_set_gen_dec(set);
	पूर्ण

	irq_set_affinity_hपूर्णांक(msix->irq, शून्य);
	cpumask_clear(&msix->mask);
	mutex_unlock(&node_affinity.lock);
पूर्ण

/* This should be called with node_affinity.lock held */
अटल व्योम find_hw_thपढ़ो_mask(uपूर्णांक hw_thपढ़ो_no, cpumask_var_t hw_thपढ़ो_mask,
				काष्ठा hfi1_affinity_node_list *affinity)
अणु
	पूर्णांक possible, curr_cpu, i;
	uपूर्णांक num_cores_per_socket = node_affinity.num_online_cpus /
					affinity->num_core_siblings /
						node_affinity.num_online_nodes;

	cpumask_copy(hw_thपढ़ो_mask, &affinity->proc.mask);
	अगर (affinity->num_core_siblings > 0) अणु
		/* Removing other siblings not needed क्रम now */
		possible = cpumask_weight(hw_thपढ़ो_mask);
		curr_cpu = cpumask_first(hw_thपढ़ो_mask);
		क्रम (i = 0;
		     i < num_cores_per_socket * node_affinity.num_online_nodes;
		     i++)
			curr_cpu = cpumask_next(curr_cpu, hw_thपढ़ो_mask);

		क्रम (; i < possible; i++) अणु
			cpumask_clear_cpu(curr_cpu, hw_thपढ़ो_mask);
			curr_cpu = cpumask_next(curr_cpu, hw_thपढ़ो_mask);
		पूर्ण

		/* Identअगरying correct HW thपढ़ोs within physical cores */
		cpumask_shअगरt_left(hw_thपढ़ो_mask, hw_thपढ़ो_mask,
				   num_cores_per_socket *
				   node_affinity.num_online_nodes *
				   hw_thपढ़ो_no);
	पूर्ण
पूर्ण

पूर्णांक hfi1_get_proc_affinity(पूर्णांक node)
अणु
	पूर्णांक cpu = -1, ret, i;
	काष्ठा hfi1_affinity_node *entry;
	cpumask_var_t dअगरf, hw_thपढ़ो_mask, available_mask, पूर्णांकrs_mask;
	स्थिर काष्ठा cpumask *node_mask,
		*proc_mask = current->cpus_ptr;
	काष्ठा hfi1_affinity_node_list *affinity = &node_affinity;
	काष्ठा cpu_mask_set *set = &affinity->proc;

	/*
	 * check whether process/context affinity has alपढ़ोy
	 * been set
	 */
	अगर (current->nr_cpus_allowed == 1) अणु
		hfi1_cdbg(PROC, "PID %u %s affinity set to CPU %*pbl",
			  current->pid, current->comm,
			  cpumask_pr_args(proc_mask));
		/*
		 * Mark the pre-set CPU as used. This is atomic so we करोn't
		 * need the lock
		 */
		cpu = cpumask_first(proc_mask);
		cpumask_set_cpu(cpu, &set->used);
		जाओ करोne;
	पूर्ण अन्यथा अगर (current->nr_cpus_allowed < cpumask_weight(&set->mask)) अणु
		hfi1_cdbg(PROC, "PID %u %s affinity set to CPU set(s) %*pbl",
			  current->pid, current->comm,
			  cpumask_pr_args(proc_mask));
		जाओ करोne;
	पूर्ण

	/*
	 * The process करोes not have a preset CPU affinity so find one to
	 * recommend using the following algorithm:
	 *
	 * For each user process that is खोलोing a context on HFI Y:
	 *  a) If all cores are filled, reinitialize the biपंचांगask
	 *  b) Fill real cores first, then HT cores (First set of HT
	 *     cores on all physical cores, then second set of HT core,
	 *     and, so on) in the following order:
	 *
	 *     1. Same NUMA node as HFI Y and not running an IRQ
	 *        handler
	 *     2. Same NUMA node as HFI Y and running an IRQ handler
	 *     3. Dअगरferent NUMA node to HFI Y and not running an IRQ
	 *        handler
	 *     4. Dअगरferent NUMA node to HFI Y and running an IRQ
	 *        handler
	 *  c) Mark core as filled in the biपंचांगask. As user processes are
	 *     करोne, clear cores from the biपंचांगask.
	 */

	ret = zalloc_cpumask_var(&dअगरf, GFP_KERNEL);
	अगर (!ret)
		जाओ करोne;
	ret = zalloc_cpumask_var(&hw_thपढ़ो_mask, GFP_KERNEL);
	अगर (!ret)
		जाओ मुक्त_dअगरf;
	ret = zalloc_cpumask_var(&available_mask, GFP_KERNEL);
	अगर (!ret)
		जाओ मुक्त_hw_thपढ़ो_mask;
	ret = zalloc_cpumask_var(&पूर्णांकrs_mask, GFP_KERNEL);
	अगर (!ret)
		जाओ मुक्त_available_mask;

	mutex_lock(&affinity->lock);
	/*
	 * If we've used all available HW thपढ़ोs, clear the mask and start
	 * overloading.
	 */
	_cpu_mask_set_gen_inc(set);

	/*
	 * If NUMA node has CPUs used by पूर्णांकerrupt handlers, include them in the
	 * पूर्णांकerrupt handler mask.
	 */
	entry = node_affinity_lookup(node);
	अगर (entry) अणु
		cpumask_copy(पूर्णांकrs_mask, (entry->def_पूर्णांकr.gen ?
					  &entry->def_पूर्णांकr.mask :
					  &entry->def_पूर्णांकr.used));
		cpumask_or(पूर्णांकrs_mask, पूर्णांकrs_mask, (entry->rcv_पूर्णांकr.gen ?
						    &entry->rcv_पूर्णांकr.mask :
						    &entry->rcv_पूर्णांकr.used));
		cpumask_or(पूर्णांकrs_mask, पूर्णांकrs_mask, &entry->general_पूर्णांकr_mask);
	पूर्ण
	hfi1_cdbg(PROC, "CPUs used by interrupts: %*pbl",
		  cpumask_pr_args(पूर्णांकrs_mask));

	cpumask_copy(hw_thपढ़ो_mask, &set->mask);

	/*
	 * If HT cores are enabled, identअगरy which HW thपढ़ोs within the
	 * physical cores should be used.
	 */
	अगर (affinity->num_core_siblings > 0) अणु
		क्रम (i = 0; i < affinity->num_core_siblings; i++) अणु
			find_hw_thपढ़ो_mask(i, hw_thपढ़ो_mask, affinity);

			/*
			 * If there's at least one available core क्रम this HW
			 * thपढ़ो number, stop looking क्रम a core.
			 *
			 * dअगरf will always be not empty at least once in this
			 * loop as the used mask माला_लो reset when
			 * (set->mask == set->used) beक्रमe this loop.
			 */
			cpumask_andnot(dअगरf, hw_thपढ़ो_mask, &set->used);
			अगर (!cpumask_empty(dअगरf))
				अवरोध;
		पूर्ण
	पूर्ण
	hfi1_cdbg(PROC, "Same available HW thread on all physical CPUs: %*pbl",
		  cpumask_pr_args(hw_thपढ़ो_mask));

	node_mask = cpumask_of_node(node);
	hfi1_cdbg(PROC, "Device on NUMA %u, CPUs %*pbl", node,
		  cpumask_pr_args(node_mask));

	/* Get cpumask of available CPUs on preferred NUMA */
	cpumask_and(available_mask, hw_thपढ़ो_mask, node_mask);
	cpumask_andnot(available_mask, available_mask, &set->used);
	hfi1_cdbg(PROC, "Available CPUs on NUMA %u: %*pbl", node,
		  cpumask_pr_args(available_mask));

	/*
	 * At first, we करोn't want to place processes on the same
	 * CPUs as पूर्णांकerrupt handlers. Then, CPUs running पूर्णांकerrupt
	 * handlers are used.
	 *
	 * 1) If dअगरf is not empty, then there are CPUs not running
	 *    non-पूर्णांकerrupt handlers available, so dअगरf माला_लो copied
	 *    over to available_mask.
	 * 2) If dअगरf is empty, then all CPUs not running पूर्णांकerrupt
	 *    handlers are taken, so available_mask contains all
	 *    available CPUs running पूर्णांकerrupt handlers.
	 * 3) If available_mask is empty, then all CPUs on the
	 *    preferred NUMA node are taken, so other NUMA nodes are
	 *    used क्रम process assignments using the same method as
	 *    the preferred NUMA node.
	 */
	cpumask_andnot(dअगरf, available_mask, पूर्णांकrs_mask);
	अगर (!cpumask_empty(dअगरf))
		cpumask_copy(available_mask, dअगरf);

	/* If we करोn't have CPUs on the preferred node, use other NUMA nodes */
	अगर (cpumask_empty(available_mask)) अणु
		cpumask_andnot(available_mask, hw_thपढ़ो_mask, &set->used);
		/* Excluding preferred NUMA cores */
		cpumask_andnot(available_mask, available_mask, node_mask);
		hfi1_cdbg(PROC,
			  "Preferred NUMA node cores are taken, cores available in other NUMA nodes: %*pbl",
			  cpumask_pr_args(available_mask));

		/*
		 * At first, we करोn't want to place processes on the same
		 * CPUs as पूर्णांकerrupt handlers.
		 */
		cpumask_andnot(dअगरf, available_mask, पूर्णांकrs_mask);
		अगर (!cpumask_empty(dअगरf))
			cpumask_copy(available_mask, dअगरf);
	पूर्ण
	hfi1_cdbg(PROC, "Possible CPUs for process: %*pbl",
		  cpumask_pr_args(available_mask));

	cpu = cpumask_first(available_mask);
	अगर (cpu >= nr_cpu_ids) /* empty */
		cpu = -1;
	अन्यथा
		cpumask_set_cpu(cpu, &set->used);

	mutex_unlock(&affinity->lock);
	hfi1_cdbg(PROC, "Process assigned to CPU %d", cpu);

	मुक्त_cpumask_var(पूर्णांकrs_mask);
मुक्त_available_mask:
	मुक्त_cpumask_var(available_mask);
मुक्त_hw_thपढ़ो_mask:
	मुक्त_cpumask_var(hw_thपढ़ो_mask);
मुक्त_dअगरf:
	मुक्त_cpumask_var(dअगरf);
करोne:
	वापस cpu;
पूर्ण

व्योम hfi1_put_proc_affinity(पूर्णांक cpu)
अणु
	काष्ठा hfi1_affinity_node_list *affinity = &node_affinity;
	काष्ठा cpu_mask_set *set = &affinity->proc;

	अगर (cpu < 0)
		वापस;

	mutex_lock(&affinity->lock);
	cpu_mask_set_put(set, cpu);
	hfi1_cdbg(PROC, "Returning CPU %d for future process assignment", cpu);
	mutex_unlock(&affinity->lock);
पूर्ण
