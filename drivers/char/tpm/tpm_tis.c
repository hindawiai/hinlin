<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005, 2006 IBM Corporation
 * Copyright (C) 2014, 2015 Intel Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * This device driver implements the TPM पूर्णांकerface as defined in
 * the TCG TPM Interface Spec version 1.2, revision 1.0.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/acpi.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dmi.h>
#समावेश "tpm.h"
#समावेश "tpm_tis_core.h"

काष्ठा tpm_info अणु
	काष्ठा resource res;
	/* irq > 0 means: use irq $irq;
	 * irq = 0 means: स्वतःprobe क्रम an irq;
	 * irq = -1 means: no irq support
	 */
	पूर्णांक irq;
पूर्ण;

काष्ठा tpm_tis_tcg_phy अणु
	काष्ठा tpm_tis_data priv;
	व्योम __iomem *iobase;
पूर्ण;

अटल अंतरभूत काष्ठा tpm_tis_tcg_phy *to_tpm_tis_tcg_phy(काष्ठा tpm_tis_data *data)
अणु
	वापस container_of(data, काष्ठा tpm_tis_tcg_phy, priv);
पूर्ण

अटल पूर्णांक पूर्णांकerrupts = -1;
module_param(पूर्णांकerrupts, पूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांकerrupts, "Enable interrupts");

अटल bool itpm;
module_param(itpm, bool, 0444);
MODULE_PARM_DESC(itpm, "Force iTPM workarounds (found on some Lenovo laptops)");

अटल bool क्रमce;
#अगर_घोषित CONFIG_X86
module_param(क्रमce, bool, 0444);
MODULE_PARM_DESC(क्रमce, "Force device probe rather than using ACPI entry");
#पूर्ण_अगर

अटल पूर्णांक tpm_tis_disable_irq(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (पूर्णांकerrupts == -1) अणु
		pr_notice("tpm_tis: %s detected: disabling interrupts.\n", d->ident);
		पूर्णांकerrupts = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id tpm_tis_dmi_table[] = अणु
	अणु
		.callback = tpm_tis_disable_irq,
		.ident = "ThinkPad T490s",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T490s"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

#अगर defined(CONFIG_PNP) && defined(CONFIG_ACPI)
अटल पूर्णांक has_hid(काष्ठा acpi_device *dev, स्थिर अक्षर *hid)
अणु
	काष्ठा acpi_hardware_id *id;

	list_क्रम_each_entry(id, &dev->pnp.ids, list)
		अगर (!म_भेद(hid, id->id))
			वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_itpm(काष्ठा acpi_device *dev)
अणु
	अगर (!dev)
		वापस 0;
	वापस has_hid(dev, "INTC0102");
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक is_itpm(काष्ठा acpi_device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI)
#घोषणा DEVICE_IS_TPM2 1

अटल स्थिर काष्ठा acpi_device_id tpm_acpi_tbl[] = अणु
	अणु"MSFT0101", DEVICE_IS_TPM2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, tpm_acpi_tbl);

