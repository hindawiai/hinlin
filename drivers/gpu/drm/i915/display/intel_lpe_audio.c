<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Pierre-Louis Bossart <pierre-louis.bossart@linux.पूर्णांकel.com>
 *    Jerome Anand <jerome.anand@पूर्णांकel.com>
 *    based on VED patches
 *
 */

/**
 * DOC: LPE Audio पूर्णांकegration क्रम HDMI or DP playback
 *
 * Motivation:
 * Atom platक्रमms (e.g. valleyview and cherryTrail) पूर्णांकegrates a DMA-based
 * पूर्णांकerface as an alternative to the traditional HDaudio path. While this
 * mode is unrelated to the LPE aka SST audio engine, the करोcumentation refers
 * to this mode as LPE so we keep this notation क्रम the sake of consistency.
 *
 * The पूर्णांकerface is handled by a separate standalone driver मुख्यtained in the
 * ALSA subप्रणाली क्रम simplicity. To minimize the पूर्णांकeraction between the two
 * subप्रणालीs, a bridge is setup between the hdmi-lpe-audio and i915:
 * 1. Create a platक्रमm device to share MMIO/IRQ resources
 * 2. Make the platक्रमm device child of i915 device क्रम runसमय PM.
 * 3. Create IRQ chip to क्रमward the LPE audio irqs.
 * the hdmi-lpe-audio driver probes the lpe audio device and creates a new
 * sound card
 *
 * Threats:
 * Due to the restriction in Linux platक्रमm device model, user need manually
 * uninstall the hdmi-lpe-audio driver beक्रमe uninstalling i915 module,
 * otherwise we might run पूर्णांकo use-after-मुक्त issues after i915 हटाओs the
 * platक्रमm device: even though hdmi-lpe-audio driver is released, the modules
 * is still in "installed" status.
 *
 * Implementation:
 * The MMIO/REG platक्रमm resources are created according to the रेजिस्टरs
 * specअगरication.
 * When क्रमwarding LPE audio irqs, the flow control handler selection depends
 * on the platक्रमm, क्रम example on valleyview handle_simple_irq is enough.
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/पूर्णांकel_lpe_audपन.स>

#समावेश "i915_drv.h"
#समावेश "intel_de.h"
#समावेश "intel_lpe_audio.h"

#घोषणा HAS_LPE_AUDIO(dev_priv) ((dev_priv)->lpe_audio.platdev != शून्य)

अटल काष्ठा platक्रमm_device *
lpe_audio_platdev_create(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा platक्रमm_device_info pinfo = अणुपूर्ण;
	काष्ठा resource *rsc;
	काष्ठा platक्रमm_device *platdev;
	काष्ठा पूर्णांकel_hdmi_lpe_audio_pdata *pdata;

	pdata = kzalloc(माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	rsc = kसुस्मृति(2, माप(*rsc), GFP_KERNEL);
	अगर (!rsc) अणु
		kमुक्त(pdata);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rsc[0].start    = rsc[0].end = dev_priv->lpe_audio.irq;
	rsc[0].flags    = IORESOURCE_IRQ;
	rsc[0].name     = "hdmi-lpe-audio-irq";

	rsc[1].start    = pci_resource_start(pdev, 0) +
		I915_HDMI_LPE_AUDIO_BASE;
	rsc[1].end      = pci_resource_start(pdev, 0) +
		I915_HDMI_LPE_AUDIO_BASE + I915_HDMI_LPE_AUDIO_SIZE - 1;
	rsc[1].flags    = IORESOURCE_MEM;
	rsc[1].name     = "hdmi-lpe-audio-mmio";

	pinfo.parent = dev->dev;
	pinfo.name = "hdmi-lpe-audio";
	pinfo.id = -1;
	pinfo.res = rsc;
	pinfo.num_res = 2;
	pinfo.data = pdata;
	pinfo.size_data = माप(*pdata);
	pinfo.dma_mask = DMA_BIT_MASK(32);

	pdata->num_pipes = INTEL_NUM_PIPES(dev_priv);
	pdata->num_ports = IS_CHERRYVIEW(dev_priv) ? 3 : 2; /* B,C,D or B,C */
	pdata->port[0].pipe = -1;
	pdata->port[1].pipe = -1;
	pdata->port[2].pipe = -1;
	spin_lock_init(&pdata->lpe_audio_slock);

	platdev = platक्रमm_device_रेजिस्टर_full(&pinfo);
	kमुक्त(rsc);
	kमुक्त(pdata);

	अगर (IS_ERR(platdev)) अणु
		drm_err(&dev_priv->drm,
			"Failed to allocate LPE audio platform device\n");
		वापस platdev;
	पूर्ण

	pm_runसमय_no_callbacks(&platdev->dev);

	वापस platdev;
