<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel BXT WhiskeyCove PMIC operation region driver
 *
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "intel_pmic.h"

#घोषणा WHISKEY_COVE_ALRT_HIGH_BIT_MASK 0x0F
#घोषणा WHISKEY_COVE_ADC_HIGH_BIT(x)	(((x & 0x0F) << 8))
#घोषणा WHISKEY_COVE_ADC_CURSRC(x)	(((x & 0xF0) >> 4))
#घोषणा VR_MODE_DISABLED        0
#घोषणा VR_MODE_AUTO            BIT(0)
#घोषणा VR_MODE_NORMAL          BIT(1)
#घोषणा VR_MODE_SWITCH          BIT(2)
#घोषणा VR_MODE_ECO             (BIT(0)|BIT(1))
#घोषणा VSWITCH2_OUTPUT         BIT(5)
#घोषणा VSWITCH1_OUTPUT         BIT(4)
#घोषणा VUSBPHY_CHARGE          BIT(1)

अटल काष्ठा pmic_table घातer_table[] = अणु
	अणु
		.address = 0x0,
		.reg = 0x63,
		.bit = VR_MODE_AUTO,
	पूर्ण, /* VDD1 -> VDD1CNT */
	अणु
		.address = 0x04,
		.reg = 0x65,
		.bit = VR_MODE_AUTO,
	पूर्ण, /* VDD2 -> VDD2CNT */
	अणु
		.address = 0x08,
		.reg = 0x67,
		.bit = VR_MODE_AUTO,
	पूर्ण, /* VDD3 -> VDD3CNT */
	अणु
		.address = 0x0c,
		.reg = 0x6d,
		.bit = VR_MODE_AUTO,
	पूर्ण, /* VLFX -> VFLEXCNT */
	अणु
		.address = 0x10,
		.reg = 0x6f,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP1A -> VPROG1ACNT */
	अणु
		.address = 0x14,
		.reg = 0x70,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP1B -> VPROG1BCNT */
	अणु
		.address = 0x18,
		.reg = 0x71,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP1C -> VPROG1CCNT */
	अणु
		.address = 0x1c,
		.reg = 0x72,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP1D -> VPROG1DCNT */
	अणु
		.address = 0x20,
		.reg = 0x73,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP2A -> VPROG2ACNT */
	अणु
		.address = 0x24,
		.reg = 0x74,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP2B -> VPROG2BCNT */
	अणु
		.address = 0x28,
		.reg = 0x75,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP2C -> VPROG2CCNT */
	अणु
		.address = 0x2c,
		.reg = 0x76,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP3A -> VPROG3ACNT */
	अणु
		.address = 0x30,
		.reg = 0x77,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP3B -> VPROG3BCNT */
	अणु
		.address = 0x34,
		.reg = 0x78,
		.bit = VSWITCH2_OUTPUT,
	पूर्ण, /* VSW2 -> VLD0CNT Bit 5*/
	अणु
		.address = 0x38,
		.reg = 0x78,
		.bit = VSWITCH1_OUTPUT,
	पूर्ण, /* VSW1 -> VLD0CNT Bit 4 */
	अणु
		.address = 0x3c,
		.reg = 0x78,
		.bit = VUSBPHY_CHARGE,
	पूर्ण, /* VUPY -> VLDOCNT Bit 1 */
	अणु
		.address = 0x40,
		.reg = 0x7b,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VRSO -> VREFSOCCNT*/
	अणु
		.address = 0x44,
		.reg = 0xA0,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP1E -> VPROG1ECNT */
	अणु
		.address = 0x48,
		.reg = 0xA1,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP1F -> VPROG1FCNT */
	अणु
		.address = 0x4c,
		.reg = 0xA2,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP2D -> VPROG2DCNT */
	अणु
		.address = 0x50,
		.reg = 0xA3,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP4A -> VPROG4ACNT */
	अणु
		.address = 0x54,
		.reg = 0xA4,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP4B -> VPROG4BCNT */
	अणु
		.address = 0x58,
		.reg = 0xA5,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP4C -> VPROG4CCNT */
	अणु
		.address = 0x5c,
		.reg = 0xA6,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP4D -> VPROG4DCNT */
	अणु
		.address = 0x60,
		.reg = 0xA7,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP5A -> VPROG5ACNT */
	अणु
		.address = 0x64,
		.reg = 0xA8,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP5B -> VPROG5BCNT */
	अणु
		.address = 0x68,
		.reg = 0xA9,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP6A -> VPROG6ACNT */
	अणु
		.address = 0x6c,
		.reg = 0xAA,
		.bit = VR_MODE_NORMAL,
	पूर्ण, /* VP6B -> VPROG6BCNT */
	अणु
		.address = 0x70,
		.reg = 0x36,
		.bit = BIT(2),
	पूर्ण, /* SDWN_N -> MODEMCTRL Bit 2 */
	अणु
		.address = 0x74,
		.reg = 0x36,
		.bit = BIT(0),
	पूर्ण /* MOFF -> MODEMCTRL Bit 0 */
