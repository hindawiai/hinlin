<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Secure Digital Host Controller Interface ACPI driver.
 *
 * Copyright (c) 2012, Intel Corporation.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/compiler.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/pm.h>
#समावेश <linux/mmc/slot-gpपन.स>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/iosf_mbi.h>
#समावेश <linux/pci.h>
#पूर्ण_अगर

#समावेश "sdhci.h"

क्रमागत अणु
	SDHCI_ACPI_SD_CD		= BIT(0),
	SDHCI_ACPI_RUNTIME_PM		= BIT(1),
	SDHCI_ACPI_SD_CD_OVERRIDE_LEVEL	= BIT(2),
पूर्ण;

काष्ठा sdhci_acpi_chip अणु
	स्थिर काष्ठा	sdhci_ops *ops;
	अचिन्हित पूर्णांक	quirks;
	अचिन्हित पूर्णांक	quirks2;
	अचिन्हित दीर्घ	caps;
	अचिन्हित पूर्णांक	caps2;
	mmc_pm_flag_t	pm_caps;
पूर्ण;

काष्ठा sdhci_acpi_slot अणु
	स्थिर काष्ठा	sdhci_acpi_chip *chip;
	अचिन्हित पूर्णांक	quirks;
	अचिन्हित पूर्णांक	quirks2;
	अचिन्हित दीर्घ	caps;
	अचिन्हित पूर्णांक	caps2;
	mmc_pm_flag_t	pm_caps;
	अचिन्हित पूर्णांक	flags;
	माप_प्रकार		priv_size;
	पूर्णांक (*probe_slot)(काष्ठा platक्रमm_device *, काष्ठा acpi_device *);
	पूर्णांक (*हटाओ_slot)(काष्ठा platक्रमm_device *);
	पूर्णांक (*मुक्त_slot)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*setup_host)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

काष्ठा sdhci_acpi_host अणु
	काष्ठा sdhci_host		*host;
	स्थिर काष्ठा sdhci_acpi_slot	*slot;
	काष्ठा platक्रमm_device		*pdev;
	bool				use_runसमय_pm;
	bool				is_पूर्णांकel;
	bool				reset_संकेत_volt_on_suspend;
	अचिन्हित दीर्घ			निजी[] ____cacheline_aligned;
पूर्ण;

क्रमागत अणु
	DMI_QUIRK_RESET_SD_SIGNAL_VOLT_ON_SUSP			= BIT(0),
	DMI_QUIRK_SD_NO_WRITE_PROTECT				= BIT(1),
पूर्ण;

अटल अंतरभूत व्योम *sdhci_acpi_priv(काष्ठा sdhci_acpi_host *c)
अणु
	वापस (व्योम *)c->निजी;
पूर्ण

अटल अंतरभूत bool sdhci_acpi_flag(काष्ठा sdhci_acpi_host *c, अचिन्हित पूर्णांक flag)
अणु
	वापस c->slot && (c->slot->flags & flag);
पूर्ण

#घोषणा INTEL_DSM_HS_CAPS_SDR25		BIT(0)
#घोषणा INTEL_DSM_HS_CAPS_DDR50		BIT(1)
#घोषणा INTEL_DSM_HS_CAPS_SDR50		BIT(2)
#घोषणा INTEL_DSM_HS_CAPS_SDR104	BIT(3)

क्रमागत अणु
	INTEL_DSM_FNS		=  0,
	INTEL_DSM_V18_SWITCH	=  3,
	INTEL_DSM_V33_SWITCH	=  4,
	INTEL_DSM_HS_CAPS	=  8,
पूर्ण;

काष्ठा पूर्णांकel_host अणु
	u32	dsm_fns;
	u32	hs_caps;
पूर्ण;

अटल स्थिर guid_t पूर्णांकel_dsm_guid =
	GUID_INIT(0xF6C13EA5, 0x65CD, 0x461F,
		  0xAB, 0x7A, 0x29, 0xF7, 0xE8, 0xD5, 0xBD, 0x61);

अटल पूर्णांक __पूर्णांकel_dsm(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev,
		       अचिन्हित पूर्णांक fn, u32 *result)
अणु
	जोड़ acpi_object *obj;
	पूर्णांक err = 0;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), &पूर्णांकel_dsm_guid, 0, fn, शून्य);
	अगर (!obj)
		वापस -EOPNOTSUPP;

	अगर (obj->type == ACPI_TYPE_INTEGER) अणु
		*result = obj->पूर्णांकeger.value;
	पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_BUFFER && obj->buffer.length > 0) अणु
		माप_प्रकार len = min_t(माप_प्रकार, obj->buffer.length, 4);

		*result = 0;
		स_नकल(result, obj->buffer.poपूर्णांकer, len);
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s DSM fn %u obj->type %d obj->buffer.length %d\n",
			__func__, fn, obj->type, obj->buffer.length);
		err = -EINVAL;
	पूर्ण

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

	पूर्णांकel_host->hs_caps = ~0;

	err = __पूर्णांकel_dsm(पूर्णांकel_host, dev, INTEL_DSM_FNS, &पूर्णांकel_host->dsm_fns);
	अगर (err) अणु
		pr_debug("%s: DSM not supported, error %d\n",
			 mmc_hostname(mmc), err);
		वापस;
	पूर्ण

	pr_debug("%s: DSM function mask %#x\n",
		 mmc_hostname(mmc), पूर्णांकel_host->dsm_fns);

	पूर्णांकel_dsm(पूर्णांकel_host, dev, INTEL_DSM_HS_CAPS, &पूर्णांकel_host->hs_caps);
