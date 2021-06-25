<शैली गुरु>
/**************************************************************************
 * Copyright (c) 2009-2011, Intel Corporation.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Benjamin Defnet <benjamin.r.defnet@पूर्णांकel.com>
 *    Rajesh Poornachandran <rajesh.poornachandran@पूर्णांकel.com>
 * Massively reworked
 *    Alan Cox <alan@linux.पूर्णांकel.com>
 */

#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_reg.h"
#समावेश "psb_intel_reg.h"
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>

अटल काष्ठा mutex घातer_mutex;	/* Serialize घातer ops */
अटल DEFINE_SPINLOCK(घातer_ctrl_lock);	/* Serialize घातer claim */

/**
 *	gma_घातer_init		-	initialise घातer manager
 *	@dev: our device
 *
 *	Set up क्रम घातer management tracking of our hardware.
 */
व्योम gma_घातer_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	/* FIXME: Move APM/OSPM base पूर्णांकo relevant device code */
	dev_priv->apm_base = dev_priv->apm_reg & 0xffff;
	dev_priv->ospm_base &= 0xffff;

	dev_priv->display_घातer = true;	/* We start active */
	dev_priv->display_count = 0;	/* Currently no users */
	dev_priv->suspended = false;	/* And not suspended */
	mutex_init(&घातer_mutex);

	अगर (dev_priv->ops->init_pm)
		dev_priv->ops->init_pm(dev);
पूर्ण

/**
 *	gma_घातer_uninit	-	end घातer manager
 *	@dev: device to end क्रम
 *
 *	Unकरो the effects of gma_घातer_init
 */
व्योम gma_घातer_uninit(काष्ठा drm_device *dev)
अणु
	pm_runसमय_disable(dev->dev);
	pm_runसमय_set_suspended(dev->dev);
पूर्ण

/**
 *	gma_suspend_display	-	suspend the display logic
 *	@dev: our DRM device
 *
 *	Suspend the display logic of the graphics पूर्णांकerface
 */
