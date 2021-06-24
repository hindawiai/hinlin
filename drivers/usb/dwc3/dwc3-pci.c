<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-pci.c - PCI Specअगरic glue layer
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>

#घोषणा PCI_DEVICE_ID_INTEL_BYT			0x0f37
#घोषणा PCI_DEVICE_ID_INTEL_MRFLD		0x119e
#घोषणा PCI_DEVICE_ID_INTEL_BSW			0x22b7
#घोषणा PCI_DEVICE_ID_INTEL_SPTLP		0x9d30
#घोषणा PCI_DEVICE_ID_INTEL_SPTH		0xa130
#घोषणा PCI_DEVICE_ID_INTEL_BXT			0x0aaa
#घोषणा PCI_DEVICE_ID_INTEL_BXT_M		0x1aaa
#घोषणा PCI_DEVICE_ID_INTEL_APL			0x5aaa
#घोषणा PCI_DEVICE_ID_INTEL_KBP			0xa2b0
#घोषणा PCI_DEVICE_ID_INTEL_CMLLP		0x02ee
#घोषणा PCI_DEVICE_ID_INTEL_CMLH		0x06ee
#घोषणा PCI_DEVICE_ID_INTEL_GLK			0x31aa
#घोषणा PCI_DEVICE_ID_INTEL_CNPLP		0x9dee
#घोषणा PCI_DEVICE_ID_INTEL_CNPH		0xa36e
#घोषणा PCI_DEVICE_ID_INTEL_CNPV		0xa3b0
#घोषणा PCI_DEVICE_ID_INTEL_ICLLP		0x34ee
#घोषणा PCI_DEVICE_ID_INTEL_EHLLP		0x4b7e
#घोषणा PCI_DEVICE_ID_INTEL_TGPLP		0xa0ee
#घोषणा PCI_DEVICE_ID_INTEL_TGPH		0x43ee
#घोषणा PCI_DEVICE_ID_INTEL_JSP			0x4dee
#घोषणा PCI_DEVICE_ID_INTEL_ADLP		0x51ee
#घोषणा PCI_DEVICE_ID_INTEL_ADLM		0x54ee
#घोषणा PCI_DEVICE_ID_INTEL_ADLS		0x7ae1
#घोषणा PCI_DEVICE_ID_INTEL_TGL			0x9a15

#घोषणा PCI_INTEL_BXT_DSM_GUID		"732b85d5-b7a7-4a1b-9ba0-4bbd00ffd511"
#घोषणा PCI_INTEL_BXT_FUNC_PMU_PWR	4
#घोषणा PCI_INTEL_BXT_STATE_D0		0
#घोषणा PCI_INTEL_BXT_STATE_D3		3

#घोषणा GP_RWBAR			1
#घोषणा GP_RWREG1			0xa0
#घोषणा GP_RWREG1_ULPI_REFCLK_DISABLE	(1 << 17)

/**
 * काष्ठा dwc3_pci - Driver निजी काष्ठाure
 * @dwc3: child dwc3 platक्रमm_device
 * @pci: our link to PCI bus
 * @guid: _DSM GUID
 * @has_dsm_क्रम_pm: true क्रम devices which need to run _DSM on runसमय PM
 * @wakeup_work: work क्रम asynchronous resume
 */
