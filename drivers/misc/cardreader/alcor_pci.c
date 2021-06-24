<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Oleksij Rempel <linux@rempel-privat.de>
 *
 * Driver क्रम Alcor Micro AU6601 and AU6621 controllers
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>

#समावेश <linux/alcor_pci.h>

#घोषणा DRV_NAME_ALCOR_PCI			"alcor_pci"

अटल DEFINE_IDA(alcor_pci_idr);

अटल काष्ठा mfd_cell alcor_pci_cells[] = अणु
	[ALCOR_SD_CARD] = अणु
		.name = DRV_NAME_ALCOR_PCI_SDMMC,
	पूर्ण,
	[ALCOR_MS_CARD] = अणु
		.name = DRV_NAME_ALCOR_PCI_MS,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा alcor_dev_cfg alcor_cfg = अणु
	.dma = 0,
पूर्ण;

अटल स्थिर काष्ठा alcor_dev_cfg au6621_cfg = अणु
	.dma = 1,
पूर्ण;

अटल स्थिर काष्ठा alcor_dev_cfg au6625_cfg = अणु
	.dma = 0,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_ID_ALCOR_MICRO, PCI_ID_AU6601),
		.driver_data = (kernel_uदीर्घ_t)&alcor_cfg पूर्ण,
	अणु PCI_DEVICE(PCI_ID_ALCOR_MICRO, PCI_ID_AU6621),
		.driver_data = (kernel_uदीर्घ_t)&au6621_cfg पूर्ण,
	अणु PCI_DEVICE(PCI_ID_ALCOR_MICRO, PCI_ID_AU6625),
		.driver_data = (kernel_uदीर्घ_t)&au6625_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

व्योम alcor_ग_लिखो8(काष्ठा alcor_pci_priv *priv, u8 val, अचिन्हित पूर्णांक addr)
अणु
	ग_लिखोb(val, priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_ग_लिखो8);

व्योम alcor_ग_लिखो16(काष्ठा alcor_pci_priv *priv, u16 val, अचिन्हित पूर्णांक addr)
अणु
	ग_लिखोw(val, priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_ग_लिखो16);

व्योम alcor_ग_लिखो32(काष्ठा alcor_pci_priv *priv, u32 val, अचिन्हित पूर्णांक addr)
अणु
	ग_लिखोl(val, priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_ग_लिखो32);

व्योम alcor_ग_लिखो32be(काष्ठा alcor_pci_priv *priv, u32 val, अचिन्हित पूर्णांक addr)
अणु
	ioग_लिखो32be(val, priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_ग_लिखो32be);

u8 alcor_पढ़ो8(काष्ठा alcor_pci_priv *priv, अचिन्हित पूर्णांक addr)
अणु
	वापस पढ़ोb(priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_पढ़ो8);

u32 alcor_पढ़ो32(काष्ठा alcor_pci_priv *priv, अचिन्हित पूर्णांक addr)
अणु
	वापस पढ़ोl(priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_पढ़ो32);

u32 alcor_पढ़ो32be(काष्ठा alcor_pci_priv *priv, अचिन्हित पूर्णांक addr)
अणु
	वापस ioपढ़ो32be(priv->iobase + addr);
पूर्ण
EXPORT_SYMBOL_GPL(alcor_पढ़ो32be);

अटल पूर्णांक alcor_pci_find_cap_offset(काष्ठा alcor_pci_priv *priv,
				     काष्ठा pci_dev *pci)
अणु
	पूर्णांक where;
	u8 val8;
	u32 val32;

	where = ALCOR_CAP_START_OFFSET;
	pci_पढ़ो_config_byte(pci, where, &val8);
	अगर (!val8)
		वापस 0;

	where = (पूर्णांक)val8;
	जबतक (1) अणु
		pci_पढ़ो_config_dword(pci, where, &val32);
		अगर (val32 == 0xffffffff) अणु
			dev_dbg(priv->dev, "find_cap_offset invalid value %x.\n",
				val32);
			वापस 0;
		पूर्ण

		अगर ((val32 & 0xff) == 0x10) अणु
			dev_dbg(priv->dev, "pcie cap offset: %x\n", where);
			वापस where;
		पूर्ण

		अगर ((val32 & 0xff00) == 0x00) अणु
			dev_dbg(priv->dev, "pci_find_cap_offset invalid value %x.\n",
				val32);
			अवरोध;
		पूर्ण
		where = (पूर्णांक)((val32 >> 8) & 0xff);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alcor_pci_init_check_aspm(काष्ठा alcor_pci_priv *priv)
