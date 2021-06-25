<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl.c - Implementation of ASoC Intel SKL HD Audio driver
 *
 *  Copyright (C) 2014-2015 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *
 *  Derived mostly from Intel HDA driver with following copyrights:
 *  Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 *                     PeiSen Hou <pshou@realtek.com.tw>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_i915.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/पूर्णांकel-nhlt.h>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश "skl.h"
#समावेश "skl-sst-dsp.h"
#समावेश "skl-sst-ipc.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC)
#समावेश "../../../soc/codecs/hdac_hda.h"
#पूर्ण_अगर
अटल पूर्णांक skl_pci_binding;
module_param_named(pci_binding, skl_pci_binding, पूर्णांक, 0444);
MODULE_PARM_DESC(pci_binding, "PCI binding (0=auto, 1=only legacy, 2=only asoc");

/*
 * initialize the PCI रेजिस्टरs
 */
अटल व्योम skl_update_pci_byte(काष्ठा pci_dev *pci, अचिन्हित पूर्णांक reg,
			    अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर data;

	pci_पढ़ो_config_byte(pci, reg, &data);
	data &= ~mask;
	data |= (val & mask);
	pci_ग_लिखो_config_byte(pci, reg, data);
पूर्ण

अटल व्योम skl_init_pci(काष्ठा skl_dev *skl)
अणु
	काष्ठा hdac_bus *bus = skl_to_bus(skl);

	/*
	 * Clear bits 0-2 of PCI रेजिस्टर TCSEL (at offset 0x44)
	 * TCSEL == Traffic Class Select Register, which sets PCI express QOS
	 * Ensuring these bits are 0 clears playback अटल on some HD Audio
	 * codecs.
	 * The PCI रेजिस्टर TCSEL is defined in the Intel manuals.
	 */
	dev_dbg(bus->dev, "Clearing TCSEL\n");
	skl_update_pci_byte(skl->pci, AZX_PCIREG_TCSEL, 0x07, 0);
पूर्ण

अटल व्योम update_pci_dword(काष्ठा pci_dev *pci,
			अचिन्हित पूर्णांक reg, u32 mask, u32 val)
अणु
	u32 data = 0;

	pci_पढ़ो_config_dword(pci, reg, &data);
	data &= ~mask;
	data |= (val & mask);
	pci_ग_लिखो_config_dword(pci, reg, data);
पूर्ण

/*
 * skl_enable_miscbdcge - enable/dsiable CGCTL.MISCBDCGE bits
 *
 * @dev: device poपूर्णांकer
 * @enable: enable/disable flag
 */
अटल व्योम skl_enable_miscbdcge(काष्ठा device *dev, bool enable)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	u32 val;

	val = enable ? AZX_CGCTL_MISCBDCGE_MASK : 0;

	update_pci_dword(pci, AZX_PCIREG_CGCTL, AZX_CGCTL_MISCBDCGE_MASK, val);
पूर्ण

/**
 * skl_घड़ी_घातer_gating: Enable/Disable घड़ी and घातer gating
 *
 * @dev: Device poपूर्णांकer
 * @enable: Enable/Disable flag
 */
अटल व्योम skl_घड़ी_घातer_gating(काष्ठा device *dev, bool enable)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	u32 val;

	/* Update PDCGE bit of CGCTL रेजिस्टर */
	val = enable ? AZX_CGCTL_ADSPDCGE : 0;
	update_pci_dword(pci, AZX_PCIREG_CGCTL, AZX_CGCTL_ADSPDCGE, val);

	/* Update L1SEN bit of EM2 रेजिस्टर */
	val = enable ? AZX_REG_VS_EM2_L1SEN : 0;
	snd_hdac_chip_updatel(bus, VS_EM2, AZX_REG_VS_EM2_L1SEN, val);

	/* Update ADSPPGD bit of PGCTL रेजिस्टर */
	val = enable ? 0 : AZX_PGCTL_ADSPPGD;
	update_pci_dword(pci, AZX_PCIREG_PGCTL, AZX_PGCTL_ADSPPGD, val);
पूर्ण

/*
 * While perक्रमming reset, controller may not come back properly causing
 * issues, so recommendation is to set CGCTL.MISCBDCGE to 0 then करो reset
 * (init chip) and then again set CGCTL.MISCBDCGE to 1
 */
अटल पूर्णांक skl_init_chip(काष्ठा hdac_bus *bus, bool full_reset)
अणु
	काष्ठा hdac_ext_link *hlink;
	पूर्णांक ret;

	snd_hdac_set_codec_wakeup(bus, true);
	skl_enable_miscbdcge(bus->dev, false);
	ret = snd_hdac_bus_init_chip(bus, full_reset);

	/* Reset stream-to-link mapping */
	list_क्रम_each_entry(hlink, &bus->hlink_list, list)
		ग_लिखोl(0, hlink->ml_addr + AZX_REG_ML_LOSIDV);

	skl_enable_miscbdcge(bus->dev, true);
	snd_hdac_set_codec_wakeup(bus, false);

	वापस ret;
पूर्ण

व्योम skl_update_d0i3c(काष्ठा device *dev, bool enable)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	u8 reg;
	पूर्णांक समयout = 50;

	reg = snd_hdac_chip_पढ़ोb(bus, VS_D0I3C);
	/* Do not ग_लिखो to D0I3C until command in progress bit is cleared */
	जबतक ((reg & AZX_REG_VS_D0I3C_CIP) && --समयout) अणु
		udelay(10);
		reg = snd_hdac_chip_पढ़ोb(bus, VS_D0I3C);
	पूर्ण

	/* Highly unlikely. But अगर it happens, flag error explicitly */
	अगर (!समयout) अणु
		dev_err(bus->dev, "Before D0I3C update: D0I3C CIP timeout\n");
		वापस;
	पूर्ण

	अगर (enable)
		reg = reg | AZX_REG_VS_D0I3C_I3;
	अन्यथा
		reg = reg & (~AZX_REG_VS_D0I3C_I3);

	snd_hdac_chip_ग_लिखोb(bus, VS_D0I3C, reg);

	समयout = 50;
	/* Wait क्रम cmd in progress to be cleared beक्रमe निकासing the function */
	reg = snd_hdac_chip_पढ़ोb(bus, VS_D0I3C);
	जबतक ((reg & AZX_REG_VS_D0I3C_CIP) && --समयout) अणु
		udelay(10);
		reg = snd_hdac_chip_पढ़ोb(bus, VS_D0I3C);
	पूर्ण

	/* Highly unlikely. But अगर it happens, flag error explicitly */
	अगर (!समयout) अणु
		dev_err(bus->dev, "After D0I3C update: D0I3C CIP timeout\n");
		वापस;
	पूर्ण

	dev_dbg(bus->dev, "D0I3C register = 0x%x\n",
			snd_hdac_chip_पढ़ोb(bus, VS_D0I3C));
पूर्ण

/**
 * skl_dum_set - set DUM bit in EM2 रेजिस्टर
 * @bus: HD-audio core bus
 *
 * Addresses incorrect position reporting क्रम capture streams.
 * Used on device घातer up.
 */
अटल व्योम skl_dum_set(काष्ठा hdac_bus *bus)
अणु
	/* For the DUM bit to be set, CRST needs to be out of reset state */
	अगर (!(snd_hdac_chip_पढ़ोb(bus, GCTL) & AZX_GCTL_RESET)) अणु
		skl_enable_miscbdcge(bus->dev, false);
		snd_hdac_bus_निकास_link_reset(bus);
		skl_enable_miscbdcge(bus->dev, true);
	पूर्ण

	snd_hdac_chip_updatel(bus, VS_EM2, AZX_VS_EM2_DUM, AZX_VS_EM2_DUM);
पूर्ण

/* called from IRQ */
अटल व्योम skl_stream_update(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *hstr)
अणु
	snd_pcm_period_elapsed(hstr->substream);
पूर्ण

अटल irqवापस_t skl_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hdac_bus *bus = dev_id;
	u32 status;

	अगर (!pm_runसमय_active(bus->dev))
		वापस IRQ_NONE;

	spin_lock(&bus->reg_lock);

	status = snd_hdac_chip_पढ़ोl(bus, INTSTS);
	अगर (status == 0 || status == 0xffffffff) अणु
		spin_unlock(&bus->reg_lock);
		वापस IRQ_NONE;
	पूर्ण

	/* clear rirb पूर्णांक */
	status = snd_hdac_chip_पढ़ोb(bus, RIRBSTS);
	अगर (status & RIRB_INT_MASK) अणु
		अगर (status & RIRB_INT_RESPONSE)
			snd_hdac_bus_update_rirb(bus);
		snd_hdac_chip_ग_लिखोb(bus, RIRBSTS, RIRB_INT_MASK);
	पूर्ण

	spin_unlock(&bus->reg_lock);

	वापस snd_hdac_chip_पढ़ोl(bus, INTSTS) ? IRQ_WAKE_THREAD : IRQ_HANDLED;
पूर्ण

अटल irqवापस_t skl_thपढ़ोed_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hdac_bus *bus = dev_id;
	u32 status;

	status = snd_hdac_chip_पढ़ोl(bus, INTSTS);

	snd_hdac_bus_handle_stream_irq(bus, status, skl_stream_update);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक skl_acquire_irq(काष्ठा hdac_bus *bus, पूर्णांक करो_disconnect)
अणु
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	पूर्णांक ret;

	ret = request_thपढ़ोed_irq(skl->pci->irq, skl_पूर्णांकerrupt,
			skl_thपढ़ोed_handler,
			IRQF_SHARED,
			KBUILD_MODNAME, bus);
	अगर (ret) अणु
		dev_err(bus->dev,
			"unable to grab IRQ %d, disabling device\n",
			skl->pci->irq);
		वापस ret;
	पूर्ण

	bus->irq = skl->pci->irq;
	pci_पूर्णांकx(skl->pci, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	वापस skl_suspend_late_dsp(skl);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक _skl_suspend(काष्ठा hdac_bus *bus)
अणु
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा pci_dev *pci = to_pci_dev(bus->dev);
	पूर्णांक ret;

	snd_hdac_ext_bus_link_घातer_करोwn_all(bus);

	ret = skl_suspend_dsp(skl);
	अगर (ret < 0)
		वापस ret;

	snd_hdac_bus_stop_chip(bus);
	update_pci_dword(pci, AZX_PCIREG_PGCTL,
		AZX_PGCTL_LSRMD_MASK, AZX_PGCTL_LSRMD_MASK);
	skl_enable_miscbdcge(bus->dev, false);
	snd_hdac_bus_enter_link_reset(bus);
	skl_enable_miscbdcge(bus->dev, true);
	skl_cleanup_resources(skl);

	वापस 0;
पूर्ण

अटल पूर्णांक _skl_resume(काष्ठा hdac_bus *bus)
अणु
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	skl_init_pci(skl);
	skl_dum_set(bus);
	skl_init_chip(bus, true);

	वापस skl_resume_dsp(skl);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल पूर्णांक skl_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	काष्ठा skl_dev *skl  = bus_to_skl(bus);
	पूर्णांक ret;

	/*
	 * Do not suspend अगर streams which are marked ignore suspend are
	 * running, we need to save the state क्रम these and जारी
	 */
	अगर (skl->supend_active) अणु
		/* turn off the links and stop the CORB/RIRB DMA अगर it is On */
		snd_hdac_ext_bus_link_घातer_करोwn_all(bus);

		अगर (bus->cmd_dma_state)
			snd_hdac_bus_stop_cmd_io(bus);

		enable_irq_wake(bus->irq);
		pci_save_state(pci);
	पूर्ण अन्यथा अणु
		ret = _skl_suspend(bus);
		अगर (ret < 0)
			वापस ret;
		skl->fw_loaded = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	काष्ठा skl_dev *skl  = bus_to_skl(bus);
	काष्ठा hdac_ext_link *hlink;
	पूर्णांक ret;

	/*
	 * resume only when we are not in suspend active, otherwise need to
	 * restore the device
	 */
	अगर (skl->supend_active) अणु
		pci_restore_state(pci);
		snd_hdac_ext_bus_link_घातer_up_all(bus);
		disable_irq_wake(bus->irq);
		/*
		 * turn On the links which are On beक्रमe active suspend
		 * and start the CORB/RIRB DMA अगर On beक्रमe
		 * active suspend.
		 */
		list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
			अगर (hlink->ref_count)
				snd_hdac_ext_bus_link_घातer_up(hlink);
		पूर्ण

		ret = 0;
		अगर (bus->cmd_dma_state)
			snd_hdac_bus_init_cmd_io(bus);
	पूर्ण अन्यथा अणु
		ret = _skl_resume(bus);

		/* turn off the links which are off beक्रमe suspend */
		list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
			अगर (!hlink->ref_count)
				snd_hdac_ext_bus_link_घातer_करोwn(hlink);
		पूर्ण

		अगर (!bus->cmd_dma_state)
			snd_hdac_bus_stop_cmd_io(bus);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक skl_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);

	dev_dbg(bus->dev, "in %s\n", __func__);

	वापस _skl_suspend(bus);
पूर्ण

अटल पूर्णांक skl_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);

	dev_dbg(bus->dev, "in %s\n", __func__);

	वापस _skl_resume(bus);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops skl_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(skl_suspend, skl_resume)
	SET_RUNTIME_PM_OPS(skl_runसमय_suspend, skl_runसमय_resume, शून्य)
	.suspend_late = skl_suspend_late,