काष्ठा dwc3_pci अणु
	काष्ठा platक्रमm_device *dwc3;
	काष्ठा pci_dev *pci;

	guid_t guid;

	अचिन्हित पूर्णांक has_dsm_क्रम_pm:1;
	काष्ठा work_काष्ठा wakeup_work;
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params reset_gpios = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params cs_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_dwc3_byt_gpios[] = अणु
	अणु "reset-gpios", &reset_gpios, 1 पूर्ण,
	अणु "cs-gpios", &cs_gpios, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table platक्रमm_bytcr_gpios = अणु
	.dev_id		= "0000:00:16.0",
	.table		= अणु
		GPIO_LOOKUP("INT33FC:00", 54, "reset", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("INT33FC:02", 14, "cs", GPIO_ACTIVE_HIGH),
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक dwc3_byt_enable_ulpi_refघड़ी(काष्ठा pci_dev *pci)
अणु
	व्योम __iomem	*reg;
	u32		value;

	reg = pcim_iomap(pci, GP_RWBAR, 0);
	अगर (!reg)
		वापस -ENOMEM;

	value = पढ़ोl(reg + GP_RWREG1);
	अगर (!(value & GP_RWREG1_ULPI_REFCLK_DISABLE))
		जाओ unmap; /* ULPI refclk alपढ़ोy enabled */

	value &= ~GP_RWREG1_ULPI_REFCLK_DISABLE;
	ग_लिखोl(value, reg + GP_RWREG1);
	/* This comes from the Intel Android x86 tree w/o any explanation */
	msleep(100);
unmap:
	pcim_iounmap(pci, reg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा property_entry dwc3_pci_पूर्णांकel_properties[] = अणु
	PROPERTY_ENTRY_STRING("dr_mode", "peripheral"),
	PROPERTY_ENTRY_BOOL("linux,sysdev_is_parent"),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा property_entry dwc3_pci_mrfld_properties[] = अणु
	PROPERTY_ENTRY_STRING("dr_mode", "otg"),
	PROPERTY_ENTRY_STRING("linux,extcon-name", "mrfld_bcove_pwrsrc"),
	PROPERTY_ENTRY_BOOL("snps,dis_u3_susphy_quirk"),
	PROPERTY_ENTRY_BOOL("snps,dis_u2_susphy_quirk"),
	PROPERTY_ENTRY_BOOL("snps,usb2-gadget-lpm-disable"),
	PROPERTY_ENTRY_BOOL("linux,sysdev_is_parent"),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा property_entry dwc3_pci_amd_properties[] = अणु
	PROPERTY_ENTRY_BOOL("snps,has-lpm-erratum"),
	PROPERTY_ENTRY_U8("snps,lpm-nyet-threshold", 0xf),
	PROPERTY_ENTRY_BOOL("snps,u2exit_lfps_quirk"),
	PROPERTY_ENTRY_BOOL("snps,u2ss_inp3_quirk"),
	PROPERTY_ENTRY_BOOL("snps,req_p1p2p3_quirk"),
	PROPERTY_ENTRY_BOOL("snps,del_p1p2p3_quirk"),
	PROPERTY_ENTRY_BOOL("snps,del_phy_power_chg_quirk"),
	PROPERTY_ENTRY_BOOL("snps,lfps_filter_quirk"),
	PROPERTY_ENTRY_BOOL("snps,rx_detect_poll_quirk"),
	PROPERTY_ENTRY_BOOL("snps,tx_de_emphasis_quirk"),
	PROPERTY_ENTRY_U8("snps,tx_de_emphasis", 1),
	/* FIXME these quirks should be हटाओd when AMD NL tapes out */
	PROPERTY_ENTRY_BOOL("snps,disable_scramble_quirk"),
	PROPERTY_ENTRY_BOOL("snps,dis_u3_susphy_quirk"),
	PROPERTY_ENTRY_BOOL("snps,dis_u2_susphy_quirk"),
	PROPERTY_ENTRY_BOOL("linux,sysdev_is_parent"),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node dwc3_pci_पूर्णांकel_swnode = अणु
	.properties = dwc3_pci_पूर्णांकel_properties,
पूर्ण;

अटल स्थिर काष्ठा software_node dwc3_pci_पूर्णांकel_mrfld_swnode = अणु
	.properties = dwc3_pci_mrfld_properties,
पूर्ण;

अटल स्थिर काष्ठा software_node dwc3_pci_amd_swnode = अणु
	.properties = dwc3_pci_amd_properties,
पूर्ण;

अटल पूर्णांक dwc3_pci_quirks(काष्ठा dwc3_pci *dwc)
अणु
	काष्ठा pci_dev			*pdev = dwc->pci;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL) अणु
		अगर (pdev->device == PCI_DEVICE_ID_INTEL_BXT ||
		    pdev->device == PCI_DEVICE_ID_INTEL_BXT_M ||
		    pdev->device == PCI_DEVICE_ID_INTEL_EHLLP) अणु
			guid_parse(PCI_INTEL_BXT_DSM_GUID, &dwc->guid);
			dwc->has_dsm_क्रम_pm = true;
		पूर्ण

		अगर (pdev->device == PCI_DEVICE_ID_INTEL_BYT) अणु
			काष्ठा gpio_desc *gpio;
			पूर्णांक ret;

			/* On BYT the FW करोes not always enable the refघड़ी */
			ret = dwc3_byt_enable_ulpi_refघड़ी(pdev);
			अगर (ret)
				वापस ret;

			ret = devm_acpi_dev_add_driver_gpios(&pdev->dev,
					acpi_dwc3_byt_gpios);
			अगर (ret)
				dev_dbg(&pdev->dev, "failed to add mapping table\n");

			/*
			 * A lot of BYT devices lack ACPI resource entries क्रम
			 * the GPIOs, add a fallback mapping to the reference
			 * design GPIOs which all boards seem to use.
			 */
			gpiod_add_lookup_table(&platक्रमm_bytcr_gpios);

			/*
			 * These GPIOs will turn on the USB2 PHY. Note that we have to
			 * put the gpio descriptors again here because the phy driver
			 * might want to grab them, too.
			 */
			gpio = gpiod_get_optional(&pdev->dev, "cs", GPIOD_OUT_LOW);
			अगर (IS_ERR(gpio))
				वापस PTR_ERR(gpio);

			gpiod_set_value_cansleep(gpio, 1);
			gpiod_put(gpio);

			gpio = gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
			अगर (IS_ERR(gpio))
				वापस PTR_ERR(gpio);

			अगर (gpio) अणु
				gpiod_set_value_cansleep(gpio, 1);
				gpiod_put(gpio);
				usleep_range(10000, 11000);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम dwc3_pci_resume_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dwc3_pci *dwc = container_of(work, काष्ठा dwc3_pci, wakeup_work);
	काष्ठा platक्रमm_device *dwc3 = dwc->dwc3;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&dwc3->dev);
	अगर (ret) अणु
		pm_runसमय_put_sync_स्वतःsuspend(&dwc3->dev);
		वापस;
	पूर्ण

	pm_runसमय_mark_last_busy(&dwc3->dev);
	pm_runसमय_put_sync_स्वतःsuspend(&dwc3->dev);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dwc3_pci_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा dwc3_pci		*dwc;
	काष्ठा resource		res[2];
	पूर्णांक			ret;
	काष्ठा device		*dev = &pci->dev;

	ret = pcim_enable_device(pci);
	अगर (ret) अणु
		dev_err(dev, "failed to enable pci device\n");
		वापस -ENODEV;
	पूर्ण

	pci_set_master(pci);

	dwc = devm_kzalloc(dev, माप(*dwc), GFP_KERNEL);
	अगर (!dwc)
		वापस -ENOMEM;

	dwc->dwc3 = platक्रमm_device_alloc("dwc3", PLATFORM_DEVID_AUTO);
	अगर (!dwc->dwc3)
		वापस -ENOMEM;

	स_रखो(res, 0x00, माप(काष्ठा resource) * ARRAY_SIZE(res));

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= "dwc_usb3";
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= "dwc_usb3";
	res[1].flags	= IORESOURCE_IRQ;

	ret = platक्रमm_device_add_resources(dwc->dwc3, res, ARRAY_SIZE(res));
	अगर (ret) अणु
		dev_err(dev, "couldn't add resources to dwc3 device\n");
		जाओ err;
	पूर्ण

	dwc->pci = pci;
	dwc->dwc3->dev.parent = dev;
	ACPI_COMPANION_SET(&dwc->dwc3->dev, ACPI_COMPANION(dev));

	ret = device_add_software_node(&dwc->dwc3->dev, (व्योम *)id->driver_data);
	अगर (ret < 0)
		जाओ err;

	ret = dwc3_pci_quirks(dwc);
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add(dwc->dwc3);
	अगर (ret) अणु
		dev_err(dev, "failed to register dwc3 device\n");
		जाओ err;
	पूर्ण

	device_init_wakeup(dev, true);
	pci_set_drvdata(pci, dwc);
	pm_runसमय_put(dev);
