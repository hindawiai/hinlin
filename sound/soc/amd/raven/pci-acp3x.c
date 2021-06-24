<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// AMD ACP PCI Driver
//
//Copyright 2016 Advanced Micro Devices, Inc.

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>

#समावेश "acp3x.h"

काष्ठा acp3x_dev_data अणु
	व्योम __iomem *acp3x_base;
	bool acp3x_audio_mode;
	काष्ठा resource *res;
	काष्ठा platक्रमm_device *pdev[ACP3x_DEVS];
	u32 pme_en;
पूर्ण;

अटल पूर्णांक acp3x_घातer_on(काष्ठा acp3x_dev_data *adata)
अणु
	व्योम __iomem *acp3x_base = adata->acp3x_base;
	u32 val;
	पूर्णांक समयout;

	val = rv_पढ़ोl(acp3x_base + mmACP_PGFSM_STATUS);

	अगर (val == 0)
		वापस val;

	अगर (!((val & ACP_PGFSM_STATUS_MASK) ==
				ACP_POWER_ON_IN_PROGRESS))
		rv_ग_लिखोl(ACP_PGFSM_CNTL_POWER_ON_MASK,
			acp3x_base + mmACP_PGFSM_CONTROL);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rv_पढ़ोl(acp3x_base + mmACP_PGFSM_STATUS);
		अगर (!val) अणु
			/* ACP घातer On clears PME_EN.
			 * Restore the value to its prior state
			 */
			rv_ग_लिखोl(adata->pme_en, acp3x_base + mmACP_PME_EN);
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक acp3x_reset(व्योम __iomem *acp3x_base)
अणु
	u32 val;
	पूर्णांक समयout;

	rv_ग_लिखोl(1, acp3x_base + mmACP_SOFT_RESET);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rv_पढ़ोl(acp3x_base + mmACP_SOFT_RESET);
		अगर (val & ACP3x_SOFT_RESET__SoftResetAudDone_MASK)
			अवरोध;
		cpu_relax();
	पूर्ण
	rv_ग_लिखोl(0, acp3x_base + mmACP_SOFT_RESET);
	समयout = 0;
	जबतक (++समयout < 500) अणु
		val = rv_पढ़ोl(acp3x_base + mmACP_SOFT_RESET);
		अगर (!val)
			वापस 0;
		cpu_relax();
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम acp3x_enable_पूर्णांकerrupts(व्योम __iomem *acp_base)
अणु
	rv_ग_लिखोl(0x01, acp_base + mmACP_EXTERNAL_INTR_ENB);
पूर्ण

अटल व्योम acp3x_disable_पूर्णांकerrupts(व्योम __iomem *acp_base)
अणु
	rv_ग_लिखोl(ACP_EXT_INTR_STAT_CLEAR_MASK, acp_base +
		  mmACP_EXTERNAL_INTR_STAT);
	rv_ग_लिखोl(0x00, acp_base + mmACP_EXTERNAL_INTR_CNTL);
	rv_ग_लिखोl(0x00, acp_base + mmACP_EXTERNAL_INTR_ENB);
पूर्ण