पूर्ण;

/*
 * deकाष्ठाor
 */
अटल पूर्णांक skl_मुक्त(काष्ठा hdac_bus *bus)
अणु
	काष्ठा skl_dev *skl  = bus_to_skl(bus);

	skl->init_करोne = 0; /* to be sure */

	snd_hdac_ext_stop_streams(bus);

	अगर (bus->irq >= 0)
		मुक्त_irq(bus->irq, (व्योम *)bus);
	snd_hdac_bus_मुक्त_stream_pages(bus);
	snd_hdac_stream_मुक्त_all(bus);
	snd_hdac_link_मुक्त_all(bus);

	अगर (bus->remap_addr)
		iounmap(bus->remap_addr);

	pci_release_regions(skl->pci);
	pci_disable_device(skl->pci);

	snd_hdac_ext_bus_निकास(bus);

	अगर (IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI)) अणु
		snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, false);
		snd_hdac_i915_निकास(bus);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * For each ssp there are 3 घड़ीs (mclk/sclk/sclkfs).
 * e.g. क्रम ssp0, घड़ीs will be named as
 *      "ssp0_mclk", "ssp0_sclk", "ssp0_sclkfs"
 * So क्रम skl+, there are 6 ssps, so 18 घड़ीs will be created.
 */
अटल काष्ठा skl_ssp_clk skl_ssp_clks[] = अणु
	अणु.name = "ssp0_mclk"पूर्ण, अणु.name = "ssp1_mclk"पूर्ण, अणु.name = "ssp2_mclk"पूर्ण,
	अणु.name = "ssp3_mclk"पूर्ण, अणु.name = "ssp4_mclk"पूर्ण, अणु.name = "ssp5_mclk"पूर्ण,
	अणु.name = "ssp0_sclk"पूर्ण, अणु.name = "ssp1_sclk"पूर्ण, अणु.name = "ssp2_sclk"पूर्ण,
	अणु.name = "ssp3_sclk"पूर्ण, अणु.name = "ssp4_sclk"पूर्ण, अणु.name = "ssp5_sclk"पूर्ण,
	अणु.name = "ssp0_sclkfs"पूर्ण, अणु.name = "ssp1_sclkfs"पूर्ण,
						अणु.name = "ssp2_sclkfs"पूर्ण,
	अणु.name = "ssp3_sclkfs"पूर्ण, अणु.name = "ssp4_sclkfs"पूर्ण,
						अणु.name = "ssp5_sclkfs"पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_acpi_mach *skl_find_hda_machine(काष्ठा skl_dev *skl,
					काष्ठा snd_soc_acpi_mach *machines)