#अगर_घोषित CONFIG_PM
	INIT_WORK(&dwc->wakeup_work, dwc3_pci_resume_work);
#पूर्ण_अगर

	वापस 0;
err:
	device_हटाओ_software_node(&dwc->dwc3->dev);
	platक्रमm_device_put(dwc->dwc3);
	वापस ret;
पूर्ण

अटल व्योम dwc3_pci_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा dwc3_pci		*dwc = pci_get_drvdata(pci);
	काष्ठा pci_dev		*pdev = dwc->pci;

	अगर (pdev->device == PCI_DEVICE_ID_INTEL_BYT)
		gpiod_हटाओ_lookup_table(&platक्रमm_bytcr_gpios);
#अगर_घोषित CONFIG_PM
	cancel_work_sync(&dwc->wakeup_work);
#पूर्ण_अगर
	device_init_wakeup(&pci->dev, false);
	pm_runसमय_get(&pci->dev);
	device_हटाओ_software_node(&dwc->dwc3->dev);
	platक्रमm_device_unरेजिस्टर(dwc->dwc3);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dwc3_pci_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_BSW),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_BYT),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_MRFLD),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_mrfld_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CMLLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CMLH),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_SPTLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_SPTH),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_BXT),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_BXT_M),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_APL),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_KBP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_GLK),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CNPLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CNPH),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CNPV),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ICLLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_EHLLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGPLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGPH),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_JSP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ADLP),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ADLM),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ADLS),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGL),
	  (kernel_uदीर्घ_t) &dwc3_pci_पूर्णांकel_swnode, पूर्ण,

	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_NL_USB),
	  (kernel_uदीर्घ_t) &dwc3_pci_amd_swnode, पूर्ण,
	अणु  पूर्ण	/* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, dwc3_pci_id_table);

#अगर defined(CONFIG_PM) || defined(CONFIG_PM_SLEEP)
अटल पूर्णांक dwc3_pci_dsm(काष्ठा dwc3_pci *dwc, पूर्णांक param)
अणु
	जोड़ acpi_object *obj;
	जोड़ acpi_object पंचांगp;
	जोड़ acpi_object argv4 = ACPI_INIT_DSM_ARGV4(1, &पंचांगp);

	अगर (!dwc->has_dsm_क्रम_pm)
		वापस 0;

	पंचांगp.type = ACPI_TYPE_INTEGER;
	पंचांगp.पूर्णांकeger.value = param;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(&dwc->pci->dev), &dwc->guid,
			1, PCI_INTEL_BXT_FUNC_PMU_PWR, &argv4);
	अगर (!obj) अणु
		dev_err(&dwc->pci->dev, "failed to evaluate _DSM\n");
		वापस -EIO;
	पूर्ण

	ACPI_FREE(obj);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM || CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dwc3_pci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_pci		*dwc = dev_get_drvdata(dev);

	अगर (device_can_wakeup(dev))
		वापस dwc3_pci_dsm(dwc, PCI_INTEL_BXT_STATE_D3);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dwc3_pci_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_pci		*dwc = dev_get_drvdata(dev);
	पूर्णांक			ret;

	ret = dwc3_pci_dsm(dwc, PCI_INTEL_BXT_STATE_D0);
	अगर (ret)
		वापस ret;

	queue_work(pm_wq, &dwc->wakeup_work);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwc3_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_pci		*dwc = dev_get_drvdata(dev);

	वापस dwc3_pci_dsm(dwc, PCI_INTEL_BXT_STATE_D3);
पूर्ण

अटल पूर्णांक dwc3_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_pci		*dwc = dev_get_drvdata(dev);

	वापस dwc3_pci_dsm(dwc, PCI_INTEL_BXT_STATE_D0);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops dwc3_pci_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_pci_suspend, dwc3_pci_resume)
	SET_RUNTIME_PM_OPS(dwc3_pci_runसमय_suspend, dwc3_pci_runसमय_resume,
		शून्य)
पूर्ण;

अटल काष्ठा pci_driver dwc3_pci_driver = अणु
	.name		= "dwc3-pci",
	.id_table	= dwc3_pci_id_table,
	.probe		= dwc3_pci_probe,
	.हटाओ		= dwc3_pci_हटाओ,
	.driver		= अणु
		.pm	= &dwc3_pci_dev_pm_ops,
	पूर्ण
पूर्ण;

MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 PCI Glue Layer");

module_pci_driver(dwc3_pci_driver);
