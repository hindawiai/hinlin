<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO PCI पूर्णांकerrupt handling
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>
#समावेश <linux/file.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>

#समावेश "vfio_pci_private.h"

/*
 * INTx
 */
अटल व्योम vfio_send_पूर्णांकx_eventfd(व्योम *opaque, व्योम *unused)
अणु
	काष्ठा vfio_pci_device *vdev = opaque;

	अगर (likely(is_पूर्णांकx(vdev) && !vdev->virq_disabled))
		eventfd_संकेत(vdev->ctx[0].trigger, 1);
पूर्ण

व्योम vfio_pci_पूर्णांकx_mask(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdev->irqlock, flags);

	/*
	 * Masking can come from पूर्णांकerrupt, ioctl, or config space
	 * via INTx disable.  The latter means this can get called
	 * even when not using पूर्णांकx delivery.  In this हाल, just
	 * try to have the physical bit follow the भव bit.
	 */
	अगर (unlikely(!is_पूर्णांकx(vdev))) अणु
		अगर (vdev->pci_2_3)
			pci_पूर्णांकx(pdev, 0);
	पूर्ण अन्यथा अगर (!vdev->ctx[0].masked) अणु
		/*
		 * Can't use check_and_mask here because we always want to
		 * mask, not just when something is pending.
		 */
		अगर (vdev->pci_2_3)
			pci_पूर्णांकx(pdev, 0);
		अन्यथा
			disable_irq_nosync(pdev->irq);

		vdev->ctx[0].masked = true;
	पूर्ण

	spin_unlock_irqrestore(&vdev->irqlock, flags);
पूर्ण

/*
 * If this is triggered by an eventfd, we can't call eventfd_संकेत
 * or अन्यथा we'll deadlock on the eventfd रुको queue.  Return >0 when
 * a संकेत is necessary, which can then be handled via a work queue
 * or directly depending on the caller.
 */
अटल पूर्णांक vfio_pci_पूर्णांकx_unmask_handler(व्योम *opaque, व्योम *unused)
अणु
	काष्ठा vfio_pci_device *vdev = opaque;
	काष्ठा pci_dev *pdev = vdev->pdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&vdev->irqlock, flags);

	/*
	 * Unmasking comes from ioctl or config, so again, have the
	 * physical bit follow the भव even when not using INTx.
	 */
	अगर (unlikely(!is_पूर्णांकx(vdev))) अणु
		अगर (vdev->pci_2_3)
			pci_पूर्णांकx(pdev, 1);
	पूर्ण अन्यथा अगर (vdev->ctx[0].masked && !vdev->virq_disabled) अणु
		/*
		 * A pending पूर्णांकerrupt here would immediately trigger,
		 * but we can aव्योम that overhead by just re-sending
		 * the पूर्णांकerrupt to the user.
		 */
		अगर (vdev->pci_2_3) अणु
			अगर (!pci_check_and_unmask_पूर्णांकx(pdev))
				ret = 1;
		पूर्ण अन्यथा
			enable_irq(pdev->irq);

		vdev->ctx[0].masked = (ret > 0);
	पूर्ण

	spin_unlock_irqrestore(&vdev->irqlock, flags);

	वापस ret;
पूर्ण

व्योम vfio_pci_पूर्णांकx_unmask(काष्ठा vfio_pci_device *vdev)
अणु
	अगर (vfio_pci_पूर्णांकx_unmask_handler(vdev, शून्य) > 0)
		vfio_send_पूर्णांकx_eventfd(vdev, शून्य);
पूर्ण

