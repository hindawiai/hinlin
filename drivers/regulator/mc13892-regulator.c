<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Regulator Driver क्रम Freescale MC13892 PMIC
//
// Copyright 2010 Yong Shen <yong.shen@linaro.org>
//
// Based on draft driver from Arnaud Patard <arnaud.patard@rtp-net.org>

#समावेश <linux/mfd/mc13892.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश "mc13xxx.h"

#घोषणा MC13892_REVISION			7

#घोषणा MC13892_POWERCTL0			13
#घोषणा MC13892_POWERCTL0_USEROFFSPI		3
#घोषणा MC13892_POWERCTL0_VCOINCELLVSEL		20
#घोषणा MC13892_POWERCTL0_VCOINCELLVSEL_M	(7<<20)
#घोषणा MC13892_POWERCTL0_VCOINCELLEN		(1<<23)

#घोषणा MC13892_SWITCHERS0_SWxHI		(1<<23)

#घोषणा MC13892_SWITCHERS0			24
#घोषणा MC13892_SWITCHERS0_SW1VSEL		0
#घोषणा MC13892_SWITCHERS0_SW1VSEL_M		(0x1f<<0)
#घोषणा MC13892_SWITCHERS0_SW1HI		(1<<23)
#घोषणा MC13892_SWITCHERS0_SW1EN		0

#घोषणा MC13892_SWITCHERS1			25
#घोषणा MC13892_SWITCHERS1_SW2VSEL		0
#घोषणा MC13892_SWITCHERS1_SW2VSEL_M		(0x1f<<0)
#घोषणा MC13892_SWITCHERS1_SW2HI		(1<<23)
#घोषणा MC13892_SWITCHERS1_SW2EN		0

#घोषणा MC13892_SWITCHERS2			26
#घोषणा MC13892_SWITCHERS2_SW3VSEL		0
#घोषणा MC13892_SWITCHERS2_SW3VSEL_M		(0x1f<<0)
#घोषणा MC13892_SWITCHERS2_SW3HI		(1<<23)
#घोषणा MC13892_SWITCHERS2_SW3EN		0

#घोषणा MC13892_SWITCHERS3			27
#घोषणा MC13892_SWITCHERS3_SW4VSEL		0
#घोषणा MC13892_SWITCHERS3_SW4VSEL_M		(0x1f<<0)
#घोषणा MC13892_SWITCHERS3_SW4HI		(1<<23)
#घोषणा MC13892_SWITCHERS3_SW4EN		0

#घोषणा MC13892_SWITCHERS4			28
#घोषणा MC13892_SWITCHERS4_SW1MODE		0
#घोषणा MC13892_SWITCHERS4_SW1MODE_AUTO		(8<<0)
#घोषणा MC13892_SWITCHERS4_SW1MODE_M		(0xf<<0)
#घोषणा MC13892_SWITCHERS4_SW2MODE		10
#घोषणा MC13892_SWITCHERS4_SW2MODE_AUTO		(8<<10)
#घोषणा MC13892_SWITCHERS4_SW2MODE_M		(0xf<<10)

#घोषणा MC13892_SWITCHERS5			29
#घोषणा MC13892_SWITCHERS5_SW3MODE		0
#घोषणा MC13892_SWITCHERS5_SW3MODE_AUTO		(8<<0)
#घोषणा MC13892_SWITCHERS5_SW3MODE_M		(0xf<<0)
#घोषणा MC13892_SWITCHERS5_SW4MODE		8
#घोषणा MC13892_SWITCHERS5_SW4MODE_AUTO		(8<<8)
#घोषणा MC13892_SWITCHERS5_SW4MODE_M		(0xf<<8)
#घोषणा MC13892_SWITCHERS5_SWBSTEN		(1<<20)