पूर्ण

अटल पूर्णांक पूर्णांकel_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
					     काष्ठा mmc_ios *ios)
अणु
	काष्ठा device *dev = mmc_dev(mmc);
	काष्ठा sdhci_acpi_host *c = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_acpi_priv(c);
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

अटल व्योम sdhci_acpi_पूर्णांक_hw_reset(काष्ठा sdhci_host *host)
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

अटल स्थिर काष्ठा sdhci_ops sdhci_acpi_ops_dflt = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_acpi_ops_पूर्णांक = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.hw_reset   = sdhci_acpi_पूर्णांक_hw_reset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_chip sdhci_acpi_chip_पूर्णांक = अणु
	.ops = &sdhci_acpi_ops_पूर्णांक,
पूर्ण;

#अगर_घोषित CONFIG_X86

अटल bool sdhci_acpi_byt(व्योम)
अणु
	अटल स्थिर काष्ठा x86_cpu_id byt[] = अणु
		X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT, शून्य),
		अणुपूर्ण
	पूर्ण;

	वापस x86_match_cpu(byt);
पूर्ण

अटल bool sdhci_acpi_cht(व्योम)
अणु
	अटल स्थिर काष्ठा x86_cpu_id cht[] = अणु
		X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT, शून्य),
		अणुपूर्ण
	पूर्ण;

	वापस x86_match_cpu(cht);
पूर्ण

#घोषणा BYT_IOSF_SCCEP			0x63
#घोषणा BYT_IOSF_OCP_NETCTRL0		0x1078
#घोषणा BYT_IOSF_OCP_TIMEOUT_BASE	GENMASK(10, 8)

अटल व्योम sdhci_acpi_byt_setting(काष्ठा device *dev)
अणु
	u32 val = 0;

	अगर (!sdhci_acpi_byt())
		वापस;

	अगर (iosf_mbi_पढ़ो(BYT_IOSF_SCCEP, MBI_CR_READ, BYT_IOSF_OCP_NETCTRL0,
			  &val)) अणु
		dev_err(dev, "%s read error\n", __func__);
		वापस;
	पूर्ण

	अगर (!(val & BYT_IOSF_OCP_TIMEOUT_BASE))
		वापस;

	val &= ~BYT_IOSF_OCP_TIMEOUT_BASE;

	अगर (iosf_mbi_ग_लिखो(BYT_IOSF_SCCEP, MBI_CR_WRITE, BYT_IOSF_OCP_NETCTRL0,
			   val)) अणु
		dev_err(dev, "%s write error\n", __func__);
		वापस;
	पूर्ण

	dev_dbg(dev, "%s completed\n", __func__);
पूर्ण

अटल bool sdhci_acpi_byt_defer(काष्ठा device *dev)
अणु
	अगर (!sdhci_acpi_byt())
		वापस false;

	अगर (!iosf_mbi_available())
		वापस true;

	sdhci_acpi_byt_setting(dev);

	वापस false;
पूर्ण

अटल bool sdhci_acpi_cht_pci_wअगरi(अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
				    अचिन्हित पूर्णांक slot, अचिन्हित पूर्णांक parent_slot)
अणु
	काष्ठा pci_dev *dev, *parent, *from = शून्य;

	जबतक (1) अणु
		dev = pci_get_device(venकरोr, device, from);
		pci_dev_put(from);
		अगर (!dev)
			अवरोध;
		parent = pci_upstream_bridge(dev);
		अगर (ACPI_COMPANION(&dev->dev) && PCI_SLOT(dev->devfn) == slot &&
		    parent && PCI_SLOT(parent->devfn) == parent_slot &&
		    !pci_upstream_bridge(parent)) अणु
			pci_dev_put(dev);
			वापस true;
		पूर्ण
		from = dev;
	पूर्ण

	वापस false;
पूर्ण

/*
 * GPDwin uses PCI wअगरi which conflicts with SDIO's use of
 * acpi_device_fix_up_घातer() on child device nodes. Identअगरying GPDwin is
 * problematic, but since SDIO is only used क्रम wअगरi, the presence of the PCI
 * wअगरi card in the expected slot with an ACPI companion node, is used to
 * indicate that acpi_device_fix_up_घातer() should be aव्योमed.
 */
