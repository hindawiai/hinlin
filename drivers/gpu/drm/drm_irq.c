<शैली गुरु>
/*
 * drm_irq.c IRQ and vblank support
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created: Fri Mar 19 14:30:16 1999 by faith@valinux.com
 *
 * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>	/* For task queue support */
#समावेश <linux/pci.h>
#समावेश <linux/vgaarb.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "drm_internal.h"

/**
 * DOC: irq helpers
 *
 * The DRM core provides very simple support helpers to enable IRQ handling on a
 * device through the drm_irq_install() and drm_irq_uninstall() functions. This
 * only supports devices with a single पूर्णांकerrupt on the मुख्य device stored in
 * &drm_device.dev and set as the device paramter in drm_dev_alloc().
 *
 * These IRQ helpers are strictly optional. Drivers which roll their own only
 * need to set &drm_device.irq_enabled to संकेत the DRM core that vblank
 * पूर्णांकerrupts are working. Since these helpers करोn't स्वतःmatically clean up the
 * requested पूर्णांकerrupt like e.g. devm_request_irq() they're not really
 * recommended.
 */

/**
 * drm_irq_install - install IRQ handler
 * @dev: DRM device
 * @irq: IRQ number to install the handler क्रम
 *
 * Initializes the IRQ related data. Installs the handler, calling the driver
 * &drm_driver.irq_preinstall and &drm_driver.irq_postinstall functions beक्रमe
 * and after the installation.
 *
 * This is the simplअगरied helper पूर्णांकerface provided क्रम drivers with no special
 * needs. Drivers which need to install पूर्णांकerrupt handlers क्रम multiple
 * पूर्णांकerrupts must instead set &drm_device.irq_enabled to संकेत the DRM core
 * that vblank पूर्णांकerrupts are available.
 *
 * @irq must match the पूर्णांकerrupt number that would be passed to request_irq(),
 * अगर called directly instead of using this helper function.
 *
 * &drm_driver.irq_handler is called to handle the रेजिस्टरed पूर्णांकerrupt.
 *
 * Returns:
 * Zero on success or a negative error code on failure.
 */
पूर्णांक drm_irq_install(काष्ठा drm_device *dev, पूर्णांक irq)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ sh_flags = 0;

	अगर (irq == 0)
		वापस -EINVAL;

	अगर (dev->irq_enabled)
		वापस -EBUSY;
	dev->irq_enabled = true;

	DRM_DEBUG("irq=%d\n", irq);

	/* Beक्रमe installing handler */
	अगर (dev->driver->irq_preinstall)
		dev->driver->irq_preinstall(dev);

	/* PCI devices require shared पूर्णांकerrupts. */
	अगर (dev_is_pci(dev->dev))
		sh_flags = IRQF_SHARED;

	ret = request_irq(irq, dev->driver->irq_handler,
			  sh_flags, dev->driver->name, dev);

	अगर (ret < 0) अणु
		dev->irq_enabled = false;
		वापस ret;
	पूर्ण

	/* After installing handler */
	अगर (dev->driver->irq_postinstall)
		ret = dev->driver->irq_postinstall(dev);

	अगर (ret < 0) अणु
		dev->irq_enabled = false;
		अगर (drm_core_check_feature(dev, DRIVER_LEGACY))
			vga_client_रेजिस्टर(to_pci_dev(dev->dev), शून्य, शून्य, शून्य);
		मुक्त_irq(irq, dev);
	पूर्ण अन्यथा अणु
		dev->irq = irq;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_irq_install);

/**
 * drm_irq_uninstall - uninstall the IRQ handler
 * @dev: DRM device
 *
 * Calls the driver's &drm_driver.irq_uninstall function and unरेजिस्टरs the IRQ
 * handler.  This should only be called by drivers which used drm_irq_install()
 * to set up their पूर्णांकerrupt handler. Other drivers must only reset
 * &drm_device.irq_enabled to false.
 *
 * Note that क्रम kernel modesetting drivers it is a bug अगर this function fails.
 * The sanity checks are only to catch buggy user modesetting drivers which call
 * the same function through an ioctl.
 *
 * Returns:
 * Zero on success or a negative error code on failure.
 */