पूर्ण

अटल व्योम lpe_audio_platdev_destroy(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* XXX Note that platक्रमm_device_रेजिस्टर_full() allocates a dma_mask
	 * and never मुक्तs it. We can't मुक्त it here as we cannot guarantee
	 * this is the last reference (i.e. that the dma_mask will not be
	 * used after our unरेजिस्टर). So ee choose to leak the माप(u64)
	 * allocation here - it should be fixed in the platक्रमm_device rather
	 * than us fiddle with its पूर्णांकernals.
	 */

	platक्रमm_device_unरेजिस्टर(dev_priv->lpe_audio.platdev);
पूर्ण

अटल व्योम lpe_audio_irq_unmask(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम lpe_audio_irq_mask(काष्ठा irq_data *d)
अणु
पूर्ण

अटल काष्ठा irq_chip lpe_audio_irqchip = अणु
	.name = "hdmi_lpe_audio_irqchip",
	.irq_mask = lpe_audio_irq_mask,
	.irq_unmask = lpe_audio_irq_unmask,
पूर्ण;

अटल पूर्णांक lpe_audio_irq_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक irq = dev_priv->lpe_audio.irq;

	drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv));
	irq_set_chip_and_handler_name(irq,
				&lpe_audio_irqchip,
				handle_simple_irq,
				"hdmi_lpe_audio_irq_handler");

	वापस irq_set_chip_data(irq, dev_priv);
पूर्ण

अटल bool lpe_audio_detect(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक lpe_present = false;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		अटल स्थिर काष्ठा pci_device_id atom_hdaudio_ids[] = अणु
			/* Baytrail */
			अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x0f04)पूर्ण,
			/* Braswell */
			अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2284)पूर्ण,
			अणुपूर्ण
		पूर्ण;

		अगर (!pci_dev_present(atom_hdaudio_ids)) अणु
			drm_info(&dev_priv->drm,
				 "HDaudio controller not detected, using LPE audio instead\n");
			lpe_present = true;
		पूर्ण
	पूर्ण
	वापस lpe_present;
पूर्ण