अटल पूर्णांक check_acpi_tpm2(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *aid = acpi_match_device(tpm_acpi_tbl, dev);
	काष्ठा acpi_table_tpm2 *tbl;
	acpi_status st;

	अगर (!aid || aid->driver_data != DEVICE_IS_TPM2)
		वापस 0;

	/* If the ACPI TPM2 signature is matched then a global ACPI_SIG_TPM2
	 * table is mandatory
	 */
	st =
	    acpi_get_table(ACPI_SIG_TPM2, 1, (काष्ठा acpi_table_header **)&tbl);
	अगर (ACPI_FAILURE(st) || tbl->header.length < माप(*tbl)) अणु
		dev_err(dev, FW_BUG "failed to get TPM2 ACPI table\n");
		वापस -EINVAL;
	पूर्ण

	/* The tpm2_crb driver handles this device */
	अगर (tbl->start_method != ACPI_TPM2_MEMORY_MAPPED)
		वापस -ENODEV;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक check_acpi_tpm2(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tpm_tcg_पढ़ो_bytes(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
			      u8 *result)
अणु
	काष्ठा tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);

	जबतक (len--)
		*result++ = ioपढ़ो8(phy->iobase + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tcg_ग_लिखो_bytes(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
			       स्थिर u8 *value)
अणु
	काष्ठा tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);

	जबतक (len--)
		ioग_लिखो8(*value++, phy->iobase + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tcg_पढ़ो16(काष्ठा tpm_tis_data *data, u32 addr, u16 *result)
अणु
	काष्ठा tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);

	*result = ioपढ़ो16(phy->iobase + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tcg_पढ़ो32(काष्ठा tpm_tis_data *data, u32 addr, u32 *result)
अणु
	काष्ठा tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);

	*result = ioपढ़ो32(phy->iobase + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tcg_ग_लिखो32(काष्ठा tpm_tis_data *data, u32 addr, u32 value)
अणु
	काष्ठा tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);

	ioग_लिखो32(value, phy->iobase + addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tpm_tis_phy_ops tpm_tcg = अणु
	.पढ़ो_bytes = tpm_tcg_पढ़ो_bytes,
	.ग_लिखो_bytes = tpm_tcg_ग_लिखो_bytes,
	.पढ़ो16 = tpm_tcg_पढ़ो16,
	.पढ़ो32 = tpm_tcg_पढ़ो32,
	.ग_लिखो32 = tpm_tcg_ग_लिखो32,
पूर्ण;

अटल पूर्णांक tpm_tis_init(काष्ठा device *dev, काष्ठा tpm_info *tpm_info)
अणु
	काष्ठा tpm_tis_tcg_phy *phy;
	पूर्णांक irq = -1;
	पूर्णांक rc;

	dmi_check_प्रणाली(tpm_tis_dmi_table);

	rc = check_acpi_tpm2(dev);
	अगर (rc)
		वापस rc;

	phy = devm_kzalloc(dev, माप(काष्ठा tpm_tis_tcg_phy), GFP_KERNEL);
	अगर (phy == शून्य)
		वापस -ENOMEM;

	phy->iobase = devm_ioremap_resource(dev, &tpm_info->res);
	अगर (IS_ERR(phy->iobase))
		वापस PTR_ERR(phy->iobase);

	अगर (पूर्णांकerrupts)
		irq = tpm_info->irq;

	अगर (itpm || is_itpm(ACPI_COMPANION(dev)))
		phy->priv.flags |= TPM_TIS_ITPM_WORKAROUND;

	वापस tpm_tis_core_init(dev, &phy->priv, irq, &tpm_tcg,
				 ACPI_HANDLE(dev));
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tpm_tis_pm, tpm_pm_suspend, tpm_tis_resume);

अटल पूर्णांक tpm_tis_pnp_init(काष्ठा pnp_dev *pnp_dev,
			    स्थिर काष्ठा pnp_device_id *pnp_id)
अणु
	काष्ठा tpm_info tpm_info = अणुपूर्ण;
	काष्ठा resource *res;

	res = pnp_get_resource(pnp_dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	tpm_info.res = *res;

	अगर (pnp_irq_valid(pnp_dev, 0))
		tpm_info.irq = pnp_irq(pnp_dev, 0);
	अन्यथा
		tpm_info.irq = -1;

	वापस tpm_tis_init(&pnp_dev->dev, &tpm_info);
पूर्ण

/*
 * There is a known bug caused by 93e1b7d42e1e ("[PATCH] tpm: add HID module
 * parameter"). This commit added IFX0102 device ID, which is also used by
 * tpm_infineon but ignored to add quirks to probe which driver ought to be
 * used.
 */

अटल काष्ठा pnp_device_id tpm_pnp_tbl[] = अणु
	अणु"PNP0C31", 0पूर्ण,		/* TPM */
	अणु"ATM1200", 0पूर्ण,		/* Aपंचांगel */
	अणु"IFX0102", 0पूर्ण,		/* Infineon */
	अणु"BCM0101", 0पूर्ण,		/* Broadcom */
	अणु"BCM0102", 0पूर्ण,		/* Broadcom */
	अणु"NSC1200", 0पूर्ण,		/* National */
	अणु"ICO0102", 0पूर्ण,		/* Intel */
	/* Add new here */
	अणु"", 0पूर्ण,		/* User Specअगरied */
	अणु"", 0पूर्ण			/* Terminator */
पूर्ण;
MODULE_DEVICE_TABLE(pnp, tpm_pnp_tbl);

अटल व्योम tpm_tis_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	काष्ठा tpm_chip *chip = pnp_get_drvdata(dev);

	tpm_chip_unरेजिस्टर(chip);
	tpm_tis_हटाओ(chip);
पूर्ण

अटल काष्ठा pnp_driver tis_pnp_driver = अणु
	.name = "tpm_tis",
	.id_table = tpm_pnp_tbl,
	.probe = tpm_tis_pnp_init,
	.हटाओ = tpm_tis_pnp_हटाओ,
	.driver	= अणु
		.pm = &tpm_tis_pm,
	पूर्ण,
पूर्ण;

#घोषणा TIS_HID_USR_IDX (ARRAY_SIZE(tpm_pnp_tbl) - 2)
module_param_string(hid, tpm_pnp_tbl[TIS_HID_USR_IDX].id,
		    माप(tpm_pnp_tbl[TIS_HID_USR_IDX].id), 0444);
MODULE_PARM_DESC(hid, "Set additional specific HID for this driver to probe");

अटल काष्ठा platक्रमm_device *क्रमce_pdev;

अटल पूर्णांक tpm_tis_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpm_info tpm_info = अणुपूर्ण;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no memory resource defined\n");
		वापस -ENODEV;
	पूर्ण
	tpm_info.res = *res;

	tpm_info.irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (tpm_info.irq <= 0) अणु
		अगर (pdev != क्रमce_pdev)
			tpm_info.irq = -1;
		अन्यथा
			/* When क्रमcing स्वतः probe the IRQ */
			tpm_info.irq = 0;
	पूर्ण

	वापस tpm_tis_init(&pdev->dev, &tpm_info);
पूर्ण

अटल पूर्णांक tpm_tis_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(&pdev->dev);

	tpm_chip_unरेजिस्टर(chip);
	tpm_tis_हटाओ(chip);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tis_of_platक्रमm_match[] = अणु
	अणु.compatible = "tcg,tpm-tis-mmio"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tis_of_platक्रमm_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tis_drv = अणु
	.probe = tpm_tis_plat_probe,
	.हटाओ = tpm_tis_plat_हटाओ,
	.driver = अणु
		.name		= "tpm_tis",
		.pm		= &tpm_tis_pm,
		.of_match_table = of_match_ptr(tis_of_platक्रमm_match),
		.acpi_match_table = ACPI_PTR(tpm_acpi_tbl),
	पूर्ण,
पूर्ण;

अटल पूर्णांक tpm_tis_क्रमce_device(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	अटल स्थिर काष्ठा resource x86_resources[] = अणु
		अणु
			.start = 0xFED40000,
			.end = 0xFED40000 + TIS_MEM_LEN - 1,
			.flags = IORESOURCE_MEM,
		पूर्ण,
	पूर्ण;

	अगर (!क्रमce)
		वापस 0;

	/* The driver core will match the name tpm_tis of the device to
	 * the tpm_tis platक्रमm driver and complete the setup via
	 * tpm_tis_plat_probe
	 */
	pdev = platक्रमm_device_रेजिस्टर_simple("tpm_tis", -1, x86_resources,
					       ARRAY_SIZE(x86_resources));
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);
	क्रमce_pdev = pdev;

	वापस 0;
पूर्ण

अटल पूर्णांक __init init_tis(व्योम)
अणु
	पूर्णांक rc;

	rc = tpm_tis_क्रमce_device();
	अगर (rc)
		जाओ err_क्रमce;

	rc = platक्रमm_driver_रेजिस्टर(&tis_drv);
	अगर (rc)
		जाओ err_platक्रमm;


	अगर (IS_ENABLED(CONFIG_PNP)) अणु
		rc = pnp_रेजिस्टर_driver(&tis_pnp_driver);
		अगर (rc)
			जाओ err_pnp;
	पूर्ण

	वापस 0;

err_pnp:
	platक्रमm_driver_unरेजिस्टर(&tis_drv);
err_platक्रमm:
	अगर (क्रमce_pdev)
		platक्रमm_device_unरेजिस्टर(क्रमce_pdev);
err_क्रमce:
	वापस rc;
पूर्ण

अटल व्योम __निकास cleanup_tis(व्योम)
अणु
	pnp_unरेजिस्टर_driver(&tis_pnp_driver);
	platक्रमm_driver_unरेजिस्टर(&tis_drv);

	अगर (क्रमce_pdev)
		platक्रमm_device_unरेजिस्टर(क्रमce_pdev);
पूर्ण

module_init(init_tis);
module_निकास(cleanup_tis);
MODULE_AUTHOR("Leendert van Doorn (leendert@watson.ibm.com)");
MODULE_DESCRIPTION("TPM Driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
