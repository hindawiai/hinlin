<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * platक्रमm.c - DesignWare HS OTG Controller platक्रमm driver
 *
 * Copyright (C) Matthijs Kooijman <matthijs@मानक_निवेश.nl>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_data/s3c-hsotg.h>
#समावेश <linux/reset.h>

#समावेश <linux/usb/of.h>

#समावेश "core.h"
#समावेश "hcd.h"
#समावेश "debug.h"

अटल स्थिर अक्षर dwc2_driver_name[] = "dwc2";

/*
 * Check the dr_mode against the module configuration and hardware
 * capabilities.
 *
 * The hardware, module, and dr_mode, can each be set to host, device,
 * or otg. Check that all these values are compatible and adjust the
 * value of dr_mode अगर possible.
 *
 *                      actual
 *    HW  MOD dr_mode   dr_mode
 *  ------------------------------
 *   HST  HST  any    :  HST
 *   HST  DEV  any    :  ---
 *   HST  OTG  any    :  HST
 *
 *   DEV  HST  any    :  ---
 *   DEV  DEV  any    :  DEV
 *   DEV  OTG  any    :  DEV
 *
 *   OTG  HST  any    :  HST
 *   OTG  DEV  any    :  DEV
 *   OTG  OTG  any    :  dr_mode
 */
अटल पूर्णांक dwc2_get_dr_mode(काष्ठा dwc2_hsotg *hsotg)
अणु
	क्रमागत usb_dr_mode mode;

	hsotg->dr_mode = usb_get_dr_mode(hsotg->dev);
	अगर (hsotg->dr_mode == USB_DR_MODE_UNKNOWN)
		hsotg->dr_mode = USB_DR_MODE_OTG;

	mode = hsotg->dr_mode;

	अगर (dwc2_hw_is_device(hsotg)) अणु
		अगर (IS_ENABLED(CONFIG_USB_DWC2_HOST)) अणु
			dev_err(hsotg->dev,
				"Controller does not support host mode.\n");
			वापस -EINVAL;
		पूर्ण
		mode = USB_DR_MODE_PERIPHERAL;
	पूर्ण अन्यथा अगर (dwc2_hw_is_host(hsotg)) अणु
		अगर (IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL)) अणु
			dev_err(hsotg->dev,
				"Controller does not support device mode.\n");
			वापस -EINVAL;
		पूर्ण
		mode = USB_DR_MODE_HOST;
	पूर्ण अन्यथा अणु
		अगर (IS_ENABLED(CONFIG_USB_DWC2_HOST))
			mode = USB_DR_MODE_HOST;
		अन्यथा अगर (IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL))
			mode = USB_DR_MODE_PERIPHERAL;
	पूर्ण

	अगर (mode != hsotg->dr_mode) अणु
		dev_warn(hsotg->dev,
			 "Configuration mismatch. dr_mode forced to %s\n",
			mode == USB_DR_MODE_HOST ? "host" : "device");

		hsotg->dr_mode = mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __dwc2_disable_regulators(व्योम *data)
अणु
	काष्ठा dwc2_hsotg *hsotg = data;

	regulator_bulk_disable(ARRAY_SIZE(hsotg->supplies), hsotg->supplies);
पूर्ण