अणु
	काष्ठा pci_dev *pci;
	पूर्णांक where;
	u32 val32;

	priv->pdev_cap_off    = alcor_pci_find_cap_offset(priv, priv->pdev);
	priv->parent_cap_off = alcor_pci_find_cap_offset(priv,
							 priv->parent_pdev);

	अगर ((priv->pdev_cap_off == 0) || (priv->parent_cap_off == 0)) अणु
		dev_dbg(priv->dev, "pci_cap_off: %x, parent_cap_off: %x\n",
			priv->pdev_cap_off, priv->parent_cap_off);
		वापस;
	पूर्ण

	/* link capability */
	pci   = priv->pdev;
	where = priv->pdev_cap_off + ALCOR_PCIE_LINK_CAP_OFFSET;
	pci_पढ़ो_config_dword(pci, where, &val32);
	priv->pdev_aspm_cap = (u8)(val32 >> 10) & 0x03;

	pci   = priv->parent_pdev;
	where = priv->parent_cap_off + ALCOR_PCIE_LINK_CAP_OFFSET;
	pci_पढ़ो_config_dword(pci, where, &val32);
	priv->parent_aspm_cap = (u8)(val32 >> 10) & 0x03;

	अगर (priv->pdev_aspm_cap != priv->parent_aspm_cap) अणु
		u8 aspm_cap;

		dev_dbg(priv->dev, "pdev_aspm_cap: %x, parent_aspm_cap: %x\n",
			priv->pdev_aspm_cap, priv->parent_aspm_cap);
		aspm_cap = priv->pdev_aspm_cap & priv->parent_aspm_cap;
		priv->pdev_aspm_cap    = aspm_cap;
		priv->parent_aspm_cap = aspm_cap;
	पूर्ण

	dev_dbg(priv->dev, "ext_config_dev_aspm: %x, pdev_aspm_cap: %x\n",
		priv->ext_config_dev_aspm, priv->pdev_aspm_cap);
	priv->ext_config_dev_aspm &= priv->pdev_aspm_cap;
पूर्ण

अटल व्योम alcor_pci_aspm_ctrl(काष्ठा alcor_pci_priv *priv, u8 aspm_enable)
अणु
	काष्ठा pci_dev *pci;
	u8 aspm_ctrl, i;
	पूर्णांक where;
	u32 val32;

	अगर ((!priv->pdev_cap_off) || (!priv->parent_cap_off)) अणु
		dev_dbg(priv->dev, "pci_cap_off: %x, parent_cap_off: %x\n",
			priv->pdev_cap_off, priv->parent_cap_off);
		वापस;
	पूर्ण

	अगर (!priv->pdev_aspm_cap)
		वापस;

	aspm_ctrl = 0;
	अगर (aspm_enable) अणु
		aspm_ctrl = priv->ext_config_dev_aspm;

		अगर (!aspm_ctrl) अणु
			dev_dbg(priv->dev, "aspm_ctrl == 0\n");
			वापस;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु

		अगर (i) अणु
			pci   = priv->parent_pdev;
			where = priv->parent_cap_off
				+ ALCOR_PCIE_LINK_CTRL_OFFSET;
		पूर्ण अन्यथा अणु
			pci   = priv->pdev;
			where = priv->pdev_cap_off
				+ ALCOR_PCIE_LINK_CTRL_OFFSET;
		पूर्ण

		pci_पढ़ो_config_dword(pci, where, &val32);
		val32 &= (~0x03);
		val32 |= (aspm_ctrl & priv->pdev_aspm_cap);
		pci_ग_लिखो_config_byte(pci, where, (u8)val32);
	पूर्ण

पूर्ण

अटल अंतरभूत व्योम alcor_mask_sd_irqs(काष्ठा alcor_pci_priv *priv)
अणु
	alcor_ग_लिखो32(priv, 0, AU6601_REG_INT_ENABLE);
पूर्ण

अटल अंतरभूत व्योम alcor_unmask_sd_irqs(काष्ठा alcor_pci_priv *priv)
अणु
	alcor_ग_लिखो32(priv, AU6601_INT_CMD_MASK | AU6601_INT_DATA_MASK |
		  AU6601_INT_CARD_INSERT | AU6601_INT_CARD_REMOVE |
		  AU6601_INT_OVER_CURRENT_ERR,
		  AU6601_REG_INT_ENABLE);