अटल अंतरभूत bool sdhci_acpi_no_fixup_child_घातer(काष्ठा acpi_device *adev)
अणु
	वापस sdhci_acpi_cht() &&
	       acpi_dev_hid_uid_match(adev, "80860F14", "2") &&
	       sdhci_acpi_cht_pci_wअगरi(0x14e4, 0x43ec, 0, 28);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम sdhci_acpi_byt_setting(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत bool sdhci_acpi_byt_defer(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool sdhci_acpi_no_fixup_child_घातer(काष्ठा acpi_device *adev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

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

अटल पूर्णांक पूर्णांकel_probe_slot(काष्ठा platक्रमm_device *pdev, काष्ठा acpi_device *adev)
अणु
	काष्ठा sdhci_acpi_host *c = platक्रमm_get_drvdata(pdev);
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_acpi_priv(c);
	काष्ठा sdhci_host *host = c->host;

	अगर (acpi_dev_hid_uid_match(adev, "80860F14", "1") &&
	    sdhci_पढ़ोl(host, SDHCI_CAPABILITIES) == 0x446cc8b2 &&
	    sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1) == 0x00000807)
		host->समयout_clk = 1000; /* 1000 kHz i.e. 1 MHz */

	अगर (acpi_dev_hid_uid_match(adev, "80865ACA", शून्य))
		host->mmc_host_ops.get_cd = bxt_get_cd;

	पूर्णांकel_dsm_init(पूर्णांकel_host, &pdev->dev, host->mmc);

	host->mmc_host_ops.start_संकेत_voltage_चयन =
					पूर्णांकel_start_संकेत_voltage_चयन;

	c->is_पूर्णांकel = true;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_setup_host(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_acpi_host *c = platक्रमm_get_drvdata(pdev);
	काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_acpi_priv(c);

	अगर (!(पूर्णांकel_host->hs_caps & INTEL_DSM_HS_CAPS_SDR25))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDR25;

	अगर (!(पूर्णांकel_host->hs_caps & INTEL_DSM_HS_CAPS_SDR50))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDR50;

	अगर (!(पूर्णांकel_host->hs_caps & INTEL_DSM_HS_CAPS_DDR50))
		c->host->mmc->caps &= ~MMC_CAP_UHS_DDR50;

	अगर (!(पूर्णांकel_host->hs_caps & INTEL_DSM_HS_CAPS_SDR104))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDR104;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_acpi_slot sdhci_acpi_slot_पूर्णांक_emmc = अणु
	.chip    = &sdhci_acpi_chip_पूर्णांक,
	.caps    = MMC_CAP_8_BIT_DATA | MMC_CAP_NONREMOVABLE |
		   MMC_CAP_HW_RESET | MMC_CAP_1_8V_DDR |
		   MMC_CAP_CMD_DURING_TFR | MMC_CAP_WAIT_WHILE_BUSY,
	.flags   = SDHCI_ACPI_RUNTIME_PM,
	.quirks  = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		   SDHCI_QUIRK_NO_LED,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		   SDHCI_QUIRK2_STOP_WITH_TC |
		   SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400,
	.probe_slot	= पूर्णांकel_probe_slot,
	.setup_host	= पूर्णांकel_setup_host,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_slot sdhci_acpi_slot_पूर्णांक_sdio = अणु
	.quirks  = SDHCI_QUIRK_BROKEN_CARD_DETECTION |
		   SDHCI_QUIRK_NO_LED |
		   SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.quirks2 = SDHCI_QUIRK2_HOST_OFF_CARD_ON,
	.caps    = MMC_CAP_NONREMOVABLE | MMC_CAP_POWER_OFF_CARD |
		   MMC_CAP_WAIT_WHILE_BUSY,
	.flags   = SDHCI_ACPI_RUNTIME_PM,
	.pm_caps = MMC_PM_KEEP_POWER,
	.probe_slot	= पूर्णांकel_probe_slot,
	.setup_host	= पूर्णांकel_setup_host,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_slot sdhci_acpi_slot_पूर्णांक_sd = अणु
	.flags   = SDHCI_ACPI_SD_CD | SDHCI_ACPI_SD_CD_OVERRIDE_LEVEL |
		   SDHCI_ACPI_RUNTIME_PM,
	.quirks  = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		   SDHCI_QUIRK_NO_LED,
	.quirks2 = SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON |
		   SDHCI_QUIRK2_STOP_WITH_TC,
	.caps    = MMC_CAP_WAIT_WHILE_BUSY | MMC_CAP_AGGRESSIVE_PM,
	.probe_slot	= पूर्णांकel_probe_slot,
	.setup_host	= पूर्णांकel_setup_host,
	.priv_size	= माप(काष्ठा पूर्णांकel_host),
पूर्ण;

#घोषणा VENDOR_SPECIFIC_PWRCTL_CLEAR_REG	0x1a8
#घोषणा VENDOR_SPECIFIC_PWRCTL_CTL_REG		0x1ac
अटल irqवापस_t sdhci_acpi_qcom_handler(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा sdhci_host *host = ptr;

	sdhci_ग_लिखोl(host, 0x3, VENDOR_SPECIFIC_PWRCTL_CLEAR_REG);
	sdhci_ग_लिखोl(host, 0x1, VENDOR_SPECIFIC_PWRCTL_CTL_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_probe_slot(काष्ठा platक्रमm_device *pdev, काष्ठा acpi_device *adev)
अणु
	काष्ठा sdhci_acpi_host *c = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_host *host = c->host;
	पूर्णांक *irq = sdhci_acpi_priv(c);

	*irq = -EINVAL;

	अगर (!acpi_dev_hid_uid_match(adev, "QCOM8051", शून्य))
		वापस 0;

	*irq = platक्रमm_get_irq(pdev, 1);
	अगर (*irq < 0)
		वापस 0;

	वापस request_thपढ़ोed_irq(*irq, शून्य, sdhci_acpi_qcom_handler,
				    IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
				    "sdhci_qcom", host);
पूर्ण

अटल पूर्णांक qcom_मुक्त_slot(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_acpi_host *c = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_host *host = c->host;
	काष्ठा acpi_device *adev;
	पूर्णांक *irq = sdhci_acpi_priv(c);

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस -ENODEV;

	अगर (!acpi_dev_hid_uid_match(adev, "QCOM8051", शून्य))
		वापस 0;

	अगर (*irq < 0)
		वापस 0;

	मुक्त_irq(*irq, host);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_acpi_slot sdhci_acpi_slot_qcom_sd_3v = अणु
	.quirks  = SDHCI_QUIRK_BROKEN_CARD_DETECTION,
	.quirks2 = SDHCI_QUIRK2_NO_1_8_V,
	.caps    = MMC_CAP_NONREMOVABLE,
	.priv_size	= माप(पूर्णांक),
	.probe_slot	= qcom_probe_slot,
	.मुक्त_slot	= qcom_मुक्त_slot,
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_slot sdhci_acpi_slot_qcom_sd = अणु
	.quirks  = SDHCI_QUIRK_BROKEN_CARD_DETECTION,
	.caps    = MMC_CAP_NONREMOVABLE,
पूर्ण;

काष्ठा amd_sdhci_host अणु
	bool	tuned_घड़ी;
	bool	dll_enabled;
पूर्ण;

/* AMD sdhci reset dll रेजिस्टर. */
#घोषणा SDHCI_AMD_RESET_DLL_REGISTER    0x908

अटल पूर्णांक amd_select_drive_strength(काष्ठा mmc_card *card,
				     अचिन्हित पूर्णांक max_dtr, पूर्णांक host_drv,
				     पूर्णांक card_drv, पूर्णांक *host_driver_strength)
अणु
	काष्ठा sdhci_host *host = mmc_priv(card->host);
	u16 preset, preset_driver_strength;

	/*
	 * This method is only called by mmc_select_hs200 so we only need to
	 * पढ़ो from the HS200 (SDR104) preset रेजिस्टर.
	 *
	 * Firmware that has "invalid/default" presets वापस a driver strength
	 * of A. This matches the previously hard coded value.
	 */
	preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_SDR104);
	preset_driver_strength = FIELD_GET(SDHCI_PRESET_DRV_MASK, preset);

	/*
	 * We want the controller driver strength to match the card's driver
	 * strength so they have similar rise/fall बार.
	 *
	 * The controller driver strength set by this method is sticky क्रम all
	 * timings after this method is called. This unक्रमtunately means that
	 * जबतक HS400 tuning is in progress we end up with mismatched driver
	 * strengths between the controller and the card. HS400 tuning requires
	 * चयनing from HS400->DDR52->HS->HS200->HS400. So the driver mismatch
	 * happens जबतक in DDR52 and HS modes. This has not been observed to
	 * cause problems. Enabling presets would fix this issue.
	 */
	*host_driver_strength = preset_driver_strength;

	/*
	 * The resulting card driver strength is only set when चयनing the
	 * card's timing to HS200 or HS400. The card will use the शेष driver
	 * strength (B) क्रम any other mode.
	 */
	वापस preset_driver_strength;
पूर्ण

अटल व्योम sdhci_acpi_amd_hs400_dll(काष्ठा sdhci_host *host, bool enable)
अणु
	काष्ठा sdhci_acpi_host *acpi_host = sdhci_priv(host);
	काष्ठा amd_sdhci_host *amd_host = sdhci_acpi_priv(acpi_host);

	/* AMD Platक्रमm requires dll setting */
	sdhci_ग_लिखोl(host, 0x40003210, SDHCI_AMD_RESET_DLL_REGISTER);
	usleep_range(10, 20);
	अगर (enable)
		sdhci_ग_लिखोl(host, 0x40033210, SDHCI_AMD_RESET_DLL_REGISTER);

	amd_host->dll_enabled = enable;
पूर्ण

/*
 * The initialization sequence क्रम HS400 is:
 *     HS->HS200->Perक्रमm Tuning->HS->HS400
 *
 * The re-tuning sequence is:
 *     HS400->DDR52->HS->HS200->Perक्रमm Tuning->HS->HS400
 *
 * The AMD eMMC Controller can only use the tuned घड़ी जबतक in HS200 and HS400
 * mode. If we चयन to a dअगरferent mode, we need to disable the tuned घड़ी.
 * If we have previously perक्रमmed tuning and चयन back to HS200 or
 * HS400, we can re-enable the tuned घड़ी.
 *
 */
अटल व्योम amd_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_acpi_host *acpi_host = sdhci_priv(host);
	काष्ठा amd_sdhci_host *amd_host = sdhci_acpi_priv(acpi_host);
	अचिन्हित पूर्णांक old_timing = host->timing;
	u16 val;

	sdhci_set_ios(mmc, ios);

	अगर (old_timing != host->timing && amd_host->tuned_घड़ी) अणु
		अगर (host->timing == MMC_TIMING_MMC_HS400 ||
		    host->timing == MMC_TIMING_MMC_HS200) अणु
			val = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
			val |= SDHCI_CTRL_TUNED_CLK;
			sdhci_ग_लिखोw(host, val, SDHCI_HOST_CONTROL2);
		पूर्ण अन्यथा अणु
			val = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
			val &= ~SDHCI_CTRL_TUNED_CLK;
			sdhci_ग_लिखोw(host, val, SDHCI_HOST_CONTROL2);
		पूर्ण

		/* DLL is only required क्रम HS400 */
		अगर (host->timing == MMC_TIMING_MMC_HS400 &&
		    !amd_host->dll_enabled)
			sdhci_acpi_amd_hs400_dll(host, true);
	पूर्ण
पूर्ण

अटल पूर्णांक amd_sdhci_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	पूर्णांक err;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_acpi_host *acpi_host = sdhci_priv(host);
	काष्ठा amd_sdhci_host *amd_host = sdhci_acpi_priv(acpi_host);

	amd_host->tuned_घड़ी = false;

	err = sdhci_execute_tuning(mmc, opcode);

	अगर (!err && !host->tuning_err)
		amd_host->tuned_घड़ी = true;

	वापस err;
पूर्ण

अटल व्योम amd_sdhci_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_acpi_host *acpi_host = sdhci_priv(host);
	काष्ठा amd_sdhci_host *amd_host = sdhci_acpi_priv(acpi_host);

	अगर (mask & SDHCI_RESET_ALL) अणु
		amd_host->tuned_घड़ी = false;
		sdhci_acpi_amd_hs400_dll(host, false);
	पूर्ण

	sdhci_reset(host, mask);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_acpi_ops_amd = अणु
	.set_घड़ी	= sdhci_set_घड़ी,
	.set_bus_width	= sdhci_set_bus_width,
	.reset		= amd_sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_chip sdhci_acpi_chip_amd = अणु
	.ops = &sdhci_acpi_ops_amd,
पूर्ण;

अटल पूर्णांक sdhci_acpi_emmc_amd_probe_slot(काष्ठा platक्रमm_device *pdev,
					  काष्ठा acpi_device *adev)
अणु
	काष्ठा sdhci_acpi_host *c = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_host *host   = c->host;

	sdhci_पढ़ो_caps(host);
	अगर (host->caps1 & SDHCI_SUPPORT_DDR50)
		host->mmc->caps = MMC_CAP_1_8V_DDR;

	अगर ((host->caps1 & SDHCI_SUPPORT_SDR104) &&
	    (host->mmc->caps & MMC_CAP_1_8V_DDR))
		host->mmc->caps2 = MMC_CAP2_HS400_1_8V;

	/*
	 * There are two types of presets out in the wild:
	 * 1) Default/broken presets.
	 *    These presets have two sets of problems:
	 *    a) The घड़ी भागisor क्रम SDR12, SDR25, and SDR50 is too small.
	 *       This results in घड़ी frequencies that are 2x higher than
	 *       acceptable. i.e., SDR12 = 25 MHz, SDR25 = 50 MHz, SDR50 =
	 *       100 MHz.x
	 *    b) The HS200 and HS400 driver strengths करोn't match.
	 *       By शेष, the SDR104 preset रेजिस्टर has a driver strength of
	 *       A, but the (पूर्णांकernal) HS400 preset रेजिस्टर has a driver
	 *       strength of B. As part of initializing HS400, HS200 tuning
	 *       needs to be perक्रमmed. Having dअगरferent driver strengths
	 *       between tuning and operation is wrong. It results in dअगरferent
	 *       rise/fall बार that lead to incorrect sampling.
	 * 2) Firmware with properly initialized presets.
	 *    These presets have proper घड़ी भागisors. i.e., SDR12 => 12MHz,
	 *    SDR25 => 25 MHz, SDR50 => 50 MHz. Additionally the HS200 and
	 *    HS400 preset driver strengths match.
	 *
	 *    Enabling presets क्रम HS400 करोesn't work क्रम the following reasons:
	 *    1) sdhci_set_ios has a hard coded list of timings that are used
	 *       to determine अगर presets should be enabled.
	 *    2) sdhci_get_preset_value is using a non-standard रेजिस्टर to
	 *       पढ़ो out HS400 presets. The AMD controller करोesn't support this
	 *       non-standard रेजिस्टर. In fact, it करोesn't expose the HS400
	 *       preset रेजिस्टर anywhere in the SDHCI memory map. This results
	 *       in पढ़ोing a garbage value and using the wrong presets.
	 *
	 *       Since HS400 and HS200 presets must be identical, we could
	 *       instead use the the SDR104 preset रेजिस्टर.
	 *
	 *    If the above issues are resolved we could हटाओ this quirk क्रम
	 *    firmware that that has valid presets (i.e., SDR12 <= 12 MHz).
	 */
	host->quirks2 |= SDHCI_QUIRK2_PRESET_VALUE_BROKEN;

	host->mmc_host_ops.select_drive_strength = amd_select_drive_strength;
	host->mmc_host_ops.set_ios = amd_set_ios;
	host->mmc_host_ops.execute_tuning = amd_sdhci_execute_tuning;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_acpi_slot sdhci_acpi_slot_amd_emmc = अणु
	.chip		= &sdhci_acpi_chip_amd,
	.caps		= MMC_CAP_8_BIT_DATA | MMC_CAP_NONREMOVABLE,
	.quirks		= SDHCI_QUIRK_32BIT_DMA_ADDR |
			  SDHCI_QUIRK_32BIT_DMA_SIZE |
			  SDHCI_QUIRK_32BIT_ADMA_SIZE,
	.quirks2	= SDHCI_QUIRK2_BROKEN_64_BIT_DMA,
	.probe_slot     = sdhci_acpi_emmc_amd_probe_slot,
	.priv_size	= माप(काष्ठा amd_sdhci_host),
पूर्ण;

काष्ठा sdhci_acpi_uid_slot अणु
	स्थिर अक्षर *hid;
	स्थिर अक्षर *uid;
	स्थिर काष्ठा sdhci_acpi_slot *slot;
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_uid_slot sdhci_acpi_uids[] = अणु
	अणु "80865ACA", शून्य, &sdhci_acpi_slot_पूर्णांक_sd पूर्ण,
	अणु "80865ACC", शून्य, &sdhci_acpi_slot_पूर्णांक_emmc पूर्ण,
	अणु "80865AD0", शून्य, &sdhci_acpi_slot_पूर्णांक_sdio पूर्ण,
	अणु "80860F14" , "1" , &sdhci_acpi_slot_पूर्णांक_emmc पूर्ण,
	अणु "80860F14" , "2" , &sdhci_acpi_slot_पूर्णांक_sdio पूर्ण,
	अणु "80860F14" , "3" , &sdhci_acpi_slot_पूर्णांक_sd   पूर्ण,
	अणु "80860F16" , शून्य, &sdhci_acpi_slot_पूर्णांक_sd   पूर्ण,
	अणु "INT33BB"  , "2" , &sdhci_acpi_slot_पूर्णांक_sdio पूर्ण,
	अणु "INT33BB"  , "3" , &sdhci_acpi_slot_पूर्णांक_sd पूर्ण,
	अणु "INT33C6"  , शून्य, &sdhci_acpi_slot_पूर्णांक_sdio पूर्ण,
	अणु "INT3436"  , शून्य, &sdhci_acpi_slot_पूर्णांक_sdio पूर्ण,
	अणु "INT344D"  , शून्य, &sdhci_acpi_slot_पूर्णांक_sdio पूर्ण,
	अणु "PNP0FFF"  , "3" , &sdhci_acpi_slot_पूर्णांक_sd   पूर्ण,
	अणु "PNP0D40"  पूर्ण,
	अणु "QCOM8051", शून्य, &sdhci_acpi_slot_qcom_sd_3v पूर्ण,
	अणु "QCOM8052", शून्य, &sdhci_acpi_slot_qcom_sd पूर्ण,
	अणु "AMDI0040", शून्य, &sdhci_acpi_slot_amd_emmc पूर्ण,
	अणु "AMDI0041", शून्य, &sdhci_acpi_slot_amd_emmc पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id sdhci_acpi_ids[] = अणु
	अणु "80865ACA" पूर्ण,
	अणु "80865ACC" पूर्ण,
	अणु "80865AD0" पूर्ण,
	अणु "80860F14" पूर्ण,
	अणु "80860F16" पूर्ण,
	अणु "INT33BB"  पूर्ण,
	अणु "INT33C6"  पूर्ण,
	अणु "INT3436"  पूर्ण,
	अणु "INT344D"  पूर्ण,
	अणु "PNP0D40"  पूर्ण,
	अणु "QCOM8051" पूर्ण,
	अणु "QCOM8052" पूर्ण,
	अणु "AMDI0040" पूर्ण,
	अणु "AMDI0041" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sdhci_acpi_ids);

अटल स्थिर काष्ठा dmi_प्रणाली_id sdhci_acpi_quirks[] = अणु
	अणु
		/*
		 * The Lenovo Miix 320-10ICR has a bug in the _PS0 method of
		 * the SHC1 ACPI device, this bug causes it to reprogram the
		 * wrong LDO (DLDO3) to 1.8V अगर 1.8V modes are used and the
		 * card is (runसमय) suspended + resumed. DLDO3 is used क्रम
		 * the LCD and setting it to 1.8V causes the LCD to go black.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo MIIX 320-10ICR"),
		पूर्ण,
		.driver_data = (व्योम *)DMI_QUIRK_RESET_SD_SIGNAL_VOLT_ON_SUSP,
	पूर्ण,
	अणु
		/*
		 * The Acer Aspire Switch 10 (SW5-012) microSD slot always
		 * reports the card being ग_लिखो-रक्षित even though microSD
		 * cards करो not have a ग_लिखो-protect चयन at all.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire SW5-012"),
		पूर्ण,
		.driver_data = (व्योम *)DMI_QUIRK_SD_NO_WRITE_PROTECT,
	पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा sdhci_acpi_slot *sdhci_acpi_get_slot(काष्ठा acpi_device *adev)
अणु
	स्थिर काष्ठा sdhci_acpi_uid_slot *u;

	क्रम (u = sdhci_acpi_uids; u->hid; u++) अणु
		अगर (acpi_dev_hid_uid_match(adev, u->hid, u->uid))
			वापस u->slot;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक sdhci_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा sdhci_acpi_slot *slot;
	काष्ठा acpi_device *device, *child;
	स्थिर काष्ठा dmi_प्रणाली_id *id;
	काष्ठा sdhci_acpi_host *c;
	काष्ठा sdhci_host *host;
	काष्ठा resource *iomem;
	resource_माप_प्रकार len;
	माप_प्रकार priv_size;
	पूर्णांक quirks = 0;
	पूर्णांक err;

	device = ACPI_COMPANION(dev);
	अगर (!device)
		वापस -ENODEV;

	id = dmi_first_match(sdhci_acpi_quirks);
	अगर (id)
		quirks = (दीर्घ)id->driver_data;

	slot = sdhci_acpi_get_slot(device);

	/* Power on the SDHCI controller and its children */
	acpi_device_fix_up_घातer(device);
	अगर (!sdhci_acpi_no_fixup_child_घातer(device)) अणु
		list_क्रम_each_entry(child, &device->children, node)
			अगर (child->status.present && child->status.enabled)
				acpi_device_fix_up_घातer(child);
	पूर्ण

	अगर (sdhci_acpi_byt_defer(dev))
		वापस -EPROBE_DEFER;

	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iomem)
		वापस -ENOMEM;

	len = resource_size(iomem);
	अगर (len < 0x100)
		dev_err(dev, "Invalid iomem size!\n");

	अगर (!devm_request_mem_region(dev, iomem->start, len, dev_name(dev)))
		वापस -ENOMEM;

	priv_size = slot ? slot->priv_size : 0;
	host = sdhci_alloc_host(dev, माप(काष्ठा sdhci_acpi_host) + priv_size);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	c = sdhci_priv(host);
	c->host = host;
	c->slot = slot;
	c->pdev = pdev;
	c->use_runसमय_pm = sdhci_acpi_flag(c, SDHCI_ACPI_RUNTIME_PM);

	platक्रमm_set_drvdata(pdev, c);

	host->hw_name	= "ACPI";
	host->ops	= &sdhci_acpi_ops_dflt;
	host->irq	= platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0) अणु
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	host->ioaddr = devm_ioremap(dev, iomem->start,
					    resource_size(iomem));
	अगर (host->ioaddr == शून्य) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	अगर (c->slot) अणु
		अगर (c->slot->probe_slot) अणु
			err = c->slot->probe_slot(pdev, device);
			अगर (err)
				जाओ err_मुक्त;
		पूर्ण
		अगर (c->slot->chip) अणु
			host->ops            = c->slot->chip->ops;
			host->quirks        |= c->slot->chip->quirks;
			host->quirks2       |= c->slot->chip->quirks2;
			host->mmc->caps     |= c->slot->chip->caps;
			host->mmc->caps2    |= c->slot->chip->caps2;
			host->mmc->pm_caps  |= c->slot->chip->pm_caps;
		पूर्ण
		host->quirks        |= c->slot->quirks;
		host->quirks2       |= c->slot->quirks2;
		host->mmc->caps     |= c->slot->caps;
		host->mmc->caps2    |= c->slot->caps2;
		host->mmc->pm_caps  |= c->slot->pm_caps;
	पूर्ण

	host->mmc->caps2 |= MMC_CAP2_NO_PRESCAN_POWERUP;

	अगर (sdhci_acpi_flag(c, SDHCI_ACPI_SD_CD)) अणु
		bool v = sdhci_acpi_flag(c, SDHCI_ACPI_SD_CD_OVERRIDE_LEVEL);

		err = mmc_gpiod_request_cd(host->mmc, शून्य, 0, v, 0);
		अगर (err) अणु
			अगर (err == -EPROBE_DEFER)
				जाओ err_मुक्त;
			dev_warn(dev, "failed to setup card detect gpio\n");
			c->use_runसमय_pm = false;
		पूर्ण

		अगर (quirks & DMI_QUIRK_RESET_SD_SIGNAL_VOLT_ON_SUSP)
			c->reset_संकेत_volt_on_suspend = true;

		अगर (quirks & DMI_QUIRK_SD_NO_WRITE_PROTECT)
			host->mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;
	पूर्ण

	err = sdhci_setup_host(host);
	अगर (err)
		जाओ err_मुक्त;

	अगर (c->slot && c->slot->setup_host) अणु
		err = c->slot->setup_host(pdev);
		अगर (err)
			जाओ err_cleanup;
	पूर्ण

	err = __sdhci_add_host(host);
	अगर (err)
		जाओ err_cleanup;

	अगर (c->use_runसमय_pm) अणु
		pm_runसमय_set_active(dev);
		pm_suspend_ignore_children(dev, 1);
		pm_runसमय_set_स्वतःsuspend_delay(dev, 50);
		pm_runसमय_use_स्वतःsuspend(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	device_enable_async_suspend(dev);

	वापस 0;

err_cleanup:
	sdhci_cleanup_host(c->host);
err_मुक्त:
	अगर (c->slot && c->slot->मुक्त_slot)
		c->slot->मुक्त_slot(pdev);

	sdhci_मुक्त_host(c->host);
	वापस err;
पूर्ण

अटल पूर्णांक sdhci_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_acpi_host *c = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक dead;

	अगर (c->use_runसमय_pm) अणु
		pm_runसमय_get_sync(dev);
		pm_runसमय_disable(dev);
		pm_runसमय_put_noidle(dev);
	पूर्ण

	अगर (c->slot && c->slot->हटाओ_slot)
		c->slot->हटाओ_slot(pdev);

	dead = (sdhci_पढ़ोl(c->host, SDHCI_INT_STATUS) == ~0);
	sdhci_हटाओ_host(c->host, dead);

	अगर (c->slot && c->slot->मुक्त_slot)
		c->slot->मुक्त_slot(pdev);

	sdhci_मुक्त_host(c->host);

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused sdhci_acpi_reset_संकेत_voltage_अगर_needed(
	काष्ठा device *dev)
अणु
	काष्ठा sdhci_acpi_host *c = dev_get_drvdata(dev);
	काष्ठा sdhci_host *host = c->host;

	अगर (c->is_पूर्णांकel && c->reset_संकेत_volt_on_suspend &&
	    host->mmc->ios.संकेत_voltage != MMC_SIGNAL_VOLTAGE_330) अणु
		काष्ठा पूर्णांकel_host *पूर्णांकel_host = sdhci_acpi_priv(c);
		अचिन्हित पूर्णांक fn = INTEL_DSM_V33_SWITCH;
		u32 result = 0;

		पूर्णांकel_dsm(पूर्णांकel_host, dev, fn, &result);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक sdhci_acpi_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_acpi_host *c = dev_get_drvdata(dev);
	काष्ठा sdhci_host *host = c->host;
	पूर्णांक ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	ret = sdhci_suspend_host(host);
	अगर (ret)
		वापस ret;

	sdhci_acpi_reset_संकेत_voltage_अगर_needed(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_acpi_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_acpi_host *c = dev_get_drvdata(dev);

	sdhci_acpi_byt_setting(&c->pdev->dev);

	वापस sdhci_resume_host(c->host);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PM

अटल पूर्णांक sdhci_acpi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_acpi_host *c = dev_get_drvdata(dev);
	काष्ठा sdhci_host *host = c->host;
	पूर्णांक ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	ret = sdhci_runसमय_suspend_host(host);
	अगर (ret)
		वापस ret;

	sdhci_acpi_reset_संकेत_voltage_अगर_needed(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_acpi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_acpi_host *c = dev_get_drvdata(dev);

	sdhci_acpi_byt_setting(&c->pdev->dev);

	वापस sdhci_runसमय_resume_host(c->host, 0);
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_acpi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_acpi_suspend, sdhci_acpi_resume)
	SET_RUNTIME_PM_OPS(sdhci_acpi_runसमय_suspend,
			sdhci_acpi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sdhci_acpi_driver = अणु
	.driver = अणु
		.name			= "sdhci-acpi",
		.probe_type		= PROBE_PREFER_ASYNCHRONOUS,
		.acpi_match_table	= sdhci_acpi_ids,
		.pm			= &sdhci_acpi_pm_ops,
	पूर्ण,
	.probe	= sdhci_acpi_probe,
	.हटाओ	= sdhci_acpi_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_acpi_driver);

MODULE_DESCRIPTION("Secure Digital Host Controller Interface ACPI driver");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL v2");