#घोषणा MC13892_REGULATORSETTING0		30
#घोषणा MC13892_REGULATORSETTING0_VGEN1VSEL	0
#घोषणा MC13892_REGULATORSETTING0_VDIGVSEL	4
#घोषणा MC13892_REGULATORSETTING0_VGEN2VSEL	6
#घोषणा MC13892_REGULATORSETTING0_VPLLVSEL	9
#घोषणा MC13892_REGULATORSETTING0_VUSB2VSEL	11
#घोषणा MC13892_REGULATORSETTING0_VGEN3VSEL	14
#घोषणा MC13892_REGULATORSETTING0_VCAMVSEL	16

#घोषणा MC13892_REGULATORSETTING0_VGEN1VSEL_M	(3<<0)
#घोषणा MC13892_REGULATORSETTING0_VDIGVSEL_M	(3<<4)
#घोषणा MC13892_REGULATORSETTING0_VGEN2VSEL_M	(7<<6)
#घोषणा MC13892_REGULATORSETTING0_VPLLVSEL_M	(3<<9)
#घोषणा MC13892_REGULATORSETTING0_VUSB2VSEL_M	(3<<11)
#घोषणा MC13892_REGULATORSETTING0_VGEN3VSEL_M	(1<<14)
#घोषणा MC13892_REGULATORSETTING0_VCAMVSEL_M	(3<<16)

#घोषणा MC13892_REGULATORSETTING1		31
#घोषणा MC13892_REGULATORSETTING1_VVIDEOVSEL	2
#घोषणा MC13892_REGULATORSETTING1_VAUDIOVSEL	4
#घोषणा MC13892_REGULATORSETTING1_VSDVSEL	6

#घोषणा MC13892_REGULATORSETTING1_VVIDEOVSEL_M	(3<<2)
#घोषणा MC13892_REGULATORSETTING1_VAUDIOVSEL_M	(3<<4)
#घोषणा MC13892_REGULATORSETTING1_VSDVSEL_M	(7<<6)

#घोषणा MC13892_REGULATORMODE0			32
#घोषणा MC13892_REGULATORMODE0_VGEN1EN		(1<<0)
#घोषणा MC13892_REGULATORMODE0_VGEN1STDBY	(1<<1)
#घोषणा MC13892_REGULATORMODE0_VGEN1MODE	(1<<2)
#घोषणा MC13892_REGULATORMODE0_VIOHIEN		(1<<3)
#घोषणा MC13892_REGULATORMODE0_VIOHISTDBY	(1<<4)
#घोषणा MC13892_REGULATORMODE0_VIOHIMODE	(1<<5)
#घोषणा MC13892_REGULATORMODE0_VDIGEN		(1<<9)
#घोषणा MC13892_REGULATORMODE0_VDIGSTDBY	(1<<10)
#घोषणा MC13892_REGULATORMODE0_VDIGMODE		(1<<11)
#घोषणा MC13892_REGULATORMODE0_VGEN2EN		(1<<12)
#घोषणा MC13892_REGULATORMODE0_VGEN2STDBY	(1<<13)
#घोषणा MC13892_REGULATORMODE0_VGEN2MODE	(1<<14)
#घोषणा MC13892_REGULATORMODE0_VPLLEN		(1<<15)
#घोषणा MC13892_REGULATORMODE0_VPLLSTDBY	(1<<16)
#घोषणा MC13892_REGULATORMODE0_VPLLMODE		(1<<17)
#घोषणा MC13892_REGULATORMODE0_VUSB2EN		(1<<18)
#घोषणा MC13892_REGULATORMODE0_VUSB2STDBY	(1<<19)
#घोषणा MC13892_REGULATORMODE0_VUSB2MODE	(1<<20)

