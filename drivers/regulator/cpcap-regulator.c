<शैली गुरु>
/*
 * Motorola CPCAP PMIC regulator driver
 *
 * Based on cpcap-regulator.c from Motorola Linux kernel tree
 * Copyright (C) 2009-2011 Motorola, Inc.
 *
 * Rewritten क्रम मुख्यline kernel to use device tree and regmap
 * Copyright (C) 2017 Tony Lindgren <tony@atomide.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/motorola-cpcap.h>

/*
 * Resource assignment रेजिस्टर bits. These seem to control the state
 * idle modes adn are used at least क्रम omap4.
 */

/* CPCAP_REG_ASSIGN2 bits - Resource Assignment 2 */
#घोषणा CPCAP_BIT_VSDIO_SEL		BIT(15)
#घोषणा CPCAP_BIT_VDIG_SEL		BIT(14)
#घोषणा CPCAP_BIT_VCAM_SEL		BIT(13)
#घोषणा CPCAP_BIT_SW6_SEL		BIT(12)
#घोषणा CPCAP_BIT_SW5_SEL		BIT(11)
#घोषणा CPCAP_BIT_SW4_SEL		BIT(10)
#घोषणा CPCAP_BIT_SW3_SEL		BIT(9)
#घोषणा CPCAP_BIT_SW2_SEL		BIT(8)
#घोषणा CPCAP_BIT_SW1_SEL		BIT(7)

/* CPCAP_REG_ASSIGN3 bits - Resource Assignment 3 */
#घोषणा CPCAP_BIT_VUSBINT2_SEL		BIT(15)
#घोषणा CPCAP_BIT_VUSBINT1_SEL		BIT(14)
#घोषणा CPCAP_BIT_VVIB_SEL		BIT(13)
#घोषणा CPCAP_BIT_VWLAN1_SEL		BIT(12)
#घोषणा CPCAP_BIT_VRF1_SEL		BIT(11)
#घोषणा CPCAP_BIT_VHVIO_SEL		BIT(10)
#घोषणा CPCAP_BIT_VDAC_SEL		BIT(9)
#घोषणा CPCAP_BIT_VUSB_SEL		BIT(8)
#घोषणा CPCAP_BIT_VSIM_SEL		BIT(7)
#घोषणा CPCAP_BIT_VRFREF_SEL		BIT(6)
#घोषणा CPCAP_BIT_VPLL_SEL		BIT(5)
#घोषणा CPCAP_BIT_VFUSE_SEL		BIT(4)
#घोषणा CPCAP_BIT_VCSI_SEL		BIT(3)
#घोषणा CPCAP_BIT_SPARE_14_2		BIT(2)
#घोषणा CPCAP_BIT_VWLAN2_SEL		BIT(1)
#घोषणा CPCAP_BIT_VRF2_SEL		BIT(0)

/* CPCAP_REG_ASSIGN4 bits - Resource Assignment 4 */
#घोषणा CPCAP_BIT_VAUDIO_SEL		BIT(0)

/*
 * Enable रेजिस्टर bits. At least CPCAP_BIT_AUDIO_LOW_PWR is generic,
 * and not limited to audio regulator. Let's use the Motorola kernel
 * naming क्रम now until we have a better understanding of the other
 * enable रेजिस्टर bits. No idea why BIT(3) is not defined.
 */
#घोषणा CPCAP_BIT_AUDIO_LOW_PWR		BIT(6)
#घोषणा CPCAP_BIT_AUD_LOWPWR_SPEED	BIT(5)
#घोषणा CPCAP_BIT_VAUDIOPRISTBY		BIT(4)
#घोषणा CPCAP_BIT_VAUDIO_MODE1		BIT(2)
#घोषणा CPCAP_BIT_VAUDIO_MODE0		BIT(1)
#घोषणा CPCAP_BIT_V_AUDIO_EN		BIT(0)

#घोषणा CPCAP_BIT_AUDIO_NORMAL_MODE	0x00

