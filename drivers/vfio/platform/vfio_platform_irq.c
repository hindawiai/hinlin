<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO platक्रमm devices पूर्णांकerrupt handling
 *
 * Copyright (C) 2013 - Virtual Open Systems
 * Author: Antonios Motakis <a.motakis@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/eventfd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/irq.h>

#समावेश "vfio_platform_private.h"

अटल व्योम vfio_platक्रमm_mask(काष्ठा vfio_platक्रमm_irq *irq_ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irq_ctx->lock, flags);

	अगर (!irq_ctx->masked) अणु
		disable_irq_nosync(irq_ctx->hwirq);
		irq_ctx->masked = true;
	पूर्ण

	spin_unlock_irqrestore(&irq_ctx->lock, flags);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_mask_handler(व्योम *opaque, व्योम *unused)
अणु
	काष्ठा vfio_platक्रमm_irq *irq_ctx = opaque;

	vfio_platक्रमm_mask(irq_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_set_irq_mask(काष्ठा vfio_platक्रमm_device *vdev,
				      अचिन्हित index, अचिन्हित start,
				      अचिन्हित count, uपूर्णांक32_t flags,
				      व्योम *data)
अणु
	अगर (start != 0 || count != 1)
		वापस -EINVAL;

	अगर (!(vdev->irqs[index].flags & VFIO_IRQ_INFO_MASKABLE))
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t fd = *(पूर्णांक32_t *)data;

		अगर (fd >= 0)
			वापस vfio_virqfd_enable((व्योम *) &vdev->irqs[index],
						  vfio_platक्रमm_mask_handler,
						  शून्य, शून्य,
						  &vdev->irqs[index].mask, fd);

		vfio_virqfd_disable(&vdev->irqs[index].mask);
		वापस 0;
	पूर्ण

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		vfio_platक्रमm_mask(&vdev->irqs[index]);

	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t mask = *(uपूर्णांक8_t *)data;

		अगर (mask)
			vfio_platक्रमm_mask(&vdev->irqs[index]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vfio_platक्रमm_unmask(काष्ठा vfio_platक्रमm_irq *irq_ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irq_ctx->lock, flags);

	अगर (irq_ctx->masked) अणु
		enable_irq(irq_ctx->hwirq);
		irq_ctx->masked = false;
	पूर्ण

	spin_unlock_irqrestore(&irq_ctx->lock, flags);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_unmask_handler(व्योम *opaque, व्योम *unused)
अणु
	काष्ठा vfio_platक्रमm_irq *irq_ctx = opaque;

	vfio_platक्रमm_unmask(irq_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_set_irq_unmask(काष्ठा vfio_platक्रमm_device *vdev,
					अचिन्हित index, अचिन्हित start,
					अचिन्हित count, uपूर्णांक32_t flags,
					व्योम *data)
अणु
	अगर (start != 0 || count != 1)
		वापस -EINVAL;

	अगर (!(vdev->irqs[index].flags & VFIO_IRQ_INFO_MASKABLE))
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t fd = *(पूर्णांक32_t *)data;

		अगर (fd >= 0)
			वापस vfio_virqfd_enable((व्योम *) &vdev->irqs[index],
						  vfio_platक्रमm_unmask_handler,
						  शून्य, शून्य,
						  &vdev->irqs[index].unmask,
						  fd);

		vfio_virqfd_disable(&vdev->irqs[index].unmask);
		वापस 0;
	पूर्ण

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		vfio_platक्रमm_unmask(&vdev->irqs[index]);

	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t unmask = *(uपूर्णांक8_t *)data;

		अगर (unmask)
			vfio_platक्रमm_unmask(&vdev->irqs[index]);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t vfio_स्वतःmasked_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vfio_platक्रमm_irq *irq_ctx = dev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = IRQ_NONE;

	spin_lock_irqsave(&irq_ctx->lock, flags);

	अगर (!irq_ctx->masked) अणु
		ret = IRQ_HANDLED;

		/* स्वतःmask maskable पूर्णांकerrupts */
		disable_irq_nosync(irq_ctx->hwirq);
		irq_ctx->masked = true;
	पूर्ण

	spin_unlock_irqrestore(&irq_ctx->lock, flags);

	अगर (ret == IRQ_HANDLED)
		eventfd_संकेत(irq_ctx->trigger, 1);

	वापस ret;
पूर्ण

अटल irqवापस_t vfio_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vfio_platक्रमm_irq *irq_ctx = dev_id;

	eventfd_संकेत(irq_ctx->trigger, 1);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vfio_set_trigger(काष्ठा vfio_platक्रमm_device *vdev, पूर्णांक index,
			    पूर्णांक fd, irq_handler_t handler)
अणु
	काष्ठा vfio_platक्रमm_irq *irq = &vdev->irqs[index];
	काष्ठा eventfd_ctx *trigger;
	पूर्णांक ret;

	अगर (irq->trigger) अणु
		irq_clear_status_flags(irq->hwirq, IRQ_NOAUTOEN);
		मुक्त_irq(irq->hwirq, irq);
		kमुक्त(irq->name);
		eventfd_ctx_put(irq->trigger);
		irq->trigger = शून्य;
	पूर्ण

	अगर (fd < 0) /* Disable only */
		वापस 0;

	irq->name = kaप्र_लिखो(GFP_KERNEL, "vfio-irq[%d](%s)",
						irq->hwirq, vdev->name);
	अगर (!irq->name)
		वापस -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(trigger)) अणु
		kमुक्त(irq->name);
		वापस PTR_ERR(trigger);
	पूर्ण

	irq->trigger = trigger;

	irq_set_status_flags(irq->hwirq, IRQ_NOAUTOEN);
	ret = request_irq(irq->hwirq, handler, 0, irq->name, irq);
	अगर (ret) अणु
		kमुक्त(irq->name);
		eventfd_ctx_put(trigger);
		irq->trigger = शून्य;
		वापस ret;
	पूर्ण

	अगर (!irq->masked)
		enable_irq(irq->hwirq);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_set_irq_trigger(काष्ठा vfio_platक्रमm_device *vdev,
					 अचिन्हित index, अचिन्हित start,
					 अचिन्हित count, uपूर्णांक32_t flags,
					 व्योम *data)
अणु
	काष्ठा vfio_platक्रमm_irq *irq = &vdev->irqs[index];
	irq_handler_t handler;

	अगर (vdev->irqs[index].flags & VFIO_IRQ_INFO_AUTOMASKED)
		handler = vfio_स्वतःmasked_irq_handler;
	अन्यथा
		handler = vfio_irq_handler;

	अगर (!count && (flags & VFIO_IRQ_SET_DATA_NONE))
		वापस vfio_set_trigger(vdev, index, -1, handler);

	अगर (start != 0 || count != 1)
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t fd = *(पूर्णांक32_t *)data;

		वापस vfio_set_trigger(vdev, index, fd, handler);
	पूर्ण

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		handler(irq->hwirq, irq);

	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t trigger = *(uपूर्णांक8_t *)data;

		अगर (trigger)
			handler(irq->hwirq, irq);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vfio_platक्रमm_set_irqs_ioctl(काष्ठा vfio_platक्रमm_device *vdev,
				 uपूर्णांक32_t flags, अचिन्हित index, अचिन्हित start,
				 अचिन्हित count, व्योम *data)
अणु
	पूर्णांक (*func)(काष्ठा vfio_platक्रमm_device *vdev, अचिन्हित index,
		    अचिन्हित start, अचिन्हित count, uपूर्णांक32_t flags,
		    व्योम *data) = शून्य;

	चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
	हाल VFIO_IRQ_SET_ACTION_MASK:
		func = vfio_platक्रमm_set_irq_mask;
		अवरोध;
	हाल VFIO_IRQ_SET_ACTION_UNMASK:
		func = vfio_platक्रमm_set_irq_unmask;
		अवरोध;
	हाल VFIO_IRQ_SET_ACTION_TRIGGER:
		func = vfio_platक्रमm_set_irq_trigger;
		अवरोध;
	पूर्ण

	अगर (!func)
		वापस -ENOTTY;

	वापस func(vdev, index, start, count, flags, data);
पूर्ण

पूर्णांक vfio_platक्रमm_irq_init(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	पूर्णांक cnt = 0, i;

	जबतक (vdev->get_irq(vdev, cnt) >= 0)
		cnt++;

	vdev->irqs = kसुस्मृति(cnt, माप(काष्ठा vfio_platक्रमm_irq), GFP_KERNEL);
	अगर (!vdev->irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < cnt; i++) अणु
		पूर्णांक hwirq = vdev->get_irq(vdev, i);

		अगर (hwirq < 0)
			जाओ err;

		spin_lock_init(&vdev->irqs[i].lock);

		vdev->irqs[i].flags = VFIO_IRQ_INFO_EVENTFD;

		अगर (irq_get_trigger_type(hwirq) & IRQ_TYPE_LEVEL_MASK)
			vdev->irqs[i].flags |= VFIO_IRQ_INFO_MASKABLE
						| VFIO_IRQ_INFO_AUTOMASKED;

		vdev->irqs[i].count = 1;
		vdev->irqs[i].hwirq = hwirq;
		vdev->irqs[i].masked = false;
	पूर्ण

	vdev->num_irqs = cnt;

	वापस 0;
err:
	kमुक्त(vdev->irqs);
	वापस -EINVAL;
पूर्ण

व्योम vfio_platक्रमm_irq_cleanup(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vdev->num_irqs; i++)
		vfio_set_trigger(vdev, i, -1, शून्य);

	vdev->num_irqs = 0;
	kमुक्त(vdev->irqs);
पूर्ण
