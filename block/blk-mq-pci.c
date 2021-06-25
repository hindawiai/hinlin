<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Christoph Hellwig.
 */
#समावेश <linux/kobject.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>

#समावेश "blk-mq.h"

/**
 * blk_mq_pci_map_queues - provide a शेष queue mapping क्रम PCI device
 * @qmap:	CPU to hardware queue map.
 * @pdev:	PCI device associated with @set.
 * @offset:	Offset to use क्रम the pci irq vector
 *
 * This function assumes the PCI device @pdev has at least as many available
 * पूर्णांकerrupt vectors as @set has queues.  It will then query the vector
 * corresponding to each queue क्रम it's affinity mask and built queue mapping
 * that maps a queue to the CPUs that have irq affinity क्रम the corresponding
 * vector.
 */
पूर्णांक blk_mq_pci_map_queues(काष्ठा blk_mq_queue_map *qmap, काष्ठा pci_dev *pdev,
			    पूर्णांक offset)
अणु
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक queue, cpu;

	क्रम (queue = 0; queue < qmap->nr_queues; queue++) अणु
		mask = pci_irq_get_affinity(pdev, queue + offset);
		अगर (!mask)
			जाओ fallback;

		क्रम_each_cpu(cpu, mask)
			qmap->mq_map[cpu] = qmap->queue_offset + queue;
	पूर्ण

	वापस 0;

fallback:
	WARN_ON_ONCE(qmap->nr_queues > 1);
	blk_mq_clear_mq_map(qmap);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_pci_map_queues);