पूर्ण

अटल अंतरभूत व्योम alcor_mask_ms_irqs(काष्ठा alcor_pci_priv *priv)
अणु
	alcor_ग_लिखो32(priv, 0, AU6601_MS_INT_ENABLE);
पूर्ण

अटल अंतरभूत व्योम alcor_unmask_ms_irqs(काष्ठा alcor_pci_priv *priv)
अणु
	alcor_ग_लिखो32(priv, 0x3d00fa, AU6601_MS_INT_ENABLE);
पूर्ण

अटल पूर्णांक alcor_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा alcor_dev_cfg *cfg;
	काष्ठा alcor_pci_priv *priv;
	पूर्णांक ret, i, bar = 0;

	cfg = (व्योम *)ent->driver_data;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = ida_simple_get(&alcor_pci_idr, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		वापस ret;
	priv->id = ret;

	priv->pdev = pdev;
	priv->parent_pdev = pdev->bus->self;
	priv->dev = &pdev->dev;
	priv->cfg = cfg;
	priv->irq = pdev->irq;

	ret = pci_request_regions(pdev, DRV_NAME_ALCOR_PCI);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request region\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "BAR %d is not iomem. Aborting.\n", bar);
		ret = -ENODEV;
		जाओ error_release_regions;
	पूर्ण

	priv->iobase = pcim_iomap(pdev, bar, 0);
	अगर (!priv->iobase) अणु
		ret = -ENOMEM;
		जाओ error_release_regions;
	पूर्ण

	/* make sure irqs are disabled */
	alcor_ग_लिखो32(priv, 0, AU6601_REG_INT_ENABLE);
	alcor_ग_लिखो32(priv, 0, AU6601_MS_INT_ENABLE);

	ret = dma_set_mask_and_coherent(priv->dev, AU6601_SDMA_MASK);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set DMA mask\n");
		जाओ error_release_regions;
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, priv);
	alcor_pci_init_check_aspm(priv);

	क्रम (i = 0; i < ARRAY_SIZE(alcor_pci_cells); i++) अणु
		alcor_pci_cells[i].platक्रमm_data = priv;
		alcor_pci_cells[i].pdata_size = माप(*priv);
	पूर्ण
	ret = mfd_add_devices(&pdev->dev, priv->id, alcor_pci_cells,
			ARRAY_SIZE(alcor_pci_cells), शून्य, 0, शून्य);
	अगर (ret < 0)
		जाओ error_release_regions;

	alcor_pci_aspm_ctrl(priv, 0);

	वापस 0;

error_release_regions:
	pci_release_regions(pdev);
	वापस ret;
पूर्ण

अटल व्योम alcor_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा alcor_pci_priv *priv;

	priv = pci_get_drvdata(pdev);

	alcor_pci_aspm_ctrl(priv, 1);

	mfd_हटाओ_devices(&pdev->dev);

	ida_simple_हटाओ(&alcor_pci_idr, priv->id);

	pci_release_regions(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक alcor_suspend(काष्ठा device *dev)
अणु
	काष्ठा alcor_pci_priv *priv = dev_get_drvdata(dev);

	alcor_pci_aspm_ctrl(priv, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक alcor_resume(काष्ठा device *dev)
अणु

	काष्ठा alcor_pci_priv *priv = dev_get_drvdata(dev);

	alcor_pci_aspm_ctrl(priv, 0);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(alcor_pci_pm_ops, alcor_suspend, alcor_resume);

अटल काष्ठा pci_driver alcor_driver = अणु
	.name	=	DRV_NAME_ALCOR_PCI,
	.id_table =	pci_ids,
	.probe	=	alcor_pci_probe,
	.हटाओ =	alcor_pci_हटाओ,
	.driver	=	अणु
		.pm	= &alcor_pci_pm_ops
	पूर्ण,
पूर्ण;

module_pci_driver(alcor_driver);

MODULE_AUTHOR("Oleksij Rempel <linux@rempel-privat.de>");
MODULE_DESCRIPTION("PCI driver for Alcor Micro AU6601 Secure Digital Host Controller Interface");
MODULE_LICENSE("GPL");
