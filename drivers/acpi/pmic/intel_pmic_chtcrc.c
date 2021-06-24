<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Cherry Trail Crystal Cove PMIC operation region driver
 *
 * Copyright (C) 2019 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश "intel_pmic.h"

/*
 * We have no करोcs क्रम the CHT Crystal Cove PMIC. The Asus Zenfone-2 kernel
 * code has 2 Crystal Cove regulator drivers, one calls the PMIC a "Crystal
 * Cove Plus" PMIC and talks about Cherry Trail, so presumably that one
 * could be used to get रेजिस्टर info क्रम the regulators अगर we need to
 * implement regulator support in the future.
 *
 * For now the sole purpose of this driver is to make
 * पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element work on devices with a
 * CHT Crystal Cove PMIC.
 */
अटल काष्ठा पूर्णांकel_pmic_opregion_data पूर्णांकel_chtcrc_pmic_opregion_data = अणु
	.pmic_i2c_address = 0x6e,
पूर्ण;

अटल पूर्णांक पूर्णांकel_chtcrc_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	वापस पूर्णांकel_pmic_install_opregion_handler(&pdev->dev,
			ACPI_HANDLE(pdev->dev.parent), pmic->regmap,
			&पूर्णांकel_chtcrc_pmic_opregion_data);
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_chtcrc_pmic_opregion_driver = अणु
	.probe = पूर्णांकel_chtcrc_pmic_opregion_probe,
	.driver = अणु
		.name = "cht_crystal_cove_pmic",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(पूर्णांकel_chtcrc_pmic_opregion_driver);
