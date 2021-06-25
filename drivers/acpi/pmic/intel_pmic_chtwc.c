<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel CHT Whiskey Cove PMIC operation region driver
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on various non upstream patches to support the CHT Whiskey Cove PMIC:
 * Copyright (C) 2013-2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश "intel_pmic.h"

#घोषणा CHT_WC_V1P05A_CTRL		0x6e3b
#घोषणा CHT_WC_V1P15_CTRL		0x6e3c
#घोषणा CHT_WC_V1P05A_VSEL		0x6e3d
#घोषणा CHT_WC_V1P15_VSEL		0x6e3e
#घोषणा CHT_WC_V1P8A_CTRL		0x6e56
#घोषणा CHT_WC_V1P8SX_CTRL		0x6e57
#घोषणा CHT_WC_VDDQ_CTRL		0x6e58
#घोषणा CHT_WC_V1P2A_CTRL		0x6e59
#घोषणा CHT_WC_V1P2SX_CTRL		0x6e5a
#घोषणा CHT_WC_V1P8A_VSEL		0x6e5b
#घोषणा CHT_WC_VDDQ_VSEL		0x6e5c
#घोषणा CHT_WC_V2P8SX_CTRL		0x6e5d
#घोषणा CHT_WC_V3P3A_CTRL		0x6e5e
#घोषणा CHT_WC_V3P3SD_CTRL		0x6e5f
#घोषणा CHT_WC_VSDIO_CTRL		0x6e67
#घोषणा CHT_WC_V3P3A_VSEL		0x6e68
#घोषणा CHT_WC_VPROG1A_CTRL		0x6e90
#घोषणा CHT_WC_VPROG1B_CTRL		0x6e91
#घोषणा CHT_WC_VPROG1F_CTRL		0x6e95
#घोषणा CHT_WC_VPROG2D_CTRL		0x6e99
#घोषणा CHT_WC_VPROG3A_CTRL		0x6e9a
#घोषणा CHT_WC_VPROG3B_CTRL		0x6e9b
#घोषणा CHT_WC_VPROG4A_CTRL		0x6e9c
#घोषणा CHT_WC_VPROG4B_CTRL		0x6e9d
#घोषणा CHT_WC_VPROG4C_CTRL		0x6e9e
#घोषणा CHT_WC_VPROG4D_CTRL		0x6e9f
#घोषणा CHT_WC_VPROG5A_CTRL		0x6ea0
#घोषणा CHT_WC_VPROG5B_CTRL		0x6ea1
#घोषणा CHT_WC_VPROG6A_CTRL		0x6ea2
#घोषणा CHT_WC_VPROG6B_CTRL		0x6ea3
#घोषणा CHT_WC_VPROG1A_VSEL		0x6ec0
#घोषणा CHT_WC_VPROG1B_VSEL		0x6ec1
#घोषणा CHT_WC_V1P8SX_VSEL		0x6ec2
#घोषणा CHT_WC_V1P2SX_VSEL		0x6ec3
#घोषणा CHT_WC_V1P2A_VSEL		0x6ec4
#घोषणा CHT_WC_VPROG1F_VSEL		0x6ec5
#घोषणा CHT_WC_VSDIO_VSEL		0x6ec6
#घोषणा CHT_WC_V2P8SX_VSEL		0x6ec7
#घोषणा CHT_WC_V3P3SD_VSEL		0x6ec8
#घोषणा CHT_WC_VPROG2D_VSEL		0x6ec9
#घोषणा CHT_WC_VPROG3A_VSEL		0x6eca
#घोषणा CHT_WC_VPROG3B_VSEL		0x6ecb
#घोषणा CHT_WC_VPROG4A_VSEL		0x6ecc
#घोषणा CHT_WC_VPROG4B_VSEL		0x6ecd
#घोषणा CHT_WC_VPROG4C_VSEL		0x6ece
#घोषणा CHT_WC_VPROG4D_VSEL		0x6ecf
#घोषणा CHT_WC_VPROG5A_VSEL		0x6ed0
#घोषणा CHT_WC_VPROG5B_VSEL		0x6ed1
#घोषणा CHT_WC_VPROG6A_VSEL		0x6ed2
#घोषणा CHT_WC_VPROG6B_VSEL		0x6ed3

/*
 * Regulator support is based on the non upstream patch:
 * "regulator: whiskey_cove: implements Whiskey Cove pmic VRF support"
 * https://github.com/पूर्णांकel-aero/meta-पूर्णांकel-aero/blob/master/recipes-kernel/linux/linux-yocto/0019-regulator-whiskey_cove-implements-WhiskeyCove-pmic-V.patch
 */