#घोषणा MC13892_REGULATORMODE1			33
#घोषणा MC13892_REGULATORMODE1_VGEN3EN		(1<<0)
#घोषणा MC13892_REGULATORMODE1_VGEN3STDBY	(1<<1)
#घोषणा MC13892_REGULATORMODE1_VGEN3MODE	(1<<2)
#घोषणा MC13892_REGULATORMODE1_VCAMEN		(1<<6)
#घोषणा MC13892_REGULATORMODE1_VCAMSTDBY	(1<<7)
#घोषणा MC13892_REGULATORMODE1_VCAMMODE		(1<<8)
#घोषणा MC13892_REGULATORMODE1_VCAMCONFIGEN	(1<<9)
#घोषणा MC13892_REGULATORMODE1_VVIDEOEN		(1<<12)
#घोषणा MC13892_REGULATORMODE1_VVIDEOSTDBY	(1<<13)
#घोषणा MC13892_REGULATORMODE1_VVIDEOMODE	(1<<14)
#घोषणा MC13892_REGULATORMODE1_VAUDIOEN		(1<<15)
#घोषणा MC13892_REGULATORMODE1_VAUDIOSTDBY	(1<<16)
#घोषणा MC13892_REGULATORMODE1_VAUDIOMODE	(1<<17)
#घोषणा MC13892_REGULATORMODE1_VSDEN		(1<<18)
#घोषणा MC13892_REGULATORMODE1_VSDSTDBY		(1<<19)
#घोषणा MC13892_REGULATORMODE1_VSDMODE		(1<<20)

#घोषणा MC13892_POWERMISC			34
#घोषणा MC13892_POWERMISC_GPO1EN		(1<<6)
#घोषणा MC13892_POWERMISC_GPO2EN		(1<<8)
#घोषणा MC13892_POWERMISC_GPO3EN		(1<<10)
#घोषणा MC13892_POWERMISC_GPO4EN		(1<<12)
#घोषणा MC13892_POWERMISC_PWGT1SPIEN		(1<<15)
#घोषणा MC13892_POWERMISC_PWGT2SPIEN		(1<<16)
#घोषणा MC13892_POWERMISC_GPO4ADINEN		(1<<21)

#घोषणा MC13892_POWERMISC_PWGTSPI_M		(3 << 15)

#घोषणा MC13892_USB1				50
#घोषणा MC13892_USB1_VUSBEN			(1<<3)

अटल स्थिर अचिन्हित पूर्णांक mc13892_vcoincell[] = अणु
	2500000, 2700000, 2800000, 2900000, 3000000, 3100000,
	3200000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_sw1[] = अणु
	600000,   625000,  650000,  675000,  700000,  725000,
	750000,   775000,  800000,  825000,  850000,  875000,
	900000,   925000,  950000,  975000, 1000000, 1025000,
	1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000,
	1350000, 1375000
पूर्ण;

/*
 * Note: this table is used to derive SWxVSEL by index पूर्णांकo
 * the array. Offset the values by the index of 1100000uV
 * to get the actual रेजिस्टर value क्रम that voltage selector
 * अगर the HI bit is to be set as well.
 */
#घोषणा MC13892_SWxHI_SEL_OFFSET		20

अटल स्थिर अचिन्हित पूर्णांक mc13892_sw[] = अणु
	600000,   625000,  650000,  675000,  700000,  725000,
	750000,   775000,  800000,  825000,  850000,  875000,
	900000,   925000,  950000,  975000, 1000000, 1025000,
	1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000,
	1350000, 1375000, 1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000, 1600000, 1625000,
	1650000, 1675000, 1700000, 1725000, 1750000, 1775000,
	1800000, 1825000, 1850000, 1875000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_swbst[] = अणु
	5000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_viohi[] = अणु
	2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vpll[] = अणु
	1050000, 1250000, 1650000, 1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vdig[] = अणु
	1050000, 1250000, 1650000, 1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vsd[] = अणु
	1800000, 2000000, 2600000, 2700000,
	2800000, 2900000, 3000000, 3150000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vusb2[] = अणु
	2400000, 2600000, 2700000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vvideo[] = अणु
	2700000, 2775000, 2500000, 2600000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vaudio[] = अणु
	2300000, 2500000, 2775000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vcam[] = अणु
	2500000, 2600000, 2750000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vgen1[] = अणु
	1200000, 1500000, 2775000, 3150000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vgen2[] = अणु
	1200000, 1500000, 1600000, 1800000,
	2700000, 2800000, 3000000, 3150000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vgen3[] = अणु
	1800000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_vusb[] = अणु
	3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_gpo[] = अणु
	2750000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mc13892_pwgtdrv[] = अणु
	5000000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mc13892_gpo_regulator_ops;
