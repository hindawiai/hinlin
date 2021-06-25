<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Regulator Driver क्रम Freescale MC13783 PMIC
//
// Copyright 2010 Yong Shen <yong.shen@linaro.org>
// Copyright (C) 2008 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
// Copyright 2009 Alberto Panizzo <maramaopercheseimorto@gmail.com>

#समावेश <linux/mfd/mc13783.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश "mc13xxx.h"

#घोषणा MC13783_REG_SWITCHERS0			24
/* Enable करोes not exist क्रम SW1A */
#घोषणा MC13783_REG_SWITCHERS0_SW1AEN			0
#घोषणा MC13783_REG_SWITCHERS0_SW1AVSEL			0
#घोषणा MC13783_REG_SWITCHERS0_SW1AVSEL_M		(63 << 0)

#घोषणा MC13783_REG_SWITCHERS1			25
/* Enable करोes not exist क्रम SW1B */
#घोषणा MC13783_REG_SWITCHERS1_SW1BEN			0
#घोषणा MC13783_REG_SWITCHERS1_SW1BVSEL			0
#घोषणा MC13783_REG_SWITCHERS1_SW1BVSEL_M		(63 << 0)

#घोषणा MC13783_REG_SWITCHERS2			26
/* Enable करोes not exist क्रम SW2A */
#घोषणा MC13783_REG_SWITCHERS2_SW2AEN			0
#घोषणा MC13783_REG_SWITCHERS2_SW2AVSEL			0
#घोषणा MC13783_REG_SWITCHERS2_SW2AVSEL_M		(63 << 0)

#घोषणा MC13783_REG_SWITCHERS3			27
/* Enable करोes not exist क्रम SW2B */
#घोषणा MC13783_REG_SWITCHERS3_SW2BEN			0
#घोषणा MC13783_REG_SWITCHERS3_SW2BVSEL			0
#घोषणा MC13783_REG_SWITCHERS3_SW2BVSEL_M		(63 << 0)

#घोषणा MC13783_REG_SWITCHERS5			29
#घोषणा MC13783_REG_SWITCHERS5_SW3EN			(1 << 20)
#घोषणा MC13783_REG_SWITCHERS5_SW3VSEL			18
#घोषणा MC13783_REG_SWITCHERS5_SW3VSEL_M		(3 << 18)

#घोषणा MC13783_REG_REGULATORSETTING0		30
#घोषणा MC13783_REG_REGULATORSETTING0_VIOLOVSEL		2
#घोषणा MC13783_REG_REGULATORSETTING0_VDIGVSEL		4
#घोषणा MC13783_REG_REGULATORSETTING0_VGENVSEL		6
#घोषणा MC13783_REG_REGULATORSETTING0_VRFDIGVSEL	9
#घोषणा MC13783_REG_REGULATORSETTING0_VRFREFVSEL	11
#घोषणा MC13783_REG_REGULATORSETTING0_VRFCPVSEL		13
#घोषणा MC13783_REG_REGULATORSETTING0_VSIMVSEL		14
#घोषणा MC13783_REG_REGULATORSETTING0_VESIMVSEL		15
#घोषणा MC13783_REG_REGULATORSETTING0_VCAMVSEL		16

#घोषणा MC13783_REG_REGULATORSETTING0_VIOLOVSEL_M	(3 << 2)
#घोषणा MC13783_REG_REGULATORSETTING0_VDIGVSEL_M	(3 << 4)
#घोषणा MC13783_REG_REGULATORSETTING0_VGENVSEL_M	(7 << 6)
#घोषणा MC13783_REG_REGULATORSETTING0_VRFDIGVSEL_M	(3 << 9)
#घोषणा MC13783_REG_REGULATORSETTING0_VRFREFVSEL_M	(3 << 11)
#घोषणा MC13783_REG_REGULATORSETTING0_VRFCPVSEL_M	(1 << 13)
#घोषणा MC13783_REG_REGULATORSETTING0_VSIMVSEL_M	(1 << 14)
#घोषणा MC13783_REG_REGULATORSETTING0_VESIMVSEL_M	(1 << 15)
#घोषणा MC13783_REG_REGULATORSETTING0_VCAMVSEL_M	(7 << 16)