अटल irqवापस_t vfio_पूर्णांकx_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vfio_pci_device *vdev = dev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = IRQ_NONE;

	spin_lock_irqsave(&vdev->irqlock, flags);

	अगर (!vdev->pci_2_3) अणु
		disable_irq_nosync(vdev->pdev->irq);
		vdev->ctx[0].masked = true;
		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (!vdev->ctx[0].masked &&  /* may be shared */
		   pci_check_and_mask_पूर्णांकx(vdev->pdev)) अणु
		vdev->ctx[0].masked = true;
		ret = IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&vdev->irqlock, flags);

	अगर (ret == IRQ_HANDLED)
		vfio_send_पूर्णांकx_eventfd(vdev, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_पूर्णांकx_enable(काष्ठा vfio_pci_device *vdev)
अणु
	अगर (!is_irq_none(vdev))
		वापस -EINVAL;

	अगर (!vdev->pdev->irq)
		वापस -ENODEV;

	vdev->ctx = kzalloc(माप(काष्ठा vfio_pci_irq_ctx), GFP_KERNEL);
	अगर (!vdev->ctx)
		वापस -ENOMEM;

	vdev->num_ctx = 1;

	/*
	 * If the भव पूर्णांकerrupt is masked, restore it.  Devices
	 * supporting DisINTx can be masked at the hardware level
	 * here, non-PCI-2.3 devices will have to रुको until the
	 * पूर्णांकerrupt is enabled.
	 */
	vdev->ctx[0].masked = vdev->virq_disabled;
	अगर (vdev->pci_2_3)
		pci_पूर्णांकx(vdev->pdev, !vdev->ctx[0].masked);

	vdev->irq_type = VFIO_PCI_INTX_IRQ_INDEX;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_पूर्णांकx_set_संकेत(काष्ठा vfio_pci_device *vdev, पूर्णांक fd)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	अचिन्हित दीर्घ irqflags = IRQF_SHARED;
	काष्ठा eventfd_ctx *trigger;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (vdev->ctx[0].trigger) अणु
		मुक्त_irq(pdev->irq, vdev);
		kमुक्त(vdev->ctx[0].name);
		eventfd_ctx_put(vdev->ctx[0].trigger);
		vdev->ctx[0].trigger = शून्य;
	पूर्ण

	अगर (fd < 0) /* Disable only */
		वापस 0;

	vdev->ctx[0].name = kaप्र_लिखो(GFP_KERNEL, "vfio-intx(%s)",
				      pci_name(pdev));
	अगर (!vdev->ctx[0].name)
		वापस -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(trigger)) अणु
		kमुक्त(vdev->ctx[0].name);
		वापस PTR_ERR(trigger);
	पूर्ण

	vdev->ctx[0].trigger = trigger;

	अगर (!vdev->pci_2_3)
		irqflags = 0;

	ret = request_irq(pdev->irq, vfio_पूर्णांकx_handler,
			  irqflags, vdev->ctx[0].name, vdev);
	अगर (ret) अणु
		vdev->ctx[0].trigger = शून्य;
		kमुक्त(vdev->ctx[0].name);
		eventfd_ctx_put(trigger);
		वापस ret;
	पूर्ण

	/*
	 * INTx disable will stick across the new irq setup,
	 * disable_irq won't.
	 */
	spin_lock_irqsave(&vdev->irqlock, flags);
	अगर (!vdev->pci_2_3 && vdev->ctx[0].masked)
		disable_irq_nosync(pdev->irq);
	spin_unlock_irqrestore(&vdev->irqlock, flags);

	वापस 0;
पूर्ण

अटल व्योम vfio_पूर्णांकx_disable(काष्ठा vfio_pci_device *vdev)
अणु
	vfio_virqfd_disable(&vdev->ctx[0].unmask);
	vfio_virqfd_disable(&vdev->ctx[0].mask);
	vfio_पूर्णांकx_set_संकेत(vdev, -1);
	vdev->irq_type = VFIO_PCI_NUM_IRQS;
	vdev->num_ctx = 0;
	kमुक्त(vdev->ctx);
पूर्ण

/*
 * MSI/MSI-X
 */
