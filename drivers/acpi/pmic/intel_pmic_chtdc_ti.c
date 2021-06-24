<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dollar Cove TI PMIC operation region driver
 * Copyright (C) 2014 Intel Corporation. All rights reserved.
 *
 * Rewritten and cleaned up
 * Copyright (C) 2017 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "intel_pmic.h"

/* रेजिस्टरs stored in 16bit BE (high:low, total 10bit) */
#घोषणा CHTDC_TI_VBAT		0x54
#घोषणा CHTDC_TI_DIETEMP	0x56
#घोषणा CHTDC_TI_BPTHERM	0x58
#घोषणा CHTDC_TI_GPADC		0x5a

अटल काष्ठा pmic_table chtdc_ti_घातer_table[] = अणु
	अणु .address = 0x00, .reg = 0x41 पूर्ण,
	अणु .address = 0x04, .reg = 0x42 पूर्ण,
	अणु .address = 0x08, .reg = 0x43 पूर्ण,
	अणु .address = 0x0c, .reg = 0x45 पूर्ण,
	अणु .address = 0x10, .reg = 0x46 पूर्ण,
	अणु .address = 0x14, .reg = 0x47 पूर्ण,
	अणु .address = 0x18, .reg = 0x48 पूर्ण,
	अणु .address = 0x1c, .reg = 0x49 पूर्ण,
	अणु .address = 0x20, .reg = 0x4a पूर्ण,
	अणु .address = 0x24, .reg = 0x4b पूर्ण,
	अणु .address = 0x28, .reg = 0x4c पूर्ण,
	अणु .address = 0x2c, .reg = 0x4d पूर्ण,
	अणु .address = 0x30, .reg = 0x4e पूर्ण,
पूर्ण;

अटल काष्ठा pmic_table chtdc_ti_thermal_table[] = अणु
	अणु
		.address = 0x00,
		.reg = CHTDC_TI_GPADC
	पूर्ण,
	अणु
		.address = 0x0c,
		.reg = CHTDC_TI_GPADC
	पूर्ण,
	/* TMP2 -> SYSTEMP */
	अणु
		.address = 0x18,
		.reg = CHTDC_TI_GPADC
	पूर्ण,
	/* TMP3 -> BPTHERM */
	अणु
		.address = 0x24,
		.reg = CHTDC_TI_BPTHERM
	पूर्ण,
	अणु
		.address = 0x30,
		.reg = CHTDC_TI_GPADC
	पूर्ण,
	/* TMP5 -> DIETEMP */
	अणु
		.address = 0x3c,
		.reg = CHTDC_TI_DIETEMP
	पूर्ण,
पूर्ण;

अटल पूर्णांक chtdc_ti_pmic_get_घातer(काष्ठा regmap *regmap, पूर्णांक reg, पूर्णांक bit,
				   u64 *value)
अणु
	पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = data & 1;
	वापस 0;
पूर्ण

अटल पूर्णांक chtdc_ti_pmic_update_घातer(काष्ठा regmap *regmap, पूर्णांक reg, पूर्णांक bit,
				      bool on)
अणु
	वापस regmap_update_bits(regmap, reg, 1, on);
पूर्ण

अटल पूर्णांक chtdc_ti_pmic_get_raw_temp(काष्ठा regmap *regmap, पूर्णांक reg)
अणु
	u8 buf[2];

	अगर (regmap_bulk_पढ़ो(regmap, reg, buf, 2))
		वापस -EIO;

	/* stored in big-endian */
	वापस ((buf[0] & 0x03) << 8) | buf[1];
पूर्ण

अटल काष्ठा पूर्णांकel_pmic_opregion_data chtdc_ti_pmic_opregion_data = अणु
	.get_घातer = chtdc_ti_pmic_get_घातer,
	.update_घातer = chtdc_ti_pmic_update_घातer,
	.get_raw_temp = chtdc_ti_pmic_get_raw_temp,
	.घातer_table = chtdc_ti_घातer_table,
	.घातer_table_count = ARRAY_SIZE(chtdc_ti_घातer_table),
	.thermal_table = chtdc_ti_thermal_table,
	.thermal_table_count = ARRAY_SIZE(chtdc_ti_thermal_table),
	.pmic_i2c_address = 0x5e,
पूर्ण;

अटल पूर्णांक chtdc_ti_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक err;

	err = पूर्णांकel_pmic_install_opregion_handler(&pdev->dev,
			ACPI_HANDLE(pdev->dev.parent), pmic->regmap,
			&chtdc_ti_pmic_opregion_data);
	अगर (err < 0)
		वापस err;

	/* Re-क्रमागतerate devices depending on PMIC */
	acpi_walk_dep_device_list(ACPI_HANDLE(pdev->dev.parent));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id chtdc_ti_pmic_opregion_id_table[] = अणु
	अणु .name = "chtdc_ti_region" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver chtdc_ti_pmic_opregion_driver = अणु
	.probe = chtdc_ti_pmic_opregion_probe,
	.driver = अणु
		.name = "cht_dollar_cove_ti_pmic",
	पूर्ण,
	.id_table = chtdc_ti_pmic_opregion_id_table,
पूर्ण;
builtin_platक्रमm_driver(chtdc_ti_pmic_opregion_driver);
