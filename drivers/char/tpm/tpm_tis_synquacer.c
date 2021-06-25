<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Linaro Ltd.
 *
 * This device driver implements MMIO TPM on SynQuacer Platक्रमm.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/kernel.h>
#समावेश "tpm.h"
#समावेश "tpm_tis_core.h"

/*
 * irq > 0 means: use irq $irq;
 * irq = 0 means: स्वतःprobe क्रम an irq;
 * irq = -1 means: no irq support
 */
काष्ठा tpm_tis_synquacer_info अणु
	काष्ठा resource res;
	पूर्णांक irq;
पूर्ण;

काष्ठा tpm_tis_synquacer_phy अणु
	काष्ठा tpm_tis_data priv;
	व्योम __iomem *iobase;
पूर्ण;

अटल अंतरभूत काष्ठा tpm_tis_synquacer_phy *to_tpm_tis_tcg_phy(काष्ठा tpm_tis_data *data)
अणु
	वापस container_of(data, काष्ठा tpm_tis_synquacer_phy, priv);
पूर्ण

अटल पूर्णांक tpm_tis_synquacer_पढ़ो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
					u16 len, u8 *result)
अणु
	काष्ठा tpm_tis_synquacer_phy *phy = to_tpm_tis_tcg_phy(data);

	जबतक (len--)
		*result++ = ioपढ़ो8(phy->iobase + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tis_synquacer_ग_लिखो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
					 u16 len, स्थिर u8 *value)
अणु
	काष्ठा tpm_tis_synquacer_phy *phy = to_tpm_tis_tcg_phy(data);

	जबतक (len--)
		ioग_लिखो8(*value++, phy->iobase + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tis_synquacer_पढ़ो16_bw(काष्ठा tpm_tis_data *data,
				       u32 addr, u16 *result)
अणु
	काष्ठा tpm_tis_synquacer_phy *phy = to_tpm_tis_tcg_phy(data);

	/*
	 * Due to the limitation of SPI controller on SynQuacer,
	 * 16/32 bits access must be करोne in byte-wise and descending order.
	 */
	*result = (ioपढ़ो8(phy->iobase + addr + 1) << 8) |
		  (ioपढ़ो8(phy->iobase + addr));

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tis_synquacer_पढ़ो32_bw(काष्ठा tpm_tis_data *data,
				       u32 addr, u32 *result)
अणु
	काष्ठा tpm_tis_synquacer_phy *phy = to_tpm_tis_tcg_phy(data);

	/*
	 * Due to the limitation of SPI controller on SynQuacer,
	 * 16/32 bits access must be करोne in byte-wise and descending order.
	 */
	*result = (ioपढ़ो8(phy->iobase + addr + 3) << 24) |
		  (ioपढ़ो8(phy->iobase + addr + 2) << 16) |
		  (ioपढ़ो8(phy->iobase + addr + 1) << 8) |
		  (ioपढ़ो8(phy->iobase + addr));

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tis_synquacer_ग_लिखो32_bw(काष्ठा tpm_tis_data *data,
					u32 addr, u32 value)
अणु
	काष्ठा tpm_tis_synquacer_phy *phy = to_tpm_tis_tcg_phy(data);

	/*
	 * Due to the limitation of SPI controller on SynQuacer,
	 * 16/32 bits access must be करोne in byte-wise and descending order.
	 */
	ioग_लिखो8(value >> 24, phy->iobase + addr + 3);
	ioग_लिखो8(value >> 16, phy->iobase + addr + 2);
	ioग_लिखो8(value >> 8, phy->iobase + addr + 1);
	ioग_लिखो8(value, phy->iobase + addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tpm_tis_phy_ops tpm_tcg_bw = अणु
	.पढ़ो_bytes	= tpm_tis_synquacer_पढ़ो_bytes,
	.ग_लिखो_bytes	= tpm_tis_synquacer_ग_लिखो_bytes,
	.पढ़ो16		= tpm_tis_synquacer_पढ़ो16_bw,
	.पढ़ो32		= tpm_tis_synquacer_पढ़ो32_bw,
	.ग_लिखो32	= tpm_tis_synquacer_ग_लिखो32_bw,
पूर्ण;

अटल पूर्णांक tpm_tis_synquacer_init(काष्ठा device *dev,
				  काष्ठा tpm_tis_synquacer_info *tpm_info)
अणु
	काष्ठा tpm_tis_synquacer_phy *phy;

	phy = devm_kzalloc(dev, माप(काष्ठा tpm_tis_synquacer_phy), GFP_KERNEL);
	अगर (phy == शून्य)
		वापस -ENOMEM;

	phy->iobase = devm_ioremap_resource(dev, &tpm_info->res);
	अगर (IS_ERR(phy->iobase))
		वापस PTR_ERR(phy->iobase);

	वापस tpm_tis_core_init(dev, &phy->priv, tpm_info->irq, &tpm_tcg_bw,
				 ACPI_HANDLE(dev));
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tpm_tis_synquacer_pm, tpm_pm_suspend, tpm_tis_resume);

अटल पूर्णांक tpm_tis_synquacer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpm_tis_synquacer_info tpm_info = अणुपूर्ण;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no memory resource defined\n");
		वापस -ENODEV;
	पूर्ण
	tpm_info.res = *res;

	tpm_info.irq = -1;

	वापस tpm_tis_synquacer_init(&pdev->dev, &tpm_info);
पूर्ण

अटल पूर्णांक tpm_tis_synquacer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(&pdev->dev);

	tpm_chip_unरेजिस्टर(chip);
	tpm_tis_हटाओ(chip);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tis_synquacer_of_platक्रमm_match[] = अणु
	अणु.compatible = "socionext,synquacer-tpm-mmio"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tis_synquacer_of_platक्रमm_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id tpm_synquacer_acpi_tbl[] = अणु
	अणु "SCX0009" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, tpm_synquacer_acpi_tbl);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tis_synquacer_drv = अणु
	.probe = tpm_tis_synquacer_probe,
	.हटाओ = tpm_tis_synquacer_हटाओ,
	.driver = अणु
		.name		= "tpm_tis_synquacer",
		.pm		= &tpm_tis_synquacer_pm,
		.of_match_table = of_match_ptr(tis_synquacer_of_platक्रमm_match),
		.acpi_match_table = ACPI_PTR(tpm_synquacer_acpi_tbl),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tpm_tis_synquacer_module_init(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_रेजिस्टर(&tis_synquacer_drv);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम __निकास tpm_tis_synquacer_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tis_synquacer_drv);
पूर्ण

module_init(tpm_tis_synquacer_module_init);
module_निकास(tpm_tis_synquacer_module_निकास);
MODULE_DESCRIPTION("TPM MMIO Driver for Socionext SynQuacer platform");
MODULE_LICENSE("GPL");