अटल irqवापस_t vfio_msihandler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा eventfd_ctx *trigger = arg;

	eventfd_संकेत(trigger, 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vfio_msi_enable(काष्ठा vfio_pci_device *vdev, पूर्णांक nvec, bool msix)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	अचिन्हित पूर्णांक flag = msix ? PCI_IRQ_MSIX : PCI_IRQ_MSI;
	पूर्णांक ret;
	u16 cmd;

	अगर (!is_irq_none(vdev))
		वापस -EINVAL;

	vdev->ctx = kसुस्मृति(nvec, माप(काष्ठा vfio_pci_irq_ctx), GFP_KERNEL);
	अगर (!vdev->ctx)
		वापस -ENOMEM;

	/* वापस the number of supported vectors अगर we can't get all: */
	cmd = vfio_pci_memory_lock_and_enable(vdev);
	ret = pci_alloc_irq_vectors(pdev, 1, nvec, flag);
	अगर (ret < nvec) अणु
		अगर (ret > 0)
			pci_मुक्त_irq_vectors(pdev);
		vfio_pci_memory_unlock_and_restore(vdev, cmd);
		kमुक्त(vdev->ctx);
		वापस ret;
	पूर्ण
	vfio_pci_memory_unlock_and_restore(vdev, cmd);

	vdev->num_ctx = nvec;
	vdev->irq_type = msix ? VFIO_PCI_MSIX_IRQ_INDEX :
				VFIO_PCI_MSI_IRQ_INDEX;

	अगर (!msix) अणु
		/*
		 * Compute the भव hardware field क्रम max msi vectors -
		 * it is the log base 2 of the number of vectors.
		 */
		vdev->msi_qmax = fls(nvec * 2 - 1) - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_msi_set_vector_संकेत(काष्ठा vfio_pci_device *vdev,
				      पूर्णांक vector, पूर्णांक fd, bool msix)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	काष्ठा eventfd_ctx *trigger;
	पूर्णांक irq, ret;
	u16 cmd;

	अगर (vector < 0 || vector >= vdev->num_ctx)
		वापस -EINVAL;

	irq = pci_irq_vector(pdev, vector);

	अगर (vdev->ctx[vector].trigger) अणु
		irq_bypass_unरेजिस्टर_producer(&vdev->ctx[vector].producer);

		cmd = vfio_pci_memory_lock_and_enable(vdev);
		मुक्त_irq(irq, vdev->ctx[vector].trigger);
		vfio_pci_memory_unlock_and_restore(vdev, cmd);

		kमुक्त(vdev->ctx[vector].name);
		eventfd_ctx_put(vdev->ctx[vector].trigger);
		vdev->ctx[vector].trigger = शून्य;
	पूर्ण

	अगर (fd < 0)
		वापस 0;

	vdev->ctx[vector].name = kaप्र_लिखो(GFP_KERNEL, "vfio-msi%s[%d](%s)",
					   msix ? "x" : "", vector,
					   pci_name(pdev));
	अगर (!vdev->ctx[vector].name)
		वापस -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(trigger)) अणु
		kमुक्त(vdev->ctx[vector].name);
		वापस PTR_ERR(trigger);
	पूर्ण

	/*
	 * The MSIx vector table resides in device memory which may be cleared
	 * via backकरोor resets. We करोn't allow direct access to the vector
	 * table so even अगर a userspace driver attempts to save/restore around
	 * such a reset it would be unsuccessful. To aव्योम this, restore the
	 * cached value of the message prior to enabling.
	 */
	cmd = vfio_pci_memory_lock_and_enable(vdev);
	अगर (msix) अणु
		काष्ठा msi_msg msg;

		get_cached_msi_msg(irq, &msg);
		pci_ग_लिखो_msi_msg(irq, &msg);
	पूर्ण

	ret = request_irq(irq, vfio_msihandler, 0,
			  vdev->ctx[vector].name, trigger);
	vfio_pci_memory_unlock_and_restore(vdev, cmd);
	अगर (ret) अणु
		kमुक्त(vdev->ctx[vector].name);
		eventfd_ctx_put(trigger);
		वापस ret;
	पूर्ण

	vdev->ctx[vector].producer.token = trigger;
	vdev->ctx[vector].producer.irq = irq;
	ret = irq_bypass_रेजिस्टर_producer(&vdev->ctx[vector].producer);
	अगर (unlikely(ret)) अणु
		dev_info(&pdev->dev,
		"irq bypass producer (token %p) registration fails: %d\n",
		vdev->ctx[vector].producer.token, ret);

		vdev->ctx[vector].producer.token = शून्य;
	पूर्ण
	vdev->ctx[vector].trigger = trigger;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_msi_set_block(काष्ठा vfio_pci_device *vdev, अचिन्हित start,
			      अचिन्हित count, पूर्णांक32_t *fds, bool msix)
अणु
	पूर्णांक i, j, ret = 0;

	अगर (start >= vdev->num_ctx || start + count > vdev->num_ctx)
		वापस -EINVAL;

	क्रम (i = 0, j = start; i < count && !ret; i++, j++) अणु
		पूर्णांक fd = fds ? fds[i] : -1;
		ret = vfio_msi_set_vector_संकेत(vdev, j, fd, msix);
	पूर्ण

	अगर (ret) अणु
		क्रम (--j; j >= (पूर्णांक)start; j--)
			vfio_msi_set_vector_संकेत(vdev, j, -1, msix);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vfio_msi_disable(काष्ठा vfio_pci_device *vdev, bool msix)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक i;
	u16 cmd;

	क्रम (i = 0; i < vdev->num_ctx; i++) अणु
		vfio_virqfd_disable(&vdev->ctx[i].unmask);
		vfio_virqfd_disable(&vdev->ctx[i].mask);
	पूर्ण

	vfio_msi_set_block(vdev, 0, vdev->num_ctx, शून्य, msix);

	cmd = vfio_pci_memory_lock_and_enable(vdev);
	pci_मुक्त_irq_vectors(pdev);
	vfio_pci_memory_unlock_and_restore(vdev, cmd);

	/*
	 * Both disable paths above use pci_पूर्णांकx_क्रम_msi() to clear DisINTx
	 * via their shutकरोwn paths.  Restore क्रम NoINTx devices.
	 */
	अगर (vdev->noपूर्णांकx)
		pci_पूर्णांकx(pdev, 0);

	vdev->irq_type = VFIO_PCI_NUM_IRQS;
	vdev->num_ctx = 0;
	kमुक्त(vdev->ctx);