अटल स्थिर काष्ठा regulator_ops mc13892_sw_regulator_ops;


#घोषणा MC13892_FIXED_DEFINE(name, node, reg, voltages)			\
	MC13xxx_FIXED_DEFINE(MC13892_, name, node, reg, voltages,	\
			mc13xxx_fixed_regulator_ops)

#घोषणा MC13892_GPO_DEFINE(name, node, reg, voltages)			\
	MC13xxx_GPO_DEFINE(MC13892_, name, node, reg, voltages,		\
			mc13892_gpo_regulator_ops)

#घोषणा MC13892_SW_DEFINE(name, node, reg, vsel_reg, voltages)		\
	MC13xxx_DEFINE(MC13892_, name, node, reg, vsel_reg, voltages,	\
			mc13892_sw_regulator_ops)

#घोषणा MC13892_DEFINE_REGU(name, node, reg, vsel_reg, voltages)	\
	MC13xxx_DEFINE(MC13892_, name, node, reg, vsel_reg, voltages, \
			mc13xxx_regulator_ops)

अटल काष्ठा mc13xxx_regulator mc13892_regulators[] = अणु
	MC13892_DEFINE_REGU(VCOINCELL, vcoincell, POWERCTL0, POWERCTL0, mc13892_vcoincell),
	MC13892_SW_DEFINE(SW1, sw1, SWITCHERS0, SWITCHERS0, mc13892_sw1),
	MC13892_SW_DEFINE(SW2, sw2, SWITCHERS1, SWITCHERS1, mc13892_sw),
	MC13892_SW_DEFINE(SW3, sw3, SWITCHERS2, SWITCHERS2, mc13892_sw),
	MC13892_SW_DEFINE(SW4, sw4, SWITCHERS3, SWITCHERS3, mc13892_sw),
	MC13892_FIXED_DEFINE(SWBST, swbst, SWITCHERS5, mc13892_swbst),
	MC13892_FIXED_DEFINE(VIOHI, viohi, REGULATORMODE0, mc13892_viohi),
	MC13892_DEFINE_REGU(VPLL, vpll, REGULATORMODE0, REGULATORSETTING0,
		mc13892_vpll),
	MC13892_DEFINE_REGU(VDIG, vdig, REGULATORMODE0, REGULATORSETTING0,
		mc13892_vdig),
	MC13892_DEFINE_REGU(VSD, vsd, REGULATORMODE1, REGULATORSETTING1,
		mc13892_vsd),
	MC13892_DEFINE_REGU(VUSB2, vusb2, REGULATORMODE0, REGULATORSETTING0,
		mc13892_vusb2),
	MC13892_DEFINE_REGU(VVIDEO, vvideo, REGULATORMODE1, REGULATORSETTING1,
		mc13892_vvideo),
	MC13892_DEFINE_REGU(VAUDIO, vaudio, REGULATORMODE1, REGULATORSETTING1,
		mc13892_vaudio),
	MC13892_DEFINE_REGU(VCAM, vcam, REGULATORMODE1, REGULATORSETTING0,
		mc13892_vcam),
	MC13892_DEFINE_REGU(VGEN1, vgen1, REGULATORMODE0, REGULATORSETTING0,
		mc13892_vgen1),
	MC13892_DEFINE_REGU(VGEN2, vgen2, REGULATORMODE0, REGULATORSETTING0,
		mc13892_vgen2),
	MC13892_DEFINE_REGU(VGEN3, vgen3, REGULATORMODE1, REGULATORSETTING0,
		mc13892_vgen3),
	MC13892_FIXED_DEFINE(VUSB, vusb, USB1, mc13892_vusb),
	MC13892_GPO_DEFINE(GPO1, gpo1, POWERMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(GPO2, gpo2, POWERMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(GPO3, gpo3, POWERMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(GPO4, gpo4, POWERMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(PWGT1SPI, pwgt1spi, POWERMISC, mc13892_pwgtdrv),
	MC13892_GPO_DEFINE(PWGT2SPI, pwgt2spi, POWERMISC, mc13892_pwgtdrv),
पूर्ण;

अटल पूर्णांक mc13892_घातermisc_rmw(काष्ठा mc13xxx_regulator_priv *priv, u32 mask,
				 u32 val)
अणु
	काष्ठा mc13xxx *mc13892 = priv->mc13xxx;
	पूर्णांक ret;
	u32 valपढ़ो;

	BUG_ON(val & ~mask);

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_पढ़ो(mc13892, MC13892_POWERMISC, &valपढ़ो);
	अगर (ret)
		जाओ out;

	/* Update the stored state क्रम Power Gates. */
	priv->घातermisc_pwgt_state =
		(priv->घातermisc_pwgt_state & ~mask) | val;
	priv->घातermisc_pwgt_state &= MC13892_POWERMISC_PWGTSPI_M;

	/* Conकाष्ठा the new रेजिस्टर value */
	valपढ़ो = (valपढ़ो & ~mask) | val;
	/* Overग_लिखो the PWGTxEN with the stored version */
	valपढ़ो = (valपढ़ो & ~MC13892_POWERMISC_PWGTSPI_M) |
		priv->घातermisc_pwgt_state;

	ret = mc13xxx_reg_ग_लिखो(mc13892, MC13892_POWERMISC, valपढ़ो);
out:
	mc13xxx_unlock(priv->mc13xxx);
	वापस ret;
पूर्ण

अटल पूर्णांक mc13892_gpo_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	u32 en_val = mc13892_regulators[id].enable_bit;
	u32 mask = mc13892_regulators[id].enable_bit;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	/* Power Gate enable value is 0 */
	अगर (id == MC13892_PWGT1SPI || id == MC13892_PWGT2SPI)
		en_val = 0;

	अगर (id == MC13892_GPO4)
		mask |= MC13892_POWERMISC_GPO4ADINEN;

	वापस mc13892_घातermisc_rmw(priv, mask, en_val);
पूर्ण

अटल पूर्णांक mc13892_gpo_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	u32 dis_val = 0;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	/* Power Gate disable value is 1 */
	अगर (id == MC13892_PWGT1SPI || id == MC13892_PWGT2SPI)
		dis_val = mc13892_regulators[id].enable_bit;

	वापस mc13892_घातermisc_rmw(priv, mc13892_regulators[id].enable_bit,
		dis_val);
पूर्ण

अटल पूर्णांक mc13892_gpo_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret, id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, mc13892_regulators[id].reg, &val);
	mc13xxx_unlock(priv->mc13xxx);

	अगर (ret)
		वापस ret;

	/* Power Gates state is stored in घातermisc_pwgt_state
	 * where the meaning of bits is negated */
	val = (val & ~MC13892_POWERMISC_PWGTSPI_M) |
		(priv->घातermisc_pwgt_state ^ MC13892_POWERMISC_PWGTSPI_M);

	वापस (val & mc13892_regulators[id].enable_bit) != 0;
पूर्ण


अटल स्थिर काष्ठा regulator_ops mc13892_gpo_regulator_ops = अणु
	.enable = mc13892_gpo_regulator_enable,
	.disable = mc13892_gpo_regulator_disable,
	.is_enabled = mc13892_gpo_regulator_is_enabled,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage = mc13xxx_fixed_regulator_set_voltage,
पूर्ण;

अटल पूर्णांक mc13892_sw_regulator_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret, id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val, selector;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx,
		mc13892_regulators[id].vsel_reg, &val);
	mc13xxx_unlock(priv->mc13xxx);
	अगर (ret)
		वापस ret;

	/*
	 * Figure out अगर the HI bit is set inside the चयनer mode रेजिस्टर
	 * since this means the selector value we वापस is at a dअगरferent
	 * offset पूर्णांकo the selector table.
	 *
	 * According to the MC13892 करोcumentation note 59 (Table 47) the SW1
	 * buck चयनer करोes not support output range programming thereक्रमe
	 * the HI bit must always reमुख्य 0. So करो not करो anything strange अगर
	 * our रेजिस्टर is MC13892_SWITCHERS0.
	 */

	selector = val & mc13892_regulators[id].vsel_mask;

	अगर ((mc13892_regulators[id].vsel_reg != MC13892_SWITCHERS0) &&
	    (val & MC13892_SWITCHERS0_SWxHI)) अणु
		selector += MC13892_SWxHI_SEL_OFFSET;
	पूर्ण

	dev_dbg(rdev_get_dev(rdev), "%s id: %d val: 0x%08x selector: %d\n",
			__func__, id, val, selector);

	वापस selector;
पूर्ण

अटल पूर्णांक mc13892_sw_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
						अचिन्हित selector)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक volt, mask, id = rdev_get_id(rdev);
	u32 reg_value;
	पूर्णांक ret;

	volt = rdev->desc->volt_table[selector];
	mask = mc13892_regulators[id].vsel_mask;
	reg_value = selector;

	/*
	 * Don't mess with the HI bit or support HI voltage offsets क्रम SW1.
	 *
	 * Since the get_voltage_sel callback has given a fudged value क्रम
	 * the selector offset, we need to back out that offset अगर HI is
	 * to be set so we ग_लिखो the correct value to the रेजिस्टर.
	 *
	 * The HI bit addition and selector offset handling COULD be more
	 * complicated by shअगरting and masking off the voltage selector part
	 * of the रेजिस्टर then logical OR it back in, but since the selector
	 * is at bits 4:0 there is very little poपूर्णांक. This makes the whole
	 * thing more पढ़ोable and we करो far less work.
	 */

	अगर (mc13892_regulators[id].vsel_reg != MC13892_SWITCHERS0) अणु
		mask |= MC13892_SWITCHERS0_SWxHI;

		अगर (volt > 1375000) अणु
			reg_value -= MC13892_SWxHI_SEL_OFFSET;
			reg_value |= MC13892_SWITCHERS0_SWxHI;
		पूर्ण अन्यथा अणु
			reg_value &= ~MC13892_SWITCHERS0_SWxHI;
		पूर्ण
	पूर्ण

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_rmw(priv->mc13xxx, mc13892_regulators[id].vsel_reg,
			      mask, reg_value);
	mc13xxx_unlock(priv->mc13xxx);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mc13892_sw_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = mc13892_sw_regulator_set_voltage_sel,
	.get_voltage_sel = mc13892_sw_regulator_get_voltage_sel,
पूर्ण;

अटल पूर्णांक mc13892_vcam_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक en_val = 0;
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret, id = rdev_get_id(rdev);

	अगर (mode == REGULATOR_MODE_FAST)
		en_val = MC13892_REGULATORMODE1_VCAMCONFIGEN;

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_rmw(priv->mc13xxx, mc13892_regulators[id].reg,
		MC13892_REGULATORMODE1_VCAMCONFIGEN, en_val);
	mc13xxx_unlock(priv->mc13xxx);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक mc13892_vcam_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret, id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, mc13892_regulators[id].reg, &val);
	mc13xxx_unlock(priv->mc13xxx);

	अगर (ret)
		वापस ret;

	अगर (val & MC13892_REGULATORMODE1_VCAMCONFIGEN)
		वापस REGULATOR_MODE_FAST;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल काष्ठा regulator_ops mc13892_vcam_ops;