अटल काष्ठा pmic_table घातer_table[] = अणु
	अणु
		.address = 0x0,
		.reg = CHT_WC_V1P8A_CTRL,
		.bit = 0x01,
	पूर्ण, /* V18A */
	अणु
		.address = 0x04,
		.reg = CHT_WC_V1P8SX_CTRL,
		.bit = 0x07,
	पूर्ण, /* V18X */
	अणु
		.address = 0x08,
		.reg = CHT_WC_VDDQ_CTRL,
		.bit = 0x01,
	पूर्ण, /* VDDQ */
	अणु
		.address = 0x0c,
		.reg = CHT_WC_V1P2A_CTRL,
		.bit = 0x07,
	पूर्ण, /* V12A */
	अणु
		.address = 0x10,
		.reg = CHT_WC_V1P2SX_CTRL,
		.bit = 0x07,
	पूर्ण, /* V12X */
	अणु
		.address = 0x14,
		.reg = CHT_WC_V2P8SX_CTRL,
		.bit = 0x07,
	पूर्ण, /* V28X */
	अणु
		.address = 0x18,
		.reg = CHT_WC_V3P3A_CTRL,
		.bit = 0x01,
	पूर्ण, /* V33A */
	अणु
		.address = 0x1c,
		.reg = CHT_WC_V3P3SD_CTRL,
		.bit = 0x07,
	पूर्ण, /* V3SD */
	अणु
		.address = 0x20,
		.reg = CHT_WC_VSDIO_CTRL,
		.bit = 0x07,
	पूर्ण, /* VSD */
/*	अणु
		.address = 0x24,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** VSW2 */
/*	अणु
		.address = 0x28,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** VSW1 */
/*	अणु
		.address = 0x2c,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** VUPY */
/*	अणु
		.address = 0x30,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** VRSO */
	अणु
		.address = 0x34,
		.reg = CHT_WC_VPROG1A_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP1A */
	अणु
		.address = 0x38,
		.reg = CHT_WC_VPROG1B_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP1B */
	अणु
		.address = 0x3c,
		.reg = CHT_WC_VPROG1F_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP1F */
	अणु
		.address = 0x40,
		.reg = CHT_WC_VPROG2D_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP2D */
	अणु
		.address = 0x44,
		.reg = CHT_WC_VPROG3A_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP3A */
	अणु
		.address = 0x48,
		.reg = CHT_WC_VPROG3B_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP3B */
	अणु
		.address = 0x4c,
		.reg = CHT_WC_VPROG4A_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP4A */
	अणु
		.address = 0x50,
		.reg = CHT_WC_VPROG4B_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP4B */
	अणु
		.address = 0x54,
		.reg = CHT_WC_VPROG4C_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP4C */
	अणु
		.address = 0x58,
		.reg = CHT_WC_VPROG4D_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP4D */
	अणु
		.address = 0x5c,
		.reg = CHT_WC_VPROG5A_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP5A */
	अणु
		.address = 0x60,
		.reg = CHT_WC_VPROG5B_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP5B */
	अणु
		.address = 0x64,
		.reg = CHT_WC_VPROG6A_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP6A */
	अणु
		.address = 0x68,
		.reg = CHT_WC_VPROG6B_CTRL,
		.bit = 0x07,
	पूर्ण, /* VP6B */
/*	अणु
		.address = 0x6c,
		.reg = ??,
		.bit = ??,
	पूर्ण  ** VP7A */
पूर्ण;

अटल पूर्णांक पूर्णांकel_cht_wc_pmic_get_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
		पूर्णांक bit, u64 *value)
अणु
	पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = (data & bit) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_cht_wc_pmic_update_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
		पूर्णांक biपंचांगask, bool on)
अणु
	वापस regmap_update_bits(regmap, reg, biपंचांगask, on ? 1 : 0);
पूर्ण

अटल पूर्णांक पूर्णांकel_cht_wc_exec_mipi_pmic_seq_element(काष्ठा regmap *regmap,
						   u16 i2c_client_address,
						   u32 reg_address,
						   u32 value, u32 mask)
अणु
	u32 address;

	अगर (i2c_client_address > 0xff || reg_address > 0xff) अणु
		pr_warn("%s warning addresses too big client 0x%x reg 0x%x\n",
			__func__, i2c_client_address, reg_address);
		वापस -दुस्फल;
	पूर्ण

	address = (i2c_client_address << 8) | reg_address;

	वापस regmap_update_bits(regmap, address, mask, value);
पूर्ण

/*
 * The thermal table and ops are empty, we करो not support the Thermal opregion
 * (DPTF) due to lacking करोcumentation.
 */
अटल काष्ठा पूर्णांकel_pmic_opregion_data पूर्णांकel_cht_wc_pmic_opregion_data = अणु
	.get_घातer		= पूर्णांकel_cht_wc_pmic_get_घातer,
	.update_घातer		= पूर्णांकel_cht_wc_pmic_update_घातer,
	.exec_mipi_pmic_seq_element = पूर्णांकel_cht_wc_exec_mipi_pmic_seq_element,
	.घातer_table		= घातer_table,
	.घातer_table_count	= ARRAY_SIZE(घातer_table),
पूर्ण;

अटल पूर्णांक पूर्णांकel_cht_wc_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);

	वापस पूर्णांकel_pmic_install_opregion_handler(&pdev->dev,
			ACPI_HANDLE(pdev->dev.parent),
			pmic->regmap,
			&पूर्णांकel_cht_wc_pmic_opregion_data);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cht_wc_opregion_id_table[] = अणु
	अणु .name = "cht_wcove_region" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_cht_wc_pmic_opregion_driver = अणु
	.probe = पूर्णांकel_cht_wc_pmic_opregion_probe,
	.driver = अणु
		.name = "cht_whiskey_cove_pmic",
	पूर्ण,
	.id_table = cht_wc_opregion_id_table,
पूर्ण;
builtin_platक्रमm_driver(पूर्णांकel_cht_wc_pmic_opregion_driver);
