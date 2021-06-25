<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Christoph Hellwig.
 */
#समावेश <linux/device.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/module.h>
#समावेश "blk-mq.h"

/**
 * blk_mq_virtio_map_queues - provide a शेष queue mapping क्रम virtio device
 * @qmap:	CPU to hardware queue map.
 * @vdev:	virtio device to provide a mapping क्रम.
 * @first_vec:	first पूर्णांकerrupt vectors to use क्रम queues (usually 0)
 *
 * This function assumes the virtio device @vdev has at least as many available
 * पूर्णांकerrupt vectors as @set has queues.  It will then query the vector
 * corresponding to each queue क्रम it's affinity mask and built queue mapping
 * that maps a queue to the CPUs that have irq affinity क्रम the corresponding
 * vector.
 */
पूर्णांक blk_mq_virtio_map_queues(काष्ठा blk_mq_queue_map *qmap,
		काष्ठा virtio_device *vdev, पूर्णांक first_vec)
अणु
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक queue, cpu;

	अगर (!vdev->config->get_vq_affinity)
		जाओ fallback;

	क्रम (queue = 0; queue < qmap->nr_queues; queue++) अणु
		mask = vdev->config->get_vq_affinity(vdev, first_vec + queue);
		अगर (!mask)
			जाओ fallback;

		क्रम_each_cpu(cpu, mask)
			qmap->mq_map[cpu] = qmap->queue_offset + queue;
	पूर्ण

	वापस 0;
fallback:
	वापस blk_mq_map_queues(qmap);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_virtio_map_queues);