अणु
	काष्ठा snd_soc_acpi_mach *mach;

	/* poपूर्णांक to common table */
	mach = snd_soc_acpi_पूर्णांकel_hda_machines;

	/* all entries in the machine table use the same firmware */
	mach->fw_filename = machines->fw_filename;

	वापस mach;
पूर्ण

अटल पूर्णांक skl_find_machine(काष्ठा skl_dev *skl, व्योम *driver_data)
अणु
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा snd_soc_acpi_mach *mach = driver_data;
	काष्ठा skl_machine_pdata *pdata;

	mach = snd_soc_acpi_find_machine(mach);
	अगर (!mach) अणु
		dev_dbg(bus->dev, "No matching I2S machine driver found\n");
		mach = skl_find_hda_machine(skl, driver_data);
		अगर (!mach) अणु
			dev_err(bus->dev, "No matching machine driver found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	skl->mach = mach;
	skl->fw_name = mach->fw_filename;
	pdata = mach->pdata;

	अगर (pdata) अणु
		skl->use_tplg_pcm = pdata->use_tplg_pcm;
		mach->mach_params.dmic_num =
			पूर्णांकel_nhlt_get_dmic_geo(&skl->pci->dev,
						skl->nhlt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_machine_device_रेजिस्टर(काष्ठा skl_dev *skl)
अणु
	काष्ठा snd_soc_acpi_mach *mach = skl->mach;
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc(mach->drv_name, -1);
	अगर (pdev == शून्य) अणु
		dev_err(bus->dev, "platform device alloc failed\n");
		वापस -EIO;
	पूर्ण

	mach->mach_params.platक्रमm = dev_name(bus->dev);
	mach->mach_params.codec_mask = bus->codec_mask;

	ret = platक्रमm_device_add_data(pdev, (स्थिर व्योम *)mach, माप(*mach));
	अगर (ret) अणु
		dev_err(bus->dev, "failed to add machine device platform data\n");
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
		dev_err(bus->dev, "failed to add machine device\n");
		platक्रमm_device_put(pdev);
		वापस -EIO;
	पूर्ण


	skl->i2s_dev = pdev;

	वापस 0;
पूर्ण

अटल व्योम skl_machine_device_unरेजिस्टर(काष्ठा skl_dev *skl)
अणु
	अगर (skl->i2s_dev)
		platक्रमm_device_unरेजिस्टर(skl->i2s_dev);
पूर्ण

अटल पूर्णांक skl_dmic_device_रेजिस्टर(काष्ठा skl_dev *skl)
अणु
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	/* SKL has one dmic port, so allocate dmic device क्रम this */
	pdev = platक्रमm_device_alloc("dmic-codec", -1);
	अगर (!pdev) अणु
		dev_err(bus->dev, "failed to allocate dmic device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
		dev_err(bus->dev, "failed to add dmic device: %d\n", ret);
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण
	skl->dmic_dev = pdev;

	वापस 0;
पूर्ण

अटल व्योम skl_dmic_device_unरेजिस्टर(काष्ठा skl_dev *skl)
अणु
	अगर (skl->dmic_dev)
		platक्रमm_device_unरेजिस्टर(skl->dmic_dev);
पूर्ण

अटल काष्ठा skl_clk_parent_src skl_clk_src[] = अणु
	अणु .clk_id = SKL_XTAL, .name = "xtal" पूर्ण,
	अणु .clk_id = SKL_CARDINAL, .name = "cardinal", .rate = 24576000 पूर्ण,
	अणु .clk_id = SKL_PLL, .name = "pll", .rate = 96000000 पूर्ण,
पूर्ण;

काष्ठा skl_clk_parent_src *skl_get_parent_clk(u8 clk_id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(skl_clk_src); i++) अणु
		अगर (skl_clk_src[i].clk_id == clk_id)
			वापस &skl_clk_src[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम init_skl_xtal_rate(पूर्णांक pci_id)
अणु
	चयन (pci_id) अणु
	हाल 0x9d70:
	हाल 0x9d71:
		skl_clk_src[0].rate = 24000000;
		वापस;

	शेष:
		skl_clk_src[0].rate = 19200000;
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_घड़ी_device_रेजिस्टर(काष्ठा skl_dev *skl)
अणु
	काष्ठा platक्रमm_device_info pdevinfo = अणुशून्यपूर्ण;
	काष्ठा skl_clk_pdata *clk_pdata;

	अगर (!skl->nhlt)
		वापस 0;

	clk_pdata = devm_kzalloc(&skl->pci->dev, माप(*clk_pdata),
							GFP_KERNEL);
	अगर (!clk_pdata)
		वापस -ENOMEM;

	init_skl_xtal_rate(skl->pci->device);

	clk_pdata->parent_clks = skl_clk_src;
	clk_pdata->ssp_clks = skl_ssp_clks;
	clk_pdata->num_clks = ARRAY_SIZE(skl_ssp_clks);

	/* Query NHLT to fill the rates and parent */
	skl_get_clks(skl, clk_pdata->ssp_clks);
	clk_pdata->pvt_data = skl;

	/* Register Platक्रमm device */
	pdevinfo.parent = &skl->pci->dev;
	pdevinfo.id = -1;
	pdevinfo.name = "skl-ssp-clk";
	pdevinfo.data = clk_pdata;
	pdevinfo.size_data = माप(*clk_pdata);
	skl->clk_dev = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	वापस PTR_ERR_OR_ZERO(skl->clk_dev);
पूर्ण

अटल व्योम skl_घड़ी_device_unरेजिस्टर(काष्ठा skl_dev *skl)
अणु
	अगर (skl->clk_dev)
		platक्रमm_device_unरेजिस्टर(skl->clk_dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC)

#घोषणा IDISP_INTEL_VENDOR_ID	0x80860000

/*
 * load the legacy codec driver
 */
अटल व्योम load_codec_module(काष्ठा hda_codec *codec)
अणु
#अगर_घोषित MODULE
	अक्षर modalias[MODULE_NAME_LEN];
	स्थिर अक्षर *mod = शून्य;

	snd_hdac_codec_modalias(&codec->core, modalias, माप(modalias));
	mod = modalias;
	dev_dbg(&codec->core.dev, "loading %s codec module\n", mod);
	request_module(mod);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC */

/*
 * Probe the given codec address
 */
अटल पूर्णांक probe_codec(काष्ठा hdac_bus *bus, पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक cmd = (addr << 28) | (AC_NODE_ROOT << 20) |
		(AC_VERB_PARAMETERS << 8) | AC_PAR_VENDOR_ID;
	अचिन्हित पूर्णांक res = -1;
	काष्ठा skl_dev *skl = bus_to_skl(bus);
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC)
	काष्ठा hdac_hda_priv *hda_codec;
	पूर्णांक err;
#पूर्ण_अगर
	काष्ठा hdac_device *hdev;

	mutex_lock(&bus->cmd_mutex);
	snd_hdac_bus_send_cmd(bus, cmd);
	snd_hdac_bus_get_response(bus, addr, &res);
	mutex_unlock(&bus->cmd_mutex);
	अगर (res == -1)
		वापस -EIO;
	dev_dbg(bus->dev, "codec #%d probed OK: %x\n", addr, res);

#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC)
	hda_codec = devm_kzalloc(&skl->pci->dev, माप(*hda_codec),
				 GFP_KERNEL);
	अगर (!hda_codec)
		वापस -ENOMEM;

	hda_codec->codec.bus = skl_to_hbus(skl);
	hdev = &hda_codec->codec.core;

	err = snd_hdac_ext_bus_device_init(bus, addr, hdev, HDA_DEV_ASOC);
	अगर (err < 0)
		वापस err;

	/* use legacy bus only क्रम HDA codecs, idisp uses ext bus */
	अगर ((res & 0xFFFF0000) != IDISP_INTEL_VENDOR_ID) अणु
		hdev->type = HDA_DEV_LEGACY;
		load_codec_module(&hda_codec->codec);
	पूर्ण
	वापस 0;
#अन्यथा
	hdev = devm_kzalloc(&skl->pci->dev, माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	वापस snd_hdac_ext_bus_device_init(bus, addr, hdev, HDA_DEV_ASOC);
#पूर्ण_अगर /* CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC */
पूर्ण

/* Codec initialization */
अटल व्योम skl_codec_create(काष्ठा hdac_bus *bus)
अणु
	पूर्णांक c, max_slots;

	max_slots = HDA_MAX_CODECS;

	/* First try to probe all given codec slots */
	क्रम (c = 0; c < max_slots; c++) अणु
		अगर ((bus->codec_mask & (1 << c))) अणु
			अगर (probe_codec(bus, c) < 0) अणु
				/*
				 * Some BIOSen give you wrong codec addresses
				 * that करोn't exist
				 */
				dev_warn(bus->dev,
					 "Codec #%d probe error; disabling it...\n", c);
				bus->codec_mask &= ~(1 << c);
				/*
				 * More badly, accessing to a non-existing
				 * codec often screws up the controller bus,
				 * and disturbs the further communications.
				 * Thus अगर an error occurs during probing,
				 * better to reset the controller bus to get
				 * back to the sanity state.
				 */
				snd_hdac_bus_stop_chip(bus);
				skl_init_chip(bus, true);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक skl_i915_init(काष्ठा hdac_bus *bus)
अणु
	पूर्णांक err;

	/*
	 * The HDMI codec is in GPU so we need to ensure that it is घातered
	 * up and पढ़ोy क्रम probe
	 */
	err = snd_hdac_i915_init(bus);
	अगर (err < 0)
		वापस err;

	snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, true);

	वापस 0;
पूर्ण

अटल व्योम skl_probe_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा skl_dev *skl = container_of(work, काष्ठा skl_dev, probe_work);
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा hdac_ext_link *hlink;
	पूर्णांक err;

	अगर (IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI)) अणु
		err = skl_i915_init(bus);
		अगर (err < 0)
			वापस;
	पूर्ण

	skl_init_pci(skl);
	skl_dum_set(bus);

	err = skl_init_chip(bus, true);
	अगर (err < 0) अणु
		dev_err(bus->dev, "Init chip failed with err: %d\n", err);
		जाओ out_err;
	पूर्ण

	/* codec detection */
	अगर (!bus->codec_mask)
		dev_info(bus->dev, "no hda codecs found!\n");

	/* create codec instances */
	skl_codec_create(bus);

	/* रेजिस्टर platक्रमm dai and controls */
	err = skl_platक्रमm_रेजिस्टर(bus->dev);
	अगर (err < 0) अणु
		dev_err(bus->dev, "platform register failed: %d\n", err);
		जाओ out_err;
	पूर्ण

	err = skl_machine_device_रेजिस्टर(skl);
	अगर (err < 0) अणु
		dev_err(bus->dev, "machine register failed: %d\n", err);
		जाओ out_err;
	पूर्ण

	/*
	 * we are करोne probing so decrement link counts
	 */
	list_क्रम_each_entry(hlink, &bus->hlink_list, list)
		snd_hdac_ext_bus_link_put(bus, hlink);

	अगर (IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI))
		snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, false);

	/* configure PM */
	pm_runसमय_put_noidle(bus->dev);
	pm_runसमय_allow(bus->dev);
	skl->init_करोne = 1;

	वापस;

out_err:
	अगर (IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI))
		snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, false);
