<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// AMD Renoir ACP PCI Driver
//
//Copyright 2020 Advanced Micro Devices, Inc.

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "rn_acp3x.h"

अटल पूर्णांक acp_घातer_gating;
module_param(acp_घातer_gating, पूर्णांक, 0644);
MODULE_PARM_DESC(acp_घातer_gating, "Enable acp power gating");

/*
 * dmic_acpi_check = -1 - Use ACPI/DMI method to detect the DMIC hardware presence at runसमय
 *                 =  0 - Skip the DMIC device creation and वापस probe failure
 *                 =  1 - Force DMIC support
 */
अटल पूर्णांक dmic_acpi_check = ACP_DMIC_AUTO;
module_param(dmic_acpi_check, bपूर्णांक, 0644);
MODULE_PARM_DESC(dmic_acpi_check, "Digital microphone presence (-1=auto, 0=none, 1=force)");

काष्ठा acp_dev_data अणु
	व्योम __iomem *acp_base;
	काष्ठा resource *res;
	काष्ठा platक्रमm_device *pdev[ACP_DEVS];
पूर्ण;

अटल पूर्णांक rn_acp_घातer_on(व्योम __iomem *acp_base)
अणु
	u32 val;
	पूर्णांक समयout;

	val = rn_पढ़ोl(acp_base + ACP_PGFSM_STATUS);

	अगर (val == 0)
		वापस val;

	अगर ((val & ACP_PGFSM_STATUS_MASK) !=
				ACP_POWER_ON_IN_PROGRESS)
		rn_ग_लिखोl(ACP_PGFSM_CNTL_POWER_ON_MASK,
			  acp_base + ACP_PGFSM_CONTROL);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rn_पढ़ोl(acp_base + ACP_PGFSM_STATUS);
		अगर (!val)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक rn_acp_घातer_off(व्योम __iomem *acp_base)
अणु
	u32 val;
	पूर्णांक समयout;

	rn_ग_लिखोl(ACP_PGFSM_CNTL_POWER_OFF_MASK,
		  acp_base + ACP_PGFSM_CONTROL);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rn_पढ़ोl(acp_base + ACP_PGFSM_STATUS);
		अगर ((val & ACP_PGFSM_STATUS_MASK) == ACP_POWERED_OFF)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक rn_acp_reset(व्योम __iomem *acp_base)
अणु
	u32 val;
	पूर्णांक समयout;

	rn_ग_लिखोl(1, acp_base + ACP_SOFT_RESET);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rn_पढ़ोl(acp_base + ACP_SOFT_RESET);
		अगर (val & ACP_SOFT_RESET_SOFTRESET_AUDDONE_MASK)
			अवरोध;
		cpu_relax();
	पूर्ण
	rn_ग_लिखोl(0, acp_base + ACP_SOFT_RESET);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rn_पढ़ोl(acp_base + ACP_SOFT_RESET);
		अगर (!val)
			वापस 0;
		cpu_relax();
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम rn_acp_enable_पूर्णांकerrupts(व्योम __iomem *acp_base)
अणु
	u32 ext_पूर्णांकr_ctrl;

	rn_ग_लिखोl(0x01, acp_base + ACP_EXTERNAL_INTR_ENB);
	ext_पूर्णांकr_ctrl = rn_पढ़ोl(acp_base + ACP_EXTERNAL_INTR_CNTL);
	ext_पूर्णांकr_ctrl |= ACP_ERROR_MASK;
	rn_ग_लिखोl(ext_पूर्णांकr_ctrl, acp_base + ACP_EXTERNAL_INTR_CNTL);
पूर्ण

अटल व्योम rn_acp_disable_पूर्णांकerrupts(व्योम __iomem *acp_base)
अणु
	rn_ग_लिखोl(ACP_EXT_INTR_STAT_CLEAR_MASK, acp_base +
		  ACP_EXTERNAL_INTR_STAT);
	rn_ग_लिखोl(0x00, acp_base + ACP_EXTERNAL_INTR_ENB);
पूर्ण

अटल पूर्णांक rn_acp_init(व्योम __iomem *acp_base)
अणु
	पूर्णांक ret;

	/* घातer on */
	ret = rn_acp_घातer_on(acp_base);
	अगर (ret) अणु
		pr_err("ACP power on failed\n");
		वापस ret;
	पूर्ण
	rn_ग_लिखोl(0x01, acp_base + ACP_CONTROL);
	/* Reset */
	ret = rn_acp_reset(acp_base);
	अगर (ret) अणु
		pr_err("ACP reset failed\n");
		वापस ret;
	पूर्ण
	rn_ग_लिखोl(0x03, acp_base + ACP_CLKMUX_SEL);
	rn_acp_enable_पूर्णांकerrupts(acp_base);
	वापस 0;
