<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Bay Trail Crystal Cove PMIC operation region driver
 *
 * Copyright (C) 2014 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश "intel_pmic.h"

#घोषणा PWR_SOURCE_SELECT	BIT(1)

#घोषणा PMIC_A0LOCK_REG		0xc5

अटल काष्ठा pmic_table घातer_table[] = अणु
/*	अणु
		.address = 0x00,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** VSYS */
	अणु
		.address = 0x04,
		.reg = 0x63,
		.bit = 0x00,
	पूर्ण, /* SYSX -> VSYS_SX */
	अणु
		.address = 0x08,
		.reg = 0x62,
		.bit = 0x00,
	पूर्ण, /* SYSU -> VSYS_U */
	अणु
		.address = 0x0c,
		.reg = 0x64,
		.bit = 0x00,
	पूर्ण, /* SYSS -> VSYS_S */
	अणु
		.address = 0x10,
		.reg = 0x6a,
		.bit = 0x00,
	पूर्ण, /* V50S -> V5P0S */
	अणु
		.address = 0x14,
		.reg = 0x6b,
		.bit = 0x00,
	पूर्ण, /* HOST -> VHOST, USB2/3 host */
	अणु
		.address = 0x18,
		.reg = 0x6c,
		.bit = 0x00,
	पूर्ण, /* VBUS -> VBUS, USB2/3 OTG */
	अणु
		.address = 0x1c,
		.reg = 0x6d,
		.bit = 0x00,
	पूर्ण, /* HDMI -> VHDMI */
/*	अणु
		.address = 0x20,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** S285 */
	अणु
		.address = 0x24,
		.reg = 0x66,
		.bit = 0x00,
	पूर्ण, /* X285 -> V2P85SX, camera */
/*	अणु
		.address = 0x28,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** V33A */
	अणु
		.address = 0x2c,
		.reg = 0x69,
		.bit = 0x00,
	पूर्ण, /* V33S -> V3P3S, display/ssd/audio */
	अणु
		.address = 0x30,
		.reg = 0x68,
		.bit = 0x00,
	पूर्ण, /* V33U -> V3P3U, SDIO wअगरi&bt */
/*	अणु
		.address = 0x34 .. 0x40,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** V33I, V18A, REFQ, V12A */
	अणु
		.address = 0x44,
		.reg = 0x5c,
		.bit = 0x00,
	पूर्ण, /* V18S -> V1P8S, SOC/USB PHY/SIM */
	अणु
		.address = 0x48,
		.reg = 0x5d,
		.bit = 0x00,
	पूर्ण, /* V18X -> V1P8SX, eMMC/camara/audio */
	अणु
		.address = 0x4c,
		.reg = 0x5b,
		.bit = 0x00,
	पूर्ण, /* V18U -> V1P8U, LPDDR */
	अणु
		.address = 0x50,
		.reg = 0x61,
		.bit = 0x00,
	पूर्ण, /* V12X -> V1P2SX, SOC SFR */
	अणु
		.address = 0x54,
		.reg = 0x60,
		.bit = 0x00,
	पूर्ण, /* V12S -> V1P2S, MIPI */
/*	अणु
		.address = 0x58,
		.reg = ??,
		.bit = ??,
	पूर्ण, ** V10A */
	अणु
		.address = 0x5c,
		.reg = 0x56,
		.bit = 0x00,
	पूर्ण, /* V10S -> V1P0S, SOC GFX */
	अणु
		.address = 0x60,
		.reg = 0x57,
		.bit = 0x00,
	पूर्ण, /* V10X -> V1P0SX, SOC display/DDR IO/PCIe */
	अणु
		.address = 0x64,
		.reg = 0x59,
		.bit = 0x00,
	पूर्ण, /* V105 -> V1P05S, L2 SRAM */
पूर्ण;

अटल काष्ठा pmic_table thermal_table[] = अणु
	अणु
		.address = 0x00,
		.reg = 0x75
	पूर्ण,
	अणु
		.address = 0x04,
		.reg = 0x95
	पूर्ण,
	अणु
		.address = 0x08,
		.reg = 0x97
	पूर्ण,
	अणु
		.address = 0x0c,
		.reg = 0x77
	पूर्ण,
	अणु
		.address = 0x10,
		.reg = 0x9a
	पूर्ण,
	अणु
		.address = 0x14,
		.reg = 0x9c
	पूर्ण,
	अणु
		.address = 0x18,
		.reg = 0x79
	पूर्ण,
	अणु
		.address = 0x1c,
		.reg = 0x9f
	पूर्ण,
	अणु
		.address = 0x20,
		.reg = 0xa1
	पूर्ण,
	अणु
		.address = 0x48,
		.reg = 0x94
	पूर्ण,
	अणु
		.address = 0x4c,
		.reg = 0x99
	पूर्ण,
	अणु
		.address = 0x50,
		.reg = 0x9e
	पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकel_crc_pmic_get_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
				    पूर्णांक bit, u64 *value)