पूर्ण

/*
 * स्थिरructor
 */
अटल पूर्णांक skl_create(काष्ठा pci_dev *pci,
		      काष्ठा skl_dev **rskl)
अणु
	काष्ठा hdac_ext_bus_ops *ext_ops = शून्य;
	काष्ठा skl_dev *skl;
	काष्ठा hdac_bus *bus;
	काष्ठा hda_bus *hbus;
	पूर्णांक err;

	*rskl = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	skl = devm_kzalloc(&pci->dev, माप(*skl), GFP_KERNEL);
	अगर (!skl) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	hbus = skl_to_hbus(skl);
	bus = skl_to_bus(skl);

	INIT_LIST_HEAD(&skl->ppl_list);
	INIT_LIST_HEAD(&skl->bind_list);

#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC)
	ext_ops = snd_soc_hdac_hda_get_ops();
#पूर्ण_अगर
	snd_hdac_ext_bus_init(bus, &pci->dev, शून्य, ext_ops);
	bus->use_posbuf = 1;
	skl->pci = pci;
	INIT_WORK(&skl->probe_work, skl_probe_work);
	bus->bdl_pos_adj = 0;

	mutex_init(&hbus->prepare_mutex);
	hbus->pci = pci;
	hbus->mixer_asचिन्हित = -1;
	hbus->modelname = "sklbus";

	*rskl = skl;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_first_init(काष्ठा hdac_bus *bus)