पूर्ण

अटल पूर्णांक rn_acp_deinit(व्योम __iomem *acp_base)
अणु
	पूर्णांक ret;

	rn_acp_disable_पूर्णांकerrupts(acp_base);
	/* Reset */
	ret = rn_acp_reset(acp_base);
	अगर (ret) अणु
		pr_err("ACP reset failed\n");
		वापस ret;
	पूर्ण
	rn_ग_लिखोl(0x00, acp_base + ACP_CLKMUX_SEL);
	rn_ग_लिखोl(0x00, acp_base + ACP_CONTROL);
	/* घातer off */
	अगर (acp_घातer_gating) अणु
		ret = rn_acp_घातer_off(acp_base);
		अगर (ret) अणु
			pr_err("ACP power off failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id rn_acp_quirk_table[] = अणु
	अणु
		/* Lenovo IdeaPad S340-14API */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "81NB"),
		पूर्ण
	पूर्ण,
	अणु
		/* Lenovo IdeaPad Flex 5 14ARE05 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "81X2"),
		पूर्ण
	पूर्ण,
	अणु
		/* Lenovo IdeaPad 5 15ARE05 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "81YQ"),
		पूर्ण
	पूर्ण,
	अणु
		/* Lenovo ThinkPad E14 Gen 2 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "20T6CTO1WW"),
		पूर्ण
	पूर्ण,
	अणु
		/* Lenovo ThinkPad X395 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "20NLCTO1WW"),
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक snd_rn_acp_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा acp_dev_data *adata;
	काष्ठा platक्रमm_device_info pdevinfo[ACP_DEVS];
#अगर defined(CONFIG_ACPI)
	acpi_handle handle;
	acpi_पूर्णांकeger dmic_status;
#पूर्ण_अगर
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	अचिन्हित पूर्णांक irqflags;
	पूर्णांक ret, index;
	u32 addr;

	/* Renoir device check */
	अगर (pci->revision != 0x01)
		वापस -ENODEV;

	अगर (pci_enable_device(pci)) अणु
		dev_err(&pci->dev, "pci_enable_device failed\n");
		वापस -ENODEV;
	पूर्ण

	ret = pci_request_regions(pci, "AMD ACP3x audio");
	अगर (ret < 0) अणु
		dev_err(&pci->dev, "pci_request_regions failed\n");
		जाओ disable_pci;
	पूर्ण

	adata = devm_kzalloc(&pci->dev, माप(काष्ठा acp_dev_data),
			     GFP_KERNEL);
	अगर (!adata) अणु
		ret = -ENOMEM;
		जाओ release_regions;
	पूर्ण

	/* check क्रम msi पूर्णांकerrupt support */
	ret = pci_enable_msi(pci);
	अगर (ret)
		/* msi is not enabled */
		irqflags = IRQF_SHARED;
	अन्यथा
		/* msi is enabled */
		irqflags = 0;

	addr = pci_resource_start(pci, 0);
	adata->acp_base = devm_ioremap(&pci->dev, addr,
				       pci_resource_len(pci, 0));
	अगर (!adata->acp_base) अणु
		ret = -ENOMEM;
		जाओ disable_msi;
	पूर्ण
	pci_set_master(pci);
	pci_set_drvdata(pci, adata);
	ret = rn_acp_init(adata->acp_base);
	अगर (ret)
		जाओ disable_msi;

	अगर (!dmic_acpi_check) अणु
		ret = -ENODEV;
		जाओ de_init;
	पूर्ण अन्यथा अगर (dmic_acpi_check == ACP_DMIC_AUTO) अणु
#अगर defined(CONFIG_ACPI)
		handle = ACPI_HANDLE(&pci->dev);
		ret = acpi_evaluate_पूर्णांकeger(handle, "_WOV", शून्य, &dmic_status);
		अगर (ACPI_FAILURE(ret)) अणु
			ret = -ENODEV;
			जाओ de_init;
		पूर्ण
		अगर (!dmic_status) अणु
			ret = -ENODEV;
			जाओ de_init;
		पूर्ण