/*
 * Off mode configuration bit. Used currently only by SW5 on omap4. There's
 * the following comment in Motorola Linux kernel tree क्रम it:
 *
 * When set in the regulator mode, the regulator assignment will be changed
 * to secondary when the regulator is disabled. The mode will be set back to
 * primary when the regulator is turned on.
 */
#घोषणा CPCAP_REG_OFF_MODE_SEC		BIT(15)

/*
 * SoC specअगरic configuration क्रम CPCAP regulator. There are at least three
 * dअगरferent SoCs each with their own parameters: omap3, omap4 and tegra2.
 *
 * The assign_reg and assign_mask seem to allow toggling between primary
 * and secondary mode that at least omap4 uses क्रम off mode.
 */
काष्ठा cpcap_regulator अणु
	काष्ठा regulator_desc rdesc;
	स्थिर u16 assign_reg;
	स्थिर u16 assign_mask;
पूर्ण;

#घोषणा CPCAP_REG(_ID, reg, assignment_reg, assignment_mask, val_tbl,	\
		mode_mask, volt_mask, mode_val, off_val,		\
		volt_trans_समय) अणु					\
	.rdesc = अणु							\
		.name = #_ID,						\
		.of_match = of_match_ptr(#_ID),				\
		.ops = &cpcap_regulator_ops,				\
		.regulators_node = of_match_ptr("regulators"),		\
		.type = REGULATOR_VOLTAGE,				\
		.id = CPCAP_##_ID,					\
		.owner = THIS_MODULE,					\
		.n_voltages = ARRAY_SIZE(val_tbl),			\
		.volt_table = (val_tbl),				\
		.vsel_reg = (reg),					\
		.vsel_mask = (volt_mask),				\
		.enable_reg = (reg),					\
		.enable_mask = (mode_mask),				\
		.enable_val = (mode_val),				\
		.disable_val = (off_val),				\
		.ramp_delay = (volt_trans_समय),			\
		.of_map_mode = cpcap_map_mode,				\
	पूर्ण,								\
	.assign_reg = (assignment_reg),					\
	.assign_mask = (assignment_mask),				\
पूर्ण

काष्ठा cpcap_ddata अणु
	काष्ठा regmap *reg;
	काष्ठा device *dev;
	स्थिर काष्ठा cpcap_regulator *soc;
पूर्ण;

क्रमागत cpcap_regulator_id अणु
	CPCAP_SW1,
	CPCAP_SW2,
	CPCAP_SW3,
	CPCAP_SW4,
	CPCAP_SW5,
	CPCAP_SW6,
	CPCAP_VCAM,
	CPCAP_VCSI,
	CPCAP_VDAC,
	CPCAP_VDIG,
	CPCAP_VFUSE,
	CPCAP_VHVIO,
	CPCAP_VSDIO,
	CPCAP_VPLL,
	CPCAP_VRF1,
	CPCAP_VRF2,
	CPCAP_VRFREF,
	CPCAP_VWLAN1,
	CPCAP_VWLAN2,
	CPCAP_VSIM,
	CPCAP_VSIMCARD,
	CPCAP_VVIB,
	CPCAP_VUSB,
	CPCAP_VAUDIO,
	CPCAP_NR_REGULATORS,
पूर्ण;

/*
 * We need to also configure regulator idle mode क्रम SoC off mode अगर
 * CPCAP_REG_OFF_MODE_SEC is set.
 */
अटल पूर्णांक cpcap_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा cpcap_regulator *regulator = rdev_get_drvdata(rdev);
	पूर्णांक error;

	error = regulator_enable_regmap(rdev);
	अगर (error)
		वापस error;

	अगर (rdev->desc->enable_val & CPCAP_REG_OFF_MODE_SEC) अणु
		error = regmap_update_bits(rdev->regmap, regulator->assign_reg,
					   regulator->assign_mask,
					   regulator->assign_mask);
		अगर (error)
			regulator_disable_regmap(rdev);
	पूर्ण

	वापस error;
पूर्ण

/*
 * We need to also configure regulator idle mode क्रम SoC off mode अगर
 * CPCAP_REG_OFF_MODE_SEC is set.
 */
अटल पूर्णांक cpcap_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा cpcap_regulator *regulator = rdev_get_drvdata(rdev);
	पूर्णांक error;

	अगर (rdev->desc->enable_val & CPCAP_REG_OFF_MODE_SEC) अणु
		error = regmap_update_bits(rdev->regmap, regulator->assign_reg,
					   regulator->assign_mask, 0);
		अगर (error)
			वापस error;
	पूर्ण

	error = regulator_disable_regmap(rdev);
	अगर (error && (rdev->desc->enable_val & CPCAP_REG_OFF_MODE_SEC)) अणु
		regmap_update_bits(rdev->regmap, regulator->assign_reg,
				   regulator->assign_mask,
				   regulator->assign_mask);
	पूर्ण

	वापस error;
पूर्ण

अटल अचिन्हित पूर्णांक cpcap_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल CPCAP_BIT_AUDIO_NORMAL_MODE:
		वापस REGULATOR_MODE_NORMAL;
	हाल CPCAP_BIT_AUDIO_LOW_PWR:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक cpcap_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक value;

	regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &value);

	अगर (value & CPCAP_BIT_AUDIO_LOW_PWR)
		वापस REGULATOR_MODE_STANDBY;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक cpcap_regulator_set_mode(काष्ठा regulator_dev *rdev,
				    अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक value;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		value = CPCAP_BIT_AUDIO_NORMAL_MODE;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		value = CPCAP_BIT_AUDIO_LOW_PWR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  CPCAP_BIT_AUDIO_LOW_PWR, value);