पूर्णांक drm_irq_uninstall(काष्ठा drm_device *dev)
अणु
	अचिन्हित दीर्घ irqflags;
	bool irq_enabled;
	पूर्णांक i;

	irq_enabled = dev->irq_enabled;
	dev->irq_enabled = false;

	/*
	 * Wake up any रुकोers so they करोn't hang. This is just to paper over
	 * issues क्रम UMS drivers which aren't in full control of their
	 * vblank/irq handling. KMS drivers must ensure that vblanks are all
	 * disabled when uninstalling the irq handler.
	 */
	अगर (drm_dev_has_vblank(dev)) अणु
		spin_lock_irqsave(&dev->vbl_lock, irqflags);
		क्रम (i = 0; i < dev->num_crtcs; i++) अणु
			काष्ठा drm_vblank_crtc *vblank = &dev->vblank[i];

			अगर (!vblank->enabled)
				जारी;

			WARN_ON(drm_core_check_feature(dev, DRIVER_MODESET));

			drm_vblank_disable_and_save(dev, i);
			wake_up(&vblank->queue);
		पूर्ण
		spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
	पूर्ण

	अगर (!irq_enabled)
		वापस -EINVAL;

	DRM_DEBUG("irq=%d\n", dev->irq);

	अगर (drm_core_check_feature(dev, DRIVER_LEGACY))
		vga_client_रेजिस्टर(to_pci_dev(dev->dev), शून्य, शून्य, शून्य);

	अगर (dev->driver->irq_uninstall)
		dev->driver->irq_uninstall(dev);

	मुक्त_irq(dev->irq, dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_irq_uninstall);

अटल व्योम devm_drm_irq_uninstall(व्योम *data)
अणु
	drm_irq_uninstall(data);
पूर्ण

/**
 * devm_drm_irq_install - install IRQ handler
 * @dev: DRM device
 * @irq: IRQ number to install the handler क्रम
 *
 * devm_drm_irq_install is a  help function of drm_irq_install.
 *
 * अगर the driver uses devm_drm_irq_install, there is no need
 * to call drm_irq_uninstall when the drm module get unloaded,
 * as this will करोne स्वतःmagically.
 *
 * Returns:
 * Zero on success or a negative error code on failure.
 */
पूर्णांक devm_drm_irq_install(काष्ठा drm_device *dev, पूर्णांक irq)
अणु
	पूर्णांक ret;

	ret = drm_irq_install(dev, irq);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev->dev,
					devm_drm_irq_uninstall, dev);
पूर्ण
EXPORT_SYMBOL(devm_drm_irq_install);

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक drm_legacy_irq_control(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_control *ctl = data;
	पूर्णांक ret = 0, irq;
	काष्ठा pci_dev *pdev;

	/* अगर we haven't irq we fallback क्रम compatibility reasons -
	 * this used to be a separate function in drm_dma.h
	 */

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_IRQ))
		वापस 0;
	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस 0;
	/* UMS was only ever supported on pci devices. */
	अगर (WARN_ON(!dev_is_pci(dev->dev)))
		वापस -EINVAL;

	चयन (ctl->func) अणु
	हाल DRM_INST_HANDLER:
		pdev = to_pci_dev(dev->dev);
		irq = pdev->irq;

		अगर (dev->अगर_version < DRM_IF_VERSION(1, 2) &&
		    ctl->irq != irq)
			वापस -EINVAL;
		mutex_lock(&dev->काष्ठा_mutex);
		ret = drm_irq_install(dev, irq);
		mutex_unlock(&dev->काष्ठा_mutex);

		वापस ret;
	हाल DRM_UNINST_HANDLER:
		mutex_lock(&dev->काष्ठा_mutex);
		ret = drm_irq_uninstall(dev);
		mutex_unlock(&dev->काष्ठा_mutex);

		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
#पूर्ण_अगर