अटल पूर्णांक __dwc2_lowlevel_hw_enable(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(hsotg->dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(hsotg->supplies),
				    hsotg->supplies);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&pdev->dev,
				       __dwc2_disable_regulators, hsotg);
	अगर (ret)
		वापस ret;

	अगर (hsotg->clk) अणु
		ret = clk_prepare_enable(hsotg->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (hsotg->uphy) अणु
		ret = usb_phy_init(hsotg->uphy);
	पूर्ण अन्यथा अगर (hsotg->plat && hsotg->plat->phy_init) अणु
		ret = hsotg->plat->phy_init(pdev, hsotg->plat->phy_type);
	पूर्ण अन्यथा अणु
		ret = phy_घातer_on(hsotg->phy);
		अगर (ret == 0)
			ret = phy_init(hsotg->phy);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dwc2_lowlevel_hw_enable - enable platक्रमm lowlevel hw resources
 * @hsotg: The driver state
 *
 * A wrapper क्रम platक्रमm code responsible क्रम controlling
 * low-level USB platक्रमm resources (phy, घड़ी, regulators)
 */
पूर्णांक dwc2_lowlevel_hw_enable(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक ret = __dwc2_lowlevel_hw_enable(hsotg);

	अगर (ret == 0)
		hsotg->ll_hw_enabled = true;
	वापस ret;
पूर्ण

अटल पूर्णांक __dwc2_lowlevel_hw_disable(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(hsotg->dev);
	पूर्णांक ret = 0;

	अगर (hsotg->uphy) अणु
		usb_phy_shutकरोwn(hsotg->uphy);
	पूर्ण अन्यथा अगर (hsotg->plat && hsotg->plat->phy_निकास) अणु
		ret = hsotg->plat->phy_निकास(pdev, hsotg->plat->phy_type);
	पूर्ण अन्यथा अणु
		ret = phy_निकास(hsotg->phy);
		अगर (ret == 0)
			ret = phy_घातer_off(hsotg->phy);
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (hsotg->clk)
		clk_disable_unprepare(hsotg->clk);

	वापस 0;
पूर्ण

/**
 * dwc2_lowlevel_hw_disable - disable platक्रमm lowlevel hw resources
 * @hsotg: The driver state
 *
 * A wrapper क्रम platक्रमm code responsible क्रम controlling
 * low-level USB platक्रमm resources (phy, घड़ी, regulators)
 */
पूर्णांक dwc2_lowlevel_hw_disable(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक ret = __dwc2_lowlevel_hw_disable(hsotg);

	अगर (ret == 0)
		hsotg->ll_hw_enabled = false;
	वापस ret;
पूर्ण

अटल पूर्णांक dwc2_lowlevel_hw_init(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक i, ret;

	hsotg->reset = devm_reset_control_get_optional(hsotg->dev, "dwc2");
	अगर (IS_ERR(hsotg->reset)) अणु
		ret = PTR_ERR(hsotg->reset);
		dev_err(hsotg->dev, "error getting reset control %d\n", ret);
		वापस ret;
	पूर्ण

	reset_control_deनिश्चित(hsotg->reset);

	hsotg->reset_ecc = devm_reset_control_get_optional(hsotg->dev, "dwc2-ecc");
	अगर (IS_ERR(hsotg->reset_ecc)) अणु
		ret = PTR_ERR(hsotg->reset_ecc);
		dev_err(hsotg->dev, "error getting reset control for ecc %d\n", ret);
		वापस ret;
	पूर्ण

	reset_control_deनिश्चित(hsotg->reset_ecc);

	/*
	 * Attempt to find a generic PHY, then look क्रम an old style
	 * USB PHY and then fall back to pdata
	 */
	hsotg->phy = devm_phy_get(hsotg->dev, "usb2-phy");
	अगर (IS_ERR(hsotg->phy)) अणु
		ret = PTR_ERR(hsotg->phy);
		चयन (ret) अणु
		हाल -ENODEV:
		हाल -ENOSYS:
			hsotg->phy = शून्य;
			अवरोध;
		हाल -EPROBE_DEFER:
			वापस ret;
		शेष:
			dev_err(hsotg->dev, "error getting phy %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!hsotg->phy) अणु
		hsotg->uphy = devm_usb_get_phy(hsotg->dev, USB_PHY_TYPE_USB2);
		अगर (IS_ERR(hsotg->uphy)) अणु
			ret = PTR_ERR(hsotg->uphy);
			चयन (ret) अणु
			हाल -ENODEV:
			हाल -ENXIO:
				hsotg->uphy = शून्य;
				अवरोध;
			हाल -EPROBE_DEFER:
				वापस ret;
			शेष:
				dev_err(hsotg->dev, "error getting usb phy %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	hsotg->plat = dev_get_platdata(hsotg->dev);

	/* Clock */
	hsotg->clk = devm_clk_get_optional(hsotg->dev, "otg");
	अगर (IS_ERR(hsotg->clk)) अणु
		dev_err(hsotg->dev, "cannot get otg clock\n");
		वापस PTR_ERR(hsotg->clk);
	पूर्ण

	/* Regulators */
	क्रम (i = 0; i < ARRAY_SIZE(hsotg->supplies); i++)
		hsotg->supplies[i].supply = dwc2_hsotg_supply_names[i];

	ret = devm_regulator_bulk_get(hsotg->dev, ARRAY_SIZE(hsotg->supplies),
				      hsotg->supplies);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(hsotg->dev, "failed to request supplies: %d\n",
				ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dwc2_driver_हटाओ() - Called when the DWC_otg core is unरेजिस्टरed with the
 * DWC_otg driver
 *
 * @dev: Platक्रमm device
 *
 * This routine is called, क्रम example, when the rmmod command is executed. The
 * device may or may not be electrically present. If it is present, the driver
 * stops device processing. Any resources used on behalf of this device are
 * मुक्तd.
 */
अटल पूर्णांक dwc2_driver_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा dwc2_hsotg *hsotg = platक्रमm_get_drvdata(dev);
	काष्ठा dwc2_gregs_backup *gr;
	पूर्णांक ret = 0;

	gr = &hsotg->gr_backup;

	/* Exit Hibernation when driver is हटाओd. */
	अगर (hsotg->hibernated) अणु
		अगर (gr->gotgctl & GOTGCTL_CURMODE_HOST)
			ret = dwc2_निकास_hibernation(hsotg, 0, 0, 1);
		अन्यथा
			ret = dwc2_निकास_hibernation(hsotg, 0, 0, 0);

		अगर (ret)
			dev_err(hsotg->dev,
				"exit hibernation failed.\n");
	पूर्ण

	/* Exit Partial Power Down when driver is हटाओd. */
	अगर (hsotg->in_ppd) अणु
		ret = dwc2_निकास_partial_घातer_करोwn(hsotg, 0, true);
		अगर (ret)
			dev_err(hsotg->dev,
				"exit partial_power_down failed\n");
	पूर्ण

	/* Exit घड़ी gating when driver is हटाओd. */
	अगर (hsotg->params.घातer_करोwn == DWC2_POWER_DOWN_PARAM_NONE &&
	    hsotg->bus_suspended) अणु
		अगर (dwc2_is_device_mode(hsotg))
			dwc2_gadget_निकास_घड़ी_gating(hsotg, 0);
		अन्यथा
			dwc2_host_निकास_घड़ी_gating(hsotg, 0);
	पूर्ण

	dwc2_debugfs_निकास(hsotg);
	अगर (hsotg->hcd_enabled)
		dwc2_hcd_हटाओ(hsotg);
	अगर (hsotg->gadget_enabled)
		dwc2_hsotg_हटाओ(hsotg);

	dwc2_drd_निकास(hsotg);

	अगर (hsotg->params.activate_sपंचांग_id_vb_detection)
		regulator_disable(hsotg->usb33d);

	अगर (hsotg->ll_hw_enabled)
		dwc2_lowlevel_hw_disable(hsotg);

	reset_control_निश्चित(hsotg->reset);
	reset_control_निश्चित(hsotg->reset_ecc);

	वापस ret;
पूर्ण

/**
 * dwc2_driver_shutकरोwn() - Called on device shutकरोwn
 *
 * @dev: Platक्रमm device
 *
 * In specअगरic conditions (involving usb hubs) dwc2 devices can create a
 * lot of पूर्णांकerrupts, even to the poपूर्णांक of overwhelming devices running
 * at low frequencies. Some devices need to करो special घड़ी handling
 * at shutकरोwn-समय which may bring the प्रणाली घड़ी below the threshold
 * of being able to handle the dwc2 पूर्णांकerrupts. Disabling dwc2-irqs
 * prevents reboots/घातeroffs from getting stuck in such हालs.
 */
अटल व्योम dwc2_driver_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा dwc2_hsotg *hsotg = platक्रमm_get_drvdata(dev);

	dwc2_disable_global_पूर्णांकerrupts(hsotg);
	synchronize_irq(hsotg->irq);
पूर्ण

/**
 * dwc2_check_core_endianness() - Returns true अगर core and AHB have
 * opposite endianness.
 * @hsotg:	Programming view of the DWC_otg controller.
 */
अटल bool dwc2_check_core_endianness(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 snpsid;

	snpsid = ioपढ़ो32(hsotg->regs + GSNPSID);
	अगर ((snpsid & GSNPSID_ID_MASK) == DWC2_OTG_ID ||
	    (snpsid & GSNPSID_ID_MASK) == DWC2_FS_IOT_ID ||
	    (snpsid & GSNPSID_ID_MASK) == DWC2_HS_IOT_ID)
		वापस false;
	वापस true;
पूर्ण

/**
 * Check core version
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
पूर्णांक dwc2_check_core_version(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;

	/*
	 * Attempt to ensure this device is really a DWC_otg Controller.
	 * Read and verअगरy the GSNPSID रेजिस्टर contents. The value should be
	 * 0x45f4xxxx, 0x5531xxxx or 0x5532xxxx
	 */

	hw->snpsid = dwc2_पढ़ोl(hsotg, GSNPSID);
	अगर ((hw->snpsid & GSNPSID_ID_MASK) != DWC2_OTG_ID &&
	    (hw->snpsid & GSNPSID_ID_MASK) != DWC2_FS_IOT_ID &&
	    (hw->snpsid & GSNPSID_ID_MASK) != DWC2_HS_IOT_ID) अणु
		dev_err(hsotg->dev, "Bad value for GSNPSID: 0x%08x\n",
			hw->snpsid);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(hsotg->dev, "Core Release: %1x.%1x%1x%1x (snpsid=%x)\n",
		hw->snpsid >> 12 & 0xf, hw->snpsid >> 8 & 0xf,
		hw->snpsid >> 4 & 0xf, hw->snpsid & 0xf, hw->snpsid);
	वापस 0;
पूर्ण

/**
 * dwc2_driver_probe() - Called when the DWC_otg core is bound to the DWC_otg
 * driver
 *
 * @dev: Platक्रमm device
 *
 * This routine creates the driver components required to control the device
 * (core, HCD, and PCD) and initializes the device. The driver components are
 * stored in a dwc2_hsotg काष्ठाure. A reference to the dwc2_hsotg is saved
 * in the device निजी data. This allows the driver to access the dwc2_hsotg
 * काष्ठाure on subsequent calls to driver methods क्रम this device.
 */
अटल पूर्णांक dwc2_driver_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा dwc2_hsotg *hsotg;
	काष्ठा resource *res;
	पूर्णांक retval;

	hsotg = devm_kzalloc(&dev->dev, माप(*hsotg), GFP_KERNEL);
	अगर (!hsotg)
		वापस -ENOMEM;

	hsotg->dev = &dev->dev;

	/*
	 * Use reasonable शेषs so platक्रमms करोn't have to provide these.
	 */
	अगर (!dev->dev.dma_mask)
		dev->dev.dma_mask = &dev->dev.coherent_dma_mask;
	retval = dma_set_coherent_mask(&dev->dev, DMA_BIT_MASK(32));
	अगर (retval) अणु
		dev_err(&dev->dev, "can't set coherent DMA mask: %d\n", retval);
		वापस retval;
	पूर्ण

	hsotg->regs = devm_platक्रमm_get_and_ioremap_resource(dev, 0, &res);
	अगर (IS_ERR(hsotg->regs))
		वापस PTR_ERR(hsotg->regs);

	dev_dbg(&dev->dev, "mapped PA %08lx to VA %p\n",
		(अचिन्हित दीर्घ)res->start, hsotg->regs);

	retval = dwc2_lowlevel_hw_init(hsotg);
	अगर (retval)
		वापस retval;

	spin_lock_init(&hsotg->lock);

	hsotg->irq = platक्रमm_get_irq(dev, 0);
	अगर (hsotg->irq < 0)
		वापस hsotg->irq;

	dev_dbg(hsotg->dev, "registering common handler for irq%d\n",
		hsotg->irq);
	retval = devm_request_irq(hsotg->dev, hsotg->irq,
				  dwc2_handle_common_पूर्णांकr, IRQF_SHARED,
				  dev_name(hsotg->dev), hsotg);
	अगर (retval)
		वापस retval;

	hsotg->vbus_supply = devm_regulator_get_optional(hsotg->dev, "vbus");
	अगर (IS_ERR(hsotg->vbus_supply)) अणु
		retval = PTR_ERR(hsotg->vbus_supply);
		hsotg->vbus_supply = शून्य;
		अगर (retval != -ENODEV)
			वापस retval;
	पूर्ण

	retval = dwc2_lowlevel_hw_enable(hsotg);
	अगर (retval)
		वापस retval;

	hsotg->needs_byte_swap = dwc2_check_core_endianness(hsotg);

	retval = dwc2_get_dr_mode(hsotg);
	अगर (retval)
		जाओ error;

	hsotg->need_phy_क्रम_wake =
		of_property_पढ़ो_bool(dev->dev.of_node,
				      "snps,need-phy-for-wake");

	/*
	 * Beक्रमe perक्रमming any core related operations
	 * check core version.
	 */
	retval = dwc2_check_core_version(hsotg);
	अगर (retval)
		जाओ error;

	/*
	 * Reset beक्रमe dwc2_get_hwparams() then it could get घातer-on real
	 * reset value क्रमm रेजिस्टरs.
	 */
	retval = dwc2_core_reset(hsotg, false);
	अगर (retval)
		जाओ error;

	/* Detect config values from hardware */
	retval = dwc2_get_hwparams(hsotg);
	अगर (retval)
		जाओ error;

	/*
	 * For OTG cores, set the क्रमce mode bits to reflect the value
	 * of dr_mode. Force mode bits should not be touched at any
	 * other समय after this.
	 */
	dwc2_क्रमce_dr_mode(hsotg);

	retval = dwc2_init_params(hsotg);
	अगर (retval)
		जाओ error;

	अगर (hsotg->params.activate_sपंचांग_id_vb_detection) अणु
		u32 ggpio;

		hsotg->usb33d = devm_regulator_get(hsotg->dev, "usb33d");
		अगर (IS_ERR(hsotg->usb33d)) अणु
			retval = PTR_ERR(hsotg->usb33d);
			अगर (retval != -EPROBE_DEFER)
				dev_err(hsotg->dev,
					"failed to request usb33d supply: %d\n",
					retval);
			जाओ error;
		पूर्ण
		retval = regulator_enable(hsotg->usb33d);
		अगर (retval) अणु
			dev_err(hsotg->dev,
				"failed to enable usb33d supply: %d\n", retval);
			जाओ error;
		पूर्ण

		ggpio = dwc2_पढ़ोl(hsotg, GGPIO);
		ggpio |= GGPIO_STM32_OTG_GCCFG_IDEN;
		ggpio |= GGPIO_STM32_OTG_GCCFG_VBDEN;
		dwc2_ग_लिखोl(hsotg, ggpio, GGPIO);
	पूर्ण

	retval = dwc2_drd_init(hsotg);
	अगर (retval) अणु
		अगर (retval != -EPROBE_DEFER)
			dev_err(hsotg->dev, "failed to initialize dual-role\n");
		जाओ error_init;
	पूर्ण

	अगर (hsotg->dr_mode != USB_DR_MODE_HOST) अणु
		retval = dwc2_gadget_init(hsotg);
		अगर (retval)
			जाओ error_drd;
		hsotg->gadget_enabled = 1;
	पूर्ण

	/*
	 * If we need PHY क्रम wakeup we must be wakeup capable.
	 * When we have a device that can wake without the PHY we
	 * can adjust this condition.
	 */
	अगर (hsotg->need_phy_क्रम_wake)
		device_set_wakeup_capable(&dev->dev, true);

	hsotg->reset_phy_on_wake =
		of_property_पढ़ो_bool(dev->dev.of_node,
				      "snps,reset-phy-on-wake");
	अगर (hsotg->reset_phy_on_wake && !hsotg->phy) अणु
		dev_warn(hsotg->dev,
			 "Quirk reset-phy-on-wake only supports generic PHYs\n");
		hsotg->reset_phy_on_wake = false;
	पूर्ण

	अगर (hsotg->dr_mode != USB_DR_MODE_PERIPHERAL) अणु
		retval = dwc2_hcd_init(hsotg);
		अगर (retval) अणु
			अगर (hsotg->gadget_enabled)
				dwc2_hsotg_हटाओ(hsotg);
			जाओ error_drd;
		पूर्ण
		hsotg->hcd_enabled = 1;
	पूर्ण

	platक्रमm_set_drvdata(dev, hsotg);
	hsotg->hibernated = 0;

	dwc2_debugfs_init(hsotg);

	/* Gadget code manages lowlevel hw on its own */
	अगर (hsotg->dr_mode == USB_DR_MODE_PERIPHERAL)
		dwc2_lowlevel_hw_disable(hsotg);

#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
	/* Postponed adding a new gadget to the udc class driver list */
	अगर (hsotg->gadget_enabled) अणु
		retval = usb_add_gadget_udc(hsotg->dev, &hsotg->gadget);
		अगर (retval) अणु
			hsotg->gadget.udc = शून्य;
			dwc2_hsotg_हटाओ(hsotg);
			जाओ error_debugfs;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_USB_DWC2_PERIPHERAL || CONFIG_USB_DWC2_DUAL_ROLE */
	वापस 0;

#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
error_debugfs:
	dwc2_debugfs_निकास(hsotg);
	अगर (hsotg->hcd_enabled)
		dwc2_hcd_हटाओ(hsotg);
#पूर्ण_अगर
error_drd:
	dwc2_drd_निकास(hsotg);

error_init:
	अगर (hsotg->params.activate_sपंचांग_id_vb_detection)
		regulator_disable(hsotg->usb33d);
error:
	अगर (hsotg->dr_mode != USB_DR_MODE_PERIPHERAL)
		dwc2_lowlevel_hw_disable(hsotg);
	वापस retval;
पूर्ण

अटल पूर्णांक __maybe_unused dwc2_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc2_hsotg *dwc2 = dev_get_drvdata(dev);
	bool is_device_mode = dwc2_is_device_mode(dwc2);
	पूर्णांक ret = 0;

	अगर (is_device_mode)
		dwc2_hsotg_suspend(dwc2);

	dwc2_drd_suspend(dwc2);

	अगर (dwc2->params.activate_sपंचांग_id_vb_detection) अणु
		अचिन्हित दीर्घ flags;
		u32 ggpio, gotgctl;

		/*
		 * Need to क्रमce the mode to the current mode to aव्योम Mode
		 * Mismatch Interrupt when ID detection will be disabled.
		 */
		dwc2_क्रमce_mode(dwc2, !is_device_mode);

		spin_lock_irqsave(&dwc2->lock, flags);
		gotgctl = dwc2_पढ़ोl(dwc2, GOTGCTL);
		/* bypass debounce filter, enable overrides */
		gotgctl |= GOTGCTL_DBNCE_FLTR_BYPASS;
		gotgctl |= GOTGCTL_BVALOEN | GOTGCTL_AVALOEN;
		/* Force A / B session अगर needed */
		अगर (gotgctl & GOTGCTL_ASESVLD)
			gotgctl |= GOTGCTL_AVALOVAL;
		अगर (gotgctl & GOTGCTL_BSESVLD)
			gotgctl |= GOTGCTL_BVALOVAL;
		dwc2_ग_लिखोl(dwc2, gotgctl, GOTGCTL);
		spin_unlock_irqrestore(&dwc2->lock, flags);

		ggpio = dwc2_पढ़ोl(dwc2, GGPIO);
		ggpio &= ~GGPIO_STM32_OTG_GCCFG_IDEN;
		ggpio &= ~GGPIO_STM32_OTG_GCCFG_VBDEN;
		dwc2_ग_लिखोl(dwc2, ggpio, GGPIO);

		regulator_disable(dwc2->usb33d);
	पूर्ण

	अगर (dwc2->ll_hw_enabled &&
	    (is_device_mode || dwc2_host_can_घातeroff_phy(dwc2))) अणु
		ret = __dwc2_lowlevel_hw_disable(dwc2);
		dwc2->phy_off_क्रम_suspend = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused dwc2_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc2_hsotg *dwc2 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (dwc2->phy_off_क्रम_suspend && dwc2->ll_hw_enabled) अणु
		ret = __dwc2_lowlevel_hw_enable(dwc2);
		अगर (ret)
			वापस ret;
	पूर्ण
	dwc2->phy_off_क्रम_suspend = false;

	अगर (dwc2->params.activate_sपंचांग_id_vb_detection) अणु
		अचिन्हित दीर्घ flags;
		u32 ggpio, gotgctl;

		ret = regulator_enable(dwc2->usb33d);
		अगर (ret)
			वापस ret;

		ggpio = dwc2_पढ़ोl(dwc2, GGPIO);
		ggpio |= GGPIO_STM32_OTG_GCCFG_IDEN;
		ggpio |= GGPIO_STM32_OTG_GCCFG_VBDEN;
		dwc2_ग_लिखोl(dwc2, ggpio, GGPIO);

		/* ID/VBUS detection startup समय */
		usleep_range(5000, 7000);

		spin_lock_irqsave(&dwc2->lock, flags);
		gotgctl = dwc2_पढ़ोl(dwc2, GOTGCTL);
		gotgctl &= ~GOTGCTL_DBNCE_FLTR_BYPASS;
		gotgctl &= ~(GOTGCTL_BVALOEN | GOTGCTL_AVALOEN |
			     GOTGCTL_BVALOVAL | GOTGCTL_AVALOVAL);
		dwc2_ग_लिखोl(dwc2, gotgctl, GOTGCTL);
		spin_unlock_irqrestore(&dwc2->lock, flags);
	पूर्ण

	/* Need to restore FORCEDEVMODE/FORCEHOSTMODE */
	dwc2_क्रमce_dr_mode(dwc2);

	dwc2_drd_resume(dwc2);

	अगर (dwc2_is_device_mode(dwc2))
		ret = dwc2_hsotg_resume(dwc2);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc2_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc2_suspend, dwc2_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver dwc2_platक्रमm_driver = अणु
	.driver = अणु
		.name = dwc2_driver_name,
		.of_match_table = dwc2_of_match_table,
		.acpi_match_table = ACPI_PTR(dwc2_acpi_match),
		.pm = &dwc2_dev_pm_ops,
	पूर्ण,
	.probe = dwc2_driver_probe,
	.हटाओ = dwc2_driver_हटाओ,
	.shutकरोwn = dwc2_driver_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(dwc2_platक्रमm_driver);