अटल पूर्णांक lpe_audio_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	dev_priv->lpe_audio.irq = irq_alloc_desc(0);
	अगर (dev_priv->lpe_audio.irq < 0) अणु
		drm_err(&dev_priv->drm, "Failed to allocate IRQ desc: %d\n",
			dev_priv->lpe_audio.irq);
		ret = dev_priv->lpe_audio.irq;
		जाओ err;
	पूर्ण

	drm_dbg(&dev_priv->drm, "irq = %d\n", dev_priv->lpe_audio.irq);

	ret = lpe_audio_irq_init(dev_priv);

	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Failed to initialize irqchip for lpe audio: %d\n",
			ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	dev_priv->lpe_audio.platdev = lpe_audio_platdev_create(dev_priv);

	अगर (IS_ERR(dev_priv->lpe_audio.platdev)) अणु
		ret = PTR_ERR(dev_priv->lpe_audio.platdev);
		drm_err(&dev_priv->drm,
			"Failed to create lpe audio platform device: %d\n",
			ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	/* enable chicken bit; at least this is required क्रम Dell Wyse 3040
	 * with DP outमाला_दो (but only someबार by some reason!)
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_AUD_CHICKEN_BIT_REG,
		       VLV_CHICKEN_BIT_DBG_ENABLE);

	वापस 0;
err_मुक्त_irq:
	irq_मुक्त_desc(dev_priv->lpe_audio.irq);
err:
	dev_priv->lpe_audio.irq = -1;
	dev_priv->lpe_audio.platdev = शून्य;
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_lpe_audio_irq_handler() - क्रमwards the LPE audio irq
 * @dev_priv: the i915 drm device निजी data
 *
 * the LPE Audio irq is क्रमwarded to the irq handler रेजिस्टरed by LPE audio
 * driver.
 */
व्योम पूर्णांकel_lpe_audio_irq_handler(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (!HAS_LPE_AUDIO(dev_priv))
		वापस;

	ret = generic_handle_irq(dev_priv->lpe_audio.irq);
	अगर (ret)
		drm_err_ratelimited(&dev_priv->drm,
				    "error handling LPE audio irq: %d\n", ret);
पूर्ण

/**
 * पूर्णांकel_lpe_audio_init() - detect and setup the bridge between HDMI LPE Audio
 * driver and i915
 * @dev_priv: the i915 drm device निजी data
 *
 * Return: 0 अगर successful. non-zero अगर detection or
 * llocation/initialization fails
 */
पूर्णांक पूर्णांकel_lpe_audio_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (lpe_audio_detect(dev_priv)) अणु
		ret = lpe_audio_setup(dev_priv);
		अगर (ret < 0)
			drm_err(&dev_priv->drm,
				"failed to setup LPE Audio bridge\n");
	पूर्ण
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_lpe_audio_tearकरोwn() - destroy the bridge between HDMI LPE
 * audio driver and i915
 * @dev_priv: the i915 drm device निजी data
 *
 * release all the resources क्रम LPE audio <-> i915 bridge.
 */
व्योम पूर्णांकel_lpe_audio_tearकरोwn(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_LPE_AUDIO(dev_priv))
		वापस;

	lpe_audio_platdev_destroy(dev_priv);

	irq_मुक्त_desc(dev_priv->lpe_audio.irq);

	dev_priv->lpe_audio.irq = -1;
	dev_priv->lpe_audio.platdev = शून्य;
पूर्ण

/**
 * पूर्णांकel_lpe_audio_notअगरy() - notअगरy lpe audio event
 * audio driver and i915
 * @dev_priv: the i915 drm device निजी data
 * @pipe: pipe
 * @port: port
 * @eld : ELD data
 * @ls_घड़ी: Link symbol घड़ी in kHz
 * @dp_output: Driving a DP output?
 *
 * Notअगरy lpe audio driver of eld change.
 */
व्योम पूर्णांकel_lpe_audio_notअगरy(काष्ठा drm_i915_निजी *dev_priv,
			    क्रमागत pipe pipe, क्रमागत port port,
			    स्थिर व्योम *eld, पूर्णांक ls_घड़ी, bool dp_output)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा पूर्णांकel_hdmi_lpe_audio_pdata *pdata;
	काष्ठा पूर्णांकel_hdmi_lpe_audio_port_pdata *ppdata;
	u32 audio_enable;

	अगर (!HAS_LPE_AUDIO(dev_priv))
		वापस;

	pdata = dev_get_platdata(&dev_priv->lpe_audio.platdev->dev);
	ppdata = &pdata->port[port - PORT_B];

	spin_lock_irqsave(&pdata->lpe_audio_slock, irqflags);

	audio_enable = पूर्णांकel_de_पढ़ो(dev_priv, VLV_AUD_PORT_EN_DBG(port));

	अगर (eld != शून्य) अणु
		स_नकल(ppdata->eld, eld, HDMI_MAX_ELD_BYTES);
		ppdata->pipe = pipe;
		ppdata->ls_घड़ी = ls_घड़ी;
		ppdata->dp_output = dp_output;

		/* Unmute the amp क्रम both DP and HDMI */
		पूर्णांकel_de_ग_लिखो(dev_priv, VLV_AUD_PORT_EN_DBG(port),
			       audio_enable & ~VLV_AMP_MUTE);
	पूर्ण अन्यथा अणु
		स_रखो(ppdata->eld, 0, HDMI_MAX_ELD_BYTES);
		ppdata->pipe = -1;
		ppdata->ls_घड़ी = 0;
		ppdata->dp_output = false;

		/* Mute the amp क्रम both DP and HDMI */
		पूर्णांकel_de_ग_लिखो(dev_priv, VLV_AUD_PORT_EN_DBG(port),
			       audio_enable | VLV_AMP_MUTE);
	पूर्ण

	अगर (pdata->notअगरy_audio_lpe)
		pdata->notअगरy_audio_lpe(dev_priv->lpe_audio.platdev, port - PORT_B);

	spin_unlock_irqrestore(&pdata->lpe_audio_slock, irqflags);
पूर्ण