#घोषणा MC13783_REG_REGULATORSETTING1		31
#घोषणा MC13783_REG_REGULATORSETTING1_VVIBVSEL		0
#घोषणा MC13783_REG_REGULATORSETTING1_VRF1VSEL		2
#घोषणा MC13783_REG_REGULATORSETTING1_VRF2VSEL		4
#घोषणा MC13783_REG_REGULATORSETTING1_VMMC1VSEL		6
#घोषणा MC13783_REG_REGULATORSETTING1_VMMC2VSEL		9

#घोषणा MC13783_REG_REGULATORSETTING1_VVIBVSEL_M	(3 << 0)
#घोषणा MC13783_REG_REGULATORSETTING1_VRF1VSEL_M	(3 << 2)
#घोषणा MC13783_REG_REGULATORSETTING1_VRF2VSEL_M	(3 << 4)
#घोषणा MC13783_REG_REGULATORSETTING1_VMMC1VSEL_M	(7 << 6)
#घोषणा MC13783_REG_REGULATORSETTING1_VMMC2VSEL_M	(7 << 9)

#घोषणा MC13783_REG_REGULATORMODE0		32
#घोषणा MC13783_REG_REGULATORMODE0_VAUDIOEN		(1 << 0)
#घोषणा MC13783_REG_REGULATORMODE0_VIOHIEN		(1 << 3)
#घोषणा MC13783_REG_REGULATORMODE0_VIOLOEN		(1 << 6)
#घोषणा MC13783_REG_REGULATORMODE0_VDIGEN		(1 << 9)
#घोषणा MC13783_REG_REGULATORMODE0_VGENEN		(1 << 12)
#घोषणा MC13783_REG_REGULATORMODE0_VRFDIGEN		(1 << 15)
#घोषणा MC13783_REG_REGULATORMODE0_VRFREFEN		(1 << 18)
#घोषणा MC13783_REG_REGULATORMODE0_VRFCPEN		(1 << 21)

#घोषणा MC13783_REG_REGULATORMODE1		33
#घोषणा MC13783_REG_REGULATORMODE1_VSIMEN		(1 << 0)
#घोषणा MC13783_REG_REGULATORMODE1_VESIMEN		(1 << 3)
#घोषणा MC13783_REG_REGULATORMODE1_VCAMEN		(1 << 6)
#घोषणा MC13783_REG_REGULATORMODE1_VRFBGEN		(1 << 9)
#घोषणा MC13783_REG_REGULATORMODE1_VVIBEN		(1 << 11)
#घोषणा MC13783_REG_REGULATORMODE1_VRF1EN		(1 << 12)
#घोषणा MC13783_REG_REGULATORMODE1_VRF2EN		(1 << 15)
#घोषणा MC13783_REG_REGULATORMODE1_VMMC1EN		(1 << 18)
#घोषणा MC13783_REG_REGULATORMODE1_VMMC2EN		(1 << 21)

#घोषणा MC13783_REG_POWERMISC			34
#घोषणा MC13783_REG_POWERMISC_GPO1EN			(1 << 6)
#घोषणा MC13783_REG_POWERMISC_GPO2EN			(1 << 8)
#घोषणा MC13783_REG_POWERMISC_GPO3EN			(1 << 10)
#घोषणा MC13783_REG_POWERMISC_GPO4EN			(1 << 12)
#घोषणा MC13783_REG_POWERMISC_PWGT1SPIEN		(1 << 15)
#घोषणा MC13783_REG_POWERMISC_PWGT2SPIEN		(1 << 16)

#घोषणा MC13783_REG_POWERMISC_PWGTSPI_M			(3 << 15)


/* Voltage Values */
अटल स्थिर पूर्णांक mc13783_sw1x_val[] = अणु
	900000, 925000, 950000, 975000,
	1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000,
	1600000, 1625000, 1650000, 1675000,
	1700000, 1700000, 1700000, 1700000,
	1800000, 1800000, 1800000, 1800000,
	1850000, 1850000, 1850000, 1850000,
	2000000, 2000000, 2000000, 2000000,
	2100000, 2100000, 2100000, 2100000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
पूर्ण;