अणु
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा pci_dev *pci = skl->pci;
	पूर्णांक err;
	अचिन्हित लघु gcap;
	पूर्णांक cp_streams, pb_streams, start_idx;

	err = pci_request_regions(pci, "Skylake HD audio");
	अगर (err < 0)
		वापस err;

	bus->addr = pci_resource_start(pci, 0);
	bus->remap_addr = pci_ioremap_bar(pci, 0);
	अगर (bus->remap_addr == शून्य) अणु
		dev_err(bus->dev, "ioremap error\n");
		वापस -ENXIO;
	पूर्ण

	snd_hdac_bus_parse_capabilities(bus);

	/* check अगर PPCAP exists */
	अगर (!bus->ppcap) अणु
		dev_err(bus->dev, "bus ppcap not set, HDAudio or DSP not present?\n");
		वापस -ENODEV;
	पूर्ण

	अगर (skl_acquire_irq(bus, 0) < 0)
		वापस -EBUSY;

	pci_set_master(pci);
	synchronize_irq(bus->irq);

	gcap = snd_hdac_chip_पढ़ोw(bus, GCAP);
	dev_dbg(bus->dev, "chipset global capabilities = 0x%x\n", gcap);

	/* पढ़ो number of streams from GCAP रेजिस्टर */
	cp_streams = (gcap >> 8) & 0x0f;
	pb_streams = (gcap >> 12) & 0x0f;

	अगर (!pb_streams && !cp_streams) अणु
		dev_err(bus->dev, "no streams found in GCAP definitions?\n");
		वापस -EIO;
	पूर्ण

	bus->num_streams = cp_streams + pb_streams;

	/* allow 64bit DMA address अगर supported by H/W */
	अगर (dma_set_mask_and_coherent(bus->dev, DMA_BIT_MASK(64)))
		dma_set_mask_and_coherent(bus->dev, DMA_BIT_MASK(32));

	/* initialize streams */
	snd_hdac_ext_stream_init_all
		(bus, 0, cp_streams, SNDRV_PCM_STREAM_CAPTURE);
	start_idx = cp_streams;
	snd_hdac_ext_stream_init_all
		(bus, start_idx, pb_streams, SNDRV_PCM_STREAM_PLAYBACK);

	err = snd_hdac_bus_alloc_stream_pages(bus);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_probe(काष्ठा pci_dev *pci,
		     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा skl_dev *skl;
	काष्ठा hdac_bus *bus = शून्य;
	पूर्णांक err;

	चयन (skl_pci_binding) अणु
	हाल SND_SKL_PCI_BIND_AUTO:
		err = snd_पूर्णांकel_dsp_driver_probe(pci);
		अगर (err != SND_INTEL_DSP_DRIVER_ANY &&
		    err != SND_INTEL_DSP_DRIVER_SST)
			वापस -ENODEV;
		अवरोध;
	हाल SND_SKL_PCI_BIND_LEGACY:
		dev_info(&pci->dev, "Module parameter forced binding with HDAudio legacy, aborting probe\n");
		वापस -ENODEV;
	हाल SND_SKL_PCI_BIND_ASOC:
		dev_info(&pci->dev, "Module parameter forced binding with SKL driver, bypassed detection logic\n");
		अवरोध;
	शेष:
		dev_err(&pci->dev, "invalid value for skl_pci_binding module parameter, ignored\n");
		अवरोध;
	पूर्ण

	/* we use ext core ops, so provide शून्य क्रम ops here */
	err = skl_create(pci, &skl);
	अगर (err < 0)
		वापस err;

	bus = skl_to_bus(skl);

	err = skl_first_init(bus);
	अगर (err < 0) अणु
		dev_err(bus->dev, "skl_first_init failed with err: %d\n", err);
		जाओ out_मुक्त;
	पूर्ण

	skl->pci_id = pci->device;

	device_disable_async_suspend(bus->dev);

	skl->nhlt = पूर्णांकel_nhlt_init(bus->dev);

	अगर (skl->nhlt == शून्य) अणु
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_SKYLAKE_HDAUDIO_CODEC)
		dev_err(bus->dev, "no nhlt info found\n");
		err = -ENODEV;
		जाओ out_मुक्त;