पूर्ण

अटल स्थिर काष्ठा regulator_ops cpcap_regulator_ops = अणु
	.enable = cpcap_regulator_enable,
	.disable = cpcap_regulator_disable,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = cpcap_regulator_get_mode,
	.set_mode = cpcap_regulator_set_mode,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक unknown_val_tbl[] = अणु 0, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sw2_sw4_val_tbl[] = अणु 612500, 625000, 637500,
						650000, 662500, 675000,
						687500, 700000, 712500,
						725000, 737500, 750000,
						762500, 775000, 787500,
						800000, 812500, 825000,
						837500, 850000, 862500,
						875000, 887500, 900000,
						912500, 925000, 937500,
						950000, 962500, 975000,
						987500, 1000000, 1012500,
						1025000, 1037500, 1050000,
						1062500, 1075000, 1087500,
						1100000, 1112500, 1125000,
						1137500, 1150000, 1162500,
						1175000, 1187500, 1200000,
						1212500, 1225000, 1237500,
						1250000, 1262500, 1275000,
						1287500, 1300000, 1312500,
						1325000, 1337500, 1350000,
						1362500, 1375000, 1387500,
						1400000, 1412500, 1425000,
						1437500, 1450000, 1462500, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sw5_val_tbl[] = अणु 0, 5050000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vcam_val_tbl[] = अणु 2600000, 2700000, 2800000,
					     2900000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vcsi_val_tbl[] = अणु 1200000, 1800000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vdac_val_tbl[] = अणु 1200000, 1500000, 1800000,
					     2500000,पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vdig_val_tbl[] = अणु 1200000, 1350000, 1500000,
					     1875000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vfuse_val_tbl[] = अणु 1500000, 1600000, 1700000,
					      1800000, 1900000, 2000000,
					      2100000, 2200000, 2300000,
					      2400000, 2500000, 2600000,
					      2700000, 3150000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vhvio_val_tbl[] = अणु 2775000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vsdio_val_tbl[] = अणु 1500000, 1600000, 1800000,
					      2600000, 2700000, 2800000,
					      2900000, 3000000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vpll_val_tbl[] = अणु 1200000, 1300000, 1400000,
					     1800000, पूर्ण;
