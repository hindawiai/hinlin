<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2019 NXP
 */

#समावेश <linux/vfपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/msi.h>

#समावेश "linux/fsl/mc.h"
#समावेश "vfio_fsl_mc_private.h"

अटल पूर्णांक vfio_fsl_mc_irqs_allocate(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	काष्ठा vfio_fsl_mc_irq *mc_irq;
	पूर्णांक irq_count;
	पूर्णांक ret, i;

	/* Device करोes not support any पूर्णांकerrupt */
	अगर (mc_dev->obj_desc.irq_count == 0)
		वापस 0;

	/* पूर्णांकerrupts were alपढ़ोy allocated क्रम this device */
	अगर (vdev->mc_irqs)
		वापस 0;

	irq_count = mc_dev->obj_desc.irq_count;

	mc_irq = kसुस्मृति(irq_count, माप(*mc_irq), GFP_KERNEL);
	अगर (!mc_irq)
		वापस -ENOMEM;

	/* Allocate IRQs */
	ret = fsl_mc_allocate_irqs(mc_dev);
	अगर (ret) अणु
		kमुक्त(mc_irq);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < irq_count; i++) अणु
		mc_irq[i].count = 1;
		mc_irq[i].flags = VFIO_IRQ_INFO_EVENTFD;
	पूर्ण

	vdev->mc_irqs = mc_irq;

	वापस 0;
पूर्ण

अटल irqवापस_t vfio_fsl_mc_irq_handler(पूर्णांक irq_num, व्योम *arg)
अणु
	काष्ठा vfio_fsl_mc_irq *mc_irq = (काष्ठा vfio_fsl_mc_irq *)arg;

	eventfd_संकेत(mc_irq->trigger, 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vfio_set_trigger(काष्ठा vfio_fsl_mc_device *vdev,
						   पूर्णांक index, पूर्णांक fd)
अणु
	काष्ठा vfio_fsl_mc_irq *irq = &vdev->mc_irqs[index];
	काष्ठा eventfd_ctx *trigger;
	पूर्णांक hwirq;
	पूर्णांक ret;

	hwirq = vdev->mc_dev->irqs[index]->msi_desc->irq;
	अगर (irq->trigger) अणु
		मुक्त_irq(hwirq, irq);
		kमुक्त(irq->name);
		eventfd_ctx_put(irq->trigger);
		irq->trigger = शून्य;
	पूर्ण

	अगर (fd < 0) /* Disable only */
		वापस 0;

	irq->name = kaप्र_लिखो(GFP_KERNEL, "vfio-irq[%d](%s)",
			    hwirq, dev_name(&vdev->mc_dev->dev));
	अगर (!irq->name)
		वापस -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(trigger)) अणु
		kमुक्त(irq->name);
		वापस PTR_ERR(trigger);
	पूर्ण

	irq->trigger = trigger;

	ret = request_irq(hwirq, vfio_fsl_mc_irq_handler, 0,
		  irq->name, irq);
	अगर (ret) अणु
		kमुक्त(irq->name);
		eventfd_ctx_put(trigger);
		irq->trigger = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_fsl_mc_set_irq_trigger(काष्ठा vfio_fsl_mc_device *vdev,
				       अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start,
				       अचिन्हित पूर्णांक count, u32 flags,
				       व्योम *data)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	पूर्णांक ret, hwirq;
	काष्ठा vfio_fsl_mc_irq *irq;
	काष्ठा device *cont_dev = fsl_mc_cont_dev(&mc_dev->dev);
	काष्ठा fsl_mc_device *mc_cont = to_fsl_mc_device(cont_dev);

	अगर (!count && (flags & VFIO_IRQ_SET_DATA_NONE))
		वापस vfio_set_trigger(vdev, index, -1);

	अगर (start != 0 || count != 1)
		वापस -EINVAL;

	mutex_lock(&vdev->reflck->lock);
	ret = fsl_mc_populate_irq_pool(mc_cont,
			FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS);
	अगर (ret)
		जाओ unlock;

	ret = vfio_fsl_mc_irqs_allocate(vdev);
	अगर (ret)
		जाओ unlock;
	mutex_unlock(&vdev->reflck->lock);

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		s32 fd = *(s32 *)data;

		वापस vfio_set_trigger(vdev, index, fd);
	पूर्ण

	hwirq = vdev->mc_dev->irqs[index]->msi_desc->irq;

	irq = &vdev->mc_irqs[index];

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		vfio_fsl_mc_irq_handler(hwirq, irq);

	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		u8 trigger = *(u8 *)data;

		अगर (trigger)
			vfio_fsl_mc_irq_handler(hwirq, irq);
	पूर्ण

	वापस 0;

unlock:
	mutex_unlock(&vdev->reflck->lock);
	वापस ret;

पूर्ण

पूर्णांक vfio_fsl_mc_set_irqs_ioctl(काष्ठा vfio_fsl_mc_device *vdev,
			       u32 flags, अचिन्हित पूर्णांक index,
			       अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
			       व्योम *data)
अणु
	अगर (flags & VFIO_IRQ_SET_ACTION_TRIGGER)
		वापस  vfio_fsl_mc_set_irq_trigger(vdev, index, start,
			  count, flags, data);
	अन्यथा
		वापस -EINVAL;
पूर्ण

/* Free All IRQs क्रम the given MC object */
व्योम vfio_fsl_mc_irqs_cleanup(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	पूर्णांक irq_count = mc_dev->obj_desc.irq_count;
	पूर्णांक i;

	/*
	 * Device करोes not support any पूर्णांकerrupt or the पूर्णांकerrupts
	 * were not configured
	 */
	अगर (!vdev->mc_irqs)
		वापस;

	क्रम (i = 0; i < irq_count; i++)
		vfio_set_trigger(vdev, i, -1);

	fsl_mc_मुक्त_irqs(mc_dev);
	kमुक्त(vdev->mc_irqs);
	vdev->mc_irqs = शून्य;
पूर्ण