#अन्यथा
		dev_warn(bus->dev, "no nhlt info found, continuing to try to enable HDAudio codec\n");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु

		err = skl_nhlt_create_sysfs(skl);
		अगर (err < 0) अणु
			dev_err(bus->dev, "skl_nhlt_create_sysfs failed with err: %d\n", err);
			जाओ out_nhlt_मुक्त;
		पूर्ण

		skl_nhlt_update_topology_bin(skl);

		/* create device क्रम dsp clk */
		err = skl_घड़ी_device_रेजिस्टर(skl);
		अगर (err < 0) अणु
			dev_err(bus->dev, "skl_clock_device_register failed with err: %d\n", err);
			जाओ out_clk_मुक्त;
		पूर्ण
	पूर्ण

	pci_set_drvdata(skl->pci, bus);


	err = skl_find_machine(skl, (व्योम *)pci_id->driver_data);
	अगर (err < 0) अणु
		dev_err(bus->dev, "skl_find_machine failed with err: %d\n", err);
		जाओ out_nhlt_मुक्त;
	पूर्ण

	err = skl_init_dsp(skl);
	अगर (err < 0) अणु
		dev_dbg(bus->dev, "error failed to register dsp\n");
		जाओ out_nhlt_मुक्त;
	पूर्ण
	skl->enable_miscbdcge = skl_enable_miscbdcge;
	skl->घड़ी_घातer_gating = skl_घड़ी_घातer_gating;

	अगर (bus->mlcap)
		snd_hdac_ext_bus_get_ml_capabilities(bus);

	/* create device क्रम soc dmic */
	err = skl_dmic_device_रेजिस्टर(skl);
	अगर (err < 0) अणु
		dev_err(bus->dev, "skl_dmic_device_register failed with err: %d\n", err);
		जाओ out_dsp_मुक्त;
	पूर्ण

	schedule_work(&skl->probe_work);

	वापस 0;