/* Quirk: 2775000 is beक्रमe 2500000 क्रम vrf1 regulator */
अटल स्थिर अचिन्हित पूर्णांक vrf1_val_tbl[] = अणु 2775000, 2500000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vrf2_val_tbl[] = अणु 0, 2775000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vrfref_val_tbl[] = अणु 2500000, 2775000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vwlan1_val_tbl[] = अणु 1800000, 1900000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vwlan2_val_tbl[] = अणु 2775000, 3000000, 3300000,
					       3300000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vsim_val_tbl[] = अणु 1800000, 2900000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vsimcard_val_tbl[] = अणु 1800000, 2900000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vvib_val_tbl[] = अणु 1300000, 1800000, 2000000,
					     3000000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vusb_val_tbl[] = अणु 0, 3300000, पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vaudio_val_tbl[] = अणु 0, 2775000, पूर्ण;

/*
 * SoC specअगरic configuration क्रम omap4. The data below is comes from Motorola
 * Linux kernel tree. It's basically the values of cpcap_regltr_data,
 * cpcap_regulator_mode_values and cpcap_regulator_off_mode_values, see
 * CPCAP_REG macro above.
 *
 * SW1 to SW4 and SW6 seems to be unused क्रम mapphone. Note that VSIM and
 * VSIMCARD have a shared resource assignment bit.
 */