पूर्ण;

अटल काष्ठा pmic_table thermal_table[] = अणु
	अणु
		.address = 0x00,
		.reg = 0x4F39
	पूर्ण,
	अणु
		.address = 0x04,
		.reg = 0x4F24
	पूर्ण,
	अणु
		.address = 0x08,
		.reg = 0x4F26
	पूर्ण,
	अणु
		.address = 0x0c,
		.reg = 0x4F3B
	पूर्ण,
	अणु
		.address = 0x10,
		.reg = 0x4F28
	पूर्ण,
	अणु
		.address = 0x14,
		.reg = 0x4F2A
	पूर्ण,
	अणु
		.address = 0x18,
		.reg = 0x4F3D
	पूर्ण,
	अणु
		.address = 0x1c,
		.reg = 0x4F2C
	पूर्ण,
	अणु
		.address = 0x20,
		.reg = 0x4F2E
	पूर्ण,
	अणु
		.address = 0x24,
		.reg = 0x4F3F
	पूर्ण,
	अणु
		.address = 0x28,
		.reg = 0x4F30
	पूर्ण,
	अणु
		.address = 0x30,
		.reg = 0x4F41
	पूर्ण,
	अणु
		.address = 0x34,
		.reg = 0x4F32
	पूर्ण,
	अणु
		.address = 0x3c,
		.reg = 0x4F43
	पूर्ण,
	अणु
		.address = 0x40,
		.reg = 0x4F34
	पूर्ण,
	अणु
		.address = 0x48,
		.reg = 0x4F6A,
		.bit = 0,
	पूर्ण,
	अणु
		.address = 0x4C,
		.reg = 0x4F6A,
		.bit = 1
	पूर्ण,
	अणु
		.address = 0x50,
		.reg = 0x4F6A,
		.bit = 2
	पूर्ण,
	अणु
		.address = 0x54,
		.reg = 0x4F6A,
		.bit = 4
	पूर्ण,
	अणु
		.address = 0x58,
		.reg = 0x4F6A,
		.bit = 5
	पूर्ण,
	अणु
		.address = 0x5C,
		.reg = 0x4F6A,
		.bit = 3
	पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकel_bxtwc_pmic_get_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
		पूर्णांक bit, u64 *value)
अणु
	पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = (data & bit) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bxtwc_pmic_update_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
		पूर्णांक bit, bool on)
अणु
	u8 val, mask = bit;

	अगर (on)
		val = 0xFF;
	अन्यथा
		val = 0x0;

	वापस regmap_update_bits(regmap, reg, mask, val);
पूर्ण