अणु
	पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = (data & PWR_SOURCE_SELECT) && (data & BIT(bit)) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_crc_pmic_update_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
				       पूर्णांक bit, bool on)
अणु
	पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	अगर (on) अणु
		data |= PWR_SOURCE_SELECT | BIT(bit);
	पूर्ण अन्यथा अणु
		data &= ~BIT(bit);
		data |= PWR_SOURCE_SELECT;
	पूर्ण

	अगर (regmap_ग_लिखो(regmap, reg, data))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_crc_pmic_get_raw_temp(काष्ठा regmap *regmap, पूर्णांक reg)
अणु
	पूर्णांक temp_l, temp_h;

	/*
	 * Raw temperature value is 10bits: 8bits in reg
	 * and 2bits in reg-1: bit0,1
	 */
	अगर (regmap_पढ़ो(regmap, reg, &temp_l) ||
	    regmap_पढ़ो(regmap, reg - 1, &temp_h))
		वापस -EIO;

	वापस temp_l | (temp_h & 0x3) << 8;
पूर्ण

अटल पूर्णांक पूर्णांकel_crc_pmic_update_aux(काष्ठा regmap *regmap, पूर्णांक reg, पूर्णांक raw)
अणु
	वापस regmap_ग_लिखो(regmap, reg, raw) ||
		regmap_update_bits(regmap, reg - 1, 0x3, raw >> 8) ? -EIO : 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_crc_pmic_get_policy(काष्ठा regmap *regmap,
					पूर्णांक reg, पूर्णांक bit, u64 *value)
अणु
	पूर्णांक pen;

	अगर (regmap_पढ़ो(regmap, reg, &pen))
		वापस -EIO;
	*value = pen >> 7;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_crc_pmic_update_policy(काष्ठा regmap *regmap,
					पूर्णांक reg, पूर्णांक bit, पूर्णांक enable)
अणु
	पूर्णांक alert0;

	/* Update to policy enable bit requires unlocking a0lock */
	अगर (regmap_पढ़ो(regmap, PMIC_A0LOCK_REG, &alert0))
		वापस -EIO;

	अगर (regmap_update_bits(regmap, PMIC_A0LOCK_REG, 0x01, 0))
		वापस -EIO;

	अगर (regmap_update_bits(regmap, reg, 0x80, enable << 7))
		वापस -EIO;

	/* restore alert0 */
	अगर (regmap_ग_लिखो(regmap, PMIC_A0LOCK_REG, alert0))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_pmic_opregion_data पूर्णांकel_crc_pmic_opregion_data = अणु
	.get_घातer	= पूर्णांकel_crc_pmic_get_घातer,
	.update_घातer	= पूर्णांकel_crc_pmic_update_घातer,
	.get_raw_temp	= पूर्णांकel_crc_pmic_get_raw_temp,
	.update_aux	= पूर्णांकel_crc_pmic_update_aux,
	.get_policy	= पूर्णांकel_crc_pmic_get_policy,
	.update_policy	= पूर्णांकel_crc_pmic_update_policy,
	.घातer_table	= घातer_table,
	.घातer_table_count= ARRAY_SIZE(घातer_table),
	.thermal_table	= thermal_table,
	.thermal_table_count = ARRAY_SIZE(thermal_table),
पूर्ण;

अटल पूर्णांक पूर्णांकel_crc_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	वापस पूर्णांकel_pmic_install_opregion_handler(&pdev->dev,
			ACPI_HANDLE(pdev->dev.parent), pmic->regmap,
			&पूर्णांकel_crc_pmic_opregion_data);
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_crc_pmic_opregion_driver = अणु
	.probe = पूर्णांकel_crc_pmic_opregion_probe,
	.driver = अणु
		.name = "byt_crystal_cove_pmic",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(पूर्णांकel_crc_pmic_opregion_driver);