अटल स्थिर पूर्णांक mc13783_sw2x_val[] = अणु
	900000, 925000, 950000, 975000,
	1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000,
	1600000, 1625000, 1650000, 1675000,
	1700000, 1700000, 1700000, 1700000,
	1800000, 1800000, 1800000, 1800000,
	1900000, 1900000, 1900000, 1900000,
	2000000, 2000000, 2000000, 2000000,
	2100000, 2100000, 2100000, 2100000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_sw3_val[] = अणु
	5000000, 5000000, 5000000, 5500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vaudio_val[] = अणु
	2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_viohi_val[] = अणु
	2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_violo_val[] = अणु
	1200000, 1300000, 1500000, 1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vdig_val[] = अणु
	1200000, 1300000, 1500000, 1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vgen_val[] = अणु
	1200000, 1300000, 1500000, 1800000,
	1100000, 2000000, 2775000, 2400000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vrfdig_val[] = अणु
	1200000, 1500000, 1800000, 1875000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vrfref_val[] = अणु
	2475000, 2600000, 2700000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vrfcp_val[] = अणु
	2700000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vsim_val[] = अणु
	1800000, 2900000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vesim_val[] = अणु
	1800000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vcam_val[] = अणु
	1500000, 1800000, 2500000, 2550000,
	2600000, 2750000, 2800000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vrfbg_val[] = अणु
	1250000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vvib_val[] = अणु
	1300000, 1800000, 2000000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vmmc_val[] = अणु
	1600000, 1800000, 2000000, 2600000,
	2700000, 2800000, 2900000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_vrf_val[] = अणु
	1500000, 1875000, 2700000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_gpo_val[] = अणु
	3100000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13783_pwgtdrv_val[] = अणु
	5500000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mc13783_gpo_regulator_ops;

#घोषणा MC13783_DEFINE(prefix, name, node, reg, vsel_reg, voltages)	\
	MC13xxx_DEFINE(MC13783_REG_, name, node, reg, vsel_reg, voltages, \
			mc13xxx_regulator_ops)

#घोषणा MC13783_FIXED_DEFINE(prefix, name, node, reg, voltages)		\
	MC13xxx_FIXED_DEFINE(MC13783_REG_, name, node, reg, voltages,	\
			mc13xxx_fixed_regulator_ops)

#घोषणा MC13783_GPO_DEFINE(prefix, name, node, reg, voltages)		\
	MC13xxx_GPO_DEFINE(MC13783_REG_, name, node, reg, voltages,	\
			mc13783_gpo_regulator_ops)

#घोषणा MC13783_DEFINE_SW(_name, _node, _reg, _vsel_reg, _voltages)	\
	MC13783_DEFINE(REG, _name, _node, _reg, _vsel_reg, _voltages)
#घोषणा MC13783_DEFINE_REGU(_name, _node, _reg, _vsel_reg, _voltages)	\
	MC13783_DEFINE(REG, _name, _node, _reg, _vsel_reg, _voltages)

