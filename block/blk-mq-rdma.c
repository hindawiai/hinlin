<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 Sagi Grimberg.
 */
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-rdma.h>
#समावेश <rdma/ib_verbs.h>

/**
 * blk_mq_rdma_map_queues - provide a शेष queue mapping क्रम rdma device
 * @map:	CPU to hardware queue map.
 * @dev:	rdma device to provide a mapping क्रम.
 * @first_vec:	first पूर्णांकerrupt vectors to use क्रम queues (usually 0)
 *
 * This function assumes the rdma device @dev has at least as many available
 * पूर्णांकerrupt vetors as @set has queues.  It will then query it's affinity mask
 * and built queue mapping that maps a queue to the CPUs that have irq affinity
 * क्रम the corresponding vector.
 *
 * In हाल either the driver passed a @dev with less vectors than
 * @set->nr_hw_queues, or @dev करोes not provide an affinity mask क्रम a
 * vector, we fallback to the naive mapping.
 */
पूर्णांक blk_mq_rdma_map_queues(काष्ठा blk_mq_queue_map *map,
		काष्ठा ib_device *dev, पूर्णांक first_vec)
अणु
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक queue, cpu;

	क्रम (queue = 0; queue < map->nr_queues; queue++) अणु
		mask = ib_get_vector_affinity(dev, first_vec + queue);
		अगर (!mask)
			जाओ fallback;

		क्रम_each_cpu(cpu, mask)
			map->mq_map[cpu] = map->queue_offset + queue;
	पूर्ण

	वापस 0;

fallback:
	वापस blk_mq_map_queues(map);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_rdma_map_queues);