out_dsp_मुक्त:
	skl_मुक्त_dsp(skl);
out_clk_मुक्त:
	skl_घड़ी_device_unरेजिस्टर(skl);
out_nhlt_मुक्त:
	अगर (skl->nhlt)
		पूर्णांकel_nhlt_मुक्त(skl->nhlt);
out_मुक्त:
	skl_मुक्त(bus);

	वापस err;
पूर्ण

अटल व्योम skl_shutकरोwn(काष्ठा pci_dev *pci)
अणु
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	काष्ठा hdac_stream *s;
	काष्ठा hdac_ext_stream *stream;
	काष्ठा skl_dev *skl;

	अगर (!bus)
		वापस;

	skl = bus_to_skl(bus);

	अगर (!skl->init_करोne)
		वापस;

	snd_hdac_ext_stop_streams(bus);
	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		stream = stream_to_hdac_ext_stream(s);
		snd_hdac_ext_stream_decouple(bus, stream, false);
	पूर्ण

	snd_hdac_bus_stop_chip(bus);
पूर्ण

अटल व्योम skl_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	cancel_work_sync(&skl->probe_work);

	pm_runसमय_get_noresume(&pci->dev);

	/* codec removal, invoke bus_device_हटाओ */
	snd_hdac_ext_bus_device_हटाओ(bus);

	skl_platक्रमm_unरेजिस्टर(&pci->dev);
	skl_मुक्त_dsp(skl);
	skl_machine_device_unरेजिस्टर(skl);
	skl_dmic_device_unरेजिस्टर(skl);
	skl_घड़ी_device_unरेजिस्टर(skl);
	skl_nhlt_हटाओ_sysfs(skl);
	अगर (skl->nhlt)
		पूर्णांकel_nhlt_मुक्त(skl->nhlt);
	skl_मुक्त(bus);
	dev_set_drvdata(&pci->dev, शून्य);