अटल काष्ठा mc13xxx_regulator mc13783_regulators[] = अणु
	MC13783_DEFINE_SW(SW1A, sw1a, SWITCHERS0, SWITCHERS0, mc13783_sw1x_val),
	MC13783_DEFINE_SW(SW1B, sw1b, SWITCHERS1, SWITCHERS1, mc13783_sw1x_val),
	MC13783_DEFINE_SW(SW2A, sw2a, SWITCHERS2, SWITCHERS2, mc13783_sw2x_val),
	MC13783_DEFINE_SW(SW2B, sw2b, SWITCHERS3, SWITCHERS3, mc13783_sw2x_val),
	MC13783_DEFINE_SW(SW3, sw3, SWITCHERS5, SWITCHERS5, mc13783_sw3_val),

	MC13783_FIXED_DEFINE(REG, VAUDIO, vaudio, REGULATORMODE0, mc13783_vaudio_val),
	MC13783_FIXED_DEFINE(REG, VIOHI, viohi, REGULATORMODE0, mc13783_viohi_val),
	MC13783_DEFINE_REGU(VIOLO, violo, REGULATORMODE0, REGULATORSETTING0,
			    mc13783_violo_val),
	MC13783_DEFINE_REGU(VDIG, vdig, REGULATORMODE0, REGULATORSETTING0,
			    mc13783_vdig_val),
	MC13783_DEFINE_REGU(VGEN, vgen, REGULATORMODE0, REGULATORSETTING0,
			    mc13783_vgen_val),
	MC13783_DEFINE_REGU(VRFDIG, vrfdig, REGULATORMODE0, REGULATORSETTING0,
			    mc13783_vrfdig_val),
	MC13783_DEFINE_REGU(VRFREF, vrfref, REGULATORMODE0, REGULATORSETTING0,
			    mc13783_vrfref_val),
	MC13783_DEFINE_REGU(VRFCP, vrfcp, REGULATORMODE0, REGULATORSETTING0,
			    mc13783_vrfcp_val),
	MC13783_DEFINE_REGU(VSIM, vsim, REGULATORMODE1, REGULATORSETTING0,
			    mc13783_vsim_val),
	MC13783_DEFINE_REGU(VESIM, vesim, REGULATORMODE1, REGULATORSETTING0,
			    mc13783_vesim_val),
	MC13783_DEFINE_REGU(VCAM, vcam, REGULATORMODE1, REGULATORSETTING0,
			    mc13783_vcam_val),
	MC13783_FIXED_DEFINE(REG, VRFBG, vrfbg, REGULATORMODE1, mc13783_vrfbg_val),
	MC13783_DEFINE_REGU(VVIB, vvib, REGULATORMODE1, REGULATORSETTING1,
			    mc13783_vvib_val),
	MC13783_DEFINE_REGU(VRF1, vrf1, REGULATORMODE1, REGULATORSETTING1,
			    mc13783_vrf_val),
	MC13783_DEFINE_REGU(VRF2, vrf2, REGULATORMODE1, REGULATORSETTING1,
			    mc13783_vrf_val),
	MC13783_DEFINE_REGU(VMMC1, vmmc1, REGULATORMODE1, REGULATORSETTING1,
			    mc13783_vmmc_val),
	MC13783_DEFINE_REGU(VMMC2, vmmc2, REGULATORMODE1, REGULATORSETTING1,
			    mc13783_vmmc_val),
	MC13783_GPO_DEFINE(REG, GPO1, gpo1, POWERMISC, mc13783_gpo_val),
	MC13783_GPO_DEFINE(REG, GPO2, gpo1, POWERMISC, mc13783_gpo_val),
	MC13783_GPO_DEFINE(REG, GPO3, gpo1, POWERMISC, mc13783_gpo_val),
	MC13783_GPO_DEFINE(REG, GPO4, gpo1, POWERMISC, mc13783_gpo_val),
	MC13783_GPO_DEFINE(REG, PWGT1SPI, pwgt1spi, POWERMISC, mc13783_pwgtdrv_val),
	MC13783_GPO_DEFINE(REG, PWGT2SPI, pwgt2spi, POWERMISC, mc13783_pwgtdrv_val),
पूर्ण;

अटल पूर्णांक mc13783_घातermisc_rmw(काष्ठा mc13xxx_regulator_priv *priv, u32 mask,
		u32 val)
अणु
	काष्ठा mc13xxx *mc13783 = priv->mc13xxx;
	पूर्णांक ret;
	u32 valपढ़ो;

	BUG_ON(val & ~mask);

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_पढ़ो(mc13783, MC13783_REG_POWERMISC, &valपढ़ो);
	अगर (ret)
		जाओ out;

	/* Update the stored state क्रम Power Gates. */
	priv->घातermisc_pwgt_state =
				(priv->घातermisc_pwgt_state & ~mask) | val;
	priv->घातermisc_pwgt_state &= MC13783_REG_POWERMISC_PWGTSPI_M;

	/* Conकाष्ठा the new रेजिस्टर value */
	valपढ़ो = (valपढ़ो & ~mask) | val;
	/* Overग_लिखो the PWGTxEN with the stored version */
	valपढ़ो = (valपढ़ो & ~MC13783_REG_POWERMISC_PWGTSPI_M) |
						priv->घातermisc_pwgt_state;

	ret = mc13xxx_reg_ग_लिखो(mc13783, MC13783_REG_POWERMISC, valपढ़ो);
out:
	mc13xxx_unlock(priv->mc13xxx);
	वापस ret;
पूर्ण

