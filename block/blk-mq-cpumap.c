<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CPU <-> hardware queue mapping helpers
 *
 * Copyright (C) 2013-2014 Jens Axboe
 */
#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>

#समावेश <linux/blk-mq.h>
#समावेश "blk.h"
#समावेश "blk-mq.h"

अटल पूर्णांक queue_index(काष्ठा blk_mq_queue_map *qmap,
		       अचिन्हित पूर्णांक nr_queues, स्थिर पूर्णांक q)
अणु
	वापस qmap->queue_offset + (q % nr_queues);
पूर्ण

अटल पूर्णांक get_first_sibling(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक ret;

	ret = cpumask_first(topology_sibling_cpumask(cpu));
	अगर (ret < nr_cpu_ids)
		वापस ret;

	वापस cpu;
पूर्ण

पूर्णांक blk_mq_map_queues(काष्ठा blk_mq_queue_map *qmap)
अणु
	अचिन्हित पूर्णांक *map = qmap->mq_map;
	अचिन्हित पूर्णांक nr_queues = qmap->nr_queues;
	अचिन्हित पूर्णांक cpu, first_sibling, q = 0;

	क्रम_each_possible_cpu(cpu)
		map[cpu] = -1;

	/*
	 * Spपढ़ो queues among present CPUs first क्रम minimizing
	 * count of dead queues which are mapped by all un-present CPUs
	 */
	क्रम_each_present_cpu(cpu) अणु
		अगर (q >= nr_queues)
			अवरोध;
		map[cpu] = queue_index(qmap, nr_queues, q++);
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		अगर (map[cpu] != -1)
			जारी;
		/*
		 * First करो sequential mapping between CPUs and queues.
		 * In हाल we still have CPUs to map, and we have some number of
		 * thपढ़ोs per cores then map sibling thपढ़ोs to the same queue
		 * क्रम perक्रमmance optimizations.
		 */
		अगर (q < nr_queues) अणु
			map[cpu] = queue_index(qmap, nr_queues, q++);
		पूर्ण अन्यथा अणु
			first_sibling = get_first_sibling(cpu);
			अगर (first_sibling == cpu)
				map[cpu] = queue_index(qmap, nr_queues, q++);
			अन्यथा
				map[cpu] = map[first_sibling];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_map_queues);

/**
 * blk_mq_hw_queue_to_node - Look up the memory node क्रम a hardware queue index
 * @qmap: CPU to hardware queue map.
 * @index: hardware queue index.
 *
 * We have no quick way of करोing reverse lookups. This is only used at
 * queue init समय, so runसमय isn't important.
 */
पूर्णांक blk_mq_hw_queue_to_node(काष्ठा blk_mq_queue_map *qmap, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		अगर (index == qmap->mq_map[i])
			वापस cpu_to_node(i);
	पूर्ण

	वापस NUMA_NO_NODE;
पूर्ण