पूर्ण

/* PCI IDs */
अटल स्थिर काष्ठा pci_device_id skl_ids[] = अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_SKL)
	/* Sunrise Poपूर्णांक-LP */
	अणु PCI_DEVICE(0x8086, 0x9d70),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_skl_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_APL)
	/* BXT-P */
	अणु PCI_DEVICE(0x8086, 0x5a98),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_bxt_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_KBL)
	/* KBL */
	अणु PCI_DEVICE(0x8086, 0x9D71),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_kbl_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_GLK)
	/* GLK */
	अणु PCI_DEVICE(0x8086, 0x3198),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_glk_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_CNL)
	/* CNL */
	अणु PCI_DEVICE(0x8086, 0x9dc8),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_cnl_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_CFL)
	/* CFL */
	अणु PCI_DEVICE(0x8086, 0xa348),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_cnl_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_CML_LP)
	/* CML-LP */
	अणु PCI_DEVICE(0x8086, 0x02c8),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_cnl_machinesपूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_CML_H)
	/* CML-H */
	अणु PCI_DEVICE(0x8086, 0x06c8),
		.driver_data = (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_cnl_machinesपूर्ण,
#पूर्ण_अगर
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, skl_ids);

/* pci_driver definition */
अटल काष्ठा pci_driver skl_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = skl_ids,
	.probe = skl_probe,
	.हटाओ = skl_हटाओ,
	.shutकरोwn = skl_shutकरोwn,
	.driver = अणु
		.pm = &skl_pm,
	पूर्ण,
पूर्ण;
module_pci_driver(skl_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Skylake ASoC HDA driver");