अटल पूर्णांक mc13892_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv;
	काष्ठा mc13xxx *mc13892 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा mc13xxx_regulator_platक्रमm_data *pdata =
		dev_get_platdata(&pdev->dev);
	काष्ठा mc13xxx_regulator_init_data *mc13xxx_data;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, ret;
	पूर्णांक num_regulators = 0;
	u32 val;

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
	priv->mc13xxx_regulators = mc13892_regulators;
	priv->mc13xxx = mc13892;
	platक्रमm_set_drvdata(pdev, priv);

	mc13xxx_lock(mc13892);
	ret = mc13xxx_reg_पढ़ो(mc13892, MC13892_REVISION, &val);
	अगर (ret)
		जाओ err_unlock;

	/* enable चयन स्वतः mode (on 2.0A silicon only) */
	अगर ((val & 0x0000FFFF) == 0x45d0) अणु
		ret = mc13xxx_reg_rmw(mc13892, MC13892_SWITCHERS4,
			MC13892_SWITCHERS4_SW1MODE_M |
			MC13892_SWITCHERS4_SW2MODE_M,
			MC13892_SWITCHERS4_SW1MODE_AUTO |
			MC13892_SWITCHERS4_SW2MODE_AUTO);
		अगर (ret)
			जाओ err_unlock;

		ret = mc13xxx_reg_rmw(mc13892, MC13892_SWITCHERS5,
			MC13892_SWITCHERS5_SW3MODE_M |
			MC13892_SWITCHERS5_SW4MODE_M,
			MC13892_SWITCHERS5_SW3MODE_AUTO |
			MC13892_SWITCHERS5_SW4MODE_AUTO);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण
	mc13xxx_unlock(mc13892);

	/* update mc13892_vcam ops */
	स_नकल(&mc13892_vcam_ops, mc13892_regulators[MC13892_VCAM].desc.ops,
						माप(काष्ठा regulator_ops));
	mc13892_vcam_ops.set_mode = mc13892_vcam_set_mode;
	mc13892_vcam_ops.get_mode = mc13892_vcam_get_mode;
	mc13892_regulators[MC13892_VCAM].desc.ops = &mc13892_vcam_ops;

	mc13xxx_data = mc13xxx_parse_regulators_dt(pdev, mc13892_regulators,
					ARRAY_SIZE(mc13892_regulators));

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
		desc = &mc13892_regulators[id].desc;

		config.dev = &pdev->dev;
		config.init_data = init_data;
		config.driver_data = priv;
		config.of_node = node;

		priv->regulators[i] = devm_regulator_रेजिस्टर(&pdev->dev, desc,
							      &config);
		अगर (IS_ERR(priv->regulators[i])) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				mc13892_regulators[i].desc.name);
			वापस PTR_ERR(priv->regulators[i]);
		पूर्ण
	पूर्ण

	वापस 0;

err_unlock:
	mc13xxx_unlock(mc13892);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mc13892_regulator_driver = अणु
	.driver	= अणु
		.name	= "mc13892-regulator",
	पूर्ण,
	.probe	= mc13892_regulator_probe,
पूर्ण;

अटल पूर्णांक __init mc13892_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mc13892_regulator_driver);
पूर्ण
subsys_initcall(mc13892_regulator_init);

अटल व्योम __निकास mc13892_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mc13892_regulator_driver);
पूर्ण
module_निकास(mc13892_regulator_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yong Shen <yong.shen@linaro.org>");
MODULE_DESCRIPTION("Regulator Driver for Freescale MC13892 PMIC");
MODULE_ALIAS("platform:mc13892-regulator");