पूर्ण

/*
 * IOCTL support
 */
अटल पूर्णांक vfio_pci_set_पूर्णांकx_unmask(काष्ठा vfio_pci_device *vdev,
				    अचिन्हित index, अचिन्हित start,
				    अचिन्हित count, uपूर्णांक32_t flags, व्योम *data)
अणु
	अगर (!is_पूर्णांकx(vdev) || start != 0 || count != 1)
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		vfio_pci_पूर्णांकx_unmask(vdev);
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t unmask = *(uपूर्णांक8_t *)data;
		अगर (unmask)
			vfio_pci_पूर्णांकx_unmask(vdev);
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t fd = *(पूर्णांक32_t *)data;
		अगर (fd >= 0)
			वापस vfio_virqfd_enable((व्योम *) vdev,
						  vfio_pci_पूर्णांकx_unmask_handler,
						  vfio_send_पूर्णांकx_eventfd, शून्य,
						  &vdev->ctx[0].unmask, fd);

		vfio_virqfd_disable(&vdev->ctx[0].unmask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_set_पूर्णांकx_mask(काष्ठा vfio_pci_device *vdev,
				  अचिन्हित index, अचिन्हित start,
				  अचिन्हित count, uपूर्णांक32_t flags, व्योम *data)
अणु
	अगर (!is_पूर्णांकx(vdev) || start != 0 || count != 1)
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		vfio_pci_पूर्णांकx_mask(vdev);
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t mask = *(uपूर्णांक8_t *)data;
		अगर (mask)
			vfio_pci_पूर्णांकx_mask(vdev);
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		वापस -ENOTTY; /* XXX implement me */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_set_पूर्णांकx_trigger(काष्ठा vfio_pci_device *vdev,
				     अचिन्हित index, अचिन्हित start,
				     अचिन्हित count, uपूर्णांक32_t flags, व्योम *data)
अणु
	अगर (is_पूर्णांकx(vdev) && !count && (flags & VFIO_IRQ_SET_DATA_NONE)) अणु
		vfio_पूर्णांकx_disable(vdev);
		वापस 0;
	पूर्ण

	अगर (!(is_पूर्णांकx(vdev) || is_irq_none(vdev)) || start != 0 || count != 1)
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t fd = *(पूर्णांक32_t *)data;
		पूर्णांक ret;

		अगर (is_पूर्णांकx(vdev))
			वापस vfio_पूर्णांकx_set_संकेत(vdev, fd);

		ret = vfio_पूर्णांकx_enable(vdev);
		अगर (ret)
			वापस ret;

		ret = vfio_पूर्णांकx_set_संकेत(vdev, fd);
		अगर (ret)
			vfio_पूर्णांकx_disable(vdev);

		वापस ret;
	पूर्ण

	अगर (!is_पूर्णांकx(vdev))
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		vfio_send_पूर्णांकx_eventfd(vdev, शून्य);
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t trigger = *(uपूर्णांक8_t *)data;
		अगर (trigger)
			vfio_send_पूर्णांकx_eventfd(vdev, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_set_msi_trigger(काष्ठा vfio_pci_device *vdev,
				    अचिन्हित index, अचिन्हित start,
				    अचिन्हित count, uपूर्णांक32_t flags, व्योम *data)
अणु
	पूर्णांक i;
	bool msix = (index == VFIO_PCI_MSIX_IRQ_INDEX) ? true : false;

	अगर (irq_is(vdev, index) && !count && (flags & VFIO_IRQ_SET_DATA_NONE)) अणु
		vfio_msi_disable(vdev, msix);
		वापस 0;
	पूर्ण

	अगर (!(irq_is(vdev, index) || is_irq_none(vdev)))
		वापस -EINVAL;

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t *fds = data;
		पूर्णांक ret;

		अगर (vdev->irq_type == index)
			वापस vfio_msi_set_block(vdev, start, count,
						  fds, msix);

		ret = vfio_msi_enable(vdev, start + count, msix);
		अगर (ret)
			वापस ret;

		ret = vfio_msi_set_block(vdev, start, count, fds, msix);
		अगर (ret)
			vfio_msi_disable(vdev, msix);

		वापस ret;
	पूर्ण

	अगर (!irq_is(vdev, index) || start + count > vdev->num_ctx)
		वापस -EINVAL;

	क्रम (i = start; i < start + count; i++) अणु
		अगर (!vdev->ctx[i].trigger)
			जारी;
		अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
			eventfd_संकेत(vdev->ctx[i].trigger, 1);
		पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
			uपूर्णांक8_t *bools = data;
			अगर (bools[i - start])
				eventfd_संकेत(vdev->ctx[i].trigger, 1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_set_ctx_trigger_single(काष्ठा eventfd_ctx **ctx,
					   अचिन्हित पूर्णांक count, uपूर्णांक32_t flags,
					   व्योम *data)
अणु
	/* DATA_NONE/DATA_BOOL enables loopback testing */
	अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
		अगर (*ctx) अणु
			अगर (count) अणु
				eventfd_संकेत(*ctx, 1);
			पूर्ण अन्यथा अणु
				eventfd_ctx_put(*ctx);
				*ctx = शून्य;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_BOOL) अणु
		uपूर्णांक8_t trigger;

		अगर (!count)
			वापस -EINVAL;

		trigger = *(uपूर्णांक8_t *)data;
		अगर (trigger && *ctx)
			eventfd_संकेत(*ctx, 1);

		वापस 0;
	पूर्ण अन्यथा अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक32_t fd;

		अगर (!count)
			वापस -EINVAL;

		fd = *(पूर्णांक32_t *)data;
		अगर (fd == -1) अणु
			अगर (*ctx)
				eventfd_ctx_put(*ctx);
			*ctx = शून्य;
		पूर्ण अन्यथा अगर (fd >= 0) अणु
			काष्ठा eventfd_ctx *efdctx;

			efdctx = eventfd_ctx_fdget(fd);
			अगर (IS_ERR(efdctx))
				वापस PTR_ERR(efdctx);

			अगर (*ctx)
				eventfd_ctx_put(*ctx);

			*ctx = efdctx;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vfio_pci_set_err_trigger(काष्ठा vfio_pci_device *vdev,
				    अचिन्हित index, अचिन्हित start,
				    अचिन्हित count, uपूर्णांक32_t flags, व्योम *data)
अणु
	अगर (index != VFIO_PCI_ERR_IRQ_INDEX || start != 0 || count > 1)
		वापस -EINVAL;

	वापस vfio_pci_set_ctx_trigger_single(&vdev->err_trigger,
					       count, flags, data);
पूर्ण

अटल पूर्णांक vfio_pci_set_req_trigger(काष्ठा vfio_pci_device *vdev,
				    अचिन्हित index, अचिन्हित start,
				    अचिन्हित count, uपूर्णांक32_t flags, व्योम *data)
अणु
	अगर (index != VFIO_PCI_REQ_IRQ_INDEX || start != 0 || count > 1)
		वापस -EINVAL;

	वापस vfio_pci_set_ctx_trigger_single(&vdev->req_trigger,
					       count, flags, data);
पूर्ण

पूर्णांक vfio_pci_set_irqs_ioctl(काष्ठा vfio_pci_device *vdev, uपूर्णांक32_t flags,
			    अचिन्हित index, अचिन्हित start, अचिन्हित count,
			    व्योम *data)
अणु
	पूर्णांक (*func)(काष्ठा vfio_pci_device *vdev, अचिन्हित index,
		    अचिन्हित start, अचिन्हित count, uपूर्णांक32_t flags,
		    व्योम *data) = शून्य;

	चयन (index) अणु
	हाल VFIO_PCI_INTX_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_MASK:
			func = vfio_pci_set_पूर्णांकx_mask;
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_UNMASK:
			func = vfio_pci_set_पूर्णांकx_unmask;
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			func = vfio_pci_set_पूर्णांकx_trigger;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल VFIO_PCI_MSI_IRQ_INDEX:
	हाल VFIO_PCI_MSIX_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_MASK:
		हाल VFIO_IRQ_SET_ACTION_UNMASK:
			/* XXX Need masking support exported */
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			func = vfio_pci_set_msi_trigger;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल VFIO_PCI_ERR_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			अगर (pci_is_pcie(vdev->pdev))
				func = vfio_pci_set_err_trigger;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल VFIO_PCI_REQ_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			func = vfio_pci_set_req_trigger;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!func)
		वापस -ENOTTY;

	वापस func(vdev, index, start, count, flags, data);
पूर्ण