#पूर्ण_अगर
		dmi_id = dmi_first_match(rn_acp_quirk_table);
		अगर (dmi_id && !dmi_id->driver_data) अणु
			dev_info(&pci->dev, "ACPI settings override using DMI (ACP mic is not present)");
			ret = -ENODEV;
			जाओ de_init;
		पूर्ण
	पूर्ण

	adata->res = devm_kzalloc(&pci->dev,
				  माप(काष्ठा resource) * 2,
				  GFP_KERNEL);
	अगर (!adata->res) अणु
		ret = -ENOMEM;
		जाओ de_init;
	पूर्ण

	adata->res[0].name = "acp_pdm_iomem";
	adata->res[0].flags = IORESOURCE_MEM;
	adata->res[0].start = addr;
	adata->res[0].end = addr + (ACP_REG_END - ACP_REG_START);
	adata->res[1].name = "acp_pdm_irq";
	adata->res[1].flags = IORESOURCE_IRQ;
	adata->res[1].start = pci->irq;
	adata->res[1].end = pci->irq;

	स_रखो(&pdevinfo, 0, माप(pdevinfo));
	pdevinfo[0].name = "acp_rn_pdm_dma";
	pdevinfo[0].id = 0;
	pdevinfo[0].parent = &pci->dev;
	pdevinfo[0].num_res = 2;
	pdevinfo[0].res = adata->res;
	pdevinfo[0].data = &irqflags;
	pdevinfo[0].size_data = माप(irqflags);

	pdevinfo[1].name = "dmic-codec";
	pdevinfo[1].id = 0;
	pdevinfo[1].parent = &pci->dev;
	pdevinfo[2].name = "acp_pdm_mach";
	pdevinfo[2].id = 0;
	pdevinfo[2].parent = &pci->dev;
	क्रम (index = 0; index < ACP_DEVS; index++) अणु
		adata->pdev[index] =
				platक्रमm_device_रेजिस्टर_full(&pdevinfo[index]);
		अगर (IS_ERR(adata->pdev[index])) अणु
			dev_err(&pci->dev, "cannot register %s device\n",
				pdevinfo[index].name);
			ret = PTR_ERR(adata->pdev[index]);
			जाओ unरेजिस्टर_devs;
		पूर्ण
	पूर्ण
	pm_runसमय_set_स्वतःsuspend_delay(&pci->dev, ACP_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&pci->dev);
	pm_runसमय_put_noidle(&pci->dev);
	pm_runसमय_allow(&pci->dev);
	वापस 0;

unरेजिस्टर_devs:
	क्रम (index = 0; index < ACP_DEVS; index++)
		platक्रमm_device_unरेजिस्टर(adata->pdev[index]);
de_init:
	अगर (rn_acp_deinit(adata->acp_base))
		dev_err(&pci->dev, "ACP de-init failed\n");
disable_msi:
	pci_disable_msi(pci);
release_regions:
	pci_release_regions(pci);
disable_pci:
	pci_disable_device(pci);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_rn_acp_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा acp_dev_data *adata;

	adata = dev_get_drvdata(dev);
	ret = rn_acp_deinit(adata->acp_base);
	अगर (ret)
		dev_err(dev, "ACP de-init failed\n");
	अन्यथा
		dev_dbg(dev, "ACP de-initialized\n");

	वापस ret;
पूर्ण

अटल पूर्णांक snd_rn_acp_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा acp_dev_data *adata;

	adata = dev_get_drvdata(dev);
	ret = rn_acp_init(adata->acp_base);
	अगर (ret) अणु
		dev_err(dev, "ACP init failed\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rn_acp_pm = अणु
	.runसमय_suspend = snd_rn_acp_suspend,
	.runसमय_resume =  snd_rn_acp_resume,
	.suspend = snd_rn_acp_suspend,
	.resume =	snd_rn_acp_resume,
पूर्ण;

अटल व्योम snd_rn_acp_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा acp_dev_data *adata;
	पूर्णांक ret, index;

	adata = pci_get_drvdata(pci);
	क्रम (index = 0; index < ACP_DEVS; index++)
		platक्रमm_device_unरेजिस्टर(adata->pdev[index]);
	ret = rn_acp_deinit(adata->acp_base);
	अगर (ret)
		dev_err(&pci->dev, "ACP de-init failed\n");
	pm_runसमय_क्रमbid(&pci->dev);
	pm_runसमय_get_noresume(&pci->dev);
	pci_disable_msi(pci);
	pci_release_regions(pci);
	pci_disable_device(pci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id snd_rn_acp_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, ACP_DEVICE_ID),
	.class = PCI_CLASS_MULTIMEDIA_OTHER << 8,
	.class_mask = 0xffffff पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_rn_acp_ids);

अटल काष्ठा pci_driver rn_acp_driver  = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_rn_acp_ids,
	.probe = snd_rn_acp_probe,
	.हटाओ = snd_rn_acp_हटाओ,
	.driver = अणु
		.pm = &rn_acp_pm,
	पूर्ण
पूर्ण;

module_pci_driver(rn_acp_driver);

MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_DESCRIPTION("AMD ACP Renoir PCI driver");
MODULE_LICENSE("GPL v2");