अटल पूर्णांक mc13783_gpo_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक id = rdev_get_id(rdev);
	u32 en_val = mc13xxx_regulators[id].enable_bit;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	/* Power Gate enable value is 0 */
	अगर (id == MC13783_REG_PWGT1SPI ||
	    id == MC13783_REG_PWGT2SPI)
		en_val = 0;

	वापस mc13783_घातermisc_rmw(priv, mc13xxx_regulators[id].enable_bit,
					en_val);
पूर्ण

अटल पूर्णांक mc13783_gpo_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक id = rdev_get_id(rdev);
	u32 dis_val = 0;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	/* Power Gate disable value is 1 */
	अगर (id == MC13783_REG_PWGT1SPI ||
	    id == MC13783_REG_PWGT2SPI)
		dis_val = mc13xxx_regulators[id].enable_bit;

	वापस mc13783_घातermisc_rmw(priv, mc13xxx_regulators[id].enable_bit,
					dis_val);
पूर्ण

अटल पूर्णांक mc13783_gpo_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक ret, id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, mc13xxx_regulators[id].reg, &val);
	mc13xxx_unlock(priv->mc13xxx);

	अगर (ret)
		वापस ret;

	/* Power Gates state is stored in घातermisc_pwgt_state
	 * where the meaning of bits is negated */
	val = (val & ~MC13783_REG_POWERMISC_PWGTSPI_M) |
	      (priv->घातermisc_pwgt_state ^ MC13783_REG_POWERMISC_PWGTSPI_M);

	वापस (val & mc13xxx_regulators[id].enable_bit) != 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mc13783_gpo_regulator_ops = अणु
	.enable = mc13783_gpo_regulator_enable,
	.disable = mc13783_gpo_regulator_disable,
	.is_enabled = mc13783_gpo_regulator_is_enabled,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage = mc13xxx_fixed_regulator_set_voltage,
पूर्ण;

अटल पूर्णांक mc13783_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv;
	काष्ठा mc13xxx *mc13783 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा mc13xxx_regulator_platक्रमm_data *pdata =
		dev_get_platdata(&pdev->dev);
	काष्ठा mc13xxx_regulator_init_data *mc13xxx_data;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, num_regulators;

	num_regulators = mc13xxx_get_num_regulators_dt(pdev);

	अगर (num_regulators <= 0 && pdata)
		num_regulators = pdata->num_regulators;
	अगर (num_regulators <= 0)
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev,
			    काष्ठा_size(priv, regulators, num_regulators),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->num_regulators = num_regulators;
	priv->mc13xxx_regulators = mc13783_regulators;
	priv->mc13xxx = mc13783;
	platक्रमm_set_drvdata(pdev, priv);

	mc13xxx_data = mc13xxx_parse_regulators_dt(pdev, mc13783_regulators,
					ARRAY_SIZE(mc13783_regulators));

	क्रम (i = 0; i < priv->num_regulators; i++) अणु
		काष्ठा regulator_init_data *init_data;
		काष्ठा regulator_desc *desc;
		काष्ठा device_node *node = शून्य;
		पूर्णांक id;

		अगर (mc13xxx_data) अणु
			id = mc13xxx_data[i].id;
			init_data = mc13xxx_data[i].init_data;
			node = mc13xxx_data[i].node;
		पूर्ण अन्यथा अणु
			id = pdata->regulators[i].id;
			init_data = pdata->regulators[i].init_data;
		पूर्ण
		desc = &mc13783_regulators[id].desc;

		config.dev = &pdev->dev;
		config.init_data = init_data;
		config.driver_data = priv;
		config.of_node = node;

		priv->regulators[i] = devm_regulator_रेजिस्टर(&pdev->dev, desc,
							      &config);
		अगर (IS_ERR(priv->regulators[i])) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				mc13783_regulators[i].desc.name);
			वापस PTR_ERR(priv->regulators[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mc13783_regulator_driver = अणु
	.driver	= अणु
		.name	= "mc13783-regulator",
	पूर्ण,
	.probe		= mc13783_regulator_probe,
पूर्ण;

अटल पूर्णांक __init mc13783_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mc13783_regulator_driver);
पूर्ण
subsys_initcall(mc13783_regulator_init);

अटल व्योम __निकास mc13783_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mc13783_regulator_driver);
पूर्ण
module_निकास(mc13783_regulator_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("Regulator Driver for Freescale MC13783 PMIC");
MODULE_ALIAS("platform:mc13783-regulator");
