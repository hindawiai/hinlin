<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  linux/drivers/mmc/host/sdhci-pci.c - SDHCI on PCI bus पूर्णांकerface
 *
 *  Copyright (C) 2005-2008 Pierre Ossman, All Rights Reserved.
 *
 * Thanks to the following companies क्रम their support:
 *
 *     - JMicron (hardware and technical support)
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/mmc/sdhci-pci-data.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/iosf_mbi.h>
#पूर्ण_अगर

#समावेश "cqhci.h"

#समावेश "sdhci.h"
#समावेश "sdhci-pci.h"

अटल व्योम sdhci_pci_hw_reset(काष्ठा sdhci_host *host);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_pci_init_wakeup(काष्ठा sdhci_pci_chip *chip)
अणु
	mmc_pm_flag_t pm_flags = 0;
	bool cap_cd_wake = false;
	पूर्णांक i;

	क्रम (i = 0; i < chip->num_slots; i++) अणु
		काष्ठा sdhci_pci_slot *slot = chip->slots[i];

		अगर (slot) अणु
			pm_flags |= slot->host->mmc->pm_flags;
			अगर (slot->host->mmc->caps & MMC_CAP_CD_WAKE)
				cap_cd_wake = true;
		पूर्ण
	पूर्ण

	अगर ((pm_flags & MMC_PM_KEEP_POWER) && (pm_flags & MMC_PM_WAKE_SDIO_IRQ))
		वापस device_wakeup_enable(&chip->pdev->dev);
	अन्यथा अगर (!cap_cd_wake)
		वापस device_wakeup_disable(&chip->pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_pci_suspend_host(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक i, ret;

	sdhci_pci_init_wakeup(chip);

	क्रम (i = 0; i < chip->num_slots; i++) अणु
		काष्ठा sdhci_pci_slot *slot = chip->slots[i];
		काष्ठा sdhci_host *host;

		अगर (!slot)
			जारी;

		host = slot->host;

		अगर (chip->pm_retune && host->tuning_mode != SDHCI_TUNING_MODE_3)
			mmc_retune_needed(host->mmc);

		ret = sdhci_suspend_host(host);
		अगर (ret)
			जाओ err_pci_suspend;

		अगर (device_may_wakeup(&chip->pdev->dev))
			mmc_gpio_set_cd_wake(host->mmc, true);
	पूर्ण

	वापस 0;

err_pci_suspend:
	जबतक (--i >= 0)
		sdhci_resume_host(chip->slots[i]->host);
	वापस ret;
पूर्ण

पूर्णांक sdhci_pci_resume_host(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा sdhci_pci_slot *slot;
	पूर्णांक i, ret;

	क्रम (i = 0; i < chip->num_slots; i++) अणु
		slot = chip->slots[i];
		अगर (!slot)
			जारी;

		ret = sdhci_resume_host(slot->host);
		अगर (ret)
			वापस ret;

		mmc_gpio_set_cd_wake(slot->host->mmc, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_cqhci_suspend(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;

	ret = cqhci_suspend(chip->slots[0]->host->mmc);
	अगर (ret)
		वापस ret;

	वापस sdhci_pci_suspend_host(chip);
पूर्ण

अटल पूर्णांक sdhci_cqhci_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;

	ret = sdhci_pci_resume_host(chip);
	अगर (ret)
		वापस ret;

	वापस cqhci_resume(chip->slots[0]->host->mmc);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_pci_runसमय_suspend_host(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा sdhci_pci_slot *slot;
	काष्ठा sdhci_host *host;
	पूर्णांक i, ret;

	क्रम (i = 0; i < chip->num_slots; i++) अणु
		slot = chip->slots[i];
		अगर (!slot)
			जारी;

		host = slot->host;

		ret = sdhci_runसमय_suspend_host(host);
		अगर (ret)
			जाओ err_pci_runसमय_suspend;

		अगर (chip->rpm_retune &&
		    host->tuning_mode != SDHCI_TUNING_MODE_3)
			mmc_retune_needed(host->mmc);
	पूर्ण

	वापस 0;

err_pci_runसमय_suspend:
	जबतक (--i >= 0)
		sdhci_runसमय_resume_host(chip->slots[i]->host, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_pci_runसमय_resume_host(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा sdhci_pci_slot *slot;
	पूर्णांक i, ret;

	क्रम (i = 0; i < chip->num_slots; i++) अणु
		slot = chip->slots[i];
		अगर (!slot)
			जारी;

		ret = sdhci_runसमय_resume_host(slot->host, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_cqhci_runसमय_suspend(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;

	ret = cqhci_suspend(chip->slots[0]->host->mmc);
	अगर (ret)
		वापस ret;

	वापस sdhci_pci_runसमय_suspend_host(chip);
पूर्ण

अटल पूर्णांक sdhci_cqhci_runसमय_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;

	ret = sdhci_pci_runसमय_resume_host(chip);
	अगर (ret)
		वापस ret;

	वापस cqhci_resume(chip->slots[0]->host->mmc);
पूर्ण
#पूर्ण_अगर

अटल u32 sdhci_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

अटल व्योम sdhci_pci_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल व्योम sdhci_cqhci_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	अगर ((host->mmc->caps2 & MMC_CAP2_CQE) && (mask & SDHCI_RESET_ALL) &&
	    host->mmc->cqe_निजी)
		cqhci_deactivate(host->mmc);
	sdhci_reset(host, mask);
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Hardware specअगरic quirk handling                                          *
 *                                                                           *
\*****************************************************************************/

अटल पूर्णांक ricoh_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	अगर (chip->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SAMSUNG ||
	    chip->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SONY)
		chip->quirks |= SDHCI_QUIRK_NO_CARD_NO_RESET;
	वापस 0;
पूर्ण

अटल पूर्णांक ricoh_mmc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	slot->host->caps =
		FIELD_PREP(SDHCI_TIMEOUT_CLK_MASK, 0x21) |
		FIELD_PREP(SDHCI_CLOCK_BASE_MASK, 0x21) |
		SDHCI_TIMEOUT_CLK_UNIT |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_SDMA;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ricoh_mmc_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	/* Apply a delay to allow controller to settle */
	/* Otherwise it becomes confused अगर card state changed
		during suspend */
	msleep(500);
	वापस sdhci_pci_resume_host(chip);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_ricoh = अणु
	.probe		= ricoh_probe,
	.quirks		= SDHCI_QUIRK_32BIT_DMA_ADDR |
			  SDHCI_QUIRK_FORCE_DMA |
			  SDHCI_QUIRK_CLOCK_BEFORE_RESET,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_ricoh_mmc = अणु
	.probe_slot	= ricoh_mmc_probe_slot,
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= ricoh_mmc_resume,
#पूर्ण_अगर
	.quirks		= SDHCI_QUIRK_32BIT_DMA_ADDR |
			  SDHCI_QUIRK_CLOCK_BEFORE_RESET |
			  SDHCI_QUIRK_NO_CARD_NO_RESET |
			  SDHCI_QUIRK_MISSING_CAPS
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_ene_712 = अणु
	.quirks		= SDHCI_QUIRK_SINGLE_POWER_WRITE |
			  SDHCI_QUIRK_BROKEN_DMA,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_ene_714 = अणु
	.quirks		= SDHCI_QUIRK_SINGLE_POWER_WRITE |
			  SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS |
			  SDHCI_QUIRK_BROKEN_DMA,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_cafe = अणु
	.quirks		= SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER |
			  SDHCI_QUIRK_NO_BUSY_IRQ |
			  SDHCI_QUIRK_BROKEN_CARD_DETECTION |
			  SDHCI_QUIRK_BROKEN_TIMEOUT_VAL,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_qrk = अणु
	.quirks		= SDHCI_QUIRK_NO_HISPD_BIT,
पूर्ण;

अटल पूर्णांक mrst_hc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	slot->host->mmc->caps |= MMC_CAP_8_BIT_DATA;
	वापस 0;
पूर्ण

/*
 * ADMA operation is disabled क्रम Moorestown platक्रमm due to
 * hardware bugs.
 */
अटल पूर्णांक mrst_hc_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	/*
	 * slots number is fixed here क्रम MRST as SDIO3/5 are never used and
	 * have hardware bugs.
	 */
	chip->num_slots = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक pch_hc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	slot->host->mmc->caps |= MMC_CAP_8_BIT_DATA;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल irqवापस_t sdhci_pci_sd_cd(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sdhci_pci_slot *slot = dev_id;
	काष्ठा sdhci_host *host = slot->host;

	mmc_detect_change(host->mmc, msecs_to_jअगरfies(200));
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sdhci_pci_add_own_cd(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक err, irq, gpio = slot->cd_gpio;

	slot->cd_gpio = -EINVAL;
	slot->cd_irq = -EINVAL;

	अगर (!gpio_is_valid(gpio))
		वापस;

	err = devm_gpio_request(&slot->chip->pdev->dev, gpio, "sd_cd");
	अगर (err < 0)
		जाओ out;

	err = gpio_direction_input(gpio);
	अगर (err < 0)
		जाओ out_मुक्त;

	irq = gpio_to_irq(gpio);
	अगर (irq < 0)
		जाओ out_मुक्त;

	err = request_irq(irq, sdhci_pci_sd_cd, IRQF_TRIGGER_RISING |
			  IRQF_TRIGGER_FALLING, "sd_cd", slot);
	अगर (err)
		जाओ out_मुक्त;

	slot->cd_gpio = gpio;
	slot->cd_irq = irq;

	वापस;

out_मुक्त:
	devm_gpio_मुक्त(&slot->chip->pdev->dev, gpio);
out:
	dev_warn(&slot->chip->pdev->dev, "failed to setup card detect wake up\n");
पूर्ण

अटल व्योम sdhci_pci_हटाओ_own_cd(काष्ठा sdhci_pci_slot *slot)
अणु
	अगर (slot->cd_irq >= 0)
		मुक्त_irq(slot->cd_irq, slot);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम sdhci_pci_add_own_cd(काष्ठा sdhci_pci_slot *slot)
अणु
पूर्ण

अटल अंतरभूत व्योम sdhci_pci_हटाओ_own_cd(काष्ठा sdhci_pci_slot *slot)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक mfd_emmc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	slot->host->mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_NONREMOVABLE;
	slot->host->mmc->caps2 |= MMC_CAP2_BOOTPART_NOACC;
	वापस 0;
पूर्ण

अटल पूर्णांक mfd_sdio_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	slot->host->mmc->caps |= MMC_CAP_POWER_OFF_CARD | MMC_CAP_NONREMOVABLE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_mrst_hc0 = अणु
	.quirks		= SDHCI_QUIRK_BROKEN_ADMA | SDHCI_QUIRK_NO_HISPD_BIT,
	.probe_slot	= mrst_hc_probe_slot,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_mrst_hc1_hc2 = अणु
	.quirks		= SDHCI_QUIRK_BROKEN_ADMA | SDHCI_QUIRK_NO_HISPD_BIT,
	.probe		= mrst_hc_probe,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_mfd_sd = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.allow_runसमय_pm = true,
	.own_cd_क्रम_runसमय_pm = true,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_mfd_sdio = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.quirks2	= SDHCI_QUIRK2_HOST_OFF_CARD_ON,
	.allow_runसमय_pm = true,
	.probe_slot	= mfd_sdio_probe_slot,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_mfd_emmc = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.allow_runसमय_pm = true,
	.probe_slot	= mfd_emmc_probe_slot,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_pch_sdio = अणु
	.quirks		= SDHCI_QUIRK_BROKEN_ADMA,
	.probe_slot	= pch_hc_probe_slot,
पूर्ण;

#अगर_घोषित CONFIG_X86

#घोषणा BYT_IOSF_SCCEP			0x63
#घोषणा BYT_IOSF_OCP_NETCTRL0		0x1078
#घोषणा BYT_IOSF_OCP_TIMEOUT_BASE	GENMASK(10, 8)

अटल व्योम byt_ocp_setting(काष्ठा pci_dev *pdev)
अणु
	u32 val = 0;

	अगर (pdev->device != PCI_DEVICE_ID_INTEL_BYT_EMMC &&
	    pdev->device != PCI_DEVICE_ID_INTEL_BYT_SDIO &&
	    pdev->device != PCI_DEVICE_ID_INTEL_BYT_SD &&
	    pdev->device != PCI_DEVICE_ID_INTEL_BYT_EMMC2)
		वापस;

	अगर (iosf_mbi_पढ़ो(BYT_IOSF_SCCEP, MBI_CR_READ, BYT_IOSF_OCP_NETCTRL0,
			  &val)) अणु
		dev_err(&pdev->dev, "%s read error\n", __func__);
		वापस;
	पूर्ण

	अगर (!(val & BYT_IOSF_OCP_TIMEOUT_BASE))
		वापस;

	val &= ~BYT_IOSF_OCP_TIMEOUT_BASE;

	अगर (iosf_mbi_ग_लिखो(BYT_IOSF_SCCEP, MBI_CR_WRITE, BYT_IOSF_OCP_NETCTRL0,
			   val)) अणु
		dev_err(&pdev->dev, "%s write error\n", __func__);
		वापस;
	पूर्ण

	dev_dbg(&pdev->dev, "%s completed\n", __func__);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम byt_ocp_setting(काष्ठा pci_dev *pdev)
अणु
पूर्ण

#पूर्ण_अगर

क्रमागत अणु
	INTEL_DSM_FNS		=  0,
	INTEL_DSM_V18_SWITCH	=  3,
	INTEL_DSM_V33_SWITCH	=  4,
	INTEL_DSM_DRV_STRENGTH	=  9,
	INTEL_DSM_D3_RETUNE	= 10,
पूर्ण;

काष्ठा पूर्णांकel_host अणु
	u32	dsm_fns;
	पूर्णांक	drv_strength;
	bool	d3_retune;
	bool	rpm_retune_ok;
	bool	needs_pwr_off;
	u32	glk_rx_ctrl1;
	u32	glk_tun_val;
	u32	active_ltr;
	u32	idle_ltr;
पूर्ण;

अटल स्थिर guid_t पूर्णांकel_dsm_guid =
	GUID_INIT(0xF6C13EA5, 0x65CD, 0x461F,
		  0xAB, 0x7A, 0x29, 0xF7, 0xE8, 0xD5, 0xBD, 0x61);

अटल पूर्णांक __पूर्णांकel_dsm(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev,
		       अचिन्हित पूर्णांक fn, u32 *result)
अणु
	जोड़ acpi_object *obj;
	पूर्णांक err = 0;
	माप_प्रकार len;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), &पूर्णांकel_dsm_guid, 0, fn, शून्य);
	अगर (!obj)
		वापस -EOPNOTSUPP;

	अगर (obj->type != ACPI_TYPE_BUFFER || obj->buffer.length < 1) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	len = min_t(माप_प्रकार, obj->buffer.length, 4);

	*result = 0;
	स_नकल(result, obj->buffer.poपूर्णांकer, len);
out:
	ACPI_FREE(obj);

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_dsm(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev,
		     अचिन्हित पूर्णांक fn, u32 *result)
अणु
	अगर (fn > 31 || !(पूर्णांकel_host->dsm_fns & (1 << fn)))
		वापस -EOPNOTSUPP;

	वापस __पूर्णांकel_dsm(पूर्णांकel_host, dev, fn, result);
पूर्ण

अटल व्योम पूर्णांकel_dsm_init(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev,
			   काष्ठा mmc_host *mmc)
अणु
	पूर्णांक err;
	u32 val;

	पूर्णांकel_host->d3_retune = true;

	err = __पूर्णांकel_dsm(पूर्णांकel_host, dev, INTEL_DSM_FNS, &पूर्णांकel_host->dsm_fns);
	अगर (err) अणु
		pr_debug("%s: DSM not supported, error %d\n",
			 mmc_hostname(mmc), err);
		वापस;
	पूर्ण

	pr_debug("%s: DSM function mask %#x\n",
		 mmc_hostname(mmc), पूर्णांकel_host->dsm_fns);

	err = पूर्णांकel_dsm(पूर्णांकel_host, dev, INTEL_DSM_DRV_STRENGTH, &val);
	पूर्णांकel_host->drv_strength = err ? 0 : val;

	err = पूर्णांकel_dsm(पूर्णांकel_host, dev, INTEL_DSM_D3_RETUNE, &val);
	पूर्णांकel_host->d3_retune = err ? true : !!val;
पूर्ण

अटल व्योम sdhci_pci_पूर्णांक_hw_reset(काष्ठा sdhci_host *host)
अणु
	u8 reg;

	reg = sdhci_पढ़ोb(host, SDHCI_POWER_CONTROL);
	reg |= 0x10;
	sdhci_ग_लिखोb(host, reg, SDHCI_POWER_CONTROL);
	/* For eMMC, minimum is 1us but give it 9us क्रम good measure */
	udelay(9);
	reg &= ~0x10;
	sdhci_ग_लिखोb(host, reg, SDHCI_POWER_CONTROL);
	/* For eMMC, minimum is 200us but give it 300us क्रम good measure */
	usleep_range(300, 1000);
पूर्ण

अटल पूर्णांक पूर्णांकel_select_drive_strength(काष्ठा mmc_card *card,
				       अचिन्हित पूर्णांक max_dtr, पूर्णांक host_drv,
				       पूर्णांक card_drv, पूर्णांक *drv_type)
अणु
	काष्ठा sdhci_host *host = mmc_priv(card->host);
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);

	अगर (!(mmc_driver_type_mask(पूर्णांकel_host->drv_strength) & card_drv))
		वापस 0;

	वापस पूर्णांकel_host->drv_strength;
पूर्ण

अटल पूर्णांक bxt_get_cd(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक gpio_cd = mmc_gpio_get_cd(mmc);
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!gpio_cd)
		वापस 0;

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->flags & SDHCI_DEVICE_DEAD)
		जाओ out;

	ret = !!(sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT);
out:
	spin_unlock_irqrestore(&host->lock, flags);

	वापस ret;
पूर्ण

#घोषणा SDHCI_INTEL_PWR_TIMEOUT_CNT	20
#घोषणा SDHCI_INTEL_PWR_TIMEOUT_UDELAY	100

अटल व्योम sdhci_पूर्णांकel_set_घातer(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
				  अचिन्हित लघु vdd)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	पूर्णांक cntr;
	u8 reg;

	/*
	 * Bus घातer may control card घातer, but a full reset still may not
	 * reset the घातer, whereas a direct ग_लिखो to SDHCI_POWER_CONTROL can.
	 * That might be needed to initialize correctly, अगर the card was left
	 * घातered on previously.
	 */
	अगर (पूर्णांकel_host->needs_pwr_off) अणु
		पूर्णांकel_host->needs_pwr_off = false;
		अगर (mode != MMC_POWER_OFF) अणु
			sdhci_ग_लिखोb(host, 0, SDHCI_POWER_CONTROL);
			usleep_range(10000, 12500);
		पूर्ण
	पूर्ण

	sdhci_set_घातer(host, mode, vdd);

	अगर (mode == MMC_POWER_OFF)
		वापस;

	/*
	 * Bus घातer might not enable after D3 -> D0 transition due to the
	 * present state not yet having propagated. Retry क्रम up to 2ms.
	 */
	क्रम (cntr = 0; cntr < SDHCI_INTEL_PWR_TIMEOUT_CNT; cntr++) अणु
		reg = sdhci_पढ़ोb(host, SDHCI_POWER_CONTROL);
		अगर (reg & SDHCI_POWER_ON)
			अवरोध;
		udelay(SDHCI_INTEL_PWR_TIMEOUT_UDELAY);
		reg |= SDHCI_POWER_ON;
		sdhci_ग_लिखोb(host, reg, SDHCI_POWER_CONTROL);
	पूर्ण
पूर्ण

अटल व्योम sdhci_पूर्णांकel_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					  अचिन्हित पूर्णांक timing)
अणु
	/* Set UHS timing to SDR25 क्रम High Speed mode */
	अगर (timing == MMC_TIMING_MMC_HS || timing == MMC_TIMING_SD_HS)
		timing = MMC_TIMING_UHS_SDR25;
	sdhci_set_uhs_संकेतing(host, timing);
पूर्ण

#घोषणा INTEL_HS400_ES_REG 0x78
#घोषणा INTEL_HS400_ES_BIT BIT(0)

अटल व्योम पूर्णांकel_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 val;

	val = sdhci_पढ़ोl(host, INTEL_HS400_ES_REG);
	अगर (ios->enhanced_strobe)
		val |= INTEL_HS400_ES_BIT;
	अन्यथा
		val &= ~INTEL_HS400_ES_BIT;
	sdhci_ग_लिखोl(host, val, INTEL_HS400_ES_REG);
पूर्ण

अटल पूर्णांक पूर्णांकel_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
					     काष्ठा mmc_ios *ios)
अणु
	काष्ठा device *dev = mmc_dev(mmc);
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	अचिन्हित पूर्णांक fn;
	u32 result = 0;
	पूर्णांक err;

	err = sdhci_start_संकेत_voltage_चयन(mmc, ios);
	अगर (err)
		वापस err;

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		fn = INTEL_DSM_V33_SWITCH;
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		fn = INTEL_DSM_V18_SWITCH;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	err = पूर्णांकel_dsm(पूर्णांकel_host, dev, fn, &result);
	pr_debug("%s: %s DSM fn %u error %d result %u\n",
		 mmc_hostname(mmc), __func__, fn, err, result);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_पूर्णांकel_byt_ops = अणु
	.set_घड़ी		= sdhci_set_घड़ी,
	.set_घातer		= sdhci_पूर्णांकel_set_घातer,
	.enable_dma		= sdhci_pci_enable_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_reset,
	.set_uhs_संकेतing	= sdhci_पूर्णांकel_set_uhs_संकेतing,
	.hw_reset		= sdhci_pci_hw_reset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_पूर्णांकel_glk_ops = अणु
	.set_घड़ी		= sdhci_set_घड़ी,
	.set_घातer		= sdhci_पूर्णांकel_set_घातer,
	.enable_dma		= sdhci_pci_enable_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_cqhci_reset,
	.set_uhs_संकेतing	= sdhci_पूर्णांकel_set_uhs_संकेतing,
	.hw_reset		= sdhci_pci_hw_reset,
	.irq			= sdhci_cqhci_irq,
पूर्ण;

अटल व्योम byt_पढ़ो_dsm(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	काष्ठा device *dev = &slot->chip->pdev->dev;
	काष्ठा mmc_host *mmc = slot->host->mmc;

	पूर्णांकel_dsm_init(पूर्णांकel_host, dev, mmc);
	slot->chip->rpm_retune = पूर्णांकel_host->d3_retune;
पूर्ण

अटल पूर्णांक पूर्णांकel_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	पूर्णांक err = sdhci_execute_tuning(mmc, opcode);
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	अगर (err)
		वापस err;

	/*
	 * Tuning can leave the IP in an active state (Buffer Read Enable bit
	 * set) which prevents the entry to low घातer states (i.e. S0i3). Data
	 * reset will clear it.
	 */
	sdhci_reset(host, SDHCI_RESET_DATA);

	वापस 0;
पूर्ण

#घोषणा INTEL_ACTIVELTR		0x804
#घोषणा INTEL_IDLELTR		0x808

#घोषणा INTEL_LTR_REQ		BIT(15)
#घोषणा INTEL_LTR_SCALE_MASK	GENMASK(11, 10)
#घोषणा INTEL_LTR_SCALE_1US	(2 << 10)
#घोषणा INTEL_LTR_SCALE_32US	(3 << 10)
#घोषणा INTEL_LTR_VALUE_MASK	GENMASK(9, 0)

अटल व्योम पूर्णांकel_cache_ltr(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	काष्ठा sdhci_host *host = slot->host;

	पूर्णांकel_host->active_ltr = पढ़ोl(host->ioaddr + INTEL_ACTIVELTR);
	पूर्णांकel_host->idle_ltr = पढ़ोl(host->ioaddr + INTEL_IDLELTR);
पूर्ण

अटल व्योम पूर्णांकel_ltr_set(काष्ठा device *dev, s32 val)
अणु
	काष्ठा sdhci_pci_chip *chip = dev_get_drvdata(dev);
	काष्ठा sdhci_pci_slot *slot = chip->slots[0];
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	काष्ठा sdhci_host *host = slot->host;
	u32 ltr;

	pm_runसमय_get_sync(dev);

	/*
	 * Program latency tolerance (LTR) accordingly what has been asked
	 * by the PM QoS layer or disable it in हाल we were passed
	 * negative value or PM_QOS_LATENCY_ANY.
	 */
	ltr = पढ़ोl(host->ioaddr + INTEL_ACTIVELTR);

	अगर (val == PM_QOS_LATENCY_ANY || val < 0) अणु
		ltr &= ~INTEL_LTR_REQ;
	पूर्ण अन्यथा अणु
		ltr |= INTEL_LTR_REQ;
		ltr &= ~INTEL_LTR_SCALE_MASK;
		ltr &= ~INTEL_LTR_VALUE_MASK;

		अगर (val > INTEL_LTR_VALUE_MASK) अणु
			val >>= 5;
			अगर (val > INTEL_LTR_VALUE_MASK)
				val = INTEL_LTR_VALUE_MASK;
			ltr |= INTEL_LTR_SCALE_32US | val;
		पूर्ण अन्यथा अणु
			ltr |= INTEL_LTR_SCALE_1US | val;
		पूर्ण
	पूर्ण

	अगर (ltr == पूर्णांकel_host->active_ltr)
		जाओ out;

	ग_लिखोl(ltr, host->ioaddr + INTEL_ACTIVELTR);
	ग_लिखोl(ltr, host->ioaddr + INTEL_IDLELTR);

	/* Cache the values पूर्णांकo lpss काष्ठाure */
	पूर्णांकel_cache_ltr(slot);
out:
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल bool पूर्णांकel_use_ltr(काष्ठा sdhci_pci_chip *chip)
अणु
	चयन (chip->pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_BYT_EMMC:
	हाल PCI_DEVICE_ID_INTEL_BYT_EMMC2:
	हाल PCI_DEVICE_ID_INTEL_BYT_SDIO:
	हाल PCI_DEVICE_ID_INTEL_BYT_SD:
	हाल PCI_DEVICE_ID_INTEL_BSW_EMMC:
	हाल PCI_DEVICE_ID_INTEL_BSW_SDIO:
	हाल PCI_DEVICE_ID_INTEL_BSW_SD:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_ltr_expose(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा device *dev = &chip->pdev->dev;

	अगर (!पूर्णांकel_use_ltr(chip))
		वापस;

	dev->घातer.set_latency_tolerance = पूर्णांकel_ltr_set;
	dev_pm_qos_expose_latency_tolerance(dev);
पूर्ण

अटल व्योम पूर्णांकel_ltr_hide(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा device *dev = &chip->pdev->dev;

	अगर (!पूर्णांकel_use_ltr(chip))
		वापस;

	dev_pm_qos_hide_latency_tolerance(dev);
	dev->घातer.set_latency_tolerance = शून्य;
पूर्ण

अटल व्योम byt_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा mmc_host_ops *ops = &slot->host->mmc_host_ops;
	काष्ठा device *dev = &slot->chip->pdev->dev;
	काष्ठा mmc_host *mmc = slot->host->mmc;

	byt_पढ़ो_dsm(slot);

	byt_ocp_setting(slot->chip->pdev);

	ops->execute_tuning = पूर्णांकel_execute_tuning;
	ops->start_संकेत_voltage_चयन = पूर्णांकel_start_संकेत_voltage_चयन;

	device_property_पढ़ो_u32(dev, "max-frequency", &mmc->f_max);

	अगर (!mmc->slotno) अणु
		slot->chip->slots[mmc->slotno] = slot;
		पूर्णांकel_ltr_expose(slot->chip);
	पूर्ण
पूर्ण

अटल व्योम byt_add_debugfs(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	काष्ठा mmc_host *mmc = slot->host->mmc;
	काष्ठा dentry *dir = mmc->debugfs_root;

	अगर (!पूर्णांकel_use_ltr(slot->chip))
		वापस;

	debugfs_create_x32("active_ltr", 0444, dir, &पूर्णांकel_host->active_ltr);
	debugfs_create_x32("idle_ltr", 0444, dir, &पूर्णांकel_host->idle_ltr);

	पूर्णांकel_cache_ltr(slot);
पूर्ण

अटल पूर्णांक byt_add_host(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक ret = sdhci_add_host(slot->host);

	अगर (!ret)
		byt_add_debugfs(slot);
	वापस ret;
पूर्ण

अटल व्योम byt_हटाओ_slot(काष्ठा sdhci_pci_slot *slot, पूर्णांक dead)
अणु
	काष्ठा mmc_host *mmc = slot->host->mmc;

	अगर (!mmc->slotno)
		पूर्णांकel_ltr_hide(slot->chip);
पूर्ण

अटल पूर्णांक byt_emmc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	byt_probe_slot(slot);
	slot->host->mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_NONREMOVABLE |
				 MMC_CAP_HW_RESET | MMC_CAP_1_8V_DDR |
				 MMC_CAP_CMD_DURING_TFR |
				 MMC_CAP_WAIT_WHILE_BUSY;
	slot->hw_reset = sdhci_pci_पूर्णांक_hw_reset;
	अगर (slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_BSW_EMMC)
		slot->host->समयout_clk = 1000; /* 1000 kHz i.e. 1 MHz */
	slot->host->mmc_host_ops.select_drive_strength =
						पूर्णांकel_select_drive_strength;
	वापस 0;
पूर्ण

अटल bool glk_broken_cqhci(काष्ठा sdhci_pci_slot *slot)
अणु
	वापस slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_GLK_EMMC &&
	       (dmi_match(DMI_BIOS_VENDOR, "LENOVO") ||
		dmi_match(DMI_SYS_VENDOR, "IRBIS"));
पूर्ण

अटल पूर्णांक glk_emmc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक ret = byt_emmc_probe_slot(slot);

	अगर (!glk_broken_cqhci(slot))
		slot->host->mmc->caps2 |= MMC_CAP2_CQE;

	अगर (slot->chip->pdev->device != PCI_DEVICE_ID_INTEL_GLK_EMMC) अणु
		slot->host->mmc->caps2 |= MMC_CAP2_HS400_ES;
		slot->host->mmc_host_ops.hs400_enhanced_strobe =
						पूर्णांकel_hs400_enhanced_strobe;
		slot->host->mmc->caps2 |= MMC_CAP2_CQE_DCMD;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops glk_cqhci_ops = अणु
	.enable		= sdhci_cqe_enable,
	.disable	= sdhci_cqe_disable,
	.dumpregs	= sdhci_pci_dumpregs,
पूर्ण;

अटल पूर्णांक glk_emmc_add_host(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा device *dev = &slot->chip->pdev->dev;
	काष्ठा sdhci_host *host = slot->host;
	काष्ठा cqhci_host *cq_host;
	bool dma64;
	पूर्णांक ret;

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	cq_host = devm_kzalloc(dev, माप(*cq_host), GFP_KERNEL);
	अगर (!cq_host) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	cq_host->mmio = host->ioaddr + 0x200;
	cq_host->quirks |= CQHCI_QUIRK_SHORT_TXFR_DESC_SZ;
	cq_host->ops = &glk_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;
	अगर (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	ret = cqhci_init(cq_host, host->mmc, dma64);
	अगर (ret)
		जाओ cleanup;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ cleanup;

	byt_add_debugfs(slot);

	वापस 0;

cleanup:
	sdhci_cleanup_host(host);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
#घोषणा GLK_RX_CTRL1	0x834
#घोषणा GLK_TUN_VAL	0x840
#घोषणा GLK_PATH_PLL	GENMASK(13, 8)
#घोषणा GLK_DLY		GENMASK(6, 0)
/* Workaround firmware failing to restore the tuning value */
अटल व्योम glk_rpm_retune_wa(काष्ठा sdhci_pci_chip *chip, bool susp)
अणु
	काष्ठा sdhci_pci_slot *slot = chip->slots[0];
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	काष्ठा sdhci_host *host = slot->host;
	u32 glk_rx_ctrl1;
	u32 glk_tun_val;
	u32 dly;

	अगर (पूर्णांकel_host->rpm_retune_ok || !mmc_can_retune(host->mmc))
		वापस;

	glk_rx_ctrl1 = sdhci_पढ़ोl(host, GLK_RX_CTRL1);
	glk_tun_val = sdhci_पढ़ोl(host, GLK_TUN_VAL);

	अगर (susp) अणु
		पूर्णांकel_host->glk_rx_ctrl1 = glk_rx_ctrl1;
		पूर्णांकel_host->glk_tun_val = glk_tun_val;
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_host->glk_tun_val)
		वापस;

	अगर (glk_rx_ctrl1 != पूर्णांकel_host->glk_rx_ctrl1) अणु
		पूर्णांकel_host->rpm_retune_ok = true;
		वापस;
	पूर्ण

	dly = FIELD_PREP(GLK_DLY, FIELD_GET(GLK_PATH_PLL, glk_rx_ctrl1) +
				  (पूर्णांकel_host->glk_tun_val << 1));
	अगर (dly == FIELD_GET(GLK_DLY, glk_rx_ctrl1))
		वापस;

	glk_rx_ctrl1 = (glk_rx_ctrl1 & ~GLK_DLY) | dly;
	sdhci_ग_लिखोl(host, glk_rx_ctrl1, GLK_RX_CTRL1);

	पूर्णांकel_host->rpm_retune_ok = true;
	chip->rpm_retune = true;
	mmc_retune_needed(host->mmc);
	pr_info("%s: Requiring re-tune after rpm resume", mmc_hostname(host->mmc));
पूर्ण

अटल व्योम glk_rpm_retune_chk(काष्ठा sdhci_pci_chip *chip, bool susp)
अणु
	अगर (chip->pdev->device == PCI_DEVICE_ID_INTEL_GLK_EMMC &&
	    !chip->rpm_retune)
		glk_rpm_retune_wa(chip, susp);
पूर्ण

अटल पूर्णांक glk_runसमय_suspend(काष्ठा sdhci_pci_chip *chip)
अणु
	glk_rpm_retune_chk(chip, true);

	वापस sdhci_cqhci_runसमय_suspend(chip);
पूर्ण

अटल पूर्णांक glk_runसमय_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	glk_rpm_retune_chk(chip, false);

	वापस sdhci_cqhci_runसमय_resume(chip);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक ni_set_max_freq(काष्ठा sdhci_pci_slot *slot)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ max_freq;

	status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(&slot->chip->pdev->dev),
				       "MXFQ", शून्य, &max_freq);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&slot->chip->pdev->dev,
			"MXFQ not found in acpi table\n");
		वापस -EINVAL;
	पूर्ण

	slot->host->mmc->f_max = max_freq * 1000000;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ni_set_max_freq(काष्ठा sdhci_pci_slot *slot)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ni_byt_sdio_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक err;

	byt_probe_slot(slot);

	err = ni_set_max_freq(slot);
	अगर (err)
		वापस err;

	slot->host->mmc->caps |= MMC_CAP_POWER_OFF_CARD | MMC_CAP_NONREMOVABLE |
				 MMC_CAP_WAIT_WHILE_BUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक byt_sdio_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	byt_probe_slot(slot);
	slot->host->mmc->caps |= MMC_CAP_POWER_OFF_CARD | MMC_CAP_NONREMOVABLE |
				 MMC_CAP_WAIT_WHILE_BUSY;
	वापस 0;
पूर्ण

अटल व्योम byt_needs_pwr_off(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_pci_priv(slot);
	u8 reg = sdhci_पढ़ोb(slot->host, SDHCI_POWER_CONTROL);

	पूर्णांकel_host->needs_pwr_off = reg  & SDHCI_POWER_ON;
पूर्ण

अटल पूर्णांक byt_sd_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	byt_probe_slot(slot);
	slot->host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY |
				 MMC_CAP_AGGRESSIVE_PM | MMC_CAP_CD_WAKE;
	slot->cd_idx = 0;
	slot->cd_override_level = true;
	अगर (slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_BXT_SD ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_BXTM_SD ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_APL_SD ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_GLK_SD)
		slot->host->mmc_host_ops.get_cd = bxt_get_cd;

	अगर (slot->chip->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_NI &&
	    slot->chip->pdev->subप्रणाली_device == PCI_SUBDEVICE_ID_NI_78E3)
		slot->host->mmc->caps2 |= MMC_CAP2_AVOID_3_3V;

	byt_needs_pwr_off(slot);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक byt_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	byt_ocp_setting(chip->pdev);

	वापस sdhci_pci_resume_host(chip);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PM

अटल पूर्णांक byt_runसमय_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	byt_ocp_setting(chip->pdev);

	वापस sdhci_pci_runसमय_resume_host(chip);
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_byt_emmc = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= byt_resume,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	.runसमय_resume	= byt_runसमय_resume,
#पूर्ण_अगर
	.allow_runसमय_pm = true,
	.probe_slot	= byt_emmc_probe_slot,
	.add_host	= byt_add_host,
	.हटाओ_slot	= byt_हटाओ_slot,
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
			  SDHCI_QUIRK_NO_LED,
	.quirks2	= SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
			  SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 |
			  SDHCI_QUIRK2_STOP_WITH_TC,
	.ops		= &sdhci_पूर्णांकel_byt_ops,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_glk_emmc = अणु
	.allow_runसमय_pm	= true,
	.probe_slot		= glk_emmc_probe_slot,
	.add_host		= glk_emmc_add_host,
	.हटाओ_slot		= byt_हटाओ_slot,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= sdhci_cqhci_suspend,
	.resume			= sdhci_cqhci_resume,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	.runसमय_suspend	= glk_runसमय_suspend,
	.runसमय_resume		= glk_runसमय_resume,
#पूर्ण_अगर
	.quirks			= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
				  SDHCI_QUIRK_NO_LED,
	.quirks2		= SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
				  SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 |
				  SDHCI_QUIRK2_STOP_WITH_TC,
	.ops			= &sdhci_पूर्णांकel_glk_ops,
	.priv_size		= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_ni_byt_sdio = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= byt_resume,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	.runसमय_resume	= byt_runसमय_resume,
#पूर्ण_अगर
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
			  SDHCI_QUIRK_NO_LED,
	.quirks2	= SDHCI_QUIRK2_HOST_OFF_CARD_ON |
			  SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.allow_runसमय_pm = true,
	.probe_slot	= ni_byt_sdio_probe_slot,
	.add_host	= byt_add_host,
	.हटाओ_slot	= byt_हटाओ_slot,
	.ops		= &sdhci_पूर्णांकel_byt_ops,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_byt_sdio = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= byt_resume,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	.runसमय_resume	= byt_runसमय_resume,
#पूर्ण_अगर
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
			  SDHCI_QUIRK_NO_LED,
	.quirks2	= SDHCI_QUIRK2_HOST_OFF_CARD_ON |
			SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.allow_runसमय_pm = true,
	.probe_slot	= byt_sdio_probe_slot,
	.add_host	= byt_add_host,
	.हटाओ_slot	= byt_हटाओ_slot,
	.ops		= &sdhci_पूर्णांकel_byt_ops,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_byt_sd = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= byt_resume,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	.runसमय_resume	= byt_runसमय_resume,
#पूर्ण_अगर
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
			  SDHCI_QUIRK_NO_LED,
	.quirks2	= SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON |
			  SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
			  SDHCI_QUIRK2_STOP_WITH_TC,
	.allow_runसमय_pm = true,
	.own_cd_क्रम_runसमय_pm = true,
	.probe_slot	= byt_sd_probe_slot,
	.add_host	= byt_add_host,
	.हटाओ_slot	= byt_हटाओ_slot,
	.ops		= &sdhci_पूर्णांकel_byt_ops,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

/* Define Host controllers क्रम Intel Merrअगरield platक्रमm */
#घोषणा INTEL_MRFLD_EMMC_0	0
#घोषणा INTEL_MRFLD_EMMC_1	1
#घोषणा INTEL_MRFLD_SD		2
#घोषणा INTEL_MRFLD_SDIO	3

#अगर_घोषित CONFIG_ACPI
अटल व्योम पूर्णांकel_mrfld_mmc_fix_up_घातer_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा acpi_device *device, *child;

	device = ACPI_COMPANION(&slot->chip->pdev->dev);
	अगर (!device)
		वापस;

	acpi_device_fix_up_घातer(device);
	list_क्रम_each_entry(child, &device->children, node)
		अगर (child->status.present && child->status.enabled)
			acpi_device_fix_up_घातer(child);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_mrfld_mmc_fix_up_घातer_slot(काष्ठा sdhci_pci_slot *slot) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक पूर्णांकel_mrfld_mmc_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	अचिन्हित पूर्णांक func = PCI_FUNC(slot->chip->pdev->devfn);

	चयन (func) अणु
	हाल INTEL_MRFLD_EMMC_0:
	हाल INTEL_MRFLD_EMMC_1:
		slot->host->mmc->caps |= MMC_CAP_NONREMOVABLE |
					 MMC_CAP_8_BIT_DATA |
					 MMC_CAP_1_8V_DDR;
		अवरोध;
	हाल INTEL_MRFLD_SD:
		slot->host->quirks2 |= SDHCI_QUIRK2_NO_1_8_V;
		अवरोध;
	हाल INTEL_MRFLD_SDIO:
		/* Advertise 2.0v क्रम compatibility with the SDIO card's OCR */
		slot->host->ocr_mask = MMC_VDD_20_21 | MMC_VDD_165_195;
		slot->host->mmc->caps |= MMC_CAP_NONREMOVABLE |
					 MMC_CAP_POWER_OFF_CARD;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	पूर्णांकel_mrfld_mmc_fix_up_घातer_slot(slot);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_पूर्णांकel_mrfld_mmc = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.quirks2	= SDHCI_QUIRK2_BROKEN_HS200 |
			SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.allow_runसमय_pm = true,
	.probe_slot	= पूर्णांकel_mrfld_mmc_probe_slot,
पूर्ण;

अटल पूर्णांक jmicron_pmos(काष्ठा sdhci_pci_chip *chip, पूर्णांक on)
अणु
	u8 scratch;
	पूर्णांक ret;

	ret = pci_पढ़ो_config_byte(chip->pdev, 0xAE, &scratch);
	अगर (ret)
		वापस ret;

	/*
	 * Turn PMOS on [bit 0], set over current detection to 2.4 V
	 * [bit 1:2] and enable over current debouncing [bit 6].
	 */
	अगर (on)
		scratch |= 0x47;
	अन्यथा
		scratch &= ~0x47;

	वापस pci_ग_लिखो_config_byte(chip->pdev, 0xAE, scratch);
पूर्ण

अटल पूर्णांक jmicron_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;
	u16 mmcdev = 0;

	अगर (chip->pdev->revision == 0) अणु
		chip->quirks |= SDHCI_QUIRK_32BIT_DMA_ADDR |
			  SDHCI_QUIRK_32BIT_DMA_SIZE |
			  SDHCI_QUIRK_32BIT_ADMA_SIZE |
			  SDHCI_QUIRK_RESET_AFTER_REQUEST |
			  SDHCI_QUIRK_BROKEN_SMALL_PIO;
	पूर्ण

	/*
	 * JMicron chips can have two पूर्णांकerfaces to the same hardware
	 * in order to work around limitations in Microsoft's driver.
	 * We need to make sure we only bind to one of them.
	 *
	 * This code assumes two things:
	 *
	 * 1. The PCI code adds subfunctions in order.
	 *
	 * 2. The MMC पूर्णांकerface has a lower subfunction number
	 *    than the SD पूर्णांकerface.
	 */
	अगर (chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_SD)
		mmcdev = PCI_DEVICE_ID_JMICRON_JMB38X_MMC;
	अन्यथा अगर (chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_SD)
		mmcdev = PCI_DEVICE_ID_JMICRON_JMB388_ESD;

	अगर (mmcdev) अणु
		काष्ठा pci_dev *sd_dev;

		sd_dev = शून्य;
		जबतक ((sd_dev = pci_get_device(PCI_VENDOR_ID_JMICRON,
						mmcdev, sd_dev)) != शून्य) अणु
			अगर ((PCI_SLOT(chip->pdev->devfn) ==
				PCI_SLOT(sd_dev->devfn)) &&
				(chip->pdev->bus == sd_dev->bus))
				अवरोध;
		पूर्ण

		अगर (sd_dev) अणु
			pci_dev_put(sd_dev);
			dev_info(&chip->pdev->dev, "Refusing to bind to "
				"secondary interface.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * JMicron chips need a bit of a nudge to enable the घातer
	 * output pins.
	 */
	ret = jmicron_pmos(chip, 1);
	अगर (ret) अणु
		dev_err(&chip->pdev->dev, "Failure enabling card power\n");
		वापस ret;
	पूर्ण

	/* quirk क्रम unsable RO-detection on JM388 chips */
	अगर (chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_SD ||
	    chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_ESD)
		chip->quirks |= SDHCI_QUIRK_UNSTABLE_RO_DETECT;

	वापस 0;
पूर्ण

अटल व्योम jmicron_enable_mmc(काष्ठा sdhci_host *host, पूर्णांक on)
अणु
	u8 scratch;

	scratch = पढ़ोb(host->ioaddr + 0xC0);

	अगर (on)
		scratch |= 0x01;
	अन्यथा
		scratch &= ~0x01;

	ग_लिखोb(scratch, host->ioaddr + 0xC0);
पूर्ण

अटल पूर्णांक jmicron_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	अगर (slot->chip->pdev->revision == 0) अणु
		u16 version;

		version = पढ़ोl(slot->host->ioaddr + SDHCI_HOST_VERSION);
		version = (version & SDHCI_VENDOR_VER_MASK) >>
			SDHCI_VENDOR_VER_SHIFT;

		/*
		 * Older versions of the chip have lots of nasty glitches
		 * in the ADMA engine. It's best just to aव्योम it
		 * completely.
		 */
		अगर (version < 0xAC)
			slot->host->quirks |= SDHCI_QUIRK_BROKEN_ADMA;
	पूर्ण

	/* JM388 MMC करोesn't support 1.8V जबतक SD supports it */
	अगर (slot->chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_ESD) अणु
		slot->host->ocr_avail_sd = MMC_VDD_32_33 | MMC_VDD_33_34 |
			MMC_VDD_29_30 | MMC_VDD_30_31 |
			MMC_VDD_165_195; /* allow 1.8V */
		slot->host->ocr_avail_mmc = MMC_VDD_32_33 | MMC_VDD_33_34 |
			MMC_VDD_29_30 | MMC_VDD_30_31; /* no 1.8V क्रम MMC */
	पूर्ण

	/*
	 * The secondary पूर्णांकerface requires a bit set to get the
	 * पूर्णांकerrupts.
	 */
	अगर (slot->chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_MMC ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_ESD)
		jmicron_enable_mmc(slot->host, 1);

	slot->host->mmc->caps |= MMC_CAP_BUS_WIDTH_TEST;

	वापस 0;
पूर्ण

अटल व्योम jmicron_हटाओ_slot(काष्ठा sdhci_pci_slot *slot, पूर्णांक dead)
अणु
	अगर (dead)
		वापस;

	अगर (slot->chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_MMC ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_ESD)
		jmicron_enable_mmc(slot->host, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक jmicron_suspend(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक i, ret;

	ret = sdhci_pci_suspend_host(chip);
	अगर (ret)
		वापस ret;

	अगर (chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_MMC ||
	    chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_ESD) अणु
		क्रम (i = 0; i < chip->num_slots; i++)
			jmicron_enable_mmc(chip->slots[i]->host, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jmicron_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret, i;

	अगर (chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB38X_MMC ||
	    chip->pdev->device == PCI_DEVICE_ID_JMICRON_JMB388_ESD) अणु
		क्रम (i = 0; i < chip->num_slots; i++)
			jmicron_enable_mmc(chip->slots[i]->host, 1);
	पूर्ण

	ret = jmicron_pmos(chip, 1);
	अगर (ret) अणु
		dev_err(&chip->pdev->dev, "Failure enabling card power\n");
		वापस ret;
	पूर्ण

	वापस sdhci_pci_resume_host(chip);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_jmicron = अणु
	.probe		= jmicron_probe,

	.probe_slot	= jmicron_probe_slot,
	.हटाओ_slot	= jmicron_हटाओ_slot,

#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= jmicron_suspend,
	.resume		= jmicron_resume,
#पूर्ण_अगर
पूर्ण;

/* SysKonnect CardBus2SDIO extra रेजिस्टरs */
#घोषणा SYSKT_CTRL		0x200
#घोषणा SYSKT_RDFIFO_STAT	0x204
#घोषणा SYSKT_WRFIFO_STAT	0x208
#घोषणा SYSKT_POWER_DATA	0x20c
#घोषणा   SYSKT_POWER_330	0xef
#घोषणा   SYSKT_POWER_300	0xf8
#घोषणा   SYSKT_POWER_184	0xcc
#घोषणा SYSKT_POWER_CMD		0x20d
#घोषणा   SYSKT_POWER_START	(1 << 7)
#घोषणा SYSKT_POWER_STATUS	0x20e
#घोषणा   SYSKT_POWER_STATUS_OK	(1 << 0)
#घोषणा SYSKT_BOARD_REV		0x210
#घोषणा SYSKT_CHIP_REV		0x211
#घोषणा SYSKT_CONF_DATA		0x212
#घोषणा   SYSKT_CONF_DATA_1V8	(1 << 2)
#घोषणा   SYSKT_CONF_DATA_2V5	(1 << 1)
#घोषणा   SYSKT_CONF_DATA_3V3	(1 << 0)

अटल पूर्णांक syskt_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	अगर ((chip->pdev->class & 0x0000FF) == PCI_SDHCI_IFVENDOR) अणु
		chip->pdev->class &= ~0x0000FF;
		chip->pdev->class |= PCI_SDHCI_IFDMA;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक syskt_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक पंचांग, ps;

	u8 board_rev = पढ़ोb(slot->host->ioaddr + SYSKT_BOARD_REV);
	u8  chip_rev = पढ़ोb(slot->host->ioaddr + SYSKT_CHIP_REV);
	dev_info(&slot->chip->pdev->dev, "SysKonnect CardBus2SDIO, "
					 "board rev %d.%d, chip rev %d.%d\n",
					 board_rev >> 4, board_rev & 0xf,
					 chip_rev >> 4,  chip_rev & 0xf);
	अगर (chip_rev >= 0x20)
		slot->host->quirks |= SDHCI_QUIRK_FORCE_DMA;

	ग_लिखोb(SYSKT_POWER_330, slot->host->ioaddr + SYSKT_POWER_DATA);
	ग_लिखोb(SYSKT_POWER_START, slot->host->ioaddr + SYSKT_POWER_CMD);
	udelay(50);
	पंचांग = 10;  /* Wait max 1 ms */
	करो अणु
		ps = पढ़ोw(slot->host->ioaddr + SYSKT_POWER_STATUS);
		अगर (ps & SYSKT_POWER_STATUS_OK)
			अवरोध;
		udelay(100);
	पूर्ण जबतक (--पंचांग);
	अगर (!पंचांग) अणु
		dev_err(&slot->chip->pdev->dev,
			"power regulator never stabilized");
		ग_लिखोb(0, slot->host->ioaddr + SYSKT_POWER_CMD);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_syskt = अणु
	.quirks		= SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER,
	.probe		= syskt_probe,
	.probe_slot	= syskt_probe_slot,
पूर्ण;

अटल पूर्णांक via_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	अगर (chip->pdev->revision == 0x10)
		chip->quirks |= SDHCI_QUIRK_DELAY_AFTER_POWER;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_via = अणु
	.probe		= via_probe,
पूर्ण;

अटल पूर्णांक rtsx_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	slot->host->mmc->caps2 |= MMC_CAP2_HS200;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_rtsx = अणु
	.quirks2	= SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
			SDHCI_QUIRK2_BROKEN_64_BIT_DMA |
			SDHCI_QUIRK2_BROKEN_DDR50,
	.probe_slot	= rtsx_probe_slot,
पूर्ण;

/*AMD chipset generation*/
क्रमागत amd_chipset_gen अणु
	AMD_CHIPSET_BEFORE_ML,
	AMD_CHIPSET_CZ,
	AMD_CHIPSET_NL,
	AMD_CHIPSET_UNKNOWN,
पूर्ण;

/* AMD रेजिस्टरs */
#घोषणा AMD_SD_AUTO_PATTERN		0xB8
#घोषणा AMD_MSLEEP_DURATION		4
#घोषणा AMD_SD_MISC_CONTROL		0xD0
#घोषणा AMD_MAX_TUNE_VALUE		0x0B
#घोषणा AMD_AUTO_TUNE_SEL		0x10800
#घोषणा AMD_FIFO_PTR			0x30
#घोषणा AMD_BIT_MASK			0x1F

अटल व्योम amd_tuning_reset(काष्ठा sdhci_host *host)
अणु
	अचिन्हित पूर्णांक val;

	val = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	val |= SDHCI_CTRL_PRESET_VAL_ENABLE | SDHCI_CTRL_EXEC_TUNING;
	sdhci_ग_लिखोw(host, val, SDHCI_HOST_CONTROL2);

	val = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	val &= ~SDHCI_CTRL_EXEC_TUNING;
	sdhci_ग_लिखोw(host, val, SDHCI_HOST_CONTROL2);
पूर्ण

अटल व्योम amd_config_tuning_phase(काष्ठा pci_dev *pdev, u8 phase)
अणु
	अचिन्हित पूर्णांक val;

	pci_पढ़ो_config_dword(pdev, AMD_SD_AUTO_PATTERN, &val);
	val &= ~AMD_BIT_MASK;
	val |= (AMD_AUTO_TUNE_SEL | (phase << 1));
	pci_ग_लिखो_config_dword(pdev, AMD_SD_AUTO_PATTERN, val);
पूर्ण

अटल व्योम amd_enable_manual_tuning(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;

	pci_पढ़ो_config_dword(pdev, AMD_SD_MISC_CONTROL, &val);
	val |= AMD_FIFO_PTR;
	pci_ग_लिखो_config_dword(pdev, AMD_SD_MISC_CONTROL, val);
पूर्ण

अटल पूर्णांक amd_execute_tuning_hs200(काष्ठा sdhci_host *host, u32 opcode)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा pci_dev *pdev = slot->chip->pdev;
	u8 valid_win = 0;
	u8 valid_win_max = 0;
	u8 valid_win_end = 0;
	u8 ctrl, tune_around;

	amd_tuning_reset(host);

	क्रम (tune_around = 0; tune_around < 12; tune_around++) अणु
		amd_config_tuning_phase(pdev, tune_around);

		अगर (mmc_send_tuning(host->mmc, opcode, शून्य)) अणु
			valid_win = 0;
			msleep(AMD_MSLEEP_DURATION);
			ctrl = SDHCI_RESET_CMD | SDHCI_RESET_DATA;
			sdhci_ग_लिखोb(host, ctrl, SDHCI_SOFTWARE_RESET);
		पूर्ण अन्यथा अगर (++valid_win > valid_win_max) अणु
			valid_win_max = valid_win;
			valid_win_end = tune_around;
		पूर्ण
	पूर्ण

	अगर (!valid_win_max) अणु
		dev_err(&pdev->dev, "no tuning point found\n");
		वापस -EIO;
	पूर्ण

	amd_config_tuning_phase(pdev, valid_win_end - valid_win_max / 2);

	amd_enable_manual_tuning(pdev);

	host->mmc->retune_period = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक amd_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	/* AMD requires custom HS200 tuning */
	अगर (host->timing == MMC_TIMING_MMC_HS200)
		वापस amd_execute_tuning_hs200(host, opcode);

	/* Otherwise perक्रमm standard SDHCI tuning */
	वापस sdhci_execute_tuning(mmc, opcode);
पूर्ण

अटल पूर्णांक amd_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा mmc_host_ops *ops = &slot->host->mmc_host_ops;

	ops->execute_tuning = amd_execute_tuning;

	वापस 0;
पूर्ण

अटल पूर्णांक amd_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा pci_dev	*smbus_dev;
	क्रमागत amd_chipset_gen gen;

	smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
			PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, शून्य);
	अगर (smbus_dev) अणु
		gen = AMD_CHIPSET_BEFORE_ML;
	पूर्ण अन्यथा अणु
		smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
				PCI_DEVICE_ID_AMD_KERNCZ_SMBUS, शून्य);
		अगर (smbus_dev) अणु
			अगर (smbus_dev->revision < 0x51)
				gen = AMD_CHIPSET_CZ;
			अन्यथा
				gen = AMD_CHIPSET_NL;
		पूर्ण अन्यथा अणु
			gen = AMD_CHIPSET_UNKNOWN;
		पूर्ण
	पूर्ण

	अगर (gen == AMD_CHIPSET_BEFORE_ML || gen == AMD_CHIPSET_CZ)
		chip->quirks2 |= SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD;

	वापस 0;
पूर्ण

अटल u32 sdhci_पढ़ो_present_state(काष्ठा sdhci_host *host)
अणु
	वापस sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
पूर्ण

अटल व्योम amd_sdhci_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा pci_dev *pdev = slot->chip->pdev;
	u32 present_state;

	/*
	 * SDHC 0x7906 requires a hard reset to clear all पूर्णांकernal state.
	 * Otherwise it can get पूर्णांकo a bad state where the DATA lines are always
	 * पढ़ो as zeros.
	 */
	अगर (pdev->device == 0x7906 && (mask & SDHCI_RESET_ALL)) अणु
		pci_clear_master(pdev);

		pci_save_state(pdev);

		pci_set_घातer_state(pdev, PCI_D3cold);
		pr_debug("%s: power_state=%u\n", mmc_hostname(host->mmc),
			pdev->current_state);
		pci_set_घातer_state(pdev, PCI_D0);

		pci_restore_state(pdev);

		/*
		 * SDHCI_RESET_ALL says the card detect logic should not be
		 * reset, but since we need to reset the entire controller
		 * we should रुको until the card detect logic has stabilized.
		 *
		 * This normally takes about 40ms.
		 */
		पढ़ोx_poll_समयout(
			sdhci_पढ़ो_present_state,
			host,
			present_state,
			present_state & SDHCI_CD_STABLE,
			10000,
			100000
		);
	पूर्ण

	वापस sdhci_reset(host, mask);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops amd_sdhci_pci_ops = अणु
	.set_घड़ी			= sdhci_set_घड़ी,
	.enable_dma			= sdhci_pci_enable_dma,
	.set_bus_width			= sdhci_set_bus_width,
	.reset				= amd_sdhci_reset,
	.set_uhs_संकेतing		= sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pci_fixes sdhci_amd = अणु
	.probe		= amd_probe,
	.ops		= &amd_sdhci_pci_ops,
	.probe_slot	= amd_probe_slot,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	SDHCI_PCI_DEVICE(RICOH, R5C822,  ricoh),
	SDHCI_PCI_DEVICE(RICOH, R5C843,  ricoh_mmc),
	SDHCI_PCI_DEVICE(RICOH, R5CE822, ricoh_mmc),
	SDHCI_PCI_DEVICE(RICOH, R5CE823, ricoh_mmc),
	SDHCI_PCI_DEVICE(ENE, CB712_SD,   ene_712),
	SDHCI_PCI_DEVICE(ENE, CB712_SD_2, ene_712),
	SDHCI_PCI_DEVICE(ENE, CB714_SD,   ene_714),
	SDHCI_PCI_DEVICE(ENE, CB714_SD_2, ene_714),
	SDHCI_PCI_DEVICE(MARVELL, 88ALP01_SD, cafe),
	SDHCI_PCI_DEVICE(JMICRON, JMB38X_SD,  jmicron),
	SDHCI_PCI_DEVICE(JMICRON, JMB38X_MMC, jmicron),
	SDHCI_PCI_DEVICE(JMICRON, JMB388_SD,  jmicron),
	SDHCI_PCI_DEVICE(JMICRON, JMB388_ESD, jmicron),
	SDHCI_PCI_DEVICE(SYSKONNECT, 8000, syskt),
	SDHCI_PCI_DEVICE(VIA, 95D0, via),
	SDHCI_PCI_DEVICE(REALTEK, 5250, rtsx),
	SDHCI_PCI_DEVICE(INTEL, QRK_SD,    पूर्णांकel_qrk),
	SDHCI_PCI_DEVICE(INTEL, MRST_SD0,  पूर्णांकel_mrst_hc0),
	SDHCI_PCI_DEVICE(INTEL, MRST_SD1,  पूर्णांकel_mrst_hc1_hc2),
	SDHCI_PCI_DEVICE(INTEL, MRST_SD2,  पूर्णांकel_mrst_hc1_hc2),
	SDHCI_PCI_DEVICE(INTEL, MFD_SD,    पूर्णांकel_mfd_sd),
	SDHCI_PCI_DEVICE(INTEL, MFD_SDIO1, पूर्णांकel_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEL, MFD_SDIO2, पूर्णांकel_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEL, MFD_EMMC0, पूर्णांकel_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEL, MFD_EMMC1, पूर्णांकel_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEL, PCH_SDIO0, पूर्णांकel_pch_sdio),
	SDHCI_PCI_DEVICE(INTEL, PCH_SDIO1, पूर्णांकel_pch_sdio),
	SDHCI_PCI_DEVICE(INTEL, BYT_EMMC,  पूर्णांकel_byt_emmc),
	SDHCI_PCI_SUBDEVICE(INTEL, BYT_SDIO, NI, 7884, ni_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, BYT_SDIO,  पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, BYT_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, BYT_EMMC2, पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, BSW_EMMC,  पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, BSW_SDIO,  पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, BSW_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, CLV_SDIO0, पूर्णांकel_mfd_sd),
	SDHCI_PCI_DEVICE(INTEL, CLV_SDIO1, पूर्णांकel_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEL, CLV_SDIO2, पूर्णांकel_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEL, CLV_EMMC0, पूर्णांकel_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEL, CLV_EMMC1, पूर्णांकel_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEL, MRFLD_MMC, पूर्णांकel_mrfld_mmc),
	SDHCI_PCI_DEVICE(INTEL, SPT_EMMC,  पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, SPT_SDIO,  पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, SPT_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, DNV_EMMC,  पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, CDF_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, BXT_EMMC,  पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, BXT_SDIO,  पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, BXT_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, BXTM_EMMC, पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, BXTM_SDIO, पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, BXTM_SD,   पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, APL_EMMC,  पूर्णांकel_byt_emmc),
	SDHCI_PCI_DEVICE(INTEL, APL_SDIO,  पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, APL_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, GLK_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, GLK_SDIO,  पूर्णांकel_byt_sdio),
	SDHCI_PCI_DEVICE(INTEL, GLK_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, CNP_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, CNP_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, CNPH_SD,   पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, ICP_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, ICP_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, EHL_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, EHL_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, CML_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, CML_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, CMLH_SD,   पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, JSL_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, JSL_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(INTEL, LKF_EMMC,  पूर्णांकel_glk_emmc),
	SDHCI_PCI_DEVICE(INTEL, LKF_SD,    पूर्णांकel_byt_sd),
	SDHCI_PCI_DEVICE(O2, 8120,     o2),
	SDHCI_PCI_DEVICE(O2, 8220,     o2),
	SDHCI_PCI_DEVICE(O2, 8221,     o2),
	SDHCI_PCI_DEVICE(O2, 8320,     o2),
	SDHCI_PCI_DEVICE(O2, 8321,     o2),
	SDHCI_PCI_DEVICE(O2, FUJIN2,   o2),
	SDHCI_PCI_DEVICE(O2, SDS0,     o2),
	SDHCI_PCI_DEVICE(O2, SDS1,     o2),
	SDHCI_PCI_DEVICE(O2, SEABIRD0, o2),
	SDHCI_PCI_DEVICE(O2, SEABIRD1, o2),
	SDHCI_PCI_DEVICE(ARASAN, PHY_EMMC, arasan),
	SDHCI_PCI_DEVICE(SYNOPSYS, DWC_MSHC, snps),
	SDHCI_PCI_DEVICE(GLI, 9750, gl9750),
	SDHCI_PCI_DEVICE(GLI, 9755, gl9755),
	SDHCI_PCI_DEVICE(GLI, 9763E, gl9763e),
	SDHCI_PCI_DEVICE_CLASS(AMD, SYSTEM_SDHCI, PCI_CLASS_MASK, amd),
	/* Generic SD host controller */
	अणुPCI_DEVICE_CLASS(SYSTEM_SDHCI, PCI_CLASS_MASK)पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_ids);

/*****************************************************************************\
 *                                                                           *
 * SDHCI core callbacks                                                      *
 *                                                                           *
\*****************************************************************************/

पूर्णांक sdhci_pci_enable_dma(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pci_slot *slot;
	काष्ठा pci_dev *pdev;

	slot = sdhci_priv(host);
	pdev = slot->chip->pdev;

	अगर (((pdev->class & 0xFFFF00) == (PCI_CLASS_SYSTEM_SDHCI << 8)) &&
		((pdev->class & 0x0000FF) != PCI_SDHCI_IFDMA) &&
		(host->flags & SDHCI_USE_SDMA)) अणु
		dev_warn(&pdev->dev, "Will use DMA mode even though HW "
			"doesn't fully claim to support it.\n");
	पूर्ण

	pci_set_master(pdev);

	वापस 0;
पूर्ण

अटल व्योम sdhci_pci_gpio_hw_reset(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	पूर्णांक rst_n_gpio = slot->rst_n_gpio;

	अगर (!gpio_is_valid(rst_n_gpio))
		वापस;
	gpio_set_value_cansleep(rst_n_gpio, 0);
	/* For eMMC, minimum is 1us but give it 10us क्रम good measure */
	udelay(10);
	gpio_set_value_cansleep(rst_n_gpio, 1);
	/* For eMMC, minimum is 200us but give it 300us क्रम good measure */
	usleep_range(300, 1000);
पूर्ण

अटल व्योम sdhci_pci_hw_reset(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);

	अगर (slot->hw_reset)
		slot->hw_reset(host);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_pci_ops = अणु
	.set_घड़ी	= sdhci_set_घड़ी,
	.enable_dma	= sdhci_pci_enable_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.reset		= sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.hw_reset		= sdhci_pci_hw_reset,
पूर्ण;

/*****************************************************************************\
 *                                                                           *
 * Suspend/resume                                                            *
 *                                                                           *
\*****************************************************************************/

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_pci_chip *chip = dev_get_drvdata(dev);

	अगर (!chip)
		वापस 0;

	अगर (chip->fixes && chip->fixes->suspend)
		वापस chip->fixes->suspend(chip);

	वापस sdhci_pci_suspend_host(chip);
पूर्ण

अटल पूर्णांक sdhci_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_pci_chip *chip = dev_get_drvdata(dev);

	अगर (!chip)
		वापस 0;

	अगर (chip->fixes && chip->fixes->resume)
		वापस chip->fixes->resume(chip);

	वापस sdhci_pci_resume_host(chip);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_pci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_pci_chip *chip = dev_get_drvdata(dev);

	अगर (!chip)
		वापस 0;

	अगर (chip->fixes && chip->fixes->runसमय_suspend)
		वापस chip->fixes->runसमय_suspend(chip);

	वापस sdhci_pci_runसमय_suspend_host(chip);
पूर्ण

अटल पूर्णांक sdhci_pci_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_pci_chip *chip = dev_get_drvdata(dev);

	अगर (!chip)
		वापस 0;

	अगर (chip->fixes && chip->fixes->runसमय_resume)
		वापस chip->fixes->runसमय_resume(chip);

	वापस sdhci_pci_runसमय_resume_host(chip);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_pci_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_pci_suspend, sdhci_pci_resume)
	SET_RUNTIME_PM_OPS(sdhci_pci_runसमय_suspend,
			sdhci_pci_runसमय_resume, शून्य)
पूर्ण;

/*****************************************************************************\
 *                                                                           *
 * Device probing/removal                                                    *
 *                                                                           *
\*****************************************************************************/

अटल काष्ठा sdhci_pci_slot *sdhci_pci_probe_slot(
	काष्ठा pci_dev *pdev, काष्ठा sdhci_pci_chip *chip, पूर्णांक first_bar,
	पूर्णांक slotno)
अणु
	काष्ठा sdhci_pci_slot *slot;
	काष्ठा sdhci_host *host;
	पूर्णांक ret, bar = first_bar + slotno;
	माप_प्रकार priv_size = chip->fixes ? chip->fixes->priv_size : 0;

	अगर (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "BAR %d is not iomem. Aborting.\n", bar);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (pci_resource_len(pdev, bar) < 0x100) अणु
		dev_err(&pdev->dev, "Invalid iomem size. You may "
			"experience problems.\n");
	पूर्ण

	अगर ((pdev->class & 0x0000FF) == PCI_SDHCI_IFVENDOR) अणु
		dev_err(&pdev->dev, "Vendor specific interface. Aborting.\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर ((pdev->class & 0x0000FF) > PCI_SDHCI_IFVENDOR) अणु
		dev_err(&pdev->dev, "Unknown interface. Aborting.\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	host = sdhci_alloc_host(&pdev->dev, माप(*slot) + priv_size);
	अगर (IS_ERR(host)) अणु
		dev_err(&pdev->dev, "cannot allocate host\n");
		वापस ERR_CAST(host);
	पूर्ण

	slot = sdhci_priv(host);

	slot->chip = chip;
	slot->host = host;
	slot->rst_n_gpio = -EINVAL;
	slot->cd_gpio = -EINVAL;
	slot->cd_idx = -1;

	/* Retrieve platक्रमm data अगर there is any */
	अगर (*sdhci_pci_get_data)
		slot->data = sdhci_pci_get_data(pdev, slotno);

	अगर (slot->data) अणु
		अगर (slot->data->setup) अणु
			ret = slot->data->setup(slot->data);
			अगर (ret) अणु
				dev_err(&pdev->dev, "platform setup failed\n");
				जाओ मुक्त;
			पूर्ण
		पूर्ण
		slot->rst_n_gpio = slot->data->rst_n_gpio;
		slot->cd_gpio = slot->data->cd_gpio;
	पूर्ण

	host->hw_name = "PCI";
	host->ops = chip->fixes && chip->fixes->ops ?
		    chip->fixes->ops :
		    &sdhci_pci_ops;
	host->quirks = chip->quirks;
	host->quirks2 = chip->quirks2;

	host->irq = pdev->irq;

	ret = pcim_iomap_regions(pdev, BIT(bar), mmc_hostname(host->mmc));
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot request region\n");
		जाओ cleanup;
	पूर्ण

	host->ioaddr = pcim_iomap_table(pdev)[bar];

	अगर (chip->fixes && chip->fixes->probe_slot) अणु
		ret = chip->fixes->probe_slot(slot);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	अगर (gpio_is_valid(slot->rst_n_gpio)) अणु
		अगर (!devm_gpio_request(&pdev->dev, slot->rst_n_gpio, "eMMC_reset")) अणु
			gpio_direction_output(slot->rst_n_gpio, 1);
			slot->host->mmc->caps |= MMC_CAP_HW_RESET;
			slot->hw_reset = sdhci_pci_gpio_hw_reset;
		पूर्ण अन्यथा अणु
			dev_warn(&pdev->dev, "failed to request rst_n_gpio\n");
			slot->rst_n_gpio = -EINVAL;
		पूर्ण
	पूर्ण

	host->mmc->pm_caps = MMC_PM_KEEP_POWER;
	host->mmc->slotno = slotno;
	host->mmc->caps2 |= MMC_CAP2_NO_PRESCAN_POWERUP;

	अगर (device_can_wakeup(&pdev->dev))
		host->mmc->pm_caps |= MMC_PM_WAKE_SDIO_IRQ;

	अगर (host->mmc->caps & MMC_CAP_CD_WAKE)
		device_init_wakeup(&pdev->dev, true);

	अगर (slot->cd_idx >= 0) अणु
		ret = mmc_gpiod_request_cd(host->mmc, "cd", slot->cd_idx,
					   slot->cd_override_level, 0);
		अगर (ret && ret != -EPROBE_DEFER)
			ret = mmc_gpiod_request_cd(host->mmc, शून्य,
						   slot->cd_idx,
						   slot->cd_override_level,
						   0);
		अगर (ret == -EPROBE_DEFER)
			जाओ हटाओ;

		अगर (ret) अणु
			dev_warn(&pdev->dev, "failed to setup card detect gpio\n");
			slot->cd_idx = -1;
		पूर्ण
	पूर्ण

	अगर (chip->fixes && chip->fixes->add_host)
		ret = chip->fixes->add_host(slot);
	अन्यथा
		ret = sdhci_add_host(host);
	अगर (ret)
		जाओ हटाओ;

	sdhci_pci_add_own_cd(slot);

	/*
	 * Check अगर the chip needs a separate GPIO क्रम card detect to wake up
	 * from runसमय suspend.  If it is not there, करोn't allow runसमय PM.
	 * Note sdhci_pci_add_own_cd() sets slot->cd_gpio to -EINVAL on failure.
	 */
	अगर (chip->fixes && chip->fixes->own_cd_क्रम_runसमय_pm &&
	    !gpio_is_valid(slot->cd_gpio) && slot->cd_idx < 0)
		chip->allow_runसमय_pm = false;

	वापस slot;

हटाओ:
	अगर (chip->fixes && chip->fixes->हटाओ_slot)
		chip->fixes->हटाओ_slot(slot, 0);

cleanup:
	अगर (slot->data && slot->data->cleanup)
		slot->data->cleanup(slot->data);

मुक्त:
	sdhci_मुक्त_host(host);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम sdhci_pci_हटाओ_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक dead;
	u32 scratch;

	sdhci_pci_हटाओ_own_cd(slot);

	dead = 0;
	scratch = पढ़ोl(slot->host->ioaddr + SDHCI_INT_STATUS);
	अगर (scratch == (u32)-1)
		dead = 1;

	sdhci_हटाओ_host(slot->host, dead);

	अगर (slot->chip->fixes && slot->chip->fixes->हटाओ_slot)
		slot->chip->fixes->हटाओ_slot(slot, dead);

	अगर (slot->data && slot->data->cleanup)
		slot->data->cleanup(slot->data);

	sdhci_मुक्त_host(slot->host);
पूर्ण

अटल व्योम sdhci_pci_runसमय_pm_allow(काष्ठा device *dev)
अणु
	pm_suspend_ignore_children(dev, 1);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 50);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_allow(dev);
	/* Stay active until mmc core scans क्रम a card */
	pm_runसमय_put_noidle(dev);
पूर्ण

अटल व्योम sdhci_pci_runसमय_pm_क्रमbid(काष्ठा device *dev)
अणु
	pm_runसमय_क्रमbid(dev);
	pm_runसमय_get_noresume(dev);
पूर्ण

अटल पूर्णांक sdhci_pci_probe(काष्ठा pci_dev *pdev,
				     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sdhci_pci_chip *chip;
	काष्ठा sdhci_pci_slot *slot;

	u8 slots, first_bar;
	पूर्णांक ret, i;

	BUG_ON(pdev == शून्य);
	BUG_ON(ent == शून्य);

	dev_info(&pdev->dev, "SDHCI controller found [%04x:%04x] (rev %x)\n",
		 (पूर्णांक)pdev->venकरोr, (पूर्णांक)pdev->device, (पूर्णांक)pdev->revision);

	ret = pci_पढ़ो_config_byte(pdev, PCI_SLOT_INFO, &slots);
	अगर (ret)
		वापस ret;

	slots = PCI_SLOT_INFO_SLOTS(slots) + 1;
	dev_dbg(&pdev->dev, "found %d slot(s)\n", slots);

	BUG_ON(slots > MAX_SLOTS);

	ret = pci_पढ़ो_config_byte(pdev, PCI_SLOT_INFO, &first_bar);
	अगर (ret)
		वापस ret;

	first_bar &= PCI_SLOT_INFO_FIRST_BAR_MASK;

	अगर (first_bar > 5) अणु
		dev_err(&pdev->dev, "Invalid first BAR. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->pdev = pdev;
	chip->fixes = (स्थिर काष्ठा sdhci_pci_fixes *)ent->driver_data;
	अगर (chip->fixes) अणु
		chip->quirks = chip->fixes->quirks;
		chip->quirks2 = chip->fixes->quirks2;
		chip->allow_runसमय_pm = chip->fixes->allow_runसमय_pm;
	पूर्ण
	chip->num_slots = slots;
	chip->pm_retune = true;
	chip->rpm_retune = true;

	pci_set_drvdata(pdev, chip);

	अगर (chip->fixes && chip->fixes->probe) अणु
		ret = chip->fixes->probe(chip);
		अगर (ret)
			वापस ret;
	पूर्ण

	slots = chip->num_slots;	/* Quirk may have changed this */

	क्रम (i = 0; i < slots; i++) अणु
		slot = sdhci_pci_probe_slot(pdev, chip, first_bar, i);
		अगर (IS_ERR(slot)) अणु
			क्रम (i--; i >= 0; i--)
				sdhci_pci_हटाओ_slot(chip->slots[i]);
			वापस PTR_ERR(slot);
		पूर्ण

		chip->slots[i] = slot;
	पूर्ण

	अगर (chip->allow_runसमय_pm)
		sdhci_pci_runसमय_pm_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम sdhci_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा sdhci_pci_chip *chip = pci_get_drvdata(pdev);

	अगर (chip->allow_runसमय_pm)
		sdhci_pci_runसमय_pm_क्रमbid(&pdev->dev);

	क्रम (i = 0; i < chip->num_slots; i++)
		sdhci_pci_हटाओ_slot(chip->slots[i]);
पूर्ण

अटल काष्ठा pci_driver sdhci_driver = अणु
	.name =		"sdhci-pci",
	.id_table =	pci_ids,
	.probe =	sdhci_pci_probe,
	.हटाओ =	sdhci_pci_हटाओ,
	.driver =	अणु
		.pm =   &sdhci_pci_pm_ops
	पूर्ण,
पूर्ण;

module_pci_driver(sdhci_driver);

MODULE_AUTHOR("Pierre Ossman <pierre@ossman.eu>");
MODULE_DESCRIPTION("Secure Digital Host Controller Interface PCI driver");
MODULE_LICENSE("GPL");