अटल व्योम gma_suspend_display(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	अगर (dev_priv->suspended)
		वापस;
	dev_priv->ops->save_regs(dev);
	dev_priv->ops->घातer_करोwn(dev);
	dev_priv->display_घातer = false;
पूर्ण

/**
 *	gma_resume_display	-	resume display side logic
 *	@pdev: PCI device
 *
 *	Resume the display hardware restoring state and enabling
 *	as necessary.
 */
अटल व्योम gma_resume_display(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	/* turn on the display घातer island */
	dev_priv->ops->घातer_up(dev);
	dev_priv->suspended = false;
	dev_priv->display_घातer = true;

	PSB_WVDC32(dev_priv->pge_ctl | _PSB_PGETBL_ENABLED, PSB_PGETBL_CTL);
	pci_ग_लिखो_config_word(pdev, PSB_GMCH_CTRL,
			dev_priv->gmch_ctrl | _PSB_GMCH_ENABLED);

	psb_gtt_restore(dev); /* Rebuild our GTT mappings */
	dev_priv->ops->restore_regs(dev);
पूर्ण

/**
 *	gma_suspend_pci		-	suspend PCI side
 *	@pdev: PCI device
 *
 *	Perक्रमm the suspend processing on our PCI device state
 */
अटल व्योम gma_suspend_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक bsm, vbt;

	अगर (dev_priv->suspended)
		वापस;

	pci_save_state(pdev);
	pci_पढ़ो_config_dword(pdev, 0x5C, &bsm);
	dev_priv->regs.saveBSM = bsm;
	pci_पढ़ो_config_dword(pdev, 0xFC, &vbt);
	dev_priv->regs.saveVBT = vbt;
	pci_पढ़ो_config_dword(pdev, PSB_PCIx_MSI_ADDR_LOC, &dev_priv->msi_addr);
	pci_पढ़ो_config_dword(pdev, PSB_PCIx_MSI_DATA_LOC, &dev_priv->msi_data);

	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);

	dev_priv->suspended = true;
पूर्ण

/**
 *	gma_resume_pci		-	resume helper
 *	@pdev: our PCI device
 *
 *	Perक्रमm the resume processing on our PCI device state - reग_लिखो
 *	रेजिस्टर state and re-enable the PCI device
 */
अटल bool gma_resume_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret;

	अगर (!dev_priv->suspended)
		वापस true;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	pci_ग_लिखो_config_dword(pdev, 0x5c, dev_priv->regs.saveBSM);
	pci_ग_लिखो_config_dword(pdev, 0xFC, dev_priv->regs.saveVBT);
	/* restoring MSI address and data in PCIx space */
	pci_ग_लिखो_config_dword(pdev, PSB_PCIx_MSI_ADDR_LOC, dev_priv->msi_addr);
	pci_ग_लिखो_config_dword(pdev, PSB_PCIx_MSI_DATA_LOC, dev_priv->msi_data);
	ret = pci_enable_device(pdev);

	अगर (ret != 0)
		dev_err(&pdev->dev, "pci_enable failed: %d\n", ret);
	अन्यथा
		dev_priv->suspended = false;
	वापस !dev_priv->suspended;
पूर्ण

/**
 *	gma_घातer_suspend		-	bus callback क्रम suspend
 *	@_dev: our device
 *
 *	Called back by the PCI layer during a suspend of the प्रणाली. We
 *	perक्रमm the necessary shut करोwn steps and save enough state that
 *	we can unकरो this when resume is called.
 */
पूर्णांक gma_घातer_suspend(काष्ठा device *_dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(_dev);
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	mutex_lock(&घातer_mutex);
	अगर (!dev_priv->suspended) अणु
		अगर (dev_priv->display_count) अणु
			mutex_unlock(&घातer_mutex);
			dev_err(dev->dev, "GPU hardware busy, cannot suspend\n");
			वापस -EBUSY;
		पूर्ण
		psb_irq_uninstall(dev);
		gma_suspend_display(dev);
		gma_suspend_pci(pdev);
	पूर्ण
	mutex_unlock(&घातer_mutex);
	वापस 0;
पूर्ण

/**
 *	gma_घातer_resume		-	resume घातer
 *	@_dev: our device
 *
 *	Resume the PCI side of the graphics and then the displays
 */
पूर्णांक gma_घातer_resume(काष्ठा device *_dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(_dev);
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	mutex_lock(&घातer_mutex);
	gma_resume_pci(pdev);
	gma_resume_display(pdev);
	psb_irq_preinstall(dev);
	psb_irq_postinstall(dev);
	mutex_unlock(&घातer_mutex);
	वापस 0;
पूर्ण

/**
 *	gma_घातer_is_on		-	वापसe true अगर घातer is on
 *	@dev: our DRM device
 *
 *	Returns true अगर the display island घातer is on at this moment
 */
bool gma_घातer_is_on(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	वापस dev_priv->display_घातer;
पूर्ण

/**
 *	gma_घातer_begin		-	begin requiring घातer
 *	@dev: our DRM device
 *	@क्रमce_on: true to क्रमce घातer on
 *
 *	Begin an action that requires the display घातer island is enabled.
 *	We refcount the islands.
 */
bool gma_घातer_begin(काष्ठा drm_device *dev, bool क्रमce_on)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&घातer_ctrl_lock, flags);
	/* Power alपढ़ोy on ? */
	अगर (dev_priv->display_घातer) अणु
		dev_priv->display_count++;
		pm_runसमय_get(dev->dev);
		spin_unlock_irqrestore(&घातer_ctrl_lock, flags);
		वापस true;
	पूर्ण
	अगर (क्रमce_on == false)
		जाओ out_false;

	/* Ok घातer up needed */
	ret = gma_resume_pci(pdev);
	अगर (ret == 0) अणु
		psb_irq_preinstall(dev);
		psb_irq_postinstall(dev);
		pm_runसमय_get(dev->dev);
		dev_priv->display_count++;
		spin_unlock_irqrestore(&घातer_ctrl_lock, flags);
		वापस true;
	पूर्ण
out_false:
	spin_unlock_irqrestore(&घातer_ctrl_lock, flags);
	वापस false;
पूर्ण

/**
 *	gma_घातer_end		-	end use of घातer
 *	@dev: Our DRM device
 *
 *	Indicate that one of our gma_घातer_begin() requested periods when
 *	the diplay island घातer is needed has completed.
 */
व्योम gma_घातer_end(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&घातer_ctrl_lock, flags);
	dev_priv->display_count--;
	WARN_ON(dev_priv->display_count < 0);
	spin_unlock_irqrestore(&घातer_ctrl_lock, flags);
	pm_runसमय_put(dev->dev);
पूर्ण

पूर्णांक psb_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस gma_घातer_suspend(dev);
पूर्ण

पूर्णांक psb_runसमय_resume(काष्ठा device *dev)
अणु
	वापस gma_घातer_resume(dev);
पूर्ण

पूर्णांक psb_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drmdev = pci_get_drvdata(to_pci_dev(dev));
	काष्ठा drm_psb_निजी *dev_priv = drmdev->dev_निजी;
	अगर (dev_priv->display_count)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

पूर्णांक gma_घातer_thaw(काष्ठा device *_dev)
अणु
	वापस gma_घातer_resume(_dev);
पूर्ण

पूर्णांक gma_घातer_मुक्तze(काष्ठा device *_dev)
अणु
	वापस gma_घातer_suspend(_dev);
पूर्ण

पूर्णांक gma_घातer_restore(काष्ठा device *_dev)
अणु
	वापस gma_घातer_resume(_dev);
पूर्ण