अटल स्थिर काष्ठा cpcap_regulator omap4_regulators[] = अणु
	CPCAP_REG(SW1, CPCAP_REG_S1C1, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW1_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(SW2, CPCAP_REG_S2C1, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW2_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(SW3, CPCAP_REG_S3C, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW3_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(SW4, CPCAP_REG_S4C1, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW4_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(SW5, CPCAP_REG_S5C, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW5_SEL, sw5_val_tbl,
		  0x28, 0, 0x20 | CPCAP_REG_OFF_MODE_SEC, 0, 0),
	CPCAP_REG(SW6, CPCAP_REG_S6C, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW6_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(VCAM, CPCAP_REG_VCAMC, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_VCAM_SEL, vcam_val_tbl,
		  0x87, 0x30, 0x3, 0, 420),
	CPCAP_REG(VCSI, CPCAP_REG_VCSIC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VCSI_SEL, vcsi_val_tbl,
		  0x47, 0x10, 0x43, 0x41, 350),
	CPCAP_REG(VDAC, CPCAP_REG_VDACC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VDAC_SEL, vdac_val_tbl,
		  0x87, 0x30, 0x3, 0, 420),
	CPCAP_REG(VDIG, CPCAP_REG_VDIGC, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_VDIG_SEL, vdig_val_tbl,
		  0x87, 0x30, 0x82, 0, 420),
	CPCAP_REG(VFUSE, CPCAP_REG_VFUSEC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VFUSE_SEL, vfuse_val_tbl,
		  0x80, 0xf, 0x80, 0, 420),
	CPCAP_REG(VHVIO, CPCAP_REG_VHVIOC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VHVIO_SEL, vhvio_val_tbl,
		  0x17, 0, 0, 0x12, 0),
	CPCAP_REG(VSDIO, CPCAP_REG_VSDIOC, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_VSDIO_SEL, vsdio_val_tbl,
		  0x87, 0x38, 0x82, 0, 420),
	CPCAP_REG(VPLL, CPCAP_REG_VPLLC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VPLL_SEL, vpll_val_tbl,
		  0x43, 0x18, 0x2, 0, 420),
	CPCAP_REG(VRF1, CPCAP_REG_VRF1C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VRF1_SEL, vrf1_val_tbl,
		  0xac, 0x2, 0x4, 0, 10),
	CPCAP_REG(VRF2, CPCAP_REG_VRF2C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VRF2_SEL, vrf2_val_tbl,
		  0x23, 0x8, 0, 0, 10),
	CPCAP_REG(VRFREF, CPCAP_REG_VRFREFC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VRFREF_SEL, vrfref_val_tbl,
		  0x23, 0x8, 0, 0, 420),
	CPCAP_REG(VWLAN1, CPCAP_REG_VWLAN1C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VWLAN1_SEL, vwlan1_val_tbl,
		  0x47, 0x10, 0, 0, 420),
	CPCAP_REG(VWLAN2, CPCAP_REG_VWLAN2C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VWLAN2_SEL, vwlan2_val_tbl,
		  0x20c, 0xc0, 0x20c, 0, 420),
	CPCAP_REG(VSIM, CPCAP_REG_VSIMC, CPCAP_REG_ASSIGN3,
		  0xffff, vsim_val_tbl,
		  0x23, 0x8, 0x3, 0, 420),
	CPCAP_REG(VSIMCARD, CPCAP_REG_VSIMC, CPCAP_REG_ASSIGN3,
		  0xffff, vsimcard_val_tbl,
		  0x1e80, 0x8, 0x1e00, 0, 420),
	CPCAP_REG(VVIB, CPCAP_REG_VVIBC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VVIB_SEL, vvib_val_tbl,
		  0x1, 0xc, 0x1, 0, 500),
	CPCAP_REG(VUSB, CPCAP_REG_VUSBC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VUSB_SEL, vusb_val_tbl,
		  0x11c, 0x40, 0xc, 0, 0),
	CPCAP_REG(VAUDIO, CPCAP_REG_VAUDIOC, CPCAP_REG_ASSIGN4,
		  CPCAP_BIT_VAUDIO_SEL, vaudio_val_tbl,
		  0x16, 0x1, 0x4, 0, 0),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cpcap_regulator xoom_regulators[] = अणु
	CPCAP_REG(SW1, CPCAP_REG_S1C1, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW1_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(SW2, CPCAP_REG_S2C1, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW2_SEL, sw2_sw4_val_tbl,
		  0xf00, 0x7f, 0x800, 0, 120),
	CPCAP_REG(SW3, CPCAP_REG_S3C, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW3_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(SW4, CPCAP_REG_S4C1, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW4_SEL, sw2_sw4_val_tbl,
		  0xf00, 0x7f, 0x900, 0, 100),
	CPCAP_REG(SW5, CPCAP_REG_S5C, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW5_SEL, sw5_val_tbl,
		  0x2a, 0, 0x22, 0, 0),
	CPCAP_REG(SW6, CPCAP_REG_S6C, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_SW6_SEL, unknown_val_tbl,
		  0, 0, 0, 0, 0),
	CPCAP_REG(VCAM, CPCAP_REG_VCAMC, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_VCAM_SEL, vcam_val_tbl,
		  0x87, 0x30, 0x7, 0, 420),
	CPCAP_REG(VCSI, CPCAP_REG_VCSIC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VCSI_SEL, vcsi_val_tbl,
		  0x47, 0x10, 0x7, 0, 350),
	CPCAP_REG(VDAC, CPCAP_REG_VDACC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VDAC_SEL, vdac_val_tbl,
		  0x87, 0x30, 0x3, 0, 420),
	CPCAP_REG(VDIG, CPCAP_REG_VDIGC, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_VDIG_SEL, vdig_val_tbl,
		  0x87, 0x30, 0x5, 0, 420),
	CPCAP_REG(VFUSE, CPCAP_REG_VFUSEC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VFUSE_SEL, vfuse_val_tbl,
		  0x80, 0xf, 0x80, 0, 420),
	CPCAP_REG(VHVIO, CPCAP_REG_VHVIOC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VHVIO_SEL, vhvio_val_tbl,
		  0x17, 0, 0x2, 0, 0),
	CPCAP_REG(VSDIO, CPCAP_REG_VSDIOC, CPCAP_REG_ASSIGN2,
		  CPCAP_BIT_VSDIO_SEL, vsdio_val_tbl,
		  0x87, 0x38, 0x2, 0, 420),
	CPCAP_REG(VPLL, CPCAP_REG_VPLLC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VPLL_SEL, vpll_val_tbl,
		  0x43, 0x18, 0x1, 0, 420),
	CPCAP_REG(VRF1, CPCAP_REG_VRF1C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VRF1_SEL, vrf1_val_tbl,
		  0xac, 0x2, 0xc, 0, 10),
	CPCAP_REG(VRF2, CPCAP_REG_VRF2C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VRF2_SEL, vrf2_val_tbl,
		  0x23, 0x8, 0x3, 0, 10),
	CPCAP_REG(VRFREF, CPCAP_REG_VRFREFC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VRFREF_SEL, vrfref_val_tbl,
		  0x23, 0x8, 0x3, 0, 420),
	CPCAP_REG(VWLAN1, CPCAP_REG_VWLAN1C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VWLAN1_SEL, vwlan1_val_tbl,
		  0x47, 0x10, 0x5, 0, 420),
	CPCAP_REG(VWLAN2, CPCAP_REG_VWLAN2C, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VWLAN2_SEL, vwlan2_val_tbl,
		  0x20c, 0xc0, 0x8, 0, 420),
	CPCAP_REG(VSIM, CPCAP_REG_VSIMC, CPCAP_REG_ASSIGN3,
		  0xffff, vsim_val_tbl,
		  0x23, 0x8, 0x3, 0, 420),
	CPCAP_REG(VSIMCARD, CPCAP_REG_VSIMC, CPCAP_REG_ASSIGN3,
		  0xffff, vsimcard_val_tbl,
		  0x1e80, 0x8, 0x1e00, 0, 420),
	CPCAP_REG(VVIB, CPCAP_REG_VVIBC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VVIB_SEL, vvib_val_tbl,
		  0x1, 0xc, 0, 0x1, 500),
	CPCAP_REG(VUSB, CPCAP_REG_VUSBC, CPCAP_REG_ASSIGN3,
		  CPCAP_BIT_VUSB_SEL, vusb_val_tbl,
		  0x11c, 0x40, 0xc, 0, 0),
	CPCAP_REG(VAUDIO, CPCAP_REG_VAUDIOC, CPCAP_REG_ASSIGN4,
		  CPCAP_BIT_VAUDIO_SEL, vaudio_val_tbl,
		  0x16, 0x1, 0x4, 0, 0),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cpcap_regulator_id_table[] = अणु
	अणु
		.compatible = "motorola,cpcap-regulator",
	पूर्ण,
	अणु
		.compatible = "motorola,mapphone-cpcap-regulator",
		.data = omap4_regulators,
	पूर्ण,
	अणु
		.compatible = "motorola,xoom-cpcap-regulator",
		.data = xoom_regulators,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_regulator_id_table);

अटल पूर्णांक cpcap_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_ddata *ddata;
	स्थिर काष्ठा cpcap_regulator *match_data;
	काष्ठा regulator_config config;
	पूर्णांक i;

	match_data = of_device_get_match_data(&pdev->dev);
	अगर (!match_data) अणु
		dev_err(&pdev->dev, "no configuration data found\n");

		वापस -ENODEV;
	पूर्ण

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->reg = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!ddata->reg)
		वापस -ENODEV;

	ddata->dev = &pdev->dev;
	ddata->soc = match_data;
	platक्रमm_set_drvdata(pdev, ddata);

	स_रखो(&config, 0, माप(config));
	config.dev = &pdev->dev;
	config.regmap = ddata->reg;

	क्रम (i = 0; i < CPCAP_NR_REGULATORS; i++) अणु
		स्थिर काष्ठा cpcap_regulator *regulator = &ddata->soc[i];
		काष्ठा regulator_dev *rdev;

		अगर (!regulator->rdesc.name)
			अवरोध;

		अगर (regulator->rdesc.volt_table == unknown_val_tbl)
			जारी;

		config.driver_data = (व्योम *)regulator;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
					       &regulator->rdesc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				regulator->rdesc.name);

			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_regulator_driver = अणु
	.probe		= cpcap_regulator_probe,
	.driver		= अणु
		.name	= "cpcap-regulator",
		.of_match_table = of_match_ptr(cpcap_regulator_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cpcap_regulator_driver);

MODULE_ALIAS("platform:cpcap-regulator");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("CPCAP regulator driver");
MODULE_LICENSE("GPL v2");