अटल पूर्णांक acp3x_init(काष्ठा acp3x_dev_data *adata)
अणु
	व्योम __iomem *acp3x_base = adata->acp3x_base;
	पूर्णांक ret;

	/* घातer on */
	ret = acp3x_घातer_on(adata);
	अगर (ret) अणु
		pr_err("ACP3x power on failed\n");
		वापस ret;
	पूर्ण
	/* Reset */
	ret = acp3x_reset(acp3x_base);
	अगर (ret) अणु
		pr_err("ACP3x reset failed\n");
		वापस ret;
	पूर्ण
	acp3x_enable_पूर्णांकerrupts(acp3x_base);
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_deinit(व्योम __iomem *acp3x_base)
अणु
	पूर्णांक ret;

	acp3x_disable_पूर्णांकerrupts(acp3x_base);
	/* Reset */
	ret = acp3x_reset(acp3x_base);
	अगर (ret) अणु
		pr_err("ACP3x reset failed\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_acp3x_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा acp3x_dev_data *adata;
	काष्ठा platक्रमm_device_info pdevinfo[ACP3x_DEVS];
	अचिन्हित पूर्णांक irqflags;
	पूर्णांक ret, i;
	u32 addr, val;

	/* Raven device detection */
	अगर (pci->revision != 0x00)
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

	adata = devm_kzalloc(&pci->dev, माप(काष्ठा acp3x_dev_data),
			     GFP_KERNEL);
	अगर (!adata) अणु
		ret = -ENOMEM;
		जाओ release_regions;
	पूर्ण

	irqflags = IRQF_SHARED;

	addr = pci_resource_start(pci, 0);
	adata->acp3x_base = devm_ioremap(&pci->dev, addr,
					pci_resource_len(pci, 0));
	अगर (!adata->acp3x_base) अणु
		ret = -ENOMEM;
		जाओ release_regions;
	पूर्ण
	pci_set_master(pci);
	pci_set_drvdata(pci, adata);
	/* Save ACP_PME_EN state */
	adata->pme_en = rv_पढ़ोl(adata->acp3x_base + mmACP_PME_EN);
	ret = acp3x_init(adata);
	अगर (ret)
		जाओ release_regions;

	val = rv_पढ़ोl(adata->acp3x_base + mmACP_I2S_PIN_CONFIG);
	चयन (val) अणु
	हाल I2S_MODE:
		adata->res = devm_kzalloc(&pci->dev,
					  माप(काष्ठा resource) * 4,
					  GFP_KERNEL);
		अगर (!adata->res) अणु
			ret = -ENOMEM;
			जाओ de_init;
		पूर्ण

		adata->res[0].name = "acp3x_i2s_iomem";
		adata->res[0].flags = IORESOURCE_MEM;
		adata->res[0].start = addr;
		adata->res[0].end = addr + (ACP3x_REG_END - ACP3x_REG_START);

		adata->res[1].name = "acp3x_i2s_sp";
		adata->res[1].flags = IORESOURCE_MEM;
		adata->res[1].start = addr + ACP3x_I2STDM_REG_START;
		adata->res[1].end = addr + ACP3x_I2STDM_REG_END;

		adata->res[2].name = "acp3x_i2s_bt";
		adata->res[2].flags = IORESOURCE_MEM;
		adata->res[2].start = addr + ACP3x_BT_TDM_REG_START;
		adata->res[2].end = addr + ACP3x_BT_TDM_REG_END;

		adata->res[3].name = "acp3x_i2s_irq";
		adata->res[3].flags = IORESOURCE_IRQ;
		adata->res[3].start = pci->irq;
		adata->res[3].end = adata->res[3].start;

		adata->acp3x_audio_mode = ACP3x_I2S_MODE;

		स_रखो(&pdevinfo, 0, माप(pdevinfo));
		pdevinfo[0].name = "acp3x_rv_i2s_dma";
		pdevinfo[0].id = 0;
		pdevinfo[0].parent = &pci->dev;
		pdevinfo[0].num_res = 4;
		pdevinfo[0].res = &adata->res[0];
		pdevinfo[0].data = &irqflags;
		pdevinfo[0].size_data = माप(irqflags);

		pdevinfo[1].name = "acp3x_i2s_playcap";
		pdevinfo[1].id = 0;
		pdevinfo[1].parent = &pci->dev;
		pdevinfo[1].num_res = 1;
		pdevinfo[1].res = &adata->res[1];

		pdevinfo[2].name = "acp3x_i2s_playcap";
		pdevinfo[2].id = 1;
		pdevinfo[2].parent = &pci->dev;
		pdevinfo[2].num_res = 1;
		pdevinfo[2].res = &adata->res[1];

		pdevinfo[3].name = "acp3x_i2s_playcap";
		pdevinfo[3].id = 2;
		pdevinfo[3].parent = &pci->dev;
		pdevinfo[3].num_res = 1;
		pdevinfo[3].res = &adata->res[2];
		क्रम (i = 0; i < ACP3x_DEVS; i++) अणु
			adata->pdev[i] =
				platक्रमm_device_रेजिस्टर_full(&pdevinfo[i]);
			अगर (IS_ERR(adata->pdev[i])) अणु
				dev_err(&pci->dev, "cannot register %s device\n",
					pdevinfo[i].name);
				ret = PTR_ERR(adata->pdev[i]);
				जाओ unरेजिस्टर_devs;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		dev_info(&pci->dev, "ACP audio mode : %d\n", val);
		अवरोध;
	पूर्ण
	pm_runसमय_set_स्वतःsuspend_delay(&pci->dev, 2000);
	pm_runसमय_use_स्वतःsuspend(&pci->dev);
	pm_runसमय_put_noidle(&pci->dev);
	pm_runसमय_allow(&pci->dev);
	वापस 0;

unरेजिस्टर_devs:
	अगर (val == I2S_MODE)
		क्रम (i = 0; i < ACP3x_DEVS; i++)
			platक्रमm_device_unरेजिस्टर(adata->pdev[i]);
de_init:
	अगर (acp3x_deinit(adata->acp3x_base))
		dev_err(&pci->dev, "ACP de-init failed\n");
release_regions:
	pci_release_regions(pci);
disable_pci:
	pci_disable_device(pci);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_acp3x_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा acp3x_dev_data *adata;

	adata = dev_get_drvdata(dev);
	ret = acp3x_deinit(adata->acp3x_base);
	अगर (ret)
		dev_err(dev, "ACP de-init failed\n");
	अन्यथा
		dev_dbg(dev, "ACP de-initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक snd_acp3x_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा acp3x_dev_data *adata;

	adata = dev_get_drvdata(dev);
	ret = acp3x_init(adata);
	अगर (ret) अणु
		dev_err(dev, "ACP init failed\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops acp3x_pm = अणु
	.runसमय_suspend = snd_acp3x_suspend,
	.runसमय_resume =  snd_acp3x_resume,
	.resume =	snd_acp3x_resume,
पूर्ण;

अटल व्योम snd_acp3x_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा acp3x_dev_data *adata;
	पूर्णांक i, ret;

	adata = pci_get_drvdata(pci);
	अगर (adata->acp3x_audio_mode == ACP3x_I2S_MODE) अणु
		क्रम (i = 0; i < ACP3x_DEVS; i++)
			platक्रमm_device_unरेजिस्टर(adata->pdev[i]);
	पूर्ण
	ret = acp3x_deinit(adata->acp3x_base);
	अगर (ret)
		dev_err(&pci->dev, "ACP de-init failed\n");
	pm_runसमय_क्रमbid(&pci->dev);
	pm_runसमय_get_noresume(&pci->dev);
	pci_release_regions(pci);
	pci_disable_device(pci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id snd_acp3x_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, 0x15e2),
	.class = PCI_CLASS_MULTIMEDIA_OTHER << 8,
	.class_mask = 0xffffff पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_acp3x_ids);

अटल काष्ठा pci_driver acp3x_driver  = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_acp3x_ids,
	.probe = snd_acp3x_probe,
	.हटाओ = snd_acp3x_हटाओ,
	.driver = अणु
		.pm = &acp3x_pm,
	पूर्ण
पूर्ण;

module_pci_driver(acp3x_driver);

MODULE_AUTHOR("Vishnuvardhanrao.Ravulapati@amd.com");
MODULE_AUTHOR("Maruthi.Bayyavarapu@amd.com");
MODULE_DESCRIPTION("AMD ACP3x PCI driver");
MODULE_LICENSE("GPL v2");