अटल पूर्णांक पूर्णांकel_bxtwc_pmic_get_raw_temp(काष्ठा regmap *regmap, पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val, adc_val, reg_val;
	u8 temp_l, temp_h, cursrc;
	अचिन्हित दीर्घ rlsb;
	अटल स्थिर अचिन्हित दीर्घ rlsb_array[] = अणु
		0, 260420, 130210, 65100, 32550, 16280,
		8140, 4070, 2030, 0, 260420, 130210 पूर्ण;

	अगर (regmap_पढ़ो(regmap, reg, &val))
		वापस -EIO;
	temp_l = (u8) val;

	अगर (regmap_पढ़ो(regmap, (reg - 1), &val))
		वापस -EIO;
	temp_h = (u8) val;

	reg_val = temp_l | WHISKEY_COVE_ADC_HIGH_BIT(temp_h);
	cursrc = WHISKEY_COVE_ADC_CURSRC(temp_h);
	rlsb = rlsb_array[cursrc];
	adc_val = reg_val * rlsb / 1000;

	वापस adc_val;
पूर्ण

अटल पूर्णांक
पूर्णांकel_bxtwc_pmic_update_aux(काष्ठा regmap *regmap, पूर्णांक reg, पूर्णांक raw)
अणु
	u32 bsr_num;
	u16 resi_val, count = 0, thrsh = 0;
	u8 alrt_h, alrt_l, cursel = 0;

	bsr_num = raw;
	bsr_num /= (1 << 5);

	count = fls(bsr_num) - 1;

	cursel = clamp_t(s8, (count - 7), 0, 7);
	thrsh = raw / (1 << (4 + cursel));

	resi_val = (cursel << 9) | thrsh;
	alrt_h = (resi_val >> 8) & WHISKEY_COVE_ALRT_HIGH_BIT_MASK;
	अगर (regmap_update_bits(regmap,
				reg - 1,
				WHISKEY_COVE_ALRT_HIGH_BIT_MASK,
				alrt_h))
		वापस -EIO;

	alrt_l = (u8)resi_val;
	वापस regmap_ग_लिखो(regmap, reg, alrt_l);
पूर्ण

अटल पूर्णांक
पूर्णांकel_bxtwc_pmic_get_policy(काष्ठा regmap *regmap, पूर्णांक reg, पूर्णांक bit, u64 *value)
अणु
	u8 mask = BIT(bit);
	अचिन्हित पूर्णांक val;

	अगर (regmap_पढ़ो(regmap, reg, &val))
		वापस -EIO;

	*value = (val & mask) >> bit;
	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_bxtwc_pmic_update_policy(काष्ठा regmap *regmap,
				पूर्णांक reg, पूर्णांक bit, पूर्णांक enable)
अणु
	u8 mask = BIT(bit), val = enable << bit;

	वापस regmap_update_bits(regmap, reg, mask, val);
पूर्ण

अटल काष्ठा पूर्णांकel_pmic_opregion_data पूर्णांकel_bxtwc_pmic_opregion_data = अणु
	.get_घातer      = पूर्णांकel_bxtwc_pmic_get_घातer,
	.update_घातer   = पूर्णांकel_bxtwc_pmic_update_घातer,
	.get_raw_temp   = पूर्णांकel_bxtwc_pmic_get_raw_temp,
	.update_aux     = पूर्णांकel_bxtwc_pmic_update_aux,
	.get_policy     = पूर्णांकel_bxtwc_pmic_get_policy,
	.update_policy  = पूर्णांकel_bxtwc_pmic_update_policy,
	.घातer_table      = घातer_table,
	.घातer_table_count = ARRAY_SIZE(घातer_table),
	.thermal_table     = thermal_table,
	.thermal_table_count = ARRAY_SIZE(thermal_table),
पूर्ण;

अटल पूर्णांक पूर्णांकel_bxtwc_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);

	वापस पूर्णांकel_pmic_install_opregion_handler(&pdev->dev,
			ACPI_HANDLE(pdev->dev.parent),
			pmic->regmap,
			&पूर्णांकel_bxtwc_pmic_opregion_data);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bxt_wc_opregion_id_table[] = अणु
	अणु .name = "bxt_wcove_region" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_bxtwc_pmic_opregion_driver = अणु
	.probe = पूर्णांकel_bxtwc_pmic_opregion_probe,
	.driver = अणु
		.name = "bxt_whiskey_cove_pmic",
	पूर्ण,
	.id_table = bxt_wc_opregion_id_table,
पूर्ण;
builtin_platक्रमm_driver(पूर्णांकel_bxtwc_pmic_opregion_driver);
